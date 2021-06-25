<शैली गुरु>
/*
 * Hardware exception handling
 *
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 * Copyright (C) 2001 Vic Phillips
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/ptrace.h>

#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/sections.h>
#समावेश <linux/uaccess.h>

अटल DEFINE_SPINLOCK(die_lock);

अटल व्योम _send_sig(पूर्णांक signo, पूर्णांक code, अचिन्हित दीर्घ addr)
अणु
	क्रमce_sig_fault(signo, code, (व्योम __user *) addr);
पूर्ण

व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	console_verbose();
	spin_lock_irq(&die_lock);
	pr_warn("Oops: %s, sig: %ld\n", str, err);
	show_regs(regs);
	spin_unlock_irq(&die_lock);
	/*
	 * करो_निकास() should take care of panic'ing from an पूर्णांकerrupt
	 * context so we करोn't handle it here
	 */
	करो_निकास(err);
पूर्ण

व्योम _exception(पूर्णांक signo, काष्ठा pt_regs *regs, पूर्णांक code, अचिन्हित दीर्घ addr)
अणु
	अगर (!user_mode(regs))
		die("Exception in kernel mode", regs, signo);

	_send_sig(signo, code, addr);
पूर्ण

/*
 * The show_stack() is बाह्यal API which we करो not use ourselves.
 */

पूर्णांक kstack_depth_to_prपूर्णांक = 48;

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *stack,
		स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ *endstack, addr;
	पूर्णांक i;

	अगर (!stack) अणु
		अगर (task)
			stack = (अचिन्हित दीर्घ *)task->thपढ़ो.ksp;
		अन्यथा
			stack = (अचिन्हित दीर्घ *)&stack;
	पूर्ण

	addr = (अचिन्हित दीर्घ) stack;
	endstack = (अचिन्हित दीर्घ *) PAGE_ALIGN(addr);

	prपूर्णांकk("%sStack from %08lx:", loglvl, (अचिन्हित दीर्घ)stack);
	क्रम (i = 0; i < kstack_depth_to_prपूर्णांक; i++) अणु
		अगर (stack + 1 > endstack)
			अवरोध;
		अगर (i % 8 == 0)
			prपूर्णांकk("%s\n       ", loglvl);
		prपूर्णांकk("%s %08lx", loglvl, *stack++);
	पूर्ण

	prपूर्णांकk("%s\nCall Trace:", loglvl);
	i = 0;
	जबतक (stack + 1 <= endstack) अणु
		addr = *stack++;
		/*
		 * If the address is either in the text segment of the
		 * kernel, or in the region which contains vदो_स्मृति'ed
		 * memory, it *may* be the address of a calling
		 * routine; अगर so, prपूर्णांक it so that someone tracing
		 * करोwn the cause of the crash will be able to figure
		 * out the call path that was taken.
		 */
		अगर (((addr >= (अचिन्हित दीर्घ) _stext) &&
		     (addr <= (अचिन्हित दीर्घ) _etext))) अणु
			अगर (i % 4 == 0)
				pr_emerg("\n       ");
			prपूर्णांकk("%s [<%08lx>]", loglvl, addr);
			i++;
		पूर्ण
	पूर्ण
	prपूर्णांकk("%s\n", loglvl);
पूर्ण

व्योम __init trap_init(व्योम)
अणु
	/* Nothing to करो here */
पूर्ण

/* Breakpoपूर्णांक handler */
यंत्रlinkage व्योम अवरोधpoपूर्णांक_c(काष्ठा pt_regs *fp)
अणु
	/*
	 * The अवरोधpoपूर्णांक entry code has moved the PC on by 4 bytes, so we must
	 * move it back. This could be करोne on the host but we करो it here
	 * because monitor.S of JTAG gdbserver करोes it too.
	 */
	fp->ea -= 4;
	_exception(SIGTRAP, fp, TRAP_BRKPT, fp->ea);
पूर्ण

#अगर_अघोषित CONFIG_NIOS2_ALIGNMENT_TRAP
/* Alignment exception handler */
यंत्रlinkage व्योम handle_unaligned_c(काष्ठा pt_regs *fp, पूर्णांक cause)
अणु
	अचिन्हित दीर्घ addr = RDCTL(CTL_BADADDR);

	cause >>= 2;
	fp->ea -= 4;

	अगर (fixup_exception(fp))
		वापस;

	अगर (!user_mode(fp)) अणु
		pr_alert("Unaligned access from kernel mode, this might be a hardware\n");
		pr_alert("problem, dump registers and restart the instruction\n");
		pr_alert("  BADADDR 0x%08lx\n", addr);
		pr_alert("  cause   %d\n", cause);
		pr_alert("  op-code 0x%08lx\n", *(अचिन्हित दीर्घ *)(fp->ea));
		show_regs(fp);
		वापस;
	पूर्ण

	_exception(SIGBUS, fp, BUS_ADRALN, addr);
पूर्ण
#पूर्ण_अगर /* CONFIG_NIOS2_ALIGNMENT_TRAP */

/* Illegal inकाष्ठाion handler */
यंत्रlinkage व्योम handle_illegal_c(काष्ठा pt_regs *fp)
अणु
	fp->ea -= 4;
	_exception(संक_अवैध, fp, ILL_ILLOPC, fp->ea);
पूर्ण

/* Supervisor inकाष्ठाion handler */
यंत्रlinkage व्योम handle_supervisor_instr(काष्ठा pt_regs *fp)
अणु
	fp->ea -= 4;
	_exception(संक_अवैध, fp, ILL_PRVOPC, fp->ea);
पूर्ण

/* Division error handler */
यंत्रlinkage व्योम handle_भागerror_c(काष्ठा pt_regs *fp)
अणु
	fp->ea -= 4;
	_exception(संक_भ_त्रुटि, fp, FPE_INTDIV, fp->ea);
पूर्ण

/* Unhandled exception handler */
यंत्रlinkage व्योम unhandled_exception(काष्ठा pt_regs *regs, पूर्णांक cause)
अणु
	अचिन्हित दीर्घ addr = RDCTL(CTL_BADADDR);

	cause /= 4;

	pr_emerg("Unhandled exception #%d in %s mode (badaddr=0x%08lx)\n",
			cause, user_mode(regs) ? "user" : "kernel", addr);

	regs->ea -= 4;
	show_regs(regs);

	pr_emerg("opcode: 0x%08lx\n", *(अचिन्हित दीर्घ *)(regs->ea));
पूर्ण

यंत्रlinkage व्योम handle_trap_1_c(काष्ठा pt_regs *fp)
अणु
	_send_sig(SIGUSR1, 0, fp->ea);
पूर्ण

यंत्रlinkage व्योम handle_trap_2_c(काष्ठा pt_regs *fp)
अणु
	_send_sig(SIGUSR2, 0, fp->ea);
पूर्ण

यंत्रlinkage व्योम handle_trap_3_c(काष्ठा pt_regs *fp)
अणु
	_send_sig(संक_अवैध, ILL_ILLTRP, fp->ea);
पूर्ण
