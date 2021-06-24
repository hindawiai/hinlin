<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * x86 FPU boot समय init code:
 */
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/setup.h>

#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/init.h>

/*
 * Initialize the रेजिस्टरs found in all CPUs, CR0 and CR4:
 */
अटल व्योम fpu__init_cpu_generic(व्योम)
अणु
	अचिन्हित दीर्घ cr0;
	अचिन्हित दीर्घ cr4_mask = 0;

	अगर (boot_cpu_has(X86_FEATURE_FXSR))
		cr4_mask |= X86_CR4_OSFXSR;
	अगर (boot_cpu_has(X86_FEATURE_XMM))
		cr4_mask |= X86_CR4_OSXMMEXCPT;
	अगर (cr4_mask)
		cr4_set_bits(cr4_mask);

	cr0 = पढ़ो_cr0();
	cr0 &= ~(X86_CR0_TS|X86_CR0_EM); /* clear TS and EM */
	अगर (!boot_cpu_has(X86_FEATURE_FPU))
		cr0 |= X86_CR0_EM;
	ग_लिखो_cr0(cr0);

	/* Flush out any pending x87 state: */
#अगर_घोषित CONFIG_MATH_EMULATION
	अगर (!boot_cpu_has(X86_FEATURE_FPU))
		fpstate_init_soft(&current->thपढ़ो.fpu.state.soft);
	अन्यथा
#पूर्ण_अगर
		यंत्र अस्थिर ("fninit");
पूर्ण

/*
 * Enable all supported FPU features. Called when a CPU is brought online:
 */
व्योम fpu__init_cpu(व्योम)
अणु
	fpu__init_cpu_generic();
	fpu__init_cpu_xstate();
पूर्ण

अटल bool fpu__probe_without_cpuid(व्योम)
अणु
	अचिन्हित दीर्घ cr0;
	u16 fsw, fcw;

	fsw = fcw = 0xffff;

	cr0 = पढ़ो_cr0();
	cr0 &= ~(X86_CR0_TS | X86_CR0_EM);
	ग_लिखो_cr0(cr0);

	यंत्र अस्थिर("fninit ; fnstsw %0 ; fnstcw %1" : "+m" (fsw), "+m" (fcw));

	pr_info("x86/fpu: Probing for FPU: FSW=0x%04hx FCW=0x%04hx\n", fsw, fcw);

	वापस fsw == 0 && (fcw & 0x103f) == 0x003f;
पूर्ण

अटल व्योम fpu__init_प्रणाली_early_generic(काष्ठा cpuinfo_x86 *c)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_CPUID) &&
	    !test_bit(X86_FEATURE_FPU, (अचिन्हित दीर्घ *)cpu_caps_cleared)) अणु
		अगर (fpu__probe_without_cpuid())
			setup_क्रमce_cpu_cap(X86_FEATURE_FPU);
		अन्यथा
			setup_clear_cpu_cap(X86_FEATURE_FPU);
	पूर्ण

#अगर_अघोषित CONFIG_MATH_EMULATION
	अगर (!test_cpu_cap(&boot_cpu_data, X86_FEATURE_FPU)) अणु
		pr_emerg("x86/fpu: Giving up, no FPU found and no math emulation present\n");
		क्रम (;;)
			यंत्र अस्थिर("hlt");
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Boot समय FPU feature detection code:
 */
अचिन्हित पूर्णांक mxcsr_feature_mask __पढ़ो_mostly = 0xffffffffu;
EXPORT_SYMBOL_GPL(mxcsr_feature_mask);

अटल व्योम __init fpu__init_प्रणाली_mxcsr(व्योम)
अणु
	अचिन्हित पूर्णांक mask = 0;

	अगर (boot_cpu_has(X86_FEATURE_FXSR)) अणु
		/* Static because GCC करोes not get 16-byte stack alignment right: */
		अटल काष्ठा fxregs_state fxregs __initdata;

		यंत्र अस्थिर("fxsave %0" : "+m" (fxregs));

		mask = fxregs.mxcsr_mask;

		/*
		 * If zero then use the शेष features mask,
		 * which has all features set, except the
		 * denormals-are-zero feature bit:
		 */
		अगर (mask == 0)
			mask = 0x0000ffbf;
	पूर्ण
	mxcsr_feature_mask &= mask;
पूर्ण

/*
 * Once per bootup FPU initialization sequences that will run on most x86 CPUs:
 */
अटल व्योम __init fpu__init_प्रणाली_generic(व्योम)
अणु
	/*
	 * Set up the legacy init FPU context. (xstate init might overग_लिखो this
	 * with a more modern क्रमmat, अगर the CPU supports it.)
	 */
	fpstate_init(&init_fpstate);

	fpu__init_प्रणाली_mxcsr();
पूर्ण

/*
 * Size of the FPU context state. All tasks in the प्रणाली use the
 * same context size, regardless of what portion they use.
 * This is inherent to the XSAVE architecture which माला_दो all state
 * components पूर्णांकo a single, continuous memory block:
 */
अचिन्हित पूर्णांक fpu_kernel_xstate_size;
EXPORT_SYMBOL_GPL(fpu_kernel_xstate_size);

/* Get alignment of the TYPE. */
#घोषणा TYPE_ALIGN(TYPE) दुरत्व(काष्ठा अणु अक्षर x; TYPE test; पूर्ण, test)

/*
 * Enक्रमce that 'MEMBER' is the last field of 'TYPE'.
 *
 * Align the computed size with alignment of the TYPE,
 * because that's how C aligns काष्ठाs.
 */
#घोषणा CHECK_MEMBER_AT_END_OF(TYPE, MEMBER) \
	BUILD_BUG_ON(माप(TYPE) != ALIGN(दुरत्वend(TYPE, MEMBER), \
					   TYPE_ALIGN(TYPE)))

/*
 * We append the 'struct fpu' to the task_काष्ठा:
 */
अटल व्योम __init fpu__init_task_काष्ठा_size(व्योम)
अणु
	पूर्णांक task_size = माप(काष्ठा task_काष्ठा);

	/*
	 * Subtract off the अटल size of the रेजिस्टर state.
	 * It potentially has a bunch of padding.
	 */
	task_size -= माप(((काष्ठा task_काष्ठा *)0)->thपढ़ो.fpu.state);

	/*
	 * Add back the dynamically-calculated रेजिस्टर state
	 * size.
	 */
	task_size += fpu_kernel_xstate_size;

	/*
	 * We dynamically size 'struct fpu', so we require that
	 * it be at the end of 'thread_struct' and that
	 * 'thread_struct' be at the end of 'task_struct'.  If
	 * you hit a compile error here, check the काष्ठाure to
	 * see अगर something got added to the end.
	 */
	CHECK_MEMBER_AT_END_OF(काष्ठा fpu, state);
	CHECK_MEMBER_AT_END_OF(काष्ठा thपढ़ो_काष्ठा, fpu);
	CHECK_MEMBER_AT_END_OF(काष्ठा task_काष्ठा, thपढ़ो);

	arch_task_काष्ठा_size = task_size;
पूर्ण

/*
 * Set up the user and kernel xstate sizes based on the legacy FPU context size.
 *
 * We set this up first, and later it will be overwritten by
 * fpu__init_प्रणाली_xstate() अगर the CPU knows about xstates.
 */
अटल व्योम __init fpu__init_प्रणाली_xstate_size_legacy(व्योम)
अणु
	अटल पूर्णांक on_boot_cpu __initdata = 1;

	WARN_ON_FPU(!on_boot_cpu);
	on_boot_cpu = 0;

	/*
	 * Note that xstate sizes might be overwritten later during
	 * fpu__init_प्रणाली_xstate().
	 */

	अगर (!boot_cpu_has(X86_FEATURE_FPU)) अणु
		fpu_kernel_xstate_size = माप(काष्ठा swregs_state);
	पूर्ण अन्यथा अणु
		अगर (boot_cpu_has(X86_FEATURE_FXSR))
			fpu_kernel_xstate_size =
				माप(काष्ठा fxregs_state);
		अन्यथा
			fpu_kernel_xstate_size =
				माप(काष्ठा fregs_state);
	पूर्ण

	fpu_user_xstate_size = fpu_kernel_xstate_size;
पूर्ण

/*
 * Find supported xfeatures based on cpu features and command-line input.
 * This must be called after fpu__init_parse_early_param() is called and
 * xfeatures_mask is क्रमागतerated.
 */
u64 __init fpu__get_supported_xfeatures_mask(व्योम)
अणु
	वापस XFEATURE_MASK_USER_SUPPORTED |
	       XFEATURE_MASK_SUPERVISOR_SUPPORTED;
पूर्ण

/* Legacy code to initialize eager fpu mode. */
अटल व्योम __init fpu__init_प्रणाली_ctx_चयन(व्योम)
अणु
	अटल bool on_boot_cpu __initdata = 1;

	WARN_ON_FPU(!on_boot_cpu);
	on_boot_cpu = 0;
पूर्ण

/*
 * Called on the boot CPU once per प्रणाली bootup, to set up the initial
 * FPU state that is later cloned पूर्णांकo all processes:
 */
व्योम __init fpu__init_प्रणाली(काष्ठा cpuinfo_x86 *c)
अणु
	fpu__init_प्रणाली_early_generic(c);

	/*
	 * The FPU has to be operational क्रम some of the
	 * later FPU init activities:
	 */
	fpu__init_cpu();

	fpu__init_प्रणाली_generic();
	fpu__init_प्रणाली_xstate_size_legacy();
	fpu__init_प्रणाली_xstate();
	fpu__init_task_काष्ठा_size();

	fpu__init_प्रणाली_ctx_चयन();
पूर्ण
