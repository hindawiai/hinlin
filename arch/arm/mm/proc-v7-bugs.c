<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/arm-smccc.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#अगर_घोषित CONFIG_HARDEN_BRANCH_PREDICTOR
DEFINE_PER_CPU(harden_branch_predictor_fn_t, harden_branch_predictor_fn);

बाह्य व्योम cpu_v7_iciallu_चयन_mm(phys_addr_t pgd_phys, काष्ठा mm_काष्ठा *mm);
बाह्य व्योम cpu_v7_bpiall_चयन_mm(phys_addr_t pgd_phys, काष्ठा mm_काष्ठा *mm);
बाह्य व्योम cpu_v7_smc_चयन_mm(phys_addr_t pgd_phys, काष्ठा mm_काष्ठा *mm);
बाह्य व्योम cpu_v7_hvc_चयन_mm(phys_addr_t pgd_phys, काष्ठा mm_काष्ठा *mm);

अटल व्योम harden_branch_predictor_bpiall(व्योम)
अणु
	ग_लिखो_sysreg(0, BPIALL);
पूर्ण

अटल व्योम harden_branch_predictor_iciallu(व्योम)
अणु
	ग_लिखो_sysreg(0, ICIALLU);
पूर्ण

अटल व्योम __maybe_unused call_smc_arch_workaround_1(व्योम)
अणु
	arm_smccc_1_1_smc(ARM_SMCCC_ARCH_WORKAROUND_1, शून्य);
पूर्ण

अटल व्योम __maybe_unused call_hvc_arch_workaround_1(व्योम)
अणु
	arm_smccc_1_1_hvc(ARM_SMCCC_ARCH_WORKAROUND_1, शून्य);
पूर्ण

अटल व्योम cpu_v7_spectre_init(व्योम)
अणु
	स्थिर अक्षर *spectre_v2_method = शून्य;
	पूर्णांक cpu = smp_processor_id();

	अगर (per_cpu(harden_branch_predictor_fn, cpu))
		वापस;

	चयन (पढ़ो_cpuid_part()) अणु
	हाल ARM_CPU_PART_CORTEX_A8:
	हाल ARM_CPU_PART_CORTEX_A9:
	हाल ARM_CPU_PART_CORTEX_A12:
	हाल ARM_CPU_PART_CORTEX_A17:
	हाल ARM_CPU_PART_CORTEX_A73:
	हाल ARM_CPU_PART_CORTEX_A75:
		per_cpu(harden_branch_predictor_fn, cpu) =
			harden_branch_predictor_bpiall;
		spectre_v2_method = "BPIALL";
		अवरोध;

	हाल ARM_CPU_PART_CORTEX_A15:
	हाल ARM_CPU_PART_BRAHMA_B15:
		per_cpu(harden_branch_predictor_fn, cpu) =
			harden_branch_predictor_iciallu;
		spectre_v2_method = "ICIALLU";
		अवरोध;

#अगर_घोषित CONFIG_ARM_PSCI
	हाल ARM_CPU_PART_BRAHMA_B53:
		/* Requires no workaround */
		अवरोध;
	शेष:
		/* Other ARM CPUs require no workaround */
		अगर (पढ़ो_cpuid_implementor() == ARM_CPU_IMP_ARM)
			अवरोध;
		fallthrough;
		/* Cortex A57/A72 require firmware workaround */
	हाल ARM_CPU_PART_CORTEX_A57:
	हाल ARM_CPU_PART_CORTEX_A72: अणु
		काष्ठा arm_smccc_res res;

		arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_FEATURES_FUNC_ID,
				     ARM_SMCCC_ARCH_WORKAROUND_1, &res);
		अगर ((पूर्णांक)res.a0 != 0)
			वापस;

		चयन (arm_smccc_1_1_get_conduit()) अणु
		हाल SMCCC_CONDUIT_HVC:
			per_cpu(harden_branch_predictor_fn, cpu) =
				call_hvc_arch_workaround_1;
			cpu_करो_चयन_mm = cpu_v7_hvc_चयन_mm;
			spectre_v2_method = "hypervisor";
			अवरोध;

		हाल SMCCC_CONDUIT_SMC:
			per_cpu(harden_branch_predictor_fn, cpu) =
				call_smc_arch_workaround_1;
			cpu_करो_चयन_mm = cpu_v7_smc_चयन_mm;
			spectre_v2_method = "firmware";
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (spectre_v2_method)
		pr_info("CPU%u: Spectre v2: using %s workaround\n",
			smp_processor_id(), spectre_v2_method);
पूर्ण
#अन्यथा
अटल व्योम cpu_v7_spectre_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल __maybe_unused bool cpu_v7_check_auxcr_set(bool *warned,
						  u32 mask, स्थिर अक्षर *msg)
अणु
	u32 aux_cr;

	यंत्र("mrc p15, 0, %0, c1, c0, 1" : "=r" (aux_cr));

	अगर ((aux_cr & mask) != mask) अणु
		अगर (!*warned)
			pr_err("CPU%u: %s", smp_processor_id(), msg);
		*warned = true;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल DEFINE_PER_CPU(bool, spectre_warned);

अटल bool check_spectre_auxcr(bool *warned, u32 bit)
अणु
	वापस IS_ENABLED(CONFIG_HARDEN_BRANCH_PREDICTOR) &&
		cpu_v7_check_auxcr_set(warned, bit,
				       "Spectre v2: firmware did not set auxiliary control register IBE bit, system vulnerable\n");
पूर्ण

व्योम cpu_v7_ca8_ibe(व्योम)
अणु
	अगर (check_spectre_auxcr(this_cpu_ptr(&spectre_warned), BIT(6)))
		cpu_v7_spectre_init();
पूर्ण

व्योम cpu_v7_ca15_ibe(व्योम)
अणु
	अगर (check_spectre_auxcr(this_cpu_ptr(&spectre_warned), BIT(0)))
		cpu_v7_spectre_init();
पूर्ण

व्योम cpu_v7_bugs_init(व्योम)
अणु
	cpu_v7_spectre_init();
पूर्ण
