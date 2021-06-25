<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ACPI event handling क्रम Wilco Embedded Controller
 *
 * Copyright 2019 Google LLC
 *
 * The Wilco Embedded Controller can create custom events that
 * are not handled as standard ACPI objects. These events can
 * contain inक्रमmation about changes in EC controlled features,
 * such as errors and events in the करोck or display. For example,
 * an event is triggered अगर the करोck is plugged पूर्णांकo a display
 * incorrectly. These events are needed क्रम telemetry and
 * diagnostics reasons, and क्रम possibly alerting the user.

 * These events are triggered by the EC with an ACPI Notअगरy(0x90),
 * and then the BIOS पढ़ोs the event buffer from EC RAM via an
 * ACPI method. When the OS receives these events via ACPI,
 * it passes them aदीर्घ to this driver. The events are put पूर्णांकo
 * a queue which can be पढ़ो by a userspace daemon via a अक्षर device
 * that implements पढ़ो() and poll(). The event queue acts as a
 * circular buffer of size 64, so अगर there are no userspace consumers
 * the kernel will not run out of memory. The अक्षर device will appear at
 * /dev/wilco_eventअणुnपूर्ण, where n is some small non-negative पूर्णांकeger,
 * starting from 0. Standard ACPI events such as the battery getting
 * plugged/unplugged can also come through this path, but they are
 * dealt with via other paths, and are ignored here.

 * To test, you can tail the binary data with
 * $ cat /dev/wilco_event0 | hexdump -ve '1/1 "%x\n"'
 * and then create an event by plugging/unplugging the battery.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>

/* ACPI Notअगरy event code indicating event data is available. */
#घोषणा EC_ACPI_NOTIFY_EVENT		0x90
/* ACPI Method to execute to retrieve event data buffer from the EC. */
#घोषणा EC_ACPI_GET_EVENT		"QSET"
/* Maximum number of words in event data वापसed by the EC. */
#घोषणा EC_ACPI_MAX_EVENT_WORDS		6
#घोषणा EC_ACPI_MAX_EVENT_SIZE \
	(माप(काष्ठा ec_event) + (EC_ACPI_MAX_EVENT_WORDS) * माप(u16))

/* Node will appear in /dev/EVENT_DEV_NAME */
#घोषणा EVENT_DEV_NAME		"wilco_event"
#घोषणा EVENT_CLASS_NAME	EVENT_DEV_NAME
#घोषणा DRV_NAME		EVENT_DEV_NAME
#घोषणा EVENT_DEV_NAME_FMT	(EVENT_DEV_NAME "%d")
अटल काष्ठा class event_class = अणु
	.owner	= THIS_MODULE,
	.name	= EVENT_CLASS_NAME,
पूर्ण;

/* Keep track of all the device numbers used. */
#घोषणा EVENT_MAX_DEV 128
अटल पूर्णांक event_major;
अटल DEFINE_IDA(event_ida);

/* Size of circular queue of events. */
#घोषणा MAX_NUM_EVENTS 64

/**
 * काष्ठा ec_event - Extended event वापसed by the EC.
 * @size: Number of 16bit words in काष्ठाure after the size word.
 * @type: Extended event type, meaningless क्रम us.
 * @event: Event data words.  Max count is %EC_ACPI_MAX_EVENT_WORDS.
 */
काष्ठा ec_event अणु
	u16 size;
	u16 type;
	u16 event[];
पूर्ण __packed;

#घोषणा ec_event_num_words(ev) (ev->size - 1)
#घोषणा ec_event_size(ev) (माप(*ev) + (ec_event_num_words(ev) * माप(u16)))

/**
 * काष्ठा ec_event_queue - Circular queue क्रम events.
 * @capacity: Number of elements the queue can hold.
 * @head: Next index to ग_लिखो to.
 * @tail: Next index to पढ़ो from.
 * @entries: Array of events.
 */
काष्ठा ec_event_queue अणु
	पूर्णांक capacity;
	पूर्णांक head;
	पूर्णांक tail;
	काष्ठा ec_event *entries[];
पूर्ण;

/* Maximum number of events to store in ec_event_queue */
अटल पूर्णांक queue_size = 64;
module_param(queue_size, पूर्णांक, 0644);

अटल काष्ठा ec_event_queue *event_queue_new(पूर्णांक capacity)
अणु
	काष्ठा ec_event_queue *q;

	q = kzalloc(काष्ठा_size(q, entries, capacity), GFP_KERNEL);
	अगर (!q)
		वापस शून्य;

	q->capacity = capacity;

	वापस q;
पूर्ण

अटल अंतरभूत bool event_queue_empty(काष्ठा ec_event_queue *q)
अणु
	/* head==tail when both full and empty, but head==शून्य when empty */
	वापस q->head == q->tail && !q->entries[q->head];
पूर्ण

अटल अंतरभूत bool event_queue_full(काष्ठा ec_event_queue *q)
अणु
	/* head==tail when both full and empty, but head!=शून्य when full */
	वापस q->head == q->tail && q->entries[q->head];
पूर्ण

अटल काष्ठा ec_event *event_queue_pop(काष्ठा ec_event_queue *q)
अणु
	काष्ठा ec_event *ev;

	अगर (event_queue_empty(q))
		वापस शून्य;

	ev = q->entries[q->tail];
	q->entries[q->tail] = शून्य;
	q->tail = (q->tail + 1) % q->capacity;

	वापस ev;
पूर्ण

/*
 * If full, overग_लिखो the oldest event and वापस it so the caller
 * can kमुक्त it. If not full, वापस शून्य.
 */
अटल काष्ठा ec_event *event_queue_push(काष्ठा ec_event_queue *q,
					 काष्ठा ec_event *ev)
अणु
	काष्ठा ec_event *popped = शून्य;

	अगर (event_queue_full(q))
		popped = event_queue_pop(q);
	q->entries[q->head] = ev;
	q->head = (q->head + 1) % q->capacity;

	वापस popped;
पूर्ण

अटल व्योम event_queue_मुक्त(काष्ठा ec_event_queue *q)
अणु
	काष्ठा ec_event *event;

	जबतक ((event = event_queue_pop(q)) != शून्य)
		kमुक्त(event);

	kमुक्त(q);
पूर्ण

/**
 * काष्ठा event_device_data - Data क्रम a Wilco EC device that responds to ACPI.
 * @events: Circular queue of EC events to be provided to userspace.
 * @queue_lock: Protect the queue from simultaneous पढ़ो/ग_लिखोs.
 * @wq: Wait queue to notअगरy processes when events are available or the
 *	device has been हटाओd.
 * @cdev: Char dev that userspace पढ़ोs() and polls() from.
 * @dev: Device associated with the %cdev.
 * @exist: Has the device been not been हटाओd? Once a device has been हटाओd,
 *	   ग_लिखोs, पढ़ोs, and new खोलोs will fail.
 * @available: Guarantee only one client can खोलो() file and पढ़ो from queue.
 *
 * There will be one of these काष्ठाs क्रम each ACPI device रेजिस्टरed. This data
 * is the queue of events received from ACPI that still need to be पढ़ो from
 * userspace, the device and अक्षर device that userspace is using, a रुको queue
 * used to notअगरy dअगरferent thपढ़ोs when something has changed, plus a flag
 * on whether the ACPI device has been हटाओd.
 */
काष्ठा event_device_data अणु
	काष्ठा ec_event_queue *events;
	spinlock_t queue_lock;
	रुको_queue_head_t wq;
	काष्ठा device dev;
	काष्ठा cdev cdev;
	bool exist;
	atomic_t available;
पूर्ण;

/**
 * enqueue_events() - Place EC events in queue to be पढ़ो by userspace.
 * @adev: Device the events came from.
 * @buf: Buffer of event data.
 * @length: Length of event data buffer.
 *
 * %buf contains a number of ec_event's, packed one after the other.
 * Each ec_event is of variable length. Start with the first event, copy it
 * पूर्णांकo a persistent ec_event, store that entry in the queue, move on
 * to the next ec_event in buf, and repeat.
 *
 * Return: 0 on success or negative error code on failure.
 */
अटल पूर्णांक enqueue_events(काष्ठा acpi_device *adev, स्थिर u8 *buf, u32 length)
अणु
	काष्ठा event_device_data *dev_data = adev->driver_data;
	काष्ठा ec_event *event, *queue_event, *old_event;
	माप_प्रकार num_words, event_size;
	u32 offset = 0;

	जबतक (offset < length) अणु
		event = (काष्ठा ec_event *)(buf + offset);

		num_words = ec_event_num_words(event);
		event_size = ec_event_size(event);
		अगर (num_words > EC_ACPI_MAX_EVENT_WORDS) अणु
			dev_err(&adev->dev, "Too many event words: %zu > %d\n",
				num_words, EC_ACPI_MAX_EVENT_WORDS);
			वापस -EOVERFLOW;
		पूर्ण

		/* Ensure event करोes not overflow the available buffer */
		अगर ((offset + event_size) > length) अणु
			dev_err(&adev->dev, "Event exceeds buffer: %zu > %d\n",
				offset + event_size, length);
			वापस -EOVERFLOW;
		पूर्ण

		/* Poपूर्णांक to the next event in the buffer */
		offset += event_size;

		/* Copy event पूर्णांकo the queue */
		queue_event = kmemdup(event, event_size, GFP_KERNEL);
		अगर (!queue_event)
			वापस -ENOMEM;
		spin_lock(&dev_data->queue_lock);
		old_event = event_queue_push(dev_data->events, queue_event);
		spin_unlock(&dev_data->queue_lock);
		kमुक्त(old_event);
		wake_up_पूर्णांकerruptible(&dev_data->wq);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * event_device_notअगरy() - Callback when EC generates an event over ACPI.
 * @adev: The device that the event is coming from.
 * @value: Value passed to Notअगरy() in ACPI.
 *
 * This function will पढ़ो the events from the device and enqueue them.
 */
अटल व्योम event_device_notअगरy(काष्ठा acpi_device *adev, u32 value)
अणु
	काष्ठा acpi_buffer event_buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;
	acpi_status status;

	अगर (value != EC_ACPI_NOTIFY_EVENT) अणु
		dev_err(&adev->dev, "Invalid event: 0x%08x\n", value);
		वापस;
	पूर्ण

	/* Execute ACPI method to get event data buffer. */
	status = acpi_evaluate_object(adev->handle, EC_ACPI_GET_EVENT,
				      शून्य, &event_buffer);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&adev->dev, "Error executing ACPI method %s()\n",
			EC_ACPI_GET_EVENT);
		वापस;
	पूर्ण

	obj = (जोड़ acpi_object *)event_buffer.poपूर्णांकer;
	अगर (!obj) अणु
		dev_err(&adev->dev, "Nothing returned from %s()\n",
			EC_ACPI_GET_EVENT);
		वापस;
	पूर्ण
	अगर (obj->type != ACPI_TYPE_BUFFER) अणु
		dev_err(&adev->dev, "Invalid object returned from %s()\n",
			EC_ACPI_GET_EVENT);
		kमुक्त(obj);
		वापस;
	पूर्ण
	अगर (obj->buffer.length < माप(काष्ठा ec_event)) अणु
		dev_err(&adev->dev, "Invalid buffer length %d from %s()\n",
			obj->buffer.length, EC_ACPI_GET_EVENT);
		kमुक्त(obj);
		वापस;
	पूर्ण

	enqueue_events(adev, obj->buffer.poपूर्णांकer, obj->buffer.length);
	kमुक्त(obj);
पूर्ण

अटल पूर्णांक event_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा event_device_data *dev_data;

	dev_data = container_of(inode->i_cdev, काष्ठा event_device_data, cdev);
	अगर (!dev_data->exist)
		वापस -ENODEV;

	अगर (atomic_cmpxchg(&dev_data->available, 1, 0) == 0)
		वापस -EBUSY;

	/* Increase refcount on device so dev_data is not मुक्तd */
	get_device(&dev_data->dev);
	stream_खोलो(inode, filp);
	filp->निजी_data = dev_data;

	वापस 0;
पूर्ण

अटल __poll_t event_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा event_device_data *dev_data = filp->निजी_data;
	__poll_t mask = 0;

	poll_रुको(filp, &dev_data->wq, रुको);
	अगर (!dev_data->exist)
		वापस EPOLLHUP;
	अगर (!event_queue_empty(dev_data->events))
		mask |= EPOLLIN | EPOLLRDNORM | EPOLLPRI;
	वापस mask;
पूर्ण

/**
 * event_पढ़ो() - Callback क्रम passing event data to userspace via पढ़ो().
 * @filp: The file we are पढ़ोing from.
 * @buf: Poपूर्णांकer to userspace buffer to fill with one event.
 * @count: Number of bytes requested. Must be at least EC_ACPI_MAX_EVENT_SIZE.
 * @pos: File position poपूर्णांकer, irrelevant since we करोn't support seeking.
 *
 * Removes the first event from the queue, places it in the passed buffer.
 *
 * If there are no events in the the queue, then one of two things happens,
 * depending on अगर the file was खोलोed in nonblocking mode: If in nonblocking
 * mode, then वापस -EAGAIN to say there's no data. If in blocking mode, then
 * block until an event is available.
 *
 * Return: Number of bytes placed in buffer, negative error code on failure.
 */
अटल sमाप_प्रकार event_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
			  loff_t *pos)
अणु
	काष्ठा event_device_data *dev_data = filp->निजी_data;
	काष्ठा ec_event *event;
	sमाप_प्रकार n_bytes_written = 0;
	पूर्णांक err;

	/* We only will give them the entire event at once */
	अगर (count != 0 && count < EC_ACPI_MAX_EVENT_SIZE)
		वापस -EINVAL;

	spin_lock(&dev_data->queue_lock);
	जबतक (event_queue_empty(dev_data->events)) अणु
		spin_unlock(&dev_data->queue_lock);
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		err = रुको_event_पूर्णांकerruptible(dev_data->wq,
					!event_queue_empty(dev_data->events) ||
					!dev_data->exist);
		अगर (err)
			वापस err;

		/* Device was हटाओd as we रुकोed? */
		अगर (!dev_data->exist)
			वापस -ENODEV;
		spin_lock(&dev_data->queue_lock);
	पूर्ण
	event = event_queue_pop(dev_data->events);
	spin_unlock(&dev_data->queue_lock);
	n_bytes_written = ec_event_size(event);
	अगर (copy_to_user(buf, event, n_bytes_written))
		n_bytes_written = -EFAULT;
	kमुक्त(event);

	वापस n_bytes_written;
पूर्ण

अटल पूर्णांक event_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा event_device_data *dev_data = filp->निजी_data;

	atomic_set(&dev_data->available, 1);
	put_device(&dev_data->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations event_fops = अणु
	.खोलो = event_खोलो,
	.poll  = event_poll,
	.पढ़ो = event_पढ़ो,
	.release = event_release,
	.llseek = no_llseek,
	.owner = THIS_MODULE,
पूर्ण;

/**
 * मुक्त_device_data() - Callback to मुक्त the event_device_data काष्ठाure.
 * @d: The device embedded in our device data, which we have been ref counting.
 *
 * This is called only after event_device_हटाओ() has been called and all
 * userspace programs have called event_release() on all the खोलो file
 * descriptors.
 */
अटल व्योम मुक्त_device_data(काष्ठा device *d)
अणु
	काष्ठा event_device_data *dev_data;

	dev_data = container_of(d, काष्ठा event_device_data, dev);
	event_queue_मुक्त(dev_data->events);
	kमुक्त(dev_data);
पूर्ण

अटल व्योम hangup_device(काष्ठा event_device_data *dev_data)
अणु
	dev_data->exist = false;
	/* Wake up the रुकोing processes so they can बंद. */
	wake_up_पूर्णांकerruptible(&dev_data->wq);
	put_device(&dev_data->dev);
पूर्ण

/**
 * event_device_add() - Callback when creating a new device.
 * @adev: ACPI device that we will be receiving events from.
 *
 * This finds a मुक्त minor number क्रम the device, allocates and initializes
 * some device data, and creates a new device and अक्षर dev node.
 *
 * The device data is मुक्तd in मुक्त_device_data(), which is called when
 * %dev_data->dev is release()ed. This happens after all references to
 * %dev_data->dev are dropped, which happens once both event_device_हटाओ()
 * has been called and every खोलो()ed file descriptor has been release()ed.
 *
 * Return: 0 on success, negative error code on failure.
 */
अटल पूर्णांक event_device_add(काष्ठा acpi_device *adev)
अणु
	काष्ठा event_device_data *dev_data;
	पूर्णांक error, minor;

	minor = ida_alloc_max(&event_ida, EVENT_MAX_DEV-1, GFP_KERNEL);
	अगर (minor < 0) अणु
		error = minor;
		dev_err(&adev->dev, "Failed to find minor number: %d\n", error);
		वापस error;
	पूर्ण

	dev_data = kzalloc(माप(*dev_data), GFP_KERNEL);
	अगर (!dev_data) अणु
		error = -ENOMEM;
		जाओ मुक्त_minor;
	पूर्ण

	/* Initialize the device data. */
	adev->driver_data = dev_data;
	dev_data->events = event_queue_new(queue_size);
	अगर (!dev_data->events) अणु
		kमुक्त(dev_data);
		error = -ENOMEM;
		जाओ मुक्त_minor;
	पूर्ण
	spin_lock_init(&dev_data->queue_lock);
	init_रुकोqueue_head(&dev_data->wq);
	dev_data->exist = true;
	atomic_set(&dev_data->available, 1);

	/* Initialize the device. */
	dev_data->dev.devt = MKDEV(event_major, minor);
	dev_data->dev.class = &event_class;
	dev_data->dev.release = मुक्त_device_data;
	dev_set_name(&dev_data->dev, EVENT_DEV_NAME_FMT, minor);
	device_initialize(&dev_data->dev);

	/* Initialize the अक्षरacter device, and add it to userspace. */
	cdev_init(&dev_data->cdev, &event_fops);
	error = cdev_device_add(&dev_data->cdev, &dev_data->dev);
	अगर (error)
		जाओ मुक्त_dev_data;

	वापस 0;

मुक्त_dev_data:
	hangup_device(dev_data);
मुक्त_minor:
	ida_simple_हटाओ(&event_ida, minor);
	वापस error;
पूर्ण

अटल पूर्णांक event_device_हटाओ(काष्ठा acpi_device *adev)
अणु
	काष्ठा event_device_data *dev_data = adev->driver_data;

	cdev_device_del(&dev_data->cdev, &dev_data->dev);
	ida_simple_हटाओ(&event_ida, MINOR(dev_data->dev.devt));
	hangup_device(dev_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id event_acpi_ids[] = अणु
	अणु "GOOG000D", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, event_acpi_ids);

अटल काष्ठा acpi_driver event_driver = अणु
	.name = DRV_NAME,
	.class = DRV_NAME,
	.ids = event_acpi_ids,
	.ops = अणु
		.add = event_device_add,
		.notअगरy = event_device_notअगरy,
		.हटाओ = event_device_हटाओ,
	पूर्ण,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init event_module_init(व्योम)
अणु
	dev_t dev_num = 0;
	पूर्णांक ret;

	ret = class_रेजिस्टर(&event_class);
	अगर (ret) अणु
		pr_err(DRV_NAME ": Failed registering class: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Request device numbers, starting with minor=0. Save the major num. */
	ret = alloc_chrdev_region(&dev_num, 0, EVENT_MAX_DEV, EVENT_DEV_NAME);
	अगर (ret) अणु
		pr_err(DRV_NAME ": Failed allocating dev numbers: %d\n", ret);
		जाओ destroy_class;
	पूर्ण
	event_major = MAJOR(dev_num);

	ret = acpi_bus_रेजिस्टर_driver(&event_driver);
	अगर (ret < 0) अणु
		pr_err(DRV_NAME ": Failed registering driver: %d\n", ret);
		जाओ unरेजिस्टर_region;
	पूर्ण

	वापस 0;

unरेजिस्टर_region:
	unरेजिस्टर_chrdev_region(MKDEV(event_major, 0), EVENT_MAX_DEV);
destroy_class:
	class_unरेजिस्टर(&event_class);
	ida_destroy(&event_ida);
	वापस ret;
पूर्ण

अटल व्योम __निकास event_module_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&event_driver);
	unरेजिस्टर_chrdev_region(MKDEV(event_major, 0), EVENT_MAX_DEV);
	class_unरेजिस्टर(&event_class);
	ida_destroy(&event_ida);
पूर्ण

module_init(event_module_init);
module_निकास(event_module_निकास);

MODULE_AUTHOR("Nick Crews <ncrews@chromium.org>");
MODULE_DESCRIPTION("Wilco EC ACPI event driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
