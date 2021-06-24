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

/**
 * DOC: Overview
 *
 * The GPU scheduler provides entities which allow userspace to push jobs
 * पूर्णांकo software queues which are then scheduled on a hardware run queue.
 * The software queues have a priority among them. The scheduler selects the entities
 * from the run queue using a FIFO. The scheduler provides dependency handling
 * features among jobs. The driver is supposed to provide callback functions क्रम
 * backend operations to the scheduler like submitting a job to hardware run queue,
 * वापसing the dependencies of a job etc.
 *
 * The organisation of the scheduler is the following:
 *
 * 1. Each hw run queue has one scheduler
 * 2. Each scheduler has multiple run queues with dअगरferent priorities
 *    (e.g., HIGH_HW,HIGH_SW, KERNEL, NORMAL)
 * 3. Each scheduler run queue has a queue of entities to schedule
 * 4. Entities themselves मुख्यtain a queue of jobs that will be scheduled on
 *    the hardware.
 *
 * The jobs in a entity are always scheduled in the order that they were pushed.
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <uapi/linux/sched/types.h>

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/gpu_scheduler.h>
#समावेश <drm/spsc_queue.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "gpu_scheduler_trace.h"

#घोषणा to_drm_sched_job(sched_job)		\
		container_of((sched_job), काष्ठा drm_sched_job, queue_node)

/**
 * drm_sched_rq_init - initialize a given run queue काष्ठा
 *
 * @sched: scheduler instance to associate with this run queue
 * @rq: scheduler run queue
 *
 * Initializes a scheduler runqueue.
 */
अटल व्योम drm_sched_rq_init(काष्ठा drm_gpu_scheduler *sched,
			      काष्ठा drm_sched_rq *rq)
अणु
	spin_lock_init(&rq->lock);
	INIT_LIST_HEAD(&rq->entities);
	rq->current_entity = शून्य;
	rq->sched = sched;
पूर्ण

/**
 * drm_sched_rq_add_entity - add an entity
 *
 * @rq: scheduler run queue
 * @entity: scheduler entity
 *
 * Adds a scheduler entity to the run queue.
 */
व्योम drm_sched_rq_add_entity(काष्ठा drm_sched_rq *rq,
			     काष्ठा drm_sched_entity *entity)
अणु
	अगर (!list_empty(&entity->list))
		वापस;
	spin_lock(&rq->lock);
	atomic_inc(rq->sched->score);
	list_add_tail(&entity->list, &rq->entities);
	spin_unlock(&rq->lock);
पूर्ण

/**
 * drm_sched_rq_हटाओ_entity - हटाओ an entity
 *
 * @rq: scheduler run queue
 * @entity: scheduler entity
 *
 * Removes a scheduler entity from the run queue.
 */
व्योम drm_sched_rq_हटाओ_entity(काष्ठा drm_sched_rq *rq,
				काष्ठा drm_sched_entity *entity)
अणु
	अगर (list_empty(&entity->list))
		वापस;
	spin_lock(&rq->lock);
	atomic_dec(rq->sched->score);
	list_del_init(&entity->list);
	अगर (rq->current_entity == entity)
		rq->current_entity = शून्य;
	spin_unlock(&rq->lock);
पूर्ण

/**
 * drm_sched_rq_select_entity - Select an entity which could provide a job to run
 *
 * @rq: scheduler run queue to check.
 *
 * Try to find a पढ़ोy entity, वापसs शून्य अगर none found.
 */
अटल काष्ठा drm_sched_entity *
drm_sched_rq_select_entity(काष्ठा drm_sched_rq *rq)
अणु
	काष्ठा drm_sched_entity *entity;

	spin_lock(&rq->lock);

	entity = rq->current_entity;
	अगर (entity) अणु
		list_क्रम_each_entry_जारी(entity, &rq->entities, list) अणु
			अगर (drm_sched_entity_is_पढ़ोy(entity)) अणु
				rq->current_entity = entity;
				reinit_completion(&entity->entity_idle);
				spin_unlock(&rq->lock);
				वापस entity;
			पूर्ण
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(entity, &rq->entities, list) अणु

		अगर (drm_sched_entity_is_पढ़ोy(entity)) अणु
			rq->current_entity = entity;
			reinit_completion(&entity->entity_idle);
			spin_unlock(&rq->lock);
			वापस entity;
		पूर्ण

		अगर (entity == rq->current_entity)
			अवरोध;
	पूर्ण

	spin_unlock(&rq->lock);

	वापस शून्य;
पूर्ण

/**
 * drm_sched_job_करोne - complete a job
 * @s_job: poपूर्णांकer to the job which is करोne
 *
 * Finish the job's fence and wake up the worker thपढ़ो.
 */
अटल व्योम drm_sched_job_करोne(काष्ठा drm_sched_job *s_job)
अणु
	काष्ठा drm_sched_fence *s_fence = s_job->s_fence;
	काष्ठा drm_gpu_scheduler *sched = s_fence->sched;

	atomic_dec(&sched->hw_rq_count);
	atomic_dec(sched->score);

	trace_drm_sched_process_job(s_fence);

	dma_fence_get(&s_fence->finished);
	drm_sched_fence_finished(s_fence);
	dma_fence_put(&s_fence->finished);
	wake_up_पूर्णांकerruptible(&sched->wake_up_worker);
पूर्ण

/**
 * drm_sched_job_करोne_cb - the callback क्रम a करोne job
 * @f: fence
 * @cb: fence callbacks
 */
अटल व्योम drm_sched_job_करोne_cb(काष्ठा dma_fence *f, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा drm_sched_job *s_job = container_of(cb, काष्ठा drm_sched_job, cb);

	drm_sched_job_करोne(s_job);
पूर्ण

/**
 * drm_sched_dependency_optimized
 *
 * @fence: the dependency fence
 * @entity: the entity which depends on the above fence
 *
 * Returns true अगर the dependency can be optimized and false otherwise
 */
bool drm_sched_dependency_optimized(काष्ठा dma_fence* fence,
				    काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा drm_gpu_scheduler *sched = entity->rq->sched;
	काष्ठा drm_sched_fence *s_fence;

	अगर (!fence || dma_fence_is_संकेतed(fence))
		वापस false;
	अगर (fence->context == entity->fence_context)
		वापस true;
	s_fence = to_drm_sched_fence(fence);
	अगर (s_fence && s_fence->sched == sched)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(drm_sched_dependency_optimized);

/**
 * drm_sched_start_समयout - start समयout क्रम reset worker
 *
 * @sched: scheduler instance to start the worker क्रम
 *
 * Start the समयout क्रम the given scheduler.
 */
अटल व्योम drm_sched_start_समयout(काष्ठा drm_gpu_scheduler *sched)
अणु
	अगर (sched->समयout != MAX_SCHEDULE_TIMEOUT &&
	    !list_empty(&sched->pending_list))
		schedule_delayed_work(&sched->work_tdr, sched->समयout);
पूर्ण

/**
 * drm_sched_fault - immediately start समयout handler
 *
 * @sched: scheduler where the समयout handling should be started.
 *
 * Start समयout handling immediately when the driver detects a hardware fault.
 */
व्योम drm_sched_fault(काष्ठा drm_gpu_scheduler *sched)
अणु
	mod_delayed_work(प्रणाली_wq, &sched->work_tdr, 0);
पूर्ण
EXPORT_SYMBOL(drm_sched_fault);

/**
 * drm_sched_suspend_समयout - Suspend scheduler job समयout
 *
 * @sched: scheduler instance क्रम which to suspend the समयout
 *
 * Suspend the delayed work समयout क्रम the scheduler. This is करोne by
 * modअगरying the delayed work समयout to an arbitrary large value,
 * MAX_SCHEDULE_TIMEOUT in this हाल.
 *
 * Returns the समयout reमुख्यing
 *
 */
अचिन्हित दीर्घ drm_sched_suspend_समयout(काष्ठा drm_gpu_scheduler *sched)
अणु
	अचिन्हित दीर्घ sched_समयout, now = jअगरfies;

	sched_समयout = sched->work_tdr.समयr.expires;

	/*
	 * Modअगरy the समयout to an arbitrarily large value. This also prevents
	 * the समयout to be restarted when new submissions arrive
	 */
	अगर (mod_delayed_work(प्रणाली_wq, &sched->work_tdr, MAX_SCHEDULE_TIMEOUT)
			&& समय_after(sched_समयout, now))
		वापस sched_समयout - now;
	अन्यथा
		वापस sched->समयout;
पूर्ण
EXPORT_SYMBOL(drm_sched_suspend_समयout);

/**
 * drm_sched_resume_समयout - Resume scheduler job समयout
 *
 * @sched: scheduler instance क्रम which to resume the समयout
 * @reमुख्यing: reमुख्यing समयout
 *
 * Resume the delayed work समयout क्रम the scheduler.
 */
व्योम drm_sched_resume_समयout(काष्ठा drm_gpu_scheduler *sched,
		अचिन्हित दीर्घ reमुख्यing)
अणु
	spin_lock(&sched->job_list_lock);

	अगर (list_empty(&sched->pending_list))
		cancel_delayed_work(&sched->work_tdr);
	अन्यथा
		mod_delayed_work(प्रणाली_wq, &sched->work_tdr, reमुख्यing);

	spin_unlock(&sched->job_list_lock);
पूर्ण
EXPORT_SYMBOL(drm_sched_resume_समयout);

अटल व्योम drm_sched_job_begin(काष्ठा drm_sched_job *s_job)
अणु
	काष्ठा drm_gpu_scheduler *sched = s_job->sched;

	spin_lock(&sched->job_list_lock);
	list_add_tail(&s_job->list, &sched->pending_list);
	drm_sched_start_समयout(sched);
	spin_unlock(&sched->job_list_lock);
पूर्ण

अटल व्योम drm_sched_job_समयकरोut(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_gpu_scheduler *sched;
	काष्ठा drm_sched_job *job;

	sched = container_of(work, काष्ठा drm_gpu_scheduler, work_tdr.work);

	/* Protects against concurrent deletion in drm_sched_get_cleanup_job */
	spin_lock(&sched->job_list_lock);
	job = list_first_entry_or_null(&sched->pending_list,
				       काष्ठा drm_sched_job, list);

	अगर (job) अणु
		/*
		 * Remove the bad job so it cannot be मुक्तd by concurrent
		 * drm_sched_cleanup_jobs. It will be reinserted back after sched->thपढ़ो
		 * is parked at which poपूर्णांक it's safe.
		 */
		list_del_init(&job->list);
		spin_unlock(&sched->job_list_lock);

		job->sched->ops->समयकरोut_job(job);

		/*
		 * Guilty job did complete and hence needs to be manually हटाओd
		 * See drm_sched_stop करोc.
		 */
		अगर (sched->मुक्त_guilty) अणु
			job->sched->ops->मुक्त_job(job);
			sched->मुक्त_guilty = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock(&sched->job_list_lock);
	पूर्ण

	spin_lock(&sched->job_list_lock);
	drm_sched_start_समयout(sched);
	spin_unlock(&sched->job_list_lock);
पूर्ण

 /**
  * drm_sched_increase_karma - Update sched_entity guilty flag
  *
  * @bad: The job guilty of समय out
  *
  * Increment on every hang caused by the 'bad' job. If this exceeds the hang
  * limit of the scheduler then the respective sched entity is marked guilty and
  * jobs from it will not be scheduled further
  */
व्योम drm_sched_increase_karma(काष्ठा drm_sched_job *bad)
अणु
	drm_sched_increase_karma_ext(bad, 1);
पूर्ण
EXPORT_SYMBOL(drm_sched_increase_karma);

व्योम drm_sched_reset_karma(काष्ठा drm_sched_job *bad)
अणु
	drm_sched_increase_karma_ext(bad, 0);
पूर्ण
EXPORT_SYMBOL(drm_sched_reset_karma);

/**
 * drm_sched_stop - stop the scheduler
 *
 * @sched: scheduler instance
 * @bad: job which caused the समय out
 *
 * Stop the scheduler and also हटाओs and मुक्तs all completed jobs.
 * Note: bad job will not be मुक्तd as it might be used later and so it's
 * callers responsibility to release it manually अगर it's not part of the
 * pending list any more.
 *
 */
व्योम drm_sched_stop(काष्ठा drm_gpu_scheduler *sched, काष्ठा drm_sched_job *bad)
अणु
	काष्ठा drm_sched_job *s_job, *पंचांगp;

	kthपढ़ो_park(sched->thपढ़ो);

	/*
	 * Reinsert back the bad job here - now it's safe as
	 * drm_sched_get_cleanup_job cannot race against us and release the
	 * bad job at this poपूर्णांक - we parked (रुकोed क्रम) any in progress
	 * (earlier) cleanups and drm_sched_get_cleanup_job will not be called
	 * now until the scheduler thपढ़ो is unparked.
	 */
	अगर (bad && bad->sched == sched)
		/*
		 * Add at the head of the queue to reflect it was the earliest
		 * job extracted.
		 */
		list_add(&bad->list, &sched->pending_list);

	/*
	 * Iterate the job list from later to  earlier one and either deactive
	 * their HW callbacks or हटाओ them from pending list अगर they alपढ़ोy
	 * संकेतed.
	 * This iteration is thपढ़ो safe as sched thपढ़ो is stopped.
	 */
	list_क्रम_each_entry_safe_reverse(s_job, पंचांगp, &sched->pending_list,
					 list) अणु
		अगर (s_job->s_fence->parent &&
		    dma_fence_हटाओ_callback(s_job->s_fence->parent,
					      &s_job->cb)) अणु
			atomic_dec(&sched->hw_rq_count);
		पूर्ण अन्यथा अणु
			/*
			 * हटाओ job from pending_list.
			 * Locking here is क्रम concurrent resume समयout
			 */
			spin_lock(&sched->job_list_lock);
			list_del_init(&s_job->list);
			spin_unlock(&sched->job_list_lock);

			/*
			 * Wait क्रम job's HW fence callback to finish using s_job
			 * beक्रमe releasing it.
			 *
			 * Job is still alive so fence refcount at least 1
			 */
			dma_fence_रुको(&s_job->s_fence->finished, false);

			/*
			 * We must keep bad job alive क्रम later use during
			 * recovery by some of the drivers but leave a hपूर्णांक
			 * that the guilty job must be released.
			 */
			अगर (bad != s_job)
				sched->ops->मुक्त_job(s_job);
			अन्यथा
				sched->मुक्त_guilty = true;
		पूर्ण
	पूर्ण

	/*
	 * Stop pending समयr in flight as we rearm it in  drm_sched_start. This
	 * aव्योमs the pending समयout work in progress to fire right away after
	 * this TDR finished and beक्रमe the newly restarted jobs had a
	 * chance to complete.
	 */
	cancel_delayed_work(&sched->work_tdr);
पूर्ण

EXPORT_SYMBOL(drm_sched_stop);

/**
 * drm_sched_start - recover jobs after a reset
 *
 * @sched: scheduler instance
 * @full_recovery: proceed with complete sched restart
 *
 */
व्योम drm_sched_start(काष्ठा drm_gpu_scheduler *sched, bool full_recovery)
अणु
	काष्ठा drm_sched_job *s_job, *पंचांगp;
	पूर्णांक r;

	/*
	 * Locking the list is not required here as the sched thपढ़ो is parked
	 * so no new jobs are being inserted or हटाओd. Also concurrent
	 * GPU recovers can't run in parallel.
	 */
	list_क्रम_each_entry_safe(s_job, पंचांगp, &sched->pending_list, list) अणु
		काष्ठा dma_fence *fence = s_job->s_fence->parent;

		atomic_inc(&sched->hw_rq_count);

		अगर (!full_recovery)
			जारी;

		अगर (fence) अणु
			r = dma_fence_add_callback(fence, &s_job->cb,
						   drm_sched_job_करोne_cb);
			अगर (r == -ENOENT)
				drm_sched_job_करोne(s_job);
			अन्यथा अगर (r)
				DRM_ERROR("fence add callback failed (%d)\n",
					  r);
		पूर्ण अन्यथा
			drm_sched_job_करोne(s_job);
	पूर्ण

	अगर (full_recovery) अणु
		spin_lock(&sched->job_list_lock);
		drm_sched_start_समयout(sched);
		spin_unlock(&sched->job_list_lock);
	पूर्ण

	kthपढ़ो_unpark(sched->thपढ़ो);
पूर्ण
EXPORT_SYMBOL(drm_sched_start);

/**
 * drm_sched_resubmit_jobs - helper to relaunch jobs from the pending list
 *
 * @sched: scheduler instance
 *
 */
व्योम drm_sched_resubmit_jobs(काष्ठा drm_gpu_scheduler *sched)
अणु
	drm_sched_resubmit_jobs_ext(sched, पूर्णांक_उच्च);
पूर्ण
EXPORT_SYMBOL(drm_sched_resubmit_jobs);

/**
 * drm_sched_resubmit_jobs_ext - helper to relunch certain number of jobs from mirror ring list
 *
 * @sched: scheduler instance
 * @max: job numbers to relaunch
 *
 */
व्योम drm_sched_resubmit_jobs_ext(काष्ठा drm_gpu_scheduler *sched, पूर्णांक max)
अणु
	काष्ठा drm_sched_job *s_job, *पंचांगp;
	uपूर्णांक64_t guilty_context;
	bool found_guilty = false;
	काष्ठा dma_fence *fence;
	पूर्णांक i = 0;

	list_क्रम_each_entry_safe(s_job, पंचांगp, &sched->pending_list, list) अणु
		काष्ठा drm_sched_fence *s_fence = s_job->s_fence;

		अगर (i >= max)
			अवरोध;

		अगर (!found_guilty && atomic_पढ़ो(&s_job->karma) > sched->hang_limit) अणु
			found_guilty = true;
			guilty_context = s_job->s_fence->scheduled.context;
		पूर्ण

		अगर (found_guilty && s_job->s_fence->scheduled.context == guilty_context)
			dma_fence_set_error(&s_fence->finished, -ECANCELED);

		dma_fence_put(s_job->s_fence->parent);
		fence = sched->ops->run_job(s_job);
		i++;

		अगर (IS_ERR_OR_शून्य(fence)) अणु
			अगर (IS_ERR(fence))
				dma_fence_set_error(&s_fence->finished, PTR_ERR(fence));

			s_job->s_fence->parent = शून्य;
		पूर्ण अन्यथा अणु
			s_job->s_fence->parent = fence;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_sched_resubmit_jobs_ext);

/**
 * drm_sched_job_init - init a scheduler job
 *
 * @job: scheduler job to init
 * @entity: scheduler entity to use
 * @owner: job owner क्रम debugging
 *
 * Refer to drm_sched_entity_push_job() करोcumentation
 * क्रम locking considerations.
 *
 * Returns 0 क्रम success, negative error code otherwise.
 */
पूर्णांक drm_sched_job_init(काष्ठा drm_sched_job *job,
		       काष्ठा drm_sched_entity *entity,
		       व्योम *owner)
अणु
	काष्ठा drm_gpu_scheduler *sched;

	drm_sched_entity_select_rq(entity);
	अगर (!entity->rq)
		वापस -ENOENT;

	sched = entity->rq->sched;

	job->sched = sched;
	job->entity = entity;
	job->s_priority = entity->rq - sched->sched_rq;
	job->s_fence = drm_sched_fence_create(entity, owner);
	अगर (!job->s_fence)
		वापस -ENOMEM;
	job->id = atomic64_inc_वापस(&sched->job_id_count);

	INIT_LIST_HEAD(&job->list);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_sched_job_init);

/**
 * drm_sched_job_cleanup - clean up scheduler job resources
 *
 * @job: scheduler job to clean up
 */
व्योम drm_sched_job_cleanup(काष्ठा drm_sched_job *job)
अणु
	dma_fence_put(&job->s_fence->finished);
	job->s_fence = शून्य;
पूर्ण
EXPORT_SYMBOL(drm_sched_job_cleanup);

/**
 * drm_sched_पढ़ोy - is the scheduler पढ़ोy
 *
 * @sched: scheduler instance
 *
 * Return true अगर we can push more jobs to the hw, otherwise false.
 */
अटल bool drm_sched_पढ़ोy(काष्ठा drm_gpu_scheduler *sched)
अणु
	वापस atomic_पढ़ो(&sched->hw_rq_count) <
		sched->hw_submission_limit;
पूर्ण

/**
 * drm_sched_wakeup - Wake up the scheduler when it is पढ़ोy
 *
 * @sched: scheduler instance
 *
 */
व्योम drm_sched_wakeup(काष्ठा drm_gpu_scheduler *sched)
अणु
	अगर (drm_sched_पढ़ोy(sched))
		wake_up_पूर्णांकerruptible(&sched->wake_up_worker);
पूर्ण

/**
 * drm_sched_select_entity - Select next entity to process
 *
 * @sched: scheduler instance
 *
 * Returns the entity to process or शून्य अगर none are found.
 */
अटल काष्ठा drm_sched_entity *
drm_sched_select_entity(काष्ठा drm_gpu_scheduler *sched)
अणु
	काष्ठा drm_sched_entity *entity;
	पूर्णांक i;

	अगर (!drm_sched_पढ़ोy(sched))
		वापस शून्य;

	/* Kernel run queue has higher priority than normal run queue*/
	क्रम (i = DRM_SCHED_PRIORITY_COUNT - 1; i >= DRM_SCHED_PRIORITY_MIN; i--) अणु
		entity = drm_sched_rq_select_entity(&sched->sched_rq[i]);
		अगर (entity)
			अवरोध;
	पूर्ण

	वापस entity;
पूर्ण

/**
 * drm_sched_get_cleanup_job - fetch the next finished job to be destroyed
 *
 * @sched: scheduler instance
 *
 * Returns the next finished job from the pending list (अगर there is one)
 * पढ़ोy क्रम it to be destroyed.
 */
अटल काष्ठा drm_sched_job *
drm_sched_get_cleanup_job(काष्ठा drm_gpu_scheduler *sched)
अणु
	काष्ठा drm_sched_job *job;

	/*
	 * Don't destroy jobs जबतक the समयout worker is running  OR thपढ़ो
	 * is being parked and hence assumed to not touch pending_list
	 */
	अगर ((sched->समयout != MAX_SCHEDULE_TIMEOUT &&
	    !cancel_delayed_work(&sched->work_tdr)) ||
	    kthपढ़ो_should_park())
		वापस शून्य;

	spin_lock(&sched->job_list_lock);

	job = list_first_entry_or_null(&sched->pending_list,
				       काष्ठा drm_sched_job, list);

	अगर (job && dma_fence_is_संकेतed(&job->s_fence->finished)) अणु
		/* हटाओ job from pending_list */
		list_del_init(&job->list);
	पूर्ण अन्यथा अणु
		job = शून्य;
		/* queue समयout क्रम next job */
		drm_sched_start_समयout(sched);
	पूर्ण

	spin_unlock(&sched->job_list_lock);

	वापस job;
पूर्ण

/**
 * drm_sched_pick_best - Get a drm sched from a sched_list with the least load
 * @sched_list: list of drm_gpu_schedulers
 * @num_sched_list: number of drm_gpu_schedulers in the sched_list
 *
 * Returns poपूर्णांकer of the sched with the least load or शून्य अगर none of the
 * drm_gpu_schedulers are पढ़ोy
 */
काष्ठा drm_gpu_scheduler *
drm_sched_pick_best(काष्ठा drm_gpu_scheduler **sched_list,
		     अचिन्हित पूर्णांक num_sched_list)
अणु
	काष्ठा drm_gpu_scheduler *sched, *picked_sched = शून्य;
	पूर्णांक i;
	अचिन्हित पूर्णांक min_score = अच_पूर्णांक_उच्च, num_score;

	क्रम (i = 0; i < num_sched_list; ++i) अणु
		sched = sched_list[i];

		अगर (!sched->पढ़ोy) अणु
			DRM_WARN("scheduler %s is not ready, skipping",
				 sched->name);
			जारी;
		पूर्ण

		num_score = atomic_पढ़ो(sched->score);
		अगर (num_score < min_score) अणु
			min_score = num_score;
			picked_sched = sched;
		पूर्ण
	पूर्ण

	वापस picked_sched;
पूर्ण
EXPORT_SYMBOL(drm_sched_pick_best);

/**
 * drm_sched_blocked - check अगर the scheduler is blocked
 *
 * @sched: scheduler instance
 *
 * Returns true अगर blocked, otherwise false.
 */
अटल bool drm_sched_blocked(काष्ठा drm_gpu_scheduler *sched)
अणु
	अगर (kthपढ़ो_should_park()) अणु
		kthपढ़ो_parkme();
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * drm_sched_मुख्य - मुख्य scheduler thपढ़ो
 *
 * @param: scheduler instance
 *
 * Returns 0.
 */
अटल पूर्णांक drm_sched_मुख्य(व्योम *param)
अणु
	काष्ठा drm_gpu_scheduler *sched = (काष्ठा drm_gpu_scheduler *)param;
	पूर्णांक r;

	sched_set_fअगरo_low(current);

	जबतक (!kthपढ़ो_should_stop()) अणु
		काष्ठा drm_sched_entity *entity = शून्य;
		काष्ठा drm_sched_fence *s_fence;
		काष्ठा drm_sched_job *sched_job;
		काष्ठा dma_fence *fence;
		काष्ठा drm_sched_job *cleanup_job = शून्य;

		रुको_event_पूर्णांकerruptible(sched->wake_up_worker,
					 (cleanup_job = drm_sched_get_cleanup_job(sched)) ||
					 (!drm_sched_blocked(sched) &&
					  (entity = drm_sched_select_entity(sched))) ||
					 kthपढ़ो_should_stop());

		अगर (cleanup_job) अणु
			sched->ops->मुक्त_job(cleanup_job);
			/* queue समयout क्रम next job */
			drm_sched_start_समयout(sched);
		पूर्ण

		अगर (!entity)
			जारी;

		sched_job = drm_sched_entity_pop_job(entity);

		complete(&entity->entity_idle);

		अगर (!sched_job)
			जारी;

		s_fence = sched_job->s_fence;

		atomic_inc(&sched->hw_rq_count);
		drm_sched_job_begin(sched_job);

		trace_drm_run_job(sched_job, entity);
		fence = sched->ops->run_job(sched_job);
		drm_sched_fence_scheduled(s_fence);

		अगर (!IS_ERR_OR_शून्य(fence)) अणु
			s_fence->parent = dma_fence_get(fence);
			r = dma_fence_add_callback(fence, &sched_job->cb,
						   drm_sched_job_करोne_cb);
			अगर (r == -ENOENT)
				drm_sched_job_करोne(sched_job);
			अन्यथा अगर (r)
				DRM_ERROR("fence add callback failed (%d)\n",
					  r);
			dma_fence_put(fence);
		पूर्ण अन्यथा अणु
			अगर (IS_ERR(fence))
				dma_fence_set_error(&s_fence->finished, PTR_ERR(fence));

			drm_sched_job_करोne(sched_job);
		पूर्ण

		wake_up(&sched->job_scheduled);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * drm_sched_init - Init a gpu scheduler instance
 *
 * @sched: scheduler instance
 * @ops: backend operations क्रम this scheduler
 * @hw_submission: number of hw submissions that can be in flight
 * @hang_limit: number of बार to allow a job to hang beक्रमe dropping it
 * @समयout: समयout value in jअगरfies क्रम the scheduler
 * @score: optional score atomic shared with other schedulers
 * @name: name used क्रम debugging
 *
 * Return 0 on success, otherwise error code.
 */
पूर्णांक drm_sched_init(काष्ठा drm_gpu_scheduler *sched,
		   स्थिर काष्ठा drm_sched_backend_ops *ops,
		   अचिन्हित hw_submission, अचिन्हित hang_limit, दीर्घ समयout,
		   atomic_t *score, स्थिर अक्षर *name)
अणु
	पूर्णांक i, ret;
	sched->ops = ops;
	sched->hw_submission_limit = hw_submission;
	sched->name = name;
	sched->समयout = समयout;
	sched->hang_limit = hang_limit;
	sched->score = score ? score : &sched->_score;
	क्रम (i = DRM_SCHED_PRIORITY_MIN; i < DRM_SCHED_PRIORITY_COUNT; i++)
		drm_sched_rq_init(sched, &sched->sched_rq[i]);

	init_रुकोqueue_head(&sched->wake_up_worker);
	init_रुकोqueue_head(&sched->job_scheduled);
	INIT_LIST_HEAD(&sched->pending_list);
	spin_lock_init(&sched->job_list_lock);
	atomic_set(&sched->hw_rq_count, 0);
	INIT_DELAYED_WORK(&sched->work_tdr, drm_sched_job_समयकरोut);
	atomic_set(&sched->_score, 0);
	atomic64_set(&sched->job_id_count, 0);

	/* Each scheduler will run on a seperate kernel thपढ़ो */
	sched->thपढ़ो = kthपढ़ो_run(drm_sched_मुख्य, sched, sched->name);
	अगर (IS_ERR(sched->thपढ़ो)) अणु
		ret = PTR_ERR(sched->thपढ़ो);
		sched->thपढ़ो = शून्य;
		DRM_ERROR("Failed to create scheduler for %s.\n", name);
		वापस ret;
	पूर्ण

	sched->पढ़ोy = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_sched_init);

/**
 * drm_sched_fini - Destroy a gpu scheduler
 *
 * @sched: scheduler instance
 *
 * Tears करोwn and cleans up the scheduler.
 */
व्योम drm_sched_fini(काष्ठा drm_gpu_scheduler *sched)
अणु
	अगर (sched->thपढ़ो)
		kthपढ़ो_stop(sched->thपढ़ो);

	/* Confirm no work left behind accessing device काष्ठाures */
	cancel_delayed_work_sync(&sched->work_tdr);

	sched->पढ़ोy = false;
पूर्ण
EXPORT_SYMBOL(drm_sched_fini);

/**
 * drm_sched_increase_karma_ext - Update sched_entity guilty flag
 *
 * @bad: The job guilty of समय out
 * @type: type क्रम increase/reset karma
 *
 */
व्योम drm_sched_increase_karma_ext(काष्ठा drm_sched_job *bad, पूर्णांक type)
अणु
	पूर्णांक i;
	काष्ठा drm_sched_entity *पंचांगp;
	काष्ठा drm_sched_entity *entity;
	काष्ठा drm_gpu_scheduler *sched = bad->sched;

	/* करोn't change @bad's karma if it's from KERNEL RQ,
	 * because someबार GPU hang would cause kernel jobs (like VM updating jobs)
	 * corrupt but keep in mind that kernel jobs always considered good.
	 */
	अगर (bad->s_priority != DRM_SCHED_PRIORITY_KERNEL) अणु
		अगर (type == 0)
			atomic_set(&bad->karma, 0);
		अन्यथा अगर (type == 1)
			atomic_inc(&bad->karma);

		क्रम (i = DRM_SCHED_PRIORITY_MIN; i < DRM_SCHED_PRIORITY_KERNEL;
		     i++) अणु
			काष्ठा drm_sched_rq *rq = &sched->sched_rq[i];

			spin_lock(&rq->lock);
			list_क्रम_each_entry_safe(entity, पंचांगp, &rq->entities, list) अणु
				अगर (bad->s_fence->scheduled.context ==
				    entity->fence_context) अणु
					अगर (entity->guilty)
						atomic_set(entity->guilty, type);
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock(&rq->lock);
			अगर (&entity->list != &rq->entities)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_sched_increase_karma_ext);
