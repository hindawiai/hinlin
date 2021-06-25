<शैली गुरु>
/*
 * Copyright (C) 2014 Stefan Kristiansson <stefan.kristiansson@saunalahti.fi>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित __ASM_OPENRISC_ATOMIC_H
#घोषणा __ASM_OPENRISC_ATOMIC_H

#समावेश <linux/types.h>

/* Atomically perक्रमm op with v->counter and i */
#घोषणा ATOMIC_OP(op)							\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__(						\
		"1:	l.lwa	%0,0(%1)	\n"			\
		"	l." #op " %0,%0,%2	\n"			\
		"	l.swa	0(%1),%0	\n"			\
		"	l.bnf	1b		\n"			\
		"	 l.nop			\n"			\
		: "=&r"(पंचांगp)						\
		: "r"(&v->counter), "r"(i)				\
		: "cc", "memory");					\
पूर्ण

/* Atomically perक्रमm op with v->counter and i, वापस the result */
#घोषणा ATOMIC_OP_RETURN(op)						\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	पूर्णांक पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__(						\
		"1:	l.lwa	%0,0(%1)	\n"			\
		"	l." #op " %0,%0,%2	\n"			\
		"	l.swa	0(%1),%0	\n"			\
		"	l.bnf	1b		\n"			\
		"	 l.nop			\n"			\
		: "=&r"(पंचांगp)						\
		: "r"(&v->counter), "r"(i)				\
		: "cc", "memory");					\
									\
	वापस पंचांगp;							\
पूर्ण

/* Atomically perक्रमm op with v->counter and i, वापस orig v->counter */
#घोषणा ATOMIC_FETCH_OP(op)						\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक पंचांगp, old;							\
									\
	__यंत्र__ __अस्थिर__(						\
		"1:	l.lwa	%0,0(%2)	\n"			\
		"	l." #op " %1,%0,%3	\n"			\
		"	l.swa	0(%2),%1	\n"			\
		"	l.bnf	1b		\n"			\
		"	 l.nop			\n"			\
		: "=&r"(old), "=&r"(पंचांगp)				\
		: "r"(&v->counter), "r"(i)				\
		: "cc", "memory");					\
									\
	वापस old;							\
पूर्ण

ATOMIC_OP_RETURN(add)
ATOMIC_OP_RETURN(sub)

ATOMIC_FETCH_OP(add)
ATOMIC_FETCH_OP(sub)
ATOMIC_FETCH_OP(and)
ATOMIC_FETCH_OP(or)
ATOMIC_FETCH_OP(xor)

ATOMIC_OP(and)
ATOMIC_OP(or)
ATOMIC_OP(xor)

#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#घोषणा atomic_add_वापस	atomic_add_वापस
#घोषणा atomic_sub_वापस	atomic_sub_वापस
#घोषणा atomic_fetch_add	atomic_fetch_add
#घोषणा atomic_fetch_sub	atomic_fetch_sub
#घोषणा atomic_fetch_and	atomic_fetch_and
#घोषणा atomic_fetch_or		atomic_fetch_or
#घोषणा atomic_fetch_xor	atomic_fetch_xor
#घोषणा atomic_and	atomic_and
#घोषणा atomic_or	atomic_or
#घोषणा atomic_xor	atomic_xor

/*
 * Atomically add a to v->counter as दीर्घ as v is not alपढ़ोy u.
 * Returns the original value at v->counter.
 *
 * This is often used through atomic_inc_not_zero()
 */
अटल अंतरभूत पूर्णांक atomic_fetch_add_unless(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
	पूर्णांक old, पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	l.lwa %0, 0(%2)		\n"
		"	l.sfeq %0, %4		\n"
		"	l.bf 2f			\n"
		"	 l.add %1, %0, %3	\n"
		"	l.swa 0(%2), %1		\n"
		"	l.bnf 1b		\n"
		"	 l.nop			\n"
		"2:				\n"
		: "=&r"(old), "=&r" (पंचांगp)
		: "r"(&v->counter), "r"(a), "r"(u)
		: "cc", "memory");

	वापस old;
पूर्ण
#घोषणा atomic_fetch_add_unless	atomic_fetch_add_unless

#समावेश <यंत्र-generic/atomic.h>

#पूर्ण_अगर /* __ASM_OPENRISC_ATOMIC_H */
