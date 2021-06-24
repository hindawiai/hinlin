<शैली गुरु>
/*
 * arch/xtensa/kernel/संकेत.c
 *
 * Default platक्रमm functions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005, 2006 Tensilica Inc.
 * Copyright (C) 1991, 1992  Linus Torvalds
 * 1997-11-28  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 *
 * Chris Zankel <chris@zankel.net>
 * Joe Taylor <joe@tensilica.com>
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/personality.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/ucontext.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/coprocessor.h>
#समावेश <यंत्र/unistd.h>

बाह्य काष्ठा task_काष्ठा *coproc_owners[];

काष्ठा rt_sigframe
अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
	काष्ठा अणु
		xtregs_opt_t opt;
		xtregs_user_t user;
#अगर XTENSA_HAVE_COPROCESSORS
		xtregs_coprocessor_t cp;
#पूर्ण_अगर
	पूर्ण xtregs;
	अचिन्हित अक्षर retcode[6];
	अचिन्हित पूर्णांक winकरोw[4];
पूर्ण;

/* 
 * Flush रेजिस्टर winकरोws stored in pt_regs to stack.
 * Returns 1 क्रम errors.
 */

पूर्णांक
flush_winकरोw_regs_user(काष्ठा pt_regs *regs)
अणु
	स्थिर अचिन्हित दीर्घ ws = regs->winकरोwstart;
	स्थिर अचिन्हित दीर्घ wb = regs->winकरोwbase;
	अचिन्हित दीर्घ sp = 0;
	अचिन्हित दीर्घ wm;
	पूर्णांक err = 1;
	पूर्णांक base;

	/* Return अगर no other frames. */

	अगर (regs->wmask == 1)
		वापस 0;

	/* Rotate winकरोwmask and skip empty frames. */

	wm = (ws >> wb) | (ws << (XCHAL_NUM_AREGS / 4 - wb));
	base = (XCHAL_NUM_AREGS / 4) - (regs->wmask >> 4);
		
	/* For call8 or call12 frames, we need the previous stack poपूर्णांकer. */

	अगर ((regs->wmask & 2) == 0)
		अगर (__get_user(sp, (पूर्णांक*)(regs->areg[base * 4 + 1] - 12)))
			जाओ errout;

	/* Spill frames to stack. */

	जबतक (base < XCHAL_NUM_AREGS / 4) अणु

		पूर्णांक m = (wm >> base);
		पूर्णांक inc = 0;

		/* Save रेजिस्टरs a4..a7 (call8) or a4...a11 (call12) */

		अगर (m & 2) अणु			/* call4 */
			inc = 1;

		पूर्ण अन्यथा अगर (m & 4) अणु		/* call8 */
			अगर (copy_to_user(&SPILL_SLOT_CALL8(sp, 4),
					 &regs->areg[(base + 1) * 4], 16))
				जाओ errout;
			inc = 2;

		पूर्ण अन्यथा अगर (m & 8) अणु	/* call12 */
			अगर (copy_to_user(&SPILL_SLOT_CALL12(sp, 4),
					 &regs->areg[(base + 1) * 4], 32))
				जाओ errout;
			inc = 3;
		पूर्ण

		/* Save current frame a0..a3 under next SP */

		sp = regs->areg[((base + inc) * 4 + 1) % XCHAL_NUM_AREGS];
		अगर (copy_to_user(&SPILL_SLOT(sp, 0), &regs->areg[base * 4], 16))
			जाओ errout;

		/* Get current stack poपूर्णांकer क्रम next loop iteration. */

		sp = regs->areg[base * 4 + 1];
		base += inc;
	पूर्ण

	regs->wmask = 1;
	regs->winकरोwstart = 1 << wb;

	वापस 0;

errout:
	वापस err;
पूर्ण

/*
 * Note: We करोn't copy double exception 'regs', we have to finish द्विगुन exc. 
 * first beक्रमe we वापस to संकेत handler! This dbl.exc.handler might cause 
 * another द्विगुन exception, but I think we are fine as the situation is the 
 * same as अगर we had वापसed to the संकेत handerl and got an पूर्णांकerrupt 
 * immediately...
 */

अटल पूर्णांक
setup_sigcontext(काष्ठा rt_sigframe __user *frame, काष्ठा pt_regs *regs)
अणु
	काष्ठा sigcontext __user *sc = &frame->uc.uc_mcontext;
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	पूर्णांक err = 0;

#घोषणा COPY(x)	err |= __put_user(regs->x, &sc->sc_##x)
	COPY(pc);
	COPY(ps);
	COPY(lbeg);
	COPY(lend);
	COPY(lcount);
	COPY(sar);
#अघोषित COPY

	err |= flush_winकरोw_regs_user(regs);
	err |= __copy_to_user (sc->sc_a, regs->areg, 16 * 4);
	err |= __put_user(0, &sc->sc_xtregs);

	अगर (err)
		वापस err;

#अगर XTENSA_HAVE_COPROCESSORS
	coprocessor_flush_all(ti);
	coprocessor_release_all(ti);
	err |= __copy_to_user(&frame->xtregs.cp, &ti->xtregs_cp,
			      माप (frame->xtregs.cp));
#पूर्ण_अगर
	err |= __copy_to_user(&frame->xtregs.opt, &regs->xtregs_opt,
			      माप (xtregs_opt_t));
	err |= __copy_to_user(&frame->xtregs.user, &ti->xtregs_user,
			      माप (xtregs_user_t));

	err |= __put_user(err ? शून्य : &frame->xtregs, &sc->sc_xtregs);

	वापस err;
पूर्ण

अटल पूर्णांक
restore_sigcontext(काष्ठा pt_regs *regs, काष्ठा rt_sigframe __user *frame)
अणु
	काष्ठा sigcontext __user *sc = &frame->uc.uc_mcontext;
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	अचिन्हित पूर्णांक err = 0;
	अचिन्हित दीर्घ ps;

#घोषणा COPY(x)	err |= __get_user(regs->x, &sc->sc_##x)
	COPY(pc);
	COPY(lbeg);
	COPY(lend);
	COPY(lcount);
	COPY(sar);
#अघोषित COPY

	/* All रेजिस्टरs were flushed to stack. Start with a pristine frame. */

	regs->wmask = 1;
	regs->winकरोwbase = 0;
	regs->winकरोwstart = 1;

	regs->syscall = NO_SYSCALL;	/* disable syscall checks */

	/* For PS, restore only PS.CALLINC.
	 * Assume that all other bits are either the same as क्रम the संकेत
	 * handler, or the user mode value करोesn't matter (e.g. PS.OWB).
	 */
	err |= __get_user(ps, &sc->sc_ps);
	regs->ps = (regs->ps & ~PS_CALLINC_MASK) | (ps & PS_CALLINC_MASK);

	/* Additional corruption checks */

	अगर ((regs->lcount > 0)
	    && ((regs->lbeg > TASK_SIZE) || (regs->lend > TASK_SIZE)) )
		err = 1;

	err |= __copy_from_user(regs->areg, sc->sc_a, 16 * 4);

	अगर (err)
		वापस err;

	/* The संकेत handler may have used coprocessors in which
	 * हाल they are still enabled.  We disable them to क्रमce a
	 * reloading of the original task's CP state by the lazy
	 * context-चयनing mechanisms of CP exception handling.
	 * Also, we essentially discard any coprocessor state that the
	 * संकेत handler created. */

#अगर XTENSA_HAVE_COPROCESSORS
	coprocessor_release_all(ti);
	err |= __copy_from_user(&ti->xtregs_cp, &frame->xtregs.cp,
				माप (frame->xtregs.cp));
#पूर्ण_अगर
	err |= __copy_from_user(&ti->xtregs_user, &frame->xtregs.user,
				माप (xtregs_user_t));
	err |= __copy_from_user(&regs->xtregs_opt, &frame->xtregs.opt,
				माप (xtregs_opt_t));

	वापस err;
पूर्ण


/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 */

यंत्रlinkage दीर्घ xtensa_rt_sigवापस(व्योम)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा rt_sigframe __user *frame;
	sigset_t set;
	पूर्णांक ret;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (regs->depc > 64)
		panic("rt_sigreturn in double exception!\n");

	frame = (काष्ठा rt_sigframe __user *) regs->areg[1];

	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;

	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	अगर (restore_sigcontext(regs, frame))
		जाओ badframe;

	ret = regs->areg[2];

	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;

	वापस ret;

badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण



/*
 * Set up a संकेत frame.
 */

अटल पूर्णांक
gen_वापस_code(अचिन्हित अक्षर *codemem)
अणु
	पूर्णांक err = 0;

	/*
	 * The 12-bit immediate is really split up within the 24-bit MOVI
	 * inकाष्ठाion.  As दीर्घ as the above प्रणाली call numbers fit within
	 * 8-bits, the following code works fine. See the Xtensa ISA क्रम
	 * details.
	 */

#अगर __NR_rt_sigवापस > 255
# error Generating the MOVI inकाष्ठाion below अवरोधs!
#पूर्ण_अगर

#अगर_घोषित __XTENSA_EB__   /* Big Endian version */
	/* Generate inकाष्ठाion:  MOVI a2, __NR_rt_sigवापस */
	err |= __put_user(0x22, &codemem[0]);
	err |= __put_user(0x0a, &codemem[1]);
	err |= __put_user(__NR_rt_sigवापस, &codemem[2]);
	/* Generate inकाष्ठाion:  SYSCALL */
	err |= __put_user(0x00, &codemem[3]);
	err |= __put_user(0x05, &codemem[4]);
	err |= __put_user(0x00, &codemem[5]);

#या_अगर defined __XTENSA_EL__   /* Little Endian version */
	/* Generate inकाष्ठाion:  MOVI a2, __NR_rt_sigवापस */
	err |= __put_user(0x22, &codemem[0]);
	err |= __put_user(0xa0, &codemem[1]);
	err |= __put_user(__NR_rt_sigवापस, &codemem[2]);
	/* Generate inकाष्ठाion:  SYSCALL */
	err |= __put_user(0x00, &codemem[3]);
	err |= __put_user(0x50, &codemem[4]);
	err |= __put_user(0x00, &codemem[5]);
#अन्यथा
# error Must use compiler क्रम Xtensa processors.
#पूर्ण_अगर

	/* Flush generated code out of the data cache */

	अगर (err == 0) अणु
		__invalidate_icache_range((अचिन्हित दीर्घ)codemem, 6UL);
		__flush_invalidate_dcache_range((अचिन्हित दीर्घ)codemem, 6UL);
	पूर्ण

	वापस err;
पूर्ण


अटल पूर्णांक setup_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
		       काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe *frame;
	पूर्णांक err = 0, sig = ksig->sig;
	अचिन्हित दीर्घ sp, ra, tp, ps;
	अचिन्हित पूर्णांक base;

	sp = regs->areg[1];

	अगर ((ksig->ka.sa.sa_flags & SA_ONSTACK) != 0 && sas_ss_flags(sp) == 0) अणु
		sp = current->sas_ss_sp + current->sas_ss_size;
	पूर्ण

	frame = (व्योम *)((sp - माप(*frame)) & -16ul);

	अगर (regs->depc > 64)
		panic ("Double exception sys_sigreturn\n");

	अगर (!access_ok(frame, माप(*frame))) अणु
		वापस -EFAULT;
	पूर्ण

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO) अणु
		err |= copy_siginfo_to_user(&frame->info, &ksig->info);
	पूर्ण

	/* Create the user context.  */

	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(0, &frame->uc.uc_link);
	err |= __save_altstack(&frame->uc.uc_stack, regs->areg[1]);
	err |= setup_sigcontext(frame, regs);
	err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));

	अगर (ksig->ka.sa.sa_flags & SA_RESTORER) अणु
		ra = (अचिन्हित दीर्घ)ksig->ka.sa.sa_restorer;
	पूर्ण अन्यथा अणु

		/* Create sys_rt_sigवापस syscall in stack frame */

		err |= gen_वापस_code(frame->retcode);

		अगर (err) अणु
			वापस -EFAULT;
		पूर्ण
		ra = (अचिन्हित दीर्घ) frame->retcode;
	पूर्ण

	/* 
	 * Create संकेत handler execution context.
	 * Return context not modअगरied until this poपूर्णांक.
	 */

	/* Set up रेजिस्टरs क्रम संकेत handler; preserve the thपढ़ोptr */
	tp = regs->thपढ़ोptr;
	ps = regs->ps;
	start_thपढ़ो(regs, (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler,
		     (अचिन्हित दीर्घ) frame);

	/* Set up a stack frame क्रम a call4 अगर userspace uses winकरोwed ABI */
	अगर (ps & PS_WOE_MASK) अणु
		base = 4;
		regs->areg[base] =
			(((अचिन्हित दीर्घ) ra) & 0x3fffffff) | 0x40000000;
		ps = (ps & ~(PS_CALLINC_MASK | PS_OWB_MASK)) |
			(1 << PS_CALLINC_SHIFT);
	पूर्ण अन्यथा अणु
		base = 0;
		regs->areg[base] = (अचिन्हित दीर्घ) ra;
	पूर्ण
	regs->areg[base + 2] = (अचिन्हित दीर्घ) sig;
	regs->areg[base + 3] = (अचिन्हित दीर्घ) &frame->info;
	regs->areg[base + 4] = (अचिन्हित दीर्घ) &frame->uc;
	regs->thपढ़ोptr = tp;
	regs->ps = ps;

	pr_debug("SIG rt deliver (%s:%d): signal=%d sp=%p pc=%08lx\n",
		 current->comm, current->pid, sig, frame, regs->pc);

	वापस 0;
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

	task_pt_regs(current)->icountlevel = 0;

	अगर (get_संकेत(&ksig)) अणु
		पूर्णांक ret;

		/* Are we from a प्रणाली call? */

		अगर (regs->syscall != NO_SYSCALL) अणु

			/* If so, check प्रणाली call restarting.. */

			चयन (regs->areg[2]) अणु
				हाल -ERESTARTNOHAND:
				हाल -ERESTART_RESTARTBLOCK:
					regs->areg[2] = -EINTR;
					अवरोध;

				हाल -ERESTARTSYS:
					अगर (!(ksig.ka.sa.sa_flags & SA_RESTART)) अणु
						regs->areg[2] = -EINTR;
						अवरोध;
					पूर्ण
					fallthrough;
				हाल -ERESTARTNOINTR:
					regs->areg[2] = regs->syscall;
					regs->pc -= 3;
					अवरोध;

				शेष:
					/* nothing to करो */
					अगर (regs->areg[2] != 0)
					अवरोध;
			पूर्ण
		पूर्ण

		/* Whee!  Actually deliver the संकेत.  */
		/* Set up the stack frame */
		ret = setup_frame(&ksig, sigmask_to_save(), regs);
		संकेत_setup_करोne(ret, &ksig, 0);
		अगर (current->ptrace & PT_SINGLESTEP)
			task_pt_regs(current)->icountlevel = 1;

		वापस;
	पूर्ण

	/* Did we come from a प्रणाली call? */
	अगर (regs->syscall != NO_SYSCALL) अणु
		/* Restart the प्रणाली call - no handlers present */
		चयन (regs->areg[2]) अणु
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			regs->areg[2] = regs->syscall;
			regs->pc -= 3;
			अवरोध;
		हाल -ERESTART_RESTARTBLOCK:
			regs->areg[2] = __NR_restart_syscall;
			regs->pc -= 3;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If there's no संकेत to deliver, we just restore the saved mask.  */
	restore_saved_sigmask();

	अगर (current->ptrace & PT_SINGLESTEP)
		task_pt_regs(current)->icountlevel = 1;
	वापस;
पूर्ण

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_SIGPENDING) ||
	    test_thपढ़ो_flag(TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs);

	अगर (test_thपढ़ो_flag(TIF_NOTIFY_RESUME))
		tracehook_notअगरy_resume(regs);
पूर्ण
