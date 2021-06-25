<शैली गुरु>
/*
 * Copyright 2009 Jerome Glisse.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors:
 *    Jerome Glisse <glisse@मुक्तdesktop.org>
 *    Dave Airlie
 */
#समावेश <linux/seq_file.h>
#समावेश <linux/atomic.h>
#समावेश <linux/रुको.h>
#समावेश <linux/kref.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"

/*
 * Fences
 * Fences mark an event in the GPUs pipeline and are used
 * क्रम GPU/CPU synchronization.  When the fence is written,
 * it is expected that all buffers associated with that fence
 * are no दीर्घer in use by the associated ring on the GPU and
 * that the the relevant GPU caches have been flushed.
 */

काष्ठा amdgpu_fence अणु
	काष्ठा dma_fence base;

	/* RB, DMA, etc. */
	काष्ठा amdgpu_ring		*ring;
पूर्ण;

अटल काष्ठा kmem_cache *amdgpu_fence_slab;

पूर्णांक amdgpu_fence_slab_init(व्योम)
अणु
	amdgpu_fence_slab = kmem_cache_create(
		"amdgpu_fence", माप(काष्ठा amdgpu_fence), 0,
		SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!amdgpu_fence_slab)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम amdgpu_fence_slab_fini(व्योम)
अणु
	rcu_barrier();
	kmem_cache_destroy(amdgpu_fence_slab);
पूर्ण
/*
 * Cast helper
 */
अटल स्थिर काष्ठा dma_fence_ops amdgpu_fence_ops;
अटल अंतरभूत काष्ठा amdgpu_fence *to_amdgpu_fence(काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_fence *__f = container_of(f, काष्ठा amdgpu_fence, base);

	अगर (__f->base.ops == &amdgpu_fence_ops)
		वापस __f;

	वापस शून्य;
पूर्ण

/**
 * amdgpu_fence_ग_लिखो - ग_लिखो a fence value
 *
 * @ring: ring the fence is associated with
 * @seq: sequence number to ग_लिखो
 *
 * Writes a fence value to memory (all asics).
 */
अटल व्योम amdgpu_fence_ग_लिखो(काष्ठा amdgpu_ring *ring, u32 seq)
अणु
	काष्ठा amdgpu_fence_driver *drv = &ring->fence_drv;

	अगर (drv->cpu_addr)
		*drv->cpu_addr = cpu_to_le32(seq);
पूर्ण

/**
 * amdgpu_fence_पढ़ो - पढ़ो a fence value
 *
 * @ring: ring the fence is associated with
 *
 * Reads a fence value from memory (all asics).
 * Returns the value of the fence पढ़ो from memory.
 */
अटल u32 amdgpu_fence_पढ़ो(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_fence_driver *drv = &ring->fence_drv;
	u32 seq = 0;

	अगर (drv->cpu_addr)
		seq = le32_to_cpu(*drv->cpu_addr);
	अन्यथा
		seq = atomic_पढ़ो(&drv->last_seq);

	वापस seq;
पूर्ण

/**
 * amdgpu_fence_emit - emit a fence on the requested ring
 *
 * @ring: ring the fence is associated with
 * @f: resulting fence object
 * @flags: flags to pass पूर्णांकo the subordinate .emit_fence() call
 *
 * Emits a fence command on the requested ring (all asics).
 * Returns 0 on success, -ENOMEM on failure.
 */
पूर्णांक amdgpu_fence_emit(काष्ठा amdgpu_ring *ring, काष्ठा dma_fence **f,
		      अचिन्हित flags)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_fence *fence;
	काष्ठा dma_fence __rcu **ptr;
	uपूर्णांक32_t seq;
	पूर्णांक r;

	fence = kmem_cache_alloc(amdgpu_fence_slab, GFP_KERNEL);
	अगर (fence == शून्य)
		वापस -ENOMEM;

	seq = ++ring->fence_drv.sync_seq;
	fence->ring = ring;
	dma_fence_init(&fence->base, &amdgpu_fence_ops,
		       &ring->fence_drv.lock,
		       adev->fence_context + ring->idx,
		       seq);
	amdgpu_ring_emit_fence(ring, ring->fence_drv.gpu_addr,
			       seq, flags | AMDGPU_FENCE_FLAG_INT);
	pm_runसमय_get_noresume(adev_to_drm(adev)->dev);
	ptr = &ring->fence_drv.fences[seq & ring->fence_drv.num_fences_mask];
	अगर (unlikely(rcu_dereference_रक्षित(*ptr, 1))) अणु
		काष्ठा dma_fence *old;

		rcu_पढ़ो_lock();
		old = dma_fence_get_rcu_safe(ptr);
		rcu_पढ़ो_unlock();

		अगर (old) अणु
			r = dma_fence_रुको(old, false);
			dma_fence_put(old);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	/* This function can't be called concurrently anyway, otherwise
	 * emitting the fence would mess up the hardware ring buffer.
	 */
	rcu_assign_poपूर्णांकer(*ptr, dma_fence_get(&fence->base));

	*f = &fence->base;

	वापस 0;
पूर्ण

/**
 * amdgpu_fence_emit_polling - emit a fence on the requeste ring
 *
 * @ring: ring the fence is associated with
 * @s: resulting sequence number
 * @समयout: the समयout क्रम रुकोing in usecs
 *
 * Emits a fence command on the requested ring (all asics).
 * Used For polling fence.
 * Returns 0 on success, -ENOMEM on failure.
 */
पूर्णांक amdgpu_fence_emit_polling(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t *s,
			      uपूर्णांक32_t समयout)
अणु
	uपूर्णांक32_t seq;
	चिन्हित दीर्घ r;

	अगर (!s)
		वापस -EINVAL;

	seq = ++ring->fence_drv.sync_seq;
	r = amdgpu_fence_रुको_polling(ring,
				      seq - ring->fence_drv.num_fences_mask,
				      समयout);
	अगर (r < 1)
		वापस -ETIMEDOUT;

	amdgpu_ring_emit_fence(ring, ring->fence_drv.gpu_addr,
			       seq, 0);

	*s = seq;

	वापस 0;
पूर्ण

/**
 * amdgpu_fence_schedule_fallback - schedule fallback check
 *
 * @ring: poपूर्णांकer to काष्ठा amdgpu_ring
 *
 * Start a समयr as fallback to our पूर्णांकerrupts.
 */
अटल व्योम amdgpu_fence_schedule_fallback(काष्ठा amdgpu_ring *ring)
अणु
	mod_समयr(&ring->fence_drv.fallback_समयr,
		  jअगरfies + AMDGPU_FENCE_JIFFIES_TIMEOUT);
पूर्ण

/**
 * amdgpu_fence_process - check क्रम fence activity
 *
 * @ring: poपूर्णांकer to काष्ठा amdgpu_ring
 *
 * Checks the current fence value and calculates the last
 * संकेतled fence value. Wakes the fence queue अगर the
 * sequence number has increased.
 *
 * Returns true अगर fence was processed
 */
bool amdgpu_fence_process(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_fence_driver *drv = &ring->fence_drv;
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t seq, last_seq;
	पूर्णांक r;

	करो अणु
		last_seq = atomic_पढ़ो(&ring->fence_drv.last_seq);
		seq = amdgpu_fence_पढ़ो(ring);

	पूर्ण जबतक (atomic_cmpxchg(&drv->last_seq, last_seq, seq) != last_seq);

	अगर (del_समयr(&ring->fence_drv.fallback_समयr) &&
	    seq != ring->fence_drv.sync_seq)
		amdgpu_fence_schedule_fallback(ring);

	अगर (unlikely(seq == last_seq))
		वापस false;

	last_seq &= drv->num_fences_mask;
	seq &= drv->num_fences_mask;

	करो अणु
		काष्ठा dma_fence *fence, **ptr;

		++last_seq;
		last_seq &= drv->num_fences_mask;
		ptr = &drv->fences[last_seq];

		/* There is always exactly one thपढ़ो संकेतing this fence slot */
		fence = rcu_dereference_रक्षित(*ptr, 1);
		RCU_INIT_POINTER(*ptr, शून्य);

		अगर (!fence)
			जारी;

		r = dma_fence_संकेत(fence);
		अगर (!r)
			DMA_FENCE_TRACE(fence, "signaled from irq context\n");
		अन्यथा
			BUG();

		dma_fence_put(fence);
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
	पूर्ण जबतक (last_seq != seq);

	वापस true;
पूर्ण

/**
 * amdgpu_fence_fallback - fallback क्रम hardware पूर्णांकerrupts
 *
 * @t: समयr context used to obtain the poपूर्णांकer to ring काष्ठाure
 *
 * Checks क्रम fence activity.
 */
अटल व्योम amdgpu_fence_fallback(काष्ठा समयr_list *t)
अणु
	काष्ठा amdgpu_ring *ring = from_समयr(ring, t,
					      fence_drv.fallback_समयr);

	अगर (amdgpu_fence_process(ring))
		DRM_WARN("Fence fallback timer expired on ring %s\n", ring->name);
पूर्ण

/**
 * amdgpu_fence_रुको_empty - रुको क्रम all fences to संकेत
 *
 * @ring: ring index the fence is associated with
 *
 * Wait क्रम all fences on the requested ring to संकेत (all asics).
 * Returns 0 अगर the fences have passed, error क्रम all other हालs.
 */
पूर्णांक amdgpu_fence_रुको_empty(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक64_t seq = READ_ONCE(ring->fence_drv.sync_seq);
	काष्ठा dma_fence *fence, **ptr;
	पूर्णांक r;

	अगर (!seq)
		वापस 0;

	ptr = &ring->fence_drv.fences[seq & ring->fence_drv.num_fences_mask];
	rcu_पढ़ो_lock();
	fence = rcu_dereference(*ptr);
	अगर (!fence || !dma_fence_get_rcu(fence)) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	r = dma_fence_रुको(fence, false);
	dma_fence_put(fence);
	वापस r;
पूर्ण

/**
 * amdgpu_fence_रुको_polling - busy रुको क्रम givn sequence number
 *
 * @ring: ring index the fence is associated with
 * @रुको_seq: sequence number to रुको
 * @समयout: the समयout क्रम रुकोing in usecs
 *
 * Wait क्रम all fences on the requested ring to संकेत (all asics).
 * Returns left समय अगर no समयout, 0 or minus अगर समयout.
 */
चिन्हित दीर्घ amdgpu_fence_रुको_polling(काष्ठा amdgpu_ring *ring,
				      uपूर्णांक32_t रुको_seq,
				      चिन्हित दीर्घ समयout)
अणु
	uपूर्णांक32_t seq;

	करो अणु
		seq = amdgpu_fence_पढ़ो(ring);
		udelay(5);
		समयout -= 5;
	पूर्ण जबतक ((पूर्णांक32_t)(रुको_seq - seq) > 0 && समयout > 0);

	वापस समयout > 0 ? समयout : 0;
पूर्ण
/**
 * amdgpu_fence_count_emitted - get the count of emitted fences
 *
 * @ring: ring the fence is associated with
 *
 * Get the number of fences emitted on the requested ring (all asics).
 * Returns the number of emitted fences on the ring.  Used by the
 * dynpm code to ring track activity.
 */
अचिन्हित amdgpu_fence_count_emitted(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक64_t emitted;

	/* We are not रक्षित by ring lock when पढ़ोing the last sequence
	 * but it's ok to report slightly wrong fence count here.
	 */
	amdgpu_fence_process(ring);
	emitted = 0x100000000ull;
	emitted -= atomic_पढ़ो(&ring->fence_drv.last_seq);
	emitted += READ_ONCE(ring->fence_drv.sync_seq);
	वापस lower_32_bits(emitted);
पूर्ण

/**
 * amdgpu_fence_driver_start_ring - make the fence driver
 * पढ़ोy क्रम use on the requested ring.
 *
 * @ring: ring to start the fence driver on
 * @irq_src: पूर्णांकerrupt source to use क्रम this ring
 * @irq_type: पूर्णांकerrupt type to use क्रम this ring
 *
 * Make the fence driver पढ़ोy क्रम processing (all asics).
 * Not all asics have all rings, so each asic will only
 * start the fence driver on the rings it has.
 * Returns 0 क्रम success, errors क्रम failure.
 */
पूर्णांक amdgpu_fence_driver_start_ring(काष्ठा amdgpu_ring *ring,
				   काष्ठा amdgpu_irq_src *irq_src,
				   अचिन्हित irq_type)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक64_t index;

	अगर (ring->funcs->type != AMDGPU_RING_TYPE_UVD) अणु
		ring->fence_drv.cpu_addr = &adev->wb.wb[ring->fence_offs];
		ring->fence_drv.gpu_addr = adev->wb.gpu_addr + (ring->fence_offs * 4);
	पूर्ण अन्यथा अणु
		/* put fence directly behind firmware */
		index = ALIGN(adev->uvd.fw->size, 8);
		ring->fence_drv.cpu_addr = adev->uvd.inst[ring->me].cpu_addr + index;
		ring->fence_drv.gpu_addr = adev->uvd.inst[ring->me].gpu_addr + index;
	पूर्ण
	amdgpu_fence_ग_लिखो(ring, atomic_पढ़ो(&ring->fence_drv.last_seq));

	अगर (irq_src)
		amdgpu_irq_get(adev, irq_src, irq_type);

	ring->fence_drv.irq_src = irq_src;
	ring->fence_drv.irq_type = irq_type;
	ring->fence_drv.initialized = true;

	DRM_DEV_DEBUG(adev->dev, "fence driver on ring %s use gpu addr 0x%016llx\n",
		      ring->name, ring->fence_drv.gpu_addr);
	वापस 0;
पूर्ण

/**
 * amdgpu_fence_driver_init_ring - init the fence driver
 * क्रम the requested ring.
 *
 * @ring: ring to init the fence driver on
 * @num_hw_submission: number of entries on the hardware queue
 *
 * Init the fence driver क्रम the requested ring (all asics).
 * Helper function क्रम amdgpu_fence_driver_init().
 */
पूर्णांक amdgpu_fence_driver_init_ring(काष्ठा amdgpu_ring *ring,
				  अचिन्हित num_hw_submission,
				  atomic_t *sched_score)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	दीर्घ समयout;
	पूर्णांक r;

	अगर (!adev)
		वापस -EINVAL;

	अगर (!is_घातer_of_2(num_hw_submission))
		वापस -EINVAL;

	ring->fence_drv.cpu_addr = शून्य;
	ring->fence_drv.gpu_addr = 0;
	ring->fence_drv.sync_seq = 0;
	atomic_set(&ring->fence_drv.last_seq, 0);
	ring->fence_drv.initialized = false;

	समयr_setup(&ring->fence_drv.fallback_समयr, amdgpu_fence_fallback, 0);

	ring->fence_drv.num_fences_mask = num_hw_submission * 2 - 1;
	spin_lock_init(&ring->fence_drv.lock);
	ring->fence_drv.fences = kसुस्मृति(num_hw_submission * 2, माप(व्योम *),
					 GFP_KERNEL);
	अगर (!ring->fence_drv.fences)
		वापस -ENOMEM;

	/* No need to setup the GPU scheduler क्रम rings that करोn't need it */
	अगर (ring->no_scheduler)
		वापस 0;

	चयन (ring->funcs->type) अणु
	हाल AMDGPU_RING_TYPE_GFX:
		समयout = adev->gfx_समयout;
		अवरोध;
	हाल AMDGPU_RING_TYPE_COMPUTE:
		समयout = adev->compute_समयout;
		अवरोध;
	हाल AMDGPU_RING_TYPE_SDMA:
		समयout = adev->sdma_समयout;
		अवरोध;
	शेष:
		समयout = adev->video_समयout;
		अवरोध;
	पूर्ण

	r = drm_sched_init(&ring->sched, &amdgpu_sched_ops,
			   num_hw_submission, amdgpu_job_hang_limit,
			   समयout, sched_score, ring->name);
	अगर (r) अणु
		DRM_ERROR("Failed to create scheduler on ring %s.\n",
			  ring->name);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * amdgpu_fence_driver_init - init the fence driver
 * क्रम all possible rings.
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Init the fence driver क्रम all possible rings (all asics).
 * Not all asics have all rings, so each asic will only
 * start the fence driver on the rings it has using
 * amdgpu_fence_driver_start_ring().
 * Returns 0 क्रम success.
 */
पूर्णांक amdgpu_fence_driver_init(काष्ठा amdgpu_device *adev)
अणु
	वापस 0;
पूर्ण

/**
 * amdgpu_fence_driver_fini - tear करोwn the fence driver
 * क्रम all possible rings.
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Tear करोwn the fence driver क्रम all possible rings (all asics).
 */
व्योम amdgpu_fence_driver_fini(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i, j;
	पूर्णांक r;

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; i++) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];

		अगर (!ring || !ring->fence_drv.initialized)
			जारी;
		अगर (!ring->no_scheduler)
			drm_sched_fini(&ring->sched);
		r = amdgpu_fence_रुको_empty(ring);
		अगर (r) अणु
			/* no need to trigger GPU reset as we are unloading */
			amdgpu_fence_driver_क्रमce_completion(ring);
		पूर्ण
		अगर (ring->fence_drv.irq_src)
			amdgpu_irq_put(adev, ring->fence_drv.irq_src,
				       ring->fence_drv.irq_type);

		del_समयr_sync(&ring->fence_drv.fallback_समयr);
		क्रम (j = 0; j <= ring->fence_drv.num_fences_mask; ++j)
			dma_fence_put(ring->fence_drv.fences[j]);
		kमुक्त(ring->fence_drv.fences);
		ring->fence_drv.fences = शून्य;
		ring->fence_drv.initialized = false;
	पूर्ण
पूर्ण

/**
 * amdgpu_fence_driver_suspend - suspend the fence driver
 * क्रम all possible rings.
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Suspend the fence driver क्रम all possible rings (all asics).
 */
व्योम amdgpu_fence_driver_suspend(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; i++) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];
		अगर (!ring || !ring->fence_drv.initialized)
			जारी;

		/* रुको क्रम gpu to finish processing current batch */
		r = amdgpu_fence_रुको_empty(ring);
		अगर (r) अणु
			/* delay GPU reset to resume */
			amdgpu_fence_driver_क्रमce_completion(ring);
		पूर्ण

		/* disable the पूर्णांकerrupt */
		अगर (ring->fence_drv.irq_src)
			amdgpu_irq_put(adev, ring->fence_drv.irq_src,
				       ring->fence_drv.irq_type);
	पूर्ण
पूर्ण

/**
 * amdgpu_fence_driver_resume - resume the fence driver
 * क्रम all possible rings.
 *
 * @adev: amdgpu device poपूर्णांकer
 *
 * Resume the fence driver क्रम all possible rings (all asics).
 * Not all asics have all rings, so each asic will only
 * start the fence driver on the rings it has using
 * amdgpu_fence_driver_start_ring().
 * Returns 0 क्रम success.
 */
व्योम amdgpu_fence_driver_resume(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; i++) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];
		अगर (!ring || !ring->fence_drv.initialized)
			जारी;

		/* enable the पूर्णांकerrupt */
		अगर (ring->fence_drv.irq_src)
			amdgpu_irq_get(adev, ring->fence_drv.irq_src,
				       ring->fence_drv.irq_type);
	पूर्ण
पूर्ण

/**
 * amdgpu_fence_driver_क्रमce_completion - क्रमce संकेत latest fence of ring
 *
 * @ring: fence of the ring to संकेत
 *
 */
व्योम amdgpu_fence_driver_क्रमce_completion(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_fence_ग_लिखो(ring, ring->fence_drv.sync_seq);
	amdgpu_fence_process(ring);
पूर्ण

/*
 * Common fence implementation
 */

अटल स्थिर अक्षर *amdgpu_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "amdgpu";
पूर्ण

अटल स्थिर अक्षर *amdgpu_fence_get_समयline_name(काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_fence *fence = to_amdgpu_fence(f);
	वापस (स्थिर अक्षर *)fence->ring->name;
पूर्ण

/**
 * amdgpu_fence_enable_संकेतing - enable संकेतling on fence
 * @f: fence
 *
 * This function is called with fence_queue lock held, and adds a callback
 * to fence_queue that checks अगर this fence is संकेतed, and अगर so it
 * संकेतs the fence and हटाओs itself.
 */
अटल bool amdgpu_fence_enable_संकेतing(काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_fence *fence = to_amdgpu_fence(f);
	काष्ठा amdgpu_ring *ring = fence->ring;

	अगर (!समयr_pending(&ring->fence_drv.fallback_समयr))
		amdgpu_fence_schedule_fallback(ring);

	DMA_FENCE_TRACE(&fence->base, "armed on ring %i!\n", ring->idx);

	वापस true;
पूर्ण

/**
 * amdgpu_fence_मुक्त - मुक्त up the fence memory
 *
 * @rcu: RCU callback head
 *
 * Free up the fence memory after the RCU grace period.
 */
अटल व्योम amdgpu_fence_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा dma_fence *f = container_of(rcu, काष्ठा dma_fence, rcu);
	काष्ठा amdgpu_fence *fence = to_amdgpu_fence(f);
	kmem_cache_मुक्त(amdgpu_fence_slab, fence);
पूर्ण

/**
 * amdgpu_fence_release - callback that fence can be मुक्तd
 *
 * @f: fence
 *
 * This function is called when the reference count becomes zero.
 * It just RCU schedules मुक्तing up the fence.
 */
अटल व्योम amdgpu_fence_release(काष्ठा dma_fence *f)
अणु
	call_rcu(&f->rcu, amdgpu_fence_मुक्त);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops amdgpu_fence_ops = अणु
	.get_driver_name = amdgpu_fence_get_driver_name,
	.get_समयline_name = amdgpu_fence_get_समयline_name,
	.enable_संकेतing = amdgpu_fence_enable_संकेतing,
	.release = amdgpu_fence_release,
पूर्ण;

/*
 * Fence debugfs
 */
#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक amdgpu_debugfs_fence_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	पूर्णांक i;

	क्रम (i = 0; i < AMDGPU_MAX_RINGS; ++i) अणु
		काष्ठा amdgpu_ring *ring = adev->rings[i];
		अगर (!ring || !ring->fence_drv.initialized)
			जारी;

		amdgpu_fence_process(ring);

		seq_म_लिखो(m, "--- ring %d (%s) ---\n", i, ring->name);
		seq_म_लिखो(m, "Last signaled fence          0x%08x\n",
			   atomic_पढ़ो(&ring->fence_drv.last_seq));
		seq_म_लिखो(m, "Last emitted                 0x%08x\n",
			   ring->fence_drv.sync_seq);

		अगर (ring->funcs->type == AMDGPU_RING_TYPE_GFX ||
		    ring->funcs->type == AMDGPU_RING_TYPE_SDMA) अणु
			seq_म_लिखो(m, "Last signaled trailing fence 0x%08x\n",
				   le32_to_cpu(*ring->trail_fence_cpu_addr));
			seq_म_लिखो(m, "Last emitted                 0x%08x\n",
				   ring->trail_seq);
		पूर्ण

		अगर (ring->funcs->type != AMDGPU_RING_TYPE_GFX)
			जारी;

		/* set in CP_VMID_PREEMPT and preemption occurred */
		seq_म_लिखो(m, "Last preempted               0x%08x\n",
			   le32_to_cpu(*(ring->fence_drv.cpu_addr + 2)));
		/* set in CP_VMID_RESET and reset occurred */
		seq_म_लिखो(m, "Last reset                   0x%08x\n",
			   le32_to_cpu(*(ring->fence_drv.cpu_addr + 4)));
		/* Both preemption and reset occurred */
		seq_म_लिखो(m, "Last both                    0x%08x\n",
			   le32_to_cpu(*(ring->fence_drv.cpu_addr + 6)));
	पूर्ण
	वापस 0;
पूर्ण

/*
 * amdgpu_debugfs_gpu_recover - manually trigger a gpu reset & recover
 *
 * Manually trigger a gpu reset at the next fence रुको.
 */
अटल पूर्णांक gpu_recover_get(व्योम *data, u64 *val)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)data;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	पूर्णांक r;

	r = pm_runसमय_get_sync(dev->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस 0;
	पूर्ण

	*val = amdgpu_device_gpu_recover(adev, शून्य);

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(amdgpu_debugfs_fence_info);
DEFINE_DEBUGFS_ATTRIBUTE(amdgpu_debugfs_gpu_recover_fops, gpu_recover_get, शून्य,
			 "%lld\n");

#पूर्ण_अगर

व्योम amdgpu_debugfs_fence_init(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *root = minor->debugfs_root;

	debugfs_create_file("amdgpu_fence_info", 0444, root, adev,
			    &amdgpu_debugfs_fence_info_fops);

	अगर (!amdgpu_sriov_vf(adev))
		debugfs_create_file("amdgpu_gpu_recover", 0444, root, adev,
				    &amdgpu_debugfs_gpu_recover_fops);
#पूर्ण_अगर
पूर्ण

