<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/संकेत.c
 *
 * Copyright (C) 1995-2009 Russell King
 * Copyright (C) 2012 ARM Ltd.
 * Modअगरied by Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/compat.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/ratelimit.h>

#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/संकेत32.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/vdso.h>

काष्ठा compat_vfp_sigframe अणु
	compat_uदीर्घ_t	magic;
	compat_uदीर्घ_t	size;
	काष्ठा compat_user_vfp अणु
		compat_u64	fpregs[32];
		compat_uदीर्घ_t	fpscr;
	पूर्ण ufp;
	काष्ठा compat_user_vfp_exc अणु
		compat_uदीर्घ_t	fpexc;
		compat_uदीर्घ_t	fpinst;
		compat_uदीर्घ_t	fpinst2;
	पूर्ण ufp_exc;
पूर्ण __attribute__((__aligned__(8)));

#घोषणा VFP_MAGIC		0x56465001
#घोषणा VFP_STORAGE_SIZE	माप(काष्ठा compat_vfp_sigframe)

#घोषणा FSR_WRITE_SHIFT		(11)

काष्ठा compat_aux_sigframe अणु
	काष्ठा compat_vfp_sigframe	vfp;

	/* Something that isn't a valid magic number क्रम any coprocessor.  */
	अचिन्हित दीर्घ			end_magic;
पूर्ण __attribute__((__aligned__(8)));

#घोषणा _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))

अटल अंतरभूत पूर्णांक put_sigset_t(compat_sigset_t __user *uset, sigset_t *set)
अणु
	compat_sigset_t	cset;

	cset.sig[0] = set->sig[0] & 0xffffffffull;
	cset.sig[1] = set->sig[0] >> 32;

	वापस copy_to_user(uset, &cset, माप(*uset));
पूर्ण

अटल अंतरभूत पूर्णांक get_sigset_t(sigset_t *set,
			       स्थिर compat_sigset_t __user *uset)
अणु
	compat_sigset_t s32;

	अगर (copy_from_user(&s32, uset, माप(*uset)))
		वापस -EFAULT;

	set->sig[0] = s32.sig[0] | (((दीर्घ)s32.sig[1]) << 32);
	वापस 0;
पूर्ण

/*
 * VFP save/restore code.
 *
 * We have to be careful with endianness, since the fpsimd context-चयन
 * code operates on 128-bit (Q) रेजिस्टर values whereas the compat ABI
 * uses an array of 64-bit (D) रेजिस्टरs. Consequently, we need to swap
 * the two halves of each Q रेजिस्टर when running on a big-endian CPU.
 */
जोड़ __fpsimd_vreg अणु
	__uपूर्णांक128_t	raw;
	काष्ठा अणु
#अगर_घोषित __AARCH64EB__
		u64	hi;
		u64	lo;
#अन्यथा
		u64	lo;
		u64	hi;
#पूर्ण_अगर
	पूर्ण;
पूर्ण;

अटल पूर्णांक compat_preserve_vfp_context(काष्ठा compat_vfp_sigframe __user *frame)
अणु
	काष्ठा user_fpsimd_state स्थिर *fpsimd =
		&current->thपढ़ो.uw.fpsimd_state;
	compat_uदीर्घ_t magic = VFP_MAGIC;
	compat_uदीर्घ_t size = VFP_STORAGE_SIZE;
	compat_uदीर्घ_t fpscr, fpexc;
	पूर्णांक i, err = 0;

	/*
	 * Save the hardware रेजिस्टरs to the fpsimd_state काष्ठाure.
	 * Note that this also saves V16-31, which aren't visible
	 * in AArch32.
	 */
	fpsimd_संकेत_preserve_current_state();

	/* Place काष्ठाure header on the stack */
	__put_user_error(magic, &frame->magic, err);
	__put_user_error(size, &frame->size, err);

	/*
	 * Now copy the FP रेजिस्टरs. Since the रेजिस्टरs are packed,
	 * we can copy the prefix we want (V0-V15) as it is.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(frame->ufp.fpregs); i += 2) अणु
		जोड़ __fpsimd_vreg vreg = अणु
			.raw = fpsimd->vregs[i >> 1],
		पूर्ण;

		__put_user_error(vreg.lo, &frame->ufp.fpregs[i], err);
		__put_user_error(vreg.hi, &frame->ufp.fpregs[i + 1], err);
	पूर्ण

	/* Create an AArch32 fpscr from the fpsr and the fpcr. */
	fpscr = (fpsimd->fpsr & VFP_FPSCR_STAT_MASK) |
		(fpsimd->fpcr & VFP_FPSCR_CTRL_MASK);
	__put_user_error(fpscr, &frame->ufp.fpscr, err);

	/*
	 * The exception रेजिस्टर aren't available so we fake up a
	 * basic FPEXC and zero everything अन्यथा.
	 */
	fpexc = (1 << 30);
	__put_user_error(fpexc, &frame->ufp_exc.fpexc, err);
	__put_user_error(0, &frame->ufp_exc.fpinst, err);
	__put_user_error(0, &frame->ufp_exc.fpinst2, err);

	वापस err ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक compat_restore_vfp_context(काष्ठा compat_vfp_sigframe __user *frame)
अणु
	काष्ठा user_fpsimd_state fpsimd;
	compat_uदीर्घ_t magic = VFP_MAGIC;
	compat_uदीर्घ_t size = VFP_STORAGE_SIZE;
	compat_uदीर्घ_t fpscr;
	पूर्णांक i, err = 0;

	__get_user_error(magic, &frame->magic, err);
	__get_user_error(size, &frame->size, err);

	अगर (err)
		वापस -EFAULT;
	अगर (magic != VFP_MAGIC || size != VFP_STORAGE_SIZE)
		वापस -EINVAL;

	/* Copy the FP रेजिस्टरs पूर्णांकo the start of the fpsimd_state. */
	क्रम (i = 0; i < ARRAY_SIZE(frame->ufp.fpregs); i += 2) अणु
		जोड़ __fpsimd_vreg vreg;

		__get_user_error(vreg.lo, &frame->ufp.fpregs[i], err);
		__get_user_error(vreg.hi, &frame->ufp.fpregs[i + 1], err);
		fpsimd.vregs[i >> 1] = vreg.raw;
	पूर्ण

	/* Extract the fpsr and the fpcr from the fpscr */
	__get_user_error(fpscr, &frame->ufp.fpscr, err);
	fpsimd.fpsr = fpscr & VFP_FPSCR_STAT_MASK;
	fpsimd.fpcr = fpscr & VFP_FPSCR_CTRL_MASK;

	/*
	 * We करोn't need to touch the exception रेजिस्टर, so
	 * reload the hardware state.
	 */
	अगर (!err)
		fpsimd_update_current_state(&fpsimd);

	वापस err ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक compat_restore_sigframe(काष्ठा pt_regs *regs,
				   काष्ठा compat_sigframe __user *sf)
अणु
	पूर्णांक err;
	sigset_t set;
	काष्ठा compat_aux_sigframe __user *aux;
	अचिन्हित दीर्घ psr;

	err = get_sigset_t(&set, &sf->uc.uc_sigmask);
	अगर (err == 0) अणु
		sigdअन्यथापंचांगask(&set, ~_BLOCKABLE);
		set_current_blocked(&set);
	पूर्ण

	__get_user_error(regs->regs[0], &sf->uc.uc_mcontext.arm_r0, err);
	__get_user_error(regs->regs[1], &sf->uc.uc_mcontext.arm_r1, err);
	__get_user_error(regs->regs[2], &sf->uc.uc_mcontext.arm_r2, err);
	__get_user_error(regs->regs[3], &sf->uc.uc_mcontext.arm_r3, err);
	__get_user_error(regs->regs[4], &sf->uc.uc_mcontext.arm_r4, err);
	__get_user_error(regs->regs[5], &sf->uc.uc_mcontext.arm_r5, err);
	__get_user_error(regs->regs[6], &sf->uc.uc_mcontext.arm_r6, err);
	__get_user_error(regs->regs[7], &sf->uc.uc_mcontext.arm_r7, err);
	__get_user_error(regs->regs[8], &sf->uc.uc_mcontext.arm_r8, err);
	__get_user_error(regs->regs[9], &sf->uc.uc_mcontext.arm_r9, err);
	__get_user_error(regs->regs[10], &sf->uc.uc_mcontext.arm_r10, err);
	__get_user_error(regs->regs[11], &sf->uc.uc_mcontext.arm_fp, err);
	__get_user_error(regs->regs[12], &sf->uc.uc_mcontext.arm_ip, err);
	__get_user_error(regs->compat_sp, &sf->uc.uc_mcontext.arm_sp, err);
	__get_user_error(regs->compat_lr, &sf->uc.uc_mcontext.arm_lr, err);
	__get_user_error(regs->pc, &sf->uc.uc_mcontext.arm_pc, err);
	__get_user_error(psr, &sf->uc.uc_mcontext.arm_cpsr, err);

	regs->pstate = compat_psr_to_pstate(psr);

	/*
	 * Aव्योम compat_sys_sigवापस() restarting.
	 */
	क्रमget_syscall(regs);

	err |= !valid_user_regs(&regs->user_regs, current);

	aux = (काष्ठा compat_aux_sigframe __user *) sf->uc.uc_regspace;
	अगर (err == 0 && प्रणाली_supports_fpsimd())
		err |= compat_restore_vfp_context(&aux->vfp);

	वापस err;
पूर्ण

COMPAT_SYSCALL_DEFINE0(sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा compat_sigframe __user *frame;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/*
	 * Since we stacked the संकेत on a 64-bit boundary,
	 * then 'sp' should be word aligned here.  If it's
	 * not, then the user is trying to mess with us.
	 */
	अगर (regs->compat_sp & 7)
		जाओ badframe;

	frame = (काष्ठा compat_sigframe __user *)regs->compat_sp;

	अगर (!access_ok(frame, माप (*frame)))
		जाओ badframe;

	अगर (compat_restore_sigframe(regs, frame))
		जाओ badframe;

	वापस regs->regs[0];

badframe:
	arm64_notअगरy_segfault(regs->compat_sp);
	वापस 0;
पूर्ण

COMPAT_SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा compat_rt_sigframe __user *frame;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	/*
	 * Since we stacked the संकेत on a 64-bit boundary,
	 * then 'sp' should be word aligned here.  If it's
	 * not, then the user is trying to mess with us.
	 */
	अगर (regs->compat_sp & 7)
		जाओ badframe;

	frame = (काष्ठा compat_rt_sigframe __user *)regs->compat_sp;

	अगर (!access_ok(frame, माप (*frame)))
		जाओ badframe;

	अगर (compat_restore_sigframe(regs, &frame->sig))
		जाओ badframe;

	अगर (compat_restore_altstack(&frame->sig.uc.uc_stack))
		जाओ badframe;

	वापस regs->regs[0];

badframe:
	arm64_notअगरy_segfault(regs->compat_sp);
	वापस 0;
पूर्ण

अटल व्योम __user *compat_get_sigframe(काष्ठा kसंकेत *ksig,
					काष्ठा pt_regs *regs,
					पूर्णांक framesize)
अणु
	compat_uदीर्घ_t sp = sigsp(regs->compat_sp, ksig);
	व्योम __user *frame;

	/*
	 * ATPCS B01 mandates 8-byte alignment
	 */
	frame = compat_ptr((compat_uptr_t)((sp - framesize) & ~7));

	/*
	 * Check that we can actually ग_लिखो to the संकेत frame.
	 */
	अगर (!access_ok(frame, framesize))
		frame = शून्य;

	वापस frame;
पूर्ण

अटल व्योम compat_setup_वापस(काष्ठा pt_regs *regs, काष्ठा k_sigaction *ka,
				compat_uदीर्घ_t __user *rc, व्योम __user *frame,
				पूर्णांक usig)
अणु
	compat_uदीर्घ_t handler = ptr_to_compat(ka->sa.sa_handler);
	compat_uदीर्घ_t retcode;
	compat_uदीर्घ_t spsr = regs->pstate & ~(PSR_f | PSR_AA32_E_BIT);
	पूर्णांक thumb;

	/* Check अगर the handler is written क्रम ARM or Thumb */
	thumb = handler & 1;

	अगर (thumb)
		spsr |= PSR_AA32_T_BIT;
	अन्यथा
		spsr &= ~PSR_AA32_T_BIT;

	/* The IT state must be cleared क्रम both ARM and Thumb-2 */
	spsr &= ~PSR_AA32_IT_MASK;

	/* Restore the original endianness */
	spsr |= PSR_AA32_ENDSTATE;

	अगर (ka->sa.sa_flags & SA_RESTORER) अणु
		retcode = ptr_to_compat(ka->sa.sa_restorer);
	पूर्ण अन्यथा अणु
		/* Set up sigवापस poपूर्णांकer */
		अचिन्हित पूर्णांक idx = thumb << 1;

		अगर (ka->sa.sa_flags & SA_SIGINFO)
			idx += 3;

		retcode = (अचिन्हित दीर्घ)current->mm->context.sigpage +
			  (idx << 2) + thumb;
	पूर्ण

	regs->regs[0]	= usig;
	regs->compat_sp	= ptr_to_compat(frame);
	regs->compat_lr	= retcode;
	regs->pc	= handler;
	regs->pstate	= spsr;
पूर्ण

अटल पूर्णांक compat_setup_sigframe(काष्ठा compat_sigframe __user *sf,
				 काष्ठा pt_regs *regs, sigset_t *set)
अणु
	काष्ठा compat_aux_sigframe __user *aux;
	अचिन्हित दीर्घ psr = pstate_to_compat_psr(regs->pstate);
	पूर्णांक err = 0;

	__put_user_error(regs->regs[0], &sf->uc.uc_mcontext.arm_r0, err);
	__put_user_error(regs->regs[1], &sf->uc.uc_mcontext.arm_r1, err);
	__put_user_error(regs->regs[2], &sf->uc.uc_mcontext.arm_r2, err);
	__put_user_error(regs->regs[3], &sf->uc.uc_mcontext.arm_r3, err);
	__put_user_error(regs->regs[4], &sf->uc.uc_mcontext.arm_r4, err);
	__put_user_error(regs->regs[5], &sf->uc.uc_mcontext.arm_r5, err);
	__put_user_error(regs->regs[6], &sf->uc.uc_mcontext.arm_r6, err);
	__put_user_error(regs->regs[7], &sf->uc.uc_mcontext.arm_r7, err);
	__put_user_error(regs->regs[8], &sf->uc.uc_mcontext.arm_r8, err);
	__put_user_error(regs->regs[9], &sf->uc.uc_mcontext.arm_r9, err);
	__put_user_error(regs->regs[10], &sf->uc.uc_mcontext.arm_r10, err);
	__put_user_error(regs->regs[11], &sf->uc.uc_mcontext.arm_fp, err);
	__put_user_error(regs->regs[12], &sf->uc.uc_mcontext.arm_ip, err);
	__put_user_error(regs->compat_sp, &sf->uc.uc_mcontext.arm_sp, err);
	__put_user_error(regs->compat_lr, &sf->uc.uc_mcontext.arm_lr, err);
	__put_user_error(regs->pc, &sf->uc.uc_mcontext.arm_pc, err);
	__put_user_error(psr, &sf->uc.uc_mcontext.arm_cpsr, err);

	__put_user_error((compat_uदीर्घ_t)0, &sf->uc.uc_mcontext.trap_no, err);
	/* set the compat FSR WnR */
	__put_user_error(!!(current->thपढ़ो.fault_code & ESR_ELx_WNR) <<
			 FSR_WRITE_SHIFT, &sf->uc.uc_mcontext.error_code, err);
	__put_user_error(current->thपढ़ो.fault_address, &sf->uc.uc_mcontext.fault_address, err);
	__put_user_error(set->sig[0], &sf->uc.uc_mcontext.oldmask, err);

	err |= put_sigset_t(&sf->uc.uc_sigmask, set);

	aux = (काष्ठा compat_aux_sigframe __user *) sf->uc.uc_regspace;

	अगर (err == 0 && प्रणाली_supports_fpsimd())
		err |= compat_preserve_vfp_context(&aux->vfp);
	__put_user_error(0, &aux->end_magic, err);

	वापस err;
पूर्ण

/*
 * 32-bit संकेत handling routines called from संकेत.c
 */
पूर्णांक compat_setup_rt_frame(पूर्णांक usig, काष्ठा kसंकेत *ksig,
			  sigset_t *set, काष्ठा pt_regs *regs)
अणु
	काष्ठा compat_rt_sigframe __user *frame;
	पूर्णांक err = 0;

	frame = compat_get_sigframe(ksig, regs, माप(*frame));

	अगर (!frame)
		वापस 1;

	err |= copy_siginfo_to_user32(&frame->info, &ksig->info);

	__put_user_error(0, &frame->sig.uc.uc_flags, err);
	__put_user_error(0, &frame->sig.uc.uc_link, err);

	err |= __compat_save_altstack(&frame->sig.uc.uc_stack, regs->compat_sp);

	err |= compat_setup_sigframe(&frame->sig, regs, set);

	अगर (err == 0) अणु
		compat_setup_वापस(regs, &ksig->ka, frame->sig.retcode, frame, usig);
		regs->regs[1] = (compat_uदीर्घ_t)(अचिन्हित दीर्घ)&frame->info;
		regs->regs[2] = (compat_uदीर्घ_t)(अचिन्हित दीर्घ)&frame->sig.uc;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक compat_setup_frame(पूर्णांक usig, काष्ठा kसंकेत *ksig, sigset_t *set,
		       काष्ठा pt_regs *regs)
अणु
	काष्ठा compat_sigframe __user *frame;
	पूर्णांक err = 0;

	frame = compat_get_sigframe(ksig, regs, माप(*frame));

	अगर (!frame)
		वापस 1;

	__put_user_error(0x5ac3c35a, &frame->uc.uc_flags, err);

	err |= compat_setup_sigframe(frame, regs, set);
	अगर (err == 0)
		compat_setup_वापस(regs, &ksig->ka, frame->retcode, frame, usig);

	वापस err;
पूर्ण

व्योम compat_setup_restart_syscall(काष्ठा pt_regs *regs)
अणु
       regs->regs[7] = __NR_compat_restart_syscall;
पूर्ण
