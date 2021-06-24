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
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/gpu_scheduler.h>

#समावेश "gpu_scheduler_trace.h"

#घोषणा to_drm_sched_job(sched_job)		\
		container_of((sched_job), काष्ठा drm_sched_job, queue_node)

/**
 * drm_sched_entity_init - Init a context entity used by scheduler when
 * submit to HW ring.
 *
 * @entity: scheduler entity to init
 * @priority: priority of the entity
 * @sched_list: the list of drm scheds on which jobs from this
 *           entity can be submitted
 * @num_sched_list: number of drm sched in sched_list
 * @guilty: atomic_t set to 1 when a job on this queue
 *          is found to be guilty causing a समयout
 *
 * Note: the sched_list should have at least one element to schedule
 *       the entity
 *
 * Returns 0 on success or a negative error code on failure.
 */
पूर्णांक drm_sched_entity_init(काष्ठा drm_sched_entity *entity,
			  क्रमागत drm_sched_priority priority,
			  काष्ठा drm_gpu_scheduler **sched_list,
			  अचिन्हित पूर्णांक num_sched_list,
			  atomic_t *guilty)
अणु
	अगर (!(entity && sched_list && (num_sched_list == 0 || sched_list[0])))
		वापस -EINVAL;

	स_रखो(entity, 0, माप(काष्ठा drm_sched_entity));
	INIT_LIST_HEAD(&entity->list);
	entity->rq = शून्य;
	entity->guilty = guilty;
	entity->num_sched_list = num_sched_list;
	entity->priority = priority;
	entity->sched_list = num_sched_list > 1 ? sched_list : शून्य;
	entity->last_scheduled = शून्य;

	अगर(num_sched_list)
		entity->rq = &sched_list[0]->sched_rq[entity->priority];

	init_completion(&entity->entity_idle);

	/* We start in an idle state. */
	complete(&entity->entity_idle);

	spin_lock_init(&entity->rq_lock);
	spsc_queue_init(&entity->job_queue);

	atomic_set(&entity->fence_seq, 0);
	entity->fence_context = dma_fence_context_alloc(2);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_sched_entity_init);

/**
 * drm_sched_entity_modअगरy_sched - Modअगरy sched of an entity
 * @entity: scheduler entity to init
 * @sched_list: the list of new drm scheds which will replace
 *		 existing entity->sched_list
 * @num_sched_list: number of drm sched in sched_list
 */
व्योम drm_sched_entity_modअगरy_sched(काष्ठा drm_sched_entity *entity,
				    काष्ठा drm_gpu_scheduler **sched_list,
				    अचिन्हित पूर्णांक num_sched_list)
अणु
	WARN_ON(!num_sched_list || !sched_list);

	entity->sched_list = sched_list;
	entity->num_sched_list = num_sched_list;
पूर्ण
EXPORT_SYMBOL(drm_sched_entity_modअगरy_sched);

/**
 * drm_sched_entity_is_idle - Check अगर entity is idle
 *
 * @entity: scheduler entity
 *
 * Returns true अगर the entity करोes not have any unscheduled jobs.
 */
अटल bool drm_sched_entity_is_idle(काष्ठा drm_sched_entity *entity)
अणु
	rmb(); /* क्रम list_empty to work without lock */

	अगर (list_empty(&entity->list) ||
	    spsc_queue_count(&entity->job_queue) == 0)
		वापस true;

	वापस false;
पूर्ण

/**
 * drm_sched_entity_is_पढ़ोy - Check अगर entity is पढ़ोy
 *
 * @entity: scheduler entity
 *
 * Return true अगर entity could provide a job.
 */
bool drm_sched_entity_is_पढ़ोy(काष्ठा drm_sched_entity *entity)
अणु
	अगर (spsc_queue_peek(&entity->job_queue) == शून्य)
		वापस false;

	अगर (READ_ONCE(entity->dependency))
		वापस false;

	वापस true;
पूर्ण

/**
 * drm_sched_entity_flush - Flush a context entity
 *
 * @entity: scheduler entity
 * @समयout: समय to रुको in क्रम Q to become empty in jअगरfies.
 *
 * Splitting drm_sched_entity_fini() पूर्णांकo two functions, The first one करोes the
 * रुकोing, हटाओs the entity from the runqueue and वापसs an error when the
 * process was समाप्तed.
 *
 * Returns the reमुख्यing समय in jअगरfies left from the input समयout
 */
दीर्घ drm_sched_entity_flush(काष्ठा drm_sched_entity *entity, दीर्घ समयout)
अणु
	काष्ठा drm_gpu_scheduler *sched;
	काष्ठा task_काष्ठा *last_user;
	दीर्घ ret = समयout;

	अगर (!entity->rq)
		वापस 0;

	sched = entity->rq->sched;
	/**
	 * The client will not queue more IBs during this fini, consume existing
	 * queued IBs or discard them on SIGKILL
	 */
	अगर (current->flags & PF_EXITING) अणु
		अगर (समयout)
			ret = रुको_event_समयout(
					sched->job_scheduled,
					drm_sched_entity_is_idle(entity),
					समयout);
	पूर्ण अन्यथा अणु
		रुको_event_समाप्तable(sched->job_scheduled,
				    drm_sched_entity_is_idle(entity));
	पूर्ण

	/* For समाप्तed process disable any more IBs enqueue right now */
	last_user = cmpxchg(&entity->last_user, current->group_leader, शून्य);
	अगर ((!last_user || last_user == current->group_leader) &&
	    (current->flags & PF_EXITING) && (current->निकास_code == SIGKILL)) अणु
		spin_lock(&entity->rq_lock);
		entity->stopped = true;
		drm_sched_rq_हटाओ_entity(entity->rq, entity);
		spin_unlock(&entity->rq_lock);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_sched_entity_flush);

/**
 * drm_sched_entity_समाप्त_jobs - helper क्रम drm_sched_entity_समाप्त_jobs
 *
 * @f: संकेतed fence
 * @cb: our callback काष्ठाure
 *
 * Signal the scheduler finished fence when the entity in question is समाप्तed.
 */
अटल व्योम drm_sched_entity_समाप्त_jobs_cb(काष्ठा dma_fence *f,
					  काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा drm_sched_job *job = container_of(cb, काष्ठा drm_sched_job,
						 finish_cb);

	drm_sched_fence_finished(job->s_fence);
	WARN_ON(job->s_fence->parent);
	job->sched->ops->मुक्त_job(job);
पूर्ण

/**
 * drm_sched_entity_समाप्त_jobs - Make sure all reमुख्यing jobs are समाप्तed
 *
 * @entity: entity which is cleaned up
 *
 * Makes sure that all reमुख्यing jobs in an entity are समाप्तed beक्रमe it is
 * destroyed.
 */
अटल व्योम drm_sched_entity_समाप्त_jobs(काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा drm_sched_job *job;
	पूर्णांक r;

	जबतक ((job = to_drm_sched_job(spsc_queue_pop(&entity->job_queue)))) अणु
		काष्ठा drm_sched_fence *s_fence = job->s_fence;

		drm_sched_fence_scheduled(s_fence);
		dma_fence_set_error(&s_fence->finished, -ESRCH);

		/*
		 * When pipe is hanged by older entity, new entity might
		 * not even have chance to submit it's first job to HW
		 * and so entity->last_scheduled will reमुख्य शून्य
		 */
		अगर (!entity->last_scheduled) अणु
			drm_sched_entity_समाप्त_jobs_cb(शून्य, &job->finish_cb);
			जारी;
		पूर्ण

		r = dma_fence_add_callback(entity->last_scheduled,
					   &job->finish_cb,
					   drm_sched_entity_समाप्त_jobs_cb);
		अगर (r == -ENOENT)
			drm_sched_entity_समाप्त_jobs_cb(शून्य, &job->finish_cb);
		अन्यथा अगर (r)
			DRM_ERROR("fence add callback failed (%d)\n", r);
	पूर्ण
पूर्ण

/**
 * drm_sched_entity_cleanup - Destroy a context entity
 *
 * @entity: scheduler entity
 *
 * This should be called after @drm_sched_entity_करो_release. It goes over the
 * entity and संकेतs all jobs with an error code अगर the process was समाप्तed.
 *
 */
व्योम drm_sched_entity_fini(काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा drm_gpu_scheduler *sched = शून्य;

	अगर (entity->rq) अणु
		sched = entity->rq->sched;
		drm_sched_rq_हटाओ_entity(entity->rq, entity);
	पूर्ण

	/* Consumption of existing IBs wasn't completed. Forcefully
	 * हटाओ them here.
	 */
	अगर (spsc_queue_count(&entity->job_queue)) अणु
		अगर (sched) अणु
			/*
			 * Wait क्रम thपढ़ो to idle to make sure it isn't processing
			 * this entity.
			 */
			रुको_क्रम_completion(&entity->entity_idle);

		पूर्ण
		अगर (entity->dependency) अणु
			dma_fence_हटाओ_callback(entity->dependency,
						  &entity->cb);
			dma_fence_put(entity->dependency);
			entity->dependency = शून्य;
		पूर्ण

		drm_sched_entity_समाप्त_jobs(entity);
	पूर्ण

	dma_fence_put(entity->last_scheduled);
	entity->last_scheduled = शून्य;
पूर्ण
EXPORT_SYMBOL(drm_sched_entity_fini);

/**
 * drm_sched_entity_fini - Destroy a context entity
 *
 * @entity: scheduler entity
 *
 * Calls drm_sched_entity_करो_release() and drm_sched_entity_cleanup()
 */
व्योम drm_sched_entity_destroy(काष्ठा drm_sched_entity *entity)
अणु
	drm_sched_entity_flush(entity, MAX_WAIT_SCHED_ENTITY_Q_EMPTY);
	drm_sched_entity_fini(entity);
पूर्ण
EXPORT_SYMBOL(drm_sched_entity_destroy);

/*
 * drm_sched_entity_clear_dep - callback to clear the entities dependency
 */
अटल व्योम drm_sched_entity_clear_dep(काष्ठा dma_fence *f,
				       काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा drm_sched_entity *entity =
		container_of(cb, काष्ठा drm_sched_entity, cb);

	entity->dependency = शून्य;
	dma_fence_put(f);
पूर्ण

/*
 * drm_sched_entity_clear_dep - callback to clear the entities dependency and
 * wake up scheduler
 */
अटल व्योम drm_sched_entity_wakeup(काष्ठा dma_fence *f,
				    काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा drm_sched_entity *entity =
		container_of(cb, काष्ठा drm_sched_entity, cb);

	drm_sched_entity_clear_dep(f, cb);
	drm_sched_wakeup(entity->rq->sched);
पूर्ण

/**
 * drm_sched_entity_set_priority - Sets priority of the entity
 *
 * @entity: scheduler entity
 * @priority: scheduler priority
 *
 * Update the priority of runqueus used क्रम the entity.
 */
व्योम drm_sched_entity_set_priority(काष्ठा drm_sched_entity *entity,
				   क्रमागत drm_sched_priority priority)
अणु
	spin_lock(&entity->rq_lock);
	entity->priority = priority;
	spin_unlock(&entity->rq_lock);
पूर्ण
EXPORT_SYMBOL(drm_sched_entity_set_priority);

/**
 * drm_sched_entity_add_dependency_cb - add callback क्रम the entities dependency
 *
 * @entity: entity with dependency
 *
 * Add a callback to the current dependency of the entity to wake up the
 * scheduler when the entity becomes available.
 */
अटल bool drm_sched_entity_add_dependency_cb(काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा drm_gpu_scheduler *sched = entity->rq->sched;
	काष्ठा dma_fence *fence = entity->dependency;
	काष्ठा drm_sched_fence *s_fence;

	अगर (fence->context == entity->fence_context ||
	    fence->context == entity->fence_context + 1) अणु
		/*
		 * Fence is a scheduled/finished fence from a job
		 * which beदीर्घs to the same entity, we can ignore
		 * fences from ourself
		 */
		dma_fence_put(entity->dependency);
		वापस false;
	पूर्ण

	s_fence = to_drm_sched_fence(fence);
	अगर (s_fence && s_fence->sched == sched) अणु

		/*
		 * Fence is from the same scheduler, only need to रुको क्रम
		 * it to be scheduled
		 */
		fence = dma_fence_get(&s_fence->scheduled);
		dma_fence_put(entity->dependency);
		entity->dependency = fence;
		अगर (!dma_fence_add_callback(fence, &entity->cb,
					    drm_sched_entity_clear_dep))
			वापस true;

		/* Ignore it when it is alपढ़ोy scheduled */
		dma_fence_put(fence);
		वापस false;
	पूर्ण

	अगर (!dma_fence_add_callback(entity->dependency, &entity->cb,
				    drm_sched_entity_wakeup))
		वापस true;

	dma_fence_put(entity->dependency);
	वापस false;
पूर्ण

/**
 * drm_sched_entity_pop_job - get a पढ़ोy to be scheduled job from the entity
 *
 * @entity: entity to get the job from
 *
 * Process all dependencies and try to get one job from the entities queue.
 */
काष्ठा drm_sched_job *drm_sched_entity_pop_job(काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा drm_gpu_scheduler *sched = entity->rq->sched;
	काष्ठा drm_sched_job *sched_job;

	sched_job = to_drm_sched_job(spsc_queue_peek(&entity->job_queue));
	अगर (!sched_job)
		वापस शून्य;

	जबतक ((entity->dependency =
			sched->ops->dependency(sched_job, entity))) अणु
		trace_drm_sched_job_रुको_dep(sched_job, entity->dependency);

		अगर (drm_sched_entity_add_dependency_cb(entity))
			वापस शून्य;
	पूर्ण

	/* skip jobs from entity that marked guilty */
	अगर (entity->guilty && atomic_पढ़ो(entity->guilty))
		dma_fence_set_error(&sched_job->s_fence->finished, -ECANCELED);

	dma_fence_put(entity->last_scheduled);
	entity->last_scheduled = dma_fence_get(&sched_job->s_fence->finished);

	spsc_queue_pop(&entity->job_queue);
	वापस sched_job;
पूर्ण

/**
 * drm_sched_entity_select_rq - select a new rq क्रम the entity
 *
 * @entity: scheduler entity
 *
 * Check all prerequisites and select a new rq क्रम the entity क्रम load
 * balancing.
 */
व्योम drm_sched_entity_select_rq(काष्ठा drm_sched_entity *entity)
अणु
	काष्ठा dma_fence *fence;
	काष्ठा drm_gpu_scheduler *sched;
	काष्ठा drm_sched_rq *rq;

	अगर (spsc_queue_count(&entity->job_queue) || !entity->sched_list)
		वापस;

	fence = READ_ONCE(entity->last_scheduled);
	अगर (fence && !dma_fence_is_संकेतed(fence))
		वापस;

	spin_lock(&entity->rq_lock);
	sched = drm_sched_pick_best(entity->sched_list, entity->num_sched_list);
	rq = sched ? &sched->sched_rq[entity->priority] : शून्य;
	अगर (rq != entity->rq) अणु
		drm_sched_rq_हटाओ_entity(entity->rq, entity);
		entity->rq = rq;
	पूर्ण
	spin_unlock(&entity->rq_lock);

	अगर (entity->num_sched_list == 1)
		entity->sched_list = शून्य;
पूर्ण

/**
 * drm_sched_entity_push_job - Submit a job to the entity's job queue
 *
 * @sched_job: job to submit
 * @entity: scheduler entity
 *
 * Note: To guarantee that the order of insertion to queue matches
 * the job's fence sequence number this function should be
 * called with drm_sched_job_init under common lock.
 *
 * Returns 0 क्रम success, negative error code otherwise.
 */
व्योम drm_sched_entity_push_job(काष्ठा drm_sched_job *sched_job,
			       काष्ठा drm_sched_entity *entity)
अणु
	bool first;

	trace_drm_sched_job(sched_job, entity);
	atomic_inc(entity->rq->sched->score);
	WRITE_ONCE(entity->last_user, current->group_leader);
	first = spsc_queue_push(&entity->job_queue, &sched_job->queue_node);

	/* first job wakes up scheduler */
	अगर (first) अणु
		/* Add the entity to the run queue */
		spin_lock(&entity->rq_lock);
		अगर (entity->stopped) अणु
			spin_unlock(&entity->rq_lock);

			DRM_ERROR("Trying to push to a killed entity\n");
			वापस;
		पूर्ण
		drm_sched_rq_add_entity(entity->rq, entity);
		spin_unlock(&entity->rq_lock);
		drm_sched_wakeup(entity->rq->sched);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_sched_entity_push_job);
