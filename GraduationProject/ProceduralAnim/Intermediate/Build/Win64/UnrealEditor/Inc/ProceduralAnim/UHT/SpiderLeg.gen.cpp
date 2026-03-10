// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralAnim/SpiderLeg.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSpiderLeg() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
PROCEDURALANIM_API UScriptStruct* Z_Construct_UScriptStruct_FSpiderLeg();
UPackage* Z_Construct_UPackage__Script_ProceduralAnim();
// End Cross Module References

// Begin ScriptStruct FSpiderLeg
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_SpiderLeg;
class UScriptStruct* FSpiderLeg::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_SpiderLeg.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_SpiderLeg.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FSpiderLeg, (UObject*)Z_Construct_UPackage__Script_ProceduralAnim(), TEXT("SpiderLeg"));
	}
	return Z_Registration_Info_UScriptStruct_SpiderLeg.OuterSingleton;
}
template<> PROCEDURALANIM_API UScriptStruct* StaticStruct<FSpiderLeg>()
{
	return FSpiderLeg::StaticStruct();
}
struct Z_Construct_UScriptStruct_FSpiderLeg_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UpperBone_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MidBone_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TipBone_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentFootPos_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DesiredFootPos_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RestOffset_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PoleOffset_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FootGroundOffset_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UpperMaxAngle_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MidMaxAngle_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TipMaxAngle_MetaData[] = {
		{ "Category", "SpiderLeg" },
		{ "ModuleRelativePath", "SpiderLeg.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FNamePropertyParams NewProp_UpperBone;
	static const UECodeGen_Private::FNamePropertyParams NewProp_MidBone;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TipBone;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CurrentFootPos;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DesiredFootPos;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RestOffset;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PoleOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FootGroundOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_UpperMaxAngle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MidMaxAngle;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TipMaxAngle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSpiderLeg>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_UpperBone = { "UpperBone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, UpperBone), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UpperBone_MetaData), NewProp_UpperBone_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_MidBone = { "MidBone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, MidBone), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MidBone_MetaData), NewProp_MidBone_MetaData) };
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_TipBone = { "TipBone", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, TipBone), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TipBone_MetaData), NewProp_TipBone_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_CurrentFootPos = { "CurrentFootPos", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, CurrentFootPos), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentFootPos_MetaData), NewProp_CurrentFootPos_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_DesiredFootPos = { "DesiredFootPos", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, DesiredFootPos), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DesiredFootPos_MetaData), NewProp_DesiredFootPos_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_RestOffset = { "RestOffset", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, RestOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RestOffset_MetaData), NewProp_RestOffset_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_PoleOffset = { "PoleOffset", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, PoleOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PoleOffset_MetaData), NewProp_PoleOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_FootGroundOffset = { "FootGroundOffset", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, FootGroundOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FootGroundOffset_MetaData), NewProp_FootGroundOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_UpperMaxAngle = { "UpperMaxAngle", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, UpperMaxAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UpperMaxAngle_MetaData), NewProp_UpperMaxAngle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_MidMaxAngle = { "MidMaxAngle", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, MidMaxAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MidMaxAngle_MetaData), NewProp_MidMaxAngle_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_TipMaxAngle = { "TipMaxAngle", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSpiderLeg, TipMaxAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TipMaxAngle_MetaData), NewProp_TipMaxAngle_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSpiderLeg_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_UpperBone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_MidBone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_TipBone,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_CurrentFootPos,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_DesiredFootPos,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_RestOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_PoleOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_FootGroundOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_UpperMaxAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_MidMaxAngle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewProp_TipMaxAngle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpiderLeg_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSpiderLeg_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_ProceduralAnim,
	nullptr,
	&NewStructOps,
	"SpiderLeg",
	Z_Construct_UScriptStruct_FSpiderLeg_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpiderLeg_Statics::PropPointers),
	sizeof(FSpiderLeg),
	alignof(FSpiderLeg),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpiderLeg_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FSpiderLeg_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FSpiderLeg()
{
	if (!Z_Registration_Info_UScriptStruct_SpiderLeg.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_SpiderLeg.InnerSingleton, Z_Construct_UScriptStruct_FSpiderLeg_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_SpiderLeg.InnerSingleton;
}
// End ScriptStruct FSpiderLeg

// Begin Registration
struct Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderLeg_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FSpiderLeg::StaticStruct, Z_Construct_UScriptStruct_FSpiderLeg_Statics::NewStructOps, TEXT("SpiderLeg"), &Z_Registration_Info_UScriptStruct_SpiderLeg, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FSpiderLeg), 1474427033U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderLeg_h_642372471(TEXT("/Script/ProceduralAnim"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderLeg_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderLeg_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
