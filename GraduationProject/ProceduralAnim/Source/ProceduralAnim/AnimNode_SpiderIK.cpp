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

        // Convert foot target to component space
        FVector LocalTarget =
            ComponentTransform.InverseTransformPosition(Leg.CurrentFootPos);

        // Calculate tip bone length
        float TipBoneLen = FVector::Dist(MidPos, TipPos);

        // Virtual 4th point — the actual end of the tip bone
        FVector TipDir = (TipPos - MidPos).GetSafeNormal();
        FVector TipEnd = TipPos + TipDir * TipBoneLen;

        // Bias mid bone upward for knee arc
        FVector MidBias = MidPos;
        MidBias.Z += Leg.PoleOffset.Z;

        // Build 4-point chain
        // Chain[3] = TipEnd is the point that reaches LocalTarget
        TArray<FVector> Chain = { UpperPos, MidBias, TipPos, TipEnd };
        FSpiderFABRIK::Solve(Chain, LocalTarget, 10);

        // Directions from solved chain
        // Chain[3] == LocalTarget after solving
        FVector UpperDir = (Chain[1] - Chain[0]).GetSafeNormal();
        FVector MidDir = (Chain[2] - Chain[1]).GetSafeNormal();
        FVector TipSolvedDir = (Chain[3] - Chain[2]).GetSafeNormal();

        // Reconstruct positions using bone lengths
        float UpperLen = FVector::Dist(UpperPos, MidPos);
        float MidLen = FVector::Dist(MidPos, TipPos);

        Chain[1] = Chain[0] + UpperDir * UpperLen;
        Chain[2] = Chain[1] + MidDir * MidLen;
        // Chain[3] is virtual — not written to any bone

        // Apply to transforms
        FTransform NewUpperCS = UpperCS;
        FTransform NewMidCS = MidCS;
        FTransform NewTipCS = TipCS;

        NewUpperCS.SetLocation(Chain[0]);
        NewMidCS.SetLocation(Chain[1]);
        NewTipCS.SetLocation(Chain[2]);

        auto GetBoneAxis = [](const FTransform& Transform, const FVector& ActualBoneDir) -> FVector
            {
                FQuat Rot = Transform.GetRotation();
                FVector Axes[6] = {
                     Rot.GetForwardVector(),
                    -Rot.GetForwardVector(),
                     Rot.GetRightVector(),
                    -Rot.GetRightVector(),
                     Rot.GetUpVector(),
                    -Rot.GetUpVector()
                };

                FVector BestAxis = Axes[0];
                float BestDot = -1.f;
                for (const FVector& Axis : Axes)
                {
                    float Dot = FVector::DotProduct(Axis, ActualBoneDir);
                    if (Dot > BestDot)
                    {
                        BestDot = Dot;
                        BestAxis = Axis;
                    }
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

        FVector ActualUpperDir = (MidPos - UpperPos).GetSafeNormal();
        FVector ActualMidDir = (TipPos - MidPos).GetSafeNormal();
        FVector ActualTipDir = (TipEnd - TipPos).GetSafeNormal();

        if (Leg.UpperBone == FName("LegBL_Upper") || Leg.UpperBone == FName("LegBR_Upper"))
        {
            UE_LOG(LogTemp, Warning, TEXT("=== %s ==="), *Leg.UpperBone.ToString());
            UE_LOG(LogTemp, Warning, TEXT("UpperPos: %s"), *UpperPos.ToString());
            UE_LOG(LogTemp, Warning, TEXT("MidPos: %s"), *MidPos.ToString());
            UE_LOG(LogTemp, Warning, TEXT("ActualUpperDir: %s"), *ActualUpperDir.ToString());
            UE_LOG(LogTemp, Warning, TEXT("LocalTarget: %s"), *LocalTarget.ToString());
        }

        ApplyRotation(NewUpperCS, UpperDir, ActualUpperDir);
        ApplyRotation(NewMidCS, MidDir, ActualMidDir);
        ApplyRotation(NewTipCS, TipSolvedDir, ActualTipDir);

        OutBoneTransforms.Add(FBoneTransform(UpperIdx, NewUpperCS));
        OutBoneTransforms.Add(FBoneTransform(MidIdx, NewMidCS));
        OutBoneTransforms.Add(FBoneTransform(TipIdx, NewTipCS));
    }

    OutBoneTransforms.Sort(FCompareBoneTransformIndex());
}