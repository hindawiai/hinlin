<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018, Red Hat, Inc.
 *
 * Tests क्रम SMM.
 */
#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"

#समावेश "kvm_util.h"

#समावेश "vmx.h"
#समावेश "svm_util.h"

#घोषणा VCPU_ID	      1

#घोषणा PAGE_SIZE  4096

#घोषणा SMRAM_SIZE 65536
#घोषणा SMRAM_MEMSLOT ((1 << 16) | 1)
#घोषणा SMRAM_PAGES (SMRAM_SIZE / PAGE_SIZE)
#घोषणा SMRAM_GPA 0x1000000
#घोषणा SMRAM_STAGE 0xfe

#घोषणा STR(x) #x
#घोषणा XSTR(s) STR(s)

#घोषणा SYNC_PORT 0xe
#घोषणा DONE 0xff

/*
 * This is compiled as normal 64-bit code, however, SMI handler is executed
 * in real-address mode. To stay simple we're limiting ourselves to a mode
 * independent subset of यंत्र here.
 * SMI handler always report back fixed stage SMRAM_STAGE.
 */
uपूर्णांक8_t smi_handler[] = अणु
	0xb0, SMRAM_STAGE,    /* mov $SMRAM_STAGE, %al */
	0xe4, SYNC_PORT,      /* in $SYNC_PORT, %al */
	0x0f, 0xaa,           /* rsm */
पूर्ण;

अटल अंतरभूत व्योम sync_with_host(uपूर्णांक64_t phase)
अणु
	यंत्र अस्थिर("in $" XSTR(SYNC_PORT)", %%al \n"
		     : "+a" (phase));
पूर्ण

व्योम self_smi(व्योम)
अणु
	wrmsr(APIC_BASE_MSR + (APIC_ICR >> 4),
	      APIC_DEST_SELF | APIC_INT_ASSERT | APIC_DM_SMI);
पूर्ण

व्योम guest_code(व्योम *arg)
अणु
	uपूर्णांक64_t apicbase = rdmsr(MSR_IA32_APICBASE);

	sync_with_host(1);

	wrmsr(MSR_IA32_APICBASE, apicbase | X2APIC_ENABLE);

	sync_with_host(2);

	self_smi();

	sync_with_host(4);

	अगर (arg) अणु
		अगर (cpu_has_svm())
			generic_svm_setup(arg, शून्य, शून्य);
		अन्यथा
			GUEST_ASSERT(prepare_क्रम_vmx_operation(arg));

		sync_with_host(5);

		self_smi();

		sync_with_host(7);
	पूर्ण

	sync_with_host(DONE);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	vm_vaddr_t nested_gva = 0;

	काष्ठा kvm_regs regs;
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	काष्ठा kvm_x86_state *state;
	पूर्णांक stage, stage_reported;

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code);

	run = vcpu_state(vm, VCPU_ID);

	vm_userspace_mem_region_add(vm, VM_MEM_SRC_ANONYMOUS, SMRAM_GPA,
				    SMRAM_MEMSLOT, SMRAM_PAGES, 0);
	TEST_ASSERT(vm_phy_pages_alloc(vm, SMRAM_PAGES, SMRAM_GPA, SMRAM_MEMSLOT)
		    == SMRAM_GPA, "could not allocate guest physical addresses?");

	स_रखो(addr_gpa2hva(vm, SMRAM_GPA), 0x0, SMRAM_SIZE);
	स_नकल(addr_gpa2hva(vm, SMRAM_GPA) + 0x8000, smi_handler,
	       माप(smi_handler));

	vcpu_set_msr(vm, VCPU_ID, MSR_IA32_SMBASE, SMRAM_GPA);

	अगर (kvm_check_cap(KVM_CAP_NESTED_STATE)) अणु
		अगर (nested_svm_supported())
			vcpu_alloc_svm(vm, &nested_gva);
		अन्यथा अगर (nested_vmx_supported())
			vcpu_alloc_vmx(vm, &nested_gva);
	पूर्ण

	अगर (!nested_gva)
		pr_info("will skip SMM test with VMX enabled\n");

	vcpu_args_set(vm, VCPU_ID, 1, nested_gva);

	क्रम (stage = 1;; stage++) अणु
		_vcpu_run(vm, VCPU_ID);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			    "Stage %d: unexpected exit reason: %u (%s),\n",
			    stage, run->निकास_reason,
			    निकास_reason_str(run->निकास_reason));

		स_रखो(&regs, 0, माप(regs));
		vcpu_regs_get(vm, VCPU_ID, &regs);

		stage_reported = regs.rax & 0xff;

		अगर (stage_reported == DONE)
			जाओ करोne;

		TEST_ASSERT(stage_reported == stage ||
			    stage_reported == SMRAM_STAGE,
			    "Unexpected stage: #%x, got %x",
			    stage, stage_reported);

		state = vcpu_save_state(vm, VCPU_ID);
		kvm_vm_release(vm);
		kvm_vm_restart(vm, O_RDWR);
		vm_vcpu_add(vm, VCPU_ID);
		vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());
		vcpu_load_state(vm, VCPU_ID, state);
		run = vcpu_state(vm, VCPU_ID);
		मुक्त(state);
	पूर्ण

करोne:
	kvm_vm_मुक्त(vm);
पूर्ण
