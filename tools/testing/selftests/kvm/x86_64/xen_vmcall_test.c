<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * xen_vmcall_test
 *
 * Copyright तऊ 2020 Amazon.com, Inc. or its affiliates.
 *
 * Userspace hypercall testing
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा VCPU_ID		5

#घोषणा HCALL_REGION_GPA	0xc0000000ULL
#घोषणा HCALL_REGION_SLOT	10
#घोषणा PAGE_SIZE		4096

अटल काष्ठा kvm_vm *vm;

#घोषणा INPUTVALUE 17
#घोषणा ARGVALUE(x) (0xdeadbeef5a5a0000UL + x)
#घोषणा RETVALUE 0xcafef00dfbfbffffUL

#घोषणा XEN_HYPERCALL_MSR	0x40000200
#घोषणा HV_GUEST_OS_ID_MSR	0x40000000
#घोषणा HV_HYPERCALL_MSR	0x40000001

#घोषणा HVCALL_SIGNAL_EVENT		0x005d
#घोषणा HV_STATUS_INVALID_ALIGNMENT	4

अटल व्योम guest_code(व्योम)
अणु
	अचिन्हित दीर्घ rax = INPUTVALUE;
	अचिन्हित दीर्घ rdi = ARGVALUE(1);
	अचिन्हित दीर्घ rsi = ARGVALUE(2);
	अचिन्हित दीर्घ rdx = ARGVALUE(3);
	अचिन्हित दीर्घ rcx;
	रेजिस्टर अचिन्हित दीर्घ r10 __यंत्र__("r10") = ARGVALUE(4);
	रेजिस्टर अचिन्हित दीर्घ r8 __यंत्र__("r8") = ARGVALUE(5);
	रेजिस्टर अचिन्हित दीर्घ r9 __यंत्र__("r9") = ARGVALUE(6);

	/* First a direct invocation of 'vmcall' */
	__यंत्र__ __अस्थिर__("vmcall" :
			     "=a"(rax) :
			     "a"(rax), "D"(rdi), "S"(rsi), "d"(rdx),
			     "r"(r10), "r"(r8), "r"(r9));
	GUEST_ASSERT(rax == RETVALUE);

	/* Fill in the Xen hypercall page */
	__यंत्र__ __अस्थिर__("wrmsr" : : "c" (XEN_HYPERCALL_MSR),
			     "a" (HCALL_REGION_GPA & 0xffffffff),
			     "d" (HCALL_REGION_GPA >> 32));

	/* Set Hyper-V Guest OS ID */
	__यंत्र__ __अस्थिर__("wrmsr" : : "c" (HV_GUEST_OS_ID_MSR),
			     "a" (0x5a), "d" (0));

	/* Hyper-V hypercall page */
	u64 msrval = HCALL_REGION_GPA + PAGE_SIZE + 1;
	__यंत्र__ __अस्थिर__("wrmsr" : : "c" (HV_HYPERCALL_MSR),
			     "a" (msrval & 0xffffffff),
			     "d" (msrval >> 32));

	/* Invoke a Xen hypercall */
	__यंत्र__ __अस्थिर__("call *%1" : "=a"(rax) :
			     "r"(HCALL_REGION_GPA + INPUTVALUE * 32),
			     "a"(rax), "D"(rdi), "S"(rsi), "d"(rdx),
			     "r"(r10), "r"(r8), "r"(r9));
	GUEST_ASSERT(rax == RETVALUE);

	/* Invoke a Hyper-V hypercall */
	rax = 0;
	rcx = HVCALL_SIGNAL_EVENT;	/* code */
	rdx = 0x5a5a5a5a;		/* ingpa (badly aligned) */
	__यंत्र__ __अस्थिर__("call *%1" : "=a"(rax) :
			     "r"(HCALL_REGION_GPA + PAGE_SIZE),
			     "a"(rax), "c"(rcx), "d"(rdx),
			     "r"(r8));
	GUEST_ASSERT(rax == HV_STATUS_INVALID_ALIGNMENT);

	GUEST_DONE();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (!(kvm_check_cap(KVM_CAP_XEN_HVM) &
	      KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL) ) अणु
		prपूर्णांक_skip("KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL not available");
		निकास(KSFT_SKIP);
	पूर्ण

	vm = vm_create_शेष(VCPU_ID, 0, (व्योम *) guest_code);
	vcpu_set_hv_cpuid(vm, VCPU_ID);

	काष्ठा kvm_xen_hvm_config hvmc = अणु
		.flags = KVM_XEN_HVM_CONFIG_INTERCEPT_HCALL,
		.msr = XEN_HYPERCALL_MSR,
	पूर्ण;
	vm_ioctl(vm, KVM_XEN_HVM_CONFIG, &hvmc);

	/* Map a region क्रम the hypercall pages */
	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS,
				    HCALL_REGION_GPA, HCALL_REGION_SLOT, 2, 0);
	virt_map(vm, HCALL_REGION_GPA, HCALL_REGION_GPA, 2, 0);

	क्रम (;;) अणु
		अस्थिर काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
		काष्ठा ucall uc;

		vcpu_run(vm, VCPU_ID);

		अगर (run->निकास_reason == KVM_EXIT_XEN) अणु
			ASSERT_EQ(run->xen.type, KVM_EXIT_XEN_HCALL);
			ASSERT_EQ(run->xen.u.hcall.cpl, 0);
			ASSERT_EQ(run->xen.u.hcall.दीर्घmode, 1);
			ASSERT_EQ(run->xen.u.hcall.input, INPUTVALUE);
			ASSERT_EQ(run->xen.u.hcall.params[0], ARGVALUE(1));
			ASSERT_EQ(run->xen.u.hcall.params[1], ARGVALUE(2));
			ASSERT_EQ(run->xen.u.hcall.params[2], ARGVALUE(3));
			ASSERT_EQ(run->xen.u.hcall.params[3], ARGVALUE(4));
			ASSERT_EQ(run->xen.u.hcall.params[4], ARGVALUE(5));
			ASSERT_EQ(run->xen.u.hcall.params[5], ARGVALUE(6));
			run->xen.u.hcall.result = RETVALUE;
			जारी;
		पूर्ण

		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Got exit_reason other than KVM_EXIT_IO: %u (%s)\n",
			    run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_ABORT:
			TEST_FAIL("%s", (स्थिर अक्षर *)uc.args[0]);
			/* NOT REACHED */
		हाल UCALL_SYNC:
			अवरोध;
		हाल UCALL_DONE:
			जाओ करोne;
		शेष:
			TEST_FAIL("Unknown ucall 0x%lx.", uc.cmd);
		पूर्ण
	पूर्ण
करोne:
	kvm_vm_मुक्त(vm);
	वापस 0;
पूर्ण
