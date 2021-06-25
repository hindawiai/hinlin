<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Runसमय locking correctness validator
 *
 *  Copyright (C) 2006,2007 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *  Copyright (C) 2007 Red Hat, Inc., Peter Zijlstra
 *
 * see Documentation/locking/lockdep-design.rst क्रम more details.
 */
#अगर_अघोषित __LINUX_LOCKDEP_H
#घोषणा __LINUX_LOCKDEP_H

#समावेश <linux/lockdep_types.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/percpu.h>

काष्ठा task_काष्ठा;

/* क्रम sysctl */
बाह्य पूर्णांक prove_locking;
बाह्य पूर्णांक lock_stat;

#अगर_घोषित CONFIG_LOCKDEP

#समावेश <linux/linkage.h>
#समावेश <linux/list.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/stacktrace.h>

अटल अंतरभूत व्योम lockdep_copy_map(काष्ठा lockdep_map *to,
				    काष्ठा lockdep_map *from)
अणु
	पूर्णांक i;

	*to = *from;
	/*
	 * Since the class cache can be modअगरied concurrently we could observe
	 * half poपूर्णांकers (64bit arch using 32bit copy insns). Thereक्रमe clear
	 * the caches and take the perक्रमmance hit.
	 *
	 * XXX it करोesn't work well with lockdep_set_class_and_subclass(), since
	 *     that relies on cache abuse.
	 */
	क्रम (i = 0; i < NR_LOCKDEP_CACHING_CLASSES; i++)
		to->class_cache[i] = शून्य;
पूर्ण

/*
 * Every lock has a list of other locks that were taken after it.
 * We only grow the list, never हटाओ from it:
 */
काष्ठा lock_list अणु
	काष्ठा list_head		entry;
	काष्ठा lock_class		*class;
	काष्ठा lock_class		*links_to;
	स्थिर काष्ठा lock_trace		*trace;
	u16				distance;
	/* biपंचांगap of dअगरferent dependencies from head to this */
	u8				dep;
	/* used by BFS to record whether "prev -> this" only has -(*R)-> */
	u8				only_xr;

	/*
	 * The parent field is used to implement bपढ़ोth-first search, and the
	 * bit 0 is reused to indicate अगर the lock has been accessed in BFS.
	 */
	काष्ठा lock_list		*parent;
पूर्ण;

/**
 * काष्ठा lock_chain - lock dependency chain record
 *
 * @irq_context: the same as irq_context in held_lock below
 * @depth:       the number of held locks in this chain
 * @base:        the index in chain_hlocks क्रम this chain
 * @entry:       the collided lock chains in lock_chain hash list
 * @chain_key:   the hash key of this lock_chain
 */
काष्ठा lock_chain अणु
	/* see BUILD_BUG_ON()s in add_chain_cache() */
	अचिन्हित पूर्णांक			irq_context :  2,
					depth       :  6,
					base	    : 24;
	/* 4 byte hole */
	काष्ठा hlist_node		entry;
	u64				chain_key;
पूर्ण;

#घोषणा MAX_LOCKDEP_KEYS_BITS		13
#घोषणा MAX_LOCKDEP_KEYS		(1UL << MAX_LOCKDEP_KEYS_BITS)
#घोषणा INITIAL_CHAIN_KEY		-1

काष्ठा held_lock अणु
	/*
	 * One-way hash of the dependency chain up to this poपूर्णांक. We
	 * hash the hashes step by step as the dependency chain grows.
	 *
	 * We use it क्रम dependency-caching and we skip detection
	 * passes and dependency-updates अगर there is a cache-hit, so
	 * it is असलolutely critical क्रम 100% coverage of the validator
	 * to have a unique key value क्रम every unique dependency path
	 * that can occur in the प्रणाली, to make a unique hash value
	 * as likely as possible - hence the 64-bit width.
	 *
	 * The task काष्ठा holds the current hash value (initialized
	 * with zero), here we store the previous hash value:
	 */
	u64				prev_chain_key;
	अचिन्हित दीर्घ			acquire_ip;
	काष्ठा lockdep_map		*instance;
	काष्ठा lockdep_map		*nest_lock;
#अगर_घोषित CONFIG_LOCK_STAT
	u64 				रुकोसमय_stamp;
	u64				holdसमय_stamp;
#पूर्ण_अगर
	/*
	 * class_idx is zero-indexed; it poपूर्णांकs to the element in
	 * lock_classes this held lock instance beदीर्घs to. class_idx is in
	 * the range from 0 to (MAX_LOCKDEP_KEYS-1) inclusive.
	 */
	अचिन्हित पूर्णांक			class_idx:MAX_LOCKDEP_KEYS_BITS;
	/*
	 * The lock-stack is unअगरied in that the lock chains of पूर्णांकerrupt
	 * contexts nest ontop of process context chains, but we 'separate'
	 * the hashes by starting with 0 अगर we cross पूर्णांकo an पूर्णांकerrupt
	 * context, and we also keep करो not add cross-context lock
	 * dependencies - the lock usage graph walking covers that area
	 * anyway, and we'd just unnecessarily increase the number of
	 * dependencies otherwise. [Note: hardirq and softirq contexts
	 * are separated from each other too.]
	 *
	 * The following field is used to detect when we cross पूर्णांकo an
	 * पूर्णांकerrupt context:
	 */
	अचिन्हित पूर्णांक irq_context:2; /* bit 0 - soft, bit 1 - hard */
	अचिन्हित पूर्णांक trylock:1;						/* 16 bits */

	अचिन्हित पूर्णांक पढ़ो:2;        /* see lock_acquire() comment */
	अचिन्हित पूर्णांक check:1;       /* see lock_acquire() comment */
	अचिन्हित पूर्णांक hardirqs_off:1;
	अचिन्हित पूर्णांक references:12;					/* 32 bits */
	अचिन्हित पूर्णांक pin_count;
पूर्ण;

/*
 * Initialization, self-test and debugging-output methods:
 */
बाह्य व्योम lockdep_init(व्योम);
बाह्य व्योम lockdep_reset(व्योम);
बाह्य व्योम lockdep_reset_lock(काष्ठा lockdep_map *lock);
बाह्य व्योम lockdep_मुक्त_key_range(व्योम *start, अचिन्हित दीर्घ size);
बाह्य यंत्रlinkage व्योम lockdep_sys_निकास(व्योम);
बाह्य व्योम lockdep_set_selftest_task(काष्ठा task_काष्ठा *task);

बाह्य व्योम lockdep_init_task(काष्ठा task_काष्ठा *task);

/*
 * Split the recursion counter in two to पढ़ोily detect 'off' vs recursion.
 */
#घोषणा LOCKDEP_RECURSION_BITS	16
#घोषणा LOCKDEP_OFF		(1U << LOCKDEP_RECURSION_BITS)
#घोषणा LOCKDEP_RECURSION_MASK	(LOCKDEP_OFF - 1)

/*
 * lockdep_अणुoff,onपूर्ण() are macros to aव्योम tracing and kprobes; not अंतरभूतs due
 * to header dependencies.
 */

#घोषणा lockdep_off()					\
करो अणु							\
	current->lockdep_recursion += LOCKDEP_OFF;	\
पूर्ण जबतक (0)

#घोषणा lockdep_on()					\
करो अणु							\
	current->lockdep_recursion -= LOCKDEP_OFF;	\
पूर्ण जबतक (0)

बाह्य व्योम lockdep_रेजिस्टर_key(काष्ठा lock_class_key *key);
बाह्य व्योम lockdep_unरेजिस्टर_key(काष्ठा lock_class_key *key);

/*
 * These methods are used by specअगरic locking variants (spinlocks,
 * rwlocks, mutexes and rwsems) to pass init/acquire/release events
 * to lockdep:
 */

बाह्य व्योम lockdep_init_map_type(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
	काष्ठा lock_class_key *key, पूर्णांक subclass, u8 inner, u8 outer, u8 lock_type);

अटल अंतरभूत व्योम
lockdep_init_map_रुकोs(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
		       काष्ठा lock_class_key *key, पूर्णांक subclass, u8 inner, u8 outer)
अणु
	lockdep_init_map_type(lock, name, key, subclass, inner, LD_WAIT_INV, LD_LOCK_NORMAL);
पूर्ण

अटल अंतरभूत व्योम
lockdep_init_map_रुको(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
		      काष्ठा lock_class_key *key, पूर्णांक subclass, u8 inner)
अणु
	lockdep_init_map_रुकोs(lock, name, key, subclass, inner, LD_WAIT_INV);
पूर्ण

अटल अंतरभूत व्योम lockdep_init_map(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
			     काष्ठा lock_class_key *key, पूर्णांक subclass)
अणु
	lockdep_init_map_रुको(lock, name, key, subclass, LD_WAIT_INV);
पूर्ण

/*
 * Reinitialize a lock key - क्रम हालs where there is special locking or
 * special initialization of locks so that the validator माला_लो the scope
 * of dependencies wrong: they are either too broad (they need a class-split)
 * or they are too narrow (they suffer from a false class-split):
 */
#घोषणा lockdep_set_class(lock, key)				\
	lockdep_init_map_रुकोs(&(lock)->dep_map, #key, key, 0,	\
			       (lock)->dep_map.रुको_type_inner,	\
			       (lock)->dep_map.रुको_type_outer)

#घोषणा lockdep_set_class_and_name(lock, key, name)		\
	lockdep_init_map_रुकोs(&(lock)->dep_map, name, key, 0,	\
			       (lock)->dep_map.रुको_type_inner,	\
			       (lock)->dep_map.रुको_type_outer)

#घोषणा lockdep_set_class_and_subclass(lock, key, sub)		\
	lockdep_init_map_रुकोs(&(lock)->dep_map, #key, key, sub,\
			       (lock)->dep_map.रुको_type_inner,	\
			       (lock)->dep_map.रुको_type_outer)

#घोषणा lockdep_set_subclass(lock, sub)					\
	lockdep_init_map_रुकोs(&(lock)->dep_map, #lock, (lock)->dep_map.key, sub,\
			       (lock)->dep_map.रुको_type_inner,		\
			       (lock)->dep_map.रुको_type_outer)

#घोषणा lockdep_set_novalidate_class(lock) \
	lockdep_set_class_and_name(lock, &__lockdep_no_validate__, #lock)

/*
 * Compare locking classes
 */
#घोषणा lockdep_match_class(lock, key) lockdep_match_key(&(lock)->dep_map, key)

अटल अंतरभूत पूर्णांक lockdep_match_key(काष्ठा lockdep_map *lock,
				    काष्ठा lock_class_key *key)
अणु
	वापस lock->key == key;
पूर्ण

/*
 * Acquire a lock.
 *
 * Values क्रम "read":
 *
 *   0: exclusive (ग_लिखो) acquire
 *   1: पढ़ो-acquire (no recursion allowed)
 *   2: पढ़ो-acquire with same-instance recursion allowed
 *
 * Values क्रम check:
 *
 *   0: simple checks (मुक्तing, held-at-निकास-समय, etc.)
 *   1: full validation
 */
बाह्य व्योम lock_acquire(काष्ठा lockdep_map *lock, अचिन्हित पूर्णांक subclass,
			 पूर्णांक trylock, पूर्णांक पढ़ो, पूर्णांक check,
			 काष्ठा lockdep_map *nest_lock, अचिन्हित दीर्घ ip);

बाह्य व्योम lock_release(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip);

/* lock_is_held_type() वापसs */
#घोषणा LOCK_STATE_UNKNOWN	-1
#घोषणा LOCK_STATE_NOT_HELD	0
#घोषणा LOCK_STATE_HELD		1

/*
 * Same "read" as क्रम lock_acquire(), except -1 means any.
 */
बाह्य पूर्णांक lock_is_held_type(स्थिर काष्ठा lockdep_map *lock, पूर्णांक पढ़ो);

अटल अंतरभूत पूर्णांक lock_is_held(स्थिर काष्ठा lockdep_map *lock)
अणु
	वापस lock_is_held_type(lock, -1);
पूर्ण

#घोषणा lockdep_is_held(lock)		lock_is_held(&(lock)->dep_map)
#घोषणा lockdep_is_held_type(lock, r)	lock_is_held_type(&(lock)->dep_map, (r))

बाह्य व्योम lock_set_class(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
			   काष्ठा lock_class_key *key, अचिन्हित पूर्णांक subclass,
			   अचिन्हित दीर्घ ip);

अटल अंतरभूत व्योम lock_set_subclass(काष्ठा lockdep_map *lock,
		अचिन्हित पूर्णांक subclass, अचिन्हित दीर्घ ip)
अणु
	lock_set_class(lock, lock->name, lock->key, subclass, ip);
पूर्ण

बाह्य व्योम lock_करोwngrade(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip);

#घोषणा NIL_COOKIE (काष्ठा pin_cookie)अणु .val = 0U, पूर्ण

बाह्य काष्ठा pin_cookie lock_pin_lock(काष्ठा lockdep_map *lock);
बाह्य व्योम lock_repin_lock(काष्ठा lockdep_map *lock, काष्ठा pin_cookie);
बाह्य व्योम lock_unpin_lock(काष्ठा lockdep_map *lock, काष्ठा pin_cookie);

#घोषणा lockdep_depth(tsk)	(debug_locks ? (tsk)->lockdep_depth : 0)

#घोषणा lockdep_निश्चित_held(l)	करो अणु					\
		WARN_ON(debug_locks &&					\
			lockdep_is_held(l) == LOCK_STATE_NOT_HELD);	\
	पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_not_held(l)	करो अणु				\
		WARN_ON(debug_locks &&					\
			lockdep_is_held(l) == LOCK_STATE_HELD);		\
	पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_held_ग_लिखो(l)	करो अणु			\
		WARN_ON(debug_locks && !lockdep_is_held_type(l, 0));	\
	पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_held_पढ़ो(l)	करो अणु				\
		WARN_ON(debug_locks && !lockdep_is_held_type(l, 1));	\
	पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_held_once(l)	करो अणु				\
		WARN_ON_ONCE(debug_locks && !lockdep_is_held(l));	\
	पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_none_held_once()	करो अणु				\
		WARN_ON_ONCE(debug_locks && current->lockdep_depth);	\
	पूर्ण जबतक (0)

#घोषणा lockdep_recursing(tsk)	((tsk)->lockdep_recursion)

#घोषणा lockdep_pin_lock(l)	lock_pin_lock(&(l)->dep_map)
#घोषणा lockdep_repin_lock(l,c)	lock_repin_lock(&(l)->dep_map, (c))
#घोषणा lockdep_unpin_lock(l,c)	lock_unpin_lock(&(l)->dep_map, (c))

#अन्यथा /* !CONFIG_LOCKDEP */

अटल अंतरभूत व्योम lockdep_init_task(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

अटल अंतरभूत व्योम lockdep_off(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम lockdep_on(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम lockdep_set_selftest_task(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

# define lock_acquire(l, s, t, r, c, n, i)	करो अणु पूर्ण जबतक (0)
# define lock_release(l, i)			करो अणु पूर्ण जबतक (0)
# define lock_करोwngrade(l, i)			करो अणु पूर्ण जबतक (0)
# define lock_set_class(l, n, k, s, i)		करो अणु पूर्ण जबतक (0)
# define lock_set_subclass(l, s, i)		करो अणु पूर्ण जबतक (0)
# define lockdep_init()				करो अणु पूर्ण जबतक (0)
# define lockdep_init_map_type(lock, name, key, sub, inner, outer, type) \
		करो अणु (व्योम)(name); (व्योम)(key); पूर्ण जबतक (0)
# define lockdep_init_map_रुकोs(lock, name, key, sub, inner, outer) \
		करो अणु (व्योम)(name); (व्योम)(key); पूर्ण जबतक (0)
# define lockdep_init_map_रुको(lock, name, key, sub, inner) \
		करो अणु (व्योम)(name); (व्योम)(key); पूर्ण जबतक (0)
# define lockdep_init_map(lock, name, key, sub) \
		करो अणु (व्योम)(name); (व्योम)(key); पूर्ण जबतक (0)
# define lockdep_set_class(lock, key)		करो अणु (व्योम)(key); पूर्ण जबतक (0)
# define lockdep_set_class_and_name(lock, key, name) \
		करो अणु (व्योम)(key); (व्योम)(name); पूर्ण जबतक (0)
#घोषणा lockdep_set_class_and_subclass(lock, key, sub) \
		करो अणु (व्योम)(key); पूर्ण जबतक (0)
#घोषणा lockdep_set_subclass(lock, sub)		करो अणु पूर्ण जबतक (0)

#घोषणा lockdep_set_novalidate_class(lock) करो अणु पूर्ण जबतक (0)

/*
 * We करोn't define lockdep_match_class() and lockdep_match_key() क्रम !LOCKDEP
 * हाल since the result is not well defined and the caller should rather
 * #अगर_घोषित the call himself.
 */

# define lockdep_reset()		करो अणु debug_locks = 1; पूर्ण जबतक (0)
# define lockdep_मुक्त_key_range(start, size)	करो अणु पूर्ण जबतक (0)
# define lockdep_sys_निकास() 			करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम lockdep_रेजिस्टर_key(काष्ठा lock_class_key *key)
अणु
पूर्ण

अटल अंतरभूत व्योम lockdep_unरेजिस्टर_key(काष्ठा lock_class_key *key)
अणु
पूर्ण

#घोषणा lockdep_depth(tsk)	(0)

/*
 * Dummy क्रमward declarations, allow users to ग_लिखो less अगरdef-y code
 * and depend on dead code elimination.
 */
बाह्य पूर्णांक lock_is_held(स्थिर व्योम *);
बाह्य पूर्णांक lockdep_is_held(स्थिर व्योम *);
#घोषणा lockdep_is_held_type(l, r)		(1)

#घोषणा lockdep_निश्चित_held(l)			करो अणु (व्योम)(l); पूर्ण जबतक (0)
#घोषणा lockdep_निश्चित_not_held(l)		करो अणु (व्योम)(l); पूर्ण जबतक (0)
#घोषणा lockdep_निश्चित_held_ग_लिखो(l)		करो अणु (व्योम)(l); पूर्ण जबतक (0)
#घोषणा lockdep_निश्चित_held_पढ़ो(l)		करो अणु (व्योम)(l); पूर्ण जबतक (0)
#घोषणा lockdep_निश्चित_held_once(l)		करो अणु (व्योम)(l); पूर्ण जबतक (0)
#घोषणा lockdep_निश्चित_none_held_once()	करो अणु पूर्ण जबतक (0)

#घोषणा lockdep_recursing(tsk)			(0)

#घोषणा NIL_COOKIE (काष्ठा pin_cookie)अणु पूर्ण

#घोषणा lockdep_pin_lock(l)			(अणु काष्ठा pin_cookie cookie = अणु पूर्ण; cookie; पूर्ण)
#घोषणा lockdep_repin_lock(l, c)		करो अणु (व्योम)(l); (व्योम)(c); पूर्ण जबतक (0)
#घोषणा lockdep_unpin_lock(l, c)		करो अणु (व्योम)(l); (व्योम)(c); पूर्ण जबतक (0)

#पूर्ण_अगर /* !LOCKDEP */

क्रमागत xhlock_context_t अणु
	XHLOCK_HARD,
	XHLOCK_SOFT,
	XHLOCK_CTX_NR,
पूर्ण;

#घोषणा lockdep_init_map_crosslock(m, n, k, s) करो अणुपूर्ण जबतक (0)
/*
 * To initialize a lockdep_map अटलally use this macro.
 * Note that _name must not be शून्य.
 */
#घोषणा STATIC_LOCKDEP_MAP_INIT(_name, _key) \
	अणु .name = (_name), .key = (व्योम *)(_key), पूर्ण

अटल अंतरभूत व्योम lockdep_invariant_state(bool क्रमce) अणुपूर्ण
अटल अंतरभूत व्योम lockdep_मुक्त_task(काष्ठा task_काष्ठा *task) अणुपूर्ण

#अगर_घोषित CONFIG_LOCK_STAT

बाह्य व्योम lock_contended(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip);
बाह्य व्योम lock_acquired(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip);

#घोषणा LOCK_CONTENDED(_lock, try, lock)			\
करो अणु								\
	अगर (!try(_lock)) अणु					\
		lock_contended(&(_lock)->dep_map, _RET_IP_);	\
		lock(_lock);					\
	पूर्ण							\
	lock_acquired(&(_lock)->dep_map, _RET_IP_);			\
पूर्ण जबतक (0)

#घोषणा LOCK_CONTENDED_RETURN(_lock, try, lock)			\
(अणु								\
	पूर्णांक ____err = 0;					\
	अगर (!try(_lock)) अणु					\
		lock_contended(&(_lock)->dep_map, _RET_IP_);	\
		____err = lock(_lock);				\
	पूर्ण							\
	अगर (!____err)						\
		lock_acquired(&(_lock)->dep_map, _RET_IP_);	\
	____err;						\
पूर्ण)

#अन्यथा /* CONFIG_LOCK_STAT */

#घोषणा lock_contended(lockdep_map, ip) करो अणुपूर्ण जबतक (0)
#घोषणा lock_acquired(lockdep_map, ip) करो अणुपूर्ण जबतक (0)

#घोषणा LOCK_CONTENDED(_lock, try, lock) \
	lock(_lock)

#घोषणा LOCK_CONTENDED_RETURN(_lock, try, lock) \
	lock(_lock)

#पूर्ण_अगर /* CONFIG_LOCK_STAT */

#अगर_घोषित CONFIG_LOCKDEP

/*
 * On lockdep we करोnt want the hand-coded irq-enable of
 * _raw_*_lock_flags() code, because lockdep assumes
 * that पूर्णांकerrupts are not re-enabled during lock-acquire:
 */
#घोषणा LOCK_CONTENDED_FLAGS(_lock, try, lock, lockfl, flags) \
	LOCK_CONTENDED((_lock), (try), (lock))

#अन्यथा /* CONFIG_LOCKDEP */

#घोषणा LOCK_CONTENDED_FLAGS(_lock, try, lock, lockfl, flags) \
	lockfl((_lock), (flags))

#पूर्ण_अगर /* CONFIG_LOCKDEP */

#अगर_घोषित CONFIG_PROVE_LOCKING
बाह्य व्योम prपूर्णांक_irqtrace_events(काष्ठा task_काष्ठा *curr);
#अन्यथा
अटल अंतरभूत व्योम prपूर्णांक_irqtrace_events(काष्ठा task_काष्ठा *curr)
अणु
पूर्ण
#पूर्ण_अगर

/* Variable used to make lockdep treat पढ़ो_lock() as recursive in selftests */
#अगर_घोषित CONFIG_DEBUG_LOCKING_API_SELFTESTS
बाह्य अचिन्हित पूर्णांक क्रमce_पढ़ो_lock_recursive;
#अन्यथा /* CONFIG_DEBUG_LOCKING_API_SELFTESTS */
#घोषणा क्रमce_पढ़ो_lock_recursive 0
#पूर्ण_अगर /* CONFIG_DEBUG_LOCKING_API_SELFTESTS */

#अगर_घोषित CONFIG_LOCKDEP
बाह्य bool पढ़ो_lock_is_recursive(व्योम);
#अन्यथा /* CONFIG_LOCKDEP */
/* If !LOCKDEP, the value is meaningless */
#घोषणा पढ़ो_lock_is_recursive() 0
#पूर्ण_अगर

/*
 * For trivial one-depth nesting of a lock-class, the following
 * global define can be used. (Subप्रणालीs with multiple levels
 * of nesting should define their own lock-nesting subclasses.)
 */
#घोषणा SINGLE_DEPTH_NESTING			1

/*
 * Map the dependency ops to NOP or to real lockdep ops, depending
 * on the per lock-class debug mode:
 */

#घोषणा lock_acquire_exclusive(l, s, t, n, i)		lock_acquire(l, s, t, 0, 1, n, i)
#घोषणा lock_acquire_shared(l, s, t, n, i)		lock_acquire(l, s, t, 1, 1, n, i)
#घोषणा lock_acquire_shared_recursive(l, s, t, n, i)	lock_acquire(l, s, t, 2, 1, n, i)

#घोषणा spin_acquire(l, s, t, i)		lock_acquire_exclusive(l, s, t, शून्य, i)
#घोषणा spin_acquire_nest(l, s, t, n, i)	lock_acquire_exclusive(l, s, t, n, i)
#घोषणा spin_release(l, i)			lock_release(l, i)

#घोषणा rwlock_acquire(l, s, t, i)		lock_acquire_exclusive(l, s, t, शून्य, i)
#घोषणा rwlock_acquire_पढ़ो(l, s, t, i)					\
करो अणु									\
	अगर (पढ़ो_lock_is_recursive())					\
		lock_acquire_shared_recursive(l, s, t, शून्य, i);	\
	अन्यथा								\
		lock_acquire_shared(l, s, t, शून्य, i);			\
पूर्ण जबतक (0)

#घोषणा rwlock_release(l, i)			lock_release(l, i)

#घोषणा seqcount_acquire(l, s, t, i)		lock_acquire_exclusive(l, s, t, शून्य, i)
#घोषणा seqcount_acquire_पढ़ो(l, s, t, i)	lock_acquire_shared_recursive(l, s, t, शून्य, i)
#घोषणा seqcount_release(l, i)			lock_release(l, i)

#घोषणा mutex_acquire(l, s, t, i)		lock_acquire_exclusive(l, s, t, शून्य, i)
#घोषणा mutex_acquire_nest(l, s, t, n, i)	lock_acquire_exclusive(l, s, t, n, i)
#घोषणा mutex_release(l, i)			lock_release(l, i)

#घोषणा rwsem_acquire(l, s, t, i)		lock_acquire_exclusive(l, s, t, शून्य, i)
#घोषणा rwsem_acquire_nest(l, s, t, n, i)	lock_acquire_exclusive(l, s, t, n, i)
#घोषणा rwsem_acquire_पढ़ो(l, s, t, i)		lock_acquire_shared(l, s, t, शून्य, i)
#घोषणा rwsem_release(l, i)			lock_release(l, i)

#घोषणा lock_map_acquire(l)			lock_acquire_exclusive(l, 0, 0, शून्य, _THIS_IP_)
#घोषणा lock_map_acquire_पढ़ो(l)		lock_acquire_shared_recursive(l, 0, 0, शून्य, _THIS_IP_)
#घोषणा lock_map_acquire_tryपढ़ो(l)		lock_acquire_shared_recursive(l, 0, 1, शून्य, _THIS_IP_)
#घोषणा lock_map_release(l)			lock_release(l, _THIS_IP_)

#अगर_घोषित CONFIG_PROVE_LOCKING
# define might_lock(lock)						\
करो अणु									\
	typecheck(काष्ठा lockdep_map *, &(lock)->dep_map);		\
	lock_acquire(&(lock)->dep_map, 0, 0, 0, 1, शून्य, _THIS_IP_);	\
	lock_release(&(lock)->dep_map, _THIS_IP_);			\
पूर्ण जबतक (0)
# define might_lock_पढ़ो(lock)						\
करो अणु									\
	typecheck(काष्ठा lockdep_map *, &(lock)->dep_map);		\
	lock_acquire(&(lock)->dep_map, 0, 0, 1, 1, शून्य, _THIS_IP_);	\
	lock_release(&(lock)->dep_map, _THIS_IP_);			\
पूर्ण जबतक (0)
# define might_lock_nested(lock, subclass)				\
करो अणु									\
	typecheck(काष्ठा lockdep_map *, &(lock)->dep_map);		\
	lock_acquire(&(lock)->dep_map, subclass, 0, 1, 1, शून्य,		\
		     _THIS_IP_);					\
	lock_release(&(lock)->dep_map, _THIS_IP_);			\
पूर्ण जबतक (0)

DECLARE_PER_CPU(पूर्णांक, hardirqs_enabled);
DECLARE_PER_CPU(पूर्णांक, hardirq_context);
DECLARE_PER_CPU(अचिन्हित पूर्णांक, lockdep_recursion);

#घोषणा __lockdep_enabled	(debug_locks && !this_cpu_पढ़ो(lockdep_recursion))

#घोषणा lockdep_निश्चित_irqs_enabled()					\
करो अणु									\
	WARN_ON_ONCE(__lockdep_enabled && !this_cpu_पढ़ो(hardirqs_enabled)); \
पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_irqs_disabled()					\
करो अणु									\
	WARN_ON_ONCE(__lockdep_enabled && this_cpu_पढ़ो(hardirqs_enabled)); \
पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_in_irq()						\
करो अणु									\
	WARN_ON_ONCE(__lockdep_enabled && !this_cpu_पढ़ो(hardirq_context)); \
पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_preemption_enabled()				\
करो अणु									\
	WARN_ON_ONCE(IS_ENABLED(CONFIG_PREEMPT_COUNT)	&&		\
		     __lockdep_enabled			&&		\
		     (preempt_count() != 0		||		\
		      !this_cpu_पढ़ो(hardirqs_enabled)));		\
पूर्ण जबतक (0)

#घोषणा lockdep_निश्चित_preemption_disabled()				\
करो अणु									\
	WARN_ON_ONCE(IS_ENABLED(CONFIG_PREEMPT_COUNT)	&&		\
		     __lockdep_enabled			&&		\
		     (preempt_count() == 0		&&		\
		      this_cpu_पढ़ो(hardirqs_enabled)));		\
पूर्ण जबतक (0)

/*
 * Acceptable क्रम protecting per-CPU resources accessed from BH.
 * Much like in_softirq() - semantics are ambiguous, use carefully.
 */
#घोषणा lockdep_निश्चित_in_softirq()					\
करो अणु									\
	WARN_ON_ONCE(__lockdep_enabled			&&		\
		     (!in_softirq() || in_irq() || in_nmi()));		\
पूर्ण जबतक (0)

#अन्यथा
# define might_lock(lock) करो अणु पूर्ण जबतक (0)
# define might_lock_पढ़ो(lock) करो अणु पूर्ण जबतक (0)
# define might_lock_nested(lock, subclass) करो अणु पूर्ण जबतक (0)

# define lockdep_निश्चित_irqs_enabled() करो अणु पूर्ण जबतक (0)
# define lockdep_निश्चित_irqs_disabled() करो अणु पूर्ण जबतक (0)
# define lockdep_निश्चित_in_irq() करो अणु पूर्ण जबतक (0)

# define lockdep_निश्चित_preemption_enabled() करो अणु पूर्ण जबतक (0)
# define lockdep_निश्चित_preemption_disabled() करो अणु पूर्ण जबतक (0)
# define lockdep_निश्चित_in_softirq() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROVE_RAW_LOCK_NESTING

# define lockdep_निश्चित_RT_in_thपढ़ोed_ctx() करो अणु			\
		WARN_ONCE(debug_locks && !current->lockdep_recursion &&	\
			  lockdep_hardirq_context() &&			\
			  !(current->hardirq_thपढ़ोed || current->irq_config),	\
			  "Not in threaded context on PREEMPT_RT as expected\n");	\
पूर्ण जबतक (0)

#अन्यथा

# define lockdep_निश्चित_RT_in_thपढ़ोed_ctx() करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

#अगर_घोषित CONFIG_LOCKDEP
व्योम lockdep_rcu_suspicious(स्थिर अक्षर *file, स्थिर पूर्णांक line, स्थिर अक्षर *s);
#अन्यथा
अटल अंतरभूत व्योम
lockdep_rcu_suspicious(स्थिर अक्षर *file, स्थिर पूर्णांक line, स्थिर अक्षर *s)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_LOCKDEP_H */
