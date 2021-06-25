<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vmx_apic_access_test
 *
 * Copyright (C) 2020, Google LLC.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 *
 * The first subtest simply checks to see that an L2 guest can be
 * launched with a valid APIC-access address that is backed by a
 * page of L1 physical memory.
 *
 * The second subtest sets the APIC-access address to a (valid) L1
 * physical address that is not backed by memory. KVM can't handle
 * this situation, so resuming L2 should result in a KVM निकास क्रम
 * पूर्णांकernal error (emulation). This is not an architectural
 * requirement. It is just a लघुcoming of KVM. The पूर्णांकernal error
 * is unक्रमtunate, but it's better than what used to happen!
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"
#समावेश "vmx.h"

#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "kselftest.h"

#घोषणा VCPU_ID		0

/* The भव machine object. */
अटल काष्ठा kvm_vm *vm;

अटल व्योम l2_guest_code(व्योम)
अणु
	/* Exit to L1 */
	__यंत्र__ __अस्थिर__("vmcall");
पूर्ण

अटल व्योम l1_guest_code(काष्ठा vmx_pages *vmx_pages, अचिन्हित दीर्घ high_gpa)
अणु
#घोषणा L2_GUEST_STACK_SIZE 64
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];
	uपूर्णांक32_t control;

	GUEST_ASSERT(prepare_क्रम_vmx_operation(vmx_pages));
	GUEST_ASSERT(load_vmcs(vmx_pages));

	/* Prepare the VMCS क्रम L2 execution. */
	prepare_vmcs(vmx_pages, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);
	control = vmपढ़ोz(CPU_BASED_VM_EXEC_CONTROL);
	control |= CPU_BASED_ACTIVATE_SECONDARY_CONTROLS;
	vmग_लिखो(CPU_BASED_VM_EXEC_CONTROL, control);
	control = vmपढ़ोz(SECONDARY_VM_EXEC_CONTROL);
	control |= SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES;
	vmग_लिखो(SECONDARY_VM_EXEC_CONTROL, control);
	vmग_लिखो(APIC_ACCESS_ADDR, vmx_pages->apic_access_gpa);

	/* Try to launch L2 with the memory-backed APIC-access address. */
	GUEST_SYNC(vmपढ़ोz(APIC_ACCESS_ADDR));
	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	vmग_लिखो(APIC_ACCESS_ADDR, high_gpa);

	/* Try to resume L2 with the unbacked APIC-access address. */
	GUEST_SYNC(vmपढ़ोz(APIC_ACCESS_ADDR));
	GUEST_ASSERT(!vmresume());
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	GUEST_DONE();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अचिन्हित दीर्घ apic_access_addr = ~0ul;
	अचिन्हित पूर्णांक paddr_width;
	अचिन्हित पूर्णांक vaddr_width;
	vm_vaddr_t vmx_pages_gva;
	अचिन्हित दीर्घ high_gpa;
	काष्ठा vmx_pages *vmx;
	bool करोne = false;

	nested_vmx_check_supported();

	vm = vm_create_शेष(VCPU_ID, 0, (व्योम *) l1_guest_code);

	kvm_get_cpu_address_width(&paddr_width, &vaddr_width);
	high_gpa = (1ul << paddr_width) - getpagesize();
	अगर ((अचिन्हित दीर्घ)DEFAULT_GUEST_PHY_PAGES * getpagesize() > high_gpa) अणु
		prपूर्णांक_skip("No unbacked physical page available");
		निकास(KSFT_SKIP);
	पूर्ण

	vmx = vcpu_alloc_vmx(vm, &vmx_pages_gva);
	prepare_भवize_apic_accesses(vmx, vm, 0);
	vcpu_args_set(vm, VCPU_ID, 2, vmx_pages_gva, high_gpa);

	जबतक (!करोne) अणु
		अस्थिर काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
		काष्ठा ucall uc;

		vcpu_run(vm, VCPU_ID);
		अगर (apic_access_addr == high_gpa) अणु
			TEST_ASSERT(run->निकास_reason ==
				    KVM_EXIT_INTERNAL_ERROR,
				    "Got exit reason other than KVM_EXIT_INTERNAL_ERROR: %u (%s)\n",
				    run->निकास_reason,
				    निकास_reason_str(run->निकास_reason));
			TEST_ASSERT(run->पूर्णांकernal.suberror ==
				    KVM_INTERNAL_ERROR_EMULATION,
				    "Got internal suberror other than KVM_INTERNAL_ERROR_EMULATION: %u\n",
				    run->पूर्णांकernal.suberror);
			अवरोध;
		पूर्ण
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Got exit_reason other than KVM_EXIT_IO: %u (%s)\n",
			    run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_ABORT:
			TEST_FAIL("%s at %s:%ld", (स्थिर अक्षर *)uc.args[0],
				  __खाता__, uc.args[1]);
			/* NOT REACHED */
		हाल UCALL_SYNC:
			apic_access_addr = uc.args[1];
			अवरोध;
		हाल UCALL_DONE:
			करोne = true;
			अवरोध;
		शेष:
			TEST_ASSERT(false, "Unknown ucall %lu", uc.cmd);
		पूर्ण
	पूर्ण
	kvm_vm_मुक्त(vm);
	वापस 0;
पूर्ण
