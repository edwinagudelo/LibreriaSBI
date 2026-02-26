# Debugging Guide for CLib Tests

This guide explains how to debug the CLib unit tests using LLDB or other debuggers.

## Debug Symbols Configuration

The CMake files have been configured to include full debug symbols in all builds:

### For GCC/Clang:
- `-g3`: Maximum debug information
- `-O0`: No optimization (Debug builds only)
- Debug symbols are included even in Release builds for easier debugging

### For MSVC:
- `/Zi`: Full debug information in PDB files
- `/Od`: No optimization (Debug builds only)
- `/DEBUG:FULL`: Generate complete debug information
- PDB files are generated for both Debug and Release builds

## Building with Debug Symbols

### Debug Build (Recommended for debugging)
```bash
# Install dependencies
conan install . --output-folder=build --build=missing -s build_type=Debug

# Configure with debug symbols
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build build --config Debug --target sbi_clib configura_test entorno_test
```

### Release Build with Debug Symbols
```bash
# Install dependencies
conan install . --output-folder=build --build=missing -s build_type=Release

# Configure
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="build/build/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release

# Build (debug symbols are automatically included)
cmake --build build --config Release --target sbi_clib configura_test entorno_test
```

## Debugging with LLDB

### Command Line

#### Debug configura_test:
```bash
cd build/CLib/tests
set PATH=..\..\CLib\Debug;%PATH%
lldb Debug\configura_test.exe
```

#### Debug entorno_test:
```bash
cd build/CLib/tests
set PATH=..\..\CLib\Debug;%PATH%
lldb Debug\entorno_test.exe
```

### LLDB Commands

```lldb
# Set a breakpoint
(lldb) b agregarParam
(lldb) b Configura.c:25

# Run the program
(lldb) run

# Run with specific test
(lldb) run "[configura]"

# Step through code
(lldb) step      # Step into
(lldb) next      # Step over
(lldb) finish    # Step out

# Inspect variables
(lldb) print paramRoot
(lldb) print *newOne
(lldb) frame variable

# View backtrace
(lldb) bt

# Continue execution
(lldb) continue

# List source code
(lldb) list
```

## Debugging with VS Code

The project includes pre-configured launch configurations in `.vscode/launch.json`:

### Available Configurations:

1. **"(LLDB) Debug configura_test - Debug"**
   - Debugs configura_test in Debug mode
   - Full debug symbols, no optimization

2. **"(LLDB) Debug entorno_test - Debug"**
   - Debugs entorno_test in Debug mode
   - Full debug symbols, no optimization

3. **"(LLDB) Debug configura_test - Release with Symbols"**
   - Debugs configura_test in Release mode
   - Optimized code but with debug symbols

4. **"(LLDB) Debug entorno_test - Release with Symbols"**
   - Debugs entorno_test in Release mode
   - Optimized code but with debug symbols

### How to Use:

1. Open VS Code in the project root
2. Open a test file (e.g., `CLib/tests/configura_test.cpp`)
3. Set breakpoints by clicking in the gutter (left of line numbers)
4. Press `F5` or go to Run > Start Debugging
5. Select the appropriate configuration from the dropdown
6. The debugger will stop at your breakpoints

### Setting Breakpoints:

- Click in the gutter next to line numbers
- Or use the command palette: `Debug: Toggle Breakpoint`
- Conditional breakpoints: Right-click on a breakpoint > Edit Breakpoint

## Debugging Specific Tests

You can debug specific test cases by passing arguments:

### Command Line:
```bash
lldb -- Debug\configura_test.exe "[configura]"
```

### In VS Code:
Modify the `args` array in the launch configuration:
```json
"args": ["[configura]", "-s"]
```

Common Catch2 arguments:
- `"[configura]"` - Run only tests with the [configura] tag
- `"-s"` - Show successful assertions
- `"--break"` - Break into debugger on failure
- `"--list-tests"` - List all available tests

## Debugging Memory Issues

### Enable Address Sanitizer (GCC/Clang):
Add to CMakeLists.txt:
```cmake
target_compile_options(configura_test PRIVATE -fsanitize=address)
target_link_options(configura_test PRIVATE -fsanitize=address)
```

### MSVC Debug Heap:
The Debug build automatically enables heap checking. Assertions will trigger on:
- Buffer overruns
- Use after free
- Double free
- Memory leaks

## Verifying Debug Symbols

### Windows (MSVC):
Check for PDB files:
```bash
dir build\CLib\Debug\*.pdb
dir build\CLib\tests\Debug\*.pdb
```

You should see:
- `sbi_clib.pdb`
- `configura_test.pdb`
- `entorno_test.pdb`

### Linux/macOS (GCC/Clang):
```bash
file build/CLib/tests/configura_test
# Should show: "not stripped" or "with debug_info"

# Or use objdump
objdump --debugging build/CLib/tests/configura_test | head
```

## Common Issues

### Issue: "No debug symbols found"
**Solution:** Rebuild with Debug configuration or verify PDB files exist

### Issue: "Cannot find source file"
**Solution:** Ensure you're running the debugger from the correct working directory

### Issue: "Breakpoint not hit"
**Solution:** 
- Verify the code is actually executed
- Check if optimization removed the code
- Ensure debug symbols are loaded

### Issue: DLL not found when debugging
**Solution:** The PATH is automatically set in launch configurations. If running manually:
```bash
set PATH=%CD%\..\..\CLib\Debug;%PATH%
```

## Tips

1. **Use Debug builds for debugging** - They have no optimization and full symbols
2. **Release builds with symbols** - Good for debugging performance issues
3. **Set breakpoints early** - Before the issue occurs to trace execution
4. **Use conditional breakpoints** - To break only when specific conditions are met
5. **Watch variables** - Add variables to watch window to track changes
6. **Check call stack** - Understand how you got to the current point

## Additional Resources

- [LLDB Tutorial](https://lldb.llvm.org/use/tutorial.html)
- [VS Code Debugging](https://code.visualstudio.com/docs/editor/debugging)
- [Catch2 Documentation](https://github.com/catchorg/Catch2/blob/devel/docs/Readme.md)
