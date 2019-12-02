--pramake.lua

workspace "Test"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--include "Luna/vendor/GLFW"
startproject "Client"

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
        "%{prj.name}/**.hpp",
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
        symbols "On"

    filter "configurations:Release"
        symbols "Off"

project "Client"
    location "Client"
    kind "ConsoleApp"    
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.hpp",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        "DynLib/"
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
        symbols "On"

    filter "configurations:Release"
        symbols "Off"

