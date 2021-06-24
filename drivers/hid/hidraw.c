<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID raw devices, giving access to raw HID events.
 *
 * In comparison to hiddev, this device करोes not process the
 * hid events at all (no parsing, no lookups). This lets applications
 * to work on raw hid events as they want to, and aव्योमs a need to
 * use a transport-specअगरic userspace libhid/libusb libraries.
 *
 *  Copyright (c) 2007-2014 Jiri Kosina
 */


#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/cdev.h>
#समावेश <linux/poll.h>
#समावेश <linux/device.h>
#समावेश <linux/major.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/माला.स>

#समावेश <linux/hidraw.h>

अटल पूर्णांक hidraw_major;
अटल काष्ठा cdev hidraw_cdev;
अटल काष्ठा class *hidraw_class;
अटल काष्ठा hidraw *hidraw_table[HIDRAW_MAX_DEVICES];
अटल DEFINE_MUTEX(minors_lock);

अटल sमाप_प्रकार hidraw_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hidraw_list *list = file->निजी_data;
	पूर्णांक ret = 0, len;
	DECLARE_WAITQUEUE(रुको, current);

	mutex_lock(&list->पढ़ो_mutex);

	जबतक (ret == 0) अणु
		अगर (list->head == list->tail) अणु
			add_रुको_queue(&list->hidraw->रुको, &रुको);
			set_current_state(TASK_INTERRUPTIBLE);

			जबतक (list->head == list->tail) अणु
				अगर (संकेत_pending(current)) अणु
					ret = -ERESTARTSYS;
					अवरोध;
				पूर्ण
				अगर (!list->hidraw->exist) अणु
					ret = -EIO;
					अवरोध;
				पूर्ण
				अगर (file->f_flags & O_NONBLOCK) अणु
					ret = -EAGAIN;
					अवरोध;
				पूर्ण

				/* allow O_NONBLOCK to work well from other thपढ़ोs */
				mutex_unlock(&list->पढ़ो_mutex);
				schedule();
				mutex_lock(&list->पढ़ो_mutex);
				set_current_state(TASK_INTERRUPTIBLE);
			पूर्ण

			set_current_state(TASK_RUNNING);
			हटाओ_रुको_queue(&list->hidraw->रुको, &रुको);
		पूर्ण

		अगर (ret)
			जाओ out;

		len = list->buffer[list->tail].len > count ?
			count : list->buffer[list->tail].len;

		अगर (list->buffer[list->tail].value) अणु
			अगर (copy_to_user(buffer, list->buffer[list->tail].value, len)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
			ret = len;
		पूर्ण

		kमुक्त(list->buffer[list->tail].value);
		list->buffer[list->tail].value = शून्य;
		list->tail = (list->tail + 1) & (HIDRAW_BUFFER_SIZE - 1);
	पूर्ण
out:
	mutex_unlock(&list->पढ़ो_mutex);
	वापस ret;
पूर्ण

/*
 * The first byte of the report buffer is expected to be a report number.
 */
अटल sमाप_प्रकार hidraw_send_report(काष्ठा file *file, स्थिर अक्षर __user *buffer, माप_प्रकार count, अचिन्हित अक्षर report_type)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	काष्ठा hid_device *dev;
	__u8 *buf;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&minors_lock);

	अगर (!hidraw_table[minor] || !hidraw_table[minor]->exist) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	dev = hidraw_table[minor]->hid;

	अगर (count > HID_MAX_BUFFER_SIZE) अणु
		hid_warn(dev, "pid %d passed too large report\n",
			 task_pid_nr(current));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (count < 2) अणु
		hid_warn(dev, "pid %d passed too short report\n",
			 task_pid_nr(current));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	buf = memdup_user(buffer, count);
	अगर (IS_ERR(buf)) अणु
		ret = PTR_ERR(buf);
		जाओ out;
	पूर्ण

	अगर ((report_type == HID_OUTPUT_REPORT) &&
	    !(dev->quirks & HID_QUIRK_NO_OUTPUT_REPORTS_ON_INTR_EP)) अणु
		ret = hid_hw_output_report(dev, buf, count);
		/*
		 * compatibility with old implementation of USB-HID and I2C-HID:
		 * अगर the device करोes not support receiving output reports,
		 * on an पूर्णांकerrupt endpoपूर्णांक, fallback to SET_REPORT HID command.
		 */
		अगर (ret != -ENOSYS)
			जाओ out_मुक्त;
	पूर्ण

	ret = hid_hw_raw_request(dev, buf[0], buf, count, report_type,
				HID_REQ_SET_REPORT);

out_मुक्त:
	kमुक्त(buf);
out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार hidraw_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	mutex_lock(&minors_lock);
	ret = hidraw_send_report(file, buffer, count, HID_OUTPUT_REPORT);
	mutex_unlock(&minors_lock);
	वापस ret;
पूर्ण


/*
 * This function perक्रमms a Get_Report transfer over the control endpoपूर्णांक
 * per section 7.2.1 of the HID specअगरication, version 1.1.  The first byte
 * of buffer is the report number to request, or 0x0 अगर the device करोes not
 * use numbered reports. The report_type parameter can be HID_FEATURE_REPORT
 * or HID_INPUT_REPORT.
 */
अटल sमाप_प्रकार hidraw_get_report(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count, अचिन्हित अक्षर report_type)
अणु
	अचिन्हित पूर्णांक minor = iminor(file_inode(file));
	काष्ठा hid_device *dev;
	__u8 *buf;
	पूर्णांक ret = 0, len;
	अचिन्हित अक्षर report_number;

	lockdep_निश्चित_held(&minors_lock);

	अगर (!hidraw_table[minor] || !hidraw_table[minor]->exist) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	dev = hidraw_table[minor]->hid;

	अगर (!dev->ll_driver->raw_request) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (count > HID_MAX_BUFFER_SIZE) अणु
		hid_warn(dev, "pid %d passed too large report\n",
			task_pid_nr(current));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (count < 2) अणु
		hid_warn(dev, "pid %d passed too short report\n",
			task_pid_nr(current));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	buf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Read the first byte from the user. This is the report number,
	 * which is passed to hid_hw_raw_request().
	 */
	अगर (copy_from_user(&report_number, buffer, 1)) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	ret = hid_hw_raw_request(dev, report_number, buf, count, report_type,
				 HID_REQ_GET_REPORT);

	अगर (ret < 0)
		जाओ out_मुक्त;

	len = (ret < count) ? ret : count;

	अगर (copy_to_user(buffer, buf, len)) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	ret = len;

out_मुक्त:
	kमुक्त(buf);
out:
	वापस ret;
पूर्ण

अटल __poll_t hidraw_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा hidraw_list *list = file->निजी_data;
	__poll_t mask = EPOLLOUT | EPOLLWRNORM; /* hidraw is always writable */

	poll_रुको(file, &list->hidraw->रुको, रुको);
	अगर (list->head != list->tail)
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (!list->hidraw->exist)
		mask |= EPOLLERR | EPOLLHUP;
	वापस mask;
पूर्ण

अटल पूर्णांक hidraw_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा hidraw *dev;
	काष्ठा hidraw_list *list;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	अगर (!(list = kzalloc(माप(काष्ठा hidraw_list), GFP_KERNEL))) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_lock(&minors_lock);
	अगर (!hidraw_table[minor] || !hidraw_table[minor]->exist) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	dev = hidraw_table[minor];
	अगर (!dev->खोलो++) अणु
		err = hid_hw_घातer(dev->hid, PM_HINT_FULLON);
		अगर (err < 0) अणु
			dev->खोलो--;
			जाओ out_unlock;
		पूर्ण

		err = hid_hw_खोलो(dev->hid);
		अगर (err < 0) अणु
			hid_hw_घातer(dev->hid, PM_HINT_NORMAL);
			dev->खोलो--;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	list->hidraw = hidraw_table[minor];
	mutex_init(&list->पढ़ो_mutex);
	spin_lock_irqsave(&hidraw_table[minor]->list_lock, flags);
	list_add_tail(&list->node, &hidraw_table[minor]->list);
	spin_unlock_irqrestore(&hidraw_table[minor]->list_lock, flags);
	file->निजी_data = list;
out_unlock:
	mutex_unlock(&minors_lock);
out:
	अगर (err < 0)
		kमुक्त(list);
	वापस err;

पूर्ण

अटल पूर्णांक hidraw_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा hidraw_list *list = file->निजी_data;

	वापस fasync_helper(fd, file, on, &list->fasync);
पूर्ण

अटल व्योम drop_ref(काष्ठा hidraw *hidraw, पूर्णांक exists_bit)
अणु
	अगर (exists_bit) अणु
		hidraw->exist = 0;
		अगर (hidraw->खोलो) अणु
			hid_hw_बंद(hidraw->hid);
			wake_up_पूर्णांकerruptible(&hidraw->रुको);
		पूर्ण
		device_destroy(hidraw_class,
			       MKDEV(hidraw_major, hidraw->minor));
	पूर्ण अन्यथा अणु
		--hidraw->खोलो;
	पूर्ण
	अगर (!hidraw->खोलो) अणु
		अगर (!hidraw->exist) अणु
			hidraw_table[hidraw->minor] = शून्य;
			kमुक्त(hidraw);
		पूर्ण अन्यथा अणु
			/* बंद device क्रम last पढ़ोer */
			hid_hw_बंद(hidraw->hid);
			hid_hw_घातer(hidraw->hid, PM_HINT_NORMAL);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hidraw_release(काष्ठा inode * inode, काष्ठा file * file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा hidraw_list *list = file->निजी_data;
	अचिन्हित दीर्घ flags;

	mutex_lock(&minors_lock);

	spin_lock_irqsave(&hidraw_table[minor]->list_lock, flags);
	list_del(&list->node);
	spin_unlock_irqrestore(&hidraw_table[minor]->list_lock, flags);
	kमुक्त(list);

	drop_ref(hidraw_table[minor], 0);

	mutex_unlock(&minors_lock);
	वापस 0;
पूर्ण

अटल दीर्घ hidraw_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(file);
	अचिन्हित पूर्णांक minor = iminor(inode);
	दीर्घ ret = 0;
	काष्ठा hidraw *dev;
	व्योम __user *user_arg = (व्योम __user*) arg;

	mutex_lock(&minors_lock);
	dev = hidraw_table[minor];
	अगर (!dev || !dev->exist) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
		हाल HIDIOCGRDESCSIZE:
			अगर (put_user(dev->hid->rsize, (पूर्णांक __user *)arg))
				ret = -EFAULT;
			अवरोध;

		हाल HIDIOCGRDESC:
			अणु
				__u32 len;

				अगर (get_user(len, (पूर्णांक __user *)arg))
					ret = -EFAULT;
				अन्यथा अगर (len > HID_MAX_DESCRIPTOR_SIZE - 1)
					ret = -EINVAL;
				अन्यथा अगर (copy_to_user(user_arg + दुरत्व(
					काष्ठा hidraw_report_descriptor,
					value[0]),
					dev->hid->rdesc,
					min(dev->hid->rsize, len)))
					ret = -EFAULT;
				अवरोध;
			पूर्ण
		हाल HIDIOCGRAWINFO:
			अणु
				काष्ठा hidraw_devinfo dinfo;

				dinfo.bustype = dev->hid->bus;
				dinfo.venकरोr = dev->hid->venकरोr;
				dinfo.product = dev->hid->product;
				अगर (copy_to_user(user_arg, &dinfo, माप(dinfo)))
					ret = -EFAULT;
				अवरोध;
			पूर्ण
		शेष:
			अणु
				काष्ठा hid_device *hid = dev->hid;
				अगर (_IOC_TYPE(cmd) != 'H') अणु
					ret = -EINVAL;
					अवरोध;
				पूर्ण

				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCSFEATURE(0))) अणु
					पूर्णांक len = _IOC_SIZE(cmd);
					ret = hidraw_send_report(file, user_arg, len, HID_FEATURE_REPORT);
					अवरोध;
				पूर्ण
				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCGFEATURE(0))) अणु
					पूर्णांक len = _IOC_SIZE(cmd);
					ret = hidraw_get_report(file, user_arg, len, HID_FEATURE_REPORT);
					अवरोध;
				पूर्ण

				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCSINPUT(0))) अणु
					पूर्णांक len = _IOC_SIZE(cmd);
					ret = hidraw_send_report(file, user_arg, len, HID_INPUT_REPORT);
					अवरोध;
				पूर्ण
				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCGINPUT(0))) अणु
					पूर्णांक len = _IOC_SIZE(cmd);
					ret = hidraw_get_report(file, user_arg, len, HID_INPUT_REPORT);
					अवरोध;
				पूर्ण

				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCSOUTPUT(0))) अणु
					पूर्णांक len = _IOC_SIZE(cmd);
					ret = hidraw_send_report(file, user_arg, len, HID_OUTPUT_REPORT);
					अवरोध;
				पूर्ण
				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCGOUTPUT(0))) अणु
					पूर्णांक len = _IOC_SIZE(cmd);
					ret = hidraw_get_report(file, user_arg, len, HID_OUTPUT_REPORT);
					अवरोध;
				पूर्ण

				/* Begin Read-only ioctls. */
				अगर (_IOC_सूची(cmd) != _IOC_READ) अणु
					ret = -EINVAL;
					अवरोध;
				पूर्ण

				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCGRAWNAME(0))) अणु
					पूर्णांक len = म_माप(hid->name) + 1;
					अगर (len > _IOC_SIZE(cmd))
						len = _IOC_SIZE(cmd);
					ret = copy_to_user(user_arg, hid->name, len) ?
						-EFAULT : len;
					अवरोध;
				पूर्ण

				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCGRAWPHYS(0))) अणु
					पूर्णांक len = म_माप(hid->phys) + 1;
					अगर (len > _IOC_SIZE(cmd))
						len = _IOC_SIZE(cmd);
					ret = copy_to_user(user_arg, hid->phys, len) ?
						-EFAULT : len;
					अवरोध;
				पूर्ण

				अगर (_IOC_NR(cmd) == _IOC_NR(HIDIOCGRAWUNIQ(0))) अणु
					पूर्णांक len = म_माप(hid->uniq) + 1;
					अगर (len > _IOC_SIZE(cmd))
						len = _IOC_SIZE(cmd);
					ret = copy_to_user(user_arg, hid->uniq, len) ?
						-EFAULT : len;
					अवरोध;
				पूर्ण
			पूर्ण

		ret = -ENOTTY;
	पूर्ण
out:
	mutex_unlock(&minors_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations hidraw_ops = अणु
	.owner =        THIS_MODULE,
	.पढ़ो =         hidraw_पढ़ो,
	.ग_लिखो =        hidraw_ग_लिखो,
	.poll =         hidraw_poll,
	.खोलो =         hidraw_खोलो,
	.release =      hidraw_release,
	.unlocked_ioctl = hidraw_ioctl,
	.fasync =	hidraw_fasync,
	.compat_ioctl   = compat_ptr_ioctl,
	.llseek =	noop_llseek,
पूर्ण;

पूर्णांक hidraw_report_event(काष्ठा hid_device *hid, u8 *data, पूर्णांक len)
अणु
	काष्ठा hidraw *dev = hid->hidraw;
	काष्ठा hidraw_list *list;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->list_lock, flags);
	list_क्रम_each_entry(list, &dev->list, node) अणु
		पूर्णांक new_head = (list->head + 1) & (HIDRAW_BUFFER_SIZE - 1);

		अगर (new_head == list->tail)
			जारी;

		अगर (!(list->buffer[list->head].value = kmemdup(data, len, GFP_ATOMIC))) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		list->buffer[list->head].len = len;
		list->head = new_head;
		समाप्त_fasync(&list->fasync, SIGIO, POLL_IN);
	पूर्ण
	spin_unlock_irqrestore(&dev->list_lock, flags);

	wake_up_पूर्णांकerruptible(&dev->रुको);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(hidraw_report_event);

पूर्णांक hidraw_connect(काष्ठा hid_device *hid)
अणु
	पूर्णांक minor, result;
	काष्ठा hidraw *dev;

	/* we accept any HID device, all applications */

	dev = kzalloc(माप(काष्ठा hidraw), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	result = -EINVAL;

	mutex_lock(&minors_lock);

	क्रम (minor = 0; minor < HIDRAW_MAX_DEVICES; minor++) अणु
		अगर (hidraw_table[minor])
			जारी;
		hidraw_table[minor] = dev;
		result = 0;
		अवरोध;
	पूर्ण

	अगर (result) अणु
		mutex_unlock(&minors_lock);
		kमुक्त(dev);
		जाओ out;
	पूर्ण

	dev->dev = device_create(hidraw_class, &hid->dev, MKDEV(hidraw_major, minor),
				 शून्य, "%s%d", "hidraw", minor);

	अगर (IS_ERR(dev->dev)) अणु
		hidraw_table[minor] = शून्य;
		mutex_unlock(&minors_lock);
		result = PTR_ERR(dev->dev);
		kमुक्त(dev);
		जाओ out;
	पूर्ण

	init_रुकोqueue_head(&dev->रुको);
	spin_lock_init(&dev->list_lock);
	INIT_LIST_HEAD(&dev->list);

	dev->hid = hid;
	dev->minor = minor;

	dev->exist = 1;
	hid->hidraw = dev;

	mutex_unlock(&minors_lock);
out:
	वापस result;

पूर्ण
EXPORT_SYMBOL_GPL(hidraw_connect);

व्योम hidraw_disconnect(काष्ठा hid_device *hid)
अणु
	काष्ठा hidraw *hidraw = hid->hidraw;

	mutex_lock(&minors_lock);

	drop_ref(hidraw, 1);

	mutex_unlock(&minors_lock);
पूर्ण
EXPORT_SYMBOL_GPL(hidraw_disconnect);

पूर्णांक __init hidraw_init(व्योम)
अणु
	पूर्णांक result;
	dev_t dev_id;

	result = alloc_chrdev_region(&dev_id, HIDRAW_FIRST_MINOR,
			HIDRAW_MAX_DEVICES, "hidraw");
	अगर (result < 0) अणु
		pr_warn("can't get major number\n");
		जाओ out;
	पूर्ण

	hidraw_major = MAJOR(dev_id);

	hidraw_class = class_create(THIS_MODULE, "hidraw");
	अगर (IS_ERR(hidraw_class)) अणु
		result = PTR_ERR(hidraw_class);
		जाओ error_cdev;
	पूर्ण

        cdev_init(&hidraw_cdev, &hidraw_ops);
	result = cdev_add(&hidraw_cdev, dev_id, HIDRAW_MAX_DEVICES);
	अगर (result < 0)
		जाओ error_class;

	pr_info("raw HID events driver (C) Jiri Kosina\n");
out:
	वापस result;

error_class:
	class_destroy(hidraw_class);
error_cdev:
	unरेजिस्टर_chrdev_region(dev_id, HIDRAW_MAX_DEVICES);
	जाओ out;
पूर्ण

व्योम hidraw_निकास(व्योम)
अणु
	dev_t dev_id = MKDEV(hidraw_major, 0);

	cdev_del(&hidraw_cdev);
	class_destroy(hidraw_class);
	unरेजिस्टर_chrdev_region(dev_id, HIDRAW_MAX_DEVICES);

पूर्ण
