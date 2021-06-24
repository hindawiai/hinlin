<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * copyright (C) 1999/2000 by Henning Zabel <henning@uni-paderborn.de>
 */


/*
 *	USB-Kernel Driver क्रम the Mustek MDC800 Digital Camera
 *	(c) 1999/2000 Henning Zabel <henning@uni-paderborn.de>
 *
 *
 * The driver brings the USB functions of the MDC800 to Linux.
 * To use the Camera you must support the USB Protocol of the camera
 * to the Kernel Node.
 * The Driver uses a misc device Node. Create it with :
 * mknod /dev/mustek c 180 32
 *
 * The driver supports only one camera.
 * 
 * Fix: mdc800 used sleep_on and slept with io_lock held.
 * Converted sleep_on to रुकोqueues with schedule_समयout and made io_lock
 * a semaphore from a spinlock.
 * by Oliver Neukum <oliver@neukum.name>
 * (02/12/2001)
 * 
 * Identअगरy version on module load.
 * (08/04/2001) gb
 *
 * version 0.7.5
 * Fixed potential SMP races with Spinlocks.
 * Thanks to Oliver Neukum <oliver@neukum.name> who 
 * noticed the race conditions.
 * (30/10/2000)
 *
 * Fixed: Setting urb->dev beक्रमe submitting urb.
 * by Greg KH <greg@kroah.com>
 * (13/10/2000)
 *
 * version 0.7.3
 * bugfix : The mdc800->state field माला_लो set to READY after the
 * the disconnect function sets it to NOT_CONNECTED. This makes the
 * driver running like the camera is connected and causes some
 * hang ups.
 *
 * version 0.7.1
 * MOD_INC and MOD_DEC are changed in usb_probe to prevent load/unload
 * problems when compiled as Module.
 * (04/04/2000)
 *
 * The mdc800 driver माला_लो asचिन्हित the USB Minor 32-47. The Registration
 * was updated to use these values.
 * (26/03/2000)
 *
 * The Init und Exit Module Function are updated.
 * (01/03/2000)
 *
 * version 0.7.0
 * Reग_लिखो of the driver : The driver now uses URB's. The old stuff
 * has been हटाओd.
 *
 * version 0.6.0
 * Reग_लिखो of this driver: The Emulation of the rs232 protocoll
 * has been हटाओd from the driver. A special executeCommand function
 * क्रम this driver is included to gphoto.
 * The driver supports two kind of communication to bulk endpoपूर्णांकs.
 * Either with the dev->bus->ops->bulk... or with callback function.
 * (09/11/1999)
 *
 * version 0.5.0:
 * first Version that माला_लो a version number. Most of the needed
 * functions work.
 * (20/10/1999)
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/poll.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>

#समावेश <linux/usb.h>
#समावेश <linux/fs.h>

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_VERSION "v0.7.5 (30/10/2000)"
#घोषणा DRIVER_AUTHOR "Henning Zabel <henning@uni-paderborn.de>"
#घोषणा DRIVER_DESC "USB Driver for Mustek MDC800 Digital Camera"

/* Venकरोr and Product Inक्रमmation */
#घोषणा MDC800_VENDOR_ID 	0x055f
#घोषणा MDC800_PRODUCT_ID	0xa800

/* Timeouts (msec) */
#घोषणा TO_DOWNLOAD_GET_READY		1500
#घोषणा TO_DOWNLOAD_GET_BUSY		1500
#घोषणा TO_WRITE_GET_READY		1000
#घोषणा TO_DEFAULT_COMMAND		5000
#घोषणा TO_READ_FROM_IRQ 		TO_DEFAULT_COMMAND
#घोषणा TO_GET_READY			TO_DEFAULT_COMMAND

/* Minor Number of the device (create with mknod /dev/mustek c 180 32) */
#घोषणा MDC800_DEVICE_MINOR_BASE 32


/**************************************************************************
	Data and काष्ठाs
***************************************************************************/


प्रकार क्रमागत अणु
	NOT_CONNECTED, READY, WORKING, DOWNLOAD
पूर्ण mdc800_state;


/* Data क्रम the driver */
काष्ठा mdc800_data
अणु
	काष्ठा usb_device *	dev;			// Device Data
	mdc800_state 		state;

	अचिन्हित पूर्णांक		endpoपूर्णांक [4];

	काष्ठा urb *		irq_urb;
	रुको_queue_head_t	irq_रुको;
	पूर्णांक			irq_woken;
	अक्षर*			irq_urb_buffer;

	पूर्णांक			camera_busy;          // is camera busy ?
	पूर्णांक 			camera_request_पढ़ोy; // Status to synchronize with irq
	अक्षर 			camera_response [8];  // last Bytes send after busy

	काष्ठा urb *   		ग_लिखो_urb;
	अक्षर*			ग_लिखो_urb_buffer;
	रुको_queue_head_t	ग_लिखो_रुको;
	पूर्णांक			written;


	काष्ठा urb *   		करोwnload_urb;
	अक्षर*			करोwnload_urb_buffer;
	रुको_queue_head_t	करोwnload_रुको;
	पूर्णांक			करोwnloaded;
	पूर्णांक			करोwnload_left;		// Bytes left to करोwnload ?


	/* Device Data */
	अक्षर			out [64];	// Answer Buffer
	पूर्णांक 			out_ptr;	// Index to the first not पढ़ोen byte
	पूर्णांक			out_count;	// Bytes in the buffer

	पूर्णांक			खोलो;		// Camera device खोलो ?
	काष्ठा mutex		io_lock;	// IO -lock

	अक्षर 			in [8];		// Command Input Buffer
	पूर्णांक  			in_count;

	पूर्णांक			pic_index;	// Cache क्रम the Imagesize (-1 क्रम nothing cached )
	पूर्णांक			pic_len;
	पूर्णांक			minor;
पूर्ण;


/* Specअगरication of the Endpoपूर्णांकs */
अटल काष्ठा usb_endpoपूर्णांक_descriptor mdc800_ed [4] =
अणु
	अणु 
		.bLength = 		0,
		.bDescriptorType =	0,
		.bEndpoपूर्णांकAddress =	0x01,
		.bmAttributes = 	0x02,
		.wMaxPacketSize =	cpu_to_le16(8),
		.bInterval = 		0,
		.bRefresh = 		0,
		.bSynchAddress = 	0,
	पूर्ण,
	अणु
		.bLength = 		0,
		.bDescriptorType = 	0,
		.bEndpoपूर्णांकAddress = 	0x82,
		.bmAttributes = 	0x03,
		.wMaxPacketSize = 	cpu_to_le16(8),
		.bInterval = 		0,
		.bRefresh = 		0,
		.bSynchAddress = 	0,
	पूर्ण,
	अणु
		.bLength = 		0,
		.bDescriptorType = 	0,
		.bEndpoपूर्णांकAddress = 	0x03,
		.bmAttributes = 	0x02,
		.wMaxPacketSize = 	cpu_to_le16(64),
		.bInterval = 		0,
		.bRefresh = 		0,
		.bSynchAddress = 	0,
	पूर्ण,
	अणु
		.bLength = 		0,
		.bDescriptorType = 	0,
		.bEndpoपूर्णांकAddress = 	0x84,
		.bmAttributes = 	0x02,
		.wMaxPacketSize = 	cpu_to_le16(64),
		.bInterval = 		0,
		.bRefresh = 		0,
		.bSynchAddress = 	0,
	पूर्ण,
पूर्ण;

/* The Variable used by the driver */
अटल काष्ठा mdc800_data* mdc800;


/***************************************************************************
	The USB Part of the driver
****************************************************************************/

अटल पूर्णांक mdc800_endpoपूर्णांक_equals (काष्ठा usb_endpoपूर्णांक_descriptor *a,काष्ठा usb_endpoपूर्णांक_descriptor *b)
अणु
	वापस (
		   ( a->bEndpoपूर्णांकAddress == b->bEndpoपूर्णांकAddress )
		&& ( a->bmAttributes     == b->bmAttributes     )
		&& ( a->wMaxPacketSize   == b->wMaxPacketSize   )
	);
पूर्ण


/*
 * Checks whether the camera responds busy
 */
अटल पूर्णांक mdc800_isBusy (अक्षर* ch)
अणु
	पूर्णांक i=0;
	जबतक (i<8)
	अणु
		अगर (ch [i] != (अक्षर)0x99)
			वापस 0;
		i++;
	पूर्ण
	वापस 1;
पूर्ण


/*
 * Checks whether the Camera is पढ़ोy
 */
अटल पूर्णांक mdc800_isReady (अक्षर *ch)
अणु
	पूर्णांक i=0;
	जबतक (i<8)
	अणु
		अगर (ch [i] != (अक्षर)0xbb)
			वापस 0;
		i++;
	पूर्ण
	वापस 1;
पूर्ण



/*
 * USB IRQ Handler क्रम InputLine
 */
अटल व्योम mdc800_usb_irq (काष्ठा urb *urb)
अणु
	पूर्णांक data_received=0, wake_up;
	अचिन्हित अक्षर* b=urb->transfer_buffer;
	काष्ठा mdc800_data* mdc800=urb->context;
	काष्ठा device *dev = &mdc800->dev->dev;
	पूर्णांक status = urb->status;

	अगर (status >= 0) अणु
		अगर (mdc800_isBusy (b))
		अणु
			अगर (!mdc800->camera_busy)
			अणु
				mdc800->camera_busy=1;
				dev_dbg(dev, "gets busy\n");
			पूर्ण
		पूर्ण
		अन्यथा
		अणु
			अगर (mdc800->camera_busy && mdc800_isReady (b))
			अणु
				mdc800->camera_busy=0;
				dev_dbg(dev, "gets ready\n");
			पूर्ण
		पूर्ण
		अगर (!(mdc800_isBusy (b) || mdc800_isReady (b)))
		अणु
			/* Store Data in camera_answer field */
			dev_dbg(dev, "%i %i %i %i %i %i %i %i \n",b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7]);

			स_नकल (mdc800->camera_response,b,8);
			data_received=1;
		पूर्ण
	पूर्ण
	wake_up= ( mdc800->camera_request_पढ़ोy > 0 )
		&&
		(
			((mdc800->camera_request_पढ़ोy == 1) && (!mdc800->camera_busy))
		||
			((mdc800->camera_request_पढ़ोy == 2) && data_received)
		||
			((mdc800->camera_request_पढ़ोy == 3) && (mdc800->camera_busy))
		||
			(status < 0)
		);

	अगर (wake_up)
	अणु
		mdc800->camera_request_पढ़ोy=0;
		mdc800->irq_woken=1;
		wake_up (&mdc800->irq_रुको);
	पूर्ण
पूर्ण


/*
 * Waits a जबतक until the irq responds that camera is पढ़ोy
 *
 *  mode : 0: Wait क्रम camera माला_लो पढ़ोy
 *         1: Wait क्रम receiving data
 *         2: Wait क्रम camera माला_लो busy
 *
 * msec: Time to रुको
 */
अटल पूर्णांक mdc800_usb_रुकोForIRQ (पूर्णांक mode, पूर्णांक msec)
अणु
	mdc800->camera_request_पढ़ोy=1+mode;

	रुको_event_समयout(mdc800->irq_रुको, mdc800->irq_woken,
			   msecs_to_jअगरfies(msec));
	mdc800->irq_woken = 0;

	अगर (mdc800->camera_request_पढ़ोy>0)
	अणु
		mdc800->camera_request_पढ़ोy=0;
		dev_err(&mdc800->dev->dev, "timeout waiting for camera.\n");
		वापस -1;
	पूर्ण
	
	अगर (mdc800->state == NOT_CONNECTED)
	अणु
		prपूर्णांकk(KERN_WARNING "mdc800: Camera gets disconnected "
		       "during waiting for irq.\n");
		mdc800->camera_request_पढ़ोy=0;
		वापस -2;
	पूर्ण
	
	वापस 0;
पूर्ण


/*
 * The ग_लिखो_urb callback function
 */
अटल व्योम mdc800_usb_ग_लिखो_notअगरy (काष्ठा urb *urb)
अणु
	काष्ठा mdc800_data* mdc800=urb->context;
	पूर्णांक status = urb->status;

	अगर (status != 0)
		dev_err(&mdc800->dev->dev,
			"writing command fails (status=%i)\n", status);
	अन्यथा
		mdc800->state=READY;
	mdc800->written = 1;
	wake_up (&mdc800->ग_लिखो_रुको);
पूर्ण


/*
 * The करोwnload_urb callback function
 */
अटल व्योम mdc800_usb_करोwnload_notअगरy (काष्ठा urb *urb)
अणु
	काष्ठा mdc800_data* mdc800=urb->context;
	पूर्णांक status = urb->status;

	अगर (status == 0) अणु
		/* Fill output buffer with these data */
		स_नकल (mdc800->out,  urb->transfer_buffer, 64);
		mdc800->out_count=64;
		mdc800->out_ptr=0;
		mdc800->करोwnload_left-=64;
		अगर (mdc800->करोwnload_left == 0)
		अणु
			mdc800->state=READY;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(&mdc800->dev->dev,
			"request bytes fails (status:%i)\n", status);
	पूर्ण
	mdc800->करोwnloaded = 1;
	wake_up (&mdc800->करोwnload_रुको);
पूर्ण


/***************************************************************************
	Probing क्रम the Camera
 ***************************************************************************/

अटल काष्ठा usb_driver mdc800_usb_driver;
अटल स्थिर काष्ठा file_operations mdc800_device_ops;
अटल काष्ठा usb_class_driver mdc800_class = अणु
	.name =		"mdc800%d",
	.fops =		&mdc800_device_ops,
	.minor_base =	MDC800_DEVICE_MINOR_BASE,
पूर्ण;


/*
 * Callback to search the Mustek MDC800 on the USB Bus
 */
अटल पूर्णांक mdc800_usb_probe (काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			       स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक i,j;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकf_desc;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev (पूर्णांकf);
	पूर्णांक irq_पूर्णांकerval=0;
	पूर्णांक retval;

	dev_dbg(&पूर्णांकf->dev, "(%s) called.\n", __func__);


	अगर (mdc800->dev != शून्य)
	अणु
		dev_warn(&पूर्णांकf->dev, "only one Mustek MDC800 is supported.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dev->descriptor.bNumConfigurations != 1)
	अणु
		dev_err(&पूर्णांकf->dev,
			"probe fails -> wrong Number of Configuration\n");
		वापस -ENODEV;
	पूर्ण
	पूर्णांकf_desc = पूर्णांकf->cur_altsetting;

	अगर (
			( पूर्णांकf_desc->desc.bInterfaceClass != 0xff )
		||	( पूर्णांकf_desc->desc.bInterfaceSubClass != 0 )
		|| ( पूर्णांकf_desc->desc.bInterfaceProtocol != 0 )
		|| ( पूर्णांकf_desc->desc.bNumEndpoपूर्णांकs != 4)
	)
	अणु
		dev_err(&पूर्णांकf->dev, "probe fails -> wrong Interface\n");
		वापस -ENODEV;
	पूर्ण

	/* Check the Endpoपूर्णांकs */
	क्रम (i=0; i<4; i++)
	अणु
		mdc800->endpoपूर्णांक[i]=-1;
		क्रम (j=0; j<4; j++)
		अणु
			अगर (mdc800_endpoपूर्णांक_equals (&पूर्णांकf_desc->endpoपूर्णांक [j].desc,&mdc800_ed [i]))
			अणु
				mdc800->endpoपूर्णांक[i]=पूर्णांकf_desc->endpoपूर्णांक [j].desc.bEndpoपूर्णांकAddress ;
				अगर (i==1)
				अणु
					irq_पूर्णांकerval=पूर्णांकf_desc->endpoपूर्णांक [j].desc.bInterval;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (mdc800->endpoपूर्णांक[i] == -1)
		अणु
			dev_err(&पूर्णांकf->dev, "probe fails -> Wrong Endpoints.\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण


	dev_info(&पूर्णांकf->dev, "Found Mustek MDC800 on USB.\n");

	mutex_lock(&mdc800->io_lock);

	retval = usb_रेजिस्टर_dev(पूर्णांकf, &mdc800_class);
	अगर (retval) अणु
		dev_err(&पूर्णांकf->dev, "Not able to get a minor for this device.\n");
		mutex_unlock(&mdc800->io_lock);
		वापस -ENODEV;
	पूर्ण

	mdc800->dev=dev;
	mdc800->खोलो=0;

	/* Setup URB Structs */
	usb_fill_पूर्णांक_urb (
		mdc800->irq_urb,
		mdc800->dev,
		usb_rcvपूर्णांकpipe (mdc800->dev,mdc800->endpoपूर्णांक [1]),
		mdc800->irq_urb_buffer,
		8,
		mdc800_usb_irq,
		mdc800,
		irq_पूर्णांकerval
	);

	usb_fill_bulk_urb (
		mdc800->ग_लिखो_urb,
		mdc800->dev,
		usb_sndbulkpipe (mdc800->dev, mdc800->endpoपूर्णांक[0]),
		mdc800->ग_लिखो_urb_buffer,
		8,
		mdc800_usb_ग_लिखो_notअगरy,
		mdc800
	);

	usb_fill_bulk_urb (
		mdc800->करोwnload_urb,
		mdc800->dev,
		usb_rcvbulkpipe (mdc800->dev, mdc800->endpoपूर्णांक [3]),
		mdc800->करोwnload_urb_buffer,
		64,
		mdc800_usb_करोwnload_notअगरy,
		mdc800
	);

	mdc800->state=READY;

	mutex_unlock(&mdc800->io_lock);
	
	usb_set_पूर्णांकfdata(पूर्णांकf, mdc800);
	वापस 0;
पूर्ण


/*
 * Disconnect USB device (maybe the MDC800)
 */
अटल व्योम mdc800_usb_disconnect (काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा mdc800_data* mdc800 = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_dbg(&पूर्णांकf->dev, "(%s) called\n", __func__);

	अगर (mdc800) अणु
		अगर (mdc800->state == NOT_CONNECTED)
			वापस;

		usb_deरेजिस्टर_dev(पूर्णांकf, &mdc800_class);

		/* must be under lock to make sure no URB
		   is submitted after usb_समाप्त_urb() */
		mutex_lock(&mdc800->io_lock);
		mdc800->state=NOT_CONNECTED;

		usb_समाप्त_urb(mdc800->irq_urb);
		usb_समाप्त_urb(mdc800->ग_लिखो_urb);
		usb_समाप्त_urb(mdc800->करोwnload_urb);
		mutex_unlock(&mdc800->io_lock);

		mdc800->dev = शून्य;
		usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	पूर्ण
	dev_info(&पूर्णांकf->dev, "Mustek MDC800 disconnected from USB.\n");
पूर्ण


/***************************************************************************
	The Misc device Part (file_operations)
****************************************************************************/

/*
 * This Function calc the Answersize क्रम a command.
 */
अटल पूर्णांक mdc800_getAnswerSize (अक्षर command)
अणु
	चयन ((अचिन्हित अक्षर) command)
	अणु
		हाल 0x2a:
		हाल 0x49:
		हाल 0x51:
		हाल 0x0d:
		हाल 0x20:
		हाल 0x07:
		हाल 0x01:
		हाल 0x25:
		हाल 0x00:
			वापस 8;

		हाल 0x05:
		हाल 0x3e:
			वापस mdc800->pic_len;

		हाल 0x09:
			वापस 4096;

		शेष:
			वापस 0;
	पूर्ण
पूर्ण


/*
 * Init the device: (1) alloc mem (2) Increase MOD Count ..
 */
अटल पूर्णांक mdc800_device_खोलो (काष्ठा inode* inode, काष्ठा file *file)
अणु
	पूर्णांक retval=0;
	पूर्णांक errn=0;

	mutex_lock(&mdc800->io_lock);
	
	अगर (mdc800->state == NOT_CONNECTED)
	अणु
		errn=-EBUSY;
		जाओ error_out;
	पूर्ण
	अगर (mdc800->खोलो)
	अणु
		errn=-EBUSY;
		जाओ error_out;
	पूर्ण

	mdc800->in_count=0;
	mdc800->out_count=0;
	mdc800->out_ptr=0;
	mdc800->pic_index=0;
	mdc800->pic_len=-1;
	mdc800->करोwnload_left=0;

	mdc800->camera_busy=0;
	mdc800->camera_request_पढ़ोy=0;

	retval=0;
	mdc800->irq_urb->dev = mdc800->dev;
	retval = usb_submit_urb (mdc800->irq_urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&mdc800->dev->dev,
			"request USB irq fails (submit_retval=%i).\n", retval);
		errn = -EIO;
		जाओ error_out;
	पूर्ण

	mdc800->खोलो=1;
	dev_dbg(&mdc800->dev->dev, "Mustek MDC800 device opened.\n");

error_out:
	mutex_unlock(&mdc800->io_lock);
	वापस errn;
पूर्ण


/*
 * Close the Camera and release Memory
 */
अटल पूर्णांक mdc800_device_release (काष्ठा inode* inode, काष्ठा file *file)
अणु
	पूर्णांक retval=0;

	mutex_lock(&mdc800->io_lock);
	अगर (mdc800->खोलो && (mdc800->state != NOT_CONNECTED))
	अणु
		usb_समाप्त_urb(mdc800->irq_urb);
		usb_समाप्त_urb(mdc800->ग_लिखो_urb);
		usb_समाप्त_urb(mdc800->करोwnload_urb);
		mdc800->खोलो=0;
	पूर्ण
	अन्यथा
	अणु
		retval=-EIO;
	पूर्ण

	mutex_unlock(&mdc800->io_lock);
	वापस retval;
पूर्ण


/*
 * The Device पढ़ो callback Function
 */
अटल sमाप_प्रकार mdc800_device_पढ़ो (काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len, loff_t *pos)
अणु
	माप_प्रकार left=len, sts=len; /* single transfer size */
	अक्षर __user *ptr = buf;
	पूर्णांक retval;

	mutex_lock(&mdc800->io_lock);
	अगर (mdc800->state == NOT_CONNECTED)
	अणु
		mutex_unlock(&mdc800->io_lock);
		वापस -EBUSY;
	पूर्ण
	अगर (mdc800->state == WORKING)
	अणु
		prपूर्णांकk(KERN_WARNING "mdc800: Illegal State \"working\""
		       "reached during read ?!\n");
		mutex_unlock(&mdc800->io_lock);
		वापस -EBUSY;
	पूर्ण
	अगर (!mdc800->खोलो)
	अणु
		mutex_unlock(&mdc800->io_lock);
		वापस -EBUSY;
	पूर्ण

	जबतक (left)
	अणु
		अगर (संकेत_pending (current)) 
		अणु
			mutex_unlock(&mdc800->io_lock);
			वापस -EINTR;
		पूर्ण

		sts=left > (mdc800->out_count-mdc800->out_ptr)?mdc800->out_count-mdc800->out_ptr:left;

		अगर (sts <= 0)
		अणु
			/* Too less Data in buffer */
			अगर (mdc800->state == DOWNLOAD)
			अणु
				mdc800->out_count=0;
				mdc800->out_ptr=0;

				/* Download -> Request new bytes */
				mdc800->करोwnload_urb->dev = mdc800->dev;
				retval = usb_submit_urb (mdc800->करोwnload_urb, GFP_KERNEL);
				अगर (retval) अणु
					dev_err(&mdc800->dev->dev,
						"Can't submit download urb "
						"(retval=%i)\n", retval);
					mutex_unlock(&mdc800->io_lock);
					वापस len-left;
				पूर्ण
				रुको_event_समयout(mdc800->करोwnload_रुको,
				     mdc800->करोwnloaded,
				     msecs_to_jअगरfies(TO_DOWNLOAD_GET_READY));
				mdc800->करोwnloaded = 0;
				अगर (mdc800->करोwnload_urb->status != 0)
				अणु
					dev_err(&mdc800->dev->dev,
						"request download-bytes fails "
						"(status=%i)\n",
						mdc800->करोwnload_urb->status);
					mutex_unlock(&mdc800->io_lock);
					वापस len-left;
				पूर्ण
			पूर्ण
			अन्यथा
			अणु
				/* No more bytes -> that's an error*/
				mutex_unlock(&mdc800->io_lock);
				वापस -EIO;
			पूर्ण
		पूर्ण
		अन्यथा
		अणु
			/* Copy Bytes */
			अगर (copy_to_user(ptr, &mdc800->out [mdc800->out_ptr],
						sts)) अणु
				mutex_unlock(&mdc800->io_lock);
				वापस -EFAULT;
			पूर्ण
			ptr+=sts;
			left-=sts;
			mdc800->out_ptr+=sts;
		पूर्ण
	पूर्ण

	mutex_unlock(&mdc800->io_lock);
	वापस len-left;
पूर्ण


/*
 * The Device ग_लिखो callback Function
 * If a 8Byte Command is received, it will be send to the camera.
 * After this the driver initiates the request क्रम the answer or
 * just रुकोs until the camera becomes पढ़ोy.
 */
अटल sमाप_प्रकार mdc800_device_ग_लिखो (काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार len, loff_t *pos)
अणु
	माप_प्रकार i=0;
	पूर्णांक retval;

	mutex_lock(&mdc800->io_lock);
	अगर (mdc800->state != READY)
	अणु
		mutex_unlock(&mdc800->io_lock);
		वापस -EBUSY;
	पूर्ण
	अगर (!mdc800->खोलो )
	अणु
		mutex_unlock(&mdc800->io_lock);
		वापस -EBUSY;
	पूर्ण

	जबतक (i<len)
	अणु
		अचिन्हित अक्षर c;
		अगर (संकेत_pending (current)) 
		अणु
			mutex_unlock(&mdc800->io_lock);
			वापस -EINTR;
		पूर्ण
		
		अगर(get_user(c, buf+i))
		अणु
			mutex_unlock(&mdc800->io_lock);
			वापस -EFAULT;
		पूर्ण

		/* check क्रम command start */
		अगर (c == 0x55)
		अणु
			mdc800->in_count=0;
			mdc800->out_count=0;
			mdc800->out_ptr=0;
			mdc800->करोwnload_left=0;
		पूर्ण

		/* save command byte */
		अगर (mdc800->in_count < 8)
		अणु
			mdc800->in[mdc800->in_count] = c;
			mdc800->in_count++;
		पूर्ण
		अन्यथा
		अणु
			mutex_unlock(&mdc800->io_lock);
			वापस -EIO;
		पूर्ण

		/* Command Buffer full ? -> send it to camera */
		अगर (mdc800->in_count == 8)
		अणु
			पूर्णांक answersize;

			अगर (mdc800_usb_रुकोForIRQ (0,TO_GET_READY))
			अणु
				dev_err(&mdc800->dev->dev,
					"Camera didn't get ready.\n");
				mutex_unlock(&mdc800->io_lock);
				वापस -EIO;
			पूर्ण

			answersize=mdc800_getAnswerSize (mdc800->in[1]);

			mdc800->state=WORKING;
			स_नकल (mdc800->ग_लिखो_urb->transfer_buffer, mdc800->in,8);
			mdc800->ग_लिखो_urb->dev = mdc800->dev;
			retval = usb_submit_urb (mdc800->ग_लिखो_urb, GFP_KERNEL);
			अगर (retval) अणु
				dev_err(&mdc800->dev->dev,
					"submitting write urb fails "
					"(retval=%i)\n", retval);
				mutex_unlock(&mdc800->io_lock);
				वापस -EIO;
			पूर्ण
			रुको_event_समयout(mdc800->ग_लिखो_रुको, mdc800->written,
					msecs_to_jअगरfies(TO_WRITE_GET_READY));
			mdc800->written = 0;
			अगर (mdc800->state == WORKING)
			अणु
				usb_समाप्त_urb(mdc800->ग_लिखो_urb);
				mutex_unlock(&mdc800->io_lock);
				वापस -EIO;
			पूर्ण

			चयन ((अचिन्हित अक्षर) mdc800->in[1])
			अणु
				हाल 0x05: /* Download Image */
				हाल 0x3e: /* Take shot in Fine Mode (WCam Mode) */
					अगर (mdc800->pic_len < 0)
					अणु
						dev_err(&mdc800->dev->dev,
							"call 0x07 before "
							"0x05,0x3e\n");
						mdc800->state=READY;
						mutex_unlock(&mdc800->io_lock);
						वापस -EIO;
					पूर्ण
					mdc800->pic_len=-1;
					fallthrough;

				हाल 0x09: /* Download Thumbnail */
					mdc800->करोwnload_left=answersize+64;
					mdc800->state=DOWNLOAD;
					mdc800_usb_रुकोForIRQ (0,TO_DOWNLOAD_GET_BUSY);
					अवरोध;


				शेष:
					अगर (answersize)
					अणु

						अगर (mdc800_usb_रुकोForIRQ (1,TO_READ_FROM_IRQ))
						अणु
							dev_err(&mdc800->dev->dev, "requesting answer from irq fails\n");
							mutex_unlock(&mdc800->io_lock);
							वापस -EIO;
						पूर्ण

						/* Write dummy data, (this is ugly but part of the USB Protocol */
						/* अगर you use endpoपूर्णांक 1 as bulk and not as irq) */
						स_नकल (mdc800->out, mdc800->camera_response,8);

						/* This is the पूर्णांकerpreted answer */
						स_नकल (&mdc800->out[8], mdc800->camera_response,8);

						mdc800->out_ptr=0;
						mdc800->out_count=16;

						/* Cache the Imagesize, अगर command was getImageSize */
						अगर (mdc800->in [1] == (अक्षर) 0x07)
						अणु
							mdc800->pic_len=(पूर्णांक) 65536*(अचिन्हित अक्षर) mdc800->camera_response[0]+256*(अचिन्हित अक्षर) mdc800->camera_response[1]+(अचिन्हित अक्षर) mdc800->camera_response[2];

							dev_dbg(&mdc800->dev->dev, "cached imagesize = %i\n", mdc800->pic_len);
						पूर्ण

					पूर्ण
					अन्यथा
					अणु
						अगर (mdc800_usb_रुकोForIRQ (0,TO_DEFAULT_COMMAND))
						अणु
							dev_err(&mdc800->dev->dev, "Command Timeout.\n");
							mutex_unlock(&mdc800->io_lock);
							वापस -EIO;
						पूर्ण
					पूर्ण
					mdc800->state=READY;
					अवरोध;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण
	mutex_unlock(&mdc800->io_lock);
	वापस i;
पूर्ण


/***************************************************************************
	Init and Cleanup this driver (Structs and types)
****************************************************************************/

/* File Operations of this drivers */
अटल स्थिर काष्ठा file_operations mdc800_device_ops =
अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		mdc800_device_पढ़ो,
	.ग_लिखो =	mdc800_device_ग_लिखो,
	.खोलो =		mdc800_device_खोलो,
	.release =	mdc800_device_release,
	.llseek =	noop_llseek,
पूर्ण;



अटल स्थिर काष्ठा usb_device_id mdc800_table[] = अणु
	अणु USB_DEVICE(MDC800_VENDOR_ID, MDC800_PRODUCT_ID) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, mdc800_table);
/*
 * USB Driver Struct क्रम this device
 */
अटल काष्ठा usb_driver mdc800_usb_driver =
अणु
	.name =		"mdc800",
	.probe =	mdc800_usb_probe,
	.disconnect =	mdc800_usb_disconnect,
	.id_table =	mdc800_table
पूर्ण;



/************************************************************************
	Init and Cleanup this driver (Main Functions)
*************************************************************************/

अटल पूर्णांक __init usb_mdc800_init (व्योम)
अणु
	पूर्णांक retval = -ENODEV;
	/* Allocate Memory */
	mdc800=kzalloc (माप (काष्ठा mdc800_data), GFP_KERNEL);
	अगर (!mdc800)
		जाओ cleanup_on_fail;

	mdc800->dev = शून्य;
	mdc800->state=NOT_CONNECTED;
	mutex_init (&mdc800->io_lock);

	init_रुकोqueue_head (&mdc800->irq_रुको);
	init_रुकोqueue_head (&mdc800->ग_लिखो_रुको);
	init_रुकोqueue_head (&mdc800->करोwnload_रुको);

	mdc800->irq_woken = 0;
	mdc800->करोwnloaded = 0;
	mdc800->written = 0;

	mdc800->irq_urb_buffer=kदो_स्मृति (8, GFP_KERNEL);
	अगर (!mdc800->irq_urb_buffer)
		जाओ cleanup_on_fail;
	mdc800->ग_लिखो_urb_buffer=kदो_स्मृति (8, GFP_KERNEL);
	अगर (!mdc800->ग_लिखो_urb_buffer)
		जाओ cleanup_on_fail;
	mdc800->करोwnload_urb_buffer=kदो_स्मृति (64, GFP_KERNEL);
	अगर (!mdc800->करोwnload_urb_buffer)
		जाओ cleanup_on_fail;

	mdc800->irq_urb=usb_alloc_urb (0, GFP_KERNEL);
	अगर (!mdc800->irq_urb)
		जाओ cleanup_on_fail;
	mdc800->करोwnload_urb=usb_alloc_urb (0, GFP_KERNEL);
	अगर (!mdc800->करोwnload_urb)
		जाओ cleanup_on_fail;
	mdc800->ग_लिखो_urb=usb_alloc_urb (0, GFP_KERNEL);
	अगर (!mdc800->ग_लिखो_urb)
		जाओ cleanup_on_fail;

	/* Register the driver */
	retval = usb_रेजिस्टर(&mdc800_usb_driver);
	अगर (retval)
		जाओ cleanup_on_fail;

	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": " DRIVER_VERSION ":"
	       DRIVER_DESC "\n");

	वापस 0;

	/* Clean driver up, when something fails */

cleanup_on_fail:

	अगर (mdc800 != शून्य)
	अणु
		prपूर्णांकk(KERN_ERR "mdc800: can't alloc memory!\n");

		kमुक्त(mdc800->करोwnload_urb_buffer);
		kमुक्त(mdc800->ग_लिखो_urb_buffer);
		kमुक्त(mdc800->irq_urb_buffer);

		usb_मुक्त_urb(mdc800->ग_लिखो_urb);
		usb_मुक्त_urb(mdc800->करोwnload_urb);
		usb_मुक्त_urb(mdc800->irq_urb);

		kमुक्त (mdc800);
	पूर्ण
	mdc800 = शून्य;
	वापस retval;
पूर्ण


अटल व्योम __निकास usb_mdc800_cleanup (व्योम)
अणु
	usb_deरेजिस्टर (&mdc800_usb_driver);

	usb_मुक्त_urb (mdc800->irq_urb);
	usb_मुक्त_urb (mdc800->करोwnload_urb);
	usb_मुक्त_urb (mdc800->ग_लिखो_urb);

	kमुक्त (mdc800->irq_urb_buffer);
	kमुक्त (mdc800->ग_लिखो_urb_buffer);
	kमुक्त (mdc800->करोwnload_urb_buffer);

	kमुक्त (mdc800);
	mdc800 = शून्य;
पूर्ण

module_init (usb_mdc800_init);
module_निकास (usb_mdc800_cleanup);

MODULE_AUTHOR( DRIVER_AUTHOR );
MODULE_DESCRIPTION( DRIVER_DESC );
MODULE_LICENSE("GPL");

