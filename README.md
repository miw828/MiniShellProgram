# myShell — Mini Unix Shell

A C++ shell-like program that forks child processes to execute Linux commands,
built using object-oriented design with smart pointers.

## Features
- Executes any valid Linux program (`ls`, `pwd`, `echo`, custom executables, etc.)
- `last` — re-runs the most recently entered command
- `exit` — cleanly exits the shell
- Prevents zombie processes via `waitpid()`
- Smart pointer memory management (`unique_ptr`, `shared_ptr`)

## Usage
```bash
./myShell
```

**Built-in commands:**
| Command | Description |
|---------|-------------|
| `exit` | Exit the shell |
| `last` | Re-run the previous command |
| Any Linux command | Executed in a child process |

**Example session:**
```
Simple Shell (PID: 2575465)
Type 'exit' to quit; Type 'last' to re-run the last command.
myshell> echo Hello World!
Hello World!
myshell> last
Re-running: echo Hello World!
Hello World!
myshell> exit
Exiting shell.
```

## Build
```bash
make
make clean   # removes object files and executable
```

## File Structure
```
.
├── myShell.cpp         # Main orchestration loop
├── Process.hpp/.cpp    # Encapsulates fork(), exec(), waitpid()
├── Command.hpp/.cpp    # Parses input; converts args for execvp()
├── wrappedFuncs.hpp    # Stevens-style wrapper prototypes
├── wrappedFuncs.cpp    # Wrapped: fork, execvp, waitpid, etc.
└── Makefile
```

## Class Overview
- **`Process`** — manages the full child process lifecycle (fork → exec → wait)
- **`Command`** — tokenizes user input; converts `vector<string>` to `char*[]` for `execvp()`

## Error Handling
- System call failures print to `stderr` with `strerror(errno)` and throw `std::runtime_error`
- Invalid commands report the error and return control to the shell prompt
- All dynamically allocated memory is managed via smart pointers
