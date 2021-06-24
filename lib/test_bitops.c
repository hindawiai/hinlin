<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Intel Corporation
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>

/* a tiny module only meant to test
 *
 *   set/clear_bit
 *   get_count_order/दीर्घ
 */

/* use an क्रमागत because thats the most common BITMAP usage */
क्रमागत bitops_fun अणु
	BITOPS_4 = 4,
	BITOPS_7 = 7,
	BITOPS_11 = 11,
	BITOPS_31 = 31,
	BITOPS_88 = 88,
	BITOPS_LAST = 255,
	BITOPS_LENGTH = 256
पूर्ण;

अटल DECLARE_BITMAP(g_biपंचांगap, BITOPS_LENGTH);

अटल अचिन्हित पूर्णांक order_comb[][2] = अणु
	अणु0x00000003,  2पूर्ण,
	अणु0x00000004,  2पूर्ण,
	अणु0x00001fff, 13पूर्ण,
	अणु0x00002000, 13पूर्ण,
	अणु0x50000000, 31पूर्ण,
	अणु0x80000000, 31पूर्ण,
	अणु0x80003000, 32पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_64BIT
अटल अचिन्हित दीर्घ order_comb_दीर्घ[][2] = अणु
	अणु0x0000000300000000, 34पूर्ण,
	अणु0x0000000400000000, 34पूर्ण,
	अणु0x00001fff00000000, 45पूर्ण,
	अणु0x0000200000000000, 45पूर्ण,
	अणु0x5000000000000000, 63पूर्ण,
	अणु0x8000000000000000, 63पूर्ण,
	अणु0x8000300000000000, 64पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init test_bitops_startup(व्योम)
अणु
	पूर्णांक i, bit_set;

	pr_info("Starting bitops test\n");
	set_bit(BITOPS_4, g_biपंचांगap);
	set_bit(BITOPS_7, g_biपंचांगap);
	set_bit(BITOPS_11, g_biपंचांगap);
	set_bit(BITOPS_31, g_biपंचांगap);
	set_bit(BITOPS_88, g_biपंचांगap);

	क्रम (i = 0; i < ARRAY_SIZE(order_comb); i++) अणु
		अगर (order_comb[i][1] != get_count_order(order_comb[i][0]))
			pr_warn("get_count_order wrong for %x\n",
				       order_comb[i][0]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(order_comb); i++) अणु
		अगर (order_comb[i][1] != get_count_order_दीर्घ(order_comb[i][0]))
			pr_warn("get_count_order_long wrong for %x\n",
				       order_comb[i][0]);
	पूर्ण

#अगर_घोषित CONFIG_64BIT
	क्रम (i = 0; i < ARRAY_SIZE(order_comb_दीर्घ); i++) अणु
		अगर (order_comb_दीर्घ[i][1] !=
			       get_count_order_दीर्घ(order_comb_दीर्घ[i][0]))
			pr_warn("get_count_order_long wrong for %lx\n",
				       order_comb_दीर्घ[i][0]);
	पूर्ण
#पूर्ण_अगर

	barrier();

	clear_bit(BITOPS_4, g_biपंचांगap);
	clear_bit(BITOPS_7, g_biपंचांगap);
	clear_bit(BITOPS_11, g_biपंचांगap);
	clear_bit(BITOPS_31, g_biपंचांगap);
	clear_bit(BITOPS_88, g_biपंचांगap);

	bit_set = find_first_bit(g_biपंचांगap, BITOPS_LAST);
	अगर (bit_set != BITOPS_LAST)
		pr_err("ERROR: FOUND SET BIT %d\n", bit_set);

	pr_info("Completed bitops test\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास test_bitops_unstartup(व्योम)
अणु
पूर्ण

module_init(test_bitops_startup);
module_निकास(test_bitops_unstartup);

MODULE_AUTHOR("Jesse Brandeburg <jesse.brandeburg@intel.com>, Wei Yang <richard.weiyang@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Bit testing module");
