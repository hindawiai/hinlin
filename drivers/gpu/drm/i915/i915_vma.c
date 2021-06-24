<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
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
#समावेश <drm/drm_gem.h>

#समावेश "display/intel_frontbuffer.h"

#समावेश "gt/intel_engine.h"
#समावेश "gt/intel_engine_heartbeat.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_requests.h"

#समावेश "i915_drv.h"
#समावेश "i915_globals.h"
#समावेश "i915_sw_fence_work.h"
#समावेश "i915_trace.h"
#समावेश "i915_vma.h"

अटल काष्ठा i915_global_vma अणु
	काष्ठा i915_global base;
	काष्ठा kmem_cache *slab_vmas;
पूर्ण global;

काष्ठा i915_vma *i915_vma_alloc(व्योम)
अणु
	वापस kmem_cache_zalloc(global.slab_vmas, GFP_KERNEL);
पूर्ण

व्योम i915_vma_मुक्त(काष्ठा i915_vma *vma)
अणु
	वापस kmem_cache_मुक्त(global.slab_vmas, vma);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_ERRLOG_GEM) && IS_ENABLED(CONFIG_DRM_DEBUG_MM)

#समावेश <linux/stackdepot.h>

अटल व्योम vma_prपूर्णांक_allocator(काष्ठा i915_vma *vma, स्थिर अक्षर *reason)
अणु
	अचिन्हित दीर्घ *entries;
	अचिन्हित पूर्णांक nr_entries;
	अक्षर buf[512];

	अगर (!vma->node.stack) अणु
		DRM_DEBUG_DRIVER("vma.node [%08llx + %08llx] %s: unknown owner\n",
				 vma->node.start, vma->node.size, reason);
		वापस;
	पूर्ण

	nr_entries = stack_depot_fetch(vma->node.stack, &entries);
	stack_trace_snprपूर्णांक(buf, माप(buf), entries, nr_entries, 0);
	DRM_DEBUG_DRIVER("vma.node [%08llx + %08llx] %s: inserted at %s\n",
			 vma->node.start, vma->node.size, reason, buf);
पूर्ण

#अन्यथा

अटल व्योम vma_prपूर्णांक_allocator(काष्ठा i915_vma *vma, स्थिर अक्षर *reason)
अणु
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत काष्ठा i915_vma *active_to_vma(काष्ठा i915_active *ref)
अणु
	वापस container_of(ref, typeof(काष्ठा i915_vma), active);
पूर्ण

अटल पूर्णांक __i915_vma_active(काष्ठा i915_active *ref)
अणु
	वापस i915_vma_tryget(active_to_vma(ref)) ? 0 : -ENOENT;
पूर्ण

__i915_active_call
अटल व्योम __i915_vma_retire(काष्ठा i915_active *ref)
अणु
	i915_vma_put(active_to_vma(ref));
पूर्ण

अटल काष्ठा i915_vma *
vma_create(काष्ठा drm_i915_gem_object *obj,
	   काष्ठा i915_address_space *vm,
	   स्थिर काष्ठा i915_ggtt_view *view)
अणु
	काष्ठा i915_vma *pos = ERR_PTR(-E2BIG);
	काष्ठा i915_vma *vma;
	काष्ठा rb_node *rb, **p;

	/* The aliasing_ppgtt should never be used directly! */
	GEM_BUG_ON(vm == &vm->gt->ggtt->alias->vm);

	vma = i915_vma_alloc();
	अगर (vma == शून्य)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&vma->ref);
	mutex_init(&vma->pages_mutex);
	vma->vm = i915_vm_get(vm);
	vma->ops = &vm->vma_ops;
	vma->obj = obj;
	vma->resv = obj->base.resv;
	vma->size = obj->base.size;
	vma->display_alignment = I915_GTT_MIN_ALIGNMENT;

	i915_active_init(&vma->active, __i915_vma_active, __i915_vma_retire);

	/* Declare ourselves safe क्रम use inside shrinkers */
	अगर (IS_ENABLED(CONFIG_LOCKDEP)) अणु
		fs_reclaim_acquire(GFP_KERNEL);
		might_lock(&vma->active.mutex);
		fs_reclaim_release(GFP_KERNEL);
	पूर्ण

	INIT_LIST_HEAD(&vma->बंदd_link);

	अगर (view && view->type != I915_GGTT_VIEW_NORMAL) अणु
		vma->ggtt_view = *view;
		अगर (view->type == I915_GGTT_VIEW_PARTIAL) अणु
			GEM_BUG_ON(range_overflows_t(u64,
						     view->partial.offset,
						     view->partial.size,
						     obj->base.size >> PAGE_SHIFT));
			vma->size = view->partial.size;
			vma->size <<= PAGE_SHIFT;
			GEM_BUG_ON(vma->size > obj->base.size);
		पूर्ण अन्यथा अगर (view->type == I915_GGTT_VIEW_ROTATED) अणु
			vma->size = पूर्णांकel_rotation_info_size(&view->rotated);
			vma->size <<= PAGE_SHIFT;
		पूर्ण अन्यथा अगर (view->type == I915_GGTT_VIEW_REMAPPED) अणु
			vma->size = पूर्णांकel_remapped_info_size(&view->remapped);
			vma->size <<= PAGE_SHIFT;
		पूर्ण
	पूर्ण

	अगर (unlikely(vma->size > vm->total))
		जाओ err_vma;

	GEM_BUG_ON(!IS_ALIGNED(vma->size, I915_GTT_PAGE_SIZE));

	spin_lock(&obj->vma.lock);

	अगर (i915_is_ggtt(vm)) अणु
		अगर (unlikely(overflows_type(vma->size, u32)))
			जाओ err_unlock;

		vma->fence_size = i915_gem_fence_size(vm->i915, vma->size,
						      i915_gem_object_get_tiling(obj),
						      i915_gem_object_get_stride(obj));
		अगर (unlikely(vma->fence_size < vma->size || /* overflow */
			     vma->fence_size > vm->total))
			जाओ err_unlock;

		GEM_BUG_ON(!IS_ALIGNED(vma->fence_size, I915_GTT_MIN_ALIGNMENT));

		vma->fence_alignment = i915_gem_fence_alignment(vm->i915, vma->size,
								i915_gem_object_get_tiling(obj),
								i915_gem_object_get_stride(obj));
		GEM_BUG_ON(!is_घातer_of_2(vma->fence_alignment));

		__set_bit(I915_VMA_GGTT_BIT, __i915_vma_flags(vma));
	पूर्ण

	rb = शून्य;
	p = &obj->vma.tree.rb_node;
	जबतक (*p) अणु
		दीर्घ cmp;

		rb = *p;
		pos = rb_entry(rb, काष्ठा i915_vma, obj_node);

		/*
		 * If the view alपढ़ोy exists in the tree, another thपढ़ो
		 * alपढ़ोy created a matching vma, so वापस the older instance
		 * and dispose of ours.
		 */
		cmp = i915_vma_compare(pos, vm, view);
		अगर (cmp < 0)
			p = &rb->rb_right;
		अन्यथा अगर (cmp > 0)
			p = &rb->rb_left;
		अन्यथा
			जाओ err_unlock;
	पूर्ण
	rb_link_node(&vma->obj_node, rb, p);
	rb_insert_color(&vma->obj_node, &obj->vma.tree);

	अगर (i915_vma_is_ggtt(vma))
		/*
		 * We put the GGTT vma at the start of the vma-list, followed
		 * by the ppGGTT vma. This allows us to अवरोध early when
		 * iterating over only the GGTT vma क्रम an object, see
		 * क्रम_each_ggtt_vma()
		 */
		list_add(&vma->obj_link, &obj->vma.list);
	अन्यथा
		list_add_tail(&vma->obj_link, &obj->vma.list);

	spin_unlock(&obj->vma.lock);

	वापस vma;

err_unlock:
	spin_unlock(&obj->vma.lock);
err_vma:
	i915_vm_put(vm);
	i915_vma_मुक्त(vma);
	वापस pos;
पूर्ण

अटल काष्ठा i915_vma *
i915_vma_lookup(काष्ठा drm_i915_gem_object *obj,
	   काष्ठा i915_address_space *vm,
	   स्थिर काष्ठा i915_ggtt_view *view)
अणु
	काष्ठा rb_node *rb;

	rb = obj->vma.tree.rb_node;
	जबतक (rb) अणु
		काष्ठा i915_vma *vma = rb_entry(rb, काष्ठा i915_vma, obj_node);
		दीर्घ cmp;

		cmp = i915_vma_compare(vma, vm, view);
		अगर (cmp == 0)
			वापस vma;

		अगर (cmp < 0)
			rb = rb->rb_right;
		अन्यथा
			rb = rb->rb_left;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * i915_vma_instance - वापस the singleton instance of the VMA
 * @obj: parent &काष्ठा drm_i915_gem_object to be mapped
 * @vm: address space in which the mapping is located
 * @view: additional mapping requirements
 *
 * i915_vma_instance() looks up an existing VMA of the @obj in the @vm with
 * the same @view अक्षरacteristics. If a match is not found, one is created.
 * Once created, the VMA is kept until either the object is मुक्तd, or the
 * address space is बंदd.
 *
 * Returns the vma, or an error poपूर्णांकer.
 */
काष्ठा i915_vma *
i915_vma_instance(काष्ठा drm_i915_gem_object *obj,
		  काष्ठा i915_address_space *vm,
		  स्थिर काष्ठा i915_ggtt_view *view)
अणु
	काष्ठा i915_vma *vma;

	GEM_BUG_ON(view && !i915_is_ggtt(vm));
	GEM_BUG_ON(!atomic_पढ़ो(&vm->खोलो));

	spin_lock(&obj->vma.lock);
	vma = i915_vma_lookup(obj, vm, view);
	spin_unlock(&obj->vma.lock);

	/* vma_create() will resolve the race अगर another creates the vma */
	अगर (unlikely(!vma))
		vma = vma_create(obj, vm, view);

	GEM_BUG_ON(!IS_ERR(vma) && i915_vma_compare(vma, vm, view));
	वापस vma;
पूर्ण

काष्ठा i915_vma_work अणु
	काष्ठा dma_fence_work base;
	काष्ठा i915_address_space *vm;
	काष्ठा i915_vm_pt_stash stash;
	काष्ठा i915_vma *vma;
	काष्ठा drm_i915_gem_object *pinned;
	काष्ठा i915_sw_dma_fence_cb cb;
	क्रमागत i915_cache_level cache_level;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल पूर्णांक __vma_bind(काष्ठा dma_fence_work *work)
अणु
	काष्ठा i915_vma_work *vw = container_of(work, typeof(*vw), base);
	काष्ठा i915_vma *vma = vw->vma;

	vma->ops->bind_vma(vw->vm, &vw->stash,
			   vma, vw->cache_level, vw->flags);
	वापस 0;
पूर्ण

अटल व्योम __vma_release(काष्ठा dma_fence_work *work)
अणु
	काष्ठा i915_vma_work *vw = container_of(work, typeof(*vw), base);

	अगर (vw->pinned) अणु
		__i915_gem_object_unpin_pages(vw->pinned);
		i915_gem_object_put(vw->pinned);
	पूर्ण

	i915_vm_मुक्त_pt_stash(vw->vm, &vw->stash);
	i915_vm_put(vw->vm);
पूर्ण

अटल स्थिर काष्ठा dma_fence_work_ops bind_ops = अणु
	.name = "bind",
	.work = __vma_bind,
	.release = __vma_release,
पूर्ण;

काष्ठा i915_vma_work *i915_vma_work(व्योम)
अणु
	काष्ठा i915_vma_work *vw;

	vw = kzalloc(माप(*vw), GFP_KERNEL);
	अगर (!vw)
		वापस शून्य;

	dma_fence_work_init(&vw->base, &bind_ops);
	vw->base.dma.error = -EAGAIN; /* disable the worker by शेष */

	वापस vw;
पूर्ण

पूर्णांक i915_vma_रुको_क्रम_bind(काष्ठा i915_vma *vma)
अणु
	पूर्णांक err = 0;

	अगर (rcu_access_poपूर्णांकer(vma->active.excl.fence)) अणु
		काष्ठा dma_fence *fence;

		rcu_पढ़ो_lock();
		fence = dma_fence_get_rcu_safe(&vma->active.excl.fence);
		rcu_पढ़ो_unlock();
		अगर (fence) अणु
			err = dma_fence_रुको(fence, MAX_SCHEDULE_TIMEOUT);
			dma_fence_put(fence);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * i915_vma_bind - Sets up PTEs क्रम an VMA in it's corresponding address space.
 * @vma: VMA to map
 * @cache_level: mapping cache level
 * @flags: flags like global or local mapping
 * @work: pपुनः_स्मृतिated worker क्रम allocating and binding the PTE
 *
 * DMA addresses are taken from the scatter-gather table of this object (or of
 * this VMA in हाल of non-शेष GGTT views) and PTE entries set up.
 * Note that DMA addresses are also the only part of the SG table we care about.
 */
पूर्णांक i915_vma_bind(काष्ठा i915_vma *vma,
		  क्रमागत i915_cache_level cache_level,
		  u32 flags,
		  काष्ठा i915_vma_work *work)
अणु
	u32 bind_flags;
	u32 vma_flags;

	GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	GEM_BUG_ON(vma->size > vma->node.size);

	अगर (GEM_DEBUG_WARN_ON(range_overflows(vma->node.start,
					      vma->node.size,
					      vma->vm->total)))
		वापस -ENODEV;

	अगर (GEM_DEBUG_WARN_ON(!flags))
		वापस -EINVAL;

	bind_flags = flags;
	bind_flags &= I915_VMA_GLOBAL_BIND | I915_VMA_LOCAL_BIND;

	vma_flags = atomic_पढ़ो(&vma->flags);
	vma_flags &= I915_VMA_GLOBAL_BIND | I915_VMA_LOCAL_BIND;

	bind_flags &= ~vma_flags;
	अगर (bind_flags == 0)
		वापस 0;

	GEM_BUG_ON(!vma->pages);

	trace_i915_vma_bind(vma, bind_flags);
	अगर (work && bind_flags & vma->vm->bind_async_flags) अणु
		काष्ठा dma_fence *prev;

		work->vma = vma;
		work->cache_level = cache_level;
		work->flags = bind_flags;

		/*
		 * Note we only want to chain up to the migration fence on
		 * the pages (not the object itself). As we करोn't track that,
		 * yet, we have to use the exclusive fence instead.
		 *
		 * Also note that we करो not want to track the async vma as
		 * part of the obj->resv->excl_fence as it only affects
		 * execution and not content or object's backing store lअगरeसमय.
		 */
		prev = i915_active_set_exclusive(&vma->active, &work->base.dma);
		अगर (prev) अणु
			__i915_sw_fence_aरुको_dma_fence(&work->base.chain,
							prev,
							&work->cb);
			dma_fence_put(prev);
		पूर्ण

		work->base.dma.error = 0; /* enable the queue_work() */

		अगर (vma->obj) अणु
			__i915_gem_object_pin_pages(vma->obj);
			work->pinned = i915_gem_object_get(vma->obj);
		पूर्ण
	पूर्ण अन्यथा अणु
		vma->ops->bind_vma(vma->vm, शून्य, vma, cache_level, bind_flags);
	पूर्ण

	atomic_or(bind_flags, &vma->flags);
	वापस 0;
पूर्ण

व्योम __iomem *i915_vma_pin_iomap(काष्ठा i915_vma *vma)
अणु
	व्योम __iomem *ptr;
	पूर्णांक err;

	अगर (GEM_WARN_ON(!i915_vma_is_map_and_fenceable(vma))) अणु
		err = -ENODEV;
		जाओ err;
	पूर्ण

	GEM_BUG_ON(!i915_vma_is_ggtt(vma));
	GEM_BUG_ON(!i915_vma_is_bound(vma, I915_VMA_GLOBAL_BIND));

	ptr = READ_ONCE(vma->iomap);
	अगर (ptr == शून्य) अणु
		ptr = io_mapping_map_wc(&i915_vm_to_ggtt(vma->vm)->iomap,
					vma->node.start,
					vma->node.size);
		अगर (ptr == शून्य) अणु
			err = -ENOMEM;
			जाओ err;
		पूर्ण

		अगर (unlikely(cmpxchg(&vma->iomap, शून्य, ptr))) अणु
			io_mapping_unmap(ptr);
			ptr = vma->iomap;
		पूर्ण
	पूर्ण

	__i915_vma_pin(vma);

	err = i915_vma_pin_fence(vma);
	अगर (err)
		जाओ err_unpin;

	i915_vma_set_ggtt_ग_लिखो(vma);

	/* NB Access through the GTT requires the device to be awake. */
	वापस ptr;

err_unpin:
	__i915_vma_unpin(vma);
err:
	वापस IO_ERR_PTR(err);
पूर्ण

व्योम i915_vma_flush_ग_लिखोs(काष्ठा i915_vma *vma)
अणु
	अगर (i915_vma_unset_ggtt_ग_लिखो(vma))
		पूर्णांकel_gt_flush_ggtt_ग_लिखोs(vma->vm->gt);
पूर्ण

व्योम i915_vma_unpin_iomap(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(vma->iomap == शून्य);

	i915_vma_flush_ग_लिखोs(vma);

	i915_vma_unpin_fence(vma);
	i915_vma_unpin(vma);
पूर्ण

व्योम i915_vma_unpin_and_release(काष्ठा i915_vma **p_vma, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i915_vma *vma;
	काष्ठा drm_i915_gem_object *obj;

	vma = fetch_and_zero(p_vma);
	अगर (!vma)
		वापस;

	obj = vma->obj;
	GEM_BUG_ON(!obj);

	i915_vma_unpin(vma);

	अगर (flags & I915_VMA_RELEASE_MAP)
		i915_gem_object_unpin_map(obj);

	i915_gem_object_put(obj);
पूर्ण

bool i915_vma_misplaced(स्थिर काष्ठा i915_vma *vma,
			u64 size, u64 alignment, u64 flags)
अणु
	अगर (!drm_mm_node_allocated(&vma->node))
		वापस false;

	अगर (test_bit(I915_VMA_ERROR_BIT, __i915_vma_flags(vma)))
		वापस true;

	अगर (vma->node.size < size)
		वापस true;

	GEM_BUG_ON(alignment && !is_घातer_of_2(alignment));
	अगर (alignment && !IS_ALIGNED(vma->node.start, alignment))
		वापस true;

	अगर (flags & PIN_MAPPABLE && !i915_vma_is_map_and_fenceable(vma))
		वापस true;

	अगर (flags & PIN_OFFSET_BIAS &&
	    vma->node.start < (flags & PIN_OFFSET_MASK))
		वापस true;

	अगर (flags & PIN_OFFSET_FIXED &&
	    vma->node.start != (flags & PIN_OFFSET_MASK))
		वापस true;

	वापस false;
पूर्ण

व्योम __i915_vma_set_map_and_fenceable(काष्ठा i915_vma *vma)
अणु
	bool mappable, fenceable;

	GEM_BUG_ON(!i915_vma_is_ggtt(vma));
	GEM_BUG_ON(!vma->fence_size);

	fenceable = (vma->node.size >= vma->fence_size &&
		     IS_ALIGNED(vma->node.start, vma->fence_alignment));

	mappable = vma->node.start + vma->fence_size <= i915_vm_to_ggtt(vma->vm)->mappable_end;

	अगर (mappable && fenceable)
		set_bit(I915_VMA_CAN_FENCE_BIT, __i915_vma_flags(vma));
	अन्यथा
		clear_bit(I915_VMA_CAN_FENCE_BIT, __i915_vma_flags(vma));
पूर्ण

bool i915_gem_valid_gtt_space(काष्ठा i915_vma *vma, अचिन्हित दीर्घ color)
अणु
	काष्ठा drm_mm_node *node = &vma->node;
	काष्ठा drm_mm_node *other;

	/*
	 * On some machines we have to be careful when putting dअगरfering types
	 * of snoopable memory together to aव्योम the prefetcher crossing memory
	 * करोमुख्यs and dying. During vm initialisation, we decide whether or not
	 * these स्थिरraपूर्णांकs apply and set the drm_mm.color_adjust
	 * appropriately.
	 */
	अगर (!i915_vm_has_cache_coloring(vma->vm))
		वापस true;

	/* Only valid to be called on an alपढ़ोy inserted vma */
	GEM_BUG_ON(!drm_mm_node_allocated(node));
	GEM_BUG_ON(list_empty(&node->node_list));

	other = list_prev_entry(node, node_list);
	अगर (i915_node_color_dअगरfers(other, color) &&
	    !drm_mm_hole_follows(other))
		वापस false;

	other = list_next_entry(node, node_list);
	अगर (i915_node_color_dअगरfers(other, color) &&
	    !drm_mm_hole_follows(node))
		वापस false;

	वापस true;
पूर्ण

/**
 * i915_vma_insert - finds a slot क्रम the vma in its address space
 * @vma: the vma
 * @size: requested size in bytes (can be larger than the VMA)
 * @alignment: required alignment
 * @flags: mask of PIN_* flags to use
 *
 * First we try to allocate some मुक्त space that meets the requirements क्रम
 * the VMA. Failiing that, अगर the flags permit, it will evict an old VMA,
 * preferrably the oldest idle entry to make room क्रम the new VMA.
 *
 * Returns:
 * 0 on success, negative error code otherwise.
 */
अटल पूर्णांक
i915_vma_insert(काष्ठा i915_vma *vma, u64 size, u64 alignment, u64 flags)
अणु
	अचिन्हित दीर्घ color;
	u64 start, end;
	पूर्णांक ret;

	GEM_BUG_ON(i915_vma_is_bound(vma, I915_VMA_GLOBAL_BIND | I915_VMA_LOCAL_BIND));
	GEM_BUG_ON(drm_mm_node_allocated(&vma->node));

	size = max(size, vma->size);
	alignment = max(alignment, vma->display_alignment);
	अगर (flags & PIN_MAPPABLE) अणु
		size = max_t(typeof(size), size, vma->fence_size);
		alignment = max_t(typeof(alignment),
				  alignment, vma->fence_alignment);
	पूर्ण

	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(!IS_ALIGNED(alignment, I915_GTT_MIN_ALIGNMENT));
	GEM_BUG_ON(!is_घातer_of_2(alignment));

	start = flags & PIN_OFFSET_BIAS ? flags & PIN_OFFSET_MASK : 0;
	GEM_BUG_ON(!IS_ALIGNED(start, I915_GTT_PAGE_SIZE));

	end = vma->vm->total;
	अगर (flags & PIN_MAPPABLE)
		end = min_t(u64, end, i915_vm_to_ggtt(vma->vm)->mappable_end);
	अगर (flags & PIN_ZONE_4G)
		end = min_t(u64, end, (1ULL << 32) - I915_GTT_PAGE_SIZE);
	GEM_BUG_ON(!IS_ALIGNED(end, I915_GTT_PAGE_SIZE));

	/* If binding the object/GGTT view requires more space than the entire
	 * aperture has, reject it early beक्रमe evicting everything in a vain
	 * attempt to find space.
	 */
	अगर (size > end) अणु
		DRM_DEBUG("Attempting to bind an object larger than the aperture: request=%llu > %s aperture=%llu\n",
			  size, flags & PIN_MAPPABLE ? "mappable" : "total",
			  end);
		वापस -ENOSPC;
	पूर्ण

	color = 0;
	अगर (vma->obj && i915_vm_has_cache_coloring(vma->vm))
		color = vma->obj->cache_level;

	अगर (flags & PIN_OFFSET_FIXED) अणु
		u64 offset = flags & PIN_OFFSET_MASK;
		अगर (!IS_ALIGNED(offset, alignment) ||
		    range_overflows(offset, size, end))
			वापस -EINVAL;

		ret = i915_gem_gtt_reserve(vma->vm, &vma->node,
					   size, offset, color,
					   flags);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/*
		 * We only support huge gtt pages through the 48b PPGTT,
		 * however we also करोn't want to क्रमce any alignment क्रम
		 * objects which need to be tightly packed पूर्णांकo the low 32bits.
		 *
		 * Note that we assume that GGTT are limited to 4GiB क्रम the
		 * क्रमseeable future. See also i915_ggtt_offset().
		 */
		अगर (upper_32_bits(end - 1) &&
		    vma->page_sizes.sg > I915_GTT_PAGE_SIZE) अणु
			/*
			 * We can't mix 64K and 4K PTEs in the same page-table
			 * (2M block), and so to aव्योम the ugliness and
			 * complनिकासy of coloring we opt क्रम just aligning 64K
			 * objects to 2M.
			 */
			u64 page_alignment =
				roundकरोwn_घात_of_two(vma->page_sizes.sg |
						     I915_GTT_PAGE_SIZE_2M);

			/*
			 * Check we करोn't expand क्रम the limited Global GTT
			 * (mappable aperture is even more precious!). This
			 * also checks that we exclude the aliasing-ppgtt.
			 */
			GEM_BUG_ON(i915_vma_is_ggtt(vma));

			alignment = max(alignment, page_alignment);

			अगर (vma->page_sizes.sg & I915_GTT_PAGE_SIZE_64K)
				size = round_up(size, I915_GTT_PAGE_SIZE_2M);
		पूर्ण

		ret = i915_gem_gtt_insert(vma->vm, &vma->node,
					  size, alignment, color,
					  start, end, flags);
		अगर (ret)
			वापस ret;

		GEM_BUG_ON(vma->node.start < start);
		GEM_BUG_ON(vma->node.start + vma->node.size > end);
	पूर्ण
	GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	GEM_BUG_ON(!i915_gem_valid_gtt_space(vma, color));

	list_add_tail(&vma->vm_link, &vma->vm->bound_list);

	वापस 0;
पूर्ण

अटल व्योम
i915_vma_detach(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	GEM_BUG_ON(i915_vma_is_bound(vma, I915_VMA_GLOBAL_BIND | I915_VMA_LOCAL_BIND));

	/*
	 * And finally now the object is completely decoupled from this
	 * vma, we can drop its hold on the backing storage and allow
	 * it to be reaped by the shrinker.
	 */
	list_del(&vma->vm_link);
पूर्ण

अटल bool try_qad_pin(काष्ठा i915_vma *vma, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक bound;
	bool pinned = true;

	bound = atomic_पढ़ो(&vma->flags);
	करो अणु
		अगर (unlikely(flags & ~bound))
			वापस false;

		अगर (unlikely(bound & (I915_VMA_OVERFLOW | I915_VMA_ERROR)))
			वापस false;

		अगर (!(bound & I915_VMA_PIN_MASK))
			जाओ unpinned;

		GEM_BUG_ON(((bound + 1) & I915_VMA_PIN_MASK) == 0);
	पूर्ण जबतक (!atomic_try_cmpxchg(&vma->flags, &bound, bound + 1));

	वापस true;

unpinned:
	/*
	 * If pin_count==0, but we are bound, check under the lock to aव्योम
	 * racing with a concurrent i915_vma_unbind().
	 */
	mutex_lock(&vma->vm->mutex);
	करो अणु
		अगर (unlikely(bound & (I915_VMA_OVERFLOW | I915_VMA_ERROR))) अणु
			pinned = false;
			अवरोध;
		पूर्ण

		अगर (unlikely(flags & ~bound)) अणु
			pinned = false;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (!atomic_try_cmpxchg(&vma->flags, &bound, bound + 1));
	mutex_unlock(&vma->vm->mutex);

	वापस pinned;
पूर्ण

अटल पूर्णांक vma_get_pages(काष्ठा i915_vma *vma)
अणु
	पूर्णांक err = 0;

	अगर (atomic_add_unless(&vma->pages_count, 1, 0))
		वापस 0;

	/* Allocations ahoy! */
	अगर (mutex_lock_पूर्णांकerruptible(&vma->pages_mutex))
		वापस -EINTR;

	अगर (!atomic_पढ़ो(&vma->pages_count)) अणु
		अगर (vma->obj) अणु
			err = i915_gem_object_pin_pages(vma->obj);
			अगर (err)
				जाओ unlock;
		पूर्ण

		err = vma->ops->set_pages(vma);
		अगर (err) अणु
			अगर (vma->obj)
				i915_gem_object_unpin_pages(vma->obj);
			जाओ unlock;
		पूर्ण
	पूर्ण
	atomic_inc(&vma->pages_count);

unlock:
	mutex_unlock(&vma->pages_mutex);

	वापस err;
पूर्ण

अटल व्योम __vma_put_pages(काष्ठा i915_vma *vma, अचिन्हित पूर्णांक count)
अणु
	/* We allocate under vma_get_pages, so beware the shrinker */
	mutex_lock_nested(&vma->pages_mutex, SINGLE_DEPTH_NESTING);
	GEM_BUG_ON(atomic_पढ़ो(&vma->pages_count) < count);
	अगर (atomic_sub_वापस(count, &vma->pages_count) == 0) अणु
		vma->ops->clear_pages(vma);
		GEM_BUG_ON(vma->pages);
		अगर (vma->obj)
			i915_gem_object_unpin_pages(vma->obj);
	पूर्ण
	mutex_unlock(&vma->pages_mutex);
पूर्ण

अटल व्योम vma_put_pages(काष्ठा i915_vma *vma)
अणु
	अगर (atomic_add_unless(&vma->pages_count, -1, 1))
		वापस;

	__vma_put_pages(vma, 1);
पूर्ण

अटल व्योम vma_unbind_pages(काष्ठा i915_vma *vma)
अणु
	अचिन्हित पूर्णांक count;

	lockdep_निश्चित_held(&vma->vm->mutex);

	/* The upper portion of pages_count is the number of bindings */
	count = atomic_पढ़ो(&vma->pages_count);
	count >>= I915_VMA_PAGES_BIAS;
	GEM_BUG_ON(!count);

	__vma_put_pages(vma, count | count << I915_VMA_PAGES_BIAS);
पूर्ण

पूर्णांक i915_vma_pin_ww(काष्ठा i915_vma *vma, काष्ठा i915_gem_ww_ctx *ww,
		    u64 size, u64 alignment, u64 flags)
अणु
	काष्ठा i915_vma_work *work = शून्य;
	पूर्णांकel_wakeref_t wakeref = 0;
	अचिन्हित पूर्णांक bound;
	पूर्णांक err;

#अगर_घोषित CONFIG_PROVE_LOCKING
	अगर (debug_locks && !WARN_ON(!ww) && vma->resv)
		निश्चित_vma_held(vma);
#पूर्ण_अगर

	BUILD_BUG_ON(PIN_GLOBAL != I915_VMA_GLOBAL_BIND);
	BUILD_BUG_ON(PIN_USER != I915_VMA_LOCAL_BIND);

	GEM_BUG_ON(!(flags & (PIN_USER | PIN_GLOBAL)));

	/* First try and grab the pin without rebinding the vma */
	अगर (try_qad_pin(vma, flags & I915_VMA_BIND_MASK))
		वापस 0;

	err = vma_get_pages(vma);
	अगर (err)
		वापस err;

	अगर (flags & PIN_GLOBAL)
		wakeref = पूर्णांकel_runसमय_pm_get(&vma->vm->i915->runसमय_pm);

	अगर (flags & vma->vm->bind_async_flags) अणु
		/* lock VM */
		err = i915_vm_lock_objects(vma->vm, ww);
		अगर (err)
			जाओ err_rpm;

		work = i915_vma_work();
		अगर (!work) अणु
			err = -ENOMEM;
			जाओ err_rpm;
		पूर्ण

		work->vm = i915_vm_get(vma->vm);

		/* Allocate enough page directories to used PTE */
		अगर (vma->vm->allocate_va_range) अणु
			err = i915_vm_alloc_pt_stash(vma->vm,
						     &work->stash,
						     vma->size);
			अगर (err)
				जाओ err_fence;

			err = i915_vm_pin_pt_stash(vma->vm,
						   &work->stash);
			अगर (err)
				जाओ err_fence;
		पूर्ण
	पूर्ण

	/*
	 * Dअगरferentiate between user/kernel vma inside the aliasing-ppgtt.
	 *
	 * We conflate the Global GTT with the user's vma when using the
	 * aliasing-ppgtt, but it is still vitally important to try and
	 * keep the use हालs distinct. For example, userptr objects are
	 * not allowed inside the Global GTT as that will cause lock
	 * inversions when we have to evict them the mmu_notअगरier callbacks -
	 * but they are allowed to be part of the user ppGTT which can never
	 * be mapped. As such we try to give the distinct users of the same
	 * mutex, distinct lockclasses [equivalent to how we keep i915_ggtt
	 * and i915_ppgtt separate].
	 *
	 * NB this may cause us to mask real lock inversions -- जबतक the
	 * code is safe today, lockdep may not be able to spot future
	 * transgressions.
	 */
	err = mutex_lock_पूर्णांकerruptible_nested(&vma->vm->mutex,
					      !(flags & PIN_GLOBAL));
	अगर (err)
		जाओ err_fence;

	/* No more allocations allowed now we hold vm->mutex */

	अगर (unlikely(i915_vma_is_बंदd(vma))) अणु
		err = -ENOENT;
		जाओ err_unlock;
	पूर्ण

	bound = atomic_पढ़ो(&vma->flags);
	अगर (unlikely(bound & I915_VMA_ERROR)) अणु
		err = -ENOMEM;
		जाओ err_unlock;
	पूर्ण

	अगर (unlikely(!((bound + 1) & I915_VMA_PIN_MASK))) अणु
		err = -EAGAIN; /* pins are meant to be fairly temporary */
		जाओ err_unlock;
	पूर्ण

	अगर (unlikely(!(flags & ~bound & I915_VMA_BIND_MASK))) अणु
		__i915_vma_pin(vma);
		जाओ err_unlock;
	पूर्ण

	err = i915_active_acquire(&vma->active);
	अगर (err)
		जाओ err_unlock;

	अगर (!(bound & I915_VMA_BIND_MASK)) अणु
		err = i915_vma_insert(vma, size, alignment, flags);
		अगर (err)
			जाओ err_active;

		अगर (i915_is_ggtt(vma->vm))
			__i915_vma_set_map_and_fenceable(vma);
	पूर्ण

	GEM_BUG_ON(!vma->pages);
	err = i915_vma_bind(vma,
			    vma->obj ? vma->obj->cache_level : 0,
			    flags, work);
	अगर (err)
		जाओ err_हटाओ;

	/* There should only be at most 2 active bindings (user, global) */
	GEM_BUG_ON(bound + I915_VMA_PAGES_ACTIVE < bound);
	atomic_add(I915_VMA_PAGES_ACTIVE, &vma->pages_count);
	list_move_tail(&vma->vm_link, &vma->vm->bound_list);

	__i915_vma_pin(vma);
	GEM_BUG_ON(!i915_vma_is_pinned(vma));
	GEM_BUG_ON(!i915_vma_is_bound(vma, flags));
	GEM_BUG_ON(i915_vma_misplaced(vma, size, alignment, flags));

err_हटाओ:
	अगर (!i915_vma_is_bound(vma, I915_VMA_BIND_MASK)) अणु
		i915_vma_detach(vma);
		drm_mm_हटाओ_node(&vma->node);
	पूर्ण
err_active:
	i915_active_release(&vma->active);
err_unlock:
	mutex_unlock(&vma->vm->mutex);
err_fence:
	अगर (work)
		dma_fence_work_commit_imm(&work->base);
err_rpm:
	अगर (wakeref)
		पूर्णांकel_runसमय_pm_put(&vma->vm->i915->runसमय_pm, wakeref);
	vma_put_pages(vma);
	वापस err;
पूर्ण

अटल व्योम flush_idle_contexts(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt, id)
		पूर्णांकel_engine_flush_barriers(engine);

	पूर्णांकel_gt_रुको_क्रम_idle(gt, MAX_SCHEDULE_TIMEOUT);
पूर्ण

पूर्णांक i915_ggtt_pin(काष्ठा i915_vma *vma, काष्ठा i915_gem_ww_ctx *ww,
		  u32 align, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i915_address_space *vm = vma->vm;
	पूर्णांक err;

	GEM_BUG_ON(!i915_vma_is_ggtt(vma));

#अगर_घोषित CONFIG_LOCKDEP
	WARN_ON(!ww && vma->resv && dma_resv_held(vma->resv));
#पूर्ण_अगर

	करो अणु
		अगर (ww)
			err = i915_vma_pin_ww(vma, ww, 0, align, flags | PIN_GLOBAL);
		अन्यथा
			err = i915_vma_pin(vma, 0, align, flags | PIN_GLOBAL);
		अगर (err != -ENOSPC) अणु
			अगर (!err) अणु
				err = i915_vma_रुको_क्रम_bind(vma);
				अगर (err)
					i915_vma_unpin(vma);
			पूर्ण
			वापस err;
		पूर्ण

		/* Unlike i915_vma_pin, we करोn't take no क्रम an answer! */
		flush_idle_contexts(vm->gt);
		अगर (mutex_lock_पूर्णांकerruptible(&vm->mutex) == 0) अणु
			i915_gem_evict_vm(vm);
			mutex_unlock(&vm->mutex);
		पूर्ण
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम __vma_बंद(काष्ठा i915_vma *vma, काष्ठा पूर्णांकel_gt *gt)
अणु
	/*
	 * We defer actually closing, unbinding and destroying the VMA until
	 * the next idle poपूर्णांक, or अगर the object is मुक्तd in the meanसमय. By
	 * postponing the unbind, we allow क्रम it to be resurrected by the
	 * client, aव्योमing the work required to rebind the VMA. This is
	 * advantageous क्रम DRI, where the client/server pass objects
	 * between themselves, temporarily खोलोing a local VMA to the
	 * object, and then closing it again. The same object is then reused
	 * on the next frame (or two, depending on the depth of the swap queue)
	 * causing us to rebind the VMA once more. This ends up being a lot
	 * of wasted work क्रम the steady state.
	 */
	GEM_BUG_ON(i915_vma_is_बंदd(vma));
	list_add(&vma->बंदd_link, &gt->बंदd_vma);
पूर्ण

व्योम i915_vma_बंद(काष्ठा i915_vma *vma)
अणु
	काष्ठा पूर्णांकel_gt *gt = vma->vm->gt;
	अचिन्हित दीर्घ flags;

	अगर (i915_vma_is_ggtt(vma))
		वापस;

	GEM_BUG_ON(!atomic_पढ़ो(&vma->खोलो_count));
	अगर (atomic_dec_and_lock_irqsave(&vma->खोलो_count,
					&gt->बंदd_lock,
					flags)) अणु
		__vma_बंद(vma, gt);
		spin_unlock_irqrestore(&gt->बंदd_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम __i915_vma_हटाओ_बंदd(काष्ठा i915_vma *vma)
अणु
	काष्ठा पूर्णांकel_gt *gt = vma->vm->gt;

	spin_lock_irq(&gt->बंदd_lock);
	list_del_init(&vma->बंदd_link);
	spin_unlock_irq(&gt->बंदd_lock);
पूर्ण

व्योम i915_vma_reखोलो(काष्ठा i915_vma *vma)
अणु
	अगर (i915_vma_is_बंदd(vma))
		__i915_vma_हटाओ_बंदd(vma);
पूर्ण

व्योम i915_vma_release(काष्ठा kref *ref)
अणु
	काष्ठा i915_vma *vma = container_of(ref, typeof(*vma), ref);

	अगर (drm_mm_node_allocated(&vma->node)) अणु
		mutex_lock(&vma->vm->mutex);
		atomic_and(~I915_VMA_PIN_MASK, &vma->flags);
		WARN_ON(__i915_vma_unbind(vma));
		mutex_unlock(&vma->vm->mutex);
		GEM_BUG_ON(drm_mm_node_allocated(&vma->node));
	पूर्ण
	GEM_BUG_ON(i915_vma_is_active(vma));

	अगर (vma->obj) अणु
		काष्ठा drm_i915_gem_object *obj = vma->obj;

		spin_lock(&obj->vma.lock);
		list_del(&vma->obj_link);
		अगर (!RB_EMPTY_NODE(&vma->obj_node))
			rb_erase(&vma->obj_node, &obj->vma.tree);
		spin_unlock(&obj->vma.lock);
	पूर्ण

	__i915_vma_हटाओ_बंदd(vma);
	i915_vm_put(vma->vm);

	i915_active_fini(&vma->active);
	i915_vma_मुक्त(vma);
पूर्ण

व्योम i915_vma_parked(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा i915_vma *vma, *next;
	LIST_HEAD(बंदd);

	spin_lock_irq(&gt->बंदd_lock);
	list_क्रम_each_entry_safe(vma, next, &gt->बंदd_vma, बंदd_link) अणु
		काष्ठा drm_i915_gem_object *obj = vma->obj;
		काष्ठा i915_address_space *vm = vma->vm;

		/* XXX All to aव्योम keeping a reference on i915_vma itself */

		अगर (!kref_get_unless_zero(&obj->base.refcount))
			जारी;

		अगर (!i915_vm_tryखोलो(vm)) अणु
			i915_gem_object_put(obj);
			जारी;
		पूर्ण

		list_move(&vma->बंदd_link, &बंदd);
	पूर्ण
	spin_unlock_irq(&gt->बंदd_lock);

	/* As the GT is held idle, no vma can be reखोलोed as we destroy them */
	list_क्रम_each_entry_safe(vma, next, &बंदd, बंदd_link) अणु
		काष्ठा drm_i915_gem_object *obj = vma->obj;
		काष्ठा i915_address_space *vm = vma->vm;

		INIT_LIST_HEAD(&vma->बंदd_link);
		__i915_vma_put(vma);

		i915_gem_object_put(obj);
		i915_vm_बंद(vm);
	पूर्ण
पूर्ण

अटल व्योम __i915_vma_iounmap(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(i915_vma_is_pinned(vma));

	अगर (vma->iomap == शून्य)
		वापस;

	io_mapping_unmap(vma->iomap);
	vma->iomap = शून्य;
पूर्ण

व्योम i915_vma_revoke_mmap(काष्ठा i915_vma *vma)
अणु
	काष्ठा drm_vma_offset_node *node;
	u64 vma_offset;

	अगर (!i915_vma_has_userfault(vma))
		वापस;

	GEM_BUG_ON(!i915_vma_is_map_and_fenceable(vma));
	GEM_BUG_ON(!vma->obj->userfault_count);

	node = &vma->mmo->vma_node;
	vma_offset = vma->ggtt_view.partial.offset << PAGE_SHIFT;
	unmap_mapping_range(vma->vm->i915->drm.anon_inode->i_mapping,
			    drm_vma_node_offset_addr(node) + vma_offset,
			    vma->size,
			    1);

	i915_vma_unset_userfault(vma);
	अगर (!--vma->obj->userfault_count)
		list_del(&vma->obj->userfault_link);
पूर्ण

अटल पूर्णांक
__i915_request_aरुको_bind(काष्ठा i915_request *rq, काष्ठा i915_vma *vma)
अणु
	वापस __i915_request_aरुको_exclusive(rq, &vma->active);
पूर्ण

पूर्णांक __i915_vma_move_to_active(काष्ठा i915_vma *vma, काष्ठा i915_request *rq)
अणु
	पूर्णांक err;

	GEM_BUG_ON(!i915_vma_is_pinned(vma));

	/* Wait क्रम the vma to be bound beक्रमe we start! */
	err = __i915_request_aरुको_bind(rq, vma);
	अगर (err)
		वापस err;

	वापस i915_active_add_request(&vma->active, rq);
पूर्ण

पूर्णांक i915_vma_move_to_active(काष्ठा i915_vma *vma,
			    काष्ठा i915_request *rq,
			    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा drm_i915_gem_object *obj = vma->obj;
	पूर्णांक err;

	निश्चित_object_held(obj);

	err = __i915_vma_move_to_active(vma, rq);
	अगर (unlikely(err))
		वापस err;

	अगर (flags & EXEC_OBJECT_WRITE) अणु
		काष्ठा पूर्णांकel_frontbuffer *front;

		front = __पूर्णांकel_frontbuffer_get(obj);
		अगर (unlikely(front)) अणु
			अगर (पूर्णांकel_frontbuffer_invalidate(front, ORIGIN_CS))
				i915_active_add_request(&front->ग_लिखो, rq);
			पूर्णांकel_frontbuffer_put(front);
		पूर्ण

		dma_resv_add_excl_fence(vma->resv, &rq->fence);
		obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_RENDER;
		obj->पढ़ो_करोमुख्यs = 0;
	पूर्ण अन्यथा अणु
		अगर (!(flags & __EXEC_OBJECT_NO_RESERVE)) अणु
			err = dma_resv_reserve_shared(vma->resv, 1);
			अगर (unlikely(err))
				वापस err;
		पूर्ण

		dma_resv_add_shared_fence(vma->resv, &rq->fence);
		obj->ग_लिखो_करोमुख्य = 0;
	पूर्ण

	अगर (flags & EXEC_OBJECT_NEEDS_FENCE && vma->fence)
		i915_active_add_request(&vma->fence->active, rq);

	obj->पढ़ो_करोमुख्यs |= I915_GEM_GPU_DOMAINS;
	obj->mm.dirty = true;

	GEM_BUG_ON(!i915_vma_is_active(vma));
	वापस 0;
पूर्ण

व्योम __i915_vma_evict(काष्ठा i915_vma *vma)
अणु
	GEM_BUG_ON(i915_vma_is_pinned(vma));

	अगर (i915_vma_is_map_and_fenceable(vma)) अणु
		/* Force a pagefault क्रम करोमुख्य tracking on next user access */
		i915_vma_revoke_mmap(vma);

		/*
		 * Check that we have flushed all ग_लिखोs through the GGTT
		 * beक्रमe the unbind, other due to non-strict nature of those
		 * indirect ग_लिखोs they may end up referencing the GGTT PTE
		 * after the unbind.
		 *
		 * Note that we may be concurrently poking at the GGTT_WRITE
		 * bit from set-करोमुख्य, as we mark all GGTT vma associated
		 * with an object. We know this is क्रम another vma, as we
		 * are currently unbinding this one -- so अगर this vma will be
		 * reused, it will be refaulted and have its dirty bit set
		 * beक्रमe the next ग_लिखो.
		 */
		i915_vma_flush_ग_लिखोs(vma);

		/* release the fence reg _after_ flushing */
		i915_vma_revoke_fence(vma);

		__i915_vma_iounmap(vma);
		clear_bit(I915_VMA_CAN_FENCE_BIT, __i915_vma_flags(vma));
	पूर्ण
	GEM_BUG_ON(vma->fence);
	GEM_BUG_ON(i915_vma_has_userfault(vma));

	अगर (likely(atomic_पढ़ो(&vma->vm->खोलो))) अणु
		trace_i915_vma_unbind(vma);
		vma->ops->unbind_vma(vma->vm, vma);
	पूर्ण
	atomic_and(~(I915_VMA_BIND_MASK | I915_VMA_ERROR | I915_VMA_GGTT_WRITE),
		   &vma->flags);

	i915_vma_detach(vma);
	vma_unbind_pages(vma);
पूर्ण

पूर्णांक __i915_vma_unbind(काष्ठा i915_vma *vma)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&vma->vm->mutex);

	अगर (!drm_mm_node_allocated(&vma->node))
		वापस 0;

	अगर (i915_vma_is_pinned(vma)) अणु
		vma_prपूर्णांक_allocator(vma, "is pinned");
		वापस -EAGAIN;
	पूर्ण

	/*
	 * After confirming that no one अन्यथा is pinning this vma, रुको क्रम
	 * any laggards who may have crept in during the रुको (through
	 * a residual pin skipping the vm->mutex) to complete.
	 */
	ret = i915_vma_sync(vma);
	अगर (ret)
		वापस ret;

	GEM_BUG_ON(i915_vma_is_active(vma));
	__i915_vma_evict(vma);

	drm_mm_हटाओ_node(&vma->node); /* pairs with i915_vma_release() */
	वापस 0;
पूर्ण

पूर्णांक i915_vma_unbind(काष्ठा i915_vma *vma)
अणु
	काष्ठा i915_address_space *vm = vma->vm;
	पूर्णांकel_wakeref_t wakeref = 0;
	पूर्णांक err;

	/* Optimistic रुको beक्रमe taking the mutex */
	err = i915_vma_sync(vma);
	अगर (err)
		वापस err;

	अगर (!drm_mm_node_allocated(&vma->node))
		वापस 0;

	अगर (i915_vma_is_pinned(vma)) अणु
		vma_prपूर्णांक_allocator(vma, "is pinned");
		वापस -EAGAIN;
	पूर्ण

	अगर (i915_vma_is_bound(vma, I915_VMA_GLOBAL_BIND))
		/* XXX not always required: nop_clear_range */
		wakeref = पूर्णांकel_runसमय_pm_get(&vm->i915->runसमय_pm);

	err = mutex_lock_पूर्णांकerruptible_nested(&vma->vm->mutex, !wakeref);
	अगर (err)
		जाओ out_rpm;

	err = __i915_vma_unbind(vma);
	mutex_unlock(&vm->mutex);

out_rpm:
	अगर (wakeref)
		पूर्णांकel_runसमय_pm_put(&vm->i915->runसमय_pm, wakeref);
	वापस err;
पूर्ण

काष्ठा i915_vma *i915_vma_make_unshrinkable(काष्ठा i915_vma *vma)
अणु
	i915_gem_object_make_unshrinkable(vma->obj);
	वापस vma;
पूर्ण

व्योम i915_vma_make_shrinkable(काष्ठा i915_vma *vma)
अणु
	i915_gem_object_make_shrinkable(vma->obj);
पूर्ण

व्योम i915_vma_make_purgeable(काष्ठा i915_vma *vma)
अणु
	i915_gem_object_make_purgeable(vma->obj);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_vma.c"
#पूर्ण_अगर

अटल व्योम i915_global_vma_shrink(व्योम)
अणु
	kmem_cache_shrink(global.slab_vmas);
पूर्ण

अटल व्योम i915_global_vma_निकास(व्योम)
अणु
	kmem_cache_destroy(global.slab_vmas);
पूर्ण

अटल काष्ठा i915_global_vma global = अणु अणु
	.shrink = i915_global_vma_shrink,
	.निकास = i915_global_vma_निकास,
पूर्ण पूर्ण;

पूर्णांक __init i915_global_vma_init(व्योम)
अणु
	global.slab_vmas = KMEM_CACHE(i915_vma, SLAB_HWCACHE_ALIGN);
	अगर (!global.slab_vmas)
		वापस -ENOMEM;

	i915_global_रेजिस्टर(&global.base);
	वापस 0;
पूर्ण
