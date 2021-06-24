<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Test handler क्रम the s390x DIAGNOSE 0x0318 inकाष्ठाion.
 *
 * Copyright (C) 2020, IBM
 */

#समावेश "test_util.h"
#समावेश "kvm_util.h"

#घोषणा VCPU_ID	6

#घोषणा ICPT_INSTRUCTION	0x04
#घोषणा IPA0_DIAG		0x8300

अटल व्योम guest_code(व्योम)
अणु
	uपूर्णांक64_t diag318_info = 0x12345678;

	यंत्र अस्थिर ("diag %0,0,0x318\n" : : "d" (diag318_info));
पूर्ण

/*
 * The DIAGNOSE 0x0318 inकाष्ठाion call must be handled via userspace. As such,
 * we create an ad-hoc VM here to handle the inकाष्ठाion then extract the
 * necessary data. It is up to the caller to decide what to करो with that data.
 */
अटल uपूर्णांक64_t diag318_handler(व्योम)
अणु
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	uपूर्णांक64_t reg;
	uपूर्णांक64_t diag318_info;

	vm = vm_create_शेष(VCPU_ID, 0, guest_code);
	vcpu_run(vm, VCPU_ID);
	run = vcpu_state(vm, VCPU_ID);

	TEST_ASSERT(run->निकास_reason == KVM_EXIT_S390_SIEIC,
		    "DIAGNOSE 0x0318 instruction was not intercepted");
	TEST_ASSERT(run->s390_sieic.icptcode == ICPT_INSTRUCTION,
		    "Unexpected intercept code: 0x%x", run->s390_sieic.icptcode);
	TEST_ASSERT((run->s390_sieic.ipa & 0xff00) == IPA0_DIAG,
		    "Unexpected IPA0 code: 0x%x", (run->s390_sieic.ipa & 0xff00));

	reg = (run->s390_sieic.ipa & 0x00f0) >> 4;
	diag318_info = run->s.regs.gprs[reg];

	TEST_ASSERT(diag318_info != 0, "DIAGNOSE 0x0318 info not set");

	kvm_vm_मुक्त(vm);

	वापस diag318_info;
पूर्ण

uपूर्णांक64_t get_diag318_info(व्योम)
अणु
	अटल uपूर्णांक64_t diag318_info;
	अटल bool prपूर्णांकed_skip;

	/*
	 * If KVM करोes not support diag318, then वापस 0 to
	 * ensure tests करो not अवरोध.
	 */
	अगर (!kvm_check_cap(KVM_CAP_S390_DIAG318)) अणु
		अगर (!prपूर्णांकed_skip) अणु
			ख_लिखो(मानक_निकास, "KVM_CAP_S390_DIAG318 not supported. "
				"Skipping diag318 test.\n");
			prपूर्णांकed_skip = true;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * If a test has previously requested the diag318 info,
	 * then करोn't bother spinning up a temporary VM again.
	 */
	अगर (!diag318_info)
		diag318_info = diag318_handler();

	वापस diag318_info;
पूर्ण
