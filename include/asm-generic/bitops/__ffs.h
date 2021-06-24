<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS___FFS_H_
#घोषणा _ASM_GENERIC_BITOPS___FFS_H_

#समावेश <यंत्र/types.h>

/**
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined अगर no bit exists, so code should check against 0 first.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ __ffs(अचिन्हित दीर्घ word)
अणु
	पूर्णांक num = 0;

#अगर BITS_PER_LONG == 64
	अगर ((word & 0xffffffff) == 0) अणु
		num += 32;
		word >>= 32;
	पूर्ण
#पूर्ण_अगर
	अगर ((word & 0xffff) == 0) अणु
		num += 16;
		word >>= 16;
	पूर्ण
	अगर ((word & 0xff) == 0) अणु
		num += 8;
		word >>= 8;
	पूर्ण
	अगर ((word & 0xf) == 0) अणु
		num += 4;
		word >>= 4;
	पूर्ण
	अगर ((word & 0x3) == 0) अणु
		num += 2;
		word >>= 2;
	पूर्ण
	अगर ((word & 0x1) == 0)
		num += 1;
	वापस num;
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS___FFS_H_ */
