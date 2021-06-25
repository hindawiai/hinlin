<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KVM_GET/SET_* tests
 *
 * Copyright (C) 2018, Red Hat, Inc.
 *
 * Tests क्रम vCPU state save/restore, including nested guest state.
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
#समावेश "vmx.h"
#समावेश "svm_util.h"

#घोषणा VCPU_ID		5
#घोषणा L2_GUEST_STACK_SIZE 256

व्योम svm_l2_guest_code(व्योम)
अणु
	GUEST_SYNC(4);
	/* Exit to L1 */
	vmcall();
	GUEST_SYNC(6);
	/* Done, निकास to L1 and never come back.  */
	vmcall();
पूर्ण

अटल व्योम svm_l1_guest_code(काष्ठा svm_test_data *svm)
अणु
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];
	काष्ठा vmcb *vmcb = svm->vmcb;

	GUEST_ASSERT(svm->vmcb_gpa);
	/* Prepare क्रम L2 execution. */
	generic_svm_setup(svm, svm_l2_guest_code,
			  &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_SYNC(3);
	run_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSERT(vmcb->control.निकास_code == SVM_EXIT_VMMCALL);
	GUEST_SYNC(5);
	vmcb->save.rip += 3;
	run_guest(vmcb, svm->vmcb_gpa);
	GUEST_ASSERT(vmcb->control.निकास_code == SVM_EXIT_VMMCALL);
	GUEST_SYNC(7);
पूर्ण

व्योम vmx_l2_guest_code(व्योम)
अणु
	GUEST_SYNC(6);

	/* Exit to L1 */
	vmcall();

	/* L1 has now set up a shaकरोw VMCS क्रम us.  */
	GUEST_ASSERT(vmपढ़ोz(GUEST_RIP) == 0xc0ffee);
	GUEST_SYNC(10);
	GUEST_ASSERT(vmपढ़ोz(GUEST_RIP) == 0xc0ffee);
	GUEST_ASSERT(!vmग_लिखो(GUEST_RIP, 0xc0fffee));
	GUEST_SYNC(11);
	GUEST_ASSERT(vmपढ़ोz(GUEST_RIP) == 0xc0fffee);
	GUEST_ASSERT(!vmग_लिखो(GUEST_RIP, 0xc0ffffee));
	GUEST_SYNC(12);

	/* Done, निकास to L1 and never come back.  */
	vmcall();
पूर्ण

अटल व्योम vmx_l1_guest_code(काष्ठा vmx_pages *vmx_pages)
अणु
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];

	GUEST_ASSERT(vmx_pages->vmcs_gpa);
	GUEST_ASSERT(prepare_क्रम_vmx_operation(vmx_pages));
	GUEST_SYNC(3);
	GUEST_ASSERT(load_vmcs(vmx_pages));
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);

	GUEST_SYNC(4);
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);

	prepare_vmcs(vmx_pages, vmx_l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_SYNC(5);
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);
	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	/* Check that the launched state is preserved.  */
	GUEST_ASSERT(vmlaunch());

	GUEST_ASSERT(!vmresume());
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	GUEST_SYNC(7);
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	GUEST_ASSERT(!vmresume());
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	vmग_लिखो(GUEST_RIP, vmपढ़ोz(GUEST_RIP) + 3);

	vmग_लिखो(SECONDARY_VM_EXEC_CONTROL, SECONDARY_EXEC_SHADOW_VMCS);
	vmग_लिखो(VMCS_LINK_POINTER, vmx_pages->shaकरोw_vmcs_gpa);

	GUEST_ASSERT(!vmptrld(vmx_pages->shaकरोw_vmcs_gpa));
	GUEST_ASSERT(vmlaunch());
	GUEST_SYNC(8);
	GUEST_ASSERT(vmlaunch());
	GUEST_ASSERT(vmresume());

	vmग_लिखो(GUEST_RIP, 0xc0ffee);
	GUEST_SYNC(9);
	GUEST_ASSERT(vmपढ़ोz(GUEST_RIP) == 0xc0ffee);

	GUEST_ASSERT(!vmptrld(vmx_pages->vmcs_gpa));
	GUEST_ASSERT(!vmresume());
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	GUEST_ASSERT(!vmptrld(vmx_pages->shaकरोw_vmcs_gpa));
	GUEST_ASSERT(vmपढ़ोz(GUEST_RIP) == 0xc0ffffee);
	GUEST_ASSERT(vmlaunch());
	GUEST_ASSERT(vmresume());
	GUEST_SYNC(13);
	GUEST_ASSERT(vmपढ़ोz(GUEST_RIP) == 0xc0ffffee);
	GUEST_ASSERT(vmlaunch());
	GUEST_ASSERT(vmresume());
पूर्ण

अटल व्योम __attribute__((__flatten__)) guest_code(व्योम *arg)
अणु
	GUEST_SYNC(1);
	GUEST_SYNC(2);

	अगर (arg) अणु
		अगर (cpu_has_svm())
			svm_l1_guest_code(arg);
		अन्यथा
			vmx_l1_guest_code(arg);
	पूर्ण

	GUEST_DONE();
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	vm_vaddr_t nested_gva = 0;

	काष्ठा kvm_regs regs1, regs2;
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	काष्ठा kvm_x86_state *state;
	काष्ठा ucall uc;
	पूर्णांक stage;

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code);
	run = vcpu_state(vm, VCPU_ID);

	vcpu_regs_get(vm, VCPU_ID, &regs1);

	अगर (kvm_check_cap(KVM_CAP_NESTED_STATE)) अणु
		अगर (nested_svm_supported())
			vcpu_alloc_svm(vm, &nested_gva);
		अन्यथा अगर (nested_vmx_supported())
			vcpu_alloc_vmx(vm, &nested_gva);
	पूर्ण

	अगर (!nested_gva)
		pr_info("will skip nested state checks\n");

	vcpu_args_set(vm, VCPU_ID, 1, nested_gva);

	क्रम (stage = 1;; stage++) अणु
		_vcpu_run(vm, VCPU_ID);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Stage %d: unexpected exit reason: %u (%s),\n",
			    stage, run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_ABORT:
			TEST_FAIL("%s at %s:%ld", (स्थिर अक्षर *)uc.args[0],
			       	  __खाता__, uc.args[1]);
			/* NOT REACHED */
		हाल UCALL_SYNC:
			अवरोध;
		हाल UCALL_DONE:
			जाओ करोne;
		शेष:
			TEST_FAIL("Unknown ucall %lu", uc.cmd);
		पूर्ण

		/* UCALL_SYNC is handled here.  */
		TEST_ASSERT(!म_भेद((स्थिर अक्षर *)uc.args[0], "hello") &&
			    uc.args[1] == stage, "Stage %d: Unexpected register values vmexit, got %lx",
			    stage, (uदीर्घ)uc.args[1]);

		state = vcpu_save_state(vm, VCPU_ID);
		स_रखो(&regs1, 0, माप(regs1));
		vcpu_regs_get(vm, VCPU_ID, &regs1);

		kvm_vm_release(vm);

		/* Restore state in a new VM.  */
		kvm_vm_restart(vm, O_RDWR);
		vm_vcpu_add(vm, VCPU_ID);
		vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());
		vcpu_load_state(vm, VCPU_ID, state);
		run = vcpu_state(vm, VCPU_ID);
		मुक्त(state);

		स_रखो(&regs2, 0, माप(regs2));
		vcpu_regs_get(vm, VCPU_ID, &regs2);
		TEST_ASSERT(!स_भेद(&regs1, &regs2, माप(regs2)),
			    "Unexpected register values after vcpu_load_state; rdi: %lx rsi: %lx",
			    (uदीर्घ) regs2.rdi, (uदीर्घ) regs2.rsi);
	पूर्ण

करोne:
	kvm_vm_मुक्त(vm);
पूर्ण
