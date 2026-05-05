// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralAnim/SpiderCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSpiderCharacter() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
PROCEDURALANIM_API UClass* Z_Construct_UClass_ASpiderCharacter();
PROCEDURALANIM_API UClass* Z_Construct_UClass_ASpiderCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProceduralAnim();
// End Cross Module References

// Begin Class ASpiderCharacter
void ASpiderCharacter::StaticRegisterNativesASpiderCharacter()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASpiderCharacter);
UClass* Z_Construct_UClass_ASpiderCharacter_NoRegister()
{
	return ASpiderCharacter::StaticClass();
}
struct Z_Construct_UClass_ASpiderCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SpiderCharacter.h" },
		{ "ModuleRelativePath", "SpiderCharacter.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementInput_MetaData[] = {
		{ "Category", "SpiderCharacter" },
		{ "ModuleRelativePath", "SpiderCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PitchMin_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "SpiderCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PitchMax_MetaData[] = {
		{ "Category", "Camera" },
		{ "ModuleRelativePath", "SpiderCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_MovementInput;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PitchMin;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PitchMax;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASpiderCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ASpiderCharacter_Statics::NewProp_MovementInput = { "MovementInput", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASpiderCharacter, MovementInput), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementInput_MetaData), NewProp_MovementInput_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASpiderCharacter_Statics::NewProp_PitchMin = { "PitchMin", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASpiderCharacter, PitchMin), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PitchMin_MetaData), NewProp_PitchMin_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASpiderCharacter_Statics::NewProp_PitchMax = { "PitchMax", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASpiderCharacter, PitchMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PitchMax_MetaData), NewProp_PitchMax_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASpiderCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASpiderCharacter_Statics::NewProp_MovementInput,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASpiderCharacter_Statics::NewProp_PitchMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASpiderCharacter_Statics::NewProp_PitchMax,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASpiderCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASpiderCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_ProceduralAnim,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASpiderCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASpiderCharacter_Statics::ClassParams = {
	&ASpiderCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASpiderCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASpiderCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASpiderCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ASpiderCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASpiderCharacter()
{
	if (!Z_Registration_Info_UClass_ASpiderCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASpiderCharacter.OuterSingleton, Z_Construct_UClass_ASpiderCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASpiderCharacter.OuterSingleton;
}
template<> PROCEDURALANIM_API UClass* StaticClass<ASpiderCharacter>()
{
	return ASpiderCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASpiderCharacter);
ASpiderCharacter::~ASpiderCharacter() {}
// End Class ASpiderCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASpiderCharacter, ASpiderCharacter::StaticClass, TEXT("ASpiderCharacter"), &Z_Registration_Info_UClass_ASpiderCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASpiderCharacter), 2342119993U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderCharacter_h_1895296002(TEXT("/Script/ProceduralAnim"),
	Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
