add_executable(bench_gcd bench_gcd.c)

target_compile_options(bench_gcd PRIVATE
    "-O3"
)

target_link_libraries(bench_gcd PRIVATE arithmos)
