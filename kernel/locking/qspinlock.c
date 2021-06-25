<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Queued spinlock
 *
 * (C) Copyright 2013-2015 Hewlett-Packard Development Company, L.P.
 * (C) Copyright 2013-2014,2018 Red Hat, Inc.
 * (C) Copyright 2015 Intel Corp.
 * (C) Copyright 2015 Hewlett-Packard Enterprise Development LP
 *
 * Authors: Waiman Long <दीर्घman@redhat.com>
 *          Peter Zijlstra <peterz@infradead.org>
 */

#अगर_अघोषित _GEN_PV_LOCK_SLOWPATH

#समावेश <linux/smp.h>
#समावेश <linux/bug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/mutex.h>
#समावेश <linux/prefetch.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/qspinlock.h>

/*
 * Include queued spinlock statistics code
 */
#समावेश "qspinlock_stat.h"

/*
 * The basic principle of a queue-based spinlock can best be understood
 * by studying a classic queue-based spinlock implementation called the
 * MCS lock. A copy of the original MCS lock paper ("Algorithms क्रम Scalable
 * Synchronization on Shared-Memory Multiprocessors by Mellor-Crummey and
 * Scott") is available at
 *
 * https://bugzilla.kernel.org/show_bug.cgi?id=206115
 *
 * This queued spinlock implementation is based on the MCS lock, however to
 * make it fit the 4 bytes we assume spinlock_t to be, and preserve its
 * existing API, we must modअगरy it somehow.
 *
 * In particular; where the traditional MCS lock consists of a tail poपूर्णांकer
 * (8 bytes) and needs the next poपूर्णांकer (another 8 bytes) of its own node to
 * unlock the next pending (next->locked), we compress both these: अणुtail,
 * next->lockedपूर्ण पूर्णांकo a single u32 value.
 *
 * Since a spinlock disables recursion of its own context and there is a limit
 * to the contexts that can nest; namely: task, softirq, hardirq, nmi. As there
 * are at most 4 nesting levels, it can be encoded by a 2-bit number. Now
 * we can encode the tail by combining the 2-bit nesting level with the cpu
 * number. With one byte क्रम the lock value and 3 bytes क्रम the tail, only a
 * 32-bit word is now needed. Even though we only need 1 bit क्रम the lock,
 * we extend it to a full byte to achieve better perक्रमmance क्रम architectures
 * that support atomic byte ग_लिखो.
 *
 * We also change the first spinner to spin on the lock bit instead of its
 * node; whereby aव्योमing the need to carry a node from lock to unlock, and
 * preserving existing lock API. This also makes the unlock code simpler and
 * faster.
 *
 * N.B. The current implementation only supports architectures that allow
 *      atomic operations on smaller 8-bit and 16-bit data types.
 *
 */

#समावेश "mcs_spinlock.h"
#घोषणा MAX_NODES	4

/*
 * On 64-bit architectures, the mcs_spinlock काष्ठाure will be 16 bytes in
 * size and four of them will fit nicely in one 64-byte cacheline. For
 * pvqspinlock, however, we need more space क्रम extra data. To accommodate
 * that, we insert two more दीर्घ words to pad it up to 32 bytes. IOW, only
 * two of them can fit in a cacheline in this हाल. That is OK as it is rare
 * to have more than 2 levels of slowpath nesting in actual use. We करोn't
 * want to penalize pvqspinlocks to optimize क्रम a rare हाल in native
 * qspinlocks.
 */
काष्ठा qnode अणु
	काष्ठा mcs_spinlock mcs;
#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
	दीर्घ reserved[2];
#पूर्ण_अगर
पूर्ण;

/*
 * The pending bit spinning loop count.
 * This heuristic is used to limit the number of lockword accesses
 * made by atomic_cond_पढ़ो_relaxed when रुकोing क्रम the lock to
 * transition out of the "== _Q_PENDING_VAL" state. We करोn't spin
 * indefinitely because there's no guarantee that we'll make क्रमward
 * progress.
 */
#अगर_अघोषित _Q_PENDING_LOOPS
#घोषणा _Q_PENDING_LOOPS	1
#पूर्ण_अगर

/*
 * Per-CPU queue node काष्ठाures; we can never have more than 4 nested
 * contexts: task, softirq, hardirq, nmi.
 *
 * Exactly fits one 64-byte cacheline on a 64-bit architecture.
 *
 * PV द्विगुनs the storage and uses the second cacheline क्रम PV state.
 */
अटल DEFINE_PER_CPU_ALIGNED(काष्ठा qnode, qnodes[MAX_NODES]);

/*
 * We must be able to distinguish between no-tail and the tail at 0:0,
 * thereक्रमe increment the cpu number by one.
 */

अटल अंतरभूत __pure u32 encode_tail(पूर्णांक cpu, पूर्णांक idx)
अणु
	u32 tail;

	tail  = (cpu + 1) << _Q_TAIL_CPU_OFFSET;
	tail |= idx << _Q_TAIL_IDX_OFFSET; /* assume < 4 */

	वापस tail;
पूर्ण

अटल अंतरभूत __pure काष्ठा mcs_spinlock *decode_tail(u32 tail)
अणु
	पूर्णांक cpu = (tail >> _Q_TAIL_CPU_OFFSET) - 1;
	पूर्णांक idx = (tail &  _Q_TAIL_IDX_MASK) >> _Q_TAIL_IDX_OFFSET;

	वापस per_cpu_ptr(&qnodes[idx].mcs, cpu);
पूर्ण

अटल अंतरभूत __pure
काष्ठा mcs_spinlock *grab_mcs_node(काष्ठा mcs_spinlock *base, पूर्णांक idx)
अणु
	वापस &((काष्ठा qnode *)base + idx)->mcs;
पूर्ण

#घोषणा _Q_LOCKED_PENDING_MASK (_Q_LOCKED_MASK | _Q_PENDING_MASK)

#अगर _Q_PENDING_BITS == 8
/**
 * clear_pending - clear the pending bit.
 * @lock: Poपूर्णांकer to queued spinlock काष्ठाure
 *
 * *,1,* -> *,0,*
 */
अटल __always_अंतरभूत व्योम clear_pending(काष्ठा qspinlock *lock)
अणु
	WRITE_ONCE(lock->pending, 0);
पूर्ण

/**
 * clear_pending_set_locked - take ownership and clear the pending bit.
 * @lock: Poपूर्णांकer to queued spinlock काष्ठाure
 *
 * *,1,0 -> *,0,1
 *
 * Lock stealing is not allowed अगर this function is used.
 */
अटल __always_अंतरभूत व्योम clear_pending_set_locked(काष्ठा qspinlock *lock)
अणु
	WRITE_ONCE(lock->locked_pending, _Q_LOCKED_VAL);
पूर्ण

/*
 * xchg_tail - Put in the new queue tail code word & retrieve previous one
 * @lock : Poपूर्णांकer to queued spinlock काष्ठाure
 * @tail : The new queue tail code word
 * Return: The previous queue tail code word
 *
 * xchg(lock, tail), which heads an address dependency
 *
 * p,*,* -> n,*,* ; prev = xchg(lock, node)
 */
अटल __always_अंतरभूत u32 xchg_tail(काष्ठा qspinlock *lock, u32 tail)
अणु
	/*
	 * We can use relaxed semantics since the caller ensures that the
	 * MCS node is properly initialized beक्रमe updating the tail.
	 */
	वापस (u32)xchg_relaxed(&lock->tail,
				 tail >> _Q_TAIL_OFFSET) << _Q_TAIL_OFFSET;
पूर्ण

#अन्यथा /* _Q_PENDING_BITS == 8 */

/**
 * clear_pending - clear the pending bit.
 * @lock: Poपूर्णांकer to queued spinlock काष्ठाure
 *
 * *,1,* -> *,0,*
 */
अटल __always_अंतरभूत व्योम clear_pending(काष्ठा qspinlock *lock)
अणु
	atomic_andnot(_Q_PENDING_VAL, &lock->val);
पूर्ण

/**
 * clear_pending_set_locked - take ownership and clear the pending bit.
 * @lock: Poपूर्णांकer to queued spinlock काष्ठाure
 *
 * *,1,0 -> *,0,1
 */
अटल __always_अंतरभूत व्योम clear_pending_set_locked(काष्ठा qspinlock *lock)
अणु
	atomic_add(-_Q_PENDING_VAL + _Q_LOCKED_VAL, &lock->val);
पूर्ण

/**
 * xchg_tail - Put in the new queue tail code word & retrieve previous one
 * @lock : Poपूर्णांकer to queued spinlock काष्ठाure
 * @tail : The new queue tail code word
 * Return: The previous queue tail code word
 *
 * xchg(lock, tail)
 *
 * p,*,* -> n,*,* ; prev = xchg(lock, node)
 */
अटल __always_अंतरभूत u32 xchg_tail(काष्ठा qspinlock *lock, u32 tail)
अणु
	u32 old, new, val = atomic_पढ़ो(&lock->val);

	क्रम (;;) अणु
		new = (val & _Q_LOCKED_PENDING_MASK) | tail;
		/*
		 * We can use relaxed semantics since the caller ensures that
		 * the MCS node is properly initialized beक्रमe updating the
		 * tail.
		 */
		old = atomic_cmpxchg_relaxed(&lock->val, val, new);
		अगर (old == val)
			अवरोध;

		val = old;
	पूर्ण
	वापस old;
पूर्ण
#पूर्ण_अगर /* _Q_PENDING_BITS == 8 */

/**
 * queued_fetch_set_pending_acquire - fetch the whole lock value and set pending
 * @lock : Poपूर्णांकer to queued spinlock काष्ठाure
 * Return: The previous lock value
 *
 * *,*,* -> *,1,*
 */
#अगर_अघोषित queued_fetch_set_pending_acquire
अटल __always_अंतरभूत u32 queued_fetch_set_pending_acquire(काष्ठा qspinlock *lock)
अणु
	वापस atomic_fetch_or_acquire(_Q_PENDING_VAL, &lock->val);
पूर्ण
#पूर्ण_अगर

/**
 * set_locked - Set the lock bit and own the lock
 * @lock: Poपूर्णांकer to queued spinlock काष्ठाure
 *
 * *,*,0 -> *,0,1
 */
अटल __always_अंतरभूत व्योम set_locked(काष्ठा qspinlock *lock)
अणु
	WRITE_ONCE(lock->locked, _Q_LOCKED_VAL);
पूर्ण


/*
 * Generate the native code क्रम queued_spin_unlock_slowpath(); provide NOPs क्रम
 * all the PV callbacks.
 */

अटल __always_अंतरभूत व्योम __pv_init_node(काष्ठा mcs_spinlock *node) अणु पूर्ण
अटल __always_अंतरभूत व्योम __pv_रुको_node(काष्ठा mcs_spinlock *node,
					   काष्ठा mcs_spinlock *prev) अणु पूर्ण
अटल __always_अंतरभूत व्योम __pv_kick_node(काष्ठा qspinlock *lock,
					   काष्ठा mcs_spinlock *node) अणु पूर्ण
अटल __always_अंतरभूत u32  __pv_रुको_head_or_lock(काष्ठा qspinlock *lock,
						   काष्ठा mcs_spinlock *node)
						   अणु वापस 0; पूर्ण

#घोषणा pv_enabled()		false

#घोषणा pv_init_node		__pv_init_node
#घोषणा pv_रुको_node		__pv_रुको_node
#घोषणा pv_kick_node		__pv_kick_node
#घोषणा pv_रुको_head_or_lock	__pv_रुको_head_or_lock

#अगर_घोषित CONFIG_PARAVIRT_SPINLOCKS
#घोषणा queued_spin_lock_slowpath	native_queued_spin_lock_slowpath
#पूर्ण_अगर

#पूर्ण_अगर /* _GEN_PV_LOCK_SLOWPATH */

/**
 * queued_spin_lock_slowpath - acquire the queued spinlock
 * @lock: Poपूर्णांकer to queued spinlock काष्ठाure
 * @val: Current value of the queued spinlock 32-bit word
 *
 * (queue tail, pending bit, lock value)
 *
 *              fast     :    slow                                  :    unlock
 *                       :                                          :
 * uncontended  (0,0,0) -:--> (0,0,1) ------------------------------:--> (*,*,0)
 *                       :       | ^--------.------.             /  :
 *                       :       v           \      \            |  :
 * pending               :    (0,1,1) +--> (0,1,0)   \           |  :
 *                       :       | ^--'              |           |  :
 *                       :       v                   |           |  :
 * uncontended           :    (n,x,y) +--> (n,0,0) --'           |  :
 *   queue               :       | ^--'                          |  :
 *                       :       v                               |  :
 * contended             :    (*,x,y) +--> (*,0,0) ---> (*,0,1) -'  :
 *   queue               :         ^--'                             :
 */
व्योम queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val)
अणु
	काष्ठा mcs_spinlock *prev, *next, *node;
	u32 old, tail;
	पूर्णांक idx;

	BUILD_BUG_ON(CONFIG_NR_CPUS >= (1U << _Q_TAIL_CPU_BITS));

	अगर (pv_enabled())
		जाओ pv_queue;

	अगर (virt_spin_lock(lock))
		वापस;

	/*
	 * Wait क्रम in-progress pending->locked hand-overs with a bounded
	 * number of spins so that we guarantee क्रमward progress.
	 *
	 * 0,1,0 -> 0,0,1
	 */
	अगर (val == _Q_PENDING_VAL) अणु
		पूर्णांक cnt = _Q_PENDING_LOOPS;
		val = atomic_cond_पढ़ो_relaxed(&lock->val,
					       (VAL != _Q_PENDING_VAL) || !cnt--);
	पूर्ण

	/*
	 * If we observe any contention; queue.
	 */
	अगर (val & ~_Q_LOCKED_MASK)
		जाओ queue;

	/*
	 * trylock || pending
	 *
	 * 0,0,* -> 0,1,* -> 0,0,1 pending, trylock
	 */
	val = queued_fetch_set_pending_acquire(lock);

	/*
	 * If we observe contention, there is a concurrent locker.
	 *
	 * Unकरो and queue; our setting of PENDING might have made the
	 * n,0,0 -> 0,0,0 transition fail and it will now be रुकोing
	 * on @next to become !शून्य.
	 */
	अगर (unlikely(val & ~_Q_LOCKED_MASK)) अणु

		/* Unकरो PENDING अगर we set it. */
		अगर (!(val & _Q_PENDING_MASK))
			clear_pending(lock);

		जाओ queue;
	पूर्ण

	/*
	 * We're pending, रुको क्रम the owner to go away.
	 *
	 * 0,1,1 -> 0,1,0
	 *
	 * this रुको loop must be a load-acquire such that we match the
	 * store-release that clears the locked bit and create lock
	 * sequentiality; this is because not all
	 * clear_pending_set_locked() implementations imply full
	 * barriers.
	 */
	अगर (val & _Q_LOCKED_MASK)
		atomic_cond_पढ़ो_acquire(&lock->val, !(VAL & _Q_LOCKED_MASK));

	/*
	 * take ownership and clear the pending bit.
	 *
	 * 0,1,0 -> 0,0,1
	 */
	clear_pending_set_locked(lock);
	lockevent_inc(lock_pending);
	वापस;

	/*
	 * End of pending bit optimistic spinning and beginning of MCS
	 * queuing.
	 */
queue:
	lockevent_inc(lock_slowpath);
pv_queue:
	node = this_cpu_ptr(&qnodes[0].mcs);
	idx = node->count++;
	tail = encode_tail(smp_processor_id(), idx);

	/*
	 * 4 nodes are allocated based on the assumption that there will
	 * not be nested NMIs taking spinlocks. That may not be true in
	 * some architectures even though the chance of needing more than
	 * 4 nodes will still be extremely unlikely. When that happens,
	 * we fall back to spinning on the lock directly without using
	 * any MCS node. This is not the most elegant solution, but is
	 * simple enough.
	 */
	अगर (unlikely(idx >= MAX_NODES)) अणु
		lockevent_inc(lock_no_node);
		जबतक (!queued_spin_trylock(lock))
			cpu_relax();
		जाओ release;
	पूर्ण

	node = grab_mcs_node(node, idx);

	/*
	 * Keep counts of non-zero index values:
	 */
	lockevent_cond_inc(lock_use_node2 + idx - 1, idx);

	/*
	 * Ensure that we increment the head node->count beक्रमe initialising
	 * the actual node. If the compiler is kind enough to reorder these
	 * stores, then an IRQ could overग_लिखो our assignments.
	 */
	barrier();

	node->locked = 0;
	node->next = शून्य;
	pv_init_node(node);

	/*
	 * We touched a (possibly) cold cacheline in the per-cpu queue node;
	 * attempt the trylock once more in the hope someone let go जबतक we
	 * weren't watching.
	 */
	अगर (queued_spin_trylock(lock))
		जाओ release;

	/*
	 * Ensure that the initialisation of @node is complete beक्रमe we
	 * publish the updated tail via xchg_tail() and potentially link
	 * @node पूर्णांकo the रुकोqueue via WRITE_ONCE(prev->next, node) below.
	 */
	smp_wmb();

	/*
	 * Publish the updated tail.
	 * We have alपढ़ोy touched the queueing cacheline; करोn't bother with
	 * pending stuff.
	 *
	 * p,*,* -> n,*,*
	 */
	old = xchg_tail(lock, tail);
	next = शून्य;

	/*
	 * अगर there was a previous node; link it and रुको until reaching the
	 * head of the रुकोqueue.
	 */
	अगर (old & _Q_TAIL_MASK) अणु
		prev = decode_tail(old);

		/* Link @node पूर्णांकo the रुकोqueue. */
		WRITE_ONCE(prev->next, node);

		pv_रुको_node(node, prev);
		arch_mcs_spin_lock_contended(&node->locked);

		/*
		 * While रुकोing क्रम the MCS lock, the next poपूर्णांकer may have
		 * been set by another lock रुकोer. We optimistically load
		 * the next poपूर्णांकer & prefetch the cacheline क्रम writing
		 * to reduce latency in the upcoming MCS unlock operation.
		 */
		next = READ_ONCE(node->next);
		अगर (next)
			prefetchw(next);
	पूर्ण

	/*
	 * we're at the head of the रुकोqueue, रुको क्रम the owner & pending to
	 * go away.
	 *
	 * *,x,y -> *,0,0
	 *
	 * this रुको loop must use a load-acquire such that we match the
	 * store-release that clears the locked bit and create lock
	 * sequentiality; this is because the set_locked() function below
	 * करोes not imply a full barrier.
	 *
	 * The PV pv_रुको_head_or_lock function, अगर active, will acquire
	 * the lock and वापस a non-zero value. So we have to skip the
	 * atomic_cond_पढ़ो_acquire() call. As the next PV queue head hasn't
	 * been designated yet, there is no way क्रम the locked value to become
	 * _Q_SLOW_VAL. So both the set_locked() and the
	 * atomic_cmpxchg_relaxed() calls will be safe.
	 *
	 * If PV isn't active, 0 will be वापसed instead.
	 *
	 */
	अगर ((val = pv_रुको_head_or_lock(lock, node)))
		जाओ locked;

	val = atomic_cond_पढ़ो_acquire(&lock->val, !(VAL & _Q_LOCKED_PENDING_MASK));

locked:
	/*
	 * claim the lock:
	 *
	 * n,0,0 -> 0,0,1 : lock, uncontended
	 * *,*,0 -> *,*,1 : lock, contended
	 *
	 * If the queue head is the only one in the queue (lock value == tail)
	 * and nobody is pending, clear the tail code and grab the lock.
	 * Otherwise, we only need to grab the lock.
	 */

	/*
	 * In the PV हाल we might alपढ़ोy have _Q_LOCKED_VAL set, because
	 * of lock stealing; thereक्रमe we must also allow:
	 *
	 * n,0,1 -> 0,0,1
	 *
	 * Note: at this poपूर्णांक: (val & _Q_PENDING_MASK) == 0, because of the
	 *       above रुको condition, thereक्रमe any concurrent setting of
	 *       PENDING will make the uncontended transition fail.
	 */
	अगर ((val & _Q_TAIL_MASK) == tail) अणु
		अगर (atomic_try_cmpxchg_relaxed(&lock->val, &val, _Q_LOCKED_VAL))
			जाओ release; /* No contention */
	पूर्ण

	/*
	 * Either somebody is queued behind us or _Q_PENDING_VAL got set
	 * which will then detect the reमुख्यing tail and queue behind us
	 * ensuring we'll see a @next.
	 */
	set_locked(lock);

	/*
	 * contended path; रुको क्रम next अगर not observed yet, release.
	 */
	अगर (!next)
		next = smp_cond_load_relaxed(&node->next, (VAL));

	arch_mcs_spin_unlock_contended(&next->locked);
	pv_kick_node(lock, next);

release:
	/*
	 * release the node
	 */
	__this_cpu_dec(qnodes[0].mcs.count);
पूर्ण
EXPORT_SYMBOL(queued_spin_lock_slowpath);

/*
 * Generate the paravirt code क्रम queued_spin_unlock_slowpath().
 */
#अगर !defined(_GEN_PV_LOCK_SLOWPATH) && defined(CONFIG_PARAVIRT_SPINLOCKS)
#घोषणा _GEN_PV_LOCK_SLOWPATH

#अघोषित  pv_enabled
#घोषणा pv_enabled()	true

#अघोषित pv_init_node
#अघोषित pv_रुको_node
#अघोषित pv_kick_node
#अघोषित pv_रुको_head_or_lock

#अघोषित  queued_spin_lock_slowpath
#घोषणा queued_spin_lock_slowpath	__pv_queued_spin_lock_slowpath

#समावेश "qspinlock_paravirt.h"
#समावेश "qspinlock.c"

bool nopvspin __initdata;
अटल __init पूर्णांक parse_nopvspin(अक्षर *arg)
अणु
	nopvspin = true;
	वापस 0;
पूर्ण
early_param("nopvspin", parse_nopvspin);
#पूर्ण_अगर
