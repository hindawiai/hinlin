<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020, Google LLC.
 *
 * Tests क्रम निकासing पूर्णांकo userspace on रेजिस्टरed MSRs
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "vmx.h"

/* Forced emulation prefix, used to invoke the emulator unconditionally. */
#घोषणा KVM_FEP "ud2; .byte 'k', 'v', 'm';"
#घोषणा KVM_FEP_LENGTH 5
अटल पूर्णांक fep_available = 1;

#घोषणा VCPU_ID	      1
#घोषणा MSR_NON_EXISTENT 0x474f4f00

अटल u64 deny_bits = 0;
काष्ठा kvm_msr_filter filter_allow = अणु
	.flags = KVM_MSR_FILTER_DEFAULT_ALLOW,
	.ranges = अणु
		अणु
			.flags = KVM_MSR_FILTER_READ |
				 KVM_MSR_FILTER_WRITE,
			.nmsrs = 1,
			/* Test an MSR the kernel knows about. */
			.base = MSR_IA32_XSS,
			.biपंचांगap = (uपूर्णांक8_t*)&deny_bits,
		पूर्ण, अणु
			.flags = KVM_MSR_FILTER_READ |
				 KVM_MSR_FILTER_WRITE,
			.nmsrs = 1,
			/* Test an MSR the kernel करोesn't know about. */
			.base = MSR_IA32_FLUSH_CMD,
			.biपंचांगap = (uपूर्णांक8_t*)&deny_bits,
		पूर्ण, अणु
			.flags = KVM_MSR_FILTER_READ |
				 KVM_MSR_FILTER_WRITE,
			.nmsrs = 1,
			/* Test a fabricated MSR that no one knows about. */
			.base = MSR_NON_EXISTENT,
			.biपंचांगap = (uपूर्णांक8_t*)&deny_bits,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा kvm_msr_filter filter_fs = अणु
	.flags = KVM_MSR_FILTER_DEFAULT_ALLOW,
	.ranges = अणु
		अणु
			.flags = KVM_MSR_FILTER_READ,
			.nmsrs = 1,
			.base = MSR_FS_BASE,
			.biपंचांगap = (uपूर्णांक8_t*)&deny_bits,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा kvm_msr_filter filter_gs = अणु
	.flags = KVM_MSR_FILTER_DEFAULT_ALLOW,
	.ranges = अणु
		अणु
			.flags = KVM_MSR_FILTER_READ,
			.nmsrs = 1,
			.base = MSR_GS_BASE,
			.biपंचांगap = (uपूर्णांक8_t*)&deny_bits,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल uपूर्णांक64_t msr_non_existent_data;
अटल पूर्णांक guest_exception_count;
अटल u32 msr_पढ़ोs, msr_ग_लिखोs;

अटल u8 biपंचांगap_00000000[KVM_MSR_FILTER_MAX_BITMAP_SIZE];
अटल u8 biपंचांगap_00000000_ग_लिखो[KVM_MSR_FILTER_MAX_BITMAP_SIZE];
अटल u8 biपंचांगap_40000000[KVM_MSR_FILTER_MAX_BITMAP_SIZE];
अटल u8 biपंचांगap_c0000000[KVM_MSR_FILTER_MAX_BITMAP_SIZE];
अटल u8 biपंचांगap_c0000000_पढ़ो[KVM_MSR_FILTER_MAX_BITMAP_SIZE];
अटल u8 biपंचांगap_deadbeef[1] = अणु 0x1 पूर्ण;

अटल व्योम deny_msr(uपूर्णांक8_t *biपंचांगap, u32 msr)
अणु
	u32 idx = msr & (KVM_MSR_FILTER_MAX_BITMAP_SIZE - 1);

	biपंचांगap[idx / 8] &= ~(1 << (idx % 8));
पूर्ण

अटल व्योम prepare_biपंचांगaps(व्योम)
अणु
	स_रखो(biपंचांगap_00000000, 0xff, माप(biपंचांगap_00000000));
	स_रखो(biपंचांगap_00000000_ग_लिखो, 0xff, माप(biपंचांगap_00000000_ग_लिखो));
	स_रखो(biपंचांगap_40000000, 0xff, माप(biपंचांगap_40000000));
	स_रखो(biपंचांगap_c0000000, 0xff, माप(biपंचांगap_c0000000));
	स_रखो(biपंचांगap_c0000000_पढ़ो, 0xff, माप(biपंचांगap_c0000000_पढ़ो));

	deny_msr(biपंचांगap_00000000_ग_लिखो, MSR_IA32_POWER_CTL);
	deny_msr(biपंचांगap_c0000000_पढ़ो, MSR_SYSCALL_MASK);
	deny_msr(biपंचांगap_c0000000_पढ़ो, MSR_GS_BASE);
पूर्ण

काष्ठा kvm_msr_filter filter_deny = अणु
	.flags = KVM_MSR_FILTER_DEFAULT_DENY,
	.ranges = अणु
		अणु
			.flags = KVM_MSR_FILTER_READ,
			.base = 0x00000000,
			.nmsrs = KVM_MSR_FILTER_MAX_BITMAP_SIZE * BITS_PER_BYTE,
			.biपंचांगap = biपंचांगap_00000000,
		पूर्ण, अणु
			.flags = KVM_MSR_FILTER_WRITE,
			.base = 0x00000000,
			.nmsrs = KVM_MSR_FILTER_MAX_BITMAP_SIZE * BITS_PER_BYTE,
			.biपंचांगap = biपंचांगap_00000000_ग_लिखो,
		पूर्ण, अणु
			.flags = KVM_MSR_FILTER_READ | KVM_MSR_FILTER_WRITE,
			.base = 0x40000000,
			.nmsrs = KVM_MSR_FILTER_MAX_BITMAP_SIZE * BITS_PER_BYTE,
			.biपंचांगap = biपंचांगap_40000000,
		पूर्ण, अणु
			.flags = KVM_MSR_FILTER_READ,
			.base = 0xc0000000,
			.nmsrs = KVM_MSR_FILTER_MAX_BITMAP_SIZE * BITS_PER_BYTE,
			.biपंचांगap = biपंचांगap_c0000000_पढ़ो,
		पूर्ण, अणु
			.flags = KVM_MSR_FILTER_WRITE,
			.base = 0xc0000000,
			.nmsrs = KVM_MSR_FILTER_MAX_BITMAP_SIZE * BITS_PER_BYTE,
			.biपंचांगap = biपंचांगap_c0000000,
		पूर्ण, अणु
			.flags = KVM_MSR_FILTER_WRITE | KVM_MSR_FILTER_READ,
			.base = 0xdeadbeef,
			.nmsrs = 1,
			.biपंचांगap = biपंचांगap_deadbeef,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा kvm_msr_filter no_filter_deny = अणु
	.flags = KVM_MSR_FILTER_DEFAULT_ALLOW,
पूर्ण;

/*
 * Note: Force test_rdmsr() to not be अंतरभूतd to prevent the labels,
 * rdmsr_start and rdmsr_end, from being defined multiple बार.
 */
अटल noअंतरभूत uपूर्णांक64_t test_rdmsr(uपूर्णांक32_t msr)
अणु
	uपूर्णांक32_t a, d;

	guest_exception_count = 0;

	__यंत्र__ __अस्थिर__("rdmsr_start: rdmsr; rdmsr_end:" :
			"=a"(a), "=d"(d) : "c"(msr) : "memory");

	वापस a | ((uपूर्णांक64_t) d << 32);
पूर्ण

/*
 * Note: Force test_wrmsr() to not be अंतरभूतd to prevent the labels,
 * wrmsr_start and wrmsr_end, from being defined multiple बार.
 */
अटल noअंतरभूत व्योम test_wrmsr(uपूर्णांक32_t msr, uपूर्णांक64_t value)
अणु
	uपूर्णांक32_t a = value;
	uपूर्णांक32_t d = value >> 32;

	guest_exception_count = 0;

	__यंत्र__ __अस्थिर__("wrmsr_start: wrmsr; wrmsr_end:" ::
			"a"(a), "d"(d), "c"(msr) : "memory");
पूर्ण

बाह्य अक्षर rdmsr_start, rdmsr_end;
बाह्य अक्षर wrmsr_start, wrmsr_end;

/*
 * Note: Force test_em_rdmsr() to not be अंतरभूतd to prevent the labels,
 * rdmsr_start and rdmsr_end, from being defined multiple बार.
 */
अटल noअंतरभूत uपूर्णांक64_t test_em_rdmsr(uपूर्णांक32_t msr)
अणु
	uपूर्णांक32_t a, d;

	guest_exception_count = 0;

	__यंत्र__ __अस्थिर__(KVM_FEP "em_rdmsr_start: rdmsr; em_rdmsr_end:" :
			"=a"(a), "=d"(d) : "c"(msr) : "memory");

	वापस a | ((uपूर्णांक64_t) d << 32);
पूर्ण

/*
 * Note: Force test_em_wrmsr() to not be अंतरभूतd to prevent the labels,
 * wrmsr_start and wrmsr_end, from being defined multiple बार.
 */
अटल noअंतरभूत व्योम test_em_wrmsr(uपूर्णांक32_t msr, uपूर्णांक64_t value)
अणु
	uपूर्णांक32_t a = value;
	uपूर्णांक32_t d = value >> 32;

	guest_exception_count = 0;

	__यंत्र__ __अस्थिर__(KVM_FEP "em_wrmsr_start: wrmsr; em_wrmsr_end:" ::
			"a"(a), "d"(d), "c"(msr) : "memory");
पूर्ण

बाह्य अक्षर em_rdmsr_start, em_rdmsr_end;
बाह्य अक्षर em_wrmsr_start, em_wrmsr_end;

अटल व्योम guest_code_filter_allow(व्योम)
अणु
	uपूर्णांक64_t data;

	/*
	 * Test userspace पूर्णांकercepting rdmsr / wrmsr क्रम MSR_IA32_XSS.
	 *
	 * A GP is thrown अगर anything other than 0 is written to
	 * MSR_IA32_XSS.
	 */
	data = test_rdmsr(MSR_IA32_XSS);
	GUEST_ASSERT(data == 0);
	GUEST_ASSERT(guest_exception_count == 0);

	test_wrmsr(MSR_IA32_XSS, 0);
	GUEST_ASSERT(guest_exception_count == 0);

	test_wrmsr(MSR_IA32_XSS, 1);
	GUEST_ASSERT(guest_exception_count == 1);

	/*
	 * Test userspace पूर्णांकercepting rdmsr / wrmsr क्रम MSR_IA32_FLUSH_CMD.
	 *
	 * A GP is thrown अगर MSR_IA32_FLUSH_CMD is पढ़ो
	 * from or अगर a value other than 1 is written to it.
	 */
	test_rdmsr(MSR_IA32_FLUSH_CMD);
	GUEST_ASSERT(guest_exception_count == 1);

	test_wrmsr(MSR_IA32_FLUSH_CMD, 0);
	GUEST_ASSERT(guest_exception_count == 1);

	test_wrmsr(MSR_IA32_FLUSH_CMD, 1);
	GUEST_ASSERT(guest_exception_count == 0);

	/*
	 * Test userspace पूर्णांकercepting rdmsr / wrmsr क्रम MSR_NON_EXISTENT.
	 *
	 * Test that a fabricated MSR can pass through the kernel
	 * and be handled in userspace.
	 */
	test_wrmsr(MSR_NON_EXISTENT, 2);
	GUEST_ASSERT(guest_exception_count == 0);

	data = test_rdmsr(MSR_NON_EXISTENT);
	GUEST_ASSERT(data == 2);
	GUEST_ASSERT(guest_exception_count == 0);

	/*
	 * Test to see अगर the inकाष्ठाion emulator is available (ie: the module
	 * parameter 'kvm.force_emulation_prefix=1' is set).  This inकाष्ठाion
	 * will #UD अगर it isn't available.
	 */
	__यंत्र__ __अस्थिर__(KVM_FEP "nop");

	अगर (fep_available) अणु
		/* Let userspace know we aren't करोne. */
		GUEST_SYNC(0);

		/*
		 * Now run the same tests with the inकाष्ठाion emulator.
		 */
		data = test_em_rdmsr(MSR_IA32_XSS);
		GUEST_ASSERT(data == 0);
		GUEST_ASSERT(guest_exception_count == 0);
		test_em_wrmsr(MSR_IA32_XSS, 0);
		GUEST_ASSERT(guest_exception_count == 0);
		test_em_wrmsr(MSR_IA32_XSS, 1);
		GUEST_ASSERT(guest_exception_count == 1);

		test_em_rdmsr(MSR_IA32_FLUSH_CMD);
		GUEST_ASSERT(guest_exception_count == 1);
		test_em_wrmsr(MSR_IA32_FLUSH_CMD, 0);
		GUEST_ASSERT(guest_exception_count == 1);
		test_em_wrmsr(MSR_IA32_FLUSH_CMD, 1);
		GUEST_ASSERT(guest_exception_count == 0);

		test_em_wrmsr(MSR_NON_EXISTENT, 2);
		GUEST_ASSERT(guest_exception_count == 0);
		data = test_em_rdmsr(MSR_NON_EXISTENT);
		GUEST_ASSERT(data == 2);
		GUEST_ASSERT(guest_exception_count == 0);
	पूर्ण

	GUEST_DONE();
पूर्ण

अटल व्योम guest_msr_calls(bool trapped)
अणु
	/* This goes पूर्णांकo the in-kernel emulation */
	wrmsr(MSR_SYSCALL_MASK, 0);

	अगर (trapped) अणु
		/* This goes पूर्णांकo user space emulation */
		GUEST_ASSERT(rdmsr(MSR_SYSCALL_MASK) == MSR_SYSCALL_MASK);
		GUEST_ASSERT(rdmsr(MSR_GS_BASE) == MSR_GS_BASE);
	पूर्ण अन्यथा अणु
		GUEST_ASSERT(rdmsr(MSR_SYSCALL_MASK) != MSR_SYSCALL_MASK);
		GUEST_ASSERT(rdmsr(MSR_GS_BASE) != MSR_GS_BASE);
	पूर्ण

	/* If trapped == true, this goes पूर्णांकo user space emulation */
	wrmsr(MSR_IA32_POWER_CTL, 0x1234);

	/* This goes पूर्णांकo the in-kernel emulation */
	rdmsr(MSR_IA32_POWER_CTL);

	/* Invalid MSR, should always be handled by user space निकास */
	GUEST_ASSERT(rdmsr(0xdeadbeef) == 0xdeadbeef);
	wrmsr(0xdeadbeef, 0x1234);
पूर्ण

अटल व्योम guest_code_filter_deny(व्योम)
अणु
	guest_msr_calls(true);

	/*
	 * Disable msr filtering, so that the kernel
	 * handles everything in the next round
	 */
	GUEST_SYNC(0);

	guest_msr_calls(false);

	GUEST_DONE();
पूर्ण

अटल व्योम guest_code_permission_biपंचांगap(व्योम)
अणु
	uपूर्णांक64_t data;

	data = test_rdmsr(MSR_FS_BASE);
	GUEST_ASSERT(data == MSR_FS_BASE);
	data = test_rdmsr(MSR_GS_BASE);
	GUEST_ASSERT(data != MSR_GS_BASE);

	/* Let userspace know to चयन the filter */
	GUEST_SYNC(0);

	data = test_rdmsr(MSR_FS_BASE);
	GUEST_ASSERT(data != MSR_FS_BASE);
	data = test_rdmsr(MSR_GS_BASE);
	GUEST_ASSERT(data == MSR_GS_BASE);

	GUEST_DONE();
पूर्ण

अटल व्योम __guest_gp_handler(काष्ठा ex_regs *regs,
			       अक्षर *r_start, अक्षर *r_end,
			       अक्षर *w_start, अक्षर *w_end)
अणु
	अगर (regs->rip == (uपूर्णांकptr_t)r_start) अणु
		regs->rip = (uपूर्णांकptr_t)r_end;
		regs->rax = 0;
		regs->rdx = 0;
	पूर्ण अन्यथा अगर (regs->rip == (uपूर्णांकptr_t)w_start) अणु
		regs->rip = (uपूर्णांकptr_t)w_end;
	पूर्ण अन्यथा अणु
		GUEST_ASSERT(!"RIP is at an unknown location!");
	पूर्ण

	++guest_exception_count;
पूर्ण

अटल व्योम guest_gp_handler(काष्ठा ex_regs *regs)
अणु
	__guest_gp_handler(regs, &rdmsr_start, &rdmsr_end,
			   &wrmsr_start, &wrmsr_end);
पूर्ण

अटल व्योम guest_fep_gp_handler(काष्ठा ex_regs *regs)
अणु
	__guest_gp_handler(regs, &em_rdmsr_start, &em_rdmsr_end,
			   &em_wrmsr_start, &em_wrmsr_end);
पूर्ण

अटल व्योम guest_ud_handler(काष्ठा ex_regs *regs)
अणु
	fep_available = 0;
	regs->rip += KVM_FEP_LENGTH;
पूर्ण

अटल व्योम run_guest(काष्ठा kvm_vm *vm)
अणु
	पूर्णांक rc;

	rc = _vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(rc == 0, "vcpu_run failed: %d\n", rc);
पूर्ण

अटल व्योम check_क्रम_guest_निश्चित(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
	काष्ठा ucall uc;

	अगर (run->निकास_reason == KVM_EXIT_IO &&
		get_ucall(vm, VCPU_ID, &uc) == UCALL_ABORT) अणु
			TEST_FAIL("%s at %s:%ld", (स्थिर अक्षर *)uc.args[0],
				__खाता__, uc.args[1]);
	पूर्ण
पूर्ण

अटल व्योम process_rdmsr(काष्ठा kvm_vm *vm, uपूर्णांक32_t msr_index)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);

	check_क्रम_guest_निश्चित(vm);

	TEST_ASSERT(run->निकास_reason == KVM_EXIT_X86_RDMSR,
		    "Unexpected exit reason: %u (%s),\n",
		    run->निकास_reason,
		    निकास_reason_str(run->निकास_reason));
	TEST_ASSERT(run->msr.index == msr_index,
			"Unexpected msr (0x%04x), expected 0x%04x",
			run->msr.index, msr_index);

	चयन (run->msr.index) अणु
	हाल MSR_IA32_XSS:
		run->msr.data = 0;
		अवरोध;
	हाल MSR_IA32_FLUSH_CMD:
		run->msr.error = 1;
		अवरोध;
	हाल MSR_NON_EXISTENT:
		run->msr.data = msr_non_existent_data;
		अवरोध;
	हाल MSR_FS_BASE:
		run->msr.data = MSR_FS_BASE;
		अवरोध;
	हाल MSR_GS_BASE:
		run->msr.data = MSR_GS_BASE;
		अवरोध;
	शेष:
		TEST_ASSERT(false, "Unexpected MSR: 0x%04x", run->msr.index);
	पूर्ण
पूर्ण

अटल व्योम process_wrmsr(काष्ठा kvm_vm *vm, uपूर्णांक32_t msr_index)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);

	check_क्रम_guest_निश्चित(vm);

	TEST_ASSERT(run->निकास_reason == KVM_EXIT_X86_WRMSR,
		    "Unexpected exit reason: %u (%s),\n",
		    run->निकास_reason,
		    निकास_reason_str(run->निकास_reason));
	TEST_ASSERT(run->msr.index == msr_index,
			"Unexpected msr (0x%04x), expected 0x%04x",
			run->msr.index, msr_index);

	चयन (run->msr.index) अणु
	हाल MSR_IA32_XSS:
		अगर (run->msr.data != 0)
			run->msr.error = 1;
		अवरोध;
	हाल MSR_IA32_FLUSH_CMD:
		अगर (run->msr.data != 1)
			run->msr.error = 1;
		अवरोध;
	हाल MSR_NON_EXISTENT:
		msr_non_existent_data = run->msr.data;
		अवरोध;
	शेष:
		TEST_ASSERT(false, "Unexpected MSR: 0x%04x", run->msr.index);
	पूर्ण
पूर्ण

अटल व्योम process_ucall_करोne(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
	काष्ठा ucall uc;

	check_क्रम_guest_निश्चित(vm);

	TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
		    "Unexpected exit reason: %u (%s)",
		    run->निकास_reason,
		    निकास_reason_str(run->निकास_reason));

	TEST_ASSERT(get_ucall(vm, VCPU_ID, &uc) == UCALL_DONE,
		    "Unexpected ucall command: %lu, expected UCALL_DONE (%d)",
		    uc.cmd, UCALL_DONE);
पूर्ण

अटल uपूर्णांक64_t process_ucall(काष्ठा kvm_vm *vm)
अणु
	काष्ठा kvm_run *run = vcpu_state(vm, VCPU_ID);
	काष्ठा ucall uc = अणुपूर्ण;

	check_क्रम_guest_निश्चित(vm);

	TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO,
		    "Unexpected exit reason: %u (%s)",
		    run->निकास_reason,
		    निकास_reason_str(run->निकास_reason));

	चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
	हाल UCALL_SYNC:
		अवरोध;
	हाल UCALL_ABORT:
		check_क्रम_guest_निश्चित(vm);
		अवरोध;
	हाल UCALL_DONE:
		process_ucall_करोne(vm);
		अवरोध;
	शेष:
		TEST_ASSERT(false, "Unexpected ucall");
	पूर्ण

	वापस uc.cmd;
पूर्ण

अटल व्योम run_guest_then_process_rdmsr(काष्ठा kvm_vm *vm, uपूर्णांक32_t msr_index)
अणु
	run_guest(vm);
	process_rdmsr(vm, msr_index);
पूर्ण

अटल व्योम run_guest_then_process_wrmsr(काष्ठा kvm_vm *vm, uपूर्णांक32_t msr_index)
अणु
	run_guest(vm);
	process_wrmsr(vm, msr_index);
पूर्ण

अटल uपूर्णांक64_t run_guest_then_process_ucall(काष्ठा kvm_vm *vm)
अणु
	run_guest(vm);
	वापस process_ucall(vm);
पूर्ण

अटल व्योम run_guest_then_process_ucall_करोne(काष्ठा kvm_vm *vm)
अणु
	run_guest(vm);
	process_ucall_करोne(vm);
पूर्ण

अटल व्योम test_msr_filter_allow(व्योम) अणु
	काष्ठा kvm_enable_cap cap = अणु
		.cap = KVM_CAP_X86_USER_SPACE_MSR,
		.args[0] = KVM_MSR_EXIT_REASON_FILTER,
	पूर्ण;
	काष्ठा kvm_vm *vm;
	पूर्णांक rc;

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code_filter_allow);
	vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());

	rc = kvm_check_cap(KVM_CAP_X86_USER_SPACE_MSR);
	TEST_ASSERT(rc, "KVM_CAP_X86_USER_SPACE_MSR is available");
	vm_enable_cap(vm, &cap);

	rc = kvm_check_cap(KVM_CAP_X86_MSR_FILTER);
	TEST_ASSERT(rc, "KVM_CAP_X86_MSR_FILTER is available");

	vm_ioctl(vm, KVM_X86_SET_MSR_FILTER, &filter_allow);

	vm_init_descriptor_tables(vm);
	vcpu_init_descriptor_tables(vm, VCPU_ID);

	vm_handle_exception(vm, GP_VECTOR, guest_gp_handler);

	/* Process guest code userspace निकासs. */
	run_guest_then_process_rdmsr(vm, MSR_IA32_XSS);
	run_guest_then_process_wrmsr(vm, MSR_IA32_XSS);
	run_guest_then_process_wrmsr(vm, MSR_IA32_XSS);

	run_guest_then_process_rdmsr(vm, MSR_IA32_FLUSH_CMD);
	run_guest_then_process_wrmsr(vm, MSR_IA32_FLUSH_CMD);
	run_guest_then_process_wrmsr(vm, MSR_IA32_FLUSH_CMD);

	run_guest_then_process_wrmsr(vm, MSR_NON_EXISTENT);
	run_guest_then_process_rdmsr(vm, MSR_NON_EXISTENT);

	vm_handle_exception(vm, UD_VECTOR, guest_ud_handler);
	run_guest(vm);
	vm_handle_exception(vm, UD_VECTOR, शून्य);

	अगर (process_ucall(vm) != UCALL_DONE) अणु
		vm_handle_exception(vm, GP_VECTOR, guest_fep_gp_handler);

		/* Process emulated rdmsr and wrmsr inकाष्ठाions. */
		run_guest_then_process_rdmsr(vm, MSR_IA32_XSS);
		run_guest_then_process_wrmsr(vm, MSR_IA32_XSS);
		run_guest_then_process_wrmsr(vm, MSR_IA32_XSS);

		run_guest_then_process_rdmsr(vm, MSR_IA32_FLUSH_CMD);
		run_guest_then_process_wrmsr(vm, MSR_IA32_FLUSH_CMD);
		run_guest_then_process_wrmsr(vm, MSR_IA32_FLUSH_CMD);

		run_guest_then_process_wrmsr(vm, MSR_NON_EXISTENT);
		run_guest_then_process_rdmsr(vm, MSR_NON_EXISTENT);

		/* Confirm the guest completed without issues. */
		run_guest_then_process_ucall_करोne(vm);
	पूर्ण अन्यथा अणु
		म_लिखो("To run the instruction emulated tests set the module parameter 'kvm.force_emulation_prefix=1'\n");
	पूर्ण

	kvm_vm_मुक्त(vm);
पूर्ण

अटल पूर्णांक handle_ucall(काष्ठा kvm_vm *vm)
अणु
	काष्ठा ucall uc;

	चयन (get_ucall(vm, VCPU_ID, &uc)) अणु
	हाल UCALL_ABORT:
		TEST_FAIL("Guest assertion not met");
		अवरोध;
	हाल UCALL_SYNC:
		vm_ioctl(vm, KVM_X86_SET_MSR_FILTER, &no_filter_deny);
		अवरोध;
	हाल UCALL_DONE:
		वापस 1;
	शेष:
		TEST_FAIL("Unknown ucall %lu", uc.cmd);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम handle_rdmsr(काष्ठा kvm_run *run)
अणु
	run->msr.data = run->msr.index;
	msr_पढ़ोs++;

	अगर (run->msr.index == MSR_SYSCALL_MASK ||
	    run->msr.index == MSR_GS_BASE) अणु
		TEST_ASSERT(run->msr.reason == KVM_MSR_EXIT_REASON_FILTER,
			    "MSR read trap w/o access fault");
	पूर्ण

	अगर (run->msr.index == 0xdeadbeef) अणु
		TEST_ASSERT(run->msr.reason == KVM_MSR_EXIT_REASON_UNKNOWN,
			    "MSR deadbeef read trap w/o inval fault");
	पूर्ण
पूर्ण

अटल व्योम handle_wrmsr(काष्ठा kvm_run *run)
अणु
	/* ignore */
	msr_ग_लिखोs++;

	अगर (run->msr.index == MSR_IA32_POWER_CTL) अणु
		TEST_ASSERT(run->msr.data == 0x1234,
			    "MSR data for MSR_IA32_POWER_CTL incorrect");
		TEST_ASSERT(run->msr.reason == KVM_MSR_EXIT_REASON_FILTER,
			    "MSR_IA32_POWER_CTL trap w/o access fault");
	पूर्ण

	अगर (run->msr.index == 0xdeadbeef) अणु
		TEST_ASSERT(run->msr.data == 0x1234,
			    "MSR data for deadbeef incorrect");
		TEST_ASSERT(run->msr.reason == KVM_MSR_EXIT_REASON_UNKNOWN,
			    "deadbeef trap w/o inval fault");
	पूर्ण
पूर्ण

अटल व्योम test_msr_filter_deny(व्योम) अणु
	काष्ठा kvm_enable_cap cap = अणु
		.cap = KVM_CAP_X86_USER_SPACE_MSR,
		.args[0] = KVM_MSR_EXIT_REASON_INVAL |
			   KVM_MSR_EXIT_REASON_UNKNOWN |
			   KVM_MSR_EXIT_REASON_FILTER,
	पूर्ण;
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	पूर्णांक rc;

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code_filter_deny);
	vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());
	run = vcpu_state(vm, VCPU_ID);

	rc = kvm_check_cap(KVM_CAP_X86_USER_SPACE_MSR);
	TEST_ASSERT(rc, "KVM_CAP_X86_USER_SPACE_MSR is available");
	vm_enable_cap(vm, &cap);

	rc = kvm_check_cap(KVM_CAP_X86_MSR_FILTER);
	TEST_ASSERT(rc, "KVM_CAP_X86_MSR_FILTER is available");

	prepare_biपंचांगaps();
	vm_ioctl(vm, KVM_X86_SET_MSR_FILTER, &filter_deny);

	जबतक (1) अणु
		rc = _vcpu_run(vm, VCPU_ID);

		TEST_ASSERT(rc == 0, "vcpu_run failed: %d\n", rc);

		चयन (run->निकास_reason) अणु
		हाल KVM_EXIT_X86_RDMSR:
			handle_rdmsr(run);
			अवरोध;
		हाल KVM_EXIT_X86_WRMSR:
			handle_wrmsr(run);
			अवरोध;
		हाल KVM_EXIT_IO:
			अगर (handle_ucall(vm))
				जाओ करोne;
			अवरोध;
		पूर्ण

	पूर्ण

करोne:
	TEST_ASSERT(msr_पढ़ोs == 4, "Handled 4 rdmsr in user space");
	TEST_ASSERT(msr_ग_लिखोs == 3, "Handled 3 wrmsr in user space");

	kvm_vm_मुक्त(vm);
पूर्ण

अटल व्योम test_msr_permission_biपंचांगap(व्योम) अणु
	काष्ठा kvm_enable_cap cap = अणु
		.cap = KVM_CAP_X86_USER_SPACE_MSR,
		.args[0] = KVM_MSR_EXIT_REASON_FILTER,
	पूर्ण;
	काष्ठा kvm_vm *vm;
	पूर्णांक rc;

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code_permission_biपंचांगap);
	vcpu_set_cpuid(vm, VCPU_ID, kvm_get_supported_cpuid());

	rc = kvm_check_cap(KVM_CAP_X86_USER_SPACE_MSR);
	TEST_ASSERT(rc, "KVM_CAP_X86_USER_SPACE_MSR is available");
	vm_enable_cap(vm, &cap);

	rc = kvm_check_cap(KVM_CAP_X86_MSR_FILTER);
	TEST_ASSERT(rc, "KVM_CAP_X86_MSR_FILTER is available");

	vm_ioctl(vm, KVM_X86_SET_MSR_FILTER, &filter_fs);
	run_guest_then_process_rdmsr(vm, MSR_FS_BASE);
	TEST_ASSERT(run_guest_then_process_ucall(vm) == UCALL_SYNC, "Expected ucall state to be UCALL_SYNC.");
	vm_ioctl(vm, KVM_X86_SET_MSR_FILTER, &filter_gs);
	run_guest_then_process_rdmsr(vm, MSR_GS_BASE);
	run_guest_then_process_ucall_करोne(vm);

	kvm_vm_मुक्त(vm);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	/* Tell मानक_निकास not to buffer its content */
	रखो_बफ(मानक_निकास, शून्य);

	test_msr_filter_allow();

	test_msr_filter_deny();

	test_msr_permission_biपंचांगap();

	वापस 0;
पूर्ण
