-- ~/Source/Kreckanism/premake5.lua

project "Kreckanism"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files { "**.h", "**.cpp" }

    includedirs
    {
        "%{wks.location}/Source/",
        "%{wks.location}/ThirdParty/glad/include",
        "%{wks.location}/ThirdParty/glfw/include",
        "%{wks.location}/ThirdParty/glm",
        "%{wks.location}/ThirdParty/imgui",
        "%{wks.location}/ThirdParty/fmt/include",
        "%{wks.location}/ThirdParty/stb"
    }

    filter "system:linux"
        includedirs { "/opt/fbxsdk/include" }
        libdirs { "/opt/fbxsdk/lib/gcc/x64/debug" }
        links { "glfw", "glad", "imgui", "fmt", "GL", "rt", "m", "dl", "X11", "pthread", "fbxsdk", "xml2" }

    filter "system:windows"
        includedirs { "D:/Program Files/Autodesk/FBX/FBX SDK/2020.2.1/include" }
        libdirs { "D:/Program Files/Autodesk/FBX/FBX SDK/2020.2.1/lib/vs2019/x64/debug" }
        links { "glfw", "glad", "imgui", "opengl32", "libfbxsdk-md", "libxml2-md", "zlib-md" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        optimize "On"
