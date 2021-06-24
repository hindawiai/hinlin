<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * idr-test.c: Test the IDR API
 * Copyright (c) 2016 Matthew Wilcox <willy@infradead.org>
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश "test.h"

#घोषणा DUMMY_PTR	((व्योम *)0x10)

पूर्णांक item_idr_मुक्त(पूर्णांक id, व्योम *p, व्योम *data)
अणु
	काष्ठा item *item = p;
	निश्चित(item->index == id);
	मुक्त(p);

	वापस 0;
पूर्ण

व्योम item_idr_हटाओ(काष्ठा idr *idr, पूर्णांक id)
अणु
	काष्ठा item *item = idr_find(idr, id);
	निश्चित(item->index == id);
	idr_हटाओ(idr, id);
	मुक्त(item);
पूर्ण

व्योम idr_alloc_test(व्योम)
अणु
	अचिन्हित दीर्घ i;
	DEFINE_IDR(idr);

	निश्चित(idr_alloc_cyclic(&idr, DUMMY_PTR, 0, 0x4000, GFP_KERNEL) == 0);
	निश्चित(idr_alloc_cyclic(&idr, DUMMY_PTR, 0x3ffd, 0x4000, GFP_KERNEL) == 0x3ffd);
	idr_हटाओ(&idr, 0x3ffd);
	idr_हटाओ(&idr, 0);

	क्रम (i = 0x3ffe; i < 0x4003; i++) अणु
		पूर्णांक id;
		काष्ठा item *item;

		अगर (i < 0x4000)
			item = item_create(i, 0);
		अन्यथा
			item = item_create(i - 0x3fff, 0);

		id = idr_alloc_cyclic(&idr, item, 1, 0x4000, GFP_KERNEL);
		निश्चित(id == item->index);
	पूर्ण

	idr_क्रम_each(&idr, item_idr_मुक्त, &idr);
	idr_destroy(&idr);
पूर्ण

व्योम idr_replace_test(व्योम)
अणु
	DEFINE_IDR(idr);

	idr_alloc(&idr, (व्योम *)-1, 10, 11, GFP_KERNEL);
	idr_replace(&idr, &idr, 10);

	idr_destroy(&idr);
पूर्ण

/*
 * Unlike the radix tree, you can put a शून्य poपूर्णांकer -- with care -- पूर्णांकo
 * the IDR.  Some पूर्णांकerfaces, like idr_find() करो not distinguish between
 * "present, value is NULL" and "not present", but that's exactly what some
 * users want.
 */
व्योम idr_null_test(व्योम)
अणु
	पूर्णांक i;
	DEFINE_IDR(idr);

	निश्चित(idr_is_empty(&idr));

	निश्चित(idr_alloc(&idr, शून्य, 0, 0, GFP_KERNEL) == 0);
	निश्चित(!idr_is_empty(&idr));
	idr_हटाओ(&idr, 0);
	निश्चित(idr_is_empty(&idr));

	निश्चित(idr_alloc(&idr, शून्य, 0, 0, GFP_KERNEL) == 0);
	निश्चित(!idr_is_empty(&idr));
	idr_destroy(&idr);
	निश्चित(idr_is_empty(&idr));

	क्रम (i = 0; i < 10; i++) अणु
		निश्चित(idr_alloc(&idr, शून्य, 0, 0, GFP_KERNEL) == i);
	पूर्ण

	निश्चित(idr_replace(&idr, DUMMY_PTR, 3) == शून्य);
	निश्चित(idr_replace(&idr, DUMMY_PTR, 4) == शून्य);
	निश्चित(idr_replace(&idr, शून्य, 4) == DUMMY_PTR);
	निश्चित(idr_replace(&idr, DUMMY_PTR, 11) == ERR_PTR(-ENOENT));
	idr_हटाओ(&idr, 5);
	निश्चित(idr_alloc(&idr, शून्य, 0, 0, GFP_KERNEL) == 5);
	idr_हटाओ(&idr, 5);

	क्रम (i = 0; i < 9; i++) अणु
		idr_हटाओ(&idr, i);
		निश्चित(!idr_is_empty(&idr));
	पूर्ण
	idr_हटाओ(&idr, 8);
	निश्चित(!idr_is_empty(&idr));
	idr_हटाओ(&idr, 9);
	निश्चित(idr_is_empty(&idr));

	निश्चित(idr_alloc(&idr, शून्य, 0, 0, GFP_KERNEL) == 0);
	निश्चित(idr_replace(&idr, DUMMY_PTR, 3) == ERR_PTR(-ENOENT));
	निश्चित(idr_replace(&idr, DUMMY_PTR, 0) == शून्य);
	निश्चित(idr_replace(&idr, शून्य, 0) == DUMMY_PTR);

	idr_destroy(&idr);
	निश्चित(idr_is_empty(&idr));

	क्रम (i = 1; i < 10; i++) अणु
		निश्चित(idr_alloc(&idr, शून्य, 1, 0, GFP_KERNEL) == i);
	पूर्ण

	idr_destroy(&idr);
	निश्चित(idr_is_empty(&idr));
पूर्ण

व्योम idr_noरुको_test(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	DEFINE_IDR(idr);

	idr_preload(GFP_KERNEL);

	क्रम (i = 0; i < 3; i++) अणु
		काष्ठा item *item = item_create(i, 0);
		निश्चित(idr_alloc(&idr, item, i, i + 1, GFP_NOWAIT) == i);
	पूर्ण

	idr_preload_end();

	idr_क्रम_each(&idr, item_idr_मुक्त, &idr);
	idr_destroy(&idr);
पूर्ण

व्योम idr_get_next_test(पूर्णांक base)
अणु
	अचिन्हित दीर्घ i;
	पूर्णांक nextid;
	DEFINE_IDR(idr);
	idr_init_base(&idr, base);

	पूर्णांक indices[] = अणु4, 7, 9, 15, 65, 128, 1000, 99999, 0पूर्ण;

	क्रम(i = 0; indices[i]; i++) अणु
		काष्ठा item *item = item_create(indices[i], 0);
		निश्चित(idr_alloc(&idr, item, indices[i], indices[i+1],
				 GFP_KERNEL) == indices[i]);
	पूर्ण

	क्रम(i = 0, nextid = 0; indices[i]; i++) अणु
		idr_get_next(&idr, &nextid);
		निश्चित(nextid == indices[i]);
		nextid++;
	पूर्ण

	idr_क्रम_each(&idr, item_idr_मुक्त, &idr);
	idr_destroy(&idr);
पूर्ण

पूर्णांक idr_u32_cb(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	BUG_ON(id < 0);
	BUG_ON(ptr != DUMMY_PTR);
	वापस 0;
पूर्ण

व्योम idr_u32_test1(काष्ठा idr *idr, u32 handle)
अणु
	अटल bool warned = false;
	u32 id = handle;
	पूर्णांक sid = 0;
	व्योम *ptr;

	BUG_ON(idr_alloc_u32(idr, DUMMY_PTR, &id, id, GFP_KERNEL));
	BUG_ON(id != handle);
	BUG_ON(idr_alloc_u32(idr, DUMMY_PTR, &id, id, GFP_KERNEL) != -ENOSPC);
	BUG_ON(id != handle);
	अगर (!warned && id > पूर्णांक_उच्च)
		prपूर्णांकk("vvv Ignore these warnings\n");
	ptr = idr_get_next(idr, &sid);
	अगर (id > पूर्णांक_उच्च) अणु
		BUG_ON(ptr != शून्य);
		BUG_ON(sid != 0);
	पूर्ण अन्यथा अणु
		BUG_ON(ptr != DUMMY_PTR);
		BUG_ON(sid != id);
	पूर्ण
	idr_क्रम_each(idr, idr_u32_cb, शून्य);
	अगर (!warned && id > पूर्णांक_उच्च) अणु
		prपूर्णांकk("^^^ Warnings over\न");
		warned = true;
	पूर्ण
	BUG_ON(idr_हटाओ(idr, id) != DUMMY_PTR);
	BUG_ON(!idr_is_empty(idr));
पूर्ण

व्योम idr_u32_test(पूर्णांक base)
अणु
	DEFINE_IDR(idr);
	idr_init_base(&idr, base);
	idr_u32_test1(&idr, 10);
	idr_u32_test1(&idr, 0x7fffffff);
	idr_u32_test1(&idr, 0x80000000);
	idr_u32_test1(&idr, 0x80000001);
	idr_u32_test1(&idr, 0xffe00000);
	idr_u32_test1(&idr, 0xffffffff);
पूर्ण

अटल व्योम idr_align_test(काष्ठा idr *idr)
अणु
	अक्षर name[] = "Motorola 68000";
	पूर्णांक i, id;
	व्योम *entry;

	क्रम (i = 0; i < 9; i++) अणु
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != i);
		idr_क्रम_each_entry(idr, entry, id);
	पूर्ण
	idr_destroy(idr);

	क्रम (i = 1; i < 10; i++) अणु
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != i - 1);
		idr_क्रम_each_entry(idr, entry, id);
	पूर्ण
	idr_destroy(idr);

	क्रम (i = 2; i < 11; i++) अणु
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != i - 2);
		idr_क्रम_each_entry(idr, entry, id);
	पूर्ण
	idr_destroy(idr);

	क्रम (i = 3; i < 12; i++) अणु
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != i - 3);
		idr_क्रम_each_entry(idr, entry, id);
	पूर्ण
	idr_destroy(idr);

	क्रम (i = 0; i < 8; i++) अणु
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != 0);
		BUG_ON(idr_alloc(idr, &name[i + 1], 0, 0, GFP_KERNEL) != 1);
		idr_क्रम_each_entry(idr, entry, id);
		idr_हटाओ(idr, 1);
		idr_क्रम_each_entry(idr, entry, id);
		idr_हटाओ(idr, 0);
		BUG_ON(!idr_is_empty(idr));
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		BUG_ON(idr_alloc(idr, शून्य, 0, 0, GFP_KERNEL) != 0);
		idr_क्रम_each_entry(idr, entry, id);
		idr_replace(idr, &name[i], 0);
		idr_क्रम_each_entry(idr, entry, id);
		BUG_ON(idr_find(idr, 0) != &name[i]);
		idr_हटाओ(idr, 0);
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		BUG_ON(idr_alloc(idr, &name[i], 0, 0, GFP_KERNEL) != 0);
		BUG_ON(idr_alloc(idr, शून्य, 0, 0, GFP_KERNEL) != 1);
		idr_हटाओ(idr, 1);
		idr_क्रम_each_entry(idr, entry, id);
		idr_replace(idr, &name[i + 1], 0);
		idr_क्रम_each_entry(idr, entry, id);
		idr_हटाओ(idr, 0);
	पूर्ण
पूर्ण

DEFINE_IDR(find_idr);

अटल व्योम *idr_throbber(व्योम *arg)
अणु
	समय_प्रकार start = समय(शून्य);
	पूर्णांक id = *(पूर्णांक *)arg;

	rcu_रेजिस्टर_thपढ़ो();
	करो अणु
		idr_alloc(&find_idr, xa_mk_value(id), id, id + 1, GFP_KERNEL);
		idr_हटाओ(&find_idr, id);
	पूर्ण जबतक (समय(शून्य) < start + 10);
	rcu_unरेजिस्टर_thपढ़ो();

	वापस शून्य;
पूर्ण

/*
 * There are always either 1 or 2 objects in the IDR.  If we find nothing,
 * or we find something at an ID we didn't expect, that's a bug.
 */
व्योम idr_find_test_1(पूर्णांक anchor_id, पूर्णांक throbber_id)
अणु
	pthपढ़ो_t throbber;
	समय_प्रकार start = समय(शून्य);

	BUG_ON(idr_alloc(&find_idr, xa_mk_value(anchor_id), anchor_id,
				anchor_id + 1, GFP_KERNEL) != anchor_id);

	pthपढ़ो_create(&throbber, शून्य, idr_throbber, &throbber_id);

	rcu_पढ़ो_lock();
	करो अणु
		पूर्णांक id = 0;
		व्योम *entry = idr_get_next(&find_idr, &id);
		rcu_पढ़ो_unlock();
		अगर ((id != anchor_id && id != throbber_id) ||
		    entry != xa_mk_value(id)) अणु
			म_लिखो("%s(%d, %d): %p at %d\n", __func__, anchor_id,
				throbber_id, entry, id);
			पात();
		पूर्ण
		rcu_पढ़ो_lock();
	पूर्ण जबतक (समय(शून्य) < start + 11);
	rcu_पढ़ो_unlock();

	pthपढ़ो_join(throbber, शून्य);

	idr_हटाओ(&find_idr, anchor_id);
	BUG_ON(!idr_is_empty(&find_idr));
पूर्ण

व्योम idr_find_test(व्योम)
अणु
	idr_find_test_1(100000, 0);
	idr_find_test_1(0, 100000);
पूर्ण

व्योम idr_checks(व्योम)
अणु
	अचिन्हित दीर्घ i;
	DEFINE_IDR(idr);

	क्रम (i = 0; i < 10000; i++) अणु
		काष्ठा item *item = item_create(i, 0);
		निश्चित(idr_alloc(&idr, item, 0, 20000, GFP_KERNEL) == i);
	पूर्ण

	निश्चित(idr_alloc(&idr, DUMMY_PTR, 5, 30, GFP_KERNEL) < 0);

	क्रम (i = 0; i < 5000; i++)
		item_idr_हटाओ(&idr, i);

	idr_हटाओ(&idr, 3);

	idr_क्रम_each(&idr, item_idr_मुक्त, &idr);
	idr_destroy(&idr);

	निश्चित(idr_is_empty(&idr));

	idr_हटाओ(&idr, 3);
	idr_हटाओ(&idr, 0);

	निश्चित(idr_alloc(&idr, DUMMY_PTR, 0, 0, GFP_KERNEL) == 0);
	idr_हटाओ(&idr, 1);
	क्रम (i = 1; i < RADIX_TREE_MAP_SIZE; i++)
		निश्चित(idr_alloc(&idr, DUMMY_PTR, 0, 0, GFP_KERNEL) == i);
	idr_हटाओ(&idr, 1 << 30);
	idr_destroy(&idr);

	क्रम (i = पूर्णांक_उच्च - 3UL; i < पूर्णांक_उच्च + 1UL; i++) अणु
		काष्ठा item *item = item_create(i, 0);
		निश्चित(idr_alloc(&idr, item, i, i + 10, GFP_KERNEL) == i);
	पूर्ण
	निश्चित(idr_alloc(&idr, DUMMY_PTR, i - 2, i, GFP_KERNEL) == -ENOSPC);
	निश्चित(idr_alloc(&idr, DUMMY_PTR, i - 2, i + 10, GFP_KERNEL) == -ENOSPC);

	idr_क्रम_each(&idr, item_idr_मुक्त, &idr);
	idr_destroy(&idr);
	idr_destroy(&idr);

	निश्चित(idr_is_empty(&idr));

	idr_set_cursor(&idr, पूर्णांक_उच्च - 3UL);
	क्रम (i = पूर्णांक_उच्च - 3UL; i < पूर्णांक_उच्च + 3UL; i++) अणु
		काष्ठा item *item;
		अचिन्हित पूर्णांक id;
		अगर (i <= पूर्णांक_उच्च)
			item = item_create(i, 0);
		अन्यथा
			item = item_create(i - पूर्णांक_उच्च - 1, 0);

		id = idr_alloc_cyclic(&idr, item, 0, 0, GFP_KERNEL);
		निश्चित(id == item->index);
	पूर्ण

	idr_क्रम_each(&idr, item_idr_मुक्त, &idr);
	idr_destroy(&idr);
	निश्चित(idr_is_empty(&idr));

	क्रम (i = 1; i < 10000; i++) अणु
		काष्ठा item *item = item_create(i, 0);
		निश्चित(idr_alloc(&idr, item, 1, 20000, GFP_KERNEL) == i);
	पूर्ण

	idr_क्रम_each(&idr, item_idr_मुक्त, &idr);
	idr_destroy(&idr);

	idr_replace_test();
	idr_alloc_test();
	idr_null_test();
	idr_noरुको_test();
	idr_get_next_test(0);
	idr_get_next_test(1);
	idr_get_next_test(4);
	idr_u32_test(4);
	idr_u32_test(1);
	idr_u32_test(0);
	idr_align_test(&idr);
	idr_find_test();
पूर्ण

#घोषणा module_init(x)
#घोषणा module_निकास(x)
#घोषणा MODULE_AUTHOR(x)
#घोषणा MODULE_LICENSE(x)
#घोषणा dump_stack()    निश्चित(0)
व्योम ida_dump(काष्ठा ida *);

#समावेश "../../../lib/test_ida.c"

/*
 * Check that we get the correct error when we run out of memory करोing
 * allocations.  In userspace, GFP_NOWAIT will always fail an allocation.
 * The first test is क्रम not having a biपंचांगap available, and the second test
 * is क्रम not being able to allocate a level of the radix tree.
 */
व्योम ida_check_nomem(व्योम)
अणु
	DEFINE_IDA(ida);
	पूर्णांक id;

	id = ida_alloc_min(&ida, 256, GFP_NOWAIT);
	IDA_BUG_ON(&ida, id != -ENOMEM);
	id = ida_alloc_min(&ida, 1UL << 30, GFP_NOWAIT);
	IDA_BUG_ON(&ida, id != -ENOMEM);
	IDA_BUG_ON(&ida, !ida_is_empty(&ida));
पूर्ण

/*
 * Check handling of conversions between exceptional entries and full biपंचांगaps.
 */
व्योम ida_check_conv_user(व्योम)
अणु
	DEFINE_IDA(ida);
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < 1000000; i++) अणु
		पूर्णांक id = ida_alloc(&ida, GFP_NOWAIT);
		अगर (id == -ENOMEM) अणु
			IDA_BUG_ON(&ida, ((i % IDA_BITMAP_BITS) !=
					  BITS_PER_XA_VALUE) &&
					 ((i % IDA_BITMAP_BITS) != 0));
			id = ida_alloc(&ida, GFP_KERNEL);
		पूर्ण अन्यथा अणु
			IDA_BUG_ON(&ida, (i % IDA_BITMAP_BITS) ==
					BITS_PER_XA_VALUE);
		पूर्ण
		IDA_BUG_ON(&ida, id != i);
	पूर्ण
	ida_destroy(&ida);
पूर्ण

व्योम ida_check_अक्रमom(व्योम)
अणु
	DEFINE_IDA(ida);
	DECLARE_BITMAP(biपंचांगap, 2048);
	अचिन्हित पूर्णांक i;
	समय_प्रकार s = समय(शून्य);

 repeat:
	स_रखो(biपंचांगap, 0, माप(biपंचांगap));
	क्रम (i = 0; i < 100000; i++) अणु
		पूर्णांक i = अक्रम();
		पूर्णांक bit = i & 2047;
		अगर (test_bit(bit, biपंचांगap)) अणु
			__clear_bit(bit, biपंचांगap);
			ida_मुक्त(&ida, bit);
		पूर्ण अन्यथा अणु
			__set_bit(bit, biपंचांगap);
			IDA_BUG_ON(&ida, ida_alloc_min(&ida, bit, GFP_KERNEL)
					!= bit);
		पूर्ण
	पूर्ण
	ida_destroy(&ida);
	अगर (समय(शून्य) < s + 10)
		जाओ repeat;
पूर्ण

व्योम ida_simple_get_हटाओ_test(व्योम)
अणु
	DEFINE_IDA(ida);
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < 10000; i++) अणु
		निश्चित(ida_simple_get(&ida, 0, 20000, GFP_KERNEL) == i);
	पूर्ण
	निश्चित(ida_simple_get(&ida, 5, 30, GFP_KERNEL) < 0);

	क्रम (i = 0; i < 10000; i++) अणु
		ida_simple_हटाओ(&ida, i);
	पूर्ण
	निश्चित(ida_is_empty(&ida));

	ida_destroy(&ida);
पूर्ण

व्योम user_ida_checks(व्योम)
अणु
	radix_tree_cpu_dead(1);

	ida_check_nomem();
	ida_check_conv_user();
	ida_check_अक्रमom();
	ida_simple_get_हटाओ_test();

	radix_tree_cpu_dead(1);
पूर्ण

अटल व्योम *ida_अक्रमom_fn(व्योम *arg)
अणु
	rcu_रेजिस्टर_thपढ़ो();
	ida_check_अक्रमom();
	rcu_unरेजिस्टर_thपढ़ो();
	वापस शून्य;
पूर्ण

अटल व्योम *ida_leak_fn(व्योम *arg)
अणु
	काष्ठा ida *ida = arg;
	समय_प्रकार s = समय(शून्य);
	पूर्णांक i, ret;

	rcu_रेजिस्टर_thपढ़ो();

	करो क्रम (i = 0; i < 1000; i++) अणु
		ret = ida_alloc_range(ida, 128, 128, GFP_KERNEL);
		अगर (ret >= 0)
			ida_मुक्त(ida, 128);
	पूर्ण जबतक (समय(शून्य) < s + 2);

	rcu_unरेजिस्टर_thपढ़ो();
	वापस शून्य;
पूर्ण

व्योम ida_thपढ़ो_tests(व्योम)
अणु
	DEFINE_IDA(ida);
	pthपढ़ो_t thपढ़ोs[20];
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(thपढ़ोs); i++)
		अगर (pthपढ़ो_create(&thपढ़ोs[i], शून्य, ida_अक्रमom_fn, शून्य)) अणु
			लिखो_त्रुटि("creating ida thread");
			निकास(1);
		पूर्ण

	जबतक (i--)
		pthपढ़ो_join(thपढ़ोs[i], शून्य);

	क्रम (i = 0; i < ARRAY_SIZE(thपढ़ोs); i++)
		अगर (pthपढ़ो_create(&thपढ़ोs[i], शून्य, ida_leak_fn, &ida)) अणु
			लिखो_त्रुटि("creating ida thread");
			निकास(1);
		पूर्ण

	जबतक (i--)
		pthपढ़ो_join(thपढ़ोs[i], शून्य);
	निश्चित(ida_is_empty(&ida));
पूर्ण

व्योम ida_tests(व्योम)
अणु
	user_ida_checks();
	ida_checks();
	ida_निकास();
	ida_thपढ़ो_tests();
पूर्ण

पूर्णांक __weak मुख्य(व्योम)
अणु
	rcu_रेजिस्टर_thपढ़ो();
	radix_tree_init();
	idr_checks();
	ida_tests();
	radix_tree_cpu_dead(1);
	rcu_barrier();
	अगर (nr_allocated)
		म_लिखो("nr_allocated = %d\n", nr_allocated);
	rcu_unरेजिस्टर_thपढ़ो();
	वापस 0;
पूर्ण
