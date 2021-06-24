<शैली गुरु>
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 2000, 2001, 2002 Andi Kleen, SuSE Lअसल
 *
 *  Pentium III FXSR, SSE support
 *	Gareth Hughes <gareth@valinux.com>, May 2000
 */

/*
 * Handle hardware traps and faults.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/context_tracking.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kexec.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/bug.h>
#समावेश <linux/nmi.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/पन.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/atomic.h>

#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/debugreg.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/mach_traps.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/fpu/xstate.h>
#समावेश <यंत्र/vm86.h>
#समावेश <यंत्र/umip.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/insn-eval.h>
#समावेश <यंत्र/vdso.h>

#अगर_घोषित CONFIG_X86_64
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/proto.h>
#अन्यथा
#समावेश <यंत्र/processor-flags.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/proto.h>
#पूर्ण_अगर

DECLARE_BITMAP(प्रणाली_vectors, NR_VECTORS);

अटल अंतरभूत व्योम cond_local_irq_enable(काष्ठा pt_regs *regs)
अणु
	अगर (regs->flags & X86_EFLAGS_IF)
		local_irq_enable();
पूर्ण

अटल अंतरभूत व्योम cond_local_irq_disable(काष्ठा pt_regs *regs)
अणु
	अगर (regs->flags & X86_EFLAGS_IF)
		local_irq_disable();
पूर्ण

__always_अंतरभूत पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ addr)
अणु
	अगर (addr < TASK_SIZE_MAX)
		वापस 0;

	/*
	 * We got #UD, अगर the text isn't readable we'd have gotten
	 * a dअगरferent exception.
	 */
	वापस *(अचिन्हित लघु *)addr == INSN_UD2;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक
करो_trap_no_संकेत(काष्ठा task_काष्ठा *tsk, पूर्णांक trapnr, स्थिर अक्षर *str,
		  काष्ठा pt_regs *regs,	दीर्घ error_code)
अणु
	अगर (v8086_mode(regs)) अणु
		/*
		 * Traps 0, 1, 3, 4, and 5 should be क्रमwarded to vm86.
		 * On nmi (पूर्णांकerrupt 2), करो_trap should not be called.
		 */
		अगर (trapnr < X86_TRAP_UD) अणु
			अगर (!handle_vm86_trap((काष्ठा kernel_vm86_regs *) regs,
						error_code, trapnr))
				वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (!user_mode(regs)) अणु
		अगर (fixup_exception(regs, trapnr, error_code, 0))
			वापस 0;

		tsk->thपढ़ो.error_code = error_code;
		tsk->thपढ़ो.trap_nr = trapnr;
		die(str, regs, error_code);
	पूर्ण अन्यथा अणु
		अगर (fixup_vdso_exception(regs, trapnr, error_code, 0))
			वापस 0;
	पूर्ण

	/*
	 * We want error_code and trap_nr set क्रम userspace faults and
	 * kernelspace faults which result in die(), but not
	 * kernelspace faults which are fixed up.  die() gives the
	 * process no chance to handle the संकेत and notice the
	 * kernel fault inक्रमmation, so that won't result in polluting
	 * the inक्रमmation about previously queued, but not yet
	 * delivered, faults.  See also exc_general_protection below.
	 */
	tsk->thपढ़ो.error_code = error_code;
	tsk->thपढ़ो.trap_nr = trapnr;

	वापस -1;
पूर्ण

अटल व्योम show_संकेत(काष्ठा task_काष्ठा *tsk, पूर्णांक signr,
			स्थिर अक्षर *type, स्थिर अक्षर *desc,
			काष्ठा pt_regs *regs, दीर्घ error_code)
अणु
	अगर (show_unhandled_संकेतs && unhandled_संकेत(tsk, signr) &&
	    prपूर्णांकk_ratelimit()) अणु
		pr_info("%s[%d] %s%s ip:%lx sp:%lx error:%lx",
			tsk->comm, task_pid_nr(tsk), type, desc,
			regs->ip, regs->sp, error_code);
		prपूर्णांक_vma_addr(KERN_CONT " in ", regs->ip);
		pr_cont("\n");
	पूर्ण
पूर्ण

अटल व्योम
करो_trap(पूर्णांक trapnr, पूर्णांक signr, अक्षर *str, काष्ठा pt_regs *regs,
	दीर्घ error_code, पूर्णांक sicode, व्योम __user *addr)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	अगर (!करो_trap_no_संकेत(tsk, trapnr, str, regs, error_code))
		वापस;

	show_संकेत(tsk, signr, "trap ", str, regs, error_code);

	अगर (!sicode)
		क्रमce_sig(signr);
	अन्यथा
		क्रमce_sig_fault(signr, sicode, addr);
पूर्ण
NOKPROBE_SYMBOL(करो_trap);

अटल व्योम करो_error_trap(काष्ठा pt_regs *regs, दीर्घ error_code, अक्षर *str,
	अचिन्हित दीर्घ trapnr, पूर्णांक signr, पूर्णांक sicode, व्योम __user *addr)
अणु
	RCU_LOCKDEP_WARN(!rcu_is_watching(), "entry code didn't wake RCU");

	अगर (notअगरy_die(DIE_TRAP, str, regs, error_code, trapnr, signr) !=
			NOTIFY_STOP) अणु
		cond_local_irq_enable(regs);
		करो_trap(trapnr, signr, str, regs, error_code, sicode, addr);
		cond_local_irq_disable(regs);
	पूर्ण
पूर्ण

/*
 * Posix requires to provide the address of the faulting inकाष्ठाion क्रम
 * संक_अवैध (#UD) and संक_भ_त्रुटि (#DE) in the si_addr member of siginfo_t.
 *
 * This address is usually regs->ip, but when an uprobe moved the code out
 * of line then regs->ip poपूर्णांकs to the XOL code which would confuse
 * anything which analyzes the fault address vs. the unmodअगरied binary. If
 * a trap happened in XOL code then uprobe maps regs->ip back to the
 * original inकाष्ठाion address.
 */
अटल __always_अंतरभूत व्योम __user *error_get_trap_addr(काष्ठा pt_regs *regs)
अणु
	वापस (व्योम __user *)uprobe_get_trap_addr(regs);
पूर्ण

DEFINE_IDTENTRY(exc_भागide_error)
अणु
	करो_error_trap(regs, 0, "divide error", X86_TRAP_DE, संक_भ_त्रुटि,
		      FPE_INTDIV, error_get_trap_addr(regs));
पूर्ण

DEFINE_IDTENTRY(exc_overflow)
अणु
	करो_error_trap(regs, 0, "overflow", X86_TRAP_OF, संक_अंश, 0, शून्य);
पूर्ण

#अगर_घोषित CONFIG_X86_F00F_BUG
व्योम handle_invalid_op(काष्ठा pt_regs *regs)
#अन्यथा
अटल अंतरभूत व्योम handle_invalid_op(काष्ठा pt_regs *regs)
#पूर्ण_अगर
अणु
	करो_error_trap(regs, 0, "invalid opcode", X86_TRAP_UD, संक_अवैध,
		      ILL_ILLOPN, error_get_trap_addr(regs));
पूर्ण

अटल noinstr bool handle_bug(काष्ठा pt_regs *regs)
अणु
	bool handled = false;

	अगर (!is_valid_bugaddr(regs->ip))
		वापस handled;

	/*
	 * All lies, just get the WARN/BUG out.
	 */
	instrumentation_begin();
	/*
	 * Since we're emulating a CALL with exceptions, restore the पूर्णांकerrupt
	 * state to what it was at the exception site.
	 */
	अगर (regs->flags & X86_EFLAGS_IF)
		raw_local_irq_enable();
	अगर (report_bug(regs->ip, regs) == BUG_TRAP_TYPE_WARN) अणु
		regs->ip += LEN_UD2;
		handled = true;
	पूर्ण
	अगर (regs->flags & X86_EFLAGS_IF)
		raw_local_irq_disable();
	instrumentation_end();

	वापस handled;
पूर्ण

DEFINE_IDTENTRY_RAW(exc_invalid_op)
अणु
	irqentry_state_t state;

	/*
	 * We use UD2 as a लघु encoding क्रम 'CALL __WARN', as such
	 * handle it beक्रमe exception entry to aव्योम recursive WARN
	 * in हाल exception entry is the one triggering WARNs.
	 */
	अगर (!user_mode(regs) && handle_bug(regs))
		वापस;

	state = irqentry_enter(regs);
	instrumentation_begin();
	handle_invalid_op(regs);
	instrumentation_end();
	irqentry_निकास(regs, state);
पूर्ण

DEFINE_IDTENTRY(exc_coproc_segment_overrun)
अणु
	करो_error_trap(regs, 0, "coprocessor segment overrun",
		      X86_TRAP_OLD_MF, संक_भ_त्रुटि, 0, शून्य);
पूर्ण

DEFINE_IDTENTRY_ERRORCODE(exc_invalid_tss)
अणु
	करो_error_trap(regs, error_code, "invalid TSS", X86_TRAP_TS, संक_अंश,
		      0, शून्य);
पूर्ण

DEFINE_IDTENTRY_ERRORCODE(exc_segment_not_present)
अणु
	करो_error_trap(regs, error_code, "segment not present", X86_TRAP_NP,
		      SIGBUS, 0, शून्य);
पूर्ण

DEFINE_IDTENTRY_ERRORCODE(exc_stack_segment)
अणु
	करो_error_trap(regs, error_code, "stack segment", X86_TRAP_SS, SIGBUS,
		      0, शून्य);
पूर्ण

DEFINE_IDTENTRY_ERRORCODE(exc_alignment_check)
अणु
	अक्षर *str = "alignment check";

	अगर (notअगरy_die(DIE_TRAP, str, regs, error_code, X86_TRAP_AC, SIGBUS) == NOTIFY_STOP)
		वापस;

	अगर (!user_mode(regs))
		die("Split lock detected\n", regs, error_code);

	local_irq_enable();

	अगर (handle_user_split_lock(regs, error_code))
		जाओ out;

	करो_trap(X86_TRAP_AC, SIGBUS, "alignment check", regs,
		error_code, BUS_ADRALN, शून्य);

out:
	local_irq_disable();
पूर्ण

#अगर_घोषित CONFIG_VMAP_STACK
__visible व्योम __noवापस handle_stack_overflow(स्थिर अक्षर *message,
						काष्ठा pt_regs *regs,
						अचिन्हित दीर्घ fault_address)
अणु
	prपूर्णांकk(KERN_EMERG "BUG: stack guard page was hit at %p (stack is %p..%p)\n",
		 (व्योम *)fault_address, current->stack,
		 (अक्षर *)current->stack + THREAD_SIZE - 1);
	die(message, regs, 0);

	/* Be असलolutely certain we करोn't वापस. */
	panic("%s", message);
पूर्ण
#पूर्ण_अगर

/*
 * Runs on an IST stack क्रम x86_64 and on a special task stack क्रम x86_32.
 *
 * On x86_64, this is more or less a normal kernel entry.  Notwithstanding the
 * SDM's warnings about द्विगुन faults being unrecoverable, वापसing works as
 * expected.  Presumably what the SDM actually means is that the CPU may get
 * the रेजिस्टर state wrong on entry, so वापसing could be a bad idea.
 *
 * Various CPU engineers have promised that द्विगुन faults due to an IRET fault
 * जबतक the stack is पढ़ो-only are, in fact, recoverable.
 *
 * On x86_32, this is entered through a task gate, and regs are synthesized
 * from the TSS.  Returning is, in principle, okay, but changes to regs will
 * be lost.  If, क्रम some reason, we need to वापस to a context with modअगरied
 * regs, the shim code could be adjusted to synchronize the रेजिस्टरs.
 *
 * The 32bit #DF shim provides CR2 alपढ़ोy as an argument. On 64bit it needs
 * to be पढ़ो beक्रमe करोing anything अन्यथा.
 */
DEFINE_IDTENTRY_DF(exc_द्विगुन_fault)
अणु
	अटल स्थिर अक्षर str[] = "double fault";
	काष्ठा task_काष्ठा *tsk = current;

#अगर_घोषित CONFIG_VMAP_STACK
	अचिन्हित दीर्घ address = पढ़ो_cr2();
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_ESPFIX64
	बाह्य अचिन्हित अक्षर native_irq_वापस_iret[];

	/*
	 * If IRET takes a non-IST fault on the espfix64 stack, then we
	 * end up promoting it to a द्विगुनfault.  In that हाल, take
	 * advantage of the fact that we're not using the normal (TSS.sp0)
	 * stack right now.  We can ग_लिखो a fake #GP(0) frame at TSS.sp0
	 * and then modअगरy our own IRET frame so that, when we वापस,
	 * we land directly at the #GP(0) vector with the stack alपढ़ोy
	 * set up according to its expectations.
	 *
	 * The net result is that our #GP handler will think that we
	 * entered from usermode with the bad user context.
	 *
	 * No need क्रम nmi_enter() here because we करोn't use RCU.
	 */
	अगर (((दीर्घ)regs->sp >> P4D_SHIFT) == ESPFIX_PGD_ENTRY &&
		regs->cs == __KERNEL_CS &&
		regs->ip == (अचिन्हित दीर्घ)native_irq_वापस_iret)
	अणु
		काष्ठा pt_regs *gpregs = (काष्ठा pt_regs *)this_cpu_पढ़ो(cpu_tss_rw.x86_tss.sp0) - 1;
		अचिन्हित दीर्घ *p = (अचिन्हित दीर्घ *)regs->sp;

		/*
		 * regs->sp poपूर्णांकs to the failing IRET frame on the
		 * ESPFIX64 stack.  Copy it to the entry stack.  This fills
		 * in gpregs->ss through gpregs->ip.
		 *
		 */
		gpregs->ip	= p[0];
		gpregs->cs	= p[1];
		gpregs->flags	= p[2];
		gpregs->sp	= p[3];
		gpregs->ss	= p[4];
		gpregs->orig_ax = 0;  /* Missing (lost) #GP error code */

		/*
		 * Adjust our frame so that we वापस straight to the #GP
		 * vector with the expected RSP value.  This is safe because
		 * we won't enable पूर्णांकerrupts or schedule beक्रमe we invoke
		 * general_protection, so nothing will clobber the stack
		 * frame we just set up.
		 *
		 * We will enter general_protection with kernel GSBASE,
		 * which is what the stub expects, given that the faulting
		 * RIP will be the IRET inकाष्ठाion.
		 */
		regs->ip = (अचिन्हित दीर्घ)यंत्र_exc_general_protection;
		regs->sp = (अचिन्हित दीर्घ)&gpregs->orig_ax;

		वापस;
	पूर्ण
#पूर्ण_अगर

	irqentry_nmi_enter(regs);
	instrumentation_begin();
	notअगरy_die(DIE_TRAP, str, regs, error_code, X86_TRAP_DF, संक_अंश);

	tsk->thपढ़ो.error_code = error_code;
	tsk->thपढ़ो.trap_nr = X86_TRAP_DF;

#अगर_घोषित CONFIG_VMAP_STACK
	/*
	 * If we overflow the stack पूर्णांकo a guard page, the CPU will fail
	 * to deliver #PF and will send #DF instead.  Similarly, अगर we
	 * take any non-IST exception जबतक too बंद to the bottom of
	 * the stack, the processor will get a page fault जबतक
	 * delivering the exception and will generate a द्विगुन fault.
	 *
	 * According to the SDM (footnote in 6.15 under "Interrupt 14 -
	 * Page-Fault Exception (#PF):
	 *
	 *   Processors update CR2 whenever a page fault is detected. If a
	 *   second page fault occurs जबतक an earlier page fault is being
	 *   delivered, the faulting linear address of the second fault will
	 *   overग_लिखो the contents of CR2 (replacing the previous
	 *   address). These updates to CR2 occur even अगर the page fault
	 *   results in a द्विगुन fault or occurs during the delivery of a
	 *   द्विगुन fault.
	 *
	 * The logic below has a small possibility of incorrectly diagnosing
	 * some errors as stack overflows.  For example, अगर the IDT or GDT
	 * माला_लो corrupted such that #GP delivery fails due to a bad descriptor
	 * causing #GP and we hit this condition जबतक CR2 coincidentally
	 * poपूर्णांकs to the stack guard page, we'll think we overflowed the
	 * stack.  Given that we're going to panic one way or another
	 * अगर this happens, this isn't necessarily worth fixing.
	 *
	 * If necessary, we could improve the test by only diagnosing
	 * a stack overflow अगर the saved RSP poपूर्णांकs within 47 bytes of
	 * the bottom of the stack: अगर RSP == tsk_stack + 48 and we
	 * take an exception, the stack is alपढ़ोy aligned and there
	 * will be enough room SS, RSP, RFLAGS, CS, RIP, and a
	 * possible error code, so a stack overflow would *not* द्विगुन
	 * fault.  With any less space left, exception delivery could
	 * fail, and, as a practical matter, we've overflowed the
	 * stack even अगर the actual trigger क्रम the द्विगुन fault was
	 * something अन्यथा.
	 */
	अगर ((अचिन्हित दीर्घ)task_stack_page(tsk) - 1 - address < PAGE_SIZE) अणु
		handle_stack_overflow("kernel stack overflow (double-fault)",
				      regs, address);
	पूर्ण
#पूर्ण_अगर

	pr_emerg("PANIC: double fault, error_code: 0x%lx\n", error_code);
	die("double fault", regs, error_code);
	panic("Machine halted.");
	instrumentation_end();
पूर्ण

DEFINE_IDTENTRY(exc_bounds)
अणु
	अगर (notअगरy_die(DIE_TRAP, "bounds", regs, 0,
			X86_TRAP_BR, संक_अंश) == NOTIFY_STOP)
		वापस;
	cond_local_irq_enable(regs);

	अगर (!user_mode(regs))
		die("bounds", regs, 0);

	करो_trap(X86_TRAP_BR, संक_अंश, "bounds", regs, 0, 0, शून्य);

	cond_local_irq_disable(regs);
पूर्ण

क्रमागत kernel_gp_hपूर्णांक अणु
	GP_NO_HINT,
	GP_NON_CANONICAL,
	GP_CANONICAL
पूर्ण;

/*
 * When an uncaught #GP occurs, try to determine the memory address accessed by
 * the inकाष्ठाion and वापस that address to the caller. Also, try to figure
 * out whether any part of the access to that address was non-canonical.
 */
अटल क्रमागत kernel_gp_hपूर्णांक get_kernel_gp_address(काष्ठा pt_regs *regs,
						 अचिन्हित दीर्घ *addr)
अणु
	u8 insn_buf[MAX_INSN_SIZE];
	काष्ठा insn insn;
	पूर्णांक ret;

	अगर (copy_from_kernel_nofault(insn_buf, (व्योम *)regs->ip,
			MAX_INSN_SIZE))
		वापस GP_NO_HINT;

	ret = insn_decode_kernel(&insn, insn_buf);
	अगर (ret < 0)
		वापस GP_NO_HINT;

	*addr = (अचिन्हित दीर्घ)insn_get_addr_ref(&insn, regs);
	अगर (*addr == -1UL)
		वापस GP_NO_HINT;

#अगर_घोषित CONFIG_X86_64
	/*
	 * Check that:
	 *  - the opeअक्रम is not in the kernel half
	 *  - the last byte of the opeअक्रम is not in the user canonical half
	 */
	अगर (*addr < ~__VIRTUAL_MASK &&
	    *addr + insn.opnd_bytes - 1 > __VIRTUAL_MASK)
		वापस GP_NON_CANONICAL;
#पूर्ण_अगर

	वापस GP_CANONICAL;
पूर्ण

#घोषणा GPFSTR "general protection fault"

DEFINE_IDTENTRY_ERRORCODE(exc_general_protection)
अणु
	अक्षर desc[माप(GPFSTR) + 50 + 2*माप(अचिन्हित दीर्घ) + 1] = GPFSTR;
	क्रमागत kernel_gp_hपूर्णांक hपूर्णांक = GP_NO_HINT;
	काष्ठा task_काष्ठा *tsk;
	अचिन्हित दीर्घ gp_addr;
	पूर्णांक ret;

	cond_local_irq_enable(regs);

	अगर (अटल_cpu_has(X86_FEATURE_UMIP)) अणु
		अगर (user_mode(regs) && fixup_umip_exception(regs))
			जाओ निकास;
	पूर्ण

	अगर (v8086_mode(regs)) अणु
		local_irq_enable();
		handle_vm86_fault((काष्ठा kernel_vm86_regs *) regs, error_code);
		local_irq_disable();
		वापस;
	पूर्ण

	tsk = current;

	अगर (user_mode(regs)) अणु
		tsk->thपढ़ो.error_code = error_code;
		tsk->thपढ़ो.trap_nr = X86_TRAP_GP;

		अगर (fixup_vdso_exception(regs, X86_TRAP_GP, error_code, 0))
			जाओ निकास;

		show_संकेत(tsk, संक_अंश, "", desc, regs, error_code);
		क्रमce_sig(संक_अंश);
		जाओ निकास;
	पूर्ण

	अगर (fixup_exception(regs, X86_TRAP_GP, error_code, 0))
		जाओ निकास;

	tsk->thपढ़ो.error_code = error_code;
	tsk->thपढ़ो.trap_nr = X86_TRAP_GP;

	/*
	 * To be potentially processing a kprobe fault and to trust the result
	 * from kprobe_running(), we have to be non-preemptible.
	 */
	अगर (!preemptible() &&
	    kprobe_running() &&
	    kprobe_fault_handler(regs, X86_TRAP_GP))
		जाओ निकास;

	ret = notअगरy_die(DIE_GPF, desc, regs, error_code, X86_TRAP_GP, संक_अंश);
	अगर (ret == NOTIFY_STOP)
		जाओ निकास;

	अगर (error_code)
		snम_लिखो(desc, माप(desc), "segment-related " GPFSTR);
	अन्यथा
		hपूर्णांक = get_kernel_gp_address(regs, &gp_addr);

	अगर (hपूर्णांक != GP_NO_HINT)
		snम_लिखो(desc, माप(desc), GPFSTR ", %s 0x%lx",
			 (hपूर्णांक == GP_NON_CANONICAL) ? "probably for non-canonical address"
						    : "maybe for address",
			 gp_addr);

	/*
	 * KASAN is पूर्णांकerested only in the non-canonical हाल, clear it
	 * otherwise.
	 */
	अगर (hपूर्णांक != GP_NON_CANONICAL)
		gp_addr = 0;

	die_addr(desc, regs, error_code, gp_addr);

निकास:
	cond_local_irq_disable(regs);
पूर्ण

अटल bool करो_पूर्णांक3(काष्ठा pt_regs *regs)
अणु
	पूर्णांक res;

#अगर_घोषित CONFIG_KGDB_LOW_LEVEL_TRAP
	अगर (kgdb_ll_trap(DIE_INT3, "int3", regs, 0, X86_TRAP_BP,
			 SIGTRAP) == NOTIFY_STOP)
		वापस true;
#पूर्ण_अगर /* CONFIG_KGDB_LOW_LEVEL_TRAP */

#अगर_घोषित CONFIG_KPROBES
	अगर (kprobe_पूर्णांक3_handler(regs))
		वापस true;
#पूर्ण_अगर
	res = notअगरy_die(DIE_INT3, "int3", regs, 0, X86_TRAP_BP, SIGTRAP);

	वापस res == NOTIFY_STOP;
पूर्ण

अटल व्योम करो_पूर्णांक3_user(काष्ठा pt_regs *regs)
अणु
	अगर (करो_पूर्णांक3(regs))
		वापस;

	cond_local_irq_enable(regs);
	करो_trap(X86_TRAP_BP, SIGTRAP, "int3", regs, 0, 0, शून्य);
	cond_local_irq_disable(regs);
पूर्ण

DEFINE_IDTENTRY_RAW(exc_पूर्णांक3)
अणु
	/*
	 * poke_पूर्णांक3_handler() is completely self contained code; it करोes (and
	 * must) *NOT* call out to anything, lest it hits upon yet another
	 * INT3.
	 */
	अगर (poke_पूर्णांक3_handler(regs))
		वापस;

	/*
	 * irqentry_enter_from_user_mode() uses अटल_branch_अणु,unपूर्णlikely()
	 * and thereक्रमe can trigger INT3, hence poke_पूर्णांक3_handler() must
	 * be करोne beक्रमe. If the entry came from kernel mode, then use
	 * nmi_enter() because the INT3 could have been hit in any context
	 * including NMI.
	 */
	अगर (user_mode(regs)) अणु
		irqentry_enter_from_user_mode(regs);
		instrumentation_begin();
		करो_पूर्णांक3_user(regs);
		instrumentation_end();
		irqentry_निकास_to_user_mode(regs);
	पूर्ण अन्यथा अणु
		irqentry_state_t irq_state = irqentry_nmi_enter(regs);

		instrumentation_begin();
		अगर (!करो_पूर्णांक3(regs))
			die("int3", regs, 0);
		instrumentation_end();
		irqentry_nmi_निकास(regs, irq_state);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_64
/*
 * Help handler running on a per-cpu (IST or entry trampoline) stack
 * to चयन to the normal thपढ़ो stack अगर the पूर्णांकerrupted code was in
 * user mode. The actual stack चयन is करोne in entry_64.S
 */
यंत्रlinkage __visible noinstr काष्ठा pt_regs *sync_regs(काष्ठा pt_regs *eregs)
अणु
	काष्ठा pt_regs *regs = (काष्ठा pt_regs *)this_cpu_पढ़ो(cpu_current_top_of_stack) - 1;
	अगर (regs != eregs)
		*regs = *eregs;
	वापस regs;
पूर्ण

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
यंत्रlinkage __visible noinstr काष्ठा pt_regs *vc_चयन_off_ist(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ sp, *stack;
	काष्ठा stack_info info;
	काष्ठा pt_regs *regs_ret;

	/*
	 * In the SYSCALL entry path the RSP value comes from user-space - करोn't
	 * trust it and चयन to the current kernel stack
	 */
	अगर (ip_within_syscall_gap(regs)) अणु
		sp = this_cpu_पढ़ो(cpu_current_top_of_stack);
		जाओ sync;
	पूर्ण

	/*
	 * From here on the RSP value is trusted. Now check whether entry
	 * happened from a safe stack. Not safe are the entry or unknown stacks,
	 * use the fall-back stack instead in this हाल.
	 */
	sp    = regs->sp;
	stack = (अचिन्हित दीर्घ *)sp;

	अगर (!get_stack_info_noinstr(stack, current, &info) || info.type == STACK_TYPE_ENTRY ||
	    info.type >= STACK_TYPE_EXCEPTION_LAST)
		sp = __this_cpu_ist_top_va(VC2);

sync:
	/*
	 * Found a safe stack - चयन to it as अगर the entry didn't happen via
	 * IST stack. The code below only copies pt_regs, the real चयन happens
	 * in assembly code.
	 */
	sp = ALIGN_DOWN(sp, 8) - माप(*regs_ret);

	regs_ret = (काष्ठा pt_regs *)sp;
	*regs_ret = *regs;

	वापस regs_ret;
पूर्ण
#पूर्ण_अगर

काष्ठा bad_iret_stack अणु
	व्योम *error_entry_ret;
	काष्ठा pt_regs regs;
पूर्ण;

यंत्रlinkage __visible noinstr
काष्ठा bad_iret_stack *fixup_bad_iret(काष्ठा bad_iret_stack *s)
अणु
	/*
	 * This is called from entry_64.S early in handling a fault
	 * caused by a bad iret to user mode.  To handle the fault
	 * correctly, we want to move our stack frame to where it would
	 * be had we entered directly on the entry stack (rather than
	 * just below the IRET frame) and we want to pretend that the
	 * exception came from the IRET target.
	 */
	काष्ठा bad_iret_stack पंचांगp, *new_stack =
		(काष्ठा bad_iret_stack *)__this_cpu_पढ़ो(cpu_tss_rw.x86_tss.sp0) - 1;

	/* Copy the IRET target to the temporary storage. */
	__स_नकल(&पंचांगp.regs.ip, (व्योम *)s->regs.sp, 5*8);

	/* Copy the reमुख्यder of the stack from the current stack. */
	__स_नकल(&पंचांगp, s, दुरत्व(काष्ठा bad_iret_stack, regs.ip));

	/* Update the entry stack */
	__स_नकल(new_stack, &पंचांगp, माप(पंचांगp));

	BUG_ON(!user_mode(&new_stack->regs));
	वापस new_stack;
पूर्ण
#पूर्ण_अगर

अटल bool is_sysenter_singlestep(काष्ठा pt_regs *regs)
अणु
	/*
	 * We करोn't try for precision here.  If we're anywhere in the region of
	 * code that can be single-stepped in the SYSENTER entry path, then
	 * assume that this is a useless single-step trap due to SYSENTER
	 * being invoked with TF set.  (We करोn't know in advance exactly
	 * which inकाष्ठाions will be hit because BTF could plausibly
	 * be set.)
	 */
#अगर_घोषित CONFIG_X86_32
	वापस (regs->ip - (अचिन्हित दीर्घ)__begin_SYSENTER_singlestep_region) <
		(अचिन्हित दीर्घ)__end_SYSENTER_singlestep_region -
		(अचिन्हित दीर्घ)__begin_SYSENTER_singlestep_region;
#या_अगर defined(CONFIG_IA32_EMULATION)
	वापस (regs->ip - (अचिन्हित दीर्घ)entry_SYSENTER_compat) <
		(अचिन्हित दीर्घ)__end_entry_SYSENTER_compat -
		(अचिन्हित दीर्घ)entry_SYSENTER_compat;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल __always_अंतरभूत अचिन्हित दीर्घ debug_पढ़ो_clear_dr6(व्योम)
अणु
	अचिन्हित दीर्घ dr6;

	/*
	 * The Intel SDM says:
	 *
	 *   Certain debug exceptions may clear bits 0-3. The reमुख्यing
	 *   contents of the DR6 रेजिस्टर are never cleared by the
	 *   processor. To aव्योम confusion in identअगरying debug
	 *   exceptions, debug handlers should clear the रेजिस्टर beक्रमe
	 *   वापसing to the पूर्णांकerrupted task.
	 *
	 * Keep it simple: clear DR6 immediately.
	 */
	get_debugreg(dr6, 6);
	set_debugreg(DR6_RESERVED, 6);
	dr6 ^= DR6_RESERVED; /* Flip to positive polarity */

	वापस dr6;
पूर्ण

/*
 * Our handling of the processor debug रेजिस्टरs is non-trivial.
 * We करो not clear them on entry and निकास from the kernel. Thereक्रमe
 * it is possible to get a watchpoपूर्णांक trap here from inside the kernel.
 * However, the code in ./ptrace.c has ensured that the user can
 * only set watchpoपूर्णांकs on userspace addresses. Thereक्रमe the in-kernel
 * watchpoपूर्णांक trap can only occur in code which is पढ़ोing/writing
 * from user space. Such code must not hold kernel locks (since it
 * can equally take a page fault), thereक्रमe it is safe to call
 * क्रमce_sig_info even though that claims and releases locks.
 *
 * Code in ./संकेत.c ensures that the debug control रेजिस्टर
 * is restored beक्रमe we deliver any संकेत, and thereक्रमe that
 * user code runs with the correct debug control रेजिस्टर even though
 * we clear it here.
 *
 * Being careful here means that we करोn't have to be as careful in a
 * lot of more complicated places (task चयनing can be a bit lazy
 * about restoring all the debug state, and ptrace करोesn't have to
 * find every occurrence of the TF bit that could be saved away even
 * by user code)
 *
 * May run on IST stack.
 */

अटल bool notअगरy_debug(काष्ठा pt_regs *regs, अचिन्हित दीर्घ *dr6)
अणु
	/*
	 * Notअगरiers will clear bits in @dr6 to indicate the event has been
	 * consumed - hw_अवरोधpoपूर्णांक_handler(), single_stop_cont().
	 *
	 * Notअगरiers will set bits in @भव_dr6 to indicate the desire
	 * क्रम संकेतs - ptrace_triggered(), kgdb_hw_overflow_handler().
	 */
	अगर (notअगरy_die(DIE_DEBUG, "debug", regs, (दीर्घ)dr6, 0, SIGTRAP) == NOTIFY_STOP)
		वापस true;

	वापस false;
पूर्ण

अटल __always_अंतरभूत व्योम exc_debug_kernel(काष्ठा pt_regs *regs,
					     अचिन्हित दीर्घ dr6)
अणु
	/*
	 * Disable अवरोधpoपूर्णांकs during exception handling; recursive exceptions
	 * are exceedingly 'fun'.
	 *
	 * Since this function is NOKPROBE, and that also applies to
	 * HW_BREAKPOINT_X, we can't hit a अवरोधpoपूर्णांक beक्रमe this (XXX except a
	 * HW_BREAKPOINT_W on our stack)
	 *
	 * Entry text is excluded क्रम HW_BP_X and cpu_entry_area, which
	 * includes the entry stack is excluded क्रम everything.
	 */
	अचिन्हित दीर्घ dr7 = local_db_save();
	irqentry_state_t irq_state = irqentry_nmi_enter(regs);
	instrumentation_begin();

	/*
	 * If something माला_लो miswired and we end up here क्रम a user mode
	 * #DB, we will malfunction.
	 */
	WARN_ON_ONCE(user_mode(regs));

	अगर (test_thपढ़ो_flag(TIF_BLOCKSTEP)) अणु
		/*
		 * The SDM says "The processor clears the BTF flag when it
		 * generates a debug exception." but PTRACE_BLOCKSTEP requested
		 * it क्रम userspace, but we just took a kernel #DB, so re-set
		 * BTF.
		 */
		अचिन्हित दीर्घ debugctl;

		rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
		debugctl |= DEBUGCTLMSR_BTF;
		wrmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
	पूर्ण

	/*
	 * Catch SYSENTER with TF set and clear DR_STEP. If this hit a
	 * watchpoपूर्णांक at the same समय then that will still be handled.
	 */
	अगर ((dr6 & DR_STEP) && is_sysenter_singlestep(regs))
		dr6 &= ~DR_STEP;

	/*
	 * The kernel करोesn't use INT1
	 */
	अगर (!dr6)
		जाओ out;

	अगर (notअगरy_debug(regs, &dr6))
		जाओ out;

	/*
	 * The kernel करोesn't use TF single-step outside of:
	 *
	 *  - Kprobes, consumed through kprobe_debug_handler()
	 *  - KGDB, consumed through notअगरy_debug()
	 *
	 * So अगर we get here with DR_STEP set, something is wonky.
	 *
	 * A known way to trigger this is through QEMU's GDB stub,
	 * which leaks #DB पूर्णांकo the guest and causes IST recursion.
	 */
	अगर (WARN_ON_ONCE(dr6 & DR_STEP))
		regs->flags &= ~X86_EFLAGS_TF;
out:
	instrumentation_end();
	irqentry_nmi_निकास(regs, irq_state);

	local_db_restore(dr7);
पूर्ण

अटल __always_अंतरभूत व्योम exc_debug_user(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ dr6)
अणु
	bool icebp;

	/*
	 * If something माला_लो miswired and we end up here क्रम a kernel mode
	 * #DB, we will malfunction.
	 */
	WARN_ON_ONCE(!user_mode(regs));

	/*
	 * NB: We can't easily clear DR7 here because
	 * irqentry_निकास_to_usermode() can invoke ptrace, schedule, access
	 * user memory, etc.  This means that a recursive #DB is possible.  If
	 * this happens, that #DB will hit exc_debug_kernel() and clear DR7.
	 * Since we're not on the IST stack right now, everything will be
	 * fine.
	 */

	irqentry_enter_from_user_mode(regs);
	instrumentation_begin();

	/*
	 * Start the भव/ptrace DR6 value with just the DR_STEP mask
	 * of the real DR6. ptrace_triggered() will set the DR_TRAPn bits.
	 *
	 * Userspace expects DR_STEP to be visible in ptrace_get_debugreg(6)
	 * even अगर it is not the result of PTRACE_SINGLESTEP.
	 */
	current->thपढ़ो.भव_dr6 = (dr6 & DR_STEP);

	/*
	 * The SDM says "The processor clears the BTF flag when it
	 * generates a debug exception."  Clear TIF_BLOCKSTEP to keep
	 * TIF_BLOCKSTEP in sync with the hardware BTF flag.
	 */
	clear_thपढ़ो_flag(TIF_BLOCKSTEP);

	/*
	 * If dr6 has no reason to give us about the origin of this trap,
	 * then it's very likely the result of an icebp/पूर्णांक01 trap.
	 * User wants a sigtrap क्रम that.
	 */
	icebp = !dr6;

	अगर (notअगरy_debug(regs, &dr6))
		जाओ out;

	/* It's safe to allow irq's after DR6 has been saved */
	local_irq_enable();

	अगर (v8086_mode(regs)) अणु
		handle_vm86_trap((काष्ठा kernel_vm86_regs *)regs, 0, X86_TRAP_DB);
		जाओ out_irq;
	पूर्ण

	/* #DB क्रम bus lock can only be triggered from userspace. */
	अगर (dr6 & DR_BUS_LOCK)
		handle_bus_lock(regs);

	/* Add the भव_dr6 bits क्रम संकेतs. */
	dr6 |= current->thपढ़ो.भव_dr6;
	अगर (dr6 & (DR_STEP | DR_TRAP_BITS) || icebp)
		send_sigtrap(regs, 0, get_si_code(dr6));

out_irq:
	local_irq_disable();
out:
	instrumentation_end();
	irqentry_निकास_to_user_mode(regs);
पूर्ण

#अगर_घोषित CONFIG_X86_64
/* IST stack entry */
DEFINE_IDTENTRY_DEBUG(exc_debug)
अणु
	exc_debug_kernel(regs, debug_पढ़ो_clear_dr6());
पूर्ण

/* User entry, runs on regular task stack */
DEFINE_IDTENTRY_DEBUG_USER(exc_debug)
अणु
	exc_debug_user(regs, debug_पढ़ो_clear_dr6());
पूर्ण
#अन्यथा
/* 32 bit करोes not have separate entry poपूर्णांकs. */
DEFINE_IDTENTRY_RAW(exc_debug)
अणु
	अचिन्हित दीर्घ dr6 = debug_पढ़ो_clear_dr6();

	अगर (user_mode(regs))
		exc_debug_user(regs, dr6);
	अन्यथा
		exc_debug_kernel(regs, dr6);
पूर्ण
#पूर्ण_अगर

/*
 * Note that we play around with the 'TS' bit in an attempt to get
 * the correct behaviour even in the presence of the asynchronous
 * IRQ13 behaviour
 */
अटल व्योम math_error(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	काष्ठा task_काष्ठा *task = current;
	काष्ठा fpu *fpu = &task->thपढ़ो.fpu;
	पूर्णांक si_code;
	अक्षर *str = (trapnr == X86_TRAP_MF) ? "fpu exception" :
						"simd exception";

	cond_local_irq_enable(regs);

	अगर (!user_mode(regs)) अणु
		अगर (fixup_exception(regs, trapnr, 0, 0))
			जाओ निकास;

		task->thपढ़ो.error_code = 0;
		task->thपढ़ो.trap_nr = trapnr;

		अगर (notअगरy_die(DIE_TRAP, str, regs, 0, trapnr,
			       संक_भ_त्रुटि) != NOTIFY_STOP)
			die(str, regs, 0);
		जाओ निकास;
	पूर्ण

	/*
	 * Save the info क्रम the exception handler and clear the error.
	 */
	fpu__save(fpu);

	task->thपढ़ो.trap_nr	= trapnr;
	task->thपढ़ो.error_code = 0;

	si_code = fpu__exception_code(fpu, trapnr);
	/* Retry when we get spurious exceptions: */
	अगर (!si_code)
		जाओ निकास;

	अगर (fixup_vdso_exception(regs, trapnr, 0, 0))
		जाओ निकास;

	क्रमce_sig_fault(संक_भ_त्रुटि, si_code,
			(व्योम __user *)uprobe_get_trap_addr(regs));
निकास:
	cond_local_irq_disable(regs);
पूर्ण

DEFINE_IDTENTRY(exc_coprocessor_error)
अणु
	math_error(regs, X86_TRAP_MF);
पूर्ण

DEFINE_IDTENTRY(exc_simd_coprocessor_error)
अणु
	अगर (IS_ENABLED(CONFIG_X86_INVD_BUG)) अणु
		/* AMD 486 bug: INVD in CPL 0 उठाओs #XF instead of #GP */
		अगर (!अटल_cpu_has(X86_FEATURE_XMM)) अणु
			__exc_general_protection(regs, 0);
			वापस;
		पूर्ण
	पूर्ण
	math_error(regs, X86_TRAP_XF);
पूर्ण

DEFINE_IDTENTRY(exc_spurious_पूर्णांकerrupt_bug)
अणु
	/*
	 * This addresses a Pentium Pro Erratum:
	 *
	 * PROBLEM: If the APIC subप्रणाली is configured in mixed mode with
	 * Virtual Wire mode implemented through the local APIC, an
	 * पूर्णांकerrupt vector of 0Fh (Intel reserved encoding) may be
	 * generated by the local APIC (Int 15).  This vector may be
	 * generated upon receipt of a spurious पूर्णांकerrupt (an पूर्णांकerrupt
	 * which is हटाओd beक्रमe the प्रणाली receives the INTA sequence)
	 * instead of the programmed 8259 spurious पूर्णांकerrupt vector.
	 *
	 * IMPLICATION: The spurious पूर्णांकerrupt vector programmed in the
	 * 8259 is normally handled by an operating प्रणाली's spurious
	 * पूर्णांकerrupt handler. However, a vector of 0Fh is unknown to some
	 * operating प्रणालीs, which would crash अगर this erratum occurred.
	 *
	 * In theory this could be limited to 32bit, but the handler is not
	 * hurting and who knows which other CPUs suffer from this.
	 */
पूर्ण

DEFINE_IDTENTRY(exc_device_not_available)
अणु
	अचिन्हित दीर्घ cr0 = पढ़ो_cr0();

#अगर_घोषित CONFIG_MATH_EMULATION
	अगर (!boot_cpu_has(X86_FEATURE_FPU) && (cr0 & X86_CR0_EM)) अणु
		काष्ठा math_emu_info info = अणु पूर्ण;

		cond_local_irq_enable(regs);

		info.regs = regs;
		math_emulate(&info);

		cond_local_irq_disable(regs);
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* This should not happen. */
	अगर (WARN(cr0 & X86_CR0_TS, "CR0.TS was set")) अणु
		/* Try to fix it up and carry on. */
		ग_लिखो_cr0(cr0 & ~X86_CR0_TS);
	पूर्ण अन्यथा अणु
		/*
		 * Something terrible happened, and we're better off trying
		 * to समाप्त the task than getting stuck in a never-ending
		 * loop of #NM faults.
		 */
		die("unexpected #NM exception", regs, 0);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_32
DEFINE_IDTENTRY_SW(iret_error)
अणु
	local_irq_enable();
	अगर (notअगरy_die(DIE_TRAP, "iret exception", regs, 0,
			X86_TRAP_IRET, संक_अवैध) != NOTIFY_STOP) अणु
		करो_trap(X86_TRAP_IRET, संक_अवैध, "iret exception", regs, 0,
			ILL_BADSTK, (व्योम __user *)शून्य);
	पूर्ण
	local_irq_disable();
पूर्ण
#पूर्ण_अगर

व्योम __init trap_init(व्योम)
अणु
	/* Init cpu_entry_area beक्रमe IST entries are set up */
	setup_cpu_entry_areas();

	/* Init GHCB memory pages when running as an SEV-ES guest */
	sev_es_init_vc_handling();

	idt_setup_traps();

	/*
	 * Should be a barrier क्रम any बाह्यal CPU state:
	 */
	cpu_init();

	idt_setup_ist_traps();
पूर्ण
