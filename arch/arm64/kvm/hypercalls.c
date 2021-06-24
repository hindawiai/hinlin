<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Arm Ltd.

#समावेश <linux/arm-smccc.h>
#समावेश <linux/kvm_host.h>

#समावेश <यंत्र/kvm_emulate.h>

#समावेश <kvm/arm_hypercalls.h>
#समावेश <kvm/arm_psci.h>

अटल व्योम kvm_ptp_get_समय(काष्ठा kvm_vcpu *vcpu, u64 *val)
अणु
	काष्ठा प्रणाली_समय_snapshot sysसमय_snapshot;
	u64 cycles = ~0UL;
	u32 feature;

	/*
	 * प्रणाली समय and counter value must captured at the same
	 * समय to keep consistency and precision.
	 */
	kसमय_get_snapshot(&sysसमय_snapshot);

	/*
	 * This is only valid अगर the current घड़ीsource is the
	 * architected counter, as this is the only one the guest
	 * can see.
	 */
	अगर (sysसमय_snapshot.cs_id != CSID_ARM_ARCH_COUNTER)
		वापस;

	/*
	 * The guest selects one of the two reference counters
	 * (भव or physical) with the first argument of the SMCCC
	 * call. In हाल the identअगरier is not supported, error out.
	 */
	feature = smccc_get_arg1(vcpu);
	चयन (feature) अणु
	हाल KVM_PTP_VIRT_COUNTER:
		cycles = sysसमय_snapshot.cycles - vcpu_पढ़ो_sys_reg(vcpu, CNTVOFF_EL2);
		अवरोध;
	हाल KVM_PTP_PHYS_COUNTER:
		cycles = sysसमय_snapshot.cycles;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/*
	 * This relies on the top bit of val[0] never being set क्रम
	 * valid values of प्रणाली समय, because that is *really* far
	 * in the future (about 292 years from 1970, and at that stage
	 * nobody will give a damn about it).
	 */
	val[0] = upper_32_bits(sysसमय_snapshot.real);
	val[1] = lower_32_bits(sysसमय_snapshot.real);
	val[2] = upper_32_bits(cycles);
	val[3] = lower_32_bits(cycles);
पूर्ण

पूर्णांक kvm_hvc_call_handler(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 func_id = smccc_get_function(vcpu);
	u64 val[4] = अणुSMCCC_RET_NOT_SUPPORTEDपूर्ण;
	u32 feature;
	gpa_t gpa;

	चयन (func_id) अणु
	हाल ARM_SMCCC_VERSION_FUNC_ID:
		val[0] = ARM_SMCCC_VERSION_1_1;
		अवरोध;
	हाल ARM_SMCCC_ARCH_FEATURES_FUNC_ID:
		feature = smccc_get_arg1(vcpu);
		चयन (feature) अणु
		हाल ARM_SMCCC_ARCH_WORKAROUND_1:
			चयन (arm64_get_spectre_v2_state()) अणु
			हाल SPECTRE_VULNERABLE:
				अवरोध;
			हाल SPECTRE_MITIGATED:
				val[0] = SMCCC_RET_SUCCESS;
				अवरोध;
			हाल SPECTRE_UNAFFECTED:
				val[0] = SMCCC_ARCH_WORKAROUND_RET_UNAFFECTED;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल ARM_SMCCC_ARCH_WORKAROUND_2:
			चयन (arm64_get_spectre_v4_state()) अणु
			हाल SPECTRE_VULNERABLE:
				अवरोध;
			हाल SPECTRE_MITIGATED:
				/*
				 * SSBS everywhere: Indicate no firmware
				 * support, as the SSBS support will be
				 * indicated to the guest and the शेष is
				 * safe.
				 *
				 * Otherwise, expose a permanent mitigation
				 * to the guest, and hide SSBS so that the
				 * guest stays रक्षित.
				 */
				अगर (cpus_have_final_cap(ARM64_SSBS))
					अवरोध;
				fallthrough;
			हाल SPECTRE_UNAFFECTED:
				val[0] = SMCCC_RET_NOT_REQUIRED;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल ARM_SMCCC_HV_PV_TIME_FEATURES:
			val[0] = SMCCC_RET_SUCCESS;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ARM_SMCCC_HV_PV_TIME_FEATURES:
		val[0] = kvm_hypercall_pv_features(vcpu);
		अवरोध;
	हाल ARM_SMCCC_HV_PV_TIME_ST:
		gpa = kvm_init_stolen_समय(vcpu);
		अगर (gpa != GPA_INVALID)
			val[0] = gpa;
		अवरोध;
	हाल ARM_SMCCC_VENDOR_HYP_CALL_UID_FUNC_ID:
		val[0] = ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_0;
		val[1] = ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_1;
		val[2] = ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_2;
		val[3] = ARM_SMCCC_VENDOR_HYP_UID_KVM_REG_3;
		अवरोध;
	हाल ARM_SMCCC_VENDOR_HYP_KVM_FEATURES_FUNC_ID:
		val[0] = BIT(ARM_SMCCC_KVM_FUNC_FEATURES);
		val[0] |= BIT(ARM_SMCCC_KVM_FUNC_PTP);
		अवरोध;
	हाल ARM_SMCCC_VENDOR_HYP_KVM_PTP_FUNC_ID:
		kvm_ptp_get_समय(vcpu, val);
		अवरोध;
	हाल ARM_SMCCC_TRNG_VERSION:
	हाल ARM_SMCCC_TRNG_FEATURES:
	हाल ARM_SMCCC_TRNG_GET_UUID:
	हाल ARM_SMCCC_TRNG_RND32:
	हाल ARM_SMCCC_TRNG_RND64:
		वापस kvm_trng_call(vcpu);
	शेष:
		वापस kvm_psci_call(vcpu);
	पूर्ण

	smccc_set_retval(vcpu, val[0], val[1], val[2], val[3]);
	वापस 1;
पूर्ण
