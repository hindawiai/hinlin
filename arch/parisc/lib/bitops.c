<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bitops.c: atomic operations which got too दीर्घ to be अंतरभूतd all over
 *      the place.
 * 
 * Copyright 1999 Philipp Rumpf (prumpf@tux.org)
 * Copyright 2000 Grant Grundler (grundler@cup.hp.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>

#अगर_घोषित CONFIG_SMP
arch_spinlock_t __atomic_hash[ATOMIC_HASH_SIZE] __lock_aligned = अणु
	[0 ... (ATOMIC_HASH_SIZE-1)]  = __ARCH_SPIN_LOCK_UNLOCKED
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
अचिन्हित दीर्घ __xchg64(अचिन्हित दीर्घ x, अस्थिर अचिन्हित दीर्घ *ptr)
अणु
	अचिन्हित दीर्घ temp, flags;

	_atomic_spin_lock_irqsave(ptr, flags);
	temp = *ptr;
	*ptr = x;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	वापस temp;
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ __xchg32(पूर्णांक x, अस्थिर पूर्णांक *ptr)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ temp;

	_atomic_spin_lock_irqsave(ptr, flags);
	temp = (दीर्घ) *ptr;	/* XXX - sign extension wanted? */
	*ptr = x;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	वापस (अचिन्हित दीर्घ)temp;
पूर्ण


अचिन्हित दीर्घ __xchg8(अक्षर x, अस्थिर अक्षर *ptr)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ temp;

	_atomic_spin_lock_irqsave(ptr, flags);
	temp = (दीर्घ) *ptr;	/* XXX - sign extension wanted? */
	*ptr = x;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	वापस (अचिन्हित दीर्घ)temp;
पूर्ण


u64 __cmpxchg_u64(अस्थिर u64 *ptr, u64 old, u64 new)
अणु
	अचिन्हित दीर्घ flags;
	u64 prev;

	_atomic_spin_lock_irqsave(ptr, flags);
	अगर ((prev = *ptr) == old)
		*ptr = new;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	वापस prev;
पूर्ण

अचिन्हित दीर्घ __cmpxchg_u32(अस्थिर अचिन्हित पूर्णांक *ptr, अचिन्हित पूर्णांक old, अचिन्हित पूर्णांक new)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक prev;

	_atomic_spin_lock_irqsave(ptr, flags);
	अगर ((prev = *ptr) == old)
		*ptr = new;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	वापस (अचिन्हित दीर्घ)prev;
पूर्ण

u8 __cmpxchg_u8(अस्थिर u8 *ptr, u8 old, u8 new)
अणु
	अचिन्हित दीर्घ flags;
	u8 prev;

	_atomic_spin_lock_irqsave(ptr, flags);
	अगर ((prev = *ptr) == old)
		*ptr = new;
	_atomic_spin_unlock_irqrestore(ptr, flags);
	वापस prev;
पूर्ण
