<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARM_WORD_AT_A_TIME_H
#घोषणा __ASM_ARM_WORD_AT_A_TIME_H

#अगर_अघोषित __ARMEB__

/*
 * Little-endian word-at-a-समय zero byte handling.
 * Heavily based on the x86 algorithm.
 */
#समावेश <linux/kernel.h>

काष्ठा word_at_a_समय अणु
	स्थिर अचिन्हित दीर्घ one_bits, high_bits;
पूर्ण;

#घोषणा WORD_AT_A_TIME_CONSTANTS अणु REPEAT_BYTE(0x01), REPEAT_BYTE(0x80) पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ has_zero(अचिन्हित दीर्घ a, अचिन्हित दीर्घ *bits,
				     स्थिर काष्ठा word_at_a_समय *c)
अणु
	अचिन्हित दीर्घ mask = ((a - c->one_bits) & ~a) & c->high_bits;
	*bits = mask;
	वापस mask;
पूर्ण

#घोषणा prep_zero_mask(a, bits, c) (bits)

अटल अंतरभूत अचिन्हित दीर्घ create_zero_mask(अचिन्हित दीर्घ bits)
अणु
	bits = (bits - 1) & ~bits;
	वापस bits >> 7;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ find_zero(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ ret;

#अगर __LINUX_ARM_ARCH__ >= 5
	/* We have clz available. */
	ret = fls(mask) >> 3;
#अन्यथा
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	ret = (0x0ff0001 + mask) >> 23;
	/* Fix the 1 क्रम 00 हाल */
	ret &= mask;
#पूर्ण_अगर

	वापस ret;
पूर्ण

#घोषणा zero_bytemask(mask) (mask)

#अन्यथा	/* __ARMEB__ */
#समावेश <यंत्र-generic/word-at-a-समय.स>
#पूर्ण_अगर

#अगर_घोषित CONFIG_DCACHE_WORD_ACCESS

/*
 * Load an unaligned word from kernel space.
 *
 * In the (very unlikely) हाल of the word being a page-crosser
 * and the next page not being mapped, take the exception and
 * वापस zeroes in the non-existing part.
 */
अटल अंतरभूत अचिन्हित दीर्घ load_unaligned_zeropad(स्थिर व्योम *addr)
अणु
	अचिन्हित दीर्घ ret, offset;

	/* Load word from unaligned poपूर्णांकer addr */
	यंत्र(
	"1:	ldr	%0, [%2]\n"
	"2:\n"
	"	.pushsection .text.fixup,\"ax\"\n"
	"	.align 2\n"
	"3:	and	%1, %2, #0x3\n"
	"	bic	%2, %2, #0x3\n"
	"	ldr	%0, [%2]\n"
	"	lsl	%1, %1, #0x3\n"
#अगर_अघोषित __ARMEB__
	"	lsr	%0, %0, %1\n"
#अन्यथा
	"	lsl	%0, %0, %1\n"
#पूर्ण_अगर
	"	b	2b\n"
	"	.popsection\n"
	"	.pushsection __ex_table,\"a\"\n"
	"	.align	3\n"
	"	.long	1b, 3b\n"
	"	.popsection"
	: "=&r" (ret), "=&r" (offset)
	: "r" (addr), "Qo" (*(अचिन्हित दीर्घ *)addr));

	वापस ret;
पूर्ण

#पूर्ण_अगर	/* DCACHE_WORD_ACCESS */
#पूर्ण_अगर /* __ASM_ARM_WORD_AT_A_TIME_H */
