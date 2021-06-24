<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>

#अगर_अघोषित REMOTE_UNWIND_LIBUNWIND
#समावेश <libunwind.h>
#समावेश "perf_regs.h"
#समावेश "../../../util/unwind.h"
#पूर्ण_अगर
#समावेश "../../../util/debug.h"

पूर्णांक LIBUNWIND__ARCH_REG_ID(पूर्णांक regnum)
अणु
	चयन (regnum) अणु
	हाल UNW_AARCH64_X0:
		वापस PERF_REG_ARM64_X0;
	हाल UNW_AARCH64_X1:
		वापस PERF_REG_ARM64_X1;
	हाल UNW_AARCH64_X2:
		वापस PERF_REG_ARM64_X2;
	हाल UNW_AARCH64_X3:
		वापस PERF_REG_ARM64_X3;
	हाल UNW_AARCH64_X4:
		वापस PERF_REG_ARM64_X4;
	हाल UNW_AARCH64_X5:
		वापस PERF_REG_ARM64_X5;
	हाल UNW_AARCH64_X6:
		वापस PERF_REG_ARM64_X6;
	हाल UNW_AARCH64_X7:
		वापस PERF_REG_ARM64_X7;
	हाल UNW_AARCH64_X8:
		वापस PERF_REG_ARM64_X8;
	हाल UNW_AARCH64_X9:
		वापस PERF_REG_ARM64_X9;
	हाल UNW_AARCH64_X10:
		वापस PERF_REG_ARM64_X10;
	हाल UNW_AARCH64_X11:
		वापस PERF_REG_ARM64_X11;
	हाल UNW_AARCH64_X12:
		वापस PERF_REG_ARM64_X12;
	हाल UNW_AARCH64_X13:
		वापस PERF_REG_ARM64_X13;
	हाल UNW_AARCH64_X14:
		वापस PERF_REG_ARM64_X14;
	हाल UNW_AARCH64_X15:
		वापस PERF_REG_ARM64_X15;
	हाल UNW_AARCH64_X16:
		वापस PERF_REG_ARM64_X16;
	हाल UNW_AARCH64_X17:
		वापस PERF_REG_ARM64_X17;
	हाल UNW_AARCH64_X18:
		वापस PERF_REG_ARM64_X18;
	हाल UNW_AARCH64_X19:
		वापस PERF_REG_ARM64_X19;
	हाल UNW_AARCH64_X20:
		वापस PERF_REG_ARM64_X20;
	हाल UNW_AARCH64_X21:
		वापस PERF_REG_ARM64_X21;
	हाल UNW_AARCH64_X22:
		वापस PERF_REG_ARM64_X22;
	हाल UNW_AARCH64_X23:
		वापस PERF_REG_ARM64_X23;
	हाल UNW_AARCH64_X24:
		वापस PERF_REG_ARM64_X24;
	हाल UNW_AARCH64_X25:
		वापस PERF_REG_ARM64_X25;
	हाल UNW_AARCH64_X26:
		वापस PERF_REG_ARM64_X26;
	हाल UNW_AARCH64_X27:
		वापस PERF_REG_ARM64_X27;
	हाल UNW_AARCH64_X28:
		वापस PERF_REG_ARM64_X28;
	हाल UNW_AARCH64_X29:
		वापस PERF_REG_ARM64_X29;
	हाल UNW_AARCH64_X30:
		वापस PERF_REG_ARM64_LR;
	हाल UNW_AARCH64_SP:
		वापस PERF_REG_ARM64_SP;
	हाल UNW_AARCH64_PC:
		वापस PERF_REG_ARM64_PC;
	शेष:
		pr_err("unwind: invalid reg id %d\n", regnum);
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण
