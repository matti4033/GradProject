#include "SpiderMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "SpiderCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

USpiderMovementComponent::USpiderMovementComponent()
{
    GravityScale = 0.f;
    SetWalkableFloorAngle(180.f);
    TargetSurfaceNormal = FVector::UpVector;
    MaxSpiderSpeed = 900.f;
}

void USpiderMovementComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    if (MovementMode != MOVE_Custom)
    {
        SetMovementMode(MOVE_Custom, 0);
    }

    ACharacter* Owner = CharacterOwner;
    if (Owner && Owner->Controller)
    {
        FVector Up = TargetSurfaceNormal.GetSafeNormal();
        if (Up.IsNearlyZero())
            Up = FVector::UpVector;

        FRotator ControlRot = Owner->Controller->GetControlRotation();
        FVector DesiredForward = ControlRot.Vector();

        FVector Forward = FVector::VectorPlaneProject(DesiredForward, Up).GetSafeNormal();
        if (Forward.IsNearlyZero())
            Forward = FVector::CrossProduct(Up, FVector::RightVector).GetSafeNormal();

        FVector Right = FVector::CrossProduct(Up, Forward).GetSafeNormal();

        const FMatrix Basis(
            Forward,
            Right,
            Up,
            FVector::ZeroVector);

        FRotator TargetRot = Basis.Rotator();

        Owner->SetActorRotation(TargetRot);
    }

    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void USpiderMovementComponent::NotifyFootNormals(
    const FVector& AvgNormal,
    float SupportFraction)
{
    if (SupportFraction < 0.4f)
        return;

    FVector Desired = AvgNormal.GetSafeNormal();
    FVector Old = TargetSurfaceNormal.GetSafeNormal();

    if (!Old.IsNearlyZero())
    {
        float HemDot = FVector::DotProduct(Old, Desired);
        if (HemDot < 0.f)
            Desired = -Desired;
    }

    float DeltaTime = GetWorld()->GetDeltaSeconds();
    float MaxAnglePerSec = 180.f;
    float MaxAngleThisFrame = MaxAnglePerSec * DeltaTime;

    float Dot = FMath::Clamp(FVector::DotProduct(Old, Desired), -1.f, 1.f);
    float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));

    FVector Final = Desired;

    if (Angle > MaxAngleThisFrame && Angle > KINDA_SMALL_NUMBER)
    {
        float T = MaxAngleThisFrame / Angle;
        Final = FMath::Lerp(Old, Desired, T).GetSafeNormal();
    }

    TargetSurfaceNormal = Final;

     if (GEngine)
     {
         GEngine->AddOnScreenDebugMessage(
             1234, 0.f, FColor::Green,
             FString::Printf(TEXT("FootNormals: %s  Support=%.2f"),
                 *AvgNormal.ToString(), SupportFraction));
     }
}

void USpiderMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
    if (CustomMovementMode == 0)
    {
        PhysCustom_Custom(DeltaTime, Iterations);
        return;
    }

    Super::PhysCustom(DeltaTime, Iterations);
}

void USpiderMovementComponent::PhysCustom_Custom(float DeltaTime, int32 Iterations)
{
    ASpiderCharacter* Spider = Cast<ASpiderCharacter>(CharacterOwner);
    if (!Spider || DeltaTime <= 0.f) return;

    FFindFloorResult Floor;
    SpiderFindFloor(Spider->GetActorLocation(), Floor);

    bool bOnGround = false;
    FVector FloorNormal = TargetSurfaceNormal;

    if (Floor.bBlockingHit)
    {
        FloorNormal = Floor.HitResult.Normal;
        float DotUp = FVector::DotProduct(FloorNormal, FVector::UpVector);
        bOnGround = (DotUp > 0.7f);
    }

    FVector SurfUp = TargetSurfaceNormal.GetSafeNormal();
    float SurfDotWorldUp = FVector::DotProduct(SurfUp, FVector::UpVector);
    bool bClearlyOnWall = (FMath::Abs(SurfDotWorldUp) < 0.5f);

    if (bClearlyOnWall)
    {
        bOnGround = false;
    }

    FVector Up = bOnGround ? FloorNormal.GetSafeNormal()
        : SurfUp;

    FRotator ControlRot = Spider->Controller->GetControlRotation();
    FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

    /*FVector DesiredForward = YawRot.Vector();*/
    FVector DesiredForward =
        (bOnGround ? YawRot.Vector() : Spider->GetActorForwardVector());

    FVector SurfaceForward = FVector::VectorPlaneProject(DesiredForward, Up);

    if (SurfaceForward.SizeSquared() < 0.01f)
    {
        SurfaceForward = FVector::CrossProduct(Up, FVector::RightVector);
    }

    SurfaceForward.Normalize();

    FVector SurfaceRight = FVector::CrossProduct(Up, SurfaceForward).GetSafeNormal();

    FVector2D Input = Spider->MovementInput;

    FVector MoveDir =
        SurfaceForward * Input.X +
        SurfaceRight * Input.Y;

    if (MoveDir.SizeSquared() < 0.0001f)
    {
        MoveDir = FVector::ZeroVector;
    }
    else
    {
        MoveDir.Normalize();
    }

    Velocity = FMath::VInterpTo(Velocity, MoveDir * MaxSpiderSpeed, DeltaTime, 6.f);

    FVector Delta = Velocity * DeltaTime;
    FVector Remaining = Delta;

    for (int32 i = 0; i < 4 && !Remaining.IsNearlyZero(); i++)
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(Remaining, Spider->GetActorQuat(), true, Hit);

        if (!Hit.IsValidBlockingHit())
            break;

        if (bOnGround && SpiderTryStepUp(Hit, Remaining))
            break;

        Remaining = ComputeSlideVector(Remaining, 1.f - Hit.Time, Hit.Normal, Hit);
    }

     if (GEngine)
     {
         GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Red,
             FString::Printf(TEXT("MoveDir: %s"), *MoveDir.ToString()));
         GEngine->AddOnScreenDebugMessage(2, 0.f, FColor::Yellow,
             FString::Printf(TEXT("Velocity: %s"), *Velocity.ToString()));
     }
 }

bool USpiderMovementComponent::SpiderFindFloor(const FVector& Location, FFindFloorResult& OutFloor)
{
    FindFloor(Location, OutFloor, false);
    return OutFloor.IsWalkableFloor();
}

bool USpiderMovementComponent::SpiderTryStepUp(const FHitResult& Hit, const FVector& Delta)
{
    if (!CanStepUp(Hit))
        return false;

    FVector GravDir = FVector(0.f, 0.f, -1.f);
    FVector StepUp = -GravDir * MaxStepHeight;

    FHitResult StepHit;
    SafeMoveUpdatedComponent(StepUp, UpdatedComponent->GetComponentQuat(), true, StepHit);

    if (StepHit.bBlockingHit)
        return false;

    SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, StepHit);
    return true;
}