<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Raw Gadget driver.
 * See Documentation/usb/raw-gadget.rst क्रम more details.
 *
 * Copyright (c) 2020 Google, Inc.
 * Author: Andrey Konovalov <andreyknvl@gmail.com>
 */

#समावेश <linux/compiler.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/kref.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>

#समावेश <linux/usb.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/ch11.h>
#समावेश <linux/usb/gadget.h>

#समावेश <uapi/linux/usb/raw_gadget.h>

#घोषणा	DRIVER_DESC "USB Raw Gadget"
#घोषणा DRIVER_NAME "raw-gadget"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Andrey Konovalov");
MODULE_LICENSE("GPL");

/*----------------------------------------------------------------------*/

#घोषणा RAW_EVENT_QUEUE_SIZE	16

काष्ठा raw_event_queue अणु
	/* See the comment in raw_event_queue_fetch() क्रम locking details. */
	spinlock_t		lock;
	काष्ठा semaphore	sema;
	काष्ठा usb_raw_event	*events[RAW_EVENT_QUEUE_SIZE];
	पूर्णांक			size;
पूर्ण;

अटल व्योम raw_event_queue_init(काष्ठा raw_event_queue *queue)
अणु
	spin_lock_init(&queue->lock);
	sema_init(&queue->sema, 0);
	queue->size = 0;
पूर्ण

अटल पूर्णांक raw_event_queue_add(काष्ठा raw_event_queue *queue,
	क्रमागत usb_raw_event_type type, माप_प्रकार length, स्थिर व्योम *data)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_raw_event *event;

	spin_lock_irqsave(&queue->lock, flags);
	अगर (WARN_ON(queue->size >= RAW_EVENT_QUEUE_SIZE)) अणु
		spin_unlock_irqrestore(&queue->lock, flags);
		वापस -ENOMEM;
	पूर्ण
	event = kदो_स्मृति(माप(*event) + length, GFP_ATOMIC);
	अगर (!event) अणु
		spin_unlock_irqrestore(&queue->lock, flags);
		वापस -ENOMEM;
	पूर्ण
	event->type = type;
	event->length = length;
	अगर (event->length)
		स_नकल(&event->data[0], data, length);
	queue->events[queue->size] = event;
	queue->size++;
	up(&queue->sema);
	spin_unlock_irqrestore(&queue->lock, flags);
	वापस 0;
पूर्ण

अटल काष्ठा usb_raw_event *raw_event_queue_fetch(
				काष्ठा raw_event_queue *queue)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_raw_event *event;

	/*
	 * This function can be called concurrently. We first check that
	 * there's at least one event queued by decrementing the semaphore,
	 * and then take the lock to protect queue काष्ठा fields.
	 */
	ret = करोwn_पूर्णांकerruptible(&queue->sema);
	अगर (ret)
		वापस ERR_PTR(ret);
	spin_lock_irqsave(&queue->lock, flags);
	/*
	 * queue->size must have the same value as queue->sema counter (beक्रमe
	 * the करोwn_पूर्णांकerruptible() call above), so this check is a fail-safe.
	 */
	अगर (WARN_ON(!queue->size)) अणु
		spin_unlock_irqrestore(&queue->lock, flags);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	event = queue->events[0];
	queue->size--;
	स_हटाओ(&queue->events[0], &queue->events[1],
			queue->size * माप(queue->events[0]));
	spin_unlock_irqrestore(&queue->lock, flags);
	वापस event;
पूर्ण

अटल व्योम raw_event_queue_destroy(काष्ठा raw_event_queue *queue)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < queue->size; i++)
		kमुक्त(queue->events[i]);
	queue->size = 0;
पूर्ण

/*----------------------------------------------------------------------*/

काष्ठा raw_dev;

क्रमागत ep_state अणु
	STATE_EP_DISABLED,
	STATE_EP_ENABLED,
पूर्ण;

काष्ठा raw_ep अणु
	काष्ठा raw_dev		*dev;
	क्रमागत ep_state		state;
	काष्ठा usb_ep		*ep;
	u8			addr;
	काष्ठा usb_request	*req;
	bool			urb_queued;
	bool			disabling;
	sमाप_प्रकार			status;
पूर्ण;

क्रमागत dev_state अणु
	STATE_DEV_INVALID = 0,
	STATE_DEV_OPENED,
	STATE_DEV_INITIALIZED,
	STATE_DEV_RUNNING,
	STATE_DEV_CLOSED,
	STATE_DEV_FAILED
पूर्ण;

काष्ठा raw_dev अणु
	काष्ठा kref			count;
	spinlock_t			lock;

	स्थिर अक्षर			*udc_name;
	काष्ठा usb_gadget_driver	driver;

	/* Reference to misc device: */
	काष्ठा device			*dev;

	/* Protected by lock: */
	क्रमागत dev_state			state;
	bool				gadget_रेजिस्टरed;
	काष्ठा usb_gadget		*gadget;
	काष्ठा usb_request		*req;
	bool				ep0_in_pending;
	bool				ep0_out_pending;
	bool				ep0_urb_queued;
	sमाप_प्रकार				ep0_status;
	काष्ठा raw_ep			eps[USB_RAW_EPS_NUM_MAX];
	पूर्णांक				eps_num;

	काष्ठा completion		ep0_करोne;
	काष्ठा raw_event_queue		queue;
पूर्ण;

अटल काष्ठा raw_dev *dev_new(व्योम)
अणु
	काष्ठा raw_dev *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;
	/* Matches kref_put() in raw_release(). */
	kref_init(&dev->count);
	spin_lock_init(&dev->lock);
	init_completion(&dev->ep0_करोne);
	raw_event_queue_init(&dev->queue);
	वापस dev;
पूर्ण

अटल व्योम dev_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा raw_dev *dev = container_of(kref, काष्ठा raw_dev, count);
	पूर्णांक i;

	kमुक्त(dev->udc_name);
	kमुक्त(dev->driver.udc_name);
	अगर (dev->req) अणु
		अगर (dev->ep0_urb_queued)
			usb_ep_dequeue(dev->gadget->ep0, dev->req);
		usb_ep_मुक्त_request(dev->gadget->ep0, dev->req);
	पूर्ण
	raw_event_queue_destroy(&dev->queue);
	क्रम (i = 0; i < dev->eps_num; i++) अणु
		अगर (dev->eps[i].state == STATE_EP_DISABLED)
			जारी;
		usb_ep_disable(dev->eps[i].ep);
		usb_ep_मुक्त_request(dev->eps[i].ep, dev->eps[i].req);
		kमुक्त(dev->eps[i].ep->desc);
		dev->eps[i].state = STATE_EP_DISABLED;
	पूर्ण
	kमुक्त(dev);
पूर्ण

/*----------------------------------------------------------------------*/

अटल पूर्णांक raw_queue_event(काष्ठा raw_dev *dev,
	क्रमागत usb_raw_event_type type, माप_प्रकार length, स्थिर व्योम *data)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	ret = raw_event_queue_add(&dev->queue, type, length, data);
	अगर (ret < 0) अणु
		spin_lock_irqsave(&dev->lock, flags);
		dev->state = STATE_DEV_FAILED;
		spin_unlock_irqrestore(&dev->lock, flags);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम gadget_ep0_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा raw_dev *dev = req->context;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (req->status)
		dev->ep0_status = req->status;
	अन्यथा
		dev->ep0_status = req->actual;
	अगर (dev->ep0_in_pending)
		dev->ep0_in_pending = false;
	अन्यथा
		dev->ep0_out_pending = false;
	spin_unlock_irqrestore(&dev->lock, flags);

	complete(&dev->ep0_करोne);
पूर्ण

अटल u8 get_ep_addr(स्थिर अक्षर *name)
अणु
	/* If the endpoपूर्णांक has fixed function (named as e.g. "ep12out-bulk"),
	 * parse the endpoपूर्णांक address from its name. We deliberately use
	 * deprecated simple_म_से_अदीर्घ() function here, as the number isn't
	 * followed by '\0' nor '\n'.
	 */
	अगर (है_अंक(name[2]))
		वापस simple_म_से_अदीर्घ(&name[2], शून्य, 10);
	/* Otherwise the endpoपूर्णांक is configurable (named as e.g. "ep-a"). */
	वापस USB_RAW_EP_ADDR_ANY;
पूर्ण

अटल पूर्णांक gadget_bind(काष्ठा usb_gadget *gadget,
			काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक ret = 0, i = 0;
	काष्ठा raw_dev *dev = container_of(driver, काष्ठा raw_dev, driver);
	काष्ठा usb_request *req;
	काष्ठा usb_ep *ep;
	अचिन्हित दीर्घ flags;

	अगर (म_भेद(gadget->name, dev->udc_name) != 0)
		वापस -ENODEV;

	set_gadget_data(gadget, dev);
	req = usb_ep_alloc_request(gadget->ep0, GFP_KERNEL);
	अगर (!req) अणु
		dev_err(&gadget->dev, "usb_ep_alloc_request failed\n");
		set_gadget_data(gadget, शून्य);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	dev->req = req;
	dev->req->context = dev;
	dev->req->complete = gadget_ep0_complete;
	dev->gadget = gadget;
	gadget_क्रम_each_ep(ep, dev->gadget) अणु
		dev->eps[i].ep = ep;
		dev->eps[i].addr = get_ep_addr(ep->name);
		dev->eps[i].state = STATE_EP_DISABLED;
		i++;
	पूर्ण
	dev->eps_num = i;
	spin_unlock_irqrestore(&dev->lock, flags);

	/* Matches kref_put() in gadget_unbind(). */
	kref_get(&dev->count);

	ret = raw_queue_event(dev, USB_RAW_EVENT_CONNECT, 0, शून्य);
	अगर (ret < 0)
		dev_err(&gadget->dev, "failed to queue event\n");

	वापस ret;
पूर्ण

अटल व्योम gadget_unbind(काष्ठा usb_gadget *gadget)
अणु
	काष्ठा raw_dev *dev = get_gadget_data(gadget);

	set_gadget_data(gadget, शून्य);
	/* Matches kref_get() in gadget_bind(). */
	kref_put(&dev->count, dev_मुक्त);
पूर्ण

अटल पूर्णांक gadget_setup(काष्ठा usb_gadget *gadget,
			स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	पूर्णांक ret = 0;
	काष्ठा raw_dev *dev = get_gadget_data(gadget);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_err(&gadget->dev, "ignoring, device is not running\n");
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->ep0_in_pending || dev->ep0_out_pending) अणु
		dev_dbg(&gadget->dev, "stalling, request already pending\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर ((ctrl->bRequestType & USB_सूची_IN) && ctrl->wLength)
		dev->ep0_in_pending = true;
	अन्यथा
		dev->ep0_out_pending = true;
	spin_unlock_irqrestore(&dev->lock, flags);

	ret = raw_queue_event(dev, USB_RAW_EVENT_CONTROL, माप(*ctrl), ctrl);
	अगर (ret < 0)
		dev_err(&gadget->dev, "failed to queue event\n");
	जाओ out;

out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
out:
	वापस ret;
पूर्ण

/* These are currently unused but present in हाल UDC driver requires them. */
अटल व्योम gadget_disconnect(काष्ठा usb_gadget *gadget) अणु पूर्ण
अटल व्योम gadget_suspend(काष्ठा usb_gadget *gadget) अणु पूर्ण
अटल व्योम gadget_resume(काष्ठा usb_gadget *gadget) अणु पूर्ण
अटल व्योम gadget_reset(काष्ठा usb_gadget *gadget) अणु पूर्ण

/*----------------------------------------------------------------------*/

अटल काष्ठा miscdevice raw_misc_device;

अटल पूर्णांक raw_खोलो(काष्ठा inode *inode, काष्ठा file *fd)
अणु
	काष्ठा raw_dev *dev;

	/* Nonblocking I/O is not supported yet. */
	अगर (fd->f_flags & O_NONBLOCK)
		वापस -EINVAL;

	dev = dev_new();
	अगर (!dev)
		वापस -ENOMEM;
	fd->निजी_data = dev;
	dev->state = STATE_DEV_OPENED;
	dev->dev = raw_misc_device.this_device;
	वापस 0;
पूर्ण

अटल पूर्णांक raw_release(काष्ठा inode *inode, काष्ठा file *fd)
अणु
	पूर्णांक ret = 0;
	काष्ठा raw_dev *dev = fd->निजी_data;
	अचिन्हित दीर्घ flags;
	bool unरेजिस्टर = false;

	spin_lock_irqsave(&dev->lock, flags);
	dev->state = STATE_DEV_CLOSED;
	अगर (!dev->gadget) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		जाओ out_put;
	पूर्ण
	अगर (dev->gadget_रेजिस्टरed)
		unरेजिस्टर = true;
	dev->gadget_रेजिस्टरed = false;
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (unरेजिस्टर) अणु
		ret = usb_gadget_unरेजिस्टर_driver(&dev->driver);
		अगर (ret != 0)
			dev_err(dev->dev,
				"usb_gadget_unregister_driver() failed with %d\n",
				ret);
		/* Matches kref_get() in raw_ioctl_run(). */
		kref_put(&dev->count, dev_मुक्त);
	पूर्ण

out_put:
	/* Matches dev_new() in raw_खोलो(). */
	kref_put(&dev->count, dev_मुक्त);
	वापस ret;
पूर्ण

/*----------------------------------------------------------------------*/

अटल पूर्णांक raw_ioctl_init(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	काष्ठा usb_raw_init arg;
	अक्षर *udc_driver_name;
	अक्षर *udc_device_name;
	अचिन्हित दीर्घ flags;

	अगर (copy_from_user(&arg, (व्योम __user *)value, माप(arg)))
		वापस -EFAULT;

	चयन (arg.speed) अणु
	हाल USB_SPEED_UNKNOWN:
		arg.speed = USB_SPEED_HIGH;
		अवरोध;
	हाल USB_SPEED_LOW:
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_SUPER:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	udc_driver_name = kदो_स्मृति(UDC_NAME_LENGTH_MAX, GFP_KERNEL);
	अगर (!udc_driver_name)
		वापस -ENOMEM;
	ret = strscpy(udc_driver_name, &arg.driver_name[0],
				UDC_NAME_LENGTH_MAX);
	अगर (ret < 0) अणु
		kमुक्त(udc_driver_name);
		वापस ret;
	पूर्ण
	ret = 0;

	udc_device_name = kदो_स्मृति(UDC_NAME_LENGTH_MAX, GFP_KERNEL);
	अगर (!udc_device_name) अणु
		kमुक्त(udc_driver_name);
		वापस -ENOMEM;
	पूर्ण
	ret = strscpy(udc_device_name, &arg.device_name[0],
				UDC_NAME_LENGTH_MAX);
	अगर (ret < 0) अणु
		kमुक्त(udc_driver_name);
		kमुक्त(udc_device_name);
		वापस ret;
	पूर्ण
	ret = 0;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_OPENED) अणु
		dev_dbg(dev->dev, "fail, device is not opened\n");
		kमुक्त(udc_driver_name);
		kमुक्त(udc_device_name);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	dev->udc_name = udc_driver_name;

	dev->driver.function = DRIVER_DESC;
	dev->driver.max_speed = arg.speed;
	dev->driver.setup = gadget_setup;
	dev->driver.disconnect = gadget_disconnect;
	dev->driver.bind = gadget_bind;
	dev->driver.unbind = gadget_unbind;
	dev->driver.suspend = gadget_suspend;
	dev->driver.resume = gadget_resume;
	dev->driver.reset = gadget_reset;
	dev->driver.driver.name = DRIVER_NAME;
	dev->driver.udc_name = udc_device_name;
	dev->driver.match_existing_only = 1;

	dev->state = STATE_DEV_INITIALIZED;

out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_run(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	अगर (value)
		वापस -EINVAL;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_INITIALIZED) अणु
		dev_dbg(dev->dev, "fail, device is not initialized\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	ret = usb_gadget_probe_driver(&dev->driver);

	spin_lock_irqsave(&dev->lock, flags);
	अगर (ret) अणु
		dev_err(dev->dev,
			"fail, usb_gadget_probe_driver returned %d\n", ret);
		dev->state = STATE_DEV_FAILED;
		जाओ out_unlock;
	पूर्ण
	dev->gadget_रेजिस्टरed = true;
	dev->state = STATE_DEV_RUNNING;
	/* Matches kref_put() in raw_release(). */
	kref_get(&dev->count);

out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_event_fetch(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	काष्ठा usb_raw_event arg;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_raw_event *event;
	uपूर्णांक32_t length;

	अगर (copy_from_user(&arg, (व्योम __user *)value, माप(arg)))
		वापस -EFAULT;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस -EINVAL;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	event = raw_event_queue_fetch(&dev->queue);
	अगर (PTR_ERR(event) == -EINTR) अणु
		dev_dbg(&dev->gadget->dev, "event fetching interrupted\n");
		वापस -EINTR;
	पूर्ण
	अगर (IS_ERR(event)) अणु
		dev_err(&dev->gadget->dev, "failed to fetch event\n");
		spin_lock_irqsave(&dev->lock, flags);
		dev->state = STATE_DEV_FAILED;
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस -ENODEV;
	पूर्ण
	length = min(arg.length, event->length);
	अगर (copy_to_user((व्योम __user *)value, event, माप(*event) + length)) अणु
		kमुक्त(event);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(event);
	वापस 0;
पूर्ण

अटल व्योम *raw_alloc_io_data(काष्ठा usb_raw_ep_io *io, व्योम __user *ptr,
				bool get_from_user)
अणु
	व्योम *data;

	अगर (copy_from_user(io, ptr, माप(*io)))
		वापस ERR_PTR(-EFAULT);
	अगर (io->ep >= USB_RAW_EPS_NUM_MAX)
		वापस ERR_PTR(-EINVAL);
	अगर (!usb_raw_io_flags_valid(io->flags))
		वापस ERR_PTR(-EINVAL);
	अगर (io->length > PAGE_SIZE)
		वापस ERR_PTR(-EINVAL);
	अगर (get_from_user)
		data = memdup_user(ptr + माप(*io), io->length);
	अन्यथा अणु
		data = kदो_स्मृति(io->length, GFP_KERNEL);
		अगर (!data)
			data = ERR_PTR(-ENOMEM);
	पूर्ण
	वापस data;
पूर्ण

अटल पूर्णांक raw_process_ep0_io(काष्ठा raw_dev *dev, काष्ठा usb_raw_ep_io *io,
				व्योम *data, bool in)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->ep0_urb_queued) अणु
		dev_dbg(&dev->gadget->dev, "fail, urb already queued\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर ((in && !dev->ep0_in_pending) ||
			(!in && !dev->ep0_out_pending)) अणु
		dev_dbg(&dev->gadget->dev, "fail, wrong direction\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (WARN_ON(in && dev->ep0_out_pending)) अणु
		ret = -ENODEV;
		dev->state = STATE_DEV_FAILED;
		जाओ out_करोne;
	पूर्ण
	अगर (WARN_ON(!in && dev->ep0_in_pending)) अणु
		ret = -ENODEV;
		dev->state = STATE_DEV_FAILED;
		जाओ out_करोne;
	पूर्ण

	dev->req->buf = data;
	dev->req->length = io->length;
	dev->req->zero = usb_raw_io_flags_zero(io->flags);
	dev->ep0_urb_queued = true;
	spin_unlock_irqrestore(&dev->lock, flags);

	ret = usb_ep_queue(dev->gadget->ep0, dev->req, GFP_KERNEL);
	अगर (ret) अणु
		dev_err(&dev->gadget->dev,
				"fail, usb_ep_queue returned %d\n", ret);
		spin_lock_irqsave(&dev->lock, flags);
		dev->state = STATE_DEV_FAILED;
		जाओ out_करोne;
	पूर्ण

	ret = रुको_क्रम_completion_पूर्णांकerruptible(&dev->ep0_करोne);
	अगर (ret) अणु
		dev_dbg(&dev->gadget->dev, "wait interrupted\n");
		usb_ep_dequeue(dev->gadget->ep0, dev->req);
		रुको_क्रम_completion(&dev->ep0_करोne);
		spin_lock_irqsave(&dev->lock, flags);
		जाओ out_करोne;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	ret = dev->ep0_status;

out_करोne:
	dev->ep0_urb_queued = false;
out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_ep0_ग_लिखो(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	व्योम *data;
	काष्ठा usb_raw_ep_io io;

	data = raw_alloc_io_data(&io, (व्योम __user *)value, true);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	ret = raw_process_ep0_io(dev, &io, data, true);
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_ep0_पढ़ो(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	व्योम *data;
	काष्ठा usb_raw_ep_io io;
	अचिन्हित पूर्णांक length;

	data = raw_alloc_io_data(&io, (व्योम __user *)value, false);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	ret = raw_process_ep0_io(dev, &io, data, false);
	अगर (ret < 0)
		जाओ मुक्त;

	length = min(io.length, (अचिन्हित पूर्णांक)ret);
	अगर (copy_to_user((व्योम __user *)(value + माप(io)), data, length))
		ret = -EFAULT;
	अन्यथा
		ret = length;
मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_ep0_stall(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	अगर (value)
		वापस -EINVAL;
	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->ep0_urb_queued) अणु
		dev_dbg(&dev->gadget->dev, "fail, urb already queued\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (!dev->ep0_in_pending && !dev->ep0_out_pending) अणु
		dev_dbg(&dev->gadget->dev, "fail, no request pending\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	ret = usb_ep_set_halt(dev->gadget->ep0);
	अगर (ret < 0)
		dev_err(&dev->gadget->dev,
				"fail, usb_ep_set_halt returned %d\n", ret);

	अगर (dev->ep0_in_pending)
		dev->ep0_in_pending = false;
	अन्यथा
		dev->ep0_out_pending = false;

out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_ep_enable(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0, i;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	काष्ठा raw_ep *ep;

	desc = memdup_user((व्योम __user *)value, माप(*desc));
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	/*
	 * Endpoपूर्णांकs with a maxpacket length of 0 can cause crashes in UDC
	 * drivers.
	 */
	अगर (usb_endpoपूर्णांक_maxp(desc) == 0) अणु
		dev_dbg(dev->dev, "fail, bad endpoint maxpacket\n");
		kमुक्त(desc);
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < dev->eps_num; i++) अणु
		ep = &dev->eps[i];
		अगर (ep->state != STATE_EP_DISABLED)
			जारी;
		अगर (ep->addr != usb_endpoपूर्णांक_num(desc) &&
				ep->addr != USB_RAW_EP_ADDR_ANY)
			जारी;
		अगर (!usb_gadget_ep_match_desc(dev->gadget, ep->ep, desc, शून्य))
			जारी;
		ep->ep->desc = desc;
		ret = usb_ep_enable(ep->ep);
		अगर (ret < 0) अणु
			dev_err(&dev->gadget->dev,
				"fail, usb_ep_enable returned %d\n", ret);
			जाओ out_मुक्त;
		पूर्ण
		ep->req = usb_ep_alloc_request(ep->ep, GFP_ATOMIC);
		अगर (!ep->req) अणु
			dev_err(&dev->gadget->dev,
				"fail, usb_ep_alloc_request failed\n");
			usb_ep_disable(ep->ep);
			ret = -ENOMEM;
			जाओ out_मुक्त;
		पूर्ण
		ep->state = STATE_EP_ENABLED;
		ep->ep->driver_data = ep;
		ret = i;
		जाओ out_unlock;
	पूर्ण

	dev_dbg(&dev->gadget->dev, "fail, no gadget endpoints available\n");
	ret = -EBUSY;

out_मुक्त:
	kमुक्त(desc);
out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_ep_disable(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0, i = value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (i < 0 || i >= dev->eps_num) अणु
		dev_dbg(dev->dev, "fail, invalid endpoint\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->eps[i].state == STATE_EP_DISABLED) अणु
		dev_dbg(&dev->gadget->dev, "fail, endpoint is not enabled\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->eps[i].disabling) अणु
		dev_dbg(&dev->gadget->dev,
				"fail, disable already in progress\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->eps[i].urb_queued) अणु
		dev_dbg(&dev->gadget->dev,
				"fail, waiting for urb completion\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	dev->eps[i].disabling = true;
	spin_unlock_irqrestore(&dev->lock, flags);

	usb_ep_disable(dev->eps[i].ep);

	spin_lock_irqsave(&dev->lock, flags);
	usb_ep_मुक्त_request(dev->eps[i].ep, dev->eps[i].req);
	kमुक्त(dev->eps[i].ep->desc);
	dev->eps[i].state = STATE_EP_DISABLED;
	dev->eps[i].disabling = false;

out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_ep_set_clear_halt_wedge(काष्ठा raw_dev *dev,
		अचिन्हित दीर्घ value, bool set, bool halt)
अणु
	पूर्णांक ret = 0, i = value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (i < 0 || i >= dev->eps_num) अणु
		dev_dbg(dev->dev, "fail, invalid endpoint\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->eps[i].state == STATE_EP_DISABLED) अणु
		dev_dbg(&dev->gadget->dev, "fail, endpoint is not enabled\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->eps[i].disabling) अणु
		dev_dbg(&dev->gadget->dev,
				"fail, disable is in progress\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (dev->eps[i].urb_queued) अणु
		dev_dbg(&dev->gadget->dev,
				"fail, waiting for urb completion\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (usb_endpoपूर्णांक_xfer_isoc(dev->eps[i].ep->desc)) अणु
		dev_dbg(&dev->gadget->dev,
				"fail, can't halt/wedge ISO endpoint\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (set && halt) अणु
		ret = usb_ep_set_halt(dev->eps[i].ep);
		अगर (ret < 0)
			dev_err(&dev->gadget->dev,
				"fail, usb_ep_set_halt returned %d\n", ret);
	पूर्ण अन्यथा अगर (!set && halt) अणु
		ret = usb_ep_clear_halt(dev->eps[i].ep);
		अगर (ret < 0)
			dev_err(&dev->gadget->dev,
				"fail, usb_ep_clear_halt returned %d\n", ret);
	पूर्ण अन्यथा अगर (set && !halt) अणु
		ret = usb_ep_set_wedge(dev->eps[i].ep);
		अगर (ret < 0)
			dev_err(&dev->gadget->dev,
				"fail, usb_ep_set_wedge returned %d\n", ret);
	पूर्ण

out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम gadget_ep_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा raw_ep *r_ep = (काष्ठा raw_ep *)ep->driver_data;
	काष्ठा raw_dev *dev = r_ep->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (req->status)
		r_ep->status = req->status;
	अन्यथा
		r_ep->status = req->actual;
	spin_unlock_irqrestore(&dev->lock, flags);

	complete((काष्ठा completion *)req->context);
पूर्ण

अटल पूर्णांक raw_process_ep_io(काष्ठा raw_dev *dev, काष्ठा usb_raw_ep_io *io,
				व्योम *data, bool in)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा raw_ep *ep;
	DECLARE_COMPLETION_ONSTACK(करोne);

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (io->ep >= dev->eps_num) अणु
		dev_dbg(&dev->gadget->dev, "fail, invalid endpoint\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	ep = &dev->eps[io->ep];
	अगर (ep->state != STATE_EP_ENABLED) अणु
		dev_dbg(&dev->gadget->dev, "fail, endpoint is not enabled\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (ep->disabling) अणु
		dev_dbg(&dev->gadget->dev,
				"fail, endpoint is already being disabled\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर (ep->urb_queued) अणु
		dev_dbg(&dev->gadget->dev, "fail, urb already queued\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	अगर ((in && !ep->ep->caps.dir_in) || (!in && ep->ep->caps.dir_in)) अणु
		dev_dbg(&dev->gadget->dev, "fail, wrong direction\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ep->dev = dev;
	ep->req->context = &करोne;
	ep->req->complete = gadget_ep_complete;
	ep->req->buf = data;
	ep->req->length = io->length;
	ep->req->zero = usb_raw_io_flags_zero(io->flags);
	ep->urb_queued = true;
	spin_unlock_irqrestore(&dev->lock, flags);

	ret = usb_ep_queue(ep->ep, ep->req, GFP_KERNEL);
	अगर (ret) अणु
		dev_err(&dev->gadget->dev,
				"fail, usb_ep_queue returned %d\n", ret);
		spin_lock_irqsave(&dev->lock, flags);
		dev->state = STATE_DEV_FAILED;
		जाओ out_करोne;
	पूर्ण

	ret = रुको_क्रम_completion_पूर्णांकerruptible(&करोne);
	अगर (ret) अणु
		dev_dbg(&dev->gadget->dev, "wait interrupted\n");
		usb_ep_dequeue(ep->ep, ep->req);
		रुको_क्रम_completion(&करोne);
		spin_lock_irqsave(&dev->lock, flags);
		जाओ out_करोne;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	ret = ep->status;

out_करोne:
	ep->urb_queued = false;
out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_ep_ग_लिखो(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	अक्षर *data;
	काष्ठा usb_raw_ep_io io;

	data = raw_alloc_io_data(&io, (व्योम __user *)value, true);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	ret = raw_process_ep_io(dev, &io, data, true);
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_ep_पढ़ो(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	अक्षर *data;
	काष्ठा usb_raw_ep_io io;
	अचिन्हित पूर्णांक length;

	data = raw_alloc_io_data(&io, (व्योम __user *)value, false);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);
	ret = raw_process_ep_io(dev, &io, data, false);
	अगर (ret < 0)
		जाओ मुक्त;

	length = min(io.length, (अचिन्हित पूर्णांक)ret);
	अगर (copy_to_user((व्योम __user *)(value + माप(io)), data, length))
		ret = -EFAULT;
	अन्यथा
		ret = length;
मुक्त:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_configure(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	अगर (value)
		वापस -EINVAL;
	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	usb_gadget_set_state(dev->gadget, USB_STATE_CONFIGURED);

out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक raw_ioctl_vbus_draw(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	usb_gadget_vbus_draw(dev->gadget, 2 * value);

out_unlock:
	spin_unlock_irqrestore(&dev->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम fill_ep_caps(काष्ठा usb_ep_caps *caps,
				काष्ठा usb_raw_ep_caps *raw_caps)
अणु
	raw_caps->type_control = caps->type_control;
	raw_caps->type_iso = caps->type_iso;
	raw_caps->type_bulk = caps->type_bulk;
	raw_caps->type_पूर्णांक = caps->type_पूर्णांक;
	raw_caps->dir_in = caps->dir_in;
	raw_caps->dir_out = caps->dir_out;
पूर्ण

अटल व्योम fill_ep_limits(काष्ठा usb_ep *ep, काष्ठा usb_raw_ep_limits *limits)
अणु
	limits->maxpacket_limit = ep->maxpacket_limit;
	limits->max_streams = ep->max_streams;
पूर्ण

अटल पूर्णांक raw_ioctl_eps_info(काष्ठा raw_dev *dev, अचिन्हित दीर्घ value)
अणु
	पूर्णांक ret = 0, i;
	अचिन्हित दीर्घ flags;
	काष्ठा usb_raw_eps_info *info;
	काष्ठा raw_ep *ep;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->state != STATE_DEV_RUNNING) अणु
		dev_dbg(dev->dev, "fail, device is not running\n");
		ret = -EINVAL;
		spin_unlock_irqrestore(&dev->lock, flags);
		जाओ out_मुक्त;
	पूर्ण
	अगर (!dev->gadget) अणु
		dev_dbg(dev->dev, "fail, gadget is not bound\n");
		ret = -EBUSY;
		spin_unlock_irqrestore(&dev->lock, flags);
		जाओ out_मुक्त;
	पूर्ण

	स_रखो(info, 0, माप(*info));
	क्रम (i = 0; i < dev->eps_num; i++) अणु
		ep = &dev->eps[i];
		strscpy(&info->eps[i].name[0], ep->ep->name,
				USB_RAW_EP_NAME_MAX);
		info->eps[i].addr = ep->addr;
		fill_ep_caps(&ep->ep->caps, &info->eps[i].caps);
		fill_ep_limits(ep->ep, &info->eps[i].limits);
	पूर्ण
	ret = dev->eps_num;
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (copy_to_user((व्योम __user *)value, info, माप(*info)))
		ret = -EFAULT;

out_मुक्त:
	kमुक्त(info);
out:
	वापस ret;
पूर्ण

अटल दीर्घ raw_ioctl(काष्ठा file *fd, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ value)
अणु
	काष्ठा raw_dev *dev = fd->निजी_data;
	पूर्णांक ret = 0;

	अगर (!dev)
		वापस -EBUSY;

	चयन (cmd) अणु
	हाल USB_RAW_IOCTL_INIT:
		ret = raw_ioctl_init(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_RUN:
		ret = raw_ioctl_run(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EVENT_FETCH:
		ret = raw_ioctl_event_fetch(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EP0_WRITE:
		ret = raw_ioctl_ep0_ग_लिखो(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EP0_READ:
		ret = raw_ioctl_ep0_पढ़ो(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EP_ENABLE:
		ret = raw_ioctl_ep_enable(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EP_DISABLE:
		ret = raw_ioctl_ep_disable(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EP_WRITE:
		ret = raw_ioctl_ep_ग_लिखो(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EP_READ:
		ret = raw_ioctl_ep_पढ़ो(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_CONFIGURE:
		ret = raw_ioctl_configure(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_VBUS_DRAW:
		ret = raw_ioctl_vbus_draw(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EPS_INFO:
		ret = raw_ioctl_eps_info(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EP0_STALL:
		ret = raw_ioctl_ep0_stall(dev, value);
		अवरोध;
	हाल USB_RAW_IOCTL_EP_SET_HALT:
		ret = raw_ioctl_ep_set_clear_halt_wedge(
					dev, value, true, true);
		अवरोध;
	हाल USB_RAW_IOCTL_EP_CLEAR_HALT:
		ret = raw_ioctl_ep_set_clear_halt_wedge(
					dev, value, false, true);
		अवरोध;
	हाल USB_RAW_IOCTL_EP_SET_WEDGE:
		ret = raw_ioctl_ep_set_clear_halt_wedge(
					dev, value, true, false);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/*----------------------------------------------------------------------*/

अटल स्थिर काष्ठा file_operations raw_fops = अणु
	.खोलो =			raw_खोलो,
	.unlocked_ioctl =	raw_ioctl,
	.compat_ioctl =		raw_ioctl,
	.release =		raw_release,
	.llseek =		no_llseek,
पूर्ण;

अटल काष्ठा miscdevice raw_misc_device = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = DRIVER_NAME,
	.fops = &raw_fops,
पूर्ण;

module_misc_device(raw_misc_device);
