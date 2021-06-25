<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2019 Linaro, Ltd, Rob Herring <robh@kernel.org> */
/* Copyright 2019 Collabora ltd. */
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-resv.h>
#समावेश <drm/gpu_scheduler.h>
#समावेश <drm/panfrost_drm.h>

#समावेश "panfrost_device.h"
#समावेश "panfrost_devfreq.h"
#समावेश "panfrost_job.h"
#समावेश "panfrost_features.h"
#समावेश "panfrost_issues.h"
#समावेश "panfrost_gem.h"
#समावेश "panfrost_regs.h"
#समावेश "panfrost_gpu.h"
#समावेश "panfrost_mmu.h"

#घोषणा JOB_TIMEOUT_MS 500

#घोषणा job_ग_लिखो(dev, reg, data) ग_लिखोl(data, dev->iomem + (reg))
#घोषणा job_पढ़ो(dev, reg) पढ़ोl(dev->iomem + (reg))

क्रमागत panfrost_queue_status अणु
	PANFROST_QUEUE_STATUS_ACTIVE,
	PANFROST_QUEUE_STATUS_STOPPED,
	PANFROST_QUEUE_STATUS_STARTING,
	PANFROST_QUEUE_STATUS_FAULT_PENDING,
पूर्ण;

काष्ठा panfrost_queue_state अणु
	काष्ठा drm_gpu_scheduler sched;
	atomic_t status;
	काष्ठा mutex lock;
	u64 fence_context;
	u64 emit_seqno;
पूर्ण;

काष्ठा panfrost_job_slot अणु
	काष्ठा panfrost_queue_state queue[NUM_JOB_SLOTS];
	spinlock_t job_lock;
पूर्ण;

अटल काष्ठा panfrost_job *
to_panfrost_job(काष्ठा drm_sched_job *sched_job)
अणु
	वापस container_of(sched_job, काष्ठा panfrost_job, base);
पूर्ण

काष्ठा panfrost_fence अणु
	काष्ठा dma_fence base;
	काष्ठा drm_device *dev;
	/* panfrost seqno क्रम संकेतed() test */
	u64 seqno;
	पूर्णांक queue;
पूर्ण;

अटल अंतरभूत काष्ठा panfrost_fence *
to_panfrost_fence(काष्ठा dma_fence *fence)
अणु
	वापस (काष्ठा panfrost_fence *)fence;
पूर्ण

अटल स्थिर अक्षर *panfrost_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "panfrost";
पूर्ण

अटल स्थिर अक्षर *panfrost_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा panfrost_fence *f = to_panfrost_fence(fence);

	चयन (f->queue) अणु
	हाल 0:
		वापस "panfrost-js-0";
	हाल 1:
		वापस "panfrost-js-1";
	हाल 2:
		वापस "panfrost-js-2";
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops panfrost_fence_ops = अणु
	.get_driver_name = panfrost_fence_get_driver_name,
	.get_समयline_name = panfrost_fence_get_समयline_name,
पूर्ण;

अटल काष्ठा dma_fence *panfrost_fence_create(काष्ठा panfrost_device *pfdev, पूर्णांक js_num)
अणु
	काष्ठा panfrost_fence *fence;
	काष्ठा panfrost_job_slot *js = pfdev->js;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (!fence)
		वापस ERR_PTR(-ENOMEM);

	fence->dev = pfdev->ddev;
	fence->queue = js_num;
	fence->seqno = ++js->queue[js_num].emit_seqno;
	dma_fence_init(&fence->base, &panfrost_fence_ops, &js->job_lock,
		       js->queue[js_num].fence_context, fence->seqno);

	वापस &fence->base;
पूर्ण

अटल पूर्णांक panfrost_job_get_slot(काष्ठा panfrost_job *job)
अणु
	/* JS0: fragment jobs.
	 * JS1: vertex/tiler jobs
	 * JS2: compute jobs
	 */
	अगर (job->requirements & PANFROST_JD_REQ_FS)
		वापस 0;

/* Not exposed to userspace yet */
#अगर 0
	अगर (job->requirements & PANFROST_JD_REQ_ONLY_COMPUTE) अणु
		अगर ((job->requirements & PANFROST_JD_REQ_CORE_GRP_MASK) &&
		    (job->pfdev->features.nr_core_groups == 2))
			वापस 2;
		अगर (panfrost_has_hw_issue(job->pfdev, HW_ISSUE_8987))
			वापस 2;
	पूर्ण
#पूर्ण_अगर
	वापस 1;
पूर्ण

अटल व्योम panfrost_job_ग_लिखो_affinity(काष्ठा panfrost_device *pfdev,
					u32 requirements,
					पूर्णांक js)
अणु
	u64 affinity;

	/*
	 * Use all cores क्रम now.
	 * Eventually we may need to support tiler only jobs and h/w with
	 * multiple (2) coherent core groups
	 */
	affinity = pfdev->features.shader_present;

	job_ग_लिखो(pfdev, JS_AFFINITY_NEXT_LO(js), affinity & 0xFFFFFFFF);
	job_ग_लिखो(pfdev, JS_AFFINITY_NEXT_HI(js), affinity >> 32);
पूर्ण

अटल व्योम panfrost_job_hw_submit(काष्ठा panfrost_job *job, पूर्णांक js)
अणु
	काष्ठा panfrost_device *pfdev = job->pfdev;
	u32 cfg;
	u64 jc_head = job->jc;
	पूर्णांक ret;

	panfrost_devfreq_record_busy(&pfdev->pfdevfreq);

	ret = pm_runसमय_get_sync(pfdev->dev);
	अगर (ret < 0)
		वापस;

	अगर (WARN_ON(job_पढ़ो(pfdev, JS_COMMAND_NEXT(js)))) अणु
		वापस;
	पूर्ण

	cfg = panfrost_mmu_as_get(pfdev, &job->file_priv->mmu);

	job_ग_लिखो(pfdev, JS_HEAD_NEXT_LO(js), jc_head & 0xFFFFFFFF);
	job_ग_लिखो(pfdev, JS_HEAD_NEXT_HI(js), jc_head >> 32);

	panfrost_job_ग_लिखो_affinity(pfdev, job->requirements, js);

	/* start MMU, medium priority, cache clean/flush on end, clean/flush on
	 * start */
	cfg |= JS_CONFIG_THREAD_PRI(8) |
		JS_CONFIG_START_FLUSH_CLEAN_INVALIDATE |
		JS_CONFIG_END_FLUSH_CLEAN_INVALIDATE;

	अगर (panfrost_has_hw_feature(pfdev, HW_FEATURE_FLUSH_REDUCTION))
		cfg |= JS_CONFIG_ENABLE_FLUSH_REDUCTION;

	अगर (panfrost_has_hw_issue(pfdev, HW_ISSUE_10649))
		cfg |= JS_CONFIG_START_MMU;

	job_ग_लिखो(pfdev, JS_CONFIG_NEXT(js), cfg);

	अगर (panfrost_has_hw_feature(pfdev, HW_FEATURE_FLUSH_REDUCTION))
		job_ग_लिखो(pfdev, JS_FLUSH_ID_NEXT(js), job->flush_id);

	/* GO ! */
	dev_dbg(pfdev->dev, "JS: Submitting atom %p to js[%d] with head=0x%llx",
				job, js, jc_head);

	job_ग_लिखो(pfdev, JS_COMMAND_NEXT(js), JS_COMMAND_START);
पूर्ण

अटल व्योम panfrost_acquire_object_fences(काष्ठा drm_gem_object **bos,
					   पूर्णांक bo_count,
					   काष्ठा dma_fence **implicit_fences)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bo_count; i++)
		implicit_fences[i] = dma_resv_get_excl_rcu(bos[i]->resv);
पूर्ण

अटल व्योम panfrost_attach_object_fences(काष्ठा drm_gem_object **bos,
					  पूर्णांक bo_count,
					  काष्ठा dma_fence *fence)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bo_count; i++)
		dma_resv_add_excl_fence(bos[i]->resv, fence);
पूर्ण

पूर्णांक panfrost_job_push(काष्ठा panfrost_job *job)
अणु
	काष्ठा panfrost_device *pfdev = job->pfdev;
	पूर्णांक slot = panfrost_job_get_slot(job);
	काष्ठा drm_sched_entity *entity = &job->file_priv->sched_entity[slot];
	काष्ठा ww_acquire_ctx acquire_ctx;
	पूर्णांक ret = 0;

	mutex_lock(&pfdev->sched_lock);

	ret = drm_gem_lock_reservations(job->bos, job->bo_count,
					    &acquire_ctx);
	अगर (ret) अणु
		mutex_unlock(&pfdev->sched_lock);
		वापस ret;
	पूर्ण

	ret = drm_sched_job_init(&job->base, entity, शून्य);
	अगर (ret) अणु
		mutex_unlock(&pfdev->sched_lock);
		जाओ unlock;
	पूर्ण

	job->render_करोne_fence = dma_fence_get(&job->base.s_fence->finished);

	kref_get(&job->refcount); /* put by scheduler job completion */

	panfrost_acquire_object_fences(job->bos, job->bo_count,
				       job->implicit_fences);

	drm_sched_entity_push_job(&job->base, entity);

	mutex_unlock(&pfdev->sched_lock);

	panfrost_attach_object_fences(job->bos, job->bo_count,
				      job->render_करोne_fence);

unlock:
	drm_gem_unlock_reservations(job->bos, job->bo_count, &acquire_ctx);

	वापस ret;
पूर्ण

अटल व्योम panfrost_job_cleanup(काष्ठा kref *ref)
अणु
	काष्ठा panfrost_job *job = container_of(ref, काष्ठा panfrost_job,
						refcount);
	अचिन्हित पूर्णांक i;

	अगर (job->in_fences) अणु
		क्रम (i = 0; i < job->in_fence_count; i++)
			dma_fence_put(job->in_fences[i]);
		kvमुक्त(job->in_fences);
	पूर्ण
	अगर (job->implicit_fences) अणु
		क्रम (i = 0; i < job->bo_count; i++)
			dma_fence_put(job->implicit_fences[i]);
		kvमुक्त(job->implicit_fences);
	पूर्ण
	dma_fence_put(job->करोne_fence);
	dma_fence_put(job->render_करोne_fence);

	अगर (job->mappings) अणु
		क्रम (i = 0; i < job->bo_count; i++) अणु
			अगर (!job->mappings[i])
				अवरोध;

			atomic_dec(&job->mappings[i]->obj->gpu_usecount);
			panfrost_gem_mapping_put(job->mappings[i]);
		पूर्ण
		kvमुक्त(job->mappings);
	पूर्ण

	अगर (job->bos) अणु
		क्रम (i = 0; i < job->bo_count; i++)
			drm_gem_object_put(job->bos[i]);

		kvमुक्त(job->bos);
	पूर्ण

	kमुक्त(job);
पूर्ण

व्योम panfrost_job_put(काष्ठा panfrost_job *job)
अणु
	kref_put(&job->refcount, panfrost_job_cleanup);
पूर्ण

अटल व्योम panfrost_job_मुक्त(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा panfrost_job *job = to_panfrost_job(sched_job);

	drm_sched_job_cleanup(sched_job);

	panfrost_job_put(job);
पूर्ण

अटल काष्ठा dma_fence *panfrost_job_dependency(काष्ठा drm_sched_job *sched_job,
						 काष्ठा drm_sched_entity *s_entity)
अणु
	काष्ठा panfrost_job *job = to_panfrost_job(sched_job);
	काष्ठा dma_fence *fence;
	अचिन्हित पूर्णांक i;

	/* Explicit fences */
	क्रम (i = 0; i < job->in_fence_count; i++) अणु
		अगर (job->in_fences[i]) अणु
			fence = job->in_fences[i];
			job->in_fences[i] = शून्य;
			वापस fence;
		पूर्ण
	पूर्ण

	/* Implicit fences, max. one per BO */
	क्रम (i = 0; i < job->bo_count; i++) अणु
		अगर (job->implicit_fences[i]) अणु
			fence = job->implicit_fences[i];
			job->implicit_fences[i] = शून्य;
			वापस fence;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_fence *panfrost_job_run(काष्ठा drm_sched_job *sched_job)
अणु
	काष्ठा panfrost_job *job = to_panfrost_job(sched_job);
	काष्ठा panfrost_device *pfdev = job->pfdev;
	पूर्णांक slot = panfrost_job_get_slot(job);
	काष्ठा dma_fence *fence = शून्य;

	अगर (unlikely(job->base.s_fence->finished.error))
		वापस शून्य;

	pfdev->jobs[slot] = job;

	fence = panfrost_fence_create(pfdev, slot);
	अगर (IS_ERR(fence))
		वापस शून्य;

	अगर (job->करोne_fence)
		dma_fence_put(job->करोne_fence);
	job->करोne_fence = dma_fence_get(fence);

	panfrost_job_hw_submit(job, slot);

	वापस fence;
पूर्ण

व्योम panfrost_job_enable_पूर्णांकerrupts(काष्ठा panfrost_device *pfdev)
अणु
	पूर्णांक j;
	u32 irq_mask = 0;

	क्रम (j = 0; j < NUM_JOB_SLOTS; j++) अणु
		irq_mask |= MK_JS_MASK(j);
	पूर्ण

	job_ग_लिखो(pfdev, JOB_INT_CLEAR, irq_mask);
	job_ग_लिखो(pfdev, JOB_INT_MASK, irq_mask);
पूर्ण

अटल bool panfrost_scheduler_stop(काष्ठा panfrost_queue_state *queue,
				    काष्ठा drm_sched_job *bad)
अणु
	क्रमागत panfrost_queue_status old_status;
	bool stopped = false;

	mutex_lock(&queue->lock);
	old_status = atomic_xchg(&queue->status,
				 PANFROST_QUEUE_STATUS_STOPPED);
	अगर (old_status == PANFROST_QUEUE_STATUS_STOPPED)
		जाओ out;

	WARN_ON(old_status != PANFROST_QUEUE_STATUS_ACTIVE);
	drm_sched_stop(&queue->sched, bad);
	अगर (bad)
		drm_sched_increase_karma(bad);

	stopped = true;

	/*
	 * Set the समयout to max so the समयr करोesn't get started
	 * when we वापस from the समयout handler (restored in
	 * panfrost_scheduler_start()).
	 */
	queue->sched.समयout = MAX_SCHEDULE_TIMEOUT;

out:
	mutex_unlock(&queue->lock);

	वापस stopped;
पूर्ण

अटल व्योम panfrost_scheduler_start(काष्ठा panfrost_queue_state *queue)
अणु
	क्रमागत panfrost_queue_status old_status;

	mutex_lock(&queue->lock);
	old_status = atomic_xchg(&queue->status,
				 PANFROST_QUEUE_STATUS_STARTING);
	WARN_ON(old_status != PANFROST_QUEUE_STATUS_STOPPED);

	/* Restore the original समयout beक्रमe starting the scheduler. */
	queue->sched.समयout = msecs_to_jअगरfies(JOB_TIMEOUT_MS);
	drm_sched_resubmit_jobs(&queue->sched);
	drm_sched_start(&queue->sched, true);
	old_status = atomic_xchg(&queue->status,
				 PANFROST_QUEUE_STATUS_ACTIVE);
	अगर (old_status == PANFROST_QUEUE_STATUS_FAULT_PENDING)
		drm_sched_fault(&queue->sched);

	mutex_unlock(&queue->lock);
पूर्ण

अटल क्रमागत drm_gpu_sched_stat panfrost_job_समयकरोut(काष्ठा drm_sched_job
						     *sched_job)
अणु
	काष्ठा panfrost_job *job = to_panfrost_job(sched_job);
	काष्ठा panfrost_device *pfdev = job->pfdev;
	पूर्णांक js = panfrost_job_get_slot(job);

	/*
	 * If the GPU managed to complete this jobs fence, the समयout is
	 * spurious. Bail out.
	 */
	अगर (dma_fence_is_संकेतed(job->करोne_fence))
		वापस DRM_GPU_SCHED_STAT_NOMINAL;

	dev_err(pfdev->dev, "gpu sched timeout, js=%d, config=0x%x, status=0x%x, head=0x%x, tail=0x%x, sched_job=%p",
		js,
		job_पढ़ो(pfdev, JS_CONFIG(js)),
		job_पढ़ो(pfdev, JS_STATUS(js)),
		job_पढ़ो(pfdev, JS_HEAD_LO(js)),
		job_पढ़ो(pfdev, JS_TAIL_LO(js)),
		sched_job);

	/* Scheduler is alपढ़ोy stopped, nothing to करो. */
	अगर (!panfrost_scheduler_stop(&pfdev->js->queue[js], sched_job))
		वापस DRM_GPU_SCHED_STAT_NOMINAL;

	/* Schedule a reset अगर there's no reset in progress. */
	अगर (!atomic_xchg(&pfdev->reset.pending, 1))
		schedule_work(&pfdev->reset.work);

	वापस DRM_GPU_SCHED_STAT_NOMINAL;
पूर्ण

अटल स्थिर काष्ठा drm_sched_backend_ops panfrost_sched_ops = अणु
	.dependency = panfrost_job_dependency,
	.run_job = panfrost_job_run,
	.समयकरोut_job = panfrost_job_समयकरोut,
	.मुक्त_job = panfrost_job_मुक्त
पूर्ण;

अटल irqवापस_t panfrost_job_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा panfrost_device *pfdev = data;
	u32 status = job_पढ़ो(pfdev, JOB_INT_STAT);
	पूर्णांक j;

	dev_dbg(pfdev->dev, "jobslot irq status=%x\n", status);

	अगर (!status)
		वापस IRQ_NONE;

	pm_runसमय_mark_last_busy(pfdev->dev);

	क्रम (j = 0; status; j++) अणु
		u32 mask = MK_JS_MASK(j);

		अगर (!(status & mask))
			जारी;

		job_ग_लिखो(pfdev, JOB_INT_CLEAR, mask);

		अगर (status & JOB_INT_MASK_ERR(j)) अणु
			क्रमागत panfrost_queue_status old_status;

			job_ग_लिखो(pfdev, JS_COMMAND_NEXT(j), JS_COMMAND_NOP);

			dev_err(pfdev->dev, "js fault, js=%d, status=%s, head=0x%x, tail=0x%x",
				j,
				panfrost_exception_name(pfdev, job_पढ़ो(pfdev, JS_STATUS(j))),
				job_पढ़ो(pfdev, JS_HEAD_LO(j)),
				job_पढ़ो(pfdev, JS_TAIL_LO(j)));

			/*
			 * When the queue is being restarted we करोn't report
			 * faults directly to aव्योम races between the समयout
			 * and reset handlers. panfrost_scheduler_start() will
			 * call drm_sched_fault() after the queue has been
			 * started अगर status == FAULT_PENDING.
			 */
			old_status = atomic_cmpxchg(&pfdev->js->queue[j].status,
						    PANFROST_QUEUE_STATUS_STARTING,
						    PANFROST_QUEUE_STATUS_FAULT_PENDING);
			अगर (old_status == PANFROST_QUEUE_STATUS_ACTIVE)
				drm_sched_fault(&pfdev->js->queue[j].sched);
		पूर्ण

		अगर (status & JOB_INT_MASK_DONE(j)) अणु
			काष्ठा panfrost_job *job;

			spin_lock(&pfdev->js->job_lock);
			job = pfdev->jobs[j];
			/* Only शून्य अगर job समयout occurred */
			अगर (job) अणु
				pfdev->jobs[j] = शून्य;

				panfrost_mmu_as_put(pfdev, &job->file_priv->mmu);
				panfrost_devfreq_record_idle(&pfdev->pfdevfreq);

				dma_fence_संकेत_locked(job->करोne_fence);
				pm_runसमय_put_स्वतःsuspend(pfdev->dev);
			पूर्ण
			spin_unlock(&pfdev->js->job_lock);
		पूर्ण

		status &= ~mask;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम panfrost_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा panfrost_device *pfdev = container_of(work,
						     काष्ठा panfrost_device,
						     reset.work);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	bool cookie;

	cookie = dma_fence_begin_संकेतling();
	क्रम (i = 0; i < NUM_JOB_SLOTS; i++) अणु
		/*
		 * We want pending समयouts to be handled beक्रमe we attempt
		 * to stop the scheduler. If we करोn't करो that and the समयout
		 * handler is in flight, it might have हटाओd the bad job
		 * from the list, and we'll lose this job अगर the reset handler
		 * enters the critical section in panfrost_scheduler_stop()
		 * beक्रमe the समयout handler.
		 *
		 * Timeout is set to MAX_SCHEDULE_TIMEOUT - 1 because we need
		 * something big enough to make sure the समयr will not expire
		 * beक्रमe we manage to stop the scheduler, but we can't use
		 * MAX_SCHEDULE_TIMEOUT because drm_sched_get_cleanup_job()
		 * considers that as 'timer is not running' and will dequeue
		 * the job without making sure the समयout handler is not
		 * running.
		 */
		pfdev->js->queue[i].sched.समयout = MAX_SCHEDULE_TIMEOUT - 1;
		cancel_delayed_work_sync(&pfdev->js->queue[i].sched.work_tdr);
		panfrost_scheduler_stop(&pfdev->js->queue[i], शून्य);
	पूर्ण

	/* All समयrs have been stopped, we can safely reset the pending state. */
	atomic_set(&pfdev->reset.pending, 0);

	spin_lock_irqsave(&pfdev->js->job_lock, flags);
	क्रम (i = 0; i < NUM_JOB_SLOTS; i++) अणु
		अगर (pfdev->jobs[i]) अणु
			pm_runसमय_put_noidle(pfdev->dev);
			panfrost_devfreq_record_idle(&pfdev->pfdevfreq);
			pfdev->jobs[i] = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&pfdev->js->job_lock, flags);

	panfrost_device_reset(pfdev);

	क्रम (i = 0; i < NUM_JOB_SLOTS; i++)
		panfrost_scheduler_start(&pfdev->js->queue[i]);

	dma_fence_end_संकेतling(cookie);
पूर्ण

पूर्णांक panfrost_job_init(काष्ठा panfrost_device *pfdev)
अणु
	काष्ठा panfrost_job_slot *js;
	पूर्णांक ret, j, irq;

	INIT_WORK(&pfdev->reset.work, panfrost_reset);

	pfdev->js = js = devm_kzalloc(pfdev->dev, माप(*js), GFP_KERNEL);
	अगर (!js)
		वापस -ENOMEM;

	spin_lock_init(&js->job_lock);

	irq = platक्रमm_get_irq_byname(to_platक्रमm_device(pfdev->dev), "job");
	अगर (irq <= 0)
		वापस -ENODEV;

	ret = devm_request_irq(pfdev->dev, irq, panfrost_job_irq_handler,
			       IRQF_SHARED, KBUILD_MODNAME "-job", pfdev);
	अगर (ret) अणु
		dev_err(pfdev->dev, "failed to request job irq");
		वापस ret;
	पूर्ण

	क्रम (j = 0; j < NUM_JOB_SLOTS; j++) अणु
		mutex_init(&js->queue[j].lock);

		js->queue[j].fence_context = dma_fence_context_alloc(1);

		ret = drm_sched_init(&js->queue[j].sched,
				     &panfrost_sched_ops,
				     1, 0, msecs_to_jअगरfies(JOB_TIMEOUT_MS),
				     शून्य, "pan_js");
		अगर (ret) अणु
			dev_err(pfdev->dev, "Failed to create scheduler: %d.", ret);
			जाओ err_sched;
		पूर्ण
	पूर्ण

	panfrost_job_enable_पूर्णांकerrupts(pfdev);

	वापस 0;

err_sched:
	क्रम (j--; j >= 0; j--)
		drm_sched_fini(&js->queue[j].sched);

	वापस ret;
पूर्ण

व्योम panfrost_job_fini(काष्ठा panfrost_device *pfdev)
अणु
	काष्ठा panfrost_job_slot *js = pfdev->js;
	पूर्णांक j;

	job_ग_लिखो(pfdev, JOB_INT_MASK, 0);

	क्रम (j = 0; j < NUM_JOB_SLOTS; j++) अणु
		drm_sched_fini(&js->queue[j].sched);
		mutex_destroy(&js->queue[j].lock);
	पूर्ण

पूर्ण

पूर्णांक panfrost_job_खोलो(काष्ठा panfrost_file_priv *panfrost_priv)
अणु
	काष्ठा panfrost_device *pfdev = panfrost_priv->pfdev;
	काष्ठा panfrost_job_slot *js = pfdev->js;
	काष्ठा drm_gpu_scheduler *sched;
	पूर्णांक ret, i;

	क्रम (i = 0; i < NUM_JOB_SLOTS; i++) अणु
		sched = &js->queue[i].sched;
		ret = drm_sched_entity_init(&panfrost_priv->sched_entity[i],
					    DRM_SCHED_PRIORITY_NORMAL, &sched,
					    1, शून्य);
		अगर (WARN_ON(ret))
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

व्योम panfrost_job_बंद(काष्ठा panfrost_file_priv *panfrost_priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_JOB_SLOTS; i++)
		drm_sched_entity_destroy(&panfrost_priv->sched_entity[i]);
पूर्ण

पूर्णांक panfrost_job_is_idle(काष्ठा panfrost_device *pfdev)
अणु
	काष्ठा panfrost_job_slot *js = pfdev->js;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_JOB_SLOTS; i++) अणु
		/* If there are any jobs in the HW queue, we're not idle */
		अगर (atomic_पढ़ो(&js->queue[i].sched.hw_rq_count))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
