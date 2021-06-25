<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compat.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/bug.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/perf_regs.h>
#समावेश <यंत्र/ptrace.h>

u64 perf_reg_value(काष्ठा pt_regs *regs, पूर्णांक idx)
अणु
	अगर (WARN_ON_ONCE((u32)idx >= PERF_REG_ARM64_MAX))
		वापस 0;

	/*
	 * Our handling of compat tasks (PERF_SAMPLE_REGS_ABI_32) is weird, but
	 * we're stuck with it क्रम ABI compatibility reasons.
	 *
	 * For a 32-bit consumer inspecting a 32-bit task, then it will look at
	 * the first 16 रेजिस्टरs (see arch/arm/include/uapi/यंत्र/perf_regs.h).
	 * These correspond directly to a prefix of the रेजिस्टरs saved in our
	 * 'struct pt_regs', with the exception of the PC, so we copy that करोwn
	 * (x15 corresponds to SP_hyp in the architecture).
	 *
	 * So far, so good.
	 *
	 * The oddity arises when a 64-bit consumer looks at a 32-bit task and
	 * asks क्रम रेजिस्टरs beyond PERF_REG_ARM_MAX. In this हाल, we वापस
	 * SP_usr, LR_usr and PC in the positions where the AArch64 SP, LR and
	 * PC रेजिस्टरs would normally live. The initial idea was to allow a
	 * 64-bit unwinder to unwind a 32-bit task and, although it's not clear
	 * how well that works in practice, somebody might be relying on it.
	 *
	 * At the समय we make a sample, we करोn't know whether the consumer is
	 * 32-bit or 64-bit, so we have to cater क्रम both possibilities.
	 */
	अगर (compat_user_mode(regs)) अणु
		अगर ((u32)idx == PERF_REG_ARM64_SP)
			वापस regs->compat_sp;
		अगर ((u32)idx == PERF_REG_ARM64_LR)
			वापस regs->compat_lr;
		अगर (idx == 15)
			वापस regs->pc;
	पूर्ण

	अगर ((u32)idx == PERF_REG_ARM64_SP)
		वापस regs->sp;

	अगर ((u32)idx == PERF_REG_ARM64_PC)
		वापस regs->pc;

	वापस regs->regs[idx];
पूर्ण

#घोषणा REG_RESERVED (~((1ULL << PERF_REG_ARM64_MAX) - 1))

पूर्णांक perf_reg_validate(u64 mask)
अणु
	अगर (!mask || mask & REG_RESERVED)
		वापस -EINVAL;

	वापस 0;
पूर्ण

u64 perf_reg_abi(काष्ठा task_काष्ठा *task)
अणु
	अगर (is_compat_thपढ़ो(task_thपढ़ो_info(task)))
		वापस PERF_SAMPLE_REGS_ABI_32;
	अन्यथा
		वापस PERF_SAMPLE_REGS_ABI_64;
पूर्ण

व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
			काष्ठा pt_regs *regs)
अणु
	regs_user->regs = task_pt_regs(current);
	regs_user->abi = perf_reg_abi(current);
पूर्ण
