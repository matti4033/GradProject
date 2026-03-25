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
    float SurfaceAlignSpeed = 5.f;

    UPROPERTY(EditAnywhere, Category = "Spider")
    float WallDetectDistance = 80.f;

    UPROPERTY(EditAnywhere, Category = "Spider")
    float WallDetectRadius = 20.f;

    UPROPERTY(BlueprintReadOnly, Category = "Spider")
    FVector GravityDir = FVector(0, 0, -1.f);

    UPROPERTY(BlueprintReadWrite, Category = "Spider")
    FVector TargetSurfaceNormal = FVector(0, 0, 1.f);

    virtual float GetGravityZ() const override;

    virtual void PhysicsRotation(float DeltaTime) override;
    virtual void TickComponent(float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

private:
    void DetectWall(float DeltaTime);
    void AlignToSurface(float DeltaTime);
};