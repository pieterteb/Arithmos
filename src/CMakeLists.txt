add_library(arithmos STATIC)

target_include_directories(arithmos
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)


set(C_BASE_COMPILE_FLAGS
    -std=c11

    # Diagnostic flags
    -fdiagnostics-color=always

    # Warning flags
    -Wno-unknown-warning-option

    -Werror
    -Wpedantic
    -Wall
    -Wextra
    -Wdouble-promotion
    -Wformat=2
    -Wformat-signedness
    -Wnull-dereference
    -Winit-self
    -Wmissing-include-dirs
    -Wunused
    -Wuseless-cast
    -Wuninitialized
    -Wstrict-overflow=2
    -Wduplicated-branches
    -Wduplicated-cond
    -Wzero-as-null-pointer-constant
    -Wshadow
    -Wundef
    -Wbad-function-cast
    -Wcast-qual
    -Wcast-align
    -Wwrite-strings
    -Wconversion
    -Wstrict-prototypes
    -Wmissing-parameter-name
    -Wpacked
    -Wredundant-decls
    -Wnested-externs
    -Winline
    -Winvalid-utf8
)

set(CXX_BASE_COMPILE_FLAGS
    -std=c++20

    # Diagnostic flags
    -fdiagnostics-color=always

    # Warning flags
    -Wno-unknown-warning-option

    -Werror
    -Wpedantic
    -Wall
    -Wextra
    -Wdouble-promotion
    -Wformat=2
    -Wformat-signedness
    -Wnull-dereference
    -Winit-self
    -Wmissing-include-dirs
    -Wunused
    -Wuseless-cast
    -Wuninitialized
    -Wstrict-overflow=2
    -Wduplicated-branches
    -Wduplicated-cond
    -Wzero-as-null-pointer-constant
    -Wshadow
    -Wundef
    -Wcast-qual
    -Wcast-align
    -Wwrite-strings
    -Wconversion
    -Wpacked
    -Wredundant-decls
    -Winline
    -Winvalid-utf8
)

set(DEBUG_COMPILE_FLAGS
    -g    
    -O0
    -fsanitize=address
    -fstack-protector-all
    -DDEBUG
)

set(RELEASE_COMPILE_FLAGS
    -O3
    -march=native
    -flto
    -fno-stack-protector
    -DNDEBUG
)


add_library(c-compile-flags INTERFACE)
add_library(cxx-compile-flags INTERFACE)
target_compile_options(c-compile-flags INTERFACE ${C_BASE_COMPILE_FLAGS})
target_compile_options(cxx-compile-flags INTERFACE ${CXX_BASE_COMPILE_FLAGS})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(c-compile-flags INTERFACE ${DEBUG_COMPILE_FLAGS})
    target_compile_options(cxx-compile-flags INTERFACE ${DEBUG_COMPILE_FLAGS})
else()
    target_compile_options(c-compile-flags INTERFACE ${RELEASE_COMPILE_FLAGS})
    target_compile_options(cxx-compile-flags INTERFACE ${RELEASE_COMPILE_FLAGS})
endif()


# Link to standard math library
target_link_libraries(arithmos PRIVATE c-compile-flags m)


# add_subdirectory(algebra)
add_subdirectory(numeric)
