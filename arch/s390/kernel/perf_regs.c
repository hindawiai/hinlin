<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/perf_event.h>
#समावेश <linux/perf_regs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/fpu/types.h>

u64 perf_reg_value(काष्ठा pt_regs *regs, पूर्णांक idx)
अणु
	freg_t fp;

	अगर (idx >= PERF_REG_S390_R0 && idx <= PERF_REG_S390_R15)
		वापस regs->gprs[idx];

	अगर (idx >= PERF_REG_S390_FP0 && idx <= PERF_REG_S390_FP15) अणु
		अगर (!user_mode(regs))
			वापस 0;

		idx -= PERF_REG_S390_FP0;
		fp = MACHINE_HAS_VX ? *(freg_t *)(current->thपढ़ो.fpu.vxrs + idx)
				    : current->thपढ़ो.fpu.fprs[idx];
		वापस fp.ui;
	पूर्ण

	अगर (idx == PERF_REG_S390_MASK)
		वापस regs->psw.mask;
	अगर (idx == PERF_REG_S390_PC)
		वापस regs->psw.addr;

	WARN_ON_ONCE((u32)idx >= PERF_REG_S390_MAX);
	वापस 0;
पूर्ण

#घोषणा REG_RESERVED (~((1UL << PERF_REG_S390_MAX) - 1))

पूर्णांक perf_reg_validate(u64 mask)
अणु
	अगर (!mask || mask & REG_RESERVED)
		वापस -EINVAL;

	वापस 0;
पूर्ण

u64 perf_reg_abi(काष्ठा task_काष्ठा *task)
अणु
	अगर (test_tsk_thपढ़ो_flag(task, TIF_31BIT))
		वापस PERF_SAMPLE_REGS_ABI_32;

	वापस PERF_SAMPLE_REGS_ABI_64;
पूर्ण

व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
			काष्ठा pt_regs *regs)
अणु
	/*
	 * Use the regs from the first पूर्णांकerruption and let
	 * perf_sample_regs_पूर्णांकr() handle पूर्णांकerrupts (regs == get_irq_regs()).
	 *
	 * Also save FPU रेजिस्टरs क्रम user-space tasks only.
	 */
	regs_user->regs = task_pt_regs(current);
	अगर (user_mode(regs_user->regs))
		save_fpu_regs();
	regs_user->abi = perf_reg_abi(current);
पूर्ण
