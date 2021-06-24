<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <त्रुटिसं.स>
#समावेश <libunwind.h>
#समावेश "perf_regs.h"
#समावेश "../../util/unwind.h"
#समावेश "../../util/debug.h"

पूर्णांक libunwind__arch_reg_id(पूर्णांक regnum)
अणु
	चयन (regnum) अणु
	हाल UNW_ARM_R0:
		वापस PERF_REG_ARM_R0;
	हाल UNW_ARM_R1:
		वापस PERF_REG_ARM_R1;
	हाल UNW_ARM_R2:
		वापस PERF_REG_ARM_R2;
	हाल UNW_ARM_R3:
		वापस PERF_REG_ARM_R3;
	हाल UNW_ARM_R4:
		वापस PERF_REG_ARM_R4;
	हाल UNW_ARM_R5:
		वापस PERF_REG_ARM_R5;
	हाल UNW_ARM_R6:
		वापस PERF_REG_ARM_R6;
	हाल UNW_ARM_R7:
		वापस PERF_REG_ARM_R7;
	हाल UNW_ARM_R8:
		वापस PERF_REG_ARM_R8;
	हाल UNW_ARM_R9:
		वापस PERF_REG_ARM_R9;
	हाल UNW_ARM_R10:
		वापस PERF_REG_ARM_R10;
	हाल UNW_ARM_R11:
		वापस PERF_REG_ARM_FP;
	हाल UNW_ARM_R12:
		वापस PERF_REG_ARM_IP;
	हाल UNW_ARM_R13:
		वापस PERF_REG_ARM_SP;
	हाल UNW_ARM_R14:
		वापस PERF_REG_ARM_LR;
	हाल UNW_ARM_R15:
		वापस PERF_REG_ARM_PC;
	शेष:
		pr_err("unwind: invalid reg id %d\n", regnum);
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण
