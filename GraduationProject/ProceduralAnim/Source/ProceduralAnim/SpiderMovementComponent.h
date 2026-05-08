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
    bool bLedgeTransition = false;

    float TransitionAlpha = 0.f;

    float MaxSpiderSpeed = 400.f;

    UPROPERTY(EditAnywhere, Category = "Spider")
    float WallDetectDistance = 150.f;

    UPROPERTY(EditAnywhere, Category = "Spider")
    float WallDetectRadius = 20.f;

    UPROPERTY(BlueprintReadOnly, Category = "Spider")
    bool WallDetected = false;
    FVector LastWallNormal = FVector::ZeroVector;

private:
    float LastControllerYaw = 0.f;
    FVector CurrentSurfaceForward = FVector::ForwardVector;
};