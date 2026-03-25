#include "SpiderMovementComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

float USpiderMovementComponent::GetGravityZ() const
{
    float DefaultGravZ = Super::GetGravityZ();
    return DefaultGravZ;
}

void USpiderMovementComponent::TickComponent(float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    DetectWall(DeltaTime);
    AlignToSurface(DeltaTime);
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpiderMovementComponent::DetectWall(float DeltaTime)
{
    ACharacter* Owner = Cast<ACharacter>(GetOwner());
    if (!Owner) return;

    FVector Forward = Owner->GetActorForwardVector();
    FVector Start = Owner->GetActorLocation();
    FVector End = Start + Forward * WallDetectDistance;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    FCollisionShape Sphere = FCollisionShape::MakeSphere(WallDetectRadius);
    bool bHit = GetWorld()->SweepSingleByChannel(
        Hit, Start, End, FQuat::Identity,
        ECC_WorldStatic, Sphere, Params);

    if (bHit)
    {
        float Dot = FVector::DotProduct(Hit.Normal, -GravityDir);
        if (Dot < 0.7f)
        {
            TargetSurfaceNormal = FMath::VInterpTo(
                TargetSurfaceNormal, Hit.Normal, DeltaTime, 2.f);
        }
    }
    else
    {
    }
}

void USpiderMovementComponent::AlignToSurface(float DeltaTime)
{
    ACharacter* Owner = Cast<ACharacter>(GetOwner());
    if (!Owner) return;

    FVector TargetGravityDir = -TargetSurfaceNormal;
    GravityDir = FMath::VInterpTo(
        GravityDir, TargetGravityDir, DeltaTime, SurfaceAlignSpeed);
    GravityDir = GravityDir.GetSafeNormal();

    FVector CurrentUp = Owner->GetActorUpVector();
    FVector TargetUp = -GravityDir;

    if (!FVector::Coincident(CurrentUp, TargetUp))
    {
        FQuat AlignDelta = FQuat::FindBetweenNormals(CurrentUp, TargetUp);
        FQuat CurrentRot = Owner->GetActorQuat();
        FQuat TargetRot = FQuat::Slerp(
            CurrentRot, AlignDelta * CurrentRot,
            FMath::Clamp(DeltaTime * SurfaceAlignSpeed, 0.f, 1.f));

        Owner->SetActorRotation(TargetRot);
    }
}

void USpiderMovementComponent::PhysicsRotation(float DeltaTime)
{
    if (!HasValidData()) return;

    FRotator CurrentRot = UpdatedComponent->GetComponentRotation();

    if (!Velocity.IsNearlyZero())
    {
        FVector LocalVel = CharacterOwner->GetActorTransform()
            .InverseTransformVector(Velocity);

        if (!FMath::IsNearlyZero(LocalVel.X))
        {
            float TargetYawDelta = FMath::RadiansToDegrees(
                FMath::Atan2(LocalVel.Y, LocalVel.X));

            FRotator NewRot = CurrentRot;
            NewRot.Yaw += TargetYawDelta * DeltaTime * RotationRate.Yaw * 0.01f;
            MoveUpdatedComponent(FVector::ZeroVector, NewRot, true);
        }
    }
}