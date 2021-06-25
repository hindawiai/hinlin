<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Etnaviv Project
 */

#समावेश <linux/moduleparam.h>

#समावेश "etnaviv_drv.h"
#समावेश "etnaviv_dump.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_sched.h"
#समावेश "state.xml.h"

अटल पूर्णांक etnaviv_job_hang_limit = 0;
module_param_named(job_hang_limit, etnaviv_job_hang_limit, पूर्णांक , 0444);
अटल पूर्णांक etnaviv_hw_jobs_limit = 4;
module_param_named(hw_job_limit, etnaviv_hw_jobs_limit, पूर्णांक , 0444);

अटल काष्ठा dma_fence *
etnaviv_sched_dependency(काष्ठा drm_sched_job *sched_job,
			 काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा etnaviv_gem_submit *submit = to_etnaviv_submit(sched_job);
	काष्ठा dma_fence *fence;
	पूर्णांक i;

	अगर (unlikely(submit->in_fence)) अणु
		fence = submit->in_fence;
		submit->in_fence = शून्य;

		अगर (!dma_fence_is_संकेतed(fence))
			वापस fence;

		dma_fence_put(fence);
	पूर्ण

	क्रम (i = 0; i < submit->nr_bos; i++) अणु
		काष्ठा etnaviv_gem_submit_bo *bo = &submit->bos[i];
		पूर्णांक j;

		अगर (bo->excl) अणु
			fence = bo->excl;
			bo->excl = शून्य;

			अगर (!dma_fence_is_संकेतed(fence))
				वापस fence;

			dma_fence_put(fence);
		पूर्ण

		क्रम (j = 0; j < bo->nr_shared; j++) अणु
			अगर (!bo->shared[j])
				जारी;

			fence = bo->shared[j];
			bo->shared[j] = शून्य;

			अगर (!dma_fence_is_संकेतed(fence))
				वापस fence;

			dma_fence_put(fence);
		पूर्ण
		kमुक्त(bo->shared);
		bo->nr_shared = 0;
		bo->shared = शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_fence *etnaviv_sched_run_job(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा etnaviv_gem_submit *submit = to_etnaviv_submit(sched_job);
	काष्ठा dma_fence *fence = शून्य;

	अगर (likely(!sched_job->s_fence->finished.error))
		fence = etnaviv_gpu_submit(submit);
	अन्यथा
		dev_dbg(submit->gpu->dev, "skipping bad job\n");

	वापस fence;
पूर्ण

अटल क्रमागत drm_gpu_sched_stat etnaviv_sched_समयकरोut_job(काष्ठा drm_sched_job
							  *sched_job)
अणु
	काष्ठा etnaviv_gem_submit *submit = to_etnaviv_submit(sched_job);
	काष्ठा etnaviv_gpu *gpu = submit->gpu;
	u32 dma_addr;
	पूर्णांक change;

	/* block scheduler */
	drm_sched_stop(&gpu->sched, sched_job);

	/*
	 * If the GPU managed to complete this jobs fence, the timout is
	 * spurious. Bail out.
	 */
	अगर (dma_fence_is_संकेतed(submit->out_fence))
		जाओ out_no_समयout;

	/*
	 * If the GPU is still making क्रमward progress on the front-end (which
	 * should never loop) we shअगरt out the समयout to give it a chance to
	 * finish the job.
	 */
	dma_addr = gpu_पढ़ो(gpu, VIVS_FE_DMA_ADDRESS);
	change = dma_addr - gpu->hangcheck_dma_addr;
	अगर (change < 0 || change > 16) अणु
		gpu->hangcheck_dma_addr = dma_addr;
		जाओ out_no_समयout;
	पूर्ण

	अगर(sched_job)
		drm_sched_increase_karma(sched_job);

	/* get the GPU back पूर्णांकo the init state */
	etnaviv_core_dump(submit);
	etnaviv_gpu_recover_hang(gpu);

	drm_sched_resubmit_jobs(&gpu->sched);

	drm_sched_start(&gpu->sched, true);
	वापस DRM_GPU_SCHED_STAT_NOMINAL;

out_no_समयout:
	/* restart scheduler after GPU is usable again */
	drm_sched_start(&gpu->sched, true);
	वापस DRM_GPU_SCHED_STAT_NOMINAL;
पूर्ण

अटल व्योम etnaviv_sched_मुक्त_job(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा etnaviv_gem_submit *submit = to_etnaviv_submit(sched_job);

	drm_sched_job_cleanup(sched_job);

	etnaviv_submit_put(submit);
पूर्ण

अटल स्थिर काष्ठा drm_sched_backend_ops etnaviv_sched_ops = अणु
	.dependency = etnaviv_sched_dependency,
	.run_job = etnaviv_sched_run_job,
	.समयकरोut_job = etnaviv_sched_समयकरोut_job,
	.मुक्त_job = etnaviv_sched_मुक्त_job,
पूर्ण;

पूर्णांक etnaviv_sched_push_job(काष्ठा drm_sched_entity *sched_entity,
			   काष्ठा etnaviv_gem_submit *submit)
अणु
	पूर्णांक ret = 0;

	/*
	 * Hold the fence lock across the whole operation to aव्योम jobs being
	 * pushed out of order with regard to their sched fence seqnos as
	 * allocated in drm_sched_job_init.
	 */
	mutex_lock(&submit->gpu->fence_lock);

	ret = drm_sched_job_init(&submit->sched_job, sched_entity,
				 submit->ctx);
	अगर (ret)
		जाओ out_unlock;

	submit->out_fence = dma_fence_get(&submit->sched_job.s_fence->finished);
	submit->out_fence_id = idr_alloc_cyclic(&submit->gpu->fence_idr,
						submit->out_fence, 0,
						पूर्णांक_उच्च, GFP_KERNEL);
	अगर (submit->out_fence_id < 0) अणु
		drm_sched_job_cleanup(&submit->sched_job);
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	/* the scheduler holds on to the job now */
	kref_get(&submit->refcount);

	drm_sched_entity_push_job(&submit->sched_job, sched_entity);

out_unlock:
	mutex_unlock(&submit->gpu->fence_lock);

	वापस ret;
पूर्ण

पूर्णांक etnaviv_sched_init(काष्ठा etnaviv_gpu *gpu)
अणु
	पूर्णांक ret;

	ret = drm_sched_init(&gpu->sched, &etnaviv_sched_ops,
			     etnaviv_hw_jobs_limit, etnaviv_job_hang_limit,
			     msecs_to_jअगरfies(500), शून्य, dev_name(gpu->dev));
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

व्योम etnaviv_sched_fini(काष्ठा etnaviv_gpu *gpu)
अणु
	drm_sched_fini(&gpu->sched);
पूर्ण
