using UnrealBuildTool;

public class ProceduralAnimEditor : ModuleRules
{
    public ProceduralAnimEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "AnimGraph",
            "BlueprintGraph",
            "AnimGraphRuntime",
            "ProceduralAnim"
        });

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "UnrealEd",
                "SlateCore",
                "Slate"
            });
        }

        PublicIncludePaths.Add("$(ModuleDir)/../ProceduralAnim");
    }
}