# CLib Unit Tests

This directory contains unit tests for the CLib library using Catch2 framework.

## Test Files

- `configura_test.cpp` - Tests for the Configura module (parameter management)
- `entorno_test.cpp` - Tests for the Entorno module (environment and file operations)

## Building and Running Tests

### Prerequisites

- CMake 3.20 or higher
- Conan package manager
- C/C++ compiler (GCC, MSVC, or Clang)

### Build Steps (from project root)

1. Install dependencies with Conan:
```bash
conan install . --output-folder=build --build=missing
```

2. Configure CMake:
```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release
```

3. Build the project:
```bash
cmake --build build --config Release --target sbi_clib configura_test entorno_test
```

### Running Tests

Run all tests from the tests directory:
```bash
cd build/CLib/tests
ctest --output-on-failure -C Release
```

Run specific test executable directly:
```bash
cd build/CLib/tests
$env:PATH="$PWD\..\..\CLib\Release;$env:PATH"
.\Release\configura_test.exe
.\Release\entorno_test.exe
```

Run tests with verbose output:
```bash
.\Release\configura_test.exe -s
.\Release\entorno_test.exe -s
```

Run specific test cases:
```bash
.\Release\configura_test.exe "[configura]"
.\Release\entorno_test.exe "[file]"
```

## Known Issues

### Configura Module
- The original implementation had memory allocation bugs (missing +1 for null terminators)
- These have been fixed in the source code

### Entorno Module  
- `mkdir` on Windows requires different parameters than POSIX systems
- Some directory operations may fail due to permissions
- The `traerListaArchivos` function has complex platform-specific behavior

## Test Coverage

### Configura Module Tests
- Parameter creation (`crearParam`)
- Adding parameters (`agregarParam`)
  - String parameters
  - Integer parameters
  - Multiple parameters
- Retrieving parameters (`traerParamComoChar`)
  - Existing keys
  - Non-existent keys
  - Empty values
- Memory cleanup (`liberarMemoriaParametros`)
- Edge cases (long names, special characters)

### Entorno Module Tests
- Directory operations
  - Create directory (`crearDirectorio`)
  - Validate directory exists (`validarDirectorioExiste`)
  - Rename directory (`renonmbrarDirectorio`)
  - Delete directory (`borrarDirectorio`)
- File operations
  - Create empty file (`crearArchivoVacio`)
  - Check file exists (`archivoExiste`)
  - Delete file (`borrarArchivo`)
- Environment variables
  - Read existing variables (`leerVariableEntorno`)
  - Handle non-existent variables
- Edge cases and error conditions

## Catch2 Features Used

- `TEST_CASE` - Define test cases with tags
- `SECTION` - Group related tests within a test case
- `REQUIRE` - Assert conditions that must be true
- Tags for filtering tests: `[configura]`, `[entorno]`, `[file]`, `[directory]`, `[env]`, `[edge]`

## Notes

- Tests create temporary files and directories during execution
- Cleanup is performed after each test section
- Some tests may fail if run without proper permissions
- The DLL path must be in PATH for tests to run on Windows
