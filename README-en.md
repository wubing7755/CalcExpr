# CExpression-Calculator

A mathematical expression calculator written in C language, supporting basic operations and parentheses priority.

[![C Version](https://img.shields.io/badge/C-C11-blue)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CMake](https://img.shields.io/badge/CMake-3.10+-blue)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![CN](https://img.shields.io/badge/中文-red)](README.md)
[![ES](https://img.shields.io/badge/Español-yellow)](README-es.md)

🌐 **Choose Language**: [中文](README.md) | [Español](README-es.md) | **English**

## 📚 Project Overview

This is a practice project for learning C language, implementing mathematical expression evaluation using the **Recursive Descent Parser** algorithm. Through this project, you can learn:

- C language fundamentals
- Recursive descent algorithm
- Lexical analysis basics
- Modular code design

## ✨ Features

- ✅ Addition (+), Subtraction (-), Multiplication (*), Division (/)
- ✅ Parentheses priority handling
- ✅ Operator precedence (multiplication/division > addition/subtraction)
- ✅ Decimal number support
- ✅ Command-line interactive interface

## 🛠️ Tech Stack

- **Programming Language**: C (C11)
- **Build Tools**: CMake / GCC
- **Algorithm**: Recursive Descent Parser

## 📁 File Structure

```
CExpressionCalculator/
├── main.c           # Main program entry
├── calculator.c     # Calculator core logic (to be implemented)
├── calculator.h     # Calculator header file
├── token.h          # Token type definitions
├── CMakeLists.txt   # CMake build configuration
└── README.md        # Project documentation
```

## 🚀 Quick Start

### Build the Project

#### Method 1: Using GCC

```bash
gcc main.c calculator.c -o calculator.exe -lm
```

#### Method 2: Using CMake

```bash
# Create build directory
mkdir build && cd build

# Configure project (specify MinGW)
cmake -G "MinGW Makefiles" ..   # Windows
cmake ..                        # Linux / macOS

# Specify the build type（Debug / Release）
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build
cmake --build .
```

### Run the Program

```bash
./calculator.exe    # Windows
./calculator        # Linux / macOS
```

### Usage Example

```
Please enter expression> 2+3*4
Expression: 2+3*4
Result:    14.00

Please enter expression> (2+3)*4
Expression: (2+3)*4
Result:    20.00

Please enter expression> (3-5)*6
Expression: (3-5)*6
Result:    -12.00
```

## 📖 Learning Topics

### 1. Recursive Descent Algorithm

Recursive definition of mathematical expressions:

```
Expression = Term { (+|-) Term }
Term       = Factor { (*|/) Factor }
Factor     = Number | '(' Expression ')'
```

This recursive definition naturally supports operator precedence!

### 2. Lexical Analysis (Lexer)

Breaking input string into Tokens:
- Numbers: `123`, `45.67`
- Operators: `+`, `-`, `*`, `/`
- Parentheses: `(`, `)`

### 3. Modular Design

- `token.h` - Token type definitions
- `calculator.c` - Calculation logic
- `main.c` - User interaction

## 🤝 Contributing

1. Fork this repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

##  License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

⭐ If this project helps you, please star to show your support!
