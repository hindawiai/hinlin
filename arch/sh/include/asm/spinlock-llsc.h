<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/spinlock-llsc.h
 *
 * Copyright (C) 2002, 2003 Paul Mundt
 * Copyright (C) 2006, 2007 Akio Idehara
 */
#अगर_अघोषित __ASM_SH_SPINLOCK_LLSC_H
#घोषणा __ASM_SH_SPINLOCK_LLSC_H

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h>

/*
 * Your basic SMP spinlocks, allowing only a single CPU anywhere
 */

#घोषणा arch_spin_is_locked(x)		((x)->lock <= 0)

/*
 * Simple spin lock operations.  There are two variants, one clears IRQ's
 * on the local processor, one करोes not.
 *
 * We make no fairness assumptions.  They have a cost.
 */
अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित दीर्घ oldval;

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%2, %0	! arch_spin_lock	\n\t"
		"mov		%0, %1				\n\t"
		"mov		#0, %0				\n\t"
		"movco.l	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"cmp/pl		%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (पंचांगp), "=&r" (oldval)
		: "r" (&lock->lock)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* This could be optimised with ARCH_HAS_MMIOWB */
	mmiowb();
	__यंत्र__ __अस्थिर__ (
		"mov		#1, %0 ! arch_spin_unlock	\n\t"
		"mov.l		%0, @%1				\n\t"
		: "=&z" (पंचांगp)
		: "r" (&lock->lock)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	अचिन्हित दीर्घ पंचांगp, oldval;

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%2, %0	! arch_spin_trylock	\n\t"
		"mov		%0, %1				\n\t"
		"mov		#0, %0				\n\t"
		"movco.l	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"synco						\n\t"
		: "=&z" (पंचांगp), "=&r" (oldval)
		: "r" (&lock->lock)
		: "t", "memory"
	);

	वापस oldval;
पूर्ण

/*
 * Read-ग_लिखो spinlocks, allowing multiple पढ़ोers but only one ग_लिखोr.
 *
 * NOTE! it is quite common to have पढ़ोers in पूर्णांकerrupts but no पूर्णांकerrupt
 * ग_लिखोrs. For those circumstances we can "mix" irq-safe locks - any ग_लिखोr
 * needs to get a irq-safe ग_लिखो-lock, but पढ़ोers can get non-irqsafe
 * पढ़ो-locks.
 */

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%1, %0	! arch_read_lock	\n\t"
		"cmp/pl		%0				\n\t"
		"bf		1b				\n\t"
		"add		#-1, %0				\n\t"
		"movco.l	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (पंचांगp)
		: "r" (&rw->lock)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%1, %0	! arch_read_unlock	\n\t"
		"add		#1, %0				\n\t"
		"movco.l	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (पंचांगp)
		: "r" (&rw->lock)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ पंचांगp;

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%1, %0	! arch_write_lock	\n\t"
		"cmp/hs		%2, %0				\n\t"
		"bf		1b				\n\t"
		"sub		%2, %0				\n\t"
		"movco.l	%0, @%1				\n\t"
		"bf		1b				\n\t"
		: "=&z" (पंचांगp)
		: "r" (&rw->lock), "r" (RW_LOCK_BIAS)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *rw)
अणु
	__यंत्र__ __अस्थिर__ (
		"mov.l		%1, @%0 ! arch_write_unlock	\n\t"
		:
		: "r" (&rw->lock), "r" (RW_LOCK_BIAS)
		: "t", "memory"
	);
पूर्ण

अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ पंचांगp, oldval;

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%2, %0	! arch_read_trylock	\n\t"
		"mov		%0, %1				\n\t"
		"cmp/pl		%0				\n\t"
		"bf		2f				\n\t"
		"add		#-1, %0				\n\t"
		"movco.l	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"2:						\n\t"
		"synco						\n\t"
		: "=&z" (पंचांगp), "=&r" (oldval)
		: "r" (&rw->lock)
		: "t", "memory"
	);

	वापस (oldval > 0);
पूर्ण

अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ पंचांगp, oldval;

	__यंत्र__ __अस्थिर__ (
		"1:						\n\t"
		"movli.l	@%2, %0	! arch_write_trylock	\n\t"
		"mov		%0, %1				\n\t"
		"cmp/hs		%3, %0				\n\t"
		"bf		2f				\n\t"
		"sub		%3, %0				\n\t"
		"2:						\n\t"
		"movco.l	%0, @%2				\n\t"
		"bf		1b				\n\t"
		"synco						\n\t"
		: "=&z" (पंचांगp), "=&r" (oldval)
		: "r" (&rw->lock), "r" (RW_LOCK_BIAS)
		: "t", "memory"
	);

	वापस (oldval > (RW_LOCK_BIAS - 1));
पूर्ण

#पूर्ण_अगर /* __ASM_SH_SPINLOCK_LLSC_H */
