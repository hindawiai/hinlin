<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_ATOMIC_LLSC_H
#घोषणा __ASM_SH_ATOMIC_LLSC_H

/*
 * SH-4A note:
 *
 * We basically get atomic_xxx_वापस() क्रम मुक्त compared with
 * atomic_xxx(). movli.l/movco.l require r0 due to the inकाष्ठाion
 * encoding, so the retval is स्वतःmatically set without having to
 * करो any special work.
 */
/*
 * To get proper branch prediction क्रम the मुख्य line, we must branch
 * क्रमward to code at the end of this object's .text section, then
 * branch back to restart the operation.
 */

#घोषणा ATOMIC_OP(op)							\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ पंचांगp;						\
									\
	__यंत्र__ __अस्थिर__ (						\
"1:	movli.l @%2, %0		! atomic_" #op "\n"			\
"	" #op "	%1, %0				\n"			\
"	movco.l	%0, @%2				\n"			\
"	bf	1b				\n"			\
	: "=&z" (पंचांगp)							\
	: "r" (i), "r" (&v->counter)					\
	: "t");								\
पूर्ण

#घोषणा ATOMIC_OP_RETURN(op)						\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	अचिन्हित दीर्घ temp;						\
									\
	__यंत्र__ __अस्थिर__ (						\
"1:	movli.l @%2, %0		! atomic_" #op "_return	\n"		\
"	" #op "	%1, %0					\n"		\
"	movco.l	%0, @%2					\n"		\
"	bf	1b					\n"		\
"	synco						\n"		\
	: "=&z" (temp)							\
	: "r" (i), "r" (&v->counter)					\
	: "t");								\
									\
	वापस temp;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op)						\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ res, temp;					\
									\
	__यंत्र__ __अस्थिर__ (						\
"1:	movli.l @%3, %0		! atomic_fetch_" #op "	\n"		\
"	mov %0, %1					\n"		\
"	" #op "	%2, %0					\n"		\
"	movco.l	%0, @%3					\n"		\
"	bf	1b					\n"		\
"	synco						\n"		\
	: "=&z" (temp), "=&r" (res)					\
	: "r" (i), "r" (&v->counter)					\
	: "t");								\
									\
	वापस res;							\
पूर्ण

#घोषणा ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_OP_RETURN(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(add)
ATOMIC_OPS(sub)

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op) ATOMIC_OP(op) ATOMIC_FETCH_OP(op)

ATOMIC_OPS(and)
ATOMIC_OPS(or)
ATOMIC_OPS(xor)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#पूर्ण_अगर /* __ASM_SH_ATOMIC_LLSC_H */
