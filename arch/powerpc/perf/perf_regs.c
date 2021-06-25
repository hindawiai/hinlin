<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016 Anju T, IBM Corporation.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/bug.h>
#समावेश <linux/मानकघोष.स>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/perf_regs.h>

u64 PERF_REG_EXTENDED_MASK;

#घोषणा PT_REGS_OFFSET(id, r) [id] = दुरत्व(काष्ठा pt_regs, r)

#घोषणा REG_RESERVED (~(PERF_REG_EXTENDED_MASK | PERF_REG_PMU_MASK))

अटल अचिन्हित पूर्णांक pt_regs_offset[PERF_REG_POWERPC_MAX] = अणु
	PT_REGS_OFFSET(PERF_REG_POWERPC_R0,  gpr[0]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R1,  gpr[1]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R2,  gpr[2]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R3,  gpr[3]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R4,  gpr[4]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R5,  gpr[5]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R6,  gpr[6]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R7,  gpr[7]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R8,  gpr[8]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R9,  gpr[9]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R10, gpr[10]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R11, gpr[11]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R12, gpr[12]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R13, gpr[13]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R14, gpr[14]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R15, gpr[15]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R16, gpr[16]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R17, gpr[17]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R18, gpr[18]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R19, gpr[19]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R20, gpr[20]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R21, gpr[21]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R22, gpr[22]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R23, gpr[23]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R24, gpr[24]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R25, gpr[25]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R26, gpr[26]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R27, gpr[27]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R28, gpr[28]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R29, gpr[29]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R30, gpr[30]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_R31, gpr[31]),
	PT_REGS_OFFSET(PERF_REG_POWERPC_NIP, nip),
	PT_REGS_OFFSET(PERF_REG_POWERPC_MSR, msr),
	PT_REGS_OFFSET(PERF_REG_POWERPC_ORIG_R3, orig_gpr3),
	PT_REGS_OFFSET(PERF_REG_POWERPC_CTR, ctr),
	PT_REGS_OFFSET(PERF_REG_POWERPC_LINK, link),
	PT_REGS_OFFSET(PERF_REG_POWERPC_XER, xer),
	PT_REGS_OFFSET(PERF_REG_POWERPC_CCR, ccr),
#अगर_घोषित CONFIG_PPC64
	PT_REGS_OFFSET(PERF_REG_POWERPC_SOFTE, softe),
#अन्यथा
	PT_REGS_OFFSET(PERF_REG_POWERPC_SOFTE, mq),
#पूर्ण_अगर
	PT_REGS_OFFSET(PERF_REG_POWERPC_TRAP, trap),
	PT_REGS_OFFSET(PERF_REG_POWERPC_DAR, dar),
	PT_REGS_OFFSET(PERF_REG_POWERPC_DSISR, dsisr),
	PT_REGS_OFFSET(PERF_REG_POWERPC_SIER, dar),
	PT_REGS_OFFSET(PERF_REG_POWERPC_MMCRA, dsisr),
पूर्ण;

/* Function to वापस the extended रेजिस्टर values */
अटल u64 get_ext_regs_value(पूर्णांक idx)
अणु
	चयन (idx) अणु
	हाल PERF_REG_POWERPC_PMC1 ... PERF_REG_POWERPC_PMC6:
		वापस get_pmcs_ext_regs(idx - PERF_REG_POWERPC_PMC1);
	हाल PERF_REG_POWERPC_MMCR0:
		वापस mfspr(SPRN_MMCR0);
	हाल PERF_REG_POWERPC_MMCR1:
		वापस mfspr(SPRN_MMCR1);
	हाल PERF_REG_POWERPC_MMCR2:
		वापस mfspr(SPRN_MMCR2);
#अगर_घोषित CONFIG_PPC64
	हाल PERF_REG_POWERPC_MMCR3:
		वापस mfspr(SPRN_MMCR3);
	हाल PERF_REG_POWERPC_SIER2:
		वापस mfspr(SPRN_SIER2);
	हाल PERF_REG_POWERPC_SIER3:
		वापस mfspr(SPRN_SIER3);
#पूर्ण_अगर
	शेष: वापस 0;
	पूर्ण
पूर्ण

u64 perf_reg_value(काष्ठा pt_regs *regs, पूर्णांक idx)
अणु
	अगर (idx == PERF_REG_POWERPC_SIER &&
	   (IS_ENABLED(CONFIG_FSL_EMB_PERF_EVENT) ||
	    IS_ENABLED(CONFIG_PPC32) ||
	    !is_sier_available()))
		वापस 0;

	अगर (idx == PERF_REG_POWERPC_MMCRA &&
	   (IS_ENABLED(CONFIG_FSL_EMB_PERF_EVENT) ||
	    IS_ENABLED(CONFIG_PPC32)))
		वापस 0;

	अगर (idx >= PERF_REG_POWERPC_MAX && idx < PERF_REG_EXTENDED_MAX)
		वापस get_ext_regs_value(idx);

	/*
	 * If the idx is referring to value beyond the
	 * supported रेजिस्टरs, वापस 0 with a warning
	 */
	अगर (WARN_ON_ONCE(idx >= PERF_REG_EXTENDED_MAX))
		वापस 0;

	वापस regs_get_रेजिस्टर(regs, pt_regs_offset[idx]);
पूर्ण

पूर्णांक perf_reg_validate(u64 mask)
अणु
	अगर (!mask || mask & REG_RESERVED)
		वापस -EINVAL;
	वापस 0;
पूर्ण

u64 perf_reg_abi(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_PPC64
	अगर (!test_tsk_thपढ़ो_flag(task, TIF_32BIT))
		वापस PERF_SAMPLE_REGS_ABI_64;
	अन्यथा
#पूर्ण_अगर
	वापस PERF_SAMPLE_REGS_ABI_32;
पूर्ण

व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
			काष्ठा pt_regs *regs)
अणु
	regs_user->regs = task_pt_regs(current);
	regs_user->abi = (regs_user->regs) ? perf_reg_abi(current) :
			 PERF_SAMPLE_REGS_ABI_NONE;
पूर्ण
