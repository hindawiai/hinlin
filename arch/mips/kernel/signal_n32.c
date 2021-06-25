<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2003 Broadcom Corporation
 */
#समावेश <linux/cache.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/compat.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/abi.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/compat-संकेत.स>
#समावेश <यंत्र/sim.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/war.h>

#समावेश "signal-common.h"

/*
 * Including <यंत्र/unistd.h> would give use the 64-bit syscall numbers ...
 */
#घोषणा __NR_N32_restart_syscall	6214

बाह्य पूर्णांक setup_sigcontext(काष्ठा pt_regs *, काष्ठा sigcontext __user *);
बाह्य पूर्णांक restore_sigcontext(काष्ठा pt_regs *, काष्ठा sigcontext __user *);

काष्ठा ucontextn32 अणु
	u32		    uc_flags;
	s32		    uc_link;
	compat_stack_t      uc_stack;
	काष्ठा sigcontext   uc_mcontext;
	compat_sigset_t	    uc_sigmask;	  /* mask last क्रम extensibility */
पूर्ण;

काष्ठा rt_sigframe_n32 अणु
	u32 rs_ass[4];			/* argument save space क्रम o32 */
	u32 rs_pad[2];			/* Was: संकेत trampoline */
	काष्ठा compat_siginfo rs_info;
	काष्ठा ucontextn32 rs_uc;
पूर्ण;

यंत्रlinkage व्योम sysn32_rt_sigवापस(व्योम)
अणु
	काष्ठा rt_sigframe_n32 __user *frame;
	काष्ठा pt_regs *regs;
	sigset_t set;
	पूर्णांक sig;

	regs = current_pt_regs();
	frame = (काष्ठा rt_sigframe_n32 __user *)regs->regs[29];
	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_conv_sigset_from_user(&set, &frame->rs_uc.uc_sigmask))
		जाओ badframe;

	set_current_blocked(&set);

	sig = restore_sigcontext(regs, &frame->rs_uc.uc_mcontext);
	अगर (sig < 0)
		जाओ badframe;
	अन्यथा अगर (sig)
		क्रमce_sig(sig);

	अगर (compat_restore_altstack(&frame->rs_uc.uc_stack))
		जाओ badframe;

	/*
	 * Don't let your children करो this ...
	 */
	__यंत्र__ __अस्थिर__(
		"move\t$29, %0\n\t"
		"j\tsyscall_exit"
		: /* no outमाला_दो */
		: "r" (regs));
	/* Unreached */

badframe:
	क्रमce_sig(संक_अंश);
पूर्ण

अटल पूर्णांक setup_rt_frame_n32(व्योम *sig_वापस, काष्ठा kसंकेत *ksig,
			      काष्ठा pt_regs *regs, sigset_t *set)
अणु
	काष्ठा rt_sigframe_n32 __user *frame;
	पूर्णांक err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));
	अगर (!access_ok(frame, माप (*frame)))
		वापस -EFAULT;

	/* Create siginfo.  */
	err |= copy_siginfo_to_user32(&frame->rs_info, &ksig->info);

	/* Create the ucontext.	 */
	err |= __put_user(0, &frame->rs_uc.uc_flags);
	err |= __put_user(0, &frame->rs_uc.uc_link);
	err |= __compat_save_altstack(&frame->rs_uc.uc_stack, regs->regs[29]);
	err |= setup_sigcontext(regs, &frame->rs_uc.uc_mcontext);
	err |= __copy_conv_sigset_to_user(&frame->rs_uc.uc_sigmask, set);

	अगर (err)
		वापस -EFAULT;

	/*
	 * Arguments to संकेत handler:
	 *
	 *   a0 = संकेत number
	 *   a1 = 0 (should be cause)
	 *   a2 = poपूर्णांकer to ucontext
	 *
	 * $25 and c0_epc poपूर्णांक to the संकेत handler, $29 poपूर्णांकs to
	 * the काष्ठा rt_sigframe.
	 */
	regs->regs[ 4] = ksig->sig;
	regs->regs[ 5] = (अचिन्हित दीर्घ) &frame->rs_info;
	regs->regs[ 6] = (अचिन्हित दीर्घ) &frame->rs_uc;
	regs->regs[29] = (अचिन्हित दीर्घ) frame;
	regs->regs[31] = (अचिन्हित दीर्घ) sig_वापस;
	regs->cp0_epc = regs->regs[25] = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;

	DEBUGP("SIG deliver (%s:%d): sp=0x%p pc=0x%lx ra=0x%lx\n",
	       current->comm, current->pid,
	       frame, regs->cp0_epc, regs->regs[31]);

	वापस 0;
पूर्ण

काष्ठा mips_abi mips_abi_n32 = अणु
	.setup_rt_frame = setup_rt_frame_n32,
	.restart	= __NR_N32_restart_syscall,

	.off_sc_fpregs = दुरत्व(काष्ठा sigcontext, sc_fpregs),
	.off_sc_fpc_csr = दुरत्व(काष्ठा sigcontext, sc_fpc_csr),
	.off_sc_used_math = दुरत्व(काष्ठा sigcontext, sc_used_math),

	.vdso		= &vdso_image_n32,
पूर्ण;
