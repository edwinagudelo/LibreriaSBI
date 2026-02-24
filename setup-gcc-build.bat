@echo off
REM Setup script for building with GCC on Windows

echo ========================================
echo GCC Build Setup for LibreriaSBI
echo ========================================
echo.

REM Check if GCC is available
where gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: GCC not found in PATH
    echo.
    echo Please install MSYS2 or MinGW-w64 and add to PATH
    echo Example: C:\msys64\mingw64\bin
    echo.
    pause
    exit /b 1
)

echo Found GCC:
gcc --version | findstr "gcc"
echo.

REM Check if GDB is available
where gdb >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo WARNING: GDB not found in PATH
    echo Debugging will not work without GDB
    echo.
)

REM Clean previous GCC build
echo Cleaning previous GCC build...
if exist build-gcc (
    rmdir /s /q build-gcc
)
echo.

REM Create Conan profile for GCC
echo Creating Conan GCC profile...
if not exist "%USERPROFILE%\.conan2\profiles" mkdir "%USERPROFILE%\.conan2\profiles"

(
echo [settings]
echo os=Windows
echo arch=x86_64
echo compiler=gcc
echo compiler.version=13
echo compiler.libcxx=libstdc++11
echo compiler.cppstd=17
echo build_type=Debug
echo.
echo [buildenv]
echo CC=gcc
echo CXX=g++
) > "%USERPROFILE%\.conan2\profiles\gcc-windows"

echo Conan profile created at: %USERPROFILE%\.conan2\profiles\gcc-windows
echo.

REM Install dependencies with Conan
echo Installing dependencies with Conan...
conan install . --output-folder=build-gcc --build=missing --profile=gcc-windows -s build_type=Debug
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Conan install failed
    pause
    exit /b 1
)
echo.

REM Configure with CMake
echo Configuring with CMake...
cmake -S . -B build-gcc -G "MinGW Makefiles" ^
    -DCMAKE_TOOLCHAIN_FILE="build-gcc/build/Debug/generators/conan_toolchain.cmake" ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DCMAKE_C_COMPILER=gcc ^
    -DCMAKE_CXX_COMPILER=g++

if %ERRORLEVEL% NEQ 0 (
    echo ERROR: CMake configuration failed
    pause
    exit /b 1
)
echo.

REM Build
echo Building with GCC...
cmake --build build-gcc --config Debug --target sbi_clib configura_test entorno_test
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Build failed
    pause
    exit /b 1
)
echo.

echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Test executables:
echo   - build-gcc\CLib\tests\configura_test.exe
echo   - build-gcc\CLib\tests\entorno_test.exe
echo.
echo To run tests:
echo   cd build-gcc\CLib\tests
echo   set PATH=..\..\CLib;%%PATH%%
echo   configura_test.exe
echo   entorno_test.exe
echo.
echo To debug in VS Code:
echo   1. Press F5
echo   2. Select a (GDB) configuration
echo.
pause
