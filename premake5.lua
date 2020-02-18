
workspace "Example"
architecture "x64"
configurations { "Debug", "Release" }
location "build"
toolset "clang"

project "Test"
location "build"
kind "ConsoleApp"
language "C++"
targetdir "bin/%{cfg.buildcfg}"
cppdialect "C++17"

files 
{
    "inc/**.hpp", 
    "src/**.cpp"
}

includedirs 
{
    "inc",
    "src"
}

filter "configurations:Debug"
    defines {"DEBUG"}
    symbols "On"

filter "configurations:Release"
    defines {"NDEBUG"}
    optimize "On"

