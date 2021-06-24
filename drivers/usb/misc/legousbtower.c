<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * LEGO USB Tower driver
 *
 * Copyright (C) 2003 David Glance <davidgsf@sourceक्रमge.net>
 *               2001-2004 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *
 * derived from USB Skeleton driver - 0.5
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan (greg@kroah.com)
 *
 * History:
 *
 * 2001-10-13 - 0.1 js
 *   - first version
 * 2001-11-03 - 0.2 js
 *   - simplअगरied buffering, one-shot URBs क्रम writing
 * 2001-11-10 - 0.3 js
 *   - हटाओd IOCTL (setting घातer/mode is more complicated, postponed)
 * 2001-11-28 - 0.4 js
 *   - added venकरोr commands क्रम mode of operation and घातer level in खोलो
 * 2001-12-04 - 0.5 js
 *   - set IR mode by शेष (by oversight 0.4 set VLL mode)
 * 2002-01-11 - 0.5? pcchan
 *   - make पढ़ो buffer reusable and work around bytes_to_ग_लिखो issue between
 *     uhci and legusbtower
 * 2002-09-23 - 0.52 david (david@csse.uwa.edu.au)
 *   - imported पूर्णांकo lejos project
 *   - changed wake_up to wake_up_पूर्णांकerruptible
 *   - changed to use lego0 rather than tower0
 *   - changed dbg() to use __func__ rather than deprecated __func__
 * 2003-01-12 - 0.53 david (david@csse.uwa.edu.au)
 *   - changed पढ़ो and ग_लिखो to ग_लिखो everything or
 *     समयout (from a patch by Chris Riesen and Brett Thaeler driver)
 *   - added ioctl functionality to set समयouts
 * 2003-07-18 - 0.54 davidgsf (david@csse.uwa.edu.au)
 *   - initial import पूर्णांकo LegoUSB project
 *   - merge of existing LegoUSB.c driver
 * 2003-07-18 - 0.56 davidgsf (david@csse.uwa.edu.au)
 *   - port to 2.6 style driver
 * 2004-02-29 - 0.6 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - fix locking
 *   - unlink पढ़ो URBs which are no दीर्घer needed
 *   - allow increased buffer size, eliminates need क्रम समयout on ग_लिखो
 *   - have पढ़ो URB running continuously
 *   - added poll
 *   - क्रमbid seeking
 *   - added nonblocking I/O
 *   - changed back __func__ to __func__
 *   - पढ़ो and log tower firmware version
 *   - reset tower on probe, aव्योमs failure of first ग_लिखो
 * 2004-03-09 - 0.7 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - समयout पढ़ो now only after inactivity, लघुen शेष accordingly
 * 2004-03-11 - 0.8 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - log major, minor instead of possibly confusing device filename
 *   - whitespace cleanup
 * 2004-03-12 - 0.9 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - normalize whitespace in debug messages
 *   - take care about endianness in control message responses
 * 2004-03-13 - 0.91 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - make शेष पूर्णांकervals दीर्घer to accommodate current EHCI driver
 * 2004-03-19 - 0.92 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - replaced atomic_t by memory barriers
 * 2004-04-21 - 0.93 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - रुको क्रम completion of ग_लिखो urb in release (needed क्रम remotecontrol)
 *   - corrected poll क्रम ग_लिखो direction (missing negation)
 * 2004-04-22 - 0.94 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - make device locking पूर्णांकerruptible
 * 2004-04-30 - 0.95 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - check क्रम valid udev on resubmitting and unlinking urbs
 * 2004-08-03 - 0.96 Juergen Stuber <starblue@users.sourceक्रमge.net>
 *   - move reset पूर्णांकo खोलो to clean out spurious data
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/poll.h>


#घोषणा DRIVER_AUTHOR "Juergen Stuber <starblue@sourceforge.net>"
#घोषणा DRIVER_DESC "LEGO USB Tower Driver"


/* The शेषs are chosen to work with the latest versions of leJOS and NQC.
 */

/* Some legacy software likes to receive packets in one piece.
 * In this हाल पढ़ो_buffer_size should exceed the maximal packet length
 * (417 क्रम datalog uploads), and packet_समयout should be set.
 */
अटल पूर्णांक पढ़ो_buffer_size = 480;
module_param(पढ़ो_buffer_size, पूर्णांक, 0);
MODULE_PARM_DESC(पढ़ो_buffer_size, "Read buffer size");

/* Some legacy software likes to send packets in one piece.
 * In this हाल ग_लिखो_buffer_size should exceed the maximal packet length
 * (417 क्रम firmware and program करोwnloads).
 * A problem with दीर्घ ग_लिखोs is that the following पढ़ो may समय out
 * अगर the software is not prepared to रुको दीर्घ enough.
 */
अटल पूर्णांक ग_लिखो_buffer_size = 480;
module_param(ग_लिखो_buffer_size, पूर्णांक, 0);
MODULE_PARM_DESC(ग_लिखो_buffer_size, "Write buffer size");

/* Some legacy software expects पढ़ोs to contain whole LASM packets.
 * To achieve this, अक्षरacters which arrive beक्रमe a packet समयout
 * occurs will be वापसed in a single पढ़ो operation.
 * A problem with दीर्घ पढ़ोs is that the software may समय out
 * अगर it is not prepared to रुको दीर्घ enough.
 * The packet समयout should be greater than the समय between the
 * reception of subsequent अक्षरacters, which should arrive about
 * every 5ms क्रम the standard 2400 baud.
 * Set it to 0 to disable.
 */
अटल पूर्णांक packet_समयout = 50;
module_param(packet_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(packet_समयout, "Packet timeout in ms");

/* Some legacy software expects blocking पढ़ोs to समय out.
 * Timeout occurs after the specअगरied समय of पढ़ो and ग_लिखो inactivity.
 * Set it to 0 to disable.
 */
अटल पूर्णांक पढ़ो_समयout = 200;
module_param(पढ़ो_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(पढ़ो_समयout, "Read timeout in ms");

/* As of kernel version 2.6.4 ehci-hcd uses an
 * "only one interrupt transfer per frame" लघुcut
 * to simplअगरy the scheduling of periodic transfers.
 * This conflicts with our standard 1ms पूर्णांकervals क्रम in and out URBs.
 * We use शेष पूर्णांकervals of 2ms क्रम in and 8ms क्रम out transfers,
 * which is fast enough क्रम 2400 baud and allows a small additional load.
 * Increase the पूर्णांकerval to allow more devices that करो पूर्णांकerrupt transfers,
 * or set to 0 to use the standard पूर्णांकerval from the endpoपूर्णांक descriptors.
 */
अटल पूर्णांक पूर्णांकerrupt_in_पूर्णांकerval = 2;
module_param(पूर्णांकerrupt_in_पूर्णांकerval, पूर्णांक, 0);
MODULE_PARM_DESC(पूर्णांकerrupt_in_पूर्णांकerval, "Interrupt in interval in ms");

अटल पूर्णांक पूर्णांकerrupt_out_पूर्णांकerval = 8;
module_param(पूर्णांकerrupt_out_पूर्णांकerval, पूर्णांक, 0);
MODULE_PARM_DESC(पूर्णांकerrupt_out_पूर्णांकerval, "Interrupt out interval in ms");

/* Define these values to match your device */
#घोषणा LEGO_USB_TOWER_VENDOR_ID	0x0694
#घोषणा LEGO_USB_TOWER_PRODUCT_ID	0x0001

/* Venकरोr requests */
#घोषणा LEGO_USB_TOWER_REQUEST_RESET		0x04
#घोषणा LEGO_USB_TOWER_REQUEST_GET_VERSION	0xFD

काष्ठा tower_reset_reply अणु
	__le16 size;
	__u8 err_code;
	__u8 spare;
पूर्ण;

काष्ठा tower_get_version_reply अणु
	__le16 size;
	__u8 err_code;
	__u8 spare;
	__u8 major;
	__u8 minor;
	__le16 build_no;
पूर्ण;


/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id tower_table[] = अणु
	अणु USB_DEVICE(LEGO_USB_TOWER_VENDOR_ID, LEGO_USB_TOWER_PRODUCT_ID) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, tower_table);

#घोषणा LEGO_USB_TOWER_MINOR_BASE	160


/* Structure to hold all of our device specअगरic stuff */
काष्ठा lego_usb_tower अणु
	काष्ठा mutex		lock;		/* locks this काष्ठाure */
	काष्ठा usb_device	*udev;		/* save off the usb device poपूर्णांकer */
	अचिन्हित अक्षर		minor;		/* the starting minor number क्रम this device */

	पूर्णांक			खोलो_count;	/* number of बार this port has been खोलोed */
	अचिन्हित दीर्घ		disconnected:1;

	अक्षर			*पढ़ो_buffer;
	माप_प्रकार			पढ़ो_buffer_length; /* this much came in */
	माप_प्रकार			पढ़ो_packet_length; /* this much will be वापसed on पढ़ो */
	spinlock_t		पढ़ो_buffer_lock;
	पूर्णांक			packet_समयout_jअगरfies;
	अचिन्हित दीर्घ		पढ़ो_last_arrival;

	रुको_queue_head_t	पढ़ो_रुको;
	रुको_queue_head_t	ग_लिखो_रुको;

	अक्षर			*पूर्णांकerrupt_in_buffer;
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकerrupt_in_endpoपूर्णांक;
	काष्ठा urb		*पूर्णांकerrupt_in_urb;
	पूर्णांक			पूर्णांकerrupt_in_पूर्णांकerval;
	पूर्णांक			पूर्णांकerrupt_in_करोne;

	अक्षर			*पूर्णांकerrupt_out_buffer;
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकerrupt_out_endpoपूर्णांक;
	काष्ठा urb		*पूर्णांकerrupt_out_urb;
	पूर्णांक			पूर्णांकerrupt_out_पूर्णांकerval;
	पूर्णांक			पूर्णांकerrupt_out_busy;

पूर्ण;


/* local function prototypes */
अटल sमाप_प्रकार tower_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos);
अटल sमाप_प्रकार tower_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos);
अटल अंतरभूत व्योम tower_delete(काष्ठा lego_usb_tower *dev);
अटल पूर्णांक tower_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक tower_release(काष्ठा inode *inode, काष्ठा file *file);
अटल __poll_t tower_poll(काष्ठा file *file, poll_table *रुको);
अटल loff_t tower_llseek(काष्ठा file *file, loff_t off, पूर्णांक whence);

अटल व्योम tower_check_क्रम_पढ़ो_packet(काष्ठा lego_usb_tower *dev);
अटल व्योम tower_पूर्णांकerrupt_in_callback(काष्ठा urb *urb);
अटल व्योम tower_पूर्णांकerrupt_out_callback(काष्ठा urb *urb);

अटल पूर्णांक  tower_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, स्थिर काष्ठा usb_device_id *id);
अटल व्योम tower_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);


/* file operations needed when we रेजिस्टर this driver */
अटल स्थिर काष्ठा file_operations tower_fops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो  =	tower_पढ़ो,
	.ग_लिखो =	tower_ग_लिखो,
	.खोलो =		tower_खोलो,
	.release =	tower_release,
	.poll =		tower_poll,
	.llseek =	tower_llseek,
पूर्ण;

अटल अक्षर *legousbtower_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "usb/%s", dev_name(dev));
पूर्ण

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device रेजिस्टरed with the driver core
 */
अटल काष्ठा usb_class_driver tower_class = अणु
	.name =		"legousbtower%d",
	.devnode = 	legousbtower_devnode,
	.fops =		&tower_fops,
	.minor_base =	LEGO_USB_TOWER_MINOR_BASE,
पूर्ण;


/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver tower_driver = अणु
	.name =		"legousbtower",
	.probe =	tower_probe,
	.disconnect =	tower_disconnect,
	.id_table =	tower_table,
पूर्ण;


/*
 *	lego_usb_tower_debug_data
 */
अटल अंतरभूत व्योम lego_usb_tower_debug_data(काष्ठा device *dev,
					     स्थिर अक्षर *function, पूर्णांक size,
					     स्थिर अचिन्हित अक्षर *data)
अणु
	dev_dbg(dev, "%s - length = %d, data = %*ph\n",
		function, size, size, data);
पूर्ण


/*
 *	tower_delete
 */
अटल अंतरभूत व्योम tower_delete(काष्ठा lego_usb_tower *dev)
अणु
	/* मुक्त data काष्ठाures */
	usb_मुक्त_urb(dev->पूर्णांकerrupt_in_urb);
	usb_मुक्त_urb(dev->पूर्णांकerrupt_out_urb);
	kमुक्त(dev->पढ़ो_buffer);
	kमुक्त(dev->पूर्णांकerrupt_in_buffer);
	kमुक्त(dev->पूर्णांकerrupt_out_buffer);
	usb_put_dev(dev->udev);
	kमुक्त(dev);
पूर्ण


/*
 *	tower_खोलो
 */
अटल पूर्णांक tower_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा lego_usb_tower *dev = शून्य;
	पूर्णांक subminor;
	पूर्णांक retval = 0;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	काष्ठा tower_reset_reply reset_reply;
	पूर्णांक result;

	nonseekable_खोलो(inode, file);
	subminor = iminor(inode);

	पूर्णांकerface = usb_find_पूर्णांकerface(&tower_driver, subminor);
	अगर (!पूर्णांकerface) अणु
		pr_err("error, can't find device for minor %d\n", subminor);
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	/* lock this device */
	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock)) अणु
	        retval = -ERESTARTSYS;
		जाओ निकास;
	पूर्ण


	/* allow खोलोing only once */
	अगर (dev->खोलो_count) अणु
		retval = -EBUSY;
		जाओ unlock_निकास;
	पूर्ण

	/* reset the tower */
	result = usb_control_msg_recv(dev->udev, 0,
				      LEGO_USB_TOWER_REQUEST_RESET,
				      USB_TYPE_VENDOR | USB_सूची_IN | USB_RECIP_DEVICE,
				      0, 0,
				      &reset_reply, माप(reset_reply), 1000,
				      GFP_KERNEL);
	अगर (result < 0) अणु
		dev_err(&dev->udev->dev,
			"LEGO USB Tower reset control request failed\n");
		retval = result;
		जाओ unlock_निकास;
	पूर्ण

	/* initialize in direction */
	dev->पढ़ो_buffer_length = 0;
	dev->पढ़ो_packet_length = 0;
	usb_fill_पूर्णांक_urb(dev->पूर्णांकerrupt_in_urb,
			 dev->udev,
			 usb_rcvपूर्णांकpipe(dev->udev, dev->पूर्णांकerrupt_in_endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 dev->पूर्णांकerrupt_in_buffer,
			 usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_in_endpoपूर्णांक),
			 tower_पूर्णांकerrupt_in_callback,
			 dev,
			 dev->पूर्णांकerrupt_in_पूर्णांकerval);

	dev->पूर्णांकerrupt_in_करोne = 0;
	mb();

	retval = usb_submit_urb(dev->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&dev->udev->dev,
			"Couldn't submit interrupt_in_urb %d\n", retval);
		जाओ unlock_निकास;
	पूर्ण

	/* save device in the file's निजी काष्ठाure */
	file->निजी_data = dev;

	dev->खोलो_count = 1;

unlock_निकास:
	mutex_unlock(&dev->lock);

निकास:
	वापस retval;
पूर्ण

/*
 *	tower_release
 */
अटल पूर्णांक tower_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा lego_usb_tower *dev;
	पूर्णांक retval = 0;

	dev = file->निजी_data;
	अगर (dev == शून्य) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	mutex_lock(&dev->lock);

	अगर (dev->disconnected) अणु
		/* the device was unplugged beक्रमe the file was released */

		/* unlock here as tower_delete मुक्तs dev */
		mutex_unlock(&dev->lock);
		tower_delete(dev);
		जाओ निकास;
	पूर्ण

	/* रुको until ग_लिखो transfer is finished */
	अगर (dev->पूर्णांकerrupt_out_busy) अणु
		रुको_event_पूर्णांकerruptible_समयout(dev->ग_लिखो_रुको, !dev->पूर्णांकerrupt_out_busy,
						 2 * HZ);
	पूर्ण

	/* shutकरोwn transfers */
	usb_समाप्त_urb(dev->पूर्णांकerrupt_in_urb);
	usb_समाप्त_urb(dev->पूर्णांकerrupt_out_urb);

	dev->खोलो_count = 0;

	mutex_unlock(&dev->lock);
निकास:
	वापस retval;
पूर्ण

/*
 *	tower_check_क्रम_पढ़ो_packet
 *
 *      To get correct semantics क्रम संकेतs and non-blocking I/O
 *      with packetizing we pretend not to see any data in the पढ़ो buffer
 *      until it has been there unchanged क्रम at least
 *      dev->packet_समयout_jअगरfies, or until the buffer is full.
 */
अटल व्योम tower_check_क्रम_पढ़ो_packet(काष्ठा lego_usb_tower *dev)
अणु
	spin_lock_irq(&dev->पढ़ो_buffer_lock);
	अगर (!packet_समयout
	    || समय_after(jअगरfies, dev->पढ़ो_last_arrival + dev->packet_समयout_jअगरfies)
	    || dev->पढ़ो_buffer_length == पढ़ो_buffer_size) अणु
		dev->पढ़ो_packet_length = dev->पढ़ो_buffer_length;
	पूर्ण
	dev->पूर्णांकerrupt_in_करोne = 0;
	spin_unlock_irq(&dev->पढ़ो_buffer_lock);
पूर्ण


/*
 *	tower_poll
 */
अटल __poll_t tower_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा lego_usb_tower *dev;
	__poll_t mask = 0;

	dev = file->निजी_data;

	अगर (dev->disconnected)
		वापस EPOLLERR | EPOLLHUP;

	poll_रुको(file, &dev->पढ़ो_रुको, रुको);
	poll_रुको(file, &dev->ग_लिखो_रुको, रुको);

	tower_check_क्रम_पढ़ो_packet(dev);
	अगर (dev->पढ़ो_packet_length > 0)
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (!dev->पूर्णांकerrupt_out_busy)
		mask |= EPOLLOUT | EPOLLWRNORM;

	वापस mask;
पूर्ण


/*
 *	tower_llseek
 */
अटल loff_t tower_llseek(काष्ठा file *file, loff_t off, पूर्णांक whence)
अणु
	वापस -ESPIPE;		/* unseekable */
पूर्ण


/*
 *	tower_पढ़ो
 */
अटल sमाप_प्रकार tower_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lego_usb_tower *dev;
	माप_प्रकार bytes_to_पढ़ो;
	पूर्णांक i;
	पूर्णांक retval = 0;
	अचिन्हित दीर्घ समयout = 0;

	dev = file->निजी_data;

	/* lock this object */
	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock)) अणु
		retval = -ERESTARTSYS;
		जाओ निकास;
	पूर्ण

	/* verअगरy that the device wasn't unplugged */
	अगर (dev->disconnected) अणु
		retval = -ENODEV;
		जाओ unlock_निकास;
	पूर्ण

	/* verअगरy that we actually have some data to पढ़ो */
	अगर (count == 0) अणु
		dev_dbg(&dev->udev->dev, "read request of 0 bytes\n");
		जाओ unlock_निकास;
	पूर्ण

	अगर (पढ़ो_समयout)
		समयout = jअगरfies + msecs_to_jअगरfies(पढ़ो_समयout);

	/* रुको क्रम data */
	tower_check_क्रम_पढ़ो_packet(dev);
	जबतक (dev->पढ़ो_packet_length == 0) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			जाओ unlock_निकास;
		पूर्ण
		retval = रुको_event_पूर्णांकerruptible_समयout(dev->पढ़ो_रुको, dev->पूर्णांकerrupt_in_करोne, dev->packet_समयout_jअगरfies);
		अगर (retval < 0)
			जाओ unlock_निकास;

		/* reset पढ़ो समयout during पढ़ो or ग_लिखो activity */
		अगर (पढ़ो_समयout
		    && (dev->पढ़ो_buffer_length || dev->पूर्णांकerrupt_out_busy)) अणु
			समयout = jअगरfies + msecs_to_jअगरfies(पढ़ो_समयout);
		पूर्ण
		/* check क्रम पढ़ो समयout */
		अगर (पढ़ो_समयout && समय_after(jअगरfies, समयout)) अणु
			retval = -ETIMEDOUT;
			जाओ unlock_निकास;
		पूर्ण
		tower_check_क्रम_पढ़ो_packet(dev);
	पूर्ण

	/* copy the data from पढ़ो_buffer पूर्णांकo userspace */
	bytes_to_पढ़ो = min(count, dev->पढ़ो_packet_length);

	अगर (copy_to_user(buffer, dev->पढ़ो_buffer, bytes_to_पढ़ो)) अणु
		retval = -EFAULT;
		जाओ unlock_निकास;
	पूर्ण

	spin_lock_irq(&dev->पढ़ो_buffer_lock);
	dev->पढ़ो_buffer_length -= bytes_to_पढ़ो;
	dev->पढ़ो_packet_length -= bytes_to_पढ़ो;
	क्रम (i = 0; i < dev->पढ़ो_buffer_length; i++)
		dev->पढ़ो_buffer[i] = dev->पढ़ो_buffer[i+bytes_to_पढ़ो];
	spin_unlock_irq(&dev->पढ़ो_buffer_lock);

	retval = bytes_to_पढ़ो;

unlock_निकास:
	/* unlock the device */
	mutex_unlock(&dev->lock);

निकास:
	वापस retval;
पूर्ण


/*
 *	tower_ग_लिखो
 */
अटल sमाप_प्रकार tower_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा lego_usb_tower *dev;
	माप_प्रकार bytes_to_ग_लिखो;
	पूर्णांक retval = 0;

	dev = file->निजी_data;

	/* lock this object */
	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock)) अणु
		retval = -ERESTARTSYS;
		जाओ निकास;
	पूर्ण

	/* verअगरy that the device wasn't unplugged */
	अगर (dev->disconnected) अणु
		retval = -ENODEV;
		जाओ unlock_निकास;
	पूर्ण

	/* verअगरy that we actually have some data to ग_लिखो */
	अगर (count == 0) अणु
		dev_dbg(&dev->udev->dev, "write request of 0 bytes\n");
		जाओ unlock_निकास;
	पूर्ण

	/* रुको until previous transfer is finished */
	जबतक (dev->पूर्णांकerrupt_out_busy) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			जाओ unlock_निकास;
		पूर्ण
		retval = रुको_event_पूर्णांकerruptible(dev->ग_लिखो_रुको,
						  !dev->पूर्णांकerrupt_out_busy);
		अगर (retval)
			जाओ unlock_निकास;
	पूर्ण

	/* ग_लिखो the data पूर्णांकo पूर्णांकerrupt_out_buffer from userspace */
	bytes_to_ग_लिखो = min_t(पूर्णांक, count, ग_लिखो_buffer_size);
	dev_dbg(&dev->udev->dev, "%s: count = %zd, bytes_to_write = %zd\n",
		__func__, count, bytes_to_ग_लिखो);

	अगर (copy_from_user(dev->पूर्णांकerrupt_out_buffer, buffer, bytes_to_ग_लिखो)) अणु
		retval = -EFAULT;
		जाओ unlock_निकास;
	पूर्ण

	/* send off the urb */
	usb_fill_पूर्णांक_urb(dev->पूर्णांकerrupt_out_urb,
			 dev->udev,
			 usb_sndपूर्णांकpipe(dev->udev, dev->पूर्णांकerrupt_out_endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 dev->पूर्णांकerrupt_out_buffer,
			 bytes_to_ग_लिखो,
			 tower_पूर्णांकerrupt_out_callback,
			 dev,
			 dev->पूर्णांकerrupt_out_पूर्णांकerval);

	dev->पूर्णांकerrupt_out_busy = 1;
	wmb();

	retval = usb_submit_urb(dev->पूर्णांकerrupt_out_urb, GFP_KERNEL);
	अगर (retval) अणु
		dev->पूर्णांकerrupt_out_busy = 0;
		dev_err(&dev->udev->dev,
			"Couldn't submit interrupt_out_urb %d\n", retval);
		जाओ unlock_निकास;
	पूर्ण
	retval = bytes_to_ग_लिखो;

unlock_निकास:
	/* unlock the device */
	mutex_unlock(&dev->lock);

निकास:
	वापस retval;
पूर्ण


/*
 *	tower_पूर्णांकerrupt_in_callback
 */
अटल व्योम tower_पूर्णांकerrupt_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा lego_usb_tower *dev = urb->context;
	पूर्णांक status = urb->status;
	पूर्णांक retval;
	अचिन्हित दीर्घ flags;

	lego_usb_tower_debug_data(&dev->udev->dev, __func__,
				  urb->actual_length, urb->transfer_buffer);

	अगर (status) अणु
		अगर (status == -ENOENT ||
		    status == -ECONNRESET ||
		    status == -ESHUTDOWN) अणु
			जाओ निकास;
		पूर्ण अन्यथा अणु
			dev_dbg(&dev->udev->dev,
				"%s: nonzero status received: %d\n", __func__,
				status);
			जाओ resubmit; /* maybe we can recover */
		पूर्ण
	पूर्ण

	अगर (urb->actual_length > 0) अणु
		spin_lock_irqsave(&dev->पढ़ो_buffer_lock, flags);
		अगर (dev->पढ़ो_buffer_length + urb->actual_length < पढ़ो_buffer_size) अणु
			स_नकल(dev->पढ़ो_buffer + dev->पढ़ो_buffer_length,
			       dev->पूर्णांकerrupt_in_buffer,
			       urb->actual_length);
			dev->पढ़ो_buffer_length += urb->actual_length;
			dev->पढ़ो_last_arrival = jअगरfies;
			dev_dbg(&dev->udev->dev, "%s: received %d bytes\n",
				__func__, urb->actual_length);
		पूर्ण अन्यथा अणु
			pr_warn("read_buffer overflow, %d bytes dropped\n",
				urb->actual_length);
		पूर्ण
		spin_unlock_irqrestore(&dev->पढ़ो_buffer_lock, flags);
	पूर्ण

resubmit:
	retval = usb_submit_urb(dev->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
	अगर (retval) अणु
		dev_err(&dev->udev->dev, "%s: usb_submit_urb failed (%d)\n",
			__func__, retval);
	पूर्ण
निकास:
	dev->पूर्णांकerrupt_in_करोne = 1;
	wake_up_पूर्णांकerruptible(&dev->पढ़ो_रुको);
पूर्ण


/*
 *	tower_पूर्णांकerrupt_out_callback
 */
अटल व्योम tower_पूर्णांकerrupt_out_callback(काष्ठा urb *urb)
अणु
	काष्ठा lego_usb_tower *dev = urb->context;
	पूर्णांक status = urb->status;

	lego_usb_tower_debug_data(&dev->udev->dev, __func__,
				  urb->actual_length, urb->transfer_buffer);

	/* sync/async unlink faults aren't errors */
	अगर (status && !(status == -ENOENT ||
			status == -ECONNRESET ||
			status == -ESHUTDOWN)) अणु
		dev_dbg(&dev->udev->dev,
			"%s: nonzero write bulk status received: %d\n", __func__,
			status);
	पूर्ण

	dev->पूर्णांकerrupt_out_busy = 0;
	wake_up_पूर्णांकerruptible(&dev->ग_लिखो_रुको);
पूर्ण


/*
 *	tower_probe
 *
 *	Called by the usb core when a new device is connected that it thinks
 *	this driver might be पूर्णांकerested in.
 */
अटल पूर्णांक tower_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा device *idev = &पूर्णांकerface->dev;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा lego_usb_tower *dev;
	काष्ठा tower_get_version_reply get_version_reply;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक result;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		जाओ निकास;

	mutex_init(&dev->lock);
	dev->udev = usb_get_dev(udev);
	spin_lock_init(&dev->पढ़ो_buffer_lock);
	dev->packet_समयout_jअगरfies = msecs_to_jअगरfies(packet_समयout);
	dev->पढ़ो_last_arrival = jअगरfies;
	init_रुकोqueue_head(&dev->पढ़ो_रुको);
	init_रुकोqueue_head(&dev->ग_लिखो_रुको);

	result = usb_find_common_endpoपूर्णांकs_reverse(पूर्णांकerface->cur_altsetting,
			शून्य, शून्य,
			&dev->पूर्णांकerrupt_in_endpoपूर्णांक,
			&dev->पूर्णांकerrupt_out_endpoपूर्णांक);
	अगर (result) अणु
		dev_err(idev, "interrupt endpoints not found\n");
		retval = result;
		जाओ error;
	पूर्ण

	dev->पढ़ो_buffer = kदो_स्मृति(पढ़ो_buffer_size, GFP_KERNEL);
	अगर (!dev->पढ़ो_buffer)
		जाओ error;
	dev->पूर्णांकerrupt_in_buffer = kदो_स्मृति(usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_in_endpoपूर्णांक), GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_in_buffer)
		जाओ error;
	dev->पूर्णांकerrupt_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_in_urb)
		जाओ error;
	dev->पूर्णांकerrupt_out_buffer = kदो_स्मृति(ग_लिखो_buffer_size, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_out_buffer)
		जाओ error;
	dev->पूर्णांकerrupt_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_out_urb)
		जाओ error;
	dev->पूर्णांकerrupt_in_पूर्णांकerval = पूर्णांकerrupt_in_पूर्णांकerval ? पूर्णांकerrupt_in_पूर्णांकerval : dev->पूर्णांकerrupt_in_endpoपूर्णांक->bInterval;
	dev->पूर्णांकerrupt_out_पूर्णांकerval = पूर्णांकerrupt_out_पूर्णांकerval ? पूर्णांकerrupt_out_पूर्णांकerval : dev->पूर्णांकerrupt_out_endpoपूर्णांक->bInterval;

	/* get the firmware version and log it */
	result = usb_control_msg_recv(udev, 0,
				      LEGO_USB_TOWER_REQUEST_GET_VERSION,
				      USB_TYPE_VENDOR | USB_सूची_IN | USB_RECIP_DEVICE,
				      0,
				      0,
				      &get_version_reply,
				      माप(get_version_reply),
				      1000, GFP_KERNEL);
	अगर (result) अणु
		dev_err(idev, "get version request failed: %d\n", result);
		retval = result;
		जाओ error;
	पूर्ण
	dev_info(&पूर्णांकerface->dev,
		 "LEGO USB Tower firmware version is %d.%d build %d\n",
		 get_version_reply.major,
		 get_version_reply.minor,
		 le16_to_cpu(get_version_reply.build_no));

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	retval = usb_रेजिस्टर_dev(पूर्णांकerface, &tower_class);
	अगर (retval) अणु
		/* something prevented us from रेजिस्टरing this driver */
		dev_err(idev, "Not able to get a minor for this device.\n");
		जाओ error;
	पूर्ण
	dev->minor = पूर्णांकerface->minor;

	/* let the user know what node this device is now attached to */
	dev_info(&पूर्णांकerface->dev, "LEGO USB Tower #%d now attached to major "
		 "%d minor %d\n", (dev->minor - LEGO_USB_TOWER_MINOR_BASE),
		 USB_MAJOR, dev->minor);

निकास:
	वापस retval;

error:
	tower_delete(dev);
	वापस retval;
पूर्ण


/*
 *	tower_disconnect
 *
 *	Called by the usb core when the device is हटाओd from the प्रणाली.
 */
अटल व्योम tower_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा lego_usb_tower *dev;
	पूर्णांक minor;

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	minor = dev->minor;

	/* give back our minor and prevent further खोलो() */
	usb_deरेजिस्टर_dev(पूर्णांकerface, &tower_class);

	/* stop I/O */
	usb_poison_urb(dev->पूर्णांकerrupt_in_urb);
	usb_poison_urb(dev->पूर्णांकerrupt_out_urb);

	mutex_lock(&dev->lock);

	/* अगर the device is not खोलोed, then we clean up right now */
	अगर (!dev->खोलो_count) अणु
		mutex_unlock(&dev->lock);
		tower_delete(dev);
	पूर्ण अन्यथा अणु
		dev->disconnected = 1;
		/* wake up pollers */
		wake_up_पूर्णांकerruptible_all(&dev->पढ़ो_रुको);
		wake_up_पूर्णांकerruptible_all(&dev->ग_लिखो_रुको);
		mutex_unlock(&dev->lock);
	पूर्ण

	dev_info(&पूर्णांकerface->dev, "LEGO USB Tower #%d now disconnected\n",
		 (minor - LEGO_USB_TOWER_MINOR_BASE));
पूर्ण

module_usb_driver(tower_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
