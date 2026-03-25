#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SpiderLeg.h"
#include "SpiderAnimInstance.generated.h"

UCLASS()
class PROCEDURALANIM_API USpiderAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spider")
    TArray<FSpiderLeg> Legs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tuning")
    float StepThreshold = 40.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tuning")
    float StepDuration = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tuning")
    float StepHeight = 20.f;
    UPROPERTY(EditAnywhere, Category = "Tuning")
    float StepCooldown = 0.25f;

    float GroupCooldown[2] = { 0.f, 0.f };

    UPROPERTY(BlueprintReadWrite, Category = "Body")
    FVector SurfaceNormal = FVector(0, 0, 1.f);

    float CachedDelta = 0.f;

    UPROPERTY(EditAnywhere)
    float TurnStepThresholdScale = 0.4f;
    UPROPERTY(EditAnywhere)
    float TurnRateFullScale = 90.f;
    FRotator LastBodyRotation;

    UPROPERTY(BlueprintReadWrite)
    FRotator BodyLeanRotation = FRotator::ZeroRotator;
    UPROPERTY(EditAnywhere)
    float    MaxLeanAngle = 8.f;
    UPROPERTY(EditAnywhere)
    float    LeanInterpSpeed = 5.f;
    UPROPERTY(EditAnywhere)
    float    LeanSpeedRef = 600.f;

    UPROPERTY(BlueprintReadWrite)
    FRotator BodyRotationOffset = FRotator::ZeroRotator;
    UPROPERTY(BlueprintReadWrite)
    float BodyHeightOffset = 0.f;
    UPROPERTY(EditAnywhere)
    float BodyRestHeight = 50.f;    
    UPROPERTY(EditAnywhere)
    float    BodyRotInterpSpeed = 6.f;
    UPROPERTY(EditAnywhere)
    float    BodyHeightInterpSpeed = 8.f;
    UPROPERTY(EditAnywhere)
    float    SpiderBodyLength = 80.f;
    UPROPERTY(EditAnywhere)
    float    SpiderBodyWidth = 60.f;

    void UpdateBody(float DeltaSeconds);

private:
    void UpdateLegs(float DeltaSeconds);
    void DoRaycast(FSpiderLeg& Leg);
    ACharacter* Owner = nullptr;
};