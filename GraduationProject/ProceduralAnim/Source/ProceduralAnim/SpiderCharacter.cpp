#include "SpiderCharacter.h"
#include "SpiderMovementComponent.h"

ASpiderCharacter::ASpiderCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass
        <USpiderMovementComponent>(ACharacter::CharacterMovementComponentName))
{
}