add_library(algebra_obj OBJECT gcd.c)

target_include_directories(algebra_obj PRIVATE ${PROJECT_SOURCE_DIR}/include)
