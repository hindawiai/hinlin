<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/lib/io.c - SH32 optimized I/O routines
 *
 * Copyright (C) 2000  Stuart Menefy
 * Copyright (C) 2005  Paul Mundt
 *
 * Provide real functions which expand to whatever the header file defined.
 * Also definitions of machine independent IO functions.
 */
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

व्योम __raw_पढ़ोsl(स्थिर व्योम __iomem *addr, व्योम *datap, पूर्णांक len)
अणु
	u32 *data;

	क्रम (data = datap; (len != 0) && (((u32)data & 0x1f) != 0); len--)
		*data++ = __raw_पढ़ोl(addr);

	अगर (likely(len >= (0x20 >> 2))) अणु
		पूर्णांक पंचांगp2, पंचांगp3, पंचांगp4, पंचांगp5, पंचांगp6;

		__यंत्र__ __अस्थिर__(
			"1:			\n\t"
			"mov.l	@%7, r0		\n\t"
			"mov.l	@%7, %2		\n\t"
#अगर_घोषित CONFIG_CPU_SH4
			"movca.l r0, @%0	\n\t"
#अन्यथा
			"mov.l	r0, @%0		\n\t"
#पूर्ण_अगर
			"mov.l	@%7, %3		\n\t"
			"mov.l	@%7, %4		\n\t"
			"mov.l	@%7, %5		\n\t"
			"mov.l	@%7, %6		\n\t"
			"mov.l	@%7, r7		\n\t"
			"mov.l	@%7, r0		\n\t"
			"mov.l	%2, @(0x04,%0)	\n\t"
			"mov	#0x20>>2, %2	\n\t"
			"mov.l	%3, @(0x08,%0)	\n\t"
			"sub	%2, %1		\n\t"
			"mov.l	%4, @(0x0c,%0)	\n\t"
			"cmp/hi	%1, %2		! T if 32 > len	\n\t"
			"mov.l	%5, @(0x10,%0)	\n\t"
			"mov.l	%6, @(0x14,%0)	\n\t"
			"mov.l	r7, @(0x18,%0)	\n\t"
			"mov.l	r0, @(0x1c,%0)	\n\t"
			"bf.s	1b		\n\t"
			" add	#0x20, %0	\n\t"
			: "=&r" (data), "=&r" (len),
			  "=&r" (पंचांगp2), "=&r" (पंचांगp3), "=&r" (पंचांगp4),
			  "=&r" (पंचांगp5), "=&r" (पंचांगp6)
			: "r"(addr), "0" (data), "1" (len)
			: "r0", "r7", "t", "memory");
	पूर्ण

	क्रम (; len != 0; len--)
		*data++ = __raw_पढ़ोl(addr);
पूर्ण
EXPORT_SYMBOL(__raw_पढ़ोsl);

व्योम __raw_ग_लिखोsl(व्योम __iomem *addr, स्थिर व्योम *data, पूर्णांक len)
अणु
	अगर (likely(len != 0)) अणु
		पूर्णांक पंचांगp1;

		__यंत्र__ __अस्थिर__ (
			"1:				\n\t"
			"mov.l	@%0+, %1	\n\t"
			"dt		%3		\n\t"
			"bf.s		1b		\n\t"
			" mov.l	%1, @%4		\n\t"
			: "=&r" (data), "=&r" (पंचांगp1)
			: "0" (data), "r" (len), "r"(addr)
			: "t", "memory");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__raw_ग_लिखोsl);
