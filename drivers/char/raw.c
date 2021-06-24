<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/अक्षर/raw.c
 *
 * Front-end raw अक्षरacter devices.  These can be bound to any block
 * devices to provide genuine Unix raw अक्षरacter device semantics.
 *
 * We reserve minor number 0 क्रम a control पूर्णांकerface.  ioctl()s on this
 * device are used to bind the other minor numbers to block devices.
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/major.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/module.h>
#समावेश <linux/raw.h>
#समावेश <linux/capability.h>
#समावेश <linux/uपन.स>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gfp.h>
#समावेश <linux/compat.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/uaccess.h>

काष्ठा raw_device_data अणु
	dev_t binding;
	काष्ठा block_device *bdev;
	पूर्णांक inuse;
पूर्ण;

अटल काष्ठा class *raw_class;
अटल काष्ठा raw_device_data *raw_devices;
अटल DEFINE_MUTEX(raw_mutex);
अटल स्थिर काष्ठा file_operations raw_ctl_fops; /* क्रमward declaration */

अटल पूर्णांक max_raw_minors = CONFIG_MAX_RAW_DEVS;

module_param(max_raw_minors, पूर्णांक, 0);
MODULE_PARM_DESC(max_raw_minors, "Maximum number of raw devices (1-65536)");

/*
 * Open/बंद code क्रम raw IO.
 *
 * We just reग_लिखो the i_mapping क्रम the /dev/raw/rawN file descriptor to
 * poपूर्णांक at the blockdev's address_space and set the file handle to use
 * O_सूचीECT.
 *
 * Set the device's soft blocksize to the minimum possible.  This gives the
 * finest possible alignment and has no adverse impact on perक्रमmance.
 */
अटल पूर्णांक raw_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	स्थिर पूर्णांक minor = iminor(inode);
	काष्ठा block_device *bdev;
	पूर्णांक err;

	अगर (minor == 0) अणु	/* It is the control device */
		filp->f_op = &raw_ctl_fops;
		वापस 0;
	पूर्ण

	pr_warn_ratelimited(
		"process %s (pid %d) is using the deprecated raw device\n"
		"support will be removed in Linux 5.14.\n",
		current->comm, current->pid);

	mutex_lock(&raw_mutex);

	/*
	 * All we need to करो on खोलो is check that the device is bound.
	 */
	err = -ENODEV;
	अगर (!raw_devices[minor].binding)
		जाओ out;
	bdev = blkdev_get_by_dev(raw_devices[minor].binding,
				 filp->f_mode | FMODE_EXCL, raw_खोलो);
	अगर (IS_ERR(bdev)) अणु
		err = PTR_ERR(bdev);
		जाओ out;
	पूर्ण
	err = set_blocksize(bdev, bdev_logical_block_size(bdev));
	अगर (err)
		जाओ out1;
	filp->f_flags |= O_सूचीECT;
	filp->f_mapping = bdev->bd_inode->i_mapping;
	अगर (++raw_devices[minor].inuse == 1)
		file_inode(filp)->i_mapping =
			bdev->bd_inode->i_mapping;
	filp->निजी_data = bdev;
	raw_devices[minor].bdev = bdev;
	mutex_unlock(&raw_mutex);
	वापस 0;

out1:
	blkdev_put(bdev, filp->f_mode | FMODE_EXCL);
out:
	mutex_unlock(&raw_mutex);
	वापस err;
पूर्ण

/*
 * When the final fd which refers to this अक्षरacter-special node is बंदd, we
 * make its ->mapping poपूर्णांक back at its own i_data.
 */
अटल पूर्णांक raw_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	स्थिर पूर्णांक minor= iminor(inode);
	काष्ठा block_device *bdev;

	mutex_lock(&raw_mutex);
	bdev = raw_devices[minor].bdev;
	अगर (--raw_devices[minor].inuse == 0)
		/* Here  inode->i_mapping == bdev->bd_inode->i_mapping  */
		inode->i_mapping = &inode->i_data;
	mutex_unlock(&raw_mutex);

	blkdev_put(bdev, filp->f_mode | FMODE_EXCL);
	वापस 0;
पूर्ण

/*
 * Forward ioctls to the underlying block device.
 */
अटल दीर्घ
raw_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक command, अचिन्हित दीर्घ arg)
अणु
	काष्ठा block_device *bdev = filp->निजी_data;
	वापस blkdev_ioctl(bdev, 0, command, arg);
पूर्ण

अटल पूर्णांक bind_set(पूर्णांक number, u64 major, u64 minor)
अणु
	dev_t dev = MKDEV(major, minor);
	dev_t raw = MKDEV(RAW_MAJOR, number);
	काष्ठा raw_device_data *rawdev;
	पूर्णांक err = 0;

	अगर (number <= 0 || number >= max_raw_minors)
		वापस -EINVAL;

	अगर (MAJOR(dev) != major || MINOR(dev) != minor)
		वापस -EINVAL;

	rawdev = &raw_devices[number];

	/*
	 * This is like making block devices, so demand the
	 * same capability
	 */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/*
	 * For now, we करोn't need to check that the underlying
	 * block device is present or not: we can करो that when
	 * the raw device is खोलोed.  Just check that the
	 * major/minor numbers make sense.
	 */

	अगर (MAJOR(dev) == 0 && dev != 0)
		वापस -EINVAL;

	mutex_lock(&raw_mutex);
	अगर (rawdev->inuse) अणु
		mutex_unlock(&raw_mutex);
		वापस -EBUSY;
	पूर्ण
	अगर (rawdev->binding)
		module_put(THIS_MODULE);

	rawdev->binding = dev;
	अगर (!dev) अणु
		/* unbind */
		device_destroy(raw_class, raw);
	पूर्ण अन्यथा अणु
		__module_get(THIS_MODULE);
		device_destroy(raw_class, raw);
		device_create(raw_class, शून्य, raw, शून्य, "raw%d", number);
	पूर्ण
	mutex_unlock(&raw_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक bind_get(पूर्णांक number, dev_t *dev)
अणु
	अगर (number <= 0 || number >= max_raw_minors)
		वापस -EINVAL;
	*dev = raw_devices[number].binding;
	वापस 0;
पूर्ण

/*
 * Deal with ioctls against the raw-device control पूर्णांकerface, to bind
 * and unbind other raw devices.
 */
अटल दीर्घ raw_ctl_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक command,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा raw_config_request rq;
	dev_t dev;
	पूर्णांक err;

	चयन (command) अणु
	हाल RAW_SETBIND:
		अगर (copy_from_user(&rq, (व्योम __user *) arg, माप(rq)))
			वापस -EFAULT;

		वापस bind_set(rq.raw_minor, rq.block_major, rq.block_minor);

	हाल RAW_GETBIND:
		अगर (copy_from_user(&rq, (व्योम __user *) arg, माप(rq)))
			वापस -EFAULT;

		err = bind_get(rq.raw_minor, &dev);
		अगर (err)
			वापस err;

		rq.block_major = MAJOR(dev);
		rq.block_minor = MINOR(dev);

		अगर (copy_to_user((व्योम __user *)arg, &rq, माप(rq)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा raw32_config_request अणु
	compat_पूर्णांक_t	raw_minor;
	compat_u64	block_major;
	compat_u64	block_minor;
पूर्ण;

अटल दीर्घ raw_ctl_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा raw32_config_request __user *user_req = compat_ptr(arg);
	काष्ठा raw32_config_request rq;
	dev_t dev;
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल RAW_SETBIND:
		अगर (copy_from_user(&rq, user_req, माप(rq)))
			वापस -EFAULT;

		वापस bind_set(rq.raw_minor, rq.block_major, rq.block_minor);

	हाल RAW_GETBIND:
		अगर (copy_from_user(&rq, user_req, माप(rq)))
			वापस -EFAULT;

		err = bind_get(rq.raw_minor, &dev);
		अगर (err)
			वापस err;

		rq.block_major = MAJOR(dev);
		rq.block_minor = MINOR(dev);

		अगर (copy_to_user(user_req, &rq, माप(rq)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations raw_fops = अणु
	.पढ़ो_iter	= blkdev_पढ़ो_iter,
	.ग_लिखो_iter	= blkdev_ग_लिखो_iter,
	.fsync		= blkdev_fsync,
	.खोलो		= raw_खोलो,
	.release	= raw_release,
	.unlocked_ioctl = raw_ioctl,
	.llseek		= शेष_llseek,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा file_operations raw_ctl_fops = अणु
	.unlocked_ioctl = raw_ctl_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= raw_ctl_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= raw_खोलो,
	.owner		= THIS_MODULE,
	.llseek		= noop_llseek,
पूर्ण;

अटल काष्ठा cdev raw_cdev;

अटल अक्षर *raw_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "raw/%s", dev_name(dev));
पूर्ण

अटल पूर्णांक __init raw_init(व्योम)
अणु
	dev_t dev = MKDEV(RAW_MAJOR, 0);
	पूर्णांक ret;

	अगर (max_raw_minors < 1 || max_raw_minors > 65536) अणु
		pr_warn("raw: invalid max_raw_minors (must be between 1 and 65536), using %d\n",
			CONFIG_MAX_RAW_DEVS);
		max_raw_minors = CONFIG_MAX_RAW_DEVS;
	पूर्ण

	raw_devices = vzalloc(array_size(max_raw_minors,
					 माप(काष्ठा raw_device_data)));
	अगर (!raw_devices) अणु
		prपूर्णांकk(KERN_ERR "Not enough memory for raw device structures\n");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	ret = रेजिस्टर_chrdev_region(dev, max_raw_minors, "raw");
	अगर (ret)
		जाओ error;

	cdev_init(&raw_cdev, &raw_fops);
	ret = cdev_add(&raw_cdev, dev, max_raw_minors);
	अगर (ret)
		जाओ error_region;
	raw_class = class_create(THIS_MODULE, "raw");
	अगर (IS_ERR(raw_class)) अणु
		prपूर्णांकk(KERN_ERR "Error creating raw class.\n");
		cdev_del(&raw_cdev);
		ret = PTR_ERR(raw_class);
		जाओ error_region;
	पूर्ण
	raw_class->devnode = raw_devnode;
	device_create(raw_class, शून्य, MKDEV(RAW_MAJOR, 0), शून्य, "rawctl");

	वापस 0;

error_region:
	unरेजिस्टर_chrdev_region(dev, max_raw_minors);
error:
	vमुक्त(raw_devices);
	वापस ret;
पूर्ण

अटल व्योम __निकास raw_निकास(व्योम)
अणु
	device_destroy(raw_class, MKDEV(RAW_MAJOR, 0));
	class_destroy(raw_class);
	cdev_del(&raw_cdev);
	unरेजिस्टर_chrdev_region(MKDEV(RAW_MAJOR, 0), max_raw_minors);
पूर्ण

module_init(raw_init);
module_निकास(raw_निकास);
MODULE_LICENSE("GPL");
