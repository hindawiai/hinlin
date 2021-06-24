<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _GEN_PV_LOCK_SLOWPATH
#त्रुटि "do not include this file"
#पूर्ण_अगर

#समावेश <linux/hash.h>
#समावेश <linux/memblock.h>
#समावेश <linux/debug_locks.h>

/*
 * Implement paravirt qspinlocks; the general idea is to halt the vcpus instead
 * of spinning them.
 *
 * This relies on the architecture to provide two paravirt hypercalls:
 *
 *   pv_रुको(u8 *ptr, u8 val) -- suspends the vcpu अगर *ptr == val
 *   pv_kick(cpu)             -- wakes a suspended vcpu
 *
 * Using these we implement __pv_queued_spin_lock_slowpath() and
 * __pv_queued_spin_unlock() to replace native_queued_spin_lock_slowpath() and
 * native_queued_spin_unlock().
 */

#घोषणा _Q_SLOW_VAL	(3U << _Q_LOCKED_OFFSET)

/*
 * Queue Node Adaptive Spinning
 *
 * A queue node vCPU will stop spinning अगर the vCPU in the previous node is
 * not running. The one lock stealing attempt allowed at slowpath entry
 * mitigates the slight slowकरोwn क्रम non-overcommitted guest with this
 * aggressive रुको-early mechanism.
 *
 * The status of the previous node will be checked at fixed पूर्णांकerval
 * controlled by PV_PREV_CHECK_MASK. This is to ensure that we won't
 * pound on the cacheline of the previous node too heavily.
 */
#घोषणा PV_PREV_CHECK_MASK	0xff

/*
 * Queue node uses: vcpu_running & vcpu_halted.
 * Queue head uses: vcpu_running & vcpu_hashed.
 */
क्रमागत vcpu_state अणु
	vcpu_running = 0,
	vcpu_halted,		/* Used only in pv_रुको_node */
	vcpu_hashed,		/* = pv_hash'ed + vcpu_halted */
पूर्ण;

काष्ठा pv_node अणु
	काष्ठा mcs_spinlock	mcs;
	पूर्णांक			cpu;
	u8			state;
पूर्ण;

/*
 * Hybrid PV queued/unfair lock
 *
 * By replacing the regular queued_spin_trylock() with the function below,
 * it will be called once when a lock रुकोer enter the PV slowpath beक्रमe
 * being queued.
 *
 * The pending bit is set by the queue head vCPU of the MCS रुको queue in
 * pv_रुको_head_or_lock() to संकेत that it is पढ़ोy to spin on the lock.
 * When that bit becomes visible to the incoming रुकोers, no lock stealing
 * is allowed. The function will वापस immediately to make the रुकोers
 * enter the MCS रुको queue. So lock starvation shouldn't happen as दीर्घ
 * as the queued mode vCPUs are actively running to set the pending bit
 * and hence disabling lock stealing.
 *
 * When the pending bit isn't set, the lock रुकोers will stay in the unfair
 * mode spinning on the lock unless the MCS रुको queue is empty. In this
 * हाल, the lock रुकोers will enter the queued mode slowpath trying to
 * become the queue head and set the pending bit.
 *
 * This hybrid PV queued/unfair lock combines the best attributes of a
 * queued lock (no lock starvation) and an unfair lock (good perक्रमmance
 * on not heavily contended locks).
 */
#घोषणा queued_spin_trylock(l)	pv_hybrid_queued_unfair_trylock(l)
अटल अंतरभूत bool pv_hybrid_queued_unfair_trylock(काष्ठा qspinlock *lock)
अणु
	/*
	 * Stay in unfair lock mode as दीर्घ as queued mode रुकोers are
	 * present in the MCS रुको queue but the pending bit isn't set.
	 */
	क्रम (;;) अणु
		पूर्णांक val = atomic_पढ़ो(&lock->val);

		अगर (!(val & _Q_LOCKED_PENDING_MASK) &&
		   (cmpxchg_acquire(&lock->locked, 0, _Q_LOCKED_VAL) == 0)) अणु
			lockevent_inc(pv_lock_stealing);
			वापस true;
		पूर्ण
		अगर (!(val & _Q_TAIL_MASK) || (val & _Q_PENDING_MASK))
			अवरोध;

		cpu_relax();
	पूर्ण

	वापस false;
पूर्ण

/*
 * The pending bit is used by the queue head vCPU to indicate that it
 * is actively spinning on the lock and no lock stealing is allowed.
 */
#अगर _Q_PENDING_BITS == 8
अटल __always_अंतरभूत व्योम set_pending(काष्ठा qspinlock *lock)
अणु
	WRITE_ONCE(lock->pending, 1);
पूर्ण

/*
 * The pending bit check in pv_queued_spin_steal_lock() isn't a memory
 * barrier. Thereक्रमe, an atomic cmpxchg_acquire() is used to acquire the
 * lock just to be sure that it will get it.
 */
अटल __always_अंतरभूत पूर्णांक trylock_clear_pending(काष्ठा qspinlock *lock)
अणु
	वापस !READ_ONCE(lock->locked) &&
	       (cmpxchg_acquire(&lock->locked_pending, _Q_PENDING_VAL,
				_Q_LOCKED_VAL) == _Q_PENDING_VAL);
पूर्ण
#अन्यथा /* _Q_PENDING_BITS == 8 */
अटल __always_अंतरभूत व्योम set_pending(काष्ठा qspinlock *lock)
अणु
	atomic_or(_Q_PENDING_VAL, &lock->val);
पूर्ण

अटल __always_अंतरभूत पूर्णांक trylock_clear_pending(काष्ठा qspinlock *lock)
अणु
	पूर्णांक val = atomic_पढ़ो(&lock->val);

	क्रम (;;) अणु
		पूर्णांक old, new;

		अगर (val  & _Q_LOCKED_MASK)
			अवरोध;

		/*
		 * Try to clear pending bit & set locked bit
		 */
		old = val;
		new = (val & ~_Q_PENDING_MASK) | _Q_LOCKED_VAL;
		val = atomic_cmpxchg_acquire(&lock->val, old, new);

		अगर (val == old)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* _Q_PENDING_BITS == 8 */

/*
 * Lock and MCS node addresses hash table क्रम fast lookup
 *
 * Hashing is करोne on a per-cacheline basis to minimize the need to access
 * more than one cacheline.
 *
 * Dynamically allocate a hash table big enough to hold at least 4X the
 * number of possible cpus in the प्रणाली. Allocation is करोne on page
 * granularity. So the minimum number of hash buckets should be at least
 * 256 (64-bit) or 512 (32-bit) to fully utilize a 4k page.
 *
 * Since we should not be holding locks from NMI context (very rare indeed) the
 * max load factor is 0.75, which is around the poपूर्णांक where खोलो addressing
 * अवरोधs करोwn.
 *
 */
काष्ठा pv_hash_entry अणु
	काष्ठा qspinlock *lock;
	काष्ठा pv_node   *node;
पूर्ण;

#घोषणा PV_HE_PER_LINE	(SMP_CACHE_BYTES / माप(काष्ठा pv_hash_entry))
#घोषणा PV_HE_MIN	(PAGE_SIZE / माप(काष्ठा pv_hash_entry))

अटल काष्ठा pv_hash_entry *pv_lock_hash;
अटल अचिन्हित पूर्णांक pv_lock_hash_bits __पढ़ो_mostly;

/*
 * Allocate memory क्रम the PV qspinlock hash buckets
 *
 * This function should be called from the paravirt spinlock initialization
 * routine.
 */
व्योम __init __pv_init_lock_hash(व्योम)
अणु
	पूर्णांक pv_hash_size = ALIGN(4 * num_possible_cpus(), PV_HE_PER_LINE);

	अगर (pv_hash_size < PV_HE_MIN)
		pv_hash_size = PV_HE_MIN;

	/*
	 * Allocate space from booपंचांगem which should be page-size aligned
	 * and hence cacheline aligned.
	 */
	pv_lock_hash = alloc_large_प्रणाली_hash("PV qspinlock",
					       माप(काष्ठा pv_hash_entry),
					       pv_hash_size, 0,
					       HASH_EARLY | HASH_ZERO,
					       &pv_lock_hash_bits, शून्य,
					       pv_hash_size, pv_hash_size);
पूर्ण

#घोषणा क्रम_each_hash_entry(he, offset, hash)						\
	क्रम (hash &= ~(PV_HE_PER_LINE - 1), he = &pv_lock_hash[hash], offset = 0;	\
	     offset < (1 << pv_lock_hash_bits);						\
	     offset++, he = &pv_lock_hash[(hash + offset) & ((1 << pv_lock_hash_bits) - 1)])

अटल काष्ठा qspinlock **pv_hash(काष्ठा qspinlock *lock, काष्ठा pv_node *node)
अणु
	अचिन्हित दीर्घ offset, hash = hash_ptr(lock, pv_lock_hash_bits);
	काष्ठा pv_hash_entry *he;
	पूर्णांक hopcnt = 0;

	क्रम_each_hash_entry(he, offset, hash) अणु
		hopcnt++;
		अगर (!cmpxchg(&he->lock, शून्य, lock)) अणु
			WRITE_ONCE(he->node, node);
			lockevent_pv_hop(hopcnt);
			वापस &he->lock;
		पूर्ण
	पूर्ण
	/*
	 * Hard assume there is a मुक्त entry क्रम us.
	 *
	 * This is guaranteed by ensuring every blocked lock only ever consumes
	 * a single entry, and since we only have 4 nesting levels per CPU
	 * and allocated 4*nr_possible_cpus(), this must be so.
	 *
	 * The single entry is guaranteed by having the lock owner unhash
	 * beक्रमe it releases.
	 */
	BUG();
पूर्ण

अटल काष्ठा pv_node *pv_unhash(काष्ठा qspinlock *lock)
अणु
	अचिन्हित दीर्घ offset, hash = hash_ptr(lock, pv_lock_hash_bits);
	काष्ठा pv_hash_entry *he;
	काष्ठा pv_node *node;

	क्रम_each_hash_entry(he, offset, hash) अणु
		अगर (READ_ONCE(he->lock) == lock) अणु
			node = READ_ONCE(he->node);
			WRITE_ONCE(he->lock, शून्य);
			वापस node;
		पूर्ण
	पूर्ण
	/*
	 * Hard assume we'll find an entry.
	 *
	 * This guarantees a limited lookup समय and is itself guaranteed by
	 * having the lock owner करो the unhash -- IFF the unlock sees the
	 * SLOW flag, there MUST be a hash entry.
	 */
	BUG();
पूर्ण

/*
 * Return true अगर when it is समय to check the previous node which is not
 * in a running state.
 */
अटल अंतरभूत bool
pv_रुको_early(काष्ठा pv_node *prev, पूर्णांक loop)
अणु
	अगर ((loop & PV_PREV_CHECK_MASK) != 0)
		वापस false;

	वापस READ_ONCE(prev->state) != vcpu_running;
पूर्ण

/*
 * Initialize the PV part of the mcs_spinlock node.
 */
अटल व्योम pv_init_node(काष्ठा mcs_spinlock *node)
अणु
	काष्ठा pv_node *pn = (काष्ठा pv_node *)node;

	BUILD_BUG_ON(माप(काष्ठा pv_node) > माप(काष्ठा qnode));

	pn->cpu = smp_processor_id();
	pn->state = vcpu_running;
पूर्ण

/*
 * Wait क्रम node->locked to become true, halt the vcpu after a लघु spin.
 * pv_kick_node() is used to set _Q_SLOW_VAL and fill in hash table on its
 * behalf.
 */
अटल व्योम pv_रुको_node(काष्ठा mcs_spinlock *node, काष्ठा mcs_spinlock *prev)
अणु
	काष्ठा pv_node *pn = (काष्ठा pv_node *)node;
	काष्ठा pv_node *pp = (काष्ठा pv_node *)prev;
	पूर्णांक loop;
	bool रुको_early;

	क्रम (;;) अणु
		क्रम (रुको_early = false, loop = SPIN_THRESHOLD; loop; loop--) अणु
			अगर (READ_ONCE(node->locked))
				वापस;
			अगर (pv_रुको_early(pp, loop)) अणु
				रुको_early = true;
				अवरोध;
			पूर्ण
			cpu_relax();
		पूर्ण

		/*
		 * Order pn->state vs pn->locked thusly:
		 *
		 * [S] pn->state = vcpu_halted	  [S] next->locked = 1
		 *     MB			      MB
		 * [L] pn->locked		[RmW] pn->state = vcpu_hashed
		 *
		 * Matches the cmpxchg() from pv_kick_node().
		 */
		smp_store_mb(pn->state, vcpu_halted);

		अगर (!READ_ONCE(node->locked)) अणु
			lockevent_inc(pv_रुको_node);
			lockevent_cond_inc(pv_रुको_early, रुको_early);
			pv_रुको(&pn->state, vcpu_halted);
		पूर्ण

		/*
		 * If pv_kick_node() changed us to vcpu_hashed, retain that
		 * value so that pv_रुको_head_or_lock() knows to not also try
		 * to hash this lock.
		 */
		cmpxchg(&pn->state, vcpu_halted, vcpu_running);

		/*
		 * If the locked flag is still not set after wakeup, it is a
		 * spurious wakeup and the vCPU should रुको again. However,
		 * there is a pretty high overhead क्रम CPU halting and kicking.
		 * So it is better to spin क्रम a जबतक in the hope that the
		 * MCS lock will be released soon.
		 */
		lockevent_cond_inc(pv_spurious_wakeup,
				  !READ_ONCE(node->locked));
	पूर्ण

	/*
	 * By now our node->locked should be 1 and our caller will not actually
	 * spin-रुको क्रम it. We करो however rely on our caller to करो a
	 * load-acquire क्रम us.
	 */
पूर्ण

/*
 * Called after setting next->locked = 1 when we're the lock owner.
 *
 * Instead of waking the रुकोers stuck in pv_रुको_node() advance their state
 * such that they're रुकोing in pv_रुको_head_or_lock(), this aव्योमs a
 * wake/sleep cycle.
 */
अटल व्योम pv_kick_node(काष्ठा qspinlock *lock, काष्ठा mcs_spinlock *node)
अणु
	काष्ठा pv_node *pn = (काष्ठा pv_node *)node;

	/*
	 * If the vCPU is indeed halted, advance its state to match that of
	 * pv_रुको_node(). If OTOH this fails, the vCPU was running and will
	 * observe its next->locked value and advance itself.
	 *
	 * Matches with smp_store_mb() and cmpxchg() in pv_रुको_node()
	 *
	 * The ग_लिखो to next->locked in arch_mcs_spin_unlock_contended()
	 * must be ordered beक्रमe the पढ़ो of pn->state in the cmpxchg()
	 * below क्रम the code to work correctly. To guarantee full ordering
	 * irrespective of the success or failure of the cmpxchg(),
	 * a relaxed version with explicit barrier is used. The control
	 * dependency will order the पढ़ोing of pn->state beक्रमe any
	 * subsequent ग_लिखोs.
	 */
	smp_mb__beक्रमe_atomic();
	अगर (cmpxchg_relaxed(&pn->state, vcpu_halted, vcpu_hashed)
	    != vcpu_halted)
		वापस;

	/*
	 * Put the lock पूर्णांकo the hash table and set the _Q_SLOW_VAL.
	 *
	 * As this is the same vCPU that will check the _Q_SLOW_VAL value and
	 * the hash table later on at unlock समय, no atomic inकाष्ठाion is
	 * needed.
	 */
	WRITE_ONCE(lock->locked, _Q_SLOW_VAL);
	(व्योम)pv_hash(lock, pn);
पूर्ण

/*
 * Wait क्रम l->locked to become clear and acquire the lock;
 * halt the vcpu after a लघु spin.
 * __pv_queued_spin_unlock() will wake us.
 *
 * The current value of the lock will be वापसed क्रम additional processing.
 */
अटल u32
pv_रुको_head_or_lock(काष्ठा qspinlock *lock, काष्ठा mcs_spinlock *node)
अणु
	काष्ठा pv_node *pn = (काष्ठा pv_node *)node;
	काष्ठा qspinlock **lp = शून्य;
	पूर्णांक रुकोcnt = 0;
	पूर्णांक loop;

	/*
	 * If pv_kick_node() alपढ़ोy advanced our state, we करोn't need to
	 * insert ourselves पूर्णांकo the hash table anymore.
	 */
	अगर (READ_ONCE(pn->state) == vcpu_hashed)
		lp = (काष्ठा qspinlock **)1;

	/*
	 * Tracking # of slowpath locking operations
	 */
	lockevent_inc(lock_slowpath);

	क्रम (;; रुकोcnt++) अणु
		/*
		 * Set correct vCPU state to be used by queue node रुको-early
		 * mechanism.
		 */
		WRITE_ONCE(pn->state, vcpu_running);

		/*
		 * Set the pending bit in the active lock spinning loop to
		 * disable lock stealing beक्रमe attempting to acquire the lock.
		 */
		set_pending(lock);
		क्रम (loop = SPIN_THRESHOLD; loop; loop--) अणु
			अगर (trylock_clear_pending(lock))
				जाओ gotlock;
			cpu_relax();
		पूर्ण
		clear_pending(lock);


		अगर (!lp) अणु /* ONCE */
			lp = pv_hash(lock, pn);

			/*
			 * We must hash beक्रमe setting _Q_SLOW_VAL, such that
			 * when we observe _Q_SLOW_VAL in __pv_queued_spin_unlock()
			 * we'll be sure to be able to observe our hash entry.
			 *
			 *   [S] <hash>                 [Rmw] l->locked == _Q_SLOW_VAL
			 *       MB                           RMB
			 * [RmW] l->locked = _Q_SLOW_VAL  [L] <unhash>
			 *
			 * Matches the smp_rmb() in __pv_queued_spin_unlock().
			 */
			अगर (xchg(&lock->locked, _Q_SLOW_VAL) == 0) अणु
				/*
				 * The lock was मुक्त and now we own the lock.
				 * Change the lock value back to _Q_LOCKED_VAL
				 * and unhash the table.
				 */
				WRITE_ONCE(lock->locked, _Q_LOCKED_VAL);
				WRITE_ONCE(*lp, शून्य);
				जाओ gotlock;
			पूर्ण
		पूर्ण
		WRITE_ONCE(pn->state, vcpu_hashed);
		lockevent_inc(pv_रुको_head);
		lockevent_cond_inc(pv_रुको_again, रुकोcnt);
		pv_रुको(&lock->locked, _Q_SLOW_VAL);

		/*
		 * Because of lock stealing, the queue head vCPU may not be
		 * able to acquire the lock beक्रमe it has to रुको again.
		 */
	पूर्ण

	/*
	 * The cmpxchg() or xchg() call beक्रमe coming here provides the
	 * acquire semantics क्रम locking. The dummy ORing of _Q_LOCKED_VAL
	 * here is to indicate to the compiler that the value will always
	 * be nozero to enable better code optimization.
	 */
gotlock:
	वापस (u32)(atomic_पढ़ो(&lock->val) | _Q_LOCKED_VAL);
पूर्ण

/*
 * PV versions of the unlock fastpath and slowpath functions to be used
 * instead of queued_spin_unlock().
 */
__visible व्योम
__pv_queued_spin_unlock_slowpath(काष्ठा qspinlock *lock, u8 locked)
अणु
	काष्ठा pv_node *node;

	अगर (unlikely(locked != _Q_SLOW_VAL)) अणु
		WARN(!debug_locks_silent,
		     "pvqspinlock: lock 0x%lx has corrupted value 0x%x!\n",
		     (अचिन्हित दीर्घ)lock, atomic_पढ़ो(&lock->val));
		वापस;
	पूर्ण

	/*
	 * A failed cmpxchg करोesn't provide any memory-ordering guarantees,
	 * so we need a barrier to order the पढ़ो of the node data in
	 * pv_unhash *after* we've पढ़ो the lock being _Q_SLOW_VAL.
	 *
	 * Matches the cmpxchg() in pv_रुको_head_or_lock() setting _Q_SLOW_VAL.
	 */
	smp_rmb();

	/*
	 * Since the above failed to release, this must be the SLOW path.
	 * Thereक्रमe start by looking up the blocked node and unhashing it.
	 */
	node = pv_unhash(lock);

	/*
	 * Now that we have a reference to the (likely) blocked pv_node,
	 * release the lock.
	 */
	smp_store_release(&lock->locked, 0);

	/*
	 * At this poपूर्णांक the memory poपूर्णांकed at by lock can be मुक्तd/reused,
	 * however we can still use the pv_node to kick the CPU.
	 * The other vCPU may not really be halted, but kicking an active
	 * vCPU is harmless other than the additional latency in completing
	 * the unlock.
	 */
	lockevent_inc(pv_kick_unlock);
	pv_kick(node->cpu);
पूर्ण

/*
 * Include the architecture specअगरic callee-save thunk of the
 * __pv_queued_spin_unlock(). This thunk is put together with
 * __pv_queued_spin_unlock() to make the callee-save thunk and the real unlock
 * function बंद to each other sharing consecutive inकाष्ठाion cachelines.
 * Alternatively, architecture specअगरic version of __pv_queued_spin_unlock()
 * can be defined.
 */
#समावेश <यंत्र/qspinlock_paravirt.h>

#अगर_अघोषित __pv_queued_spin_unlock
__visible व्योम __pv_queued_spin_unlock(काष्ठा qspinlock *lock)
अणु
	u8 locked;

	/*
	 * We must not unlock अगर SLOW, because in that हाल we must first
	 * unhash. Otherwise it would be possible to have multiple @lock
	 * entries, which would be BAD.
	 */
	locked = cmpxchg_release(&lock->locked, _Q_LOCKED_VAL, 0);
	अगर (likely(locked == _Q_LOCKED_VAL))
		वापस;

	__pv_queued_spin_unlock_slowpath(lock, locked);
पूर्ण
#पूर्ण_अगर /* __pv_queued_spin_unlock */
