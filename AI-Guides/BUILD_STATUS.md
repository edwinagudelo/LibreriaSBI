# Build Status - LibreriaSBI

## Current Status: ✅ Ready for Development

### GCC Build (Primary - For Debugging)
- **Status**: ✅ Working
- **Location**: `build-gcc/`
- **Compiler**: GCC 15.2.0 (MinGW)
- **Debugger**: GDB 17.1
- **Tests**: All passing

### MSVC Build (Secondary - For Production)
- **Status**: ⚠️ Compiles but no debugging in Kiro
- **Location**: `build/`
- **Compiler**: MSVC 19.x
- **Debugger**: Not available in Kiro
- **Use Case**: Production builds only

## Test Results

### CLib Tests (GCC Build)

#### configura_test.exe
```
✅ All tests passed (31 assertions in 5 test cases)
```

Tests covered:
- Parameter creation and retrieval
- Parameter updates
- Parameter deletion
- Memory management
- Edge cases (NULL parameters, empty values)

#### entorno_test.exe
```
✅ All tests passed (36 assertions in 4 test cases)
```

Tests covered:
- Directory creation and deletion
- Directory existence validation
- Environment variable reading
- File operations (create, delete, exists)
- File listing with directory traversal

## Quick Commands

### Build Everything
```powershell
./setup-gcc-build.bat
```

### Build Manually
```powershell
# Install dependencies
conan install . --output-folder=build-gcc --build=missing --profile=gcc-windows -s build_type=Debug

# Configure
cmake -S . -B build-gcc -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="build-gcc/build/Debug/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++

# Build
cmake --build build-gcc --config Debug --target configura_test entorno_test
```

### Run Tests
```powershell
cd build-gcc
$env:PATH="$PWD\CLib;$env:PATH"
./CLib/tests/configura_test.exe
./CLib/tests/entorno_test.exe
```

### Debug in Kiro
1. Open a test file (e.g., `CLib/tests/configura_test.cpp`)
2. Set breakpoints
3. Press `F5`
4. Select `(GDB) Debug configura_test - Debug` or `(GDB) Debug entorno_test - Debug`

## Project Structure

```
LibreriaSBI/
├── CLib/                      # C library
│   ├── include/              # Public headers
│   │   ├── Configura.h       # Configuration management (documented)
│   │   ├── Constantes.h      # Constants
│   │   └── Entorno.h         # Environment utilities
│   ├── src/                  # Implementation
│   │   ├── Configura.c       # Fixed memory bugs
│   │   └── Entorno.c         # Fixed for GCC/MinGW
│   └── tests/                # Unit tests
│       ├── configura_test.cpp
│       ├── entorno_test.cpp
│       ├── README.md
│       ├── DEBUGGING_GUIDE.md
│       └── DEBUG_BUILD_FIX.md
├── CppLib/                    # C++ library (not yet tested)
├── Hardware/                  # Hardware abstraction
├── build/                     # MSVC build output
├── build-gcc/                 # GCC build output (for debugging)
├── .vscode/
│   └── launch.json           # Debug configurations
├── .github/workflows/
│   └── sbilib_pipeline.yml   # CI/CD pipeline
├── CMakeLists.txt            # Main build config
├── conanfile.txt             # Dependencies (Catch2)
├── setup-gcc-build.bat       # Automated setup
├── COMPILER_SETUP_GUIDE.md   # Detailed setup guide
├── GCC_MIGRATION_SUCCESS.md  # Migration summary
└── BUILD_STATUS.md           # This file
```

## Dependencies

### Required
- **CMake**: 3.15+
- **Conan**: 2.x
- **GCC**: 13+ (MinGW/MSYS2)
- **GDB**: For debugging

### Libraries (via Conan)
- **Catch2**: 3.4.0 (unit testing)

## Known Issues

### Resolved ✅
- ✅ Debug mode heap corruption (runtime library mismatch)
- ✅ Static variable duplication across translation units
- ✅ Memory allocation bugs (missing +1 for null terminators)
- ✅ GCC compilation errors on Windows (POSIX vs Windows API)
- ✅ Missing debug symbols
- ✅ DLL path issues when running tests

### Warnings (Non-Critical)
- ⚠️ Unused parameter `mascara` in `traerListaArchivosConMascara` (not implemented yet)
- ⚠️ Use-after-free warning in `traerListaArchivos` (false positive, temp is freed correctly)

## Documentation

- **[COMPILER_SETUP_GUIDE.md](COMPILER_SETUP_GUIDE.md)** - How to set up GCC and build
- **[GCC_MIGRATION_SUCCESS.md](GCC_MIGRATION_SUCCESS.md)** - What was fixed during migration
- **[CLib/tests/README.md](CLib/tests/README.md)** - How to run and write tests
- **[CLib/tests/DEBUGGING_GUIDE.md](CLib/tests/DEBUGGING_GUIDE.md)** - How to debug with GDB
- **[CLib/tests/DEBUG_BUILD_FIX.md](CLib/tests/DEBUG_BUILD_FIX.md)** - Debug mode fixes
- **[CLib/include/Configura.h](CLib/include/Configura.h)** - API documentation

## CI/CD

GitHub Actions pipeline configured:
- **File**: `.github/workflows/sbilib_pipeline.yml`
- **Platforms**: Windows, Linux, macOS
- **Builds**: Debug and Release
- **Tests**: Automatic execution
- **Artifacts**: Build outputs uploaded

## Next Steps

### Immediate
1. ✅ GCC build working
2. ✅ Tests passing
3. ✅ Debugging configured
4. ✅ Documentation complete

### Future Enhancements
- [ ] Add tests for CppLib
- [ ] Implement `traerListaArchivosConMascara` mask filtering
- [ ] Add more edge case tests
- [ ] Set up code coverage reporting
- [ ] Add sanitizer builds (AddressSanitizer, UndefinedBehaviorSanitizer)

## Support

For issues or questions:
1. Check the documentation files listed above
2. Review the troubleshooting section in COMPILER_SETUP_GUIDE.md
3. Verify GCC and GDB are in PATH
4. Ensure Conan profile is created correctly

---

**Last Updated**: After successful GCC migration
**Build System**: CMake + Conan
**Primary Compiler**: GCC 15.2.0 (MinGW)
**Test Framework**: Catch2 3.4.0
