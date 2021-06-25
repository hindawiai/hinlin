<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/base/dd.c - The core device/driver पूर्णांकeractions.
 *
 * This file contains the (someबार tricky) code that controls the
 * पूर्णांकeractions between devices and drivers, which primarily includes
 * driver binding and unbinding.
 *
 * All of this code used to exist in drivers/base/bus.c, but was
 * relocated to here in the name of comparपंचांगentalization (since it wasn't
 * strictly code just क्रम the 'struct bus_type'.
 *
 * Copyright (c) 2002-5 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Lअसल
 * Copyright (c) 2007-2009 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (c) 2007-2009 Novell Inc.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>
#समावेश <linux/async.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pinctrl/devinfo.h>
#समावेश <linux/slab.h>

#समावेश "base.h"
#समावेश "power/power.h"

/*
 * Deferred Probe infraकाष्ठाure.
 *
 * Someबार driver probe order matters, but the kernel करोesn't always have
 * dependency inक्रमmation which means some drivers will get probed beक्रमe a
 * resource it depends on is available.  For example, an SDHCI driver may
 * first need a GPIO line from an i2c GPIO controller beक्रमe it can be
 * initialized.  If a required resource is not available yet, a driver can
 * request probing to be deferred by वापसing -EPROBE_DEFER from its probe hook
 *
 * Deferred probe मुख्यtains two lists of devices, a pending list and an active
 * list.  A driver वापसing -EPROBE_DEFER causes the device to be added to the
 * pending list.  A successful driver probe will trigger moving all devices
 * from the pending to the active list so that the workqueue will eventually
 * retry them.
 *
 * The deferred_probe_mutex must be held any समय the deferred_probe_*_list
 * of the (काष्ठा device*)->p->deferred_probe poपूर्णांकers are manipulated
 */
अटल DEFINE_MUTEX(deferred_probe_mutex);
अटल LIST_HEAD(deferred_probe_pending_list);
अटल LIST_HEAD(deferred_probe_active_list);
अटल atomic_t deferred_trigger_count = ATOMIC_INIT(0);
अटल bool initcalls_करोne;

/* Save the async probe drivers' name from kernel cmdline */
#घोषणा ASYNC_DRV_NAMES_MAX_LEN	256
अटल अक्षर async_probe_drv_names[ASYNC_DRV_NAMES_MAX_LEN];

/*
 * In some हालs, like suspend to RAM or hibernation, It might be reasonable
 * to prohibit probing of devices as it could be unsafe.
 * Once defer_all_probes is true all drivers probes will be क्रमcibly deferred.
 */
अटल bool defer_all_probes;

अटल व्योम __device_set_deferred_probe_reason(स्थिर काष्ठा device *dev, अक्षर *reason)
अणु
	kमुक्त(dev->p->deferred_probe_reason);
	dev->p->deferred_probe_reason = reason;
पूर्ण

/*
 * deferred_probe_work_func() - Retry probing devices in the active list.
 */
अटल व्योम deferred_probe_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा device *dev;
	काष्ठा device_निजी *निजी;
	/*
	 * This block processes every device in the deferred 'active' list.
	 * Each device is हटाओd from the active list and passed to
	 * bus_probe_device() to re-attempt the probe.  The loop जारीs
	 * until every device in the active list is हटाओd and retried.
	 *
	 * Note: Once the device is हटाओd from the list and the mutex is
	 * released, it is possible क्रम the device get मुक्तd by another thपढ़ो
	 * and cause a illegal poपूर्णांकer dereference.  This code uses
	 * get/put_device() to ensure the device काष्ठाure cannot disappear
	 * from under our feet.
	 */
	mutex_lock(&deferred_probe_mutex);
	जबतक (!list_empty(&deferred_probe_active_list)) अणु
		निजी = list_first_entry(&deferred_probe_active_list,
					typeof(*dev->p), deferred_probe);
		dev = निजी->device;
		list_del_init(&निजी->deferred_probe);

		get_device(dev);

		__device_set_deferred_probe_reason(dev, शून्य);

		/*
		 * Drop the mutex जबतक probing each device; the probe path may
		 * manipulate the deferred list
		 */
		mutex_unlock(&deferred_probe_mutex);

		/*
		 * Force the device to the end of the dpm_list since
		 * the PM code assumes that the order we add things to
		 * the list is a good order क्रम suspend but deferred
		 * probe makes that very unsafe.
		 */
		device_pm_move_to_tail(dev);

		dev_dbg(dev, "Retrying from deferred list\n");
		bus_probe_device(dev);
		mutex_lock(&deferred_probe_mutex);

		put_device(dev);
	पूर्ण
	mutex_unlock(&deferred_probe_mutex);
पूर्ण
अटल DECLARE_WORK(deferred_probe_work, deferred_probe_work_func);

व्योम driver_deferred_probe_add(काष्ठा device *dev)
अणु
	अगर (!dev->can_match)
		वापस;

	mutex_lock(&deferred_probe_mutex);
	अगर (list_empty(&dev->p->deferred_probe)) अणु
		dev_dbg(dev, "Added to deferred list\n");
		list_add_tail(&dev->p->deferred_probe, &deferred_probe_pending_list);
	पूर्ण
	mutex_unlock(&deferred_probe_mutex);
पूर्ण

व्योम driver_deferred_probe_del(काष्ठा device *dev)
अणु
	mutex_lock(&deferred_probe_mutex);
	अगर (!list_empty(&dev->p->deferred_probe)) अणु
		dev_dbg(dev, "Removed from deferred list\n");
		list_del_init(&dev->p->deferred_probe);
		__device_set_deferred_probe_reason(dev, शून्य);
	पूर्ण
	mutex_unlock(&deferred_probe_mutex);
पूर्ण

अटल bool driver_deferred_probe_enable = false;
/**
 * driver_deferred_probe_trigger() - Kick off re-probing deferred devices
 *
 * This functions moves all devices from the pending list to the active
 * list and schedules the deferred probe workqueue to process them.  It
 * should be called anyसमय a driver is successfully bound to a device.
 *
 * Note, there is a race condition in multi-thपढ़ोed probe. In the हाल where
 * more than one device is probing at the same समय, it is possible क्रम one
 * probe to complete successfully जबतक another is about to defer. If the second
 * depends on the first, then it will get put on the pending list after the
 * trigger event has alपढ़ोy occurred and will be stuck there.
 *
 * The atomic 'deferred_trigger_count' is used to determine अगर a successful
 * trigger has occurred in the midst of probing a driver. If the trigger count
 * changes in the midst of a probe, then deferred processing should be triggered
 * again.
 */
अटल व्योम driver_deferred_probe_trigger(व्योम)
अणु
	अगर (!driver_deferred_probe_enable)
		वापस;

	/*
	 * A successful probe means that all the devices in the pending list
	 * should be triggered to be reprobed.  Move all the deferred devices
	 * पूर्णांकo the active list so they can be retried by the workqueue
	 */
	mutex_lock(&deferred_probe_mutex);
	atomic_inc(&deferred_trigger_count);
	list_splice_tail_init(&deferred_probe_pending_list,
			      &deferred_probe_active_list);
	mutex_unlock(&deferred_probe_mutex);

	/*
	 * Kick the re-probe thपढ़ो.  It may alपढ़ोy be scheduled, but it is
	 * safe to kick it again.
	 */
	queue_work(प्रणाली_unbound_wq, &deferred_probe_work);
पूर्ण

/**
 * device_block_probing() - Block/defer device's probes
 *
 *	It will disable probing of devices and defer their probes instead.
 */
व्योम device_block_probing(व्योम)
अणु
	defer_all_probes = true;
	/* sync with probes to aव्योम races. */
	रुको_क्रम_device_probe();
पूर्ण

/**
 * device_unblock_probing() - Unblock/enable device's probes
 *
 *	It will restore normal behavior and trigger re-probing of deferred
 * devices.
 */
व्योम device_unblock_probing(व्योम)
अणु
	defer_all_probes = false;
	driver_deferred_probe_trigger();
पूर्ण

/**
 * device_set_deferred_probe_reason() - Set defer probe reason message क्रम device
 * @dev: the poपूर्णांकer to the काष्ठा device
 * @vaf: the poपूर्णांकer to va_क्रमmat काष्ठाure with message
 */
व्योम device_set_deferred_probe_reason(स्थिर काष्ठा device *dev, काष्ठा va_क्रमmat *vaf)
अणु
	स्थिर अक्षर *drv = dev_driver_string(dev);
	अक्षर *reason;

	mutex_lock(&deferred_probe_mutex);

	reason = kaप्र_लिखो(GFP_KERNEL, "%s: %pV", drv, vaf);
	__device_set_deferred_probe_reason(dev, reason);

	mutex_unlock(&deferred_probe_mutex);
पूर्ण

/*
 * deferred_devs_show() - Show the devices in the deferred probe pending list.
 */
अटल पूर्णांक deferred_devs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा device_निजी *curr;

	mutex_lock(&deferred_probe_mutex);

	list_क्रम_each_entry(curr, &deferred_probe_pending_list, deferred_probe)
		seq_म_लिखो(s, "%s\t%s", dev_name(curr->device),
			   curr->device->p->deferred_probe_reason ?: "\n");

	mutex_unlock(&deferred_probe_mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(deferred_devs);

पूर्णांक driver_deferred_probe_समयout;
EXPORT_SYMBOL_GPL(driver_deferred_probe_समयout);
अटल DECLARE_WAIT_QUEUE_HEAD(probe_समयout_रुकोqueue);

अटल पूर्णांक __init deferred_probe_समयout_setup(अक्षर *str)
अणु
	पूर्णांक समयout;

	अगर (!kstrtoपूर्णांक(str, 10, &समयout))
		driver_deferred_probe_समयout = समयout;
	वापस 1;
पूर्ण
__setup("deferred_probe_timeout=", deferred_probe_समयout_setup);

/**
 * driver_deferred_probe_check_state() - Check deferred probe state
 * @dev: device to check
 *
 * Return:
 * -ENODEV अगर initcalls have completed and modules are disabled.
 * -ETIMEDOUT अगर the deferred probe समयout was set and has expired
 *  and modules are enabled.
 * -EPROBE_DEFER in other हालs.
 *
 * Drivers or subप्रणालीs can opt-in to calling this function instead of directly
 * वापसing -EPROBE_DEFER.
 */
पूर्णांक driver_deferred_probe_check_state(काष्ठा device *dev)
अणु
	अगर (!IS_ENABLED(CONFIG_MODULES) && initcalls_करोne) अणु
		dev_warn(dev, "ignoring dependency for device, assuming no driver\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!driver_deferred_probe_समयout && initcalls_करोne) अणु
		dev_warn(dev, "deferred probe timeout, ignoring dependency\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस -EPROBE_DEFER;
पूर्ण

अटल व्योम deferred_probe_समयout_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा device_निजी *p;

	fw_devlink_drivers_करोne();

	driver_deferred_probe_समयout = 0;
	driver_deferred_probe_trigger();
	flush_work(&deferred_probe_work);

	mutex_lock(&deferred_probe_mutex);
	list_क्रम_each_entry(p, &deferred_probe_pending_list, deferred_probe)
		dev_info(p->device, "deferred probe pending\n");
	mutex_unlock(&deferred_probe_mutex);
	wake_up_all(&probe_समयout_रुकोqueue);
पूर्ण
अटल DECLARE_DELAYED_WORK(deferred_probe_समयout_work, deferred_probe_समयout_work_func);

/**
 * deferred_probe_initcall() - Enable probing of deferred devices
 *
 * We करोn't want to get in the way when the bulk of drivers are getting probed.
 * Instead, this initcall makes sure that deferred probing is delayed until
 * late_initcall समय.
 */
अटल पूर्णांक deferred_probe_initcall(व्योम)
अणु
	debugfs_create_file("devices_deferred", 0444, शून्य, शून्य,
			    &deferred_devs_fops);

	driver_deferred_probe_enable = true;
	driver_deferred_probe_trigger();
	/* Sort as many dependencies as possible beक्रमe निकासing initcalls */
	flush_work(&deferred_probe_work);
	initcalls_करोne = true;

	अगर (!IS_ENABLED(CONFIG_MODULES))
		fw_devlink_drivers_करोne();

	/*
	 * Trigger deferred probe again, this समय we won't defer anything
	 * that is optional
	 */
	driver_deferred_probe_trigger();
	flush_work(&deferred_probe_work);

	अगर (driver_deferred_probe_समयout > 0) अणु
		schedule_delayed_work(&deferred_probe_समयout_work,
			driver_deferred_probe_समयout * HZ);
	पूर्ण
	वापस 0;
पूर्ण
late_initcall(deferred_probe_initcall);

अटल व्योम __निकास deferred_probe_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_lookup("devices_deferred", शून्य));
पूर्ण
__निकासcall(deferred_probe_निकास);

/**
 * device_is_bound() - Check अगर device is bound to a driver
 * @dev: device to check
 *
 * Returns true अगर passed device has alपढ़ोy finished probing successfully
 * against a driver.
 *
 * This function must be called with the device lock held.
 */
bool device_is_bound(काष्ठा device *dev)
अणु
	वापस dev->p && klist_node_attached(&dev->p->knode_driver);
पूर्ण

अटल व्योम driver_bound(काष्ठा device *dev)
अणु
	अगर (device_is_bound(dev)) अणु
		pr_warn("%s: device %s already bound\n",
			__func__, kobject_name(&dev->kobj));
		वापस;
	पूर्ण

	pr_debug("driver: '%s': %s: bound to device '%s'\n", dev->driver->name,
		 __func__, dev_name(dev));

	klist_add_tail(&dev->p->knode_driver, &dev->driver->p->klist_devices);
	device_links_driver_bound(dev);

	device_pm_check_callbacks(dev);

	/*
	 * Make sure the device is no दीर्घer in one of the deferred lists and
	 * kick off retrying all pending devices
	 */
	driver_deferred_probe_del(dev);
	driver_deferred_probe_trigger();

	अगर (dev->bus)
		blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
					     BUS_NOTIFY_BOUND_DRIVER, dev);

	kobject_uevent(&dev->kobj, KOBJ_BIND);
पूर्ण

अटल sमाप_प्रकार coredump_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	device_lock(dev);
	dev->driver->coredump(dev);
	device_unlock(dev);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(coredump);

अटल पूर्णांक driver_sysfs_add(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (dev->bus)
		blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
					     BUS_NOTIFY_BIND_DRIVER, dev);

	ret = sysfs_create_link(&dev->driver->p->kobj, &dev->kobj,
				kobject_name(&dev->kobj));
	अगर (ret)
		जाओ fail;

	ret = sysfs_create_link(&dev->kobj, &dev->driver->p->kobj,
				"driver");
	अगर (ret)
		जाओ rm_dev;

	अगर (!IS_ENABLED(CONFIG_DEV_COREDUMP) || !dev->driver->coredump)
		वापस 0;

	ret = device_create_file(dev, &dev_attr_coredump);
	अगर (!ret)
		वापस 0;

	sysfs_हटाओ_link(&dev->kobj, "driver");

rm_dev:
	sysfs_हटाओ_link(&dev->driver->p->kobj,
			  kobject_name(&dev->kobj));

fail:
	वापस ret;
पूर्ण

अटल व्योम driver_sysfs_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा device_driver *drv = dev->driver;

	अगर (drv) अणु
		अगर (drv->coredump)
			device_हटाओ_file(dev, &dev_attr_coredump);
		sysfs_हटाओ_link(&drv->p->kobj, kobject_name(&dev->kobj));
		sysfs_हटाओ_link(&dev->kobj, "driver");
	पूर्ण
पूर्ण

/**
 * device_bind_driver - bind a driver to one device.
 * @dev: device.
 *
 * Allow manual attachment of a driver to a device.
 * Caller must have alपढ़ोy set @dev->driver.
 *
 * Note that this करोes not modअगरy the bus reference count.
 * Please verअगरy that is accounted क्रम beक्रमe calling this.
 * (It is ok to call with no other efक्रमt from a driver's probe() method.)
 *
 * This function must be called with the device lock held.
 */
पूर्णांक device_bind_driver(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = driver_sysfs_add(dev);
	अगर (!ret) अणु
		device_links_क्रमce_bind(dev);
		driver_bound(dev);
	पूर्ण
	अन्यथा अगर (dev->bus)
		blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
					     BUS_NOTIFY_DRIVER_NOT_BOUND, dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(device_bind_driver);

अटल atomic_t probe_count = ATOMIC_INIT(0);
अटल DECLARE_WAIT_QUEUE_HEAD(probe_रुकोqueue);

अटल व्योम driver_deferred_probe_add_trigger(काष्ठा device *dev,
					      पूर्णांक local_trigger_count)
अणु
	driver_deferred_probe_add(dev);
	/* Did a trigger occur जबतक probing? Need to re-trigger अगर yes */
	अगर (local_trigger_count != atomic_पढ़ो(&deferred_trigger_count))
		driver_deferred_probe_trigger();
पूर्ण

अटल sमाप_प्रकार state_synced_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	bool val;

	device_lock(dev);
	val = dev->state_synced;
	device_unlock(dev);

	वापस sysfs_emit(buf, "%u\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(state_synced);

अटल पूर्णांक really_probe(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	पूर्णांक ret = -EPROBE_DEFER;
	पूर्णांक local_trigger_count = atomic_पढ़ो(&deferred_trigger_count);
	bool test_हटाओ = IS_ENABLED(CONFIG_DEBUG_TEST_DRIVER_REMOVE) &&
			   !drv->suppress_bind_attrs;

	अगर (defer_all_probes) अणु
		/*
		 * Value of defer_all_probes can be set only by
		 * device_block_probing() which, in turn, will call
		 * रुको_क्रम_device_probe() right after that to aव्योम any races.
		 */
		dev_dbg(dev, "Driver %s force probe deferral\n", drv->name);
		driver_deferred_probe_add(dev);
		वापस ret;
	पूर्ण

	ret = device_links_check_suppliers(dev);
	अगर (ret == -EPROBE_DEFER)
		driver_deferred_probe_add_trigger(dev, local_trigger_count);
	अगर (ret)
		वापस ret;

	atomic_inc(&probe_count);
	pr_debug("bus: '%s': %s: probing driver %s with device %s\n",
		 drv->bus->name, __func__, drv->name, dev_name(dev));
	अगर (!list_empty(&dev->devres_head)) अणु
		dev_crit(dev, "Resources present before probing\n");
		ret = -EBUSY;
		जाओ करोne;
	पूर्ण

re_probe:
	dev->driver = drv;

	/* If using pinctrl, bind pins now beक्रमe probing */
	ret = pinctrl_bind_pins(dev);
	अगर (ret)
		जाओ pinctrl_bind_failed;

	अगर (dev->bus->dma_configure) अणु
		ret = dev->bus->dma_configure(dev);
		अगर (ret)
			जाओ probe_failed;
	पूर्ण

	अगर (driver_sysfs_add(dev)) अणु
		pr_err("%s: driver_sysfs_add(%s) failed\n",
		       __func__, dev_name(dev));
		जाओ probe_failed;
	पूर्ण

	अगर (dev->pm_करोमुख्य && dev->pm_करोमुख्य->activate) अणु
		ret = dev->pm_करोमुख्य->activate(dev);
		अगर (ret)
			जाओ probe_failed;
	पूर्ण

	अगर (dev->bus->probe) अणु
		ret = dev->bus->probe(dev);
		अगर (ret)
			जाओ probe_failed;
	पूर्ण अन्यथा अगर (drv->probe) अणु
		ret = drv->probe(dev);
		अगर (ret)
			जाओ probe_failed;
	पूर्ण

	अगर (device_add_groups(dev, drv->dev_groups)) अणु
		dev_err(dev, "device_add_groups() failed\n");
		जाओ dev_groups_failed;
	पूर्ण

	अगर (dev_has_sync_state(dev) &&
	    device_create_file(dev, &dev_attr_state_synced)) अणु
		dev_err(dev, "state_synced sysfs add failed\n");
		जाओ dev_sysfs_state_synced_failed;
	पूर्ण

	अगर (test_हटाओ) अणु
		test_हटाओ = false;

		device_हटाओ_file(dev, &dev_attr_state_synced);
		device_हटाओ_groups(dev, drv->dev_groups);

		अगर (dev->bus->हटाओ)
			dev->bus->हटाओ(dev);
		अन्यथा अगर (drv->हटाओ)
			drv->हटाओ(dev);

		devres_release_all(dev);
		driver_sysfs_हटाओ(dev);
		dev->driver = शून्य;
		dev_set_drvdata(dev, शून्य);
		अगर (dev->pm_करोमुख्य && dev->pm_करोमुख्य->dismiss)
			dev->pm_करोमुख्य->dismiss(dev);
		pm_runसमय_reinit(dev);

		जाओ re_probe;
	पूर्ण

	pinctrl_init_करोne(dev);

	अगर (dev->pm_करोमुख्य && dev->pm_करोमुख्य->sync)
		dev->pm_करोमुख्य->sync(dev);

	driver_bound(dev);
	ret = 1;
	pr_debug("bus: '%s': %s: bound device %s to driver %s\n",
		 drv->bus->name, __func__, dev_name(dev), drv->name);
	जाओ करोne;

dev_sysfs_state_synced_failed:
	device_हटाओ_groups(dev, drv->dev_groups);
dev_groups_failed:
	अगर (dev->bus->हटाओ)
		dev->bus->हटाओ(dev);
	अन्यथा अगर (drv->हटाओ)
		drv->हटाओ(dev);
probe_failed:
	kमुक्त(dev->dma_range_map);
	dev->dma_range_map = शून्य;
	अगर (dev->bus)
		blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
					     BUS_NOTIFY_DRIVER_NOT_BOUND, dev);
pinctrl_bind_failed:
	device_links_no_driver(dev);
	devres_release_all(dev);
	arch_tearकरोwn_dma_ops(dev);
	driver_sysfs_हटाओ(dev);
	dev->driver = शून्य;
	dev_set_drvdata(dev, शून्य);
	अगर (dev->pm_करोमुख्य && dev->pm_करोमुख्य->dismiss)
		dev->pm_करोमुख्य->dismiss(dev);
	pm_runसमय_reinit(dev);
	dev_pm_set_driver_flags(dev, 0);

	चयन (ret) अणु
	हाल -EPROBE_DEFER:
		/* Driver requested deferred probing */
		dev_dbg(dev, "Driver %s requests probe deferral\n", drv->name);
		driver_deferred_probe_add_trigger(dev, local_trigger_count);
		अवरोध;
	हाल -ENODEV:
	हाल -ENXIO:
		pr_debug("%s: probe of %s rejects match %d\n",
			 drv->name, dev_name(dev), ret);
		अवरोध;
	शेष:
		/* driver matched but the probe failed */
		pr_warn("%s: probe of %s failed with error %d\n",
			drv->name, dev_name(dev), ret);
	पूर्ण
	/*
	 * Ignore errors वापसed by ->probe so that the next driver can try
	 * its luck.
	 */
	ret = 0;
करोne:
	atomic_dec(&probe_count);
	wake_up_all(&probe_रुकोqueue);
	वापस ret;
पूर्ण

/*
 * For initcall_debug, show the driver probe समय.
 */
अटल पूर्णांक really_probe_debug(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	kसमय_प्रकार callसमय, retसमय;
	पूर्णांक ret;

	callसमय = kसमय_get();
	ret = really_probe(dev, drv);
	retसमय = kसमय_get();
	pr_debug("probe of %s returned %d after %lld usecs\n",
		 dev_name(dev), ret, kसमय_us_delta(retसमय, callसमय));
	वापस ret;
पूर्ण

/**
 * driver_probe_करोne
 * Determine अगर the probe sequence is finished or not.
 *
 * Should somehow figure out how to use a semaphore, not an atomic variable...
 */
पूर्णांक driver_probe_करोne(व्योम)
अणु
	पूर्णांक local_probe_count = atomic_पढ़ो(&probe_count);

	pr_debug("%s: probe_count = %d\n", __func__, local_probe_count);
	अगर (local_probe_count)
		वापस -EBUSY;
	वापस 0;
पूर्ण

/**
 * रुको_क्रम_device_probe
 * Wait क्रम device probing to be completed.
 */
व्योम रुको_क्रम_device_probe(व्योम)
अणु
	/* रुको क्रम probe समयout */
	रुको_event(probe_समयout_रुकोqueue, !driver_deferred_probe_समयout);

	/* रुको क्रम the deferred probe workqueue to finish */
	flush_work(&deferred_probe_work);

	/* रुको क्रम the known devices to complete their probing */
	रुको_event(probe_रुकोqueue, atomic_पढ़ो(&probe_count) == 0);
	async_synchronize_full();
पूर्ण
EXPORT_SYMBOL_GPL(रुको_क्रम_device_probe);

/**
 * driver_probe_device - attempt to bind device & driver together
 * @drv: driver to bind a device to
 * @dev: device to try to bind to the driver
 *
 * This function वापसs -ENODEV अगर the device is not रेजिस्टरed,
 * 1 अगर the device is bound successfully and 0 otherwise.
 *
 * This function must be called with @dev lock held.  When called क्रम a
 * USB पूर्णांकerface, @dev->parent lock must be held as well.
 *
 * If the device has a parent, runसमय-resume the parent beक्रमe driver probing.
 */
अटल पूर्णांक driver_probe_device(काष्ठा device_driver *drv, काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;

	अगर (!device_is_रेजिस्टरed(dev))
		वापस -ENODEV;

	dev->can_match = true;
	pr_debug("bus: '%s': %s: matched device %s with driver %s\n",
		 drv->bus->name, __func__, dev_name(dev), drv->name);

	pm_runसमय_get_suppliers(dev);
	अगर (dev->parent)
		pm_runसमय_get_sync(dev->parent);

	pm_runसमय_barrier(dev);
	अगर (initcall_debug)
		ret = really_probe_debug(dev, drv);
	अन्यथा
		ret = really_probe(dev, drv);
	pm_request_idle(dev);

	अगर (dev->parent)
		pm_runसमय_put(dev->parent);

	pm_runसमय_put_suppliers(dev);
	वापस ret;
पूर्ण

अटल अंतरभूत bool cmdline_requested_async_probing(स्थिर अक्षर *drv_name)
अणु
	वापस parse_option_str(async_probe_drv_names, drv_name);
पूर्ण

/* The option क्रमmat is "driver_async_probe=drv_name1,drv_name2,..." */
अटल पूर्णांक __init save_async_options(अक्षर *buf)
अणु
	अगर (म_माप(buf) >= ASYNC_DRV_NAMES_MAX_LEN)
		pr_warn("Too long list of driver names for 'driver_async_probe'!\n");

	strlcpy(async_probe_drv_names, buf, ASYNC_DRV_NAMES_MAX_LEN);
	वापस 0;
पूर्ण
__setup("driver_async_probe=", save_async_options);

bool driver_allows_async_probing(काष्ठा device_driver *drv)
अणु
	चयन (drv->probe_type) अणु
	हाल PROBE_PREFER_ASYNCHRONOUS:
		वापस true;

	हाल PROBE_FORCE_SYNCHRONOUS:
		वापस false;

	शेष:
		अगर (cmdline_requested_async_probing(drv->name))
			वापस true;

		अगर (module_requested_async_probing(drv->owner))
			वापस true;

		वापस false;
	पूर्ण
पूर्ण

काष्ठा device_attach_data अणु
	काष्ठा device *dev;

	/*
	 * Indicates whether we are are considering asynchronous probing or
	 * not. Only initial binding after device or driver registration
	 * (including deferral processing) may be करोne asynchronously, the
	 * rest is always synchronous, as we expect it is being करोne by
	 * request from userspace.
	 */
	bool check_async;

	/*
	 * Indicates अगर we are binding synchronous or asynchronous drivers.
	 * When asynchronous probing is enabled we'll execute 2 passes
	 * over drivers: first pass करोing synchronous probing and second
	 * करोing asynchronous probing (अगर synchronous did not succeed -
	 * most likely because there was no driver requiring synchronous
	 * probing - and we found asynchronous driver during first pass).
	 * The 2 passes are करोne because we can't shoot asynchronous
	 * probe क्रम given device and driver from bus_क्रम_each_drv() since
	 * driver poपूर्णांकer is not guaranteed to stay valid once
	 * bus_क्रम_each_drv() iterates to the next driver on the bus.
	 */
	bool want_async;

	/*
	 * We'll set have_async to 'true' अगर, जबतक scanning क्रम matching
	 * driver, we'll encounter one that requests asynchronous probing.
	 */
	bool have_async;
पूर्ण;

अटल पूर्णांक __device_attach_driver(काष्ठा device_driver *drv, व्योम *_data)
अणु
	काष्ठा device_attach_data *data = _data;
	काष्ठा device *dev = data->dev;
	bool async_allowed;
	पूर्णांक ret;

	ret = driver_match_device(drv, dev);
	अगर (ret == 0) अणु
		/* no match */
		वापस 0;
	पूर्ण अन्यथा अगर (ret == -EPROBE_DEFER) अणु
		dev_dbg(dev, "Device match requests probe deferral\n");
		dev->can_match = true;
		driver_deferred_probe_add(dev);
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_dbg(dev, "Bus failed to match device: %d\n", ret);
		वापस ret;
	पूर्ण /* ret > 0 means positive match */

	async_allowed = driver_allows_async_probing(drv);

	अगर (async_allowed)
		data->have_async = true;

	अगर (data->check_async && async_allowed != data->want_async)
		वापस 0;

	वापस driver_probe_device(drv, dev);
पूर्ण

अटल व्योम __device_attach_async_helper(व्योम *_dev, async_cookie_t cookie)
अणु
	काष्ठा device *dev = _dev;
	काष्ठा device_attach_data data = अणु
		.dev		= dev,
		.check_async	= true,
		.want_async	= true,
	पूर्ण;

	device_lock(dev);

	/*
	 * Check अगर device has alपढ़ोy been हटाओd or claimed. This may
	 * happen with driver loading, device discovery/registration,
	 * and deferred probe processing happens all at once with
	 * multiple thपढ़ोs.
	 */
	अगर (dev->p->dead || dev->driver)
		जाओ out_unlock;

	अगर (dev->parent)
		pm_runसमय_get_sync(dev->parent);

	bus_क्रम_each_drv(dev->bus, शून्य, &data, __device_attach_driver);
	dev_dbg(dev, "async probe completed\n");

	pm_request_idle(dev);

	अगर (dev->parent)
		pm_runसमय_put(dev->parent);
out_unlock:
	device_unlock(dev);

	put_device(dev);
पूर्ण

अटल पूर्णांक __device_attach(काष्ठा device *dev, bool allow_async)
अणु
	पूर्णांक ret = 0;

	device_lock(dev);
	अगर (dev->p->dead) अणु
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (dev->driver) अणु
		अगर (device_is_bound(dev)) अणु
			ret = 1;
			जाओ out_unlock;
		पूर्ण
		ret = device_bind_driver(dev);
		अगर (ret == 0)
			ret = 1;
		अन्यथा अणु
			dev->driver = शून्य;
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा device_attach_data data = अणु
			.dev = dev,
			.check_async = allow_async,
			.want_async = false,
		पूर्ण;

		अगर (dev->parent)
			pm_runसमय_get_sync(dev->parent);

		ret = bus_क्रम_each_drv(dev->bus, शून्य, &data,
					__device_attach_driver);
		अगर (!ret && allow_async && data.have_async) अणु
			/*
			 * If we could not find appropriate driver
			 * synchronously and we are allowed to करो
			 * async probes and there are drivers that
			 * want to probe asynchronously, we'll
			 * try them.
			 */
			dev_dbg(dev, "scheduling asynchronous probe\n");
			get_device(dev);
			async_schedule_dev(__device_attach_async_helper, dev);
		पूर्ण अन्यथा अणु
			pm_request_idle(dev);
		पूर्ण

		अगर (dev->parent)
			pm_runसमय_put(dev->parent);
	पूर्ण
out_unlock:
	device_unlock(dev);
	वापस ret;
पूर्ण

/**
 * device_attach - try to attach device to a driver.
 * @dev: device.
 *
 * Walk the list of drivers that the bus has and call
 * driver_probe_device() क्रम each pair. If a compatible
 * pair is found, अवरोध out and वापस.
 *
 * Returns 1 अगर the device was bound to a driver;
 * 0 अगर no matching driver was found;
 * -ENODEV अगर the device is not रेजिस्टरed.
 *
 * When called क्रम a USB पूर्णांकerface, @dev->parent lock must be held.
 */
पूर्णांक device_attach(काष्ठा device *dev)
अणु
	वापस __device_attach(dev, false);
पूर्ण
EXPORT_SYMBOL_GPL(device_attach);

व्योम device_initial_probe(काष्ठा device *dev)
अणु
	__device_attach(dev, true);
पूर्ण

/*
 * __device_driver_lock - acquire locks needed to manipulate dev->drv
 * @dev: Device we will update driver info क्रम
 * @parent: Parent device. Needed अगर the bus requires parent lock
 *
 * This function will take the required locks क्रम manipulating dev->drv.
 * Normally this will just be the @dev lock, but when called क्रम a USB
 * पूर्णांकerface, @parent lock will be held as well.
 */
अटल व्योम __device_driver_lock(काष्ठा device *dev, काष्ठा device *parent)
अणु
	अगर (parent && dev->bus->need_parent_lock)
		device_lock(parent);
	device_lock(dev);
पूर्ण

/*
 * __device_driver_unlock - release locks needed to manipulate dev->drv
 * @dev: Device we will update driver info क्रम
 * @parent: Parent device. Needed अगर the bus requires parent lock
 *
 * This function will release the required locks क्रम manipulating dev->drv.
 * Normally this will just be the the @dev lock, but when called क्रम a
 * USB पूर्णांकerface, @parent lock will be released as well.
 */
अटल व्योम __device_driver_unlock(काष्ठा device *dev, काष्ठा device *parent)
अणु
	device_unlock(dev);
	अगर (parent && dev->bus->need_parent_lock)
		device_unlock(parent);
पूर्ण

/**
 * device_driver_attach - attach a specअगरic driver to a specअगरic device
 * @drv: Driver to attach
 * @dev: Device to attach it to
 *
 * Manually attach driver to a device. Will acquire both @dev lock and
 * @dev->parent lock अगर needed.
 */
पूर्णांक device_driver_attach(काष्ठा device_driver *drv, काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;

	__device_driver_lock(dev, dev->parent);

	/*
	 * If device has been हटाओd or someone has alपढ़ोy successfully
	 * bound a driver beक्रमe us just skip the driver probe call.
	 */
	अगर (!dev->p->dead && !dev->driver)
		ret = driver_probe_device(drv, dev);

	__device_driver_unlock(dev, dev->parent);

	वापस ret;
पूर्ण

अटल व्योम __driver_attach_async_helper(व्योम *_dev, async_cookie_t cookie)
अणु
	काष्ठा device *dev = _dev;
	काष्ठा device_driver *drv;
	पूर्णांक ret = 0;

	__device_driver_lock(dev, dev->parent);

	drv = dev->p->async_driver;

	/*
	 * If device has been हटाओd or someone has alपढ़ोy successfully
	 * bound a driver beक्रमe us just skip the driver probe call.
	 */
	अगर (!dev->p->dead && !dev->driver)
		ret = driver_probe_device(drv, dev);

	__device_driver_unlock(dev, dev->parent);

	dev_dbg(dev, "driver %s async attach completed: %d\n", drv->name, ret);

	put_device(dev);
पूर्ण

अटल पूर्णांक __driver_attach(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device_driver *drv = data;
	पूर्णांक ret;

	/*
	 * Lock device and try to bind to it. We drop the error
	 * here and always वापस 0, because we need to keep trying
	 * to bind to devices and some drivers will वापस an error
	 * simply अगर it didn't support the device.
	 *
	 * driver_probe_device() will spit a warning अगर there
	 * is an error.
	 */

	ret = driver_match_device(drv, dev);
	अगर (ret == 0) अणु
		/* no match */
		वापस 0;
	पूर्ण अन्यथा अगर (ret == -EPROBE_DEFER) अणु
		dev_dbg(dev, "Device match requests probe deferral\n");
		dev->can_match = true;
		driver_deferred_probe_add(dev);
	पूर्ण अन्यथा अगर (ret < 0) अणु
		dev_dbg(dev, "Bus failed to match device: %d\n", ret);
		वापस ret;
	पूर्ण /* ret > 0 means positive match */

	अगर (driver_allows_async_probing(drv)) अणु
		/*
		 * Instead of probing the device synchronously we will
		 * probe it asynchronously to allow क्रम more parallelism.
		 *
		 * We only take the device lock here in order to guarantee
		 * that the dev->driver and async_driver fields are रक्षित
		 */
		dev_dbg(dev, "probing driver %s asynchronously\n", drv->name);
		device_lock(dev);
		अगर (!dev->driver) अणु
			get_device(dev);
			dev->p->async_driver = drv;
			async_schedule_dev(__driver_attach_async_helper, dev);
		पूर्ण
		device_unlock(dev);
		वापस 0;
	पूर्ण

	device_driver_attach(drv, dev);

	वापस 0;
पूर्ण

/**
 * driver_attach - try to bind driver to devices.
 * @drv: driver.
 *
 * Walk the list of devices that the bus has on it and try to
 * match the driver with each one.  If driver_probe_device()
 * वापसs 0 and the @dev->driver is set, we've found a
 * compatible pair.
 */
पूर्णांक driver_attach(काष्ठा device_driver *drv)
अणु
	वापस bus_क्रम_each_dev(drv->bus, शून्य, drv, __driver_attach);
पूर्ण
EXPORT_SYMBOL_GPL(driver_attach);

/*
 * __device_release_driver() must be called with @dev lock held.
 * When called क्रम a USB पूर्णांकerface, @dev->parent lock must be held as well.
 */
अटल व्योम __device_release_driver(काष्ठा device *dev, काष्ठा device *parent)
अणु
	काष्ठा device_driver *drv;

	drv = dev->driver;
	अगर (drv) अणु
		pm_runसमय_get_sync(dev);

		जबतक (device_links_busy(dev)) अणु
			__device_driver_unlock(dev, parent);

			device_links_unbind_consumers(dev);

			__device_driver_lock(dev, parent);
			/*
			 * A concurrent invocation of the same function might
			 * have released the driver successfully जबतक this one
			 * was रुकोing, so check क्रम that.
			 */
			अगर (dev->driver != drv) अणु
				pm_runसमय_put(dev);
				वापस;
			पूर्ण
		पूर्ण

		driver_sysfs_हटाओ(dev);

		अगर (dev->bus)
			blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
						     BUS_NOTIFY_UNBIND_DRIVER,
						     dev);

		pm_runसमय_put_sync(dev);

		device_हटाओ_file(dev, &dev_attr_state_synced);
		device_हटाओ_groups(dev, drv->dev_groups);

		अगर (dev->bus && dev->bus->हटाओ)
			dev->bus->हटाओ(dev);
		अन्यथा अगर (drv->हटाओ)
			drv->हटाओ(dev);

		device_links_driver_cleanup(dev);

		devres_release_all(dev);
		arch_tearकरोwn_dma_ops(dev);
		dev->driver = शून्य;
		dev_set_drvdata(dev, शून्य);
		अगर (dev->pm_करोमुख्य && dev->pm_करोमुख्य->dismiss)
			dev->pm_करोमुख्य->dismiss(dev);
		pm_runसमय_reinit(dev);
		dev_pm_set_driver_flags(dev, 0);

		klist_हटाओ(&dev->p->knode_driver);
		device_pm_check_callbacks(dev);
		अगर (dev->bus)
			blocking_notअगरier_call_chain(&dev->bus->p->bus_notअगरier,
						     BUS_NOTIFY_UNBOUND_DRIVER,
						     dev);

		kobject_uevent(&dev->kobj, KOBJ_UNBIND);
	पूर्ण
पूर्ण

व्योम device_release_driver_पूर्णांकernal(काष्ठा device *dev,
				    काष्ठा device_driver *drv,
				    काष्ठा device *parent)
अणु
	__device_driver_lock(dev, parent);

	अगर (!drv || drv == dev->driver)
		__device_release_driver(dev, parent);

	__device_driver_unlock(dev, parent);
पूर्ण

/**
 * device_release_driver - manually detach device from driver.
 * @dev: device.
 *
 * Manually detach device from driver.
 * When called क्रम a USB पूर्णांकerface, @dev->parent lock must be held.
 *
 * If this function is to be called with @dev->parent lock held, ensure that
 * the device's consumers are unbound in advance or that their locks can be
 * acquired under the @dev->parent lock.
 */
व्योम device_release_driver(काष्ठा device *dev)
अणु
	/*
	 * If anyone calls device_release_driver() recursively from
	 * within their ->हटाओ callback क्रम the same device, they
	 * will deadlock right here.
	 */
	device_release_driver_पूर्णांकernal(dev, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(device_release_driver);

/**
 * device_driver_detach - detach driver from a specअगरic device
 * @dev: device to detach driver from
 *
 * Detach driver from device. Will acquire both @dev lock and @dev->parent
 * lock अगर needed.
 */
व्योम device_driver_detach(काष्ठा device *dev)
अणु
	device_release_driver_पूर्णांकernal(dev, शून्य, dev->parent);
पूर्ण

/**
 * driver_detach - detach driver from all devices it controls.
 * @drv: driver.
 */
व्योम driver_detach(काष्ठा device_driver *drv)
अणु
	काष्ठा device_निजी *dev_prv;
	काष्ठा device *dev;

	अगर (driver_allows_async_probing(drv))
		async_synchronize_full();

	क्रम (;;) अणु
		spin_lock(&drv->p->klist_devices.k_lock);
		अगर (list_empty(&drv->p->klist_devices.k_list)) अणु
			spin_unlock(&drv->p->klist_devices.k_lock);
			अवरोध;
		पूर्ण
		dev_prv = list_last_entry(&drv->p->klist_devices.k_list,
				     काष्ठा device_निजी,
				     knode_driver.n_node);
		dev = dev_prv->device;
		get_device(dev);
		spin_unlock(&drv->p->klist_devices.k_lock);
		device_release_driver_पूर्णांकernal(dev, drv, dev->parent);
		put_device(dev);
	पूर्ण
पूर्ण
