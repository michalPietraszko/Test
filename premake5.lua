--pramake.lua

workspace "Luna"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
--IncludeDir["GLFW"] = "Luna/vendor/GLFW/include"

--include "Luna/vendor/GLFW"

project "DynLib"
    location "DynLib"
    kind "SharedLib"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

--    pchheader "lnpch.h"
--    pchsource "Luna/src/lnpch.cpp"

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/"
    } 

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Client")
        }
    
    filter "configurations:Debug"
        defines "LN_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        symbols "On"

project "Client"
    location "Client"
    kind "ConsoleApp"    
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        "DynLib/src"
    }

    links
    {
        "DynLib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "LN_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "LN_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "LN_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "LN_DIST"
        symbols "On"
