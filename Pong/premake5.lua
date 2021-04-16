project "Pong"
	kind "ConsoleApp"
	language "C"
	cdialect "C99"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.c",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.c"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{IncludeDir.cglm}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.stb_image}",
	}		

	filter "system:windows"
		systemversion "latest"

		defines { }
		
		links
		{
			"cglm",
			"glfw",
			"glad",
			"opengl32.lib"
		}
		
	filter "system:linux"
		systemversion "latest"
			
		links
		{
			"cglm",
			"glfw",
			"glad"
		}
		
		linkoptions
		{
			"-std=c99",
			"-pthread",
			"-lm",
			"-Wl,--no-as-needed",
			"-ldl",
			"-lGL",
			"-lXmu",
			"-lX11"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
