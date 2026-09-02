# =============================================================================
# CalcExpr - CMake 构建配置（跨平台表达式计算器）
#
# 构建：cmake --preset ninja-debug && cmake --build --preset ninja-debug
# 测试：ctest --preset ninja-debug --output-on-failure
# =============================================================================

cmake_minimum_required(VERSION 3.21...3.31)

project(CalcExpr
    VERSION 1.0.0
    DESCRIPTION "A cross-platform expression calculator written in C"
    HOMEPAGE_URL "https://github.com/wubing7755/CalcExpr"
    LANGUAGES C
)

# CTest 开关（默认开启 BUILD_TESTING）
include(CTest)

# 导出 compile_commands.json（VSCode/clangd 智能提示）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =============================================================================
# 构建类型配置
# =============================================================================
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# =============================================================================
# C 语言标准
# =============================================================================
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# =============================================================================
# 特性开关
# =============================================================================
option(ENABLE_DEBUG "Enable debug macro system (zero overhead when OFF)" OFF)
option(CALCEXPR_ENABLE_ASAN "Enable AddressSanitizer where supported" OFF)
option(CALCEXPR_ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer where supported" OFF)
option(CALCEXPR_ENABLE_COVERAGE "Enable coverage flags where supported" OFF)

# =============================================================================
# 调试系统配置
# =============================================================================
if(ENABLE_DEBUG)
    add_compile_definitions(DEBUG_ENABLE=1)
    add_compile_definitions(DEBUG_DEFAULT_LEVEL=5)  # TRACE level
    add_compile_definitions(DEBUG_DEFAULT_MODULE=0xFF)  # ALL modules
else()
    add_compile_definitions(DEBUG_ENABLE=0)
endif()

# =============================================================================
# 构建模块
# =============================================================================
include(cmake/platform.cmake)
include(cmake/CompilerOptions.cmake)
include(cmake/Sources.cmake)

# =============================================================================
# 主程序可执行文件
# =============================================================================
set(CALCEXPR_CORE_ALL ${CALCEXPR_CORE_SOURCES} ${CALCEXPR_PLATFORM_SOURCES})
if(ENABLE_DEBUG)
    list(APPEND CALCEXPR_CORE_ALL ${CALCEXPR_DEBUG_SOURCES})
endif()

add_executable(calculator ${CALCEXPR_CORE_ALL} ${CALCEXPR_MAIN_SOURCES})

target_include_directories(calculator
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform
)

calcexpr_target_defaults(calculator)

# 数学库 - Unix-like 系统需要，Windows 不需要
if(UNIX)
    target_link_libraries(calculator PRIVATE m)
endif()

set_target_properties(calculator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "calculator"
)

# =============================================================================
# 单元测试
# =============================================================================
if(BUILD_TESTING)
    enable_testing()
    include(cmake/Tests.cmake)
endif()

# =============================================================================
# 安装规则
# =============================================================================
install(TARGETS calculator
    RUNTIME DESTINATION bin
)

# =============================================================================
# 打印构建信息
# =============================================================================
message(STATUS "")
message(STATUS "============================================================")
message(STATUS "  CalcExpr - Build Configuration")
message(STATUS "============================================================")
message(STATUS "  Version:        ${PROJECT_VERSION}")
message(STATUS "  Platform:       ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Compiler:       ${CMAKE_C_COMPILER_ID} (${CMAKE_C_COMPILER})")
message(STATUS "  Build Type:     ${CMAKE_BUILD_TYPE}")
message(STATUS "  C Standard:     C${CMAKE_C_STANDARD}")
message(STATUS "  Debug System:   ${ENABLE_DEBUG}")
message(STATUS "============================================================")
message(STATUS "")
