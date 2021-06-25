<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CMPXCHG_LLSC_H
#घोषणा __ASM_SH_CMPXCHG_LLSC_H

अटल अंतरभूत अचिन्हित दीर्घ xchg_u32(अस्थिर u32 *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ retval;
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__ (
		"1:					\n\t"
		"movli.l	@%2, %0	! xchg_u32	\n\t"
		"mov		%0, %1			\n\t"
		"mov		%3, %0			\n\t"
		"movco.l	%0, @%2			\n\t"
		"bf		1b			\n\t"
		"synco					\n\t"
		: "=&z"(पंचांगp), "=&r" (retval)
		: "r" (m), "r" (val)
		: "t", "memory"
	);

	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
__cmpxchg_u32(अस्थिर u32 *m, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ retval;
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%2, %0	! __cmpxchg_u32		\n\t"
		"mov		%0, %1				\n\t"
		"cmp/eq		%1, %3				\n\t"
		"bf		2f				\n\t"
		"mov		%4, %0				\n\t"
		"2:						\n\t"
		"movco.l	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"synco						\n\t"
		: "=&z" (पंचांगp), "=&r" (retval)
		: "r" (m), "r" (old), "r" (new)
		: "t", "memory"
	);

	वापस retval;
पूर्ण

#समावेश <यंत्र/cmpxchg-xchg.h>

#पूर्ण_अगर /* __ASM_SH_CMPXCHG_LLSC_H */
