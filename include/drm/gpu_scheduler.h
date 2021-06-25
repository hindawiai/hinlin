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

#अगर_अघोषित _DRM_GPU_SCHEDULER_H_
#घोषणा _DRM_GPU_SCHEDULER_H_

#समावेश <drm/spsc_queue.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/completion.h>

#घोषणा MAX_WAIT_SCHED_ENTITY_Q_EMPTY msecs_to_jअगरfies(1000)

काष्ठा drm_gpu_scheduler;
काष्ठा drm_sched_rq;

/* These are often used as an (initial) index
 * to an array, and as such should start at 0.
 */
क्रमागत drm_sched_priority अणु
	DRM_SCHED_PRIORITY_MIN,
	DRM_SCHED_PRIORITY_NORMAL,
	DRM_SCHED_PRIORITY_HIGH,
	DRM_SCHED_PRIORITY_KERNEL,

	DRM_SCHED_PRIORITY_COUNT,
	DRM_SCHED_PRIORITY_UNSET = -2
पूर्ण;

/**
 * काष्ठा drm_sched_entity - A wrapper around a job queue (typically
 * attached to the DRM file_priv).
 *
 * @list: used to append this काष्ठा to the list of entities in the
 *        runqueue.
 * @rq: runqueue on which this entity is currently scheduled.
 * @sched_list: A list of schedulers (drm_gpu_schedulers).
 *              Jobs from this entity can be scheduled on any scheduler
 *              on this list.
 * @num_sched_list: number of drm_gpu_schedulers in the sched_list.
 * @priority: priority of the entity
 * @rq_lock: lock to modअगरy the runqueue to which this entity beदीर्घs.
 * @job_queue: the list of jobs of this entity.
 * @fence_seq: a linearly increasing seqno incremented with each
 *             new &drm_sched_fence which is part of the entity.
 * @fence_context: a unique context क्रम all the fences which beदीर्घ
 *                 to this entity.
 *                 The &drm_sched_fence.scheduled uses the
 *                 fence_context but &drm_sched_fence.finished uses
 *                 fence_context + 1.
 * @dependency: the dependency fence of the job which is on the top
 *              of the job queue.
 * @cb: callback क्रम the dependency fence above.
 * @guilty: poपूर्णांकs to ctx's guilty.
 * @fini_status: contains the निकास status in हाल the process was संकेतled.
 * @last_scheduled: poपूर्णांकs to the finished fence of the last scheduled job.
 * @last_user: last group leader pushing a job पूर्णांकo the entity.
 * @stopped: Marks the enity as हटाओd from rq and destined क्रम termination.
 * @entity_idle: Signals when enityt is not in use
 *
 * Entities will emit jobs in order to their corresponding hardware
 * ring, and the scheduler will alternate between entities based on
 * scheduling policy.
 */
काष्ठा drm_sched_entity अणु
	काष्ठा list_head		list;
	काष्ठा drm_sched_rq		*rq;
	काष्ठा drm_gpu_scheduler        **sched_list;
	अचिन्हित पूर्णांक                    num_sched_list;
	क्रमागत drm_sched_priority         priority;
	spinlock_t			rq_lock;

	काष्ठा spsc_queue		job_queue;

	atomic_t			fence_seq;
	uपूर्णांक64_t			fence_context;

	काष्ठा dma_fence		*dependency;
	काष्ठा dma_fence_cb		cb;
	atomic_t			*guilty;
	काष्ठा dma_fence                *last_scheduled;
	काष्ठा task_काष्ठा		*last_user;
	bool 				stopped;
	काष्ठा completion		entity_idle;
पूर्ण;

/**
 * काष्ठा drm_sched_rq - queue of entities to be scheduled.
 *
 * @lock: to modअगरy the entities list.
 * @sched: the scheduler to which this rq beदीर्घs to.
 * @entities: list of the entities to be scheduled.
 * @current_entity: the entity which is to be scheduled.
 *
 * Run queue is a set of entities scheduling command submissions क्रम
 * one specअगरic ring. It implements the scheduling policy that selects
 * the next entity to emit commands from.
 */
काष्ठा drm_sched_rq अणु
	spinlock_t			lock;
	काष्ठा drm_gpu_scheduler	*sched;
	काष्ठा list_head		entities;
	काष्ठा drm_sched_entity		*current_entity;
पूर्ण;

/**
 * काष्ठा drm_sched_fence - fences corresponding to the scheduling of a job.
 */
काष्ठा drm_sched_fence अणु
        /**
         * @scheduled: this fence is what will be संकेतed by the scheduler
         * when the job is scheduled.
         */
	काष्ठा dma_fence		scheduled;

        /**
         * @finished: this fence is what will be संकेतed by the scheduler
         * when the job is completed.
         *
         * When setting up an out fence क्रम the job, you should use
         * this, since it's available immediately upon
         * drm_sched_job_init(), and the fence वापसed by the driver
         * from run_job() won't be created until the dependencies have
         * resolved.
         */
	काष्ठा dma_fence		finished;

        /**
         * @parent: the fence वापसed by &drm_sched_backend_ops.run_job
         * when scheduling the job on hardware. We संकेत the
         * &drm_sched_fence.finished fence once parent is संकेतled.
         */
	काष्ठा dma_fence		*parent;
        /**
         * @sched: the scheduler instance to which the job having this काष्ठा
         * beदीर्घs to.
         */
	काष्ठा drm_gpu_scheduler	*sched;
        /**
         * @lock: the lock used by the scheduled and the finished fences.
         */
	spinlock_t			lock;
        /**
         * @owner: job owner क्रम debugging
         */
	व्योम				*owner;
पूर्ण;

काष्ठा drm_sched_fence *to_drm_sched_fence(काष्ठा dma_fence *f);

/**
 * काष्ठा drm_sched_job - A job to be run by an entity.
 *
 * @queue_node: used to append this काष्ठा to the queue of jobs in an entity.
 * @list: a job participates in a "pending" and "done" lists.
 * @sched: the scheduler instance on which this job is scheduled.
 * @s_fence: contains the fences क्रम the scheduling of job.
 * @finish_cb: the callback क्रम the finished fence.
 * @id: a unique id asचिन्हित to each job scheduled on the scheduler.
 * @karma: increment on every hang caused by this job. If this exceeds the hang
 *         limit of the scheduler then the job is marked guilty and will not
 *         be scheduled further.
 * @s_priority: the priority of the job.
 * @entity: the entity to which this job beदीर्घs.
 * @cb: the callback क्रम the parent fence in s_fence.
 *
 * A job is created by the driver using drm_sched_job_init(), and
 * should call drm_sched_entity_push_job() once it wants the scheduler
 * to schedule the job.
 */
काष्ठा drm_sched_job अणु
	काष्ठा spsc_node		queue_node;
	काष्ठा list_head		list;
	काष्ठा drm_gpu_scheduler	*sched;
	काष्ठा drm_sched_fence		*s_fence;
	काष्ठा dma_fence_cb		finish_cb;
	uपूर्णांक64_t			id;
	atomic_t			karma;
	क्रमागत drm_sched_priority		s_priority;
	काष्ठा drm_sched_entity         *entity;
	काष्ठा dma_fence_cb		cb;
पूर्ण;

अटल अंतरभूत bool drm_sched_invalidate_job(काष्ठा drm_sched_job *s_job,
					    पूर्णांक threshold)
अणु
	वापस s_job && atomic_inc_वापस(&s_job->karma) > threshold;
पूर्ण

क्रमागत drm_gpu_sched_stat अणु
	DRM_GPU_SCHED_STAT_NONE, /* Reserve 0 */
	DRM_GPU_SCHED_STAT_NOMINAL,
	DRM_GPU_SCHED_STAT_ENODEV,
पूर्ण;

/**
 * काष्ठा drm_sched_backend_ops
 *
 * Define the backend operations called by the scheduler,
 * these functions should be implemented in driver side.
 */
काष्ठा drm_sched_backend_ops अणु
	/**
         * @dependency: Called when the scheduler is considering scheduling
         * this job next, to get another काष्ठा dma_fence क्रम this job to
	 * block on.  Once it वापसs शून्य, run_job() may be called.
	 */
	काष्ठा dma_fence *(*dependency)(काष्ठा drm_sched_job *sched_job,
					काष्ठा drm_sched_entity *s_entity);

	/**
         * @run_job: Called to execute the job once all of the dependencies
         * have been resolved.  This may be called multiple बार, अगर
	 * समयकरोut_job() has happened and drm_sched_job_recovery()
	 * decides to try it again.
	 */
	काष्ठा dma_fence *(*run_job)(काष्ठा drm_sched_job *sched_job);

	/**
	 * @समयकरोut_job: Called when a job has taken too दीर्घ to execute,
	 * to trigger GPU recovery.
	 *
	 * Return DRM_GPU_SCHED_STAT_NOMINAL, when all is normal,
	 * and the underlying driver has started or completed recovery.
	 *
	 * Return DRM_GPU_SCHED_STAT_ENODEV, अगर the device is no दीर्घer
	 * available, i.e. has been unplugged.
	 */
	क्रमागत drm_gpu_sched_stat (*समयकरोut_job)(काष्ठा drm_sched_job *sched_job);

	/**
         * @मुक्त_job: Called once the job's finished fence has been संकेतed
         * and it's समय to clean it up.
	 */
	व्योम (*मुक्त_job)(काष्ठा drm_sched_job *sched_job);
पूर्ण;

/**
 * काष्ठा drm_gpu_scheduler
 *
 * @ops: backend operations provided by the driver.
 * @hw_submission_limit: the max size of the hardware queue.
 * @समयout: the समय after which a job is हटाओd from the scheduler.
 * @name: name of the ring क्रम which this scheduler is being used.
 * @sched_rq: priority wise array of run queues.
 * @wake_up_worker: the रुको queue on which the scheduler sleeps until a job
 *                  is पढ़ोy to be scheduled.
 * @job_scheduled: once @drm_sched_entity_करो_release is called the scheduler
 *                 रुकोs on this रुको queue until all the scheduled jobs are
 *                 finished.
 * @hw_rq_count: the number of jobs currently in the hardware queue.
 * @job_id_count: used to assign unique id to the each job.
 * @work_tdr: schedules a delayed call to @drm_sched_job_समयकरोut after the
 *            समयout पूर्णांकerval is over.
 * @thपढ़ो: the kthपढ़ो on which the scheduler which run.
 * @pending_list: the list of jobs which are currently in the job queue.
 * @job_list_lock: lock to protect the pending_list.
 * @hang_limit: once the hangs by a job crosses this limit then it is marked
 *              guilty and it will be considered क्रम scheduling further.
 * @score: score to help loadbalancer pick a idle sched
 * @_score: score used when the driver करोesn't provide one
 * @पढ़ोy: marks अगर the underlying HW is पढ़ोy to work
 * @मुक्त_guilty: A hit to समय out handler to मुक्त the guilty job.
 *
 * One scheduler is implemented क्रम each hardware ring.
 */
काष्ठा drm_gpu_scheduler अणु
	स्थिर काष्ठा drm_sched_backend_ops	*ops;
	uपूर्णांक32_t			hw_submission_limit;
	दीर्घ				समयout;
	स्थिर अक्षर			*name;
	काष्ठा drm_sched_rq		sched_rq[DRM_SCHED_PRIORITY_COUNT];
	रुको_queue_head_t		wake_up_worker;
	रुको_queue_head_t		job_scheduled;
	atomic_t			hw_rq_count;
	atomic64_t			job_id_count;
	काष्ठा delayed_work		work_tdr;
	काष्ठा task_काष्ठा		*thपढ़ो;
	काष्ठा list_head		pending_list;
	spinlock_t			job_list_lock;
	पूर्णांक				hang_limit;
	atomic_t                        *score;
	atomic_t                        _score;
	bool				पढ़ोy;
	bool				मुक्त_guilty;
पूर्ण;

पूर्णांक drm_sched_init(काष्ठा drm_gpu_scheduler *sched,
		   स्थिर काष्ठा drm_sched_backend_ops *ops,
		   uपूर्णांक32_t hw_submission, अचिन्हित hang_limit, दीर्घ समयout,
		   atomic_t *score, स्थिर अक्षर *name);

व्योम drm_sched_fini(काष्ठा drm_gpu_scheduler *sched);
पूर्णांक drm_sched_job_init(काष्ठा drm_sched_job *job,
		       काष्ठा drm_sched_entity *entity,
		       व्योम *owner);
व्योम drm_sched_entity_modअगरy_sched(काष्ठा drm_sched_entity *entity,
				    काष्ठा drm_gpu_scheduler **sched_list,
                                   अचिन्हित पूर्णांक num_sched_list);

व्योम drm_sched_job_cleanup(काष्ठा drm_sched_job *job);
व्योम drm_sched_wakeup(काष्ठा drm_gpu_scheduler *sched);
व्योम drm_sched_stop(काष्ठा drm_gpu_scheduler *sched, काष्ठा drm_sched_job *bad);
व्योम drm_sched_start(काष्ठा drm_gpu_scheduler *sched, bool full_recovery);
व्योम drm_sched_resubmit_jobs(काष्ठा drm_gpu_scheduler *sched);
व्योम drm_sched_resubmit_jobs_ext(काष्ठा drm_gpu_scheduler *sched, पूर्णांक max);
व्योम drm_sched_increase_karma(काष्ठा drm_sched_job *bad);
व्योम drm_sched_reset_karma(काष्ठा drm_sched_job *bad);
व्योम drm_sched_increase_karma_ext(काष्ठा drm_sched_job *bad, पूर्णांक type);
bool drm_sched_dependency_optimized(काष्ठा dma_fence* fence,
				    काष्ठा drm_sched_entity *entity);
व्योम drm_sched_fault(काष्ठा drm_gpu_scheduler *sched);
व्योम drm_sched_job_kickout(काष्ठा drm_sched_job *s_job);

व्योम drm_sched_rq_add_entity(काष्ठा drm_sched_rq *rq,
			     काष्ठा drm_sched_entity *entity);
व्योम drm_sched_rq_हटाओ_entity(काष्ठा drm_sched_rq *rq,
				काष्ठा drm_sched_entity *entity);

पूर्णांक drm_sched_entity_init(काष्ठा drm_sched_entity *entity,
			  क्रमागत drm_sched_priority priority,
			  काष्ठा drm_gpu_scheduler **sched_list,
			  अचिन्हित पूर्णांक num_sched_list,
			  atomic_t *guilty);
दीर्घ drm_sched_entity_flush(काष्ठा drm_sched_entity *entity, दीर्घ समयout);
व्योम drm_sched_entity_fini(काष्ठा drm_sched_entity *entity);
व्योम drm_sched_entity_destroy(काष्ठा drm_sched_entity *entity);
व्योम drm_sched_entity_select_rq(काष्ठा drm_sched_entity *entity);
काष्ठा drm_sched_job *drm_sched_entity_pop_job(काष्ठा drm_sched_entity *entity);
व्योम drm_sched_entity_push_job(काष्ठा drm_sched_job *sched_job,
			       काष्ठा drm_sched_entity *entity);
व्योम drm_sched_entity_set_priority(काष्ठा drm_sched_entity *entity,
				   क्रमागत drm_sched_priority priority);
bool drm_sched_entity_is_पढ़ोy(काष्ठा drm_sched_entity *entity);

काष्ठा drm_sched_fence *drm_sched_fence_create(
	काष्ठा drm_sched_entity *s_entity, व्योम *owner);
व्योम drm_sched_fence_scheduled(काष्ठा drm_sched_fence *fence);
व्योम drm_sched_fence_finished(काष्ठा drm_sched_fence *fence);

अचिन्हित दीर्घ drm_sched_suspend_समयout(काष्ठा drm_gpu_scheduler *sched);
व्योम drm_sched_resume_समयout(काष्ठा drm_gpu_scheduler *sched,
		                अचिन्हित दीर्घ reमुख्यing);
काष्ठा drm_gpu_scheduler *
drm_sched_pick_best(काष्ठा drm_gpu_scheduler **sched_list,
		     अचिन्हित पूर्णांक num_sched_list);

#पूर्ण_अगर
