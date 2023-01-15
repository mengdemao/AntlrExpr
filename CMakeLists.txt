cmake_minimum_required(VERSION 3.10)

project(AntlrExpr C CXX)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_SOURCE_DIR}/cmake)

include(CTest)
include(ProcessorCount)
include(GNUInstallDirs)
include(Compiler)

# 添加外部软件
find_package(Threads REQUIRED)
find_package(Doxygen REQUIRED)
find_package(LLVM REQUIRED)
find_package(Git REQUIRED)

# 设置编译工具
set(ANTLR_EXECUTABLE ${CMAKE_SOURCE_DIR}/bin/antlr-complete.jar)

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

# 三方库
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# 添加头文件路径
include_directories(${CMAKE_SOURCE_DIR}/inc/generated)
include_directories(${CMAKE_SOURCE_DIR}/grammar)
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${Boost_INCLUDE_DIRS})
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

# 添加可执行文件
add_executable(${PROJECT_NAME}
  ${CMAKE_SOURCE_DIR}/main.cc
  ${CMAKE_SOURCE_DIR}/src/proto.cc
  ${CMAKE_SOURCE_DIR}/src/llvm.cc
  ${CMAKE_SOURCE_DIR}/src/option.cc
  ${CMAKE_SOURCE_DIR}/src/grammar.cc
  ${CMAKE_SOURCE_DIR}/src/semantic.cc
  ${ANTLR_RUNTIME_SRC}
  ${ANTLR_Expr_CXX_OUTPUTS})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt gtest gtest_main)

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

# 添加LLVM库
if(LLVM_FOUND)
  message(STATUS "llvm include path is : ${LLVM_INCLUDE_DIRS}")
  message(STATUS "llvm library path is : ${LLVM_LIBRARY_DIRS}")
  add_definitions(${LLVM_DEFINITIONS})
  include_directories(${LLVM_INCLUDE_DIRS})
  link_directories(${LLVM_LIBRARY_DIRS})

  set(TARGET_WebAssembly WebAssemblyCodeGen WebAssemblyAsmParser WebAssemblyDesc WebAssemblyInfo)
  set(TARGET_XCore XCoreCodeGen XCoreDesc XCoreInfo)
  set(TARGET_SystemZ SystemZCodeGen SystemZAsmParser SystemZDesc SystemZInfo)
  set(TARGET_Sparc SparcCodeGen SparcAsmParser SparcDesc SparcInfo)
  set(TARGET_RISCV RISCVCodeGen RISCVAsmParser RISCVDesc RISCVInfo)
  set(TARGET_PowerPC PowerPCCodeGen PowerPCAsmParser PowerPCDesc PowerPCInfo)
  set(TARGET_NVPTX NVPTXCodeGen NVPTXDesc NVPTXInfo)
  set(TARGET_MSP430 MSP430CodeGen MSP430AsmParser MSP430Desc MSP430Info)
  set(TARGET_Mips MipsCodeGen MipsAsmParser MipsDesc MipsInfo)
  set(TARGET_Lanai LanaiCodeGen LanaiAsmParser LanaiDesc LanaiInfo)
  set(TARGET_Hexagon HexagonCodeGen HexagonAsmParser HexagonDesc HexagonInfo)
  set(TARGET_BPF BPFCodeGen BPFAsmParser BPFDesc BPFInfo)
  set(TARGET_ARM ARMCodeGen ARMAsmParser ARMDesc ARMUtils ARMInfo)
  set(TARGET_AMDGPU AMDGPUCodeGen AMDGPUAsmParser AMDGPUDesc AMDGPUUtils AMDGPUInfo)
  set(TARGET_X86 X86CodeGen X86AsmParser X86Desc X86Info)
  set(TARGET_AArch64 AArch64CodeGen AArch64AsmParser AArch64Desc AArch64Utils AArch64Info)
  set(TARGET_AVR AVRCodeGen AVRAsmParser AVRDesc AVRInfo)
  set(TARGET_VE VECodeGen VEAsmParser VEDesc VEInfo)
  set(TARGET_M68K M68KCodeGen M68KAsmParser M68KDesc M68KInfo)
  set(TARGETS_TO_BUILD "WebAssembly" "XCore" "SystemZ" "Sparc" "RISCV" "PowerPC" "NVPTX" "MSP430" "Mips" "Lanai" "Hexagon" "BPF" "ARM" "AMDGPU" "X86" "AArch64" "AVR" "VE" "M68K")

  set(LLVM_TARGETS)
  foreach (target IN ITEMS ${TARGETS_TO_BUILD})
    list(APPEND LLVM_TARGETS "${TARGET_${target}}")
  endforeach(target)

  llvm_map_components_to_libnames(llvm_libs
    TextAPI
    OrcJIT
    JITLink
    ObjectYAML
    WindowsManifest
    Coverage
    TableGen
    LTO
    Passes
    ObjCARCOpts
    Coroutines
    LibDriver
    XRay
    ${LLVM_TARGETS}
    MIRParser
    ipo
    Instrumentation
    Vectorize
    Linker
    IRReader
    AsmParser
    Symbolize
    DebugInfoPDB
    FuzzMutate
    LineEditor
    MCA
    DebugInfoGSYM
    GlobalISel
    SelectionDAG
    AsmPrinter
    DebugInfoDWARF
    MCJIT
    Interpreter
    ExecutionEngine
    RuntimeDyld
    CodeGen
    Target
    ScalarOpts
    InstCombine
    AggressiveInstCombine
    TransformUtils
    BitWriter
    Analysis
    ProfileData
    DlltoolDriver
    Option
    Object
    MCParser
    MC
    DebugInfoCodeView
    DebugInfoMSF
    BitReader
    Core
    Remarks
    BinaryFormat
    BitstreamReader
    Support
    Demangle
    )
  target_link_libraries(${PROJECT_NAME} PRIVATE ${llvm_libs})
endif(LLVM_FOUND)

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
