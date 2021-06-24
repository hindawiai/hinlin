<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Generic USB driver क्रम report based पूर्णांकerrupt in/out devices
 * like LD Didactic's USB devices. LD Didactic's USB devices are
 * HID devices which करो not use HID report definitons (they use
 * raw पूर्णांकerrupt in and our reports only क्रम communication).
 *
 * This driver uses a ring buffer क्रम समय critical पढ़ोing of
 * पूर्णांकerrupt in reports and provides पढ़ो and ग_लिखो methods क्रम
 * raw पूर्णांकerrupt reports (similar to the Winकरोws HID driver).
 * Devices based on the book USB COMPLETE by Jan Axelson may need
 * such a compatibility to the Winकरोws HID driver.
 *
 * Copyright (C) 2005 Michael Hund <mhund@ld-didactic.de>
 *
 * Derived from Lego USB Tower driver
 * Copyright (C) 2003 David Glance <advidgsf@sourceक्रमge.net>
 *		 2001-2004 Juergen Stuber <starblue@users.sourceक्रमge.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/input.h>
#समावेश <linux/usb.h>
#समावेश <linux/poll.h>

/* Define these values to match your devices */
#घोषणा USB_VENDOR_ID_LD		0x0f11	/* USB Venकरोr ID of LD Didactic GmbH */
#घोषणा USB_DEVICE_ID_LD_CASSY		0x1000	/* USB Product ID of CASSY-S modules with 8 bytes endpoपूर्णांक size */
#घोषणा USB_DEVICE_ID_LD_CASSY2		0x1001	/* USB Product ID of CASSY-S modules with 64 bytes endpoपूर्णांक size */
#घोषणा USB_DEVICE_ID_LD_POCKETCASSY	0x1010	/* USB Product ID of Pocket-CASSY */
#घोषणा USB_DEVICE_ID_LD_POCKETCASSY2	0x1011	/* USB Product ID of Pocket-CASSY 2 (reserved) */
#घोषणा USB_DEVICE_ID_LD_MOBILECASSY	0x1020	/* USB Product ID of Mobile-CASSY */
#घोषणा USB_DEVICE_ID_LD_MOBILECASSY2	0x1021	/* USB Product ID of Mobile-CASSY 2 (reserved) */
#घोषणा USB_DEVICE_ID_LD_MICROCASSYVOLTAGE	0x1031	/* USB Product ID of Micro-CASSY Voltage */
#घोषणा USB_DEVICE_ID_LD_MICROCASSYCURRENT	0x1032	/* USB Product ID of Micro-CASSY Current */
#घोषणा USB_DEVICE_ID_LD_MICROCASSYTIME		0x1033	/* USB Product ID of Micro-CASSY Time (reserved) */
#घोषणा USB_DEVICE_ID_LD_MICROCASSYTEMPERATURE	0x1035	/* USB Product ID of Micro-CASSY Temperature */
#घोषणा USB_DEVICE_ID_LD_MICROCASSYPH		0x1038	/* USB Product ID of Micro-CASSY pH */
#घोषणा USB_DEVICE_ID_LD_POWERANALYSERCASSY	0x1040	/* USB Product ID of Power Analyser CASSY */
#घोषणा USB_DEVICE_ID_LD_CONVERTERCONTROLLERCASSY	0x1042	/* USB Product ID of Converter Controller CASSY */
#घोषणा USB_DEVICE_ID_LD_MACHINETESTCASSY	0x1043	/* USB Product ID of Machine Test CASSY */
#घोषणा USB_DEVICE_ID_LD_JWM		0x1080	/* USB Product ID of Joule and Watपंचांगeter */
#घोषणा USB_DEVICE_ID_LD_DMMP		0x1081	/* USB Product ID of Digital Mulसमयter P (reserved) */
#घोषणा USB_DEVICE_ID_LD_UMIP		0x1090	/* USB Product ID of UMI P */
#घोषणा USB_DEVICE_ID_LD_UMIC		0x10A0	/* USB Product ID of UMI C */
#घोषणा USB_DEVICE_ID_LD_UMIB		0x10B0	/* USB Product ID of UMI B */
#घोषणा USB_DEVICE_ID_LD_XRAY		0x1100	/* USB Product ID of X-Ray Apparatus 55481 */
#घोषणा USB_DEVICE_ID_LD_XRAY2		0x1101	/* USB Product ID of X-Ray Apparatus 554800 */
#घोषणा USB_DEVICE_ID_LD_XRAYCT		0x1110	/* USB Product ID of X-Ray Apparatus CT 554821*/
#घोषणा USB_DEVICE_ID_LD_VIDEOCOM	0x1200	/* USB Product ID of VideoCom */
#घोषणा USB_DEVICE_ID_LD_MOTOR		0x1210	/* USB Product ID of Motor (reserved) */
#घोषणा USB_DEVICE_ID_LD_COM3LAB	0x2000	/* USB Product ID of COM3LAB */
#घोषणा USB_DEVICE_ID_LD_TELEPORT	0x2010	/* USB Product ID of Terminal Adapter */
#घोषणा USB_DEVICE_ID_LD_NETWORKANALYSER 0x2020	/* USB Product ID of Network Analyser */
#घोषणा USB_DEVICE_ID_LD_POWERCONTROL	0x2030	/* USB Product ID of Converter Control Unit */
#घोषणा USB_DEVICE_ID_LD_MACHINETEST	0x2040	/* USB Product ID of Machine Test System */
#घोषणा USB_DEVICE_ID_LD_MOSTANALYSER	0x2050	/* USB Product ID of MOST Protocol Analyser */
#घोषणा USB_DEVICE_ID_LD_MOSTANALYSER2	0x2051	/* USB Product ID of MOST Protocol Analyser 2 */
#घोषणा USB_DEVICE_ID_LD_ABSESP		0x2060	/* USB Product ID of ABS ESP */
#घोषणा USB_DEVICE_ID_LD_AUTODATABUS	0x2070	/* USB Product ID of Automotive Data Buses */
#घोषणा USB_DEVICE_ID_LD_MCT		0x2080	/* USB Product ID of Microcontroller technique */
#घोषणा USB_DEVICE_ID_LD_HYBRID		0x2090	/* USB Product ID of Automotive Hybrid */
#घोषणा USB_DEVICE_ID_LD_HEATCONTROL	0x20A0	/* USB Product ID of Heat control */

#अगर_घोषित CONFIG_USB_DYNAMIC_MINORS
#घोषणा USB_LD_MINOR_BASE	0
#अन्यथा
#घोषणा USB_LD_MINOR_BASE	176
#पूर्ण_अगर

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id ld_usb_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_CASSY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_CASSY2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_POCKETCASSY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_POCKETCASSY2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MOBILECASSY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MOBILECASSY2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MICROCASSYVOLTAGE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MICROCASSYCURRENT) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MICROCASSYTIME) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MICROCASSYTEMPERATURE) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MICROCASSYPH) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_POWERANALYSERCASSY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_CONVERTERCONTROLLERCASSY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MACHINETESTCASSY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_JWM) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_DMMP) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_UMIP) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_UMIC) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_UMIB) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_XRAY) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_XRAY2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_VIDEOCOM) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MOTOR) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_COM3LAB) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_TELEPORT) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_NETWORKANALYSER) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_POWERCONTROL) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MACHINETEST) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MOSTANALYSER) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MOSTANALYSER2) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_ABSESP) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_AUTODATABUS) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_MCT) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_HYBRID) पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_LD, USB_DEVICE_ID_LD_HEATCONTROL) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, ld_usb_table);
MODULE_AUTHOR("Michael Hund <mhund@ld-didactic.de>");
MODULE_DESCRIPTION("LD USB Driver");
MODULE_LICENSE("GPL");

/* All पूर्णांकerrupt in transfers are collected in a ring buffer to
 * aव्योम racing conditions and get better perक्रमmance of the driver.
 */
अटल पूर्णांक ring_buffer_size = 128;
module_param(ring_buffer_size, पूर्णांक, 0000);
MODULE_PARM_DESC(ring_buffer_size, "Read ring buffer size in reports");

/* The ग_लिखो_buffer can contain more than one पूर्णांकerrupt out transfer.
 */
अटल पूर्णांक ग_लिखो_buffer_size = 10;
module_param(ग_लिखो_buffer_size, पूर्णांक, 0000);
MODULE_PARM_DESC(ग_लिखो_buffer_size, "Write buffer size in reports");

/* As of kernel version 2.6.4 ehci-hcd uses an
 * "only one interrupt transfer per frame" लघुcut
 * to simplअगरy the scheduling of periodic transfers.
 * This conflicts with our standard 1ms पूर्णांकervals क्रम in and out URBs.
 * We use शेष पूर्णांकervals of 2ms क्रम in and 2ms क्रम out transfers,
 * which should be fast enough.
 * Increase the पूर्णांकerval to allow more devices that करो पूर्णांकerrupt transfers,
 * or set to 1 to use the standard पूर्णांकerval from the endpoपूर्णांक descriptors.
 */
अटल पूर्णांक min_पूर्णांकerrupt_in_पूर्णांकerval = 2;
module_param(min_पूर्णांकerrupt_in_पूर्णांकerval, पूर्णांक, 0000);
MODULE_PARM_DESC(min_पूर्णांकerrupt_in_पूर्णांकerval, "Minimum interrupt in interval in ms");

अटल पूर्णांक min_पूर्णांकerrupt_out_पूर्णांकerval = 2;
module_param(min_पूर्णांकerrupt_out_पूर्णांकerval, पूर्णांक, 0000);
MODULE_PARM_DESC(min_पूर्णांकerrupt_out_पूर्णांकerval, "Minimum interrupt out interval in ms");

/* Structure to hold all of our device specअगरic stuff */
काष्ठा ld_usb अणु
	काष्ठा mutex		mutex;		/* locks this काष्ठाure */
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;		/* save off the usb पूर्णांकerface poपूर्णांकer */
	अचिन्हित दीर्घ		disconnected:1;

	पूर्णांक			खोलो_count;	/* number of बार this port has been खोलोed */

	अक्षर			*ring_buffer;
	अचिन्हित पूर्णांक		ring_head;
	अचिन्हित पूर्णांक		ring_tail;

	रुको_queue_head_t	पढ़ो_रुको;
	रुको_queue_head_t	ग_लिखो_रुको;

	अक्षर			*पूर्णांकerrupt_in_buffer;
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकerrupt_in_endpoपूर्णांक;
	काष्ठा urb		*पूर्णांकerrupt_in_urb;
	पूर्णांक			पूर्णांकerrupt_in_पूर्णांकerval;
	माप_प्रकार			पूर्णांकerrupt_in_endpoपूर्णांक_size;
	पूर्णांक			पूर्णांकerrupt_in_running;
	पूर्णांक			पूर्णांकerrupt_in_करोne;
	पूर्णांक			buffer_overflow;
	spinlock_t		rbsl;

	अक्षर			*पूर्णांकerrupt_out_buffer;
	काष्ठा usb_endpoपूर्णांक_descriptor *पूर्णांकerrupt_out_endpoपूर्णांक;
	काष्ठा urb		*पूर्णांकerrupt_out_urb;
	पूर्णांक			पूर्णांकerrupt_out_पूर्णांकerval;
	माप_प्रकार			पूर्णांकerrupt_out_endpoपूर्णांक_size;
	पूर्णांक			पूर्णांकerrupt_out_busy;
पूर्ण;

अटल काष्ठा usb_driver ld_usb_driver;

/*
 *	ld_usb_पात_transfers
 *      पातs transfers and मुक्तs associated data काष्ठाures
 */
अटल व्योम ld_usb_पात_transfers(काष्ठा ld_usb *dev)
अणु
	/* shutकरोwn transfer */
	अगर (dev->पूर्णांकerrupt_in_running) अणु
		dev->पूर्णांकerrupt_in_running = 0;
		usb_समाप्त_urb(dev->पूर्णांकerrupt_in_urb);
	पूर्ण
	अगर (dev->पूर्णांकerrupt_out_busy)
		usb_समाप्त_urb(dev->पूर्णांकerrupt_out_urb);
पूर्ण

/*
 *	ld_usb_delete
 */
अटल व्योम ld_usb_delete(काष्ठा ld_usb *dev)
अणु
	/* मुक्त data काष्ठाures */
	usb_मुक्त_urb(dev->पूर्णांकerrupt_in_urb);
	usb_मुक्त_urb(dev->पूर्णांकerrupt_out_urb);
	kमुक्त(dev->ring_buffer);
	kमुक्त(dev->पूर्णांकerrupt_in_buffer);
	kमुक्त(dev->पूर्णांकerrupt_out_buffer);
	kमुक्त(dev);
पूर्ण

/*
 *	ld_usb_पूर्णांकerrupt_in_callback
 */
अटल व्योम ld_usb_पूर्णांकerrupt_in_callback(काष्ठा urb *urb)
अणु
	काष्ठा ld_usb *dev = urb->context;
	माप_प्रकार *actual_buffer;
	अचिन्हित पूर्णांक next_ring_head;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	अगर (status) अणु
		अगर (status == -ENOENT ||
		    status == -ECONNRESET ||
		    status == -ESHUTDOWN) अणु
			जाओ निकास;
		पूर्ण अन्यथा अणु
			dev_dbg(&dev->पूर्णांकf->dev,
				"%s: nonzero status received: %d\n", __func__,
				status);
			spin_lock_irqsave(&dev->rbsl, flags);
			जाओ resubmit; /* maybe we can recover */
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&dev->rbsl, flags);
	अगर (urb->actual_length > 0) अणु
		next_ring_head = (dev->ring_head+1) % ring_buffer_size;
		अगर (next_ring_head != dev->ring_tail) अणु
			actual_buffer = (माप_प्रकार *)(dev->ring_buffer + dev->ring_head * (माप(माप_प्रकार)+dev->पूर्णांकerrupt_in_endpoपूर्णांक_size));
			/* actual_buffer माला_लो urb->actual_length + पूर्णांकerrupt_in_buffer */
			*actual_buffer = urb->actual_length;
			स_नकल(actual_buffer+1, dev->पूर्णांकerrupt_in_buffer, urb->actual_length);
			dev->ring_head = next_ring_head;
			dev_dbg(&dev->पूर्णांकf->dev, "%s: received %d bytes\n",
				__func__, urb->actual_length);
		पूर्ण अन्यथा अणु
			dev_warn(&dev->पूर्णांकf->dev,
				 "Ring buffer overflow, %d bytes dropped\n",
				 urb->actual_length);
			dev->buffer_overflow = 1;
		पूर्ण
	पूर्ण

resubmit:
	/* resubmit अगर we're still running */
	अगर (dev->पूर्णांकerrupt_in_running && !dev->buffer_overflow) अणु
		retval = usb_submit_urb(dev->पूर्णांकerrupt_in_urb, GFP_ATOMIC);
		अगर (retval) अणु
			dev_err(&dev->पूर्णांकf->dev,
				"usb_submit_urb failed (%d)\n", retval);
			dev->buffer_overflow = 1;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->rbsl, flags);
निकास:
	dev->पूर्णांकerrupt_in_करोne = 1;
	wake_up_पूर्णांकerruptible(&dev->पढ़ो_रुको);
पूर्ण

/*
 *	ld_usb_पूर्णांकerrupt_out_callback
 */
अटल व्योम ld_usb_पूर्णांकerrupt_out_callback(काष्ठा urb *urb)
अणु
	काष्ठा ld_usb *dev = urb->context;
	पूर्णांक status = urb->status;

	/* sync/async unlink faults aren't errors */
	अगर (status && !(status == -ENOENT ||
			status == -ECONNRESET ||
			status == -ESHUTDOWN))
		dev_dbg(&dev->पूर्णांकf->dev,
			"%s - nonzero write interrupt status received: %d\n",
			__func__, status);

	dev->पूर्णांकerrupt_out_busy = 0;
	wake_up_पूर्णांकerruptible(&dev->ग_लिखो_रुको);
पूर्ण

/*
 *	ld_usb_खोलो
 */
अटल पूर्णांक ld_usb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ld_usb *dev;
	पूर्णांक subminor;
	पूर्णांक retval;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	stream_खोलो(inode, file);
	subminor = iminor(inode);

	पूर्णांकerface = usb_find_पूर्णांकerface(&ld_usb_driver, subminor);

	अगर (!पूर्णांकerface) अणु
		prपूर्णांकk(KERN_ERR "%s - error, can't find device for minor %d\n",
		       __func__, subminor);
		वापस -ENODEV;
	पूर्ण

	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	अगर (!dev)
		वापस -ENODEV;

	/* lock this device */
	अगर (mutex_lock_पूर्णांकerruptible(&dev->mutex))
		वापस -ERESTARTSYS;

	/* allow खोलोing only once */
	अगर (dev->खोलो_count) अणु
		retval = -EBUSY;
		जाओ unlock_निकास;
	पूर्ण
	dev->खोलो_count = 1;

	/* initialize in direction */
	dev->ring_head = 0;
	dev->ring_tail = 0;
	dev->buffer_overflow = 0;
	usb_fill_पूर्णांक_urb(dev->पूर्णांकerrupt_in_urb,
			 पूर्णांकerface_to_usbdev(पूर्णांकerface),
			 usb_rcvपूर्णांकpipe(पूर्णांकerface_to_usbdev(पूर्णांकerface),
					dev->पूर्णांकerrupt_in_endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 dev->पूर्णांकerrupt_in_buffer,
			 dev->पूर्णांकerrupt_in_endpoपूर्णांक_size,
			 ld_usb_पूर्णांकerrupt_in_callback,
			 dev,
			 dev->पूर्णांकerrupt_in_पूर्णांकerval);

	dev->पूर्णांकerrupt_in_running = 1;
	dev->पूर्णांकerrupt_in_करोne = 0;

	retval = usb_submit_urb(dev->पूर्णांकerrupt_in_urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&पूर्णांकerface->dev, "Couldn't submit interrupt_in_urb %d\n", retval);
		dev->पूर्णांकerrupt_in_running = 0;
		dev->खोलो_count = 0;
		जाओ unlock_निकास;
	पूर्ण

	/* save device in the file's निजी काष्ठाure */
	file->निजी_data = dev;

unlock_निकास:
	mutex_unlock(&dev->mutex);

	वापस retval;
पूर्ण

/*
 *	ld_usb_release
 */
अटल पूर्णांक ld_usb_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ld_usb *dev;
	पूर्णांक retval = 0;

	dev = file->निजी_data;

	अगर (dev == शून्य) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	mutex_lock(&dev->mutex);

	अगर (dev->खोलो_count != 1) अणु
		retval = -ENODEV;
		जाओ unlock_निकास;
	पूर्ण
	अगर (dev->disconnected) अणु
		/* the device was unplugged beक्रमe the file was released */
		mutex_unlock(&dev->mutex);
		/* unlock here as ld_usb_delete मुक्तs dev */
		ld_usb_delete(dev);
		जाओ निकास;
	पूर्ण

	/* रुको until ग_लिखो transfer is finished */
	अगर (dev->पूर्णांकerrupt_out_busy)
		रुको_event_पूर्णांकerruptible_समयout(dev->ग_लिखो_रुको, !dev->पूर्णांकerrupt_out_busy, 2 * HZ);
	ld_usb_पात_transfers(dev);
	dev->खोलो_count = 0;

unlock_निकास:
	mutex_unlock(&dev->mutex);

निकास:
	वापस retval;
पूर्ण

/*
 *	ld_usb_poll
 */
अटल __poll_t ld_usb_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा ld_usb *dev;
	__poll_t mask = 0;

	dev = file->निजी_data;

	अगर (dev->disconnected)
		वापस EPOLLERR | EPOLLHUP;

	poll_रुको(file, &dev->पढ़ो_रुको, रुको);
	poll_रुको(file, &dev->ग_लिखो_रुको, रुको);

	अगर (dev->ring_head != dev->ring_tail)
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (!dev->पूर्णांकerrupt_out_busy)
		mask |= EPOLLOUT | EPOLLWRNORM;

	वापस mask;
पूर्ण

/*
 *	ld_usb_पढ़ो
 */
अटल sमाप_प्रकार ld_usb_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count,
			   loff_t *ppos)
अणु
	काष्ठा ld_usb *dev;
	माप_प्रकार *actual_buffer;
	माप_प्रकार bytes_to_पढ़ो;
	पूर्णांक retval = 0;
	पूर्णांक rv;

	dev = file->निजी_data;

	/* verअगरy that we actually have some data to पढ़ो */
	अगर (count == 0)
		जाओ निकास;

	/* lock this object */
	अगर (mutex_lock_पूर्णांकerruptible(&dev->mutex)) अणु
		retval = -ERESTARTSYS;
		जाओ निकास;
	पूर्ण

	/* verअगरy that the device wasn't unplugged */
	अगर (dev->disconnected) अणु
		retval = -ENODEV;
		prपूर्णांकk(KERN_ERR "ldusb: No device or device unplugged %d\n", retval);
		जाओ unlock_निकास;
	पूर्ण

	/* रुको क्रम data */
	spin_lock_irq(&dev->rbsl);
	जबतक (dev->ring_head == dev->ring_tail) अणु
		dev->पूर्णांकerrupt_in_करोne = 0;
		spin_unlock_irq(&dev->rbsl);
		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			जाओ unlock_निकास;
		पूर्ण
		retval = रुको_event_पूर्णांकerruptible(dev->पढ़ो_रुको, dev->पूर्णांकerrupt_in_करोne);
		अगर (retval < 0)
			जाओ unlock_निकास;

		spin_lock_irq(&dev->rbsl);
	पूर्ण
	spin_unlock_irq(&dev->rbsl);

	/* actual_buffer contains actual_length + पूर्णांकerrupt_in_buffer */
	actual_buffer = (माप_प्रकार *)(dev->ring_buffer + dev->ring_tail * (माप(माप_प्रकार)+dev->पूर्णांकerrupt_in_endpoपूर्णांक_size));
	अगर (*actual_buffer > dev->पूर्णांकerrupt_in_endpoपूर्णांक_size) अणु
		retval = -EIO;
		जाओ unlock_निकास;
	पूर्ण
	bytes_to_पढ़ो = min(count, *actual_buffer);
	अगर (bytes_to_पढ़ो < *actual_buffer)
		dev_warn(&dev->पूर्णांकf->dev, "Read buffer overflow, %zu bytes dropped\n",
			 *actual_buffer-bytes_to_पढ़ो);

	/* copy one पूर्णांकerrupt_in_buffer from ring_buffer पूर्णांकo userspace */
	अगर (copy_to_user(buffer, actual_buffer+1, bytes_to_पढ़ो)) अणु
		retval = -EFAULT;
		जाओ unlock_निकास;
	पूर्ण
	retval = bytes_to_पढ़ो;

	spin_lock_irq(&dev->rbsl);
	dev->ring_tail = (dev->ring_tail + 1) % ring_buffer_size;

	अगर (dev->buffer_overflow) अणु
		dev->buffer_overflow = 0;
		spin_unlock_irq(&dev->rbsl);
		rv = usb_submit_urb(dev->पूर्णांकerrupt_in_urb, GFP_KERNEL);
		अगर (rv < 0)
			dev->buffer_overflow = 1;
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&dev->rbsl);
	पूर्ण

unlock_निकास:
	/* unlock the device */
	mutex_unlock(&dev->mutex);

निकास:
	वापस retval;
पूर्ण

/*
 *	ld_usb_ग_लिखो
 */
अटल sमाप_प्रकार ld_usb_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ld_usb *dev;
	माप_प्रकार bytes_to_ग_लिखो;
	पूर्णांक retval = 0;

	dev = file->निजी_data;

	/* verअगरy that we actually have some data to ग_लिखो */
	अगर (count == 0)
		जाओ निकास;

	/* lock this object */
	अगर (mutex_lock_पूर्णांकerruptible(&dev->mutex)) अणु
		retval = -ERESTARTSYS;
		जाओ निकास;
	पूर्ण

	/* verअगरy that the device wasn't unplugged */
	अगर (dev->disconnected) अणु
		retval = -ENODEV;
		prपूर्णांकk(KERN_ERR "ldusb: No device or device unplugged %d\n", retval);
		जाओ unlock_निकास;
	पूर्ण

	/* रुको until previous transfer is finished */
	अगर (dev->पूर्णांकerrupt_out_busy) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			जाओ unlock_निकास;
		पूर्ण
		retval = रुको_event_पूर्णांकerruptible(dev->ग_लिखो_रुको, !dev->पूर्णांकerrupt_out_busy);
		अगर (retval < 0) अणु
			जाओ unlock_निकास;
		पूर्ण
	पूर्ण

	/* ग_लिखो the data पूर्णांकo पूर्णांकerrupt_out_buffer from userspace */
	bytes_to_ग_लिखो = min(count, ग_लिखो_buffer_size*dev->पूर्णांकerrupt_out_endpoपूर्णांक_size);
	अगर (bytes_to_ग_लिखो < count)
		dev_warn(&dev->पूर्णांकf->dev, "Write buffer overflow, %zu bytes dropped\n",
			count - bytes_to_ग_लिखो);
	dev_dbg(&dev->पूर्णांकf->dev, "%s: count = %zu, bytes_to_write = %zu\n",
		__func__, count, bytes_to_ग_लिखो);

	अगर (copy_from_user(dev->पूर्णांकerrupt_out_buffer, buffer, bytes_to_ग_लिखो)) अणु
		retval = -EFAULT;
		जाओ unlock_निकास;
	पूर्ण

	अगर (dev->पूर्णांकerrupt_out_endpoपूर्णांक == शून्य) अणु
		/* try HID_REQ_SET_REPORT=9 on control_endpoपूर्णांक instead of पूर्णांकerrupt_out_endpoपूर्णांक */
		retval = usb_control_msg(पूर्णांकerface_to_usbdev(dev->पूर्णांकf),
					 usb_sndctrlpipe(पूर्णांकerface_to_usbdev(dev->पूर्णांकf), 0),
					 9,
					 USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_OUT,
					 1 << 8, 0,
					 dev->पूर्णांकerrupt_out_buffer,
					 bytes_to_ग_लिखो,
					 USB_CTRL_SET_TIMEOUT);
		अगर (retval < 0)
			dev_err(&dev->पूर्णांकf->dev,
				"Couldn't submit HID_REQ_SET_REPORT %d\n",
				retval);
		जाओ unlock_निकास;
	पूर्ण

	/* send off the urb */
	usb_fill_पूर्णांक_urb(dev->पूर्णांकerrupt_out_urb,
			 पूर्णांकerface_to_usbdev(dev->पूर्णांकf),
			 usb_sndपूर्णांकpipe(पूर्णांकerface_to_usbdev(dev->पूर्णांकf),
					dev->पूर्णांकerrupt_out_endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 dev->पूर्णांकerrupt_out_buffer,
			 bytes_to_ग_लिखो,
			 ld_usb_पूर्णांकerrupt_out_callback,
			 dev,
			 dev->पूर्णांकerrupt_out_पूर्णांकerval);

	dev->पूर्णांकerrupt_out_busy = 1;
	wmb();

	retval = usb_submit_urb(dev->पूर्णांकerrupt_out_urb, GFP_KERNEL);
	अगर (retval) अणु
		dev->पूर्णांकerrupt_out_busy = 0;
		dev_err(&dev->पूर्णांकf->dev,
			"Couldn't submit interrupt_out_urb %d\n", retval);
		जाओ unlock_निकास;
	पूर्ण
	retval = bytes_to_ग_लिखो;

unlock_निकास:
	/* unlock the device */
	mutex_unlock(&dev->mutex);

निकास:
	वापस retval;
पूर्ण

/* file operations needed when we रेजिस्टर this driver */
अटल स्थिर काष्ठा file_operations ld_usb_fops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो  =	ld_usb_पढ़ो,
	.ग_लिखो =	ld_usb_ग_लिखो,
	.खोलो =		ld_usb_खोलो,
	.release =	ld_usb_release,
	.poll =		ld_usb_poll,
	.llseek =	no_llseek,
पूर्ण;

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device रेजिस्टरed with the driver core
 */
अटल काष्ठा usb_class_driver ld_usb_class = अणु
	.name =		"ldusb%d",
	.fops =		&ld_usb_fops,
	.minor_base =	USB_LD_MINOR_BASE,
पूर्ण;

/*
 *	ld_usb_probe
 *
 *	Called by the usb core when a new device is connected that it thinks
 *	this driver might be पूर्णांकerested in.
 */
अटल पूर्णांक ld_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा ld_usb *dev = शून्य;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	अक्षर *buffer;
	पूर्णांक retval = -ENOMEM;
	पूर्णांक res;

	/* allocate memory क्रम our device state and initialize it */

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		जाओ निकास;
	mutex_init(&dev->mutex);
	spin_lock_init(&dev->rbsl);
	dev->पूर्णांकf = पूर्णांकf;
	init_रुकोqueue_head(&dev->पढ़ो_रुको);
	init_रुकोqueue_head(&dev->ग_लिखो_रुको);

	/* workaround क्रम early firmware versions on fast computers */
	अगर ((le16_to_cpu(udev->descriptor.idVenकरोr) == USB_VENDOR_ID_LD) &&
	    ((le16_to_cpu(udev->descriptor.idProduct) == USB_DEVICE_ID_LD_CASSY) ||
	     (le16_to_cpu(udev->descriptor.idProduct) == USB_DEVICE_ID_LD_COM3LAB)) &&
	    (le16_to_cpu(udev->descriptor.bcdDevice) <= 0x103)) अणु
		buffer = kदो_स्मृति(256, GFP_KERNEL);
		अगर (!buffer)
			जाओ error;
		/* usb_string makes SETUP+STALL to leave always ControlReadLoop */
		usb_string(udev, 255, buffer, 256);
		kमुक्त(buffer);
	पूर्ण

	अगरace_desc = पूर्णांकf->cur_altsetting;

	res = usb_find_last_पूर्णांक_in_endpoपूर्णांक(अगरace_desc,
			&dev->पूर्णांकerrupt_in_endpoपूर्णांक);
	अगर (res) अणु
		dev_err(&पूर्णांकf->dev, "Interrupt in endpoint not found\n");
		retval = res;
		जाओ error;
	पूर्ण

	res = usb_find_last_पूर्णांक_out_endpoपूर्णांक(अगरace_desc,
			&dev->पूर्णांकerrupt_out_endpoपूर्णांक);
	अगर (res)
		dev_warn(&पूर्णांकf->dev, "Interrupt out endpoint not found (using control endpoint instead)\n");

	dev->पूर्णांकerrupt_in_endpoपूर्णांक_size = usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_in_endpoपूर्णांक);
	dev->ring_buffer = kसुस्मृति(ring_buffer_size,
			माप(माप_प्रकार) + dev->पूर्णांकerrupt_in_endpoपूर्णांक_size,
			GFP_KERNEL);
	अगर (!dev->ring_buffer)
		जाओ error;
	dev->पूर्णांकerrupt_in_buffer = kदो_स्मृति(dev->पूर्णांकerrupt_in_endpoपूर्णांक_size, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_in_buffer)
		जाओ error;
	dev->पूर्णांकerrupt_in_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_in_urb)
		जाओ error;
	dev->पूर्णांकerrupt_out_endpoपूर्णांक_size = dev->पूर्णांकerrupt_out_endpoपूर्णांक ? usb_endpoपूर्णांक_maxp(dev->पूर्णांकerrupt_out_endpoपूर्णांक) :
									 udev->descriptor.bMaxPacketSize0;
	dev->पूर्णांकerrupt_out_buffer =
		kदो_स्मृति_array(ग_लिखो_buffer_size,
			      dev->पूर्णांकerrupt_out_endpoपूर्णांक_size, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_out_buffer)
		जाओ error;
	dev->पूर्णांकerrupt_out_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->पूर्णांकerrupt_out_urb)
		जाओ error;
	dev->पूर्णांकerrupt_in_पूर्णांकerval = min_पूर्णांकerrupt_in_पूर्णांकerval > dev->पूर्णांकerrupt_in_endpoपूर्णांक->bInterval ? min_पूर्णांकerrupt_in_पूर्णांकerval : dev->पूर्णांकerrupt_in_endpoपूर्णांक->bInterval;
	अगर (dev->पूर्णांकerrupt_out_endpoपूर्णांक)
		dev->पूर्णांकerrupt_out_पूर्णांकerval = min_पूर्णांकerrupt_out_पूर्णांकerval > dev->पूर्णांकerrupt_out_endpoपूर्णांक->bInterval ? min_पूर्णांकerrupt_out_पूर्णांकerval : dev->पूर्णांकerrupt_out_endpoपूर्णांक->bInterval;

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	retval = usb_रेजिस्टर_dev(पूर्णांकf, &ld_usb_class);
	अगर (retval) अणु
		/* something prevented us from रेजिस्टरing this driver */
		dev_err(&पूर्णांकf->dev, "Not able to get a minor for this device.\n");
		usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
		जाओ error;
	पूर्ण

	/* let the user know what node this device is now attached to */
	dev_info(&पूर्णांकf->dev, "LD USB Device #%d now attached to major %d minor %d\n",
		(पूर्णांकf->minor - USB_LD_MINOR_BASE), USB_MAJOR, पूर्णांकf->minor);

निकास:
	वापस retval;

error:
	ld_usb_delete(dev);

	वापस retval;
पूर्ण

/*
 *	ld_usb_disconnect
 *
 *	Called by the usb core when the device is हटाओd from the प्रणाली.
 */
अटल व्योम ld_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ld_usb *dev;
	पूर्णांक minor;

	dev = usb_get_पूर्णांकfdata(पूर्णांकf);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	minor = पूर्णांकf->minor;

	/* give back our minor */
	usb_deरेजिस्टर_dev(पूर्णांकf, &ld_usb_class);

	usb_poison_urb(dev->पूर्णांकerrupt_in_urb);
	usb_poison_urb(dev->पूर्णांकerrupt_out_urb);

	mutex_lock(&dev->mutex);

	/* अगर the device is not खोलोed, then we clean up right now */
	अगर (!dev->खोलो_count) अणु
		mutex_unlock(&dev->mutex);
		ld_usb_delete(dev);
	पूर्ण अन्यथा अणु
		dev->disconnected = 1;
		/* wake up pollers */
		wake_up_पूर्णांकerruptible_all(&dev->पढ़ो_रुको);
		wake_up_पूर्णांकerruptible_all(&dev->ग_लिखो_रुको);
		mutex_unlock(&dev->mutex);
	पूर्ण

	dev_info(&पूर्णांकf->dev, "LD USB Device #%d now disconnected\n",
		 (minor - USB_LD_MINOR_BASE));
पूर्ण

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver ld_usb_driver = अणु
	.name =		"ldusb",
	.probe =	ld_usb_probe,
	.disconnect =	ld_usb_disconnect,
	.id_table =	ld_usb_table,
पूर्ण;

module_usb_driver(ld_usb_driver);

