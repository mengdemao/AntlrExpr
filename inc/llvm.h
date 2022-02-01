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
#ifndef __LLVM_H__
#define __LLVM_H__
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/TargetSelect.h>
#include <memory>
#include <string>
#include <type_traits>

class scope
{
  private:

	std::unordered_map<std::string, llvm::Value*> variables;
	llvm::Function* current_function = nullptr;
  
  public:

	scope(llvm::Function* pcurrent_function = nullptr) : current_function(pcurrent_function) 
	{
		/* No Body */
	}

	llvm::Value* set_variable(const std::string& name, llvm::Value*);
	llvm::Value* get_variable(const std::string& name);
};

class jit
{
private:
    std::unique_ptr<llvm::orc::LLJIT> lljit;

public:
    jit(std::unique_ptr<llvm::orc::LLJIT> lljit) : lljit(std::move(lljit))
    {
        /* No Body */
    }

    template <typename T, typename = std::enable_if_t<std::is_pointer<T>::value && std::is_function<std::remove_pointer_t<T>>::value>>
    llvm::Expected<T> lookup(const std::string &name)
    {
        auto symbol = this->lljit->lookup(name);

        if (!symbol)
        {
            return symbol.takeError();
        }

        return (T)symbol.get().getAddress();
    }

    template <typename T, typename = std::enable_if_t<std::is_function<T>::value>>
    inline llvm::Expected<T *> lookup(const std::string &name)
    {
        return this->lookup<T *>(name);
    }

    static llvm::Expected<jit> create(std::unique_ptr<llvm::Module> &module, std::unique_ptr<llvm::LLVMContext> &context)
    {
        auto lljit = llvm::orc::LLJITBuilder().create();
        auto &jd = lljit.get()->getMainJITDylib();

        jd.addGenerator(llvm::cantFail(llvm::orc::DynamicLibrarySearchGenerator::GetForCurrentProcess('_')));

        if (!lljit)
        {
            return lljit.takeError();
        }

        if (auto err = lljit.get()->addIRModule(llvm::orc::ThreadSafeModule(std::move(module), std::move(context))))
        {
            return std::move(err);
        }

        return jit(std::move(lljit.get()));
    }
};

void llvm_init(void);

#endif /* __LLVM_H__ */