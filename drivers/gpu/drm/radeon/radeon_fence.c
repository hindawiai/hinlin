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

#समावेश <linux/atomic.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kref.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>

#समावेश "radeon.h"
#समावेश "radeon_reg.h"
#समावेश "radeon_trace.h"

/*
 * Fences
 * Fences mark an event in the GPUs pipeline and are used
 * क्रम GPU/CPU synchronization.  When the fence is written,
 * it is expected that all buffers associated with that fence
 * are no दीर्घer in use by the associated ring on the GPU and
 * that the the relevant GPU caches have been flushed.  Whether
 * we use a scratch रेजिस्टर or memory location depends on the asic
 * and whether ग_लिखोback is enabled.
 */

/**
 * radeon_fence_ग_लिखो - ग_लिखो a fence value
 *
 * @rdev: radeon_device poपूर्णांकer
 * @seq: sequence number to ग_लिखो
 * @ring: ring index the fence is associated with
 *
 * Writes a fence value to memory or a scratch रेजिस्टर (all asics).
 */
अटल व्योम radeon_fence_ग_लिखो(काष्ठा radeon_device *rdev, u32 seq, पूर्णांक ring)
अणु
	काष्ठा radeon_fence_driver *drv = &rdev->fence_drv[ring];
	अगर (likely(rdev->wb.enabled || !drv->scratch_reg)) अणु
		अगर (drv->cpu_addr) अणु
			*drv->cpu_addr = cpu_to_le32(seq);
		पूर्ण
	पूर्ण अन्यथा अणु
		WREG32(drv->scratch_reg, seq);
	पूर्ण
पूर्ण

/**
 * radeon_fence_पढ़ो - पढ़ो a fence value
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: ring index the fence is associated with
 *
 * Reads a fence value from memory or a scratch रेजिस्टर (all asics).
 * Returns the value of the fence पढ़ो from memory or रेजिस्टर.
 */
अटल u32 radeon_fence_पढ़ो(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	काष्ठा radeon_fence_driver *drv = &rdev->fence_drv[ring];
	u32 seq = 0;

	अगर (likely(rdev->wb.enabled || !drv->scratch_reg)) अणु
		अगर (drv->cpu_addr) अणु
			seq = le32_to_cpu(*drv->cpu_addr);
		पूर्ण अन्यथा अणु
			seq = lower_32_bits(atomic64_पढ़ो(&drv->last_seq));
		पूर्ण
	पूर्ण अन्यथा अणु
		seq = RREG32(drv->scratch_reg);
	पूर्ण
	वापस seq;
पूर्ण

/**
 * radeon_fence_schedule_check - schedule lockup check
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: ring index we should work with
 *
 * Queues a delayed work item to check क्रम lockups.
 */
अटल व्योम radeon_fence_schedule_check(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	/*
	 * Do not reset the समयr here with mod_delayed_work,
	 * this can livelock in an पूर्णांकeraction with TTM delayed destroy.
	 */
	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &rdev->fence_drv[ring].lockup_work,
			   RADEON_FENCE_JIFFIES_TIMEOUT);
पूर्ण

/**
 * radeon_fence_emit - emit a fence on the requested ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: radeon fence object
 * @ring: ring index the fence is associated with
 *
 * Emits a fence command on the requested ring (all asics).
 * Returns 0 on success, -ENOMEM on failure.
 */
पूर्णांक radeon_fence_emit(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_fence **fence,
		      पूर्णांक ring)
अणु
	u64 seq;

	/* we are रक्षित by the ring emission mutex */
	*fence = kदो_स्मृति(माप(काष्ठा radeon_fence), GFP_KERNEL);
	अगर ((*fence) == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
	(*fence)->rdev = rdev;
	(*fence)->seq = seq = ++rdev->fence_drv[ring].sync_seq[ring];
	(*fence)->ring = ring;
	(*fence)->is_vm_update = false;
	dma_fence_init(&(*fence)->base, &radeon_fence_ops,
		       &rdev->fence_queue.lock,
		       rdev->fence_context + ring,
		       seq);
	radeon_fence_ring_emit(rdev, ring, *fence);
	trace_radeon_fence_emit(rdev->ddev, ring, (*fence)->seq);
	radeon_fence_schedule_check(rdev, ring);
	वापस 0;
पूर्ण

/*
 * radeon_fence_check_संकेतed - callback from fence_queue
 *
 * this function is called with fence_queue lock held, which is also used
 * क्रम the fence locking itself, so unlocked variants are used क्रम
 * fence_संकेत, and हटाओ_रुको_queue.
 */
अटल पूर्णांक radeon_fence_check_संकेतed(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक flags, व्योम *key)
अणु
	काष्ठा radeon_fence *fence;
	u64 seq;

	fence = container_of(रुको, काष्ठा radeon_fence, fence_wake);

	/*
	 * We cannot use radeon_fence_process here because we're alपढ़ोy
	 * in the रुकोqueue, in a call from wake_up_all.
	 */
	seq = atomic64_पढ़ो(&fence->rdev->fence_drv[fence->ring].last_seq);
	अगर (seq >= fence->seq) अणु
		पूर्णांक ret = dma_fence_संकेत_locked(&fence->base);

		अगर (!ret)
			DMA_FENCE_TRACE(&fence->base, "signaled from irq context\n");
		अन्यथा
			DMA_FENCE_TRACE(&fence->base, "was already signaled\n");

		radeon_irq_kms_sw_irq_put(fence->rdev, fence->ring);
		__हटाओ_रुको_queue(&fence->rdev->fence_queue, &fence->fence_wake);
		dma_fence_put(&fence->base);
	पूर्ण अन्यथा
		DMA_FENCE_TRACE(&fence->base, "pending\n");
	वापस 0;
पूर्ण

/**
 * radeon_fence_activity - check क्रम fence activity
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: ring index the fence is associated with
 *
 * Checks the current fence value and calculates the last
 * संकेतled fence value. Returns true अगर activity occured
 * on the ring, and the fence_queue should be waken up.
 */
अटल bool radeon_fence_activity(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	uपूर्णांक64_t seq, last_seq, last_emitted;
	अचिन्हित count_loop = 0;
	bool wake = false;

	/* Note there is a scenario here क्रम an infinite loop but it's
	 * very unlikely to happen. For it to happen, the current polling
	 * process need to be पूर्णांकerrupted by another process and another
	 * process needs to update the last_seq btw the atomic पढ़ो and
	 * xchg of the current process.
	 *
	 * More over क्रम this to go in infinite loop there need to be
	 * continuously new fence संकेतed ie radeon_fence_पढ़ो needs
	 * to वापस a dअगरferent value each समय क्रम both the currently
	 * polling process and the other process that xchg the last_seq
	 * btw atomic पढ़ो and xchg of the current process. And the
	 * value the other process set as last seq must be higher than
	 * the seq value we just पढ़ो. Which means that current process
	 * need to be पूर्णांकerrupted after radeon_fence_पढ़ो and beक्रमe
	 * atomic xchg.
	 *
	 * To be even more safe we count the number of समय we loop and
	 * we bail after 10 loop just accepting the fact that we might
	 * have temporarly set the last_seq not to the true real last
	 * seq but to an older one.
	 */
	last_seq = atomic64_पढ़ो(&rdev->fence_drv[ring].last_seq);
	करो अणु
		last_emitted = rdev->fence_drv[ring].sync_seq[ring];
		seq = radeon_fence_पढ़ो(rdev, ring);
		seq |= last_seq & 0xffffffff00000000LL;
		अगर (seq < last_seq) अणु
			seq &= 0xffffffff;
			seq |= last_emitted & 0xffffffff00000000LL;
		पूर्ण

		अगर (seq <= last_seq || seq > last_emitted) अणु
			अवरोध;
		पूर्ण
		/* If we loop over we करोn't want to वापस without
		 * checking अगर a fence is संकेतed as it means that the
		 * seq we just पढ़ो is dअगरferent from the previous on.
		 */
		wake = true;
		last_seq = seq;
		अगर ((count_loop++) > 10) अणु
			/* We looped over too many समय leave with the
			 * fact that we might have set an older fence
			 * seq then the current real last seq as संकेतed
			 * by the hw.
			 */
			अवरोध;
		पूर्ण
	पूर्ण जबतक (atomic64_xchg(&rdev->fence_drv[ring].last_seq, seq) > seq);

	अगर (seq < last_emitted)
		radeon_fence_schedule_check(rdev, ring);

	वापस wake;
पूर्ण

/**
 * radeon_fence_check_lockup - check क्रम hardware lockup
 *
 * @work: delayed work item
 *
 * Checks क्रम fence activity and अगर there is none probe
 * the hardware अगर a lockup occured.
 */
अटल व्योम radeon_fence_check_lockup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा radeon_fence_driver *fence_drv;
	काष्ठा radeon_device *rdev;
	पूर्णांक ring;

	fence_drv = container_of(work, काष्ठा radeon_fence_driver,
				 lockup_work.work);
	rdev = fence_drv->rdev;
	ring = fence_drv - &rdev->fence_drv[0];

	अगर (!करोwn_पढ़ो_trylock(&rdev->exclusive_lock)) अणु
		/* just reschedule the check अगर a reset is going on */
		radeon_fence_schedule_check(rdev, ring);
		वापस;
	पूर्ण

	अगर (fence_drv->delayed_irq && rdev->ddev->irq_enabled) अणु
		अचिन्हित दीर्घ irqflags;

		fence_drv->delayed_irq = false;
		spin_lock_irqsave(&rdev->irq.lock, irqflags);
		radeon_irq_set(rdev);
		spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	पूर्ण

	अगर (radeon_fence_activity(rdev, ring))
		wake_up_all(&rdev->fence_queue);

	अन्यथा अगर (radeon_ring_is_lockup(rdev, ring, &rdev->ring[ring])) अणु

		/* good news we believe it's a lockup */
		dev_warn(rdev->dev, "GPU lockup (current fence id "
			 "0x%016llx last fence id 0x%016llx on ring %d)\n",
			 (uपूर्णांक64_t)atomic64_पढ़ो(&fence_drv->last_seq),
			 fence_drv->sync_seq[ring], ring);

		/* remember that we need an reset */
		rdev->needs_reset = true;
		wake_up_all(&rdev->fence_queue);
	पूर्ण
	up_पढ़ो(&rdev->exclusive_lock);
पूर्ण

/**
 * radeon_fence_process - process a fence
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: ring index the fence is associated with
 *
 * Checks the current fence value and wakes the fence queue
 * अगर the sequence number has increased (all asics).
 */
व्योम radeon_fence_process(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	अगर (radeon_fence_activity(rdev, ring))
		wake_up_all(&rdev->fence_queue);
पूर्ण

/**
 * radeon_fence_seq_संकेतed - check अगर a fence sequence number has संकेतed
 *
 * @rdev: radeon device poपूर्णांकer
 * @seq: sequence number
 * @ring: ring index the fence is associated with
 *
 * Check अगर the last संकेतed fence sequnce number is >= the requested
 * sequence number (all asics).
 * Returns true अगर the fence has संकेतed (current fence value
 * is >= requested value) or false अगर it has not (current fence
 * value is < the requested value.  Helper function क्रम
 * radeon_fence_संकेतed().
 */
अटल bool radeon_fence_seq_संकेतed(काष्ठा radeon_device *rdev,
				      u64 seq, अचिन्हित ring)
अणु
	अगर (atomic64_पढ़ो(&rdev->fence_drv[ring].last_seq) >= seq) अणु
		वापस true;
	पूर्ण
	/* poll new last sequence at least once */
	radeon_fence_process(rdev, ring);
	अगर (atomic64_पढ़ो(&rdev->fence_drv[ring].last_seq) >= seq) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool radeon_fence_is_संकेतed(काष्ठा dma_fence *f)
अणु
	काष्ठा radeon_fence *fence = to_radeon_fence(f);
	काष्ठा radeon_device *rdev = fence->rdev;
	अचिन्हित ring = fence->ring;
	u64 seq = fence->seq;

	अगर (atomic64_पढ़ो(&rdev->fence_drv[ring].last_seq) >= seq) अणु
		वापस true;
	पूर्ण

	अगर (करोwn_पढ़ो_trylock(&rdev->exclusive_lock)) अणु
		radeon_fence_process(rdev, ring);
		up_पढ़ो(&rdev->exclusive_lock);

		अगर (atomic64_पढ़ो(&rdev->fence_drv[ring].last_seq) >= seq) अणु
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/**
 * radeon_fence_enable_संकेतing - enable संकेतling on fence
 * @f: fence
 *
 * This function is called with fence_queue lock held, and adds a callback
 * to fence_queue that checks अगर this fence is संकेतed, and अगर so it
 * संकेतs the fence and हटाओs itself.
 */
अटल bool radeon_fence_enable_संकेतing(काष्ठा dma_fence *f)
अणु
	काष्ठा radeon_fence *fence = to_radeon_fence(f);
	काष्ठा radeon_device *rdev = fence->rdev;

	अगर (atomic64_पढ़ो(&rdev->fence_drv[fence->ring].last_seq) >= fence->seq)
		वापस false;

	अगर (करोwn_पढ़ो_trylock(&rdev->exclusive_lock)) अणु
		radeon_irq_kms_sw_irq_get(rdev, fence->ring);

		अगर (radeon_fence_activity(rdev, fence->ring))
			wake_up_all_locked(&rdev->fence_queue);

		/* did fence get संकेतed after we enabled the sw irq? */
		अगर (atomic64_पढ़ो(&rdev->fence_drv[fence->ring].last_seq) >= fence->seq) अणु
			radeon_irq_kms_sw_irq_put(rdev, fence->ring);
			up_पढ़ो(&rdev->exclusive_lock);
			वापस false;
		पूर्ण

		up_पढ़ो(&rdev->exclusive_lock);
	पूर्ण अन्यथा अणु
		/* we're probably in a lockup, lets not fiddle too much */
		अगर (radeon_irq_kms_sw_irq_get_delayed(rdev, fence->ring))
			rdev->fence_drv[fence->ring].delayed_irq = true;
		radeon_fence_schedule_check(rdev, fence->ring);
	पूर्ण

	fence->fence_wake.flags = 0;
	fence->fence_wake.निजी = शून्य;
	fence->fence_wake.func = radeon_fence_check_संकेतed;
	__add_रुको_queue(&rdev->fence_queue, &fence->fence_wake);
	dma_fence_get(f);

	DMA_FENCE_TRACE(&fence->base, "armed on ring %i!\n", fence->ring);
	वापस true;
पूर्ण

/**
 * radeon_fence_संकेतed - check अगर a fence has संकेतed
 *
 * @fence: radeon fence object
 *
 * Check अगर the requested fence has संकेतed (all asics).
 * Returns true अगर the fence has संकेतed or false अगर it has not.
 */
bool radeon_fence_संकेतed(काष्ठा radeon_fence *fence)
अणु
	अगर (!fence)
		वापस true;

	अगर (radeon_fence_seq_संकेतed(fence->rdev, fence->seq, fence->ring)) अणु
		पूर्णांक ret;

		ret = dma_fence_संकेत(&fence->base);
		अगर (!ret)
			DMA_FENCE_TRACE(&fence->base, "signaled from radeon_fence_signaled\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * radeon_fence_any_seq_संकेतed - check अगर any sequence number is संकेतed
 *
 * @rdev: radeon device poपूर्णांकer
 * @seq: sequence numbers
 *
 * Check अगर the last संकेतed fence sequnce number is >= the requested
 * sequence number (all asics).
 * Returns true अगर any has संकेतed (current value is >= requested value)
 * or false अगर it has not. Helper function क्रम radeon_fence_रुको_seq.
 */
अटल bool radeon_fence_any_seq_संकेतed(काष्ठा radeon_device *rdev, u64 *seq)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		अगर (seq[i] && radeon_fence_seq_संकेतed(rdev, seq[i], i))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * radeon_fence_रुको_seq_समयout - रुको क्रम a specअगरic sequence numbers
 *
 * @rdev: radeon device poपूर्णांकer
 * @target_seq: sequence number(s) we want to रुको क्रम
 * @पूर्णांकr: use पूर्णांकerruptable sleep
 * @समयout: maximum समय to रुको, or MAX_SCHEDULE_TIMEOUT क्रम infinite रुको
 *
 * Wait क्रम the requested sequence number(s) to be written by any ring
 * (all asics).  Sequnce number array is indexed by ring id.
 * @पूर्णांकr selects whether to use पूर्णांकerruptable (true) or non-पूर्णांकerruptable
 * (false) sleep when रुकोing क्रम the sequence number.  Helper function
 * क्रम radeon_fence_रुको_*().
 * Returns reमुख्यing समय अगर the sequence number has passed, 0 when
 * the रुको समयout, or an error क्रम all other हालs.
 * -EDEADLK is वापसed when a GPU lockup has been detected.
 */
अटल दीर्घ radeon_fence_रुको_seq_समयout(काष्ठा radeon_device *rdev,
					  u64 *target_seq, bool पूर्णांकr,
					  दीर्घ समयout)
अणु
	दीर्घ r;
	पूर्णांक i;

	अगर (radeon_fence_any_seq_संकेतed(rdev, target_seq))
		वापस समयout;

	/* enable IRQs and tracing */
	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		अगर (!target_seq[i])
			जारी;

		trace_radeon_fence_रुको_begin(rdev->ddev, i, target_seq[i]);
		radeon_irq_kms_sw_irq_get(rdev, i);
	पूर्ण

	अगर (पूर्णांकr) अणु
		r = रुको_event_पूर्णांकerruptible_समयout(rdev->fence_queue, (
			radeon_fence_any_seq_संकेतed(rdev, target_seq)
			 || rdev->needs_reset), समयout);
	पूर्ण अन्यथा अणु
		r = रुको_event_समयout(rdev->fence_queue, (
			radeon_fence_any_seq_संकेतed(rdev, target_seq)
			 || rdev->needs_reset), समयout);
	पूर्ण

	अगर (rdev->needs_reset)
		r = -EDEADLK;

	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		अगर (!target_seq[i])
			जारी;

		radeon_irq_kms_sw_irq_put(rdev, i);
		trace_radeon_fence_रुको_end(rdev->ddev, i, target_seq[i]);
	पूर्ण

	वापस r;
पूर्ण

/**
 * radeon_fence_रुको_समयout - रुको क्रम a fence to संकेत with समयout
 *
 * @fence: radeon fence object
 * @पूर्णांकr: use पूर्णांकerruptible sleep
 *
 * Wait क्रम the requested fence to संकेत (all asics).
 * @पूर्णांकr selects whether to use पूर्णांकerruptable (true) or non-पूर्णांकerruptable
 * (false) sleep when रुकोing क्रम the fence.
 * @समयout: maximum समय to रुको, or MAX_SCHEDULE_TIMEOUT क्रम infinite रुको
 * Returns reमुख्यing समय अगर the sequence number has passed, 0 when
 * the रुको समयout, or an error क्रम all other हालs.
 */
दीर्घ radeon_fence_रुको_समयout(काष्ठा radeon_fence *fence, bool पूर्णांकr, दीर्घ समयout)
अणु
	uपूर्णांक64_t seq[RADEON_NUM_RINGS] = अणुपूर्ण;
	दीर्घ r;
	पूर्णांक r_sig;

	/*
	 * This function should not be called on !radeon fences.
	 * If this is the हाल, it would mean this function can
	 * also be called on radeon fences beदीर्घing to another card.
	 * exclusive_lock is not held in that हाल.
	 */
	अगर (WARN_ON_ONCE(!to_radeon_fence(&fence->base)))
		वापस dma_fence_रुको(&fence->base, पूर्णांकr);

	seq[fence->ring] = fence->seq;
	r = radeon_fence_रुको_seq_समयout(fence->rdev, seq, पूर्णांकr, समयout);
	अगर (r <= 0) अणु
		वापस r;
	पूर्ण

	r_sig = dma_fence_संकेत(&fence->base);
	अगर (!r_sig)
		DMA_FENCE_TRACE(&fence->base, "signaled from fence_wait\n");
	वापस r;
पूर्ण

/**
 * radeon_fence_रुको - रुको क्रम a fence to संकेत
 *
 * @fence: radeon fence object
 * @पूर्णांकr: use पूर्णांकerruptible sleep
 *
 * Wait क्रम the requested fence to संकेत (all asics).
 * @पूर्णांकr selects whether to use पूर्णांकerruptable (true) or non-पूर्णांकerruptable
 * (false) sleep when रुकोing क्रम the fence.
 * Returns 0 अगर the fence has passed, error क्रम all other हालs.
 */
पूर्णांक radeon_fence_रुको(काष्ठा radeon_fence *fence, bool पूर्णांकr)
अणु
	दीर्घ r = radeon_fence_रुको_समयout(fence, पूर्णांकr, MAX_SCHEDULE_TIMEOUT);
	अगर (r > 0) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस r;
	पूर्ण
पूर्ण

/**
 * radeon_fence_रुको_any - रुको क्रम a fence to संकेत on any ring
 *
 * @rdev: radeon device poपूर्णांकer
 * @fences: radeon fence object(s)
 * @पूर्णांकr: use पूर्णांकerruptable sleep
 *
 * Wait क्रम any requested fence to संकेत (all asics).  Fence
 * array is indexed by ring id.  @पूर्णांकr selects whether to use
 * पूर्णांकerruptable (true) or non-पूर्णांकerruptable (false) sleep when
 * रुकोing क्रम the fences. Used by the suballocator.
 * Returns 0 अगर any fence has passed, error क्रम all other हालs.
 */
पूर्णांक radeon_fence_रुको_any(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_fence **fences,
			  bool पूर्णांकr)
अणु
	uपूर्णांक64_t seq[RADEON_NUM_RINGS];
	अचिन्हित i, num_rings = 0;
	दीर्घ r;

	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		seq[i] = 0;

		अगर (!fences[i]) अणु
			जारी;
		पूर्ण

		seq[i] = fences[i]->seq;
		++num_rings;
	पूर्ण

	/* nothing to रुको क्रम ? */
	अगर (num_rings == 0)
		वापस -ENOENT;

	r = radeon_fence_रुको_seq_समयout(rdev, seq, पूर्णांकr, MAX_SCHEDULE_TIMEOUT);
	अगर (r < 0) अणु
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * radeon_fence_रुको_next - रुको क्रम the next fence to संकेत
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: ring index the fence is associated with
 *
 * Wait क्रम the next fence on the requested ring to संकेत (all asics).
 * Returns 0 अगर the next fence has passed, error क्रम all other हालs.
 * Caller must hold ring lock.
 */
पूर्णांक radeon_fence_रुको_next(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	uपूर्णांक64_t seq[RADEON_NUM_RINGS] = अणुपूर्ण;
	दीर्घ r;

	seq[ring] = atomic64_पढ़ो(&rdev->fence_drv[ring].last_seq) + 1ULL;
	अगर (seq[ring] >= rdev->fence_drv[ring].sync_seq[ring]) अणु
		/* nothing to रुको क्रम, last_seq is
		   alपढ़ोy the last emited fence */
		वापस -ENOENT;
	पूर्ण
	r = radeon_fence_रुको_seq_समयout(rdev, seq, false, MAX_SCHEDULE_TIMEOUT);
	अगर (r < 0)
		वापस r;
	वापस 0;
पूर्ण

/**
 * radeon_fence_रुको_empty - रुको क्रम all fences to संकेत
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: ring index the fence is associated with
 *
 * Wait क्रम all fences on the requested ring to संकेत (all asics).
 * Returns 0 अगर the fences have passed, error क्रम all other हालs.
 * Caller must hold ring lock.
 */
पूर्णांक radeon_fence_रुको_empty(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	uपूर्णांक64_t seq[RADEON_NUM_RINGS] = अणुपूर्ण;
	दीर्घ r;

	seq[ring] = rdev->fence_drv[ring].sync_seq[ring];
	अगर (!seq[ring])
		वापस 0;

	r = radeon_fence_रुको_seq_समयout(rdev, seq, false, MAX_SCHEDULE_TIMEOUT);
	अगर (r < 0) अणु
		अगर (r == -EDEADLK)
			वापस -EDEADLK;

		dev_err(rdev->dev, "error waiting for ring[%d] to become idle (%ld)\n",
			ring, r);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * radeon_fence_ref - take a ref on a fence
 *
 * @fence: radeon fence object
 *
 * Take a reference on a fence (all asics).
 * Returns the fence.
 */
काष्ठा radeon_fence *radeon_fence_ref(काष्ठा radeon_fence *fence)
अणु
	dma_fence_get(&fence->base);
	वापस fence;
पूर्ण

/**
 * radeon_fence_unref - हटाओ a ref on a fence
 *
 * @fence: radeon fence object
 *
 * Remove a reference on a fence (all asics).
 */
व्योम radeon_fence_unref(काष्ठा radeon_fence **fence)
अणु
	काष्ठा radeon_fence *पंचांगp = *fence;

	*fence = शून्य;
	अगर (पंचांगp) अणु
		dma_fence_put(&पंचांगp->base);
	पूर्ण
पूर्ण

/**
 * radeon_fence_count_emitted - get the count of emitted fences
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: ring index the fence is associated with
 *
 * Get the number of fences emitted on the requested ring (all asics).
 * Returns the number of emitted fences on the ring.  Used by the
 * dynpm code to ring track activity.
 */
अचिन्हित radeon_fence_count_emitted(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	uपूर्णांक64_t emitted;

	/* We are not रक्षित by ring lock when पढ़ोing the last sequence
	 * but it's ok to report slightly wrong fence count here.
	 */
	radeon_fence_process(rdev, ring);
	emitted = rdev->fence_drv[ring].sync_seq[ring]
		- atomic64_पढ़ो(&rdev->fence_drv[ring].last_seq);
	/* to aव्योम 32bits warp around */
	अगर (emitted > 0x10000000) अणु
		emitted = 0x10000000;
	पूर्ण
	वापस (अचिन्हित)emitted;
पूर्ण

/**
 * radeon_fence_need_sync - करो we need a semaphore
 *
 * @fence: radeon fence object
 * @dst_ring: which ring to check against
 *
 * Check अगर the fence needs to be synced against another ring
 * (all asics).  If so, we need to emit a semaphore.
 * Returns true अगर we need to sync with another ring, false अगर
 * not.
 */
bool radeon_fence_need_sync(काष्ठा radeon_fence *fence, पूर्णांक dst_ring)
अणु
	काष्ठा radeon_fence_driver *fdrv;

	अगर (!fence) अणु
		वापस false;
	पूर्ण

	अगर (fence->ring == dst_ring) अणु
		वापस false;
	पूर्ण

	/* we are रक्षित by the ring mutex */
	fdrv = &fence->rdev->fence_drv[dst_ring];
	अगर (fence->seq <= fdrv->sync_seq[fence->ring]) अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * radeon_fence_note_sync - record the sync poपूर्णांक
 *
 * @fence: radeon fence object
 * @dst_ring: which ring to check against
 *
 * Note the sequence number at which poपूर्णांक the fence will
 * be synced with the requested ring (all asics).
 */
व्योम radeon_fence_note_sync(काष्ठा radeon_fence *fence, पूर्णांक dst_ring)
अणु
	काष्ठा radeon_fence_driver *dst, *src;
	अचिन्हित i;

	अगर (!fence) अणु
		वापस;
	पूर्ण

	अगर (fence->ring == dst_ring) अणु
		वापस;
	पूर्ण

	/* we are रक्षित by the ring mutex */
	src = &fence->rdev->fence_drv[fence->ring];
	dst = &fence->rdev->fence_drv[dst_ring];
	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		अगर (i == dst_ring) अणु
			जारी;
		पूर्ण
		dst->sync_seq[i] = max(dst->sync_seq[i], src->sync_seq[i]);
	पूर्ण
पूर्ण

/**
 * radeon_fence_driver_start_ring - make the fence driver
 * पढ़ोy क्रम use on the requested ring.
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: ring index to start the fence driver on
 *
 * Make the fence driver पढ़ोy क्रम processing (all asics).
 * Not all asics have all rings, so each asic will only
 * start the fence driver on the rings it has.
 * Returns 0 क्रम success, errors क्रम failure.
 */
पूर्णांक radeon_fence_driver_start_ring(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	uपूर्णांक64_t index;
	पूर्णांक r;

	radeon_scratch_मुक्त(rdev, rdev->fence_drv[ring].scratch_reg);
	अगर (rdev->wb.use_event || !radeon_ring_supports_scratch_reg(rdev, &rdev->ring[ring])) अणु
		rdev->fence_drv[ring].scratch_reg = 0;
		अगर (ring != R600_RING_TYPE_UVD_INDEX) अणु
			index = R600_WB_EVENT_OFFSET + ring * 4;
			rdev->fence_drv[ring].cpu_addr = &rdev->wb.wb[index/4];
			rdev->fence_drv[ring].gpu_addr = rdev->wb.gpu_addr +
							 index;

		पूर्ण अन्यथा अणु
			/* put fence directly behind firmware */
			index = ALIGN(rdev->uvd_fw->size, 8);
			rdev->fence_drv[ring].cpu_addr = rdev->uvd.cpu_addr + index;
			rdev->fence_drv[ring].gpu_addr = rdev->uvd.gpu_addr + index;
		पूर्ण

	पूर्ण अन्यथा अणु
		r = radeon_scratch_get(rdev, &rdev->fence_drv[ring].scratch_reg);
		अगर (r) अणु
			dev_err(rdev->dev, "fence failed to get scratch register\n");
			वापस r;
		पूर्ण
		index = RADEON_WB_SCRATCH_OFFSET +
			rdev->fence_drv[ring].scratch_reg -
			rdev->scratch.reg_base;
		rdev->fence_drv[ring].cpu_addr = &rdev->wb.wb[index/4];
		rdev->fence_drv[ring].gpu_addr = rdev->wb.gpu_addr + index;
	पूर्ण
	radeon_fence_ग_लिखो(rdev, atomic64_पढ़ो(&rdev->fence_drv[ring].last_seq), ring);
	rdev->fence_drv[ring].initialized = true;
	dev_info(rdev->dev, "fence driver on ring %d use gpu addr 0x%016llx\n",
		 ring, rdev->fence_drv[ring].gpu_addr);
	वापस 0;
पूर्ण

/**
 * radeon_fence_driver_init_ring - init the fence driver
 * क्रम the requested ring.
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: ring index to start the fence driver on
 *
 * Init the fence driver क्रम the requested ring (all asics).
 * Helper function क्रम radeon_fence_driver_init().
 */
अटल व्योम radeon_fence_driver_init_ring(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	पूर्णांक i;

	rdev->fence_drv[ring].scratch_reg = -1;
	rdev->fence_drv[ring].cpu_addr = शून्य;
	rdev->fence_drv[ring].gpu_addr = 0;
	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i)
		rdev->fence_drv[ring].sync_seq[i] = 0;
	atomic64_set(&rdev->fence_drv[ring].last_seq, 0);
	rdev->fence_drv[ring].initialized = false;
	INIT_DELAYED_WORK(&rdev->fence_drv[ring].lockup_work,
			  radeon_fence_check_lockup);
	rdev->fence_drv[ring].rdev = rdev;
पूर्ण

/**
 * radeon_fence_driver_init - init the fence driver
 * क्रम all possible rings.
 *
 * @rdev: radeon device poपूर्णांकer
 *
 * Init the fence driver क्रम all possible rings (all asics).
 * Not all asics have all rings, so each asic will only
 * start the fence driver on the rings it has using
 * radeon_fence_driver_start_ring().
 * Returns 0 क्रम success.
 */
पूर्णांक radeon_fence_driver_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ring;

	init_रुकोqueue_head(&rdev->fence_queue);
	क्रम (ring = 0; ring < RADEON_NUM_RINGS; ring++) अणु
		radeon_fence_driver_init_ring(rdev, ring);
	पूर्ण

	radeon_debugfs_fence_init(rdev);

	वापस 0;
पूर्ण

/**
 * radeon_fence_driver_fini - tear करोwn the fence driver
 * क्रम all possible rings.
 *
 * @rdev: radeon device poपूर्णांकer
 *
 * Tear करोwn the fence driver क्रम all possible rings (all asics).
 */
व्योम radeon_fence_driver_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ring, r;

	mutex_lock(&rdev->ring_lock);
	क्रम (ring = 0; ring < RADEON_NUM_RINGS; ring++) अणु
		अगर (!rdev->fence_drv[ring].initialized)
			जारी;
		r = radeon_fence_रुको_empty(rdev, ring);
		अगर (r) अणु
			/* no need to trigger GPU reset as we are unloading */
			radeon_fence_driver_क्रमce_completion(rdev, ring);
		पूर्ण
		cancel_delayed_work_sync(&rdev->fence_drv[ring].lockup_work);
		wake_up_all(&rdev->fence_queue);
		radeon_scratch_मुक्त(rdev, rdev->fence_drv[ring].scratch_reg);
		rdev->fence_drv[ring].initialized = false;
	पूर्ण
	mutex_unlock(&rdev->ring_lock);
पूर्ण

/**
 * radeon_fence_driver_क्रमce_completion - क्रमce all fence रुकोer to complete
 *
 * @rdev: radeon device poपूर्णांकer
 * @ring: the ring to complete
 *
 * In हाल of GPU reset failure make sure no process keep रुकोing on fence
 * that will never complete.
 */
व्योम radeon_fence_driver_क्रमce_completion(काष्ठा radeon_device *rdev, पूर्णांक ring)
अणु
	अगर (rdev->fence_drv[ring].initialized) अणु
		radeon_fence_ग_लिखो(rdev, rdev->fence_drv[ring].sync_seq[ring], ring);
		cancel_delayed_work_sync(&rdev->fence_drv[ring].lockup_work);
	पूर्ण
पूर्ण


/*
 * Fence debugfs
 */
#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक radeon_debugfs_fence_info_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	पूर्णांक i, j;

	क्रम (i = 0; i < RADEON_NUM_RINGS; ++i) अणु
		अगर (!rdev->fence_drv[i].initialized)
			जारी;

		radeon_fence_process(rdev, i);

		seq_म_लिखो(m, "--- ring %d ---\n", i);
		seq_म_लिखो(m, "Last signaled fence 0x%016llx\n",
			   (अचिन्हित दीर्घ दीर्घ)atomic64_पढ़ो(&rdev->fence_drv[i].last_seq));
		seq_म_लिखो(m, "Last emitted        0x%016llx\n",
			   rdev->fence_drv[i].sync_seq[i]);

		क्रम (j = 0; j < RADEON_NUM_RINGS; ++j) अणु
			अगर (i != j && rdev->fence_drv[j].initialized)
				seq_म_लिखो(m, "Last sync to ring %d 0x%016llx\n",
					   j, rdev->fence_drv[i].sync_seq[j]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * radeon_debugfs_gpu_reset - manually trigger a gpu reset
 *
 * Manually trigger a gpu reset at the next fence रुको.
 */
अटल पूर्णांक radeon_debugfs_gpu_reset(व्योम *data, u64 *val)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)data;

	करोwn_पढ़ो(&rdev->exclusive_lock);
	*val = rdev->needs_reset;
	rdev->needs_reset = true;
	wake_up_all(&rdev->fence_queue);
	up_पढ़ो(&rdev->exclusive_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(radeon_debugfs_fence_info);
DEFINE_DEBUGFS_ATTRIBUTE(radeon_debugfs_gpu_reset_fops,
			 radeon_debugfs_gpu_reset, शून्य, "%lld\n");
#पूर्ण_अगर

व्योम radeon_debugfs_fence_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("radeon_gpu_reset", 0444, root, rdev,
			    &radeon_debugfs_gpu_reset_fops);
	debugfs_create_file("radeon_fence_info", 0444, root, rdev,
			    &radeon_debugfs_fence_info_fops);


#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर *radeon_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "radeon";
पूर्ण

अटल स्थिर अक्षर *radeon_fence_get_समयline_name(काष्ठा dma_fence *f)
अणु
	काष्ठा radeon_fence *fence = to_radeon_fence(f);
	चयन (fence->ring) अणु
	हाल RADEON_RING_TYPE_GFX_INDEX: वापस "radeon.gfx";
	हाल CAYMAN_RING_TYPE_CP1_INDEX: वापस "radeon.cp1";
	हाल CAYMAN_RING_TYPE_CP2_INDEX: वापस "radeon.cp2";
	हाल R600_RING_TYPE_DMA_INDEX: वापस "radeon.dma";
	हाल CAYMAN_RING_TYPE_DMA1_INDEX: वापस "radeon.dma1";
	हाल R600_RING_TYPE_UVD_INDEX: वापस "radeon.uvd";
	हाल TN_RING_TYPE_VCE1_INDEX: वापस "radeon.vce1";
	हाल TN_RING_TYPE_VCE2_INDEX: वापस "radeon.vce2";
	शेष: WARN_ON_ONCE(1); वापस "radeon.unk";
	पूर्ण
पूर्ण

अटल अंतरभूत bool radeon_test_संकेतed(काष्ठा radeon_fence *fence)
अणु
	वापस test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->base.flags);
पूर्ण

काष्ठा radeon_रुको_cb अणु
	काष्ठा dma_fence_cb base;
	काष्ठा task_काष्ठा *task;
पूर्ण;

अटल व्योम
radeon_fence_रुको_cb(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा radeon_रुको_cb *रुको =
		container_of(cb, काष्ठा radeon_रुको_cb, base);

	wake_up_process(रुको->task);
पूर्ण

अटल चिन्हित दीर्घ radeon_fence_शेष_रुको(काष्ठा dma_fence *f, bool पूर्णांकr,
					     चिन्हित दीर्घ t)
अणु
	काष्ठा radeon_fence *fence = to_radeon_fence(f);
	काष्ठा radeon_device *rdev = fence->rdev;
	काष्ठा radeon_रुको_cb cb;

	cb.task = current;

	अगर (dma_fence_add_callback(f, &cb.base, radeon_fence_रुको_cb))
		वापस t;

	जबतक (t > 0) अणु
		अगर (पूर्णांकr)
			set_current_state(TASK_INTERRUPTIBLE);
		अन्यथा
			set_current_state(TASK_UNINTERRUPTIBLE);

		/*
		 * radeon_test_संकेतed must be called after
		 * set_current_state to prevent a race with wake_up_process
		 */
		अगर (radeon_test_संकेतed(fence))
			अवरोध;

		अगर (rdev->needs_reset) अणु
			t = -EDEADLK;
			अवरोध;
		पूर्ण

		t = schedule_समयout(t);

		अगर (t > 0 && पूर्णांकr && संकेत_pending(current))
			t = -ERESTARTSYS;
	पूर्ण

	__set_current_state(TASK_RUNNING);
	dma_fence_हटाओ_callback(f, &cb.base);

	वापस t;
पूर्ण

स्थिर काष्ठा dma_fence_ops radeon_fence_ops = अणु
	.get_driver_name = radeon_fence_get_driver_name,
	.get_समयline_name = radeon_fence_get_समयline_name,
	.enable_संकेतing = radeon_fence_enable_संकेतing,
	.संकेतed = radeon_fence_is_संकेतed,
	.रुको = radeon_fence_शेष_रुको,
	.release = शून्य,
पूर्ण;
