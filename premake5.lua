workspace "calc"
	configurations { "release", "debug" }

include "vendor/lua"

project "calc"
	kind "ConsoleApp"
	language "C"
	targetdir "bin"

	includedirs "lua/src"
	
	files { "src/**.h", "src/**.c" }

	links { "lua" }

	filter "configurations:Debug"
		defines { "DEBUG=1", "RELEASE=0" }
		symbols "On"

 	filter "configurations:Release"
		defines { "DEBUG=0", "RELEASE=1" }
		optimize "On"

	filter "system:linux or bsd or hurd or aix or solaris or haiku"
		links { "m", "dl" }
