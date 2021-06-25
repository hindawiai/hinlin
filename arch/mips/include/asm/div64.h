<शैली गुरु>
/*
 * Copyright (C) 2000, 2004, 2021  Maciej W. Rozycki
 * Copyright (C) 2003, 07 Ralf Baechle (ralf@linux-mips.org)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_DIV64_H
#घोषणा __ASM_DIV64_H

#समावेश <यंत्र/bitsperदीर्घ.h>

#अगर BITS_PER_LONG == 32

/*
 * No traps on overflows क्रम any of these...
 */

#घोषणा करो_भाग64_32(res, high, low, base) (अणु				\
	अचिन्हित दीर्घ __cf, __पंचांगp, __पंचांगp2, __i;				\
	अचिन्हित दीर्घ __quot32, __mod32;				\
									\
	__यंत्र__(							\
	"	.set	push					\n"	\
	"	.set	noat					\n"	\
	"	.set	noreorder				\n"	\
	"	move	%2, $0					\n"	\
	"	move	%3, $0					\n"	\
	"	b	1f					\n"	\
	"	 li	%4, 0x21				\n"	\
	"0:							\n"	\
	"	sll	$1, %0, 0x1				\n"	\
	"	srl	%3, %0, 0x1f				\n"	\
	"	or	%0, $1, %5				\n"	\
	"	sll	%1, %1, 0x1				\n"	\
	"	sll	%2, %2, 0x1				\n"	\
	"1:							\n"	\
	"	bnez	%3, 2f					\n"	\
	"	 sltu	%5, %0, %z6				\n"	\
	"	bnez	%5, 3f					\n"	\
	"2:							\n"	\
	"	 addiu	%4, %4, -1				\n"	\
	"	subu	%0, %0, %z6				\n"	\
	"	addiu	%2, %2, 1				\n"	\
	"3:							\n"	\
	"	bnez	%4, 0b					\n"	\
	"	 srl	%5, %1, 0x1f				\n"	\
	"	.set	pop"						\
	: "=&r" (__mod32), "=&r" (__पंचांगp),				\
	  "=&r" (__quot32), "=&r" (__cf),				\
	  "=&r" (__i), "=&r" (__पंचांगp2)					\
	: "Jr" (base), "0" (high), "1" (low));				\
									\
	(res) = __quot32;						\
	__mod32;							\
पूर्ण)

#घोषणा __भाग64_32(n, base) (अणु						\
	अचिन्हित दीर्घ __upper, __low, __high, __radix;			\
	अचिन्हित दीर्घ दीर्घ __quot;					\
	अचिन्हित दीर्घ दीर्घ __भाग;					\
	अचिन्हित दीर्घ __mod;						\
									\
	__भाग = (*n);							\
	__radix = (base);						\
									\
	__high = __भाग >> 32;						\
	__low = __भाग;							\
									\
	अगर (__high < __radix) अणु						\
		__upper = __high;					\
		__high = 0;						\
	पूर्ण अन्यथा अणु							\
		__upper = __high % __radix;				\
		__high /= __radix;					\
	पूर्ण								\
									\
	__mod = करो_भाग64_32(__low, __upper, __low, __radix);		\
									\
	__quot = __high;						\
	__quot = __quot << 32 | __low;					\
	(*n) = __quot;							\
	__mod;								\
पूर्ण)

#पूर्ण_अगर /* BITS_PER_LONG == 32 */

#समावेश <यंत्र-generic/भाग64.h>

#पूर्ण_अगर /* __ASM_DIV64_H */
