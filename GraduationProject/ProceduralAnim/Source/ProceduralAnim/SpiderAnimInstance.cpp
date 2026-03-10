#include "SpiderAnimInstance.h"
#include "SpiderFABRIK.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"

void USpiderAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    Owner = Cast<ACharacter>(GetOwningActor());
}

void USpiderAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (!Owner) return;
    UpdateLegs(DeltaSeconds);
}

void USpiderAnimInstance::UpdateLegs(float DeltaSeconds)
{
    GroupCooldown[0] = FMath::Max(0.f, GroupCooldown[0] - DeltaSeconds);
    GroupCooldown[1] = FMath::Max(0.f, GroupCooldown[1] - DeltaSeconds);

    for (FSpiderLeg& Leg : Legs)
        DoRaycast(Leg);

    FVector Forward = Owner->GetActorForwardVector();
    FVector FRPos, FLPos, MRPos, MLPos;
    FRPos = FLPos = MRPos = MLPos = FVector::ZeroVector;

    for (const FSpiderLeg& Leg : Legs)
    {
        if (Leg.UpperBone == FName("LegFR_Upper")) FRPos = Leg.CurrentFootPos;
        if (Leg.UpperBone == FName("LegFL_Upper")) FLPos = Leg.CurrentFootPos;
        if (Leg.UpperBone == FName("LegMR_Upper")) MRPos = Leg.CurrentFootPos;
        if (Leg.UpperBone == FName("LegML_Upper")) MLPos = Leg.CurrentFootPos;
    }

    for (FSpiderLeg& Leg : Legs)
    {
        if (Leg.UpperBone == FName("LegMR_Upper") && !FRPos.IsNearlyZero())
        {
            float FrontDot = FVector::DotProduct(FRPos, Forward);
            float MidDot = FVector::DotProduct(Leg.DesiredFootPos, Forward);
            if (MidDot > FrontDot)
                Leg.DesiredFootPos -= Forward * (MidDot - FrontDot);
        }
        if (Leg.UpperBone == FName("LegML_Upper") && !FLPos.IsNearlyZero())
        {
            float FrontDot = FVector::DotProduct(FLPos, Forward);
            float MidDot = FVector::DotProduct(Leg.DesiredFootPos, Forward);
            if (MidDot > FrontDot)
                Leg.DesiredFootPos -= Forward * (MidDot - FrontDot);
        }
        if (Leg.UpperBone == FName("LegRR_Upper") && !MRPos.IsNearlyZero())
        {
            float MidDotVal = FVector::DotProduct(MRPos, Forward);
            float RearDot = FVector::DotProduct(Leg.DesiredFootPos, Forward);
            if (RearDot > MidDotVal)
                Leg.DesiredFootPos -= Forward * (RearDot - MidDotVal);
        }
        if (Leg.UpperBone == FName("LegRL_Upper") && !MLPos.IsNearlyZero())
        {
            float MidDotVal = FVector::DotProduct(MLPos, Forward);
            float RearDot = FVector::DotProduct(Leg.DesiredFootPos, Forward);
            if (RearDot > MidDotVal)
                Leg.DesiredFootPos -= Forward * (RearDot - MidDotVal);
        }
    }

    bool bGroupStepping[2] = { false, false };
    for (const FSpiderLeg& Leg : Legs)
        if (Leg.bIsStepping)
            bGroupStepping[Leg.GaitGroup] = true;

    bool bGroupNeedsStep[2] = { false, false };
    for (const FSpiderLeg& Leg : Legs)
    {
        if (!Leg.bIsStepping)
        {
            float Dist = FVector::Dist(Leg.CurrentFootPos, Leg.DesiredFootPos);
            if (Dist > StepThreshold)
                bGroupNeedsStep[Leg.GaitGroup] = true;
        }
    }

    for (int32 Group = 0; Group < 2; Group++)
    {
        int32 OtherGroup = 1 - Group;
        if (bGroupNeedsStep[Group]
            && !bGroupStepping[Group]
            && !bGroupStepping[OtherGroup]
            && GroupCooldown[Group] <= 0.f)
        {
            for (FSpiderLeg& Leg : Legs)
            {
                if (Leg.GaitGroup == Group && !Leg.bIsStepping)
                {
                    Leg.bIsStepping = true;
                    Leg.StepProgress = 0.f;
                    Leg.StepStartPos = Leg.CurrentFootPos;
                    Leg.StepEndPos = Leg.DesiredFootPos;
                }
            }
            bGroupStepping[Group] = true;
        }
    }

    for (FSpiderLeg& Leg : Legs)
    {
        if (Leg.bIsStepping)
        {
            Leg.StepProgress += DeltaSeconds / StepDuration;
            Leg.StepProgress = FMath::Clamp(Leg.StepProgress, 0.f, 1.f);

            Leg.CurrentFootPos = FMath::Lerp(
                Leg.StepStartPos, Leg.StepEndPos, Leg.StepProgress);

            float Arc = FMath::Sin(Leg.StepProgress * PI) * StepHeight;
            Leg.CurrentFootPos.Z += Arc;

            if (Leg.StepProgress >= 1.f)
            {
                Leg.bIsStepping = false;
                Leg.StepProgress = 0.f;
                Leg.CurrentFootPos = Leg.StepEndPos;
                GroupCooldown[Leg.GaitGroup] = StepCooldown;
            }
        }

        DrawDebugSphere(Owner->GetWorld(), Leg.CurrentFootPos,
            5.f, 8,
            Leg.bIsStepping ? FColor::Yellow : FColor::Green,
            false, -1.f);
    }
}

void USpiderAnimInstance::DoRaycast(FSpiderLeg& Leg)
{
    if (!Owner) return;

    FVector Velocity = Owner->GetVelocity();
    float Speed = Velocity.Size();
    FVector VelocityDir = Velocity.GetSafeNormal();

    float PredictionScale = FMath::Clamp(Speed / 300.f, 0.f, 1.f);
    FVector PredictionOffset = VelocityDir * Speed * 0.15f * PredictionScale;

    FVector WorldOffset = Owner->GetActorTransform()
        .TransformPosition(Leg.RestOffset);
    WorldOffset += PredictionOffset;

    FVector Start = WorldOffset + FVector(0, 0, 300.f);
    FVector End = WorldOffset - FVector(0, 0, 500.f);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    bool bHit = Owner->GetWorld()->LineTraceSingleByChannel(
        Hit, Start, End, ECC_WorldStatic, Params);

    if (bHit)
        Leg.DesiredFootPos = Hit.Location + Hit.Normal * Leg.FootGroundOffset;
    else
        Leg.DesiredFootPos = WorldOffset;

    if (Leg.CurrentFootPos.IsNearlyZero())
        Leg.CurrentFootPos = Leg.DesiredFootPos;
}