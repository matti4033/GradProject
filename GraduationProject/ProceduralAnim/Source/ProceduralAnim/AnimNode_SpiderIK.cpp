#include "AnimNode_SpiderIK.h"
#include "SpiderFABRIK.h"
#include "SpiderAnimInstance.h"
#include "Animation/AnimInstanceProxy.h"

bool FAnimNode_SpiderIK::IsValidToEvaluate(
    const USkeleton* Skeleton,
    const FBoneContainer& RequiredBones)
{
    return true;
}

void FAnimNode_SpiderIK::EvaluateSkeletalControl_AnyThread(
    FComponentSpacePoseContext& Output,
    TArray<FBoneTransform>& OutBoneTransforms)
{
    const FBoneContainer& BoneContainer =
        Output.AnimInstanceProxy->GetRequiredBones();

    USpiderAnimInstance* SpiderInstance = Cast<USpiderAnimInstance>(
        Output.AnimInstanceProxy->GetAnimInstanceObject());
    if (!SpiderInstance) return;

    const TArray<FSpiderLeg>& LegsToUse = SpiderInstance->Legs;

    FTransform ComponentTransform =
        Output.AnimInstanceProxy->GetComponentTransform();

    for (const FSpiderLeg& Leg : LegsToUse)
    {
        FCompactPoseBoneIndex UpperIdx(
            BoneContainer.GetPoseBoneIndexForBoneName(Leg.UpperBone));
        FCompactPoseBoneIndex MidIdx(
            BoneContainer.GetPoseBoneIndexForBoneName(Leg.MidBone));
        FCompactPoseBoneIndex TipIdx(
            BoneContainer.GetPoseBoneIndexForBoneName(Leg.TipBone));

        if (UpperIdx == INDEX_NONE ||
            MidIdx == INDEX_NONE ||
            TipIdx == INDEX_NONE) continue;

        if (Leg.CurrentFootPos.IsNearlyZero()) continue;

        FTransform UpperCS = Output.Pose.GetComponentSpaceTransform(UpperIdx);
        FTransform MidCS = Output.Pose.GetComponentSpaceTransform(MidIdx);
        FTransform TipCS = Output.Pose.GetComponentSpaceTransform(TipIdx);

        FVector UpperPos = UpperCS.GetLocation();
        FVector MidPos = MidCS.GetLocation();
        FVector TipPos = TipCS.GetLocation();

        FVector ActualUpperDir = (MidPos - UpperPos).GetSafeNormal();
        FVector ActualMidDir = (TipPos - MidPos).GetSafeNormal();
        float UpperLen = FVector::Dist(UpperPos, MidPos);
        float MidLen = FVector::Dist(MidPos, TipPos);


        FVector LocalTarget =
            ComponentTransform.InverseTransformPosition(Leg.CurrentFootPos);

        float HeightDiff = FMath::Max(0.f, LocalTarget.Z - UpperPos.Z);
        float UpwardBias = 2.f + HeightDiff * 0.05f;

        FVector UpDir = SpiderInstance->SurfaceNormal;

        FVector OutwardDir = UpperPos.GetSafeNormal();
        FVector PoleDir = (OutwardDir + UpDir * UpwardBias).GetSafeNormal();
        FVector BiasedKnee = UpperPos + PoleDir * UpperLen;
        FVector BiasedAnkle = BiasedKnee + ActualMidDir * MidLen;
        FVector BiasedTipEnd = BiasedAnkle + ActualMidDir * MidLen;

        TArray<FVector> Chain = { UpperPos, BiasedKnee, BiasedAnkle, BiasedTipEnd };
        FSpiderFABRIK::Solve(Chain, LocalTarget, 20);

        float MinAnkleZ = Chain[3].Z + 40.f;
        if (Chain[2].Z < MinAnkleZ)
        {
            Chain[2].Z = MinAnkleZ;
            FVector AnkleToRoot = (Chain[0] - Chain[2]).GetSafeNormal();
            Chain[1] = Chain[2] + AnkleToRoot * MidLen;
            FVector RootToKnee = Chain[1] - Chain[0];
            if (RootToKnee.Size() > UpperLen)
                Chain[1] = Chain[0] + RootToKnee.GetSafeNormal() * UpperLen;
        }

        FVector UpperDir = (Chain[1] - Chain[0]).GetSafeNormal();
        FVector MidDir = (Chain[2] - Chain[1]).GetSafeNormal();
        FVector TipSolvedDir = (Chain[3] - Chain[2]).GetSafeNormal();

        FTransform NewUpperCS = UpperCS;
        FTransform NewMidCS = MidCS;
        FTransform NewTipCS = TipCS;

        NewUpperCS.SetLocation(UpperPos);
        NewMidCS.SetLocation(Chain[1]);
        NewTipCS.SetLocation(Chain[2]);

        auto GetBoneAxis = [](
            const FTransform& Transform,
            const FVector& ActualBoneDir) -> FVector
            {
                FQuat Rot = Transform.GetRotation();
                FVector Axes[6] = {
                     Rot.GetForwardVector(), -Rot.GetForwardVector(),
                     Rot.GetRightVector(),   -Rot.GetRightVector(),
                     Rot.GetUpVector(),      -Rot.GetUpVector()
                };
                FVector BestAxis = Axes[0];
                float   BestDot = -1.f;
                for (const FVector& Axis : Axes)
                {
                    float Dot = FVector::DotProduct(Axis, ActualBoneDir);
                    if (Dot > BestDot) { BestDot = Dot; BestAxis = Axis; }
                }
                return BestAxis;
            };

        auto ApplyRotation = [&GetBoneAxis](
            FTransform& Transform,
            const FVector& NewDir,
            const FVector& ActualBoneDir)
            {
                if (NewDir.IsNearlyZero()) return;
                FVector CurrentDir = GetBoneAxis(Transform, ActualBoneDir);
                if (CurrentDir.IsNearlyZero()) return;
                FQuat Delta = FQuat::FindBetweenNormals(CurrentDir, NewDir);
                Transform.SetRotation(Delta * Transform.GetRotation());
            };

        ApplyRotation(NewUpperCS, UpperDir, ActualUpperDir);
        ApplyRotation(NewMidCS, MidDir, ActualMidDir);
        ApplyRotation(NewTipCS, TipSolvedDir, ActualMidDir);

        OutBoneTransforms.Add(FBoneTransform(UpperIdx, NewUpperCS));
        OutBoneTransforms.Add(FBoneTransform(MidIdx, NewMidCS));
        OutBoneTransforms.Add(FBoneTransform(TipIdx, NewTipCS));
    }

    OutBoneTransforms.Sort(FCompareBoneTransformIndex());
}