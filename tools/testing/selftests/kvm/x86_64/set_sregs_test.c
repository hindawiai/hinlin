<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KVM_SET_SREGS tests
 *
 * Copyright (C) 2018, Google LLC.
 *
 * This is a regression test क्रम the bug fixed by the following commit:
 * d3802286fa0f ("kvm: x86: Disallow illegal IA32_APIC_BASE MSR values")
 *
 * That bug allowed a user-mode program that called the KVM_SET_SREGS
 * ioctl to put a VCPU's local APIC पूर्णांकo an invalid state.
 */
#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"

#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा VCPU_ID                  5

अटल व्योम test_cr4_feature_bit(काष्ठा kvm_vm *vm, काष्ठा kvm_sregs *orig,
				 uपूर्णांक64_t feature_bit)
अणु
	काष्ठा kvm_sregs sregs;
	पूर्णांक rc;

	/* Skip the sub-test, the feature is supported. */
	अगर (orig->cr4 & feature_bit)
		वापस;

	स_नकल(&sregs, orig, माप(sregs));
	sregs.cr4 |= feature_bit;

	rc = _vcpu_sregs_set(vm, VCPU_ID, &sregs);
	TEST_ASSERT(rc, "KVM allowed unsupported CR4 bit (0x%lx)", feature_bit);

	/* Sanity check that KVM didn't change anything. */
	vcpu_sregs_get(vm, VCPU_ID, &sregs);
	TEST_ASSERT(!स_भेद(&sregs, orig, माप(sregs)), "KVM modified sregs");
पूर्ण

अटल uपूर्णांक64_t calc_cr4_feature_bits(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_cpuid_entry2 *cpuid_1, *cpuid_7;
	uपूर्णांक64_t cr4;

	cpuid_1 = kvm_get_supported_cpuid_entry(1);
	cpuid_7 = kvm_get_supported_cpuid_entry(7);

	cr4 = X86_CR4_VME | X86_CR4_PVI | X86_CR4_TSD | X86_CR4_DE |
	      X86_CR4_PSE | X86_CR4_PAE | X86_CR4_MCE | X86_CR4_PGE |
	      X86_CR4_PCE | X86_CR4_OSFXSR | X86_CR4_OSXMMEXCPT;
	अगर (cpuid_7->ecx & CPUID_UMIP)
		cr4 |= X86_CR4_UMIP;
	अगर (cpuid_7->ecx & CPUID_LA57)
		cr4 |= X86_CR4_LA57;
	अगर (cpuid_1->ecx & CPUID_VMX)
		cr4 |= X86_CR4_VMXE;
	अगर (cpuid_1->ecx & CPUID_SMX)
		cr4 |= X86_CR4_SMXE;
	अगर (cpuid_7->ebx & CPUID_FSGSBASE)
		cr4 |= X86_CR4_FSGSBASE;
	अगर (cpuid_1->ecx & CPUID_PCID)
		cr4 |= X86_CR4_PCIDE;
	अगर (cpuid_1->ecx & CPUID_XSAVE)
		cr4 |= X86_CR4_OSXSAVE;
	अगर (cpuid_7->ebx & CPUID_SMEP)
		cr4 |= X86_CR4_SMEP;
	अगर (cpuid_7->ebx & CPUID_SMAP)
		cr4 |= X86_CR4_SMAP;
	अगर (cpuid_7->ecx & CPUID_PKU)
		cr4 |= X86_CR4_PKE;

	वापस cr4;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_sregs sregs;
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t cr4;
	पूर्णांक rc;

	/* Tell मानक_निकास not to buffer its content */
	रखो_बफ(मानक_निकास, शून्य);

	/*
	 * Create a dummy VM, specअगरically to aव्योम करोing KVM_SET_CPUID2, and
	 * use it to verअगरy all supported CR4 bits can be set prior to defining
	 * the vCPU model, i.e. without करोing KVM_SET_CPUID2.
	 */
	vm = vm_create(VM_MODE_DEFAULT, DEFAULT_GUEST_PHY_PAGES, O_RDWR);
	vm_vcpu_add(vm, VCPU_ID);

	vcpu_sregs_get(vm, VCPU_ID, &sregs);

	sregs.cr4 |= calc_cr4_feature_bits(vm);
	cr4 = sregs.cr4;

	rc = _vcpu_sregs_set(vm, VCPU_ID, &sregs);
	TEST_ASSERT(!rc, "Failed to set supported CR4 bits (0x%lx)", cr4);

	vcpu_sregs_get(vm, VCPU_ID, &sregs);
	TEST_ASSERT(sregs.cr4 == cr4, "sregs.CR4 (0x%llx) != CR4 (0x%lx)",
		    sregs.cr4, cr4);

	/* Verअगरy all unsupported features are rejected by KVM. */
	test_cr4_feature_bit(vm, &sregs, X86_CR4_UMIP);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_LA57);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_VMXE);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_SMXE);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_FSGSBASE);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_PCIDE);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_OSXSAVE);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_SMEP);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_SMAP);
	test_cr4_feature_bit(vm, &sregs, X86_CR4_PKE);
	kvm_vm_मुक्त(vm);

	/* Create a "real" VM and verअगरy APIC_BASE can be set. */
	vm = vm_create_शेष(VCPU_ID, 0, शून्य);

	vcpu_sregs_get(vm, VCPU_ID, &sregs);
	sregs.apic_base = 1 << 10;
	rc = _vcpu_sregs_set(vm, VCPU_ID, &sregs);
	TEST_ASSERT(rc, "Set IA32_APIC_BASE to %llx (invalid)",
		    sregs.apic_base);
	sregs.apic_base = 1 << 11;
	rc = _vcpu_sregs_set(vm, VCPU_ID, &sregs);
	TEST_ASSERT(!rc, "Couldn't set IA32_APIC_BASE to %llx (valid)",
		    sregs.apic_base);

	kvm_vm_मुक्त(vm);

	वापस 0;
पूर्ण
