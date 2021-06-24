<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_WORD_AT_A_TIME_H
#घोषणा _ASM_WORD_AT_A_TIME_H

#समावेश <linux/kernel.h>

/*
 * This is largely generic क्रम little-endian machines, but the
 * optimal byte mask counting is probably going to be something
 * that is architecture-specअगरic. If you have a reliably fast
 * bit count inकाष्ठाion, that might be better than the multiply
 * and shअगरt, क्रम example.
 */
काष्ठा word_at_a_समय अणु
	स्थिर अचिन्हित दीर्घ one_bits, high_bits;
पूर्ण;

#घोषणा WORD_AT_A_TIME_CONSTANTS अणु REPEAT_BYTE(0x01), REPEAT_BYTE(0x80) पूर्ण

#अगर_घोषित CONFIG_64BIT

/*
 * Jan Achrenius on G+: microoptimized version of
 * the simpler "(mask & ONEBYTES) * ONEBYTES >> 56"
 * that works क्रम the bytemasks without having to
 * mask them first.
 */
अटल अंतरभूत दीर्घ count_masked_bytes(अचिन्हित दीर्घ mask)
अणु
	वापस mask*0x0001020304050608ul >> 56;
पूर्ण

#अन्यथा	/* 32-bit हाल */

/* Carl Chatfield / Jan Achrenius G+ version क्रम 32-bit */
अटल अंतरभूत दीर्घ count_masked_bytes(दीर्घ mask)
अणु
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	दीर्घ a = (0x0ff0001+mask) >> 23;
	/* Fix the 1 क्रम 00 हाल */
	वापस a & mask;
पूर्ण

#पूर्ण_अगर

/* Return nonzero अगर it has a zero */
अटल अंतरभूत अचिन्हित दीर्घ has_zero(अचिन्हित दीर्घ a, अचिन्हित दीर्घ *bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	अचिन्हित दीर्घ mask = ((a - c->one_bits) & ~a) & c->high_bits;
	*bits = mask;
	वापस mask;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prep_zero_mask(अचिन्हित दीर्घ a, अचिन्हित दीर्घ bits, स्थिर काष्ठा word_at_a_समय *c)
अणु
	वापस bits;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ create_zero_mask(अचिन्हित दीर्घ bits)
अणु
	bits = (bits - 1) & ~bits;
	वापस bits >> 7;
पूर्ण

/* The mask we created is directly usable as a bytemask */
#घोषणा zero_bytemask(mask) (mask)

अटल अंतरभूत अचिन्हित दीर्घ find_zero(अचिन्हित दीर्घ mask)
अणु
	वापस count_masked_bytes(mask);
पूर्ण

/*
 * Load an unaligned word from kernel space.
 *
 * In the (very unlikely) हाल of the word being a page-crosser
 * and the next page not being mapped, take the exception and
 * वापस zeroes in the non-existing part.
 */
अटल अंतरभूत अचिन्हित दीर्घ load_unaligned_zeropad(स्थिर व्योम *addr)
अणु
	अचिन्हित दीर्घ ret, dummy;

	यंत्र(
		"1:\tmov %2,%0\n"
		"2:\n"
		".section .fixup,\"ax\"\n"
		"3:\t"
		"lea %2,%1\n\t"
		"and %3,%1\n\t"
		"mov (%1),%0\n\t"
		"leal %2,%%ecx\n\t"
		"andl %4,%%ecx\n\t"
		"shll $3,%%ecx\n\t"
		"shr %%cl,%0\n\t"
		"jmp 2b\n"
		".previous\n"
		_ASM_EXTABLE(1b, 3b)
		:"=&r" (ret),"=&c" (dummy)
		:"m" (*(अचिन्हित दीर्घ *)addr),
		 "i" (-माप(अचिन्हित दीर्घ)),
		 "i" (माप(अचिन्हित दीर्घ)-1));
	वापस ret;
पूर्ण

#पूर्ण_अगर /* _ASM_WORD_AT_A_TIME_H */
