<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat driver क्रम Linux
 *
 * Copyright (c) 2010 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/*
 * Module roccat is a अक्षर device used to report special events of roccat
 * hardware to userland. These events include requests क्रम on-screen-display of
 * profile or dpi settings or requests क्रम execution of macro sequences that are
 * not stored in device. The inक्रमmation in these events depends on hid device
 * implementation and contains data that is not available in a single hid event
 * or अन्यथा hidraw could have been used.
 * It is inspired by hidraw, but uses only one circular buffer क्रम all पढ़ोers.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cdev.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/hid-roccat.h>
#समावेश <linux/module.h>

#घोषणा ROCCAT_FIRST_MINOR 0
#घोषणा ROCCAT_MAX_DEVICES 8

/* should be a घातer of 2 क्रम perक्रमmance reason */
#घोषणा ROCCAT_CBUF_SIZE 16

काष्ठा roccat_report अणु
	uपूर्णांक8_t *value;
पूर्ण;

काष्ठा roccat_device अणु
	अचिन्हित पूर्णांक minor;
	पूर्णांक report_size;
	पूर्णांक खोलो;
	पूर्णांक exist;
	रुको_queue_head_t रुको;
	काष्ठा device *dev;
	काष्ठा hid_device *hid;
	काष्ठा list_head पढ़ोers;
	/* protects modअगरications of पढ़ोers list */
	काष्ठा mutex पढ़ोers_lock;

	/*
	 * circular_buffer has one ग_लिखोr and multiple पढ़ोers with their own
	 * पढ़ो poपूर्णांकers
	 */
	काष्ठा roccat_report cbuf[ROCCAT_CBUF_SIZE];
	पूर्णांक cbuf_end;
	काष्ठा mutex cbuf_lock;
पूर्ण;

काष्ठा roccat_पढ़ोer अणु
	काष्ठा list_head node;
	काष्ठा roccat_device *device;
	पूर्णांक cbuf_start;
पूर्ण;

अटल पूर्णांक roccat_major;
अटल काष्ठा cdev roccat_cdev;

अटल काष्ठा roccat_device *devices[ROCCAT_MAX_DEVICES];
/* protects modअगरications of devices array */
अटल DEFINE_MUTEX(devices_lock);

अटल sमाप_प्रकार roccat_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा roccat_पढ़ोer *पढ़ोer = file->निजी_data;
	काष्ठा roccat_device *device = पढ़ोer->device;
	काष्ठा roccat_report *report;
	sमाप_प्रकार retval = 0, len;
	DECLARE_WAITQUEUE(रुको, current);

	mutex_lock(&device->cbuf_lock);

	/* no data? */
	अगर (पढ़ोer->cbuf_start == device->cbuf_end) अणु
		add_रुको_queue(&device->रुको, &रुको);
		set_current_state(TASK_INTERRUPTIBLE);

		/* रुको क्रम data */
		जबतक (पढ़ोer->cbuf_start == device->cbuf_end) अणु
			अगर (file->f_flags & O_NONBLOCK) अणु
				retval = -EAGAIN;
				अवरोध;
			पूर्ण
			अगर (संकेत_pending(current)) अणु
				retval = -ERESTARTSYS;
				अवरोध;
			पूर्ण
			अगर (!device->exist) अणु
				retval = -EIO;
				अवरोध;
			पूर्ण

			mutex_unlock(&device->cbuf_lock);
			schedule();
			mutex_lock(&device->cbuf_lock);
			set_current_state(TASK_INTERRUPTIBLE);
		पूर्ण

		set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&device->रुको, &रुको);
	पूर्ण

	/* here we either have data or a reason to वापस अगर retval is set */
	अगर (retval)
		जाओ निकास_unlock;

	report = &device->cbuf[पढ़ोer->cbuf_start];
	/*
	 * If report is larger than requested amount of data, rest of report
	 * is lost!
	 */
	len = device->report_size > count ? count : device->report_size;

	अगर (copy_to_user(buffer, report->value, len)) अणु
		retval = -EFAULT;
		जाओ निकास_unlock;
	पूर्ण
	retval += len;
	पढ़ोer->cbuf_start = (पढ़ोer->cbuf_start + 1) % ROCCAT_CBUF_SIZE;

निकास_unlock:
	mutex_unlock(&device->cbuf_lock);
	वापस retval;
पूर्ण

अटल __poll_t roccat_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा roccat_पढ़ोer *पढ़ोer = file->निजी_data;
	poll_रुको(file, &पढ़ोer->device->रुको, रुको);
	अगर (पढ़ोer->cbuf_start != पढ़ोer->device->cbuf_end)
		वापस EPOLLIN | EPOLLRDNORM;
	अगर (!पढ़ोer->device->exist)
		वापस EPOLLERR | EPOLLHUP;
	वापस 0;
पूर्ण

अटल पूर्णांक roccat_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा roccat_पढ़ोer *पढ़ोer;
	काष्ठा roccat_device *device;
	पूर्णांक error = 0;

	पढ़ोer = kzalloc(माप(काष्ठा roccat_पढ़ोer), GFP_KERNEL);
	अगर (!पढ़ोer)
		वापस -ENOMEM;

	mutex_lock(&devices_lock);

	device = devices[minor];

	अगर (!device) अणु
		pr_emerg("roccat device with minor %d doesn't exist\n", minor);
		error = -ENODEV;
		जाओ निकास_err_devices;
	पूर्ण

	mutex_lock(&device->पढ़ोers_lock);

	अगर (!device->खोलो++) अणु
		/* घातer on device on adding first पढ़ोer */
		error = hid_hw_घातer(device->hid, PM_HINT_FULLON);
		अगर (error < 0) अणु
			--device->खोलो;
			जाओ निकास_err_पढ़ोers;
		पूर्ण

		error = hid_hw_खोलो(device->hid);
		अगर (error < 0) अणु
			hid_hw_घातer(device->hid, PM_HINT_NORMAL);
			--device->खोलो;
			जाओ निकास_err_पढ़ोers;
		पूर्ण
	पूर्ण

	पढ़ोer->device = device;
	/* new पढ़ोer करोesn't get old events */
	पढ़ोer->cbuf_start = device->cbuf_end;

	list_add_tail(&पढ़ोer->node, &device->पढ़ोers);
	file->निजी_data = पढ़ोer;

निकास_err_पढ़ोers:
	mutex_unlock(&device->पढ़ोers_lock);
निकास_err_devices:
	mutex_unlock(&devices_lock);
	अगर (error)
		kमुक्त(पढ़ोer);
	वापस error;
पूर्ण

अटल पूर्णांक roccat_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा roccat_पढ़ोer *पढ़ोer = file->निजी_data;
	काष्ठा roccat_device *device;

	mutex_lock(&devices_lock);

	device = devices[minor];
	अगर (!device) अणु
		mutex_unlock(&devices_lock);
		pr_emerg("roccat device with minor %d doesn't exist\n", minor);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&device->पढ़ोers_lock);
	list_del(&पढ़ोer->node);
	mutex_unlock(&device->पढ़ोers_lock);
	kमुक्त(पढ़ोer);

	अगर (!--device->खोलो) अणु
		/* removing last पढ़ोer */
		अगर (device->exist) अणु
			hid_hw_घातer(device->hid, PM_HINT_NORMAL);
			hid_hw_बंद(device->hid);
		पूर्ण अन्यथा अणु
			kमुक्त(device);
		पूर्ण
	पूर्ण

	mutex_unlock(&devices_lock);

	वापस 0;
पूर्ण

/*
 * roccat_report_event() - output data to पढ़ोers
 * @minor: minor device number वापसed by roccat_connect()
 * @data: poपूर्णांकer to data
 *
 * Return value is zero on success, a negative error code on failure.
 *
 * This is called from पूर्णांकerrupt handler.
 */
पूर्णांक roccat_report_event(पूर्णांक minor, u8 स्थिर *data)
अणु
	काष्ठा roccat_device *device;
	काष्ठा roccat_पढ़ोer *पढ़ोer;
	काष्ठा roccat_report *report;
	uपूर्णांक8_t *new_value;

	device = devices[minor];

	new_value = kmemdup(data, device->report_size, GFP_ATOMIC);
	अगर (!new_value)
		वापस -ENOMEM;

	report = &device->cbuf[device->cbuf_end];

	/* passing शून्य is safe */
	kमुक्त(report->value);

	report->value = new_value;
	device->cbuf_end = (device->cbuf_end + 1) % ROCCAT_CBUF_SIZE;

	list_क्रम_each_entry(पढ़ोer, &device->पढ़ोers, node) अणु
		/*
		 * As we alपढ़ोy inserted one element, the buffer can't be
		 * empty. If start and end are equal, buffer is full and we
		 * increase start, so that slow पढ़ोer misses one event, but
		 * माला_लो the newer ones in the right order.
		 */
		अगर (पढ़ोer->cbuf_start == device->cbuf_end)
			पढ़ोer->cbuf_start = (पढ़ोer->cbuf_start + 1) % ROCCAT_CBUF_SIZE;
	पूर्ण

	wake_up_पूर्णांकerruptible(&device->रुको);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(roccat_report_event);

/*
 * roccat_connect() - create a अक्षर device क्रम special event output
 * @class: the class thats used to create the device. Meant to hold device
 * specअगरic sysfs attributes.
 * @hid: the hid device the अक्षर device should be connected to.
 * @report_size: size of reports
 *
 * Return value is minor device number in Range [0, ROCCAT_MAX_DEVICES] on
 * success, a negative error code on failure.
 */
पूर्णांक roccat_connect(काष्ठा class *klass, काष्ठा hid_device *hid, पूर्णांक report_size)
अणु
	अचिन्हित पूर्णांक minor;
	काष्ठा roccat_device *device;
	पूर्णांक temp;

	device = kzalloc(माप(काष्ठा roccat_device), GFP_KERNEL);
	अगर (!device)
		वापस -ENOMEM;

	mutex_lock(&devices_lock);

	क्रम (minor = 0; minor < ROCCAT_MAX_DEVICES; ++minor) अणु
		अगर (devices[minor])
			जारी;
		अवरोध;
	पूर्ण

	अगर (minor < ROCCAT_MAX_DEVICES) अणु
		devices[minor] = device;
	पूर्ण अन्यथा अणु
		mutex_unlock(&devices_lock);
		kमुक्त(device);
		वापस -EINVAL;
	पूर्ण

	device->dev = device_create(klass, &hid->dev,
			MKDEV(roccat_major, minor), शून्य,
			"%s%s%d", "roccat", hid->driver->name, minor);

	अगर (IS_ERR(device->dev)) अणु
		devices[minor] = शून्य;
		mutex_unlock(&devices_lock);
		temp = PTR_ERR(device->dev);
		kमुक्त(device);
		वापस temp;
	पूर्ण

	mutex_unlock(&devices_lock);

	init_रुकोqueue_head(&device->रुको);
	INIT_LIST_HEAD(&device->पढ़ोers);
	mutex_init(&device->पढ़ोers_lock);
	mutex_init(&device->cbuf_lock);
	device->minor = minor;
	device->hid = hid;
	device->exist = 1;
	device->cbuf_end = 0;
	device->report_size = report_size;

	वापस minor;
पूर्ण
EXPORT_SYMBOL_GPL(roccat_connect);

/* roccat_disconnect() - हटाओ अक्षर device from hid device
 * @minor: the minor device number वापसed by roccat_connect()
 */
व्योम roccat_disconnect(पूर्णांक minor)
अणु
	काष्ठा roccat_device *device;

	mutex_lock(&devices_lock);
	device = devices[minor];
	mutex_unlock(&devices_lock);

	device->exist = 0; /* TODO exist maybe not needed */

	device_destroy(device->dev->class, MKDEV(roccat_major, minor));

	mutex_lock(&devices_lock);
	devices[minor] = शून्य;
	mutex_unlock(&devices_lock);

	अगर (device->खोलो) अणु
		hid_hw_बंद(device->hid);
		wake_up_पूर्णांकerruptible(&device->रुको);
	पूर्ण अन्यथा अणु
		kमुक्त(device);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(roccat_disconnect);

अटल दीर्घ roccat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा roccat_device *device;
	अचिन्हित पूर्णांक minor = iminor(inode);
	दीर्घ retval = 0;

	mutex_lock(&devices_lock);

	device = devices[minor];
	अगर (!device) अणु
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
	हाल ROCCATIOCGREPSIZE:
		अगर (put_user(device->report_size, (पूर्णांक __user *)arg))
			retval = -EFAULT;
		अवरोध;
	शेष:
		retval = -ENOTTY;
	पूर्ण
out:
	mutex_unlock(&devices_lock);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations roccat_ops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = roccat_पढ़ो,
	.poll = roccat_poll,
	.खोलो = roccat_खोलो,
	.release = roccat_release,
	.llseek = noop_llseek,
	.unlocked_ioctl = roccat_ioctl,
पूर्ण;

अटल पूर्णांक __init roccat_init(व्योम)
अणु
	पूर्णांक retval;
	dev_t dev_id;

	retval = alloc_chrdev_region(&dev_id, ROCCAT_FIRST_MINOR,
			ROCCAT_MAX_DEVICES, "roccat");
	अगर (retval < 0) अणु
		pr_warn("can't get major number\n");
		जाओ error;
	पूर्ण

	roccat_major = MAJOR(dev_id);

	cdev_init(&roccat_cdev, &roccat_ops);
	retval = cdev_add(&roccat_cdev, dev_id, ROCCAT_MAX_DEVICES);

	अगर (retval < 0) अणु
		pr_warn("cannot add cdev\n");
		जाओ cleanup_alloc_chrdev_region;
	पूर्ण
	वापस 0;


 cleanup_alloc_chrdev_region:
	unरेजिस्टर_chrdev_region(dev_id, ROCCAT_MAX_DEVICES);
 error:
	वापस retval;
पूर्ण

अटल व्योम __निकास roccat_निकास(व्योम)
अणु
	dev_t dev_id = MKDEV(roccat_major, 0);

	cdev_del(&roccat_cdev);
	unरेजिस्टर_chrdev_region(dev_id, ROCCAT_MAX_DEVICES);
पूर्ण

module_init(roccat_init);
module_निकास(roccat_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat char device");
MODULE_LICENSE("GPL v2");
