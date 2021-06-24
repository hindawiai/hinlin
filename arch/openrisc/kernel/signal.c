<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC संकेत.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tracehook.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <linux/uaccess.h>

#घोषणा DEBUG_SIG 0

काष्ठा rt_sigframe अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
	अचिन्हित अक्षर retcode[16];	/* trampoline code */
पूर्ण;

अटल पूर्णांक restore_sigcontext(काष्ठा pt_regs *regs,
			      काष्ठा sigcontext __user *sc)
अणु
	पूर्णांक err = 0;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/*
	 * Restore the regs from &sc->regs.
	 * (sc is alपढ़ोy checked since the sigframe was
	 *  checked in sys_sigवापस previously)
	 */
	err |= __copy_from_user(regs, sc->regs.gpr, 32 * माप(अचिन्हित दीर्घ));
	err |= __copy_from_user(&regs->pc, &sc->regs.pc, माप(अचिन्हित दीर्घ));
	err |= __copy_from_user(&regs->sr, &sc->regs.sr, माप(अचिन्हित दीर्घ));

	/* make sure the SM-bit is cleared so user-mode cannot fool us */
	regs->sr &= ~SPR_SR_SM;

	regs->orig_gpr11 = -1;	/* Aव्योम syscall restart checks */

	/* TODO: the other ports use regs->orig_XX to disable syscall checks
	 * after this completes, but we करोn't use that mechanism. maybe we can
	 * use it now ?
	 */

	वापस err;
पूर्ण

यंत्रlinkage दीर्घ _sys_rt_sigवापस(काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame = (काष्ठा rt_sigframe __user *)regs->sp;
	sigset_t set;

	/*
	 * Since we stacked the संकेत on a dword boundary,
	 * then frame should be dword aligned here.  If it's
	 * not, then the user is trying to mess with us.
	 */
	अगर (((अचिन्हित दीर्घ)frame) & 3)
		जाओ badframe;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, &frame->uc.uc_mcontext))
		जाओ badframe;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस regs->gpr[11];

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

/*
 * Set up a संकेत frame.
 */

अटल पूर्णांक setup_sigcontext(काष्ठा pt_regs *regs, काष्ठा sigcontext __user *sc)
अणु
	पूर्णांक err = 0;

	/* copy the regs */
	/* There should be no need to save callee-saved रेजिस्टरs here...
	 * ...but we save them anyway.  Revisit this
	 */
	err |= __copy_to_user(sc->regs.gpr, regs, 32 * माप(अचिन्हित दीर्घ));
	err |= __copy_to_user(&sc->regs.pc, &regs->pc, माप(अचिन्हित दीर्घ));
	err |= __copy_to_user(&sc->regs.sr, &regs->sr, माप(अचिन्हित दीर्घ));

	वापस err;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ align_sigframe(अचिन्हित दीर्घ sp)
अणु
	वापस sp & ~3UL;
पूर्ण

/*
 * Work out where the संकेत frame should go.  It's either on the user stack
 * or the alternate stack.
 */

अटल अंतरभूत व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig,
					काष्ठा pt_regs *regs, माप_प्रकार frame_size)
अणु
	अचिन्हित दीर्घ sp = regs->sp;

	/* redzone */
	sp -= STACK_FRAME_OVERHEAD;
	sp = sigsp(sp, ksig);
	sp = align_sigframe(sp - frame_size);

	वापस (व्योम __user *)sp;
पूर्ण

/* grab and setup a संकेत frame.
 *
 * basically we stack a lot of state info, and arrange क्रम the
 * user-mode program to वापस to the kernel using either a
 * trampoline which perक्रमms the syscall sigवापस, or a provided
 * user-mode trampoline.
 */
अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;
	अचिन्हित दीर्घ वापस_ip;
	पूर्णांक err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));

	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	/* Create siginfo.  */
	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext.  */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(शून्य, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->sp);
	err |= setup_sigcontext(regs, &frame->uc.uc_mcontext);

	err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));

	अगर (err)
		वापस -EFAULT;

	/* trampoline - the desired वापस ip is the retcode itself */
	वापस_ip = (अचिन्हित दीर्घ)&frame->retcode;
	/* This is:
		l.ori r11,r0,__NR_sigवापस
		l.sys 1
	 */
	err |= __put_user(0xa960,             (लघु __user *)(frame->retcode + 0));
	err |= __put_user(__NR_rt_sigवापस,  (लघु __user *)(frame->retcode + 2));
	err |= __put_user(0x20000001, (अचिन्हित दीर्घ __user *)(frame->retcode + 4));
	err |= __put_user(0x15000000, (अचिन्हित दीर्घ __user *)(frame->retcode + 8));

	अगर (err)
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->pc = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler; /* what we enter NOW */
	regs->gpr[9] = (अचिन्हित दीर्घ)वापस_ip;     /* what we enter LATER */
	regs->gpr[3] = (अचिन्हित दीर्घ)ksig->sig;           /* arg 1: signo */
	regs->gpr[4] = (अचिन्हित दीर्घ)&frame->info;  /* arg 2: (siginfo_t*) */
	regs->gpr[5] = (अचिन्हित दीर्घ)&frame->uc;    /* arg 3: ucontext */

	/* actually move the usp to reflect the stacked frame */
	regs->sp = (अचिन्हित दीर्घ)frame;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;

	ret = setup_rt_frame(ksig, sigmask_to_save(), regs);

	संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLESTEP));
पूर्ण

/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 *
 * Also note that the regs काष्ठाure given here as an argument, is the latest
 * pushed pt_regs. It may or may not be the same as the first pushed रेजिस्टरs
 * when the initial usermode->kernelmode transition took place. Thereक्रमe
 * we can use user_mode(regs) to see अगर we came directly from kernel or user
 * mode below.
 */

पूर्णांक करो_संकेत(काष्ठा pt_regs *regs, पूर्णांक syscall)
अणु
	काष्ठा kसंकेत ksig;
	अचिन्हित दीर्घ जारी_addr = 0;
	अचिन्हित दीर्घ restart_addr = 0;
	अचिन्हित दीर्घ retval = 0;
	पूर्णांक restart = 0;

	अगर (syscall) अणु
		जारी_addr = regs->pc;
		restart_addr = जारी_addr - 4;
		retval = regs->gpr[11];

		/*
		 * Setup syscall restart here so that a debugger will
		 * see the alपढ़ोy changed PC.
		 */
		चयन (retval) अणु
		हाल -ERESTART_RESTARTBLOCK:
			restart = -2;
			fallthrough;
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			restart++;
			regs->gpr[11] = regs->orig_gpr11;
			regs->pc = restart_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Get the संकेत to deliver.  During the call to get_संकेत the
	 * debugger may change all our रेजिस्टरs so we may need to revert
	 * the decision to restart the syscall; specअगरically, अगर the PC is
	 * changed, करोn't restart the syscall.
	 */
	अगर (get_संकेत(&ksig)) अणु
		अगर (unlikely(restart) && regs->pc == restart_addr) अणु
			अगर (retval == -ERESTARTNOHAND ||
			    retval == -ERESTART_RESTARTBLOCK
			    || (retval == -ERESTARTSYS
			        && !(ksig.ka.sa.sa_flags & SA_RESTART))) अणु
				/* No स्वतःmatic restart */
				regs->gpr[11] = -EINTR;
				regs->pc = जारी_addr;
			पूर्ण
		पूर्ण
		handle_संकेत(&ksig, regs);
	पूर्ण अन्यथा अणु
		/* no handler */
		restore_saved_sigmask();
		/*
		 * Restore pt_regs PC as syscall restart will be handled by
		 * kernel without वापस to userspace
		 */
		अगर (unlikely(restart) && regs->pc == restart_addr) अणु
			regs->pc = जारी_addr;
			वापस restart;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक
करो_work_pending(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक thपढ़ो_flags, पूर्णांक syscall)
अणु
	करो अणु
		अगर (likely(thपढ़ो_flags & _TIF_NEED_RESCHED)) अणु
			schedule();
		पूर्ण अन्यथा अणु
			अगर (unlikely(!user_mode(regs)))
				वापस 0;
			local_irq_enable();
			अगर (thपढ़ो_flags & (_TIF_SIGPENDING|_TIF_NOTIFY_SIGNAL)) अणु
				पूर्णांक restart = करो_संकेत(regs, syscall);
				अगर (unlikely(restart)) अणु
					/*
					 * Restart without handlers.
					 * Deal with it without leaving
					 * the kernel space.
					 */
					वापस restart;
				पूर्ण
				syscall = 0;
			पूर्ण अन्यथा अणु
				tracehook_notअगरy_resume(regs);
			पूर्ण
		पूर्ण
		local_irq_disable();
		thपढ़ो_flags = current_thपढ़ो_info()->flags;
	पूर्ण जबतक (thपढ़ो_flags & _TIF_WORK_MASK);
	वापस 0;
पूर्ण
