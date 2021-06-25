<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <a.ryabinin@samsung.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/page.h>

#समावेश <kunit/test.h>

#समावेश "../mm/kasan/kasan.h"

#घोषणा OOB_TAG_OFF (IS_ENABLED(CONFIG_KASAN_GENERIC) ? 0 : KASAN_GRANULE_SIZE)

/*
 * Some tests use these global variables to store वापस values from function
 * calls that could otherwise be eliminated by the compiler as dead code.
 */
व्योम *kasan_ptr_result;
पूर्णांक kasan_पूर्णांक_result;

अटल काष्ठा kunit_resource resource;
अटल काष्ठा kunit_kasan_expectation fail_data;
अटल bool multishot;

/*
 * Temporarily enable multi-shot mode. Otherwise, KASAN would only report the
 * first detected bug and panic the kernel अगर panic_on_warn is enabled. For
 * hardware tag-based KASAN also allow tag checking to be reenabled क्रम each
 * test, see the comment क्रम KUNIT_EXPECT_KASAN_FAIL().
 */
अटल पूर्णांक kasan_test_init(काष्ठा kunit *test)
अणु
	अगर (!kasan_enabled()) अणु
		kunit_err(test, "can't run KASAN tests with KASAN disabled");
		वापस -1;
	पूर्ण

	multishot = kasan_save_enable_multi_shot();
	kasan_set_tagging_report_once(false);
	fail_data.report_found = false;
	fail_data.report_expected = false;
	kunit_add_named_resource(test, शून्य, शून्य, &resource,
					"kasan_data", &fail_data);
	वापस 0;
पूर्ण

अटल व्योम kasan_test_निकास(काष्ठा kunit *test)
अणु
	kasan_set_tagging_report_once(true);
	kasan_restore_multi_shot(multishot);
	KUNIT_EXPECT_FALSE(test, fail_data.report_found);
पूर्ण

/**
 * KUNIT_EXPECT_KASAN_FAIL() - check that the executed expression produces a
 * KASAN report; causes a test failure otherwise. This relies on a KUnit
 * resource named "kasan_data". Do not use this name क्रम KUnit resources
 * outside of KASAN tests.
 *
 * For hardware tag-based KASAN in sync mode, when a tag fault happens, tag
 * checking is स्वतः-disabled. When this happens, this test handler reenables
 * tag checking. As tag checking can be only disabled or enabled per CPU,
 * this handler disables migration (preemption).
 *
 * Since the compiler करोesn't see that the expression can change the fail_data
 * fields, it can reorder or optimize away the accesses to those fields.
 * Use READ/WRITE_ONCE() क्रम the accesses and compiler barriers around the
 * expression to prevent that.
 *
 * In between KUNIT_EXPECT_KASAN_FAIL checks, fail_data.report_found is kept as
 * false. This allows detecting KASAN reports that happen outside of the checks
 * by निश्चितing !fail_data.report_found at the start of KUNIT_EXPECT_KASAN_FAIL
 * and in kasan_test_निकास.
 */
#घोषणा KUNIT_EXPECT_KASAN_FAIL(test, expression) करो अणु			\
	अगर (IS_ENABLED(CONFIG_KASAN_HW_TAGS) &&				\
	    !kasan_async_mode_enabled())				\
		migrate_disable();					\
	KUNIT_EXPECT_FALSE(test, READ_ONCE(fail_data.report_found));	\
	WRITE_ONCE(fail_data.report_expected, true);			\
	barrier();							\
	expression;							\
	barrier();							\
	KUNIT_EXPECT_EQ(test,						\
			READ_ONCE(fail_data.report_expected),		\
			READ_ONCE(fail_data.report_found));		\
	अगर (IS_ENABLED(CONFIG_KASAN_HW_TAGS)) अणु				\
		अगर (READ_ONCE(fail_data.report_found))			\
			kasan_enable_tagging_sync();			\
		migrate_enable();					\
	पूर्ण								\
	WRITE_ONCE(fail_data.report_found, false);			\
	WRITE_ONCE(fail_data.report_expected, false);			\
पूर्ण जबतक (0)

#घोषणा KASAN_TEST_NEEDS_CONFIG_ON(test, config) करो अणु			\
	अगर (!IS_ENABLED(config)) अणु					\
		kunit_info((test), "skipping, " #config " required");	\
		वापस;							\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा KASAN_TEST_NEEDS_CONFIG_OFF(test, config) करो अणु			\
	अगर (IS_ENABLED(config)) अणु					\
		kunit_info((test), "skipping, " #config " enabled");	\
		वापस;							\
	पूर्ण								\
पूर्ण जबतक (0)

अटल व्योम kदो_स्मृति_oob_right(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 123;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, ptr[size + OOB_TAG_OFF] = 'x');
	kमुक्त(ptr);
पूर्ण

अटल व्योम kदो_स्मृति_oob_left(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 15;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, *ptr = *(ptr - 1));
	kमुक्त(ptr);
पूर्ण

अटल व्योम kदो_स्मृति_node_oob_right(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 4096;

	ptr = kदो_स्मृति_node(size, GFP_KERNEL, 0);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, ptr[size] = 0);
	kमुक्त(ptr);
पूर्ण

/*
 * These kदो_स्मृति_pagealloc_* tests try allocating a memory chunk that करोesn't
 * fit पूर्णांकo a slab cache and thereक्रमe is allocated via the page allocator
 * fallback. Since this kind of fallback is only implemented क्रम SLUB, these
 * tests are limited to that allocator.
 */
अटल व्योम kदो_स्मृति_pagealloc_oob_right(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = KMALLOC_MAX_CACHE_SIZE + 10;

	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_SLUB);

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, ptr[size + OOB_TAG_OFF] = 0);

	kमुक्त(ptr);
पूर्ण

अटल व्योम kदो_स्मृति_pagealloc_uaf(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = KMALLOC_MAX_CACHE_SIZE + 10;

	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_SLUB);

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);
	kमुक्त(ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, ptr[0] = 0);
पूर्ण

अटल व्योम kदो_स्मृति_pagealloc_invalid_मुक्त(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = KMALLOC_MAX_CACHE_SIZE + 10;

	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_SLUB);

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, kमुक्त(ptr + 1));
पूर्ण

अटल व्योम pagealloc_oob_right(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	काष्ठा page *pages;
	माप_प्रकार order = 4;
	माप_प्रकार size = (1UL << (PAGE_SHIFT + order));

	/*
	 * With generic KASAN page allocations have no redzones, thus
	 * out-of-bounds detection is not guaranteed.
	 * See https://bugzilla.kernel.org/show_bug.cgi?id=210503.
	 */
	KASAN_TEST_NEEDS_CONFIG_OFF(test, CONFIG_KASAN_GENERIC);

	pages = alloc_pages(GFP_KERNEL, order);
	ptr = page_address(pages);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, ptr[size] = 0);
	मुक्त_pages((अचिन्हित दीर्घ)ptr, order);
पूर्ण

अटल व्योम pagealloc_uaf(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	काष्ठा page *pages;
	माप_प्रकार order = 4;

	pages = alloc_pages(GFP_KERNEL, order);
	ptr = page_address(pages);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);
	मुक्त_pages((अचिन्हित दीर्घ)ptr, order);

	KUNIT_EXPECT_KASAN_FAIL(test, ptr[0] = 0);
पूर्ण

अटल व्योम kदो_स्मृति_large_oob_right(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = KMALLOC_MAX_CACHE_SIZE - 256;

	/*
	 * Allocate a chunk that is large enough, but still fits पूर्णांकo a slab
	 * and करोes not trigger the page allocator fallback in SLUB.
	 */
	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, ptr[size] = 0);
	kमुक्त(ptr);
पूर्ण

अटल व्योम kपुनः_स्मृति_more_oob_helper(काष्ठा kunit *test,
					माप_प्रकार size1, माप_प्रकार size2)
अणु
	अक्षर *ptr1, *ptr2;
	माप_प्रकार middle;

	KUNIT_ASSERT_LT(test, size1, size2);
	middle = size1 + (size2 - size1) / 2;

	ptr1 = kदो_स्मृति(size1, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr1);

	ptr2 = kपुनः_स्मृति(ptr1, size2, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr2);

	/* All offsets up to size2 must be accessible. */
	ptr2[size1 - 1] = 'x';
	ptr2[size1] = 'x';
	ptr2[middle] = 'x';
	ptr2[size2 - 1] = 'x';

	/* Generic mode is precise, so unaligned size2 must be inaccessible. */
	अगर (IS_ENABLED(CONFIG_KASAN_GENERIC))
		KUNIT_EXPECT_KASAN_FAIL(test, ptr2[size2] = 'x');

	/* For all modes first aligned offset after size2 must be inaccessible. */
	KUNIT_EXPECT_KASAN_FAIL(test,
		ptr2[round_up(size2, KASAN_GRANULE_SIZE)] = 'x');

	kमुक्त(ptr2);
पूर्ण

अटल व्योम kपुनः_स्मृति_less_oob_helper(काष्ठा kunit *test,
					माप_प्रकार size1, माप_प्रकार size2)
अणु
	अक्षर *ptr1, *ptr2;
	माप_प्रकार middle;

	KUNIT_ASSERT_LT(test, size2, size1);
	middle = size2 + (size1 - size2) / 2;

	ptr1 = kदो_स्मृति(size1, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr1);

	ptr2 = kपुनः_स्मृति(ptr1, size2, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr2);

	/* Must be accessible क्रम all modes. */
	ptr2[size2 - 1] = 'x';

	/* Generic mode is precise, so unaligned size2 must be inaccessible. */
	अगर (IS_ENABLED(CONFIG_KASAN_GENERIC))
		KUNIT_EXPECT_KASAN_FAIL(test, ptr2[size2] = 'x');

	/* For all modes first aligned offset after size2 must be inaccessible. */
	KUNIT_EXPECT_KASAN_FAIL(test,
		ptr2[round_up(size2, KASAN_GRANULE_SIZE)] = 'x');

	/*
	 * For all modes all size2, middle, and size1 should land in separate
	 * granules and thus the latter two offsets should be inaccessible.
	 */
	KUNIT_EXPECT_LE(test, round_up(size2, KASAN_GRANULE_SIZE),
				round_करोwn(middle, KASAN_GRANULE_SIZE));
	KUNIT_EXPECT_LE(test, round_up(middle, KASAN_GRANULE_SIZE),
				round_करोwn(size1, KASAN_GRANULE_SIZE));
	KUNIT_EXPECT_KASAN_FAIL(test, ptr2[middle] = 'x');
	KUNIT_EXPECT_KASAN_FAIL(test, ptr2[size1 - 1] = 'x');
	KUNIT_EXPECT_KASAN_FAIL(test, ptr2[size1] = 'x');

	kमुक्त(ptr2);
पूर्ण

अटल व्योम kपुनः_स्मृति_more_oob(काष्ठा kunit *test)
अणु
	kपुनः_स्मृति_more_oob_helper(test, 201, 235);
पूर्ण

अटल व्योम kपुनः_स्मृति_less_oob(काष्ठा kunit *test)
अणु
	kपुनः_स्मृति_less_oob_helper(test, 235, 201);
पूर्ण

अटल व्योम kपुनः_स्मृति_pagealloc_more_oob(काष्ठा kunit *test)
अणु
	/* page_alloc fallback in only implemented क्रम SLUB. */
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_SLUB);

	kपुनः_स्मृति_more_oob_helper(test, KMALLOC_MAX_CACHE_SIZE + 201,
					KMALLOC_MAX_CACHE_SIZE + 235);
पूर्ण

अटल व्योम kपुनः_स्मृति_pagealloc_less_oob(काष्ठा kunit *test)
अणु
	/* page_alloc fallback in only implemented क्रम SLUB. */
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_SLUB);

	kपुनः_स्मृति_less_oob_helper(test, KMALLOC_MAX_CACHE_SIZE + 235,
					KMALLOC_MAX_CACHE_SIZE + 201);
पूर्ण

/*
 * Check that kपुनः_स्मृति() detects a use-after-मुक्त, वापसs शून्य,
 * and करोesn't unpoison the मुक्तd object.
 */
अटल व्योम kपुनः_स्मृति_uaf(काष्ठा kunit *test)
अणु
	अक्षर *ptr1, *ptr2;
	पूर्णांक size1 = 201;
	पूर्णांक size2 = 235;

	ptr1 = kदो_स्मृति(size1, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr1);
	kमुक्त(ptr1);

	KUNIT_EXPECT_KASAN_FAIL(test, ptr2 = kपुनः_स्मृति(ptr1, size2, GFP_KERNEL));
	KUNIT_ASSERT_PTR_EQ(test, (व्योम *)ptr2, शून्य);
	KUNIT_EXPECT_KASAN_FAIL(test, *(अस्थिर अक्षर *)ptr1);
पूर्ण

अटल व्योम kदो_स्मृति_oob_16(काष्ठा kunit *test)
अणु
	काष्ठा अणु
		u64 words[2];
	पूर्ण *ptr1, *ptr2;

	/* This test is specअगरically crafted क्रम the generic mode. */
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_GENERIC);

	ptr1 = kदो_स्मृति(माप(*ptr1) - 3, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr1);

	ptr2 = kदो_स्मृति(माप(*ptr2), GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr2);

	KUNIT_EXPECT_KASAN_FAIL(test, *ptr1 = *ptr2);
	kमुक्त(ptr1);
	kमुक्त(ptr2);
पूर्ण

अटल व्योम kदो_स्मृति_uaf_16(काष्ठा kunit *test)
अणु
	काष्ठा अणु
		u64 words[2];
	पूर्ण *ptr1, *ptr2;

	ptr1 = kदो_स्मृति(माप(*ptr1), GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr1);

	ptr2 = kदो_स्मृति(माप(*ptr2), GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr2);
	kमुक्त(ptr2);

	KUNIT_EXPECT_KASAN_FAIL(test, *ptr1 = *ptr2);
	kमुक्त(ptr1);
पूर्ण

अटल व्योम kदो_स्मृति_oob_स_रखो_2(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 8;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, स_रखो(ptr + 7 + OOB_TAG_OFF, 0, 2));
	kमुक्त(ptr);
पूर्ण

अटल व्योम kदो_स्मृति_oob_स_रखो_4(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 8;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, स_रखो(ptr + 5 + OOB_TAG_OFF, 0, 4));
	kमुक्त(ptr);
पूर्ण


अटल व्योम kदो_स्मृति_oob_स_रखो_8(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 8;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, स_रखो(ptr + 1 + OOB_TAG_OFF, 0, 8));
	kमुक्त(ptr);
पूर्ण

अटल व्योम kदो_स्मृति_oob_स_रखो_16(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 16;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, स_रखो(ptr + 1 + OOB_TAG_OFF, 0, 16));
	kमुक्त(ptr);
पूर्ण

अटल व्योम kदो_स्मृति_oob_in_स_रखो(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 666;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, स_रखो(ptr, 0, size + 5 + OOB_TAG_OFF));
	kमुक्त(ptr);
पूर्ण

अटल व्योम kदो_स्मृति_स_हटाओ_invalid_size(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 64;
	अस्थिर माप_प्रकार invalid_size = -2;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	स_रखो((अक्षर *)ptr, 0, 64);

	KUNIT_EXPECT_KASAN_FAIL(test,
		स_हटाओ((अक्षर *)ptr, (अक्षर *)ptr + 4, invalid_size));
	kमुक्त(ptr);
पूर्ण

अटल व्योम kदो_स्मृति_uaf(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 10;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	kमुक्त(ptr);
	KUNIT_EXPECT_KASAN_FAIL(test, *(ptr + 8) = 'x');
पूर्ण

अटल व्योम kदो_स्मृति_uaf_स_रखो(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 33;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	kमुक्त(ptr);
	KUNIT_EXPECT_KASAN_FAIL(test, स_रखो(ptr, 0, size));
पूर्ण

अटल व्योम kदो_स्मृति_uaf2(काष्ठा kunit *test)
अणु
	अक्षर *ptr1, *ptr2;
	माप_प्रकार size = 43;
	पूर्णांक counter = 0;

again:
	ptr1 = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr1);

	kमुक्त(ptr1);

	ptr2 = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr2);

	/*
	 * For tag-based KASAN ptr1 and ptr2 tags might happen to be the same.
	 * Allow up to 16 attempts at generating dअगरferent tags.
	 */
	अगर (!IS_ENABLED(CONFIG_KASAN_GENERIC) && ptr1 == ptr2 && counter++ < 16) अणु
		kमुक्त(ptr2);
		जाओ again;
	पूर्ण

	KUNIT_EXPECT_KASAN_FAIL(test, ptr1[40] = 'x');
	KUNIT_EXPECT_PTR_NE(test, ptr1, ptr2);

	kमुक्त(ptr2);
पूर्ण

अटल व्योम kमुक्त_via_page(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 8;
	काष्ठा page *page;
	अचिन्हित दीर्घ offset;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	page = virt_to_page(ptr);
	offset = offset_in_page(ptr);
	kमुक्त(page_address(page) + offset);
पूर्ण

अटल व्योम kमुक्त_via_phys(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 8;
	phys_addr_t phys;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	phys = virt_to_phys(ptr);
	kमुक्त(phys_to_virt(phys));
पूर्ण

अटल व्योम kmem_cache_oob(काष्ठा kunit *test)
अणु
	अक्षर *p;
	माप_प्रकार size = 200;
	काष्ठा kmem_cache *cache;

	cache = kmem_cache_create("test_cache", size, 0, 0, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, cache);

	p = kmem_cache_alloc(cache, GFP_KERNEL);
	अगर (!p) अणु
		kunit_err(test, "Allocation failed: %s\n", __func__);
		kmem_cache_destroy(cache);
		वापस;
	पूर्ण

	KUNIT_EXPECT_KASAN_FAIL(test, *p = p[size + OOB_TAG_OFF]);

	kmem_cache_मुक्त(cache, p);
	kmem_cache_destroy(cache);
पूर्ण

अटल व्योम kmem_cache_accounted(काष्ठा kunit *test)
अणु
	पूर्णांक i;
	अक्षर *p;
	माप_प्रकार size = 200;
	काष्ठा kmem_cache *cache;

	cache = kmem_cache_create("test_cache", size, 0, SLAB_ACCOUNT, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, cache);

	/*
	 * Several allocations with a delay to allow क्रम lazy per memcg kmem
	 * cache creation.
	 */
	क्रम (i = 0; i < 5; i++) अणु
		p = kmem_cache_alloc(cache, GFP_KERNEL);
		अगर (!p)
			जाओ मुक्त_cache;

		kmem_cache_मुक्त(cache, p);
		msleep(100);
	पूर्ण

मुक्त_cache:
	kmem_cache_destroy(cache);
पूर्ण

अटल व्योम kmem_cache_bulk(काष्ठा kunit *test)
अणु
	काष्ठा kmem_cache *cache;
	माप_प्रकार size = 200;
	अक्षर *p[10];
	bool ret;
	पूर्णांक i;

	cache = kmem_cache_create("test_cache", size, 0, 0, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, cache);

	ret = kmem_cache_alloc_bulk(cache, GFP_KERNEL, ARRAY_SIZE(p), (व्योम **)&p);
	अगर (!ret) अणु
		kunit_err(test, "Allocation failed: %s\n", __func__);
		kmem_cache_destroy(cache);
		वापस;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(p); i++)
		p[i][0] = p[i][size - 1] = 42;

	kmem_cache_मुक्त_bulk(cache, ARRAY_SIZE(p), (व्योम **)&p);
	kmem_cache_destroy(cache);
पूर्ण

अटल अक्षर global_array[10];

अटल व्योम kasan_global_oob(काष्ठा kunit *test)
अणु
	/*
	 * Deliberate out-of-bounds access. To prevent CONFIG_UBSAN_LOCAL_BOUNDS
	 * from failing here and panicing the kernel, access the array via a
	 * अस्थिर poपूर्णांकer, which will prevent the compiler from being able to
	 * determine the array bounds.
	 *
	 * This access uses a अस्थिर poपूर्णांकer to अक्षर (अक्षर *अस्थिर) rather
	 * than the more conventional poपूर्णांकer to अस्थिर अक्षर (अस्थिर अक्षर *)
	 * because we want to prevent the compiler from making inferences about
	 * the poपूर्णांकer itself (i.e. its array bounds), not the data that it
	 * refers to.
	 */
	अक्षर *अस्थिर array = global_array;
	अक्षर *p = &array[ARRAY_SIZE(global_array) + 3];

	/* Only generic mode instruments globals. */
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_GENERIC);

	KUNIT_EXPECT_KASAN_FAIL(test, *(अस्थिर अक्षर *)p);
पूर्ण

/* Check that ksize() makes the whole object accessible. */
अटल व्योम ksize_unpoisons_memory(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 123, real_size;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);
	real_size = ksize(ptr);

	/* This access shouldn't trigger a KASAN report. */
	ptr[size] = 'x';

	/* This one must. */
	KUNIT_EXPECT_KASAN_FAIL(test, ptr[real_size] = 'y');

	kमुक्त(ptr);
पूर्ण

/*
 * Check that a use-after-मुक्त is detected by ksize() and via normal accesses
 * after it.
 */
अटल व्योम ksize_uaf(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	पूर्णांक size = 128 - KASAN_GRANULE_SIZE;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);
	kमुक्त(ptr);

	KUNIT_EXPECT_KASAN_FAIL(test, ksize(ptr));
	KUNIT_EXPECT_KASAN_FAIL(test, kasan_पूर्णांक_result = *ptr);
	KUNIT_EXPECT_KASAN_FAIL(test, kasan_पूर्णांक_result = *(ptr + size));
पूर्ण

अटल व्योम kasan_stack_oob(काष्ठा kunit *test)
अणु
	अक्षर stack_array[10];
	/* See comment in kasan_global_oob. */
	अक्षर *अस्थिर array = stack_array;
	अक्षर *p = &array[ARRAY_SIZE(stack_array) + OOB_TAG_OFF];

	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_STACK);

	KUNIT_EXPECT_KASAN_FAIL(test, *(अस्थिर अक्षर *)p);
पूर्ण

अटल व्योम kasan_alloca_oob_left(काष्ठा kunit *test)
अणु
	अस्थिर पूर्णांक i = 10;
	अक्षर alloca_array[i];
	/* See comment in kasan_global_oob. */
	अक्षर *अस्थिर array = alloca_array;
	अक्षर *p = array - 1;

	/* Only generic mode instruments dynamic allocas. */
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_GENERIC);
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_STACK);

	KUNIT_EXPECT_KASAN_FAIL(test, *(अस्थिर अक्षर *)p);
पूर्ण

अटल व्योम kasan_alloca_oob_right(काष्ठा kunit *test)
अणु
	अस्थिर पूर्णांक i = 10;
	अक्षर alloca_array[i];
	/* See comment in kasan_global_oob. */
	अक्षर *अस्थिर array = alloca_array;
	अक्षर *p = array + i;

	/* Only generic mode instruments dynamic allocas. */
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_GENERIC);
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_STACK);

	KUNIT_EXPECT_KASAN_FAIL(test, *(अस्थिर अक्षर *)p);
पूर्ण

अटल व्योम kmem_cache_द्विगुन_मुक्त(काष्ठा kunit *test)
अणु
	अक्षर *p;
	माप_प्रकार size = 200;
	काष्ठा kmem_cache *cache;

	cache = kmem_cache_create("test_cache", size, 0, 0, शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, cache);

	p = kmem_cache_alloc(cache, GFP_KERNEL);
	अगर (!p) अणु
		kunit_err(test, "Allocation failed: %s\n", __func__);
		kmem_cache_destroy(cache);
		वापस;
	पूर्ण

	kmem_cache_मुक्त(cache, p);
	KUNIT_EXPECT_KASAN_FAIL(test, kmem_cache_मुक्त(cache, p));
	kmem_cache_destroy(cache);
पूर्ण

अटल व्योम kmem_cache_invalid_मुक्त(काष्ठा kunit *test)
अणु
	अक्षर *p;
	माप_प्रकार size = 200;
	काष्ठा kmem_cache *cache;

	cache = kmem_cache_create("test_cache", size, 0, SLAB_TYPESAFE_BY_RCU,
				  शून्य);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, cache);

	p = kmem_cache_alloc(cache, GFP_KERNEL);
	अगर (!p) अणु
		kunit_err(test, "Allocation failed: %s\n", __func__);
		kmem_cache_destroy(cache);
		वापस;
	पूर्ण

	/* Trigger invalid मुक्त, the object करोesn't get मुक्तd. */
	KUNIT_EXPECT_KASAN_FAIL(test, kmem_cache_मुक्त(cache, p + 1));

	/*
	 * Properly मुक्त the object to prevent the "Objects reमुख्यing in
	 * test_cache on __kmem_cache_shutकरोwn" BUG failure.
	 */
	kmem_cache_मुक्त(cache, p);

	kmem_cache_destroy(cache);
पूर्ण

अटल व्योम kasan_स_प्रथम(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 24;

	/*
	 * str* functions are not instrumented with CONFIG_AMD_MEM_ENCRYPT.
	 * See https://bugzilla.kernel.org/show_bug.cgi?id=206337 क्रम details.
	 */
	KASAN_TEST_NEEDS_CONFIG_OFF(test, CONFIG_AMD_MEM_ENCRYPT);

	अगर (OOB_TAG_OFF)
		size = round_up(size, OOB_TAG_OFF);

	ptr = kदो_स्मृति(size, GFP_KERNEL | __GFP_ZERO);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	KUNIT_EXPECT_KASAN_FAIL(test,
		kasan_ptr_result = स_प्रथम(ptr, '1', size + 1));

	kमुक्त(ptr);
पूर्ण

अटल व्योम kasan_स_भेद(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 24;
	पूर्णांक arr[9];

	/*
	 * str* functions are not instrumented with CONFIG_AMD_MEM_ENCRYPT.
	 * See https://bugzilla.kernel.org/show_bug.cgi?id=206337 क्रम details.
	 */
	KASAN_TEST_NEEDS_CONFIG_OFF(test, CONFIG_AMD_MEM_ENCRYPT);

	अगर (OOB_TAG_OFF)
		size = round_up(size, OOB_TAG_OFF);

	ptr = kदो_स्मृति(size, GFP_KERNEL | __GFP_ZERO);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);
	स_रखो(arr, 0, माप(arr));

	KUNIT_EXPECT_KASAN_FAIL(test,
		kasan_पूर्णांक_result = स_भेद(ptr, arr, size+1));
	kमुक्त(ptr);
पूर्ण

अटल व्योम kasan_strings(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 24;

	/*
	 * str* functions are not instrumented with CONFIG_AMD_MEM_ENCRYPT.
	 * See https://bugzilla.kernel.org/show_bug.cgi?id=206337 क्रम details.
	 */
	KASAN_TEST_NEEDS_CONFIG_OFF(test, CONFIG_AMD_MEM_ENCRYPT);

	ptr = kदो_स्मृति(size, GFP_KERNEL | __GFP_ZERO);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	kमुक्त(ptr);

	/*
	 * Try to cause only 1 invalid access (less spam in dmesg).
	 * For that we need ptr to poपूर्णांक to zeroed byte.
	 * Skip metadata that could be stored in मुक्तd object so ptr
	 * will likely poपूर्णांक to zeroed byte.
	 */
	ptr += 16;
	KUNIT_EXPECT_KASAN_FAIL(test, kasan_ptr_result = म_अक्षर(ptr, '1'));

	KUNIT_EXPECT_KASAN_FAIL(test, kasan_ptr_result = म_खोजप(ptr, '1'));

	KUNIT_EXPECT_KASAN_FAIL(test, kasan_पूर्णांक_result = म_भेद(ptr, "2"));

	KUNIT_EXPECT_KASAN_FAIL(test, kasan_पूर्णांक_result = म_भेदन(ptr, "2", 1));

	KUNIT_EXPECT_KASAN_FAIL(test, kasan_पूर्णांक_result = म_माप(ptr));

	KUNIT_EXPECT_KASAN_FAIL(test, kasan_पूर्णांक_result = strnlen(ptr, 1));
पूर्ण

अटल व्योम kasan_bitops_modअगरy(काष्ठा kunit *test, पूर्णांक nr, व्योम *addr)
अणु
	KUNIT_EXPECT_KASAN_FAIL(test, set_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, __set_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, clear_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, __clear_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, clear_bit_unlock(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, __clear_bit_unlock(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, change_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, __change_bit(nr, addr));
पूर्ण

अटल व्योम kasan_bitops_test_and_modअगरy(काष्ठा kunit *test, पूर्णांक nr, व्योम *addr)
अणु
	KUNIT_EXPECT_KASAN_FAIL(test, test_and_set_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, __test_and_set_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, test_and_set_bit_lock(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, test_and_clear_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, __test_and_clear_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, test_and_change_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, __test_and_change_bit(nr, addr));
	KUNIT_EXPECT_KASAN_FAIL(test, kasan_पूर्णांक_result = test_bit(nr, addr));

#अगर defined(clear_bit_unlock_is_negative_byte)
	KUNIT_EXPECT_KASAN_FAIL(test, kasan_पूर्णांक_result =
				clear_bit_unlock_is_negative_byte(nr, addr));
#पूर्ण_अगर
पूर्ण

अटल व्योम kasan_bitops_generic(काष्ठा kunit *test)
अणु
	दीर्घ *bits;

	/* This test is specअगरically crafted क्रम the generic mode. */
	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_GENERIC);

	/*
	 * Allocate 1 more byte, which causes kzalloc to round up to 16 bytes;
	 * this way we करो not actually corrupt other memory.
	 */
	bits = kzalloc(माप(*bits) + 1, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, bits);

	/*
	 * Below calls try to access bit within allocated memory; however, the
	 * below accesses are still out-of-bounds, since bitops are defined to
	 * operate on the whole दीर्घ the bit is in.
	 */
	kasan_bitops_modअगरy(test, BITS_PER_LONG, bits);

	/*
	 * Below calls try to access bit beyond allocated memory.
	 */
	kasan_bitops_test_and_modअगरy(test, BITS_PER_LONG + BITS_PER_BYTE, bits);

	kमुक्त(bits);
पूर्ण

अटल व्योम kasan_bitops_tags(काष्ठा kunit *test)
अणु
	दीर्घ *bits;

	/* This test is specअगरically crafted क्रम tag-based modes. */
	KASAN_TEST_NEEDS_CONFIG_OFF(test, CONFIG_KASAN_GENERIC);

	/* kदो_स्मृति-64 cache will be used and the last 16 bytes will be the redzone. */
	bits = kzalloc(48, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, bits);

	/* Do the accesses past the 48 allocated bytes, but within the reकरोne. */
	kasan_bitops_modअगरy(test, BITS_PER_LONG, (व्योम *)bits + 48);
	kasan_bitops_test_and_modअगरy(test, BITS_PER_LONG + BITS_PER_BYTE, (व्योम *)bits + 48);

	kमुक्त(bits);
पूर्ण

अटल व्योम kदो_स्मृति_द्विगुन_kzमुक्त(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	माप_प्रकार size = 16;

	ptr = kदो_स्मृति(size, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	kमुक्त_sensitive(ptr);
	KUNIT_EXPECT_KASAN_FAIL(test, kमुक्त_sensitive(ptr));
पूर्ण

अटल व्योम vदो_स्मृति_oob(काष्ठा kunit *test)
अणु
	व्योम *area;

	KASAN_TEST_NEEDS_CONFIG_ON(test, CONFIG_KASAN_VMALLOC);

	/*
	 * We have to be careful not to hit the guard page.
	 * The MMU will catch that and crash us.
	 */
	area = vदो_स्मृति(3000);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, area);

	KUNIT_EXPECT_KASAN_FAIL(test, ((अस्थिर अक्षर *)area)[3100]);
	vमुक्त(area);
पूर्ण

/*
 * Check that the asचिन्हित poपूर्णांकer tag falls within the [KASAN_TAG_MIN,
 * KASAN_TAG_KERNEL) range (note: excluding the match-all tag) क्रम tag-based
 * modes.
 */
अटल व्योम match_all_not_asचिन्हित(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	काष्ठा page *pages;
	पूर्णांक i, size, order;

	KASAN_TEST_NEEDS_CONFIG_OFF(test, CONFIG_KASAN_GENERIC);

	क्रम (i = 0; i < 256; i++) अणु
		size = (get_अक्रमom_पूर्णांक() % 1024) + 1;
		ptr = kदो_स्मृति(size, GFP_KERNEL);
		KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);
		KUNIT_EXPECT_GE(test, (u8)get_tag(ptr), (u8)KASAN_TAG_MIN);
		KUNIT_EXPECT_LT(test, (u8)get_tag(ptr), (u8)KASAN_TAG_KERNEL);
		kमुक्त(ptr);
	पूर्ण

	क्रम (i = 0; i < 256; i++) अणु
		order = (get_अक्रमom_पूर्णांक() % 4) + 1;
		pages = alloc_pages(GFP_KERNEL, order);
		ptr = page_address(pages);
		KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);
		KUNIT_EXPECT_GE(test, (u8)get_tag(ptr), (u8)KASAN_TAG_MIN);
		KUNIT_EXPECT_LT(test, (u8)get_tag(ptr), (u8)KASAN_TAG_KERNEL);
		मुक्त_pages((अचिन्हित दीर्घ)ptr, order);
	पूर्ण
पूर्ण

/* Check that 0xff works as a match-all poपूर्णांकer tag क्रम tag-based modes. */
अटल व्योम match_all_ptr_tag(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	u8 tag;

	KASAN_TEST_NEEDS_CONFIG_OFF(test, CONFIG_KASAN_GENERIC);

	ptr = kदो_स्मृति(128, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);

	/* Backup the asचिन्हित tag. */
	tag = get_tag(ptr);
	KUNIT_EXPECT_NE(test, tag, (u8)KASAN_TAG_KERNEL);

	/* Reset the tag to 0xff.*/
	ptr = set_tag(ptr, KASAN_TAG_KERNEL);

	/* This access shouldn't trigger a KASAN report. */
	*ptr = 0;

	/* Recover the poपूर्णांकer tag and मुक्त. */
	ptr = set_tag(ptr, tag);
	kमुक्त(ptr);
पूर्ण

/* Check that there are no match-all memory tags क्रम tag-based modes. */
अटल व्योम match_all_mem_tag(काष्ठा kunit *test)
अणु
	अक्षर *ptr;
	पूर्णांक tag;

	KASAN_TEST_NEEDS_CONFIG_OFF(test, CONFIG_KASAN_GENERIC);

	ptr = kदो_स्मृति(128, GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_शून्य(test, ptr);
	KUNIT_EXPECT_NE(test, (u8)get_tag(ptr), (u8)KASAN_TAG_KERNEL);

	/* For each possible tag value not matching the poपूर्णांकer tag. */
	क्रम (tag = KASAN_TAG_MIN; tag <= KASAN_TAG_KERNEL; tag++) अणु
		अगर (tag == get_tag(ptr))
			जारी;

		/* Mark the first memory granule with the chosen memory tag. */
		kasan_poison(ptr, KASAN_GRANULE_SIZE, (u8)tag, false);

		/* This access must cause a KASAN report. */
		KUNIT_EXPECT_KASAN_FAIL(test, *ptr = 0);
	पूर्ण

	/* Recover the memory tag and मुक्त. */
	kasan_poison(ptr, KASAN_GRANULE_SIZE, get_tag(ptr), false);
	kमुक्त(ptr);
पूर्ण

अटल काष्ठा kunit_हाल kasan_kunit_test_हालs[] = अणु
	KUNIT_CASE(kदो_स्मृति_oob_right),
	KUNIT_CASE(kदो_स्मृति_oob_left),
	KUNIT_CASE(kदो_स्मृति_node_oob_right),
	KUNIT_CASE(kदो_स्मृति_pagealloc_oob_right),
	KUNIT_CASE(kदो_स्मृति_pagealloc_uaf),
	KUNIT_CASE(kदो_स्मृति_pagealloc_invalid_मुक्त),
	KUNIT_CASE(pagealloc_oob_right),
	KUNIT_CASE(pagealloc_uaf),
	KUNIT_CASE(kदो_स्मृति_large_oob_right),
	KUNIT_CASE(kपुनः_स्मृति_more_oob),
	KUNIT_CASE(kपुनः_स्मृति_less_oob),
	KUNIT_CASE(kपुनः_स्मृति_pagealloc_more_oob),
	KUNIT_CASE(kपुनः_स्मृति_pagealloc_less_oob),
	KUNIT_CASE(kपुनः_स्मृति_uaf),
	KUNIT_CASE(kदो_स्मृति_oob_16),
	KUNIT_CASE(kदो_स्मृति_uaf_16),
	KUNIT_CASE(kदो_स्मृति_oob_in_स_रखो),
	KUNIT_CASE(kदो_स्मृति_oob_स_रखो_2),
	KUNIT_CASE(kदो_स्मृति_oob_स_रखो_4),
	KUNIT_CASE(kदो_स्मृति_oob_स_रखो_8),
	KUNIT_CASE(kदो_स्मृति_oob_स_रखो_16),
	KUNIT_CASE(kदो_स्मृति_स_हटाओ_invalid_size),
	KUNIT_CASE(kदो_स्मृति_uaf),
	KUNIT_CASE(kदो_स्मृति_uaf_स_रखो),
	KUNIT_CASE(kदो_स्मृति_uaf2),
	KUNIT_CASE(kमुक्त_via_page),
	KUNIT_CASE(kमुक्त_via_phys),
	KUNIT_CASE(kmem_cache_oob),
	KUNIT_CASE(kmem_cache_accounted),
	KUNIT_CASE(kmem_cache_bulk),
	KUNIT_CASE(kasan_global_oob),
	KUNIT_CASE(kasan_stack_oob),
	KUNIT_CASE(kasan_alloca_oob_left),
	KUNIT_CASE(kasan_alloca_oob_right),
	KUNIT_CASE(ksize_unpoisons_memory),
	KUNIT_CASE(ksize_uaf),
	KUNIT_CASE(kmem_cache_द्विगुन_मुक्त),
	KUNIT_CASE(kmem_cache_invalid_मुक्त),
	KUNIT_CASE(kasan_स_प्रथम),
	KUNIT_CASE(kasan_स_भेद),
	KUNIT_CASE(kasan_strings),
	KUNIT_CASE(kasan_bitops_generic),
	KUNIT_CASE(kasan_bitops_tags),
	KUNIT_CASE(kदो_स्मृति_द्विगुन_kzमुक्त),
	KUNIT_CASE(vदो_स्मृति_oob),
	KUNIT_CASE(match_all_not_asचिन्हित),
	KUNIT_CASE(match_all_ptr_tag),
	KUNIT_CASE(match_all_mem_tag),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite kasan_kunit_test_suite = अणु
	.name = "kasan",
	.init = kasan_test_init,
	.test_हालs = kasan_kunit_test_हालs,
	.निकास = kasan_test_निकास,
पूर्ण;

kunit_test_suite(kasan_kunit_test_suite);

MODULE_LICENSE("GPL");
