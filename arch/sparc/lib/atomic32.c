<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * atomic32.c: 32-bit atomic_t implementation
 *
 * Copyright (C) 2004 Keith M Wesolowski
 * Copyright (C) 2007 Kyle McMartin
 * 
 * Based on यंत्र-parisc/atomic.h Copyright (C) 2000 Philipp Rumpf
 */

#समावेश <linux/atomic.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>

#अगर_घोषित CONFIG_SMP
#घोषणा ATOMIC_HASH_SIZE	4
#घोषणा ATOMIC_HASH(a)	(&__atomic_hash[(((अचिन्हित दीर्घ)a)>>8) & (ATOMIC_HASH_SIZE-1)])

spinlock_t __atomic_hash[ATOMIC_HASH_SIZE] = अणु
	[0 ... (ATOMIC_HASH_SIZE-1)] = __SPIN_LOCK_UNLOCKED(__atomic_hash)
पूर्ण;

#अन्यथा /* SMP */

अटल DEFINE_SPINLOCK(dummy);
#घोषणा ATOMIC_HASH_SIZE	1
#घोषणा ATOMIC_HASH(a)		(&dummy)

#पूर्ण_अगर /* SMP */

#घोषणा ATOMIC_FETCH_OP(op, c_op)					\
पूर्णांक atomic_fetch_##op(पूर्णांक i, atomic_t *v)				\
अणु									\
	पूर्णांक ret;							\
	अचिन्हित दीर्घ flags;						\
	spin_lock_irqsave(ATOMIC_HASH(v), flags);			\
									\
	ret = v->counter;						\
	v->counter c_op i;						\
									\
	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);			\
	वापस ret;							\
पूर्ण									\
EXPORT_SYMBOL(atomic_fetch_##op);

#घोषणा ATOMIC_OP_RETURN(op, c_op)					\
पूर्णांक atomic_##op##_वापस(पूर्णांक i, atomic_t *v)				\
अणु									\
	पूर्णांक ret;							\
	अचिन्हित दीर्घ flags;						\
	spin_lock_irqsave(ATOMIC_HASH(v), flags);			\
									\
	ret = (v->counter c_op i);					\
									\
	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);			\
	वापस ret;							\
पूर्ण									\
EXPORT_SYMBOL(atomic_##op##_वापस);

ATOMIC_OP_RETURN(add, +=)

ATOMIC_FETCH_OP(add, +=)
ATOMIC_FETCH_OP(and, &=)
ATOMIC_FETCH_OP(or, |=)
ATOMIC_FETCH_OP(xor, ^=)

#अघोषित ATOMIC_FETCH_OP
#अघोषित ATOMIC_OP_RETURN

पूर्णांक atomic_xchg(atomic_t *v, पूर्णांक new)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ATOMIC_HASH(v), flags);
	ret = v->counter;
	v->counter = new;
	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(atomic_xchg);

पूर्णांक atomic_cmpxchg(atomic_t *v, पूर्णांक old, पूर्णांक new)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ATOMIC_HASH(v), flags);
	ret = v->counter;
	अगर (likely(ret == old))
		v->counter = new;

	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(atomic_cmpxchg);

पूर्णांक atomic_fetch_add_unless(atomic_t *v, पूर्णांक a, पूर्णांक u)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ATOMIC_HASH(v), flags);
	ret = v->counter;
	अगर (ret != u)
		v->counter += a;
	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(atomic_fetch_add_unless);

/* Atomic operations are alपढ़ोy serializing */
व्योम atomic_set(atomic_t *v, पूर्णांक i)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ATOMIC_HASH(v), flags);
	v->counter = i;
	spin_unlock_irqrestore(ATOMIC_HASH(v), flags);
पूर्ण
EXPORT_SYMBOL(atomic_set);

अचिन्हित दीर्घ ___set_bit(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ old, flags;

	spin_lock_irqsave(ATOMIC_HASH(addr), flags);
	old = *addr;
	*addr = old | mask;
	spin_unlock_irqrestore(ATOMIC_HASH(addr), flags);

	वापस old & mask;
पूर्ण
EXPORT_SYMBOL(___set_bit);

अचिन्हित दीर्घ ___clear_bit(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ old, flags;

	spin_lock_irqsave(ATOMIC_HASH(addr), flags);
	old = *addr;
	*addr = old & ~mask;
	spin_unlock_irqrestore(ATOMIC_HASH(addr), flags);

	वापस old & mask;
पूर्ण
EXPORT_SYMBOL(___clear_bit);

अचिन्हित दीर्घ ___change_bit(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ old, flags;

	spin_lock_irqsave(ATOMIC_HASH(addr), flags);
	old = *addr;
	*addr = old ^ mask;
	spin_unlock_irqrestore(ATOMIC_HASH(addr), flags);

	वापस old & mask;
पूर्ण
EXPORT_SYMBOL(___change_bit);

अचिन्हित दीर्घ __cmpxchg_u32(अस्थिर u32 *ptr, u32 old, u32 new)
अणु
	अचिन्हित दीर्घ flags;
	u32 prev;

	spin_lock_irqsave(ATOMIC_HASH(ptr), flags);
	अगर ((prev = *ptr) == old)
		*ptr = new;
	spin_unlock_irqrestore(ATOMIC_HASH(ptr), flags);

	वापस (अचिन्हित दीर्घ)prev;
पूर्ण
EXPORT_SYMBOL(__cmpxchg_u32);

u64 __cmpxchg_u64(u64 *ptr, u64 old, u64 new)
अणु
	अचिन्हित दीर्घ flags;
	u64 prev;

	spin_lock_irqsave(ATOMIC_HASH(ptr), flags);
	अगर ((prev = *ptr) == old)
		*ptr = new;
	spin_unlock_irqrestore(ATOMIC_HASH(ptr), flags);

	वापस prev;
पूर्ण
EXPORT_SYMBOL(__cmpxchg_u64);

अचिन्हित दीर्घ __xchg_u32(अस्थिर u32 *ptr, u32 new)
अणु
	अचिन्हित दीर्घ flags;
	u32 prev;

	spin_lock_irqsave(ATOMIC_HASH(ptr), flags);
	prev = *ptr;
	*ptr = new;
	spin_unlock_irqrestore(ATOMIC_HASH(ptr), flags);

	वापस (अचिन्हित दीर्घ)prev;
पूर्ण
EXPORT_SYMBOL(__xchg_u32);
