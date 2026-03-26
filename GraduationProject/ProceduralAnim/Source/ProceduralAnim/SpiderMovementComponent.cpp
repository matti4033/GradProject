#include "SpiderMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

void USpiderMovementComponent::TickComponent(float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    DetectWall(DeltaTime);
    AlignToSurface(DeltaTime);
}

void USpiderMovementComponent::DetectWall(float DeltaTime)
{
    ACharacter* Owner = Cast<ACharacter>(GetOwner());
    if (!Owner) return;

    FVector Forward = Owner->GetActorForwardVector();
    FVector Start = Owner->GetActorLocation();

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);
    FCollisionShape Sphere = FCollisionShape::MakeSphere(WallDetectRadius);

    bool bHitFar = GetWorld()->SweepSingleByChannel(
        Hit, Start, Start + Forward * WallDetectDistance,
        FQuat::Identity, ECC_WorldStatic, Sphere, Params);

    FHitResult HitClose;
    bool bHitClose = GetWorld()->SweepSingleByChannel(
        HitClose, Start, Start + Forward * WallDetectDistance * 0.4f,
        FQuat::Identity, ECC_WorldStatic, Sphere, Params);

    FHitResult& BestHit = bHitClose ? HitClose : Hit;
    bool        bAnyHit = bHitClose || bHitFar;

    if (bAnyHit)
    {
        float Dot = FVector::DotProduct(BestHit.Normal, Owner->GetActorUpVector());
        if (Dot < 0.85f)
        {
            WallDetected = true;
            LastWallNormal = BestHit.Normal;

            float BlendSpeed = bHitClose ? 3.f : 0.5f;
            TargetSurfaceNormal = FMath::VInterpTo(
                TargetSurfaceNormal, BestHit.Normal, DeltaTime, BlendSpeed);
        }
    }
    else
    {
        WallDetected = false;
        if (WallCommitAlpha < 0.1f)
        {
            TargetSurfaceNormal = FMath::VInterpTo(
                TargetSurfaceNormal, FVector(0, 0, 1.f), DeltaTime, 2.f);
        }
    }
}

void USpiderMovementComponent::NotifyFootNormals(
    const FVector& AverageFootNormal, float WallFootFraction)
{
    WallCommitAlpha = FMath::FInterpTo(
        WallCommitAlpha, WallFootFraction,
        GetWorld()->GetDeltaSeconds(), 2.f);

    if (WallFootFraction > 0.1f)
    {
        float BlendSpeed = 1.f + WallCommitAlpha * 3.f;
        TargetSurfaceNormal = FMath::VInterpTo(
            TargetSurfaceNormal, AverageFootNormal,
            GetWorld()->GetDeltaSeconds(), BlendSpeed);
    }
    else if (!WallDetected)
    {
        WallCommitAlpha = FMath::FInterpTo(
            WallCommitAlpha, 0.f, GetWorld()->GetDeltaSeconds(), 1.f);
        TargetSurfaceNormal = FMath::VInterpTo(
            TargetSurfaceNormal, FVector(0, 0, 1.f),
            GetWorld()->GetDeltaSeconds(), 1.f);
    }
}

void USpiderMovementComponent::AlignToSurface(float DeltaTime)
{
    ACharacter* Owner = Cast<ACharacter>(GetOwner());
    if (!Owner) return;

    GravityDir = (-TargetSurfaceNormal).GetSafeNormal();

    FVector CurrentUp = Owner->GetActorUpVector();
    FVector TargetUp = TargetSurfaceNormal.GetSafeNormal();

    float AngleBetween = FMath::RadiansToDegrees(
        FMath::Acos(FMath::Clamp(
            FVector::DotProduct(CurrentUp, TargetUp), -1.f, 1.f)));

    if (AngleBetween > 0.1f)
    {
        FVector RightAxis = Owner->GetActorRightVector();

        FVector CurrProj = (CurrentUp - RightAxis *
            FVector::DotProduct(CurrentUp, RightAxis)).GetSafeNormal();
        FVector TargProj = (TargetUp - RightAxis *
            FVector::DotProduct(TargetUp, RightAxis)).GetSafeNormal();

        float CosA = FMath::Clamp(
            FVector::DotProduct(CurrProj, TargProj), -1.f, 1.f);
        float Angle = FMath::Acos(CosA);

        FVector Cross = FVector::CrossProduct(CurrProj, TargProj);
        if (FVector::DotProduct(Cross, RightAxis) < 0.f)
            Angle = -Angle;

        float MaxRad = FMath::DegreesToRadians(20.f * DeltaTime);
        Angle = FMath::Clamp(Angle, -MaxRad, MaxRad);

        FQuat AlignDelta = FQuat(RightAxis, Angle);
        FQuat NewRot = AlignDelta * Owner->GetActorQuat();
        MoveUpdatedComponent(FVector::ZeroVector, NewRot, true);
    }

    float UpDot = FVector::DotProduct(Owner->GetActorUpVector(),
        FVector(0, 0, 1.f));
    TransitionAlpha = 1.f - FMath::Abs(UpDot);
}

void USpiderMovementComponent::FindFloor(
    const FVector& CapsuleLocation,
    FFindFloorResult& OutFloorResult,
    bool bCanUseCachedLocation,
    const FHitResult* DownwardSweepResult) const
{
    ACharacter* Owner = Cast<ACharacter>(GetOwner());
    if (!Owner)
    {
        Super::FindFloor(CapsuleLocation, OutFloorResult,
            bCanUseCachedLocation, DownwardSweepResult);
        return;
    }

    FVector ActorDown = -Owner->GetActorUpVector();

    float CapsuleHalfHeight = Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    float CapsuleRadius = Owner->GetCapsuleComponent()->GetScaledCapsuleRadius();

    FVector Start = CapsuleLocation;
    FVector End = CapsuleLocation + ActorDown * (CapsuleHalfHeight + 20.f);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);
    FCollisionShape Capsule = FCollisionShape::MakeSphere(CapsuleRadius * 0.8f);

    bool bHit = GetWorld()->SweepSingleByChannel(
        Hit, Start, End, FQuat::Identity, ECC_WorldStatic, Capsule, Params);

    if (bHit)
    {
        OutFloorResult.bWalkableFloor = true;
        OutFloorResult.bBlockingHit = true;
        OutFloorResult.HitResult = Hit;
        OutFloorResult.FloorDist = Hit.Distance;
        OutFloorResult.LineDist = Hit.Distance;
    }
    else
    {
        Super::FindFloor(CapsuleLocation, OutFloorResult,
            bCanUseCachedLocation, DownwardSweepResult);
    }
}