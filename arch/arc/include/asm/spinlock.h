<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_SPINLOCK_H
#घोषणा __ASM_SPINLOCK_H

#समावेश <यंत्र/spinlock_types.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/barrier.h>

#घोषणा arch_spin_is_locked(x)	((x)->slock != __ARCH_SPIN_LOCK_UNLOCKED__)

#अगर_घोषित CONFIG_ARC_HAS_LLSC

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक val;

	__यंत्र__ __अस्थिर__(
	"1:	llock	%[val], [%[slock]]	\n"
	"	breq	%[val], %[LOCKED], 1b	\n"	/* spin जबतक LOCKED */
	"	scond	%[LOCKED], [%[slock]]	\n"	/* acquire */
	"	bnz	1b			\n"
	"					\n"
	: [val]		"=&r"	(val)
	: [slock]	"r"	(&(lock->slock)),
	  [LOCKED]	"r"	(__ARCH_SPIN_LOCK_LOCKED__)
	: "memory", "cc");

	/*
	 * ACQUIRE barrier to ensure load/store after taking the lock
	 * करोn't "bleed-up" out of the critical section (leak-in is allowed)
	 * http://www.spinics.net/lists/kernel/msg2010409.hपंचांगl
	 *
	 * ARCv2 only has load-load, store-store and all-all barrier
	 * thus need the full all-all barrier
	 */
	smp_mb();
पूर्ण

/* 1 - lock taken successfully */
अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक val, got_it = 0;

	__यंत्र__ __अस्थिर__(
	"1:	llock	%[val], [%[slock]]	\n"
	"	breq	%[val], %[LOCKED], 4f	\n"	/* alपढ़ोy LOCKED, just bail */
	"	scond	%[LOCKED], [%[slock]]	\n"	/* acquire */
	"	bnz	1b			\n"
	"	mov	%[got_it], 1		\n"
	"4:					\n"
	"					\n"
	: [val]		"=&r"	(val),
	  [got_it]	"+&r"	(got_it)
	: [slock]	"r"	(&(lock->slock)),
	  [LOCKED]	"r"	(__ARCH_SPIN_LOCK_LOCKED__)
	: "memory", "cc");

	smp_mb();

	वापस got_it;
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	smp_mb();

	WRITE_ONCE(lock->slock, __ARCH_SPIN_LOCK_UNLOCKED__);
पूर्ण

/*
 * Read-ग_लिखो spinlocks, allowing multiple पढ़ोers but only one ग_लिखोr.
 * Unfair locking as Writers could be starved indefinitely by Reader(s)
 */

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	अचिन्हित पूर्णांक val;

	/*
	 * zero means ग_लिखोr holds the lock exclusively, deny Reader.
	 * Otherwise grant lock to first/subseq पढ़ोer
	 *
	 * 	अगर (rw->counter > 0) अणु
	 *		rw->counter--;
	 *		ret = 1;
	 *	पूर्ण
	 */

	__यंत्र__ __अस्थिर__(
	"1:	llock	%[val], [%[rwlock]]	\n"
	"	brls	%[val], %[WR_LOCKED], 1b\n"	/* <= 0: spin जबतक ग_लिखो locked */
	"	sub	%[val], %[val], 1	\n"	/* पढ़ोer lock */
	"	scond	%[val], [%[rwlock]]	\n"
	"	bnz	1b			\n"
	"					\n"
	: [val]		"=&r"	(val)
	: [rwlock]	"r"	(&(rw->counter)),
	  [WR_LOCKED]	"ir"	(0)
	: "memory", "cc");

	smp_mb();
पूर्ण

/* 1 - lock taken successfully */
अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	अचिन्हित पूर्णांक val, got_it = 0;

	__यंत्र__ __अस्थिर__(
	"1:	llock	%[val], [%[rwlock]]	\n"
	"	brls	%[val], %[WR_LOCKED], 4f\n"	/* <= 0: alपढ़ोy ग_लिखो locked, bail */
	"	sub	%[val], %[val], 1	\n"	/* counter-- */
	"	scond	%[val], [%[rwlock]]	\n"
	"	bnz	1b			\n"	/* retry अगर collided with someone */
	"	mov	%[got_it], 1		\n"
	"					\n"
	"4: ; --- done ---			\n"

	: [val]		"=&r"	(val),
	  [got_it]	"+&r"	(got_it)
	: [rwlock]	"r"	(&(rw->counter)),
	  [WR_LOCKED]	"ir"	(0)
	: "memory", "cc");

	smp_mb();

	वापस got_it;
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	अचिन्हित पूर्णांक val;

	/*
	 * If पढ़ोer(s) hold lock (lock < __ARCH_RW_LOCK_UNLOCKED__),
	 * deny ग_लिखोr. Otherwise अगर unlocked grant to ग_लिखोr
	 * Hence the claim that Linux rwlocks are unfair to ग_लिखोrs.
	 * (can be starved क्रम an indefinite समय by पढ़ोers).
	 *
	 *	अगर (rw->counter == __ARCH_RW_LOCK_UNLOCKED__) अणु
	 *		rw->counter = 0;
	 *		ret = 1;
	 *	पूर्ण
	 */

	__यंत्र__ __अस्थिर__(
	"1:	llock	%[val], [%[rwlock]]	\n"
	"	brne	%[val], %[UNLOCKED], 1b	\n"	/* जबतक !UNLOCKED spin */
	"	mov	%[val], %[WR_LOCKED]	\n"
	"	scond	%[val], [%[rwlock]]	\n"
	"	bnz	1b			\n"
	"					\n"
	: [val]		"=&r"	(val)
	: [rwlock]	"r"	(&(rw->counter)),
	  [UNLOCKED]	"ir"	(__ARCH_RW_LOCK_UNLOCKED__),
	  [WR_LOCKED]	"ir"	(0)
	: "memory", "cc");

	smp_mb();
पूर्ण

/* 1 - lock taken successfully */
अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	अचिन्हित पूर्णांक val, got_it = 0;

	__यंत्र__ __अस्थिर__(
	"1:	llock	%[val], [%[rwlock]]	\n"
	"	brne	%[val], %[UNLOCKED], 4f	\n"	/* !UNLOCKED, bail */
	"	mov	%[val], %[WR_LOCKED]	\n"
	"	scond	%[val], [%[rwlock]]	\n"
	"	bnz	1b			\n"	/* retry अगर collided with someone */
	"	mov	%[got_it], 1		\n"
	"					\n"
	"4: ; --- done ---			\n"

	: [val]		"=&r"	(val),
	  [got_it]	"+&r"	(got_it)
	: [rwlock]	"r"	(&(rw->counter)),
	  [UNLOCKED]	"ir"	(__ARCH_RW_LOCK_UNLOCKED__),
	  [WR_LOCKED]	"ir"	(0)
	: "memory", "cc");

	smp_mb();

	वापस got_it;
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	अचिन्हित पूर्णांक val;

	smp_mb();

	/*
	 * rw->counter++;
	 */
	__यंत्र__ __अस्थिर__(
	"1:	llock	%[val], [%[rwlock]]	\n"
	"	add	%[val], %[val], 1	\n"
	"	scond	%[val], [%[rwlock]]	\n"
	"	bnz	1b			\n"
	"					\n"
	: [val]		"=&r"	(val)
	: [rwlock]	"r"	(&(rw->counter))
	: "memory", "cc");
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *rw)
अणु
	smp_mb();

	WRITE_ONCE(rw->counter, __ARCH_RW_LOCK_UNLOCKED__);
पूर्ण

#अन्यथा	/* !CONFIG_ARC_HAS_LLSC */

अटल अंतरभूत व्योम arch_spin_lock(arch_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक val = __ARCH_SPIN_LOCK_LOCKED__;

	/*
	 * Per lkmm, smp_mb() is only required after _lock (and beक्रमe_unlock)
	 * क्रम ACQ and REL semantics respectively. However EX based spinlocks
	 * need the extra smp_mb to workaround a hardware quirk.
	 */
	smp_mb();

	__यंत्र__ __अस्थिर__(
	"1:	ex  %0, [%1]		\n"
	"	breq  %0, %2, 1b	\n"
	: "+&r" (val)
	: "r"(&(lock->slock)), "ir"(__ARCH_SPIN_LOCK_LOCKED__)
	: "memory");

	smp_mb();
पूर्ण

/* 1 - lock taken successfully */
अटल अंतरभूत पूर्णांक arch_spin_trylock(arch_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक val = __ARCH_SPIN_LOCK_LOCKED__;

	smp_mb();

	__यंत्र__ __अस्थिर__(
	"1:	ex  %0, [%1]		\n"
	: "+r" (val)
	: "r"(&(lock->slock))
	: "memory");

	smp_mb();

	वापस (val == __ARCH_SPIN_LOCK_UNLOCKED__);
पूर्ण

अटल अंतरभूत व्योम arch_spin_unlock(arch_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक val = __ARCH_SPIN_LOCK_UNLOCKED__;

	/*
	 * RELEASE barrier: given the inकाष्ठाions avail on ARCv2, full barrier
	 * is the only option
	 */
	smp_mb();

	/*
	 * EX is not really required here, a simple STore of 0 suffices.
	 * However this causes tasklist livelocks in SystemC based SMP भव
	 * platक्रमms where the प्रणालीc core scheduler uses EX as a cue क्रम
	 * moving to next core. Do a git log of this file क्रम details
	 */
	__यंत्र__ __अस्थिर__(
	"	ex  %0, [%1]		\n"
	: "+r" (val)
	: "r"(&(lock->slock))
	: "memory");

	/*
	 * see pairing version/comment in arch_spin_lock above
	 */
	smp_mb();
पूर्ण

/*
 * Read-ग_लिखो spinlocks, allowing multiple पढ़ोers but only one ग_लिखोr.
 * Unfair locking as Writers could be starved indefinitely by Reader(s)
 *
 * The spinlock itself is contained in @counter and access to it is
 * serialized with @lock_mutex.
 */

/* 1 - lock taken successfully */
अटल अंतरभूत पूर्णांक arch_पढ़ो_trylock(arch_rwlock_t *rw)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&(rw->lock_mutex));

	/*
	 * zero means ग_लिखोr holds the lock exclusively, deny Reader.
	 * Otherwise grant lock to first/subseq पढ़ोer
	 */
	अगर (rw->counter > 0) अणु
		rw->counter--;
		ret = 1;
	पूर्ण

	arch_spin_unlock(&(rw->lock_mutex));
	local_irq_restore(flags);

	वापस ret;
पूर्ण

/* 1 - lock taken successfully */
अटल अंतरभूत पूर्णांक arch_ग_लिखो_trylock(arch_rwlock_t *rw)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&(rw->lock_mutex));

	/*
	 * If पढ़ोer(s) hold lock (lock < __ARCH_RW_LOCK_UNLOCKED__),
	 * deny ग_लिखोr. Otherwise अगर unlocked grant to ग_लिखोr
	 * Hence the claim that Linux rwlocks are unfair to ग_लिखोrs.
	 * (can be starved क्रम an indefinite समय by पढ़ोers).
	 */
	अगर (rw->counter == __ARCH_RW_LOCK_UNLOCKED__) अणु
		rw->counter = 0;
		ret = 1;
	पूर्ण
	arch_spin_unlock(&(rw->lock_mutex));
	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_lock(arch_rwlock_t *rw)
अणु
	जबतक (!arch_पढ़ो_trylock(rw))
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_lock(arch_rwlock_t *rw)
अणु
	जबतक (!arch_ग_लिखो_trylock(rw))
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम arch_पढ़ो_unlock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&(rw->lock_mutex));
	rw->counter++;
	arch_spin_unlock(&(rw->lock_mutex));
	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम arch_ग_लिखो_unlock(arch_rwlock_t *rw)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	arch_spin_lock(&(rw->lock_mutex));
	rw->counter = __ARCH_RW_LOCK_UNLOCKED__;
	arch_spin_unlock(&(rw->lock_mutex));
	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SPINLOCK_H */
