<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018, Red Hat, Inc.
 *
 * Tests क्रम Enlightened VMCS, including nested guest state.
 */
#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"

#समावेश "kvm_util.h"

#समावेश "vmx.h"

#घोषणा VCPU_ID		5
#घोषणा NMI_VECTOR	2

अटल पूर्णांक ud_count;

व्योम enable_x2apic(व्योम)
अणु
	uपूर्णांक32_t spiv_reg = APIC_BASE_MSR + (APIC_SPIV >> 4);

	wrmsr(MSR_IA32_APICBASE, rdmsr(MSR_IA32_APICBASE) |
	      MSR_IA32_APICBASE_ENABLE | MSR_IA32_APICBASE_EXTD);
	wrmsr(spiv_reg, rdmsr(spiv_reg) | APIC_SPIV_APIC_ENABLED);
पूर्ण

अटल व्योम guest_ud_handler(काष्ठा ex_regs *regs)
अणु
	ud_count++;
	regs->rip += 3; /* VMLAUNCH */
पूर्ण

अटल व्योम guest_nmi_handler(काष्ठा ex_regs *regs)
अणु
पूर्ण

व्योम l2_guest_code(व्योम)
अणु
	GUEST_SYNC(7);

	GUEST_SYNC(8);

	/* Forced निकास to L1 upon restore */
	GUEST_SYNC(9);

	/* Done, निकास to L1 and never come back.  */
	vmcall();
पूर्ण

व्योम guest_code(काष्ठा vmx_pages *vmx_pages)
अणु
#घोषणा L2_GUEST_STACK_SIZE 64
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];

	enable_x2apic();

	GUEST_SYNC(1);
	GUEST_SYNC(2);

	enable_vp_assist(vmx_pages->vp_assist_gpa, vmx_pages->vp_assist);

	GUEST_ASSERT(vmx_pages->vmcs_gpa);
	GUEST_ASSERT(prepare_क्रम_vmx_operation(vmx_pages));
	GUEST_SYNC(3);
	GUEST_ASSERT(load_vmcs(vmx_pages));
	GUEST_ASSERT(vmptrstz() == vmx_pages->enlightened_vmcs_gpa);

	GUEST_SYNC(4);
	GUEST_ASSERT(vmptrstz() == vmx_pages->enlightened_vmcs_gpa);

	prepare_vmcs(vmx_pages, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	GUEST_SYNC(5);
	GUEST_ASSERT(vmptrstz() == vmx_pages->enlightened_vmcs_gpa);
	current_evmcs->revision_id = -1u;
	GUEST_ASSERT(vmlaunch());
	current_evmcs->revision_id = EVMCS_VERSION;
	GUEST_SYNC(6);

	current_evmcs->pin_based_vm_exec_control |=
		PIN_BASED_NMI_EXITING;
	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(vmptrstz() == vmx_pages->enlightened_vmcs_gpa);

	/*
	 * NMI क्रमces L2->L1 निकास, resuming L2 and hope that EVMCS is
	 * up-to-date (RIP poपूर्णांकs where it should and not at the beginning
	 * of l2_guest_code(). GUEST_SYNC(9) checkes that.
	 */
	GUEST_ASSERT(!vmresume());

	GUEST_SYNC(10);

	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);
	GUEST_SYNC(11);

	/* Try enlightened vmptrld with an incorrect GPA */
	evmcs_vmptrld(0xdeadbeef, vmx_pages->enlightened_vmcs);
	GUEST_ASSERT(vmlaunch());
	GUEST_ASSERT(ud_count == 1);
	GUEST_DONE();
पूर्ण

व्योम inject_nmi(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_vcpu_events events;

	vcpu_events_get(vm, VCPU_ID, &events);

	events.nmi.pending = 1;
	events.flags |= KVM_VCPUEVENT_VALID_NMI_PENDING;

	vcpu_events_set(vm, VCPU_ID, &events);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	vm_vaddr_t vmx_pages_gva = 0;

	काष्ठा kvm_regs regs1, regs2;
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	काष्ठा kvm_x86_state *state;
	काष्ठा ucall uc;
	पूर्णांक stage;

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code);

	अगर (!nested_vmx_supported() ||
	    !kvm_check_cap(KVM_CAP_NESTED_STATE) ||
	    !kvm_check_cap(KVM_CAP_HYPERV_ENLIGHTENED_VMCS)) अणु
		prपूर्णांक_skip("Enlightened VMCS is unsupported");
		निकास(KSFT_SKIP);
	पूर्ण

	vcpu_set_hv_cpuid(vm, VCPU_ID);
	vcpu_enable_evmcs(vm, VCPU_ID);

	run = vcpu_state(vm, VCPU_ID);

	vcpu_regs_get(vm, VCPU_ID, &regs1);

	vcpu_alloc_vmx(vm, &vmx_pages_gva);
	vcpu_args_set(vm, VCPU_ID, 1, vmx_pages_gva);

	vm_init_descriptor_tables(vm);
	vcpu_init_descriptor_tables(vm, VCPU_ID);
	vm_handle_exception(vm, UD_VECTOR, guest_ud_handler);
	vm_handle_exception(vm, NMI_VECTOR, guest_nmi_handler);

	pr_info("Running L1 which uses EVMCS to run L2\n");

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
		vcpu_set_hv_cpuid(vm, VCPU_ID);
		vcpu_enable_evmcs(vm, VCPU_ID);
		vcpu_load_state(vm, VCPU_ID, state);
		run = vcpu_state(vm, VCPU_ID);
		मुक्त(state);

		स_रखो(&regs2, 0, माप(regs2));
		vcpu_regs_get(vm, VCPU_ID, &regs2);
		TEST_ASSERT(!स_भेद(&regs1, &regs2, माप(regs2)),
			    "Unexpected register values after vcpu_load_state; rdi: %lx rsi: %lx",
			    (uदीर्घ) regs2.rdi, (uदीर्घ) regs2.rsi);

		/* Force immediate L2->L1 निकास beक्रमe resuming */
		अगर (stage == 8) अणु
			pr_info("Injecting NMI into L1 before L2 had a chance to run after restore\n");
			inject_nmi(vm);
		पूर्ण
	पूर्ण

करोne:
	kvm_vm_मुक्त(vm);
पूर्ण
