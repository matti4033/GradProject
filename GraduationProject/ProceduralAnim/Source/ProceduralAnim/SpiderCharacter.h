#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpiderCharacter.generated.h"

UCLASS()
class PROCEDURALANIM_API ASpiderCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASpiderCharacter(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(BlueprintReadWrite)
    FVector2D MovementInput;

    virtual void Tick(float DeltaSeconds) override;
    virtual FRotator GetViewRotation() const override;
    virtual void AddControllerPitchInput(float Value) override;

    UPROPERTY(EditAnywhere, Category = "Camera")
    float PitchMin = -20.f;

    UPROPERTY(EditAnywhere, Category = "Camera")
    float PitchMax = 70.f;

private:
    float CameraPitch = 0.f;
    float RawPitchInput = 0.f;

};