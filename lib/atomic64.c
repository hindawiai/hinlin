<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic implementation of 64-bit atomics using spinlocks,
 * useful on processors that करोn't have 64-bit atomic inकाष्ठाions.
 *
 * Copyright तऊ 2009 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/cache.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/atomic.h>

/*
 * We use a hashed array of spinlocks to provide exclusive access
 * to each atomic64_t variable.  Since this is expected to used on
 * प्रणालीs with small numbers of CPUs (<= 4 or so), we use a
 * relatively small array of 16 spinlocks to aव्योम wasting too much
 * memory on the spinlock array.
 */
#घोषणा NR_LOCKS	16

/*
 * Ensure each lock is in a separate cacheline.
 */
अटल जोड़ अणु
	raw_spinlock_t lock;
	अक्षर pad[L1_CACHE_BYTES];
पूर्ण atomic64_lock[NR_LOCKS] __cacheline_aligned_in_smp = अणु
	[0 ... (NR_LOCKS - 1)] = अणु
		.lock =  __RAW_SPIN_LOCK_UNLOCKED(atomic64_lock.lock),
	पूर्ण,
पूर्ण;

अटल अंतरभूत raw_spinlock_t *lock_addr(स्थिर atomic64_t *v)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) v;

	addr >>= L1_CACHE_SHIFT;
	addr ^= (addr >> 8) ^ (addr >> 16);
	वापस &atomic64_lock[addr & (NR_LOCKS - 1)].lock;
पूर्ण

s64 atomic64_पढ़ो(स्थिर atomic64_t *v)
अणु
	अचिन्हित दीर्घ flags;
	raw_spinlock_t *lock = lock_addr(v);
	s64 val;

	raw_spin_lock_irqsave(lock, flags);
	val = v->counter;
	raw_spin_unlock_irqrestore(lock, flags);
	वापस val;
पूर्ण
EXPORT_SYMBOL(atomic64_पढ़ो);

व्योम atomic64_set(atomic64_t *v, s64 i)
अणु
	अचिन्हित दीर्घ flags;
	raw_spinlock_t *lock = lock_addr(v);

	raw_spin_lock_irqsave(lock, flags);
	v->counter = i;
	raw_spin_unlock_irqrestore(lock, flags);
पूर्ण
EXPORT_SYMBOL(atomic64_set);

#घोषणा ATOMIC64_OP(op, c_op)						\
व्योम atomic64_##op(s64 a, atomic64_t *v)				\
अणु									\
	अचिन्हित दीर्घ flags;						\
	raw_spinlock_t *lock = lock_addr(v);				\
									\
	raw_spin_lock_irqsave(lock, flags);				\
	v->counter c_op a;						\
	raw_spin_unlock_irqrestore(lock, flags);			\
पूर्ण									\
EXPORT_SYMBOL(atomic64_##op);

#घोषणा ATOMIC64_OP_RETURN(op, c_op)					\
s64 atomic64_##op##_वापस(s64 a, atomic64_t *v)			\
अणु									\
	अचिन्हित दीर्घ flags;						\
	raw_spinlock_t *lock = lock_addr(v);				\
	s64 val;							\
									\
	raw_spin_lock_irqsave(lock, flags);				\
	val = (v->counter c_op a);					\
	raw_spin_unlock_irqrestore(lock, flags);			\
	वापस val;							\
पूर्ण									\
EXPORT_SYMBOL(atomic64_##op##_वापस);

#घोषणा ATOMIC64_FETCH_OP(op, c_op)					\
s64 atomic64_fetch_##op(s64 a, atomic64_t *v)				\
अणु									\
	अचिन्हित दीर्घ flags;						\
	raw_spinlock_t *lock = lock_addr(v);				\
	s64 val;							\
									\
	raw_spin_lock_irqsave(lock, flags);				\
	val = v->counter;						\
	v->counter c_op a;						\
	raw_spin_unlock_irqrestore(lock, flags);			\
	वापस val;							\
पूर्ण									\
EXPORT_SYMBOL(atomic64_fetch_##op);

#घोषणा ATOMIC64_OPS(op, c_op)						\
	ATOMIC64_OP(op, c_op)						\
	ATOMIC64_OP_RETURN(op, c_op)					\
	ATOMIC64_FETCH_OP(op, c_op)

ATOMIC64_OPS(add, +=)
ATOMIC64_OPS(sub, -=)

#अघोषित ATOMIC64_OPS
#घोषणा ATOMIC64_OPS(op, c_op)						\
	ATOMIC64_OP(op, c_op)						\
	ATOMIC64_OP_RETURN(op, c_op)					\
	ATOMIC64_FETCH_OP(op, c_op)

ATOMIC64_OPS(and, &=)
ATOMIC64_OPS(or, |=)
ATOMIC64_OPS(xor, ^=)

#अघोषित ATOMIC64_OPS
#अघोषित ATOMIC64_FETCH_OP
#अघोषित ATOMIC64_OP_RETURN
#अघोषित ATOMIC64_OP

s64 atomic64_dec_अगर_positive(atomic64_t *v)
अणु
	अचिन्हित दीर्घ flags;
	raw_spinlock_t *lock = lock_addr(v);
	s64 val;

	raw_spin_lock_irqsave(lock, flags);
	val = v->counter - 1;
	अगर (val >= 0)
		v->counter = val;
	raw_spin_unlock_irqrestore(lock, flags);
	वापस val;
पूर्ण
EXPORT_SYMBOL(atomic64_dec_अगर_positive);

s64 atomic64_cmpxchg(atomic64_t *v, s64 o, s64 n)
अणु
	अचिन्हित दीर्घ flags;
	raw_spinlock_t *lock = lock_addr(v);
	s64 val;

	raw_spin_lock_irqsave(lock, flags);
	val = v->counter;
	अगर (val == o)
		v->counter = n;
	raw_spin_unlock_irqrestore(lock, flags);
	वापस val;
पूर्ण
EXPORT_SYMBOL(atomic64_cmpxchg);

s64 atomic64_xchg(atomic64_t *v, s64 new)
अणु
	अचिन्हित दीर्घ flags;
	raw_spinlock_t *lock = lock_addr(v);
	s64 val;

	raw_spin_lock_irqsave(lock, flags);
	val = v->counter;
	v->counter = new;
	raw_spin_unlock_irqrestore(lock, flags);
	वापस val;
पूर्ण
EXPORT_SYMBOL(atomic64_xchg);

s64 atomic64_fetch_add_unless(atomic64_t *v, s64 a, s64 u)
अणु
	अचिन्हित दीर्घ flags;
	raw_spinlock_t *lock = lock_addr(v);
	s64 val;

	raw_spin_lock_irqsave(lock, flags);
	val = v->counter;
	अगर (val != u)
		v->counter += a;
	raw_spin_unlock_irqrestore(lock, flags);

	वापस val;
पूर्ण
EXPORT_SYMBOL(atomic64_fetch_add_unless);
