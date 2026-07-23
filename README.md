## License
This project is licensed under the GNU General Public License v3.0 (GPL-3.0) - see the [LICENSE](LICENSE) file for details.


This project is the implementation of High-level Raylib API that adds an abstraction layer between raylib and your game.
This will have many built-in features and will act like pretty much a game engine that has a core architecture to make a game. For instance, adding objects, animations, levels, basic physics, particle vfx, resource handling etc.

Currently, Only available for Linux; The original CMake file is used to build the static library

To use this in your project, just copy the CMake code below with the header available in the include/ directory and place them right next to your project:


============CMAKE CODE FOR BUILDING YOUR GAME=================
project(TickTockAction LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 26)

add_executable(TickTockAction main.cpp)                         # replace main.cpp with all the source files in your project

set(ENGINE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/libraylib_api.a")
target_link_libraries(TickTockAction PRIVATE ${ENGINE_LIB})


# === Platform Detection ===
if (MINGW OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "🔧 Building for Windows using MinGW")

    # Adjust these paths to where your Raylib for Windows is built
    set(RAYLIB_LIB_PATH "/home/mfaseeh/raylib/build-mingw/raylib/libraylib.a")
    set(RAYLIB_INCLUDE_PATH "/home/mfaseeh/raylib/src")

    if (NOT EXISTS ${RAYLIB_LIB_PATH})
        message(FATAL_ERROR "❌ Raylib static library not found at: ${RAYLIB_LIB_PATH}")
    endif()

    target_link_libraries(TickTockAction PRIVATE ${RAYLIB_LIB_PATH})
    target_include_directories(TickTockAction PRIVATE ${RAYLIB_INCLUDE_PATH})

    # Link required Windows libraries
    target_link_libraries(TickTockAction PRIVATE winmm gdi32 opengl32 m)

else()
    message(STATUS "🐧 Building for Linux")

    target_link_libraries(TickTockAction PRIVATE raylib m)
    target_include_directories(TickTockAction PRIVATE ${raylib_INCLUDE_DIRS})
endif()

include(CTest)
enable_testing()


