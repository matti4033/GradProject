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
    USpiderMovementComponent* SpiderMove = Cast<USpiderMovementComponent>(
        Owner->GetMovementComponent());
    if (SpiderMove)
        SurfaceNormal = -SpiderMove->GravityDir;

    float UpDot = FVector::DotProduct(
        Owner->GetActorUpVector(), FVector(0, 0, 1.f));
    if (UpDot > 0.95f)
    {
        for (FSpiderLeg& Leg : Legs)
            Leg.LastSurfaceNormal = FVector(0, 0, 1.f);
    }

    GroupCooldown[0] = FMath::Max(0.f, GroupCooldown[0] - DeltaSeconds);
    GroupCooldown[1] = FMath::Max(0.f, GroupCooldown[1] - DeltaSeconds);

    FRotator CurrentRot = Owner->GetActorRotation();
    float YawDelta = FMath::Abs(
        FMath::FindDeltaAngleDegrees(LastBodyRotation.Yaw, CurrentRot.Yaw));
    LastBodyRotation = CurrentRot;

    float TurnRate = (DeltaSeconds > 0.f) ? (YawDelta / DeltaSeconds) : 0.f;
    float TurnAlpha = FMath::Clamp(TurnRate / TurnRateFullScale, 0.f, 1.f);

    float TransitionAlpha = SpiderMove ? SpiderMove->TransitionAlpha : 0.f;
    float TransitionThresholdScale = FMath::Lerp(1.f, 3.f, TransitionAlpha);
    float EffectiveThreshold = FMath::Lerp(
        StepThreshold, StepThreshold * TurnStepThresholdScale, TurnAlpha)
        * TransitionThresholdScale;

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

    if (TransitionAlpha < 0.2f)
    {
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

    if (SpiderMove)
    {
        SurfaceNormal = -SpiderMove->GravityDir;

        FVector ActorUp = Owner->GetActorUpVector();
        FVector NormalSum = FVector::ZeroVector;
        int32 WallFeet = 0;

        for (const FSpiderLeg& Leg : Legs)
        {
            if (!Leg.bIsStepping && !Leg.LastSurfaceNormal.IsNearlyZero())
            {
                float Dot = FVector::DotProduct(Leg.LastSurfaceNormal, ActorUp);
                if (Dot < 0.7f)
                {
                    NormalSum += Leg.LastSurfaceNormal;
                    WallFeet++;
                }
            }
        }

        if (WallFeet > 0)
        {
            FVector AvgWallNormal = (NormalSum / WallFeet).GetSafeNormal();
            float WallFraction = (float)WallFeet / Legs.Num();
            SpiderMove->NotifyFootNormals(AvgWallNormal, WallFraction);
        }
        else
        {
            SpiderMove->NotifyFootNormals(FVector(0, 0, 1.f), 0.f);
        }
    }
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

    FTransform ActorTransform = Owner->GetActorTransform();
    TArray<FVector> LocalPos;
    for (const FVector& P : StablePos)
        LocalPos.Add(ActorTransform.InverseTransformPosition(P));

    FVector FrontCenter = (LocalPos[0] + LocalPos[1]) * 0.5f;
    FVector BackCenter = (LocalPos[6] + LocalPos[7]) * 0.5f;
    FVector RightCenter = (LocalPos[0] + LocalPos[2] + LocalPos[5] + LocalPos[6]) * 0.25f;
    FVector LeftCenter = (LocalPos[1] + LocalPos[3] + LocalPos[4] + LocalPos[7]) * 0.25f;

    FVector FwdVec = (BackCenter - FrontCenter).GetSafeNormal();
    FVector RightVec = (RightCenter - LeftCenter).GetSafeNormal();

    FVector FootPlaneNormal = FVector::CrossProduct(RightVec, FwdVec).GetSafeNormal();
    if (FootPlaneNormal.Z < 0.f) FootPlaneNormal = -FootPlaneNormal;

    float TargetBodyPitch = -FMath::RadiansToDegrees(
        FMath::Atan2(FootPlaneNormal.X, FootPlaneNormal.Z));
    float TargetBodyRoll = -FMath::RadiansToDegrees(
        FMath::Atan2(FootPlaneNormal.Y, FootPlaneNormal.Z));

    TargetBodyPitch = FMath::Clamp(TargetBodyPitch, -15.f, 15.f);
    TargetBodyRoll = FMath::Clamp(TargetBodyRoll, -15.f, 15.f);

    BodyRotationOffset = FMath::RInterpTo(
        BodyRotationOffset,
        FRotator(TargetBodyPitch, 0.f, TargetBodyRoll) + BodyLeanRotation,
        DeltaSeconds, BodyRotInterpSpeed);
}

void USpiderAnimInstance::DoRaycast(FSpiderLeg& Leg)
{
    if (!Owner) return;

    USpiderMovementComponent* SpiderMove = Cast<USpiderMovementComponent>(
        Owner->GetMovementComponent());
    float Alpha = SpiderMove ? SpiderMove->TransitionAlpha : 0.f;

    if (Alpha > 0.15f && Alpha < 0.85f && !Leg.bIsStepping)
        return;

    FVector Velocity = Owner->GetVelocity();
    float   Speed = Velocity.Size();
    FVector PredOffset = Velocity.GetSafeNormal() *
        Speed * 0.15f *
        FMath::Clamp(Speed / 300.f, 0.f, 1.f);

    FVector WorldOffset = Owner->GetActorTransform()
        .TransformPosition(Leg.RestOffset) + PredOffset;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    FVector RawDesired;
    bool    bFoundSurface = false;

    if (Alpha > 0.15f)
    {
        TArray<FVector> CastDirs = {
            -Owner->GetActorUpVector(),
            FVector(0, 0, -1.f),
            SurfaceNormal * -1.f
        };

        float    BestDist = FLT_MAX;
        FHitResult BestHit;

        for (const FVector& Dir : CastDirs)
        {
            FHitResult Hit;
            FVector    S = WorldOffset + (-Dir) * 200.f;
            FVector    E = WorldOffset + Dir * 400.f;

            FCollisionShape Sphere = FCollisionShape::MakeSphere(20.f);
            bool bHit = GetWorld()->SweepSingleByChannel(
                Hit, S, E, FQuat::Identity, ECC_WorldStatic, Sphere, Params);

            if (bHit && Hit.Distance < BestDist)
            {
                BestDist = Hit.Distance;
                BestHit = Hit;
                bFoundSurface = true;
            }
        }

        if (bFoundSurface)
        {
            Leg.LastSurfaceNormal = BestHit.Normal;

            FHitResult PreciseHit;
            bool bPrecise = GetWorld()->LineTraceSingleByChannel(
                PreciseHit,
                BestHit.ImpactPoint + BestHit.Normal * 50.f,
                BestHit.ImpactPoint - BestHit.Normal * 80.f,
                ECC_WorldStatic, Params);

            RawDesired = bPrecise
                ? PreciseHit.ImpactPoint + PreciseHit.Normal * Leg.FootGroundOffset
                : BestHit.ImpactPoint + BestHit.Normal * Leg.FootGroundOffset;
        }
    }
    else
    {
        FVector Start = WorldOffset + SurfaceNormal * 300.f;
        FVector End = WorldOffset - SurfaceNormal * 500.f;

        FHitResult SweepHit;
        FCollisionShape Sphere = FCollisionShape::MakeSphere(25.f);
        bool bSweepHit = GetWorld()->SweepSingleByChannel(
            SweepHit, Start, End, FQuat::Identity, ECC_WorldStatic, Sphere, Params);

        if (bSweepHit)
        {
            FHitResult PreciseHit;
            bool bPrecise = GetWorld()->LineTraceSingleByChannel(
                PreciseHit,
                SweepHit.ImpactPoint + SurfaceNormal * 50.f,
                SweepHit.ImpactPoint - SurfaceNormal * 80.f,
                ECC_WorldStatic, Params);

            RawDesired = bPrecise
                ? PreciseHit.ImpactPoint + PreciseHit.Normal * Leg.FootGroundOffset
                : SweepHit.ImpactPoint + SweepHit.Normal * Leg.FootGroundOffset;

            Leg.LastSurfaceNormal = bPrecise ? PreciseHit.Normal : SweepHit.Normal;
            bFoundSurface = true;
        }
    }

    if (!bFoundSurface)
    {
        if (!Leg.DesiredFootPos.IsNearlyZero())
            return;
        RawDesired = WorldOffset;
    }

    FHitResult LOSHit;
    bool bLOS = GetWorld()->LineTraceSingleByChannel(
        LOSHit, Owner->GetActorLocation(), RawDesired, ECC_WorldStatic, Params);
    if (bLOS)
        RawDesired = LOSHit.ImpactPoint + LOSHit.Normal * Leg.FootGroundOffset;

    if (Leg.bIsStepping)
        Leg.DesiredFootPos = RawDesired;
    else
        Leg.DesiredFootPos = FMath::VInterpTo(
            Leg.DesiredFootPos, RawDesired, CachedDelta, 20.f);

    if (Leg.CurrentFootPos.IsNearlyZero())
        Leg.CurrentFootPos = Leg.DesiredFootPos;
}