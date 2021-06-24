<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/sh/kernel/संकेत.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  1997-11-28  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 *
 *  SuperH version:  Copyright (C) 1999, 2000  Niibe Yutaka & Kaz Kojima
 *
 */
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tty.h>
#समावेश <linux/elf.h>
#समावेश <linux/personality.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/पन.स>
#समावेश <linux/tracehook.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/fpu.h>

काष्ठा fdpic_func_descriptor अणु
	अचिन्हित दीर्घ	text;
	अचिन्हित दीर्घ	GOT;
पूर्ण;

/*
 * The following define adds a 64 byte gap between the संकेत
 * stack frame and previous contents of the stack.  This allows
 * frame unwinding in a function epilogue but only अगर a frame
 * poपूर्णांकer is used in the function.  This is necessary because
 * current gcc compilers (<4.3) करो not generate unwind info on
 * SH क्रम function epilogues.
 */
#घोषणा UNWINDGUARD 64

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 */

#घोषणा MOVW(n)	 (0x9300|((n)-2))	/* Move mem word at PC+n to R3 */
#अगर defined(CONFIG_CPU_SH2)
#घोषणा TRAP_NOARG 0xc320		/* Syscall w/no args (NR in R3) */
#अन्यथा
#घोषणा TRAP_NOARG 0xc310		/* Syscall w/no args (NR in R3) */
#पूर्ण_अगर
#घोषणा OR_R0_R0 0x200b			/* or r0,r0 (insert to aव्योम hardware bug) */

काष्ठा sigframe
अणु
	काष्ठा sigcontext sc;
	अचिन्हित दीर्घ extramask[_NSIG_WORDS-1];
	u16 retcode[8];
पूर्ण;

काष्ठा rt_sigframe
अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
	u16 retcode[8];
पूर्ण;

#अगर_घोषित CONFIG_SH_FPU
अटल अंतरभूत पूर्णांक restore_sigcontext_fpu(काष्ठा sigcontext __user *sc)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	अगर (!(boot_cpu_data.flags & CPU_HAS_FPU))
		वापस 0;

	set_used_math();
	वापस __copy_from_user(&tsk->thपढ़ो.xstate->hardfpu, &sc->sc_fpregs[0],
				माप(दीर्घ)*(16*2+2));
पूर्ण

अटल अंतरभूत पूर्णांक save_sigcontext_fpu(काष्ठा sigcontext __user *sc,
				      काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	अगर (!(boot_cpu_data.flags & CPU_HAS_FPU))
		वापस 0;

	अगर (!used_math())
		वापस __put_user(0, &sc->sc_ownedfp);

	अगर (__put_user(1, &sc->sc_ownedfp))
		वापस -EFAULT;

	/* This will cause a "finit" to be triggered by the next
	   attempted FPU operation by the 'current' process.
	   */
	clear_used_math();

	unlazy_fpu(tsk, regs);
	वापस __copy_to_user(&sc->sc_fpregs[0], &tsk->thपढ़ो.xstate->hardfpu,
			      माप(दीर्घ)*(16*2+2));
पूर्ण
#पूर्ण_अगर /* CONFIG_SH_FPU */

अटल पूर्णांक
restore_sigcontext(काष्ठा pt_regs *regs, काष्ठा sigcontext __user *sc, पूर्णांक *r0_p)
अणु
	अचिन्हित पूर्णांक err = 0;

#घोषणा COPY(x)		err |= __get_user(regs->x, &sc->sc_##x)
			COPY(regs[1]);
	COPY(regs[2]);	COPY(regs[3]);
	COPY(regs[4]);	COPY(regs[5]);
	COPY(regs[6]);	COPY(regs[7]);
	COPY(regs[8]);	COPY(regs[9]);
	COPY(regs[10]);	COPY(regs[11]);
	COPY(regs[12]);	COPY(regs[13]);
	COPY(regs[14]);	COPY(regs[15]);
	COPY(gbr);	COPY(mach);
	COPY(macl);	COPY(pr);
	COPY(sr);	COPY(pc);
#अघोषित COPY

#अगर_घोषित CONFIG_SH_FPU
	अगर (boot_cpu_data.flags & CPU_HAS_FPU) अणु
		पूर्णांक owned_fp;
		काष्ठा task_काष्ठा *tsk = current;

		regs->sr |= SR_FD; /* Release FPU */
		clear_fpu(tsk, regs);
		clear_used_math();
		err |= __get_user (owned_fp, &sc->sc_ownedfp);
		अगर (owned_fp)
			err |= restore_sigcontext_fpu(sc);
	पूर्ण
#पूर्ण_अगर

	regs->tra = -1;		/* disable syscall checks */
	err |= __get_user(*r0_p, &sc->sc_regs[0]);
	वापस err;
पूर्ण

यंत्रlinkage पूर्णांक sys_sigवापस(व्योम)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा sigframe __user *frame = (काष्ठा sigframe __user *)regs->regs[15];
	sigset_t set;
	पूर्णांक r0;

        /* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;

	अगर (__get_user(set.sig[0], &frame->sc.oldmask)
	    || (_NSIG_WORDS > 1
		&& __copy_from_user(&set.sig[1], &frame->extramask,
				    माप(frame->extramask))))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, &frame->sc, &r0))
		जाओ badframe;
	वापस r0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक sys_rt_sigवापस(व्योम)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe __user *frame = (काष्ठा rt_sigframe __user *)regs->regs[15];
	sigset_t set;
	पूर्णांक r0;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;

	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, &frame->uc.uc_mcontext, &r0))
		जाओ badframe;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस r0;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

/*
 * Set up a संकेत frame.
 */

अटल पूर्णांक
setup_sigcontext(काष्ठा sigcontext __user *sc, काष्ठा pt_regs *regs,
		 अचिन्हित दीर्घ mask)
अणु
	पूर्णांक err = 0;

#घोषणा COPY(x)		err |= __put_user(regs->x, &sc->sc_##x)
	COPY(regs[0]);	COPY(regs[1]);
	COPY(regs[2]);	COPY(regs[3]);
	COPY(regs[4]);	COPY(regs[5]);
	COPY(regs[6]);	COPY(regs[7]);
	COPY(regs[8]);	COPY(regs[9]);
	COPY(regs[10]);	COPY(regs[11]);
	COPY(regs[12]);	COPY(regs[13]);
	COPY(regs[14]);	COPY(regs[15]);
	COPY(gbr);	COPY(mach);
	COPY(macl);	COPY(pr);
	COPY(sr);	COPY(pc);
#अघोषित COPY

#अगर_घोषित CONFIG_SH_FPU
	err |= save_sigcontext_fpu(sc, regs);
#पूर्ण_अगर

	/* non-iBCS2 extensions.. */
	err |= __put_user(mask, &sc->oldmask);

	वापस err;
पूर्ण

/*
 * Determine which stack to use..
 */
अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा k_sigaction *ka, अचिन्हित दीर्घ sp, माप_प्रकार frame_size)
अणु
	अगर (ka->sa.sa_flags & SA_ONSTACK) अणु
		अगर (sas_ss_flags(sp) == 0)
			sp = current->sas_ss_sp + current->sas_ss_size;
	पूर्ण

	वापस (व्योम __user *)((sp - (frame_size+UNWINDGUARD)) & -8ul);
पूर्ण

/* These symbols are defined with the addresses in the vsyscall page.
   See vsyscall-trapa.S.  */
बाह्य व्योम __kernel_sigवापस(व्योम);
बाह्य व्योम __kernel_rt_sigवापस(व्योम);

अटल पूर्णांक setup_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
		       काष्ठा pt_regs *regs)
अणु
	काष्ठा sigframe __user *frame;
	पूर्णांक err = 0, sig = ksig->sig;

	frame = get_sigframe(&ksig->ka, regs->regs[15], माप(*frame));

	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	err |= setup_sigcontext(&frame->sc, regs, set->sig[0]);

	अगर (_NSIG_WORDS > 1)
		err |= __copy_to_user(frame->extramask, &set->sig[1],
				      माप(frame->extramask));

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER) अणु
		regs->pr = (अचिन्हित दीर्घ) ksig->ka.sa.sa_restorer;
#अगर_घोषित CONFIG_VSYSCALL
	पूर्ण अन्यथा अगर (likely(current->mm->context.vdso)) अणु
		regs->pr = VDSO_SYM(&__kernel_sigवापस);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* Generate वापस code (प्रणाली call to sigवापस) */
		err |= __put_user(MOVW(7), &frame->retcode[0]);
		err |= __put_user(TRAP_NOARG, &frame->retcode[1]);
		err |= __put_user(OR_R0_R0, &frame->retcode[2]);
		err |= __put_user(OR_R0_R0, &frame->retcode[3]);
		err |= __put_user(OR_R0_R0, &frame->retcode[4]);
		err |= __put_user(OR_R0_R0, &frame->retcode[5]);
		err |= __put_user(OR_R0_R0, &frame->retcode[6]);
		err |= __put_user((__NR_sigवापस), &frame->retcode[7]);
		regs->pr = (अचिन्हित दीर्घ) frame->retcode;
		flush_icache_range(regs->pr, regs->pr + माप(frame->retcode));
	पूर्ण

	अगर (err)
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->regs[15] = (अचिन्हित दीर्घ) frame;
	regs->regs[4] = sig; /* Arg क्रम संकेत handler */
	regs->regs[5] = 0;
	regs->regs[6] = (अचिन्हित दीर्घ) &frame->sc;

	अगर (current->personality & FDPIC_FUNCPTRS) अणु
		काष्ठा fdpic_func_descriptor __user *funcptr =
			(काष्ठा fdpic_func_descriptor __user *)ksig->ka.sa.sa_handler;

		err |= __get_user(regs->pc, &funcptr->text);
		err |= __get_user(regs->regs[12], &funcptr->GOT);
	पूर्ण अन्यथा
		regs->pc = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;

	अगर (err)
		वापस -EFAULT;

	pr_debug("SIG deliver (%s:%d): sp=%p pc=%08lx pr=%08lx\n",
		 current->comm, task_pid_nr(current), frame, regs->pc, regs->pr);

	वापस 0;
पूर्ण

अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;
	पूर्णांक err = 0, sig = ksig->sig;

	frame = get_sigframe(&ksig->ka, regs->regs[15], माप(*frame));

	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext.  */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(शून्य, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->regs[15]);
	err |= setup_sigcontext(&frame->uc.uc_mcontext,
			        regs, set->sig[0]);
	err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER) अणु
		regs->pr = (अचिन्हित दीर्घ) ksig->ka.sa.sa_restorer;
#अगर_घोषित CONFIG_VSYSCALL
	पूर्ण अन्यथा अगर (likely(current->mm->context.vdso)) अणु
		regs->pr = VDSO_SYM(&__kernel_rt_sigवापस);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* Generate वापस code (प्रणाली call to rt_sigवापस) */
		err |= __put_user(MOVW(7), &frame->retcode[0]);
		err |= __put_user(TRAP_NOARG, &frame->retcode[1]);
		err |= __put_user(OR_R0_R0, &frame->retcode[2]);
		err |= __put_user(OR_R0_R0, &frame->retcode[3]);
		err |= __put_user(OR_R0_R0, &frame->retcode[4]);
		err |= __put_user(OR_R0_R0, &frame->retcode[5]);
		err |= __put_user(OR_R0_R0, &frame->retcode[6]);
		err |= __put_user((__NR_rt_sigवापस), &frame->retcode[7]);
		regs->pr = (अचिन्हित दीर्घ) frame->retcode;
		flush_icache_range(regs->pr, regs->pr + माप(frame->retcode));
	पूर्ण

	अगर (err)
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->regs[15] = (अचिन्हित दीर्घ) frame;
	regs->regs[4] = sig; /* Arg क्रम संकेत handler */
	regs->regs[5] = (अचिन्हित दीर्घ) &frame->info;
	regs->regs[6] = (अचिन्हित दीर्घ) &frame->uc;

	अगर (current->personality & FDPIC_FUNCPTRS) अणु
		काष्ठा fdpic_func_descriptor __user *funcptr =
			(काष्ठा fdpic_func_descriptor __user *)ksig->ka.sa.sa_handler;

		err |= __get_user(regs->pc, &funcptr->text);
		err |= __get_user(regs->regs[12], &funcptr->GOT);
	पूर्ण अन्यथा
		regs->pc = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;

	अगर (err)
		वापस -EFAULT;

	pr_debug("SIG deliver (%s:%d): sp=%p pc=%08lx pr=%08lx\n",
		 current->comm, task_pid_nr(current), frame, regs->pc, regs->pr);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
handle_syscall_restart(अचिन्हित दीर्घ save_r0, काष्ठा pt_regs *regs,
		       काष्ठा sigaction *sa)
अणु
	/* If we're not from a syscall, bail out */
	अगर (regs->tra < 0)
		वापस;

	/* check क्रम प्रणाली call restart.. */
	चयन (regs->regs[0]) अणु
		हाल -ERESTART_RESTARTBLOCK:
		हाल -ERESTARTNOHAND:
		no_प्रणाली_call_restart:
			regs->regs[0] = -EINTR;
			अवरोध;

		हाल -ERESTARTSYS:
			अगर (!(sa->sa_flags & SA_RESTART))
				जाओ no_प्रणाली_call_restart;
			fallthrough;
		हाल -ERESTARTNOINTR:
			regs->regs[0] = save_r0;
			regs->pc -= inकाष्ठाion_size(__raw_पढ़ोw(regs->pc - 4));
			अवरोध;
	पूर्ण
पूर्ण

/*
 * OK, we're invoking a handler
 */
अटल व्योम
handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs, अचिन्हित पूर्णांक save_r0)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक ret;

	/* Set up the stack frame */
	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		ret = setup_rt_frame(ksig, oldset, regs);
	अन्यथा
		ret = setup_frame(ksig, oldset, regs);

	संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLESTEP));
पूर्ण

/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 *
 * Note that we go through the संकेतs twice: once to check the संकेतs that
 * the kernel can handle, and then we build all the user-level संकेत handling
 * stack-frames in one go after that.
 */
अटल व्योम करो_संकेत(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक save_r0)
अणु
	काष्ठा kसंकेत ksig;

	/*
	 * We want the common हाल to go fast, which
	 * is why we may in certain हालs get here from
	 * kernel mode. Just वापस without करोing anything
	 * अगर so.
	 */
	अगर (!user_mode(regs))
		वापस;

	अगर (get_संकेत(&ksig)) अणु
		handle_syscall_restart(save_r0, regs, &ksig.ka.sa);

		/* Whee!  Actually deliver the संकेत.  */
		handle_संकेत(&ksig, regs, save_r0);
		वापस;
	पूर्ण

	/* Did we come from a प्रणाली call? */
	अगर (regs->tra >= 0) अणु
		/* Restart the प्रणाली call - no handlers present */
		अगर (regs->regs[0] == -ERESTARTNOHAND ||
		    regs->regs[0] == -ERESTARTSYS ||
		    regs->regs[0] == -ERESTARTNOINTR) अणु
			regs->regs[0] = save_r0;
			regs->pc -= inकाष्ठाion_size(__raw_पढ़ोw(regs->pc - 4));
		पूर्ण अन्यथा अगर (regs->regs[0] == -ERESTART_RESTARTBLOCK) अणु
			regs->pc -= inकाष्ठाion_size(__raw_पढ़ोw(regs->pc - 4));
			regs->regs[3] = __NR_restart_syscall;
		पूर्ण
	पूर्ण

	/*
	 * If there's no संकेत to deliver, we just put the saved sigmask
	 * back.
	 */
	restore_saved_sigmask();
पूर्ण

यंत्रlinkage व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक save_r0,
				 अचिन्हित दीर्घ thपढ़ो_info_flags)
अणु
	/* deal with pending संकेत delivery */
	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs, save_r0);

	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME)
		tracehook_notअगरy_resume(regs);
पूर्ण
