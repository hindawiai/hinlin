<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __KVM_ARM_PSCI_H__
#घोषणा __KVM_ARM_PSCI_H__

#समावेश <linux/kvm_host.h>
#समावेश <uapi/linux/psci.h>

#घोषणा KVM_ARM_PSCI_0_1	PSCI_VERSION(0, 1)
#घोषणा KVM_ARM_PSCI_0_2	PSCI_VERSION(0, 2)
#घोषणा KVM_ARM_PSCI_1_0	PSCI_VERSION(1, 0)

#घोषणा KVM_ARM_PSCI_LATEST	KVM_ARM_PSCI_1_0

/*
 * We need the KVM poपूर्णांकer independently from the vcpu as we can call
 * this from HYP, and need to apply kern_hyp_va on it...
 */
अटल अंतरभूत पूर्णांक kvm_psci_version(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm *kvm)
अणु
	/*
	 * Our PSCI implementation stays the same across versions from
	 * v0.2 onward, only adding the few mandatory functions (such
	 * as FEATURES with 1.0) that are required by newer
	 * revisions. It is thus safe to वापस the latest, unless
	 * userspace has inकाष्ठाed us otherwise.
	 */
	अगर (test_bit(KVM_ARM_VCPU_PSCI_0_2, vcpu->arch.features)) अणु
		अगर (vcpu->kvm->arch.psci_version)
			वापस vcpu->kvm->arch.psci_version;

		वापस KVM_ARM_PSCI_LATEST;
	पूर्ण

	वापस KVM_ARM_PSCI_0_1;
पूर्ण


पूर्णांक kvm_psci_call(काष्ठा kvm_vcpu *vcpu);

काष्ठा kvm_one_reg;

पूर्णांक kvm_arm_get_fw_num_regs(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_arm_copy_fw_reg_indices(काष्ठा kvm_vcpu *vcpu, u64 __user *uindices);
पूर्णांक kvm_arm_get_fw_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg);
पूर्णांक kvm_arm_set_fw_reg(काष्ठा kvm_vcpu *vcpu, स्थिर काष्ठा kvm_one_reg *reg);

#पूर्ण_अगर /* __KVM_ARM_PSCI_H__ */
