
cmake_minimum_required(VERSION 3.15)

project(LIBSBICTests LANGUAGES C)

find_package(Catch2 REQUIRED)

add_executable( configura_test configura_test.cpp)
target_include_directories(configura_test PUBLIC ${catch2_INCLUDE_DIRS_RELEASE})
target_link_directories(configura_test PUBLIC ${catch2_LIB_DIRS_RELEASE})
target_link_libraries(configura_test PRIVATE Catch2)
target_link_libraries(configura_test PRIVATE Catch2Main)
target_link_libraries(configura_test PUBLIC CConfigura)


