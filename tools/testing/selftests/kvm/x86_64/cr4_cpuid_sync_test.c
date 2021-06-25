<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CR4 and CPUID sync test
 *
 * Copyright 2018, Red Hat, Inc. and/or its affiliates.
 *
 * Author:
 *   Wei Huang <wei@redhat.com>
 */

#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"

#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा X86_FEATURE_XSAVE	(1<<26)
#घोषणा X86_FEATURE_OSXSAVE	(1<<27)
#घोषणा VCPU_ID			1

अटल अंतरभूत bool cr4_cpuid_is_sync(व्योम)
अणु
	पूर्णांक func, subfunc;
	uपूर्णांक32_t eax, ebx, ecx, edx;
	uपूर्णांक64_t cr4;

	func = 0x1;
	subfunc = 0x0;
	__यंत्र__ __अस्थिर__("cpuid"
			     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
			     : "a"(func), "c"(subfunc));

	cr4 = get_cr4();

	वापस (!!(ecx & X86_FEATURE_OSXSAVE)) == (!!(cr4 & X86_CR4_OSXSAVE));
पूर्ण

अटल व्योम guest_code(व्योम)
अणु
	uपूर्णांक64_t cr4;

	/* turn on CR4.OSXSAVE */
	cr4 = get_cr4();
	cr4 |= X86_CR4_OSXSAVE;
	set_cr4(cr4);

	/* verअगरy CR4.OSXSAVE == CPUID.OSXSAVE */
	GUEST_ASSERT(cr4_cpuid_is_sync());

	/* notअगरy hypervisor to change CR4 */
	GUEST_SYNC(0);

	/* check again */
	GUEST_ASSERT(cr4_cpuid_is_sync());

	GUEST_DONE();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_run *run;
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_sregs sregs;
	काष्ठा kvm_cpuid_entry2 *entry;
	काष्ठा ucall uc;
	पूर्णांक rc;

	entry = kvm_get_supported_cpuid_entry(1);
	अगर (!(entry->ecx & X86_FEATURE_XSAVE)) अणु
		prपूर्णांक_skip("XSAVE feature not supported");
		वापस 0;
	पूर्ण

	/* Tell मानक_निकास not to buffer its content */
	रखो_बफ(मानक_निकास, शून्य);

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code);
	run = vcpu_state(vm, VCPU_ID);

	जबतक (1) अणु
		rc = _vcpu_run(vm, VCPU_ID);

		TEST_ASSERT(rc == 0, "vcpu_run failed: %d\n", rc);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Unexpected exit reason: %u (%s),\n",
			    run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_SYNC:
			/* emulate hypervisor clearing CR4.OSXSAVE */
			vcpu_sregs_get(vm, VCPU_ID, &sregs);
			sregs.cr4 &= ~X86_CR4_OSXSAVE;
			vcpu_sregs_set(vm, VCPU_ID, &sregs);
			अवरोध;
		हाल UCALL_ABORT:
			TEST_FAIL("Guest CR4 bit (OSXSAVE) unsynchronized with CPUID bit.");
			अवरोध;
		हाल UCALL_DONE:
			जाओ करोne;
		शेष:
			TEST_FAIL("Unknown ucall %lu", uc.cmd);
		पूर्ण
	पूर्ण

	kvm_vm_मुक्त(vm);

करोne:
	वापस 0;
पूर्ण
