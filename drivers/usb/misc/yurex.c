<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Meywa-Denki & KAYAC YUREX
 *
 * Copyright (C) 2010 Tomoki Sekiyama (tomoki.sekiyama@gmail.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/hid.h>

#घोषणा DRIVER_AUTHOR "Tomoki Sekiyama"
#घोषणा DRIVER_DESC "Driver for Meywa-Denki & KAYAC YUREX"

#घोषणा YUREX_VENDOR_ID		0x0c45
#घोषणा YUREX_PRODUCT_ID	0x1010

#घोषणा CMD_ACK		'!'
#घोषणा CMD_ANIMATE	'A'
#घोषणा CMD_COUNT	'C'
#घोषणा CMD_LED		'L'
#घोषणा CMD_READ	'R'
#घोषणा CMD_SET		'S'
#घोषणा CMD_VERSION	'V'
#घोषणा CMD_खातापूर्ण		0x0d
#घोषणा CMD_PADDING	0xff

#घोषणा YUREX_BUF_SIZE		8
#घोषणा YUREX_WRITE_TIMEOUT	(HZ*2)

/* table of devices that work with this driver */
अटल काष्ठा usb_device_id yurex_table[] = अणु
	अणु USB_DEVICE(YUREX_VENDOR_ID, YUREX_PRODUCT_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, yurex_table);

#अगर_घोषित CONFIG_USB_DYNAMIC_MINORS
#घोषणा YUREX_MINOR_BASE	0
#अन्यथा
#घोषणा YUREX_MINOR_BASE	192
#पूर्ण_अगर

/* Structure to hold all of our device specअगरic stuff */
काष्ठा usb_yurex अणु
	काष्ठा usb_device	*udev;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकerface;
	__u8			पूर्णांक_in_endpoपूर्णांकAddr;
	काष्ठा urb		*urb;		/* URB क्रम पूर्णांकerrupt in */
	अचिन्हित अक्षर           *पूर्णांक_buffer;	/* buffer क्रम पूर्णांकterupt in */
	काष्ठा urb		*cntl_urb;	/* URB क्रम control msg */
	काष्ठा usb_ctrlrequest	*cntl_req;	/* req क्रम control msg */
	अचिन्हित अक्षर		*cntl_buffer;	/* buffer क्रम control msg */

	काष्ठा kref		kref;
	काष्ठा mutex		io_mutex;
	अचिन्हित दीर्घ		disconnected:1;
	काष्ठा fasync_काष्ठा	*async_queue;
	रुको_queue_head_t	रुकोq;

	spinlock_t		lock;
	__s64			bbu;		/* BBU from device */
पूर्ण;
#घोषणा to_yurex_dev(d) container_of(d, काष्ठा usb_yurex, kref)

अटल काष्ठा usb_driver yurex_driver;
अटल स्थिर काष्ठा file_operations yurex_fops;


अटल व्योम yurex_control_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_yurex *dev = urb->context;
	पूर्णांक status = urb->status;

	अगर (status) अणु
		dev_err(&urb->dev->dev, "%s - control failed: %d\n",
			__func__, status);
		wake_up_पूर्णांकerruptible(&dev->रुकोq);
		वापस;
	पूर्ण
	/* on success, sender woken up by CMD_ACK पूर्णांक in, or समयout */
पूर्ण

अटल व्योम yurex_delete(काष्ठा kref *kref)
अणु
	काष्ठा usb_yurex *dev = to_yurex_dev(kref);

	dev_dbg(&dev->पूर्णांकerface->dev, "%s\n", __func__);

	अगर (dev->cntl_urb) अणु
		usb_समाप्त_urb(dev->cntl_urb);
		kमुक्त(dev->cntl_req);
		usb_मुक्त_coherent(dev->udev, YUREX_BUF_SIZE,
				dev->cntl_buffer, dev->cntl_urb->transfer_dma);
		usb_मुक्त_urb(dev->cntl_urb);
	पूर्ण
	अगर (dev->urb) अणु
		usb_समाप्त_urb(dev->urb);
		usb_मुक्त_coherent(dev->udev, YUREX_BUF_SIZE,
				dev->पूर्णांक_buffer, dev->urb->transfer_dma);
		usb_मुक्त_urb(dev->urb);
	पूर्ण
	usb_put_पूर्णांकf(dev->पूर्णांकerface);
	usb_put_dev(dev->udev);
	kमुक्त(dev);
पूर्ण

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device रेजिस्टरed with the driver core
 */
अटल काष्ठा usb_class_driver yurex_class = अणु
	.name =		"yurex%d",
	.fops =		&yurex_fops,
	.minor_base =	YUREX_MINOR_BASE,
पूर्ण;

अटल व्योम yurex_पूर्णांकerrupt(काष्ठा urb *urb)
अणु
	काष्ठा usb_yurex *dev = urb->context;
	अचिन्हित अक्षर *buf = dev->पूर्णांक_buffer;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval, i;

	चयन (status) अणु
	हाल 0: /*success*/
		अवरोध;
	/* The device is terminated or messed up, give up */
	हाल -EOVERFLOW:
		dev_err(&dev->पूर्णांकerface->dev,
			"%s - overflow with length %d, actual length is %d\n",
			__func__, YUREX_BUF_SIZE, dev->urb->actual_length);
		वापस;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -EILSEQ:
	हाल -EPROTO:
	हाल -ETIME:
		वापस;
	शेष:
		dev_err(&dev->पूर्णांकerface->dev,
			"%s - unknown status received: %d\n", __func__, status);
		वापस;
	पूर्ण

	/* handle received message */
	चयन (buf[0]) अणु
	हाल CMD_COUNT:
	हाल CMD_READ:
		अगर (buf[6] == CMD_खातापूर्ण) अणु
			spin_lock_irqsave(&dev->lock, flags);
			dev->bbu = 0;
			क्रम (i = 1; i < 6; i++) अणु
				dev->bbu += buf[i];
				अगर (i != 5)
					dev->bbu <<= 8;
			पूर्ण
			dev_dbg(&dev->पूर्णांकerface->dev, "%s count: %lld\n",
				__func__, dev->bbu);
			spin_unlock_irqrestore(&dev->lock, flags);

			समाप्त_fasync(&dev->async_queue, SIGIO, POLL_IN);
		पूर्ण
		अन्यथा
			dev_dbg(&dev->पूर्णांकerface->dev,
				"data format error - no EOF\n");
		अवरोध;
	हाल CMD_ACK:
		dev_dbg(&dev->पूर्णांकerface->dev, "%s ack: %c\n",
			__func__, buf[1]);
		wake_up_पूर्णांकerruptible(&dev->रुकोq);
		अवरोध;
	पूर्ण

	retval = usb_submit_urb(dev->urb, GFP_ATOMIC);
	अगर (retval) अणु
		dev_err(&dev->पूर्णांकerface->dev, "%s - usb_submit_urb failed: %d\n",
			__func__, retval);
	पूर्ण
पूर्ण

अटल पूर्णांक yurex_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_yurex *dev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक retval = -ENOMEM;
	DEFINE_WAIT(रुको);
	पूर्णांक res;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		जाओ error;
	kref_init(&dev->kref);
	mutex_init(&dev->io_mutex);
	spin_lock_init(&dev->lock);
	init_रुकोqueue_head(&dev->रुकोq);

	dev->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	dev->पूर्णांकerface = usb_get_पूर्णांकf(पूर्णांकerface);

	/* set up the endpoपूर्णांक inक्रमmation */
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	res = usb_find_पूर्णांक_in_endpoपूर्णांक(अगरace_desc, &endpoपूर्णांक);
	अगर (res) अणु
		dev_err(&पूर्णांकerface->dev, "Could not find endpoints\n");
		retval = res;
		जाओ error;
	पूर्ण

	dev->पूर्णांक_in_endpoपूर्णांकAddr = endpoपूर्णांक->bEndpoपूर्णांकAddress;

	/* allocate control URB */
	dev->cntl_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->cntl_urb)
		जाओ error;

	/* allocate buffer क्रम control req */
	dev->cntl_req = kदो_स्मृति(YUREX_BUF_SIZE, GFP_KERNEL);
	अगर (!dev->cntl_req)
		जाओ error;

	/* allocate buffer क्रम control msg */
	dev->cntl_buffer = usb_alloc_coherent(dev->udev, YUREX_BUF_SIZE,
					      GFP_KERNEL,
					      &dev->cntl_urb->transfer_dma);
	अगर (!dev->cntl_buffer) अणु
		dev_err(&पूर्णांकerface->dev, "Could not allocate cntl_buffer\n");
		जाओ error;
	पूर्ण

	/* configure control URB */
	dev->cntl_req->bRequestType = USB_सूची_OUT | USB_TYPE_CLASS |
				      USB_RECIP_INTERFACE;
	dev->cntl_req->bRequest	= HID_REQ_SET_REPORT;
	dev->cntl_req->wValue	= cpu_to_le16((HID_OUTPUT_REPORT + 1) << 8);
	dev->cntl_req->wIndex	= cpu_to_le16(अगरace_desc->desc.bInterfaceNumber);
	dev->cntl_req->wLength	= cpu_to_le16(YUREX_BUF_SIZE);

	usb_fill_control_urb(dev->cntl_urb, dev->udev,
			     usb_sndctrlpipe(dev->udev, 0),
			     (व्योम *)dev->cntl_req, dev->cntl_buffer,
			     YUREX_BUF_SIZE, yurex_control_callback, dev);
	dev->cntl_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;


	/* allocate पूर्णांकerrupt URB */
	dev->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->urb)
		जाओ error;

	/* allocate buffer क्रम पूर्णांकerrupt in */
	dev->पूर्णांक_buffer = usb_alloc_coherent(dev->udev, YUREX_BUF_SIZE,
					GFP_KERNEL, &dev->urb->transfer_dma);
	अगर (!dev->पूर्णांक_buffer) अणु
		dev_err(&पूर्णांकerface->dev, "Could not allocate int_buffer\n");
		जाओ error;
	पूर्ण

	/* configure पूर्णांकerrupt URB */
	usb_fill_पूर्णांक_urb(dev->urb, dev->udev,
			 usb_rcvपूर्णांकpipe(dev->udev, dev->पूर्णांक_in_endpoपूर्णांकAddr),
			 dev->पूर्णांक_buffer, YUREX_BUF_SIZE, yurex_पूर्णांकerrupt,
			 dev, 1);
	dev->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	अगर (usb_submit_urb(dev->urb, GFP_KERNEL)) अणु
		retval = -EIO;
		dev_err(&पूर्णांकerface->dev, "Could not submitting URB\n");
		जाओ error;
	पूर्ण

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);
	dev->bbu = -1;

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	retval = usb_रेजिस्टर_dev(पूर्णांकerface, &yurex_class);
	अगर (retval) अणु
		dev_err(&पूर्णांकerface->dev,
			"Not able to get a minor for this device.\n");
		usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
		जाओ error;
	पूर्ण

	dev_info(&पूर्णांकerface->dev,
		 "USB YUREX device now attached to Yurex #%d\n",
		 पूर्णांकerface->minor);

	वापस 0;

error:
	अगर (dev)
		/* this मुक्तs allocated memory */
		kref_put(&dev->kref, yurex_delete);
	वापस retval;
पूर्ण

अटल व्योम yurex_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_yurex *dev;
	पूर्णांक minor = पूर्णांकerface->minor;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	/* give back our minor */
	usb_deरेजिस्टर_dev(पूर्णांकerface, &yurex_class);

	/* prevent more I/O from starting */
	usb_poison_urb(dev->urb);
	usb_poison_urb(dev->cntl_urb);
	mutex_lock(&dev->io_mutex);
	dev->disconnected = 1;
	mutex_unlock(&dev->io_mutex);

	/* wakeup रुकोers */
	समाप्त_fasync(&dev->async_queue, SIGIO, POLL_IN);
	wake_up_पूर्णांकerruptible(&dev->रुकोq);

	/* decrement our usage count */
	kref_put(&dev->kref, yurex_delete);

	dev_info(&पूर्णांकerface->dev, "USB YUREX #%d now disconnected\n", minor);
पूर्ण

अटल काष्ठा usb_driver yurex_driver = अणु
	.name =		"yurex",
	.probe =	yurex_probe,
	.disconnect =	yurex_disconnect,
	.id_table =	yurex_table,
पूर्ण;


अटल पूर्णांक yurex_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा usb_yurex *dev;

	dev = file->निजी_data;
	वापस fasync_helper(fd, file, on, &dev->async_queue);
पूर्ण

अटल पूर्णांक yurex_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_yurex *dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक subminor;
	पूर्णांक retval = 0;

	subminor = iminor(inode);

	पूर्णांकerface = usb_find_पूर्णांकerface(&yurex_driver, subminor);
	अगर (!पूर्णांकerface) अणु
		prपूर्णांकk(KERN_ERR "%s - error, can't find device for minor %d",
		       __func__, subminor);
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* increment our usage count क्रम the device */
	kref_get(&dev->kref);

	/* save our object in the file's निजी काष्ठाure */
	mutex_lock(&dev->io_mutex);
	file->निजी_data = dev;
	mutex_unlock(&dev->io_mutex);

निकास:
	वापस retval;
पूर्ण

अटल पूर्णांक yurex_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_yurex *dev;

	dev = file->निजी_data;
	अगर (dev == शून्य)
		वापस -ENODEV;

	/* decrement the count on our device */
	kref_put(&dev->kref, yurex_delete);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार yurex_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count,
			  loff_t *ppos)
अणु
	काष्ठा usb_yurex *dev;
	पूर्णांक len = 0;
	अक्षर in_buffer[20];
	अचिन्हित दीर्घ flags;

	dev = file->निजी_data;

	mutex_lock(&dev->io_mutex);
	अगर (dev->disconnected) अणु		/* alपढ़ोy disconnected */
		mutex_unlock(&dev->io_mutex);
		वापस -ENODEV;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	len = snम_लिखो(in_buffer, 20, "%lld\n", dev->bbu);
	spin_unlock_irqrestore(&dev->lock, flags);
	mutex_unlock(&dev->io_mutex);

	अगर (WARN_ON_ONCE(len >= माप(in_buffer)))
		वापस -EIO;

	वापस simple_पढ़ो_from_buffer(buffer, count, ppos, in_buffer, len);
पूर्ण

अटल sमाप_प्रकार yurex_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buffer,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा usb_yurex *dev;
	पूर्णांक i, set = 0, retval = 0;
	अक्षर buffer[16 + 1];
	अक्षर *data = buffer;
	अचिन्हित दीर्घ दीर्घ c, c2 = 0;
	चिन्हित दीर्घ समयout = 0;
	DEFINE_WAIT(रुको);

	count = min(माप(buffer) - 1, count);
	dev = file->निजी_data;

	/* verअगरy that we actually have some data to ग_लिखो */
	अगर (count == 0)
		जाओ error;

	mutex_lock(&dev->io_mutex);
	अगर (dev->disconnected) अणु		/* alपढ़ोy disconnected */
		mutex_unlock(&dev->io_mutex);
		retval = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (copy_from_user(buffer, user_buffer, count)) अणु
		mutex_unlock(&dev->io_mutex);
		retval = -EFAULT;
		जाओ error;
	पूर्ण
	buffer[count] = 0;
	स_रखो(dev->cntl_buffer, CMD_PADDING, YUREX_BUF_SIZE);

	चयन (buffer[0]) अणु
	हाल CMD_ANIMATE:
	हाल CMD_LED:
		dev->cntl_buffer[0] = buffer[0];
		dev->cntl_buffer[1] = buffer[1];
		dev->cntl_buffer[2] = CMD_खातापूर्ण;
		अवरोध;
	हाल CMD_READ:
	हाल CMD_VERSION:
		dev->cntl_buffer[0] = buffer[0];
		dev->cntl_buffer[1] = 0x00;
		dev->cntl_buffer[2] = CMD_खातापूर्ण;
		अवरोध;
	हाल CMD_SET:
		data++;
		fallthrough;
	हाल '0' ... '9':
		set = 1;
		c = c2 = simple_म_से_अदीर्घl(data, शून्य, 0);
		dev->cntl_buffer[0] = CMD_SET;
		क्रम (i = 1; i < 6; i++) अणु
			dev->cntl_buffer[i] = (c>>32) & 0xff;
			c <<= 8;
		पूर्ण
		buffer[6] = CMD_खातापूर्ण;
		अवरोध;
	शेष:
		mutex_unlock(&dev->io_mutex);
		वापस -EINVAL;
	पूर्ण

	/* send the data as the control msg */
	prepare_to_रुको(&dev->रुकोq, &रुको, TASK_INTERRUPTIBLE);
	dev_dbg(&dev->पूर्णांकerface->dev, "%s - submit %c\n", __func__,
		dev->cntl_buffer[0]);
	retval = usb_submit_urb(dev->cntl_urb, GFP_ATOMIC);
	अगर (retval >= 0)
		समयout = schedule_समयout(YUREX_WRITE_TIMEOUT);
	finish_रुको(&dev->रुकोq, &रुको);

	/* make sure URB is idle after समयout or (spurious) CMD_ACK */
	usb_समाप्त_urb(dev->cntl_urb);

	mutex_unlock(&dev->io_mutex);

	अगर (retval < 0) अणु
		dev_err(&dev->पूर्णांकerface->dev,
			"%s - failed to send bulk msg, error %d\n",
			__func__, retval);
		जाओ error;
	पूर्ण
	अगर (set && समयout)
		dev->bbu = c2;
	वापस समयout ? count : -EIO;

error:
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations yurex_fops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		yurex_पढ़ो,
	.ग_लिखो =	yurex_ग_लिखो,
	.खोलो =		yurex_खोलो,
	.release =	yurex_release,
	.fasync	=	yurex_fasync,
	.llseek =	शेष_llseek,
पूर्ण;

module_usb_driver(yurex_driver);

MODULE_LICENSE("GPL");
