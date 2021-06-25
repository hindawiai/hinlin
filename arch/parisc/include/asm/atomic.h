<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2000 Philipp Rumpf <prumpf@tux.org>
 * Copyright (C) 2006 Kyle McMartin <kyle@parisc-linux.org>
 */

#अगर_अघोषित _ASM_PARISC_ATOMIC_H_
#घोषणा _ASM_PARISC_ATOMIC_H_

#समावेश <linux/types.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/barrier.h>

/*
 * Atomic operations that C can't guarantee us.  Useful क्रम
 * resource counting etc..
 *
 * And probably incredibly slow on parisc.  OTOH, we करोn't
 * have to ग_लिखो any serious assembly.   prumpf
 */

#अगर_घोषित CONFIG_SMP
#समावेश <यंत्र/spinlock.h>
#समावेश <यंत्र/cache.h>		/* we use L1_CACHE_BYTES */

/* Use an array of spinlocks क्रम our atomic_ts.
 * Hash function to index पूर्णांकo a dअगरferent SPINLOCK.
 * Since "a" is usually an address, use one spinlock per cacheline.
 */
#  define ATOMIC_HASH_SIZE 4
#  define ATOMIC_HASH(a) (&(__atomic_hash[ (((अचिन्हित दीर्घ) (a))/L1_CACHE_BYTES) & (ATOMIC_HASH_SIZE-1) ]))

बाह्य arch_spinlock_t __atomic_hash[ATOMIC_HASH_SIZE] __lock_aligned;

/* Can't use raw_spin_lock_irq because of #समावेश problems, so
 * this is the substitute */
#घोषणा _atomic_spin_lock_irqsave(l,f) करो अणु	\
	arch_spinlock_t *s = ATOMIC_HASH(l);	\
	local_irq_save(f);			\
	arch_spin_lock(s);			\
पूर्ण जबतक(0)

#घोषणा _atomic_spin_unlock_irqrestore(l,f) करो अणु	\
	arch_spinlock_t *s = ATOMIC_HASH(l);		\
	arch_spin_unlock(s);				\
	local_irq_restore(f);				\
पूर्ण जबतक(0)


#अन्यथा
#  define _atomic_spin_lock_irqsave(l,f) करो अणु local_irq_save(f); पूर्ण जबतक (0)
#  define _atomic_spin_unlock_irqrestore(l,f) करो अणु local_irq_restore(f); पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * Note that we need not lock पढ़ो accesses - aligned word ग_लिखोs/पढ़ोs
 * are atomic, so a पढ़ोer never sees inconsistent values.
 */

अटल __अंतरभूत__ व्योम atomic_set(atomic_t *v, पूर्णांक i)
अणु
	अचिन्हित दीर्घ flags;
	_atomic_spin_lock_irqsave(v, flags);

	v->counter = i;

	_atomic_spin_unlock_irqrestore(v, flags);
पूर्ण

#घोषणा atomic_set_release(v, i)	atomic_set((v), (i))

अटल __अंतरभूत__ पूर्णांक atomic_पढ़ो(स्थिर atomic_t *v)
अणु
	वापस READ_ONCE((v)->counter);
पूर्ण

/* exported पूर्णांकerface */
#घोषणा atomic_cmpxchg(v, o, n) (cmpxchg(&((v)->counter), (o), (n)))
#घोषणा atomic_xchg(v, new) (xchg(&((v)->counter), new))

#घोषणा ATOMIC_OP(op, c_op)						\
अटल __अंतरभूत__ व्योम atomic_##op(पूर्णांक i, atomic_t *v)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
									\
	_atomic_spin_lock_irqsave(v, flags);				\
	v->counter c_op i;						\
	_atomic_spin_unlock_irqrestore(v, flags);			\
पूर्ण

#घोषणा ATOMIC_OP_RETURN(op, c_op)					\
अटल __अंतरभूत__ पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक ret;							\
									\
	_atomic_spin_lock_irqsave(v, flags);				\
	ret = (v->counter c_op i);					\
	_atomic_spin_unlock_irqrestore(v, flags);			\
									\
	वापस ret;							\
पूर्ण

#घोषणा ATOMIC_FETCH_OP(op, c_op)					\
अटल __अंतरभूत__ पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
	पूर्णांक ret;							\
									\
	_atomic_spin_lock_irqsave(v, flags);				\
	ret = v->counter;						\
	v->counter c_op i;						\
	_atomic_spin_unlock_irqrestore(v, flags);			\
									\
	वापस ret;							\
पूर्ण

#घोषणा ATOMIC_OPS(op, c_op)						\
	ATOMIC_OP(op, c_op)						\
	ATOMIC_OP_RETURN(op, c_op)					\
	ATOMIC_FETCH_OP(op, c_op)

ATOMIC_OPS(add, +=)
ATOMIC_OPS(sub, -=)

#अघोषित ATOMIC_OPS
#घोषणा ATOMIC_OPS(op, c_op)						\
	ATOMIC_OP(op, c_op)						\
	ATOMIC_FETCH_OP(op, c_op)

ATOMIC_OPS(and, &=)
ATOMIC_OPS(or, |=)
ATOMIC_OPS(xor, ^=)

#अघोषित ATOMIC_OPS
#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN
#अघोषित ATOMIC_OP

#अगर_घोषित CONFIG_64BIT

#घोषणा ATOMIC64_INIT(i) अणु (i) पूर्ण

#घोषणा ATOMIC64_OP(op, c_op)						\
अटल __अंतरभूत__ व्योम atomic64_##op(s64 i, atomic64_t *v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
									\
	_atomic_spin_lock_irqsave(v, flags);				\
	v->counter c_op i;						\
	_atomic_spin_unlock_irqrestore(v, flags);			\
पूर्ण

#घोषणा ATOMIC64_OP_RETURN(op, c_op)					\
अटल __अंतरभूत__ s64 atomic64_##op##_वापस(s64 i, atomic64_t *v)	\
अणु									\
	अचिन्हित दीर्घ flags;						\
	s64 ret;							\
									\
	_atomic_spin_lock_irqsave(v, flags);				\
	ret = (v->counter c_op i);					\
	_atomic_spin_unlock_irqrestore(v, flags);			\
									\
	वापस ret;							\
पूर्ण

#घोषणा ATOMIC64_FETCH_OP(op, c_op)					\
अटल __अंतरभूत__ s64 atomic64_fetch_##op(s64 i, atomic64_t *v)		\
अणु									\
	अचिन्हित दीर्घ flags;						\
	s64 ret;							\
									\
	_atomic_spin_lock_irqsave(v, flags);				\
	ret = v->counter;						\
	v->counter c_op i;						\
	_atomic_spin_unlock_irqrestore(v, flags);			\
									\
	वापस ret;							\
पूर्ण

#घोषणा ATOMIC64_OPS(op, c_op)						\
	ATOMIC64_OP(op, c_op)						\
	ATOMIC64_OP_RETURN(op, c_op)					\
	ATOMIC64_FETCH_OP(op, c_op)

ATOMIC64_OPS(add, +=)
ATOMIC64_OPS(sub, -=)

#अघोषित ATOMIC64_OPS
#घोषणा ATOMIC64_OPS(op, c_op)						\
	ATOMIC64_OP(op, c_op)						\
	ATOMIC64_FETCH_OP(op, c_op)

ATOMIC64_OPS(and, &=)
ATOMIC64_OPS(or, |=)
ATOMIC64_OPS(xor, ^=)

#अघोषित ATOMIC64_OPS
#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_OP_RETURN
#अघोषित ATOMIC64_OP

अटल __अंतरभूत__ व्योम
atomic64_set(atomic64_t *v, s64 i)
अणु
	अचिन्हित दीर्घ flags;
	_atomic_spin_lock_irqsave(v, flags);

	v->counter = i;

	_atomic_spin_unlock_irqrestore(v, flags);
पूर्ण

#घोषणा atomic64_set_release(v, i)	atomic64_set((v), (i))

अटल __अंतरभूत__ s64
atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	वापस READ_ONCE((v)->counter);
पूर्ण

/* exported पूर्णांकerface */
#घोषणा atomic64_cmpxchg(v, o, n) \
	((__typeof__((v)->counter))cmpxchg(&((v)->counter), (o), (n)))
#घोषणा atomic64_xchg(v, new) (xchg(&((v)->counter), new))

#पूर्ण_अगर /* !CONFIG_64BIT */


#पूर्ण_अगर /* _ASM_PARISC_ATOMIC_H_ */
