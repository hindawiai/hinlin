<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "gem/i915_gem_lmem.h"
#समावेश "gem/i915_gem_object.h"

#समावेश "i915_drv.h"
#समावेश "i915_vma.h"
#समावेश "intel_engine.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_ring.h"
#समावेश "intel_timeline.h"

अचिन्हित पूर्णांक पूर्णांकel_ring_update_space(काष्ठा पूर्णांकel_ring *ring)
अणु
	अचिन्हित पूर्णांक space;

	space = __पूर्णांकel_ring_space(ring->head, ring->emit, ring->size);

	ring->space = space;
	वापस space;
पूर्ण

व्योम __पूर्णांकel_ring_pin(काष्ठा पूर्णांकel_ring *ring)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&ring->pin_count));
	atomic_inc(&ring->pin_count);
पूर्ण

पूर्णांक पूर्णांकel_ring_pin(काष्ठा पूर्णांकel_ring *ring, काष्ठा i915_gem_ww_ctx *ww)
अणु
	काष्ठा i915_vma *vma = ring->vma;
	अचिन्हित पूर्णांक flags;
	व्योम *addr;
	पूर्णांक ret;

	अगर (atomic_fetch_inc(&ring->pin_count))
		वापस 0;

	/* Ring wraparound at offset 0 someबार hangs. No idea why. */
	flags = PIN_OFFSET_BIAS | i915_ggtt_pin_bias(vma);

	अगर (i915_gem_object_is_stolen(vma->obj))
		flags |= PIN_MAPPABLE;
	अन्यथा
		flags |= PIN_HIGH;

	ret = i915_ggtt_pin(vma, ww, 0, flags);
	अगर (unlikely(ret))
		जाओ err_unpin;

	अगर (i915_vma_is_map_and_fenceable(vma))
		addr = (व्योम __क्रमce *)i915_vma_pin_iomap(vma);
	अन्यथा
		addr = i915_gem_object_pin_map(vma->obj,
					       i915_coherent_map_type(vma->vm->i915));
	अगर (IS_ERR(addr)) अणु
		ret = PTR_ERR(addr);
		जाओ err_ring;
	पूर्ण

	i915_vma_make_unshrinkable(vma);

	/* Discard any unused bytes beyond that submitted to hw. */
	पूर्णांकel_ring_reset(ring, ring->emit);

	ring->vaddr = addr;
	वापस 0;

err_ring:
	i915_vma_unpin(vma);
err_unpin:
	atomic_dec(&ring->pin_count);
	वापस ret;
पूर्ण

व्योम पूर्णांकel_ring_reset(काष्ठा पूर्णांकel_ring *ring, u32 tail)
अणु
	tail = पूर्णांकel_ring_wrap(ring, tail);
	ring->tail = tail;
	ring->head = tail;
	ring->emit = tail;
	पूर्णांकel_ring_update_space(ring);
पूर्ण

व्योम पूर्णांकel_ring_unpin(काष्ठा पूर्णांकel_ring *ring)
अणु
	काष्ठा i915_vma *vma = ring->vma;

	अगर (!atomic_dec_and_test(&ring->pin_count))
		वापस;

	i915_vma_unset_ggtt_ग_लिखो(vma);
	अगर (i915_vma_is_map_and_fenceable(vma))
		i915_vma_unpin_iomap(vma);
	अन्यथा
		i915_gem_object_unpin_map(vma->obj);

	i915_vma_make_purgeable(vma);
	i915_vma_unpin(vma);
पूर्ण

अटल काष्ठा i915_vma *create_ring_vma(काष्ठा i915_ggtt *ggtt, पूर्णांक size)
अणु
	काष्ठा i915_address_space *vm = &ggtt->vm;
	काष्ठा drm_i915_निजी *i915 = vm->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;

	obj = i915_gem_object_create_lmem(i915, size, I915_BO_ALLOC_VOLATILE);
	अगर (IS_ERR(obj) && i915_ggtt_has_aperture(ggtt))
		obj = i915_gem_object_create_stolen(i915, size);
	अगर (IS_ERR(obj))
		obj = i915_gem_object_create_पूर्णांकernal(i915, size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	/*
	 * Mark ring buffers as पढ़ो-only from GPU side (so no stray overग_लिखोs)
	 * अगर supported by the platक्रमm's GGTT.
	 */
	अगर (vm->has_पढ़ो_only)
		i915_gem_object_set_पढ़ोonly(obj);

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma))
		जाओ err;

	वापस vma;

err:
	i915_gem_object_put(obj);
	वापस vma;
पूर्ण

काष्ठा पूर्णांकel_ring *
पूर्णांकel_engine_create_ring(काष्ठा पूर्णांकel_engine_cs *engine, पूर्णांक size)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;
	काष्ठा पूर्णांकel_ring *ring;
	काष्ठा i915_vma *vma;

	GEM_BUG_ON(!is_घातer_of_2(size));
	GEM_BUG_ON(RING_CTL_SIZE(size) & ~RING_NR_PAGES);

	ring = kzalloc(माप(*ring), GFP_KERNEL);
	अगर (!ring)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&ring->ref);
	ring->size = size;
	ring->wrap = BITS_PER_TYPE(ring->size) - ilog2(size);

	/*
	 * Workaround an erratum on the i830 which causes a hang अगर
	 * the TAIL poपूर्णांकer poपूर्णांकs to within the last 2 cachelines
	 * of the buffer.
	 */
	ring->effective_size = size;
	अगर (IS_I830(i915) || IS_I845G(i915))
		ring->effective_size -= 2 * CACHELINE_BYTES;

	पूर्णांकel_ring_update_space(ring);

	vma = create_ring_vma(engine->gt->ggtt, size);
	अगर (IS_ERR(vma)) अणु
		kमुक्त(ring);
		वापस ERR_CAST(vma);
	पूर्ण
	ring->vma = vma;

	वापस ring;
पूर्ण

व्योम पूर्णांकel_ring_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा पूर्णांकel_ring *ring = container_of(ref, typeof(*ring), ref);

	i915_vma_put(ring->vma);
	kमुक्त(ring);
पूर्ण

अटल noअंतरभूत पूर्णांक
रुको_क्रम_space(काष्ठा पूर्णांकel_ring *ring,
	       काष्ठा पूर्णांकel_समयline *tl,
	       अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा i915_request *target;
	दीर्घ समयout;

	अगर (पूर्णांकel_ring_update_space(ring) >= bytes)
		वापस 0;

	GEM_BUG_ON(list_empty(&tl->requests));
	list_क्रम_each_entry(target, &tl->requests, link) अणु
		अगर (target->ring != ring)
			जारी;

		/* Would completion of this request मुक्त enough space? */
		अगर (bytes <= __पूर्णांकel_ring_space(target->postfix,
						ring->emit, ring->size))
			अवरोध;
	पूर्ण

	अगर (GEM_WARN_ON(&target->link == &tl->requests))
		वापस -ENOSPC;

	समयout = i915_request_रुको(target,
				    I915_WAIT_INTERRUPTIBLE,
				    MAX_SCHEDULE_TIMEOUT);
	अगर (समयout < 0)
		वापस समयout;

	i915_request_retire_upto(target);

	पूर्णांकel_ring_update_space(ring);
	GEM_BUG_ON(ring->space < bytes);
	वापस 0;
पूर्ण

u32 *पूर्णांकel_ring_begin(काष्ठा i915_request *rq, अचिन्हित पूर्णांक num_dwords)
अणु
	काष्ठा पूर्णांकel_ring *ring = rq->ring;
	स्थिर अचिन्हित पूर्णांक reमुख्य_usable = ring->effective_size - ring->emit;
	स्थिर अचिन्हित पूर्णांक bytes = num_dwords * माप(u32);
	अचिन्हित पूर्णांक need_wrap = 0;
	अचिन्हित पूर्णांक total_bytes;
	u32 *cs;

	/* Packets must be qword aligned. */
	GEM_BUG_ON(num_dwords & 1);

	total_bytes = bytes + rq->reserved_space;
	GEM_BUG_ON(total_bytes > ring->effective_size);

	अगर (unlikely(total_bytes > reमुख्य_usable)) अणु
		स्थिर पूर्णांक reमुख्य_actual = ring->size - ring->emit;

		अगर (bytes > reमुख्य_usable) अणु
			/*
			 * Not enough space क्रम the basic request. So need to
			 * flush out the reमुख्यder and then रुको क्रम
			 * base + reserved.
			 */
			total_bytes += reमुख्य_actual;
			need_wrap = reमुख्य_actual | 1;
		पूर्ण अन्यथा  अणु
			/*
			 * The base request will fit but the reserved space
			 * falls off the end. So we करोn't need an immediate
			 * wrap and only need to effectively रुको क्रम the
			 * reserved size from the start of ringbuffer.
			 */
			total_bytes = rq->reserved_space + reमुख्य_actual;
		पूर्ण
	पूर्ण

	अगर (unlikely(total_bytes > ring->space)) अणु
		पूर्णांक ret;

		/*
		 * Space is reserved in the ringbuffer क्रम finalising the
		 * request, as that cannot be allowed to fail. During request
		 * finalisation, reserved_space is set to 0 to stop the
		 * overallocation and the assumption is that then we never need
		 * to रुको (which has the risk of failing with EINTR).
		 *
		 * See also i915_request_alloc() and i915_request_add().
		 */
		GEM_BUG_ON(!rq->reserved_space);

		ret = रुको_क्रम_space(ring,
				     i915_request_समयline(rq),
				     total_bytes);
		अगर (unlikely(ret))
			वापस ERR_PTR(ret);
	पूर्ण

	अगर (unlikely(need_wrap)) अणु
		need_wrap &= ~1;
		GEM_BUG_ON(need_wrap > ring->space);
		GEM_BUG_ON(ring->emit + need_wrap > ring->size);
		GEM_BUG_ON(!IS_ALIGNED(need_wrap, माप(u64)));

		/* Fill the tail with MI_NOOP */
		स_रखो64(ring->vaddr + ring->emit, 0, need_wrap / माप(u64));
		ring->space -= need_wrap;
		ring->emit = 0;
	पूर्ण

	GEM_BUG_ON(ring->emit > ring->size - bytes);
	GEM_BUG_ON(ring->space < bytes);
	cs = ring->vaddr + ring->emit;
	GEM_DEBUG_EXEC(स_रखो32(cs, POISON_INUSE, bytes / माप(*cs)));
	ring->emit += bytes;
	ring->space -= bytes;

	वापस cs;
पूर्ण

/* Align the ring tail to a cacheline boundary */
पूर्णांक पूर्णांकel_ring_cacheline_align(काष्ठा i915_request *rq)
अणु
	पूर्णांक num_dwords;
	व्योम *cs;

	num_dwords = (rq->ring->emit & (CACHELINE_BYTES - 1)) / माप(u32);
	अगर (num_dwords == 0)
		वापस 0;

	num_dwords = CACHELINE_DWORDS - num_dwords;
	GEM_BUG_ON(num_dwords & 1);

	cs = पूर्णांकel_ring_begin(rq, num_dwords);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	स_रखो64(cs, (u64)MI_NOOP << 32 | MI_NOOP, num_dwords / 2);
	पूर्णांकel_ring_advance(rq, cs + num_dwords);

	GEM_BUG_ON(rq->ring->emit & (CACHELINE_BYTES - 1));
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_ring.c"
#पूर्ण_अगर
