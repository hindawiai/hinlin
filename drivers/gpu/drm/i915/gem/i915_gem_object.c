<शैली गुरु>
/*
 * Copyright तऊ 2017 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <linux/sched/mm.h>

#समावेश "display/intel_frontbuffer.h"
#समावेश "i915_drv.h"
#समावेश "i915_gem_clflush.h"
#समावेश "i915_gem_context.h"
#समावेश "i915_gem_mman.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_globals.h"
#समावेश "i915_memcpy.h"
#समावेश "i915_trace.h"

अटल काष्ठा i915_global_object अणु
	काष्ठा i915_global base;
	काष्ठा kmem_cache *slab_objects;
पूर्ण global;

अटल स्थिर काष्ठा drm_gem_object_funcs i915_gem_object_funcs;

काष्ठा drm_i915_gem_object *i915_gem_object_alloc(व्योम)
अणु
	काष्ठा drm_i915_gem_object *obj;

	obj = kmem_cache_zalloc(global.slab_objects, GFP_KERNEL);
	अगर (!obj)
		वापस शून्य;
	obj->base.funcs = &i915_gem_object_funcs;

	वापस obj;
पूर्ण

व्योम i915_gem_object_मुक्त(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस kmem_cache_मुक्त(global.slab_objects, obj);
पूर्ण

व्योम i915_gem_object_init(काष्ठा drm_i915_gem_object *obj,
			  स्थिर काष्ठा drm_i915_gem_object_ops *ops,
			  काष्ठा lock_class_key *key, अचिन्हित flags)
अणु
	spin_lock_init(&obj->vma.lock);
	INIT_LIST_HEAD(&obj->vma.list);

	INIT_LIST_HEAD(&obj->mm.link);

	INIT_LIST_HEAD(&obj->lut_list);
	spin_lock_init(&obj->lut_lock);

	spin_lock_init(&obj->mmo.lock);
	obj->mmo.offsets = RB_ROOT;

	init_rcu_head(&obj->rcu);

	obj->ops = ops;
	GEM_BUG_ON(flags & ~I915_BO_ALLOC_FLAGS);
	obj->flags = flags;

	obj->mm.madv = I915_MADV_WILLNEED;
	INIT_RADIX_TREE(&obj->mm.get_page.radix, GFP_KERNEL | __GFP_NOWARN);
	mutex_init(&obj->mm.get_page.lock);
	INIT_RADIX_TREE(&obj->mm.get_dma_page.radix, GFP_KERNEL | __GFP_NOWARN);
	mutex_init(&obj->mm.get_dma_page.lock);
पूर्ण

/**
 * Mark up the object's coherency levels क्रम a given cache_level
 * @obj: #drm_i915_gem_object
 * @cache_level: cache level
 */
व्योम i915_gem_object_set_cache_coherency(काष्ठा drm_i915_gem_object *obj,
					 अचिन्हित पूर्णांक cache_level)
अणु
	obj->cache_level = cache_level;

	अगर (cache_level != I915_CACHE_NONE)
		obj->cache_coherent = (I915_BO_CACHE_COHERENT_FOR_READ |
				       I915_BO_CACHE_COHERENT_FOR_WRITE);
	अन्यथा अगर (HAS_LLC(to_i915(obj->base.dev)))
		obj->cache_coherent = I915_BO_CACHE_COHERENT_FOR_READ;
	अन्यथा
		obj->cache_coherent = 0;

	obj->cache_dirty =
		!(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_WRITE);
पूर्ण

अटल व्योम i915_gem_बंद_object(काष्ठा drm_gem_object *gem, काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_object *obj = to_पूर्णांकel_bo(gem);
	काष्ठा drm_i915_file_निजी *fpriv = file->driver_priv;
	काष्ठा i915_lut_handle bookmark = अणुपूर्ण;
	काष्ठा i915_mmap_offset *mmo, *mn;
	काष्ठा i915_lut_handle *lut, *ln;
	LIST_HEAD(बंद);

	spin_lock(&obj->lut_lock);
	list_क्रम_each_entry_safe(lut, ln, &obj->lut_list, obj_link) अणु
		काष्ठा i915_gem_context *ctx = lut->ctx;

		अगर (ctx && ctx->file_priv == fpriv) अणु
			i915_gem_context_get(ctx);
			list_move(&lut->obj_link, &बंद);
		पूर्ण

		/* Break दीर्घ locks, and carefully जारी on from this spot */
		अगर (&ln->obj_link != &obj->lut_list) अणु
			list_add_tail(&bookmark.obj_link, &ln->obj_link);
			अगर (cond_resched_lock(&obj->lut_lock))
				list_safe_reset_next(&bookmark, ln, obj_link);
			__list_del_entry(&bookmark.obj_link);
		पूर्ण
	पूर्ण
	spin_unlock(&obj->lut_lock);

	spin_lock(&obj->mmo.lock);
	rbtree_postorder_क्रम_each_entry_safe(mmo, mn, &obj->mmo.offsets, offset)
		drm_vma_node_revoke(&mmo->vma_node, file);
	spin_unlock(&obj->mmo.lock);

	list_क्रम_each_entry_safe(lut, ln, &बंद, obj_link) अणु
		काष्ठा i915_gem_context *ctx = lut->ctx;
		काष्ठा i915_vma *vma;

		/*
		 * We allow the process to have multiple handles to the same
		 * vma, in the same fd namespace, by virtue of flink/खोलो.
		 */

		mutex_lock(&ctx->lut_mutex);
		vma = radix_tree_delete(&ctx->handles_vma, lut->handle);
		अगर (vma) अणु
			GEM_BUG_ON(vma->obj != obj);
			GEM_BUG_ON(!atomic_पढ़ो(&vma->खोलो_count));
			i915_vma_बंद(vma);
		पूर्ण
		mutex_unlock(&ctx->lut_mutex);

		i915_gem_context_put(lut->ctx);
		i915_lut_handle_मुक्त(lut);
		i915_gem_object_put(obj);
	पूर्ण
पूर्ण

अटल व्योम __i915_gem_मुक्त_object_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा drm_i915_gem_object *obj =
		container_of(head, typeof(*obj), rcu);
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);

	dma_resv_fini(&obj->base._resv);
	i915_gem_object_मुक्त(obj);

	GEM_BUG_ON(!atomic_पढ़ो(&i915->mm.मुक्त_count));
	atomic_dec(&i915->mm.मुक्त_count);
पूर्ण

अटल व्योम __i915_gem_object_मुक्त_mmaps(काष्ठा drm_i915_gem_object *obj)
अणु
	/* Skip serialisation and waking the device अगर known to be not used. */

	अगर (obj->userfault_count)
		i915_gem_object_release_mmap_gtt(obj);

	अगर (!RB_EMPTY_ROOT(&obj->mmo.offsets)) अणु
		काष्ठा i915_mmap_offset *mmo, *mn;

		i915_gem_object_release_mmap_offset(obj);

		rbtree_postorder_क्रम_each_entry_safe(mmo, mn,
						     &obj->mmo.offsets,
						     offset) अणु
			drm_vma_offset_हटाओ(obj->base.dev->vma_offset_manager,
					      &mmo->vma_node);
			kमुक्त(mmo);
		पूर्ण
		obj->mmo.offsets = RB_ROOT;
	पूर्ण
पूर्ण

अटल व्योम __i915_gem_मुक्त_objects(काष्ठा drm_i915_निजी *i915,
				    काष्ठा llist_node *मुक्तd)
अणु
	काष्ठा drm_i915_gem_object *obj, *on;

	llist_क्रम_each_entry_safe(obj, on, मुक्तd, मुक्तd) अणु
		trace_i915_gem_object_destroy(obj);

		अगर (!list_empty(&obj->vma.list)) अणु
			काष्ठा i915_vma *vma;

			/*
			 * Note that the vma keeps an object reference जबतक
			 * it is active, so it *should* not sleep जबतक we
			 * destroy it. Our debug code errs insits it *might*.
			 * For the moment, play aदीर्घ.
			 */
			spin_lock(&obj->vma.lock);
			जबतक ((vma = list_first_entry_or_null(&obj->vma.list,
							       काष्ठा i915_vma,
							       obj_link))) अणु
				GEM_BUG_ON(vma->obj != obj);
				spin_unlock(&obj->vma.lock);

				__i915_vma_put(vma);

				spin_lock(&obj->vma.lock);
			पूर्ण
			spin_unlock(&obj->vma.lock);
		पूर्ण

		__i915_gem_object_मुक्त_mmaps(obj);

		GEM_BUG_ON(!list_empty(&obj->lut_list));

		atomic_set(&obj->mm.pages_pin_count, 0);
		__i915_gem_object_put_pages(obj);
		GEM_BUG_ON(i915_gem_object_has_pages(obj));
		biपंचांगap_मुक्त(obj->bit_17);

		अगर (obj->base.import_attach)
			drm_prime_gem_destroy(&obj->base, शून्य);

		drm_gem_मुक्त_mmap_offset(&obj->base);

		अगर (obj->ops->release)
			obj->ops->release(obj);

		/* But keep the poपूर्णांकer alive क्रम RCU-रक्षित lookups */
		call_rcu(&obj->rcu, __i915_gem_मुक्त_object_rcu);
		cond_resched();
	पूर्ण
पूर्ण

व्योम i915_gem_flush_मुक्त_objects(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा llist_node *मुक्तd = llist_del_all(&i915->mm.मुक्त_list);

	अगर (unlikely(मुक्तd))
		__i915_gem_मुक्त_objects(i915, मुक्तd);
पूर्ण

अटल व्योम __i915_gem_मुक्त_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(work, काष्ठा drm_i915_निजी, mm.मुक्त_work);

	i915_gem_flush_मुक्त_objects(i915);
पूर्ण

अटल व्योम i915_gem_मुक्त_object(काष्ठा drm_gem_object *gem_obj)
अणु
	काष्ठा drm_i915_gem_object *obj = to_पूर्णांकel_bo(gem_obj);
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);

	GEM_BUG_ON(i915_gem_object_is_framebuffer(obj));

	/*
	 * Beक्रमe we मुक्त the object, make sure any pure RCU-only
	 * पढ़ो-side critical sections are complete, e.g.
	 * i915_gem_busy_ioctl(). For the corresponding synchronized
	 * lookup see i915_gem_object_lookup_rcu().
	 */
	atomic_inc(&i915->mm.मुक्त_count);

	/*
	 * This serializes मुक्तing with the shrinker. Since the मुक्त
	 * is delayed, first by RCU then by the workqueue, we want the
	 * shrinker to be able to मुक्त pages of unreferenced objects,
	 * or अन्यथा we may oom whilst there are plenty of deferred
	 * मुक्तd objects.
	 */
	i915_gem_object_make_unshrinkable(obj);

	/*
	 * Since we require blocking on काष्ठा_mutex to unbind the मुक्तd
	 * object from the GPU beक्रमe releasing resources back to the
	 * प्रणाली, we can not करो that directly from the RCU callback (which may
	 * be a softirq context), but must instead then defer that work onto a
	 * kthपढ़ो. We use the RCU callback rather than move the मुक्तd object
	 * directly onto the work queue so that we can mix between using the
	 * worker and perक्रमming मुक्तs directly from subsequent allocations क्रम
	 * crude but effective memory throttling.
	 */
	अगर (llist_add(&obj->मुक्तd, &i915->mm.मुक्त_list))
		queue_work(i915->wq, &i915->mm.मुक्त_work);
पूर्ण

व्योम __i915_gem_object_flush_frontbuffer(काष्ठा drm_i915_gem_object *obj,
					 क्रमागत fb_op_origin origin)
अणु
	काष्ठा पूर्णांकel_frontbuffer *front;

	front = __पूर्णांकel_frontbuffer_get(obj);
	अगर (front) अणु
		पूर्णांकel_frontbuffer_flush(front, origin);
		पूर्णांकel_frontbuffer_put(front);
	पूर्ण
पूर्ण

व्योम __i915_gem_object_invalidate_frontbuffer(काष्ठा drm_i915_gem_object *obj,
					      क्रमागत fb_op_origin origin)
अणु
	काष्ठा पूर्णांकel_frontbuffer *front;

	front = __पूर्णांकel_frontbuffer_get(obj);
	अगर (front) अणु
		पूर्णांकel_frontbuffer_invalidate(front, origin);
		पूर्णांकel_frontbuffer_put(front);
	पूर्ण
पूर्ण

अटल व्योम
i915_gem_object_पढ़ो_from_page_kmap(काष्ठा drm_i915_gem_object *obj, u64 offset, व्योम *dst, पूर्णांक size)
अणु
	व्योम *src_map;
	व्योम *src_ptr;

	src_map = kmap_atomic(i915_gem_object_get_page(obj, offset >> PAGE_SHIFT));

	src_ptr = src_map + offset_in_page(offset);
	अगर (!(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
		drm_clflush_virt_range(src_ptr, size);
	स_नकल(dst, src_ptr, size);

	kunmap_atomic(src_map);
पूर्ण

अटल व्योम
i915_gem_object_पढ़ो_from_page_iomap(काष्ठा drm_i915_gem_object *obj, u64 offset, व्योम *dst, पूर्णांक size)
अणु
	व्योम __iomem *src_map;
	व्योम __iomem *src_ptr;
	dma_addr_t dma = i915_gem_object_get_dma_address(obj, offset >> PAGE_SHIFT);

	src_map = io_mapping_map_wc(&obj->mm.region->iomap,
				    dma - obj->mm.region->region.start,
				    PAGE_SIZE);

	src_ptr = src_map + offset_in_page(offset);
	अगर (!i915_स_नकल_from_wc(dst, (व्योम __क्रमce *)src_ptr, size))
		स_नकल_fromio(dst, src_ptr, size);

	io_mapping_unmap(src_map);
पूर्ण

/**
 * i915_gem_object_पढ़ो_from_page - पढ़ो data from the page of a GEM object
 * @obj: GEM object to पढ़ो from
 * @offset: offset within the object
 * @dst: buffer to store the पढ़ो data
 * @size: size to पढ़ो
 *
 * Reads data from @obj at the specअगरied offset. The requested region to पढ़ो
 * from can't cross a page boundary. The caller must ensure that @obj pages
 * are pinned and that @obj is synced wrt. any related ग_लिखोs.
 *
 * Returns 0 on success or -ENODEV अगर the type of @obj's backing store is
 * unsupported.
 */
पूर्णांक i915_gem_object_पढ़ो_from_page(काष्ठा drm_i915_gem_object *obj, u64 offset, व्योम *dst, पूर्णांक size)
अणु
	GEM_BUG_ON(offset >= obj->base.size);
	GEM_BUG_ON(offset_in_page(offset) > PAGE_SIZE - size);
	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));

	अगर (i915_gem_object_has_काष्ठा_page(obj))
		i915_gem_object_पढ़ो_from_page_kmap(obj, offset, dst, size);
	अन्यथा अगर (i915_gem_object_has_iomem(obj))
		i915_gem_object_पढ़ो_from_page_iomap(obj, offset, dst, size);
	अन्यथा
		वापस -ENODEV;

	वापस 0;
पूर्ण

व्योम i915_gem_init__objects(काष्ठा drm_i915_निजी *i915)
अणु
	INIT_WORK(&i915->mm.मुक्त_work, __i915_gem_मुक्त_work);
पूर्ण

अटल व्योम i915_global_objects_shrink(व्योम)
अणु
	kmem_cache_shrink(global.slab_objects);
पूर्ण

अटल व्योम i915_global_objects_निकास(व्योम)
अणु
	kmem_cache_destroy(global.slab_objects);
पूर्ण

अटल काष्ठा i915_global_object global = अणु अणु
	.shrink = i915_global_objects_shrink,
	.निकास = i915_global_objects_निकास,
पूर्ण पूर्ण;

पूर्णांक __init i915_global_objects_init(व्योम)
अणु
	global.slab_objects =
		KMEM_CACHE(drm_i915_gem_object, SLAB_HWCACHE_ALIGN);
	अगर (!global.slab_objects)
		वापस -ENOMEM;

	i915_global_रेजिस्टर(&global.base);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs i915_gem_object_funcs = अणु
	.मुक्त = i915_gem_मुक्त_object,
	.बंद = i915_gem_बंद_object,
	.export = i915_gem_prime_export,
पूर्ण;

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/huge_gem_object.c"
#समावेश "selftests/huge_pages.c"
#समावेश "selftests/i915_gem_object.c"
#समावेश "selftests/i915_gem_coherency.c"
#पूर्ण_अगर
