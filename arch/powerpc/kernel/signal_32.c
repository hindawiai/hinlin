<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Signal handling क्रम 32bit PPC and 32bit tasks on 64bit PPC
 *
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 * Copyright (C) 2001 IBM
 * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
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
#समावेश <linux/elf.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/syscalls.h>
#अगर_घोषित CONFIG_PPC64
#समावेश <linux/compat.h>
#अन्यथा
#समावेश <linux/रुको.h>
#समावेश <linux/unistd.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tty.h>
#समावेश <linux/binfmts.h>
#पूर्ण_अगर

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/पंचांग.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#अगर_घोषित CONFIG_PPC64
#समावेश "ppc32.h"
#समावेश <यंत्र/unistd.h>
#अन्यथा
#समावेश <यंत्र/ucontext.h>
#पूर्ण_अगर

#समावेश "signal.h"


#अगर_घोषित CONFIG_PPC64
#घोषणा old_sigaction	old_sigaction32
#घोषणा sigcontext	sigcontext32
#घोषणा mcontext	mcontext32
#घोषणा ucontext	ucontext32

/*
 * Userspace code may pass a ucontext which करोesn't include VSX added
 * at the end.  We need to check क्रम this हाल.
 */
#घोषणा UCONTEXTSIZEWITHOUTVSX \
		(माप(काष्ठा ucontext) - माप(elf_vsrreghalf_t32))

/*
 * Returning 0 means we वापस to userspace via
 * ret_from_except and thus restore all user
 * रेजिस्टरs from *regs.  This is what we need
 * to करो when a संकेत has been delivered.
 */

#घोषणा GP_REGS_SIZE	min(माप(elf_gregset_t32), माप(काष्ठा pt_regs32))
#अघोषित __SIGNAL_FRAMESIZE
#घोषणा __SIGNAL_FRAMESIZE	__SIGNAL_FRAMESIZE32
#अघोषित ELF_NVRREG
#घोषणा ELF_NVRREG	ELF_NVRREG32

/*
 * Functions क्रम flipping sigsets (thanks to brain dead generic
 * implementation that makes things simple क्रम little endian only)
 */
#घोषणा unsafe_put_sigset_t	unsafe_put_compat_sigset
#घोषणा unsafe_get_sigset_t	unsafe_get_compat_sigset

#घोषणा to_user_ptr(p)		ptr_to_compat(p)
#घोषणा from_user_ptr(p)	compat_ptr(p)

अटल __always_अंतरभूत पूर्णांक
__unsafe_save_general_regs(काष्ठा pt_regs *regs, काष्ठा mcontext __user *frame)
अणु
	elf_greg_t64 *gregs = (elf_greg_t64 *)regs;
	पूर्णांक val, i;

	क्रम (i = 0; i <= PT_RESULT; i ++) अणु
		/* Force usr to alway see softe as 1 (पूर्णांकerrupts enabled) */
		अगर (i == PT_SOFTE)
			val = 1;
		अन्यथा
			val = gregs[i];

		unsafe_put_user(val, &frame->mc_gregs[i], failed);
	पूर्ण
	वापस 0;

failed:
	वापस 1;
पूर्ण

अटल __always_अंतरभूत पूर्णांक
__unsafe_restore_general_regs(काष्ठा pt_regs *regs, काष्ठा mcontext __user *sr)
अणु
	elf_greg_t64 *gregs = (elf_greg_t64 *)regs;
	पूर्णांक i;

	क्रम (i = 0; i <= PT_RESULT; i++) अणु
		अगर ((i == PT_MSR) || (i == PT_SOFTE))
			जारी;
		unsafe_get_user(gregs[i], &sr->mc_gregs[i], failed);
	पूर्ण
	वापस 0;

failed:
	वापस 1;
पूर्ण

#अन्यथा /* CONFIG_PPC64 */

#घोषणा GP_REGS_SIZE	min(माप(elf_gregset_t), माप(काष्ठा pt_regs))

#घोषणा unsafe_put_sigset_t(uset, set, label) करो अणु			\
	sigset_t __user *__us = uset	;				\
	स्थिर sigset_t *__s = set;					\
									\
	unsafe_copy_to_user(__us, __s, माप(*__us), label);		\
पूर्ण जबतक (0)

#घोषणा unsafe_get_sigset_t	unsafe_get_user_sigset

#घोषणा to_user_ptr(p)		((अचिन्हित दीर्घ)(p))
#घोषणा from_user_ptr(p)	((व्योम __user *)(p))

अटल __always_अंतरभूत पूर्णांक
__unsafe_save_general_regs(काष्ठा pt_regs *regs, काष्ठा mcontext __user *frame)
अणु
	unsafe_copy_to_user(&frame->mc_gregs, regs, GP_REGS_SIZE, failed);
	वापस 0;

failed:
	वापस 1;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक __unsafe_restore_general_regs(काष्ठा pt_regs *regs, काष्ठा mcontext __user *sr)
अणु
	/* copy up to but not including MSR */
	unsafe_copy_from_user(regs, &sr->mc_gregs, PT_MSR * माप(elf_greg_t), failed);

	/* copy from orig_r3 (the word after the MSR) up to the end */
	unsafe_copy_from_user(&regs->orig_gpr3, &sr->mc_gregs[PT_ORIG_R3],
			      GP_REGS_SIZE - PT_ORIG_R3 * माप(elf_greg_t), failed);

	वापस 0;

failed:
	वापस 1;
पूर्ण
#पूर्ण_अगर

#घोषणा unsafe_save_general_regs(regs, frame, label) करो अणु	\
	अगर (__unsafe_save_general_regs(regs, frame))		\
		जाओ label;					\
पूर्ण जबतक (0)

#घोषणा unsafe_restore_general_regs(regs, frame, label) करो अणु	\
	अगर (__unsafe_restore_general_regs(regs, frame))		\
		जाओ label;					\
पूर्ण जबतक (0)

/*
 * When we have संकेतs to deliver, we set up on the
 * user stack, going करोwn from the original stack poपूर्णांकer:
 *	an ABI gap of 56 words
 *	an mcontext काष्ठा
 *	a sigcontext काष्ठा
 *	a gap of __SIGNAL_FRAMESIZE bytes
 *
 * Each of these things must be a multiple of 16 bytes in size. The following
 * काष्ठाure represent all of this except the __SIGNAL_FRAMESIZE gap
 *
 */
काष्ठा sigframe अणु
	काष्ठा sigcontext sctx;		/* the sigcontext */
	काष्ठा mcontext	mctx;		/* all the रेजिस्टर values */
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	काष्ठा sigcontext sctx_transact;
	काष्ठा mcontext	mctx_transact;
#पूर्ण_अगर
	/*
	 * Programs using the rs6000/xcoff abi can save up to 19 gp
	 * regs and 18 fp regs below sp beक्रमe decrementing it.
	 */
	पूर्णांक			abigap[56];
पूर्ण;

/*
 *  When we have rt संकेतs to deliver, we set up on the
 *  user stack, going करोwn from the original stack poपूर्णांकer:
 *	one rt_sigframe काष्ठा (siginfo + ucontext + ABI gap)
 *	a gap of __SIGNAL_FRAMESIZE+16 bytes
 *  (the +16 is to get the siginfo and ucontext in the same
 *  positions as in older kernels).
 *
 *  Each of these things must be a multiple of 16 bytes in size.
 *
 */
काष्ठा rt_sigframe अणु
#अगर_घोषित CONFIG_PPC64
	compat_siginfo_t info;
#अन्यथा
	काष्ठा siginfo info;
#पूर्ण_अगर
	काष्ठा ucontext	uc;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	काष्ठा ucontext	uc_transact;
#पूर्ण_अगर
	/*
	 * Programs using the rs6000/xcoff abi can save up to 19 gp
	 * regs and 18 fp regs below sp beक्रमe decrementing it.
	 */
	पूर्णांक			abigap[56];
पूर्ण;

/*
 * Save the current user रेजिस्टरs on the user stack.
 * We only save the altivec/spe रेजिस्टरs अगर the process has used
 * altivec/spe inकाष्ठाions at some poपूर्णांक.
 */
अटल व्योम prepare_save_user_regs(पूर्णांक ctx_has_vsx_region)
अणु
	/* Make sure भग्नing poपूर्णांक रेजिस्टरs are stored in regs */
	flush_fp_to_thपढ़ो(current);
#अगर_घोषित CONFIG_ALTIVEC
	अगर (current->thपढ़ो.used_vr)
		flush_altivec_to_thपढ़ो(current);
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		current->thपढ़ो.vrsave = mfspr(SPRN_VRSAVE);
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	अगर (current->thपढ़ो.used_vsr && ctx_has_vsx_region)
		flush_vsx_to_thपढ़ो(current);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPE
	अगर (current->thपढ़ो.used_spe)
		flush_spe_to_thपढ़ो(current);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __unsafe_save_user_regs(काष्ठा pt_regs *regs, काष्ठा mcontext __user *frame,
				   काष्ठा mcontext __user *पंचांग_frame, पूर्णांक ctx_has_vsx_region)
अणु
	अचिन्हित दीर्घ msr = regs->msr;

	/* save general रेजिस्टरs */
	unsafe_save_general_regs(regs, frame, failed);

#अगर_घोषित CONFIG_ALTIVEC
	/* save altivec रेजिस्टरs */
	अगर (current->thपढ़ो.used_vr) अणु
		unsafe_copy_to_user(&frame->mc_vregs, &current->thपढ़ो.vr_state,
				    ELF_NVRREG * माप(vector128), failed);
		/* set MSR_VEC in the saved MSR value to indicate that
		   frame->mc_vregs contains valid data */
		msr |= MSR_VEC;
	पूर्ण
	/* अन्यथा निश्चित((regs->msr & MSR_VEC) == 0) */

	/* We always copy to/from vrsave, it's 0 if we don't have or don't
	 * use altivec. Since VSCR only contains 32 bits saved in the least
	 * signअगरicant bits of a vector, we "cheat" and stuff VRSAVE in the
	 * most signअगरicant bits of that same vector. --BenH
	 * Note that the current VRSAVE value is in the SPR at this poपूर्णांक.
	 */
	unsafe_put_user(current->thपढ़ो.vrsave, (u32 __user *)&frame->mc_vregs[32],
			failed);
#पूर्ण_अगर /* CONFIG_ALTIVEC */
	unsafe_copy_fpr_to_user(&frame->mc_fregs, current, failed);

	/*
	 * Clear the MSR VSX bit to indicate there is no valid state attached
	 * to this context, except in the specअगरic हाल below where we set it.
	 */
	msr &= ~MSR_VSX;
#अगर_घोषित CONFIG_VSX
	/*
	 * Copy VSR 0-31 upper half from thपढ़ो_काष्ठा to local
	 * buffer, then ग_लिखो that to userspace.  Also set MSR_VSX in
	 * the saved MSR value to indicate that frame->mc_vregs
	 * contains valid data
	 */
	अगर (current->thपढ़ो.used_vsr && ctx_has_vsx_region) अणु
		unsafe_copy_vsx_to_user(&frame->mc_vsregs, current, failed);
		msr |= MSR_VSX;
	पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */
#अगर_घोषित CONFIG_SPE
	/* save spe रेजिस्टरs */
	अगर (current->thपढ़ो.used_spe) अणु
		unsafe_copy_to_user(&frame->mc_vregs, current->thपढ़ो.evr,
				    ELF_NEVRREG * माप(u32), failed);
		/* set MSR_SPE in the saved MSR value to indicate that
		   frame->mc_vregs contains valid data */
		msr |= MSR_SPE;
	पूर्ण
	/* अन्यथा निश्चित((regs->msr & MSR_SPE) == 0) */

	/* We always copy to/from spefscr */
	unsafe_put_user(current->thपढ़ो.spefscr,
			(u32 __user *)&frame->mc_vregs + ELF_NEVRREG, failed);
#पूर्ण_अगर /* CONFIG_SPE */

	unsafe_put_user(msr, &frame->mc_gregs[PT_MSR], failed);

	/* We need to ग_लिखो 0 the MSR top 32 bits in the पंचांग frame so that we
	 * can check it on the restore to see अगर TM is active
	 */
	अगर (पंचांग_frame)
		unsafe_put_user(0, &पंचांग_frame->mc_gregs[PT_MSR], failed);

	वापस 0;

failed:
	वापस 1;
पूर्ण

#घोषणा unsafe_save_user_regs(regs, frame, पंचांग_frame, has_vsx, label) करो अणु \
	अगर (__unsafe_save_user_regs(regs, frame, पंचांग_frame, has_vsx))	\
		जाओ label;						\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
/*
 * Save the current user रेजिस्टरs on the user stack.
 * We only save the altivec/spe रेजिस्टरs अगर the process has used
 * altivec/spe inकाष्ठाions at some poपूर्णांक.
 * We also save the transactional रेजिस्टरs to a second ucontext in the
 * frame.
 *
 * See __unsafe_save_user_regs() and संकेत_64.c:setup_पंचांग_sigcontexts().
 */
अटल व्योम prepare_save_पंचांग_user_regs(व्योम)
अणु
	WARN_ON(पंचांग_suspend_disabled);

#अगर_घोषित CONFIG_ALTIVEC
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		current->thपढ़ो.ckvrsave = mfspr(SPRN_VRSAVE);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPE
	अगर (current->thपढ़ो.used_spe)
		flush_spe_to_thपढ़ो(current);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक save_पंचांग_user_regs_unsafe(काष्ठा pt_regs *regs, काष्ठा mcontext __user *frame,
				    काष्ठा mcontext __user *पंचांग_frame, अचिन्हित दीर्घ msr)
अणु
	/* Save both sets of general रेजिस्टरs */
	unsafe_save_general_regs(&current->thपढ़ो.ckpt_regs, frame, failed);
	unsafe_save_general_regs(regs, पंचांग_frame, failed);

	/* Stash the top half of the 64bit MSR पूर्णांकo the 32bit MSR word
	 * of the transactional mcontext.  This way we have a backward-compatible
	 * MSR in the 'normal' (checkpoपूर्णांकed) mcontext and additionally one can
	 * also look at what type of transaction (T or S) was active at the
	 * समय of the संकेत.
	 */
	unsafe_put_user((msr >> 32), &पंचांग_frame->mc_gregs[PT_MSR], failed);

#अगर_घोषित CONFIG_ALTIVEC
	/* save altivec रेजिस्टरs */
	अगर (current->thपढ़ो.used_vr) अणु
		unsafe_copy_to_user(&frame->mc_vregs, &current->thपढ़ो.ckvr_state,
				    ELF_NVRREG * माप(vector128), failed);
		अगर (msr & MSR_VEC)
			unsafe_copy_to_user(&पंचांग_frame->mc_vregs,
					    &current->thपढ़ो.vr_state,
					    ELF_NVRREG * माप(vector128), failed);
		अन्यथा
			unsafe_copy_to_user(&पंचांग_frame->mc_vregs,
					    &current->thपढ़ो.ckvr_state,
					    ELF_NVRREG * माप(vector128), failed);

		/* set MSR_VEC in the saved MSR value to indicate that
		 * frame->mc_vregs contains valid data
		 */
		msr |= MSR_VEC;
	पूर्ण

	/* We always copy to/from vrsave, it's 0 if we don't have or don't
	 * use altivec. Since VSCR only contains 32 bits saved in the least
	 * signअगरicant bits of a vector, we "cheat" and stuff VRSAVE in the
	 * most signअगरicant bits of that same vector. --BenH
	 */
	unsafe_put_user(current->thपढ़ो.ckvrsave,
			(u32 __user *)&frame->mc_vregs[32], failed);
	अगर (msr & MSR_VEC)
		unsafe_put_user(current->thपढ़ो.vrsave,
				(u32 __user *)&पंचांग_frame->mc_vregs[32], failed);
	अन्यथा
		unsafe_put_user(current->thपढ़ो.ckvrsave,
				(u32 __user *)&पंचांग_frame->mc_vregs[32], failed);
#पूर्ण_अगर /* CONFIG_ALTIVEC */

	unsafe_copy_ckfpr_to_user(&frame->mc_fregs, current, failed);
	अगर (msr & MSR_FP)
		unsafe_copy_fpr_to_user(&पंचांग_frame->mc_fregs, current, failed);
	अन्यथा
		unsafe_copy_ckfpr_to_user(&पंचांग_frame->mc_fregs, current, failed);

#अगर_घोषित CONFIG_VSX
	/*
	 * Copy VSR 0-31 upper half from thपढ़ो_काष्ठा to local
	 * buffer, then ग_लिखो that to userspace.  Also set MSR_VSX in
	 * the saved MSR value to indicate that frame->mc_vregs
	 * contains valid data
	 */
	अगर (current->thपढ़ो.used_vsr) अणु
		unsafe_copy_ckvsx_to_user(&frame->mc_vsregs, current, failed);
		अगर (msr & MSR_VSX)
			unsafe_copy_vsx_to_user(&पंचांग_frame->mc_vsregs, current, failed);
		अन्यथा
			unsafe_copy_ckvsx_to_user(&पंचांग_frame->mc_vsregs, current, failed);

		msr |= MSR_VSX;
	पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */
#अगर_घोषित CONFIG_SPE
	/* SPE regs are not checkpoपूर्णांकed with TM, so this section is
	 * simply the same as in __unsafe_save_user_regs().
	 */
	अगर (current->thपढ़ो.used_spe) अणु
		unsafe_copy_to_user(&frame->mc_vregs, current->thपढ़ो.evr,
				    ELF_NEVRREG * माप(u32), failed);
		/* set MSR_SPE in the saved MSR value to indicate that
		 * frame->mc_vregs contains valid data */
		msr |= MSR_SPE;
	पूर्ण

	/* We always copy to/from spefscr */
	unsafe_put_user(current->thपढ़ो.spefscr,
			(u32 __user *)&frame->mc_vregs + ELF_NEVRREG, failed);
#पूर्ण_अगर /* CONFIG_SPE */

	unsafe_put_user(msr, &frame->mc_gregs[PT_MSR], failed);

	वापस 0;

failed:
	वापस 1;
पूर्ण
#अन्यथा
अटल व्योम prepare_save_पंचांग_user_regs(व्योम) अणु पूर्ण

अटल पूर्णांक save_पंचांग_user_regs_unsafe(काष्ठा pt_regs *regs, काष्ठा mcontext __user *frame,
				    काष्ठा mcontext __user *पंचांग_frame, अचिन्हित दीर्घ msr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा unsafe_save_पंचांग_user_regs(regs, frame, पंचांग_frame, msr, label) करो अणु \
	अगर (save_पंचांग_user_regs_unsafe(regs, frame, पंचांग_frame, msr))	\
		जाओ label;						\
पूर्ण जबतक (0)

/*
 * Restore the current user रेजिस्टर values from the user stack,
 * (except क्रम MSR).
 */
अटल दीर्घ restore_user_regs(काष्ठा pt_regs *regs,
			      काष्ठा mcontext __user *sr, पूर्णांक sig)
अणु
	अचिन्हित पूर्णांक save_r2 = 0;
	अचिन्हित दीर्घ msr;
#अगर_घोषित CONFIG_VSX
	पूर्णांक i;
#पूर्ण_अगर

	अगर (!user_पढ़ो_access_begin(sr, माप(*sr)))
		वापस 1;
	/*
	 * restore general रेजिस्टरs but not including MSR or SOFTE. Also
	 * take care of keeping r2 (TLS) पूर्णांकact अगर not a संकेत
	 */
	अगर (!sig)
		save_r2 = (अचिन्हित पूर्णांक)regs->gpr[2];
	unsafe_restore_general_regs(regs, sr, failed);
	set_trap_norestart(regs);
	unsafe_get_user(msr, &sr->mc_gregs[PT_MSR], failed);
	अगर (!sig)
		regs->gpr[2] = (अचिन्हित दीर्घ) save_r2;

	/* अगर करोing संकेत वापस, restore the previous little-endian mode */
	अगर (sig)
		regs->msr = (regs->msr & ~MSR_LE) | (msr & MSR_LE);

#अगर_घोषित CONFIG_ALTIVEC
	/*
	 * Force the process to reload the altivec रेजिस्टरs from
	 * current->thपढ़ो when it next करोes altivec inकाष्ठाions
	 */
	regs->msr &= ~MSR_VEC;
	अगर (msr & MSR_VEC) अणु
		/* restore altivec रेजिस्टरs from the stack */
		unsafe_copy_from_user(&current->thपढ़ो.vr_state, &sr->mc_vregs,
				      माप(sr->mc_vregs), failed);
		current->thपढ़ो.used_vr = true;
	पूर्ण अन्यथा अगर (current->thपढ़ो.used_vr)
		स_रखो(&current->thपढ़ो.vr_state, 0,
		       ELF_NVRREG * माप(vector128));

	/* Always get VRSAVE back */
	unsafe_get_user(current->thपढ़ो.vrsave, (u32 __user *)&sr->mc_vregs[32], failed);
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		mtspr(SPRN_VRSAVE, current->thपढ़ो.vrsave);
#पूर्ण_अगर /* CONFIG_ALTIVEC */
	unsafe_copy_fpr_from_user(current, &sr->mc_fregs, failed);

#अगर_घोषित CONFIG_VSX
	/*
	 * Force the process to reload the VSX रेजिस्टरs from
	 * current->thपढ़ो when it next करोes VSX inकाष्ठाion.
	 */
	regs->msr &= ~MSR_VSX;
	अगर (msr & MSR_VSX) अणु
		/*
		 * Restore altivec रेजिस्टरs from the stack to a local
		 * buffer, then ग_लिखो this out to the thपढ़ो_काष्ठा
		 */
		unsafe_copy_vsx_from_user(current, &sr->mc_vsregs, failed);
		current->thपढ़ो.used_vsr = true;
	पूर्ण अन्यथा अगर (current->thपढ़ो.used_vsr)
		क्रम (i = 0; i < 32 ; i++)
			current->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET] = 0;
#पूर्ण_अगर /* CONFIG_VSX */
	/*
	 * क्रमce the process to reload the FP रेजिस्टरs from
	 * current->thपढ़ो when it next करोes FP inकाष्ठाions
	 */
	regs->msr &= ~(MSR_FP | MSR_FE0 | MSR_FE1);

#अगर_घोषित CONFIG_SPE
	/* क्रमce the process to reload the spe रेजिस्टरs from
	   current->thपढ़ो when it next करोes spe inकाष्ठाions */
	regs->msr &= ~MSR_SPE;
	अगर (msr & MSR_SPE) अणु
		/* restore spe रेजिस्टरs from the stack */
		unsafe_copy_from_user(current->thपढ़ो.evr, &sr->mc_vregs,
				      ELF_NEVRREG * माप(u32), failed);
		current->thपढ़ो.used_spe = true;
	पूर्ण अन्यथा अगर (current->thपढ़ो.used_spe)
		स_रखो(current->thपढ़ो.evr, 0, ELF_NEVRREG * माप(u32));

	/* Always get SPEFSCR back */
	unsafe_get_user(current->thपढ़ो.spefscr, (u32 __user *)&sr->mc_vregs + ELF_NEVRREG, failed);
#पूर्ण_अगर /* CONFIG_SPE */

	user_पढ़ो_access_end();
	वापस 0;

failed:
	user_पढ़ो_access_end();
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
/*
 * Restore the current user रेजिस्टर values from the user stack, except क्रम
 * MSR, and recheckpoपूर्णांक the original checkpoपूर्णांकed रेजिस्टर state क्रम processes
 * in transactions.
 */
अटल दीर्घ restore_पंचांग_user_regs(काष्ठा pt_regs *regs,
				 काष्ठा mcontext __user *sr,
				 काष्ठा mcontext __user *पंचांग_sr)
अणु
	अचिन्हित दीर्घ msr, msr_hi;
#अगर_घोषित CONFIG_VSX
	पूर्णांक i;
#पूर्ण_अगर

	अगर (पंचांग_suspend_disabled)
		वापस 1;
	/*
	 * restore general रेजिस्टरs but not including MSR or SOFTE. Also
	 * take care of keeping r2 (TLS) पूर्णांकact अगर not a संकेत.
	 * See comment in संकेत_64.c:restore_पंचांग_sigcontexts();
	 * TFHAR is restored from the checkpoपूर्णांकed NIP; TEXASR and TFIAR
	 * were set by the संकेत delivery.
	 */
	अगर (!user_पढ़ो_access_begin(sr, माप(*sr)))
		वापस 1;

	unsafe_restore_general_regs(&current->thपढ़ो.ckpt_regs, sr, failed);
	unsafe_get_user(current->thपढ़ो.पंचांग_tfhar, &sr->mc_gregs[PT_NIP], failed);
	unsafe_get_user(msr, &sr->mc_gregs[PT_MSR], failed);

	/* Restore the previous little-endian mode */
	regs->msr = (regs->msr & ~MSR_LE) | (msr & MSR_LE);

#अगर_घोषित CONFIG_ALTIVEC
	regs->msr &= ~MSR_VEC;
	अगर (msr & MSR_VEC) अणु
		/* restore altivec रेजिस्टरs from the stack */
		unsafe_copy_from_user(&current->thपढ़ो.ckvr_state, &sr->mc_vregs,
				      माप(sr->mc_vregs), failed);
		current->thपढ़ो.used_vr = true;
	पूर्ण अन्यथा अगर (current->thपढ़ो.used_vr) अणु
		स_रखो(&current->thपढ़ो.vr_state, 0,
		       ELF_NVRREG * माप(vector128));
		स_रखो(&current->thपढ़ो.ckvr_state, 0,
		       ELF_NVRREG * माप(vector128));
	पूर्ण

	/* Always get VRSAVE back */
	unsafe_get_user(current->thपढ़ो.ckvrsave,
			(u32 __user *)&sr->mc_vregs[32], failed);
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		mtspr(SPRN_VRSAVE, current->thपढ़ो.ckvrsave);
#पूर्ण_अगर /* CONFIG_ALTIVEC */

	regs->msr &= ~(MSR_FP | MSR_FE0 | MSR_FE1);

	unsafe_copy_fpr_from_user(current, &sr->mc_fregs, failed);

#अगर_घोषित CONFIG_VSX
	regs->msr &= ~MSR_VSX;
	अगर (msr & MSR_VSX) अणु
		/*
		 * Restore altivec रेजिस्टरs from the stack to a local
		 * buffer, then ग_लिखो this out to the thपढ़ो_काष्ठा
		 */
		unsafe_copy_ckvsx_from_user(current, &sr->mc_vsregs, failed);
		current->thपढ़ो.used_vsr = true;
	पूर्ण अन्यथा अगर (current->thपढ़ो.used_vsr)
		क्रम (i = 0; i < 32 ; i++) अणु
			current->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET] = 0;
			current->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET] = 0;
		पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित CONFIG_SPE
	/* SPE regs are not checkpoपूर्णांकed with TM, so this section is
	 * simply the same as in restore_user_regs().
	 */
	regs->msr &= ~MSR_SPE;
	अगर (msr & MSR_SPE) अणु
		unsafe_copy_from_user(current->thपढ़ो.evr, &sr->mc_vregs,
				      ELF_NEVRREG * माप(u32), failed);
		current->thपढ़ो.used_spe = true;
	पूर्ण अन्यथा अगर (current->thपढ़ो.used_spe)
		स_रखो(current->thपढ़ो.evr, 0, ELF_NEVRREG * माप(u32));

	/* Always get SPEFSCR back */
	unsafe_get_user(current->thपढ़ो.spefscr,
			(u32 __user *)&sr->mc_vregs + ELF_NEVRREG, failed);
#पूर्ण_अगर /* CONFIG_SPE */

	user_पढ़ो_access_end();

	अगर (!user_पढ़ो_access_begin(पंचांग_sr, माप(*पंचांग_sr)))
		वापस 1;

	unsafe_restore_general_regs(regs, पंचांग_sr, failed);

#अगर_घोषित CONFIG_ALTIVEC
	/* restore altivec रेजिस्टरs from the stack */
	अगर (msr & MSR_VEC)
		unsafe_copy_from_user(&current->thपढ़ो.vr_state, &पंचांग_sr->mc_vregs,
				      माप(sr->mc_vregs), failed);

	/* Always get VRSAVE back */
	unsafe_get_user(current->thपढ़ो.vrsave,
			(u32 __user *)&पंचांग_sr->mc_vregs[32], failed);
#पूर्ण_अगर /* CONFIG_ALTIVEC */

	unsafe_copy_ckfpr_from_user(current, &पंचांग_sr->mc_fregs, failed);

#अगर_घोषित CONFIG_VSX
	अगर (msr & MSR_VSX) अणु
		/*
		 * Restore altivec रेजिस्टरs from the stack to a local
		 * buffer, then ग_लिखो this out to the thपढ़ो_काष्ठा
		 */
		unsafe_copy_vsx_from_user(current, &पंचांग_sr->mc_vsregs, failed);
		current->thपढ़ो.used_vsr = true;
	पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

	/* Get the top half of the MSR from the user context */
	unsafe_get_user(msr_hi, &पंचांग_sr->mc_gregs[PT_MSR], failed);
	msr_hi <<= 32;

	user_पढ़ो_access_end();

	/* If TM bits are set to the reserved value, it's an invalid context */
	अगर (MSR_TM_RESV(msr_hi))
		वापस 1;

	/*
	 * Disabling preemption, since it is unsafe to be preempted
	 * with MSR[TS] set without recheckpoपूर्णांकing.
	 */
	preempt_disable();

	/*
	 * CAUTION:
	 * After regs->MSR[TS] being updated, make sure that get_user(),
	 * put_user() or similar functions are *not* called. These
	 * functions can generate page faults which will cause the process
	 * to be de-scheduled with MSR[TS] set but without calling
	 * पंचांग_recheckpoपूर्णांक(). This can cause a bug.
	 *
	 * Pull in the MSR TM bits from the user context
	 */
	regs->msr = (regs->msr & ~MSR_TS_MASK) | (msr_hi & MSR_TS_MASK);
	/* Now, recheckpoपूर्णांक.  This loads up all of the checkpoपूर्णांकed (older)
	 * रेजिस्टरs, including FP and V[S]Rs.  After recheckpoपूर्णांकing, the
	 * transactional versions should be loaded.
	 */
	पंचांग_enable();
	/* Make sure the transaction is marked as failed */
	current->thपढ़ो.पंचांग_texasr |= TEXASR_FS;
	/* This loads the checkpoपूर्णांकed FP/VEC state, अगर used */
	पंचांग_recheckpoपूर्णांक(&current->thपढ़ो);

	/* This loads the speculative FP/VEC state, अगर used */
	msr_check_and_set(msr & (MSR_FP | MSR_VEC));
	अगर (msr & MSR_FP) अणु
		load_fp_state(&current->thपढ़ो.fp_state);
		regs->msr |= (MSR_FP | current->thपढ़ो.fpexc_mode);
	पूर्ण
#अगर_घोषित CONFIG_ALTIVEC
	अगर (msr & MSR_VEC) अणु
		load_vr_state(&current->thपढ़ो.vr_state);
		regs->msr |= MSR_VEC;
	पूर्ण
#पूर्ण_अगर

	preempt_enable();

	वापस 0;

failed:
	user_पढ़ो_access_end();
	वापस 1;
पूर्ण
#अन्यथा
अटल दीर्घ restore_पंचांग_user_regs(काष्ठा pt_regs *regs, काष्ठा mcontext __user *sr,
				 काष्ठा mcontext __user *पंचांग_sr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64

#घोषणा copy_siginfo_to_user	copy_siginfo_to_user32

#पूर्ण_अगर /* CONFIG_PPC64 */

/*
 * Set up a संकेत frame क्रम a "real-time" संकेत handler
 * (one which माला_लो siginfo).
 */
पूर्णांक handle_rt_संकेत32(काष्ठा kसंकेत *ksig, sigset_t *oldset,
		       काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा rt_sigframe __user *frame;
	काष्ठा mcontext __user *mctx;
	काष्ठा mcontext __user *पंचांग_mctx = शून्य;
	अचिन्हित दीर्घ newsp = 0;
	अचिन्हित दीर्घ tramp;
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;
	/* Save the thपढ़ो's msr beक्रमe get_पंचांग_stackpoपूर्णांकer() changes it */
	अचिन्हित दीर्घ msr = regs->msr;

	/* Set up Signal Frame */
	frame = get_sigframe(ksig, tsk, माप(*frame), 1);
	mctx = &frame->uc.uc_mcontext;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	पंचांग_mctx = &frame->uc_transact.uc_mcontext;
#पूर्ण_अगर
	अगर (MSR_TM_ACTIVE(msr))
		prepare_save_पंचांग_user_regs();
	अन्यथा
		prepare_save_user_regs(1);

	अगर (!user_access_begin(frame, माप(*frame)))
		जाओ badframe;

	/* Put the siginfo & fill in most of the ucontext */
	unsafe_put_user(0, &frame->uc.uc_flags, failed);
#अगर_घोषित CONFIG_PPC64
	unsafe_compat_save_altstack(&frame->uc.uc_stack, regs->gpr[1], failed);
#अन्यथा
	unsafe_save_altstack(&frame->uc.uc_stack, regs->gpr[1], failed);
#पूर्ण_अगर
	unsafe_put_user(to_user_ptr(&frame->uc.uc_mcontext), &frame->uc.uc_regs, failed);

	अगर (MSR_TM_ACTIVE(msr)) अणु
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
		unsafe_put_user((अचिन्हित दीर्घ)&frame->uc_transact,
				&frame->uc.uc_link, failed);
		unsafe_put_user((अचिन्हित दीर्घ)पंचांग_mctx,
				&frame->uc_transact.uc_regs, failed);
#पूर्ण_अगर
		unsafe_save_पंचांग_user_regs(regs, mctx, पंचांग_mctx, msr, failed);
	पूर्ण अन्यथा अणु
		unsafe_put_user(0, &frame->uc.uc_link, failed);
		unsafe_save_user_regs(regs, mctx, पंचांग_mctx, 1, failed);
	पूर्ण

	/* Save user रेजिस्टरs on the stack */
	अगर (tsk->mm->context.vdso) अणु
		tramp = VDSO32_SYMBOL(tsk->mm->context.vdso, sigtramp_rt32);
	पूर्ण अन्यथा अणु
		tramp = (अचिन्हित दीर्घ)mctx->mc_pad;
		/* Set up the sigवापस trampoline: li r0,sigret; sc */
		unsafe_put_user(PPC_INST_ADDI + __NR_rt_sigवापस, &mctx->mc_pad[0],
				failed);
		unsafe_put_user(PPC_INST_SC, &mctx->mc_pad[1], failed);
		यंत्र("dcbst %y0; sync; icbi %y0; sync" :: "Z" (mctx->mc_pad[0]));
	पूर्ण
	unsafe_put_sigset_t(&frame->uc.uc_sigmask, oldset, failed);

	user_access_end();

	अगर (copy_siginfo_to_user(&frame->info, &ksig->info))
		जाओ badframe;

	regs->link = tramp;

#अगर_घोषित CONFIG_PPC_FPU_REGS
	tsk->thपढ़ो.fp_state.fpscr = 0;	/* turn off all fp exceptions */
#पूर्ण_अगर

	/* create a stack frame क्रम the caller of the handler */
	newsp = ((अचिन्हित दीर्घ)frame) - (__SIGNAL_FRAMESIZE + 16);
	अगर (put_user(regs->gpr[1], (u32 __user *)newsp))
		जाओ badframe;

	/* Fill रेजिस्टरs क्रम संकेत handler */
	regs->gpr[1] = newsp;
	regs->gpr[3] = ksig->sig;
	regs->gpr[4] = (अचिन्हित दीर्घ)&frame->info;
	regs->gpr[5] = (अचिन्हित दीर्घ)&frame->uc;
	regs->gpr[6] = (अचिन्हित दीर्घ)frame;
	regs->nip = (अचिन्हित दीर्घ) ksig->ka.sa.sa_handler;
	/* enter the संकेत handler in native-endian mode */
	regs->msr &= ~MSR_LE;
	regs->msr |= (MSR_KERNEL & MSR_LE);
	वापस 0;

failed:
	user_access_end();

badframe:
	संकेत_fault(tsk, regs, "handle_rt_signal32", frame);

	वापस 1;
पूर्ण

/*
 * OK, we're invoking a handler
 */
पूर्णांक handle_संकेत32(काष्ठा kसंकेत *ksig, sigset_t *oldset,
		काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा sigcontext __user *sc;
	काष्ठा sigframe __user *frame;
	काष्ठा mcontext __user *mctx;
	काष्ठा mcontext __user *पंचांग_mctx = शून्य;
	अचिन्हित दीर्घ newsp = 0;
	अचिन्हित दीर्घ tramp;
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;
	/* Save the thपढ़ो's msr beक्रमe get_पंचांग_stackpoपूर्णांकer() changes it */
	अचिन्हित दीर्घ msr = regs->msr;

	/* Set up Signal Frame */
	frame = get_sigframe(ksig, tsk, माप(*frame), 1);
	mctx = &frame->mctx;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	पंचांग_mctx = &frame->mctx_transact;
#पूर्ण_अगर
	अगर (MSR_TM_ACTIVE(msr))
		prepare_save_पंचांग_user_regs();
	अन्यथा
		prepare_save_user_regs(1);

	अगर (!user_access_begin(frame, माप(*frame)))
		जाओ badframe;
	sc = (काष्ठा sigcontext __user *) &frame->sctx;

#अगर _NSIG != 64
#त्रुटि "Please adjust handle_signal()"
#पूर्ण_अगर
	unsafe_put_user(to_user_ptr(ksig->ka.sa.sa_handler), &sc->handler, failed);
	unsafe_put_user(oldset->sig[0], &sc->oldmask, failed);
#अगर_घोषित CONFIG_PPC64
	unsafe_put_user((oldset->sig[0] >> 32), &sc->_unused[3], failed);
#अन्यथा
	unsafe_put_user(oldset->sig[1], &sc->_unused[3], failed);
#पूर्ण_अगर
	unsafe_put_user(to_user_ptr(mctx), &sc->regs, failed);
	unsafe_put_user(ksig->sig, &sc->संकेत, failed);

	अगर (MSR_TM_ACTIVE(msr))
		unsafe_save_पंचांग_user_regs(regs, mctx, पंचांग_mctx, msr, failed);
	अन्यथा
		unsafe_save_user_regs(regs, mctx, पंचांग_mctx, 1, failed);

	अगर (tsk->mm->context.vdso) अणु
		tramp = VDSO32_SYMBOL(tsk->mm->context.vdso, sigtramp32);
	पूर्ण अन्यथा अणु
		tramp = (अचिन्हित दीर्घ)mctx->mc_pad;
		/* Set up the sigवापस trampoline: li r0,sigret; sc */
		unsafe_put_user(PPC_INST_ADDI + __NR_sigवापस, &mctx->mc_pad[0], failed);
		unsafe_put_user(PPC_INST_SC, &mctx->mc_pad[1], failed);
		यंत्र("dcbst %y0; sync; icbi %y0; sync" :: "Z" (mctx->mc_pad[0]));
	पूर्ण
	user_access_end();

	regs->link = tramp;

#अगर_घोषित CONFIG_PPC_FPU_REGS
	tsk->thपढ़ो.fp_state.fpscr = 0;	/* turn off all fp exceptions */
#पूर्ण_अगर

	/* create a stack frame क्रम the caller of the handler */
	newsp = ((अचिन्हित दीर्घ)frame) - __SIGNAL_FRAMESIZE;
	अगर (put_user(regs->gpr[1], (u32 __user *)newsp))
		जाओ badframe;

	regs->gpr[1] = newsp;
	regs->gpr[3] = ksig->sig;
	regs->gpr[4] = (अचिन्हित दीर्घ) sc;
	regs->nip = (अचिन्हित दीर्घ)ksig->ka.sa.sa_handler;
	/* enter the संकेत handler in native-endian mode */
	regs->msr &= ~MSR_LE;
	regs->msr |= (MSR_KERNEL & MSR_LE);
	वापस 0;

failed:
	user_access_end();

badframe:
	संकेत_fault(tsk, regs, "handle_signal32", frame);

	वापस 1;
पूर्ण

अटल पूर्णांक करो_setcontext(काष्ठा ucontext __user *ucp, काष्ठा pt_regs *regs, पूर्णांक sig)
अणु
	sigset_t set;
	काष्ठा mcontext __user *mcp;

	अगर (!user_पढ़ो_access_begin(ucp, माप(*ucp)))
		वापस -EFAULT;

	unsafe_get_sigset_t(&set, &ucp->uc_sigmask, failed);
#अगर_घोषित CONFIG_PPC64
	अणु
		u32 cmcp;

		unsafe_get_user(cmcp, &ucp->uc_regs, failed);
		mcp = (काष्ठा mcontext __user *)(u64)cmcp;
	पूर्ण
#अन्यथा
	unsafe_get_user(mcp, &ucp->uc_regs, failed);
#पूर्ण_अगर
	user_पढ़ो_access_end();

	set_current_blocked(&set);
	अगर (restore_user_regs(regs, mcp, sig))
		वापस -EFAULT;

	वापस 0;

failed:
	user_पढ़ो_access_end();
	वापस -EFAULT;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
अटल पूर्णांक करो_setcontext_पंचांग(काष्ठा ucontext __user *ucp,
			    काष्ठा ucontext __user *पंचांग_ucp,
			    काष्ठा pt_regs *regs)
अणु
	sigset_t set;
	काष्ठा mcontext __user *mcp;
	काष्ठा mcontext __user *पंचांग_mcp;
	u32 cmcp;
	u32 पंचांग_cmcp;

	अगर (!user_पढ़ो_access_begin(ucp, माप(*ucp)))
		वापस -EFAULT;

	unsafe_get_sigset_t(&set, &ucp->uc_sigmask, failed);
	unsafe_get_user(cmcp, &ucp->uc_regs, failed);

	user_पढ़ो_access_end();

	अगर (__get_user(पंचांग_cmcp, &पंचांग_ucp->uc_regs))
		वापस -EFAULT;
	mcp = (काष्ठा mcontext __user *)(u64)cmcp;
	पंचांग_mcp = (काष्ठा mcontext __user *)(u64)पंचांग_cmcp;
	/* no need to check access_ok(mcp), since mcp < 4GB */

	set_current_blocked(&set);
	अगर (restore_पंचांग_user_regs(regs, mcp, पंचांग_mcp))
		वापस -EFAULT;

	वापस 0;

failed:
	user_पढ़ो_access_end();
	वापस -EFAULT;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
COMPAT_SYSCALL_DEFINE3(swapcontext, काष्ठा ucontext __user *, old_ctx,
		       काष्ठा ucontext __user *, new_ctx, पूर्णांक, ctx_size)
#अन्यथा
SYSCALL_DEFINE3(swapcontext, काष्ठा ucontext __user *, old_ctx,
		       काष्ठा ucontext __user *, new_ctx, दीर्घ, ctx_size)
#पूर्ण_अगर
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	पूर्णांक ctx_has_vsx_region = 0;

#अगर_घोषित CONFIG_PPC64
	अचिन्हित दीर्घ new_msr = 0;

	अगर (new_ctx) अणु
		काष्ठा mcontext __user *mcp;
		u32 cmcp;

		/*
		 * Get poपूर्णांकer to the real mcontext.  No need क्रम
		 * access_ok since we are dealing with compat
		 * poपूर्णांकers.
		 */
		अगर (__get_user(cmcp, &new_ctx->uc_regs))
			वापस -EFAULT;
		mcp = (काष्ठा mcontext __user *)(u64)cmcp;
		अगर (__get_user(new_msr, &mcp->mc_gregs[PT_MSR]))
			वापस -EFAULT;
	पूर्ण
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
#अन्यथा
	/* Context size is क्रम future use. Right now, we only make sure
	 * we are passed something we understand
	 */
	अगर (ctx_size < माप(काष्ठा ucontext))
		वापस -EINVAL;
#पूर्ण_अगर
	अगर (old_ctx != शून्य) अणु
		काष्ठा mcontext __user *mctx;

		/*
		 * old_ctx might not be 16-byte aligned, in which
		 * हाल old_ctx->uc_mcontext won't be either.
		 * Because we have the old_ctx->uc_pad2 field
		 * beक्रमe old_ctx->uc_mcontext, we need to round करोwn
		 * from &old_ctx->uc_mcontext to a 16-byte boundary.
		 */
		mctx = (काष्ठा mcontext __user *)
			((अचिन्हित दीर्घ) &old_ctx->uc_mcontext & ~0xfUL);
		prepare_save_user_regs(ctx_has_vsx_region);
		अगर (!user_ग_लिखो_access_begin(old_ctx, ctx_size))
			वापस -EFAULT;
		unsafe_save_user_regs(regs, mctx, शून्य, ctx_has_vsx_region, failed);
		unsafe_put_sigset_t(&old_ctx->uc_sigmask, &current->blocked, failed);
		unsafe_put_user(to_user_ptr(mctx), &old_ctx->uc_regs, failed);
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
	अगर (करो_setcontext(new_ctx, regs, 0))
		करो_निकास(संक_अंश);

	set_thपढ़ो_flag(TIF_RESTOREALL);
	वापस 0;

failed:
	user_ग_लिखो_access_end();
	वापस -EFAULT;
पूर्ण

#अगर_घोषित CONFIG_PPC64
COMPAT_SYSCALL_DEFINE0(rt_sigवापस)
#अन्यथा
SYSCALL_DEFINE0(rt_sigवापस)
#पूर्ण_अगर
अणु
	काष्ठा rt_sigframe __user *rt_sf;
	काष्ठा pt_regs *regs = current_pt_regs();
	पूर्णांक पंचांग_restore = 0;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	काष्ठा ucontext __user *uc_transact;
	अचिन्हित दीर्घ msr_hi;
	अचिन्हित दीर्घ पंचांगp;
#पूर्ण_अगर
	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	rt_sf = (काष्ठा rt_sigframe __user *)
		(regs->gpr[1] + __SIGNAL_FRAMESIZE + 16);
	अगर (!access_ok(rt_sf, माप(*rt_sf)))
		जाओ bad;

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
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

	अगर (__get_user(पंचांगp, &rt_sf->uc.uc_link))
		जाओ bad;
	uc_transact = (काष्ठा ucontext __user *)(uपूर्णांकptr_t)पंचांगp;
	अगर (uc_transact) अणु
		u32 cmcp;
		काष्ठा mcontext __user *mcp;

		अगर (__get_user(cmcp, &uc_transact->uc_regs))
			वापस -EFAULT;
		mcp = (काष्ठा mcontext __user *)(u64)cmcp;
		/* The top 32 bits of the MSR are stashed in the transactional
		 * ucontext. */
		अगर (__get_user(msr_hi, &mcp->mc_gregs[PT_MSR]))
			जाओ bad;

		अगर (MSR_TM_ACTIVE(msr_hi<<32)) अणु
			/* Trying to start TM on non TM प्रणाली */
			अगर (!cpu_has_feature(CPU_FTR_TM))
				जाओ bad;
			/* We only recheckpoपूर्णांक on वापस अगर we're
			 * transaction.
			 */
			पंचांग_restore = 1;
			अगर (करो_setcontext_पंचांग(&rt_sf->uc, uc_transact, regs))
				जाओ bad;
		पूर्ण
	पूर्ण
	अगर (!पंचांग_restore) अणु
		/*
		 * Unset regs->msr because ucontext MSR TS is not
		 * set, and recheckpoपूर्णांक was not called. This aव्योम
		 * hitting a TM Bad thing at RFID
		 */
		regs->msr &= ~MSR_TS_MASK;
	पूर्ण
	/* Fall through, क्रम non-TM restore */
#पूर्ण_अगर
	अगर (!पंचांग_restore)
		अगर (करो_setcontext(&rt_sf->uc, regs, 1))
			जाओ bad;

	/*
	 * It's not clear whether or why it is desirable to save the
	 * sigaltstack setting on संकेत delivery and restore it on
	 * संकेत वापस.  But other architectures करो this and we have
	 * always करोne it up until now so it is probably better not to
	 * change it.  -- paulus
	 */
#अगर_घोषित CONFIG_PPC64
	अगर (compat_restore_altstack(&rt_sf->uc.uc_stack))
		जाओ bad;
#अन्यथा
	अगर (restore_altstack(&rt_sf->uc.uc_stack))
		जाओ bad;
#पूर्ण_अगर
	set_thपढ़ो_flag(TIF_RESTOREALL);
	वापस 0;

 bad:
	संकेत_fault(current, regs, "sys_rt_sigreturn", rt_sf);

	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC32
SYSCALL_DEFINE3(debug_setcontext, काष्ठा ucontext __user *, ctx,
			 पूर्णांक, ndbg, काष्ठा sig_dbg_op __user *, dbg)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा sig_dbg_op op;
	पूर्णांक i;
	अचिन्हित दीर्घ new_msr = regs->msr;
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
	अचिन्हित दीर्घ new_dbcr0 = current->thपढ़ो.debug.dbcr0;
#पूर्ण_अगर

	क्रम (i=0; i<ndbg; i++) अणु
		अगर (copy_from_user(&op, dbg + i, माप(op)))
			वापस -EFAULT;
		चयन (op.dbg_type) अणु
		हाल SIG_DBG_SINGLE_STEPPING:
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
			अगर (op.dbg_value) अणु
				new_msr |= MSR_DE;
				new_dbcr0 |= (DBCR0_IDM | DBCR0_IC);
			पूर्ण अन्यथा अणु
				new_dbcr0 &= ~DBCR0_IC;
				अगर (!DBCR_ACTIVE_EVENTS(new_dbcr0,
						current->thपढ़ो.debug.dbcr1)) अणु
					new_msr &= ~MSR_DE;
					new_dbcr0 &= ~DBCR0_IDM;
				पूर्ण
			पूर्ण
#अन्यथा
			अगर (op.dbg_value)
				new_msr |= MSR_SE;
			अन्यथा
				new_msr &= ~MSR_SE;
#पूर्ण_अगर
			अवरोध;
		हाल SIG_DBG_BRANCH_TRACING:
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
			वापस -EINVAL;
#अन्यथा
			अगर (op.dbg_value)
				new_msr |= MSR_BE;
			अन्यथा
				new_msr &= ~MSR_BE;
#पूर्ण_अगर
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* We रुको until here to actually install the values in the
	   रेजिस्टरs so अगर we fail in the above loop, it will not
	   affect the contents of these रेजिस्टरs.  After this poपूर्णांक,
	   failure is a problem, anyway, and it's very unlikely unless
	   the user is really करोing something wrong. */
	regs->msr = new_msr;
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
	current->thपढ़ो.debug.dbcr0 = new_dbcr0;
#पूर्ण_अगर

	अगर (!access_ok(ctx, माप(*ctx)) ||
	    fault_in_pages_पढ़ोable((u8 __user *)ctx, माप(*ctx)))
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
	अगर (करो_setcontext(ctx, regs, 1)) अणु
		संकेत_fault(current, regs, "sys_debug_setcontext", ctx);

		क्रमce_sig(संक_अंश);
		जाओ out;
	पूर्ण

	/*
	 * It's not clear whether or why it is desirable to save the
	 * sigaltstack setting on संकेत delivery and restore it on
	 * संकेत वापस.  But other architectures करो this and we have
	 * always करोne it up until now so it is probably better not to
	 * change it.  -- paulus
	 */
	restore_altstack(&ctx->uc_stack);

	set_thपढ़ो_flag(TIF_RESTOREALL);
 out:
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Do a संकेत वापस; unकरो the संकेत stack.
 */
#अगर_घोषित CONFIG_PPC64
COMPAT_SYSCALL_DEFINE0(sigवापस)
#अन्यथा
SYSCALL_DEFINE0(sigवापस)
#पूर्ण_अगर
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा sigframe __user *sf;
	काष्ठा sigcontext __user *sc;
	काष्ठा sigcontext sigctx;
	काष्ठा mcontext __user *sr;
	sigset_t set;
	काष्ठा mcontext __user *mcp;
	काष्ठा mcontext __user *पंचांग_mcp = शून्य;
	अचिन्हित दीर्घ दीर्घ msr_hi = 0;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	sf = (काष्ठा sigframe __user *)(regs->gpr[1] + __SIGNAL_FRAMESIZE);
	sc = &sf->sctx;
	अगर (copy_from_user(&sigctx, sc, माप(sigctx)))
		जाओ badframe;

#अगर_घोषित CONFIG_PPC64
	/*
	 * Note that PPC32 माला_दो the upper 32 bits of the sigmask in the
	 * unused part of the संकेत stackframe
	 */
	set.sig[0] = sigctx.oldmask + ((दीर्घ)(sigctx._unused[3]) << 32);
#अन्यथा
	set.sig[0] = sigctx.oldmask;
	set.sig[1] = sigctx._unused[3];
#पूर्ण_अगर
	set_current_blocked(&set);

	mcp = (काष्ठा mcontext __user *)&sf->mctx;
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	पंचांग_mcp = (काष्ठा mcontext __user *)&sf->mctx_transact;
	अगर (__get_user(msr_hi, &पंचांग_mcp->mc_gregs[PT_MSR]))
		जाओ badframe;
#पूर्ण_अगर
	अगर (MSR_TM_ACTIVE(msr_hi<<32)) अणु
		अगर (!cpu_has_feature(CPU_FTR_TM))
			जाओ badframe;
		अगर (restore_पंचांग_user_regs(regs, mcp, पंचांग_mcp))
			जाओ badframe;
	पूर्ण अन्यथा अणु
		sr = (काष्ठा mcontext __user *)from_user_ptr(sigctx.regs);
		अगर (restore_user_regs(regs, sr, 1)) अणु
			संकेत_fault(current, regs, "sys_sigreturn", sr);

			क्रमce_sig(संक_अंश);
			वापस 0;
		पूर्ण
	पूर्ण

	set_thपढ़ो_flag(TIF_RESTOREALL);
	वापस 0;

badframe:
	संकेत_fault(current, regs, "sys_sigreturn", sc);

	क्रमce_sig(संक_अंश);
	वापस 0;
पूर्ण
