<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_UTIL_CLANG_H
#घोषणा PERF_UTIL_CLANG_H

#समावेश "llvm/ADT/StringRef.h"
#समावेश "llvm/IR/LLVMContext.h"
#समावेश "llvm/IR/Module.h"
#समावेश "llvm/Option/Option.h"
#समावेश <memory>

namespace perf अणु

using namespace llvm;

std::unique_ptr<Module>
getModuleFromSource(opt::ArgStringList CFlags,
		    StringRef Name, StringRef Content);

std::unique_ptr<Module>
getModuleFromSource(opt::ArgStringList CFlags,
		    StringRef Path);

std::unique_ptr<llvm::SmallVectorImpl<अक्षर>>
getBPFObjectFromModule(llvm::Module *Module);

पूर्ण
#पूर्ण_अगर
