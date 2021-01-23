workspace "Fall-ENG-Down"
	location "..\\build\\"

	targetdir "%{wks.location}\\bin\\%{cfg.buildcfg}\\"
	objdir "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}\\"
	buildlog "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}.log"

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "mbcs"
	architecture "x86"
	warnings "extra"

	includedirs {
		"..\\src\\",
	}

	syslibdirs {
		"..\\deps\\DxLib\\",
	}

	buildoptions {
		"/Zm200",
		"/utf-8",
		"/std:c++latest",
		"/bigobj",
	}

	flags {
		"noincrementallink",
		"no64bitchecks",
		"shadowedvariables",
		"undefinedidentifiers",
		"multiprocessorcompile",
	}

	defines {
		"NOMINMAX",
		"WIN32_LEAN_AND_MEAN",
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
	}

	platforms {
		"x86",
	}

	configurations {
		"Release",
		"Debug",
	}
	
	configuration "Release"
		defines "NDEBUG"
		optimize "full"
		runtime "release"
		symbols "off"

	configuration "Debug"
		defines "DEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"

	project "game"
		targetname "Fall-ENG-Down"
		pchheader "stdafx.hpp"
		pchsource "../src/stdafx.cpp"
		forceincludes "stdafx.hpp"

		language "c++"
		kind "windowedapp"
		warnings "off"

		links {
			"DxLib.lib",
		}
		
		files {
			"..\\src\\**",
		}

		includedirs {
			"..\\deps\\DxLib\\",
		}