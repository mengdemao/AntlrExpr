cmake_minimum_required(VERSION 3.10)

project(AntlrExpr C CXX) 

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 显示详细信息
set (CMAKE_VERBOSE_MAKEFILE OFF)

# 设置编译工具
set(ANTLR_EXECUTABLE ${CMAKE_SOURCE_DIR}/bin/antlr-complete.jar)

# 设置版本号
find_package(Git QUIET)
if (GIT_FOUND)
    # 主版本号
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0 HEAD
        OUTPUT_VARIABLE GIT_TAG
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    # 次版本号
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        OUTPUT_VARIABLE GIT_SHA
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif (GIT_FOUND)
set(${PROJECT_NAME}_VERSION_MAJOR ${GIT_TAG})
set(${PROJECT_NAME}_VERSION_MINOR ${GIT_SHA})
set(PROJECT_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})

# 生成配置文件
configure_file(inc/config.h.in inc/config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/inc)

# 添加头文件路径
include_directories(${CMAKE_SOURCE_DIR}/inc)

include_directories(
  ${CMAKE_SOURCE_DIR}/runtime
  ${CMAKE_SOURCE_DIR}/runtime/atn
  ${CMAKE_SOURCE_DIR}/runtime/dfa
  ${CMAKE_SOURCE_DIR}/runtime/misc
  ${CMAKE_SOURCE_DIR}/runtime/support
  ${CMAKE_SOURCE_DIR}/runtime/tree
  ${CMAKE_SOURCE_DIR}/runtime/tree/pattern
  ${CMAKE_SOURCE_DIR}/runtime/tree/xpath
)

add_definitions(-DANTLR4CPP_STATIC)
file(GLOB_RECURSE ANTLR_RUNTIME_SRC ${CMAKE_SOURCE_DIR}/runtime/*.cpp)

macro(ANTLR_TARGET Name)
    # 一个相同名字的文件结构
    list(APPEND ANTLR_${Name}_INPUT 
        ${CMAKE_CURRENT_SOURCE_DIR}/${Name}.g4)

    set(ANTLR_${Name}_OUTPUT_DIR
            ${CMAKE_SOURCE_DIR})

    list(APPEND ANTLR_${Name}_CXX_OUTPUTS
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Lexer.h
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Lexer.cpp
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Parser.h
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Parser.cpp
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}BaseListener.h
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}BaseListener.cpp
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Listener.h
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Listener.cpp
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Visitor.h
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Visitor.cpp
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}BaseVisitor.h
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}BaseVisitor.cpp)
    
    list(APPEND ANTLR_${Name}_OUTPUTS
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Lexer.interp
        ${ANTLR_${Name}_OUTPUT_DIR}/src/${Name}Lexer.tokens
        ${ANTLR_${Name}_CXX_OUTPUTS})

    list(APPEND ANTLR_TARGET_COMPILE_FLAGS
        -Werror -listener -visitor)

    add_custom_command(
        OUTPUT ${ANTLR_${Name}_OUTPUTS}
        COMMAND java -jar ${ANTLR_EXECUTABLE}
            -o ${ANTLR_${Name}_OUTPUT_DIR}/src
            -Dlanguage=Cpp
            ${ANTLR_TARGET_COMPILE_FLAGS}
            ${ANTLR_${Name}_INPUT}
        DEPENDS ${ANTLR_${Name}_INPUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Building ${Name} with ANTLR")
endmacro(ANTLR_TARGET)

ANTLR_TARGET(Expr)

# 添加编译头文件
include_directories(${CMAKE_SOURCE_DIR}/src)

# Disable warning C4819
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 添加可执行文件
add_executable(${PROJECT_NAME}
               ${CMAKE_SOURCE_DIR}/main.cc
               ${ANTLR_RUNTIME_SRC}
               ${ANTLR_Expr_CXX_OUTPUTS})

# 
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

# 启动测试
include(CTest)
enable_testing()

# 添加测试
add_test(NAME AntlrExprTest_1 COMMAND AntlrExpr "1+2+3")
set_tests_properties(AntlrExprTest_1 PROPERTIES PASS_REGULAR_EXPRESSION 1)

add_test(NAME AntlrExprTest_2 COMMAND AntlrExpr "1+2*3")
set_tests_properties(AntlrExprTest_2 PROPERTIES PASS_REGULAR_EXPRESSION 0)

add_test(NAME AntlrExprTest_3 COMMAND AntlrExpr "(1+2)*3")
set_tests_properties(AntlrExprTest_3 PROPERTIES PASS_REGULAR_EXPRESSION 0)

add_test(NAME AntlrExprTest_4 COMMAND AntlrExpr "1*(2+3)")
set_tests_properties(AntlrExprTest_4 PROPERTIES PASS_REGULAR_EXPRESSION 0)

add_test(NAME AntlrExprTest_5 COMMAND AntlrExpr "1*(2+3)")
set_tests_properties(AntlrExprTest_5 PROPERTIES PASS_REGULAR_EXPRESSION 0)
