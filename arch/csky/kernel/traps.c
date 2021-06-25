<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/user.h>
#समावेश <linux/माला.स>
#समावेश <linux/linkage.h>
#समावेश <linux/init.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/rtc.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched/debug.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/siginfo.h>

#समावेश <यंत्र/mmu_context.h>

#अगर_घोषित CONFIG_CPU_HAS_FPU
#समावेश <abi/fpu.h>
#पूर्ण_अगर

पूर्णांक show_unhandled_संकेतs = 1;

/* Defined in entry.S */
यंत्रlinkage व्योम csky_trap(व्योम);

यंत्रlinkage व्योम csky_प्रणालीcall(व्योम);
यंत्रlinkage व्योम csky_cmpxchg(व्योम);
यंत्रlinkage व्योम csky_get_tls(व्योम);
यंत्रlinkage व्योम csky_irq(व्योम);

यंत्रlinkage व्योम csky_pagefault(व्योम);

/* Defined in head.S */
यंत्रlinkage व्योम _start_smp_secondary(व्योम);

व्योम __init pre_trap_init(व्योम)
अणु
	पूर्णांक i;

	mtcr("vbr", vec_base);

	क्रम (i = 1; i < 128; i++)
		VEC_INIT(i, csky_trap);
पूर्ण

व्योम __init trap_init(व्योम)
अणु
	VEC_INIT(VEC_AUTOVEC, csky_irq);

	/* setup trap0 trap2 trap3 */
	VEC_INIT(VEC_TRAP0, csky_प्रणालीcall);
	VEC_INIT(VEC_TRAP2, csky_cmpxchg);
	VEC_INIT(VEC_TRAP3, csky_get_tls);

	/* setup MMU TLB exception */
	VEC_INIT(VEC_TLBINVALIDL, csky_pagefault);
	VEC_INIT(VEC_TLBINVALIDS, csky_pagefault);
	VEC_INIT(VEC_TLBMODIFIED, csky_pagefault);

#अगर_घोषित CONFIG_CPU_HAS_FPU
	init_fpu();
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
	mtcr("cr<28, 0>", virt_to_phys(vec_base));

	VEC_INIT(VEC_RESET, (व्योम *)virt_to_phys(_start_smp_secondary));
#पूर्ण_अगर
पूर्ण

अटल DEFINE_SPINLOCK(die_lock);

व्योम die(काष्ठा pt_regs *regs, स्थिर अक्षर *str)
अणु
	अटल पूर्णांक die_counter;
	पूर्णांक ret;

	oops_enter();

	spin_lock_irq(&die_lock);
	console_verbose();
	bust_spinlocks(1);

	pr_emerg("%s [#%d]\n", str, ++die_counter);
	prपूर्णांक_modules();
	show_regs(regs);
	show_stack(current, (अचिन्हित दीर्घ *)regs->regs[4], KERN_INFO);

	ret = notअगरy_die(DIE_OOPS, str, regs, 0, trap_no(regs), संक_अंश);

	bust_spinlocks(0);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irq(&die_lock);
	oops_निकास();

	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");
	अगर (panic_on_oops)
		panic("Fatal exception");
	अगर (ret != NOTIFY_STOP)
		करो_निकास(संक_अंश);
पूर्ण

व्योम करो_trap(काष्ठा pt_regs *regs, पूर्णांक signo, पूर्णांक code, अचिन्हित दीर्घ addr)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	अगर (show_unhandled_संकेतs && unhandled_संकेत(tsk, signo)
	    && prपूर्णांकk_ratelimit()) अणु
		pr_info("%s[%d]: unhandled signal %d code 0x%x at 0x%08lx",
			tsk->comm, task_pid_nr(tsk), signo, code, addr);
		prपूर्णांक_vma_addr(KERN_CONT " in ", inकाष्ठाion_poपूर्णांकer(regs));
		pr_cont("\n");
		show_regs(regs);
	पूर्ण

	क्रमce_sig_fault(signo, code, (व्योम __user *)addr);
पूर्ण

अटल व्योम करो_trap_error(काष्ठा pt_regs *regs, पूर्णांक signo, पूर्णांक code,
	अचिन्हित दीर्घ addr, स्थिर अक्षर *str)
अणु
	current->thपढ़ो.trap_no = trap_no(regs);

	अगर (user_mode(regs)) अणु
		करो_trap(regs, signo, code, addr);
	पूर्ण अन्यथा अणु
		अगर (!fixup_exception(regs))
			die(regs, str);
	पूर्ण
पूर्ण

#घोषणा DO_ERROR_INFO(name, signo, code, str)				\
यंत्रlinkage __visible व्योम name(काष्ठा pt_regs *regs)			\
अणु									\
	करो_trap_error(regs, signo, code, regs->pc, "Oops - " str);	\
पूर्ण

DO_ERROR_INFO(करो_trap_unknown,
	संक_अवैध, ILL_ILLTRP, "unknown exception");
DO_ERROR_INFO(करो_trap_zभाग,
	संक_भ_त्रुटि, FPE_INTDIV, "error zero div exception");
DO_ERROR_INFO(करो_trap_buserr,
	संक_अंश, ILL_ILLADR, "error bus error exception");

यंत्रlinkage व्योम करो_trap_misaligned(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_CPU_NEED_SOFTALIGN
	csky_alignment(regs);
#अन्यथा
	current->thपढ़ो.trap_no = trap_no(regs);
	करो_trap_error(regs, SIGBUS, BUS_ADRALN, regs->pc,
		      "Oops - load/store address misaligned");
#पूर्ण_अगर
पूर्ण

यंत्रlinkage व्योम करो_trap_bkpt(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_KPROBES
	अगर (kprobe_single_step_handler(regs))
		वापस;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBES
	अगर (uprobe_single_step_handler(regs))
		वापस;
#पूर्ण_अगर
	अगर (user_mode(regs)) अणु
		send_sig(SIGTRAP, current, 0);
		वापस;
	पूर्ण

	करो_trap_error(regs, संक_अवैध, ILL_ILLTRP, regs->pc,
		      "Oops - illegal trap exception");
पूर्ण

यंत्रlinkage व्योम करो_trap_illinsn(काष्ठा pt_regs *regs)
अणु
	current->thपढ़ो.trap_no = trap_no(regs);

#अगर_घोषित CONFIG_KPROBES
	अगर (kprobe_अवरोधpoपूर्णांक_handler(regs))
		वापस;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBES
	अगर (uprobe_अवरोधpoपूर्णांक_handler(regs))
		वापस;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_CPU_NO_USER_BKPT
	अगर (*(uपूर्णांक16_t *)inकाष्ठाion_poपूर्णांकer(regs) != USR_BKPT) अणु
		send_sig(SIGTRAP, current, 0);
		वापस;
	पूर्ण
#पूर्ण_अगर

	करो_trap_error(regs, संक_अवैध, ILL_ILLOPC, regs->pc,
		      "Oops - illegal instruction exception");
पूर्ण

यंत्रlinkage व्योम करो_trap_fpe(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_CPU_HAS_FP
	वापस fpu_fpe(regs);
#अन्यथा
	करो_trap_error(regs, संक_अवैध, ILL_ILLOPC, regs->pc,
		      "Oops - fpu instruction exception");
#पूर्ण_अगर
पूर्ण

यंत्रlinkage व्योम करो_trap_priv(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_CPU_HAS_FP
	अगर (user_mode(regs) && fpu_libc_helper(regs))
		वापस;
#पूर्ण_अगर
	करो_trap_error(regs, संक_अवैध, ILL_PRVOPC, regs->pc,
		      "Oops - illegal privileged exception");
पूर्ण

यंत्रlinkage व्योम trap_c(काष्ठा pt_regs *regs)
अणु
	चयन (trap_no(regs)) अणु
	हाल VEC_ZERODIV:
		करो_trap_zभाग(regs);
		अवरोध;
	हाल VEC_TRACE:
		करो_trap_bkpt(regs);
		अवरोध;
	हाल VEC_ILLEGAL:
		करो_trap_illinsn(regs);
		अवरोध;
	हाल VEC_TRAP1:
	हाल VEC_BREAKPOINT:
		करो_trap_bkpt(regs);
		अवरोध;
	हाल VEC_ACCESS:
		करो_trap_buserr(regs);
		अवरोध;
	हाल VEC_ALIGN:
		करो_trap_misaligned(regs);
		अवरोध;
	हाल VEC_FPE:
		करो_trap_fpe(regs);
		अवरोध;
	हाल VEC_PRIV:
		करो_trap_priv(regs);
		अवरोध;
	शेष:
		करो_trap_unknown(regs);
		अवरोध;
	पूर्ण
पूर्ण
