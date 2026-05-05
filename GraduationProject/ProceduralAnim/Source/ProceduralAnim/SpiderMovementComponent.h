#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpiderMovementComponent.generated.h"

UCLASS()
class PROCEDURALANIM_API USpiderMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()
public:
    USpiderMovementComponent();

    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    virtual void PhysCustom(float DeltaTime, int32 Iterations) override;
    virtual void PhysCustom_Custom(float DeltaTime, int32 Iterations);

    bool SpiderFindFloor(const FVector& Location, FFindFloorResult& OutFloor);
    bool SpiderTryStepUp(const FHitResult& Hit, const FVector& Delta);

    void NotifyFootNormals(const FVector& AvgNormal, float SupportFraction);

    FVector TargetSurfaceNormal = FVector::UpVector;

    float TransitionAlpha = 0.f;

    float MaxSpiderSpeed = 400.f;

private:
    float LastControllerYaw = 0.f;
    FVector CurrentSurfaceForward = FVector::ForwardVector;
};