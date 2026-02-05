cmake_minimum_required(VERSION 3.20)

project(
    AudioPlaybackConnector 
    VERSION 1.3.1.0
    LANGUAGES CXX
)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)
set(CMAKE_SKIP_INSTALL_RULES ON)

# Use later to put version in directly
# configure_file(
#     "${PROJECT_SOURCE_DIR}/AudioPlaybackConnector.rc.in"
#     "${CMAKE_CURRENT_BINARY_DIR}/AudioPlaybackConnector.rc"
# )

add_executable(AudioPlaybackConnector
    "${PROJECT_SOURCE_DIR}/AudioPlaybackConnector.cpp"
)

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

target_compile_options(AudioPlaybackConnector PRIVATE
    /EHsc
    /W4
    /GR
    /Zc:preprocessor
    /await:strict

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
