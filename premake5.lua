workspace "Pong"
    architecture "x64"
    startproject "Pong"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["cglm"] = "%{wks.location}/Pong/vendor/cglm/include"
IncludeDir["glfw"] = "%{wks.location}/Pong/vendor/glfw/include"
IncludeDir["glad"] = "%{wks.location}/Pong/vendor/glad/include"
IncludeDir["stb_image"] = "%{wks.location}/Pong/vendor/stb_image"

group "Dependencies"
	include "Pong/vendor/cglm"
	include "Pong/vendor/glfw"
	include "Pong/vendor/glad"
group ""

include "Pong"
