<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Some parts derived from x86 version of this file.
 *
 * Copyright (C) 2013 Cavium, Inc.
 */

#समावेश <linux/perf_event.h>

#समावेश <यंत्र/ptrace.h>

#अगर_घोषित CONFIG_32BIT
u64 perf_reg_abi(काष्ठा task_काष्ठा *tsk)
अणु
	वापस PERF_SAMPLE_REGS_ABI_32;
पूर्ण
#अन्यथा /* Must be CONFIG_64BIT */
u64 perf_reg_abi(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (test_tsk_thपढ़ो_flag(tsk, TIF_32BIT_REGS))
		वापस PERF_SAMPLE_REGS_ABI_32;
	अन्यथा
		वापस PERF_SAMPLE_REGS_ABI_64;
पूर्ण
#पूर्ण_अगर /* CONFIG_32BIT */

पूर्णांक perf_reg_validate(u64 mask)
अणु
	अगर (!mask)
		वापस -EINVAL;
	अगर (mask & ~((1ull << PERF_REG_MIPS_MAX) - 1))
		वापस -EINVAL;
	वापस 0;
पूर्ण

u64 perf_reg_value(काष्ठा pt_regs *regs, पूर्णांक idx)
अणु
	दीर्घ v;

	चयन (idx) अणु
	हाल PERF_REG_MIPS_PC:
		v = regs->cp0_epc;
		अवरोध;
	हाल PERF_REG_MIPS_R1 ... PERF_REG_MIPS_R25:
		v = regs->regs[idx - PERF_REG_MIPS_R1 + 1];
		अवरोध;
	हाल PERF_REG_MIPS_R28 ... PERF_REG_MIPS_R31:
		v = regs->regs[idx - PERF_REG_MIPS_R28 + 28];
		अवरोध;

	शेष:
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	वापस (s64)v; /* Sign extend अगर 32-bit. */
पूर्ण

व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
			काष्ठा pt_regs *regs)
अणु
	regs_user->regs = task_pt_regs(current);
	regs_user->abi = perf_reg_abi(current);
पूर्ण
