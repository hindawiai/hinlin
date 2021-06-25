<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/kdebug.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/csr.h>

पूर्णांक show_unhandled_संकेतs = 1;

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

	ret = notअगरy_die(DIE_OOPS, str, regs, 0, regs->cause, संक_अंश);

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
		pr_info("%s[%d]: unhandled signal %d code 0x%x at 0x" REG_FMT,
			tsk->comm, task_pid_nr(tsk), signo, code, addr);
		prपूर्णांक_vma_addr(KERN_CONT " in ", inकाष्ठाion_poपूर्णांकer(regs));
		pr_cont("\n");
		__show_regs(regs);
	पूर्ण

	क्रमce_sig_fault(signo, code, (व्योम __user *)addr);
पूर्ण

अटल व्योम करो_trap_error(काष्ठा pt_regs *regs, पूर्णांक signo, पूर्णांक code,
	अचिन्हित दीर्घ addr, स्थिर अक्षर *str)
अणु
	current->thपढ़ो.bad_cause = regs->cause;

	अगर (user_mode(regs)) अणु
		करो_trap(regs, signo, code, addr);
	पूर्ण अन्यथा अणु
		अगर (!fixup_exception(regs))
			die(regs, str);
	पूर्ण
पूर्ण

#अगर defined (CONFIG_XIP_KERNEL) && defined (CONFIG_RISCV_ERRATA_ALTERNATIVE)
#घोषणा __trap_section		__section(".xip.traps")
#अन्यथा
#घोषणा __trap_section
#पूर्ण_अगर
#घोषणा DO_ERROR_INFO(name, signo, code, str)				\
यंत्रlinkage __visible __trap_section व्योम name(काष्ठा pt_regs *regs)	\
अणु									\
	करो_trap_error(regs, signo, code, regs->epc, "Oops - " str);	\
पूर्ण

DO_ERROR_INFO(करो_trap_unknown,
	संक_अवैध, ILL_ILLTRP, "unknown exception");
DO_ERROR_INFO(करो_trap_insn_misaligned,
	SIGBUS, BUS_ADRALN, "instruction address misaligned");
DO_ERROR_INFO(करो_trap_insn_fault,
	संक_अंश, SEGV_ACCERR, "instruction access fault");
DO_ERROR_INFO(करो_trap_insn_illegal,
	संक_अवैध, ILL_ILLOPC, "illegal instruction");
DO_ERROR_INFO(करो_trap_load_fault,
	संक_अंश, SEGV_ACCERR, "load access fault");
#अगर_अघोषित CONFIG_RISCV_M_MODE
DO_ERROR_INFO(करो_trap_load_misaligned,
	SIGBUS, BUS_ADRALN, "Oops - load address misaligned");
DO_ERROR_INFO(करो_trap_store_misaligned,
	SIGBUS, BUS_ADRALN, "Oops - store (or AMO) address misaligned");
#अन्यथा
पूर्णांक handle_misaligned_load(काष्ठा pt_regs *regs);
पूर्णांक handle_misaligned_store(काष्ठा pt_regs *regs);

यंत्रlinkage व्योम __trap_section करो_trap_load_misaligned(काष्ठा pt_regs *regs)
अणु
	अगर (!handle_misaligned_load(regs))
		वापस;
	करो_trap_error(regs, SIGBUS, BUS_ADRALN, regs->epc,
		      "Oops - load address misaligned");
पूर्ण

यंत्रlinkage व्योम __trap_section करो_trap_store_misaligned(काष्ठा pt_regs *regs)
अणु
	अगर (!handle_misaligned_store(regs))
		वापस;
	करो_trap_error(regs, SIGBUS, BUS_ADRALN, regs->epc,
		      "Oops - store (or AMO) address misaligned");
पूर्ण
#पूर्ण_अगर
DO_ERROR_INFO(करो_trap_store_fault,
	संक_अंश, SEGV_ACCERR, "store (or AMO) access fault");
DO_ERROR_INFO(करो_trap_ecall_u,
	संक_अवैध, ILL_ILLTRP, "environment call from U-mode");
DO_ERROR_INFO(करो_trap_ecall_s,
	संक_अवैध, ILL_ILLTRP, "environment call from S-mode");
DO_ERROR_INFO(करो_trap_ecall_m,
	संक_अवैध, ILL_ILLTRP, "environment call from M-mode");

अटल अंतरभूत अचिन्हित दीर्घ get_अवरोध_insn_length(अचिन्हित दीर्घ pc)
अणु
	bug_insn_t insn;

	अगर (get_kernel_nofault(insn, (bug_insn_t *)pc))
		वापस 0;

	वापस GET_INSN_LENGTH(insn);
पूर्ण

यंत्रlinkage __visible __trap_section व्योम करो_trap_अवरोध(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_KPROBES
	अगर (kprobe_single_step_handler(regs))
		वापस;

	अगर (kprobe_अवरोधpoपूर्णांक_handler(regs))
		वापस;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBES
	अगर (uprobe_single_step_handler(regs))
		वापस;

	अगर (uprobe_अवरोधpoपूर्णांक_handler(regs))
		वापस;
#पूर्ण_अगर
	current->thपढ़ो.bad_cause = regs->cause;

	अगर (user_mode(regs))
		क्रमce_sig_fault(SIGTRAP, TRAP_BRKPT, (व्योम __user *)regs->epc);
#अगर_घोषित CONFIG_KGDB
	अन्यथा अगर (notअगरy_die(DIE_TRAP, "EBREAK", regs, 0, regs->cause, SIGTRAP)
								== NOTIFY_STOP)
		वापस;
#पूर्ण_अगर
	अन्यथा अगर (report_bug(regs->epc, regs) == BUG_TRAP_TYPE_WARN)
		regs->epc += get_अवरोध_insn_length(regs->epc);
	अन्यथा
		die(regs, "Kernel BUG");
पूर्ण
NOKPROBE_SYMBOL(करो_trap_अवरोध);

#अगर_घोषित CONFIG_GENERIC_BUG
पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ pc)
अणु
	bug_insn_t insn;

	अगर (pc < VMALLOC_START)
		वापस 0;
	अगर (get_kernel_nofault(insn, (bug_insn_t *)pc))
		वापस 0;
	अगर ((insn & __INSN_LENGTH_MASK) == __INSN_LENGTH_32)
		वापस (insn == __BUG_INSN_32);
	अन्यथा
		वापस ((insn & __COMPRESSED_INSN_MASK) == __BUG_INSN_16);
पूर्ण
#पूर्ण_अगर /* CONFIG_GENERIC_BUG */

/* stvec & scratch is alपढ़ोy set from head.S */
व्योम __init trap_init(व्योम)
अणु
पूर्ण
