<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Handle detection, reporting and mitigation of Spectre v1, v2, v3a and v4, as
 * detailed at:
 *
 *   https://developer.arm.com/support/arm-security-updates/speculative-processor-vulnerability
 *
 * This code was originally written hastily under an awful lot of stress and so
 * aspects of it are somewhat hacky. Unक्रमtunately, changing anything in here
 * instantly makes me feel ill. Thanks, Jann. Thann.
 *
 * Copyright (C) 2018 ARM Ltd, All Rights Reserved.
 * Copyright (C) 2020 Google LLC
 *
 * "If there's something strange in your neighbourhood, who you gonna call?"
 *
 * Authors: Will Deacon <will@kernel.org> and Marc Zyngier <maz@kernel.org>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/cpu.h>
#समावेश <linux/device.h>
#समावेश <linux/nospec.h>
#समावेश <linux/prctl.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/spectre.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/virt.h>

/*
 * We try to ensure that the mitigation state can never change as the result of
 * onlining a late CPU.
 */
अटल व्योम update_mitigation_state(क्रमागत mitigation_state *oldp,
				    क्रमागत mitigation_state new)
अणु
	क्रमागत mitigation_state state;

	करो अणु
		state = READ_ONCE(*oldp);
		अगर (new <= state)
			अवरोध;

		/* Userspace almost certainly can't deal with this. */
		अगर (WARN_ON(प्रणाली_capabilities_finalized()))
			अवरोध;
	पूर्ण जबतक (cmpxchg_relaxed(oldp, state, new) != state);
पूर्ण

/*
 * Spectre v1.
 *
 * The kernel can't protect userspace for this one: it's each person क्रम
 * themselves. Advertise what we're करोing and be करोne with it.
 */
sमाप_प्रकार cpu_show_spectre_v1(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "Mitigation: __user pointer sanitization\n");
पूर्ण

/*
 * Spectre v2.
 *
 * This one sucks. A CPU is either:
 *
 * - Mitigated in hardware and advertised by ID_AA64PFR0_EL1.CSV2.
 * - Mitigated in hardware and listed in our "safe list".
 * - Mitigated in software by firmware.
 * - Mitigated in software by a CPU-specअगरic dance in the kernel and a
 *   firmware call at EL2.
 * - Vulnerable.
 *
 * It's not unlikely क्रम dअगरferent CPUs in a big.LITTLE प्रणाली to fall पूर्णांकo
 * dअगरferent camps.
 */
अटल क्रमागत mitigation_state spectre_v2_state;

अटल bool __पढ़ो_mostly __nospectre_v2;
अटल पूर्णांक __init parse_spectre_v2_param(अक्षर *str)
अणु
	__nospectre_v2 = true;
	वापस 0;
पूर्ण
early_param("nospectre_v2", parse_spectre_v2_param);

अटल bool spectre_v2_mitigations_off(व्योम)
अणु
	bool ret = __nospectre_v2 || cpu_mitigations_off();

	अगर (ret)
		pr_info_once("spectre-v2 mitigation disabled by command line option\n");

	वापस ret;
पूर्ण

sमाप_प्रकार cpu_show_spectre_v2(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	चयन (spectre_v2_state) अणु
	हाल SPECTRE_UNAFFECTED:
		वापस प्र_लिखो(buf, "Not affected\n");
	हाल SPECTRE_MITIGATED:
		वापस प्र_लिखो(buf, "Mitigation: Branch predictor hardening\n");
	हाल SPECTRE_VULNERABLE:
		fallthrough;
	शेष:
		वापस प्र_लिखो(buf, "Vulnerable\n");
	पूर्ण
पूर्ण

अटल क्रमागत mitigation_state spectre_v2_get_cpu_hw_mitigation_state(व्योम)
अणु
	u64 pfr0;
	अटल स्थिर काष्ठा midr_range spectre_v2_safe_list[] = अणु
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A35),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A53),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A55),
		MIDR_ALL_VERSIONS(MIDR_BRAHMA_B53),
		MIDR_ALL_VERSIONS(MIDR_HISI_TSV110),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_2XX_SILVER),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_3XX_SILVER),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_4XX_SILVER),
		अणु /* sentinel */ पूर्ण
	पूर्ण;

	/* If the CPU has CSV2 set, we're safe */
	pfr0 = पढ़ो_cpuid(ID_AA64PFR0_EL1);
	अगर (cpuid_feature_extract_अचिन्हित_field(pfr0, ID_AA64PFR0_CSV2_SHIFT))
		वापस SPECTRE_UNAFFECTED;

	/* Alternatively, we have a list of unaffected CPUs */
	अगर (is_midr_in_range_list(पढ़ो_cpuid_id(), spectre_v2_safe_list))
		वापस SPECTRE_UNAFFECTED;

	वापस SPECTRE_VULNERABLE;
पूर्ण

अटल क्रमागत mitigation_state spectre_v2_get_cpu_fw_mitigation_state(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा arm_smccc_res res;

	arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_FEATURES_FUNC_ID,
			     ARM_SMCCC_ARCH_WORKAROUND_1, &res);

	ret = res.a0;
	चयन (ret) अणु
	हाल SMCCC_RET_SUCCESS:
		वापस SPECTRE_MITIGATED;
	हाल SMCCC_ARCH_WORKAROUND_RET_UNAFFECTED:
		वापस SPECTRE_UNAFFECTED;
	शेष:
		fallthrough;
	हाल SMCCC_RET_NOT_SUPPORTED:
		वापस SPECTRE_VULNERABLE;
	पूर्ण
पूर्ण

bool has_spectre_v2(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक scope)
अणु
	WARN_ON(scope != SCOPE_LOCAL_CPU || preemptible());

	अगर (spectre_v2_get_cpu_hw_mitigation_state() == SPECTRE_UNAFFECTED)
		वापस false;

	अगर (spectre_v2_get_cpu_fw_mitigation_state() == SPECTRE_UNAFFECTED)
		वापस false;

	वापस true;
पूर्ण

क्रमागत mitigation_state arm64_get_spectre_v2_state(व्योम)
अणु
	वापस spectre_v2_state;
पूर्ण

DEFINE_PER_CPU_READ_MOSTLY(काष्ठा bp_hardening_data, bp_hardening_data);

अटल व्योम install_bp_hardening_cb(bp_hardening_cb_t fn)
अणु
	__this_cpu_ग_लिखो(bp_hardening_data.fn, fn);

	/*
	 * Vinz Clortho takes the hyp_vecs start/end "keys" at
	 * the करोor when we're a guest. Skip the hyp-vectors work.
	 */
	अगर (!is_hyp_mode_available())
		वापस;

	__this_cpu_ग_लिखो(bp_hardening_data.slot, HYP_VECTOR_SPECTRE_सूचीECT);
पूर्ण

अटल व्योम call_smc_arch_workaround_1(व्योम)
अणु
	arm_smccc_1_1_smc(ARM_SMCCC_ARCH_WORKAROUND_1, शून्य);
पूर्ण

अटल व्योम call_hvc_arch_workaround_1(व्योम)
अणु
	arm_smccc_1_1_hvc(ARM_SMCCC_ARCH_WORKAROUND_1, शून्य);
पूर्ण

अटल व्योम qcom_link_stack_sanitisation(व्योम)
अणु
	u64 पंचांगp;

	यंत्र अस्थिर("mov	%0, x30		\n"
		     ".rept	16		\n"
		     "bl	. + 4		\n"
		     ".endr			\n"
		     "mov	x30, %0		\n"
		     : "=&r" (पंचांगp));
पूर्ण

अटल bp_hardening_cb_t spectre_v2_get_sw_mitigation_cb(व्योम)
अणु
	u32 midr = पढ़ो_cpuid_id();
	अगर (((midr & MIDR_CPU_MODEL_MASK) != MIDR_QCOM_FALKOR) &&
	    ((midr & MIDR_CPU_MODEL_MASK) != MIDR_QCOM_FALKOR_V1))
		वापस शून्य;

	वापस qcom_link_stack_sanitisation;
पूर्ण

अटल क्रमागत mitigation_state spectre_v2_enable_fw_mitigation(व्योम)
अणु
	bp_hardening_cb_t cb;
	क्रमागत mitigation_state state;

	state = spectre_v2_get_cpu_fw_mitigation_state();
	अगर (state != SPECTRE_MITIGATED)
		वापस state;

	अगर (spectre_v2_mitigations_off())
		वापस SPECTRE_VULNERABLE;

	चयन (arm_smccc_1_1_get_conduit()) अणु
	हाल SMCCC_CONDUIT_HVC:
		cb = call_hvc_arch_workaround_1;
		अवरोध;

	हाल SMCCC_CONDUIT_SMC:
		cb = call_smc_arch_workaround_1;
		अवरोध;

	शेष:
		वापस SPECTRE_VULNERABLE;
	पूर्ण

	/*
	 * Prefer a CPU-specअगरic workaround अगर it exists. Note that we
	 * still rely on firmware क्रम the mitigation at EL2.
	 */
	cb = spectre_v2_get_sw_mitigation_cb() ?: cb;
	install_bp_hardening_cb(cb);
	वापस SPECTRE_MITIGATED;
पूर्ण

व्योम spectre_v2_enable_mitigation(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	क्रमागत mitigation_state state;

	WARN_ON(preemptible());

	state = spectre_v2_get_cpu_hw_mitigation_state();
	अगर (state == SPECTRE_VULNERABLE)
		state = spectre_v2_enable_fw_mitigation();

	update_mitigation_state(&spectre_v2_state, state);
पूर्ण

/*
 * Spectre-v3a.
 *
 * Phew, there's not an awful lot to करो here! We just inकाष्ठा EL2 to use
 * an indirect trampoline क्रम the hyp vectors so that guests can't पढ़ो
 * VBAR_EL2 to defeat अक्रमomisation of the hypervisor VA layout.
 */
bool has_spectre_v3a(स्थिर काष्ठा arm64_cpu_capabilities *entry, पूर्णांक scope)
अणु
	अटल स्थिर काष्ठा midr_range spectre_v3a_unsafe_list[] = अणु
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A57),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A72),
		अणुपूर्ण,
	पूर्ण;

	WARN_ON(scope != SCOPE_LOCAL_CPU || preemptible());
	वापस is_midr_in_range_list(पढ़ो_cpuid_id(), spectre_v3a_unsafe_list);
पूर्ण

व्योम spectre_v3a_enable_mitigation(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	काष्ठा bp_hardening_data *data = this_cpu_ptr(&bp_hardening_data);

	अगर (this_cpu_has_cap(ARM64_SPECTRE_V3A))
		data->slot += HYP_VECTOR_INसूचीECT;
पूर्ण

/*
 * Spectre v4.
 *
 * If you thought Spectre v2 was nasty, रुको until you see this mess. A CPU is
 * either:
 *
 * - Mitigated in hardware and listed in our "safe list".
 * - Mitigated in hardware via PSTATE.SSBS.
 * - Mitigated in software by firmware (someबार referred to as SSBD).
 *
 * Wait, that करोesn't sound so bad, करोes it? Keep पढ़ोing...
 *
 * A major source of headaches is that the software mitigation is enabled both
 * on a per-task basis, but can also be क्रमced on क्रम the kernel, necessitating
 * both context-चयन *and* entry/निकास hooks. To make it even worse, some CPUs
 * allow EL0 to toggle SSBS directly, which can end up with the prctl() state
 * being stale when re-entering the kernel. The usual big.LITTLE caveats apply,
 * so you can have प्रणालीs that have both firmware and SSBS mitigations. This
 * means we actually have to reject late onlining of CPUs with mitigations अगर
 * all of the currently onlined CPUs are safelisted, as the mitigation tends to
 * be opt-in क्रम userspace. Yes, really, the cure is worse than the disease.
 *
 * The only good part is that अगर the firmware mitigation is present, then it is
 * present क्रम all CPUs, meaning we करोn't have to worry about late onlining of a
 * vulnerable CPU अगर one of the boot CPUs is using the firmware mitigation.
 *
 * Give me a VAX-11/780 any day of the week...
 */
अटल क्रमागत mitigation_state spectre_v4_state;

/* This is the per-cpu state tracking whether we need to talk to firmware */
DEFINE_PER_CPU_READ_MOSTLY(u64, arm64_ssbd_callback_required);

क्रमागत spectre_v4_policy अणु
	SPECTRE_V4_POLICY_MITIGATION_DYNAMIC,
	SPECTRE_V4_POLICY_MITIGATION_ENABLED,
	SPECTRE_V4_POLICY_MITIGATION_DISABLED,
पूर्ण;

अटल क्रमागत spectre_v4_policy __पढ़ो_mostly __spectre_v4_policy;

अटल स्थिर काष्ठा spectre_v4_param अणु
	स्थिर अक्षर		*str;
	क्रमागत spectre_v4_policy	policy;
पूर्ण spectre_v4_params[] = अणु
	अणु "force-on",	SPECTRE_V4_POLICY_MITIGATION_ENABLED, पूर्ण,
	अणु "force-off",	SPECTRE_V4_POLICY_MITIGATION_DISABLED, पूर्ण,
	अणु "kernel",	SPECTRE_V4_POLICY_MITIGATION_DYNAMIC, पूर्ण,
पूर्ण;
अटल पूर्णांक __init parse_spectre_v4_param(अक्षर *str)
अणु
	पूर्णांक i;

	अगर (!str || !str[0])
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(spectre_v4_params); i++) अणु
		स्थिर काष्ठा spectre_v4_param *param = &spectre_v4_params[i];

		अगर (म_भेदन(str, param->str, म_माप(param->str)))
			जारी;

		__spectre_v4_policy = param->policy;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण
early_param("ssbd", parse_spectre_v4_param);

/*
 * Because this was all written in a rush by people working in dअगरferent silos,
 * we've ended up with multiple command line options to control the same thing.
 * Wrap these up in some helpers, which prefer disabling the mitigation अगर faced
 * with contradictory parameters. The mitigation is always either "off",
 * "dynamic" or "on".
 */
अटल bool spectre_v4_mitigations_off(व्योम)
अणु
	bool ret = cpu_mitigations_off() ||
		   __spectre_v4_policy == SPECTRE_V4_POLICY_MITIGATION_DISABLED;

	अगर (ret)
		pr_info_once("spectre-v4 mitigation disabled by command-line option\n");

	वापस ret;
पूर्ण

/* Do we need to toggle the mitigation state on entry to/निकास from the kernel? */
अटल bool spectre_v4_mitigations_dynamic(व्योम)
अणु
	वापस !spectre_v4_mitigations_off() &&
	       __spectre_v4_policy == SPECTRE_V4_POLICY_MITIGATION_DYNAMIC;
पूर्ण

अटल bool spectre_v4_mitigations_on(व्योम)
अणु
	वापस !spectre_v4_mitigations_off() &&
	       __spectre_v4_policy == SPECTRE_V4_POLICY_MITIGATION_ENABLED;
पूर्ण

sमाप_प्रकार cpu_show_spec_store_bypass(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	चयन (spectre_v4_state) अणु
	हाल SPECTRE_UNAFFECTED:
		वापस प्र_लिखो(buf, "Not affected\n");
	हाल SPECTRE_MITIGATED:
		वापस प्र_लिखो(buf, "Mitigation: Speculative Store Bypass disabled via prctl\n");
	हाल SPECTRE_VULNERABLE:
		fallthrough;
	शेष:
		वापस प्र_लिखो(buf, "Vulnerable\n");
	पूर्ण
पूर्ण

क्रमागत mitigation_state arm64_get_spectre_v4_state(व्योम)
अणु
	वापस spectre_v4_state;
पूर्ण

अटल क्रमागत mitigation_state spectre_v4_get_cpu_hw_mitigation_state(व्योम)
अणु
	अटल स्थिर काष्ठा midr_range spectre_v4_safe_list[] = अणु
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A35),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A53),
		MIDR_ALL_VERSIONS(MIDR_CORTEX_A55),
		MIDR_ALL_VERSIONS(MIDR_BRAHMA_B53),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_3XX_SILVER),
		MIDR_ALL_VERSIONS(MIDR_QCOM_KRYO_4XX_SILVER),
		अणु /* sentinel */ पूर्ण,
	पूर्ण;

	अगर (is_midr_in_range_list(पढ़ो_cpuid_id(), spectre_v4_safe_list))
		वापस SPECTRE_UNAFFECTED;

	/* CPU features are detected first */
	अगर (this_cpu_has_cap(ARM64_SSBS))
		वापस SPECTRE_MITIGATED;

	वापस SPECTRE_VULNERABLE;
पूर्ण

अटल क्रमागत mitigation_state spectre_v4_get_cpu_fw_mitigation_state(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा arm_smccc_res res;

	arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_FEATURES_FUNC_ID,
			     ARM_SMCCC_ARCH_WORKAROUND_2, &res);

	ret = res.a0;
	चयन (ret) अणु
	हाल SMCCC_RET_SUCCESS:
		वापस SPECTRE_MITIGATED;
	हाल SMCCC_ARCH_WORKAROUND_RET_UNAFFECTED:
		fallthrough;
	हाल SMCCC_RET_NOT_REQUIRED:
		वापस SPECTRE_UNAFFECTED;
	शेष:
		fallthrough;
	हाल SMCCC_RET_NOT_SUPPORTED:
		वापस SPECTRE_VULNERABLE;
	पूर्ण
पूर्ण

bool has_spectre_v4(स्थिर काष्ठा arm64_cpu_capabilities *cap, पूर्णांक scope)
अणु
	क्रमागत mitigation_state state;

	WARN_ON(scope != SCOPE_LOCAL_CPU || preemptible());

	state = spectre_v4_get_cpu_hw_mitigation_state();
	अगर (state == SPECTRE_VULNERABLE)
		state = spectre_v4_get_cpu_fw_mitigation_state();

	वापस state != SPECTRE_UNAFFECTED;
पूर्ण

अटल पूर्णांक ssbs_emulation_handler(काष्ठा pt_regs *regs, u32 instr)
अणु
	अगर (user_mode(regs))
		वापस 1;

	अगर (instr & BIT(PSTATE_Imm_shअगरt))
		regs->pstate |= PSR_SSBS_BIT;
	अन्यथा
		regs->pstate &= ~PSR_SSBS_BIT;

	arm64_skip_faulting_inकाष्ठाion(regs, 4);
	वापस 0;
पूर्ण

अटल काष्ठा undef_hook ssbs_emulation_hook = अणु
	.instr_mask	= ~(1U << PSTATE_Imm_shअगरt),
	.instr_val	= 0xd500401f | PSTATE_SSBS,
	.fn		= ssbs_emulation_handler,
पूर्ण;

अटल क्रमागत mitigation_state spectre_v4_enable_hw_mitigation(व्योम)
अणु
	अटल bool undef_hook_रेजिस्टरed = false;
	अटल DEFINE_RAW_SPINLOCK(hook_lock);
	क्रमागत mitigation_state state;

	/*
	 * If the प्रणाली is mitigated but this CPU करोesn't have SSBS, then
	 * we must be on the safelist and there's nothing more to करो.
	 */
	state = spectre_v4_get_cpu_hw_mitigation_state();
	अगर (state != SPECTRE_MITIGATED || !this_cpu_has_cap(ARM64_SSBS))
		वापस state;

	raw_spin_lock(&hook_lock);
	अगर (!undef_hook_रेजिस्टरed) अणु
		रेजिस्टर_undef_hook(&ssbs_emulation_hook);
		undef_hook_रेजिस्टरed = true;
	पूर्ण
	raw_spin_unlock(&hook_lock);

	अगर (spectre_v4_mitigations_off()) अणु
		sysreg_clear_set(sctlr_el1, 0, SCTLR_ELx_DSSBS);
		set_pstate_ssbs(1);
		वापस SPECTRE_VULNERABLE;
	पूर्ण

	/* SCTLR_EL1.DSSBS was initialised to 0 during boot */
	set_pstate_ssbs(0);
	वापस SPECTRE_MITIGATED;
पूर्ण

/*
 * Patch a branch over the Spectre-v4 mitigation code with a NOP so that
 * we fallthrough and check whether firmware needs to be called on this CPU.
 */
व्योम __init spectre_v4_patch_fw_mitigation_enable(काष्ठा alt_instr *alt,
						  __le32 *origptr,
						  __le32 *updptr, पूर्णांक nr_inst)
अणु
	BUG_ON(nr_inst != 1); /* Branch -> NOP */

	अगर (spectre_v4_mitigations_off())
		वापस;

	अगर (cpus_have_final_cap(ARM64_SSBS))
		वापस;

	अगर (spectre_v4_mitigations_dynamic())
		*updptr = cpu_to_le32(aarch64_insn_gen_nop());
पूर्ण

/*
 * Patch a NOP in the Spectre-v4 mitigation code with an SMC/HVC inकाष्ठाion
 * to call पूर्णांकo firmware to adjust the mitigation state.
 */
व्योम __init spectre_v4_patch_fw_mitigation_conduit(काष्ठा alt_instr *alt,
						   __le32 *origptr,
						   __le32 *updptr, पूर्णांक nr_inst)
अणु
	u32 insn;

	BUG_ON(nr_inst != 1); /* NOP -> HVC/SMC */

	चयन (arm_smccc_1_1_get_conduit()) अणु
	हाल SMCCC_CONDUIT_HVC:
		insn = aarch64_insn_get_hvc_value();
		अवरोध;
	हाल SMCCC_CONDUIT_SMC:
		insn = aarch64_insn_get_smc_value();
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	*updptr = cpu_to_le32(insn);
पूर्ण

अटल क्रमागत mitigation_state spectre_v4_enable_fw_mitigation(व्योम)
अणु
	क्रमागत mitigation_state state;

	state = spectre_v4_get_cpu_fw_mitigation_state();
	अगर (state != SPECTRE_MITIGATED)
		वापस state;

	अगर (spectre_v4_mitigations_off()) अणु
		arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_WORKAROUND_2, false, शून्य);
		वापस SPECTRE_VULNERABLE;
	पूर्ण

	arm_smccc_1_1_invoke(ARM_SMCCC_ARCH_WORKAROUND_2, true, शून्य);

	अगर (spectre_v4_mitigations_dynamic())
		__this_cpu_ग_लिखो(arm64_ssbd_callback_required, 1);

	वापस SPECTRE_MITIGATED;
पूर्ण

व्योम spectre_v4_enable_mitigation(स्थिर काष्ठा arm64_cpu_capabilities *__unused)
अणु
	क्रमागत mitigation_state state;

	WARN_ON(preemptible());

	state = spectre_v4_enable_hw_mitigation();
	अगर (state == SPECTRE_VULNERABLE)
		state = spectre_v4_enable_fw_mitigation();

	update_mitigation_state(&spectre_v4_state, state);
पूर्ण

अटल व्योम __update_pstate_ssbs(काष्ठा pt_regs *regs, bool state)
अणु
	u64 bit = compat_user_mode(regs) ? PSR_AA32_SSBS_BIT : PSR_SSBS_BIT;

	अगर (state)
		regs->pstate |= bit;
	अन्यथा
		regs->pstate &= ~bit;
पूर्ण

व्योम spectre_v4_enable_task_mitigation(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(tsk);
	bool ssbs = false, kthपढ़ो = tsk->flags & PF_KTHREAD;

	अगर (spectre_v4_mitigations_off())
		ssbs = true;
	अन्यथा अगर (spectre_v4_mitigations_dynamic() && !kthपढ़ो)
		ssbs = !test_tsk_thपढ़ो_flag(tsk, TIF_SSBD);

	__update_pstate_ssbs(regs, ssbs);
पूर्ण

/*
 * The Spectre-v4 mitigation can be controlled via a prctl() from userspace.
 * This is पूर्णांकeresting because the "speculation disabled" behaviour can be
 * configured so that it is preserved across exec(), which means that the
 * prctl() may be necessary even when PSTATE.SSBS can be toggled directly
 * from userspace.
 */
अटल व्योम ssbd_prctl_enable_mitigation(काष्ठा task_काष्ठा *task)
अणु
	task_clear_spec_ssb_noexec(task);
	task_set_spec_ssb_disable(task);
	set_tsk_thपढ़ो_flag(task, TIF_SSBD);
पूर्ण

अटल व्योम ssbd_prctl_disable_mitigation(काष्ठा task_काष्ठा *task)
अणु
	task_clear_spec_ssb_noexec(task);
	task_clear_spec_ssb_disable(task);
	clear_tsk_thपढ़ो_flag(task, TIF_SSBD);
पूर्ण

अटल पूर्णांक ssbd_prctl_set(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ ctrl)
अणु
	चयन (ctrl) अणु
	हाल PR_SPEC_ENABLE:
		/* Enable speculation: disable mitigation */
		/*
		 * Force disabled speculation prevents it from being
		 * re-enabled.
		 */
		अगर (task_spec_ssb_क्रमce_disable(task))
			वापस -EPERM;

		/*
		 * If the mitigation is क्रमced on, then speculation is क्रमced
		 * off and we again prevent it from being re-enabled.
		 */
		अगर (spectre_v4_mitigations_on())
			वापस -EPERM;

		ssbd_prctl_disable_mitigation(task);
		अवरोध;
	हाल PR_SPEC_FORCE_DISABLE:
		/* Force disable speculation: क्रमce enable mitigation */
		/*
		 * If the mitigation is क्रमced off, then speculation is क्रमced
		 * on and we prevent it from being disabled.
		 */
		अगर (spectre_v4_mitigations_off())
			वापस -EPERM;

		task_set_spec_ssb_क्रमce_disable(task);
		fallthrough;
	हाल PR_SPEC_DISABLE:
		/* Disable speculation: enable mitigation */
		/* Same as PR_SPEC_FORCE_DISABLE */
		अगर (spectre_v4_mitigations_off())
			वापस -EPERM;

		ssbd_prctl_enable_mitigation(task);
		अवरोध;
	हाल PR_SPEC_DISABLE_NOEXEC:
		/* Disable speculation until execve(): enable mitigation */
		/*
		 * If the mitigation state is क्रमced one way or the other, then
		 * we must fail now beक्रमe we try to toggle it on execve().
		 */
		अगर (task_spec_ssb_क्रमce_disable(task) ||
		    spectre_v4_mitigations_off() ||
		    spectre_v4_mitigations_on()) अणु
			वापस -EPERM;
		पूर्ण

		ssbd_prctl_enable_mitigation(task);
		task_set_spec_ssb_noexec(task);
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	spectre_v4_enable_task_mitigation(task);
	वापस 0;
पूर्ण

पूर्णांक arch_prctl_spec_ctrl_set(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ which,
			     अचिन्हित दीर्घ ctrl)
अणु
	चयन (which) अणु
	हाल PR_SPEC_STORE_BYPASS:
		वापस ssbd_prctl_set(task, ctrl);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक ssbd_prctl_get(काष्ठा task_काष्ठा *task)
अणु
	चयन (spectre_v4_state) अणु
	हाल SPECTRE_UNAFFECTED:
		वापस PR_SPEC_NOT_AFFECTED;
	हाल SPECTRE_MITIGATED:
		अगर (spectre_v4_mitigations_on())
			वापस PR_SPEC_NOT_AFFECTED;

		अगर (spectre_v4_mitigations_dynamic())
			अवरोध;

		/* Mitigations are disabled, so we're vulnerable. */
		fallthrough;
	हाल SPECTRE_VULNERABLE:
		fallthrough;
	शेष:
		वापस PR_SPEC_ENABLE;
	पूर्ण

	/* Check the mitigation state क्रम this task */
	अगर (task_spec_ssb_क्रमce_disable(task))
		वापस PR_SPEC_PRCTL | PR_SPEC_FORCE_DISABLE;

	अगर (task_spec_ssb_noexec(task))
		वापस PR_SPEC_PRCTL | PR_SPEC_DISABLE_NOEXEC;

	अगर (task_spec_ssb_disable(task))
		वापस PR_SPEC_PRCTL | PR_SPEC_DISABLE;

	वापस PR_SPEC_PRCTL | PR_SPEC_ENABLE;
पूर्ण

पूर्णांक arch_prctl_spec_ctrl_get(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ which)
अणु
	चयन (which) अणु
	हाल PR_SPEC_STORE_BYPASS:
		वापस ssbd_prctl_get(task);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण
