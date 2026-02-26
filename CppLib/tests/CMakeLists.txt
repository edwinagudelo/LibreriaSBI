
cmake_minimum_required(VERSION 3.15)

project(LIBSBITests LANGUAGES CXX)

# Require C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 REQUIRED)

add_executable( configura_test configura_test.cpp)
target_include_directories(configura_test PUBLIC ${catch2_INCLUDE_DIRS_RELEASE})
target_link_directories(configura_test PUBLIC ${catch2_LIB_DIRS_RELEASE})
target_link_libraries(configura_test PRIVATE Catch2)
target_link_libraries(configura_test PRIVATE Catch2Main)
target_link_libraries(configura_test PUBLIC CConfigura)


