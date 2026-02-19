cmake_minimum_required(VERSION 3.20)

project(CLibTests LANGUAGES CXX)

find_package(Catch2 3 REQUIRED)

# Test for Configura module
add_executable(configura_test configura_test.cpp)
target_link_libraries(configura_test PRIVATE 
    sbi_clib
    Catch2::Catch2WithMain
)

# Test for Entorno module
add_executable(entorno_test entorno_test.cpp)
target_link_libraries(entorno_test PRIVATE 
    sbi_clib
    Catch2::Catch2WithMain
)

# Register tests with CTest manually (avoid catch_discover_tests on Windows with DLL issues)
include(CTest)
add_test(NAME configura_test COMMAND configura_test)
add_test(NAME entorno_test COMMAND entorno_test)

# Set the PATH for tests to find the DLL (works for both Debug and Release)
set_tests_properties(configura_test PROPERTIES 
    ENVIRONMENT "PATH=${CMAKE_BINARY_DIR}/CLib/$<CONFIG>;$ENV{PATH}"
)
set_tests_properties(entorno_test PROPERTIES 
    ENVIRONMENT "PATH=${CMAKE_BINARY_DIR}/CLib/$<CONFIG>;$ENV{PATH}"
)
