add_library(arithmos STATIC)

target_include_directories(arithmos
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)


# Base compile flags
set(C_BASE_COMPILE_FLAGS
    -fdiagnostics-color=always
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
    -fdiagnostics-color=always
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
    # -flto
    -march=native
    -fno-stack-protector
    -DNDEBUG
)


target_compile_options(arithmos PRIVATE ${C_BASE_COMPILE_FLAGS})


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(arithmos PUBLIC ${DEBUG_COMPILE_FLAGS})
else()
    target_compile_options(arithmos PUBLIC ${RELEASE_COMPILE_FLAGS})
endif()


# Link math library
target_link_libraries(arithmos PRIVATE m)


add_subdirectory(numeric)
