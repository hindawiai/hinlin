<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*****************************************************************************
 *                          USBLCD Kernel Driver                             *
 *                            Version 1.05                                   *
 *             (C) 2005 Georges Toth <g.toth@e-biz.lu>                       *
 *                                                                           *
 *     This file is licensed under the GPL. See COPYING in the package.      *
 * Based on usb-skeleton.c 2.0 by Greg Kroah-Harपंचांगan (greg@kroah.com)        *
 *                                                                           *
 *                                                                           *
 * 28.02.05 Complete reग_लिखो of the original usblcd.c driver,                *
 *          based on usb_skeleton.c.                                         *
 *          This new driver allows more than one USB-LCD to be connected     *
 *          and controlled, at once                                          *
 *****************************************************************************/
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>

#घोषणा DRIVER_VERSION "USBLCD Driver Version 1.05"

#घोषणा USBLCD_MINOR		144

#घोषणा IOCTL_GET_HARD_VERSION	1
#घोषणा IOCTL_GET_DRV_VERSION	2


अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु .idVenकरोr = 0x10D2, .match_flags = USB_DEVICE_ID_MATCH_VENDOR, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

काष्ठा usb_lcd अणु
	काष्ठा usb_device	*udev;			/* init: probe_lcd */
	काष्ठा usb_पूर्णांकerface	*पूर्णांकerface;		/* the पूर्णांकerface क्रम
							   this device */
	अचिन्हित अक्षर		*bulk_in_buffer;	/* the buffer to receive
							   data */
	माप_प्रकार			bulk_in_size;		/* the size of the
							   receive buffer */
	__u8			bulk_in_endpoपूर्णांकAddr;	/* the address of the
							   bulk in endpoपूर्णांक */
	__u8			bulk_out_endpoपूर्णांकAddr;	/* the address of the
							   bulk out endpoपूर्णांक */
	काष्ठा kref		kref;
	काष्ठा semaphore	limit_sem;		/* to stop ग_लिखोs at
							   full throttle from
							   using up all RAM */
	काष्ठा usb_anchor	submitted;		/* URBs to रुको क्रम
							   beक्रमe suspend */
	काष्ठा rw_semaphore	io_rwsem;
	अचिन्हित दीर्घ		disconnected:1;
पूर्ण;
#घोषणा to_lcd_dev(d) container_of(d, काष्ठा usb_lcd, kref)

#घोषणा USB_LCD_CONCURRENT_WRITES	5

अटल काष्ठा usb_driver lcd_driver;


अटल व्योम lcd_delete(काष्ठा kref *kref)
अणु
	काष्ठा usb_lcd *dev = to_lcd_dev(kref);

	usb_put_dev(dev->udev);
	kमुक्त(dev->bulk_in_buffer);
	kमुक्त(dev);
पूर्ण


अटल पूर्णांक lcd_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_lcd *dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक subminor, r;

	subminor = iminor(inode);

	पूर्णांकerface = usb_find_पूर्णांकerface(&lcd_driver, subminor);
	अगर (!पूर्णांकerface) अणु
		pr_err("USBLCD: %s - error, can't find device for minor %d\n",
		       __func__, subminor);
		वापस -ENODEV;
	पूर्ण

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	/* increment our usage count क्रम the device */
	kref_get(&dev->kref);

	/* grab a घातer reference */
	r = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकerface);
	अगर (r < 0) अणु
		kref_put(&dev->kref, lcd_delete);
		वापस r;
	पूर्ण

	/* save our object in the file's निजी काष्ठाure */
	file->निजी_data = dev;

	वापस 0;
पूर्ण

अटल पूर्णांक lcd_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_lcd *dev;

	dev = file->निजी_data;
	अगर (dev == शून्य)
		वापस -ENODEV;

	/* decrement the count on our device */
	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकerface);
	kref_put(&dev->kref, lcd_delete);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार lcd_पढ़ो(काष्ठा file *file, अक्षर __user * buffer,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा usb_lcd *dev;
	पूर्णांक retval = 0;
	पूर्णांक bytes_पढ़ो;

	dev = file->निजी_data;

	करोwn_पढ़ो(&dev->io_rwsem);

	अगर (dev->disconnected) अणु
		retval = -ENODEV;
		जाओ out_up_io;
	पूर्ण

	/* करो a blocking bulk पढ़ो to get data from the device */
	retval = usb_bulk_msg(dev->udev,
			      usb_rcvbulkpipe(dev->udev,
					      dev->bulk_in_endpoपूर्णांकAddr),
			      dev->bulk_in_buffer,
			      min(dev->bulk_in_size, count),
			      &bytes_पढ़ो, 10000);

	/* अगर the पढ़ो was successful, copy the data to userspace */
	अगर (!retval) अणु
		अगर (copy_to_user(buffer, dev->bulk_in_buffer, bytes_पढ़ो))
			retval = -EFAULT;
		अन्यथा
			retval = bytes_पढ़ो;
	पूर्ण

out_up_io:
	up_पढ़ो(&dev->io_rwsem);

	वापस retval;
पूर्ण

अटल दीर्घ lcd_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usb_lcd *dev;
	u16 bcdDevice;
	अक्षर buf[30];

	dev = file->निजी_data;
	अगर (dev == शून्य)
		वापस -ENODEV;

	चयन (cmd) अणु
	हाल IOCTL_GET_HARD_VERSION:
		bcdDevice = le16_to_cpu((dev->udev)->descriptor.bcdDevice);
		प्र_लिखो(buf, "%1d%1d.%1d%1d",
			(bcdDevice & 0xF000)>>12,
			(bcdDevice & 0xF00)>>8,
			(bcdDevice & 0xF0)>>4,
			(bcdDevice & 0xF));
		अगर (copy_to_user((व्योम __user *)arg, buf, म_माप(buf)) != 0)
			वापस -EFAULT;
		अवरोध;
	हाल IOCTL_GET_DRV_VERSION:
		प्र_लिखो(buf, DRIVER_VERSION);
		अगर (copy_to_user((व्योम __user *)arg, buf, म_माप(buf)) != 0)
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -ENOTTY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lcd_ग_लिखो_bulk_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_lcd *dev;
	पूर्णांक status = urb->status;

	dev = urb->context;

	/* sync/async unlink faults aren't errors */
	अगर (status &&
	    !(status == -ENOENT ||
	      status == -ECONNRESET ||
	      status == -ESHUTDOWN)) अणु
		dev_dbg(&dev->पूर्णांकerface->dev,
			"nonzero write bulk status received: %d\n", status);
	पूर्ण

	/* मुक्त up our allocated buffer */
	usb_मुक्त_coherent(urb->dev, urb->transfer_buffer_length,
			  urb->transfer_buffer, urb->transfer_dma);
	up(&dev->limit_sem);
पूर्ण

अटल sमाप_प्रकार lcd_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user * user_buffer,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा usb_lcd *dev;
	पूर्णांक retval = 0, r;
	काष्ठा urb *urb = शून्य;
	अक्षर *buf = शून्य;

	dev = file->निजी_data;

	/* verअगरy that we actually have some data to ग_लिखो */
	अगर (count == 0)
		जाओ निकास;

	r = करोwn_पूर्णांकerruptible(&dev->limit_sem);
	अगर (r < 0)
		वापस -EINTR;

	करोwn_पढ़ो(&dev->io_rwsem);

	अगर (dev->disconnected) अणु
		retval = -ENODEV;
		जाओ err_up_io;
	पूर्ण

	/* create a urb, and a buffer क्रम it, and copy the data to the urb */
	urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!urb) अणु
		retval = -ENOMEM;
		जाओ err_up_io;
	पूर्ण

	buf = usb_alloc_coherent(dev->udev, count, GFP_KERNEL,
				 &urb->transfer_dma);
	अगर (!buf) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	अगर (copy_from_user(buf, user_buffer, count)) अणु
		retval = -EFAULT;
		जाओ error;
	पूर्ण

	/* initialize the urb properly */
	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev,
			  dev->bulk_out_endpoपूर्णांकAddr),
			  buf, count, lcd_ग_लिखो_bulk_callback, dev);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	usb_anchor_urb(urb, &dev->submitted);

	/* send the data out the bulk port */
	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&dev->udev->dev,
			"%s - failed submitting write urb, error %d\n",
			__func__, retval);
		जाओ error_unanchor;
	पूर्ण

	/* release our reference to this urb,
	   the USB core will eventually मुक्त it entirely */
	usb_मुक्त_urb(urb);

	up_पढ़ो(&dev->io_rwsem);
निकास:
	वापस count;
error_unanchor:
	usb_unanchor_urb(urb);
error:
	usb_मुक्त_coherent(dev->udev, count, buf, urb->transfer_dma);
	usb_मुक्त_urb(urb);
err_up_io:
	up_पढ़ो(&dev->io_rwsem);
	up(&dev->limit_sem);
	वापस retval;
पूर्ण

अटल स्थिर काष्ठा file_operations lcd_fops = अणु
	.owner =        THIS_MODULE,
	.पढ़ो =         lcd_पढ़ो,
	.ग_लिखो =        lcd_ग_लिखो,
	.खोलो =         lcd_खोलो,
	.unlocked_ioctl = lcd_ioctl,
	.release =      lcd_release,
	.llseek =	 noop_llseek,
पूर्ण;

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device रेजिस्टरed with the driver core
 */
अटल काष्ठा usb_class_driver lcd_class = अणु
	.name =         "lcd%d",
	.fops =         &lcd_fops,
	.minor_base =   USBLCD_MINOR,
पूर्ण;

अटल पूर्णांक lcd_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		     स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_lcd *dev = शून्य;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_in, *bulk_out;
	पूर्णांक i;
	पूर्णांक retval;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	kref_init(&dev->kref);
	sema_init(&dev->limit_sem, USB_LCD_CONCURRENT_WRITES);
	init_rwsem(&dev->io_rwsem);
	init_usb_anchor(&dev->submitted);

	dev->udev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	dev->पूर्णांकerface = पूर्णांकerface;

	अगर (le16_to_cpu(dev->udev->descriptor.idProduct) != 0x0001) अणु
		dev_warn(&पूर्णांकerface->dev, "USBLCD model not supported.\n");
		retval = -ENODEV;
		जाओ error;
	पूर्ण

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

	dev->bulk_out_endpoपूर्णांकAddr = bulk_out->bEndpoपूर्णांकAddress;

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	retval = usb_रेजिस्टर_dev(पूर्णांकerface, &lcd_class);
	अगर (retval) अणु
		/* something prevented us from रेजिस्टरing this driver */
		dev_err(&पूर्णांकerface->dev,
			"Not able to get a minor for this device.\n");
		जाओ error;
	पूर्ण

	i = le16_to_cpu(dev->udev->descriptor.bcdDevice);

	dev_info(&पूर्णांकerface->dev, "USBLCD Version %1d%1d.%1d%1d found "
		 "at address %d\n", (i & 0xF000)>>12, (i & 0xF00)>>8,
		 (i & 0xF0)>>4, (i & 0xF), dev->udev->devnum);

	/* let the user know what node this device is now attached to */
	dev_info(&पूर्णांकerface->dev, "USB LCD device now attached to USBLCD-%d\n",
		 पूर्णांकerface->minor);
	वापस 0;

error:
	kref_put(&dev->kref, lcd_delete);
	वापस retval;
पूर्ण

अटल व्योम lcd_draw_करोwn(काष्ठा usb_lcd *dev)
अणु
	पूर्णांक समय;

	समय = usb_रुको_anchor_empty_समयout(&dev->submitted, 1000);
	अगर (!समय)
		usb_समाप्त_anchored_urbs(&dev->submitted);
पूर्ण

अटल पूर्णांक lcd_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usb_lcd *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!dev)
		वापस 0;
	lcd_draw_करोwn(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक lcd_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

अटल व्योम lcd_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_lcd *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	पूर्णांक minor = पूर्णांकerface->minor;

	/* give back our minor */
	usb_deरेजिस्टर_dev(पूर्णांकerface, &lcd_class);

	करोwn_ग_लिखो(&dev->io_rwsem);
	dev->disconnected = 1;
	up_ग_लिखो(&dev->io_rwsem);

	usb_समाप्त_anchored_urbs(&dev->submitted);

	/* decrement our usage count */
	kref_put(&dev->kref, lcd_delete);

	dev_info(&पूर्णांकerface->dev, "USB LCD #%d now disconnected\n", minor);
पूर्ण

अटल काष्ठा usb_driver lcd_driver = अणु
	.name =		"usblcd",
	.probe =	lcd_probe,
	.disconnect =	lcd_disconnect,
	.suspend =	lcd_suspend,
	.resume =	lcd_resume,
	.id_table =	id_table,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(lcd_driver);

MODULE_AUTHOR("Georges Toth <g.toth@e-biz.lu>");
MODULE_DESCRIPTION(DRIVER_VERSION);
MODULE_LICENSE("GPL");
