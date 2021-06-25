<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  arch/sparc64/kernel/संकेत.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 1995, 2008 David S. Miller (davem@davemloft.net)
 *  Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)
 *  Copyright (C) 1997 Eddie C. Dost   (ecd@skynet.be)
 *  Copyright (C) 1997,1998 Jakub Jelinek   (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/unistd.h>
#समावेश <linux/mm.h>
#समावेश <linux/tty.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/bitops.h>
#समावेश <linux/context_tracking.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <यंत्र/uctx.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/visयंत्र.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "sigutil.h"
#समावेश "systbls.h"
#समावेश "kernel.h"
#समावेश "entry.h"

/* अणुset, getपूर्णcontext() needed क्रम 64-bit SparcLinux userland. */
यंत्रlinkage व्योम sparc64_set_context(काष्ठा pt_regs *regs)
अणु
	काष्ठा ucontext __user *ucp = (काष्ठा ucontext __user *)
		regs->u_regs[UREG_I0];
	क्रमागत ctx_state prev_state = exception_enter();
	mc_gregset_t __user *grp;
	अचिन्हित दीर्घ pc, npc, tstate;
	अचिन्हित दीर्घ fp, i7;
	अचिन्हित अक्षर fenab;
	पूर्णांक err;

	synchronize_user_stack();
	अगर (get_thपढ़ो_wsaved()					||
	    (((अचिन्हित दीर्घ)ucp) & (माप(अचिन्हित दीर्घ)-1))	||
	    (!__access_ok(ucp, माप(*ucp))))
		जाओ करो_sigsegv;
	grp  = &ucp->uc_mcontext.mc_gregs;
	err  = __get_user(pc, &((*grp)[MC_PC]));
	err |= __get_user(npc, &((*grp)[MC_NPC]));
	अगर (err || ((pc | npc) & 3))
		जाओ करो_sigsegv;
	अगर (regs->u_regs[UREG_I1]) अणु
		sigset_t set;

		अगर (_NSIG_WORDS == 1) अणु
			अगर (__get_user(set.sig[0], &ucp->uc_sigmask.sig[0]))
				जाओ करो_sigsegv;
		पूर्ण अन्यथा अणु
			अगर (__copy_from_user(&set, &ucp->uc_sigmask, माप(sigset_t)))
				जाओ करो_sigsegv;
		पूर्ण
		set_current_blocked(&set);
	पूर्ण
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		pc &= 0xffffffff;
		npc &= 0xffffffff;
	पूर्ण
	regs->tpc = pc;
	regs->tnpc = npc;
	err |= __get_user(regs->y, &((*grp)[MC_Y]));
	err |= __get_user(tstate, &((*grp)[MC_TSTATE]));
	regs->tstate &= ~(TSTATE_ASI | TSTATE_ICC | TSTATE_XCC);
	regs->tstate |= (tstate & (TSTATE_ASI | TSTATE_ICC | TSTATE_XCC));
	err |= __get_user(regs->u_regs[UREG_G1], (&(*grp)[MC_G1]));
	err |= __get_user(regs->u_regs[UREG_G2], (&(*grp)[MC_G2]));
	err |= __get_user(regs->u_regs[UREG_G3], (&(*grp)[MC_G3]));
	err |= __get_user(regs->u_regs[UREG_G4], (&(*grp)[MC_G4]));
	err |= __get_user(regs->u_regs[UREG_G5], (&(*grp)[MC_G5]));
	err |= __get_user(regs->u_regs[UREG_G6], (&(*grp)[MC_G6]));

	/* Skip %g7 as that's the thपढ़ो रेजिस्टर in userspace.  */

	err |= __get_user(regs->u_regs[UREG_I0], (&(*grp)[MC_O0]));
	err |= __get_user(regs->u_regs[UREG_I1], (&(*grp)[MC_O1]));
	err |= __get_user(regs->u_regs[UREG_I2], (&(*grp)[MC_O2]));
	err |= __get_user(regs->u_regs[UREG_I3], (&(*grp)[MC_O3]));
	err |= __get_user(regs->u_regs[UREG_I4], (&(*grp)[MC_O4]));
	err |= __get_user(regs->u_regs[UREG_I5], (&(*grp)[MC_O5]));
	err |= __get_user(regs->u_regs[UREG_I6], (&(*grp)[MC_O6]));
	err |= __get_user(regs->u_regs[UREG_I7], (&(*grp)[MC_O7]));

	err |= __get_user(fp, &(ucp->uc_mcontext.mc_fp));
	err |= __get_user(i7, &(ucp->uc_mcontext.mc_i7));
	err |= __put_user(fp,
	      (&(((काष्ठा reg_winकरोw __user *)(STACK_BIAS+regs->u_regs[UREG_I6]))->ins[6])));
	err |= __put_user(i7,
	      (&(((काष्ठा reg_winकरोw __user *)(STACK_BIAS+regs->u_regs[UREG_I6]))->ins[7])));

	err |= __get_user(fenab, &(ucp->uc_mcontext.mc_fpregs.mcfpu_enab));
	अगर (fenab) अणु
		अचिन्हित दीर्घ *fpregs = current_thपढ़ो_info()->fpregs;
		अचिन्हित दीर्घ fprs;
		
		fprs_ग_लिखो(0);
		err |= __get_user(fprs, &(ucp->uc_mcontext.mc_fpregs.mcfpu_fprs));
		अगर (fprs & FPRS_DL)
			err |= copy_from_user(fpregs,
					      &(ucp->uc_mcontext.mc_fpregs.mcfpu_fregs),
					      (माप(अचिन्हित पूर्णांक) * 32));
		अगर (fprs & FPRS_DU)
			err |= copy_from_user(fpregs+16,
			 ((अचिन्हित दीर्घ __user *)&(ucp->uc_mcontext.mc_fpregs.mcfpu_fregs))+16,
			 (माप(अचिन्हित पूर्णांक) * 32));
		err |= __get_user(current_thपढ़ो_info()->xfsr[0],
				  &(ucp->uc_mcontext.mc_fpregs.mcfpu_fsr));
		err |= __get_user(current_thपढ़ो_info()->gsr[0],
				  &(ucp->uc_mcontext.mc_fpregs.mcfpu_gsr));
		regs->tstate &= ~TSTATE_PEF;
	पूर्ण
	अगर (err)
		जाओ करो_sigsegv;
out:
	exception_निकास(prev_state);
	वापस;
करो_sigsegv:
	क्रमce_sig(संक_अंश);
	जाओ out;
पूर्ण

यंत्रlinkage व्योम sparc64_get_context(काष्ठा pt_regs *regs)
अणु
	काष्ठा ucontext __user *ucp = (काष्ठा ucontext __user *)
		regs->u_regs[UREG_I0];
	क्रमागत ctx_state prev_state = exception_enter();
	mc_gregset_t __user *grp;
	mcontext_t __user *mcp;
	अचिन्हित दीर्घ fp, i7;
	अचिन्हित अक्षर fenab;
	पूर्णांक err;

	synchronize_user_stack();
	अगर (get_thपढ़ो_wsaved() || clear_user(ucp, माप(*ucp)))
		जाओ करो_sigsegv;

#अगर 1
	fenab = 0; /* IMO get_context is like any other प्रणाली call, thus modअगरies FPU state -jj */
#अन्यथा
	fenab = (current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF);
#पूर्ण_अगर
		
	mcp = &ucp->uc_mcontext;
	grp = &mcp->mc_gregs;

	/* Skip over the trap inकाष्ठाion, first. */
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc   = (regs->tnpc & 0xffffffff);
		regs->tnpc  = (regs->tnpc + 4) & 0xffffffff;
	पूर्ण अन्यथा अणु
		regs->tpc   = regs->tnpc;
		regs->tnpc += 4;
	पूर्ण
	err = 0;
	अगर (_NSIG_WORDS == 1)
		err |= __put_user(current->blocked.sig[0],
				  (अचिन्हित दीर्घ __user *)&ucp->uc_sigmask);
	अन्यथा
		err |= __copy_to_user(&ucp->uc_sigmask, &current->blocked,
				      माप(sigset_t));

	err |= __put_user(regs->tstate, &((*grp)[MC_TSTATE]));
	err |= __put_user(regs->tpc, &((*grp)[MC_PC]));
	err |= __put_user(regs->tnpc, &((*grp)[MC_NPC]));
	err |= __put_user(regs->y, &((*grp)[MC_Y]));
	err |= __put_user(regs->u_regs[UREG_G1], &((*grp)[MC_G1]));
	err |= __put_user(regs->u_regs[UREG_G2], &((*grp)[MC_G2]));
	err |= __put_user(regs->u_regs[UREG_G3], &((*grp)[MC_G3]));
	err |= __put_user(regs->u_regs[UREG_G4], &((*grp)[MC_G4]));
	err |= __put_user(regs->u_regs[UREG_G5], &((*grp)[MC_G5]));
	err |= __put_user(regs->u_regs[UREG_G6], &((*grp)[MC_G6]));
	err |= __put_user(regs->u_regs[UREG_G7], &((*grp)[MC_G7]));
	err |= __put_user(regs->u_regs[UREG_I0], &((*grp)[MC_O0]));
	err |= __put_user(regs->u_regs[UREG_I1], &((*grp)[MC_O1]));
	err |= __put_user(regs->u_regs[UREG_I2], &((*grp)[MC_O2]));
	err |= __put_user(regs->u_regs[UREG_I3], &((*grp)[MC_O3]));
	err |= __put_user(regs->u_regs[UREG_I4], &((*grp)[MC_O4]));
	err |= __put_user(regs->u_regs[UREG_I5], &((*grp)[MC_O5]));
	err |= __put_user(regs->u_regs[UREG_I6], &((*grp)[MC_O6]));
	err |= __put_user(regs->u_regs[UREG_I7], &((*grp)[MC_O7]));

	err |= __get_user(fp,
		 (&(((काष्ठा reg_winकरोw __user *)(STACK_BIAS+regs->u_regs[UREG_I6]))->ins[6])));
	err |= __get_user(i7,
		 (&(((काष्ठा reg_winकरोw __user *)(STACK_BIAS+regs->u_regs[UREG_I6]))->ins[7])));
	err |= __put_user(fp, &(mcp->mc_fp));
	err |= __put_user(i7, &(mcp->mc_i7));

	err |= __put_user(fenab, &(mcp->mc_fpregs.mcfpu_enab));
	अगर (fenab) अणु
		अचिन्हित दीर्घ *fpregs = current_thपढ़ो_info()->fpregs;
		अचिन्हित दीर्घ fprs;
		
		fprs = current_thपढ़ो_info()->fpsaved[0];
		अगर (fprs & FPRS_DL)
			err |= copy_to_user(&(mcp->mc_fpregs.mcfpu_fregs), fpregs,
					    (माप(अचिन्हित पूर्णांक) * 32));
		अगर (fprs & FPRS_DU)
			err |= copy_to_user(
                          ((अचिन्हित दीर्घ __user *)&(mcp->mc_fpregs.mcfpu_fregs))+16, fpregs+16,
			  (माप(अचिन्हित पूर्णांक) * 32));
		err |= __put_user(current_thपढ़ो_info()->xfsr[0], &(mcp->mc_fpregs.mcfpu_fsr));
		err |= __put_user(current_thपढ़ो_info()->gsr[0], &(mcp->mc_fpregs.mcfpu_gsr));
		err |= __put_user(fprs, &(mcp->mc_fpregs.mcfpu_fprs));
	पूर्ण
	अगर (err)
		जाओ करो_sigsegv;
out:
	exception_निकास(prev_state);
	वापस;
करो_sigsegv:
	क्रमce_sig(संक_अंश);
	जाओ out;
पूर्ण

/* Checks अगर the fp is valid.  We always build rt संकेत frames which
 * are 16-byte aligned, thereक्रमe we can always enक्रमce that the
 * restore frame has that property as well.
 */
अटल bool invalid_frame_poपूर्णांकer(व्योम __user *fp)
अणु
	अगर (((अचिन्हित दीर्घ) fp) & 15)
		वापस true;
	वापस false;
पूर्ण

काष्ठा rt_संकेत_frame अणु
	काष्ठा sparc_stackf	ss;
	siginfo_t		info;
	काष्ठा pt_regs		regs;
	__siginfo_fpu_t __user	*fpu_save;
	stack_t			stack;
	sigset_t		mask;
	__siginfo_rwin_t	*rwin_save;
पूर्ण;

व्योम करो_rt_sigवापस(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ tpc, tnpc, tstate, ufp;
	काष्ठा rt_संकेत_frame __user *sf;
	__siginfo_fpu_t __user *fpu_save;
	__siginfo_rwin_t __user *rwin_save;
	sigset_t set;
	पूर्णांक err;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	synchronize_user_stack ();
	sf = (काष्ठा rt_संकेत_frame __user *)
		(regs->u_regs [UREG_FP] + STACK_BIAS);

	/* 1. Make sure we are not getting garbage from the user */
	अगर (invalid_frame_poपूर्णांकer(sf))
		जाओ segv;

	अगर (get_user(ufp, &sf->regs.u_regs[UREG_FP]))
		जाओ segv;

	अगर ((ufp + STACK_BIAS) & 0x7)
		जाओ segv;

	err = __get_user(tpc, &sf->regs.tpc);
	err |= __get_user(tnpc, &sf->regs.tnpc);
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		tpc &= 0xffffffff;
		tnpc &= 0xffffffff;
	पूर्ण
	err |= ((tpc | tnpc) & 3);

	/* 2. Restore the state */
	err |= __get_user(regs->y, &sf->regs.y);
	err |= __get_user(tstate, &sf->regs.tstate);
	err |= copy_from_user(regs->u_regs, sf->regs.u_regs, माप(regs->u_regs));

	/* User can only change condition codes and %asi in %tstate. */
	regs->tstate &= ~(TSTATE_ASI | TSTATE_ICC | TSTATE_XCC);
	regs->tstate |= (tstate & (TSTATE_ASI | TSTATE_ICC | TSTATE_XCC));

	err |= __get_user(fpu_save, &sf->fpu_save);
	अगर (!err && fpu_save)
		err |= restore_fpu_state(regs, fpu_save);

	err |= __copy_from_user(&set, &sf->mask, माप(sigset_t));
	err |= restore_altstack(&sf->stack);
	अगर (err)
		जाओ segv;

	err |= __get_user(rwin_save, &sf->rwin_save);
	अगर (!err && rwin_save) अणु
		अगर (restore_rwin_state(rwin_save))
			जाओ segv;
	पूर्ण

	regs->tpc = tpc;
	regs->tnpc = tnpc;

	/* Prevent syscall restart.  */
	pt_regs_clear_syscall(regs);

	set_current_blocked(&set);
	वापस;
segv:
	क्रमce_sig(संक_अंश);
पूर्ण

अटल अंतरभूत व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs, अचिन्हित दीर्घ framesize)
अणु
	अचिन्हित दीर्घ sp = regs->u_regs[UREG_FP] + STACK_BIAS;

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

अटल अंतरभूत पूर्णांक
setup_rt_frame(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_संकेत_frame __user *sf;
	पूर्णांक wsaved, err, sf_size;
	व्योम __user *tail;

	/* 1. Make sure everything is clean */
	synchronize_user_stack();
	save_and_clear_fpu();
	
	wsaved = get_thपढ़ो_wsaved();

	sf_size = माप(काष्ठा rt_संकेत_frame);
	अगर (current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF)
		sf_size += माप(__siginfo_fpu_t);
	अगर (wsaved)
		sf_size += माप(__siginfo_rwin_t);
	sf = (काष्ठा rt_संकेत_frame __user *)
		get_sigframe(ksig, regs, sf_size);

	अगर (invalid_frame_poपूर्णांकer (sf)) अणु
		अगर (show_unhandled_संकेतs)
			pr_info("%s[%d] bad frame in setup_rt_frame: %016lx TPC %016lx O7 %016lx\n",
				current->comm, current->pid, (अचिन्हित दीर्घ)sf,
				regs->tpc, regs->u_regs[UREG_I7]);
		क्रमce_sigsegv(ksig->sig);
		वापस -EINVAL;
	पूर्ण

	tail = (sf + 1);

	/* 2. Save the current process state */
	err = copy_to_user(&sf->regs, regs, माप (*regs));

	अगर (current_thपढ़ो_info()->fpsaved[0] & FPRS_FEF) अणु
		__siginfo_fpu_t __user *fpu_save = tail;
		tail += माप(__siginfo_fpu_t);
		err |= save_fpu_state(regs, fpu_save);
		err |= __put_user((u64)fpu_save, &sf->fpu_save);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->fpu_save);
	पूर्ण
	अगर (wsaved) अणु
		__siginfo_rwin_t __user *rwin_save = tail;
		tail += माप(__siginfo_rwin_t);
		err |= save_rwin_state(wsaved, rwin_save);
		err |= __put_user((u64)rwin_save, &sf->rwin_save);
		set_thपढ़ो_wsaved(0);
	पूर्ण अन्यथा अणु
		err |= __put_user(0, &sf->rwin_save);
	पूर्ण
	
	/* Setup sigaltstack */
	err |= __save_altstack(&sf->stack, regs->u_regs[UREG_FP]);

	err |= copy_to_user(&sf->mask, sigmask_to_save(), माप(sigset_t));

	अगर (!wsaved) अणु
		err |= copy_in_user((u64 __user *)sf,
				    (u64 __user *)(regs->u_regs[UREG_FP] +
						   STACK_BIAS),
				    माप(काष्ठा reg_winकरोw));
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw *rp;

		rp = &current_thपढ़ो_info()->reg_winकरोw[wsaved - 1];
		err |= copy_to_user(sf, rp, माप(काष्ठा reg_winकरोw));
	पूर्ण
	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		err |= copy_siginfo_to_user(&sf->info, &ksig->info);
	अन्यथा अणु
		err |= __put_user(ksig->sig, &sf->info.si_signo);
		err |= __put_user(SI_NOINFO, &sf->info.si_code);
	पूर्ण
	अगर (err)
		वापस err;
	
	/* 3. संकेत handler back-trampoline and parameters */
	regs->u_regs[UREG_FP] = ((अचिन्हित दीर्घ) sf) - STACK_BIAS;
	regs->u_regs[UREG_I0] = ksig->sig;
	regs->u_regs[UREG_I1] = (अचिन्हित दीर्घ) &sf->info;

	/* The sigcontext is passed in this way because of how it
	 * is defined in GLIBC's /usr/include/bits/sigcontext.h
	 * क्रम sparc64.  It includes the 128 bytes of siginfo_t.
	 */
	regs->u_regs[UREG_I2] = (अचिन्हित दीर्घ) &sf->info;

	/* 5. संकेत handler */
	regs->tpc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	regs->tnpc = (regs->tpc + 4);
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
	/* 4. वापस to kernel inकाष्ठाions */
	regs->u_regs[UREG_I7] = (अचिन्हित दीर्घ)ksig->ka.ka_restorer;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम syscall_restart(अचिन्हित दीर्घ orig_i0, काष्ठा pt_regs *regs,
				   काष्ठा sigaction *sa)
अणु
	चयन (regs->u_regs[UREG_I0]) अणु
	हाल ERESTART_RESTARTBLOCK:
	हाल ERESTARTNOHAND:
	no_प्रणाली_call_restart:
		regs->u_regs[UREG_I0] = EINTR;
		regs->tstate |= (TSTATE_ICARRY|TSTATE_XCARRY);
		अवरोध;
	हाल ERESTARTSYS:
		अगर (!(sa->sa_flags & SA_RESTART))
			जाओ no_प्रणाली_call_restart;
		fallthrough;
	हाल ERESTARTNOINTR:
		regs->u_regs[UREG_I0] = orig_i0;
		regs->tpc -= 4;
		regs->tnpc -= 4;
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
	अगर (pt_regs_is_syscall(regs) &&
	    (regs->tstate & (TSTATE_XCARRY | TSTATE_ICARRY)))
		regs->u_regs[UREG_G6] = orig_i0;

#अगर_घोषित CONFIG_COMPAT
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		करो_संकेत32(regs);
		वापस;
	पूर्ण
#पूर्ण_अगर	

	has_handler = get_संकेत(&ksig);

	restart_syscall = 0;
	अगर (pt_regs_is_syscall(regs) &&
	    (regs->tstate & (TSTATE_XCARRY | TSTATE_ICARRY))) अणु
		restart_syscall = 1;
		orig_i0 = regs->u_regs[UREG_G6];
	पूर्ण

	अगर (has_handler) अणु
		अगर (restart_syscall)
			syscall_restart(orig_i0, regs, &ksig.ka.sa);
		संकेत_setup_करोne(setup_rt_frame(&ksig, regs), &ksig, 0);
	पूर्ण अन्यथा अणु
		अगर (restart_syscall) अणु
			चयन (regs->u_regs[UREG_I0]) अणु
			हाल ERESTARTNOHAND:
	     		हाल ERESTARTSYS:
			हाल ERESTARTNOINTR:
				/* replay the प्रणाली call when we are करोne */
				regs->u_regs[UREG_I0] = orig_i0;
				regs->tpc -= 4;
				regs->tnpc -= 4;
				pt_regs_clear_syscall(regs);
				fallthrough;
			हाल ERESTART_RESTARTBLOCK:
				regs->u_regs[UREG_G1] = __NR_restart_syscall;
				regs->tpc -= 4;
				regs->tnpc -= 4;
				pt_regs_clear_syscall(regs);
			पूर्ण
		पूर्ण
		restore_saved_sigmask();
	पूर्ण
पूर्ण

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, अचिन्हित दीर्घ orig_i0, अचिन्हित दीर्घ thपढ़ो_info_flags)
अणु
	user_निकास();
	अगर (thपढ़ो_info_flags & _TIF_UPROBE)
		uprobe_notअगरy_resume(regs);
	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs, orig_i0);
	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME)
		tracehook_notअगरy_resume(regs);
	user_enter();
पूर्ण

