<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Architecture-specअगरic संकेत handling support.
 *
 * Copyright (C) 1999-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * Derived from i386 and Alpha versions.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tty.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/unistd.h>
#समावेश <linux/रुको.h>

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/rse.h>
#समावेश <यंत्र/sigcontext.h>

#समावेश "sigframe.h"

#घोषणा DEBUG_SIG	0
#घोषणा STACK_ALIGN	16		/* minimal alignment क्रम stack poपूर्णांकer */

#अगर _NSIG_WORDS > 1
# define PUT_SIGSET(k,u)	__copy_to_user((u)->sig, (k)->sig, माप(sigset_t))
# define GET_SIGSET(k,u)	__copy_from_user((k)->sig, (u)->sig, माप(sigset_t))
#अन्यथा
# define PUT_SIGSET(k,u)	__put_user((k)->sig[0], &(u)->sig[0])
# define GET_SIGSET(k,u)	__get_user((k)->sig[0], &(u)->sig[0])
#पूर्ण_अगर

अटल दीर्घ
restore_sigcontext (काष्ठा sigcontext __user *sc, काष्ठा sigscratch *scr)
अणु
	अचिन्हित दीर्घ ip, flags, nat, um, cfm, rsc;
	दीर्घ err;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/* restore scratch that always needs माला_लो updated during संकेत delivery: */
	err  = __get_user(flags, &sc->sc_flags);
	err |= __get_user(nat, &sc->sc_nat);
	err |= __get_user(ip, &sc->sc_ip);			/* inकाष्ठाion poपूर्णांकer */
	err |= __get_user(cfm, &sc->sc_cfm);
	err |= __get_user(um, &sc->sc_um);			/* user mask */
	err |= __get_user(rsc, &sc->sc_ar_rsc);
	err |= __get_user(scr->pt.ar_unat, &sc->sc_ar_unat);
	err |= __get_user(scr->pt.ar_fpsr, &sc->sc_ar_fpsr);
	err |= __get_user(scr->pt.ar_pfs, &sc->sc_ar_pfs);
	err |= __get_user(scr->pt.pr, &sc->sc_pr);		/* predicates */
	err |= __get_user(scr->pt.b0, &sc->sc_br[0]);		/* b0 (rp) */
	err |= __get_user(scr->pt.b6, &sc->sc_br[6]);		/* b6 */
	err |= __copy_from_user(&scr->pt.r1, &sc->sc_gr[1], 8);	/* r1 */
	err |= __copy_from_user(&scr->pt.r8, &sc->sc_gr[8], 4*8);	/* r8-r11 */
	err |= __copy_from_user(&scr->pt.r12, &sc->sc_gr[12], 2*8);	/* r12-r13 */
	err |= __copy_from_user(&scr->pt.r15, &sc->sc_gr[15], 8);	/* r15 */

	scr->pt.cr_अगरs = cfm | (1UL << 63);
	scr->pt.ar_rsc = rsc | (3 << 2); /* क्रमce PL3 */

	/* establish new inकाष्ठाion poपूर्णांकer: */
	scr->pt.cr_iip = ip & ~0x3UL;
	ia64_psr(&scr->pt)->ri = ip & 0x3;
	scr->pt.cr_ipsr = (scr->pt.cr_ipsr & ~IA64_PSR_UM) | (um & IA64_PSR_UM);

	scr->scratch_unat = ia64_put_scratch_nat_bits(&scr->pt, nat);

	अगर (!(flags & IA64_SC_FLAG_IN_SYSCALL)) अणु
		/* Restore most scratch-state only when not in syscall. */
		err |= __get_user(scr->pt.ar_ccv, &sc->sc_ar_ccv);		/* ar.ccv */
		err |= __get_user(scr->pt.b7, &sc->sc_br[7]);			/* b7 */
		err |= __get_user(scr->pt.r14, &sc->sc_gr[14]);			/* r14 */
		err |= __copy_from_user(&scr->pt.ar_csd, &sc->sc_ar25, 2*8); /* ar.csd & ar.ssd */
		err |= __copy_from_user(&scr->pt.r2, &sc->sc_gr[2], 2*8);	/* r2-r3 */
		err |= __copy_from_user(&scr->pt.r16, &sc->sc_gr[16], 16*8);	/* r16-r31 */
	पूर्ण

	अगर ((flags & IA64_SC_FLAG_FPH_VALID) != 0) अणु
		काष्ठा ia64_psr *psr = ia64_psr(&scr->pt);

		err |= __copy_from_user(current->thपढ़ो.fph, &sc->sc_fr[32], 96*16);
		psr->mfh = 0;	/* drop संकेत handler's fph contents... */
		preempt_disable();
		अगर (psr->dfh)
			ia64_drop_fpu(current);
		अन्यथा अणु
			/* We alपढ़ोy own the local fph, otherwise psr->dfh wouldn't be 0.  */
			__ia64_load_fpu(current->thपढ़ो.fph);
			ia64_set_local_fpu_owner(current);
		पूर्ण
		preempt_enable();
	पूर्ण
	वापस err;
पूर्ण

दीर्घ
ia64_rt_sigवापस (काष्ठा sigscratch *scr)
अणु
	बाह्य अक्षर ia64_strace_leave_kernel, ia64_leave_kernel;
	काष्ठा sigcontext __user *sc;
	sigset_t set;
	दीर्घ retval;

	sc = &((काष्ठा sigframe __user *) (scr->pt.r12 + 16))->sc;

	/*
	 * When we वापस to the previously executing context, r8 and r10 have alपढ़ोy
	 * been setup the way we want them.  Indeed, अगर the संकेत wasn't delivered जबतक
	 * in a प्रणाली call, we must not touch r8 or r10 as otherwise user-level state
	 * could be corrupted.
	 */
	retval = (दीर्घ) &ia64_leave_kernel;
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE)
	    || test_thपढ़ो_flag(TIF_SYSCALL_AUDIT))
		/*
		 * strace expects to be notअगरied after sigवापस वापसs even though the
		 * context to which we वापस may not be in the middle of a syscall.
		 * Thus, the वापस-value that strace displays क्रम sigवापस is
		 * meaningless.
		 */
		retval = (दीर्घ) &ia64_strace_leave_kernel;

	अगर (!access_ok(sc, माप(*sc)))
		जाओ give_sigsegv;

	अगर (GET_SIGSET(&set, &sc->sc_mask))
		जाओ give_sigsegv;

	set_current_blocked(&set);

	अगर (restore_sigcontext(sc, scr))
		जाओ give_sigsegv;

#अगर DEBUG_SIG
	prपूर्णांकk("SIG return (%s:%d): sp=%lx ip=%lx\n",
	       current->comm, current->pid, scr->pt.r12, scr->pt.cr_iip);
#पूर्ण_अगर
	अगर (restore_altstack(&sc->sc_stack))
		जाओ give_sigsegv;
	वापस retval;

  give_sigsegv:
	क्रमce_sig(संक_अंश);
	वापस retval;
पूर्ण

/*
 * This करोes just the minimum required setup of sigcontext.
 * Specअगरically, it only installs data that is either not knowable at
 * the user-level or that माला_लो modअगरied beक्रमe execution in the
 * trampoline starts.  Everything अन्यथा is करोne at the user-level.
 */
अटल दीर्घ
setup_sigcontext (काष्ठा sigcontext __user *sc, sigset_t *mask, काष्ठा sigscratch *scr)
अणु
	अचिन्हित दीर्घ flags = 0, अगरs, cfm, nat;
	दीर्घ err = 0;

	अगरs = scr->pt.cr_अगरs;

	अगर (on_sig_stack((अचिन्हित दीर्घ) sc))
		flags |= IA64_SC_FLAG_ONSTACK;
	अगर ((अगरs & (1UL << 63)) == 0)
		/* अगर cr_अगरs करोesn't have the valid bit set, we got here through a syscall */
		flags |= IA64_SC_FLAG_IN_SYSCALL;
	cfm = अगरs & ((1UL << 38) - 1);
	ia64_flush_fph(current);
	अगर ((current->thपढ़ो.flags & IA64_THREAD_FPH_VALID)) अणु
		flags |= IA64_SC_FLAG_FPH_VALID;
		err = __copy_to_user(&sc->sc_fr[32], current->thपढ़ो.fph, 96*16);
	पूर्ण

	nat = ia64_get_scratch_nat_bits(&scr->pt, scr->scratch_unat);

	err |= __put_user(flags, &sc->sc_flags);
	err |= __put_user(nat, &sc->sc_nat);
	err |= PUT_SIGSET(mask, &sc->sc_mask);
	err |= __put_user(cfm, &sc->sc_cfm);
	err |= __put_user(scr->pt.cr_ipsr & IA64_PSR_UM, &sc->sc_um);
	err |= __put_user(scr->pt.ar_rsc, &sc->sc_ar_rsc);
	err |= __put_user(scr->pt.ar_unat, &sc->sc_ar_unat);		/* ar.unat */
	err |= __put_user(scr->pt.ar_fpsr, &sc->sc_ar_fpsr);		/* ar.fpsr */
	err |= __put_user(scr->pt.ar_pfs, &sc->sc_ar_pfs);
	err |= __put_user(scr->pt.pr, &sc->sc_pr);			/* predicates */
	err |= __put_user(scr->pt.b0, &sc->sc_br[0]);			/* b0 (rp) */
	err |= __put_user(scr->pt.b6, &sc->sc_br[6]);			/* b6 */
	err |= __copy_to_user(&sc->sc_gr[1], &scr->pt.r1, 8);		/* r1 */
	err |= __copy_to_user(&sc->sc_gr[8], &scr->pt.r8, 4*8);		/* r8-r11 */
	err |= __copy_to_user(&sc->sc_gr[12], &scr->pt.r12, 2*8);	/* r12-r13 */
	err |= __copy_to_user(&sc->sc_gr[15], &scr->pt.r15, 8);		/* r15 */
	err |= __put_user(scr->pt.cr_iip + ia64_psr(&scr->pt)->ri, &sc->sc_ip);

	अगर (!(flags & IA64_SC_FLAG_IN_SYSCALL)) अणु
		/* Copy scratch regs to sigcontext अगर the संकेत didn't पूर्णांकerrupt a syscall. */
		err |= __put_user(scr->pt.ar_ccv, &sc->sc_ar_ccv);		/* ar.ccv */
		err |= __put_user(scr->pt.b7, &sc->sc_br[7]);			/* b7 */
		err |= __put_user(scr->pt.r14, &sc->sc_gr[14]);			/* r14 */
		err |= __copy_to_user(&sc->sc_ar25, &scr->pt.ar_csd, 2*8); /* ar.csd & ar.ssd */
		err |= __copy_to_user(&sc->sc_gr[2], &scr->pt.r2, 2*8);		/* r2-r3 */
		err |= __copy_to_user(&sc->sc_gr[16], &scr->pt.r16, 16*8);	/* r16-r31 */
	पूर्ण
	वापस err;
पूर्ण

/*
 * Check whether the रेजिस्टर-backing store is alपढ़ोy on the संकेत stack.
 */
अटल अंतरभूत पूर्णांक
rbs_on_sig_stack (अचिन्हित दीर्घ bsp)
अणु
	वापस (bsp - current->sas_ss_sp < current->sas_ss_size);
पूर्ण

अटल दीर्घ
setup_frame(काष्ठा kसंकेत *ksig, sigset_t *set, काष्ठा sigscratch *scr)
अणु
	बाह्य अक्षर __kernel_sigtramp[];
	अचिन्हित दीर्घ tramp_addr, new_rbs = 0, new_sp;
	काष्ठा sigframe __user *frame;
	दीर्घ err;

	new_sp = scr->pt.r12;
	tramp_addr = (अचिन्हित दीर्घ) __kernel_sigtramp;
	अगर (ksig->ka.sa.sa_flags & SA_ONSTACK) अणु
		पूर्णांक onstack = sas_ss_flags(new_sp);

		अगर (onstack == 0) अणु
			new_sp = current->sas_ss_sp + current->sas_ss_size;
			/*
			 * We need to check क्रम the रेजिस्टर stack being on the
			 * संकेत stack separately, because it's चयनed
			 * separately (memory stack is चयनed in the kernel,
			 * रेजिस्टर stack is चयनed in the संकेत trampoline).
			 */
			अगर (!rbs_on_sig_stack(scr->pt.ar_bspstore))
				new_rbs = ALIGN(current->sas_ss_sp,
						माप(दीर्घ));
		पूर्ण अन्यथा अगर (onstack == SS_ONSTACK) अणु
			अचिन्हित दीर्घ check_sp;

			/*
			 * If we are on the alternate संकेत stack and would
			 * overflow it, करोn't. Return an always-bogus address
			 * instead so we will die with संक_अंश.
			 */
			check_sp = (new_sp - माप(*frame)) & -STACK_ALIGN;
			अगर (!likely(on_sig_stack(check_sp))) अणु
				क्रमce_sigsegv(ksig->sig);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	frame = (व्योम __user *) ((new_sp - माप(*frame)) & -STACK_ALIGN);

	अगर (!access_ok(frame, माप(*frame))) अणु
		क्रमce_sigsegv(ksig->sig);
		वापस 1;
	पूर्ण

	err  = __put_user(ksig->sig, &frame->arg0);
	err |= __put_user(&frame->info, &frame->arg1);
	err |= __put_user(&frame->sc, &frame->arg2);
	err |= __put_user(new_rbs, &frame->sc.sc_rbs_base);
	err |= __put_user(0, &frame->sc.sc_loadrs);	/* initialize to zero */
	err |= __put_user(ksig->ka.sa.sa_handler, &frame->handler);

	err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	err |= __save_altstack(&frame->sc.sc_stack, scr->pt.r12);
	err |= setup_sigcontext(&frame->sc, set, scr);

	अगर (unlikely(err)) अणु
		क्रमce_sigsegv(ksig->sig);
		वापस 1;
	पूर्ण

	scr->pt.r12 = (अचिन्हित दीर्घ) frame - 16;	/* new stack poपूर्णांकer */
	scr->pt.ar_fpsr = FPSR_DEFAULT;			/* reset fpsr क्रम संकेत handler */
	scr->pt.cr_iip = tramp_addr;
	ia64_psr(&scr->pt)->ri = 0;			/* start executing in first slot */
	ia64_psr(&scr->pt)->be = 0;			/* क्रमce little-endian byte-order */
	/*
	 * Force the पूर्णांकerruption function mask to zero.  This has no effect when a
	 * प्रणाली-call got पूर्णांकerrupted by a संकेत (since, in that हाल, scr->pt_cr_अगरs is
	 * ignored), but it has the desirable effect of making it possible to deliver a
	 * संकेत with an incomplete रेजिस्टर frame (which happens when a mandatory RSE
	 * load faults).  Furthermore, it has no negative effect on the getting the user's
	 * dirty partition preserved, because that's governed by scr->pt.loadrs.
	 */
	scr->pt.cr_अगरs = (1UL << 63);

	/*
	 * Note: this affects only the NaT bits of the scratch regs (the ones saved in
	 * pt_regs), which is exactly what we want.
	 */
	scr->scratch_unat = 0; /* ensure NaT bits of r12 is clear */

#अगर DEBUG_SIG
	prपूर्णांकk("SIG deliver (%s:%d): sig=%d sp=%lx ip=%lx handler=%p\n",
	       current->comm, current->pid, ksig->sig, scr->pt.r12, frame->sc.sc_ip, frame->handler);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल दीर्घ
handle_संकेत (काष्ठा kसंकेत *ksig, काष्ठा sigscratch *scr)
अणु
	पूर्णांक ret = setup_frame(ksig, sigmask_to_save(), scr);

	अगर (!ret)
		संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLESTEP));

	वापस ret;
पूर्ण

/*
 * Note that `init' is a special process: it doesn't get signals it doesn't want to
 * handle.  Thus you cannot समाप्त init even with a SIGKILL even by mistake.
 */
व्योम
ia64_करो_संकेत (काष्ठा sigscratch *scr, दीर्घ in_syscall)
अणु
	दीर्घ restart = in_syscall;
	दीर्घ त्रुटि_सं = scr->pt.r8;
	काष्ठा kसंकेत ksig;

	/*
	 * This only loops in the rare हालs of handle_संकेत() failing, in which हाल we
	 * need to push through a क्रमced संक_अंश.
	 */
	जबतक (1) अणु
		अगर (!get_संकेत(&ksig))
			अवरोध;

		/*
		 * get_संकेत() may have run a debugger (via notअगरy_parent())
		 * and the debugger may have modअगरied the state (e.g., to arrange क्रम an
		 * inferior call), thus it's important to check क्रम restarting _after_
		 * get_संकेत().
		 */
		अगर ((दीर्घ) scr->pt.r10 != -1)
			/*
			 * A प्रणाली calls has to be restarted only अगर one of the error codes
			 * ERESTARTNOHAND, ERESTARTSYS, or ERESTARTNOINTR is वापसed.  If r10
			 * isn't -1 then r8 doesn't hold an error code and we don't need to
			 * restart the syscall, so we can clear the "restart" flag here.
			 */
			restart = 0;

		अगर (ksig.sig <= 0)
			अवरोध;

		अगर (unlikely(restart)) अणु
			चयन (त्रुटि_सं) अणु
			हाल ERESTART_RESTARTBLOCK:
			हाल ERESTARTNOHAND:
				scr->pt.r8 = EINTR;
				/* note: scr->pt.r10 is alपढ़ोy -1 */
				अवरोध;
			हाल ERESTARTSYS:
				अगर ((ksig.ka.sa.sa_flags & SA_RESTART) == 0) अणु
					scr->pt.r8 = EINTR;
					/* note: scr->pt.r10 is alपढ़ोy -1 */
					अवरोध;
				पूर्ण
				fallthrough;
			हाल ERESTARTNOINTR:
				ia64_decrement_ip(&scr->pt);
				restart = 0; /* करोn't restart twice अगर handle_संकेत() fails... */
			पूर्ण
		पूर्ण

		/*
		 * Whee!  Actually deliver the संकेत.  If the delivery failed, we need to
		 * जारी to iterate in this loop so we can deliver the संक_अंश...
		 */
		अगर (handle_संकेत(&ksig, scr))
			वापस;
	पूर्ण

	/* Did we come from a प्रणाली call? */
	अगर (restart) अणु
		/* Restart the प्रणाली call - no handlers present */
		अगर (त्रुटि_सं == ERESTARTNOHAND || त्रुटि_सं == ERESTARTSYS || त्रुटि_सं == ERESTARTNOINTR
		    || त्रुटि_सं == ERESTART_RESTARTBLOCK)
		अणु
			/*
			 * Note: the syscall number is in r15 which is saved in
			 * pt_regs so all we need to करो here is adjust ip so that
			 * the "break" inकाष्ठाion माला_लो re-executed.
			 */
			ia64_decrement_ip(&scr->pt);
			अगर (त्रुटि_सं == ERESTART_RESTARTBLOCK)
				scr->pt.r15 = __NR_restart_syscall;
		पूर्ण
	पूर्ण

	/* अगर there's no संकेत to deliver, we just put the saved sigmask
	 * back */
	restore_saved_sigmask();
पूर्ण
