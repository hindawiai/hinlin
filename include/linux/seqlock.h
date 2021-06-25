<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SEQLOCK_H
#घोषणा __LINUX_SEQLOCK_H

/*
 * seqcount_t / seqlock_t - a पढ़ोer-ग_लिखोr consistency mechanism with
 * lockless पढ़ोers (पढ़ो-only retry loops), and no ग_लिखोr starvation.
 *
 * See Documentation/locking/seqlock.rst
 *
 * Copyrights:
 * - Based on x86_64 vsyscall समय_लोofday: Keith Owens, Andrea Arcangeli
 * - Sequence counters with associated locks, (C) 2020 Linutronix GmbH
 */

#समावेश <linux/compiler.h>
#समावेश <linux/kcsan-checks.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ww_mutex.h>
#समावेश <linux/preempt.h>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/processor.h>

/*
 * The seqlock seqcount_t पूर्णांकerface करोes not prescribe a precise sequence of
 * पढ़ो begin/retry/end. For पढ़ोers, typically there is a call to
 * पढ़ो_seqcount_begin() and पढ़ो_seqcount_retry(), however, there are more
 * esoteric हालs which करो not follow this pattern.
 *
 * As a consequence, we take the following best-efक्रमt approach क्रम raw usage
 * via seqcount_t under KCSAN: upon beginning a seq-पढ़ोer critical section,
 * pessimistically mark the next KCSAN_SEQLOCK_REGION_MAX memory accesses as
 * atomics; अगर there is a matching पढ़ो_seqcount_retry() call, no following
 * memory operations are considered atomic. Usage of the seqlock_t पूर्णांकerface
 * is not affected.
 */
#घोषणा KCSAN_SEQLOCK_REGION_MAX 1000

/*
 * Sequence counters (seqcount_t)
 *
 * This is the raw counting mechanism, without any ग_लिखोr protection.
 *
 * Write side critical sections must be serialized and non-preemptible.
 *
 * If पढ़ोers can be invoked from hardirq or softirq contexts,
 * पूर्णांकerrupts or bottom halves must also be respectively disabled beक्रमe
 * entering the ग_लिखो section.
 *
 * This mechanism can't be used अगर the रक्षित data contains poपूर्णांकers,
 * as the ग_लिखोr can invalidate a poपूर्णांकer that a पढ़ोer is following.
 *
 * If the ग_लिखो serialization mechanism is one of the common kernel
 * locking primitives, use a sequence counter with associated lock
 * (seqcount_LOCKNAME_t) instead.
 *
 * If it's desired to स्वतःmatically handle the sequence counter ग_लिखोr
 * serialization and non-preemptibility requirements, use a sequential
 * lock (seqlock_t) instead.
 *
 * See Documentation/locking/seqlock.rst
 */
प्रकार काष्ठा seqcount अणु
	अचिन्हित sequence;
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map dep_map;
#पूर्ण_अगर
पूर्ण seqcount_t;

अटल अंतरभूत व्योम __seqcount_init(seqcount_t *s, स्थिर अक्षर *name,
					  काष्ठा lock_class_key *key)
अणु
	/*
	 * Make sure we are not reinitializing a held lock:
	 */
	lockdep_init_map(&s->dep_map, name, key, 0);
	s->sequence = 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

# define SEQCOUNT_DEP_MAP_INIT(lockname)				\
		.dep_map = अणु .name = #lockname पूर्ण

/**
 * seqcount_init() - runसमय initializer क्रम seqcount_t
 * @s: Poपूर्णांकer to the seqcount_t instance
 */
# define seqcount_init(s)						\
	करो अणु								\
		अटल काष्ठा lock_class_key __key;			\
		__seqcount_init((s), #s, &__key);			\
	पूर्ण जबतक (0)

अटल अंतरभूत व्योम seqcount_lockdep_पढ़ोer_access(स्थिर seqcount_t *s)
अणु
	seqcount_t *l = (seqcount_t *)s;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	seqcount_acquire_पढ़ो(&l->dep_map, 0, 0, _RET_IP_);
	seqcount_release(&l->dep_map, _RET_IP_);
	local_irq_restore(flags);
पूर्ण

#अन्यथा
# define SEQCOUNT_DEP_MAP_INIT(lockname)
# define seqcount_init(s) __seqcount_init(s, शून्य, शून्य)
# define seqcount_lockdep_पढ़ोer_access(x)
#पूर्ण_अगर

/**
 * SEQCNT_ZERO() - अटल initializer क्रम seqcount_t
 * @name: Name of the seqcount_t instance
 */
#घोषणा SEQCNT_ZERO(name) अणु .sequence = 0, SEQCOUNT_DEP_MAP_INIT(name) पूर्ण

/*
 * Sequence counters with associated locks (seqcount_LOCKNAME_t)
 *
 * A sequence counter which associates the lock used क्रम ग_लिखोr
 * serialization at initialization समय. This enables lockdep to validate
 * that the ग_लिखो side critical section is properly serialized.
 *
 * For associated locks which करो not implicitly disable preemption,
 * preemption protection is enक्रमced in the ग_लिखो side function.
 *
 * Lockdep is never used in any क्रम the raw ग_लिखो variants.
 *
 * See Documentation/locking/seqlock.rst
 */

/*
 * For PREEMPT_RT, seqcount_LOCKNAME_t ग_लिखो side critical sections cannot
 * disable preemption. It can lead to higher latencies, and the ग_लिखो side
 * sections will not be able to acquire locks which become sleeping locks
 * (e.g. spinlock_t).
 *
 * To reमुख्य preemptible जबतक aव्योमing a possible livelock caused by the
 * पढ़ोer preempting the ग_लिखोr, use a dअगरferent technique: let the पढ़ोer
 * detect अगर a seqcount_LOCKNAME_t ग_लिखोr is in progress. If that is the
 * हाल, acquire then release the associated LOCKNAME ग_लिखोr serialization
 * lock. This will allow any possibly-preempted ग_लिखोr to make progress
 * until the end of its ग_लिखोr serialization lock critical section.
 *
 * This lock-unlock technique must be implemented क्रम all of PREEMPT_RT
 * sleeping locks.  See Documentation/locking/locktypes.rst
 */
#अगर defined(CONFIG_LOCKDEP) || defined(CONFIG_PREEMPT_RT)
#घोषणा __SEQ_LOCK(expr)	expr
#अन्यथा
#घोषणा __SEQ_LOCK(expr)
#पूर्ण_अगर

/*
 * प्रकार seqcount_LOCKNAME_t - sequence counter with LOCKNAME associated
 * @seqcount:	The real sequence counter
 * @lock:	Poपूर्णांकer to the associated lock
 *
 * A plain sequence counter with बाह्यal ग_लिखोr synchronization by
 * LOCKNAME @lock. The lock is associated to the sequence counter in the
 * अटल initializer or init function. This enables lockdep to validate
 * that the ग_लिखो side critical section is properly serialized.
 *
 * LOCKNAME:	raw_spinlock, spinlock, rwlock, mutex, or ww_mutex.
 */

/*
 * seqcount_LOCKNAME_init() - runसमय initializer क्रम seqcount_LOCKNAME_t
 * @s:		Poपूर्णांकer to the seqcount_LOCKNAME_t instance
 * @lock:	Poपूर्णांकer to the associated lock
 */

#घोषणा seqcount_LOCKNAME_init(s, _lock, lockname)			\
	करो अणु								\
		seqcount_##lockname##_t *____s = (s);			\
		seqcount_init(&____s->seqcount);			\
		__SEQ_LOCK(____s->lock = (_lock));			\
	पूर्ण जबतक (0)

#घोषणा seqcount_raw_spinlock_init(s, lock)	seqcount_LOCKNAME_init(s, lock, raw_spinlock)
#घोषणा seqcount_spinlock_init(s, lock)		seqcount_LOCKNAME_init(s, lock, spinlock)
#घोषणा seqcount_rwlock_init(s, lock)		seqcount_LOCKNAME_init(s, lock, rwlock);
#घोषणा seqcount_mutex_init(s, lock)		seqcount_LOCKNAME_init(s, lock, mutex);
#घोषणा seqcount_ww_mutex_init(s, lock)		seqcount_LOCKNAME_init(s, lock, ww_mutex);

/*
 * SEQCOUNT_LOCKNAME()	- Instantiate seqcount_LOCKNAME_t and helpers
 * seqprop_LOCKNAME_*()	- Property accessors क्रम seqcount_LOCKNAME_t
 *
 * @lockname:		"LOCKNAME" part of seqcount_LOCKNAME_t
 * @locktype:		LOCKNAME canonical C data type
 * @preemptible:	preemptibility of above locktype
 * @lockmember:		argument क्रम lockdep_निश्चित_held()
 * @lockbase:		associated lock release function (prefix only)
 * @lock_acquire:	associated lock acquisition function (full call)
 */
#घोषणा SEQCOUNT_LOCKNAME(lockname, locktype, preemptible, lockmember, lockbase, lock_acquire) \
प्रकार काष्ठा seqcount_##lockname अणु					\
	seqcount_t		seqcount;				\
	__SEQ_LOCK(locktype	*lock);					\
पूर्ण seqcount_##lockname##_t;						\
									\
अटल __always_अंतरभूत seqcount_t *					\
__seqprop_##lockname##_ptr(seqcount_##lockname##_t *s)			\
अणु									\
	वापस &s->seqcount;						\
पूर्ण									\
									\
अटल __always_अंतरभूत अचिन्हित						\
__seqprop_##lockname##_sequence(स्थिर seqcount_##lockname##_t *s)	\
अणु									\
	अचिन्हित seq = READ_ONCE(s->seqcount.sequence);			\
									\
	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT))				\
		वापस seq;						\
									\
	अगर (preemptible && unlikely(seq & 1)) अणु				\
		__SEQ_LOCK(lock_acquire);				\
		__SEQ_LOCK(lockbase##_unlock(s->lock));			\
									\
		/*							\
		 * Re-पढ़ो the sequence counter since the (possibly	\
		 * preempted) ग_लिखोr made progress.			\
		 */							\
		seq = READ_ONCE(s->seqcount.sequence);			\
	पूर्ण								\
									\
	वापस seq;							\
पूर्ण									\
									\
अटल __always_अंतरभूत bool						\
__seqprop_##lockname##_preemptible(स्थिर seqcount_##lockname##_t *s)	\
अणु									\
	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT))				\
		वापस preemptible;					\
									\
	/* PREEMPT_RT relies on the above LOCK+UNLOCK */		\
	वापस false;							\
पूर्ण									\
									\
अटल __always_अंतरभूत व्योम						\
__seqprop_##lockname##_निश्चित(स्थिर seqcount_##lockname##_t *s)		\
अणु									\
	__SEQ_LOCK(lockdep_निश्चित_held(lockmember));			\
पूर्ण

/*
 * __seqprop() क्रम seqcount_t
 */

अटल अंतरभूत seqcount_t *__seqprop_ptr(seqcount_t *s)
अणु
	वापस s;
पूर्ण

अटल अंतरभूत अचिन्हित __seqprop_sequence(स्थिर seqcount_t *s)
अणु
	वापस READ_ONCE(s->sequence);
पूर्ण

अटल अंतरभूत bool __seqprop_preemptible(स्थिर seqcount_t *s)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम __seqprop_निश्चित(स्थिर seqcount_t *s)
अणु
	lockdep_निश्चित_preemption_disabled();
पूर्ण

#घोषणा __SEQ_RT	IS_ENABLED(CONFIG_PREEMPT_RT)

SEQCOUNT_LOCKNAME(raw_spinlock, raw_spinlock_t,  false,    s->lock,        raw_spin, raw_spin_lock(s->lock))
SEQCOUNT_LOCKNAME(spinlock,     spinlock_t,      __SEQ_RT, s->lock,        spin,     spin_lock(s->lock))
SEQCOUNT_LOCKNAME(rwlock,       rwlock_t,        __SEQ_RT, s->lock,        पढ़ो,     पढ़ो_lock(s->lock))
SEQCOUNT_LOCKNAME(mutex,        काष्ठा mutex,    true,     s->lock,        mutex,    mutex_lock(s->lock))
SEQCOUNT_LOCKNAME(ww_mutex,     काष्ठा ww_mutex, true,     &s->lock->base, ww_mutex, ww_mutex_lock(s->lock, शून्य))

/*
 * SEQCNT_LOCKNAME_ZERO - अटल initializer क्रम seqcount_LOCKNAME_t
 * @name:	Name of the seqcount_LOCKNAME_t instance
 * @lock:	Poपूर्णांकer to the associated LOCKNAME
 */

#घोषणा SEQCOUNT_LOCKNAME_ZERO(seq_name, assoc_lock) अणु			\
	.seqcount		= SEQCNT_ZERO(seq_name.seqcount),	\
	__SEQ_LOCK(.lock	= (assoc_lock))				\
पूर्ण

#घोषणा SEQCNT_RAW_SPINLOCK_ZERO(name, lock)	SEQCOUNT_LOCKNAME_ZERO(name, lock)
#घोषणा SEQCNT_SPINLOCK_ZERO(name, lock)	SEQCOUNT_LOCKNAME_ZERO(name, lock)
#घोषणा SEQCNT_RWLOCK_ZERO(name, lock)		SEQCOUNT_LOCKNAME_ZERO(name, lock)
#घोषणा SEQCNT_MUTEX_ZERO(name, lock)		SEQCOUNT_LOCKNAME_ZERO(name, lock)
#घोषणा SEQCNT_WW_MUTEX_ZERO(name, lock) 	SEQCOUNT_LOCKNAME_ZERO(name, lock)

#घोषणा __seqprop_हाल(s, lockname, prop)				\
	seqcount_##lockname##_t: __seqprop_##lockname##_##prop((व्योम *)(s))

#घोषणा __seqprop(s, prop) _Generic(*(s),				\
	seqcount_t:		__seqprop_##prop((व्योम *)(s)),		\
	__seqprop_हाल((s),	raw_spinlock,	prop),			\
	__seqprop_हाल((s),	spinlock,	prop),			\
	__seqprop_हाल((s),	rwlock,		prop),			\
	__seqprop_हाल((s),	mutex,		prop),			\
	__seqprop_हाल((s),	ww_mutex,	prop))

#घोषणा seqprop_ptr(s)			__seqprop(s, ptr)
#घोषणा seqprop_sequence(s)		__seqprop(s, sequence)
#घोषणा seqprop_preemptible(s)		__seqprop(s, preemptible)
#घोषणा seqprop_निश्चित(s)		__seqprop(s, निश्चित)

/**
 * __पढ़ो_seqcount_begin() - begin a seqcount_t पढ़ो section w/o barrier
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * __पढ़ो_seqcount_begin is like पढ़ो_seqcount_begin, but has no smp_rmb()
 * barrier. Callers should ensure that smp_rmb() or equivalent ordering is
 * provided beक्रमe actually loading any of the variables that are to be
 * रक्षित in this critical section.
 *
 * Use carefully, only in critical code, and comment how the barrier is
 * provided.
 *
 * Return: count to be passed to पढ़ो_seqcount_retry()
 */
#घोषणा __पढ़ो_seqcount_begin(s)					\
(अणु									\
	अचिन्हित __seq;							\
									\
	जबतक ((__seq = seqprop_sequence(s)) & 1)			\
		cpu_relax();						\
									\
	kcsan_atomic_next(KCSAN_SEQLOCK_REGION_MAX);			\
	__seq;								\
पूर्ण)

/**
 * raw_पढ़ो_seqcount_begin() - begin a seqcount_t पढ़ो section w/o lockdep
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * Return: count to be passed to पढ़ो_seqcount_retry()
 */
#घोषणा raw_पढ़ो_seqcount_begin(s)					\
(अणु									\
	अचिन्हित _seq = __पढ़ो_seqcount_begin(s);			\
									\
	smp_rmb();							\
	_seq;								\
पूर्ण)

/**
 * पढ़ो_seqcount_begin() - begin a seqcount_t पढ़ो critical section
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * Return: count to be passed to पढ़ो_seqcount_retry()
 */
#घोषणा पढ़ो_seqcount_begin(s)						\
(अणु									\
	seqcount_lockdep_पढ़ोer_access(seqprop_ptr(s));			\
	raw_पढ़ो_seqcount_begin(s);					\
पूर्ण)

/**
 * raw_पढ़ो_seqcount() - पढ़ो the raw seqcount_t counter value
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * raw_पढ़ो_seqcount खोलोs a पढ़ो critical section of the given
 * seqcount_t, without any lockdep checking, and without checking or
 * masking the sequence counter LSB. Calling code is responsible क्रम
 * handling that.
 *
 * Return: count to be passed to पढ़ो_seqcount_retry()
 */
#घोषणा raw_पढ़ो_seqcount(s)						\
(अणु									\
	अचिन्हित __seq = seqprop_sequence(s);				\
									\
	smp_rmb();							\
	kcsan_atomic_next(KCSAN_SEQLOCK_REGION_MAX);			\
	__seq;								\
पूर्ण)

/**
 * raw_seqcount_begin() - begin a seqcount_t पढ़ो critical section w/o
 *                        lockdep and w/o counter stabilization
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * raw_seqcount_begin खोलोs a पढ़ो critical section of the given
 * seqcount_t. Unlike पढ़ो_seqcount_begin(), this function will not रुको
 * क्रम the count to stabilize. If a ग_लिखोr is active when it begins, it
 * will fail the पढ़ो_seqcount_retry() at the end of the पढ़ो critical
 * section instead of stabilizing at the beginning of it.
 *
 * Use this only in special kernel hot paths where the पढ़ो section is
 * small and has a high probability of success through other बाह्यal
 * means. It will save a single branching inकाष्ठाion.
 *
 * Return: count to be passed to पढ़ो_seqcount_retry()
 */
#घोषणा raw_seqcount_begin(s)						\
(अणु									\
	/*								\
	 * If the counter is odd, let पढ़ो_seqcount_retry() fail	\
	 * by decrementing the counter.					\
	 */								\
	raw_पढ़ो_seqcount(s) & ~1;					\
पूर्ण)

/**
 * __पढ़ो_seqcount_retry() - end a seqcount_t पढ़ो section w/o barrier
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 * @start: count, from पढ़ो_seqcount_begin()
 *
 * __पढ़ो_seqcount_retry is like पढ़ो_seqcount_retry, but has no smp_rmb()
 * barrier. Callers should ensure that smp_rmb() or equivalent ordering is
 * provided beक्रमe actually loading any of the variables that are to be
 * रक्षित in this critical section.
 *
 * Use carefully, only in critical code, and comment how the barrier is
 * provided.
 *
 * Return: true अगर a पढ़ो section retry is required, अन्यथा false
 */
#घोषणा __पढ़ो_seqcount_retry(s, start)					\
	करो___पढ़ो_seqcount_retry(seqprop_ptr(s), start)

अटल अंतरभूत पूर्णांक करो___पढ़ो_seqcount_retry(स्थिर seqcount_t *s, अचिन्हित start)
अणु
	kcsan_atomic_next(0);
	वापस unlikely(READ_ONCE(s->sequence) != start);
पूर्ण

/**
 * पढ़ो_seqcount_retry() - end a seqcount_t पढ़ो critical section
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 * @start: count, from पढ़ो_seqcount_begin()
 *
 * पढ़ो_seqcount_retry बंदs the पढ़ो critical section of given
 * seqcount_t.  If the critical section was invalid, it must be ignored
 * (and typically retried).
 *
 * Return: true अगर a पढ़ो section retry is required, अन्यथा false
 */
#घोषणा पढ़ो_seqcount_retry(s, start)					\
	करो_पढ़ो_seqcount_retry(seqprop_ptr(s), start)

अटल अंतरभूत पूर्णांक करो_पढ़ो_seqcount_retry(स्थिर seqcount_t *s, अचिन्हित start)
अणु
	smp_rmb();
	वापस करो___पढ़ो_seqcount_retry(s, start);
पूर्ण

/**
 * raw_ग_लिखो_seqcount_begin() - start a seqcount_t ग_लिखो section w/o lockdep
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * Context: check ग_लिखो_seqcount_begin()
 */
#घोषणा raw_ग_लिखो_seqcount_begin(s)					\
करो अणु									\
	अगर (seqprop_preemptible(s))					\
		preempt_disable();					\
									\
	करो_raw_ग_लिखो_seqcount_begin(seqprop_ptr(s));			\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम करो_raw_ग_लिखो_seqcount_begin(seqcount_t *s)
अणु
	kcsan_nestable_atomic_begin();
	s->sequence++;
	smp_wmb();
पूर्ण

/**
 * raw_ग_लिखो_seqcount_end() - end a seqcount_t ग_लिखो section w/o lockdep
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * Context: check ग_लिखो_seqcount_end()
 */
#घोषणा raw_ग_लिखो_seqcount_end(s)					\
करो अणु									\
	करो_raw_ग_लिखो_seqcount_end(seqprop_ptr(s));			\
									\
	अगर (seqprop_preemptible(s))					\
		preempt_enable();					\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम करो_raw_ग_लिखो_seqcount_end(seqcount_t *s)
अणु
	smp_wmb();
	s->sequence++;
	kcsan_nestable_atomic_end();
पूर्ण

/**
 * ग_लिखो_seqcount_begin_nested() - start a seqcount_t ग_लिखो section with
 *                                 custom lockdep nesting level
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 * @subclass: lockdep nesting level
 *
 * See Documentation/locking/lockdep-design.rst
 * Context: check ग_लिखो_seqcount_begin()
 */
#घोषणा ग_लिखो_seqcount_begin_nested(s, subclass)			\
करो अणु									\
	seqprop_निश्चित(s);						\
									\
	अगर (seqprop_preemptible(s))					\
		preempt_disable();					\
									\
	करो_ग_लिखो_seqcount_begin_nested(seqprop_ptr(s), subclass);	\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम करो_ग_लिखो_seqcount_begin_nested(seqcount_t *s, पूर्णांक subclass)
अणु
	करो_raw_ग_लिखो_seqcount_begin(s);
	seqcount_acquire(&s->dep_map, subclass, 0, _RET_IP_);
पूर्ण

/**
 * ग_लिखो_seqcount_begin() - start a seqcount_t ग_लिखो side critical section
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * Context: sequence counter ग_लिखो side sections must be serialized and
 * non-preemptible. Preemption will be स्वतःmatically disabled अगर and
 * only अगर the seqcount ग_लिखो serialization lock is associated, and
 * preemptible.  If पढ़ोers can be invoked from hardirq or softirq
 * context, पूर्णांकerrupts or bottom halves must be respectively disabled.
 */
#घोषणा ग_लिखो_seqcount_begin(s)						\
करो अणु									\
	seqprop_निश्चित(s);						\
									\
	अगर (seqprop_preemptible(s))					\
		preempt_disable();					\
									\
	करो_ग_लिखो_seqcount_begin(seqprop_ptr(s));			\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम करो_ग_लिखो_seqcount_begin(seqcount_t *s)
अणु
	करो_ग_लिखो_seqcount_begin_nested(s, 0);
पूर्ण

/**
 * ग_लिखो_seqcount_end() - end a seqcount_t ग_लिखो side critical section
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * Context: Preemption will be स्वतःmatically re-enabled अगर and only अगर
 * the seqcount ग_लिखो serialization lock is associated, and preemptible.
 */
#घोषणा ग_लिखो_seqcount_end(s)						\
करो अणु									\
	करो_ग_लिखो_seqcount_end(seqprop_ptr(s));				\
									\
	अगर (seqprop_preemptible(s))					\
		preempt_enable();					\
पूर्ण जबतक (0)

अटल अंतरभूत व्योम करो_ग_लिखो_seqcount_end(seqcount_t *s)
अणु
	seqcount_release(&s->dep_map, _RET_IP_);
	करो_raw_ग_लिखो_seqcount_end(s);
पूर्ण

/**
 * raw_ग_लिखो_seqcount_barrier() - करो a seqcount_t ग_लिखो barrier
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * This can be used to provide an ordering guarantee instead of the usual
 * consistency guarantee. It is one wmb cheaper, because it can collapse
 * the two back-to-back wmb()s.
 *
 * Note that ग_लिखोs surrounding the barrier should be declared atomic (e.g.
 * via WRITE_ONCE): a) to ensure the ग_लिखोs become visible to other thपढ़ोs
 * atomically, aव्योमing compiler optimizations; b) to करोcument which ग_लिखोs are
 * meant to propagate to the पढ़ोer critical section. This is necessary because
 * neither ग_लिखोs beक्रमe and after the barrier are enबंदd in a seq-ग_लिखोr
 * critical section that would ensure पढ़ोers are aware of ongoing ग_लिखोs::
 *
 *	seqcount_t seq;
 *	bool X = true, Y = false;
 *
 *	व्योम पढ़ो(व्योम)
 *	अणु
 *		bool x, y;
 *
 *		करो अणु
 *			पूर्णांक s = पढ़ो_seqcount_begin(&seq);
 *
 *			x = X; y = Y;
 *
 *		पूर्ण जबतक (पढ़ो_seqcount_retry(&seq, s));
 *
 *		BUG_ON(!x && !y);
 *      पूर्ण
 *
 *      व्योम ग_लिखो(व्योम)
 *      अणु
 *		WRITE_ONCE(Y, true);
 *
 *		raw_ग_लिखो_seqcount_barrier(seq);
 *
 *		WRITE_ONCE(X, false);
 *      पूर्ण
 */
#घोषणा raw_ग_लिखो_seqcount_barrier(s)					\
	करो_raw_ग_लिखो_seqcount_barrier(seqprop_ptr(s))

अटल अंतरभूत व्योम करो_raw_ग_लिखो_seqcount_barrier(seqcount_t *s)
अणु
	kcsan_nestable_atomic_begin();
	s->sequence++;
	smp_wmb();
	s->sequence++;
	kcsan_nestable_atomic_end();
पूर्ण

/**
 * ग_लिखो_seqcount_invalidate() - invalidate in-progress seqcount_t पढ़ो
 *                               side operations
 * @s: Poपूर्णांकer to seqcount_t or any of the seqcount_LOCKNAME_t variants
 *
 * After ग_लिखो_seqcount_invalidate, no seqcount_t पढ़ो side operations
 * will complete successfully and see data older than this.
 */
#घोषणा ग_लिखो_seqcount_invalidate(s)					\
	करो_ग_लिखो_seqcount_invalidate(seqprop_ptr(s))

अटल अंतरभूत व्योम करो_ग_लिखो_seqcount_invalidate(seqcount_t *s)
अणु
	smp_wmb();
	kcsan_nestable_atomic_begin();
	s->sequence+=2;
	kcsan_nestable_atomic_end();
पूर्ण

/*
 * Latch sequence counters (seqcount_latch_t)
 *
 * A sequence counter variant where the counter even/odd value is used to
 * चयन between two copies of रक्षित data. This allows the पढ़ो path,
 * typically NMIs, to safely पूर्णांकerrupt the ग_लिखो side critical section.
 *
 * As the ग_लिखो sections are fully preemptible, no special handling क्रम
 * PREEMPT_RT is needed.
 */
प्रकार काष्ठा अणु
	seqcount_t seqcount;
पूर्ण seqcount_latch_t;

/**
 * SEQCNT_LATCH_ZERO() - अटल initializer क्रम seqcount_latch_t
 * @seq_name: Name of the seqcount_latch_t instance
 */
#घोषणा SEQCNT_LATCH_ZERO(seq_name) अणु					\
	.seqcount		= SEQCNT_ZERO(seq_name.seqcount),	\
पूर्ण

/**
 * seqcount_latch_init() - runसमय initializer क्रम seqcount_latch_t
 * @s: Poपूर्णांकer to the seqcount_latch_t instance
 */
#घोषणा seqcount_latch_init(s) seqcount_init(&(s)->seqcount)

/**
 * raw_पढ़ो_seqcount_latch() - pick even/odd latch data copy
 * @s: Poपूर्णांकer to seqcount_latch_t
 *
 * See raw_ग_लिखो_seqcount_latch() क्रम details and a full पढ़ोer/ग_लिखोr
 * usage example.
 *
 * Return: sequence counter raw value. Use the lowest bit as an index क्रम
 * picking which data copy to पढ़ो. The full counter must then be checked
 * with पढ़ो_seqcount_latch_retry().
 */
अटल अंतरभूत अचिन्हित raw_पढ़ो_seqcount_latch(स्थिर seqcount_latch_t *s)
अणु
	/*
	 * Pairs with the first smp_wmb() in raw_ग_लिखो_seqcount_latch().
	 * Due to the dependent load, a full smp_rmb() is not needed.
	 */
	वापस READ_ONCE(s->seqcount.sequence);
पूर्ण

/**
 * पढ़ो_seqcount_latch_retry() - end a seqcount_latch_t पढ़ो section
 * @s:		Poपूर्णांकer to seqcount_latch_t
 * @start:	count, from raw_पढ़ो_seqcount_latch()
 *
 * Return: true अगर a पढ़ो section retry is required, अन्यथा false
 */
अटल अंतरभूत पूर्णांक
पढ़ो_seqcount_latch_retry(स्थिर seqcount_latch_t *s, अचिन्हित start)
अणु
	वापस पढ़ो_seqcount_retry(&s->seqcount, start);
पूर्ण

/**
 * raw_ग_लिखो_seqcount_latch() - redirect latch पढ़ोers to even/odd copy
 * @s: Poपूर्णांकer to seqcount_latch_t
 *
 * The latch technique is a multiversion concurrency control method that allows
 * queries during non-atomic modअगरications. If you can guarantee queries never
 * पूर्णांकerrupt the modअगरication -- e.g. the concurrency is strictly between CPUs
 * -- you most likely करो not need this.
 *
 * Where the traditional RCU/lockless data काष्ठाures rely on atomic
 * modअगरications to ensure queries observe either the old or the new state the
 * latch allows the same क्रम non-atomic updates. The trade-off is करोubling the
 * cost of storage; we have to मुख्यtain two copies of the entire data
 * काष्ठाure.
 *
 * Very simply put: we first modअगरy one copy and then the other. This ensures
 * there is always one copy in a stable state, पढ़ोy to give us an answer.
 *
 * The basic क्रमm is a data काष्ठाure like::
 *
 *	काष्ठा latch_काष्ठा अणु
 *		seqcount_latch_t	seq;
 *		काष्ठा data_काष्ठा	data[2];
 *	पूर्ण;
 *
 * Where a modअगरication, which is assumed to be बाह्यally serialized, करोes the
 * following::
 *
 *	व्योम latch_modअगरy(काष्ठा latch_काष्ठा *latch, ...)
 *	अणु
 *		smp_wmb();	// Ensure that the last data[1] update is visible
 *		latch->seq.sequence++;
 *		smp_wmb();	// Ensure that the seqcount update is visible
 *
 *		modअगरy(latch->data[0], ...);
 *
 *		smp_wmb();	// Ensure that the data[0] update is visible
 *		latch->seq.sequence++;
 *		smp_wmb();	// Ensure that the seqcount update is visible
 *
 *		modअगरy(latch->data[1], ...);
 *	पूर्ण
 *
 * The query will have a क्रमm like::
 *
 *	काष्ठा entry *latch_query(काष्ठा latch_काष्ठा *latch, ...)
 *	अणु
 *		काष्ठा entry *entry;
 *		अचिन्हित seq, idx;
 *
 *		करो अणु
 *			seq = raw_पढ़ो_seqcount_latch(&latch->seq);
 *
 *			idx = seq & 0x01;
 *			entry = data_query(latch->data[idx], ...);
 *
 *		// This includes needed smp_rmb()
 *		पूर्ण जबतक (पढ़ो_seqcount_latch_retry(&latch->seq, seq));
 *
 *		वापस entry;
 *	पूर्ण
 *
 * So during the modअगरication, queries are first redirected to data[1]. Then we
 * modअगरy data[0]. When that is complete, we redirect queries back to data[0]
 * and we can modअगरy data[1].
 *
 * NOTE:
 *
 *	The non-requirement क्रम atomic modअगरications करोes _NOT_ include
 *	the publishing of new entries in the हाल where data is a dynamic
 *	data काष्ठाure.
 *
 *	An iteration might start in data[0] and get suspended दीर्घ enough
 *	to miss an entire modअगरication sequence, once it resumes it might
 *	observe the new entry.
 *
 * NOTE2:
 *
 *	When data is a dynamic data काष्ठाure; one should use regular RCU
 *	patterns to manage the lअगरeबार of the objects within.
 */
अटल अंतरभूत व्योम raw_ग_लिखो_seqcount_latch(seqcount_latch_t *s)
अणु
	smp_wmb();	/* prior stores beक्रमe incrementing "sequence" */
	s->seqcount.sequence++;
	smp_wmb();      /* increment "sequence" beक्रमe following stores */
पूर्ण

/*
 * Sequential locks (seqlock_t)
 *
 * Sequence counters with an embedded spinlock क्रम ग_लिखोr serialization
 * and non-preemptibility.
 *
 * For more info, see:
 *    - Comments on top of seqcount_t
 *    - Documentation/locking/seqlock.rst
 */
प्रकार काष्ठा अणु
	/*
	 * Make sure that पढ़ोers करोn't starve ग_लिखोrs on PREEMPT_RT: use
	 * seqcount_spinlock_t instead of seqcount_t. Check __SEQ_LOCK().
	 */
	seqcount_spinlock_t seqcount;
	spinlock_t lock;
पूर्ण seqlock_t;

#घोषणा __SEQLOCK_UNLOCKED(lockname)					\
	अणु								\
		.seqcount = SEQCNT_SPINLOCK_ZERO(lockname, &(lockname).lock), \
		.lock =	__SPIN_LOCK_UNLOCKED(lockname)			\
	पूर्ण

/**
 * seqlock_init() - dynamic initializer क्रम seqlock_t
 * @sl: Poपूर्णांकer to the seqlock_t instance
 */
#घोषणा seqlock_init(sl)						\
	करो अणु								\
		spin_lock_init(&(sl)->lock);				\
		seqcount_spinlock_init(&(sl)->seqcount, &(sl)->lock);	\
	पूर्ण जबतक (0)

/**
 * DEFINE_SEQLOCK(sl) - Define a अटलally allocated seqlock_t
 * @sl: Name of the seqlock_t instance
 */
#घोषणा DEFINE_SEQLOCK(sl) \
		seqlock_t sl = __SEQLOCK_UNLOCKED(sl)

/**
 * पढ़ो_seqbegin() - start a seqlock_t पढ़ो side critical section
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * Return: count, to be passed to पढ़ो_seqretry()
 */
अटल अंतरभूत अचिन्हित पढ़ो_seqbegin(स्थिर seqlock_t *sl)
अणु
	अचिन्हित ret = पढ़ो_seqcount_begin(&sl->seqcount);

	kcsan_atomic_next(0);  /* non-raw usage, assume closing पढ़ो_seqretry() */
	kcsan_flat_atomic_begin();
	वापस ret;
पूर्ण

/**
 * पढ़ो_seqretry() - end a seqlock_t पढ़ो side section
 * @sl: Poपूर्णांकer to seqlock_t
 * @start: count, from पढ़ो_seqbegin()
 *
 * पढ़ो_seqretry बंदs the पढ़ो side critical section of given seqlock_t.
 * If the critical section was invalid, it must be ignored (and typically
 * retried).
 *
 * Return: true अगर a पढ़ो section retry is required, अन्यथा false
 */
अटल अंतरभूत अचिन्हित पढ़ो_seqretry(स्थिर seqlock_t *sl, अचिन्हित start)
अणु
	/*
	 * Assume not nested: पढ़ो_seqretry() may be called multiple बार when
	 * completing पढ़ो critical section.
	 */
	kcsan_flat_atomic_end();

	वापस पढ़ो_seqcount_retry(&sl->seqcount, start);
पूर्ण

/*
 * For all seqlock_t ग_लिखो side functions, use the the पूर्णांकernal
 * करो_ग_लिखो_seqcount_begin() instead of generic ग_लिखो_seqcount_begin().
 * This way, no redundant lockdep_निश्चित_held() checks are added.
 */

/**
 * ग_लिखो_seqlock() - start a seqlock_t ग_लिखो side critical section
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * ग_लिखो_seqlock खोलोs a ग_लिखो side critical section क्रम the given
 * seqlock_t.  It also implicitly acquires the spinlock_t embedded inside
 * that sequential lock. All seqlock_t ग_लिखो side sections are thus
 * स्वतःmatically serialized and non-preemptible.
 *
 * Context: अगर the seqlock_t पढ़ो section, or other ग_लिखो side critical
 * sections, can be invoked from hardirq or softirq contexts, use the
 * _irqsave or _bh variants of this function instead.
 */
अटल अंतरभूत व्योम ग_लिखो_seqlock(seqlock_t *sl)
अणु
	spin_lock(&sl->lock);
	करो_ग_लिखो_seqcount_begin(&sl->seqcount.seqcount);
पूर्ण

/**
 * ग_लिखो_sequnlock() - end a seqlock_t ग_लिखो side critical section
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * ग_लिखो_sequnlock बंदs the (serialized and non-preemptible) ग_लिखो side
 * critical section of given seqlock_t.
 */
अटल अंतरभूत व्योम ग_लिखो_sequnlock(seqlock_t *sl)
अणु
	करो_ग_लिखो_seqcount_end(&sl->seqcount.seqcount);
	spin_unlock(&sl->lock);
पूर्ण

/**
 * ग_लिखो_seqlock_bh() - start a softirqs-disabled seqlock_t ग_लिखो section
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * _bh variant of ग_लिखो_seqlock(). Use only अगर the पढ़ो side section, or
 * other ग_लिखो side sections, can be invoked from softirq contexts.
 */
अटल अंतरभूत व्योम ग_लिखो_seqlock_bh(seqlock_t *sl)
अणु
	spin_lock_bh(&sl->lock);
	करो_ग_लिखो_seqcount_begin(&sl->seqcount.seqcount);
पूर्ण

/**
 * ग_लिखो_sequnlock_bh() - end a softirqs-disabled seqlock_t ग_लिखो section
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * ग_लिखो_sequnlock_bh बंदs the serialized, non-preemptible, and
 * softirqs-disabled, seqlock_t ग_लिखो side critical section खोलोed with
 * ग_लिखो_seqlock_bh().
 */
अटल अंतरभूत व्योम ग_लिखो_sequnlock_bh(seqlock_t *sl)
अणु
	करो_ग_लिखो_seqcount_end(&sl->seqcount.seqcount);
	spin_unlock_bh(&sl->lock);
पूर्ण

/**
 * ग_लिखो_seqlock_irq() - start a non-पूर्णांकerruptible seqlock_t ग_लिखो section
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * _irq variant of ग_लिखो_seqlock(). Use only अगर the पढ़ो side section, or
 * other ग_लिखो sections, can be invoked from hardirq contexts.
 */
अटल अंतरभूत व्योम ग_लिखो_seqlock_irq(seqlock_t *sl)
अणु
	spin_lock_irq(&sl->lock);
	करो_ग_लिखो_seqcount_begin(&sl->seqcount.seqcount);
पूर्ण

/**
 * ग_लिखो_sequnlock_irq() - end a non-पूर्णांकerruptible seqlock_t ग_लिखो section
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * ग_लिखो_sequnlock_irq बंदs the serialized and non-पूर्णांकerruptible
 * seqlock_t ग_लिखो side section खोलोed with ग_लिखो_seqlock_irq().
 */
अटल अंतरभूत व्योम ग_लिखो_sequnlock_irq(seqlock_t *sl)
अणु
	करो_ग_लिखो_seqcount_end(&sl->seqcount.seqcount);
	spin_unlock_irq(&sl->lock);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __ग_लिखो_seqlock_irqsave(seqlock_t *sl)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sl->lock, flags);
	करो_ग_लिखो_seqcount_begin(&sl->seqcount.seqcount);
	वापस flags;
पूर्ण

/**
 * ग_लिखो_seqlock_irqsave() - start a non-पूर्णांकerruptible seqlock_t ग_लिखो
 *                           section
 * @lock:  Poपूर्णांकer to seqlock_t
 * @flags: Stack-allocated storage क्रम saving caller's local पूर्णांकerrupt
 *         state, to be passed to ग_लिखो_sequnlock_irqrestore().
 *
 * _irqsave variant of ग_लिखो_seqlock(). Use it only अगर the पढ़ो side
 * section, or other ग_लिखो sections, can be invoked from hardirq context.
 */
#घोषणा ग_लिखो_seqlock_irqsave(lock, flags)				\
	करो अणु flags = __ग_लिखो_seqlock_irqsave(lock); पूर्ण जबतक (0)

/**
 * ग_लिखो_sequnlock_irqrestore() - end non-पूर्णांकerruptible seqlock_t ग_लिखो
 *                                section
 * @sl:    Poपूर्णांकer to seqlock_t
 * @flags: Caller's saved पूर्णांकerrupt state, from ग_लिखो_seqlock_irqsave()
 *
 * ग_लिखो_sequnlock_irqrestore बंदs the serialized and non-पूर्णांकerruptible
 * seqlock_t ग_लिखो section previously खोलोed with ग_लिखो_seqlock_irqsave().
 */
अटल अंतरभूत व्योम
ग_लिखो_sequnlock_irqrestore(seqlock_t *sl, अचिन्हित दीर्घ flags)
अणु
	करो_ग_लिखो_seqcount_end(&sl->seqcount.seqcount);
	spin_unlock_irqrestore(&sl->lock, flags);
पूर्ण

/**
 * पढ़ो_seqlock_excl() - begin a seqlock_t locking पढ़ोer section
 * @sl:	Poपूर्णांकer to seqlock_t
 *
 * पढ़ो_seqlock_excl खोलोs a seqlock_t locking पढ़ोer critical section.  A
 * locking पढ़ोer exclusively locks out *both* other ग_लिखोrs *and* other
 * locking पढ़ोers, but it करोes not update the embedded sequence number.
 *
 * Locking पढ़ोers act like a normal spin_lock()/spin_unlock().
 *
 * Context: अगर the seqlock_t ग_लिखो section, *or other पढ़ो sections*, can
 * be invoked from hardirq or softirq contexts, use the _irqsave or _bh
 * variant of this function instead.
 *
 * The खोलोed पढ़ो section must be बंदd with पढ़ो_sequnlock_excl().
 */
अटल अंतरभूत व्योम पढ़ो_seqlock_excl(seqlock_t *sl)
अणु
	spin_lock(&sl->lock);
पूर्ण

/**
 * पढ़ो_sequnlock_excl() - end a seqlock_t locking पढ़ोer critical section
 * @sl: Poपूर्णांकer to seqlock_t
 */
अटल अंतरभूत व्योम पढ़ो_sequnlock_excl(seqlock_t *sl)
अणु
	spin_unlock(&sl->lock);
पूर्ण

/**
 * पढ़ो_seqlock_excl_bh() - start a seqlock_t locking पढ़ोer section with
 *			    softirqs disabled
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * _bh variant of पढ़ो_seqlock_excl(). Use this variant only अगर the
 * seqlock_t ग_लिखो side section, *or other पढ़ो sections*, can be invoked
 * from softirq contexts.
 */
अटल अंतरभूत व्योम पढ़ो_seqlock_excl_bh(seqlock_t *sl)
अणु
	spin_lock_bh(&sl->lock);
पूर्ण

/**
 * पढ़ो_sequnlock_excl_bh() - stop a seqlock_t softirq-disabled locking
 *			      पढ़ोer section
 * @sl: Poपूर्णांकer to seqlock_t
 */
अटल अंतरभूत व्योम पढ़ो_sequnlock_excl_bh(seqlock_t *sl)
अणु
	spin_unlock_bh(&sl->lock);
पूर्ण

/**
 * पढ़ो_seqlock_excl_irq() - start a non-पूर्णांकerruptible seqlock_t locking
 *			     पढ़ोer section
 * @sl: Poपूर्णांकer to seqlock_t
 *
 * _irq variant of पढ़ो_seqlock_excl(). Use this only अगर the seqlock_t
 * ग_लिखो side section, *or other पढ़ो sections*, can be invoked from a
 * hardirq context.
 */
अटल अंतरभूत व्योम पढ़ो_seqlock_excl_irq(seqlock_t *sl)
अणु
	spin_lock_irq(&sl->lock);
पूर्ण

/**
 * पढ़ो_sequnlock_excl_irq() - end an पूर्णांकerrupts-disabled seqlock_t
 *                             locking पढ़ोer section
 * @sl: Poपूर्णांकer to seqlock_t
 */
अटल अंतरभूत व्योम पढ़ो_sequnlock_excl_irq(seqlock_t *sl)
अणु
	spin_unlock_irq(&sl->lock);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __पढ़ो_seqlock_excl_irqsave(seqlock_t *sl)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sl->lock, flags);
	वापस flags;
पूर्ण

/**
 * पढ़ो_seqlock_excl_irqsave() - start a non-पूर्णांकerruptible seqlock_t
 *				 locking पढ़ोer section
 * @lock:  Poपूर्णांकer to seqlock_t
 * @flags: Stack-allocated storage क्रम saving caller's local पूर्णांकerrupt
 *         state, to be passed to पढ़ो_sequnlock_excl_irqrestore().
 *
 * _irqsave variant of पढ़ो_seqlock_excl(). Use this only अगर the seqlock_t
 * ग_लिखो side section, *or other पढ़ो sections*, can be invoked from a
 * hardirq context.
 */
#घोषणा पढ़ो_seqlock_excl_irqsave(lock, flags)				\
	करो अणु flags = __पढ़ो_seqlock_excl_irqsave(lock); पूर्ण जबतक (0)

/**
 * पढ़ो_sequnlock_excl_irqrestore() - end non-पूर्णांकerruptible seqlock_t
 *				      locking पढ़ोer section
 * @sl:    Poपूर्णांकer to seqlock_t
 * @flags: Caller saved पूर्णांकerrupt state, from पढ़ो_seqlock_excl_irqsave()
 */
अटल अंतरभूत व्योम
पढ़ो_sequnlock_excl_irqrestore(seqlock_t *sl, अचिन्हित दीर्घ flags)
अणु
	spin_unlock_irqrestore(&sl->lock, flags);
पूर्ण

/**
 * पढ़ो_seqbegin_or_lock() - begin a seqlock_t lockless or locking पढ़ोer
 * @lock: Poपूर्णांकer to seqlock_t
 * @seq : Marker and वापस parameter. If the passed value is even, the
 * पढ़ोer will become a *lockless* seqlock_t पढ़ोer as in पढ़ो_seqbegin().
 * If the passed value is odd, the पढ़ोer will become a *locking* पढ़ोer
 * as in पढ़ो_seqlock_excl().  In the first call to this function, the
 * caller *must* initialize and pass an even value to @seq; this way, a
 * lockless पढ़ो can be optimistically tried first.
 *
 * पढ़ो_seqbegin_or_lock is an API deचिन्हित to optimistically try a normal
 * lockless seqlock_t पढ़ो section first.  If an odd counter is found, the
 * lockless पढ़ो trial has failed, and the next पढ़ो iteration transक्रमms
 * itself पूर्णांकo a full seqlock_t locking पढ़ोer.
 *
 * This is typically used to aव्योम seqlock_t lockless पढ़ोers starvation
 * (too much retry loops) in the हाल of a sharp spike in ग_लिखो side
 * activity.
 *
 * Context: अगर the seqlock_t ग_लिखो section, *or other पढ़ो sections*, can
 * be invoked from hardirq or softirq contexts, use the _irqsave or _bh
 * variant of this function instead.
 *
 * Check Documentation/locking/seqlock.rst क्रम ढाँचा example code.
 *
 * Return: the encountered sequence counter value, through the @seq
 * parameter, which is overloaded as a वापस parameter. This वापसed
 * value must be checked with need_seqretry(). If the पढ़ो section need to
 * be retried, this वापसed value must also be passed as the @seq
 * parameter of the next पढ़ो_seqbegin_or_lock() iteration.
 */
अटल अंतरभूत व्योम पढ़ो_seqbegin_or_lock(seqlock_t *lock, पूर्णांक *seq)
अणु
	अगर (!(*seq & 1))	/* Even */
		*seq = पढ़ो_seqbegin(lock);
	अन्यथा			/* Odd */
		पढ़ो_seqlock_excl(lock);
पूर्ण

/**
 * need_seqretry() - validate seqlock_t "locking or lockless" पढ़ो section
 * @lock: Poपूर्णांकer to seqlock_t
 * @seq: sequence count, from पढ़ो_seqbegin_or_lock()
 *
 * Return: true अगर a पढ़ो section retry is required, false otherwise
 */
अटल अंतरभूत पूर्णांक need_seqretry(seqlock_t *lock, पूर्णांक seq)
अणु
	वापस !(seq & 1) && पढ़ो_seqretry(lock, seq);
पूर्ण

/**
 * करोne_seqretry() - end seqlock_t "locking or lockless" पढ़ोer section
 * @lock: Poपूर्णांकer to seqlock_t
 * @seq: count, from पढ़ो_seqbegin_or_lock()
 *
 * करोne_seqretry finishes the seqlock_t पढ़ो side critical section started
 * with पढ़ो_seqbegin_or_lock() and validated by need_seqretry().
 */
अटल अंतरभूत व्योम करोne_seqretry(seqlock_t *lock, पूर्णांक seq)
अणु
	अगर (seq & 1)
		पढ़ो_sequnlock_excl(lock);
पूर्ण

/**
 * पढ़ो_seqbegin_or_lock_irqsave() - begin a seqlock_t lockless पढ़ोer, or
 *                                   a non-पूर्णांकerruptible locking पढ़ोer
 * @lock: Poपूर्णांकer to seqlock_t
 * @seq:  Marker and वापस parameter. Check पढ़ो_seqbegin_or_lock().
 *
 * This is the _irqsave variant of पढ़ो_seqbegin_or_lock(). Use it only अगर
 * the seqlock_t ग_लिखो section, *or other पढ़ो sections*, can be invoked
 * from hardirq context.
 *
 * Note: Interrupts will be disabled only क्रम "locking reader" mode.
 *
 * Return:
 *
 *   1. The saved local पूर्णांकerrupts state in हाल of a locking पढ़ोer, to
 *      be passed to करोne_seqretry_irqrestore().
 *
 *   2. The encountered sequence counter value, वापसed through @seq
 *      overloaded as a वापस parameter. Check पढ़ो_seqbegin_or_lock().
 */
अटल अंतरभूत अचिन्हित दीर्घ
पढ़ो_seqbegin_or_lock_irqsave(seqlock_t *lock, पूर्णांक *seq)
अणु
	अचिन्हित दीर्घ flags = 0;

	अगर (!(*seq & 1))	/* Even */
		*seq = पढ़ो_seqbegin(lock);
	अन्यथा			/* Odd */
		पढ़ो_seqlock_excl_irqsave(lock, flags);

	वापस flags;
पूर्ण

/**
 * करोne_seqretry_irqrestore() - end a seqlock_t lockless पढ़ोer, or a
 *				non-पूर्णांकerruptible locking पढ़ोer section
 * @lock:  Poपूर्णांकer to seqlock_t
 * @seq:   Count, from पढ़ो_seqbegin_or_lock_irqsave()
 * @flags: Caller's saved local पूर्णांकerrupt state in हाल of a locking
 *	   पढ़ोer, also from पढ़ो_seqbegin_or_lock_irqsave()
 *
 * This is the _irqrestore variant of करोne_seqretry(). The पढ़ो section
 * must've been खोलोed with पढ़ो_seqbegin_or_lock_irqsave(), and validated
 * by need_seqretry().
 */
अटल अंतरभूत व्योम
करोne_seqretry_irqrestore(seqlock_t *lock, पूर्णांक seq, अचिन्हित दीर्घ flags)
अणु
	अगर (seq & 1)
		पढ़ो_sequnlock_excl_irqrestore(lock, flags);
पूर्ण
#पूर्ण_अगर /* __LINUX_SEQLOCK_H */
