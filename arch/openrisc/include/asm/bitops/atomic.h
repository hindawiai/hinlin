<शैली गुरु>
/*
 * Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __ASM_OPENRISC_BITOPS_ATOMIC_H
#घोषणा __ASM_OPENRISC_BITOPS_ATOMIC_H

अटल अंतरभूत व्योम set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	l.lwa	%0,0(%1)	\n"
		"	l.or	%0,%0,%2	\n"
		"	l.swa	0(%1),%0	\n"
		"	l.bnf	1b		\n"
		"	 l.nop			\n"
		: "=&r"(पंचांगp)
		: "r"(p), "r"(mask)
		: "cc", "memory");
पूर्ण

अटल अंतरभूत व्योम clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	l.lwa	%0,0(%1)	\n"
		"	l.and	%0,%0,%2	\n"
		"	l.swa	0(%1),%0	\n"
		"	l.bnf	1b		\n"
		"	 l.nop			\n"
		: "=&r"(पंचांगp)
		: "r"(p), "r"(~mask)
		: "cc", "memory");
पूर्ण

अटल अंतरभूत व्योम change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	l.lwa	%0,0(%1)	\n"
		"	l.xor	%0,%0,%2	\n"
		"	l.swa	0(%1),%0	\n"
		"	l.bnf	1b		\n"
		"	 l.nop			\n"
		: "=&r"(पंचांगp)
		: "r"(p), "r"(mask)
		: "cc", "memory");
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ old;
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	l.lwa	%0,0(%2)	\n"
		"	l.or	%1,%0,%3	\n"
		"	l.swa	0(%2),%1	\n"
		"	l.bnf	1b		\n"
		"	 l.nop			\n"
		: "=&r"(old), "=&r"(पंचांगp)
		: "r"(p), "r"(mask)
		: "cc", "memory");

	वापस (old & mask) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ old;
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	l.lwa	%0,0(%2)	\n"
		"	l.and	%1,%0,%3	\n"
		"	l.swa	0(%2),%1	\n"
		"	l.bnf	1b		\n"
		"	 l.nop			\n"
		: "=&r"(old), "=&r"(पंचांगp)
		: "r"(p), "r"(~mask)
		: "cc", "memory");

	वापस (old & mask) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक test_and_change_bit(पूर्णांक nr, अस्थिर अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ old;
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	l.lwa	%0,0(%2)	\n"
		"	l.xor	%1,%0,%3	\n"
		"	l.swa	0(%2),%1	\n"
		"	l.bnf	1b		\n"
		"	 l.nop			\n"
		: "=&r"(old), "=&r"(पंचांगp)
		: "r"(p), "r"(mask)
		: "cc", "memory");

	वापस (old & mask) != 0;
पूर्ण

#पूर्ण_अगर /* __ASM_OPENRISC_BITOPS_ATOMIC_H */
