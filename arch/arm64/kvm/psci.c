<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/preempt.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/kvm_emulate.h>

#समावेश <kvm/arm_psci.h>
#समावेश <kvm/arm_hypercalls.h>

/*
 * This is an implementation of the Power State Coordination Interface
 * as described in ARM करोcument number ARM DEN 0022A.
 */

#घोषणा AFFINITY_MASK(level)	~((0x1UL << ((level) * MPIDR_LEVEL_BITS)) - 1)

अटल अचिन्हित दीर्घ psci_affinity_mask(अचिन्हित दीर्घ affinity_level)
अणु
	अगर (affinity_level <= 3)
		वापस MPIDR_HWID_BITMASK & AFFINITY_MASK(affinity_level);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ kvm_psci_vcpu_suspend(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * NOTE: For simplicity, we make VCPU suspend emulation to be
	 * same-as WFI (Wait-क्रम-पूर्णांकerrupt) emulation.
	 *
	 * This means क्रम KVM the wakeup events are पूर्णांकerrupts and
	 * this is consistent with पूर्णांकended use of StateID as described
	 * in section 5.4.1 of PSCI v0.2 specअगरication (ARM DEN 0022A).
	 *
	 * Further, we also treat घातer-करोwn request to be same as
	 * stand-by request as-per section 5.4.2 clause 3 of PSCI v0.2
	 * specअगरication (ARM DEN 0022A). This means all suspend states
	 * क्रम KVM will preserve the रेजिस्टर state.
	 */
	kvm_vcpu_block(vcpu);
	kvm_clear_request(KVM_REQ_UNHALT, vcpu);

	वापस PSCI_RET_SUCCESS;
पूर्ण

अटल व्योम kvm_psci_vcpu_off(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.घातer_off = true;
	kvm_make_request(KVM_REQ_SLEEP, vcpu);
	kvm_vcpu_kick(vcpu);
पूर्ण

अटल अचिन्हित दीर्घ kvm_psci_vcpu_on(काष्ठा kvm_vcpu *source_vcpu)
अणु
	काष्ठा vcpu_reset_state *reset_state;
	काष्ठा kvm *kvm = source_vcpu->kvm;
	काष्ठा kvm_vcpu *vcpu = शून्य;
	अचिन्हित दीर्घ cpu_id;

	cpu_id = smccc_get_arg1(source_vcpu) & MPIDR_HWID_BITMASK;
	अगर (vcpu_mode_is_32bit(source_vcpu))
		cpu_id &= ~((u32) 0);

	vcpu = kvm_mpidr_to_vcpu(kvm, cpu_id);

	/*
	 * Make sure the caller requested a valid CPU and that the CPU is
	 * turned off.
	 */
	अगर (!vcpu)
		वापस PSCI_RET_INVALID_PARAMS;
	अगर (!vcpu->arch.घातer_off) अणु
		अगर (kvm_psci_version(source_vcpu, kvm) != KVM_ARM_PSCI_0_1)
			वापस PSCI_RET_ALREADY_ON;
		अन्यथा
			वापस PSCI_RET_INVALID_PARAMS;
	पूर्ण

	reset_state = &vcpu->arch.reset_state;

	reset_state->pc = smccc_get_arg2(source_vcpu);

	/* Propagate caller endianness */
	reset_state->be = kvm_vcpu_is_be(source_vcpu);

	/*
	 * NOTE: We always update r0 (or x0) because क्रम PSCI v0.1
	 * the general purpose रेजिस्टरs are undefined upon CPU_ON.
	 */
	reset_state->r0 = smccc_get_arg3(source_vcpu);

	WRITE_ONCE(reset_state->reset, true);
	kvm_make_request(KVM_REQ_VCPU_RESET, vcpu);

	/*
	 * Make sure the reset request is observed अगर the change to
	 * घातer_state is observed.
	 */
	smp_wmb();

	vcpu->arch.घातer_off = false;
	kvm_vcpu_wake_up(vcpu);

	वापस PSCI_RET_SUCCESS;
पूर्ण

अटल अचिन्हित दीर्घ kvm_psci_vcpu_affinity_info(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i, matching_cpus = 0;
	अचिन्हित दीर्घ mpidr;
	अचिन्हित दीर्घ target_affinity;
	अचिन्हित दीर्घ target_affinity_mask;
	अचिन्हित दीर्घ lowest_affinity_level;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_vcpu *पंचांगp;

	target_affinity = smccc_get_arg1(vcpu);
	lowest_affinity_level = smccc_get_arg2(vcpu);

	/* Determine target affinity mask */
	target_affinity_mask = psci_affinity_mask(lowest_affinity_level);
	अगर (!target_affinity_mask)
		वापस PSCI_RET_INVALID_PARAMS;

	/* Ignore other bits of target affinity */
	target_affinity &= target_affinity_mask;

	/*
	 * If one or more VCPU matching target affinity are running
	 * then ON अन्यथा OFF
	 */
	kvm_क्रम_each_vcpu(i, पंचांगp, kvm) अणु
		mpidr = kvm_vcpu_get_mpidr_aff(पंचांगp);
		अगर ((mpidr & target_affinity_mask) == target_affinity) अणु
			matching_cpus++;
			अगर (!पंचांगp->arch.घातer_off)
				वापस PSCI_0_2_AFFINITY_LEVEL_ON;
		पूर्ण
	पूर्ण

	अगर (!matching_cpus)
		वापस PSCI_RET_INVALID_PARAMS;

	वापस PSCI_0_2_AFFINITY_LEVEL_OFF;
पूर्ण

अटल व्योम kvm_prepare_प्रणाली_event(काष्ठा kvm_vcpu *vcpu, u32 type)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *पंचांगp;

	/*
	 * The KVM ABI specअगरies that a प्रणाली event निकास may call KVM_RUN
	 * again and may perक्रमm shutकरोwn/reboot at a later समय that when the
	 * actual request is made.  Since we are implementing PSCI and a
	 * caller of PSCI reboot and shutकरोwn expects that the प्रणाली shuts
	 * करोwn or reboots immediately, let's make sure that VCPUs are not run
	 * after this call is handled and beक्रमe the VCPUs have been
	 * re-initialized.
	 */
	kvm_क्रम_each_vcpu(i, पंचांगp, vcpu->kvm)
		पंचांगp->arch.घातer_off = true;
	kvm_make_all_cpus_request(vcpu->kvm, KVM_REQ_SLEEP);

	स_रखो(&vcpu->run->प्रणाली_event, 0, माप(vcpu->run->प्रणाली_event));
	vcpu->run->प्रणाली_event.type = type;
	vcpu->run->निकास_reason = KVM_EXIT_SYSTEM_EVENT;
पूर्ण

अटल व्योम kvm_psci_प्रणाली_off(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_prepare_प्रणाली_event(vcpu, KVM_SYSTEM_EVENT_SHUTDOWN);
पूर्ण

अटल व्योम kvm_psci_प्रणाली_reset(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_prepare_प्रणाली_event(vcpu, KVM_SYSTEM_EVENT_RESET);
पूर्ण

अटल व्योम kvm_psci_narrow_to_32bit(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;

	/*
	 * Zero the input रेजिस्टरs' upper 32 bits. They will be fully
	 * zeroed on निकास, so we're fine changing them in place.
	 */
	क्रम (i = 1; i < 4; i++)
		vcpu_set_reg(vcpu, i, lower_32_bits(vcpu_get_reg(vcpu, i)));
पूर्ण

अटल अचिन्हित दीर्घ kvm_psci_check_allowed_function(काष्ठा kvm_vcpu *vcpu, u32 fn)
अणु
	चयन(fn) अणु
	हाल PSCI_0_2_FN64_CPU_SUSPEND:
	हाल PSCI_0_2_FN64_CPU_ON:
	हाल PSCI_0_2_FN64_AFFINITY_INFO:
		/* Disallow these functions क्रम 32bit guests */
		अगर (vcpu_mode_is_32bit(vcpu))
			वापस PSCI_RET_NOT_SUPPORTED;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_psci_0_2_call(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	u32 psci_fn = smccc_get_function(vcpu);
	अचिन्हित दीर्घ val;
	पूर्णांक ret = 1;

	val = kvm_psci_check_allowed_function(vcpu, psci_fn);
	अगर (val)
		जाओ out;

	चयन (psci_fn) अणु
	हाल PSCI_0_2_FN_PSCI_VERSION:
		/*
		 * Bits[31:16] = Major Version = 0
		 * Bits[15:0] = Minor Version = 2
		 */
		val = KVM_ARM_PSCI_0_2;
		अवरोध;
	हाल PSCI_0_2_FN_CPU_SUSPEND:
	हाल PSCI_0_2_FN64_CPU_SUSPEND:
		val = kvm_psci_vcpu_suspend(vcpu);
		अवरोध;
	हाल PSCI_0_2_FN_CPU_OFF:
		kvm_psci_vcpu_off(vcpu);
		val = PSCI_RET_SUCCESS;
		अवरोध;
	हाल PSCI_0_2_FN_CPU_ON:
		kvm_psci_narrow_to_32bit(vcpu);
		fallthrough;
	हाल PSCI_0_2_FN64_CPU_ON:
		mutex_lock(&kvm->lock);
		val = kvm_psci_vcpu_on(vcpu);
		mutex_unlock(&kvm->lock);
		अवरोध;
	हाल PSCI_0_2_FN_AFFINITY_INFO:
		kvm_psci_narrow_to_32bit(vcpu);
		fallthrough;
	हाल PSCI_0_2_FN64_AFFINITY_INFO:
		val = kvm_psci_vcpu_affinity_info(vcpu);
		अवरोध;
	हाल PSCI_0_2_FN_MIGRATE_INFO_TYPE:
		/*
		 * Trusted OS is MP hence करोes not require migration
	         * or
		 * Trusted OS is not present
		 */
		val = PSCI_0_2_TOS_MP;
		अवरोध;
	हाल PSCI_0_2_FN_SYSTEM_OFF:
		kvm_psci_प्रणाली_off(vcpu);
		/*
		 * We shouldn't be going back to guest VCPU after
		 * receiving SYSTEM_OFF request.
		 *
		 * If user space accidentally/deliberately resumes
		 * guest VCPU after SYSTEM_OFF request then guest
		 * VCPU should see पूर्णांकernal failure from PSCI वापस
		 * value. To achieve this, we preload r0 (or x0) with
		 * PSCI वापस value INTERNAL_FAILURE.
		 */
		val = PSCI_RET_INTERNAL_FAILURE;
		ret = 0;
		अवरोध;
	हाल PSCI_0_2_FN_SYSTEM_RESET:
		kvm_psci_प्रणाली_reset(vcpu);
		/*
		 * Same reason as SYSTEM_OFF क्रम preloading r0 (or x0)
		 * with PSCI वापस value INTERNAL_FAILURE.
		 */
		val = PSCI_RET_INTERNAL_FAILURE;
		ret = 0;
		अवरोध;
	शेष:
		val = PSCI_RET_NOT_SUPPORTED;
		अवरोध;
	पूर्ण

out:
	smccc_set_retval(vcpu, val, 0, 0, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_psci_1_0_call(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 psci_fn = smccc_get_function(vcpu);
	u32 feature;
	अचिन्हित दीर्घ val;
	पूर्णांक ret = 1;

	चयन(psci_fn) अणु
	हाल PSCI_0_2_FN_PSCI_VERSION:
		val = KVM_ARM_PSCI_1_0;
		अवरोध;
	हाल PSCI_1_0_FN_PSCI_FEATURES:
		feature = smccc_get_arg1(vcpu);
		val = kvm_psci_check_allowed_function(vcpu, feature);
		अगर (val)
			अवरोध;

		चयन(feature) अणु
		हाल PSCI_0_2_FN_PSCI_VERSION:
		हाल PSCI_0_2_FN_CPU_SUSPEND:
		हाल PSCI_0_2_FN64_CPU_SUSPEND:
		हाल PSCI_0_2_FN_CPU_OFF:
		हाल PSCI_0_2_FN_CPU_ON:
		हाल PSCI_0_2_FN64_CPU_ON:
		हाल PSCI_0_2_FN_AFFINITY_INFO:
		हाल PSCI_0_2_FN64_AFFINITY_INFO:
		हाल PSCI_0_2_FN_MIGRATE_INFO_TYPE:
		हाल PSCI_0_2_FN_SYSTEM_OFF:
		हाल PSCI_0_2_FN_SYSTEM_RESET:
		हाल PSCI_1_0_FN_PSCI_FEATURES:
		हाल ARM_SMCCC_VERSION_FUNC_ID:
			val = 0;
			अवरोध;
		शेष:
			val = PSCI_RET_NOT_SUPPORTED;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस kvm_psci_0_2_call(vcpu);
	पूर्ण

	smccc_set_retval(vcpu, val, 0, 0, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक kvm_psci_0_1_call(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	u32 psci_fn = smccc_get_function(vcpu);
	अचिन्हित दीर्घ val;

	चयन (psci_fn) अणु
	हाल KVM_PSCI_FN_CPU_OFF:
		kvm_psci_vcpu_off(vcpu);
		val = PSCI_RET_SUCCESS;
		अवरोध;
	हाल KVM_PSCI_FN_CPU_ON:
		mutex_lock(&kvm->lock);
		val = kvm_psci_vcpu_on(vcpu);
		mutex_unlock(&kvm->lock);
		अवरोध;
	शेष:
		val = PSCI_RET_NOT_SUPPORTED;
		अवरोध;
	पूर्ण

	smccc_set_retval(vcpu, val, 0, 0, 0);
	वापस 1;
पूर्ण

/**
 * kvm_psci_call - handle PSCI call अगर r0 value is in range
 * @vcpu: Poपूर्णांकer to the VCPU काष्ठा
 *
 * Handle PSCI calls from guests through traps from HVC inकाष्ठाions.
 * The calling convention is similar to SMC calls to the secure world
 * where the function number is placed in r0.
 *
 * This function वापसs: > 0 (success), 0 (success but निकास to user
 * space), and < 0 (errors)
 *
 * Errors:
 * -EINVAL: Unrecognized PSCI function
 */
पूर्णांक kvm_psci_call(काष्ठा kvm_vcpu *vcpu)
अणु
	चयन (kvm_psci_version(vcpu, vcpu->kvm)) अणु
	हाल KVM_ARM_PSCI_1_0:
		वापस kvm_psci_1_0_call(vcpu);
	हाल KVM_ARM_PSCI_0_2:
		वापस kvm_psci_0_2_call(vcpu);
	हाल KVM_ARM_PSCI_0_1:
		वापस kvm_psci_0_1_call(vcpu);
	शेष:
		वापस -EINVAL;
	पूर्ण;
पूर्ण

पूर्णांक kvm_arm_get_fw_num_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 3;		/* PSCI version and two workaround रेजिस्टरs */
पूर्ण

पूर्णांक kvm_arm_copy_fw_reg_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *uindices)
अणु
	अगर (put_user(KVM_REG_ARM_PSCI_VERSION, uindices++))
		वापस -EFAULT;

	अगर (put_user(KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1, uindices++))
		वापस -EFAULT;

	अगर (put_user(KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2, uindices++))
		वापस -EFAULT;

	वापस 0;
पूर्ण

#घोषणा KVM_REG_FEATURE_LEVEL_WIDTH	4
#घोषणा KVM_REG_FEATURE_LEVEL_MASK	(BIT(KVM_REG_FEATURE_LEVEL_WIDTH) - 1)

/*
 * Convert the workaround level पूर्णांकo an easy-to-compare number, where higher
 * values mean better protection.
 */
अटल पूर्णांक get_kernel_wa_level(u64 regid)
अणु
	चयन (regid) अणु
	हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1:
		चयन (arm64_get_spectre_v2_state()) अणु
		हाल SPECTRE_VULNERABLE:
			वापस KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_AVAIL;
		हाल SPECTRE_MITIGATED:
			वापस KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_AVAIL;
		हाल SPECTRE_UNAFFECTED:
			वापस KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_REQUIRED;
		पूर्ण
		वापस KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_NOT_AVAIL;
	हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2:
		चयन (arm64_get_spectre_v4_state()) अणु
		हाल SPECTRE_MITIGATED:
			/*
			 * As क्रम the hypercall discovery, we pretend we
			 * करोn't have any FW mitigation अगर SSBS is there at
			 * all बार.
			 */
			अगर (cpus_have_final_cap(ARM64_SSBS))
				वापस KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_AVAIL;
			fallthrough;
		हाल SPECTRE_UNAFFECTED:
			वापस KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_REQUIRED;
		हाल SPECTRE_VULNERABLE:
			वापस KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_AVAIL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_arm_get_fw_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	व्योम __user *uaddr = (व्योम __user *)(दीर्घ)reg->addr;
	u64 val;

	चयन (reg->id) अणु
	हाल KVM_REG_ARM_PSCI_VERSION:
		val = kvm_psci_version(vcpu, vcpu->kvm);
		अवरोध;
	हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1:
	हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2:
		val = get_kernel_wa_level(reg->id) & KVM_REG_FEATURE_LEVEL_MASK;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (copy_to_user(uaddr, &val, KVM_REG_SIZE(reg->id)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

पूर्णांक kvm_arm_set_fw_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg)
अणु
	व्योम __user *uaddr = (व्योम __user *)(दीर्घ)reg->addr;
	u64 val;
	पूर्णांक wa_level;

	अगर (copy_from_user(&val, uaddr, KVM_REG_SIZE(reg->id)))
		वापस -EFAULT;

	चयन (reg->id) अणु
	हाल KVM_REG_ARM_PSCI_VERSION:
	अणु
		bool wants_02;

		wants_02 = test_bit(KVM_ARM_VCPU_PSCI_0_2, vcpu->arch.features);

		चयन (val) अणु
		हाल KVM_ARM_PSCI_0_1:
			अगर (wants_02)
				वापस -EINVAL;
			vcpu->kvm->arch.psci_version = val;
			वापस 0;
		हाल KVM_ARM_PSCI_0_2:
		हाल KVM_ARM_PSCI_1_0:
			अगर (!wants_02)
				वापस -EINVAL;
			vcpu->kvm->arch.psci_version = val;
			वापस 0;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1:
		अगर (val & ~KVM_REG_FEATURE_LEVEL_MASK)
			वापस -EINVAL;

		अगर (get_kernel_wa_level(reg->id) < val)
			वापस -EINVAL;

		वापस 0;

	हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2:
		अगर (val & ~(KVM_REG_FEATURE_LEVEL_MASK |
			    KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_ENABLED))
			वापस -EINVAL;

		/* The enabled bit must not be set unless the level is AVAIL. */
		अगर ((val & KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_ENABLED) &&
		    (val & KVM_REG_FEATURE_LEVEL_MASK) != KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_AVAIL)
			वापस -EINVAL;

		/*
		 * Map all the possible incoming states to the only two we
		 * really want to deal with.
		 */
		चयन (val & KVM_REG_FEATURE_LEVEL_MASK) अणु
		हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_AVAIL:
		हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_UNKNOWN:
			wa_level = KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_AVAIL;
			अवरोध;
		हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_AVAIL:
		हाल KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_REQUIRED:
			wa_level = KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_2_NOT_REQUIRED;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/*
		 * We can deal with NOT_AVAIL on NOT_REQUIRED, but not the
		 * other way around.
		 */
		अगर (get_kernel_wa_level(reg->id) < wa_level)
			वापस -EINVAL;

		वापस 0;
	शेष:
		वापस -ENOENT;
	पूर्ण

	वापस -EINVAL;
पूर्ण
