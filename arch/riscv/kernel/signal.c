<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Sunplus Core Technology Co., Ltd.
 *  Chen Liqin <liqin.chen@sunplusct.com>
 *  Lennox Wu <lennox.wu@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/linkage.h>

#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/csr.h>

बाह्य u32 __user_rt_sigवापस[2];

#घोषणा DEBUG_SIG 0

काष्ठा rt_sigframe अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
#अगर_अघोषित CONFIG_MMU
	u32 sigवापस_code[2];
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_FPU
अटल दीर्घ restore_fp_state(काष्ठा pt_regs *regs,
			     जोड़ __riscv_fp_state __user *sc_fpregs)
अणु
	दीर्घ err;
	काष्ठा __riscv_d_ext_state __user *state = &sc_fpregs->d;
	माप_प्रकार i;

	err = __copy_from_user(&current->thपढ़ो.ख_स्थितिe, state, माप(*state));
	अगर (unlikely(err))
		वापस err;

	ख_स्थितिe_restore(current, regs);

	/* We support no other extension state at this समय. */
	क्रम (i = 0; i < ARRAY_SIZE(sc_fpregs->q.reserved); i++) अणु
		u32 value;

		err = __get_user(value, &sc_fpregs->q.reserved[i]);
		अगर (unlikely(err))
			अवरोध;
		अगर (value != 0)
			वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल दीर्घ save_fp_state(काष्ठा pt_regs *regs,
			  जोड़ __riscv_fp_state __user *sc_fpregs)
अणु
	दीर्घ err;
	काष्ठा __riscv_d_ext_state __user *state = &sc_fpregs->d;
	माप_प्रकार i;

	ख_स्थितिe_save(current, regs);
	err = __copy_to_user(state, &current->thपढ़ो.ख_स्थितिe, माप(*state));
	अगर (unlikely(err))
		वापस err;

	/* We support no other extension state at this समय. */
	क्रम (i = 0; i < ARRAY_SIZE(sc_fpregs->q.reserved); i++) अणु
		err = __put_user(0, &sc_fpregs->q.reserved[i]);
		अगर (unlikely(err))
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण
#अन्यथा
#घोषणा save_fp_state(task, regs) (0)
#घोषणा restore_fp_state(task, regs) (0)
#पूर्ण_अगर

अटल दीर्घ restore_sigcontext(काष्ठा pt_regs *regs,
	काष्ठा sigcontext __user *sc)
अणु
	दीर्घ err;
	/* sc_regs is काष्ठाured the same as the start of pt_regs */
	err = __copy_from_user(regs, &sc->sc_regs, माप(sc->sc_regs));
	/* Restore the भग्नing-poपूर्णांक state. */
	अगर (has_fpu)
		err |= restore_fp_state(regs, &sc->sc_fpregs);
	वापस err;
पूर्ण

SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe __user *frame;
	काष्ठा task_काष्ठा *task;
	sigset_t set;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	frame = (काष्ठा rt_sigframe __user *)regs->sp;

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
	task = current;
	अगर (show_unhandled_संकेतs) अणु
		pr_info_ratelimited(
			"%s[%d]: bad frame in %s: frame=%p pc=%p sp=%p\n",
			task->comm, task_pid_nr(task), __func__,
			frame, (व्योम *)regs->epc, (व्योम *)regs->sp);
	पूर्ण
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

अटल दीर्घ setup_sigcontext(काष्ठा rt_sigframe __user *frame,
	काष्ठा pt_regs *regs)
अणु
	काष्ठा sigcontext __user *sc = &frame->uc.uc_mcontext;
	दीर्घ err;
	/* sc_regs is काष्ठाured the same as the start of pt_regs */
	err = __copy_to_user(&sc->sc_regs, regs, माप(sc->sc_regs));
	/* Save the भग्नing-poपूर्णांक state. */
	अगर (has_fpu)
		err |= save_fp_state(regs, &sc->sc_fpregs);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig,
	काष्ठा pt_regs *regs, माप_प्रकार framesize)
अणु
	अचिन्हित दीर्घ sp;
	/* Default to using normal stack */
	sp = regs->sp;

	/*
	 * If we are on the alternate संकेत stack and would overflow it, करोn't.
	 * Return an always-bogus address instead so we will die with संक_अंश.
	 */
	अगर (on_sig_stack(sp) && !likely(on_sig_stack(sp - framesize)))
		वापस (व्योम __user __क्रमce *)(-1UL);

	/* This is the X/Open sanctioned संकेत stack चयनing. */
	sp = sigsp(sp, ksig) - framesize;

	/* Align the stack frame. */
	sp &= ~0xfUL;

	वापस (व्योम __user *)sp;
पूर्ण

अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
	काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;
	दीर्घ err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));
	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext. */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(शून्य, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->sp);
	err |= setup_sigcontext(frame, regs);
	err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));
	अगर (err)
		वापस -EFAULT;

	/* Set up to वापस from userspace. */
#अगर_घोषित CONFIG_MMU
	regs->ra = (अचिन्हित दीर्घ)VDSO_SYMBOL(
		current->mm->context.vdso, rt_sigवापस);
#अन्यथा
	/*
	 * For the nommu हाल we करोn't have a VDSO.  Instead we push two
	 * inकाष्ठाions to call the rt_sigवापस syscall onto the user stack.
	 */
	अगर (copy_to_user(&frame->sigवापस_code, __user_rt_sigवापस,
			 माप(frame->sigवापस_code)))
		वापस -EFAULT;
	regs->ra = (अचिन्हित दीर्घ)&frame->sigवापस_code;
#पूर्ण_अगर /* CONFIG_MMU */

	/*
	 * Set up रेजिस्टरs क्रम संकेत handler.
	 * Registers that we करोn't modअगरy keep the value they had from
	 * user-space at the समय we took the संकेत.
	 * We always pass siginfo and mcontext, regardless of SA_SIGINFO,
	 * since some things rely on this (e.g. glibc's debug/segfault.c).
	 */
	regs->epc = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;
	regs->sp = (अचिन्हित दीर्घ)frame;
	regs->a0 = ksig->sig;                     /* a0: संकेत number */
	regs->a1 = (अचिन्हित दीर्घ)(&frame->info); /* a1: siginfo poपूर्णांकer */
	regs->a2 = (अचिन्हित दीर्घ)(&frame->uc);   /* a2: ucontext poपूर्णांकer */

#अगर DEBUG_SIG
	pr_info("SIG deliver (%s:%d): sig=%d pc=%p ra=%p sp=%p\n",
		current->comm, task_pid_nr(current), ksig->sig,
		(व्योम *)regs->epc, (व्योम *)regs->ra, frame);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक ret;

	/* Are we from a प्रणाली call? */
	अगर (regs->cause == EXC_SYSCALL) अणु
		/* Aव्योम additional syscall restarting via ret_from_exception */
		regs->cause = -1UL;
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
			regs->epc -= 0x4;
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
	अगर (regs->cause == EXC_SYSCALL) अणु
		/* Aव्योम additional syscall restarting via ret_from_exception */
		regs->cause = -1UL;

		/* Restart the प्रणाली call - no handlers present */
		चयन (regs->a0) अणु
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
                        regs->a0 = regs->orig_a0;
			regs->epc -= 0x4;
			अवरोध;
		हाल -ERESTART_RESTARTBLOCK:
                        regs->a0 = regs->orig_a0;
			regs->a7 = __NR_restart_syscall;
			regs->epc -= 0x4;
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
यंत्रlinkage __visible व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs,
					   अचिन्हित दीर्घ thपढ़ो_info_flags)
अणु
	अगर (thपढ़ो_info_flags & _TIF_UPROBE)
		uprobe_notअगरy_resume(regs);

	/* Handle pending संकेत delivery */
	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs);

	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME)
		tracehook_notअगरy_resume(regs);
पूर्ण
