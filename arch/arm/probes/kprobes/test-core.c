<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/kernel/kprobes-test.c
 *
 * Copyright (C) 2011 Jon Medhurst <tixy@yxit.co.uk>.
 */

/*
 * This file contains test code क्रम ARM kprobes.
 *
 * The top level function run_all_tests() executes tests क्रम all of the
 * supported inकाष्ठाion sets: ARM, 16-bit Thumb, and 32-bit Thumb. These tests
 * fall पूर्णांकo two categories; run_api_tests() checks basic functionality of the
 * kprobes API, and run_test_हालs() is a comprehensive test क्रम kprobes
 * inकाष्ठाion decoding and simulation.
 *
 * run_test_हालs() first checks the kprobes decoding table क्रम self consistency
 * (using table_test()) then executes a series of test हालs क्रम each of the CPU
 * inकाष्ठाion क्रमms. coverage_start() and coverage_end() are used to verअगरy
 * that these test हालs cover all of the possible combinations of inकाष्ठाions
 * described by the kprobes decoding tables.
 *
 * The inभागidual test हालs are in kprobes-test-arm.c and kprobes-test-thumb.c
 * which use the macros defined in kprobes-test.h. The rest of this
 * करोcumentation will describe the operation of the framework used by these
 * test हालs.
 */

/*
 * TESTING METHODOLOGY
 * -------------------
 *
 * The methoकरोlogy used to test an ARM inकाष्ठाion 'test_insn' is to use
 * अंतरभूत assembler like:
 *
 * test_beक्रमe: nop
 * test_हाल:	test_insn
 * test_after:	nop
 *
 * When the test हाल is run a kprobe is placed of each nop. The
 * post-handler of the test_beक्रमe probe is used to modअगरy the saved CPU
 * रेजिस्टर context to that which we require क्रम the test हाल. The
 * pre-handler of the of the test_after probe saves a copy of the CPU
 * रेजिस्टर context. In this way we can execute test_insn with a specअगरic
 * रेजिस्टर context and see the results afterwards.
 *
 * To actually test the kprobes inकाष्ठाion emulation we perक्रमm the above
 * step a second समय but with an additional kprobe on the test_हाल
 * inकाष्ठाion itself. If the emulation is accurate then the results seen
 * by the test_after probe will be identical to the first run which didn't
 * have a probe on test_हाल.
 *
 * Each test हाल is run several बार with a variety of variations in the
 * flags value of stored in CPSR, and क्रम Thumb code, dअगरferent ITState.
 *
 * For inकाष्ठाions which can modअगरy PC, a second test_after probe is used
 * like this:
 *
 * test_beक्रमe: nop
 * test_हाल:	test_insn
 * test_after:	nop
 *		b test_करोne
 * test_after2: nop
 * test_करोne:
 *
 * The test हाल is स्थिरructed such that test_insn branches to
 * test_after2, or, अगर testing a conditional inकाष्ठाion, it may just
 * जारी to test_after. The probes inserted at both locations let us
 * determine which happened. A similar approach is used क्रम testing
 * backwards branches...
 *
 *		b test_beक्रमe
 *		b test_करोne  @ helps to cope with off by 1 branches
 * test_after2: nop
 *		b test_करोne
 * test_beक्रमe: nop
 * test_हाल:	test_insn
 * test_after:	nop
 * test_करोne:
 *
 * The macros used to generate the assembler inकाष्ठाions describe above
 * are TEST_INSTRUCTION, TEST_BRANCH_F (branch क्रमwards) and TEST_BRANCH_B
 * (branch backwards). In these, the local variables numbered 1, 50, 2 and
 * 99 represent: test_beक्रमe, test_हाल, test_after2 and test_करोne.
 *
 * FRAMEWORK
 * ---------
 *
 * Each test हाल is wrapped between the pair of macros TESTCASE_START and
 * TESTCASE_END. As well as perक्रमming the अंतरभूत assembler boilerplate,
 * these call out to the kprobes_test_हाल_start() and
 * kprobes_test_हाल_end() functions which drive the execution of the test
 * हाल. The specअगरic arguments to use क्रम each test हाल are stored as
 * अंतरभूत data स्थिरructed using the various TEST_ARG_* macros. Putting
 * this all together, a simple test हाल may look like:
 *
 *	TESTCASE_START("Testing mov r0, r7")
 *	TEST_ARG_REG(7, 0x12345678) // Set r7=0x12345678
 *	TEST_ARG_END("")
 *	TEST_INSTRUCTION("mov r0, r7")
 *	TESTCASE_END
 *
 * Note, in practice the single convenience macro TEST_R would be used क्रम this
 * instead.
 *
 * The above would expand to assembler looking something like:
 *
 *	@ TESTCASE_START
 *	bl	__kprobes_test_हाल_start
 *	.pushsection .rodata
 *	"10:
 *	.ascii "mov r0, r7"	@ text title क्रम test हाल
 *	.byte	0
 *	.popsection
 *	@ start of अंतरभूत data...
 *	.word	10b		@ poपूर्णांकer to title in .rodata section
 *
 *	@ TEST_ARG_REG
 *	.byte	ARG_TYPE_REG
 *	.byte	7
 *	.लघु	0
 *	.word	0x1234567
 *
 *	@ TEST_ARG_END
 *	.byte	ARG_TYPE_END
 *	.byte	TEST_ISA	@ flags, including ISA being tested
 *	.लघु	50f-0f		@ offset of 'test_before'
 *	.लघु	2f-0f		@ offset of 'test_after2' (अगर relevent)
 *	.लघु	99f-0f		@ offset of 'test_done'
 *	@ start of test हाल code...
 *	0:
 *	.code	TEST_ISA	@ चयन to ISA being tested
 *
 *	@ TEST_INSTRUCTION
 *	50:	nop		@ location क्रम 'test_before' probe
 *	1:	mov r0, r7	@ the test हाल inकाष्ठाion 'test_insn'
 *		nop		@ location क्रम 'test_after' probe
 *
 *	// TESTCASE_END
 *	2:
 *	99:	bl __kprobes_test_हाल_end_##TEST_ISA
 *	.code	NONMAL_ISA
 *
 * When the above is execute the following happens...
 *
 * __kprobes_test_हाल_start() is an assembler wrapper which sets up space
 * क्रम a stack buffer and calls the C function kprobes_test_हाल_start().
 * This C function will करो some initial processing of the अंतरभूत data and
 * setup some global state. It then inserts the test_beक्रमe and test_after
 * kprobes and वापसs a value which causes the assembler wrapper to jump
 * to the start of the test हाल code, (local label '0').
 *
 * When the test हाल code executes, the test_beक्रमe probe will be hit and
 * test_beक्रमe_post_handler will call setup_test_context(). This fills the
 * stack buffer and CPU रेजिस्टरs with a test pattern and then processes
 * the test हाल arguments. In our example there is one TEST_ARG_REG which
 * indicates that R7 should be loaded with the value 0x12345678.
 *
 * When the test_beक्रमe probe ends, the test हाल जारीs and executes
 * the "mov r0, r7" inकाष्ठाion. It then hits the test_after probe and the
 * pre-handler क्रम this (test_after_pre_handler) will save a copy of the
 * CPU रेजिस्टर context. This should now have R0 holding the same value as
 * R7.
 *
 * Finally we get to the call to __kprobes_test_हाल_end_अणु32,16पूर्ण. This is
 * an assembler wrapper which चयनes back to the ISA used by the test
 * code and calls the C function kprobes_test_हाल_end().
 *
 * For each run through the test हाल, test_हाल_run_count is incremented
 * by one. For even runs, kprobes_test_हाल_end() saves a copy of the
 * रेजिस्टर and stack buffer contents from the test हाल just run. It then
 * inserts a kprobe on the test हाल inकाष्ठाion 'test_insn' and वापसs a
 * value to cause the test हाल code to be re-run.
 *
 * For odd numbered runs, kprobes_test_हाल_end() compares the रेजिस्टर and
 * stack buffer contents to those that were saved on the previous even
 * numbered run (the one without the kprobe on test_insn). These should be
 * the same अगर the kprobe inकाष्ठाion simulation routine is correct.
 *
 * The pair of test हाल runs is repeated with dअगरferent combinations of
 * flag values in CPSR and, क्रम Thumb, dअगरferent ITState. This is
 * controlled by test_context_cpsr().
 *
 * BUILDING TEST CASES
 * -------------------
 *
 *
 * As an aid to building test हालs, the stack buffer is initialised with
 * some special values:
 *
 *   [SP+13*4]	Contains SP+120. This can be used to test inकाष्ठाions
 *		which load a value पूर्णांकo SP.
 *
 *   [SP+15*4]	When testing branching inकाष्ठाions using TEST_BRANCH_अणुF,Bपूर्ण,
 *		this holds the target address of the branch, 'test_after2'.
 *		This can be used to test inकाष्ठाions which load a PC value
 *		from memory.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/bug.h>
#समावेश <यंत्र/opcodes.h>

#समावेश "core.h"
#समावेश "test-core.h"
#समावेश "../decode-arm.h"
#समावेश "../decode-thumb.h"


#घोषणा BENCHMARKING	1


/*
 * Test basic API
 */

अटल bool test_regs_ok;
अटल पूर्णांक test_func_instance;
अटल पूर्णांक pre_handler_called;
अटल पूर्णांक post_handler_called;
अटल पूर्णांक kretprobe_handler_called;
अटल पूर्णांक tests_failed;

#घोषणा FUNC_ARG1 0x12345678
#घोषणा FUNC_ARG2 0xabcdef


#अगर_अघोषित CONFIG_THUMB2_KERNEL

#घोषणा RET(reg)	"mov	pc, "#reg

दीर्घ arm_func(दीर्घ r0, दीर्घ r1);

अटल व्योम __used __naked __arm_kprobes_test_func(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		".arm					\n\t"
		".type arm_func, %%function		\n\t"
		"arm_func:				\n\t"
		"adds	r0, r0, r1			\n\t"
		"mov	pc, lr				\n\t"
		".code "NORMAL_ISA	 /* Back to Thumb अगर necessary */
		: : : "r0", "r1", "cc"
	);
पूर्ण

#अन्यथा /* CONFIG_THUMB2_KERNEL */

#घोषणा RET(reg)	"bx	"#reg

दीर्घ thumb16_func(दीर्घ r0, दीर्घ r1);
दीर्घ thumb32even_func(दीर्घ r0, दीर्घ r1);
दीर्घ thumb32odd_func(दीर्घ r0, दीर्घ r1);

अटल व्योम __used __naked __thumb_kprobes_test_funcs(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		".type thumb16_func, %%function		\n\t"
		"thumb16_func:				\n\t"
		"adds.n	r0, r0, r1			\n\t"
		"bx	lr				\n\t"

		".align					\n\t"
		".type thumb32even_func, %%function	\n\t"
		"thumb32even_func:			\n\t"
		"adds.w	r0, r0, r1			\n\t"
		"bx	lr				\n\t"

		".align					\n\t"
		"nop.n					\n\t"
		".type thumb32odd_func, %%function	\n\t"
		"thumb32odd_func:			\n\t"
		"adds.w	r0, r0, r1			\n\t"
		"bx	lr				\n\t"

		: : : "r0", "r1", "cc"
	);
पूर्ण

#पूर्ण_अगर /* CONFIG_THUMB2_KERNEL */


अटल पूर्णांक call_test_func(दीर्घ (*func)(दीर्घ, दीर्घ), bool check_test_regs)
अणु
	दीर्घ ret;

	++test_func_instance;
	test_regs_ok = false;

	ret = (*func)(FUNC_ARG1, FUNC_ARG2);
	अगर (ret != FUNC_ARG1 + FUNC_ARG2) अणु
		pr_err("FAIL: call_test_func: func returned %lx\n", ret);
		वापस false;
	पूर्ण

	अगर (check_test_regs && !test_regs_ok) अणु
		pr_err("FAIL: test regs not OK\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक __kprobes pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	pre_handler_called = test_func_instance;
	अगर (regs->ARM_r0 == FUNC_ARG1 && regs->ARM_r1 == FUNC_ARG2)
		test_regs_ok = true;
	वापस 0;
पूर्ण

अटल व्योम __kprobes post_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
				अचिन्हित दीर्घ flags)
अणु
	post_handler_called = test_func_instance;
	अगर (regs->ARM_r0 != FUNC_ARG1 + FUNC_ARG2 || regs->ARM_r1 != FUNC_ARG2)
		test_regs_ok = false;
पूर्ण

अटल काष्ठा kprobe the_kprobe = अणु
	.addr		= 0,
	.pre_handler	= pre_handler,
	.post_handler	= post_handler
पूर्ण;

अटल पूर्णांक test_kprobe(दीर्घ (*func)(दीर्घ, दीर्घ))
अणु
	पूर्णांक ret;

	the_kprobe.addr = (kprobe_opcode_t *)func;
	ret = रेजिस्टर_kprobe(&the_kprobe);
	अगर (ret < 0) अणु
		pr_err("FAIL: register_kprobe failed with %d\n", ret);
		वापस ret;
	पूर्ण

	ret = call_test_func(func, true);

	unरेजिस्टर_kprobe(&the_kprobe);
	the_kprobe.flags = 0; /* Clear disable flag to allow reuse */

	अगर (!ret)
		वापस -EINVAL;
	अगर (pre_handler_called != test_func_instance) अणु
		pr_err("FAIL: kprobe pre_handler not called\n");
		वापस -EINVAL;
	पूर्ण
	अगर (post_handler_called != test_func_instance) अणु
		pr_err("FAIL: kprobe post_handler not called\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!call_test_func(func, false))
		वापस -EINVAL;
	अगर (pre_handler_called == test_func_instance ||
				post_handler_called == test_func_instance) अणु
		pr_err("FAIL: probe called after unregistering\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __kprobes
kretprobe_handler(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	kretprobe_handler_called = test_func_instance;
	अगर (regs_वापस_value(regs) == FUNC_ARG1 + FUNC_ARG2)
		test_regs_ok = true;
	वापस 0;
पूर्ण

अटल काष्ठा kretprobe the_kretprobe = अणु
	.handler	= kretprobe_handler,
पूर्ण;

अटल पूर्णांक test_kretprobe(दीर्घ (*func)(दीर्घ, दीर्घ))
अणु
	पूर्णांक ret;

	the_kretprobe.kp.addr = (kprobe_opcode_t *)func;
	ret = रेजिस्टर_kretprobe(&the_kretprobe);
	अगर (ret < 0) अणु
		pr_err("FAIL: register_kretprobe failed with %d\n", ret);
		वापस ret;
	पूर्ण

	ret = call_test_func(func, true);

	unरेजिस्टर_kretprobe(&the_kretprobe);
	the_kretprobe.kp.flags = 0; /* Clear disable flag to allow reuse */

	अगर (!ret)
		वापस -EINVAL;
	अगर (kretprobe_handler_called != test_func_instance) अणु
		pr_err("FAIL: kretprobe handler not called\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!call_test_func(func, false))
		वापस -EINVAL;
	अगर (kretprobe_handler_called == test_func_instance) अणु
		pr_err("FAIL: kretprobe called after unregistering\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक run_api_tests(दीर्घ (*func)(दीर्घ, दीर्घ))
अणु
	पूर्णांक ret;

	pr_info("    kprobe\n");
	ret = test_kprobe(func);
	अगर (ret < 0)
		वापस ret;

	pr_info("    kretprobe\n");
	ret = test_kretprobe(func);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण


/*
 * Benchmarking
 */

#अगर BENCHMARKING

अटल व्योम __naked benchmark_nop(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"nop		\n\t"
		RET(lr)"	\n\t"
	);
पूर्ण

#अगर_घोषित CONFIG_THUMB2_KERNEL
#घोषणा wide ".w"
#अन्यथा
#घोषणा wide
#पूर्ण_अगर

अटल व्योम __naked benchmark_pushpop1(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"stmdb"wide"	sp!, {r3-r11,lr}  \n\t"
		"ldmia"wide"	sp!, {r3-r11,pc}"
	);
पूर्ण

अटल व्योम __naked benchmark_pushpop2(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"stmdb"wide"	sp!, {r0-r8,lr}  \n\t"
		"ldmia"wide"	sp!, {r0-r8,pc}"
	);
पूर्ण

अटल व्योम __naked benchmark_pushpop3(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"stmdb"wide"	sp!, {r4,lr}  \n\t"
		"ldmia"wide"	sp!, {r4,pc}"
	);
पूर्ण

अटल व्योम __naked benchmark_pushpop4(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"stmdb"wide"	sp!, {r0,lr}  \n\t"
		"ldmia"wide"	sp!, {r0,pc}"
	);
पूर्ण


#अगर_घोषित CONFIG_THUMB2_KERNEL

अटल व्योम __naked benchmark_pushpop_thumb(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"push.n	{r0-r7,lr}  \n\t"
		"pop.n	{r0-r7,pc}"
	);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __kprobes
benchmark_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक benchmark(व्योम(*fn)(व्योम))
अणु
	अचिन्हित n, i, t, t0;

	क्रम (n = 1000; ; n *= 2) अणु
		t0 = sched_घड़ी();
		क्रम (i = n; i > 0; --i)
			fn();
		t = sched_घड़ी() - t0;
		अगर (t >= 250000000)
			अवरोध; /* Stop once we took more than 0.25 seconds */
	पूर्ण
	वापस t / n; /* Time क्रम one iteration in nanoseconds */
पूर्ण;

अटल पूर्णांक kprobe_benchmark(व्योम(*fn)(व्योम), अचिन्हित offset)
अणु
	काष्ठा kprobe k = अणु
		.addr		= (kprobe_opcode_t *)((uपूर्णांकptr_t)fn + offset),
		.pre_handler	= benchmark_pre_handler,
	पूर्ण;

	पूर्णांक ret = रेजिस्टर_kprobe(&k);
	अगर (ret < 0) अणु
		pr_err("FAIL: register_kprobe failed with %d\n", ret);
		वापस ret;
	पूर्ण

	ret = benchmark(fn);

	unरेजिस्टर_kprobe(&k);
	वापस ret;
पूर्ण;

काष्ठा benchmarks अणु
	व्योम		(*fn)(व्योम);
	अचिन्हित	offset;
	स्थिर अक्षर	*title;
पूर्ण;

अटल पूर्णांक run_benchmarks(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा benchmarks list[] = अणु
		अणु&benchmark_nop, 0, "nop"पूर्ण,
		/*
		 * benchmark_pushpopअणु1,3पूर्ण will have the optimised
		 * inकाष्ठाion emulation, whilst benchmark_pushpopअणु2,4पूर्ण will
		 * be the equivalent unoptimised inकाष्ठाions.
		 */
		अणु&benchmark_pushpop1, 0, "stmdb	sp!, {r3-r11,lr}"पूर्ण,
		अणु&benchmark_pushpop1, 4, "ldmia	sp!, {r3-r11,pc}"पूर्ण,
		अणु&benchmark_pushpop2, 0, "stmdb	sp!, {r0-r8,lr}"पूर्ण,
		अणु&benchmark_pushpop2, 4, "ldmia	sp!, {r0-r8,pc}"पूर्ण,
		अणु&benchmark_pushpop3, 0, "stmdb	sp!, {r4,lr}"पूर्ण,
		अणु&benchmark_pushpop3, 4, "ldmia	sp!, {r4,pc}"पूर्ण,
		अणु&benchmark_pushpop4, 0, "stmdb	sp!, {r0,lr}"पूर्ण,
		अणु&benchmark_pushpop4, 4, "ldmia	sp!, {r0,pc}"पूर्ण,
#अगर_घोषित CONFIG_THUMB2_KERNEL
		अणु&benchmark_pushpop_thumb, 0, "push.n	{r0-r7,lr}"पूर्ण,
		अणु&benchmark_pushpop_thumb, 2, "pop.n	{r0-r7,pc}"पूर्ण,
#पूर्ण_अगर
		अणु0पूर्ण
	पूर्ण;

	काष्ठा benchmarks *b;
	क्रम (b = list; b->fn; ++b) अणु
		ret = kprobe_benchmark(b->fn, b->offset);
		अगर (ret < 0)
			वापस ret;
		pr_info("    %dns for kprobe %s\n", ret, b->title);
	पूर्ण

	pr_info("\n");
	वापस 0;
पूर्ण

#पूर्ण_अगर /* BENCHMARKING */


/*
 * Decoding table self-consistency tests
 */

अटल स्थिर पूर्णांक decode_काष्ठा_sizes[NUM_DECODE_TYPES] = अणु
	[DECODE_TYPE_TABLE]	= माप(काष्ठा decode_table),
	[DECODE_TYPE_CUSTOM]	= माप(काष्ठा decode_custom),
	[DECODE_TYPE_SIMULATE]	= माप(काष्ठा decode_simulate),
	[DECODE_TYPE_EMULATE]	= माप(काष्ठा decode_emulate),
	[DECODE_TYPE_OR]	= माप(काष्ठा decode_or),
	[DECODE_TYPE_REJECT]	= माप(काष्ठा decode_reject)
पूर्ण;

अटल पूर्णांक table_iter(स्थिर जोड़ decode_item *table,
			पूर्णांक (*fn)(स्थिर काष्ठा decode_header *, व्योम *),
			व्योम *args)
अणु
	स्थिर काष्ठा decode_header *h = (काष्ठा decode_header *)table;
	पूर्णांक result;

	क्रम (;;) अणु
		क्रमागत decode_type type = h->type_regs.bits & DECODE_TYPE_MASK;

		अगर (type == DECODE_TYPE_END)
			वापस 0;

		result = fn(h, args);
		अगर (result)
			वापस result;

		h = (काष्ठा decode_header *)
			((uपूर्णांकptr_t)h + decode_काष्ठा_sizes[type]);

	पूर्ण
पूर्ण

अटल पूर्णांक table_test_fail(स्थिर काष्ठा decode_header *h, स्थिर अक्षर* message)
अणु

	pr_err("FAIL: kprobes test failure \"%s\" (mask %08x, value %08x)\n",
					message, h->mask.bits, h->value.bits);
	वापस -EINVAL;
पूर्ण

काष्ठा table_test_args अणु
	स्थिर जोड़ decode_item *root_table;
	u32			parent_mask;
	u32			parent_value;
पूर्ण;

अटल पूर्णांक table_test_fn(स्थिर काष्ठा decode_header *h, व्योम *args)
अणु
	काष्ठा table_test_args *a = (काष्ठा table_test_args *)args;
	क्रमागत decode_type type = h->type_regs.bits & DECODE_TYPE_MASK;

	अगर (h->value.bits & ~h->mask.bits)
		वापस table_test_fail(h, "Match value has bits not in mask");

	अगर ((h->mask.bits & a->parent_mask) != a->parent_mask)
		वापस table_test_fail(h, "Mask has bits not in parent mask");

	अगर ((h->value.bits ^ a->parent_value) & a->parent_mask)
		वापस table_test_fail(h, "Value is inconsistent with parent");

	अगर (type == DECODE_TYPE_TABLE) अणु
		काष्ठा decode_table *d = (काष्ठा decode_table *)h;
		काष्ठा table_test_args args2 = *a;
		args2.parent_mask = h->mask.bits;
		args2.parent_value = h->value.bits;
		वापस table_iter(d->table.table, table_test_fn, &args2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक table_test(स्थिर जोड़ decode_item *table)
अणु
	काष्ठा table_test_args args = अणु
		.root_table	= table,
		.parent_mask	= 0,
		.parent_value	= 0
	पूर्ण;
	वापस table_iter(args.root_table, table_test_fn, &args);
पूर्ण


/*
 * Decoding table test coverage analysis
 *
 * coverage_start() builds a coverage_table which contains a list of
 * coverage_entry's to match each entry in the specअगरied kprobes inकाष्ठाion
 * decoding table.
 *
 * When test हालs are run, coverage_add() is called to process each हाल.
 * This looks up the corresponding entry in the coverage_table and sets it as
 * being matched, as well as clearing the regs flag appropriate क्रम the test.
 *
 * After all test हालs have been run, coverage_end() is called to check that
 * all entries in coverage_table have been matched and that all regs flags are
 * cleared. I.e. that all possible combinations of inकाष्ठाions described by
 * the kprobes decoding tables have had a test हाल executed क्रम them.
 */

bool coverage_fail;

#घोषणा MAX_COVERAGE_ENTRIES 256

काष्ठा coverage_entry अणु
	स्थिर काष्ठा decode_header	*header;
	अचिन्हित			regs;
	अचिन्हित			nesting;
	अक्षर				matched;
पूर्ण;

काष्ठा coverage_table अणु
	काष्ठा coverage_entry	*base;
	अचिन्हित		num_entries;
	अचिन्हित		nesting;
पूर्ण;

काष्ठा coverage_table coverage;

#घोषणा COVERAGE_ANY_REG	(1<<0)
#घोषणा COVERAGE_SP		(1<<1)
#घोषणा COVERAGE_PC		(1<<2)
#घोषणा COVERAGE_PCWB		(1<<3)

अटल स्थिर अक्षर coverage_रेजिस्टर_lookup[16] = अणु
	[REG_TYPE_ANY]		= COVERAGE_ANY_REG | COVERAGE_SP | COVERAGE_PC,
	[REG_TYPE_SAMEAS16]	= COVERAGE_ANY_REG,
	[REG_TYPE_SP]		= COVERAGE_SP,
	[REG_TYPE_PC]		= COVERAGE_PC,
	[REG_TYPE_NOSP]		= COVERAGE_ANY_REG | COVERAGE_SP,
	[REG_TYPE_NOSPPC]	= COVERAGE_ANY_REG | COVERAGE_SP | COVERAGE_PC,
	[REG_TYPE_NOPC]		= COVERAGE_ANY_REG | COVERAGE_PC,
	[REG_TYPE_NOPCWB]	= COVERAGE_ANY_REG | COVERAGE_PC | COVERAGE_PCWB,
	[REG_TYPE_NOPCX]	= COVERAGE_ANY_REG,
	[REG_TYPE_NOSPPCX]	= COVERAGE_ANY_REG | COVERAGE_SP,
पूर्ण;

अचिन्हित coverage_start_रेजिस्टरs(स्थिर काष्ठा decode_header *h)
अणु
	अचिन्हित regs = 0;
	पूर्णांक i;
	क्रम (i = 0; i < 20; i += 4) अणु
		पूर्णांक r = (h->type_regs.bits >> (DECODE_TYPE_BITS + i)) & 0xf;
		regs |= coverage_रेजिस्टर_lookup[r] << i;
	पूर्ण
	वापस regs;
पूर्ण

अटल पूर्णांक coverage_start_fn(स्थिर काष्ठा decode_header *h, व्योम *args)
अणु
	काष्ठा coverage_table *coverage = (काष्ठा coverage_table *)args;
	क्रमागत decode_type type = h->type_regs.bits & DECODE_TYPE_MASK;
	काष्ठा coverage_entry *entry = coverage->base + coverage->num_entries;

	अगर (coverage->num_entries == MAX_COVERAGE_ENTRIES - 1) अणु
		pr_err("FAIL: Out of space for test coverage data");
		वापस -ENOMEM;
	पूर्ण

	++coverage->num_entries;

	entry->header = h;
	entry->regs = coverage_start_रेजिस्टरs(h);
	entry->nesting = coverage->nesting;
	entry->matched = false;

	अगर (type == DECODE_TYPE_TABLE) अणु
		काष्ठा decode_table *d = (काष्ठा decode_table *)h;
		पूर्णांक ret;
		++coverage->nesting;
		ret = table_iter(d->table.table, coverage_start_fn, coverage);
		--coverage->nesting;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक coverage_start(स्थिर जोड़ decode_item *table)
अणु
	coverage.base = kदो_स्मृति_array(MAX_COVERAGE_ENTRIES,
				      माप(काष्ठा coverage_entry),
				      GFP_KERNEL);
	coverage.num_entries = 0;
	coverage.nesting = 0;
	वापस table_iter(table, coverage_start_fn, &coverage);
पूर्ण

अटल व्योम
coverage_add_रेजिस्टरs(काष्ठा coverage_entry *entry, kprobe_opcode_t insn)
अणु
	पूर्णांक regs = entry->header->type_regs.bits >> DECODE_TYPE_BITS;
	पूर्णांक i;
	क्रम (i = 0; i < 20; i += 4) अणु
		क्रमागत decode_reg_type reg_type = (regs >> i) & 0xf;
		पूर्णांक reg = (insn >> i) & 0xf;
		पूर्णांक flag;

		अगर (!reg_type)
			जारी;

		अगर (reg == 13)
			flag = COVERAGE_SP;
		अन्यथा अगर (reg == 15)
			flag = COVERAGE_PC;
		अन्यथा
			flag = COVERAGE_ANY_REG;
		entry->regs &= ~(flag << i);

		चयन (reg_type) अणु

		हाल REG_TYPE_NONE:
		हाल REG_TYPE_ANY:
		हाल REG_TYPE_SAMEAS16:
			अवरोध;

		हाल REG_TYPE_SP:
			अगर (reg != 13)
				वापस;
			अवरोध;

		हाल REG_TYPE_PC:
			अगर (reg != 15)
				वापस;
			अवरोध;

		हाल REG_TYPE_NOSP:
			अगर (reg == 13)
				वापस;
			अवरोध;

		हाल REG_TYPE_NOSPPC:
		हाल REG_TYPE_NOSPPCX:
			अगर (reg == 13 || reg == 15)
				वापस;
			अवरोध;

		हाल REG_TYPE_NOPCWB:
			अगर (!is_ग_लिखोback(insn))
				अवरोध;
			अगर (reg == 15) अणु
				entry->regs &= ~(COVERAGE_PCWB << i);
				वापस;
			पूर्ण
			अवरोध;

		हाल REG_TYPE_NOPC:
		हाल REG_TYPE_NOPCX:
			अगर (reg == 15)
				वापस;
			अवरोध;
		पूर्ण

	पूर्ण
पूर्ण

अटल व्योम coverage_add(kprobe_opcode_t insn)
अणु
	काष्ठा coverage_entry *entry = coverage.base;
	काष्ठा coverage_entry *end = coverage.base + coverage.num_entries;
	bool matched = false;
	अचिन्हित nesting = 0;

	क्रम (; entry < end; ++entry) अणु
		स्थिर काष्ठा decode_header *h = entry->header;
		क्रमागत decode_type type = h->type_regs.bits & DECODE_TYPE_MASK;

		अगर (entry->nesting > nesting)
			जारी; /* Skip sub-table we didn't match */

		अगर (entry->nesting < nesting)
			अवरोध; /* End of sub-table we were scanning */

		अगर (!matched) अणु
			अगर ((insn & h->mask.bits) != h->value.bits)
				जारी;
			entry->matched = true;
		पूर्ण

		चयन (type) अणु

		हाल DECODE_TYPE_TABLE:
			++nesting;
			अवरोध;

		हाल DECODE_TYPE_CUSTOM:
		हाल DECODE_TYPE_SIMULATE:
		हाल DECODE_TYPE_EMULATE:
			coverage_add_रेजिस्टरs(entry, insn);
			वापस;

		हाल DECODE_TYPE_OR:
			matched = true;
			अवरोध;

		हाल DECODE_TYPE_REJECT:
		शेष:
			वापस;
		पूर्ण

	पूर्ण
पूर्ण

अटल व्योम coverage_end(व्योम)
अणु
	काष्ठा coverage_entry *entry = coverage.base;
	काष्ठा coverage_entry *end = coverage.base + coverage.num_entries;

	क्रम (; entry < end; ++entry) अणु
		u32 mask = entry->header->mask.bits;
		u32 value = entry->header->value.bits;

		अगर (entry->regs) अणु
			pr_err("FAIL: Register test coverage missing for %08x %08x (%05x)\n",
				mask, value, entry->regs);
			coverage_fail = true;
		पूर्ण
		अगर (!entry->matched) अणु
			pr_err("FAIL: Test coverage entry missing for %08x %08x\n",
				mask, value);
			coverage_fail = true;
		पूर्ण
	पूर्ण

	kमुक्त(coverage.base);
पूर्ण


/*
 * Framework क्रम inकाष्ठाion set test हालs
 */

व्योम __naked __kprobes_test_हाल_start(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"mov	r2, sp					\n\t"
		"bic	r3, r2, #7				\n\t"
		"mov	sp, r3					\n\t"
		"stmdb	sp!, {r2-r11}				\n\t"
		"sub	sp, sp, #"__stringअगरy(TEST_MEMORY_SIZE)"\n\t"
		"bic	r0, lr, #1  @ r0 = inline data		\n\t"
		"mov	r1, sp					\n\t"
		"bl	kprobes_test_case_start			\n\t"
		RET(r0)"					\n\t"
	);
पूर्ण

#अगर_अघोषित CONFIG_THUMB2_KERNEL

व्योम __naked __kprobes_test_हाल_end_32(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"mov	r4, lr					\n\t"
		"bl	kprobes_test_case_end			\n\t"
		"cmp	r0, #0					\n\t"
		"movne	pc, r0					\n\t"
		"mov	r0, r4					\n\t"
		"add	sp, sp, #"__stringअगरy(TEST_MEMORY_SIZE)"\n\t"
		"ldmia	sp!, {r2-r11}				\n\t"
		"mov	sp, r2					\n\t"
		"mov	pc, r0					\n\t"
	);
पूर्ण

#अन्यथा /* CONFIG_THUMB2_KERNEL */

व्योम __naked __kprobes_test_हाल_end_16(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		"mov	r4, lr					\n\t"
		"bl	kprobes_test_case_end			\n\t"
		"cmp	r0, #0					\n\t"
		"bxne	r0					\n\t"
		"mov	r0, r4					\n\t"
		"add	sp, sp, #"__stringअगरy(TEST_MEMORY_SIZE)"\n\t"
		"ldmia	sp!, {r2-r11}				\n\t"
		"mov	sp, r2					\n\t"
		"bx	r0					\n\t"
	);
पूर्ण

व्योम __naked __kprobes_test_हाल_end_32(व्योम)
अणु
	__यंत्र__ __अस्थिर__ (
		".arm						\n\t"
		"orr	lr, lr, #1  @ will return to Thumb code	\n\t"
		"ldr	pc, 1f					\n\t"
		"1:						\n\t"
		".word	__kprobes_test_case_end_16		\n\t"
	);
पूर्ण

#पूर्ण_अगर


पूर्णांक kprobe_test_flags;
पूर्णांक kprobe_test_cc_position;

अटल पूर्णांक test_try_count;
अटल पूर्णांक test_pass_count;
अटल पूर्णांक test_fail_count;

अटल काष्ठा pt_regs initial_regs;
अटल काष्ठा pt_regs expected_regs;
अटल काष्ठा pt_regs result_regs;

अटल u32 expected_memory[TEST_MEMORY_SIZE/माप(u32)];

अटल स्थिर अक्षर *current_title;
अटल काष्ठा test_arg *current_args;
अटल u32 *current_stack;
अटल uपूर्णांकptr_t current_branch_target;

अटल uपूर्णांकptr_t current_code_start;
अटल kprobe_opcode_t current_inकाष्ठाion;


#घोषणा TEST_CASE_PASSED -1
#घोषणा TEST_CASE_FAILED -2

अटल पूर्णांक test_हाल_run_count;
अटल bool test_हाल_is_thumb;
अटल पूर्णांक test_instance;

अटल अचिन्हित दीर्घ test_check_cc(पूर्णांक cc, अचिन्हित दीर्घ cpsr)
अणु
	पूर्णांक ret = arm_check_condition(cc << 28, cpsr);

	वापस (ret != ARM_OPCODE_CONDTEST_FAIL);
पूर्ण

अटल पूर्णांक is_last_scenario;
अटल पूर्णांक probe_should_run; /* 0 = no, 1 = yes, -1 = unknown */
अटल पूर्णांक memory_needs_checking;

अटल अचिन्हित दीर्घ test_context_cpsr(पूर्णांक scenario)
अणु
	अचिन्हित दीर्घ cpsr;

	probe_should_run = 1;

	/* Default हाल is that we cycle through 16 combinations of flags */
	cpsr  = (scenario & 0xf) << 28; /* N,Z,C,V flags */
	cpsr |= (scenario & 0xf) << 16; /* GE flags */
	cpsr |= (scenario & 0x1) << 27; /* Toggle Q flag */

	अगर (!test_हाल_is_thumb) अणु
		/* Testing ARM code */
		पूर्णांक cc = current_inकाष्ठाion >> 28;

		probe_should_run = test_check_cc(cc, cpsr) != 0;
		अगर (scenario == 15)
			is_last_scenario = true;

	पूर्ण अन्यथा अगर (kprobe_test_flags & TEST_FLAG_NO_ITBLOCK) अणु
		/* Testing Thumb code without setting ITSTATE */
		अगर (kprobe_test_cc_position) अणु
			पूर्णांक cc = (current_inकाष्ठाion >> kprobe_test_cc_position) & 0xf;
			probe_should_run = test_check_cc(cc, cpsr) != 0;
		पूर्ण

		अगर (scenario == 15)
			is_last_scenario = true;

	पूर्ण अन्यथा अगर (kprobe_test_flags & TEST_FLAG_FULL_ITBLOCK) अणु
		/* Testing Thumb code with all combinations of ITSTATE */
		अचिन्हित x = (scenario >> 4);
		अचिन्हित cond_base = x % 7; /* ITSTATE<7:5> */
		अचिन्हित mask = x / 7 + 2;  /* ITSTATE<4:0>, bits reversed */

		अगर (mask > 0x1f) अणु
			/* Finish by testing state from inकाष्ठाion 'itt al' */
			cond_base = 7;
			mask = 0x4;
			अगर ((scenario & 0xf) == 0xf)
				is_last_scenario = true;
		पूर्ण

		cpsr |= cond_base << 13;	/* ITSTATE<7:5> */
		cpsr |= (mask & 0x1) << 12;	/* ITSTATE<4> */
		cpsr |= (mask & 0x2) << 10;	/* ITSTATE<3> */
		cpsr |= (mask & 0x4) << 8;	/* ITSTATE<2> */
		cpsr |= (mask & 0x8) << 23;	/* ITSTATE<1> */
		cpsr |= (mask & 0x10) << 21;	/* ITSTATE<0> */

		probe_should_run = test_check_cc((cpsr >> 12) & 0xf, cpsr) != 0;

	पूर्ण अन्यथा अणु
		/* Testing Thumb code with several combinations of ITSTATE */
		चयन (scenario) अणु
		हाल 16: /* Clear NZCV flags and 'it eq' state (false as Z=0) */
			cpsr = 0x00000800;
			probe_should_run = 0;
			अवरोध;
		हाल 17: /* Set NZCV flags and 'it vc' state (false as V=1) */
			cpsr = 0xf0007800;
			probe_should_run = 0;
			अवरोध;
		हाल 18: /* Clear NZCV flags and 'it ls' state (true as C=0) */
			cpsr = 0x00009800;
			अवरोध;
		हाल 19: /* Set NZCV flags and 'it cs' state (true as C=1) */
			cpsr = 0xf0002800;
			is_last_scenario = true;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस cpsr;
पूर्ण

अटल व्योम setup_test_context(काष्ठा pt_regs *regs)
अणु
	पूर्णांक scenario = test_हाल_run_count>>1;
	अचिन्हित दीर्घ val;
	काष्ठा test_arg *args;
	पूर्णांक i;

	is_last_scenario = false;
	memory_needs_checking = false;

	/* Initialise test memory on stack */
	val = (scenario & 1) ? VALM : ~VALM;
	क्रम (i = 0; i < TEST_MEMORY_SIZE / माप(current_stack[0]); ++i)
		current_stack[i] = val + (i << 8);
	/* Put target of branch on stack क्रम tests which load PC from memory */
	अगर (current_branch_target)
		current_stack[15] = current_branch_target;
	/* Put a value क्रम SP on stack क्रम tests which load SP from memory */
	current_stack[13] = (u32)current_stack + 120;

	/* Initialise रेजिस्टर values to their शेष state */
	val = (scenario & 2) ? VALR : ~VALR;
	क्रम (i = 0; i < 13; ++i)
		regs->uregs[i] = val ^ (i << 8);
	regs->ARM_lr = val ^ (14 << 8);
	regs->ARM_cpsr &= ~(APSR_MASK | PSR_IT_MASK);
	regs->ARM_cpsr |= test_context_cpsr(scenario);

	/* Perक्रमm testहाल specअगरic रेजिस्टर setup  */
	args = current_args;
	क्रम (; args[0].type != ARG_TYPE_END; ++args)
		चयन (args[0].type) अणु
		हाल ARG_TYPE_REG: अणु
			काष्ठा test_arg_regptr *arg =
				(काष्ठा test_arg_regptr *)args;
			regs->uregs[arg->reg] = arg->val;
			अवरोध;
		पूर्ण
		हाल ARG_TYPE_PTR: अणु
			काष्ठा test_arg_regptr *arg =
				(काष्ठा test_arg_regptr *)args;
			regs->uregs[arg->reg] =
				(अचिन्हित दीर्घ)current_stack + arg->val;
			memory_needs_checking = true;
			/*
			 * Test memory at an address below SP is in danger of
			 * being altered by an पूर्णांकerrupt occurring and pushing
			 * data onto the stack. Disable पूर्णांकerrupts to stop this.
			 */
			अगर (arg->reg == 13)
				regs->ARM_cpsr |= PSR_I_BIT;
			अवरोध;
		पूर्ण
		हाल ARG_TYPE_MEM: अणु
			काष्ठा test_arg_mem *arg = (काष्ठा test_arg_mem *)args;
			current_stack[arg->index] = arg->val;
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
पूर्ण

काष्ठा test_probe अणु
	काष्ठा kprobe	kprobe;
	bool		रेजिस्टरed;
	पूर्णांक		hit;
पूर्ण;

अटल व्योम unरेजिस्टर_test_probe(काष्ठा test_probe *probe)
अणु
	अगर (probe->रेजिस्टरed) अणु
		unरेजिस्टर_kprobe(&probe->kprobe);
		probe->kprobe.flags = 0; /* Clear disable flag to allow reuse */
	पूर्ण
	probe->रेजिस्टरed = false;
पूर्ण

अटल पूर्णांक रेजिस्टर_test_probe(काष्ठा test_probe *probe)
अणु
	पूर्णांक ret;

	अगर (probe->रेजिस्टरed)
		BUG();

	ret = रेजिस्टर_kprobe(&probe->kprobe);
	अगर (ret >= 0) अणु
		probe->रेजिस्टरed = true;
		probe->hit = -1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __kprobes
test_beक्रमe_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	container_of(p, काष्ठा test_probe, kprobe)->hit = test_instance;
	वापस 0;
पूर्ण

अटल व्योम __kprobes
test_beक्रमe_post_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
							अचिन्हित दीर्घ flags)
अणु
	setup_test_context(regs);
	initial_regs = *regs;
	initial_regs.ARM_cpsr &= ~PSR_IGNORE_BITS;
पूर्ण

अटल पूर्णांक __kprobes
test_हाल_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	container_of(p, काष्ठा test_probe, kprobe)->hit = test_instance;
	वापस 0;
पूर्ण

अटल पूर्णांक __kprobes
test_after_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	काष्ठा test_arg *args;

	अगर (container_of(p, काष्ठा test_probe, kprobe)->hit == test_instance)
		वापस 0; /* Alपढ़ोy run क्रम this test instance */

	result_regs = *regs;

	/* Mask out results which are indeterminate */
	result_regs.ARM_cpsr &= ~PSR_IGNORE_BITS;
	क्रम (args = current_args; args[0].type != ARG_TYPE_END; ++args)
		अगर (args[0].type == ARG_TYPE_REG_MASKED) अणु
			काष्ठा test_arg_regptr *arg =
				(काष्ठा test_arg_regptr *)args;
			result_regs.uregs[arg->reg] &= arg->val;
		पूर्ण

	/* Unकरो any changes करोne to SP by the test हाल */
	regs->ARM_sp = (अचिन्हित दीर्घ)current_stack;
	/* Enable पूर्णांकerrupts in हाल setup_test_context disabled them */
	regs->ARM_cpsr &= ~PSR_I_BIT;

	container_of(p, काष्ठा test_probe, kprobe)->hit = test_instance;
	वापस 0;
पूर्ण

अटल काष्ठा test_probe test_beक्रमe_probe = अणु
	.kprobe.pre_handler	= test_beक्रमe_pre_handler,
	.kprobe.post_handler	= test_beक्रमe_post_handler,
पूर्ण;

अटल काष्ठा test_probe test_हाल_probe = अणु
	.kprobe.pre_handler	= test_हाल_pre_handler,
पूर्ण;

अटल काष्ठा test_probe test_after_probe = अणु
	.kprobe.pre_handler	= test_after_pre_handler,
पूर्ण;

अटल काष्ठा test_probe test_after2_probe = अणु
	.kprobe.pre_handler	= test_after_pre_handler,
पूर्ण;

अटल व्योम test_हाल_cleanup(व्योम)
अणु
	unरेजिस्टर_test_probe(&test_beक्रमe_probe);
	unरेजिस्टर_test_probe(&test_हाल_probe);
	unरेजिस्टर_test_probe(&test_after_probe);
	unरेजिस्टर_test_probe(&test_after2_probe);
पूर्ण

अटल व्योम prपूर्णांक_रेजिस्टरs(काष्ठा pt_regs *regs)
अणु
	pr_err("r0  %08lx | r1  %08lx | r2  %08lx | r3  %08lx\n",
		regs->ARM_r0, regs->ARM_r1, regs->ARM_r2, regs->ARM_r3);
	pr_err("r4  %08lx | r5  %08lx | r6  %08lx | r7  %08lx\n",
		regs->ARM_r4, regs->ARM_r5, regs->ARM_r6, regs->ARM_r7);
	pr_err("r8  %08lx | r9  %08lx | r10 %08lx | r11 %08lx\n",
		regs->ARM_r8, regs->ARM_r9, regs->ARM_r10, regs->ARM_fp);
	pr_err("r12 %08lx | sp  %08lx | lr  %08lx | pc  %08lx\n",
		regs->ARM_ip, regs->ARM_sp, regs->ARM_lr, regs->ARM_pc);
	pr_err("cpsr %08lx\n", regs->ARM_cpsr);
पूर्ण

अटल व्योम prपूर्णांक_memory(u32 *mem, माप_प्रकार size)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < size / माप(u32); i += 4)
		pr_err("%08x %08x %08x %08x\n", mem[i], mem[i+1],
						mem[i+2], mem[i+3]);
पूर्ण

अटल माप_प्रकार expected_memory_size(u32 *sp)
अणु
	माप_प्रकार size = माप(expected_memory);
	पूर्णांक offset = (uपूर्णांकptr_t)sp - (uपूर्णांकptr_t)current_stack;
	अगर (offset > 0)
		size -= offset;
	वापस size;
पूर्ण

अटल व्योम test_हाल_failed(स्थिर अक्षर *message)
अणु
	test_हाल_cleanup();

	pr_err("FAIL: %s\n", message);
	pr_err("FAIL: Test %s\n", current_title);
	pr_err("FAIL: Scenario %d\n", test_हाल_run_count >> 1);
पूर्ण

अटल अचिन्हित दीर्घ next_inकाष्ठाion(अचिन्हित दीर्घ pc)
अणु
#अगर_घोषित CONFIG_THUMB2_KERNEL
	अगर ((pc & 1) &&
	    !is_wide_inकाष्ठाion(__mem_to_opcode_thumb16(*(u16 *)(pc - 1))))
		वापस pc + 2;
	अन्यथा
#पूर्ण_अगर
	वापस pc + 4;
पूर्ण

अटल uपूर्णांकptr_t __used kprobes_test_हाल_start(स्थिर अक्षर **title, व्योम *stack)
अणु
	काष्ठा test_arg *args;
	काष्ठा test_arg_end *end_arg;
	अचिन्हित दीर्घ test_code;

	current_title = *title++;
	args = (काष्ठा test_arg *)title;
	current_args = args;
	current_stack = stack;

	++test_try_count;

	जबतक (args->type != ARG_TYPE_END)
		++args;
	end_arg = (काष्ठा test_arg_end *)args;

	test_code = (अचिन्हित दीर्घ)(args + 1); /* Code starts after args */

	test_हाल_is_thumb = end_arg->flags & ARG_FLAG_THUMB;
	अगर (test_हाल_is_thumb)
		test_code |= 1;

	current_code_start = test_code;

	current_branch_target = 0;
	अगर (end_arg->branch_offset != end_arg->end_offset)
		current_branch_target = test_code + end_arg->branch_offset;

	test_code += end_arg->code_offset;
	test_beक्रमe_probe.kprobe.addr = (kprobe_opcode_t *)test_code;

	test_code = next_inकाष्ठाion(test_code);
	test_हाल_probe.kprobe.addr = (kprobe_opcode_t *)test_code;

	अगर (test_हाल_is_thumb) अणु
		u16 *p = (u16 *)(test_code & ~1);
		current_inकाष्ठाion = __mem_to_opcode_thumb16(p[0]);
		अगर (is_wide_inकाष्ठाion(current_inकाष्ठाion)) अणु
			u16 instr2 = __mem_to_opcode_thumb16(p[1]);
			current_inकाष्ठाion = __opcode_thumb32_compose(current_inकाष्ठाion, instr2);
		पूर्ण
	पूर्ण अन्यथा अणु
		current_inकाष्ठाion = __mem_to_opcode_arm(*(u32 *)test_code);
	पूर्ण

	अगर (current_title[0] == '.')
		verbose("%s\n", current_title);
	अन्यथा
		verbose("%s\t@ %0*x\n", current_title,
					test_हाल_is_thumb ? 4 : 8,
					current_inकाष्ठाion);

	test_code = next_inकाष्ठाion(test_code);
	test_after_probe.kprobe.addr = (kprobe_opcode_t *)test_code;

	अगर (kprobe_test_flags & TEST_FLAG_NARROW_INSTR) अणु
		अगर (!test_हाल_is_thumb ||
			is_wide_inकाष्ठाion(current_inकाष्ठाion)) अणु
				test_हाल_failed("expected 16-bit instruction");
				जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (test_हाल_is_thumb &&
			!is_wide_inकाष्ठाion(current_inकाष्ठाion)) अणु
				test_हाल_failed("expected 32-bit instruction");
				जाओ fail;
		पूर्ण
	पूर्ण

	coverage_add(current_inकाष्ठाion);

	अगर (end_arg->flags & ARG_FLAG_UNSUPPORTED) अणु
		अगर (रेजिस्टर_test_probe(&test_हाल_probe) < 0)
			जाओ pass;
		test_हाल_failed("registered probe for unsupported instruction");
		जाओ fail;
	पूर्ण

	अगर (end_arg->flags & ARG_FLAG_SUPPORTED) अणु
		अगर (रेजिस्टर_test_probe(&test_हाल_probe) >= 0)
			जाओ pass;
		test_हाल_failed("couldn't register probe for supported instruction");
		जाओ fail;
	पूर्ण

	अगर (रेजिस्टर_test_probe(&test_beक्रमe_probe) < 0) अणु
		test_हाल_failed("register test_before_probe failed");
		जाओ fail;
	पूर्ण
	अगर (रेजिस्टर_test_probe(&test_after_probe) < 0) अणु
		test_हाल_failed("register test_after_probe failed");
		जाओ fail;
	पूर्ण
	अगर (current_branch_target) अणु
		test_after2_probe.kprobe.addr =
				(kprobe_opcode_t *)current_branch_target;
		अगर (रेजिस्टर_test_probe(&test_after2_probe) < 0) अणु
			test_हाल_failed("register test_after2_probe failed");
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Start first run of test हाल */
	test_हाल_run_count = 0;
	++test_instance;
	वापस current_code_start;
pass:
	test_हाल_run_count = TEST_CASE_PASSED;
	वापस (uपूर्णांकptr_t)test_after_probe.kprobe.addr;
fail:
	test_हाल_run_count = TEST_CASE_FAILED;
	वापस (uपूर्णांकptr_t)test_after_probe.kprobe.addr;
पूर्ण

अटल bool check_test_results(व्योम)
अणु
	माप_प्रकार mem_size = 0;
	u32 *mem = 0;

	अगर (स_भेद(&expected_regs, &result_regs, माप(expected_regs))) अणु
		test_हाल_failed("registers differ");
		जाओ fail;
	पूर्ण

	अगर (memory_needs_checking) अणु
		mem = (u32 *)result_regs.ARM_sp;
		mem_size = expected_memory_size(mem);
		अगर (स_भेद(expected_memory, mem, mem_size)) अणु
			test_हाल_failed("test memory differs");
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस true;

fail:
	pr_err("initial_regs:\n");
	prपूर्णांक_रेजिस्टरs(&initial_regs);
	pr_err("expected_regs:\n");
	prपूर्णांक_रेजिस्टरs(&expected_regs);
	pr_err("result_regs:\n");
	prपूर्णांक_रेजिस्टरs(&result_regs);

	अगर (mem) अणु
		pr_err("expected_memory:\n");
		prपूर्णांक_memory(expected_memory, mem_size);
		pr_err("result_memory:\n");
		prपूर्णांक_memory(mem, mem_size);
	पूर्ण

	वापस false;
पूर्ण

अटल uपूर्णांकptr_t __used kprobes_test_हाल_end(व्योम)
अणु
	अगर (test_हाल_run_count < 0) अणु
		अगर (test_हाल_run_count == TEST_CASE_PASSED)
			/* kprobes_test_हाल_start did all the needed testing */
			जाओ pass;
		अन्यथा
			/* kprobes_test_हाल_start failed */
			जाओ fail;
	पूर्ण

	अगर (test_beक्रमe_probe.hit != test_instance) अणु
		test_हाल_failed("test_before_handler not run");
		जाओ fail;
	पूर्ण

	अगर (test_after_probe.hit != test_instance &&
				test_after2_probe.hit != test_instance) अणु
		test_हाल_failed("test_after_handler not run");
		जाओ fail;
	पूर्ण

	/*
	 * Even numbered test runs ran without a probe on the test हाल so
	 * we can gather reference results. The subsequent odd numbered run
	 * will have the probe inserted.
	*/
	अगर ((test_हाल_run_count & 1) == 0) अणु
		/* Save results from run without probe */
		u32 *mem = (u32 *)result_regs.ARM_sp;
		expected_regs = result_regs;
		स_नकल(expected_memory, mem, expected_memory_size(mem));

		/* Insert probe onto test हाल inकाष्ठाion */
		अगर (रेजिस्टर_test_probe(&test_हाल_probe) < 0) अणु
			test_हाल_failed("register test_case_probe failed");
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Check probe ran as expected */
		अगर (probe_should_run == 1) अणु
			अगर (test_हाल_probe.hit != test_instance) अणु
				test_हाल_failed("test_case_handler not run");
				जाओ fail;
			पूर्ण
		पूर्ण अन्यथा अगर (probe_should_run == 0) अणु
			अगर (test_हाल_probe.hit == test_instance) अणु
				test_हाल_failed("test_case_handler ran");
				जाओ fail;
			पूर्ण
		पूर्ण

		/* Remove probe क्रम any subsequent reference run */
		unरेजिस्टर_test_probe(&test_हाल_probe);

		अगर (!check_test_results())
			जाओ fail;

		अगर (is_last_scenario)
			जाओ pass;
	पूर्ण

	/* Do next test run */
	++test_हाल_run_count;
	++test_instance;
	वापस current_code_start;
fail:
	++test_fail_count;
	जाओ end;
pass:
	++test_pass_count;
end:
	test_हाल_cleanup();
	वापस 0;
पूर्ण


/*
 * Top level test functions
 */

अटल पूर्णांक run_test_हालs(व्योम (*tests)(व्योम), स्थिर जोड़ decode_item *table)
अणु
	पूर्णांक ret;

	pr_info("    Check decoding tables\n");
	ret = table_test(table);
	अगर (ret)
		वापस ret;

	pr_info("    Run test cases\n");
	ret = coverage_start(table);
	अगर (ret)
		वापस ret;

	tests();

	coverage_end();
	वापस 0;
पूर्ण


अटल पूर्णांक __init run_all_tests(व्योम)
अणु
	पूर्णांक ret = 0;

	pr_info("Beginning kprobe tests...\n");

#अगर_अघोषित CONFIG_THUMB2_KERNEL

	pr_info("Probe ARM code\n");
	ret = run_api_tests(arm_func);
	अगर (ret)
		जाओ out;

	pr_info("ARM instruction simulation\n");
	ret = run_test_हालs(kprobe_arm_test_हालs, probes_decode_arm_table);
	अगर (ret)
		जाओ out;

#अन्यथा /* CONFIG_THUMB2_KERNEL */

	pr_info("Probe 16-bit Thumb code\n");
	ret = run_api_tests(thumb16_func);
	अगर (ret)
		जाओ out;

	pr_info("Probe 32-bit Thumb code, even halfword\n");
	ret = run_api_tests(thumb32even_func);
	अगर (ret)
		जाओ out;

	pr_info("Probe 32-bit Thumb code, odd halfword\n");
	ret = run_api_tests(thumb32odd_func);
	अगर (ret)
		जाओ out;

	pr_info("16-bit Thumb instruction simulation\n");
	ret = run_test_हालs(kprobe_thumb16_test_हालs,
				probes_decode_thumb16_table);
	अगर (ret)
		जाओ out;

	pr_info("32-bit Thumb instruction simulation\n");
	ret = run_test_हालs(kprobe_thumb32_test_हालs,
				probes_decode_thumb32_table);
	अगर (ret)
		जाओ out;
#पूर्ण_अगर

	pr_info("Total instruction simulation tests=%d, pass=%d fail=%d\n",
		test_try_count, test_pass_count, test_fail_count);
	अगर (test_fail_count) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

#अगर BENCHMARKING
	pr_info("Benchmarks\n");
	ret = run_benchmarks();
	अगर (ret)
		जाओ out;
#पूर्ण_अगर

#अगर __LINUX_ARM_ARCH__ >= 7
	/* We are able to run all test हालs so coverage should be complete */
	अगर (coverage_fail) अणु
		pr_err("FAIL: Test coverage checks failed\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण
#पूर्ण_अगर

out:
	अगर (ret == 0)
		ret = tests_failed;
	अगर (ret == 0)
		pr_info("Finished kprobe tests OK\n");
	अन्यथा
		pr_err("kprobe tests failed\n");

	वापस ret;
पूर्ण


/*
 * Module setup
 */

#अगर_घोषित MODULE

अटल व्योम __निकास kprobe_test_निकास(व्योम)
अणु
पूर्ण

module_init(run_all_tests)
module_निकास(kprobe_test_निकास)
MODULE_LICENSE("GPL");

#अन्यथा /* !MODULE */

late_initcall(run_all_tests);

#पूर्ण_अगर
