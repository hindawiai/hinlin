<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test क्रम x86 KVM_CAP_MSR_PLATFORM_INFO
 *
 * Copyright (C) 2018, Google LLC.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 *
 * Verअगरies expected behavior of controlling guest access to
 * MSR_PLATFORM_INFO.
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

#घोषणा VCPU_ID 0
#घोषणा MSR_PLATFORM_INFO_MAX_TURBO_RATIO 0xff00

अटल व्योम guest_code(व्योम)
अणु
	uपूर्णांक64_t msr_platक्रमm_info;

	क्रम (;;) अणु
		msr_platक्रमm_info = rdmsr(MSR_PLATFORM_INFO);
		GUEST_SYNC(msr_platक्रमm_info);
		यंत्र अस्थिर ("inc %r11");
	पूर्ण
पूर्ण

अटल व्योम set_msr_platक्रमm_info_enabled(काष्ठा kvm_vm *vm, bool enable)
अणु
	काष्ठा kvm_enable_cap cap = अणुपूर्ण;

	cap.cap = KVM_CAP_MSR_PLATFORM_INFO;
	cap.flags = 0;
	cap.args[0] = (पूर्णांक)enable;
	vm_enable_cap(vm, &cap);
पूर्ण

अटल व्योम test_msr_platक्रमm_info_enabled(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
	काष्ठा ucall uc;

	set_msr_platक्रमm_info_enabled(vm, true);
	vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
			"Exit_reason other than KVM_EXIT_IO: %u (%s),\n",
			run->निकास_reason,
			निकास_reason_str(run->निकास_reason));
	get_ucall(vm, VCPU_ID, &uc);
	TEST_ASSERT(uc.cmd == UCALL_SYNC,
			"Received ucall other than UCALL_SYNC: %lu\n", uc.cmd);
	TEST_ASSERT((uc.args[1] & MSR_PLATFORM_INFO_MAX_TURBO_RATIO) ==
		MSR_PLATFORM_INFO_MAX_TURBO_RATIO,
		"Expected MSR_PLATFORM_INFO to have max turbo ratio mask: %i.",
		MSR_PLATFORM_INFO_MAX_TURBO_RATIO);
पूर्ण

अटल व्योम test_msr_platक्रमm_info_disabled(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);

	set_msr_platक्रमm_info_enabled(vm, false);
	vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_SHUTDOWN,
			"Exit_reason other than KVM_EXIT_SHUTDOWN: %u (%s)\n",
			run->निकास_reason,
			निकास_reason_str(run->निकास_reason));
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_vm *vm;
	पूर्णांक rv;
	uपूर्णांक64_t msr_platक्रमm_info;

	/* Tell मानक_निकास not to buffer its content */
	रखो_बफ(मानक_निकास, शून्य);

	rv = kvm_check_cap(KVM_CAP_MSR_PLATFORM_INFO);
	अगर (!rv) अणु
		prपूर्णांक_skip("KVM_CAP_MSR_PLATFORM_INFO not supported");
		निकास(KSFT_SKIP);
	पूर्ण

	vm = vm_create_शेष(VCPU_ID, 0, guest_code);

	msr_platक्रमm_info = vcpu_get_msr(vm, VCPU_ID, MSR_PLATFORM_INFO);
	vcpu_set_msr(vm, VCPU_ID, MSR_PLATFORM_INFO,
		msr_platक्रमm_info | MSR_PLATFORM_INFO_MAX_TURBO_RATIO);
	test_msr_platक्रमm_info_enabled(vm);
	test_msr_platक्रमm_info_disabled(vm);
	vcpu_set_msr(vm, VCPU_ID, MSR_PLATFORM_INFO, msr_platक्रमm_info);

	kvm_vm_मुक्त(vm);

	वापस 0;
पूर्ण
