<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SPINLOCK_H
#घोषणा __LINUX_SPINLOCK_H

/*
 * include/linux/spinlock.h - generic spinlock/rwlock declarations
 *
 * here's the role of the various spinlock/rwlock related include files:
 *
 * on SMP builds:
 *
 *  यंत्र/spinlock_types.h: contains the arch_spinlock_t/arch_rwlock_t and the
 *                        initializers
 *
 *  linux/spinlock_types.h:
 *                        defines the generic type and initializers
 *
 *  यंत्र/spinlock.h:       contains the arch_spin_*()/etc. lowlevel
 *                        implementations, mostly अंतरभूत assembly code
 *
 *   (also included on UP-debug builds:)
 *
 *  linux/spinlock_api_smp.h:
 *                        contains the prototypes क्रम the _spin_*() APIs.
 *
 *  linux/spinlock.h:     builds the final spin_*() APIs.
 *
 * on UP builds:
 *
 *  linux/spinlock_type_up.h:
 *                        contains the generic, simplअगरied UP spinlock type.
 *                        (which is an empty काष्ठाure on non-debug builds)
 *
 *  linux/spinlock_types.h:
 *                        defines the generic type and initializers
 *
 *  linux/spinlock_up.h:
 *                        contains the arch_spin_*()/etc. version of UP
 *                        builds. (which are NOPs on non-debug, non-preempt
 *                        builds)
 *
 *   (included on UP-non-debug builds:)
 *
 *  linux/spinlock_api_up.h:
 *                        builds the _spin_*() APIs.
 *
 *  linux/spinlock.h:     builds the final spin_*() APIs.
 */

#समावेश <linux/typecheck.h>
#समावेश <linux/preempt.h>
#समावेश <linux/linkage.h>
#समावेश <linux/compiler.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/kernel.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/bottom_half.h>
#समावेश <linux/lockdep.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/mmiowb.h>


/*
 * Must define these beक्रमe including other files, अंतरभूत functions need them
 */
#घोषणा LOCK_SECTION_NAME ".text..lock."KBUILD_BASENAME

#घोषणा LOCK_SECTION_START(extra)               \
        ".subsection 1\n\t"                     \
        extra                                   \
        ".ifndef " LOCK_SECTION_NAME "\n\t"     \
        LOCK_SECTION_NAME ":\n\t"               \
        ".endif\n"

#घोषणा LOCK_SECTION_END                        \
        ".previous\n\t"

#घोषणा __lockfunc __section(".spinlock.text")

/*
 * Pull the arch_spinlock_t and arch_rwlock_t definitions:
 */
#समावेश <linux/spinlock_types.h>

/*
 * Pull the arch_spin*() functions/declarations (UP-nondebug करोesn't need them):
 */
#अगर_घोषित CONFIG_SMP
# include <यंत्र/spinlock.h>
#अन्यथा
# include <linux/spinlock_up.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
  बाह्य व्योम __raw_spin_lock_init(raw_spinlock_t *lock, स्थिर अक्षर *name,
				   काष्ठा lock_class_key *key, लघु inner);

# define raw_spin_lock_init(lock)					\
करो अणु									\
	अटल काष्ठा lock_class_key __key;				\
									\
	__raw_spin_lock_init((lock), #lock, &__key, LD_WAIT_SPIN);	\
पूर्ण जबतक (0)

#अन्यथा
# define raw_spin_lock_init(lock)				\
	करो अणु *(lock) = __RAW_SPIN_LOCK_UNLOCKED(lock); पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा raw_spin_is_locked(lock)	arch_spin_is_locked(&(lock)->raw_lock)

#अगर_घोषित arch_spin_is_contended
#घोषणा raw_spin_is_contended(lock)	arch_spin_is_contended(&(lock)->raw_lock)
#अन्यथा
#घोषणा raw_spin_is_contended(lock)	(((व्योम)(lock), 0))
#पूर्ण_अगर /*arch_spin_is_contended*/

/*
 * smp_mb__after_spinlock() provides the equivalent of a full memory barrier
 * between program-order earlier lock acquisitions and program-order later
 * memory accesses.
 *
 * This guarantees that the following two properties hold:
 *
 *   1) Given the snippet:
 *
 *	  अणु X = 0;  Y = 0; पूर्ण
 *
 *	  CPU0				CPU1
 *
 *	  WRITE_ONCE(X, 1);		WRITE_ONCE(Y, 1);
 *	  spin_lock(S);			smp_mb();
 *	  smp_mb__after_spinlock();	r1 = READ_ONCE(X);
 *	  r0 = READ_ONCE(Y);
 *	  spin_unlock(S);
 *
 *      it is क्रमbidden that CPU0 करोes not observe CPU1's store to Y (r0 = 0)
 *      and CPU1 करोes not observe CPU0's store to X (r1 = 0); see the comments
 *      preceding the call to smp_mb__after_spinlock() in __schedule() and in
 *      try_to_wake_up().
 *
 *   2) Given the snippet:
 *
 *  अणु X = 0;  Y = 0; पूर्ण
 *
 *  CPU0		CPU1				CPU2
 *
 *  spin_lock(S);	spin_lock(S);			r1 = READ_ONCE(Y);
 *  WRITE_ONCE(X, 1);	smp_mb__after_spinlock();	smp_rmb();
 *  spin_unlock(S);	r0 = READ_ONCE(X);		r2 = READ_ONCE(X);
 *			WRITE_ONCE(Y, 1);
 *			spin_unlock(S);
 *
 *      it is क्रमbidden that CPU0's critical section executes before CPU1's
 *      critical section (r0 = 1), CPU2 observes CPU1's store to Y (r1 = 1)
 *      and CPU2 करोes not observe CPU0's store to X (r2 = 0); see the comments
 *      preceding the calls to smp_rmb() in try_to_wake_up() क्रम similar
 *      snippets but "projected" onto two CPUs.
 *
 * Property (2) upgrades the lock to an RCsc lock.
 *
 * Since most load-store architectures implement ACQUIRE with an smp_mb() after
 * the LL/SC loop, they need no further barriers. Similarly all our TSO
 * architectures imply an smp_mb() क्रम each atomic inकाष्ठाion and equally करोn't
 * need more.
 *
 * Architectures that can implement ACQUIRE better need to take care.
 */
#अगर_अघोषित smp_mb__after_spinlock
#घोषणा smp_mb__after_spinlock()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_SPINLOCK
 बाह्य व्योम करो_raw_spin_lock(raw_spinlock_t *lock) __acquires(lock);
#घोषणा करो_raw_spin_lock_flags(lock, flags) करो_raw_spin_lock(lock)
 बाह्य पूर्णांक करो_raw_spin_trylock(raw_spinlock_t *lock);
 बाह्य व्योम करो_raw_spin_unlock(raw_spinlock_t *lock) __releases(lock);
#अन्यथा
अटल अंतरभूत व्योम करो_raw_spin_lock(raw_spinlock_t *lock) __acquires(lock)
अणु
	__acquire(lock);
	arch_spin_lock(&lock->raw_lock);
	mmiowb_spin_lock();
पूर्ण

#अगर_अघोषित arch_spin_lock_flags
#घोषणा arch_spin_lock_flags(lock, flags)	arch_spin_lock(lock)
#पूर्ण_अगर

अटल अंतरभूत व्योम
करो_raw_spin_lock_flags(raw_spinlock_t *lock, अचिन्हित दीर्घ *flags) __acquires(lock)
अणु
	__acquire(lock);
	arch_spin_lock_flags(&lock->raw_lock, *flags);
	mmiowb_spin_lock();
पूर्ण

अटल अंतरभूत पूर्णांक करो_raw_spin_trylock(raw_spinlock_t *lock)
अणु
	पूर्णांक ret = arch_spin_trylock(&(lock)->raw_lock);

	अगर (ret)
		mmiowb_spin_lock();

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम करो_raw_spin_unlock(raw_spinlock_t *lock) __releases(lock)
अणु
	mmiowb_spin_unlock();
	arch_spin_unlock(&lock->raw_lock);
	__release(lock);
पूर्ण
#पूर्ण_अगर

/*
 * Define the various spin_lock methods.  Note we define these
 * regardless of whether CONFIG_SMP or CONFIG_PREEMPTION are set. The
 * various methods are defined as nops in the हाल they are not
 * required.
 */
#घोषणा raw_spin_trylock(lock)	__cond_lock(lock, _raw_spin_trylock(lock))

#घोषणा raw_spin_lock(lock)	_raw_spin_lock(lock)

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# define raw_spin_lock_nested(lock, subclass) \
	_raw_spin_lock_nested(lock, subclass)

# define raw_spin_lock_nest_lock(lock, nest_lock)			\
	 करो अणु								\
		 typecheck(काष्ठा lockdep_map *, &(nest_lock)->dep_map);\
		 _raw_spin_lock_nest_lock(lock, &(nest_lock)->dep_map);	\
	 पूर्ण जबतक (0)
#अन्यथा
/*
 * Always evaluate the 'subclass' argument to aव्योम that the compiler
 * warns about set-but-not-used variables when building with
 * CONFIG_DEBUG_LOCK_ALLOC=n and with W=1.
 */
# define raw_spin_lock_nested(lock, subclass)		\
	_raw_spin_lock(((व्योम)(subclass), (lock)))
# define raw_spin_lock_nest_lock(lock, nest_lock)	_raw_spin_lock(lock)
#पूर्ण_अगर

#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)

#घोषणा raw_spin_lock_irqsave(lock, flags)			\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		flags = _raw_spin_lock_irqsave(lock);	\
	पूर्ण जबतक (0)

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
#घोषणा raw_spin_lock_irqsave_nested(lock, flags, subclass)		\
	करो अणु								\
		typecheck(अचिन्हित दीर्घ, flags);			\
		flags = _raw_spin_lock_irqsave_nested(lock, subclass);	\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा raw_spin_lock_irqsave_nested(lock, flags, subclass)		\
	करो अणु								\
		typecheck(अचिन्हित दीर्घ, flags);			\
		flags = _raw_spin_lock_irqsave(lock);			\
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अन्यथा

#घोषणा raw_spin_lock_irqsave(lock, flags)		\
	करो अणु						\
		typecheck(अचिन्हित दीर्घ, flags);	\
		_raw_spin_lock_irqsave(lock, flags);	\
	पूर्ण जबतक (0)

#घोषणा raw_spin_lock_irqsave_nested(lock, flags, subclass)	\
	raw_spin_lock_irqsave(lock, flags)

#पूर्ण_अगर

#घोषणा raw_spin_lock_irq(lock)		_raw_spin_lock_irq(lock)
#घोषणा raw_spin_lock_bh(lock)		_raw_spin_lock_bh(lock)
#घोषणा raw_spin_unlock(lock)		_raw_spin_unlock(lock)
#घोषणा raw_spin_unlock_irq(lock)	_raw_spin_unlock_irq(lock)

#घोषणा raw_spin_unlock_irqrestore(lock, flags)		\
	करो अणु							\
		typecheck(अचिन्हित दीर्घ, flags);		\
		_raw_spin_unlock_irqrestore(lock, flags);	\
	पूर्ण जबतक (0)
#घोषणा raw_spin_unlock_bh(lock)	_raw_spin_unlock_bh(lock)

#घोषणा raw_spin_trylock_bh(lock) \
	__cond_lock(lock, _raw_spin_trylock_bh(lock))

#घोषणा raw_spin_trylock_irq(lock) \
(अणु \
	local_irq_disable(); \
	raw_spin_trylock(lock) ? \
	1 : (अणु local_irq_enable(); 0;  पूर्ण); \
पूर्ण)

#घोषणा raw_spin_trylock_irqsave(lock, flags) \
(अणु \
	local_irq_save(flags); \
	raw_spin_trylock(lock) ? \
	1 : (अणु local_irq_restore(flags); 0; पूर्ण); \
पूर्ण)

/* Include rwlock functions */
#समावेश <linux/rwlock.h>

/*
 * Pull the _spin_*()/_पढ़ो_*()/_ग_लिखो_*() functions/declarations:
 */
#अगर defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINLOCK)
# include <linux/spinlock_api_smp.h>
#अन्यथा
# include <linux/spinlock_api_up.h>
#पूर्ण_अगर

/*
 * Map the spin_lock functions to the raw variants क्रम PREEMPT_RT=n
 */

अटल __always_अंतरभूत raw_spinlock_t *spinlock_check(spinlock_t *lock)
अणु
	वापस &lock->rlock;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_SPINLOCK

# define spin_lock_init(lock)					\
करो अणु								\
	अटल काष्ठा lock_class_key __key;			\
								\
	__raw_spin_lock_init(spinlock_check(lock),		\
			     #lock, &__key, LD_WAIT_CONFIG);	\
पूर्ण जबतक (0)

#अन्यथा

# define spin_lock_init(_lock)			\
करो अणु						\
	spinlock_check(_lock);			\
	*(_lock) = __SPIN_LOCK_UNLOCKED(_lock);	\
पूर्ण जबतक (0)

#पूर्ण_अगर

अटल __always_अंतरभूत व्योम spin_lock(spinlock_t *lock)
अणु
	raw_spin_lock(&lock->rlock);
पूर्ण

अटल __always_अंतरभूत व्योम spin_lock_bh(spinlock_t *lock)
अणु
	raw_spin_lock_bh(&lock->rlock);
पूर्ण

अटल __always_अंतरभूत पूर्णांक spin_trylock(spinlock_t *lock)
अणु
	वापस raw_spin_trylock(&lock->rlock);
पूर्ण

#घोषणा spin_lock_nested(lock, subclass)			\
करो अणु								\
	raw_spin_lock_nested(spinlock_check(lock), subclass);	\
पूर्ण जबतक (0)

#घोषणा spin_lock_nest_lock(lock, nest_lock)				\
करो अणु									\
	raw_spin_lock_nest_lock(spinlock_check(lock), nest_lock);	\
पूर्ण जबतक (0)

अटल __always_अंतरभूत व्योम spin_lock_irq(spinlock_t *lock)
अणु
	raw_spin_lock_irq(&lock->rlock);
पूर्ण

#घोषणा spin_lock_irqsave(lock, flags)				\
करो अणु								\
	raw_spin_lock_irqsave(spinlock_check(lock), flags);	\
पूर्ण जबतक (0)

#घोषणा spin_lock_irqsave_nested(lock, flags, subclass)			\
करो अणु									\
	raw_spin_lock_irqsave_nested(spinlock_check(lock), flags, subclass); \
पूर्ण जबतक (0)

अटल __always_अंतरभूत व्योम spin_unlock(spinlock_t *lock)
अणु
	raw_spin_unlock(&lock->rlock);
पूर्ण

अटल __always_अंतरभूत व्योम spin_unlock_bh(spinlock_t *lock)
अणु
	raw_spin_unlock_bh(&lock->rlock);
पूर्ण

अटल __always_अंतरभूत व्योम spin_unlock_irq(spinlock_t *lock)
अणु
	raw_spin_unlock_irq(&lock->rlock);
पूर्ण

अटल __always_अंतरभूत व्योम spin_unlock_irqrestore(spinlock_t *lock, अचिन्हित दीर्घ flags)
अणु
	raw_spin_unlock_irqrestore(&lock->rlock, flags);
पूर्ण

अटल __always_अंतरभूत पूर्णांक spin_trylock_bh(spinlock_t *lock)
अणु
	वापस raw_spin_trylock_bh(&lock->rlock);
पूर्ण

अटल __always_अंतरभूत पूर्णांक spin_trylock_irq(spinlock_t *lock)
अणु
	वापस raw_spin_trylock_irq(&lock->rlock);
पूर्ण

#घोषणा spin_trylock_irqsave(lock, flags)			\
(अणु								\
	raw_spin_trylock_irqsave(spinlock_check(lock), flags); \
पूर्ण)

/**
 * spin_is_locked() - Check whether a spinlock is locked.
 * @lock: Poपूर्णांकer to the spinlock.
 *
 * This function is NOT required to provide any memory ordering
 * guarantees; it could be used क्रम debugging purposes or, when
 * additional synchronization is needed, accompanied with other
 * स्थिरructs (memory barriers) enक्रमcing the synchronization.
 *
 * Returns: 1 अगर @lock is locked, 0 otherwise.
 *
 * Note that the function only tells you that the spinlock is
 * seen to be locked, not that it is locked on your CPU.
 *
 * Further, on CONFIG_SMP=n builds with CONFIG_DEBUG_SPINLOCK=n,
 * the वापस value is always 0 (see include/linux/spinlock_up.h).
 * Thereक्रमe you should not rely heavily on the वापस value.
 */
अटल __always_अंतरभूत पूर्णांक spin_is_locked(spinlock_t *lock)
अणु
	वापस raw_spin_is_locked(&lock->rlock);
पूर्ण

अटल __always_अंतरभूत पूर्णांक spin_is_contended(spinlock_t *lock)
अणु
	वापस raw_spin_is_contended(&lock->rlock);
पूर्ण

#घोषणा निश्चित_spin_locked(lock)	निश्चित_raw_spin_locked(&(lock)->rlock)

/*
 * Pull the atomic_t declaration:
 * (यंत्र-mips/atomic.h needs above definitions)
 */
#समावेश <linux/atomic.h>
/**
 * atomic_dec_and_lock - lock on reaching reference count zero
 * @atomic: the atomic counter
 * @lock: the spinlock in question
 *
 * Decrements @atomic by 1.  If the result is 0, वापसs true and locks
 * @lock.  Returns false क्रम all other हालs.
 */
बाह्य पूर्णांक _atomic_dec_and_lock(atomic_t *atomic, spinlock_t *lock);
#घोषणा atomic_dec_and_lock(atomic, lock) \
		__cond_lock(lock, _atomic_dec_and_lock(atomic, lock))

बाह्य पूर्णांक _atomic_dec_and_lock_irqsave(atomic_t *atomic, spinlock_t *lock,
					अचिन्हित दीर्घ *flags);
#घोषणा atomic_dec_and_lock_irqsave(atomic, lock, flags) \
		__cond_lock(lock, _atomic_dec_and_lock_irqsave(atomic, lock, &(flags)))

पूर्णांक __alloc_bucket_spinlocks(spinlock_t **locks, अचिन्हित पूर्णांक *lock_mask,
			     माप_प्रकार max_size, अचिन्हित पूर्णांक cpu_mult,
			     gfp_t gfp, स्थिर अक्षर *name,
			     काष्ठा lock_class_key *key);

#घोषणा alloc_bucket_spinlocks(locks, lock_mask, max_size, cpu_mult, gfp)    \
	(अणु								     \
		अटल काष्ठा lock_class_key key;			     \
		पूर्णांक ret;						     \
									     \
		ret = __alloc_bucket_spinlocks(locks, lock_mask, max_size,   \
					       cpu_mult, gfp, #locks, &key); \
		ret;							     \
	पूर्ण)

व्योम मुक्त_bucket_spinlocks(spinlock_t *locks);

#पूर्ण_अगर /* __LINUX_SPINLOCK_H */
