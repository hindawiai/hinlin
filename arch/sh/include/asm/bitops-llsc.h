<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BITOPS_LLSC_H
#घोषणा __ASM_SH_BITOPS_LLSC_H

अटल अंतरभूत व्योम set_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक	mask;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
	अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%1, %0	! set_bit		\n\t"
		"or		%2, %0				\n\t"
		"movco.l	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (पंचांगp)
		: "r" (a), "r" (mask)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत व्योम clear_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक	mask;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
	अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%1, %0	! clear_bit		\n\t"
		"and		%2, %0				\n\t"
		"movco.l	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (पंचांगp)
		: "r" (a), "r" (~mask)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत व्योम change_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक	mask;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
	अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%1, %0	! change_bit		\n\t"
		"xor		%2, %0				\n\t"
		"movco.l	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (पंचांगp)
		: "r" (a), "r" (mask)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक	mask, retval;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
	अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%2, %0	! test_and_set_bit	\n\t"
		"mov		%0, %1				\n\t"
		"or		%3, %0				\n\t"
		"movco.l	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"and		%3, %1				\n\t"
		: "=&z" (पंचांगp), "=&r" (retval)
		: "r" (a), "r" (mask)
		: "t", "memory"
	);

	वापस retval != 0;
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक	mask, retval;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
	अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%2, %0	! test_and_clear_bit	\n\t"
		"mov		%0, %1				\n\t"
		"and		%4, %0				\n\t"
		"movco.l	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"and		%3, %1				\n\t"
		"synco						\n\t"
		: "=&z" (पंचांगp), "=&r" (retval)
		: "r" (a), "r" (mask), "r" (~mask)
		: "t", "memory"
	);

	वापस retval != 0;
पूर्ण

अटल अंतरभूत पूर्णांक test_and_change_bit(पूर्णांक nr, अस्थिर व्योम *addr)
अणु
	पूर्णांक	mask, retval;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
	अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%2, %0	! test_and_change_bit	\n\t"
		"mov		%0, %1				\n\t"
		"xor		%3, %0				\n\t"
		"movco.l	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"and		%3, %1				\n\t"
		"synco						\n\t"
		: "=&z" (पंचांगp), "=&r" (retval)
		: "r" (a), "r" (mask)
		: "t", "memory"
	);

	वापस retval != 0;
पूर्ण

#समावेश <यंत्र-generic/bitops/non-atomic.h>

#पूर्ण_अगर /* __ASM_SH_BITOPS_LLSC_H */
