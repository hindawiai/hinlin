<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/kernel/संकेत.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 *
 *  1997-11-02  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tty.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/bitops.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/tracehook.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/ucontext.h>

#समावेश "proto.h"


#घोषणा DEBUG_SIG 0

#घोषणा _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))

यंत्रlinkage व्योम ret_from_sys_call(व्योम);

/*
 * The OSF/1 sigprocmask calling sequence is dअगरferent from the
 * C sigprocmask() sequence..
 */
SYSCALL_DEFINE2(osf_sigprocmask, पूर्णांक, how, अचिन्हित दीर्घ, newmask)
अणु
	sigset_t oldmask;
	sigset_t mask;
	अचिन्हित दीर्घ res;

	siginitset(&mask, newmask & _BLOCKABLE);
	res = sigprocmask(how, &mask, &oldmask);
	अगर (!res) अणु
		क्रमce_successful_syscall_वापस();
		res = oldmask.sig[0];
	पूर्ण
	वापस res;
पूर्ण

SYSCALL_DEFINE3(osf_sigaction, पूर्णांक, sig,
		स्थिर काष्ठा osf_sigaction __user *, act,
		काष्ठा osf_sigaction __user *, oact)
अणु
	काष्ठा k_sigaction new_ka, old_ka;
	पूर्णांक ret;

	अगर (act) अणु
		old_sigset_t mask;
		अगर (!access_ok(act, माप(*act)) ||
		    __get_user(new_ka.sa.sa_handler, &act->sa_handler) ||
		    __get_user(new_ka.sa.sa_flags, &act->sa_flags) ||
		    __get_user(mask, &act->sa_mask))
			वापस -EFAULT;
		siginitset(&new_ka.sa.sa_mask, mask);
		new_ka.ka_restorer = शून्य;
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);

	अगर (!ret && oact) अणु
		अगर (!access_ok(oact, माप(*oact)) ||
		    __put_user(old_ka.sa.sa_handler, &oact->sa_handler) ||
		    __put_user(old_ka.sa.sa_flags, &oact->sa_flags) ||
		    __put_user(old_ka.sa.sa_mask.sig[0], &oact->sa_mask))
			वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE5(rt_sigaction, पूर्णांक, sig, स्थिर काष्ठा sigaction __user *, act,
		काष्ठा sigaction __user *, oact,
		माप_प्रकार, sigsetsize, व्योम __user *, restorer)
अणु
	काष्ठा k_sigaction new_ka, old_ka;
	पूर्णांक ret;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (act) अणु
		new_ka.ka_restorer = restorer;
		अगर (copy_from_user(&new_ka.sa, act, माप(*act)))
			वापस -EFAULT;
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);

	अगर (!ret && oact) अणु
		अगर (copy_to_user(oact, &old_ka.sa, माप(*oact)))
			वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 */

#अगर _NSIG_WORDS > 1
# error "Non SA_SIGINFO frame needs rearranging"
#पूर्ण_अगर

काष्ठा sigframe
अणु
	काष्ठा sigcontext sc;
	अचिन्हित पूर्णांक retcode[3];
पूर्ण;

काष्ठा rt_sigframe
अणु
	काष्ठा siginfo info;
	काष्ठा ucontext uc;
	अचिन्हित पूर्णांक retcode[3];
पूर्ण;

/* If this changes, userland unwinders that Know Things about our संकेत
   frame will अवरोध.  Do not undertake lightly.  It also implies an ABI
   change wrt the size of siginfo_t, which may cause some pain.  */
बाह्य अक्षर compile_समय_निश्चित
        [दुरत्व(काष्ठा rt_sigframe, uc.uc_mcontext) == 176 ? 1 : -1];

#घोषणा INSN_MOV_R30_R16	0x47fe0410
#घोषणा INSN_LDI_R0		0x201f0000
#घोषणा INSN_CALLSYS		0x00000083

अटल दीर्घ
restore_sigcontext(काष्ठा sigcontext __user *sc, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ usp;
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)regs - 1;
	दीर्घ i, err = __get_user(regs->pc, &sc->sc_pc);

	current->restart_block.fn = करो_no_restart_syscall;

	sw->r26 = (अचिन्हित दीर्घ) ret_from_sys_call;

	err |= __get_user(regs->r0, sc->sc_regs+0);
	err |= __get_user(regs->r1, sc->sc_regs+1);
	err |= __get_user(regs->r2, sc->sc_regs+2);
	err |= __get_user(regs->r3, sc->sc_regs+3);
	err |= __get_user(regs->r4, sc->sc_regs+4);
	err |= __get_user(regs->r5, sc->sc_regs+5);
	err |= __get_user(regs->r6, sc->sc_regs+6);
	err |= __get_user(regs->r7, sc->sc_regs+7);
	err |= __get_user(regs->r8, sc->sc_regs+8);
	err |= __get_user(sw->r9, sc->sc_regs+9);
	err |= __get_user(sw->r10, sc->sc_regs+10);
	err |= __get_user(sw->r11, sc->sc_regs+11);
	err |= __get_user(sw->r12, sc->sc_regs+12);
	err |= __get_user(sw->r13, sc->sc_regs+13);
	err |= __get_user(sw->r14, sc->sc_regs+14);
	err |= __get_user(sw->r15, sc->sc_regs+15);
	err |= __get_user(regs->r16, sc->sc_regs+16);
	err |= __get_user(regs->r17, sc->sc_regs+17);
	err |= __get_user(regs->r18, sc->sc_regs+18);
	err |= __get_user(regs->r19, sc->sc_regs+19);
	err |= __get_user(regs->r20, sc->sc_regs+20);
	err |= __get_user(regs->r21, sc->sc_regs+21);
	err |= __get_user(regs->r22, sc->sc_regs+22);
	err |= __get_user(regs->r23, sc->sc_regs+23);
	err |= __get_user(regs->r24, sc->sc_regs+24);
	err |= __get_user(regs->r25, sc->sc_regs+25);
	err |= __get_user(regs->r26, sc->sc_regs+26);
	err |= __get_user(regs->r27, sc->sc_regs+27);
	err |= __get_user(regs->r28, sc->sc_regs+28);
	err |= __get_user(regs->gp, sc->sc_regs+29);
	err |= __get_user(usp, sc->sc_regs+30);
	wrusp(usp);

	क्रम (i = 0; i < 31; i++)
		err |= __get_user(sw->fp[i], sc->sc_fpregs+i);
	err |= __get_user(sw->fp[31], &sc->sc_fpcr);

	वापस err;
पूर्ण

/* Note that this syscall is also used by setcontext(3) to install
   a given sigcontext.  This because it's impossible to set *all*
   रेजिस्टरs and transfer control from userland.  */

यंत्रlinkage व्योम
करो_sigवापस(काष्ठा sigcontext __user *sc)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	sigset_t set;

	/* Verअगरy that it's a good sigcontext beक्रमe using it */
	अगर (!access_ok(sc, माप(*sc)))
		जाओ give_sigsegv;
	अगर (__get_user(set.sig[0], &sc->sc_mask))
		जाओ give_sigsegv;

	set_current_blocked(&set);

	अगर (restore_sigcontext(sc, regs))
		जाओ give_sigsegv;

	/* Send SIGTRAP अगर we're single-stepping: */
	अगर (ptrace_cancel_bpt (current)) अणु
		send_sig_fault(SIGTRAP, TRAP_BRKPT, (व्योम __user *) regs->pc, 0,
			       current);
	पूर्ण
	वापस;

give_sigsegv:
	क्रमce_sig(संक_अंश);
पूर्ण

यंत्रlinkage व्योम
करो_rt_sigवापस(काष्ठा rt_sigframe __user *frame)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	sigset_t set;

	/* Verअगरy that it's a good ucontext_t beक्रमe using it */
	अगर (!access_ok(&frame->uc, माप(frame->uc)))
		जाओ give_sigsegv;
	अगर (__copy_from_user(&set, &frame->uc.uc_sigmask, माप(set)))
		जाओ give_sigsegv;

	set_current_blocked(&set);

	अगर (restore_sigcontext(&frame->uc.uc_mcontext, regs))
		जाओ give_sigsegv;

	/* Send SIGTRAP अगर we're single-stepping: */
	अगर (ptrace_cancel_bpt (current)) अणु
		send_sig_fault(SIGTRAP, TRAP_BRKPT, (व्योम __user *) regs->pc, 0,
			       current);
	पूर्ण
	वापस;

give_sigsegv:
	क्रमce_sig(संक_अंश);
पूर्ण


/*
 * Set up a संकेत frame.
 */

अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा kसंकेत *ksig, अचिन्हित दीर्घ sp, माप_प्रकार frame_size)
अणु
	वापस (व्योम __user *)((sigsp(sp, ksig) - frame_size) & -32ul);
पूर्ण

अटल दीर्घ
setup_sigcontext(काष्ठा sigcontext __user *sc, काष्ठा pt_regs *regs, 
		 अचिन्हित दीर्घ mask, अचिन्हित दीर्घ sp)
अणु
	काष्ठा चयन_stack *sw = (काष्ठा चयन_stack *)regs - 1;
	दीर्घ i, err = 0;

	err |= __put_user(on_sig_stack((अचिन्हित दीर्घ)sc), &sc->sc_onstack);
	err |= __put_user(mask, &sc->sc_mask);
	err |= __put_user(regs->pc, &sc->sc_pc);
	err |= __put_user(8, &sc->sc_ps);

	err |= __put_user(regs->r0 , sc->sc_regs+0);
	err |= __put_user(regs->r1 , sc->sc_regs+1);
	err |= __put_user(regs->r2 , sc->sc_regs+2);
	err |= __put_user(regs->r3 , sc->sc_regs+3);
	err |= __put_user(regs->r4 , sc->sc_regs+4);
	err |= __put_user(regs->r5 , sc->sc_regs+5);
	err |= __put_user(regs->r6 , sc->sc_regs+6);
	err |= __put_user(regs->r7 , sc->sc_regs+7);
	err |= __put_user(regs->r8 , sc->sc_regs+8);
	err |= __put_user(sw->r9   , sc->sc_regs+9);
	err |= __put_user(sw->r10  , sc->sc_regs+10);
	err |= __put_user(sw->r11  , sc->sc_regs+11);
	err |= __put_user(sw->r12  , sc->sc_regs+12);
	err |= __put_user(sw->r13  , sc->sc_regs+13);
	err |= __put_user(sw->r14  , sc->sc_regs+14);
	err |= __put_user(sw->r15  , sc->sc_regs+15);
	err |= __put_user(regs->r16, sc->sc_regs+16);
	err |= __put_user(regs->r17, sc->sc_regs+17);
	err |= __put_user(regs->r18, sc->sc_regs+18);
	err |= __put_user(regs->r19, sc->sc_regs+19);
	err |= __put_user(regs->r20, sc->sc_regs+20);
	err |= __put_user(regs->r21, sc->sc_regs+21);
	err |= __put_user(regs->r22, sc->sc_regs+22);
	err |= __put_user(regs->r23, sc->sc_regs+23);
	err |= __put_user(regs->r24, sc->sc_regs+24);
	err |= __put_user(regs->r25, sc->sc_regs+25);
	err |= __put_user(regs->r26, sc->sc_regs+26);
	err |= __put_user(regs->r27, sc->sc_regs+27);
	err |= __put_user(regs->r28, sc->sc_regs+28);
	err |= __put_user(regs->gp , sc->sc_regs+29);
	err |= __put_user(sp, sc->sc_regs+30);
	err |= __put_user(0, sc->sc_regs+31);

	क्रम (i = 0; i < 31; i++)
		err |= __put_user(sw->fp[i], sc->sc_fpregs+i);
	err |= __put_user(0, sc->sc_fpregs+31);
	err |= __put_user(sw->fp[31], &sc->sc_fpcr);

	err |= __put_user(regs->trap_a0, &sc->sc_traparg_a0);
	err |= __put_user(regs->trap_a1, &sc->sc_traparg_a1);
	err |= __put_user(regs->trap_a2, &sc->sc_traparg_a2);

	वापस err;
पूर्ण

अटल पूर्णांक
setup_frame(काष्ठा kसंकेत *ksig, sigset_t *set, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ oldsp, r26, err = 0;
	काष्ठा sigframe __user *frame;

	oldsp = rdusp();
	frame = get_sigframe(ksig, oldsp, माप(*frame));
	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	err |= setup_sigcontext(&frame->sc, regs, set->sig[0], oldsp);
	अगर (err)
		वापस -EFAULT;

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	r26 = (अचिन्हित दीर्घ) ksig->ka.ka_restorer;
	अगर (!r26) अणु
		err |= __put_user(INSN_MOV_R30_R16, frame->retcode+0);
		err |= __put_user(INSN_LDI_R0+__NR_sigवापस, frame->retcode+1);
		err |= __put_user(INSN_CALLSYS, frame->retcode+2);
		imb();
		r26 = (अचिन्हित दीर्घ) frame->retcode;
	पूर्ण

	/* Check that everything was written properly.  */
	अगर (err)
		वापस err;

	/* "Return" to the handler */
	regs->r26 = r26;
	regs->r27 = regs->pc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	regs->r16 = ksig->sig;			/* a0: संकेत number */
	regs->r17 = 0;				/* a1: exception code */
	regs->r18 = (अचिन्हित दीर्घ) &frame->sc;	/* a2: sigcontext poपूर्णांकer */
	wrusp((अचिन्हित दीर्घ) frame);
	
#अगर DEBUG_SIG
	prपूर्णांकk("SIG deliver (%s:%d): sp=%p pc=%p ra=%p\n",
		current->comm, current->pid, frame, regs->pc, regs->r26);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक
setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ oldsp, r26, err = 0;
	काष्ठा rt_sigframe __user *frame;

	oldsp = rdusp();
	frame = get_sigframe(ksig, oldsp, माप(*frame));
	अगर (!access_ok(frame, माप(*frame)))
		वापस -EFAULT;

	err |= copy_siginfo_to_user(&frame->info, &ksig->info);

	/* Create the ucontext.  */
	err |= __put_user(0, &frame->uc.uc_flags);
	err |= __put_user(0, &frame->uc.uc_link);
	err |= __put_user(set->sig[0], &frame->uc.uc_osf_sigmask);
	err |= __save_altstack(&frame->uc.uc_stack, oldsp);
	err |= setup_sigcontext(&frame->uc.uc_mcontext, regs, 
				set->sig[0], oldsp);
	err |= __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set));
	अगर (err)
		वापस -EFAULT;

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	r26 = (अचिन्हित दीर्घ) ksig->ka.ka_restorer;
	अगर (!r26) अणु
		err |= __put_user(INSN_MOV_R30_R16, frame->retcode+0);
		err |= __put_user(INSN_LDI_R0+__NR_rt_sigवापस,
				  frame->retcode+1);
		err |= __put_user(INSN_CALLSYS, frame->retcode+2);
		imb();
		r26 = (अचिन्हित दीर्घ) frame->retcode;
	पूर्ण

	अगर (err)
		वापस -EFAULT;

	/* "Return" to the handler */
	regs->r26 = r26;
	regs->r27 = regs->pc = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	regs->r16 = ksig->sig;			  /* a0: संकेत number */
	regs->r17 = (अचिन्हित दीर्घ) &frame->info; /* a1: siginfo poपूर्णांकer */
	regs->r18 = (अचिन्हित दीर्घ) &frame->uc;	  /* a2: ucontext poपूर्णांकer */
	wrusp((अचिन्हित दीर्घ) frame);

#अगर DEBUG_SIG
	prपूर्णांकk("SIG deliver (%s:%d): sp=%p pc=%p ra=%p\n",
		current->comm, current->pid, frame, regs->pc, regs->r26);
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 * OK, we're invoking a handler.
 */
अटल अंतरभूत व्योम
handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक ret;

	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		ret = setup_rt_frame(ksig, oldset, regs);
	अन्यथा
		ret = setup_frame(ksig, oldset, regs);

	संकेत_setup_करोne(ret, ksig, 0);
पूर्ण

अटल अंतरभूत व्योम
syscall_restart(अचिन्हित दीर्घ r0, अचिन्हित दीर्घ r19,
		काष्ठा pt_regs *regs, काष्ठा k_sigaction *ka)
अणु
	चयन (regs->r0) अणु
	हाल ERESTARTSYS:
		अगर (!(ka->sa.sa_flags & SA_RESTART)) अणु
		हाल ERESTARTNOHAND:
			regs->r0 = EINTR;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल ERESTARTNOINTR:
		regs->r0 = r0;	/* reset v0 and a3 and replay syscall */
		regs->r19 = r19;
		regs->pc -= 4;
		अवरोध;
	हाल ERESTART_RESTARTBLOCK:
		regs->r0 = EINTR;
		अवरोध;
	पूर्ण
पूर्ण


/*
 * Note that 'init' is a special process: it doesn't get signals it doesn't
 * want to handle. Thus you cannot समाप्त init even with a SIGKILL even by
 * mistake.
 *
 * Note that we go through the संकेतs twice: once to check the संकेतs that
 * the kernel can handle, and then we build all the user-level संकेत handling
 * stack-frames in one go after that.
 *
 * "r0" and "r19" are the रेजिस्टरs we need to restore क्रम प्रणाली call
 * restart. "r0" is also used as an indicator whether we can restart at
 * all (अगर we get here from anything but a syscall वापस, it will be 0)
 */
अटल व्योम
करो_संकेत(काष्ठा pt_regs *regs, अचिन्हित दीर्घ r0, अचिन्हित दीर्घ r19)
अणु
	अचिन्हित दीर्घ single_stepping = ptrace_cancel_bpt(current);
	काष्ठा kसंकेत ksig;

	/* This lets the debugger run, ... */
	अगर (get_संकेत(&ksig)) अणु
		/* ... so re-check the single stepping. */
		single_stepping |= ptrace_cancel_bpt(current);
		/* Whee!  Actually deliver the संकेत.  */
		अगर (r0)
			syscall_restart(r0, r19, regs, &ksig.ka);
		handle_संकेत(&ksig, regs);
	पूर्ण अन्यथा अणु
		single_stepping |= ptrace_cancel_bpt(current);
		अगर (r0) अणु
			चयन (regs->r0) अणु
			हाल ERESTARTNOHAND:
			हाल ERESTARTSYS:
			हाल ERESTARTNOINTR:
				/* Reset v0 and a3 and replay syscall.  */
				regs->r0 = r0;
				regs->r19 = r19;
				regs->pc -= 4;
				अवरोध;
			हाल ERESTART_RESTARTBLOCK:
				/* Set v0 to the restart_syscall and replay */
				regs->r0 = __NR_restart_syscall;
				regs->pc -= 4;
				अवरोध;
			पूर्ण
		पूर्ण
		restore_saved_sigmask();
	पूर्ण
	अगर (single_stepping)
		ptrace_set_bpt(current);	/* re-set अवरोधpoपूर्णांक */
पूर्ण

व्योम
करो_work_pending(काष्ठा pt_regs *regs, अचिन्हित दीर्घ thपढ़ो_flags,
		 अचिन्हित दीर्घ r0, अचिन्हित दीर्घ r19)
अणु
	करो अणु
		अगर (thपढ़ो_flags & _TIF_NEED_RESCHED) अणु
			schedule();
		पूर्ण अन्यथा अणु
			local_irq_enable();
			अगर (thपढ़ो_flags & (_TIF_SIGPENDING|_TIF_NOTIFY_SIGNAL)) अणु
				करो_संकेत(regs, r0, r19);
				r0 = 0;
			पूर्ण अन्यथा अणु
				tracehook_notअगरy_resume(regs);
			पूर्ण
		पूर्ण
		local_irq_disable();
		thपढ़ो_flags = current_thपढ़ो_info()->flags;
	पूर्ण जबतक (thपढ़ो_flags & _TIF_WORK_MASK);
पूर्ण
