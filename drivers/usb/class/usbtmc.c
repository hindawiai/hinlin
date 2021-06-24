<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/usb/class/usbपंचांगc.c - USB Test & Measurement class driver
 *
 * Copyright (C) 2007 Stefan Kopp, Gechingen, Germany
 * Copyright (C) 2008 Novell, Inc.
 * Copyright (C) 2008 Greg Kroah-Harपंचांगan <gregkh@suse.de>
 * Copyright (C) 2018 IVI Foundation, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kref.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>
#समावेश <linux/compat.h>
#समावेश <linux/usb/पंचांगc.h>

/* Increment API VERSION when changing पंचांगc.h with new flags or ioctls
 * or when changing a signअगरicant behavior of the driver.
 */
#घोषणा USBTMC_API_VERSION (3)

#घोषणा USBTMC_HEADER_SIZE	12
#घोषणा USBTMC_MINOR_BASE	176

/* Minimum USB समयout (in milliseconds) */
#घोषणा USBTMC_MIN_TIMEOUT	100
/* Default USB समयout (in milliseconds) */
#घोषणा USBTMC_TIMEOUT		5000

/* Max number of urbs used in ग_लिखो transfers */
#घोषणा MAX_URBS_IN_FLIGHT	16
/* I/O buffer size used in generic पढ़ो/ग_लिखो functions */
#घोषणा USBTMC_बफ_मानE		(4096)

/*
 * Maximum number of पढ़ो cycles to empty bulk in endpoपूर्णांक during CLEAR and
 * ABORT_BULK_IN requests. Ends the loop अगर (क्रम whatever reason) a लघु
 * packet is never पढ़ो.
 */
#घोषणा USBTMC_MAX_READS_TO_CLEAR_BULK_IN	100

अटल स्थिर काष्ठा usb_device_id usbपंचांगc_devices[] = अणु
	अणु USB_INTERFACE_INFO(USB_CLASS_APP_SPEC, 3, 0), पूर्ण,
	अणु USB_INTERFACE_INFO(USB_CLASS_APP_SPEC, 3, 1), पूर्ण,
	अणु 0, पूर्ण /* terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, usbपंचांगc_devices);

/*
 * This काष्ठाure is the capabilities क्रम the device
 * See section 4.2.1.8 of the USBTMC specअगरication,
 * and section 4.2.2 of the USBTMC usb488 subclass
 * specअगरication क्रम details.
 */
काष्ठा usbपंचांगc_dev_capabilities अणु
	__u8 पूर्णांकerface_capabilities;
	__u8 device_capabilities;
	__u8 usb488_पूर्णांकerface_capabilities;
	__u8 usb488_device_capabilities;
पूर्ण;

/* This काष्ठाure holds निजी data क्रम each USBTMC device. One copy is
 * allocated क्रम each USBTMC device in the driver's probe function.
 */
काष्ठा usbपंचांगc_device_data अणु
	स्थिर काष्ठा usb_device_id *id;
	काष्ठा usb_device *usb_dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा list_head file_list;

	अचिन्हित पूर्णांक bulk_in;
	अचिन्हित पूर्णांक bulk_out;

	u8 bTag;
	u8 bTag_last_ग_लिखो;	/* needed क्रम पात */
	u8 bTag_last_पढ़ो;	/* needed क्रम पात */

	/* packet size of IN bulk */
	u16            wMaxPacketSize;

	/* data क्रम पूर्णांकerrupt in endpoपूर्णांक handling */
	u8             bNotअगरy1;
	u8             bNotअगरy2;
	u16            अगरnum;
	u8             iin_bTag;
	u8            *iin_buffer;
	atomic_t       iin_data_valid;
	अचिन्हित पूर्णांक   iin_ep;
	पूर्णांक            iin_ep_present;
	पूर्णांक            iin_पूर्णांकerval;
	काष्ठा urb    *iin_urb;
	u16            iin_wMaxPacketSize;

	/* coalesced usb488_caps from usbपंचांगc_dev_capabilities */
	__u8 usb488_caps;

	bool zombie; /* fd of disconnected device */

	काष्ठा usbपंचांगc_dev_capabilities	capabilities;
	काष्ठा kref kref;
	काष्ठा mutex io_mutex;	/* only one i/o function running at a समय */
	रुको_queue_head_t रुकोq;
	काष्ठा fasync_काष्ठा *fasync;
	spinlock_t dev_lock; /* lock क्रम file_list */
पूर्ण;
#घोषणा to_usbपंचांगc_data(d) container_of(d, काष्ठा usbपंचांगc_device_data, kref)

/*
 * This काष्ठाure holds निजी data क्रम each USBTMC file handle.
 */
काष्ठा usbपंचांगc_file_data अणु
	काष्ठा usbपंचांगc_device_data *data;
	काष्ठा list_head file_elem;

	u32            समयout;
	u8             srq_byte;
	atomic_t       srq_निश्चितed;
	atomic_t       closing;
	u8             bmTransferAttributes; /* member of DEV_DEP_MSG_IN */

	u8             eom_val;
	u8             term_अक्षर;
	bool           term_अक्षर_enabled;
	bool           स्वतः_पात;

	spinlock_t     err_lock; /* lock क्रम errors */

	काष्ठा usb_anchor submitted;

	/* data क्रम generic_ग_लिखो */
	काष्ठा semaphore limit_ग_लिखो_sem;
	u32 out_transfer_size;
	पूर्णांक out_status;

	/* data क्रम generic_पढ़ो */
	u32 in_transfer_size;
	पूर्णांक in_status;
	पूर्णांक in_urbs_used;
	काष्ठा usb_anchor in_anchor;
	रुको_queue_head_t रुको_bulk_in;
पूर्ण;

/* Forward declarations */
अटल काष्ठा usb_driver usbपंचांगc_driver;
अटल व्योम usbपंचांगc_draw_करोwn(काष्ठा usbपंचांगc_file_data *file_data);

अटल व्योम usbपंचांगc_delete(काष्ठा kref *kref)
अणु
	काष्ठा usbपंचांगc_device_data *data = to_usbपंचांगc_data(kref);

	usb_put_dev(data->usb_dev);
	kमुक्त(data);
पूर्ण

अटल पूर्णांक usbपंचांगc_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा usbपंचांगc_device_data *data;
	काष्ठा usbपंचांगc_file_data *file_data;

	पूर्णांकf = usb_find_पूर्णांकerface(&usbपंचांगc_driver, iminor(inode));
	अगर (!पूर्णांकf) अणु
		pr_err("can not find device for minor %d", iminor(inode));
		वापस -ENODEV;
	पूर्ण

	file_data = kzalloc(माप(*file_data), GFP_KERNEL);
	अगर (!file_data)
		वापस -ENOMEM;

	spin_lock_init(&file_data->err_lock);
	sema_init(&file_data->limit_ग_लिखो_sem, MAX_URBS_IN_FLIGHT);
	init_usb_anchor(&file_data->submitted);
	init_usb_anchor(&file_data->in_anchor);
	init_रुकोqueue_head(&file_data->रुको_bulk_in);

	data = usb_get_पूर्णांकfdata(पूर्णांकf);
	/* Protect reference to data from file काष्ठाure until release */
	kref_get(&data->kref);

	mutex_lock(&data->io_mutex);
	file_data->data = data;

	atomic_set(&file_data->closing, 0);

	file_data->समयout = USBTMC_TIMEOUT;
	file_data->term_अक्षर = '\n';
	file_data->term_अक्षर_enabled = 0;
	file_data->स्वतः_पात = 0;
	file_data->eom_val = 1;

	INIT_LIST_HEAD(&file_data->file_elem);
	spin_lock_irq(&data->dev_lock);
	list_add_tail(&file_data->file_elem, &data->file_list);
	spin_unlock_irq(&data->dev_lock);
	mutex_unlock(&data->io_mutex);

	/* Store poपूर्णांकer in file काष्ठाure's निजी data field */
	filp->निजी_data = file_data;

	वापस 0;
पूर्ण

/*
 * usbपंचांगc_flush - called beक्रमe file handle is बंदd
 */
अटल पूर्णांक usbपंचांगc_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा usbपंचांगc_file_data *file_data;
	काष्ठा usbपंचांगc_device_data *data;

	file_data = file->निजी_data;
	अगर (file_data == शून्य)
		वापस -ENODEV;

	atomic_set(&file_data->closing, 1);
	data = file_data->data;

	/* रुको क्रम io to stop */
	mutex_lock(&data->io_mutex);

	usbपंचांगc_draw_करोwn(file_data);

	spin_lock_irq(&file_data->err_lock);
	file_data->in_status = 0;
	file_data->in_transfer_size = 0;
	file_data->in_urbs_used = 0;
	file_data->out_status = 0;
	file_data->out_transfer_size = 0;
	spin_unlock_irq(&file_data->err_lock);

	wake_up_पूर्णांकerruptible_all(&data->रुकोq);
	mutex_unlock(&data->io_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक usbपंचांगc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usbपंचांगc_file_data *file_data = file->निजी_data;

	/* prevent IO _AND_ usbपंचांगc_पूर्णांकerrupt */
	mutex_lock(&file_data->data->io_mutex);
	spin_lock_irq(&file_data->data->dev_lock);

	list_del(&file_data->file_elem);

	spin_unlock_irq(&file_data->data->dev_lock);
	mutex_unlock(&file_data->data->io_mutex);

	kref_put(&file_data->data->kref, usbपंचांगc_delete);
	file_data->data = शून्य;
	kमुक्त(file_data);
	वापस 0;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_पात_bulk_in_tag(काष्ठा usbपंचांगc_device_data *data,
					  u8 tag)
अणु
	u8 *buffer;
	काष्ठा device *dev;
	पूर्णांक rv;
	पूर्णांक n;
	पूर्णांक actual;

	dev = &data->पूर्णांकf->dev;
	buffer = kदो_स्मृति(USBTMC_बफ_मानE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_INITIATE_ABORT_BULK_IN,
			     USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			     tag, data->bulk_in,
			     buffer, 2, USB_CTRL_GET_TIMEOUT);

	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण

	dev_dbg(dev, "INITIATE_ABORT_BULK_IN returned %x with tag %02x\n",
		buffer[0], buffer[1]);

	अगर (buffer[0] == USBTMC_STATUS_FAILED) अणु
		/* No transfer in progress and the Bulk-OUT FIFO is empty. */
		rv = 0;
		जाओ निकास;
	पूर्ण

	अगर (buffer[0] == USBTMC_STATUS_TRANSFER_NOT_IN_PROGRESS) अणु
		/* The device वापसs this status अगर either:
		 * - There is a transfer in progress, but the specअगरied bTag
		 *   करोes not match.
		 * - There is no transfer in progress, but the Bulk-OUT FIFO
		 *   is not empty.
		 */
		rv = -ENOMSG;
		जाओ निकास;
	पूर्ण

	अगर (buffer[0] != USBTMC_STATUS_SUCCESS) अणु
		dev_err(dev, "INITIATE_ABORT_BULK_IN returned %x\n",
			buffer[0]);
		rv = -EPERM;
		जाओ निकास;
	पूर्ण

	n = 0;

usbपंचांगc_पात_bulk_in_status:
	dev_dbg(dev, "Reading from bulk in EP\n");

	/* Data must be present. So use low समयout 300 ms */
	actual = 0;
	rv = usb_bulk_msg(data->usb_dev,
			  usb_rcvbulkpipe(data->usb_dev,
					  data->bulk_in),
			  buffer, USBTMC_बफ_मानE,
			  &actual, 300);

	prपूर्णांक_hex_dump_debug("usbtmc ", DUMP_PREFIX_NONE, 16, 1,
			     buffer, actual, true);

	n++;

	अगर (rv < 0) अणु
		dev_err(dev, "usb_bulk_msg returned %d\n", rv);
		अगर (rv != -ETIMEDOUT)
			जाओ निकास;
	पूर्ण

	अगर (actual == USBTMC_बफ_मानE)
		जाओ usbपंचांगc_पात_bulk_in_status;

	अगर (n >= USBTMC_MAX_READS_TO_CLEAR_BULK_IN) अणु
		dev_err(dev, "Couldn't clear device buffer within %d cycles\n",
			USBTMC_MAX_READS_TO_CLEAR_BULK_IN);
		rv = -EPERM;
		जाओ निकास;
	पूर्ण

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_CHECK_ABORT_BULK_IN_STATUS,
			     USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			     0, data->bulk_in, buffer, 0x08,
			     USB_CTRL_GET_TIMEOUT);

	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण

	dev_dbg(dev, "CHECK_ABORT_BULK_IN returned %x\n", buffer[0]);

	अगर (buffer[0] == USBTMC_STATUS_SUCCESS) अणु
		rv = 0;
		जाओ निकास;
	पूर्ण

	अगर (buffer[0] != USBTMC_STATUS_PENDING) अणु
		dev_err(dev, "CHECK_ABORT_BULK_IN returned %x\n", buffer[0]);
		rv = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर ((buffer[1] & 1) > 0) अणु
		/* The device has 1 or more queued packets the Host can पढ़ो */
		जाओ usbपंचांगc_पात_bulk_in_status;
	पूर्ण

	/* The Host must send CHECK_ABORT_BULK_IN_STATUS at a later समय. */
	rv = -EAGAIN;
निकास:
	kमुक्त(buffer);
	वापस rv;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_पात_bulk_in(काष्ठा usbपंचांगc_device_data *data)
अणु
	वापस usbपंचांगc_ioctl_पात_bulk_in_tag(data, data->bTag_last_पढ़ो);
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_पात_bulk_out_tag(काष्ठा usbपंचांगc_device_data *data,
					   u8 tag)
अणु
	काष्ठा device *dev;
	u8 *buffer;
	पूर्णांक rv;
	पूर्णांक n;

	dev = &data->पूर्णांकf->dev;

	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_INITIATE_ABORT_BULK_OUT,
			     USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			     tag, data->bulk_out,
			     buffer, 2, USB_CTRL_GET_TIMEOUT);

	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण

	dev_dbg(dev, "INITIATE_ABORT_BULK_OUT returned %x\n", buffer[0]);

	अगर (buffer[0] != USBTMC_STATUS_SUCCESS) अणु
		dev_err(dev, "INITIATE_ABORT_BULK_OUT returned %x\n",
			buffer[0]);
		rv = -EPERM;
		जाओ निकास;
	पूर्ण

	n = 0;

usbपंचांगc_पात_bulk_out_check_status:
	/* करो not stress device with subsequent requests */
	msleep(50);
	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_CHECK_ABORT_BULK_OUT_STATUS,
			     USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_ENDPOINT,
			     0, data->bulk_out, buffer, 0x08,
			     USB_CTRL_GET_TIMEOUT);
	n++;
	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण

	dev_dbg(dev, "CHECK_ABORT_BULK_OUT returned %x\n", buffer[0]);

	अगर (buffer[0] == USBTMC_STATUS_SUCCESS)
		जाओ usbपंचांगc_पात_bulk_out_clear_halt;

	अगर ((buffer[0] == USBTMC_STATUS_PENDING) &&
	    (n < USBTMC_MAX_READS_TO_CLEAR_BULK_IN))
		जाओ usbपंचांगc_पात_bulk_out_check_status;

	rv = -EPERM;
	जाओ निकास;

usbपंचांगc_पात_bulk_out_clear_halt:
	rv = usb_clear_halt(data->usb_dev,
			    usb_sndbulkpipe(data->usb_dev, data->bulk_out));

	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण
	rv = 0;

निकास:
	kमुक्त(buffer);
	वापस rv;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_पात_bulk_out(काष्ठा usbपंचांगc_device_data *data)
अणु
	वापस usbपंचांगc_ioctl_पात_bulk_out_tag(data, data->bTag_last_ग_लिखो);
पूर्ण

अटल पूर्णांक usbपंचांगc_get_stb(काष्ठा usbपंचांगc_file_data *file_data, __u8 *stb)
अणु
	काष्ठा usbपंचांगc_device_data *data = file_data->data;
	काष्ठा device *dev = &data->पूर्णांकf->dev;
	u8 *buffer;
	u8 tag;
	पूर्णांक rv;

	dev_dbg(dev, "Enter ioctl_read_stb iin_ep_present: %d\n",
		data->iin_ep_present);

	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	atomic_set(&data->iin_data_valid, 0);

	rv = usb_control_msg(data->usb_dev,
			usb_rcvctrlpipe(data->usb_dev, 0),
			USBTMC488_REQUEST_READ_STATUS_BYTE,
			USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			data->iin_bTag,
			data->अगरnum,
			buffer, 0x03, USB_CTRL_GET_TIMEOUT);
	अगर (rv < 0) अणु
		dev_err(dev, "stb usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण

	अगर (buffer[0] != USBTMC_STATUS_SUCCESS) अणु
		dev_err(dev, "control status returned %x\n", buffer[0]);
		rv = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (data->iin_ep_present) अणु
		rv = रुको_event_पूर्णांकerruptible_समयout(
			data->रुकोq,
			atomic_पढ़ो(&data->iin_data_valid) != 0,
			file_data->समयout);
		अगर (rv < 0) अणु
			dev_dbg(dev, "wait interrupted %d\n", rv);
			जाओ निकास;
		पूर्ण

		अगर (rv == 0) अणु
			dev_dbg(dev, "wait timed out\n");
			rv = -ETIMEDOUT;
			जाओ निकास;
		पूर्ण

		tag = data->bNotअगरy1 & 0x7f;
		अगर (tag != data->iin_bTag) अणु
			dev_err(dev, "expected bTag %x got %x\n",
				data->iin_bTag, tag);
		पूर्ण

		*stb = data->bNotअगरy2;
	पूर्ण अन्यथा अणु
		*stb = buffer[2];
	पूर्ण

	dev_dbg(dev, "stb:0x%02x received %d\n", (अचिन्हित पूर्णांक)*stb, rv);

 निकास:
	/* bump पूर्णांकerrupt bTag */
	data->iin_bTag += 1;
	अगर (data->iin_bTag > 127)
		/* 1 is क्रम SRQ see USBTMC-USB488 subclass spec section 4.3.1 */
		data->iin_bTag = 2;

	kमुक्त(buffer);
	वापस rv;
पूर्ण

अटल पूर्णांक usbपंचांगc488_ioctl_पढ़ो_stb(काष्ठा usbपंचांगc_file_data *file_data,
				व्योम __user *arg)
अणु
	पूर्णांक srq_निश्चितed = 0;
	__u8 stb;
	पूर्णांक rv;

	rv = usbपंचांगc_get_stb(file_data, &stb);

	अगर (rv > 0) अणु
		srq_निश्चितed = atomic_xchg(&file_data->srq_निश्चितed,
					srq_निश्चितed);
		अगर (srq_निश्चितed)
			stb |= 0x40; /* Set RQS bit */

		rv = put_user(stb, (__u8 __user *)arg);
	पूर्ण
	वापस rv;

पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_get_srq_stb(काष्ठा usbपंचांगc_file_data *file_data,
				व्योम __user *arg)
अणु
	काष्ठा usbपंचांगc_device_data *data = file_data->data;
	काष्ठा device *dev = &data->पूर्णांकf->dev;
	पूर्णांक srq_निश्चितed = 0;
	__u8 stb = 0;
	पूर्णांक rv;

	spin_lock_irq(&data->dev_lock);
	srq_निश्चितed  = atomic_xchg(&file_data->srq_निश्चितed, srq_निश्चितed);

	अगर (srq_निश्चितed) अणु
		stb = file_data->srq_byte;
		spin_unlock_irq(&data->dev_lock);
		rv = put_user(stb, (__u8 __user *)arg);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&data->dev_lock);
		rv = -ENOMSG;
	पूर्ण

	dev_dbg(dev, "stb:0x%02x with srq received %d\n", (अचिन्हित पूर्णांक)stb, rv);

	वापस rv;
पूर्ण

अटल पूर्णांक usbपंचांगc488_ioctl_रुको_srq(काष्ठा usbपंचांगc_file_data *file_data,
				    __u32 __user *arg)
अणु
	काष्ठा usbपंचांगc_device_data *data = file_data->data;
	काष्ठा device *dev = &data->पूर्णांकf->dev;
	पूर्णांक rv;
	u32 समयout;
	अचिन्हित दीर्घ expire;

	अगर (!data->iin_ep_present) अणु
		dev_dbg(dev, "no interrupt endpoint present\n");
		वापस -EFAULT;
	पूर्ण

	अगर (get_user(समयout, arg))
		वापस -EFAULT;

	expire = msecs_to_jअगरfies(समयout);

	mutex_unlock(&data->io_mutex);

	rv = रुको_event_पूर्णांकerruptible_समयout(
			data->रुकोq,
			atomic_पढ़ो(&file_data->srq_निश्चितed) != 0 ||
			atomic_पढ़ो(&file_data->closing),
			expire);

	mutex_lock(&data->io_mutex);

	/* Note! disconnect or बंद could be called in the meanसमय */
	अगर (atomic_पढ़ो(&file_data->closing) || data->zombie)
		rv = -ENODEV;

	अगर (rv < 0) अणु
		/* dev can be invalid now! */
		pr_debug("%s - wait interrupted %d\n", __func__, rv);
		वापस rv;
	पूर्ण

	अगर (rv == 0) अणु
		dev_dbg(dev, "%s - wait timed out\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(dev, "%s - srq asserted\n", __func__);
	वापस 0;
पूर्ण

अटल पूर्णांक usbपंचांगc488_ioctl_simple(काष्ठा usbपंचांगc_device_data *data,
				व्योम __user *arg, अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा device *dev = &data->पूर्णांकf->dev;
	__u8 val;
	u8 *buffer;
	u16 wValue;
	पूर्णांक rv;

	अगर (!(data->usb488_caps & USBTMC488_CAPABILITY_SIMPLE))
		वापस -EINVAL;

	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	अगर (cmd == USBTMC488_REQUEST_REN_CONTROL) अणु
		rv = copy_from_user(&val, arg, माप(val));
		अगर (rv) अणु
			rv = -EFAULT;
			जाओ निकास;
		पूर्ण
		wValue = val ? 1 : 0;
	पूर्ण अन्यथा अणु
		wValue = 0;
	पूर्ण

	rv = usb_control_msg(data->usb_dev,
			usb_rcvctrlpipe(data->usb_dev, 0),
			cmd,
			USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			wValue,
			data->अगरnum,
			buffer, 0x01, USB_CTRL_GET_TIMEOUT);
	अगर (rv < 0) अणु
		dev_err(dev, "simple usb_control_msg failed %d\n", rv);
		जाओ निकास;
	पूर्ण अन्यथा अगर (rv != 1) अणु
		dev_warn(dev, "simple usb_control_msg returned %d\n", rv);
		rv = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (buffer[0] != USBTMC_STATUS_SUCCESS) अणु
		dev_err(dev, "simple control status returned %x\n", buffer[0]);
		rv = -EIO;
		जाओ निकास;
	पूर्ण
	rv = 0;

 निकास:
	kमुक्त(buffer);
	वापस rv;
पूर्ण

/*
 * Sends a TRIGGER Bulk-OUT command message
 * See the USBTMC-USB488 specअगरication, Table 2.
 *
 * Also updates bTag_last_ग_लिखो.
 */
अटल पूर्णांक usbपंचांगc488_ioctl_trigger(काष्ठा usbपंचांगc_file_data *file_data)
अणु
	काष्ठा usbपंचांगc_device_data *data = file_data->data;
	पूर्णांक retval;
	u8 *buffer;
	पूर्णांक actual;

	buffer = kzalloc(USBTMC_HEADER_SIZE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer[0] = 128;
	buffer[1] = data->bTag;
	buffer[2] = ~data->bTag;

	retval = usb_bulk_msg(data->usb_dev,
			      usb_sndbulkpipe(data->usb_dev,
					      data->bulk_out),
			      buffer, USBTMC_HEADER_SIZE,
			      &actual, file_data->समयout);

	/* Store bTag (in हाल we need to पात) */
	data->bTag_last_ग_लिखो = data->bTag;

	/* Increment bTag -- and increment again अगर zero */
	data->bTag++;
	अगर (!data->bTag)
		data->bTag++;

	kमुक्त(buffer);
	अगर (retval < 0) अणु
		dev_err(&data->पूर्णांकf->dev, "%s returned %d\n",
			__func__, retval);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा urb *usbपंचांगc_create_urb(व्योम)
अणु
	स्थिर माप_प्रकार bufsize = USBTMC_बफ_मानE;
	u8 *dmabuf = शून्य;
	काष्ठा urb *urb = usb_alloc_urb(0, GFP_KERNEL);

	अगर (!urb)
		वापस शून्य;

	dmabuf = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!dmabuf) अणु
		usb_मुक्त_urb(urb);
		वापस शून्य;
	पूर्ण

	urb->transfer_buffer = dmabuf;
	urb->transfer_buffer_length = bufsize;
	urb->transfer_flags |= URB_FREE_BUFFER;
	वापस urb;
पूर्ण

अटल व्योम usbपंचांगc_पढ़ो_bulk_cb(काष्ठा urb *urb)
अणु
	काष्ठा usbपंचांगc_file_data *file_data = urb->context;
	पूर्णांक status = urb->status;
	अचिन्हित दीर्घ flags;

	/* sync/async unlink faults aren't errors */
	अगर (status) अणु
		अगर (!(/* status == -ENOENT || */
			status == -ECONNRESET ||
			status == -EREMOTEIO || /* Short packet */
			status == -ESHUTDOWN))
			dev_err(&file_data->data->पूर्णांकf->dev,
			"%s - nonzero read bulk status received: %d\n",
			__func__, status);

		spin_lock_irqsave(&file_data->err_lock, flags);
		अगर (!file_data->in_status)
			file_data->in_status = status;
		spin_unlock_irqrestore(&file_data->err_lock, flags);
	पूर्ण

	spin_lock_irqsave(&file_data->err_lock, flags);
	file_data->in_transfer_size += urb->actual_length;
	dev_dbg(&file_data->data->पूर्णांकf->dev,
		"%s - total size: %u current: %d status: %d\n",
		__func__, file_data->in_transfer_size,
		urb->actual_length, status);
	spin_unlock_irqrestore(&file_data->err_lock, flags);
	usb_anchor_urb(urb, &file_data->in_anchor);

	wake_up_पूर्णांकerruptible(&file_data->रुको_bulk_in);
	wake_up_पूर्णांकerruptible(&file_data->data->रुकोq);
पूर्ण

अटल अंतरभूत bool usbपंचांगc_करो_transfer(काष्ठा usbपंचांगc_file_data *file_data)
अणु
	bool data_or_error;

	spin_lock_irq(&file_data->err_lock);
	data_or_error = !usb_anchor_empty(&file_data->in_anchor)
			|| file_data->in_status;
	spin_unlock_irq(&file_data->err_lock);
	dev_dbg(&file_data->data->पूर्णांकf->dev, "%s: returns %d\n", __func__,
		data_or_error);
	वापस data_or_error;
पूर्ण

अटल sमाप_प्रकार usbपंचांगc_generic_पढ़ो(काष्ठा usbपंचांगc_file_data *file_data,
				   व्योम __user *user_buffer,
				   u32 transfer_size,
				   u32 *transferred,
				   u32 flags)
अणु
	काष्ठा usbपंचांगc_device_data *data = file_data->data;
	काष्ठा device *dev = &data->पूर्णांकf->dev;
	u32 करोne = 0;
	u32 reमुख्यing;
	स्थिर u32 bufsize = USBTMC_बफ_मानE;
	पूर्णांक retval = 0;
	u32 max_transfer_size;
	अचिन्हित दीर्घ expire;
	पूर्णांक bufcount = 1;
	पूर्णांक again = 0;

	/* mutex alपढ़ोy locked */

	*transferred = करोne;

	max_transfer_size = transfer_size;

	अगर (flags & USBTMC_FLAG_IGNORE_TRAILER) अणु
		/* The device may send extra alignment bytes (up to
		 * wMaxPacketSize ै  1) to aव्योम sending a zero-length
		 * packet
		 */
		reमुख्यing = transfer_size;
		अगर ((max_transfer_size % data->wMaxPacketSize) == 0)
			max_transfer_size += (data->wMaxPacketSize - 1);
	पूर्ण अन्यथा अणु
		/* round करोwn to bufsize to aव्योम truncated data left */
		अगर (max_transfer_size > bufsize) अणु
			max_transfer_size =
				roundup(max_transfer_size + 1 - bufsize,
					bufsize);
		पूर्ण
		reमुख्यing = max_transfer_size;
	पूर्ण

	spin_lock_irq(&file_data->err_lock);

	अगर (file_data->in_status) अणु
		/* वापस the very first error */
		retval = file_data->in_status;
		spin_unlock_irq(&file_data->err_lock);
		जाओ error;
	पूर्ण

	अगर (flags & USBTMC_FLAG_ASYNC) अणु
		अगर (usb_anchor_empty(&file_data->in_anchor))
			again = 1;

		अगर (file_data->in_urbs_used == 0) अणु
			file_data->in_transfer_size = 0;
			file_data->in_status = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		file_data->in_transfer_size = 0;
		file_data->in_status = 0;
	पूर्ण

	अगर (max_transfer_size == 0) अणु
		bufcount = 0;
	पूर्ण अन्यथा अणु
		bufcount = roundup(max_transfer_size, bufsize) / bufsize;
		अगर (bufcount > file_data->in_urbs_used)
			bufcount -= file_data->in_urbs_used;
		अन्यथा
			bufcount = 0;

		अगर (bufcount + file_data->in_urbs_used > MAX_URBS_IN_FLIGHT) अणु
			bufcount = MAX_URBS_IN_FLIGHT -
					file_data->in_urbs_used;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&file_data->err_lock);

	dev_dbg(dev, "%s: requested=%u flags=0x%X size=%u bufs=%d used=%d\n",
		__func__, transfer_size, flags,
		max_transfer_size, bufcount, file_data->in_urbs_used);

	जबतक (bufcount > 0) अणु
		u8 *dmabuf = शून्य;
		काष्ठा urb *urb = usbपंचांगc_create_urb();

		अगर (!urb) अणु
			retval = -ENOMEM;
			जाओ error;
		पूर्ण

		dmabuf = urb->transfer_buffer;

		usb_fill_bulk_urb(urb, data->usb_dev,
			usb_rcvbulkpipe(data->usb_dev, data->bulk_in),
			dmabuf, bufsize,
			usbपंचांगc_पढ़ो_bulk_cb, file_data);

		usb_anchor_urb(urb, &file_data->submitted);
		retval = usb_submit_urb(urb, GFP_KERNEL);
		/* urb is anchored. We can release our reference. */
		usb_मुक्त_urb(urb);
		अगर (unlikely(retval)) अणु
			usb_unanchor_urb(urb);
			जाओ error;
		पूर्ण
		file_data->in_urbs_used++;
		bufcount--;
	पूर्ण

	अगर (again) अणु
		dev_dbg(dev, "%s: ret=again\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	अगर (user_buffer == शून्य)
		वापस -EINVAL;

	expire = msecs_to_jअगरfies(file_data->समयout);

	जबतक (max_transfer_size > 0) अणु
		u32 this_part;
		काष्ठा urb *urb = शून्य;

		अगर (!(flags & USBTMC_FLAG_ASYNC)) अणु
			dev_dbg(dev, "%s: before wait time %lu\n",
				__func__, expire);
			retval = रुको_event_पूर्णांकerruptible_समयout(
				file_data->रुको_bulk_in,
				usbपंचांगc_करो_transfer(file_data),
				expire);

			dev_dbg(dev, "%s: wait returned %d\n",
				__func__, retval);

			अगर (retval <= 0) अणु
				अगर (retval == 0)
					retval = -ETIMEDOUT;
				जाओ error;
			पूर्ण
		पूर्ण

		urb = usb_get_from_anchor(&file_data->in_anchor);
		अगर (!urb) अणु
			अगर (!(flags & USBTMC_FLAG_ASYNC)) अणु
				/* synchronous हाल: must not happen */
				retval = -EFAULT;
				जाओ error;
			पूर्ण

			/* asynchronous हाल: पढ़ोy, करो not block or रुको */
			*transferred = करोne;
			dev_dbg(dev, "%s: (async) done=%u ret=0\n",
				__func__, करोne);
			वापस 0;
		पूर्ण

		file_data->in_urbs_used--;

		अगर (max_transfer_size > urb->actual_length)
			max_transfer_size -= urb->actual_length;
		अन्यथा
			max_transfer_size = 0;

		अगर (reमुख्यing > urb->actual_length)
			this_part = urb->actual_length;
		अन्यथा
			this_part = reमुख्यing;

		prपूर्णांक_hex_dump_debug("usbtmc ", DUMP_PREFIX_NONE, 16, 1,
			urb->transfer_buffer, urb->actual_length, true);

		अगर (copy_to_user(user_buffer + करोne,
				 urb->transfer_buffer, this_part)) अणु
			usb_मुक्त_urb(urb);
			retval = -EFAULT;
			जाओ error;
		पूर्ण

		reमुख्यing -= this_part;
		करोne += this_part;

		spin_lock_irq(&file_data->err_lock);
		अगर (urb->status) अणु
			/* वापस the very first error */
			retval = file_data->in_status;
			spin_unlock_irq(&file_data->err_lock);
			usb_मुक्त_urb(urb);
			जाओ error;
		पूर्ण
		spin_unlock_irq(&file_data->err_lock);

		अगर (urb->actual_length < bufsize) अणु
			/* लघु packet or ZLP received => पढ़ोy */
			usb_मुक्त_urb(urb);
			retval = 1;
			अवरोध;
		पूर्ण

		अगर (!(flags & USBTMC_FLAG_ASYNC) &&
		    max_transfer_size > (bufsize * file_data->in_urbs_used)) अणु
			/* resubmit, since other buffers still not enough */
			usb_anchor_urb(urb, &file_data->submitted);
			retval = usb_submit_urb(urb, GFP_KERNEL);
			अगर (unlikely(retval)) अणु
				usb_unanchor_urb(urb);
				usb_मुक्त_urb(urb);
				जाओ error;
			पूर्ण
			file_data->in_urbs_used++;
		पूर्ण
		usb_मुक्त_urb(urb);
		retval = 0;
	पूर्ण

error:
	*transferred = करोne;

	dev_dbg(dev, "%s: before kill\n", __func__);
	/* Attention: समाप्तing urbs can take दीर्घ समय (2 ms) */
	usb_समाप्त_anchored_urbs(&file_data->submitted);
	dev_dbg(dev, "%s: after kill\n", __func__);
	usb_scuttle_anchored_urbs(&file_data->in_anchor);
	file_data->in_urbs_used = 0;
	file_data->in_status = 0; /* no spinlock needed here */
	dev_dbg(dev, "%s: done=%u ret=%d\n", __func__, करोne, retval);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार usbपंचांगc_ioctl_generic_पढ़ो(काष्ठा usbपंचांगc_file_data *file_data,
					 व्योम __user *arg)
अणु
	काष्ठा usbपंचांगc_message msg;
	sमाप_प्रकार retval = 0;

	/* mutex alपढ़ोy locked */

	अगर (copy_from_user(&msg, arg, माप(काष्ठा usbपंचांगc_message)))
		वापस -EFAULT;

	retval = usbपंचांगc_generic_पढ़ो(file_data, msg.message,
				     msg.transfer_size, &msg.transferred,
				     msg.flags);

	अगर (put_user(msg.transferred,
		     &((काष्ठा usbपंचांगc_message __user *)arg)->transferred))
		वापस -EFAULT;

	वापस retval;
पूर्ण

अटल व्योम usbपंचांगc_ग_लिखो_bulk_cb(काष्ठा urb *urb)
अणु
	काष्ठा usbपंचांगc_file_data *file_data = urb->context;
	पूर्णांक wakeup = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&file_data->err_lock, flags);
	file_data->out_transfer_size += urb->actual_length;

	/* sync/async unlink faults aren't errors */
	अगर (urb->status) अणु
		अगर (!(urb->status == -ENOENT ||
			urb->status == -ECONNRESET ||
			urb->status == -ESHUTDOWN))
			dev_err(&file_data->data->पूर्णांकf->dev,
				"%s - nonzero write bulk status received: %d\n",
				__func__, urb->status);

		अगर (!file_data->out_status) अणु
			file_data->out_status = urb->status;
			wakeup = 1;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&file_data->err_lock, flags);

	dev_dbg(&file_data->data->पूर्णांकf->dev,
		"%s - write bulk total size: %u\n",
		__func__, file_data->out_transfer_size);

	up(&file_data->limit_ग_लिखो_sem);
	अगर (usb_anchor_empty(&file_data->submitted) || wakeup)
		wake_up_पूर्णांकerruptible(&file_data->data->रुकोq);
पूर्ण

अटल sमाप_प्रकार usbपंचांगc_generic_ग_लिखो(काष्ठा usbपंचांगc_file_data *file_data,
				    स्थिर व्योम __user *user_buffer,
				    u32 transfer_size,
				    u32 *transferred,
				    u32 flags)
अणु
	काष्ठा usbपंचांगc_device_data *data = file_data->data;
	काष्ठा device *dev;
	u32 करोne = 0;
	u32 reमुख्यing;
	अचिन्हित दीर्घ expire;
	स्थिर u32 bufsize = USBTMC_बफ_मानE;
	काष्ठा urb *urb = शून्य;
	पूर्णांक retval = 0;
	u32 समयout;

	*transferred = 0;

	/* Get poपूर्णांकer to निजी data काष्ठाure */
	dev = &data->पूर्णांकf->dev;

	dev_dbg(dev, "%s: size=%u flags=0x%X sema=%u\n",
		__func__, transfer_size, flags,
		file_data->limit_ग_लिखो_sem.count);

	अगर (flags & USBTMC_FLAG_APPEND) अणु
		spin_lock_irq(&file_data->err_lock);
		retval = file_data->out_status;
		spin_unlock_irq(&file_data->err_lock);
		अगर (retval < 0)
			वापस retval;
	पूर्ण अन्यथा अणु
		spin_lock_irq(&file_data->err_lock);
		file_data->out_transfer_size = 0;
		file_data->out_status = 0;
		spin_unlock_irq(&file_data->err_lock);
	पूर्ण

	reमुख्यing = transfer_size;
	अगर (reमुख्यing > पूर्णांक_उच्च)
		reमुख्यing = पूर्णांक_उच्च;

	समयout = file_data->समयout;
	expire = msecs_to_jअगरfies(समयout);

	जबतक (reमुख्यing > 0) अणु
		u32 this_part, aligned;
		u8 *buffer = शून्य;

		अगर (flags & USBTMC_FLAG_ASYNC) अणु
			अगर (करोwn_trylock(&file_data->limit_ग_लिखो_sem)) अणु
				retval = (करोne)?(0):(-EAGAIN);
				जाओ निकास;
			पूर्ण
		पूर्ण अन्यथा अणु
			retval = करोwn_समयout(&file_data->limit_ग_लिखो_sem,
					      expire);
			अगर (retval < 0) अणु
				retval = -ETIMEDOUT;
				जाओ error;
			पूर्ण
		पूर्ण

		spin_lock_irq(&file_data->err_lock);
		retval = file_data->out_status;
		spin_unlock_irq(&file_data->err_lock);
		अगर (retval < 0) अणु
			up(&file_data->limit_ग_लिखो_sem);
			जाओ error;
		पूर्ण

		/* prepare next urb to send */
		urb = usbपंचांगc_create_urb();
		अगर (!urb) अणु
			retval = -ENOMEM;
			up(&file_data->limit_ग_लिखो_sem);
			जाओ error;
		पूर्ण
		buffer = urb->transfer_buffer;

		अगर (reमुख्यing > bufsize)
			this_part = bufsize;
		अन्यथा
			this_part = reमुख्यing;

		अगर (copy_from_user(buffer, user_buffer + करोne, this_part)) अणु
			retval = -EFAULT;
			up(&file_data->limit_ग_लिखो_sem);
			जाओ error;
		पूर्ण

		prपूर्णांक_hex_dump_debug("usbtmc ", DUMP_PREFIX_NONE,
			16, 1, buffer, this_part, true);

		/* fill bulk with 32 bit alignment to meet USBTMC specअगरication
		 * (size + 3 & ~3) rounds up and simplअगरies user code
		 */
		aligned = (this_part + 3) & ~3;
		dev_dbg(dev, "write(size:%u align:%u done:%u)\n",
			(अचिन्हित पूर्णांक)this_part,
			(अचिन्हित पूर्णांक)aligned,
			(अचिन्हित पूर्णांक)करोne);

		usb_fill_bulk_urb(urb, data->usb_dev,
			usb_sndbulkpipe(data->usb_dev, data->bulk_out),
			urb->transfer_buffer, aligned,
			usbपंचांगc_ग_लिखो_bulk_cb, file_data);

		usb_anchor_urb(urb, &file_data->submitted);
		retval = usb_submit_urb(urb, GFP_KERNEL);
		अगर (unlikely(retval)) अणु
			usb_unanchor_urb(urb);
			up(&file_data->limit_ग_लिखो_sem);
			जाओ error;
		पूर्ण

		usb_मुक्त_urb(urb);
		urb = शून्य; /* urb will be finally released by usb driver */

		reमुख्यing -= this_part;
		करोne += this_part;
	पूर्ण

	/* All urbs are on the fly */
	अगर (!(flags & USBTMC_FLAG_ASYNC)) अणु
		अगर (!usb_रुको_anchor_empty_समयout(&file_data->submitted,
						   समयout)) अणु
			retval = -ETIMEDOUT;
			जाओ error;
		पूर्ण
	पूर्ण

	retval = 0;
	जाओ निकास;

error:
	usb_समाप्त_anchored_urbs(&file_data->submitted);
निकास:
	usb_मुक्त_urb(urb);

	spin_lock_irq(&file_data->err_lock);
	अगर (!(flags & USBTMC_FLAG_ASYNC))
		करोne = file_data->out_transfer_size;
	अगर (!retval && file_data->out_status)
		retval = file_data->out_status;
	spin_unlock_irq(&file_data->err_lock);

	*transferred = करोne;

	dev_dbg(dev, "%s: done=%u, retval=%d, urbstat=%d\n",
		__func__, करोne, retval, file_data->out_status);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार usbपंचांगc_ioctl_generic_ग_लिखो(काष्ठा usbपंचांगc_file_data *file_data,
					  व्योम __user *arg)
अणु
	काष्ठा usbपंचांगc_message msg;
	sमाप_प्रकार retval = 0;

	/* mutex alपढ़ोy locked */

	अगर (copy_from_user(&msg, arg, माप(काष्ठा usbपंचांगc_message)))
		वापस -EFAULT;

	retval = usbपंचांगc_generic_ग_लिखो(file_data, msg.message,
				      msg.transfer_size, &msg.transferred,
				      msg.flags);

	अगर (put_user(msg.transferred,
		     &((काष्ठा usbपंचांगc_message __user *)arg)->transferred))
		वापस -EFAULT;

	वापस retval;
पूर्ण

/*
 * Get the generic ग_लिखो result
 */
अटल sमाप_प्रकार usbपंचांगc_ioctl_ग_लिखो_result(काष्ठा usbपंचांगc_file_data *file_data,
				व्योम __user *arg)
अणु
	u32 transferred;
	पूर्णांक retval;

	spin_lock_irq(&file_data->err_lock);
	transferred = file_data->out_transfer_size;
	retval = file_data->out_status;
	spin_unlock_irq(&file_data->err_lock);

	अगर (put_user(transferred, (__u32 __user *)arg))
		वापस -EFAULT;

	वापस retval;
पूर्ण

/*
 * Sends a REQUEST_DEV_DEP_MSG_IN message on the Bulk-OUT endpoपूर्णांक.
 * @transfer_size: number of bytes to request from the device.
 *
 * See the USBTMC specअगरication, Table 4.
 *
 * Also updates bTag_last_ग_लिखो.
 */
अटल पूर्णांक send_request_dev_dep_msg_in(काष्ठा usbपंचांगc_file_data *file_data,
				       u32 transfer_size)
अणु
	काष्ठा usbपंचांगc_device_data *data = file_data->data;
	पूर्णांक retval;
	u8 *buffer;
	पूर्णांक actual;

	buffer = kदो_स्मृति(USBTMC_HEADER_SIZE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;
	/* Setup IO buffer क्रम REQUEST_DEV_DEP_MSG_IN message
	 * Refer to class specs क्रम details
	 */
	buffer[0] = 2;
	buffer[1] = data->bTag;
	buffer[2] = ~data->bTag;
	buffer[3] = 0; /* Reserved */
	buffer[4] = transfer_size >> 0;
	buffer[5] = transfer_size >> 8;
	buffer[6] = transfer_size >> 16;
	buffer[7] = transfer_size >> 24;
	buffer[8] = file_data->term_अक्षर_enabled * 2;
	/* Use term अक्षरacter? */
	buffer[9] = file_data->term_अक्षर;
	buffer[10] = 0; /* Reserved */
	buffer[11] = 0; /* Reserved */

	/* Send bulk URB */
	retval = usb_bulk_msg(data->usb_dev,
			      usb_sndbulkpipe(data->usb_dev,
					      data->bulk_out),
			      buffer, USBTMC_HEADER_SIZE,
			      &actual, file_data->समयout);

	/* Store bTag (in हाल we need to पात) */
	data->bTag_last_ग_लिखो = data->bTag;

	/* Increment bTag -- and increment again अगर zero */
	data->bTag++;
	अगर (!data->bTag)
		data->bTag++;

	kमुक्त(buffer);
	अगर (retval < 0)
		dev_err(&data->पूर्णांकf->dev, "%s returned %d\n",
			__func__, retval);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार usbपंचांगc_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा usbपंचांगc_file_data *file_data;
	काष्ठा usbपंचांगc_device_data *data;
	काष्ठा device *dev;
	स्थिर u32 bufsize = USBTMC_बफ_मानE;
	u32 n_अक्षरacters;
	u8 *buffer;
	पूर्णांक actual;
	u32 करोne = 0;
	u32 reमुख्यing;
	पूर्णांक retval;

	/* Get poपूर्णांकer to निजी data काष्ठाure */
	file_data = filp->निजी_data;
	data = file_data->data;
	dev = &data->पूर्णांकf->dev;

	buffer = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	mutex_lock(&data->io_mutex);
	अगर (data->zombie) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	अगर (count > पूर्णांक_उच्च)
		count = पूर्णांक_उच्च;

	dev_dbg(dev, "%s(count:%zu)\n", __func__, count);

	retval = send_request_dev_dep_msg_in(file_data, count);

	अगर (retval < 0) अणु
		अगर (file_data->स्वतः_पात)
			usbपंचांगc_ioctl_पात_bulk_out(data);
		जाओ निकास;
	पूर्ण

	/* Loop until we have fetched everything we requested */
	reमुख्यing = count;
	actual = 0;

	/* Send bulk URB */
	retval = usb_bulk_msg(data->usb_dev,
			      usb_rcvbulkpipe(data->usb_dev,
					      data->bulk_in),
			      buffer, bufsize, &actual,
			      file_data->समयout);

	dev_dbg(dev, "%s: bulk_msg retval(%u), actual(%d)\n",
		__func__, retval, actual);

	/* Store bTag (in हाल we need to पात) */
	data->bTag_last_पढ़ो = data->bTag;

	अगर (retval < 0) अणु
		अगर (file_data->स्वतः_पात)
			usbपंचांगc_ioctl_पात_bulk_in(data);
		जाओ निकास;
	पूर्ण

	/* Sanity checks क्रम the header */
	अगर (actual < USBTMC_HEADER_SIZE) अणु
		dev_err(dev, "Device sent too small first packet: %u < %u\n",
			actual, USBTMC_HEADER_SIZE);
		अगर (file_data->स्वतः_पात)
			usbपंचांगc_ioctl_पात_bulk_in(data);
		जाओ निकास;
	पूर्ण

	अगर (buffer[0] != 2) अणु
		dev_err(dev, "Device sent reply with wrong MsgID: %u != 2\n",
			buffer[0]);
		अगर (file_data->स्वतः_पात)
			usbपंचांगc_ioctl_पात_bulk_in(data);
		जाओ निकास;
	पूर्ण

	अगर (buffer[1] != data->bTag_last_ग_लिखो) अणु
		dev_err(dev, "Device sent reply with wrong bTag: %u != %u\n",
		buffer[1], data->bTag_last_ग_लिखो);
		अगर (file_data->स्वतः_पात)
			usbपंचांगc_ioctl_पात_bulk_in(data);
		जाओ निकास;
	पूर्ण

	/* How many अक्षरacters did the instrument send? */
	n_अक्षरacters = buffer[4] +
		       (buffer[5] << 8) +
		       (buffer[6] << 16) +
		       (buffer[7] << 24);

	file_data->bmTransferAttributes = buffer[8];

	dev_dbg(dev, "Bulk-IN header: N_characters(%u), bTransAttr(%u)\n",
		n_अक्षरacters, buffer[8]);

	अगर (n_अक्षरacters > reमुख्यing) अणु
		dev_err(dev, "Device wants to return more data than requested: %u > %zu\n",
			n_अक्षरacters, count);
		अगर (file_data->स्वतः_पात)
			usbपंचांगc_ioctl_पात_bulk_in(data);
		जाओ निकास;
	पूर्ण

	prपूर्णांक_hex_dump_debug("usbtmc ", DUMP_PREFIX_NONE,
			     16, 1, buffer, actual, true);

	reमुख्यing = n_अक्षरacters;

	/* Remove the USBTMC header */
	actual -= USBTMC_HEADER_SIZE;

	/* Remove padding अगर it exists */
	अगर (actual > reमुख्यing)
		actual = reमुख्यing;

	reमुख्यing -= actual;

	/* Copy buffer to user space */
	अगर (copy_to_user(buf, &buffer[USBTMC_HEADER_SIZE], actual)) अणु
		/* There must have been an addressing problem */
		retval = -EFAULT;
		जाओ निकास;
	पूर्ण

	अगर ((actual + USBTMC_HEADER_SIZE) == bufsize) अणु
		retval = usbपंचांगc_generic_पढ़ो(file_data, buf + actual,
					     reमुख्यing,
					     &करोne,
					     USBTMC_FLAG_IGNORE_TRAILER);
		अगर (retval < 0)
			जाओ निकास;
	पूर्ण
	करोne += actual;

	/* Update file position value */
	*f_pos = *f_pos + करोne;
	retval = करोne;

निकास:
	mutex_unlock(&data->io_mutex);
	kमुक्त(buffer);
	वापस retval;
पूर्ण

अटल sमाप_प्रकार usbपंचांगc_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा usbपंचांगc_file_data *file_data;
	काष्ठा usbपंचांगc_device_data *data;
	काष्ठा urb *urb = शून्य;
	sमाप_प्रकार retval = 0;
	u8 *buffer;
	u32 reमुख्यing, करोne;
	u32 transfersize, aligned, buflen;

	file_data = filp->निजी_data;
	data = file_data->data;

	mutex_lock(&data->io_mutex);

	अगर (data->zombie) अणु
		retval = -ENODEV;
		जाओ निकास;
	पूर्ण

	करोne = 0;

	spin_lock_irq(&file_data->err_lock);
	file_data->out_transfer_size = 0;
	file_data->out_status = 0;
	spin_unlock_irq(&file_data->err_lock);

	अगर (!count)
		जाओ निकास;

	अगर (करोwn_trylock(&file_data->limit_ग_लिखो_sem)) अणु
		/* previous calls were async */
		retval = -EBUSY;
		जाओ निकास;
	पूर्ण

	urb = usbपंचांगc_create_urb();
	अगर (!urb) अणु
		retval = -ENOMEM;
		up(&file_data->limit_ग_लिखो_sem);
		जाओ निकास;
	पूर्ण

	buffer = urb->transfer_buffer;
	buflen = urb->transfer_buffer_length;

	अगर (count > पूर्णांक_उच्च) अणु
		transfersize = पूर्णांक_उच्च;
		buffer[8] = 0;
	पूर्ण अन्यथा अणु
		transfersize = count;
		buffer[8] = file_data->eom_val;
	पूर्ण

	/* Setup IO buffer क्रम DEV_DEP_MSG_OUT message */
	buffer[0] = 1;
	buffer[1] = data->bTag;
	buffer[2] = ~data->bTag;
	buffer[3] = 0; /* Reserved */
	buffer[4] = transfersize >> 0;
	buffer[5] = transfersize >> 8;
	buffer[6] = transfersize >> 16;
	buffer[7] = transfersize >> 24;
	/* buffer[8] is set above... */
	buffer[9] = 0; /* Reserved */
	buffer[10] = 0; /* Reserved */
	buffer[11] = 0; /* Reserved */

	reमुख्यing = transfersize;

	अगर (transfersize + USBTMC_HEADER_SIZE > buflen) अणु
		transfersize = buflen - USBTMC_HEADER_SIZE;
		aligned = buflen;
	पूर्ण अन्यथा अणु
		aligned = (transfersize + (USBTMC_HEADER_SIZE + 3)) & ~3;
	पूर्ण

	अगर (copy_from_user(&buffer[USBTMC_HEADER_SIZE], buf, transfersize)) अणु
		retval = -EFAULT;
		up(&file_data->limit_ग_लिखो_sem);
		जाओ निकास;
	पूर्ण

	dev_dbg(&data->पूर्णांकf->dev, "%s(size:%u align:%u)\n", __func__,
		(अचिन्हित पूर्णांक)transfersize, (अचिन्हित पूर्णांक)aligned);

	prपूर्णांक_hex_dump_debug("usbtmc ", DUMP_PREFIX_NONE,
			     16, 1, buffer, aligned, true);

	usb_fill_bulk_urb(urb, data->usb_dev,
		usb_sndbulkpipe(data->usb_dev, data->bulk_out),
		urb->transfer_buffer, aligned,
		usbपंचांगc_ग_लिखो_bulk_cb, file_data);

	usb_anchor_urb(urb, &file_data->submitted);
	retval = usb_submit_urb(urb, GFP_KERNEL);
	अगर (unlikely(retval)) अणु
		usb_unanchor_urb(urb);
		up(&file_data->limit_ग_लिखो_sem);
		जाओ निकास;
	पूर्ण

	reमुख्यing -= transfersize;

	data->bTag_last_ग_लिखो = data->bTag;
	data->bTag++;

	अगर (!data->bTag)
		data->bTag++;

	/* call generic_ग_लिखो even when reमुख्यing = 0 */
	retval = usbपंचांगc_generic_ग_लिखो(file_data, buf + transfersize, reमुख्यing,
				      &करोne, USBTMC_FLAG_APPEND);
	/* truncate alignment bytes */
	अगर (करोne > reमुख्यing)
		करोne = reमुख्यing;

	/*add size of first urb*/
	करोne += transfersize;

	अगर (retval < 0) अणु
		usb_समाप्त_anchored_urbs(&file_data->submitted);

		dev_err(&data->पूर्णांकf->dev,
			"Unable to send data, error %d\n", (पूर्णांक)retval);
		अगर (file_data->स्वतः_पात)
			usbपंचांगc_ioctl_पात_bulk_out(data);
		जाओ निकास;
	पूर्ण

	retval = करोne;
निकास:
	usb_मुक्त_urb(urb);
	mutex_unlock(&data->io_mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_clear(काष्ठा usbपंचांगc_device_data *data)
अणु
	काष्ठा device *dev;
	u8 *buffer;
	पूर्णांक rv;
	पूर्णांक n;
	पूर्णांक actual = 0;

	dev = &data->पूर्णांकf->dev;

	dev_dbg(dev, "Sending INITIATE_CLEAR request\n");

	buffer = kदो_स्मृति(USBTMC_बफ_मानE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_INITIATE_CLEAR,
			     USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			     0, 0, buffer, 1, USB_CTRL_GET_TIMEOUT);
	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण

	dev_dbg(dev, "INITIATE_CLEAR returned %x\n", buffer[0]);

	अगर (buffer[0] != USBTMC_STATUS_SUCCESS) अणु
		dev_err(dev, "INITIATE_CLEAR returned %x\n", buffer[0]);
		rv = -EPERM;
		जाओ निकास;
	पूर्ण

	n = 0;

usbपंचांगc_clear_check_status:

	dev_dbg(dev, "Sending CHECK_CLEAR_STATUS request\n");

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_CHECK_CLEAR_STATUS,
			     USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			     0, 0, buffer, 2, USB_CTRL_GET_TIMEOUT);
	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण

	dev_dbg(dev, "CHECK_CLEAR_STATUS returned %x\n", buffer[0]);

	अगर (buffer[0] == USBTMC_STATUS_SUCCESS)
		जाओ usbपंचांगc_clear_bulk_out_halt;

	अगर (buffer[0] != USBTMC_STATUS_PENDING) अणु
		dev_err(dev, "CHECK_CLEAR_STATUS returned %x\n", buffer[0]);
		rv = -EPERM;
		जाओ निकास;
	पूर्ण

	अगर ((buffer[1] & 1) != 0) अणु
		करो अणु
			dev_dbg(dev, "Reading from bulk in EP\n");

			actual = 0;
			rv = usb_bulk_msg(data->usb_dev,
					  usb_rcvbulkpipe(data->usb_dev,
							  data->bulk_in),
					  buffer, USBTMC_बफ_मानE,
					  &actual, USB_CTRL_GET_TIMEOUT);

			prपूर्णांक_hex_dump_debug("usbtmc ", DUMP_PREFIX_NONE,
					     16, 1, buffer, actual, true);

			n++;

			अगर (rv < 0) अणु
				dev_err(dev, "usb_control_msg returned %d\n",
					rv);
				जाओ निकास;
			पूर्ण
		पूर्ण जबतक ((actual == USBTMC_बफ_मानE) &&
			  (n < USBTMC_MAX_READS_TO_CLEAR_BULK_IN));
	पूर्ण अन्यथा अणु
		/* करो not stress device with subsequent requests */
		msleep(50);
		n++;
	पूर्ण

	अगर (n >= USBTMC_MAX_READS_TO_CLEAR_BULK_IN) अणु
		dev_err(dev, "Couldn't clear device buffer within %d cycles\n",
			USBTMC_MAX_READS_TO_CLEAR_BULK_IN);
		rv = -EPERM;
		जाओ निकास;
	पूर्ण

	जाओ usbपंचांगc_clear_check_status;

usbपंचांगc_clear_bulk_out_halt:

	rv = usb_clear_halt(data->usb_dev,
			    usb_sndbulkpipe(data->usb_dev, data->bulk_out));
	अगर (rv < 0) अणु
		dev_err(dev, "usb_clear_halt returned %d\n", rv);
		जाओ निकास;
	पूर्ण
	rv = 0;

निकास:
	kमुक्त(buffer);
	वापस rv;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_clear_out_halt(काष्ठा usbपंचांगc_device_data *data)
अणु
	पूर्णांक rv;

	rv = usb_clear_halt(data->usb_dev,
			    usb_sndbulkpipe(data->usb_dev, data->bulk_out));

	अगर (rv < 0)
		dev_err(&data->usb_dev->dev, "%s returned %d\n", __func__, rv);
	वापस rv;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_clear_in_halt(काष्ठा usbपंचांगc_device_data *data)
अणु
	पूर्णांक rv;

	rv = usb_clear_halt(data->usb_dev,
			    usb_rcvbulkpipe(data->usb_dev, data->bulk_in));

	अगर (rv < 0)
		dev_err(&data->usb_dev->dev, "%s returned %d\n", __func__, rv);
	वापस rv;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_cancel_io(काष्ठा usbपंचांगc_file_data *file_data)
अणु
	spin_lock_irq(&file_data->err_lock);
	file_data->in_status = -ECANCELED;
	file_data->out_status = -ECANCELED;
	spin_unlock_irq(&file_data->err_lock);
	usb_समाप्त_anchored_urbs(&file_data->submitted);
	वापस 0;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_cleanup_io(काष्ठा usbपंचांगc_file_data *file_data)
अणु
	usb_समाप्त_anchored_urbs(&file_data->submitted);
	usb_scuttle_anchored_urbs(&file_data->in_anchor);
	spin_lock_irq(&file_data->err_lock);
	file_data->in_status = 0;
	file_data->in_transfer_size = 0;
	file_data->out_status = 0;
	file_data->out_transfer_size = 0;
	spin_unlock_irq(&file_data->err_lock);

	file_data->in_urbs_used = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक get_capabilities(काष्ठा usbपंचांगc_device_data *data)
अणु
	काष्ठा device *dev = &data->usb_dev->dev;
	अक्षर *buffer;
	पूर्णांक rv = 0;

	buffer = kदो_स्मृति(0x18, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	rv = usb_control_msg(data->usb_dev, usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_GET_CAPABILITIES,
			     USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			     0, 0, buffer, 0x18, USB_CTRL_GET_TIMEOUT);
	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ err_out;
	पूर्ण

	dev_dbg(dev, "GET_CAPABILITIES returned %x\n", buffer[0]);
	अगर (buffer[0] != USBTMC_STATUS_SUCCESS) अणु
		dev_err(dev, "GET_CAPABILITIES returned %x\n", buffer[0]);
		rv = -EPERM;
		जाओ err_out;
	पूर्ण
	dev_dbg(dev, "Interface capabilities are %x\n", buffer[4]);
	dev_dbg(dev, "Device capabilities are %x\n", buffer[5]);
	dev_dbg(dev, "USB488 interface capabilities are %x\n", buffer[14]);
	dev_dbg(dev, "USB488 device capabilities are %x\n", buffer[15]);

	data->capabilities.पूर्णांकerface_capabilities = buffer[4];
	data->capabilities.device_capabilities = buffer[5];
	data->capabilities.usb488_पूर्णांकerface_capabilities = buffer[14];
	data->capabilities.usb488_device_capabilities = buffer[15];
	data->usb488_caps = (buffer[14] & 0x07) | ((buffer[15] & 0x0f) << 4);
	rv = 0;

err_out:
	kमुक्त(buffer);
	वापस rv;
पूर्ण

#घोषणा capability_attribute(name)					\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);		\
	काष्ठा usbपंचांगc_device_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);	\
									\
	वापस प्र_लिखो(buf, "%d\n", data->capabilities.name);		\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

capability_attribute(पूर्णांकerface_capabilities);
capability_attribute(device_capabilities);
capability_attribute(usb488_पूर्णांकerface_capabilities);
capability_attribute(usb488_device_capabilities);

अटल काष्ठा attribute *usbपंचांगc_attrs[] = अणु
	&dev_attr_पूर्णांकerface_capabilities.attr,
	&dev_attr_device_capabilities.attr,
	&dev_attr_usb488_पूर्णांकerface_capabilities.attr,
	&dev_attr_usb488_device_capabilities.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(usbपंचांगc);

अटल पूर्णांक usbपंचांगc_ioctl_indicator_pulse(काष्ठा usbपंचांगc_device_data *data)
अणु
	काष्ठा device *dev;
	u8 *buffer;
	पूर्णांक rv;

	dev = &data->पूर्णांकf->dev;

	buffer = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	rv = usb_control_msg(data->usb_dev,
			     usb_rcvctrlpipe(data->usb_dev, 0),
			     USBTMC_REQUEST_INDICATOR_PULSE,
			     USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			     0, 0, buffer, 0x01, USB_CTRL_GET_TIMEOUT);

	अगर (rv < 0) अणु
		dev_err(dev, "usb_control_msg returned %d\n", rv);
		जाओ निकास;
	पूर्ण

	dev_dbg(dev, "INDICATOR_PULSE returned %x\n", buffer[0]);

	अगर (buffer[0] != USBTMC_STATUS_SUCCESS) अणु
		dev_err(dev, "INDICATOR_PULSE returned %x\n", buffer[0]);
		rv = -EPERM;
		जाओ निकास;
	पूर्ण
	rv = 0;

निकास:
	kमुक्त(buffer);
	वापस rv;
पूर्ण

अटल पूर्णांक usbपंचांगc_ioctl_request(काष्ठा usbपंचांगc_device_data *data,
				व्योम __user *arg)
अणु
	काष्ठा device *dev = &data->पूर्णांकf->dev;
	काष्ठा usbपंचांगc_ctrlrequest request;
	u8 *buffer = शून्य;
	पूर्णांक rv;
	अचिन्हित दीर्घ res;

	res = copy_from_user(&request, arg, माप(काष्ठा usbपंचांगc_ctrlrequest));
	अगर (res)
		वापस -EFAULT;

	अगर (request.req.wLength > USBTMC_बफ_मानE)
		वापस -EMSGSIZE;

	अगर (request.req.wLength) अणु
		buffer = kदो_स्मृति(request.req.wLength, GFP_KERNEL);
		अगर (!buffer)
			वापस -ENOMEM;

		अगर ((request.req.bRequestType & USB_सूची_IN) == 0) अणु
			/* Send control data to device */
			res = copy_from_user(buffer, request.data,
					     request.req.wLength);
			अगर (res) अणु
				rv = -EFAULT;
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	rv = usb_control_msg(data->usb_dev,
			usb_rcvctrlpipe(data->usb_dev, 0),
			request.req.bRequest,
			request.req.bRequestType,
			request.req.wValue,
			request.req.wIndex,
			buffer, request.req.wLength, USB_CTRL_GET_TIMEOUT);

	अगर (rv < 0) अणु
		dev_err(dev, "%s failed %d\n", __func__, rv);
		जाओ निकास;
	पूर्ण

	अगर (rv && (request.req.bRequestType & USB_सूची_IN)) अणु
		/* Read control data from device */
		res = copy_to_user(request.data, buffer, rv);
		अगर (res)
			rv = -EFAULT;
	पूर्ण

 निकास:
	kमुक्त(buffer);
	वापस rv;
पूर्ण

/*
 * Get the usb समयout value
 */
अटल पूर्णांक usbपंचांगc_ioctl_get_समयout(काष्ठा usbपंचांगc_file_data *file_data,
				व्योम __user *arg)
अणु
	u32 समयout;

	समयout = file_data->समयout;

	वापस put_user(समयout, (__u32 __user *)arg);
पूर्ण

/*
 * Set the usb समयout value
 */
अटल पूर्णांक usbपंचांगc_ioctl_set_समयout(काष्ठा usbपंचांगc_file_data *file_data,
				व्योम __user *arg)
अणु
	u32 समयout;

	अगर (get_user(समयout, (__u32 __user *)arg))
		वापस -EFAULT;

	/* Note that समयout = 0 means
	 * MAX_SCHEDULE_TIMEOUT in usb_control_msg
	 */
	अगर (समयout < USBTMC_MIN_TIMEOUT)
		वापस -EINVAL;

	file_data->समयout = समयout;

	वापस 0;
पूर्ण

/*
 * enables/disables sending EOM on ग_लिखो
 */
अटल पूर्णांक usbपंचांगc_ioctl_eom_enable(काष्ठा usbपंचांगc_file_data *file_data,
				व्योम __user *arg)
अणु
	u8 eom_enable;

	अगर (copy_from_user(&eom_enable, arg, माप(eom_enable)))
		वापस -EFAULT;

	अगर (eom_enable > 1)
		वापस -EINVAL;

	file_data->eom_val = eom_enable;

	वापस 0;
पूर्ण

/*
 * Configure termination अक्षरacter क्रम पढ़ो()
 */
अटल पूर्णांक usbपंचांगc_ioctl_config_termc(काष्ठा usbपंचांगc_file_data *file_data,
				व्योम __user *arg)
अणु
	काष्ठा usbपंचांगc_termअक्षर termc;

	अगर (copy_from_user(&termc, arg, माप(termc)))
		वापस -EFAULT;

	अगर ((termc.term_अक्षर_enabled > 1) ||
		(termc.term_अक्षर_enabled &&
		!(file_data->data->capabilities.device_capabilities & 1)))
		वापस -EINVAL;

	file_data->term_अक्षर = termc.term_अक्षर;
	file_data->term_अक्षर_enabled = termc.term_अक्षर_enabled;

	वापस 0;
पूर्ण

अटल दीर्घ usbपंचांगc_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा usbपंचांगc_file_data *file_data;
	काष्ठा usbपंचांगc_device_data *data;
	पूर्णांक retval = -EBADRQC;
	__u8 पंचांगp_byte;

	file_data = file->निजी_data;
	data = file_data->data;

	mutex_lock(&data->io_mutex);
	अगर (data->zombie) अणु
		retval = -ENODEV;
		जाओ skip_io_on_zombie;
	पूर्ण

	चयन (cmd) अणु
	हाल USBTMC_IOCTL_CLEAR_OUT_HALT:
		retval = usbपंचांगc_ioctl_clear_out_halt(data);
		अवरोध;

	हाल USBTMC_IOCTL_CLEAR_IN_HALT:
		retval = usbपंचांगc_ioctl_clear_in_halt(data);
		अवरोध;

	हाल USBTMC_IOCTL_INDICATOR_PULSE:
		retval = usbपंचांगc_ioctl_indicator_pulse(data);
		अवरोध;

	हाल USBTMC_IOCTL_CLEAR:
		retval = usbपंचांगc_ioctl_clear(data);
		अवरोध;

	हाल USBTMC_IOCTL_ABORT_BULK_OUT:
		retval = usbपंचांगc_ioctl_पात_bulk_out(data);
		अवरोध;

	हाल USBTMC_IOCTL_ABORT_BULK_IN:
		retval = usbपंचांगc_ioctl_पात_bulk_in(data);
		अवरोध;

	हाल USBTMC_IOCTL_CTRL_REQUEST:
		retval = usbपंचांगc_ioctl_request(data, (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_GET_TIMEOUT:
		retval = usbपंचांगc_ioctl_get_समयout(file_data,
						  (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_SET_TIMEOUT:
		retval = usbपंचांगc_ioctl_set_समयout(file_data,
						  (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_EOM_ENABLE:
		retval = usbपंचांगc_ioctl_eom_enable(file_data,
						 (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_CONFIG_TERMCHAR:
		retval = usbपंचांगc_ioctl_config_termc(file_data,
						   (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_WRITE:
		retval = usbपंचांगc_ioctl_generic_ग_लिखो(file_data,
						    (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_READ:
		retval = usbपंचांगc_ioctl_generic_पढ़ो(file_data,
						   (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_WRITE_RESULT:
		retval = usbपंचांगc_ioctl_ग_लिखो_result(file_data,
						   (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_API_VERSION:
		retval = put_user(USBTMC_API_VERSION,
				  (__u32 __user *)arg);
		अवरोध;

	हाल USBTMC488_IOCTL_GET_CAPS:
		retval = put_user(data->usb488_caps,
				  (अचिन्हित अक्षर __user *)arg);
		अवरोध;

	हाल USBTMC488_IOCTL_READ_STB:
		retval = usbपंचांगc488_ioctl_पढ़ो_stb(file_data,
						  (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC488_IOCTL_REN_CONTROL:
		retval = usbपंचांगc488_ioctl_simple(data, (व्योम __user *)arg,
						USBTMC488_REQUEST_REN_CONTROL);
		अवरोध;

	हाल USBTMC488_IOCTL_GOTO_LOCAL:
		retval = usbपंचांगc488_ioctl_simple(data, (व्योम __user *)arg,
						USBTMC488_REQUEST_GOTO_LOCAL);
		अवरोध;

	हाल USBTMC488_IOCTL_LOCAL_LOCKOUT:
		retval = usbपंचांगc488_ioctl_simple(data, (व्योम __user *)arg,
						USBTMC488_REQUEST_LOCAL_LOCKOUT);
		अवरोध;

	हाल USBTMC488_IOCTL_TRIGGER:
		retval = usbपंचांगc488_ioctl_trigger(file_data);
		अवरोध;

	हाल USBTMC488_IOCTL_WAIT_SRQ:
		retval = usbपंचांगc488_ioctl_रुको_srq(file_data,
						  (__u32 __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_MSG_IN_ATTR:
		retval = put_user(file_data->bmTransferAttributes,
				  (__u8 __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_AUTO_ABORT:
		retval = get_user(पंचांगp_byte, (अचिन्हित अक्षर __user *)arg);
		अगर (retval == 0)
			file_data->स्वतः_पात = !!पंचांगp_byte;
		अवरोध;

	हाल USBTMC_IOCTL_GET_STB:
		retval = usbपंचांगc_get_stb(file_data, &पंचांगp_byte);
		अगर (retval > 0)
			retval = put_user(पंचांगp_byte, (__u8 __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_GET_SRQ_STB:
		retval = usbपंचांगc_ioctl_get_srq_stb(file_data,
						  (व्योम __user *)arg);
		अवरोध;

	हाल USBTMC_IOCTL_CANCEL_IO:
		retval = usbपंचांगc_ioctl_cancel_io(file_data);
		अवरोध;

	हाल USBTMC_IOCTL_CLEANUP_IO:
		retval = usbपंचांगc_ioctl_cleanup_io(file_data);
		अवरोध;
	पूर्ण

skip_io_on_zombie:
	mutex_unlock(&data->io_mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक usbपंचांगc_fasync(पूर्णांक fd, काष्ठा file *file, पूर्णांक on)
अणु
	काष्ठा usbपंचांगc_file_data *file_data = file->निजी_data;

	वापस fasync_helper(fd, file, on, &file_data->data->fasync);
पूर्ण

अटल __poll_t usbपंचांगc_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा usbपंचांगc_file_data *file_data = file->निजी_data;
	काष्ठा usbपंचांगc_device_data *data = file_data->data;
	__poll_t mask;

	mutex_lock(&data->io_mutex);

	अगर (data->zombie) अणु
		mask = EPOLLHUP | EPOLLERR;
		जाओ no_poll;
	पूर्ण

	poll_रुको(file, &data->रुकोq, रुको);

	/* Note that EPOLLPRI is now asचिन्हित to SRQ, and
	 * EPOLLIN|EPOLLRDNORM to normal पढ़ो data.
	 */
	mask = 0;
	अगर (atomic_पढ़ो(&file_data->srq_निश्चितed))
		mask |= EPOLLPRI;

	/* Note that the anchor submitted includes all urbs क्रम BULK IN
	 * and OUT. So EPOLLOUT is संकेतed when BULK OUT is empty and
	 * all BULK IN urbs are completed and moved to in_anchor.
	 */
	अगर (usb_anchor_empty(&file_data->submitted))
		mask |= (EPOLLOUT | EPOLLWRNORM);
	अगर (!usb_anchor_empty(&file_data->in_anchor))
		mask |= (EPOLLIN | EPOLLRDNORM);

	spin_lock_irq(&file_data->err_lock);
	अगर (file_data->in_status || file_data->out_status)
		mask |= EPOLLERR;
	spin_unlock_irq(&file_data->err_lock);

	dev_dbg(&data->पूर्णांकf->dev, "poll mask = %x\n", mask);

no_poll:
	mutex_unlock(&data->io_mutex);
	वापस mask;
पूर्ण

अटल स्थिर काष्ठा file_operations fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= usbपंचांगc_पढ़ो,
	.ग_लिखो		= usbपंचांगc_ग_लिखो,
	.खोलो		= usbपंचांगc_खोलो,
	.release	= usbपंचांगc_release,
	.flush		= usbपंचांगc_flush,
	.unlocked_ioctl	= usbपंचांगc_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.fasync         = usbपंचांगc_fasync,
	.poll           = usbपंचांगc_poll,
	.llseek		= शेष_llseek,
पूर्ण;

अटल काष्ठा usb_class_driver usbपंचांगc_class = अणु
	.name =		"usbtmc%d",
	.fops =		&fops,
	.minor_base =	USBTMC_MINOR_BASE,
पूर्ण;

अटल व्योम usbपंचांगc_पूर्णांकerrupt(काष्ठा urb *urb)
अणु
	काष्ठा usbपंचांगc_device_data *data = urb->context;
	काष्ठा device *dev = &data->पूर्णांकf->dev;
	पूर्णांक status = urb->status;
	पूर्णांक rv;

	dev_dbg(&data->पूर्णांकf->dev, "int status: %d len %d\n",
		status, urb->actual_length);

	चयन (status) अणु
	हाल 0: /* SUCCESS */
		/* check क्रम valid STB notअगरication */
		अगर (data->iin_buffer[0] > 0x81) अणु
			data->bNotअगरy1 = data->iin_buffer[0];
			data->bNotअगरy2 = data->iin_buffer[1];
			atomic_set(&data->iin_data_valid, 1);
			wake_up_पूर्णांकerruptible(&data->रुकोq);
			जाओ निकास;
		पूर्ण
		/* check क्रम SRQ notअगरication */
		अगर (data->iin_buffer[0] == 0x81) अणु
			अचिन्हित दीर्घ flags;
			काष्ठा list_head *elem;

			अगर (data->fasync)
				समाप्त_fasync(&data->fasync,
					SIGIO, POLL_PRI);

			spin_lock_irqsave(&data->dev_lock, flags);
			list_क्रम_each(elem, &data->file_list) अणु
				काष्ठा usbपंचांगc_file_data *file_data;

				file_data = list_entry(elem,
						       काष्ठा usbपंचांगc_file_data,
						       file_elem);
				file_data->srq_byte = data->iin_buffer[1];
				atomic_set(&file_data->srq_निश्चितed, 1);
			पूर्ण
			spin_unlock_irqrestore(&data->dev_lock, flags);

			dev_dbg(dev, "srq received bTag %x stb %x\n",
				(अचिन्हित पूर्णांक)data->iin_buffer[0],
				(अचिन्हित पूर्णांक)data->iin_buffer[1]);
			wake_up_पूर्णांकerruptible_all(&data->रुकोq);
			जाओ निकास;
		पूर्ण
		dev_warn(dev, "invalid notification: %x\n",
			 data->iin_buffer[0]);
		अवरोध;
	हाल -EOVERFLOW:
		dev_err(dev, "overflow with length %d, actual length is %d\n",
			data->iin_wMaxPacketSize, urb->actual_length);
		fallthrough;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -EILSEQ:
	हाल -ETIME:
	हाल -EPIPE:
		/* urb terminated, clean up */
		dev_dbg(dev, "urb terminated, status: %d\n", status);
		वापस;
	शेष:
		dev_err(dev, "unknown status received: %d\n", status);
	पूर्ण
निकास:
	rv = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rv)
		dev_err(dev, "usb_submit_urb failed: %d\n", rv);
पूर्ण

अटल व्योम usbपंचांगc_मुक्त_पूर्णांक(काष्ठा usbपंचांगc_device_data *data)
अणु
	अगर (!data->iin_ep_present || !data->iin_urb)
		वापस;
	usb_समाप्त_urb(data->iin_urb);
	kमुक्त(data->iin_buffer);
	data->iin_buffer = शून्य;
	usb_मुक्त_urb(data->iin_urb);
	data->iin_urb = शून्य;
	kref_put(&data->kref, usbपंचांगc_delete);
पूर्ण

अटल पूर्णांक usbपंचांगc_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usbपंचांगc_device_data *data;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *bulk_in, *bulk_out, *पूर्णांक_in;
	पूर्णांक retcode;

	dev_dbg(&पूर्णांकf->dev, "%s called\n", __func__);

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->पूर्णांकf = पूर्णांकf;
	data->id = id;
	data->usb_dev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकf));
	usb_set_पूर्णांकfdata(पूर्णांकf, data);
	kref_init(&data->kref);
	mutex_init(&data->io_mutex);
	init_रुकोqueue_head(&data->रुकोq);
	atomic_set(&data->iin_data_valid, 0);
	INIT_LIST_HEAD(&data->file_list);
	spin_lock_init(&data->dev_lock);

	data->zombie = 0;

	/* Initialize USBTMC bTag and other fields */
	data->bTag	= 1;
	/*  2 <= bTag <= 127   USBTMC-USB488 subclass specअगरication 4.3.1 */
	data->iin_bTag = 2;

	/* USBTMC devices have only one setting, so use that */
	अगरace_desc = data->पूर्णांकf->cur_altsetting;
	data->अगरnum = अगरace_desc->desc.bInterfaceNumber;

	/* Find bulk endpoपूर्णांकs */
	retcode = usb_find_common_endpoपूर्णांकs(अगरace_desc,
			&bulk_in, &bulk_out, शून्य, शून्य);
	अगर (retcode) अणु
		dev_err(&पूर्णांकf->dev, "bulk endpoints not found\n");
		जाओ err_put;
	पूर्ण

	retcode = -EINVAL;
	data->bulk_in = bulk_in->bEndpoपूर्णांकAddress;
	data->wMaxPacketSize = usb_endpoपूर्णांक_maxp(bulk_in);
	अगर (!data->wMaxPacketSize)
		जाओ err_put;
	dev_dbg(&पूर्णांकf->dev, "Found bulk in endpoint at %u\n", data->bulk_in);

	data->bulk_out = bulk_out->bEndpoपूर्णांकAddress;
	dev_dbg(&पूर्णांकf->dev, "Found Bulk out endpoint at %u\n", data->bulk_out);

	/* Find पूर्णांक endpoपूर्णांक */
	retcode = usb_find_पूर्णांक_in_endpoपूर्णांक(अगरace_desc, &पूर्णांक_in);
	अगर (!retcode) अणु
		data->iin_ep_present = 1;
		data->iin_ep = पूर्णांक_in->bEndpoपूर्णांकAddress;
		data->iin_wMaxPacketSize = usb_endpoपूर्णांक_maxp(पूर्णांक_in);
		data->iin_पूर्णांकerval = पूर्णांक_in->bInterval;
		dev_dbg(&पूर्णांकf->dev, "Found Int in endpoint at %u\n",
				data->iin_ep);
	पूर्ण

	retcode = get_capabilities(data);
	अगर (retcode)
		dev_err(&पूर्णांकf->dev, "can't read capabilities\n");

	अगर (data->iin_ep_present) अणु
		/* allocate पूर्णांक urb */
		data->iin_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!data->iin_urb) अणु
			retcode = -ENOMEM;
			जाओ error_रेजिस्टर;
		पूर्ण

		/* Protect पूर्णांकerrupt in endpoपूर्णांक data until iin_urb is मुक्तd */
		kref_get(&data->kref);

		/* allocate buffer क्रम पूर्णांकerrupt in */
		data->iin_buffer = kदो_स्मृति(data->iin_wMaxPacketSize,
					GFP_KERNEL);
		अगर (!data->iin_buffer) अणु
			retcode = -ENOMEM;
			जाओ error_रेजिस्टर;
		पूर्ण

		/* fill पूर्णांकerrupt urb */
		usb_fill_पूर्णांक_urb(data->iin_urb, data->usb_dev,
				usb_rcvपूर्णांकpipe(data->usb_dev, data->iin_ep),
				data->iin_buffer, data->iin_wMaxPacketSize,
				usbपंचांगc_पूर्णांकerrupt,
				data, data->iin_पूर्णांकerval);

		retcode = usb_submit_urb(data->iin_urb, GFP_KERNEL);
		अगर (retcode) अणु
			dev_err(&पूर्णांकf->dev, "Failed to submit iin_urb\n");
			जाओ error_रेजिस्टर;
		पूर्ण
	पूर्ण

	retcode = usb_रेजिस्टर_dev(पूर्णांकf, &usbपंचांगc_class);
	अगर (retcode) अणु
		dev_err(&पूर्णांकf->dev, "Not able to get a minor (base %u, slice default): %d\n",
			USBTMC_MINOR_BASE,
			retcode);
		जाओ error_रेजिस्टर;
	पूर्ण
	dev_dbg(&पूर्णांकf->dev, "Using minor number %d\n", पूर्णांकf->minor);

	वापस 0;

error_रेजिस्टर:
	usbपंचांगc_मुक्त_पूर्णांक(data);
err_put:
	kref_put(&data->kref, usbपंचांगc_delete);
	वापस retcode;
पूर्ण

अटल व्योम usbपंचांगc_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbपंचांगc_device_data *data  = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा list_head *elem;

	usb_deरेजिस्टर_dev(पूर्णांकf, &usbपंचांगc_class);
	mutex_lock(&data->io_mutex);
	data->zombie = 1;
	wake_up_पूर्णांकerruptible_all(&data->रुकोq);
	list_क्रम_each(elem, &data->file_list) अणु
		काष्ठा usbपंचांगc_file_data *file_data;

		file_data = list_entry(elem,
				       काष्ठा usbपंचांगc_file_data,
				       file_elem);
		usb_समाप्त_anchored_urbs(&file_data->submitted);
		usb_scuttle_anchored_urbs(&file_data->in_anchor);
	पूर्ण
	mutex_unlock(&data->io_mutex);
	usbपंचांगc_मुक्त_पूर्णांक(data);
	kref_put(&data->kref, usbपंचांगc_delete);
पूर्ण

अटल व्योम usbपंचांगc_draw_करोwn(काष्ठा usbपंचांगc_file_data *file_data)
अणु
	पूर्णांक समय;

	समय = usb_रुको_anchor_empty_समयout(&file_data->submitted, 1000);
	अगर (!समय)
		usb_समाप्त_anchored_urbs(&file_data->submitted);
	usb_scuttle_anchored_urbs(&file_data->in_anchor);
पूर्ण

अटल पूर्णांक usbपंचांगc_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usbपंचांगc_device_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा list_head *elem;

	अगर (!data)
		वापस 0;

	mutex_lock(&data->io_mutex);
	list_क्रम_each(elem, &data->file_list) अणु
		काष्ठा usbपंचांगc_file_data *file_data;

		file_data = list_entry(elem,
				       काष्ठा usbपंचांगc_file_data,
				       file_elem);
		usbपंचांगc_draw_करोwn(file_data);
	पूर्ण

	अगर (data->iin_ep_present && data->iin_urb)
		usb_समाप्त_urb(data->iin_urb);

	mutex_unlock(&data->io_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक usbपंचांगc_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbपंचांगc_device_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक retcode = 0;

	अगर (data->iin_ep_present && data->iin_urb)
		retcode = usb_submit_urb(data->iin_urb, GFP_KERNEL);
	अगर (retcode)
		dev_err(&पूर्णांकf->dev, "Failed to submit iin_urb\n");

	वापस retcode;
पूर्ण

अटल पूर्णांक usbपंचांगc_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbपंचांगc_device_data *data  = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा list_head *elem;

	अगर (!data)
		वापस 0;

	mutex_lock(&data->io_mutex);

	list_क्रम_each(elem, &data->file_list) अणु
		काष्ठा usbपंचांगc_file_data *file_data;

		file_data = list_entry(elem,
				       काष्ठा usbपंचांगc_file_data,
				       file_elem);
		usbपंचांगc_ioctl_cancel_io(file_data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbपंचांगc_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usbपंचांगc_device_data *data  = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_unlock(&data->io_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा usb_driver usbपंचांगc_driver = अणु
	.name		= "usbtmc",
	.id_table	= usbपंचांगc_devices,
	.probe		= usbपंचांगc_probe,
	.disconnect	= usbपंचांगc_disconnect,
	.suspend	= usbपंचांगc_suspend,
	.resume		= usbपंचांगc_resume,
	.pre_reset	= usbपंचांगc_pre_reset,
	.post_reset	= usbपंचांगc_post_reset,
	.dev_groups	= usbपंचांगc_groups,
पूर्ण;

module_usb_driver(usbपंचांगc_driver);

MODULE_LICENSE("GPL");
