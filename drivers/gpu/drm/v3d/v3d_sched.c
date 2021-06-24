<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2018 Broadcom */

/**
 * DOC: Broadcom V3D scheduling
 *
 * The shared DRM GPU scheduler is used to coordinate submitting jobs
 * to the hardware.  Each DRM fd (roughly a client process) माला_लो its
 * own scheduler entity, which will process jobs in order.  The GPU
 * scheduler will round-robin between clients to submit the next job.
 *
 * For simplicity, and in order to keep latency low क्रम पूर्णांकeractive
 * jobs when bulk background jobs are queued up, we submit a new job
 * to the HW only when it has completed the last one, instead of
 * filling up the CT[01]Q FIFOs with jobs.  Similarly, we use
 * v3d_job_dependency() to manage the dependency between bin and
 * render, instead of having the clients submit jobs using the HW's
 * semaphores to पूर्णांकerlock between them.
 */

#समावेश <linux/kthपढ़ो.h>

#समावेश "v3d_drv.h"
#समावेश "v3d_regs.h"
#समावेश "v3d_trace.h"

अटल काष्ठा v3d_job *
to_v3d_job(काष्ठा drm_sched_job *sched_job)
अणु
	वापस container_of(sched_job, काष्ठा v3d_job, base);
पूर्ण

अटल काष्ठा v3d_bin_job *
to_bin_job(काष्ठा drm_sched_job *sched_job)
अणु
	वापस container_of(sched_job, काष्ठा v3d_bin_job, base.base);
पूर्ण

अटल काष्ठा v3d_render_job *
to_render_job(काष्ठा drm_sched_job *sched_job)
अणु
	वापस container_of(sched_job, काष्ठा v3d_render_job, base.base);
पूर्ण

अटल काष्ठा v3d_tfu_job *
to_tfu_job(काष्ठा drm_sched_job *sched_job)
अणु
	वापस container_of(sched_job, काष्ठा v3d_tfu_job, base.base);
पूर्ण

अटल काष्ठा v3d_csd_job *
to_csd_job(काष्ठा drm_sched_job *sched_job)
अणु
	वापस container_of(sched_job, काष्ठा v3d_csd_job, base.base);
पूर्ण

अटल व्योम
v3d_job_मुक्त(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_job *job = to_v3d_job(sched_job);

	drm_sched_job_cleanup(sched_job);
	v3d_job_put(job);
पूर्ण

/*
 * Returns the fences that the job depends on, one by one.
 *
 * If placed in the scheduler's .dependency method, the corresponding
 * .run_job won't be called until all of them have been संकेतed.
 */
अटल काष्ठा dma_fence *
v3d_job_dependency(काष्ठा drm_sched_job *sched_job,
		   काष्ठा drm_sched_entity *s_entity)
अणु
	काष्ठा v3d_job *job = to_v3d_job(sched_job);

	/* XXX: Wait on a fence क्रम चयनing the GMP अगर necessary,
	 * and then करो so.
	 */

	अगर (!xa_empty(&job->deps))
		वापस xa_erase(&job->deps, job->last_dep++);

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_fence *v3d_bin_job_run(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_bin_job *job = to_bin_job(sched_job);
	काष्ठा v3d_dev *v3d = job->base.v3d;
	काष्ठा drm_device *dev = &v3d->drm;
	काष्ठा dma_fence *fence;
	अचिन्हित दीर्घ irqflags;

	अगर (unlikely(job->base.base.s_fence->finished.error))
		वापस शून्य;

	/* Lock required around bin_job update vs
	 * v3d_overflow_mem_work().
	 */
	spin_lock_irqsave(&v3d->job_lock, irqflags);
	v3d->bin_job = job;
	/* Clear out the overflow allocation, so we करोn't
	 * reuse the overflow attached to a previous job.
	 */
	V3D_CORE_WRITE(0, V3D_PTB_BPOS, 0);
	spin_unlock_irqrestore(&v3d->job_lock, irqflags);

	v3d_invalidate_caches(v3d);

	fence = v3d_fence_create(v3d, V3D_BIN);
	अगर (IS_ERR(fence))
		वापस शून्य;

	अगर (job->base.irq_fence)
		dma_fence_put(job->base.irq_fence);
	job->base.irq_fence = dma_fence_get(fence);

	trace_v3d_submit_cl(dev, false, to_v3d_fence(fence)->seqno,
			    job->start, job->end);

	/* Set the current and end address of the control list.
	 * Writing the end रेजिस्टर is what starts the job.
	 */
	अगर (job->qma) अणु
		V3D_CORE_WRITE(0, V3D_CLE_CT0QMA, job->qma);
		V3D_CORE_WRITE(0, V3D_CLE_CT0QMS, job->qms);
	पूर्ण
	अगर (job->qts) अणु
		V3D_CORE_WRITE(0, V3D_CLE_CT0QTS,
			       V3D_CLE_CT0QTS_ENABLE |
			       job->qts);
	पूर्ण
	V3D_CORE_WRITE(0, V3D_CLE_CT0QBA, job->start);
	V3D_CORE_WRITE(0, V3D_CLE_CT0QEA, job->end);

	वापस fence;
पूर्ण

अटल काष्ठा dma_fence *v3d_render_job_run(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_render_job *job = to_render_job(sched_job);
	काष्ठा v3d_dev *v3d = job->base.v3d;
	काष्ठा drm_device *dev = &v3d->drm;
	काष्ठा dma_fence *fence;

	अगर (unlikely(job->base.base.s_fence->finished.error))
		वापस शून्य;

	v3d->render_job = job;

	/* Can we aव्योम this flush?  We need to be careful of
	 * scheduling, though -- imagine job0 rendering to texture and
	 * job1 पढ़ोing, and them being executed as bin0, bin1,
	 * render0, render1, so that render1's flush at bin समय
	 * wasn't enough.
	 */
	v3d_invalidate_caches(v3d);

	fence = v3d_fence_create(v3d, V3D_RENDER);
	अगर (IS_ERR(fence))
		वापस शून्य;

	अगर (job->base.irq_fence)
		dma_fence_put(job->base.irq_fence);
	job->base.irq_fence = dma_fence_get(fence);

	trace_v3d_submit_cl(dev, true, to_v3d_fence(fence)->seqno,
			    job->start, job->end);

	/* XXX: Set the QCFG */

	/* Set the current and end address of the control list.
	 * Writing the end रेजिस्टर is what starts the job.
	 */
	V3D_CORE_WRITE(0, V3D_CLE_CT1QBA, job->start);
	V3D_CORE_WRITE(0, V3D_CLE_CT1QEA, job->end);

	वापस fence;
पूर्ण

अटल काष्ठा dma_fence *
v3d_tfu_job_run(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_tfu_job *job = to_tfu_job(sched_job);
	काष्ठा v3d_dev *v3d = job->base.v3d;
	काष्ठा drm_device *dev = &v3d->drm;
	काष्ठा dma_fence *fence;

	fence = v3d_fence_create(v3d, V3D_TFU);
	अगर (IS_ERR(fence))
		वापस शून्य;

	v3d->tfu_job = job;
	अगर (job->base.irq_fence)
		dma_fence_put(job->base.irq_fence);
	job->base.irq_fence = dma_fence_get(fence);

	trace_v3d_submit_tfu(dev, to_v3d_fence(fence)->seqno);

	V3D_WRITE(V3D_TFU_IIA, job->args.iia);
	V3D_WRITE(V3D_TFU_IIS, job->args.iis);
	V3D_WRITE(V3D_TFU_ICA, job->args.ica);
	V3D_WRITE(V3D_TFU_IUA, job->args.iua);
	V3D_WRITE(V3D_TFU_IOA, job->args.ioa);
	V3D_WRITE(V3D_TFU_IOS, job->args.ios);
	V3D_WRITE(V3D_TFU_COEF0, job->args.coef[0]);
	अगर (job->args.coef[0] & V3D_TFU_COEF0_USECOEF) अणु
		V3D_WRITE(V3D_TFU_COEF1, job->args.coef[1]);
		V3D_WRITE(V3D_TFU_COEF2, job->args.coef[2]);
		V3D_WRITE(V3D_TFU_COEF3, job->args.coef[3]);
	पूर्ण
	/* ICFG kicks off the job. */
	V3D_WRITE(V3D_TFU_ICFG, job->args.icfg | V3D_TFU_ICFG_IOC);

	वापस fence;
पूर्ण

अटल काष्ठा dma_fence *
v3d_csd_job_run(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_csd_job *job = to_csd_job(sched_job);
	काष्ठा v3d_dev *v3d = job->base.v3d;
	काष्ठा drm_device *dev = &v3d->drm;
	काष्ठा dma_fence *fence;
	पूर्णांक i;

	v3d->csd_job = job;

	v3d_invalidate_caches(v3d);

	fence = v3d_fence_create(v3d, V3D_CSD);
	अगर (IS_ERR(fence))
		वापस शून्य;

	अगर (job->base.irq_fence)
		dma_fence_put(job->base.irq_fence);
	job->base.irq_fence = dma_fence_get(fence);

	trace_v3d_submit_csd(dev, to_v3d_fence(fence)->seqno);

	क्रम (i = 1; i <= 6; i++)
		V3D_CORE_WRITE(0, V3D_CSD_QUEUED_CFG0 + 4 * i, job->args.cfg[i]);
	/* CFG0 ग_लिखो kicks off the job. */
	V3D_CORE_WRITE(0, V3D_CSD_QUEUED_CFG0, job->args.cfg[0]);

	वापस fence;
पूर्ण

अटल काष्ठा dma_fence *
v3d_cache_clean_job_run(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_job *job = to_v3d_job(sched_job);
	काष्ठा v3d_dev *v3d = job->v3d;

	v3d_clean_caches(v3d);

	वापस शून्य;
पूर्ण

अटल क्रमागत drm_gpu_sched_stat
v3d_gpu_reset_क्रम_समयout(काष्ठा v3d_dev *v3d, काष्ठा drm_sched_job *sched_job)
अणु
	क्रमागत v3d_queue q;

	mutex_lock(&v3d->reset_lock);

	/* block scheduler */
	क्रम (q = 0; q < V3D_MAX_QUEUES; q++)
		drm_sched_stop(&v3d->queue[q].sched, sched_job);

	अगर (sched_job)
		drm_sched_increase_karma(sched_job);

	/* get the GPU back पूर्णांकo the init state */
	v3d_reset(v3d);

	क्रम (q = 0; q < V3D_MAX_QUEUES; q++)
		drm_sched_resubmit_jobs(&v3d->queue[q].sched);

	/* Unblock schedulers and restart their jobs. */
	क्रम (q = 0; q < V3D_MAX_QUEUES; q++) अणु
		drm_sched_start(&v3d->queue[q].sched, true);
	पूर्ण

	mutex_unlock(&v3d->reset_lock);

	वापस DRM_GPU_SCHED_STAT_NOMINAL;
पूर्ण

/* If the current address or वापस address have changed, then the GPU
 * has probably made progress and we should delay the reset.  This
 * could fail अगर the GPU got in an infinite loop in the CL, but that
 * is pretty unlikely outside of an i-g-t testहाल.
 */
अटल क्रमागत drm_gpu_sched_stat
v3d_cl_job_समयकरोut(काष्ठा drm_sched_job *sched_job, क्रमागत v3d_queue q,
		    u32 *समयकरोut_ctca, u32 *समयकरोut_ctra)
अणु
	काष्ठा v3d_job *job = to_v3d_job(sched_job);
	काष्ठा v3d_dev *v3d = job->v3d;
	u32 ctca = V3D_CORE_READ(0, V3D_CLE_CTNCA(q));
	u32 ctra = V3D_CORE_READ(0, V3D_CLE_CTNRA(q));

	अगर (*समयकरोut_ctca != ctca || *समयकरोut_ctra != ctra) अणु
		*समयकरोut_ctca = ctca;
		*समयकरोut_ctra = ctra;
		वापस DRM_GPU_SCHED_STAT_NOMINAL;
	पूर्ण

	वापस v3d_gpu_reset_क्रम_समयout(v3d, sched_job);
पूर्ण

अटल क्रमागत drm_gpu_sched_stat
v3d_bin_job_समयकरोut(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_bin_job *job = to_bin_job(sched_job);

	वापस v3d_cl_job_समयकरोut(sched_job, V3D_BIN,
				   &job->समयकरोut_ctca, &job->समयकरोut_ctra);
पूर्ण

अटल क्रमागत drm_gpu_sched_stat
v3d_render_job_समयकरोut(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_render_job *job = to_render_job(sched_job);

	वापस v3d_cl_job_समयकरोut(sched_job, V3D_RENDER,
				   &job->समयकरोut_ctca, &job->समयकरोut_ctra);
पूर्ण

अटल क्रमागत drm_gpu_sched_stat
v3d_generic_job_समयकरोut(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_job *job = to_v3d_job(sched_job);

	वापस v3d_gpu_reset_क्रम_समयout(job->v3d, sched_job);
पूर्ण

अटल क्रमागत drm_gpu_sched_stat
v3d_csd_job_समयकरोut(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा v3d_csd_job *job = to_csd_job(sched_job);
	काष्ठा v3d_dev *v3d = job->base.v3d;
	u32 batches = V3D_CORE_READ(0, V3D_CSD_CURRENT_CFG4);

	/* If we've made progress, skip reset and let the समयr get
	 * rearmed.
	 */
	अगर (job->समयकरोut_batches != batches) अणु
		job->समयकरोut_batches = batches;
		वापस DRM_GPU_SCHED_STAT_NOMINAL;
	पूर्ण

	वापस v3d_gpu_reset_क्रम_समयout(v3d, sched_job);
पूर्ण

अटल स्थिर काष्ठा drm_sched_backend_ops v3d_bin_sched_ops = अणु
	.dependency = v3d_job_dependency,
	.run_job = v3d_bin_job_run,
	.समयकरोut_job = v3d_bin_job_समयकरोut,
	.मुक्त_job = v3d_job_मुक्त,
पूर्ण;

अटल स्थिर काष्ठा drm_sched_backend_ops v3d_render_sched_ops = अणु
	.dependency = v3d_job_dependency,
	.run_job = v3d_render_job_run,
	.समयकरोut_job = v3d_render_job_समयकरोut,
	.मुक्त_job = v3d_job_मुक्त,
पूर्ण;

अटल स्थिर काष्ठा drm_sched_backend_ops v3d_tfu_sched_ops = अणु
	.dependency = v3d_job_dependency,
	.run_job = v3d_tfu_job_run,
	.समयकरोut_job = v3d_generic_job_समयकरोut,
	.मुक्त_job = v3d_job_मुक्त,
पूर्ण;

अटल स्थिर काष्ठा drm_sched_backend_ops v3d_csd_sched_ops = अणु
	.dependency = v3d_job_dependency,
	.run_job = v3d_csd_job_run,
	.समयकरोut_job = v3d_csd_job_समयकरोut,
	.मुक्त_job = v3d_job_मुक्त
पूर्ण;

अटल स्थिर काष्ठा drm_sched_backend_ops v3d_cache_clean_sched_ops = अणु
	.dependency = v3d_job_dependency,
	.run_job = v3d_cache_clean_job_run,
	.समयकरोut_job = v3d_generic_job_समयकरोut,
	.मुक्त_job = v3d_job_मुक्त
पूर्ण;

पूर्णांक
v3d_sched_init(काष्ठा v3d_dev *v3d)
अणु
	पूर्णांक hw_jobs_limit = 1;
	पूर्णांक job_hang_limit = 0;
	पूर्णांक hang_limit_ms = 500;
	पूर्णांक ret;

	ret = drm_sched_init(&v3d->queue[V3D_BIN].sched,
			     &v3d_bin_sched_ops,
			     hw_jobs_limit, job_hang_limit,
			     msecs_to_jअगरfies(hang_limit_ms),
			     शून्य, "v3d_bin");
	अगर (ret) अणु
		dev_err(v3d->drm.dev, "Failed to create bin scheduler: %d.", ret);
		वापस ret;
	पूर्ण

	ret = drm_sched_init(&v3d->queue[V3D_RENDER].sched,
			     &v3d_render_sched_ops,
			     hw_jobs_limit, job_hang_limit,
			     msecs_to_jअगरfies(hang_limit_ms),
			     शून्य, "v3d_render");
	अगर (ret) अणु
		dev_err(v3d->drm.dev, "Failed to create render scheduler: %d.",
			ret);
		v3d_sched_fini(v3d);
		वापस ret;
	पूर्ण

	ret = drm_sched_init(&v3d->queue[V3D_TFU].sched,
			     &v3d_tfu_sched_ops,
			     hw_jobs_limit, job_hang_limit,
			     msecs_to_jअगरfies(hang_limit_ms),
			     शून्य, "v3d_tfu");
	अगर (ret) अणु
		dev_err(v3d->drm.dev, "Failed to create TFU scheduler: %d.",
			ret);
		v3d_sched_fini(v3d);
		वापस ret;
	पूर्ण

	अगर (v3d_has_csd(v3d)) अणु
		ret = drm_sched_init(&v3d->queue[V3D_CSD].sched,
				     &v3d_csd_sched_ops,
				     hw_jobs_limit, job_hang_limit,
				     msecs_to_jअगरfies(hang_limit_ms),
				     शून्य, "v3d_csd");
		अगर (ret) अणु
			dev_err(v3d->drm.dev, "Failed to create CSD scheduler: %d.",
				ret);
			v3d_sched_fini(v3d);
			वापस ret;
		पूर्ण

		ret = drm_sched_init(&v3d->queue[V3D_CACHE_CLEAN].sched,
				     &v3d_cache_clean_sched_ops,
				     hw_jobs_limit, job_hang_limit,
				     msecs_to_jअगरfies(hang_limit_ms),
				     शून्य, "v3d_cache_clean");
		अगर (ret) अणु
			dev_err(v3d->drm.dev, "Failed to create CACHE_CLEAN scheduler: %d.",
				ret);
			v3d_sched_fini(v3d);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम
v3d_sched_fini(काष्ठा v3d_dev *v3d)
अणु
	क्रमागत v3d_queue q;

	क्रम (q = 0; q < V3D_MAX_QUEUES; q++) अणु
		अगर (v3d->queue[q].sched.पढ़ोy)
			drm_sched_fini(&v3d->queue[q].sched);
	पूर्ण
पूर्ण
