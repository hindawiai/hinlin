<शैली गुरु>
// SPDX-License-Identअगरier: MIT

#समावेश <uapi/linux/sched/types.h>

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_vblank_work.h>
#समावेश <drm/drm_crtc.h>

#समावेश "drm_internal.h"

/**
 * DOC: vblank works
 *
 * Many DRM drivers need to program hardware in a समय-sensitive manner, many
 * बार with a deadline of starting and finishing within a certain region of
 * the scanout. Most of the समय the safest way to accomplish this is to
 * simply करो said समय-sensitive programming in the driver's IRQ handler,
 * which allows drivers to aव्योम being preempted during these critical
 * regions. Or even better, the hardware may even handle applying such
 * समय-critical programming independently of the CPU.
 *
 * While there's a decent amount of hardware that's deचिन्हित so that the CPU
 * करोesn't need to be concerned with extremely समय-sensitive programming,
 * there's a few situations where it can't be helped. Some unक्रमgiving
 * hardware may require that certain समय-sensitive programming be handled
 * completely by the CPU, and said programming may even take too दीर्घ to
 * handle in an IRQ handler. Another such situation would be where the driver
 * needs to perक्रमm a task that needs to complete within a specअगरic scanout
 * period, but might possibly block and thus cannot be handled in an IRQ
 * context. Both of these situations can't be solved perfectly in Linux since
 * we're not a realसमय kernel, and thus the scheduler may cause us to miss
 * our deadline अगर it decides to preempt us. But क्रम some drivers, it's good
 * enough अगर we can lower our chance of being preempted to an असलolute
 * minimum.
 *
 * This is where &drm_vblank_work comes in. &drm_vblank_work provides a simple
 * generic delayed work implementation which delays work execution until a
 * particular vblank has passed, and then executes the work at realसमय
 * priority. This provides the best possible chance at perक्रमming
 * समय-sensitive hardware programming on समय, even when the प्रणाली is under
 * heavy load. &drm_vblank_work also supports rescheduling, so that self
 * re-arming work items can be easily implemented.
 */

व्योम drm_handle_vblank_works(काष्ठा drm_vblank_crtc *vblank)
अणु
	काष्ठा drm_vblank_work *work, *next;
	u64 count = atomic64_पढ़ो(&vblank->count);
	bool wake = false;

	निश्चित_spin_locked(&vblank->dev->event_lock);

	list_क्रम_each_entry_safe(work, next, &vblank->pending_work, node) अणु
		अगर (!drm_vblank_passed(count, work->count))
			जारी;

		list_del_init(&work->node);
		drm_vblank_put(vblank->dev, vblank->pipe);
		kthपढ़ो_queue_work(vblank->worker, &work->base);
		wake = true;
	पूर्ण
	अगर (wake)
		wake_up_all(&vblank->work_रुको_queue);
पूर्ण

/* Handle cancelling any pending vblank work items and drop respective vblank
 * references in response to vblank पूर्णांकerrupts being disabled.
 */
व्योम drm_vblank_cancel_pending_works(काष्ठा drm_vblank_crtc *vblank)
अणु
	काष्ठा drm_vblank_work *work, *next;

	निश्चित_spin_locked(&vblank->dev->event_lock);

	list_क्रम_each_entry_safe(work, next, &vblank->pending_work, node) अणु
		list_del_init(&work->node);
		drm_vblank_put(vblank->dev, vblank->pipe);
	पूर्ण

	wake_up_all(&vblank->work_रुको_queue);
पूर्ण

/**
 * drm_vblank_work_schedule - schedule a vblank work
 * @work: vblank work to schedule
 * @count: target vblank count
 * @nextonmiss: defer until the next vblank अगर target vblank was missed
 *
 * Schedule @work क्रम execution once the crtc vblank count reaches @count.
 *
 * If the crtc vblank count has alपढ़ोy reached @count and @nextonmiss is
 * %false the work starts to execute immediately.
 *
 * If the crtc vblank count has alपढ़ोy reached @count and @nextonmiss is
 * %true the work is deferred until the next vblank (as अगर @count has been
 * specअगरied as crtc vblank count + 1).
 *
 * If @work is alपढ़ोy scheduled, this function will reschedule said work
 * using the new @count. This can be used क्रम self-rearming work items.
 *
 * Returns:
 * %1 अगर @work was successfully (re)scheduled, %0 अगर it was either alपढ़ोy
 * scheduled or cancelled, or a negative error code on failure.
 */
पूर्णांक drm_vblank_work_schedule(काष्ठा drm_vblank_work *work,
			     u64 count, bool nextonmiss)
अणु
	काष्ठा drm_vblank_crtc *vblank = work->vblank;
	काष्ठा drm_device *dev = vblank->dev;
	u64 cur_vbl;
	अचिन्हित दीर्घ irqflags;
	bool passed, inmodeset, rescheduling = false, wake = false;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&dev->event_lock, irqflags);
	अगर (work->cancelling)
		जाओ out;

	spin_lock(&dev->vbl_lock);
	inmodeset = vblank->inmodeset;
	spin_unlock(&dev->vbl_lock);
	अगर (inmodeset)
		जाओ out;

	अगर (list_empty(&work->node)) अणु
		ret = drm_vblank_get(dev, vblank->pipe);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अगर (work->count == count) अणु
		/* Alपढ़ोy scheduled w/ same vbl count */
		जाओ out;
	पूर्ण अन्यथा अणु
		rescheduling = true;
	पूर्ण

	work->count = count;
	cur_vbl = drm_vblank_count(dev, vblank->pipe);
	passed = drm_vblank_passed(cur_vbl, count);
	अगर (passed)
		drm_dbg_core(dev,
			     "crtc %d vblank %llu already passed (current %llu)\n",
			     vblank->pipe, count, cur_vbl);

	अगर (!nextonmiss && passed) अणु
		drm_vblank_put(dev, vblank->pipe);
		ret = kthपढ़ो_queue_work(vblank->worker, &work->base);

		अगर (rescheduling) अणु
			list_del_init(&work->node);
			wake = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!rescheduling)
			list_add_tail(&work->node, &vblank->pending_work);
		ret = true;
	पूर्ण

out:
	spin_unlock_irqrestore(&dev->event_lock, irqflags);
	अगर (wake)
		wake_up_all(&vblank->work_रुको_queue);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_vblank_work_schedule);

/**
 * drm_vblank_work_cancel_sync - cancel a vblank work and रुको क्रम it to
 * finish executing
 * @work: vblank work to cancel
 *
 * Cancel an alपढ़ोy scheduled vblank work and रुको क्रम its
 * execution to finish.
 *
 * On वापस, @work is guaranteed to no दीर्घer be scheduled or running, even
 * अगर it's self-arming.
 *
 * Returns:
 * %True अगर the work was cancelled beक्रमe it started to execute, %false
 * otherwise.
 */
bool drm_vblank_work_cancel_sync(काष्ठा drm_vblank_work *work)
अणु
	काष्ठा drm_vblank_crtc *vblank = work->vblank;
	काष्ठा drm_device *dev = vblank->dev;
	bool ret = false;

	spin_lock_irq(&dev->event_lock);
	अगर (!list_empty(&work->node)) अणु
		list_del_init(&work->node);
		drm_vblank_put(vblank->dev, vblank->pipe);
		ret = true;
	पूर्ण

	work->cancelling++;
	spin_unlock_irq(&dev->event_lock);

	wake_up_all(&vblank->work_रुको_queue);

	अगर (kthपढ़ो_cancel_work_sync(&work->base))
		ret = true;

	spin_lock_irq(&dev->event_lock);
	work->cancelling--;
	spin_unlock_irq(&dev->event_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_vblank_work_cancel_sync);

/**
 * drm_vblank_work_flush - रुको क्रम a scheduled vblank work to finish
 * executing
 * @work: vblank work to flush
 *
 * Wait until @work has finished executing once.
 */
व्योम drm_vblank_work_flush(काष्ठा drm_vblank_work *work)
अणु
	काष्ठा drm_vblank_crtc *vblank = work->vblank;
	काष्ठा drm_device *dev = vblank->dev;

	spin_lock_irq(&dev->event_lock);
	रुको_event_lock_irq(vblank->work_रुको_queue, list_empty(&work->node),
			    dev->event_lock);
	spin_unlock_irq(&dev->event_lock);

	kthपढ़ो_flush_work(&work->base);
पूर्ण
EXPORT_SYMBOL(drm_vblank_work_flush);

/**
 * drm_vblank_work_init - initialize a vblank work item
 * @work: vblank work item
 * @crtc: CRTC whose vblank will trigger the work execution
 * @func: work function to be executed
 *
 * Initialize a vblank work item क्रम a specअगरic crtc.
 */
व्योम drm_vblank_work_init(काष्ठा drm_vblank_work *work, काष्ठा drm_crtc *crtc,
			  व्योम (*func)(काष्ठा kthपढ़ो_work *work))
अणु
	kthपढ़ो_init_work(&work->base, func);
	INIT_LIST_HEAD(&work->node);
	work->vblank = &crtc->dev->vblank[drm_crtc_index(crtc)];
पूर्ण
EXPORT_SYMBOL(drm_vblank_work_init);

पूर्णांक drm_vblank_worker_init(काष्ठा drm_vblank_crtc *vblank)
अणु
	काष्ठा kthपढ़ो_worker *worker;

	INIT_LIST_HEAD(&vblank->pending_work);
	init_रुकोqueue_head(&vblank->work_रुको_queue);
	worker = kthपढ़ो_create_worker(0, "card%d-crtc%d",
				       vblank->dev->primary->index,
				       vblank->pipe);
	अगर (IS_ERR(worker))
		वापस PTR_ERR(worker);

	vblank->worker = worker;

	sched_set_fअगरo(worker->task);
	वापस 0;
पूर्ण
