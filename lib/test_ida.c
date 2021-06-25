<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * test_ida.c: Test the IDA API
 * Copyright (c) 2016-2018 Microsoft Corporation
 * Copyright (c) 2018 Oracle Corporation
 * Author: Matthew Wilcox <willy@infradead.org>
 */

#समावेश <linux/idr.h>
#समावेश <linux/module.h>

अटल अचिन्हित पूर्णांक tests_run;
अटल अचिन्हित पूर्णांक tests_passed;

#अगर_घोषित __KERNEL__
व्योम ida_dump(काष्ठा ida *ida) अणु पूर्ण
#पूर्ण_अगर
#घोषणा IDA_BUG_ON(ida, x) करो अणु						\
	tests_run++;							\
	अगर (x) अणु							\
		ida_dump(ida);						\
		dump_stack();						\
	पूर्ण अन्यथा अणु							\
		tests_passed++;						\
	पूर्ण								\
पूर्ण जबतक (0)

/*
 * Straightक्रमward checks that allocating and मुक्तing IDs work.
 */
अटल व्योम ida_check_alloc(काष्ठा ida *ida)
अणु
	पूर्णांक i, id;

	क्रम (i = 0; i < 10000; i++)
		IDA_BUG_ON(ida, ida_alloc(ida, GFP_KERNEL) != i);

	ida_मुक्त(ida, 20);
	ida_मुक्त(ida, 21);
	क्रम (i = 0; i < 3; i++) अणु
		id = ida_alloc(ida, GFP_KERNEL);
		IDA_BUG_ON(ida, id < 0);
		अगर (i == 2)
			IDA_BUG_ON(ida, id != 10000);
	पूर्ण

	क्रम (i = 0; i < 5000; i++)
		ida_मुक्त(ida, i);

	IDA_BUG_ON(ida, ida_alloc_min(ida, 5000, GFP_KERNEL) != 10001);
	ida_destroy(ida);

	IDA_BUG_ON(ida, !ida_is_empty(ida));
पूर्ण

/* Destroy an IDA with a single entry at @base */
अटल व्योम ida_check_destroy_1(काष्ठा ida *ida, अचिन्हित पूर्णांक base)
अणु
	IDA_BUG_ON(ida, ida_alloc_min(ida, base, GFP_KERNEL) != base);
	IDA_BUG_ON(ida, ida_is_empty(ida));
	ida_destroy(ida);
	IDA_BUG_ON(ida, !ida_is_empty(ida));
पूर्ण

/* Check that ida_destroy and ida_is_empty work */
अटल व्योम ida_check_destroy(काष्ठा ida *ida)
अणु
	/* Destroy an alपढ़ोy-empty IDA */
	IDA_BUG_ON(ida, !ida_is_empty(ida));
	ida_destroy(ida);
	IDA_BUG_ON(ida, !ida_is_empty(ida));

	ida_check_destroy_1(ida, 0);
	ida_check_destroy_1(ida, 1);
	ida_check_destroy_1(ida, 1023);
	ida_check_destroy_1(ida, 1024);
	ida_check_destroy_1(ida, 12345678);
पूर्ण

/*
 * Check what happens when we fill a leaf and then delete it.  This may
 * discover mishandling of IDR_FREE.
 */
अटल व्योम ida_check_leaf(काष्ठा ida *ida, अचिन्हित पूर्णांक base)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < IDA_BITMAP_BITS; i++) अणु
		IDA_BUG_ON(ida, ida_alloc_min(ida, base, GFP_KERNEL) !=
				base + i);
	पूर्ण

	ida_destroy(ida);
	IDA_BUG_ON(ida, !ida_is_empty(ida));

	IDA_BUG_ON(ida, ida_alloc(ida, GFP_KERNEL) != 0);
	IDA_BUG_ON(ida, ida_is_empty(ida));
	ida_मुक्त(ida, 0);
	IDA_BUG_ON(ida, !ida_is_empty(ida));
पूर्ण

/*
 * Check allocations up to and slightly above the maximum allowed (2^31-1) ID.
 * Allocating up to 2^31-1 should succeed, and then allocating the next one
 * should fail.
 */
अटल व्योम ida_check_max(काष्ठा ida *ida)
अणु
	अचिन्हित दीर्घ i, j;

	क्रम (j = 1; j < 65537; j *= 2) अणु
		अचिन्हित दीर्घ base = (1UL << 31) - j;
		क्रम (i = 0; i < j; i++) अणु
			IDA_BUG_ON(ida, ida_alloc_min(ida, base, GFP_KERNEL) !=
					base + i);
		पूर्ण
		IDA_BUG_ON(ida, ida_alloc_min(ida, base, GFP_KERNEL) !=
				-ENOSPC);
		ida_destroy(ida);
		IDA_BUG_ON(ida, !ida_is_empty(ida));
	पूर्ण
पूर्ण

/*
 * Check handling of conversions between exceptional entries and full biपंचांगaps.
 */
अटल व्योम ida_check_conv(काष्ठा ida *ida)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < IDA_BITMAP_BITS * 2; i += IDA_BITMAP_BITS) अणु
		IDA_BUG_ON(ida, ida_alloc_min(ida, i + 1, GFP_KERNEL) != i + 1);
		IDA_BUG_ON(ida, ida_alloc_min(ida, i + BITS_PER_LONG,
					GFP_KERNEL) != i + BITS_PER_LONG);
		ida_मुक्त(ida, i + 1);
		ida_मुक्त(ida, i + BITS_PER_LONG);
		IDA_BUG_ON(ida, !ida_is_empty(ida));
	पूर्ण

	क्रम (i = 0; i < IDA_BITMAP_BITS * 2; i++)
		IDA_BUG_ON(ida, ida_alloc(ida, GFP_KERNEL) != i);
	क्रम (i = IDA_BITMAP_BITS * 2; i > 0; i--)
		ida_मुक्त(ida, i - 1);
	IDA_BUG_ON(ida, !ida_is_empty(ida));

	क्रम (i = 0; i < IDA_BITMAP_BITS + BITS_PER_LONG - 4; i++)
		IDA_BUG_ON(ida, ida_alloc(ida, GFP_KERNEL) != i);
	क्रम (i = IDA_BITMAP_BITS + BITS_PER_LONG - 4; i > 0; i--)
		ida_मुक्त(ida, i - 1);
	IDA_BUG_ON(ida, !ida_is_empty(ida));
पूर्ण

अटल DEFINE_IDA(ida);

अटल पूर्णांक ida_checks(व्योम)
अणु
	IDA_BUG_ON(&ida, !ida_is_empty(&ida));
	ida_check_alloc(&ida);
	ida_check_destroy(&ida);
	ida_check_leaf(&ida, 0);
	ida_check_leaf(&ida, 1024);
	ida_check_leaf(&ida, 1024 * 64);
	ida_check_max(&ida);
	ida_check_conv(&ida);

	prपूर्णांकk("IDA: %u of %u tests passed\n", tests_passed, tests_run);
	वापस (tests_run != tests_passed) ? 0 : -EINVAL;
पूर्ण

अटल व्योम ida_निकास(व्योम)
अणु
पूर्ण

module_init(ida_checks);
module_निकास(ida_निकास);
MODULE_AUTHOR("Matthew Wilcox <willy@infradead.org>");
MODULE_LICENSE("GPL");
