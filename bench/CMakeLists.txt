find_package(benchmark REQUIRED)


add_library(bench-lib INTERFACE)
target_link_libraries(bench-lib INTERFACE arithmos benchmark cxx-compile-flags pthread)


add_subdirectory(numeric)
