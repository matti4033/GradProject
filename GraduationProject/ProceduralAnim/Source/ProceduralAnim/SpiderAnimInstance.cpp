#include "SpiderAnimInstance.h"
#include "SpiderFABRIK.h"
#include "SpiderMovementComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

void USpiderAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    Owner = Cast<ACharacter>(GetOwningActor());
}

void USpiderAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (!Owner) return;
    CachedDelta = DeltaSeconds;
    UpdateLegs(DeltaSeconds);
    UpdateBody(DeltaSeconds);
}

void USpiderAnimInstance::UpdateLegs(float DeltaSeconds)
{
    GroupCooldown[0] = FMath::Max(0.f, GroupCooldown[0] - DeltaSeconds);
    GroupCooldown[1] = FMath::Max(0.f, GroupCooldown[1] - DeltaSeconds);

    FRotator CurrentRot = Owner->GetActorRotation();
    float YawDelta = FMath::Abs(
        FMath::FindDeltaAngleDegrees(LastBodyRotation.Yaw, CurrentRot.Yaw));
    LastBodyRotation = CurrentRot;

    float TurnRate = (DeltaSeconds > 0.f) ? (YawDelta / DeltaSeconds) : 0.f;
    float TurnAlpha = FMath::Clamp(TurnRate / TurnRateFullScale, 0.f, 1.f);
    float EffectiveThreshold = FMath::Lerp(
        StepThreshold, StepThreshold * TurnStepThresholdScale, TurnAlpha);

    for (FSpiderLeg& Leg : Legs)
        DoRaycast(Leg);

    FVector Forward = Owner->GetActorForwardVector();
    FVector FRPos, FLPos, MRPos, MLPos;
    FRPos = FLPos = MRPos = MLPos = FVector::ZeroVector;

    for (const FSpiderLeg& Leg : Legs)
    {
        if (Leg.UpperBone == FName("LegFR_Upper")) FRPos = Leg.CurrentFootPos;
        if (Leg.UpperBone == FName("LegFL_Upper")) FLPos = Leg.CurrentFootPos;
        if (Leg.UpperBone == FName("LegMR_Upper")) MRPos = Leg.CurrentFootPos;
        if (Leg.UpperBone == FName("LegML_Upper")) MLPos = Leg.CurrentFootPos;
    }

    for (FSpiderLeg& Leg : Legs)
    {
        if (Leg.UpperBone == FName("LegMR_Upper") && !FRPos.IsNearlyZero())
        {
            float FrontDot = FVector::DotProduct(FRPos, Forward);
            float MidDot = FVector::DotProduct(Leg.DesiredFootPos, Forward);
            if (MidDot > FrontDot)
                Leg.DesiredFootPos -= Forward * (MidDot - FrontDot);
        }
        if (Leg.UpperBone == FName("LegML_Upper") && !FLPos.IsNearlyZero())
        {
            float FrontDot = FVector::DotProduct(FLPos, Forward);
            float MidDot = FVector::DotProduct(Leg.DesiredFootPos, Forward);
            if (MidDot > FrontDot)
                Leg.DesiredFootPos -= Forward * (MidDot - FrontDot);
        }
        if (Leg.UpperBone == FName("LegRR_Upper") && !MRPos.IsNearlyZero())
        {
            float MidDotVal = FVector::DotProduct(MRPos, Forward);
            float RearDot = FVector::DotProduct(Leg.DesiredFootPos, Forward);
            if (RearDot > MidDotVal)
                Leg.DesiredFootPos -= Forward * (RearDot - MidDotVal);
        }
        if (Leg.UpperBone == FName("LegRL_Upper") && !MLPos.IsNearlyZero())
        {
            float MidDotVal = FVector::DotProduct(MLPos, Forward);
            float RearDot = FVector::DotProduct(Leg.DesiredFootPos, Forward);
            if (RearDot > MidDotVal)
                Leg.DesiredFootPos -= Forward * (RearDot - MidDotVal);
        }
    }

    bool bGroupStepping[2] = { false, false };
    for (const FSpiderLeg& Leg : Legs)
        if (Leg.bIsStepping)
            bGroupStepping[Leg.GaitGroup] = true;

    bool bGroupNeedsStep[2] = { false, false };
    for (const FSpiderLeg& Leg : Legs)
    {
        if (!Leg.bIsStepping)
        {
            float Dist = FVector::Dist(Leg.CurrentFootPos, Leg.DesiredFootPos);
            if (Dist > EffectiveThreshold)
                bGroupNeedsStep[Leg.GaitGroup] = true;
        }
    }

    for (int32 Group = 0; Group < 2; Group++)
    {
        int32 OtherGroup = 1 - Group;
        if (bGroupNeedsStep[Group]
            && !bGroupStepping[Group]
            && !bGroupStepping[OtherGroup]
            && GroupCooldown[Group] <= 0.f)
        {
            for (FSpiderLeg& Leg : Legs)
            {
                if (Leg.GaitGroup == Group && !Leg.bIsStepping)
                {
                    Leg.bIsStepping = true;
                    Leg.StepProgress = 0.f;
                    Leg.StepStartPos = Leg.CurrentFootPos;
                    Leg.StepEndPos = Leg.DesiredFootPos;
                }
            }
            bGroupStepping[Group] = true;
        }
    }

    for (FSpiderLeg& Leg : Legs)
    {
        if (Leg.bIsStepping)
        {
            Leg.StepProgress += DeltaSeconds / StepDuration;
            Leg.StepProgress = FMath::Clamp(Leg.StepProgress, 0.f, 1.f);

            float T = Leg.StepProgress;

            float LeanBias = FMath::Sin(T * PI) * 0.2f;
            float HorizT = FMath::Clamp(T + LeanBias, 0.f, 1.f);
            FVector Horiz = FMath::Lerp(Leg.StepStartPos, Leg.StepEndPos, HorizT);

            float Arc = FMath::Sin(T * PI) * StepHeight;
            Leg.CurrentFootPos = Horiz + SurfaceNormal * Arc;

            if (Leg.StepProgress >= 1.f)
            {
                Leg.bIsStepping = false;
                Leg.StepProgress = 0.f;
                Leg.CurrentFootPos = Leg.StepEndPos;
                GroupCooldown[Leg.GaitGroup] = StepCooldown;
            }
        }

        DrawDebugSphere(Owner->GetWorld(), Leg.CurrentFootPos,
            5.f, 8,
            Leg.bIsStepping ? FColor::Yellow : FColor::Green,
            false, -1.f);
    }
    FVector NormalSum = FVector::ZeroVector;
    int32 PlantedCount = 0;
    for (const FSpiderLeg& Leg : Legs)
    {
        if (!Leg.bIsStepping)
        {
            NormalSum += Leg.LastSurfaceNormal;
            PlantedCount++;
        }
    }

    if (PlantedCount > 0)
    {
        FVector TargetNormal = (NormalSum / PlantedCount).GetSafeNormal();
        SurfaceNormal = FMath::VInterpTo(
            SurfaceNormal, TargetNormal, DeltaSeconds, 5.f);
    }
    USpiderMovementComponent* SpiderMove = Cast<USpiderMovementComponent>(
        Owner->GetMovementComponent());
    if (SpiderMove)
        SpiderMove->TargetSurfaceNormal = SurfaceNormal;
}

void USpiderAnimInstance::UpdateBody(float DeltaSeconds)
{
    if (!Owner || Legs.Num() < 8) return;

    FVector LocalVel = Owner->GetActorTransform()
        .InverseTransformVector(Owner->GetVelocity());

    float TargetPitch = FMath::Clamp(-LocalVel.X / LeanSpeedRef, -1.f, 1.f) * MaxLeanAngle;
    float TargetRoll = FMath::Clamp(-LocalVel.Y / LeanSpeedRef, -1.f, 1.f) * MaxLeanAngle;

    BodyLeanRotation = FMath::RInterpTo(
        BodyLeanRotation,
        FRotator(TargetPitch, 0.f, TargetRoll),
        DeltaSeconds, LeanInterpSpeed);

    TArray<FVector> StablePos;
    for (const FSpiderLeg& Leg : Legs)
        StablePos.Add(Leg.bIsStepping ? Leg.StepEndPos : Leg.CurrentFootPos);

    FVector AvgFootPos = FVector::ZeroVector;
    for (const FVector& P : StablePos) AvgFootPos += P;
    AvgFootPos /= StablePos.Num();

    FVector ActorToFeet = AvgFootPos - Owner->GetActorLocation();
    float FeetAlongNormal = FVector::DotProduct(ActorToFeet, SurfaceNormal);
    float TargetOffset = FeetAlongNormal - BodyRestHeight;

    BodyHeightOffset = FMath::FInterpTo(
        BodyHeightOffset, TargetOffset, DeltaSeconds, BodyHeightInterpSpeed);

    FVector FrontCenter = (StablePos[0] + StablePos[1]) * 0.5f;
    FVector BackCenter = (StablePos[6] + StablePos[7]) * 0.5f;
    FVector RightCenter = (StablePos[0] + StablePos[2] + StablePos[5] + StablePos[6]) * 0.25f;
    FVector LeftCenter = (StablePos[1] + StablePos[3] + StablePos[4] + StablePos[7]) * 0.25f;

    FVector FwdVec = (BackCenter - FrontCenter).GetSafeNormal();
    FVector RightVec = (RightCenter - LeftCenter).GetSafeNormal();

    FVector FootPlaneNormal = FVector::CrossProduct(RightVec, FwdVec).GetSafeNormal();
    if (FootPlaneNormal.Z < 0.f) FootPlaneNormal = -FootPlaneNormal;

    float TargetBodyPitch = FMath::RadiansToDegrees(
        FMath::Atan2(FootPlaneNormal.X, FootPlaneNormal.Z));
    float TargetBodyRoll = -FMath::RadiansToDegrees(
        FMath::Atan2(FootPlaneNormal.Y, FootPlaneNormal.Z));

    BodyRotationOffset = FMath::RInterpTo(
        BodyRotationOffset,
        FRotator(TargetBodyPitch, 0.f, TargetBodyRoll) + BodyLeanRotation,
        DeltaSeconds, BodyRotInterpSpeed);
}

void USpiderAnimInstance::DoRaycast(FSpiderLeg& Leg)
{
    if (!Owner) return;

    FVector Velocity = Owner->GetVelocity();
    float   Speed = Velocity.Size();
    float   PredScale = FMath::Clamp(Speed / 300.f, 0.f, 1.f);
    FVector PredOffset = Velocity.GetSafeNormal() * Speed * 0.15f * PredScale;

    FVector WorldOffset = Owner->GetActorTransform()
        .TransformPosition(Leg.RestOffset) + PredOffset;

    FVector Start = WorldOffset + SurfaceNormal * 300.f;
    FVector End = WorldOffset - SurfaceNormal * 500.f;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    FHitResult SweepHit;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(25.f);
    bool bSweepHit = Owner->GetWorld()->SweepSingleByChannel(
        SweepHit, Start, End, FQuat::Identity,
        ECC_WorldStatic, Sphere, Params);

    FVector RawDesired;
    if (bSweepHit)
    {
        FVector PreciseStart = SweepHit.ImpactPoint + SurfaceNormal * 50.f;
        FVector PreciseEnd = SweepHit.ImpactPoint - SurfaceNormal * 80.f;

        FHitResult PreciseHit;
        bool bPrecise = Owner->GetWorld()->LineTraceSingleByChannel(
            PreciseHit, PreciseStart, PreciseEnd, ECC_WorldStatic, Params);

        RawDesired = bPrecise
            ? PreciseHit.ImpactPoint + PreciseHit.Normal * Leg.FootGroundOffset
            : SweepHit.ImpactPoint + SweepHit.Normal * Leg.FootGroundOffset;

        Leg.LastSurfaceNormal = bPrecise ? PreciseHit.Normal : SweepHit.Normal;
    }
    else
    {
        RawDesired = WorldOffset;
    }

    FVector HipWorld = Owner->GetActorTransform()
        .TransformPosition(Leg.RestOffset) + SurfaceNormal * 60.f;

    FVector ActorCenter = Owner->GetActorLocation();

    FHitResult LOSHit;
    bool bLOSBlocked = Owner->GetWorld()->LineTraceSingleByChannel(LOSHit, ActorCenter, RawDesired, ECC_WorldStatic, Params);

    if (bLOSBlocked)
        RawDesired = LOSHit.ImpactPoint + LOSHit.Normal * Leg.FootGroundOffset;

    if (Leg.bIsStepping)
        Leg.DesiredFootPos = RawDesired;
    else
        Leg.DesiredFootPos = FMath::VInterpTo(
            Leg.DesiredFootPos, RawDesired, CachedDelta, 20.f);

    if (Leg.CurrentFootPos.IsNearlyZero())
        Leg.CurrentFootPos = Leg.DesiredFootPos;
}