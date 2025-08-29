add_library(geometry_obj OBJECT point_2d.c)

target_include_directories(geometry_obj PRIVATE ${PROJECT_SOURCE_DIR}/include)
