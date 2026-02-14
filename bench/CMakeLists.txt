find_package(benchmark REQUIRED)

add_library(google_benchmark STATIC IMPORTED GLOBAL)
set_target_properties(google_benchmark PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libbenchmark.a"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include"
    INTERFACE_LINK_LIBRARIES "stdc++"
)


add_library(bench-lib INTERFACE)
target_link_libraries(bench-lib INTERFACE arithmos google_benchmark pthread)


# Propagate C++ compile flags to bench executables
target_compile_options(bench-lib INTERFACE ${CXX_BASE_COMPILE_FLAGS})


add_subdirectory(numeric)
