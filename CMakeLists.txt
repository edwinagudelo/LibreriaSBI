# 
# CMake file

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(LibreriaSBI LANGUAGES CXX)

# Require C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols for all configurations
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # GCC/Clang - Full debug symbols
    add_compile_options(-g3)
    # Keep debug symbols even in Release builds
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g3")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC - Full debug info
    add_compile_options(/Zi)
    add_link_options(/DEBUG:FULL)
    # Keep debug symbols even in Release builds
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG:FULL")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG:FULL")
endif()

option(USE_HARDWARE "Usar las librerias de hardware" ON)

# includes
include_directories("./hardware/include")
include_directories("./include")
include_directories("./CppLib/include")

add_executable(libsbitest libsbi_test.cpp)

target_include_directories(libsbitest PUBLIC "${PROJECT_SOURCE_DIR}/hardware/include")
target_include_directories(libsbitest PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(libsbitest PUBLIC "${PROJECT_SOURCE_DIR}/CppLib/include")

if(USE_HARDWARE)
    add_subdirectory(hardware)
    target_link_libraries(libsbitest PUBLIC CSensor)
    target_link_libraries(libsbitest PUBLIC CRegistro)
endif()

add_subdirectory(CLib)

