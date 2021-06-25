<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vmx_बंद_जबतक_nested
 *
 * Copyright (C) 2019, Red Hat, Inc.
 *
 * Verअगरy that nothing bad happens अगर a KVM user निकासs with खोलो
 * file descriptors जबतक executing a nested guest.
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"
#समावेश "vmx.h"

#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "kselftest.h"

#घोषणा VCPU_ID		5

क्रमागत अणु
	PORT_L0_EXIT = 0x2000,
पूर्ण;

/* The भव machine object. */
अटल काष्ठा kvm_vm *vm;

अटल व्योम l2_guest_code(व्योम)
अणु
	/* Exit to L0 */
        यंत्र अस्थिर("inb %%dx, %%al"
                     : : [port] "d" (PORT_L0_EXIT) : "rax");
पूर्ण

अटल व्योम l1_guest_code(काष्ठा vmx_pages *vmx_pages)
अणु
#घोषणा L2_GUEST_STACK_SIZE 64
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];

	GUEST_ASSERT(prepare_क्रम_vmx_operation(vmx_pages));
	GUEST_ASSERT(load_vmcs(vmx_pages));

	/* Prepare the VMCS क्रम L2 execution. */
	prepare_vmcs(vmx_pages, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	vm_vaddr_t vmx_pages_gva;

	nested_vmx_check_supported();

	vm = vm_create_शेष(VCPU_ID, 0, (व्योम *) l1_guest_code);

	/* Allocate VMX pages and shared descriptors (vmx_pages). */
	vcpu_alloc_vmx(vm, &vmx_pages_gva);
	vcpu_args_set(vm, VCPU_ID, 1, vmx_pages_gva);

	क्रम (;;) अणु
		अस्थिर काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
		काष्ठा ucall uc;

		vcpu_run(vm, VCPU_ID);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Got exit_reason other than KVM_EXIT_IO: %u (%s)\n",
			    run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		अगर (run->io.port == PORT_L0_EXIT)
			अवरोध;

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_ABORT:
			TEST_FAIL("%s", (स्थिर अक्षर *)uc.args[0]);
			/* NOT REACHED */
		शेष:
			TEST_FAIL("Unknown ucall %lu", uc.cmd);
		पूर्ण
	पूर्ण
पूर्ण
