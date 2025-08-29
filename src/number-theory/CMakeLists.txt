add_library(number_theory_obj OBJECT
    big_int.c
    gcd.c
    int128.c
    lcm.c
    power.c
    rational.c
)

target_include_directories(number_theory_obj PRIVATE ${PROJECT_SOURCE_DIR}/include/*)
