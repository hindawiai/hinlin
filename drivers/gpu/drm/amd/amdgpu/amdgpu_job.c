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
 *
 */
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"

अटल क्रमागत drm_gpu_sched_stat amdgpu_job_समयकरोut(काष्ठा drm_sched_job *s_job)
अणु
	काष्ठा amdgpu_ring *ring = to_amdgpu_ring(s_job->sched);
	काष्ठा amdgpu_job *job = to_amdgpu_job(s_job);
	काष्ठा amdgpu_task_info ti;
	काष्ठा amdgpu_device *adev = ring->adev;

	स_रखो(&ti, 0, माप(काष्ठा amdgpu_task_info));

	अगर (amdgpu_gpu_recovery &&
	    amdgpu_ring_soft_recovery(ring, job->vmid, s_job->s_fence->parent)) अणु
		DRM_ERROR("ring %s timeout, but soft recovered\n",
			  s_job->sched->name);
		वापस DRM_GPU_SCHED_STAT_NOMINAL;
	पूर्ण

	amdgpu_vm_get_task_info(ring->adev, job->pasid, &ti);
	DRM_ERROR("ring %s timeout, signaled seq=%u, emitted seq=%u\n",
		  job->base.sched->name, atomic_पढ़ो(&ring->fence_drv.last_seq),
		  ring->fence_drv.sync_seq);
	DRM_ERROR("Process information: process %s pid %d thread %s pid %d\n",
		  ti.process_name, ti.tgid, ti.task_name, ti.pid);

	अगर (amdgpu_device_should_recover_gpu(ring->adev)) अणु
		amdgpu_device_gpu_recover(ring->adev, job);
		वापस DRM_GPU_SCHED_STAT_NOMINAL;
	पूर्ण अन्यथा अणु
		drm_sched_suspend_समयout(&ring->sched);
		अगर (amdgpu_sriov_vf(adev))
			adev->virt.tdr_debug = true;
		वापस DRM_GPU_SCHED_STAT_NOMINAL;
	पूर्ण
पूर्ण

पूर्णांक amdgpu_job_alloc(काष्ठा amdgpu_device *adev, अचिन्हित num_ibs,
		     काष्ठा amdgpu_job **job, काष्ठा amdgpu_vm *vm)
अणु
	माप_प्रकार size = माप(काष्ठा amdgpu_job);

	अगर (num_ibs == 0)
		वापस -EINVAL;

	size += माप(काष्ठा amdgpu_ib) * num_ibs;

	*job = kzalloc(size, GFP_KERNEL);
	अगर (!*job)
		वापस -ENOMEM;

	/*
	 * Initialize the scheduler to at least some ring so that we always
	 * have a poपूर्णांकer to adev.
	 */
	(*job)->base.sched = &adev->rings[0]->sched;
	(*job)->vm = vm;
	(*job)->ibs = (व्योम *)&(*job)[1];
	(*job)->num_ibs = num_ibs;

	amdgpu_sync_create(&(*job)->sync);
	amdgpu_sync_create(&(*job)->sched_sync);
	(*job)->vram_lost_counter = atomic_पढ़ो(&adev->vram_lost_counter);
	(*job)->vm_pd_addr = AMDGPU_BO_INVALID_OFFSET;

	वापस 0;
पूर्ण

पूर्णांक amdgpu_job_alloc_with_ib(काष्ठा amdgpu_device *adev, अचिन्हित size,
		क्रमागत amdgpu_ib_pool_type pool_type,
		काष्ठा amdgpu_job **job)
अणु
	पूर्णांक r;

	r = amdgpu_job_alloc(adev, 1, job, शून्य);
	अगर (r)
		वापस r;

	r = amdgpu_ib_get(adev, शून्य, size, pool_type, &(*job)->ibs[0]);
	अगर (r)
		kमुक्त(*job);

	वापस r;
पूर्ण

व्योम amdgpu_job_मुक्त_resources(काष्ठा amdgpu_job *job)
अणु
	काष्ठा amdgpu_ring *ring = to_amdgpu_ring(job->base.sched);
	काष्ठा dma_fence *f;
	अचिन्हित i;

	/* use sched fence अगर available */
	f = job->base.s_fence ? &job->base.s_fence->finished : job->fence;

	क्रम (i = 0; i < job->num_ibs; ++i)
		amdgpu_ib_मुक्त(ring->adev, &job->ibs[i], f);
पूर्ण

अटल व्योम amdgpu_job_मुक्त_cb(काष्ठा drm_sched_job *s_job)
अणु
	काष्ठा amdgpu_job *job = to_amdgpu_job(s_job);

	drm_sched_job_cleanup(s_job);

	dma_fence_put(job->fence);
	amdgpu_sync_मुक्त(&job->sync);
	amdgpu_sync_मुक्त(&job->sched_sync);
	kमुक्त(job);
पूर्ण

व्योम amdgpu_job_मुक्त(काष्ठा amdgpu_job *job)
अणु
	amdgpu_job_मुक्त_resources(job);

	dma_fence_put(job->fence);
	amdgpu_sync_मुक्त(&job->sync);
	amdgpu_sync_मुक्त(&job->sched_sync);
	kमुक्त(job);
पूर्ण

पूर्णांक amdgpu_job_submit(काष्ठा amdgpu_job *job, काष्ठा drm_sched_entity *entity,
		      व्योम *owner, काष्ठा dma_fence **f)
अणु
	पूर्णांक r;

	अगर (!f)
		वापस -EINVAL;

	r = drm_sched_job_init(&job->base, entity, owner);
	अगर (r)
		वापस r;

	*f = dma_fence_get(&job->base.s_fence->finished);
	amdgpu_job_मुक्त_resources(job);
	drm_sched_entity_push_job(&job->base, entity);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_job_submit_direct(काष्ठा amdgpu_job *job, काष्ठा amdgpu_ring *ring,
			     काष्ठा dma_fence **fence)
अणु
	पूर्णांक r;

	job->base.sched = &ring->sched;
	r = amdgpu_ib_schedule(ring, job->num_ibs, job->ibs, शून्य, fence);
	job->fence = dma_fence_get(*fence);
	अगर (r)
		वापस r;

	amdgpu_job_मुक्त(job);
	वापस 0;
पूर्ण

अटल काष्ठा dma_fence *amdgpu_job_dependency(काष्ठा drm_sched_job *sched_job,
					       काष्ठा drm_sched_entity *s_entity)
अणु
	काष्ठा amdgpu_ring *ring = to_amdgpu_ring(s_entity->rq->sched);
	काष्ठा amdgpu_job *job = to_amdgpu_job(sched_job);
	काष्ठा amdgpu_vm *vm = job->vm;
	काष्ठा dma_fence *fence;
	पूर्णांक r;

	fence = amdgpu_sync_get_fence(&job->sync);
	अगर (fence && drm_sched_dependency_optimized(fence, s_entity)) अणु
		r = amdgpu_sync_fence(&job->sched_sync, fence);
		अगर (r)
			DRM_ERROR("Error adding fence (%d)\n", r);
	पूर्ण

	जबतक (fence == शून्य && vm && !job->vmid) अणु
		r = amdgpu_vmid_grab(vm, ring, &job->sync,
				     &job->base.s_fence->finished,
				     job);
		अगर (r)
			DRM_ERROR("Error getting VM ID (%d)\n", r);

		fence = amdgpu_sync_get_fence(&job->sync);
	पूर्ण

	वापस fence;
पूर्ण

अटल काष्ठा dma_fence *amdgpu_job_run(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा amdgpu_ring *ring = to_amdgpu_ring(sched_job->sched);
	काष्ठा dma_fence *fence = शून्य, *finished;
	काष्ठा amdgpu_job *job;
	पूर्णांक r = 0;

	job = to_amdgpu_job(sched_job);
	finished = &job->base.s_fence->finished;

	BUG_ON(amdgpu_sync_peek_fence(&job->sync, शून्य));

	trace_amdgpu_sched_run_job(job);

	अगर (job->vram_lost_counter != atomic_पढ़ो(&ring->adev->vram_lost_counter))
		dma_fence_set_error(finished, -ECANCELED);/* skip IB as well अगर VRAM lost */

	अगर (finished->error < 0) अणु
		DRM_INFO("Skip scheduling IBs!\n");
	पूर्ण अन्यथा अणु
		r = amdgpu_ib_schedule(ring, job->num_ibs, job->ibs, job,
				       &fence);
		अगर (r)
			DRM_ERROR("Error scheduling IBs (%d)\n", r);
	पूर्ण
	/* अगर gpu reset, hw fence will be replaced here */
	dma_fence_put(job->fence);
	job->fence = dma_fence_get(fence);

	amdgpu_job_मुक्त_resources(job);

	fence = r ? ERR_PTR(r) : fence;
	वापस fence;
पूर्ण

#घोषणा to_drm_sched_job(sched_job)		\
		container_of((sched_job), काष्ठा drm_sched_job, queue_node)

व्योम amdgpu_job_stop_all_jobs_on_sched(काष्ठा drm_gpu_scheduler *sched)
अणु
	काष्ठा drm_sched_job *s_job;
	काष्ठा drm_sched_entity *s_entity = शून्य;
	पूर्णांक i;

	/* Signal all jobs not yet scheduled */
	क्रम (i = DRM_SCHED_PRIORITY_COUNT - 1; i >= DRM_SCHED_PRIORITY_MIN; i--) अणु
		काष्ठा drm_sched_rq *rq = &sched->sched_rq[i];

		अगर (!rq)
			जारी;

		spin_lock(&rq->lock);
		list_क्रम_each_entry(s_entity, &rq->entities, list) अणु
			जबतक ((s_job = to_drm_sched_job(spsc_queue_pop(&s_entity->job_queue)))) अणु
				काष्ठा drm_sched_fence *s_fence = s_job->s_fence;

				dma_fence_संकेत(&s_fence->scheduled);
				dma_fence_set_error(&s_fence->finished, -EHWPOISON);
				dma_fence_संकेत(&s_fence->finished);
			पूर्ण
		पूर्ण
		spin_unlock(&rq->lock);
	पूर्ण

	/* Signal all jobs alपढ़ोy scheduled to HW */
	list_क्रम_each_entry(s_job, &sched->pending_list, list) अणु
		काष्ठा drm_sched_fence *s_fence = s_job->s_fence;

		dma_fence_set_error(&s_fence->finished, -EHWPOISON);
		dma_fence_संकेत(&s_fence->finished);
	पूर्ण
पूर्ण

स्थिर काष्ठा drm_sched_backend_ops amdgpu_sched_ops = अणु
	.dependency = amdgpu_job_dependency,
	.run_job = amdgpu_job_run,
	.समयकरोut_job = amdgpu_job_समयकरोut,
	.मुक्त_job = amdgpu_job_मुक्त_cb
पूर्ण;
