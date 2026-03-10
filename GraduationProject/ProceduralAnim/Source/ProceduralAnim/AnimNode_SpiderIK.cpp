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

        FVector TipEnd = TipPos + ActualMidDir * MidLen;

        TArray<FVector> Chain = { UpperPos, MidPos, TipPos, TipEnd };
        FSpiderFABRIK::Solve(Chain, LocalTarget, 10);
       
        FVector RootToTip = (Chain[3] - Chain[0]).GetSafeNormal();

        FVector OutwardDir = UpperPos.GetSafeNormal();
        FVector WorldPole = UpperPos +
            (OutwardDir + FVector(0, 0, 6.f)).GetSafeNormal() *
            Leg.PoleOffset.Z;

        FVector RootToPole = WorldPole - Chain[0];
        FVector PoleOnPlane = (RootToPole -
            FVector::DotProduct(RootToPole, RootToTip) * RootToTip
            ).GetSafeNormal();

        FVector RootToKnee = Chain[1] - Chain[0];
        FVector KneeOnPlane = (RootToKnee -
            FVector::DotProduct(RootToKnee, RootToTip) * RootToTip
            ).GetSafeNormal();

        if (!PoleOnPlane.IsNearlyZero(0.001f) &&
            !KneeOnPlane.IsNearlyZero(0.001f))
        {
            FQuat PoleRot = FQuat::FindBetweenNormals(
                KneeOnPlane, PoleOnPlane);
            FVector NewKneeOffset = PoleRot.RotateVector(RootToKnee);
            Chain[1] = Chain[0] + NewKneeOffset.GetSafeNormal() * UpperLen;
        }

        Chain[2].X = FMath::Lerp(Chain[1].X, Chain[3].X, 0.5f);
        Chain[2].Y = FMath::Lerp(Chain[1].Y, Chain[3].Y, 0.5f);
        Chain[2].Z = FMath::Lerp(Chain[1].Z, Chain[3].Z, 0.3f);

        FVector KneeToAnkle = Chain[2] - Chain[1];
        if (KneeToAnkle.Size() > MidLen)
            Chain[2] = Chain[1] + KneeToAnkle.GetSafeNormal() * MidLen;

        if (Chain[2].Z < Chain[3].Z + 20.f)
            Chain[2].Z = Chain[3].Z + 20.f;

        Chain[3] = LocalTarget;

        FVector AnkleToTarget = (Chain[3] - Chain[2]).GetSafeNormal();
        Chain[2] = Chain[3] - AnkleToTarget * MidLen;
        
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