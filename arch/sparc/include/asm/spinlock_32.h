<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* spinlock.h: 32-bit Sparc spinlock support.
 *
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित __SPARC_SPINLOCK_H
#घोषणा __SPARC_SPINLOCK_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/psr.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h> /* क्रम cpu_relax */

#घोषणा arch_spin_is_locked(lock) (*((अस्थिर अचिन्हित अक्षर *)(lock)) != 0)

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__(
	"\n1:\n\t"
	"ldstub	[%0], %%g2\n\t"
	"orcc	%%g2, 0x0, %%g0\n\t"
	"bne,a	2f\n\t"
	" ldub	[%0], %%g2\n\t"
	".subsection	2\n"
	"2:\n\t"
	"orcc	%%g2, 0x0, %%g0\n\t"
	"bne,a	2b\n\t"
	" ldub	[%0], %%g2\n\t"
	"b,a	1b\n\t"
	".previous\n"
	: /* no outमाला_दो */
	: "r" (lock)
	: "g2", "memory", "cc");
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक result;
	__यंत्र__ __अस्थिर__("ldstub [%1], %0"
			     : "=r" (result)
			     : "r" (lock)
			     : "memory");
	वापस (result == 0);
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__("stb %%g0, [%0]" : : "r" (lock) : "memory");
पूर्ण

/* Read-ग_लिखो spinlocks, allowing multiple पढ़ोers
 * but only one ग_लिखोr.
 *
 * NOTE! it is quite common to have पढ़ोers in पूर्णांकerrupts
 * but no पूर्णांकerrupt ग_लिखोrs. For those circumstances we
 * can "mix" irq-safe locks - any ग_लिखोr needs to get a
 * irq-safe ग_लिखो-lock, but पढ़ोers can get non-irqsafe
 * पढ़ो-locks.
 *
 * XXX This might create some problems with my dual spinlock
 * XXX scheme, deadlocks etc. -DaveM
 *
 * Sort of like atomic_t's on Sparc, but even more clever.
 *
 *	------------------------------------
 *	| 24-bit counter           | wlock |  arch_rwlock_t
 *	------------------------------------
 *	 31                       8 7     0
 *
 * wlock signअगरies the one ग_लिखोr is in or somebody is updating
 * counter. For a ग_लिखोr, अगर he successfully acquires the wlock,
 * but counter is non-zero, he has to release the lock and रुको,
 * till both counter and wlock are zero.
 *
 * Unक्रमtunately this scheme limits us to ~16,000,000 cpus.
 */
अटल अंतरभूत व्योम __arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	रेजिस्टर arch_rwlock_t *lp यंत्र("g1");
	lp = rw;
	__यंत्र__ __अस्थिर__(
	"mov	%%o7, %%g4\n\t"
	"call	___rw_read_enter\n\t"
	" ldstub	[%%g1 + 3], %%g2\n"
	: /* no outमाला_दो */
	: "r" (lp)
	: "g2", "g4", "memory", "cc");
पूर्ण

#घोषणा arch_पढ़ो_lock(lock) \
करो अणु	अचिन्हित दीर्घ flags; \
	local_irq_save(flags); \
	__arch_पढ़ो_lock(lock); \
	local_irq_restore(flags); \
पूर्ण जबतक(0)

अटल अंतरभूत व्योम __arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	रेजिस्टर arch_rwlock_t *lp यंत्र("g1");
	lp = rw;
	__यंत्र__ __अस्थिर__(
	"mov	%%o7, %%g4\n\t"
	"call	___rw_read_exit\n\t"
	" ldstub	[%%g1 + 3], %%g2\n"
	: /* no outमाला_दो */
	: "r" (lp)
	: "g2", "g4", "memory", "cc");
पूर्ण

#घोषणा arch_पढ़ो_unlock(lock) \
करो अणु	अचिन्हित दीर्घ flags; \
	local_irq_save(flags); \
	__arch_पढ़ो_unlock(lock); \
	local_irq_restore(flags); \
पूर्ण जबतक(0)

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	रेजिस्टर arch_rwlock_t *lp यंत्र("g1");
	lp = rw;
	__यंत्र__ __अस्थिर__(
	"mov	%%o7, %%g4\n\t"
	"call	___rw_write_enter\n\t"
	" ldstub	[%%g1 + 3], %%g2\n"
	: /* no outमाला_दो */
	: "r" (lp)
	: "g2", "g4", "memory", "cc");
	*(अस्थिर __u32 *)&lp->lock = ~0U;
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *lock)
अणु
	__यंत्र__ __अस्थिर__(
"	st		%%g0, [%0]"
	: /* no outमाला_दो */
	: "r" (lock)
	: "memory");
पूर्ण

अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	अचिन्हित पूर्णांक val;

	__यंत्र__ __अस्थिर__("ldstub [%1 + 3], %0"
			     : "=r" (val)
			     : "r" (&rw->lock)
			     : "memory");

	अगर (val == 0) अणु
		val = rw->lock & ~0xff;
		अगर (val)
			((अस्थिर u8*)&rw->lock)[3] = 0;
		अन्यथा
			*(अस्थिर u32*)&rw->lock = ~0U;
	पूर्ण

	वापस (val == 0);
पूर्ण

अटल अंतरभूत पूर्णांक __arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	रेजिस्टर arch_rwlock_t *lp यंत्र("g1");
	रेजिस्टर पूर्णांक res यंत्र("o0");
	lp = rw;
	__यंत्र__ __अस्थिर__(
	"mov	%%o7, %%g4\n\t"
	"call	___rw_read_try\n\t"
	" ldstub	[%%g1 + 3], %%g2\n"
	: "=r" (res)
	: "r" (lp)
	: "g2", "g4", "memory", "cc");
	वापस res;
पूर्ण

#घोषणा arch_पढ़ो_trylock(lock) \
(अणु	अचिन्हित दीर्घ flags; \
	पूर्णांक res; \
	local_irq_save(flags); \
	res = __arch_पढ़ो_trylock(lock); \
	local_irq_restore(flags); \
	res; \
पूर्ण)

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* __SPARC_SPINLOCK_H */
