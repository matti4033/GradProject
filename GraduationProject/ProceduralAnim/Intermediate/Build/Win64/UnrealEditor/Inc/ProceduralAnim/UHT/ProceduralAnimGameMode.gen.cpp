// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ProceduralAnim/ProceduralAnimGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProceduralAnimGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
PROCEDURALANIM_API UClass* Z_Construct_UClass_AProceduralAnimGameMode();
PROCEDURALANIM_API UClass* Z_Construct_UClass_AProceduralAnimGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProceduralAnim();
// End Cross Module References

// Begin Class AProceduralAnimGameMode
void AProceduralAnimGameMode::StaticRegisterNativesAProceduralAnimGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProceduralAnimGameMode);
UClass* Z_Construct_UClass_AProceduralAnimGameMode_NoRegister()
{
	return AProceduralAnimGameMode::StaticClass();
}
struct Z_Construct_UClass_AProceduralAnimGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ProceduralAnimGameMode.h" },
		{ "ModuleRelativePath", "ProceduralAnimGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProceduralAnimGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AProceduralAnimGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_ProceduralAnim,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralAnimGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProceduralAnimGameMode_Statics::ClassParams = {
	&AProceduralAnimGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProceduralAnimGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AProceduralAnimGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProceduralAnimGameMode()
{
	if (!Z_Registration_Info_UClass_AProceduralAnimGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProceduralAnimGameMode.OuterSingleton, Z_Construct_UClass_AProceduralAnimGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProceduralAnimGameMode.OuterSingleton;
}
template<> PROCEDURALANIM_API UClass* StaticClass<AProceduralAnimGameMode>()
{
	return AProceduralAnimGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProceduralAnimGameMode);
AProceduralAnimGameMode::~AProceduralAnimGameMode() {}
// End Class AProceduralAnimGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_ProceduralAnimGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProceduralAnimGameMode, AProceduralAnimGameMode::StaticClass, TEXT("AProceduralAnimGameMode"), &Z_Registration_Info_UClass_AProceduralAnimGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProceduralAnimGameMode), 990800328U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_ProceduralAnimGameMode_h_1695706951(TEXT("/Script/ProceduralAnim"),
	Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_ProceduralAnimGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_ProceduralAnimGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
