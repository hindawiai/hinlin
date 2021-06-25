<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Generic C implementation of atomic counter operations. Usable on
 * UP प्रणालीs only. Do not include in machine independent code.
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अगर_अघोषित __ASM_GENERIC_ATOMIC_H
#घोषणा __ASM_GENERIC_ATOMIC_H

#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>

/*
 * atomic_$op() - $op पूर्णांकeger to atomic variable
 * @i: पूर्णांकeger value to $op
 * @v: poपूर्णांकer to the atomic variable
 *
 * Atomically $ops @i to @v. Does not strictly guarantee a memory-barrier, use
 * smp_mb__अणुbeक्रमe,afterपूर्ण_atomic().
 */

/*
 * atomic_$op_वापस() - $op पूर्णांकerer to atomic variable and वापसs the result
 * @i: पूर्णांकeger value to $op
 * @v: poपूर्णांकer to the atomic variable
 *
 * Atomically $ops @i to @v. Does imply a full memory barrier.
 */

#अगर_घोषित CONFIG_SMP

/* we can build all atomic primitives from cmpxchg */

#घोषणा ATOMIC_OP(op, c_op)						\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक c, old;							\
									\
	c = v->counter;							\
	जबतक ((old = cmpxchg(&v->counter, c, c c_op i)) != c)		\
		c = old;						\
पूर्ण

#घोषणा ATOMIC_OP_RETURN(op, c_op)					\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	पूर्णांक c, old;							\
									\
	c = v->counter;							\
	जबतक ((old = cmpxchg(&v->counter, c, c c_op i)) != c)		\
		c = old;						\
									\
	वापस c c_op i;						\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op)					\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	पूर्णांक c, old;							\
									\
	c = v->counter;							\
	जबतक ((old = cmpxchg(&v->counter, c, c c_op i)) != c)		\
		c = old;						\
									\
	वापस c;							\
पूर्ण

#अन्यथा

#समावेश <linux/irqflags.h>

#घोषणा ATOMIC_OP(op, c_op)						\
अटल अंतरभूत व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
									\
	raw_local_irq_save(flags);					\
	v->counter = v->counter c_op i;					\
	raw_local_irq_restore(flags);					\
पूर्ण

#घोषणा ATOMIC_OP_RETURN(op, c_op)					\
अटल अंतरभूत पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक ret;							\
									\
	raw_local_irq_save(flags);					\
	ret = (v->counter = v->counter c_op i);				\
	raw_local_irq_restore(flags);					\
									\
	वापस ret;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op)					\
अटल अंतरभूत पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक ret;							\
									\
	raw_local_irq_save(flags);					\
	ret = v->counter;						\
	v->counter = v->counter c_op i;					\
	raw_local_irq_restore(flags);					\
									\
	वापस ret;							\
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#अगर_अघोषित atomic_add_वापस
ATOMIC_OP_RETURN(add, +)
#पूर्ण_अगर

#अगर_अघोषित atomic_sub_वापस
ATOMIC_OP_RETURN(sub, -)
#पूर्ण_अगर

#अगर_अघोषित atomic_fetch_add
ATOMIC_FETCH_OP(add, +)
#पूर्ण_अगर

#अगर_अघोषित atomic_fetch_sub
ATOMIC_FETCH_OP(sub, -)
#पूर्ण_अगर

#अगर_अघोषित atomic_fetch_and
ATOMIC_FETCH_OP(and, &)
#पूर्ण_अगर

#अगर_अघोषित atomic_fetch_or
ATOMIC_FETCH_OP(or, |)
#पूर्ण_अगर

#अगर_अघोषित atomic_fetch_xor
ATOMIC_FETCH_OP(xor, ^)
#पूर्ण_अगर

#अगर_अघोषित atomic_and
ATOMIC_OP(and, &)
#पूर्ण_अगर

#अगर_अघोषित atomic_or
ATOMIC_OP(or, |)
#पूर्ण_अगर

#अगर_अघोषित atomic_xor
ATOMIC_OP(xor, ^)
#पूर्ण_अगर

#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 */

/**
 * atomic_पढ़ो - पढ़ो atomic variable
 * @v: poपूर्णांकer of type atomic_t
 *
 * Atomically पढ़ोs the value of @v.
 */
#अगर_अघोषित atomic_पढ़ो
#घोषणा atomic_पढ़ो(v)	READ_ONCE((v)->counter)
#पूर्ण_अगर

/**
 * atomic_set - set atomic variable
 * @v: poपूर्णांकer of type atomic_t
 * @i: required value
 *
 * Atomically sets the value of @v to @i.
 */
#घोषणा atomic_set(v, i) WRITE_ONCE(((v)->counter), (i))

#समावेश <linux/irqflags.h>

अटल अंतरभूत व्योम atomic_add(पूर्णांक i, atomic_t *v)
अणु
	atomic_add_वापस(i, v);
पूर्ण

अटल अंतरभूत व्योम atomic_sub(पूर्णांक i, atomic_t *v)
अणु
	atomic_sub_वापस(i, v);
पूर्ण

#घोषणा atomic_xchg(ptr, v)		(xchg(&(ptr)->counter, (v)))
#घोषणा atomic_cmpxchg(v, old, new)	(cmpxchg(&((v)->counter), (old), (new)))

#पूर्ण_अगर /* __ASM_GENERIC_ATOMIC_H */
