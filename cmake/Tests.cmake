# 测试目标注册。
#
# CalcExpr 使用自带的手写测试框架（支持 --suite/--filter/中文用例名），
# 不引入 Unity。每个测试入口编译为独立可执行文件并注册到 CTest。

set(CALCEXPR_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test/test_calculator.c
    ${CALCEXPR_CORE_SOURCES}
)
if(ENABLE_DEBUG)
    list(APPEND CALCEXPR_TEST_SOURCES ${CALCEXPR_DEBUG_SOURCES})
endif()

add_executable(calculator_tests ${CALCEXPR_TEST_SOURCES})

target_include_directories(calculator_tests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

calcexpr_target_defaults(calculator_tests)

if(UNIX)
    target_link_libraries(calculator_tests PRIVATE m)
endif()

set_target_properties(calculator_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "test_calculator"
)

# 全套测试
add_test(NAME calc_tests_all COMMAND calculator_tests)
# 成功用例
add_test(NAME calc_tests_success COMMAND calculator_tests --suite=success)
# 错误用例
add_test(NAME calc_tests_error COMMAND calculator_tests --suite=error)
# API 合约
add_test(NAME calc_tests_api COMMAND calculator_tests --suite=api)
# 除零专项
add_test(NAME calc_tests_error_div0 COMMAND calculator_tests --suite=error --filter=1/0)
