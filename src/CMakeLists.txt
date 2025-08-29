# Collect all source files from submodules
# add_subdirectory(algebra)
add_subdirectory(geometry)
add_subdirectory(number-theory)

# Create a static library from all collected sources
add_library(arithmos STATIC
    # $<TARGET_OBJECTS:algebra_obj>
    $<TARGET_OBJECTS:geometry_obj>
    $<TARGET_OBJECTS:number_theory_obj>
)

add_library(test_compile_options INTERFACE)

set(gcc_like_c "$<COMPILE_LANG_AND_ID:C,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_c "$<COMPILE_LANG_AND_ID:C,MSVC>")

target_compile_options(test_compile_options INTERFACE "$<${gcc_like_c}:-fdiagnostics-color=always;-Wall;-Wextra;-Werror;-Wno-error=unused-result;-Wpedantic;-Wshadow;-Wconversion;-Wunused;-Wnull-dereference;-Wformat=2;-fstack-protector-all;-D_FORTIFY_SOURCE=2;-O;-fsanitize=address>;-pg"
"$<${msvc_c}:/W4;/WX;/permissive-;/analyze;/GS;/sdl>")

target_link_options(test_compile_options INTERFACE "$<${gcc_like_c}:-fdiagnostics-color=always;-Wall;-Wextra;-Werror;-Wno-error=unused-result;-Wpedantic;-Wshadow;-Wconversion;-Wunused;-Wnull-dereference;-Wformat=2;-fstack-protector-all;-D_FORTIFY_SOURCE=2;-O;-fsanitize=address>;-pg"
"$<${msvc_c}:/W4;/WX;/permissive-;/analyze;/GS;/sdl>")

target_link_libraries(arithmos PUBLIC test_compile_options)


# Public include path for consumers of the library
target_include_directories(arithmos PUBLIC ${PROJECT_SOURCE_DIR}/include)
