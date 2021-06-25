<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 The Linux Foundation. All rights reserved.
 */

#समावेश "msm_gem.h"
#समावेश "a5xx_gpu.h"

/*
 * Try to transition the preemption state from old to new. Return
 * true on success or false अगर the original state wasn't 'old'
 */
अटल अंतरभूत bool try_preempt_state(काष्ठा a5xx_gpu *a5xx_gpu,
		क्रमागत preempt_state old, क्रमागत preempt_state new)
अणु
	क्रमागत preempt_state cur = atomic_cmpxchg(&a5xx_gpu->preempt_state,
		old, new);

	वापस (cur == old);
पूर्ण

/*
 * Force the preemption state to the specअगरied state.  This is used in हालs
 * where the current state is known and won't change
 */
अटल अंतरभूत व्योम set_preempt_state(काष्ठा a5xx_gpu *gpu,
		क्रमागत preempt_state new)
अणु
	/*
	 * preempt_state may be पढ़ो by other cores trying to trigger a
	 * preemption or in the पूर्णांकerrupt handler so barriers are needed
	 * beक्रमe...
	 */
	smp_mb__beक्रमe_atomic();
	atomic_set(&gpu->preempt_state, new);
	/* ... and after*/
	smp_mb__after_atomic();
पूर्ण

/* Write the most recent wptr क्रम the given ring पूर्णांकo the hardware */
अटल अंतरभूत व्योम update_wptr(काष्ठा msm_gpu *gpu, काष्ठा msm_ringbuffer *ring)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t wptr;

	अगर (!ring)
		वापस;

	spin_lock_irqsave(&ring->preempt_lock, flags);
	wptr = get_wptr(ring);
	spin_unlock_irqrestore(&ring->preempt_lock, flags);

	gpu_ग_लिखो(gpu, REG_A5XX_CP_RB_WPTR, wptr);
पूर्ण

/* Return the highest priority ringbuffer with something in it */
अटल काष्ठा msm_ringbuffer *get_next_ring(काष्ठा msm_gpu *gpu)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		bool empty;
		काष्ठा msm_ringbuffer *ring = gpu->rb[i];

		spin_lock_irqsave(&ring->preempt_lock, flags);
		empty = (get_wptr(ring) == ring->memptrs->rptr);
		spin_unlock_irqrestore(&ring->preempt_lock, flags);

		अगर (!empty)
			वापस ring;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम a5xx_preempt_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा a5xx_gpu *a5xx_gpu = from_समयr(a5xx_gpu, t, preempt_समयr);
	काष्ठा msm_gpu *gpu = &a5xx_gpu->base.base;
	काष्ठा drm_device *dev = gpu->dev;

	अगर (!try_preempt_state(a5xx_gpu, PREEMPT_TRIGGERED, PREEMPT_FAULTED))
		वापस;

	DRM_DEV_ERROR(dev->dev, "%s: preemption timed out\n", gpu->name);
	kthपढ़ो_queue_work(gpu->worker, &gpu->recover_work);
पूर्ण

/* Try to trigger a preemption चयन */
व्योम a5xx_preempt_trigger(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	अचिन्हित दीर्घ flags;
	काष्ठा msm_ringbuffer *ring;

	अगर (gpu->nr_rings == 1)
		वापस;

	/*
	 * Try to start preemption by moving from NONE to START. If
	 * unsuccessful, a preemption is alपढ़ोy in flight
	 */
	अगर (!try_preempt_state(a5xx_gpu, PREEMPT_NONE, PREEMPT_START))
		वापस;

	/* Get the next ring to preempt to */
	ring = get_next_ring(gpu);

	/*
	 * If no ring is populated or the highest priority ring is the current
	 * one करो nothing except to update the wptr to the latest and greatest
	 */
	अगर (!ring || (a5xx_gpu->cur_ring == ring)) अणु
		/*
		 * Its possible that जबतक a preemption request is in progress
		 * from an irq context, a user context trying to submit might
		 * fail to update the ग_लिखो poपूर्णांकer, because it determines
		 * that the preempt state is not PREEMPT_NONE.
		 *
		 * Close the race by पूर्णांकroducing an पूर्णांकermediate
		 * state PREEMPT_ABORT to let the submit path
		 * know that the ringbuffer is not going to change
		 * and can safely update the ग_लिखो poपूर्णांकer.
		 */

		set_preempt_state(a5xx_gpu, PREEMPT_ABORT);
		update_wptr(gpu, a5xx_gpu->cur_ring);
		set_preempt_state(a5xx_gpu, PREEMPT_NONE);
		वापस;
	पूर्ण

	/* Make sure the wptr करोesn't update while we're in motion */
	spin_lock_irqsave(&ring->preempt_lock, flags);
	a5xx_gpu->preempt[ring->id]->wptr = get_wptr(ring);
	spin_unlock_irqrestore(&ring->preempt_lock, flags);

	/* Set the address of the incoming preemption record */
	gpu_ग_लिखो64(gpu, REG_A5XX_CP_CONTEXT_SWITCH_RESTORE_ADDR_LO,
		REG_A5XX_CP_CONTEXT_SWITCH_RESTORE_ADDR_HI,
		a5xx_gpu->preempt_iova[ring->id]);

	a5xx_gpu->next_ring = ring;

	/* Start a समयr to catch a stuck preemption */
	mod_समयr(&a5xx_gpu->preempt_समयr, jअगरfies + msecs_to_jअगरfies(10000));

	/* Set the preemption state to triggered */
	set_preempt_state(a5xx_gpu, PREEMPT_TRIGGERED);

	/* Make sure everything is written beक्रमe hitting the button */
	wmb();

	/* And actually start the preemption */
	gpu_ग_लिखो(gpu, REG_A5XX_CP_CONTEXT_SWITCH_CNTL, 1);
पूर्ण

व्योम a5xx_preempt_irq(काष्ठा msm_gpu *gpu)
अणु
	uपूर्णांक32_t status;
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	काष्ठा drm_device *dev = gpu->dev;

	अगर (!try_preempt_state(a5xx_gpu, PREEMPT_TRIGGERED, PREEMPT_PENDING))
		वापस;

	/* Delete the preemption watchकरोg समयr */
	del_समयr(&a5xx_gpu->preempt_समयr);

	/*
	 * The hardware should be setting CP_CONTEXT_SWITCH_CNTL to zero beक्रमe
	 * firing the पूर्णांकerrupt, but there is a non zero chance of a hardware
	 * condition or a software race that could set it again beक्रमe we have a
	 * chance to finish. If that happens, log and go क्रम recovery
	 */
	status = gpu_पढ़ो(gpu, REG_A5XX_CP_CONTEXT_SWITCH_CNTL);
	अगर (unlikely(status)) अणु
		set_preempt_state(a5xx_gpu, PREEMPT_FAULTED);
		DRM_DEV_ERROR(dev->dev, "%s: Preemption failed to complete\n",
			gpu->name);
		kthपढ़ो_queue_work(gpu->worker, &gpu->recover_work);
		वापस;
	पूर्ण

	a5xx_gpu->cur_ring = a5xx_gpu->next_ring;
	a5xx_gpu->next_ring = शून्य;

	update_wptr(gpu, a5xx_gpu->cur_ring);

	set_preempt_state(a5xx_gpu, PREEMPT_NONE);
पूर्ण

व्योम a5xx_preempt_hw_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	पूर्णांक i;

	/* Always come up on rb 0 */
	a5xx_gpu->cur_ring = gpu->rb[0];

	/* No preemption अगर we only have one ring */
	अगर (gpu->nr_rings == 1)
		वापस;

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		a5xx_gpu->preempt[i]->wptr = 0;
		a5xx_gpu->preempt[i]->rptr = 0;
		a5xx_gpu->preempt[i]->rbase = gpu->rb[i]->iova;
	पूर्ण

	/* Write a 0 to संकेत that we aren't चयनing pagetables */
	gpu_ग_लिखो64(gpu, REG_A5XX_CP_CONTEXT_SWITCH_SMMU_INFO_LO,
		REG_A5XX_CP_CONTEXT_SWITCH_SMMU_INFO_HI, 0);

	/* Reset the preemption state */
	set_preempt_state(a5xx_gpu, PREEMPT_NONE);
पूर्ण

अटल पूर्णांक preempt_init_ring(काष्ठा a5xx_gpu *a5xx_gpu,
		काष्ठा msm_ringbuffer *ring)
अणु
	काष्ठा adreno_gpu *adreno_gpu = &a5xx_gpu->base;
	काष्ठा msm_gpu *gpu = &adreno_gpu->base;
	काष्ठा a5xx_preempt_record *ptr;
	व्योम *counters;
	काष्ठा drm_gem_object *bo = शून्य, *counters_bo = शून्य;
	u64 iova = 0, counters_iova = 0;

	ptr = msm_gem_kernel_new(gpu->dev,
		A5XX_PREEMPT_RECORD_SIZE + A5XX_PREEMPT_COUNTER_SIZE,
		MSM_BO_UNCACHED | MSM_BO_MAP_PRIV, gpu->aspace, &bo, &iova);

	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);

	/* The buffer to store counters needs to be unprivileged */
	counters = msm_gem_kernel_new(gpu->dev,
		A5XX_PREEMPT_COUNTER_SIZE,
		MSM_BO_UNCACHED, gpu->aspace, &counters_bo, &counters_iova);
	अगर (IS_ERR(counters)) अणु
		msm_gem_kernel_put(bo, gpu->aspace, true);
		वापस PTR_ERR(counters);
	पूर्ण

	msm_gem_object_set_name(bo, "preempt");
	msm_gem_object_set_name(counters_bo, "preempt_counters");

	a5xx_gpu->preempt_bo[ring->id] = bo;
	a5xx_gpu->preempt_counters_bo[ring->id] = counters_bo;
	a5xx_gpu->preempt_iova[ring->id] = iova;
	a5xx_gpu->preempt[ring->id] = ptr;

	/* Set up the शेषs on the preemption record */

	ptr->magic = A5XX_PREEMPT_RECORD_MAGIC;
	ptr->info = 0;
	ptr->data = 0;
	ptr->cntl = MSM_GPU_RB_CNTL_DEFAULT | AXXX_CP_RB_CNTL_NO_UPDATE;

	ptr->rptr_addr = shaकरोwptr(a5xx_gpu, ring);
	ptr->counter = counters_iova;

	वापस 0;
पूर्ण

व्योम a5xx_preempt_fini(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	पूर्णांक i;

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		msm_gem_kernel_put(a5xx_gpu->preempt_bo[i], gpu->aspace, true);
		msm_gem_kernel_put(a5xx_gpu->preempt_counters_bo[i],
			gpu->aspace, true);
	पूर्ण
पूर्ण

व्योम a5xx_preempt_init(काष्ठा msm_gpu *gpu)
अणु
	काष्ठा adreno_gpu *adreno_gpu = to_adreno_gpu(gpu);
	काष्ठा a5xx_gpu *a5xx_gpu = to_a5xx_gpu(adreno_gpu);
	पूर्णांक i;

	/* No preemption अगर we only have one ring */
	अगर (gpu->nr_rings <= 1)
		वापस;

	क्रम (i = 0; i < gpu->nr_rings; i++) अणु
		अगर (preempt_init_ring(a5xx_gpu, gpu->rb[i])) अणु
			/*
			 * On any failure our adventure is over. Clean up and
			 * set nr_rings to 1 to क्रमce preemption off
			 */
			a5xx_preempt_fini(gpu);
			gpu->nr_rings = 1;

			वापस;
		पूर्ण
	पूर्ण

	समयr_setup(&a5xx_gpu->preempt_समयr, a5xx_preempt_समयr, 0);
पूर्ण
