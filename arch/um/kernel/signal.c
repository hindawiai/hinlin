<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/ftrace.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/unistd.h>
#समावेश <frame_kern.h>
#समावेश <kern_util.h>
#समावेश <os.h>

EXPORT_SYMBOL(block_संकेतs);
EXPORT_SYMBOL(unblock_संकेतs);

व्योम block_संकेतs_trace(व्योम)
अणु
	block_संकेतs();
	अगर (current_thपढ़ो_info())
		trace_hardirqs_off();
पूर्ण

व्योम unblock_संकेतs_trace(व्योम)
अणु
	अगर (current_thपढ़ो_info())
		trace_hardirqs_on();
	unblock_संकेतs();
पूर्ण

व्योम um_trace_संकेतs_on(व्योम)
अणु
	अगर (current_thपढ़ो_info())
		trace_hardirqs_on();
पूर्ण

व्योम um_trace_संकेतs_off(व्योम)
अणु
	अगर (current_thपढ़ो_info())
		trace_hardirqs_off();
पूर्ण

/*
 * OK, we're invoking a handler
 */
अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक singlestep = 0;
	अचिन्हित दीर्घ sp;
	पूर्णांक err;

	अगर ((current->ptrace & PT_DTRACE) && (current->ptrace & PT_PTRACED))
		singlestep = 1;

	/* Did we come from a प्रणाली call? */
	अगर (PT_REGS_SYSCALL_NR(regs) >= 0) अणु
		/* If so, check प्रणाली call restarting.. */
		चयन (PT_REGS_SYSCALL_RET(regs)) अणु
		हाल -ERESTART_RESTARTBLOCK:
		हाल -ERESTARTNOHAND:
			PT_REGS_SYSCALL_RET(regs) = -EINTR;
			अवरोध;

		हाल -ERESTARTSYS:
			अगर (!(ksig->ka.sa.sa_flags & SA_RESTART)) अणु
				PT_REGS_SYSCALL_RET(regs) = -EINTR;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल -ERESTARTNOINTR:
			PT_REGS_RESTART_SYSCALL(regs);
			PT_REGS_ORIG_SYSCALL(regs) = PT_REGS_SYSCALL_NR(regs);
			अवरोध;
		पूर्ण
	पूर्ण

	sp = PT_REGS_SP(regs);
	अगर ((ksig->ka.sa.sa_flags & SA_ONSTACK) && (sas_ss_flags(sp) == 0))
		sp = current->sas_ss_sp + current->sas_ss_size;

#अगर_घोषित CONFIG_ARCH_HAS_SC_SIGNALS
	अगर (!(ksig->ka.sa.sa_flags & SA_SIGINFO))
		err = setup_संकेत_stack_sc(sp, ksig, regs, oldset);
	अन्यथा
#पूर्ण_अगर
		err = setup_संकेत_stack_si(sp, ksig, regs, oldset);

	संकेत_setup_करोne(err, ksig, singlestep);
पूर्ण

व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	काष्ठा kसंकेत ksig;
	पूर्णांक handled_sig = 0;

	जबतक (get_संकेत(&ksig)) अणु
		handled_sig = 1;
		/* Whee!  Actually deliver the संकेत.  */
		handle_संकेत(&ksig, regs);
	पूर्ण

	/* Did we come from a प्रणाली call? */
	अगर (!handled_sig && (PT_REGS_SYSCALL_NR(regs) >= 0)) अणु
		/* Restart the प्रणाली call - no handlers present */
		चयन (PT_REGS_SYSCALL_RET(regs)) अणु
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			PT_REGS_ORIG_SYSCALL(regs) = PT_REGS_SYSCALL_NR(regs);
			PT_REGS_RESTART_SYSCALL(regs);
			अवरोध;
		हाल -ERESTART_RESTARTBLOCK:
			PT_REGS_ORIG_SYSCALL(regs) = __NR_restart_syscall;
			PT_REGS_RESTART_SYSCALL(regs);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * This बंदs a way to execute a प्रणाली call on the host.  If
	 * you set a अवरोधpoपूर्णांक on a प्रणाली call inकाष्ठाion and singlestep
	 * from it, the tracing thपढ़ो used to PTRACE_SINGLESTEP the process
	 * rather than PTRACE_SYSCALL it, allowing the प्रणाली call to execute
	 * on the host.  The tracing thपढ़ो will check this flag and
	 * PTRACE_SYSCALL अगर necessary.
	 */
	अगर (current->ptrace & PT_DTRACE)
		current->thपढ़ो.singlestep_syscall =
			is_syscall(PT_REGS_IP(&current->thपढ़ो.regs));

	/*
	 * अगर there's no संकेत to deliver, we just put the saved sigmask
	 * back
	 */
	अगर (!handled_sig)
		restore_saved_sigmask();
पूर्ण
