<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Amit Bhor, Kanika Nema: Codito Technologies 2004
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/elf.h>
#समावेश <linux/tick.h>

#समावेश <यंत्र/fpu.h>

SYSCALL_DEFINE1(arc_settls, व्योम *, user_tls_data_ptr)
अणु
	task_thपढ़ो_info(current)->thr_ptr = (अचिन्हित पूर्णांक)user_tls_data_ptr;
	वापस 0;
पूर्ण

/*
 * We वापस the user space TLS data ptr as sys-call वापस code
 * Ideally it should be copy to user.
 * However we can cheat by the fact that some sys-calls करो वापस
 * असलurdly high values
 * Since the tls dat aptr is not going to be in range of 0xFFFF_xxxx
 * it won't be considered a sys-call error
 * and it will be loads better than copy-to-user, which is a definite
 * D-TLB Miss
 */
SYSCALL_DEFINE0(arc_gettls)
अणु
	वापस task_thपढ़ो_info(current)->thr_ptr;
पूर्ण

SYSCALL_DEFINE3(arc_usr_cmpxchg, पूर्णांक *, uaddr, पूर्णांक, expected, पूर्णांक, new)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	u32 uval;
	पूर्णांक ret;

	/*
	 * This is only क्रम old cores lacking LLOCK/SCOND, which by definition
	 * can't possibly be SMP. Thus doesn't need to be SMP safe.
	 * And this also helps reduce the overhead क्रम serializing in
	 * the UP हाल
	 */
	WARN_ON_ONCE(IS_ENABLED(CONFIG_SMP));

	/* Z indicates to userspace अगर operation succeeded */
	regs->status32 &= ~STATUS_Z_MASK;

	ret = access_ok(uaddr, माप(*uaddr));
	अगर (!ret)
		 जाओ fail;

again:
	preempt_disable();

	ret = __get_user(uval, uaddr);
	अगर (ret)
		 जाओ fault;

	अगर (uval != expected)
		 जाओ out;

	ret = __put_user(new, uaddr);
	अगर (ret)
		 जाओ fault;

	regs->status32 |= STATUS_Z_MASK;

out:
	preempt_enable();
	वापस uval;

fault:
	preempt_enable();

	अगर (unlikely(ret != -EFAULT))
		 जाओ fail;

	mmap_पढ़ो_lock(current->mm);
	ret = fixup_user_fault(current->mm, (अचिन्हित दीर्घ) uaddr,
			       FAULT_FLAG_WRITE, शून्य);
	mmap_पढ़ो_unlock(current->mm);

	अगर (likely(!ret))
		 जाओ again;

fail:
	क्रमce_sig(संक_अंश);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_ISA_ARCV2

व्योम arch_cpu_idle(व्योम)
अणु
	/* Re-enable पूर्णांकerrupts <= शेष irq priority beक्रमe committing SLEEP */
	स्थिर अचिन्हित पूर्णांक arg = 0x10 | ARCV2_IRQ_DEF_PRIO;

	__यंत्र__ __अस्थिर__(
		"sleep %0	\n"
		:
		:"I"(arg)); /* can't be "r" has to be embedded स्थिर */
पूर्ण

#अन्यथा	/* ARC700 */

व्योम arch_cpu_idle(व्योम)
अणु
	/* sleep, but enable both set E1/E2 (levels of पूर्णांकerrupts) beक्रमe committing */
	__यंत्र__ __अस्थिर__("sleep 0x3	\n");
पूर्ण

#पूर्ण_अगर

यंत्रlinkage व्योम ret_from_विभाजन(व्योम);

/*
 * Copy architecture-specअगरic thपढ़ो state
 *
 * Layout of Child kernel mode stack as setup at the end of this function is
 *
 * |     ...        |
 * |     ...        |
 * |    unused      |
 * |                |
 * ------------------
 * |     r25        |   <==== top of Stack (thपढ़ो.ksp)
 * ~                ~
 * |    --to--      |   (CALLEE Regs of kernel mode)
 * |     r13        |
 * ------------------
 * |     fp         |
 * |    blink       |   @ret_from_विभाजन
 * ------------------
 * |                |
 * ~                ~
 * ~                ~
 * |                |
 * ------------------
 * |     r12        |
 * ~                ~
 * |    --to--      |   (scratch Regs of user mode)
 * |     r0         |
 * ------------------
 * |      SP        |
 * |    orig_r0     |
 * |    event/ECR   |
 * |    user_r25    |
 * ------------------  <===== END of PAGE
 */
पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp,
		अचिन्हित दीर्घ kthपढ़ो_arg, काष्ठा task_काष्ठा *p,
		अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *c_regs;        /* child's pt_regs */
	अचिन्हित दीर्घ *childksp;       /* to unwind out of __चयन_to() */
	काष्ठा callee_regs *c_callee;  /* child's callee regs */
	काष्ठा callee_regs *parent_callee;  /* paren't callee */
	काष्ठा pt_regs *regs = current_pt_regs();

	/* Mark the specअगरic anchors to begin with (see pic above) */
	c_regs = task_pt_regs(p);
	childksp = (अचिन्हित दीर्घ *)c_regs - 2;  /* 2 words क्रम FP/BLINK */
	c_callee = ((काष्ठा callee_regs *)childksp) - 1;

	/*
	 * __चयन_to() uses thपढ़ो.ksp to start unwinding stack
	 * For kernel thपढ़ोs we करोn't need to create callee regs, the
	 * stack layout nevertheless needs to reमुख्य the same.
	 * Also, since __चयन_to anyways unwinds callee regs, we use
	 * this to populate kernel thपढ़ो entry-pt/args पूर्णांकo callee regs,
	 * so that ret_from_kernel_thपढ़ो() becomes simpler.
	 */
	p->thपढ़ो.ksp = (अचिन्हित दीर्घ)c_callee;	/* THREAD_KSP */

	/* __चयन_to expects FP(0), BLINK(वापस addr) at top */
	childksp[0] = 0;			/* fp */
	childksp[1] = (अचिन्हित दीर्घ)ret_from_विभाजन; /* blink */

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(c_regs, 0, माप(काष्ठा pt_regs));

		c_callee->r13 = kthपढ़ो_arg;
		c_callee->r14 = usp;  /* function */

		वापस 0;
	पूर्ण

	/*--------- User Task Only --------------*/

	/* __चयन_to expects FP(0), BLINK(वापस addr) at top of stack */
	childksp[0] = 0;				/* क्रम POP fp */
	childksp[1] = (अचिन्हित दीर्घ)ret_from_विभाजन;	/* क्रम POP blink */

	/* Copy parents pt regs on child's kernel mode stack */
	*c_regs = *regs;

	अगर (usp)
		c_regs->sp = usp;

	c_regs->r0 = 0;		/* विभाजन वापसs 0 in child */

	parent_callee = ((काष्ठा callee_regs *)regs) - 1;
	*c_callee = *parent_callee;

	अगर (unlikely(clone_flags & CLONE_SETTLS)) अणु
		/*
		 * set task's userland tls data ptr from 4th arg
		 * clone C-lib call is dअगरft from clone sys-call
		 */
		task_thपढ़ो_info(p)->thr_ptr = tls;
	पूर्ण अन्यथा अणु
		/* Normal विभाजन हाल: set parent's TLS ptr in child */
		task_thपढ़ो_info(p)->thr_ptr =
		task_thपढ़ो_info(current)->thr_ptr;
	पूर्ण


	/*
	 * setup usermode thपढ़ो poपूर्णांकer #1:
	 * when child is picked by scheduler, __चयन_to() uses @c_callee to
	 * populate usermode callee regs: this works (despite being in a kernel
	 * function) since special वापस path क्रम child @ret_from_विभाजन()
	 * ensures those regs are not clobbered all the way to RTIE to usermode
	 */
	c_callee->r25 = task_thपढ़ो_info(p)->thr_ptr;

#अगर_घोषित CONFIG_ARC_CURR_IN_REG
	/*
	 * setup usermode thपढ़ो poपूर्णांकer #2:
	 * however क्रम this special use of r25 in kernel, __चयन_to() sets
	 * r25 क्रम kernel needs and only in the final वापस path is usermode
	 * r25 setup, from pt_regs->user_r25. So set that up as well
	 */
	c_regs->user_r25 = c_callee->r25;
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * Do necessary setup to start up a new user task
 */
व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ usp)
अणु
	regs->sp = usp;
	regs->ret = pc;

	/*
	 * [U]ser Mode bit set
	 * [L] ZOL loop inhibited to begin with - cleared by a LP insn
	 * Interrupts enabled
	 */
	regs->status32 = STATUS_U_MASK | STATUS_L_MASK | ISA_INIT_STATUS_BITS;

	fpu_init_task(regs);

	/* bogus seed values क्रम debugging */
	regs->lp_start = 0x10;
	regs->lp_end = 0x80;
पूर्ण

/*
 * Some archs flush debug and FPU info here
 */
व्योम flush_thपढ़ो(व्योम)
अणु
पूर्ण

पूर्णांक elf_check_arch(स्थिर काष्ठा elf32_hdr *x)
अणु
	अचिन्हित पूर्णांक eflags;

	अगर (x->e_machine != EM_ARC_INUSE) अणु
		pr_err("ELF not built for %s ISA\n",
			is_isa_arcompact() ? "ARCompact":"ARCv2");
		वापस 0;
	पूर्ण

	eflags = x->e_flags;
	अगर ((eflags & EF_ARC_OSABI_MSK) != EF_ARC_OSABI_CURRENT) अणु
		pr_err("ABI mismatch - you need newer toolchain\n");
		क्रमce_sigsegv(संक_अंश);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL(elf_check_arch);
