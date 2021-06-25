<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2010 Tilera Corporation. All Rights Reserved.
 * Copyright 2015 Regents of the University of Calअगरornia
 * Copyright 2017 SiFive
 *
 * Copied from arch/tile/kernel/ptrace.c
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <linux/audit.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/elf.h>
#समावेश <linux/regset.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/tracehook.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/syscalls.h>

क्रमागत riscv_regset अणु
	REGSET_X,
#अगर_घोषित CONFIG_FPU
	REGSET_F,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक riscv_gpr_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	वापस membuf_ग_लिखो(&to, task_pt_regs(target),
			    माप(काष्ठा user_regs_काष्ठा));
पूर्ण

अटल पूर्णांक riscv_gpr_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा pt_regs *regs;

	regs = task_pt_regs(target);
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, regs, 0, -1);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_FPU
अटल पूर्णांक riscv_fpr_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	काष्ठा __riscv_d_ext_state *ख_स्थितिe = &target->thपढ़ो.ख_स्थितिe;

	membuf_ग_लिखो(&to, ख_स्थितिe, दुरत्व(काष्ठा __riscv_d_ext_state, fcsr));
	membuf_store(&to, ख_स्थितिe->fcsr);
	वापस membuf_zero(&to, 4);	// explicitly pad
पूर्ण

अटल पूर्णांक riscv_fpr_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक ret;
	काष्ठा __riscv_d_ext_state *ख_स्थितिe = &target->thपढ़ो.ख_स्थितिe;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, ख_स्थितिe, 0,
				 दुरत्व(काष्ठा __riscv_d_ext_state, fcsr));
	अगर (!ret) अणु
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf, ख_स्थितिe, 0,
					 दुरत्व(काष्ठा __riscv_d_ext_state, fcsr) +
					 माप(ख_स्थितिe->fcsr));
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा user_regset riscv_user_regset[] = अणु
	[REGSET_X] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = ELF_NGREG,
		.size = माप(elf_greg_t),
		.align = माप(elf_greg_t),
		.regset_get = riscv_gpr_get,
		.set = riscv_gpr_set,
	पूर्ण,
#अगर_घोषित CONFIG_FPU
	[REGSET_F] = अणु
		.core_note_type = NT_PRFPREG,
		.n = ELF_NFPREG,
		.size = माप(elf_fpreg_t),
		.align = माप(elf_fpreg_t),
		.regset_get = riscv_fpr_get,
		.set = riscv_fpr_set,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा user_regset_view riscv_user_native_view = अणु
	.name = "riscv",
	.e_machine = EM_RISCV,
	.regsets = riscv_user_regset,
	.n = ARRAY_SIZE(riscv_user_regset),
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &riscv_user_native_view;
पूर्ण

काष्ठा pt_regs_offset अणु
	स्थिर अक्षर *name;
	पूर्णांक offset;
पूर्ण;

#घोषणा REG_OFFSET_NAME(r) अणु.name = #r, .offset = दुरत्व(काष्ठा pt_regs, r)पूर्ण
#घोषणा REG_OFFSET_END अणु.name = शून्य, .offset = 0पूर्ण

अटल स्थिर काष्ठा pt_regs_offset regoffset_table[] = अणु
	REG_OFFSET_NAME(epc),
	REG_OFFSET_NAME(ra),
	REG_OFFSET_NAME(sp),
	REG_OFFSET_NAME(gp),
	REG_OFFSET_NAME(tp),
	REG_OFFSET_NAME(t0),
	REG_OFFSET_NAME(t1),
	REG_OFFSET_NAME(t2),
	REG_OFFSET_NAME(s0),
	REG_OFFSET_NAME(s1),
	REG_OFFSET_NAME(a0),
	REG_OFFSET_NAME(a1),
	REG_OFFSET_NAME(a2),
	REG_OFFSET_NAME(a3),
	REG_OFFSET_NAME(a4),
	REG_OFFSET_NAME(a5),
	REG_OFFSET_NAME(a6),
	REG_OFFSET_NAME(a7),
	REG_OFFSET_NAME(s2),
	REG_OFFSET_NAME(s3),
	REG_OFFSET_NAME(s4),
	REG_OFFSET_NAME(s5),
	REG_OFFSET_NAME(s6),
	REG_OFFSET_NAME(s7),
	REG_OFFSET_NAME(s8),
	REG_OFFSET_NAME(s9),
	REG_OFFSET_NAME(s10),
	REG_OFFSET_NAME(s11),
	REG_OFFSET_NAME(t3),
	REG_OFFSET_NAME(t4),
	REG_OFFSET_NAME(t5),
	REG_OFFSET_NAME(t6),
	REG_OFFSET_NAME(status),
	REG_OFFSET_NAME(badaddr),
	REG_OFFSET_NAME(cause),
	REG_OFFSET_NAME(orig_a0),
	REG_OFFSET_END,
पूर्ण;

/**
 * regs_query_रेजिस्टर_offset() - query रेजिस्टर offset from its name
 * @name:	the name of a रेजिस्टर
 *
 * regs_query_रेजिस्टर_offset() वापसs the offset of a रेजिस्टर in काष्ठा
 * pt_regs from its name. If the name is invalid, this वापसs -EINVAL;
 */
पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा pt_regs_offset *roff;

	क्रम (roff = regoffset_table; roff->name != शून्य; roff++)
		अगर (!म_भेद(roff->name, name))
			वापस roff->offset;
	वापस -EINVAL;
पूर्ण

/**
 * regs_within_kernel_stack() - check the address in the stack
 * @regs:      pt_regs which contains kernel stack poपूर्णांकer.
 * @addr:      address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it वापसs true. If not, वापसs false.
 */
अटल bool regs_within_kernel_stack(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	वापस (addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_poपूर्णांकer(regs) & ~(THREAD_SIZE - 1));
पूर्ण

/**
 * regs_get_kernel_stack_nth() - get Nth entry of the stack
 * @regs:	pt_regs which contains kernel stack poपूर्णांकer.
 * @n:		stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs @n th entry of the kernel stack which
 * is specअगरied by @regs. If the @n th entry is NOT in the kernel stack,
 * this वापसs 0.
 */
अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ *addr = (अचिन्हित दीर्घ *)kernel_stack_poपूर्णांकer(regs);

	addr += n;
	अगर (regs_within_kernel_stack(regs, (अचिन्हित दीर्घ)addr))
		वापस *addr;
	अन्यथा
		वापस 0;
पूर्ण

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	clear_tsk_thपढ़ो_flag(child, TIF_SYSCALL_TRACE);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	दीर्घ ret = -EIO;

	चयन (request) अणु
	शेष:
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Allows PTRACE_SYSCALL to work.  These are called from entry.S in
 * अणुhandle,ret_fromपूर्ण_syscall.
 */
__visible पूर्णांक करो_syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		अगर (tracehook_report_syscall_entry(regs))
			वापस -1;

	/*
	 * Do the secure computing after ptrace; failures should be fast.
	 * If this fails we might have वापस value in a0 from seccomp
	 * (via SECCOMP_RET_ERRNO/TRACE).
	 */
	अगर (secure_computing() == -1)
		वापस -1;

#अगर_घोषित CONFIG_HAVE_SYSCALL_TRACEPOINTS
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_enter(regs, syscall_get_nr(current, regs));
#पूर्ण_अगर

	audit_syscall_entry(regs->a7, regs->a0, regs->a1, regs->a2, regs->a3);
	वापस 0;
पूर्ण

__visible व्योम करो_syscall_trace_निकास(काष्ठा pt_regs *regs)
अणु
	audit_syscall_निकास(regs);

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, 0);

#अगर_घोषित CONFIG_HAVE_SYSCALL_TRACEPOINTS
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_निकास(regs, regs_वापस_value(regs));
#पूर्ण_अगर
पूर्ण
