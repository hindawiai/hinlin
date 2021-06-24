<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <त्रुटिसं.स>
#समावेश "../../util/debug.h"
#अगर_अघोषित REMOTE_UNWIND_LIBUNWIND
#समावेश <libunwind.h>
#समावेश "perf_regs.h"
#समावेश "../../util/unwind.h"
#पूर्ण_अगर

#अगर_घोषित HAVE_ARCH_X86_64_SUPPORT
पूर्णांक LIBUNWIND__ARCH_REG_ID(पूर्णांक regnum)
अणु
	पूर्णांक id;

	चयन (regnum) अणु
	हाल UNW_X86_64_RAX:
		id = PERF_REG_X86_AX;
		अवरोध;
	हाल UNW_X86_64_RDX:
		id = PERF_REG_X86_DX;
		अवरोध;
	हाल UNW_X86_64_RCX:
		id = PERF_REG_X86_CX;
		अवरोध;
	हाल UNW_X86_64_RBX:
		id = PERF_REG_X86_BX;
		अवरोध;
	हाल UNW_X86_64_RSI:
		id = PERF_REG_X86_SI;
		अवरोध;
	हाल UNW_X86_64_RDI:
		id = PERF_REG_X86_DI;
		अवरोध;
	हाल UNW_X86_64_RBP:
		id = PERF_REG_X86_BP;
		अवरोध;
	हाल UNW_X86_64_RSP:
		id = PERF_REG_X86_SP;
		अवरोध;
	हाल UNW_X86_64_R8:
		id = PERF_REG_X86_R8;
		अवरोध;
	हाल UNW_X86_64_R9:
		id = PERF_REG_X86_R9;
		अवरोध;
	हाल UNW_X86_64_R10:
		id = PERF_REG_X86_R10;
		अवरोध;
	हाल UNW_X86_64_R11:
		id = PERF_REG_X86_R11;
		अवरोध;
	हाल UNW_X86_64_R12:
		id = PERF_REG_X86_R12;
		अवरोध;
	हाल UNW_X86_64_R13:
		id = PERF_REG_X86_R13;
		अवरोध;
	हाल UNW_X86_64_R14:
		id = PERF_REG_X86_R14;
		अवरोध;
	हाल UNW_X86_64_R15:
		id = PERF_REG_X86_R15;
		अवरोध;
	हाल UNW_X86_64_RIP:
		id = PERF_REG_X86_IP;
		अवरोध;
	शेष:
		pr_err("unwind: invalid reg id %d\n", regnum);
		वापस -EINVAL;
	पूर्ण

	वापस id;
पूर्ण
#अन्यथा
पूर्णांक LIBUNWIND__ARCH_REG_ID(पूर्णांक regnum)
अणु
	पूर्णांक id;

	चयन (regnum) अणु
	हाल UNW_X86_EAX:
		id = PERF_REG_X86_AX;
		अवरोध;
	हाल UNW_X86_EDX:
		id = PERF_REG_X86_DX;
		अवरोध;
	हाल UNW_X86_ECX:
		id = PERF_REG_X86_CX;
		अवरोध;
	हाल UNW_X86_EBX:
		id = PERF_REG_X86_BX;
		अवरोध;
	हाल UNW_X86_ESI:
		id = PERF_REG_X86_SI;
		अवरोध;
	हाल UNW_X86_EDI:
		id = PERF_REG_X86_DI;
		अवरोध;
	हाल UNW_X86_EBP:
		id = PERF_REG_X86_BP;
		अवरोध;
	हाल UNW_X86_ESP:
		id = PERF_REG_X86_SP;
		अवरोध;
	हाल UNW_X86_EIP:
		id = PERF_REG_X86_IP;
		अवरोध;
	शेष:
		pr_err("unwind: invalid reg id %d\n", regnum);
		वापस -EINVAL;
	पूर्ण

	वापस id;
पूर्ण
#पूर्ण_अगर /* HAVE_ARCH_X86_64_SUPPORT */
