target_include_directories(arithmos
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(abs)
add_subdirectory(gcd)
add_subdirectory(lcm)
add_subdirectory(multiply)
add_subdirectory(power)
