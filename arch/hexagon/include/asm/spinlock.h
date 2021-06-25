<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Spinlock support क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_SPINLOCK_H
#घोषणा _ASM_SPINLOCK_H

#समावेश <यंत्र/irqflags.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h>

/*
 * This file is pulled in क्रम SMP builds.
 * Really need to check all the barrier stuff क्रम "true" SMP
 */

/*
 * Read locks:
 * - load the lock value
 * - increment it
 * - अगर the lock value is still negative, go back and try again.
 * - unsuccessful store is unsuccessful.  Go back and try again.  Loser.
 * - successful store new lock value अगर positive -> lock acquired
 */
अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__(
		"1:	R6 = memw_locked(%0);\n"
		"	{ P3 = cmp.ge(R6,#0); R6 = add(R6,#1);}\n"
		"	{ if (!P3) jump 1b; }\n"
		"	memw_locked(%0,P3) = R6;\n"
		"	{ if (!P3) jump 1b; }\n"
		:
		: "r" (&lock->lock)
		: "memory", "r6", "p3"
	);

पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__(
		"1:	R6 = memw_locked(%0);\n"
		"	R6 = add(R6,#-1);\n"
		"	memw_locked(%0,P3) = R6\n"
		"	if (!P3) jump 1b;\n"
		:
		: "r" (&lock->lock)
		: "memory", "r6", "p3"
	);

पूर्ण

/*  I think this वापसs 0 on fail, 1 on success.  */
अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *lock)
अणु
	पूर्णांक temp;
	__यंत्र__ __अस्थिर__(
		"	R6 = memw_locked(%1);\n"
		"	{ %0 = #0; P3 = cmp.ge(R6,#0); R6 = add(R6,#1);}\n"
		"	{ if (!P3) jump 1f; }\n"
		"	memw_locked(%1,P3) = R6;\n"
		"	{ %0 = P3 }\n"
		"1:\n"
		: "=&r" (temp)
		: "r" (&lock->lock)
		: "memory", "r6", "p3"
	);
	वापस temp;
पूर्ण

/*  Stuffs a -1 in the lock value?  */
अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__(
		"1:	R6 = memw_locked(%0)\n"
		"	{ P3 = cmp.eq(R6,#0);  R6 = #-1;}\n"
		"	{ if (!P3) jump 1b; }\n"
		"	memw_locked(%0,P3) = R6;\n"
		"	{ if (!P3) jump 1b; }\n"
		:
		: "r" (&lock->lock)
		: "memory", "r6", "p3"
	);
पूर्ण


अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *lock)
अणु
	पूर्णांक temp;
	__यंत्र__ __अस्थिर__(
		"	R6 = memw_locked(%1)\n"
		"	{ %0 = #0; P3 = cmp.eq(R6,#0);  R6 = #-1;}\n"
		"	{ if (!P3) jump 1f; }\n"
		"	memw_locked(%1,P3) = R6;\n"
		"	%0 = P3;\n"
		"1:\n"
		: "=&r" (temp)
		: "r" (&lock->lock)
		: "memory", "r6", "p3"
	);
	वापस temp;

पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *lock)
अणु
	smp_mb();
	lock->lock = 0;
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__(
		"1:	R6 = memw_locked(%0);\n"
		"	P3 = cmp.eq(R6,#0);\n"
		"	{ if (!P3) jump 1b; R6 = #1; }\n"
		"	memw_locked(%0,P3) = R6;\n"
		"	{ if (!P3) jump 1b; }\n"
		:
		: "r" (&lock->lock)
		: "memory", "r6", "p3"
	);

पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	smp_mb();
	lock->lock = 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	पूर्णांक temp;
	__यंत्र__ __अस्थिर__(
		"	R6 = memw_locked(%1);\n"
		"	P3 = cmp.eq(R6,#0);\n"
		"	{ if (!P3) jump 1f; R6 = #1; %0 = #0; }\n"
		"	memw_locked(%1,P3) = R6;\n"
		"	%0 = P3;\n"
		"1:\n"
		: "=&r" (temp)
		: "r" (&lock->lock)
		: "memory", "r6", "p3"
	);
	वापस temp;
पूर्ण

/*
 * SMP spinlocks are पूर्णांकended to allow only a single CPU at the lock
 */
#घोषणा arch_spin_is_locked(x) ((x)->lock != 0)

#पूर्ण_अगर
