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
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USpiderMovementComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
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
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
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
DEFINE_VTABLE_PTR_HELPER_CTOR(USpiderMovementComponent);
USpiderMovementComponent::~USpiderMovementComponent() {}
// End Class USpiderMovementComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderMovementComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USpiderMovementComponent, USpiderMovementComponent::StaticClass, TEXT("USpiderMovementComponent"), &Z_Registration_Info_UClass_USpiderMovementComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USpiderMovementComponent), 3041907852U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderMovementComponent_h_566938722(TEXT("/Script/ProceduralAnim"),
	Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderMovementComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skola_GradProject_GraduationProject_ProceduralAnim_Source_ProceduralAnim_SpiderMovementComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
