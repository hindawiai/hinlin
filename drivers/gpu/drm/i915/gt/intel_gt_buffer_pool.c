<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014-2018 Intel Corporation
 */

#समावेश "gem/i915_gem_object.h"

#समावेश "i915_drv.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gt_buffer_pool.h"

अटल काष्ठा पूर्णांकel_gt *to_gt(काष्ठा पूर्णांकel_gt_buffer_pool *pool)
अणु
	वापस container_of(pool, काष्ठा पूर्णांकel_gt, buffer_pool);
पूर्ण

अटल काष्ठा list_head *
bucket_क्रम_size(काष्ठा पूर्णांकel_gt_buffer_pool *pool, माप_प्रकार sz)
अणु
	पूर्णांक n;

	/*
	 * Compute a घातer-of-two bucket, but throw everything greater than
	 * 16KiB पूर्णांकo the same bucket: i.e. the buckets hold objects of
	 * (1 page, 2 pages, 4 pages, 8+ pages).
	 */
	n = fls(sz >> PAGE_SHIFT) - 1;
	अगर (n >= ARRAY_SIZE(pool->cache_list))
		n = ARRAY_SIZE(pool->cache_list) - 1;

	वापस &pool->cache_list[n];
पूर्ण

अटल व्योम node_मुक्त(काष्ठा पूर्णांकel_gt_buffer_pool_node *node)
अणु
	i915_gem_object_put(node->obj);
	i915_active_fini(&node->active);
	kमुक्त_rcu(node, rcu);
पूर्ण

अटल bool pool_मुक्त_older_than(काष्ठा पूर्णांकel_gt_buffer_pool *pool, दीर्घ keep)
अणु
	काष्ठा पूर्णांकel_gt_buffer_pool_node *node, *stale = शून्य;
	bool active = false;
	पूर्णांक n;

	/* Free buffers that have not been used in the past second */
	क्रम (n = 0; n < ARRAY_SIZE(pool->cache_list); n++) अणु
		काष्ठा list_head *list = &pool->cache_list[n];

		अगर (list_empty(list))
			जारी;

		अगर (spin_trylock_irq(&pool->lock)) अणु
			काष्ठा list_head *pos;

			/* Most recent at head; oldest at tail */
			list_क्रम_each_prev(pos, list) अणु
				अचिन्हित दीर्घ age;

				node = list_entry(pos, typeof(*node), link);

				age = READ_ONCE(node->age);
				अगर (!age || jअगरfies - age < keep)
					अवरोध;

				/* Check we are the first to claim this node */
				अगर (!xchg(&node->age, 0))
					अवरोध;

				node->मुक्त = stale;
				stale = node;
			पूर्ण
			अगर (!list_is_last(pos, list))
				__list_del_many(pos, list);

			spin_unlock_irq(&pool->lock);
		पूर्ण

		active |= !list_empty(list);
	पूर्ण

	जबतक ((node = stale)) अणु
		stale = stale->मुक्त;
		node_मुक्त(node);
	पूर्ण

	वापस active;
पूर्ण

अटल व्योम pool_मुक्त_work(काष्ठा work_काष्ठा *wrk)
अणु
	काष्ठा पूर्णांकel_gt_buffer_pool *pool =
		container_of(wrk, typeof(*pool), work.work);

	अगर (pool_मुक्त_older_than(pool, HZ))
		schedule_delayed_work(&pool->work,
				      round_jअगरfies_up_relative(HZ));
पूर्ण

__i915_active_call
अटल व्योम pool_retire(काष्ठा i915_active *ref)
अणु
	काष्ठा पूर्णांकel_gt_buffer_pool_node *node =
		container_of(ref, typeof(*node), active);
	काष्ठा पूर्णांकel_gt_buffer_pool *pool = node->pool;
	काष्ठा list_head *list = bucket_क्रम_size(pool, node->obj->base.size);
	अचिन्हित दीर्घ flags;

	अगर (node->pinned) अणु
		i915_gem_object_unpin_pages(node->obj);

		/* Return this object to the shrinker pool */
		i915_gem_object_make_purgeable(node->obj);
		node->pinned = false;
	पूर्ण

	GEM_BUG_ON(node->age);
	spin_lock_irqsave(&pool->lock, flags);
	list_add_rcu(&node->link, list);
	WRITE_ONCE(node->age, jअगरfies ?: 1); /* 0 reserved क्रम active nodes */
	spin_unlock_irqrestore(&pool->lock, flags);

	schedule_delayed_work(&pool->work,
			      round_jअगरfies_up_relative(HZ));
पूर्ण

व्योम पूर्णांकel_gt_buffer_pool_mark_used(काष्ठा पूर्णांकel_gt_buffer_pool_node *node)
अणु
	निश्चित_object_held(node->obj);

	अगर (node->pinned)
		वापस;

	__i915_gem_object_pin_pages(node->obj);
	/* Hide this pinned object from the shrinker until retired */
	i915_gem_object_make_unshrinkable(node->obj);
	node->pinned = true;
पूर्ण

अटल काष्ठा पूर्णांकel_gt_buffer_pool_node *
node_create(काष्ठा पूर्णांकel_gt_buffer_pool *pool, माप_प्रकार sz,
	    क्रमागत i915_map_type type)
अणु
	काष्ठा पूर्णांकel_gt *gt = to_gt(pool);
	काष्ठा पूर्णांकel_gt_buffer_pool_node *node;
	काष्ठा drm_i915_gem_object *obj;

	node = kदो_स्मृति(माप(*node),
		       GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
	अगर (!node)
		वापस ERR_PTR(-ENOMEM);

	node->age = 0;
	node->pool = pool;
	node->pinned = false;
	i915_active_init(&node->active, शून्य, pool_retire);

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, sz);
	अगर (IS_ERR(obj)) अणु
		i915_active_fini(&node->active);
		kमुक्त(node);
		वापस ERR_CAST(obj);
	पूर्ण

	i915_gem_object_set_पढ़ोonly(obj);

	node->type = type;
	node->obj = obj;
	वापस node;
पूर्ण

काष्ठा पूर्णांकel_gt_buffer_pool_node *
पूर्णांकel_gt_get_buffer_pool(काष्ठा पूर्णांकel_gt *gt, माप_प्रकार size,
			 क्रमागत i915_map_type type)
अणु
	काष्ठा पूर्णांकel_gt_buffer_pool *pool = &gt->buffer_pool;
	काष्ठा पूर्णांकel_gt_buffer_pool_node *node;
	काष्ठा list_head *list;
	पूर्णांक ret;

	size = PAGE_ALIGN(size);
	list = bucket_क्रम_size(pool, size);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(node, list, link) अणु
		अचिन्हित दीर्घ age;

		अगर (node->obj->base.size < size)
			जारी;

		अगर (node->type != type)
			जारी;

		age = READ_ONCE(node->age);
		अगर (!age)
			जारी;

		अगर (cmpxchg(&node->age, age, 0) == age) अणु
			spin_lock_irq(&pool->lock);
			list_del_rcu(&node->link);
			spin_unlock_irq(&pool->lock);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (&node->link == list) अणु
		node = node_create(pool, size, type);
		अगर (IS_ERR(node))
			वापस node;
	पूर्ण

	ret = i915_active_acquire(&node->active);
	अगर (ret) अणु
		node_मुक्त(node);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस node;
पूर्ण

व्योम पूर्णांकel_gt_init_buffer_pool(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_gt_buffer_pool *pool = &gt->buffer_pool;
	पूर्णांक n;

	spin_lock_init(&pool->lock);
	क्रम (n = 0; n < ARRAY_SIZE(pool->cache_list); n++)
		INIT_LIST_HEAD(&pool->cache_list[n]);
	INIT_DELAYED_WORK(&pool->work, pool_मुक्त_work);
पूर्ण

व्योम पूर्णांकel_gt_flush_buffer_pool(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_gt_buffer_pool *pool = &gt->buffer_pool;

	करो अणु
		जबतक (pool_मुक्त_older_than(pool, 0))
			;
	पूर्ण जबतक (cancel_delayed_work_sync(&pool->work));
पूर्ण

व्योम पूर्णांकel_gt_fini_buffer_pool(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_gt_buffer_pool *pool = &gt->buffer_pool;
	पूर्णांक n;

	पूर्णांकel_gt_flush_buffer_pool(gt);

	क्रम (n = 0; n < ARRAY_SIZE(pool->cache_list); n++)
		GEM_BUG_ON(!list_empty(&pool->cache_list[n]));
पूर्ण
