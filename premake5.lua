outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
workspace "PBD"
	architecture "x86_64"
	configurations {
		"Debug", 
		"Release"
	}
	ignoredefaultlibraries {
		"MSVCRT",
		"MSVCRTd"
	}

	flags {
		"MultiProcessorCompile",
	}

project "PoissonBinomialDistribution"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
	targetdir ("%{wks.location}/bin/" .. outputDir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin/intermediates/" .. outputDir .. "/%{prj.name}")

	files { 
		"src/**.hpp", 
		"src/**.cpp",

		"include/**.hpp",
		"Lud_Utils/include/**.hpp",
	}

	includedirs {
		"src",
		"include",
		"Lud_Utils/include/"
	}

	filter "configurations:Debug"
		defines { 
			"CONF_DEBUG"
		}
		runtime "debug"
		symbols "On"

	filter "configurations:Release"
		defines { 
			"CONF_RELEASE"
		}
		runtime "release"
		symbols "Off"
		optimize "On"