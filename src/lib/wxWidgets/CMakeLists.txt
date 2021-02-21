# Check if wxWidgets is installed in the system
# Use CMake's built-in script: FindwxWidgets

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(wxWidgets REQUIRED)

if (wxWidgets_FOUND)
    message(STATUS "wxWidgets libraries found: ${wxWidgets_LIBRARIES}")
    add_library(wxWidgets INTERFACE)
else()
    message(STATUS "wxWidgets not found.")
    message(STATUS "Downloading/installing wxWidgets in ${STAGED_INSTALL_PREFIX}")

    include(ExternalProject)

    ExternalProject_Add(
        wxWidgets

        GIT_REPOSITORY
        https://github.com/wxWidgets/wxWidgets.git

        GIT_TAG
        master

        UPDATE_COMMAND
        ""

        CMAKE_ARGS
        -DCMAKE_POLICY_DEFAULT_CMP0091:STRING=NEW
        -DCMAKE_MSVC_RUNTIME_LIBRARY:STRING=MultiThreaded$<$<CONFIG:Debug>:Debug>
        -DCMAKE_INSTALL_PREFIX=${STAGED_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
        -DCMAKE_CXX_EXTENSIONS=${CMAKE_CXX_EXTENSIONS}
        -DCMAKE_CXX_STANDARD_REQUIRED=${CMAKE_CXX_STANDARD_REQUIRED}
        -DwxBUILD_SHARED=OFF

        CMAKE_CACHE_ARGS
        -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}

        TEST_AFTER_INSTALL
        0

        DOWNLOAD_NO_PROGRESS
        1

        LOG_CONFIGURE
        1

        LOG_BUILD
        1

        LOG_INSTALL
        1
    )

    set(wxWidgets_ROOT_DIR ${STAGED_INSTALL_PREFIX})
    file(TO_NATIVE_PATH "${wxWidgets_ROOT_DIR}" wxWidgets_ROOT_DIR)
    set(wxWidgets_ROOT_DIR ${wxWidgets_ROOT_DIR} CACHE INTERNAL "wxWidgets installation dir")

    set(ENV_WX_CONFIG ${STAGED_INSTALL_PREFIX}/bin/wx-config)
    file(TO_NATIVE_PATH "${ENV_WX_CONFIG}" ENV_WX_CONFIG)
    set(ENV_WX_CONFIG ${ENV_WX_CONFIG} CACHE INTERNAL "wx-config dir")
endif()
