<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test that KVM_SET_BOOT_CPU_ID works as पूर्णांकended
 *
 * Copyright (C) 2020, Red Hat, Inc.
 */
#घोषणा _GNU_SOURCE /* क्रम program_invocation_name */
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा N_VCPU 2
#घोषणा VCPU_ID0 0
#घोषणा VCPU_ID1 1

अटल uपूर्णांक32_t get_bsp_flag(व्योम)
अणु
	वापस rdmsr(MSR_IA32_APICBASE) & MSR_IA32_APICBASE_BSP;
पूर्ण

अटल व्योम guest_bsp_vcpu(व्योम *arg)
अणु
	GUEST_SYNC(1);

	GUEST_ASSERT(get_bsp_flag() != 0);

	GUEST_DONE();
पूर्ण

अटल व्योम guest_not_bsp_vcpu(व्योम *arg)
अणु
	GUEST_SYNC(1);

	GUEST_ASSERT(get_bsp_flag() == 0);

	GUEST_DONE();
पूर्ण

अटल व्योम test_set_boot_busy(काष्ठा kvm_vm *vm)
अणु
	पूर्णांक res;

	res = _vm_ioctl(vm, KVM_SET_BOOT_CPU_ID, (व्योम *) VCPU_ID0);
	TEST_ASSERT(res == -1 && त्रुटि_सं == EBUSY,
			"KVM_SET_BOOT_CPU_ID set while running vm");
पूर्ण

अटल व्योम run_vcpu(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	काष्ठा ucall uc;
	पूर्णांक stage;

	क्रम (stage = 0; stage < 2; stage++) अणु

		vcpu_run(vm, vcpuid);

		चयन (get_ucall(vm, vcpuid, &uc)) अणु
		हाल UCALL_SYNC:
			TEST_ASSERT(!म_भेद((स्थिर अक्षर *)uc.args[0], "hello") &&
					uc.args[1] == stage + 1,
					"Stage %d: Unexpected register values vmexit, got %lx",
					stage + 1, (uदीर्घ)uc.args[1]);
			test_set_boot_busy(vm);
			अवरोध;
		हाल UCALL_DONE:
			TEST_ASSERT(stage == 1,
					"Expected GUEST_DONE in stage 2, got stage %d",
					stage);
			अवरोध;
		हाल UCALL_ABORT:
			TEST_ASSERT(false, "%s at %s:%ld\n\tvalues: %#lx, %#lx",
						(स्थिर अक्षर *)uc.args[0], __खाता__,
						uc.args[1], uc.args[2], uc.args[3]);
		शेष:
			TEST_ASSERT(false, "Unexpected exit: %s",
					निकास_reason_str(vcpu_state(vm, vcpuid)->निकास_reason));
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा kvm_vm *create_vm(व्योम)
अणु
	काष्ठा kvm_vm *vm;
	uपूर्णांक64_t vcpu_pages = (DEFAULT_STACK_PGS) * 2;
	uपूर्णांक64_t extra_pg_pages = vcpu_pages / PTES_PER_MIN_PAGE * N_VCPU;
	uपूर्णांक64_t pages = DEFAULT_GUEST_PHY_PAGES + vcpu_pages + extra_pg_pages;

	pages = vm_adjust_num_guest_pages(VM_MODE_DEFAULT, pages);
	vm = vm_create(VM_MODE_DEFAULT, pages, O_RDWR);

	kvm_vm_elf_load(vm, program_invocation_name, 0, 0);
	vm_create_irqchip(vm);

	वापस vm;
पूर्ण

अटल व्योम add_x86_vcpu(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid, bool bsp_code)
अणु
	अगर (bsp_code)
		vm_vcpu_add_शेष(vm, vcpuid, guest_bsp_vcpu);
	अन्यथा
		vm_vcpu_add_शेष(vm, vcpuid, guest_not_bsp_vcpu);

	vcpu_set_cpuid(vm, vcpuid, kvm_get_supported_cpuid());
पूर्ण

अटल व्योम run_vm_bsp(uपूर्णांक32_t bsp_vcpu)
अणु
	काष्ठा kvm_vm *vm;
	bool is_bsp_vcpu1 = bsp_vcpu == VCPU_ID1;

	vm = create_vm();

	अगर (is_bsp_vcpu1)
		vm_ioctl(vm, KVM_SET_BOOT_CPU_ID, (व्योम *) VCPU_ID1);

	add_x86_vcpu(vm, VCPU_ID0, !is_bsp_vcpu1);
	add_x86_vcpu(vm, VCPU_ID1, is_bsp_vcpu1);

	run_vcpu(vm, VCPU_ID0);
	run_vcpu(vm, VCPU_ID1);

	kvm_vm_मुक्त(vm);
पूर्ण

अटल व्योम check_set_bsp_busy(व्योम)
अणु
	काष्ठा kvm_vm *vm;
	पूर्णांक res;

	vm = create_vm();

	add_x86_vcpu(vm, VCPU_ID0, true);
	add_x86_vcpu(vm, VCPU_ID1, false);

	res = _vm_ioctl(vm, KVM_SET_BOOT_CPU_ID, (व्योम *) VCPU_ID1);
	TEST_ASSERT(res == -1 && त्रुटि_सं == EBUSY, "KVM_SET_BOOT_CPU_ID set after adding vcpu");

	run_vcpu(vm, VCPU_ID0);
	run_vcpu(vm, VCPU_ID1);

	res = _vm_ioctl(vm, KVM_SET_BOOT_CPU_ID, (व्योम *) VCPU_ID1);
	TEST_ASSERT(res == -1 && त्रुटि_सं == EBUSY, "KVM_SET_BOOT_CPU_ID set to a terminated vcpu");

	kvm_vm_मुक्त(vm);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	अगर (!kvm_check_cap(KVM_CAP_SET_BOOT_CPU_ID)) अणु
		prपूर्णांक_skip("set_boot_cpu_id not available");
		वापस 0;
	पूर्ण

	run_vm_bsp(VCPU_ID0);
	run_vm_bsp(VCPU_ID1);
	run_vm_bsp(VCPU_ID0);

	check_set_bsp_busy();
पूर्ण
