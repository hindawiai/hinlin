<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * media-dev-allocator.c - Media Controller Device Allocator API
 *
 * Copyright (c) 2019 Shuah Khan <shuah@kernel.org>
 *
 * Credits: Suggested by Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

/*
 * This file adds a global refcounted Media Controller Device Instance API.
 * A प्रणाली wide global media device list is managed and each media device
 * includes a kref count. The last put on the media device releases the media
 * device instance.
 *
 */

#समावेश <linux/kref.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <media/media-device.h>
#समावेश <media/media-dev-allocator.h>

अटल LIST_HEAD(media_device_list);
अटल DEFINE_MUTEX(media_device_lock);

काष्ठा media_device_instance अणु
	काष्ठा media_device mdev;
	काष्ठा module *owner;
	काष्ठा list_head list;
	काष्ठा kref refcount;
पूर्ण;

अटल अंतरभूत काष्ठा media_device_instance *
to_media_device_instance(काष्ठा media_device *mdev)
अणु
	वापस container_of(mdev, काष्ठा media_device_instance, mdev);
पूर्ण

अटल व्योम media_device_instance_release(काष्ठा kref *kref)
अणु
	काष्ठा media_device_instance *mdi =
		container_of(kref, काष्ठा media_device_instance, refcount);

	dev_dbg(mdi->mdev.dev, "%s: releasing Media Device\n", __func__);

	mutex_lock(&media_device_lock);

	media_device_unरेजिस्टर(&mdi->mdev);
	media_device_cleanup(&mdi->mdev);

	list_del(&mdi->list);
	mutex_unlock(&media_device_lock);

	kमुक्त(mdi);
पूर्ण

/* Callers should hold media_device_lock when calling this function */
अटल काष्ठा media_device *__media_device_get(काष्ठा device *dev,
						स्थिर अक्षर *module_name,
						काष्ठा module *owner)
अणु
	काष्ठा media_device_instance *mdi;

	list_क्रम_each_entry(mdi, &media_device_list, list) अणु
		अगर (mdi->mdev.dev != dev)
			जारी;

		kref_get(&mdi->refcount);

		/* get module reference क्रम the media_device owner */
		अगर (owner != mdi->owner && !try_module_get(mdi->owner))
			dev_err(dev,
				"%s: module %s get owner reference error\n",
					__func__, module_name);
		अन्यथा
			dev_dbg(dev, "%s: module %s got owner reference\n",
					__func__, module_name);
		वापस &mdi->mdev;
	पूर्ण

	mdi = kzalloc(माप(*mdi), GFP_KERNEL);
	अगर (!mdi)
		वापस शून्य;

	mdi->owner = owner;
	kref_init(&mdi->refcount);
	list_add_tail(&mdi->list, &media_device_list);

	dev_dbg(dev, "%s: Allocated media device for owner %s\n",
			__func__, module_name);
	वापस &mdi->mdev;
पूर्ण

काष्ठा media_device *media_device_usb_allocate(काष्ठा usb_device *udev,
					       स्थिर अक्षर *module_name,
					       काष्ठा module *owner)
अणु
	काष्ठा media_device *mdev;

	mutex_lock(&media_device_lock);
	mdev = __media_device_get(&udev->dev, module_name, owner);
	अगर (!mdev) अणु
		mutex_unlock(&media_device_lock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* check अगर media device is alपढ़ोy initialized */
	अगर (!mdev->dev)
		__media_device_usb_init(mdev, udev, udev->product,
					module_name);
	mutex_unlock(&media_device_lock);
	वापस mdev;
पूर्ण
EXPORT_SYMBOL_GPL(media_device_usb_allocate);

व्योम media_device_delete(काष्ठा media_device *mdev, स्थिर अक्षर *module_name,
			 काष्ठा module *owner)
अणु
	काष्ठा media_device_instance *mdi = to_media_device_instance(mdev);

	mutex_lock(&media_device_lock);
	/* put module reference क्रम the media_device owner */
	अगर (mdi->owner != owner) अणु
		module_put(mdi->owner);
		dev_dbg(mdi->mdev.dev,
			"%s: module %s put owner module reference\n",
			__func__, module_name);
	पूर्ण
	mutex_unlock(&media_device_lock);
	kref_put(&mdi->refcount, media_device_instance_release);
पूर्ण
EXPORT_SYMBOL_GPL(media_device_delete);
