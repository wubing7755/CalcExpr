# CalcExpr

一个用 C 语言编写的表达式计算器，支持基本数学运算和括号优先级。

[![C Version](https://img.shields.io/badge/C-C11-blue)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CMake](https://img.shields.io/badge/CMake-3.10+-blue)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)
[![EN](https://img.shields.io/badge/English-blue)](../README.md)
[![ES](https://img.shields.io/badge/Español-yellow)](README-es.md)

🌐 **选择语言**: [English](../README.md) | [Español](README-es.md) | **中文**

## 📚 项目简介

CalcExpr 是一个用 C 语言开发的表达式计算器，采用**递归下降解析器（Recursive Descent Parser）**算法实现数学表达式求值。

项目特点：
- 简洁的模块化架构
- 零依赖（仅使用标准 C 库）
- 运行时可控的调试系统
- 完整的单元测试覆盖

## ✨ 功能特性

- ✅ 加法 (+)、减法 (-)、乘法 (*)、除法 (/)
- ✅ 括号优先级处理
- ✅ 运算符优先级（乘除 > 加减）
- ✅ 支持小数和科学计数法
- ✅ 命令行交互界面
- ✅ 交互式调试级别选择
- ✅ 调试系统（支持编译时开启/运行时控制）

## 🛠️ 技术栈

- **编程语言**: C (C11)
- **构建工具**: CMake
- **算法**: 递归下降解析器
- **测试**: CTest

## 📁 文件结构

```
CalcExpr/
├── src/                    # 源代码
│   ├── main.c            # 主程序入口
│   ├── calculator.c       # 计算器公共接口
│   ├── parser.c          # 递归下降解析器
│   ├── lexer.c           # 词法分析器
│   ├── command.c         # 命令行命令处理
│   ├── logger.c          # 日志系统
│   ├── debug.c           # 调试系统
│   └── platform/          # 平台相关代码
├── include/               # 头文件
│   ├── calculator.h      # 公共接口
│   ├── parser.h         # 解析器接口
│   ├── lexer.h          # 词法分析器接口
│   ├── command.h        # 命令接口
│   ├── logger.h         # 日志接口
│   └── debug.h          # 调试宏接口
├── test/                  # 单元测试
├── .vscode/              # VS Code 配置
├── CMakeLists.txt        # CMake 构建配置
└── README.md             # 项目说明
```

## 🚀 快速开始

### 编译项目 (CMake)

```bash
# 1. 创建构建目录
mkdir build && cd build

# 2. 根据平台配置
# Windows MinGW:
cmake -G "MinGW Makefiles" ..

# Windows MSVC:
cmake -G "Visual Studio 17 2022" ..

# Linux/macOS:
cmake ..

# 3. 编译
cmake --build .
```

### 运行程序

```bash
# Windows
./bin/calculator.exe

# Linux / macOS
./bin/calculator
```

### 交互式调试

```bash
# 开启调试模式
./bin/calculator --debug

# 在程序中使用命令
/show process   # 交互选择调试级别
/hide process    # 关闭调试输出
```

### 使用示例

```
请输入表达式> 2+3*4
表达式: 2+3*4
结果:   14.00

请输入表达式> (2+3)*4
表达式: (2+3)*4
结果:   20.00

请输入表达式> (3-5)*6
表达式: (3-5)*6
结果:   -12.00
```

## 🧪 测试

项目已集成 CTest。

```bash
# 运行所有测试
ctest --output-on-failure

# 运行指定测试套件
ctest -R calc_tests_error --output-on-failure
```

可用测试套件：
- `calc_tests_all` - 运行所有测试
- `calc_tests_success` - 成功用例
- `calc_tests_error` - 错误用例
- `calc_tests_api` - API 合约测试
- `calc_tests_error_div0` - 除零错误测试

## 🔧 调试系统

### 编译时启用

构建时添加 `-DENABLE_DEBUG=ON`：

```bash
cmake -DENABLE_DEBUG=ON -DCMAKE_BUILD_TYPE=Debug -S . -B build
cmake --build build
```

### 命令行参数

| 参数 | 说明 |
|------|------|
| `--debug` | 开启调试模式 |
| `--debug-level=N` | 设置调试级别 (1-5) |
| `--debug-module=NAME` | 设置模块 (lexer/parser/calc/main/all) |

### 调试级别

| 级别 | 说明 |
|------|------|
| 1. 仅错误 | 关闭调试输出 |
| 2. 警告+信息 | 显示一般信息 |
| 3. 计算步骤 | 显示表达式求值过程 |
| 4. 解析器跟踪 | 显示语法分析详情 |
| 5. 完整跟踪 | 显示全部调用链 |

### 调试输出示例

输入 `2+3*4` 在调试模式级别 5：

```
[步骤1] 读取数字 2
[步骤2] 读取数字 3
[步骤3] 读取数字 4
[步骤4] 3 * 4 = 12
[步骤5] 2 + 12 = 14
表达式: 2+3*4
结果:   14
```

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/amazing-feature`)
3. 提交更改 (`git commit -m 'Add amazing feature'`)
4. 推送到分支 (`git push origin feature/amazing-feature`)
5. 开启 Pull Request

## 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

---

⭐ 如果这个项目对你有帮助，请 star 支持！
