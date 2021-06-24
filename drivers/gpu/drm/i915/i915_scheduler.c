<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/mutex.h>

#समावेश "i915_drv.h"
#समावेश "i915_globals.h"
#समावेश "i915_request.h"
#समावेश "i915_scheduler.h"

अटल काष्ठा i915_global_scheduler अणु
	काष्ठा i915_global base;
	काष्ठा kmem_cache *slab_dependencies;
	काष्ठा kmem_cache *slab_priorities;
पूर्ण global;

अटल DEFINE_SPINLOCK(schedule_lock);

अटल स्थिर काष्ठा i915_request *
node_to_request(स्थिर काष्ठा i915_sched_node *node)
अणु
	वापस container_of(node, स्थिर काष्ठा i915_request, sched);
पूर्ण

अटल अंतरभूत bool node_started(स्थिर काष्ठा i915_sched_node *node)
अणु
	वापस i915_request_started(node_to_request(node));
पूर्ण

अटल अंतरभूत bool node_संकेतed(स्थिर काष्ठा i915_sched_node *node)
अणु
	वापस i915_request_completed(node_to_request(node));
पूर्ण

अटल अंतरभूत काष्ठा i915_priolist *to_priolist(काष्ठा rb_node *rb)
अणु
	वापस rb_entry(rb, काष्ठा i915_priolist, node);
पूर्ण

अटल व्योम निश्चित_priolists(काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists)
अणु
	काष्ठा rb_node *rb;
	दीर्घ last_prio;

	अगर (!IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		वापस;

	GEM_BUG_ON(rb_first_cached(&execlists->queue) !=
		   rb_first(&execlists->queue.rb_root));

	last_prio = पूर्णांक_उच्च;
	क्रम (rb = rb_first_cached(&execlists->queue); rb; rb = rb_next(rb)) अणु
		स्थिर काष्ठा i915_priolist *p = to_priolist(rb);

		GEM_BUG_ON(p->priority > last_prio);
		last_prio = p->priority;
	पूर्ण
पूर्ण

काष्ठा list_head *
i915_sched_lookup_priolist(काष्ठा पूर्णांकel_engine_cs *engine, पूर्णांक prio)
अणु
	काष्ठा पूर्णांकel_engine_execlists * स्थिर execlists = &engine->execlists;
	काष्ठा i915_priolist *p;
	काष्ठा rb_node **parent, *rb;
	bool first = true;

	lockdep_निश्चित_held(&engine->active.lock);
	निश्चित_priolists(execlists);

	अगर (unlikely(execlists->no_priolist))
		prio = I915_PRIORITY_NORMAL;

find_priolist:
	/* most positive priority is scheduled first, equal priorities fअगरo */
	rb = शून्य;
	parent = &execlists->queue.rb_root.rb_node;
	जबतक (*parent) अणु
		rb = *parent;
		p = to_priolist(rb);
		अगर (prio > p->priority) अणु
			parent = &rb->rb_left;
		पूर्ण अन्यथा अगर (prio < p->priority) अणु
			parent = &rb->rb_right;
			first = false;
		पूर्ण अन्यथा अणु
			वापस &p->requests;
		पूर्ण
	पूर्ण

	अगर (prio == I915_PRIORITY_NORMAL) अणु
		p = &execlists->शेष_priolist;
	पूर्ण अन्यथा अणु
		p = kmem_cache_alloc(global.slab_priorities, GFP_ATOMIC);
		/* Convert an allocation failure to a priority bump */
		अगर (unlikely(!p)) अणु
			prio = I915_PRIORITY_NORMAL; /* recurses just once */

			/* To मुख्यtain ordering with all rendering, after an
			 * allocation failure we have to disable all scheduling.
			 * Requests will then be executed in fअगरo, and schedule
			 * will ensure that dependencies are emitted in fअगरo.
			 * There will be still some reordering with existing
			 * requests, so अगर userspace lied about their
			 * dependencies that reordering may be visible.
			 */
			execlists->no_priolist = true;
			जाओ find_priolist;
		पूर्ण
	पूर्ण

	p->priority = prio;
	INIT_LIST_HEAD(&p->requests);

	rb_link_node(&p->node, rb, parent);
	rb_insert_color_cached(&p->node, &execlists->queue, first);

	वापस &p->requests;
पूर्ण

व्योम __i915_priolist_मुक्त(काष्ठा i915_priolist *p)
अणु
	kmem_cache_मुक्त(global.slab_priorities, p);
पूर्ण

काष्ठा sched_cache अणु
	काष्ठा list_head *priolist;
पूर्ण;

अटल काष्ठा पूर्णांकel_engine_cs *
sched_lock_engine(स्थिर काष्ठा i915_sched_node *node,
		  काष्ठा पूर्णांकel_engine_cs *locked,
		  काष्ठा sched_cache *cache)
अणु
	स्थिर काष्ठा i915_request *rq = node_to_request(node);
	काष्ठा पूर्णांकel_engine_cs *engine;

	GEM_BUG_ON(!locked);

	/*
	 * Virtual engines complicate acquiring the engine समयline lock,
	 * as their rq->engine poपूर्णांकer is not stable until under that
	 * engine lock. The simple ploy we use is to take the lock then
	 * check that the rq still beदीर्घs to the newly locked engine.
	 */
	जबतक (locked != (engine = READ_ONCE(rq->engine))) अणु
		spin_unlock(&locked->active.lock);
		स_रखो(cache, 0, माप(*cache));
		spin_lock(&engine->active.lock);
		locked = engine;
	पूर्ण

	GEM_BUG_ON(locked != engine);
	वापस locked;
पूर्ण

अटल अंतरभूत पूर्णांक rq_prio(स्थिर काष्ठा i915_request *rq)
अणु
	वापस rq->sched.attr.priority;
पूर्ण

अटल अंतरभूत bool need_preempt(पूर्णांक prio, पूर्णांक active)
अणु
	/*
	 * Allow preemption of low -> normal -> high, but we करो
	 * not allow low priority tasks to preempt other low priority
	 * tasks under the impression that latency क्रम low priority
	 * tasks करोes not matter (as much as background throughput),
	 * so kiss.
	 */
	वापस prio >= max(I915_PRIORITY_NORMAL, active);
पूर्ण

अटल व्योम kick_submission(काष्ठा पूर्णांकel_engine_cs *engine,
			    स्थिर काष्ठा i915_request *rq,
			    पूर्णांक prio)
अणु
	स्थिर काष्ठा i915_request *inflight;

	/*
	 * We only need to kick the tasklet once क्रम the high priority
	 * new context we add पूर्णांकo the queue.
	 */
	अगर (prio <= engine->execlists.queue_priority_hपूर्णांक)
		वापस;

	rcu_पढ़ो_lock();

	/* Nothing currently active? We're overdue क्रम a submission! */
	inflight = execlists_active(&engine->execlists);
	अगर (!inflight)
		जाओ unlock;

	/*
	 * If we are alपढ़ोy the currently executing context, करोn't
	 * bother evaluating अगर we should preempt ourselves.
	 */
	अगर (inflight->context == rq->context)
		जाओ unlock;

	ENGINE_TRACE(engine,
		     "bumping queue-priority-hint:%d for rq:%llx:%lld, inflight:%llx:%lld prio %d\n",
		     prio,
		     rq->fence.context, rq->fence.seqno,
		     inflight->fence.context, inflight->fence.seqno,
		     inflight->sched.attr.priority);

	engine->execlists.queue_priority_hपूर्णांक = prio;
	अगर (need_preempt(prio, rq_prio(inflight)))
		tasklet_hi_schedule(&engine->execlists.tasklet);

unlock:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम __i915_schedule(काष्ठा i915_sched_node *node,
			    स्थिर काष्ठा i915_sched_attr *attr)
अणु
	स्थिर पूर्णांक prio = max(attr->priority, node->attr.priority);
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_dependency *dep, *p;
	काष्ठा i915_dependency stack;
	काष्ठा sched_cache cache;
	LIST_HEAD(dfs);

	/* Needed in order to use the temporary link inside i915_dependency */
	lockdep_निश्चित_held(&schedule_lock);
	GEM_BUG_ON(prio == I915_PRIORITY_INVALID);

	अगर (node_संकेतed(node))
		वापस;

	stack.संकेतer = node;
	list_add(&stack.dfs_link, &dfs);

	/*
	 * Recursively bump all dependent priorities to match the new request.
	 *
	 * A naive approach would be to use recursion:
	 * अटल व्योम update_priorities(काष्ठा i915_sched_node *node, prio) अणु
	 *	list_क्रम_each_entry(dep, &node->संकेतers_list, संकेत_link)
	 *		update_priorities(dep->संकेत, prio)
	 *	queue_request(node);
	 * पूर्ण
	 * but that may have unlimited recursion depth and so runs a very
	 * real risk of overunning the kernel stack. Instead, we build
	 * a flat list of all dependencies starting with the current request.
	 * As we walk the list of dependencies, we add all of its dependencies
	 * to the end of the list (this may include an alपढ़ोy visited
	 * request) and जारी to walk onwards onto the new dependencies. The
	 * end result is a topological list of requests in reverse order, the
	 * last element in the list is the request we must execute first.
	 */
	list_क्रम_each_entry(dep, &dfs, dfs_link) अणु
		काष्ठा i915_sched_node *node = dep->संकेतer;

		/* If we are alपढ़ोy flying, we know we have no संकेतers */
		अगर (node_started(node))
			जारी;

		/*
		 * Within an engine, there can be no cycle, but we may
		 * refer to the same dependency chain multiple बार
		 * (redundant dependencies are not eliminated) and across
		 * engines.
		 */
		list_क्रम_each_entry(p, &node->संकेतers_list, संकेत_link) अणु
			GEM_BUG_ON(p == dep); /* no cycles! */

			अगर (node_संकेतed(p->संकेतer))
				जारी;

			अगर (prio > READ_ONCE(p->संकेतer->attr.priority))
				list_move_tail(&p->dfs_link, &dfs);
		पूर्ण
	पूर्ण

	/*
	 * If we didn't need to bump any existing priorities, and we haven't
	 * yet submitted this request (i.e. there is no potential race with
	 * execlists_submit_request()), we can set our own priority and skip
	 * acquiring the engine locks.
	 */
	अगर (node->attr.priority == I915_PRIORITY_INVALID) अणु
		GEM_BUG_ON(!list_empty(&node->link));
		node->attr = *attr;

		अगर (stack.dfs_link.next == stack.dfs_link.prev)
			वापस;

		__list_del_entry(&stack.dfs_link);
	पूर्ण

	स_रखो(&cache, 0, माप(cache));
	engine = node_to_request(node)->engine;
	spin_lock(&engine->active.lock);

	/* Fअगरo and depth-first replacement ensure our deps execute beक्रमe us */
	engine = sched_lock_engine(node, engine, &cache);
	list_क्रम_each_entry_safe_reverse(dep, p, &dfs, dfs_link) अणु
		INIT_LIST_HEAD(&dep->dfs_link);

		node = dep->संकेतer;
		engine = sched_lock_engine(node, engine, &cache);
		lockdep_निश्चित_held(&engine->active.lock);

		/* Recheck after acquiring the engine->समयline.lock */
		अगर (prio <= node->attr.priority || node_संकेतed(node))
			जारी;

		GEM_BUG_ON(node_to_request(node)->engine != engine);

		WRITE_ONCE(node->attr.priority, prio);

		/*
		 * Once the request is पढ़ोy, it will be placed पूर्णांकo the
		 * priority lists and then onto the HW runlist. Beक्रमe the
		 * request is पढ़ोy, it करोes not contribute to our preemption
		 * decisions and we can safely ignore it, as it will, and
		 * any preemption required, be dealt with upon submission.
		 * See engine->submit_request()
		 */
		अगर (list_empty(&node->link))
			जारी;

		अगर (i915_request_in_priority_queue(node_to_request(node))) अणु
			अगर (!cache.priolist)
				cache.priolist =
					i915_sched_lookup_priolist(engine,
								   prio);
			list_move_tail(&node->link, cache.priolist);
		पूर्ण

		/* Defer (tasklet) submission until after all of our updates. */
		kick_submission(engine, node_to_request(node), prio);
	पूर्ण

	spin_unlock(&engine->active.lock);
पूर्ण

व्योम i915_schedule(काष्ठा i915_request *rq, स्थिर काष्ठा i915_sched_attr *attr)
अणु
	spin_lock_irq(&schedule_lock);
	__i915_schedule(&rq->sched, attr);
	spin_unlock_irq(&schedule_lock);
पूर्ण

व्योम i915_sched_node_init(काष्ठा i915_sched_node *node)
अणु
	INIT_LIST_HEAD(&node->संकेतers_list);
	INIT_LIST_HEAD(&node->रुकोers_list);
	INIT_LIST_HEAD(&node->link);

	i915_sched_node_reinit(node);
पूर्ण

व्योम i915_sched_node_reinit(काष्ठा i915_sched_node *node)
अणु
	node->attr.priority = I915_PRIORITY_INVALID;
	node->semaphores = 0;
	node->flags = 0;

	GEM_BUG_ON(!list_empty(&node->संकेतers_list));
	GEM_BUG_ON(!list_empty(&node->रुकोers_list));
	GEM_BUG_ON(!list_empty(&node->link));
पूर्ण

अटल काष्ठा i915_dependency *
i915_dependency_alloc(व्योम)
अणु
	वापस kmem_cache_alloc(global.slab_dependencies, GFP_KERNEL);
पूर्ण

अटल व्योम
i915_dependency_मुक्त(काष्ठा i915_dependency *dep)
अणु
	kmem_cache_मुक्त(global.slab_dependencies, dep);
पूर्ण

bool __i915_sched_node_add_dependency(काष्ठा i915_sched_node *node,
				      काष्ठा i915_sched_node *संकेत,
				      काष्ठा i915_dependency *dep,
				      अचिन्हित दीर्घ flags)
अणु
	bool ret = false;

	spin_lock_irq(&schedule_lock);

	अगर (!node_संकेतed(संकेत)) अणु
		INIT_LIST_HEAD(&dep->dfs_link);
		dep->संकेतer = संकेत;
		dep->रुकोer = node;
		dep->flags = flags;

		/* All set, now publish. Beware the lockless walkers. */
		list_add_rcu(&dep->संकेत_link, &node->संकेतers_list);
		list_add_rcu(&dep->रुको_link, &संकेत->रुकोers_list);

		/* Propagate the chains */
		node->flags |= संकेत->flags;
		ret = true;
	पूर्ण

	spin_unlock_irq(&schedule_lock);

	वापस ret;
पूर्ण

पूर्णांक i915_sched_node_add_dependency(काष्ठा i915_sched_node *node,
				   काष्ठा i915_sched_node *संकेत,
				   अचिन्हित दीर्घ flags)
अणु
	काष्ठा i915_dependency *dep;

	dep = i915_dependency_alloc();
	अगर (!dep)
		वापस -ENOMEM;

	अगर (!__i915_sched_node_add_dependency(node, संकेत, dep,
					      flags | I915_DEPENDENCY_ALLOC))
		i915_dependency_मुक्त(dep);

	वापस 0;
पूर्ण

व्योम i915_sched_node_fini(काष्ठा i915_sched_node *node)
अणु
	काष्ठा i915_dependency *dep, *पंचांगp;

	spin_lock_irq(&schedule_lock);

	/*
	 * Everyone we depended upon (the fences we रुको to be संकेतed)
	 * should retire beक्रमe us and हटाओ themselves from our list.
	 * However, retirement is run independently on each समयline and
	 * so we may be called out-of-order.
	 */
	list_क्रम_each_entry_safe(dep, पंचांगp, &node->संकेतers_list, संकेत_link) अणु
		GEM_BUG_ON(!list_empty(&dep->dfs_link));

		list_del_rcu(&dep->रुको_link);
		अगर (dep->flags & I915_DEPENDENCY_ALLOC)
			i915_dependency_मुक्त(dep);
	पूर्ण
	INIT_LIST_HEAD(&node->संकेतers_list);

	/* Remove ourselves from everyone who depends upon us */
	list_क्रम_each_entry_safe(dep, पंचांगp, &node->रुकोers_list, रुको_link) अणु
		GEM_BUG_ON(dep->संकेतer != node);
		GEM_BUG_ON(!list_empty(&dep->dfs_link));

		list_del_rcu(&dep->संकेत_link);
		अगर (dep->flags & I915_DEPENDENCY_ALLOC)
			i915_dependency_मुक्त(dep);
	पूर्ण
	INIT_LIST_HEAD(&node->रुकोers_list);

	spin_unlock_irq(&schedule_lock);
पूर्ण

व्योम i915_request_show_with_schedule(काष्ठा drm_prपूर्णांकer *m,
				     स्थिर काष्ठा i915_request *rq,
				     स्थिर अक्षर *prefix,
				     पूर्णांक indent)
अणु
	काष्ठा i915_dependency *dep;

	i915_request_show(m, rq, prefix, indent);
	अगर (i915_request_completed(rq))
		वापस;

	rcu_पढ़ो_lock();
	क्रम_each_संकेतer(dep, rq) अणु
		स्थिर काष्ठा i915_request *संकेतer =
			node_to_request(dep->संकेतer);

		/* Dependencies aदीर्घ the same समयline are expected. */
		अगर (संकेतer->समयline == rq->समयline)
			जारी;

		अगर (__i915_request_is_complete(संकेतer))
			जारी;

		i915_request_show(m, संकेतer, prefix, indent + 2);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम i915_global_scheduler_shrink(व्योम)
अणु
	kmem_cache_shrink(global.slab_dependencies);
	kmem_cache_shrink(global.slab_priorities);
पूर्ण

अटल व्योम i915_global_scheduler_निकास(व्योम)
अणु
	kmem_cache_destroy(global.slab_dependencies);
	kmem_cache_destroy(global.slab_priorities);
पूर्ण

अटल काष्ठा i915_global_scheduler global = अणु अणु
	.shrink = i915_global_scheduler_shrink,
	.निकास = i915_global_scheduler_निकास,
पूर्ण पूर्ण;

पूर्णांक __init i915_global_scheduler_init(व्योम)
अणु
	global.slab_dependencies = KMEM_CACHE(i915_dependency,
					      SLAB_HWCACHE_ALIGN |
					      SLAB_TYPESAFE_BY_RCU);
	अगर (!global.slab_dependencies)
		वापस -ENOMEM;

	global.slab_priorities = KMEM_CACHE(i915_priolist, 0);
	अगर (!global.slab_priorities)
		जाओ err_priorities;

	i915_global_रेजिस्टर(&global.base);
	वापस 0;

err_priorities:
	kmem_cache_destroy(global.slab_priorities);
	वापस -ENOMEM;
पूर्ण
