<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/runसमय.c - Helper functions क्रम device runसमय PM
 *
 * Copyright (c) 2009 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 * Copyright (C) 2010 Alan Stern <stern@rowland.harvard.edu>
 */
#समावेश <linux/sched/mm.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/export.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <trace/events/rpm.h>

#समावेश "../base.h"
#समावेश "power.h"

प्रकार पूर्णांक (*pm_callback_t)(काष्ठा device *);

अटल pm_callback_t __rpm_get_callback(काष्ठा device *dev, माप_प्रकार cb_offset)
अणु
	pm_callback_t cb;
	स्थिर काष्ठा dev_pm_ops *ops;

	अगर (dev->pm_करोमुख्य)
		ops = &dev->pm_करोमुख्य->ops;
	अन्यथा अगर (dev->type && dev->type->pm)
		ops = dev->type->pm;
	अन्यथा अगर (dev->class && dev->class->pm)
		ops = dev->class->pm;
	अन्यथा अगर (dev->bus && dev->bus->pm)
		ops = dev->bus->pm;
	अन्यथा
		ops = शून्य;

	अगर (ops)
		cb = *(pm_callback_t *)((व्योम *)ops + cb_offset);
	अन्यथा
		cb = शून्य;

	अगर (!cb && dev->driver && dev->driver->pm)
		cb = *(pm_callback_t *)((व्योम *)dev->driver->pm + cb_offset);

	वापस cb;
पूर्ण

#घोषणा RPM_GET_CALLBACK(dev, callback) \
		__rpm_get_callback(dev, दुरत्व(काष्ठा dev_pm_ops, callback))

अटल पूर्णांक rpm_resume(काष्ठा device *dev, पूर्णांक rpmflags);
अटल पूर्णांक rpm_suspend(काष्ठा device *dev, पूर्णांक rpmflags);

/**
 * update_pm_runसमय_accounting - Update the समय accounting of घातer states
 * @dev: Device to update the accounting क्रम
 *
 * In order to be able to have समय accounting of the various घातer states
 * (as used by programs such as PowerTOP to show the effectiveness of runसमय
 * PM), we need to track the समय spent in each state.
 * update_pm_runसमय_accounting must be called each समय beक्रमe the
 * runसमय_status field is updated, to account the समय in the old state
 * correctly.
 */
अटल व्योम update_pm_runसमय_accounting(काष्ठा device *dev)
अणु
	u64 now, last, delta;

	अगर (dev->घातer.disable_depth > 0)
		वापस;

	last = dev->घातer.accounting_बारtamp;

	now = kसमय_get_mono_fast_ns();
	dev->घातer.accounting_बारtamp = now;

	/*
	 * Because kसमय_get_mono_fast_ns() is not monotonic during
	 * समयkeeping updates, ensure that 'now' is after the last saved
	 * बारptamp.
	 */
	अगर (now < last)
		वापस;

	delta = now - last;

	अगर (dev->घातer.runसमय_status == RPM_SUSPENDED)
		dev->घातer.suspended_समय += delta;
	अन्यथा
		dev->घातer.active_समय += delta;
पूर्ण

अटल व्योम __update_runसमय_status(काष्ठा device *dev, क्रमागत rpm_status status)
अणु
	update_pm_runसमय_accounting(dev);
	dev->घातer.runसमय_status = status;
पूर्ण

अटल u64 rpm_get_accounted_समय(काष्ठा device *dev, bool suspended)
अणु
	u64 समय;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->घातer.lock, flags);

	update_pm_runसमय_accounting(dev);
	समय = suspended ? dev->घातer.suspended_समय : dev->घातer.active_समय;

	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	वापस समय;
पूर्ण

u64 pm_runसमय_active_समय(काष्ठा device *dev)
अणु
	वापस rpm_get_accounted_समय(dev, false);
पूर्ण

u64 pm_runसमय_suspended_समय(काष्ठा device *dev)
अणु
	वापस rpm_get_accounted_समय(dev, true);
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_suspended_समय);

/**
 * pm_runसमय_deactivate_समयr - Deactivate given device's suspend समयr.
 * @dev: Device to handle.
 */
अटल व्योम pm_runसमय_deactivate_समयr(काष्ठा device *dev)
अणु
	अगर (dev->घातer.समयr_expires > 0) अणु
		hrसमयr_try_to_cancel(&dev->घातer.suspend_समयr);
		dev->घातer.समयr_expires = 0;
	पूर्ण
पूर्ण

/**
 * pm_runसमय_cancel_pending - Deactivate suspend समयr and cancel requests.
 * @dev: Device to handle.
 */
अटल व्योम pm_runसमय_cancel_pending(काष्ठा device *dev)
अणु
	pm_runसमय_deactivate_समयr(dev);
	/*
	 * In हाल there's a request pending, make sure its work function will
	 * वापस without करोing anything.
	 */
	dev->घातer.request = RPM_REQ_NONE;
पूर्ण

/*
 * pm_runसमय_स्वतःsuspend_expiration - Get a device's स्वतःsuspend-delay expiration समय.
 * @dev: Device to handle.
 *
 * Compute the स्वतःsuspend-delay expiration समय based on the device's
 * घातer.last_busy समय.  If the delay has alपढ़ोy expired or is disabled
 * (negative) or the घातer.use_स्वतःsuspend flag isn't set, वापस 0.
 * Otherwise वापस the expiration समय in nanoseconds (adjusted to be nonzero).
 *
 * This function may be called either with or without dev->घातer.lock held.
 * Either way it can be racy, since घातer.last_busy may be updated at any समय.
 */
u64 pm_runसमय_स्वतःsuspend_expiration(काष्ठा device *dev)
अणु
	पूर्णांक स्वतःsuspend_delay;
	u64 expires;

	अगर (!dev->घातer.use_स्वतःsuspend)
		वापस 0;

	स्वतःsuspend_delay = READ_ONCE(dev->घातer.स्वतःsuspend_delay);
	अगर (स्वतःsuspend_delay < 0)
		वापस 0;

	expires  = READ_ONCE(dev->घातer.last_busy);
	expires += (u64)स्वतःsuspend_delay * NSEC_PER_MSEC;
	अगर (expires > kसमय_get_mono_fast_ns())
		वापस expires;	/* Expires in the future */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_स्वतःsuspend_expiration);

अटल पूर्णांक dev_meदो_स्मृति_noio(काष्ठा device *dev, व्योम *data)
अणु
	वापस dev->घातer.meदो_स्मृति_noio;
पूर्ण

/*
 * pm_runसमय_set_meदो_स्मृति_noio - Set a device's meदो_स्मृति_noio flag.
 * @dev: Device to handle.
 * @enable: True क्रम setting the flag and False क्रम clearing the flag.
 *
 * Set the flag क्रम all devices in the path from the device to the
 * root device in the device tree अगर @enable is true, otherwise clear
 * the flag क्रम devices in the path whose siblings करोn't set the flag.
 *
 * The function should only be called by block device, or network
 * device driver क्रम solving the deadlock problem during runसमय
 * resume/suspend:
 *
 *     If memory allocation with GFP_KERNEL is called inside runसमय
 *     resume/suspend callback of any one of its ancestors(or the
 *     block device itself), the deadlock may be triggered inside the
 *     memory allocation since it might not complete until the block
 *     device becomes active and the involed page I/O finishes. The
 *     situation is poपूर्णांकed out first by Alan Stern. Network device
 *     are involved in iSCSI kind of situation.
 *
 * The lock of dev_hotplug_mutex is held in the function क्रम handling
 * hotplug race because pm_runसमय_set_meदो_स्मृति_noio() may be called
 * in async probe().
 *
 * The function should be called between device_add() and device_del()
 * on the affected device(block/network device).
 */
व्योम pm_runसमय_set_meदो_स्मृति_noio(काष्ठा device *dev, bool enable)
अणु
	अटल DEFINE_MUTEX(dev_hotplug_mutex);

	mutex_lock(&dev_hotplug_mutex);
	क्रम (;;) अणु
		bool enabled;

		/* hold घातer lock since bitfield is not SMP-safe. */
		spin_lock_irq(&dev->घातer.lock);
		enabled = dev->घातer.meदो_स्मृति_noio;
		dev->घातer.meदो_स्मृति_noio = enable;
		spin_unlock_irq(&dev->घातer.lock);

		/*
		 * not need to enable ancestors any more अगर the device
		 * has been enabled.
		 */
		अगर (enabled && enable)
			अवरोध;

		dev = dev->parent;

		/*
		 * clear flag of the parent device only अगर all the
		 * children करोn't set the flag because ancestor's
		 * flag was set by any one of the descendants.
		 */
		अगर (!dev || (!enable &&
			     device_क्रम_each_child(dev, शून्य,
						   dev_meदो_स्मृति_noio)))
			अवरोध;
	पूर्ण
	mutex_unlock(&dev_hotplug_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_set_meदो_स्मृति_noio);

/**
 * rpm_check_suspend_allowed - Test whether a device may be suspended.
 * @dev: Device to test.
 */
अटल पूर्णांक rpm_check_suspend_allowed(काष्ठा device *dev)
अणु
	पूर्णांक retval = 0;

	अगर (dev->घातer.runसमय_error)
		retval = -EINVAL;
	अन्यथा अगर (dev->घातer.disable_depth > 0)
		retval = -EACCES;
	अन्यथा अगर (atomic_पढ़ो(&dev->घातer.usage_count) > 0)
		retval = -EAGAIN;
	अन्यथा अगर (!dev->घातer.ignore_children &&
			atomic_पढ़ो(&dev->घातer.child_count))
		retval = -EBUSY;

	/* Pending resume requests take precedence over suspends. */
	अन्यथा अगर ((dev->घातer.deferred_resume
			&& dev->घातer.runसमय_status == RPM_SUSPENDING)
	    || (dev->घातer.request_pending
			&& dev->घातer.request == RPM_REQ_RESUME))
		retval = -EAGAIN;
	अन्यथा अगर (__dev_pm_qos_resume_latency(dev) == 0)
		retval = -EPERM;
	अन्यथा अगर (dev->घातer.runसमय_status == RPM_SUSPENDED)
		retval = 1;

	वापस retval;
पूर्ण

अटल पूर्णांक rpm_get_suppliers(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;

	list_क्रम_each_entry_rcu(link, &dev->links.suppliers, c_node,
				device_links_पढ़ो_lock_held()) अणु
		पूर्णांक retval;

		अगर (!(link->flags & DL_FLAG_PM_RUNTIME))
			जारी;

		retval = pm_runसमय_get_sync(link->supplier);
		/* Ignore suppliers with disabled runसमय PM. */
		अगर (retval < 0 && retval != -EACCES) अणु
			pm_runसमय_put_noidle(link->supplier);
			वापस retval;
		पूर्ण
		refcount_inc(&link->rpm_active);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __rpm_put_suppliers(काष्ठा device *dev, bool try_to_suspend)
अणु
	काष्ठा device_link *link;

	list_क्रम_each_entry_rcu(link, &dev->links.suppliers, c_node,
				device_links_पढ़ो_lock_held()) अणु

		जबतक (refcount_dec_not_one(&link->rpm_active))
			pm_runसमय_put_noidle(link->supplier);

		अगर (try_to_suspend)
			pm_request_idle(link->supplier);
	पूर्ण
पूर्ण

अटल व्योम rpm_put_suppliers(काष्ठा device *dev)
अणु
	__rpm_put_suppliers(dev, true);
पूर्ण

अटल व्योम rpm_suspend_suppliers(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;
	पूर्णांक idx = device_links_पढ़ो_lock();

	list_क्रम_each_entry_rcu(link, &dev->links.suppliers, c_node,
				device_links_पढ़ो_lock_held())
		pm_request_idle(link->supplier);

	device_links_पढ़ो_unlock(idx);
पूर्ण

/**
 * __rpm_callback - Run a given runसमय PM callback क्रम a given device.
 * @cb: Runसमय PM callback to run.
 * @dev: Device to run the callback क्रम.
 */
अटल पूर्णांक __rpm_callback(पूर्णांक (*cb)(काष्ठा device *), काष्ठा device *dev)
	__releases(&dev->घातer.lock) __acquires(&dev->घातer.lock)
अणु
	पूर्णांक retval, idx;
	bool use_links = dev->घातer.links_count > 0;

	अगर (dev->घातer.irq_safe) अणु
		spin_unlock(&dev->घातer.lock);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&dev->घातer.lock);

		/*
		 * Resume suppliers अगर necessary.
		 *
		 * The device's runसमय PM status cannot change until this
		 * routine वापसs, so it is safe to पढ़ो the status outside of
		 * the lock.
		 */
		अगर (use_links && dev->घातer.runसमय_status == RPM_RESUMING) अणु
			idx = device_links_पढ़ो_lock();

			retval = rpm_get_suppliers(dev);
			अगर (retval) अणु
				rpm_put_suppliers(dev);
				जाओ fail;
			पूर्ण

			device_links_पढ़ो_unlock(idx);
		पूर्ण
	पूर्ण

	retval = cb(dev);

	अगर (dev->घातer.irq_safe) अणु
		spin_lock(&dev->घातer.lock);
	पूर्ण अन्यथा अणु
		/*
		 * If the device is suspending and the callback has वापसed
		 * success, drop the usage counters of the suppliers that have
		 * been reference counted on its resume.
		 *
		 * Do that अगर resume fails too.
		 */
		अगर (use_links
		    && ((dev->घातer.runसमय_status == RPM_SUSPENDING && !retval)
		    || (dev->घातer.runसमय_status == RPM_RESUMING && retval))) अणु
			idx = device_links_पढ़ो_lock();

			__rpm_put_suppliers(dev, false);

fail:
			device_links_पढ़ो_unlock(idx);
		पूर्ण

		spin_lock_irq(&dev->घातer.lock);
	पूर्ण

	वापस retval;
पूर्ण

/**
 * rpm_idle - Notअगरy device bus type अगर the device can be suspended.
 * @dev: Device to notअगरy the bus type about.
 * @rpmflags: Flag bits.
 *
 * Check अगर the device's runसमय PM status allows it to be suspended.  If
 * another idle notअगरication has been started earlier, वापस immediately.  If
 * the RPM_ASYNC flag is set then queue an idle-notअगरication request; otherwise
 * run the ->runसमय_idle() callback directly. If the ->runसमय_idle callback
 * करोesn't exist or अगर it वापसs 0, call rpm_suspend with the RPM_AUTO flag.
 *
 * This function must be called under dev->घातer.lock with पूर्णांकerrupts disabled.
 */
अटल पूर्णांक rpm_idle(काष्ठा device *dev, पूर्णांक rpmflags)
अणु
	पूर्णांक (*callback)(काष्ठा device *);
	पूर्णांक retval;

	trace_rpm_idle_rcuidle(dev, rpmflags);
	retval = rpm_check_suspend_allowed(dev);
	अगर (retval < 0)
		;	/* Conditions are wrong. */

	/* Idle notअगरications are allowed only in the RPM_ACTIVE state. */
	अन्यथा अगर (dev->घातer.runसमय_status != RPM_ACTIVE)
		retval = -EAGAIN;

	/*
	 * Any pending request other than an idle notअगरication takes
	 * precedence over us, except that the समयr may be running.
	 */
	अन्यथा अगर (dev->घातer.request_pending &&
	    dev->घातer.request > RPM_REQ_IDLE)
		retval = -EAGAIN;

	/* Act as though RPM_NOWAIT is always set. */
	अन्यथा अगर (dev->घातer.idle_notअगरication)
		retval = -EINPROGRESS;
	अगर (retval)
		जाओ out;

	/* Pending requests need to be canceled. */
	dev->घातer.request = RPM_REQ_NONE;

	अगर (dev->घातer.no_callbacks)
		जाओ out;

	/* Carry out an asynchronous or a synchronous idle notअगरication. */
	अगर (rpmflags & RPM_ASYNC) अणु
		dev->घातer.request = RPM_REQ_IDLE;
		अगर (!dev->घातer.request_pending) अणु
			dev->घातer.request_pending = true;
			queue_work(pm_wq, &dev->घातer.work);
		पूर्ण
		trace_rpm_वापस_पूर्णांक_rcuidle(dev, _THIS_IP_, 0);
		वापस 0;
	पूर्ण

	dev->घातer.idle_notअगरication = true;

	callback = RPM_GET_CALLBACK(dev, runसमय_idle);

	अगर (callback)
		retval = __rpm_callback(callback, dev);

	dev->घातer.idle_notअगरication = false;
	wake_up_all(&dev->घातer.रुको_queue);

 out:
	trace_rpm_वापस_पूर्णांक_rcuidle(dev, _THIS_IP_, retval);
	वापस retval ? retval : rpm_suspend(dev, rpmflags | RPM_AUTO);
पूर्ण

/**
 * rpm_callback - Run a given runसमय PM callback क्रम a given device.
 * @cb: Runसमय PM callback to run.
 * @dev: Device to run the callback क्रम.
 */
अटल पूर्णांक rpm_callback(पूर्णांक (*cb)(काष्ठा device *), काष्ठा device *dev)
अणु
	पूर्णांक retval;

	अगर (!cb)
		वापस -ENOSYS;

	अगर (dev->घातer.meदो_स्मृति_noio) अणु
		अचिन्हित पूर्णांक noio_flag;

		/*
		 * Deadlock might be caused अगर memory allocation with
		 * GFP_KERNEL happens inside runसमय_suspend and
		 * runसमय_resume callbacks of one block device's
		 * ancestor or the block device itself. Network
		 * device might be thought as part of iSCSI block
		 * device, so network device and its ancestor should
		 * be marked as meदो_स्मृति_noio too.
		 */
		noio_flag = meदो_स्मृति_noio_save();
		retval = __rpm_callback(cb, dev);
		meदो_स्मृति_noio_restore(noio_flag);
	पूर्ण अन्यथा अणु
		retval = __rpm_callback(cb, dev);
	पूर्ण

	dev->घातer.runसमय_error = retval;
	वापस retval != -EACCES ? retval : -EIO;
पूर्ण

/**
 * rpm_suspend - Carry out runसमय suspend of given device.
 * @dev: Device to suspend.
 * @rpmflags: Flag bits.
 *
 * Check अगर the device's runसमय PM status allows it to be suspended.
 * Cancel a pending idle notअगरication, स्वतःsuspend or suspend. If
 * another suspend has been started earlier, either वापस immediately
 * or रुको क्रम it to finish, depending on the RPM_NOWAIT and RPM_ASYNC
 * flags. If the RPM_ASYNC flag is set then queue a suspend request;
 * otherwise run the ->runसमय_suspend() callback directly. When
 * ->runसमय_suspend succeeded, अगर a deferred resume was requested जबतक
 * the callback was running then carry it out, otherwise send an idle
 * notअगरication क्रम its parent (अगर the suspend succeeded and both
 * ignore_children of parent->घातer and irq_safe of dev->घातer are not set).
 * If ->runसमय_suspend failed with -EAGAIN or -EBUSY, and अगर the RPM_AUTO
 * flag is set and the next स्वतःsuspend-delay expiration समय is in the
 * future, schedule another स्वतःsuspend attempt.
 *
 * This function must be called under dev->घातer.lock with पूर्णांकerrupts disabled.
 */
अटल पूर्णांक rpm_suspend(काष्ठा device *dev, पूर्णांक rpmflags)
	__releases(&dev->घातer.lock) __acquires(&dev->घातer.lock)
अणु
	पूर्णांक (*callback)(काष्ठा device *);
	काष्ठा device *parent = शून्य;
	पूर्णांक retval;

	trace_rpm_suspend_rcuidle(dev, rpmflags);

 repeat:
	retval = rpm_check_suspend_allowed(dev);
	अगर (retval < 0)
		जाओ out;	/* Conditions are wrong. */

	/* Synchronous suspends are not allowed in the RPM_RESUMING state. */
	अगर (dev->घातer.runसमय_status == RPM_RESUMING && !(rpmflags & RPM_ASYNC))
		retval = -EAGAIN;
	अगर (retval)
		जाओ out;

	/* If the स्वतःsuspend_delay समय hasn't expired yet, reschedule. */
	अगर ((rpmflags & RPM_AUTO)
	    && dev->घातer.runसमय_status != RPM_SUSPENDING) अणु
		u64 expires = pm_runसमय_स्वतःsuspend_expiration(dev);

		अगर (expires != 0) अणु
			/* Pending requests need to be canceled. */
			dev->घातer.request = RPM_REQ_NONE;

			/*
			 * Optimization: If the समयr is alपढ़ोy running and is
			 * set to expire at or beक्रमe the स्वतःsuspend delay,
			 * aव्योम the overhead of resetting it.  Just let it
			 * expire; pm_suspend_समयr_fn() will take care of the
			 * rest.
			 */
			अगर (!(dev->घातer.समयr_expires &&
					dev->घातer.समयr_expires <= expires)) अणु
				/*
				 * We add a slack of 25% to gather wakeups
				 * without sacrअगरicing the granularity.
				 */
				u64 slack = (u64)READ_ONCE(dev->घातer.स्वतःsuspend_delay) *
						    (NSEC_PER_MSEC >> 2);

				dev->घातer.समयr_expires = expires;
				hrसमयr_start_range_ns(&dev->घातer.suspend_समयr,
						ns_to_kसमय(expires),
						slack,
						HRTIMER_MODE_ABS);
			पूर्ण
			dev->घातer.समयr_स्वतःsuspends = 1;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Other scheduled or pending requests need to be canceled. */
	pm_runसमय_cancel_pending(dev);

	अगर (dev->घातer.runसमय_status == RPM_SUSPENDING) अणु
		DEFINE_WAIT(रुको);

		अगर (rpmflags & (RPM_ASYNC | RPM_NOWAIT)) अणु
			retval = -EINPROGRESS;
			जाओ out;
		पूर्ण

		अगर (dev->घातer.irq_safe) अणु
			spin_unlock(&dev->घातer.lock);

			cpu_relax();

			spin_lock(&dev->घातer.lock);
			जाओ repeat;
		पूर्ण

		/* Wait क्रम the other suspend running in parallel with us. */
		क्रम (;;) अणु
			prepare_to_रुको(&dev->घातer.रुको_queue, &रुको,
					TASK_UNINTERRUPTIBLE);
			अगर (dev->घातer.runसमय_status != RPM_SUSPENDING)
				अवरोध;

			spin_unlock_irq(&dev->घातer.lock);

			schedule();

			spin_lock_irq(&dev->घातer.lock);
		पूर्ण
		finish_रुको(&dev->घातer.रुको_queue, &रुको);
		जाओ repeat;
	पूर्ण

	अगर (dev->घातer.no_callbacks)
		जाओ no_callback;	/* Assume success. */

	/* Carry out an asynchronous or a synchronous suspend. */
	अगर (rpmflags & RPM_ASYNC) अणु
		dev->घातer.request = (rpmflags & RPM_AUTO) ?
		    RPM_REQ_AUTOSUSPEND : RPM_REQ_SUSPEND;
		अगर (!dev->घातer.request_pending) अणु
			dev->घातer.request_pending = true;
			queue_work(pm_wq, &dev->घातer.work);
		पूर्ण
		जाओ out;
	पूर्ण

	__update_runसमय_status(dev, RPM_SUSPENDING);

	callback = RPM_GET_CALLBACK(dev, runसमय_suspend);

	dev_pm_enable_wake_irq_check(dev, true);
	retval = rpm_callback(callback, dev);
	अगर (retval)
		जाओ fail;

 no_callback:
	__update_runसमय_status(dev, RPM_SUSPENDED);
	pm_runसमय_deactivate_समयr(dev);

	अगर (dev->parent) अणु
		parent = dev->parent;
		atomic_add_unless(&parent->घातer.child_count, -1, 0);
	पूर्ण
	wake_up_all(&dev->घातer.रुको_queue);

	अगर (dev->घातer.deferred_resume) अणु
		dev->घातer.deferred_resume = false;
		rpm_resume(dev, 0);
		retval = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (dev->घातer.irq_safe)
		जाओ out;

	/* Maybe the parent is now able to suspend. */
	अगर (parent && !parent->घातer.ignore_children) अणु
		spin_unlock(&dev->घातer.lock);

		spin_lock(&parent->घातer.lock);
		rpm_idle(parent, RPM_ASYNC);
		spin_unlock(&parent->घातer.lock);

		spin_lock(&dev->घातer.lock);
	पूर्ण
	/* Maybe the suppliers are now able to suspend. */
	अगर (dev->घातer.links_count > 0) अणु
		spin_unlock_irq(&dev->घातer.lock);

		rpm_suspend_suppliers(dev);

		spin_lock_irq(&dev->घातer.lock);
	पूर्ण

 out:
	trace_rpm_वापस_पूर्णांक_rcuidle(dev, _THIS_IP_, retval);

	वापस retval;

 fail:
	dev_pm_disable_wake_irq_check(dev);
	__update_runसमय_status(dev, RPM_ACTIVE);
	dev->घातer.deferred_resume = false;
	wake_up_all(&dev->घातer.रुको_queue);

	अगर (retval == -EAGAIN || retval == -EBUSY) अणु
		dev->घातer.runसमय_error = 0;

		/*
		 * If the callback routine failed an स्वतःsuspend, and
		 * अगर the last_busy समय has been updated so that there
		 * is a new स्वतःsuspend expiration समय, स्वतःmatically
		 * reschedule another स्वतःsuspend.
		 */
		अगर ((rpmflags & RPM_AUTO) &&
		    pm_runसमय_स्वतःsuspend_expiration(dev) != 0)
			जाओ repeat;
	पूर्ण अन्यथा अणु
		pm_runसमय_cancel_pending(dev);
	पूर्ण
	जाओ out;
पूर्ण

/**
 * rpm_resume - Carry out runसमय resume of given device.
 * @dev: Device to resume.
 * @rpmflags: Flag bits.
 *
 * Check अगर the device's runसमय PM status allows it to be resumed.  Cancel
 * any scheduled or pending requests.  If another resume has been started
 * earlier, either वापस immediately or रुको क्रम it to finish, depending on the
 * RPM_NOWAIT and RPM_ASYNC flags.  Similarly, अगर there's a suspend running in
 * parallel with this function, either tell the other process to resume after
 * suspending (deferred_resume) or रुको क्रम it to finish.  If the RPM_ASYNC
 * flag is set then queue a resume request; otherwise run the
 * ->runसमय_resume() callback directly.  Queue an idle notअगरication क्रम the
 * device अगर the resume succeeded.
 *
 * This function must be called under dev->घातer.lock with पूर्णांकerrupts disabled.
 */
अटल पूर्णांक rpm_resume(काष्ठा device *dev, पूर्णांक rpmflags)
	__releases(&dev->घातer.lock) __acquires(&dev->घातer.lock)
अणु
	पूर्णांक (*callback)(काष्ठा device *);
	काष्ठा device *parent = शून्य;
	पूर्णांक retval = 0;

	trace_rpm_resume_rcuidle(dev, rpmflags);

 repeat:
	अगर (dev->घातer.runसमय_error)
		retval = -EINVAL;
	अन्यथा अगर (dev->घातer.disable_depth == 1 && dev->घातer.is_suspended
	    && dev->घातer.runसमय_status == RPM_ACTIVE)
		retval = 1;
	अन्यथा अगर (dev->घातer.disable_depth > 0)
		retval = -EACCES;
	अगर (retval)
		जाओ out;

	/*
	 * Other scheduled or pending requests need to be canceled.  Small
	 * optimization: If an स्वतःsuspend समयr is running, leave it running
	 * rather than cancelling it now only to restart it again in the near
	 * future.
	 */
	dev->घातer.request = RPM_REQ_NONE;
	अगर (!dev->घातer.समयr_स्वतःsuspends)
		pm_runसमय_deactivate_समयr(dev);

	अगर (dev->घातer.runसमय_status == RPM_ACTIVE) अणु
		retval = 1;
		जाओ out;
	पूर्ण

	अगर (dev->घातer.runसमय_status == RPM_RESUMING
	    || dev->घातer.runसमय_status == RPM_SUSPENDING) अणु
		DEFINE_WAIT(रुको);

		अगर (rpmflags & (RPM_ASYNC | RPM_NOWAIT)) अणु
			अगर (dev->घातer.runसमय_status == RPM_SUSPENDING)
				dev->घातer.deferred_resume = true;
			अन्यथा
				retval = -EINPROGRESS;
			जाओ out;
		पूर्ण

		अगर (dev->घातer.irq_safe) अणु
			spin_unlock(&dev->घातer.lock);

			cpu_relax();

			spin_lock(&dev->घातer.lock);
			जाओ repeat;
		पूर्ण

		/* Wait क्रम the operation carried out in parallel with us. */
		क्रम (;;) अणु
			prepare_to_रुको(&dev->घातer.रुको_queue, &रुको,
					TASK_UNINTERRUPTIBLE);
			अगर (dev->घातer.runसमय_status != RPM_RESUMING
			    && dev->घातer.runसमय_status != RPM_SUSPENDING)
				अवरोध;

			spin_unlock_irq(&dev->घातer.lock);

			schedule();

			spin_lock_irq(&dev->घातer.lock);
		पूर्ण
		finish_रुको(&dev->घातer.रुको_queue, &रुको);
		जाओ repeat;
	पूर्ण

	/*
	 * See अगर we can skip waking up the parent.  This is safe only अगर
	 * घातer.no_callbacks is set, because otherwise we करोn't know whether
	 * the resume will actually succeed.
	 */
	अगर (dev->घातer.no_callbacks && !parent && dev->parent) अणु
		spin_lock_nested(&dev->parent->घातer.lock, SINGLE_DEPTH_NESTING);
		अगर (dev->parent->घातer.disable_depth > 0
		    || dev->parent->घातer.ignore_children
		    || dev->parent->घातer.runसमय_status == RPM_ACTIVE) अणु
			atomic_inc(&dev->parent->घातer.child_count);
			spin_unlock(&dev->parent->घातer.lock);
			retval = 1;
			जाओ no_callback;	/* Assume success. */
		पूर्ण
		spin_unlock(&dev->parent->घातer.lock);
	पूर्ण

	/* Carry out an asynchronous or a synchronous resume. */
	अगर (rpmflags & RPM_ASYNC) अणु
		dev->घातer.request = RPM_REQ_RESUME;
		अगर (!dev->घातer.request_pending) अणु
			dev->घातer.request_pending = true;
			queue_work(pm_wq, &dev->घातer.work);
		पूर्ण
		retval = 0;
		जाओ out;
	पूर्ण

	अगर (!parent && dev->parent) अणु
		/*
		 * Increment the parent's usage counter and resume it अगर
		 * necessary.  Not needed अगर dev is irq-safe; then the
		 * parent is permanently resumed.
		 */
		parent = dev->parent;
		अगर (dev->घातer.irq_safe)
			जाओ skip_parent;
		spin_unlock(&dev->घातer.lock);

		pm_runसमय_get_noresume(parent);

		spin_lock(&parent->घातer.lock);
		/*
		 * Resume the parent अगर it has runसमय PM enabled and not been
		 * set to ignore its children.
		 */
		अगर (!parent->घातer.disable_depth
		    && !parent->घातer.ignore_children) अणु
			rpm_resume(parent, 0);
			अगर (parent->घातer.runसमय_status != RPM_ACTIVE)
				retval = -EBUSY;
		पूर्ण
		spin_unlock(&parent->घातer.lock);

		spin_lock(&dev->घातer.lock);
		अगर (retval)
			जाओ out;
		जाओ repeat;
	पूर्ण
 skip_parent:

	अगर (dev->घातer.no_callbacks)
		जाओ no_callback;	/* Assume success. */

	__update_runसमय_status(dev, RPM_RESUMING);

	callback = RPM_GET_CALLBACK(dev, runसमय_resume);

	dev_pm_disable_wake_irq_check(dev);
	retval = rpm_callback(callback, dev);
	अगर (retval) अणु
		__update_runसमय_status(dev, RPM_SUSPENDED);
		pm_runसमय_cancel_pending(dev);
		dev_pm_enable_wake_irq_check(dev, false);
	पूर्ण अन्यथा अणु
 no_callback:
		__update_runसमय_status(dev, RPM_ACTIVE);
		pm_runसमय_mark_last_busy(dev);
		अगर (parent)
			atomic_inc(&parent->घातer.child_count);
	पूर्ण
	wake_up_all(&dev->घातer.रुको_queue);

	अगर (retval >= 0)
		rpm_idle(dev, RPM_ASYNC);

 out:
	अगर (parent && !dev->घातer.irq_safe) अणु
		spin_unlock_irq(&dev->घातer.lock);

		pm_runसमय_put(parent);

		spin_lock_irq(&dev->घातer.lock);
	पूर्ण

	trace_rpm_वापस_पूर्णांक_rcuidle(dev, _THIS_IP_, retval);

	वापस retval;
पूर्ण

/**
 * pm_runसमय_work - Universal runसमय PM work function.
 * @work: Work काष्ठाure used क्रम scheduling the execution of this function.
 *
 * Use @work to get the device object the work is to be करोne क्रम, determine what
 * is to be करोne and execute the appropriate runसमय PM function.
 */
अटल व्योम pm_runसमय_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा device *dev = container_of(work, काष्ठा device, घातer.work);
	क्रमागत rpm_request req;

	spin_lock_irq(&dev->घातer.lock);

	अगर (!dev->घातer.request_pending)
		जाओ out;

	req = dev->घातer.request;
	dev->घातer.request = RPM_REQ_NONE;
	dev->घातer.request_pending = false;

	चयन (req) अणु
	हाल RPM_REQ_NONE:
		अवरोध;
	हाल RPM_REQ_IDLE:
		rpm_idle(dev, RPM_NOWAIT);
		अवरोध;
	हाल RPM_REQ_SUSPEND:
		rpm_suspend(dev, RPM_NOWAIT);
		अवरोध;
	हाल RPM_REQ_AUTOSUSPEND:
		rpm_suspend(dev, RPM_NOWAIT | RPM_AUTO);
		अवरोध;
	हाल RPM_REQ_RESUME:
		rpm_resume(dev, RPM_NOWAIT);
		अवरोध;
	पूर्ण

 out:
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण

/**
 * pm_suspend_समयr_fn - Timer function क्रम pm_schedule_suspend().
 * @समयr: hrसमयr used by pm_schedule_suspend().
 *
 * Check अगर the समय is right and queue a suspend request.
 */
अटल क्रमागत hrसमयr_restart  pm_suspend_समयr_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा device *dev = container_of(समयr, काष्ठा device, घातer.suspend_समयr);
	अचिन्हित दीर्घ flags;
	u64 expires;

	spin_lock_irqsave(&dev->घातer.lock, flags);

	expires = dev->घातer.समयr_expires;
	/*
	 * If 'expires' is after the current time, we've been called
	 * too early.
	 */
	अगर (expires > 0 && expires < kसमय_get_mono_fast_ns()) अणु
		dev->घातer.समयr_expires = 0;
		rpm_suspend(dev, dev->घातer.समयr_स्वतःsuspends ?
		    (RPM_ASYNC | RPM_AUTO) : RPM_ASYNC);
	पूर्ण

	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	वापस HRTIMER_NORESTART;
पूर्ण

/**
 * pm_schedule_suspend - Set up a समयr to submit a suspend request in future.
 * @dev: Device to suspend.
 * @delay: Time to रुको beक्रमe submitting a suspend request, in milliseconds.
 */
पूर्णांक pm_schedule_suspend(काष्ठा device *dev, अचिन्हित पूर्णांक delay)
अणु
	अचिन्हित दीर्घ flags;
	u64 expires;
	पूर्णांक retval;

	spin_lock_irqsave(&dev->घातer.lock, flags);

	अगर (!delay) अणु
		retval = rpm_suspend(dev, RPM_ASYNC);
		जाओ out;
	पूर्ण

	retval = rpm_check_suspend_allowed(dev);
	अगर (retval)
		जाओ out;

	/* Other scheduled or pending requests need to be canceled. */
	pm_runसमय_cancel_pending(dev);

	expires = kसमय_get_mono_fast_ns() + (u64)delay * NSEC_PER_MSEC;
	dev->घातer.समयr_expires = expires;
	dev->घातer.समयr_स्वतःsuspends = 0;
	hrसमयr_start(&dev->घातer.suspend_समयr, expires, HRTIMER_MODE_ABS);

 out:
	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(pm_schedule_suspend);

/**
 * __pm_runसमय_idle - Entry poपूर्णांक क्रम runसमय idle operations.
 * @dev: Device to send idle notअगरication क्रम.
 * @rpmflags: Flag bits.
 *
 * If the RPM_GET_PUT flag is set, decrement the device's usage count and
 * वापस immediately अगर it is larger than zero.  Then carry out an idle
 * notअगरication, either synchronous or asynchronous.
 *
 * This routine may be called in atomic context अगर the RPM_ASYNC flag is set,
 * or अगर pm_runसमय_irq_safe() has been called.
 */
पूर्णांक __pm_runसमय_idle(काष्ठा device *dev, पूर्णांक rpmflags)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (rpmflags & RPM_GET_PUT) अणु
		अगर (!atomic_dec_and_test(&dev->घातer.usage_count)) अणु
			trace_rpm_usage_rcuidle(dev, rpmflags);
			वापस 0;
		पूर्ण
	पूर्ण

	might_sleep_अगर(!(rpmflags & RPM_ASYNC) && !dev->घातer.irq_safe);

	spin_lock_irqsave(&dev->घातer.lock, flags);
	retval = rpm_idle(dev, rpmflags);
	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(__pm_runसमय_idle);

/**
 * __pm_runसमय_suspend - Entry poपूर्णांक क्रम runसमय put/suspend operations.
 * @dev: Device to suspend.
 * @rpmflags: Flag bits.
 *
 * If the RPM_GET_PUT flag is set, decrement the device's usage count and
 * वापस immediately अगर it is larger than zero.  Then carry out a suspend,
 * either synchronous or asynchronous.
 *
 * This routine may be called in atomic context अगर the RPM_ASYNC flag is set,
 * or अगर pm_runसमय_irq_safe() has been called.
 */
पूर्णांक __pm_runसमय_suspend(काष्ठा device *dev, पूर्णांक rpmflags)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (rpmflags & RPM_GET_PUT) अणु
		अगर (!atomic_dec_and_test(&dev->घातer.usage_count)) अणु
			trace_rpm_usage_rcuidle(dev, rpmflags);
			वापस 0;
		पूर्ण
	पूर्ण

	might_sleep_अगर(!(rpmflags & RPM_ASYNC) && !dev->घातer.irq_safe);

	spin_lock_irqsave(&dev->घातer.lock, flags);
	retval = rpm_suspend(dev, rpmflags);
	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(__pm_runसमय_suspend);

/**
 * __pm_runसमय_resume - Entry poपूर्णांक क्रम runसमय resume operations.
 * @dev: Device to resume.
 * @rpmflags: Flag bits.
 *
 * If the RPM_GET_PUT flag is set, increment the device's usage count.  Then
 * carry out a resume, either synchronous or asynchronous.
 *
 * This routine may be called in atomic context अगर the RPM_ASYNC flag is set,
 * or अगर pm_runसमय_irq_safe() has been called.
 */
पूर्णांक __pm_runसमय_resume(काष्ठा device *dev, पूर्णांक rpmflags)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	might_sleep_अगर(!(rpmflags & RPM_ASYNC) && !dev->घातer.irq_safe &&
			dev->घातer.runसमय_status != RPM_ACTIVE);

	अगर (rpmflags & RPM_GET_PUT)
		atomic_inc(&dev->घातer.usage_count);

	spin_lock_irqsave(&dev->घातer.lock, flags);
	retval = rpm_resume(dev, rpmflags);
	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(__pm_runसमय_resume);

/**
 * pm_runसमय_get_अगर_active - Conditionally bump up device usage counter.
 * @dev: Device to handle.
 * @ign_usage_count: Whether or not to look at the current usage counter value.
 *
 * Return -EINVAL अगर runसमय PM is disabled क्रम @dev.
 *
 * Otherwise, अगर the runसमय PM status of @dev is %RPM_ACTIVE and either
 * @ign_usage_count is %true or the runसमय PM usage counter of @dev is not
 * zero, increment the usage counter of @dev and वापस 1. Otherwise, वापस 0
 * without changing the usage counter.
 *
 * If @ign_usage_count is %true, this function can be used to prevent suspending
 * the device when its runसमय PM status is %RPM_ACTIVE.
 *
 * If @ign_usage_count is %false, this function can be used to prevent
 * suspending the device when both its runसमय PM status is %RPM_ACTIVE and its
 * runसमय PM usage counter is not zero.
 *
 * The caller is responsible क्रम decrementing the runसमय PM usage counter of
 * @dev after this function has वापसed a positive value क्रम it.
 */
पूर्णांक pm_runसमय_get_अगर_active(काष्ठा device *dev, bool ign_usage_count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&dev->घातer.lock, flags);
	अगर (dev->घातer.disable_depth > 0) अणु
		retval = -EINVAL;
	पूर्ण अन्यथा अगर (dev->घातer.runसमय_status != RPM_ACTIVE) अणु
		retval = 0;
	पूर्ण अन्यथा अगर (ign_usage_count) अणु
		retval = 1;
		atomic_inc(&dev->घातer.usage_count);
	पूर्ण अन्यथा अणु
		retval = atomic_inc_not_zero(&dev->घातer.usage_count);
	पूर्ण
	trace_rpm_usage_rcuidle(dev, 0);
	spin_unlock_irqrestore(&dev->घातer.lock, flags);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_get_अगर_active);

/**
 * __pm_runसमय_set_status - Set runसमय PM status of a device.
 * @dev: Device to handle.
 * @status: New runसमय PM status of the device.
 *
 * If runसमय PM of the device is disabled or its घातer.runसमय_error field is
 * dअगरferent from zero, the status may be changed either to RPM_ACTIVE, or to
 * RPM_SUSPENDED, as दीर्घ as that reflects the actual state of the device.
 * However, अगर the device has a parent and the parent is not active, and the
 * parent's power.ignore_children flag is unset, the device's status cannot be
 * set to RPM_ACTIVE, so -EBUSY is वापसed in that हाल.
 *
 * If successful, __pm_runसमय_set_status() clears the घातer.runसमय_error field
 * and the device parent's counter of unsuspended children is modअगरied to
 * reflect the new status.  If the new status is RPM_SUSPENDED, an idle
 * notअगरication request क्रम the parent is submitted.
 *
 * If @dev has any suppliers (as reflected by device links to them), and @status
 * is RPM_ACTIVE, they will be activated upfront and अगर the activation of one
 * of them fails, the status of @dev will be changed to RPM_SUSPENDED (instead
 * of the @status value) and the suppliers will be deacticated on निकास.  The
 * error वापसed by the failing supplier activation will be वापसed in that
 * हाल.
 */
पूर्णांक __pm_runसमय_set_status(काष्ठा device *dev, अचिन्हित पूर्णांक status)
अणु
	काष्ठा device *parent = dev->parent;
	bool notअगरy_parent = false;
	पूर्णांक error = 0;

	अगर (status != RPM_ACTIVE && status != RPM_SUSPENDED)
		वापस -EINVAL;

	spin_lock_irq(&dev->घातer.lock);

	/*
	 * Prevent PM-runसमय from being enabled क्रम the device or वापस an
	 * error अगर it is enabled alपढ़ोy and working.
	 */
	अगर (dev->घातer.runसमय_error || dev->घातer.disable_depth)
		dev->घातer.disable_depth++;
	अन्यथा
		error = -EAGAIN;

	spin_unlock_irq(&dev->घातer.lock);

	अगर (error)
		वापस error;

	/*
	 * If the new status is RPM_ACTIVE, the suppliers can be activated
	 * upfront regardless of the current status, because next समय
	 * rpm_put_suppliers() runs, the rpm_active refcounts of the links
	 * involved will be dropped करोwn to one anyway.
	 */
	अगर (status == RPM_ACTIVE) अणु
		पूर्णांक idx = device_links_पढ़ो_lock();

		error = rpm_get_suppliers(dev);
		अगर (error)
			status = RPM_SUSPENDED;

		device_links_पढ़ो_unlock(idx);
	पूर्ण

	spin_lock_irq(&dev->घातer.lock);

	अगर (dev->घातer.runसमय_status == status || !parent)
		जाओ out_set;

	अगर (status == RPM_SUSPENDED) अणु
		atomic_add_unless(&parent->घातer.child_count, -1, 0);
		notअगरy_parent = !parent->घातer.ignore_children;
	पूर्ण अन्यथा अणु
		spin_lock_nested(&parent->घातer.lock, SINGLE_DEPTH_NESTING);

		/*
		 * It is invalid to put an active child under a parent that is
		 * not active, has runसमय PM enabled and the
		 * 'power.ignore_children' flag unset.
		 */
		अगर (!parent->घातer.disable_depth
		    && !parent->घातer.ignore_children
		    && parent->घातer.runसमय_status != RPM_ACTIVE) अणु
			dev_err(dev, "runtime PM trying to activate child device %s but parent (%s) is not active\n",
				dev_name(dev),
				dev_name(parent));
			error = -EBUSY;
		पूर्ण अन्यथा अगर (dev->घातer.runसमय_status == RPM_SUSPENDED) अणु
			atomic_inc(&parent->घातer.child_count);
		पूर्ण

		spin_unlock(&parent->घातer.lock);

		अगर (error) अणु
			status = RPM_SUSPENDED;
			जाओ out;
		पूर्ण
	पूर्ण

 out_set:
	__update_runसमय_status(dev, status);
	अगर (!error)
		dev->घातer.runसमय_error = 0;

 out:
	spin_unlock_irq(&dev->घातer.lock);

	अगर (notअगरy_parent)
		pm_request_idle(parent);

	अगर (status == RPM_SUSPENDED) अणु
		पूर्णांक idx = device_links_पढ़ो_lock();

		rpm_put_suppliers(dev);

		device_links_पढ़ो_unlock(idx);
	पूर्ण

	pm_runसमय_enable(dev);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(__pm_runसमय_set_status);

/**
 * __pm_runसमय_barrier - Cancel pending requests and रुको क्रम completions.
 * @dev: Device to handle.
 *
 * Flush all pending requests क्रम the device from pm_wq and रुको क्रम all
 * runसमय PM operations involving the device in progress to complete.
 *
 * Should be called under dev->घातer.lock with पूर्णांकerrupts disabled.
 */
अटल व्योम __pm_runसमय_barrier(काष्ठा device *dev)
अणु
	pm_runसमय_deactivate_समयr(dev);

	अगर (dev->घातer.request_pending) अणु
		dev->घातer.request = RPM_REQ_NONE;
		spin_unlock_irq(&dev->घातer.lock);

		cancel_work_sync(&dev->घातer.work);

		spin_lock_irq(&dev->घातer.lock);
		dev->घातer.request_pending = false;
	पूर्ण

	अगर (dev->घातer.runसमय_status == RPM_SUSPENDING
	    || dev->घातer.runसमय_status == RPM_RESUMING
	    || dev->घातer.idle_notअगरication) अणु
		DEFINE_WAIT(रुको);

		/* Suspend, wake-up or idle notअगरication in progress. */
		क्रम (;;) अणु
			prepare_to_रुको(&dev->घातer.रुको_queue, &रुको,
					TASK_UNINTERRUPTIBLE);
			अगर (dev->घातer.runसमय_status != RPM_SUSPENDING
			    && dev->घातer.runसमय_status != RPM_RESUMING
			    && !dev->घातer.idle_notअगरication)
				अवरोध;
			spin_unlock_irq(&dev->घातer.lock);

			schedule();

			spin_lock_irq(&dev->घातer.lock);
		पूर्ण
		finish_रुको(&dev->घातer.रुको_queue, &रुको);
	पूर्ण
पूर्ण

/**
 * pm_runसमय_barrier - Flush pending requests and रुको क्रम completions.
 * @dev: Device to handle.
 *
 * Prevent the device from being suspended by incrementing its usage counter and
 * अगर there's a pending resume request क्रम the device, wake the device up.
 * Next, make sure that all pending requests क्रम the device have been flushed
 * from pm_wq and रुको क्रम all runसमय PM operations involving the device in
 * progress to complete.
 *
 * Return value:
 * 1, अगर there was a resume request pending and the device had to be woken up,
 * 0, otherwise
 */
पूर्णांक pm_runसमय_barrier(काष्ठा device *dev)
अणु
	पूर्णांक retval = 0;

	pm_runसमय_get_noresume(dev);
	spin_lock_irq(&dev->घातer.lock);

	अगर (dev->घातer.request_pending
	    && dev->घातer.request == RPM_REQ_RESUME) अणु
		rpm_resume(dev, 0);
		retval = 1;
	पूर्ण

	__pm_runसमय_barrier(dev);

	spin_unlock_irq(&dev->घातer.lock);
	pm_runसमय_put_noidle(dev);

	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_barrier);

/**
 * __pm_runसमय_disable - Disable runसमय PM of a device.
 * @dev: Device to handle.
 * @check_resume: If set, check अगर there's a resume request क्रम the device.
 *
 * Increment घातer.disable_depth क्रम the device and अगर it was zero previously,
 * cancel all pending runसमय PM requests क्रम the device and रुको क्रम all
 * operations in progress to complete.  The device can be either active or
 * suspended after its runसमय PM has been disabled.
 *
 * If @check_resume is set and there's a resume request pending when
 * __pm_runसमय_disable() is called and घातer.disable_depth is zero, the
 * function will wake up the device beक्रमe disabling its runसमय PM.
 */
व्योम __pm_runसमय_disable(काष्ठा device *dev, bool check_resume)
अणु
	spin_lock_irq(&dev->घातer.lock);

	अगर (dev->घातer.disable_depth > 0) अणु
		dev->घातer.disable_depth++;
		जाओ out;
	पूर्ण

	/*
	 * Wake up the device अगर there's a resume request pending, because that
	 * means there probably is some I/O to process and disabling runसमय PM
	 * shouldn't prevent the device from processing the I/O.
	 */
	अगर (check_resume && dev->घातer.request_pending
	    && dev->घातer.request == RPM_REQ_RESUME) अणु
		/*
		 * Prevent suspends and idle notअगरications from being carried
		 * out after we have woken up the device.
		 */
		pm_runसमय_get_noresume(dev);

		rpm_resume(dev, 0);

		pm_runसमय_put_noidle(dev);
	पूर्ण

	/* Update समय accounting beक्रमe disabling PM-runसमय. */
	update_pm_runसमय_accounting(dev);

	अगर (!dev->घातer.disable_depth++)
		__pm_runसमय_barrier(dev);

 out:
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण
EXPORT_SYMBOL_GPL(__pm_runसमय_disable);

/**
 * pm_runसमय_enable - Enable runसमय PM of a device.
 * @dev: Device to handle.
 */
व्योम pm_runसमय_enable(काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->घातer.lock, flags);

	अगर (dev->घातer.disable_depth > 0) अणु
		dev->घातer.disable_depth--;

		/* About to enable runसमय pm, set accounting_बारtamp to now */
		अगर (!dev->घातer.disable_depth)
			dev->घातer.accounting_बारtamp = kसमय_get_mono_fast_ns();
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Unbalanced %s!\n", __func__);
	पूर्ण

	WARN(!dev->घातer.disable_depth &&
	     dev->घातer.runसमय_status == RPM_SUSPENDED &&
	     !dev->घातer.ignore_children &&
	     atomic_पढ़ो(&dev->घातer.child_count) > 0,
	     "Enabling runtime PM for inactive device (%s) with active children\n",
	     dev_name(dev));

	spin_unlock_irqrestore(&dev->घातer.lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_enable);

/**
 * pm_runसमय_क्रमbid - Block runसमय PM of a device.
 * @dev: Device to handle.
 *
 * Increase the device's usage count and clear its घातer.runसमय_स्वतः flag,
 * so that it cannot be suspended at run समय until pm_runसमय_allow() is called
 * क्रम it.
 */
व्योम pm_runसमय_क्रमbid(काष्ठा device *dev)
अणु
	spin_lock_irq(&dev->घातer.lock);
	अगर (!dev->घातer.runसमय_स्वतः)
		जाओ out;

	dev->घातer.runसमय_स्वतः = false;
	atomic_inc(&dev->घातer.usage_count);
	rpm_resume(dev, 0);

 out:
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_क्रमbid);

/**
 * pm_runसमय_allow - Unblock runसमय PM of a device.
 * @dev: Device to handle.
 *
 * Decrease the device's usage count and set its घातer.runसमय_स्वतः flag.
 */
व्योम pm_runसमय_allow(काष्ठा device *dev)
अणु
	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.runसमय_स्वतः)
		जाओ out;

	dev->घातer.runसमय_स्वतः = true;
	अगर (atomic_dec_and_test(&dev->घातer.usage_count))
		rpm_idle(dev, RPM_AUTO | RPM_ASYNC);
	अन्यथा
		trace_rpm_usage_rcuidle(dev, RPM_AUTO | RPM_ASYNC);

 out:
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_allow);

/**
 * pm_runसमय_no_callbacks - Ignore runसमय PM callbacks क्रम a device.
 * @dev: Device to handle.
 *
 * Set the घातer.no_callbacks flag, which tells the PM core that this
 * device is घातer-managed through its parent and has no runसमय PM
 * callbacks of its own.  The runसमय sysfs attributes will be हटाओd.
 */
व्योम pm_runसमय_no_callbacks(काष्ठा device *dev)
अणु
	spin_lock_irq(&dev->घातer.lock);
	dev->घातer.no_callbacks = 1;
	spin_unlock_irq(&dev->घातer.lock);
	अगर (device_is_रेजिस्टरed(dev))
		rpm_sysfs_हटाओ(dev);
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_no_callbacks);

/**
 * pm_runसमय_irq_safe - Leave पूर्णांकerrupts disabled during callbacks.
 * @dev: Device to handle
 *
 * Set the घातer.irq_safe flag, which tells the PM core that the
 * ->runसमय_suspend() and ->runसमय_resume() callbacks क्रम this device should
 * always be invoked with the spinlock held and पूर्णांकerrupts disabled.  It also
 * causes the parent's usage counter to be permanently incremented, preventing
 * the parent from runसमय suspending -- otherwise an irq-safe child might have
 * to रुको क्रम a non-irq-safe parent.
 */
व्योम pm_runसमय_irq_safe(काष्ठा device *dev)
अणु
	अगर (dev->parent)
		pm_runसमय_get_sync(dev->parent);
	spin_lock_irq(&dev->घातer.lock);
	dev->घातer.irq_safe = 1;
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_irq_safe);

/**
 * update_स्वतःsuspend - Handle a change to a device's स्वतःsuspend settings.
 * @dev: Device to handle.
 * @old_delay: The क्रमmer स्वतःsuspend_delay value.
 * @old_use: The क्रमmer use_स्वतःsuspend value.
 *
 * Prevent runसमय suspend अगर the new delay is negative and use_स्वतःsuspend is
 * set; otherwise allow it.  Send an idle notअगरication अगर suspends are allowed.
 *
 * This function must be called under dev->घातer.lock with पूर्णांकerrupts disabled.
 */
अटल व्योम update_स्वतःsuspend(काष्ठा device *dev, पूर्णांक old_delay, पूर्णांक old_use)
अणु
	पूर्णांक delay = dev->घातer.स्वतःsuspend_delay;

	/* Should runसमय suspend be prevented now? */
	अगर (dev->घातer.use_स्वतःsuspend && delay < 0) अणु

		/* If it used to be allowed then prevent it. */
		अगर (!old_use || old_delay >= 0) अणु
			atomic_inc(&dev->घातer.usage_count);
			rpm_resume(dev, 0);
		पूर्ण अन्यथा अणु
			trace_rpm_usage_rcuidle(dev, 0);
		पूर्ण
	पूर्ण

	/* Runसमय suspend should be allowed now. */
	अन्यथा अणु

		/* If it used to be prevented then allow it. */
		अगर (old_use && old_delay < 0)
			atomic_dec(&dev->घातer.usage_count);

		/* Maybe we can स्वतःsuspend now. */
		rpm_idle(dev, RPM_AUTO);
	पूर्ण
पूर्ण

/**
 * pm_runसमय_set_स्वतःsuspend_delay - Set a device's स्वतःsuspend_delay value.
 * @dev: Device to handle.
 * @delay: Value of the new delay in milliseconds.
 *
 * Set the device's घातer.स्वतःsuspend_delay value.  If it changes to negative
 * and the घातer.use_स्वतःsuspend flag is set, prevent runसमय suspends.  If it
 * changes the other way, allow runसमय suspends.
 */
व्योम pm_runसमय_set_स्वतःsuspend_delay(काष्ठा device *dev, पूर्णांक delay)
अणु
	पूर्णांक old_delay, old_use;

	spin_lock_irq(&dev->घातer.lock);
	old_delay = dev->घातer.स्वतःsuspend_delay;
	old_use = dev->घातer.use_स्वतःsuspend;
	dev->घातer.स्वतःsuspend_delay = delay;
	update_स्वतःsuspend(dev, old_delay, old_use);
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_set_स्वतःsuspend_delay);

/**
 * __pm_runसमय_use_स्वतःsuspend - Set a device's use_स्वतःsuspend flag.
 * @dev: Device to handle.
 * @use: New value क्रम use_स्वतःsuspend.
 *
 * Set the device's घातer.use_स्वतःsuspend flag, and allow or prevent runसमय
 * suspends as needed.
 */
व्योम __pm_runसमय_use_स्वतःsuspend(काष्ठा device *dev, bool use)
अणु
	पूर्णांक old_delay, old_use;

	spin_lock_irq(&dev->घातer.lock);
	old_delay = dev->घातer.स्वतःsuspend_delay;
	old_use = dev->घातer.use_स्वतःsuspend;
	dev->घातer.use_स्वतःsuspend = use;
	update_स्वतःsuspend(dev, old_delay, old_use);
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण
EXPORT_SYMBOL_GPL(__pm_runसमय_use_स्वतःsuspend);

/**
 * pm_runसमय_init - Initialize runसमय PM fields in given device object.
 * @dev: Device object to initialize.
 */
व्योम pm_runसमय_init(काष्ठा device *dev)
अणु
	dev->घातer.runसमय_status = RPM_SUSPENDED;
	dev->घातer.idle_notअगरication = false;

	dev->घातer.disable_depth = 1;
	atomic_set(&dev->घातer.usage_count, 0);

	dev->घातer.runसमय_error = 0;

	atomic_set(&dev->घातer.child_count, 0);
	pm_suspend_ignore_children(dev, false);
	dev->घातer.runसमय_स्वतः = true;

	dev->घातer.request_pending = false;
	dev->घातer.request = RPM_REQ_NONE;
	dev->घातer.deferred_resume = false;
	dev->घातer.needs_क्रमce_resume = 0;
	INIT_WORK(&dev->घातer.work, pm_runसमय_work);

	dev->घातer.समयr_expires = 0;
	hrसमयr_init(&dev->घातer.suspend_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	dev->घातer.suspend_समयr.function = pm_suspend_समयr_fn;

	init_रुकोqueue_head(&dev->घातer.रुको_queue);
पूर्ण

/**
 * pm_runसमय_reinit - Re-initialize runसमय PM fields in given device object.
 * @dev: Device object to re-initialize.
 */
व्योम pm_runसमय_reinit(काष्ठा device *dev)
अणु
	अगर (!pm_runसमय_enabled(dev)) अणु
		अगर (dev->घातer.runसमय_status == RPM_ACTIVE)
			pm_runसमय_set_suspended(dev);
		अगर (dev->घातer.irq_safe) अणु
			spin_lock_irq(&dev->घातer.lock);
			dev->घातer.irq_safe = 0;
			spin_unlock_irq(&dev->घातer.lock);
			अगर (dev->parent)
				pm_runसमय_put(dev->parent);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * pm_runसमय_हटाओ - Prepare क्रम removing a device from device hierarchy.
 * @dev: Device object being हटाओd from device hierarchy.
 */
व्योम pm_runसमय_हटाओ(काष्ठा device *dev)
अणु
	__pm_runसमय_disable(dev, false);
	pm_runसमय_reinit(dev);
पूर्ण

/**
 * pm_runसमय_get_suppliers - Resume and reference-count supplier devices.
 * @dev: Consumer device.
 */
व्योम pm_runसमय_get_suppliers(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;
	पूर्णांक idx;

	idx = device_links_पढ़ो_lock();

	list_क्रम_each_entry_rcu(link, &dev->links.suppliers, c_node,
				device_links_पढ़ो_lock_held())
		अगर (link->flags & DL_FLAG_PM_RUNTIME) अणु
			link->supplier_preactivated = true;
			pm_runसमय_get_sync(link->supplier);
			refcount_inc(&link->rpm_active);
		पूर्ण

	device_links_पढ़ो_unlock(idx);
पूर्ण

/**
 * pm_runसमय_put_suppliers - Drop references to supplier devices.
 * @dev: Consumer device.
 */
व्योम pm_runसमय_put_suppliers(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;
	अचिन्हित दीर्घ flags;
	bool put;
	पूर्णांक idx;

	idx = device_links_पढ़ो_lock();

	list_क्रम_each_entry_rcu(link, &dev->links.suppliers, c_node,
				device_links_पढ़ो_lock_held())
		अगर (link->supplier_preactivated) अणु
			link->supplier_preactivated = false;
			spin_lock_irqsave(&dev->घातer.lock, flags);
			put = pm_runसमय_status_suspended(dev) &&
			      refcount_dec_not_one(&link->rpm_active);
			spin_unlock_irqrestore(&dev->घातer.lock, flags);
			अगर (put)
				pm_runसमय_put(link->supplier);
		पूर्ण

	device_links_पढ़ो_unlock(idx);
पूर्ण

व्योम pm_runसमय_new_link(काष्ठा device *dev)
अणु
	spin_lock_irq(&dev->घातer.lock);
	dev->घातer.links_count++;
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण

अटल व्योम pm_runसमय_drop_link_count(काष्ठा device *dev)
अणु
	spin_lock_irq(&dev->घातer.lock);
	WARN_ON(dev->घातer.links_count == 0);
	dev->घातer.links_count--;
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण

/**
 * pm_runसमय_drop_link - Prepare क्रम device link removal.
 * @link: Device link going away.
 *
 * Drop the link count of the consumer end of @link and decrement the supplier
 * device's runसमय PM usage counter as many बार as needed to drop all of the
 * PM runसमय reference to it from the consumer.
 */
व्योम pm_runसमय_drop_link(काष्ठा device_link *link)
अणु
	अगर (!(link->flags & DL_FLAG_PM_RUNTIME))
		वापस;

	pm_runसमय_drop_link_count(link->consumer);

	जबतक (refcount_dec_not_one(&link->rpm_active))
		pm_runसमय_put(link->supplier);
पूर्ण

अटल bool pm_runसमय_need_not_resume(काष्ठा device *dev)
अणु
	वापस atomic_पढ़ो(&dev->घातer.usage_count) <= 1 &&
		(atomic_पढ़ो(&dev->घातer.child_count) == 0 ||
		 dev->घातer.ignore_children);
पूर्ण

/**
 * pm_runसमय_क्रमce_suspend - Force a device पूर्णांकo suspend state अगर needed.
 * @dev: Device to suspend.
 *
 * Disable runसमय PM so we safely can check the device's runसमय PM status and
 * अगर it is active, invoke its ->runसमय_suspend callback to suspend it and
 * change its runसमय PM status field to RPM_SUSPENDED.  Also, अगर the device's
 * usage and children counters करोn't indicate that the device was in use beक्रमe
 * the प्रणाली-wide transition under way, decrement its parent's children counter
 * (अगर there is a parent).  Keep runसमय PM disabled to preserve the state
 * unless we encounter errors.
 *
 * Typically this function may be invoked from a प्रणाली suspend callback to make
 * sure the device is put पूर्णांकo low घातer state and it should only be used during
 * प्रणाली-wide PM transitions to sleep states.  It assumes that the analogous
 * pm_runसमय_क्रमce_resume() will be used to resume the device.
 */
पूर्णांक pm_runसमय_क्रमce_suspend(काष्ठा device *dev)
अणु
	पूर्णांक (*callback)(काष्ठा device *);
	पूर्णांक ret;

	pm_runसमय_disable(dev);
	अगर (pm_runसमय_status_suspended(dev))
		वापस 0;

	callback = RPM_GET_CALLBACK(dev, runसमय_suspend);

	ret = callback ? callback(dev) : 0;
	अगर (ret)
		जाओ err;

	/*
	 * If the device can stay in suspend after the प्रणाली-wide transition
	 * to the working state that will follow, drop the children counter of
	 * its parent, but set its status to RPM_SUSPENDED anyway in हाल this
	 * function will be called again क्रम it in the meanसमय.
	 */
	अगर (pm_runसमय_need_not_resume(dev)) अणु
		pm_runसमय_set_suspended(dev);
	पूर्ण अन्यथा अणु
		__update_runसमय_status(dev, RPM_SUSPENDED);
		dev->घातer.needs_क्रमce_resume = 1;
	पूर्ण

	वापस 0;

err:
	pm_runसमय_enable(dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_क्रमce_suspend);

/**
 * pm_runसमय_क्रमce_resume - Force a device पूर्णांकo resume state अगर needed.
 * @dev: Device to resume.
 *
 * Prior invoking this function we expect the user to have brought the device
 * पूर्णांकo low घातer state by a call to pm_runसमय_क्रमce_suspend(). Here we reverse
 * those actions and bring the device पूर्णांकo full घातer, अगर it is expected to be
 * used on प्रणाली resume.  In the other हाल, we defer the resume to be managed
 * via runसमय PM.
 *
 * Typically this function may be invoked from a प्रणाली resume callback.
 */
पूर्णांक pm_runसमय_क्रमce_resume(काष्ठा device *dev)
अणु
	पूर्णांक (*callback)(काष्ठा device *);
	पूर्णांक ret = 0;

	अगर (!pm_runसमय_status_suspended(dev) || !dev->घातer.needs_क्रमce_resume)
		जाओ out;

	/*
	 * The value of the parent's children counter is correct alपढ़ोy, so
	 * just update the status of the device.
	 */
	__update_runसमय_status(dev, RPM_ACTIVE);

	callback = RPM_GET_CALLBACK(dev, runसमय_resume);

	ret = callback ? callback(dev) : 0;
	अगर (ret) अणु
		pm_runसमय_set_suspended(dev);
		जाओ out;
	पूर्ण

	pm_runसमय_mark_last_busy(dev);
out:
	dev->घातer.needs_क्रमce_resume = 0;
	pm_runसमय_enable(dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pm_runसमय_क्रमce_resume);
