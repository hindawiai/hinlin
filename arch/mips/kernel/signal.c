<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1991, 1992  Linus Torvalds
 * Copyright (C) 1994 - 2000  Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2014, Imagination Technologies Ltd.
 */
#समावेश <linux/cache.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/personality.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/unistd.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/compiler.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/tracehook.h>

#समावेश <यंत्र/abi.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/sim.h>
#समावेश <यंत्र/ucontext.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/war.h>
#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/msa.h>

#समावेश "signal-common.h"

अटल पूर्णांक (*save_fp_context)(व्योम __user *sc);
अटल पूर्णांक (*restore_fp_context)(व्योम __user *sc);

काष्ठा sigframe अणु
	u32 sf_ass[4];		/* argument save space क्रम o32 */
	u32 sf_pad[2];		/* Was: संकेत trampoline */

	/* Matches काष्ठा ucontext from its uc_mcontext field onwards */
	काष्ठा sigcontext sf_sc;
	sigset_t sf_mask;
	अचिन्हित दीर्घ दीर्घ sf_extcontext[];
पूर्ण;

काष्ठा rt_sigframe अणु
	u32 rs_ass[4];		/* argument save space क्रम o32 */
	u32 rs_pad[2];		/* Was: संकेत trampoline */
	काष्ठा siginfo rs_info;
	काष्ठा ucontext rs_uc;
पूर्ण;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

/*
 * Thपढ़ो saved context copy to/from a संकेत context presumed to be on the
 * user stack, and thereक्रमe accessed with appropriate macros from uaccess.h.
 */
अटल पूर्णांक copy_fp_to_sigcontext(व्योम __user *sc)
अणु
	काष्ठा mips_abi *abi = current->thपढ़ो.abi;
	uपूर्णांक64_t __user *fpregs = sc + abi->off_sc_fpregs;
	uपूर्णांक32_t __user *csr = sc + abi->off_sc_fpc_csr;
	पूर्णांक i;
	पूर्णांक err = 0;
	पूर्णांक inc = test_thपढ़ो_flag(TIF_32BIT_FPREGS) ? 2 : 1;

	क्रम (i = 0; i < NUM_FPU_REGS; i += inc) अणु
		err |=
		    __put_user(get_fpr64(&current->thपढ़ो.fpu.fpr[i], 0),
			       &fpregs[i]);
	पूर्ण
	err |= __put_user(current->thपढ़ो.fpu.fcr31, csr);

	वापस err;
पूर्ण

अटल पूर्णांक copy_fp_from_sigcontext(व्योम __user *sc)
अणु
	काष्ठा mips_abi *abi = current->thपढ़ो.abi;
	uपूर्णांक64_t __user *fpregs = sc + abi->off_sc_fpregs;
	uपूर्णांक32_t __user *csr = sc + abi->off_sc_fpc_csr;
	पूर्णांक i;
	पूर्णांक err = 0;
	पूर्णांक inc = test_thपढ़ो_flag(TIF_32BIT_FPREGS) ? 2 : 1;
	u64 fpr_val;

	क्रम (i = 0; i < NUM_FPU_REGS; i += inc) अणु
		err |= __get_user(fpr_val, &fpregs[i]);
		set_fpr64(&current->thपढ़ो.fpu.fpr[i], 0, fpr_val);
	पूर्ण
	err |= __get_user(current->thपढ़ो.fpu.fcr31, csr);

	वापस err;
पूर्ण

#अन्यथा /* !CONFIG_MIPS_FP_SUPPORT */

अटल पूर्णांक copy_fp_to_sigcontext(व्योम __user *sc)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक copy_fp_from_sigcontext(व्योम __user *sc)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_MIPS_FP_SUPPORT */

/*
 * Wrappers क्रम the assembly _अणुsave,restoreपूर्ण_fp_context functions.
 */
अटल पूर्णांक save_hw_fp_context(व्योम __user *sc)
अणु
	काष्ठा mips_abi *abi = current->thपढ़ो.abi;
	uपूर्णांक64_t __user *fpregs = sc + abi->off_sc_fpregs;
	uपूर्णांक32_t __user *csr = sc + abi->off_sc_fpc_csr;

	वापस _save_fp_context(fpregs, csr);
पूर्ण

अटल पूर्णांक restore_hw_fp_context(व्योम __user *sc)
अणु
	काष्ठा mips_abi *abi = current->thपढ़ो.abi;
	uपूर्णांक64_t __user *fpregs = sc + abi->off_sc_fpregs;
	uपूर्णांक32_t __user *csr = sc + abi->off_sc_fpc_csr;

	वापस _restore_fp_context(fpregs, csr);
पूर्ण

/*
 * Extended context handling.
 */

अटल अंतरभूत व्योम __user *sc_to_extcontext(व्योम __user *sc)
अणु
	काष्ठा ucontext __user *uc;

	/*
	 * We can just pretend the sigcontext is always embedded in a काष्ठा
	 * ucontext here, because the offset from sigcontext to extended
	 * context is the same in the काष्ठा sigframe हाल.
	 */
	uc = container_of(sc, काष्ठा ucontext, uc_mcontext);
	वापस &uc->uc_extcontext;
पूर्ण

#अगर_घोषित CONFIG_CPU_HAS_MSA

अटल पूर्णांक save_msa_extcontext(व्योम __user *buf)
अणु
	काष्ठा msa_extcontext __user *msa = buf;
	uपूर्णांक64_t val;
	पूर्णांक i, err;

	अगर (!thपढ़ो_msa_context_live())
		वापस 0;

	/*
	 * Ensure that we can't lose the live MSA context between checking
	 * क्रम it & writing it to memory.
	 */
	preempt_disable();

	अगर (is_msa_enabled()) अणु
		/*
		 * There are no EVA versions of the vector रेजिस्टर load/store
		 * inकाष्ठाions, so MSA context has to be saved to kernel memory
		 * and then copied to user memory. The save to kernel memory
		 * should alपढ़ोy have been करोne when handling scalar FP
		 * context.
		 */
		BUG_ON(IS_ENABLED(CONFIG_EVA));

		err = __put_user(पढ़ो_msa_csr(), &msa->csr);
		err |= _save_msa_all_upper(&msa->wr);

		preempt_enable();
	पूर्ण अन्यथा अणु
		preempt_enable();

		err = __put_user(current->thपढ़ो.fpu.msacsr, &msa->csr);

		क्रम (i = 0; i < NUM_FPU_REGS; i++) अणु
			val = get_fpr64(&current->thपढ़ो.fpu.fpr[i], 1);
			err |= __put_user(val, &msa->wr[i]);
		पूर्ण
	पूर्ण

	err |= __put_user(MSA_EXTCONTEXT_MAGIC, &msa->ext.magic);
	err |= __put_user(माप(*msa), &msa->ext.size);

	वापस err ? -EFAULT : माप(*msa);
पूर्ण

अटल पूर्णांक restore_msa_extcontext(व्योम __user *buf, अचिन्हित पूर्णांक size)
अणु
	काष्ठा msa_extcontext __user *msa = buf;
	अचिन्हित दीर्घ दीर्घ val;
	अचिन्हित पूर्णांक csr;
	पूर्णांक i, err;

	अगर (size != माप(*msa))
		वापस -EINVAL;

	err = get_user(csr, &msa->csr);
	अगर (err)
		वापस err;

	preempt_disable();

	अगर (is_msa_enabled()) अणु
		/*
		 * There are no EVA versions of the vector रेजिस्टर load/store
		 * inकाष्ठाions, so MSA context has to be copied to kernel
		 * memory and later loaded to रेजिस्टरs. The same is true of
		 * scalar FP context, so FPU & MSA should have alपढ़ोy been
		 * disabled whilst handling scalar FP context.
		 */
		BUG_ON(IS_ENABLED(CONFIG_EVA));

		ग_लिखो_msa_csr(csr);
		err |= _restore_msa_all_upper(&msa->wr);
		preempt_enable();
	पूर्ण अन्यथा अणु
		preempt_enable();

		current->thपढ़ो.fpu.msacsr = csr;

		क्रम (i = 0; i < NUM_FPU_REGS; i++) अणु
			err |= __get_user(val, &msa->wr[i]);
			set_fpr64(&current->thपढ़ो.fpu.fpr[i], 1, val);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

#अन्यथा /* !CONFIG_CPU_HAS_MSA */

अटल पूर्णांक save_msa_extcontext(व्योम __user *buf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक restore_msa_extcontext(व्योम __user *buf, अचिन्हित पूर्णांक size)
अणु
	वापस SIGSYS;
पूर्ण

#पूर्ण_अगर /* !CONFIG_CPU_HAS_MSA */

अटल पूर्णांक save_extcontext(व्योम __user *buf)
अणु
	पूर्णांक sz;

	sz = save_msa_extcontext(buf);
	अगर (sz < 0)
		वापस sz;
	buf += sz;

	/* If no context was saved then trivially वापस */
	अगर (!sz)
		वापस 0;

	/* Write the end marker */
	अगर (__put_user(END_EXTCONTEXT_MAGIC, (u32 *)buf))
		वापस -EFAULT;

	sz += माप(((काष्ठा extcontext *)शून्य)->magic);
	वापस sz;
पूर्ण

अटल पूर्णांक restore_extcontext(व्योम __user *buf)
अणु
	काष्ठा extcontext ext;
	पूर्णांक err;

	जबतक (1) अणु
		err = __get_user(ext.magic, (अचिन्हित पूर्णांक *)buf);
		अगर (err)
			वापस err;

		अगर (ext.magic == END_EXTCONTEXT_MAGIC)
			वापस 0;

		err = __get_user(ext.size, (अचिन्हित पूर्णांक *)(buf
			+ दुरत्व(काष्ठा extcontext, size)));
		अगर (err)
			वापस err;

		चयन (ext.magic) अणु
		हाल MSA_EXTCONTEXT_MAGIC:
			err = restore_msa_extcontext(buf, ext.size);
			अवरोध;

		शेष:
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (err)
			वापस err;

		buf += ext.size;
	पूर्ण
पूर्ण

/*
 * Helper routines
 */
पूर्णांक रक्षित_save_fp_context(व्योम __user *sc)
अणु
	काष्ठा mips_abi *abi = current->thपढ़ो.abi;
	uपूर्णांक64_t __user *fpregs = sc + abi->off_sc_fpregs;
	uपूर्णांक32_t __user *csr = sc + abi->off_sc_fpc_csr;
	uपूर्णांक32_t __user *used_math = sc + abi->off_sc_used_math;
	अचिन्हित पूर्णांक used, ext_sz;
	पूर्णांक err;

	used = used_math() ? USED_FP : 0;
	अगर (!used)
		जाओ fp_करोne;

	अगर (!test_thपढ़ो_flag(TIF_32BIT_FPREGS))
		used |= USED_FR1;
	अगर (test_thपढ़ो_flag(TIF_HYBRID_FPREGS))
		used |= USED_HYBRID_FPRS;

	/*
	 * EVA करोes not have userland equivalents of ldc1 or sdc1, so
	 * save to the kernel FP context & copy that to userland below.
	 */
	अगर (IS_ENABLED(CONFIG_EVA))
		lose_fpu(1);

	जबतक (1) अणु
		lock_fpu_owner();
		अगर (is_fpu_owner()) अणु
			err = save_fp_context(sc);
			unlock_fpu_owner();
		पूर्ण अन्यथा अणु
			unlock_fpu_owner();
			err = copy_fp_to_sigcontext(sc);
		पूर्ण
		अगर (likely(!err))
			अवरोध;
		/* touch the sigcontext and try again */
		err = __put_user(0, &fpregs[0]) |
			__put_user(0, &fpregs[31]) |
			__put_user(0, csr);
		अगर (err)
			वापस err;	/* really bad sigcontext */
	पूर्ण

fp_करोne:
	ext_sz = err = save_extcontext(sc_to_extcontext(sc));
	अगर (err < 0)
		वापस err;
	used |= ext_sz ? USED_EXTCONTEXT : 0;

	वापस __put_user(used, used_math);
पूर्ण

पूर्णांक रक्षित_restore_fp_context(व्योम __user *sc)
अणु
	काष्ठा mips_abi *abi = current->thपढ़ो.abi;
	uपूर्णांक64_t __user *fpregs = sc + abi->off_sc_fpregs;
	uपूर्णांक32_t __user *csr = sc + abi->off_sc_fpc_csr;
	uपूर्णांक32_t __user *used_math = sc + abi->off_sc_used_math;
	अचिन्हित पूर्णांक used;
	पूर्णांक err, sig = 0, पंचांगp __maybe_unused;

	err = __get_user(used, used_math);
	conditional_used_math(used & USED_FP);

	/*
	 * The संकेत handler may have used FPU; give it up अगर the program
	 * करोesn't want it following sigवापस.
	 */
	अगर (err || !(used & USED_FP))
		lose_fpu(0);
	अगर (err)
		वापस err;
	अगर (!(used & USED_FP))
		जाओ fp_करोne;

	err = sig = fpcsr_pending(csr);
	अगर (err < 0)
		वापस err;

	/*
	 * EVA करोes not have userland equivalents of ldc1 or sdc1, so we
	 * disable the FPU here such that the code below simply copies to
	 * the kernel FP context.
	 */
	अगर (IS_ENABLED(CONFIG_EVA))
		lose_fpu(0);

	जबतक (1) अणु
		lock_fpu_owner();
		अगर (is_fpu_owner()) अणु
			err = restore_fp_context(sc);
			unlock_fpu_owner();
		पूर्ण अन्यथा अणु
			unlock_fpu_owner();
			err = copy_fp_from_sigcontext(sc);
		पूर्ण
		अगर (likely(!err))
			अवरोध;
		/* touch the sigcontext and try again */
		err = __get_user(पंचांगp, &fpregs[0]) |
			__get_user(पंचांगp, &fpregs[31]) |
			__get_user(पंचांगp, csr);
		अगर (err)
			अवरोध;	/* really bad sigcontext */
	पूर्ण

fp_करोne:
	अगर (!err && (used & USED_EXTCONTEXT))
		err = restore_extcontext(sc_to_extcontext(sc));

	वापस err ?: sig;
पूर्ण

पूर्णांक setup_sigcontext(काष्ठा pt_regs *regs, काष्ठा sigcontext __user *sc)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	err |= __put_user(regs->cp0_epc, &sc->sc_pc);

	err |= __put_user(0, &sc->sc_regs[0]);
	क्रम (i = 1; i < 32; i++)
		err |= __put_user(regs->regs[i], &sc->sc_regs[i]);

#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
	err |= __put_user(regs->acx, &sc->sc_acx);
#पूर्ण_अगर
	err |= __put_user(regs->hi, &sc->sc_mdhi);
	err |= __put_user(regs->lo, &sc->sc_mdlo);
	अगर (cpu_has_dsp) अणु
		err |= __put_user(mfhi1(), &sc->sc_hi1);
		err |= __put_user(mflo1(), &sc->sc_lo1);
		err |= __put_user(mfhi2(), &sc->sc_hi2);
		err |= __put_user(mflo2(), &sc->sc_lo2);
		err |= __put_user(mfhi3(), &sc->sc_hi3);
		err |= __put_user(mflo3(), &sc->sc_lo3);
		err |= __put_user(rddsp(DSP_MASK), &sc->sc_dsp);
	पूर्ण


	/*
	 * Save FPU state to संकेत context. Signal handler
	 * will "inherit" current FPU state.
	 */
	err |= रक्षित_save_fp_context(sc);

	वापस err;
पूर्ण

अटल माप_प्रकार extcontext_max_size(व्योम)
अणु
	माप_प्रकार sz = 0;

	/*
	 * The assumption here is that between this poपूर्णांक & the poपूर्णांक at which
	 * the extended context is saved the size of the context should only
	 * ever be able to shrink (अगर the task is preempted), but never grow.
	 * That is, what this function वापसs is an upper bound on the size of
	 * the extended context क्रम the current task at the current समय.
	 */

	अगर (thपढ़ो_msa_context_live())
		sz += माप(काष्ठा msa_extcontext);

	/* If any context is saved then we'll append the end marker */
	अगर (sz)
		sz += माप(((काष्ठा extcontext *)शून्य)->magic);

	वापस sz;
पूर्ण

पूर्णांक fpcsr_pending(अचिन्हित पूर्णांक __user *fpcsr)
अणु
	पूर्णांक err, sig = 0;
	अचिन्हित पूर्णांक csr, enabled;

	err = __get_user(csr, fpcsr);
	enabled = FPU_CSR_UNI_X | ((csr & FPU_CSR_ALL_E) << 5);
	/*
	 * If the संकेत handler set some FPU exceptions, clear it and
	 * send संक_भ_त्रुटि.
	 */
	अगर (csr & enabled) अणु
		csr &= ~enabled;
		err |= __put_user(csr, fpcsr);
		sig = संक_भ_त्रुटि;
	पूर्ण
	वापस err ?: sig;
पूर्ण

पूर्णांक restore_sigcontext(काष्ठा pt_regs *regs, काष्ठा sigcontext __user *sc)
अणु
	अचिन्हित दीर्घ treg;
	पूर्णांक err = 0;
	पूर्णांक i;

	/* Always make any pending restarted प्रणाली calls वापस -EINTR */
	current->restart_block.fn = करो_no_restart_syscall;

	err |= __get_user(regs->cp0_epc, &sc->sc_pc);

#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
	err |= __get_user(regs->acx, &sc->sc_acx);
#पूर्ण_अगर
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

#अगर_घोषित CONFIG_WAR_ICACHE_REFILLS
#घोषणा SIGMASK		~(cpu_icache_line_size()-1)
#अन्यथा
#घोषणा SIGMASK		ALMASK
#पूर्ण_अगर

व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs,
			  माप_प्रकार frame_size)
अणु
	अचिन्हित दीर्घ sp;

	/* Leave space क्रम potential extended context */
	frame_size += extcontext_max_size();

	/* Default to using normal stack */
	sp = regs->regs[29];

	/*
	 * FPU emulator may have it's own trampoline active just
	 * above the user stack, 16-bytes beक्रमe the next lowest
	 * 16 byte boundary.  Try to aव्योम trashing it.
	 */
	sp -= 32;

	sp = sigsp(sp, ksig);

	वापस (व्योम __user *)((sp - frame_size) & SIGMASK);
पूर्ण

/*
 * Atomically swap in the new संकेत mask, and रुको क्रम a संकेत.
 */

#अगर_घोषित CONFIG_TRAD_SIGNALS
SYSCALL_DEFINE1(संक_रोको, sigset_t __user *, uset)
अणु
	वापस sys_rt_संक_रोको(uset, माप(sigset_t));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRAD_SIGNALS
SYSCALL_DEFINE3(sigaction, पूर्णांक, sig, स्थिर काष्ठा sigaction __user *, act,
	काष्ठा sigaction __user *, oact)
अणु
	काष्ठा k_sigaction new_ka, old_ka;
	पूर्णांक ret;
	पूर्णांक err = 0;

	अगर (act) अणु
		old_sigset_t mask;

		अगर (!access_ok(act, माप(*act)))
			वापस -EFAULT;
		err |= __get_user(new_ka.sa.sa_handler, &act->sa_handler);
		err |= __get_user(new_ka.sa.sa_flags, &act->sa_flags);
		err |= __get_user(mask, &act->sa_mask.sig[0]);
		अगर (err)
			वापस -EFAULT;

		siginitset(&new_ka.sa.sa_mask, mask);
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);

	अगर (!ret && oact) अणु
		अगर (!access_ok(oact, माप(*oact)))
			वापस -EFAULT;
		err |= __put_user(old_ka.sa.sa_flags, &oact->sa_flags);
		err |= __put_user(old_ka.sa.sa_handler, &oact->sa_handler);
		err |= __put_user(old_ka.sa.sa_mask.sig[0], oact->sa_mask.sig);
		err |= __put_user(0, &oact->sa_mask.sig[1]);
		err |= __put_user(0, &oact->sa_mask.sig[2]);
		err |= __put_user(0, &oact->sa_mask.sig[3]);
		अगर (err)
			वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRAD_SIGNALS
यंत्रlinkage व्योम sys_sigवापस(व्योम)
अणु
	काष्ठा sigframe __user *frame;
	काष्ठा pt_regs *regs;
	sigset_t blocked;
	पूर्णांक sig;

	regs = current_pt_regs();
	frame = (काष्ठा sigframe __user *)regs->regs[29];
	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_from_user(&blocked, &frame->sf_mask, माप(blocked)))
		जाओ badframe;

	set_current_blocked(&blocked);

	sig = restore_sigcontext(regs, &frame->sf_sc);
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
#पूर्ण_अगर /* CONFIG_TRAD_SIGNALS */

यंत्रlinkage व्योम sys_rt_sigवापस(व्योम)
अणु
	काष्ठा rt_sigframe __user *frame;
	काष्ठा pt_regs *regs;
	sigset_t set;
	पूर्णांक sig;

	regs = current_pt_regs();
	frame = (काष्ठा rt_sigframe __user *)regs->regs[29];
	अगर (!access_ok(frame, माप(*frame)))
		जाओ badframe;
	अगर (__copy_from_user(&set, &frame->rs_uc.uc_sigmask, माप(set)))
		जाओ badframe;

	set_current_blocked(&set);

	sig = restore_sigcontext(regs, &frame->rs_uc.uc_mcontext);
	अगर (sig < 0)
		जाओ badframe;
	अन्यथा अगर (sig)
		क्रमce_sig(sig);

	अगर (restore_altstack(&frame->rs_uc.uc_stack))
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

#अगर_घोषित CONFIG_TRAD_SIGNALS
अटल पूर्णांक setup_frame(व्योम *sig_वापस, काष्ठा kसंकेत *ksig,
		       काष्ठा pt_regs *regs, sigset_t *set)
अणु
	काष्ठा sigframe __user *frame;
	पूर्णांक err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));
	अगर (!access_ok(frame, माप (*frame)))
		वापस -EFAULT;

	err |= setup_sigcontext(regs, &frame->sf_sc);
	err |= __copy_to_user(&frame->sf_mask, set, माप(*set));
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
#पूर्ण_अगर

अटल पूर्णांक setup_rt_frame(व्योम *sig_वापस, काष्ठा kसंकेत *ksig,
			  काष्ठा pt_regs *regs, sigset_t *set)
अणु
	काष्ठा rt_sigframe __user *frame;
	पूर्णांक err = 0;

	frame = get_sigframe(ksig, regs, माप(*frame));
	अगर (!access_ok(frame, माप (*frame)))
		वापस -EFAULT;

	/* Create siginfo.  */
	err |= copy_siginfo_to_user(&frame->rs_info, &ksig->info);

	/* Create the ucontext.	 */
	err |= __put_user(0, &frame->rs_uc.uc_flags);
	err |= __put_user(शून्य, &frame->rs_uc.uc_link);
	err |= __save_altstack(&frame->rs_uc.uc_stack, regs->regs[29]);
	err |= setup_sigcontext(regs, &frame->rs_uc.uc_mcontext);
	err |= __copy_to_user(&frame->rs_uc.uc_sigmask, set, माप(*set));

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

काष्ठा mips_abi mips_abi = अणु
#अगर_घोषित CONFIG_TRAD_SIGNALS
	.setup_frame	= setup_frame,
#पूर्ण_अगर
	.setup_rt_frame = setup_rt_frame,
	.restart	= __NR_restart_syscall,

	.off_sc_fpregs = दुरत्व(काष्ठा sigcontext, sc_fpregs),
	.off_sc_fpc_csr = दुरत्व(काष्ठा sigcontext, sc_fpc_csr),
	.off_sc_used_math = दुरत्व(काष्ठा sigcontext, sc_used_math),

	.vdso		= &vdso_image,
पूर्ण;

अटल व्योम handle_संकेत(काष्ठा kसंकेत *ksig, काष्ठा pt_regs *regs)
अणु
	sigset_t *oldset = sigmask_to_save();
	पूर्णांक ret;
	काष्ठा mips_abi *abi = current->thपढ़ो.abi;
	व्योम *vdso = current->mm->context.vdso;

	/*
	 * If we were emulating a delay slot inकाष्ठाion, निकास that frame such
	 * that addresses in the sigframe are as expected क्रम userland and we
	 * करोn't have a problem if we reuse the thread's frame क्रम an
	 * inकाष्ठाion within the संकेत handler.
	 */
	dsemul_thपढ़ो_rollback(regs);

	अगर (regs->regs[0]) अणु
		चयन(regs->regs[2]) अणु
		हाल ERESTART_RESTARTBLOCK:
		हाल ERESTARTNOHAND:
			regs->regs[2] = EINTR;
			अवरोध;
		हाल ERESTARTSYS:
			अगर (!(ksig->ka.sa.sa_flags & SA_RESTART)) अणु
				regs->regs[2] = EINTR;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल ERESTARTNOINTR:
			regs->regs[7] = regs->regs[26];
			regs->regs[2] = regs->regs[0];
			regs->cp0_epc -= 4;
		पूर्ण

		regs->regs[0] = 0;		/* Don't deal with this again.	*/
	पूर्ण

	rseq_संकेत_deliver(ksig, regs);

	अगर (sig_uses_siginfo(&ksig->ka, abi))
		ret = abi->setup_rt_frame(vdso + abi->vdso->off_rt_sigवापस,
					  ksig, regs, oldset);
	अन्यथा
		ret = abi->setup_frame(vdso + abi->vdso->off_sigवापस,
				       ksig, regs, oldset);

	संकेत_setup_करोne(ret, ksig, 0);
पूर्ण

अटल व्योम करो_संकेत(काष्ठा pt_regs *regs)
अणु
	काष्ठा kसंकेत ksig;

	अगर (get_संकेत(&ksig)) अणु
		/* Whee!  Actually deliver the संकेत.	*/
		handle_संकेत(&ksig, regs);
		वापस;
	पूर्ण

	अगर (regs->regs[0]) अणु
		चयन (regs->regs[2]) अणु
		हाल ERESTARTNOHAND:
		हाल ERESTARTSYS:
		हाल ERESTARTNOINTR:
			regs->regs[2] = regs->regs[0];
			regs->regs[7] = regs->regs[26];
			regs->cp0_epc -= 4;
			अवरोध;

		हाल ERESTART_RESTARTBLOCK:
			regs->regs[2] = current->thपढ़ो.abi->restart;
			regs->regs[7] = regs->regs[26];
			regs->cp0_epc -= 4;
			अवरोध;
		पूर्ण
		regs->regs[0] = 0;	/* Don't deal with this again.	*/
	पूर्ण

	/*
	 * If there's no संकेत to deliver, we just put the saved sigmask
	 * back
	 */
	restore_saved_sigmask();
पूर्ण

/*
 * notअगरication of userspace execution resumption
 * - triggered by the TIF_WORK_MASK flags
 */
यंत्रlinkage व्योम करो_notअगरy_resume(काष्ठा pt_regs *regs, व्योम *unused,
	__u32 thपढ़ो_info_flags)
अणु
	local_irq_enable();

	user_निकास();

	अगर (thपढ़ो_info_flags & _TIF_UPROBE)
		uprobe_notअगरy_resume(regs);

	/* deal with pending संकेत delivery */
	अगर (thपढ़ो_info_flags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAL))
		करो_संकेत(regs);

	अगर (thपढ़ो_info_flags & _TIF_NOTIFY_RESUME) अणु
		tracehook_notअगरy_resume(regs);
		rseq_handle_notअगरy_resume(शून्य, regs);
	पूर्ण

	user_enter();
पूर्ण

#अगर defined(CONFIG_SMP) && defined(CONFIG_MIPS_FP_SUPPORT)
अटल पूर्णांक smp_save_fp_context(व्योम __user *sc)
अणु
	वापस raw_cpu_has_fpu
	       ? save_hw_fp_context(sc)
	       : copy_fp_to_sigcontext(sc);
पूर्ण

अटल पूर्णांक smp_restore_fp_context(व्योम __user *sc)
अणु
	वापस raw_cpu_has_fpu
	       ? restore_hw_fp_context(sc)
	       : copy_fp_from_sigcontext(sc);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक संकेत_setup(व्योम)
अणु
	/*
	 * The offset from sigcontext to extended context should be the same
	 * regardless of the type of संकेत, such that userland can always know
	 * where to look अगर it wishes to find the extended context काष्ठाures.
	 */
	BUILD_BUG_ON((दुरत्व(काष्ठा sigframe, sf_extcontext) -
		      दुरत्व(काष्ठा sigframe, sf_sc)) !=
		     (दुरत्व(काष्ठा rt_sigframe, rs_uc.uc_extcontext) -
		      दुरत्व(काष्ठा rt_sigframe, rs_uc.uc_mcontext)));

#अगर defined(CONFIG_SMP) && defined(CONFIG_MIPS_FP_SUPPORT)
	/* For now just करो the cpu_has_fpu check when the functions are invoked */
	save_fp_context = smp_save_fp_context;
	restore_fp_context = smp_restore_fp_context;
#अन्यथा
	अगर (cpu_has_fpu) अणु
		save_fp_context = save_hw_fp_context;
		restore_fp_context = restore_hw_fp_context;
	पूर्ण अन्यथा अणु
		save_fp_context = copy_fp_to_sigcontext;
		restore_fp_context = copy_fp_from_sigcontext;
	पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

	वापस 0;
पूर्ण

arch_initcall(संकेत_setup);
