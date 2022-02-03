/**
 * @file llvm.cc
 * @author mengdemao (mengdemao19951021@163.com)
 * @version 1.0
 * @date 2022-01-30
 *
 * @brief LLVM接口封装
 *
 * @copyright Copyright (c) 2022  mengdemao
 *
 */
#include <cassert>
#include <llvm/Support/TargetSelect.h>
#include <exception>
#include <gtest/gtest.h>
#include <iostream>
#include <llvm.h>
#include <vector>

/**
 * @brief LLVM相关库的初始化
 */
void llvm_init(void)
{
	llvm::InitializeAllTargetInfos();
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmParsers();
	llvm::InitializeAllAsmPrinters();
}

llvm::Value* scope::set_variable(const std::string& name, llvm::Value* value)
{
	this->variables[name] = value;
	return value;
}

llvm::Value* scope::get_variable(const std::string& name)
{
	return this->variables.at(name);
}