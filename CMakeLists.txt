cmake_minimum_required(VERSION 3.10.0)
project(raylib_api VERSION 0.1.0 LANGUAGES C CXX)

add_executable(raylib_api  main.cpp)

# === Platform Detection ===
if (MINGW OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "🔧 Building for Windows using MinGW")

    # Adjust these paths to where your Raylib for Windows is built
    set(RAYLIB_LIB_PATH "/home/mfaseeh/raylib/build-mingw/raylib/libraylib.a")
    set(RAYLIB_INCLUDE_PATH "/home/mfaseeh/raylib/src")

    if (NOT EXISTS ${RAYLIB_LIB_PATH})
        message(FATAL_ERROR "❌ Raylib static library not found at: ${RAYLIB_LIB_PATH}")
    endif()

    target_link_libraries(raylib_api PRIVATE ${RAYLIB_LIB_PATH})
    target_include_directories(raylib_api PRIVATE ${RAYLIB_INCLUDE_PATH})

    # Link required Windows libraries
    target_link_libraries(raylib_api PRIVATE winmm gdi32 opengl32 m)

else()
    message(STATUS "🐧 Building for Linux")

    target_link_libraries(raylib_api PRIVATE raylib m)
    target_include_directories(raylib_api PRIVATE ${raylib_INCLUDE_DIRS})
endif()

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
