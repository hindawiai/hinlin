<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Test क्रम s390x KVM_CAP_SYNC_REGS
 *
 * Based on the same test क्रम x86:
 * Copyright (C) 2018, Google LLC.
 *
 * Adaptions क्रम s390x:
 * Copyright (C) 2019, Red Hat, Inc.
 *
 * Test expected behavior of the KVM_CAP_SYNC_REGS functionality.
 */

#घोषणा _GNU_SOURCE /* क्रम program_invocation_लघु_name */
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "diag318_test_handler.h"

#घोषणा VCPU_ID 5

अटल व्योम guest_code(व्योम)
अणु
	/*
	 * We embed diag 501 here instead of करोing a ucall to aव्योम that
	 * the compiler has messed with r11 at the समय of the ucall.
	 */
	यंत्र अस्थिर (
		"0:	diag 0,0,0x501\n"
		"	ahi 11,1\n"
		"	j 0b\n"
	);
पूर्ण

#घोषणा REG_COMPARE(reg) \
	TEST_ASSERT(left->reg == right->reg, \
		    "Register " #reg \
		    " values did not match: 0x%llx, 0x%llx\n", \
		    left->reg, right->reg)

#घोषणा REG_COMPARE32(reg) \
	TEST_ASSERT(left->reg == right->reg, \
		    "Register " #reg \
		    " values did not match: 0x%x, 0x%x\n", \
		    left->reg, right->reg)


अटल व्योम compare_regs(काष्ठा kvm_regs *left, काष्ठा kvm_sync_regs *right)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		REG_COMPARE(gprs[i]);
पूर्ण

अटल व्योम compare_sregs(काष्ठा kvm_sregs *left, काष्ठा kvm_sync_regs *right)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		REG_COMPARE32(acrs[i]);

	क्रम (i = 0; i < 16; i++)
		REG_COMPARE(crs[i]);
पूर्ण

#अघोषित REG_COMPARE

#घोषणा TEST_SYNC_FIELDS   (KVM_SYNC_GPRS|KVM_SYNC_ACRS|KVM_SYNC_CRS|KVM_SYNC_DIAG318)
#घोषणा INVALID_SYNC_FIELD 0x80000000

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा kvm_vm *vm;
	काष्ठा kvm_run *run;
	काष्ठा kvm_regs regs;
	काष्ठा kvm_sregs sregs;
	पूर्णांक rv, cap;

	/* Tell मानक_निकास not to buffer its content */
	रखो_बफ(मानक_निकास, शून्य);

	cap = kvm_check_cap(KVM_CAP_SYNC_REGS);
	अगर (!cap) अणु
		prपूर्णांक_skip("CAP_SYNC_REGS not supported");
		निकास(KSFT_SKIP);
	पूर्ण

	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code);

	run = vcpu_state(vm, VCPU_ID);

	/* Request पढ़ोing invalid रेजिस्टर set from VCPU. */
	run->kvm_valid_regs = INVALID_SYNC_FIELD;
	rv = _vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(rv < 0 && त्रुटि_सं == EINVAL,
		    "Invalid kvm_valid_regs did not cause expected KVM_RUN error: %d\n",
		    rv);
	vcpu_state(vm, VCPU_ID)->kvm_valid_regs = 0;

	run->kvm_valid_regs = INVALID_SYNC_FIELD | TEST_SYNC_FIELDS;
	rv = _vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(rv < 0 && त्रुटि_सं == EINVAL,
		    "Invalid kvm_valid_regs did not cause expected KVM_RUN error: %d\n",
		    rv);
	vcpu_state(vm, VCPU_ID)->kvm_valid_regs = 0;

	/* Request setting invalid रेजिस्टर set पूर्णांकo VCPU. */
	run->kvm_dirty_regs = INVALID_SYNC_FIELD;
	rv = _vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(rv < 0 && त्रुटि_सं == EINVAL,
		    "Invalid kvm_dirty_regs did not cause expected KVM_RUN error: %d\n",
		    rv);
	vcpu_state(vm, VCPU_ID)->kvm_dirty_regs = 0;

	run->kvm_dirty_regs = INVALID_SYNC_FIELD | TEST_SYNC_FIELDS;
	rv = _vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(rv < 0 && त्रुटि_सं == EINVAL,
		    "Invalid kvm_dirty_regs did not cause expected KVM_RUN error: %d\n",
		    rv);
	vcpu_state(vm, VCPU_ID)->kvm_dirty_regs = 0;

	/* Request and verअगरy all valid रेजिस्टर sets. */
	run->kvm_valid_regs = TEST_SYNC_FIELDS;
	rv = _vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(rv == 0, "vcpu_run failed: %d\n", rv);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_S390_SIEIC,
		    "Unexpected exit reason: %u (%s)\n",
		    run->निकास_reason,
		    निकास_reason_str(run->निकास_reason));
	TEST_ASSERT(run->s390_sieic.icptcode == 4 &&
		    (run->s390_sieic.ipa >> 8) == 0x83 &&
		    (run->s390_sieic.ipb >> 16) == 0x501,
		    "Unexpected interception code: ic=%u, ipa=0x%x, ipb=0x%x\n",
		    run->s390_sieic.icptcode, run->s390_sieic.ipa,
		    run->s390_sieic.ipb);

	vcpu_regs_get(vm, VCPU_ID, &regs);
	compare_regs(&regs, &run->s.regs);

	vcpu_sregs_get(vm, VCPU_ID, &sregs);
	compare_sregs(&sregs, &run->s.regs);

	/* Set and verअगरy various रेजिस्टर values */
	run->s.regs.gprs[11] = 0xBAD1DEA;
	run->s.regs.acrs[0] = 1 << 11;

	run->kvm_valid_regs = TEST_SYNC_FIELDS;
	run->kvm_dirty_regs = KVM_SYNC_GPRS | KVM_SYNC_ACRS;

	अगर (get_diag318_info() > 0) अणु
		run->s.regs.diag318 = get_diag318_info();
		run->kvm_dirty_regs |= KVM_SYNC_DIAG318;
	पूर्ण

	rv = _vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(rv == 0, "vcpu_run failed: %d\n", rv);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_S390_SIEIC,
		    "Unexpected exit reason: %u (%s)\n",
		    run->निकास_reason,
		    निकास_reason_str(run->निकास_reason));
	TEST_ASSERT(run->s.regs.gprs[11] == 0xBAD1DEA + 1,
		    "r11 sync regs value incorrect 0x%llx.",
		    run->s.regs.gprs[11]);
	TEST_ASSERT(run->s.regs.acrs[0]  == 1 << 11,
		    "acr0 sync regs value incorrect 0x%x.",
		    run->s.regs.acrs[0]);
	TEST_ASSERT(run->s.regs.diag318 == get_diag318_info(),
		    "diag318 sync regs value incorrect 0x%llx.",
		    run->s.regs.diag318);

	vcpu_regs_get(vm, VCPU_ID, &regs);
	compare_regs(&regs, &run->s.regs);

	vcpu_sregs_get(vm, VCPU_ID, &sregs);
	compare_sregs(&sregs, &run->s.regs);

	/* Clear kvm_dirty_regs bits, verअगरy new s.regs values are
	 * overwritten with existing guest values.
	 */
	run->kvm_valid_regs = TEST_SYNC_FIELDS;
	run->kvm_dirty_regs = 0;
	run->s.regs.gprs[11] = 0xDEADBEEF;
	run->s.regs.diag318 = 0x4B1D;
	rv = _vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(rv == 0, "vcpu_run failed: %d\n", rv);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_S390_SIEIC,
		    "Unexpected exit reason: %u (%s)\n",
		    run->निकास_reason,
		    निकास_reason_str(run->निकास_reason));
	TEST_ASSERT(run->s.regs.gprs[11] != 0xDEADBEEF,
		    "r11 sync regs value incorrect 0x%llx.",
		    run->s.regs.gprs[11]);
	TEST_ASSERT(run->s.regs.diag318 != 0x4B1D,
		    "diag318 sync regs value incorrect 0x%llx.",
		    run->s.regs.diag318);

	kvm_vm_मुक्त(vm);

	वापस 0;
पूर्ण
