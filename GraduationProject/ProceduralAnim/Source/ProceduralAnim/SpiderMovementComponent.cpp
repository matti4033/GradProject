#include "SpiderMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "SpiderCharacter.h"
#include "GameFramework/SpringArmComponent.h"

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
        //surfacenormal is new up!
        FVector Up = TargetSurfaceNormal.GetSafeNormal();
        if (Up.IsNearlyZero())
            Up = FVector::UpVector;

        FRotator ControlRot = Owner->Controller->GetControlRotation();

        float SurfDotUp = FVector::DotProduct(Up, FVector::UpVector);
        if (SurfDotUp > 0.7f)
        {
            FVector WorldFwd = FRotator(0, Owner->Controller->GetControlRotation().Yaw, 0).Vector();
            FVector Projected = FVector::VectorPlaneProject(WorldFwd, Up).GetSafeNormal();
            if (!Projected.IsNearlyZero())
                CurrentSurfaceForward = Projected;
        }

        float CurrentYaw = ControlRot.Yaw;
        float YawDelta = FMath::FindDeltaAngleDegrees(LastControllerYaw, CurrentYaw);
        LastControllerYaw = CurrentYaw;

        FQuat YawQ(Up, FMath::DegreesToRadians(YawDelta));
        CurrentSurfaceForward = YawQ.RotateVector(CurrentSurfaceForward);
        CurrentSurfaceForward = FVector::VectorPlaneProject(
            CurrentSurfaceForward, Up).GetSafeNormal();

        if (CurrentSurfaceForward.IsNearlyZero())
            CurrentSurfaceForward = FVector::CrossProduct(Up, FVector::RightVector).GetSafeNormal();

        FVector Right = FVector::CrossProduct(Up, CurrentSurfaceForward).GetSafeNormal();

        const FMatrix Basis(
            CurrentSurfaceForward,
            Right,
            Up,
            FVector::ZeroVector);

        Owner->SetActorRotation(Basis.Rotator());
    }

    if (Owner)
    {
        FVector ActorFwd = Owner->GetActorForwardVector();
        FVector ActorUp = Owner->GetActorUpVector();
        FVector ActorLoc = Owner->GetActorLocation();

        FCollisionQueryParams LedgeParams;
        LedgeParams.AddIgnoredActor(Owner);
        FCollisionShape LedgeSphere = FCollisionShape::MakeSphere(WallDetectRadius);

        //attempt at making ledge-walking work, not fully functional
        FVector LedgeStart = ActorLoc
            + ActorFwd * 60.f
            - ActorUp * 40.f;

        FVector LedgeEnd = LedgeStart
            + ActorFwd * 80.f
            - ActorUp * WallDetectDistance;

        FHitResult LedgeHit;
        bool bLedgeFound = GetWorld()->SweepSingleByChannel(
            LedgeHit, LedgeStart, LedgeEnd,
            FQuat::Identity, ECC_WorldStatic, LedgeSphere, LedgeParams);

        if (bLedgeFound)
        {
            float Dot = FVector::DotProduct(LedgeHit.Normal, ActorUp);
            if (Dot < 0.5f)
            {
                WallDetected = true;
                LastWallNormal = LedgeHit.Normal;
                bLedgeTransition = true;
            }
            else
            {
                WallDetected = false;
                bLedgeTransition = false;
            }
        }
        else
        {
            WallDetected = false;
            bLedgeTransition = false;

            float ActorUpDot = FVector::DotProduct(ActorUp, FVector::UpVector);
            if (ActorUpDot > 0.85f)
            {
                TargetSurfaceNormal = FMath::VInterpTo(
                    TargetSurfaceNormal, FVector::UpVector, DeltaTime, 3.f);
            }
        }

        float UpDot = FVector::DotProduct(ActorUp, FVector::UpVector);
        TransitionAlpha = 1.f - FMath::Abs(UpDot);
    }
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void USpiderMovementComponent::NotifyFootNormals(
    const FVector& AvgNormal,
    float SupportFraction)
{
    float MinFraction = bLedgeTransition ? 0.1f : 0.4f;
    if (SupportFraction < MinFraction)
        return;

    FVector Desired = AvgNormal.GetSafeNormal();
    FVector Old = TargetSurfaceNormal.GetSafeNormal();

    if (!Old.IsNearlyZero())
    {
        float HemDot = FVector::DotProduct(Old, Desired);
        if (HemDot < 0.f)
            Desired = -Desired;
    }

    if (bLedgeTransition)
    {
        TargetSurfaceNormal = Desired;
        return;
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
    //float MinFraction = bLedgeTransition ? 0.1f : 0.4f;
    //if (SupportFraction < MinFraction)
    //    return;

    //FVector Desired = AvgNormal.GetSafeNormal();
    //FVector Old = TargetSurfaceNormal.GetSafeNormal();

    //if (!Old.IsNearlyZero())
    //{
    //    float HemDot = FVector::DotProduct(Old, Desired);
    //    if (HemDot < 0.f)
    //        Desired = -Desired;
    //}

    //float DeltaTime = GetWorld()->GetDeltaSeconds();
    //float MaxAnglePerSec = 180.f;
    //float MaxAngleThisFrame = MaxAnglePerSec * DeltaTime;

    //float Dot = FMath::Clamp(FVector::DotProduct(Old, Desired), -1.f, 1.f);
    //float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));

    //FVector Final = Desired;

    //if (Angle > MaxAngleThisFrame && Angle > KINDA_SMALL_NUMBER)
    //{
    //    float T = MaxAngleThisFrame / Angle;
    //    Final = FMath::Lerp(Old, Desired, T).GetSafeNormal();
    //}

    //TargetSurfaceNormal = Final;
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

    //override ground if surfacenormal is wall
    FVector SurfUp = TargetSurfaceNormal.GetSafeNormal();
    float SurfDotWorldUp = FVector::DotProduct(SurfUp, FVector::UpVector);
    bool bClearlyOnWall = (FMath::Abs(SurfDotWorldUp) < 0.5f);

    if (bClearlyOnWall)
    {
        bOnGround = false;
    }
    //choose what is "up"
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

    //new
    FVector SurfaceDown = -TargetSurfaceNormal.GetSafeNormal();

    FHitResult GroundHit;
    FVector GroundStart = Spider->GetActorLocation();
    FVector GroundEnd = GroundStart + SurfaceDown * 300.f;

    FCollisionQueryParams GroundParams;
    GroundParams.AddIgnoredActor(Spider);

    bool bGroundFound = GetWorld()->LineTraceSingleByChannel(
        GroundHit, GroundStart, GroundEnd, ECC_WorldStatic, GroundParams);

    float CapsuleHalf = Spider->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

    float CurrentNormalVel = FVector::DotProduct(Velocity, SurfaceDown);

    if (bGroundFound)
    {
        float DistError = GroundHit.Distance - (CapsuleHalf + 10.f);

        if (DistError > 2.f)
        {
            float TargetNormalVel = FMath::Clamp(DistError * 4.f, 0.f, 250.f);
            float NewNormalVel = FMath::FInterpTo(
                CurrentNormalVel, TargetNormalVel, DeltaTime, 8.f);
            Velocity += SurfaceDown * (NewNormalVel - CurrentNormalVel);
        }
        else if (DistError < -2.f)
        {
            float TargetNormalVel = FMath::Clamp(DistError * 4.f, -250.f, 0.f);
            float NewNormalVel = FMath::FInterpTo(
                CurrentNormalVel, TargetNormalVel, DeltaTime, 8.f);
            Velocity += SurfaceDown * (NewNormalVel - CurrentNormalVel);
        }
        else
        {
            Velocity -= SurfaceDown * CurrentNormalVel;
        }
    }
    else
    {
        float TargetNormalVel = FMath::Min(CurrentNormalVel + 200.f * DeltaTime, 400.f);
        Velocity += SurfaceDown * (TargetNormalVel - CurrentNormalVel);
    }

    if (!bGroundFound)
        Velocity += SurfaceDown * 200.f * DeltaTime;
    //end new

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

    //Velocity = FMath::VInterpTo(Velocity, MoveDir * MaxSpiderSpeed, DeltaTime, 6.f);
    FVector SurfNormal = TargetSurfaceNormal.GetSafeNormal();
    FVector NormalVelocity = SurfNormal * FVector::DotProduct(Velocity, SurfNormal);
    FVector LateralVelocity = Velocity - NormalVelocity;

    LateralVelocity = FMath::VInterpTo(
        LateralVelocity, MoveDir * MaxSpiderSpeed, DeltaTime, 6.f);

    Velocity = LateralVelocity + NormalVelocity;

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