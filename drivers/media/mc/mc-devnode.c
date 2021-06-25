<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Media device node
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Based on drivers/media/video/v4l2_dev.c code authored by
 *	Mauro Carvalho Chehab <mchehab@kernel.org> (version 2)
 *	Alan Cox, <alan@lxorguk.ukuu.org.uk> (version 1)
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 *
 * --
 *
 * Generic media device node infraकाष्ठाure to रेजिस्टर and unरेजिस्टर
 * अक्षरacter devices using a dynamic major number and proper reference
 * counting.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#समावेश <media/media-devnode.h>
#समावेश <media/media-device.h>

#घोषणा MEDIA_NUM_DEVICES	256
#घोषणा MEDIA_NAME		"media"

अटल dev_t media_dev_t;

/*
 *	Active devices
 */
अटल DEFINE_MUTEX(media_devnode_lock);
अटल DECLARE_BITMAP(media_devnode_nums, MEDIA_NUM_DEVICES);

/* Called when the last user of the media device निकासs. */
अटल व्योम media_devnode_release(काष्ठा device *cd)
अणु
	काष्ठा media_devnode *devnode = to_media_devnode(cd);

	mutex_lock(&media_devnode_lock);
	/* Mark device node number as मुक्त */
	clear_bit(devnode->minor, media_devnode_nums);
	mutex_unlock(&media_devnode_lock);

	/* Release media_devnode and perक्रमm other cleanups as needed. */
	अगर (devnode->release)
		devnode->release(devnode);

	kमुक्त(devnode);
	pr_debug("%s: Media Devnode Deallocated\n", __func__);
पूर्ण

अटल काष्ठा bus_type media_bus_type = अणु
	.name = MEDIA_NAME,
पूर्ण;

अटल sमाप_प्रकार media_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
		माप_प्रकार sz, loff_t *off)
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);

	अगर (!devnode->fops->पढ़ो)
		वापस -EINVAL;
	अगर (!media_devnode_is_रेजिस्टरed(devnode))
		वापस -EIO;
	वापस devnode->fops->पढ़ो(filp, buf, sz, off);
पूर्ण

अटल sमाप_प्रकार media_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
		माप_प्रकार sz, loff_t *off)
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);

	अगर (!devnode->fops->ग_लिखो)
		वापस -EINVAL;
	अगर (!media_devnode_is_रेजिस्टरed(devnode))
		वापस -EIO;
	वापस devnode->fops->ग_लिखो(filp, buf, sz, off);
पूर्ण

अटल __poll_t media_poll(काष्ठा file *filp,
			       काष्ठा poll_table_काष्ठा *poll)
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);

	अगर (!media_devnode_is_रेजिस्टरed(devnode))
		वापस EPOLLERR | EPOLLHUP;
	अगर (!devnode->fops->poll)
		वापस DEFAULT_POLLMASK;
	वापस devnode->fops->poll(filp, poll);
पूर्ण

अटल दीर्घ
__media_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg,
	      दीर्घ (*ioctl_func)(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg))
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);

	अगर (!ioctl_func)
		वापस -ENOTTY;

	अगर (!media_devnode_is_रेजिस्टरed(devnode))
		वापस -EIO;

	वापस ioctl_func(filp, cmd, arg);
पूर्ण

अटल दीर्घ media_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);

	वापस __media_ioctl(filp, cmd, arg, devnode->fops->ioctl);
पूर्ण

#अगर_घोषित CONFIG_COMPAT

अटल दीर्घ media_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);

	वापस __media_ioctl(filp, cmd, arg, devnode->fops->compat_ioctl);
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */

/* Override क्रम the खोलो function */
अटल पूर्णांक media_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा media_devnode *devnode;
	पूर्णांक ret;

	/* Check अगर the media device is available. This needs to be करोne with
	 * the media_devnode_lock held to prevent an खोलो/unरेजिस्टर race:
	 * without the lock, the device could be unरेजिस्टरed and मुक्तd between
	 * the media_devnode_is_रेजिस्टरed() and get_device() calls, leading to
	 * a crash.
	 */
	mutex_lock(&media_devnode_lock);
	devnode = container_of(inode->i_cdev, काष्ठा media_devnode, cdev);
	/* वापस ENXIO अगर the media device has been हटाओd
	   alपढ़ोy or अगर it is not रेजिस्टरed anymore. */
	अगर (!media_devnode_is_रेजिस्टरed(devnode)) अणु
		mutex_unlock(&media_devnode_lock);
		वापस -ENXIO;
	पूर्ण
	/* and increase the device refcount */
	get_device(&devnode->dev);
	mutex_unlock(&media_devnode_lock);

	filp->निजी_data = devnode;

	अगर (devnode->fops->खोलो) अणु
		ret = devnode->fops->खोलो(filp);
		अगर (ret) अणु
			put_device(&devnode->dev);
			filp->निजी_data = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Override क्रम the release function */
अटल पूर्णांक media_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा media_devnode *devnode = media_devnode_data(filp);

	अगर (devnode->fops->release)
		devnode->fops->release(filp);

	filp->निजी_data = शून्य;

	/* decrease the refcount unconditionally since the release()
	   वापस value is ignored. */
	put_device(&devnode->dev);

	pr_debug("%s: Media Release\n", __func__);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations media_devnode_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = media_पढ़ो,
	.ग_लिखो = media_ग_लिखो,
	.खोलो = media_खोलो,
	.unlocked_ioctl = media_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = media_compat_ioctl,
#पूर्ण_अगर /* CONFIG_COMPAT */
	.release = media_release,
	.poll = media_poll,
	.llseek = no_llseek,
पूर्ण;

पूर्णांक __must_check media_devnode_रेजिस्टर(काष्ठा media_device *mdev,
					काष्ठा media_devnode *devnode,
					काष्ठा module *owner)
अणु
	पूर्णांक minor;
	पूर्णांक ret;

	/* Part 1: Find a मुक्त minor number */
	mutex_lock(&media_devnode_lock);
	minor = find_next_zero_bit(media_devnode_nums, MEDIA_NUM_DEVICES, 0);
	अगर (minor == MEDIA_NUM_DEVICES) अणु
		mutex_unlock(&media_devnode_lock);
		pr_err("could not get a free minor\n");
		kमुक्त(devnode);
		वापस -ENखाता;
	पूर्ण

	set_bit(minor, media_devnode_nums);
	mutex_unlock(&media_devnode_lock);

	devnode->minor = minor;
	devnode->media_dev = mdev;

	/* Part 1: Initialize dev now to use dev.kobj क्रम cdev.kobj.parent */
	devnode->dev.bus = &media_bus_type;
	devnode->dev.devt = MKDEV(MAJOR(media_dev_t), devnode->minor);
	devnode->dev.release = media_devnode_release;
	अगर (devnode->parent)
		devnode->dev.parent = devnode->parent;
	dev_set_name(&devnode->dev, "media%d", devnode->minor);
	device_initialize(&devnode->dev);

	/* Part 2: Initialize the अक्षरacter device */
	cdev_init(&devnode->cdev, &media_devnode_fops);
	devnode->cdev.owner = owner;
	kobject_set_name(&devnode->cdev.kobj, "media%d", devnode->minor);

	/* Part 3: Add the media and अक्षर device */
	ret = cdev_device_add(&devnode->cdev, &devnode->dev);
	अगर (ret < 0) अणु
		pr_err("%s: cdev_device_add failed\n", __func__);
		जाओ cdev_add_error;
	पूर्ण

	/* Part 4: Activate this minor. The अक्षर device can now be used. */
	set_bit(MEDIA_FLAG_REGISTERED, &devnode->flags);

	वापस 0;

cdev_add_error:
	mutex_lock(&media_devnode_lock);
	clear_bit(devnode->minor, media_devnode_nums);
	devnode->media_dev = शून्य;
	mutex_unlock(&media_devnode_lock);

	put_device(&devnode->dev);
	वापस ret;
पूर्ण

व्योम media_devnode_unरेजिस्टर_prepare(काष्ठा media_devnode *devnode)
अणु
	/* Check अगर devnode was ever रेजिस्टरed at all */
	अगर (!media_devnode_is_रेजिस्टरed(devnode))
		वापस;

	mutex_lock(&media_devnode_lock);
	clear_bit(MEDIA_FLAG_REGISTERED, &devnode->flags);
	mutex_unlock(&media_devnode_lock);
पूर्ण

व्योम media_devnode_unरेजिस्टर(काष्ठा media_devnode *devnode)
अणु
	mutex_lock(&media_devnode_lock);
	/* Delete the cdev on this minor as well */
	cdev_device_del(&devnode->cdev, &devnode->dev);
	devnode->media_dev = शून्य;
	mutex_unlock(&media_devnode_lock);

	put_device(&devnode->dev);
पूर्ण

/*
 *	Initialise media क्रम linux
 */
अटल पूर्णांक __init media_devnode_init(व्योम)
अणु
	पूर्णांक ret;

	pr_info("Linux media interface: v0.10\n");
	ret = alloc_chrdev_region(&media_dev_t, 0, MEDIA_NUM_DEVICES,
				  MEDIA_NAME);
	अगर (ret < 0) अणु
		pr_warn("unable to allocate major\n");
		वापस ret;
	पूर्ण

	ret = bus_रेजिस्टर(&media_bus_type);
	अगर (ret < 0) अणु
		unरेजिस्टर_chrdev_region(media_dev_t, MEDIA_NUM_DEVICES);
		pr_warn("bus_register failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास media_devnode_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&media_bus_type);
	unरेजिस्टर_chrdev_region(media_dev_t, MEDIA_NUM_DEVICES);
पूर्ण

subsys_initcall(media_devnode_init);
module_निकास(media_devnode_निकास)

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Device node registration for media drivers");
MODULE_LICENSE("GPL");
