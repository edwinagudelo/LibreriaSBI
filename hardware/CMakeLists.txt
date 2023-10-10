# Se usa este archivo si esta definido la inclusión de hardware

add_library(CSensor src/CSensor.cpp)
add_library(CRegistro src/CRegistro.cpp)

target_include_directories(CSensor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(CRegistro PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# option(USE_HARDWARE "Usar las librerias de hardware" ON)

# if(USE_HARDWARE)
#     target_compile_definitions(hardware INTERFACE "USE_HARDWARE")
# endif()

# if(USE_HARDWARE)
#     target_link_libraries(hardware PUBLIC CSensor)
#     target_link_libraries(hardware PUBLIC CRegistro)
# endif()

#target_compile_definitions(CRegistro PUBLIC CSensor)
