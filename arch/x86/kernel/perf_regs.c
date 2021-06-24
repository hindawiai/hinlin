<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/bug.h>
#समावेश <linux/मानकघोष.स>
#समावेश <यंत्र/perf_regs.h>
#समावेश <यंत्र/ptrace.h>

#अगर_घोषित CONFIG_X86_32
#घोषणा PERF_REG_X86_MAX PERF_REG_X86_32_MAX
#अन्यथा
#घोषणा PERF_REG_X86_MAX PERF_REG_X86_64_MAX
#पूर्ण_अगर

#घोषणा PT_REGS_OFFSET(id, r) [id] = दुरत्व(काष्ठा pt_regs, r)

अटल अचिन्हित पूर्णांक pt_regs_offset[PERF_REG_X86_MAX] = अणु
	PT_REGS_OFFSET(PERF_REG_X86_AX, ax),
	PT_REGS_OFFSET(PERF_REG_X86_BX, bx),
	PT_REGS_OFFSET(PERF_REG_X86_CX, cx),
	PT_REGS_OFFSET(PERF_REG_X86_DX, dx),
	PT_REGS_OFFSET(PERF_REG_X86_SI, si),
	PT_REGS_OFFSET(PERF_REG_X86_DI, di),
	PT_REGS_OFFSET(PERF_REG_X86_BP, bp),
	PT_REGS_OFFSET(PERF_REG_X86_SP, sp),
	PT_REGS_OFFSET(PERF_REG_X86_IP, ip),
	PT_REGS_OFFSET(PERF_REG_X86_FLAGS, flags),
	PT_REGS_OFFSET(PERF_REG_X86_CS, cs),
	PT_REGS_OFFSET(PERF_REG_X86_SS, ss),
#अगर_घोषित CONFIG_X86_32
	PT_REGS_OFFSET(PERF_REG_X86_DS, ds),
	PT_REGS_OFFSET(PERF_REG_X86_ES, es),
	PT_REGS_OFFSET(PERF_REG_X86_FS, fs),
	PT_REGS_OFFSET(PERF_REG_X86_GS, gs),
#अन्यथा
	/*
	 * The pt_regs काष्ठा करोes not store
	 * ds, es, fs, gs in 64 bit mode.
	 */
	(अचिन्हित पूर्णांक) -1,
	(अचिन्हित पूर्णांक) -1,
	(अचिन्हित पूर्णांक) -1,
	(अचिन्हित पूर्णांक) -1,
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86_64
	PT_REGS_OFFSET(PERF_REG_X86_R8, r8),
	PT_REGS_OFFSET(PERF_REG_X86_R9, r9),
	PT_REGS_OFFSET(PERF_REG_X86_R10, r10),
	PT_REGS_OFFSET(PERF_REG_X86_R11, r11),
	PT_REGS_OFFSET(PERF_REG_X86_R12, r12),
	PT_REGS_OFFSET(PERF_REG_X86_R13, r13),
	PT_REGS_OFFSET(PERF_REG_X86_R14, r14),
	PT_REGS_OFFSET(PERF_REG_X86_R15, r15),
#पूर्ण_अगर
पूर्ण;

u64 perf_reg_value(काष्ठा pt_regs *regs, पूर्णांक idx)
अणु
	काष्ठा x86_perf_regs *perf_regs;

	अगर (idx >= PERF_REG_X86_XMM0 && idx < PERF_REG_X86_XMM_MAX) अणु
		perf_regs = container_of(regs, काष्ठा x86_perf_regs, regs);
		अगर (!perf_regs->xmm_regs)
			वापस 0;
		वापस perf_regs->xmm_regs[idx - PERF_REG_X86_XMM0];
	पूर्ण

	अगर (WARN_ON_ONCE(idx >= ARRAY_SIZE(pt_regs_offset)))
		वापस 0;

	वापस regs_get_रेजिस्टर(regs, pt_regs_offset[idx]);
पूर्ण

#घोषणा PERF_REG_X86_RESERVED	(((1ULL << PERF_REG_X86_XMM0) - 1) & \
				 ~((1ULL << PERF_REG_X86_MAX) - 1))

#अगर_घोषित CONFIG_X86_32
#घोषणा REG_NOSUPPORT ((1ULL << PERF_REG_X86_R8) | \
		       (1ULL << PERF_REG_X86_R9) | \
		       (1ULL << PERF_REG_X86_R10) | \
		       (1ULL << PERF_REG_X86_R11) | \
		       (1ULL << PERF_REG_X86_R12) | \
		       (1ULL << PERF_REG_X86_R13) | \
		       (1ULL << PERF_REG_X86_R14) | \
		       (1ULL << PERF_REG_X86_R15))

पूर्णांक perf_reg_validate(u64 mask)
अणु
	अगर (!mask || (mask & (REG_NOSUPPORT | PERF_REG_X86_RESERVED)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

u64 perf_reg_abi(काष्ठा task_काष्ठा *task)
अणु
	वापस PERF_SAMPLE_REGS_ABI_32;
पूर्ण

व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
			काष्ठा pt_regs *regs)
अणु
	regs_user->regs = task_pt_regs(current);
	regs_user->abi = perf_reg_abi(current);
पूर्ण
#अन्यथा /* CONFIG_X86_64 */
#घोषणा REG_NOSUPPORT ((1ULL << PERF_REG_X86_DS) | \
		       (1ULL << PERF_REG_X86_ES) | \
		       (1ULL << PERF_REG_X86_FS) | \
		       (1ULL << PERF_REG_X86_GS))

पूर्णांक perf_reg_validate(u64 mask)
अणु
	अगर (!mask || (mask & (REG_NOSUPPORT | PERF_REG_X86_RESERVED)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

u64 perf_reg_abi(काष्ठा task_काष्ठा *task)
अणु
	अगर (!user_64bit_mode(task_pt_regs(task)))
		वापस PERF_SAMPLE_REGS_ABI_32;
	अन्यथा
		वापस PERF_SAMPLE_REGS_ABI_64;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा pt_regs, nmi_user_regs);

व्योम perf_get_regs_user(काष्ठा perf_regs *regs_user,
			काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *regs_user_copy = this_cpu_ptr(&nmi_user_regs);
	काष्ठा pt_regs *user_regs = task_pt_regs(current);

	अगर (!in_nmi()) अणु
		regs_user->regs = user_regs;
		regs_user->abi = perf_reg_abi(current);
		वापस;
	पूर्ण

	/*
	 * If we're in an NMI that पूर्णांकerrupted task_pt_regs setup, then
	 * we can't sample user regs at all.  This check isn't really
	 * sufficient, though, as we could be in an NMI inside an पूर्णांकerrupt
	 * that happened during task_pt_regs setup.
	 */
	अगर (regs->sp > (अचिन्हित दीर्घ)&user_regs->r11 &&
	    regs->sp <= (अचिन्हित दीर्घ)(user_regs + 1)) अणु
		regs_user->abi = PERF_SAMPLE_REGS_ABI_NONE;
		regs_user->regs = शून्य;
		वापस;
	पूर्ण

	/*
	 * These रेजिस्टरs are always saved on 64-bit syscall entry.
	 * On 32-bit entry poपूर्णांकs, they are saved too except r8..r11.
	 */
	regs_user_copy->ip = user_regs->ip;
	regs_user_copy->ax = user_regs->ax;
	regs_user_copy->cx = user_regs->cx;
	regs_user_copy->dx = user_regs->dx;
	regs_user_copy->si = user_regs->si;
	regs_user_copy->di = user_regs->di;
	regs_user_copy->r8 = user_regs->r8;
	regs_user_copy->r9 = user_regs->r9;
	regs_user_copy->r10 = user_regs->r10;
	regs_user_copy->r11 = user_regs->r11;
	regs_user_copy->orig_ax = user_regs->orig_ax;
	regs_user_copy->flags = user_regs->flags;
	regs_user_copy->sp = user_regs->sp;
	regs_user_copy->cs = user_regs->cs;
	regs_user_copy->ss = user_regs->ss;
	/*
	 * Store user space frame-poपूर्णांकer value on sample
	 * to facilitate stack unwinding क्रम हालs when
	 * user space executable code has such support
	 * enabled at compile समय:
	 */
	regs_user_copy->bp = user_regs->bp;

	regs_user_copy->bx = -1;
	regs_user_copy->r12 = -1;
	regs_user_copy->r13 = -1;
	regs_user_copy->r14 = -1;
	regs_user_copy->r15 = -1;
	/*
	 * For this to be at all useful, we need a reasonable guess क्रम
	 * the ABI.  Be careful: we're in NMI context, and we're
	 * considering current to be the current task, so we should
	 * be careful not to look at any other percpu variables that might
	 * change during context चयनes.
	 */
	regs_user->abi = user_64bit_mode(user_regs) ?
		PERF_SAMPLE_REGS_ABI_64 : PERF_SAMPLE_REGS_ABI_32;

	regs_user->regs = regs_user_copy;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_32 */
