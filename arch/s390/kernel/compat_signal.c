<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2000, 2006
 *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)
 *               Gerhard Tonn (ton@de.ibm.com)                  
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  1997-11-28  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 */

#समावेश <linux/compat.h>
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
#समावेश <linux/personality.h>
#समावेश <linux/binfmts.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश "compat_linux.h"
#समावेश "compat_ptrace.h"
#समावेश "entry.h"

प्रकार काष्ठा 
अणु
	__u8 callee_used_stack[__SIGNAL_FRAMESIZE32];
	काष्ठा sigcontext32 sc;
	_sigregs32 sregs;
	पूर्णांक signo;
	_sigregs_ext32 sregs_ext;
	__u16 svc_insn;		/* Offset of svc_insn is NOT fixed! */
पूर्ण sigframe32;

प्रकार काष्ठा 
अणु
	__u8 callee_used_stack[__SIGNAL_FRAMESIZE32];
	__u16 svc_insn;
	compat_siginfo_t info;
	काष्ठा ucontext32 uc;
पूर्ण rt_sigframe32;

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

अटल पूर्णांक save_sigregs32(काष्ठा pt_regs *regs, _sigregs32 __user *sregs)
अणु
	_sigregs32 user_sregs;
	पूर्णांक i;

	user_sregs.regs.psw.mask = (__u32)(regs->psw.mask >> 32);
	user_sregs.regs.psw.mask &= PSW32_MASK_USER | PSW32_MASK_RI;
	user_sregs.regs.psw.mask |= PSW32_USER_BITS;
	user_sregs.regs.psw.addr = (__u32) regs->psw.addr |
		(__u32)(regs->psw.mask & PSW_MASK_BA);
	क्रम (i = 0; i < NUM_GPRS; i++)
		user_sregs.regs.gprs[i] = (__u32) regs->gprs[i];
	स_नकल(&user_sregs.regs.acrs, current->thपढ़ो.acrs,
	       माप(user_sregs.regs.acrs));
	fpregs_store((_s390_fp_regs *) &user_sregs.fpregs, &current->thपढ़ो.fpu);
	अगर (__copy_to_user(sregs, &user_sregs, माप(_sigregs32)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक restore_sigregs32(काष्ठा pt_regs *regs,_sigregs32 __user *sregs)
अणु
	_sigregs32 user_sregs;
	पूर्णांक i;

	/* Alwys make any pending restarted प्रणाली call वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (__copy_from_user(&user_sregs, &sregs->regs, माप(user_sregs)))
		वापस -EFAULT;

	अगर (!is_ri_task(current) && (user_sregs.regs.psw.mask & PSW32_MASK_RI))
		वापस -EINVAL;

	/* Test the भग्नing-poपूर्णांक-control word. */
	अगर (test_fp_ctl(user_sregs.fpregs.fpc))
		वापस -EINVAL;

	/* Use regs->psw.mask instead of PSW_USER_BITS to preserve PER bit. */
	regs->psw.mask = (regs->psw.mask & ~(PSW_MASK_USER | PSW_MASK_RI)) |
		(__u64)(user_sregs.regs.psw.mask & PSW32_MASK_USER) << 32 |
		(__u64)(user_sregs.regs.psw.mask & PSW32_MASK_RI) << 32 |
		(__u64)(user_sregs.regs.psw.addr & PSW32_ADDR_AMODE);
	/* Check क्रम invalid user address space control. */
	अगर ((regs->psw.mask & PSW_MASK_ASC) == PSW_ASC_HOME)
		regs->psw.mask = PSW_ASC_PRIMARY |
			(regs->psw.mask & ~PSW_MASK_ASC);
	regs->psw.addr = (__u64)(user_sregs.regs.psw.addr & PSW32_ADDR_INSN);
	क्रम (i = 0; i < NUM_GPRS; i++)
		regs->gprs[i] = (__u64) user_sregs.regs.gprs[i];
	स_नकल(&current->thपढ़ो.acrs, &user_sregs.regs.acrs,
	       माप(current->thपढ़ो.acrs));
	fpregs_load((_s390_fp_regs *) &user_sregs.fpregs, &current->thपढ़ो.fpu);

	clear_pt_regs_flag(regs, PIF_SYSCALL); /* No दीर्घer in a प्रणाली call */
	clear_pt_regs_flag(regs, PIF_SYSCALL_RESTART);
	वापस 0;
पूर्ण

अटल पूर्णांक save_sigregs_ext32(काष्ठा pt_regs *regs,
			      _sigregs_ext32 __user *sregs_ext)
अणु
	__u32 gprs_high[NUM_GPRS];
	__u64 vxrs[__NUM_VXRS_LOW];
	पूर्णांक i;

	/* Save high gprs to संकेत stack */
	क्रम (i = 0; i < NUM_GPRS; i++)
		gprs_high[i] = regs->gprs[i] >> 32;
	अगर (__copy_to_user(&sregs_ext->gprs_high, &gprs_high,
			   माप(sregs_ext->gprs_high)))
		वापस -EFAULT;

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

अटल पूर्णांक restore_sigregs_ext32(काष्ठा pt_regs *regs,
				 _sigregs_ext32 __user *sregs_ext)
अणु
	__u32 gprs_high[NUM_GPRS];
	__u64 vxrs[__NUM_VXRS_LOW];
	पूर्णांक i;

	/* Restore high gprs from संकेत stack */
	अगर (__copy_from_user(&gprs_high, &sregs_ext->gprs_high,
			     माप(sregs_ext->gprs_high)))
		वापस -EFAULT;
	क्रम (i = 0; i < NUM_GPRS; i++)
		*(__u32 *)&regs->gprs[i] = gprs_high[i];

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

COMPAT_SYSCALL_DEFINE0(sigवापस)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(current);
	sigframe32 __user *frame = (sigframe32 __user *)regs->gprs[15];
	sigset_t set;

	अगर (get_compat_sigset(&set, (compat_sigset_t __user *)frame->sc.oldmask))
		जाओ badframe;
	set_current_blocked(&set);
	save_fpu_regs();
	अगर (restore_sigregs32(regs, &frame->sregs))
		जाओ badframe;
	अगर (restore_sigregs_ext32(regs, &frame->sregs_ext))
		जाओ badframe;
	load_sigregs();
	वापस regs->gprs[2];
badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

COMPAT_SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(current);
	rt_sigframe32 __user *frame = (rt_sigframe32 __user *)regs->gprs[15];
	sigset_t set;

	अगर (get_compat_sigset(&set, &frame->uc.uc_sigmask))
		जाओ badframe;
	set_current_blocked(&set);
	अगर (compat_restore_altstack(&frame->uc.uc_stack))
		जाओ badframe;
	save_fpu_regs();
	अगर (restore_sigregs32(regs, &frame->uc.uc_mcontext))
		जाओ badframe;
	अगर (restore_sigregs_ext32(regs, &frame->uc.uc_mcontext_ext))
		जाओ badframe;
	load_sigregs();
	वापस regs->gprs[2];
badframe:
	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण	

/*
 * Set up a संकेत frame.
 */


/*
 * Determine which stack to use..
 */
अटल अंतरभूत व्योम __user *
get_sigframe(काष्ठा k_sigaction *ka, काष्ठा pt_regs * regs, माप_प्रकार frame_size)
अणु
	अचिन्हित दीर्घ sp;

	/* Default to using normal stack */
	sp = (अचिन्हित दीर्घ) A(regs->gprs[15]);

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

अटल पूर्णांक setup_frame32(काष्ठा kसंकेत *ksig, sigset_t *set,
			 काष्ठा pt_regs *regs)
अणु
	पूर्णांक sig = ksig->sig;
	sigframe32 __user *frame;
	अचिन्हित दीर्घ restorer;
	माप_प्रकार frame_size;

	/*
	 * gprs_high are always present क्रम 31-bit compat tasks.
	 * The space क्रम vector रेजिस्टरs is only allocated अगर
	 * the machine supports it
	 */
	frame_size = माप(*frame) - माप(frame->sregs_ext.__reserved);
	अगर (!MACHINE_HAS_VX)
		frame_size -= माप(frame->sregs_ext.vxrs_low) +
			      माप(frame->sregs_ext.vxrs_high);
	frame = get_sigframe(&ksig->ka, regs, frame_size);
	अगर (frame == (व्योम __user *) -1UL)
		वापस -EFAULT;

	/* Set up backchain. */
	अगर (__put_user(regs->gprs[15], (अचिन्हित पूर्णांक __user *) frame))
		वापस -EFAULT;

	/* Create काष्ठा sigcontext32 on the संकेत stack */
	अगर (put_compat_sigset((compat_sigset_t __user *)frame->sc.oldmask,
			      set, माप(compat_sigset_t)))
		वापस -EFAULT;
	अगर (__put_user(ptr_to_compat(&frame->sregs), &frame->sc.sregs))
		वापस -EFAULT;

	/* Store रेजिस्टरs needed to create the संकेत frame */
	store_sigregs();

	/* Create _sigregs32 on the संकेत stack */
	अगर (save_sigregs32(regs, &frame->sregs))
		वापस -EFAULT;

	/* Place संकेत number on stack to allow backtrace from handler.  */
	अगर (__put_user(regs->gprs[2], (पूर्णांक __क्रमce __user *) &frame->signo))
		वापस -EFAULT;

	/* Create _sigregs_ext32 on the संकेत stack */
	अगर (save_sigregs_ext32(regs, &frame->sregs_ext))
		वापस -EFAULT;

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER) अणु
		restorer = (अचिन्हित दीर्घ __क्रमce)
			ksig->ka.sa.sa_restorer | PSW32_ADDR_AMODE;
	पूर्ण अन्यथा अणु
		/* Signal frames without vectors रेजिस्टरs are लघु ! */
		__u16 __user *svc = (व्योम __user *) frame + frame_size - 2;
		अगर (__put_user(S390_SYSCALL_OPCODE | __NR_sigवापस, svc))
			वापस -EFAULT;
		restorer = (अचिन्हित दीर्घ __क्रमce) svc | PSW32_ADDR_AMODE;
        पूर्ण

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->gprs[14] = restorer;
	regs->gprs[15] = (__क्रमce __u64) frame;
	/* Force 31 bit amode and शेष user address space control. */
	regs->psw.mask = PSW_MASK_BA |
		(PSW_USER_BITS & PSW_MASK_ASC) |
		(regs->psw.mask & ~PSW_MASK_ASC);
	regs->psw.addr = (__क्रमce __u64) ksig->ka.sa.sa_handler;

	regs->gprs[2] = sig;
	regs->gprs[3] = (__क्रमce __u64) &frame->sc;

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

अटल पूर्णांक setup_rt_frame32(काष्ठा kसंकेत *ksig, sigset_t *set,
			    काष्ठा pt_regs *regs)
अणु
	rt_sigframe32 __user *frame;
	अचिन्हित दीर्घ restorer;
	माप_प्रकार frame_size;
	u32 uc_flags;

	frame_size = माप(*frame) -
		     माप(frame->uc.uc_mcontext_ext.__reserved);
	/*
	 * gprs_high are always present क्रम 31-bit compat tasks.
	 * The space क्रम vector रेजिस्टरs is only allocated अगर
	 * the machine supports it
	 */
	uc_flags = UC_GPRS_HIGH;
	अगर (MACHINE_HAS_VX) अणु
		uc_flags |= UC_VXRS;
	पूर्ण अन्यथा
		frame_size -= माप(frame->uc.uc_mcontext_ext.vxrs_low) +
			      माप(frame->uc.uc_mcontext_ext.vxrs_high);
	frame = get_sigframe(&ksig->ka, regs, frame_size);
	अगर (frame == (व्योम __user *) -1UL)
		वापस -EFAULT;

	/* Set up backchain. */
	अगर (__put_user(regs->gprs[15], (अचिन्हित पूर्णांक __क्रमce __user *) frame))
		वापस -EFAULT;

	/* Set up to वापस from userspace.  If provided, use a stub
	   alपढ़ोy in userspace.  */
	अगर (ksig->ka.sa.sa_flags & SA_RESTORER) अणु
		restorer = (अचिन्हित दीर्घ __क्रमce)
			ksig->ka.sa.sa_restorer | PSW32_ADDR_AMODE;
	पूर्ण अन्यथा अणु
		__u16 __user *svc = &frame->svc_insn;
		अगर (__put_user(S390_SYSCALL_OPCODE | __NR_rt_sigवापस, svc))
			वापस -EFAULT;
		restorer = (अचिन्हित दीर्घ __क्रमce) svc | PSW32_ADDR_AMODE;
	पूर्ण

	/* Create siginfo on the संकेत stack */
	अगर (copy_siginfo_to_user32(&frame->info, &ksig->info))
		वापस -EFAULT;

	/* Store रेजिस्टरs needed to create the संकेत frame */
	store_sigregs();

	/* Create ucontext on the संकेत stack. */
	अगर (__put_user(uc_flags, &frame->uc.uc_flags) ||
	    __put_user(0, &frame->uc.uc_link) ||
	    __compat_save_altstack(&frame->uc.uc_stack, regs->gprs[15]) ||
	    save_sigregs32(regs, &frame->uc.uc_mcontext) ||
	    put_compat_sigset(&frame->uc.uc_sigmask, set, माप(compat_sigset_t)) ||
	    save_sigregs_ext32(regs, &frame->uc.uc_mcontext_ext))
		वापस -EFAULT;

	/* Set up रेजिस्टरs क्रम संकेत handler */
	regs->gprs[14] = restorer;
	regs->gprs[15] = (__क्रमce __u64) frame;
	/* Force 31 bit amode and शेष user address space control. */
	regs->psw.mask = PSW_MASK_BA |
		(PSW_USER_BITS & PSW_MASK_ASC) |
		(regs->psw.mask & ~PSW_MASK_ASC);
	regs->psw.addr = (__u64 __क्रमce) ksig->ka.sa.sa_handler;

	regs->gprs[2] = ksig->sig;
	regs->gprs[3] = (__क्रमce __u64) &frame->info;
	regs->gprs[4] = (__क्रमce __u64) &frame->uc;
	regs->gprs[5] = current->thपढ़ो.last_अवरोध;
	वापस 0;
पूर्ण

/*
 * OK, we're invoking a handler
 */	

व्योम handle_संकेत32(काष्ठा kसंकेत *ksig, sigset_t *oldset,
		     काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;

	/* Set up the stack frame */
	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO)
		ret = setup_rt_frame32(ksig, oldset, regs);
	अन्यथा
		ret = setup_frame32(ksig, oldset, regs);

	संकेत_setup_करोne(ret, ksig, test_thपढ़ो_flag(TIF_SINGLE_STEP));
पूर्ण

