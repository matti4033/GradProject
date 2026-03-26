// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralAnim/SpiderMovementComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSpiderMovementComponent() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_UCharacterMovementComponent();
PROCEDURALANIM_API UClass* Z_Construct_UClass_USpiderMovementComponent();
PROCEDURALANIM_API UClass* Z_Construct_UClass_USpiderMovementComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProceduralAnim();
// End Cross Module References

// Begin Class USpiderMovementComponent
void USpiderMovementComponent::StaticRegisterNativesUSpiderMovementComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USpiderMovementComponent);
UClass* Z_Construct_UClass_USpiderMovementComponent_NoRegister()
{
	return USpiderMovementComponent::StaticClass();
}
struct Z_Construct_UClass_USpiderMovementComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "SpiderMovementComponent.h" },
		{ "ModuleRelativePath", "SpiderMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SurfaceAlignSpeed_MetaData[] = {
		{ "Category", "Spider" },
		{ "ModuleRelativePath", "SpiderMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallDetectDistance_MetaData[] = {
		{ "Category", "Spider" },
		{ "ModuleRelativePath", "SpiderMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallDetectRadius_MetaData[] = {
		{ "Category", "Spider" },
		{ "ModuleRelativePath", "SpiderMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GravityDir_MetaData[] = {
		{ "Category", "Spider" },
		{ "ModuleRelativePath", "SpiderMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TransitionAlpha_MetaData[] = {
		{ "Category", "Spider" },
		{ "ModuleRelativePath", "SpiderMovementComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallDetected_MetaData[] = {
		{ "Category", "Spider" },
		{ "ModuleRelativePath", "SpiderMovementComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SurfaceAlignSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallDetectDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallDetectRadius;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GravityDir;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TransitionAlpha;
	static void NewProp_WallDetected_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_WallDetected;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USpiderMovementComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_SurfaceAlignSpeed = { "SurfaceAlignSpeed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderMovementComponent, SurfaceAlignSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SurfaceAlignSpeed_MetaData), NewProp_SurfaceAlignSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_WallDetectDistance = { "WallDetectDistance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderMovementComponent, WallDetectDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallDetectDistance_MetaData), NewProp_WallDetectDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_WallDetectRadius = { "WallDetectRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderMovementComponent, WallDetectRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallDetectRadius_MetaData), NewProp_WallDetectRadius_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_GravityDir = { "GravityDir", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderMovementComponent, GravityDir), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GravityDir_MetaData), NewProp_GravityDir_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_TransitionAlpha = { "TransitionAlpha", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USpiderMovementComponent, TransitionAlpha), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TransitionAlpha_MetaData), NewProp_TransitionAlpha_MetaData) };
void Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_WallDetected_SetBit(void* Obj)
{
	((USpiderMovementComponent*)Obj)->WallDetected = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_WallDetected = { "WallDetected", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(USpiderMovementComponent), &Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_WallDetected_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallDetected_MetaData), NewProp_WallDetected_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USpiderMovementComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_SurfaceAlignSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_WallDetectDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_WallDetectRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_GravityDir,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_TransitionAlpha,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USpiderMovementComponent_Statics::NewProp_WallDetected,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USpiderMovementComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USpiderMovementComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UCharacterMovementComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_ProceduralAnim,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USpiderMovementComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USpiderMovementComponent_Statics::ClassParams = {
	&USpiderMovementComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_USpiderMovementComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_USpiderMovementComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USpiderMovementComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_USpiderMovementComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USpiderMovementComponent()
{
	if (!Z_Registration_Info_UClass_USpiderMovementComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USpiderMovementComponent.OuterSingleton, Z_Construct_UClass_USpiderMovementComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USpiderMovementComponent.OuterSingleton;
}
template<> PROCEDURALANIM_API UClass* StaticClass<USpiderMovementComponent>()
{
	return USpiderMovementComponent::StaticClass();
}
USpiderMovementComponent::USpiderMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(USpiderMovementComponent);
USpiderMovementComponent::~USpiderMovementComponent() {}
// End Class USpiderMovementComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderMovementComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USpiderMovementComponent, USpiderMovementComponent::StaticClass, TEXT("USpiderMovementComponent"), &Z_Registration_Info_UClass_USpiderMovementComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USpiderMovementComponent), 405332871U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderMovementComponent_h_588352641(TEXT("/Script/ProceduralAnim"),
	Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderMovementComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderMovementComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
