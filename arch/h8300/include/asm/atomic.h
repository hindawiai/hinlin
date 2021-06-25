<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_H8300_ATOMIC__
#घोषणा __ARCH_H8300_ATOMIC__

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/irqflags.h>

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 */

#घोषणा atomic_पढ़ो(v)		READ_ONCE((v)->counter)
#घोषणा atomic_set(v, i)	WRITE_ONCE(((v)->counter), (i))

#घोषणा ATOMIC_OP_RETURN(op, c_op)				\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)	\
अणु								\
	h8300flags flags;					\
	पूर्णांक ret;						\
								\
	flags = arch_local_irq_save();				\
	ret = v->counter c_op i;				\
	arch_local_irq_restore(flags);				\
	वापस ret;						\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op)				\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)		\
अणु								\
	h8300flags flags;					\
	पूर्णांक ret;						\
								\
	flags = arch_local_irq_save();				\
	ret = v->counter;					\
	v->counter c_op i;					\
	arch_local_irq_restore(flags);				\
	वापस ret;						\
पूर्ण

#घोषणा ATOMIC_OP(op, c_op)					\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)		\
अणु								\
	h8300flags flags;					\
								\
	flags = arch_local_irq_save();				\
	v->counter c_op i;					\
	arch_local_irq_restore(flags);				\
पूर्ण

ATOMIC_OP_RETURN(add, +=)
ATOMIC_OP_RETURN(sub, -=)

#घोषणा ATOMIC_OPS(op, c_op)					\
	ATOMIC_OP(op, c_op)					\
	ATOMIC_FETCH_OP(op, c_op)

ATOMIC_OPS(and, &=)
ATOMIC_OPS(or,  |=)
ATOMIC_OPS(xor, ^=)
ATOMIC_OPS(add, +=)
ATOMIC_OPS(sub, -=)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

अटल अंतरभूत पूर्णांक atomic_cmpxchg(atomic_t *v, पूर्णांक old, पूर्णांक new)
अणु
	पूर्णांक ret;
	h8300flags flags;

	flags = arch_local_irq_save();
	ret = v->counter;
	अगर (likely(ret == old))
		v->counter = new;
	arch_local_irq_restore(flags);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक atomic_fetch_add_unless(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
	पूर्णांक ret;
	h8300flags flags;

	flags = arch_local_irq_save();
	ret = v->counter;
	अगर (ret != u)
		v->counter += a;
	arch_local_irq_restore(flags);
	वापस ret;
पूर्ण
#घोषणा atomic_fetch_add_unless		atomic_fetch_add_unless

#पूर्ण_अगर /* __ARCH_H8300_ATOMIC __ */
