<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/osq_lock.h>

/*
 * An MCS like lock especially tailored क्रम optimistic spinning क्रम sleeping
 * lock implementations (mutex, rwsem, etc).
 *
 * Using a single mcs node per CPU is safe because sleeping locks should not be
 * called from पूर्णांकerrupt context and we have preemption disabled जबतक
 * spinning.
 */
अटल DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा optimistic_spin_node, osq_node);

/*
 * We use the value 0 to represent "no CPU", thus the encoded value
 * will be the CPU number incremented by 1.
 */
अटल अंतरभूत पूर्णांक encode_cpu(पूर्णांक cpu_nr)
अणु
	वापस cpu_nr + 1;
पूर्ण

अटल अंतरभूत पूर्णांक node_cpu(काष्ठा optimistic_spin_node *node)
अणु
	वापस node->cpu - 1;
पूर्ण

अटल अंतरभूत काष्ठा optimistic_spin_node *decode_cpu(पूर्णांक encoded_cpu_val)
अणु
	पूर्णांक cpu_nr = encoded_cpu_val - 1;

	वापस per_cpu_ptr(&osq_node, cpu_nr);
पूर्ण

/*
 * Get a stable @node->next poपूर्णांकer, either क्रम unlock() or unqueue() purposes.
 * Can वापस शून्य in हाल we were the last queued and we updated @lock instead.
 */
अटल अंतरभूत काष्ठा optimistic_spin_node *
osq_रुको_next(काष्ठा optimistic_spin_queue *lock,
	      काष्ठा optimistic_spin_node *node,
	      काष्ठा optimistic_spin_node *prev)
अणु
	काष्ठा optimistic_spin_node *next = शून्य;
	पूर्णांक curr = encode_cpu(smp_processor_id());
	पूर्णांक old;

	/*
	 * If there is a prev node in queue, then the 'old' value will be
	 * the prev node's CPU #, else it's set to OSQ_UNLOCKED_VAL since अगर
	 * we're currently last in queue, then the queue will then become empty.
	 */
	old = prev ? prev->cpu : OSQ_UNLOCKED_VAL;

	क्रम (;;) अणु
		अगर (atomic_पढ़ो(&lock->tail) == curr &&
		    atomic_cmpxchg_acquire(&lock->tail, curr, old) == curr) अणु
			/*
			 * We were the last queued, we moved @lock back. @prev
			 * will now observe @lock and will complete its
			 * unlock()/unqueue().
			 */
			अवरोध;
		पूर्ण

		/*
		 * We must xchg() the @node->next value, because अगर we were to
		 * leave it in, a concurrent unlock()/unqueue() from
		 * @node->next might complete Step-A and think its @prev is
		 * still valid.
		 *
		 * If the concurrent unlock()/unqueue() wins the race, we'll
		 * रुको क्रम either @lock to poपूर्णांक to us, through its Step-B, or
		 * रुको क्रम a new @node->next from its Step-C.
		 */
		अगर (node->next) अणु
			next = xchg(&node->next, शून्य);
			अगर (next)
				अवरोध;
		पूर्ण

		cpu_relax();
	पूर्ण

	वापस next;
पूर्ण

bool osq_lock(काष्ठा optimistic_spin_queue *lock)
अणु
	काष्ठा optimistic_spin_node *node = this_cpu_ptr(&osq_node);
	काष्ठा optimistic_spin_node *prev, *next;
	पूर्णांक curr = encode_cpu(smp_processor_id());
	पूर्णांक old;

	node->locked = 0;
	node->next = शून्य;
	node->cpu = curr;

	/*
	 * We need both ACQUIRE (pairs with corresponding RELEASE in
	 * unlock() uncontended, or fastpath) and RELEASE (to publish
	 * the node fields we just initialised) semantics when updating
	 * the lock tail.
	 */
	old = atomic_xchg(&lock->tail, curr);
	अगर (old == OSQ_UNLOCKED_VAL)
		वापस true;

	prev = decode_cpu(old);
	node->prev = prev;

	/*
	 * osq_lock()			unqueue
	 *
	 * node->prev = prev		osq_रुको_next()
	 * WMB				MB
	 * prev->next = node		next->prev = prev // unqueue-C
	 *
	 * Here 'node->prev' and 'next->prev' are the same variable and we need
	 * to ensure these stores happen in-order to aव्योम corrupting the list.
	 */
	smp_wmb();

	WRITE_ONCE(prev->next, node);

	/*
	 * Normally @prev is untouchable after the above store; because at that
	 * moment unlock can proceed and wipe the node element from stack.
	 *
	 * However, since our nodes are अटल per-cpu storage, we're
	 * guaranteed their existence -- this allows us to apply
	 * cmpxchg in an attempt to unकरो our queueing.
	 */

	/*
	 * Wait to acquire the lock or cancellation. Note that need_resched()
	 * will come with an IPI, which will wake smp_cond_load_relaxed() अगर it
	 * is implemented with a monitor-रुको. vcpu_is_preempted() relies on
	 * polling, be careful.
	 */
	अगर (smp_cond_load_relaxed(&node->locked, VAL || need_resched() ||
				  vcpu_is_preempted(node_cpu(node->prev))))
		वापस true;

	/* unqueue */
	/*
	 * Step - A  -- stabilize @prev
	 *
	 * Unकरो our @prev->next assignment; this will make @prev's
	 * unlock()/unqueue() रुको क्रम a next poपूर्णांकer since @lock poपूर्णांकs to us
	 * (or later).
	 */

	क्रम (;;) अणु
		/*
		 * cpu_relax() below implies a compiler barrier which would
		 * prevent this comparison being optimized away.
		 */
		अगर (data_race(prev->next) == node &&
		    cmpxchg(&prev->next, node, शून्य) == node)
			अवरोध;

		/*
		 * We can only fail the cmpxchg() racing against an unlock(),
		 * in which हाल we should observe @node->locked becoming
		 * true.
		 */
		अगर (smp_load_acquire(&node->locked))
			वापस true;

		cpu_relax();

		/*
		 * Or we race against a concurrent unqueue()'s step-B, in which
		 * हाल its step-C will ग_लिखो us a new @node->prev poपूर्णांकer.
		 */
		prev = READ_ONCE(node->prev);
	पूर्ण

	/*
	 * Step - B -- stabilize @next
	 *
	 * Similar to unlock(), रुको क्रम @node->next or move @lock from @node
	 * back to @prev.
	 */

	next = osq_रुको_next(lock, node, prev);
	अगर (!next)
		वापस false;

	/*
	 * Step - C -- unlink
	 *
	 * @prev is stable because its still रुकोing क्रम a new @prev->next
	 * poपूर्णांकer, @next is stable because our @node->next poपूर्णांकer is शून्य and
	 * it will रुको in Step-A.
	 */

	WRITE_ONCE(next->prev, prev);
	WRITE_ONCE(prev->next, next);

	वापस false;
पूर्ण

व्योम osq_unlock(काष्ठा optimistic_spin_queue *lock)
अणु
	काष्ठा optimistic_spin_node *node, *next;
	पूर्णांक curr = encode_cpu(smp_processor_id());

	/*
	 * Fast path क्रम the uncontended हाल.
	 */
	अगर (likely(atomic_cmpxchg_release(&lock->tail, curr,
					  OSQ_UNLOCKED_VAL) == curr))
		वापस;

	/*
	 * Second most likely हाल.
	 */
	node = this_cpu_ptr(&osq_node);
	next = xchg(&node->next, शून्य);
	अगर (next) अणु
		WRITE_ONCE(next->locked, 1);
		वापस;
	पूर्ण

	next = osq_रुको_next(lock, node, शून्य);
	अगर (next)
		WRITE_ONCE(next->locked, 1);
पूर्ण
