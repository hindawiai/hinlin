<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Test module क्रम unwind_क्रम_each_frame
 */

#घोषणा pr_fmt(fmt) "test_unwind: " fmt
#समावेश <यंत्र/unwind.h>
#समावेश <linux/completion.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/kprobes.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/irq.h>

#घोषणा BT_BUF_SIZE (PAGE_SIZE * 4)

/*
 * To aव्योम prपूर्णांकk line limit split backtrace by lines
 */
अटल व्योम prपूर्णांक_backtrace(अक्षर *bt)
अणु
	अक्षर *p;

	जबतक (true) अणु
		p = strsep(&bt, "\n");
		अगर (!p)
			अवरोध;
		pr_err("%s\n", p);
	पूर्ण
पूर्ण

/*
 * Calls unwind_क्रम_each_frame(task, regs, sp) and verअगरies that the result
 * contains unwindme_func2 followed by unwindme_func1.
 */
अटल noअंतरभूत पूर्णांक test_unwind(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
				अचिन्हित दीर्घ sp)
अणु
	पूर्णांक frame_count, prev_is_func2, seen_func2_func1;
	स्थिर पूर्णांक max_frames = 128;
	काष्ठा unwind_state state;
	माप_प्रकार bt_pos = 0;
	पूर्णांक ret = 0;
	अक्षर *bt;

	bt = kदो_स्मृति(BT_BUF_SIZE, GFP_ATOMIC);
	अगर (!bt) अणु
		pr_err("failed to allocate backtrace buffer\n");
		वापस -ENOMEM;
	पूर्ण
	/* Unwind. */
	frame_count = 0;
	prev_is_func2 = 0;
	seen_func2_func1 = 0;
	unwind_क्रम_each_frame(&state, task, regs, sp) अणु
		अचिन्हित दीर्घ addr = unwind_get_वापस_address(&state);
		अक्षर sym[KSYM_SYMBOL_LEN];

		अगर (frame_count++ == max_frames)
			अवरोध;
		अगर (state.reliable && !addr) अणु
			pr_err("unwind state reliable but addr is 0\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		sprपूर्णांक_symbol(sym, addr);
		अगर (bt_pos < BT_BUF_SIZE) अणु
			bt_pos += snम_लिखो(bt + bt_pos, BT_BUF_SIZE - bt_pos,
					   state.reliable ? " [%-7s%px] %pSR\n" :
							    "([%-7s%px] %pSR)\n",
					   stack_type_name(state.stack_info.type),
					   (व्योम *)state.sp, (व्योम *)state.ip);
			अगर (bt_pos >= BT_BUF_SIZE)
				pr_err("backtrace buffer is too small\n");
		पूर्ण
		frame_count += 1;
		अगर (prev_is_func2 && str_has_prefix(sym, "unwindme_func1"))
			seen_func2_func1 = 1;
		prev_is_func2 = str_has_prefix(sym, "unwindme_func2");
	पूर्ण

	/* Check the results. */
	अगर (unwind_error(&state)) अणु
		pr_err("unwind error\n");
		ret = -EINVAL;
	पूर्ण
	अगर (!seen_func2_func1) अणु
		pr_err("unwindme_func2 and unwindme_func1 not found\n");
		ret = -EINVAL;
	पूर्ण
	अगर (frame_count == max_frames) अणु
		pr_err("Maximum number of frames exceeded\n");
		ret = -EINVAL;
	पूर्ण
	अगर (ret)
		prपूर्णांक_backtrace(bt);
	kमुक्त(bt);
	वापस ret;
पूर्ण

/* State of the task being unwound. */
काष्ठा unwindme अणु
	पूर्णांक flags;
	पूर्णांक ret;
	काष्ठा task_काष्ठा *task;
	काष्ठा completion task_पढ़ोy;
	रुको_queue_head_t task_wq;
	अचिन्हित दीर्घ sp;
पूर्ण;

अटल काष्ठा unwindme *unwindme;

/* Values of unwindme.flags. */
#घोषणा UWM_DEFAULT		0x0
#घोषणा UWM_THREAD		0x1	/* Unwind a separate task. */
#घोषणा UWM_REGS		0x2	/* Pass regs to test_unwind(). */
#घोषणा UWM_SP			0x4	/* Pass sp to test_unwind(). */
#घोषणा UWM_CALLER		0x8	/* Unwind starting from caller. */
#घोषणा UWM_SWITCH_STACK	0x10	/* Use CALL_ON_STACK. */
#घोषणा UWM_IRQ			0x20	/* Unwind from irq context. */
#घोषणा UWM_PGM			0x40	/* Unwind from program check handler. */

अटल __always_अंतरभूत अचिन्हित दीर्घ get_psw_addr(व्योम)
अणु
	अचिन्हित दीर्घ psw_addr;

	यंत्र अस्थिर(
		"basr	%[psw_addr],0\n"
		: [psw_addr] "=d" (psw_addr));
	वापस psw_addr;
पूर्ण

#अगर_घोषित CONFIG_KPROBES
अटल पूर्णांक pgm_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	काष्ठा unwindme *u = unwindme;

	u->ret = test_unwind(शून्य, (u->flags & UWM_REGS) ? regs : शून्य,
			     (u->flags & UWM_SP) ? u->sp : 0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* This function may or may not appear in the backtrace. */
अटल noअंतरभूत पूर्णांक unwindme_func4(काष्ठा unwindme *u)
अणु
	अगर (!(u->flags & UWM_CALLER))
		u->sp = current_frame_address();
	अगर (u->flags & UWM_THREAD) अणु
		complete(&u->task_पढ़ोy);
		रुको_event(u->task_wq, kthपढ़ो_should_park());
		kthपढ़ो_parkme();
		वापस 0;
#अगर_घोषित CONFIG_KPROBES
	पूर्ण अन्यथा अगर (u->flags & UWM_PGM) अणु
		काष्ठा kprobe kp;
		पूर्णांक ret;

		unwindme = u;
		स_रखो(&kp, 0, माप(kp));
		kp.symbol_name = "do_report_trap";
		kp.pre_handler = pgm_pre_handler;
		ret = रेजिस्टर_kprobe(&kp);
		अगर (ret < 0) अणु
			pr_err("register_kprobe failed %d\n", ret);
			वापस -EINVAL;
		पूर्ण

		/*
		 * trigger specअगरication exception
		 */
		यंत्र अस्थिर(
			"	mvcl	%%r1,%%r1\n"
			"0:	nopr	%%r7\n"
			EX_TABLE(0b, 0b)
			:);

		unरेजिस्टर_kprobe(&kp);
		unwindme = शून्य;
		वापस u->ret;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		काष्ठा pt_regs regs;

		स_रखो(&regs, 0, माप(regs));
		regs.psw.addr = get_psw_addr();
		regs.gprs[15] = current_stack_poपूर्णांकer();
		वापस test_unwind(शून्य,
				   (u->flags & UWM_REGS) ? &regs : शून्य,
				   (u->flags & UWM_SP) ? u->sp : 0);
	पूर्ण
पूर्ण

/* This function may or may not appear in the backtrace. */
अटल noअंतरभूत पूर्णांक unwindme_func3(काष्ठा unwindme *u)
अणु
	u->sp = current_frame_address();
	वापस unwindme_func4(u);
पूर्ण

/* This function must appear in the backtrace. */
अटल noअंतरभूत पूर्णांक unwindme_func2(काष्ठा unwindme *u)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (u->flags & UWM_SWITCH_STACK) अणु
		local_irq_save(flags);
		local_mcck_disable();
		rc = CALL_ON_STACK(unwindme_func3, S390_lowcore.nodat_stack, 1, u);
		local_mcck_enable();
		local_irq_restore(flags);
		वापस rc;
	पूर्ण अन्यथा अणु
		वापस unwindme_func3(u);
	पूर्ण
पूर्ण

/* This function must follow unwindme_func2 in the backtrace. */
अटल noअंतरभूत पूर्णांक unwindme_func1(व्योम *u)
अणु
	वापस unwindme_func2((काष्ठा unwindme *)u);
पूर्ण

अटल व्योम unwindme_समयr_fn(काष्ठा समयr_list *unused)
अणु
	काष्ठा unwindme *u = READ_ONCE(unwindme);

	अगर (u) अणु
		unwindme = शून्य;
		u->task = शून्य;
		u->ret = unwindme_func1(u);
		complete(&u->task_पढ़ोy);
	पूर्ण
पूर्ण

अटल काष्ठा समयr_list unwind_समयr;

अटल पूर्णांक test_unwind_irq(काष्ठा unwindme *u)
अणु
	unwindme = u;
	init_completion(&u->task_पढ़ोy);
	समयr_setup(&unwind_समयr, unwindme_समयr_fn, 0);
	mod_समयr(&unwind_समयr, jअगरfies + 1);
	रुको_क्रम_completion(&u->task_पढ़ोy);
	वापस u->ret;
पूर्ण

/* Spawns a task and passes it to test_unwind(). */
अटल पूर्णांक test_unwind_task(काष्ठा unwindme *u)
अणु
	काष्ठा task_काष्ठा *task;
	पूर्णांक ret;

	/* Initialize thपढ़ो-related fields. */
	init_completion(&u->task_पढ़ोy);
	init_रुकोqueue_head(&u->task_wq);

	/*
	 * Start the task and रुको until it reaches unwindme_func4() and sleeps
	 * in (task_पढ़ोy, unwind_करोne] range.
	 */
	task = kthपढ़ो_run(unwindme_func1, u, "%s", __func__);
	अगर (IS_ERR(task)) अणु
		pr_err("kthread_run() failed\n");
		वापस PTR_ERR(task);
	पूर्ण
	/*
	 * Make sure task reaches unwindme_func4 beक्रमe parking it,
	 * we might park it beक्रमe kthपढ़ो function has been executed otherwise
	 */
	रुको_क्रम_completion(&u->task_पढ़ोy);
	kthपढ़ो_park(task);
	/* Unwind. */
	ret = test_unwind(task, शून्य, (u->flags & UWM_SP) ? u->sp : 0);
	kthपढ़ो_stop(task);
	वापस ret;
पूर्ण

अटल पूर्णांक test_unwind_flags(पूर्णांक flags)
अणु
	काष्ठा unwindme u;

	u.flags = flags;
	अगर (u.flags & UWM_THREAD)
		वापस test_unwind_task(&u);
	अन्यथा अगर (u.flags & UWM_IRQ)
		वापस test_unwind_irq(&u);
	अन्यथा
		वापस unwindme_func1(&u);
पूर्ण

अटल पूर्णांक test_unwind_init(व्योम)
अणु
	पूर्णांक failed = 0;
	पूर्णांक total = 0;

#घोषणा TEST(flags)							\
करो अणु									\
	pr_info("[ RUN      ] " #flags "\n");				\
	total++;							\
	अगर (!test_unwind_flags((flags))) अणु				\
		pr_info("[       OK ] " #flags "\n");			\
	पूर्ण अन्यथा अणु							\
		pr_err("[  FAILED  ] " #flags "\n");			\
		failed++;						\
	पूर्ण								\
पूर्ण जबतक (0)

	pr_info("running stack unwinder tests");
	TEST(UWM_DEFAULT);
	TEST(UWM_SP);
	TEST(UWM_REGS);
	TEST(UWM_SWITCH_STACK);
	TEST(UWM_SP | UWM_REGS);
	TEST(UWM_CALLER | UWM_SP);
	TEST(UWM_CALLER | UWM_SP | UWM_REGS);
	TEST(UWM_CALLER | UWM_SP | UWM_REGS | UWM_SWITCH_STACK);
	TEST(UWM_THREAD);
	TEST(UWM_THREAD | UWM_SP);
	TEST(UWM_THREAD | UWM_CALLER | UWM_SP);
	TEST(UWM_IRQ);
	TEST(UWM_IRQ | UWM_SWITCH_STACK);
	TEST(UWM_IRQ | UWM_SP);
	TEST(UWM_IRQ | UWM_REGS);
	TEST(UWM_IRQ | UWM_SP | UWM_REGS);
	TEST(UWM_IRQ | UWM_CALLER | UWM_SP);
	TEST(UWM_IRQ | UWM_CALLER | UWM_SP | UWM_REGS);
	TEST(UWM_IRQ | UWM_CALLER | UWM_SP | UWM_REGS | UWM_SWITCH_STACK);
#अगर_घोषित CONFIG_KPROBES
	TEST(UWM_PGM);
	TEST(UWM_PGM | UWM_SP);
	TEST(UWM_PGM | UWM_REGS);
	TEST(UWM_PGM | UWM_SP | UWM_REGS);
#पूर्ण_अगर
#अघोषित TEST
	अगर (failed) अणु
		pr_err("%d of %d stack unwinder tests failed", failed, total);
		WARN(1, "%d of %d stack unwinder tests failed", failed, total);
	पूर्ण अन्यथा अणु
		pr_info("all %d stack unwinder tests passed", total);
	पूर्ण

	वापस failed ? -EINVAL : 0;
पूर्ण

अटल व्योम test_unwind_निकास(व्योम)
अणु
पूर्ण

module_init(test_unwind_init);
module_निकास(test_unwind_निकास);
MODULE_LICENSE("GPL");
