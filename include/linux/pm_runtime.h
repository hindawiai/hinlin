<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * pm_runसमय.स - Device run-समय घातer management helper functions.
 *
 * Copyright (C) 2009 Rafael J. Wysocki <rjw@sisk.pl>
 */

#अगर_अघोषित _LINUX_PM_RUNTIME_H
#घोषणा _LINUX_PM_RUNTIME_H

#समावेश <linux/device.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pm.h>

#समावेश <linux/jअगरfies.h>

/* Runसमय PM flag argument bits */
#घोषणा RPM_ASYNC		0x01	/* Request is asynchronous */
#घोषणा RPM_NOWAIT		0x02	/* Don't रुको क्रम concurrent
					    state change */
#घोषणा RPM_GET_PUT		0x04	/* Increment/decrement the
					    usage_count */
#घोषणा RPM_AUTO		0x08	/* Use स्वतःsuspend_delay */

#अगर_घोषित CONFIG_PM
बाह्य काष्ठा workqueue_काष्ठा *pm_wq;

अटल अंतरभूत bool queue_pm_work(काष्ठा work_काष्ठा *work)
अणु
	वापस queue_work(pm_wq, work);
पूर्ण

बाह्य पूर्णांक pm_generic_runसमय_suspend(काष्ठा device *dev);
बाह्य पूर्णांक pm_generic_runसमय_resume(काष्ठा device *dev);
बाह्य पूर्णांक pm_runसमय_क्रमce_suspend(काष्ठा device *dev);
बाह्य पूर्णांक pm_runसमय_क्रमce_resume(काष्ठा device *dev);

बाह्य पूर्णांक __pm_runसमय_idle(काष्ठा device *dev, पूर्णांक rpmflags);
बाह्य पूर्णांक __pm_runसमय_suspend(काष्ठा device *dev, पूर्णांक rpmflags);
बाह्य पूर्णांक __pm_runसमय_resume(काष्ठा device *dev, पूर्णांक rpmflags);
बाह्य पूर्णांक pm_runसमय_get_अगर_active(काष्ठा device *dev, bool ign_usage_count);
बाह्य पूर्णांक pm_schedule_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक delay);
बाह्य पूर्णांक __pm_runसमय_set_status(काष्ठा device *dev, अचिन्हित पूर्णांक status);
बाह्य पूर्णांक pm_runसमय_barrier(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_enable(काष्ठा device *dev);
बाह्य व्योम __pm_runसमय_disable(काष्ठा device *dev, bool check_resume);
बाह्य व्योम pm_runसमय_allow(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_क्रमbid(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_no_callbacks(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_irq_safe(काष्ठा device *dev);
बाह्य व्योम __pm_runसमय_use_स्वतःsuspend(काष्ठा device *dev, bool use);
बाह्य व्योम pm_runसमय_set_स्वतःsuspend_delay(काष्ठा device *dev, पूर्णांक delay);
बाह्य u64 pm_runसमय_स्वतःsuspend_expiration(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_update_max_समय_suspended(काष्ठा device *dev,
						 s64 delta_ns);
बाह्य व्योम pm_runसमय_set_meदो_स्मृति_noio(काष्ठा device *dev, bool enable);
बाह्य व्योम pm_runसमय_get_suppliers(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_put_suppliers(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_new_link(काष्ठा device *dev);
बाह्य व्योम pm_runसमय_drop_link(काष्ठा device_link *link);

/**
 * pm_runसमय_get_अगर_in_use - Conditionally bump up runसमय PM usage counter.
 * @dev: Target device.
 *
 * Increment the runसमय PM usage counter of @dev अगर its runसमय PM status is
 * %RPM_ACTIVE and its runसमय PM usage counter is greater than 0.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_get_अगर_in_use(काष्ठा device *dev)
अणु
	वापस pm_runसमय_get_अगर_active(dev, false);
पूर्ण

/**
 * pm_suspend_ignore_children - Set runसमय PM behavior regarding children.
 * @dev: Target device.
 * @enable: Whether or not to ignore possible dependencies on children.
 *
 * The dependencies of @dev on its children will not be taken पूर्णांकo account by
 * the runसमय PM framework going क्रमward अगर @enable is %true, or they will
 * be taken पूर्णांकo account otherwise.
 */
अटल अंतरभूत व्योम pm_suspend_ignore_children(काष्ठा device *dev, bool enable)
अणु
	dev->घातer.ignore_children = enable;
पूर्ण

/**
 * pm_runसमय_get_noresume - Bump up runसमय PM usage counter of a device.
 * @dev: Target device.
 */
अटल अंतरभूत व्योम pm_runसमय_get_noresume(काष्ठा device *dev)
अणु
	atomic_inc(&dev->घातer.usage_count);
पूर्ण

/**
 * pm_runसमय_put_noidle - Drop runसमय PM usage counter of a device.
 * @dev: Target device.
 *
 * Decrement the runसमय PM usage counter of @dev unless it is 0 alपढ़ोy.
 */
अटल अंतरभूत व्योम pm_runसमय_put_noidle(काष्ठा device *dev)
अणु
	atomic_add_unless(&dev->घातer.usage_count, -1, 0);
पूर्ण

/**
 * pm_runसमय_suspended - Check whether or not a device is runसमय-suspended.
 * @dev: Target device.
 *
 * Return %true अगर runसमय PM is enabled क्रम @dev and its runसमय PM status is
 * %RPM_SUSPENDED, or %false otherwise.
 *
 * Note that the वापस value of this function can only be trusted अगर it is
 * called under the runसमय PM lock of @dev or under conditions in which
 * runसमय PM cannot be either disabled or enabled क्रम @dev and its runसमय PM
 * status cannot change.
 */
अटल अंतरभूत bool pm_runसमय_suspended(काष्ठा device *dev)
अणु
	वापस dev->घातer.runसमय_status == RPM_SUSPENDED
		&& !dev->घातer.disable_depth;
पूर्ण

/**
 * pm_runसमय_active - Check whether or not a device is runसमय-active.
 * @dev: Target device.
 *
 * Return %true अगर runसमय PM is enabled क्रम @dev and its runसमय PM status is
 * %RPM_ACTIVE, or %false otherwise.
 *
 * Note that the वापस value of this function can only be trusted अगर it is
 * called under the runसमय PM lock of @dev or under conditions in which
 * runसमय PM cannot be either disabled or enabled क्रम @dev and its runसमय PM
 * status cannot change.
 */
अटल अंतरभूत bool pm_runसमय_active(काष्ठा device *dev)
अणु
	वापस dev->घातer.runसमय_status == RPM_ACTIVE
		|| dev->घातer.disable_depth;
पूर्ण

/**
 * pm_runसमय_status_suspended - Check अगर runसमय PM status is "suspended".
 * @dev: Target device.
 *
 * Return %true अगर the runसमय PM status of @dev is %RPM_SUSPENDED, or %false
 * otherwise, regardless of whether or not runसमय PM has been enabled क्रम @dev.
 *
 * Note that the वापस value of this function can only be trusted अगर it is
 * called under the runसमय PM lock of @dev or under conditions in which the
 * runसमय PM status of @dev cannot change.
 */
अटल अंतरभूत bool pm_runसमय_status_suspended(काष्ठा device *dev)
अणु
	वापस dev->घातer.runसमय_status == RPM_SUSPENDED;
पूर्ण

/**
 * pm_runसमय_enabled - Check अगर runसमय PM is enabled.
 * @dev: Target device.
 *
 * Return %true अगर runसमय PM is enabled क्रम @dev or %false otherwise.
 *
 * Note that the वापस value of this function can only be trusted अगर it is
 * called under the runसमय PM lock of @dev or under conditions in which
 * runसमय PM cannot be either disabled or enabled क्रम @dev.
 */
अटल अंतरभूत bool pm_runसमय_enabled(काष्ठा device *dev)
अणु
	वापस !dev->घातer.disable_depth;
पूर्ण

/**
 * pm_runसमय_has_no_callbacks - Check अगर runसमय PM callbacks may be present.
 * @dev: Target device.
 *
 * Return %true अगर @dev is a special device without runसमय PM callbacks or
 * %false otherwise.
 */
अटल अंतरभूत bool pm_runसमय_has_no_callbacks(काष्ठा device *dev)
अणु
	वापस dev->घातer.no_callbacks;
पूर्ण

/**
 * pm_runसमय_mark_last_busy - Update the last access समय of a device.
 * @dev: Target device.
 *
 * Update the last access समय of @dev used by the runसमय PM स्वतःsuspend
 * mechanism to the current समय as वापसed by kसमय_get_mono_fast_ns().
 */
अटल अंतरभूत व्योम pm_runसमय_mark_last_busy(काष्ठा device *dev)
अणु
	WRITE_ONCE(dev->घातer.last_busy, kसमय_get_mono_fast_ns());
पूर्ण

/**
 * pm_runसमय_is_irq_safe - Check अगर runसमय PM can work in पूर्णांकerrupt context.
 * @dev: Target device.
 *
 * Return %true अगर @dev has been marked as an "IRQ-safe" device (with respect
 * to runसमय PM), in which हाल its runसमय PM callabcks can be expected to
 * work correctly when invoked from पूर्णांकerrupt handlers.
 */
अटल अंतरभूत bool pm_runसमय_is_irq_safe(काष्ठा device *dev)
अणु
	वापस dev->घातer.irq_safe;
पूर्ण

बाह्य u64 pm_runसमय_suspended_समय(काष्ठा device *dev);

#अन्यथा /* !CONFIG_PM */

अटल अंतरभूत bool queue_pm_work(काष्ठा work_काष्ठा *work) अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक pm_generic_runसमय_suspend(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pm_generic_runसमय_resume(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pm_runसमय_क्रमce_suspend(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pm_runसमय_क्रमce_resume(काष्ठा device *dev) अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक __pm_runसमय_idle(काष्ठा device *dev, पूर्णांक rpmflags)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक __pm_runसमय_suspend(काष्ठा device *dev, पूर्णांक rpmflags)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक __pm_runसमय_resume(काष्ठा device *dev, पूर्णांक rpmflags)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक pm_schedule_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक delay)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक pm_runसमय_get_अगर_in_use(काष्ठा device *dev)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक pm_runसमय_get_अगर_active(काष्ठा device *dev,
					   bool ign_usage_count)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक __pm_runसमय_set_status(काष्ठा device *dev,
					    अचिन्हित पूर्णांक status) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pm_runसमय_barrier(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pm_runसमय_enable(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम __pm_runसमय_disable(काष्ठा device *dev, bool c) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_allow(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_क्रमbid(काष्ठा device *dev) अणुपूर्ण

अटल अंतरभूत व्योम pm_suspend_ignore_children(काष्ठा device *dev, bool enable) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_get_noresume(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_put_noidle(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत bool pm_runसमय_suspended(काष्ठा device *dev) अणु वापस false; पूर्ण
अटल अंतरभूत bool pm_runसमय_active(काष्ठा device *dev) अणु वापस true; पूर्ण
अटल अंतरभूत bool pm_runसमय_status_suspended(काष्ठा device *dev) अणु वापस false; पूर्ण
अटल अंतरभूत bool pm_runसमय_enabled(काष्ठा device *dev) अणु वापस false; पूर्ण

अटल अंतरभूत व्योम pm_runसमय_no_callbacks(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_irq_safe(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत bool pm_runसमय_is_irq_safe(काष्ठा device *dev) अणु वापस false; पूर्ण

अटल अंतरभूत bool pm_runसमय_has_no_callbacks(काष्ठा device *dev) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम pm_runसमय_mark_last_busy(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम __pm_runसमय_use_स्वतःsuspend(काष्ठा device *dev,
						bool use) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_set_स्वतःsuspend_delay(काष्ठा device *dev,
						पूर्णांक delay) अणुपूर्ण
अटल अंतरभूत u64 pm_runसमय_स्वतःsuspend_expiration(
				काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम pm_runसमय_set_meदो_स्मृति_noio(काष्ठा device *dev,
						bool enable)अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_get_suppliers(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_put_suppliers(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_new_link(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत व्योम pm_runसमय_drop_link(काष्ठा device_link *link) अणुपूर्ण

#पूर्ण_अगर /* !CONFIG_PM */

/**
 * pm_runसमय_idle - Conditionally set up स्वतःsuspend of a device or suspend it.
 * @dev: Target device.
 *
 * Invoke the "idle check" callback of @dev and, depending on its वापस value,
 * set up स्वतःsuspend of @dev or suspend it (depending on whether or not
 * स्वतःsuspend has been enabled क्रम it).
 */
अटल अंतरभूत पूर्णांक pm_runसमय_idle(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_idle(dev, 0);
पूर्ण

/**
 * pm_runसमय_suspend - Suspend a device synchronously.
 * @dev: Target device.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_suspend(dev, 0);
पूर्ण

/**
 * pm_runसमय_स्वतःsuspend - Set up स्वतःsuspend of a device or suspend it.
 * @dev: Target device.
 *
 * Set up स्वतःsuspend of @dev or suspend it (depending on whether or not
 * स्वतःsuspend is enabled क्रम it) without engaging its "idle check" callback.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_स्वतःsuspend(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_suspend(dev, RPM_AUTO);
पूर्ण

/**
 * pm_runसमय_resume - Resume a device synchronously.
 * @dev: Target device.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_resume(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_resume(dev, 0);
पूर्ण

/**
 * pm_request_idle - Queue up "idle check" execution क्रम a device.
 * @dev: Target device.
 *
 * Queue up a work item to run an equivalent of pm_runसमय_idle() क्रम @dev
 * asynchronously.
 */
अटल अंतरभूत पूर्णांक pm_request_idle(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_idle(dev, RPM_ASYNC);
पूर्ण

/**
 * pm_request_resume - Queue up runसमय-resume of a device.
 * @dev: Target device.
 */
अटल अंतरभूत पूर्णांक pm_request_resume(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_resume(dev, RPM_ASYNC);
पूर्ण

/**
 * pm_request_स्वतःsuspend - Queue up स्वतःsuspend of a device.
 * @dev: Target device.
 *
 * Queue up a work item to run an equivalent pm_runसमय_स्वतःsuspend() क्रम @dev
 * asynchronously.
 */
अटल अंतरभूत पूर्णांक pm_request_स्वतःsuspend(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_suspend(dev, RPM_ASYNC | RPM_AUTO);
पूर्ण

/**
 * pm_runसमय_get - Bump up usage counter and queue up resume of a device.
 * @dev: Target device.
 *
 * Bump up the runसमय PM usage counter of @dev and queue up a work item to
 * carry out runसमय-resume of it.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_get(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_resume(dev, RPM_GET_PUT | RPM_ASYNC);
पूर्ण

/**
 * pm_runसमय_get_sync - Bump up usage counter of a device and resume it.
 * @dev: Target device.
 *
 * Bump up the runसमय PM usage counter of @dev and carry out runसमय-resume of
 * it synchronously.
 *
 * The possible वापस values of this function are the same as क्रम
 * pm_runसमय_resume() and the runसमय PM usage counter of @dev reमुख्यs
 * incremented in all हालs, even अगर it वापसs an error code.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_get_sync(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_resume(dev, RPM_GET_PUT);
पूर्ण

/**
 * pm_runसमय_resume_and_get - Bump up usage counter of a device and resume it.
 * @dev: Target device.
 *
 * Resume @dev synchronously and अगर that is successful, increment its runसमय
 * PM usage counter. Return 0 अगर the runसमय PM usage counter of @dev has been
 * incremented or a negative error code otherwise.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_resume_and_get(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = __pm_runसमय_resume(dev, RPM_GET_PUT);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pm_runसमय_put - Drop device usage counter and queue up "idle check" अगर 0.
 * @dev: Target device.
 *
 * Decrement the runसमय PM usage counter of @dev and अगर it turns out to be
 * equal to 0, queue up a work item क्रम @dev like in pm_request_idle().
 */
अटल अंतरभूत पूर्णांक pm_runसमय_put(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_idle(dev, RPM_GET_PUT | RPM_ASYNC);
पूर्ण

/**
 * pm_runसमय_put_स्वतःsuspend - Drop device usage counter and queue स्वतःsuspend अगर 0.
 * @dev: Target device.
 *
 * Decrement the runसमय PM usage counter of @dev and अगर it turns out to be
 * equal to 0, queue up a work item क्रम @dev like in pm_request_स्वतःsuspend().
 */
अटल अंतरभूत पूर्णांक pm_runसमय_put_स्वतःsuspend(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_suspend(dev,
	    RPM_GET_PUT | RPM_ASYNC | RPM_AUTO);
पूर्ण

/**
 * pm_runसमय_put_sync - Drop device usage counter and run "idle check" अगर 0.
 * @dev: Target device.
 *
 * Decrement the runसमय PM usage counter of @dev and अगर it turns out to be
 * equal to 0, invoke the "idle check" callback of @dev and, depending on its
 * वापस value, set up स्वतःsuspend of @dev or suspend it (depending on whether
 * or not स्वतःsuspend has been enabled क्रम it).
 *
 * The possible वापस values of this function are the same as क्रम
 * pm_runसमय_idle() and the runसमय PM usage counter of @dev reमुख्यs
 * decremented in all हालs, even अगर it वापसs an error code.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_put_sync(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_idle(dev, RPM_GET_PUT);
पूर्ण

/**
 * pm_runसमय_put_sync_suspend - Drop device usage counter and suspend अगर 0.
 * @dev: Target device.
 *
 * Decrement the runसमय PM usage counter of @dev and अगर it turns out to be
 * equal to 0, carry out runसमय-suspend of @dev synchronously.
 *
 * The possible वापस values of this function are the same as क्रम
 * pm_runसमय_suspend() and the runसमय PM usage counter of @dev reमुख्यs
 * decremented in all हालs, even अगर it वापसs an error code.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_put_sync_suspend(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_suspend(dev, RPM_GET_PUT);
पूर्ण

/**
 * pm_runसमय_put_sync_स्वतःsuspend - Drop device usage counter and स्वतःsuspend अगर 0.
 * @dev: Target device.
 *
 * Decrement the runसमय PM usage counter of @dev and अगर it turns out to be
 * equal to 0, set up स्वतःsuspend of @dev or suspend it synchronously (depending
 * on whether or not स्वतःsuspend has been enabled क्रम it).
 *
 * The possible वापस values of this function are the same as क्रम
 * pm_runसमय_स्वतःsuspend() and the runसमय PM usage counter of @dev reमुख्यs
 * decremented in all हालs, even अगर it वापसs an error code.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_put_sync_स्वतःsuspend(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_suspend(dev, RPM_GET_PUT | RPM_AUTO);
पूर्ण

/**
 * pm_runसमय_set_active - Set runसमय PM status to "active".
 * @dev: Target device.
 *
 * Set the runसमय PM status of @dev to %RPM_ACTIVE and ensure that dependencies
 * of it will be taken पूर्णांकo account.
 *
 * It is not valid to call this function क्रम devices with runसमय PM enabled.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_set_active(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_set_status(dev, RPM_ACTIVE);
पूर्ण

/**
 * pm_runसमय_set_suspended - Set runसमय PM status to "suspended".
 * @dev: Target device.
 *
 * Set the runसमय PM status of @dev to %RPM_SUSPENDED and ensure that
 * dependencies of it will be taken पूर्णांकo account.
 *
 * It is not valid to call this function क्रम devices with runसमय PM enabled.
 */
अटल अंतरभूत पूर्णांक pm_runसमय_set_suspended(काष्ठा device *dev)
अणु
	वापस __pm_runसमय_set_status(dev, RPM_SUSPENDED);
पूर्ण

/**
 * pm_runसमय_disable - Disable runसमय PM क्रम a device.
 * @dev: Target device.
 *
 * Prevent the runसमय PM framework from working with @dev (by incrementing its
 * "blocking" counter).
 *
 * For each invocation of this function क्रम @dev there must be a matching
 * pm_runसमय_enable() call in order क्रम runसमय PM to be enabled क्रम it.
 */
अटल अंतरभूत व्योम pm_runसमय_disable(काष्ठा device *dev)
अणु
	__pm_runसमय_disable(dev, true);
पूर्ण

/**
 * pm_runसमय_use_स्वतःsuspend - Allow स्वतःsuspend to be used क्रम a device.
 * @dev: Target device.
 *
 * Allow the runसमय PM स्वतःsuspend mechanism to be used क्रम @dev whenever
 * requested (or "autosuspend" will be handled as direct runसमय-suspend क्रम
 * it).
 */
अटल अंतरभूत व्योम pm_runसमय_use_स्वतःsuspend(काष्ठा device *dev)
अणु
	__pm_runसमय_use_स्वतःsuspend(dev, true);
पूर्ण

/**
 * pm_runसमय_करोnt_use_स्वतःsuspend - Prevent स्वतःsuspend from being used.
 * @dev: Target device.
 *
 * Prevent the runसमय PM स्वतःsuspend mechanism from being used क्रम @dev which
 * means that "autosuspend" will be handled as direct runसमय-suspend क्रम it
 * going क्रमward.
 */
अटल अंतरभूत व्योम pm_runसमय_करोnt_use_स्वतःsuspend(काष्ठा device *dev)
अणु
	__pm_runसमय_use_स्वतःsuspend(dev, false);
पूर्ण

#पूर्ण_अगर
