#include "SpiderAnimInstance.h"
#include "SpiderFABRIK.h"
#include "SpiderMovementComponent.h"
#include "Engine/OverlapResult.h"
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
    USpiderMovementComponent* SpiderMove =
        Cast<USpiderMovementComponent>(Owner->GetMovementComponent());

    GroupCooldown[0] = FMath::Max(0.f, GroupCooldown[0] - DeltaSeconds);
    GroupCooldown[1] = FMath::Max(0.f, GroupCooldown[1] - DeltaSeconds);

    FRotator CurrentRot = Owner->GetActorRotation();
    float YawDelta = FMath::Abs(
        FMath::FindDeltaAngleDegrees(LastBodyRotation.Yaw, CurrentRot.Yaw));
    LastBodyRotation = CurrentRot;

    float TurnRate = (DeltaSeconds > 0.f) ? (YawDelta / DeltaSeconds) : 0.f;
    float TurnAlpha = FMath::Clamp(TurnRate / TurnRateFullScale, 0.f, 1.f);

    float TransitionAlpha = SpiderMove ? SpiderMove->TransitionAlpha : 0.f;

    float TransitionThresholdScale = FMath::Lerp(1.f, 1.8f, TransitionAlpha);

    float EffectiveThreshold = FMath::Lerp(
        StepThreshold,
        StepThreshold * TurnStepThresholdScale,
        TurnAlpha
    ) * TransitionThresholdScale;

    for (FSpiderLeg& Leg : Legs)
        DoRaycast(Leg);

    if (SpiderMove)
    {
        TArray<FVector> SupportNormals;

        for (const FSpiderLeg& Leg : Legs)
        {
            if (!Leg.bIsStepping && Leg.StepProgress == 0.f)
            {
                if (!Leg.LastSurfaceNormal.IsNearlyZero())
                    SupportNormals.Add(Leg.LastSurfaceNormal);
            }
        }

        if (SupportNormals.Num() > 0)
        {
            FVector AvgNormal = FVector::ZeroVector;
            for (const FVector& N : SupportNormals)
                AvgNormal += N;

            AvgNormal.Normalize();

            float SupportFraction =
                (float)SupportNormals.Num() / (float)Legs.Num();

            SpiderMove->NotifyFootNormals(AvgNormal, SupportFraction);
        }
    }

    bool bOnFloor = (SurfaceNormal.Z > 0.7f);

    if (bOnFloor && TransitionAlpha < 0.2f)
    {
        FVector Up = SurfaceNormal;
        FVector Forward = FVector::VectorPlaneProject(
            Owner->GetActorForwardVector(), Up).GetSafeNormal();

        FVector FRPos, FLPos, MRPos, MLPos;
        FRPos = FLPos = MRPos = MLPos = FVector::ZeroVector;

        for (const FSpiderLeg& Leg : Legs)
        {
            if (Leg.UpperBone == FName("LegFR_Upper")) FRPos = Leg.CurrentFootPos;
            if (Leg.UpperBone == FName("LegFL_Upper")) FLPos = Leg.CurrentFootPos;
            if (Leg.UpperBone == FName("LegMR_Upper")) MRPos = Leg.CurrentFootPos;
            if (Leg.UpperBone == FName("LegML_Upper")) MLPos = Leg.CurrentFootPos;
        }
        //keep legs in their "place"
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
            bool bIsRear = Leg.UpperBone == FName("LegRR_Upper") ||
                Leg.UpperBone == FName("LegRL_Upper");
            float LegThreshold = bIsRear ? EffectiveThreshold * 0.55f : EffectiveThreshold;

            float Dist = FVector::Dist(Leg.CurrentFootPos, Leg.DesiredFootPos);

            float SpiderSpeed = Owner->GetVelocity().Size();
            float StationaryScale = FMath::Lerp(2.5f, 1.f,
                FMath::Clamp(SpiderSpeed / 150.f, 0.f, 1.f));

            if (Dist > LegThreshold * StationaryScale)
                bGroupNeedsStep[Leg.GaitGroup] = true;
        }
    }

    for (int32 Group = 0; Group < 2; Group++)
    {
        int32 OtherGroup = 1 - Group;

        //nytt
        bool bUrgent = false;
        for (const FSpiderLeg& Leg : Legs)
        {
            if (Leg.GaitGroup == Group && !Leg.bIsStepping)
            {
                float Dist = FVector::Dist(Leg.CurrentFootPos, Leg.DesiredFootPos);
                if (Dist > EffectiveThreshold * 2.2f)
                    bUrgent = true;
            }
        }

        if (bGroupNeedsStep[Group]
            && !bGroupStepping[Group]
            && (bUrgent || !bGroupStepping[OtherGroup])
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

            //new
            float Arc = FMath::Sin(T * PI) * FMath::Pow(1.f - T, 0.3f) * StepHeight * 1.4f;
            //float Arc = FMath::Sin(T * PI) * StepHeight;
            Leg.CurrentFootPos = Horiz + SurfaceNormal * Arc;

            if (Leg.StepProgress >= 1.f)
            {
                Leg.bIsStepping = false;
                Leg.StepProgress = 0.f;
                Leg.CurrentFootPos = Leg.StepEndPos;
                GroupCooldown[Leg.GaitGroup] = StepCooldown;
            }
        }

        //DrawDebugSphere(
        //    Owner->GetWorld(),
        //    Leg.CurrentFootPos,
        //    5.f, 8,
        //    Leg.bIsStepping ? FColor::Yellow : FColor::Green,
        //    false, -1.f);
    }

    if (SpiderMove)
        SurfaceNormal = SpiderMove->TargetSurfaceNormal;
}


void USpiderAnimInstance::UpdateBody(float DeltaSeconds)
{
    //not fully implemented
    if (!Owner || Legs.Num() < 8) return;

    USpiderMovementComponent* SpiderMove =
        Cast<USpiderMovementComponent>(Owner->GetMovementComponent());

    FVector LocalVel = Owner->GetActorTransform()
        .InverseTransformVector(Owner->GetVelocity());

    float TargetPitch = FMath::Clamp(-LocalVel.X / LeanSpeedRef, -1.f, 1.f) * MaxLeanAngle;
    float TargetRoll = FMath::Clamp(-LocalVel.Y / LeanSpeedRef, -1.f, 1.f) * MaxLeanAngle;

    BodyLeanRotation = FMath::RInterpTo(
        BodyLeanRotation,
        FRotator(TargetPitch, 0.f, TargetRoll),
        DeltaSeconds, LeanInterpSpeed);

    //new
    int32 SteppingGroup = -1;
    for (const FSpiderLeg& Leg : Legs)
        if (Leg.bIsStepping) { SteppingGroup = Leg.GaitGroup; break; }

    float TargetSway = 0.f;
    if (SteppingGroup == 0) TargetSway = 3.5f;
    if (SteppingGroup == 1) TargetSway = -3.5f;

    CurrentSway = FMath::FInterpTo(CurrentSway, TargetSway, DeltaSeconds, 4.f);

    BodyRotationOffset.Roll += CurrentSway;

    //new
         
    TArray<FVector> HeightPos;
    for (const FSpiderLeg& Leg : Legs)
    {
        if (!Leg.bIsStepping)
            HeightPos.Add(Leg.DesiredFootPos.IsNearlyZero()
                ? Leg.CurrentFootPos : Leg.DesiredFootPos);
        else
            HeightPos.Add(Leg.StepEndPos);
    }

    FVector AvgFootPos = FVector::ZeroVector;
    for (const FVector& P : HeightPos) AvgFootPos += P;
    AvgFootPos /= HeightPos.Num();

    FVector UpForHeight = SurfaceNormal;
    if (SpiderMove)
    {
        float DotUp = FVector::DotProduct(SurfaceNormal, FVector::UpVector);
        if (DotUp > 0.7f) // mostly floor
            UpForHeight = FVector::UpVector;
    }
    //static FVector PrevSurfaceNormal = FVector::UpVector;
    float SurfDot = FVector::DotProduct(PrevSurfaceNormal, SurfaceNormal);
    if (SurfDot < 0.5f)
    {
        BodyRotationOffset = FRotator::ZeroRotator;
        BodyLeanRotation = FRotator::ZeroRotator;
        //BodyHeightOffset = 0.f;
    }
    PrevSurfaceNormal = SurfaceNormal;

    FVector ActorToFeet = AvgFootPos - Owner->GetActorLocation();
    float FeetAlongNormal = FVector::DotProduct(ActorToFeet, UpForHeight);
    float TargetOffset = FeetAlongNormal - BodyRestHeight;

    TargetOffset = FMath::Clamp(TargetOffset, -150.f, 60.f);

    //float SurfDot = FVector::DotProduct(PrevSurfaceNormal, SurfaceNormal);
    //if (SurfDot < 0.5f)
    //{
    //}

    float HeightInterpSpeed = (TargetOffset < BodyHeightOffset)
        ? BodyHeightInterpSpeed * 5.f
        : BodyHeightInterpSpeed;

    BodyHeightOffset = FMath::FInterpTo(
        BodyHeightOffset, TargetOffset, DeltaSeconds, HeightInterpSpeed);
    //BodyHeightOffset = FMath::FInterpTo(
    //    BodyHeightOffset, TargetOffset, DeltaSeconds, BodyHeightInterpSpeed);

    FTransform ActorTransform = Owner->GetActorTransform();
    TArray<FVector> LocalPos;
    for (const FVector& P : HeightPos)
        LocalPos.Add(ActorTransform.InverseTransformPosition(P));

    FVector FrontCenter = (LocalPos[0] + LocalPos[1]) * 0.5f;
    FVector BackCenter = (LocalPos[6] + LocalPos[7]) * 0.5f;
    FVector RightCenter = (LocalPos[0] + LocalPos[2] + LocalPos[5] + LocalPos[6]) * 0.25f;
    FVector LeftCenter = (LocalPos[1] + LocalPos[3] + LocalPos[4] + LocalPos[7]) * 0.25f;

    FVector FwdVec = (BackCenter - FrontCenter).GetSafeNormal();
    FVector RightVec = (RightCenter - LeftCenter).GetSafeNormal();

    FVector FootPlaneNormal = FVector::CrossProduct(RightVec, FwdVec).GetSafeNormal();
    if (FVector::DotProduct(FootPlaneNormal, SurfaceNormal) < 0.f)
        FootPlaneNormal = -FootPlaneNormal;

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

    USpiderMovementComponent* SpiderMove =
        Cast<USpiderMovementComponent>(Owner->GetMovementComponent());

    float Alpha = SpiderMove ? SpiderMove->TransitionAlpha : 0.f;

    FVector Up = SurfaceNormal.GetSafeNormal();
    if (Up.IsNearlyZero())
        Up = FVector::UpVector;

    FVector Fwd = FVector::VectorPlaneProject(
        Owner->GetActorForwardVector(), Up).GetSafeNormal();
    if (Fwd.IsNearlyZero())
        Fwd = FVector::ForwardVector;

    FVector Right = FVector::CrossProduct(Up, Fwd).GetSafeNormal();

    FVector Velocity = Owner->GetVelocity();
    FVector TangentVel = FVector::VectorPlaneProject(Velocity, Up);
    float Speed = TangentVel.Size();

    FVector PredOffset = FVector::ZeroVector;

    FVector WorldRest = Owner->GetActorTransform()
        .TransformPosition(Leg.RestOffset);

    FVector WorldOffset = WorldRest + PredOffset;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    FVector RawDesired = WorldOffset;
    bool bFoundSurface = false;

    TArray<FVector> CastDirs;

    if (Alpha > 0.15f)
    {
        CastDirs = {
            -Up,   
            -Fwd,    
            Fwd,      
            -Right,     
            Right      
        };

        float BestDist = FLT_MAX;
        FHitResult BestHit;

        for (const FVector& Dir : CastDirs)
        {
            FHitResult Hit;
            FVector S = WorldOffset + (-Dir) * 200.f;
            FVector E = WorldOffset + Dir * 400.f;

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
            Leg.LastSurfaceNormal = BestHit.Normal.GetSafeNormal();
            if (!SurfaceNormal.IsNearlyZero())
            {
                if (FVector::DotProduct(Leg.LastSurfaceNormal, SurfaceNormal) < 0.f)
                    Leg.LastSurfaceNormal = -Leg.LastSurfaceNormal;
            }

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
        bool bLedge = SpiderMove && SpiderMove->WallDetected;
        float SweepRadius = bLedge ? 80.f : 25.f;

        FHitResult SweepHit;
        bool bSweepHit = GetWorld()->SweepSingleByChannel(
            SweepHit,
            WorldOffset + Up * 300.f,
            WorldOffset - Up * 500.f,
            FQuat::Identity, ECC_WorldStatic,
            FCollisionShape::MakeSphere(SweepRadius), Params);

        if (bSweepHit)
        {
            FHitResult PreciseHit;
            bool bPrecise = GetWorld()->LineTraceSingleByChannel(
                PreciseHit,
                SweepHit.ImpactPoint + SweepHit.Normal * 50.f,
                SweepHit.ImpactPoint - SweepHit.Normal * 80.f,
                ECC_WorldStatic, Params);

            RawDesired = bPrecise
                ? PreciseHit.ImpactPoint + PreciseHit.Normal * Leg.FootGroundOffset
                : SweepHit.ImpactPoint + SweepHit.Normal * Leg.FootGroundOffset;

            Leg.LastSurfaceNormal = (bPrecise
                ? PreciseHit.Normal : SweepHit.Normal).GetSafeNormal();

            if (!SurfaceNormal.IsNearlyZero() &&
                FVector::DotProduct(Leg.LastSurfaceNormal, SurfaceNormal) < 0.f)
                Leg.LastSurfaceNormal = -Leg.LastSurfaceNormal;

            bFoundSurface = true;
        }
    }
    if (!bFoundSurface)
    {
        if (!Leg.CurrentFootPos.IsNearlyZero())
        {
            FHitResult EdgeHit;
            FVector EdgeStart = Leg.CurrentFootPos + Up * 50.f;
            FVector EdgeEnd = Leg.CurrentFootPos - Up * 200.f;

            bool bEdgeHit = GetWorld()->LineTraceSingleByChannel(
                EdgeHit, EdgeStart, EdgeEnd, ECC_WorldStatic, Params);

            if (bEdgeHit)
            {
                float FlatScore = FVector::DotProduct(EdgeHit.Normal, Up);
                if (FlatScore > 0.3f)
                {
                    RawDesired = EdgeHit.ImpactPoint + EdgeHit.Normal * Leg.FootGroundOffset;
                    Leg.LastSurfaceNormal = EdgeHit.Normal;
                    bFoundSurface = true;
                }
            }
        }

        if (!bFoundSurface)
        {
            if (!Leg.DesiredFootPos.IsNearlyZero())
            {
                Leg.DesiredFootPos = FMath::VInterpTo(
                    Leg.DesiredFootPos, WorldOffset, CachedDelta, 3.f);
                return;
            }
            RawDesired = WorldOffset;
        }
    }

    bool bSkipLOS = false;
    if (SpiderMove && SpiderMove->bLedgeTransition)
    {
        FVector LocalRestCheck = Owner->GetActorTransform()
            .InverseTransformPosition(WorldRest);
        if (LocalRestCheck.X > 0.f)
            bSkipLOS = true;
    }

    if (!bSkipLOS)
    {
        FHitResult LOSHit;
        bool bLOS = GetWorld()->LineTraceSingleByChannel(
            LOSHit, Owner->GetActorLocation(), RawDesired, ECC_WorldStatic, Params);
        if (bLOS)
        {
            RawDesired = LOSHit.ImpactPoint + LOSHit.Normal * Leg.FootGroundOffset;
            Leg.LastSurfaceNormal = LOSHit.Normal;
        }
    }

    //new
    if (Leg.bIsStepping)
    {
        Leg.DesiredFootPos = RawDesired;
    }
    else
    {
        FVector Vel = Owner->GetVelocity();

        FVector LocalRest = Owner->GetActorTransform().InverseTransformPosition(WorldRest);
        float FwdFraction = FMath::Clamp(-LocalRest.X / 100.f, 0.f, 1.f);
        float ReachScale = FMath::Lerp(0.06f, 0.18f, FwdFraction);
        FVector VelOffset = TangentVel * ReachScale;
        FVector ReachTarget = RawDesired + VelOffset;

        float SmoothSpeed = FMath::Lerp(3.f, 10.f,
            FMath::Clamp(Speed / 200.f, 0.f, 1.f));

        Leg.DesiredFootPos = FMath::VInterpTo(
            Leg.DesiredFootPos, ReachTarget, CachedDelta, SmoothSpeed);
    }
    if (Leg.CurrentFootPos.IsNearlyZero())
        Leg.CurrentFootPos = Leg.DesiredFootPos;
}
