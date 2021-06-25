<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/tracehook.h>

#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/vdso.h>

#समावेश <abi/regdef.h>

#अगर_घोषित CONFIG_CPU_HAS_FPU
#समावेश <abi/fpu.h>
अटल पूर्णांक restore_fpu_state(काष्ठा sigcontext __user *sc)
अणु
	पूर्णांक err = 0;
	काष्ठा user_fp user_fp;

	err = __copy_from_user(&user_fp, &sc->sc_user_fp, माप(user_fp));

	restore_from_user_fp(&user_fp);

	वापस err;
पूर्ण

अटल पूर्णांक save_fpu_state(काष्ठा sigcontext __user *sc)
अणु
	काष्ठा user_fp user_fp;

	save_to_user_fp(&user_fp);

	वापस __copy_to_user(&sc->sc_user_fp, &user_fp, माप(user_fp));
पूर्ण
#अन्यथा
#घोषणा restore_fpu_state(sigcontext)	(0)
#घोषणा save_fpu_state(sigcontext)	(0)
#पूर्ण_अगर

काष्ठा rt_sigframe अणु
	/*
	 * pad[3] is compatible with the same काष्ठा defined in
	 * gcc/libgcc/config/csky/linux-unwind.h
	 */
	पूर्णांक pad[3];
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
पूर्ण;

अटल दीर्घ restore_sigcontext(काष्ठा pt_regs *regs,
	काष्ठा sigcontext __user *sc)
अणु
	पूर्णांक err = 0;

	/* sc_pt_regs is काष्ठाured the same as the start of pt_regs */
	err |= __copy_from_user(regs, &sc->sc_pt_regs, माप(काष्ठा pt_regs));

	/* Restore the भग्नing-poपूर्णांक state. */
	err |= restore_fpu_state(sc);

	वापस err;
पूर्ण

SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe __user *frame;
	sigset_t set;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	frame = (काष्ठा rt_sigframe __user *)regs->usp;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;

	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, &frame->uc.uc_mcontext))
		जाओ badframe;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस regs->a0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_sigcontext(काष्ठा rt_sigframe __user *frame,
	काष्ठा pt_regs *regs)
अणु
	काष्ठा sigcontext __user *sc = &frame->uc.uc_mcontext;
	पूर्णांक err = 0;

	err |= __copy_to_user(&sc->sc_pt_regs, regs, माप(काष्ठा pt_regs));
	err |= save_fpu_state(sc);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig,
	काष्ठा pt_regs *regs, माप_प्रकार framesize)
अणु
	अचिन्हित दीर्घ sp;
	/* Default to using normal stack */
	sp = regs->usp;

	/*
	 * If we are on the alternate संकेत stack and would overflow it, करोn't.
	 * Return an always-bogus address instead so we will die with संक_अंश.
	 */
	अगर (on_sig_stack(sp) && !likely(on_sig_stack(sp - framesize)))
		वापस (व्योम __user __क्रमce *)(-1UL);

	/* This is the X/Open sanctioned संकेत stack चयनing. */
	sp = sigsp(sp, ksig) - framesize;

	/* Align the stack frame. */
	sp &= -8UL;

	वापस (व्योम __user *)sp;
पूर्ण

अटल पूर्णांक
setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe *frame;
	पूर्णांक err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));
	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext. */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(शून्य, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->usp);
	err |= setup_sigcontext(frame, regs);
	err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));
	अगर (err)
		वापस -EFAULT;

	/* Set up to वापस from userspace. */
	regs->lr = (अचिन्हित दीर्घ)VDSO_SYMBOL(
		current->mm->context.vdso, rt_sigवापस);

	/*
	 * Set up रेजिस्टरs क्रम संकेत handler.
	 * Registers that we करोn't modअगरy keep the value they had from
	 * user-space at the समय we took the संकेत.
	 * We always pass siginfo and mcontext, regardless of SA_SIGINFO,
	 * since some things rely on this (e.g. glibc's debug/segfault.c).
	 */
	regs->pc  = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;
	regs->usp = (अचिन्हित दीर्घ)frame;
	regs->a0  = ksig->sig;				/* a0: संकेत number */
	regs->a1  = (अचिन्हित दीर्घ)(&(frame->info));	/* a1: siginfo poपूर्णांकer */
	regs->a2  = (अचिन्हित दीर्घ)(&(frame->uc));	/* a2: ucontext poपूर्णांकer */

	वापस 0;
पूर्ण

अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक ret;

	rseq_संकेत_deliver(ksig, regs);

	/* Are we from a प्रणाली call? */
	अगर (in_syscall(regs)) अणु
		/* Aव्योम additional syscall restarting via ret_from_exception */
		क्रमget_syscall(regs);

		/* If so, check प्रणाली call restarting.. */
		चयन (regs->a0) अणु
		हाल -ERESTART_RESTARTBLOCK:
		हाल -ERESTARTNOHAND:
			regs->a0 = -EINTR;
			अवरोध;

		हाल -ERESTARTSYS:
			अगर (!(ksig->ka.sa.sa_flags & SA_RESTART)) अणु
				regs->a0 = -EINTR;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल -ERESTARTNOINTR:
			regs->a0 = regs->orig_a0;
			regs->pc -= TRAP0_SIZE;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Set up the stack frame */
	ret = setup_rt_frame(ksig, oldset, regs);

	संकेत_setup_करोne(ret, ksig, 0);
पूर्ण

अटल व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	काष्ठा kसंकेत ksig;

	अगर (get_संकेत(&ksig)) अणु
		/* Actually deliver the संकेत */
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	/* Did we come from a प्रणाली call? */
	अगर (in_syscall(regs)) अणु
		/* Aव्योम additional syscall restarting via ret_from_exception */
		क्रमget_syscall(regs);

		/* Restart the प्रणाली call - no handlers present */
		चयन (regs->a0) अणु
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			regs->a0 = regs->orig_a0;
			regs->pc -= TRAP0_SIZE;
			अवरोध;
		हाल -ERESTART_RESTARTBLOCK:
			regs->a0 = regs->orig_a0;
			regs_syscallid(regs) = __NR_restart_syscall;
			regs->pc -= TRAP0_SIZE;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If there is no संकेत to deliver, we just put the saved
	 * sigmask back.
	 */
	restore_saved_sigmask();
पूर्ण

/*
 * notअगरication of userspace execution resumption
 * - triggered by the _TIF_WORK_MASK flags
 */
यंत्रlinkage व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs,
	अचिन्हित दीर्घ thपढ़ो_info_flags)
अणु
	अगर (thपढ़ो_info_flags & _TIF_UPROBE)
		uprobe_notअगरy_resume(regs);

	/* Handle pending संकेत delivery */
	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs);

	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME) अणु
		tracehook_notअगरy_resume(regs);
		rseq_handle_notअगरy_resume(शून्य, regs);
	पूर्ण
पूर्ण
