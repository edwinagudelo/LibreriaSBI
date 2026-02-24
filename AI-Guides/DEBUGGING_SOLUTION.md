# Debugging Solution - Quick Start

You have **two options** for debugging your tests:

## ✅ Option 1: Debug MSVC Builds (EASIEST - Recommended)

### What You Need:
Install the **C/C++ extension** by Microsoft in VS Code:

1. Press `Ctrl+Shift+X`
2. Search for "C/C++"
3. Install "C/C++" by Microsoft (ms-vscode.cpptools)
4. Restart VS Code

### How to Debug:
1. Open a test file (e.g., `CLib/tests/configura_test.cpp`)
2. Set breakpoints (click left of line numbers)
3. Press `F5`
4. Select `(MSVC) Debug configura_test - Debug`
5. Debug with full symbols! ✨

### Why This is Best:
- ✅ **Already compiled** - No changes needed
- ✅ **Full debug symbols** - PDB files already generated
- ✅ **Native Windows debugging** - Best integration
- ✅ **Works immediately** - Just install the extension

---

## 🔧 Option 2: Switch to GCC Compiler

### When to Use This:
- You prefer GDB debugger
- You need cross-platform compatibility
- You want Address Sanitizer support

### Quick Setup:
Run the provided script:
```bash
setup-gcc-build.bat
```

This will:
1. Check if GCC is installed
2. Create Conan GCC profile
3. Install dependencies
4. Configure and build with GCC
5. Create `build-gcc/` directory

### How to Debug with GCC:
1. After running the script
2. Press `F5` in VS Code
3. Select `(GDB) Debug configura_test - Debug`
4. Debug with GDB!

---

## 📋 Available Debug Configurations

After installing the C/C++ extension, you'll have:

### MSVC Debugger (cppvsdbg):
- `(MSVC) Debug configura_test - Debug`
- `(MSVC) Debug entorno_test - Debug`
- `(MSVC) Debug configura_test - Release`
- `(MSVC) Debug entorno_test - Release`

### GDB Debugger (after GCC setup):
- `(GDB) Debug configura_test - Debug`
- `(GDB) Debug entorno_test - Debug`

---

## 🎯 Recommendation

**Start with Option 1 (MSVC)** because:
1. Your code is already compiled with MSVC
2. Debug symbols (PDB files) are already generated
3. Just install one extension and you're ready
4. Native Windows debugging experience

**Switch to Option 2 (GCC)** only if:
- You specifically need GDB
- You're developing for cross-platform
- You need specific GCC features

---

## 🚀 Quick Start (MSVC)

```bash
# 1. Install C/C++ extension in VS Code (Ctrl+Shift+X)

# 2. Your build is already ready:
#    - build/CLib/Debug/sbi_clib.dll
#    - build/CLib/tests/Debug/configura_test.exe
#    - build/CLib/tests/Debug/entorno_test.exe
#    - All PDB files with debug symbols

# 3. Press F5 and select (MSVC) configuration

# That's it! 🎉
```

---

## 📚 More Information

- **Full compiler comparison**: See `COMPILER_SETUP_GUIDE.md`
- **Debugging commands**: See `CLib/tests/DEBUGGING_GUIDE.md`
- **Quick reference**: See `CLib/tests/QUICK_DEBUG_COMMANDS.md`

---

## ❓ Troubleshooting

### "Unable to start debugging"
→ Install C/C++ extension (ms-vscode.cpptools)

### "Cannot find sbi_clib.dll"
→ The launch.json already sets PATH correctly. Should work automatically.

### "No debug symbols found"
→ Verify PDB files exist: `dir build\CLib\Debug\*.pdb`
   They should be there (7-14 MB each)

### Want to use GCC instead?
→ Run `setup-gcc-build.bat`

---

## 🎓 Summary

**You don't need to change compilers!** 

Just install the C/C++ extension and you can debug your MSVC-compiled tests immediately with full symbol support. The debug symbols are already there, you just need the right VS Code extension to use them.
