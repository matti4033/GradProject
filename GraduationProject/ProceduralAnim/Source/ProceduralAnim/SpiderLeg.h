#pragma once
#include "CoreMinimal.h"
#include "SpiderLeg.generated.h"

USTRUCT(BlueprintType)
struct FSpiderLeg
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere) FName UpperBone;
    UPROPERTY(EditAnywhere) FName MidBone;
    UPROPERTY(EditAnywhere) FName TipBone;

    UPROPERTY(EditAnywhere) FVector CurrentFootPos = FVector::ZeroVector;
    UPROPERTY(EditAnywhere) FVector DesiredFootPos = FVector::ZeroVector;
    UPROPERTY(EditAnywhere) FVector RestOffset = FVector::ZeroVector;
    UPROPERTY(EditAnywhere) FVector PoleOffset = FVector(0.f, 0.f, 80.f);
    UPROPERTY(EditAnywhere) float UpperMaxAngle = 80.f;
    UPROPERTY(EditAnywhere) float MidMaxAngle = 120.f;
    UPROPERTY(EditAnywhere) float TipMaxAngle = 120.f;


    bool    bIsStepping = false;
    float   StepProgress = 0.f;
    FVector StepStartPos = FVector::ZeroVector;
    FVector StepEndPos = FVector::ZeroVector;
};