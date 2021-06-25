<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Test क्रम find_*_bit functions.
 *
 * Copyright (c) 2017 Cavium.
 */

/*
 * find_bit functions are widely used in kernel, so the successful boot
 * is good enough test क्रम correctness.
 *
 * This test is focused on perक्रमmance of traversing biपंचांगaps. Two typical
 * scenarios are reproduced:
 * - अक्रमomly filled biपंचांगap with approximately equal number of set and
 *   cleared bits;
 * - sparse biपंचांगap with few set bits at अक्रमom positions.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>

#घोषणा BITMAP_LEN	(4096UL * 8 * 10)
#घोषणा SPARSE		500

अटल DECLARE_BITMAP(biपंचांगap, BITMAP_LEN) __initdata;
अटल DECLARE_BITMAP(biपंचांगap2, BITMAP_LEN) __initdata;

/*
 * This is Schlemiel the Paपूर्णांकer's algorithm. It should be called after
 * all other tests क्रम the same biपंचांगap because it sets all bits of biपंचांगap to 1.
 */
अटल पूर्णांक __init test_find_first_bit(व्योम *biपंचांगap, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ i, cnt;
	kसमय_प्रकार समय;

	समय = kसमय_get();
	क्रम (cnt = i = 0; i < len; cnt++) अणु
		i = find_first_bit(biपंचांगap, len);
		__clear_bit(i, biपंचांगap);
	पूर्ण
	समय = kसमय_get() - समय;
	pr_err("find_first_bit:     %18llu ns, %6ld iterations\n", समय, cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_find_next_bit(स्थिर व्योम *biपंचांगap, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ i, cnt;
	kसमय_प्रकार समय;

	समय = kसमय_get();
	क्रम (cnt = i = 0; i < BITMAP_LEN; cnt++)
		i = find_next_bit(biपंचांगap, BITMAP_LEN, i) + 1;
	समय = kसमय_get() - समय;
	pr_err("find_next_bit:      %18llu ns, %6ld iterations\n", समय, cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_find_next_zero_bit(स्थिर व्योम *biपंचांगap, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ i, cnt;
	kसमय_प्रकार समय;

	समय = kसमय_get();
	क्रम (cnt = i = 0; i < BITMAP_LEN; cnt++)
		i = find_next_zero_bit(biपंचांगap, len, i) + 1;
	समय = kसमय_get() - समय;
	pr_err("find_next_zero_bit: %18llu ns, %6ld iterations\n", समय, cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_find_last_bit(स्थिर व्योम *biपंचांगap, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ l, cnt = 0;
	kसमय_प्रकार समय;

	समय = kसमय_get();
	करो अणु
		cnt++;
		l = find_last_bit(biपंचांगap, len);
		अगर (l >= len)
			अवरोध;
		len = l;
	पूर्ण जबतक (len);
	समय = kसमय_get() - समय;
	pr_err("find_last_bit:      %18llu ns, %6ld iterations\n", समय, cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक __init test_find_next_and_bit(स्थिर व्योम *biपंचांगap,
		स्थिर व्योम *biपंचांगap2, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ i, cnt;
	kसमय_प्रकार समय;

	समय = kसमय_get();
	क्रम (cnt = i = 0; i < BITMAP_LEN; cnt++)
		i = find_next_and_bit(biपंचांगap, biपंचांगap2, BITMAP_LEN, i + 1);
	समय = kसमय_get() - समय;
	pr_err("find_next_and_bit:  %18llu ns, %6ld iterations\n", समय, cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक __init find_bit_test(व्योम)
अणु
	अचिन्हित दीर्घ nbits = BITMAP_LEN / SPARSE;

	pr_err("\nStart testing find_bit() with random-filled bitmap\n");

	get_अक्रमom_bytes(biपंचांगap, माप(biपंचांगap));
	get_अक्रमom_bytes(biपंचांगap2, माप(biपंचांगap2));

	test_find_next_bit(biपंचांगap, BITMAP_LEN);
	test_find_next_zero_bit(biपंचांगap, BITMAP_LEN);
	test_find_last_bit(biपंचांगap, BITMAP_LEN);

	/*
	 * test_find_first_bit() may take some समय, so
	 * traverse only part of biपंचांगap to aव्योम soft lockup.
	 */
	test_find_first_bit(biपंचांगap, BITMAP_LEN / 10);
	test_find_next_and_bit(biपंचांगap, biपंचांगap2, BITMAP_LEN);

	pr_err("\nStart testing find_bit() with sparse bitmap\n");

	biपंचांगap_zero(biपंचांगap, BITMAP_LEN);
	biपंचांगap_zero(biपंचांगap2, BITMAP_LEN);

	जबतक (nbits--) अणु
		__set_bit(pअक्रमom_u32() % BITMAP_LEN, biपंचांगap);
		__set_bit(pअक्रमom_u32() % BITMAP_LEN, biपंचांगap2);
	पूर्ण

	test_find_next_bit(biपंचांगap, BITMAP_LEN);
	test_find_next_zero_bit(biपंचांगap, BITMAP_LEN);
	test_find_last_bit(biपंचांगap, BITMAP_LEN);
	test_find_first_bit(biपंचांगap, BITMAP_LEN);
	test_find_next_and_bit(biपंचांगap, biपंचांगap2, BITMAP_LEN);

	/*
	 * Everything is OK. Return error just to let user run benchmark
	 * again without annoying rmmod.
	 */
	वापस -EINVAL;
पूर्ण
module_init(find_bit_test);

MODULE_LICENSE("GPL");
