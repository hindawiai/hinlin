<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * User space memory access functions
 *
 * Copyright (C) 1999, 2002  Niibe Yutaka
 * Copyright (C) 2003 - 2008  Paul Mundt
 *
 *  Based on:
 *     MIPS implementation version 1.15 by
 *              Copyright (C) 1996, 1997, 1998 by Ralf Baechle
 *     and i386 version.
 */
#अगर_अघोषित __ASM_SH_UACCESS_32_H
#घोषणा __ASM_SH_UACCESS_32_H

#घोषणा __get_user_size(x,ptr,size,retval)			\
करो अणु								\
	retval = 0;						\
	चयन (size) अणु						\
	हाल 1:							\
		__get_user_यंत्र(x, ptr, retval, "b");		\
		अवरोध;						\
	हाल 2:							\
		__get_user_यंत्र(x, ptr, retval, "w");		\
		अवरोध;						\
	हाल 4:							\
		__get_user_यंत्र(x, ptr, retval, "l");		\
		अवरोध;						\
	हाल 8:							\
		__get_user_u64(x, ptr, retval);			\
		अवरोध;						\
	शेष:						\
		__get_user_unknown();				\
		अवरोध;						\
	पूर्ण							\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_MMU
#घोषणा __get_user_यंत्र(x, addr, err, insn) \
(अणु \
__यंत्र__ __अस्थिर__( \
	"1:\n\t" \
	"mov." insn "	%2, %1\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov	#0, %1\n\t" \
	"mov.l	4f, %0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3, %0\n\t" \
	".balign	4\n" \
	"4:	.long	2b\n\t" \
	".previous\n" \
	".section	__ex_table,\"a\"\n\t" \
	".long	1b, 3b\n\t" \
	".previous" \
	:"=&r" (err), "=&r" (x) \
	:"m" (__m(addr)), "i" (-EFAULT), "0" (err)); पूर्ण)
#अन्यथा
#घोषणा __get_user_यंत्र(x, addr, err, insn)		\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
		"mov." insn "	%1, %0\n\t"		\
		: "=&r" (x)				\
		: "m" (__m(addr))			\
	);						\
पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_MMU */

बाह्य व्योम __get_user_unknown(व्योम);

#अगर defined(CONFIG_CPU_LITTLE_ENDIAN)
#घोषणा __get_user_u64(x, addr, err) \
(अणु \
__यंत्र__ __अस्थिर__( \
	"1:\n\t" \
	"mov.l	%2,%R1\n\t" \
	"mov.l	%T2,%S1\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov  #0,%R1\n\t"   \
	"mov  #0,%S1\n\t"   \
	"mov.l	4f, %0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3, %0\n\t" \
	".balign	4\n" \
	"4:	.long	2b\n\t" \
	".previous\n" \
	".section	__ex_table,\"a\"\n\t" \
	".long	1b, 3b\n\t" \
	".long	1b + 2, 3b\n\t" \
	".previous" \
	:"=&r" (err), "=&r" (x) \
	:"m" (__m(addr)), "i" (-EFAULT), "0" (err)); पूर्ण)
#अन्यथा
#घोषणा __get_user_u64(x, addr, err) \
(अणु \
__यंत्र__ __अस्थिर__( \
	"1:\n\t" \
	"mov.l	%2,%S1\n\t" \
	"mov.l	%T2,%R1\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov  #0,%S1\n\t"   \
	"mov  #0,%R1\n\t"   \
	"mov.l	4f, %0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3, %0\n\t" \
	".balign	4\n" \
	"4:	.long	2b\n\t" \
	".previous\n" \
	".section	__ex_table,\"a\"\n\t" \
	".long	1b, 3b\n\t" \
	".long	1b + 2, 3b\n\t" \
	".previous" \
	:"=&r" (err), "=&r" (x) \
	:"m" (__m(addr)), "i" (-EFAULT), "0" (err)); पूर्ण)
#पूर्ण_अगर

#घोषणा __put_user_size(x,ptr,size,retval)		\
करो अणु							\
	retval = 0;					\
	चयन (size) अणु					\
	हाल 1:						\
		__put_user_यंत्र(x, ptr, retval, "b");	\
		अवरोध;					\
	हाल 2:						\
		__put_user_यंत्र(x, ptr, retval, "w");	\
		अवरोध;					\
	हाल 4:						\
		__put_user_यंत्र(x, ptr, retval, "l");	\
		अवरोध;					\
	हाल 8:						\
		__put_user_u64(x, ptr, retval);		\
		अवरोध;					\
	शेष:					\
		__put_user_unknown();			\
	पूर्ण						\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_MMU
#घोषणा __put_user_यंत्र(x, addr, err, insn)			\
करो अणु								\
	__यंत्र__ __अस्थिर__ (					\
		"1:\n\t"					\
		"mov." insn "	%1, %2\n\t"			\
		"2:\n"						\
		".section	.fixup,\"ax\"\n"		\
		"3:\n\t"					\
		"mov.l	4f, %0\n\t"				\
		"jmp	@%0\n\t"				\
		" mov	%3, %0\n\t"				\
		".balign	4\n"				\
		"4:	.long	2b\n\t"				\
		".previous\n"					\
		".section	__ex_table,\"a\"\n\t"		\
		".long	1b, 3b\n\t"				\
		".previous"					\
		: "=&r" (err)					\
		: "r" (x), "m" (__m(addr)), "i" (-EFAULT),	\
		  "0" (err)					\
		: "memory"					\
	);							\
पूर्ण जबतक (0)
#अन्यथा
#घोषणा __put_user_यंत्र(x, addr, err, insn)		\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
		"mov." insn "	%0, %1\n\t"		\
		: /* no outमाला_दो */			\
		: "r" (x), "m" (__m(addr))		\
		: "memory"				\
	);						\
पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_MMU */

#अगर defined(CONFIG_CPU_LITTLE_ENDIAN)
#घोषणा __put_user_u64(val,addr,retval) \
(अणु \
__यंत्र__ __अस्थिर__( \
	"1:\n\t" \
	"mov.l	%R1,%2\n\t" \
	"mov.l	%S1,%T2\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov.l	4f,%0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3,%0\n\t" \
	".balign	4\n" \
	"4:	.long	2b\n\t" \
	".previous\n" \
	".section	__ex_table,\"a\"\n\t" \
	".long	1b, 3b\n\t" \
	".previous" \
	: "=r" (retval) \
	: "r" (val), "m" (__m(addr)), "i" (-EFAULT), "0" (retval) \
        : "memory"); पूर्ण)
#अन्यथा
#घोषणा __put_user_u64(val,addr,retval) \
(अणु \
__यंत्र__ __अस्थिर__( \
	"1:\n\t" \
	"mov.l	%S1,%2\n\t" \
	"mov.l	%R1,%T2\n\t" \
	"2:\n" \
	".section	.fixup,\"ax\"\n" \
	"3:\n\t" \
	"mov.l	4f,%0\n\t" \
	"jmp	@%0\n\t" \
	" mov	%3,%0\n\t" \
	".balign	4\n" \
	"4:	.long	2b\n\t" \
	".previous\n" \
	".section	__ex_table,\"a\"\n\t" \
	".long	1b, 3b\n\t" \
	".previous" \
	: "=r" (retval) \
	: "r" (val), "m" (__m(addr)), "i" (-EFAULT), "0" (retval) \
        : "memory"); पूर्ण)
#पूर्ण_अगर

बाह्य व्योम __put_user_unknown(व्योम);

#पूर्ण_अगर /* __ASM_SH_UACCESS_32_H */
