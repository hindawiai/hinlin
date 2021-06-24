<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMX-preemption समयr test
 *
 * Copyright (C) 2020, Google, LLC.
 *
 * Test to ensure the VM-Enter after migration करोesn't
 * incorrectly restarts the समयr with the full समयr
 * value instead of partially decayed समयr value
 *
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

#घोषणा VCPU_ID		5
#घोषणा PREEMPTION_TIMER_VALUE			100000000ull
#घोषणा PREEMPTION_TIMER_VALUE_THRESHOLD1	 80000000ull

u32 vmx_pt_rate;
bool l2_save_restore_करोne;
अटल u64 l2_vmx_pt_start;
अस्थिर u64 l2_vmx_pt_finish;

जोड़ vmx_basic basic;
जोड़ vmx_ctrl_msr ctrl_pin_rev;
जोड़ vmx_ctrl_msr ctrl_निकास_rev;

व्योम l2_guest_code(व्योम)
अणु
	u64 vmx_pt_delta;

	vmcall();
	l2_vmx_pt_start = (rdtsc() >> vmx_pt_rate) << vmx_pt_rate;

	/*
	 * Wait until the 1st threshold has passed
	 */
	करो अणु
		l2_vmx_pt_finish = rdtsc();
		vmx_pt_delta = (l2_vmx_pt_finish - l2_vmx_pt_start) >>
				vmx_pt_rate;
	पूर्ण जबतक (vmx_pt_delta < PREEMPTION_TIMER_VALUE_THRESHOLD1);

	/*
	 * Force L2 through Save and Restore cycle
	 */
	GUEST_SYNC(1);

	l2_save_restore_करोne = 1;

	/*
	 * Now रुको क्रम the preemption समयr to fire and
	 * निकास to L1
	 */
	जबतक ((l2_vmx_pt_finish = rdtsc()))
		;
पूर्ण

व्योम l1_guest_code(काष्ठा vmx_pages *vmx_pages)
अणु
#घोषणा L2_GUEST_STACK_SIZE 64
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];
	u64 l1_vmx_pt_start;
	u64 l1_vmx_pt_finish;
	u64 l1_tsc_deadline, l2_tsc_deadline;

	GUEST_ASSERT(vmx_pages->vmcs_gpa);
	GUEST_ASSERT(prepare_क्रम_vmx_operation(vmx_pages));
	GUEST_ASSERT(load_vmcs(vmx_pages));
	GUEST_ASSERT(vmptrstz() == vmx_pages->vmcs_gpa);

	prepare_vmcs(vmx_pages, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);

	/*
	 * Check क्रम Preemption समयr support
	 */
	basic.val = rdmsr(MSR_IA32_VMX_BASIC);
	ctrl_pin_rev.val = rdmsr(basic.ctrl ? MSR_IA32_VMX_TRUE_PINBASED_CTLS
			: MSR_IA32_VMX_PINBASED_CTLS);
	ctrl_निकास_rev.val = rdmsr(basic.ctrl ? MSR_IA32_VMX_TRUE_EXIT_CTLS
			: MSR_IA32_VMX_EXIT_CTLS);

	अगर (!(ctrl_pin_rev.clr & PIN_BASED_VMX_PREEMPTION_TIMER) ||
	    !(ctrl_निकास_rev.clr & VM_EXIT_SAVE_VMX_PREEMPTION_TIMER))
		वापस;

	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);
	vmग_लिखो(GUEST_RIP, vmपढ़ोz(GUEST_RIP) + vmपढ़ोz(VM_EXIT_INSTRUCTION_LEN));

	/*
	 * Turn on PIN control and resume the guest
	 */
	GUEST_ASSERT(!vmग_लिखो(PIN_BASED_VM_EXEC_CONTROL,
			      vmपढ़ोz(PIN_BASED_VM_EXEC_CONTROL) |
			      PIN_BASED_VMX_PREEMPTION_TIMER));

	GUEST_ASSERT(!vmग_लिखो(VMX_PREEMPTION_TIMER_VALUE,
			      PREEMPTION_TIMER_VALUE));

	vmx_pt_rate = rdmsr(MSR_IA32_VMX_MISC) & 0x1F;

	l2_save_restore_करोne = 0;

	l1_vmx_pt_start = (rdtsc() >> vmx_pt_rate) << vmx_pt_rate;

	GUEST_ASSERT(!vmresume());

	l1_vmx_pt_finish = rdtsc();

	/*
	 * Ensure निकास from L2 happens after L2 goes through
	 * save and restore
	 */
	GUEST_ASSERT(l2_save_restore_करोne);

	/*
	 * Ensure the निकास from L2 is due to preemption समयr expiry
	 */
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_PREEMPTION_TIMER);

	l1_tsc_deadline = l1_vmx_pt_start +
		(PREEMPTION_TIMER_VALUE << vmx_pt_rate);

	l2_tsc_deadline = l2_vmx_pt_start +
		(PREEMPTION_TIMER_VALUE << vmx_pt_rate);

	/*
	 * Sync with the host and pass the l1|l2 pt_expiry_finish बार and
	 * tsc deadlines so that host can verअगरy they are as expected
	 */
	GUEST_SYNC_ARGS(2, l1_vmx_pt_finish, l1_tsc_deadline,
		l2_vmx_pt_finish, l2_tsc_deadline);
पूर्ण

व्योम guest_code(काष्ठा vmx_pages *vmx_pages)
अणु
	अगर (vmx_pages)
		l1_guest_code(vmx_pages);

	GUEST_DONE();
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

	/*
	 * AMD currently करोes not implement any VMX features, so क्रम now we
	 * just early out.
	 */
	nested_vmx_check_supported();

	अगर (!kvm_check_cap(KVM_CAP_NESTED_STATE)) अणु
		prपूर्णांक_skip("KVM_CAP_NESTED_STATE not supported");
		निकास(KSFT_SKIP);
	पूर्ण

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code);
	run = vcpu_state(vm, VCPU_ID);

	vcpu_regs_get(vm, VCPU_ID, &regs1);

	vcpu_alloc_vmx(vm, &vmx_pages_gva);
	vcpu_args_set(vm, VCPU_ID, 1, vmx_pages_gva);

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
		/*
		 * If this stage 2 then we should verअगरy the vmx pt expiry
		 * is as expected.
		 * From L1's perspective verify Preemption timer hasn't
		 * expired too early.
		 * From L2's perspective verify Preemption timer hasn't
		 * expired too late.
		 */
		अगर (stage == 2) अणु

			pr_info("Stage %d: L1 PT expiry TSC (%lu) , L1 TSC deadline (%lu)\n",
				stage, uc.args[2], uc.args[3]);

			pr_info("Stage %d: L2 PT expiry TSC (%lu) , L2 TSC deadline (%lu)\n",
				stage, uc.args[4], uc.args[5]);

			TEST_ASSERT(uc.args[2] >= uc.args[3],
				"Stage %d: L1 PT expiry TSC (%lu) < L1 TSC deadline (%lu)",
				stage, uc.args[2], uc.args[3]);

			TEST_ASSERT(uc.args[4] < uc.args[5],
				"Stage %d: L2 PT expiry TSC (%lu) > L2 TSC deadline (%lu)",
				stage, uc.args[4], uc.args[5]);
		पूर्ण

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
