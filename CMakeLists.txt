cmake_minimum_required(VERSION 3.20)

project(
    AudioPlaybackConnector 
    VERSION 1.3.1.0
    LANGUAGES CXX
)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)
set(CMAKE_SKIP_INSTALL_RULES ON)

configure_file(
    "${PROJECT_SOURCE_DIR}/AudioPlaybackConnector.rc.in"
    "${PROJECT_SOURCE_DIR}/AudioPlaybackConnector.rc"
)

add_executable(AudioPlaybackConnector
    "${PROJECT_SOURCE_DIR}/AudioPlaybackConnector.cpp"
    "${PROJECT_SOURCE_DIR}/AudioPlaybackConnector.manifest"
    "${PROJECT_SOURCE_DIR}/AudioPlaybackConnector.rc"
)

# Brings WIL in
include(FetchContent)

FetchContent_Declare(
    usylibpp
    GIT_REPOSITORY https://github.com/usyless/usylibpp.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(usylibpp)

target_link_libraries(AudioPlaybackConnector PRIVATE usylibpp::usylibpp)

target_compile_features(AudioPlaybackConnector PRIVATE
    cxx_std_23
)

set_property(TARGET AudioPlaybackConnector PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

target_precompile_headers(AudioPlaybackConnector PRIVATE
    "${PROJECT_SOURCE_DIR}/pch.h"
)

target_link_options(AudioPlaybackConnector PRIVATE
    /SUBSYSTEM:WINDOWS

    $<$<CONFIG:Debug>:
        "/DEBUG"
    >
    $<$<CONFIG:Release>:
        "/OPT:ICF"
        "/OPT:REF"
        # "/NODEFAULTLIB:libucrt.lib"
    >
)

target_link_libraries(AudioPlaybackConnector PRIVATE
    # $<$<CONFIG:Release>:
    #     ucrt.lib
    # >
    comctl32.lib
    shlwapi.lib
)


target_compile_definitions(AudioPlaybackConnector PRIVATE
    _WINDOWS
    UNICODE
    _UNICODE

    $<$<CONFIG:Debug>:
        _DEBUG
    >
    $<$<CONFIG:Release>:
        NDEBUG
    >
)

target_compile_options(AudioPlaybackConnector PRIVATE
    /EHsc
    /W4
    /GR
    /Zc:preprocessor
    /await:strict
    /permissive-
    /WX
    /sdl

    # /Zi
    # /DEBUG
    $<$<CONFIG:Debug>:
        /RTC1
        /Zi
        /Od
    >

    $<$<CONFIG:Release>:
        /O2
        /Ob2
        /Oi
        /Oy
        /Gy
    >
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set_property(TARGET AudioPlaybackConnector PROPERTY
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    )
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/builddebug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/builddebug")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/builddebug")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build")
