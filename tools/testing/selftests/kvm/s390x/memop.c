<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Test क्रम s390x KVM_S390_MEM_OP
 *
 * Copyright (C) 2019, Red Hat, Inc.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"

#घोषणा VCPU_ID 1

अटल uपूर्णांक8_t mem1[65536];
अटल uपूर्णांक8_t mem2[65536];

अटल व्योम guest_code(व्योम)
अणु
	पूर्णांक i;

	क्रम (;;) अणु
		क्रम (i = 0; i < माप(mem2); i++)
			mem2[i] = mem1[i];
		GUEST_SYNC(0);
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	काष्ठा kvm_s390_mem_op ksmo;
	पूर्णांक rv, i, maxsize;

	रखो_बफ(मानक_निकास, शून्य);	/* Tell मानक_निकास not to buffer its content */

	maxsize = kvm_check_cap(KVM_CAP_S390_MEM_OP);
	अगर (!maxsize) अणु
		prपूर्णांक_skip("CAP_S390_MEM_OP not supported");
		निकास(KSFT_SKIP);
	पूर्ण
	अगर (maxsize > माप(mem1))
		maxsize = माप(mem1);

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code);
	run = vcpu_state(vm, VCPU_ID);

	क्रम (i = 0; i < माप(mem1); i++)
		mem1[i] = i * i + i;

	/* Set the first array */
	ksmo.gaddr = addr_gva2gpa(vm, (uपूर्णांकptr_t)mem1);
	ksmo.flags = 0;
	ksmo.size = maxsize;
	ksmo.op = KVM_S390_MEMOP_LOGICAL_WRITE;
	ksmo.buf = (uपूर्णांकptr_t)mem1;
	ksmo.ar = 0;
	vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);

	/* Let the guest code copy the first array to the second */
	vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_S390_SIEIC,
		    "Unexpected exit reason: %u (%s)\n",
		    run->निकास_reason,
		    निकास_reason_str(run->निकास_reason));

	स_रखो(mem2, 0xaa, माप(mem2));

	/* Get the second array */
	ksmo.gaddr = (uपूर्णांकptr_t)mem2;
	ksmo.flags = 0;
	ksmo.size = maxsize;
	ksmo.op = KVM_S390_MEMOP_LOGICAL_READ;
	ksmo.buf = (uपूर्णांकptr_t)mem2;
	ksmo.ar = 0;
	vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);

	TEST_ASSERT(!स_भेद(mem1, mem2, maxsize),
		    "Memory contents do not match!");

	/* Check error conditions - first bad size: */
	ksmo.gaddr = (uपूर्णांकptr_t)mem1;
	ksmo.flags = 0;
	ksmo.size = -1;
	ksmo.op = KVM_S390_MEMOP_LOGICAL_WRITE;
	ksmo.buf = (uपूर्णांकptr_t)mem1;
	ksmo.ar = 0;
	rv = _vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);
	TEST_ASSERT(rv == -1 && त्रुटि_सं == E2BIG, "ioctl allows insane sizes");

	/* Zero size: */
	ksmo.gaddr = (uपूर्णांकptr_t)mem1;
	ksmo.flags = 0;
	ksmo.size = 0;
	ksmo.op = KVM_S390_MEMOP_LOGICAL_WRITE;
	ksmo.buf = (uपूर्णांकptr_t)mem1;
	ksmo.ar = 0;
	rv = _vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);
	TEST_ASSERT(rv == -1 && (त्रुटि_सं == EINVAL || त्रुटि_सं == ENOMEM),
		    "ioctl allows 0 as size");

	/* Bad flags: */
	ksmo.gaddr = (uपूर्णांकptr_t)mem1;
	ksmo.flags = -1;
	ksmo.size = maxsize;
	ksmo.op = KVM_S390_MEMOP_LOGICAL_WRITE;
	ksmo.buf = (uपूर्णांकptr_t)mem1;
	ksmo.ar = 0;
	rv = _vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);
	TEST_ASSERT(rv == -1 && त्रुटि_सं == EINVAL, "ioctl allows all flags");

	/* Bad operation: */
	ksmo.gaddr = (uपूर्णांकptr_t)mem1;
	ksmo.flags = 0;
	ksmo.size = maxsize;
	ksmo.op = -1;
	ksmo.buf = (uपूर्णांकptr_t)mem1;
	ksmo.ar = 0;
	rv = _vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);
	TEST_ASSERT(rv == -1 && त्रुटि_सं == EINVAL, "ioctl allows bad operations");

	/* Bad guest address: */
	ksmo.gaddr = ~0xfffUL;
	ksmo.flags = KVM_S390_MEMOP_F_CHECK_ONLY;
	ksmo.size = maxsize;
	ksmo.op = KVM_S390_MEMOP_LOGICAL_WRITE;
	ksmo.buf = (uपूर्णांकptr_t)mem1;
	ksmo.ar = 0;
	rv = _vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);
	TEST_ASSERT(rv > 0, "ioctl does not report bad guest memory access");

	/* Bad host address: */
	ksmo.gaddr = (uपूर्णांकptr_t)mem1;
	ksmo.flags = 0;
	ksmo.size = maxsize;
	ksmo.op = KVM_S390_MEMOP_LOGICAL_WRITE;
	ksmo.buf = 0;
	ksmo.ar = 0;
	rv = _vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);
	TEST_ASSERT(rv == -1 && त्रुटि_सं == EFAULT,
		    "ioctl does not report bad host memory address");

	/* Bad access रेजिस्टर: */
	run->psw_mask &= ~(3UL << (63 - 17));
	run->psw_mask |= 1UL << (63 - 17);  /* Enable AR mode */
	vcpu_run(vm, VCPU_ID);              /* To sync new state to SIE block */
	ksmo.gaddr = (uपूर्णांकptr_t)mem1;
	ksmo.flags = 0;
	ksmo.size = maxsize;
	ksmo.op = KVM_S390_MEMOP_LOGICAL_WRITE;
	ksmo.buf = (uपूर्णांकptr_t)mem1;
	ksmo.ar = 17;
	rv = _vcpu_ioctl(vm, VCPU_ID, KVM_S390_MEM_OP, &ksmo);
	TEST_ASSERT(rv == -1 && त्रुटि_सं == EINVAL, "ioctl allows ARs > 15");
	run->psw_mask &= ~(3UL << (63 - 17));   /* Disable AR mode */
	vcpu_run(vm, VCPU_ID);                  /* Run to sync new state */

	kvm_vm_मुक्त(vm);

	वापस 0;
पूर्ण
