<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_BITS_H
#घोषणा __LINUX_BITS_H

#समावेश <linux/स्थिर.h>
#समावेश <vdso/bits.h>
#समावेश <यंत्र/bitsperदीर्घ.h>

#घोषणा BIT_ULL(nr)		(ULL(1) << (nr))
#घोषणा BIT_MASK(nr)		(UL(1) << ((nr) % BITS_PER_LONG))
#घोषणा BIT_WORD(nr)		((nr) / BITS_PER_LONG)
#घोषणा BIT_ULL_MASK(nr)	(ULL(1) << ((nr) % BITS_PER_LONG_LONG))
#घोषणा BIT_ULL_WORD(nr)	((nr) / BITS_PER_LONG_LONG)
#घोषणा BITS_PER_BYTE		8

/*
 * Create a contiguous biपंचांगask starting at bit position @l and ending at
 * position @h. For example
 * GENMASK_ULL(39, 21) gives us the 64bit vector 0x000000ffffe00000.
 */
#अगर !defined(__ASSEMBLY__)
#समावेश <linux/build_bug.h>
#घोषणा GENMASK_INPUT_CHECK(h, l) \
	(BUILD_BUG_ON_ZERO(__builtin_choose_expr( \
		__is_स्थिरexpr((l) > (h)), (l) > (h), 0)))
#अन्यथा
/*
 * BUILD_BUG_ON_ZERO is not available in h files included from यंत्र files,
 * disable the input check अगर that is the हाल.
 */
#घोषणा GENMASK_INPUT_CHECK(h, l) 0
#पूर्ण_अगर

#घोषणा __GENMASK(h, l) \
	(((~UL(0)) - (UL(1) << (l)) + 1) & \
	 (~UL(0) >> (BITS_PER_LONG - 1 - (h))))
#घोषणा GENMASK(h, l) \
	(GENMASK_INPUT_CHECK(h, l) + __GENMASK(h, l))

#घोषणा __GENMASK_ULL(h, l) \
	(((~ULL(0)) - (ULL(1) << (l)) + 1) & \
	 (~ULL(0) >> (BITS_PER_LONG_LONG - 1 - (h))))
#घोषणा GENMASK_ULL(h, l) \
	(GENMASK_INPUT_CHECK(h, l) + __GENMASK_ULL(h, l))

#पूर्ण_अगर	/* __LINUX_BITS_H */
