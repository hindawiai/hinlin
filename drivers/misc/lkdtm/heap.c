<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is क्रम all the tests relating directly to heap memory, including
 * page allocation and slab allocations.
 */
#समावेश "lkdtm.h"
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>

अटल काष्ठा kmem_cache *द्विगुन_मुक्त_cache;
अटल काष्ठा kmem_cache *a_cache;
अटल काष्ठा kmem_cache *b_cache;

/*
 * This tries to stay within the next largest घातer-of-2 kदो_स्मृति cache
 * to aव्योम actually overwriting anything important अगर it's not detected
 * correctly.
 */
व्योम lkdपंचांग_OVERWRITE_ALLOCATION(व्योम)
अणु
	माप_प्रकार len = 1020;
	u32 *data = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!data)
		वापस;

	data[1024 / माप(u32)] = 0x12345678;
	kमुक्त(data);
पूर्ण

व्योम lkdपंचांग_WRITE_AFTER_FREE(व्योम)
अणु
	पूर्णांक *base, *again;
	माप_प्रकार len = 1024;
	/*
	 * The slub allocator uses the first word to store the मुक्त
	 * poपूर्णांकer in some configurations. Use the middle of the
	 * allocation to aव्योम running पूर्णांकo the मुक्तlist
	 */
	माप_प्रकार offset = (len / माप(*base)) / 2;

	base = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!base)
		वापस;
	pr_info("Allocated memory %p-%p\n", base, &base[offset * 2]);
	pr_info("Attempting bad write to freed memory at %p\n",
		&base[offset]);
	kमुक्त(base);
	base[offset] = 0x0abcdef0;
	/* Attempt to notice the overग_लिखो. */
	again = kदो_स्मृति(len, GFP_KERNEL);
	kमुक्त(again);
	अगर (again != base)
		pr_info("Hmm, didn't get the same memory range.\n");
पूर्ण

व्योम lkdपंचांग_READ_AFTER_FREE(व्योम)
अणु
	पूर्णांक *base, *val, saw;
	माप_प्रकार len = 1024;
	/*
	 * The slub allocator will use the either the first word or
	 * the middle of the allocation to store the मुक्त poपूर्णांकer,
	 * depending on configurations. Store in the second word to
	 * aव्योम running पूर्णांकo the मुक्तlist.
	 */
	माप_प्रकार offset = माप(*base);

	base = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!base) अणु
		pr_info("Unable to allocate base memory.\n");
		वापस;
	पूर्ण

	val = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!val) अणु
		pr_info("Unable to allocate val memory.\n");
		kमुक्त(base);
		वापस;
	पूर्ण

	*val = 0x12345678;
	base[offset] = *val;
	pr_info("Value in memory before free: %x\n", base[offset]);

	kमुक्त(base);

	pr_info("Attempting bad read from freed memory\n");
	saw = base[offset];
	अगर (saw != *val) अणु
		/* Good! Poisoning happened, so declare a win. */
		pr_info("Memory correctly poisoned (%x)\n", saw);
		BUG();
	पूर्ण
	pr_info("Memory was not poisoned\n");

	kमुक्त(val);
पूर्ण

व्योम lkdपंचांग_WRITE_BUDDY_AFTER_FREE(व्योम)
अणु
	अचिन्हित दीर्घ p = __get_मुक्त_page(GFP_KERNEL);
	अगर (!p) अणु
		pr_info("Unable to allocate free page\n");
		वापस;
	पूर्ण

	pr_info("Writing to the buddy page before free\n");
	स_रखो((व्योम *)p, 0x3, PAGE_SIZE);
	मुक्त_page(p);
	schedule();
	pr_info("Attempting bad write to the buddy page after free\n");
	स_रखो((व्योम *)p, 0x78, PAGE_SIZE);
	/* Attempt to notice the overग_लिखो. */
	p = __get_मुक्त_page(GFP_KERNEL);
	मुक्त_page(p);
	schedule();
पूर्ण

व्योम lkdपंचांग_READ_BUDDY_AFTER_FREE(व्योम)
अणु
	अचिन्हित दीर्घ p = __get_मुक्त_page(GFP_KERNEL);
	पूर्णांक saw, *val;
	पूर्णांक *base;

	अगर (!p) अणु
		pr_info("Unable to allocate free page\n");
		वापस;
	पूर्ण

	val = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (!val) अणु
		pr_info("Unable to allocate val memory.\n");
		मुक्त_page(p);
		वापस;
	पूर्ण

	base = (पूर्णांक *)p;

	*val = 0x12345678;
	base[0] = *val;
	pr_info("Value in memory before free: %x\n", base[0]);
	मुक्त_page(p);
	pr_info("Attempting to read from freed memory\n");
	saw = base[0];
	अगर (saw != *val) अणु
		/* Good! Poisoning happened, so declare a win. */
		pr_info("Memory correctly poisoned (%x)\n", saw);
		BUG();
	पूर्ण
	pr_info("Buddy page was not poisoned\n");

	kमुक्त(val);
पूर्ण

व्योम lkdपंचांग_SLAB_FREE_DOUBLE(व्योम)
अणु
	पूर्णांक *val;

	val = kmem_cache_alloc(द्विगुन_मुक्त_cache, GFP_KERNEL);
	अगर (!val) अणु
		pr_info("Unable to allocate double_free_cache memory.\n");
		वापस;
	पूर्ण

	/* Just make sure we got real memory. */
	*val = 0x12345678;
	pr_info("Attempting double slab free ...\n");
	kmem_cache_मुक्त(द्विगुन_मुक्त_cache, val);
	kmem_cache_मुक्त(द्विगुन_मुक्त_cache, val);
पूर्ण

व्योम lkdपंचांग_SLAB_FREE_CROSS(व्योम)
अणु
	पूर्णांक *val;

	val = kmem_cache_alloc(a_cache, GFP_KERNEL);
	अगर (!val) अणु
		pr_info("Unable to allocate a_cache memory.\n");
		वापस;
	पूर्ण

	/* Just make sure we got real memory. */
	*val = 0x12345679;
	pr_info("Attempting cross-cache slab free ...\n");
	kmem_cache_मुक्त(b_cache, val);
पूर्ण

व्योम lkdपंचांग_SLAB_FREE_PAGE(व्योम)
अणु
	अचिन्हित दीर्घ p = __get_मुक्त_page(GFP_KERNEL);

	pr_info("Attempting non-Slab slab free ...\n");
	kmem_cache_मुक्त(शून्य, (व्योम *)p);
	मुक्त_page(p);
पूर्ण

/*
 * We have स्थिरructors to keep the caches distinctly separated without
 * needing to boot with "slab_nomerge".
 */
अटल व्योम ctor_द्विगुन_मुक्त(व्योम *region)
अणु पूर्ण
अटल व्योम ctor_a(व्योम *region)
अणु पूर्ण
अटल व्योम ctor_b(व्योम *region)
अणु पूर्ण

व्योम __init lkdपंचांग_heap_init(व्योम)
अणु
	द्विगुन_मुक्त_cache = kmem_cache_create("lkdtm-heap-double_free",
					      64, 0, 0, ctor_द्विगुन_मुक्त);
	a_cache = kmem_cache_create("lkdtm-heap-a", 64, 0, 0, ctor_a);
	b_cache = kmem_cache_create("lkdtm-heap-b", 64, 0, 0, ctor_b);
पूर्ण

व्योम __निकास lkdपंचांग_heap_निकास(व्योम)
अणु
	kmem_cache_destroy(द्विगुन_मुक्त_cache);
	kmem_cache_destroy(a_cache);
	kmem_cache_destroy(b_cache);
पूर्ण
