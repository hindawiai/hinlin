<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Signal support क्रम Hexagon processor
 *
 * Copyright (c) 2010-2012, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/linkage.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/रेजिस्टरs.h>
#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/unistd.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/vdso.h>

काष्ठा rt_sigframe अणु
	अचिन्हित दीर्घ tramp[2];
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
पूर्ण;

अटल व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
			  माप_प्रकार frame_size)
अणु
	अचिन्हित दीर्घ sp = sigsp(regs->r29, ksig);

	वापस (व्योम __user *)((sp - frame_size) & ~(माप(दीर्घ दीर्घ) - 1));
पूर्ण

अटल पूर्णांक setup_sigcontext(काष्ठा pt_regs *regs, काष्ठा sigcontext __user *sc)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक err = 0;

	err |= copy_to_user(&sc->sc_regs.r0, &regs->r00,
			    32*माप(अचिन्हित दीर्घ));

	err |= __put_user(regs->sa0, &sc->sc_regs.sa0);
	err |= __put_user(regs->lc0, &sc->sc_regs.lc0);
	err |= __put_user(regs->sa1, &sc->sc_regs.sa1);
	err |= __put_user(regs->lc1, &sc->sc_regs.lc1);
	err |= __put_user(regs->m0, &sc->sc_regs.m0);
	err |= __put_user(regs->m1, &sc->sc_regs.m1);
	err |= __put_user(regs->usr, &sc->sc_regs.usr);
	err |= __put_user(regs->preds, &sc->sc_regs.p3_0);
	err |= __put_user(regs->gp, &sc->sc_regs.gp);
	err |= __put_user(regs->ugp, &sc->sc_regs.ugp);
#अगर CONFIG_HEXAGON_ARCH_VERSION >= 4
	err |= __put_user(regs->cs0, &sc->sc_regs.cs0);
	err |= __put_user(regs->cs1, &sc->sc_regs.cs1);
#पूर्ण_अगर
	पंचांगp = pt_elr(regs); err |= __put_user(पंचांगp, &sc->sc_regs.pc);
	पंचांगp = pt_cause(regs); err |= __put_user(पंचांगp, &sc->sc_regs.cause);
	पंचांगp = pt_badva(regs); err |= __put_user(पंचांगp, &sc->sc_regs.badva);

	वापस err;
पूर्ण

अटल पूर्णांक restore_sigcontext(काष्ठा pt_regs *regs,
			      काष्ठा sigcontext __user *sc)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक err = 0;

	err |= copy_from_user(&regs->r00, &sc->sc_regs.r0,
			      32 * माप(अचिन्हित दीर्घ));

	err |= __get_user(regs->sa0, &sc->sc_regs.sa0);
	err |= __get_user(regs->lc0, &sc->sc_regs.lc0);
	err |= __get_user(regs->sa1, &sc->sc_regs.sa1);
	err |= __get_user(regs->lc1, &sc->sc_regs.lc1);
	err |= __get_user(regs->m0, &sc->sc_regs.m0);
	err |= __get_user(regs->m1, &sc->sc_regs.m1);
	err |= __get_user(regs->usr, &sc->sc_regs.usr);
	err |= __get_user(regs->preds, &sc->sc_regs.p3_0);
	err |= __get_user(regs->gp, &sc->sc_regs.gp);
	err |= __get_user(regs->ugp, &sc->sc_regs.ugp);
#अगर CONFIG_HEXAGON_ARCH_VERSION >= 4
	err |= __get_user(regs->cs0, &sc->sc_regs.cs0);
	err |= __get_user(regs->cs1, &sc->sc_regs.cs1);
#पूर्ण_अगर
	err |= __get_user(पंचांगp, &sc->sc_regs.pc); pt_set_elr(regs, पंचांगp);

	वापस err;
पूर्ण

/*
 * Setup संकेत stack frame with siginfo काष्ठाure
 */
अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs)
अणु
	पूर्णांक err = 0;
	काष्ठा rt_sigframe __user *frame;
	काष्ठा hexagon_vdso *vdso = current->mm->context.vdso;

	frame = get_sigframe(ksig, regs, माप(काष्ठा rt_sigframe));

	अगर (!access_ok(frame, माप(काष्ठा rt_sigframe)))
		वापस -EFAULT;

	अगर (copy_siginfo_to_user(&frame->info, &ksig->info))
		वापस -EFAULT;

	/* The on-stack संकेत trampoline is no दीर्घer executed;
	 * however, the libgcc संकेत frame unwinding code checks क्रम
	 * the presence of these two numeric magic values.
	 */
	err |= __put_user(0x7800d166, &frame->tramp[0]);
	err |= __put_user(0x5400c004, &frame->tramp[1]);
	err |= setup_sigcontext(regs, &frame->uc.uc_mcontext);
	err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));
	err |= __save_altstack(&frame->uc.uc_stack, user_stack_poपूर्णांकer(regs));
	अगर (err)
		वापस -EFAULT;

	/* Load r0/r1 pair with signumber/siginfo poपूर्णांकer... */
	regs->r0100 = ((अचिन्हित दीर्घ दीर्घ)((अचिन्हित दीर्घ)&frame->info) << 32)
		| (अचिन्हित दीर्घ दीर्घ)ksig->sig;
	regs->r02 = (अचिन्हित दीर्घ) &frame->uc;
	regs->r31 = (अचिन्हित दीर्घ) vdso->rt_संकेत_trampoline;
	pt_psp(regs) = (अचिन्हित दीर्घ) frame;
	pt_set_elr(regs, (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler);

	वापस 0;
पूर्ण

/*
 * Setup invocation of संकेत handler
 */
अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;

	/*
	 * If we're handling a संकेत that पातed a प्रणाली call,
	 * set up the error वापस value beक्रमe adding the संकेत
	 * frame to the stack.
	 */

	अगर (regs->syscall_nr >= 0) अणु
		चयन (regs->r00) अणु
		हाल -ERESTART_RESTARTBLOCK:
		हाल -ERESTARTNOHAND:
			regs->r00 = -EINTR;
			अवरोध;
		हाल -ERESTARTSYS:
			अगर (!(ksig->ka.sa.sa_flags & SA_RESTART)) अणु
				regs->r00 = -EINTR;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल -ERESTARTNOINTR:
			regs->r06 = regs->syscall_nr;
			pt_set_elr(regs, pt_elr(regs) - 4);
			regs->r00 = regs->restart_r0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Set up the stack frame; not करोing the SA_SIGINFO thing.  We
	 * only set up the rt_frame flavor.
	 */
	/* If there was an error on setup, no संकेत was delivered. */
	ret = setup_rt_frame(ksig, sigmask_to_save(), regs);

	संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLESTEP));
पूर्ण

/*
 * Called from वापस-from-event code.
 */
व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	काष्ठा kसंकेत ksig;

	अगर (!user_mode(regs))
		वापस;

	अगर (get_संकेत(&ksig)) अणु
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	/*
	 * No (more) संकेतs; अगर we came from a प्रणाली call, handle the restart.
	 */

	अगर (regs->syscall_nr >= 0) अणु
		चयन (regs->r00) अणु
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			regs->r06 = regs->syscall_nr;
			अवरोध;
		हाल -ERESTART_RESTARTBLOCK:
			regs->r06 = __NR_restart_syscall;
			अवरोध;
		शेष:
			जाओ no_restart;
		पूर्ण
		pt_set_elr(regs, pt_elr(regs) - 4);
		regs->r00 = regs->restart_r0;
	पूर्ण

no_restart:
	/* If there's no संकेत to deliver, put the saved sigmask back */
	restore_saved_sigmask();
पूर्ण

/*
 * Architecture-specअगरic wrappers क्रम संकेत-related प्रणाली calls
 */

यंत्रlinkage पूर्णांक sys_rt_sigवापस(व्योम)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe __user *frame;
	sigset_t blocked;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	frame = (काष्ठा rt_sigframe __user *)pt_psp(regs);
	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_from_user(&blocked, &frame->uc.uc_sigmask, माप(blocked)))
		जाओ badframe;

	set_current_blocked(&blocked);

	अगर (restore_sigcontext(regs, &frame->uc.uc_mcontext))
		जाओ badframe;

	/* Restore the user's stack as well */
	pt_psp(regs) = regs->r29;

	regs->syscall_nr = -1;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस regs->r00;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण
