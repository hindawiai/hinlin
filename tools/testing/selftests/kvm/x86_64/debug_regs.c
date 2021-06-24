<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KVM guest debug रेजिस्टर tests
 *
 * Copyright (C) 2020, Red Hat, Inc.
 */
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा VCPU_ID 0

#घोषणा DR6_BD		(1 << 13)
#घोषणा DR7_GD		(1 << 13)

/* For testing data access debug BP */
uपूर्णांक32_t guest_value;

बाह्य अचिन्हित अक्षर sw_bp, hw_bp, ग_लिखो_data, ss_start, bd_start;

अटल व्योम guest_code(व्योम)
अणु
	/*
	 * Software BP tests.
	 *
	 * NOTE: sw_bp need to be beक्रमe the cmd here, because पूर्णांक3 is an
	 * exception rather than a normal trap क्रम KVM_SET_GUEST_DEBUG (we
	 * capture it using the vcpu exception biपंचांगap).
	 */
	यंत्र अस्थिर("sw_bp: int3");

	/* Hardware inकाष्ठाion BP test */
	यंत्र अस्थिर("hw_bp: nop");

	/* Hardware data BP test */
	यंत्र अस्थिर("mov $1234,%%rax;\n\t"
		     "mov %%rax,%0;\n\t write_data:"
		     : "=m" (guest_value) : : "rax");

	/* Single step test, covers 2 basic inकाष्ठाions and 2 emulated */
	यंत्र अस्थिर("ss_start: "
		     "xor %%eax,%%eax\n\t"
		     "cpuid\n\t"
		     "movl $0x1a0,%%ecx\n\t"
		     "rdmsr\n\t"
		     : : : "eax", "ebx", "ecx", "edx");

	/* DR6.BD test */
	यंत्र अस्थिर("bd_start: mov %%dr0, %%rax" : : : "rax");
	GUEST_DONE();
पूर्ण

#घोषणा  CLEAR_DEBUG()  स_रखो(&debug, 0, माप(debug))
#घोषणा  APPLY_DEBUG()  vcpu_set_guest_debug(vm, VCPU_ID, &debug)
#घोषणा  CAST_TO_RIP(v)  ((अचिन्हित दीर्घ दीर्घ)&(v))
#घोषणा  SET_RIP(v)  करो अणु				\
		vcpu_regs_get(vm, VCPU_ID, &regs);	\
		regs.rip = (v);				\
		vcpu_regs_set(vm, VCPU_ID, &regs);	\
	पूर्ण जबतक (0)
#घोषणा  MOVE_RIP(v)  SET_RIP(regs.rip + (v));

पूर्णांक मुख्य(व्योम)
अणु
	काष्ठा kvm_guest_debug debug;
	अचिन्हित दीर्घ दीर्घ target_dr6, target_rip;
	काष्ठा kvm_regs regs;
	काष्ठा kvm_run *run;
	काष्ठा kvm_vm *vm;
	काष्ठा ucall uc;
	uपूर्णांक64_t cmd;
	पूर्णांक i;
	/* Inकाष्ठाion lengths starting at ss_start */
	पूर्णांक ss_size[4] = अणु
		2,		/* xor */
		2,		/* cpuid */
		5,		/* mov */
		2,		/* rdmsr */
	पूर्ण;

	अगर (!kvm_check_cap(KVM_CAP_SET_GUEST_DEBUG)) अणु
		prपूर्णांक_skip("KVM_CAP_SET_GUEST_DEBUG not supported");
		वापस 0;
	पूर्ण

	vm = vm_create_शेष(VCPU_ID, 0, guest_code);
	run = vcpu_state(vm, VCPU_ID);

	/* Test software BPs - पूर्णांक3 */
	CLEAR_DEBUG();
	debug.control = KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_SW_BP;
	APPLY_DEBUG();
	vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_DEBUG &&
		    run->debug.arch.exception == BP_VECTOR &&
		    run->debug.arch.pc == CAST_TO_RIP(sw_bp),
		    "INT3: exit %d exception %d rip 0x%llx (should be 0x%llx)",
		    run->निकास_reason, run->debug.arch.exception,
		    run->debug.arch.pc, CAST_TO_RIP(sw_bp));
	MOVE_RIP(1);

	/* Test inकाष्ठाion HW BP over DR[0-3] */
	क्रम (i = 0; i < 4; i++) अणु
		CLEAR_DEBUG();
		debug.control = KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_HW_BP;
		debug.arch.debugreg[i] = CAST_TO_RIP(hw_bp);
		debug.arch.debugreg[7] = 0x400 | (1UL << (2*i+1));
		APPLY_DEBUG();
		vcpu_run(vm, VCPU_ID);
		target_dr6 = 0xffff0ff0 | (1UL << i);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_DEBUG &&
			    run->debug.arch.exception == DB_VECTOR &&
			    run->debug.arch.pc == CAST_TO_RIP(hw_bp) &&
			    run->debug.arch.dr6 == target_dr6,
			    "INS_HW_BP (DR%d): exit %d exception %d rip 0x%llx "
			    "(should be 0x%llx) dr6 0x%llx (should be 0x%llx)",
			    i, run->निकास_reason, run->debug.arch.exception,
			    run->debug.arch.pc, CAST_TO_RIP(hw_bp),
			    run->debug.arch.dr6, target_dr6);
	पूर्ण
	/* Skip "nop" */
	MOVE_RIP(1);

	/* Test data access HW BP over DR[0-3] */
	क्रम (i = 0; i < 4; i++) अणु
		CLEAR_DEBUG();
		debug.control = KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_HW_BP;
		debug.arch.debugreg[i] = CAST_TO_RIP(guest_value);
		debug.arch.debugreg[7] = 0x00000400 | (1UL << (2*i+1)) |
		    (0x000d0000UL << (4*i));
		APPLY_DEBUG();
		vcpu_run(vm, VCPU_ID);
		target_dr6 = 0xffff0ff0 | (1UL << i);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_DEBUG &&
			    run->debug.arch.exception == DB_VECTOR &&
			    run->debug.arch.pc == CAST_TO_RIP(ग_लिखो_data) &&
			    run->debug.arch.dr6 == target_dr6,
			    "DATA_HW_BP (DR%d): exit %d exception %d rip 0x%llx "
			    "(should be 0x%llx) dr6 0x%llx (should be 0x%llx)",
			    i, run->निकास_reason, run->debug.arch.exception,
			    run->debug.arch.pc, CAST_TO_RIP(ग_लिखो_data),
			    run->debug.arch.dr6, target_dr6);
		/* Rollback the 4-bytes "mov" */
		MOVE_RIP(-7);
	पूर्ण
	/* Skip the 4-bytes "mov" */
	MOVE_RIP(7);

	/* Test single step */
	target_rip = CAST_TO_RIP(ss_start);
	target_dr6 = 0xffff4ff0ULL;
	vcpu_regs_get(vm, VCPU_ID, &regs);
	क्रम (i = 0; i < (माप(ss_size) / माप(ss_size[0])); i++) अणु
		target_rip += ss_size[i];
		CLEAR_DEBUG();
		debug.control = KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_SINGLESTEP;
		debug.arch.debugreg[7] = 0x00000400;
		APPLY_DEBUG();
		vcpu_run(vm, VCPU_ID);
		TEST_ASSERT(run->निकास_reason == KVM_EXIT_DEBUG &&
			    run->debug.arch.exception == DB_VECTOR &&
			    run->debug.arch.pc == target_rip &&
			    run->debug.arch.dr6 == target_dr6,
			    "SINGLE_STEP[%d]: exit %d exception %d rip 0x%llx "
			    "(should be 0x%llx) dr6 0x%llx (should be 0x%llx)",
			    i, run->निकास_reason, run->debug.arch.exception,
			    run->debug.arch.pc, target_rip, run->debug.arch.dr6,
			    target_dr6);
	पूर्ण

	/* Finally test global disable */
	CLEAR_DEBUG();
	debug.control = KVM_GUESTDBG_ENABLE | KVM_GUESTDBG_USE_HW_BP;
	debug.arch.debugreg[7] = 0x400 | DR7_GD;
	APPLY_DEBUG();
	vcpu_run(vm, VCPU_ID);
	target_dr6 = 0xffff0ff0 | DR6_BD;
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_DEBUG &&
		    run->debug.arch.exception == DB_VECTOR &&
		    run->debug.arch.pc == CAST_TO_RIP(bd_start) &&
		    run->debug.arch.dr6 == target_dr6,
			    "DR7.GD: exit %d exception %d rip 0x%llx "
			    "(should be 0x%llx) dr6 0x%llx (should be 0x%llx)",
			    run->निकास_reason, run->debug.arch.exception,
			    run->debug.arch.pc, target_rip, run->debug.arch.dr6,
			    target_dr6);

	/* Disable all debug controls, run to the end */
	CLEAR_DEBUG();
	APPLY_DEBUG();

	vcpu_run(vm, VCPU_ID);
	TEST_ASSERT(run->निकास_reason == KVM_EXIT_IO, "KVM_EXIT_IO");
	cmd = get_ucall(vm, VCPU_ID, &uc);
	TEST_ASSERT(cmd == UCALL_DONE, "UCALL_DONE");

	kvm_vm_मुक्त(vm);

	वापस 0;
पूर्ण
