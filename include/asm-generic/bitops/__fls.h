<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS___FLS_H_
#घोषणा _ASM_GENERIC_BITOPS___FLS_H_

#समावेश <यंत्र/types.h>

/**
 * __fls - find last (most-signअगरicant) set bit in a दीर्घ word
 * @word: the word to search
 *
 * Undefined अगर no set bit exists, so code should check against 0 first.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __fls(अचिन्हित दीर्घ word)
अणु
	पूर्णांक num = BITS_PER_LONG - 1;

#अगर BITS_PER_LONG == 64
	अगर (!(word & (~0ul << 32))) अणु
		num -= 32;
		word <<= 32;
	पूर्ण
#पूर्ण_अगर
	अगर (!(word & (~0ul << (BITS_PER_LONG-16)))) अणु
		num -= 16;
		word <<= 16;
	पूर्ण
	अगर (!(word & (~0ul << (BITS_PER_LONG-8)))) अणु
		num -= 8;
		word <<= 8;
	पूर्ण
	अगर (!(word & (~0ul << (BITS_PER_LONG-4)))) अणु
		num -= 4;
		word <<= 4;
	पूर्ण
	अगर (!(word & (~0ul << (BITS_PER_LONG-2)))) अणु
		num -= 2;
		word <<= 2;
	पूर्ण
	अगर (!(word & (~0ul << (BITS_PER_LONG-1))))
		num -= 1;
	वापस num;
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS___FLS_H_ */
