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

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # G++
    target_compile_options(sbi_clib PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC - Let CMake/Conan handle runtime library selection
    target_compile_options(sbi_clib PRIVATE /EHsc /W2)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(sbi_clib PRIVATE WIN_EXPORT)
endif()

# Enable testing
enable_testing()
add_subdirectory(tests)
