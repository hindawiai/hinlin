<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <त्रुटिसं.स>
#समावेश <libunwind.h>
#समावेश "perf_regs.h"
#समावेश "../../util/unwind.h"
#समावेश "util/debug.h"

पूर्णांक libunwind__arch_reg_id(पूर्णांक regnum)
अणु
	चयन (regnum) अणु
	हाल UNW_MIPS_R1 ... UNW_MIPS_R25:
		वापस regnum - UNW_MIPS_R1 + PERF_REG_MIPS_R1;
	हाल UNW_MIPS_R28 ... UNW_MIPS_R31:
		वापस regnum - UNW_MIPS_R28 + PERF_REG_MIPS_R28;
	हाल UNW_MIPS_PC:
		वापस PERF_REG_MIPS_PC;
	शेष:
		pr_err("unwind: invalid reg id %d\n", regnum);
		वापस -EINVAL;
	पूर्ण
पूर्ण
