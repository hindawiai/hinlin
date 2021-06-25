<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <pthपढ़ो.h>
#समावेश <मानकपन.स>
#समावेश <dlfcn.h>
#समावेश <मानककोष.स>
#समावेश <sysनिकासs.h>
#समावेश <unistd.h>
#समावेश "include/liblockdep/mutex.h"
#समावेश "../../include/linux/rbtree.h"

/**
 * काष्ठा lock_lookup - liblockdep's view of a single unique lock
 * @orig: poपूर्णांकer to the original pthपढ़ो lock, used क्रम lookups
 * @dep_map: lockdep's dep_map काष्ठाure
 * @key: lockdep's key काष्ठाure
 * @node: rb-tree node used to store the lock in a global tree
 * @name: a unique name क्रम the lock
 */
काष्ठा lock_lookup अणु
	व्योम *orig; /* Original pthपढ़ो lock, used क्रम lookups */
	काष्ठा lockdep_map dep_map; /* Since all locks are dynamic, we need
				     * a dep_map and a key क्रम each lock */
	/*
	 * Wait, there's no support क्रम key classes? Yup :(
	 * Most big projects wrap the pthपढ़ो api with their own calls to
	 * be compatible with dअगरferent locking methods. This means that
	 * "classes" will be brokes since the function that creates all
	 * locks will poपूर्णांक to a generic locking function instead of the
	 * actual code that wants to करो the locking.
	 */
	काष्ठा lock_class_key key;
	काष्ठा rb_node node;
#घोषणा LIBLOCKDEP_MAX_LOCK_NAME 22
	अक्षर name[LIBLOCKDEP_MAX_LOCK_NAME];
पूर्ण;

/* This is where we store our locks */
अटल काष्ठा rb_root locks = RB_ROOT;
अटल pthपढ़ो_rwlock_t locks_rwlock = PTHREAD_RWLOCK_INITIALIZER;

/* pthपढ़ो mutex API */

#अगर_घोषित __GLIBC__
बाह्य पूर्णांक __pthपढ़ो_mutex_init(pthपढ़ो_mutex_t *mutex, स्थिर pthपढ़ो_mutexattr_t *attr);
बाह्य पूर्णांक __pthपढ़ो_mutex_lock(pthपढ़ो_mutex_t *mutex);
बाह्य पूर्णांक __pthपढ़ो_mutex_trylock(pthपढ़ो_mutex_t *mutex);
बाह्य पूर्णांक __pthपढ़ो_mutex_unlock(pthपढ़ो_mutex_t *mutex);
बाह्य पूर्णांक __pthपढ़ो_mutex_destroy(pthपढ़ो_mutex_t *mutex);
#अन्यथा
#घोषणा __pthपढ़ो_mutex_init	शून्य
#घोषणा __pthपढ़ो_mutex_lock	शून्य
#घोषणा __pthपढ़ो_mutex_trylock	शून्य
#घोषणा __pthपढ़ो_mutex_unlock	शून्य
#घोषणा __pthपढ़ो_mutex_destroy	शून्य
#पूर्ण_अगर
अटल पूर्णांक (*ll_pthपढ़ो_mutex_init)(pthपढ़ो_mutex_t *mutex,
			स्थिर pthपढ़ो_mutexattr_t *attr)	= __pthपढ़ो_mutex_init;
अटल पूर्णांक (*ll_pthपढ़ो_mutex_lock)(pthपढ़ो_mutex_t *mutex)	= __pthपढ़ो_mutex_lock;
अटल पूर्णांक (*ll_pthपढ़ो_mutex_trylock)(pthपढ़ो_mutex_t *mutex)	= __pthपढ़ो_mutex_trylock;
अटल पूर्णांक (*ll_pthपढ़ो_mutex_unlock)(pthपढ़ो_mutex_t *mutex)	= __pthपढ़ो_mutex_unlock;
अटल पूर्णांक (*ll_pthपढ़ो_mutex_destroy)(pthपढ़ो_mutex_t *mutex)	= __pthपढ़ो_mutex_destroy;

/* pthपढ़ो rwlock API */

#अगर_घोषित __GLIBC__
बाह्य पूर्णांक __pthपढ़ो_rwlock_init(pthपढ़ो_rwlock_t *rwlock, स्थिर pthपढ़ो_rwlockattr_t *attr);
बाह्य पूर्णांक __pthपढ़ो_rwlock_destroy(pthपढ़ो_rwlock_t *rwlock);
बाह्य पूर्णांक __pthपढ़ो_rwlock_wrlock(pthपढ़ो_rwlock_t *rwlock);
बाह्य पूर्णांक __pthपढ़ो_rwlock_trywrlock(pthपढ़ो_rwlock_t *rwlock);
बाह्य पूर्णांक __pthपढ़ो_rwlock_rdlock(pthपढ़ो_rwlock_t *rwlock);
बाह्य पूर्णांक __pthपढ़ो_rwlock_tryrdlock(pthपढ़ो_rwlock_t *rwlock);
बाह्य पूर्णांक __pthपढ़ो_rwlock_unlock(pthपढ़ो_rwlock_t *rwlock);
#अन्यथा
#घोषणा __pthपढ़ो_rwlock_init		शून्य
#घोषणा __pthपढ़ो_rwlock_destroy	शून्य
#घोषणा __pthपढ़ो_rwlock_wrlock		शून्य
#घोषणा __pthपढ़ो_rwlock_trywrlock	शून्य
#घोषणा __pthपढ़ो_rwlock_rdlock		शून्य
#घोषणा __pthपढ़ो_rwlock_tryrdlock	शून्य
#घोषणा __pthपढ़ो_rwlock_unlock		शून्य
#पूर्ण_अगर

अटल पूर्णांक (*ll_pthपढ़ो_rwlock_init)(pthपढ़ो_rwlock_t *rwlock,
			स्थिर pthपढ़ो_rwlockattr_t *attr)		= __pthपढ़ो_rwlock_init;
अटल पूर्णांक (*ll_pthपढ़ो_rwlock_destroy)(pthपढ़ो_rwlock_t *rwlock)	= __pthपढ़ो_rwlock_destroy;
अटल पूर्णांक (*ll_pthपढ़ो_rwlock_rdlock)(pthपढ़ो_rwlock_t *rwlock)	= __pthपढ़ो_rwlock_rdlock;
अटल पूर्णांक (*ll_pthपढ़ो_rwlock_tryrdlock)(pthपढ़ो_rwlock_t *rwlock)	= __pthपढ़ो_rwlock_tryrdlock;
अटल पूर्णांक (*ll_pthपढ़ो_rwlock_trywrlock)(pthपढ़ो_rwlock_t *rwlock)	= __pthपढ़ो_rwlock_trywrlock;
अटल पूर्णांक (*ll_pthपढ़ो_rwlock_wrlock)(pthपढ़ो_rwlock_t *rwlock)	= __pthपढ़ो_rwlock_wrlock;
अटल पूर्णांक (*ll_pthपढ़ो_rwlock_unlock)(pthपढ़ो_rwlock_t *rwlock)	= __pthपढ़ो_rwlock_unlock;

क्रमागत अणु none, prepare, करोne, पूर्ण __init_state;
अटल व्योम init_preload(व्योम);
अटल व्योम try_init_preload(व्योम)
अणु
	अगर (__init_state != करोne)
		init_preload();
पूर्ण

अटल काष्ठा rb_node **__get_lock_node(व्योम *lock, काष्ठा rb_node **parent)
अणु
	काष्ठा rb_node **node = &locks.rb_node;
	काष्ठा lock_lookup *l;

	*parent = शून्य;

	जबतक (*node) अणु
		l = rb_entry(*node, काष्ठा lock_lookup, node);

		*parent = *node;
		अगर (lock < l->orig)
			node = &l->node.rb_left;
		अन्यथा अगर (lock > l->orig)
			node = &l->node.rb_right;
		अन्यथा
			वापस node;
	पूर्ण

	वापस node;
पूर्ण

#अगर_अघोषित LIBLOCKDEP_STATIC_ENTRIES
#घोषणा LIBLOCKDEP_STATIC_ENTRIES	1024
#पूर्ण_अगर

अटल काष्ठा lock_lookup __locks[LIBLOCKDEP_STATIC_ENTRIES];
अटल पूर्णांक __locks_nr;

अटल अंतरभूत bool is_अटल_lock(काष्ठा lock_lookup *lock)
अणु
	वापस lock >= __locks && lock < __locks + ARRAY_SIZE(__locks);
पूर्ण

अटल काष्ठा lock_lookup *alloc_lock(व्योम)
अणु
	अगर (__init_state != करोne) अणु
		/*
		 * Some programs attempt to initialize and use locks in their
		 * allocation path. This means that a call to दो_स्मृति() would
		 * result in locks being initialized and locked.
		 *
		 * Why is it an issue क्रम us? dlsym() below will try allocating
		 * to give us the original function. Since this allocation will
		 * result in a locking operations, we have to let pthपढ़ो deal
		 * with it, but we can't! we don't have the poपूर्णांकer to the
		 * original API since we're inside dlsym() trying to get it
		 */

		पूर्णांक idx = __locks_nr++;
		अगर (idx >= ARRAY_SIZE(__locks)) अणु
			dम_लिखो(STDERR_खाताNO,
		"LOCKDEP error: insufficient LIBLOCKDEP_STATIC_ENTRIES\n");
			निकास(EX_UNAVAILABLE);
		पूर्ण
		वापस __locks + idx;
	पूर्ण

	वापस दो_स्मृति(माप(काष्ठा lock_lookup));
पूर्ण

अटल अंतरभूत व्योम मुक्त_lock(काष्ठा lock_lookup *lock)
अणु
	अगर (likely(!is_अटल_lock(lock)))
		मुक्त(lock);
पूर्ण

/**
 * __get_lock - find or create a lock instance
 * @lock: poपूर्णांकer to a pthपढ़ो lock function
 *
 * Try to find an existing lock in the rbtree using the provided poपूर्णांकer. If
 * one wasn't found - create it.
 */
अटल काष्ठा lock_lookup *__get_lock(व्योम *lock)
अणु
	काष्ठा rb_node **node, *parent;
	काष्ठा lock_lookup *l;

	ll_pthपढ़ो_rwlock_rdlock(&locks_rwlock);
	node = __get_lock_node(lock, &parent);
	ll_pthपढ़ो_rwlock_unlock(&locks_rwlock);
	अगर (*node) अणु
		वापस rb_entry(*node, काष्ठा lock_lookup, node);
	पूर्ण

	/* We didn't find the lock, let's create it */
	l = alloc_lock();
	अगर (l == शून्य)
		वापस शून्य;

	l->orig = lock;
	/*
	 * Currently the name of the lock is the ptr value of the pthपढ़ो lock,
	 * जबतक not optimal, it makes debugging a bit easier.
	 *
	 * TODO: Get the real name of the lock using libdwarf
	 */
	प्र_लिखो(l->name, "%p", lock);
	lockdep_init_map(&l->dep_map, l->name, &l->key, 0);

	ll_pthपढ़ो_rwlock_wrlock(&locks_rwlock);
	/* This might have changed since the last समय we fetched it */
	node = __get_lock_node(lock, &parent);
	rb_link_node(&l->node, parent, node);
	rb_insert_color(&l->node, &locks);
	ll_pthपढ़ो_rwlock_unlock(&locks_rwlock);

	वापस l;
पूर्ण

अटल व्योम __del_lock(काष्ठा lock_lookup *lock)
अणु
	ll_pthपढ़ो_rwlock_wrlock(&locks_rwlock);
	rb_erase(&lock->node, &locks);
	ll_pthपढ़ो_rwlock_unlock(&locks_rwlock);
	मुक्त_lock(lock);
पूर्ण

पूर्णांक pthपढ़ो_mutex_init(pthपढ़ो_mutex_t *mutex,
			स्थिर pthपढ़ो_mutexattr_t *attr)
अणु
	पूर्णांक r;

	/*
	 * We keep trying to init our preload module because there might be
	 * code in init sections that tries to touch locks beक्रमe we are
	 * initialized, in that हाल we'll need to manually call preload
	 * to get us going.
	 *
	 * Funny enough, kernel's lockdep had the same issue, and used
	 * (almost) the same solution. See look_up_lock_class() in
	 * kernel/locking/lockdep.c क्रम details.
	 */
	try_init_preload();

	r = ll_pthपढ़ो_mutex_init(mutex, attr);
	अगर (r == 0)
		/*
		 * We करो a dummy initialization here so that lockdep could
		 * warn us अगर something fishy is going on - such as
		 * initializing a held lock.
		 */
		__get_lock(mutex);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_mutex_lock(pthपढ़ो_mutex_t *mutex)
अणु
	पूर्णांक r;

	try_init_preload();

	lock_acquire(&__get_lock(mutex)->dep_map, 0, 0, 0, 1, शून्य,
			(अचिन्हित दीर्घ)_RET_IP_);
	/*
	 * Here's the thing with pthपढ़ो mutexes: unlike the kernel variant,
	 * they can fail.
	 *
	 * This means that the behaviour here is a bit dअगरferent from what's
	 * going on in the kernel: there we just tell lockdep that we took the
	 * lock beक्रमe actually taking it, but here we must deal with the हाल
	 * that locking failed.
	 *
	 * To करो that we'll "release" the lock अगर locking failed - this way
	 * we'll get lockdep करोing the correct checks when we try to take
	 * the lock, and अगर that fails - we'll be back to the correct
	 * state by releasing it.
	 */
	r = ll_pthपढ़ो_mutex_lock(mutex);
	अगर (r)
		lock_release(&__get_lock(mutex)->dep_map, (अचिन्हित दीर्घ)_RET_IP_);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_mutex_trylock(pthपढ़ो_mutex_t *mutex)
अणु
	पूर्णांक r;

	try_init_preload();

	lock_acquire(&__get_lock(mutex)->dep_map, 0, 1, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	r = ll_pthपढ़ो_mutex_trylock(mutex);
	अगर (r)
		lock_release(&__get_lock(mutex)->dep_map, (अचिन्हित दीर्घ)_RET_IP_);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_mutex_unlock(pthपढ़ो_mutex_t *mutex)
अणु
	पूर्णांक r;

	try_init_preload();

	lock_release(&__get_lock(mutex)->dep_map, (अचिन्हित दीर्घ)_RET_IP_);
	/*
	 * Just like taking a lock, only in reverse!
	 *
	 * If we fail releasing the lock, tell lockdep we're holding it again.
	 */
	r = ll_pthपढ़ो_mutex_unlock(mutex);
	अगर (r)
		lock_acquire(&__get_lock(mutex)->dep_map, 0, 0, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_mutex_destroy(pthपढ़ो_mutex_t *mutex)
अणु
	try_init_preload();

	/*
	 * Let's see if we're releasing a lock that's held.
	 *
	 * TODO: Hook पूर्णांकo मुक्त() and add that check there as well.
	 */
	debug_check_no_locks_मुक्तd(mutex, माप(*mutex));
	__del_lock(__get_lock(mutex));
	वापस ll_pthपढ़ो_mutex_destroy(mutex);
पूर्ण

/* This is the rwlock part, very similar to what happened with mutex above */
पूर्णांक pthपढ़ो_rwlock_init(pthपढ़ो_rwlock_t *rwlock,
			स्थिर pthपढ़ो_rwlockattr_t *attr)
अणु
	पूर्णांक r;

	try_init_preload();

	r = ll_pthपढ़ो_rwlock_init(rwlock, attr);
	अगर (r == 0)
		__get_lock(rwlock);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_rwlock_destroy(pthपढ़ो_rwlock_t *rwlock)
अणु
	try_init_preload();

	debug_check_no_locks_मुक्तd(rwlock, माप(*rwlock));
	__del_lock(__get_lock(rwlock));
	वापस ll_pthपढ़ो_rwlock_destroy(rwlock);
पूर्ण

पूर्णांक pthपढ़ो_rwlock_rdlock(pthपढ़ो_rwlock_t *rwlock)
अणु
	पूर्णांक r;

        init_preload();

	lock_acquire(&__get_lock(rwlock)->dep_map, 0, 0, 2, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	r = ll_pthपढ़ो_rwlock_rdlock(rwlock);
	अगर (r)
		lock_release(&__get_lock(rwlock)->dep_map, (अचिन्हित दीर्घ)_RET_IP_);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_rwlock_tryrdlock(pthपढ़ो_rwlock_t *rwlock)
अणु
	पूर्णांक r;

        init_preload();

	lock_acquire(&__get_lock(rwlock)->dep_map, 0, 1, 2, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	r = ll_pthपढ़ो_rwlock_tryrdlock(rwlock);
	अगर (r)
		lock_release(&__get_lock(rwlock)->dep_map, (अचिन्हित दीर्घ)_RET_IP_);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_rwlock_trywrlock(pthपढ़ो_rwlock_t *rwlock)
अणु
	पूर्णांक r;

        init_preload();

	lock_acquire(&__get_lock(rwlock)->dep_map, 0, 1, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	r = ll_pthपढ़ो_rwlock_trywrlock(rwlock);
	अगर (r)
		lock_release(&__get_lock(rwlock)->dep_map, (अचिन्हित दीर्घ)_RET_IP_);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_rwlock_wrlock(pthपढ़ो_rwlock_t *rwlock)
अणु
	पूर्णांक r;

        init_preload();

	lock_acquire(&__get_lock(rwlock)->dep_map, 0, 0, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);
	r = ll_pthपढ़ो_rwlock_wrlock(rwlock);
	अगर (r)
		lock_release(&__get_lock(rwlock)->dep_map, (अचिन्हित दीर्घ)_RET_IP_);

	वापस r;
पूर्ण

पूर्णांक pthपढ़ो_rwlock_unlock(pthपढ़ो_rwlock_t *rwlock)
अणु
	पूर्णांक r;

        init_preload();

	lock_release(&__get_lock(rwlock)->dep_map, (अचिन्हित दीर्घ)_RET_IP_);
	r = ll_pthपढ़ो_rwlock_unlock(rwlock);
	अगर (r)
		lock_acquire(&__get_lock(rwlock)->dep_map, 0, 0, 0, 1, शून्य, (अचिन्हित दीर्घ)_RET_IP_);

	वापस r;
पूर्ण

__attribute__((स्थिरructor)) अटल व्योम init_preload(व्योम)
अणु
	अगर (__init_state == करोne)
		वापस;

#अगर_अघोषित __GLIBC__
	__init_state = prepare;

	ll_pthपढ़ो_mutex_init = dlsym(RTLD_NEXT, "pthread_mutex_init");
	ll_pthपढ़ो_mutex_lock = dlsym(RTLD_NEXT, "pthread_mutex_lock");
	ll_pthपढ़ो_mutex_trylock = dlsym(RTLD_NEXT, "pthread_mutex_trylock");
	ll_pthपढ़ो_mutex_unlock = dlsym(RTLD_NEXT, "pthread_mutex_unlock");
	ll_pthपढ़ो_mutex_destroy = dlsym(RTLD_NEXT, "pthread_mutex_destroy");

	ll_pthपढ़ो_rwlock_init = dlsym(RTLD_NEXT, "pthread_rwlock_init");
	ll_pthपढ़ो_rwlock_destroy = dlsym(RTLD_NEXT, "pthread_rwlock_destroy");
	ll_pthपढ़ो_rwlock_rdlock = dlsym(RTLD_NEXT, "pthread_rwlock_rdlock");
	ll_pthपढ़ो_rwlock_tryrdlock = dlsym(RTLD_NEXT, "pthread_rwlock_tryrdlock");
	ll_pthपढ़ो_rwlock_wrlock = dlsym(RTLD_NEXT, "pthread_rwlock_wrlock");
	ll_pthपढ़ो_rwlock_trywrlock = dlsym(RTLD_NEXT, "pthread_rwlock_trywrlock");
	ll_pthपढ़ो_rwlock_unlock = dlsym(RTLD_NEXT, "pthread_rwlock_unlock");
#पूर्ण_अगर

	__init_state = करोne;
पूर्ण
