#pragma once
#include "CoreMinimal.h"
#include "AnimGraphNode_SkeletalControlBase.h"
#include "../ProceduralAnim/AnimNode_SpiderIK.h"
#include "AnimGraphNode_SpiderIK.generated.h"

UCLASS()
class PROCEDURALANIMEDITOR_API UAnimGraphNode_SpiderIK 
    : public UAnimGraphNode_SkeletalControlBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Settings")
    FAnimNode_SpiderIK Node;

    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) 
        const override;
    virtual FText GetTooltipText() const override;
    virtual FText GetControllerDescription() const override;

protected:
    virtual const FAnimNode_SkeletalControlBase* GetNode() const override
    {
        return &Node;
    }
};