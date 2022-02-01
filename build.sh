#!/bin/bash

ROOT_PATH=`pwd`
BUILD_DIR=${ROOT_PATH}/build

if [ ! -d ${BUILD_DIR} ];
then
	mkdir -p ${BUILD_DIR}
fi

cmake -DCMAKE_CXX_CPPCHECK:FILEPATH=cppcheck -B ${BUILD_DIR} -DCMAKE_BUILD_TYPE=Debug

cmake --build ${BUILD_DIR} --config Debug

ln -sf ${BUILD_DIR}/compile_commands.json

# 执行静态分析 https://github.com/facebook/infer.git
infer run --compilation-database ${ROOT_PATH}/compile_commands.json -o ${BUILD_DIR}/infer_out
