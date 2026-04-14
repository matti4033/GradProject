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
};
