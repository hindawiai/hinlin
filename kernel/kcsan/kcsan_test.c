<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * KCSAN test with various race scenarious to test runसमय behaviour. Since the
 * पूर्णांकerface with which KCSAN's reports are obtained is via the console, this is
 * the output we should verअगरy. For each test हाल checks the presence (or
 * असलence) of generated reports. Relies on 'console' tracepoपूर्णांक to capture
 * reports as they appear in the kernel log.
 *
 * Makes use of KUnit क्रम test organization, and the Torture framework क्रम test
 * thपढ़ो control.
 *
 * Copyright (C) 2020, Google LLC.
 * Author: Marco Elver <elver@google.com>
 */

#घोषणा pr_fmt(fmt) "kcsan_test: " fmt

#समावेश <kunit/test.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kcsan-checks.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/torture.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/types.h>
#समावेश <trace/events/prपूर्णांकk.h>

#अगर_घोषित CONFIG_CC_HAS_TSAN_COMPOUND_READ_BEFORE_WRITE
#घोषणा __KCSAN_ACCESS_RW(alt) (KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE)
#अन्यथा
#घोषणा __KCSAN_ACCESS_RW(alt) (alt)
#पूर्ण_अगर

/* Poपूर्णांकs to current test-हाल memory access "kernels". */
अटल व्योम (*access_kernels[2])(व्योम);

अटल काष्ठा task_काष्ठा **thपढ़ोs; /* Lists of thपढ़ोs. */
अटल अचिन्हित दीर्घ end_समय;       /* End समय of test. */

/* Report as observed from console. */
अटल काष्ठा अणु
	spinlock_t lock;
	पूर्णांक nlines;
	अक्षर lines[3][512];
पूर्ण observed = अणु
	.lock = __SPIN_LOCK_UNLOCKED(observed.lock),
पूर्ण;

/* Setup test checking loop. */
अटल __no_kcsan अंतरभूत व्योम
begin_test_checks(व्योम (*func1)(व्योम), व्योम (*func2)(व्योम))
अणु
	kcsan_disable_current();

	/*
	 * Require at least as दीर्घ as KCSAN_REPORT_ONCE_IN_MS, to ensure at
	 * least one race is reported.
	 */
	end_समय = jअगरfies + msecs_to_jअगरfies(CONFIG_KCSAN_REPORT_ONCE_IN_MS + 500);

	/* Signal start; release potential initialization of shared data. */
	smp_store_release(&access_kernels[0], func1);
	smp_store_release(&access_kernels[1], func2);
पूर्ण

/* End test checking loop. */
अटल __no_kcsan अंतरभूत bool
end_test_checks(bool stop)
अणु
	अगर (!stop && समय_beक्रमe(jअगरfies, end_समय)) अणु
		/* Continue checking */
		might_sleep();
		वापस false;
	पूर्ण

	kcsan_enable_current();
	वापस true;
पूर्ण

/*
 * Probe क्रम console output: checks अगर a race was reported, and obtains observed
 * lines of पूर्णांकerest.
 */
__no_kcsan
अटल व्योम probe_console(व्योम *ignore, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक nlines;

	/*
	 * Note that KCSAN reports under a global lock, so we करो not risk the
	 * possibility of having multiple reports पूर्णांकerleaved. If that were the
	 * हाल, we'd expect tests to fail.
	 */

	spin_lock_irqsave(&observed.lock, flags);
	nlines = observed.nlines;

	अगर (strnstr(buf, "BUG: KCSAN: ", len) && strnstr(buf, "test_", len)) अणु
		/*
		 * KCSAN report and related to the test.
		 *
		 * The provided @buf is not NUL-terminated; copy no more than
		 * @len bytes and let strscpy() add the missing NUL-terminator.
		 */
		strscpy(observed.lines[0], buf, min(len + 1, माप(observed.lines[0])));
		nlines = 1;
	पूर्ण अन्यथा अगर ((nlines == 1 || nlines == 2) && strnstr(buf, "bytes by", len)) अणु
		strscpy(observed.lines[nlines++], buf, min(len + 1, माप(observed.lines[0])));

		अगर (strnstr(buf, "race at unknown origin", len)) अणु
			अगर (WARN_ON(nlines != 2))
				जाओ out;

			/* No second line of पूर्णांकerest. */
			म_नकल(observed.lines[nlines++], "<none>");
		पूर्ण
	पूर्ण

out:
	WRITE_ONCE(observed.nlines, nlines); /* Publish new nlines. */
	spin_unlock_irqrestore(&observed.lock, flags);
पूर्ण

/* Check अगर a report related to the test exists. */
__no_kcsan
अटल bool report_available(व्योम)
अणु
	वापस READ_ONCE(observed.nlines) == ARRAY_SIZE(observed.lines);
पूर्ण

/* Report inक्रमmation we expect in a report. */
काष्ठा expect_report अणु
	/* Access inक्रमmation of both accesses. */
	काष्ठा अणु
		व्योम *fn;    /* Function poपूर्णांकer to expected function of top frame. */
		व्योम *addr;  /* Address of access; unchecked अगर शून्य. */
		माप_प्रकार size; /* Size of access; unchecked अगर @addr is शून्य. */
		पूर्णांक type;    /* Access type, see KCSAN_ACCESS definitions. */
	पूर्ण access[2];
पूर्ण;

/* Check observed report matches inक्रमmation in @r. */
__no_kcsan
अटल bool report_matches(स्थिर काष्ठा expect_report *r)
अणु
	स्थिर bool is_निश्चित = (r->access[0].type | r->access[1].type) & KCSAN_ACCESS_ASSERT;
	bool ret = false;
	अचिन्हित दीर्घ flags;
	typeof(observed.lines) expect;
	स्थिर अक्षर *end;
	अक्षर *cur;
	पूर्णांक i;

	/* Doubled-checked locking. */
	अगर (!report_available())
		वापस false;

	/* Generate expected report contents. */

	/* Title */
	cur = expect[0];
	end = &expect[0][माप(expect[0]) - 1];
	cur += scnम_लिखो(cur, end - cur, "BUG: KCSAN: %s in ",
			 is_निश्चित ? "assert: race" : "data-race");
	अगर (r->access[1].fn) अणु
		अक्षर पंचांगp[2][64];
		पूर्णांक cmp;

		/* Expect lexographically sorted function names in title. */
		scnम_लिखो(पंचांगp[0], माप(पंचांगp[0]), "%pS", r->access[0].fn);
		scnम_लिखो(पंचांगp[1], माप(पंचांगp[1]), "%pS", r->access[1].fn);
		cmp = म_भेद(पंचांगp[0], पंचांगp[1]);
		cur += scnम_लिखो(cur, end - cur, "%ps / %ps",
				 cmp < 0 ? r->access[0].fn : r->access[1].fn,
				 cmp < 0 ? r->access[1].fn : r->access[0].fn);
	पूर्ण अन्यथा अणु
		scnम_लिखो(cur, end - cur, "%pS", r->access[0].fn);
		/* The exact offset won't match, हटाओ it. */
		cur = म_अक्षर(expect[0], '+');
		अगर (cur)
			*cur = '\0';
	पूर्ण

	/* Access 1 */
	cur = expect[1];
	end = &expect[1][माप(expect[1]) - 1];
	अगर (!r->access[1].fn)
		cur += scnम_लिखो(cur, end - cur, "race at unknown origin, with ");

	/* Access 1 & 2 */
	क्रम (i = 0; i < 2; ++i) अणु
		स्थिर पूर्णांक ty = r->access[i].type;
		स्थिर अक्षर *स्थिर access_type =
			(ty & KCSAN_ACCESS_ASSERT) ?
				      ((ty & KCSAN_ACCESS_WRITE) ?
					       "assert no accesses" :
					       "assert no writes") :
				      ((ty & KCSAN_ACCESS_WRITE) ?
					       ((ty & KCSAN_ACCESS_COMPOUND) ?
							"read-write" :
							"write") :
					       "read");
		स्थिर अक्षर *स्थिर access_type_aux =
			(ty & KCSAN_ACCESS_ATOMIC) ?
				      " (marked)" :
				      ((ty & KCSAN_ACCESS_SCOPED) ? " (scoped)" : "");

		अगर (i == 1) अणु
			/* Access 2 */
			cur = expect[2];
			end = &expect[2][माप(expect[2]) - 1];

			अगर (!r->access[1].fn) अणु
				/* Dummy string अगर no second access is available. */
				म_नकल(cur, "<none>");
				अवरोध;
			पूर्ण
		पूर्ण

		cur += scnम_लिखो(cur, end - cur, "%s%s to ", access_type,
				 access_type_aux);

		अगर (r->access[i].addr) /* Address is optional. */
			cur += scnम_लिखो(cur, end - cur, "0x%px of %zu bytes",
					 r->access[i].addr, r->access[i].size);
	पूर्ण

	spin_lock_irqsave(&observed.lock, flags);
	अगर (!report_available())
		जाओ out; /* A new report is being captured. */

	/* Finally match expected output to what we actually observed. */
	ret = म_माला(observed.lines[0], expect[0]) &&
	      /* Access info may appear in any order. */
	      ((म_माला(observed.lines[1], expect[1]) &&
		म_माला(observed.lines[2], expect[2])) ||
	       (म_माला(observed.lines[1], expect[2]) &&
		म_माला(observed.lines[2], expect[1])));
out:
	spin_unlock_irqrestore(&observed.lock, flags);
	वापस ret;
पूर्ण

/* ===== Test kernels ===== */

अटल दीर्घ test_sink;
अटल दीर्घ test_var;
/* @test_array should be large enough to fall पूर्णांकo multiple watchpoपूर्णांक slots. */
अटल दीर्घ test_array[3 * PAGE_SIZE / माप(दीर्घ)];
अटल काष्ठा अणु
	दीर्घ val[8];
पूर्ण test_काष्ठा;
अटल DEFINE_SEQLOCK(test_seqlock);

/*
 * Helper to aव्योम compiler optimizing out पढ़ोs, and to generate source values
 * क्रम ग_लिखोs.
 */
__no_kcsan
अटल noअंतरभूत व्योम sink_value(दीर्घ v) अणु WRITE_ONCE(test_sink, v); पूर्ण

अटल noअंतरभूत व्योम test_kernel_पढ़ो(व्योम) अणु sink_value(test_var); पूर्ण

अटल noअंतरभूत व्योम test_kernel_ग_लिखो(व्योम)
अणु
	test_var = READ_ONCE_NOCHECK(test_sink) + 1;
पूर्ण

अटल noअंतरभूत व्योम test_kernel_ग_लिखो_nochange(व्योम) अणु test_var = 42; पूर्ण

/* Suffixed by value-change exception filter. */
अटल noअंतरभूत व्योम test_kernel_ग_लिखो_nochange_rcu(व्योम) अणु test_var = 42; पूर्ण

अटल noअंतरभूत व्योम test_kernel_पढ़ो_atomic(व्योम)
अणु
	sink_value(READ_ONCE(test_var));
पूर्ण

अटल noअंतरभूत व्योम test_kernel_ग_लिखो_atomic(व्योम)
अणु
	WRITE_ONCE(test_var, READ_ONCE_NOCHECK(test_sink) + 1);
पूर्ण

अटल noअंतरभूत व्योम test_kernel_atomic_rmw(व्योम)
अणु
	/* Use builtin, so we can set up the "bad" atomic/non-atomic scenario. */
	__atomic_fetch_add(&test_var, 1, __ATOMIC_RELAXED);
पूर्ण

__no_kcsan
अटल noअंतरभूत व्योम test_kernel_ग_लिखो_uninstrumented(व्योम) अणु test_var++; पूर्ण

अटल noअंतरभूत व्योम test_kernel_data_race(व्योम) अणु data_race(test_var++); पूर्ण

अटल noअंतरभूत व्योम test_kernel_निश्चित_ग_लिखोr(व्योम)
अणु
	ASSERT_EXCLUSIVE_WRITER(test_var);
पूर्ण

अटल noअंतरभूत व्योम test_kernel_निश्चित_access(व्योम)
अणु
	ASSERT_EXCLUSIVE_ACCESS(test_var);
पूर्ण

#घोषणा TEST_CHANGE_BITS 0xff00ff00

अटल noअंतरभूत व्योम test_kernel_change_bits(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS)) अणु
		/*
		 * Aव्योम race of unknown origin क्रम this test, just pretend they
		 * are atomic.
		 */
		kcsan_nestable_atomic_begin();
		test_var ^= TEST_CHANGE_BITS;
		kcsan_nestable_atomic_end();
	पूर्ण अन्यथा
		WRITE_ONCE(test_var, READ_ONCE(test_var) ^ TEST_CHANGE_BITS);
पूर्ण

अटल noअंतरभूत व्योम test_kernel_निश्चित_bits_change(व्योम)
अणु
	ASSERT_EXCLUSIVE_BITS(test_var, TEST_CHANGE_BITS);
पूर्ण

अटल noअंतरभूत व्योम test_kernel_निश्चित_bits_nochange(व्योम)
अणु
	ASSERT_EXCLUSIVE_BITS(test_var, ~TEST_CHANGE_BITS);
पूर्ण

/* To check that scoped निश्चितions करो trigger anywhere in scope. */
अटल noअंतरभूत व्योम test_enter_scope(व्योम)
अणु
	पूर्णांक x = 0;

	/* Unrelated accesses to scoped निश्चित. */
	READ_ONCE(test_sink);
	kcsan_check_पढ़ो(&x, माप(x));
पूर्ण

अटल noअंतरभूत व्योम test_kernel_निश्चित_ग_लिखोr_scoped(व्योम)
अणु
	ASSERT_EXCLUSIVE_WRITER_SCOPED(test_var);
	test_enter_scope();
पूर्ण

अटल noअंतरभूत व्योम test_kernel_निश्चित_access_scoped(व्योम)
अणु
	ASSERT_EXCLUSIVE_ACCESS_SCOPED(test_var);
	test_enter_scope();
पूर्ण

अटल noअंतरभूत व्योम test_kernel_rmw_array(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(test_array); ++i)
		test_array[i]++;
पूर्ण

अटल noअंतरभूत व्योम test_kernel_ग_लिखो_काष्ठा(व्योम)
अणु
	kcsan_check_ग_लिखो(&test_काष्ठा, माप(test_काष्ठा));
	kcsan_disable_current();
	test_काष्ठा.val[3]++; /* induce value change */
	kcsan_enable_current();
पूर्ण

अटल noअंतरभूत व्योम test_kernel_ग_लिखो_काष्ठा_part(व्योम)
अणु
	test_काष्ठा.val[3] = 42;
पूर्ण

अटल noअंतरभूत व्योम test_kernel_पढ़ो_काष्ठा_zero_size(व्योम)
अणु
	kcsan_check_पढ़ो(&test_काष्ठा.val[3], 0);
पूर्ण

अटल noअंतरभूत व्योम test_kernel_jअगरfies_पढ़ोer(व्योम)
अणु
	sink_value((दीर्घ)jअगरfies);
पूर्ण

अटल noअंतरभूत व्योम test_kernel_seqlock_पढ़ोer(व्योम)
अणु
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqbegin(&test_seqlock);
		sink_value(test_var);
	पूर्ण जबतक (पढ़ो_seqretry(&test_seqlock, seq));
पूर्ण

अटल noअंतरभूत व्योम test_kernel_seqlock_ग_लिखोr(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_seqlock_irqsave(&test_seqlock, flags);
	test_var++;
	ग_लिखो_sequnlock_irqrestore(&test_seqlock, flags);
पूर्ण

अटल noअंतरभूत व्योम test_kernel_atomic_builtins(व्योम)
अणु
	/*
	 * Generate concurrent accesses, expecting no reports, ensuring KCSAN
	 * treats builtin atomics as actually atomic.
	 */
	__atomic_load_n(&test_var, __ATOMIC_RELAXED);
पूर्ण

/* ===== Test हालs ===== */

/* Simple test with normal data race. */
__no_kcsan
अटल व्योम test_basic(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_ग_लिखो, &test_var, माप(test_var), KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा expect_report never = अणु
		.access = अणु
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;
	bool match_never = false;

	begin_test_checks(test_kernel_ग_लिखो, test_kernel_पढ़ो);
	करो अणु
		match_expect |= report_matches(&expect);
		match_never = report_matches(&never);
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_TRUE(test, match_expect);
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

/*
 * Stress KCSAN with lots of concurrent races on dअगरferent addresses until
 * समयout.
 */
__no_kcsan
अटल व्योम test_concurrent_races(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			/* शून्य will match any address. */
			अणु test_kernel_rmw_array, शून्य, 0, __KCSAN_ACCESS_RW(KCSAN_ACCESS_WRITE) पूर्ण,
			अणु test_kernel_rmw_array, शून्य, 0, __KCSAN_ACCESS_RW(0) पूर्ण,
		पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा expect_report never = अणु
		.access = अणु
			अणु test_kernel_rmw_array, शून्य, 0, 0 पूर्ण,
			अणु test_kernel_rmw_array, शून्य, 0, 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;
	bool match_never = false;

	begin_test_checks(test_kernel_rmw_array, test_kernel_rmw_array);
	करो अणु
		match_expect |= report_matches(&expect);
		match_never |= report_matches(&never);
	पूर्ण जबतक (!end_test_checks(false));
	KUNIT_EXPECT_TRUE(test, match_expect); /* Sanity check matches exist. */
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

/* Test the KCSAN_REPORT_VALUE_CHANGE_ONLY option. */
__no_kcsan
अटल व्योम test_novalue_change(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_ग_लिखो_nochange, &test_var, माप(test_var), KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_ग_लिखो_nochange, test_kernel_पढ़ो);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	अगर (IS_ENABLED(CONFIG_KCSAN_REPORT_VALUE_CHANGE_ONLY))
		KUNIT_EXPECT_FALSE(test, match_expect);
	अन्यथा
		KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

/*
 * Test that the rules where the KCSAN_REPORT_VALUE_CHANGE_ONLY option should
 * never apply work.
 */
__no_kcsan
अटल व्योम test_novalue_change_exception(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_ग_लिखो_nochange_rcu, &test_var, माप(test_var), KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_ग_लिखो_nochange_rcu, test_kernel_पढ़ो);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

/* Test that data races of unknown origin are reported. */
__no_kcsan
अटल व्योम test_unknown_origin(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_ग_लिखो_uninstrumented, test_kernel_पढ़ो);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	अगर (IS_ENABLED(CONFIG_KCSAN_REPORT_RACE_UNKNOWN_ORIGIN))
		KUNIT_EXPECT_TRUE(test, match_expect);
	अन्यथा
		KUNIT_EXPECT_FALSE(test, match_expect);
पूर्ण

/* Test KCSAN_ASSUME_PLAIN_WRITES_ATOMIC अगर it is selected. */
__no_kcsan
अटल व्योम test_ग_लिखो_ग_लिखो_assume_atomic(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_ग_लिखो, &test_var, माप(test_var), KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_ग_लिखो, &test_var, माप(test_var), KCSAN_ACCESS_WRITE पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_ग_लिखो, test_kernel_ग_लिखो);
	करो अणु
		sink_value(READ_ONCE(test_var)); /* induce value-change */
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	अगर (IS_ENABLED(CONFIG_KCSAN_ASSUME_PLAIN_WRITES_ATOMIC))
		KUNIT_EXPECT_FALSE(test, match_expect);
	अन्यथा
		KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

/*
 * Test that data races with ग_लिखोs larger than word-size are always reported,
 * even अगर KCSAN_ASSUME_PLAIN_WRITES_ATOMIC is selected.
 */
__no_kcsan
अटल व्योम test_ग_लिखो_ग_लिखो_काष्ठा(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_ग_लिखो_काष्ठा, &test_काष्ठा, माप(test_काष्ठा), KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_ग_लिखो_काष्ठा, &test_काष्ठा, माप(test_काष्ठा), KCSAN_ACCESS_WRITE पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_ग_लिखो_काष्ठा, test_kernel_ग_लिखो_काष्ठा);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

/*
 * Test that data races where only one ग_लिखो is larger than word-size are always
 * reported, even अगर KCSAN_ASSUME_PLAIN_WRITES_ATOMIC is selected.
 */
__no_kcsan
अटल व्योम test_ग_लिखो_ग_लिखो_काष्ठा_part(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_ग_लिखो_काष्ठा, &test_काष्ठा, माप(test_काष्ठा), KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_ग_लिखो_काष्ठा_part, &test_काष्ठा.val[3], माप(test_काष्ठा.val[3]), KCSAN_ACCESS_WRITE पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_ग_लिखो_काष्ठा, test_kernel_ग_लिखो_काष्ठा_part);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

/* Test that races with atomic accesses never result in reports. */
__no_kcsan
अटल व्योम test_पढ़ो_atomic_ग_लिखो_atomic(काष्ठा kunit *test)
अणु
	bool match_never = false;

	begin_test_checks(test_kernel_पढ़ो_atomic, test_kernel_ग_लिखो_atomic);
	करो अणु
		match_never = report_available();
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

/* Test that a race with an atomic and plain access result in reports. */
__no_kcsan
अटल व्योम test_पढ़ो_plain_atomic_ग_लिखो(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
			अणु test_kernel_ग_लिखो_atomic, &test_var, माप(test_var), KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ATOMIC पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	अगर (IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS))
		वापस;

	begin_test_checks(test_kernel_पढ़ो, test_kernel_ग_लिखो_atomic);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

/* Test that atomic RMWs generate correct report. */
__no_kcsan
अटल व्योम test_पढ़ो_plain_atomic_rmw(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
			अणु test_kernel_atomic_rmw, &test_var, माप(test_var),
				KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WRITE | KCSAN_ACCESS_ATOMIC पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	अगर (IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS))
		वापस;

	begin_test_checks(test_kernel_पढ़ो, test_kernel_atomic_rmw);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

/* Zero-sized accesses should never cause data race reports. */
__no_kcsan
अटल व्योम test_zero_size_access(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_ग_लिखो_काष्ठा, &test_काष्ठा, माप(test_काष्ठा), KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_ग_लिखो_काष्ठा, &test_काष्ठा, माप(test_काष्ठा), KCSAN_ACCESS_WRITE पूर्ण,
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा expect_report never = अणु
		.access = अणु
			अणु test_kernel_ग_लिखो_काष्ठा, &test_काष्ठा, माप(test_काष्ठा), KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_पढ़ो_काष्ठा_zero_size, &test_काष्ठा.val[3], 0, 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;
	bool match_never = false;

	begin_test_checks(test_kernel_ग_लिखो_काष्ठा, test_kernel_पढ़ो_काष्ठा_zero_size);
	करो अणु
		match_expect |= report_matches(&expect);
		match_never = report_matches(&never);
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_TRUE(test, match_expect); /* Sanity check. */
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

/* Test the data_race() macro. */
__no_kcsan
अटल व्योम test_data_race(काष्ठा kunit *test)
अणु
	bool match_never = false;

	begin_test_checks(test_kernel_data_race, test_kernel_data_race);
	करो अणु
		match_never = report_available();
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

__no_kcsan
अटल व्योम test_निश्चित_exclusive_ग_लिखोr(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_निश्चित_ग_लिखोr, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT पूर्ण,
			अणु test_kernel_ग_लिखो_nochange, &test_var, माप(test_var), KCSAN_ACCESS_WRITE पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_निश्चित_ग_लिखोr, test_kernel_ग_लिखो_nochange);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

__no_kcsan
अटल व्योम test_निश्चित_exclusive_access(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_निश्चित_access, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT | KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_निश्चित_access, test_kernel_पढ़ो);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

__no_kcsan
अटल व्योम test_निश्चित_exclusive_access_ग_लिखोr(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect_access_ग_लिखोr = अणु
		.access = अणु
			अणु test_kernel_निश्चित_access, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT | KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_निश्चित_ग_लिखोr, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT पूर्ण,
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा expect_report expect_access_access = अणु
		.access = अणु
			अणु test_kernel_निश्चित_access, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT | KCSAN_ACCESS_WRITE पूर्ण,
			अणु test_kernel_निश्चित_access, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT | KCSAN_ACCESS_WRITE पूर्ण,
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा expect_report never = अणु
		.access = अणु
			अणु test_kernel_निश्चित_ग_लिखोr, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT पूर्ण,
			अणु test_kernel_निश्चित_ग_लिखोr, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect_access_ग_लिखोr = false;
	bool match_expect_access_access = false;
	bool match_never = false;

	begin_test_checks(test_kernel_निश्चित_access, test_kernel_निश्चित_ग_लिखोr);
	करो अणु
		match_expect_access_ग_लिखोr |= report_matches(&expect_access_ग_लिखोr);
		match_expect_access_access |= report_matches(&expect_access_access);
		match_never |= report_matches(&never);
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_TRUE(test, match_expect_access_ग_लिखोr);
	KUNIT_EXPECT_TRUE(test, match_expect_access_access);
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

__no_kcsan
अटल व्योम test_निश्चित_exclusive_bits_change(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.access = अणु
			अणु test_kernel_निश्चित_bits_change, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT पूर्ण,
			अणु test_kernel_change_bits, &test_var, माप(test_var),
				KCSAN_ACCESS_WRITE | (IS_ENABLED(CONFIG_KCSAN_IGNORE_ATOMICS) ? 0 : KCSAN_ACCESS_ATOMIC) पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect = false;

	begin_test_checks(test_kernel_निश्चित_bits_change, test_kernel_change_bits);
	करो अणु
		match_expect = report_matches(&expect);
	पूर्ण जबतक (!end_test_checks(match_expect));
	KUNIT_EXPECT_TRUE(test, match_expect);
पूर्ण

__no_kcsan
अटल व्योम test_निश्चित_exclusive_bits_nochange(काष्ठा kunit *test)
अणु
	bool match_never = false;

	begin_test_checks(test_kernel_निश्चित_bits_nochange, test_kernel_change_bits);
	करो अणु
		match_never = report_available();
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

__no_kcsan
अटल व्योम test_निश्चित_exclusive_ग_लिखोr_scoped(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect_start = अणु
		.access = अणु
			अणु test_kernel_निश्चित_ग_लिखोr_scoped, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT | KCSAN_ACCESS_SCOPED पूर्ण,
			अणु test_kernel_ग_लिखो_nochange, &test_var, माप(test_var), KCSAN_ACCESS_WRITE पूर्ण,
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा expect_report expect_anywhere = अणु
		.access = अणु
			अणु test_enter_scope, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT | KCSAN_ACCESS_SCOPED पूर्ण,
			अणु test_kernel_ग_लिखो_nochange, &test_var, माप(test_var), KCSAN_ACCESS_WRITE पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect_start = false;
	bool match_expect_anywhere = false;

	begin_test_checks(test_kernel_निश्चित_ग_लिखोr_scoped, test_kernel_ग_लिखो_nochange);
	करो अणु
		match_expect_start |= report_matches(&expect_start);
		match_expect_anywhere |= report_matches(&expect_anywhere);
	पूर्ण जबतक (!end_test_checks(match_expect_start && match_expect_anywhere));
	KUNIT_EXPECT_TRUE(test, match_expect_start);
	KUNIT_EXPECT_TRUE(test, match_expect_anywhere);
पूर्ण

__no_kcsan
अटल व्योम test_निश्चित_exclusive_access_scoped(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect_start1 = अणु
		.access = अणु
			अणु test_kernel_निश्चित_access_scoped, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT | KCSAN_ACCESS_WRITE | KCSAN_ACCESS_SCOPED पूर्ण,
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	स्थिर काष्ठा expect_report expect_start2 = अणु
		.access = अणु expect_start1.access[0], expect_start1.access[0] पूर्ण,
	पूर्ण;
	स्थिर काष्ठा expect_report expect_inscope = अणु
		.access = अणु
			अणु test_enter_scope, &test_var, माप(test_var), KCSAN_ACCESS_ASSERT | KCSAN_ACCESS_WRITE | KCSAN_ACCESS_SCOPED पूर्ण,
			अणु test_kernel_पढ़ो, &test_var, माप(test_var), 0 पूर्ण,
		पूर्ण,
	पूर्ण;
	bool match_expect_start = false;
	bool match_expect_inscope = false;

	begin_test_checks(test_kernel_निश्चित_access_scoped, test_kernel_पढ़ो);
	end_समय += msecs_to_jअगरfies(1000); /* This test requires a bit more समय. */
	करो अणु
		match_expect_start |= report_matches(&expect_start1) || report_matches(&expect_start2);
		match_expect_inscope |= report_matches(&expect_inscope);
	पूर्ण जबतक (!end_test_checks(match_expect_start && match_expect_inscope));
	KUNIT_EXPECT_TRUE(test, match_expect_start);
	KUNIT_EXPECT_TRUE(test, match_expect_inscope);
पूर्ण

/*
 * jअगरfies is special (declared to be अस्थिर) and its accesses are typically
 * not marked; this test ensures that the compiler nor KCSAN माला_लो confused about
 * jअगरfies's declaration on dअगरferent architectures.
 */
__no_kcsan
अटल व्योम test_jअगरfies_noreport(काष्ठा kunit *test)
अणु
	bool match_never = false;

	begin_test_checks(test_kernel_jअगरfies_पढ़ोer, test_kernel_jअगरfies_पढ़ोer);
	करो अणु
		match_never = report_available();
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

/* Test that racing accesses in seqlock critical sections are not reported. */
__no_kcsan
अटल व्योम test_seqlock_noreport(काष्ठा kunit *test)
अणु
	bool match_never = false;

	begin_test_checks(test_kernel_seqlock_पढ़ोer, test_kernel_seqlock_ग_लिखोr);
	करो अणु
		match_never = report_available();
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

/*
 * Test atomic builtins work and required instrumentation functions exist. We
 * also test that KCSAN understands they're atomic by racing with them via
 * test_kernel_atomic_builtins(), and expect no reports.
 *
 * The atomic builtins _SHOULD NOT_ be used in normal kernel code!
 */
अटल व्योम test_atomic_builtins(काष्ठा kunit *test)
अणु
	bool match_never = false;

	begin_test_checks(test_kernel_atomic_builtins, test_kernel_atomic_builtins);
	करो अणु
		दीर्घ पंचांगp;

		kcsan_enable_current();

		__atomic_store_n(&test_var, 42L, __ATOMIC_RELAXED);
		KUNIT_EXPECT_EQ(test, 42L, __atomic_load_n(&test_var, __ATOMIC_RELAXED));

		KUNIT_EXPECT_EQ(test, 42L, __atomic_exchange_n(&test_var, 20, __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, 20L, test_var);

		पंचांगp = 20L;
		KUNIT_EXPECT_TRUE(test, __atomic_compare_exchange_n(&test_var, &पंचांगp, 30L,
								    0, __ATOMIC_RELAXED,
								    __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, पंचांगp, 20L);
		KUNIT_EXPECT_EQ(test, test_var, 30L);
		KUNIT_EXPECT_FALSE(test, __atomic_compare_exchange_n(&test_var, &पंचांगp, 40L,
								     1, __ATOMIC_RELAXED,
								     __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, पंचांगp, 30L);
		KUNIT_EXPECT_EQ(test, test_var, 30L);

		KUNIT_EXPECT_EQ(test, 30L, __atomic_fetch_add(&test_var, 1, __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, 31L, __atomic_fetch_sub(&test_var, 1, __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, 30L, __atomic_fetch_and(&test_var, 0xf, __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, 14L, __atomic_fetch_xor(&test_var, 0xf, __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, 1L, __atomic_fetch_or(&test_var, 0xf0, __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, 241L, __atomic_fetch_nand(&test_var, 0xf, __ATOMIC_RELAXED));
		KUNIT_EXPECT_EQ(test, -2L, test_var);

		__atomic_thपढ़ो_fence(__ATOMIC_SEQ_CST);
		__atomic_संकेत_fence(__ATOMIC_SEQ_CST);

		kcsan_disable_current();

		match_never = report_available();
	पूर्ण जबतक (!end_test_checks(match_never));
	KUNIT_EXPECT_FALSE(test, match_never);
पूर्ण

/*
 * Generate thपढ़ो counts क्रम all test हालs. Values generated are in पूर्णांकerval
 * [2, 5] followed by exponentially increasing thपढ़ो counts from 8 to 32.
 *
 * The thपढ़ो counts are chosen to cover potentially पूर्णांकeresting boundaries and
 * corner हालs (2 to 5), and then stress the प्रणाली with larger counts.
 */
अटल स्थिर व्योम *nthपढ़ोs_gen_params(स्थिर व्योम *prev, अक्षर *desc)
अणु
	दीर्घ nthपढ़ोs = (दीर्घ)prev;

	अगर (nthपढ़ोs < 0 || nthपढ़ोs >= 32)
		nthपढ़ोs = 0; /* stop */
	अन्यथा अगर (!nthपढ़ोs)
		nthपढ़ोs = 2; /* initial value */
	अन्यथा अगर (nthपढ़ोs < 5)
		nthपढ़ोs++;
	अन्यथा अगर (nthपढ़ोs == 5)
		nthपढ़ोs = 8;
	अन्यथा
		nthपढ़ोs *= 2;

	अगर (!IS_ENABLED(CONFIG_PREEMPT) || !IS_ENABLED(CONFIG_KCSAN_INTERRUPT_WATCHER)) अणु
		/*
		 * Without any preemption, keep 2 CPUs मुक्त क्रम other tasks, one
		 * of which is the मुख्य test हाल function checking क्रम
		 * completion or failure.
		 */
		स्थिर दीर्घ min_unused_cpus = IS_ENABLED(CONFIG_PREEMPT_NONE) ? 2 : 0;
		स्थिर दीर्घ min_required_cpus = 2 + min_unused_cpus;

		अगर (num_online_cpus() < min_required_cpus) अणु
			pr_err_once("Too few online CPUs (%u < %ld) for test\n",
				    num_online_cpus(), min_required_cpus);
			nthपढ़ोs = 0;
		पूर्ण अन्यथा अगर (nthपढ़ोs >= num_online_cpus() - min_unused_cpus) अणु
			/* Use negative value to indicate last param. */
			nthपढ़ोs = -(num_online_cpus() - min_unused_cpus);
			pr_warn_once("Limiting number of threads to %ld (only %d online CPUs)\n",
				     -nthपढ़ोs, num_online_cpus());
		पूर्ण
	पूर्ण

	snम_लिखो(desc, KUNIT_PARAM_DESC_SIZE, "threads=%ld", असल(nthपढ़ोs));
	वापस (व्योम *)nthपढ़ोs;
पूर्ण

#घोषणा KCSAN_KUNIT_CASE(test_name) KUNIT_CASE_PARAM(test_name, nthपढ़ोs_gen_params)
अटल काष्ठा kunit_हाल kcsan_test_हालs[] = अणु
	KCSAN_KUNIT_CASE(test_basic),
	KCSAN_KUNIT_CASE(test_concurrent_races),
	KCSAN_KUNIT_CASE(test_novalue_change),
	KCSAN_KUNIT_CASE(test_novalue_change_exception),
	KCSAN_KUNIT_CASE(test_unknown_origin),
	KCSAN_KUNIT_CASE(test_ग_लिखो_ग_लिखो_assume_atomic),
	KCSAN_KUNIT_CASE(test_ग_लिखो_ग_लिखो_काष्ठा),
	KCSAN_KUNIT_CASE(test_ग_लिखो_ग_लिखो_काष्ठा_part),
	KCSAN_KUNIT_CASE(test_पढ़ो_atomic_ग_लिखो_atomic),
	KCSAN_KUNIT_CASE(test_पढ़ो_plain_atomic_ग_लिखो),
	KCSAN_KUNIT_CASE(test_पढ़ो_plain_atomic_rmw),
	KCSAN_KUNIT_CASE(test_zero_size_access),
	KCSAN_KUNIT_CASE(test_data_race),
	KCSAN_KUNIT_CASE(test_निश्चित_exclusive_ग_लिखोr),
	KCSAN_KUNIT_CASE(test_निश्चित_exclusive_access),
	KCSAN_KUNIT_CASE(test_निश्चित_exclusive_access_ग_लिखोr),
	KCSAN_KUNIT_CASE(test_निश्चित_exclusive_bits_change),
	KCSAN_KUNIT_CASE(test_निश्चित_exclusive_bits_nochange),
	KCSAN_KUNIT_CASE(test_निश्चित_exclusive_ग_लिखोr_scoped),
	KCSAN_KUNIT_CASE(test_निश्चित_exclusive_access_scoped),
	KCSAN_KUNIT_CASE(test_jअगरfies_noreport),
	KCSAN_KUNIT_CASE(test_seqlock_noreport),
	KCSAN_KUNIT_CASE(test_atomic_builtins),
	अणुपूर्ण,
पूर्ण;

/* ===== End test हालs ===== */

/* Concurrent accesses from पूर्णांकerrupts. */
__no_kcsan
अटल व्योम access_thपढ़ो_समयr(काष्ठा समयr_list *समयr)
अणु
	अटल atomic_t cnt = ATOMIC_INIT(0);
	अचिन्हित पूर्णांक idx;
	व्योम (*func)(व्योम);

	idx = (अचिन्हित पूर्णांक)atomic_inc_वापस(&cnt) % ARRAY_SIZE(access_kernels);
	/* Acquire potential initialization. */
	func = smp_load_acquire(&access_kernels[idx]);
	अगर (func)
		func();
पूर्ण

/* The मुख्य loop क्रम each thपढ़ो. */
__no_kcsan
अटल पूर्णांक access_thपढ़ो(व्योम *arg)
अणु
	काष्ठा समयr_list समयr;
	अचिन्हित पूर्णांक cnt = 0;
	अचिन्हित पूर्णांक idx;
	व्योम (*func)(व्योम);

	समयr_setup_on_stack(&समयr, access_thपढ़ो_समयr, 0);
	करो अणु
		might_sleep();

		अगर (!समयr_pending(&समयr))
			mod_समयr(&समयr, jअगरfies + 1);
		अन्यथा अणु
			/* Iterate through all kernels. */
			idx = cnt++ % ARRAY_SIZE(access_kernels);
			/* Acquire potential initialization. */
			func = smp_load_acquire(&access_kernels[idx]);
			अगर (func)
				func();
		पूर्ण
	पूर्ण जबतक (!torture_must_stop());
	del_समयr_sync(&समयr);
	destroy_समयr_on_stack(&समयr);

	torture_kthपढ़ो_stopping("access_thread");
	वापस 0;
पूर्ण

__no_kcsan
अटल पूर्णांक test_init(काष्ठा kunit *test)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक nthपढ़ोs;
	पूर्णांक i;

	spin_lock_irqsave(&observed.lock, flags);
	क्रम (i = 0; i < ARRAY_SIZE(observed.lines); ++i)
		observed.lines[i][0] = '\0';
	observed.nlines = 0;
	spin_unlock_irqrestore(&observed.lock, flags);

	अगर (!torture_init_begin((अक्षर *)test->name, 1))
		वापस -EBUSY;

	अगर (WARN_ON(thपढ़ोs))
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(access_kernels); ++i) अणु
		अगर (WARN_ON(access_kernels[i]))
			जाओ err;
	पूर्ण

	nthपढ़ोs = असल((दीर्घ)test->param_value);
	अगर (WARN_ON(!nthपढ़ोs))
		जाओ err;

	thपढ़ोs = kसुस्मृति(nthपढ़ोs + 1, माप(काष्ठा task_काष्ठा *), GFP_KERNEL);
	अगर (WARN_ON(!thपढ़ोs))
		जाओ err;

	thपढ़ोs[nthपढ़ोs] = शून्य;
	क्रम (i = 0; i < nthपढ़ोs; ++i) अणु
		अगर (torture_create_kthपढ़ो(access_thपढ़ो, शून्य, thपढ़ोs[i]))
			जाओ err;
	पूर्ण

	torture_init_end();

	वापस 0;

err:
	kमुक्त(thपढ़ोs);
	thपढ़ोs = शून्य;
	torture_init_end();
	वापस -EINVAL;
पूर्ण

__no_kcsan
अटल व्योम test_निकास(काष्ठा kunit *test)
अणु
	काष्ठा task_काष्ठा **stop_thपढ़ो;
	पूर्णांक i;

	अगर (torture_cleanup_begin())
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(access_kernels); ++i)
		WRITE_ONCE(access_kernels[i], शून्य);

	अगर (thपढ़ोs) अणु
		क्रम (stop_thपढ़ो = thपढ़ोs; *stop_thपढ़ो; stop_thपढ़ो++)
			torture_stop_kthपढ़ो(पढ़ोer_thपढ़ो, *stop_thपढ़ो);

		kमुक्त(thपढ़ोs);
		thपढ़ोs = शून्य;
	पूर्ण

	torture_cleanup_end();
पूर्ण

अटल काष्ठा kunit_suite kcsan_test_suite = अणु
	.name = "kcsan",
	.test_हालs = kcsan_test_हालs,
	.init = test_init,
	.निकास = test_निकास,
पूर्ण;
अटल काष्ठा kunit_suite *kcsan_test_suites[] = अणु &kcsan_test_suite, शून्य पूर्ण;

__no_kcsan
अटल व्योम रेजिस्टर_tracepoपूर्णांकs(काष्ठा tracepoपूर्णांक *tp, व्योम *ignore)
अणु
	check_trace_callback_type_console(probe_console);
	अगर (!म_भेद(tp->name, "console"))
		WARN_ON(tracepoपूर्णांक_probe_रेजिस्टर(tp, probe_console, शून्य));
पूर्ण

__no_kcsan
अटल व्योम unरेजिस्टर_tracepoपूर्णांकs(काष्ठा tracepoपूर्णांक *tp, व्योम *ignore)
अणु
	अगर (!म_भेद(tp->name, "console"))
		tracepoपूर्णांक_probe_unरेजिस्टर(tp, probe_console, शून्य);
पूर्ण

/*
 * We only want to करो tracepoपूर्णांकs setup and tearकरोwn once, thereक्रमe we have to
 * customize the init and निकास functions and cannot rely on kunit_test_suite().
 */
अटल पूर्णांक __init kcsan_test_init(व्योम)
अणु
	/*
	 * Because we want to be able to build the test as a module, we need to
	 * iterate through all known tracepoपूर्णांकs, since the अटल registration
	 * won't work here.
	 */
	क्रम_each_kernel_tracepoपूर्णांक(रेजिस्टर_tracepoपूर्णांकs, शून्य);
	वापस __kunit_test_suites_init(kcsan_test_suites);
पूर्ण

अटल व्योम kcsan_test_निकास(व्योम)
अणु
	__kunit_test_suites_निकास(kcsan_test_suites);
	क्रम_each_kernel_tracepoपूर्णांक(unरेजिस्टर_tracepoपूर्णांकs, शून्य);
	tracepoपूर्णांक_synchronize_unरेजिस्टर();
पूर्ण

late_initcall(kcsan_test_init);
module_निकास(kcsan_test_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Marco Elver <elver@google.com>");
