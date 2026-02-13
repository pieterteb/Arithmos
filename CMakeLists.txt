cmake_minimum_required(VERSION 3.16)

project(Arithmos
    VERSION 0.0.0
    LANGUAGES C
)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_VERBOSE_MAKEFILE OFF CACHE BOOL "Always show compile commands" FORCE)


add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ..
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(release
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ..
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(tests
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Tests ..
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(bench
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Bench ..
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)


if(CMAKE_BUILD_TYPE STREQUAL "Tests")
    enable_testing()
    add_subdirectory(tests)
elseif(CMAKE_BUILD_TYPE STREQUAL "Bench")
    add_subdirectory(bench)
endif()

add_subdirectory(src)
