# Debug Build Fix Summary

## Problem
When building and running tests in Debug mode, the application crashed with a heap corruption error:
```
Debug Assertion Failed!
File: minkernel\crts\ucrt\src\appcrt\heap\debug_heap.cpp
Line: 996
Expression: __acrt_first_block == header
```

## Root Causes

### 1. Runtime Library Mismatch (CRITICAL)
**Location:** `CLib/CMakeLists.txt` line 27

**Problem:** The CMakeLists.txt was forcing `/MTd` (static debug runtime) while Conan's toolchain was setting `/MDd` (dynamic debug runtime). This caused different parts of the application to use different heaps, leading to heap corruption when memory allocated in one heap was freed in another.

**Fix:** Removed `/MTd` and `/c` flags, allowing CMake/Conan to handle runtime library selection automatically.

```cmake
# Before (WRONG):
target_compile_options(sbi_clib PRIVATE /EHsc /MTd /W2 /c)

# After (CORRECT):
target_compile_options(sbi_clib PRIVATE /EHsc /W2)
```

### 2. Static Variable in Header File
**Location:** `CLib/include/Configura.h`

**Problem:** The `paramRoot` static variable was declared in the header file, causing each translation unit (C file and C++ test file) to have its own copy. This meant the C implementation and C++ tests were working with different linked lists.

**Fix:** Moved the static variable declaration from the header to the implementation file.

```c
// Removed from Configura.h:
static struct Param *paramRoot = NULL;

// Added to Configura.c:
static struct Param *paramRoot = NULL;
```

### 3. Removed cunit Dependency
**Location:** `conanfile.txt`

**Problem:** cunit doesn't build properly on Windows in Debug mode with MSVC.

**Fix:** Removed cunit from dependencies since only Catch2 is being used for testing.

## Test Results

### Debug Mode
- `configura_test`: ✅ All tests pass (31 assertions in 5 test cases)
- `entorno_test`: ⚠️ Has separate issues (directory operations, not related to heap corruption)

### Release Mode
- Both tests build and run successfully

## Key Lessons

1. **Always match runtime libraries** - When mixing C and C++ code with external libraries, ensure all components use the same runtime library (static vs dynamic, debug vs release)

2. **Never use static variables in headers** - Static variables in headers create separate instances per translation unit, breaking shared state

3. **Let build systems manage compiler flags** - When using Conan or other package managers, let them control runtime library selection rather than hardcoding flags

4. **Debug builds catch memory issues** - The Debug runtime has additional checks that catch heap corruption that Release builds might miss

## Commands to Build and Test

### Debug Mode
```bash
conan install . --output-folder=build --build=missing -s build_type=Debug
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug --target sbi_clib configura_test entorno_test
cd build/CLib/tests
ctest --output-on-failure -C Debug
```

### Release Mode
```bash
conan install . --output-folder=build --build=missing -s build_type=Release
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target sbi_clib configura_test entorno_test
cd build/CLib/tests
ctest --output-on-failure -C Release
```
