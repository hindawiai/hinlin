<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 *
 * Derived from arch/arm/kvm/reset.c
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <kvm/arm_arch_समयr.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/fpsimd.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/virt.h>

/* Maximum phys_shअगरt supported क्रम any VM on this host */
अटल u32 kvm_ipa_limit;

/*
 * ARMv8 Reset Values
 */
#घोषणा VCPU_RESET_PSTATE_EL1	(PSR_MODE_EL1h | PSR_A_BIT | PSR_I_BIT | \
				 PSR_F_BIT | PSR_D_BIT)

#घोषणा VCPU_RESET_PSTATE_SVC	(PSR_AA32_MODE_SVC | PSR_AA32_A_BIT | \
				 PSR_AA32_I_BIT | PSR_AA32_F_BIT)

अचिन्हित पूर्णांक kvm_sve_max_vl;

पूर्णांक kvm_arm_init_sve(व्योम)
अणु
	अगर (प्रणाली_supports_sve()) अणु
		kvm_sve_max_vl = sve_max_भवisable_vl;

		/*
		 * The get_sve_reg()/set_sve_reg() ioctl पूर्णांकerface will need
		 * to be extended with multiple रेजिस्टर slice support in
		 * order to support vector lengths greater than
		 * SVE_VL_ARCH_MAX:
		 */
		अगर (WARN_ON(kvm_sve_max_vl > SVE_VL_ARCH_MAX))
			kvm_sve_max_vl = SVE_VL_ARCH_MAX;

		/*
		 * Don't even try to make use of vector lengths that
		 * aren't available on all CPUs, क्रम now:
		 */
		अगर (kvm_sve_max_vl < sve_max_vl)
			pr_warn("KVM: SVE vector length for guests limited to %u bytes\n",
				kvm_sve_max_vl);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_enable_sve(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (!प्रणाली_supports_sve())
		वापस -EINVAL;

	vcpu->arch.sve_max_vl = kvm_sve_max_vl;

	/*
	 * Userspace can still customize the vector lengths by writing
	 * KVM_REG_ARM64_SVE_VLS.  Allocation is deferred until
	 * kvm_arm_vcpu_finalize(), which मुक्तzes the configuration.
	 */
	vcpu->arch.flags |= KVM_ARM64_GUEST_HAS_SVE;

	वापस 0;
पूर्ण

/*
 * Finalize vcpu's maximum SVE vector length, allocating
 * vcpu->arch.sve_state as necessary.
 */
अटल पूर्णांक kvm_vcpu_finalize_sve(काष्ठा kvm_vcpu *vcpu)
अणु
	व्योम *buf;
	अचिन्हित पूर्णांक vl;

	vl = vcpu->arch.sve_max_vl;

	/*
	 * Responsibility क्रम these properties is shared between
	 * kvm_arm_init_arch_resources(), kvm_vcpu_enable_sve() and
	 * set_sve_vls().  Double-check here just to be sure:
	 */
	अगर (WARN_ON(!sve_vl_valid(vl) || vl > sve_max_भवisable_vl ||
		    vl > SVE_VL_ARCH_MAX))
		वापस -EIO;

	buf = kzalloc(SVE_SIG_REGS_SIZE(sve_vq_from_vl(vl)), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	vcpu->arch.sve_state = buf;
	vcpu->arch.flags |= KVM_ARM64_VCPU_SVE_FINALIZED;
	वापस 0;
पूर्ण

पूर्णांक kvm_arm_vcpu_finalize(काष्ठा kvm_vcpu *vcpu, पूर्णांक feature)
अणु
	चयन (feature) अणु
	हाल KVM_ARM_VCPU_SVE:
		अगर (!vcpu_has_sve(vcpu))
			वापस -EINVAL;

		अगर (kvm_arm_vcpu_sve_finalized(vcpu))
			वापस -EPERM;

		वापस kvm_vcpu_finalize_sve(vcpu);
	पूर्ण

	वापस -EINVAL;
पूर्ण

bool kvm_arm_vcpu_is_finalized(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_has_sve(vcpu) && !kvm_arm_vcpu_sve_finalized(vcpu))
		वापस false;

	वापस true;
पूर्ण

व्योम kvm_arm_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	kमुक्त(vcpu->arch.sve_state);
पूर्ण

अटल व्योम kvm_vcpu_reset_sve(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu_has_sve(vcpu))
		स_रखो(vcpu->arch.sve_state, 0, vcpu_sve_state_size(vcpu));
पूर्ण

अटल पूर्णांक kvm_vcpu_enable_ptrauth(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * For now make sure that both address/generic poपूर्णांकer authentication
	 * features are requested by the userspace together and the प्रणाली
	 * supports these capabilities.
	 */
	अगर (!test_bit(KVM_ARM_VCPU_PTRAUTH_ADDRESS, vcpu->arch.features) ||
	    !test_bit(KVM_ARM_VCPU_PTRAUTH_GENERIC, vcpu->arch.features) ||
	    !प्रणाली_has_full_ptr_auth())
		वापस -EINVAL;

	vcpu->arch.flags |= KVM_ARM64_GUEST_HAS_PTRAUTH;
	वापस 0;
पूर्ण

अटल bool vcpu_allowed_रेजिस्टर_width(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu *पंचांगp;
	bool is32bit;
	पूर्णांक i;

	is32bit = vcpu_has_feature(vcpu, KVM_ARM_VCPU_EL1_32BIT);
	अगर (!cpus_have_स्थिर_cap(ARM64_HAS_32BIT_EL1) && is32bit)
		वापस false;

	/* Check that the vcpus are either all 32bit or all 64bit */
	kvm_क्रम_each_vcpu(i, पंचांगp, vcpu->kvm) अणु
		अगर (vcpu_has_feature(पंचांगp, KVM_ARM_VCPU_EL1_32BIT) != is32bit)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * kvm_reset_vcpu - sets core रेजिस्टरs and sys_regs to reset value
 * @vcpu: The VCPU poपूर्णांकer
 *
 * This function finds the right table above and sets the रेजिस्टरs on
 * the भव CPU काष्ठा to their architecturally defined reset
 * values, except क्रम रेजिस्टरs whose reset is deferred until
 * kvm_arm_vcpu_finalize().
 *
 * Note: This function can be called from two paths: The KVM_ARM_VCPU_INIT
 * ioctl or as part of handling a request issued by another VCPU in the PSCI
 * handling code.  In the first हाल, the VCPU will not be loaded, and in the
 * second हाल the VCPU will be loaded.  Because this function operates purely
 * on the memory-backed values of प्रणाली रेजिस्टरs, we want to करो a full put अगर
 * we were loaded (handling a request) and load the values back at the end of
 * the function.  Otherwise we leave the state alone.  In both हालs, we
 * disable preemption around the vcpu reset as we would otherwise race with
 * preempt notअगरiers which also call put/load.
 */
पूर्णांक kvm_reset_vcpu(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक ret;
	bool loaded;
	u32 pstate;

	/* Reset PMU outside of the non-preemptible section */
	kvm_pmu_vcpu_reset(vcpu);

	preempt_disable();
	loaded = (vcpu->cpu != -1);
	अगर (loaded)
		kvm_arch_vcpu_put(vcpu);

	अगर (!kvm_arm_vcpu_sve_finalized(vcpu)) अणु
		अगर (test_bit(KVM_ARM_VCPU_SVE, vcpu->arch.features)) अणु
			ret = kvm_vcpu_enable_sve(vcpu);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		kvm_vcpu_reset_sve(vcpu);
	पूर्ण

	अगर (test_bit(KVM_ARM_VCPU_PTRAUTH_ADDRESS, vcpu->arch.features) ||
	    test_bit(KVM_ARM_VCPU_PTRAUTH_GENERIC, vcpu->arch.features)) अणु
		अगर (kvm_vcpu_enable_ptrauth(vcpu)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!vcpu_allowed_रेजिस्टर_width(vcpu)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (vcpu->arch.target) अणु
	शेष:
		अगर (test_bit(KVM_ARM_VCPU_EL1_32BIT, vcpu->arch.features)) अणु
			pstate = VCPU_RESET_PSTATE_SVC;
		पूर्ण अन्यथा अणु
			pstate = VCPU_RESET_PSTATE_EL1;
		पूर्ण

		अगर (kvm_vcpu_has_pmu(vcpu) && !kvm_arm_support_pmu_v3()) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अवरोध;
	पूर्ण

	/* Reset core रेजिस्टरs */
	स_रखो(vcpu_gp_regs(vcpu), 0, माप(*vcpu_gp_regs(vcpu)));
	स_रखो(&vcpu->arch.ctxt.fp_regs, 0, माप(vcpu->arch.ctxt.fp_regs));
	vcpu->arch.ctxt.spsr_abt = 0;
	vcpu->arch.ctxt.spsr_und = 0;
	vcpu->arch.ctxt.spsr_irq = 0;
	vcpu->arch.ctxt.spsr_fiq = 0;
	vcpu_gp_regs(vcpu)->pstate = pstate;

	/* Reset प्रणाली रेजिस्टरs */
	kvm_reset_sys_regs(vcpu);

	/*
	 * Additional reset state handling that PSCI may have imposed on us.
	 * Must be करोne after all the sys_reg reset.
	 */
	अगर (vcpu->arch.reset_state.reset) अणु
		अचिन्हित दीर्घ target_pc = vcpu->arch.reset_state.pc;

		/* Gracefully handle Thumb2 entry poपूर्णांक */
		अगर (vcpu_mode_is_32bit(vcpu) && (target_pc & 1)) अणु
			target_pc &= ~1UL;
			vcpu_set_thumb(vcpu);
		पूर्ण

		/* Propagate caller endianness */
		अगर (vcpu->arch.reset_state.be)
			kvm_vcpu_set_be(vcpu);

		*vcpu_pc(vcpu) = target_pc;
		vcpu_set_reg(vcpu, 0, vcpu->arch.reset_state.r0);

		vcpu->arch.reset_state.reset = false;
	पूर्ण

	/* Reset समयr */
	ret = kvm_समयr_vcpu_reset(vcpu);
out:
	अगर (loaded)
		kvm_arch_vcpu_load(vcpu, smp_processor_id());
	preempt_enable();
	वापस ret;
पूर्ण

u32 get_kvm_ipa_limit(व्योम)
अणु
	वापस kvm_ipa_limit;
पूर्ण

पूर्णांक kvm_set_ipa_limit(व्योम)
अणु
	अचिन्हित पूर्णांक parange, tgran_2;
	u64 mmfr0;

	mmfr0 = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	parange = cpuid_feature_extract_अचिन्हित_field(mmfr0,
				ID_AA64MMFR0_PARANGE_SHIFT);

	/*
	 * Check with ARMv8.5-GTG that our PAGE_SIZE is supported at
	 * Stage-2. If not, things will stop very quickly.
	 */
	चयन (PAGE_SIZE) अणु
	शेष:
	हाल SZ_4K:
		tgran_2 = ID_AA64MMFR0_TGRAN4_2_SHIFT;
		अवरोध;
	हाल SZ_16K:
		tgran_2 = ID_AA64MMFR0_TGRAN16_2_SHIFT;
		अवरोध;
	हाल SZ_64K:
		tgran_2 = ID_AA64MMFR0_TGRAN64_2_SHIFT;
		अवरोध;
	पूर्ण

	चयन (cpuid_feature_extract_अचिन्हित_field(mmfr0, tgran_2)) अणु
	हाल ID_AA64MMFR0_TGRAN_2_SUPPORTED_NONE:
		kvm_err("PAGE_SIZE not supported at Stage-2, giving up\n");
		वापस -EINVAL;
	हाल ID_AA64MMFR0_TGRAN_2_SUPPORTED_DEFAULT:
		kvm_debug("PAGE_SIZE supported at Stage-2 (default)\n");
		अवरोध;
	हाल ID_AA64MMFR0_TGRAN_2_SUPPORTED_MIN ... ID_AA64MMFR0_TGRAN_2_SUPPORTED_MAX:
		kvm_debug("PAGE_SIZE supported at Stage-2 (advertised)\n");
		अवरोध;
	शेष:
		kvm_err("Unsupported value for TGRAN_2, giving up\n");
		वापस -EINVAL;
	पूर्ण

	kvm_ipa_limit = id_aa64mmfr0_parange_to_phys_shअगरt(parange);
	kvm_info("IPA Size Limit: %d bits%s\n", kvm_ipa_limit,
		 ((kvm_ipa_limit < KVM_PHYS_SHIFT) ?
		  " (Reduced IPA size, limited VM/VMM compatibility)" : ""));

	वापस 0;
पूर्ण

पूर्णांक kvm_arm_setup_stage2(काष्ठा kvm *kvm, अचिन्हित दीर्घ type)
अणु
	u64 mmfr0, mmfr1;
	u32 phys_shअगरt;

	अगर (type & ~KVM_VM_TYPE_ARM_IPA_SIZE_MASK)
		वापस -EINVAL;

	phys_shअगरt = KVM_VM_TYPE_ARM_IPA_SIZE(type);
	अगर (phys_shअगरt) अणु
		अगर (phys_shअगरt > kvm_ipa_limit ||
		    phys_shअगरt < 32)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		phys_shअगरt = KVM_PHYS_SHIFT;
		अगर (phys_shअगरt > kvm_ipa_limit) अणु
			pr_warn_once("%s using unsupported default IPA limit, upgrade your VMM\n",
				     current->comm);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	mmfr0 = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	mmfr1 = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR1_EL1);
	kvm->arch.vtcr = kvm_get_vtcr(mmfr0, mmfr1, phys_shअगरt);

	वापस 0;
पूर्ण
