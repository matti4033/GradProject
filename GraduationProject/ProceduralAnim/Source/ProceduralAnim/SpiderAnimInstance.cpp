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
    for (FSpiderLeg& Leg : Legs)
    {
        DoRaycast(Leg);

        if (Leg.bIsStepping)
        {
            Leg.StepProgress += DeltaSeconds / StepDuration;
            Leg.StepProgress = FMath::Clamp(Leg.StepProgress, 0.f, 1.f);

            Leg.CurrentFootPos = FMath::Lerp(
                Leg.StepStartPos,
                Leg.StepEndPos,
                Leg.StepProgress
            );

            float Arc = FMath::Sin(Leg.StepProgress * PI) * StepHeight;
            Leg.CurrentFootPos.Z += Arc;

            if (Leg.StepProgress >= 1.f)
            {
                Leg.bIsStepping = false;
                Leg.StepProgress = 0.f;
                Leg.CurrentFootPos = Leg.StepEndPos;
            }
        }
        else
        {
            float Dist = FVector::Dist2D(Leg.CurrentFootPos, Leg.DesiredFootPos);
            if (Dist > StepThreshold)
            {
                Leg.bIsStepping = true;
                Leg.StepProgress = 0.f;
                Leg.StepStartPos = Leg.CurrentFootPos;
                Leg.StepEndPos = Leg.DesiredFootPos;
            }
        }

        DrawDebugSphere(
            Owner->GetWorld(),
            Leg.CurrentFootPos,
            5.f, 8,
            Leg.bIsStepping ? FColor::Yellow : FColor::Green,
            false, -1.f
        );
    }
}

void USpiderAnimInstance::DoRaycast(FSpiderLeg& Leg)
{
    if (!Owner) return;

    FVector WorldOffset = Owner->GetActorTransform()
        .TransformPosition(Leg.RestOffset);

    FVector Start = WorldOffset + FVector(0, 0, 100.f);
    FVector End = WorldOffset - FVector(0, 0, 200.f);

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    bool bHit = Owner->GetWorld()->LineTraceSingleByChannel(
        Hit, Start, End, ECC_WorldStatic, Params
    );

    if (bHit)
    {
        Leg.DesiredFootPos = Hit.Location + Hit.Normal * Leg.FootGroundOffset;
    }
    else
    {
        Leg.DesiredFootPos = WorldOffset;
    }
}