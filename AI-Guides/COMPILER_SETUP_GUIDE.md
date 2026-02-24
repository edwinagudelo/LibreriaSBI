# Compiler Setup Guide - GCC on Windows

This guide explains how to build and debug with GCC on Windows using Kiro IDE.

## Why GCC Instead of MSVC?

The Microsoft C/C++ debugging extension (`ms-vscode.cpptools`) is not available in Kiro IDE due to Microsoft restrictions. Therefore, we use GCC with GDB for debugging on Windows.

## GCC Setup (Required for Debugging in Kiro)

Follow these steps to build and debug with GCC:

### Prerequisites

Ensure GCC is installed and in PATH:
```bash
gcc --version
g++ --version
gdb --version
```

If not installed, install MSYS2 or MinGW-w64.

### Step 1: Create GCC Conan Profile

Create a file `~/.conan2/profiles/gcc-windows`:

```ini
[settings]
os=Windows
arch=x86_64
compiler=gcc
compiler.version=13
compiler.libcxx=libstdc++11
compiler.cppstd=17
build_type=Debug

[buildenv]
CC=gcc
CXX=g++
```

### Step 2: Install Dependencies with GCC Profile

```bash
# Clean previous build
Remove-Item -Recurse -Force build-gcc -ErrorAction SilentlyContinue

# Install with GCC profile
conan install . --output-folder=build-gcc --build=missing --profile=gcc-windows -s build_type=Debug
```

### Step 3: Configure CMake for GCC

```bash
# Configure with GCC
cmake -S . -B build-gcc -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="build-gcc/build-gcc/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
```

### Step 4: Build with GCC

```bash
cmake --build build-gcc --config Debug --target sbi_clib configura_test entorno_test
```

### Step 5: Run Tests

```bash
# Set PATH to find the DLL
$env:PATH="$PWD\build-gcc\CLib;$env:PATH"

# Run tests
./build-gcc/CLib/tests/configura_test.exe
./build-gcc/CLib/tests/entorno_test.exe
```

### Step 6: Debug with GDB

Use the `(GDB)` debug configurations in Kiro:
- `(GDB) Debug configura_test - Debug`
- `(GDB) Debug entorno_test - Debug`

Set breakpoints in your code and press F5 to start debugging.

## Code Changes for GCC Compatibility

The following changes were made to support GCC on Windows:

### CLib/src/Entorno.c

1. Added missing includes:
   ```c
   #include <stdlib.h>
   #include <string.h>
   ```

2. Added MinGW detection:
   ```c
   #if defined(__MINGW32__) || defined(__MINGW64__)
   #include <io.h>
   #include <direct.h>
   #define USE_WINDOWS_API
   #endif
   ```

3. Updated conditional compilation to use `USE_WINDOWS_API` for MinGW:
   - Changed `#ifdef _MSC_VER` to `#if defined(_MSC_VER) || defined(USE_WINDOWS_API)`
   - This ensures MinGW uses Windows API instead of POSIX functions

4. Fixed `_A_SUBDIR` to `_S_IFDIR` for MinGW compatibility

## Build Status

✅ **GCC Build**: Working and tested
- configura_test: All 31 assertions pass
- entorno_test: All 36 assertions pass

⚠️ **MSVC Build**: Compiles but cannot be debugged in Kiro
- Use for production builds only
- Debugging requires standard VS Code with Microsoft extension

## Maintaining Both Builds

You can keep both build directories:
- `build/` for MSVC builds (production)
- `build-gcc/` for GCC builds (development/debugging)

## Troubleshooting

### GCC Not Found

**Problem:** "gcc is not recognized"

**Solution:**
1. Install MSYS2 from https://www.msys2.org/
2. Add to PATH: `C:\msys64\mingw64\bin`
3. Restart terminal/VS Code

### Conan Can't Find GCC

**Problem:** "ERROR: gcc is not a valid compiler"

**Solution:**
Create the GCC profile as shown in Step 1 above.

### DLL Not Found When Running Tests

**Problem:** "The code execution cannot proceed because libsbi_clib.dll was not found"

**Solution:**
Set PATH before running:
```powershell
$env:PATH="$PWD\build-gcc\CLib;$env:PATH"
./build-gcc/CLib/tests/configura_test.exe
```

The launch.json configurations already handle this automatically for debugging.

## Commands Summary

### GCC Build (For Debugging in Kiro)
```powershell
# Install dependencies
conan install . --output-folder=build-gcc --build=missing --profile=gcc-windows -s build_type=Debug

# Configure
cmake -S . -B build-gcc -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="build-gcc/build/Debug/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# Build
cmake --build build-gcc --config Debug --target configura_test entorno_test

# Run tests
$env:PATH="$PWD\build-gcc\CLib;$env:PATH"
./build-gcc/CLib/tests/configura_test.exe
./build-gcc/CLib/tests/entorno_test.exe

# Debug: Press F5 and select a (GDB) configuration
```

### MSVC Build (For Production)
```powershell
# Build
conan install . --output-folder=build --build=missing -s build_type=Release
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Note: Cannot debug in Kiro, use for production builds only
```

## Quick Start Script

Use the provided batch script for easy setup:
```powershell
./setup-gcc-build.bat
```

This script automates all the steps above.
