<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Native support क्रम the I/O-Warrior USB devices
 *
 *  Copyright (c) 2003-2005, 2020  Code Mercenaries GmbH
 *  written by Christian Lucht <lucht@codemercs.com> and
 *  Christoph Jung <jung@codemercs.com>
 *
 *  based on

 *  usb-skeleton.c by Greg Kroah-Harपंचांगan  <greg@kroah.com>
 *  brlvger.c by Stephane Dalton  <sdalton@videotron.ca>
 *           and Stephane Doyon   <s.करोyon@videotron.ca>
 *
 *  Released under the GPLv2.
 */

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/usb/iowarrior.h>

#घोषणा DRIVER_AUTHOR "Christian Lucht <lucht@codemercs.com>"
#घोषणा DRIVER_DESC "USB IO-Warrior driver"

#घोषणा USB_VENDOR_ID_CODEMERCS		1984
/* low speed iowarrior */
#घोषणा USB_DEVICE_ID_CODEMERCS_IOW40	0x1500
#घोषणा USB_DEVICE_ID_CODEMERCS_IOW24	0x1501
#घोषणा USB_DEVICE_ID_CODEMERCS_IOWPV1	0x1511
#घोषणा USB_DEVICE_ID_CODEMERCS_IOWPV2	0x1512
/* full speed iowarrior */
#घोषणा USB_DEVICE_ID_CODEMERCS_IOW56	0x1503
/* fuller speed iowarrior */
#घोषणा USB_DEVICE_ID_CODEMERCS_IOW28	0x1504
#घोषणा USB_DEVICE_ID_CODEMERCS_IOW28L	0x1505
#घोषणा USB_DEVICE_ID_CODEMERCS_IOW100	0x1506

/* OEMed devices */
#घोषणा USB_DEVICE_ID_CODEMERCS_IOW24SAG	0x158a
#घोषणा USB_DEVICE_ID_CODEMERCS_IOW56AM		0x158b

/* Get a minor range क्रम your devices from the usb मुख्यtainer */
#अगर_घोषित CONFIG_USB_DYNAMIC_MINORS
#घोषणा IOWARRIOR_MINOR_BASE	0
#अन्यथा
#घोषणा IOWARRIOR_MINOR_BASE	208	// SKELETON_MINOR_BASE 192 + 16, not official yet
#पूर्ण_अगर

/* पूर्णांकerrupt input queue size */
#घोषणा MAX_INTERRUPT_BUFFER 16
/*
   maximum number of urbs that are submitted क्रम ग_लिखोs at the same समय,
   this applies to the IOWarrior56 only!
   IOWarrior24 and IOWarrior40 use synchronous usb_control_msg calls.
*/
#घोषणा MAX_WRITES_IN_FLIGHT 4

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल काष्ठा usb_driver iowarrior_driver;

/*--------------*/
/*     data     */
/*--------------*/

/* Structure to hold all of our device specअगरic stuff */
काष्ठा iowarrior अणु
	काष्ठा mutex mutex;			/* locks this काष्ठाure */
	काष्ठा usb_device *udev;		/* save off the usb device poपूर्णांकer */
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;	/* the पूर्णांकerface क्रम this device */
	अचिन्हित अक्षर minor;			/* the starting minor number क्रम this device */
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांक_out_endpoपूर्णांक;	/* endpoपूर्णांक क्रम पढ़ोing (needed क्रम IOW56 only) */
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांक_in_endpoपूर्णांक;	/* endpoपूर्णांक क्रम पढ़ोing */
	काष्ठा urb *पूर्णांक_in_urb;		/* the urb क्रम पढ़ोing data */
	अचिन्हित अक्षर *पूर्णांक_in_buffer;	/* buffer क्रम data to be पढ़ो */
	अचिन्हित अक्षर serial_number;	/* to detect lost packages */
	अचिन्हित अक्षर *पढ़ो_queue;	/* size is MAX_INTERRUPT_BUFFER * packet size */
	रुको_queue_head_t पढ़ो_रुको;
	रुको_queue_head_t ग_लिखो_रुको;	/* रुको-queue क्रम writing to the device */
	atomic_t ग_लिखो_busy;		/* number of ग_लिखो-urbs submitted */
	atomic_t पढ़ो_idx;
	atomic_t पूर्णांकr_idx;
	atomic_t overflow_flag;		/* संकेतs an index 'rollover' */
	पूर्णांक present;			/* this is 1 as दीर्घ as the device is connected */
	पूर्णांक खोलोed;			/* this is 1 अगर the device is currently खोलो */
	अक्षर chip_serial[9];		/* the serial number string of the chip connected */
	पूर्णांक report_size;		/* number of bytes in a report */
	u16 product_id;
	काष्ठा usb_anchor submitted;
पूर्ण;

/*--------------*/
/*    globals   */
/*--------------*/

/*
 *  USB spec identअगरies 5 second समयouts.
 */
#घोषणा GET_TIMEOUT 5
#घोषणा USB_REQ_GET_REPORT  0x01
//#अगर 0
अटल पूर्णांक usb_get_report(काष्ठा usb_device *dev,
			  काष्ठा usb_host_पूर्णांकerface *पूर्णांकer, अचिन्हित अक्षर type,
			  अचिन्हित अक्षर id, व्योम *buf, पूर्णांक size)
अणु
	वापस usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			       USB_REQ_GET_REPORT,
			       USB_सूची_IN | USB_TYPE_CLASS |
			       USB_RECIP_INTERFACE, (type << 8) + id,
			       पूर्णांकer->desc.bInterfaceNumber, buf, size,
			       GET_TIMEOUT*HZ);
पूर्ण
//#पूर्ण_अगर

#घोषणा USB_REQ_SET_REPORT 0x09

अटल पूर्णांक usb_set_report(काष्ठा usb_पूर्णांकerface *पूर्णांकf, अचिन्हित अक्षर type,
			  अचिन्हित अक्षर id, व्योम *buf, पूर्णांक size)
अणु
	वापस usb_control_msg(पूर्णांकerface_to_usbdev(पूर्णांकf),
			       usb_sndctrlpipe(पूर्णांकerface_to_usbdev(पूर्णांकf), 0),
			       USB_REQ_SET_REPORT,
			       USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			       (type << 8) + id,
			       पूर्णांकf->cur_altsetting->desc.bInterfaceNumber, buf,
			       size, HZ);
पूर्ण

/*---------------------*/
/* driver registration */
/*---------------------*/
/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id iowarrior_ids[] = अणु
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOW40)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOW24)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOWPV1)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOWPV2)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOW56)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOW24SAG)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOW56AM)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOW28)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOW28L)पूर्ण,
	अणुUSB_DEVICE(USB_VENDOR_ID_CODEMERCS, USB_DEVICE_ID_CODEMERCS_IOW100)पूर्ण,
	अणुपूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, iowarrior_ids);

/*
 * USB callback handler क्रम पढ़ोing data
 */
अटल व्योम iowarrior_callback(काष्ठा urb *urb)
अणु
	काष्ठा iowarrior *dev = urb->context;
	पूर्णांक पूर्णांकr_idx;
	पूर्णांक पढ़ो_idx;
	पूर्णांक aux_idx;
	पूर्णांक offset;
	पूर्णांक status = urb->status;
	पूर्णांक retval;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	शेष:
		जाओ निकास;
	पूर्ण

	पूर्णांकr_idx = atomic_पढ़ो(&dev->पूर्णांकr_idx);
	/* aux_idx become previous पूर्णांकr_idx */
	aux_idx = (पूर्णांकr_idx == 0) ? (MAX_INTERRUPT_BUFFER - 1) : (पूर्णांकr_idx - 1);
	पढ़ो_idx = atomic_पढ़ो(&dev->पढ़ो_idx);

	/* queue is not empty and it's पूर्णांकerface 0 */
	अगर ((पूर्णांकr_idx != पढ़ो_idx)
	    && (dev->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber == 0)) अणु
		/* + 1 क्रम serial number */
		offset = aux_idx * (dev->report_size + 1);
		अगर (!स_भेद
		    (dev->पढ़ो_queue + offset, urb->transfer_buffer,
		     dev->report_size)) अणु
			/* equal values on पूर्णांकerface 0 will be ignored */
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* aux_idx become next पूर्णांकr_idx */
	aux_idx = (पूर्णांकr_idx == (MAX_INTERRUPT_BUFFER - 1)) ? 0 : (पूर्णांकr_idx + 1);
	अगर (पढ़ो_idx == aux_idx) अणु
		/* queue full, dropping oldest input */
		पढ़ो_idx = (++पढ़ो_idx == MAX_INTERRUPT_BUFFER) ? 0 : पढ़ो_idx;
		atomic_set(&dev->पढ़ो_idx, पढ़ो_idx);
		atomic_set(&dev->overflow_flag, 1);
	पूर्ण

	/* +1 क्रम serial number */
	offset = पूर्णांकr_idx * (dev->report_size + 1);
	स_नकल(dev->पढ़ो_queue + offset, urb->transfer_buffer,
	       dev->report_size);
	*(dev->पढ़ो_queue + offset + (dev->report_size)) = dev->serial_number++;

	atomic_set(&dev->पूर्णांकr_idx, aux_idx);
	/* tell the blocking पढ़ो about the new data */
	wake_up_पूर्णांकerruptible(&dev->पढ़ो_रुको);

निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&dev->पूर्णांकerface->dev, "%s - usb_submit_urb failed with result %d\n",
			__func__, retval);

पूर्ण

/*
 * USB Callback handler क्रम ग_लिखो-ops
 */
अटल व्योम iowarrior_ग_लिखो_callback(काष्ठा urb *urb)
अणु
	काष्ठा iowarrior *dev;
	पूर्णांक status = urb->status;

	dev = urb->context;
	/* sync/async unlink faults aren't errors */
	अगर (status &&
	    !(status == -ENOENT ||
	      status == -ECONNRESET || status == -ESHUTDOWN)) अणु
		dev_dbg(&dev->पूर्णांकerface->dev,
			"nonzero write bulk status received: %d\n", status);
	पूर्ण
	/* मुक्त up our allocated buffer */
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	/* tell a रुकोing ग_लिखोr the पूर्णांकerrupt-out-pipe is available again */
	atomic_dec(&dev->ग_लिखो_busy);
	wake_up_पूर्णांकerruptible(&dev->ग_लिखो_रुको);
पूर्ण

/*
 *	iowarrior_delete
 */
अटल अंतरभूत व्योम iowarrior_delete(काष्ठा iowarrior *dev)
अणु
	dev_dbg(&dev->पूर्णांकerface->dev, "minor %d\n", dev->minor);
	kमुक्त(dev->पूर्णांक_in_buffer);
	usb_मुक्त_urb(dev->पूर्णांक_in_urb);
	kमुक्त(dev->पढ़ो_queue);
	usb_put_पूर्णांकf(dev->पूर्णांकerface);
	kमुक्त(dev);
पूर्ण

/*---------------------*/
/* fops implementation */
/*---------------------*/

अटल पूर्णांक पढ़ो_index(काष्ठा iowarrior *dev)
अणु
	पूर्णांक पूर्णांकr_idx, पढ़ो_idx;

	पढ़ो_idx = atomic_पढ़ो(&dev->पढ़ो_idx);
	पूर्णांकr_idx = atomic_पढ़ो(&dev->पूर्णांकr_idx);

	वापस (पढ़ो_idx == पूर्णांकr_idx ? -1 : पढ़ो_idx);
पूर्ण

/*
 *  iowarrior_पढ़ो
 */
अटल sमाप_प्रकार iowarrior_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iowarrior *dev;
	पूर्णांक पढ़ो_idx;
	पूर्णांक offset;

	dev = file->निजी_data;

	/* verअगरy that the device wasn't unplugged */
	अगर (!dev || !dev->present)
		वापस -ENODEV;

	dev_dbg(&dev->पूर्णांकerface->dev, "minor %d, count = %zd\n",
		dev->minor, count);

	/* पढ़ो count must be packet size (+ समय stamp) */
	अगर ((count != dev->report_size)
	    && (count != (dev->report_size + 1)))
		वापस -EINVAL;

	/* repeat until no buffer overrun in callback handler occur */
	करो अणु
		atomic_set(&dev->overflow_flag, 0);
		अगर ((पढ़ो_idx = पढ़ो_index(dev)) == -1) अणु
			/* queue empty */
			अगर (file->f_flags & O_NONBLOCK)
				वापस -EAGAIN;
			अन्यथा अणु
				//next line will वापस when there is either new data, or the device is unplugged
				पूर्णांक r = रुको_event_पूर्णांकerruptible(dev->पढ़ो_रुको,
								 (!dev->present
								  || (पढ़ो_idx =
								      पढ़ो_index
								      (dev)) !=
								  -1));
				अगर (r) अणु
					//we were पूर्णांकerrupted by a संकेत
					वापस -ERESTART;
				पूर्ण
				अगर (!dev->present) अणु
					//The device was unplugged
					वापस -ENODEV;
				पूर्ण
				अगर (पढ़ो_idx == -1) अणु
					// Can this happen ???
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण

		offset = पढ़ो_idx * (dev->report_size + 1);
		अगर (copy_to_user(buffer, dev->पढ़ो_queue + offset, count)) अणु
			वापस -EFAULT;
		पूर्ण
	पूर्ण जबतक (atomic_पढ़ो(&dev->overflow_flag));

	पढ़ो_idx = ++पढ़ो_idx == MAX_INTERRUPT_BUFFER ? 0 : पढ़ो_idx;
	atomic_set(&dev->पढ़ो_idx, पढ़ो_idx);
	वापस count;
पूर्ण

/*
 * iowarrior_ग_लिखो
 */
अटल sमाप_प्रकार iowarrior_ग_लिखो(काष्ठा file *file,
			       स्थिर अक्षर __user *user_buffer,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iowarrior *dev;
	पूर्णांक retval = 0;
	अक्षर *buf = शून्य;	/* क्रम IOW24 and IOW56 we need a buffer */
	काष्ठा urb *पूर्णांक_out_urb = शून्य;

	dev = file->निजी_data;

	mutex_lock(&dev->mutex);
	/* verअगरy that the device wasn't unplugged */
	अगर (!dev->present) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण
	dev_dbg(&dev->पूर्णांकerface->dev, "minor %d, count = %zd\n",
		dev->minor, count);
	/* अगर count is 0 we're alपढ़ोy करोne */
	अगर (count == 0) अणु
		retval = 0;
		जाओ निकास;
	पूर्ण
	/* We only accept full reports */
	अगर (count != dev->report_size) अणु
		retval = -EINVAL;
		जाओ निकास;
	पूर्ण
	चयन (dev->product_id) अणु
	हाल USB_DEVICE_ID_CODEMERCS_IOW24:
	हाल USB_DEVICE_ID_CODEMERCS_IOW24SAG:
	हाल USB_DEVICE_ID_CODEMERCS_IOWPV1:
	हाल USB_DEVICE_ID_CODEMERCS_IOWPV2:
	हाल USB_DEVICE_ID_CODEMERCS_IOW40:
		/* IOW24 and IOW40 use a synchronous call */
		buf = memdup_user(user_buffer, count);
		अगर (IS_ERR(buf)) अणु
			retval = PTR_ERR(buf);
			जाओ निकास;
		पूर्ण
		retval = usb_set_report(dev->पूर्णांकerface, 2, 0, buf, count);
		kमुक्त(buf);
		जाओ निकास;
	हाल USB_DEVICE_ID_CODEMERCS_IOW56:
	हाल USB_DEVICE_ID_CODEMERCS_IOW56AM:
	हाल USB_DEVICE_ID_CODEMERCS_IOW28:
	हाल USB_DEVICE_ID_CODEMERCS_IOW28L:
	हाल USB_DEVICE_ID_CODEMERCS_IOW100:
		/* The IOW56 uses asynchronous IO and more urbs */
		अगर (atomic_पढ़ो(&dev->ग_लिखो_busy) == MAX_WRITES_IN_FLIGHT) अणु
			/* Wait until we are below the limit क्रम submitted urbs */
			अगर (file->f_flags & O_NONBLOCK) अणु
				retval = -EAGAIN;
				जाओ निकास;
			पूर्ण अन्यथा अणु
				retval = रुको_event_पूर्णांकerruptible(dev->ग_लिखो_रुको,
								  (!dev->present || (atomic_पढ़ो (&dev-> ग_लिखो_busy) < MAX_WRITES_IN_FLIGHT)));
				अगर (retval) अणु
					/* we were पूर्णांकerrupted by a संकेत */
					retval = -ERESTART;
					जाओ निकास;
				पूर्ण
				अगर (!dev->present) अणु
					/* The device was unplugged */
					retval = -ENODEV;
					जाओ निकास;
				पूर्ण
				अगर (!dev->खोलोed) अणु
					/* We were बंदd जबतक रुकोing क्रम an URB */
					retval = -ENODEV;
					जाओ निकास;
				पूर्ण
			पूर्ण
		पूर्ण
		atomic_inc(&dev->ग_लिखो_busy);
		पूर्णांक_out_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!पूर्णांक_out_urb) अणु
			retval = -ENOMEM;
			जाओ error_no_urb;
		पूर्ण
		buf = usb_alloc_coherent(dev->udev, dev->report_size,
					 GFP_KERNEL, &पूर्णांक_out_urb->transfer_dma);
		अगर (!buf) अणु
			retval = -ENOMEM;
			dev_dbg(&dev->पूर्णांकerface->dev,
				"Unable to allocate buffer\n");
			जाओ error_no_buffer;
		पूर्ण
		usb_fill_पूर्णांक_urb(पूर्णांक_out_urb, dev->udev,
				 usb_sndपूर्णांकpipe(dev->udev,
						dev->पूर्णांक_out_endpoपूर्णांक->bEndpoपूर्णांकAddress),
				 buf, dev->report_size,
				 iowarrior_ग_लिखो_callback, dev,
				 dev->पूर्णांक_out_endpoपूर्णांक->bInterval);
		पूर्णांक_out_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		अगर (copy_from_user(buf, user_buffer, count)) अणु
			retval = -EFAULT;
			जाओ error;
		पूर्ण
		usb_anchor_urb(पूर्णांक_out_urb, &dev->submitted);
		retval = usb_submit_urb(पूर्णांक_out_urb, GFP_KERNEL);
		अगर (retval) अणु
			dev_dbg(&dev->पूर्णांकerface->dev,
				"submit error %d for urb nr.%d\n",
				retval, atomic_पढ़ो(&dev->ग_लिखो_busy));
			usb_unanchor_urb(पूर्णांक_out_urb);
			जाओ error;
		पूर्ण
		/* submit was ok */
		retval = count;
		usb_मुक्त_urb(पूर्णांक_out_urb);
		जाओ निकास;
	शेष:
		/* what करो we have here ? An unsupported Product-ID ? */
		dev_err(&dev->पूर्णांकerface->dev, "%s - not supported for product=0x%x\n",
			__func__, dev->product_id);
		retval = -EFAULT;
		जाओ निकास;
	पूर्ण
error:
	usb_मुक्त_coherent(dev->udev, dev->report_size, buf,
			  पूर्णांक_out_urb->transfer_dma);
error_no_buffer:
	usb_मुक्त_urb(पूर्णांक_out_urb);
error_no_urb:
	atomic_dec(&dev->ग_लिखो_busy);
	wake_up_पूर्णांकerruptible(&dev->ग_लिखो_रुको);
निकास:
	mutex_unlock(&dev->mutex);
	वापस retval;
पूर्ण

/*
 *	iowarrior_ioctl
 */
अटल दीर्घ iowarrior_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	काष्ठा iowarrior *dev = शून्य;
	__u8 *buffer;
	__u8 __user *user_buffer;
	पूर्णांक retval;
	पूर्णांक io_res;		/* checks क्रम bytes पढ़ो/written and copy_to/from_user results */

	dev = file->निजी_data;
	अगर (!dev)
		वापस -ENODEV;

	buffer = kzalloc(dev->report_size, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	mutex_lock(&dev->mutex);

	/* verअगरy that the device wasn't unplugged */
	अगर (!dev->present) अणु
		retval = -ENODEV;
		जाओ error_out;
	पूर्ण

	dev_dbg(&dev->पूर्णांकerface->dev, "minor %d, cmd 0x%.4x, arg %ld\n",
		dev->minor, cmd, arg);

	retval = 0;
	io_res = 0;
	चयन (cmd) अणु
	हाल IOW_WRITE:
		अगर (dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW24 ||
		    dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW24SAG ||
		    dev->product_id == USB_DEVICE_ID_CODEMERCS_IOWPV1 ||
		    dev->product_id == USB_DEVICE_ID_CODEMERCS_IOWPV2 ||
		    dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW40) अणु
			user_buffer = (__u8 __user *)arg;
			io_res = copy_from_user(buffer, user_buffer,
						dev->report_size);
			अगर (io_res) अणु
				retval = -EFAULT;
			पूर्ण अन्यथा अणु
				io_res = usb_set_report(dev->पूर्णांकerface, 2, 0,
							buffer,
							dev->report_size);
				अगर (io_res < 0)
					retval = io_res;
			पूर्ण
		पूर्ण अन्यथा अणु
			retval = -EINVAL;
			dev_err(&dev->पूर्णांकerface->dev,
				"ioctl 'IOW_WRITE' is not supported for product=0x%x.\n",
				dev->product_id);
		पूर्ण
		अवरोध;
	हाल IOW_READ:
		user_buffer = (__u8 __user *)arg;
		io_res = usb_get_report(dev->udev,
					dev->पूर्णांकerface->cur_altsetting, 1, 0,
					buffer, dev->report_size);
		अगर (io_res < 0)
			retval = io_res;
		अन्यथा अणु
			io_res = copy_to_user(user_buffer, buffer, dev->report_size);
			अगर (io_res)
				retval = -EFAULT;
		पूर्ण
		अवरोध;
	हाल IOW_GETINFO:
		अणु
			/* Report available inक्रमmation क्रम the device */
			काष्ठा iowarrior_info info;
			/* needed क्रम घातer consumption */
			काष्ठा usb_config_descriptor *cfg_descriptor = &dev->udev->actconfig->desc;

			स_रखो(&info, 0, माप(info));
			/* directly from the descriptor */
			info.venकरोr = le16_to_cpu(dev->udev->descriptor.idVenकरोr);
			info.product = dev->product_id;
			info.revision = le16_to_cpu(dev->udev->descriptor.bcdDevice);

			/* 0==UNKNOWN, 1==LOW(usb1.1) ,2=FULL(usb1.1), 3=HIGH(usb2.0) */
			info.speed = dev->udev->speed;
			info.अगर_num = dev->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber;
			info.report_size = dev->report_size;

			/* serial number string has been पढ़ो earlier 8 अक्षरs or empty string */
			स_नकल(info.serial, dev->chip_serial,
			       माप(dev->chip_serial));
			अगर (cfg_descriptor == शून्य) अणु
				info.घातer = -1;	/* no inक्रमmation available */
			पूर्ण अन्यथा अणु
				/* the MaxPower is stored in units of 2mA to make it fit पूर्णांकo a byte-value */
				info.घातer = cfg_descriptor->bMaxPower * 2;
			पूर्ण
			io_res = copy_to_user((काष्ठा iowarrior_info __user *)arg, &info,
					 माप(काष्ठा iowarrior_info));
			अगर (io_res)
				retval = -EFAULT;
			अवरोध;
		पूर्ण
	शेष:
		/* वापस that we did not understand this ioctl call */
		retval = -ENOTTY;
		अवरोध;
	पूर्ण
error_out:
	/* unlock the device */
	mutex_unlock(&dev->mutex);
	kमुक्त(buffer);
	वापस retval;
पूर्ण

/*
 *	iowarrior_खोलो
 */
अटल पूर्णांक iowarrior_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा iowarrior *dev = शून्य;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक subminor;
	पूर्णांक retval = 0;

	subminor = iminor(inode);

	पूर्णांकerface = usb_find_पूर्णांकerface(&iowarrior_driver, subminor);
	अगर (!पूर्णांकerface) अणु
		pr_err("%s - error, can't find device for minor %d\n",
		       __func__, subminor);
		वापस -ENODEV;
	पूर्ण

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->mutex);

	/* Only one process can खोलो each device, no sharing. */
	अगर (dev->खोलोed) अणु
		retval = -EBUSY;
		जाओ out;
	पूर्ण

	/* setup पूर्णांकerrupt handler क्रम receiving values */
	अगर ((retval = usb_submit_urb(dev->पूर्णांक_in_urb, GFP_KERNEL)) < 0) अणु
		dev_err(&पूर्णांकerface->dev, "Error %d while submitting URB\n", retval);
		retval = -EFAULT;
		जाओ out;
	पूर्ण
	/* increment our usage count क्रम the driver */
	++dev->खोलोed;
	/* save our object in the file's निजी काष्ठाure */
	file->निजी_data = dev;
	retval = 0;

out:
	mutex_unlock(&dev->mutex);
	वापस retval;
पूर्ण

/*
 *	iowarrior_release
 */
अटल पूर्णांक iowarrior_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा iowarrior *dev;
	पूर्णांक retval = 0;

	dev = file->निजी_data;
	अगर (!dev)
		वापस -ENODEV;

	dev_dbg(&dev->पूर्णांकerface->dev, "minor %d\n", dev->minor);

	/* lock our device */
	mutex_lock(&dev->mutex);

	अगर (dev->खोलोed <= 0) अणु
		retval = -ENODEV;	/* बंद called more than once */
		mutex_unlock(&dev->mutex);
	पूर्ण अन्यथा अणु
		dev->खोलोed = 0;	/* we're closing now */
		retval = 0;
		अगर (dev->present) अणु
			/*
			   The device is still connected so we only shutकरोwn
			   pending पढ़ो-/ग_लिखो-ops.
			 */
			usb_समाप्त_urb(dev->पूर्णांक_in_urb);
			wake_up_पूर्णांकerruptible(&dev->पढ़ो_रुको);
			wake_up_पूर्णांकerruptible(&dev->ग_लिखो_रुको);
			mutex_unlock(&dev->mutex);
		पूर्ण अन्यथा अणु
			/* The device was unplugged, cleanup resources */
			mutex_unlock(&dev->mutex);
			iowarrior_delete(dev);
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

अटल __poll_t iowarrior_poll(काष्ठा file *file, poll_table * रुको)
अणु
	काष्ठा iowarrior *dev = file->निजी_data;
	__poll_t mask = 0;

	अगर (!dev->present)
		वापस EPOLLERR | EPOLLHUP;

	poll_रुको(file, &dev->पढ़ो_रुको, रुको);
	poll_रुको(file, &dev->ग_लिखो_रुको, रुको);

	अगर (!dev->present)
		वापस EPOLLERR | EPOLLHUP;

	अगर (पढ़ो_index(dev) != -1)
		mask |= EPOLLIN | EPOLLRDNORM;

	अगर (atomic_पढ़ो(&dev->ग_लिखो_busy) < MAX_WRITES_IN_FLIGHT)
		mask |= EPOLLOUT | EPOLLWRNORM;
	वापस mask;
पूर्ण

/*
 * File operations needed when we रेजिस्टर this driver.
 * This assumes that this driver NEEDS file operations,
 * of course, which means that the driver is expected
 * to have a node in the /dev directory. If the USB
 * device were क्रम a network पूर्णांकerface then the driver
 * would use "struct net_driver" instead, and a serial
 * device would use "struct tty_driver".
 */
अटल स्थिर काष्ठा file_operations iowarrior_fops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = iowarrior_ग_लिखो,
	.पढ़ो = iowarrior_पढ़ो,
	.unlocked_ioctl = iowarrior_ioctl,
	.खोलो = iowarrior_खोलो,
	.release = iowarrior_release,
	.poll = iowarrior_poll,
	.llseek = noop_llseek,
पूर्ण;

अटल अक्षर *iowarrior_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "usb/%s", dev_name(dev));
पूर्ण

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device रेजिस्टरed with devfs and the driver core
 */
अटल काष्ठा usb_class_driver iowarrior_class = अणु
	.name = "iowarrior%d",
	.devnode = iowarrior_devnode,
	.fops = &iowarrior_fops,
	.minor_base = IOWARRIOR_MINOR_BASE,
पूर्ण;

/*---------------------------------*/
/*  probe and disconnect functions */
/*---------------------------------*/
/*
 *	iowarrior_probe
 *
 *	Called by the usb core when a new device is connected that it thinks
 *	this driver might be पूर्णांकerested in.
 */
अटल पूर्णांक iowarrior_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा iowarrior *dev = शून्य;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक res;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(काष्ठा iowarrior), GFP_KERNEL);
	अगर (!dev)
		वापस retval;

	mutex_init(&dev->mutex);

	atomic_set(&dev->पूर्णांकr_idx, 0);
	atomic_set(&dev->पढ़ो_idx, 0);
	atomic_set(&dev->overflow_flag, 0);
	init_रुकोqueue_head(&dev->पढ़ो_रुको);
	atomic_set(&dev->ग_लिखो_busy, 0);
	init_रुकोqueue_head(&dev->ग_लिखो_रुको);

	dev->udev = udev;
	dev->पूर्णांकerface = usb_get_पूर्णांकf(पूर्णांकerface);

	अगरace_desc = पूर्णांकerface->cur_altsetting;
	dev->product_id = le16_to_cpu(udev->descriptor.idProduct);

	init_usb_anchor(&dev->submitted);

	res = usb_find_last_पूर्णांक_in_endpoपूर्णांक(अगरace_desc, &dev->पूर्णांक_in_endpoपूर्णांक);
	अगर (res) अणु
		dev_err(&पूर्णांकerface->dev, "no interrupt-in endpoint found\n");
		retval = res;
		जाओ error;
	पूर्ण

	अगर ((dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW56) ||
	    (dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW56AM) ||
	    (dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW28) ||
	    (dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW28L) ||
	    (dev->product_id == USB_DEVICE_ID_CODEMERCS_IOW100)) अणु
		res = usb_find_last_पूर्णांक_out_endpoपूर्णांक(अगरace_desc,
				&dev->पूर्णांक_out_endpoपूर्णांक);
		अगर (res) अणु
			dev_err(&पूर्णांकerface->dev, "no interrupt-out endpoint found\n");
			retval = res;
			जाओ error;
		पूर्ण
	पूर्ण

	/* we have to check the report_size often, so remember it in the endianness suitable क्रम our machine */
	dev->report_size = usb_endpoपूर्णांक_maxp(dev->पूर्णांक_in_endpoपूर्णांक);

	/*
	 * Some devices need the report size to be dअगरferent than the
	 * endpoपूर्णांक size.
	 */
	अगर (dev->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber == 0) अणु
		चयन (dev->product_id) अणु
		हाल USB_DEVICE_ID_CODEMERCS_IOW56:
		हाल USB_DEVICE_ID_CODEMERCS_IOW56AM:
			dev->report_size = 7;
			अवरोध;

		हाल USB_DEVICE_ID_CODEMERCS_IOW28:
		हाल USB_DEVICE_ID_CODEMERCS_IOW28L:
			dev->report_size = 4;
			अवरोध;

		हाल USB_DEVICE_ID_CODEMERCS_IOW100:
			dev->report_size = 13;
			अवरोध;
		पूर्ण
	पूर्ण

	/* create the urb and buffer क्रम पढ़ोing */
	dev->पूर्णांक_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांक_in_urb)
		जाओ error;
	dev->पूर्णांक_in_buffer = kदो_स्मृति(dev->report_size, GFP_KERNEL);
	अगर (!dev->पूर्णांक_in_buffer)
		जाओ error;
	usb_fill_पूर्णांक_urb(dev->पूर्णांक_in_urb, dev->udev,
			 usb_rcvपूर्णांकpipe(dev->udev,
					dev->पूर्णांक_in_endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 dev->पूर्णांक_in_buffer, dev->report_size,
			 iowarrior_callback, dev,
			 dev->पूर्णांक_in_endpoपूर्णांक->bInterval);
	/* create an पूर्णांकernal buffer क्रम पूर्णांकerrupt data from the device */
	dev->पढ़ो_queue =
	    kदो_स्मृति_array(dev->report_size + 1, MAX_INTERRUPT_BUFFER,
			  GFP_KERNEL);
	अगर (!dev->पढ़ो_queue)
		जाओ error;
	/* Get the serial-number of the chip */
	स_रखो(dev->chip_serial, 0x00, माप(dev->chip_serial));
	usb_string(udev, udev->descriptor.iSerialNumber, dev->chip_serial,
		   माप(dev->chip_serial));
	अगर (म_माप(dev->chip_serial) != 8)
		स_रखो(dev->chip_serial, 0x00, माप(dev->chip_serial));

	/* Set the idle समयout to 0, अगर this is पूर्णांकerface 0 */
	अगर (dev->पूर्णांकerface->cur_altsetting->desc.bInterfaceNumber == 0) अणु
	    usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			    0x0A,
			    USB_TYPE_CLASS | USB_RECIP_INTERFACE, 0,
			    0, शून्य, 0, USB_CTRL_SET_TIMEOUT);
	पूर्ण
	/* allow device पढ़ो and ioctl */
	dev->present = 1;

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	retval = usb_रेजिस्टर_dev(पूर्णांकerface, &iowarrior_class);
	अगर (retval) अणु
		/* something prevented us from रेजिस्टरing this driver */
		dev_err(&पूर्णांकerface->dev, "Not able to get a minor for this device.\n");
		जाओ error;
	पूर्ण

	dev->minor = पूर्णांकerface->minor;

	/* let the user know what node this device is now attached to */
	dev_info(&पूर्णांकerface->dev, "IOWarrior product=0x%x, serial=%s interface=%d "
		 "now attached to iowarrior%d\n", dev->product_id, dev->chip_serial,
		 अगरace_desc->desc.bInterfaceNumber, dev->minor - IOWARRIOR_MINOR_BASE);
	वापस retval;

error:
	iowarrior_delete(dev);
	वापस retval;
पूर्ण

/*
 *	iowarrior_disconnect
 *
 *	Called by the usb core when the device is हटाओd from the प्रणाली.
 */
अटल व्योम iowarrior_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा iowarrior *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	पूर्णांक minor = dev->minor;

	usb_deरेजिस्टर_dev(पूर्णांकerface, &iowarrior_class);

	mutex_lock(&dev->mutex);

	/* prevent device पढ़ो, ग_लिखो and ioctl */
	dev->present = 0;

	अगर (dev->खोलोed) अणु
		/* There is a process that holds a filedescriptor to the device ,
		   so we only shutकरोwn पढ़ो-/ग_लिखो-ops going on.
		   Deleting the device is postponed until बंद() was called.
		 */
		usb_समाप्त_urb(dev->पूर्णांक_in_urb);
		usb_समाप्त_anchored_urbs(&dev->submitted);
		wake_up_पूर्णांकerruptible(&dev->पढ़ो_रुको);
		wake_up_पूर्णांकerruptible(&dev->ग_लिखो_रुको);
		mutex_unlock(&dev->mutex);
	पूर्ण अन्यथा अणु
		/* no process is using the device, cleanup now */
		mutex_unlock(&dev->mutex);
		iowarrior_delete(dev);
	पूर्ण

	dev_info(&पूर्णांकerface->dev, "I/O-Warror #%d now disconnected\n",
		 minor - IOWARRIOR_MINOR_BASE);
पूर्ण

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver iowarrior_driver = अणु
	.name = "iowarrior",
	.probe = iowarrior_probe,
	.disconnect = iowarrior_disconnect,
	.id_table = iowarrior_ids,
पूर्ण;

module_usb_driver(iowarrior_driver);
