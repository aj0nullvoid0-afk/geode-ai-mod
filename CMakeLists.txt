cmake_minimum_required(VERSION 3.21)
project(GeoAI)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Geode
include(${CMAKE_CURRENT_SOURCE_DIR}/geode.cmake)

# Add source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

# Create the mod
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Link Geode
target_link_libraries(${PROJECT_NAME} geode-sdk)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
