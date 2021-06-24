<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Test क्रम s390x CPU resets
 *
 * Copyright (C) 2020, IBM
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/ioctl.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"

#घोषणा VCPU_ID 3
#घोषणा LOCAL_IRQS 32

काष्ठा kvm_s390_irq buf[VCPU_ID + LOCAL_IRQS];

काष्ठा kvm_vm *vm;
काष्ठा kvm_run *run;
काष्ठा kvm_sync_regs *sync_regs;
अटल uपूर्णांक8_t regs_null[512];

अटल व्योम guest_code_initial(व्योम)
अणु
	/* set several CRs to "safe" value */
	अचिन्हित दीर्घ cr2_59 = 0x10;	/* enable guarded storage */
	अचिन्हित दीर्घ cr8_63 = 0x1;	/* monitor mask = 1 */
	अचिन्हित दीर्घ cr10 = 1;		/* PER START */
	अचिन्हित दीर्घ cr11 = -1;	/* PER END */


	/* Dirty रेजिस्टरs */
	यंत्र अस्थिर (
		"	lghi	2,0x11\n"	/* Round toward 0 */
		"	sfpc	2\n"		/* set fpc to !=0 */
		"	lctlg	2,2,%0\n"
		"	lctlg	8,8,%1\n"
		"	lctlg	10,10,%2\n"
		"	lctlg	11,11,%3\n"
		/* now clobber some general purpose regs */
		"	llihh	0,0xffff\n"
		"	llihl	1,0x5555\n"
		"	llilh	2,0xaaaa\n"
		"	llill	3,0x0000\n"
		/* now clobber a भग्नing poपूर्णांक reg */
		"	lghi	4,0x1\n"
		"	cdgbr	0,4\n"
		/* now clobber an access reg */
		"	sar	9,4\n"
		/* We embed diag 501 here to control रेजिस्टर content */
		"	diag 0,0,0x501\n"
		:
		: "m" (cr2_59), "m" (cr8_63), "m" (cr10), "m" (cr11)
		/* no clobber list as this should not वापस */
		);
पूर्ण

अटल व्योम test_one_reg(uपूर्णांक64_t id, uपूर्णांक64_t value)
अणु
	काष्ठा kvm_one_reg reg;
	uपूर्णांक64_t eval_reg;

	reg.addr = (uपूर्णांकptr_t)&eval_reg;
	reg.id = id;
	vcpu_get_reg(vm, VCPU_ID, &reg);
	TEST_ASSERT(eval_reg == value, "value == 0x%lx", value);
पूर्ण

अटल व्योम निश्चित_noirq(व्योम)
अणु
	काष्ठा kvm_s390_irq_state irq_state;
	पूर्णांक irqs;

	irq_state.len = माप(buf);
	irq_state.buf = (अचिन्हित दीर्घ)buf;
	irqs = _vcpu_ioctl(vm, VCPU_ID, KVM_S390_GET_IRQ_STATE, &irq_state);
	/*
	 * irqs contains the number of retrieved पूर्णांकerrupts. Any पूर्णांकerrupt
	 * (notably, the emergency call पूर्णांकerrupt we have injected) should
	 * be cleared by the resets, so this should be 0.
	 */
	TEST_ASSERT(irqs >= 0, "Could not fetch IRQs: errno %d\n", त्रुटि_सं);
	TEST_ASSERT(!irqs, "IRQ pending");
पूर्ण

अटल व्योम निश्चित_clear(व्योम)
अणु
	काष्ठा kvm_sregs sregs;
	काष्ठा kvm_regs regs;
	काष्ठा kvm_fpu fpu;

	vcpu_regs_get(vm, VCPU_ID, &regs);
	TEST_ASSERT(!स_भेद(&regs.gprs, regs_null, माप(regs.gprs)), "grs == 0");

	vcpu_sregs_get(vm, VCPU_ID, &sregs);
	TEST_ASSERT(!स_भेद(&sregs.acrs, regs_null, माप(sregs.acrs)), "acrs == 0");

	vcpu_fpu_get(vm, VCPU_ID, &fpu);
	TEST_ASSERT(!स_भेद(&fpu.fprs, regs_null, माप(fpu.fprs)), "fprs == 0");

	/* sync regs */
	TEST_ASSERT(!स_भेद(sync_regs->gprs, regs_null, माप(sync_regs->gprs)),
		    "gprs0-15 == 0 (sync_regs)");

	TEST_ASSERT(!स_भेद(sync_regs->acrs, regs_null, माप(sync_regs->acrs)),
		    "acrs0-15 == 0 (sync_regs)");

	TEST_ASSERT(!स_भेद(sync_regs->vrs, regs_null, माप(sync_regs->vrs)),
		    "vrs0-15 == 0 (sync_regs)");
पूर्ण

अटल व्योम निश्चित_initial_noclear(व्योम)
अणु
	TEST_ASSERT(sync_regs->gprs[0] == 0xffff000000000000UL,
		    "gpr0 == 0xffff000000000000 (sync_regs)");
	TEST_ASSERT(sync_regs->gprs[1] == 0x0000555500000000UL,
		    "gpr1 == 0x0000555500000000 (sync_regs)");
	TEST_ASSERT(sync_regs->gprs[2] == 0x00000000aaaa0000UL,
		    "gpr2 == 0x00000000aaaa0000 (sync_regs)");
	TEST_ASSERT(sync_regs->gprs[3] == 0x0000000000000000UL,
		    "gpr3 == 0x0000000000000000 (sync_regs)");
	TEST_ASSERT(sync_regs->fprs[0] == 0x3ff0000000000000UL,
		    "fpr0 == 0f1 (sync_regs)");
	TEST_ASSERT(sync_regs->acrs[9] == 1, "ar9 == 1 (sync_regs)");
पूर्ण

अटल व्योम निश्चित_initial(व्योम)
अणु
	काष्ठा kvm_sregs sregs;
	काष्ठा kvm_fpu fpu;

	/* KVM_GET_SREGS */
	vcpu_sregs_get(vm, VCPU_ID, &sregs);
	TEST_ASSERT(sregs.crs[0] == 0xE0UL, "cr0 == 0xE0 (KVM_GET_SREGS)");
	TEST_ASSERT(sregs.crs[14] == 0xC2000000UL,
		    "cr14 == 0xC2000000 (KVM_GET_SREGS)");
	TEST_ASSERT(!स_भेद(&sregs.crs[1], regs_null, माप(sregs.crs[1]) * 12),
		    "cr1-13 == 0 (KVM_GET_SREGS)");
	TEST_ASSERT(sregs.crs[15] == 0, "cr15 == 0 (KVM_GET_SREGS)");

	/* sync regs */
	TEST_ASSERT(sync_regs->crs[0] == 0xE0UL, "cr0 == 0xE0 (sync_regs)");
	TEST_ASSERT(sync_regs->crs[14] == 0xC2000000UL,
		    "cr14 == 0xC2000000 (sync_regs)");
	TEST_ASSERT(!स_भेद(&sync_regs->crs[1], regs_null, 8 * 12),
		    "cr1-13 == 0 (sync_regs)");
	TEST_ASSERT(sync_regs->crs[15] == 0, "cr15 == 0 (sync_regs)");
	TEST_ASSERT(sync_regs->fpc == 0, "fpc == 0 (sync_regs)");
	TEST_ASSERT(sync_regs->todpr == 0, "todpr == 0 (sync_regs)");
	TEST_ASSERT(sync_regs->cpuपंचांग == 0, "cputm == 0 (sync_regs)");
	TEST_ASSERT(sync_regs->ckc == 0, "ckc == 0 (sync_regs)");
	TEST_ASSERT(sync_regs->pp == 0, "pp == 0 (sync_regs)");
	TEST_ASSERT(sync_regs->gbea == 1, "gbea == 1 (sync_regs)");

	/* kvm_run */
	TEST_ASSERT(run->psw_addr == 0, "psw_addr == 0 (kvm_run)");
	TEST_ASSERT(run->psw_mask == 0, "psw_mask == 0 (kvm_run)");

	vcpu_fpu_get(vm, VCPU_ID, &fpu);
	TEST_ASSERT(!fpu.fpc, "fpc == 0");

	test_one_reg(KVM_REG_S390_GBEA, 1);
	test_one_reg(KVM_REG_S390_PP, 0);
	test_one_reg(KVM_REG_S390_TODPR, 0);
	test_one_reg(KVM_REG_S390_CPU_TIMER, 0);
	test_one_reg(KVM_REG_S390_CLOCK_COMP, 0);
पूर्ण

अटल व्योम निश्चित_normal_noclear(व्योम)
अणु
	TEST_ASSERT(sync_regs->crs[2] == 0x10, "cr2 == 10 (sync_regs)");
	TEST_ASSERT(sync_regs->crs[8] == 1, "cr10 == 1 (sync_regs)");
	TEST_ASSERT(sync_regs->crs[10] == 1, "cr10 == 1 (sync_regs)");
	TEST_ASSERT(sync_regs->crs[11] == -1, "cr11 == -1 (sync_regs)");
पूर्ण

अटल व्योम निश्चित_normal(व्योम)
अणु
	test_one_reg(KVM_REG_S390_PFTOKEN, KVM_S390_PFAULT_TOKEN_INVALID);
	TEST_ASSERT(sync_regs->pft == KVM_S390_PFAULT_TOKEN_INVALID,
			"pft == 0xff.....  (sync_regs)");
	निश्चित_noirq();
पूर्ण

अटल व्योम inject_irq(पूर्णांक cpu_id)
अणु
	काष्ठा kvm_s390_irq_state irq_state;
	काष्ठा kvm_s390_irq *irq = &buf[0];
	पूर्णांक irqs;

	/* Inject IRQ */
	irq_state.len = माप(काष्ठा kvm_s390_irq);
	irq_state.buf = (अचिन्हित दीर्घ)buf;
	irq->type = KVM_S390_INT_EMERGENCY;
	irq->u.emerg.code = cpu_id;
	irqs = _vcpu_ioctl(vm, cpu_id, KVM_S390_SET_IRQ_STATE, &irq_state);
	TEST_ASSERT(irqs >= 0, "Error injecting EMERGENCY IRQ errno %d\n", त्रुटि_सं);
पूर्ण

अटल व्योम test_normal(व्योम)
अणु
	pr_info("Testing normal reset\n");
	/* Create VM */
	vm = vm_create_शेष(VCPU_ID, 0, guest_code_initial);
	run = vcpu_state(vm, VCPU_ID);
	sync_regs = &run->s.regs;

	vcpu_run(vm, VCPU_ID);

	inject_irq(VCPU_ID);

	vcpu_ioctl(vm, VCPU_ID, KVM_S390_NORMAL_RESET, 0);

	/* must clears */
	निश्चित_normal();
	/* must not clears */
	निश्चित_normal_noclear();
	निश्चित_initial_noclear();

	kvm_vm_मुक्त(vm);
पूर्ण

अटल व्योम test_initial(व्योम)
अणु
	pr_info("Testing initial reset\n");
	vm = vm_create_शेष(VCPU_ID, 0, guest_code_initial);
	run = vcpu_state(vm, VCPU_ID);
	sync_regs = &run->s.regs;

	vcpu_run(vm, VCPU_ID);

	inject_irq(VCPU_ID);

	vcpu_ioctl(vm, VCPU_ID, KVM_S390_INITIAL_RESET, 0);

	/* must clears */
	निश्चित_normal();
	निश्चित_initial();
	/* must not clears */
	निश्चित_initial_noclear();

	kvm_vm_मुक्त(vm);
पूर्ण

अटल व्योम test_clear(व्योम)
अणु
	pr_info("Testing clear reset\n");
	vm = vm_create_शेष(VCPU_ID, 0, guest_code_initial);
	run = vcpu_state(vm, VCPU_ID);
	sync_regs = &run->s.regs;

	vcpu_run(vm, VCPU_ID);

	inject_irq(VCPU_ID);

	vcpu_ioctl(vm, VCPU_ID, KVM_S390_CLEAR_RESET, 0);

	/* must clears */
	निश्चित_normal();
	निश्चित_initial();
	निश्चित_clear();

	kvm_vm_मुक्त(vm);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	रखो_बफ(मानक_निकास, शून्य);	/* Tell मानक_निकास not to buffer its content */

	test_initial();
	अगर (kvm_check_cap(KVM_CAP_S390_VCPU_RESETS)) अणु
		test_normal();
		test_clear();
	पूर्ण
	वापस 0;
पूर्ण
