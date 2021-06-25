<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GNSS receiver core
 *
 * Copyright (C) 2018 Johan Hovold <johan@kernel.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cdev.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/gnss.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>

#घोषणा GNSS_FLAG_HAS_WRITE_RAW		BIT(0)

#घोषणा GNSS_MINORS	16

अटल DEFINE_IDA(gnss_minors);
अटल dev_t gnss_first;

/* FIFO size must be a घातer of two */
#घोषणा GNSS_READ_FIFO_SIZE	4096
#घोषणा GNSS_WRITE_BUF_SIZE	1024

#घोषणा to_gnss_device(d) container_of((d), काष्ठा gnss_device, dev)

अटल पूर्णांक gnss_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gnss_device *gdev;
	पूर्णांक ret = 0;

	gdev = container_of(inode->i_cdev, काष्ठा gnss_device, cdev);

	get_device(&gdev->dev);

	stream_खोलो(inode, file);
	file->निजी_data = gdev;

	करोwn_ग_लिखो(&gdev->rwsem);
	अगर (gdev->disconnected) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (gdev->count++ == 0) अणु
		ret = gdev->ops->खोलो(gdev);
		अगर (ret)
			gdev->count--;
	पूर्ण
unlock:
	up_ग_लिखो(&gdev->rwsem);

	अगर (ret)
		put_device(&gdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक gnss_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा gnss_device *gdev = file->निजी_data;

	करोwn_ग_लिखो(&gdev->rwsem);
	अगर (gdev->disconnected)
		जाओ unlock;

	अगर (--gdev->count == 0) अणु
		gdev->ops->बंद(gdev);
		kfअगरo_reset(&gdev->पढ़ो_fअगरo);
	पूर्ण
unlock:
	up_ग_लिखो(&gdev->rwsem);

	put_device(&gdev->dev);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार gnss_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा gnss_device *gdev = file->निजी_data;
	अचिन्हित पूर्णांक copied;
	पूर्णांक ret;

	mutex_lock(&gdev->पढ़ो_mutex);
	जबतक (kfअगरo_is_empty(&gdev->पढ़ो_fअगरo)) अणु
		mutex_unlock(&gdev->पढ़ो_mutex);

		अगर (gdev->disconnected)
			वापस 0;

		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		ret = रुको_event_पूर्णांकerruptible(gdev->पढ़ो_queue,
				gdev->disconnected ||
				!kfअगरo_is_empty(&gdev->पढ़ो_fअगरo));
		अगर (ret)
			वापस -ERESTARTSYS;

		mutex_lock(&gdev->पढ़ो_mutex);
	पूर्ण

	ret = kfअगरo_to_user(&gdev->पढ़ो_fअगरo, buf, count, &copied);
	अगर (ret == 0)
		ret = copied;

	mutex_unlock(&gdev->पढ़ो_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार gnss_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा gnss_device *gdev = file->निजी_data;
	माप_प्रकार written = 0;
	पूर्णांक ret;

	अगर (gdev->disconnected)
		वापस -EIO;

	अगर (!count)
		वापस 0;

	अगर (!(gdev->flags & GNSS_FLAG_HAS_WRITE_RAW))
		वापस -EIO;

	/* Ignoring O_NONBLOCK, ग_लिखो_raw() is synchronous. */

	ret = mutex_lock_पूर्णांकerruptible(&gdev->ग_लिखो_mutex);
	अगर (ret)
		वापस -ERESTARTSYS;

	क्रम (;;) अणु
		माप_प्रकार n = count - written;

		अगर (n > GNSS_WRITE_BUF_SIZE)
			n = GNSS_WRITE_BUF_SIZE;

		अगर (copy_from_user(gdev->ग_लिखो_buf, buf, n)) अणु
			ret = -EFAULT;
			जाओ out_unlock;
		पूर्ण

		/*
		 * Assumes ग_लिखो_raw can always accept GNSS_WRITE_BUF_SIZE
		 * bytes.
		 *
		 * FIXME: revisit
		 */
		करोwn_पढ़ो(&gdev->rwsem);
		अगर (!gdev->disconnected)
			ret = gdev->ops->ग_लिखो_raw(gdev, gdev->ग_लिखो_buf, n);
		अन्यथा
			ret = -EIO;
		up_पढ़ो(&gdev->rwsem);

		अगर (ret < 0)
			अवरोध;

		written += ret;
		buf += ret;

		अगर (written == count)
			अवरोध;
	पूर्ण

	अगर (written)
		ret = written;
out_unlock:
	mutex_unlock(&gdev->ग_लिखो_mutex);

	वापस ret;
पूर्ण

अटल __poll_t gnss_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा gnss_device *gdev = file->निजी_data;
	__poll_t mask = 0;

	poll_रुको(file, &gdev->पढ़ो_queue, रुको);

	अगर (!kfअगरo_is_empty(&gdev->पढ़ो_fअगरo))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (gdev->disconnected)
		mask |= EPOLLHUP;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations gnss_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= gnss_खोलो,
	.release	= gnss_release,
	.पढ़ो		= gnss_पढ़ो,
	.ग_लिखो		= gnss_ग_लिखो,
	.poll		= gnss_poll,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा class *gnss_class;

अटल व्योम gnss_device_release(काष्ठा device *dev)
अणु
	काष्ठा gnss_device *gdev = to_gnss_device(dev);

	kमुक्त(gdev->ग_लिखो_buf);
	kfअगरo_मुक्त(&gdev->पढ़ो_fअगरo);
	ida_simple_हटाओ(&gnss_minors, gdev->id);
	kमुक्त(gdev);
पूर्ण

काष्ठा gnss_device *gnss_allocate_device(काष्ठा device *parent)
अणु
	काष्ठा gnss_device *gdev;
	काष्ठा device *dev;
	पूर्णांक id;
	पूर्णांक ret;

	gdev = kzalloc(माप(*gdev), GFP_KERNEL);
	अगर (!gdev)
		वापस शून्य;

	id = ida_simple_get(&gnss_minors, 0, GNSS_MINORS, GFP_KERNEL);
	अगर (id < 0) अणु
		kमुक्त(gdev);
		वापस शून्य;
	पूर्ण

	gdev->id = id;

	dev = &gdev->dev;
	device_initialize(dev);
	dev->devt = gnss_first + id;
	dev->class = gnss_class;
	dev->parent = parent;
	dev->release = gnss_device_release;
	dev_set_drvdata(dev, gdev);
	dev_set_name(dev, "gnss%d", id);

	init_rwsem(&gdev->rwsem);
	mutex_init(&gdev->पढ़ो_mutex);
	mutex_init(&gdev->ग_लिखो_mutex);
	init_रुकोqueue_head(&gdev->पढ़ो_queue);

	ret = kfअगरo_alloc(&gdev->पढ़ो_fअगरo, GNSS_READ_FIFO_SIZE, GFP_KERNEL);
	अगर (ret)
		जाओ err_put_device;

	gdev->ग_लिखो_buf = kzalloc(GNSS_WRITE_BUF_SIZE, GFP_KERNEL);
	अगर (!gdev->ग_लिखो_buf)
		जाओ err_put_device;

	cdev_init(&gdev->cdev, &gnss_fops);
	gdev->cdev.owner = THIS_MODULE;

	वापस gdev;

err_put_device:
	put_device(dev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(gnss_allocate_device);

व्योम gnss_put_device(काष्ठा gnss_device *gdev)
अणु
	put_device(&gdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gnss_put_device);

पूर्णांक gnss_रेजिस्टर_device(काष्ठा gnss_device *gdev)
अणु
	पूर्णांक ret;

	/* Set a flag which can be accessed without holding the rwsem. */
	अगर (gdev->ops->ग_लिखो_raw != शून्य)
		gdev->flags |= GNSS_FLAG_HAS_WRITE_RAW;

	ret = cdev_device_add(&gdev->cdev, &gdev->dev);
	अगर (ret) अणु
		dev_err(&gdev->dev, "failed to add device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gnss_रेजिस्टर_device);

व्योम gnss_deरेजिस्टर_device(काष्ठा gnss_device *gdev)
अणु
	करोwn_ग_लिखो(&gdev->rwsem);
	gdev->disconnected = true;
	अगर (gdev->count) अणु
		wake_up_पूर्णांकerruptible(&gdev->पढ़ो_queue);
		gdev->ops->बंद(gdev);
	पूर्ण
	up_ग_लिखो(&gdev->rwsem);

	cdev_device_del(&gdev->cdev, &gdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(gnss_deरेजिस्टर_device);

/*
 * Caller guarantees serialisation.
 *
 * Must not be called क्रम a बंदd device.
 */
पूर्णांक gnss_insert_raw(काष्ठा gnss_device *gdev, स्थिर अचिन्हित अक्षर *buf,
				माप_प्रकार count)
अणु
	पूर्णांक ret;

	ret = kfअगरo_in(&gdev->पढ़ो_fअगरo, buf, count);

	wake_up_पूर्णांकerruptible(&gdev->पढ़ो_queue);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gnss_insert_raw);

अटल स्थिर अक्षर * स्थिर gnss_type_names[GNSS_TYPE_COUNT] = अणु
	[GNSS_TYPE_NMEA]	= "NMEA",
	[GNSS_TYPE_SIRF]	= "SiRF",
	[GNSS_TYPE_UBX]		= "UBX",
	[GNSS_TYPE_MTK]		= "MTK",
पूर्ण;

अटल स्थिर अक्षर *gnss_type_name(काष्ठा gnss_device *gdev)
अणु
	स्थिर अक्षर *name = शून्य;

	अगर (gdev->type < GNSS_TYPE_COUNT)
		name = gnss_type_names[gdev->type];

	अगर (!name)
		dev_WARN(&gdev->dev, "type name not defined\n");

	वापस name;
पूर्ण

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा gnss_device *gdev = to_gnss_device(dev);

	वापस प्र_लिखो(buf, "%s\n", gnss_type_name(gdev));
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *gnss_attrs[] = अणु
	&dev_attr_type.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(gnss);

अटल पूर्णांक gnss_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा gnss_device *gdev = to_gnss_device(dev);
	पूर्णांक ret;

	ret = add_uevent_var(env, "GNSS_TYPE=%s", gnss_type_name(gdev));
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक __init gnss_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = alloc_chrdev_region(&gnss_first, 0, GNSS_MINORS, "gnss");
	अगर (ret < 0) अणु
		pr_err("failed to allocate device numbers: %d\n", ret);
		वापस ret;
	पूर्ण

	gnss_class = class_create(THIS_MODULE, "gnss");
	अगर (IS_ERR(gnss_class)) अणु
		ret = PTR_ERR(gnss_class);
		pr_err("failed to create class: %d\n", ret);
		जाओ err_unरेजिस्टर_chrdev;
	पूर्ण

	gnss_class->dev_groups = gnss_groups;
	gnss_class->dev_uevent = gnss_uevent;

	pr_info("GNSS driver registered with major %d\n", MAJOR(gnss_first));

	वापस 0;

err_unरेजिस्टर_chrdev:
	unरेजिस्टर_chrdev_region(gnss_first, GNSS_MINORS);

	वापस ret;
पूर्ण
module_init(gnss_module_init);

अटल व्योम __निकास gnss_module_निकास(व्योम)
अणु
	class_destroy(gnss_class);
	unरेजिस्टर_chrdev_region(gnss_first, GNSS_MINORS);
	ida_destroy(&gnss_minors);
पूर्ण
module_निकास(gnss_module_निकास);

MODULE_AUTHOR("Johan Hovold <johan@kernel.org>");
MODULE_DESCRIPTION("GNSS receiver core");
MODULE_LICENSE("GPL v2");
