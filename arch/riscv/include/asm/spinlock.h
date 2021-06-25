<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 */

#अगर_अघोषित _ASM_RISCV_SPINLOCK_H
#घोषणा _ASM_RISCV_SPINLOCK_H

#समावेश <linux/kernel.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/fence.h>

/*
 * Simple spin lock operations.  These provide no fairness guarantees.
 */

/* FIXME: Replace this with a ticket lock, like MIPS. */

#घोषणा arch_spin_is_locked(x)	(READ_ONCE((x)->lock) != 0)

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	smp_store_release(&lock->lock, 0);
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	पूर्णांक पंचांगp = 1, busy;

	__यंत्र__ __अस्थिर__ (
		"	amoswap.w %0, %2, %1\n"
		RISCV_ACQUIRE_BARRIER
		: "=r" (busy), "+A" (lock->lock)
		: "r" (पंचांगp)
		: "memory");

	वापस !busy;
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	जबतक (1) अणु
		अगर (arch_spin_is_locked(lock))
			जारी;

		अगर (arch_spin_trylock(lock))
			अवरोध;
	पूर्ण
पूर्ण

/***********************************************************/

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *lock)
अणु
	पूर्णांक पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	lr.w	%1, %0\n"
		"	bltz	%1, 1b\n"
		"	addi	%1, %1, 1\n"
		"	sc.w	%1, %1, %0\n"
		"	bnez	%1, 1b\n"
		RISCV_ACQUIRE_BARRIER
		: "+A" (lock->lock), "=&r" (पंचांगp)
		:: "memory");
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *lock)
अणु
	पूर्णांक पंचांगp;

	__यंत्र__ __अस्थिर__(
		"1:	lr.w	%1, %0\n"
		"	bnez	%1, 1b\n"
		"	li	%1, -1\n"
		"	sc.w	%1, %1, %0\n"
		"	bnez	%1, 1b\n"
		RISCV_ACQUIRE_BARRIER
		: "+A" (lock->lock), "=&r" (पंचांगp)
		:: "memory");
पूर्ण

अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *lock)
अणु
	पूर्णांक busy;

	__यंत्र__ __अस्थिर__(
		"1:	lr.w	%1, %0\n"
		"	bltz	%1, 1f\n"
		"	addi	%1, %1, 1\n"
		"	sc.w	%1, %1, %0\n"
		"	bnez	%1, 1b\n"
		RISCV_ACQUIRE_BARRIER
		"1:\n"
		: "+A" (lock->lock), "=&r" (busy)
		:: "memory");

	वापस !busy;
पूर्ण

अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *lock)
अणु
	पूर्णांक busy;

	__यंत्र__ __अस्थिर__(
		"1:	lr.w	%1, %0\n"
		"	bnez	%1, 1f\n"
		"	li	%1, -1\n"
		"	sc.w	%1, %1, %0\n"
		"	bnez	%1, 1b\n"
		RISCV_ACQUIRE_BARRIER
		"1:\n"
		: "+A" (lock->lock), "=&r" (busy)
		:: "memory");

	वापस !busy;
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__(
		RISCV_RELEASE_BARRIER
		"	amoadd.w x0, %1, %0\n"
		: "+A" (lock->lock)
		: "r" (-1)
		: "memory");
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *lock)
अणु
	smp_store_release(&lock->lock, 0);
पूर्ण

#पूर्ण_अगर /* _ASM_RISCV_SPINLOCK_H */
