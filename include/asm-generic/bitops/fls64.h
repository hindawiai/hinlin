<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_FLS64_H_
#घोषणा _ASM_GENERIC_BITOPS_FLS64_H_

#समावेश <यंत्र/types.h>

/**
 * fls64 - find last set bit in a 64-bit word
 * @x: the word to search
 *
 * This is defined in a similar way as the libc and compiler builtin
 * ffsll, but वापसs the position of the most signअगरicant set bit.
 *
 * fls64(value) वापसs 0 अगर value is 0 or the position of the last
 * set bit अगर value is nonzero. The last (most signअगरicant) bit is
 * at position 64.
 */
#अगर BITS_PER_LONG == 32
अटल __always_अंतरभूत पूर्णांक fls64(__u64 x)
अणु
	__u32 h = x >> 32;
	अगर (h)
		वापस fls(h) + 32;
	वापस fls(x);
पूर्ण
#या_अगर BITS_PER_LONG == 64
अटल __always_अंतरभूत पूर्णांक fls64(__u64 x)
अणु
	अगर (x == 0)
		वापस 0;
	वापस __fls(x) + 1;
पूर्ण
#अन्यथा
#त्रुटि BITS_PER_LONG not 32 or 64
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_FLS64_H_ */
