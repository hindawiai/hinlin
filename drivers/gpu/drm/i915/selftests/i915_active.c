<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/kref.h>

#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_gt.h"

#समावेश "i915_selftest.h"

#समावेश "igt_flush_test.h"
#समावेश "lib_sw_fence.h"

काष्ठा live_active अणु
	काष्ठा i915_active base;
	काष्ठा kref ref;
	bool retired;
पूर्ण;

अटल व्योम __live_get(काष्ठा live_active *active)
अणु
	kref_get(&active->ref);
पूर्ण

अटल व्योम __live_मुक्त(काष्ठा live_active *active)
अणु
	i915_active_fini(&active->base);
	kमुक्त(active);
पूर्ण

अटल व्योम __live_release(काष्ठा kref *ref)
अणु
	काष्ठा live_active *active = container_of(ref, typeof(*active), ref);

	__live_मुक्त(active);
पूर्ण

अटल व्योम __live_put(काष्ठा live_active *active)
अणु
	kref_put(&active->ref, __live_release);
पूर्ण

अटल पूर्णांक __live_active(काष्ठा i915_active *base)
अणु
	काष्ठा live_active *active = container_of(base, typeof(*active), base);

	__live_get(active);
	वापस 0;
पूर्ण

अटल व्योम __live_retire(काष्ठा i915_active *base)
अणु
	काष्ठा live_active *active = container_of(base, typeof(*active), base);

	active->retired = true;
	__live_put(active);
पूर्ण

अटल काष्ठा live_active *__live_alloc(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा live_active *active;

	active = kzalloc(माप(*active), GFP_KERNEL);
	अगर (!active)
		वापस शून्य;

	kref_init(&active->ref);
	i915_active_init(&active->base, __live_active, __live_retire);

	वापस active;
पूर्ण

अटल काष्ठा live_active *
__live_active_setup(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_sw_fence *submit;
	काष्ठा live_active *active;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक err = 0;

	active = __live_alloc(i915);
	अगर (!active)
		वापस ERR_PTR(-ENOMEM);

	submit = heap_fence_create(GFP_KERNEL);
	अगर (!submit) अणु
		kमुक्त(active);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	err = i915_active_acquire(&active->base);
	अगर (err)
		जाओ out;

	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा i915_request *rq;

		rq = पूर्णांकel_engine_create_kernel_request(engine);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			अवरोध;
		पूर्ण

		err = i915_sw_fence_aरुको_sw_fence_gfp(&rq->submit,
						       submit,
						       GFP_KERNEL);
		अगर (err >= 0)
			err = i915_active_add_request(&active->base, rq);
		i915_request_add(rq);
		अगर (err) अणु
			pr_err("Failed to track active ref!\n");
			अवरोध;
		पूर्ण

		count++;
	पूर्ण

	i915_active_release(&active->base);
	अगर (READ_ONCE(active->retired) && count) अणु
		pr_err("i915_active retired before submission!\n");
		err = -EINVAL;
	पूर्ण
	अगर (atomic_पढ़ो(&active->base.count) != count) अणु
		pr_err("i915_active not tracking all requests, found %d, expected %d\n",
		       atomic_पढ़ो(&active->base.count), count);
		err = -EINVAL;
	पूर्ण

out:
	i915_sw_fence_commit(submit);
	heap_fence_put(submit);
	अगर (err) अणु
		__live_put(active);
		active = ERR_PTR(err);
	पूर्ण

	वापस active;
पूर्ण

अटल पूर्णांक live_active_रुको(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा live_active *active;
	पूर्णांक err = 0;

	/* Check that we get a callback when requests retire upon रुकोing */

	active = __live_active_setup(i915);
	अगर (IS_ERR(active))
		वापस PTR_ERR(active);

	__i915_active_रुको(&active->base, TASK_UNINTERRUPTIBLE);
	अगर (!READ_ONCE(active->retired)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_err_prपूर्णांकer(__func__);

		pr_err("i915_active not retired after waiting!\n");
		i915_active_prपूर्णांक(&active->base, &p);

		err = -EINVAL;
	पूर्ण

	__live_put(active);

	अगर (igt_flush_test(i915))
		err = -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक live_active_retire(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा live_active *active;
	पूर्णांक err = 0;

	/* Check that we get a callback when requests are indirectly retired */

	active = __live_active_setup(i915);
	अगर (IS_ERR(active))
		वापस PTR_ERR(active);

	/* रुकोs क्रम & retires all requests */
	अगर (igt_flush_test(i915))
		err = -EIO;

	अगर (!READ_ONCE(active->retired)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_err_prपूर्णांकer(__func__);

		pr_err("i915_active not retired after flushing!\n");
		i915_active_prपूर्णांक(&active->base, &p);

		err = -EINVAL;
	पूर्ण

	__live_put(active);

	वापस err;
पूर्ण

अटल पूर्णांक live_active_barrier(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा live_active *active;
	पूर्णांक err = 0;

	/* Check that we get a callback when requests retire upon रुकोing */

	active = __live_alloc(i915);
	अगर (!active)
		वापस -ENOMEM;

	err = i915_active_acquire(&active->base);
	अगर (err)
		जाओ out;

	क्रम_each_uabi_engine(engine, i915) अणु
		err = i915_active_acquire_pपुनः_स्मृतिate_barrier(&active->base,
							      engine);
		अगर (err)
			अवरोध;

		i915_active_acquire_barrier(&active->base);
	पूर्ण

	i915_active_release(&active->base);
	अगर (err)
		जाओ out;

	__i915_active_रुको(&active->base, TASK_UNINTERRUPTIBLE);
	अगर (!READ_ONCE(active->retired)) अणु
		pr_err("i915_active not retired after flushing barriers!\n");
		err = -EINVAL;
	पूर्ण

out:
	__live_put(active);

	अगर (igt_flush_test(i915))
		err = -EIO;

	वापस err;
पूर्ण

पूर्णांक i915_active_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_active_रुको),
		SUBTEST(live_active_retire),
		SUBTEST(live_active_barrier),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_subtests(tests, i915);
पूर्ण

अटल काष्ठा पूर्णांकel_engine_cs *node_to_barrier(काष्ठा active_node *it)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;

	अगर (!is_barrier(&it->base))
		वापस शून्य;

	engine = __barrier_to_engine(it);
	smp_rmb(); /* serialise with add_active_barriers */
	अगर (!is_barrier(&it->base))
		वापस शून्य;

	वापस engine;
पूर्ण

व्योम i915_active_prपूर्णांक(काष्ठा i915_active *ref, काष्ठा drm_prपूर्णांकer *m)
अणु
	drm_म_लिखो(m, "active %ps:%ps\n", ref->active, ref->retire);
	drm_म_लिखो(m, "\tcount: %d\n", atomic_पढ़ो(&ref->count));
	drm_म_लिखो(m, "\tpreallocated barriers? %s\n",
		   yesno(!llist_empty(&ref->pपुनः_स्मृतिated_barriers)));

	अगर (i915_active_acquire_अगर_busy(ref)) अणु
		काष्ठा active_node *it, *n;

		rbtree_postorder_क्रम_each_entry_safe(it, n, &ref->tree, node) अणु
			काष्ठा पूर्णांकel_engine_cs *engine;

			engine = node_to_barrier(it);
			अगर (engine) अणु
				drm_म_लिखो(m, "\tbarrier: %s\n", engine->name);
				जारी;
			पूर्ण

			अगर (i915_active_fence_isset(&it->base)) अणु
				drm_म_लिखो(m,
					   "\ttimeline: %llx\n", it->समयline);
				जारी;
			पूर्ण
		पूर्ण

		i915_active_release(ref);
	पूर्ण
पूर्ण

अटल व्योम spin_unlock_रुको(spinlock_t *lock)
अणु
	spin_lock_irq(lock);
	spin_unlock_irq(lock);
पूर्ण

अटल व्योम active_flush(काष्ठा i915_active *ref,
			 काष्ठा i915_active_fence *active)
अणु
	काष्ठा dma_fence *fence;

	fence = xchg(__active_fence_slot(active), शून्य);
	अगर (!fence)
		वापस;

	spin_lock_irq(fence->lock);
	__list_del_entry(&active->cb.node);
	spin_unlock_irq(fence->lock); /* serialise with fence->cb_list */
	atomic_dec(&ref->count);

	GEM_BUG_ON(!test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags));
पूर्ण

व्योम i915_active_unlock_रुको(काष्ठा i915_active *ref)
अणु
	अगर (i915_active_acquire_अगर_busy(ref)) अणु
		काष्ठा active_node *it, *n;

		/* Wait क्रम all active callbacks */
		rcu_पढ़ो_lock();
		active_flush(ref, &ref->excl);
		rbtree_postorder_क्रम_each_entry_safe(it, n, &ref->tree, node)
			active_flush(ref, &it->base);
		rcu_पढ़ो_unlock();

		i915_active_release(ref);
	पूर्ण

	/* And रुको क्रम the retire callback */
	spin_unlock_रुको(&ref->tree_lock);

	/* ... which may have been on a thपढ़ो instead */
	flush_work(&ref->work);
पूर्ण
