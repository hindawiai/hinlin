<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO core
 *
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Derived from original vfio:
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 * Author: Tom Lyon, pugs@cisco.com
 */

#समावेश <linux/cdev.h>
#समावेश <linux/compat.h>
#समावेश <linux/device.h>
#समावेश <linux/file.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/iommu.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>

#घोषणा DRIVER_VERSION	"0.3"
#घोषणा DRIVER_AUTHOR	"Alex Williamson <alex.williamson@redhat.com>"
#घोषणा DRIVER_DESC	"VFIO - User Level meta-driver"

अटल काष्ठा vfio अणु
	काष्ठा class			*class;
	काष्ठा list_head		iommu_drivers_list;
	काष्ठा mutex			iommu_drivers_lock;
	काष्ठा list_head		group_list;
	काष्ठा idr			group_idr;
	काष्ठा mutex			group_lock;
	काष्ठा cdev			group_cdev;
	dev_t				group_devt;
पूर्ण vfio;

काष्ठा vfio_iommu_driver अणु
	स्थिर काष्ठा vfio_iommu_driver_ops	*ops;
	काष्ठा list_head			vfio_next;
पूर्ण;

काष्ठा vfio_container अणु
	काष्ठा kref			kref;
	काष्ठा list_head		group_list;
	काष्ठा rw_semaphore		group_lock;
	काष्ठा vfio_iommu_driver	*iommu_driver;
	व्योम				*iommu_data;
	bool				noiommu;
पूर्ण;

काष्ठा vfio_unbound_dev अणु
	काष्ठा device			*dev;
	काष्ठा list_head		unbound_next;
पूर्ण;

काष्ठा vfio_group अणु
	काष्ठा kref			kref;
	पूर्णांक				minor;
	atomic_t			container_users;
	काष्ठा iommu_group		*iommu_group;
	काष्ठा vfio_container		*container;
	काष्ठा list_head		device_list;
	काष्ठा mutex			device_lock;
	काष्ठा device			*dev;
	काष्ठा notअगरier_block		nb;
	काष्ठा list_head		vfio_next;
	काष्ठा list_head		container_next;
	काष्ठा list_head		unbound_list;
	काष्ठा mutex			unbound_lock;
	atomic_t			खोलोed;
	रुको_queue_head_t		container_q;
	bool				noiommu;
	अचिन्हित पूर्णांक			dev_counter;
	काष्ठा kvm			*kvm;
	काष्ठा blocking_notअगरier_head	notअगरier;
पूर्ण;

#अगर_घोषित CONFIG_VFIO_NOIOMMU
अटल bool noiommu __पढ़ो_mostly;
module_param_named(enable_unsafe_noiommu_mode,
		   noiommu, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(enable_unsafe_noiommu_mode, "Enable UNSAFE, no-IOMMU mode.  This mode provides no device isolation, no DMA translation, no host kernel protection, cannot be used for device assignment to virtual machines, requires RAWIO permissions, and will taint the kernel.  If you do not know what this is for, step away. (default: false)");
#पूर्ण_अगर

/*
 * vfio_iommu_group_अणुget,putपूर्ण are only पूर्णांकended क्रम VFIO bus driver probe
 * and हटाओ functions, any use हालs other than acquiring the first
 * reference क्रम the purpose of calling vfio_रेजिस्टर_group_dev() or removing
 * that symmetric reference after vfio_unरेजिस्टर_group_dev() should use the raw
 * iommu_group_अणुget,putपूर्ण functions.  In particular, vfio_iommu_group_put()
 * हटाओs the device from the dummy group and cannot be nested.
 */
काष्ठा iommu_group *vfio_iommu_group_get(काष्ठा device *dev)
अणु
	काष्ठा iommu_group *group;
	पूर्णांक __maybe_unused ret;

	group = iommu_group_get(dev);

#अगर_घोषित CONFIG_VFIO_NOIOMMU
	/*
	 * With noiommu enabled, an IOMMU group will be created क्रम a device
	 * that करोesn't already have one and doesn't have an iommu_ops on their
	 * bus.  We set iommudata simply to be able to identअगरy these groups
	 * as special use and क्रम reclamation later.
	 */
	अगर (group || !noiommu || iommu_present(dev->bus))
		वापस group;

	group = iommu_group_alloc();
	अगर (IS_ERR(group))
		वापस शून्य;

	iommu_group_set_name(group, "vfio-noiommu");
	iommu_group_set_iommudata(group, &noiommu, शून्य);
	ret = iommu_group_add_device(group, dev);
	अगर (ret) अणु
		iommu_group_put(group);
		वापस शून्य;
	पूर्ण

	/*
	 * Where to taपूर्णांक?  At this poपूर्णांक we've added an IOMMU group क्रम a
	 * device that is not backed by iommu_ops, thereक्रमe any iommu_
	 * callback using iommu_ops can legitimately Oops.  So, जबतक we may
	 * be about to give a DMA capable device to a user without IOMMU
	 * protection, which is clearly taपूर्णांक-worthy, let's go ahead and करो
	 * it here.
	 */
	add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);
	dev_warn(dev, "Adding kernel taint for vfio-noiommu group on device\n");
#पूर्ण_अगर

	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_iommu_group_get);

व्योम vfio_iommu_group_put(काष्ठा iommu_group *group, काष्ठा device *dev)
अणु
#अगर_घोषित CONFIG_VFIO_NOIOMMU
	अगर (iommu_group_get_iommudata(group) == &noiommu)
		iommu_group_हटाओ_device(dev);
#पूर्ण_अगर

	iommu_group_put(group);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_iommu_group_put);

#अगर_घोषित CONFIG_VFIO_NOIOMMU
अटल व्योम *vfio_noiommu_खोलो(अचिन्हित दीर्घ arg)
अणु
	अगर (arg != VFIO_NOIOMMU_IOMMU)
		वापस ERR_PTR(-EINVAL);
	अगर (!capable(CAP_SYS_RAWIO))
		वापस ERR_PTR(-EPERM);

	वापस शून्य;
पूर्ण

अटल व्योम vfio_noiommu_release(व्योम *iommu_data)
अणु
पूर्ण

अटल दीर्घ vfio_noiommu_ioctl(व्योम *iommu_data,
			       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (cmd == VFIO_CHECK_EXTENSION)
		वापस noiommu && (arg == VFIO_NOIOMMU_IOMMU) ? 1 : 0;

	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक vfio_noiommu_attach_group(व्योम *iommu_data,
				     काष्ठा iommu_group *iommu_group)
अणु
	वापस iommu_group_get_iommudata(iommu_group) == &noiommu ? 0 : -EINVAL;
पूर्ण

अटल व्योम vfio_noiommu_detach_group(व्योम *iommu_data,
				      काष्ठा iommu_group *iommu_group)
अणु
पूर्ण

अटल स्थिर काष्ठा vfio_iommu_driver_ops vfio_noiommu_ops = अणु
	.name = "vfio-noiommu",
	.owner = THIS_MODULE,
	.खोलो = vfio_noiommu_खोलो,
	.release = vfio_noiommu_release,
	.ioctl = vfio_noiommu_ioctl,
	.attach_group = vfio_noiommu_attach_group,
	.detach_group = vfio_noiommu_detach_group,
पूर्ण;
#पूर्ण_अगर


/**
 * IOMMU driver registration
 */
पूर्णांक vfio_रेजिस्टर_iommu_driver(स्थिर काष्ठा vfio_iommu_driver_ops *ops)
अणु
	काष्ठा vfio_iommu_driver *driver, *पंचांगp;

	driver = kzalloc(माप(*driver), GFP_KERNEL);
	अगर (!driver)
		वापस -ENOMEM;

	driver->ops = ops;

	mutex_lock(&vfio.iommu_drivers_lock);

	/* Check क्रम duplicates */
	list_क्रम_each_entry(पंचांगp, &vfio.iommu_drivers_list, vfio_next) अणु
		अगर (पंचांगp->ops == ops) अणु
			mutex_unlock(&vfio.iommu_drivers_lock);
			kमुक्त(driver);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	list_add(&driver->vfio_next, &vfio.iommu_drivers_list);

	mutex_unlock(&vfio.iommu_drivers_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_रेजिस्टर_iommu_driver);

व्योम vfio_unरेजिस्टर_iommu_driver(स्थिर काष्ठा vfio_iommu_driver_ops *ops)
अणु
	काष्ठा vfio_iommu_driver *driver;

	mutex_lock(&vfio.iommu_drivers_lock);
	list_क्रम_each_entry(driver, &vfio.iommu_drivers_list, vfio_next) अणु
		अगर (driver->ops == ops) अणु
			list_del(&driver->vfio_next);
			mutex_unlock(&vfio.iommu_drivers_lock);
			kमुक्त(driver);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&vfio.iommu_drivers_lock);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_unरेजिस्टर_iommu_driver);

/**
 * Group minor allocation/मुक्त - both called with vfio.group_lock held
 */
अटल पूर्णांक vfio_alloc_group_minor(काष्ठा vfio_group *group)
अणु
	वापस idr_alloc(&vfio.group_idr, group, 0, MINORMASK + 1, GFP_KERNEL);
पूर्ण

अटल व्योम vfio_मुक्त_group_minor(पूर्णांक minor)
अणु
	idr_हटाओ(&vfio.group_idr, minor);
पूर्ण

अटल पूर्णांक vfio_iommu_group_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data);
अटल व्योम vfio_group_get(काष्ठा vfio_group *group);

/**
 * Container objects - containers are created when /dev/vfio/vfio is
 * खोलोed, but their lअगरecycle extends until the last user is करोne, so
 * it's मुक्तd via kref.  Must support container/group/device being
 * बंदd in any order.
 */
अटल व्योम vfio_container_get(काष्ठा vfio_container *container)
अणु
	kref_get(&container->kref);
पूर्ण

अटल व्योम vfio_container_release(काष्ठा kref *kref)
अणु
	काष्ठा vfio_container *container;
	container = container_of(kref, काष्ठा vfio_container, kref);

	kमुक्त(container);
पूर्ण

अटल व्योम vfio_container_put(काष्ठा vfio_container *container)
अणु
	kref_put(&container->kref, vfio_container_release);
पूर्ण

अटल व्योम vfio_group_unlock_and_मुक्त(काष्ठा vfio_group *group)
अणु
	mutex_unlock(&vfio.group_lock);
	/*
	 * Unरेजिस्टर outside of lock.  A spurious callback is harmless now
	 * that the group is no दीर्घer in vfio.group_list.
	 */
	iommu_group_unरेजिस्टर_notअगरier(group->iommu_group, &group->nb);
	kमुक्त(group);
पूर्ण

/**
 * Group objects - create, release, get, put, search
 */
अटल काष्ठा vfio_group *vfio_create_group(काष्ठा iommu_group *iommu_group)
अणु
	काष्ठा vfio_group *group, *पंचांगp;
	काष्ठा device *dev;
	पूर्णांक ret, minor;

	group = kzalloc(माप(*group), GFP_KERNEL);
	अगर (!group)
		वापस ERR_PTR(-ENOMEM);

	kref_init(&group->kref);
	INIT_LIST_HEAD(&group->device_list);
	mutex_init(&group->device_lock);
	INIT_LIST_HEAD(&group->unbound_list);
	mutex_init(&group->unbound_lock);
	atomic_set(&group->container_users, 0);
	atomic_set(&group->खोलोed, 0);
	init_रुकोqueue_head(&group->container_q);
	group->iommu_group = iommu_group;
#अगर_घोषित CONFIG_VFIO_NOIOMMU
	group->noiommu = (iommu_group_get_iommudata(iommu_group) == &noiommu);
#पूर्ण_अगर
	BLOCKING_INIT_NOTIFIER_HEAD(&group->notअगरier);

	group->nb.notअगरier_call = vfio_iommu_group_notअगरier;

	/*
	 * blocking notअगरiers acquire a rwsem around रेजिस्टरing and hold
	 * it around callback.  Thereक्रमe, need to रेजिस्टर outside of
	 * vfio.group_lock to aव्योम A-B/B-A contention.  Our callback won't
	 * करो anything unless it can find the group in vfio.group_list, so
	 * no harm in रेजिस्टरing early.
	 */
	ret = iommu_group_रेजिस्टर_notअगरier(iommu_group, &group->nb);
	अगर (ret) अणु
		kमुक्त(group);
		वापस ERR_PTR(ret);
	पूर्ण

	mutex_lock(&vfio.group_lock);

	/* Did we race creating this group? */
	list_क्रम_each_entry(पंचांगp, &vfio.group_list, vfio_next) अणु
		अगर (पंचांगp->iommu_group == iommu_group) अणु
			vfio_group_get(पंचांगp);
			vfio_group_unlock_and_मुक्त(group);
			वापस पंचांगp;
		पूर्ण
	पूर्ण

	minor = vfio_alloc_group_minor(group);
	अगर (minor < 0) अणु
		vfio_group_unlock_and_मुक्त(group);
		वापस ERR_PTR(minor);
	पूर्ण

	dev = device_create(vfio.class, शून्य,
			    MKDEV(MAJOR(vfio.group_devt), minor),
			    group, "%s%d", group->noiommu ? "noiommu-" : "",
			    iommu_group_id(iommu_group));
	अगर (IS_ERR(dev)) अणु
		vfio_मुक्त_group_minor(minor);
		vfio_group_unlock_and_मुक्त(group);
		वापस ERR_CAST(dev);
	पूर्ण

	group->minor = minor;
	group->dev = dev;

	list_add(&group->vfio_next, &vfio.group_list);

	mutex_unlock(&vfio.group_lock);

	वापस group;
पूर्ण

/* called with vfio.group_lock held */
अटल व्योम vfio_group_release(काष्ठा kref *kref)
अणु
	काष्ठा vfio_group *group = container_of(kref, काष्ठा vfio_group, kref);
	काष्ठा vfio_unbound_dev *unbound, *पंचांगp;
	काष्ठा iommu_group *iommu_group = group->iommu_group;

	WARN_ON(!list_empty(&group->device_list));
	WARN_ON(group->notअगरier.head);

	list_क्रम_each_entry_safe(unbound, पंचांगp,
				 &group->unbound_list, unbound_next) अणु
		list_del(&unbound->unbound_next);
		kमुक्त(unbound);
	पूर्ण

	device_destroy(vfio.class, MKDEV(MAJOR(vfio.group_devt), group->minor));
	list_del(&group->vfio_next);
	vfio_मुक्त_group_minor(group->minor);
	vfio_group_unlock_and_मुक्त(group);
	iommu_group_put(iommu_group);
पूर्ण

अटल व्योम vfio_group_put(काष्ठा vfio_group *group)
अणु
	kref_put_mutex(&group->kref, vfio_group_release, &vfio.group_lock);
पूर्ण

काष्ठा vfio_group_put_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा vfio_group *group;
पूर्ण;

अटल व्योम vfio_group_put_bg(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vfio_group_put_work *करो_work;

	करो_work = container_of(work, काष्ठा vfio_group_put_work, work);

	vfio_group_put(करो_work->group);
	kमुक्त(करो_work);
पूर्ण

अटल व्योम vfio_group_schedule_put(काष्ठा vfio_group *group)
अणु
	काष्ठा vfio_group_put_work *करो_work;

	करो_work = kदो_स्मृति(माप(*करो_work), GFP_KERNEL);
	अगर (WARN_ON(!करो_work))
		वापस;

	INIT_WORK(&करो_work->work, vfio_group_put_bg);
	करो_work->group = group;
	schedule_work(&करो_work->work);
पूर्ण

/* Assume group_lock or group reference is held */
अटल व्योम vfio_group_get(काष्ठा vfio_group *group)
अणु
	kref_get(&group->kref);
पूर्ण

/*
 * Not really a try as we will sleep क्रम mutex, but we need to make
 * sure the group poपूर्णांकer is valid under lock and get a reference.
 */
अटल काष्ठा vfio_group *vfio_group_try_get(काष्ठा vfio_group *group)
अणु
	काष्ठा vfio_group *target = group;

	mutex_lock(&vfio.group_lock);
	list_क्रम_each_entry(group, &vfio.group_list, vfio_next) अणु
		अगर (group == target) अणु
			vfio_group_get(group);
			mutex_unlock(&vfio.group_lock);
			वापस group;
		पूर्ण
	पूर्ण
	mutex_unlock(&vfio.group_lock);

	वापस शून्य;
पूर्ण

अटल
काष्ठा vfio_group *vfio_group_get_from_iommu(काष्ठा iommu_group *iommu_group)
अणु
	काष्ठा vfio_group *group;

	mutex_lock(&vfio.group_lock);
	list_क्रम_each_entry(group, &vfio.group_list, vfio_next) अणु
		अगर (group->iommu_group == iommu_group) अणु
			vfio_group_get(group);
			mutex_unlock(&vfio.group_lock);
			वापस group;
		पूर्ण
	पूर्ण
	mutex_unlock(&vfio.group_lock);

	वापस शून्य;
पूर्ण

अटल काष्ठा vfio_group *vfio_group_get_from_minor(पूर्णांक minor)
अणु
	काष्ठा vfio_group *group;

	mutex_lock(&vfio.group_lock);
	group = idr_find(&vfio.group_idr, minor);
	अगर (!group) अणु
		mutex_unlock(&vfio.group_lock);
		वापस शून्य;
	पूर्ण
	vfio_group_get(group);
	mutex_unlock(&vfio.group_lock);

	वापस group;
पूर्ण

अटल काष्ठा vfio_group *vfio_group_get_from_dev(काष्ठा device *dev)
अणु
	काष्ठा iommu_group *iommu_group;
	काष्ठा vfio_group *group;

	iommu_group = iommu_group_get(dev);
	अगर (!iommu_group)
		वापस शून्य;

	group = vfio_group_get_from_iommu(iommu_group);
	iommu_group_put(iommu_group);

	वापस group;
पूर्ण

/**
 * Device objects - create, release, get, put, search
 */
/* Device reference always implies a group reference */
व्योम vfio_device_put(काष्ठा vfio_device *device)
अणु
	अगर (refcount_dec_and_test(&device->refcount))
		complete(&device->comp);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_device_put);

अटल bool vfio_device_try_get(काष्ठा vfio_device *device)
अणु
	वापस refcount_inc_not_zero(&device->refcount);
पूर्ण

अटल काष्ठा vfio_device *vfio_group_get_device(काष्ठा vfio_group *group,
						 काष्ठा device *dev)
अणु
	काष्ठा vfio_device *device;

	mutex_lock(&group->device_lock);
	list_क्रम_each_entry(device, &group->device_list, group_next) अणु
		अगर (device->dev == dev && vfio_device_try_get(device)) अणु
			mutex_unlock(&group->device_lock);
			वापस device;
		पूर्ण
	पूर्ण
	mutex_unlock(&group->device_lock);
	वापस शून्य;
पूर्ण

/*
 * Some drivers, like pci-stub, are only used to prevent other drivers from
 * claiming a device and are thereक्रमe perfectly legitimate क्रम a user owned
 * group.  The pci-stub driver has no dependencies on DMA or the IOVA mapping
 * of the device, but it करोes prevent the user from having direct access to
 * the device, which is useful in some circumstances.
 *
 * We also assume that we can include PCI पूर्णांकerconnect devices, ie. bridges.
 * IOMMU grouping on PCI necessitates that अगर we lack isolation on a bridge
 * then all of the करोwnstream devices will be part of the same IOMMU group as
 * the bridge.  Thus, अगर placing the bridge पूर्णांकo the user owned IOVA space
 * अवरोधs anything, it only करोes so क्रम user owned devices करोwnstream.  Note
 * that error notअगरication via MSI can be affected क्रम platक्रमms that handle
 * MSI within the same IOVA space as DMA.
 */
अटल स्थिर अक्षर * स्थिर vfio_driver_allowed[] = अणु "pci-stub" पूर्ण;

अटल bool vfio_dev_driver_allowed(काष्ठा device *dev,
				    काष्ठा device_driver *drv)
अणु
	अगर (dev_is_pci(dev)) अणु
		काष्ठा pci_dev *pdev = to_pci_dev(dev);

		अगर (pdev->hdr_type != PCI_HEADER_TYPE_NORMAL)
			वापस true;
	पूर्ण

	वापस match_string(vfio_driver_allowed,
			    ARRAY_SIZE(vfio_driver_allowed),
			    drv->name) >= 0;
पूर्ण

/*
 * A vfio group is viable क्रम use by userspace अगर all devices are in
 * one of the following states:
 *  - driver-less
 *  - bound to a vfio driver
 *  - bound to an otherwise allowed driver
 *  - a PCI पूर्णांकerconnect device
 *
 * We use two methods to determine whether a device is bound to a vfio
 * driver.  The first is to test whether the device exists in the vfio
 * group.  The second is to test अगर the device exists on the group
 * unbound_list, indicating it's in the middle of transitioning from
 * a vfio driver to driver-less.
 */
अटल पूर्णांक vfio_dev_viable(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा vfio_group *group = data;
	काष्ठा vfio_device *device;
	काष्ठा device_driver *drv = READ_ONCE(dev->driver);
	काष्ठा vfio_unbound_dev *unbound;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&group->unbound_lock);
	list_क्रम_each_entry(unbound, &group->unbound_list, unbound_next) अणु
		अगर (dev == unbound->dev) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&group->unbound_lock);

	अगर (!ret || !drv || vfio_dev_driver_allowed(dev, drv))
		वापस 0;

	device = vfio_group_get_device(group, dev);
	अगर (device) अणु
		vfio_device_put(device);
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * Async device support
 */
अटल पूर्णांक vfio_group_nb_add_dev(काष्ठा vfio_group *group, काष्ठा device *dev)
अणु
	काष्ठा vfio_device *device;

	/* Do we alपढ़ोy know about it?  We shouldn't */
	device = vfio_group_get_device(group, dev);
	अगर (WARN_ON_ONCE(device)) अणु
		vfio_device_put(device);
		वापस 0;
	पूर्ण

	/* Nothing to करो क्रम idle groups */
	अगर (!atomic_पढ़ो(&group->container_users))
		वापस 0;

	/* TODO Prevent device स्वतः probing */
	dev_WARN(dev, "Device added to live group %d!\n",
		 iommu_group_id(group->iommu_group));

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_group_nb_verअगरy(काष्ठा vfio_group *group, काष्ठा device *dev)
अणु
	/* We करोn't care what happens when the group isn't in use */
	अगर (!atomic_पढ़ो(&group->container_users))
		वापस 0;

	वापस vfio_dev_viable(dev, group);
पूर्ण

अटल पूर्णांक vfio_iommu_group_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा vfio_group *group = container_of(nb, काष्ठा vfio_group, nb);
	काष्ठा device *dev = data;
	काष्ठा vfio_unbound_dev *unbound;

	/*
	 * Need to go through a group_lock lookup to get a reference or we
	 * risk racing a group being हटाओd.  Ignore spurious notअगरies.
	 */
	group = vfio_group_try_get(group);
	अगर (!group)
		वापस NOTIFY_OK;

	चयन (action) अणु
	हाल IOMMU_GROUP_NOTIFY_ADD_DEVICE:
		vfio_group_nb_add_dev(group, dev);
		अवरोध;
	हाल IOMMU_GROUP_NOTIFY_DEL_DEVICE:
		/*
		 * Nothing to करो here.  If the device is in use, then the
		 * vfio sub-driver should block the हटाओ callback until
		 * it is unused.  If the device is unused or attached to a
		 * stub driver, then it should be released and we करोn't
		 * care that it will be going away.
		 */
		अवरोध;
	हाल IOMMU_GROUP_NOTIFY_BIND_DRIVER:
		dev_dbg(dev, "%s: group %d binding to driver\n", __func__,
			iommu_group_id(group->iommu_group));
		अवरोध;
	हाल IOMMU_GROUP_NOTIFY_BOUND_DRIVER:
		dev_dbg(dev, "%s: group %d bound to driver %s\n", __func__,
			iommu_group_id(group->iommu_group), dev->driver->name);
		BUG_ON(vfio_group_nb_verअगरy(group, dev));
		अवरोध;
	हाल IOMMU_GROUP_NOTIFY_UNBIND_DRIVER:
		dev_dbg(dev, "%s: group %d unbinding from driver %s\n",
			__func__, iommu_group_id(group->iommu_group),
			dev->driver->name);
		अवरोध;
	हाल IOMMU_GROUP_NOTIFY_UNBOUND_DRIVER:
		dev_dbg(dev, "%s: group %d unbound from driver\n", __func__,
			iommu_group_id(group->iommu_group));
		/*
		 * XXX An unbound device in a live group is ok, but we'd
		 * really like to aव्योम the above BUG_ON by preventing other
		 * drivers from binding to it.  Once that occurs, we have to
		 * stop the प्रणाली to मुख्यtain isolation.  At a minimum, we'd
		 * want a toggle to disable driver स्वतः probe क्रम this device.
		 */

		mutex_lock(&group->unbound_lock);
		list_क्रम_each_entry(unbound,
				    &group->unbound_list, unbound_next) अणु
			अगर (dev == unbound->dev) अणु
				list_del(&unbound->unbound_next);
				kमुक्त(unbound);
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&group->unbound_lock);
		अवरोध;
	पूर्ण

	/*
	 * If we're the last reference to the group, the group will be
	 * released, which includes unरेजिस्टरing the iommu group notअगरier.
	 * We hold a पढ़ो-lock on that notअगरier list, unरेजिस्टरing needs
	 * a ग_लिखो-lock... deadlock.  Release our reference asynchronously
	 * to aव्योम that situation.
	 */
	vfio_group_schedule_put(group);
	वापस NOTIFY_OK;
पूर्ण

/**
 * VFIO driver API
 */
व्योम vfio_init_group_dev(काष्ठा vfio_device *device, काष्ठा device *dev,
			 स्थिर काष्ठा vfio_device_ops *ops)
अणु
	init_completion(&device->comp);
	device->dev = dev;
	device->ops = ops;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_init_group_dev);

पूर्णांक vfio_रेजिस्टर_group_dev(काष्ठा vfio_device *device)
अणु
	काष्ठा vfio_device *existing_device;
	काष्ठा iommu_group *iommu_group;
	काष्ठा vfio_group *group;

	iommu_group = iommu_group_get(device->dev);
	अगर (!iommu_group)
		वापस -EINVAL;

	group = vfio_group_get_from_iommu(iommu_group);
	अगर (!group) अणु
		group = vfio_create_group(iommu_group);
		अगर (IS_ERR(group)) अणु
			iommu_group_put(iommu_group);
			वापस PTR_ERR(group);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * A found vfio_group alपढ़ोy holds a reference to the
		 * iommu_group.  A created vfio_group keeps the reference.
		 */
		iommu_group_put(iommu_group);
	पूर्ण

	existing_device = vfio_group_get_device(group, device->dev);
	अगर (existing_device) अणु
		dev_WARN(device->dev, "Device already exists on group %d\n",
			 iommu_group_id(iommu_group));
		vfio_device_put(existing_device);
		vfio_group_put(group);
		वापस -EBUSY;
	पूर्ण

	/* Our reference on group is moved to the device */
	device->group = group;

	/* Refcounting can't start until the driver calls रेजिस्टर */
	refcount_set(&device->refcount, 1);

	mutex_lock(&group->device_lock);
	list_add(&device->group_next, &group->device_list);
	group->dev_counter++;
	mutex_unlock(&group->device_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_रेजिस्टर_group_dev);

/**
 * Get a reference to the vfio_device क्रम a device.  Even अगर the
 * caller thinks they own the device, they could be racing with a
 * release call path, so we can't trust drvdata क्रम the लघुcut.
 * Go the दीर्घ way around, from the iommu_group to the vfio_group
 * to the vfio_device.
 */
काष्ठा vfio_device *vfio_device_get_from_dev(काष्ठा device *dev)
अणु
	काष्ठा vfio_group *group;
	काष्ठा vfio_device *device;

	group = vfio_group_get_from_dev(dev);
	अगर (!group)
		वापस शून्य;

	device = vfio_group_get_device(group, dev);
	vfio_group_put(group);

	वापस device;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_device_get_from_dev);

अटल काष्ठा vfio_device *vfio_device_get_from_name(काष्ठा vfio_group *group,
						     अक्षर *buf)
अणु
	काष्ठा vfio_device *it, *device = ERR_PTR(-ENODEV);

	mutex_lock(&group->device_lock);
	list_क्रम_each_entry(it, &group->device_list, group_next) अणु
		पूर्णांक ret;

		अगर (it->ops->match) अणु
			ret = it->ops->match(it, buf);
			अगर (ret < 0) अणु
				device = ERR_PTR(ret);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = !म_भेद(dev_name(it->dev), buf);
		पूर्ण

		अगर (ret && vfio_device_try_get(it)) अणु
			device = it;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&group->device_lock);

	वापस device;
पूर्ण

/*
 * Decrement the device reference count and रुको क्रम the device to be
 * हटाओd.  Open file descriptors क्रम the device... */
व्योम vfio_unरेजिस्टर_group_dev(काष्ठा vfio_device *device)
अणु
	काष्ठा vfio_group *group = device->group;
	काष्ठा vfio_unbound_dev *unbound;
	अचिन्हित पूर्णांक i = 0;
	bool पूर्णांकerrupted = false;
	दीर्घ rc;

	/*
	 * When the device is हटाओd from the group, the group suddenly
	 * becomes non-viable; the device has a driver (until the unbind
	 * completes), but it's not present in the group.  This is bad news
	 * क्रम any बाह्यal users that need to re-acquire a group reference
	 * in order to match and release their existing reference.  To
	 * solve this, we track such devices on the unbound_list to bridge
	 * the gap until they're fully unbound.
	 */
	unbound = kzalloc(माप(*unbound), GFP_KERNEL);
	अगर (unbound) अणु
		unbound->dev = device->dev;
		mutex_lock(&group->unbound_lock);
		list_add(&unbound->unbound_next, &group->unbound_list);
		mutex_unlock(&group->unbound_lock);
	पूर्ण
	WARN_ON(!unbound);

	vfio_device_put(device);
	rc = try_रुको_क्रम_completion(&device->comp);
	जबतक (rc <= 0) अणु
		अगर (device->ops->request)
			device->ops->request(device, i++);

		अगर (पूर्णांकerrupted) अणु
			rc = रुको_क्रम_completion_समयout(&device->comp,
							 HZ * 10);
		पूर्ण अन्यथा अणु
			rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
				&device->comp, HZ * 10);
			अगर (rc < 0) अणु
				पूर्णांकerrupted = true;
				dev_warn(device->dev,
					 "Device is currently in use, task"
					 " \"%s\" (%d) "
					 "blocked until device is released",
					 current->comm, task_pid_nr(current));
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_lock(&group->device_lock);
	list_del(&device->group_next);
	group->dev_counter--;
	mutex_unlock(&group->device_lock);

	/*
	 * In order to support multiple devices per group, devices can be
	 * plucked from the group जबतक other devices in the group are still
	 * in use.  The container persists with this group and those reमुख्यing
	 * devices still attached.  If the user creates an isolation violation
	 * by binding this device to another driver जबतक the group is still in
	 * use, that's their fault.  However, in the हाल of removing the last,
	 * or potentially the only, device in the group there can be no other
	 * in-use devices in the group.  The user has करोne their due diligence
	 * and we should lay no claims to those devices.  In order to करो that,
	 * we need to make sure the group is detached from the container.
	 * Without this stall, we're potentially racing with a user process
	 * that may attempt to immediately bind this device to another driver.
	 */
	अगर (list_empty(&group->device_list))
		रुको_event(group->container_q, !group->container);

	/* Matches the get in vfio_रेजिस्टर_group_dev() */
	vfio_group_put(group);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_unरेजिस्टर_group_dev);

/**
 * VFIO base fd, /dev/vfio/vfio
 */
अटल दीर्घ vfio_ioctl_check_extension(काष्ठा vfio_container *container,
				       अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_iommu_driver *driver;
	दीर्घ ret = 0;

	करोwn_पढ़ो(&container->group_lock);

	driver = container->iommu_driver;

	चयन (arg) अणु
		/* No base extensions yet */
	शेष:
		/*
		 * If no driver is set, poll all रेजिस्टरed drivers क्रम
		 * extensions and वापस the first positive result.  If
		 * a driver is alपढ़ोy set, further queries will be passed
		 * only to that driver.
		 */
		अगर (!driver) अणु
			mutex_lock(&vfio.iommu_drivers_lock);
			list_क्रम_each_entry(driver, &vfio.iommu_drivers_list,
					    vfio_next) अणु

#अगर_घोषित CONFIG_VFIO_NOIOMMU
				अगर (!list_empty(&container->group_list) &&
				    (container->noiommu !=
				     (driver->ops == &vfio_noiommu_ops)))
					जारी;
#पूर्ण_अगर

				अगर (!try_module_get(driver->ops->owner))
					जारी;

				ret = driver->ops->ioctl(शून्य,
							 VFIO_CHECK_EXTENSION,
							 arg);
				module_put(driver->ops->owner);
				अगर (ret > 0)
					अवरोध;
			पूर्ण
			mutex_unlock(&vfio.iommu_drivers_lock);
		पूर्ण अन्यथा
			ret = driver->ops->ioctl(container->iommu_data,
						 VFIO_CHECK_EXTENSION, arg);
	पूर्ण

	up_पढ़ो(&container->group_lock);

	वापस ret;
पूर्ण

/* hold ग_लिखो lock on container->group_lock */
अटल पूर्णांक __vfio_container_attach_groups(काष्ठा vfio_container *container,
					  काष्ठा vfio_iommu_driver *driver,
					  व्योम *data)
अणु
	काष्ठा vfio_group *group;
	पूर्णांक ret = -ENODEV;

	list_क्रम_each_entry(group, &container->group_list, container_next) अणु
		ret = driver->ops->attach_group(data, group->iommu_group);
		अगर (ret)
			जाओ unwind;
	पूर्ण

	वापस ret;

unwind:
	list_क्रम_each_entry_जारी_reverse(group, &container->group_list,
					     container_next) अणु
		driver->ops->detach_group(data, group->iommu_group);
	पूर्ण

	वापस ret;
पूर्ण

अटल दीर्घ vfio_ioctl_set_iommu(काष्ठा vfio_container *container,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_iommu_driver *driver;
	दीर्घ ret = -ENODEV;

	करोwn_ग_लिखो(&container->group_lock);

	/*
	 * The container is deचिन्हित to be an unprivileged पूर्णांकerface जबतक
	 * the group can be asचिन्हित to specअगरic users.  Thereक्रमe, only by
	 * adding a group to a container करोes the user get the privilege of
	 * enabling the iommu, which may allocate finite resources.  There
	 * is no unset_iommu, but by removing all the groups from a container,
	 * the container is deprivileged and वापसs to an unset state.
	 */
	अगर (list_empty(&container->group_list) || container->iommu_driver) अणु
		up_ग_लिखो(&container->group_lock);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&vfio.iommu_drivers_lock);
	list_क्रम_each_entry(driver, &vfio.iommu_drivers_list, vfio_next) अणु
		व्योम *data;

#अगर_घोषित CONFIG_VFIO_NOIOMMU
		/*
		 * Only noiommu containers can use vfio-noiommu and noiommu
		 * containers can only use vfio-noiommu.
		 */
		अगर (container->noiommu != (driver->ops == &vfio_noiommu_ops))
			जारी;
#पूर्ण_अगर

		अगर (!try_module_get(driver->ops->owner))
			जारी;

		/*
		 * The arg magic क्रम SET_IOMMU is the same as CHECK_EXTENSION,
		 * so test which iommu driver reported support क्रम this
		 * extension and call खोलो on them.  We also pass them the
		 * magic, allowing a single driver to support multiple
		 * पूर्णांकerfaces अगर they'd like.
		 */
		अगर (driver->ops->ioctl(शून्य, VFIO_CHECK_EXTENSION, arg) <= 0) अणु
			module_put(driver->ops->owner);
			जारी;
		पूर्ण

		data = driver->ops->खोलो(arg);
		अगर (IS_ERR(data)) अणु
			ret = PTR_ERR(data);
			module_put(driver->ops->owner);
			जारी;
		पूर्ण

		ret = __vfio_container_attach_groups(container, driver, data);
		अगर (ret) अणु
			driver->ops->release(data);
			module_put(driver->ops->owner);
			जारी;
		पूर्ण

		container->iommu_driver = driver;
		container->iommu_data = data;
		अवरोध;
	पूर्ण

	mutex_unlock(&vfio.iommu_drivers_lock);
	up_ग_लिखो(&container->group_lock);

	वापस ret;
पूर्ण

अटल दीर्घ vfio_fops_unl_ioctl(काष्ठा file *filep,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_container *container = filep->निजी_data;
	काष्ठा vfio_iommu_driver *driver;
	व्योम *data;
	दीर्घ ret = -EINVAL;

	अगर (!container)
		वापस ret;

	चयन (cmd) अणु
	हाल VFIO_GET_API_VERSION:
		ret = VFIO_API_VERSION;
		अवरोध;
	हाल VFIO_CHECK_EXTENSION:
		ret = vfio_ioctl_check_extension(container, arg);
		अवरोध;
	हाल VFIO_SET_IOMMU:
		ret = vfio_ioctl_set_iommu(container, arg);
		अवरोध;
	शेष:
		driver = container->iommu_driver;
		data = container->iommu_data;

		अगर (driver) /* passthrough all unrecognized ioctls */
			ret = driver->ops->ioctl(data, cmd, arg);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_fops_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा vfio_container *container;

	container = kzalloc(माप(*container), GFP_KERNEL);
	अगर (!container)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&container->group_list);
	init_rwsem(&container->group_lock);
	kref_init(&container->kref);

	filep->निजी_data = container;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_fops_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा vfio_container *container = filep->निजी_data;
	काष्ठा vfio_iommu_driver *driver = container->iommu_driver;

	अगर (driver && driver->ops->notअगरy)
		driver->ops->notअगरy(container->iommu_data,
				    VFIO_IOMMU_CONTAINER_CLOSE);

	filep->निजी_data = शून्य;

	vfio_container_put(container);

	वापस 0;
पूर्ण

/*
 * Once an iommu driver is set, we optionally pass पढ़ो/ग_लिखो/mmap
 * on to the driver, allowing management पूर्णांकerfaces beyond ioctl.
 */
अटल sमाप_प्रकार vfio_fops_पढ़ो(काष्ठा file *filep, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_container *container = filep->निजी_data;
	काष्ठा vfio_iommu_driver *driver;
	sमाप_प्रकार ret = -EINVAL;

	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->पढ़ो))
		ret = driver->ops->पढ़ो(container->iommu_data,
					buf, count, ppos);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार vfio_fops_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_container *container = filep->निजी_data;
	काष्ठा vfio_iommu_driver *driver;
	sमाप_प्रकार ret = -EINVAL;

	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->ग_लिखो))
		ret = driver->ops->ग_लिखो(container->iommu_data,
					 buf, count, ppos);

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_fops_mmap(काष्ठा file *filep, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vfio_container *container = filep->निजी_data;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret = -EINVAL;

	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->mmap))
		ret = driver->ops->mmap(container->iommu_data, vma);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations vfio_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= vfio_fops_खोलो,
	.release	= vfio_fops_release,
	.पढ़ो		= vfio_fops_पढ़ो,
	.ग_लिखो		= vfio_fops_ग_लिखो,
	.unlocked_ioctl	= vfio_fops_unl_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.mmap		= vfio_fops_mmap,
पूर्ण;

/**
 * VFIO Group fd, /dev/vfio/$GROUP
 */
अटल व्योम __vfio_group_unset_container(काष्ठा vfio_group *group)
अणु
	काष्ठा vfio_container *container = group->container;
	काष्ठा vfio_iommu_driver *driver;

	करोwn_ग_लिखो(&container->group_lock);

	driver = container->iommu_driver;
	अगर (driver)
		driver->ops->detach_group(container->iommu_data,
					  group->iommu_group);

	group->container = शून्य;
	wake_up(&group->container_q);
	list_del(&group->container_next);

	/* Detaching the last group deprivileges a container, हटाओ iommu */
	अगर (driver && list_empty(&container->group_list)) अणु
		driver->ops->release(container->iommu_data);
		module_put(driver->ops->owner);
		container->iommu_driver = शून्य;
		container->iommu_data = शून्य;
	पूर्ण

	up_ग_लिखो(&container->group_lock);

	vfio_container_put(container);
पूर्ण

/*
 * VFIO_GROUP_UNSET_CONTAINER should fail अगर there are other users or
 * अगर there was no container to unset.  Since the ioctl is called on
 * the group, we know that still exists, thereक्रमe the only valid
 * transition here is 1->0.
 */
अटल पूर्णांक vfio_group_unset_container(काष्ठा vfio_group *group)
अणु
	पूर्णांक users = atomic_cmpxchg(&group->container_users, 1, 0);

	अगर (!users)
		वापस -EINVAL;
	अगर (users != 1)
		वापस -EBUSY;

	__vfio_group_unset_container(group);

	वापस 0;
पूर्ण

/*
 * When removing container users, anything that हटाओs the last user
 * implicitly हटाओs the group from the container.  That is, अगर the
 * group file descriptor is बंदd, as well as any device file descriptors,
 * the group is मुक्त.
 */
अटल व्योम vfio_group_try_dissolve_container(काष्ठा vfio_group *group)
अणु
	अगर (0 == atomic_dec_अगर_positive(&group->container_users))
		__vfio_group_unset_container(group);
पूर्ण

अटल पूर्णांक vfio_group_set_container(काष्ठा vfio_group *group, पूर्णांक container_fd)
अणु
	काष्ठा fd f;
	काष्ठा vfio_container *container;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret = 0;

	अगर (atomic_पढ़ो(&group->container_users))
		वापस -EINVAL;

	अगर (group->noiommu && !capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	f = fdget(container_fd);
	अगर (!f.file)
		वापस -EBADF;

	/* Sanity check, is this really our fd? */
	अगर (f.file->f_op != &vfio_fops) अणु
		fdput(f);
		वापस -EINVAL;
	पूर्ण

	container = f.file->निजी_data;
	WARN_ON(!container); /* fget ensures we करोn't race vfio_release */

	करोwn_ग_लिखो(&container->group_lock);

	/* Real groups and fake groups cannot mix */
	अगर (!list_empty(&container->group_list) &&
	    container->noiommu != group->noiommu) अणु
		ret = -EPERM;
		जाओ unlock_out;
	पूर्ण

	driver = container->iommu_driver;
	अगर (driver) अणु
		ret = driver->ops->attach_group(container->iommu_data,
						group->iommu_group);
		अगर (ret)
			जाओ unlock_out;
	पूर्ण

	group->container = container;
	container->noiommu = group->noiommu;
	list_add(&group->container_next, &container->group_list);

	/* Get a reference on the container and mark a user within the group */
	vfio_container_get(container);
	atomic_inc(&group->container_users);

unlock_out:
	up_ग_लिखो(&container->group_lock);
	fdput(f);
	वापस ret;
पूर्ण

अटल bool vfio_group_viable(काष्ठा vfio_group *group)
अणु
	वापस (iommu_group_क्रम_each_dev(group->iommu_group,
					 group, vfio_dev_viable) == 0);
पूर्ण

अटल पूर्णांक vfio_group_add_container_user(काष्ठा vfio_group *group)
अणु
	अगर (!atomic_inc_not_zero(&group->container_users))
		वापस -EINVAL;

	अगर (group->noiommu) अणु
		atomic_dec(&group->container_users);
		वापस -EPERM;
	पूर्ण
	अगर (!group->container->iommu_driver || !vfio_group_viable(group)) अणु
		atomic_dec(&group->container_users);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations vfio_device_fops;

अटल पूर्णांक vfio_group_get_device_fd(काष्ठा vfio_group *group, अक्षर *buf)
अणु
	काष्ठा vfio_device *device;
	काष्ठा file *filep;
	पूर्णांक ret;

	अगर (0 == atomic_पढ़ो(&group->container_users) ||
	    !group->container->iommu_driver || !vfio_group_viable(group))
		वापस -EINVAL;

	अगर (group->noiommu && !capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	device = vfio_device_get_from_name(group, buf);
	अगर (IS_ERR(device))
		वापस PTR_ERR(device);

	ret = device->ops->खोलो(device);
	अगर (ret) अणु
		vfio_device_put(device);
		वापस ret;
	पूर्ण

	/*
	 * We can't use anon_inode_getfd() because we need to modअगरy
	 * the f_mode flags directly to allow more than just ioctls
	 */
	ret = get_unused_fd_flags(O_CLOEXEC);
	अगर (ret < 0) अणु
		device->ops->release(device);
		vfio_device_put(device);
		वापस ret;
	पूर्ण

	filep = anon_inode_getfile("[vfio-device]", &vfio_device_fops,
				   device, O_RDWR);
	अगर (IS_ERR(filep)) अणु
		put_unused_fd(ret);
		ret = PTR_ERR(filep);
		device->ops->release(device);
		vfio_device_put(device);
		वापस ret;
	पूर्ण

	/*
	 * TODO: add an anon_inode पूर्णांकerface to करो this.
	 * Appears to be missing by lack of need rather than
	 * explicitly prevented.  Now there's need.
	 */
	filep->f_mode |= (FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE);

	atomic_inc(&group->container_users);

	fd_install(ret, filep);

	अगर (group->noiommu)
		dev_warn(device->dev, "vfio-noiommu device opened by user "
			 "(%s:%d)\n", current->comm, task_pid_nr(current));

	वापस ret;
पूर्ण

अटल दीर्घ vfio_group_fops_unl_ioctl(काष्ठा file *filep,
				      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_group *group = filep->निजी_data;
	दीर्घ ret = -ENOTTY;

	चयन (cmd) अणु
	हाल VFIO_GROUP_GET_STATUS:
	अणु
		काष्ठा vfio_group_status status;
		अचिन्हित दीर्घ minsz;

		minsz = दुरत्वend(काष्ठा vfio_group_status, flags);

		अगर (copy_from_user(&status, (व्योम __user *)arg, minsz))
			वापस -EFAULT;

		अगर (status.argsz < minsz)
			वापस -EINVAL;

		status.flags = 0;

		अगर (vfio_group_viable(group))
			status.flags |= VFIO_GROUP_FLAGS_VIABLE;

		अगर (group->container)
			status.flags |= VFIO_GROUP_FLAGS_CONTAINER_SET;

		अगर (copy_to_user((व्योम __user *)arg, &status, minsz))
			वापस -EFAULT;

		ret = 0;
		अवरोध;
	पूर्ण
	हाल VFIO_GROUP_SET_CONTAINER:
	अणु
		पूर्णांक fd;

		अगर (get_user(fd, (पूर्णांक __user *)arg))
			वापस -EFAULT;

		अगर (fd < 0)
			वापस -EINVAL;

		ret = vfio_group_set_container(group, fd);
		अवरोध;
	पूर्ण
	हाल VFIO_GROUP_UNSET_CONTAINER:
		ret = vfio_group_unset_container(group);
		अवरोध;
	हाल VFIO_GROUP_GET_DEVICE_FD:
	अणु
		अक्षर *buf;

		buf = strndup_user((स्थिर अक्षर __user *)arg, PAGE_SIZE);
		अगर (IS_ERR(buf))
			वापस PTR_ERR(buf);

		ret = vfio_group_get_device_fd(group, buf);
		kमुक्त(buf);
		अवरोध;
	पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_group_fops_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा vfio_group *group;
	पूर्णांक खोलोed;

	group = vfio_group_get_from_minor(iminor(inode));
	अगर (!group)
		वापस -ENODEV;

	अगर (group->noiommu && !capable(CAP_SYS_RAWIO)) अणु
		vfio_group_put(group);
		वापस -EPERM;
	पूर्ण

	/* Do we need multiple instances of the group खोलो?  Seems not. */
	खोलोed = atomic_cmpxchg(&group->खोलोed, 0, 1);
	अगर (खोलोed) अणु
		vfio_group_put(group);
		वापस -EBUSY;
	पूर्ण

	/* Is something still in use from a previous खोलो? */
	अगर (group->container) अणु
		atomic_dec(&group->खोलोed);
		vfio_group_put(group);
		वापस -EBUSY;
	पूर्ण

	/* Warn अगर previous user didn't cleanup and re-init to drop them */
	अगर (WARN_ON(group->notअगरier.head))
		BLOCKING_INIT_NOTIFIER_HEAD(&group->notअगरier);

	filep->निजी_data = group;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_group_fops_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा vfio_group *group = filep->निजी_data;

	filep->निजी_data = शून्य;

	vfio_group_try_dissolve_container(group);

	atomic_dec(&group->खोलोed);

	vfio_group_put(group);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations vfio_group_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= vfio_group_fops_unl_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= vfio_group_fops_खोलो,
	.release	= vfio_group_fops_release,
पूर्ण;

/**
 * VFIO Device fd
 */
अटल पूर्णांक vfio_device_fops_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा vfio_device *device = filep->निजी_data;

	device->ops->release(device);

	vfio_group_try_dissolve_container(device->group);

	vfio_device_put(device);

	वापस 0;
पूर्ण

अटल दीर्घ vfio_device_fops_unl_ioctl(काष्ठा file *filep,
				       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_device *device = filep->निजी_data;

	अगर (unlikely(!device->ops->ioctl))
		वापस -EINVAL;

	वापस device->ops->ioctl(device, cmd, arg);
पूर्ण

अटल sमाप_प्रकार vfio_device_fops_पढ़ो(काष्ठा file *filep, अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_device *device = filep->निजी_data;

	अगर (unlikely(!device->ops->पढ़ो))
		वापस -EINVAL;

	वापस device->ops->पढ़ो(device, buf, count, ppos);
पूर्ण

अटल sमाप_प्रकार vfio_device_fops_ग_लिखो(काष्ठा file *filep,
				      स्थिर अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vfio_device *device = filep->निजी_data;

	अगर (unlikely(!device->ops->ग_लिखो))
		वापस -EINVAL;

	वापस device->ops->ग_लिखो(device, buf, count, ppos);
पूर्ण

अटल पूर्णांक vfio_device_fops_mmap(काष्ठा file *filep, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vfio_device *device = filep->निजी_data;

	अगर (unlikely(!device->ops->mmap))
		वापस -EINVAL;

	वापस device->ops->mmap(device, vma);
पूर्ण

अटल स्थिर काष्ठा file_operations vfio_device_fops = अणु
	.owner		= THIS_MODULE,
	.release	= vfio_device_fops_release,
	.पढ़ो		= vfio_device_fops_पढ़ो,
	.ग_लिखो		= vfio_device_fops_ग_लिखो,
	.unlocked_ioctl	= vfio_device_fops_unl_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.mmap		= vfio_device_fops_mmap,
पूर्ण;

/**
 * External user API, exported by symbols to be linked dynamically.
 *
 * The protocol includes:
 *  1. करो normal VFIO init operation:
 *	- खोलोing a new container;
 *	- attaching group(s) to it;
 *	- setting an IOMMU driver क्रम a container.
 * When IOMMU is set क्रम a container, all groups in it are
 * considered पढ़ोy to use by an बाह्यal user.
 *
 * 2. User space passes a group fd to an बाह्यal user.
 * The बाह्यal user calls vfio_group_get_बाह्यal_user()
 * to verअगरy that:
 *	- the group is initialized;
 *	- IOMMU is set क्रम it.
 * If both checks passed, vfio_group_get_बाह्यal_user()
 * increments the container user counter to prevent
 * the VFIO group from disposal beक्रमe KVM निकासs.
 *
 * 3. The बाह्यal user calls vfio_बाह्यal_user_iommu_id()
 * to know an IOMMU ID.
 *
 * 4. When the बाह्यal KVM finishes, it calls
 * vfio_group_put_बाह्यal_user() to release the VFIO group.
 * This call decrements the container user counter.
 */
काष्ठा vfio_group *vfio_group_get_बाह्यal_user(काष्ठा file *filep)
अणु
	काष्ठा vfio_group *group = filep->निजी_data;
	पूर्णांक ret;

	अगर (filep->f_op != &vfio_group_fops)
		वापस ERR_PTR(-EINVAL);

	ret = vfio_group_add_container_user(group);
	अगर (ret)
		वापस ERR_PTR(ret);

	vfio_group_get(group);

	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_group_get_बाह्यal_user);

/**
 * External user API, exported by symbols to be linked dynamically.
 * The बाह्यal user passes in a device poपूर्णांकer
 * to verअगरy that:
 *	- A VFIO group is assiciated with the device;
 *	- IOMMU is set क्रम the group.
 * If both checks passed, vfio_group_get_बाह्यal_user_from_dev()
 * increments the container user counter to prevent the VFIO group
 * from disposal beक्रमe बाह्यal user निकासs and वापसs the poपूर्णांकer
 * to the VFIO group.
 *
 * When the बाह्यal user finishes using the VFIO group, it calls
 * vfio_group_put_बाह्यal_user() to release the VFIO group and
 * decrement the container user counter.
 *
 * @dev [in]	: device
 * Return error PTR or poपूर्णांकer to VFIO group.
 */

काष्ठा vfio_group *vfio_group_get_बाह्यal_user_from_dev(काष्ठा device *dev)
अणु
	काष्ठा vfio_group *group;
	पूर्णांक ret;

	group = vfio_group_get_from_dev(dev);
	अगर (!group)
		वापस ERR_PTR(-ENODEV);

	ret = vfio_group_add_container_user(group);
	अगर (ret) अणु
		vfio_group_put(group);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_group_get_बाह्यal_user_from_dev);

व्योम vfio_group_put_बाह्यal_user(काष्ठा vfio_group *group)
अणु
	vfio_group_try_dissolve_container(group);
	vfio_group_put(group);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_group_put_बाह्यal_user);

bool vfio_बाह्यal_group_match_file(काष्ठा vfio_group *test_group,
				    काष्ठा file *filep)
अणु
	काष्ठा vfio_group *group = filep->निजी_data;

	वापस (filep->f_op == &vfio_group_fops) && (group == test_group);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_बाह्यal_group_match_file);

पूर्णांक vfio_बाह्यal_user_iommu_id(काष्ठा vfio_group *group)
अणु
	वापस iommu_group_id(group->iommu_group);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_बाह्यal_user_iommu_id);

दीर्घ vfio_बाह्यal_check_extension(काष्ठा vfio_group *group, अचिन्हित दीर्घ arg)
अणु
	वापस vfio_ioctl_check_extension(group->container, arg);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_बाह्यal_check_extension);

/**
 * Sub-module support
 */
/*
 * Helper क्रम managing a buffer of info chain capabilities, allocate or
 * पुनः_स्मृतिate a buffer with additional @size, filling in @id and @version
 * of the capability.  A poपूर्णांकer to the new capability is वापसed.
 *
 * NB. The chain is based at the head of the buffer, so new entries are
 * added to the tail, vfio_info_cap_shअगरt() should be called to fixup the
 * next offsets prior to copying to the user buffer.
 */
काष्ठा vfio_info_cap_header *vfio_info_cap_add(काष्ठा vfio_info_cap *caps,
					       माप_प्रकार size, u16 id, u16 version)
अणु
	व्योम *buf;
	काष्ठा vfio_info_cap_header *header, *पंचांगp;

	buf = kपुनः_स्मृति(caps->buf, caps->size + size, GFP_KERNEL);
	अगर (!buf) अणु
		kमुक्त(caps->buf);
		caps->size = 0;
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	caps->buf = buf;
	header = buf + caps->size;

	/* Eventually copied to user buffer, zero */
	स_रखो(header, 0, size);

	header->id = id;
	header->version = version;

	/* Add to the end of the capability chain */
	क्रम (पंचांगp = buf; पंचांगp->next; पंचांगp = buf + पंचांगp->next)
		; /* nothing */

	पंचांगp->next = caps->size;
	caps->size += size;

	वापस header;
पूर्ण
EXPORT_SYMBOL_GPL(vfio_info_cap_add);

व्योम vfio_info_cap_shअगरt(काष्ठा vfio_info_cap *caps, माप_प्रकार offset)
अणु
	काष्ठा vfio_info_cap_header *पंचांगp;
	व्योम *buf = (व्योम *)caps->buf;

	क्रम (पंचांगp = buf; पंचांगp->next; पंचांगp = buf + पंचांगp->next - offset)
		पंचांगp->next += offset;
पूर्ण
EXPORT_SYMBOL(vfio_info_cap_shअगरt);

पूर्णांक vfio_info_add_capability(काष्ठा vfio_info_cap *caps,
			     काष्ठा vfio_info_cap_header *cap, माप_प्रकार size)
अणु
	काष्ठा vfio_info_cap_header *header;

	header = vfio_info_cap_add(caps, size, cap->id, cap->version);
	अगर (IS_ERR(header))
		वापस PTR_ERR(header);

	स_नकल(header + 1, cap + 1, size - माप(*header));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vfio_info_add_capability);

पूर्णांक vfio_set_irqs_validate_and_prepare(काष्ठा vfio_irq_set *hdr, पूर्णांक num_irqs,
				       पूर्णांक max_irq_type, माप_प्रकार *data_size)
अणु
	अचिन्हित दीर्घ minsz;
	माप_प्रकार size;

	minsz = दुरत्वend(काष्ठा vfio_irq_set, count);

	अगर ((hdr->argsz < minsz) || (hdr->index >= max_irq_type) ||
	    (hdr->count >= (U32_MAX - hdr->start)) ||
	    (hdr->flags & ~(VFIO_IRQ_SET_DATA_TYPE_MASK |
				VFIO_IRQ_SET_ACTION_TYPE_MASK)))
		वापस -EINVAL;

	अगर (data_size)
		*data_size = 0;

	अगर (hdr->start >= num_irqs || hdr->start + hdr->count > num_irqs)
		वापस -EINVAL;

	चयन (hdr->flags & VFIO_IRQ_SET_DATA_TYPE_MASK) अणु
	हाल VFIO_IRQ_SET_DATA_NONE:
		size = 0;
		अवरोध;
	हाल VFIO_IRQ_SET_DATA_BOOL:
		size = माप(uपूर्णांक8_t);
		अवरोध;
	हाल VFIO_IRQ_SET_DATA_EVENTFD:
		size = माप(पूर्णांक32_t);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (size) अणु
		अगर (hdr->argsz - minsz < hdr->count * size)
			वापस -EINVAL;

		अगर (!data_size)
			वापस -EINVAL;

		*data_size = hdr->count * size;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vfio_set_irqs_validate_and_prepare);

/*
 * Pin a set of guest PFNs and वापस their associated host PFNs क्रम local
 * करोमुख्य only.
 * @dev [in]     : device
 * @user_pfn [in]: array of user/guest PFNs to be pinned.
 * @npage [in]   : count of elements in user_pfn array.  This count should not
 *		   be greater VFIO_PIN_PAGES_MAX_ENTRIES.
 * @prot [in]    : protection flags
 * @phys_pfn[out]: array of host PFNs
 * Return error or number of pages pinned.
 */
पूर्णांक vfio_pin_pages(काष्ठा device *dev, अचिन्हित दीर्घ *user_pfn, पूर्णांक npage,
		   पूर्णांक prot, अचिन्हित दीर्घ *phys_pfn)
अणु
	काष्ठा vfio_container *container;
	काष्ठा vfio_group *group;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret;

	अगर (!dev || !user_pfn || !phys_pfn || !npage)
		वापस -EINVAL;

	अगर (npage > VFIO_PIN_PAGES_MAX_ENTRIES)
		वापस -E2BIG;

	group = vfio_group_get_from_dev(dev);
	अगर (!group)
		वापस -ENODEV;

	अगर (group->dev_counter > 1) अणु
		ret = -EINVAL;
		जाओ err_pin_pages;
	पूर्ण

	ret = vfio_group_add_container_user(group);
	अगर (ret)
		जाओ err_pin_pages;

	container = group->container;
	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->pin_pages))
		ret = driver->ops->pin_pages(container->iommu_data,
					     group->iommu_group, user_pfn,
					     npage, prot, phys_pfn);
	अन्यथा
		ret = -ENOTTY;

	vfio_group_try_dissolve_container(group);

err_pin_pages:
	vfio_group_put(group);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfio_pin_pages);

/*
 * Unpin set of host PFNs क्रम local करोमुख्य only.
 * @dev [in]     : device
 * @user_pfn [in]: array of user/guest PFNs to be unpinned. Number of user/guest
 *		   PFNs should not be greater than VFIO_PIN_PAGES_MAX_ENTRIES.
 * @npage [in]   : count of elements in user_pfn array.  This count should not
 *                 be greater than VFIO_PIN_PAGES_MAX_ENTRIES.
 * Return error or number of pages unpinned.
 */
पूर्णांक vfio_unpin_pages(काष्ठा device *dev, अचिन्हित दीर्घ *user_pfn, पूर्णांक npage)
अणु
	काष्ठा vfio_container *container;
	काष्ठा vfio_group *group;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret;

	अगर (!dev || !user_pfn || !npage)
		वापस -EINVAL;

	अगर (npage > VFIO_PIN_PAGES_MAX_ENTRIES)
		वापस -E2BIG;

	group = vfio_group_get_from_dev(dev);
	अगर (!group)
		वापस -ENODEV;

	ret = vfio_group_add_container_user(group);
	अगर (ret)
		जाओ err_unpin_pages;

	container = group->container;
	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->unpin_pages))
		ret = driver->ops->unpin_pages(container->iommu_data, user_pfn,
					       npage);
	अन्यथा
		ret = -ENOTTY;

	vfio_group_try_dissolve_container(group);

err_unpin_pages:
	vfio_group_put(group);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfio_unpin_pages);

/*
 * Pin a set of guest IOVA PFNs and वापस their associated host PFNs क्रम a
 * VFIO group.
 *
 * The caller needs to call vfio_group_get_बाह्यal_user() or
 * vfio_group_get_बाह्यal_user_from_dev() prior to calling this पूर्णांकerface,
 * so as to prevent the VFIO group from disposal in the middle of the call.
 * But it can keep the reference to the VFIO group क्रम several calls पूर्णांकo
 * this पूर्णांकerface.
 * After finishing using of the VFIO group, the caller needs to release the
 * VFIO group by calling vfio_group_put_बाह्यal_user().
 *
 * @group [in]		: VFIO group
 * @user_iova_pfn [in]	: array of user/guest IOVA PFNs to be pinned.
 * @npage [in]		: count of elements in user_iova_pfn array.
 *			  This count should not be greater
 *			  VFIO_PIN_PAGES_MAX_ENTRIES.
 * @prot [in]		: protection flags
 * @phys_pfn [out]	: array of host PFNs
 * Return error or number of pages pinned.
 */
पूर्णांक vfio_group_pin_pages(काष्ठा vfio_group *group,
			 अचिन्हित दीर्घ *user_iova_pfn, पूर्णांक npage,
			 पूर्णांक prot, अचिन्हित दीर्घ *phys_pfn)
अणु
	काष्ठा vfio_container *container;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret;

	अगर (!group || !user_iova_pfn || !phys_pfn || !npage)
		वापस -EINVAL;

	अगर (group->dev_counter > 1)
		वापस -EINVAL;

	अगर (npage > VFIO_PIN_PAGES_MAX_ENTRIES)
		वापस -E2BIG;

	container = group->container;
	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->pin_pages))
		ret = driver->ops->pin_pages(container->iommu_data,
					     group->iommu_group, user_iova_pfn,
					     npage, prot, phys_pfn);
	अन्यथा
		ret = -ENOTTY;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfio_group_pin_pages);

/*
 * Unpin a set of guest IOVA PFNs क्रम a VFIO group.
 *
 * The caller needs to call vfio_group_get_बाह्यal_user() or
 * vfio_group_get_बाह्यal_user_from_dev() prior to calling this पूर्णांकerface,
 * so as to prevent the VFIO group from disposal in the middle of the call.
 * But it can keep the reference to the VFIO group क्रम several calls पूर्णांकo
 * this पूर्णांकerface.
 * After finishing using of the VFIO group, the caller needs to release the
 * VFIO group by calling vfio_group_put_बाह्यal_user().
 *
 * @group [in]		: vfio group
 * @user_iova_pfn [in]	: array of user/guest IOVA PFNs to be unpinned.
 * @npage [in]		: count of elements in user_iova_pfn array.
 *			  This count should not be greater than
 *			  VFIO_PIN_PAGES_MAX_ENTRIES.
 * Return error or number of pages unpinned.
 */
पूर्णांक vfio_group_unpin_pages(काष्ठा vfio_group *group,
			   अचिन्हित दीर्घ *user_iova_pfn, पूर्णांक npage)
अणु
	काष्ठा vfio_container *container;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret;

	अगर (!group || !user_iova_pfn || !npage)
		वापस -EINVAL;

	अगर (npage > VFIO_PIN_PAGES_MAX_ENTRIES)
		वापस -E2BIG;

	container = group->container;
	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->unpin_pages))
		ret = driver->ops->unpin_pages(container->iommu_data,
					       user_iova_pfn, npage);
	अन्यथा
		ret = -ENOTTY;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfio_group_unpin_pages);


/*
 * This पूर्णांकerface allows the CPUs to perक्रमm some sort of भव DMA on
 * behalf of the device.
 *
 * CPUs पढ़ो/ग_लिखो from/पूर्णांकo a range of IOVAs poपूर्णांकing to user space memory
 * पूर्णांकo/from a kernel buffer.
 *
 * As the पढ़ो/ग_लिखो of user space memory is conducted via the CPUs and is
 * not a real device DMA, it is not necessary to pin the user space memory.
 *
 * The caller needs to call vfio_group_get_बाह्यal_user() or
 * vfio_group_get_बाह्यal_user_from_dev() prior to calling this पूर्णांकerface,
 * so as to prevent the VFIO group from disposal in the middle of the call.
 * But it can keep the reference to the VFIO group क्रम several calls पूर्णांकo
 * this पूर्णांकerface.
 * After finishing using of the VFIO group, the caller needs to release the
 * VFIO group by calling vfio_group_put_बाह्यal_user().
 *
 * @group [in]		: VFIO group
 * @user_iova [in]	: base IOVA of a user space buffer
 * @data [in]		: poपूर्णांकer to kernel buffer
 * @len [in]		: kernel buffer length
 * @ग_लिखो		: indicate पढ़ो or ग_लिखो
 * Return error code on failure or 0 on success.
 */
पूर्णांक vfio_dma_rw(काष्ठा vfio_group *group, dma_addr_t user_iova,
		व्योम *data, माप_प्रकार len, bool ग_लिखो)
अणु
	काष्ठा vfio_container *container;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret = 0;

	अगर (!group || !data || len <= 0)
		वापस -EINVAL;

	container = group->container;
	driver = container->iommu_driver;

	अगर (likely(driver && driver->ops->dma_rw))
		ret = driver->ops->dma_rw(container->iommu_data,
					  user_iova, data, len, ग_लिखो);
	अन्यथा
		ret = -ENOTTY;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfio_dma_rw);

अटल पूर्णांक vfio_रेजिस्टर_iommu_notअगरier(काष्ठा vfio_group *group,
					अचिन्हित दीर्घ *events,
					काष्ठा notअगरier_block *nb)
अणु
	काष्ठा vfio_container *container;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret;

	ret = vfio_group_add_container_user(group);
	अगर (ret)
		वापस -EINVAL;

	container = group->container;
	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->रेजिस्टर_notअगरier))
		ret = driver->ops->रेजिस्टर_notअगरier(container->iommu_data,
						     events, nb);
	अन्यथा
		ret = -ENOTTY;

	vfio_group_try_dissolve_container(group);

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_unरेजिस्टर_iommu_notअगरier(काष्ठा vfio_group *group,
					  काष्ठा notअगरier_block *nb)
अणु
	काष्ठा vfio_container *container;
	काष्ठा vfio_iommu_driver *driver;
	पूर्णांक ret;

	ret = vfio_group_add_container_user(group);
	अगर (ret)
		वापस -EINVAL;

	container = group->container;
	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->unरेजिस्टर_notअगरier))
		ret = driver->ops->unरेजिस्टर_notअगरier(container->iommu_data,
						       nb);
	अन्यथा
		ret = -ENOTTY;

	vfio_group_try_dissolve_container(group);

	वापस ret;
पूर्ण

व्योम vfio_group_set_kvm(काष्ठा vfio_group *group, काष्ठा kvm *kvm)
अणु
	group->kvm = kvm;
	blocking_notअगरier_call_chain(&group->notअगरier,
				VFIO_GROUP_NOTIFY_SET_KVM, kvm);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_group_set_kvm);

अटल पूर्णांक vfio_रेजिस्टर_group_notअगरier(काष्ठा vfio_group *group,
					अचिन्हित दीर्घ *events,
					काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret;
	bool set_kvm = false;

	अगर (*events & VFIO_GROUP_NOTIFY_SET_KVM)
		set_kvm = true;

	/* clear known events */
	*events &= ~VFIO_GROUP_NOTIFY_SET_KVM;

	/* refuse to जारी अगर still events reमुख्यing */
	अगर (*events)
		वापस -EINVAL;

	ret = vfio_group_add_container_user(group);
	अगर (ret)
		वापस -EINVAL;

	ret = blocking_notअगरier_chain_रेजिस्टर(&group->notअगरier, nb);

	/*
	 * The attaching of kvm and vfio_group might alपढ़ोy happen, so
	 * here we replay once upon registration.
	 */
	अगर (!ret && set_kvm && group->kvm)
		blocking_notअगरier_call_chain(&group->notअगरier,
					VFIO_GROUP_NOTIFY_SET_KVM, group->kvm);

	vfio_group_try_dissolve_container(group);

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_unरेजिस्टर_group_notअगरier(काष्ठा vfio_group *group,
					 काष्ठा notअगरier_block *nb)
अणु
	पूर्णांक ret;

	ret = vfio_group_add_container_user(group);
	अगर (ret)
		वापस -EINVAL;

	ret = blocking_notअगरier_chain_unरेजिस्टर(&group->notअगरier, nb);

	vfio_group_try_dissolve_container(group);

	वापस ret;
पूर्ण

पूर्णांक vfio_रेजिस्टर_notअगरier(काष्ठा device *dev, क्रमागत vfio_notअगरy_type type,
			   अचिन्हित दीर्घ *events, काष्ठा notअगरier_block *nb)
अणु
	काष्ठा vfio_group *group;
	पूर्णांक ret;

	अगर (!dev || !nb || !events || (*events == 0))
		वापस -EINVAL;

	group = vfio_group_get_from_dev(dev);
	अगर (!group)
		वापस -ENODEV;

	चयन (type) अणु
	हाल VFIO_IOMMU_NOTIFY:
		ret = vfio_रेजिस्टर_iommu_notअगरier(group, events, nb);
		अवरोध;
	हाल VFIO_GROUP_NOTIFY:
		ret = vfio_रेजिस्टर_group_notअगरier(group, events, nb);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	vfio_group_put(group);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfio_रेजिस्टर_notअगरier);

पूर्णांक vfio_unरेजिस्टर_notअगरier(काष्ठा device *dev, क्रमागत vfio_notअगरy_type type,
			     काष्ठा notअगरier_block *nb)
अणु
	काष्ठा vfio_group *group;
	पूर्णांक ret;

	अगर (!dev || !nb)
		वापस -EINVAL;

	group = vfio_group_get_from_dev(dev);
	अगर (!group)
		वापस -ENODEV;

	चयन (type) अणु
	हाल VFIO_IOMMU_NOTIFY:
		ret = vfio_unरेजिस्टर_iommu_notअगरier(group, nb);
		अवरोध;
	हाल VFIO_GROUP_NOTIFY:
		ret = vfio_unरेजिस्टर_group_notअगरier(group, nb);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	vfio_group_put(group);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfio_unरेजिस्टर_notअगरier);

काष्ठा iommu_करोमुख्य *vfio_group_iommu_करोमुख्य(काष्ठा vfio_group *group)
अणु
	काष्ठा vfio_container *container;
	काष्ठा vfio_iommu_driver *driver;

	अगर (!group)
		वापस ERR_PTR(-EINVAL);

	container = group->container;
	driver = container->iommu_driver;
	अगर (likely(driver && driver->ops->group_iommu_करोमुख्य))
		वापस driver->ops->group_iommu_करोमुख्य(container->iommu_data,
						       group->iommu_group);

	वापस ERR_PTR(-ENOTTY);
पूर्ण
EXPORT_SYMBOL_GPL(vfio_group_iommu_करोमुख्य);

/**
 * Module/class support
 */
अटल अक्षर *vfio_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "vfio/%s", dev_name(dev));
पूर्ण

अटल काष्ठा miscdevice vfio_dev = अणु
	.minor = VFIO_MINOR,
	.name = "vfio",
	.fops = &vfio_fops,
	.nodename = "vfio/vfio",
	.mode = S_IRUGO | S_IWUGO,
पूर्ण;

अटल पूर्णांक __init vfio_init(व्योम)
अणु
	पूर्णांक ret;

	idr_init(&vfio.group_idr);
	mutex_init(&vfio.group_lock);
	mutex_init(&vfio.iommu_drivers_lock);
	INIT_LIST_HEAD(&vfio.group_list);
	INIT_LIST_HEAD(&vfio.iommu_drivers_list);

	ret = misc_रेजिस्टर(&vfio_dev);
	अगर (ret) अणु
		pr_err("vfio: misc device register failed\n");
		वापस ret;
	पूर्ण

	/* /dev/vfio/$GROUP */
	vfio.class = class_create(THIS_MODULE, "vfio");
	अगर (IS_ERR(vfio.class)) अणु
		ret = PTR_ERR(vfio.class);
		जाओ err_class;
	पूर्ण

	vfio.class->devnode = vfio_devnode;

	ret = alloc_chrdev_region(&vfio.group_devt, 0, MINORMASK + 1, "vfio");
	अगर (ret)
		जाओ err_alloc_chrdev;

	cdev_init(&vfio.group_cdev, &vfio_group_fops);
	ret = cdev_add(&vfio.group_cdev, vfio.group_devt, MINORMASK + 1);
	अगर (ret)
		जाओ err_cdev_add;

	pr_info(DRIVER_DESC " version: " DRIVER_VERSION "\n");

#अगर_घोषित CONFIG_VFIO_NOIOMMU
	vfio_रेजिस्टर_iommu_driver(&vfio_noiommu_ops);
#पूर्ण_अगर
	वापस 0;

err_cdev_add:
	unरेजिस्टर_chrdev_region(vfio.group_devt, MINORMASK + 1);
err_alloc_chrdev:
	class_destroy(vfio.class);
	vfio.class = शून्य;
err_class:
	misc_deरेजिस्टर(&vfio_dev);
	वापस ret;
पूर्ण

अटल व्योम __निकास vfio_cleanup(व्योम)
अणु
	WARN_ON(!list_empty(&vfio.group_list));

#अगर_घोषित CONFIG_VFIO_NOIOMMU
	vfio_unरेजिस्टर_iommu_driver(&vfio_noiommu_ops);
#पूर्ण_अगर
	idr_destroy(&vfio.group_idr);
	cdev_del(&vfio.group_cdev);
	unरेजिस्टर_chrdev_region(vfio.group_devt, MINORMASK + 1);
	class_destroy(vfio.class);
	vfio.class = शून्य;
	misc_deरेजिस्टर(&vfio_dev);
पूर्ण

module_init(vfio_init);
module_निकास(vfio_cleanup);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_ALIAS_MISCDEV(VFIO_MINOR);
MODULE_ALIAS("devname:vfio/vfio");
MODULE_SOFTDEP("post: vfio_iommu_type1 vfio_iommu_spapr_tce");
