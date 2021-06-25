<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * svm_vmcall_test
 *
 * Copyright (C) 2020, Red Hat, Inc.
 *
 * Nested SVM testing: VMCALL
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"
#समावेश "svm_util.h"

#घोषणा VCPU_ID		5

अटल काष्ठा kvm_vm *vm;

अटल व्योम l2_guest_code(काष्ठा svm_test_data *svm)
अणु
	__यंत्र__ __अस्थिर__("vmcall");
पूर्ण

अटल व्योम l1_guest_code(काष्ठा svm_test_data *svm)
अणु
	#घोषणा L2_GUEST_STACK_SIZE 64
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];
	काष्ठा vmcb *vmcb = svm->vmcb;

	/* Prepare क्रम L2 execution. */
	generic_svm_setup(svm, l2_guest_code,
			  &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	run_guest(vmcb, svm->vmcb_gpa);

	GUEST_ASSERT(vmcb->control.निकास_code == SVM_EXIT_VMMCALL);
	GUEST_DONE();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	vm_vaddr_t svm_gva;

	nested_svm_check_supported();

	vm = vm_create_शेष(VCPU_ID, 0, (व्योम *) l1_guest_code);

	vcpu_alloc_svm(vm, &svm_gva);
	vcpu_args_set(vm, VCPU_ID, 1, svm_gva);

	क्रम (;;) अणु
		अस्थिर काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
		काष्ठा ucall uc;

		vcpu_run(vm, VCPU_ID);
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
