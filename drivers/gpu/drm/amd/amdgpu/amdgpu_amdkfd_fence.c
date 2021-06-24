<शैली गुरु>
/*
 * Copyright 2016-2018 Advanced Micro Devices, Inc.
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
 */

#समावेश <linux/dma-fence.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/mm.h>
#समावेश "amdgpu_amdkfd.h"

अटल स्थिर काष्ठा dma_fence_ops amdkfd_fence_ops;
अटल atomic_t fence_seq = ATOMIC_INIT(0);

/* Eviction Fence
 * Fence helper functions to deal with KFD memory eviction.
 * Big Idea - Since KFD submissions are करोne by user queues, a BO cannot be
 *  evicted unless all the user queues क्रम that process are evicted.
 *
 * All the BOs in a process share an eviction fence. When process X wants
 * to map VRAM memory but TTM can't find enough space, TTM will attempt to
 * evict BOs from its LRU list. TTM checks अगर the BO is valuable to evict
 * by calling tपंचांग_device_funcs->eviction_valuable().
 *
 * tपंचांग_device_funcs->eviction_valuable() - will वापस false अगर the BO beदीर्घs
 *  to process X. Otherwise, it will वापस true to indicate BO can be
 *  evicted by TTM.
 *
 * If tपंचांग_device_funcs->eviction_valuable वापसs true, then TTM will जारी
 * the evcition process क्रम that BO by calling tपंचांग_bo_evict --> amdgpu_bo_move
 * --> amdgpu_copy_buffer(). This sets up job in GPU scheduler.
 *
 * GPU Scheduler (amd_sched_मुख्य) - sets up a cb (fence_add_callback) to
 *  nofity when the BO is मुक्त to move. fence_add_callback --> enable_संकेतing
 *  --> amdgpu_amdkfd_fence.enable_संकेतing
 *
 * amdgpu_amdkfd_fence.enable_संकेतing - Start a work item that will quiesce
 * user queues and संकेत fence. The work item will also start another delayed
 * work item to restore BOs
 */

काष्ठा amdgpu_amdkfd_fence *amdgpu_amdkfd_fence_create(u64 context,
						       काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा amdgpu_amdkfd_fence *fence;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (fence == शून्य)
		वापस शून्य;

	/* This reference माला_लो released in amdkfd_fence_release */
	mmgrab(mm);
	fence->mm = mm;
	get_task_comm(fence->समयline_name, current);
	spin_lock_init(&fence->lock);

	dma_fence_init(&fence->base, &amdkfd_fence_ops, &fence->lock,
		   context, atomic_inc_वापस(&fence_seq));

	वापस fence;
पूर्ण

काष्ठा amdgpu_amdkfd_fence *to_amdgpu_amdkfd_fence(काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_amdkfd_fence *fence;

	अगर (!f)
		वापस शून्य;

	fence = container_of(f, काष्ठा amdgpu_amdkfd_fence, base);
	अगर (fence && f->ops == &amdkfd_fence_ops)
		वापस fence;

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *amdkfd_fence_get_driver_name(काष्ठा dma_fence *f)
अणु
	वापस "amdgpu_amdkfd_fence";
पूर्ण

अटल स्थिर अक्षर *amdkfd_fence_get_समयline_name(काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	वापस fence->समयline_name;
पूर्ण

/**
 * amdkfd_fence_enable_संकेतing - This माला_लो called when TTM wants to evict
 *  a KFD BO and schedules a job to move the BO.
 *  If fence is alपढ़ोy संकेतed वापस true.
 *  If fence is not संकेतed schedule a evict KFD process work item.
 */
अटल bool amdkfd_fence_enable_संकेतing(काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	अगर (!fence)
		वापस false;

	अगर (dma_fence_is_संकेतed(f))
		वापस true;

	अगर (!kgd2kfd_schedule_evict_and_restore_process(fence->mm, f))
		वापस true;

	वापस false;
पूर्ण

/**
 * amdkfd_fence_release - callback that fence can be मुक्तd
 *
 * @fence: fence
 *
 * This function is called when the reference count becomes zero.
 * Drops the mm_काष्ठा reference and RCU schedules मुक्तing up the fence.
 */
अटल व्योम amdkfd_fence_release(काष्ठा dma_fence *f)
अणु
	काष्ठा amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	/* Unconditionally संकेत the fence. The process is getting
	 * terminated.
	 */
	अगर (WARN_ON(!fence))
		वापस; /* Not an amdgpu_amdkfd_fence */

	mmdrop(fence->mm);
	kमुक्त_rcu(f, rcu);
पूर्ण

/**
 * amdkfd_fence_check_mm - Check अगर @mm is same as that of the fence @f
 *  अगर same वापस TRUE अन्यथा वापस FALSE.
 *
 * @f: [IN] fence
 * @mm: [IN] mm that needs to be verअगरied
 */
bool amdkfd_fence_check_mm(काष्ठा dma_fence *f, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा amdgpu_amdkfd_fence *fence = to_amdgpu_amdkfd_fence(f);

	अगर (!fence)
		वापस false;
	अन्यथा अगर (fence->mm == mm)
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops amdkfd_fence_ops = अणु
	.get_driver_name = amdkfd_fence_get_driver_name,
	.get_समयline_name = amdkfd_fence_get_समयline_name,
	.enable_संकेतing = amdkfd_fence_enable_संकेतing,
	.release = amdkfd_fence_release,
पूर्ण;
