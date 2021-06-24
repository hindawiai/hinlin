<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-pm.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "blk-mq.h"
#समावेश "blk-mq-tag.h"

/**
 * blk_pm_runसमय_init - Block layer runसमय PM initialization routine
 * @q: the queue of the device
 * @dev: the device the queue beदीर्घs to
 *
 * Description:
 *    Initialize runसमय-PM-related fields क्रम @q and start स्वतः suspend क्रम
 *    @dev. Drivers that want to take advantage of request-based runसमय PM
 *    should call this function after @dev has been initialized, and its
 *    request queue @q has been allocated, and runसमय PM क्रम it can not happen
 *    yet(either due to disabled/क्रमbidden or its usage_count > 0). In most
 *    हालs, driver should call this function beक्रमe any I/O has taken place.
 *
 *    This function takes care of setting up using स्वतः suspend क्रम the device,
 *    the स्वतःsuspend delay is set to -1 to make runसमय suspend impossible
 *    until an updated value is either set by user or by driver. Drivers करो
 *    not need to touch other स्वतःsuspend settings.
 *
 *    The block layer runसमय PM is request based, so only works क्रम drivers
 *    that use request as their IO unit instead of those directly use bio's.
 */
व्योम blk_pm_runसमय_init(काष्ठा request_queue *q, काष्ठा device *dev)
अणु
	q->dev = dev;
	q->rpm_status = RPM_ACTIVE;
	pm_runसमय_set_स्वतःsuspend_delay(q->dev, -1);
	pm_runसमय_use_स्वतःsuspend(q->dev);
पूर्ण
EXPORT_SYMBOL(blk_pm_runसमय_init);

/**
 * blk_pre_runसमय_suspend - Pre runसमय suspend check
 * @q: the queue of the device
 *
 * Description:
 *    This function will check अगर runसमय suspend is allowed क्रम the device
 *    by examining अगर there are any requests pending in the queue. If there
 *    are requests pending, the device can not be runसमय suspended; otherwise,
 *    the queue's status will be updated to SUSPENDING and the driver can
 *    proceed to suspend the device.
 *
 *    For the not allowed हाल, we mark last busy क्रम the device so that
 *    runसमय PM core will try to स्वतःsuspend it some समय later.
 *
 *    This function should be called near the start of the device's
 *    runसमय_suspend callback.
 *
 * Return:
 *    0		- OK to runसमय suspend the device
 *    -EBUSY	- Device should not be runसमय suspended
 */
पूर्णांक blk_pre_runसमय_suspend(काष्ठा request_queue *q)
अणु
	पूर्णांक ret = 0;

	अगर (!q->dev)
		वापस ret;

	WARN_ON_ONCE(q->rpm_status != RPM_ACTIVE);

	spin_lock_irq(&q->queue_lock);
	q->rpm_status = RPM_SUSPENDING;
	spin_unlock_irq(&q->queue_lock);

	/*
	 * Increase the pm_only counter beक्रमe checking whether any
	 * non-PM blk_queue_enter() calls are in progress to aव्योम that any
	 * new non-PM blk_queue_enter() calls succeed beक्रमe the pm_only
	 * counter is decreased again.
	 */
	blk_set_pm_only(q);
	ret = -EBUSY;
	/* Switch q_usage_counter from per-cpu to atomic mode. */
	blk_मुक्तze_queue_start(q);
	/*
	 * Wait until atomic mode has been reached. Since that
	 * involves calling call_rcu(), it is guaranteed that later
	 * blk_queue_enter() calls see the pm-only state. See also
	 * http://lwn.net/Articles/573497/.
	 */
	percpu_ref_चयन_to_atomic_sync(&q->q_usage_counter);
	अगर (percpu_ref_is_zero(&q->q_usage_counter))
		ret = 0;
	/* Switch q_usage_counter back to per-cpu mode. */
	blk_mq_unमुक्तze_queue(q);

	अगर (ret < 0) अणु
		spin_lock_irq(&q->queue_lock);
		q->rpm_status = RPM_ACTIVE;
		pm_runसमय_mark_last_busy(q->dev);
		spin_unlock_irq(&q->queue_lock);

		blk_clear_pm_only(q);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(blk_pre_runसमय_suspend);

/**
 * blk_post_runसमय_suspend - Post runसमय suspend processing
 * @q: the queue of the device
 * @err: वापस value of the device's runसमय_suspend function
 *
 * Description:
 *    Update the queue's runसमय status according to the वापस value of the
 *    device's runसमय suspend function and mark last busy क्रम the device so
 *    that PM core will try to स्वतः suspend the device at a later समय.
 *
 *    This function should be called near the end of the device's
 *    runसमय_suspend callback.
 */
व्योम blk_post_runसमय_suspend(काष्ठा request_queue *q, पूर्णांक err)
अणु
	अगर (!q->dev)
		वापस;

	spin_lock_irq(&q->queue_lock);
	अगर (!err) अणु
		q->rpm_status = RPM_SUSPENDED;
	पूर्ण अन्यथा अणु
		q->rpm_status = RPM_ACTIVE;
		pm_runसमय_mark_last_busy(q->dev);
	पूर्ण
	spin_unlock_irq(&q->queue_lock);

	अगर (err)
		blk_clear_pm_only(q);
पूर्ण
EXPORT_SYMBOL(blk_post_runसमय_suspend);

/**
 * blk_pre_runसमय_resume - Pre runसमय resume processing
 * @q: the queue of the device
 *
 * Description:
 *    Update the queue's runसमय status to RESUMING in preparation क्रम the
 *    runसमय resume of the device.
 *
 *    This function should be called near the start of the device's
 *    runसमय_resume callback.
 */
व्योम blk_pre_runसमय_resume(काष्ठा request_queue *q)
अणु
	अगर (!q->dev)
		वापस;

	spin_lock_irq(&q->queue_lock);
	q->rpm_status = RPM_RESUMING;
	spin_unlock_irq(&q->queue_lock);
पूर्ण
EXPORT_SYMBOL(blk_pre_runसमय_resume);

/**
 * blk_post_runसमय_resume - Post runसमय resume processing
 * @q: the queue of the device
 * @err: वापस value of the device's runसमय_resume function
 *
 * Description:
 *    Update the queue's runसमय status according to the वापस value of the
 *    device's runसमय_resume function. If the resume was successful, call
 *    blk_set_runसमय_active() to करो the real work of restarting the queue.
 *
 *    This function should be called near the end of the device's
 *    runसमय_resume callback.
 */
व्योम blk_post_runसमय_resume(काष्ठा request_queue *q, पूर्णांक err)
अणु
	अगर (!q->dev)
		वापस;
	अगर (!err) अणु
		blk_set_runसमय_active(q);
	पूर्ण अन्यथा अणु
		spin_lock_irq(&q->queue_lock);
		q->rpm_status = RPM_SUSPENDED;
		spin_unlock_irq(&q->queue_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(blk_post_runसमय_resume);

/**
 * blk_set_runसमय_active - Force runसमय status of the queue to be active
 * @q: the queue of the device
 *
 * If the device is left runसमय suspended during प्रणाली suspend the resume
 * hook typically resumes the device and corrects runसमय status
 * accordingly. However, that करोes not affect the queue runसमय PM status
 * which is still "suspended". This prevents processing requests from the
 * queue.
 *
 * This function can be used in driver's resume hook to correct queue
 * runसमय PM status and re-enable peeking requests from the queue. It
 * should be called beक्रमe first request is added to the queue.
 *
 * This function is also called by blk_post_runसमय_resume() क्रम successful
 * runसमय resumes.  It करोes everything necessary to restart the queue.
 */
व्योम blk_set_runसमय_active(काष्ठा request_queue *q)
अणु
	पूर्णांक old_status;

	अगर (!q->dev)
		वापस;

	spin_lock_irq(&q->queue_lock);
	old_status = q->rpm_status;
	q->rpm_status = RPM_ACTIVE;
	pm_runसमय_mark_last_busy(q->dev);
	pm_request_स्वतःsuspend(q->dev);
	spin_unlock_irq(&q->queue_lock);

	अगर (old_status != RPM_ACTIVE)
		blk_clear_pm_only(q);
पूर्ण
EXPORT_SYMBOL(blk_set_runसमय_active);
