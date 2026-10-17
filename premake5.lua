workspace "Dungeon-Crawler"
    architecture "x64"
    configurations { "Debug", "Release" }


project "Dungeon-Crawler"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    location "Dungeon-Crawler"

    targetdir "bin/Dungeon-Crawler/%{cfg.buildcfg}"
    objdir "bin-int/Dungeon-Crawler/%{cfg.buildcfg}"

    files {
        "Dungeon-Crawler/src/**.h",
        "Dungeon-Crawler/src/**.cpp"
    }

    -- Your own headers
    includedirs {
        "Dungeon-Crawler/src"
    }


    ------------------------------------------------------------
    -- Windows
    ------------------------------------------------------------

    filter "system:windows"

        includedirs {
            "Dependencies/SFML3-win/include"
        }

        libdirs {
            "Dependencies/SFML3-win/lib"
        }

        systemversion "latest"


    filter { "system:windows", "configurations:Debug" }

        symbols "On"

        links {
            "sfml-graphics-d",
            "sfml-window-d",
            "sfml-system-d",
            "sfml-audio-d"
        }


    filter { "system:windows", "configurations:Release" }

        optimize "On"

        links {
            "sfml-graphics",
            "sfml-window",
            "sfml-system",
            "sfml-audio"
        }


    ------------------------------------------------------------
    -- macOS
    ------------------------------------------------------------

    filter "system:macosx"

        includedirs {
            "Dependencies/SFML3-macos/include"
        }

        libdirs {
            "Dependencies/SFML3-macos/lib"
        }

        links {
            "sfml-graphics",
            "sfml-window",
            "sfml-system",
            "sfml-audio"
        }


    filter { "system:macosx", "configurations:Debug" }

        symbols "On"


    filter { "system:macosx", "configurations:Release" }

        optimize "On"


    ------------------------------------------------------------
    -- macOS dynamic library search path
    ------------------------------------------------------------

    filter "system:macosx"

        linkoptions {
            "-Wl,-rpath,@loader_path/../../../Dependencies/SFML3-macos/lib"
        }


    ------------------------------------------------------------
    -- Reset filters
    ------------------------------------------------------------

    filter {}