<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हालs क्रम KFENCE memory safety error detector. Since the पूर्णांकerface with
 * which KFENCE's reports are obtained is via the console, this is the output we
 * should verअगरy. For each test हाल checks the presence (or असलence) of
 * generated reports. Relies on 'console' tracepoपूर्णांक to capture reports as they
 * appear in the kernel log.
 *
 * Copyright (C) 2020, Google LLC.
 * Author: Alexander Potapenko <glider@google.com>
 *         Marco Elver <elver@google.com>
 */

#समावेश <kunit/test.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kfence.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <trace/events/prपूर्णांकk.h>

#समावेश "kfence.h"

/* Report as observed from console. */
अटल काष्ठा अणु
	spinlock_t lock;
	पूर्णांक nlines;
	अक्षर lines[2][256];
पूर्ण observed = अणु
	.lock = __SPIN_LOCK_UNLOCKED(observed.lock),
पूर्ण;

/* Probe क्रम console output: obtains observed lines of पूर्णांकerest. */
अटल व्योम probe_console(व्योम *ignore, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक nlines;

	spin_lock_irqsave(&observed.lock, flags);
	nlines = observed.nlines;

	अगर (strnstr(buf, "BUG: KFENCE: ", len) && strnstr(buf, "test_", len)) अणु
		/*
		 * KFENCE report and related to the test.
		 *
		 * The provided @buf is not NUL-terminated; copy no more than
		 * @len bytes and let strscpy() add the missing NUL-terminator.
		 */
		strscpy(observed.lines[0], buf, min(len + 1, माप(observed.lines[0])));
		nlines = 1;
	पूर्ण अन्यथा अगर (nlines == 1 && (strnstr(buf, "at 0x", len) || strnstr(buf, "of 0x", len))) अणु
		strscpy(observed.lines[nlines++], buf, min(len + 1, माप(observed.lines[0])));
	पूर्ण

	WRITE_ONCE(observed.nlines, nlines); /* Publish new nlines. */
	spin_unlock_irqrestore(&observed.lock, flags);
पूर्ण

/* Check अगर a report related to the test exists. */
अटल bool report_available(व्योम)
अणु
	वापस READ_ONCE(observed.nlines) == ARRAY_SIZE(observed.lines);
पूर्ण

/* Inक्रमmation we expect in a report. */
काष्ठा expect_report अणु
	क्रमागत kfence_error_type type; /* The type or error. */
	व्योम *fn; /* Function poपूर्णांकer to expected function where access occurred. */
	अक्षर *addr; /* Address at which the bad access occurred. */
	bool is_ग_लिखो; /* Is access a ग_लिखो. */
पूर्ण;

अटल स्थिर अक्षर *get_access_type(स्थिर काष्ठा expect_report *r)
अणु
	वापस r->is_ग_लिखो ? "write" : "read";
पूर्ण

/* Check observed report matches inक्रमmation in @r. */
अटल bool report_matches(स्थिर काष्ठा expect_report *r)
अणु
	bool ret = false;
	अचिन्हित दीर्घ flags;
	typeof(observed.lines) expect;
	स्थिर अक्षर *end;
	अक्षर *cur;

	/* Doubled-checked locking. */
	अगर (!report_available())
		वापस false;

	/* Generate expected report contents. */

	/* Title */
	cur = expect[0];
	end = &expect[0][माप(expect[0]) - 1];
	चयन (r->type) अणु
	हाल KFENCE_ERROR_OOB:
		cur += scnम_लिखो(cur, end - cur, "BUG: KFENCE: out-of-bounds %s",
				 get_access_type(r));
		अवरोध;
	हाल KFENCE_ERROR_UAF:
		cur += scnम_लिखो(cur, end - cur, "BUG: KFENCE: use-after-free %s",
				 get_access_type(r));
		अवरोध;
	हाल KFENCE_ERROR_CORRUPTION:
		cur += scnम_लिखो(cur, end - cur, "BUG: KFENCE: memory corruption");
		अवरोध;
	हाल KFENCE_ERROR_INVALID:
		cur += scnम_लिखो(cur, end - cur, "BUG: KFENCE: invalid %s",
				 get_access_type(r));
		अवरोध;
	हाल KFENCE_ERROR_INVALID_FREE:
		cur += scnम_लिखो(cur, end - cur, "BUG: KFENCE: invalid free");
		अवरोध;
	पूर्ण

	scnम_लिखो(cur, end - cur, " in %pS", r->fn);
	/* The exact offset won't match, हटाओ it; also strip module name. */
	cur = म_अक्षर(expect[0], '+');
	अगर (cur)
		*cur = '\0';

	/* Access inक्रमmation */
	cur = expect[1];
	end = &expect[1][माप(expect[1]) - 1];

	चयन (r->type) अणु
	हाल KFENCE_ERROR_OOB:
		cur += scnम_लिखो(cur, end - cur, "Out-of-bounds %s at", get_access_type(r));
		अवरोध;
	हाल KFENCE_ERROR_UAF:
		cur += scnम_लिखो(cur, end - cur, "Use-after-free %s at", get_access_type(r));
		अवरोध;
	हाल KFENCE_ERROR_CORRUPTION:
		cur += scnम_लिखो(cur, end - cur, "Corrupted memory at");
		अवरोध;
	हाल KFENCE_ERROR_INVALID:
		cur += scnम_लिखो(cur, end - cur, "Invalid %s at", get_access_type(r));
		अवरोध;
	हाल KFENCE_ERROR_INVALID_FREE:
		cur += scnम_लिखो(cur, end - cur, "Invalid free of");
		अवरोध;
	पूर्ण

	cur += scnम_लिखो(cur, end - cur, " 0x%p", (व्योम *)r->addr);

	spin_lock_irqsave(&observed.lock, flags);
	अगर (!report_available())
		जाओ out; /* A new report is being captured. */

	/* Finally match expected output to what we actually observed. */
	ret = म_माला(observed.lines[0], expect[0]) && म_माला(observed.lines[1], expect[1]);
out:
	spin_unlock_irqrestore(&observed.lock, flags);
	वापस ret;
पूर्ण

/* ===== Test हालs ===== */

#घोषणा TEST_PRIV_WANT_MEMCACHE ((व्योम *)1)

/* Cache used by tests; अगर शून्य, allocate from kदो_स्मृति instead. */
अटल काष्ठा kmem_cache *test_cache;

अटल माप_प्रकार setup_test_cache(काष्ठा kunit *test, माप_प्रकार size, slab_flags_t flags,
			       व्योम (*ctor)(व्योम *))
अणु
	अगर (test->priv != TEST_PRIV_WANT_MEMCACHE)
		वापस size;

	kunit_info(test, "%s: size=%zu, ctor=%ps\n", __func__, size, ctor);

	/*
	 * Use SLAB_NOLEAKTRACE to prevent merging with existing caches. Any
	 * other flag in SLAB_NEVER_MERGE also works. Use SLAB_ACCOUNT to
	 * allocate via memcg, अगर enabled.
	 */
	flags |= SLAB_NOLEAKTRACE | SLAB_ACCOUNT;
	test_cache = kmem_cache_create("test", size, 1, flags, ctor);
	KUNIT_ASSERT_TRUE_MSG(test, test_cache, "could not create cache");

	वापस size;
पूर्ण

अटल व्योम test_cache_destroy(व्योम)
अणु
	अगर (!test_cache)
		वापस;

	kmem_cache_destroy(test_cache);
	test_cache = शून्य;
पूर्ण

अटल अंतरभूत माप_प्रकार kदो_स्मृति_cache_alignment(माप_प्रकार size)
अणु
	वापस kदो_स्मृति_caches[kदो_स्मृति_type(GFP_KERNEL)][kदो_स्मृति_index(size)]->align;
पूर्ण

/* Must always अंतरभूत to match stack trace against caller. */
अटल __always_अंतरभूत व्योम test_मुक्त(व्योम *ptr)
अणु
	अगर (test_cache)
		kmem_cache_मुक्त(test_cache, ptr);
	अन्यथा
		kमुक्त(ptr);
पूर्ण

/*
 * If this should be a KFENCE allocation, and on which side the allocation and
 * the बंदst guard page should be.
 */
क्रमागत allocation_policy अणु
	ALLOCATE_ANY, /* KFENCE, any side. */
	ALLOCATE_LEFT, /* KFENCE, left side of page. */
	ALLOCATE_RIGHT, /* KFENCE, right side of page. */
	ALLOCATE_NONE, /* No KFENCE allocation. */
पूर्ण;

/*
 * Try to get a guarded allocation from KFENCE. Uses either kदो_स्मृति() or the
 * current test_cache अगर set up.
 */
अटल व्योम *test_alloc(काष्ठा kunit *test, माप_प्रकार size, gfp_t gfp, क्रमागत allocation_policy policy)
अणु
	व्योम *alloc;
	अचिन्हित दीर्घ समयout, resched_after;
	स्थिर अक्षर *policy_name;

	चयन (policy) अणु
	हाल ALLOCATE_ANY:
		policy_name = "any";
		अवरोध;
	हाल ALLOCATE_LEFT:
		policy_name = "left";
		अवरोध;
	हाल ALLOCATE_RIGHT:
		policy_name = "right";
		अवरोध;
	हाल ALLOCATE_NONE:
		policy_name = "none";
		अवरोध;
	पूर्ण

	kunit_info(test, "%s: size=%zu, gfp=%x, policy=%s, cache=%i\n", __func__, size, gfp,
		   policy_name, !!test_cache);

	/*
	 * 100x the sample पूर्णांकerval should be more than enough to ensure we get
	 * a KFENCE allocation eventually.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(100 * CONFIG_KFENCE_SAMPLE_INTERVAL);
	/*
	 * Especially क्रम non-preemption kernels, ensure the allocation-gate
	 * समयr can catch up: after @resched_after, every failed allocation
	 * attempt yields, to ensure the allocation-gate समयr is scheduled.
	 */
	resched_after = jअगरfies + msecs_to_jअगरfies(CONFIG_KFENCE_SAMPLE_INTERVAL);
	करो अणु
		अगर (test_cache)
			alloc = kmem_cache_alloc(test_cache, gfp);
		अन्यथा
			alloc = kदो_स्मृति(size, gfp);

		अगर (is_kfence_address(alloc)) अणु
			काष्ठा page *page = virt_to_head_page(alloc);
			काष्ठा kmem_cache *s = test_cache ?: kदो_स्मृति_caches[kदो_स्मृति_type(GFP_KERNEL)][kदो_स्मृति_index(size)];

			/*
			 * Verअगरy that various helpers वापस the right values
			 * even क्रम KFENCE objects; these are required so that
			 * memcg accounting works correctly.
			 */
			KUNIT_EXPECT_EQ(test, obj_to_index(s, page, alloc), 0U);
			KUNIT_EXPECT_EQ(test, objs_per_slab_page(s, page), 1);

			अगर (policy == ALLOCATE_ANY)
				वापस alloc;
			अगर (policy == ALLOCATE_LEFT && IS_ALIGNED((अचिन्हित दीर्घ)alloc, PAGE_SIZE))
				वापस alloc;
			अगर (policy == ALLOCATE_RIGHT &&
			    !IS_ALIGNED((अचिन्हित दीर्घ)alloc, PAGE_SIZE))
				वापस alloc;
		पूर्ण अन्यथा अगर (policy == ALLOCATE_NONE)
			वापस alloc;

		test_मुक्त(alloc);

		अगर (समय_after(jअगरfies, resched_after))
			cond_resched();
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	KUNIT_ASSERT_TRUE_MSG(test, false, "failed to allocate from KFENCE");
	वापस शून्य; /* Unreachable. */
पूर्ण

अटल व्योम test_out_of_bounds_पढ़ो(काष्ठा kunit *test)
अणु
	माप_प्रकार size = 32;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_OOB,
		.fn = test_out_of_bounds_पढ़ो,
		.is_ग_लिखो = false,
	पूर्ण;
	अक्षर *buf;

	setup_test_cache(test, size, 0, शून्य);

	/*
	 * If we करोn't have our own cache, adjust based on alignment, so that we
	 * actually access guard pages on either side.
	 */
	अगर (!test_cache)
		size = kदो_स्मृति_cache_alignment(size);

	/* Test both sides. */

	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_LEFT);
	expect.addr = buf - 1;
	READ_ONCE(*expect.addr);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
	test_मुक्त(buf);

	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_RIGHT);
	expect.addr = buf + size;
	READ_ONCE(*expect.addr);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
	test_मुक्त(buf);
पूर्ण

अटल व्योम test_out_of_bounds_ग_लिखो(काष्ठा kunit *test)
अणु
	माप_प्रकार size = 32;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_OOB,
		.fn = test_out_of_bounds_ग_लिखो,
		.is_ग_लिखो = true,
	पूर्ण;
	अक्षर *buf;

	setup_test_cache(test, size, 0, शून्य);
	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_LEFT);
	expect.addr = buf - 1;
	WRITE_ONCE(*expect.addr, 42);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
	test_मुक्त(buf);
पूर्ण

अटल व्योम test_use_after_मुक्त_पढ़ो(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_UAF,
		.fn = test_use_after_मुक्त_पढ़ो,
		.is_ग_लिखो = false,
	पूर्ण;

	setup_test_cache(test, size, 0, शून्य);
	expect.addr = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY);
	test_मुक्त(expect.addr);
	READ_ONCE(*expect.addr);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
पूर्ण

अटल व्योम test_द्विगुन_मुक्त(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_INVALID_FREE,
		.fn = test_द्विगुन_मुक्त,
	पूर्ण;

	setup_test_cache(test, size, 0, शून्य);
	expect.addr = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY);
	test_मुक्त(expect.addr);
	test_मुक्त(expect.addr); /* Double-मुक्त. */
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
पूर्ण

अटल व्योम test_invalid_addr_मुक्त(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_INVALID_FREE,
		.fn = test_invalid_addr_मुक्त,
	पूर्ण;
	अक्षर *buf;

	setup_test_cache(test, size, 0, शून्य);
	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY);
	expect.addr = buf + 1; /* Free on invalid address. */
	test_मुक्त(expect.addr); /* Invalid address मुक्त. */
	test_मुक्त(buf); /* No error. */
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
पूर्ण

अटल व्योम test_corruption(काष्ठा kunit *test)
अणु
	माप_प्रकार size = 32;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_CORRUPTION,
		.fn = test_corruption,
	पूर्ण;
	अक्षर *buf;

	setup_test_cache(test, size, 0, शून्य);

	/* Test both sides. */

	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_LEFT);
	expect.addr = buf + size;
	WRITE_ONCE(*expect.addr, 42);
	test_मुक्त(buf);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));

	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_RIGHT);
	expect.addr = buf - 1;
	WRITE_ONCE(*expect.addr, 42);
	test_मुक्त(buf);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
पूर्ण

/*
 * KFENCE is unable to detect an OOB अगर the allocation's alignment requirements
 * leave a gap between the object and the guard page. Specअगरically, an
 * allocation of e.g. 73 bytes is aligned on 8 and 128 bytes क्रम SLUB or SLAB
 * respectively. Thereक्रमe it is impossible क्रम the allocated object to
 * contiguously line up with the right guard page.
 *
 * However, we test that an access to memory beyond the gap results in KFENCE
 * detecting an OOB access.
 */
अटल व्योम test_kदो_स्मृति_aligned_oob_पढ़ो(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 73;
	स्थिर माप_प्रकार align = kदो_स्मृति_cache_alignment(size);
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_OOB,
		.fn = test_kदो_स्मृति_aligned_oob_पढ़ो,
		.is_ग_लिखो = false,
	पूर्ण;
	अक्षर *buf;

	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_RIGHT);

	/*
	 * The object is offset to the right, so there won't be an OOB to the
	 * left of it.
	 */
	READ_ONCE(*(buf - 1));
	KUNIT_EXPECT_FALSE(test, report_available());

	/*
	 * @buf must be aligned on @align, thereक्रमe buf + size beदीर्घs to the
	 * same page -> no OOB.
	 */
	READ_ONCE(*(buf + size));
	KUNIT_EXPECT_FALSE(test, report_available());

	/* Overflowing by @align bytes will result in an OOB. */
	expect.addr = buf + size + align;
	READ_ONCE(*expect.addr);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));

	test_मुक्त(buf);
पूर्ण

अटल व्योम test_kदो_स्मृति_aligned_oob_ग_लिखो(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 73;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_CORRUPTION,
		.fn = test_kदो_स्मृति_aligned_oob_ग_लिखो,
	पूर्ण;
	अक्षर *buf;

	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_RIGHT);
	/*
	 * The object is offset to the right, so we won't get a page
	 * fault immediately after it.
	 */
	expect.addr = buf + size;
	WRITE_ONCE(*expect.addr, READ_ONCE(*expect.addr) + 1);
	KUNIT_EXPECT_FALSE(test, report_available());
	test_मुक्त(buf);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
पूर्ण

/* Test cache shrinking and destroying with KFENCE. */
अटल व्योम test_shrink_memcache(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	व्योम *buf;

	setup_test_cache(test, size, 0, शून्य);
	KUNIT_EXPECT_TRUE(test, test_cache);
	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY);
	kmem_cache_shrink(test_cache);
	test_मुक्त(buf);

	KUNIT_EXPECT_FALSE(test, report_available());
पूर्ण

अटल व्योम ctor_set_x(व्योम *obj)
अणु
	/* Every object has at least 8 bytes. */
	स_रखो(obj, 'x', 8);
पूर्ण

/* Ensure that SL*B करोes not modअगरy KFENCE objects on bulk मुक्त. */
अटल व्योम test_मुक्त_bulk(काष्ठा kunit *test)
अणु
	पूर्णांक iter;

	क्रम (iter = 0; iter < 5; iter++) अणु
		स्थिर माप_प्रकार size = setup_test_cache(test, 8 + pअक्रमom_u32_max(300), 0,
						     (iter & 1) ? ctor_set_x : शून्य);
		व्योम *objects[] = अणु
			test_alloc(test, size, GFP_KERNEL, ALLOCATE_RIGHT),
			test_alloc(test, size, GFP_KERNEL, ALLOCATE_NONE),
			test_alloc(test, size, GFP_KERNEL, ALLOCATE_LEFT),
			test_alloc(test, size, GFP_KERNEL, ALLOCATE_NONE),
			test_alloc(test, size, GFP_KERNEL, ALLOCATE_NONE),
		पूर्ण;

		kmem_cache_मुक्त_bulk(test_cache, ARRAY_SIZE(objects), objects);
		KUNIT_ASSERT_FALSE(test, report_available());
		test_cache_destroy();
	पूर्ण
पूर्ण

/* Test init-on-मुक्त works. */
अटल व्योम test_init_on_मुक्त(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_UAF,
		.fn = test_init_on_मुक्त,
		.is_ग_लिखो = false,
	पूर्ण;
	पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_INIT_ON_FREE_DEFAULT_ON))
		वापस;
	/* Assume it hasn't been disabled on command line. */

	setup_test_cache(test, size, 0, शून्य);
	expect.addr = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY);
	क्रम (i = 0; i < size; i++)
		expect.addr[i] = i + 1;
	test_मुक्त(expect.addr);

	क्रम (i = 0; i < size; i++) अणु
		/*
		 * This may fail अगर the page was recycled by KFENCE and then
		 * written to again -- this however, is near impossible with a
		 * शेष config.
		 */
		KUNIT_EXPECT_EQ(test, expect.addr[i], (अक्षर)0);

		अगर (!i) /* Only check first access to not fail test अगर page is ever re-रक्षित. */
			KUNIT_EXPECT_TRUE(test, report_matches(&expect));
	पूर्ण
पूर्ण

/* Ensure that स्थिरructors work properly. */
अटल व्योम test_memcache_ctor(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	अक्षर *buf;
	पूर्णांक i;

	setup_test_cache(test, size, 0, ctor_set_x);
	buf = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY);

	क्रम (i = 0; i < 8; i++)
		KUNIT_EXPECT_EQ(test, buf[i], (अक्षर)'x');

	test_मुक्त(buf);

	KUNIT_EXPECT_FALSE(test, report_available());
पूर्ण

/* Test that memory is zeroed अगर requested. */
अटल व्योम test_gfpzero(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = PAGE_SIZE; /* PAGE_SIZE so we can use ALLOCATE_ANY. */
	अक्षर *buf1, *buf2;
	पूर्णांक i;

	अगर (CONFIG_KFENCE_SAMPLE_INTERVAL > 100) अणु
		kunit_warn(test, "skipping ... would take too long\n");
		वापस;
	पूर्ण

	setup_test_cache(test, size, 0, शून्य);
	buf1 = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY);
	क्रम (i = 0; i < size; i++)
		buf1[i] = i + 1;
	test_मुक्त(buf1);

	/* Try to get same address again -- this can take a जबतक. */
	क्रम (i = 0;; i++) अणु
		buf2 = test_alloc(test, size, GFP_KERNEL | __GFP_ZERO, ALLOCATE_ANY);
		अगर (buf1 == buf2)
			अवरोध;
		test_मुक्त(buf2);

		अगर (i == CONFIG_KFENCE_NUM_OBJECTS) अणु
			kunit_warn(test, "giving up ... cannot get same object back\n");
			वापस;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < size; i++)
		KUNIT_EXPECT_EQ(test, buf2[i], (अक्षर)0);

	test_मुक्त(buf2);

	KUNIT_EXPECT_FALSE(test, report_available());
पूर्ण

अटल व्योम test_invalid_access(काष्ठा kunit *test)
अणु
	स्थिर काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_INVALID,
		.fn = test_invalid_access,
		.addr = &__kfence_pool[10],
		.is_ग_लिखो = false,
	पूर्ण;

	READ_ONCE(__kfence_pool[10]);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
पूर्ण

/* Test SLAB_TYPESAFE_BY_RCU works. */
अटल व्योम test_memcache_typesafe_by_rcu(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_UAF,
		.fn = test_memcache_typesafe_by_rcu,
		.is_ग_लिखो = false,
	पूर्ण;

	setup_test_cache(test, size, SLAB_TYPESAFE_BY_RCU, शून्य);
	KUNIT_EXPECT_TRUE(test, test_cache); /* Want memcache. */

	expect.addr = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY);
	*expect.addr = 42;

	rcu_पढ़ो_lock();
	test_मुक्त(expect.addr);
	KUNIT_EXPECT_EQ(test, *expect.addr, (अक्षर)42);
	/*
	 * Up to this poपूर्णांक, memory should not have been मुक्तd yet, and
	 * thereक्रमe there should be no KFENCE report from the above access.
	 */
	rcu_पढ़ो_unlock();

	/* Above access to @expect.addr should not have generated a report! */
	KUNIT_EXPECT_FALSE(test, report_available());

	/* Only after rcu_barrier() is the memory guaranteed to be मुक्तd. */
	rcu_barrier();

	/* Expect use-after-मुक्त. */
	KUNIT_EXPECT_EQ(test, *expect.addr, (अक्षर)42);
	KUNIT_EXPECT_TRUE(test, report_matches(&expect));
पूर्ण

/* Test kपुनः_स्मृति(). */
अटल व्योम test_kपुनः_स्मृति(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	स्थिर काष्ठा expect_report expect = अणु
		.type = KFENCE_ERROR_UAF,
		.fn = test_kपुनः_स्मृति,
		.addr = test_alloc(test, size, GFP_KERNEL, ALLOCATE_ANY),
		.is_ग_लिखो = false,
	पूर्ण;
	अक्षर *buf = expect.addr;
	पूर्णांक i;

	KUNIT_EXPECT_FALSE(test, test_cache);
	KUNIT_EXPECT_EQ(test, ksize(buf), size); /* Precise size match after KFENCE alloc. */
	क्रम (i = 0; i < size; i++)
		buf[i] = i + 1;

	/* Check that we successfully change the size. */
	buf = kपुनः_स्मृति(buf, size * 3, GFP_KERNEL); /* Grow. */
	/* Note: Might no दीर्घer be a KFENCE alloc. */
	KUNIT_EXPECT_GE(test, ksize(buf), size * 3);
	क्रम (i = 0; i < size; i++)
		KUNIT_EXPECT_EQ(test, buf[i], (अक्षर)(i + 1));
	क्रम (; i < size * 3; i++) /* Fill to extra bytes. */
		buf[i] = i + 1;

	buf = kपुनः_स्मृति(buf, size * 2, GFP_KERNEL); /* Shrink. */
	KUNIT_EXPECT_GE(test, ksize(buf), size * 2);
	क्रम (i = 0; i < size * 2; i++)
		KUNIT_EXPECT_EQ(test, buf[i], (अक्षर)(i + 1));

	buf = kपुनः_स्मृति(buf, 0, GFP_KERNEL); /* Free. */
	KUNIT_EXPECT_EQ(test, (अचिन्हित दीर्घ)buf, (अचिन्हित दीर्घ)ZERO_SIZE_PTR);
	KUNIT_ASSERT_FALSE(test, report_available()); /* No reports yet! */

	READ_ONCE(*expect.addr); /* Ensure kपुनः_स्मृति() actually मुक्तd earlier KFENCE object. */
	KUNIT_ASSERT_TRUE(test, report_matches(&expect));
पूर्ण

/* Test that some objects from a bulk allocation beदीर्घ to KFENCE pool. */
अटल व्योम test_memcache_alloc_bulk(काष्ठा kunit *test)
अणु
	स्थिर माप_प्रकार size = 32;
	bool pass = false;
	अचिन्हित दीर्घ समयout;

	setup_test_cache(test, size, 0, शून्य);
	KUNIT_EXPECT_TRUE(test, test_cache); /* Want memcache. */
	/*
	 * 100x the sample पूर्णांकerval should be more than enough to ensure we get
	 * a KFENCE allocation eventually.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(100 * CONFIG_KFENCE_SAMPLE_INTERVAL);
	करो अणु
		व्योम *objects[100];
		पूर्णांक i, num = kmem_cache_alloc_bulk(test_cache, GFP_ATOMIC, ARRAY_SIZE(objects),
						   objects);
		अगर (!num)
			जारी;
		क्रम (i = 0; i < ARRAY_SIZE(objects); i++) अणु
			अगर (is_kfence_address(objects[i])) अणु
				pass = true;
				अवरोध;
			पूर्ण
		पूर्ण
		kmem_cache_मुक्त_bulk(test_cache, num, objects);
		/*
		 * kmem_cache_alloc_bulk() disables पूर्णांकerrupts, and calling it
		 * in a tight loop may not give KFENCE a chance to चयन the
		 * अटल branch. Call cond_resched() to let KFENCE chime in.
		 */
		cond_resched();
	पूर्ण जबतक (!pass && समय_beक्रमe(jअगरfies, समयout));

	KUNIT_EXPECT_TRUE(test, pass);
	KUNIT_EXPECT_FALSE(test, report_available());
पूर्ण

/*
 * KUnit करोes not provide a way to provide arguments to tests, and we encode
 * additional info in the name. Set up 2 tests per test हाल, one using the
 * शेष allocator, and another using a custom memcache (suffix '-memcache').
 */
#घोषणा KFENCE_KUNIT_CASE(test_name)						\
	अणु .run_हाल = test_name, .name = #test_name पूर्ण,				\
	अणु .run_हाल = test_name, .name = #test_name "-memcache" पूर्ण

अटल काष्ठा kunit_हाल kfence_test_हालs[] = अणु
	KFENCE_KUNIT_CASE(test_out_of_bounds_पढ़ो),
	KFENCE_KUNIT_CASE(test_out_of_bounds_ग_लिखो),
	KFENCE_KUNIT_CASE(test_use_after_मुक्त_पढ़ो),
	KFENCE_KUNIT_CASE(test_द्विगुन_मुक्त),
	KFENCE_KUNIT_CASE(test_invalid_addr_मुक्त),
	KFENCE_KUNIT_CASE(test_corruption),
	KFENCE_KUNIT_CASE(test_मुक्त_bulk),
	KFENCE_KUNIT_CASE(test_init_on_मुक्त),
	KUNIT_CASE(test_kदो_स्मृति_aligned_oob_पढ़ो),
	KUNIT_CASE(test_kदो_स्मृति_aligned_oob_ग_लिखो),
	KUNIT_CASE(test_shrink_memcache),
	KUNIT_CASE(test_memcache_ctor),
	KUNIT_CASE(test_invalid_access),
	KUNIT_CASE(test_gfpzero),
	KUNIT_CASE(test_memcache_typesafe_by_rcu),
	KUNIT_CASE(test_kपुनः_स्मृति),
	KUNIT_CASE(test_memcache_alloc_bulk),
	अणुपूर्ण,
पूर्ण;

/* ===== End test हालs ===== */

अटल पूर्णांक test_init(काष्ठा kunit *test)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&observed.lock, flags);
	क्रम (i = 0; i < ARRAY_SIZE(observed.lines); i++)
		observed.lines[i][0] = '\0';
	observed.nlines = 0;
	spin_unlock_irqrestore(&observed.lock, flags);

	/* Any test with 'memcache' in its name will want a memcache. */
	अगर (म_माला(test->name, "memcache"))
		test->priv = TEST_PRIV_WANT_MEMCACHE;
	अन्यथा
		test->priv = शून्य;

	वापस 0;
पूर्ण

अटल व्योम test_निकास(काष्ठा kunit *test)
अणु
	test_cache_destroy();
पूर्ण

अटल काष्ठा kunit_suite kfence_test_suite = अणु
	.name = "kfence",
	.test_हालs = kfence_test_हालs,
	.init = test_init,
	.निकास = test_निकास,
पूर्ण;
अटल काष्ठा kunit_suite *kfence_test_suites[] = अणु &kfence_test_suite, शून्य पूर्ण;

अटल व्योम रेजिस्टर_tracepoपूर्णांकs(काष्ठा tracepoपूर्णांक *tp, व्योम *ignore)
अणु
	check_trace_callback_type_console(probe_console);
	अगर (!म_भेद(tp->name, "console"))
		WARN_ON(tracepoपूर्णांक_probe_रेजिस्टर(tp, probe_console, शून्य));
पूर्ण

अटल व्योम unरेजिस्टर_tracepoपूर्णांकs(काष्ठा tracepoपूर्णांक *tp, व्योम *ignore)
अणु
	अगर (!म_भेद(tp->name, "console"))
		tracepoपूर्णांक_probe_unरेजिस्टर(tp, probe_console, शून्य);
पूर्ण

/*
 * We only want to करो tracepoपूर्णांकs setup and tearकरोwn once, thereक्रमe we have to
 * customize the init and निकास functions and cannot rely on kunit_test_suite().
 */
अटल पूर्णांक __init kfence_test_init(व्योम)
अणु
	/*
	 * Because we want to be able to build the test as a module, we need to
	 * iterate through all known tracepoपूर्णांकs, since the अटल registration
	 * won't work here.
	 */
	क्रम_each_kernel_tracepoपूर्णांक(रेजिस्टर_tracepoपूर्णांकs, शून्य);
	वापस __kunit_test_suites_init(kfence_test_suites);
पूर्ण

अटल व्योम kfence_test_निकास(व्योम)
अणु
	__kunit_test_suites_निकास(kfence_test_suites);
	क्रम_each_kernel_tracepoपूर्णांक(unरेजिस्टर_tracepoपूर्णांकs, शून्य);
	tracepoपूर्णांक_synchronize_unरेजिस्टर();
पूर्ण

late_initcall(kfence_test_init);
module_निकास(kfence_test_निकास);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Alexander Potapenko <glider@google.com>, Marco Elver <elver@google.com>");
