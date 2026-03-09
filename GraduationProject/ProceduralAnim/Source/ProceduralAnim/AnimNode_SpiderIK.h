#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "SpiderLeg.h"
#include "AnimNode_SpiderIK.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct PROCEDURALANIM_API FAnimNode_SpiderIK : public FAnimNode_SkeletalControlBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere) TArray<FSpiderLeg> Legs;

    virtual void EvaluateSkeletalControl_AnyThread(
        FComponentSpacePoseContext& Output,
        TArray<FBoneTransform>& OutBoneTransforms) override;

    virtual bool IsValidToEvaluate(
        const USkeleton* Skeleton,
        const FBoneContainer& RequiredBones) override;
};
