cmake_minimum_required(VERSION 3.16)
project(Arithmos LANGUAGES C)

# Specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Options
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_BENCH "Build benchmarks" ON)
option(BUILD_DOCS "Build documentation" OFF)    # Optional

# Include directories for public headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add subdirectories with modules
add_subdirectory(src)

# Build tests if enabled
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# Build benchmarks if enabled
if(BUILD_BENCH)
    add_subdirectory(bench)
endif()

# Build docs if enabled
if(BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    add_subdirectory(docs)
endif()
