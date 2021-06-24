<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Skeleton driver - 2.2
 *
 * Copyright (C) 2001-2004 Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * This driver is based on the 2.6.3 version of drivers/usb/usb-skeleton.c
 * but has been rewritten to be easier to पढ़ो and use.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>


/* Define these values to match your devices */
#घोषणा USB_SKEL_VENDOR_ID	0xfff0
#घोषणा USB_SKEL_PRODUCT_ID	0xfff0

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id skel_table[] = अणु
	अणु USB_DEVICE(USB_SKEL_VENDOR_ID, USB_SKEL_PRODUCT_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, skel_table);


/* Get a minor range क्रम your devices from the usb मुख्यtainer */
#घोषणा USB_SKEL_MINOR_BASE	192

/* our निजी defines. अगर this grows any larger, use your own .h file */
#घोषणा MAX_TRANSFER		(PAGE_SIZE - 512)
/*
 * MAX_TRANSFER is chosen so that the VM is not stressed by
 * allocations > PAGE_SIZE and the number of packets in a page
 * is an पूर्णांकeger 512 is the largest possible packet on EHCI
 */
#घोषणा WRITES_IN_FLIGHT	8
/* arbitrarily chosen */

/* Structure to hold all of our device specअगरic stuff */
काष्ठा usb_skel अणु
	काष्ठा usb_device	*udev;			/* the usb device क्रम this device */
	काष्ठा usb_पूर्णांकerface	*पूर्णांकerface;		/* the पूर्णांकerface क्रम this device */
	काष्ठा semaphore	limit_sem;		/* limiting the number of ग_लिखोs in progress */
	काष्ठा usb_anchor	submitted;		/* in हाल we need to retract our submissions */
	काष्ठा urb		*bulk_in_urb;		/* the urb to पढ़ो data with */
	अचिन्हित अक्षर           *bulk_in_buffer;	/* the buffer to receive data */
	माप_प्रकार			bulk_in_size;		/* the size of the receive buffer */
	माप_प्रकार			bulk_in_filled;		/* number of bytes in the buffer */
	माप_प्रकार			bulk_in_copied;		/* alपढ़ोy copied to user space */
	__u8			bulk_in_endpoपूर्णांकAddr;	/* the address of the bulk in endpoपूर्णांक */
	__u8			bulk_out_endpoपूर्णांकAddr;	/* the address of the bulk out endpoपूर्णांक */
	पूर्णांक			errors;			/* the last request tanked */
	bool			ongoing_पढ़ो;		/* a पढ़ो is going on */
	spinlock_t		err_lock;		/* lock क्रम errors */
	काष्ठा kref		kref;
	काष्ठा mutex		io_mutex;		/* synchronize I/O with disconnect */
	अचिन्हित दीर्घ		disconnected:1;
	रुको_queue_head_t	bulk_in_रुको;		/* to रुको क्रम an ongoing पढ़ो */
पूर्ण;
#घोषणा to_skel_dev(d) container_of(d, काष्ठा usb_skel, kref)

अटल काष्ठा usb_driver skel_driver;
अटल व्योम skel_draw_करोwn(काष्ठा usb_skel *dev);

अटल व्योम skel_delete(काष्ठा kref *kref)
अणु
	काष्ठा usb_skel *dev = to_skel_dev(kref);

	usb_मुक्त_urb(dev->bulk_in_urb);
	usb_put_पूर्णांकf(dev->पूर्णांकerface);
	usb_put_dev(dev->udev);
	kमुक्त(dev->bulk_in_buffer);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक skel_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_skel *dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक subminor;
	पूर्णांक retval = 0;

	subminor = iminor(inode);

	पूर्णांकerface = usb_find_पूर्णांकerface(&skel_driver, subminor);
	अगर (!पूर्णांकerface) अणु
		pr_err("%s - error, can't find device for minor %d\n",
			__func__, subminor);
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	retval = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकerface);
	अगर (retval)
		जाओ निकास;

	/* increment our usage count क्रम the device */
	kref_get(&dev->kref);

	/* save our object in the file's निजी काष्ठाure */
	file->निजी_data = dev;

निकास:
	वापस retval;
पूर्ण

अटल पूर्णांक skel_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_skel *dev;

	dev = file->निजी_data;
	अगर (dev == शून्य)
		वापस -ENODEV;

	/* allow the device to be स्वतःsuspended */
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकerface);

	/* decrement the count on our device */
	kref_put(&dev->kref, skel_delete);
	वापस 0;
पूर्ण

अटल पूर्णांक skel_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा usb_skel *dev;
	पूर्णांक res;

	dev = file->निजी_data;
	अगर (dev == शून्य)
		वापस -ENODEV;

	/* रुको क्रम io to stop */
	mutex_lock(&dev->io_mutex);
	skel_draw_करोwn(dev);

	/* पढ़ो out errors, leave subsequent खोलोs a clean slate */
	spin_lock_irq(&dev->err_lock);
	res = dev->errors ? (dev->errors == -EPIPE ? -EPIPE : -EIO) : 0;
	dev->errors = 0;
	spin_unlock_irq(&dev->err_lock);

	mutex_unlock(&dev->io_mutex);

	वापस res;
पूर्ण

अटल व्योम skel_पढ़ो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_skel *dev;
	अचिन्हित दीर्घ flags;

	dev = urb->context;

	spin_lock_irqsave(&dev->err_lock, flags);
	/* sync/async unlink faults aren't errors */
	अगर (urb->status) अणु
		अगर (!(urb->status == -ENOENT ||
		    urb->status == -ECONNRESET ||
		    urb->status == -ESHUTDOWN))
			dev_err(&dev->पूर्णांकerface->dev,
				"%s - nonzero write bulk status received: %d\n",
				__func__, urb->status);

		dev->errors = urb->status;
	पूर्ण अन्यथा अणु
		dev->bulk_in_filled = urb->actual_length;
	पूर्ण
	dev->ongoing_पढ़ो = 0;
	spin_unlock_irqrestore(&dev->err_lock, flags);

	wake_up_पूर्णांकerruptible(&dev->bulk_in_रुको);
पूर्ण

अटल पूर्णांक skel_करो_पढ़ो_io(काष्ठा usb_skel *dev, माप_प्रकार count)
अणु
	पूर्णांक rv;

	/* prepare a पढ़ो */
	usb_fill_bulk_urb(dev->bulk_in_urb,
			dev->udev,
			usb_rcvbulkpipe(dev->udev,
				dev->bulk_in_endpoपूर्णांकAddr),
			dev->bulk_in_buffer,
			min(dev->bulk_in_size, count),
			skel_पढ़ो_bulk_callback,
			dev);
	/* tell everybody to leave the URB alone */
	spin_lock_irq(&dev->err_lock);
	dev->ongoing_पढ़ो = 1;
	spin_unlock_irq(&dev->err_lock);

	/* submit bulk in urb, which means no data to deliver */
	dev->bulk_in_filled = 0;
	dev->bulk_in_copied = 0;

	/* करो it */
	rv = usb_submit_urb(dev->bulk_in_urb, GFP_KERNEL);
	अगर (rv < 0) अणु
		dev_err(&dev->पूर्णांकerface->dev,
			"%s - failed submitting read urb, error %d\n",
			__func__, rv);
		rv = (rv == -ENOMEM) ? rv : -EIO;
		spin_lock_irq(&dev->err_lock);
		dev->ongoing_पढ़ो = 0;
		spin_unlock_irq(&dev->err_lock);
	पूर्ण

	वापस rv;
पूर्ण

अटल sमाप_प्रकार skel_पढ़ो(काष्ठा file *file, अक्षर *buffer, माप_प्रकार count,
			 loff_t *ppos)
अणु
	काष्ठा usb_skel *dev;
	पूर्णांक rv;
	bool ongoing_io;

	dev = file->निजी_data;

	अगर (!count)
		वापस 0;

	/* no concurrent पढ़ोers */
	rv = mutex_lock_पूर्णांकerruptible(&dev->io_mutex);
	अगर (rv < 0)
		वापस rv;

	अगर (dev->disconnected) अणु		/* disconnect() was called */
		rv = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* अगर IO is under way, we must not touch things */
retry:
	spin_lock_irq(&dev->err_lock);
	ongoing_io = dev->ongoing_पढ़ो;
	spin_unlock_irq(&dev->err_lock);

	अगर (ongoing_io) अणु
		/* nonblocking IO shall not रुको */
		अगर (file->f_flags & O_NONBLOCK) अणु
			rv = -EAGAIN;
			जाओ निकास;
		पूर्ण
		/*
		 * IO may take क्रमever
		 * hence रुको in an पूर्णांकerruptible state
		 */
		rv = रुको_event_पूर्णांकerruptible(dev->bulk_in_रुको, (!dev->ongoing_पढ़ो));
		अगर (rv < 0)
			जाओ निकास;
	पूर्ण

	/* errors must be reported */
	rv = dev->errors;
	अगर (rv < 0) अणु
		/* any error is reported once */
		dev->errors = 0;
		/* to preserve notअगरications about reset */
		rv = (rv == -EPIPE) ? rv : -EIO;
		/* report it */
		जाओ निकास;
	पूर्ण

	/*
	 * अगर the buffer is filled we may satisfy the पढ़ो
	 * अन्यथा we need to start IO
	 */

	अगर (dev->bulk_in_filled) अणु
		/* we had पढ़ो data */
		माप_प्रकार available = dev->bulk_in_filled - dev->bulk_in_copied;
		माप_प्रकार chunk = min(available, count);

		अगर (!available) अणु
			/*
			 * all data has been used
			 * actual IO needs to be करोne
			 */
			rv = skel_करो_पढ़ो_io(dev, count);
			अगर (rv < 0)
				जाओ निकास;
			अन्यथा
				जाओ retry;
		पूर्ण
		/*
		 * data is available
		 * chunk tells us how much shall be copied
		 */

		अगर (copy_to_user(buffer,
				 dev->bulk_in_buffer + dev->bulk_in_copied,
				 chunk))
			rv = -EFAULT;
		अन्यथा
			rv = chunk;

		dev->bulk_in_copied += chunk;

		/*
		 * अगर we are asked क्रम more than we have,
		 * we start IO but करोn't रुको
		 */
		अगर (available < count)
			skel_करो_पढ़ो_io(dev, count - chunk);
	पूर्ण अन्यथा अणु
		/* no data in the buffer */
		rv = skel_करो_पढ़ो_io(dev, count);
		अगर (rv < 0)
			जाओ निकास;
		अन्यथा
			जाओ retry;
	पूर्ण
निकास:
	mutex_unlock(&dev->io_mutex);
	वापस rv;
पूर्ण

अटल व्योम skel_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_skel *dev;
	अचिन्हित दीर्घ flags;

	dev = urb->context;

	/* sync/async unlink faults aren't errors */
	अगर (urb->status) अणु
		अगर (!(urb->status == -ENOENT ||
		    urb->status == -ECONNRESET ||
		    urb->status == -ESHUTDOWN))
			dev_err(&dev->पूर्णांकerface->dev,
				"%s - nonzero write bulk status received: %d\n",
				__func__, urb->status);

		spin_lock_irqsave(&dev->err_lock, flags);
		dev->errors = urb->status;
		spin_unlock_irqrestore(&dev->err_lock, flags);
	पूर्ण

	/* मुक्त up our allocated buffer */
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	up(&dev->limit_sem);
पूर्ण

अटल sमाप_प्रकार skel_ग_लिखो(काष्ठा file *file, स्थिर अक्षर *user_buffer,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा usb_skel *dev;
	पूर्णांक retval = 0;
	काष्ठा urb *urb = शून्य;
	अक्षर *buf = शून्य;
	माप_प्रकार ग_लिखोsize = min(count, (माप_प्रकार)MAX_TRANSFER);

	dev = file->निजी_data;

	/* verअगरy that we actually have some data to ग_लिखो */
	अगर (count == 0)
		जाओ निकास;

	/*
	 * limit the number of URBs in flight to stop a user from using up all
	 * RAM
	 */
	अगर (!(file->f_flags & O_NONBLOCK)) अणु
		अगर (करोwn_पूर्णांकerruptible(&dev->limit_sem)) अणु
			retval = -ERESTARTSYS;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (करोwn_trylock(&dev->limit_sem)) अणु
			retval = -EAGAIN;
			जाओ निकास;
		पूर्ण
	पूर्ण

	spin_lock_irq(&dev->err_lock);
	retval = dev->errors;
	अगर (retval < 0) अणु
		/* any error is reported once */
		dev->errors = 0;
		/* to preserve notअगरications about reset */
		retval = (retval == -EPIPE) ? retval : -EIO;
	पूर्ण
	spin_unlock_irq(&dev->err_lock);
	अगर (retval < 0)
		जाओ error;

	/* create a urb, and a buffer क्रम it, and copy the data to the urb */
	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	buf = usb_alloc_coherent(dev->udev, ग_लिखोsize, GFP_KERNEL,
				 &urb->transfer_dma);
	अगर (!buf) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (copy_from_user(buf, user_buffer, ग_लिखोsize)) अणु
		retval = -EFAULT;
		जाओ error;
	पूर्ण

	/* this lock makes sure we करोn't submit URBs to gone devices */
	mutex_lock(&dev->io_mutex);
	अगर (dev->disconnected) अणु		/* disconnect() was called */
		mutex_unlock(&dev->io_mutex);
		retval = -ENODEV;
		जाओ error;
	पूर्ण

	/* initialize the urb properly */
	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, dev->bulk_out_endpoपूर्णांकAddr),
			  buf, ग_लिखोsize, skel_ग_लिखो_bulk_callback, dev);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &dev->submitted);

	/* send the data out the bulk port */
	retval = usb_submit_urb(urb, GFP_KERNEL);
	mutex_unlock(&dev->io_mutex);
	अगर (retval) अणु
		dev_err(&dev->पूर्णांकerface->dev,
			"%s - failed submitting write urb, error %d\n",
			__func__, retval);
		जाओ error_unanchor;
	पूर्ण

	/*
	 * release our reference to this urb, the USB core will eventually मुक्त
	 * it entirely
	 */
	usb_मुक्त_urb(urb);


	वापस ग_लिखोsize;

error_unanchor:
	usb_unanchor_urb(urb);
error:
	अगर (urb) अणु
		usb_मुक्त_coherent(dev->udev, ग_लिखोsize, buf, urb->transfer_dma);
		usb_मुक्त_urb(urb);
	पूर्ण
	up(&dev->limit_sem);

निकास:
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations skel_fops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		skel_पढ़ो,
	.ग_लिखो =	skel_ग_लिखो,
	.खोलो =		skel_खोलो,
	.release =	skel_release,
	.flush =	skel_flush,
	.llseek =	noop_llseek,
पूर्ण;

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device रेजिस्टरed with the driver core
 */
अटल काष्ठा usb_class_driver skel_class = अणु
	.name =		"skel%d",
	.fops =		&skel_fops,
	.minor_base =	USB_SKEL_MINOR_BASE,
पूर्ण;

अटल पूर्णांक skel_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		      स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_skel *dev;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_in, *bulk_out;
	पूर्णांक retval;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	kref_init(&dev->kref);
	sema_init(&dev->limit_sem, WRITES_IN_FLIGHT);
	mutex_init(&dev->io_mutex);
	spin_lock_init(&dev->err_lock);
	init_usb_anchor(&dev->submitted);
	init_रुकोqueue_head(&dev->bulk_in_रुको);

	dev->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	dev->पूर्णांकerface = usb_get_पूर्णांकf(पूर्णांकerface);

	/* set up the endpoपूर्णांक inक्रमmation */
	/* use only the first bulk-in and bulk-out endpoपूर्णांकs */
	retval = usb_find_common_endpoपूर्णांकs(पूर्णांकerface->cur_altsetting,
			&bulk_in, &bulk_out, शून्य, शून्य);
	अगर (retval) अणु
		dev_err(&पूर्णांकerface->dev,
			"Could not find both bulk-in and bulk-out endpoints\n");
		जाओ error;
	पूर्ण

	dev->bulk_in_size = usb_endpoपूर्णांक_maxp(bulk_in);
	dev->bulk_in_endpoपूर्णांकAddr = bulk_in->bEndpoपूर्णांकAddress;
	dev->bulk_in_buffer = kदो_स्मृति(dev->bulk_in_size, GFP_KERNEL);
	अगर (!dev->bulk_in_buffer) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण
	dev->bulk_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->bulk_in_urb) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	dev->bulk_out_endpoपूर्णांकAddr = bulk_out->bEndpoपूर्णांकAddress;

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	retval = usb_रेजिस्टर_dev(पूर्णांकerface, &skel_class);
	अगर (retval) अणु
		/* something prevented us from रेजिस्टरing this driver */
		dev_err(&पूर्णांकerface->dev,
			"Not able to get a minor for this device.\n");
		usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
		जाओ error;
	पूर्ण

	/* let the user know what node this device is now attached to */
	dev_info(&पूर्णांकerface->dev,
		 "USB Skeleton device now attached to USBSkel-%d",
		 पूर्णांकerface->minor);
	वापस 0;

error:
	/* this मुक्तs allocated memory */
	kref_put(&dev->kref, skel_delete);

	वापस retval;
पूर्ण

अटल व्योम skel_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_skel *dev;
	पूर्णांक minor = पूर्णांकerface->minor;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	/* give back our minor */
	usb_deरेजिस्टर_dev(पूर्णांकerface, &skel_class);

	/* prevent more I/O from starting */
	mutex_lock(&dev->io_mutex);
	dev->disconnected = 1;
	mutex_unlock(&dev->io_mutex);

	usb_समाप्त_urb(dev->bulk_in_urb);
	usb_समाप्त_anchored_urbs(&dev->submitted);

	/* decrement our usage count */
	kref_put(&dev->kref, skel_delete);

	dev_info(&पूर्णांकerface->dev, "USB Skeleton #%d now disconnected", minor);
पूर्ण

अटल व्योम skel_draw_करोwn(काष्ठा usb_skel *dev)
अणु
	पूर्णांक समय;

	समय = usb_रुको_anchor_empty_समयout(&dev->submitted, 1000);
	अगर (!समय)
		usb_समाप्त_anchored_urbs(&dev->submitted);
	usb_समाप्त_urb(dev->bulk_in_urb);
पूर्ण

अटल पूर्णांक skel_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usb_skel *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!dev)
		वापस 0;
	skel_draw_करोwn(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक skel_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक skel_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_skel *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&dev->io_mutex);
	skel_draw_करोwn(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक skel_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_skel *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	/* we are sure no URBs are active - no locking needed */
	dev->errors = -EPIPE;
	mutex_unlock(&dev->io_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा usb_driver skel_driver = अणु
	.name =		"skeleton",
	.probe =	skel_probe,
	.disconnect =	skel_disconnect,
	.suspend =	skel_suspend,
	.resume =	skel_resume,
	.pre_reset =	skel_pre_reset,
	.post_reset =	skel_post_reset,
	.id_table =	skel_table,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(skel_driver);

MODULE_LICENSE("GPL v2");
