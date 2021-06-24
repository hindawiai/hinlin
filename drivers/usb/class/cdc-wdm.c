<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cdc-wdm.c
 *
 * This driver supports USB CDC WCM Device Management.
 *
 * Copyright (c) 2007-2009 Oliver Neukum
 *
 * Some code taken from cdc-acm.c
 *
 * Released under the GPLv2.
 *
 * Many thanks to Carl Nordbeck
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/poll.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/usb/cdc-wdm.h>

#घोषणा DRIVER_AUTHOR "Oliver Neukum"
#घोषणा DRIVER_DESC "USB Abstract Control Model driver for USB WCM Device Management"

अटल स्थिर काष्ठा usb_device_id wdm_ids[] = अणु
	अणु
		.match_flags = USB_DEVICE_ID_MATCH_INT_CLASS |
				 USB_DEVICE_ID_MATCH_INT_SUBCLASS,
		.bInterfaceClass = USB_CLASS_COMM,
		.bInterfaceSubClass = USB_CDC_SUBCLASS_DMM
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (usb, wdm_ids);

#घोषणा WDM_MINOR_BASE	176


#घोषणा WDM_IN_USE		1
#घोषणा WDM_DISCONNECTING	2
#घोषणा WDM_RESULT		3
#घोषणा WDM_READ		4
#घोषणा WDM_INT_STALL		5
#घोषणा WDM_POLL_RUNNING	6
#घोषणा WDM_RESPONDING		7
#घोषणा WDM_SUSPENDING		8
#घोषणा WDM_RESETTING		9
#घोषणा WDM_OVERFLOW		10

#घोषणा WDM_MAX			16

/* we cannot रुको क्रमever at flush() */
#घोषणा WDM_FLUSH_TIMEOUT	(30 * HZ)

/* CDC-WMC r1.1 requires wMaxCommand to be "at least 256 decimal (0x100)" */
#घोषणा WDM_DEFAULT_बफ_मानE	256

अटल DEFINE_MUTEX(wdm_mutex);
अटल DEFINE_SPINLOCK(wdm_device_list_lock);
अटल LIST_HEAD(wdm_device_list);

/* --- method tables --- */

काष्ठा wdm_device अणु
	u8			*inbuf; /* buffer क्रम response */
	u8			*outbuf; /* buffer क्रम command */
	u8			*sbuf; /* buffer क्रम status */
	u8			*ubuf; /* buffer क्रम copy to user space */

	काष्ठा urb		*command;
	काष्ठा urb		*response;
	काष्ठा urb		*validity;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;
	काष्ठा usb_ctrlrequest	*orq;
	काष्ठा usb_ctrlrequest	*irq;
	spinlock_t		iuspin;

	अचिन्हित दीर्घ		flags;
	u16			bufsize;
	u16			wMaxCommand;
	u16			wMaxPacketSize;
	__le16			inum;
	पूर्णांक			reslength;
	पूर्णांक			length;
	पूर्णांक			पढ़ो;
	पूर्णांक			count;
	dma_addr_t		shandle;
	dma_addr_t		ihandle;
	काष्ठा mutex		wlock;
	काष्ठा mutex		rlock;
	रुको_queue_head_t	रुको;
	काष्ठा work_काष्ठा	rxwork;
	काष्ठा work_काष्ठा	service_outs_पूर्णांकr;
	पूर्णांक			werr;
	पूर्णांक			rerr;
	पूर्णांक                     resp_count;

	काष्ठा list_head	device_list;
	पूर्णांक			(*manage_घातer)(काष्ठा usb_पूर्णांकerface *, पूर्णांक);
पूर्ण;

अटल काष्ठा usb_driver wdm_driver;

/* वापस पूर्णांकfdata अगर we own the पूर्णांकerface, अन्यथा look up पूर्णांकf in the list */
अटल काष्ठा wdm_device *wdm_find_device(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा wdm_device *desc;

	spin_lock(&wdm_device_list_lock);
	list_क्रम_each_entry(desc, &wdm_device_list, device_list)
		अगर (desc->पूर्णांकf == पूर्णांकf)
			जाओ found;
	desc = शून्य;
found:
	spin_unlock(&wdm_device_list_lock);

	वापस desc;
पूर्ण

अटल काष्ठा wdm_device *wdm_find_device_by_minor(पूर्णांक minor)
अणु
	काष्ठा wdm_device *desc;

	spin_lock(&wdm_device_list_lock);
	list_क्रम_each_entry(desc, &wdm_device_list, device_list)
		अगर (desc->पूर्णांकf->minor == minor)
			जाओ found;
	desc = शून्य;
found:
	spin_unlock(&wdm_device_list_lock);

	वापस desc;
पूर्ण

/* --- callbacks --- */
अटल व्योम wdm_out_callback(काष्ठा urb *urb)
अणु
	काष्ठा wdm_device *desc;
	अचिन्हित दीर्घ flags;

	desc = urb->context;
	spin_lock_irqsave(&desc->iuspin, flags);
	desc->werr = urb->status;
	spin_unlock_irqrestore(&desc->iuspin, flags);
	kमुक्त(desc->outbuf);
	desc->outbuf = शून्य;
	clear_bit(WDM_IN_USE, &desc->flags);
	wake_up_all(&desc->रुको);
पूर्ण

अटल व्योम wdm_in_callback(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा wdm_device *desc = urb->context;
	पूर्णांक status = urb->status;
	पूर्णांक length = urb->actual_length;

	spin_lock_irqsave(&desc->iuspin, flags);
	clear_bit(WDM_RESPONDING, &desc->flags);

	अगर (status) अणु
		चयन (status) अणु
		हाल -ENOENT:
			dev_dbg(&desc->पूर्णांकf->dev,
				"nonzero urb status received: -ENOENT\n");
			जाओ skip_error;
		हाल -ECONNRESET:
			dev_dbg(&desc->पूर्णांकf->dev,
				"nonzero urb status received: -ECONNRESET\n");
			जाओ skip_error;
		हाल -ESHUTDOWN:
			dev_dbg(&desc->पूर्णांकf->dev,
				"nonzero urb status received: -ESHUTDOWN\n");
			जाओ skip_error;
		हाल -EPIPE:
			dev_err(&desc->पूर्णांकf->dev,
				"nonzero urb status received: -EPIPE\n");
			अवरोध;
		शेष:
			dev_err(&desc->पूर्णांकf->dev,
				"Unexpected error %d\n", status);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * only set a new error अगर there is no previous error.
	 * Errors are only cleared during पढ़ो/खोलो
	 * Aव्योम propagating -EPIPE (stall) to userspace since it is
	 * better handled as an empty पढ़ो
	 */
	अगर (desc->rerr == 0 && status != -EPIPE)
		desc->rerr = status;

	अगर (length + desc->length > desc->wMaxCommand) अणु
		/* The buffer would overflow */
		set_bit(WDM_OVERFLOW, &desc->flags);
	पूर्ण अन्यथा अणु
		/* we may alपढ़ोy be in overflow */
		अगर (!test_bit(WDM_OVERFLOW, &desc->flags)) अणु
			स_हटाओ(desc->ubuf + desc->length, desc->inbuf, length);
			desc->length += length;
			desc->reslength = length;
		पूर्ण
	पूर्ण
skip_error:

	अगर (desc->rerr) अणु
		/*
		 * Since there was an error, userspace may decide to not पढ़ो
		 * any data after poll'ing.
		 * We should respond to further attempts from the device to send
		 * data, so that we can get unstuck.
		 */
		schedule_work(&desc->service_outs_पूर्णांकr);
	पूर्ण अन्यथा अणु
		set_bit(WDM_READ, &desc->flags);
		wake_up(&desc->रुको);
	पूर्ण
	spin_unlock_irqrestore(&desc->iuspin, flags);
पूर्ण

अटल व्योम wdm_पूर्णांक_callback(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;
	पूर्णांक responding;
	पूर्णांक status = urb->status;
	काष्ठा wdm_device *desc;
	काष्ठा usb_cdc_notअगरication *dr;

	desc = urb->context;
	dr = (काष्ठा usb_cdc_notअगरication *)desc->sbuf;

	अगर (status) अणु
		चयन (status) अणु
		हाल -ESHUTDOWN:
		हाल -ENOENT:
		हाल -ECONNRESET:
			वापस; /* unplug */
		हाल -EPIPE:
			set_bit(WDM_INT_STALL, &desc->flags);
			dev_err(&desc->पूर्णांकf->dev, "Stall on int endpoint\n");
			जाओ sw; /* halt is cleared in work */
		शेष:
			dev_err(&desc->पूर्णांकf->dev,
				"nonzero urb status received: %d\n", status);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (urb->actual_length < माप(काष्ठा usb_cdc_notअगरication)) अणु
		dev_err(&desc->पूर्णांकf->dev, "wdm_int_callback - %d bytes\n",
			urb->actual_length);
		जाओ निकास;
	पूर्ण

	चयन (dr->bNotअगरicationType) अणु
	हाल USB_CDC_NOTIFY_RESPONSE_AVAILABLE:
		dev_dbg(&desc->पूर्णांकf->dev,
			"NOTIFY_RESPONSE_AVAILABLE received: index %d len %d\n",
			le16_to_cpu(dr->wIndex), le16_to_cpu(dr->wLength));
		अवरोध;

	हाल USB_CDC_NOTIFY_NETWORK_CONNECTION:

		dev_dbg(&desc->पूर्णांकf->dev,
			"NOTIFY_NETWORK_CONNECTION %s network\n",
			dr->wValue ? "connected to" : "disconnected from");
		जाओ निकास;
	हाल USB_CDC_NOTIFY_SPEED_CHANGE:
		dev_dbg(&desc->पूर्णांकf->dev, "SPEED_CHANGE received (len %u)\n",
			urb->actual_length);
		जाओ निकास;
	शेष:
		clear_bit(WDM_POLL_RUNNING, &desc->flags);
		dev_err(&desc->पूर्णांकf->dev,
			"unknown notification %d received: index %d len %d\n",
			dr->bNotअगरicationType,
			le16_to_cpu(dr->wIndex),
			le16_to_cpu(dr->wLength));
		जाओ निकास;
	पूर्ण

	spin_lock_irqsave(&desc->iuspin, flags);
	responding = test_and_set_bit(WDM_RESPONDING, &desc->flags);
	अगर (!desc->resp_count++ && !responding
		&& !test_bit(WDM_DISCONNECTING, &desc->flags)
		&& !test_bit(WDM_SUSPENDING, &desc->flags)) अणु
		rv = usb_submit_urb(desc->response, GFP_ATOMIC);
		dev_dbg(&desc->पूर्णांकf->dev, "submit response URB %d\n", rv);
	पूर्ण
	spin_unlock_irqrestore(&desc->iuspin, flags);
	अगर (rv < 0) अणु
		clear_bit(WDM_RESPONDING, &desc->flags);
		अगर (rv == -EPERM)
			वापस;
		अगर (rv == -ENOMEM) अणु
sw:
			rv = schedule_work(&desc->rxwork);
			अगर (rv)
				dev_err(&desc->पूर्णांकf->dev,
					"Cannot schedule work\n");
		पूर्ण
	पूर्ण
निकास:
	rv = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (rv)
		dev_err(&desc->पूर्णांकf->dev,
			"%s - usb_submit_urb failed with result %d\n",
			__func__, rv);

पूर्ण

अटल व्योम poison_urbs(काष्ठा wdm_device *desc)
अणु
	/* the order here is essential */
	usb_poison_urb(desc->command);
	usb_poison_urb(desc->validity);
	usb_poison_urb(desc->response);
पूर्ण

अटल व्योम unpoison_urbs(काष्ठा wdm_device *desc)
अणु
	/*
	 *  the order here is not essential
	 *  it is symmetrical just to be nice
	 */
	usb_unpoison_urb(desc->response);
	usb_unpoison_urb(desc->validity);
	usb_unpoison_urb(desc->command);
पूर्ण

अटल व्योम मुक्त_urbs(काष्ठा wdm_device *desc)
अणु
	usb_मुक्त_urb(desc->validity);
	usb_मुक्त_urb(desc->response);
	usb_मुक्त_urb(desc->command);
पूर्ण

अटल व्योम cleanup(काष्ठा wdm_device *desc)
अणु
	kमुक्त(desc->sbuf);
	kमुक्त(desc->inbuf);
	kमुक्त(desc->orq);
	kमुक्त(desc->irq);
	kमुक्त(desc->ubuf);
	मुक्त_urbs(desc);
	kमुक्त(desc);
पूर्ण

अटल sमाप_प्रकार wdm_ग_लिखो
(काष्ठा file *file, स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	u8 *buf;
	पूर्णांक rv = -EMSGSIZE, r, we;
	काष्ठा wdm_device *desc = file->निजी_data;
	काष्ठा usb_ctrlrequest *req;

	अगर (count > desc->wMaxCommand)
		count = desc->wMaxCommand;

	spin_lock_irq(&desc->iuspin);
	we = desc->werr;
	desc->werr = 0;
	spin_unlock_irq(&desc->iuspin);
	अगर (we < 0)
		वापस usb_translate_errors(we);

	buf = memdup_user(buffer, count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	/* concurrent ग_लिखोs and disconnect */
	r = mutex_lock_पूर्णांकerruptible(&desc->wlock);
	rv = -ERESTARTSYS;
	अगर (r)
		जाओ out_मुक्त_mem;

	अगर (test_bit(WDM_DISCONNECTING, &desc->flags)) अणु
		rv = -ENODEV;
		जाओ out_मुक्त_mem_lock;
	पूर्ण

	r = usb_स्वतःpm_get_पूर्णांकerface(desc->पूर्णांकf);
	अगर (r < 0) अणु
		rv = usb_translate_errors(r);
		जाओ out_मुक्त_mem_lock;
	पूर्ण

	अगर (!(file->f_flags & O_NONBLOCK))
		r = रुको_event_पूर्णांकerruptible(desc->रुको, !test_bit(WDM_IN_USE,
								&desc->flags));
	अन्यथा
		अगर (test_bit(WDM_IN_USE, &desc->flags))
			r = -EAGAIN;

	अगर (test_bit(WDM_RESETTING, &desc->flags))
		r = -EIO;

	अगर (test_bit(WDM_DISCONNECTING, &desc->flags))
		r = -ENODEV;

	अगर (r < 0) अणु
		rv = r;
		जाओ out_मुक्त_mem_pm;
	पूर्ण

	req = desc->orq;
	usb_fill_control_urb(
		desc->command,
		पूर्णांकerface_to_usbdev(desc->पूर्णांकf),
		/* using common endpoपूर्णांक 0 */
		usb_sndctrlpipe(पूर्णांकerface_to_usbdev(desc->पूर्णांकf), 0),
		(अचिन्हित अक्षर *)req,
		buf,
		count,
		wdm_out_callback,
		desc
	);

	req->bRequestType = (USB_सूची_OUT | USB_TYPE_CLASS |
			     USB_RECIP_INTERFACE);
	req->bRequest = USB_CDC_SEND_ENCAPSULATED_COMMAND;
	req->wValue = 0;
	req->wIndex = desc->inum; /* alपढ़ोy converted */
	req->wLength = cpu_to_le16(count);
	set_bit(WDM_IN_USE, &desc->flags);
	desc->outbuf = buf;

	rv = usb_submit_urb(desc->command, GFP_KERNEL);
	अगर (rv < 0) अणु
		desc->outbuf = शून्य;
		clear_bit(WDM_IN_USE, &desc->flags);
		wake_up_all(&desc->रुको); /* क्रम wdm_रुको_क्रम_response() */
		dev_err(&desc->पूर्णांकf->dev, "Tx URB error: %d\n", rv);
		rv = usb_translate_errors(rv);
		जाओ out_मुक्त_mem_pm;
	पूर्ण अन्यथा अणु
		dev_dbg(&desc->पूर्णांकf->dev, "Tx URB has been submitted index=%d\n",
			le16_to_cpu(req->wIndex));
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(desc->पूर्णांकf);
	mutex_unlock(&desc->wlock);
	वापस count;

out_मुक्त_mem_pm:
	usb_स्वतःpm_put_पूर्णांकerface(desc->पूर्णांकf);
out_मुक्त_mem_lock:
	mutex_unlock(&desc->wlock);
out_मुक्त_mem:
	kमुक्त(buf);
	वापस rv;
पूर्ण

/*
 * Submit the पढ़ो urb अगर resp_count is non-zero.
 *
 * Called with desc->iuspin locked
 */
अटल पूर्णांक service_outstanding_पूर्णांकerrupt(काष्ठा wdm_device *desc)
अणु
	पूर्णांक rv = 0;

	/* submit पढ़ो urb only अगर the device is रुकोing क्रम it */
	अगर (!desc->resp_count || !--desc->resp_count)
		जाओ out;

	अगर (test_bit(WDM_DISCONNECTING, &desc->flags)) अणु
		rv = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (test_bit(WDM_RESETTING, &desc->flags)) अणु
		rv = -EIO;
		जाओ out;
	पूर्ण

	set_bit(WDM_RESPONDING, &desc->flags);
	spin_unlock_irq(&desc->iuspin);
	rv = usb_submit_urb(desc->response, GFP_KERNEL);
	spin_lock_irq(&desc->iuspin);
	अगर (rv) अणु
		अगर (!test_bit(WDM_DISCONNECTING, &desc->flags))
			dev_err(&desc->पूर्णांकf->dev,
				"usb_submit_urb failed with result %d\n", rv);

		/* make sure the next notअगरication trigger a submit */
		clear_bit(WDM_RESPONDING, &desc->flags);
		desc->resp_count = 0;
	पूर्ण
out:
	वापस rv;
पूर्ण

अटल sमाप_प्रकार wdm_पढ़ो
(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rv, cntr;
	पूर्णांक i = 0;
	काष्ठा wdm_device *desc = file->निजी_data;


	rv = mutex_lock_पूर्णांकerruptible(&desc->rlock); /*concurrent पढ़ोs */
	अगर (rv < 0)
		वापस -ERESTARTSYS;

	cntr = READ_ONCE(desc->length);
	अगर (cntr == 0) अणु
		desc->पढ़ो = 0;
retry:
		अगर (test_bit(WDM_DISCONNECTING, &desc->flags)) अणु
			rv = -ENODEV;
			जाओ err;
		पूर्ण
		अगर (test_bit(WDM_OVERFLOW, &desc->flags)) अणु
			clear_bit(WDM_OVERFLOW, &desc->flags);
			rv = -ENOBUFS;
			जाओ err;
		पूर्ण
		i++;
		अगर (file->f_flags & O_NONBLOCK) अणु
			अगर (!test_bit(WDM_READ, &desc->flags)) अणु
				rv = -EAGAIN;
				जाओ err;
			पूर्ण
			rv = 0;
		पूर्ण अन्यथा अणु
			rv = रुको_event_पूर्णांकerruptible(desc->रुको,
				test_bit(WDM_READ, &desc->flags));
		पूर्ण

		/* may have happened जबतक we slept */
		अगर (test_bit(WDM_DISCONNECTING, &desc->flags)) अणु
			rv = -ENODEV;
			जाओ err;
		पूर्ण
		अगर (test_bit(WDM_RESETTING, &desc->flags)) अणु
			rv = -EIO;
			जाओ err;
		पूर्ण
		usb_mark_last_busy(पूर्णांकerface_to_usbdev(desc->पूर्णांकf));
		अगर (rv < 0) अणु
			rv = -ERESTARTSYS;
			जाओ err;
		पूर्ण

		spin_lock_irq(&desc->iuspin);

		अगर (desc->rerr) अणु /* पढ़ो completed, error happened */
			rv = usb_translate_errors(desc->rerr);
			desc->rerr = 0;
			spin_unlock_irq(&desc->iuspin);
			जाओ err;
		पूर्ण
		/*
		 * recheck whether we've lost the race
		 * against the completion handler
		 */
		अगर (!test_bit(WDM_READ, &desc->flags)) अणु /* lost race */
			spin_unlock_irq(&desc->iuspin);
			जाओ retry;
		पूर्ण

		अगर (!desc->reslength) अणु /* zero length पढ़ो */
			dev_dbg(&desc->पूर्णांकf->dev, "zero length - clearing WDM_READ\n");
			clear_bit(WDM_READ, &desc->flags);
			rv = service_outstanding_पूर्णांकerrupt(desc);
			spin_unlock_irq(&desc->iuspin);
			अगर (rv < 0)
				जाओ err;
			जाओ retry;
		पूर्ण
		cntr = desc->length;
		spin_unlock_irq(&desc->iuspin);
	पूर्ण

	अगर (cntr > count)
		cntr = count;
	rv = copy_to_user(buffer, desc->ubuf, cntr);
	अगर (rv > 0) अणु
		rv = -EFAULT;
		जाओ err;
	पूर्ण

	spin_lock_irq(&desc->iuspin);

	क्रम (i = 0; i < desc->length - cntr; i++)
		desc->ubuf[i] = desc->ubuf[i + cntr];

	desc->length -= cntr;
	/* in हाल we had outstanding data */
	अगर (!desc->length) अणु
		clear_bit(WDM_READ, &desc->flags);
		service_outstanding_पूर्णांकerrupt(desc);
	पूर्ण
	spin_unlock_irq(&desc->iuspin);
	rv = cntr;

err:
	mutex_unlock(&desc->rlock);
	वापस rv;
पूर्ण

अटल पूर्णांक wdm_रुको_क्रम_response(काष्ठा file *file, दीर्घ समयout)
अणु
	काष्ठा wdm_device *desc = file->निजी_data;
	दीर्घ rv; /* Use दीर्घ here because (पूर्णांक) MAX_SCHEDULE_TIMEOUT < 0. */

	/*
	 * Needs both flags. We cannot करो with one because resetting it would
	 * cause a race with ग_लिखो() yet we need to संकेत a disconnect.
	 */
	rv = रुको_event_पूर्णांकerruptible_समयout(desc->रुको,
			      !test_bit(WDM_IN_USE, &desc->flags) ||
			      test_bit(WDM_DISCONNECTING, &desc->flags),
			      समयout);

	/*
	 * To report the correct error. This is best efक्रमt.
	 * We are inevitably racing with the hardware.
	 */
	अगर (test_bit(WDM_DISCONNECTING, &desc->flags))
		वापस -ENODEV;
	अगर (!rv)
		वापस -EIO;
	अगर (rv < 0)
		वापस -EINTR;

	spin_lock_irq(&desc->iuspin);
	rv = desc->werr;
	desc->werr = 0;
	spin_unlock_irq(&desc->iuspin);

	वापस usb_translate_errors(rv);

पूर्ण

/*
 * You need to send a संकेत when you react to malicious or defective hardware.
 * Also, करोn't पात when fsync() वापसed -EINVAL, क्रम older kernels which करो
 * not implement wdm_flush() will वापस -EINVAL.
 */
अटल पूर्णांक wdm_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	वापस wdm_रुको_क्रम_response(file, MAX_SCHEDULE_TIMEOUT);
पूर्ण

/*
 * Same with wdm_fsync(), except it uses finite समयout in order to react to
 * malicious or defective hardware which ceased communication after बंद() was
 * implicitly called due to process termination.
 */
अटल पूर्णांक wdm_flush(काष्ठा file *file, fl_owner_t id)
अणु
	वापस wdm_रुको_क्रम_response(file, WDM_FLUSH_TIMEOUT);
पूर्ण

अटल __poll_t wdm_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा wdm_device *desc = file->निजी_data;
	अचिन्हित दीर्घ flags;
	__poll_t mask = 0;

	spin_lock_irqsave(&desc->iuspin, flags);
	अगर (test_bit(WDM_DISCONNECTING, &desc->flags)) अणु
		mask = EPOLLHUP | EPOLLERR;
		spin_unlock_irqrestore(&desc->iuspin, flags);
		जाओ desc_out;
	पूर्ण
	अगर (test_bit(WDM_READ, &desc->flags))
		mask = EPOLLIN | EPOLLRDNORM;
	अगर (desc->rerr || desc->werr)
		mask |= EPOLLERR;
	अगर (!test_bit(WDM_IN_USE, &desc->flags))
		mask |= EPOLLOUT | EPOLLWRNORM;
	spin_unlock_irqrestore(&desc->iuspin, flags);

	poll_रुको(file, &desc->रुको, रुको);

desc_out:
	वापस mask;
पूर्ण

अटल पूर्णांक wdm_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक minor = iminor(inode);
	पूर्णांक rv = -ENODEV;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा wdm_device *desc;

	mutex_lock(&wdm_mutex);
	desc = wdm_find_device_by_minor(minor);
	अगर (!desc)
		जाओ out;

	पूर्णांकf = desc->पूर्णांकf;
	अगर (test_bit(WDM_DISCONNECTING, &desc->flags))
		जाओ out;
	file->निजी_data = desc;

	rv = usb_स्वतःpm_get_पूर्णांकerface(desc->पूर्णांकf);
	अगर (rv < 0) अणु
		dev_err(&desc->पूर्णांकf->dev, "Error autopm - %d\n", rv);
		जाओ out;
	पूर्ण

	/* using ग_लिखो lock to protect desc->count */
	mutex_lock(&desc->wlock);
	अगर (!desc->count++) अणु
		desc->werr = 0;
		desc->rerr = 0;
		rv = usb_submit_urb(desc->validity, GFP_KERNEL);
		अगर (rv < 0) अणु
			desc->count--;
			dev_err(&desc->पूर्णांकf->dev,
				"Error submitting int urb - %d\n", rv);
			rv = usb_translate_errors(rv);
		पूर्ण
	पूर्ण अन्यथा अणु
		rv = 0;
	पूर्ण
	mutex_unlock(&desc->wlock);
	अगर (desc->count == 1)
		desc->manage_घातer(पूर्णांकf, 1);
	usb_स्वतःpm_put_पूर्णांकerface(desc->पूर्णांकf);
out:
	mutex_unlock(&wdm_mutex);
	वापस rv;
पूर्ण

अटल पूर्णांक wdm_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा wdm_device *desc = file->निजी_data;

	mutex_lock(&wdm_mutex);

	/* using ग_लिखो lock to protect desc->count */
	mutex_lock(&desc->wlock);
	desc->count--;
	mutex_unlock(&desc->wlock);

	अगर (!desc->count) अणु
		अगर (!test_bit(WDM_DISCONNECTING, &desc->flags)) अणु
			dev_dbg(&desc->पूर्णांकf->dev, "wdm_release: cleanup\n");
			poison_urbs(desc);
			spin_lock_irq(&desc->iuspin);
			desc->resp_count = 0;
			spin_unlock_irq(&desc->iuspin);
			desc->manage_घातer(desc->पूर्णांकf, 0);
			unpoison_urbs(desc);
		पूर्ण अन्यथा अणु
			/* must aव्योम dev_prपूर्णांकk here as desc->पूर्णांकf is invalid */
			pr_debug(KBUILD_MODNAME " %s: device gone - cleaning up\n", __func__);
			cleanup(desc);
		पूर्ण
	पूर्ण
	mutex_unlock(&wdm_mutex);
	वापस 0;
पूर्ण

अटल दीर्घ wdm_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा wdm_device *desc = file->निजी_data;
	पूर्णांक rv = 0;

	चयन (cmd) अणु
	हाल IOCTL_WDM_MAX_COMMAND:
		अगर (copy_to_user((व्योम __user *)arg, &desc->wMaxCommand, माप(desc->wMaxCommand)))
			rv = -EFAULT;
		अवरोध;
	शेष:
		rv = -ENOTTY;
	पूर्ण
	वापस rv;
पूर्ण

अटल स्थिर काष्ठा file_operations wdm_fops = अणु
	.owner =	THIS_MODULE,
	.पढ़ो =		wdm_पढ़ो,
	.ग_लिखो =	wdm_ग_लिखो,
	.fsync =	wdm_fsync,
	.खोलो =		wdm_खोलो,
	.flush =	wdm_flush,
	.release =	wdm_release,
	.poll =		wdm_poll,
	.unlocked_ioctl = wdm_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.llseek =	noop_llseek,
पूर्ण;

अटल काष्ठा usb_class_driver wdm_class = अणु
	.name =		"cdc-wdm%d",
	.fops =		&wdm_fops,
	.minor_base =	WDM_MINOR_BASE,
पूर्ण;

/* --- error handling --- */
अटल व्योम wdm_rxwork(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wdm_device *desc = container_of(work, काष्ठा wdm_device, rxwork);
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;
	पूर्णांक responding;

	spin_lock_irqsave(&desc->iuspin, flags);
	अगर (test_bit(WDM_DISCONNECTING, &desc->flags)) अणु
		spin_unlock_irqrestore(&desc->iuspin, flags);
	पूर्ण अन्यथा अणु
		responding = test_and_set_bit(WDM_RESPONDING, &desc->flags);
		spin_unlock_irqrestore(&desc->iuspin, flags);
		अगर (!responding)
			rv = usb_submit_urb(desc->response, GFP_KERNEL);
		अगर (rv < 0 && rv != -EPERM) अणु
			spin_lock_irqsave(&desc->iuspin, flags);
			clear_bit(WDM_RESPONDING, &desc->flags);
			अगर (!test_bit(WDM_DISCONNECTING, &desc->flags))
				schedule_work(&desc->rxwork);
			spin_unlock_irqrestore(&desc->iuspin, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम service_पूर्णांकerrupt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wdm_device *desc;

	desc = container_of(work, काष्ठा wdm_device, service_outs_पूर्णांकr);

	spin_lock_irq(&desc->iuspin);
	service_outstanding_पूर्णांकerrupt(desc);
	अगर (!desc->resp_count) अणु
		set_bit(WDM_READ, &desc->flags);
		wake_up(&desc->रुको);
	पूर्ण
	spin_unlock_irq(&desc->iuspin);
पूर्ण

/* --- hotplug --- */

अटल पूर्णांक wdm_create(काष्ठा usb_पूर्णांकerface *पूर्णांकf, काष्ठा usb_endpoपूर्णांक_descriptor *ep,
		u16 bufsize, पूर्णांक (*manage_घातer)(काष्ठा usb_पूर्णांकerface *, पूर्णांक))
अणु
	पूर्णांक rv = -ENOMEM;
	काष्ठा wdm_device *desc;

	desc = kzalloc(माप(काष्ठा wdm_device), GFP_KERNEL);
	अगर (!desc)
		जाओ out;
	INIT_LIST_HEAD(&desc->device_list);
	mutex_init(&desc->rlock);
	mutex_init(&desc->wlock);
	spin_lock_init(&desc->iuspin);
	init_रुकोqueue_head(&desc->रुको);
	desc->wMaxCommand = bufsize;
	/* this will be expanded and needed in hardware endianness */
	desc->inum = cpu_to_le16((u16)पूर्णांकf->cur_altsetting->desc.bInterfaceNumber);
	desc->पूर्णांकf = पूर्णांकf;
	INIT_WORK(&desc->rxwork, wdm_rxwork);
	INIT_WORK(&desc->service_outs_पूर्णांकr, service_पूर्णांकerrupt_work);

	rv = -EINVAL;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(ep))
		जाओ err;

	desc->wMaxPacketSize = usb_endpoपूर्णांक_maxp(ep);

	desc->orq = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_KERNEL);
	अगर (!desc->orq)
		जाओ err;
	desc->irq = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_KERNEL);
	अगर (!desc->irq)
		जाओ err;

	desc->validity = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!desc->validity)
		जाओ err;

	desc->response = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!desc->response)
		जाओ err;

	desc->command = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!desc->command)
		जाओ err;

	desc->ubuf = kदो_स्मृति(desc->wMaxCommand, GFP_KERNEL);
	अगर (!desc->ubuf)
		जाओ err;

	desc->sbuf = kदो_स्मृति(desc->wMaxPacketSize, GFP_KERNEL);
	अगर (!desc->sbuf)
		जाओ err;

	desc->inbuf = kदो_स्मृति(desc->wMaxCommand, GFP_KERNEL);
	अगर (!desc->inbuf)
		जाओ err;

	usb_fill_पूर्णांक_urb(
		desc->validity,
		पूर्णांकerface_to_usbdev(पूर्णांकf),
		usb_rcvपूर्णांकpipe(पूर्णांकerface_to_usbdev(पूर्णांकf), ep->bEndpoपूर्णांकAddress),
		desc->sbuf,
		desc->wMaxPacketSize,
		wdm_पूर्णांक_callback,
		desc,
		ep->bInterval
	);

	desc->irq->bRequestType = (USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE);
	desc->irq->bRequest = USB_CDC_GET_ENCAPSULATED_RESPONSE;
	desc->irq->wValue = 0;
	desc->irq->wIndex = desc->inum; /* alपढ़ोy converted */
	desc->irq->wLength = cpu_to_le16(desc->wMaxCommand);

	usb_fill_control_urb(
		desc->response,
		पूर्णांकerface_to_usbdev(पूर्णांकf),
		/* using common endpoपूर्णांक 0 */
		usb_rcvctrlpipe(पूर्णांकerface_to_usbdev(desc->पूर्णांकf), 0),
		(अचिन्हित अक्षर *)desc->irq,
		desc->inbuf,
		desc->wMaxCommand,
		wdm_in_callback,
		desc
	);

	desc->manage_घातer = manage_घातer;

	spin_lock(&wdm_device_list_lock);
	list_add(&desc->device_list, &wdm_device_list);
	spin_unlock(&wdm_device_list_lock);

	rv = usb_रेजिस्टर_dev(पूर्णांकf, &wdm_class);
	अगर (rv < 0)
		जाओ err;
	अन्यथा
		dev_info(&पूर्णांकf->dev, "%s: USB WDM device\n", dev_name(पूर्णांकf->usb_dev));
out:
	वापस rv;
err:
	spin_lock(&wdm_device_list_lock);
	list_del(&desc->device_list);
	spin_unlock(&wdm_device_list_lock);
	cleanup(desc);
	वापस rv;
पूर्ण

अटल पूर्णांक wdm_manage_घातer(काष्ठा usb_पूर्णांकerface *पूर्णांकf, पूर्णांक on)
अणु
	/* need स्वतःpm_get/put here to ensure the usbcore sees the new value */
	पूर्णांक rv = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);

	पूर्णांकf->needs_remote_wakeup = on;
	अगर (!rv)
		usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);
	वापस 0;
पूर्ण

अटल पूर्णांक wdm_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक rv = -EINVAL;
	काष्ठा usb_host_पूर्णांकerface *अगरace;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	काष्ठा usb_cdc_parsed_header hdr;
	u8 *buffer = पूर्णांकf->altsetting->extra;
	पूर्णांक buflen = पूर्णांकf->altsetting->extralen;
	u16 maxcom = WDM_DEFAULT_बफ_मानE;

	अगर (!buffer)
		जाओ err;

	cdc_parse_cdc_header(&hdr, पूर्णांकf, buffer, buflen);

	अगर (hdr.usb_cdc_dmm_desc)
		maxcom = le16_to_cpu(hdr.usb_cdc_dmm_desc->wMaxCommand);

	अगरace = पूर्णांकf->cur_altsetting;
	अगर (अगरace->desc.bNumEndpoपूर्णांकs != 1)
		जाओ err;
	ep = &अगरace->endpoपूर्णांक[0].desc;

	rv = wdm_create(पूर्णांकf, ep, maxcom, &wdm_manage_घातer);

err:
	वापस rv;
पूर्ण

/**
 * usb_cdc_wdm_रेजिस्टर - रेजिस्टर a WDM subdriver
 * @पूर्णांकf: usb पूर्णांकerface the subdriver will associate with
 * @ep: पूर्णांकerrupt endpoपूर्णांक to monitor क्रम notअगरications
 * @bufsize: maximum message size to support क्रम पढ़ो/ग_लिखो
 * @manage_घातer: call-back invoked during खोलो and release to
 *                manage the device's घातer
 * Create WDM usb class अक्षरacter device and associate it with पूर्णांकf
 * without binding, allowing another driver to manage the पूर्णांकerface.
 *
 * The subdriver will manage the given पूर्णांकerrupt endpoपूर्णांक exclusively
 * and will issue control requests referring to the given पूर्णांकf. It
 * will otherwise aव्योम पूर्णांकerferring, and in particular not करो
 * usb_set_पूर्णांकfdata/usb_get_पूर्णांकfdata on पूर्णांकf.
 *
 * The वापस value is a poपूर्णांकer to the subdriver's काष्ठा usb_driver.
 * The रेजिस्टरing driver is responsible क्रम calling this subdriver's
 * disconnect, suspend, resume, pre_reset and post_reset methods from
 * its own.
 */
काष्ठा usb_driver *usb_cdc_wdm_रेजिस्टर(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					काष्ठा usb_endpoपूर्णांक_descriptor *ep,
					पूर्णांक bufsize,
					पूर्णांक (*manage_घातer)(काष्ठा usb_पूर्णांकerface *, पूर्णांक))
अणु
	पूर्णांक rv;

	rv = wdm_create(पूर्णांकf, ep, bufsize, manage_घातer);
	अगर (rv < 0)
		जाओ err;

	वापस &wdm_driver;
err:
	वापस ERR_PTR(rv);
पूर्ण
EXPORT_SYMBOL(usb_cdc_wdm_रेजिस्टर);

अटल व्योम wdm_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा wdm_device *desc;
	अचिन्हित दीर्घ flags;

	usb_deरेजिस्टर_dev(पूर्णांकf, &wdm_class);
	desc = wdm_find_device(पूर्णांकf);
	mutex_lock(&wdm_mutex);

	/* the spinlock makes sure no new urbs are generated in the callbacks */
	spin_lock_irqsave(&desc->iuspin, flags);
	set_bit(WDM_DISCONNECTING, &desc->flags);
	set_bit(WDM_READ, &desc->flags);
	spin_unlock_irqrestore(&desc->iuspin, flags);
	wake_up_all(&desc->रुको);
	mutex_lock(&desc->rlock);
	mutex_lock(&desc->wlock);
	poison_urbs(desc);
	cancel_work_sync(&desc->rxwork);
	cancel_work_sync(&desc->service_outs_पूर्णांकr);
	mutex_unlock(&desc->wlock);
	mutex_unlock(&desc->rlock);

	/* the desc->पूर्णांकf poपूर्णांकer used as list key is now invalid */
	spin_lock(&wdm_device_list_lock);
	list_del(&desc->device_list);
	spin_unlock(&wdm_device_list_lock);

	अगर (!desc->count)
		cleanup(desc);
	अन्यथा
		dev_dbg(&पूर्णांकf->dev, "%d open files - postponing cleanup\n", desc->count);
	mutex_unlock(&wdm_mutex);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wdm_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा wdm_device *desc = wdm_find_device(पूर्णांकf);
	पूर्णांक rv = 0;

	dev_dbg(&desc->पूर्णांकf->dev, "wdm%d_suspend\n", पूर्णांकf->minor);

	/* अगर this is an स्वतःsuspend the caller करोes the locking */
	अगर (!PMSG_IS_AUTO(message)) अणु
		mutex_lock(&desc->rlock);
		mutex_lock(&desc->wlock);
	पूर्ण
	spin_lock_irq(&desc->iuspin);

	अगर (PMSG_IS_AUTO(message) &&
			(test_bit(WDM_IN_USE, &desc->flags)
			|| test_bit(WDM_RESPONDING, &desc->flags))) अणु
		spin_unlock_irq(&desc->iuspin);
		rv = -EBUSY;
	पूर्ण अन्यथा अणु

		set_bit(WDM_SUSPENDING, &desc->flags);
		spin_unlock_irq(&desc->iuspin);
		/* callback submits work - order is essential */
		poison_urbs(desc);
		cancel_work_sync(&desc->rxwork);
		cancel_work_sync(&desc->service_outs_पूर्णांकr);
		unpoison_urbs(desc);
	पूर्ण
	अगर (!PMSG_IS_AUTO(message)) अणु
		mutex_unlock(&desc->wlock);
		mutex_unlock(&desc->rlock);
	पूर्ण

	वापस rv;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक recover_from_urb_loss(काष्ठा wdm_device *desc)
अणु
	पूर्णांक rv = 0;

	अगर (desc->count) अणु
		rv = usb_submit_urb(desc->validity, GFP_NOIO);
		अगर (rv < 0)
			dev_err(&desc->पूर्णांकf->dev,
				"Error resume submitting int urb - %d\n", rv);
	पूर्ण
	वापस rv;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wdm_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा wdm_device *desc = wdm_find_device(पूर्णांकf);
	पूर्णांक rv;

	dev_dbg(&desc->पूर्णांकf->dev, "wdm%d_resume\n", पूर्णांकf->minor);

	clear_bit(WDM_SUSPENDING, &desc->flags);
	rv = recover_from_urb_loss(desc);

	वापस rv;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक wdm_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा wdm_device *desc = wdm_find_device(पूर्णांकf);

	/*
	 * we notअगरy everybody using poll of
	 * an exceptional situation
	 * must be करोne beक्रमe recovery lest a spontaneous
	 * message from the device is lost
	 */
	spin_lock_irq(&desc->iuspin);
	set_bit(WDM_RESETTING, &desc->flags);	/* inक्रमm पढ़ो/ग_लिखो */
	set_bit(WDM_READ, &desc->flags);	/* unblock पढ़ो */
	clear_bit(WDM_IN_USE, &desc->flags);	/* unblock ग_लिखो */
	desc->rerr = -EINTR;
	spin_unlock_irq(&desc->iuspin);
	wake_up_all(&desc->रुको);
	mutex_lock(&desc->rlock);
	mutex_lock(&desc->wlock);
	poison_urbs(desc);
	cancel_work_sync(&desc->rxwork);
	cancel_work_sync(&desc->service_outs_पूर्णांकr);
	वापस 0;
पूर्ण

अटल पूर्णांक wdm_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा wdm_device *desc = wdm_find_device(पूर्णांकf);
	पूर्णांक rv;

	unpoison_urbs(desc);
	clear_bit(WDM_OVERFLOW, &desc->flags);
	clear_bit(WDM_RESETTING, &desc->flags);
	rv = recover_from_urb_loss(desc);
	mutex_unlock(&desc->wlock);
	mutex_unlock(&desc->rlock);
	वापस rv;
पूर्ण

अटल काष्ठा usb_driver wdm_driver = अणु
	.name =		"cdc_wdm",
	.probe =	wdm_probe,
	.disconnect =	wdm_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend =	wdm_suspend,
	.resume =	wdm_resume,
	.reset_resume =	wdm_resume,
#पूर्ण_अगर
	.pre_reset =	wdm_pre_reset,
	.post_reset =	wdm_post_reset,
	.id_table =	wdm_ids,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(wdm_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
