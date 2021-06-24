<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),
 *
 *  Derived from "arch/i386/kernel/traps.c"
 *    Copyright (C) 1991, 1992 Linus Torvalds
 */

/*
 * 'Traps.c' handles hardware traps and faults after we have saved some
 * state in 'asm.s'.
 */
#समावेश "asm/irqflags.h"
#समावेश "asm/ptrace.h"
#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/अक्रमomize_kstack.h>
#समावेश <linux/extable.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/cpu.h>
#समावेश <linux/entry-common.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश <यंत्र/vसमय.स>
#समावेश "entry.h"

अटल अंतरभूत व्योम __user *get_trap_ip(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ address;

	अगर (regs->पूर्णांक_code & 0x200)
		address = *(अचिन्हित दीर्घ *)(current->thपढ़ो.trap_tdb + 24);
	अन्यथा
		address = regs->psw.addr;
	वापस (व्योम __user *) (address - (regs->पूर्णांक_code >> 16));
पूर्ण

पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ addr)
अणु
	वापस 1;
पूर्ण

व्योम करो_report_trap(काष्ठा pt_regs *regs, पूर्णांक si_signo, पूर्णांक si_code, अक्षर *str)
अणु
	अगर (user_mode(regs)) अणु
		क्रमce_sig_fault(si_signo, si_code, get_trap_ip(regs));
		report_user_fault(regs, si_signo, 0);
        पूर्ण अन्यथा अणु
                स्थिर काष्ठा exception_table_entry *fixup;
		fixup = s390_search_extables(regs->psw.addr);
		अगर (!fixup || !ex_handle(fixup, regs))
			die(regs, str);
        पूर्ण
पूर्ण

अटल व्योम करो_trap(काष्ठा pt_regs *regs, पूर्णांक si_signo, पूर्णांक si_code, अक्षर *str)
अणु
	अगर (notअगरy_die(DIE_TRAP, str, regs, 0,
		       regs->पूर्णांक_code, si_signo) == NOTIFY_STOP)
		वापस;
	करो_report_trap(regs, si_signo, si_code, str);
पूर्ण
NOKPROBE_SYMBOL(करो_trap);

व्योम करो_per_trap(काष्ठा pt_regs *regs)
अणु
	अगर (notअगरy_die(DIE_SSTEP, "sstep", regs, 0, 0, SIGTRAP) == NOTIFY_STOP)
		वापस;
	अगर (!current->ptrace)
		वापस;
	क्रमce_sig_fault(SIGTRAP, TRAP_HWBKPT,
		(व्योम __क्रमce __user *) current->thपढ़ो.per_event.address);
पूर्ण
NOKPROBE_SYMBOL(करो_per_trap);

अटल व्योम शेष_trap_handler(काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs)) अणु
		report_user_fault(regs, संक_अंश, 0);
		करो_निकास(संक_अंश);
	पूर्ण अन्यथा
		die(regs, "Unknown program exception");
पूर्ण

#घोषणा DO_ERROR_INFO(name, signr, sicode, str) \
अटल व्योम name(काष्ठा pt_regs *regs)		\
अणु						\
	करो_trap(regs, signr, sicode, str);	\
पूर्ण

DO_ERROR_INFO(addressing_exception, संक_अवैध, ILL_ILLADR,
	      "addressing exception")
DO_ERROR_INFO(execute_exception, संक_अवैध, ILL_ILLOPN,
	      "execute exception")
DO_ERROR_INFO(भागide_exception, संक_भ_त्रुटि, FPE_INTDIV,
	      "fixpoint divide exception")
DO_ERROR_INFO(overflow_exception, संक_भ_त्रुटि, FPE_INTOVF,
	      "fixpoint overflow exception")
DO_ERROR_INFO(hfp_overflow_exception, संक_भ_त्रुटि, FPE_FLTOVF,
	      "HFP overflow exception")
DO_ERROR_INFO(hfp_underflow_exception, संक_भ_त्रुटि, FPE_FLTUND,
	      "HFP underflow exception")
DO_ERROR_INFO(hfp_signअगरicance_exception, संक_भ_त्रुटि, FPE_FLTRES,
	      "HFP significance exception")
DO_ERROR_INFO(hfp_भागide_exception, संक_भ_त्रुटि, FPE_FLTDIV,
	      "HFP divide exception")
DO_ERROR_INFO(hfp_वर्ग_मूल_exception, संक_भ_त्रुटि, FPE_FLTINV,
	      "HFP square root exception")
DO_ERROR_INFO(opeअक्रम_exception, संक_अवैध, ILL_ILLOPN,
	      "operand exception")
DO_ERROR_INFO(privileged_op, संक_अवैध, ILL_PRVOPC,
	      "privileged operation")
DO_ERROR_INFO(special_op_exception, संक_अवैध, ILL_ILLOPN,
	      "special operation exception")
DO_ERROR_INFO(transaction_exception, संक_अवैध, ILL_ILLOPN,
	      "transaction constraint exception")

अटल अंतरभूत व्योम करो_fp_trap(काष्ठा pt_regs *regs, __u32 fpc)
अणु
	पूर्णांक si_code = 0;
	/* FPC[2] is Data Exception Code */
	अगर ((fpc & 0x00000300) == 0) अणु
		/* bits 6 and 7 of DXC are 0 अगरf IEEE exception */
		अगर (fpc & 0x8000) /* invalid fp operation */
			si_code = FPE_FLTINV;
		अन्यथा अगर (fpc & 0x4000) /* भाग by 0 */
			si_code = FPE_FLTDIV;
		अन्यथा अगर (fpc & 0x2000) /* overflow */
			si_code = FPE_FLTOVF;
		अन्यथा अगर (fpc & 0x1000) /* underflow */
			si_code = FPE_FLTUND;
		अन्यथा अगर (fpc & 0x0800) /* inexact */
			si_code = FPE_FLTRES;
	पूर्ण
	करो_trap(regs, संक_भ_त्रुटि, si_code, "floating point exception");
पूर्ण

अटल व्योम translation_exception(काष्ठा pt_regs *regs)
अणु
	/* May never happen. */
	panic("Translation exception");
पूर्ण

अटल व्योम illegal_op(काष्ठा pt_regs *regs)
अणु
        __u8 opcode[6];
	__u16 __user *location;
	पूर्णांक is_uprobe_insn = 0;
	पूर्णांक संकेत = 0;

	location = get_trap_ip(regs);

	अगर (user_mode(regs)) अणु
		अगर (get_user(*((__u16 *) opcode), (__u16 __user *) location))
			वापस;
		अगर (*((__u16 *) opcode) == S390_BREAKPOINT_U16) अणु
			अगर (current->ptrace)
				क्रमce_sig_fault(SIGTRAP, TRAP_BRKPT, location);
			अन्यथा
				संकेत = संक_अवैध;
#अगर_घोषित CONFIG_UPROBES
		पूर्ण अन्यथा अगर (*((__u16 *) opcode) == UPROBE_SWBP_INSN) अणु
			is_uprobe_insn = 1;
#पूर्ण_अगर
		पूर्ण अन्यथा
			संकेत = संक_अवैध;
	पूर्ण
	/*
	 * We got either an illegal op in kernel mode, or user space trapped
	 * on a uprobes illegal inकाष्ठाion. See अगर kprobes or uprobes picks
	 * it up. If not, संक_अवैध.
	 */
	अगर (is_uprobe_insn || !user_mode(regs)) अणु
		अगर (notअगरy_die(DIE_BPT, "bpt", regs, 0,
			       3, SIGTRAP) != NOTIFY_STOP)
			संकेत = संक_अवैध;
	पूर्ण
	अगर (संकेत)
		करो_trap(regs, संकेत, ILL_ILLOPC, "illegal operation");
पूर्ण
NOKPROBE_SYMBOL(illegal_op);

DO_ERROR_INFO(specअगरication_exception, संक_अवैध, ILL_ILLOPN,
	      "specification exception");

अटल व्योम vector_exception(काष्ठा pt_regs *regs)
अणु
	पूर्णांक si_code, vic;

	अगर (!MACHINE_HAS_VX) अणु
		करो_trap(regs, संक_अवैध, ILL_ILLOPN, "illegal operation");
		वापस;
	पूर्ण

	/* get vector पूर्णांकerrupt code from fpc */
	save_fpu_regs();
	vic = (current->thपढ़ो.fpu.fpc & 0xf00) >> 8;
	चयन (vic) अणु
	हाल 1: /* invalid vector operation */
		si_code = FPE_FLTINV;
		अवरोध;
	हाल 2: /* भागision by zero */
		si_code = FPE_FLTDIV;
		अवरोध;
	हाल 3: /* overflow */
		si_code = FPE_FLTOVF;
		अवरोध;
	हाल 4: /* underflow */
		si_code = FPE_FLTUND;
		अवरोध;
	हाल 5:	/* inexact */
		si_code = FPE_FLTRES;
		अवरोध;
	शेष: /* unknown cause */
		si_code = 0;
	पूर्ण
	करो_trap(regs, संक_भ_त्रुटि, si_code, "vector exception");
पूर्ण

अटल व्योम data_exception(काष्ठा pt_regs *regs)
अणु
	save_fpu_regs();
	अगर (current->thपढ़ो.fpu.fpc & FPC_DXC_MASK)
		करो_fp_trap(regs, current->thपढ़ो.fpu.fpc);
	अन्यथा
		करो_trap(regs, संक_अवैध, ILL_ILLOPN, "data exception");
पूर्ण

अटल व्योम space_चयन_exception(काष्ठा pt_regs *regs)
अणु
	/* Set user psw back to home space mode. */
	अगर (user_mode(regs))
		regs->psw.mask |= PSW_ASC_HOME;
	/* Send संक_अवैध. */
	करो_trap(regs, संक_अवैध, ILL_PRVOPC, "space switch event");
पूर्ण

अटल व्योम monitor_event_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fixup;

	अगर (user_mode(regs))
		वापस;

	चयन (report_bug(regs->psw.addr - (regs->पूर्णांक_code >> 16), regs)) अणु
	हाल BUG_TRAP_TYPE_NONE:
		fixup = s390_search_extables(regs->psw.addr);
		अगर (fixup)
			ex_handle(fixup, regs);
		अवरोध;
	हाल BUG_TRAP_TYPE_WARN:
		अवरोध;
	हाल BUG_TRAP_TYPE_BUG:
		die(regs, "monitor event");
		अवरोध;
	पूर्ण
पूर्ण

व्योम kernel_stack_overflow(काष्ठा pt_regs *regs)
अणु
	bust_spinlocks(1);
	prपूर्णांकk("Kernel stack overflow.\n");
	show_regs(regs);
	bust_spinlocks(0);
	panic("Corrupt kernel stack, can't continue.");
पूर्ण
NOKPROBE_SYMBOL(kernel_stack_overflow);

अटल व्योम __init test_monitor_call(व्योम)
अणु
	पूर्णांक val = 1;

	यंत्र अस्थिर(
		"	mc	0,0\n"
		"0:	xgr	%0,%0\n"
		"1:\n"
		EX_TABLE(0b,1b)
		: "+d" (val));
	अगर (!val)
		panic("Monitor call doesn't work!\n");
पूर्ण

व्योम __init trap_init(व्योम)
अणु
	sort_extable(__start_dma_ex_table, __stop_dma_ex_table);
	local_mcck_enable();
	test_monitor_call();
पूर्ण

अटल व्योम (*pgm_check_table[128])(काष्ठा pt_regs *regs);

व्योम noinstr __करो_pgm_check(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ last_अवरोध = S390_lowcore.अवरोधing_event_addr;
	अचिन्हित पूर्णांक trapnr, syscall_redirect = 0;
	irqentry_state_t state;

	add_अक्रमom_kstack_offset();
	regs->पूर्णांक_code = *(u32 *)&S390_lowcore.pgm_ilc;
	regs->पूर्णांक_parm_दीर्घ = S390_lowcore.trans_exc_code;

	state = irqentry_enter(regs);

	अगर (user_mode(regs)) अणु
		update_समयr_sys();
		अगर (last_अवरोध < 4096)
			last_अवरोध = 1;
		current->thपढ़ो.last_अवरोध = last_अवरोध;
		regs->args[0] = last_अवरोध;
	पूर्ण

	अगर (S390_lowcore.pgm_code & 0x0200) अणु
		/* transaction पात */
		स_नकल(&current->thपढ़ो.trap_tdb, &S390_lowcore.pgm_tdb, 256);
	पूर्ण

	अगर (S390_lowcore.pgm_code & PGM_INT_CODE_PER) अणु
		अगर (user_mode(regs)) अणु
			काष्ठा per_event *ev = &current->thपढ़ो.per_event;

			set_thपढ़ो_flag(TIF_PER_TRAP);
			ev->address = S390_lowcore.per_address;
			ev->cause = *(u16 *)&S390_lowcore.per_code;
			ev->paid = S390_lowcore.per_access_id;
		पूर्ण अन्यथा अणु
			/* PER event in kernel is kprobes */
			__arch_local_irq_ssm(regs->psw.mask & ~PSW_MASK_PER);
			करो_per_trap(regs);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!irqs_disabled_flags(regs->psw.mask))
		trace_hardirqs_on();
	__arch_local_irq_ssm(regs->psw.mask & ~PSW_MASK_PER);

	trapnr = regs->पूर्णांक_code & PGM_INT_CODE_MASK;
	अगर (trapnr)
		pgm_check_table[trapnr](regs);
	syscall_redirect = user_mode(regs) && test_pt_regs_flag(regs, PIF_SYSCALL);
out:
	local_irq_disable();
	irqentry_निकास(regs, state);

	अगर (syscall_redirect) अणु
		enter_from_user_mode(regs);
		local_irq_enable();
		regs->orig_gpr2 = regs->gprs[2];
		करो_syscall(regs);
		निकास_to_user_mode();
	पूर्ण
पूर्ण

/*
 * The program check table contains exactly 128 (0x00-0x7f) entries. Each
 * line defines the function to be called corresponding to the program check
 * पूर्णांकerruption code.
 */
अटल व्योम (*pgm_check_table[128])(काष्ठा pt_regs *regs) = अणु
	[0x00]		= शेष_trap_handler,
	[0x01]		= illegal_op,
	[0x02]		= privileged_op,
	[0x03]		= execute_exception,
	[0x04]		= करो_protection_exception,
	[0x05]		= addressing_exception,
	[0x06]		= specअगरication_exception,
	[0x07]		= data_exception,
	[0x08]		= overflow_exception,
	[0x09]		= भागide_exception,
	[0x0a]		= overflow_exception,
	[0x0b]		= भागide_exception,
	[0x0c]		= hfp_overflow_exception,
	[0x0d]		= hfp_underflow_exception,
	[0x0e]		= hfp_signअगरicance_exception,
	[0x0f]		= hfp_भागide_exception,
	[0x10]		= करो_dat_exception,
	[0x11]		= करो_dat_exception,
	[0x12]		= translation_exception,
	[0x13]		= special_op_exception,
	[0x14]		= शेष_trap_handler,
	[0x15]		= opeअक्रम_exception,
	[0x16]		= शेष_trap_handler,
	[0x17]		= शेष_trap_handler,
	[0x18]		= transaction_exception,
	[0x19]		= शेष_trap_handler,
	[0x1a]		= शेष_trap_handler,
	[0x1b]		= vector_exception,
	[0x1c]		= space_चयन_exception,
	[0x1d]		= hfp_वर्ग_मूल_exception,
	[0x1e ... 0x37] = शेष_trap_handler,
	[0x38]		= करो_dat_exception,
	[0x39]		= करो_dat_exception,
	[0x3a]		= करो_dat_exception,
	[0x3b]		= करो_dat_exception,
	[0x3c]		= शेष_trap_handler,
	[0x3d]		= करो_secure_storage_access,
	[0x3e]		= करो_non_secure_storage_access,
	[0x3f]		= करो_secure_storage_violation,
	[0x40]		= monitor_event_exception,
	[0x41 ... 0x7f] = शेष_trap_handler,
पूर्ण;

#घोषणा COND_TRAP(x) यंत्र(			\
	".weak " __stringअगरy(x) "\n\t"		\
	".set  " __stringअगरy(x) ","		\
	__stringअगरy(शेष_trap_handler))

COND_TRAP(करो_secure_storage_access);
COND_TRAP(करो_non_secure_storage_access);
COND_TRAP(करो_secure_storage_violation);
