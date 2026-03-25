// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralAnim/SpiderAnimInstance.h"
#include "ProceduralAnim/SpiderLeg.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSpiderAnimInstance() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_UAnimInstance();
PROCEDURALANIM_API UClass* Z_Construct_UClass_USpiderAnimInstance();
PROCEDURALANIM_API UClass* Z_Construct_UClass_USpiderAnimInstance_NoRegister();
PROCEDURALANIM_API UScriptStruct* Z_Construct_UScriptStruct_FSpiderLeg();
UPackage* Z_Construct_UPackage__Script_ProceduralAnim();
// End Cross Module References

// Begin Class USpiderAnimInstance
void USpiderAnimInstance::StaticRegisterNativesUSpiderAnimInstance()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USpiderAnimInstance);
UClass* Z_Construct_UClass_USpiderAnimInstance_NoRegister()
{
	return USpiderAnimInstance::StaticClass();
}
struct Z_Construct_UClass_USpiderAnimInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "AnimInstance" },
		{ "IncludePath", "SpiderAnimInstance.h" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Legs_MetaData[] = {
		{ "Category", "Spider" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StepThreshold_MetaData[] = {
		{ "Category", "Tuning" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StepDuration_MetaData[] = {
		{ "Category", "Tuning" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StepHeight_MetaData[] = {
		{ "Category", "Tuning" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StepCooldown_MetaData[] = {
		{ "Category", "Tuning" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SurfaceNormal_MetaData[] = {
		{ "Category", "Body" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TurnStepThresholdScale_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TurnRateFullScale_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BodyLeanRotation_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxLeanAngle_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeanInterpSpeed_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeanSpeedRef_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BodyRotationOffset_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BodyHeightOffset_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BodyRestHeight_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BodyRotInterpSpeed_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BodyHeightInterpSpeed_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpiderBodyLength_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpiderBodyWidth_MetaData[] = {
		{ "Category", "SpiderAnimInstance" },
		{ "ModuleRelativePath", "SpiderAnimInstance.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Legs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Legs;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepHeight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepCooldown;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SurfaceNormal;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TurnStepThresholdScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TurnRateFullScale;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BodyLeanRotation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxLeanAngle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LeanInterpSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LeanSpeedRef;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BodyRotationOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BodyHeightOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BodyRestHeight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BodyRotInterpSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BodyHeightInterpSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpiderBodyLength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpiderBodyWidth;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USpiderAnimInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_Legs_Inner = { "Legs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSpiderLeg, METADATA_PARAMS(0, nullptr) }; // 372763521
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_Legs = { "Legs", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, Legs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Legs_MetaData), NewProp_Legs_MetaData) }; // 372763521
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepThreshold = { "StepThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, StepThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepThreshold_MetaData), NewProp_StepThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepDuration = { "StepDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, StepDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepDuration_MetaData), NewProp_StepDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepHeight = { "StepHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, StepHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepHeight_MetaData), NewProp_StepHeight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepCooldown = { "StepCooldown", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, StepCooldown), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepCooldown_MetaData), NewProp_StepCooldown_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_SurfaceNormal = { "SurfaceNormal", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, SurfaceNormal), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SurfaceNormal_MetaData), NewProp_SurfaceNormal_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_TurnStepThresholdScale = { "TurnStepThresholdScale", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, TurnStepThresholdScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TurnStepThresholdScale_MetaData), NewProp_TurnStepThresholdScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_TurnRateFullScale = { "TurnRateFullScale", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, TurnRateFullScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TurnRateFullScale_MetaData), NewProp_TurnRateFullScale_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyLeanRotation = { "BodyLeanRotation", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, BodyLeanRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BodyLeanRotation_MetaData), NewProp_BodyLeanRotation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_MaxLeanAngle = { "MaxLeanAngle", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, MaxLeanAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxLeanAngle_MetaData), NewProp_MaxLeanAngle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_LeanInterpSpeed = { "LeanInterpSpeed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, LeanInterpSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeanInterpSpeed_MetaData), NewProp_LeanInterpSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_LeanSpeedRef = { "LeanSpeedRef", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, LeanSpeedRef), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeanSpeedRef_MetaData), NewProp_LeanSpeedRef_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyRotationOffset = { "BodyRotationOffset", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, BodyRotationOffset), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BodyRotationOffset_MetaData), NewProp_BodyRotationOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyHeightOffset = { "BodyHeightOffset", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, BodyHeightOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BodyHeightOffset_MetaData), NewProp_BodyHeightOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyRestHeight = { "BodyRestHeight", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, BodyRestHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BodyRestHeight_MetaData), NewProp_BodyRestHeight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyRotInterpSpeed = { "BodyRotInterpSpeed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, BodyRotInterpSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BodyRotInterpSpeed_MetaData), NewProp_BodyRotInterpSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyHeightInterpSpeed = { "BodyHeightInterpSpeed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, BodyHeightInterpSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BodyHeightInterpSpeed_MetaData), NewProp_BodyHeightInterpSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_SpiderBodyLength = { "SpiderBodyLength", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, SpiderBodyLength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpiderBodyLength_MetaData), NewProp_SpiderBodyLength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_SpiderBodyWidth = { "SpiderBodyWidth", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, SpiderBodyWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpiderBodyWidth_MetaData), NewProp_SpiderBodyWidth_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USpiderAnimInstance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_Legs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_Legs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepCooldown,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_SurfaceNormal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_TurnStepThresholdScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_TurnRateFullScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyLeanRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_MaxLeanAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_LeanInterpSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_LeanSpeedRef,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyRotationOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyHeightOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyRestHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyRotInterpSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_BodyHeightInterpSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_SpiderBodyLength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_SpiderBodyWidth,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USpiderAnimInstance_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USpiderAnimInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAnimInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_ProceduralAnim,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USpiderAnimInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USpiderAnimInstance_Statics::ClassParams = {
	&USpiderAnimInstance::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_USpiderAnimInstance_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_USpiderAnimInstance_Statics::PropPointers),
	0,
	0x009000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USpiderAnimInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_USpiderAnimInstance_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USpiderAnimInstance()
{
	if (!Z_Registration_Info_UClass_USpiderAnimInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USpiderAnimInstance.OuterSingleton, Z_Construct_UClass_USpiderAnimInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USpiderAnimInstance.OuterSingleton;
}
template<> PROCEDURALANIM_API UClass* StaticClass<USpiderAnimInstance>()
{
	return USpiderAnimInstance::StaticClass();
}
USpiderAnimInstance::USpiderAnimInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(USpiderAnimInstance);
USpiderAnimInstance::~USpiderAnimInstance() {}
// End Class USpiderAnimInstance

// Begin Registration
struct Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderAnimInstance_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USpiderAnimInstance, USpiderAnimInstance::StaticClass, TEXT("USpiderAnimInstance"), &Z_Registration_Info_UClass_USpiderAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USpiderAnimInstance), 2144858062U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderAnimInstance_h_787377438(TEXT("/Script/ProceduralAnim"),
	Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderAnimInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderAnimInstance_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
