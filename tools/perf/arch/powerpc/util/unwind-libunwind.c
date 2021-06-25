<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016 Chandan Kumar, IBM Corporation.
 */

#समावेश <त्रुटिसं.स>
#समावेश <libunwind.h>
#समावेश <यंत्र/perf_regs.h>
#समावेश "../../util/unwind.h"
#समावेश "../../util/debug.h"

पूर्णांक libunwind__arch_reg_id(पूर्णांक regnum)
अणु
	चयन (regnum) अणु
	हाल UNW_PPC64_R0:
		वापस PERF_REG_POWERPC_R0;
	हाल UNW_PPC64_R1:
		वापस PERF_REG_POWERPC_R1;
	हाल UNW_PPC64_R2:
		वापस PERF_REG_POWERPC_R2;
	हाल UNW_PPC64_R3:
		वापस PERF_REG_POWERPC_R3;
	हाल UNW_PPC64_R4:
		वापस PERF_REG_POWERPC_R4;
	हाल UNW_PPC64_R5:
		वापस PERF_REG_POWERPC_R5;
	हाल UNW_PPC64_R6:
		वापस PERF_REG_POWERPC_R6;
	हाल UNW_PPC64_R7:
		वापस PERF_REG_POWERPC_R7;
	हाल UNW_PPC64_R8:
		वापस PERF_REG_POWERPC_R8;
	हाल UNW_PPC64_R9:
		वापस PERF_REG_POWERPC_R9;
	हाल UNW_PPC64_R10:
		वापस PERF_REG_POWERPC_R10;
	हाल UNW_PPC64_R11:
		वापस PERF_REG_POWERPC_R11;
	हाल UNW_PPC64_R12:
		वापस PERF_REG_POWERPC_R12;
	हाल UNW_PPC64_R13:
		वापस PERF_REG_POWERPC_R13;
	हाल UNW_PPC64_R14:
		वापस PERF_REG_POWERPC_R14;
	हाल UNW_PPC64_R15:
		वापस PERF_REG_POWERPC_R15;
	हाल UNW_PPC64_R16:
		वापस PERF_REG_POWERPC_R16;
	हाल UNW_PPC64_R17:
		वापस PERF_REG_POWERPC_R17;
	हाल UNW_PPC64_R18:
		वापस PERF_REG_POWERPC_R18;
	हाल UNW_PPC64_R19:
		वापस PERF_REG_POWERPC_R19;
	हाल UNW_PPC64_R20:
		वापस PERF_REG_POWERPC_R20;
	हाल UNW_PPC64_R21:
		वापस PERF_REG_POWERPC_R21;
	हाल UNW_PPC64_R22:
		वापस PERF_REG_POWERPC_R22;
	हाल UNW_PPC64_R23:
		वापस PERF_REG_POWERPC_R23;
	हाल UNW_PPC64_R24:
		वापस PERF_REG_POWERPC_R24;
	हाल UNW_PPC64_R25:
		वापस PERF_REG_POWERPC_R25;
	हाल UNW_PPC64_R26:
		वापस PERF_REG_POWERPC_R26;
	हाल UNW_PPC64_R27:
		वापस PERF_REG_POWERPC_R27;
	हाल UNW_PPC64_R28:
		वापस PERF_REG_POWERPC_R28;
	हाल UNW_PPC64_R29:
		वापस PERF_REG_POWERPC_R29;
	हाल UNW_PPC64_R30:
		वापस PERF_REG_POWERPC_R30;
	हाल UNW_PPC64_R31:
		वापस PERF_REG_POWERPC_R31;
	हाल UNW_PPC64_LR:
		वापस PERF_REG_POWERPC_LINK;
	हाल UNW_PPC64_CTR:
		वापस PERF_REG_POWERPC_CTR;
	हाल UNW_PPC64_XER:
		वापस PERF_REG_POWERPC_XER;
	हाल UNW_PPC64_NIP:
		वापस PERF_REG_POWERPC_NIP;
	शेष:
		pr_err("unwind: invalid reg id %d\n", regnum);
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण
