<शैली गुरु>
/*
 * Copyright (C) 2013 Red Hat
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/slab.h>

#समावेश <drm/drm_flip_work.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_util.h>

/**
 * drm_flip_work_allocate_task - allocate a flip-work task
 * @data: data associated to the task
 * @flags: allocator flags
 *
 * Allocate a drm_flip_task object and attach निजी data to it.
 */
काष्ठा drm_flip_task *drm_flip_work_allocate_task(व्योम *data, gfp_t flags)
अणु
	काष्ठा drm_flip_task *task;

	task = kzalloc(माप(*task), flags);
	अगर (task)
		task->data = data;

	वापस task;
पूर्ण
EXPORT_SYMBOL(drm_flip_work_allocate_task);

/**
 * drm_flip_work_queue_task - queue a specअगरic task
 * @work: the flip-work
 * @task: the task to handle
 *
 * Queues task, that will later be run (passed back to drm_flip_func_t
 * func) on a work queue after drm_flip_work_commit() is called.
 */
व्योम drm_flip_work_queue_task(काष्ठा drm_flip_work *work,
			      काष्ठा drm_flip_task *task)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&work->lock, flags);
	list_add_tail(&task->node, &work->queued);
	spin_unlock_irqrestore(&work->lock, flags);
पूर्ण
EXPORT_SYMBOL(drm_flip_work_queue_task);

/**
 * drm_flip_work_queue - queue work
 * @work: the flip-work
 * @val: the value to queue
 *
 * Queues work, that will later be run (passed back to drm_flip_func_t
 * func) on a work queue after drm_flip_work_commit() is called.
 */
व्योम drm_flip_work_queue(काष्ठा drm_flip_work *work, व्योम *val)
अणु
	काष्ठा drm_flip_task *task;

	task = drm_flip_work_allocate_task(val,
				drm_can_sleep() ? GFP_KERNEL : GFP_ATOMIC);
	अगर (task) अणु
		drm_flip_work_queue_task(work, task);
	पूर्ण अन्यथा अणु
		DRM_ERROR("%s could not allocate task!\n", work->name);
		work->func(work, val);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_flip_work_queue);

/**
 * drm_flip_work_commit - commit queued work
 * @work: the flip-work
 * @wq: the work-queue to run the queued work on
 *
 * Trigger work previously queued by drm_flip_work_queue() to run
 * on a workqueue.  The typical usage would be to queue work (via
 * drm_flip_work_queue()) at any poपूर्णांक (from vblank irq and/or
 * prior), and then from vblank irq commit the queued work.
 */
व्योम drm_flip_work_commit(काष्ठा drm_flip_work *work,
		काष्ठा workqueue_काष्ठा *wq)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&work->lock, flags);
	list_splice_tail(&work->queued, &work->commited);
	INIT_LIST_HEAD(&work->queued);
	spin_unlock_irqrestore(&work->lock, flags);
	queue_work(wq, &work->worker);
पूर्ण
EXPORT_SYMBOL(drm_flip_work_commit);

अटल व्योम flip_worker(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा drm_flip_work *work = container_of(w, काष्ठा drm_flip_work, worker);
	काष्ठा list_head tasks;
	अचिन्हित दीर्घ flags;

	जबतक (1) अणु
		काष्ठा drm_flip_task *task, *पंचांगp;

		INIT_LIST_HEAD(&tasks);
		spin_lock_irqsave(&work->lock, flags);
		list_splice_tail(&work->commited, &tasks);
		INIT_LIST_HEAD(&work->commited);
		spin_unlock_irqrestore(&work->lock, flags);

		अगर (list_empty(&tasks))
			अवरोध;

		list_क्रम_each_entry_safe(task, पंचांगp, &tasks, node) अणु
			work->func(work, task->data);
			kमुक्त(task);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * drm_flip_work_init - initialize flip-work
 * @work: the flip-work to initialize
 * @name: debug name
 * @func: the callback work function
 *
 * Initializes/allocates resources क्रम the flip-work
 */
व्योम drm_flip_work_init(काष्ठा drm_flip_work *work,
		स्थिर अक्षर *name, drm_flip_func_t func)
अणु
	work->name = name;
	INIT_LIST_HEAD(&work->queued);
	INIT_LIST_HEAD(&work->commited);
	spin_lock_init(&work->lock);
	work->func = func;

	INIT_WORK(&work->worker, flip_worker);
पूर्ण
EXPORT_SYMBOL(drm_flip_work_init);

/**
 * drm_flip_work_cleanup - cleans up flip-work
 * @work: the flip-work to cleanup
 *
 * Destroy resources allocated क्रम the flip-work
 */
व्योम drm_flip_work_cleanup(काष्ठा drm_flip_work *work)
अणु
	WARN_ON(!list_empty(&work->queued) || !list_empty(&work->commited));
पूर्ण
EXPORT_SYMBOL(drm_flip_work_cleanup);
