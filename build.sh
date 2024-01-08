#!/bin/bash

ROOT_PATH=$(pwd)
BUILD_DIR=${ROOT_PATH}/build

if [ ! -d ${BUILD_DIR} ];
then
	mkdir -p ${BUILD_DIR}
fi

log_err() {
	local logTime="$(date -d today +'%Y-%m-%d %H:%M:%S')"
	printf "\033[0;31m[ERROR][${logTime}][${FUNCNAME[1]}] $*\r\n\033[0m"
}

log_warn() {
	local logTime="$(date -d today +'%Y-%m-%d %H:%M:%S')"
	printf "\033[0;33m[WARN][${logTime}][${FUNCNAME[1]}] $*\r\n\033[0m"
}

log_info() {
	local logTime="$(date -d today +'%Y-%m-%d %H:%M:%S')"
	printf "\033[0;32m[INFO][${logTime}][${FUNCNAME[1]}] $*\r\n\033[0m"
}

check_config() {
	local BUILD_TYPE=$1
	if [[ ${BUILD_TYPE} != "Debug" && ${BUILD_TYPE} != "Release" ]]; then
		log_err "输入参数错误"
		log_err "请输入Debug或者Release"
		return 1
	fi

	return 0
}

conan_config() {
	local BUILD_TYPE=$1
	check_config ${BUILD_TYPE} || exit 1

	log_info "配置conan"
	conan install conanfile.txt --build=missing -s build_type=${BUILD_TYPE} || exit 1
}

cmake_preset()
{
	local BUILD_TYPE=$1
	check_config ${BUILD_TYPE} || exit 1

	if [ ${BUILD_TYPE} == "Debug" ]; then
		cmake --preset conan-debug || exit 1
	elif [ ${BUILD_TYPE} == "Release" ]; then
		cmake --preset conan-release || exit 1
	fi
}

do_infer()
{
	# 执行静态分析 https://github.com/facebook/infer.git
	infer run --compilation-database ${ROOT_PATH}/compile_commands.json -o ${BUILD_DIR}/infer_out
}

usage() {
	log_err "输入参数错误"
	log_err "请输入Debug或者Release"
}

#############################################
#               构建脚本起点                 #
#############################################
BUILD_TYPE="Debug"
BUILD_CHECK=0

# 判断输入参数个数
if [ $# == 0 ]; then
	usage
	exit 1
fi

# 解析输入参数
ARGS=$(getopt -o c:x -l config:,lint -- "$@")
if [ $? != 0 ]; then
	log_err "args parse error" >&2
	exit 1
fi

# 展开输入
eval set -- "${ARGS}"
while true; do
	case "${1}" in
	-c | --config)
		BUILD_TYPE=${2}
		shift 2
		;;

	-x | --lint)
	   BUILD_CHECK=1
	   shift 1
	   ;;

	--)
		shift
		break
		;;

	*)
		usage
		exit
		;;
	esac
done

check_config ${BUILD_TYPE} || exit 1
conan_config ${BUILD_TYPE} || exit 1
cmake_preset ${BUILD_TYPE} || exit 1

ln -sf ${BUILD_DIR}/compile_commands.json

cmake -DCMAKE_TOOLCHAIN_FILE="${ROOT_PATH}"/build/"${BUILD_TYPE}"/generators/conan_toolchain.cmake \
	  -B ${BUILD_DIR} -DCMAKE_BUILD_TYPE=${BUILD_TYPE}

cmake --build ${BUILD_DIR} --config ${BUILD_TYPE} -j $(nproc)

if [ ${BUILD_CHECK} == 1 ]; then
	do_infer
fi
