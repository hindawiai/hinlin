<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kvm_create_max_vcpus
 *
 * Copyright (C) 2019, Google LLC.
 *
 * Test क्रम KVM_CAP_MAX_VCPUS and KVM_CAP_MAX_VCPU_ID.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "test_util.h"

#समावेश "kvm_util.h"
#समावेश "asm/kvm.h"
#समावेश "linux/kvm.h"

व्योम test_vcpu_creation(पूर्णांक first_vcpu_id, पूर्णांक num_vcpus)
अणु
	काष्ठा kvm_vm *vm;
	पूर्णांक i;

	pr_info("Testing creating %d vCPUs, with IDs %d...%d.\n",
		num_vcpus, first_vcpu_id, first_vcpu_id + num_vcpus - 1);

	vm = vm_create(VM_MODE_DEFAULT, DEFAULT_GUEST_PHY_PAGES, O_RDWR);

	क्रम (i = first_vcpu_id; i < first_vcpu_id + num_vcpus; i++)
		/* This निश्चितs that the vCPU was created. */
		vm_vcpu_add(vm, i);

	kvm_vm_मुक्त(vm);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक kvm_max_vcpu_id = kvm_check_cap(KVM_CAP_MAX_VCPU_ID);
	पूर्णांक kvm_max_vcpus = kvm_check_cap(KVM_CAP_MAX_VCPUS);

	pr_info("KVM_CAP_MAX_VCPU_ID: %d\n", kvm_max_vcpu_id);
	pr_info("KVM_CAP_MAX_VCPUS: %d\n", kvm_max_vcpus);

	/*
	 * Upstream KVM prior to 4.8 करोes not support KVM_CAP_MAX_VCPU_ID.
	 * Userspace is supposed to use KVM_CAP_MAX_VCPUS as the maximum ID
	 * in this हाल.
	 */
	अगर (!kvm_max_vcpu_id)
		kvm_max_vcpu_id = kvm_max_vcpus;

	TEST_ASSERT(kvm_max_vcpu_id >= kvm_max_vcpus,
		    "KVM_MAX_VCPU_ID (%d) must be at least as large as KVM_MAX_VCPUS (%d).",
		    kvm_max_vcpu_id, kvm_max_vcpus);

	test_vcpu_creation(0, kvm_max_vcpus);

	अगर (kvm_max_vcpu_id > kvm_max_vcpus)
		test_vcpu_creation(
			kvm_max_vcpu_id - kvm_max_vcpus, kvm_max_vcpus);

	वापस 0;
पूर्ण
