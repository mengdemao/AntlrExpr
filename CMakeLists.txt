cmake_minimum_required(VERSION 3.10)

project(AntlrExpr C CXX)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake)

include(CTest)
include(ProcessorCount)
include(GNUInstallDirs)
include(Compiler)

set(CMAKE_CXX_STANDARD 17)

# 添加外部软件
find_package(Threads REQUIRED)
find_package(Doxygen REQUIRED)
find_package(Git REQUIRED)
find_package(antlr4-runtime REQUIRED)

# 设置编译工具
set(ANTLR_EXECUTABLE ${CMAKE_SOURCE_DIR}/bin/antlr-4.13.1-complete.jar)

option(ENABLE_CHECK "单元测试" ON)
option(ENABLE_DEBUG "高级打印" ON)
if(ENABLE_DEBUG)
  set(CONFIG_DEBUG 1)
endif(ENABLE_DEBUG)

# 设置版本号
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

# 提取编译信息
string(TIMESTAMP COMPILE_TIME %Y/%m/%d-%H:%M:%S)
set(BUILD_TIME ${COMPILE_TIME})
cmake_host_system_information(RESULT BUILD_HOST QUERY HOSTNAME)

# 生成配置文件
configure_file(${CMAKE_SOURCE_DIR}/inc/version.h.in ${CMAKE_SOURCE_DIR}/inc/generated/version.h)
configure_file(${CMAKE_SOURCE_DIR}/inc/config.h.in	${CMAKE_SOURCE_DIR}/inc/generated/config.h)

add_definitions(-DANTLR4CPP_STATIC)

macro(ANTLR_TARGET Name)
  # 一个相同名字的文件结构
  list(APPEND ANTLR_${Name}_INPUT
    ${CMAKE_CURRENT_SOURCE_DIR}/${Name}.g4)

  set(ANTLR_${Name}_OUTPUT_DIR
    ${CMAKE_SOURCE_DIR})

  list(APPEND ANTLR_${Name}_CXX_OUTPUTS
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Lexer.h
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Lexer.cpp
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Parser.h
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Parser.cpp
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}BaseListener.h
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}BaseListener.cpp
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Listener.h
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Listener.cpp
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Visitor.h
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Visitor.cpp
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}BaseVisitor.h
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}BaseVisitor.cpp)

  list(APPEND ANTLR_${Name}_OUTPUTS
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Lexer.interp
    ${ANTLR_${Name}_OUTPUT_DIR}/grammar/${Name}Lexer.tokens
    ${ANTLR_${Name}_CXX_OUTPUTS})

  list(APPEND ANTLR_TARGET_COMPILE_FLAGS
    -Werror -listener -visitor)

  add_custom_command(
    OUTPUT ${ANTLR_${Name}_OUTPUTS}
    COMMAND java -jar ${ANTLR_EXECUTABLE}
    -o ${ANTLR_${Name}_OUTPUT_DIR}/grammar
    -Dlanguage=Cpp
    ${ANTLR_TARGET_COMPILE_FLAGS}
    ${ANTLR_${Name}_INPUT}
    DEPENDS ${ANTLR_${Name}_INPUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building ${Name} with ANTLR")
endmacro(ANTLR_TARGET)

ANTLR_TARGET(Expr)

# 添加编译头文件
include_directories(${CMAKE_SOURCE_DIR}/grammar)
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/inc/generated)

# 添加可执行文件
add_executable(${PROJECT_NAME}
  ${CMAKE_SOURCE_DIR}/main.cc
  ${CMAKE_SOURCE_DIR}/src/proto.cc
  ${CMAKE_SOURCE_DIR}/src/option.cc
  ${CMAKE_SOURCE_DIR}/src/grammar.cc
  ${CMAKE_SOURCE_DIR}/src/semantic.cc
  ${ANTLR_RUNTIME_SRC}
  ${ANTLR_Expr_CXX_OUTPUTS})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt gtest gtest_main)

if(antlr4-runtime_FOUND)
  message(STATUS "antlr4-runtime include path is : ${antlr4-runtime_INCLUDE_DIRS}")
  message(STATUS "antlr4-runtime libraries    is : ${antlr4-runtime_LIBRARIES}")

  add_definitions(${antlr4-runtime_DEFINITIONS})
  include_directories(${antlr4-runtime_INCLUDE_DIRS})
  link_directories(${antlr4-runtime_LIBRARIES})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${antlr4-runtime_LIBRARIES})
endif(antlr4-runtime_FOUND)

# 添加boost库
find_package(Boost REQUIRED program_options system filesystem regex date_time)
if(Boost_FOUND)
  set(Boost_USE_STATIC_LIBS        ON)
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME    OFF)
  message(STATUS "boost include path is : ${Boost_INCLUDE_DIRS}")
  message(STATUS "boost library path is : ${Boost_LIBRARY_DIRS}")
  message(STATUS "boost libraries is : ${Boost_LIBRARIES}")
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
endif(Boost_FOUND)

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
endif(BUILD_DOCUMENTATION)

# 启动测试
enable_testing()

# clang-tidy
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

# 添加命令行的测试
add_test(NAME AntlrExprHelp COMMAND AntlrExpr "--help")
set_tests_properties(AntlrExprHelp PROPERTIES PASS_REGULAR_EXPRESSION "Usage: AntlrExpr")

add_test(NAME AntlrExprVersion COMMAND AntlrExpr "--version")
set_tests_properties(AntlrExprVersion PROPERTIES PASS_REGULAR_EXPRESSION "AntlrExpr")

add_test(NAME AntlrExprText_1 COMMAND AntlrExpr "1+2+3"		RETURN_VALUE 6)
add_test(NAME AntlrExprText_2 COMMAND AntlrExpr "1+2*3"		RETURN_VALUE 7)
add_test(NAME AntlrExprText_3 COMMAND AntlrExpr "(1+2*3)"	RETURN_VALUE 8)

# 设置标准安装目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# 安装
INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  )

# 打包安装包
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_GENERATOR "DEB")

# 设置包信息
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})

set(CPACK_PACKAGE_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}")

# 指定
set(CPACK_DEBIAN_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "MengDemao")
set(CPACK_PACKAGE_CONTACT "mengdemao19951021@gmail.com")
set(CPACK_SET_DESTDIR true)
set(CPACK_INSTALL_PREFIX "/usr/AntlrExpr")
set(CPACK_OUTPUT_FILE_PREFIX  ${CMAKE_CURRENT_BINARY_DIR})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtest-dev libfmt-dev libboost-all-dev")
include(CPack)
