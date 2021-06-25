<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_M68K_ATOMIC__
#घोषणा __ARCH_M68K_ATOMIC__

#समावेश <linux/types.h>
#समावेश <linux/irqflags.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 */

/*
 * We करो not have SMP m68k प्रणालीs, so we करोn't have to deal with that.
 */

#घोषणा atomic_पढ़ो(v)		READ_ONCE((v)->counter)
#घोषणा atomic_set(v, i)	WRITE_ONCE(((v)->counter), (i))

/*
 * The ColdFire parts cannot करो some immediate to memory operations,
 * so क्रम them we करो not specअगरy the "i" यंत्र स्थिरraपूर्णांक.
 */
#अगर_घोषित CONFIG_COLDFIRE
#घोषणा	ASM_DI	"d"
#अन्यथा
#घोषणा	ASM_DI	"di"
#पूर्ण_अगर

#घोषणा ATOMIC_OP(op, c_op, यंत्र_op)					\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	__यंत्र__ __अस्थिर__(#यंत्र_op "l %1,%0" : "+m" (*v) : ASM_DI (i));\
पूर्ण									\

#अगर_घोषित CONFIG_RMW_INSNS

#घोषणा ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	पूर्णांक t, पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:	movel %2,%1\n"				\
			"	" #यंत्र_op "l %3,%1\n"			\
			"	casl %2,%1,%0\n"			\
			"	jne 1b"					\
			: "+m" (*v), "=&d" (t), "=&d" (पंचांगp)		\
			: "g" (i), "2" (atomic_पढ़ो(v)));		\
	वापस t;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक t, पंचांगp;							\
									\
	__यंत्र__ __अस्थिर__(						\
			"1:	movel %2,%1\n"				\
			"	" #यंत्र_op "l %3,%1\n"			\
			"	casl %2,%1,%0\n"			\
			"	jne 1b"					\
			: "+m" (*v), "=&d" (t), "=&d" (पंचांगp)		\
			: "g" (i), "2" (atomic_पढ़ो(v)));		\
	वापस पंचांगp;							\
पूर्ण

#अन्यथा

#घोषणा ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t * v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक t;								\
									\
	local_irq_save(flags);						\
	t = (v->counter c_op i);					\
	local_irq_restore(flags);					\
									\
	वापस t;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op, यंत्र_op)				\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t * v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक t;								\
									\
	local_irq_save(flags);						\
	t = v->counter;							\
	v->counter c_op i;						\
	local_irq_restore(flags);					\
									\
	वापस t;							\
पूर्ण

#पूर्ण_अगर /* CONFIG_RMW_INSNS */

#घोषणा ATOMIC_OPS(op, c_op, यंत्र_op)					\
	ATOMIC_OP(op, c_op, यंत्र_op)					\
	ATOMIC_OP_RETURN(op, c_op, यंत्र_op)				\
	ATOMIC_FETCH_OP(op, c_op, यंत्र_op)

ATOMIC_OPS(add, +=, add)
ATOMIC_OPS(sub, -=, sub)

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op, c_op, यंत्र_op)					\
	ATOMIC_OP(op, c_op, यंत्र_op)					\
	ATOMIC_FETCH_OP(op, c_op, यंत्र_op)

ATOMIC_OPS(and, &=, and)
ATOMIC_OPS(or, |=, or)
ATOMIC_OPS(xor, ^=, eor)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

अटल अंतरभूत व्योम atomic_inc(atomic_t *v)
अणु
	__यंत्र__ __अस्थिर__("addql #1,%0" : "+m" (*v));
पूर्ण
#घोषणा atomic_inc atomic_inc

अटल अंतरभूत व्योम atomic_dec(atomic_t *v)
अणु
	__यंत्र__ __अस्थिर__("subql #1,%0" : "+m" (*v));
पूर्ण
#घोषणा atomic_dec atomic_dec

अटल अंतरभूत पूर्णांक atomic_dec_and_test(atomic_t *v)
अणु
	अक्षर c;
	__यंत्र__ __अस्थिर__("subql #1,%1; seq %0" : "=d" (c), "+m" (*v));
	वापस c != 0;
पूर्ण
#घोषणा atomic_dec_and_test atomic_dec_and_test

अटल अंतरभूत पूर्णांक atomic_dec_and_test_lt(atomic_t *v)
अणु
	अक्षर c;
	__यंत्र__ __अस्थिर__(
		"subql #1,%1; slt %0"
		: "=d" (c), "=m" (*v)
		: "m" (*v));
	वापस c != 0;
पूर्ण

अटल अंतरभूत पूर्णांक atomic_inc_and_test(atomic_t *v)
अणु
	अक्षर c;
	__यंत्र__ __अस्थिर__("addql #1,%1; seq %0" : "=d" (c), "+m" (*v));
	वापस c != 0;
पूर्ण
#घोषणा atomic_inc_and_test atomic_inc_and_test

#अगर_घोषित CONFIG_RMW_INSNS

#घोषणा atomic_cmpxchg(v, o, n) ((पूर्णांक)cmpxchg(&((v)->counter), (o), (n)))
#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))

#अन्यथा /* !CONFIG_RMW_INSNS */

अटल अंतरभूत पूर्णांक atomic_cmpxchg(atomic_t *v, पूर्णांक old, पूर्णांक new)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक prev;

	local_irq_save(flags);
	prev = atomic_पढ़ो(v);
	अगर (prev == old)
		atomic_set(v, new);
	local_irq_restore(flags);
	वापस prev;
पूर्ण

अटल अंतरभूत पूर्णांक atomic_xchg(atomic_t *v, पूर्णांक new)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक prev;

	local_irq_save(flags);
	prev = atomic_पढ़ो(v);
	atomic_set(v, new);
	local_irq_restore(flags);
	वापस prev;
पूर्ण

#पूर्ण_अगर /* !CONFIG_RMW_INSNS */

अटल अंतरभूत पूर्णांक atomic_sub_and_test(पूर्णांक i, atomic_t *v)
अणु
	अक्षर c;
	__यंत्र__ __अस्थिर__("subl %2,%1; seq %0"
			     : "=d" (c), "+m" (*v)
			     : ASM_DI (i));
	वापस c != 0;
पूर्ण
#घोषणा atomic_sub_and_test atomic_sub_and_test

अटल अंतरभूत पूर्णांक atomic_add_negative(पूर्णांक i, atomic_t *v)
अणु
	अक्षर c;
	__यंत्र__ __अस्थिर__("addl %2,%1; smi %0"
			     : "=d" (c), "+m" (*v)
			     : ASM_DI (i));
	वापस c != 0;
पूर्ण
#घोषणा atomic_add_negative atomic_add_negative

#पूर्ण_अगर /* __ARCH_M68K_ATOMIC __ */
