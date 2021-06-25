<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2019 Arm Ltd.

#समावेश <linux/arm-smccc.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/sched/स्थिति.स>

#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/pvघड़ी-abi.h>

#समावेश <kvm/arm_hypercalls.h>

व्योम kvm_update_stolen_समय(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	u64 base = vcpu->arch.steal.base;
	u64 last_steal = vcpu->arch.steal.last_steal;
	u64 offset = दुरत्व(काष्ठा pvघड़ी_vcpu_stolen_समय, stolen_समय);
	u64 steal = 0;
	पूर्णांक idx;

	अगर (base == GPA_INVALID)
		वापस;

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	अगर (!kvm_get_guest(kvm, base + offset, steal)) अणु
		steal = le64_to_cpu(steal);
		vcpu->arch.steal.last_steal = READ_ONCE(current->sched_info.run_delay);
		steal += vcpu->arch.steal.last_steal - last_steal;
		kvm_put_guest(kvm, base + offset, cpu_to_le64(steal));
	पूर्ण
	srcu_पढ़ो_unlock(&kvm->srcu, idx);
पूर्ण

दीर्घ kvm_hypercall_pv_features(काष्ठा kvm_vcpu *vcpu)
अणु
	u32 feature = smccc_get_arg1(vcpu);
	दीर्घ val = SMCCC_RET_NOT_SUPPORTED;

	चयन (feature) अणु
	हाल ARM_SMCCC_HV_PV_TIME_FEATURES:
	हाल ARM_SMCCC_HV_PV_TIME_ST:
		अगर (vcpu->arch.steal.base != GPA_INVALID)
			val = SMCCC_RET_SUCCESS;
		अवरोध;
	पूर्ण

	वापस val;
पूर्ण

gpa_t kvm_init_stolen_समय(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा pvघड़ी_vcpu_stolen_समय init_values = अणुपूर्ण;
	काष्ठा kvm *kvm = vcpu->kvm;
	u64 base = vcpu->arch.steal.base;

	अगर (base == GPA_INVALID)
		वापस base;

	/*
	 * Start counting stolen समय from the समय the guest requests
	 * the feature enabled.
	 */
	vcpu->arch.steal.last_steal = current->sched_info.run_delay;
	kvm_ग_लिखो_guest_lock(kvm, base, &init_values, माप(init_values));

	वापस base;
पूर्ण

bool kvm_arm_pvसमय_supported(व्योम)
अणु
	वापस !!sched_info_on();
पूर्ण

पूर्णांक kvm_arm_pvसमय_set_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr)
अणु
	u64 __user *user = (u64 __user *)attr->addr;
	काष्ठा kvm *kvm = vcpu->kvm;
	u64 ipa;
	पूर्णांक ret = 0;
	पूर्णांक idx;

	अगर (!kvm_arm_pvसमय_supported() ||
	    attr->attr != KVM_ARM_VCPU_PVTIME_IPA)
		वापस -ENXIO;

	अगर (get_user(ipa, user))
		वापस -EFAULT;
	अगर (!IS_ALIGNED(ipa, 64))
		वापस -EINVAL;
	अगर (vcpu->arch.steal.base != GPA_INVALID)
		वापस -EEXIST;

	/* Check the address is in a valid memslot */
	idx = srcu_पढ़ो_lock(&kvm->srcu);
	अगर (kvm_is_error_hva(gfn_to_hva(kvm, ipa >> PAGE_SHIFT)))
		ret = -EINVAL;
	srcu_पढ़ो_unlock(&kvm->srcu, idx);

	अगर (!ret)
		vcpu->arch.steal.base = ipa;

	वापस ret;
पूर्ण

पूर्णांक kvm_arm_pvसमय_get_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr)
अणु
	u64 __user *user = (u64 __user *)attr->addr;
	u64 ipa;

	अगर (!kvm_arm_pvसमय_supported() ||
	    attr->attr != KVM_ARM_VCPU_PVTIME_IPA)
		वापस -ENXIO;

	ipa = vcpu->arch.steal.base;

	अगर (put_user(ipa, user))
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक kvm_arm_pvसमय_has_attr(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->attr) अणु
	हाल KVM_ARM_VCPU_PVTIME_IPA:
		अगर (kvm_arm_pvसमय_supported())
			वापस 0;
	पूर्ण
	वापस -ENXIO;
पूर्ण
