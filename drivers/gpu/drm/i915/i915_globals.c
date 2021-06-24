<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "i915_active.h"
#समावेश "gem/i915_gem_context.h"
#समावेश "gem/i915_gem_object.h"
#समावेश "i915_globals.h"
#समावेश "i915_request.h"
#समावेश "i915_scheduler.h"
#समावेश "i915_vma.h"

अटल LIST_HEAD(globals);

अटल atomic_t active;
अटल atomic_t epoch;
अटल काष्ठा park_work अणु
	काष्ठा delayed_work work;
	काष्ठा rcu_head rcu;
	अचिन्हित दीर्घ flags;
#घोषणा PENDING 0
	पूर्णांक epoch;
पूर्ण park;

अटल व्योम i915_globals_shrink(व्योम)
अणु
	काष्ठा i915_global *global;

	/*
	 * kmem_cache_shrink() discards empty sद_असल and reorders partially
	 * filled sद_असल to prioritise allocating from the mostly full sद_असल,
	 * with the aim of reducing fragmentation.
	 */
	list_क्रम_each_entry(global, &globals, link)
		global->shrink();
पूर्ण

अटल व्योम __i915_globals_grace(काष्ठा rcu_head *rcu)
अणु
	/* Ratelimit parking as shrinking is quite slow */
	schedule_delayed_work(&park.work, round_jअगरfies_up_relative(2 * HZ));
पूर्ण

अटल व्योम __i915_globals_queue_rcu(व्योम)
अणु
	park.epoch = atomic_inc_वापस(&epoch);
	अगर (!atomic_पढ़ो(&active)) अणु
		init_rcu_head(&park.rcu);
		call_rcu(&park.rcu, __i915_globals_grace);
	पूर्ण
पूर्ण

अटल व्योम __i915_globals_park(काष्ठा work_काष्ठा *work)
अणु
	destroy_rcu_head(&park.rcu);

	/* Confirm nothing woke up in the last grace period */
	अगर (park.epoch != atomic_पढ़ो(&epoch)) अणु
		__i915_globals_queue_rcu();
		वापस;
	पूर्ण

	clear_bit(PENDING, &park.flags);
	i915_globals_shrink();
पूर्ण

व्योम __init i915_global_रेजिस्टर(काष्ठा i915_global *global)
अणु
	GEM_BUG_ON(!global->shrink);
	GEM_BUG_ON(!global->निकास);

	list_add_tail(&global->link, &globals);
पूर्ण

अटल व्योम __i915_globals_cleanup(व्योम)
अणु
	काष्ठा i915_global *global, *next;

	list_क्रम_each_entry_safe_reverse(global, next, &globals, link)
		global->निकास();
पूर्ण

अटल __initस्थिर पूर्णांक (* स्थिर initfn[])(व्योम) = अणु
	i915_global_active_init,
	i915_global_buddy_init,
	i915_global_context_init,
	i915_global_gem_context_init,
	i915_global_objects_init,
	i915_global_request_init,
	i915_global_scheduler_init,
	i915_global_vma_init,
पूर्ण;

पूर्णांक __init i915_globals_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(initfn); i++) अणु
		पूर्णांक err;

		err = initfn[i]();
		अगर (err) अणु
			__i915_globals_cleanup();
			वापस err;
		पूर्ण
	पूर्ण

	INIT_DELAYED_WORK(&park.work, __i915_globals_park);
	वापस 0;
पूर्ण

व्योम i915_globals_park(व्योम)
अणु
	/*
	 * Defer shrinking the global slab caches (and other work) until
	 * after a RCU grace period has completed with no activity. This
	 * is to try and reduce the latency impact on the consumers caused
	 * by us shrinking the caches the same समय as they are trying to
	 * allocate, with the assumption being that अगर we idle दीर्घ enough
	 * क्रम an RCU grace period to elapse since the last use, it is likely
	 * to be दीर्घer until we need the caches again.
	 */
	अगर (!atomic_dec_and_test(&active))
		वापस;

	/* Queue cleanup after the next RCU grace period has मुक्तd sद_असल */
	अगर (!test_and_set_bit(PENDING, &park.flags))
		__i915_globals_queue_rcu();
पूर्ण

व्योम i915_globals_unpark(व्योम)
अणु
	atomic_inc(&epoch);
	atomic_inc(&active);
पूर्ण

अटल व्योम __निकास __i915_globals_flush(व्योम)
अणु
	atomic_inc(&active); /* skip shrinking */

	rcu_barrier(); /* रुको क्रम the work to be queued */
	flush_delayed_work(&park.work);

	atomic_dec(&active);
पूर्ण

व्योम __निकास i915_globals_निकास(व्योम)
अणु
	GEM_BUG_ON(atomic_पढ़ो(&active));

	__i915_globals_flush();
	__i915_globals_cleanup();

	/* And ensure that our DESTROY_BY_RCU sद_असल are truly destroyed */
	rcu_barrier();
पूर्ण
