# From project root -- Release 
conan install . --output-folder=build --build=missing
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target sbi_clib configura_test entorno_test

# Run tests
cd build/CLib/tests
ctest --output-on-failure -C Release



# From project root -- Debug 
conan install . --output-folder=build --build=missing
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug --target sbi_clib configura_test entorno_test

# Run tests
cd build/CLib/tests
ctest --output-on-failure -C Debug
