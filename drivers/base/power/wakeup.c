<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/घातer/wakeup.c - System wakeup events framework
 *
 * Copyright (c) 2010 Rafael J. Wysocki <rjw@sisk.pl>, Novell Inc.
 */
#घोषणा pr_fmt(fmt) "PM: " fmt

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/capability.h>
#समावेश <linux/export.h>
#समावेश <linux/suspend.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <trace/events/घातer.h>

#समावेश "power.h"

#अगर_अघोषित CONFIG_SUSPEND
suspend_state_t pm_suspend_target_state;
#घोषणा pm_suspend_target_state	(PM_SUSPEND_ON)
#पूर्ण_अगर

#घोषणा list_क्रम_each_entry_rcu_locked(pos, head, member) \
	list_क्रम_each_entry_rcu(pos, head, member, \
		srcu_पढ़ो_lock_held(&wakeup_srcu))
/*
 * If set, the suspend/hibernate code will पात transitions to a sleep state
 * अगर wakeup events are रेजिस्टरed during or immediately beक्रमe the transition.
 */
bool events_check_enabled __पढ़ो_mostly;

/* First wakeup IRQ seen by the kernel in the last cycle. */
अचिन्हित पूर्णांक pm_wakeup_irq __पढ़ो_mostly;

/* If greater than 0 and the प्रणाली is suspending, terminate the suspend. */
अटल atomic_t pm_पात_suspend __पढ़ो_mostly;

/*
 * Combined counters of रेजिस्टरed wakeup events and wakeup events in progress.
 * They need to be modअगरied together atomically, so it's better to use one
 * atomic variable to hold them both.
 */
अटल atomic_t combined_event_count = ATOMIC_INIT(0);

#घोषणा IN_PROGRESS_BITS	(माप(पूर्णांक) * 4)
#घोषणा MAX_IN_PROGRESS		((1 << IN_PROGRESS_BITS) - 1)

अटल व्योम split_counters(अचिन्हित पूर्णांक *cnt, अचिन्हित पूर्णांक *inpr)
अणु
	अचिन्हित पूर्णांक comb = atomic_पढ़ो(&combined_event_count);

	*cnt = (comb >> IN_PROGRESS_BITS);
	*inpr = comb & MAX_IN_PROGRESS;
पूर्ण

/* A preserved old value of the events counter. */
अटल अचिन्हित पूर्णांक saved_count;

अटल DEFINE_RAW_SPINLOCK(events_lock);

अटल व्योम pm_wakeup_समयr_fn(काष्ठा समयr_list *t);

अटल LIST_HEAD(wakeup_sources);

अटल DECLARE_WAIT_QUEUE_HEAD(wakeup_count_रुको_queue);

DEFINE_STATIC_SRCU(wakeup_srcu);

अटल काष्ठा wakeup_source deleted_ws = अणु
	.name = "deleted",
	.lock =  __SPIN_LOCK_UNLOCKED(deleted_ws.lock),
पूर्ण;

अटल DEFINE_IDA(wakeup_ida);

/**
 * wakeup_source_create - Create a काष्ठा wakeup_source object.
 * @name: Name of the new wakeup source.
 */
काष्ठा wakeup_source *wakeup_source_create(स्थिर अक्षर *name)
अणु
	काष्ठा wakeup_source *ws;
	स्थिर अक्षर *ws_name;
	पूर्णांक id;

	ws = kzalloc(माप(*ws), GFP_KERNEL);
	अगर (!ws)
		जाओ err_ws;

	ws_name = kstrdup_स्थिर(name, GFP_KERNEL);
	अगर (!ws_name)
		जाओ err_name;
	ws->name = ws_name;

	id = ida_alloc(&wakeup_ida, GFP_KERNEL);
	अगर (id < 0)
		जाओ err_id;
	ws->id = id;

	वापस ws;

err_id:
	kमुक्त_स्थिर(ws->name);
err_name:
	kमुक्त(ws);
err_ws:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_source_create);

/*
 * Record wakeup_source statistics being deleted पूर्णांकo a dummy wakeup_source.
 */
अटल व्योम wakeup_source_record(काष्ठा wakeup_source *ws)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&deleted_ws.lock, flags);

	अगर (ws->event_count) अणु
		deleted_ws.total_समय =
			kसमय_add(deleted_ws.total_समय, ws->total_समय);
		deleted_ws.prevent_sleep_समय =
			kसमय_add(deleted_ws.prevent_sleep_समय,
				  ws->prevent_sleep_समय);
		deleted_ws.max_समय =
			kसमय_compare(deleted_ws.max_समय, ws->max_समय) > 0 ?
				deleted_ws.max_समय : ws->max_समय;
		deleted_ws.event_count += ws->event_count;
		deleted_ws.active_count += ws->active_count;
		deleted_ws.relax_count += ws->relax_count;
		deleted_ws.expire_count += ws->expire_count;
		deleted_ws.wakeup_count += ws->wakeup_count;
	पूर्ण

	spin_unlock_irqrestore(&deleted_ws.lock, flags);
पूर्ण

अटल व्योम wakeup_source_मुक्त(काष्ठा wakeup_source *ws)
अणु
	ida_मुक्त(&wakeup_ida, ws->id);
	kमुक्त_स्थिर(ws->name);
	kमुक्त(ws);
पूर्ण

/**
 * wakeup_source_destroy - Destroy a काष्ठा wakeup_source object.
 * @ws: Wakeup source to destroy.
 *
 * Use only क्रम wakeup source objects created with wakeup_source_create().
 */
व्योम wakeup_source_destroy(काष्ठा wakeup_source *ws)
अणु
	अगर (!ws)
		वापस;

	__pm_relax(ws);
	wakeup_source_record(ws);
	wakeup_source_मुक्त(ws);
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_source_destroy);

/**
 * wakeup_source_add - Add given object to the list of wakeup sources.
 * @ws: Wakeup source object to add to the list.
 */
व्योम wakeup_source_add(काष्ठा wakeup_source *ws)
अणु
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!ws))
		वापस;

	spin_lock_init(&ws->lock);
	समयr_setup(&ws->समयr, pm_wakeup_समयr_fn, 0);
	ws->active = false;

	raw_spin_lock_irqsave(&events_lock, flags);
	list_add_rcu(&ws->entry, &wakeup_sources);
	raw_spin_unlock_irqrestore(&events_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_source_add);

/**
 * wakeup_source_हटाओ - Remove given object from the wakeup sources list.
 * @ws: Wakeup source object to हटाओ from the list.
 */
व्योम wakeup_source_हटाओ(काष्ठा wakeup_source *ws)
अणु
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!ws))
		वापस;

	raw_spin_lock_irqsave(&events_lock, flags);
	list_del_rcu(&ws->entry);
	raw_spin_unlock_irqrestore(&events_lock, flags);
	synchronize_srcu(&wakeup_srcu);

	del_समयr_sync(&ws->समयr);
	/*
	 * Clear समयr.function to make wakeup_source_not_रेजिस्टरed() treat
	 * this wakeup source as not रेजिस्टरed.
	 */
	ws->समयr.function = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_source_हटाओ);

/**
 * wakeup_source_रेजिस्टर - Create wakeup source and add it to the list.
 * @dev: Device this wakeup source is associated with (or शून्य अगर भव).
 * @name: Name of the wakeup source to रेजिस्टर.
 */
काष्ठा wakeup_source *wakeup_source_रेजिस्टर(काष्ठा device *dev,
					     स्थिर अक्षर *name)
अणु
	काष्ठा wakeup_source *ws;
	पूर्णांक ret;

	ws = wakeup_source_create(name);
	अगर (ws) अणु
		अगर (!dev || device_is_रेजिस्टरed(dev)) अणु
			ret = wakeup_source_sysfs_add(dev, ws);
			अगर (ret) अणु
				wakeup_source_मुक्त(ws);
				वापस शून्य;
			पूर्ण
		पूर्ण
		wakeup_source_add(ws);
	पूर्ण
	वापस ws;
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_source_रेजिस्टर);

/**
 * wakeup_source_unरेजिस्टर - Remove wakeup source from the list and हटाओ it.
 * @ws: Wakeup source object to unरेजिस्टर.
 */
व्योम wakeup_source_unरेजिस्टर(काष्ठा wakeup_source *ws)
अणु
	अगर (ws) अणु
		wakeup_source_हटाओ(ws);
		अगर (ws->dev)
			wakeup_source_sysfs_हटाओ(ws);

		wakeup_source_destroy(ws);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_source_unरेजिस्टर);

/**
 * wakeup_sources_पढ़ो_lock - Lock wakeup source list क्रम पढ़ो.
 *
 * Returns an index of srcu lock क्रम काष्ठा wakeup_srcu.
 * This index must be passed to the matching wakeup_sources_पढ़ो_unlock().
 */
पूर्णांक wakeup_sources_पढ़ो_lock(व्योम)
अणु
	वापस srcu_पढ़ो_lock(&wakeup_srcu);
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_sources_पढ़ो_lock);

/**
 * wakeup_sources_पढ़ो_unlock - Unlock wakeup source list.
 * @idx: वापस value from corresponding wakeup_sources_पढ़ो_lock()
 */
व्योम wakeup_sources_पढ़ो_unlock(पूर्णांक idx)
अणु
	srcu_पढ़ो_unlock(&wakeup_srcu, idx);
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_sources_पढ़ो_unlock);

/**
 * wakeup_sources_walk_start - Begin a walk on wakeup source list
 *
 * Returns first object of the list of wakeup sources.
 *
 * Note that to be safe, wakeup sources list needs to be locked by calling
 * wakeup_source_पढ़ो_lock() क्रम this.
 */
काष्ठा wakeup_source *wakeup_sources_walk_start(व्योम)
अणु
	काष्ठा list_head *ws_head = &wakeup_sources;

	वापस list_entry_rcu(ws_head->next, काष्ठा wakeup_source, entry);
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_sources_walk_start);

/**
 * wakeup_sources_walk_next - Get next wakeup source from the list
 * @ws: Previous wakeup source object
 *
 * Note that to be safe, wakeup sources list needs to be locked by calling
 * wakeup_source_पढ़ो_lock() क्रम this.
 */
काष्ठा wakeup_source *wakeup_sources_walk_next(काष्ठा wakeup_source *ws)
अणु
	काष्ठा list_head *ws_head = &wakeup_sources;

	वापस list_next_or_null_rcu(ws_head, &ws->entry,
				काष्ठा wakeup_source, entry);
पूर्ण
EXPORT_SYMBOL_GPL(wakeup_sources_walk_next);

/**
 * device_wakeup_attach - Attach a wakeup source object to a device object.
 * @dev: Device to handle.
 * @ws: Wakeup source object to attach to @dev.
 *
 * This causes @dev to be treated as a wakeup device.
 */
अटल पूर्णांक device_wakeup_attach(काष्ठा device *dev, काष्ठा wakeup_source *ws)
अणु
	spin_lock_irq(&dev->घातer.lock);
	अगर (dev->घातer.wakeup) अणु
		spin_unlock_irq(&dev->घातer.lock);
		वापस -EEXIST;
	पूर्ण
	dev->घातer.wakeup = ws;
	अगर (dev->घातer.wakeirq)
		device_wakeup_attach_irq(dev, dev->घातer.wakeirq);
	spin_unlock_irq(&dev->घातer.lock);
	वापस 0;
पूर्ण

/**
 * device_wakeup_enable - Enable given device to be a wakeup source.
 * @dev: Device to handle.
 *
 * Create a wakeup source object, रेजिस्टर it and attach it to @dev.
 */
पूर्णांक device_wakeup_enable(काष्ठा device *dev)
अणु
	काष्ठा wakeup_source *ws;
	पूर्णांक ret;

	अगर (!dev || !dev->घातer.can_wakeup)
		वापस -EINVAL;

	अगर (pm_suspend_target_state != PM_SUSPEND_ON)
		dev_dbg(dev, "Suspicious %s() during system transition!\n", __func__);

	ws = wakeup_source_रेजिस्टर(dev, dev_name(dev));
	अगर (!ws)
		वापस -ENOMEM;

	ret = device_wakeup_attach(dev, ws);
	अगर (ret)
		wakeup_source_unरेजिस्टर(ws);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(device_wakeup_enable);

/**
 * device_wakeup_attach_irq - Attach a wakeirq to a wakeup source
 * @dev: Device to handle
 * @wakeirq: Device specअगरic wakeirq entry
 *
 * Attach a device wakeirq to the wakeup source so the device
 * wake IRQ can be configured स्वतःmatically क्रम suspend and
 * resume.
 *
 * Call under the device's घातer.lock lock.
 */
व्योम device_wakeup_attach_irq(काष्ठा device *dev,
			     काष्ठा wake_irq *wakeirq)
अणु
	काष्ठा wakeup_source *ws;

	ws = dev->घातer.wakeup;
	अगर (!ws)
		वापस;

	अगर (ws->wakeirq)
		dev_err(dev, "Leftover wakeup IRQ found, overriding\n");

	ws->wakeirq = wakeirq;
पूर्ण

/**
 * device_wakeup_detach_irq - Detach a wakeirq from a wakeup source
 * @dev: Device to handle
 *
 * Removes a device wakeirq from the wakeup source.
 *
 * Call under the device's घातer.lock lock.
 */
व्योम device_wakeup_detach_irq(काष्ठा device *dev)
अणु
	काष्ठा wakeup_source *ws;

	ws = dev->घातer.wakeup;
	अगर (ws)
		ws->wakeirq = शून्य;
पूर्ण

/**
 * device_wakeup_arm_wake_irqs -
 *
 * Iterates over the list of device wakeirqs to arm them.
 */
व्योम device_wakeup_arm_wake_irqs(व्योम)
अणु
	काष्ठा wakeup_source *ws;
	पूर्णांक srcuidx;

	srcuidx = srcu_पढ़ो_lock(&wakeup_srcu);
	list_क्रम_each_entry_rcu_locked(ws, &wakeup_sources, entry)
		dev_pm_arm_wake_irq(ws->wakeirq);
	srcu_पढ़ो_unlock(&wakeup_srcu, srcuidx);
पूर्ण

/**
 * device_wakeup_disarm_wake_irqs -
 *
 * Iterates over the list of device wakeirqs to disarm them.
 */
व्योम device_wakeup_disarm_wake_irqs(व्योम)
अणु
	काष्ठा wakeup_source *ws;
	पूर्णांक srcuidx;

	srcuidx = srcu_पढ़ो_lock(&wakeup_srcu);
	list_क्रम_each_entry_rcu_locked(ws, &wakeup_sources, entry)
		dev_pm_disarm_wake_irq(ws->wakeirq);
	srcu_पढ़ो_unlock(&wakeup_srcu, srcuidx);
पूर्ण

/**
 * device_wakeup_detach - Detach a device's wakeup source object from it.
 * @dev: Device to detach the wakeup source object from.
 *
 * After it वापसs, @dev will not be treated as a wakeup device any more.
 */
अटल काष्ठा wakeup_source *device_wakeup_detach(काष्ठा device *dev)
अणु
	काष्ठा wakeup_source *ws;

	spin_lock_irq(&dev->घातer.lock);
	ws = dev->घातer.wakeup;
	dev->घातer.wakeup = शून्य;
	spin_unlock_irq(&dev->घातer.lock);
	वापस ws;
पूर्ण

/**
 * device_wakeup_disable - Do not regard a device as a wakeup source any more.
 * @dev: Device to handle.
 *
 * Detach the @dev's wakeup source object from it, unरेजिस्टर this wakeup source
 * object and destroy it.
 */
पूर्णांक device_wakeup_disable(काष्ठा device *dev)
अणु
	काष्ठा wakeup_source *ws;

	अगर (!dev || !dev->घातer.can_wakeup)
		वापस -EINVAL;

	ws = device_wakeup_detach(dev);
	wakeup_source_unरेजिस्टर(ws);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(device_wakeup_disable);

/**
 * device_set_wakeup_capable - Set/reset device wakeup capability flag.
 * @dev: Device to handle.
 * @capable: Whether or not @dev is capable of waking up the प्रणाली from sleep.
 *
 * If @capable is set, set the @dev's घातer.can_wakeup flag and add its
 * wakeup-related attributes to sysfs.  Otherwise, unset the @dev's
 * घातer.can_wakeup flag and हटाओ its wakeup-related attributes from sysfs.
 *
 * This function may sleep and it can't be called from any context where
 * sleeping is not allowed.
 */
व्योम device_set_wakeup_capable(काष्ठा device *dev, bool capable)
अणु
	अगर (!!dev->घातer.can_wakeup == !!capable)
		वापस;

	dev->घातer.can_wakeup = capable;
	अगर (device_is_रेजिस्टरed(dev) && !list_empty(&dev->घातer.entry)) अणु
		अगर (capable) अणु
			पूर्णांक ret = wakeup_sysfs_add(dev);

			अगर (ret)
				dev_info(dev, "Wakeup sysfs attributes not added\n");
		पूर्ण अन्यथा अणु
			wakeup_sysfs_हटाओ(dev);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(device_set_wakeup_capable);

/**
 * device_init_wakeup - Device wakeup initialization.
 * @dev: Device to handle.
 * @enable: Whether or not to enable @dev as a wakeup device.
 *
 * By शेष, most devices should leave wakeup disabled.  The exceptions are
 * devices that everyone expects to be wakeup sources: keyboards, घातer buttons,
 * possibly network पूर्णांकerfaces, etc.  Also, devices that करोn't generate their
 * own wakeup requests but merely क्रमward requests from one bus to another
 * (like PCI bridges) should have wakeup enabled by शेष.
 */
पूर्णांक device_init_wakeup(काष्ठा device *dev, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (!dev)
		वापस -EINVAL;

	अगर (enable) अणु
		device_set_wakeup_capable(dev, true);
		ret = device_wakeup_enable(dev);
	पूर्ण अन्यथा अणु
		device_wakeup_disable(dev);
		device_set_wakeup_capable(dev, false);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(device_init_wakeup);

/**
 * device_set_wakeup_enable - Enable or disable a device to wake up the प्रणाली.
 * @dev: Device to handle.
 * @enable: enable/disable flag
 */
पूर्णांक device_set_wakeup_enable(काष्ठा device *dev, bool enable)
अणु
	वापस enable ? device_wakeup_enable(dev) : device_wakeup_disable(dev);
पूर्ण
EXPORT_SYMBOL_GPL(device_set_wakeup_enable);

/**
 * wakeup_source_not_रेजिस्टरed - validate the given wakeup source.
 * @ws: Wakeup source to be validated.
 */
अटल bool wakeup_source_not_रेजिस्टरed(काष्ठा wakeup_source *ws)
अणु
	/*
	 * Use समयr काष्ठा to check अगर the given source is initialized
	 * by wakeup_source_add.
	 */
	वापस ws->समयr.function != pm_wakeup_समयr_fn;
पूर्ण

/*
 * The functions below use the observation that each wakeup event starts a
 * period in which the प्रणाली should not be suspended.  The moment this period
 * will end depends on how the wakeup event is going to be processed after being
 * detected and all of the possible हालs can be भागided पूर्णांकo two distinct
 * groups.
 *
 * First, a wakeup event may be detected by the same functional unit that will
 * carry out the entire processing of it and possibly will pass it to user space
 * क्रम further processing.  In that हाल the functional unit that has detected
 * the event may later "close" the "no suspend" period associated with it
 * directly as soon as it has been dealt with.  The pair of pm_stay_awake() and
 * pm_relax(), balanced with each other, is supposed to be used in such
 * situations.
 *
 * Second, a wakeup event may be detected by one functional unit and processed
 * by another one.  In that हाल the unit that has detected it cannot really
 * "close" the "no suspend" period associated with it, unless it knows in
 * advance what's going to happen to the event during processing.  This
 * knowledge, however, may not be available to it, so it can simply specअगरy समय
 * to रुको beक्रमe the प्रणाली can be suspended and pass it as the second
 * argument of pm_wakeup_event().
 *
 * It is valid to call pm_relax() after pm_wakeup_event(), in which हाल the
 * "no suspend" period will be ended either by the pm_relax(), or by the समयr
 * function executed when the समयr expires, whichever comes first.
 */

/**
 * wakeup_source_activate - Mark given wakeup source as active.
 * @ws: Wakeup source to handle.
 *
 * Update the @ws' statistics and, अगर @ws has just been activated, notअगरy the PM
 * core of the event by incrementing the counter of of wakeup events being
 * processed.
 */
अटल व्योम wakeup_source_activate(काष्ठा wakeup_source *ws)
अणु
	अचिन्हित पूर्णांक cec;

	अगर (WARN_ONCE(wakeup_source_not_रेजिस्टरed(ws),
			"unregistered wakeup source\n"))
		वापस;

	ws->active = true;
	ws->active_count++;
	ws->last_समय = kसमय_get();
	अगर (ws->स्वतःsleep_enabled)
		ws->start_prevent_समय = ws->last_समय;

	/* Increment the counter of events in progress. */
	cec = atomic_inc_वापस(&combined_event_count);

	trace_wakeup_source_activate(ws->name, cec);
पूर्ण

/**
 * wakeup_source_report_event - Report wakeup event using the given source.
 * @ws: Wakeup source to report the event क्रम.
 * @hard: If set, पात suspends in progress and wake up from suspend-to-idle.
 */
अटल व्योम wakeup_source_report_event(काष्ठा wakeup_source *ws, bool hard)
अणु
	ws->event_count++;
	/* This is racy, but the counter is approximate anyway. */
	अगर (events_check_enabled)
		ws->wakeup_count++;

	अगर (!ws->active)
		wakeup_source_activate(ws);

	अगर (hard)
		pm_प्रणाली_wakeup();
पूर्ण

/**
 * __pm_stay_awake - Notअगरy the PM core of a wakeup event.
 * @ws: Wakeup source object associated with the source of the event.
 *
 * It is safe to call this function from पूर्णांकerrupt context.
 */
व्योम __pm_stay_awake(काष्ठा wakeup_source *ws)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!ws)
		वापस;

	spin_lock_irqsave(&ws->lock, flags);

	wakeup_source_report_event(ws, false);
	del_समयr(&ws->समयr);
	ws->समयr_expires = 0;

	spin_unlock_irqrestore(&ws->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(__pm_stay_awake);

/**
 * pm_stay_awake - Notअगरy the PM core that a wakeup event is being processed.
 * @dev: Device the wakeup event is related to.
 *
 * Notअगरy the PM core of a wakeup event (संकेतed by @dev) by calling
 * __pm_stay_awake क्रम the @dev's wakeup source object.
 *
 * Call this function after detecting of a wakeup event अगर pm_relax() is going
 * to be called directly after processing the event (and possibly passing it to
 * user space क्रम further processing).
 */
व्योम pm_stay_awake(काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!dev)
		वापस;

	spin_lock_irqsave(&dev->घातer.lock, flags);
	__pm_stay_awake(dev->घातer.wakeup);
	spin_unlock_irqrestore(&dev->घातer.lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pm_stay_awake);

#अगर_घोषित CONFIG_PM_AUTOSLEEP
अटल व्योम update_prevent_sleep_समय(काष्ठा wakeup_source *ws, kसमय_प्रकार now)
अणु
	kसमय_प्रकार delta = kसमय_sub(now, ws->start_prevent_समय);
	ws->prevent_sleep_समय = kसमय_add(ws->prevent_sleep_समय, delta);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम update_prevent_sleep_समय(काष्ठा wakeup_source *ws,
					     kसमय_प्रकार now) अणुपूर्ण
#पूर्ण_अगर

/**
 * wakeup_source_deactivate - Mark given wakeup source as inactive.
 * @ws: Wakeup source to handle.
 *
 * Update the @ws' statistics and notअगरy the PM core that the wakeup source has
 * become inactive by decrementing the counter of wakeup events being processed
 * and incrementing the counter of रेजिस्टरed wakeup events.
 */
अटल व्योम wakeup_source_deactivate(काष्ठा wakeup_source *ws)
अणु
	अचिन्हित पूर्णांक cnt, inpr, cec;
	kसमय_प्रकार duration;
	kसमय_प्रकार now;

	ws->relax_count++;
	/*
	 * __pm_relax() may be called directly or from a समयr function.
	 * If it is called directly right after the समयr function has been
	 * started, but beक्रमe the समयr function calls __pm_relax(), it is
	 * possible that __pm_stay_awake() will be called in the meanसमय and
	 * will set ws->active.  Then, ws->active may be cleared immediately
	 * by the __pm_relax() called from the समयr function, but in such a
	 * हाल ws->relax_count will be dअगरferent from ws->active_count.
	 */
	अगर (ws->relax_count != ws->active_count) अणु
		ws->relax_count--;
		वापस;
	पूर्ण

	ws->active = false;

	now = kसमय_get();
	duration = kसमय_sub(now, ws->last_समय);
	ws->total_समय = kसमय_add(ws->total_समय, duration);
	अगर (kसमय_प्रकारo_ns(duration) > kसमय_प्रकारo_ns(ws->max_समय))
		ws->max_समय = duration;

	ws->last_समय = now;
	del_समयr(&ws->समयr);
	ws->समयr_expires = 0;

	अगर (ws->स्वतःsleep_enabled)
		update_prevent_sleep_समय(ws, now);

	/*
	 * Increment the counter of रेजिस्टरed wakeup events and decrement the
	 * couter of wakeup events in progress simultaneously.
	 */
	cec = atomic_add_वापस(MAX_IN_PROGRESS, &combined_event_count);
	trace_wakeup_source_deactivate(ws->name, cec);

	split_counters(&cnt, &inpr);
	अगर (!inpr && रुकोqueue_active(&wakeup_count_रुको_queue))
		wake_up(&wakeup_count_रुको_queue);
पूर्ण

/**
 * __pm_relax - Notअगरy the PM core that processing of a wakeup event has ended.
 * @ws: Wakeup source object associated with the source of the event.
 *
 * Call this function क्रम wakeup events whose processing started with calling
 * __pm_stay_awake().
 *
 * It is safe to call it from पूर्णांकerrupt context.
 */
व्योम __pm_relax(काष्ठा wakeup_source *ws)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!ws)
		वापस;

	spin_lock_irqsave(&ws->lock, flags);
	अगर (ws->active)
		wakeup_source_deactivate(ws);
	spin_unlock_irqrestore(&ws->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(__pm_relax);

/**
 * pm_relax - Notअगरy the PM core that processing of a wakeup event has ended.
 * @dev: Device that संकेतed the event.
 *
 * Execute __pm_relax() क्रम the @dev's wakeup source object.
 */
व्योम pm_relax(काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!dev)
		वापस;

	spin_lock_irqsave(&dev->घातer.lock, flags);
	__pm_relax(dev->घातer.wakeup);
	spin_unlock_irqrestore(&dev->घातer.lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pm_relax);

/**
 * pm_wakeup_समयr_fn - Delayed finalization of a wakeup event.
 * @t: समयr list
 *
 * Call wakeup_source_deactivate() क्रम the wakeup source whose address is stored
 * in @data अगर it is currently active and its समयr has not been canceled and
 * the expiration समय of the समयr is not in future.
 */
अटल व्योम pm_wakeup_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा wakeup_source *ws = from_समयr(ws, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ws->lock, flags);

	अगर (ws->active && ws->समयr_expires
	    && समय_after_eq(jअगरfies, ws->समयr_expires)) अणु
		wakeup_source_deactivate(ws);
		ws->expire_count++;
	पूर्ण

	spin_unlock_irqrestore(&ws->lock, flags);
पूर्ण

/**
 * pm_wakeup_ws_event - Notअगरy the PM core of a wakeup event.
 * @ws: Wakeup source object associated with the event source.
 * @msec: Anticipated event processing समय (in milliseconds).
 * @hard: If set, पात suspends in progress and wake up from suspend-to-idle.
 *
 * Notअगरy the PM core of a wakeup event whose source is @ws that will take
 * approximately @msec milliseconds to be processed by the kernel.  If @ws is
 * not active, activate it.  If @msec is nonzero, set up the @ws' समयr to
 * execute pm_wakeup_समयr_fn() in future.
 *
 * It is safe to call this function from पूर्णांकerrupt context.
 */
व्योम pm_wakeup_ws_event(काष्ठा wakeup_source *ws, अचिन्हित पूर्णांक msec, bool hard)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ expires;

	अगर (!ws)
		वापस;

	spin_lock_irqsave(&ws->lock, flags);

	wakeup_source_report_event(ws, hard);

	अगर (!msec) अणु
		wakeup_source_deactivate(ws);
		जाओ unlock;
	पूर्ण

	expires = jअगरfies + msecs_to_jअगरfies(msec);
	अगर (!expires)
		expires = 1;

	अगर (!ws->समयr_expires || समय_after(expires, ws->समयr_expires)) अणु
		mod_समयr(&ws->समयr, expires);
		ws->समयr_expires = expires;
	पूर्ण

 unlock:
	spin_unlock_irqrestore(&ws->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pm_wakeup_ws_event);

/**
 * pm_wakeup_dev_event - Notअगरy the PM core of a wakeup event.
 * @dev: Device the wakeup event is related to.
 * @msec: Anticipated event processing समय (in milliseconds).
 * @hard: If set, पात suspends in progress and wake up from suspend-to-idle.
 *
 * Call pm_wakeup_ws_event() क्रम the @dev's wakeup source object.
 */
व्योम pm_wakeup_dev_event(काष्ठा device *dev, अचिन्हित पूर्णांक msec, bool hard)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!dev)
		वापस;

	spin_lock_irqsave(&dev->घातer.lock, flags);
	pm_wakeup_ws_event(dev->घातer.wakeup, msec, hard);
	spin_unlock_irqrestore(&dev->घातer.lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(pm_wakeup_dev_event);

व्योम pm_prपूर्णांक_active_wakeup_sources(व्योम)
अणु
	काष्ठा wakeup_source *ws;
	पूर्णांक srcuidx, active = 0;
	काष्ठा wakeup_source *last_activity_ws = शून्य;

	srcuidx = srcu_पढ़ो_lock(&wakeup_srcu);
	list_क्रम_each_entry_rcu_locked(ws, &wakeup_sources, entry) अणु
		अगर (ws->active) अणु
			pm_pr_dbg("active wakeup source: %s\n", ws->name);
			active = 1;
		पूर्ण अन्यथा अगर (!active &&
			   (!last_activity_ws ||
			    kसमय_प्रकारo_ns(ws->last_समय) >
			    kसमय_प्रकारo_ns(last_activity_ws->last_समय))) अणु
			last_activity_ws = ws;
		पूर्ण
	पूर्ण

	अगर (!active && last_activity_ws)
		pm_pr_dbg("last active wakeup source: %s\n",
			last_activity_ws->name);
	srcu_पढ़ो_unlock(&wakeup_srcu, srcuidx);
पूर्ण
EXPORT_SYMBOL_GPL(pm_prपूर्णांक_active_wakeup_sources);

/**
 * pm_wakeup_pending - Check अगर घातer transition in progress should be पातed.
 *
 * Compare the current number of रेजिस्टरed wakeup events with its preserved
 * value from the past and वापस true अगर new wakeup events have been रेजिस्टरed
 * since the old value was stored.  Also वापस true अगर the current number of
 * wakeup events being processed is dअगरferent from zero.
 */
bool pm_wakeup_pending(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	bool ret = false;

	raw_spin_lock_irqsave(&events_lock, flags);
	अगर (events_check_enabled) अणु
		अचिन्हित पूर्णांक cnt, inpr;

		split_counters(&cnt, &inpr);
		ret = (cnt != saved_count || inpr > 0);
		events_check_enabled = !ret;
	पूर्ण
	raw_spin_unlock_irqrestore(&events_lock, flags);

	अगर (ret) अणु
		pm_pr_dbg("Wakeup pending, aborting suspend\n");
		pm_prपूर्णांक_active_wakeup_sources();
	पूर्ण

	वापस ret || atomic_पढ़ो(&pm_पात_suspend) > 0;
पूर्ण

व्योम pm_प्रणाली_wakeup(व्योम)
अणु
	atomic_inc(&pm_पात_suspend);
	s2idle_wake();
पूर्ण
EXPORT_SYMBOL_GPL(pm_प्रणाली_wakeup);

व्योम pm_प्रणाली_cancel_wakeup(व्योम)
अणु
	atomic_dec_अगर_positive(&pm_पात_suspend);
पूर्ण

व्योम pm_wakeup_clear(bool reset)
अणु
	pm_wakeup_irq = 0;
	अगर (reset)
		atomic_set(&pm_पात_suspend, 0);
पूर्ण

व्योम pm_प्रणाली_irq_wakeup(अचिन्हित पूर्णांक irq_number)
अणु
	अगर (pm_wakeup_irq == 0) अणु
		pm_wakeup_irq = irq_number;
		pm_प्रणाली_wakeup();
	पूर्ण
पूर्ण

/**
 * pm_get_wakeup_count - Read the number of रेजिस्टरed wakeup events.
 * @count: Address to store the value at.
 * @block: Whether or not to block.
 *
 * Store the number of रेजिस्टरed wakeup events at the address in @count.  If
 * @block is set, block until the current number of wakeup events being
 * processed is zero.
 *
 * Return 'false' अगर the current number of wakeup events being processed is
 * nonzero.  Otherwise वापस 'true'.
 */
bool pm_get_wakeup_count(अचिन्हित पूर्णांक *count, bool block)
अणु
	अचिन्हित पूर्णांक cnt, inpr;

	अगर (block) अणु
		DEFINE_WAIT(रुको);

		क्रम (;;) अणु
			prepare_to_रुको(&wakeup_count_रुको_queue, &रुको,
					TASK_INTERRUPTIBLE);
			split_counters(&cnt, &inpr);
			अगर (inpr == 0 || संकेत_pending(current))
				अवरोध;
			pm_prपूर्णांक_active_wakeup_sources();
			schedule();
		पूर्ण
		finish_रुको(&wakeup_count_रुको_queue, &रुको);
	पूर्ण

	split_counters(&cnt, &inpr);
	*count = cnt;
	वापस !inpr;
पूर्ण

/**
 * pm_save_wakeup_count - Save the current number of रेजिस्टरed wakeup events.
 * @count: Value to compare with the current number of रेजिस्टरed wakeup events.
 *
 * If @count is equal to the current number of रेजिस्टरed wakeup events and the
 * current number of wakeup events being processed is zero, store @count as the
 * old number of रेजिस्टरed wakeup events क्रम pm_check_wakeup_events(), enable
 * wakeup events detection and वापस 'true'.  Otherwise disable wakeup events
 * detection and वापस 'false'.
 */
bool pm_save_wakeup_count(अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक cnt, inpr;
	अचिन्हित दीर्घ flags;

	events_check_enabled = false;
	raw_spin_lock_irqsave(&events_lock, flags);
	split_counters(&cnt, &inpr);
	अगर (cnt == count && inpr == 0) अणु
		saved_count = count;
		events_check_enabled = true;
	पूर्ण
	raw_spin_unlock_irqrestore(&events_lock, flags);
	वापस events_check_enabled;
पूर्ण

#अगर_घोषित CONFIG_PM_AUTOSLEEP
/**
 * pm_wakep_स्वतःsleep_enabled - Modअगरy स्वतःsleep_enabled क्रम all wakeup sources.
 * @set: Whether to set or to clear the स्वतःsleep_enabled flags.
 */
व्योम pm_wakep_स्वतःsleep_enabled(bool set)
अणु
	काष्ठा wakeup_source *ws;
	kसमय_प्रकार now = kसमय_get();
	पूर्णांक srcuidx;

	srcuidx = srcu_पढ़ो_lock(&wakeup_srcu);
	list_क्रम_each_entry_rcu_locked(ws, &wakeup_sources, entry) अणु
		spin_lock_irq(&ws->lock);
		अगर (ws->स्वतःsleep_enabled != set) अणु
			ws->स्वतःsleep_enabled = set;
			अगर (ws->active) अणु
				अगर (set)
					ws->start_prevent_समय = now;
				अन्यथा
					update_prevent_sleep_समय(ws, now);
			पूर्ण
		पूर्ण
		spin_unlock_irq(&ws->lock);
	पूर्ण
	srcu_पढ़ो_unlock(&wakeup_srcu, srcuidx);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_AUTOSLEEP */

/**
 * prपूर्णांक_wakeup_source_stats - Prपूर्णांक wakeup source statistics inक्रमmation.
 * @m: seq_file to prपूर्णांक the statistics पूर्णांकo.
 * @ws: Wakeup source object to prपूर्णांक the statistics क्रम.
 */
अटल पूर्णांक prपूर्णांक_wakeup_source_stats(काष्ठा seq_file *m,
				     काष्ठा wakeup_source *ws)
अणु
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार total_समय;
	kसमय_प्रकार max_समय;
	अचिन्हित दीर्घ active_count;
	kसमय_प्रकार active_समय;
	kसमय_प्रकार prevent_sleep_समय;

	spin_lock_irqsave(&ws->lock, flags);

	total_समय = ws->total_समय;
	max_समय = ws->max_समय;
	prevent_sleep_समय = ws->prevent_sleep_समय;
	active_count = ws->active_count;
	अगर (ws->active) अणु
		kसमय_प्रकार now = kसमय_get();

		active_समय = kसमय_sub(now, ws->last_समय);
		total_समय = kसमय_add(total_समय, active_समय);
		अगर (active_समय > max_समय)
			max_समय = active_समय;

		अगर (ws->स्वतःsleep_enabled)
			prevent_sleep_समय = kसमय_add(prevent_sleep_समय,
				kसमय_sub(now, ws->start_prevent_समय));
	पूर्ण अन्यथा अणु
		active_समय = 0;
	पूर्ण

	seq_म_लिखो(m, "%-12s\t%lu\t\t%lu\t\t%lu\t\t%lu\t\t%lld\t\t%lld\t\t%lld\t\t%lld\t\t%lld\n",
		   ws->name, active_count, ws->event_count,
		   ws->wakeup_count, ws->expire_count,
		   kसमय_प्रकारo_ms(active_समय), kसमय_प्रकारo_ms(total_समय),
		   kसमय_प्रकारo_ms(max_समय), kसमय_प्रकारo_ms(ws->last_समय),
		   kसमय_प्रकारo_ms(prevent_sleep_समय));

	spin_unlock_irqrestore(&ws->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम *wakeup_sources_stats_seq_start(काष्ठा seq_file *m,
					loff_t *pos)
अणु
	काष्ठा wakeup_source *ws;
	loff_t n = *pos;
	पूर्णांक *srcuidx = m->निजी;

	अगर (n == 0) अणु
		seq_माला_दो(m, "name\t\tactive_count\tevent_count\twakeup_count\t"
			"expire_count\tactive_since\ttotal_time\tmax_time\t"
			"last_change\tprevent_suspend_time\n");
	पूर्ण

	*srcuidx = srcu_पढ़ो_lock(&wakeup_srcu);
	list_क्रम_each_entry_rcu_locked(ws, &wakeup_sources, entry) अणु
		अगर (n-- <= 0)
			वापस ws;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम *wakeup_sources_stats_seq_next(काष्ठा seq_file *m,
					व्योम *v, loff_t *pos)
अणु
	काष्ठा wakeup_source *ws = v;
	काष्ठा wakeup_source *next_ws = शून्य;

	++(*pos);

	list_क्रम_each_entry_जारी_rcu(ws, &wakeup_sources, entry) अणु
		next_ws = ws;
		अवरोध;
	पूर्ण

	अगर (!next_ws)
		prपूर्णांक_wakeup_source_stats(m, &deleted_ws);

	वापस next_ws;
पूर्ण

अटल व्योम wakeup_sources_stats_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक *srcuidx = m->निजी;

	srcu_पढ़ो_unlock(&wakeup_srcu, *srcuidx);
पूर्ण

/**
 * wakeup_sources_stats_seq_show - Prपूर्णांक wakeup sources statistics inक्रमmation.
 * @m: seq_file to prपूर्णांक the statistics पूर्णांकo.
 * @v: wakeup_source of each iteration
 */
अटल पूर्णांक wakeup_sources_stats_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा wakeup_source *ws = v;

	prपूर्णांक_wakeup_source_stats(m, ws);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations wakeup_sources_stats_seq_ops = अणु
	.start = wakeup_sources_stats_seq_start,
	.next  = wakeup_sources_stats_seq_next,
	.stop  = wakeup_sources_stats_seq_stop,
	.show  = wakeup_sources_stats_seq_show,
पूर्ण;

अटल पूर्णांक wakeup_sources_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो_निजी(file, &wakeup_sources_stats_seq_ops, माप(पूर्णांक));
पूर्ण

अटल स्थिर काष्ठा file_operations wakeup_sources_stats_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = wakeup_sources_stats_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release_निजी,
पूर्ण;

अटल पूर्णांक __init wakeup_sources_debugfs_init(व्योम)
अणु
	debugfs_create_file("wakeup_sources", S_IRUGO, शून्य, शून्य,
			    &wakeup_sources_stats_fops);
	वापस 0;
पूर्ण

postcore_initcall(wakeup_sources_debugfs_init);
