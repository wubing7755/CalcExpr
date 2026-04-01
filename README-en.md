# CalcExpr

A mathematical expression calculator written in C language, supporting basic operations and parentheses priority.

[![C Version](https://img.shields.io/badge/C-C11-blue)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CMake](https://img.shields.io/badge/CMake-3.10+-blue)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![CN](https://img.shields.io/badge/中文-red)](README.md)
[![ES](https://img.shields.io/badge/Español-yellow)](README-es.md)

🌐 **Choose Language**: [中文](README.md) | [Español](README-es.md) | **English**

## 📚 Project Overview

CalcExpr is a mathematical expression calculator developed in C, using the **Recursive Descent Parser** algorithm for expression evaluation.

Project highlights:
- Clean modular architecture
- Zero dependencies (standard C library only)
- Runtime-controllable debug system
- Complete unit test coverage

## ✨ Features

- ✅ Addition (+), Subtraction (-), Multiplication (*), Division (/)
- ✅ Parentheses priority handling
- ✅ Operator precedence (multiplication/division > addition/subtraction)
- ✅ Decimal and scientific notation support
- ✅ Command-line interactive interface
- ✅ Interactive debug level selection
- ✅ Debug system (compile-time enable / runtime control)

## 🛠️ Tech Stack

- **Programming Language**: C (C11)
- **Build Tools**: CMake
- **Algorithm**: Recursive Descent Parser
- **Testing**: CTest

## 📁 File Structure

```
CalcExpr/
├── src/                    # Source code
│   ├── main.c            # Main program entry
│   ├── calculator.c       # Calculator public interface
│   ├── parser.c          # Recursive descent parser
│   ├── lexer.c           # Lexer
│   ├── command.c         # Command handler
│   ├── logger.c          # Logging system
│   ├── debug.c            # Debug system
│   └── platform/          # Platform-specific code
├── include/               # Header files
│   ├── calculator.h      # Public interface
│   ├── parser.h         # Parser interface
│   ├── lexer.h          # Lexer interface
│   ├── command.h        # Command interface
│   ├── logger.h         # Logger interface
│   └── debug.h          # Debug macro interface
├── test/                  # Unit tests
├── .vscode/              # VS Code configuration
├── CMakeLists.txt        # CMake build configuration
└── README.md             # Project documentation
```

## 🚀 Quick Start

### Build Project (CMake)

```bash
# 1. Create build directory
mkdir build && cd build

# 2. Configure based on your platform
# Windows MinGW:
cmake -G "MinGW Makefiles" ..

# Windows MSVC:
cmake -G "Visual Studio 17 2022" ..

# Linux/macOS:
cmake ..

# 3. Build
cmake --build .
```

### Run the Program

```bash
# Windows
./bin/calculator.exe

# Linux / macOS
./bin/calculator
```

### Interactive Debug

```bash
# Enable debug mode
./bin/calculator --debug

# Use commands in program
/show process   # Interactively select debug level
/hide process    # Disable debug output
```

### Usage Example

```
Please enter expression> 2+3*4
Expression: 2+3*4
Result:   14.00

Please enter expression> (2+3)*4
Expression: (2+3)*4
Result:   20.00

Please enter expression> (3-5)*6
Expression: (3-5)*6
Result:   -12.00
```

## 🧪 Testing

The project uses CTest for testing.

```bash
# Run all tests
ctest --output-on-failure

# Run specific test suite
ctest -R calc_tests_error --output-on-failure
```

Available test suites:
- `calc_tests_all` - Run all tests
- `calc_tests_success` - Success cases
- `calc_tests_error` - Error cases
- `calc_tests_api` - API contract tests
- `calc_tests_error_div0` - Division by zero tests

## 🔧 Debug System

### Compile-time Enable

Build with `-DENABLE_DEBUG=ON`:

```bash
cmake -DENABLE_DEBUG=ON -DCMAKE_BUILD_TYPE=Debug -S . -B build
cmake --build build
```

### Command-line Arguments

| Argument | Description |
|----------|-------------|
| `--debug` | Enable debug mode |
| `--debug-level=N` | Set debug level (1-5) |
| `--debug-module=NAME` | Set module (lexer/parser/calc/main/all) |

### Debug Levels

| Level | Description |
|-------|-------------|
| 1. Error Only | Disable debug output |
| 2. Warn+Info | Show general information |
| 3. Show Steps | Display expression evaluation process |
| 4. Parser Trace | Show syntax analysis details |
| 5. Full Trace | Show complete call chain |

### Debug Output Example

Input `2+3*4` with debug mode level 5:

```
[Step 1] Read number 2
[Step 2] Read number 3
[Step 3] Read number 4
[Step 4] 3 * 4 = 12
[Step 5] 2 + 12 = 14
Expression: 2+3*4
Result:   14
```

## 🤝 Contributing

Issues and Pull Requests are welcome!

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

⭐ If this project helps you, please star to show your support!
