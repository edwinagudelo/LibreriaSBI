# 
# CMake file

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(LibreriaSBI LANGUAGES CXX)

# Require C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_HARDWARE "Usar las librerias de hardware" ON)

# includes
include_directories("./hardware/include")
include_directories("./include")

add_executable(libsbitest libsbi_test.cpp)

target_include_directories(libsbitest PUBLIC "${PROJECT_SOURCE_DIR}/hardware/include")
target_include_directories(libsbitest PUBLIC "${PROJECT_SOURCE_DIR}/include")

if(USE_HARDWARE)
    add_subdirectory(hardware)
    target_link_libraries(libsbitest PUBLIC CSensor)
    target_link_libraries(libsbitest PUBLIC CRegistro)
endif()

add_library(CConfigura STATIC src/Cconfigura.cpp include/CConfigura.h)
target_link_libraries(libsbitest PUBLIC CConfigura)

add_subdirectory(tests)
