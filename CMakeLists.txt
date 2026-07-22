cmake_minimum_required(VERSION 3.10.0)
project(raylib_api VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 26)

# 1. Change from add_executable to add_library with STATIC
# Replace main.cpp with the actual source files of your API (e.g., src/engine.cpp)
add_library(raylib_api STATIC 
    src/animation.cpp
    src/visual.cpp
)

# 2. Expose your API's own header directory to the games using it
# Replace "include" with the actual path to your API's header directory
target_include_directories(raylib_api PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if (MINGW OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "🔧 Building for Windows using MinGW")

    set(RAYLIB_LIB_PATH "/home/mfaseeh/raylib/build-mingw/raylib/libraylib.a")
    set(RAYLIB_INCLUDE_PATH "/home/mfaseeh/raylib/src")

    if (NOT EXISTS ${RAYLIB_LIB_PATH})
        message(FATAL_ERROR "❌ Raylib static library not found at: ${RAYLIB_LIB_PATH}")
    endif()

    # Changed linking to PUBLIC/INTERFACE where appropriate so your game inherits them
    target_link_libraries(raylib_api PUBLIC ${RAYLIB_LIB_PATH})
    target_include_directories(raylib_api PUBLIC ${RAYLIB_INCLUDE_PATH})

    target_link_libraries(raylib_api PUBLIC winmm gdi32 opengl32 m)

else()
    message(STATUS "🐧 Building for Linux")

    # Linked as PUBLIC so any game linking raylib_api also links raylib and math
    target_link_libraries(raylib_api PUBLIC raylib m)
endif()

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)