cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

if (WIN32)
    cmake_policy(SET CMP0091 NEW)
endif()

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

project(core LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF)
set(BUILD_STATIC_LIBS ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# A hack for CMake's FindwxWidgets script
if (DEFINED ENV_WX_CONFIG)
    set(ENV{WX_CONFIG} ${ENV_WX_CONFIG})
endif()

find_package(wxWidgets COMPONENTS core base REQUIRED)

set(CORE ${PROJECT_SOURCE_DIR}/core)
set(GUI ${PROJECT_SOURCE_DIR}/gui)
set(LIB ${PROJECT_SOURCE_DIR}/lib)
set(UTIL ${PROJECT_SOURCE_DIR}/util)

set(
    SOURCE
    ${CORE}/make.cpp
    ${CORE}/merge.cpp
    ${GUI}/about.cpp
    ${GUI}/app.cpp
    ${GUI}/listbox.cpp
    ${GUI}/menu.cpp
    ${GUI}/options.cpp
    ${GUI}/window.cpp
    ${LIB}/mini/ini.h
    ${LIB}/whereami/whereami.c
    ${UTIL}/utilities.cpp
)

include(${wxWidgets_USE_FILE})

if (APPLE)
    add_executable(DBgen MACOSX_BUNDLE ${SOURCE})

    # Set a custom plist file. It is needed for Mac OS Retina display
    set_target_properties(DBgen PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
else()
    # WIN32 is for Windows to find WinMain instead of a main function
    # This is ignored on other systems, so it works on all platforms

    add_executable(DBgen WIN32 ${SOURCE})
endif()

target_include_directories(
    DBgen
        PRIVATE ${wxWidgets_INCLUDE_DIRS}
        PRIVATE ${CORE}
        PRIVATE ${GUI}
        PRIVATE ${LIB}/mini
        PRIVATE ${LIB}/whereami
        PRIVATE ${UTIL}
)

target_link_libraries(
    DBgen
        ${wxWidgets_LIBRARIES}
)

