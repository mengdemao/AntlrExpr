cmake_minimum_required(VERSION 3.10)

project(AntlrExpr C CXX)

include(CTest)
include(FetchContent)
include(ProcessorCount)
include(GNUInstallDirs)
include(ExternalProject)

# 添加外部软件
find_package(Boost REQUIRED program_options system filesystem regex date_time) 
find_package(Doxygen REQUIRED)
find_package(Git REQUIRED)
find_package(LLVM REQUIRED)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
find_package(fmt REQUIRED)

# 检查编译器
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)
include(CheckCXXSymbolExists)
include(CheckFunctionExists)
include(CheckIncludeFileCXX)
include(CheckLibraryExists)
include(CheckStructHasMember)
include(CheckTypeSize)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置优化选项
set(CMAKE_C_FLAGS_DEBUG "-O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -flto")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto")

# 显示详细信息
set (CMAKE_VERBOSE_MAKEFILE ON)

# 设置默认编译类型
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# 设置默认的并行编译
ProcessorCount(N)
if(NOT N EQUAL 0)
  set(CTEST_BUILD_FLAGS -j${N})
  set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${N})
  set(CMAKE_MAKE_PROGRAM"${CMAKE_MAKE_PROGRAM} -j ${N}")
endif()

check_include_file_cxx (dlfcn.h HAVE_DLFCN_H)
check_include_file_cxx (execinfo.h HAVE_EXECINFO_H)
check_include_file_cxx (glob.h HAVE_GLOB_H)
check_include_file_cxx (inttypes.h HAVE_INTTYPES_H)
check_include_file_cxx (memory.h HAVE_MEMORY_H)
check_include_file_cxx (pwd.h HAVE_PWD_H)
check_include_file_cxx (stdint.h HAVE_STDINT_H)
check_include_file_cxx (strings.h HAVE_STRINGS_H)
check_include_file_cxx (sys/stat.h HAVE_SYS_STAT_H)
check_include_file_cxx (sys/syscall.h HAVE_SYS_SYSCALL_H)
check_include_file_cxx (sys/time.h HAVE_SYS_TIME_H)
check_include_file_cxx (sys/types.h HAVE_SYS_TYPES_H)
check_include_file_cxx (sys/utsname.h HAVE_SYS_UTSNAME_H)
check_include_file_cxx (sys/wait.h HAVE_SYS_WAIT_H)
check_include_file_cxx (syscall.h HAVE_SYSCALL_H)
check_include_file_cxx (ucontext.h HAVE_UCONTEXT_H)
check_include_file_cxx (unistd.h HAVE_UNISTD_H)

check_include_file_cxx ("ext/hash_map" HAVE_EXT_HASH_MAP)
check_include_file_cxx ("ext/hash_set" HAVE_EXT_HASH_SET)
check_include_file_cxx ("ext/slist" HAVE_EXT_SLIST)
check_include_file_cxx ("tr1/unordered_map" HAVE_TR1_UNORDERED_MAP)
check_include_file_cxx ("tr1/unordered_set" HAVE_TR1_UNORDERED_SET)
check_include_file_cxx ("unordered_map" HAVE_UNORDERED_MAP)
check_include_file_cxx ("unordered_set" HAVE_UNORDERED_SET)

check_type_size ("unsigned __int16" HAVE___UINT16 LANGUAGE CXX)
check_type_size (u_int16_t HAVE_U_INT16_T LANGUAGE CXX)
check_type_size (uint16_t HAVE_UINT16_T LANGUAGE CXX)

check_function_exists(dladdr HAVE_DLADDR)
check_function_exists(fcntl HAVE_FCNTL)
check_function_exists(pread HAVE_PREAD)
check_function_exists(pwrite HAVE_PWRITE)
check_function_exists(sigaction HAVE_SIGACTION)
check_function_exists(sigaltstack HAVE_SIGALTSTACK)

check_cxx_compiler_flag(-Wdeprecated HAVE_NO_DEPRECATED)
check_cxx_compiler_flag(-Wunnamed-type-template-args
    HAVE_NO_UNNAMED_TYPE_TEMPLATE_ARGS)
    
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(CMakePushCheckState)

check_cxx_source_compiles ("
#include <cstdlib>
static void foo(void) __attribute__ ((unused));
int main(void) { return 0; }
" HAVE___ATTRIBUTE__)

check_cxx_source_compiles ("
#include <cstdlib>
static void foo(void) __attribute__ ((visibility(\"default\")));
int main(void) { return 0; }
" HAVE___ATTRIBUTE__VISIBILITY_DEFAULT)

check_cxx_source_compiles ("
#include <cstdlib>
static void foo(void) __attribute__ ((visibility(\"hidden\")));
int main(void) { return 0; }
" HAVE___ATTRIBUTE__VISIBILITY_HIDDEN)

check_cxx_source_compiles ("
int main(void) { if (__builtin_expect(0, 0)) return 1; return 0; }
" HAVE___BUILTIN_EXPECT)

check_cxx_source_compiles ("
int main(void)
{
  int a; if (__sync_val_compare_and_swap(&a, 0, 1)) return 1; return 0;
}
" HAVE___SYNC_VAL_COMPARE_AND_SWAP)

cmake_push_check_state (RESET)
set (CMAKE_REQUIRED_LIBRARIES Threads::Threads)
check_cxx_source_compiles ("
#define _XOPEN_SOURCE 500
#include <pthread.h>
int main(void)
{
  pthread_rwlock_t l;
  pthread_rwlock_init(&l, NULL);
  pthread_rwlock_rdlock(&l);
  return 0;
}
" HAVE_RWLOCK)
cmake_pop_check_state ()

check_cxx_source_compiles ("
__declspec(selectany) int a;
int main(void) { return 0; }
" HAVE___DECLSPEC)

check_cxx_source_compiles ("
#include <vector>
vector<int> t; int main() { }
" STL_NO_NAMESPACE)

check_cxx_source_compiles ("
#include <vector>
std::vector<int> t; int main() { }
" STL_STD_NAMESPACE)

check_cxx_source_compiles ("
#include <iostream>
std::ostream& operator<<(std::ostream&, struct s);
using ::operator<<;
int main() { }
" HAVE_USING_OPERATOR)

check_cxx_source_compiles ("
namespace Outer { namespace Inner { int i = 0; }}
using namespace Outer::Inner;;
int main() { return i; }
" HAVE_NAMESPACES)

check_cxx_source_compiles ("
__thread int tls;
int main() { }
" HAVE_GCC_TLS)

check_cxx_source_compiles ("
__declspec(thread) int tls;
int main() { }
" HAVE_MSVC_TLS)

check_cxx_source_compiles ("
thread_local int tls;
int main() { }
" HAVE_CXX20_TLS)

check_cxx_source_compiles ("
#include <type_traits>
std::aligned_storage<sizeof(char), alignof(char)>::type data;
int main() { }
" HAVE_ALIGNED_STORAGE)

check_cxx_source_compiles ("
#include <atomic>
std::atomic<int> i;
int main() { }
" HAVE_CXX20_ATOMIC)

check_cxx_source_compiles ("
constexpr int x = 0;
int main() { }
" HAVE_CXX20_CONSTEXPR)

check_cxx_source_compiles ("
#include <chrono>
std::chrono::seconds s;
int main() { }
" HAVE_CXX20_CHRONO)

check_cxx_source_compiles ("
#include <cstddef>
void foo(std::nullptr_t) {}
int main(void) { foo(nullptr); }
" HAVE_CXX20_NULLPTR_T)

# 添加LLVM相关库
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# 添加gtest库
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${FMT_INCLUDE_DIRS})

# 添加boost库
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

if(Boost_FOUND)
    message(STATUS "boost include path is : ${Boost_INCLUDE_DIRS}")
    message(STATUS "boost library path is : ${Boost_LIBRARY_DIRS}")
    message(STATUS "boost libraries is : ${Boost_LIBRARIES}")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

if(LLVM_FOUND)
    message(STATUS "llvm include path is : ${LLVM_INCLUDE_DIRS}")
    message(STATUS "llvm library path is : ${LLVM_LIBRARY_DIRS}")
    add_definitions(${LLVM_DEFINITIONS})
    include_directories(${LLVM_INCLUDE_DIRS})
    link_directories(${LLVM_LIBRARY_DIRS})
endif(LLVM_FOUND)

# 设置编译工具
set(ANTLR_EXECUTABLE ${CMAKE_SOURCE_DIR}/bin/antlr-complete.jar)

# 添加编译选项
add_compile_options(
	-Wall
	-Werror
	-pedantic
	-Wno-unused-parameter
	-Wpointer-arith
	-Wwrite-strings
	-march=native
)

# Clang
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
add_compile_options(
  -Wno-dollar-in-identifier-extension
)
endif()

# Gcc
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Gnu")
add_compile_options(
  -rdynamic
)
endif()

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

option(DEBUG_EXPR_ENABLE "print expr debug" ON)
if(DEBUG_EXPR_ENABLE)
	set(DEBUG_EXPR 1)
endif(DEBUG_EXPR_ENABLE)

# 生成配置文件
configure_file(${CMAKE_SOURCE_DIR}/inc/version.h.in ${CMAKE_SOURCE_DIR}/inc/generated/version.h)
configure_file(${CMAKE_SOURCE_DIR}/inc/config.h.in ${CMAKE_SOURCE_DIR}/inc/generated/config.h)

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

# 添加链接文件路径
link_directories(${Boost_LIBRARY_DIRS})

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

# Disable warning C4819
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 添加可执行文件
add_executable(${PROJECT_NAME}
			   ${CMAKE_SOURCE_DIR}/main.cc
			   ${CMAKE_SOURCE_DIR}/src/ast.cc
			   ${CMAKE_SOURCE_DIR}/src/svm.cc
			   ${CMAKE_SOURCE_DIR}/src/test.cc
         ${CMAKE_SOURCE_DIR}/src/llvm.cc
			   ${CMAKE_SOURCE_DIR}/src/option.cc
			   ${CMAKE_SOURCE_DIR}/src/grammar.cc
			   ${ANTLR_RUNTIME_SRC}
			   ${ANTLR_Expr_CXX_OUTPUTS})


# 添加LLVM库
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

set(TARGETS_TO_BUILD "WebAssembly" "XCore" "SystemZ" "Sparc" "RISCV" "PowerPC" "NVPTX" "MSP430" "Mips" "Lanai" "Hexagon" "BPF" "ARM" "AMDGPU" "X86" "AArch64" "AVR")

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

target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} fmt::fmt ${GTEST_BOTH_LIBRARIES} ${llvm_libs})

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

add_test(NAME AntlrExprText_1 COMMAND AntlrExpr "1+2+3" 	RETURN_VALUE 6)
add_test(NAME AntlrExprText_2 COMMAND AntlrExpr "1+2*3" 	RETURN_VALUE 7)
add_test(NAME AntlrExprText_3 COMMAND AntlrExpr "(1+2*3)" 	RETURN_VALUE 8)

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
