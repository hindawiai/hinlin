<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Test हालs क्रम SL[AOU]B/page initialization at alloc/मुक्त समय.
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>

#घोषणा GARBAGE_INT (0x09A7BA9E)
#घोषणा GARBAGE_BYTE (0x9E)

#घोषणा REPORT_FAILURES_IN_FN() \
	करो अणु	\
		अगर (failures)	\
			pr_info("%s failed %d out of %d times\n",	\
				__func__, failures, num_tests);		\
		अन्यथा		\
			pr_info("all %d tests in %s passed\n",		\
				num_tests, __func__);			\
	पूर्ण जबतक (0)

/* Calculate the number of uninitialized bytes in the buffer. */
अटल पूर्णांक __init count_nonzero_bytes(व्योम *ptr, माप_प्रकार size)
अणु
	पूर्णांक i, ret = 0;
	अचिन्हित अक्षर *p = (अचिन्हित अक्षर *)ptr;

	क्रम (i = 0; i < size; i++)
		अगर (p[i])
			ret++;
	वापस ret;
पूर्ण

/* Fill a buffer with garbage, skipping |skip| first bytes. */
अटल व्योम __init fill_with_garbage_skip(व्योम *ptr, पूर्णांक size, माप_प्रकार skip)
अणु
	अचिन्हित पूर्णांक *p = (अचिन्हित पूर्णांक *)((अक्षर *)ptr + skip);
	पूर्णांक i = 0;

	WARN_ON(skip > size);
	size -= skip;

	जबतक (size >= माप(*p)) अणु
		p[i] = GARBAGE_INT;
		i++;
		size -= माप(*p);
	पूर्ण
	अगर (size)
		स_रखो(&p[i], GARBAGE_BYTE, size);
पूर्ण

अटल व्योम __init fill_with_garbage(व्योम *ptr, माप_प्रकार size)
अणु
	fill_with_garbage_skip(ptr, size, 0);
पूर्ण

अटल पूर्णांक __init करो_alloc_pages_order(पूर्णांक order, पूर्णांक *total_failures)
अणु
	काष्ठा page *page;
	व्योम *buf;
	माप_प्रकार size = PAGE_SIZE << order;

	page = alloc_pages(GFP_KERNEL, order);
	buf = page_address(page);
	fill_with_garbage(buf, size);
	__मुक्त_pages(page, order);

	page = alloc_pages(GFP_KERNEL, order);
	buf = page_address(page);
	अगर (count_nonzero_bytes(buf, size))
		(*total_failures)++;
	fill_with_garbage(buf, size);
	__मुक्त_pages(page, order);
	वापस 1;
पूर्ण

/* Test the page allocator by calling alloc_pages with dअगरferent orders. */
अटल पूर्णांक __init test_pages(पूर्णांक *total_failures)
अणु
	पूर्णांक failures = 0, num_tests = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++)
		num_tests += करो_alloc_pages_order(i, &failures);

	REPORT_FAILURES_IN_FN();
	*total_failures += failures;
	वापस num_tests;
पूर्ण

/* Test kदो_स्मृति() with given parameters. */
अटल पूर्णांक __init करो_kदो_स्मृति_size(माप_प्रकार size, पूर्णांक *total_failures)
अणु
	व्योम *buf;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	fill_with_garbage(buf, size);
	kमुक्त(buf);

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (count_nonzero_bytes(buf, size))
		(*total_failures)++;
	fill_with_garbage(buf, size);
	kमुक्त(buf);
	वापस 1;
पूर्ण

/* Test vदो_स्मृति() with given parameters. */
अटल पूर्णांक __init करो_vदो_स्मृति_size(माप_प्रकार size, पूर्णांक *total_failures)
अणु
	व्योम *buf;

	buf = vदो_स्मृति(size);
	fill_with_garbage(buf, size);
	vमुक्त(buf);

	buf = vदो_स्मृति(size);
	अगर (count_nonzero_bytes(buf, size))
		(*total_failures)++;
	fill_with_garbage(buf, size);
	vमुक्त(buf);
	वापस 1;
पूर्ण

/* Test kदो_स्मृति()/vदो_स्मृति() by allocating objects of dअगरferent sizes. */
अटल पूर्णांक __init test_kvदो_स्मृति(पूर्णांक *total_failures)
अणु
	पूर्णांक failures = 0, num_tests = 0;
	पूर्णांक i, size;

	क्रम (i = 0; i < 20; i++) अणु
		size = 1 << i;
		num_tests += करो_kदो_स्मृति_size(size, &failures);
		num_tests += करो_vदो_स्मृति_size(size, &failures);
	पूर्ण

	REPORT_FAILURES_IN_FN();
	*total_failures += failures;
	वापस num_tests;
पूर्ण

#घोषणा CTOR_BYTES (माप(अचिन्हित पूर्णांक))
#घोषणा CTOR_PATTERN (0x41414141)
/* Initialize the first 4 bytes of the object. */
अटल व्योम test_ctor(व्योम *obj)
अणु
	*(अचिन्हित पूर्णांक *)obj = CTOR_PATTERN;
पूर्ण

/*
 * Check the invariants क्रम the buffer allocated from a slab cache.
 * If the cache has a test स्थिरructor, the first 4 bytes of the object must
 * always reमुख्य equal to CTOR_PATTERN.
 * If the cache isn't an RCU-typesafe one, or अगर the allocation is करोne with
 * __GFP_ZERO, then the object contents must be zeroed after allocation.
 * If the cache is an RCU-typesafe one, the object contents must never be
 * zeroed after the first use. This is checked by स_भेद() in
 * करो_kmem_cache_size().
 */
अटल bool __init check_buf(व्योम *buf, पूर्णांक size, bool want_ctor,
			     bool want_rcu, bool want_zero)
अणु
	पूर्णांक bytes;
	bool fail = false;

	bytes = count_nonzero_bytes(buf, size);
	WARN_ON(want_ctor && want_zero);
	अगर (want_zero)
		वापस bytes;
	अगर (want_ctor) अणु
		अगर (*(अचिन्हित पूर्णांक *)buf != CTOR_PATTERN)
			fail = 1;
	पूर्ण अन्यथा अणु
		अगर (bytes)
			fail = !want_rcu;
	पूर्ण
	वापस fail;
पूर्ण

#घोषणा BULK_SIZE 100
अटल व्योम *bulk_array[BULK_SIZE];

/*
 * Test kmem_cache with given parameters:
 *  want_ctor - use a स्थिरructor;
 *  want_rcu - use SLAB_TYPESAFE_BY_RCU;
 *  want_zero - use __GFP_ZERO.
 */
अटल पूर्णांक __init करो_kmem_cache_size(माप_प्रकार size, bool want_ctor,
				     bool want_rcu, bool want_zero,
				     पूर्णांक *total_failures)
अणु
	काष्ठा kmem_cache *c;
	पूर्णांक iter;
	bool fail = false;
	gfp_t alloc_mask = GFP_KERNEL | (want_zero ? __GFP_ZERO : 0);
	व्योम *buf, *buf_copy;

	c = kmem_cache_create("test_cache", size, 1,
			      want_rcu ? SLAB_TYPESAFE_BY_RCU : 0,
			      want_ctor ? test_ctor : शून्य);
	क्रम (iter = 0; iter < 10; iter++) अणु
		/* Do a test of bulk allocations */
		अगर (!want_rcu && !want_ctor) अणु
			पूर्णांक ret;

			ret = kmem_cache_alloc_bulk(c, alloc_mask, BULK_SIZE, bulk_array);
			अगर (!ret) अणु
				fail = true;
			पूर्ण अन्यथा अणु
				पूर्णांक i;
				क्रम (i = 0; i < ret; i++)
					fail |= check_buf(bulk_array[i], size, want_ctor, want_rcu, want_zero);
				kmem_cache_मुक्त_bulk(c, ret, bulk_array);
			पूर्ण
		पूर्ण

		buf = kmem_cache_alloc(c, alloc_mask);
		/* Check that buf is zeroed, अगर it must be. */
		fail |= check_buf(buf, size, want_ctor, want_rcu, want_zero);
		fill_with_garbage_skip(buf, size, want_ctor ? CTOR_BYTES : 0);

		अगर (!want_rcu) अणु
			kmem_cache_मुक्त(c, buf);
			जारी;
		पूर्ण

		/*
		 * If this is an RCU cache, use a critical section to ensure we
		 * can touch objects after they're मुक्तd.
		 */
		rcu_पढ़ो_lock();
		/*
		 * Copy the buffer to check that it's not wiped on
		 * मुक्त().
		 */
		buf_copy = kदो_स्मृति(size, GFP_ATOMIC);
		अगर (buf_copy)
			स_नकल(buf_copy, buf, size);

		kmem_cache_मुक्त(c, buf);
		/*
		 * Check that |buf| is पूर्णांकact after kmem_cache_मुक्त().
		 * |want_zero| is false, because we wrote garbage to
		 * the buffer alपढ़ोy.
		 */
		fail |= check_buf(buf, size, want_ctor, want_rcu,
				  false);
		अगर (buf_copy) अणु
			fail |= (bool)स_भेद(buf, buf_copy, size);
			kमुक्त(buf_copy);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	kmem_cache_destroy(c);

	*total_failures += fail;
	वापस 1;
पूर्ण

/*
 * Check that the data written to an RCU-allocated object survives
 * पुनः_स्मृतिation.
 */
अटल पूर्णांक __init करो_kmem_cache_rcu_persistent(पूर्णांक size, पूर्णांक *total_failures)
अणु
	काष्ठा kmem_cache *c;
	व्योम *buf, *buf_contents, *saved_ptr;
	व्योम **used_objects;
	पूर्णांक i, iter, maxiter = 1024;
	bool fail = false;

	c = kmem_cache_create("test_cache", size, size, SLAB_TYPESAFE_BY_RCU,
			      शून्य);
	buf = kmem_cache_alloc(c, GFP_KERNEL);
	saved_ptr = buf;
	fill_with_garbage(buf, size);
	buf_contents = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf_contents)
		जाओ out;
	used_objects = kदो_स्मृति_array(maxiter, माप(व्योम *), GFP_KERNEL);
	अगर (!used_objects) अणु
		kमुक्त(buf_contents);
		जाओ out;
	पूर्ण
	स_नकल(buf_contents, buf, size);
	kmem_cache_मुक्त(c, buf);
	/*
	 * Run क्रम a fixed number of iterations. If we never hit saved_ptr,
	 * assume the test passes.
	 */
	क्रम (iter = 0; iter < maxiter; iter++) अणु
		buf = kmem_cache_alloc(c, GFP_KERNEL);
		used_objects[iter] = buf;
		अगर (buf == saved_ptr) अणु
			fail = स_भेद(buf_contents, buf, size);
			क्रम (i = 0; i <= iter; i++)
				kmem_cache_मुक्त(c, used_objects[i]);
			जाओ मुक्त_out;
		पूर्ण
	पूर्ण

मुक्त_out:
	kmem_cache_destroy(c);
	kमुक्त(buf_contents);
	kमुक्त(used_objects);
out:
	*total_failures += fail;
	वापस 1;
पूर्ण

अटल पूर्णांक __init करो_kmem_cache_size_bulk(पूर्णांक size, पूर्णांक *total_failures)
अणु
	काष्ठा kmem_cache *c;
	पूर्णांक i, iter, maxiter = 1024;
	पूर्णांक num, bytes;
	bool fail = false;
	व्योम *objects[10];

	c = kmem_cache_create("test_cache", size, size, 0, शून्य);
	क्रम (iter = 0; (iter < maxiter) && !fail; iter++) अणु
		num = kmem_cache_alloc_bulk(c, GFP_KERNEL, ARRAY_SIZE(objects),
					    objects);
		क्रम (i = 0; i < num; i++) अणु
			bytes = count_nonzero_bytes(objects[i], size);
			अगर (bytes)
				fail = true;
			fill_with_garbage(objects[i], size);
		पूर्ण

		अगर (num)
			kmem_cache_मुक्त_bulk(c, num, objects);
	पूर्ण
	*total_failures += fail;
	वापस 1;
पूर्ण

/*
 * Test kmem_cache allocation by creating caches of dअगरferent sizes, with and
 * without स्थिरructors, with and without SLAB_TYPESAFE_BY_RCU.
 */
अटल पूर्णांक __init test_kmemcache(पूर्णांक *total_failures)
अणु
	पूर्णांक failures = 0, num_tests = 0;
	पूर्णांक i, flags, size;
	bool ctor, rcu, zero;

	क्रम (i = 0; i < 10; i++) अणु
		size = 8 << i;
		क्रम (flags = 0; flags < 8; flags++) अणु
			ctor = flags & 1;
			rcu = flags & 2;
			zero = flags & 4;
			अगर (ctor & zero)
				जारी;
			num_tests += करो_kmem_cache_size(size, ctor, rcu, zero,
							&failures);
		पूर्ण
		num_tests += करो_kmem_cache_size_bulk(size, &failures);
	पूर्ण
	REPORT_FAILURES_IN_FN();
	*total_failures += failures;
	वापस num_tests;
पूर्ण

/* Test the behavior of SLAB_TYPESAFE_BY_RCU caches of dअगरferent sizes. */
अटल पूर्णांक __init test_rcu_persistent(पूर्णांक *total_failures)
अणु
	पूर्णांक failures = 0, num_tests = 0;
	पूर्णांक i, size;

	क्रम (i = 0; i < 10; i++) अणु
		size = 8 << i;
		num_tests += करो_kmem_cache_rcu_persistent(size, &failures);
	पूर्ण
	REPORT_FAILURES_IN_FN();
	*total_failures += failures;
	वापस num_tests;
पूर्ण

/*
 * Run the tests. Each test function वापसs the number of executed tests and
 * updates |failures| with the number of failed tests.
 */
अटल पूर्णांक __init test_meminit_init(व्योम)
अणु
	पूर्णांक failures = 0, num_tests = 0;

	num_tests += test_pages(&failures);
	num_tests += test_kvदो_स्मृति(&failures);
	num_tests += test_kmemcache(&failures);
	num_tests += test_rcu_persistent(&failures);

	अगर (failures == 0)
		pr_info("all %d tests passed!\n", num_tests);
	अन्यथा
		pr_info("failures: %d out of %d\n", failures, num_tests);

	वापस failures ? -EINVAL : 0;
पूर्ण
module_init(test_meminit_init);

MODULE_LICENSE("GPL");
