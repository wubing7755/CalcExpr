# CMakeLists.txt - C语言计算器项目构建配置
#
# 使用方法：
#   1. mkdir build && cd build
#   2. cmake -G "MinGW Makefiles" ..
#      或 cmake -G "Visual Studio 17 2022" ..
#   3. cmake --build . --config Release
#   4. 运行生成的 calculator.exe

# ============================================================

# CMake 最低版本要求
cmake_minimum_required(VERSION 3.15)

# 项目名称、版本号和语言
project(CExpressionCalculator VERSION 1.0 LANGUAGES C)

# ============================================================
# 设置默认构建类型（仅对单配置生成器有效，如 MinGW）
# ============================================================
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ============================================================
# 设置 C 语言标准
# ============================================================
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ============================================================
# 源文件列表
# ============================================================
set(SOURCES
    main.c
    calculator.c
)

# ============================================================
# 创建可执行文件
# ============================================================
add_executable(calculator ${SOURCES})

# ============================================================
# 头文件目录
# ============================================================
target_include_directories(calculator
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# ============================================================
# 编译选项（现代 CMake 推荐写法）
# ============================================================
if(MSVC)
    target_compile_options(calculator PRIVATE
        /W4         # 高警告级别
        /permissive- # 严格标准模式
    )
else()
    target_compile_options(calculator PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# ============================================================
# 打印配置信息
# ============================================================
message(STATUS "")
message(STATUS "=== CExpressionCalculator Build Config ===")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Standard: ${CMAKE_C_STANDARD}")
message(STATUS "Output dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "==========================================")
message(STATUS "")