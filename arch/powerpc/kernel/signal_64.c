<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  PowerPC version 
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 *  Derived from "arch/i386/kernel/signal.c"
 *    Copyright (C) 1991, 1992 Linus Torvalds
 *    1997-11-28  Modअगरied क्रम POSIX.1b संकेतs by Riअक्षरd Henderson
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/elf.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/पंचांग.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

#समावेश "signal.h"


#घोषणा GP_REGS_SIZE	min(माप(elf_gregset_t), माप(काष्ठा pt_regs))
#घोषणा FP_REGS_SIZE	माप(elf_fpregset_t)

#घोषणा TRAMP_TRACEBACK	4
#घोषणा TRAMP_SIZE	7

/*
 * When we have संकेतs to deliver, we set up on the user stack,
 * going करोwn from the original stack poपूर्णांकer:
 *	1) a rt_sigframe काष्ठा which contains the ucontext	
 *	2) a gap of __SIGNAL_FRAMESIZE bytes which acts as a dummy caller
 *	   frame क्रम the संकेत handler.
 */

काष्ठा rt_sigframe अणु
	/* sys_rt_sigवापस requires the ucontext be the first field */
	काष्ठा ucontext uc;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	काष्ठा ucontext uc_transact;
#पूर्ण_अगर
	अचिन्हित दीर्घ _unused[2];
	अचिन्हित पूर्णांक tramp[TRAMP_SIZE];
	काष्ठा siginfo __user *pinfo;
	व्योम __user *puc;
	काष्ठा siginfo info;
	/* New 64 bit little-endian ABI allows redzone of 512 bytes below sp */
	अक्षर abigap[USER_REDZONE_SIZE];
पूर्ण __attribute__ ((aligned (16)));

/*
 * This computes a quad word aligned poपूर्णांकer inside the vmx_reserve array
 * element. For historical reasons sigcontext might not be quad word aligned,
 * but the location we ग_लिखो the VMX regs to must be. See the comment in
 * sigcontext क्रम more detail.
 */
#अगर_घोषित CONFIG_ALTIVEC
अटल elf_vrreg_t __user *sigcontext_vmx_regs(काष्ठा sigcontext __user *sc)
अणु
	वापस (elf_vrreg_t __user *) (((अचिन्हित दीर्घ)sc->vmx_reserve + 15) & ~0xful);
पूर्ण
#पूर्ण_अगर

अटल व्योम prepare_setup_sigcontext(काष्ठा task_काष्ठा *tsk)
अणु
#अगर_घोषित CONFIG_ALTIVEC
	/* save altivec रेजिस्टरs */
	अगर (tsk->thपढ़ो.used_vr)
		flush_altivec_to_thपढ़ो(tsk);
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		tsk->thपढ़ो.vrsave = mfspr(SPRN_VRSAVE);
#पूर्ण_अगर /* CONFIG_ALTIVEC */

	flush_fp_to_thपढ़ो(tsk);

#अगर_घोषित CONFIG_VSX
	अगर (tsk->thपढ़ो.used_vsr)
		flush_vsx_to_thपढ़ो(tsk);
#पूर्ण_अगर /* CONFIG_VSX */
पूर्ण

/*
 * Set up the sigcontext क्रम the संकेत frame.
 */

#घोषणा unsafe_setup_sigcontext(sc, tsk, signr, set, handler, ctx_has_vsx_region, label)\
करो अणु											\
	अगर (__unsafe_setup_sigcontext(sc, tsk, signr, set, handler, ctx_has_vsx_region))\
		जाओ label;								\
पूर्ण जबतक (0)
अटल दीर्घ notrace __unsafe_setup_sigcontext(काष्ठा sigcontext __user *sc,
					काष्ठा task_काष्ठा *tsk, पूर्णांक signr, sigset_t *set,
					अचिन्हित दीर्घ handler, पूर्णांक ctx_has_vsx_region)
अणु
	/* When CONFIG_ALTIVEC is set, we _always_ setup v_regs even अगर the
	 * process never used altivec yet (MSR_VEC is zero in pt_regs of
	 * the context). This is very important because we must ensure we
	 * करोn't lose the VRSAVE content that may have been set prior to
	 * the process करोing its first vector operation
	 * Userland shall check AT_HWCAP to know whether it can rely on the
	 * v_regs poपूर्णांकer or not
	 */
#अगर_घोषित CONFIG_ALTIVEC
	elf_vrreg_t __user *v_regs = sigcontext_vmx_regs(sc);
#पूर्ण_अगर
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;
	अचिन्हित दीर्घ msr = regs->msr;
	/* Force usr to alway see softe as 1 (पूर्णांकerrupts enabled) */
	अचिन्हित दीर्घ softe = 0x1;

	BUG_ON(tsk != current);

#अगर_घोषित CONFIG_ALTIVEC
	unsafe_put_user(v_regs, &sc->v_regs, efault_out);

	/* save altivec रेजिस्टरs */
	अगर (tsk->thपढ़ो.used_vr) अणु
		/* Copy 33 vec रेजिस्टरs (vr0..31 and vscr) to the stack */
		unsafe_copy_to_user(v_regs, &tsk->thपढ़ो.vr_state,
				    33 * माप(vector128), efault_out);
		/* set MSR_VEC in the MSR value in the frame to indicate that sc->v_reg)
		 * contains valid data.
		 */
		msr |= MSR_VEC;
	पूर्ण
	/* We always copy to/from vrsave, it's 0 if we don't have or don't
	 * use altivec.
	 */
	unsafe_put_user(tsk->thपढ़ो.vrsave, (u32 __user *)&v_regs[33], efault_out);
#अन्यथा /* CONFIG_ALTIVEC */
	unsafe_put_user(0, &sc->v_regs, efault_out);
#पूर्ण_अगर /* CONFIG_ALTIVEC */
	/* copy fpr regs and fpscr */
	unsafe_copy_fpr_to_user(&sc->fp_regs, tsk, efault_out);

	/*
	 * Clear the MSR VSX bit to indicate there is no valid state attached
	 * to this context, except in the specअगरic हाल below where we set it.
	 */
	msr &= ~MSR_VSX;
#अगर_घोषित CONFIG_VSX
	/*
	 * Copy VSX low द्विगुनword to local buffer क्रम क्रमmatting,
	 * then out to userspace.  Update v_regs to poपूर्णांक after the
	 * VMX data.
	 */
	अगर (tsk->thपढ़ो.used_vsr && ctx_has_vsx_region) अणु
		v_regs += ELF_NVRREG;
		unsafe_copy_vsx_to_user(v_regs, tsk, efault_out);
		/* set MSR_VSX in the MSR value in the frame to
		 * indicate that sc->vs_reg) contains valid data.
		 */
		msr |= MSR_VSX;
	पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */
	unsafe_put_user(&sc->gp_regs, &sc->regs, efault_out);
	unsafe_copy_to_user(&sc->gp_regs, regs, GP_REGS_SIZE, efault_out);
	unsafe_put_user(msr, &sc->gp_regs[PT_MSR], efault_out);
	unsafe_put_user(softe, &sc->gp_regs[PT_SOFTE], efault_out);
	unsafe_put_user(signr, &sc->संकेत, efault_out);
	unsafe_put_user(handler, &sc->handler, efault_out);
	अगर (set != शून्य)
		unsafe_put_user(set->sig[0], &sc->oldmask, efault_out);

	वापस 0;

efault_out:
	वापस -EFAULT;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
/*
 * As above, but Transactional Memory is in use, so deliver sigcontexts
 * containing checkpoपूर्णांकed and transactional रेजिस्टर states.
 *
 * To करो this, we treclaim (करोne beक्रमe entering here) to gather both sets of
 * रेजिस्टरs and set up the 'normal' sigcontext रेजिस्टरs with rolled-back
 * रेजिस्टर values such that a simple संकेत handler sees a correct
 * checkpoपूर्णांकed रेजिस्टर state.  If पूर्णांकerested, a TM-aware sighandler can
 * examine the transactional रेजिस्टरs in the 2nd sigcontext to determine the
 * real origin of the संकेत.
 */
अटल दीर्घ setup_पंचांग_sigcontexts(काष्ठा sigcontext __user *sc,
				 काष्ठा sigcontext __user *पंचांग_sc,
				 काष्ठा task_काष्ठा *tsk,
				 पूर्णांक signr, sigset_t *set, अचिन्हित दीर्घ handler,
				 अचिन्हित दीर्घ msr)
अणु
	/* When CONFIG_ALTIVEC is set, we _always_ setup v_regs even अगर the
	 * process never used altivec yet (MSR_VEC is zero in pt_regs of
	 * the context). This is very important because we must ensure we
	 * करोn't lose the VRSAVE content that may have been set prior to
	 * the process करोing its first vector operation
	 * Userland shall check AT_HWCAP to know wether it can rely on the
	 * v_regs poपूर्णांकer or not.
	 */
#अगर_घोषित CONFIG_ALTIVEC
	elf_vrreg_t __user *v_regs = sigcontext_vmx_regs(sc);
	elf_vrreg_t __user *पंचांग_v_regs = sigcontext_vmx_regs(पंचांग_sc);
#पूर्ण_अगर
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;
	दीर्घ err = 0;

	BUG_ON(tsk != current);

	BUG_ON(!MSR_TM_ACTIVE(msr));

	WARN_ON(पंचांग_suspend_disabled);

	/* Restore checkpoपूर्णांकed FP, VEC, and VSX bits from ckpt_regs as
	 * it contains the correct FP, VEC, VSX state after we treclaimed
	 * the transaction and giveup_all() was called on reclaiming.
	 */
	msr |= tsk->thपढ़ो.ckpt_regs.msr & (MSR_FP | MSR_VEC | MSR_VSX);

#अगर_घोषित CONFIG_ALTIVEC
	err |= __put_user(v_regs, &sc->v_regs);
	err |= __put_user(पंचांग_v_regs, &पंचांग_sc->v_regs);

	/* save altivec रेजिस्टरs */
	अगर (tsk->thपढ़ो.used_vr) अणु
		/* Copy 33 vec रेजिस्टरs (vr0..31 and vscr) to the stack */
		err |= __copy_to_user(v_regs, &tsk->thपढ़ो.ckvr_state,
				      33 * माप(vector128));
		/* If VEC was enabled there are transactional VRs valid too,
		 * अन्यथा they're a copy of the checkpoपूर्णांकed VRs.
		 */
		अगर (msr & MSR_VEC)
			err |= __copy_to_user(पंचांग_v_regs,
					      &tsk->thपढ़ो.vr_state,
					      33 * माप(vector128));
		अन्यथा
			err |= __copy_to_user(पंचांग_v_regs,
					      &tsk->thपढ़ो.ckvr_state,
					      33 * माप(vector128));

		/* set MSR_VEC in the MSR value in the frame to indicate
		 * that sc->v_reg contains valid data.
		 */
		msr |= MSR_VEC;
	पूर्ण
	/* We always copy to/from vrsave, it's 0 if we don't have or don't
	 * use altivec.
	 */
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		tsk->thपढ़ो.ckvrsave = mfspr(SPRN_VRSAVE);
	err |= __put_user(tsk->thपढ़ो.ckvrsave, (u32 __user *)&v_regs[33]);
	अगर (msr & MSR_VEC)
		err |= __put_user(tsk->thपढ़ो.vrsave,
				  (u32 __user *)&पंचांग_v_regs[33]);
	अन्यथा
		err |= __put_user(tsk->thपढ़ो.ckvrsave,
				  (u32 __user *)&पंचांग_v_regs[33]);

#अन्यथा /* CONFIG_ALTIVEC */
	err |= __put_user(0, &sc->v_regs);
	err |= __put_user(0, &पंचांग_sc->v_regs);
#पूर्ण_अगर /* CONFIG_ALTIVEC */

	/* copy fpr regs and fpscr */
	err |= copy_ckfpr_to_user(&sc->fp_regs, tsk);
	अगर (msr & MSR_FP)
		err |= copy_fpr_to_user(&पंचांग_sc->fp_regs, tsk);
	अन्यथा
		err |= copy_ckfpr_to_user(&पंचांग_sc->fp_regs, tsk);

#अगर_घोषित CONFIG_VSX
	/*
	 * Copy VSX low द्विगुनword to local buffer क्रम क्रमmatting,
	 * then out to userspace.  Update v_regs to poपूर्णांक after the
	 * VMX data.
	 */
	अगर (tsk->thपढ़ो.used_vsr) अणु
		v_regs += ELF_NVRREG;
		पंचांग_v_regs += ELF_NVRREG;

		err |= copy_ckvsx_to_user(v_regs, tsk);

		अगर (msr & MSR_VSX)
			err |= copy_vsx_to_user(पंचांग_v_regs, tsk);
		अन्यथा
			err |= copy_ckvsx_to_user(पंचांग_v_regs, tsk);

		/* set MSR_VSX in the MSR value in the frame to
		 * indicate that sc->vs_reg) contains valid data.
		 */
		msr |= MSR_VSX;
	पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

	err |= __put_user(&sc->gp_regs, &sc->regs);
	err |= __put_user(&पंचांग_sc->gp_regs, &पंचांग_sc->regs);
	err |= __copy_to_user(&पंचांग_sc->gp_regs, regs, GP_REGS_SIZE);
	err |= __copy_to_user(&sc->gp_regs,
			      &tsk->thपढ़ो.ckpt_regs, GP_REGS_SIZE);
	err |= __put_user(msr, &पंचांग_sc->gp_regs[PT_MSR]);
	err |= __put_user(msr, &sc->gp_regs[PT_MSR]);
	err |= __put_user(signr, &sc->संकेत);
	err |= __put_user(handler, &sc->handler);
	अगर (set != शून्य)
		err |=  __put_user(set->sig[0], &sc->oldmask);

	वापस err;
पूर्ण
#पूर्ण_अगर

/*
 * Restore the sigcontext from the संकेत frame.
 */
#घोषणा unsafe_restore_sigcontext(tsk, set, sig, sc, label) करो अणु	\
	अगर (__unsafe_restore_sigcontext(tsk, set, sig, sc))		\
		जाओ label;						\
पूर्ण जबतक (0)
अटल दीर्घ notrace __unsafe_restore_sigcontext(काष्ठा task_काष्ठा *tsk, sigset_t *set,
						पूर्णांक sig, काष्ठा sigcontext __user *sc)
अणु
#अगर_घोषित CONFIG_ALTIVEC
	elf_vrreg_t __user *v_regs;
#पूर्ण_अगर
	अचिन्हित दीर्घ save_r13 = 0;
	अचिन्हित दीर्घ msr;
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;
#अगर_घोषित CONFIG_VSX
	पूर्णांक i;
#पूर्ण_अगर

	BUG_ON(tsk != current);

	/* If this is not a संकेत वापस, we preserve the TLS in r13 */
	अगर (!sig)
		save_r13 = regs->gpr[13];

	/* copy the GPRs */
	unsafe_copy_from_user(regs->gpr, sc->gp_regs, माप(regs->gpr), efault_out);
	unsafe_get_user(regs->nip, &sc->gp_regs[PT_NIP], efault_out);
	/* get MSR separately, transfer the LE bit अगर करोing संकेत वापस */
	unsafe_get_user(msr, &sc->gp_regs[PT_MSR], efault_out);
	अगर (sig)
		regs->msr = (regs->msr & ~MSR_LE) | (msr & MSR_LE);
	unsafe_get_user(regs->orig_gpr3, &sc->gp_regs[PT_ORIG_R3], efault_out);
	unsafe_get_user(regs->ctr, &sc->gp_regs[PT_CTR], efault_out);
	unsafe_get_user(regs->link, &sc->gp_regs[PT_LNK], efault_out);
	unsafe_get_user(regs->xer, &sc->gp_regs[PT_XER], efault_out);
	unsafe_get_user(regs->ccr, &sc->gp_regs[PT_CCR], efault_out);
	/* Don't allow userspace to set SOFTE */
	set_trap_norestart(regs);
	unsafe_get_user(regs->dar, &sc->gp_regs[PT_DAR], efault_out);
	unsafe_get_user(regs->dsisr, &sc->gp_regs[PT_DSISR], efault_out);
	unsafe_get_user(regs->result, &sc->gp_regs[PT_RESULT], efault_out);

	अगर (!sig)
		regs->gpr[13] = save_r13;
	अगर (set != शून्य)
		unsafe_get_user(set->sig[0], &sc->oldmask, efault_out);

	/*
	 * Force reload of FP/VEC.
	 * This has to be करोne beक्रमe copying stuff पूर्णांकo tsk->thपढ़ो.fpr/vr
	 * क्रम the reasons explained in the previous comment.
	 */
	regs->msr &= ~(MSR_FP | MSR_FE0 | MSR_FE1 | MSR_VEC | MSR_VSX);

#अगर_घोषित CONFIG_ALTIVEC
	unsafe_get_user(v_regs, &sc->v_regs, efault_out);
	अगर (v_regs && !access_ok(v_regs, 34 * माप(vector128)))
		वापस -EFAULT;
	/* Copy 33 vec रेजिस्टरs (vr0..31 and vscr) from the stack */
	अगर (v_regs != शून्य && (msr & MSR_VEC) != 0) अणु
		unsafe_copy_from_user(&tsk->thपढ़ो.vr_state, v_regs,
				      33 * माप(vector128), efault_out);
		tsk->thपढ़ो.used_vr = true;
	पूर्ण अन्यथा अगर (tsk->thपढ़ो.used_vr) अणु
		स_रखो(&tsk->thपढ़ो.vr_state, 0, 33 * माप(vector128));
	पूर्ण
	/* Always get VRSAVE back */
	अगर (v_regs != शून्य)
		unsafe_get_user(tsk->thपढ़ो.vrsave, (u32 __user *)&v_regs[33], efault_out);
	अन्यथा
		tsk->thपढ़ो.vrsave = 0;
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		mtspr(SPRN_VRSAVE, tsk->thपढ़ो.vrsave);
#पूर्ण_अगर /* CONFIG_ALTIVEC */
	/* restore भग्नing poपूर्णांक */
	unsafe_copy_fpr_from_user(tsk, &sc->fp_regs, efault_out);
#अगर_घोषित CONFIG_VSX
	/*
	 * Get additional VSX data. Update v_regs to poपूर्णांक after the
	 * VMX data.  Copy VSX low द्विगुनword from userspace to local
	 * buffer क्रम क्रमmatting, then पूर्णांकo the taskकाष्ठा.
	 */
	v_regs += ELF_NVRREG;
	अगर ((msr & MSR_VSX) != 0) अणु
		unsafe_copy_vsx_from_user(tsk, v_regs, efault_out);
		tsk->thपढ़ो.used_vsr = true;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 32 ; i++)
			tsk->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET] = 0;
	पूर्ण
#पूर्ण_अगर
	वापस 0;

efault_out:
	वापस -EFAULT;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
/*
 * Restore the two sigcontexts from the frame of a transactional processes.
 */

अटल दीर्घ restore_पंचांग_sigcontexts(काष्ठा task_काष्ठा *tsk,
				   काष्ठा sigcontext __user *sc,
				   काष्ठा sigcontext __user *पंचांग_sc)
अणु
#अगर_घोषित CONFIG_ALTIVEC
	elf_vrreg_t __user *v_regs, *पंचांग_v_regs;
#पूर्ण_अगर
	अचिन्हित दीर्घ err = 0;
	अचिन्हित दीर्घ msr;
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;
#अगर_घोषित CONFIG_VSX
	पूर्णांक i;
#पूर्ण_अगर

	BUG_ON(tsk != current);

	अगर (पंचांग_suspend_disabled)
		वापस -EINVAL;

	/* copy the GPRs */
	err |= __copy_from_user(regs->gpr, पंचांग_sc->gp_regs, माप(regs->gpr));
	err |= __copy_from_user(&tsk->thपढ़ो.ckpt_regs, sc->gp_regs,
				माप(regs->gpr));

	/*
	 * TFHAR is restored from the checkpoपूर्णांकed 'wound-back' ucontext's NIP.
	 * TEXASR was set by the संकेत delivery reclaim, as was TFIAR.
	 * Users करोing anything abhorrent like thपढ़ो-चयनing w/ संकेतs क्रम
	 * TM-Suspended code will have to back TEXASR/TFIAR up themselves.
	 * For the हाल of getting a संकेत and simply वापसing from it,
	 * we करोn't need to re-copy them here.
	 */
	err |= __get_user(regs->nip, &पंचांग_sc->gp_regs[PT_NIP]);
	err |= __get_user(tsk->thपढ़ो.पंचांग_tfhar, &sc->gp_regs[PT_NIP]);

	/* get MSR separately, transfer the LE bit अगर करोing संकेत वापस */
	err |= __get_user(msr, &sc->gp_regs[PT_MSR]);
	/* Don't allow reserved mode. */
	अगर (MSR_TM_RESV(msr))
		वापस -EINVAL;

	/* pull in MSR LE from user context */
	regs->msr = (regs->msr & ~MSR_LE) | (msr & MSR_LE);

	/* The following non-GPR non-FPR non-VR state is also checkpoपूर्णांकed: */
	err |= __get_user(regs->ctr, &पंचांग_sc->gp_regs[PT_CTR]);
	err |= __get_user(regs->link, &पंचांग_sc->gp_regs[PT_LNK]);
	err |= __get_user(regs->xer, &पंचांग_sc->gp_regs[PT_XER]);
	err |= __get_user(regs->ccr, &पंचांग_sc->gp_regs[PT_CCR]);
	err |= __get_user(tsk->thपढ़ो.ckpt_regs.ctr,
			  &sc->gp_regs[PT_CTR]);
	err |= __get_user(tsk->thपढ़ो.ckpt_regs.link,
			  &sc->gp_regs[PT_LNK]);
	err |= __get_user(tsk->thपढ़ो.ckpt_regs.xer,
			  &sc->gp_regs[PT_XER]);
	err |= __get_user(tsk->thपढ़ो.ckpt_regs.ccr,
			  &sc->gp_regs[PT_CCR]);
	/* Don't allow userspace to set SOFTE */
	set_trap_norestart(regs);
	/* These regs are not checkpoपूर्णांकed; they can go in 'regs'. */
	err |= __get_user(regs->dar, &sc->gp_regs[PT_DAR]);
	err |= __get_user(regs->dsisr, &sc->gp_regs[PT_DSISR]);
	err |= __get_user(regs->result, &sc->gp_regs[PT_RESULT]);

	/*
	 * Force reload of FP/VEC.
	 * This has to be करोne beक्रमe copying stuff पूर्णांकo tsk->thपढ़ो.fpr/vr
	 * क्रम the reasons explained in the previous comment.
	 */
	regs->msr &= ~(MSR_FP | MSR_FE0 | MSR_FE1 | MSR_VEC | MSR_VSX);

#अगर_घोषित CONFIG_ALTIVEC
	err |= __get_user(v_regs, &sc->v_regs);
	err |= __get_user(पंचांग_v_regs, &पंचांग_sc->v_regs);
	अगर (err)
		वापस err;
	अगर (v_regs && !access_ok(v_regs, 34 * माप(vector128)))
		वापस -EFAULT;
	अगर (पंचांग_v_regs && !access_ok(पंचांग_v_regs, 34 * माप(vector128)))
		वापस -EFAULT;
	/* Copy 33 vec रेजिस्टरs (vr0..31 and vscr) from the stack */
	अगर (v_regs != शून्य && पंचांग_v_regs != शून्य && (msr & MSR_VEC) != 0) अणु
		err |= __copy_from_user(&tsk->thपढ़ो.ckvr_state, v_regs,
					33 * माप(vector128));
		err |= __copy_from_user(&tsk->thपढ़ो.vr_state, पंचांग_v_regs,
					33 * माप(vector128));
		current->thपढ़ो.used_vr = true;
	पूर्ण
	अन्यथा अगर (tsk->thपढ़ो.used_vr) अणु
		स_रखो(&tsk->thपढ़ो.vr_state, 0, 33 * माप(vector128));
		स_रखो(&tsk->thपढ़ो.ckvr_state, 0, 33 * माप(vector128));
	पूर्ण
	/* Always get VRSAVE back */
	अगर (v_regs != शून्य && पंचांग_v_regs != शून्य) अणु
		err |= __get_user(tsk->thपढ़ो.ckvrsave,
				  (u32 __user *)&v_regs[33]);
		err |= __get_user(tsk->thपढ़ो.vrsave,
				  (u32 __user *)&पंचांग_v_regs[33]);
	पूर्ण
	अन्यथा अणु
		tsk->thपढ़ो.vrsave = 0;
		tsk->thपढ़ो.ckvrsave = 0;
	पूर्ण
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		mtspr(SPRN_VRSAVE, tsk->thपढ़ो.vrsave);
#पूर्ण_अगर /* CONFIG_ALTIVEC */
	/* restore भग्नing poपूर्णांक */
	err |= copy_fpr_from_user(tsk, &पंचांग_sc->fp_regs);
	err |= copy_ckfpr_from_user(tsk, &sc->fp_regs);
#अगर_घोषित CONFIG_VSX
	/*
	 * Get additional VSX data. Update v_regs to poपूर्णांक after the
	 * VMX data.  Copy VSX low द्विगुनword from userspace to local
	 * buffer क्रम क्रमmatting, then पूर्णांकo the taskकाष्ठा.
	 */
	अगर (v_regs && ((msr & MSR_VSX) != 0)) अणु
		v_regs += ELF_NVRREG;
		पंचांग_v_regs += ELF_NVRREG;
		err |= copy_vsx_from_user(tsk, पंचांग_v_regs);
		err |= copy_ckvsx_from_user(tsk, v_regs);
		tsk->thपढ़ो.used_vsr = true;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 32 ; i++) अणु
			tsk->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET] = 0;
			tsk->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET] = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	पंचांग_enable();
	/* Make sure the transaction is marked as failed */
	tsk->thपढ़ो.पंचांग_texasr |= TEXASR_FS;

	/*
	 * Disabling preemption, since it is unsafe to be preempted
	 * with MSR[TS] set without recheckpoपूर्णांकing.
	 */
	preempt_disable();

	/* pull in MSR TS bits from user context */
	regs->msr |= msr & MSR_TS_MASK;

	/*
	 * Ensure that TM is enabled in regs->msr beक्रमe we leave the संकेत
	 * handler. It could be the हाल that (a) user disabled the TM bit
	 * through the manipulation of the MSR bits in uc_mcontext or (b) the
	 * TM bit was disabled because a sufficient number of context चयनes
	 * happened whilst in the संकेत handler and load_पंचांग overflowed,
	 * disabling the TM bit. In either हाल we can end up with an illegal
	 * TM state leading to a TM Bad Thing when we वापस to userspace.
	 *
	 * CAUTION:
	 * After regs->MSR[TS] being updated, make sure that get_user(),
	 * put_user() or similar functions are *not* called. These
	 * functions can generate page faults which will cause the process
	 * to be de-scheduled with MSR[TS] set but without calling
	 * पंचांग_recheckpoपूर्णांक(). This can cause a bug.
	 */
	regs->msr |= MSR_TM;

	/* This loads the checkpoपूर्णांकed FP/VEC state, अगर used */
	पंचांग_recheckpoपूर्णांक(&tsk->thपढ़ो);

	msr_check_and_set(msr & (MSR_FP | MSR_VEC));
	अगर (msr & MSR_FP) अणु
		load_fp_state(&tsk->thपढ़ो.fp_state);
		regs->msr |= (MSR_FP | tsk->thपढ़ो.fpexc_mode);
	पूर्ण
	अगर (msr & MSR_VEC) अणु
		load_vr_state(&tsk->thपढ़ो.vr_state);
		regs->msr |= MSR_VEC;
	पूर्ण

	preempt_enable();

	वापस err;
पूर्ण
#अन्यथा /* !CONFIG_PPC_TRANSACTIONAL_MEM */
अटल दीर्घ restore_पंचांग_sigcontexts(काष्ठा task_काष्ठा *tsk, काष्ठा sigcontext __user *sc,
				   काष्ठा sigcontext __user *पंचांग_sc)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

/*
 * Setup the trampoline code on the stack
 */
अटल दीर्घ setup_trampoline(अचिन्हित पूर्णांक syscall, अचिन्हित पूर्णांक __user *tramp)
अणु
	पूर्णांक i;
	दीर्घ err = 0;

	/* bctrl # call the handler */
	err |= __put_user(PPC_INST_BCTRL, &tramp[0]);
	/* addi r1, r1, __SIGNAL_FRAMESIZE  # Pop the dummy stackframe */
	err |= __put_user(PPC_INST_ADDI | __PPC_RT(R1) | __PPC_RA(R1) |
			  (__SIGNAL_FRAMESIZE & 0xffff), &tramp[1]);
	/* li r0, __NR_[rt_]sigवापस| */
	err |= __put_user(PPC_INST_ADDI | (syscall & 0xffff), &tramp[2]);
	/* sc */
	err |= __put_user(PPC_INST_SC, &tramp[3]);

	/* Minimal traceback info */
	क्रम (i=TRAMP_TRACEBACK; i < TRAMP_SIZE ;i++)
		err |= __put_user(0, &tramp[i]);

	अगर (!err)
		flush_icache_range((अचिन्हित दीर्घ) &tramp[0],
			   (अचिन्हित दीर्घ) &tramp[TRAMP_SIZE]);

	वापस err;
पूर्ण

/*
 * Userspace code may pass a ucontext which करोesn't include VSX added
 * at the end.  We need to check क्रम this हाल.
 */
#घोषणा UCONTEXTSIZEWITHOUTVSX \
		(माप(काष्ठा ucontext) - 32*माप(दीर्घ))

/*
 * Handle अणुget,set,swapपूर्ण_context operations
 */
SYSCALL_DEFINE3(swapcontext, काष्ठा ucontext __user *, old_ctx,
		काष्ठा ucontext __user *, new_ctx, दीर्घ, ctx_size)
अणु
	sigset_t set;
	अचिन्हित दीर्घ new_msr = 0;
	पूर्णांक ctx_has_vsx_region = 0;

	अगर (new_ctx &&
	    get_user(new_msr, &new_ctx->uc_mcontext.gp_regs[PT_MSR]))
		वापस -EFAULT;
	/*
	 * Check that the context is not smaller than the original
	 * size (with VMX but without VSX)
	 */
	अगर (ctx_size < UCONTEXTSIZEWITHOUTVSX)
		वापस -EINVAL;
	/*
	 * If the new context state sets the MSR VSX bits but
	 * it करोesn't provide VSX state.
	 */
	अगर ((ctx_size < माप(काष्ठा ucontext)) &&
	    (new_msr & MSR_VSX))
		वापस -EINVAL;
	/* Does the context have enough room to store VSX data? */
	अगर (ctx_size >= माप(काष्ठा ucontext))
		ctx_has_vsx_region = 1;

	अगर (old_ctx != शून्य) अणु
		prepare_setup_sigcontext(current);
		अगर (!user_ग_लिखो_access_begin(old_ctx, ctx_size))
			वापस -EFAULT;

		unsafe_setup_sigcontext(&old_ctx->uc_mcontext, current, 0, शून्य,
					0, ctx_has_vsx_region, efault_out);
		unsafe_copy_to_user(&old_ctx->uc_sigmask, &current->blocked,
				    माप(sigset_t), efault_out);

		user_ग_लिखो_access_end();
	पूर्ण
	अगर (new_ctx == शून्य)
		वापस 0;
	अगर (!access_ok(new_ctx, ctx_size) ||
	    fault_in_pages_पढ़ोable((u8 __user *)new_ctx, ctx_size))
		वापस -EFAULT;

	/*
	 * If we get a fault copying the context पूर्णांकo the kernel's
	 * image of the user's registers, we can't just वापस -EFAULT
	 * because the user's रेजिस्टरs will be corrupted.  For instance
	 * the NIP value may have been updated but not some of the
	 * other रेजिस्टरs.  Given that we have करोne the access_ok
	 * and successfully पढ़ो the first and last bytes of the region
	 * above, this should only happen in an out-of-memory situation
	 * or अगर another thपढ़ो unmaps the region containing the context.
	 * We समाप्त the task with a संक_अंश in this situation.
	 */

	अगर (__get_user_sigset(&set, &new_ctx->uc_sigmask))
		करो_निकास(संक_अंश);
	set_current_blocked(&set);

	अगर (!user_पढ़ो_access_begin(new_ctx, ctx_size))
		वापस -EFAULT;
	अगर (__unsafe_restore_sigcontext(current, शून्य, 0, &new_ctx->uc_mcontext)) अणु
		user_पढ़ो_access_end();
		करो_निकास(संक_अंश);
	पूर्ण
	user_पढ़ो_access_end();

	/* This वापसs like rt_sigवापस */
	set_thपढ़ो_flag(TIF_RESTOREALL);
	वापस 0;

efault_out:
	user_ग_लिखो_access_end();
	वापस -EFAULT;
पूर्ण


/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 */

SYSCALL_DEFINE0(rt_sigवापस)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा ucontext __user *uc = (काष्ठा ucontext __user *)regs->gpr[1];
	sigset_t set;
	अचिन्हित दीर्घ msr;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	अगर (!access_ok(uc, माप(*uc)))
		जाओ badframe;

	अगर (__get_user_sigset(&set, &uc->uc_sigmask))
		जाओ badframe;
	set_current_blocked(&set);

	अगर (IS_ENABLED(CONFIG_PPC_TRANSACTIONAL_MEM)) अणु
		/*
		 * If there is a transactional state then throw it away.
		 * The purpose of a sigवापस is to destroy all traces of the
		 * संकेत frame, this includes any transactional state created
		 * within in. We only check क्रम suspended as we can never be
		 * active in the kernel, we are active, there is nothing better to
		 * करो than go ahead and Bad Thing later.
		 * The cause is not important as there will never be a
		 * recheckpoपूर्णांक so it's not user visible.
		 */
		अगर (MSR_TM_SUSPENDED(mfmsr()))
			पंचांग_reclaim_current(0);

		/*
		 * Disable MSR[TS] bit also, so, अगर there is an exception in the
		 * code below (as a page fault in copy_ckvsx_to_user()), it करोes
		 * not recheckpoपूर्णांक this task अगर there was a context चयन inside
		 * the exception.
		 *
		 * A major page fault can indirectly call schedule(). A reschedule
		 * process in the middle of an exception can have a side effect
		 * (Changing the CPU MSR[TS] state), since schedule() is called
		 * with the CPU MSR[TS] disable and वापसs with MSR[TS]=Suspended
		 * (चयन_to() calls पंचांग_recheckpoपूर्णांक() क्रम the 'new' process). In
		 * this हाल, the process जारीs to be the same in the CPU, but
		 * the CPU state just changed.
		 *
		 * This can cause a TM Bad Thing, since the MSR in the stack will
		 * have the MSR[TS]=0, and this is what will be used to RFID.
		 *
		 * Clearing MSR[TS] state here will aव्योम a recheckpoपूर्णांक अगर there
		 * is any process reschedule in kernel space. The MSR[TS] state
		 * करोes not need to be saved also, since it will be replaced with
		 * the MSR[TS] that came from user context later, at
		 * restore_पंचांग_sigcontexts.
		 */
		regs->msr &= ~MSR_TS_MASK;

		अगर (__get_user(msr, &uc->uc_mcontext.gp_regs[PT_MSR]))
			जाओ badframe;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PPC_TRANSACTIONAL_MEM) && MSR_TM_ACTIVE(msr)) अणु
		/* We recheckpoपूर्णांक on वापस. */
		काष्ठा ucontext __user *uc_transact;

		/* Trying to start TM on non TM प्रणाली */
		अगर (!cpu_has_feature(CPU_FTR_TM))
			जाओ badframe;

		अगर (__get_user(uc_transact, &uc->uc_link))
			जाओ badframe;
		अगर (restore_पंचांग_sigcontexts(current, &uc->uc_mcontext,
					   &uc_transact->uc_mcontext))
			जाओ badframe;
	पूर्ण अन्यथा अणु
		/*
		 * Fall through, क्रम non-TM restore
		 *
		 * Unset MSR[TS] on the thपढ़ो regs since MSR from user
		 * context करोes not have MSR active, and recheckpoपूर्णांक was
		 * not called since restore_पंचांग_sigcontexts() was not called
		 * also.
		 *
		 * If not unsetting it, the code can RFID to userspace with
		 * MSR[TS] set, but without CPU in the proper state,
		 * causing a TM bad thing.
		 */
		current->thपढ़ो.regs->msr &= ~MSR_TS_MASK;
		अगर (!user_पढ़ो_access_begin(&uc->uc_mcontext, माप(uc->uc_mcontext)))
			जाओ badframe;

		unsafe_restore_sigcontext(current, शून्य, 1, &uc->uc_mcontext,
					  badframe_block);

		user_पढ़ो_access_end();
	पूर्ण

	अगर (restore_altstack(&uc->uc_stack))
		जाओ badframe;

	set_thपढ़ो_flag(TIF_RESTOREALL);
	वापस 0;

badframe_block:
	user_पढ़ो_access_end();
badframe:
	संकेत_fault(current, regs, "rt_sigreturn", uc);

	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

पूर्णांक handle_rt_संकेत64(काष्ठा kसंकेत *ksig, sigset_t *set,
		काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा rt_sigframe __user *frame;
	अचिन्हित दीर्घ newsp = 0;
	दीर्घ err = 0;
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;
	/* Save the thपढ़ो's msr beक्रमe get_पंचांग_stackpoपूर्णांकer() changes it */
	अचिन्हित दीर्घ msr = regs->msr;

	frame = get_sigframe(ksig, tsk, माप(*frame), 0);

	/*
	 * This only applies when calling unsafe_setup_sigcontext() and must be
	 * called beक्रमe खोलोing the uaccess winकरोw.
	 */
	अगर (!MSR_TM_ACTIVE(msr))
		prepare_setup_sigcontext(tsk);

	अगर (!user_ग_लिखो_access_begin(frame, माप(*frame)))
		जाओ badframe;

	unsafe_put_user(&frame->info, &frame->pinfo, badframe_block);
	unsafe_put_user(&frame->uc, &frame->puc, badframe_block);

	/* Create the ucontext.  */
	unsafe_put_user(0, &frame->uc.uc_flags, badframe_block);
	unsafe_save_altstack(&frame->uc.uc_stack, regs->gpr[1], badframe_block);

	अगर (MSR_TM_ACTIVE(msr)) अणु
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
		/* The ucontext_t passed to userland poपूर्णांकs to the second
		 * ucontext_t (क्रम transactional state) with its uc_link ptr.
		 */
		unsafe_put_user(&frame->uc_transact, &frame->uc.uc_link, badframe_block);

		user_ग_लिखो_access_end();

		err |= setup_पंचांग_sigcontexts(&frame->uc.uc_mcontext,
					    &frame->uc_transact.uc_mcontext,
					    tsk, ksig->sig, शून्य,
					    (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler,
					    msr);

		अगर (!user_ग_लिखो_access_begin(&frame->uc.uc_sigmask,
					     माप(frame->uc.uc_sigmask)))
			जाओ badframe;

#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		unsafe_put_user(0, &frame->uc.uc_link, badframe_block);
		unsafe_setup_sigcontext(&frame->uc.uc_mcontext, tsk, ksig->sig,
					शून्य, (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler,
					1, badframe_block);
	पूर्ण

	unsafe_copy_to_user(&frame->uc.uc_sigmask, set, माप(*set), badframe_block);
	user_ग_लिखो_access_end();

	/* Save the siginfo outside of the unsafe block. */
	अगर (copy_siginfo_to_user(&frame->info, &ksig->info))
		जाओ badframe;

	/* Make sure संकेत handler करोesn't get spurious FP exceptions */
	tsk->thपढ़ो.fp_state.fpscr = 0;

	/* Set up to वापस from userspace. */
	अगर (tsk->mm->context.vdso) अणु
		regs->nip = VDSO64_SYMBOL(tsk->mm->context.vdso, sigtramp_rt64);
	पूर्ण अन्यथा अणु
		err |= setup_trampoline(__NR_rt_sigवापस, &frame->tramp[0]);
		अगर (err)
			जाओ badframe;
		regs->nip = (अचिन्हित दीर्घ) &frame->tramp[0];
	पूर्ण

	/* Allocate a dummy caller frame क्रम the संकेत handler. */
	newsp = ((अचिन्हित दीर्घ)frame) - __SIGNAL_FRAMESIZE;
	err |= put_user(regs->gpr[1], (अचिन्हित दीर्घ __user *)newsp);

	/* Set up "regs" so we "return" to the संकेत handler. */
	अगर (is_elf2_task()) अणु
		regs->ctr = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
		regs->gpr[12] = regs->ctr;
	पूर्ण अन्यथा अणु
		/* Handler is *really* a poपूर्णांकer to the function descriptor क्रम
		 * the संकेत routine.  The first entry in the function
		 * descriptor is the entry address of संकेत and the second
		 * entry is the TOC value we need to use.
		 */
		func_descr_t __user *funct_desc_ptr =
			(func_descr_t __user *) ksig->ka.sa.sa_handler;

		err |= get_user(regs->ctr, &funct_desc_ptr->entry);
		err |= get_user(regs->gpr[2], &funct_desc_ptr->toc);
	पूर्ण

	/* enter the संकेत handler in native-endian mode */
	regs->msr &= ~MSR_LE;
	regs->msr |= (MSR_KERNEL & MSR_LE);
	regs->gpr[1] = newsp;
	regs->gpr[3] = ksig->sig;
	regs->result = 0;
	अगर (ksig->ka.sa.sa_flags & SA_SIGINFO) अणु
		err |= get_user(regs->gpr[4], (अचिन्हित दीर्घ __user *)&frame->pinfo);
		err |= get_user(regs->gpr[5], (अचिन्हित दीर्घ __user *)&frame->puc);
		regs->gpr[6] = (अचिन्हित दीर्घ) frame;
	पूर्ण अन्यथा अणु
		regs->gpr[4] = (अचिन्हित दीर्घ)&frame->uc.uc_mcontext;
	पूर्ण
	अगर (err)
		जाओ badframe;

	वापस 0;

badframe_block:
	user_ग_लिखो_access_end();
badframe:
	संकेत_fault(current, regs, "handle_rt_signal64", frame);

	वापस 1;
पूर्ण
