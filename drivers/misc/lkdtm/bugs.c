<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is क्रम all the tests related to logic bugs (e.g. bad dereferences,
 * bad alignment, bad loops, bad locking, bad scheduling, deep stacks, and
 * lockups) aदीर्घ with other things that करोn't fit well पूर्णांकo existing LKDTM
 * test source files.
 */
#समावेश "lkdtm.h"
#समावेश <linux/list.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>

#अगर IS_ENABLED(CONFIG_X86_32) && !IS_ENABLED(CONFIG_UML)
#समावेश <यंत्र/desc.h>
#पूर्ण_अगर

काष्ठा lkdपंचांग_list अणु
	काष्ठा list_head node;
पूर्ण;

/*
 * Make sure our attempts to over run the kernel stack करोesn't trigger
 * a compiler warning when CONFIG_FRAME_WARN is set. Then make sure we
 * recurse past the end of THREAD_SIZE by शेष.
 */
#अगर defined(CONFIG_FRAME_WARN) && (CONFIG_FRAME_WARN > 0)
#घोषणा REC_STACK_SIZE (_AC(CONFIG_FRAME_WARN, UL) / 2)
#अन्यथा
#घोषणा REC_STACK_SIZE (THREAD_SIZE / 8)
#पूर्ण_अगर
#घोषणा REC_NUM_DEFAULT ((THREAD_SIZE / REC_STACK_SIZE) * 2)

अटल पूर्णांक recur_count = REC_NUM_DEFAULT;

अटल DEFINE_SPINLOCK(lock_me_up);

/*
 * Make sure compiler करोes not optimize this function or stack frame away:
 * - function marked noअंतरभूत
 * - stack variables are marked अस्थिर
 * - stack variables are written (स_रखो()) and पढ़ो (pr_info())
 * - function has बाह्यal effects (pr_info())
 * */
अटल पूर्णांक noअंतरभूत recursive_loop(पूर्णांक reमुख्यing)
अणु
	अस्थिर अक्षर buf[REC_STACK_SIZE];

	स_रखो((व्योम *)buf, reमुख्यing & 0xFF, माप(buf));
	pr_info("loop %d/%d ...\n", (पूर्णांक)buf[reमुख्यing % माप(buf)],
		recur_count);
	अगर (!reमुख्यing)
		वापस 0;
	अन्यथा
		वापस recursive_loop(reमुख्यing - 1);
पूर्ण

/* If the depth is negative, use the शेष, otherwise keep parameter. */
व्योम __init lkdपंचांग_bugs_init(पूर्णांक *recur_param)
अणु
	अगर (*recur_param < 0)
		*recur_param = recur_count;
	अन्यथा
		recur_count = *recur_param;
पूर्ण

व्योम lkdपंचांग_PANIC(व्योम)
अणु
	panic("dumptest");
पूर्ण

व्योम lkdपंचांग_BUG(व्योम)
अणु
	BUG();
पूर्ण

अटल पूर्णांक warn_counter;

व्योम lkdपंचांग_WARNING(व्योम)
अणु
	WARN_ON(++warn_counter);
पूर्ण

व्योम lkdपंचांग_WARNING_MESSAGE(व्योम)
अणु
	WARN(1, "Warning message trigger count: %d\n", ++warn_counter);
पूर्ण

व्योम lkdपंचांग_EXCEPTION(व्योम)
अणु
	*((अस्थिर पूर्णांक *) 0) = 0;
पूर्ण

व्योम lkdपंचांग_LOOP(व्योम)
अणु
	क्रम (;;)
		;
पूर्ण

व्योम lkdपंचांग_EXHAUST_STACK(व्योम)
अणु
	pr_info("Calling function with %lu frame size to depth %d ...\n",
		REC_STACK_SIZE, recur_count);
	recursive_loop(recur_count);
	pr_info("FAIL: survived without exhausting stack?!\n");
पूर्ण

अटल noअंतरभूत व्योम __lkdपंचांग_CORRUPT_STACK(व्योम *stack)
अणु
	स_रखो(stack, '\xff', 64);
पूर्ण

/* This should trip the stack canary, not corrupt the वापस address. */
noअंतरभूत व्योम lkdपंचांग_CORRUPT_STACK(व्योम)
अणु
	/* Use शेष अक्षर array length that triggers stack protection. */
	अक्षर data[8] __aligned(माप(व्योम *));

	pr_info("Corrupting stack containing char array ...\n");
	__lkdपंचांग_CORRUPT_STACK((व्योम *)&data);
पूर्ण

/* Same as above but will only get a canary with -fstack-protector-strong */
noअंतरभूत व्योम lkdपंचांग_CORRUPT_STACK_STRONG(व्योम)
अणु
	जोड़ अणु
		अचिन्हित लघु लघुs[4];
		अचिन्हित दीर्घ *ptr;
	पूर्ण data __aligned(माप(व्योम *));

	pr_info("Corrupting stack containing union ...\n");
	__lkdपंचांग_CORRUPT_STACK((व्योम *)&data);
पूर्ण

अटल pid_t stack_pid;
अटल अचिन्हित दीर्घ stack_addr;

व्योम lkdपंचांग_REPORT_STACK(व्योम)
अणु
	अस्थिर uपूर्णांकptr_t magic;
	pid_t pid = task_pid_nr(current);

	अगर (pid != stack_pid) अणु
		pr_info("Starting stack offset tracking for pid %d\n", pid);
		stack_pid = pid;
		stack_addr = (uपूर्णांकptr_t)&magic;
	पूर्ण

	pr_info("Stack offset: %d\n", (पूर्णांक)(stack_addr - (uपूर्णांकptr_t)&magic));
पूर्ण

व्योम lkdपंचांग_UNALIGNED_LOAD_STORE_WRITE(व्योम)
अणु
	अटल u8 data[5] __attribute__((aligned(4))) = अणु1, 2, 3, 4, 5पूर्ण;
	u32 *p;
	u32 val = 0x12345678;

	p = (u32 *)(data + 1);
	अगर (*p == 0)
		val = 0x87654321;
	*p = val;
पूर्ण

व्योम lkdपंचांग_SOFTLOCKUP(व्योम)
अणु
	preempt_disable();
	क्रम (;;)
		cpu_relax();
पूर्ण

व्योम lkdपंचांग_HARDLOCKUP(व्योम)
अणु
	local_irq_disable();
	क्रम (;;)
		cpu_relax();
पूर्ण

व्योम lkdपंचांग_SPINLOCKUP(व्योम)
अणु
	/* Must be called twice to trigger. */
	spin_lock(&lock_me_up);
	/* Let sparse know we पूर्णांकended to निकास holding the lock. */
	__release(&lock_me_up);
पूर्ण

व्योम lkdपंचांग_HUNG_TASK(व्योम)
अणु
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule();
पूर्ण

अस्थिर अचिन्हित पूर्णांक huge = पूर्णांक_उच्च - 2;
अस्थिर अचिन्हित पूर्णांक ignored;

व्योम lkdपंचांग_OVERFLOW_SIGNED(व्योम)
अणु
	पूर्णांक value;

	value = huge;
	pr_info("Normal signed addition ...\n");
	value += 1;
	ignored = value;

	pr_info("Overflowing signed addition ...\n");
	value += 4;
	ignored = value;
पूर्ण


व्योम lkdपंचांग_OVERFLOW_UNSIGNED(व्योम)
अणु
	अचिन्हित पूर्णांक value;

	value = huge;
	pr_info("Normal unsigned addition ...\n");
	value += 1;
	ignored = value;

	pr_info("Overflowing unsigned addition ...\n");
	value += 4;
	ignored = value;
पूर्ण

/* Intentionally using old-style flex array definition of 1 byte. */
काष्ठा array_bounds_flex_array अणु
	पूर्णांक one;
	पूर्णांक two;
	अक्षर data[1];
पूर्ण;

काष्ठा array_bounds अणु
	पूर्णांक one;
	पूर्णांक two;
	अक्षर data[8];
	पूर्णांक three;
पूर्ण;

व्योम lkdपंचांग_ARRAY_BOUNDS(व्योम)
अणु
	काष्ठा array_bounds_flex_array *not_checked;
	काष्ठा array_bounds *checked;
	अस्थिर पूर्णांक i;

	not_checked = kदो_स्मृति(माप(*not_checked) * 2, GFP_KERNEL);
	checked = kदो_स्मृति(माप(*checked) * 2, GFP_KERNEL);

	pr_info("Array access within bounds ...\n");
	/* For both, touch all bytes in the actual member size. */
	क्रम (i = 0; i < माप(checked->data); i++)
		checked->data[i] = 'A';
	/*
	 * For the uninstrumented flex array member, also touch 1 byte
	 * beyond to verअगरy it is correctly uninstrumented.
	 */
	क्रम (i = 0; i < माप(not_checked->data) + 1; i++)
		not_checked->data[i] = 'A';

	pr_info("Array access beyond bounds ...\n");
	क्रम (i = 0; i < माप(checked->data) + 1; i++)
		checked->data[i] = 'B';

	kमुक्त(not_checked);
	kमुक्त(checked);
	pr_err("FAIL: survived array bounds overflow!\n");
पूर्ण

व्योम lkdपंचांग_CORRUPT_LIST_ADD(व्योम)
अणु
	/*
	 * Initially, an empty list via LIST_HEAD:
	 *	test_head.next = &test_head
	 *	test_head.prev = &test_head
	 */
	LIST_HEAD(test_head);
	काष्ठा lkdपंचांग_list good, bad;
	व्योम *target[2] = अणु पूर्ण;
	व्योम *redirection = &target;

	pr_info("attempting good list addition\n");

	/*
	 * Adding to the list perक्रमms these actions:
	 *	test_head.next->prev = &good.node
	 *	good.node.next = test_head.next
	 *	good.node.prev = test_head
	 *	test_head.next = good.node
	 */
	list_add(&good.node, &test_head);

	pr_info("attempting corrupted list addition\n");
	/*
	 * In simulating this "write what where" primitive, the "what" is
	 * the address of &bad.node, and the "where" is the address held
	 * by "redirection".
	 */
	test_head.next = redirection;
	list_add(&bad.node, &test_head);

	अगर (target[0] == शून्य && target[1] == शून्य)
		pr_err("Overwrite did not happen, but no BUG?!\n");
	अन्यथा
		pr_err("list_add() corruption not detected!\n");
पूर्ण

व्योम lkdपंचांग_CORRUPT_LIST_DEL(व्योम)
अणु
	LIST_HEAD(test_head);
	काष्ठा lkdपंचांग_list item;
	व्योम *target[2] = अणु पूर्ण;
	व्योम *redirection = &target;

	list_add(&item.node, &test_head);

	pr_info("attempting good list removal\n");
	list_del(&item.node);

	pr_info("attempting corrupted list removal\n");
	list_add(&item.node, &test_head);

	/* As with the list_add() test above, this corrupts "next". */
	item.node.next = redirection;
	list_del(&item.node);

	अगर (target[0] == शून्य && target[1] == शून्य)
		pr_err("Overwrite did not happen, but no BUG?!\n");
	अन्यथा
		pr_err("list_del() corruption not detected!\n");
पूर्ण

/* Test that VMAP_STACK is actually allocating with a leading guard page */
व्योम lkdपंचांग_STACK_GUARD_PAGE_LEADING(व्योम)
अणु
	स्थिर अचिन्हित अक्षर *stack = task_stack_page(current);
	स्थिर अचिन्हित अक्षर *ptr = stack - 1;
	अस्थिर अचिन्हित अक्षर byte;

	pr_info("attempting bad read from page below current stack\n");

	byte = *ptr;

	pr_err("FAIL: accessed page before stack! (byte: %x)\n", byte);
पूर्ण

/* Test that VMAP_STACK is actually allocating with a trailing guard page */
व्योम lkdपंचांग_STACK_GUARD_PAGE_TRAILING(व्योम)
अणु
	स्थिर अचिन्हित अक्षर *stack = task_stack_page(current);
	स्थिर अचिन्हित अक्षर *ptr = stack + THREAD_SIZE;
	अस्थिर अचिन्हित अक्षर byte;

	pr_info("attempting bad read from page above current stack\n");

	byte = *ptr;

	pr_err("FAIL: accessed page after stack! (byte: %x)\n", byte);
पूर्ण

व्योम lkdपंचांग_UNSET_SMEP(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_X86_64) && !IS_ENABLED(CONFIG_UML)
#घोषणा MOV_CR4_DEPTH	64
	व्योम (*direct_ग_लिखो_cr4)(अचिन्हित दीर्घ val);
	अचिन्हित अक्षर *insn;
	अचिन्हित दीर्घ cr4;
	पूर्णांक i;

	cr4 = native_पढ़ो_cr4();

	अगर ((cr4 & X86_CR4_SMEP) != X86_CR4_SMEP) अणु
		pr_err("FAIL: SMEP not in use\n");
		वापस;
	पूर्ण
	cr4 &= ~(X86_CR4_SMEP);

	pr_info("trying to clear SMEP normally\n");
	native_ग_लिखो_cr4(cr4);
	अगर (cr4 == native_पढ़ो_cr4()) अणु
		pr_err("FAIL: pinning SMEP failed!\n");
		cr4 |= X86_CR4_SMEP;
		pr_info("restoring SMEP\n");
		native_ग_लिखो_cr4(cr4);
		वापस;
	पूर्ण
	pr_info("ok: SMEP did not get cleared\n");

	/*
	 * To test the post-ग_लिखो pinning verअगरication we need to call
	 * directly पूर्णांकo the middle of native_ग_लिखो_cr4() where the
	 * cr4 ग_लिखो happens, skipping any pinning. This searches क्रम
	 * the cr4 writing inकाष्ठाion.
	 */
	insn = (अचिन्हित अक्षर *)native_ग_लिखो_cr4;
	क्रम (i = 0; i < MOV_CR4_DEPTH; i++) अणु
		/* mov %rdi, %cr4 */
		अगर (insn[i] == 0x0f && insn[i+1] == 0x22 && insn[i+2] == 0xe7)
			अवरोध;
		/* mov %rdi,%rax; mov %rax, %cr4 */
		अगर (insn[i]   == 0x48 && insn[i+1] == 0x89 &&
		    insn[i+2] == 0xf8 && insn[i+3] == 0x0f &&
		    insn[i+4] == 0x22 && insn[i+5] == 0xe0)
			अवरोध;
	पूर्ण
	अगर (i >= MOV_CR4_DEPTH) अणु
		pr_info("ok: cannot locate cr4 writing call gadget\n");
		वापस;
	पूर्ण
	direct_ग_लिखो_cr4 = (व्योम *)(insn + i);

	pr_info("trying to clear SMEP with call gadget\n");
	direct_ग_लिखो_cr4(cr4);
	अगर (native_पढ़ो_cr4() & X86_CR4_SMEP) अणु
		pr_info("ok: SMEP removal was reverted\n");
	पूर्ण अन्यथा अणु
		pr_err("FAIL: cleared SMEP not detected!\n");
		cr4 |= X86_CR4_SMEP;
		pr_info("restoring SMEP\n");
		native_ग_लिखो_cr4(cr4);
	पूर्ण
#अन्यथा
	pr_err("XFAIL: this test is x86_64-only\n");
#पूर्ण_अगर
पूर्ण

व्योम lkdपंचांग_DOUBLE_FAULT(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_X86_32) && !IS_ENABLED(CONFIG_UML)
	/*
	 * Trigger #DF by setting the stack limit to zero.  This clobbers
	 * a GDT TLS slot, which is okay because the current task will die
	 * anyway due to the द्विगुन fault.
	 */
	काष्ठा desc_काष्ठा d = अणु
		.type = 3,	/* expand-up, writable, accessed data */
		.p = 1,		/* present */
		.d = 1,		/* 32-bit */
		.g = 0,		/* limit in bytes */
		.s = 1,		/* not प्रणाली */
	पूर्ण;

	local_irq_disable();
	ग_लिखो_gdt_entry(get_cpu_gdt_rw(smp_processor_id()),
			GDT_ENTRY_TLS_MIN, &d, DESCTYPE_S);

	/*
	 * Put our zero-limit segment in SS and then trigger a fault.  The
	 * 4-byte access to (%esp) will fault with #SS, and the attempt to
	 * deliver the fault will recursively cause #SS and result in #DF.
	 * This whole process happens जबतक NMIs and MCEs are blocked by the
	 * MOV SS winकरोw.  This is nice because an NMI with an invalid SS
	 * would also द्विगुन-fault, resulting in the NMI or MCE being lost.
	 */
	यंत्र अस्थिर ("movw %0, %%ss; addl $0, (%%esp)" ::
		      "r" ((अचिन्हित लघु)(GDT_ENTRY_TLS_MIN << 3)));

	pr_err("FAIL: tried to double fault but didn't die\n");
#अन्यथा
	pr_err("XFAIL: this test is ia32-only\n");
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_ARM64
अटल noअंतरभूत व्योम change_pac_parameters(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_ARM64_PTR_AUTH)) अणु
		/* Reset the keys of current task */
		ptrauth_thपढ़ो_init_kernel(current);
		ptrauth_thपढ़ो_चयन_kernel(current);
	पूर्ण
पूर्ण
#पूर्ण_अगर

noअंतरभूत व्योम lkdपंचांग_CORRUPT_PAC(व्योम)
अणु
#अगर_घोषित CONFIG_ARM64
#घोषणा CORRUPT_PAC_ITERATE	10
	पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_ARM64_PTR_AUTH))
		pr_err("FAIL: kernel not built with CONFIG_ARM64_PTR_AUTH\n");

	अगर (!प्रणाली_supports_address_auth()) अणु
		pr_err("FAIL: CPU lacks pointer authentication feature\n");
		वापस;
	पूर्ण

	pr_info("changing PAC parameters to force function return failure...\n");
	/*
	 * PAC is a hash value computed from input keys, वापस address and
	 * stack poपूर्णांकer. As pac has fewer bits so there is a chance of
	 * collision, so iterate few बार to reduce the collision probability.
	 */
	क्रम (i = 0; i < CORRUPT_PAC_ITERATE; i++)
		change_pac_parameters();

	pr_err("FAIL: survived PAC changes! Kernel may be unstable from here\n");
#अन्यथा
	pr_err("XFAIL: this test is arm64-only\n");
#पूर्ण_अगर
पूर्ण

व्योम lkdपंचांग_FORTIFY_OBJECT(व्योम)
अणु
	काष्ठा target अणु
		अक्षर a[10];
	पूर्ण target[2] = अणुपूर्ण;
	पूर्णांक result;

	/*
	 * Using अस्थिर prevents the compiler from determining the value of
	 * 'size' at compile समय. Without that, we would get a compile error
	 * rather than a runसमय error.
	 */
	अस्थिर पूर्णांक size = 11;

	pr_info("trying to read past the end of a struct\n");

	result = स_भेद(&target[0], &target[1], size);

	/* Prपूर्णांक result to prevent the code from being eliminated */
	pr_err("FAIL: fortify did not catch an object overread!\n"
	       "\"%d\" was the memcmp result.\n", result);
पूर्ण

व्योम lkdपंचांग_FORTIFY_SUBOBJECT(व्योम)
अणु
	काष्ठा target अणु
		अक्षर a[10];
		अक्षर b[10];
	पूर्ण target;
	अक्षर *src;

	src = kदो_स्मृति(20, GFP_KERNEL);
	strscpy(src, "over ten bytes", 20);

	pr_info("trying to strcpy past the end of a member of a struct\n");

	/*
	 * म_नकलन(target.a, src, 20); will hit a compile error because the
	 * compiler knows at build समय that target.a < 20 bytes. Use म_नकल()
	 * to क्रमce a runसमय error.
	 */
	म_नकल(target.a, src);

	/* Use target.a to prevent the code from being eliminated */
	pr_err("FAIL: fortify did not catch an sub-object overrun!\n"
	       "\"%s\" was copied.\n", target.a);

	kमुक्त(src);
पूर्ण
