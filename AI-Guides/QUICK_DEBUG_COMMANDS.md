# Quick Debug Commands Reference

## Setup (Run Once)
```bash
cd build/CLib/tests
set PATH=..\..\CLib\Debug;%PATH%
```

## Start Debugging

### Debug configura_test
```bash
lldb Debug\configura_test.exe
```

### Debug entorno_test
```bash
lldb Debug\entorno_test.exe
```

## Essential LLDB Commands

### Breakpoints
```lldb
b agregarParam                    # Break at function
b Configura.c:25                  # Break at line
b traerParamComoChar if result==0 # Conditional breakpoint
breakpoint list                   # List all breakpoints
breakpoint delete 1               # Delete breakpoint #1
```

### Running
```lldb
run                              # Start program
run "[configura]"                # Run specific test
continue                         # Continue after breakpoint
```

### Stepping
```lldb
step      # Step into (s)
next      # Step over (n)
finish    # Step out
```

### Inspecting
```lldb
print paramRoot                  # Print variable
print *newOne                    # Dereference pointer
frame variable                   # Show all local variables
frame variable -L                # Show with locations
expr paramRoot->paramName        # Evaluate expression
```

### Stack & Threads
```lldb
bt                              # Backtrace (call stack)
frame select 2                  # Switch to frame #2
thread list                     # List all threads
```

### Source Code
```lldb
list                            # Show source around current line
list agregarParam               # Show function source
source list -n 10               # Show 10 lines
```

### Memory
```lldb
memory read paramRoot           # Read memory
memory read -s4 -fx -c4 0x...  # Read 4 bytes as hex
```

### Watchpoints
```lldb
watchpoint set variable paramRoot  # Watch variable
watchpoint list                    # List watchpoints
```

## Common Debugging Scenarios

### Debug a crash
```lldb
(lldb) run
# Program crashes
(lldb) bt                       # See where it crashed
(lldb) frame variable           # See local variables
(lldb) print *pointer           # Inspect pointer
```

### Debug memory corruption
```lldb
(lldb) b liberarMemoriaParametros
(lldb) run
(lldb) watchpoint set variable paramRoot
(lldb) continue
# Stops when paramRoot changes
```

### Debug specific test
```lldb
(lldb) run "[configura]" -s
# Runs only [configura] tests with verbose output
```

### Step through function
```lldb
(lldb) b agregarParam
(lldb) run
# Stops at agregarParam
(lldb) step                     # Step into malloc
(lldb) finish                   # Return from malloc
(lldb) next                     # Next line
(lldb) print newOne             # Check result
```

## VS Code Shortcuts

- `F5` - Start debugging
- `F9` - Toggle breakpoint
- `F10` - Step over
- `F11` - Step into
- `Shift+F11` - Step out
- `F5` - Continue
- `Shift+F5` - Stop debugging

## Catch2 Test Arguments

```bash
# List all tests
Debug\configura_test.exe --list-tests

# Run specific tag
Debug\configura_test.exe "[configura]"

# Run with verbose output
Debug\configura_test.exe -s

# Break on failure
Debug\configura_test.exe --break

# Run specific test case
Debug\configura_test.exe "Configura - Adding parameters"
```

## Quick Checks

### Verify debug symbols
```bash
dir *.pdb
# Should show: sbi_clib.pdb, configura_test.pdb, entorno_test.pdb
```

### Check DLL is found
```bash
where sbi_clib.dll
# Should show: ..\..\CLib\Debug\sbi_clib.dll
```

### Test without debugger
```bash
Debug\configura_test.exe
# Should run and show test results
```
