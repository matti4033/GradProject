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

//static FVector ClampDirection(
//    const FVector& Direction,
//    const FVector& ReferenceDirection,
//    float MaxAngleDegrees)
//{
//    if (Direction.IsNearlyZero() || ReferenceDirection.IsNearlyZero())
//        return Direction;
//
//    float AngleRad = FMath::DegreesToRadians(MaxAngleDegrees);
//    float DotProduct = FVector::DotProduct(
//        Direction.GetSafeNormal(),
//        ReferenceDirection.GetSafeNormal());
//    float CurrentAngle = FMath::Acos(FMath::Clamp(DotProduct, -1.f, 1.f));
//
//    if (CurrentAngle <= AngleRad)
//        return Direction;
//
//    FVector Cross = FVector::CrossProduct(ReferenceDirection, Direction);
//    if (Cross.IsNearlyZero())
//        return ReferenceDirection;
//
//    FQuat LimitRot(Cross.GetSafeNormal(), AngleRad);
//    return LimitRot.RotateVector(ReferenceDirection).GetSafeNormal()
//        * Direction.Size();
//}

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

        float TipBoneLen = FVector::Dist(MidPos, TipPos);

        FVector MidBias = MidPos;
        MidBias.Z += Leg.PoleOffset.Z;

        // First pass
        TArray<FVector> Chain = { UpperPos, MidBias, TipPos };
        FSpiderFABRIK::Solve(Chain, LocalTarget, 5);

        // offset target back by tip length
        FVector ApproxMidDir = (Chain[2] - Chain[1]).GetSafeNormal();
        FVector AdjustedTarget = LocalTarget - ApproxMidDir * TipBoneLen;

        // Second pass
        // Now tip END lands at LocalTarget
        Chain = { UpperPos, MidBias, TipPos };
        FSpiderFABRIK::Solve(Chain, AdjustedTarget, 10);

        FVector UpperDir = (Chain[1] - Chain[0]).GetSafeNormal();
        FVector MidDir = (Chain[2] - Chain[1]).GetSafeNormal();
        FVector TipDir = (LocalTarget - Chain[2]).GetSafeNormal();

        float UpperLen = FVector::Dist(UpperPos, MidPos);
        float MidLen = FVector::Dist(MidPos, TipPos);

        Chain[1] = Chain[0] + UpperDir * UpperLen;
        Chain[2] = Chain[1] + MidDir * MidLen;

        FTransform NewUpperCS = UpperCS;
        FTransform NewMidCS = MidCS;
        FTransform NewTipCS = TipCS;

        NewUpperCS.SetLocation(Chain[0]);
        NewMidCS.SetLocation(Chain[1]);
        NewTipCS.SetLocation(Chain[2]);

        // Bone axis is -RightVector (found via debug log)
        auto ApplyRotation = [](FTransform& Transform, const FVector& NewDir)
            {
                if (NewDir.IsNearlyZero()) return;
                FVector CurrentDir = -Transform.GetRotation().GetRightVector();
                if (CurrentDir.IsNearlyZero()) return;
                FQuat Delta = FQuat::FindBetweenNormals(CurrentDir, NewDir);
                Transform.SetRotation(Delta * Transform.GetRotation());
            };

        ApplyRotation(NewUpperCS, UpperDir);
        ApplyRotation(NewMidCS, MidDir);
        ApplyRotation(NewTipCS, TipDir);

        OutBoneTransforms.Add(FBoneTransform(UpperIdx, NewUpperCS));
        OutBoneTransforms.Add(FBoneTransform(MidIdx, NewMidCS));
        OutBoneTransforms.Add(FBoneTransform(TipIdx, NewTipCS));
    }

    OutBoneTransforms.Sort(FCompareBoneTransformIndex());
}