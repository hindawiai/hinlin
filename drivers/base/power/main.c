<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/मुख्य.c - Where the driver meets घातer management.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 *
 * The driver model core calls device_pm_add() when a device is रेजिस्टरed.
 * This will initialize the embedded device_pm_info object in the device
 * and add it to the list of घातer-controlled devices. sysfs entries क्रम
 * controlling device घातer management will also be added.
 *
 * A separate list is used क्रम keeping track of घातer info, because the घातer
 * करोमुख्य dependencies may dअगरfer from the ancestral dependencies that the
 * subप्रणाली list मुख्यtains.
 */

#घोषणा pr_fmt(fmt) "PM: " fmt
#घोषणा dev_fmt pr_fmt

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm-trace.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/async.h>
#समावेश <linux/suspend.h>
#समावेश <trace/events/घातer.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/समयr.h>

#समावेश "../base.h"
#समावेश "power.h"

प्रकार पूर्णांक (*pm_callback_t)(काष्ठा device *);

#घोषणा list_क्रम_each_entry_rcu_locked(pos, head, member) \
	list_क्रम_each_entry_rcu(pos, head, member, \
			device_links_पढ़ो_lock_held())

/*
 * The entries in the dpm_list list are in a depth first order, simply
 * because children are guaranteed to be discovered after parents, and
 * are inserted at the back of the list on discovery.
 *
 * Since device_pm_add() may be called with a device lock held,
 * we must never try to acquire a device lock जबतक holding
 * dpm_list_mutex.
 */

LIST_HEAD(dpm_list);
अटल LIST_HEAD(dpm_prepared_list);
अटल LIST_HEAD(dpm_suspended_list);
अटल LIST_HEAD(dpm_late_early_list);
अटल LIST_HEAD(dpm_noirq_list);

काष्ठा suspend_stats suspend_stats;
अटल DEFINE_MUTEX(dpm_list_mtx);
अटल pm_message_t pm_transition;

अटल पूर्णांक async_error;

अटल स्थिर अक्षर *pm_verb(पूर्णांक event)
अणु
	चयन (event) अणु
	हाल PM_EVENT_SUSPEND:
		वापस "suspend";
	हाल PM_EVENT_RESUME:
		वापस "resume";
	हाल PM_EVENT_FREEZE:
		वापस "freeze";
	हाल PM_EVENT_QUIESCE:
		वापस "quiesce";
	हाल PM_EVENT_HIBERNATE:
		वापस "hibernate";
	हाल PM_EVENT_THAW:
		वापस "thaw";
	हाल PM_EVENT_RESTORE:
		वापस "restore";
	हाल PM_EVENT_RECOVER:
		वापस "recover";
	शेष:
		वापस "(unknown PM event)";
	पूर्ण
पूर्ण

/**
 * device_pm_sleep_init - Initialize प्रणाली suspend-related device fields.
 * @dev: Device object being initialized.
 */
व्योम device_pm_sleep_init(काष्ठा device *dev)
अणु
	dev->घातer.is_prepared = false;
	dev->घातer.is_suspended = false;
	dev->घातer.is_noirq_suspended = false;
	dev->घातer.is_late_suspended = false;
	init_completion(&dev->घातer.completion);
	complete_all(&dev->घातer.completion);
	dev->घातer.wakeup = शून्य;
	INIT_LIST_HEAD(&dev->घातer.entry);
पूर्ण

/**
 * device_pm_lock - Lock the list of active devices used by the PM core.
 */
व्योम device_pm_lock(व्योम)
अणु
	mutex_lock(&dpm_list_mtx);
पूर्ण

/**
 * device_pm_unlock - Unlock the list of active devices used by the PM core.
 */
व्योम device_pm_unlock(व्योम)
अणु
	mutex_unlock(&dpm_list_mtx);
पूर्ण

/**
 * device_pm_add - Add a device to the PM core's list of active devices.
 * @dev: Device to add to the list.
 */
व्योम device_pm_add(काष्ठा device *dev)
अणु
	/* Skip PM setup/initialization. */
	अगर (device_pm_not_required(dev))
		वापस;

	pr_debug("Adding info for %s:%s\n",
		 dev->bus ? dev->bus->name : "No Bus", dev_name(dev));
	device_pm_check_callbacks(dev);
	mutex_lock(&dpm_list_mtx);
	अगर (dev->parent && dev->parent->घातer.is_prepared)
		dev_warn(dev, "parent %s should not be sleeping\n",
			dev_name(dev->parent));
	list_add_tail(&dev->घातer.entry, &dpm_list);
	dev->घातer.in_dpm_list = true;
	mutex_unlock(&dpm_list_mtx);
पूर्ण

/**
 * device_pm_हटाओ - Remove a device from the PM core's list of active devices.
 * @dev: Device to be हटाओd from the list.
 */
व्योम device_pm_हटाओ(काष्ठा device *dev)
अणु
	अगर (device_pm_not_required(dev))
		वापस;

	pr_debug("Removing info for %s:%s\n",
		 dev->bus ? dev->bus->name : "No Bus", dev_name(dev));
	complete_all(&dev->घातer.completion);
	mutex_lock(&dpm_list_mtx);
	list_del_init(&dev->घातer.entry);
	dev->घातer.in_dpm_list = false;
	mutex_unlock(&dpm_list_mtx);
	device_wakeup_disable(dev);
	pm_runसमय_हटाओ(dev);
	device_pm_check_callbacks(dev);
पूर्ण

/**
 * device_pm_move_beक्रमe - Move device in the PM core's list of active devices.
 * @deva: Device to move in dpm_list.
 * @devb: Device @deva should come beक्रमe.
 */
व्योम device_pm_move_beक्रमe(काष्ठा device *deva, काष्ठा device *devb)
अणु
	pr_debug("Moving %s:%s before %s:%s\n",
		 deva->bus ? deva->bus->name : "No Bus", dev_name(deva),
		 devb->bus ? devb->bus->name : "No Bus", dev_name(devb));
	/* Delete deva from dpm_list and reinsert beक्रमe devb. */
	list_move_tail(&deva->घातer.entry, &devb->घातer.entry);
पूर्ण

/**
 * device_pm_move_after - Move device in the PM core's list of active devices.
 * @deva: Device to move in dpm_list.
 * @devb: Device @deva should come after.
 */
व्योम device_pm_move_after(काष्ठा device *deva, काष्ठा device *devb)
अणु
	pr_debug("Moving %s:%s after %s:%s\n",
		 deva->bus ? deva->bus->name : "No Bus", dev_name(deva),
		 devb->bus ? devb->bus->name : "No Bus", dev_name(devb));
	/* Delete deva from dpm_list and reinsert after devb. */
	list_move(&deva->घातer.entry, &devb->घातer.entry);
पूर्ण

/**
 * device_pm_move_last - Move device to end of the PM core's list of devices.
 * @dev: Device to move in dpm_list.
 */
व्योम device_pm_move_last(काष्ठा device *dev)
अणु
	pr_debug("Moving %s:%s to end of list\n",
		 dev->bus ? dev->bus->name : "No Bus", dev_name(dev));
	list_move_tail(&dev->घातer.entry, &dpm_list);
पूर्ण

अटल kसमय_प्रकार initcall_debug_start(काष्ठा device *dev, व्योम *cb)
अणु
	अगर (!pm_prपूर्णांक_बार_enabled)
		वापस 0;

	dev_info(dev, "calling %pS @ %i, parent: %s\n", cb,
		 task_pid_nr(current),
		 dev->parent ? dev_name(dev->parent) : "none");
	वापस kसमय_get();
पूर्ण

अटल व्योम initcall_debug_report(काष्ठा device *dev, kसमय_प्रकार callसमय,
				  व्योम *cb, पूर्णांक error)
अणु
	kसमय_प्रकार retसमय;
	s64 nsecs;

	अगर (!pm_prपूर्णांक_बार_enabled)
		वापस;

	retसमय = kसमय_get();
	nsecs = (s64) kसमय_प्रकारo_ns(kसमय_sub(retसमय, callसमय));

	dev_info(dev, "%pS returned %d after %Ld usecs\n", cb, error,
		 (अचिन्हित दीर्घ दीर्घ)nsecs >> 10);
पूर्ण

/**
 * dpm_रुको - Wait क्रम a PM operation to complete.
 * @dev: Device to रुको क्रम.
 * @async: If unset, रुको only अगर the device's घातer.async_suspend flag is set.
 */
अटल व्योम dpm_रुको(काष्ठा device *dev, bool async)
अणु
	अगर (!dev)
		वापस;

	अगर (async || (pm_async_enabled && dev->घातer.async_suspend))
		रुको_क्रम_completion(&dev->घातer.completion);
पूर्ण

अटल पूर्णांक dpm_रुको_fn(काष्ठा device *dev, व्योम *async_ptr)
अणु
	dpm_रुको(dev, *((bool *)async_ptr));
	वापस 0;
पूर्ण

अटल व्योम dpm_रुको_क्रम_children(काष्ठा device *dev, bool async)
अणु
       device_क्रम_each_child(dev, &async, dpm_रुको_fn);
पूर्ण

अटल व्योम dpm_रुको_क्रम_suppliers(काष्ठा device *dev, bool async)
अणु
	काष्ठा device_link *link;
	पूर्णांक idx;

	idx = device_links_पढ़ो_lock();

	/*
	 * If the supplier goes away right after we've checked the link to it,
	 * we'll wait for its completion to change the state, but that's fine,
	 * because the only things that will block as a result are the SRCU
	 * callbacks मुक्तing the link objects क्रम the links in the list we're
	 * walking.
	 */
	list_क्रम_each_entry_rcu_locked(link, &dev->links.suppliers, c_node)
		अगर (READ_ONCE(link->status) != DL_STATE_DORMANT)
			dpm_रुको(link->supplier, async);

	device_links_पढ़ो_unlock(idx);
पूर्ण

अटल bool dpm_रुको_क्रम_superior(काष्ठा device *dev, bool async)
अणु
	काष्ठा device *parent;

	/*
	 * If the device is resumed asynchronously and the parent's callback
	 * deletes both the device and the parent itself, the parent object may
	 * be मुक्तd जबतक this function is running, so aव्योम that by reference
	 * counting the parent once more unless the device has been deleted
	 * alपढ़ोy (in which हाल वापस right away).
	 */
	mutex_lock(&dpm_list_mtx);

	अगर (!device_pm_initialized(dev)) अणु
		mutex_unlock(&dpm_list_mtx);
		वापस false;
	पूर्ण

	parent = get_device(dev->parent);

	mutex_unlock(&dpm_list_mtx);

	dpm_रुको(parent, async);
	put_device(parent);

	dpm_रुको_क्रम_suppliers(dev, async);

	/*
	 * If the parent's callback has deleted the device, attempting to resume
	 * it would be invalid, so aव्योम करोing that then.
	 */
	वापस device_pm_initialized(dev);
पूर्ण

अटल व्योम dpm_रुको_क्रम_consumers(काष्ठा device *dev, bool async)
अणु
	काष्ठा device_link *link;
	पूर्णांक idx;

	idx = device_links_पढ़ो_lock();

	/*
	 * The status of a device link can only be changed from "dormant" by a
	 * probe, but that cannot happen during प्रणाली suspend/resume.  In
	 * theory it can change to "dormant" at that समय, but then it is
	 * reasonable to रुको क्रम the target device anyway (eg. अगर it goes
	 * away, it's better to रुको क्रम it to go away completely and then
	 * जारी instead of trying to जारी in parallel with its
	 * unregistration).
	 */
	list_क्रम_each_entry_rcu_locked(link, &dev->links.consumers, s_node)
		अगर (READ_ONCE(link->status) != DL_STATE_DORMANT)
			dpm_रुको(link->consumer, async);

	device_links_पढ़ो_unlock(idx);
पूर्ण

अटल व्योम dpm_रुको_क्रम_subordinate(काष्ठा device *dev, bool async)
अणु
	dpm_रुको_क्रम_children(dev, async);
	dpm_रुको_क्रम_consumers(dev, async);
पूर्ण

/**
 * pm_op - Return the PM operation appropriate क्रम given PM event.
 * @ops: PM operations to choose from.
 * @state: PM transition of the प्रणाली being carried out.
 */
अटल pm_callback_t pm_op(स्थिर काष्ठा dev_pm_ops *ops, pm_message_t state)
अणु
	चयन (state.event) अणु
#अगर_घोषित CONFIG_SUSPEND
	हाल PM_EVENT_SUSPEND:
		वापस ops->suspend;
	हाल PM_EVENT_RESUME:
		वापस ops->resume;
#पूर्ण_अगर /* CONFIG_SUSPEND */
#अगर_घोषित CONFIG_HIBERNATE_CALLBACKS
	हाल PM_EVENT_FREEZE:
	हाल PM_EVENT_QUIESCE:
		वापस ops->मुक्तze;
	हाल PM_EVENT_HIBERNATE:
		वापस ops->घातeroff;
	हाल PM_EVENT_THAW:
	हाल PM_EVENT_RECOVER:
		वापस ops->thaw;
	हाल PM_EVENT_RESTORE:
		वापस ops->restore;
#पूर्ण_अगर /* CONFIG_HIBERNATE_CALLBACKS */
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * pm_late_early_op - Return the PM operation appropriate क्रम given PM event.
 * @ops: PM operations to choose from.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Runसमय PM is disabled क्रम @dev जबतक this function is being executed.
 */
अटल pm_callback_t pm_late_early_op(स्थिर काष्ठा dev_pm_ops *ops,
				      pm_message_t state)
अणु
	चयन (state.event) अणु
#अगर_घोषित CONFIG_SUSPEND
	हाल PM_EVENT_SUSPEND:
		वापस ops->suspend_late;
	हाल PM_EVENT_RESUME:
		वापस ops->resume_early;
#पूर्ण_अगर /* CONFIG_SUSPEND */
#अगर_घोषित CONFIG_HIBERNATE_CALLBACKS
	हाल PM_EVENT_FREEZE:
	हाल PM_EVENT_QUIESCE:
		वापस ops->मुक्तze_late;
	हाल PM_EVENT_HIBERNATE:
		वापस ops->घातeroff_late;
	हाल PM_EVENT_THAW:
	हाल PM_EVENT_RECOVER:
		वापस ops->thaw_early;
	हाल PM_EVENT_RESTORE:
		वापस ops->restore_early;
#पूर्ण_अगर /* CONFIG_HIBERNATE_CALLBACKS */
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * pm_noirq_op - Return the PM operation appropriate क्रम given PM event.
 * @ops: PM operations to choose from.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * The driver of @dev will not receive पूर्णांकerrupts जबतक this function is being
 * executed.
 */
अटल pm_callback_t pm_noirq_op(स्थिर काष्ठा dev_pm_ops *ops, pm_message_t state)
अणु
	चयन (state.event) अणु
#अगर_घोषित CONFIG_SUSPEND
	हाल PM_EVENT_SUSPEND:
		वापस ops->suspend_noirq;
	हाल PM_EVENT_RESUME:
		वापस ops->resume_noirq;
#पूर्ण_अगर /* CONFIG_SUSPEND */
#अगर_घोषित CONFIG_HIBERNATE_CALLBACKS
	हाल PM_EVENT_FREEZE:
	हाल PM_EVENT_QUIESCE:
		वापस ops->मुक्तze_noirq;
	हाल PM_EVENT_HIBERNATE:
		वापस ops->घातeroff_noirq;
	हाल PM_EVENT_THAW:
	हाल PM_EVENT_RECOVER:
		वापस ops->thaw_noirq;
	हाल PM_EVENT_RESTORE:
		वापस ops->restore_noirq;
#पूर्ण_अगर /* CONFIG_HIBERNATE_CALLBACKS */
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम pm_dev_dbg(काष्ठा device *dev, pm_message_t state, स्थिर अक्षर *info)
अणु
	dev_dbg(dev, "%s%s%s driver flags: %x\n", info, pm_verb(state.event),
		((state.event & PM_EVENT_SLEEP) && device_may_wakeup(dev)) ?
		", may wakeup" : "", dev->घातer.driver_flags);
पूर्ण

अटल व्योम pm_dev_err(काष्ठा device *dev, pm_message_t state, स्थिर अक्षर *info,
			पूर्णांक error)
अणु
	dev_err(dev, "failed to %s%s: error %d\n", pm_verb(state.event), info,
		error);
पूर्ण

अटल व्योम dpm_show_समय(kसमय_प्रकार startसमय, pm_message_t state, पूर्णांक error,
			  स्थिर अक्षर *info)
अणु
	kसमय_प्रकार callसमय;
	u64 usecs64;
	पूर्णांक usecs;

	callसमय = kसमय_get();
	usecs64 = kसमय_प्रकारo_ns(kसमय_sub(callसमय, startसमय));
	करो_भाग(usecs64, NSEC_PER_USEC);
	usecs = usecs64;
	अगर (usecs == 0)
		usecs = 1;

	pm_pr_dbg("%s%s%s of devices %s after %ld.%03ld msecs\n",
		  info ?: "", info ? " " : "", pm_verb(state.event),
		  error ? "aborted" : "complete",
		  usecs / USEC_PER_MSEC, usecs % USEC_PER_MSEC);
पूर्ण

अटल पूर्णांक dpm_run_callback(pm_callback_t cb, काष्ठा device *dev,
			    pm_message_t state, स्थिर अक्षर *info)
अणु
	kसमय_प्रकार callसमय;
	पूर्णांक error;

	अगर (!cb)
		वापस 0;

	callसमय = initcall_debug_start(dev, cb);

	pm_dev_dbg(dev, state, info);
	trace_device_pm_callback_start(dev, info, state.event);
	error = cb(dev);
	trace_device_pm_callback_end(dev, error);
	suspend_report_result(cb, error);

	initcall_debug_report(dev, callसमय, cb, error);

	वापस error;
पूर्ण

#अगर_घोषित CONFIG_DPM_WATCHDOG
काष्ठा dpm_watchकरोg अणु
	काष्ठा device		*dev;
	काष्ठा task_काष्ठा	*tsk;
	काष्ठा समयr_list	समयr;
पूर्ण;

#घोषणा DECLARE_DPM_WATCHDOG_ON_STACK(wd) \
	काष्ठा dpm_watchकरोg wd

/**
 * dpm_watchकरोg_handler - Driver suspend / resume watchकरोg handler.
 * @t: The समयr that PM watchकरोg depends on.
 *
 * Called when a driver has समयd out suspending or resuming.
 * There's not much we can करो here to recover so panic() to
 * capture a crash-dump in pstore.
 */
अटल व्योम dpm_watchकरोg_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा dpm_watchकरोg *wd = from_समयr(wd, t, समयr);

	dev_emerg(wd->dev, "**** DPM device timeout ****\n");
	show_stack(wd->tsk, शून्य, KERN_EMERG);
	panic("%s %s: unrecoverable failure\n",
		dev_driver_string(wd->dev), dev_name(wd->dev));
पूर्ण

/**
 * dpm_watchकरोg_set - Enable pm watchकरोg क्रम given device.
 * @wd: Watchकरोg. Must be allocated on the stack.
 * @dev: Device to handle.
 */
अटल व्योम dpm_watchकरोg_set(काष्ठा dpm_watchकरोg *wd, काष्ठा device *dev)
अणु
	काष्ठा समयr_list *समयr = &wd->समयr;

	wd->dev = dev;
	wd->tsk = current;

	समयr_setup_on_stack(समयr, dpm_watchकरोg_handler, 0);
	/* use same समयout value क्रम both suspend and resume */
	समयr->expires = jअगरfies + HZ * CONFIG_DPM_WATCHDOG_TIMEOUT;
	add_समयr(समयr);
पूर्ण

/**
 * dpm_watchकरोg_clear - Disable suspend/resume watchकरोg.
 * @wd: Watchकरोg to disable.
 */
अटल व्योम dpm_watchकरोg_clear(काष्ठा dpm_watchकरोg *wd)
अणु
	काष्ठा समयr_list *समयr = &wd->समयr;

	del_समयr_sync(समयr);
	destroy_समयr_on_stack(समयr);
पूर्ण
#अन्यथा
#घोषणा DECLARE_DPM_WATCHDOG_ON_STACK(wd)
#घोषणा dpm_watchकरोg_set(x, y)
#घोषणा dpm_watchकरोg_clear(x)
#पूर्ण_अगर

/*------------------------- Resume routines -------------------------*/

/**
 * dev_pm_skip_resume - System-wide device resume optimization check.
 * @dev: Target device.
 *
 * Return:
 * - %false अगर the transition under way is RESTORE.
 * - Return value of dev_pm_skip_suspend() अगर the transition under way is THAW.
 * - The logical negation of %घातer.must_resume otherwise (that is, when the
 *   transition under way is RESUME).
 */
bool dev_pm_skip_resume(काष्ठा device *dev)
अणु
	अगर (pm_transition.event == PM_EVENT_RESTORE)
		वापस false;

	अगर (pm_transition.event == PM_EVENT_THAW)
		वापस dev_pm_skip_suspend(dev);

	वापस !dev->घातer.must_resume;
पूर्ण

/**
 * device_resume_noirq - Execute a "noirq resume" callback क्रम given device.
 * @dev: Device to handle.
 * @state: PM transition of the प्रणाली being carried out.
 * @async: If true, the device is being resumed asynchronously.
 *
 * The driver of @dev will not receive पूर्णांकerrupts जबतक this function is being
 * executed.
 */
अटल पूर्णांक device_resume_noirq(काष्ठा device *dev, pm_message_t state, bool async)
अणु
	pm_callback_t callback = शून्य;
	स्थिर अक्षर *info = शून्य;
	bool skip_resume;
	पूर्णांक error = 0;

	TRACE_DEVICE(dev);
	TRACE_RESUME(0);

	अगर (dev->घातer.syscore || dev->घातer.direct_complete)
		जाओ Out;

	अगर (!dev->घातer.is_noirq_suspended)
		जाओ Out;

	अगर (!dpm_रुको_क्रम_superior(dev, async))
		जाओ Out;

	skip_resume = dev_pm_skip_resume(dev);
	/*
	 * If the driver callback is skipped below or by the middle layer
	 * callback and device_resume_early() also skips the driver callback क्रम
	 * this device later, it needs to appear as "suspended" to PM-runसमय,
	 * so change its status accordingly.
	 *
	 * Otherwise, the device is going to be resumed, so set its PM-runसमय
	 * status to "active", but करो that only अगर DPM_FLAG_SMART_SUSPEND is set
	 * to aव्योम confusing drivers that करोn't use it.
	 */
	अगर (skip_resume)
		pm_runसमय_set_suspended(dev);
	अन्यथा अगर (dev_pm_skip_suspend(dev))
		pm_runसमय_set_active(dev);

	अगर (dev->pm_करोमुख्य) अणु
		info = "noirq power domain ";
		callback = pm_noirq_op(&dev->pm_करोमुख्य->ops, state);
	पूर्ण अन्यथा अगर (dev->type && dev->type->pm) अणु
		info = "noirq type ";
		callback = pm_noirq_op(dev->type->pm, state);
	पूर्ण अन्यथा अगर (dev->class && dev->class->pm) अणु
		info = "noirq class ";
		callback = pm_noirq_op(dev->class->pm, state);
	पूर्ण अन्यथा अगर (dev->bus && dev->bus->pm) अणु
		info = "noirq bus ";
		callback = pm_noirq_op(dev->bus->pm, state);
	पूर्ण
	अगर (callback)
		जाओ Run;

	अगर (skip_resume)
		जाओ Skip;

	अगर (dev->driver && dev->driver->pm) अणु
		info = "noirq driver ";
		callback = pm_noirq_op(dev->driver->pm, state);
	पूर्ण

Run:
	error = dpm_run_callback(callback, dev, state, info);

Skip:
	dev->घातer.is_noirq_suspended = false;

Out:
	complete_all(&dev->घातer.completion);
	TRACE_RESUME(error);
	वापस error;
पूर्ण

अटल bool is_async(काष्ठा device *dev)
अणु
	वापस dev->घातer.async_suspend && pm_async_enabled
		&& !pm_trace_is_enabled();
पूर्ण

अटल bool dpm_async_fn(काष्ठा device *dev, async_func_t func)
अणु
	reinit_completion(&dev->घातer.completion);

	अगर (is_async(dev)) अणु
		get_device(dev);
		async_schedule_dev(func, dev);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम async_resume_noirq(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	पूर्णांक error;

	error = device_resume_noirq(dev, pm_transition, true);
	अगर (error)
		pm_dev_err(dev, pm_transition, " async", error);

	put_device(dev);
पूर्ण

अटल व्योम dpm_noirq_resume_devices(pm_message_t state)
अणु
	काष्ठा device *dev;
	kसमय_प्रकार startसमय = kसमय_get();

	trace_suspend_resume(TPS("dpm_resume_noirq"), state.event, true);
	mutex_lock(&dpm_list_mtx);
	pm_transition = state;

	/*
	 * Advanced the async thपढ़ोs upfront,
	 * in हाल the starting of async thपढ़ोs is
	 * delayed by non-async resuming devices.
	 */
	list_क्रम_each_entry(dev, &dpm_noirq_list, घातer.entry)
		dpm_async_fn(dev, async_resume_noirq);

	जबतक (!list_empty(&dpm_noirq_list)) अणु
		dev = to_device(dpm_noirq_list.next);
		get_device(dev);
		list_move_tail(&dev->घातer.entry, &dpm_late_early_list);
		mutex_unlock(&dpm_list_mtx);

		अगर (!is_async(dev)) अणु
			पूर्णांक error;

			error = device_resume_noirq(dev, state, false);
			अगर (error) अणु
				suspend_stats.failed_resume_noirq++;
				dpm_save_failed_step(SUSPEND_RESUME_NOIRQ);
				dpm_save_failed_dev(dev_name(dev));
				pm_dev_err(dev, state, " noirq", error);
			पूर्ण
		पूर्ण

		mutex_lock(&dpm_list_mtx);
		put_device(dev);
	पूर्ण
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	dpm_show_समय(startसमय, state, 0, "noirq");
	trace_suspend_resume(TPS("dpm_resume_noirq"), state.event, false);
पूर्ण

/**
 * dpm_resume_noirq - Execute "noirq resume" callbacks क्रम all devices.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Invoke the "noirq" resume callbacks क्रम all devices in dpm_noirq_list and
 * allow device drivers' पूर्णांकerrupt handlers to be called.
 */
व्योम dpm_resume_noirq(pm_message_t state)
अणु
	dpm_noirq_resume_devices(state);

	resume_device_irqs();
	device_wakeup_disarm_wake_irqs();

	cpuidle_resume();
पूर्ण

/**
 * device_resume_early - Execute an "early resume" callback क्रम given device.
 * @dev: Device to handle.
 * @state: PM transition of the प्रणाली being carried out.
 * @async: If true, the device is being resumed asynchronously.
 *
 * Runसमय PM is disabled क्रम @dev जबतक this function is being executed.
 */
अटल पूर्णांक device_resume_early(काष्ठा device *dev, pm_message_t state, bool async)
अणु
	pm_callback_t callback = शून्य;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;

	TRACE_DEVICE(dev);
	TRACE_RESUME(0);

	अगर (dev->घातer.syscore || dev->घातer.direct_complete)
		जाओ Out;

	अगर (!dev->घातer.is_late_suspended)
		जाओ Out;

	अगर (!dpm_रुको_क्रम_superior(dev, async))
		जाओ Out;

	अगर (dev->pm_करोमुख्य) अणु
		info = "early power domain ";
		callback = pm_late_early_op(&dev->pm_करोमुख्य->ops, state);
	पूर्ण अन्यथा अगर (dev->type && dev->type->pm) अणु
		info = "early type ";
		callback = pm_late_early_op(dev->type->pm, state);
	पूर्ण अन्यथा अगर (dev->class && dev->class->pm) अणु
		info = "early class ";
		callback = pm_late_early_op(dev->class->pm, state);
	पूर्ण अन्यथा अगर (dev->bus && dev->bus->pm) अणु
		info = "early bus ";
		callback = pm_late_early_op(dev->bus->pm, state);
	पूर्ण
	अगर (callback)
		जाओ Run;

	अगर (dev_pm_skip_resume(dev))
		जाओ Skip;

	अगर (dev->driver && dev->driver->pm) अणु
		info = "early driver ";
		callback = pm_late_early_op(dev->driver->pm, state);
	पूर्ण

Run:
	error = dpm_run_callback(callback, dev, state, info);

Skip:
	dev->घातer.is_late_suspended = false;

Out:
	TRACE_RESUME(error);

	pm_runसमय_enable(dev);
	complete_all(&dev->घातer.completion);
	वापस error;
पूर्ण

अटल व्योम async_resume_early(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	पूर्णांक error;

	error = device_resume_early(dev, pm_transition, true);
	अगर (error)
		pm_dev_err(dev, pm_transition, " async", error);

	put_device(dev);
पूर्ण

/**
 * dpm_resume_early - Execute "early resume" callbacks क्रम all devices.
 * @state: PM transition of the प्रणाली being carried out.
 */
व्योम dpm_resume_early(pm_message_t state)
अणु
	काष्ठा device *dev;
	kसमय_प्रकार startसमय = kसमय_get();

	trace_suspend_resume(TPS("dpm_resume_early"), state.event, true);
	mutex_lock(&dpm_list_mtx);
	pm_transition = state;

	/*
	 * Advanced the async thपढ़ोs upfront,
	 * in हाल the starting of async thपढ़ोs is
	 * delayed by non-async resuming devices.
	 */
	list_क्रम_each_entry(dev, &dpm_late_early_list, घातer.entry)
		dpm_async_fn(dev, async_resume_early);

	जबतक (!list_empty(&dpm_late_early_list)) अणु
		dev = to_device(dpm_late_early_list.next);
		get_device(dev);
		list_move_tail(&dev->घातer.entry, &dpm_suspended_list);
		mutex_unlock(&dpm_list_mtx);

		अगर (!is_async(dev)) अणु
			पूर्णांक error;

			error = device_resume_early(dev, state, false);
			अगर (error) अणु
				suspend_stats.failed_resume_early++;
				dpm_save_failed_step(SUSPEND_RESUME_EARLY);
				dpm_save_failed_dev(dev_name(dev));
				pm_dev_err(dev, state, " early", error);
			पूर्ण
		पूर्ण
		mutex_lock(&dpm_list_mtx);
		put_device(dev);
	पूर्ण
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	dpm_show_समय(startसमय, state, 0, "early");
	trace_suspend_resume(TPS("dpm_resume_early"), state.event, false);
पूर्ण

/**
 * dpm_resume_start - Execute "noirq" and "early" device callbacks.
 * @state: PM transition of the प्रणाली being carried out.
 */
व्योम dpm_resume_start(pm_message_t state)
अणु
	dpm_resume_noirq(state);
	dpm_resume_early(state);
पूर्ण
EXPORT_SYMBOL_GPL(dpm_resume_start);

/**
 * device_resume - Execute "resume" callbacks क्रम given device.
 * @dev: Device to handle.
 * @state: PM transition of the प्रणाली being carried out.
 * @async: If true, the device is being resumed asynchronously.
 */
अटल पूर्णांक device_resume(काष्ठा device *dev, pm_message_t state, bool async)
अणु
	pm_callback_t callback = शून्य;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;
	DECLARE_DPM_WATCHDOG_ON_STACK(wd);

	TRACE_DEVICE(dev);
	TRACE_RESUME(0);

	अगर (dev->घातer.syscore)
		जाओ Complete;

	अगर (dev->घातer.direct_complete) अणु
		/* Match the pm_runसमय_disable() in __device_suspend(). */
		pm_runसमय_enable(dev);
		जाओ Complete;
	पूर्ण

	अगर (!dpm_रुको_क्रम_superior(dev, async))
		जाओ Complete;

	dpm_watchकरोg_set(&wd, dev);
	device_lock(dev);

	/*
	 * This is a fib.  But we'll allow new children to be added below
	 * a resumed device, even अगर the device hasn't been completed yet.
	 */
	dev->घातer.is_prepared = false;

	अगर (!dev->घातer.is_suspended)
		जाओ Unlock;

	अगर (dev->pm_करोमुख्य) अणु
		info = "power domain ";
		callback = pm_op(&dev->pm_करोमुख्य->ops, state);
		जाओ Driver;
	पूर्ण

	अगर (dev->type && dev->type->pm) अणु
		info = "type ";
		callback = pm_op(dev->type->pm, state);
		जाओ Driver;
	पूर्ण

	अगर (dev->class && dev->class->pm) अणु
		info = "class ";
		callback = pm_op(dev->class->pm, state);
		जाओ Driver;
	पूर्ण

	अगर (dev->bus) अणु
		अगर (dev->bus->pm) अणु
			info = "bus ";
			callback = pm_op(dev->bus->pm, state);
		पूर्ण अन्यथा अगर (dev->bus->resume) अणु
			info = "legacy bus ";
			callback = dev->bus->resume;
			जाओ End;
		पूर्ण
	पूर्ण

 Driver:
	अगर (!callback && dev->driver && dev->driver->pm) अणु
		info = "driver ";
		callback = pm_op(dev->driver->pm, state);
	पूर्ण

 End:
	error = dpm_run_callback(callback, dev, state, info);
	dev->घातer.is_suspended = false;

 Unlock:
	device_unlock(dev);
	dpm_watchकरोg_clear(&wd);

 Complete:
	complete_all(&dev->घातer.completion);

	TRACE_RESUME(error);

	वापस error;
पूर्ण

अटल व्योम async_resume(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	पूर्णांक error;

	error = device_resume(dev, pm_transition, true);
	अगर (error)
		pm_dev_err(dev, pm_transition, " async", error);
	put_device(dev);
पूर्ण

/**
 * dpm_resume - Execute "resume" callbacks क्रम non-sysdev devices.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Execute the appropriate "resume" callback क्रम all devices whose status
 * indicates that they are suspended.
 */
व्योम dpm_resume(pm_message_t state)
अणु
	काष्ठा device *dev;
	kसमय_प्रकार startसमय = kसमय_get();

	trace_suspend_resume(TPS("dpm_resume"), state.event, true);
	might_sleep();

	mutex_lock(&dpm_list_mtx);
	pm_transition = state;
	async_error = 0;

	list_क्रम_each_entry(dev, &dpm_suspended_list, घातer.entry)
		dpm_async_fn(dev, async_resume);

	जबतक (!list_empty(&dpm_suspended_list)) अणु
		dev = to_device(dpm_suspended_list.next);
		get_device(dev);
		अगर (!is_async(dev)) अणु
			पूर्णांक error;

			mutex_unlock(&dpm_list_mtx);

			error = device_resume(dev, state, false);
			अगर (error) अणु
				suspend_stats.failed_resume++;
				dpm_save_failed_step(SUSPEND_RESUME);
				dpm_save_failed_dev(dev_name(dev));
				pm_dev_err(dev, state, "", error);
			पूर्ण

			mutex_lock(&dpm_list_mtx);
		पूर्ण
		अगर (!list_empty(&dev->घातer.entry))
			list_move_tail(&dev->घातer.entry, &dpm_prepared_list);
		put_device(dev);
	पूर्ण
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	dpm_show_समय(startसमय, state, 0, शून्य);

	cpufreq_resume();
	devfreq_resume();
	trace_suspend_resume(TPS("dpm_resume"), state.event, false);
पूर्ण

/**
 * device_complete - Complete a PM transition क्रम given device.
 * @dev: Device to handle.
 * @state: PM transition of the प्रणाली being carried out.
 */
अटल व्योम device_complete(काष्ठा device *dev, pm_message_t state)
अणु
	व्योम (*callback)(काष्ठा device *) = शून्य;
	स्थिर अक्षर *info = शून्य;

	अगर (dev->घातer.syscore)
		वापस;

	device_lock(dev);

	अगर (dev->pm_करोमुख्य) अणु
		info = "completing power domain ";
		callback = dev->pm_करोमुख्य->ops.complete;
	पूर्ण अन्यथा अगर (dev->type && dev->type->pm) अणु
		info = "completing type ";
		callback = dev->type->pm->complete;
	पूर्ण अन्यथा अगर (dev->class && dev->class->pm) अणु
		info = "completing class ";
		callback = dev->class->pm->complete;
	पूर्ण अन्यथा अगर (dev->bus && dev->bus->pm) अणु
		info = "completing bus ";
		callback = dev->bus->pm->complete;
	पूर्ण

	अगर (!callback && dev->driver && dev->driver->pm) अणु
		info = "completing driver ";
		callback = dev->driver->pm->complete;
	पूर्ण

	अगर (callback) अणु
		pm_dev_dbg(dev, state, info);
		callback(dev);
	पूर्ण

	device_unlock(dev);

	pm_runसमय_put(dev);
पूर्ण

/**
 * dpm_complete - Complete a PM transition क्रम all non-sysdev devices.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Execute the ->complete() callbacks क्रम all devices whose PM status is not
 * DPM_ON (this allows new devices to be रेजिस्टरed).
 */
व्योम dpm_complete(pm_message_t state)
अणु
	काष्ठा list_head list;

	trace_suspend_resume(TPS("dpm_complete"), state.event, true);
	might_sleep();

	INIT_LIST_HEAD(&list);
	mutex_lock(&dpm_list_mtx);
	जबतक (!list_empty(&dpm_prepared_list)) अणु
		काष्ठा device *dev = to_device(dpm_prepared_list.prev);

		get_device(dev);
		dev->घातer.is_prepared = false;
		list_move(&dev->घातer.entry, &list);
		mutex_unlock(&dpm_list_mtx);

		trace_device_pm_callback_start(dev, "", state.event);
		device_complete(dev, state);
		trace_device_pm_callback_end(dev, 0);

		mutex_lock(&dpm_list_mtx);
		put_device(dev);
	पूर्ण
	list_splice(&list, &dpm_list);
	mutex_unlock(&dpm_list_mtx);

	/* Allow device probing and trigger re-probing of deferred devices */
	device_unblock_probing();
	trace_suspend_resume(TPS("dpm_complete"), state.event, false);
पूर्ण

/**
 * dpm_resume_end - Execute "resume" callbacks and complete प्रणाली transition.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Execute "resume" callbacks क्रम all devices and complete the PM transition of
 * the प्रणाली.
 */
व्योम dpm_resume_end(pm_message_t state)
अणु
	dpm_resume(state);
	dpm_complete(state);
पूर्ण
EXPORT_SYMBOL_GPL(dpm_resume_end);


/*------------------------- Suspend routines -------------------------*/

/**
 * resume_event - Return a "resume" message क्रम given "suspend" sleep state.
 * @sleep_state: PM message representing a sleep state.
 *
 * Return a PM message representing the resume event corresponding to given
 * sleep state.
 */
अटल pm_message_t resume_event(pm_message_t sleep_state)
अणु
	चयन (sleep_state.event) अणु
	हाल PM_EVENT_SUSPEND:
		वापस PMSG_RESUME;
	हाल PM_EVENT_FREEZE:
	हाल PM_EVENT_QUIESCE:
		वापस PMSG_RECOVER;
	हाल PM_EVENT_HIBERNATE:
		वापस PMSG_RESTORE;
	पूर्ण
	वापस PMSG_ON;
पूर्ण

अटल व्योम dpm_superior_set_must_resume(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;
	पूर्णांक idx;

	अगर (dev->parent)
		dev->parent->घातer.must_resume = true;

	idx = device_links_पढ़ो_lock();

	list_क्रम_each_entry_rcu_locked(link, &dev->links.suppliers, c_node)
		link->supplier->घातer.must_resume = true;

	device_links_पढ़ो_unlock(idx);
पूर्ण

/**
 * __device_suspend_noirq - Execute a "noirq suspend" callback क्रम given device.
 * @dev: Device to handle.
 * @state: PM transition of the प्रणाली being carried out.
 * @async: If true, the device is being suspended asynchronously.
 *
 * The driver of @dev will not receive पूर्णांकerrupts जबतक this function is being
 * executed.
 */
अटल पूर्णांक __device_suspend_noirq(काष्ठा device *dev, pm_message_t state, bool async)
अणु
	pm_callback_t callback = शून्य;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;

	TRACE_DEVICE(dev);
	TRACE_SUSPEND(0);

	dpm_रुको_क्रम_subordinate(dev, async);

	अगर (async_error)
		जाओ Complete;

	अगर (dev->घातer.syscore || dev->घातer.direct_complete)
		जाओ Complete;

	अगर (dev->pm_करोमुख्य) अणु
		info = "noirq power domain ";
		callback = pm_noirq_op(&dev->pm_करोमुख्य->ops, state);
	पूर्ण अन्यथा अगर (dev->type && dev->type->pm) अणु
		info = "noirq type ";
		callback = pm_noirq_op(dev->type->pm, state);
	पूर्ण अन्यथा अगर (dev->class && dev->class->pm) अणु
		info = "noirq class ";
		callback = pm_noirq_op(dev->class->pm, state);
	पूर्ण अन्यथा अगर (dev->bus && dev->bus->pm) अणु
		info = "noirq bus ";
		callback = pm_noirq_op(dev->bus->pm, state);
	पूर्ण
	अगर (callback)
		जाओ Run;

	अगर (dev_pm_skip_suspend(dev))
		जाओ Skip;

	अगर (dev->driver && dev->driver->pm) अणु
		info = "noirq driver ";
		callback = pm_noirq_op(dev->driver->pm, state);
	पूर्ण

Run:
	error = dpm_run_callback(callback, dev, state, info);
	अगर (error) अणु
		async_error = error;
		जाओ Complete;
	पूर्ण

Skip:
	dev->घातer.is_noirq_suspended = true;

	/*
	 * Skipping the resume of devices that were in use right beक्रमe the
	 * प्रणाली suspend (as indicated by their PM-runसमय usage counters)
	 * would be suboptimal.  Also resume them अगर करोing that is not allowed
	 * to be skipped.
	 */
	अगर (atomic_पढ़ो(&dev->घातer.usage_count) > 1 ||
	    !(dev_pm_test_driver_flags(dev, DPM_FLAG_MAY_SKIP_RESUME) &&
	      dev->घातer.may_skip_resume))
		dev->घातer.must_resume = true;

	अगर (dev->घातer.must_resume)
		dpm_superior_set_must_resume(dev);

Complete:
	complete_all(&dev->घातer.completion);
	TRACE_SUSPEND(error);
	वापस error;
पूर्ण

अटल व्योम async_suspend_noirq(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	पूर्णांक error;

	error = __device_suspend_noirq(dev, pm_transition, true);
	अगर (error) अणु
		dpm_save_failed_dev(dev_name(dev));
		pm_dev_err(dev, pm_transition, " async", error);
	पूर्ण

	put_device(dev);
पूर्ण

अटल पूर्णांक device_suspend_noirq(काष्ठा device *dev)
अणु
	अगर (dpm_async_fn(dev, async_suspend_noirq))
		वापस 0;

	वापस __device_suspend_noirq(dev, pm_transition, false);
पूर्ण

अटल पूर्णांक dpm_noirq_suspend_devices(pm_message_t state)
अणु
	kसमय_प्रकार startसमय = kसमय_get();
	पूर्णांक error = 0;

	trace_suspend_resume(TPS("dpm_suspend_noirq"), state.event, true);
	mutex_lock(&dpm_list_mtx);
	pm_transition = state;
	async_error = 0;

	जबतक (!list_empty(&dpm_late_early_list)) अणु
		काष्ठा device *dev = to_device(dpm_late_early_list.prev);

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		error = device_suspend_noirq(dev);

		mutex_lock(&dpm_list_mtx);
		अगर (error) अणु
			pm_dev_err(dev, state, " noirq", error);
			dpm_save_failed_dev(dev_name(dev));
			put_device(dev);
			अवरोध;
		पूर्ण
		अगर (!list_empty(&dev->घातer.entry))
			list_move(&dev->घातer.entry, &dpm_noirq_list);
		put_device(dev);

		अगर (async_error)
			अवरोध;
	पूर्ण
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	अगर (!error)
		error = async_error;

	अगर (error) अणु
		suspend_stats.failed_suspend_noirq++;
		dpm_save_failed_step(SUSPEND_SUSPEND_NOIRQ);
	पूर्ण
	dpm_show_समय(startसमय, state, error, "noirq");
	trace_suspend_resume(TPS("dpm_suspend_noirq"), state.event, false);
	वापस error;
पूर्ण

/**
 * dpm_suspend_noirq - Execute "noirq suspend" callbacks क्रम all devices.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Prevent device drivers' पूर्णांकerrupt handlers from being called and invoke
 * "noirq" suspend callbacks क्रम all non-sysdev devices.
 */
पूर्णांक dpm_suspend_noirq(pm_message_t state)
अणु
	पूर्णांक ret;

	cpuidle_छोड़ो();

	device_wakeup_arm_wake_irqs();
	suspend_device_irqs();

	ret = dpm_noirq_suspend_devices(state);
	अगर (ret)
		dpm_resume_noirq(resume_event(state));

	वापस ret;
पूर्ण

अटल व्योम dpm_propagate_wakeup_to_parent(काष्ठा device *dev)
अणु
	काष्ठा device *parent = dev->parent;

	अगर (!parent)
		वापस;

	spin_lock_irq(&parent->घातer.lock);

	अगर (device_wakeup_path(dev) && !parent->घातer.ignore_children)
		parent->घातer.wakeup_path = true;

	spin_unlock_irq(&parent->घातer.lock);
पूर्ण

/**
 * __device_suspend_late - Execute a "late suspend" callback क्रम given device.
 * @dev: Device to handle.
 * @state: PM transition of the प्रणाली being carried out.
 * @async: If true, the device is being suspended asynchronously.
 *
 * Runसमय PM is disabled क्रम @dev जबतक this function is being executed.
 */
अटल पूर्णांक __device_suspend_late(काष्ठा device *dev, pm_message_t state, bool async)
अणु
	pm_callback_t callback = शून्य;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;

	TRACE_DEVICE(dev);
	TRACE_SUSPEND(0);

	__pm_runसमय_disable(dev, false);

	dpm_रुको_क्रम_subordinate(dev, async);

	अगर (async_error)
		जाओ Complete;

	अगर (pm_wakeup_pending()) अणु
		async_error = -EBUSY;
		जाओ Complete;
	पूर्ण

	अगर (dev->घातer.syscore || dev->घातer.direct_complete)
		जाओ Complete;

	अगर (dev->pm_करोमुख्य) अणु
		info = "late power domain ";
		callback = pm_late_early_op(&dev->pm_करोमुख्य->ops, state);
	पूर्ण अन्यथा अगर (dev->type && dev->type->pm) अणु
		info = "late type ";
		callback = pm_late_early_op(dev->type->pm, state);
	पूर्ण अन्यथा अगर (dev->class && dev->class->pm) अणु
		info = "late class ";
		callback = pm_late_early_op(dev->class->pm, state);
	पूर्ण अन्यथा अगर (dev->bus && dev->bus->pm) अणु
		info = "late bus ";
		callback = pm_late_early_op(dev->bus->pm, state);
	पूर्ण
	अगर (callback)
		जाओ Run;

	अगर (dev_pm_skip_suspend(dev))
		जाओ Skip;

	अगर (dev->driver && dev->driver->pm) अणु
		info = "late driver ";
		callback = pm_late_early_op(dev->driver->pm, state);
	पूर्ण

Run:
	error = dpm_run_callback(callback, dev, state, info);
	अगर (error) अणु
		async_error = error;
		जाओ Complete;
	पूर्ण
	dpm_propagate_wakeup_to_parent(dev);

Skip:
	dev->घातer.is_late_suspended = true;

Complete:
	TRACE_SUSPEND(error);
	complete_all(&dev->घातer.completion);
	वापस error;
पूर्ण

अटल व्योम async_suspend_late(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	पूर्णांक error;

	error = __device_suspend_late(dev, pm_transition, true);
	अगर (error) अणु
		dpm_save_failed_dev(dev_name(dev));
		pm_dev_err(dev, pm_transition, " async", error);
	पूर्ण
	put_device(dev);
पूर्ण

अटल पूर्णांक device_suspend_late(काष्ठा device *dev)
अणु
	अगर (dpm_async_fn(dev, async_suspend_late))
		वापस 0;

	वापस __device_suspend_late(dev, pm_transition, false);
पूर्ण

/**
 * dpm_suspend_late - Execute "late suspend" callbacks क्रम all devices.
 * @state: PM transition of the प्रणाली being carried out.
 */
पूर्णांक dpm_suspend_late(pm_message_t state)
अणु
	kसमय_प्रकार startसमय = kसमय_get();
	पूर्णांक error = 0;

	trace_suspend_resume(TPS("dpm_suspend_late"), state.event, true);
	mutex_lock(&dpm_list_mtx);
	pm_transition = state;
	async_error = 0;

	जबतक (!list_empty(&dpm_suspended_list)) अणु
		काष्ठा device *dev = to_device(dpm_suspended_list.prev);

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		error = device_suspend_late(dev);

		mutex_lock(&dpm_list_mtx);
		अगर (!list_empty(&dev->घातer.entry))
			list_move(&dev->घातer.entry, &dpm_late_early_list);

		अगर (error) अणु
			pm_dev_err(dev, state, " late", error);
			dpm_save_failed_dev(dev_name(dev));
			put_device(dev);
			अवरोध;
		पूर्ण
		put_device(dev);

		अगर (async_error)
			अवरोध;
	पूर्ण
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	अगर (!error)
		error = async_error;
	अगर (error) अणु
		suspend_stats.failed_suspend_late++;
		dpm_save_failed_step(SUSPEND_SUSPEND_LATE);
		dpm_resume_early(resume_event(state));
	पूर्ण
	dpm_show_समय(startसमय, state, error, "late");
	trace_suspend_resume(TPS("dpm_suspend_late"), state.event, false);
	वापस error;
पूर्ण

/**
 * dpm_suspend_end - Execute "late" and "noirq" device suspend callbacks.
 * @state: PM transition of the प्रणाली being carried out.
 */
पूर्णांक dpm_suspend_end(pm_message_t state)
अणु
	kसमय_प्रकार startसमय = kसमय_get();
	पूर्णांक error;

	error = dpm_suspend_late(state);
	अगर (error)
		जाओ out;

	error = dpm_suspend_noirq(state);
	अगर (error)
		dpm_resume_early(resume_event(state));

out:
	dpm_show_समय(startसमय, state, error, "end");
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(dpm_suspend_end);

/**
 * legacy_suspend - Execute a legacy (bus or class) suspend callback क्रम device.
 * @dev: Device to suspend.
 * @state: PM transition of the प्रणाली being carried out.
 * @cb: Suspend callback to execute.
 * @info: string description of caller.
 */
अटल पूर्णांक legacy_suspend(काष्ठा device *dev, pm_message_t state,
			  पूर्णांक (*cb)(काष्ठा device *dev, pm_message_t state),
			  स्थिर अक्षर *info)
अणु
	पूर्णांक error;
	kसमय_प्रकार callसमय;

	callसमय = initcall_debug_start(dev, cb);

	trace_device_pm_callback_start(dev, info, state.event);
	error = cb(dev, state);
	trace_device_pm_callback_end(dev, error);
	suspend_report_result(cb, error);

	initcall_debug_report(dev, callसमय, cb, error);

	वापस error;
पूर्ण

अटल व्योम dpm_clear_superiors_direct_complete(काष्ठा device *dev)
अणु
	काष्ठा device_link *link;
	पूर्णांक idx;

	अगर (dev->parent) अणु
		spin_lock_irq(&dev->parent->घातer.lock);
		dev->parent->घातer.direct_complete = false;
		spin_unlock_irq(&dev->parent->घातer.lock);
	पूर्ण

	idx = device_links_पढ़ो_lock();

	list_क्रम_each_entry_rcu_locked(link, &dev->links.suppliers, c_node) अणु
		spin_lock_irq(&link->supplier->घातer.lock);
		link->supplier->घातer.direct_complete = false;
		spin_unlock_irq(&link->supplier->घातer.lock);
	पूर्ण

	device_links_पढ़ो_unlock(idx);
पूर्ण

/**
 * __device_suspend - Execute "suspend" callbacks क्रम given device.
 * @dev: Device to handle.
 * @state: PM transition of the प्रणाली being carried out.
 * @async: If true, the device is being suspended asynchronously.
 */
अटल पूर्णांक __device_suspend(काष्ठा device *dev, pm_message_t state, bool async)
अणु
	pm_callback_t callback = शून्य;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;
	DECLARE_DPM_WATCHDOG_ON_STACK(wd);

	TRACE_DEVICE(dev);
	TRACE_SUSPEND(0);

	dpm_रुको_क्रम_subordinate(dev, async);

	अगर (async_error) अणु
		dev->घातer.direct_complete = false;
		जाओ Complete;
	पूर्ण

	/*
	 * Wait क्रम possible runसमय PM transitions of the device in progress
	 * to complete and अगर there's a runसमय resume request pending क्रम it,
	 * resume it beक्रमe proceeding with invoking the प्रणाली-wide suspend
	 * callbacks क्रम it.
	 *
	 * If the प्रणाली-wide suspend callbacks below change the configuration
	 * of the device, they must disable runसमय PM क्रम it or otherwise
	 * ensure that its runसमय-resume callbacks will not be confused by that
	 * change in हाल they are invoked going क्रमward.
	 */
	pm_runसमय_barrier(dev);

	अगर (pm_wakeup_pending()) अणु
		dev->घातer.direct_complete = false;
		async_error = -EBUSY;
		जाओ Complete;
	पूर्ण

	अगर (dev->घातer.syscore)
		जाओ Complete;

	/* Aव्योम direct_complete to let wakeup_path propagate. */
	अगर (device_may_wakeup(dev) || device_wakeup_path(dev))
		dev->घातer.direct_complete = false;

	अगर (dev->घातer.direct_complete) अणु
		अगर (pm_runसमय_status_suspended(dev)) अणु
			pm_runसमय_disable(dev);
			अगर (pm_runसमय_status_suspended(dev)) अणु
				pm_dev_dbg(dev, state, "direct-complete ");
				जाओ Complete;
			पूर्ण

			pm_runसमय_enable(dev);
		पूर्ण
		dev->घातer.direct_complete = false;
	पूर्ण

	dev->घातer.may_skip_resume = true;
	dev->घातer.must_resume = false;

	dpm_watchकरोg_set(&wd, dev);
	device_lock(dev);

	अगर (dev->pm_करोमुख्य) अणु
		info = "power domain ";
		callback = pm_op(&dev->pm_करोमुख्य->ops, state);
		जाओ Run;
	पूर्ण

	अगर (dev->type && dev->type->pm) अणु
		info = "type ";
		callback = pm_op(dev->type->pm, state);
		जाओ Run;
	पूर्ण

	अगर (dev->class && dev->class->pm) अणु
		info = "class ";
		callback = pm_op(dev->class->pm, state);
		जाओ Run;
	पूर्ण

	अगर (dev->bus) अणु
		अगर (dev->bus->pm) अणु
			info = "bus ";
			callback = pm_op(dev->bus->pm, state);
		पूर्ण अन्यथा अगर (dev->bus->suspend) अणु
			pm_dev_dbg(dev, state, "legacy bus ");
			error = legacy_suspend(dev, state, dev->bus->suspend,
						"legacy bus ");
			जाओ End;
		पूर्ण
	पूर्ण

 Run:
	अगर (!callback && dev->driver && dev->driver->pm) अणु
		info = "driver ";
		callback = pm_op(dev->driver->pm, state);
	पूर्ण

	error = dpm_run_callback(callback, dev, state, info);

 End:
	अगर (!error) अणु
		dev->घातer.is_suspended = true;
		अगर (device_may_wakeup(dev))
			dev->घातer.wakeup_path = true;

		dpm_propagate_wakeup_to_parent(dev);
		dpm_clear_superiors_direct_complete(dev);
	पूर्ण

	device_unlock(dev);
	dpm_watchकरोg_clear(&wd);

 Complete:
	अगर (error)
		async_error = error;

	complete_all(&dev->घातer.completion);
	TRACE_SUSPEND(error);
	वापस error;
पूर्ण

अटल व्योम async_suspend(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा device *dev = (काष्ठा device *)data;
	पूर्णांक error;

	error = __device_suspend(dev, pm_transition, true);
	अगर (error) अणु
		dpm_save_failed_dev(dev_name(dev));
		pm_dev_err(dev, pm_transition, " async", error);
	पूर्ण

	put_device(dev);
पूर्ण

अटल पूर्णांक device_suspend(काष्ठा device *dev)
अणु
	अगर (dpm_async_fn(dev, async_suspend))
		वापस 0;

	वापस __device_suspend(dev, pm_transition, false);
पूर्ण

/**
 * dpm_suspend - Execute "suspend" callbacks क्रम all non-sysdev devices.
 * @state: PM transition of the प्रणाली being carried out.
 */
पूर्णांक dpm_suspend(pm_message_t state)
अणु
	kसमय_प्रकार startसमय = kसमय_get();
	पूर्णांक error = 0;

	trace_suspend_resume(TPS("dpm_suspend"), state.event, true);
	might_sleep();

	devfreq_suspend();
	cpufreq_suspend();

	mutex_lock(&dpm_list_mtx);
	pm_transition = state;
	async_error = 0;
	जबतक (!list_empty(&dpm_prepared_list)) अणु
		काष्ठा device *dev = to_device(dpm_prepared_list.prev);

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		error = device_suspend(dev);

		mutex_lock(&dpm_list_mtx);
		अगर (error) अणु
			pm_dev_err(dev, state, "", error);
			dpm_save_failed_dev(dev_name(dev));
			put_device(dev);
			अवरोध;
		पूर्ण
		अगर (!list_empty(&dev->घातer.entry))
			list_move(&dev->घातer.entry, &dpm_suspended_list);
		put_device(dev);
		अगर (async_error)
			अवरोध;
	पूर्ण
	mutex_unlock(&dpm_list_mtx);
	async_synchronize_full();
	अगर (!error)
		error = async_error;
	अगर (error) अणु
		suspend_stats.failed_suspend++;
		dpm_save_failed_step(SUSPEND_SUSPEND);
	पूर्ण
	dpm_show_समय(startसमय, state, error, शून्य);
	trace_suspend_resume(TPS("dpm_suspend"), state.event, false);
	वापस error;
पूर्ण

/**
 * device_prepare - Prepare a device क्रम प्रणाली घातer transition.
 * @dev: Device to handle.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Execute the ->prepare() callback(s) क्रम given device.  No new children of the
 * device may be रेजिस्टरed after this function has वापसed.
 */
अटल पूर्णांक device_prepare(काष्ठा device *dev, pm_message_t state)
अणु
	पूर्णांक (*callback)(काष्ठा device *) = शून्य;
	पूर्णांक ret = 0;

	अगर (dev->घातer.syscore)
		वापस 0;

	/*
	 * If a device's parent goes पूर्णांकo runसमय suspend at the wrong समय,
	 * it won't be possible to resume the device.  To prevent this we
	 * block runसमय suspend here, during the prepare phase, and allow
	 * it again during the complete phase.
	 */
	pm_runसमय_get_noresume(dev);

	device_lock(dev);

	dev->घातer.wakeup_path = false;

	अगर (dev->घातer.no_pm_callbacks)
		जाओ unlock;

	अगर (dev->pm_करोमुख्य)
		callback = dev->pm_करोमुख्य->ops.prepare;
	अन्यथा अगर (dev->type && dev->type->pm)
		callback = dev->type->pm->prepare;
	अन्यथा अगर (dev->class && dev->class->pm)
		callback = dev->class->pm->prepare;
	अन्यथा अगर (dev->bus && dev->bus->pm)
		callback = dev->bus->pm->prepare;

	अगर (!callback && dev->driver && dev->driver->pm)
		callback = dev->driver->pm->prepare;

	अगर (callback)
		ret = callback(dev);

unlock:
	device_unlock(dev);

	अगर (ret < 0) अणु
		suspend_report_result(callback, ret);
		pm_runसमय_put(dev);
		वापस ret;
	पूर्ण
	/*
	 * A positive वापस value from ->prepare() means "this device appears
	 * to be runसमय-suspended and its state is fine, so अगर it really is
	 * runसमय-suspended, you can leave it in that state provided that you
	 * will करो the same thing with all of its descendants".  This only
	 * applies to suspend transitions, however.
	 */
	spin_lock_irq(&dev->घातer.lock);
	dev->घातer.direct_complete = state.event == PM_EVENT_SUSPEND &&
		(ret > 0 || dev->घातer.no_pm_callbacks) &&
		!dev_pm_test_driver_flags(dev, DPM_FLAG_NO_सूचीECT_COMPLETE);
	spin_unlock_irq(&dev->घातer.lock);
	वापस 0;
पूर्ण

/**
 * dpm_prepare - Prepare all non-sysdev devices क्रम a प्रणाली PM transition.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Execute the ->prepare() callback(s) क्रम all devices.
 */
पूर्णांक dpm_prepare(pm_message_t state)
अणु
	पूर्णांक error = 0;

	trace_suspend_resume(TPS("dpm_prepare"), state.event, true);
	might_sleep();

	/*
	 * Give a chance क्रम the known devices to complete their probes, beक्रमe
	 * disable probing of devices. This sync poपूर्णांक is important at least
	 * at boot समय + hibernation restore.
	 */
	रुको_क्रम_device_probe();
	/*
	 * It is unsafe अगर probing of devices will happen during suspend or
	 * hibernation and प्रणाली behavior will be unpredictable in this हाल.
	 * So, let's prohibit device's probing here and defer their probes
	 * instead. The normal behavior will be restored in dpm_complete().
	 */
	device_block_probing();

	mutex_lock(&dpm_list_mtx);
	जबतक (!list_empty(&dpm_list)) अणु
		काष्ठा device *dev = to_device(dpm_list.next);

		get_device(dev);
		mutex_unlock(&dpm_list_mtx);

		trace_device_pm_callback_start(dev, "", state.event);
		error = device_prepare(dev, state);
		trace_device_pm_callback_end(dev, error);

		mutex_lock(&dpm_list_mtx);
		अगर (error) अणु
			अगर (error == -EAGAIN) अणु
				put_device(dev);
				error = 0;
				जारी;
			पूर्ण
			dev_info(dev, "not prepared for power transition: code %d\n",
				 error);
			put_device(dev);
			अवरोध;
		पूर्ण
		dev->घातer.is_prepared = true;
		अगर (!list_empty(&dev->घातer.entry))
			list_move_tail(&dev->घातer.entry, &dpm_prepared_list);
		put_device(dev);
	पूर्ण
	mutex_unlock(&dpm_list_mtx);
	trace_suspend_resume(TPS("dpm_prepare"), state.event, false);
	वापस error;
पूर्ण

/**
 * dpm_suspend_start - Prepare devices क्रम PM transition and suspend them.
 * @state: PM transition of the प्रणाली being carried out.
 *
 * Prepare all non-sysdev devices क्रम प्रणाली PM transition and execute "suspend"
 * callbacks क्रम them.
 */
पूर्णांक dpm_suspend_start(pm_message_t state)
अणु
	kसमय_प्रकार startसमय = kसमय_get();
	पूर्णांक error;

	error = dpm_prepare(state);
	अगर (error) अणु
		suspend_stats.failed_prepare++;
		dpm_save_failed_step(SUSPEND_PREPARE);
	पूर्ण अन्यथा
		error = dpm_suspend(state);
	dpm_show_समय(startसमय, state, error, "start");
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(dpm_suspend_start);

व्योम __suspend_report_result(स्थिर अक्षर *function, व्योम *fn, पूर्णांक ret)
अणु
	अगर (ret)
		pr_err("%s(): %pS returns %d\n", function, fn, ret);
पूर्ण
EXPORT_SYMBOL_GPL(__suspend_report_result);

/**
 * device_pm_रुको_क्रम_dev - Wait क्रम suspend/resume of a device to complete.
 * @subordinate: Device that needs to रुको क्रम @dev.
 * @dev: Device to रुको क्रम.
 */
पूर्णांक device_pm_रुको_क्रम_dev(काष्ठा device *subordinate, काष्ठा device *dev)
अणु
	dpm_रुको(dev, subordinate->घातer.async_suspend);
	वापस async_error;
पूर्ण
EXPORT_SYMBOL_GPL(device_pm_रुको_क्रम_dev);

/**
 * dpm_क्रम_each_dev - device iterator.
 * @data: data क्रम the callback.
 * @fn: function to be called क्रम each device.
 *
 * Iterate over devices in dpm_list, and call @fn क्रम each device,
 * passing it @data.
 */
व्योम dpm_क्रम_each_dev(व्योम *data, व्योम (*fn)(काष्ठा device *, व्योम *))
अणु
	काष्ठा device *dev;

	अगर (!fn)
		वापस;

	device_pm_lock();
	list_क्रम_each_entry(dev, &dpm_list, घातer.entry)
		fn(dev, data);
	device_pm_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(dpm_क्रम_each_dev);

अटल bool pm_ops_is_empty(स्थिर काष्ठा dev_pm_ops *ops)
अणु
	अगर (!ops)
		वापस true;

	वापस !ops->prepare &&
	       !ops->suspend &&
	       !ops->suspend_late &&
	       !ops->suspend_noirq &&
	       !ops->resume_noirq &&
	       !ops->resume_early &&
	       !ops->resume &&
	       !ops->complete;
पूर्ण

व्योम device_pm_check_callbacks(काष्ठा device *dev)
अणु
	spin_lock_irq(&dev->घातer.lock);
	dev->घातer.no_pm_callbacks =
		(!dev->bus || (pm_ops_is_empty(dev->bus->pm) &&
		 !dev->bus->suspend && !dev->bus->resume)) &&
		(!dev->class || pm_ops_is_empty(dev->class->pm)) &&
		(!dev->type || pm_ops_is_empty(dev->type->pm)) &&
		(!dev->pm_करोमुख्य || pm_ops_is_empty(&dev->pm_करोमुख्य->ops)) &&
		(!dev->driver || (pm_ops_is_empty(dev->driver->pm) &&
		 !dev->driver->suspend && !dev->driver->resume));
	spin_unlock_irq(&dev->घातer.lock);
पूर्ण

bool dev_pm_skip_suspend(काष्ठा device *dev)
अणु
	वापस dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND) &&
		pm_runसमय_status_suspended(dev);
पूर्ण
