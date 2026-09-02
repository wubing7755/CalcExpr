# CalcExpr 源文件清单。按模块组织，供主程序和测试目标复用。

# 核心源文件（不含 main 与平台相关代码）
set(CALCEXPR_CORE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/calculator.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.c
)

# 调试系统（仅在 ENABLE_DEBUG=ON 时编译）
set(CALCEXPR_DEBUG_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/debug.c
)

# 平台特定源文件
set(CALCEXPR_PLATFORM_SOURCES)
if(WIN32)
    list(APPEND CALCEXPR_PLATFORM_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_win.c)
elseif(UNIX AND NOT APPLE)
    list(APPEND CALCEXPR_PLATFORM_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_linux.c)
elseif(APPLE)
    list(APPEND CALCEXPR_PLATFORM_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/platform_mac.c)
endif()

# 主程序入口
set(CALCEXPR_MAIN_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)
