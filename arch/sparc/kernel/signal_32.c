<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  linux/arch/sparc/kernel/संकेत.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)
 *  Copyright (C) 1997 Eddie C. Dost   (ecd@skynet.be)
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/smp.h>
#समावेश <linux/binfmts.h>	/* करो_coredum */
#समावेश <linux/bitops.h>
#समावेश <linux/tracehook.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/cacheflush.h>	/* flush_sig_insns */
#समावेश <यंत्र/चयन_to.h>

#समावेश "sigutil.h"
#समावेश "kernel.h"

बाह्य व्योम fpsave(अचिन्हित दीर्घ *fpregs, अचिन्हित दीर्घ *fsr,
		   व्योम *fpqueue, अचिन्हित दीर्घ *fpqdepth);
बाह्य व्योम fpload(अचिन्हित दीर्घ *fpregs, अचिन्हित दीर्घ *fsr);

काष्ठा संकेत_frame अणु
	काष्ठा sparc_stackf	ss;
	__siginfo32_t		info;
	__siginfo_fpu_t __user	*fpu_save;
	अचिन्हित दीर्घ		insns[2] __attribute__ ((aligned (8)));
	अचिन्हित पूर्णांक		extramask[_NSIG_WORDS - 1];
	अचिन्हित पूर्णांक		extra_size; /* Should be 0 */
	__siginfo_rwin_t __user	*rwin_save;
पूर्ण __attribute__((aligned(8)));

काष्ठा rt_संकेत_frame अणु
	काष्ठा sparc_stackf	ss;
	siginfo_t		info;
	काष्ठा pt_regs		regs;
	sigset_t		mask;
	__siginfo_fpu_t __user	*fpu_save;
	अचिन्हित पूर्णांक		insns[2];
	stack_t			stack;
	अचिन्हित पूर्णांक		extra_size; /* Should be 0 */
	__siginfo_rwin_t __user	*rwin_save;
पूर्ण __attribute__((aligned(8)));

/* Align macros */
#घोषणा SF_ALIGNEDSZ  (((माप(काष्ठा संकेत_frame) + 7) & (~7)))
#घोषणा RT_ALIGNEDSZ  (((माप(काष्ठा rt_संकेत_frame) + 7) & (~7)))

/* Checks अगर the fp is valid.  We always build संकेत frames which are
 * 16-byte aligned, thereक्रमe we can always enक्रमce that the restore
 * frame has that property as well.
 */
अटल अंतरभूत bool invalid_frame_poपूर्णांकer(व्योम __user *fp, पूर्णांक fplen)
अणु
	अगर ((((अचिन्हित दीर्घ) fp) & 15) || !__access_ok((अचिन्हित दीर्घ)fp, fplen))
		वापस true;

	वापस false;
पूर्ण

यंत्रlinkage व्योम करो_sigवापस(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ up_psr, pc, npc, ufp;
	काष्ठा संकेत_frame __user *sf;
	sigset_t set;
	__siginfo_fpu_t __user *fpu_save;
	__siginfo_rwin_t __user *rwin_save;
	पूर्णांक err;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	synchronize_user_stack();

	sf = (काष्ठा संकेत_frame __user *) regs->u_regs[UREG_FP];

	/* 1. Make sure we are not getting garbage from the user */
	अगर (invalid_frame_poपूर्णांकer(sf, माप(*sf)))
		जाओ segv_and_निकास;

	अगर (get_user(ufp, &sf->info.si_regs.u_regs[UREG_FP]))
		जाओ segv_and_निकास;

	अगर (ufp & 0x7)
		जाओ segv_and_निकास;

	err = __get_user(pc,  &sf->info.si_regs.pc);
	err |= __get_user(npc, &sf->info.si_regs.npc);

	अगर ((pc | npc) & 3)
		जाओ segv_and_निकास;

	/* 2. Restore the state */
	up_psr = regs->psr;
	err |= __copy_from_user(regs, &sf->info.si_regs, माप(काष्ठा pt_regs));

	/* User can only change condition codes and FPU enabling in %psr. */
	regs->psr = (up_psr & ~(PSR_ICC | PSR_EF))
		  | (regs->psr & (PSR_ICC | PSR_EF));

	/* Prevent syscall restart.  */
	pt_regs_clear_syscall(regs);

	err |= __get_user(fpu_save, &sf->fpu_save);
	अगर (fpu_save)
		err |= restore_fpu_state(regs, fpu_save);
	err |= __get_user(rwin_save, &sf->rwin_save);
	अगर (rwin_save)
		err |= restore_rwin_state(rwin_save);

	/* This is pretty much atomic, no amount locking would prevent
	 * the races which exist anyways.
	 */
	err |= __get_user(set.sig[0], &sf->info.si_mask);
	err |= __copy_from_user(&set.sig[1], &sf->extramask,
			        (_NSIG_WORDS-1) * माप(अचिन्हित पूर्णांक));
			   
	अगर (err)
		जाओ segv_and_निकास;

	set_current_blocked(&set);
	वापस;

segv_and_निकास:
	क्रमce_sig(संक_अंश);
पूर्ण

यंत्रlinkage व्योम करो_rt_sigवापस(काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_संकेत_frame __user *sf;
	अचिन्हित पूर्णांक psr, pc, npc, ufp;
	__siginfo_fpu_t __user *fpu_save;
	__siginfo_rwin_t __user *rwin_save;
	sigset_t set;
	पूर्णांक err;

	synchronize_user_stack();
	sf = (काष्ठा rt_संकेत_frame __user *) regs->u_regs[UREG_FP];
	अगर (invalid_frame_poपूर्णांकer(sf, माप(*sf)))
		जाओ segv;

	अगर (get_user(ufp, &sf->regs.u_regs[UREG_FP]))
		जाओ segv;

	अगर (ufp & 0x7)
		जाओ segv;

	err = __get_user(pc, &sf->regs.pc);
	err |= __get_user(npc, &sf->regs.npc);
	err |= ((pc | npc) & 0x03);

	err |= __get_user(regs->y, &sf->regs.y);
	err |= __get_user(psr, &sf->regs.psr);

	err |= __copy_from_user(&regs->u_regs[UREG_G1],
				&sf->regs.u_regs[UREG_G1], 15 * माप(u32));

	regs->psr = (regs->psr & ~PSR_ICC) | (psr & PSR_ICC);

	/* Prevent syscall restart.  */
	pt_regs_clear_syscall(regs);

	err |= __get_user(fpu_save, &sf->fpu_save);
	अगर (!err && fpu_save)
		err |= restore_fpu_state(regs, fpu_save);
	err |= __copy_from_user(&set, &sf->mask, माप(sigset_t));
	err |= restore_altstack(&sf->stack);
	
	अगर (err)
		जाओ segv;
		
	regs->pc = pc;
	regs->npc = npc;
	
	err |= __get_user(rwin_save, &sf->rwin_save);
	अगर (!err && rwin_save) अणु
		अगर (restore_rwin_state(rwin_save))
			जाओ segv;
	पूर्ण

	set_current_blocked(&set);
	वापस;
segv:
	क्रमce_sig(संक_अंश);
पूर्ण

अटल अंतरभूत व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs, अचिन्हित दीर्घ framesize)
अणु
	अचिन्हित दीर्घ sp = regs->u_regs[UREG_FP];

	/*
	 * If we are on the alternate संकेत stack and would overflow it, करोn't.
	 * Return an always-bogus address instead so we will die with संक_अंश.
	 */
	अगर (on_sig_stack(sp) && !likely(on_sig_stack(sp - framesize)))
		वापस (व्योम __user *) -1L;

	/* This is the X/Open sanctioned संकेत stack चयनing.  */
	sp = sigsp(sp, ksig) - framesize;

	/* Always align the stack frame.  This handles two हालs.  First,
	 * sigaltstack need not be mindful of platक्रमm specअगरic stack
	 * alignment.  Second, अगर we took this संकेत because the stack
	 * is not aligned properly, we'd like to take the संकेत cleanly
	 * and report that.
	 */
	sp &= ~15UL;

	वापस (व्योम __user *) sp;
पूर्ण

अटल पूर्णांक setup_frame(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
		       sigset_t *oldset)
अणु
	काष्ठा संकेत_frame __user *sf;
	पूर्णांक sigframe_size, err, wsaved;
	व्योम __user *tail;

	/* 1. Make sure everything is clean */
	synchronize_user_stack();

	wsaved = current_thपढ़ो_info()->w_saved;

	sigframe_size = माप(*sf);
	अगर (used_math())
		sigframe_size += माप(__siginfo_fpu_t);
	अगर (wsaved)
		sigframe_size += माप(__siginfo_rwin_t);

	sf = (काष्ठा संकेत_frame __user *)
		get_sigframe(ksig, regs, sigframe_size);

	अगर (invalid_frame_poपूर्णांकer(sf, sigframe_size)) अणु
		करो_निकास(संक_अवैध);
		वापस -EINVAL;
	पूर्ण

	tail = sf + 1;

	/* 2. Save the current process state */
	err = __copy_to_user(&sf->info.si_regs, regs, माप(काष्ठा pt_regs));
	
	err |= __put_user(0, &sf->extra_size);

	अगर (used_math()) अणु
		__siginfo_fpu_t __user *fp = tail;
		tail += माप(*fp);
		err |= save_fpu_state(regs, fp);
		err |= __put_user(fp, &sf->fpu_save);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->fpu_save);
	पूर्ण
	अगर (wsaved) अणु
		__siginfo_rwin_t __user *rwp = tail;
		tail += माप(*rwp);
		err |= save_rwin_state(wsaved, rwp);
		err |= __put_user(rwp, &sf->rwin_save);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->rwin_save);
	पूर्ण

	err |= __put_user(oldset->sig[0], &sf->info.si_mask);
	err |= __copy_to_user(sf->extramask, &oldset->sig[1],
			      (_NSIG_WORDS - 1) * माप(अचिन्हित पूर्णांक));
	अगर (!wsaved) अणु
		err |= __copy_to_user(sf, (अक्षर *) regs->u_regs[UREG_FP],
				      माप(काष्ठा reg_winकरोw32));
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw32 *rp;

		rp = &current_thपढ़ो_info()->reg_winकरोw[wsaved - 1];
		err |= __copy_to_user(sf, rp, माप(काष्ठा reg_winकरोw32));
	पूर्ण
	अगर (err)
		वापस err;
	
	/* 3. संकेत handler back-trampoline and parameters */
	regs->u_regs[UREG_FP] = (अचिन्हित दीर्घ) sf;
	regs->u_regs[UREG_I0] = ksig->sig;
	regs->u_regs[UREG_I1] = (अचिन्हित दीर्घ) &sf->info;
	regs->u_regs[UREG_I2] = (अचिन्हित दीर्घ) &sf->info;

	/* 4. संकेत handler */
	regs->pc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	regs->npc = (regs->pc + 4);

	/* 5. वापस to kernel inकाष्ठाions */
	अगर (ksig->ka.ka_restorer)
		regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ)ksig->ka.ka_restorer;
	अन्यथा अणु
		regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ)(&(sf->insns[0]) - 2);

		/* mov __NR_sigवापस, %g1 */
		err |= __put_user(0x821020d8, &sf->insns[0]);

		/* t 0x10 */
		err |= __put_user(0x91d02010, &sf->insns[1]);
		अगर (err)
			वापस err;

		/* Flush inकाष्ठाion space. */
		flush_sig_insns(current->mm, (अचिन्हित दीर्घ) &(sf->insns[0]));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
			  sigset_t *oldset)
अणु
	काष्ठा rt_संकेत_frame __user *sf;
	पूर्णांक sigframe_size, wsaved;
	व्योम __user *tail;
	अचिन्हित पूर्णांक psr;
	पूर्णांक err;

	synchronize_user_stack();
	wsaved = current_thपढ़ो_info()->w_saved;
	sigframe_size = माप(*sf);
	अगर (used_math())
		sigframe_size += माप(__siginfo_fpu_t);
	अगर (wsaved)
		sigframe_size += माप(__siginfo_rwin_t);
	sf = (काष्ठा rt_संकेत_frame __user *)
		get_sigframe(ksig, regs, sigframe_size);
	अगर (invalid_frame_poपूर्णांकer(sf, sigframe_size)) अणु
		करो_निकास(संक_अवैध);
		वापस -EINVAL;
	पूर्ण

	tail = sf + 1;
	err  = __put_user(regs->pc, &sf->regs.pc);
	err |= __put_user(regs->npc, &sf->regs.npc);
	err |= __put_user(regs->y, &sf->regs.y);
	psr = regs->psr;
	अगर (used_math())
		psr |= PSR_EF;
	err |= __put_user(psr, &sf->regs.psr);
	err |= __copy_to_user(&sf->regs.u_regs, regs->u_regs, माप(regs->u_regs));
	err |= __put_user(0, &sf->extra_size);

	अगर (psr & PSR_EF) अणु
		__siginfo_fpu_t __user *fp = tail;
		tail += माप(*fp);
		err |= save_fpu_state(regs, fp);
		err |= __put_user(fp, &sf->fpu_save);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->fpu_save);
	पूर्ण
	अगर (wsaved) अणु
		__siginfo_rwin_t __user *rwp = tail;
		tail += माप(*rwp);
		err |= save_rwin_state(wsaved, rwp);
		err |= __put_user(rwp, &sf->rwin_save);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->rwin_save);
	पूर्ण
	err |= __copy_to_user(&sf->mask, &oldset->sig[0], माप(sigset_t));
	
	/* Setup sigaltstack */
	err |= __save_altstack(&sf->stack, regs->u_regs[UREG_FP]);
	
	अगर (!wsaved) अणु
		err |= __copy_to_user(sf, (अक्षर *) regs->u_regs[UREG_FP],
				      माप(काष्ठा reg_winकरोw32));
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw32 *rp;

		rp = &current_thपढ़ो_info()->reg_winकरोw[wsaved - 1];
		err |= __copy_to_user(sf, rp, माप(काष्ठा reg_winकरोw32));
	पूर्ण

	err |= copy_siginfo_to_user(&sf->info, &ksig->info);

	अगर (err)
		वापस err;

	regs->u_regs[UREG_FP] = (अचिन्हित दीर्घ) sf;
	regs->u_regs[UREG_I0] = ksig->sig;
	regs->u_regs[UREG_I1] = (अचिन्हित दीर्घ) &sf->info;
	regs->u_regs[UREG_I2] = (अचिन्हित दीर्घ) &sf->regs;

	regs->pc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	regs->npc = (regs->pc + 4);

	अगर (ksig->ka.ka_restorer)
		regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ)ksig->ka.ka_restorer;
	अन्यथा अणु
		regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ)(&(sf->insns[0]) - 2);

		/* mov __NR_rt_sigवापस, %g1 */
		err |= __put_user(0x82102065, &sf->insns[0]);

		/* t 0x10 */
		err |= __put_user(0x91d02010, &sf->insns[1]);
		अगर (err)
			वापस err;

		/* Flush inकाष्ठाion space. */
		flush_sig_insns(current->mm, (अचिन्हित दीर्घ) &(sf->insns[0]));
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक err;

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err = setup_rt_frame(ksig, regs, oldset);
	अन्यथा
		err = setup_frame(ksig, regs, oldset);
	संकेत_setup_करोne(err, ksig, 0);
पूर्ण

अटल अंतरभूत व्योम syscall_restart(अचिन्हित दीर्घ orig_i0, काष्ठा pt_regs *regs,
				   काष्ठा sigaction *sa)
अणु
	चयन(regs->u_regs[UREG_I0]) अणु
	हाल ERESTART_RESTARTBLOCK:
	हाल ERESTARTNOHAND:
	no_प्रणाली_call_restart:
		regs->u_regs[UREG_I0] = EINTR;
		regs->psr |= PSR_C;
		अवरोध;
	हाल ERESTARTSYS:
		अगर (!(sa->sa_flags & SA_RESTART))
			जाओ no_प्रणाली_call_restart;
		fallthrough;
	हाल ERESTARTNOINTR:
		regs->u_regs[UREG_I0] = orig_i0;
		regs->pc -= 4;
		regs->npc -= 4;
	पूर्ण
पूर्ण

/* Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 */
अटल व्योम करो_संकेत(काष्ठा pt_regs *regs, अचिन्हित दीर्घ orig_i0)
अणु
	काष्ठा kसंकेत ksig;
	पूर्णांक restart_syscall;
	bool has_handler;

	/* It's a lot of work and synchronization to add a new ptrace
	 * रेजिस्टर क्रम GDB to save and restore in order to get
	 * orig_i0 correct क्रम syscall restarts when debugging.
	 *
	 * Although it should be the हाल that most of the global
	 * रेजिस्टरs are अस्थिर across a प्रणाली call, glibc alपढ़ोy
	 * depends upon that fact that we preserve them.  So we can't
	 * just use any global रेजिस्टर to save away the orig_i0 value.
	 *
	 * In particular %g2, %g3, %g4, and %g5 are all assumed to be
	 * preserved across a प्रणाली call trap by various pieces of
	 * code in glibc.
	 *
	 * %g7 is used as the "thread register".   %g6 is not used in
	 * any fixed manner.  %g6 is used as a scratch रेजिस्टर and
	 * a compiler temporary, but it's value is never used across
	 * a प्रणाली call.  Thereक्रमe %g6 is usable क्रम orig_i0 storage.
	 */
	अगर (pt_regs_is_syscall(regs) && (regs->psr & PSR_C))
		regs->u_regs[UREG_G6] = orig_i0;

	has_handler = get_संकेत(&ksig);

	/* If the debugger messes with the program counter, it clears
	 * the software "in syscall" bit, directing us to not perक्रमm
	 * a syscall restart.
	 */
	restart_syscall = 0;
	अगर (pt_regs_is_syscall(regs) && (regs->psr & PSR_C)) अणु
		restart_syscall = 1;
		orig_i0 = regs->u_regs[UREG_G6];
	पूर्ण

	अगर (has_handler) अणु
		अगर (restart_syscall)
			syscall_restart(orig_i0, regs, &ksig.ka.sa);
		handle_संकेत(&ksig, regs);
	पूर्ण अन्यथा अणु
		अगर (restart_syscall) अणु
			चयन (regs->u_regs[UREG_I0]) अणु
			हाल ERESTARTNOHAND:
	     		हाल ERESTARTSYS:
			हाल ERESTARTNOINTR:
				/* replay the प्रणाली call when we are करोne */
				regs->u_regs[UREG_I0] = orig_i0;
				regs->pc -= 4;
				regs->npc -= 4;
				pt_regs_clear_syscall(regs);
				fallthrough;
			हाल ERESTART_RESTARTBLOCK:
				regs->u_regs[UREG_G1] = __NR_restart_syscall;
				regs->pc -= 4;
				regs->npc -= 4;
				pt_regs_clear_syscall(regs);
			पूर्ण
		पूर्ण
		restore_saved_sigmask();
	पूर्ण
पूर्ण

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, अचिन्हित दीर्घ orig_i0,
		      अचिन्हित दीर्घ thपढ़ो_info_flags)
अणु
	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs, orig_i0);
	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME)
		tracehook_notअगरy_resume(regs);
पूर्ण

यंत्रlinkage पूर्णांक करो_sys_sigstack(काष्ठा sigstack __user *ssptr,
                               काष्ठा sigstack __user *ossptr,
                               अचिन्हित दीर्घ sp)
अणु
	पूर्णांक ret = -EFAULT;

	/* First see अगर old state is wanted. */
	अगर (ossptr) अणु
		अगर (put_user(current->sas_ss_sp + current->sas_ss_size,
			     &ossptr->the_stack) ||
		    __put_user(on_sig_stack(sp), &ossptr->cur_status))
			जाओ out;
	पूर्ण

	/* Now see अगर we want to update the new state. */
	अगर (ssptr) अणु
		अक्षर *ss_sp;

		अगर (get_user(ss_sp, &ssptr->the_stack))
			जाओ out;
		/* If the current stack was set with sigaltstack, करोn't
		   swap stacks जबतक we are on it.  */
		ret = -EPERM;
		अगर (current->sas_ss_sp && on_sig_stack(sp))
			जाओ out;

		/* Since we करोn't know the extent of the stack, and we don't
		   track onstack-ness, but rather calculate it, we must
		   presume a size.  Ho hum this पूर्णांकerface is lossy.  */
		current->sas_ss_sp = (अचिन्हित दीर्घ)ss_sp - SIGSTKSZ;
		current->sas_ss_size = SIGSTKSZ;
	पूर्ण
	ret = 0;
out:
	वापस ret;
पूर्ण
