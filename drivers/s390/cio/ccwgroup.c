<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  bus driver क्रम ccwgroup
 *
 *  Copyright IBM Corp. 2002, 2012
 *
 *  Author(s): Arnd Bergmann (arndb@de.ibm.com)
 *	       Cornelia Huck (cornelia.huck@de.ibm.com)
 */
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dcache.h>

#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/ccwgroup.h>

#समावेश "device.h"

#घोषणा CCW_BUS_ID_SIZE		10

/* In Linux 2.4, we had a channel device layer called "chandev"
 * that did all sorts of obscure stuff क्रम networking devices.
 * This is another driver that serves as a replacement क्रम just
 * one of its functions, namely the translation of single subchannels
 * to devices that use multiple subchannels.
 */

अटल काष्ठा bus_type ccwgroup_bus_type;

अटल व्योम __ccwgroup_हटाओ_symlinks(काष्ठा ccwgroup_device *gdev)
अणु
	पूर्णांक i;
	अक्षर str[16];

	क्रम (i = 0; i < gdev->count; i++) अणु
		प्र_लिखो(str, "cdev%d", i);
		sysfs_हटाओ_link(&gdev->dev.kobj, str);
		sysfs_हटाओ_link(&gdev->cdev[i]->dev.kobj, "group_device");
	पूर्ण
पूर्ण

/*
 * Remove references from ccw devices to ccw group device and from
 * ccw group device to ccw devices.
 */
अटल व्योम __ccwgroup_हटाओ_cdev_refs(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा ccw_device *cdev;
	पूर्णांक i;

	क्रम (i = 0; i < gdev->count; i++) अणु
		cdev = gdev->cdev[i];
		अगर (!cdev)
			जारी;
		spin_lock_irq(cdev->ccwlock);
		dev_set_drvdata(&cdev->dev, शून्य);
		spin_unlock_irq(cdev->ccwlock);
		gdev->cdev[i] = शून्य;
		put_device(&cdev->dev);
	पूर्ण
पूर्ण

/**
 * ccwgroup_set_online() - enable a ccwgroup device
 * @gdev: target ccwgroup device
 *
 * This function attempts to put the ccwgroup device पूर्णांकo the online state.
 * Returns:
 *  %0 on success and a negative error value on failure.
 */
पूर्णांक ccwgroup_set_online(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा ccwgroup_driver *gdrv = to_ccwgroupdrv(gdev->dev.driver);
	पूर्णांक ret = -EINVAL;

	अगर (atomic_cmpxchg(&gdev->onoff, 0, 1) != 0)
		वापस -EAGAIN;
	अगर (gdev->state == CCWGROUP_ONLINE)
		जाओ out;
	अगर (gdrv->set_online)
		ret = gdrv->set_online(gdev);
	अगर (ret)
		जाओ out;

	gdev->state = CCWGROUP_ONLINE;
out:
	atomic_set(&gdev->onoff, 0);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ccwgroup_set_online);

/**
 * ccwgroup_set_offline() - disable a ccwgroup device
 * @gdev: target ccwgroup device
 *
 * This function attempts to put the ccwgroup device पूर्णांकo the offline state.
 * Returns:
 *  %0 on success and a negative error value on failure.
 */
पूर्णांक ccwgroup_set_offline(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा ccwgroup_driver *gdrv = to_ccwgroupdrv(gdev->dev.driver);
	पूर्णांक ret = -EINVAL;

	अगर (atomic_cmpxchg(&gdev->onoff, 0, 1) != 0)
		वापस -EAGAIN;
	अगर (gdev->state == CCWGROUP_OFFLINE)
		जाओ out;
	अगर (gdrv->set_offline)
		ret = gdrv->set_offline(gdev);
	अगर (ret)
		जाओ out;

	gdev->state = CCWGROUP_OFFLINE;
out:
	atomic_set(&gdev->onoff, 0);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ccwgroup_set_offline);

अटल sमाप_प्रकार ccwgroup_online_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	device_lock(dev);
	अगर (!dev->driver) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = kम_से_अदीर्घ(buf, 0, &value);
	अगर (ret)
		जाओ out;

	अगर (value == 1)
		ret = ccwgroup_set_online(gdev);
	अन्यथा अगर (value == 0)
		ret = ccwgroup_set_offline(gdev);
	अन्यथा
		ret = -EINVAL;
out:
	device_unlock(dev);
	वापस (ret == 0) ? count : ret;
पूर्ण

अटल sमाप_प्रकार ccwgroup_online_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(dev);
	पूर्णांक online;

	online = (gdev->state == CCWGROUP_ONLINE) ? 1 : 0;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", online);
पूर्ण

/*
 * Provide an 'ungroup' attribute so the user can हटाओ group devices no
 * दीर्घer needed or accidentially created. Saves memory :)
 */
अटल व्योम ccwgroup_ungroup(काष्ठा ccwgroup_device *gdev)
अणु
	mutex_lock(&gdev->reg_mutex);
	अगर (device_is_रेजिस्टरed(&gdev->dev)) अणु
		__ccwgroup_हटाओ_symlinks(gdev);
		device_unरेजिस्टर(&gdev->dev);
		__ccwgroup_हटाओ_cdev_refs(gdev);
	पूर्ण
	mutex_unlock(&gdev->reg_mutex);
पूर्ण

अटल sमाप_प्रकार ccwgroup_ungroup_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(dev);
	पूर्णांक rc = 0;

	/* Prevent concurrent online/offline processing and ungrouping. */
	अगर (atomic_cmpxchg(&gdev->onoff, 0, 1) != 0)
		वापस -EAGAIN;
	अगर (gdev->state != CCWGROUP_OFFLINE) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (device_हटाओ_file_self(dev, attr))
		ccwgroup_ungroup(gdev);
	अन्यथा
		rc = -ENODEV;
out:
	अगर (rc) अणु
		/* Release onoff "lock" when ungrouping failed. */
		atomic_set(&gdev->onoff, 0);
		वापस rc;
	पूर्ण
	वापस count;
पूर्ण
अटल DEVICE_ATTR(ungroup, 0200, शून्य, ccwgroup_ungroup_store);
अटल DEVICE_ATTR(online, 0644, ccwgroup_online_show, ccwgroup_online_store);

अटल काष्ठा attribute *ccwgroup_dev_attrs[] = अणु
	&dev_attr_online.attr,
	&dev_attr_ungroup.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ccwgroup_dev);

अटल व्योम ccwgroup_ungroup_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ccwgroup_device *gdev =
		container_of(work, काष्ठा ccwgroup_device, ungroup_work);

	ccwgroup_ungroup(gdev);
	put_device(&gdev->dev);
पूर्ण

अटल व्योम ccwgroup_release(काष्ठा device *dev)
अणु
	kमुक्त(to_ccwgroupdev(dev));
पूर्ण

अटल पूर्णांक __ccwgroup_create_symlinks(काष्ठा ccwgroup_device *gdev)
अणु
	अक्षर str[16];
	पूर्णांक i, rc;

	क्रम (i = 0; i < gdev->count; i++) अणु
		rc = sysfs_create_link(&gdev->cdev[i]->dev.kobj,
				       &gdev->dev.kobj, "group_device");
		अगर (rc) अणु
			क्रम (--i; i >= 0; i--)
				sysfs_हटाओ_link(&gdev->cdev[i]->dev.kobj,
						  "group_device");
			वापस rc;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < gdev->count; i++) अणु
		प्र_लिखो(str, "cdev%d", i);
		rc = sysfs_create_link(&gdev->dev.kobj,
				       &gdev->cdev[i]->dev.kobj, str);
		अगर (rc) अणु
			क्रम (--i; i >= 0; i--) अणु
				प्र_लिखो(str, "cdev%d", i);
				sysfs_हटाओ_link(&gdev->dev.kobj, str);
			पूर्ण
			क्रम (i = 0; i < gdev->count; i++)
				sysfs_हटाओ_link(&gdev->cdev[i]->dev.kobj,
						  "group_device");
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __get_next_id(स्थिर अक्षर **buf, काष्ठा ccw_dev_id *id)
अणु
	अचिन्हित पूर्णांक cssid, ssid, devno;
	पूर्णांक ret = 0, len;
	अक्षर *start, *end;

	start = (अक्षर *)*buf;
	end = म_अक्षर(start, ',');
	अगर (!end) अणु
		/* Last entry. Strip trailing newline, अगर applicable. */
		end = म_अक्षर(start, '\n');
		अगर (end)
			*end = '\0';
		len = म_माप(start) + 1;
	पूर्ण अन्यथा अणु
		len = end - start + 1;
		end++;
	पूर्ण
	अगर (len <= CCW_BUS_ID_SIZE) अणु
		अगर (माला_पूछो(start, "%2x.%1x.%04x", &cssid, &ssid, &devno) != 3)
			ret = -EINVAL;
	पूर्ण अन्यथा
		ret = -EINVAL;

	अगर (!ret) अणु
		id->ssid = ssid;
		id->devno = devno;
	पूर्ण
	*buf = end;
	वापस ret;
पूर्ण

/**
 * ccwgroup_create_dev() - create and रेजिस्टर a ccw group device
 * @parent: parent device क्रम the new device
 * @gdrv: driver क्रम the new group device
 * @num_devices: number of slave devices
 * @buf: buffer containing comma separated bus ids of slave devices
 *
 * Create and रेजिस्टर a new ccw group device as a child of @parent. Slave
 * devices are obtained from the list of bus ids given in @buf.
 * Returns:
 *  %0 on success and an error code on failure.
 * Context:
 *  non-atomic
 */
पूर्णांक ccwgroup_create_dev(काष्ठा device *parent, काष्ठा ccwgroup_driver *gdrv,
			पूर्णांक num_devices, स्थिर अक्षर *buf)
अणु
	काष्ठा ccwgroup_device *gdev;
	काष्ठा ccw_dev_id dev_id;
	पूर्णांक rc, i;

	अगर (num_devices < 1)
		वापस -EINVAL;

	gdev = kzalloc(काष्ठा_size(gdev, cdev, num_devices), GFP_KERNEL);
	अगर (!gdev)
		वापस -ENOMEM;

	atomic_set(&gdev->onoff, 0);
	mutex_init(&gdev->reg_mutex);
	mutex_lock(&gdev->reg_mutex);
	INIT_WORK(&gdev->ungroup_work, ccwgroup_ungroup_workfn);
	gdev->count = num_devices;
	gdev->dev.bus = &ccwgroup_bus_type;
	gdev->dev.parent = parent;
	gdev->dev.release = ccwgroup_release;
	device_initialize(&gdev->dev);

	क्रम (i = 0; i < num_devices && buf; i++) अणु
		rc = __get_next_id(&buf, &dev_id);
		अगर (rc != 0)
			जाओ error;
		gdev->cdev[i] = get_ccwdev_by_dev_id(&dev_id);
		/*
		 * All devices have to be of the same type in
		 * order to be grouped.
		 */
		अगर (!gdev->cdev[i] || !gdev->cdev[i]->drv ||
		    gdev->cdev[i]->drv != gdev->cdev[0]->drv ||
		    gdev->cdev[i]->id.driver_info !=
		    gdev->cdev[0]->id.driver_info) अणु
			rc = -EINVAL;
			जाओ error;
		पूर्ण
		/* Don't allow a device to beदीर्घ to more than one group. */
		spin_lock_irq(gdev->cdev[i]->ccwlock);
		अगर (dev_get_drvdata(&gdev->cdev[i]->dev)) अणु
			spin_unlock_irq(gdev->cdev[i]->ccwlock);
			rc = -EINVAL;
			जाओ error;
		पूर्ण
		dev_set_drvdata(&gdev->cdev[i]->dev, gdev);
		spin_unlock_irq(gdev->cdev[i]->ccwlock);
	पूर्ण
	/* Check क्रम sufficient number of bus ids. */
	अगर (i < num_devices) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण
	/* Check क्रम trailing stuff. */
	अगर (i == num_devices && buf && म_माप(buf) > 0) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण
	/* Check अगर the devices are bound to the required ccw driver. */
	अगर (gdrv && gdrv->ccw_driver &&
	    gdev->cdev[0]->drv != gdrv->ccw_driver) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	dev_set_name(&gdev->dev, "%s", dev_name(&gdev->cdev[0]->dev));

	अगर (gdrv) अणु
		gdev->dev.driver = &gdrv->driver;
		rc = gdrv->setup ? gdrv->setup(gdev) : 0;
		अगर (rc)
			जाओ error;
	पूर्ण
	rc = device_add(&gdev->dev);
	अगर (rc)
		जाओ error;
	rc = __ccwgroup_create_symlinks(gdev);
	अगर (rc) अणु
		device_del(&gdev->dev);
		जाओ error;
	पूर्ण
	mutex_unlock(&gdev->reg_mutex);
	वापस 0;
error:
	क्रम (i = 0; i < num_devices; i++)
		अगर (gdev->cdev[i]) अणु
			spin_lock_irq(gdev->cdev[i]->ccwlock);
			अगर (dev_get_drvdata(&gdev->cdev[i]->dev) == gdev)
				dev_set_drvdata(&gdev->cdev[i]->dev, शून्य);
			spin_unlock_irq(gdev->cdev[i]->ccwlock);
			put_device(&gdev->cdev[i]->dev);
			gdev->cdev[i] = शून्य;
		पूर्ण
	mutex_unlock(&gdev->reg_mutex);
	put_device(&gdev->dev);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ccwgroup_create_dev);

अटल पूर्णांक ccwgroup_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			     व्योम *data)
अणु
	काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(data);

	अगर (action == BUS_NOTIFY_UNBIND_DRIVER) अणु
		get_device(&gdev->dev);
		schedule_work(&gdev->ungroup_work);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block ccwgroup_nb = अणु
	.notअगरier_call = ccwgroup_notअगरier
पूर्ण;

अटल पूर्णांक __init init_ccwgroup(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&ccwgroup_bus_type);
	अगर (ret)
		वापस ret;

	ret = bus_रेजिस्टर_notअगरier(&ccwgroup_bus_type, &ccwgroup_nb);
	अगर (ret)
		bus_unरेजिस्टर(&ccwgroup_bus_type);

	वापस ret;
पूर्ण

अटल व्योम __निकास cleanup_ccwgroup(व्योम)
अणु
	bus_unरेजिस्टर_notअगरier(&ccwgroup_bus_type, &ccwgroup_nb);
	bus_unरेजिस्टर(&ccwgroup_bus_type);
पूर्ण

module_init(init_ccwgroup);
module_निकास(cleanup_ccwgroup);

/************************** driver stuff ******************************/

अटल पूर्णांक ccwgroup_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(dev);
	काष्ठा ccwgroup_driver *gdrv = to_ccwgroupdrv(dev->driver);

	अगर (!dev->driver)
		वापस 0;
	अगर (gdrv->हटाओ)
		gdrv->हटाओ(gdev);

	वापस 0;
पूर्ण

अटल व्योम ccwgroup_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(dev);
	काष्ठा ccwgroup_driver *gdrv = to_ccwgroupdrv(dev->driver);

	अगर (!dev->driver)
		वापस;
	अगर (gdrv->shutकरोwn)
		gdrv->shutकरोwn(gdev);
पूर्ण

अटल काष्ठा bus_type ccwgroup_bus_type = अणु
	.name   = "ccwgroup",
	.dev_groups = ccwgroup_dev_groups,
	.हटाओ = ccwgroup_हटाओ,
	.shutकरोwn = ccwgroup_shutकरोwn,
पूर्ण;

bool dev_is_ccwgroup(काष्ठा device *dev)
अणु
	वापस dev->bus == &ccwgroup_bus_type;
पूर्ण
EXPORT_SYMBOL(dev_is_ccwgroup);

/**
 * ccwgroup_driver_रेजिस्टर() - रेजिस्टर a ccw group driver
 * @cdriver: driver to be रेजिस्टरed
 *
 * This function is मुख्यly a wrapper around driver_रेजिस्टर().
 */
पूर्णांक ccwgroup_driver_रेजिस्टर(काष्ठा ccwgroup_driver *cdriver)
अणु
	/* रेजिस्टर our new driver with the core */
	cdriver->driver.bus = &ccwgroup_bus_type;

	वापस driver_रेजिस्टर(&cdriver->driver);
पूर्ण
EXPORT_SYMBOL(ccwgroup_driver_रेजिस्टर);

/**
 * ccwgroup_driver_unरेजिस्टर() - deरेजिस्टर a ccw group driver
 * @cdriver: driver to be deरेजिस्टरed
 *
 * This function is मुख्यly a wrapper around driver_unरेजिस्टर().
 */
व्योम ccwgroup_driver_unरेजिस्टर(काष्ठा ccwgroup_driver *cdriver)
अणु
	काष्ठा device *dev;

	/* We करोn't want ccwgroup devices to live दीर्घer than their driver. */
	जबतक ((dev = driver_find_next_device(&cdriver->driver, शून्य))) अणु
		काष्ठा ccwgroup_device *gdev = to_ccwgroupdev(dev);

		ccwgroup_ungroup(gdev);
		put_device(dev);
	पूर्ण
	driver_unरेजिस्टर(&cdriver->driver);
पूर्ण
EXPORT_SYMBOL(ccwgroup_driver_unरेजिस्टर);

/**
 * get_ccwgroupdev_by_busid() - obtain device from a bus id
 * @gdrv: driver the device is owned by
 * @bus_id: bus id of the device to be searched
 *
 * This function searches all devices owned by @gdrv क्रम a device with a bus
 * id matching @bus_id.
 * Returns:
 *  If a match is found, its reference count of the found device is increased
 *  and it is वापसed; अन्यथा %शून्य is वापसed.
 */
काष्ठा ccwgroup_device *get_ccwgroupdev_by_busid(काष्ठा ccwgroup_driver *gdrv,
						 अक्षर *bus_id)
अणु
	काष्ठा device *dev;

	dev = driver_find_device_by_name(&gdrv->driver, bus_id);

	वापस dev ? to_ccwgroupdev(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(get_ccwgroupdev_by_busid);

/**
 * ccwgroup_probe_ccwdev() - probe function क्रम slave devices
 * @cdev: ccw device to be probed
 *
 * This is a dummy probe function क्रम ccw devices that are slave devices in
 * a ccw group device.
 * Returns:
 *  always %0
 */
पूर्णांक ccwgroup_probe_ccwdev(काष्ठा ccw_device *cdev)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ccwgroup_probe_ccwdev);

/**
 * ccwgroup_हटाओ_ccwdev() - हटाओ function क्रम slave devices
 * @cdev: ccw device to be हटाओd
 *
 * This is a हटाओ function क्रम ccw devices that are slave devices in a ccw
 * group device. It sets the ccw device offline and also deरेजिस्टरs the
 * embedding ccw group device.
 */
व्योम ccwgroup_हटाओ_ccwdev(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccwgroup_device *gdev;

	/* Ignore offlining errors, device is gone anyway. */
	ccw_device_set_offline(cdev);
	/* If one of its devices is gone, the whole group is करोne क्रम. */
	spin_lock_irq(cdev->ccwlock);
	gdev = dev_get_drvdata(&cdev->dev);
	अगर (!gdev) अणु
		spin_unlock_irq(cdev->ccwlock);
		वापस;
	पूर्ण
	/* Get ccwgroup device reference क्रम local processing. */
	get_device(&gdev->dev);
	spin_unlock_irq(cdev->ccwlock);
	/* Unरेजिस्टर group device. */
	ccwgroup_ungroup(gdev);
	/* Release ccwgroup device reference क्रम local processing. */
	put_device(&gdev->dev);
पूर्ण
EXPORT_SYMBOL(ccwgroup_हटाओ_ccwdev);
MODULE_LICENSE("GPL");
