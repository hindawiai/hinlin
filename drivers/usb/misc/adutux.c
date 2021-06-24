<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * adutux - driver क्रम ADU devices from Ontrak Control Systems
 * This is an experimental driver. Use at your own risk.
 * This driver is not supported by Ontrak Control Systems.
 *
 * Copyright (c) 2003 John Homppi (SCO, leave this notice here)
 *
 * derived from the Lego USB Tower driver 0.56:
 * Copyright (c) 2003 David Glance <davidgsf@sourceक्रमge.net>
 *               2001 Juergen Stuber <stuber@loria.fr>
 * that was derived from USB Skeleton driver - 0.5
 * Copyright (c) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

#घोषणा DRIVER_AUTHOR "John Homppi"
#घोषणा DRIVER_DESC "adutux (see www.ontrak.net)"

/* Define these values to match your device */
#घोषणा ADU_VENDOR_ID 0x0a07
#घोषणा ADU_PRODUCT_ID 0x0064

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id device_table[] = अणु
	अणु USB_DEVICE(ADU_VENDOR_ID, ADU_PRODUCT_ID) पूर्ण,		/* ADU100 */
	अणु USB_DEVICE(ADU_VENDOR_ID, ADU_PRODUCT_ID+20) पूर्ण,	/* ADU120 */
	अणु USB_DEVICE(ADU_VENDOR_ID, ADU_PRODUCT_ID+30) पूर्ण,	/* ADU130 */
	अणु USB_DEVICE(ADU_VENDOR_ID, ADU_PRODUCT_ID+100) पूर्ण,	/* ADU200 */
	अणु USB_DEVICE(ADU_VENDOR_ID, ADU_PRODUCT_ID+108) पूर्ण,	/* ADU208 */
	अणु USB_DEVICE(ADU_VENDOR_ID, ADU_PRODUCT_ID+118) पूर्ण,	/* ADU218 */
	अणु पूर्ण /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, device_table);

#अगर_घोषित CONFIG_USB_DYNAMIC_MINORS
#घोषणा ADU_MINOR_BASE	0
#अन्यथा
#घोषणा ADU_MINOR_BASE	67
#पूर्ण_अगर

/* we can have up to this number of device plugged in at once */
#घोषणा MAX_DEVICES	16

#घोषणा COMMAND_TIMEOUT	(2*HZ)

/*
 * The locking scheme is a vanilla 3-lock:
 *   adu_device.buflock: A spinlock, covers what IRQs touch.
 *   adutux_mutex:       A Static lock to cover खोलो_count. It would also cover
 *                       any globals, but we करोn't have them in 2.6.
 *   adu_device.mtx:     A mutex to hold across sleepers like copy_from_user.
 *                       It covers all of adu_device, except the खोलो_count
 *                       and what .buflock covers.
 */

/* Structure to hold all of our device specअगरic stuff */
काष्ठा adu_device अणु
	काष्ठा mutex		mtx;
	काष्ठा usb_device *udev; /* save off the usb device poपूर्णांकer */
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	अचिन्हित पूर्णांक		minor; /* the starting minor number क्रम this device */
	अक्षर			serial_number[8];

	पूर्णांक			खोलो_count; /* number of बार this port has been खोलोed */
	अचिन्हित दीर्घ		disconnected:1;

	अक्षर		*पढ़ो_buffer_primary;
	पूर्णांक			पढ़ो_buffer_length;
	अक्षर		*पढ़ो_buffer_secondary;
	पूर्णांक			secondary_head;
	पूर्णांक			secondary_tail;
	spinlock_t		buflock;

	रुको_queue_head_t	पढ़ो_रुको;
	रुको_queue_head_t	ग_लिखो_रुको;

	अक्षर		*पूर्णांकerrupt_in_buffer;
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकerrupt_in_endpoपूर्णांक;
	काष्ठा urb	*पूर्णांकerrupt_in_urb;
	पूर्णांक			पढ़ो_urb_finished;

	अक्षर		*पूर्णांकerrupt_out_buffer;
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकerrupt_out_endpoपूर्णांक;
	काष्ठा urb	*पूर्णांकerrupt_out_urb;
	पूर्णांक			out_urb_finished;
पूर्ण;

अटल DEFINE_MUTEX(adutux_mutex);

अटल काष्ठा usb_driver adu_driver;

अटल अंतरभूत व्योम adu_debug_data(काष्ठा device *dev, स्थिर अक्षर *function,
				  पूर्णांक size, स्थिर अचिन्हित अक्षर *data)
अणु
	dev_dbg(dev, "%s - length = %d, data = %*ph\n",
		function, size, size, data);
पूर्ण

/*
 * adu_पात_transfers
 *      पातs transfers and मुक्तs associated data काष्ठाures
 */
अटल व्योम adu_पात_transfers(काष्ठा adu_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	अगर (dev->disconnected)
		वापस;

	/* shutकरोwn transfer */

	/* XXX Anchor these instead */
	spin_lock_irqsave(&dev->buflock, flags);
	अगर (!dev->पढ़ो_urb_finished) अणु
		spin_unlock_irqrestore(&dev->buflock, flags);
		usb_समाप्त_urb(dev->पूर्णांकerrupt_in_urb);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&dev->buflock, flags);

	spin_lock_irqsave(&dev->buflock, flags);
	अगर (!dev->out_urb_finished) अणु
		spin_unlock_irqrestore(&dev->buflock, flags);
		रुको_event_समयout(dev->ग_लिखो_रुको, dev->out_urb_finished,
			COMMAND_TIMEOUT);
		usb_समाप्त_urb(dev->पूर्णांकerrupt_out_urb);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&dev->buflock, flags);
पूर्ण

अटल व्योम adu_delete(काष्ठा adu_device *dev)
अणु
	/* मुक्त data काष्ठाures */
	usb_मुक्त_urb(dev->पूर्णांकerrupt_in_urb);
	usb_मुक्त_urb(dev->पूर्णांकerrupt_out_urb);
	kमुक्त(dev->पढ़ो_buffer_primary);
	kमुक्त(dev->पढ़ो_buffer_secondary);
	kमुक्त(dev->पूर्णांकerrupt_in_buffer);
	kमुक्त(dev->पूर्णांकerrupt_out_buffer);
	usb_put_dev(dev->udev);
	kमुक्त(dev);
पूर्ण

अटल व्योम adu_पूर्णांकerrupt_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा adu_device *dev = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	adu_debug_data(&dev->udev->dev, __func__,
		       urb->actual_length, urb->transfer_buffer);

	spin_lock_irqsave(&dev->buflock, flags);

	अगर (status != 0) अणु
		अगर ((status != -ENOENT) && (status != -ECONNRESET) &&
			(status != -ESHUTDOWN)) अणु
			dev_dbg(&dev->udev->dev,
				"%s : nonzero status received: %d\n",
				__func__, status);
		पूर्ण
		जाओ निकास;
	पूर्ण

	अगर (urb->actual_length > 0 && dev->पूर्णांकerrupt_in_buffer[0] != 0x00) अणु
		अगर (dev->पढ़ो_buffer_length <
		    (4 * usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_in_endpoपूर्णांक)) -
		     (urb->actual_length)) अणु
			स_नकल (dev->पढ़ो_buffer_primary +
				dev->पढ़ो_buffer_length,
				dev->पूर्णांकerrupt_in_buffer, urb->actual_length);

			dev->पढ़ो_buffer_length += urb->actual_length;
			dev_dbg(&dev->udev->dev, "%s reading  %d\n", __func__,
				urb->actual_length);
		पूर्ण अन्यथा अणु
			dev_dbg(&dev->udev->dev, "%s : read_buffer overflow\n",
				__func__);
		पूर्ण
	पूर्ण

निकास:
	dev->पढ़ो_urb_finished = 1;
	spin_unlock_irqrestore(&dev->buflock, flags);
	/* always wake up so we recover from errors */
	wake_up_पूर्णांकerruptible(&dev->पढ़ो_रुको);
पूर्ण

अटल व्योम adu_पूर्णांकerrupt_out_callback(काष्ठा urb *urb)
अणु
	काष्ठा adu_device *dev = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	adu_debug_data(&dev->udev->dev, __func__,
		       urb->actual_length, urb->transfer_buffer);

	अगर (status != 0) अणु
		अगर ((status != -ENOENT) &&
		    (status != -ESHUTDOWN) &&
		    (status != -ECONNRESET)) अणु
			dev_dbg(&dev->udev->dev,
				"%s :nonzero status received: %d\n", __func__,
				status);
		पूर्ण
		वापस;
	पूर्ण

	spin_lock_irqsave(&dev->buflock, flags);
	dev->out_urb_finished = 1;
	wake_up(&dev->ग_लिखो_रुको);
	spin_unlock_irqrestore(&dev->buflock, flags);
पूर्ण

अटल पूर्णांक adu_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा adu_device *dev = शून्य;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक subminor;
	पूर्णांक retval;

	subminor = iminor(inode);

	retval = mutex_lock_पूर्णांकerruptible(&adutux_mutex);
	अगर (retval)
		जाओ निकास_no_lock;

	पूर्णांकerface = usb_find_पूर्णांकerface(&adu_driver, subminor);
	अगर (!पूर्णांकerface) अणु
		pr_err("%s - error, can't find device for minor %d\n",
		       __func__, subminor);
		retval = -ENODEV;
		जाओ निकास_no_device;
	पूर्ण

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev) अणु
		retval = -ENODEV;
		जाओ निकास_no_device;
	पूर्ण

	/* check that nobody अन्यथा is using the device */
	अगर (dev->खोलो_count) अणु
		retval = -EBUSY;
		जाओ निकास_no_device;
	पूर्ण

	++dev->खोलो_count;
	dev_dbg(&dev->udev->dev, "%s: open count %d\n", __func__,
		dev->खोलो_count);

	/* save device in the file's निजी काष्ठाure */
	file->निजी_data = dev;

	/* initialize in direction */
	dev->पढ़ो_buffer_length = 0;

	/* fixup first पढ़ो by having urb रुकोing क्रम it */
	usb_fill_पूर्णांक_urb(dev->पूर्णांकerrupt_in_urb, dev->udev,
			 usb_rcvपूर्णांकpipe(dev->udev,
					dev->पूर्णांकerrupt_in_endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 dev->पूर्णांकerrupt_in_buffer,
			 usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_in_endpoपूर्णांक),
			 adu_पूर्णांकerrupt_in_callback, dev,
			 dev->पूर्णांकerrupt_in_endpoपूर्णांक->bInterval);
	dev->पढ़ो_urb_finished = 0;
	अगर (usb_submit_urb(dev->पूर्णांकerrupt_in_urb, GFP_KERNEL))
		dev->पढ़ो_urb_finished = 1;
	/* we ignore failure */
	/* end of fixup क्रम first पढ़ो */

	/* initialize out direction */
	dev->out_urb_finished = 1;

	retval = 0;

निकास_no_device:
	mutex_unlock(&adutux_mutex);
निकास_no_lock:
	वापस retval;
पूर्ण

अटल व्योम adu_release_पूर्णांकernal(काष्ठा adu_device *dev)
अणु
	/* decrement our usage count क्रम the device */
	--dev->खोलो_count;
	dev_dbg(&dev->udev->dev, "%s : open count %d\n", __func__,
		dev->खोलो_count);
	अगर (dev->खोलो_count <= 0) अणु
		adu_पात_transfers(dev);
		dev->खोलो_count = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक adu_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा adu_device *dev;
	पूर्णांक retval = 0;

	अगर (file == शून्य) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	dev = file->निजी_data;
	अगर (dev == शून्य) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	mutex_lock(&adutux_mutex); /* not पूर्णांकerruptible */

	अगर (dev->खोलो_count <= 0) अणु
		dev_dbg(&dev->udev->dev, "%s : device not opened\n", __func__);
		retval = -ENODEV;
		जाओ unlock;
	पूर्ण

	adu_release_पूर्णांकernal(dev);
	अगर (dev->disconnected) अणु
		/* the device was unplugged beक्रमe the file was released */
		अगर (!dev->खोलो_count)	/* ... and we're the last user */
			adu_delete(dev);
	पूर्ण
unlock:
	mutex_unlock(&adutux_mutex);
निकास:
	वापस retval;
पूर्ण

अटल sमाप_प्रकार adu_पढ़ो(काष्ठा file *file, __user अक्षर *buffer, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा adu_device *dev;
	माप_प्रकार bytes_पढ़ो = 0;
	माप_प्रकार bytes_to_पढ़ो = count;
	पूर्णांक retval = 0;
	पूर्णांक समयout = 0;
	पूर्णांक should_submit = 0;
	अचिन्हित दीर्घ flags;
	DECLARE_WAITQUEUE(रुको, current);

	dev = file->निजी_data;
	अगर (mutex_lock_पूर्णांकerruptible(&dev->mtx))
		वापस -ERESTARTSYS;

	/* verअगरy that the device wasn't unplugged */
	अगर (dev->disconnected) अणु
		retval = -ENODEV;
		pr_err("No device or device unplugged %d\n", retval);
		जाओ निकास;
	पूर्ण

	/* verअगरy that some data was requested */
	अगर (count == 0) अणु
		dev_dbg(&dev->udev->dev, "%s : read request of 0 bytes\n",
			__func__);
		जाओ निकास;
	पूर्ण

	समयout = COMMAND_TIMEOUT;
	dev_dbg(&dev->udev->dev, "%s : about to start looping\n", __func__);
	जबतक (bytes_to_पढ़ो) अणु
		माप_प्रकार data_in_secondary = dev->secondary_tail - dev->secondary_head;
		dev_dbg(&dev->udev->dev,
			"%s : while, data_in_secondary=%zu, status=%d\n",
			__func__, data_in_secondary,
			dev->पूर्णांकerrupt_in_urb->status);

		अगर (data_in_secondary) अणु
			/* drain secondary buffer */
			माप_प्रकार amount = min(bytes_to_पढ़ो, data_in_secondary);
			अगर (copy_to_user(buffer, dev->पढ़ो_buffer_secondary+dev->secondary_head, amount)) अणु
				retval = -EFAULT;
				जाओ निकास;
			पूर्ण
			dev->secondary_head += amount;
			bytes_पढ़ो += amount;
			bytes_to_पढ़ो -= amount;
		पूर्ण अन्यथा अणु
			/* we check the primary buffer */
			spin_lock_irqsave (&dev->buflock, flags);
			अगर (dev->पढ़ो_buffer_length) अणु
				/* we secure access to the primary */
				अक्षर *पंचांगp;
				dev_dbg(&dev->udev->dev,
					"%s : swap, read_buffer_length = %d\n",
					__func__, dev->पढ़ो_buffer_length);
				पंचांगp = dev->पढ़ो_buffer_secondary;
				dev->पढ़ो_buffer_secondary = dev->पढ़ो_buffer_primary;
				dev->पढ़ो_buffer_primary = पंचांगp;
				dev->secondary_head = 0;
				dev->secondary_tail = dev->पढ़ो_buffer_length;
				dev->पढ़ो_buffer_length = 0;
				spin_unlock_irqrestore(&dev->buflock, flags);
				/* we have a मुक्त buffer so use it */
				should_submit = 1;
			पूर्ण अन्यथा अणु
				/* even the primary was empty - we may need to करो IO */
				अगर (!dev->पढ़ो_urb_finished) अणु
					/* somebody is करोing IO */
					spin_unlock_irqrestore(&dev->buflock, flags);
					dev_dbg(&dev->udev->dev,
						"%s : submitted already\n",
						__func__);
				पूर्ण अन्यथा अणु
					/* we must initiate input */
					dev_dbg(&dev->udev->dev,
						"%s : initiate input\n",
						__func__);
					dev->पढ़ो_urb_finished = 0;
					spin_unlock_irqrestore(&dev->buflock, flags);

					usb_fill_पूर्णांक_urb(dev->पूर्णांकerrupt_in_urb, dev->udev,
							usb_rcvपूर्णांकpipe(dev->udev,
								dev->पूर्णांकerrupt_in_endpoपूर्णांक->bEndpoपूर्णांकAddress),
							 dev->पूर्णांकerrupt_in_buffer,
							 usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_in_endpoपूर्णांक),
							 adu_पूर्णांकerrupt_in_callback,
							 dev,
							 dev->पूर्णांकerrupt_in_endpoपूर्णांक->bInterval);
					retval = usb_submit_urb(dev->पूर्णांकerrupt_in_urb, GFP_KERNEL);
					अगर (retval) अणु
						dev->पढ़ो_urb_finished = 1;
						अगर (retval == -ENOMEM) अणु
							retval = bytes_पढ़ो ? bytes_पढ़ो : -ENOMEM;
						पूर्ण
						dev_dbg(&dev->udev->dev,
							"%s : submit failed\n",
							__func__);
						जाओ निकास;
					पूर्ण
				पूर्ण

				/* we रुको क्रम I/O to complete */
				set_current_state(TASK_INTERRUPTIBLE);
				add_रुको_queue(&dev->पढ़ो_रुको, &रुको);
				spin_lock_irqsave(&dev->buflock, flags);
				अगर (!dev->पढ़ो_urb_finished) अणु
					spin_unlock_irqrestore(&dev->buflock, flags);
					समयout = schedule_समयout(COMMAND_TIMEOUT);
				पूर्ण अन्यथा अणु
					spin_unlock_irqrestore(&dev->buflock, flags);
					set_current_state(TASK_RUNNING);
				पूर्ण
				हटाओ_रुको_queue(&dev->पढ़ो_रुको, &रुको);

				अगर (समयout <= 0) अणु
					dev_dbg(&dev->udev->dev,
						"%s : timeout\n", __func__);
					retval = bytes_पढ़ो ? bytes_पढ़ो : -ETIMEDOUT;
					जाओ निकास;
				पूर्ण

				अगर (संकेत_pending(current)) अणु
					dev_dbg(&dev->udev->dev,
						"%s : signal pending\n",
						__func__);
					retval = bytes_पढ़ो ? bytes_पढ़ो : -EINTR;
					जाओ निकास;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	retval = bytes_पढ़ो;
	/* अगर the primary buffer is empty then use it */
	spin_lock_irqsave(&dev->buflock, flags);
	अगर (should_submit && dev->पढ़ो_urb_finished) अणु
		dev->पढ़ो_urb_finished = 0;
		spin_unlock_irqrestore(&dev->buflock, flags);
		usb_fill_पूर्णांक_urb(dev->पूर्णांकerrupt_in_urb, dev->udev,
				 usb_rcvपूर्णांकpipe(dev->udev,
					dev->पूर्णांकerrupt_in_endpoपूर्णांक->bEndpoपूर्णांकAddress),
				dev->पूर्णांकerrupt_in_buffer,
				usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_in_endpoपूर्णांक),
				adu_पूर्णांकerrupt_in_callback,
				dev,
				dev->पूर्णांकerrupt_in_endpoपूर्णांक->bInterval);
		अगर (usb_submit_urb(dev->पूर्णांकerrupt_in_urb, GFP_KERNEL) != 0)
			dev->पढ़ो_urb_finished = 1;
		/* we ignore failure */
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&dev->buflock, flags);
	पूर्ण

निकास:
	/* unlock the device */
	mutex_unlock(&dev->mtx);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार adu_ग_लिखो(काष्ठा file *file, स्थिर __user अक्षर *buffer,
			 माप_प्रकार count, loff_t *ppos)
अणु
	DECLARE_WAITQUEUE(रुकोa, current);
	काष्ठा adu_device *dev;
	माप_प्रकार bytes_written = 0;
	माप_प्रकार bytes_to_ग_लिखो;
	माप_प्रकार buffer_size;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	dev = file->निजी_data;

	retval = mutex_lock_पूर्णांकerruptible(&dev->mtx);
	अगर (retval)
		जाओ निकास_nolock;

	/* verअगरy that the device wasn't unplugged */
	अगर (dev->disconnected) अणु
		retval = -ENODEV;
		pr_err("No device or device unplugged %d\n", retval);
		जाओ निकास;
	पूर्ण

	/* verअगरy that we actually have some data to ग_लिखो */
	अगर (count == 0) अणु
		dev_dbg(&dev->udev->dev, "%s : write request of 0 bytes\n",
			__func__);
		जाओ निकास;
	पूर्ण

	जबतक (count > 0) अणु
		add_रुको_queue(&dev->ग_लिखो_रुको, &रुकोa);
		set_current_state(TASK_INTERRUPTIBLE);
		spin_lock_irqsave(&dev->buflock, flags);
		अगर (!dev->out_urb_finished) अणु
			spin_unlock_irqrestore(&dev->buflock, flags);

			mutex_unlock(&dev->mtx);
			अगर (संकेत_pending(current)) अणु
				dev_dbg(&dev->udev->dev, "%s : interrupted\n",
					__func__);
				set_current_state(TASK_RUNNING);
				retval = -EINTR;
				जाओ निकास_onqueue;
			पूर्ण
			अगर (schedule_समयout(COMMAND_TIMEOUT) == 0) अणु
				dev_dbg(&dev->udev->dev,
					"%s - command timed out.\n", __func__);
				retval = -ETIMEDOUT;
				जाओ निकास_onqueue;
			पूर्ण
			हटाओ_रुको_queue(&dev->ग_लिखो_रुको, &रुकोa);
			retval = mutex_lock_पूर्णांकerruptible(&dev->mtx);
			अगर (retval) अणु
				retval = bytes_written ? bytes_written : retval;
				जाओ निकास_nolock;
			पूर्ण

			dev_dbg(&dev->udev->dev,
				"%s : in progress, count = %zd\n",
				__func__, count);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&dev->buflock, flags);
			set_current_state(TASK_RUNNING);
			हटाओ_रुको_queue(&dev->ग_लिखो_रुको, &रुकोa);
			dev_dbg(&dev->udev->dev, "%s : sending, count = %zd\n",
				__func__, count);

			/* ग_लिखो the data पूर्णांकo पूर्णांकerrupt_out_buffer from userspace */
			buffer_size = usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_out_endpoपूर्णांक);
			bytes_to_ग_लिखो = count > buffer_size ? buffer_size : count;
			dev_dbg(&dev->udev->dev,
				"%s : buffer_size = %zd, count = %zd, bytes_to_write = %zd\n",
				__func__, buffer_size, count, bytes_to_ग_लिखो);

			अगर (copy_from_user(dev->पूर्णांकerrupt_out_buffer, buffer, bytes_to_ग_लिखो) != 0) अणु
				retval = -EFAULT;
				जाओ निकास;
			पूर्ण

			/* send off the urb */
			usb_fill_पूर्णांक_urb(
				dev->पूर्णांकerrupt_out_urb,
				dev->udev,
				usb_sndपूर्णांकpipe(dev->udev, dev->पूर्णांकerrupt_out_endpoपूर्णांक->bEndpoपूर्णांकAddress),
				dev->पूर्णांकerrupt_out_buffer,
				bytes_to_ग_लिखो,
				adu_पूर्णांकerrupt_out_callback,
				dev,
				dev->पूर्णांकerrupt_out_endpoपूर्णांक->bInterval);
			dev->पूर्णांकerrupt_out_urb->actual_length = bytes_to_ग_लिखो;
			dev->out_urb_finished = 0;
			retval = usb_submit_urb(dev->पूर्णांकerrupt_out_urb, GFP_KERNEL);
			अगर (retval < 0) अणु
				dev->out_urb_finished = 1;
				dev_err(&dev->udev->dev, "Couldn't submit "
					"interrupt_out_urb %d\n", retval);
				जाओ निकास;
			पूर्ण

			buffer += bytes_to_ग_लिखो;
			count -= bytes_to_ग_लिखो;

			bytes_written += bytes_to_ग_लिखो;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->mtx);
	वापस bytes_written;

निकास:
	mutex_unlock(&dev->mtx);
निकास_nolock:
	वापस retval;

निकास_onqueue:
	हटाओ_रुको_queue(&dev->ग_लिखो_रुको, &रुकोa);
	वापस retval;
पूर्ण

/* file operations needed when we रेजिस्टर this driver */
अटल स्थिर काष्ठा file_operations adu_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो  = adu_पढ़ो,
	.ग_लिखो = adu_ग_लिखो,
	.खोलो = adu_खोलो,
	.release = adu_release,
	.llseek = noop_llseek,
पूर्ण;

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device रेजिस्टरed with devfs and the driver core
 */
अटल काष्ठा usb_class_driver adu_class = अणु
	.name = "usb/adutux%d",
	.fops = &adu_fops,
	.minor_base = ADU_MINOR_BASE,
पूर्ण;

/*
 * adu_probe
 *
 * Called by the usb core when a new device is connected that it thinks
 * this driver might be पूर्णांकerested in.
 */
अटल पूर्णांक adu_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा adu_device *dev = शून्य;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक in_end_size;
	पूर्णांक out_end_size;
	पूर्णांक res;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(काष्ठा adu_device), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mutex_init(&dev->mtx);
	spin_lock_init(&dev->buflock);
	dev->udev = usb_get_dev(udev);
	init_रुकोqueue_head(&dev->पढ़ो_रुको);
	init_रुकोqueue_head(&dev->ग_लिखो_रुको);

	res = usb_find_common_endpoपूर्णांकs_reverse(पूर्णांकerface->cur_altsetting,
			शून्य, शून्य,
			&dev->पूर्णांकerrupt_in_endpoपूर्णांक,
			&dev->पूर्णांकerrupt_out_endpoपूर्णांक);
	अगर (res) अणु
		dev_err(&पूर्णांकerface->dev, "interrupt endpoints not found\n");
		retval = res;
		जाओ error;
	पूर्ण

	in_end_size = usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_in_endpoपूर्णांक);
	out_end_size = usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_out_endpoपूर्णांक);

	dev->पढ़ो_buffer_primary = kदो_स्मृति((4 * in_end_size), GFP_KERNEL);
	अगर (!dev->पढ़ो_buffer_primary)
		जाओ error;

	/* debug code prime the buffer */
	स_रखो(dev->पढ़ो_buffer_primary, 'a', in_end_size);
	स_रखो(dev->पढ़ो_buffer_primary + in_end_size, 'b', in_end_size);
	स_रखो(dev->पढ़ो_buffer_primary + (2 * in_end_size), 'c', in_end_size);
	स_रखो(dev->पढ़ो_buffer_primary + (3 * in_end_size), 'd', in_end_size);

	dev->पढ़ो_buffer_secondary = kदो_स्मृति((4 * in_end_size), GFP_KERNEL);
	अगर (!dev->पढ़ो_buffer_secondary)
		जाओ error;

	/* debug code prime the buffer */
	स_रखो(dev->पढ़ो_buffer_secondary, 'e', in_end_size);
	स_रखो(dev->पढ़ो_buffer_secondary + in_end_size, 'f', in_end_size);
	स_रखो(dev->पढ़ो_buffer_secondary + (2 * in_end_size), 'g', in_end_size);
	स_रखो(dev->पढ़ो_buffer_secondary + (3 * in_end_size), 'h', in_end_size);

	dev->पूर्णांकerrupt_in_buffer = kदो_स्मृति(in_end_size, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_in_buffer)
		जाओ error;

	/* debug code prime the buffer */
	स_रखो(dev->पूर्णांकerrupt_in_buffer, 'i', in_end_size);

	dev->पूर्णांकerrupt_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_in_urb)
		जाओ error;
	dev->पूर्णांकerrupt_out_buffer = kदो_स्मृति(out_end_size, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_out_buffer)
		जाओ error;
	dev->पूर्णांकerrupt_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_out_urb)
		जाओ error;

	अगर (!usb_string(udev, udev->descriptor.iSerialNumber, dev->serial_number,
			माप(dev->serial_number))) अणु
		dev_err(&पूर्णांकerface->dev, "Could not retrieve serial number\n");
		retval = -EIO;
		जाओ error;
	पूर्ण
	dev_dbg(&पूर्णांकerface->dev, "serial_number=%s", dev->serial_number);

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	retval = usb_रेजिस्टर_dev(पूर्णांकerface, &adu_class);

	अगर (retval) अणु
		/* something prevented us from रेजिस्टरing this driver */
		dev_err(&पूर्णांकerface->dev, "Not able to get a minor for this device.\n");
		usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
		जाओ error;
	पूर्ण

	dev->minor = पूर्णांकerface->minor;

	/* let the user know what node this device is now attached to */
	dev_info(&पूर्णांकerface->dev, "ADU%d %s now attached to /dev/usb/adutux%d\n",
		 le16_to_cpu(udev->descriptor.idProduct), dev->serial_number,
		 (dev->minor - ADU_MINOR_BASE));

	वापस 0;

error:
	adu_delete(dev);
	वापस retval;
पूर्ण

/*
 * adu_disconnect
 *
 * Called by the usb core when the device is हटाओd from the प्रणाली.
 */
अटल व्योम adu_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा adu_device *dev;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	usb_deरेजिस्टर_dev(पूर्णांकerface, &adu_class);

	usb_poison_urb(dev->पूर्णांकerrupt_in_urb);
	usb_poison_urb(dev->पूर्णांकerrupt_out_urb);

	mutex_lock(&adutux_mutex);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	mutex_lock(&dev->mtx);	/* not पूर्णांकerruptible */
	dev->disconnected = 1;
	mutex_unlock(&dev->mtx);

	/* अगर the device is not खोलोed, then we clean up right now */
	अगर (!dev->खोलो_count)
		adu_delete(dev);

	mutex_unlock(&adutux_mutex);
पूर्ण

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver adu_driver = अणु
	.name = "adutux",
	.probe = adu_probe,
	.disconnect = adu_disconnect,
	.id_table = device_table,
पूर्ण;

module_usb_driver(adu_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
