# C Util Library
cmake_minimum_required(VERSION 3.20)

set (PROJECT_VERSION "1.0")
set (HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(sbi_clib VERSION ${PROJECT_VERSION})

add_library(sbi_clib SHARED)
target_include_directories(sbi_clib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(sbi_clib
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Configura.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Entorno.h  
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Configura.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Entorno.c
)

# Enable debug symbols for all build types
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # GCC/Clang
    target_compile_options(sbi_clib PRIVATE -Wall -Wextra -g3 -O0)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC - Let CMake/Conan handle runtime library selection
    target_compile_options(sbi_clib PRIVATE /EHsc /W2 /Zi /Od)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(sbi_clib PRIVATE WIN_EXPORT)
    # Generate PDB files for debugging
    target_link_options(sbi_clib PRIVATE /DEBUG:FULL)
endif()

# Enable testing
enable_testing()
add_subdirectory(tests)
