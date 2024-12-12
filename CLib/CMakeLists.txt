# C Util Library
cmake_minimum_required(VERSION 3.20)

set (PROJECT_VERSION "1.0")

project(sbi_clib VERSION ${PROJECT_VERSION})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(sbi_clib SHARED)

target_include_directories(sbi_clib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(sbi_clib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Configura.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Constantes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Entorno.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Configura.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Entorno.c
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # G++
    target_compile_options(sbi_clib PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC
    target_compile_options(sbi_clib PRIVATE /EHsc /MTd /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(sbi_clib PRIVATE WIN_EXPORT)
endif()


