namespace UnrealBuildTool.Rules
{
    using System.IO; // ToDo: Replace with standard mechenism
 
    public class Rudder : ModuleRules
    {
		private string ModulePath
		{
            get { return  ModuleDirectory; }
        }

        private string SDKPath
		{
			get { return Path.GetFullPath(Path.Combine(ModulePath, "../../3DRudderSDK/")); }
		}		
		
        public Rudder(TargetInfo Target)
        {
            PCHUsage = PCHUsageMode.NoSharedPCHs;
 
            // ... add public include paths required here ...
            PublicIncludePaths.AddRange( new string[] {
                "Rudder/Public",
            });
 
            // ... add other private include paths required here ...
            PrivateIncludePaths.AddRange( new string[] {
                "Rudder/Private",
            });
 
            // ... add other public dependencies that you statically link with here ...
            PublicDependencyModuleNames.AddRange( new string[] { 
                "Core", 
                "CoreUObject",      // Provides Actors and Structs
                "Engine",           // Used by Actor
                "Slate",            // Used by InputDevice to fire bespoke FKey events
                "SlateCore",
                "Projects",
                "InputCore",        // Provides LOCTEXT and other Input features
                "InputDevice",      // Provides IInputInterface
            });
 
            // ... add private dependencies that you statically link with here ...
            PrivateDependencyModuleNames.AddRange( new string[] {
            });
 
            // ... add any modules that your module loads dynamically here ...
            DynamicallyLoadedModuleNames.AddRange( new string[] { 
            });
 
            LoadThirdPartyLibraries(Target);
        }
 
        public bool LoadThirdPartyLibraries(TargetInfo Target)
        {
            bool isLibrarySupported = false;
 
            string ArchitecturePath = "";
 
            // When you are building for Win64
            if (Target.Platform == UnrealTargetPlatform.Win64 &&
                WindowsPlatform.Compiler == WindowsCompiler.VisualStudio2015)
            {
                ArchitecturePath = "x64\\Static";
 
                isLibrarySupported = true;
            }
            // When you are building for Win32
            else if (Target.Platform == UnrealTargetPlatform.Win32 &&
                WindowsPlatform.Compiler == WindowsCompiler.VisualStudio2015)
            {
                ArchitecturePath = "Win32\\Static";
 
                isLibrarySupported = true;
            }
            // Add mac/linux/mobile support in much the same way
 
            // If the current build architecture was supported by the above if statements
            if (isLibrarySupported)
            {
                // Add the architecture spacific path to the library files
                PublicAdditionalLibraries.Add(Path.Combine(SDKPath, "Lib", ArchitecturePath, "3DRudderSDK.lib"));
                // Add a more generic path to the include header files
                PublicIncludePaths.Add(Path.Combine(SDKPath, "Include"));
            }
 
            // Defination lets us know whether we successfully found our library!
            Definitions.Add(string.Format("WITH_MY_LIBRARY_PATH_USE={0}", isLibrarySupported ? 1 : 0));
 
            return isLibrarySupported;
        }
    }
}