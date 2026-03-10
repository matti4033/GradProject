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

    float GroupCooldown[2] = { 0.f, 0.f };
    UPROPERTY(EditAnywhere, Category = "Spider|Tuning")
    float StepCooldown = 0.25f;

private:
    void UpdateLegs(float DeltaSeconds);
    void DoRaycast(FSpiderLeg& Leg);
    ACharacter* Owner = nullptr;
};