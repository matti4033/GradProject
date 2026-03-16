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
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Legs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Legs;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepHeight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepCooldown;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SurfaceNormal;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USpiderAnimInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_Legs_Inner = { "Legs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSpiderLeg, METADATA_PARAMS(0, nullptr) }; // 216345057
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_Legs = { "Legs", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, Legs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Legs_MetaData), NewProp_Legs_MetaData) }; // 216345057
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepThreshold = { "StepThreshold", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, StepThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepThreshold_MetaData), NewProp_StepThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepDuration = { "StepDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, StepDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepDuration_MetaData), NewProp_StepDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepHeight = { "StepHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, StepHeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepHeight_MetaData), NewProp_StepHeight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepCooldown = { "StepCooldown", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, StepCooldown), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepCooldown_MetaData), NewProp_StepCooldown_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_SurfaceNormal = { "SurfaceNormal", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderAnimInstance, SurfaceNormal), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SurfaceNormal_MetaData), NewProp_SurfaceNormal_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USpiderAnimInstance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_Legs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_Legs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_StepCooldown,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderAnimInstance_Statics::NewProp_SurfaceNormal,
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
		{ Z_Construct_UClass_USpiderAnimInstance, USpiderAnimInstance::StaticClass, TEXT("USpiderAnimInstance"), &Z_Registration_Info_UClass_USpiderAnimInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USpiderAnimInstance), 3664119154U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderAnimInstance_h_447862242(TEXT("/Script/ProceduralAnim"),
	Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderAnimInstance_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderAnimInstance_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
