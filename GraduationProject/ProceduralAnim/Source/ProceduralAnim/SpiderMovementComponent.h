#pragma once
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpiderMovementComponent.generated.h"

UCLASS()
class PROCEDURALANIM_API USpiderMovementComponent
    : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Spider")
    float SurfaceAlignSpeed = 2.f;

    UPROPERTY(EditAnywhere, Category = "Spider")
    float WallDetectDistance = 120.f;

    UPROPERTY(EditAnywhere, Category = "Spider")
    float WallDetectRadius = 20.f;

    UPROPERTY(BlueprintReadOnly, Category = "Spider")
    FVector GravityDir = FVector(0, 0, -1.f);

    UPROPERTY(BlueprintReadOnly, Category = "Spider")
    float TransitionAlpha = 0.f;

    UPROPERTY(BlueprintReadOnly, Category = "Spider")
    bool WallDetected = false;

    FVector TargetSurfaceNormal = FVector(0, 0, 1.f);
    FVector LastWallNormal = FVector::ZeroVector;

    void NotifyFootNormals(const FVector& AverageFootNormal,
        float WallFootFraction);

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    virtual void FindFloor(const FVector& CapsuleLocation,
        FFindFloorResult& OutFloorResult,
        bool bCanUseCachedLocation,
        const FHitResult* DownwardSweepResult) const override;

private:
    float WallCommitAlpha = 0.f;

    void DetectWall(float DeltaTime);
    void AlignToSurface(float DeltaTime);
};