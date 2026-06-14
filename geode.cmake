# This file is used to fetch the Geode SDK
# It is a simplified version of the standard Geode geode.cmake

if (NOT DEFINED GEODE_SDK_VERSION)
    set(GEODE_SDK_VERSION "v1.0.0")
endif()

if (NOT DEFINED GEODE_SDK_PATH)
    set(GEODE_SDK_PATH "${CMAKE_CURRENT_BINARY_DIR}/geode-sdk")
endif()

if (NOT EXISTS "${GEODE_SDK_PATH}")
    message(STATUS "Fetching Geode SDK...")
    execute_process(
        COMMAND git clone --depth 1 --branch ${GEODE_SDK_VERSION} https://github.com/geode-sdk/geode.git "${GEODE_SDK_PATH}"
        RESULT_VARIABLE GIT_CLONE_RESULT
    )
    if (NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone Geode SDK")
    endif()
endif()

# The Geode SDK handles the rest of the setup when included
include("${GEODE_SDK_PATH}/loader/CMakeLists.txt")
