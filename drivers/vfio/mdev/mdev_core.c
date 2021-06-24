<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Mediated device Core Driver
 *
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *     Author: Neo Jia <cjia@nvidia.com>
 *             Kirti Wankhede <kwankhede@nvidia.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/mdev.h>

#समावेश "mdev_private.h"

#घोषणा DRIVER_VERSION		"0.1"
#घोषणा DRIVER_AUTHOR		"NVIDIA Corporation"
#घोषणा DRIVER_DESC		"Mediated device Core Driver"

अटल LIST_HEAD(parent_list);
अटल DEFINE_MUTEX(parent_list_lock);
अटल काष्ठा class_compat *mdev_bus_compat_class;

अटल LIST_HEAD(mdev_list);
अटल DEFINE_MUTEX(mdev_list_lock);

काष्ठा device *mdev_parent_dev(काष्ठा mdev_device *mdev)
अणु
	वापस mdev->type->parent->dev;
पूर्ण
EXPORT_SYMBOL(mdev_parent_dev);

/*
 * Return the index in supported_type_groups that this mdev_device was created
 * from.
 */
अचिन्हित पूर्णांक mdev_get_type_group_id(काष्ठा mdev_device *mdev)
अणु
	वापस mdev->type->type_group_id;
पूर्ण
EXPORT_SYMBOL(mdev_get_type_group_id);

/*
 * Used in mdev_type_attribute sysfs functions to वापस the index in the
 * supported_type_groups that the sysfs is called from.
 */
अचिन्हित पूर्णांक mtype_get_type_group_id(काष्ठा mdev_type *mtype)
अणु
	वापस mtype->type_group_id;
पूर्ण
EXPORT_SYMBOL(mtype_get_type_group_id);

/*
 * Used in mdev_type_attribute sysfs functions to वापस the parent काष्ठा
 * device
 */
काष्ठा device *mtype_get_parent_dev(काष्ठा mdev_type *mtype)
अणु
	वापस mtype->parent->dev;
पूर्ण
EXPORT_SYMBOL(mtype_get_parent_dev);

/* Should be called holding parent_list_lock */
अटल काष्ठा mdev_parent *__find_parent_device(काष्ठा device *dev)
अणु
	काष्ठा mdev_parent *parent;

	list_क्रम_each_entry(parent, &parent_list, next) अणु
		अगर (parent->dev == dev)
			वापस parent;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम mdev_release_parent(काष्ठा kref *kref)
अणु
	काष्ठा mdev_parent *parent = container_of(kref, काष्ठा mdev_parent,
						  ref);
	काष्ठा device *dev = parent->dev;

	kमुक्त(parent);
	put_device(dev);
पूर्ण

/* Caller must hold parent unreg_sem पढ़ो or ग_लिखो lock */
अटल व्योम mdev_device_हटाओ_common(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_parent *parent = mdev->type->parent;
	पूर्णांक ret;

	mdev_हटाओ_sysfs_files(mdev);
	device_del(&mdev->dev);
	lockdep_निश्चित_held(&parent->unreg_sem);
	ret = parent->ops->हटाओ(mdev);
	अगर (ret)
		dev_err(&mdev->dev, "Remove failed: err=%d\n", ret);

	/* Balances with device_initialize() */
	put_device(&mdev->dev);
पूर्ण

अटल पूर्णांक mdev_device_हटाओ_cb(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mdev_device *mdev = mdev_from_dev(dev);

	अगर (mdev)
		mdev_device_हटाओ_common(mdev);
	वापस 0;
पूर्ण

/*
 * mdev_रेजिस्टर_device : Register a device
 * @dev: device काष्ठाure representing parent device.
 * @ops: Parent device operation काष्ठाure to be रेजिस्टरed.
 *
 * Add device to list of रेजिस्टरed parent devices.
 * Returns a negative value on error, otherwise 0.
 */
पूर्णांक mdev_रेजिस्टर_device(काष्ठा device *dev, स्थिर काष्ठा mdev_parent_ops *ops)
अणु
	पूर्णांक ret;
	काष्ठा mdev_parent *parent;
	अक्षर *env_string = "MDEV_STATE=registered";
	अक्षर *envp[] = अणु env_string, शून्य पूर्ण;

	/* check क्रम mandatory ops */
	अगर (!ops || !ops->create || !ops->हटाओ || !ops->supported_type_groups)
		वापस -EINVAL;

	dev = get_device(dev);
	अगर (!dev)
		वापस -EINVAL;

	/* Not mandatory, but its असलence could be a problem */
	अगर (!ops->request)
		dev_info(dev, "Driver cannot be asked to release device\n");

	mutex_lock(&parent_list_lock);

	/* Check क्रम duplicate */
	parent = __find_parent_device(dev);
	अगर (parent) अणु
		parent = शून्य;
		ret = -EEXIST;
		जाओ add_dev_err;
	पूर्ण

	parent = kzalloc(माप(*parent), GFP_KERNEL);
	अगर (!parent) अणु
		ret = -ENOMEM;
		जाओ add_dev_err;
	पूर्ण

	kref_init(&parent->ref);
	init_rwsem(&parent->unreg_sem);

	parent->dev = dev;
	parent->ops = ops;

	अगर (!mdev_bus_compat_class) अणु
		mdev_bus_compat_class = class_compat_रेजिस्टर("mdev_bus");
		अगर (!mdev_bus_compat_class) अणु
			ret = -ENOMEM;
			जाओ add_dev_err;
		पूर्ण
	पूर्ण

	ret = parent_create_sysfs_files(parent);
	अगर (ret)
		जाओ add_dev_err;

	ret = class_compat_create_link(mdev_bus_compat_class, dev, शून्य);
	अगर (ret)
		dev_warn(dev, "Failed to create compatibility class link\n");

	list_add(&parent->next, &parent_list);
	mutex_unlock(&parent_list_lock);

	dev_info(dev, "MDEV: Registered\n");
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);

	वापस 0;

add_dev_err:
	mutex_unlock(&parent_list_lock);
	अगर (parent)
		mdev_put_parent(parent);
	अन्यथा
		put_device(dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mdev_रेजिस्टर_device);

/*
 * mdev_unरेजिस्टर_device : Unरेजिस्टर a parent device
 * @dev: device काष्ठाure representing parent device.
 *
 * Remove device from list of रेजिस्टरed parent devices. Give a chance to मुक्त
 * existing mediated devices क्रम given device.
 */

व्योम mdev_unरेजिस्टर_device(काष्ठा device *dev)
अणु
	काष्ठा mdev_parent *parent;
	अक्षर *env_string = "MDEV_STATE=unregistered";
	अक्षर *envp[] = अणु env_string, शून्य पूर्ण;

	mutex_lock(&parent_list_lock);
	parent = __find_parent_device(dev);

	अगर (!parent) अणु
		mutex_unlock(&parent_list_lock);
		वापस;
	पूर्ण
	dev_info(dev, "MDEV: Unregistering\n");

	list_del(&parent->next);
	mutex_unlock(&parent_list_lock);

	करोwn_ग_लिखो(&parent->unreg_sem);

	class_compat_हटाओ_link(mdev_bus_compat_class, dev, शून्य);

	device_क्रम_each_child(dev, शून्य, mdev_device_हटाओ_cb);

	parent_हटाओ_sysfs_files(parent);
	up_ग_लिखो(&parent->unreg_sem);

	mdev_put_parent(parent);

	/* We still have the caller's reference to use क्रम the uevent */
	kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
पूर्ण
EXPORT_SYMBOL(mdev_unरेजिस्टर_device);

अटल व्योम mdev_device_release(काष्ठा device *dev)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(dev);

	/* Pairs with the get in mdev_device_create() */
	kobject_put(&mdev->type->kobj);

	mutex_lock(&mdev_list_lock);
	list_del(&mdev->next);
	mutex_unlock(&mdev_list_lock);

	dev_dbg(&mdev->dev, "MDEV: destroying\n");
	kमुक्त(mdev);
पूर्ण

पूर्णांक mdev_device_create(काष्ठा mdev_type *type, स्थिर guid_t *uuid)
अणु
	पूर्णांक ret;
	काष्ठा mdev_device *mdev, *पंचांगp;
	काष्ठा mdev_parent *parent = type->parent;

	mutex_lock(&mdev_list_lock);

	/* Check क्रम duplicate */
	list_क्रम_each_entry(पंचांगp, &mdev_list, next) अणु
		अगर (guid_equal(&पंचांगp->uuid, uuid)) अणु
			mutex_unlock(&mdev_list_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	mdev = kzalloc(माप(*mdev), GFP_KERNEL);
	अगर (!mdev) अणु
		mutex_unlock(&mdev_list_lock);
		वापस -ENOMEM;
	पूर्ण

	device_initialize(&mdev->dev);
	mdev->dev.parent  = parent->dev;
	mdev->dev.bus = &mdev_bus_type;
	mdev->dev.release = mdev_device_release;
	mdev->dev.groups = parent->ops->mdev_attr_groups;
	mdev->type = type;
	/* Pairs with the put in mdev_device_release() */
	kobject_get(&type->kobj);

	guid_copy(&mdev->uuid, uuid);
	list_add(&mdev->next, &mdev_list);
	mutex_unlock(&mdev_list_lock);

	ret = dev_set_name(&mdev->dev, "%pUl", uuid);
	अगर (ret)
		जाओ out_put_device;

	/* Check अगर parent unregistration has started */
	अगर (!करोwn_पढ़ो_trylock(&parent->unreg_sem)) अणु
		ret = -ENODEV;
		जाओ out_put_device;
	पूर्ण

	ret = parent->ops->create(mdev);
	अगर (ret)
		जाओ out_unlock;

	ret = device_add(&mdev->dev);
	अगर (ret)
		जाओ out_हटाओ;

	ret = mdev_create_sysfs_files(mdev);
	अगर (ret)
		जाओ out_del;

	mdev->active = true;
	dev_dbg(&mdev->dev, "MDEV: created\n");
	up_पढ़ो(&parent->unreg_sem);

	वापस 0;

out_del:
	device_del(&mdev->dev);
out_हटाओ:
	parent->ops->हटाओ(mdev);
out_unlock:
	up_पढ़ो(&parent->unreg_sem);
out_put_device:
	put_device(&mdev->dev);
	वापस ret;
पूर्ण

पूर्णांक mdev_device_हटाओ(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_device *पंचांगp;
	काष्ठा mdev_parent *parent = mdev->type->parent;

	mutex_lock(&mdev_list_lock);
	list_क्रम_each_entry(पंचांगp, &mdev_list, next) अणु
		अगर (पंचांगp == mdev)
			अवरोध;
	पूर्ण

	अगर (पंचांगp != mdev) अणु
		mutex_unlock(&mdev_list_lock);
		वापस -ENODEV;
	पूर्ण

	अगर (!mdev->active) अणु
		mutex_unlock(&mdev_list_lock);
		वापस -EAGAIN;
	पूर्ण

	mdev->active = false;
	mutex_unlock(&mdev_list_lock);

	/* Check अगर parent unregistration has started */
	अगर (!करोwn_पढ़ो_trylock(&parent->unreg_sem))
		वापस -ENODEV;

	mdev_device_हटाओ_common(mdev);
	up_पढ़ो(&parent->unreg_sem);
	वापस 0;
पूर्ण

अटल पूर्णांक __init mdev_init(व्योम)
अणु
	वापस mdev_bus_रेजिस्टर();
पूर्ण

अटल व्योम __निकास mdev_निकास(व्योम)
अणु
	अगर (mdev_bus_compat_class)
		class_compat_unरेजिस्टर(mdev_bus_compat_class);

	mdev_bus_unरेजिस्टर();
पूर्ण

module_init(mdev_init)
module_निकास(mdev_निकास)

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SOFTDEP("post: vfio_mdev");
