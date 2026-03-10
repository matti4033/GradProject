// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralAnim/AnimNode_SpiderIK.h"
#include "ProceduralAnim/SpiderLeg.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnimNode_SpiderIK() {}

// Begin Cross Module References
ANIMGRAPHRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_SkeletalControlBase();
PROCEDURALANIM_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_SpiderIK();
PROCEDURALANIM_API UScriptStruct* Z_Construct_UScriptStruct_FSpiderLeg();
UPackage* Z_Construct_UPackage__Script_ProceduralAnim();
// End Cross Module References

// Begin ScriptStruct FAnimNode_SpiderIK
static_assert(std::is_polymorphic<FAnimNode_SpiderIK>() == std::is_polymorphic<FAnimNode_SkeletalControlBase>(), "USTRUCT FAnimNode_SpiderIK cannot be polymorphic unless super FAnimNode_SkeletalControlBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_AnimNode_SpiderIK;
class UScriptStruct* FAnimNode_SpiderIK::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_AnimNode_SpiderIK.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_AnimNode_SpiderIK.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FAnimNode_SpiderIK, (UObject*)Z_Construct_UPackage__Script_ProceduralAnim(), TEXT("AnimNode_SpiderIK"));
	}
	return Z_Registration_Info_UScriptStruct_AnimNode_SpiderIK.OuterSingleton;
}
template<> PROCEDURALANIM_API UScriptStruct* StaticStruct<FAnimNode_SpiderIK>()
{
	return FAnimNode_SpiderIK::StaticStruct();
}
struct Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "AnimNode_SpiderIK.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Legs_MetaData[] = {
		{ "Category", "AnimNode_SpiderIK" },
		{ "ModuleRelativePath", "AnimNode_SpiderIK.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Legs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Legs;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAnimNode_SpiderIK>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::NewProp_Legs_Inner = { "Legs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FSpiderLeg, METADATA_PARAMS(0, nullptr) }; // 1474427033
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::NewProp_Legs = { "Legs", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FAnimNode_SpiderIK, Legs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Legs_MetaData), NewProp_Legs_MetaData) }; // 1474427033
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::NewProp_Legs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::NewProp_Legs,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_ProceduralAnim,
	Z_Construct_UScriptStruct_FAnimNode_SkeletalControlBase,
	&NewStructOps,
	"AnimNode_SpiderIK",
	Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::PropPointers),
	sizeof(FAnimNode_SpiderIK),
	alignof(FAnimNode_SpiderIK),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_SpiderIK()
{
	if (!Z_Registration_Info_UScriptStruct_AnimNode_SpiderIK.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_AnimNode_SpiderIK.InnerSingleton, Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_AnimNode_SpiderIK.InnerSingleton;
}
// End ScriptStruct FAnimNode_SpiderIK

// Begin Registration
struct Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_AnimNode_SpiderIK_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FAnimNode_SpiderIK::StaticStruct, Z_Construct_UScriptStruct_FAnimNode_SpiderIK_Statics::NewStructOps, TEXT("AnimNode_SpiderIK"), &Z_Registration_Info_UScriptStruct_AnimNode_SpiderIK, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FAnimNode_SpiderIK), 3482327683U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_AnimNode_SpiderIK_h_241260781(TEXT("/Script/ProceduralAnim"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_AnimNode_SpiderIK_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_AnimNode_SpiderIK_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
