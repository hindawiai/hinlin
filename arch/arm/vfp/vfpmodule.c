<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/vfp/vfpmodule.c
 *
 *  Copyright (C) 2004 ARM Limited.
 *  Written by Deep Blue Solutions Limited.
 */
#समावेश <linux/types.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/user.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/thपढ़ो_notअगरy.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/vfp.h>

#समावेश "vfpinstr.h"
#समावेश "vfp.h"

/*
 * Our undef handlers (in entry.S)
 */
यंत्रlinkage व्योम vfp_support_entry(व्योम);
यंत्रlinkage व्योम vfp_null_entry(व्योम);

यंत्रlinkage व्योम (*vfp_vector)(व्योम) = vfp_null_entry;

/*
 * Dual-use variable.
 * Used in startup: set to non-zero अगर VFP checks fail
 * After startup, holds VFP architecture
 */
अटल अचिन्हित पूर्णांक __initdata VFP_arch;

/*
 * The poपूर्णांकer to the vfpstate काष्ठाure of the thपढ़ो which currently
 * owns the context held in the VFP hardware, or शून्य अगर the hardware
 * context is invalid.
 *
 * For UP, this is sufficient to tell which thपढ़ो owns the VFP context.
 * However, क्रम SMP, we also need to check the CPU number stored in the
 * saved state too to catch migrations.
 */
जोड़ vfp_state *vfp_current_hw_state[NR_CPUS];

/*
 * Is 'thread's most up to date state stored in this CPUs hardware?
 * Must be called from non-preemptible context.
 */
अटल bool vfp_state_in_hw(अचिन्हित पूर्णांक cpu, काष्ठा thपढ़ो_info *thपढ़ो)
अणु
#अगर_घोषित CONFIG_SMP
	अगर (thपढ़ो->vfpstate.hard.cpu != cpu)
		वापस false;
#पूर्ण_अगर
	वापस vfp_current_hw_state[cpu] == &thपढ़ो->vfpstate;
पूर्ण

/*
 * Force a reload of the VFP context from the thपढ़ो काष्ठाure.  We करो
 * this by ensuring that access to the VFP hardware is disabled, and
 * clear vfp_current_hw_state.  Must be called from non-preemptible context.
 */
अटल व्योम vfp_क्रमce_reload(अचिन्हित पूर्णांक cpu, काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	अगर (vfp_state_in_hw(cpu, thपढ़ो)) अणु
		fmxr(FPEXC, fmrx(FPEXC) & ~FPEXC_EN);
		vfp_current_hw_state[cpu] = शून्य;
	पूर्ण
#अगर_घोषित CONFIG_SMP
	thपढ़ो->vfpstate.hard.cpu = NR_CPUS;
#पूर्ण_अगर
पूर्ण

/*
 * Per-thपढ़ो VFP initialization.
 */
अटल व्योम vfp_thपढ़ो_flush(काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	जोड़ vfp_state *vfp = &thपढ़ो->vfpstate;
	अचिन्हित पूर्णांक cpu;

	/*
	 * Disable VFP to ensure we initialize it first.  We must ensure
	 * that the modअगरication of vfp_current_hw_state[] and hardware
	 * disable are करोne क्रम the same CPU and without preemption.
	 *
	 * Do this first to ensure that preemption won't overग_लिखो our
	 * state saving should access to the VFP be enabled at this poपूर्णांक.
	 */
	cpu = get_cpu();
	अगर (vfp_current_hw_state[cpu] == vfp)
		vfp_current_hw_state[cpu] = शून्य;
	fmxr(FPEXC, fmrx(FPEXC) & ~FPEXC_EN);
	put_cpu();

	स_रखो(vfp, 0, माप(जोड़ vfp_state));

	vfp->hard.fpexc = FPEXC_EN;
	vfp->hard.fpscr = FPSCR_ROUND_NEAREST;
#अगर_घोषित CONFIG_SMP
	vfp->hard.cpu = NR_CPUS;
#पूर्ण_अगर
पूर्ण

अटल व्योम vfp_thपढ़ो_निकास(काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	/* release हाल: Per-thपढ़ो VFP cleanup. */
	जोड़ vfp_state *vfp = &thपढ़ो->vfpstate;
	अचिन्हित पूर्णांक cpu = get_cpu();

	अगर (vfp_current_hw_state[cpu] == vfp)
		vfp_current_hw_state[cpu] = शून्य;
	put_cpu();
पूर्ण

अटल व्योम vfp_thपढ़ो_copy(काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	काष्ठा thपढ़ो_info *parent = current_thपढ़ो_info();

	vfp_sync_hwstate(parent);
	thपढ़ो->vfpstate = parent->vfpstate;
#अगर_घोषित CONFIG_SMP
	thपढ़ो->vfpstate.hard.cpu = NR_CPUS;
#पूर्ण_अगर
पूर्ण

/*
 * When this function is called with the following 'cmd's, the following
 * is true जबतक this function is being run:
 *  THREAD_NOFTIFY_SWTICH:
 *   - the previously running thपढ़ो will not be scheduled onto another CPU.
 *   - the next thपढ़ो to be run (v) will not be running on another CPU.
 *   - thपढ़ो->cpu is the local CPU number
 *   - not preemptible as we're called in the middle of a thपढ़ो चयन
 *  THREAD_NOTIFY_FLUSH:
 *   - the thपढ़ो (v) will be running on the local CPU, so
 *	v === current_thपढ़ो_info()
 *   - thपढ़ो->cpu is the local CPU number at the समय it is accessed,
 *	but may change at any समय.
 *   - we could be preempted अगर tree preempt rcu is enabled, so
 *	it is unsafe to use thपढ़ो->cpu.
 *  THREAD_NOTIFY_EXIT
 *   - we could be preempted अगर tree preempt rcu is enabled, so
 *	it is unsafe to use thपढ़ो->cpu.
 */
अटल पूर्णांक vfp_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd, व्योम *v)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = v;
	u32 fpexc;
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक cpu;
#पूर्ण_अगर

	चयन (cmd) अणु
	हाल THREAD_NOTIFY_SWITCH:
		fpexc = fmrx(FPEXC);

#अगर_घोषित CONFIG_SMP
		cpu = thपढ़ो->cpu;

		/*
		 * On SMP, अगर VFP is enabled, save the old state in
		 * हाल the thपढ़ो migrates to a dअगरferent CPU. The
		 * restoring is करोne lazily.
		 */
		अगर ((fpexc & FPEXC_EN) && vfp_current_hw_state[cpu])
			vfp_save_state(vfp_current_hw_state[cpu], fpexc);
#पूर्ण_अगर

		/*
		 * Always disable VFP so we can lazily save/restore the
		 * old state.
		 */
		fmxr(FPEXC, fpexc & ~FPEXC_EN);
		अवरोध;

	हाल THREAD_NOTIFY_FLUSH:
		vfp_thपढ़ो_flush(thपढ़ो);
		अवरोध;

	हाल THREAD_NOTIFY_EXIT:
		vfp_thपढ़ो_निकास(thपढ़ो);
		अवरोध;

	हाल THREAD_NOTIFY_COPY:
		vfp_thपढ़ो_copy(thपढ़ो);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block vfp_notअगरier_block = अणु
	.notअगरier_call	= vfp_notअगरier,
पूर्ण;

/*
 * Raise a संक_भ_त्रुटि क्रम the current process.
 * sicode describes the संकेत being उठाओd.
 */
अटल व्योम vfp_उठाओ_sigfpe(अचिन्हित पूर्णांक sicode, काष्ठा pt_regs *regs)
अणु
	/*
	 * This is the same as NWFPE, because it's not clear what
	 * this is used क्रम
	 */
	current->thपढ़ो.error_code = 0;
	current->thपढ़ो.trap_no = 6;

	send_sig_fault(संक_भ_त्रुटि, sicode,
		       (व्योम __user *)(inकाष्ठाion_poपूर्णांकer(regs) - 4),
		       current);
पूर्ण

अटल व्योम vfp_panic(अक्षर *reason, u32 inst)
अणु
	पूर्णांक i;

	pr_err("VFP: Error: %s\n", reason);
	pr_err("VFP: EXC 0x%08x SCR 0x%08x INST 0x%08x\n",
		fmrx(FPEXC), fmrx(FPSCR), inst);
	क्रम (i = 0; i < 32; i += 2)
		pr_err("VFP: s%2u: 0x%08x s%2u: 0x%08x\n",
		       i, vfp_get_भग्न(i), i+1, vfp_get_भग्न(i+1));
पूर्ण

/*
 * Process biपंचांगask of exception conditions.
 */
अटल व्योम vfp_उठाओ_exceptions(u32 exceptions, u32 inst, u32 fpscr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक si_code = 0;

	pr_debug("VFP: raising exceptions %08x\n", exceptions);

	अगर (exceptions == VFP_EXCEPTION_ERROR) अणु
		vfp_panic("unhandled bounce", inst);
		vfp_उठाओ_sigfpe(FPE_FLTINV, regs);
		वापस;
	पूर्ण

	/*
	 * If any of the status flags are set, update the FPSCR.
	 * Comparison inकाष्ठाions always वापस at least one of
	 * these flags set.
	 */
	अगर (exceptions & (FPSCR_N|FPSCR_Z|FPSCR_C|FPSCR_V))
		fpscr &= ~(FPSCR_N|FPSCR_Z|FPSCR_C|FPSCR_V);

	fpscr |= exceptions;

	fmxr(FPSCR, fpscr);

#घोषणा RAISE(stat,en,sig)				\
	अगर (exceptions & stat && fpscr & en)		\
		si_code = sig;

	/*
	 * These are arranged in priority order, least to highest.
	 */
	RAISE(FPSCR_DZC, FPSCR_DZE, FPE_FLTDIV);
	RAISE(FPSCR_IXC, FPSCR_IXE, FPE_FLTRES);
	RAISE(FPSCR_UFC, FPSCR_UFE, FPE_FLTUND);
	RAISE(FPSCR_OFC, FPSCR_OFE, FPE_FLTOVF);
	RAISE(FPSCR_IOC, FPSCR_IOE, FPE_FLTINV);

	अगर (si_code)
		vfp_उठाओ_sigfpe(si_code, regs);
पूर्ण

/*
 * Emulate a VFP inकाष्ठाion.
 */
अटल u32 vfp_emulate_inकाष्ठाion(u32 inst, u32 fpscr, काष्ठा pt_regs *regs)
अणु
	u32 exceptions = VFP_EXCEPTION_ERROR;

	pr_debug("VFP: emulate: INST=0x%08x SCR=0x%08x\n", inst, fpscr);

	अगर (INST_CPRTDO(inst)) अणु
		अगर (!INST_CPRT(inst)) अणु
			/*
			 * CPDO
			 */
			अगर (vfp_single(inst)) अणु
				exceptions = vfp_single_cpकरो(inst, fpscr);
			पूर्ण अन्यथा अणु
				exceptions = vfp_द्विगुन_cpकरो(inst, fpscr);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * A CPRT inकाष्ठाion can not appear in FPINST2, nor
			 * can it cause an exception.  Thereक्रमe, we करो not
			 * have to emulate it.
			 */
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * A CPDT inकाष्ठाion can not appear in FPINST2, nor can
		 * it cause an exception.  Thereक्रमe, we करो not have to
		 * emulate it.
		 */
	पूर्ण
	वापस exceptions & ~VFP_न_अंक_FLAG;
पूर्ण

/*
 * Package up a bounce condition.
 */
व्योम VFP_bounce(u32 trigger, u32 fpexc, काष्ठा pt_regs *regs)
अणु
	u32 fpscr, orig_fpscr, fpsid, exceptions;

	pr_debug("VFP: bounce: trigger %08x fpexc %08x\n", trigger, fpexc);

	/*
	 * At this poपूर्णांक, FPEXC can have the following configuration:
	 *
	 *  EX DEX IXE
	 *  0   1   x   - synchronous exception
	 *  1   x   0   - asynchronous exception
	 *  1   x   1   - sychronous on VFP subarch 1 and asynchronous on later
	 *  0   0   1   - synchronous on VFP9 (non-standard subarch 1
	 *                implementation), undefined otherwise
	 *
	 * Clear various bits and enable access to the VFP so we can
	 * handle the bounce.
	 */
	fmxr(FPEXC, fpexc & ~(FPEXC_EX|FPEXC_DEX|FPEXC_FP2V|FPEXC_VV|FPEXC_TRAP_MASK));

	fpsid = fmrx(FPSID);
	orig_fpscr = fpscr = fmrx(FPSCR);

	/*
	 * Check क्रम the special VFP subarch 1 and FPSCR.IXE bit हाल
	 */
	अगर ((fpsid & FPSID_ARCH_MASK) == (1 << FPSID_ARCH_BIT)
	    && (fpscr & FPSCR_IXE)) अणु
		/*
		 * Synchronous exception, emulate the trigger inकाष्ठाion
		 */
		जाओ emulate;
	पूर्ण

	अगर (fpexc & FPEXC_EX) अणु
#अगर_अघोषित CONFIG_CPU_FEROCEON
		/*
		 * Asynchronous exception. The inकाष्ठाion is पढ़ो from FPINST
		 * and the पूर्णांकerrupted inकाष्ठाion has to be restarted.
		 */
		trigger = fmrx(FPINST);
		regs->ARM_pc -= 4;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (!(fpexc & FPEXC_DEX)) अणु
		/*
		 * Illegal combination of bits. It can be caused by an
		 * unallocated VFP inकाष्ठाion but with FPSCR.IXE set and not
		 * on VFP subarch 1.
		 */
		 vfp_उठाओ_exceptions(VFP_EXCEPTION_ERROR, trigger, fpscr, regs);
		जाओ निकास;
	पूर्ण

	/*
	 * Modअगरy fpscr to indicate the number of iterations reमुख्यing.
	 * If FPEXC.EX is 0, FPEXC.DEX is 1 and the FPEXC.VV bit indicates
	 * whether FPEXC.VECITR or FPSCR.LEN is used.
	 */
	अगर (fpexc & (FPEXC_EX | FPEXC_VV)) अणु
		u32 len;

		len = fpexc + (1 << FPEXC_LENGTH_BIT);

		fpscr &= ~FPSCR_LENGTH_MASK;
		fpscr |= (len & FPEXC_LENGTH_MASK) << (FPSCR_LENGTH_BIT - FPEXC_LENGTH_BIT);
	पूर्ण

	/*
	 * Handle the first FP inकाष्ठाion.  We used to take note of the
	 * FPEXC bounce reason, but this appears to be unreliable.
	 * Emulate the bounced inकाष्ठाion instead.
	 */
	exceptions = vfp_emulate_inकाष्ठाion(trigger, fpscr, regs);
	अगर (exceptions)
		vfp_उठाओ_exceptions(exceptions, trigger, orig_fpscr, regs);

	/*
	 * If there isn't a second FP inकाष्ठाion, निकास now. Note that
	 * the FPEXC.FP2V bit is valid only अगर FPEXC.EX is 1.
	 */
	अगर ((fpexc & (FPEXC_EX | FPEXC_FP2V)) != (FPEXC_EX | FPEXC_FP2V))
		जाओ निकास;

	/*
	 * The barrier() here prevents fpinst2 being पढ़ो
	 * beक्रमe the condition above.
	 */
	barrier();
	trigger = fmrx(FPINST2);

 emulate:
	exceptions = vfp_emulate_inकाष्ठाion(trigger, orig_fpscr, regs);
	अगर (exceptions)
		vfp_उठाओ_exceptions(exceptions, trigger, orig_fpscr, regs);
 निकास:
	preempt_enable();
पूर्ण

अटल व्योम vfp_enable(व्योम *unused)
अणु
	u32 access;

	BUG_ON(preemptible());
	access = get_copro_access();

	/*
	 * Enable full access to VFP (cp10 and cp11)
	 */
	set_copro_access(access | CPACC_FULL(10) | CPACC_FULL(11));
पूर्ण

/* Called by platक्रमms on which we want to disable VFP because it may not be
 * present on all CPUs within a SMP complex. Needs to be called prior to
 * vfp_init().
 */
व्योम __init vfp_disable(व्योम)
अणु
	अगर (VFP_arch) अणु
		pr_debug("%s: should be called prior to vfp_init\n", __func__);
		वापस;
	पूर्ण
	VFP_arch = 1;
पूर्ण

#अगर_घोषित CONFIG_CPU_PM
अटल पूर्णांक vfp_pm_suspend(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();
	u32 fpexc = fmrx(FPEXC);

	/* अगर vfp is on, then save state क्रम resumption */
	अगर (fpexc & FPEXC_EN) अणु
		pr_debug("%s: saving vfp state\n", __func__);
		vfp_save_state(&ti->vfpstate, fpexc);

		/* disable, just in हाल */
		fmxr(FPEXC, fmrx(FPEXC) & ~FPEXC_EN);
	पूर्ण अन्यथा अगर (vfp_current_hw_state[ti->cpu]) अणु
#अगर_अघोषित CONFIG_SMP
		fmxr(FPEXC, fpexc | FPEXC_EN);
		vfp_save_state(vfp_current_hw_state[ti->cpu], fpexc);
		fmxr(FPEXC, fpexc);
#पूर्ण_अगर
	पूर्ण

	/* clear any inक्रमmation we had about last context state */
	vfp_current_hw_state[ti->cpu] = शून्य;

	वापस 0;
पूर्ण

अटल व्योम vfp_pm_resume(व्योम)
अणु
	/* ensure we have access to the vfp */
	vfp_enable(शून्य);

	/* and disable it to ensure the next usage restores the state */
	fmxr(FPEXC, fmrx(FPEXC) & ~FPEXC_EN);
पूर्ण

अटल पूर्णांक vfp_cpu_pm_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,
	व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_PM_ENTER:
		vfp_pm_suspend();
		अवरोध;
	हाल CPU_PM_ENTER_FAILED:
	हाल CPU_PM_EXIT:
		vfp_pm_resume();
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block vfp_cpu_pm_notअगरier_block = अणु
	.notअगरier_call = vfp_cpu_pm_notअगरier,
पूर्ण;

अटल व्योम vfp_pm_init(व्योम)
अणु
	cpu_pm_रेजिस्टर_notअगरier(&vfp_cpu_pm_notअगरier_block);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम vfp_pm_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_PM */

/*
 * Ensure that the VFP state stored in 'thread->vfpstate' is up to date
 * with the hardware state.
 */
व्योम vfp_sync_hwstate(काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	अचिन्हित पूर्णांक cpu = get_cpu();

	अगर (vfp_state_in_hw(cpu, thपढ़ो)) अणु
		u32 fpexc = fmrx(FPEXC);

		/*
		 * Save the last VFP state on this CPU.
		 */
		fmxr(FPEXC, fpexc | FPEXC_EN);
		vfp_save_state(&thपढ़ो->vfpstate, fpexc | FPEXC_EN);
		fmxr(FPEXC, fpexc);
	पूर्ण

	put_cpu();
पूर्ण

/* Ensure that the thपढ़ो reloads the hardware VFP state on the next use. */
व्योम vfp_flush_hwstate(काष्ठा thपढ़ो_info *thपढ़ो)
अणु
	अचिन्हित पूर्णांक cpu = get_cpu();

	vfp_क्रमce_reload(cpu, thपढ़ो);

	put_cpu();
पूर्ण

/*
 * Save the current VFP state पूर्णांकo the provided काष्ठाures and prepare
 * क्रम entry पूर्णांकo a new function (संकेत handler).
 */
पूर्णांक vfp_preserve_user_clear_hwstate(काष्ठा user_vfp *ufp,
				    काष्ठा user_vfp_exc *ufp_exc)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = current_thपढ़ो_info();
	काष्ठा vfp_hard_काष्ठा *hwstate = &thपढ़ो->vfpstate.hard;

	/* Ensure that the saved hwstate is up-to-date. */
	vfp_sync_hwstate(thपढ़ो);

	/*
	 * Copy the भग्नing poपूर्णांक रेजिस्टरs. There can be unused
	 * रेजिस्टरs see यंत्र/hwcap.h क्रम details.
	 */
	स_नकल(&ufp->fpregs, &hwstate->fpregs, माप(hwstate->fpregs));

	/*
	 * Copy the status and control रेजिस्टर.
	 */
	ufp->fpscr = hwstate->fpscr;

	/*
	 * Copy the exception रेजिस्टरs.
	 */
	ufp_exc->fpexc = hwstate->fpexc;
	ufp_exc->fpinst = hwstate->fpinst;
	ufp_exc->fpinst2 = hwstate->fpinst2;

	/* Ensure that VFP is disabled. */
	vfp_flush_hwstate(thपढ़ो);

	/*
	 * As per the PCS, clear the length and stride bits क्रम function
	 * entry.
	 */
	hwstate->fpscr &= ~(FPSCR_LENGTH_MASK | FPSCR_STRIDE_MASK);
	वापस 0;
पूर्ण

/* Sanitise and restore the current VFP state from the provided काष्ठाures. */
पूर्णांक vfp_restore_user_hwstate(काष्ठा user_vfp *ufp, काष्ठा user_vfp_exc *ufp_exc)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = current_thपढ़ो_info();
	काष्ठा vfp_hard_काष्ठा *hwstate = &thपढ़ो->vfpstate.hard;
	अचिन्हित दीर्घ fpexc;

	/* Disable VFP to aव्योम corrupting the new thपढ़ो state. */
	vfp_flush_hwstate(thपढ़ो);

	/*
	 * Copy the भग्नing poपूर्णांक रेजिस्टरs. There can be unused
	 * रेजिस्टरs see यंत्र/hwcap.h क्रम details.
	 */
	स_नकल(&hwstate->fpregs, &ufp->fpregs, माप(hwstate->fpregs));
	/*
	 * Copy the status and control रेजिस्टर.
	 */
	hwstate->fpscr = ufp->fpscr;

	/*
	 * Sanitise and restore the exception रेजिस्टरs.
	 */
	fpexc = ufp_exc->fpexc;

	/* Ensure the VFP is enabled. */
	fpexc |= FPEXC_EN;

	/* Ensure FPINST2 is invalid and the exception flag is cleared. */
	fpexc &= ~(FPEXC_EX | FPEXC_FP2V);
	hwstate->fpexc = fpexc;

	hwstate->fpinst = ufp_exc->fpinst;
	hwstate->fpinst2 = ufp_exc->fpinst2;

	वापस 0;
पूर्ण

/*
 * VFP hardware can lose all context when a CPU goes offline.
 * As we will be running in SMP mode with CPU hotplug, we will save the
 * hardware state at every thपढ़ो चयन.  We clear our held state when
 * a CPU has been समाप्तed, indicating that the VFP hardware करोesn't contain
 * a thपढ़ोs VFP state.  When a CPU starts up, we re-enable access to the
 * VFP hardware. The callbacks below are called on the CPU which
 * is being offlined/onlined.
 */
अटल पूर्णांक vfp_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	vfp_current_hw_state[cpu] = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक vfp_starting_cpu(अचिन्हित पूर्णांक unused)
अणु
	vfp_enable(शून्य);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_KERNEL_MODE_NEON

अटल पूर्णांक vfp_kmode_exception(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	/*
	 * If we reach this poपूर्णांक, a भग्नing poपूर्णांक exception has been उठाओd
	 * जबतक running in kernel mode. If the NEON/VFP unit was enabled at the
	 * समय, it means a VFP inकाष्ठाion has been issued that requires
	 * software assistance to complete, something which is not currently
	 * supported in kernel mode.
	 * If the NEON/VFP unit was disabled, and the location poपूर्णांकed to below
	 * is properly preceded by a call to kernel_neon_begin(), something has
	 * caused the task to be scheduled out and back in again. In this हाल,
	 * rebuilding and running with CONFIG_DEBUG_ATOMIC_SLEEP enabled should
	 * be helpful in localizing the problem.
	 */
	अगर (fmrx(FPEXC) & FPEXC_EN)
		pr_crit("BUG: unsupported FP instruction in kernel mode\n");
	अन्यथा
		pr_crit("BUG: FP instruction issued in kernel mode with FP unit disabled\n");
	pr_crit("FPEXC == 0x%08x\n", fmrx(FPEXC));
	वापस 1;
पूर्ण

अटल काष्ठा undef_hook vfp_kmode_exception_hook[] = अणुअणु
	.instr_mask	= 0xfe000000,
	.instr_val	= 0xf2000000,
	.cpsr_mask	= MODE_MASK | PSR_T_BIT,
	.cpsr_val	= SVC_MODE,
	.fn		= vfp_kmode_exception,
पूर्ण, अणु
	.instr_mask	= 0xff100000,
	.instr_val	= 0xf4000000,
	.cpsr_mask	= MODE_MASK | PSR_T_BIT,
	.cpsr_val	= SVC_MODE,
	.fn		= vfp_kmode_exception,
पूर्ण, अणु
	.instr_mask	= 0xef000000,
	.instr_val	= 0xef000000,
	.cpsr_mask	= MODE_MASK | PSR_T_BIT,
	.cpsr_val	= SVC_MODE | PSR_T_BIT,
	.fn		= vfp_kmode_exception,
पूर्ण, अणु
	.instr_mask	= 0xff100000,
	.instr_val	= 0xf9000000,
	.cpsr_mask	= MODE_MASK | PSR_T_BIT,
	.cpsr_val	= SVC_MODE | PSR_T_BIT,
	.fn		= vfp_kmode_exception,
पूर्ण, अणु
	.instr_mask	= 0x0c000e00,
	.instr_val	= 0x0c000a00,
	.cpsr_mask	= MODE_MASK,
	.cpsr_val	= SVC_MODE,
	.fn		= vfp_kmode_exception,
पूर्णपूर्ण;

अटल पूर्णांक __init vfp_kmode_exception_hook_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vfp_kmode_exception_hook); i++)
		रेजिस्टर_undef_hook(&vfp_kmode_exception_hook[i]);
	वापस 0;
पूर्ण
subsys_initcall(vfp_kmode_exception_hook_init);

/*
 * Kernel-side NEON support functions
 */
व्योम kernel_neon_begin(व्योम)
अणु
	काष्ठा thपढ़ो_info *thपढ़ो = current_thपढ़ो_info();
	अचिन्हित पूर्णांक cpu;
	u32 fpexc;

	/*
	 * Kernel mode NEON is only allowed outside of पूर्णांकerrupt context
	 * with preemption disabled. This will make sure that the kernel
	 * mode NEON रेजिस्टर contents never need to be preserved.
	 */
	BUG_ON(in_पूर्णांकerrupt());
	cpu = get_cpu();

	fpexc = fmrx(FPEXC) | FPEXC_EN;
	fmxr(FPEXC, fpexc);

	/*
	 * Save the userland NEON/VFP state. Under UP,
	 * the owner could be a task other than 'current'
	 */
	अगर (vfp_state_in_hw(cpu, thपढ़ो))
		vfp_save_state(&thपढ़ो->vfpstate, fpexc);
#अगर_अघोषित CONFIG_SMP
	अन्यथा अगर (vfp_current_hw_state[cpu] != शून्य)
		vfp_save_state(vfp_current_hw_state[cpu], fpexc);
#पूर्ण_अगर
	vfp_current_hw_state[cpu] = शून्य;
पूर्ण
EXPORT_SYMBOL(kernel_neon_begin);

व्योम kernel_neon_end(व्योम)
अणु
	/* Disable the NEON/VFP unit. */
	fmxr(FPEXC, fmrx(FPEXC) & ~FPEXC_EN);
	put_cpu();
पूर्ण
EXPORT_SYMBOL(kernel_neon_end);

#पूर्ण_अगर /* CONFIG_KERNEL_MODE_NEON */

अटल पूर्णांक __init vfp_detect(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक instr)
अणु
	VFP_arch = अच_पूर्णांक_उच्च;	/* mark as not present */
	regs->ARM_pc += 4;
	वापस 0;
पूर्ण

अटल काष्ठा undef_hook vfp_detect_hook __initdata = अणु
	.instr_mask	= 0x0c000e00,
	.instr_val	= 0x0c000a00,
	.cpsr_mask	= MODE_MASK,
	.cpsr_val	= SVC_MODE,
	.fn		= vfp_detect,
पूर्ण;

/*
 * VFP support code initialisation.
 */
अटल पूर्णांक __init vfp_init(व्योम)
अणु
	अचिन्हित पूर्णांक vfpsid;
	अचिन्हित पूर्णांक cpu_arch = cpu_architecture();

	/*
	 * Enable the access to the VFP on all online CPUs so the
	 * following test on FPSID will succeed.
	 */
	अगर (cpu_arch >= CPU_ARCH_ARMv6)
		on_each_cpu(vfp_enable, शून्य, 1);

	/*
	 * First check that there is a VFP that we can use.
	 * The handler is alपढ़ोy setup to just log calls, so
	 * we just need to पढ़ो the VFPSID रेजिस्टर.
	 */
	रेजिस्टर_undef_hook(&vfp_detect_hook);
	barrier();
	vfpsid = fmrx(FPSID);
	barrier();
	unरेजिस्टर_undef_hook(&vfp_detect_hook);
	vfp_vector = vfp_null_entry;

	pr_info("VFP support v0.3: ");
	अगर (VFP_arch) अणु
		pr_cont("not present\n");
		वापस 0;
	/* Extract the architecture on CPUID scheme */
	पूर्ण अन्यथा अगर ((पढ़ो_cpuid_id() & 0x000f0000) == 0x000f0000) अणु
		VFP_arch = vfpsid & FPSID_CPUID_ARCH_MASK;
		VFP_arch >>= FPSID_ARCH_BIT;
		/*
		 * Check क्रम the presence of the Advanced SIMD
		 * load/store inकाष्ठाions, पूर्णांकeger and single
		 * precision भग्नing poपूर्णांक operations. Only check
		 * क्रम NEON अगर the hardware has the MVFR रेजिस्टरs.
		 */
		अगर (IS_ENABLED(CONFIG_NEON) &&
		   (fmrx(MVFR1) & 0x000fff00) == 0x00011100)
			elf_hwcap |= HWCAP_NEON;

		अगर (IS_ENABLED(CONFIG_VFPv3)) अणु
			u32 mvfr0 = fmrx(MVFR0);
			अगर (((mvfr0 & MVFR0_DP_MASK) >> MVFR0_DP_BIT) == 0x2 ||
			    ((mvfr0 & MVFR0_SP_MASK) >> MVFR0_SP_BIT) == 0x2) अणु
				elf_hwcap |= HWCAP_VFPv3;
				/*
				 * Check क्रम VFPv3 D16 and VFPv4 D16.  CPUs in
				 * this configuration only have 16 x 64bit
				 * रेजिस्टरs.
				 */
				अगर ((mvfr0 & MVFR0_A_SIMD_MASK) == 1)
					/* also v4-D16 */
					elf_hwcap |= HWCAP_VFPv3D16;
				अन्यथा
					elf_hwcap |= HWCAP_VFPD32;
			पूर्ण

			अगर ((fmrx(MVFR1) & 0xf0000000) == 0x10000000)
				elf_hwcap |= HWCAP_VFPv4;
		पूर्ण
	/* Extract the architecture version on pre-cpuid scheme */
	पूर्ण अन्यथा अणु
		अगर (vfpsid & FPSID_NODOUBLE) अणु
			pr_cont("no double precision support\n");
			वापस 0;
		पूर्ण

		VFP_arch = (vfpsid & FPSID_ARCH_MASK) >> FPSID_ARCH_BIT;
	पूर्ण

	cpuhp_setup_state_nocalls(CPUHP_AP_ARM_VFP_STARTING,
				  "arm/vfp:starting", vfp_starting_cpu,
				  vfp_dying_cpu);

	vfp_vector = vfp_support_entry;

	thपढ़ो_रेजिस्टर_notअगरier(&vfp_notअगरier_block);
	vfp_pm_init();

	/*
	 * We detected VFP, and the support code is
	 * in place; report VFP support to userspace.
	 */
	elf_hwcap |= HWCAP_VFP;

	pr_cont("implementor %02x architecture %d part %02x variant %x rev %x\n",
		(vfpsid & FPSID_IMPLEMENTER_MASK) >> FPSID_IMPLEMENTER_BIT,
		VFP_arch,
		(vfpsid & FPSID_PART_MASK) >> FPSID_PART_BIT,
		(vfpsid & FPSID_VARIANT_MASK) >> FPSID_VARIANT_BIT,
		(vfpsid & FPSID_REV_MASK) >> FPSID_REV_BIT);

	वापस 0;
पूर्ण

core_initcall(vfp_init);
