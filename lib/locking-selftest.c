<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * lib/locking-selftest.c
 *
 * Testsuite क्रम various locking APIs: spinlocks, rwlocks,
 * mutexes and rw-semaphores.
 *
 * It is checking both false positives and false negatives.
 *
 * Started by Ingo Molnar:
 *
 *  Copyright (C) 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 */
#समावेश <linux/rwsem.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ww_mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/rपंचांगutex.h>
#समावेश <linux/local_lock.h>

/*
 * Change this to 1 अगर you want to see the failure prपूर्णांकouts:
 */
अटल अचिन्हित पूर्णांक debug_locks_verbose;
अचिन्हित पूर्णांक क्रमce_पढ़ो_lock_recursive;

अटल DEFINE_WD_CLASS(ww_lockdep);

अटल पूर्णांक __init setup_debug_locks_verbose(अक्षर *str)
अणु
	get_option(&str, &debug_locks_verbose);

	वापस 1;
पूर्ण

__setup("debug_locks_verbose=", setup_debug_locks_verbose);

#घोषणा FAILURE		0
#घोषणा SUCCESS		1

#घोषणा LOCKTYPE_SPIN	0x1
#घोषणा LOCKTYPE_RWLOCK	0x2
#घोषणा LOCKTYPE_MUTEX	0x4
#घोषणा LOCKTYPE_RWSEM	0x8
#घोषणा LOCKTYPE_WW	0x10
#घोषणा LOCKTYPE_RTMUTEX 0x20
#घोषणा LOCKTYPE_LL	0x40

अटल काष्ठा ww_acquire_ctx t, t2;
अटल काष्ठा ww_mutex o, o2, o3;

/*
 * Normal standalone locks, क्रम the circular and irq-context
 * dependency tests:
 */
अटल DEFINE_SPINLOCK(lock_A);
अटल DEFINE_SPINLOCK(lock_B);
अटल DEFINE_SPINLOCK(lock_C);
अटल DEFINE_SPINLOCK(lock_D);

अटल DEFINE_RAW_SPINLOCK(raw_lock_A);
अटल DEFINE_RAW_SPINLOCK(raw_lock_B);

अटल DEFINE_RWLOCK(rwlock_A);
अटल DEFINE_RWLOCK(rwlock_B);
अटल DEFINE_RWLOCK(rwlock_C);
अटल DEFINE_RWLOCK(rwlock_D);

अटल DEFINE_MUTEX(mutex_A);
अटल DEFINE_MUTEX(mutex_B);
अटल DEFINE_MUTEX(mutex_C);
अटल DEFINE_MUTEX(mutex_D);

अटल DECLARE_RWSEM(rwsem_A);
अटल DECLARE_RWSEM(rwsem_B);
अटल DECLARE_RWSEM(rwsem_C);
अटल DECLARE_RWSEM(rwsem_D);

#अगर_घोषित CONFIG_RT_MUTEXES

अटल DEFINE_RT_MUTEX(rपंचांगutex_A);
अटल DEFINE_RT_MUTEX(rपंचांगutex_B);
अटल DEFINE_RT_MUTEX(rपंचांगutex_C);
अटल DEFINE_RT_MUTEX(rपंचांगutex_D);

#पूर्ण_अगर

/*
 * Locks that we initialize dynamically as well so that
 * e.g. X1 and X2 becomes two instances of the same class,
 * but X* and Y* are dअगरferent classes. We करो this so that
 * we करो not trigger a real lockup:
 */
अटल DEFINE_SPINLOCK(lock_X1);
अटल DEFINE_SPINLOCK(lock_X2);
अटल DEFINE_SPINLOCK(lock_Y1);
अटल DEFINE_SPINLOCK(lock_Y2);
अटल DEFINE_SPINLOCK(lock_Z1);
अटल DEFINE_SPINLOCK(lock_Z2);

अटल DEFINE_RWLOCK(rwlock_X1);
अटल DEFINE_RWLOCK(rwlock_X2);
अटल DEFINE_RWLOCK(rwlock_Y1);
अटल DEFINE_RWLOCK(rwlock_Y2);
अटल DEFINE_RWLOCK(rwlock_Z1);
अटल DEFINE_RWLOCK(rwlock_Z2);

अटल DEFINE_MUTEX(mutex_X1);
अटल DEFINE_MUTEX(mutex_X2);
अटल DEFINE_MUTEX(mutex_Y1);
अटल DEFINE_MUTEX(mutex_Y2);
अटल DEFINE_MUTEX(mutex_Z1);
अटल DEFINE_MUTEX(mutex_Z2);

अटल DECLARE_RWSEM(rwsem_X1);
अटल DECLARE_RWSEM(rwsem_X2);
अटल DECLARE_RWSEM(rwsem_Y1);
अटल DECLARE_RWSEM(rwsem_Y2);
अटल DECLARE_RWSEM(rwsem_Z1);
अटल DECLARE_RWSEM(rwsem_Z2);

#अगर_घोषित CONFIG_RT_MUTEXES

अटल DEFINE_RT_MUTEX(rपंचांगutex_X1);
अटल DEFINE_RT_MUTEX(rपंचांगutex_X2);
अटल DEFINE_RT_MUTEX(rपंचांगutex_Y1);
अटल DEFINE_RT_MUTEX(rपंचांगutex_Y2);
अटल DEFINE_RT_MUTEX(rपंचांगutex_Z1);
अटल DEFINE_RT_MUTEX(rपंचांगutex_Z2);

#पूर्ण_अगर

अटल local_lock_t local_A = INIT_LOCAL_LOCK(local_A);

/*
 * non-अंतरभूतd runसमय initializers, to let separate locks share
 * the same lock-class:
 */
#घोषणा INIT_CLASS_FUNC(class) 				\
अटल noअंतरभूत व्योम					\
init_class_##class(spinlock_t *lock, rwlock_t *rwlock, \
	काष्ठा mutex *mutex, काष्ठा rw_semaphore *rwsem)\
अणु							\
	spin_lock_init(lock);			\
	rwlock_init(rwlock);				\
	mutex_init(mutex);				\
	init_rwsem(rwsem);				\
पूर्ण

INIT_CLASS_FUNC(X)
INIT_CLASS_FUNC(Y)
INIT_CLASS_FUNC(Z)

अटल व्योम init_shared_classes(व्योम)
अणु
#अगर_घोषित CONFIG_RT_MUTEXES
	अटल काष्ठा lock_class_key rt_X, rt_Y, rt_Z;

	__rt_mutex_init(&rपंचांगutex_X1, __func__, &rt_X);
	__rt_mutex_init(&rपंचांगutex_X2, __func__, &rt_X);
	__rt_mutex_init(&rपंचांगutex_Y1, __func__, &rt_Y);
	__rt_mutex_init(&rपंचांगutex_Y2, __func__, &rt_Y);
	__rt_mutex_init(&rपंचांगutex_Z1, __func__, &rt_Z);
	__rt_mutex_init(&rपंचांगutex_Z2, __func__, &rt_Z);
#पूर्ण_अगर

	init_class_X(&lock_X1, &rwlock_X1, &mutex_X1, &rwsem_X1);
	init_class_X(&lock_X2, &rwlock_X2, &mutex_X2, &rwsem_X2);

	init_class_Y(&lock_Y1, &rwlock_Y1, &mutex_Y1, &rwsem_Y1);
	init_class_Y(&lock_Y2, &rwlock_Y2, &mutex_Y2, &rwsem_Y2);

	init_class_Z(&lock_Z1, &rwlock_Z1, &mutex_Z1, &rwsem_Z1);
	init_class_Z(&lock_Z2, &rwlock_Z2, &mutex_Z2, &rwsem_Z2);
पूर्ण

/*
 * For spinlocks and rwlocks we also करो hardirq-safe / softirq-safe tests.
 * The following functions use a lock from a simulated hardirq/softirq
 * context, causing the locks to be marked as hardirq-safe/softirq-safe:
 */

#घोषणा HARसूचीQ_DISABLE		local_irq_disable
#घोषणा HARसूचीQ_ENABLE		local_irq_enable

#घोषणा HARसूचीQ_ENTER()				\
	local_irq_disable();			\
	__irq_enter();				\
	WARN_ON(!in_irq());

#घोषणा HARसूचीQ_EXIT()				\
	__irq_निकास();				\
	local_irq_enable();

#घोषणा SOFTIRQ_DISABLE		local_bh_disable
#घोषणा SOFTIRQ_ENABLE		local_bh_enable

#घोषणा SOFTIRQ_ENTER()				\
		local_bh_disable();		\
		local_irq_disable();		\
		lockdep_softirq_enter();	\
		WARN_ON(!in_softirq());

#घोषणा SOFTIRQ_EXIT()				\
		lockdep_softirq_निकास();		\
		local_irq_enable();		\
		local_bh_enable();

/*
 * Shortcuts क्रम lock/unlock API variants, to keep
 * the testहालs compact:
 */
#घोषणा L(x)			spin_lock(&lock_##x)
#घोषणा U(x)			spin_unlock(&lock_##x)
#घोषणा LU(x)			L(x); U(x)
#घोषणा SI(x)			spin_lock_init(&lock_##x)

#घोषणा WL(x)			ग_लिखो_lock(&rwlock_##x)
#घोषणा WU(x)			ग_लिखो_unlock(&rwlock_##x)
#घोषणा WLU(x)			WL(x); WU(x)

#घोषणा RL(x)			पढ़ो_lock(&rwlock_##x)
#घोषणा RU(x)			पढ़ो_unlock(&rwlock_##x)
#घोषणा RLU(x)			RL(x); RU(x)
#घोषणा RWI(x)			rwlock_init(&rwlock_##x)

#घोषणा ML(x)			mutex_lock(&mutex_##x)
#घोषणा MU(x)			mutex_unlock(&mutex_##x)
#घोषणा MI(x)			mutex_init(&mutex_##x)

#घोषणा RTL(x)			rt_mutex_lock(&rपंचांगutex_##x)
#घोषणा RTU(x)			rt_mutex_unlock(&rपंचांगutex_##x)
#घोषणा RTI(x)			rt_mutex_init(&rपंचांगutex_##x)

#घोषणा WSL(x)			करोwn_ग_लिखो(&rwsem_##x)
#घोषणा WSU(x)			up_ग_लिखो(&rwsem_##x)

#घोषणा RSL(x)			करोwn_पढ़ो(&rwsem_##x)
#घोषणा RSU(x)			up_पढ़ो(&rwsem_##x)
#घोषणा RWSI(x)			init_rwsem(&rwsem_##x)

#अगर_अघोषित CONFIG_DEBUG_WW_MUTEX_SLOWPATH
#घोषणा WWAI(x)			ww_acquire_init(x, &ww_lockdep)
#अन्यथा
#घोषणा WWAI(x)			करो अणु ww_acquire_init(x, &ww_lockdep); (x)->deadlock_inject_countकरोwn = ~0U; पूर्ण जबतक (0)
#पूर्ण_अगर
#घोषणा WWAD(x)			ww_acquire_करोne(x)
#घोषणा WWAF(x)			ww_acquire_fini(x)

#घोषणा WWL(x, c)		ww_mutex_lock(x, c)
#घोषणा WWT(x)			ww_mutex_trylock(x)
#घोषणा WWL1(x)			ww_mutex_lock(x, शून्य)
#घोषणा WWU(x)			ww_mutex_unlock(x)


#घोषणा LOCK_UNLOCK_2(x,y)	LOCK(x); LOCK(y); UNLOCK(y); UNLOCK(x)

/*
 * Generate dअगरferent permutations of the same testहाल, using
 * the same basic lock-dependency/state events:
 */

#घोषणा GENERATE_TESTCASE(name)			\
						\
अटल व्योम name(व्योम) अणु E(); पूर्ण

#घोषणा GENERATE_PERMUTATIONS_2_EVENTS(name)	\
						\
अटल व्योम name##_12(व्योम) अणु E1(); E2(); पूर्ण	\
अटल व्योम name##_21(व्योम) अणु E2(); E1(); पूर्ण

#घोषणा GENERATE_PERMUTATIONS_3_EVENTS(name)		\
							\
अटल व्योम name##_123(व्योम) अणु E1(); E2(); E3(); पूर्ण	\
अटल व्योम name##_132(व्योम) अणु E1(); E3(); E2(); पूर्ण	\
अटल व्योम name##_213(व्योम) अणु E2(); E1(); E3(); पूर्ण	\
अटल व्योम name##_231(व्योम) अणु E2(); E3(); E1(); पूर्ण	\
अटल व्योम name##_312(व्योम) अणु E3(); E1(); E2(); पूर्ण	\
अटल व्योम name##_321(व्योम) अणु E3(); E2(); E1(); पूर्ण

/*
 * AA deadlock:
 */

#घोषणा E()					\
						\
	LOCK(X1);				\
	LOCK(X2); /* this one should fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(AA_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(AA_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(AA_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(AA_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(AA_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(AA_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(AA_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * Special-हाल क्रम पढ़ो-locking, they are
 * allowed to recurse on the same lock class:
 */
अटल व्योम rlock_AA1(व्योम)
अणु
	RL(X1);
	RL(X1); // this one should NOT fail
पूर्ण

अटल व्योम rlock_AA1B(व्योम)
अणु
	RL(X1);
	RL(X2); // this one should NOT fail
पूर्ण

अटल व्योम rsem_AA1(व्योम)
अणु
	RSL(X1);
	RSL(X1); // this one should fail
पूर्ण

अटल व्योम rsem_AA1B(व्योम)
अणु
	RSL(X1);
	RSL(X2); // this one should fail
पूर्ण
/*
 * The mixing of पढ़ो and ग_लिखो locks is not allowed:
 */
अटल व्योम rlock_AA2(व्योम)
अणु
	RL(X1);
	WL(X2); // this one should fail
पूर्ण

अटल व्योम rsem_AA2(व्योम)
अणु
	RSL(X1);
	WSL(X2); // this one should fail
पूर्ण

अटल व्योम rlock_AA3(व्योम)
अणु
	WL(X1);
	RL(X2); // this one should fail
पूर्ण

अटल व्योम rsem_AA3(व्योम)
अणु
	WSL(X1);
	RSL(X2); // this one should fail
पूर्ण

/*
 * पढ़ो_lock(A)
 * spin_lock(B)
 *		spin_lock(B)
 *		ग_लिखो_lock(A)
 */
अटल व्योम rlock_ABBA1(व्योम)
अणु
	RL(X1);
	L(Y1);
	U(Y1);
	RU(X1);

	L(Y1);
	WL(X1);
	WU(X1);
	U(Y1); // should fail
पूर्ण

अटल व्योम rwsem_ABBA1(व्योम)
अणु
	RSL(X1);
	ML(Y1);
	MU(Y1);
	RSU(X1);

	ML(Y1);
	WSL(X1);
	WSU(X1);
	MU(Y1); // should fail
पूर्ण

/*
 * पढ़ो_lock(A)
 * spin_lock(B)
 *		spin_lock(B)
 *		ग_लिखो_lock(A)
 *
 * This test हाल is aimed at poking whether the chain cache prevents us from
 * detecting a पढ़ो-lock/lock-ग_लिखो deadlock: अगर the chain cache करोesn't dअगरfer
 * पढ़ो/ग_लिखो locks, the following हाल may happen
 *
 * 	अणु पढ़ो_lock(A)->lock(B) dependency exists पूर्ण
 *
 * 	P0:
 * 	lock(B);
 * 	पढ़ो_lock(A);
 *
 *	अणु Not a deadlock, B -> A is added in the chain cache पूर्ण
 *
 *	P1:
 *	lock(B);
 *	ग_लिखो_lock(A);
 *
 *	अणु B->A found in chain cache, not reported as a deadlock पूर्ण
 *
 */
अटल व्योम rlock_chaincache_ABBA1(व्योम)
अणु
	RL(X1);
	L(Y1);
	U(Y1);
	RU(X1);

	L(Y1);
	RL(X1);
	RU(X1);
	U(Y1);

	L(Y1);
	WL(X1);
	WU(X1);
	U(Y1); // should fail
पूर्ण

/*
 * पढ़ो_lock(A)
 * spin_lock(B)
 *		spin_lock(B)
 *		पढ़ो_lock(A)
 */
अटल व्योम rlock_ABBA2(व्योम)
अणु
	RL(X1);
	L(Y1);
	U(Y1);
	RU(X1);

	L(Y1);
	RL(X1);
	RU(X1);
	U(Y1); // should NOT fail
पूर्ण

अटल व्योम rwsem_ABBA2(व्योम)
अणु
	RSL(X1);
	ML(Y1);
	MU(Y1);
	RSU(X1);

	ML(Y1);
	RSL(X1);
	RSU(X1);
	MU(Y1); // should fail
पूर्ण


/*
 * ग_लिखो_lock(A)
 * spin_lock(B)
 *		spin_lock(B)
 *		ग_लिखो_lock(A)
 */
अटल व्योम rlock_ABBA3(व्योम)
अणु
	WL(X1);
	L(Y1);
	U(Y1);
	WU(X1);

	L(Y1);
	WL(X1);
	WU(X1);
	U(Y1); // should fail
पूर्ण

अटल व्योम rwsem_ABBA3(व्योम)
अणु
	WSL(X1);
	ML(Y1);
	MU(Y1);
	WSU(X1);

	ML(Y1);
	WSL(X1);
	WSU(X1);
	MU(Y1); // should fail
पूर्ण

/*
 * ABBA deadlock:
 */

#घोषणा E()					\
						\
	LOCK_UNLOCK_2(A, B);			\
	LOCK_UNLOCK_2(B, A); /* fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(ABBA_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(ABBA_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(ABBA_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(ABBA_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(ABBA_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(ABBA_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(ABBA_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * AB BC CA deadlock:
 */

#घोषणा E()					\
						\
	LOCK_UNLOCK_2(A, B);			\
	LOCK_UNLOCK_2(B, C);			\
	LOCK_UNLOCK_2(C, A); /* fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(ABBCCA_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(ABBCCA_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(ABBCCA_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(ABBCCA_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(ABBCCA_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(ABBCCA_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(ABBCCA_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * AB CA BC deadlock:
 */

#घोषणा E()					\
						\
	LOCK_UNLOCK_2(A, B);			\
	LOCK_UNLOCK_2(C, A);			\
	LOCK_UNLOCK_2(B, C); /* fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(ABCABC_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(ABCABC_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(ABCABC_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(ABCABC_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(ABCABC_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(ABCABC_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(ABCABC_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * AB BC CD DA deadlock:
 */

#घोषणा E()					\
						\
	LOCK_UNLOCK_2(A, B);			\
	LOCK_UNLOCK_2(B, C);			\
	LOCK_UNLOCK_2(C, D);			\
	LOCK_UNLOCK_2(D, A); /* fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(ABBCCDDA_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(ABBCCDDA_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(ABBCCDDA_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(ABBCCDDA_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(ABBCCDDA_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(ABBCCDDA_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(ABBCCDDA_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * AB CD BD DA deadlock:
 */
#घोषणा E()					\
						\
	LOCK_UNLOCK_2(A, B);			\
	LOCK_UNLOCK_2(C, D);			\
	LOCK_UNLOCK_2(B, D);			\
	LOCK_UNLOCK_2(D, A); /* fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(ABCDBDDA_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(ABCDBDDA_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(ABCDBDDA_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(ABCDBDDA_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(ABCDBDDA_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(ABCDBDDA_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(ABCDBDDA_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * AB CD BC DA deadlock:
 */
#घोषणा E()					\
						\
	LOCK_UNLOCK_2(A, B);			\
	LOCK_UNLOCK_2(C, D);			\
	LOCK_UNLOCK_2(B, C);			\
	LOCK_UNLOCK_2(D, A); /* fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(ABCDBCDA_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(ABCDBCDA_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(ABCDBCDA_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(ABCDBCDA_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(ABCDBCDA_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(ABCDBCDA_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(ABCDBCDA_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * Double unlock:
 */
#घोषणा E()					\
						\
	LOCK(A);				\
	UNLOCK(A);				\
	UNLOCK(A); /* fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(द्विगुन_unlock_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(द्विगुन_unlock_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(द्विगुन_unlock_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(द्विगुन_unlock_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(द्विगुन_unlock_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(द्विगुन_unlock_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(द्विगुन_unlock_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * initializing a held lock:
 */
#घोषणा E()					\
						\
	LOCK(A);				\
	INIT(A); /* fail */

/*
 * 6 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_TESTCASE(init_held_spin)
#समावेश "locking-selftest-wlock.h"
GENERATE_TESTCASE(init_held_wlock)
#समावेश "locking-selftest-rlock.h"
GENERATE_TESTCASE(init_held_rlock)
#समावेश "locking-selftest-mutex.h"
GENERATE_TESTCASE(init_held_mutex)
#समावेश "locking-selftest-wsem.h"
GENERATE_TESTCASE(init_held_wsem)
#समावेश "locking-selftest-rsem.h"
GENERATE_TESTCASE(init_held_rsem)

#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश "locking-selftest-rtmutex.h"
GENERATE_TESTCASE(init_held_rपंचांगutex);
#पूर्ण_अगर

#अघोषित E

/*
 * locking an irq-safe lock with irqs enabled:
 */
#घोषणा E1()				\
					\
	IRQ_ENTER();			\
	LOCK(A);			\
	UNLOCK(A);			\
	IRQ_EXIT();

#घोषणा E2()				\
					\
	LOCK(A);			\
	UNLOCK(A);

/*
 * Generate 24 testहालs:
 */
#समावेश "locking-selftest-spin-hardirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe1_hard_spin)

#समावेश "locking-selftest-rlock-hardirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe1_hard_rlock)

#समावेश "locking-selftest-wlock-hardirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe1_hard_wlock)

#समावेश "locking-selftest-spin-softirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe1_soft_spin)

#समावेश "locking-selftest-rlock-softirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe1_soft_rlock)

#समावेश "locking-selftest-wlock-softirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe1_soft_wlock)

#अघोषित E1
#अघोषित E2

/*
 * Enabling hardirqs with a softirq-safe lock held:
 */
#घोषणा E1()				\
					\
	SOFTIRQ_ENTER();		\
	LOCK(A);			\
	UNLOCK(A);			\
	SOFTIRQ_EXIT();

#घोषणा E2()				\
					\
	HARसूचीQ_DISABLE();		\
	LOCK(A);			\
	HARसूचीQ_ENABLE();		\
	UNLOCK(A);

/*
 * Generate 12 testहालs:
 */
#समावेश "locking-selftest-spin.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2A_spin)

#समावेश "locking-selftest-wlock.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2A_wlock)

#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2A_rlock)

#अघोषित E1
#अघोषित E2

/*
 * Enabling irqs with an irq-safe lock held:
 */
#घोषणा E1()				\
					\
	IRQ_ENTER();			\
	LOCK(A);			\
	UNLOCK(A);			\
	IRQ_EXIT();

#घोषणा E2()				\
					\
	IRQ_DISABLE();			\
	LOCK(A);			\
	IRQ_ENABLE();			\
	UNLOCK(A);

/*
 * Generate 24 testहालs:
 */
#समावेश "locking-selftest-spin-hardirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2B_hard_spin)

#समावेश "locking-selftest-rlock-hardirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2B_hard_rlock)

#समावेश "locking-selftest-wlock-hardirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2B_hard_wlock)

#समावेश "locking-selftest-spin-softirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2B_soft_spin)

#समावेश "locking-selftest-rlock-softirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2B_soft_rlock)

#समावेश "locking-selftest-wlock-softirq.h"
GENERATE_PERMUTATIONS_2_EVENTS(irqsafe2B_soft_wlock)

#अघोषित E1
#अघोषित E2

/*
 * Acquiring a irq-unsafe lock जबतक holding an irq-safe-lock:
 */
#घोषणा E1()				\
					\
	LOCK(A);			\
	LOCK(B);			\
	UNLOCK(B);			\
	UNLOCK(A);			\

#घोषणा E2()				\
					\
	LOCK(B);			\
	UNLOCK(B);

#घोषणा E3()				\
					\
	IRQ_ENTER();			\
	LOCK(A);			\
	UNLOCK(A);			\
	IRQ_EXIT();

/*
 * Generate 36 testहालs:
 */
#समावेश "locking-selftest-spin-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe3_hard_spin)

#समावेश "locking-selftest-rlock-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe3_hard_rlock)

#समावेश "locking-selftest-wlock-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe3_hard_wlock)

#समावेश "locking-selftest-spin-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe3_soft_spin)

#समावेश "locking-selftest-rlock-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe3_soft_rlock)

#समावेश "locking-selftest-wlock-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe3_soft_wlock)

#अघोषित E1
#अघोषित E2
#अघोषित E3

/*
 * If a lock turns पूर्णांकo softirq-safe, but earlier it took
 * a softirq-unsafe lock:
 */

#घोषणा E1()				\
	IRQ_DISABLE();			\
	LOCK(A);			\
	LOCK(B);			\
	UNLOCK(B);			\
	UNLOCK(A);			\
	IRQ_ENABLE();

#घोषणा E2()				\
	LOCK(B);			\
	UNLOCK(B);

#घोषणा E3()				\
	IRQ_ENTER();			\
	LOCK(A);			\
	UNLOCK(A);			\
	IRQ_EXIT();

/*
 * Generate 36 testहालs:
 */
#समावेश "locking-selftest-spin-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe4_hard_spin)

#समावेश "locking-selftest-rlock-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe4_hard_rlock)

#समावेश "locking-selftest-wlock-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe4_hard_wlock)

#समावेश "locking-selftest-spin-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe4_soft_spin)

#समावेश "locking-selftest-rlock-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe4_soft_rlock)

#समावेश "locking-selftest-wlock-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irqsafe4_soft_wlock)

#अघोषित E1
#अघोषित E2
#अघोषित E3

/*
 * पढ़ो-lock / ग_लिखो-lock irq inversion.
 *
 * Deadlock scenario:
 *
 * CPU#1 is at #1, i.e. it has ग_लिखो-locked A, but has not
 * taken B yet.
 *
 * CPU#2 is at #2, i.e. it has locked B.
 *
 * Hardirq hits CPU#2 at poपूर्णांक #2 and is trying to पढ़ो-lock A.
 *
 * The deadlock occurs because CPU#1 will spin on B, and CPU#2
 * will spin on A.
 */

#घोषणा E1()				\
					\
	IRQ_DISABLE();			\
	WL(A);				\
	LOCK(B);			\
	UNLOCK(B);			\
	WU(A);				\
	IRQ_ENABLE();

#घोषणा E2()				\
					\
	LOCK(B);			\
	UNLOCK(B);

#घोषणा E3()				\
					\
	IRQ_ENTER();			\
	RL(A);				\
	RU(A);				\
	IRQ_EXIT();

/*
 * Generate 36 testहालs:
 */
#समावेश "locking-selftest-spin-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_inversion_hard_spin)

#समावेश "locking-selftest-rlock-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_inversion_hard_rlock)

#समावेश "locking-selftest-wlock-hardirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_inversion_hard_wlock)

#समावेश "locking-selftest-spin-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_inversion_soft_spin)

#समावेश "locking-selftest-rlock-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_inversion_soft_rlock)

#समावेश "locking-selftest-wlock-softirq.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_inversion_soft_wlock)

#अघोषित E1
#अघोषित E2
#अघोषित E3

/*
 * ग_लिखो-पढ़ो / ग_लिखो-पढ़ो / ग_लिखो-पढ़ो deadlock even अगर पढ़ो is recursive
 */

#घोषणा E1()				\
					\
	WL(X1);				\
	RL(Y1);				\
	RU(Y1);				\
	WU(X1);

#घोषणा E2()				\
					\
	WL(Y1);				\
	RL(Z1);				\
	RU(Z1);				\
	WU(Y1);

#घोषणा E3()				\
					\
	WL(Z1);				\
	RL(X1);				\
	RU(X1);				\
	WU(Z1);

#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(W1R2_W2R3_W3R1)

#अघोषित E1
#अघोषित E2
#अघोषित E3

/*
 * ग_लिखो-ग_लिखो / पढ़ो-पढ़ो / ग_लिखो-पढ़ो deadlock even अगर पढ़ो is recursive
 */

#घोषणा E1()				\
					\
	WL(X1);				\
	WL(Y1);				\
	WU(Y1);				\
	WU(X1);

#घोषणा E2()				\
					\
	RL(Y1);				\
	RL(Z1);				\
	RU(Z1);				\
	RU(Y1);

#घोषणा E3()				\
					\
	WL(Z1);				\
	RL(X1);				\
	RU(X1);				\
	WU(Z1);

#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(W1W2_R2R3_W3R1)

#अघोषित E1
#अघोषित E2
#अघोषित E3

/*
 * ग_लिखो-ग_लिखो / पढ़ो-पढ़ो / पढ़ो-ग_लिखो is not deadlock when पढ़ो is recursive
 */

#घोषणा E1()				\
					\
	WL(X1);				\
	WL(Y1);				\
	WU(Y1);				\
	WU(X1);

#घोषणा E2()				\
					\
	RL(Y1);				\
	RL(Z1);				\
	RU(Z1);				\
	RU(Y1);

#घोषणा E3()				\
					\
	RL(Z1);				\
	WL(X1);				\
	WU(X1);				\
	RU(Z1);

#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(W1R2_R2R3_W3W1)

#अघोषित E1
#अघोषित E2
#अघोषित E3

/*
 * ग_लिखो-पढ़ो / पढ़ो-पढ़ो / ग_लिखो-ग_लिखो is not deadlock when पढ़ो is recursive
 */

#घोषणा E1()				\
					\
	WL(X1);				\
	RL(Y1);				\
	RU(Y1);				\
	WU(X1);

#घोषणा E2()				\
					\
	RL(Y1);				\
	RL(Z1);				\
	RU(Z1);				\
	RU(Y1);

#घोषणा E3()				\
					\
	WL(Z1);				\
	WL(X1);				\
	WU(X1);				\
	WU(Z1);

#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(W1W2_R2R3_R3W1)

#अघोषित E1
#अघोषित E2
#अघोषित E3
/*
 * पढ़ो-lock / ग_लिखो-lock recursion that is actually safe.
 */

#घोषणा E1()				\
					\
	IRQ_DISABLE();			\
	WL(A);				\
	WU(A);				\
	IRQ_ENABLE();

#घोषणा E2()				\
					\
	RL(A);				\
	RU(A);				\

#घोषणा E3()				\
					\
	IRQ_ENTER();			\
	LOCK(A);			\
	L(B);				\
	U(B);				\
	UNLOCK(A);			\
	IRQ_EXIT();

/*
 * Generate 24 testहालs:
 */
#समावेश "locking-selftest-hardirq.h"
#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion_hard_rlock)

#समावेश "locking-selftest-wlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion_hard_wlock)

#समावेश "locking-selftest-softirq.h"
#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion_soft_rlock)

#समावेश "locking-selftest-wlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion_soft_wlock)

#अघोषित E1
#अघोषित E2
#अघोषित E3

/*
 * पढ़ो-lock / ग_लिखो-lock recursion that is unsafe.
 */

#घोषणा E1()				\
					\
	IRQ_DISABLE();			\
	L(B);				\
	LOCK(A);			\
	UNLOCK(A);			\
	U(B);				\
	IRQ_ENABLE();

#घोषणा E2()				\
					\
	RL(A);				\
	RU(A);				\

#घोषणा E3()				\
					\
	IRQ_ENTER();			\
	L(B);				\
	U(B);				\
	IRQ_EXIT();

/*
 * Generate 24 testहालs:
 */
#समावेश "locking-selftest-hardirq.h"
#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion2_hard_rlock)

#समावेश "locking-selftest-wlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion2_hard_wlock)

#समावेश "locking-selftest-softirq.h"
#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion2_soft_rlock)

#समावेश "locking-selftest-wlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion2_soft_wlock)

#अघोषित E1
#अघोषित E2
#अघोषित E3
/*
 * पढ़ो-lock / ग_लिखो-lock recursion that is unsafe.
 *
 * A is a ENABLED_*_READ lock
 * B is a USED_IN_*_READ lock
 *
 * पढ़ो_lock(A);
 *			ग_लिखो_lock(B);
 * <पूर्णांकerrupt>
 * पढ़ो_lock(B);
 * 			ग_लिखो_lock(A); // अगर this one is पढ़ो_lock(), no deadlock
 */

#घोषणा E1()				\
					\
	IRQ_DISABLE();			\
	WL(B);				\
	LOCK(A);			\
	UNLOCK(A);			\
	WU(B);				\
	IRQ_ENABLE();

#घोषणा E2()				\
					\
	RL(A);				\
	RU(A);				\

#घोषणा E3()				\
					\
	IRQ_ENTER();			\
	RL(B);				\
	RU(B);				\
	IRQ_EXIT();

/*
 * Generate 24 testहालs:
 */
#समावेश "locking-selftest-hardirq.h"
#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion3_hard_rlock)

#समावेश "locking-selftest-wlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion3_hard_wlock)

#समावेश "locking-selftest-softirq.h"
#समावेश "locking-selftest-rlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion3_soft_rlock)

#समावेश "locking-selftest-wlock.h"
GENERATE_PERMUTATIONS_3_EVENTS(irq_पढ़ो_recursion3_soft_wlock)

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
# define I_SPINLOCK(x)	lockdep_reset_lock(&lock_##x.dep_map)
# define I_RAW_SPINLOCK(x)	lockdep_reset_lock(&raw_lock_##x.dep_map)
# define I_RWLOCK(x)	lockdep_reset_lock(&rwlock_##x.dep_map)
# define I_MUTEX(x)	lockdep_reset_lock(&mutex_##x.dep_map)
# define I_RWSEM(x)	lockdep_reset_lock(&rwsem_##x.dep_map)
# define I_WW(x)	lockdep_reset_lock(&x.dep_map)
# define I_LOCAL_LOCK(x) lockdep_reset_lock(&local_##x.dep_map)
#अगर_घोषित CONFIG_RT_MUTEXES
# define I_RTMUTEX(x)	lockdep_reset_lock(&rपंचांगutex_##x.dep_map)
#पूर्ण_अगर
#अन्यथा
# define I_SPINLOCK(x)
# define I_RAW_SPINLOCK(x)
# define I_RWLOCK(x)
# define I_MUTEX(x)
# define I_RWSEM(x)
# define I_WW(x)
# define I_LOCAL_LOCK(x)
#पूर्ण_अगर

#अगर_अघोषित I_RTMUTEX
# define I_RTMUTEX(x)
#पूर्ण_अगर

#अगर_घोषित CONFIG_RT_MUTEXES
#घोषणा I2_RTMUTEX(x)	rt_mutex_init(&rपंचांगutex_##x)
#अन्यथा
#घोषणा I2_RTMUTEX(x)
#पूर्ण_अगर

#घोषणा I1(x)					\
	करो अणु					\
		I_SPINLOCK(x);			\
		I_RWLOCK(x);			\
		I_MUTEX(x);			\
		I_RWSEM(x);			\
		I_RTMUTEX(x);			\
	पूर्ण जबतक (0)

#घोषणा I2(x)					\
	करो अणु					\
		spin_lock_init(&lock_##x);	\
		rwlock_init(&rwlock_##x);	\
		mutex_init(&mutex_##x);		\
		init_rwsem(&rwsem_##x);		\
		I2_RTMUTEX(x);			\
	पूर्ण जबतक (0)

अटल व्योम reset_locks(व्योम)
अणु
	local_irq_disable();
	lockdep_मुक्त_key_range(&ww_lockdep.acquire_key, 1);
	lockdep_मुक्त_key_range(&ww_lockdep.mutex_key, 1);

	I1(A); I1(B); I1(C); I1(D);
	I1(X1); I1(X2); I1(Y1); I1(Y2); I1(Z1); I1(Z2);
	I_WW(t); I_WW(t2); I_WW(o.base); I_WW(o2.base); I_WW(o3.base);
	I_RAW_SPINLOCK(A); I_RAW_SPINLOCK(B);
	I_LOCAL_LOCK(A);

	lockdep_reset();

	I2(A); I2(B); I2(C); I2(D);
	init_shared_classes();
	raw_spin_lock_init(&raw_lock_A);
	raw_spin_lock_init(&raw_lock_B);
	local_lock_init(&local_A);

	ww_mutex_init(&o, &ww_lockdep); ww_mutex_init(&o2, &ww_lockdep); ww_mutex_init(&o3, &ww_lockdep);
	स_रखो(&t, 0, माप(t)); स_रखो(&t2, 0, माप(t2));
	स_रखो(&ww_lockdep.acquire_key, 0, माप(ww_lockdep.acquire_key));
	स_रखो(&ww_lockdep.mutex_key, 0, माप(ww_lockdep.mutex_key));
	local_irq_enable();
पूर्ण

#अघोषित I

अटल पूर्णांक testहाल_total;
अटल पूर्णांक testहाल_successes;
अटल पूर्णांक expected_testहाल_failures;
अटल पूर्णांक unexpected_testहाल_failures;

अटल व्योम करोtest(व्योम (*testहाल_fn)(व्योम), पूर्णांक expected, पूर्णांक lockclass_mask)
अणु
	अचिन्हित दीर्घ saved_preempt_count = preempt_count();

	WARN_ON(irqs_disabled());

	debug_locks_silent = !(debug_locks_verbose & lockclass_mask);

	testहाल_fn();
	/*
	 * Filter out expected failures:
	 */
#अगर_अघोषित CONFIG_PROVE_LOCKING
	अगर (expected == FAILURE && debug_locks) अणु
		expected_testहाल_failures++;
		pr_cont("failed|");
	पूर्ण
	अन्यथा
#पूर्ण_अगर
	अगर (debug_locks != expected) अणु
		unexpected_testहाल_failures++;
		pr_cont("FAILED|");
	पूर्ण अन्यथा अणु
		testहाल_successes++;
		pr_cont("  ok  |");
	पूर्ण
	testहाल_total++;

	अगर (debug_locks_verbose & lockclass_mask)
		pr_cont(" lockclass mask: %x, debug_locks: %d, expected: %d\n",
			lockclass_mask, debug_locks, expected);
	/*
	 * Some tests (e.g. द्विगुन-unlock) might corrupt the preemption
	 * count, so restore it:
	 */
	preempt_count_set(saved_preempt_count);
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	अगर (softirq_count())
		current->softirqs_enabled = 0;
	अन्यथा
		current->softirqs_enabled = 1;
#पूर्ण_अगर

	reset_locks();
पूर्ण

#अगर_घोषित CONFIG_RT_MUTEXES
#घोषणा करोtest_rt(fn, e, m)	करोtest((fn), (e), (m))
#अन्यथा
#घोषणा करोtest_rt(fn, e, m)
#पूर्ण_अगर

अटल अंतरभूत व्योम prपूर्णांक_testname(स्थिर अक्षर *testname)
अणु
	prपूर्णांकk("%33s:", testname);
पूर्ण

#घोषणा DO_TESTCASE_1(desc, name, nr)				\
	prपूर्णांक_testname(desc"/"#nr);				\
	करोtest(name##_##nr, SUCCESS, LOCKTYPE_RWLOCK);		\
	pr_cont("\n");

#घोषणा DO_TESTCASE_1B(desc, name, nr)				\
	prपूर्णांक_testname(desc"/"#nr);				\
	करोtest(name##_##nr, FAILURE, LOCKTYPE_RWLOCK);		\
	pr_cont("\n");

#घोषणा DO_TESTCASE_1RR(desc, name, nr)				\
	prपूर्णांक_testname(desc"/"#nr);				\
	pr_cont("             |");				\
	करोtest(name##_##nr, SUCCESS, LOCKTYPE_RWLOCK);		\
	pr_cont("\n");

#घोषणा DO_TESTCASE_1RRB(desc, name, nr)			\
	prपूर्णांक_testname(desc"/"#nr);				\
	pr_cont("             |");				\
	करोtest(name##_##nr, FAILURE, LOCKTYPE_RWLOCK);		\
	pr_cont("\n");


#घोषणा DO_TESTCASE_3(desc, name, nr)				\
	prपूर्णांक_testname(desc"/"#nr);				\
	करोtest(name##_spin_##nr, FAILURE, LOCKTYPE_SPIN);	\
	करोtest(name##_wlock_##nr, FAILURE, LOCKTYPE_RWLOCK);	\
	करोtest(name##_rlock_##nr, SUCCESS, LOCKTYPE_RWLOCK);	\
	pr_cont("\n");

#घोषणा DO_TESTCASE_3RW(desc, name, nr)				\
	prपूर्णांक_testname(desc"/"#nr);				\
	करोtest(name##_spin_##nr, FAILURE, LOCKTYPE_SPIN|LOCKTYPE_RWLOCK);\
	करोtest(name##_wlock_##nr, FAILURE, LOCKTYPE_RWLOCK);	\
	करोtest(name##_rlock_##nr, SUCCESS, LOCKTYPE_RWLOCK);	\
	pr_cont("\n");

#घोषणा DO_TESTCASE_2RW(desc, name, nr)				\
	prपूर्णांक_testname(desc"/"#nr);				\
	pr_cont("      |");					\
	करोtest(name##_wlock_##nr, FAILURE, LOCKTYPE_RWLOCK);	\
	करोtest(name##_rlock_##nr, SUCCESS, LOCKTYPE_RWLOCK);	\
	pr_cont("\n");

#घोषणा DO_TESTCASE_2x2RW(desc, name, nr)			\
	DO_TESTCASE_2RW("hard-"desc, name##_hard, nr)		\
	DO_TESTCASE_2RW("soft-"desc, name##_soft, nr)		\

#घोषणा DO_TESTCASE_6x2x2RW(desc, name)				\
	DO_TESTCASE_2x2RW(desc, name, 123);			\
	DO_TESTCASE_2x2RW(desc, name, 132);			\
	DO_TESTCASE_2x2RW(desc, name, 213);			\
	DO_TESTCASE_2x2RW(desc, name, 231);			\
	DO_TESTCASE_2x2RW(desc, name, 312);			\
	DO_TESTCASE_2x2RW(desc, name, 321);

#घोषणा DO_TESTCASE_6(desc, name)				\
	prपूर्णांक_testname(desc);					\
	करोtest(name##_spin, FAILURE, LOCKTYPE_SPIN);		\
	करोtest(name##_wlock, FAILURE, LOCKTYPE_RWLOCK);		\
	करोtest(name##_rlock, FAILURE, LOCKTYPE_RWLOCK);		\
	करोtest(name##_mutex, FAILURE, LOCKTYPE_MUTEX);		\
	करोtest(name##_wsem, FAILURE, LOCKTYPE_RWSEM);		\
	करोtest(name##_rsem, FAILURE, LOCKTYPE_RWSEM);		\
	करोtest_rt(name##_rपंचांगutex, FAILURE, LOCKTYPE_RTMUTEX);	\
	pr_cont("\n");

#घोषणा DO_TESTCASE_6_SUCCESS(desc, name)			\
	prपूर्णांक_testname(desc);					\
	करोtest(name##_spin, SUCCESS, LOCKTYPE_SPIN);		\
	करोtest(name##_wlock, SUCCESS, LOCKTYPE_RWLOCK);		\
	करोtest(name##_rlock, SUCCESS, LOCKTYPE_RWLOCK);		\
	करोtest(name##_mutex, SUCCESS, LOCKTYPE_MUTEX);		\
	करोtest(name##_wsem, SUCCESS, LOCKTYPE_RWSEM);		\
	करोtest(name##_rsem, SUCCESS, LOCKTYPE_RWSEM);		\
	करोtest_rt(name##_rपंचांगutex, SUCCESS, LOCKTYPE_RTMUTEX);	\
	pr_cont("\n");

/*
 * 'read' variant: rlocks must not trigger.
 */
#घोषणा DO_TESTCASE_6R(desc, name)				\
	prपूर्णांक_testname(desc);					\
	करोtest(name##_spin, FAILURE, LOCKTYPE_SPIN);		\
	करोtest(name##_wlock, FAILURE, LOCKTYPE_RWLOCK);		\
	करोtest(name##_rlock, SUCCESS, LOCKTYPE_RWLOCK);		\
	करोtest(name##_mutex, FAILURE, LOCKTYPE_MUTEX);		\
	करोtest(name##_wsem, FAILURE, LOCKTYPE_RWSEM);		\
	करोtest(name##_rsem, FAILURE, LOCKTYPE_RWSEM);		\
	करोtest_rt(name##_rपंचांगutex, FAILURE, LOCKTYPE_RTMUTEX);	\
	pr_cont("\n");

#घोषणा DO_TESTCASE_2I(desc, name, nr)				\
	DO_TESTCASE_1("hard-"desc, name##_hard, nr);		\
	DO_TESTCASE_1("soft-"desc, name##_soft, nr);

#घोषणा DO_TESTCASE_2IB(desc, name, nr)				\
	DO_TESTCASE_1B("hard-"desc, name##_hard, nr);		\
	DO_TESTCASE_1B("soft-"desc, name##_soft, nr);

#घोषणा DO_TESTCASE_6I(desc, name, nr)				\
	DO_TESTCASE_3("hard-"desc, name##_hard, nr);		\
	DO_TESTCASE_3("soft-"desc, name##_soft, nr);

#घोषणा DO_TESTCASE_6IRW(desc, name, nr)			\
	DO_TESTCASE_3RW("hard-"desc, name##_hard, nr);		\
	DO_TESTCASE_3RW("soft-"desc, name##_soft, nr);

#घोषणा DO_TESTCASE_2x3(desc, name)				\
	DO_TESTCASE_3(desc, name, 12);				\
	DO_TESTCASE_3(desc, name, 21);

#घोषणा DO_TESTCASE_2x6(desc, name)				\
	DO_TESTCASE_6I(desc, name, 12);				\
	DO_TESTCASE_6I(desc, name, 21);

#घोषणा DO_TESTCASE_6x2(desc, name)				\
	DO_TESTCASE_2I(desc, name, 123);			\
	DO_TESTCASE_2I(desc, name, 132);			\
	DO_TESTCASE_2I(desc, name, 213);			\
	DO_TESTCASE_2I(desc, name, 231);			\
	DO_TESTCASE_2I(desc, name, 312);			\
	DO_TESTCASE_2I(desc, name, 321);

#घोषणा DO_TESTCASE_6x2B(desc, name)				\
	DO_TESTCASE_2IB(desc, name, 123);			\
	DO_TESTCASE_2IB(desc, name, 132);			\
	DO_TESTCASE_2IB(desc, name, 213);			\
	DO_TESTCASE_2IB(desc, name, 231);			\
	DO_TESTCASE_2IB(desc, name, 312);			\
	DO_TESTCASE_2IB(desc, name, 321);

#घोषणा DO_TESTCASE_6x1RR(desc, name)				\
	DO_TESTCASE_1RR(desc, name, 123);			\
	DO_TESTCASE_1RR(desc, name, 132);			\
	DO_TESTCASE_1RR(desc, name, 213);			\
	DO_TESTCASE_1RR(desc, name, 231);			\
	DO_TESTCASE_1RR(desc, name, 312);			\
	DO_TESTCASE_1RR(desc, name, 321);

#घोषणा DO_TESTCASE_6x1RRB(desc, name)				\
	DO_TESTCASE_1RRB(desc, name, 123);			\
	DO_TESTCASE_1RRB(desc, name, 132);			\
	DO_TESTCASE_1RRB(desc, name, 213);			\
	DO_TESTCASE_1RRB(desc, name, 231);			\
	DO_TESTCASE_1RRB(desc, name, 312);			\
	DO_TESTCASE_1RRB(desc, name, 321);

#घोषणा DO_TESTCASE_6x6(desc, name)				\
	DO_TESTCASE_6I(desc, name, 123);			\
	DO_TESTCASE_6I(desc, name, 132);			\
	DO_TESTCASE_6I(desc, name, 213);			\
	DO_TESTCASE_6I(desc, name, 231);			\
	DO_TESTCASE_6I(desc, name, 312);			\
	DO_TESTCASE_6I(desc, name, 321);

#घोषणा DO_TESTCASE_6x6RW(desc, name)				\
	DO_TESTCASE_6IRW(desc, name, 123);			\
	DO_TESTCASE_6IRW(desc, name, 132);			\
	DO_TESTCASE_6IRW(desc, name, 213);			\
	DO_TESTCASE_6IRW(desc, name, 231);			\
	DO_TESTCASE_6IRW(desc, name, 312);			\
	DO_TESTCASE_6IRW(desc, name, 321);

अटल व्योम ww_test_fail_acquire(व्योम)
अणु
	पूर्णांक ret;

	WWAI(&t);
	t.stamp++;

	ret = WWL(&o, &t);

	अगर (WARN_ON(!o.ctx) ||
	    WARN_ON(ret))
		वापस;

	/* No lockdep test, pure API */
	ret = WWL(&o, &t);
	WARN_ON(ret != -EALREADY);

	ret = WWT(&o);
	WARN_ON(ret);

	t2 = t;
	t2.stamp++;
	ret = WWL(&o, &t2);
	WARN_ON(ret != -EDEADLK);
	WWU(&o);

	अगर (WWT(&o))
		WWU(&o);
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	अन्यथा
		DEBUG_LOCKS_WARN_ON(1);
#पूर्ण_अगर
पूर्ण

अटल व्योम ww_test_normal(व्योम)
अणु
	पूर्णांक ret;

	WWAI(&t);

	/*
	 * None of the ww_mutex codepaths should be taken in the 'normal'
	 * mutex calls. The easiest way to verअगरy this is by using the
	 * normal mutex calls, and making sure o.ctx is unmodअगरied.
	 */

	/* mutex_lock (and indirectly, mutex_lock_nested) */
	o.ctx = (व्योम *)~0UL;
	mutex_lock(&o.base);
	mutex_unlock(&o.base);
	WARN_ON(o.ctx != (व्योम *)~0UL);

	/* mutex_lock_पूर्णांकerruptible (and *_nested) */
	o.ctx = (व्योम *)~0UL;
	ret = mutex_lock_पूर्णांकerruptible(&o.base);
	अगर (!ret)
		mutex_unlock(&o.base);
	अन्यथा
		WARN_ON(1);
	WARN_ON(o.ctx != (व्योम *)~0UL);

	/* mutex_lock_समाप्तable (and *_nested) */
	o.ctx = (व्योम *)~0UL;
	ret = mutex_lock_समाप्तable(&o.base);
	अगर (!ret)
		mutex_unlock(&o.base);
	अन्यथा
		WARN_ON(1);
	WARN_ON(o.ctx != (व्योम *)~0UL);

	/* trylock, succeeding */
	o.ctx = (व्योम *)~0UL;
	ret = mutex_trylock(&o.base);
	WARN_ON(!ret);
	अगर (ret)
		mutex_unlock(&o.base);
	अन्यथा
		WARN_ON(1);
	WARN_ON(o.ctx != (व्योम *)~0UL);

	/* trylock, failing */
	o.ctx = (व्योम *)~0UL;
	mutex_lock(&o.base);
	ret = mutex_trylock(&o.base);
	WARN_ON(ret);
	mutex_unlock(&o.base);
	WARN_ON(o.ctx != (व्योम *)~0UL);

	/* nest_lock */
	o.ctx = (व्योम *)~0UL;
	mutex_lock_nest_lock(&o.base, &t);
	mutex_unlock(&o.base);
	WARN_ON(o.ctx != (व्योम *)~0UL);
पूर्ण

अटल व्योम ww_test_two_contexts(व्योम)
अणु
	WWAI(&t);
	WWAI(&t2);
पूर्ण

अटल व्योम ww_test_dअगरf_class(व्योम)
अणु
	WWAI(&t);
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	t.ww_class = शून्य;
#पूर्ण_अगर
	WWL(&o, &t);
पूर्ण

अटल व्योम ww_test_context_करोne_twice(व्योम)
अणु
	WWAI(&t);
	WWAD(&t);
	WWAD(&t);
	WWAF(&t);
पूर्ण

अटल व्योम ww_test_context_unlock_twice(व्योम)
अणु
	WWAI(&t);
	WWAD(&t);
	WWAF(&t);
	WWAF(&t);
पूर्ण

अटल व्योम ww_test_context_fini_early(व्योम)
अणु
	WWAI(&t);
	WWL(&o, &t);
	WWAD(&t);
	WWAF(&t);
पूर्ण

अटल व्योम ww_test_context_lock_after_करोne(व्योम)
अणु
	WWAI(&t);
	WWAD(&t);
	WWL(&o, &t);
पूर्ण

अटल व्योम ww_test_object_unlock_twice(व्योम)
अणु
	WWL1(&o);
	WWU(&o);
	WWU(&o);
पूर्ण

अटल व्योम ww_test_object_lock_unbalanced(व्योम)
अणु
	WWAI(&t);
	WWL(&o, &t);
	t.acquired = 0;
	WWU(&o);
	WWAF(&t);
पूर्ण

अटल व्योम ww_test_object_lock_stale_context(व्योम)
अणु
	WWAI(&t);
	o.ctx = &t2;
	WWL(&o, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_normal(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	o2.ctx = &t2;
	mutex_release(&o2.base.dep_map, _THIS_IP_);

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	o2.ctx = शून्य;
	mutex_acquire(&o2.base.dep_map, 0, 1, _THIS_IP_);
	mutex_unlock(&o2.base);
	WWU(&o);

	WWL(&o2, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_normal_slow(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, _THIS_IP_);
	o2.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	o2.ctx = शून्य;
	mutex_acquire(&o2.base.dep_map, 0, 1, _THIS_IP_);
	mutex_unlock(&o2.base);
	WWU(&o);

	ww_mutex_lock_slow(&o2, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_no_unlock(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	o2.ctx = &t2;
	mutex_release(&o2.base.dep_map, _THIS_IP_);

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	o2.ctx = शून्य;
	mutex_acquire(&o2.base.dep_map, 0, 1, _THIS_IP_);
	mutex_unlock(&o2.base);

	WWL(&o2, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_no_unlock_slow(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, _THIS_IP_);
	o2.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	o2.ctx = शून्य;
	mutex_acquire(&o2.base.dep_map, 0, 1, _THIS_IP_);
	mutex_unlock(&o2.base);

	ww_mutex_lock_slow(&o2, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_acquire_more(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, _THIS_IP_);
	o2.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	ret = WWL(&o3, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_acquire_more_slow(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, _THIS_IP_);
	o2.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	ww_mutex_lock_slow(&o3, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_acquire_more_edeadlk(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, _THIS_IP_);
	o2.ctx = &t2;

	mutex_lock(&o3.base);
	mutex_release(&o3.base.dep_map, _THIS_IP_);
	o3.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	ret = WWL(&o3, &t);
	WARN_ON(ret != -EDEADLK);
पूर्ण

अटल व्योम ww_test_edeadlk_acquire_more_edeadlk_slow(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, _THIS_IP_);
	o2.ctx = &t2;

	mutex_lock(&o3.base);
	mutex_release(&o3.base.dep_map, _THIS_IP_);
	o3.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);

	ww_mutex_lock_slow(&o3, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_acquire_wrong(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, _THIS_IP_);
	o2.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);
	अगर (!ret)
		WWU(&o2);

	WWU(&o);

	ret = WWL(&o3, &t);
पूर्ण

अटल व्योम ww_test_edeadlk_acquire_wrong_slow(व्योम)
अणु
	पूर्णांक ret;

	mutex_lock(&o2.base);
	mutex_release(&o2.base.dep_map, _THIS_IP_);
	o2.ctx = &t2;

	WWAI(&t);
	t2 = t;
	t2.stamp--;

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret != -EDEADLK);
	अगर (!ret)
		WWU(&o2);

	WWU(&o);

	ww_mutex_lock_slow(&o3, &t);
पूर्ण

अटल व्योम ww_test_spin_nest_unlocked(व्योम)
अणु
	spin_lock_nest_lock(&lock_A, &o.base);
	U(A);
पूर्ण

/* This is not a deadlock, because we have X1 to serialize Y1 and Y2 */
अटल व्योम ww_test_spin_nest_lock(व्योम)
अणु
	spin_lock(&lock_X1);
	spin_lock_nest_lock(&lock_Y1, &lock_X1);
	spin_lock(&lock_A);
	spin_lock_nest_lock(&lock_Y2, &lock_X1);
	spin_unlock(&lock_A);
	spin_unlock(&lock_Y2);
	spin_unlock(&lock_Y1);
	spin_unlock(&lock_X1);
पूर्ण

अटल व्योम ww_test_unneeded_slow(व्योम)
अणु
	WWAI(&t);

	ww_mutex_lock_slow(&o, &t);
पूर्ण

अटल व्योम ww_test_context_block(व्योम)
अणु
	पूर्णांक ret;

	WWAI(&t);

	ret = WWL(&o, &t);
	WARN_ON(ret);
	WWL1(&o2);
पूर्ण

अटल व्योम ww_test_context_try(व्योम)
अणु
	पूर्णांक ret;

	WWAI(&t);

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWT(&o2);
	WARN_ON(!ret);
	WWU(&o2);
	WWU(&o);
पूर्ण

अटल व्योम ww_test_context_context(व्योम)
अणु
	पूर्णांक ret;

	WWAI(&t);

	ret = WWL(&o, &t);
	WARN_ON(ret);

	ret = WWL(&o2, &t);
	WARN_ON(ret);

	WWU(&o2);
	WWU(&o);
पूर्ण

अटल व्योम ww_test_try_block(व्योम)
अणु
	bool ret;

	ret = WWT(&o);
	WARN_ON(!ret);

	WWL1(&o2);
	WWU(&o2);
	WWU(&o);
पूर्ण

अटल व्योम ww_test_try_try(व्योम)
अणु
	bool ret;

	ret = WWT(&o);
	WARN_ON(!ret);
	ret = WWT(&o2);
	WARN_ON(!ret);
	WWU(&o2);
	WWU(&o);
पूर्ण

अटल व्योम ww_test_try_context(व्योम)
अणु
	पूर्णांक ret;

	ret = WWT(&o);
	WARN_ON(!ret);

	WWAI(&t);

	ret = WWL(&o2, &t);
	WARN_ON(ret);
पूर्ण

अटल व्योम ww_test_block_block(व्योम)
अणु
	WWL1(&o);
	WWL1(&o2);
पूर्ण

अटल व्योम ww_test_block_try(व्योम)
अणु
	bool ret;

	WWL1(&o);
	ret = WWT(&o2);
	WARN_ON(!ret);
पूर्ण

अटल व्योम ww_test_block_context(व्योम)
अणु
	पूर्णांक ret;

	WWL1(&o);
	WWAI(&t);

	ret = WWL(&o2, &t);
	WARN_ON(ret);
पूर्ण

अटल व्योम ww_test_spin_block(व्योम)
अणु
	L(A);
	U(A);

	WWL1(&o);
	L(A);
	U(A);
	WWU(&o);

	L(A);
	WWL1(&o);
	WWU(&o);
	U(A);
पूर्ण

अटल व्योम ww_test_spin_try(व्योम)
अणु
	bool ret;

	L(A);
	U(A);

	ret = WWT(&o);
	WARN_ON(!ret);
	L(A);
	U(A);
	WWU(&o);

	L(A);
	ret = WWT(&o);
	WARN_ON(!ret);
	WWU(&o);
	U(A);
पूर्ण

अटल व्योम ww_test_spin_context(व्योम)
अणु
	पूर्णांक ret;

	L(A);
	U(A);

	WWAI(&t);

	ret = WWL(&o, &t);
	WARN_ON(ret);
	L(A);
	U(A);
	WWU(&o);

	L(A);
	ret = WWL(&o, &t);
	WARN_ON(ret);
	WWU(&o);
	U(A);
पूर्ण

अटल व्योम ww_tests(व्योम)
अणु
	prपूर्णांकk("  --------------------------------------------------------------------------\n");
	prपूर्णांकk("  | Wound/wait tests |\n");
	prपूर्णांकk("  ---------------------\n");

	prपूर्णांक_testname("ww api failures");
	करोtest(ww_test_fail_acquire, SUCCESS, LOCKTYPE_WW);
	करोtest(ww_test_normal, SUCCESS, LOCKTYPE_WW);
	करोtest(ww_test_unneeded_slow, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("ww contexts mixing");
	करोtest(ww_test_two_contexts, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_dअगरf_class, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("finishing ww context");
	करोtest(ww_test_context_करोne_twice, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_context_unlock_twice, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_context_fini_early, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_context_lock_after_करोne, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("locking mismatches");
	करोtest(ww_test_object_unlock_twice, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_object_lock_unbalanced, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_object_lock_stale_context, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("EDEADLK handling");
	करोtest(ww_test_edeadlk_normal, SUCCESS, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_normal_slow, SUCCESS, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_no_unlock, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_no_unlock_slow, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_acquire_more, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_acquire_more_slow, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_acquire_more_edeadlk, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_acquire_more_edeadlk_slow, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_acquire_wrong, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_edeadlk_acquire_wrong_slow, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("spinlock nest unlocked");
	करोtest(ww_test_spin_nest_unlocked, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("spinlock nest test");
	करोtest(ww_test_spin_nest_lock, SUCCESS, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांकk("  -----------------------------------------------------\n");
	prपूर्णांकk("                                 |block | try  |context|\n");
	prपूर्णांकk("  -----------------------------------------------------\n");

	prपूर्णांक_testname("context");
	करोtest(ww_test_context_block, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_context_try, SUCCESS, LOCKTYPE_WW);
	करोtest(ww_test_context_context, SUCCESS, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("try");
	करोtest(ww_test_try_block, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_try_try, SUCCESS, LOCKTYPE_WW);
	करोtest(ww_test_try_context, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("block");
	करोtest(ww_test_block_block, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_block_try, SUCCESS, LOCKTYPE_WW);
	करोtest(ww_test_block_context, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");

	prपूर्णांक_testname("spinlock");
	करोtest(ww_test_spin_block, FAILURE, LOCKTYPE_WW);
	करोtest(ww_test_spin_try, SUCCESS, LOCKTYPE_WW);
	करोtest(ww_test_spin_context, FAILURE, LOCKTYPE_WW);
	pr_cont("\n");
पूर्ण


/*
 * <in hardirq handler>
 * पढ़ो_lock(&A);
 *			<hardirq disable>
 *			spin_lock(&B);
 * spin_lock(&B);
 *			पढ़ो_lock(&A);
 *
 * is a deadlock.
 */
अटल व्योम queued_पढ़ो_lock_hardirq_RE_Er(व्योम)
अणु
	HARसूचीQ_ENTER();
	पढ़ो_lock(&rwlock_A);
	LOCK(B);
	UNLOCK(B);
	पढ़ो_unlock(&rwlock_A);
	HARसूचीQ_EXIT();

	HARसूचीQ_DISABLE();
	LOCK(B);
	पढ़ो_lock(&rwlock_A);
	पढ़ो_unlock(&rwlock_A);
	UNLOCK(B);
	HARसूचीQ_ENABLE();
पूर्ण

/*
 * <in hardirq handler>
 * spin_lock(&B);
 *			<hardirq disable>
 *			पढ़ो_lock(&A);
 * पढ़ो_lock(&A);
 *			spin_lock(&B);
 *
 * is not a deadlock.
 */
अटल व्योम queued_पढ़ो_lock_hardirq_ER_rE(व्योम)
अणु
	HARसूचीQ_ENTER();
	LOCK(B);
	पढ़ो_lock(&rwlock_A);
	पढ़ो_unlock(&rwlock_A);
	UNLOCK(B);
	HARसूचीQ_EXIT();

	HARसूचीQ_DISABLE();
	पढ़ो_lock(&rwlock_A);
	LOCK(B);
	UNLOCK(B);
	पढ़ो_unlock(&rwlock_A);
	HARसूचीQ_ENABLE();
पूर्ण

/*
 * <hardirq disable>
 * spin_lock(&B);
 *			पढ़ो_lock(&A);
 *			<in hardirq handler>
 *			spin_lock(&B);
 * पढ़ो_lock(&A);
 *
 * is a deadlock. Because the two पढ़ो_lock()s are both non-recursive पढ़ोers.
 */
अटल व्योम queued_पढ़ो_lock_hardirq_inversion(व्योम)
अणु

	HARसूचीQ_ENTER();
	LOCK(B);
	UNLOCK(B);
	HARसूचीQ_EXIT();

	HARसूचीQ_DISABLE();
	LOCK(B);
	पढ़ो_lock(&rwlock_A);
	पढ़ो_unlock(&rwlock_A);
	UNLOCK(B);
	HARसूचीQ_ENABLE();

	पढ़ो_lock(&rwlock_A);
	पढ़ो_unlock(&rwlock_A);
पूर्ण

अटल व्योम queued_पढ़ो_lock_tests(व्योम)
अणु
	prपूर्णांकk("  --------------------------------------------------------------------------\n");
	prपूर्णांकk("  | queued read lock tests |\n");
	prपूर्णांकk("  ---------------------------\n");
	prपूर्णांक_testname("hardirq read-lock/lock-read");
	करोtest(queued_पढ़ो_lock_hardirq_RE_Er, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("\n");

	prपूर्णांक_testname("hardirq lock-read/read-lock");
	करोtest(queued_पढ़ो_lock_hardirq_ER_rE, SUCCESS, LOCKTYPE_RWLOCK);
	pr_cont("\n");

	prपूर्णांक_testname("hardirq inversion");
	करोtest(queued_पढ़ो_lock_hardirq_inversion, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("\n");
पूर्ण

अटल व्योम fs_reclaim_correct_nesting(व्योम)
अणु
	fs_reclaim_acquire(GFP_KERNEL);
	might_alloc(GFP_NOFS);
	fs_reclaim_release(GFP_KERNEL);
पूर्ण

अटल व्योम fs_reclaim_wrong_nesting(व्योम)
अणु
	fs_reclaim_acquire(GFP_KERNEL);
	might_alloc(GFP_KERNEL);
	fs_reclaim_release(GFP_KERNEL);
पूर्ण

अटल व्योम fs_reclaim_रक्षित_nesting(व्योम)
अणु
	अचिन्हित पूर्णांक flags;

	fs_reclaim_acquire(GFP_KERNEL);
	flags = meदो_स्मृति_nofs_save();
	might_alloc(GFP_KERNEL);
	meदो_स्मृति_nofs_restore(flags);
	fs_reclaim_release(GFP_KERNEL);
पूर्ण

अटल व्योम fs_reclaim_tests(व्योम)
अणु
	prपूर्णांकk("  --------------------\n");
	prपूर्णांकk("  | fs_reclaim tests |\n");
	prपूर्णांकk("  --------------------\n");

	prपूर्णांक_testname("correct nesting");
	करोtest(fs_reclaim_correct_nesting, SUCCESS, 0);
	pr_cont("\n");

	prपूर्णांक_testname("wrong nesting");
	करोtest(fs_reclaim_wrong_nesting, FAILURE, 0);
	pr_cont("\n");

	prपूर्णांक_testname("protected nesting");
	करोtest(fs_reclaim_रक्षित_nesting, SUCCESS, 0);
	pr_cont("\n");
पूर्ण

#घोषणा __guard(cleanup) __maybe_unused __attribute__((__cleanup__(cleanup)))

अटल व्योम hardirq_निकास(पूर्णांक *_)
अणु
	HARसूचीQ_EXIT();
पूर्ण

#घोषणा HARसूचीQ_CONTEXT(name, ...)					\
	पूर्णांक hardirq_guard_##name __guard(hardirq_निकास);			\
	HARसूचीQ_ENTER();

#घोषणा NOTTHREADED_HARसूचीQ_CONTEXT(name, ...)				\
	पूर्णांक notthपढ़ोed_hardirq_guard_##name __guard(hardirq_निकास);	\
	local_irq_disable();						\
	__irq_enter();							\
	WARN_ON(!in_irq());

अटल व्योम softirq_निकास(पूर्णांक *_)
अणु
	SOFTIRQ_EXIT();
पूर्ण

#घोषणा SOFTIRQ_CONTEXT(name, ...)				\
	पूर्णांक softirq_guard_##name __guard(softirq_निकास);		\
	SOFTIRQ_ENTER();

अटल व्योम rcu_निकास(पूर्णांक *_)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

#घोषणा RCU_CONTEXT(name, ...)					\
	पूर्णांक rcu_guard_##name __guard(rcu_निकास);			\
	rcu_पढ़ो_lock();

अटल व्योम rcu_bh_निकास(पूर्णांक *_)
अणु
	rcu_पढ़ो_unlock_bh();
पूर्ण

#घोषणा RCU_BH_CONTEXT(name, ...)				\
	पूर्णांक rcu_bh_guard_##name __guard(rcu_bh_निकास);		\
	rcu_पढ़ो_lock_bh();

अटल व्योम rcu_sched_निकास(पूर्णांक *_)
अणु
	rcu_पढ़ो_unlock_sched();
पूर्ण

#घोषणा RCU_SCHED_CONTEXT(name, ...)				\
	पूर्णांक rcu_sched_guard_##name __guard(rcu_sched_निकास);	\
	rcu_पढ़ो_lock_sched();

अटल व्योम rcu_callback_निकास(पूर्णांक *_)
अणु
	rcu_lock_release(&rcu_callback_map);
पूर्ण

#घोषणा RCU_CALLBACK_CONTEXT(name, ...)					\
	पूर्णांक rcu_callback_guard_##name __guard(rcu_callback_निकास);	\
	rcu_lock_acquire(&rcu_callback_map);


अटल व्योम raw_spinlock_निकास(raw_spinlock_t **lock)
अणु
	raw_spin_unlock(*lock);
पूर्ण

#घोषणा RAW_SPINLOCK_CONTEXT(name, lock)						\
	raw_spinlock_t *raw_spinlock_guard_##name __guard(raw_spinlock_निकास) = &(lock);	\
	raw_spin_lock(&(lock));

अटल व्योम spinlock_निकास(spinlock_t **lock)
अणु
	spin_unlock(*lock);
पूर्ण

#घोषणा SPINLOCK_CONTEXT(name, lock)						\
	spinlock_t *spinlock_guard_##name __guard(spinlock_निकास) = &(lock);	\
	spin_lock(&(lock));

अटल व्योम mutex_निकास(काष्ठा mutex **lock)
अणु
	mutex_unlock(*lock);
पूर्ण

#घोषणा MUTEX_CONTEXT(name, lock)					\
	काष्ठा mutex *mutex_guard_##name __guard(mutex_निकास) = &(lock);	\
	mutex_lock(&(lock));

#घोषणा GENERATE_2_CONTEXT_TESTCASE(outer, outer_lock, inner, inner_lock)	\
										\
अटल व्योम __maybe_unused inner##_in_##outer(व्योम)				\
अणु										\
	outer##_CONTEXT(_, outer_lock);						\
	अणु									\
		inner##_CONTEXT(_, inner_lock);					\
	पूर्ण									\
पूर्ण

/*
 * रुको contexts (considering PREEMPT_RT)
 *
 * o: inner is allowed in outer
 * x: inner is disallowed in outer
 *
 *       \  inner |  RCU  | RAW_SPIN | SPIN | MUTEX
 * outer  \       |       |          |      |
 * ---------------+-------+----------+------+-------
 * HARसूचीQ        |   o   |    o     |  o   |  x
 * ---------------+-------+----------+------+-------
 * NOTTHREADED_IRQ|   o   |    o     |  x   |  x
 * ---------------+-------+----------+------+-------
 * SOFTIRQ        |   o   |    o     |  o   |  x
 * ---------------+-------+----------+------+-------
 * RCU            |   o   |    o     |  o   |  x
 * ---------------+-------+----------+------+-------
 * RCU_BH         |   o   |    o     |  o   |  x
 * ---------------+-------+----------+------+-------
 * RCU_CALLBACK   |   o   |    o     |  o   |  x
 * ---------------+-------+----------+------+-------
 * RCU_SCHED      |   o   |    o     |  x   |  x
 * ---------------+-------+----------+------+-------
 * RAW_SPIN       |   o   |    o     |  x   |  x
 * ---------------+-------+----------+------+-------
 * SPIN           |   o   |    o     |  o   |  x
 * ---------------+-------+----------+------+-------
 * MUTEX          |   o   |    o     |  o   |  o
 * ---------------+-------+----------+------+-------
 */

#घोषणा GENERATE_2_CONTEXT_TESTCASE_FOR_ALL_OUTER(inner, inner_lock)		\
GENERATE_2_CONTEXT_TESTCASE(HARसूचीQ, , inner, inner_lock)			\
GENERATE_2_CONTEXT_TESTCASE(NOTTHREADED_HARसूचीQ, , inner, inner_lock)		\
GENERATE_2_CONTEXT_TESTCASE(SOFTIRQ, , inner, inner_lock)			\
GENERATE_2_CONTEXT_TESTCASE(RCU, , inner, inner_lock)				\
GENERATE_2_CONTEXT_TESTCASE(RCU_BH, , inner, inner_lock)			\
GENERATE_2_CONTEXT_TESTCASE(RCU_CALLBACK, , inner, inner_lock)			\
GENERATE_2_CONTEXT_TESTCASE(RCU_SCHED, , inner, inner_lock)			\
GENERATE_2_CONTEXT_TESTCASE(RAW_SPINLOCK, raw_lock_A, inner, inner_lock)	\
GENERATE_2_CONTEXT_TESTCASE(SPINLOCK, lock_A, inner, inner_lock)		\
GENERATE_2_CONTEXT_TESTCASE(MUTEX, mutex_A, inner, inner_lock)

GENERATE_2_CONTEXT_TESTCASE_FOR_ALL_OUTER(RCU, )
GENERATE_2_CONTEXT_TESTCASE_FOR_ALL_OUTER(RAW_SPINLOCK, raw_lock_B)
GENERATE_2_CONTEXT_TESTCASE_FOR_ALL_OUTER(SPINLOCK, lock_B)
GENERATE_2_CONTEXT_TESTCASE_FOR_ALL_OUTER(MUTEX, mutex_B)

/* the outer context allows all kinds of preemption */
#घोषणा DO_CONTEXT_TESTCASE_OUTER_PREEMPTIBLE(outer)			\
	करोtest(RCU_in_##outer, SUCCESS, LOCKTYPE_RWLOCK);		\
	करोtest(RAW_SPINLOCK_in_##outer, SUCCESS, LOCKTYPE_SPIN);	\
	करोtest(SPINLOCK_in_##outer, SUCCESS, LOCKTYPE_SPIN);		\
	करोtest(MUTEX_in_##outer, SUCCESS, LOCKTYPE_MUTEX);		\

/*
 * the outer context only allows the preemption पूर्णांकroduced by spinlock_t (which
 * is a sleepable lock क्रम PREEMPT_RT)
 */
#घोषणा DO_CONTEXT_TESTCASE_OUTER_LIMITED_PREEMPTIBLE(outer)		\
	करोtest(RCU_in_##outer, SUCCESS, LOCKTYPE_RWLOCK);		\
	करोtest(RAW_SPINLOCK_in_##outer, SUCCESS, LOCKTYPE_SPIN);	\
	करोtest(SPINLOCK_in_##outer, SUCCESS, LOCKTYPE_SPIN);		\
	करोtest(MUTEX_in_##outer, FAILURE, LOCKTYPE_MUTEX);		\

/* the outer करोesn't allows any kind of preemption */
#घोषणा DO_CONTEXT_TESTCASE_OUTER_NOT_PREEMPTIBLE(outer)			\
	करोtest(RCU_in_##outer, SUCCESS, LOCKTYPE_RWLOCK);		\
	करोtest(RAW_SPINLOCK_in_##outer, SUCCESS, LOCKTYPE_SPIN);	\
	करोtest(SPINLOCK_in_##outer, FAILURE, LOCKTYPE_SPIN);		\
	करोtest(MUTEX_in_##outer, FAILURE, LOCKTYPE_MUTEX);		\

अटल व्योम रुको_context_tests(व्योम)
अणु
	prपूर्णांकk("  --------------------------------------------------------------------------\n");
	prपूर्णांकk("  | wait context tests |\n");
	prपूर्णांकk("  --------------------------------------------------------------------------\n");
	prपूर्णांकk("                                 | rcu  | raw  | spin |mutex |\n");
	prपूर्णांकk("  --------------------------------------------------------------------------\n");
	prपूर्णांक_testname("in hardirq context");
	DO_CONTEXT_TESTCASE_OUTER_LIMITED_PREEMPTIBLE(HARसूचीQ);
	pr_cont("\n");

	prपूर्णांक_testname("in hardirq context (not threaded)");
	DO_CONTEXT_TESTCASE_OUTER_NOT_PREEMPTIBLE(NOTTHREADED_HARसूचीQ);
	pr_cont("\n");

	prपूर्णांक_testname("in softirq context");
	DO_CONTEXT_TESTCASE_OUTER_LIMITED_PREEMPTIBLE(SOFTIRQ);
	pr_cont("\n");

	prपूर्णांक_testname("in RCU context");
	DO_CONTEXT_TESTCASE_OUTER_LIMITED_PREEMPTIBLE(RCU);
	pr_cont("\n");

	prपूर्णांक_testname("in RCU-bh context");
	DO_CONTEXT_TESTCASE_OUTER_LIMITED_PREEMPTIBLE(RCU_BH);
	pr_cont("\n");

	prपूर्णांक_testname("in RCU callback context");
	DO_CONTEXT_TESTCASE_OUTER_LIMITED_PREEMPTIBLE(RCU_CALLBACK);
	pr_cont("\n");

	prपूर्णांक_testname("in RCU-sched context");
	DO_CONTEXT_TESTCASE_OUTER_NOT_PREEMPTIBLE(RCU_SCHED);
	pr_cont("\n");

	prपूर्णांक_testname("in RAW_SPINLOCK context");
	DO_CONTEXT_TESTCASE_OUTER_NOT_PREEMPTIBLE(RAW_SPINLOCK);
	pr_cont("\n");

	prपूर्णांक_testname("in SPINLOCK context");
	DO_CONTEXT_TESTCASE_OUTER_LIMITED_PREEMPTIBLE(SPINLOCK);
	pr_cont("\n");

	prपूर्णांक_testname("in MUTEX context");
	DO_CONTEXT_TESTCASE_OUTER_PREEMPTIBLE(MUTEX);
	pr_cont("\n");
पूर्ण

अटल व्योम local_lock_2(व्योम)
अणु
	local_lock_acquire(&local_A);	/* IRQ-ON */
	local_lock_release(&local_A);

	HARसूचीQ_ENTER();
	spin_lock(&lock_A);		/* IN-IRQ */
	spin_unlock(&lock_A);
	HARसूचीQ_EXIT()

	HARसूचीQ_DISABLE();
	spin_lock(&lock_A);
	local_lock_acquire(&local_A);	/* IN-IRQ <-> IRQ-ON cycle, false */
	local_lock_release(&local_A);
	spin_unlock(&lock_A);
	HARसूचीQ_ENABLE();
पूर्ण

अटल व्योम local_lock_3A(व्योम)
अणु
	local_lock_acquire(&local_A);	/* IRQ-ON */
	spin_lock(&lock_B);		/* IRQ-ON */
	spin_unlock(&lock_B);
	local_lock_release(&local_A);

	HARसूचीQ_ENTER();
	spin_lock(&lock_A);		/* IN-IRQ */
	spin_unlock(&lock_A);
	HARसूचीQ_EXIT()

	HARसूचीQ_DISABLE();
	spin_lock(&lock_A);
	local_lock_acquire(&local_A);	/* IN-IRQ <-> IRQ-ON cycle only अगर we count local_lock(), false */
	local_lock_release(&local_A);
	spin_unlock(&lock_A);
	HARसूचीQ_ENABLE();
पूर्ण

अटल व्योम local_lock_3B(व्योम)
अणु
	local_lock_acquire(&local_A);	/* IRQ-ON */
	spin_lock(&lock_B);		/* IRQ-ON */
	spin_unlock(&lock_B);
	local_lock_release(&local_A);

	HARसूचीQ_ENTER();
	spin_lock(&lock_A);		/* IN-IRQ */
	spin_unlock(&lock_A);
	HARसूचीQ_EXIT()

	HARसूचीQ_DISABLE();
	spin_lock(&lock_A);
	local_lock_acquire(&local_A);	/* IN-IRQ <-> IRQ-ON cycle only अगर we count local_lock(), false */
	local_lock_release(&local_A);
	spin_unlock(&lock_A);
	HARसूचीQ_ENABLE();

	HARसूचीQ_DISABLE();
	spin_lock(&lock_A);
	spin_lock(&lock_B);		/* IN-IRQ <-> IRQ-ON cycle, true */
	spin_unlock(&lock_B);
	spin_unlock(&lock_A);
	HARसूचीQ_DISABLE();

पूर्ण

अटल व्योम local_lock_tests(व्योम)
अणु
	prपूर्णांकk("  --------------------------------------------------------------------------\n");
	prपूर्णांकk("  | local_lock tests |\n");
	prपूर्णांकk("  ---------------------\n");

	prपूर्णांक_testname("local_lock inversion  2");
	करोtest(local_lock_2, SUCCESS, LOCKTYPE_LL);
	pr_cont("\n");

	prपूर्णांक_testname("local_lock inversion 3A");
	करोtest(local_lock_3A, SUCCESS, LOCKTYPE_LL);
	pr_cont("\n");

	prपूर्णांक_testname("local_lock inversion 3B");
	करोtest(local_lock_3B, FAILURE, LOCKTYPE_LL);
	pr_cont("\n");
पूर्ण

व्योम locking_selftest(व्योम)
अणु
	/*
	 * Got a locking failure beक्रमe the selftest ran?
	 */
	अगर (!debug_locks) अणु
		prपूर्णांकk("----------------------------------\n");
		prपूर्णांकk("| Locking API testsuite disabled |\n");
		prपूर्णांकk("----------------------------------\n");
		वापस;
	पूर्ण

	/*
	 * treats पढ़ो_lock() as recursive पढ़ो locks क्रम testing purpose
	 */
	क्रमce_पढ़ो_lock_recursive = 1;

	/*
	 * Run the testsuite:
	 */
	prपूर्णांकk("------------------------\n");
	prपूर्णांकk("| Locking API testsuite:\n");
	prपूर्णांकk("----------------------------------------------------------------------------\n");
	prपूर्णांकk("                                 | spin |wlock |rlock |mutex | wsem | rsem |\n");
	prपूर्णांकk("  --------------------------------------------------------------------------\n");

	init_shared_classes();
	lockdep_set_selftest_task(current);

	DO_TESTCASE_6R("A-A deadlock", AA);
	DO_TESTCASE_6R("A-B-B-A deadlock", ABBA);
	DO_TESTCASE_6R("A-B-B-C-C-A deadlock", ABBCCA);
	DO_TESTCASE_6R("A-B-C-A-B-C deadlock", ABCABC);
	DO_TESTCASE_6R("A-B-B-C-C-D-D-A deadlock", ABBCCDDA);
	DO_TESTCASE_6R("A-B-C-D-B-D-D-A deadlock", ABCDBDDA);
	DO_TESTCASE_6R("A-B-C-D-B-C-D-A deadlock", ABCDBCDA);
	DO_TESTCASE_6("double unlock", द्विगुन_unlock);
	DO_TESTCASE_6("initialize held", init_held);

	prपूर्णांकk("  --------------------------------------------------------------------------\n");
	prपूर्णांक_testname("recursive read-lock");
	pr_cont("             |");
	करोtest(rlock_AA1, SUCCESS, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	करोtest(rsem_AA1, FAILURE, LOCKTYPE_RWSEM);
	pr_cont("\n");

	prपूर्णांक_testname("recursive read-lock #2");
	pr_cont("             |");
	करोtest(rlock_AA1B, SUCCESS, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	करोtest(rsem_AA1B, FAILURE, LOCKTYPE_RWSEM);
	pr_cont("\n");

	prपूर्णांक_testname("mixed read-write-lock");
	pr_cont("             |");
	करोtest(rlock_AA2, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	करोtest(rsem_AA2, FAILURE, LOCKTYPE_RWSEM);
	pr_cont("\n");

	prपूर्णांक_testname("mixed write-read-lock");
	pr_cont("             |");
	करोtest(rlock_AA3, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	करोtest(rsem_AA3, FAILURE, LOCKTYPE_RWSEM);
	pr_cont("\n");

	prपूर्णांक_testname("mixed read-lock/lock-write ABBA");
	pr_cont("             |");
	करोtest(rlock_ABBA1, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	करोtest(rwsem_ABBA1, FAILURE, LOCKTYPE_RWSEM);

	prपूर्णांक_testname("mixed read-lock/lock-read ABBA");
	pr_cont("             |");
	करोtest(rlock_ABBA2, SUCCESS, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	करोtest(rwsem_ABBA2, FAILURE, LOCKTYPE_RWSEM);

	prपूर्णांक_testname("mixed write-lock/lock-write ABBA");
	pr_cont("             |");
	करोtest(rlock_ABBA3, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	करोtest(rwsem_ABBA3, FAILURE, LOCKTYPE_RWSEM);

	prपूर्णांक_testname("chain cached mixed R-L/L-W ABBA");
	pr_cont("             |");
	करोtest(rlock_chaincache_ABBA1, FAILURE, LOCKTYPE_RWLOCK);

	DO_TESTCASE_6x1RRB("rlock W1R2/W2R3/W3R1", W1R2_W2R3_W3R1);
	DO_TESTCASE_6x1RRB("rlock W1W2/R2R3/W3R1", W1W2_R2R3_W3R1);
	DO_TESTCASE_6x1RR("rlock W1W2/R2R3/R3W1", W1W2_R2R3_R3W1);
	DO_TESTCASE_6x1RR("rlock W1R2/R2R3/W3W1", W1R2_R2R3_W3W1);

	prपूर्णांकk("  --------------------------------------------------------------------------\n");

	/*
	 * irq-context testहालs:
	 */
	DO_TESTCASE_2x6("irqs-on + irq-safe-A", irqsafe1);
	DO_TESTCASE_2x3("sirq-safe-A => hirqs-on", irqsafe2A);
	DO_TESTCASE_2x6("safe-A + irqs-on", irqsafe2B);
	DO_TESTCASE_6x6("safe-A + unsafe-B #1", irqsafe3);
	DO_TESTCASE_6x6("safe-A + unsafe-B #2", irqsafe4);
	DO_TESTCASE_6x6RW("irq lock-inversion", irq_inversion);

	DO_TESTCASE_6x2x2RW("irq read-recursion", irq_पढ़ो_recursion);
	DO_TESTCASE_6x2x2RW("irq read-recursion #2", irq_पढ़ो_recursion2);
	DO_TESTCASE_6x2x2RW("irq read-recursion #3", irq_पढ़ो_recursion3);

	ww_tests();

	क्रमce_पढ़ो_lock_recursive = 0;
	/*
	 * queued_पढ़ो_lock() specअगरic test हालs can be put here
	 */
	अगर (IS_ENABLED(CONFIG_QUEUED_RWLOCKS))
		queued_पढ़ो_lock_tests();

	fs_reclaim_tests();

	/* Wait context test हालs that are specअगरic क्रम RAW_LOCK_NESTING */
	अगर (IS_ENABLED(CONFIG_PROVE_RAW_LOCK_NESTING))
		रुको_context_tests();

	local_lock_tests();

	अगर (unexpected_testहाल_failures) अणु
		prपूर्णांकk("-----------------------------------------------------------------\n");
		debug_locks = 0;
		prपूर्णांकk("BUG: %3d unexpected failures (out of %3d) - debugging disabled! |\n",
			unexpected_testहाल_failures, testहाल_total);
		prपूर्णांकk("-----------------------------------------------------------------\n");
	पूर्ण अन्यथा अगर (expected_testहाल_failures && testहाल_successes) अणु
		prपूर्णांकk("--------------------------------------------------------\n");
		prपूर्णांकk("%3d out of %3d testcases failed, as expected. |\n",
			expected_testहाल_failures, testहाल_total);
		prपूर्णांकk("----------------------------------------------------\n");
		debug_locks = 1;
	पूर्ण अन्यथा अगर (expected_testहाल_failures && !testहाल_successes) अणु
		prपूर्णांकk("--------------------------------------------------------\n");
		prपूर्णांकk("All %3d testcases failed, as expected. |\n",
			expected_testहाल_failures);
		prपूर्णांकk("----------------------------------------\n");
		debug_locks = 1;
	पूर्ण अन्यथा अणु
		prपूर्णांकk("-------------------------------------------------------\n");
		prपूर्णांकk("Good, all %3d testcases passed! |\n",
			testहाल_successes);
		prपूर्णांकk("---------------------------------\n");
		debug_locks = 1;
	पूर्ण
	lockdep_set_selftest_task(शून्य);
	debug_locks_silent = 0;
पूर्ण
