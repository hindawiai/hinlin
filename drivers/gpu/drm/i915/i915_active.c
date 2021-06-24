<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/debugobjects.h>

#समावेश "gt/intel_context.h"
#समावेश "gt/intel_engine_heartbeat.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_ring.h"

#समावेश "i915_drv.h"
#समावेश "i915_active.h"
#समावेश "i915_globals.h"

/*
 * Active refs memory management
 *
 * To be more economical with memory, we reap all the i915_active trees as
 * they idle (when we know the active requests are inactive) and allocate the
 * nodes from a local slab cache to hopefully reduce the fragmentation.
 */
अटल काष्ठा i915_global_active अणु
	काष्ठा i915_global base;
	काष्ठा kmem_cache *slab_cache;
पूर्ण global;

काष्ठा active_node अणु
	काष्ठा rb_node node;
	काष्ठा i915_active_fence base;
	काष्ठा i915_active *ref;
	u64 समयline;
पूर्ण;

#घोषणा fetch_node(x) rb_entry(READ_ONCE(x), typeof(काष्ठा active_node), node)

अटल अंतरभूत काष्ठा active_node *
node_from_active(काष्ठा i915_active_fence *active)
अणु
	वापस container_of(active, काष्ठा active_node, base);
पूर्ण

#घोषणा take_pपुनः_स्मृतिated_barriers(x) llist_del_all(&(x)->pपुनः_स्मृतिated_barriers)

अटल अंतरभूत bool is_barrier(स्थिर काष्ठा i915_active_fence *active)
अणु
	वापस IS_ERR(rcu_access_poपूर्णांकer(active->fence));
पूर्ण

अटल अंतरभूत काष्ठा llist_node *barrier_to_ll(काष्ठा active_node *node)
अणु
	GEM_BUG_ON(!is_barrier(&node->base));
	वापस (काष्ठा llist_node *)&node->base.cb.node;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_engine_cs *
__barrier_to_engine(काष्ठा active_node *node)
अणु
	वापस (काष्ठा पूर्णांकel_engine_cs *)READ_ONCE(node->base.cb.node.prev);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_engine_cs *
barrier_to_engine(काष्ठा active_node *node)
अणु
	GEM_BUG_ON(!is_barrier(&node->base));
	वापस __barrier_to_engine(node);
पूर्ण

अटल अंतरभूत काष्ठा active_node *barrier_from_ll(काष्ठा llist_node *x)
अणु
	वापस container_of((काष्ठा list_head *)x,
			    काष्ठा active_node, base.cb.node);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM) && IS_ENABLED(CONFIG_DEBUG_OBJECTS)

अटल व्योम *active_debug_hपूर्णांक(व्योम *addr)
अणु
	काष्ठा i915_active *ref = addr;

	वापस (व्योम *)ref->active ?: (व्योम *)ref->retire ?: (व्योम *)ref;
पूर्ण

अटल स्थिर काष्ठा debug_obj_descr active_debug_desc = अणु
	.name = "i915_active",
	.debug_hपूर्णांक = active_debug_hपूर्णांक,
पूर्ण;

अटल व्योम debug_active_init(काष्ठा i915_active *ref)
अणु
	debug_object_init(ref, &active_debug_desc);
पूर्ण

अटल व्योम debug_active_activate(काष्ठा i915_active *ref)
अणु
	lockdep_निश्चित_held(&ref->tree_lock);
	अगर (!atomic_पढ़ो(&ref->count)) /* beक्रमe the first inc */
		debug_object_activate(ref, &active_debug_desc);
पूर्ण

अटल व्योम debug_active_deactivate(काष्ठा i915_active *ref)
अणु
	lockdep_निश्चित_held(&ref->tree_lock);
	अगर (!atomic_पढ़ो(&ref->count)) /* after the last dec */
		debug_object_deactivate(ref, &active_debug_desc);
पूर्ण

अटल व्योम debug_active_fini(काष्ठा i915_active *ref)
अणु
	debug_object_मुक्त(ref, &active_debug_desc);
पूर्ण

अटल व्योम debug_active_निश्चित(काष्ठा i915_active *ref)
अणु
	debug_object_निश्चित_init(ref, &active_debug_desc);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम debug_active_init(काष्ठा i915_active *ref) अणु पूर्ण
अटल अंतरभूत व्योम debug_active_activate(काष्ठा i915_active *ref) अणु पूर्ण
अटल अंतरभूत व्योम debug_active_deactivate(काष्ठा i915_active *ref) अणु पूर्ण
अटल अंतरभूत व्योम debug_active_fini(काष्ठा i915_active *ref) अणु पूर्ण
अटल अंतरभूत व्योम debug_active_निश्चित(काष्ठा i915_active *ref) अणु पूर्ण

#पूर्ण_अगर

अटल व्योम
__active_retire(काष्ठा i915_active *ref)
अणु
	काष्ठा rb_root root = RB_ROOT;
	काष्ठा active_node *it, *n;
	अचिन्हित दीर्घ flags;

	GEM_BUG_ON(i915_active_is_idle(ref));

	/* वापस the unused nodes to our slabcache -- flushing the allocator */
	अगर (!atomic_dec_and_lock_irqsave(&ref->count, &ref->tree_lock, flags))
		वापस;

	GEM_BUG_ON(rcu_access_poपूर्णांकer(ref->excl.fence));
	debug_active_deactivate(ref);

	/* Even अगर we have not used the cache, we may still have a barrier */
	अगर (!ref->cache)
		ref->cache = fetch_node(ref->tree.rb_node);

	/* Keep the MRU cached node क्रम reuse */
	अगर (ref->cache) अणु
		/* Discard all other nodes in the tree */
		rb_erase(&ref->cache->node, &ref->tree);
		root = ref->tree;

		/* Rebuild the tree with only the cached node */
		rb_link_node(&ref->cache->node, शून्य, &ref->tree.rb_node);
		rb_insert_color(&ref->cache->node, &ref->tree);
		GEM_BUG_ON(ref->tree.rb_node != &ref->cache->node);

		/* Make the cached node available क्रम reuse with any समयline */
		ref->cache->समयline = 0; /* needs cmpxchg(u64) */
	पूर्ण

	spin_unlock_irqrestore(&ref->tree_lock, flags);

	/* After the final retire, the entire काष्ठा may be मुक्तd */
	अगर (ref->retire)
		ref->retire(ref);

	/* ... except अगर you रुको on it, you must manage your own references! */
	wake_up_var(ref);

	/* Finally मुक्त the discarded समयline tree  */
	rbtree_postorder_क्रम_each_entry_safe(it, n, &root, node) अणु
		GEM_BUG_ON(i915_active_fence_isset(&it->base));
		kmem_cache_मुक्त(global.slab_cache, it);
	पूर्ण
पूर्ण

अटल व्योम
active_work(काष्ठा work_काष्ठा *wrk)
अणु
	काष्ठा i915_active *ref = container_of(wrk, typeof(*ref), work);

	GEM_BUG_ON(!atomic_पढ़ो(&ref->count));
	अगर (atomic_add_unless(&ref->count, -1, 1))
		वापस;

	__active_retire(ref);
पूर्ण

अटल व्योम
active_retire(काष्ठा i915_active *ref)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&ref->count));
	अगर (atomic_add_unless(&ref->count, -1, 1))
		वापस;

	अगर (ref->flags & I915_ACTIVE_RETIRE_SLEEPS) अणु
		queue_work(प्रणाली_unbound_wq, &ref->work);
		वापस;
	पूर्ण

	__active_retire(ref);
पूर्ण

अटल अंतरभूत काष्ठा dma_fence **
__active_fence_slot(काष्ठा i915_active_fence *active)
अणु
	वापस (काष्ठा dma_fence ** __क्रमce)&active->fence;
पूर्ण

अटल अंतरभूत bool
active_fence_cb(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा i915_active_fence *active =
		container_of(cb, typeof(*active), cb);

	वापस cmpxchg(__active_fence_slot(active), fence, शून्य) == fence;
पूर्ण

अटल व्योम
node_retire(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	अगर (active_fence_cb(fence, cb))
		active_retire(container_of(cb, काष्ठा active_node, base.cb)->ref);
पूर्ण

अटल व्योम
excl_retire(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	अगर (active_fence_cb(fence, cb))
		active_retire(container_of(cb, काष्ठा i915_active, excl.cb));
पूर्ण

अटल काष्ठा active_node *__active_lookup(काष्ठा i915_active *ref, u64 idx)
अणु
	काष्ठा active_node *it;

	GEM_BUG_ON(idx == 0); /* 0 is the unordered समयline, rsvd क्रम cache */

	/*
	 * We track the most recently used समयline to skip a rbtree search
	 * क्रम the common हाल, under typical loads we never need the rbtree
	 * at all. We can reuse the last slot अगर it is empty, that is
	 * after the previous activity has been retired, or अगर it matches the
	 * current समयline.
	 */
	it = READ_ONCE(ref->cache);
	अगर (it) अणु
		u64 cached = READ_ONCE(it->समयline);

		/* Once claimed, this slot will only beदीर्घ to this idx */
		अगर (cached == idx)
			वापस it;

		/*
		 * An unclaimed cache [.समयline=0] can only be claimed once.
		 *
		 * If the value is alपढ़ोy non-zero, some other thपढ़ो has
		 * claimed the cache and we know that is करोes not match our
		 * idx. If, and only अगर, the समयline is currently zero is it
		 * worth competing to claim it atomically क्रम ourselves (क्रम
		 * only the winner of that race will cmpxchg वापस the old
		 * value of 0).
		 */
		अगर (!cached && !cmpxchg64(&it->समयline, 0, idx))
			वापस it;
	पूर्ण

	BUILD_BUG_ON(दुरत्व(typeof(*it), node));

	/* While active, the tree can only be built; not destroyed */
	GEM_BUG_ON(i915_active_is_idle(ref));

	it = fetch_node(ref->tree.rb_node);
	जबतक (it) अणु
		अगर (it->समयline < idx) अणु
			it = fetch_node(it->node.rb_right);
		पूर्ण अन्यथा अगर (it->समयline > idx) अणु
			it = fetch_node(it->node.rb_left);
		पूर्ण अन्यथा अणु
			WRITE_ONCE(ref->cache, it);
			अवरोध;
		पूर्ण
	पूर्ण

	/* NB: If the tree rotated beneath us, we may miss our target. */
	वापस it;
पूर्ण

अटल काष्ठा i915_active_fence *
active_instance(काष्ठा i915_active *ref, u64 idx)
अणु
	काष्ठा active_node *node;
	काष्ठा rb_node **p, *parent;

	node = __active_lookup(ref, idx);
	अगर (likely(node))
		वापस &node->base;

	spin_lock_irq(&ref->tree_lock);
	GEM_BUG_ON(i915_active_is_idle(ref));

	parent = शून्य;
	p = &ref->tree.rb_node;
	जबतक (*p) अणु
		parent = *p;

		node = rb_entry(parent, काष्ठा active_node, node);
		अगर (node->समयline == idx)
			जाओ out;

		अगर (node->समयline < idx)
			p = &parent->rb_right;
		अन्यथा
			p = &parent->rb_left;
	पूर्ण

	/*
	 * XXX: We should pपुनः_स्मृतिate this beक्रमe i915_active_ref() is ever
	 *  called, but we cannot call पूर्णांकo fs_reclaim() anyway, so use GFP_ATOMIC.
	 */
	node = kmem_cache_alloc(global.slab_cache, GFP_ATOMIC);
	अगर (!node)
		जाओ out;

	__i915_active_fence_init(&node->base, शून्य, node_retire);
	node->ref = ref;
	node->समयline = idx;

	rb_link_node(&node->node, parent, p);
	rb_insert_color(&node->node, &ref->tree);

out:
	WRITE_ONCE(ref->cache, node);
	spin_unlock_irq(&ref->tree_lock);

	वापस &node->base;
पूर्ण

व्योम __i915_active_init(काष्ठा i915_active *ref,
			पूर्णांक (*active)(काष्ठा i915_active *ref),
			व्योम (*retire)(काष्ठा i915_active *ref),
			काष्ठा lock_class_key *mkey,
			काष्ठा lock_class_key *wkey)
अणु
	अचिन्हित दीर्घ bits;

	debug_active_init(ref);

	ref->flags = 0;
	ref->active = active;
	ref->retire = ptr_unpack_bits(retire, &bits, 2);
	अगर (bits & I915_ACTIVE_MAY_SLEEP)
		ref->flags |= I915_ACTIVE_RETIRE_SLEEPS;

	spin_lock_init(&ref->tree_lock);
	ref->tree = RB_ROOT;
	ref->cache = शून्य;

	init_llist_head(&ref->pपुनः_स्मृतिated_barriers);
	atomic_set(&ref->count, 0);
	__mutex_init(&ref->mutex, "i915_active", mkey);
	__i915_active_fence_init(&ref->excl, शून्य, excl_retire);
	INIT_WORK(&ref->work, active_work);
#अगर IS_ENABLED(CONFIG_LOCKDEP)
	lockdep_init_map(&ref->work.lockdep_map, "i915_active.work", wkey, 0);
#पूर्ण_अगर
पूर्ण

अटल bool ____active_del_barrier(काष्ठा i915_active *ref,
				   काष्ठा active_node *node,
				   काष्ठा पूर्णांकel_engine_cs *engine)

अणु
	काष्ठा llist_node *head = शून्य, *tail = शून्य;
	काष्ठा llist_node *pos, *next;

	GEM_BUG_ON(node->समयline != engine->kernel_context->समयline->fence_context);

	/*
	 * Rebuild the llist excluding our node. We may perक्रमm this
	 * outside of the kernel_context समयline mutex and so someone
	 * अन्यथा may be manipulating the engine->barrier_tasks, in
	 * which हाल either we or they will be upset :)
	 *
	 * A second __active_del_barrier() will report failure to claim
	 * the active_node and the caller will just shrug and know not to
	 * claim ownership of its node.
	 *
	 * A concurrent i915_request_add_active_barriers() will miss adding
	 * any of the tasks, but we will try again on the next -- and since
	 * we are actively using the barrier, we know that there will be
	 * at least another opportunity when we idle.
	 */
	llist_क्रम_each_safe(pos, next, llist_del_all(&engine->barrier_tasks)) अणु
		अगर (node == barrier_from_ll(pos)) अणु
			node = शून्य;
			जारी;
		पूर्ण

		pos->next = head;
		head = pos;
		अगर (!tail)
			tail = pos;
	पूर्ण
	अगर (head)
		llist_add_batch(head, tail, &engine->barrier_tasks);

	वापस !node;
पूर्ण

अटल bool
__active_del_barrier(काष्ठा i915_active *ref, काष्ठा active_node *node)
अणु
	वापस ____active_del_barrier(ref, node, barrier_to_engine(node));
पूर्ण

अटल bool
replace_barrier(काष्ठा i915_active *ref, काष्ठा i915_active_fence *active)
अणु
	अगर (!is_barrier(active)) /* proto-node used by our idle barrier? */
		वापस false;

	/*
	 * This request is on the kernel_context समयline, and so
	 * we can use it to substitute क्रम the pending idle-barrer
	 * request that we want to emit on the kernel_context.
	 */
	__active_del_barrier(ref, node_from_active(active));
	वापस true;
पूर्ण

पूर्णांक i915_active_ref(काष्ठा i915_active *ref, u64 idx, काष्ठा dma_fence *fence)
अणु
	काष्ठा i915_active_fence *active;
	पूर्णांक err;

	/* Prevent reaping in हाल we दो_स्मृति/रुको जबतक building the tree */
	err = i915_active_acquire(ref);
	अगर (err)
		वापस err;

	active = active_instance(ref, idx);
	अगर (!active) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (replace_barrier(ref, active)) अणु
		RCU_INIT_POINTER(active->fence, शून्य);
		atomic_dec(&ref->count);
	पूर्ण
	अगर (!__i915_active_fence_set(active, fence))
		__i915_active_acquire(ref);

out:
	i915_active_release(ref);
	वापस err;
पूर्ण

अटल काष्ठा dma_fence *
__i915_active_set_fence(काष्ठा i915_active *ref,
			काष्ठा i915_active_fence *active,
			काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence *prev;

	अगर (replace_barrier(ref, active)) अणु
		RCU_INIT_POINTER(active->fence, fence);
		वापस शून्य;
	पूर्ण

	rcu_पढ़ो_lock();
	prev = __i915_active_fence_set(active, fence);
	अगर (prev)
		prev = dma_fence_get_rcu(prev);
	अन्यथा
		__i915_active_acquire(ref);
	rcu_पढ़ो_unlock();

	वापस prev;
पूर्ण

अटल काष्ठा i915_active_fence *
__active_fence(काष्ठा i915_active *ref, u64 idx)
अणु
	काष्ठा active_node *it;

	it = __active_lookup(ref, idx);
	अगर (unlikely(!it)) अणु /* Contention with parallel tree builders! */
		spin_lock_irq(&ref->tree_lock);
		it = __active_lookup(ref, idx);
		spin_unlock_irq(&ref->tree_lock);
	पूर्ण
	GEM_BUG_ON(!it); /* slot must be pपुनः_स्मृतिated */

	वापस &it->base;
पूर्ण

काष्ठा dma_fence *
__i915_active_ref(काष्ठा i915_active *ref, u64 idx, काष्ठा dma_fence *fence)
अणु
	/* Only valid जबतक active, see i915_active_acquire_क्रम_context() */
	वापस __i915_active_set_fence(ref, __active_fence(ref, idx), fence);
पूर्ण

काष्ठा dma_fence *
i915_active_set_exclusive(काष्ठा i915_active *ref, काष्ठा dma_fence *f)
अणु
	/* We expect the caller to manage the exclusive समयline ordering */
	वापस __i915_active_set_fence(ref, &ref->excl, f);
पूर्ण

bool i915_active_acquire_अगर_busy(काष्ठा i915_active *ref)
अणु
	debug_active_निश्चित(ref);
	वापस atomic_add_unless(&ref->count, 1, 0);
पूर्ण

अटल व्योम __i915_active_activate(काष्ठा i915_active *ref)
अणु
	spin_lock_irq(&ref->tree_lock); /* __active_retire() */
	अगर (!atomic_fetch_inc(&ref->count))
		debug_active_activate(ref);
	spin_unlock_irq(&ref->tree_lock);
पूर्ण

पूर्णांक i915_active_acquire(काष्ठा i915_active *ref)
अणु
	पूर्णांक err;

	अगर (i915_active_acquire_अगर_busy(ref))
		वापस 0;

	अगर (!ref->active) अणु
		__i915_active_activate(ref);
		वापस 0;
	पूर्ण

	err = mutex_lock_पूर्णांकerruptible(&ref->mutex);
	अगर (err)
		वापस err;

	अगर (likely(!i915_active_acquire_अगर_busy(ref))) अणु
		err = ref->active(ref);
		अगर (!err)
			__i915_active_activate(ref);
	पूर्ण

	mutex_unlock(&ref->mutex);

	वापस err;
पूर्ण

पूर्णांक i915_active_acquire_क्रम_context(काष्ठा i915_active *ref, u64 idx)
अणु
	काष्ठा i915_active_fence *active;
	पूर्णांक err;

	err = i915_active_acquire(ref);
	अगर (err)
		वापस err;

	active = active_instance(ref, idx);
	अगर (!active) अणु
		i915_active_release(ref);
		वापस -ENOMEM;
	पूर्ण

	वापस 0; /* वापस with active ref */
पूर्ण

व्योम i915_active_release(काष्ठा i915_active *ref)
अणु
	debug_active_निश्चित(ref);
	active_retire(ref);
पूर्ण

अटल व्योम enable_संकेतing(काष्ठा i915_active_fence *active)
अणु
	काष्ठा dma_fence *fence;

	अगर (unlikely(is_barrier(active)))
		वापस;

	fence = i915_active_fence_get(active);
	अगर (!fence)
		वापस;

	dma_fence_enable_sw_संकेतing(fence);
	dma_fence_put(fence);
पूर्ण

अटल पूर्णांक flush_barrier(काष्ठा active_node *it)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;

	अगर (likely(!is_barrier(&it->base)))
		वापस 0;

	engine = __barrier_to_engine(it);
	smp_rmb(); /* serialise with add_active_barriers */
	अगर (!is_barrier(&it->base))
		वापस 0;

	वापस पूर्णांकel_engine_flush_barriers(engine);
पूर्ण

अटल पूर्णांक flush_lazy_संकेतs(काष्ठा i915_active *ref)
अणु
	काष्ठा active_node *it, *n;
	पूर्णांक err = 0;

	enable_संकेतing(&ref->excl);
	rbtree_postorder_क्रम_each_entry_safe(it, n, &ref->tree, node) अणु
		err = flush_barrier(it); /* unconnected idle barrier? */
		अगर (err)
			अवरोध;

		enable_संकेतing(&it->base);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक __i915_active_रुको(काष्ठा i915_active *ref, पूर्णांक state)
अणु
	might_sleep();

	/* Any fence added after the रुको begins will not be स्वतः-संकेतed */
	अगर (i915_active_acquire_अगर_busy(ref)) अणु
		पूर्णांक err;

		err = flush_lazy_संकेतs(ref);
		i915_active_release(ref);
		अगर (err)
			वापस err;

		अगर (___रुको_var_event(ref, i915_active_is_idle(ref),
				      state, 0, 0, schedule()))
			वापस -EINTR;
	पूर्ण

	/*
	 * After the रुको is complete, the caller may मुक्त the active.
	 * We have to flush any concurrent retirement beक्रमe वापसing.
	 */
	flush_work(&ref->work);
	वापस 0;
पूर्ण

अटल पूर्णांक __aरुको_active(काष्ठा i915_active_fence *active,
			  पूर्णांक (*fn)(व्योम *arg, काष्ठा dma_fence *fence),
			  व्योम *arg)
अणु
	काष्ठा dma_fence *fence;

	अगर (is_barrier(active)) /* XXX flush the barrier? */
		वापस 0;

	fence = i915_active_fence_get(active);
	अगर (fence) अणु
		पूर्णांक err;

		err = fn(arg, fence);
		dma_fence_put(fence);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा रुको_barrier अणु
	काष्ठा रुको_queue_entry base;
	काष्ठा i915_active *ref;
पूर्ण;

अटल पूर्णांक
barrier_wake(रुको_queue_entry_t *wq, अचिन्हित पूर्णांक mode, पूर्णांक flags, व्योम *key)
अणु
	काष्ठा रुको_barrier *wb = container_of(wq, typeof(*wb), base);

	अगर (i915_active_is_idle(wb->ref)) अणु
		list_del(&wq->entry);
		i915_sw_fence_complete(wq->निजी);
		kमुक्त(wq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __aरुको_barrier(काष्ठा i915_active *ref, काष्ठा i915_sw_fence *fence)
अणु
	काष्ठा रुको_barrier *wb;

	wb = kदो_स्मृति(माप(*wb), GFP_KERNEL);
	अगर (unlikely(!wb))
		वापस -ENOMEM;

	GEM_BUG_ON(i915_active_is_idle(ref));
	अगर (!i915_sw_fence_aरुको(fence)) अणु
		kमुक्त(wb);
		वापस -EINVAL;
	पूर्ण

	wb->base.flags = 0;
	wb->base.func = barrier_wake;
	wb->base.निजी = fence;
	wb->ref = ref;

	add_रुको_queue(__var_रुकोqueue(ref), &wb->base);
	वापस 0;
पूर्ण

अटल पूर्णांक aरुको_active(काष्ठा i915_active *ref,
			अचिन्हित पूर्णांक flags,
			पूर्णांक (*fn)(व्योम *arg, काष्ठा dma_fence *fence),
			व्योम *arg, काष्ठा i915_sw_fence *barrier)
अणु
	पूर्णांक err = 0;

	अगर (!i915_active_acquire_अगर_busy(ref))
		वापस 0;

	अगर (flags & I915_ACTIVE_AWAIT_EXCL &&
	    rcu_access_poपूर्णांकer(ref->excl.fence)) अणु
		err = __aरुको_active(&ref->excl, fn, arg);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (flags & I915_ACTIVE_AWAIT_ACTIVE) अणु
		काष्ठा active_node *it, *n;

		rbtree_postorder_क्रम_each_entry_safe(it, n, &ref->tree, node) अणु
			err = __aरुको_active(&it->base, fn, arg);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (flags & I915_ACTIVE_AWAIT_BARRIER) अणु
		err = flush_lazy_संकेतs(ref);
		अगर (err)
			जाओ out;

		err = __aरुको_barrier(ref, barrier);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	i915_active_release(ref);
	वापस err;
पूर्ण

अटल पूर्णांक rq_aरुको_fence(व्योम *arg, काष्ठा dma_fence *fence)
अणु
	वापस i915_request_aरुको_dma_fence(arg, fence);
पूर्ण

पूर्णांक i915_request_aरुको_active(काष्ठा i915_request *rq,
			      काष्ठा i915_active *ref,
			      अचिन्हित पूर्णांक flags)
अणु
	वापस aरुको_active(ref, flags, rq_aरुको_fence, rq, &rq->submit);
पूर्ण

अटल पूर्णांक sw_aरुको_fence(व्योम *arg, काष्ठा dma_fence *fence)
अणु
	वापस i915_sw_fence_aरुको_dma_fence(arg, fence, 0,
					     GFP_NOWAIT | __GFP_NOWARN);
पूर्ण

पूर्णांक i915_sw_fence_aरुको_active(काष्ठा i915_sw_fence *fence,
			       काष्ठा i915_active *ref,
			       अचिन्हित पूर्णांक flags)
अणु
	वापस aरुको_active(ref, flags, sw_aरुको_fence, fence, fence);
पूर्ण

व्योम i915_active_fini(काष्ठा i915_active *ref)
अणु
	debug_active_fini(ref);
	GEM_BUG_ON(atomic_पढ़ो(&ref->count));
	GEM_BUG_ON(work_pending(&ref->work));
	mutex_destroy(&ref->mutex);

	अगर (ref->cache)
		kmem_cache_मुक्त(global.slab_cache, ref->cache);
पूर्ण

अटल अंतरभूत bool is_idle_barrier(काष्ठा active_node *node, u64 idx)
अणु
	वापस node->समयline == idx && !i915_active_fence_isset(&node->base);
पूर्ण

अटल काष्ठा active_node *reuse_idle_barrier(काष्ठा i915_active *ref, u64 idx)
अणु
	काष्ठा rb_node *prev, *p;

	अगर (RB_EMPTY_ROOT(&ref->tree))
		वापस शून्य;

	GEM_BUG_ON(i915_active_is_idle(ref));

	/*
	 * Try to reuse any existing barrier nodes alपढ़ोy allocated क्रम this
	 * i915_active, due to overlapping active phases there is likely a
	 * node kept alive (as we reuse beक्रमe parking). We prefer to reuse
	 * completely idle barriers (less hassle in manipulating the llists),
	 * but otherwise any will करो.
	 */
	अगर (ref->cache && is_idle_barrier(ref->cache, idx)) अणु
		p = &ref->cache->node;
		जाओ match;
	पूर्ण

	prev = शून्य;
	p = ref->tree.rb_node;
	जबतक (p) अणु
		काष्ठा active_node *node =
			rb_entry(p, काष्ठा active_node, node);

		अगर (is_idle_barrier(node, idx))
			जाओ match;

		prev = p;
		अगर (node->समयline < idx)
			p = READ_ONCE(p->rb_right);
		अन्यथा
			p = READ_ONCE(p->rb_left);
	पूर्ण

	/*
	 * No quick match, but we did find the lefपंचांगost rb_node क्रम the
	 * kernel_context. Walk the rb_tree in-order to see अगर there were
	 * any idle-barriers on this समयline that we missed, or just use
	 * the first pending barrier.
	 */
	क्रम (p = prev; p; p = rb_next(p)) अणु
		काष्ठा active_node *node =
			rb_entry(p, काष्ठा active_node, node);
		काष्ठा पूर्णांकel_engine_cs *engine;

		अगर (node->समयline > idx)
			अवरोध;

		अगर (node->समयline < idx)
			जारी;

		अगर (is_idle_barrier(node, idx))
			जाओ match;

		/*
		 * The list of pending barriers is रक्षित by the
		 * kernel_context समयline, which notably we करो not hold
		 * here. i915_request_add_active_barriers() may consume
		 * the barrier beक्रमe we claim it, so we have to check
		 * क्रम success.
		 */
		engine = __barrier_to_engine(node);
		smp_rmb(); /* serialise with add_active_barriers */
		अगर (is_barrier(&node->base) &&
		    ____active_del_barrier(ref, node, engine))
			जाओ match;
	पूर्ण

	वापस शून्य;

match:
	spin_lock_irq(&ref->tree_lock);
	rb_erase(p, &ref->tree); /* Hide from रुकोs and sibling allocations */
	अगर (p == &ref->cache->node)
		WRITE_ONCE(ref->cache, शून्य);
	spin_unlock_irq(&ref->tree_lock);

	वापस rb_entry(p, काष्ठा active_node, node);
पूर्ण

पूर्णांक i915_active_acquire_pपुनः_स्मृतिate_barrier(काष्ठा i915_active *ref,
					    काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_engine_mask_t पंचांगp, mask = engine->mask;
	काष्ठा llist_node *first = शून्य, *last = शून्य;
	काष्ठा पूर्णांकel_gt *gt = engine->gt;

	GEM_BUG_ON(i915_active_is_idle(ref));

	/* Wait until the previous pपुनः_स्मृतिation is completed */
	जबतक (!llist_empty(&ref->pपुनः_स्मृतिated_barriers))
		cond_resched();

	/*
	 * Pपुनः_स्मृतिate a node क्रम each physical engine supporting the target
	 * engine (remember भव engines have more than one sibling).
	 * We can then use the pपुनः_स्मृतिated nodes in
	 * i915_active_acquire_barrier()
	 */
	GEM_BUG_ON(!mask);
	क्रम_each_engine_masked(engine, gt, mask, पंचांगp) अणु
		u64 idx = engine->kernel_context->समयline->fence_context;
		काष्ठा llist_node *prev = first;
		काष्ठा active_node *node;

		rcu_पढ़ो_lock();
		node = reuse_idle_barrier(ref, idx);
		rcu_पढ़ो_unlock();
		अगर (!node) अणु
			node = kmem_cache_alloc(global.slab_cache, GFP_KERNEL);
			अगर (!node)
				जाओ unwind;

			RCU_INIT_POINTER(node->base.fence, शून्य);
			node->base.cb.func = node_retire;
			node->समयline = idx;
			node->ref = ref;
		पूर्ण

		अगर (!i915_active_fence_isset(&node->base)) अणु
			/*
			 * Mark this as being *our* unconnected proto-node.
			 *
			 * Since this node is not in any list, and we have
			 * decoupled it from the rbtree, we can reuse the
			 * request to indicate this is an idle-barrier node
			 * and then we can use the rb_node and list poपूर्णांकers
			 * क्रम our tracking of the pending barrier.
			 */
			RCU_INIT_POINTER(node->base.fence, ERR_PTR(-EAGAIN));
			node->base.cb.node.prev = (व्योम *)engine;
			__i915_active_acquire(ref);
		पूर्ण
		GEM_BUG_ON(rcu_access_poपूर्णांकer(node->base.fence) != ERR_PTR(-EAGAIN));

		GEM_BUG_ON(barrier_to_engine(node) != engine);
		first = barrier_to_ll(node);
		first->next = prev;
		अगर (!last)
			last = first;
		पूर्णांकel_engine_pm_get(engine);
	पूर्ण

	GEM_BUG_ON(!llist_empty(&ref->pपुनः_स्मृतिated_barriers));
	llist_add_batch(first, last, &ref->pपुनः_स्मृतिated_barriers);

	वापस 0;

unwind:
	जबतक (first) अणु
		काष्ठा active_node *node = barrier_from_ll(first);

		first = first->next;

		atomic_dec(&ref->count);
		पूर्णांकel_engine_pm_put(barrier_to_engine(node));

		kmem_cache_मुक्त(global.slab_cache, node);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

व्योम i915_active_acquire_barrier(काष्ठा i915_active *ref)
अणु
	काष्ठा llist_node *pos, *next;
	अचिन्हित दीर्घ flags;

	GEM_BUG_ON(i915_active_is_idle(ref));

	/*
	 * Transfer the list of pपुनः_स्मृतिated barriers पूर्णांकo the
	 * i915_active rbtree, but only as proto-nodes. They will be
	 * populated by i915_request_add_active_barriers() to poपूर्णांक to the
	 * request that will eventually release them.
	 */
	llist_क्रम_each_safe(pos, next, take_pपुनः_स्मृतिated_barriers(ref)) अणु
		काष्ठा active_node *node = barrier_from_ll(pos);
		काष्ठा पूर्णांकel_engine_cs *engine = barrier_to_engine(node);
		काष्ठा rb_node **p, *parent;

		spin_lock_irqsave_nested(&ref->tree_lock, flags,
					 SINGLE_DEPTH_NESTING);
		parent = शून्य;
		p = &ref->tree.rb_node;
		जबतक (*p) अणु
			काष्ठा active_node *it;

			parent = *p;

			it = rb_entry(parent, काष्ठा active_node, node);
			अगर (it->समयline < node->समयline)
				p = &parent->rb_right;
			अन्यथा
				p = &parent->rb_left;
		पूर्ण
		rb_link_node(&node->node, parent, p);
		rb_insert_color(&node->node, &ref->tree);
		spin_unlock_irqrestore(&ref->tree_lock, flags);

		GEM_BUG_ON(!पूर्णांकel_engine_pm_is_awake(engine));
		llist_add(barrier_to_ll(node), &engine->barrier_tasks);
		पूर्णांकel_engine_pm_put_delay(engine, 1);
	पूर्ण
पूर्ण

अटल काष्ठा dma_fence **ll_to_fence_slot(काष्ठा llist_node *node)
अणु
	वापस __active_fence_slot(&barrier_from_ll(node)->base);
पूर्ण

व्योम i915_request_add_active_barriers(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;
	काष्ठा llist_node *node, *next;
	अचिन्हित दीर्घ flags;

	GEM_BUG_ON(!पूर्णांकel_context_is_barrier(rq->context));
	GEM_BUG_ON(पूर्णांकel_engine_is_भव(engine));
	GEM_BUG_ON(i915_request_समयline(rq) != engine->kernel_context->समयline);

	node = llist_del_all(&engine->barrier_tasks);
	अगर (!node)
		वापस;
	/*
	 * Attach the list of proto-fences to the in-flight request such
	 * that the parent i915_active will be released when this request
	 * is retired.
	 */
	spin_lock_irqsave(&rq->lock, flags);
	llist_क्रम_each_safe(node, next, node) अणु
		/* serialise with reuse_idle_barrier */
		smp_store_mb(*ll_to_fence_slot(node), &rq->fence);
		list_add_tail((काष्ठा list_head *)node, &rq->fence.cb_list);
	पूर्ण
	spin_unlock_irqrestore(&rq->lock, flags);
पूर्ण

/*
 * __i915_active_fence_set: Update the last active fence aदीर्घ its समयline
 * @active: the active tracker
 * @fence: the new fence (under स्थिरruction)
 *
 * Records the new @fence as the last active fence aदीर्घ its समयline in
 * this active tracker, moving the tracking callbacks from the previous
 * fence onto this one. Returns the previous fence (अगर not alपढ़ोy completed),
 * which the caller must ensure is executed beक्रमe the new fence. To ensure
 * that the order of fences within the समयline of the i915_active_fence is
 * understood, it should be locked by the caller.
 */
काष्ठा dma_fence *
__i915_active_fence_set(काष्ठा i915_active_fence *active,
			काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence *prev;
	अचिन्हित दीर्घ flags;

	अगर (fence == rcu_access_poपूर्णांकer(active->fence))
		वापस fence;

	GEM_BUG_ON(test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags));

	/*
	 * Consider that we have two thपढ़ोs arriving (A and B), with
	 * C alपढ़ोy resident as the active->fence.
	 *
	 * A करोes the xchg first, and so it sees C or शून्य depending
	 * on the timing of the पूर्णांकerrupt handler. If it is शून्य, the
	 * previous fence must have been संकेतed and we know that
	 * we are first on the समयline. If it is still present,
	 * we acquire the lock on that fence and serialise with the पूर्णांकerrupt
	 * handler, in the process removing it from any future पूर्णांकerrupt
	 * callback. A will then रुको on C beक्रमe executing (अगर present).
	 *
	 * As B is second, it sees A as the previous fence and so रुकोs क्रम
	 * it to complete its transition and takes over the occupancy क्रम
	 * itself -- remembering that it needs to रुको on A beक्रमe executing.
	 *
	 * Note the strong ordering of the समयline also provides consistent
	 * nesting rules क्रम the fence->lock; the inner lock is always the
	 * older lock.
	 */
	spin_lock_irqsave(fence->lock, flags);
	prev = xchg(__active_fence_slot(active), fence);
	अगर (prev) अणु
		GEM_BUG_ON(prev == fence);
		spin_lock_nested(prev->lock, SINGLE_DEPTH_NESTING);
		__list_del_entry(&active->cb.node);
		spin_unlock(prev->lock); /* serialise with prev->cb_list */
	पूर्ण
	list_add_tail(&active->cb.node, &fence->cb_list);
	spin_unlock_irqrestore(fence->lock, flags);

	वापस prev;
पूर्ण

पूर्णांक i915_active_fence_set(काष्ठा i915_active_fence *active,
			  काष्ठा i915_request *rq)
अणु
	काष्ठा dma_fence *fence;
	पूर्णांक err = 0;

	/* Must मुख्यtain समयline ordering wrt previous active requests */
	rcu_पढ़ो_lock();
	fence = __i915_active_fence_set(active, &rq->fence);
	अगर (fence) /* but the previous fence may not beदीर्घ to that समयline! */
		fence = dma_fence_get_rcu(fence);
	rcu_पढ़ो_unlock();
	अगर (fence) अणु
		err = i915_request_aरुको_dma_fence(rq, fence);
		dma_fence_put(fence);
	पूर्ण

	वापस err;
पूर्ण

व्योम i915_active_noop(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	active_fence_cb(fence, cb);
पूर्ण

काष्ठा स्वतः_active अणु
	काष्ठा i915_active base;
	काष्ठा kref ref;
पूर्ण;

काष्ठा i915_active *i915_active_get(काष्ठा i915_active *ref)
अणु
	काष्ठा स्वतः_active *aa = container_of(ref, typeof(*aa), base);

	kref_get(&aa->ref);
	वापस &aa->base;
पूर्ण

अटल व्योम स्वतः_release(काष्ठा kref *ref)
अणु
	काष्ठा स्वतः_active *aa = container_of(ref, typeof(*aa), ref);

	i915_active_fini(&aa->base);
	kमुक्त(aa);
पूर्ण

व्योम i915_active_put(काष्ठा i915_active *ref)
अणु
	काष्ठा स्वतः_active *aa = container_of(ref, typeof(*aa), base);

	kref_put(&aa->ref, स्वतः_release);
पूर्ण

अटल पूर्णांक स्वतः_active(काष्ठा i915_active *ref)
अणु
	i915_active_get(ref);
	वापस 0;
पूर्ण

__i915_active_call अटल व्योम
स्वतः_retire(काष्ठा i915_active *ref)
अणु
	i915_active_put(ref);
पूर्ण

काष्ठा i915_active *i915_active_create(व्योम)
अणु
	काष्ठा स्वतः_active *aa;

	aa = kदो_स्मृति(माप(*aa), GFP_KERNEL);
	अगर (!aa)
		वापस शून्य;

	kref_init(&aa->ref);
	i915_active_init(&aa->base, स्वतः_active, स्वतः_retire);

	वापस &aa->base;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_active.c"
#पूर्ण_अगर

अटल व्योम i915_global_active_shrink(व्योम)
अणु
	kmem_cache_shrink(global.slab_cache);
पूर्ण

अटल व्योम i915_global_active_निकास(व्योम)
अणु
	kmem_cache_destroy(global.slab_cache);
पूर्ण

अटल काष्ठा i915_global_active global = अणु अणु
	.shrink = i915_global_active_shrink,
	.निकास = i915_global_active_निकास,
पूर्ण पूर्ण;

पूर्णांक __init i915_global_active_init(व्योम)
अणु
	global.slab_cache = KMEM_CACHE(active_node, SLAB_HWCACHE_ALIGN);
	अगर (!global.slab_cache)
		वापस -ENOMEM;

	i915_global_रेजिस्टर(&global.base);
	वापस 0;
पूर्ण
