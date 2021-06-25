<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/personality.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/fpu.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/vdso.h>

काष्ठा rt_sigframe अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
पूर्ण;
#अगर IS_ENABLED(CONFIG_FPU)
अटल अंतरभूत पूर्णांक restore_sigcontext_fpu(काष्ठा pt_regs *regs,
					 काष्ठा sigcontext __user *sc)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	अचिन्हित दीर्घ used_math_flag;
	पूर्णांक ret = 0;

	clear_used_math();
	__get_user_error(used_math_flag, &sc->used_math_flag, ret);

	अगर (!used_math_flag)
		वापस 0;
	set_used_math();

#अगर IS_ENABLED(CONFIG_LAZY_FPU)
	preempt_disable();
	अगर (current == last_task_used_math) अणु
		last_task_used_math = शून्य;
		disable_ptreg_fpu(regs);
	पूर्ण
	preempt_enable();
#अन्यथा
	clear_fpu(regs);
#पूर्ण_अगर

	वापस __copy_from_user(&tsk->thपढ़ो.fpu, &sc->fpu,
				माप(काष्ठा fpu_काष्ठा));
पूर्ण

अटल अंतरभूत पूर्णांक setup_sigcontext_fpu(काष्ठा pt_regs *regs,
				       काष्ठा sigcontext __user *sc)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	पूर्णांक ret = 0;

	__put_user_error(used_math(), &sc->used_math_flag, ret);

	अगर (!used_math())
		वापस ret;

	preempt_disable();
#अगर IS_ENABLED(CONFIG_LAZY_FPU)
	अगर (last_task_used_math == tsk)
		save_fpu(last_task_used_math);
#अन्यथा
	unlazy_fpu(tsk);
#पूर्ण_अगर
	ret = __copy_to_user(&sc->fpu, &tsk->thपढ़ो.fpu,
			     माप(काष्ठा fpu_काष्ठा));
	preempt_enable();
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक restore_sigframe(काष्ठा pt_regs *regs,
			    काष्ठा rt_sigframe __user * sf)
अणु
	sigset_t set;
	पूर्णांक err;

	err = __copy_from_user(&set, &sf->uc.uc_sigmask, माप(set));
	अगर (err == 0) अणु
		set_current_blocked(&set);
	पूर्ण

	__get_user_error(regs->uregs[0], &sf->uc.uc_mcontext.nds32_r0, err);
	__get_user_error(regs->uregs[1], &sf->uc.uc_mcontext.nds32_r1, err);
	__get_user_error(regs->uregs[2], &sf->uc.uc_mcontext.nds32_r2, err);
	__get_user_error(regs->uregs[3], &sf->uc.uc_mcontext.nds32_r3, err);
	__get_user_error(regs->uregs[4], &sf->uc.uc_mcontext.nds32_r4, err);
	__get_user_error(regs->uregs[5], &sf->uc.uc_mcontext.nds32_r5, err);
	__get_user_error(regs->uregs[6], &sf->uc.uc_mcontext.nds32_r6, err);
	__get_user_error(regs->uregs[7], &sf->uc.uc_mcontext.nds32_r7, err);
	__get_user_error(regs->uregs[8], &sf->uc.uc_mcontext.nds32_r8, err);
	__get_user_error(regs->uregs[9], &sf->uc.uc_mcontext.nds32_r9, err);
	__get_user_error(regs->uregs[10], &sf->uc.uc_mcontext.nds32_r10, err);
	__get_user_error(regs->uregs[11], &sf->uc.uc_mcontext.nds32_r11, err);
	__get_user_error(regs->uregs[12], &sf->uc.uc_mcontext.nds32_r12, err);
	__get_user_error(regs->uregs[13], &sf->uc.uc_mcontext.nds32_r13, err);
	__get_user_error(regs->uregs[14], &sf->uc.uc_mcontext.nds32_r14, err);
	__get_user_error(regs->uregs[15], &sf->uc.uc_mcontext.nds32_r15, err);
	__get_user_error(regs->uregs[16], &sf->uc.uc_mcontext.nds32_r16, err);
	__get_user_error(regs->uregs[17], &sf->uc.uc_mcontext.nds32_r17, err);
	__get_user_error(regs->uregs[18], &sf->uc.uc_mcontext.nds32_r18, err);
	__get_user_error(regs->uregs[19], &sf->uc.uc_mcontext.nds32_r19, err);
	__get_user_error(regs->uregs[20], &sf->uc.uc_mcontext.nds32_r20, err);
	__get_user_error(regs->uregs[21], &sf->uc.uc_mcontext.nds32_r21, err);
	__get_user_error(regs->uregs[22], &sf->uc.uc_mcontext.nds32_r22, err);
	__get_user_error(regs->uregs[23], &sf->uc.uc_mcontext.nds32_r23, err);
	__get_user_error(regs->uregs[24], &sf->uc.uc_mcontext.nds32_r24, err);
	__get_user_error(regs->uregs[25], &sf->uc.uc_mcontext.nds32_r25, err);

	__get_user_error(regs->fp, &sf->uc.uc_mcontext.nds32_fp, err);
	__get_user_error(regs->gp, &sf->uc.uc_mcontext.nds32_gp, err);
	__get_user_error(regs->lp, &sf->uc.uc_mcontext.nds32_lp, err);
	__get_user_error(regs->sp, &sf->uc.uc_mcontext.nds32_sp, err);
	__get_user_error(regs->ipc, &sf->uc.uc_mcontext.nds32_ipc, err);
#अगर defined(CONFIG_HWZOL)
	__get_user_error(regs->lc, &sf->uc.uc_mcontext.zol.nds32_lc, err);
	__get_user_error(regs->le, &sf->uc.uc_mcontext.zol.nds32_le, err);
	__get_user_error(regs->lb, &sf->uc.uc_mcontext.zol.nds32_lb, err);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_FPU)
	err |= restore_sigcontext_fpu(regs, &sf->uc.uc_mcontext);
#पूर्ण_अगर
	/*
	 * Aव्योम sys_rt_sigवापस() restarting.
	 */
	क्रमget_syscall(regs);
	वापस err;
पूर्ण

यंत्रlinkage दीर्घ sys_rt_sigवापस(काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/*
	 * Since we stacked the संकेत on a 64-bit boundary,
	 * then 'sp' should be two-word aligned here.  If it's
	 * not, then the user is trying to mess with us.
	 */
	अगर (regs->sp & 7)
		जाओ badframe;

	frame = (काष्ठा rt_sigframe __user *)regs->sp;

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;

	अगर (restore_sigframe(regs, frame))
		जाओ badframe;

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस regs->uregs[0];

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

अटल पूर्णांक
setup_sigframe(काष्ठा rt_sigframe __user * sf, काष्ठा pt_regs *regs,
	       sigset_t * set)
अणु
	पूर्णांक err = 0;

	__put_user_error(regs->uregs[0], &sf->uc.uc_mcontext.nds32_r0, err);
	__put_user_error(regs->uregs[1], &sf->uc.uc_mcontext.nds32_r1, err);
	__put_user_error(regs->uregs[2], &sf->uc.uc_mcontext.nds32_r2, err);
	__put_user_error(regs->uregs[3], &sf->uc.uc_mcontext.nds32_r3, err);
	__put_user_error(regs->uregs[4], &sf->uc.uc_mcontext.nds32_r4, err);
	__put_user_error(regs->uregs[5], &sf->uc.uc_mcontext.nds32_r5, err);
	__put_user_error(regs->uregs[6], &sf->uc.uc_mcontext.nds32_r6, err);
	__put_user_error(regs->uregs[7], &sf->uc.uc_mcontext.nds32_r7, err);
	__put_user_error(regs->uregs[8], &sf->uc.uc_mcontext.nds32_r8, err);
	__put_user_error(regs->uregs[9], &sf->uc.uc_mcontext.nds32_r9, err);
	__put_user_error(regs->uregs[10], &sf->uc.uc_mcontext.nds32_r10, err);
	__put_user_error(regs->uregs[11], &sf->uc.uc_mcontext.nds32_r11, err);
	__put_user_error(regs->uregs[12], &sf->uc.uc_mcontext.nds32_r12, err);
	__put_user_error(regs->uregs[13], &sf->uc.uc_mcontext.nds32_r13, err);
	__put_user_error(regs->uregs[14], &sf->uc.uc_mcontext.nds32_r14, err);
	__put_user_error(regs->uregs[15], &sf->uc.uc_mcontext.nds32_r15, err);
	__put_user_error(regs->uregs[16], &sf->uc.uc_mcontext.nds32_r16, err);
	__put_user_error(regs->uregs[17], &sf->uc.uc_mcontext.nds32_r17, err);
	__put_user_error(regs->uregs[18], &sf->uc.uc_mcontext.nds32_r18, err);
	__put_user_error(regs->uregs[19], &sf->uc.uc_mcontext.nds32_r19, err);
	__put_user_error(regs->uregs[20], &sf->uc.uc_mcontext.nds32_r20, err);

	__put_user_error(regs->uregs[21], &sf->uc.uc_mcontext.nds32_r21, err);
	__put_user_error(regs->uregs[22], &sf->uc.uc_mcontext.nds32_r22, err);
	__put_user_error(regs->uregs[23], &sf->uc.uc_mcontext.nds32_r23, err);
	__put_user_error(regs->uregs[24], &sf->uc.uc_mcontext.nds32_r24, err);
	__put_user_error(regs->uregs[25], &sf->uc.uc_mcontext.nds32_r25, err);
	__put_user_error(regs->fp, &sf->uc.uc_mcontext.nds32_fp, err);
	__put_user_error(regs->gp, &sf->uc.uc_mcontext.nds32_gp, err);
	__put_user_error(regs->lp, &sf->uc.uc_mcontext.nds32_lp, err);
	__put_user_error(regs->sp, &sf->uc.uc_mcontext.nds32_sp, err);
	__put_user_error(regs->ipc, &sf->uc.uc_mcontext.nds32_ipc, err);
#अगर defined(CONFIG_HWZOL)
	__put_user_error(regs->lc, &sf->uc.uc_mcontext.zol.nds32_lc, err);
	__put_user_error(regs->le, &sf->uc.uc_mcontext.zol.nds32_le, err);
	__put_user_error(regs->lb, &sf->uc.uc_mcontext.zol.nds32_lb, err);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_FPU)
	err |= setup_sigcontext_fpu(regs, &sf->uc.uc_mcontext);
#पूर्ण_अगर

	__put_user_error(current->thपढ़ो.trap_no, &sf->uc.uc_mcontext.trap_no,
			 err);
	__put_user_error(current->thपढ़ो.error_code,
			 &sf->uc.uc_mcontext.error_code, err);
	__put_user_error(current->thपढ़ो.address,
			 &sf->uc.uc_mcontext.fault_address, err);
	__put_user_error(set->sig[0], &sf->uc.uc_mcontext.oldmask, err);

	err |= __copy_to_user(&sf->uc.uc_sigmask, set, माप(*set));

	वापस err;
पूर्ण

अटल अंतरभूत व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig,
					काष्ठा pt_regs *regs, पूर्णांक framesize)
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
	sp = (sigsp(sp, ksig) - framesize);

	/*
	 * nds32 mandates 8-byte alignment
	 */
	sp &= ~0x7UL;

	वापस (व्योम __user *)sp;
पूर्ण

अटल पूर्णांक
setup_वापस(काष्ठा pt_regs *regs, काष्ठा kसंकेत *ksig, व्योम __user * frame)
अणु
	अचिन्हित दीर्घ handler = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;
	अचिन्हित दीर्घ retcode;

	retcode = VDSO_SYMBOL(current->mm->context.vdso, rt_sigtramp);
	regs->uregs[0] = ksig->sig;
	regs->sp = (अचिन्हित दीर्घ)frame;
	regs->lp = retcode;
	regs->ipc = handler;

	वापस 0;
पूर्ण

अटल पूर्णांक
setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t * set, काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame =
	    get_sigframe(ksig, regs, माप(*frame));
	पूर्णांक err = 0;

	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	__put_user_error(0, &frame->uc.uc_flags, err);
	__put_user_error(शून्य, &frame->uc.uc_link, err);

	err |= __save_altstack(&frame->uc.uc_stack, regs->sp);
	err |= setup_sigframe(frame, regs, set);
	अगर (err == 0) अणु
		setup_वापस(regs, ksig, frame);
		अगर (ksig->ka.sa.sa_flags & SA_SIGINFO) अणु
			err |= copy_siginfo_to_user(&frame->info, &ksig->info);
			regs->uregs[1] = (अचिन्हित दीर्घ)&frame->info;
			regs->uregs[2] = (अचिन्हित दीर्घ)&frame->uc;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/*
 * OK, we're invoking a handler
 */
अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;
	sigset_t *oldset = sigmask_to_save();

	अगर (in_syscall(regs)) अणु
		/* Aव्योम additional syscall restarting via ret_slow_syscall. */
		क्रमget_syscall(regs);

		चयन (regs->uregs[0]) अणु
		हाल -ERESTART_RESTARTBLOCK:
		हाल -ERESTARTNOHAND:
			regs->uregs[0] = -EINTR;
			अवरोध;
		हाल -ERESTARTSYS:
			अगर (!(ksig->ka.sa.sa_flags & SA_RESTART)) अणु
				regs->uregs[0] = -EINTR;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल -ERESTARTNOINTR:
			regs->uregs[0] = regs->orig_r0;
			regs->ipc -= 4;
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * Set up the stack frame
	 */
	ret = setup_rt_frame(ksig, oldset, regs);

	संकेत_setup_करोne(ret, ksig, 0);
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
अटल व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	काष्ठा kसंकेत ksig;

	अगर (get_संकेत(&ksig)) अणु
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	/*
	 * If we were from a प्रणाली call, check क्रम प्रणाली call restarting...
	 */
	अगर (in_syscall(regs)) अणु
		/* Restart the प्रणाली call - no handlers present */

		/* Aव्योम additional syscall restarting via ret_slow_syscall. */
		क्रमget_syscall(regs);

		चयन (regs->uregs[0]) अणु
		हाल -ERESTART_RESTARTBLOCK:
			regs->uregs[15] = __NR_restart_syscall;
			fallthrough;
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			regs->uregs[0] = regs->orig_r0;
			regs->ipc -= 0x4;
			अवरोध;
		पूर्ण
	पूर्ण
	restore_saved_sigmask();
पूर्ण

यंत्रlinkage व्योम
करो_notअगरy_resume(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक thपढ़ो_flags)
अणु
	अगर (thपढ़ो_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs);

	अगर (thपढ़ो_flags & _TIF_NOTIFY_RESUME)
		tracehook_notअगरy_resume(regs);
पूर्ण
