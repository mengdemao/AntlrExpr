#!/bin/bash

ROOT_PATH=$(pwd)
BUILD_DIR=${ROOT_PATH}/build

if [ ! -d ${BUILD_DIR} ];
then
	mkdir -p ${BUILD_DIR}
fi

cmake -DCMAKE_CXX_CPPCHECK:FILEPATH=cppcheck \
	  -DCMAKE_CXX_CPPLINT:FILEPATH=cpplint	 \
	  -DCMAKE_CXX_CLANG_TIDY:FILEPATH=clang-tidy \
	  -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE:FILEPATH=include-what-you-use \
	  -B ${BUILD_DIR} -DCMAKE_BUILD_TYPE=Debug -G Ninja

cmake --build ${BUILD_DIR} --config Debug -j $(nproc)

ln -sf ${BUILD_DIR}/compile_commands.json

# 执行静态分析 https://github.com/facebook/infer.git
infer run --compilation-database ${ROOT_PATH}/compile_commands.json -o ${BUILD_DIR}/infer_out
