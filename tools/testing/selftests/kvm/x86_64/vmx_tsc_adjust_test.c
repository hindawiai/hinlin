<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vmx_tsc_adjust_test
 *
 * Copyright (C) 2018, Google LLC.
 *
 * IA32_TSC_ADJUST test
 *
 * According to the SDM, "अगर an execution of WRMSR to the
 * IA32_TIME_STAMP_COUNTER MSR adds (or subtracts) value X from the TSC,
 * the logical processor also adds (or subtracts) value X from the
 * IA32_TSC_ADJUST MSR.
 *
 * Note that when L1 करोesn't पूर्णांकercept ग_लिखोs to IA32_TSC, a
 * WRMSR(IA32_TSC) from L2 sets L1's TSC value, not L2's perceived TSC
 * value.
 *
 * This test verअगरies that this unusual हाल is handled correctly.
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"
#समावेश "vmx.h"

#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "kselftest.h"

#अगर_अघोषित MSR_IA32_TSC_ADJUST
#घोषणा MSR_IA32_TSC_ADJUST 0x3b
#पूर्ण_अगर

#घोषणा PAGE_SIZE	4096
#घोषणा VCPU_ID		5

#घोषणा TSC_ADJUST_VALUE (1ll << 32)
#घोषणा TSC_OFFSET_VALUE -(1ll << 48)

क्रमागत अणु
	PORT_ABORT = 0x1000,
	PORT_REPORT,
	PORT_DONE,
पूर्ण;

क्रमागत अणु
	VMXON_PAGE = 0,
	VMCS_PAGE,
	MSR_BITMAP_PAGE,

	NUM_VMX_PAGES,
पूर्ण;

काष्ठा kvm_single_msr अणु
	काष्ठा kvm_msrs header;
	काष्ठा kvm_msr_entry entry;
पूर्ण __attribute__((packed));

/* The भव machine object. */
अटल काष्ठा kvm_vm *vm;

अटल व्योम check_ia32_tsc_adjust(पूर्णांक64_t max)
अणु
	पूर्णांक64_t adjust;

	adjust = rdmsr(MSR_IA32_TSC_ADJUST);
	GUEST_SYNC(adjust);
	GUEST_ASSERT(adjust <= max);
पूर्ण

अटल व्योम l2_guest_code(व्योम)
अणु
	uपूर्णांक64_t l1_tsc = rdtsc() - TSC_OFFSET_VALUE;

	wrmsr(MSR_IA32_TSC, l1_tsc - TSC_ADJUST_VALUE);
	check_ia32_tsc_adjust(-2 * TSC_ADJUST_VALUE);

	/* Exit to L1 */
	__यंत्र__ __अस्थिर__("vmcall");
पूर्ण

अटल व्योम l1_guest_code(काष्ठा vmx_pages *vmx_pages)
अणु
#घोषणा L2_GUEST_STACK_SIZE 64
	अचिन्हित दीर्घ l2_guest_stack[L2_GUEST_STACK_SIZE];
	uपूर्णांक32_t control;
	uपूर्णांकptr_t save_cr3;

	GUEST_ASSERT(rdtsc() < TSC_ADJUST_VALUE);
	wrmsr(MSR_IA32_TSC, rdtsc() - TSC_ADJUST_VALUE);
	check_ia32_tsc_adjust(-1 * TSC_ADJUST_VALUE);

	GUEST_ASSERT(prepare_क्रम_vmx_operation(vmx_pages));
	GUEST_ASSERT(load_vmcs(vmx_pages));

	/* Prepare the VMCS क्रम L2 execution. */
	prepare_vmcs(vmx_pages, l2_guest_code,
		     &l2_guest_stack[L2_GUEST_STACK_SIZE]);
	control = vmपढ़ोz(CPU_BASED_VM_EXEC_CONTROL);
	control |= CPU_BASED_USE_MSR_BITMAPS | CPU_BASED_USE_TSC_OFFSETTING;
	vmग_लिखो(CPU_BASED_VM_EXEC_CONTROL, control);
	vmग_लिखो(TSC_OFFSET, TSC_OFFSET_VALUE);

	/* Jump पूर्णांकo L2.  First, test failure to load guest CR3.  */
	save_cr3 = vmपढ़ोz(GUEST_CR3);
	vmग_लिखो(GUEST_CR3, -1ull);
	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) ==
		     (EXIT_REASON_FAILED_VMENTRY | EXIT_REASON_INVALID_STATE));
	check_ia32_tsc_adjust(-1 * TSC_ADJUST_VALUE);
	vmग_लिखो(GUEST_CR3, save_cr3);

	GUEST_ASSERT(!vmlaunch());
	GUEST_ASSERT(vmपढ़ोz(VM_EXIT_REASON) == EXIT_REASON_VMCALL);

	check_ia32_tsc_adjust(-2 * TSC_ADJUST_VALUE);

	GUEST_DONE();
पूर्ण

अटल व्योम report(पूर्णांक64_t val)
अणु
	pr_info("IA32_TSC_ADJUST is %ld (%lld * TSC_ADJUST_VALUE + %lld).\n",
		val, val / TSC_ADJUST_VALUE, val % TSC_ADJUST_VALUE);
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

		चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
		हाल UCALL_ABORT:
			TEST_FAIL("%s", (स्थिर अक्षर *)uc.args[0]);
			/* NOT REACHED */
		हाल UCALL_SYNC:
			report(uc.args[1]);
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
