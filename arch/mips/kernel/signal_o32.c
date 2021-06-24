<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1991, 1992  Linus Torvalds
 * Copyright (C) 1994 - 2000, 2006  Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2016, Imagination Technologies Ltd.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/abi.h>
#समावेश <यंत्र/compat-संकेत.स>
#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/sim.h>
#समावेश <यंत्र/unistd.h>

#समावेश "signal-common.h"

/*
 * Including <यंत्र/unistd.h> would give use the 64-bit syscall numbers ...
 */
#घोषणा __NR_O32_restart_syscall	4253

काष्ठा sigframe32 अणु
	u32 sf_ass[4];		/* argument save space क्रम o32 */
	u32 sf_pad[2];		/* Was: संकेत trampoline */
	काष्ठा sigcontext32 sf_sc;
	compat_sigset_t sf_mask;
पूर्ण;

काष्ठा ucontext32 अणु
	u32		    uc_flags;
	s32		    uc_link;
	compat_stack_t      uc_stack;
	काष्ठा sigcontext32 uc_mcontext;
	compat_sigset_t	    uc_sigmask;	  /* mask last क्रम extensibility */
पूर्ण;

काष्ठा rt_sigframe32 अणु
	u32 rs_ass[4];			/* argument save space क्रम o32 */
	u32 rs_pad[2];			/* Was: संकेत trampoline */
	compat_siginfo_t rs_info;
	काष्ठा ucontext32 rs_uc;
पूर्ण;

अटल पूर्णांक setup_sigcontext32(काष्ठा pt_regs *regs,
			      काष्ठा sigcontext32 __user *sc)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	err |= __put_user(regs->cp0_epc, &sc->sc_pc);

	err |= __put_user(0, &sc->sc_regs[0]);
	क्रम (i = 1; i < 32; i++)
		err |= __put_user(regs->regs[i], &sc->sc_regs[i]);

	err |= __put_user(regs->hi, &sc->sc_mdhi);
	err |= __put_user(regs->lo, &sc->sc_mdlo);
	अगर (cpu_has_dsp) अणु
		err |= __put_user(rddsp(DSP_MASK), &sc->sc_dsp);
		err |= __put_user(mfhi1(), &sc->sc_hi1);
		err |= __put_user(mflo1(), &sc->sc_lo1);
		err |= __put_user(mfhi2(), &sc->sc_hi2);
		err |= __put_user(mflo2(), &sc->sc_lo2);
		err |= __put_user(mfhi3(), &sc->sc_hi3);
		err |= __put_user(mflo3(), &sc->sc_lo3);
	पूर्ण

	/*
	 * Save FPU state to संकेत context.  Signal handler
	 * will "inherit" current FPU state.
	 */
	err |= रक्षित_save_fp_context(sc);

	वापस err;
पूर्ण

अटल पूर्णांक restore_sigcontext32(काष्ठा pt_regs *regs,
				काष्ठा sigcontext32 __user *sc)
अणु
	पूर्णांक err = 0;
	s32 treg;
	पूर्णांक i;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	err |= __get_user(regs->cp0_epc, &sc->sc_pc);
	err |= __get_user(regs->hi, &sc->sc_mdhi);
	err |= __get_user(regs->lo, &sc->sc_mdlo);
	अगर (cpu_has_dsp) अणु
		err |= __get_user(treg, &sc->sc_hi1); mthi1(treg);
		err |= __get_user(treg, &sc->sc_lo1); mtlo1(treg);
		err |= __get_user(treg, &sc->sc_hi2); mthi2(treg);
		err |= __get_user(treg, &sc->sc_lo2); mtlo2(treg);
		err |= __get_user(treg, &sc->sc_hi3); mthi3(treg);
		err |= __get_user(treg, &sc->sc_lo3); mtlo3(treg);
		err |= __get_user(treg, &sc->sc_dsp); wrdsp(treg, DSP_MASK);
	पूर्ण

	क्रम (i = 1; i < 32; i++)
		err |= __get_user(regs->regs[i], &sc->sc_regs[i]);

	वापस err ?: रक्षित_restore_fp_context(sc);
पूर्ण

अटल पूर्णांक setup_frame_32(व्योम *sig_वापस, काष्ठा kसंकेत *ksig,
			  काष्ठा pt_regs *regs, sigset_t *set)
अणु
	काष्ठा sigframe32 __user *frame;
	पूर्णांक err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));
	अगर (!access_ok(frame, माप (*frame)))
		वापस -EFAULT;

	err |= setup_sigcontext32(regs, &frame->sf_sc);
	err |= __copy_conv_sigset_to_user(&frame->sf_mask, set);

	अगर (err)
		वापस -EFAULT;

	/*
	 * Arguments to संकेत handler:
	 *
	 *   a0 = संकेत number
	 *   a1 = 0 (should be cause)
	 *   a2 = poपूर्णांकer to काष्ठा sigcontext
	 *
	 * $25 and c0_epc poपूर्णांक to the संकेत handler, $29 poपूर्णांकs to the
	 * काष्ठा sigframe.
	 */
	regs->regs[ 4] = ksig->sig;
	regs->regs[ 5] = 0;
	regs->regs[ 6] = (अचिन्हित दीर्घ) &frame->sf_sc;
	regs->regs[29] = (अचिन्हित दीर्घ) frame;
	regs->regs[31] = (अचिन्हित दीर्घ) sig_वापस;
	regs->cp0_epc = regs->regs[25] = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;

	DEBUGP("SIG deliver (%s:%d): sp=0x%p pc=0x%lx ra=0x%lx\n",
	       current->comm, current->pid,
	       frame, regs->cp0_epc, regs->regs[31]);

	वापस 0;
पूर्ण

यंत्रlinkage व्योम sys32_rt_sigवापस(व्योम)
अणु
	काष्ठा rt_sigframe32 __user *frame;
	काष्ठा pt_regs *regs;
	sigset_t set;
	पूर्णांक sig;

	regs = current_pt_regs();
	frame = (काष्ठा rt_sigframe32 __user *)regs->regs[29];
	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_conv_sigset_from_user(&set, &frame->rs_uc.uc_sigmask))
		जाओ badframe;

	set_current_blocked(&set);

	sig = restore_sigcontext32(regs, &frame->rs_uc.uc_mcontext);
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

अटल पूर्णांक setup_rt_frame_32(व्योम *sig_वापस, काष्ठा kसंकेत *ksig,
			     काष्ठा pt_regs *regs, sigset_t *set)
अणु
	काष्ठा rt_sigframe32 __user *frame;
	पूर्णांक err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));
	अगर (!access_ok(frame, माप (*frame)))
		वापस -EFAULT;

	/* Convert (siginfo_t -> compat_siginfo_t) and copy to user. */
	err |= copy_siginfo_to_user32(&frame->rs_info, &ksig->info);

	/* Create the ucontext.	 */
	err |= __put_user(0, &frame->rs_uc.uc_flags);
	err |= __put_user(0, &frame->rs_uc.uc_link);
	err |= __compat_save_altstack(&frame->rs_uc.uc_stack, regs->regs[29]);
	err |= setup_sigcontext32(regs, &frame->rs_uc.uc_mcontext);
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
	 * the काष्ठा rt_sigframe32.
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

/*
 * o32 compatibility on 64-bit kernels, without DSP ASE
 */
काष्ठा mips_abi mips_abi_32 = अणु
	.setup_frame	= setup_frame_32,
	.setup_rt_frame = setup_rt_frame_32,
	.restart	= __NR_O32_restart_syscall,

	.off_sc_fpregs = दुरत्व(काष्ठा sigcontext32, sc_fpregs),
	.off_sc_fpc_csr = दुरत्व(काष्ठा sigcontext32, sc_fpc_csr),
	.off_sc_used_math = दुरत्व(काष्ठा sigcontext32, sc_used_math),

	.vdso		= &vdso_image_o32,
पूर्ण;


यंत्रlinkage व्योम sys32_sigवापस(व्योम)
अणु
	काष्ठा sigframe32 __user *frame;
	काष्ठा pt_regs *regs;
	sigset_t blocked;
	पूर्णांक sig;

	regs = current_pt_regs();
	frame = (काष्ठा sigframe32 __user *)regs->regs[29];
	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_conv_sigset_from_user(&blocked, &frame->sf_mask))
		जाओ badframe;

	set_current_blocked(&blocked);

	sig = restore_sigcontext32(regs, &frame->sf_sc);
	अगर (sig < 0)
		जाओ badframe;
	अन्यथा अगर (sig)
		क्रमce_sig(sig);

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
