#include "SpiderCharacter.h"
#include "SpiderMovementComponent.h"

ASpiderCharacter::ASpiderCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass
        <USpiderMovementComponent>(ACharacter::CharacterMovementComponentName))
{

}

void ASpiderCharacter::AddControllerPitchInput(float Value)
{
    RawPitchInput = Value;
}

void ASpiderCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    CameraPitch = FMath::Clamp(CameraPitch + RawPitchInput, PitchMin, PitchMax);
    RawPitchInput = 0.f;
}

FRotator ASpiderCharacter::GetViewRotation() const
{
    if (!Controller) return GetActorRotation();

    USpiderMovementComponent* SpiderMove =
        Cast<USpiderMovementComponent>(GetMovementComponent());

    FVector SurfUp = SpiderMove
        ? SpiderMove->TargetSurfaceNormal.GetSafeNormal()
        : FVector::UpVector;

    FVector SurfFwd = GetActorForwardVector();
    FVector SurfRight = GetActorRightVector();

    FQuat PitchQ(SurfRight, FMath::DegreesToRadians(CameraPitch));
    FVector FinalFwd = PitchQ.RotateVector(SurfFwd);
    FVector FinalUp = PitchQ.RotateVector(SurfUp);

    return FRotationMatrix::MakeFromXZ(FinalFwd, FinalUp).Rotator();
}