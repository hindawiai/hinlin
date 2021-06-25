<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_ATOMIC_GRB_H
#घोषणा __ASM_SH_ATOMIC_GRB_H

#घोषणा ATOMIC_OP(op)							\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__ (						\
		"   .align 2              \n\t"				\
		"   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */	\
		"   mov    r15,   r1      \n\t" /* r1 = saved sp */	\
		"   mov    #-6,   r15     \n\t" /* LOGIN: r15 = size */	\
		"   mov.l  @%1,   %0      \n\t" /* load  old value */	\
		" " #op "   %2,   %0      \n\t" /* $op */		\
		"   mov.l   %0,   @%1     \n\t" /* store new value */	\
		"1: mov     r1,   r15     \n\t" /* LOGOUT */		\
		: "=&r" (पंचांगp),						\
		  "+r"  (v)						\
		: "r"   (i)						\
		: "memory" , "r0", "r1");				\
पूर्ण									\

#घोषणा ATOMIC_OP_RETURN(op)						\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	पूर्णांक पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__ (						\
		"   .align 2              \n\t"				\
		"   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */	\
		"   mov    r15,   r1      \n\t" /* r1 = saved sp */	\
		"   mov    #-6,   r15     \n\t" /* LOGIN: r15 = size */	\
		"   mov.l  @%1,   %0      \n\t" /* load  old value */	\
		" " #op "   %2,   %0      \n\t" /* $op */		\
		"   mov.l   %0,   @%1     \n\t" /* store new value */	\
		"1: mov     r1,   r15     \n\t" /* LOGOUT */		\
		: "=&r" (पंचांगp),						\
		  "+r"  (v)						\
		: "r"   (i)						\
		: "memory" , "r0", "r1");				\
									\
	वापस पंचांगp;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op)						\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक res, पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__ (						\
		"   .align 2              \n\t"				\
		"   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */	\
		"   mov    r15,   r1      \n\t" /* r1 = saved sp */	\
		"   mov    #-6,   r15     \n\t" /* LOGIN: r15 = size */	\
		"   mov.l  @%2,   %0      \n\t" /* load old value */	\
		"   mov     %0,   %1      \n\t" /* save old value */	\
		" " #op "   %3,   %0      \n\t" /* $op */		\
		"   mov.l   %0,   @%2     \n\t" /* store new value */	\
		"1: mov     r1,   r15     \n\t" /* LOGOUT */		\
		: "=&r" (पंचांगp), "=&r" (res), "+r"  (v)			\
		: "r"   (i)						\
		: "memory" , "r0", "r1");				\
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

#पूर्ण_अगर /* __ASM_SH_ATOMIC_GRB_H */
