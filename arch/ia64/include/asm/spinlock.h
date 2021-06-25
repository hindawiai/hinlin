<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_SPINLOCK_H
#घोषणा _ASM_IA64_SPINLOCK_H

/*
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 *
 * This file is used क्रम SMP configurations only.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h>

#घोषणा arch_spin_lock_init(x)			((x)->lock = 0)

/*
 * Ticket locks are conceptually two parts, one indicating the current head of
 * the queue, and the other indicating the current tail. The lock is acquired
 * by atomically noting the tail and incrementing it by one (thus adding
 * ourself to the queue and noting our position), then रुकोing until the head
 * becomes equal to the the initial value of the tail.
 * The pad bits in the middle are used to prevent the next_ticket number
 * overflowing पूर्णांकo the now_serving number.
 *
 *   31             17  16    15  14                    0
 *  +----------------------------------------------------+
 *  |  now_serving     | padding |   next_ticket         |
 *  +----------------------------------------------------+
 */

#घोषणा TICKET_SHIFT	17
#घोषणा TICKET_BITS	15
#घोषणा	TICKET_MASK	((1 << TICKET_BITS) - 1)

अटल __always_अंतरभूत व्योम __ticket_spin_lock(arch_spinlock_t *lock)
अणु
	पूर्णांक	*p = (पूर्णांक *)&lock->lock, ticket, serve;

	ticket = ia64_fetchadd(1, p, acq);

	अगर (!(((ticket >> TICKET_SHIFT) ^ ticket) & TICKET_MASK))
		वापस;

	ia64_invala();

	क्रम (;;) अणु
		यंत्र अस्थिर ("ld4.c.nc %0=[%1]" : "=r"(serve) : "r"(p) : "memory");

		अगर (!(((serve >> TICKET_SHIFT) ^ ticket) & TICKET_MASK))
			वापस;
		cpu_relax();
	पूर्ण
पूर्ण

अटल __always_अंतरभूत पूर्णांक __ticket_spin_trylock(arch_spinlock_t *lock)
अणु
	पूर्णांक पंचांगp = READ_ONCE(lock->lock);

	अगर (!(((पंचांगp >> TICKET_SHIFT) ^ पंचांगp) & TICKET_MASK))
		वापस ia64_cmpxchg(acq, &lock->lock, पंचांगp, पंचांगp + 1, माप (पंचांगp)) == पंचांगp;
	वापस 0;
पूर्ण

अटल __always_अंतरभूत व्योम __ticket_spin_unlock(arch_spinlock_t *lock)
अणु
	अचिन्हित लघु	*p = (अचिन्हित लघु *)&lock->lock + 1, पंचांगp;

	/* This could be optimised with ARCH_HAS_MMIOWB */
	mmiowb();
	यंत्र अस्थिर ("ld2.bias %0=[%1]" : "=r"(पंचांगp) : "r"(p));
	WRITE_ONCE(*p, (पंचांगp + 2) & ~1);
पूर्ण

अटल अंतरभूत पूर्णांक __ticket_spin_is_locked(arch_spinlock_t *lock)
अणु
	दीर्घ पंचांगp = READ_ONCE(lock->lock);

	वापस !!(((पंचांगp >> TICKET_SHIFT) ^ पंचांगp) & TICKET_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक __ticket_spin_is_contended(arch_spinlock_t *lock)
अणु
	दीर्घ पंचांगp = READ_ONCE(lock->lock);

	वापस ((पंचांगp - (पंचांगp >> TICKET_SHIFT)) & TICKET_MASK) > 1;
पूर्ण

अटल __always_अंतरभूत पूर्णांक arch_spin_value_unlocked(arch_spinlock_t lock)
अणु
	वापस !(((lock.lock >> TICKET_SHIFT) ^ lock.lock) & TICKET_MASK);
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_is_locked(arch_spinlock_t *lock)
अणु
	वापस __ticket_spin_is_locked(lock);
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_is_contended(arch_spinlock_t *lock)
अणु
	वापस __ticket_spin_is_contended(lock);
पूर्ण
#घोषणा arch_spin_is_contended	arch_spin_is_contended

अटल __always_अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	__ticket_spin_lock(lock);
पूर्ण

अटल __always_अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	वापस __ticket_spin_trylock(lock);
पूर्ण

अटल __always_अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	__ticket_spin_unlock(lock);
पूर्ण

अटल __always_अंतरभूत व्योम arch_spin_lock_flags(arch_spinlock_t *lock,
						  अचिन्हित दीर्घ flags)
अणु
	arch_spin_lock(lock);
पूर्ण
#घोषणा arch_spin_lock_flags	arch_spin_lock_flags

#अगर_घोषित ASM_SUPPORTED

अटल __always_अंतरभूत व्योम
arch_पढ़ो_lock_flags(arch_rwlock_t *lock, अचिन्हित दीर्घ flags)
अणु
	__यंत्र__ __अस्थिर__ (
		"tbit.nz p6, p0 = %1,%2\n"
		"br.few 3f\n"
		"1:\n"
		"fetchadd4.rel r2 = [%0], -1;;\n"
		"(p6) ssm psr.i\n"
		"2:\n"
		"hint @pause\n"
		"ld4 r2 = [%0];;\n"
		"cmp4.lt p7,p0 = r2, r0\n"
		"(p7) br.cond.spnt.few 2b\n"
		"(p6) rsm psr.i\n"
		";;\n"
		"3:\n"
		"fetchadd4.acq r2 = [%0], 1;;\n"
		"cmp4.lt p7,p0 = r2, r0\n"
		"(p7) br.cond.spnt.few 1b\n"
		: : "r"(lock), "r"(flags), "i"(IA64_PSR_I_BIT)
		: "p6", "p7", "r2", "memory");
पूर्ण

#घोषणा arch_पढ़ो_lock_flags arch_पढ़ो_lock_flags
#घोषणा arch_पढ़ो_lock(lock) arch_पढ़ो_lock_flags(lock, 0)

#अन्यथा /* !ASM_SUPPORTED */

#घोषणा arch_पढ़ो_lock_flags(rw, flags) arch_पढ़ो_lock(rw)

#घोषणा arch_पढ़ो_lock(rw)								\
करो अणु											\
	arch_rwlock_t *__पढ़ो_lock_ptr = (rw);						\
											\
	जबतक (unlikely(ia64_fetchadd(1, (पूर्णांक *) __पढ़ो_lock_ptr, acq) < 0)) अणु		\
		ia64_fetchadd(-1, (पूर्णांक *) __पढ़ो_lock_ptr, rel);			\
		जबतक (*(अस्थिर पूर्णांक *)__पढ़ो_lock_ptr < 0)				\
			cpu_relax();							\
	पूर्ण										\
पूर्ण जबतक (0)

#पूर्ण_अगर /* !ASM_SUPPORTED */

#घोषणा arch_पढ़ो_unlock(rw)					\
करो अणु								\
	arch_rwlock_t *__पढ़ो_lock_ptr = (rw);			\
	ia64_fetchadd(-1, (पूर्णांक *) __पढ़ो_lock_ptr, rel);	\
पूर्ण जबतक (0)

#अगर_घोषित ASM_SUPPORTED

अटल __always_अंतरभूत व्योम
arch_ग_लिखो_lock_flags(arch_rwlock_t *lock, अचिन्हित दीर्घ flags)
अणु
	__यंत्र__ __अस्थिर__ (
		"tbit.nz p6, p0 = %1, %2\n"
		"mov ar.ccv = r0\n"
		"dep r29 = -1, r0, 31, 1\n"
		"br.few 3f;;\n"
		"1:\n"
		"(p6) ssm psr.i\n"
		"2:\n"
		"hint @pause\n"
		"ld4 r2 = [%0];;\n"
		"cmp4.eq p0,p7 = r0, r2\n"
		"(p7) br.cond.spnt.few 2b\n"
		"(p6) rsm psr.i\n"
		";;\n"
		"3:\n"
		"cmpxchg4.acq r2 = [%0], r29, ar.ccv;;\n"
		"cmp4.eq p0,p7 = r0, r2\n"
		"(p7) br.cond.spnt.few 1b;;\n"
		: : "r"(lock), "r"(flags), "i"(IA64_PSR_I_BIT)
		: "ar.ccv", "p6", "p7", "r2", "r29", "memory");
पूर्ण

#घोषणा arch_ग_लिखो_lock_flags arch_ग_लिखो_lock_flags
#घोषणा arch_ग_लिखो_lock(rw) arch_ग_लिखो_lock_flags(rw, 0)

#घोषणा arch_ग_लिखो_trylock(rw)							\
(अणु										\
	रेजिस्टर दीर्घ result;							\
										\
	__यंत्र__ __अस्थिर__ (							\
		"mov ar.ccv = r0\n"						\
		"dep r29 = -1, r0, 31, 1;;\n"					\
		"cmpxchg4.acq %0 = [%1], r29, ar.ccv\n"				\
		: "=r"(result) : "r"(rw) : "ar.ccv", "r29", "memory");		\
	(result == 0);								\
पूर्ण)

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *x)
अणु
	u8 *y = (u8 *)x;
	barrier();
	यंत्र अस्थिर ("st1.rel.nta [%0] = r0\n\t" :: "r"(y+3) : "memory" );
पूर्ण

#अन्यथा /* !ASM_SUPPORTED */

#घोषणा arch_ग_लिखो_lock(l)								\
(अणु											\
	__u64 ia64_val, ia64_set_val = ia64_dep_mi(-1, 0, 31, 1);			\
	__u32 *ia64_ग_लिखो_lock_ptr = (__u32 *) (l);					\
	करो अणु										\
		जबतक (*ia64_ग_लिखो_lock_ptr)						\
			ia64_barrier();							\
		ia64_val = ia64_cmpxchg4_acq(ia64_ग_लिखो_lock_ptr, ia64_set_val, 0);	\
	पूर्ण जबतक (ia64_val);								\
पूर्ण)

#घोषणा arch_ग_लिखो_trylock(rw)						\
(अणु									\
	__u64 ia64_val;							\
	__u64 ia64_set_val = ia64_dep_mi(-1, 0, 31,1);			\
	ia64_val = ia64_cmpxchg4_acq((__u32 *)(rw), ia64_set_val, 0);	\
	(ia64_val == 0);						\
पूर्ण)

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *x)
अणु
	barrier();
	x->ग_लिखो_lock = 0;
पूर्ण

#पूर्ण_अगर /* !ASM_SUPPORTED */

अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *x)
अणु
	जोड़ अणु
		arch_rwlock_t lock;
		__u32 word;
	पूर्ण old, new;
	old.lock = new.lock = *x;
	old.lock.ग_लिखो_lock = new.lock.ग_लिखो_lock = 0;
	++new.lock.पढ़ो_counter;
	वापस (u32)ia64_cmpxchg4_acq((__u32 *)(x), new.word, old.word) == old.word;
पूर्ण

#पूर्ण_अगर /*  _ASM_IA64_SPINLOCK_H */
