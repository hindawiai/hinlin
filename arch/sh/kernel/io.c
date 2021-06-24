<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/io.c - Machine independent I/O functions.
 *
 * Copyright (C) 2000 - 2009  Stuart Menefy
 * Copyright (C) 2005  Paul Mundt
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/पन.स>

/*
 * Copy data from IO memory space to "real" memory space.
 */
व्योम स_नकल_fromio(व्योम *to, स्थिर अस्थिर व्योम __iomem *from, अचिन्हित दीर्घ count)
अणु
	/*
	 * Would it be worthजबतक करोing byte and दीर्घ transfers first
	 * to try and get aligned?
	 */
#अगर_घोषित CONFIG_CPU_SH4
	अगर ((count >= 0x20) &&
	     (((u32)to & 0x1f) == 0) && (((u32)from & 0x3) == 0)) अणु
		पूर्णांक पंचांगp2, पंचांगp3, पंचांगp4, पंचांगp5, पंचांगp6;

		__यंत्र__ __अस्थिर__(
			"1:			\n\t"
			"mov.l	@%7+, r0	\n\t"
			"mov.l	@%7+, %2	\n\t"
			"movca.l r0, @%0	\n\t"
			"mov.l	@%7+, %3	\n\t"
			"mov.l	@%7+, %4	\n\t"
			"mov.l	@%7+, %5	\n\t"
			"mov.l	@%7+, %6	\n\t"
			"mov.l	@%7+, r7	\n\t"
			"mov.l	@%7+, r0	\n\t"
			"mov.l	%2, @(0x04,%0)	\n\t"
			"mov	#0x20, %2	\n\t"
			"mov.l	%3, @(0x08,%0)	\n\t"
			"sub	%2, %1		\n\t"
			"mov.l	%4, @(0x0c,%0)	\n\t"
			"cmp/hi	%1, %2		! T if 32 > count	\n\t"
			"mov.l	%5, @(0x10,%0)	\n\t"
			"mov.l	%6, @(0x14,%0)	\n\t"
			"mov.l	r7, @(0x18,%0)	\n\t"
			"mov.l	r0, @(0x1c,%0)	\n\t"
			"bf.s	1b		\n\t"
			" add	#0x20, %0	\n\t"
			: "=&r" (to), "=&r" (count),
			  "=&r" (पंचांगp2), "=&r" (पंचांगp3), "=&r" (पंचांगp4),
			  "=&r" (पंचांगp5), "=&r" (पंचांगp6), "=&r" (from)
			: "7"(from), "0" (to), "1" (count)
			: "r0", "r7", "t", "memory");
	पूर्ण
#पूर्ण_अगर

	अगर ((((u32)to | (u32)from) & 0x3) == 0) अणु
		क्रम (; count > 3; count -= 4) अणु
			*(u32 *)to = *(अस्थिर u32 *)from;
			to += 4;
			from += 4;
		पूर्ण
	पूर्ण

	क्रम (; count > 0; count--) अणु
		*(u8 *)to = *(अस्थिर u8 *)from;
		to++;
		from++;
	पूर्ण

	mb();
पूर्ण
EXPORT_SYMBOL(स_नकल_fromio);

/*
 * Copy data from "real" memory space to IO memory space.
 */
व्योम स_नकल_toio(अस्थिर व्योम __iomem *to, स्थिर व्योम *from, अचिन्हित दीर्घ count)
अणु
	अगर ((((u32)to | (u32)from) & 0x3) == 0) अणु
		क्रम ( ; count > 3; count -= 4) अणु
			*(अस्थिर u32 *)to = *(u32 *)from;
			to += 4;
			from += 4;
		पूर्ण
	पूर्ण

	क्रम (; count > 0; count--) अणु
		*(अस्थिर u8 *)to = *(u8 *)from;
		to++;
		from++;
	पूर्ण

	mb();
पूर्ण
EXPORT_SYMBOL(स_नकल_toio);

/*
 * "memset" on IO memory space.
 * This needs to be optimized.
 */
व्योम स_रखो_io(अस्थिर व्योम __iomem *dst, पूर्णांक c, अचिन्हित दीर्घ count)
अणु
        जबतक (count) अणु
                count--;
                ग_लिखोb(c, dst);
                dst++;
        पूर्ण
पूर्ण
EXPORT_SYMBOL(स_रखो_io);
