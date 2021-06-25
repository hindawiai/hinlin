<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * AArch64 processor specअगरic defines
 *
 * Copyright (C) 2018, Red Hat, Inc.
 */
#अगर_अघोषित SELFTEST_KVM_PROCESSOR_H
#घोषणा SELFTEST_KVM_PROCESSOR_H

#समावेश "kvm_util.h"


#घोषणा ARM64_CORE_REG(x) (KVM_REG_ARM64 | KVM_REG_SIZE_U64 | \
			   KVM_REG_ARM_CORE | KVM_REG_ARM_CORE_REG(x))

#घोषणा CPACR_EL1	3, 0,  1, 0, 2
#घोषणा TCR_EL1		3, 0,  2, 0, 2
#घोषणा MAIR_EL1	3, 0, 10, 2, 0
#घोषणा TTBR0_EL1	3, 0,  2, 0, 0
#घोषणा SCTLR_EL1	3, 0,  1, 0, 0

/*
 * Default MAIR
 *                  index   attribute
 * DEVICE_nGnRnE      0     0000:0000
 * DEVICE_nGnRE       1     0000:0100
 * DEVICE_GRE         2     0000:1100
 * NORMAL_NC          3     0100:0100
 * NORMAL             4     1111:1111
 * NORMAL_WT          5     1011:1011
 */
#घोषणा DEFAULT_MAIR_EL1 ((0x00ul << (0 * 8)) | \
			  (0x04ul << (1 * 8)) | \
			  (0x0cul << (2 * 8)) | \
			  (0x44ul << (3 * 8)) | \
			  (0xfful << (4 * 8)) | \
			  (0xbbul << (5 * 8)))

अटल अंतरभूत व्योम get_reg(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक64_t id, uपूर्णांक64_t *addr)
अणु
	काष्ठा kvm_one_reg reg;
	reg.id = id;
	reg.addr = (uपूर्णांक64_t)addr;
	vcpu_ioctl(vm, vcpuid, KVM_GET_ONE_REG, &reg);
पूर्ण

अटल अंतरभूत व्योम set_reg(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, uपूर्णांक64_t id, uपूर्णांक64_t val)
अणु
	काष्ठा kvm_one_reg reg;
	reg.id = id;
	reg.addr = (uपूर्णांक64_t)&val;
	vcpu_ioctl(vm, vcpuid, KVM_SET_ONE_REG, &reg);
पूर्ण

व्योम aarch64_vcpu_setup(काष्ठा kvm_vm *vm, पूर्णांक vcpuid, काष्ठा kvm_vcpu_init *init);
व्योम aarch64_vcpu_add_शेष(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid,
			      काष्ठा kvm_vcpu_init *init, व्योम *guest_code);

#पूर्ण_अगर /* SELFTEST_KVM_PROCESSOR_H */
