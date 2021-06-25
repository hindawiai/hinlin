<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 ARM Ltd.
 */
#अगर_अघोषित __ASM_WORD_AT_A_TIME_H
#घोषणा __ASM_WORD_AT_A_TIME_H

#समावेश <linux/uaccess.h>

#अगर_अघोषित __AARCH64EB__

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
	वापस fls64(mask) >> 3;
पूर्ण

#घोषणा zero_bytemask(mask) (mask)

#अन्यथा	/* __AARCH64EB__ */
#समावेश <यंत्र-generic/word-at-a-समय.स>
#पूर्ण_अगर

/*
 * Load an unaligned word from kernel space.
 *
 * In the (very unlikely) हाल of the word being a page-crosser
 * and the next page not being mapped, take the exception and
 * वापस zeroes in the non-existing part.
 */
अटल अंतरभूत अचिन्हित दीर्घ load_unaligned_zeropad(स्थिर व्योम *addr)
अणु
	अचिन्हित दीर्घ ret, पंचांगp;

	__uaccess_enable_tco_async();

	/* Load word from unaligned poपूर्णांकer addr */
	यंत्र(
	"1:	ldr	%0, %3\n"
	"2:\n"
	"	.pushsection .fixup,\"ax\"\n"
	"	.align 2\n"
	"3:	bic	%1, %2, #0x7\n"
	"	ldr	%0, [%1]\n"
	"	and	%1, %2, #0x7\n"
	"	lsl	%1, %1, #0x3\n"
#अगर_अघोषित __AARCH64EB__
	"	lsr	%0, %0, %1\n"
#अन्यथा
	"	lsl	%0, %0, %1\n"
#पूर्ण_अगर
	"	b	2b\n"
	"	.popsection\n"
	_ASM_EXTABLE(1b, 3b)
	: "=&r" (ret), "=&r" (पंचांगp)
	: "r" (addr), "Q" (*(अचिन्हित दीर्घ *)addr));

	__uaccess_disable_tco_async();

	वापस ret;
पूर्ण

#पूर्ण_अगर /* __ASM_WORD_AT_A_TIME_H */
