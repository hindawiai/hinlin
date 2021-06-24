<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 1999, 2006
 *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)
 *
 *    Based on Intel version
 * 
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  1997-11-28  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/entry-common.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tty.h>
#समावेश <linux/personality.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/compat.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश "entry.h"

/*
 * Layout of an old-style संकेत-frame:
 *	-----------------------------------------
 *	| save area (_SIGNAL_FRAMESIZE)		|
 *	-----------------------------------------
 *	| काष्ठा sigcontext			|
 *	|	oldmask				|
 *	|	_sigregs *			|
 *	-----------------------------------------
 *	| _sigregs with				|
 *	|	_s390_regs_common		|
 *	|	_s390_fp_regs			|
 *	-----------------------------------------
 *	| पूर्णांक signo				|
 *	-----------------------------------------
 *	| _sigregs_ext with			|
 *	|	gprs_high 64 byte (opt)		|
 *	|	vxrs_low 128 byte (opt)		|
 *	|	vxrs_high 256 byte (opt)	|
 *	|	reserved 128 byte (opt)		|
 *	-----------------------------------------
 *	| __u16 svc_insn			|
 *	-----------------------------------------
 * The svc_insn entry with the sigवापस प्रणाली call opcode करोes not
 * have a fixed position and moves अगर gprs_high or vxrs exist.
 * Future extensions will be added to _sigregs_ext.
 */
काष्ठा sigframe
अणु
	__u8 callee_used_stack[__SIGNAL_FRAMESIZE];
	काष्ठा sigcontext sc;
	_sigregs sregs;
	पूर्णांक signo;
	_sigregs_ext sregs_ext;
	__u16 svc_insn;		/* Offset of svc_insn is NOT fixed! */
पूर्ण;

/*
 * Layout of an rt संकेत-frame:
 *	-----------------------------------------
 *	| save area (_SIGNAL_FRAMESIZE)		|
 *	-----------------------------------------
 *	| svc __NR_rt_sigवापस 2 byte		|
 *	-----------------------------------------
 *	| काष्ठा siginfo			|
 *	-----------------------------------------
 *	| काष्ठा ucontext_extended with		|
 *	|	अचिन्हित दीर्घ uc_flags		|
 *	|	काष्ठा ucontext *uc_link	|
 *	|	stack_t uc_stack		|
 *	|	_sigregs uc_mcontext with	|
 *	|		_s390_regs_common	|
 *	|		_s390_fp_regs		|
 *	|	sigset_t uc_sigmask		|
 *	|	_sigregs_ext uc_mcontext_ext	|
 *	|		gprs_high 64 byte (opt)	|
 *	|		vxrs_low 128 byte (opt)	|
 *	|		vxrs_high 256 byte (opt)|
 *	|		reserved 128 byte (opt)	|
 *	-----------------------------------------
 * Future extensions will be added to _sigregs_ext.
 */
काष्ठा rt_sigframe
अणु
	__u8 callee_used_stack[__SIGNAL_FRAMESIZE];
	__u16 svc_insn;
	काष्ठा siginfo info;
	काष्ठा ucontext_extended uc;
पूर्ण;

/* Store रेजिस्टरs needed to create the संकेत frame */
अटल व्योम store_sigregs(व्योम)
अणु
	save_access_regs(current->thपढ़ो.acrs);
	save_fpu_regs();
पूर्ण

/* Load रेजिस्टरs after संकेत वापस */
अटल व्योम load_sigregs(व्योम)
अणु
	restore_access_regs(current->thपढ़ो.acrs);
पूर्ण

/* Returns non-zero on fault. */
अटल पूर्णांक save_sigregs(काष्ठा pt_regs *regs, _sigregs __user *sregs)
अणु
	_sigregs user_sregs;

	/* Copy a 'clean' PSW mask to the user to aव्योम leaking
	   inक्रमmation about whether PER is currently on.  */
	user_sregs.regs.psw.mask = PSW_USER_BITS |
		(regs->psw.mask & (PSW_MASK_USER | PSW_MASK_RI));
	user_sregs.regs.psw.addr = regs->psw.addr;
	स_नकल(&user_sregs.regs.gprs, &regs->gprs, माप(sregs->regs.gprs));
	स_नकल(&user_sregs.regs.acrs, current->thपढ़ो.acrs,
	       माप(user_sregs.regs.acrs));
	fpregs_store(&user_sregs.fpregs, &current->thपढ़ो.fpu);
	अगर (__copy_to_user(sregs, &user_sregs, माप(_sigregs)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक restore_sigregs(काष्ठा pt_regs *regs, _sigregs __user *sregs)
अणु
	_sigregs user_sregs;

	/* Alwys make any pending restarted प्रणाली call वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (__copy_from_user(&user_sregs, sregs, माप(user_sregs)))
		वापस -EFAULT;

	अगर (!is_ri_task(current) && (user_sregs.regs.psw.mask & PSW_MASK_RI))
		वापस -EINVAL;

	/* Test the भग्नing-poपूर्णांक-control word. */
	अगर (test_fp_ctl(user_sregs.fpregs.fpc))
		वापस -EINVAL;

	/* Use regs->psw.mask instead of PSW_USER_BITS to preserve PER bit. */
	regs->psw.mask = (regs->psw.mask & ~(PSW_MASK_USER | PSW_MASK_RI)) |
		(user_sregs.regs.psw.mask & (PSW_MASK_USER | PSW_MASK_RI));
	/* Check क्रम invalid user address space control. */
	अगर ((regs->psw.mask & PSW_MASK_ASC) == PSW_ASC_HOME)
		regs->psw.mask = PSW_ASC_PRIMARY |
			(regs->psw.mask & ~PSW_MASK_ASC);
	/* Check क्रम invalid amode */
	अगर (regs->psw.mask & PSW_MASK_EA)
		regs->psw.mask |= PSW_MASK_BA;
	regs->psw.addr = user_sregs.regs.psw.addr;
	स_नकल(&regs->gprs, &user_sregs.regs.gprs, माप(sregs->regs.gprs));
	स_नकल(&current->thपढ़ो.acrs, &user_sregs.regs.acrs,
	       माप(current->thपढ़ो.acrs));

	fpregs_load(&user_sregs.fpregs, &current->thपढ़ो.fpu);

	clear_pt_regs_flag(regs, PIF_SYSCALL); /* No दीर्घer in a प्रणाली call */
	clear_pt_regs_flag(regs, PIF_SYSCALL_RESTART);
	वापस 0;
पूर्ण

/* Returns non-zero on fault. */
अटल पूर्णांक save_sigregs_ext(काष्ठा pt_regs *regs,
			    _sigregs_ext __user *sregs_ext)
अणु
	__u64 vxrs[__NUM_VXRS_LOW];
	पूर्णांक i;

	/* Save vector रेजिस्टरs to संकेत stack */
	अगर (MACHINE_HAS_VX) अणु
		क्रम (i = 0; i < __NUM_VXRS_LOW; i++)
			vxrs[i] = *((__u64 *)(current->thपढ़ो.fpu.vxrs + i) + 1);
		अगर (__copy_to_user(&sregs_ext->vxrs_low, vxrs,
				   माप(sregs_ext->vxrs_low)) ||
		    __copy_to_user(&sregs_ext->vxrs_high,
				   current->thपढ़ो.fpu.vxrs + __NUM_VXRS_LOW,
				   माप(sregs_ext->vxrs_high)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक restore_sigregs_ext(काष्ठा pt_regs *regs,
			       _sigregs_ext __user *sregs_ext)
अणु
	__u64 vxrs[__NUM_VXRS_LOW];
	पूर्णांक i;

	/* Restore vector रेजिस्टरs from संकेत stack */
	अगर (MACHINE_HAS_VX) अणु
		अगर (__copy_from_user(vxrs, &sregs_ext->vxrs_low,
				     माप(sregs_ext->vxrs_low)) ||
		    __copy_from_user(current->thपढ़ो.fpu.vxrs + __NUM_VXRS_LOW,
				     &sregs_ext->vxrs_high,
				     माप(sregs_ext->vxrs_high)))
			वापस -EFAULT;
		क्रम (i = 0; i < __NUM_VXRS_LOW; i++)
			*((__u64 *)(current->thपढ़ो.fpu.vxrs + i) + 1) = vxrs[i];
	पूर्ण
	वापस 0;
पूर्ण

SYSCALL_DEFINE0(sigवापस)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(current);
	काष्ठा sigframe __user *frame =
		(काष्ठा sigframe __user *) regs->gprs[15];
	sigset_t set;

	अगर (__copy_from_user(&set.sig, &frame->sc.oldmask, _SIGMASK_COPY_SIZE))
		जाओ badframe;
	set_current_blocked(&set);
	save_fpu_regs();
	अगर (restore_sigregs(regs, &frame->sregs))
		जाओ badframe;
	अगर (restore_sigregs_ext(regs, &frame->sregs_ext))
		जाओ badframe;
	load_sigregs();
	वापस regs->gprs[2];
badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(current);
	काष्ठा rt_sigframe __user *frame =
		(काष्ठा rt_sigframe __user *)regs->gprs[15];
	sigset_t set;

	अगर (__copy_from_user(&set.sig, &frame->uc.uc_sigmask, माप(set)))
		जाओ badframe;
	set_current_blocked(&set);
	अगर (restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;
	save_fpu_regs();
	अगर (restore_sigregs(regs, &frame->uc.uc_mcontext))
		जाओ badframe;
	अगर (restore_sigregs_ext(regs, &frame->uc.uc_mcontext_ext))
		जाओ badframe;
	load_sigregs();
	वापस regs->gprs[2];
badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

/*
 * Determine which stack to use..
 */
अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा k_sigaction *ka, काष्ठा pt_regs * regs, माप_प्रकार frame_size)
अणु
	अचिन्हित दीर्घ sp;

	/* Default to using normal stack */
	sp = regs->gprs[15];

	/* Overflow on alternate संकेत stack gives संक_अंश. */
	अगर (on_sig_stack(sp) && !on_sig_stack((sp - frame_size) & -8UL))
		वापस (व्योम __user *) -1UL;

	/* This is the X/Open sanctioned संकेत stack चयनing.  */
	अगर (ka->sa.sa_flags & SA_ONSTACK) अणु
		अगर (! sas_ss_flags(sp))
			sp = current->sas_ss_sp + current->sas_ss_size;
	पूर्ण

	वापस (व्योम __user *)((sp - frame_size) & -8ul);
पूर्ण

अटल पूर्णांक setup_frame(पूर्णांक sig, काष्ठा k_sigaction *ka,
		       sigset_t *set, काष्ठा pt_regs * regs)
अणु
	काष्ठा sigframe __user *frame;
	काष्ठा sigcontext sc;
	अचिन्हित दीर्घ restorer;
	माप_प्रकार frame_size;

	/*
	 * gprs_high are only present क्रम a 31-bit task running on
	 * a 64-bit kernel (see compat_संकेत.c) but the space क्रम
	 * gprs_high need to be allocated अगर vector रेजिस्टरs are
	 * included in the संकेत frame on a 31-bit प्रणाली.
	 */
	frame_size = माप(*frame) - माप(frame->sregs_ext);
	अगर (MACHINE_HAS_VX)
		frame_size += माप(frame->sregs_ext);
	frame = get_sigframe(ka, regs, frame_size);
	अगर (frame == (व्योम __user *) -1UL)
		वापस -EFAULT;

	/* Set up backchain. */
	अगर (__put_user(regs->gprs[15], (addr_t __user *) frame))
		वापस -EFAULT;

	/* Create काष्ठा sigcontext on the संकेत stack */
	स_नकल(&sc.oldmask, &set->sig, _SIGMASK_COPY_SIZE);
	sc.sregs = (_sigregs __user __क्रमce *) &frame->sregs;
	अगर (__copy_to_user(&frame->sc, &sc, माप(frame->sc)))
		वापस -EFAULT;

	/* Store रेजिस्टरs needed to create the संकेत frame */
	store_sigregs();

	/* Create _sigregs on the संकेत stack */
	अगर (save_sigregs(regs, &frame->sregs))
		वापस -EFAULT;

	/* Place संकेत number on stack to allow backtrace from handler.  */
	अगर (__put_user(regs->gprs[2], (पूर्णांक __user *) &frame->signo))
		वापस -EFAULT;

	/* Create _sigregs_ext on the संकेत stack */
	अगर (save_sigregs_ext(regs, &frame->sregs_ext))
		वापस -EFAULT;

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	अगर (ka->sa.sa_flags & SA_RESTORER) अणु
		restorer = (अचिन्हित दीर्घ) ka->sa.sa_restorer;
	पूर्ण अन्यथा अणु
		/* Signal frame without vector रेजिस्टरs are लघु ! */
		__u16 __user *svc = (व्योम __user *) frame + frame_size - 2;
		अगर (__put_user(S390_SYSCALL_OPCODE | __NR_sigवापस, svc))
			वापस -EFAULT;
		restorer = (अचिन्हित दीर्घ) svc;
	पूर्ण

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->gprs[14] = restorer;
	regs->gprs[15] = (अचिन्हित दीर्घ) frame;
	/* Force शेष amode and शेष user address space control. */
	regs->psw.mask = PSW_MASK_EA | PSW_MASK_BA |
		(PSW_USER_BITS & PSW_MASK_ASC) |
		(regs->psw.mask & ~PSW_MASK_ASC);
	regs->psw.addr = (अचिन्हित दीर्घ) ka->sa.sa_handler;

	regs->gprs[2] = sig;
	regs->gprs[3] = (अचिन्हित दीर्घ) &frame->sc;

	/* We क्रमgot to include these in the sigcontext.
	   To aव्योम अवरोधing binary compatibility, they are passed as args. */
	अगर (sig == संक_अंश || sig == SIGBUS || sig == संक_अवैध ||
	    sig == SIGTRAP || sig == संक_भ_त्रुटि) अणु
		/* set extra रेजिस्टरs only क्रम synchronous संकेतs */
		regs->gprs[4] = regs->पूर्णांक_code & 127;
		regs->gprs[5] = regs->पूर्णांक_parm_दीर्घ;
		regs->gprs[6] = current->thपढ़ो.last_अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक setup_rt_frame(काष्ठा kसंकेत *ksig, sigset_t *set,
			  काष्ठा pt_regs *regs)
अणु
	काष्ठा rt_sigframe __user *frame;
	अचिन्हित दीर्घ uc_flags, restorer;
	माप_प्रकार frame_size;

	frame_size = माप(काष्ठा rt_sigframe) - माप(_sigregs_ext);
	/*
	 * gprs_high are only present क्रम a 31-bit task running on
	 * a 64-bit kernel (see compat_संकेत.c) but the space क्रम
	 * gprs_high need to be allocated अगर vector रेजिस्टरs are
	 * included in the संकेत frame on a 31-bit प्रणाली.
	 */
	uc_flags = 0;
	अगर (MACHINE_HAS_VX) अणु
		frame_size += माप(_sigregs_ext);
		uc_flags |= UC_VXRS;
	पूर्ण
	frame = get_sigframe(&ksig->ka, regs, frame_size);
	अगर (frame == (व्योम __user *) -1UL)
		वापस -EFAULT;

	/* Set up backchain. */
	अगर (__put_user(regs->gprs[15], (addr_t __user *) frame))
		वापस -EFAULT;

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER) अणु
		restorer = (अचिन्हित दीर्घ) ksig->ka.sa.sa_restorer;
	पूर्ण अन्यथा अणु
		__u16 __user *svc = &frame->svc_insn;
		अगर (__put_user(S390_SYSCALL_OPCODE | __NR_rt_sigवापस, svc))
			वापस -EFAULT;
		restorer = (अचिन्हित दीर्घ) svc;
	पूर्ण

	/* Create siginfo on the संकेत stack */
	अगर (copy_siginfo_to_user(&frame->info, &ksig->info))
		वापस -EFAULT;

	/* Store रेजिस्टरs needed to create the संकेत frame */
	store_sigregs();

	/* Create ucontext on the संकेत stack. */
	अगर (__put_user(uc_flags, &frame->uc.uc_flags) ||
	    __put_user(शून्य, &frame->uc.uc_link) ||
	    __save_altstack(&frame->uc.uc_stack, regs->gprs[15]) ||
	    save_sigregs(regs, &frame->uc.uc_mcontext) ||
	    __copy_to_user(&frame->uc.uc_sigmask, set, माप(*set)) ||
	    save_sigregs_ext(regs, &frame->uc.uc_mcontext_ext))
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->gprs[14] = restorer;
	regs->gprs[15] = (अचिन्हित दीर्घ) frame;
	/* Force शेष amode and शेष user address space control. */
	regs->psw.mask = PSW_MASK_EA | PSW_MASK_BA |
		(PSW_USER_BITS & PSW_MASK_ASC) |
		(regs->psw.mask & ~PSW_MASK_ASC);
	regs->psw.addr = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;

	regs->gprs[2] = ksig->sig;
	regs->gprs[3] = (अचिन्हित दीर्घ) &frame->info;
	regs->gprs[4] = (अचिन्हित दीर्घ) &frame->uc;
	regs->gprs[5] = current->thपढ़ो.last_अवरोध;
	वापस 0;
पूर्ण

अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, sigset_t *oldset,
			  काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;

	/* Set up the stack frame */
	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		ret = setup_rt_frame(ksig, oldset, regs);
	अन्यथा
		ret = setup_frame(ksig->sig, &ksig->ka, oldset, regs);

	संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLE_STEP));
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

व्योम arch_करो_संकेत_or_restart(काष्ठा pt_regs *regs, bool has_संकेत)
अणु
	काष्ठा kसंकेत ksig;
	sigset_t *oldset = sigmask_to_save();

	/*
	 * Get संकेत to deliver. When running under ptrace, at this poपूर्णांक
	 * the debugger may change all our रेजिस्टरs, including the प्रणाली
	 * call inक्रमmation.
	 */
	current->thपढ़ो.प्रणाली_call =
		test_pt_regs_flag(regs, PIF_SYSCALL) ? regs->पूर्णांक_code : 0;

	अगर (has_संकेत && get_संकेत(&ksig)) अणु
		/* Whee!  Actually deliver the संकेत.  */
		अगर (current->thपढ़ो.प्रणाली_call) अणु
			regs->पूर्णांक_code = current->thपढ़ो.प्रणाली_call;
			/* Check क्रम प्रणाली call restarting. */
			चयन (regs->gprs[2]) अणु
			हाल -ERESTART_RESTARTBLOCK:
			हाल -ERESTARTNOHAND:
				regs->gprs[2] = -EINTR;
				अवरोध;
			हाल -ERESTARTSYS:
				अगर (!(ksig.ka.sa.sa_flags & SA_RESTART)) अणु
					regs->gprs[2] = -EINTR;
					अवरोध;
				पूर्ण
				fallthrough;
			हाल -ERESTARTNOINTR:
				regs->gprs[2] = regs->orig_gpr2;
				regs->psw.addr =
					__शुरुआत_psw(regs->psw,
						     regs->पूर्णांक_code >> 16);
				अवरोध;
			पूर्ण
		पूर्ण
		/* No दीर्घer in a प्रणाली call */
		clear_pt_regs_flag(regs, PIF_SYSCALL);
		clear_pt_regs_flag(regs, PIF_SYSCALL_RESTART);
		rseq_संकेत_deliver(&ksig, regs);
		अगर (is_compat_task())
			handle_संकेत32(&ksig, oldset, regs);
		अन्यथा
			handle_संकेत(&ksig, oldset, regs);
		वापस;
	पूर्ण

	/* No handlers present - check क्रम प्रणाली call restart */
	clear_pt_regs_flag(regs, PIF_SYSCALL);
	clear_pt_regs_flag(regs, PIF_SYSCALL_RESTART);
	अगर (current->thपढ़ो.प्रणाली_call) अणु
		regs->पूर्णांक_code = current->thपढ़ो.प्रणाली_call;
		चयन (regs->gprs[2]) अणु
		हाल -ERESTART_RESTARTBLOCK:
			/* Restart with sys_restart_syscall */
			regs->पूर्णांक_code = __NR_restart_syscall;
			fallthrough;
		हाल -ERESTARTNOHAND:
		हाल -ERESTARTSYS:
		हाल -ERESTARTNOINTR:
			/* Restart प्रणाली call with magic TIF bit. */
			regs->gprs[2] = regs->orig_gpr2;
			set_pt_regs_flag(regs, PIF_SYSCALL_RESTART);
			अगर (test_thपढ़ो_flag(TIF_SINGLE_STEP))
				clear_thपढ़ो_flag(TIF_PER_TRAP);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If there's no संकेत to deliver, we just put the saved sigmask back.
	 */
	restore_saved_sigmask();
पूर्ण

व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs)
अणु
	tracehook_notअगरy_resume(regs);
	rseq_handle_notअगरy_resume(शून्य, regs);
पूर्ण
