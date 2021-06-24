<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

#समावेश <drm/gpu_scheduler.h>

अटल काष्ठा kmem_cache *sched_fence_slab;

अटल पूर्णांक __init drm_sched_fence_slab_init(व्योम)
अणु
	sched_fence_slab = kmem_cache_create(
		"drm_sched_fence", माप(काष्ठा drm_sched_fence), 0,
		SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!sched_fence_slab)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __निकास drm_sched_fence_slab_fini(व्योम)
अणु
	rcu_barrier();
	kmem_cache_destroy(sched_fence_slab);
पूर्ण

व्योम drm_sched_fence_scheduled(काष्ठा drm_sched_fence *fence)
अणु
	पूर्णांक ret = dma_fence_संकेत(&fence->scheduled);

	अगर (!ret)
		DMA_FENCE_TRACE(&fence->scheduled,
				"signaled from irq context\n");
	अन्यथा
		DMA_FENCE_TRACE(&fence->scheduled,
				"was already signaled\n");
पूर्ण

व्योम drm_sched_fence_finished(काष्ठा drm_sched_fence *fence)
अणु
	पूर्णांक ret = dma_fence_संकेत(&fence->finished);

	अगर (!ret)
		DMA_FENCE_TRACE(&fence->finished,
				"signaled from irq context\n");
	अन्यथा
		DMA_FENCE_TRACE(&fence->finished,
				"was already signaled\n");
पूर्ण

अटल स्थिर अक्षर *drm_sched_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "drm_sched";
पूर्ण

अटल स्थिर अक्षर *drm_sched_fence_get_समयline_name(काष्ठा dma_fence *f)
अणु
	काष्ठा drm_sched_fence *fence = to_drm_sched_fence(f);
	वापस (स्थिर अक्षर *)fence->sched->name;
पूर्ण

/**
 * drm_sched_fence_मुक्त - मुक्त up the fence memory
 *
 * @rcu: RCU callback head
 *
 * Free up the fence memory after the RCU grace period.
 */
अटल व्योम drm_sched_fence_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा dma_fence *f = container_of(rcu, काष्ठा dma_fence, rcu);
	काष्ठा drm_sched_fence *fence = to_drm_sched_fence(f);

	kmem_cache_मुक्त(sched_fence_slab, fence);
पूर्ण

/**
 * drm_sched_fence_release_scheduled - callback that fence can be मुक्तd
 *
 * @f: fence
 *
 * This function is called when the reference count becomes zero.
 * It just RCU schedules मुक्तing up the fence.
 */
अटल व्योम drm_sched_fence_release_scheduled(काष्ठा dma_fence *f)
अणु
	काष्ठा drm_sched_fence *fence = to_drm_sched_fence(f);

	dma_fence_put(fence->parent);
	call_rcu(&fence->finished.rcu, drm_sched_fence_मुक्त);
पूर्ण

/**
 * drm_sched_fence_release_finished - drop extra reference
 *
 * @f: fence
 *
 * Drop the extra reference from the scheduled fence to the base fence.
 */
अटल व्योम drm_sched_fence_release_finished(काष्ठा dma_fence *f)
अणु
	काष्ठा drm_sched_fence *fence = to_drm_sched_fence(f);

	dma_fence_put(&fence->scheduled);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops drm_sched_fence_ops_scheduled = अणु
	.get_driver_name = drm_sched_fence_get_driver_name,
	.get_समयline_name = drm_sched_fence_get_समयline_name,
	.release = drm_sched_fence_release_scheduled,
पूर्ण;

अटल स्थिर काष्ठा dma_fence_ops drm_sched_fence_ops_finished = अणु
	.get_driver_name = drm_sched_fence_get_driver_name,
	.get_समयline_name = drm_sched_fence_get_समयline_name,
	.release = drm_sched_fence_release_finished,
पूर्ण;

काष्ठा drm_sched_fence *to_drm_sched_fence(काष्ठा dma_fence *f)
अणु
	अगर (f->ops == &drm_sched_fence_ops_scheduled)
		वापस container_of(f, काष्ठा drm_sched_fence, scheduled);

	अगर (f->ops == &drm_sched_fence_ops_finished)
		वापस container_of(f, काष्ठा drm_sched_fence, finished);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(to_drm_sched_fence);

काष्ठा drm_sched_fence *drm_sched_fence_create(काष्ठा drm_sched_entity *entity,
					       व्योम *owner)
अणु
	काष्ठा drm_sched_fence *fence = शून्य;
	अचिन्हित seq;

	fence = kmem_cache_zalloc(sched_fence_slab, GFP_KERNEL);
	अगर (fence == शून्य)
		वापस शून्य;

	fence->owner = owner;
	fence->sched = entity->rq->sched;
	spin_lock_init(&fence->lock);

	seq = atomic_inc_वापस(&entity->fence_seq);
	dma_fence_init(&fence->scheduled, &drm_sched_fence_ops_scheduled,
		       &fence->lock, entity->fence_context, seq);
	dma_fence_init(&fence->finished, &drm_sched_fence_ops_finished,
		       &fence->lock, entity->fence_context + 1, seq);

	वापस fence;
पूर्ण

module_init(drm_sched_fence_slab_init);
module_निकास(drm_sched_fence_slab_fini);

MODULE_DESCRIPTION("DRM GPU scheduler");
MODULE_LICENSE("GPL and additional rights");
