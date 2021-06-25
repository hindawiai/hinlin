<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Wound/Wait Mutexes: blocking mutual exclusion locks with deadlock aव्योमance
 *
 * Original mutex implementation started by Ingo Molnar:
 *
 *  Copyright (C) 2004, 2005, 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * Wait/Die implementation:
 *  Copyright (C) 2013 Canonical Ltd.
 * Choice of algorithm:
 *  Copyright (C) 2018 WMWare Inc.
 *
 * This file contains the मुख्य data काष्ठाure and API definitions.
 */

#अगर_अघोषित __LINUX_WW_MUTEX_H
#घोषणा __LINUX_WW_MUTEX_H

#समावेश <linux/mutex.h>

काष्ठा ww_class अणु
	atomic_दीर्घ_t stamp;
	काष्ठा lock_class_key acquire_key;
	काष्ठा lock_class_key mutex_key;
	स्थिर अक्षर *acquire_name;
	स्थिर अक्षर *mutex_name;
	अचिन्हित पूर्णांक is_रुको_die;
पूर्ण;

काष्ठा ww_acquire_ctx अणु
	काष्ठा task_काष्ठा *task;
	अचिन्हित दीर्घ stamp;
	अचिन्हित पूर्णांक acquired;
	अचिन्हित लघु wounded;
	अचिन्हित लघु is_रुको_die;
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	अचिन्हित पूर्णांक करोne_acquire;
	काष्ठा ww_class *ww_class;
	काष्ठा ww_mutex *contending_lock;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	काष्ठा lockdep_map dep_map;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_WW_MUTEX_SLOWPATH
	अचिन्हित पूर्णांक deadlock_inject_पूर्णांकerval;
	अचिन्हित पूर्णांक deadlock_inject_countकरोwn;
#पूर्ण_अगर
पूर्ण;

#घोषणा __WW_CLASS_INITIALIZER(ww_class, _is_रुको_die)	    \
		अणु .stamp = ATOMIC_LONG_INIT(0) \
		, .acquire_name = #ww_class "_acquire" \
		, .mutex_name = #ww_class "_mutex" \
		, .is_रुको_die = _is_रुको_die पूर्ण

#घोषणा DEFINE_WD_CLASS(classname) \
	काष्ठा ww_class classname = __WW_CLASS_INITIALIZER(classname, 1)

#घोषणा DEFINE_WW_CLASS(classname) \
	काष्ठा ww_class classname = __WW_CLASS_INITIALIZER(classname, 0)

/**
 * ww_mutex_init - initialize the w/w mutex
 * @lock: the mutex to be initialized
 * @ww_class: the w/w class the mutex should beदीर्घ to
 *
 * Initialize the w/w mutex to unlocked state and associate it with the given
 * class. Static define macro क्रम w/w mutex is not provided and this function
 * is the only way to properly initialize the w/w mutex.
 *
 * It is not allowed to initialize an alपढ़ोy locked mutex.
 */
अटल अंतरभूत व्योम ww_mutex_init(काष्ठा ww_mutex *lock,
				 काष्ठा ww_class *ww_class)
अणु
	__mutex_init(&lock->base, ww_class->mutex_name, &ww_class->mutex_key);
	lock->ctx = शून्य;
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	lock->ww_class = ww_class;
#पूर्ण_अगर
पूर्ण

/**
 * ww_acquire_init - initialize a w/w acquire context
 * @ctx: w/w acquire context to initialize
 * @ww_class: w/w class of the context
 *
 * Initializes an context to acquire multiple mutexes of the given w/w class.
 *
 * Context-based w/w mutex acquiring can be करोne in any order whatsoever within
 * a given lock class. Deadlocks will be detected and handled with the
 * रुको/die logic.
 *
 * Mixing of context-based w/w mutex acquiring and single w/w mutex locking can
 * result in undetected deadlocks and is so क्रमbidden. Mixing dअगरferent contexts
 * क्रम the same w/w class when acquiring mutexes can also result in undetected
 * deadlocks, and is hence also क्रमbidden. Both types of abuse will be caught by
 * enabling CONFIG_PROVE_LOCKING.
 *
 * Nesting of acquire contexts क्रम _dअगरferent_ w/w classes is possible, subject
 * to the usual locking rules between dअगरferent lock classes.
 *
 * An acquire context must be released with ww_acquire_fini by the same task
 * beक्रमe the memory is मुक्तd. It is recommended to allocate the context itself
 * on the stack.
 */
अटल अंतरभूत व्योम ww_acquire_init(काष्ठा ww_acquire_ctx *ctx,
				   काष्ठा ww_class *ww_class)
अणु
	ctx->task = current;
	ctx->stamp = atomic_दीर्घ_inc_वापस_relaxed(&ww_class->stamp);
	ctx->acquired = 0;
	ctx->wounded = false;
	ctx->is_रुको_die = ww_class->is_रुको_die;
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	ctx->ww_class = ww_class;
	ctx->करोne_acquire = 0;
	ctx->contending_lock = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	debug_check_no_locks_मुक्तd((व्योम *)ctx, माप(*ctx));
	lockdep_init_map(&ctx->dep_map, ww_class->acquire_name,
			 &ww_class->acquire_key, 0);
	mutex_acquire(&ctx->dep_map, 0, 0, _RET_IP_);
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_WW_MUTEX_SLOWPATH
	ctx->deadlock_inject_पूर्णांकerval = 1;
	ctx->deadlock_inject_countकरोwn = ctx->stamp & 0xf;
#पूर्ण_अगर
पूर्ण

/**
 * ww_acquire_करोne - marks the end of the acquire phase
 * @ctx: the acquire context
 *
 * Marks the end of the acquire phase, any further w/w mutex lock calls using
 * this context are क्रमbidden.
 *
 * Calling this function is optional, it is just useful to करोcument w/w mutex
 * code and clearly designated the acquire phase from actually using the locked
 * data काष्ठाures.
 */
अटल अंतरभूत व्योम ww_acquire_करोne(काष्ठा ww_acquire_ctx *ctx)
अणु
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	lockdep_निश्चित_held(ctx);

	DEBUG_LOCKS_WARN_ON(ctx->करोne_acquire);
	ctx->करोne_acquire = 1;
#पूर्ण_अगर
पूर्ण

/**
 * ww_acquire_fini - releases a w/w acquire context
 * @ctx: the acquire context to मुक्त
 *
 * Releases a w/w acquire context. This must be called _after_ all acquired w/w
 * mutexes have been released with ww_mutex_unlock.
 */
अटल अंतरभूत व्योम ww_acquire_fini(काष्ठा ww_acquire_ctx *ctx)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	mutex_release(&ctx->dep_map, _THIS_IP_);
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	DEBUG_LOCKS_WARN_ON(ctx->acquired);
	अगर (!IS_ENABLED(CONFIG_PROVE_LOCKING))
		/*
		 * lockdep will normally handle this,
		 * but fail without anyway
		 */
		ctx->करोne_acquire = 1;

	अगर (!IS_ENABLED(CONFIG_DEBUG_LOCK_ALLOC))
		/* ensure ww_acquire_fini will still fail अगर called twice */
		ctx->acquired = ~0U;
#पूर्ण_अगर
पूर्ण

/**
 * ww_mutex_lock - acquire the w/w mutex
 * @lock: the mutex to be acquired
 * @ctx: w/w acquire context, or शून्य to acquire only a single lock.
 *
 * Lock the w/w mutex exclusively क्रम this task.
 *
 * Deadlocks within a given w/w class of locks are detected and handled with the
 * रुको/die algorithm. If the lock isn't immediately available this function
 * will either sleep until it is (रुको हाल). Or it selects the current context
 * क्रम backing off by वापसing -EDEADLK (die हाल). Trying to acquire the
 * same lock with the same context twice is also detected and संकेतled by
 * वापसing -EALREADY. Returns 0 अगर the mutex was successfully acquired.
 *
 * In the die हाल the caller must release all currently held w/w mutexes क्रम
 * the given context and then रुको क्रम this contending lock to be available by
 * calling ww_mutex_lock_slow. Alternatively callers can opt to not acquire this
 * lock and proceed with trying to acquire further w/w mutexes (e.g. when
 * scanning through lru lists trying to मुक्त resources).
 *
 * The mutex must later on be released by the same task that
 * acquired it. The task may not निकास without first unlocking the mutex. Also,
 * kernel memory where the mutex resides must not be मुक्तd with the mutex still
 * locked. The mutex must first be initialized (or अटलally defined) beक्रमe it
 * can be locked. स_रखो()-ing the mutex to 0 is not allowed. The mutex must be
 * of the same w/w lock class as was used to initialize the acquire context.
 *
 * A mutex acquired with this function must be released with ww_mutex_unlock.
 */
बाह्य पूर्णांक /* __must_check */ ww_mutex_lock(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx);

/**
 * ww_mutex_lock_पूर्णांकerruptible - acquire the w/w mutex, पूर्णांकerruptible
 * @lock: the mutex to be acquired
 * @ctx: w/w acquire context
 *
 * Lock the w/w mutex exclusively क्रम this task.
 *
 * Deadlocks within a given w/w class of locks are detected and handled with the
 * रुको/die algorithm. If the lock isn't immediately available this function
 * will either sleep until it is (रुको हाल). Or it selects the current context
 * क्रम backing off by वापसing -EDEADLK (die हाल). Trying to acquire the
 * same lock with the same context twice is also detected and संकेतled by
 * वापसing -EALREADY. Returns 0 अगर the mutex was successfully acquired. If a
 * संकेत arrives जबतक रुकोing क्रम the lock then this function वापसs -EINTR.
 *
 * In the die हाल the caller must release all currently held w/w mutexes क्रम
 * the given context and then रुको क्रम this contending lock to be available by
 * calling ww_mutex_lock_slow_पूर्णांकerruptible. Alternatively callers can opt to
 * not acquire this lock and proceed with trying to acquire further w/w mutexes
 * (e.g. when scanning through lru lists trying to मुक्त resources).
 *
 * The mutex must later on be released by the same task that
 * acquired it. The task may not निकास without first unlocking the mutex. Also,
 * kernel memory where the mutex resides must not be मुक्तd with the mutex still
 * locked. The mutex must first be initialized (or अटलally defined) beक्रमe it
 * can be locked. स_रखो()-ing the mutex to 0 is not allowed. The mutex must be
 * of the same w/w lock class as was used to initialize the acquire context.
 *
 * A mutex acquired with this function must be released with ww_mutex_unlock.
 */
बाह्य पूर्णांक __must_check ww_mutex_lock_पूर्णांकerruptible(काष्ठा ww_mutex *lock,
						    काष्ठा ww_acquire_ctx *ctx);

/**
 * ww_mutex_lock_slow - slowpath acquiring of the w/w mutex
 * @lock: the mutex to be acquired
 * @ctx: w/w acquire context
 *
 * Acquires a w/w mutex with the given context after a die हाल. This function
 * will sleep until the lock becomes available.
 *
 * The caller must have released all w/w mutexes alपढ़ोy acquired with the
 * context and then call this function on the contended lock.
 *
 * Afterwards the caller may जारी to (re)acquire the other w/w mutexes it
 * needs with ww_mutex_lock. Note that the -EALREADY वापस code from
 * ww_mutex_lock can be used to aव्योम locking this contended mutex twice.
 *
 * It is क्रमbidden to call this function with any other w/w mutexes associated
 * with the context held. It is क्रमbidden to call this on anything अन्यथा than the
 * contending mutex.
 *
 * Note that the slowpath lock acquiring can also be करोne by calling
 * ww_mutex_lock directly. This function here is simply to help w/w mutex
 * locking code पढ़ोability by clearly denoting the slowpath.
 */
अटल अंतरभूत व्योम
ww_mutex_lock_slow(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx)
अणु
	पूर्णांक ret;
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	DEBUG_LOCKS_WARN_ON(!ctx->contending_lock);
#पूर्ण_अगर
	ret = ww_mutex_lock(lock, ctx);
	(व्योम)ret;
पूर्ण

/**
 * ww_mutex_lock_slow_पूर्णांकerruptible - slowpath acquiring of the w/w mutex, पूर्णांकerruptible
 * @lock: the mutex to be acquired
 * @ctx: w/w acquire context
 *
 * Acquires a w/w mutex with the given context after a die हाल. This function
 * will sleep until the lock becomes available and वापसs 0 when the lock has
 * been acquired. If a संकेत arrives जबतक रुकोing क्रम the lock then this
 * function वापसs -EINTR.
 *
 * The caller must have released all w/w mutexes alपढ़ोy acquired with the
 * context and then call this function on the contended lock.
 *
 * Afterwards the caller may जारी to (re)acquire the other w/w mutexes it
 * needs with ww_mutex_lock. Note that the -EALREADY वापस code from
 * ww_mutex_lock can be used to aव्योम locking this contended mutex twice.
 *
 * It is क्रमbidden to call this function with any other w/w mutexes associated
 * with the given context held. It is क्रमbidden to call this on anything अन्यथा
 * than the contending mutex.
 *
 * Note that the slowpath lock acquiring can also be करोne by calling
 * ww_mutex_lock_पूर्णांकerruptible directly. This function here is simply to help
 * w/w mutex locking code पढ़ोability by clearly denoting the slowpath.
 */
अटल अंतरभूत पूर्णांक __must_check
ww_mutex_lock_slow_पूर्णांकerruptible(काष्ठा ww_mutex *lock,
				 काष्ठा ww_acquire_ctx *ctx)
अणु
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	DEBUG_LOCKS_WARN_ON(!ctx->contending_lock);
#पूर्ण_अगर
	वापस ww_mutex_lock_पूर्णांकerruptible(lock, ctx);
पूर्ण

बाह्य व्योम ww_mutex_unlock(काष्ठा ww_mutex *lock);

/**
 * ww_mutex_trylock - tries to acquire the w/w mutex without acquire context
 * @lock: mutex to lock
 *
 * Trylocks a mutex without acquire context, so no deadlock detection is
 * possible. Returns 1 अगर the mutex has been acquired successfully, 0 otherwise.
 */
अटल अंतरभूत पूर्णांक __must_check ww_mutex_trylock(काष्ठा ww_mutex *lock)
अणु
	वापस mutex_trylock(&lock->base);
पूर्ण

/***
 * ww_mutex_destroy - mark a w/w mutex unusable
 * @lock: the mutex to be destroyed
 *
 * This function marks the mutex uninitialized, and any subsequent
 * use of the mutex is क्रमbidden. The mutex must not be locked when
 * this function is called.
 */
अटल अंतरभूत व्योम ww_mutex_destroy(काष्ठा ww_mutex *lock)
अणु
	mutex_destroy(&lock->base);
पूर्ण

/**
 * ww_mutex_is_locked - is the w/w mutex locked
 * @lock: the mutex to be queried
 *
 * Returns 1 अगर the mutex is locked, 0 अगर unlocked.
 */
अटल अंतरभूत bool ww_mutex_is_locked(काष्ठा ww_mutex *lock)
अणु
	वापस mutex_is_locked(&lock->base);
पूर्ण

#पूर्ण_अगर
