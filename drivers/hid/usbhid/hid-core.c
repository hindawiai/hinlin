<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  USB HID support क्रम Linux
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2007-2008 Oliver Neukum
 *  Copyright (c) 2006-2010 Jiri Kosina
 */

/*
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/input.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/माला.स>

#समावेश <linux/usb.h>

#समावेश <linux/hid.h>
#समावेश <linux/hiddev.h>
#समावेश <linux/hid-debug.h>
#समावेश <linux/hidraw.h>
#समावेश "usbhid.h"

/*
 * Version Inक्रमmation
 */

#घोषणा DRIVER_DESC "USB HID core driver"

/*
 * Module parameters.
 */

अटल अचिन्हित पूर्णांक hid_mousepoll_पूर्णांकerval;
module_param_named(mousepoll, hid_mousepoll_पूर्णांकerval, uपूर्णांक, 0644);
MODULE_PARM_DESC(mousepoll, "Polling interval of mice");

अटल अचिन्हित पूर्णांक hid_jspoll_पूर्णांकerval;
module_param_named(jspoll, hid_jspoll_पूर्णांकerval, uपूर्णांक, 0644);
MODULE_PARM_DESC(jspoll, "Polling interval of joysticks");

अटल अचिन्हित पूर्णांक hid_kbpoll_पूर्णांकerval;
module_param_named(kbpoll, hid_kbpoll_पूर्णांकerval, uपूर्णांक, 0644);
MODULE_PARM_DESC(kbpoll, "Polling interval of keyboards");

अटल अचिन्हित पूर्णांक ignoreled;
module_param_named(ignoreled, ignoreled, uपूर्णांक, 0644);
MODULE_PARM_DESC(ignoreled, "Autosuspend with active leds");

/* Quirks specअगरied at module load समय */
अटल अक्षर *quirks_param[MAX_USBHID_BOOT_QUIRKS];
module_param_array_named(quirks, quirks_param, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(quirks, "Add/modify USB HID quirks by specifying "
		" quirks=vendorID:productID:quirks"
		" where vendorID, productID, and quirks are all in"
		" 0x-prefixed hex");
/*
 * Input submission and I/O error handler.
 */
अटल व्योम hid_io_error(काष्ठा hid_device *hid);
अटल पूर्णांक hid_submit_out(काष्ठा hid_device *hid);
अटल पूर्णांक hid_submit_ctrl(काष्ठा hid_device *hid);
अटल व्योम hid_cancel_delayed_stuff(काष्ठा usbhid_device *usbhid);

/* Start up the input URB */
अटल पूर्णांक hid_start_in(काष्ठा hid_device *hid)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	spin_lock_irqsave(&usbhid->lock, flags);
	अगर (test_bit(HID_IN_POLLING, &usbhid->iofl) &&
	    !test_bit(HID_DISCONNECTED, &usbhid->iofl) &&
	    !test_bit(HID_SUSPENDED, &usbhid->iofl) &&
	    !test_and_set_bit(HID_IN_RUNNING, &usbhid->iofl)) अणु
		rc = usb_submit_urb(usbhid->urbin, GFP_ATOMIC);
		अगर (rc != 0) अणु
			clear_bit(HID_IN_RUNNING, &usbhid->iofl);
			अगर (rc == -ENOSPC)
				set_bit(HID_NO_BANDWIDTH, &usbhid->iofl);
		पूर्ण अन्यथा अणु
			clear_bit(HID_NO_BANDWIDTH, &usbhid->iofl);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&usbhid->lock, flags);
	वापस rc;
पूर्ण

/* I/O retry समयr routine */
अटल व्योम hid_retry_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा usbhid_device *usbhid = from_समयr(usbhid, t, io_retry);
	काष्ठा hid_device *hid = usbhid->hid;

	dev_dbg(&usbhid->पूर्णांकf->dev, "retrying intr urb\n");
	अगर (hid_start_in(hid))
		hid_io_error(hid);
पूर्ण

/* Workqueue routine to reset the device or clear a halt */
अटल व्योम hid_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usbhid_device *usbhid =
		container_of(work, काष्ठा usbhid_device, reset_work);
	काष्ठा hid_device *hid = usbhid->hid;
	पूर्णांक rc;

	अगर (test_bit(HID_CLEAR_HALT, &usbhid->iofl)) अणु
		dev_dbg(&usbhid->पूर्णांकf->dev, "clear halt\n");
		rc = usb_clear_halt(hid_to_usb_dev(hid), usbhid->urbin->pipe);
		clear_bit(HID_CLEAR_HALT, &usbhid->iofl);
		अगर (rc == 0) अणु
			hid_start_in(hid);
		पूर्ण अन्यथा अणु
			dev_dbg(&usbhid->पूर्णांकf->dev,
					"clear-halt failed: %d\n", rc);
			set_bit(HID_RESET_PENDING, &usbhid->iofl);
		पूर्ण
	पूर्ण

	अगर (test_bit(HID_RESET_PENDING, &usbhid->iofl)) अणु
		dev_dbg(&usbhid->पूर्णांकf->dev, "resetting device\n");
		usb_queue_reset_device(usbhid->पूर्णांकf);
	पूर्ण
पूर्ण

/* Main I/O error handler */
अटल व्योम hid_io_error(काष्ठा hid_device *hid)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	spin_lock_irqsave(&usbhid->lock, flags);

	/* Stop when disconnected */
	अगर (test_bit(HID_DISCONNECTED, &usbhid->iofl))
		जाओ करोne;

	/* If it has been a जबतक since the last error, we'll assume
	 * this a bअक्रम new error and reset the retry समयout. */
	अगर (समय_after(jअगरfies, usbhid->stop_retry + HZ/2))
		usbhid->retry_delay = 0;

	/* When an error occurs, retry at increasing पूर्णांकervals */
	अगर (usbhid->retry_delay == 0) अणु
		usbhid->retry_delay = 13;	/* Then 26, 52, 104, 104, ... */
		usbhid->stop_retry = jअगरfies + msecs_to_jअगरfies(1000);
	पूर्ण अन्यथा अगर (usbhid->retry_delay < 100)
		usbhid->retry_delay *= 2;

	अगर (समय_after(jअगरfies, usbhid->stop_retry)) अणु

		/* Retries failed, so करो a port reset unless we lack bandwidth*/
		अगर (!test_bit(HID_NO_BANDWIDTH, &usbhid->iofl)
		     && !test_and_set_bit(HID_RESET_PENDING, &usbhid->iofl)) अणु

			schedule_work(&usbhid->reset_work);
			जाओ करोne;
		पूर्ण
	पूर्ण

	mod_समयr(&usbhid->io_retry,
			jअगरfies + msecs_to_jअगरfies(usbhid->retry_delay));
करोne:
	spin_unlock_irqrestore(&usbhid->lock, flags);
पूर्ण

अटल व्योम usbhid_mark_busy(काष्ठा usbhid_device *usbhid)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usbhid->पूर्णांकf;

	usb_mark_last_busy(पूर्णांकerface_to_usbdev(पूर्णांकf));
पूर्ण

अटल पूर्णांक usbhid_restart_out_queue(काष्ठा usbhid_device *usbhid)
अणु
	काष्ठा hid_device *hid = usb_get_पूर्णांकfdata(usbhid->पूर्णांकf);
	पूर्णांक kicked;
	पूर्णांक r;

	अगर (!hid || test_bit(HID_RESET_PENDING, &usbhid->iofl) ||
			test_bit(HID_SUSPENDED, &usbhid->iofl))
		वापस 0;

	अगर ((kicked = (usbhid->outhead != usbhid->outtail))) अणु
		hid_dbg(hid, "Kicking head %d tail %d", usbhid->outhead, usbhid->outtail);

		/* Try to wake up from स्वतःsuspend... */
		r = usb_स्वतःpm_get_पूर्णांकerface_async(usbhid->पूर्णांकf);
		अगर (r < 0)
			वापस r;

		/*
		 * If still suspended, करोn't submit.  Submission will
		 * occur अगर/when resume drains the queue.
		 */
		अगर (test_bit(HID_SUSPENDED, &usbhid->iofl)) अणु
			usb_स्वतःpm_put_पूर्णांकerface_no_suspend(usbhid->पूर्णांकf);
			वापस r;
		पूर्ण

		/* Asynchronously flush queue. */
		set_bit(HID_OUT_RUNNING, &usbhid->iofl);
		अगर (hid_submit_out(hid)) अणु
			clear_bit(HID_OUT_RUNNING, &usbhid->iofl);
			usb_स्वतःpm_put_पूर्णांकerface_async(usbhid->पूर्णांकf);
		पूर्ण
		wake_up(&usbhid->रुको);
	पूर्ण
	वापस kicked;
पूर्ण

अटल पूर्णांक usbhid_restart_ctrl_queue(काष्ठा usbhid_device *usbhid)
अणु
	काष्ठा hid_device *hid = usb_get_पूर्णांकfdata(usbhid->पूर्णांकf);
	पूर्णांक kicked;
	पूर्णांक r;

	WARN_ON(hid == शून्य);
	अगर (!hid || test_bit(HID_RESET_PENDING, &usbhid->iofl) ||
			test_bit(HID_SUSPENDED, &usbhid->iofl))
		वापस 0;

	अगर ((kicked = (usbhid->ctrlhead != usbhid->ctrltail))) अणु
		hid_dbg(hid, "Kicking head %d tail %d", usbhid->ctrlhead, usbhid->ctrltail);

		/* Try to wake up from स्वतःsuspend... */
		r = usb_स्वतःpm_get_पूर्णांकerface_async(usbhid->पूर्णांकf);
		अगर (r < 0)
			वापस r;

		/*
		 * If still suspended, करोn't submit.  Submission will
		 * occur अगर/when resume drains the queue.
		 */
		अगर (test_bit(HID_SUSPENDED, &usbhid->iofl)) अणु
			usb_स्वतःpm_put_पूर्णांकerface_no_suspend(usbhid->पूर्णांकf);
			वापस r;
		पूर्ण

		/* Asynchronously flush queue. */
		set_bit(HID_CTRL_RUNNING, &usbhid->iofl);
		अगर (hid_submit_ctrl(hid)) अणु
			clear_bit(HID_CTRL_RUNNING, &usbhid->iofl);
			usb_स्वतःpm_put_पूर्णांकerface_async(usbhid->पूर्णांकf);
		पूर्ण
		wake_up(&usbhid->रुको);
	पूर्ण
	वापस kicked;
पूर्ण

/*
 * Input पूर्णांकerrupt completion handler.
 */

अटल व्योम hid_irq_in(काष्ठा urb *urb)
अणु
	काष्ठा hid_device	*hid = urb->context;
	काष्ठा usbhid_device	*usbhid = hid->driver_data;
	पूर्णांक			status;

	चयन (urb->status) अणु
	हाल 0:			/* success */
		usbhid->retry_delay = 0;
		अगर (!test_bit(HID_OPENED, &usbhid->iofl))
			अवरोध;
		usbhid_mark_busy(usbhid);
		अगर (!test_bit(HID_RESUME_RUNNING, &usbhid->iofl)) अणु
			hid_input_report(urb->context, HID_INPUT_REPORT,
					 urb->transfer_buffer,
					 urb->actual_length, 1);
			/*
			 * स्वतःsuspend refused जबतक keys are pressed
			 * because most keyboards करोn't wake up when
			 * a key is released
			 */
			अगर (hid_check_keys_pressed(hid))
				set_bit(HID_KEYS_PRESSED, &usbhid->iofl);
			अन्यथा
				clear_bit(HID_KEYS_PRESSED, &usbhid->iofl);
		पूर्ण
		अवरोध;
	हाल -EPIPE:		/* stall */
		usbhid_mark_busy(usbhid);
		clear_bit(HID_IN_RUNNING, &usbhid->iofl);
		set_bit(HID_CLEAR_HALT, &usbhid->iofl);
		schedule_work(&usbhid->reset_work);
		वापस;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:	/* unplug */
		clear_bit(HID_IN_RUNNING, &usbhid->iofl);
		वापस;
	हाल -EILSEQ:		/* protocol error or unplug */
	हाल -EPROTO:		/* protocol error or unplug */
	हाल -ETIME:		/* protocol error or unplug */
	हाल -ETIMEDOUT:	/* Should never happen, but... */
		usbhid_mark_busy(usbhid);
		clear_bit(HID_IN_RUNNING, &usbhid->iofl);
		hid_io_error(hid);
		वापस;
	शेष:		/* error */
		hid_warn(urb->dev, "input irq status %d received\n",
			 urb->status);
	पूर्ण

	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status) अणु
		clear_bit(HID_IN_RUNNING, &usbhid->iofl);
		अगर (status != -EPERM) अणु
			hid_err(hid, "can't resubmit intr, %s-%s/input%d, status %d\n",
				hid_to_usb_dev(hid)->bus->bus_name,
				hid_to_usb_dev(hid)->devpath,
				usbhid->अगरnum, status);
			hid_io_error(hid);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hid_submit_out(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_report *report;
	अक्षर *raw_report;
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	पूर्णांक r;

	report = usbhid->out[usbhid->outtail].report;
	raw_report = usbhid->out[usbhid->outtail].raw_report;

	usbhid->urbout->transfer_buffer_length = hid_report_len(report);
	usbhid->urbout->dev = hid_to_usb_dev(hid);
	अगर (raw_report) अणु
		स_नकल(usbhid->outbuf, raw_report,
				usbhid->urbout->transfer_buffer_length);
		kमुक्त(raw_report);
		usbhid->out[usbhid->outtail].raw_report = शून्य;
	पूर्ण

	dbg_hid("submitting out urb\n");

	r = usb_submit_urb(usbhid->urbout, GFP_ATOMIC);
	अगर (r < 0) अणु
		hid_err(hid, "usb_submit_urb(out) failed: %d\n", r);
		वापस r;
	पूर्ण
	usbhid->last_out = jअगरfies;
	वापस 0;
पूर्ण

अटल पूर्णांक hid_submit_ctrl(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_report *report;
	अचिन्हित अक्षर dir;
	अक्षर *raw_report;
	पूर्णांक len, r;
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	report = usbhid->ctrl[usbhid->ctrltail].report;
	raw_report = usbhid->ctrl[usbhid->ctrltail].raw_report;
	dir = usbhid->ctrl[usbhid->ctrltail].dir;

	len = hid_report_len(report);
	अगर (dir == USB_सूची_OUT) अणु
		usbhid->urbctrl->pipe = usb_sndctrlpipe(hid_to_usb_dev(hid), 0);
		usbhid->urbctrl->transfer_buffer_length = len;
		अगर (raw_report) अणु
			स_नकल(usbhid->ctrlbuf, raw_report, len);
			kमुक्त(raw_report);
			usbhid->ctrl[usbhid->ctrltail].raw_report = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक maxpacket, padlen;

		usbhid->urbctrl->pipe = usb_rcvctrlpipe(hid_to_usb_dev(hid), 0);
		maxpacket = usb_maxpacket(hid_to_usb_dev(hid),
					  usbhid->urbctrl->pipe, 0);
		अगर (maxpacket > 0) अणु
			padlen = DIV_ROUND_UP(len, maxpacket);
			padlen *= maxpacket;
			अगर (padlen > usbhid->bufsize)
				padlen = usbhid->bufsize;
		पूर्ण अन्यथा
			padlen = 0;
		usbhid->urbctrl->transfer_buffer_length = padlen;
	पूर्ण
	usbhid->urbctrl->dev = hid_to_usb_dev(hid);

	usbhid->cr->bRequestType = USB_TYPE_CLASS | USB_RECIP_INTERFACE | dir;
	usbhid->cr->bRequest = (dir == USB_सूची_OUT) ? HID_REQ_SET_REPORT :
						      HID_REQ_GET_REPORT;
	usbhid->cr->wValue = cpu_to_le16(((report->type + 1) << 8) |
					 report->id);
	usbhid->cr->wIndex = cpu_to_le16(usbhid->अगरnum);
	usbhid->cr->wLength = cpu_to_le16(len);

	dbg_hid("submitting ctrl urb: %s wValue=0x%04x wIndex=0x%04x wLength=%u\n",
		usbhid->cr->bRequest == HID_REQ_SET_REPORT ? "Set_Report" :
							     "Get_Report",
		usbhid->cr->wValue, usbhid->cr->wIndex, usbhid->cr->wLength);

	r = usb_submit_urb(usbhid->urbctrl, GFP_ATOMIC);
	अगर (r < 0) अणु
		hid_err(hid, "usb_submit_urb(ctrl) failed: %d\n", r);
		वापस r;
	पूर्ण
	usbhid->last_ctrl = jअगरfies;
	वापस 0;
पूर्ण

/*
 * Output पूर्णांकerrupt completion handler.
 */

अटल व्योम hid_irq_out(काष्ठा urb *urb)
अणु
	काष्ठा hid_device *hid = urb->context;
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक unplug = 0;

	चयन (urb->status) अणु
	हाल 0:			/* success */
		अवरोध;
	हाल -ESHUTDOWN:	/* unplug */
		unplug = 1;
		अवरोध;
	हाल -EILSEQ:		/* protocol error or unplug */
	हाल -EPROTO:		/* protocol error or unplug */
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
		अवरोध;
	शेष:		/* error */
		hid_warn(urb->dev, "output irq status %d received\n",
			 urb->status);
	पूर्ण

	spin_lock_irqsave(&usbhid->lock, flags);

	अगर (unplug) अणु
		usbhid->outtail = usbhid->outhead;
	पूर्ण अन्यथा अणु
		usbhid->outtail = (usbhid->outtail + 1) & (HID_OUTPUT_FIFO_SIZE - 1);

		अगर (usbhid->outhead != usbhid->outtail &&
				hid_submit_out(hid) == 0) अणु
			/* Successfully submitted next urb in queue */
			spin_unlock_irqrestore(&usbhid->lock, flags);
			वापस;
		पूर्ण
	पूर्ण

	clear_bit(HID_OUT_RUNNING, &usbhid->iofl);
	spin_unlock_irqrestore(&usbhid->lock, flags);
	usb_स्वतःpm_put_पूर्णांकerface_async(usbhid->पूर्णांकf);
	wake_up(&usbhid->रुको);
पूर्ण

/*
 * Control pipe completion handler.
 */

अटल व्योम hid_ctrl(काष्ठा urb *urb)
अणु
	काष्ठा hid_device *hid = urb->context;
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक unplug = 0, status = urb->status;

	चयन (status) अणु
	हाल 0:			/* success */
		अगर (usbhid->ctrl[usbhid->ctrltail].dir == USB_सूची_IN)
			hid_input_report(urb->context,
				usbhid->ctrl[usbhid->ctrltail].report->type,
				urb->transfer_buffer, urb->actual_length, 0);
		अवरोध;
	हाल -ESHUTDOWN:	/* unplug */
		unplug = 1;
		अवरोध;
	हाल -EILSEQ:		/* protocol error or unplug */
	हाल -EPROTO:		/* protocol error or unplug */
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -EPIPE:		/* report not available */
		अवरोध;
	शेष:		/* error */
		hid_warn(urb->dev, "ctrl urb status %d received\n", status);
	पूर्ण

	spin_lock_irqsave(&usbhid->lock, flags);

	अगर (unplug) अणु
		usbhid->ctrltail = usbhid->ctrlhead;
	पूर्ण अन्यथा अणु
		usbhid->ctrltail = (usbhid->ctrltail + 1) & (HID_CONTROL_FIFO_SIZE - 1);

		अगर (usbhid->ctrlhead != usbhid->ctrltail &&
				hid_submit_ctrl(hid) == 0) अणु
			/* Successfully submitted next urb in queue */
			spin_unlock_irqrestore(&usbhid->lock, flags);
			वापस;
		पूर्ण
	पूर्ण

	clear_bit(HID_CTRL_RUNNING, &usbhid->iofl);
	spin_unlock_irqrestore(&usbhid->lock, flags);
	usb_स्वतःpm_put_पूर्णांकerface_async(usbhid->पूर्णांकf);
	wake_up(&usbhid->रुको);
पूर्ण

अटल व्योम __usbhid_submit_report(काष्ठा hid_device *hid, काष्ठा hid_report *report,
				   अचिन्हित अक्षर dir)
अणु
	पूर्णांक head;
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	अगर (((hid->quirks & HID_QUIRK_NOGET) && dir == USB_सूची_IN) ||
		test_bit(HID_DISCONNECTED, &usbhid->iofl))
		वापस;

	अगर (usbhid->urbout && dir == USB_सूची_OUT && report->type == HID_OUTPUT_REPORT) अणु
		अगर ((head = (usbhid->outhead + 1) & (HID_OUTPUT_FIFO_SIZE - 1)) == usbhid->outtail) अणु
			hid_warn(hid, "output queue full\n");
			वापस;
		पूर्ण

		usbhid->out[usbhid->outhead].raw_report = hid_alloc_report_buf(report, GFP_ATOMIC);
		अगर (!usbhid->out[usbhid->outhead].raw_report) अणु
			hid_warn(hid, "output queueing failed\n");
			वापस;
		पूर्ण
		hid_output_report(report, usbhid->out[usbhid->outhead].raw_report);
		usbhid->out[usbhid->outhead].report = report;
		usbhid->outhead = head;

		/* If the queue isn't running, restart it */
		अगर (!test_bit(HID_OUT_RUNNING, &usbhid->iofl)) अणु
			usbhid_restart_out_queue(usbhid);

		/* Otherwise see अगर an earlier request has समयd out */
		पूर्ण अन्यथा अगर (समय_after(jअगरfies, usbhid->last_out + HZ * 5)) अणु

			/* Prevent स्वतःsuspend following the unlink */
			usb_स्वतःpm_get_पूर्णांकerface_no_resume(usbhid->पूर्णांकf);

			/*
			 * Prevent resubmission in हाल the URB completes
			 * beक्रमe we can unlink it.  We करोn't want to cancel
			 * the wrong transfer!
			 */
			usb_block_urb(usbhid->urbout);

			/* Drop lock to aव्योम deadlock अगर the callback runs */
			spin_unlock(&usbhid->lock);

			usb_unlink_urb(usbhid->urbout);
			spin_lock(&usbhid->lock);
			usb_unblock_urb(usbhid->urbout);

			/* Unlink might have stopped the queue */
			अगर (!test_bit(HID_OUT_RUNNING, &usbhid->iofl))
				usbhid_restart_out_queue(usbhid);

			/* Now we can allow स्वतःsuspend again */
			usb_स्वतःpm_put_पूर्णांकerface_async(usbhid->पूर्णांकf);
		पूर्ण
		वापस;
	पूर्ण

	अगर ((head = (usbhid->ctrlhead + 1) & (HID_CONTROL_FIFO_SIZE - 1)) == usbhid->ctrltail) अणु
		hid_warn(hid, "control queue full\n");
		वापस;
	पूर्ण

	अगर (dir == USB_सूची_OUT) अणु
		usbhid->ctrl[usbhid->ctrlhead].raw_report = hid_alloc_report_buf(report, GFP_ATOMIC);
		अगर (!usbhid->ctrl[usbhid->ctrlhead].raw_report) अणु
			hid_warn(hid, "control queueing failed\n");
			वापस;
		पूर्ण
		hid_output_report(report, usbhid->ctrl[usbhid->ctrlhead].raw_report);
	पूर्ण
	usbhid->ctrl[usbhid->ctrlhead].report = report;
	usbhid->ctrl[usbhid->ctrlhead].dir = dir;
	usbhid->ctrlhead = head;

	/* If the queue isn't running, restart it */
	अगर (!test_bit(HID_CTRL_RUNNING, &usbhid->iofl)) अणु
		usbhid_restart_ctrl_queue(usbhid);

	/* Otherwise see अगर an earlier request has समयd out */
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, usbhid->last_ctrl + HZ * 5)) अणु

		/* Prevent स्वतःsuspend following the unlink */
		usb_स्वतःpm_get_पूर्णांकerface_no_resume(usbhid->पूर्णांकf);

		/*
		 * Prevent resubmission in हाल the URB completes
		 * beक्रमe we can unlink it.  We करोn't want to cancel
		 * the wrong transfer!
		 */
		usb_block_urb(usbhid->urbctrl);

		/* Drop lock to aव्योम deadlock अगर the callback runs */
		spin_unlock(&usbhid->lock);

		usb_unlink_urb(usbhid->urbctrl);
		spin_lock(&usbhid->lock);
		usb_unblock_urb(usbhid->urbctrl);

		/* Unlink might have stopped the queue */
		अगर (!test_bit(HID_CTRL_RUNNING, &usbhid->iofl))
			usbhid_restart_ctrl_queue(usbhid);

		/* Now we can allow स्वतःsuspend again */
		usb_स्वतःpm_put_पूर्णांकerface_async(usbhid->पूर्णांकf);
	पूर्ण
पूर्ण

अटल व्योम usbhid_submit_report(काष्ठा hid_device *hid, काष्ठा hid_report *report, अचिन्हित अक्षर dir)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&usbhid->lock, flags);
	__usbhid_submit_report(hid, report, dir);
	spin_unlock_irqrestore(&usbhid->lock, flags);
पूर्ण

अटल पूर्णांक usbhid_रुको_io(काष्ठा hid_device *hid)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	अगर (!रुको_event_समयout(usbhid->रुको,
				(!test_bit(HID_CTRL_RUNNING, &usbhid->iofl) &&
				!test_bit(HID_OUT_RUNNING, &usbhid->iofl)),
					10*HZ)) अणु
		dbg_hid("timeout waiting for ctrl or out queue to clear\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hid_set_idle(काष्ठा usb_device *dev, पूर्णांक अगरnum, पूर्णांक report, पूर्णांक idle)
अणु
	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
		HID_REQ_SET_IDLE, USB_TYPE_CLASS | USB_RECIP_INTERFACE, (idle << 8) | report,
		अगरnum, शून्य, 0, USB_CTRL_SET_TIMEOUT);
पूर्ण

अटल पूर्णांक hid_get_class_descriptor(काष्ठा usb_device *dev, पूर्णांक अगरnum,
		अचिन्हित अक्षर type, व्योम *buf, पूर्णांक size)
अणु
	पूर्णांक result, retries = 4;

	स_रखो(buf, 0, size);

	करो अणु
		result = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
				USB_REQ_GET_DESCRIPTOR, USB_RECIP_INTERFACE | USB_सूची_IN,
				(type << 8), अगरnum, buf, size, USB_CTRL_GET_TIMEOUT);
		retries--;
	पूर्ण जबतक (result < size && retries);
	वापस result;
पूर्ण

अटल पूर्णांक usbhid_खोलो(काष्ठा hid_device *hid)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	पूर्णांक res;

	mutex_lock(&usbhid->mutex);

	set_bit(HID_OPENED, &usbhid->iofl);

	अगर (hid->quirks & HID_QUIRK_ALWAYS_POLL) अणु
		res = 0;
		जाओ Done;
	पूर्ण

	res = usb_स्वतःpm_get_पूर्णांकerface(usbhid->पूर्णांकf);
	/* the device must be awake to reliably request remote wakeup */
	अगर (res < 0) अणु
		clear_bit(HID_OPENED, &usbhid->iofl);
		res = -EIO;
		जाओ Done;
	पूर्ण

	usbhid->पूर्णांकf->needs_remote_wakeup = 1;

	set_bit(HID_RESUME_RUNNING, &usbhid->iofl);
	set_bit(HID_IN_POLLING, &usbhid->iofl);

	res = hid_start_in(hid);
	अगर (res) अणु
		अगर (res != -ENOSPC) अणु
			hid_io_error(hid);
			res = 0;
		पूर्ण अन्यथा अणु
			/* no use खोलोing अगर resources are insufficient */
			res = -EBUSY;
			clear_bit(HID_OPENED, &usbhid->iofl);
			clear_bit(HID_IN_POLLING, &usbhid->iofl);
			usbhid->पूर्णांकf->needs_remote_wakeup = 0;
		पूर्ण
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(usbhid->पूर्णांकf);

	/*
	 * In हाल events are generated जबतक nobody was listening,
	 * some are released when the device is re-खोलोed.
	 * Wait 50 msec क्रम the queue to empty beक्रमe allowing events
	 * to go through hid.
	 */
	अगर (res == 0)
		msleep(50);

	clear_bit(HID_RESUME_RUNNING, &usbhid->iofl);

 Done:
	mutex_unlock(&usbhid->mutex);
	वापस res;
पूर्ण

अटल व्योम usbhid_बंद(काष्ठा hid_device *hid)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	mutex_lock(&usbhid->mutex);

	/*
	 * Make sure we करोn't restart data acquisition due to
	 * a resumption we no दीर्घer care about by aव्योमing racing
	 * with hid_start_in().
	 */
	spin_lock_irq(&usbhid->lock);
	clear_bit(HID_OPENED, &usbhid->iofl);
	अगर (!(hid->quirks & HID_QUIRK_ALWAYS_POLL))
		clear_bit(HID_IN_POLLING, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);

	अगर (!(hid->quirks & HID_QUIRK_ALWAYS_POLL)) अणु
		hid_cancel_delayed_stuff(usbhid);
		usb_समाप्त_urb(usbhid->urbin);
		usbhid->पूर्णांकf->needs_remote_wakeup = 0;
	पूर्ण

	mutex_unlock(&usbhid->mutex);
पूर्ण

/*
 * Initialize all reports
 */

व्योम usbhid_init_reports(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_report *report;
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	काष्ठा hid_report_क्रमागत *report_क्रमागत;
	पूर्णांक err, ret;

	report_क्रमागत = &hid->report_क्रमागत[HID_INPUT_REPORT];
	list_क्रम_each_entry(report, &report_क्रमागत->report_list, list)
		usbhid_submit_report(hid, report, USB_सूची_IN);

	report_क्रमागत = &hid->report_क्रमागत[HID_FEATURE_REPORT];
	list_क्रम_each_entry(report, &report_क्रमागत->report_list, list)
		usbhid_submit_report(hid, report, USB_सूची_IN);

	err = 0;
	ret = usbhid_रुको_io(hid);
	जबतक (ret) अणु
		err |= ret;
		अगर (test_bit(HID_CTRL_RUNNING, &usbhid->iofl))
			usb_समाप्त_urb(usbhid->urbctrl);
		अगर (test_bit(HID_OUT_RUNNING, &usbhid->iofl))
			usb_समाप्त_urb(usbhid->urbout);
		ret = usbhid_रुको_io(hid);
	पूर्ण

	अगर (err)
		hid_warn(hid, "timeout initializing reports\n");
पूर्ण

/*
 * Reset LEDs which BIOS might have left on. For now, just NumLock (0x01).
 */
अटल पूर्णांक hid_find_field_early(काष्ठा hid_device *hid, अचिन्हित पूर्णांक page,
    अचिन्हित पूर्णांक hid_code, काष्ठा hid_field **pfield)
अणु
	काष्ठा hid_report *report;
	काष्ठा hid_field *field;
	काष्ठा hid_usage *usage;
	पूर्णांक i, j;

	list_क्रम_each_entry(report, &hid->report_क्रमागत[HID_OUTPUT_REPORT].report_list, list) अणु
		क्रम (i = 0; i < report->maxfield; i++) अणु
			field = report->field[i];
			क्रम (j = 0; j < field->maxusage; j++) अणु
				usage = &field->usage[j];
				अगर ((usage->hid & HID_USAGE_PAGE) == page &&
				    (usage->hid & 0xFFFF) == hid_code) अणु
					*pfield = field;
					वापस j;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम usbhid_set_leds(काष्ठा hid_device *hid)
अणु
	काष्ठा hid_field *field;
	पूर्णांक offset;

	अगर ((offset = hid_find_field_early(hid, HID_UP_LED, 0x01, &field)) != -1) अणु
		hid_set_field(field, offset, 0);
		usbhid_submit_report(hid, field->report, USB_सूची_OUT);
	पूर्ण
पूर्ण

/*
 * Traverse the supplied list of reports and find the दीर्घest
 */
अटल व्योम hid_find_max_report(काष्ठा hid_device *hid, अचिन्हित पूर्णांक type,
		अचिन्हित पूर्णांक *max)
अणु
	काष्ठा hid_report *report;
	अचिन्हित पूर्णांक size;

	list_क्रम_each_entry(report, &hid->report_क्रमागत[type].report_list, list) अणु
		size = ((report->size - 1) >> 3) + 1 + hid->report_क्रमागत[type].numbered;
		अगर (*max < size)
			*max = size;
	पूर्ण
पूर्ण

अटल पूर्णांक hid_alloc_buffers(काष्ठा usb_device *dev, काष्ठा hid_device *hid)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	usbhid->inbuf = usb_alloc_coherent(dev, usbhid->bufsize, GFP_KERNEL,
			&usbhid->inbuf_dma);
	usbhid->outbuf = usb_alloc_coherent(dev, usbhid->bufsize, GFP_KERNEL,
			&usbhid->outbuf_dma);
	usbhid->cr = kदो_स्मृति(माप(*usbhid->cr), GFP_KERNEL);
	usbhid->ctrlbuf = usb_alloc_coherent(dev, usbhid->bufsize, GFP_KERNEL,
			&usbhid->ctrlbuf_dma);
	अगर (!usbhid->inbuf || !usbhid->outbuf || !usbhid->cr ||
			!usbhid->ctrlbuf)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक usbhid_get_raw_report(काष्ठा hid_device *hid,
		अचिन्हित अक्षर report_number, __u8 *buf, माप_प्रकार count,
		अचिन्हित अक्षर report_type)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	काष्ठा usb_device *dev = hid_to_usb_dev(hid);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usbhid->पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = पूर्णांकf->cur_altsetting;
	पूर्णांक skipped_report_id = 0;
	पूर्णांक ret;

	/* Byte 0 is the report number. Report data starts at byte 1.*/
	buf[0] = report_number;
	अगर (report_number == 0x0) अणु
		/* Offset the वापस buffer by 1, so that the report ID
		   will reमुख्य in byte 0. */
		buf++;
		count--;
		skipped_report_id = 1;
	पूर्ण
	ret = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
		HID_REQ_GET_REPORT,
		USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		((report_type + 1) << 8) | report_number,
		पूर्णांकerface->desc.bInterfaceNumber, buf, count,
		USB_CTRL_SET_TIMEOUT);

	/* count also the report id */
	अगर (ret > 0 && skipped_report_id)
		ret++;

	वापस ret;
पूर्ण

अटल पूर्णांक usbhid_set_raw_report(काष्ठा hid_device *hid, अचिन्हित पूर्णांक reportnum,
				 __u8 *buf, माप_प्रकार count, अचिन्हित अक्षर rtype)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	काष्ठा usb_device *dev = hid_to_usb_dev(hid);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usbhid->पूर्णांकf;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = पूर्णांकf->cur_altsetting;
	पूर्णांक ret, skipped_report_id = 0;

	/* Byte 0 is the report number. Report data starts at byte 1.*/
	अगर ((rtype == HID_OUTPUT_REPORT) &&
	    (hid->quirks & HID_QUIRK_SKIP_OUTPUT_REPORT_ID))
		buf[0] = 0;
	अन्यथा
		buf[0] = reportnum;

	अगर (buf[0] == 0x0) अणु
		/* Don't send the Report ID */
		buf++;
		count--;
		skipped_report_id = 1;
	पूर्ण

	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			HID_REQ_SET_REPORT,
			USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			((rtype + 1) << 8) | reportnum,
			पूर्णांकerface->desc.bInterfaceNumber, buf, count,
			USB_CTRL_SET_TIMEOUT);
	/* count also the report id, अगर this was a numbered report. */
	अगर (ret > 0 && skipped_report_id)
		ret++;

	वापस ret;
पूर्ण

अटल पूर्णांक usbhid_output_report(काष्ठा hid_device *hid, __u8 *buf, माप_प्रकार count)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	काष्ठा usb_device *dev = hid_to_usb_dev(hid);
	पूर्णांक actual_length, skipped_report_id = 0, ret;

	अगर (!usbhid->urbout)
		वापस -ENOSYS;

	अगर (buf[0] == 0x0) अणु
		/* Don't send the Report ID */
		buf++;
		count--;
		skipped_report_id = 1;
	पूर्ण

	ret = usb_पूर्णांकerrupt_msg(dev, usbhid->urbout->pipe,
				buf, count, &actual_length,
				USB_CTRL_SET_TIMEOUT);
	/* वापस the number of bytes transferred */
	अगर (ret == 0) अणु
		ret = actual_length;
		/* count also the report id */
		अगर (skipped_report_id)
			ret++;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hid_मुक्त_buffers(काष्ठा usb_device *dev, काष्ठा hid_device *hid)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	usb_मुक्त_coherent(dev, usbhid->bufsize, usbhid->inbuf, usbhid->inbuf_dma);
	usb_मुक्त_coherent(dev, usbhid->bufsize, usbhid->outbuf, usbhid->outbuf_dma);
	kमुक्त(usbhid->cr);
	usb_मुक्त_coherent(dev, usbhid->bufsize, usbhid->ctrlbuf, usbhid->ctrlbuf_dma);
पूर्ण

अटल पूर्णांक usbhid_parse(काष्ठा hid_device *hid)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hid->dev.parent);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = पूर्णांकf->cur_altsetting;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev (पूर्णांकf);
	काष्ठा hid_descriptor *hdesc;
	u32 quirks = 0;
	अचिन्हित पूर्णांक rsize = 0;
	अक्षर *rdesc;
	पूर्णांक ret, n;
	पूर्णांक num_descriptors;
	माप_प्रकार offset = दुरत्व(काष्ठा hid_descriptor, desc);

	quirks = hid_lookup_quirk(hid);

	अगर (quirks & HID_QUIRK_IGNORE)
		वापस -ENODEV;

	/* Many keyboards and mice करोn't like to be polled क्रम reports,
	 * so we will always set the HID_QUIRK_NOGET flag क्रम them. */
	अगर (पूर्णांकerface->desc.bInterfaceSubClass == USB_INTERFACE_SUBCLASS_BOOT) अणु
		अगर (पूर्णांकerface->desc.bInterfaceProtocol == USB_INTERFACE_PROTOCOL_KEYBOARD ||
			पूर्णांकerface->desc.bInterfaceProtocol == USB_INTERFACE_PROTOCOL_MOUSE)
				quirks |= HID_QUIRK_NOGET;
	पूर्ण

	अगर (usb_get_extra_descriptor(पूर्णांकerface, HID_DT_HID, &hdesc) &&
	    (!पूर्णांकerface->desc.bNumEndpoपूर्णांकs ||
	     usb_get_extra_descriptor(&पूर्णांकerface->endpoपूर्णांक[0], HID_DT_HID, &hdesc))) अणु
		dbg_hid("class descriptor not present\n");
		वापस -ENODEV;
	पूर्ण

	अगर (hdesc->bLength < माप(काष्ठा hid_descriptor)) अणु
		dbg_hid("hid descriptor is too short\n");
		वापस -EINVAL;
	पूर्ण

	hid->version = le16_to_cpu(hdesc->bcdHID);
	hid->country = hdesc->bCountryCode;

	num_descriptors = min_t(पूर्णांक, hdesc->bNumDescriptors,
	       (hdesc->bLength - offset) / माप(काष्ठा hid_class_descriptor));

	क्रम (n = 0; n < num_descriptors; n++)
		अगर (hdesc->desc[n].bDescriptorType == HID_DT_REPORT)
			rsize = le16_to_cpu(hdesc->desc[n].wDescriptorLength);

	अगर (!rsize || rsize > HID_MAX_DESCRIPTOR_SIZE) अणु
		dbg_hid("weird size of report descriptor (%u)\n", rsize);
		वापस -EINVAL;
	पूर्ण

	rdesc = kदो_स्मृति(rsize, GFP_KERNEL);
	अगर (!rdesc)
		वापस -ENOMEM;

	hid_set_idle(dev, पूर्णांकerface->desc.bInterfaceNumber, 0, 0);

	ret = hid_get_class_descriptor(dev, पूर्णांकerface->desc.bInterfaceNumber,
			HID_DT_REPORT, rdesc, rsize);
	अगर (ret < 0) अणु
		dbg_hid("reading report descriptor failed\n");
		kमुक्त(rdesc);
		जाओ err;
	पूर्ण

	ret = hid_parse_report(hid, rdesc, rsize);
	kमुक्त(rdesc);
	अगर (ret) अणु
		dbg_hid("parsing report descriptor failed\n");
		जाओ err;
	पूर्ण

	hid->quirks |= quirks;

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक usbhid_start(काष्ठा hid_device *hid)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hid->dev.parent);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = पूर्णांकf->cur_altsetting;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	अचिन्हित पूर्णांक n, insize = 0;
	पूर्णांक ret;

	mutex_lock(&usbhid->mutex);

	clear_bit(HID_DISCONNECTED, &usbhid->iofl);

	usbhid->bufsize = HID_MIN_BUFFER_SIZE;
	hid_find_max_report(hid, HID_INPUT_REPORT, &usbhid->bufsize);
	hid_find_max_report(hid, HID_OUTPUT_REPORT, &usbhid->bufsize);
	hid_find_max_report(hid, HID_FEATURE_REPORT, &usbhid->bufsize);

	अगर (usbhid->bufsize > HID_MAX_BUFFER_SIZE)
		usbhid->bufsize = HID_MAX_BUFFER_SIZE;

	hid_find_max_report(hid, HID_INPUT_REPORT, &insize);

	अगर (insize > HID_MAX_BUFFER_SIZE)
		insize = HID_MAX_BUFFER_SIZE;

	अगर (hid_alloc_buffers(dev, hid)) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	क्रम (n = 0; n < पूर्णांकerface->desc.bNumEndpoपूर्णांकs; n++) अणु
		काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
		पूर्णांक pipe;
		पूर्णांक पूर्णांकerval;

		endpoपूर्णांक = &पूर्णांकerface->endpoपूर्णांक[n].desc;
		अगर (!usb_endpoपूर्णांक_xfer_पूर्णांक(endpoपूर्णांक))
			जारी;

		पूर्णांकerval = endpoपूर्णांक->bInterval;

		/* Some venकरोrs give fullspeed पूर्णांकerval on highspeed devides */
		अगर (hid->quirks & HID_QUIRK_FULLSPEED_INTERVAL &&
		    dev->speed == USB_SPEED_HIGH) अणु
			पूर्णांकerval = fls(endpoपूर्णांक->bInterval*8);
			pr_info("%s: Fixing fullspeed to highspeed interval: %d -> %d\n",
				hid->name, endpoपूर्णांक->bInterval, पूर्णांकerval);
		पूर्ण

		/* Change the polling पूर्णांकerval of mice, joysticks
		 * and keyboards.
		 */
		चयन (hid->collection->usage) अणु
		हाल HID_GD_MOUSE:
			अगर (hid_mousepoll_पूर्णांकerval > 0)
				पूर्णांकerval = hid_mousepoll_पूर्णांकerval;
			अवरोध;
		हाल HID_GD_JOYSTICK:
			अगर (hid_jspoll_पूर्णांकerval > 0)
				पूर्णांकerval = hid_jspoll_पूर्णांकerval;
			अवरोध;
		हाल HID_GD_KEYBOARD:
			अगर (hid_kbpoll_पूर्णांकerval > 0)
				पूर्णांकerval = hid_kbpoll_पूर्णांकerval;
			अवरोध;
		पूर्ण

		ret = -ENOMEM;
		अगर (usb_endpoपूर्णांक_dir_in(endpoपूर्णांक)) अणु
			अगर (usbhid->urbin)
				जारी;
			अगर (!(usbhid->urbin = usb_alloc_urb(0, GFP_KERNEL)))
				जाओ fail;
			pipe = usb_rcvपूर्णांकpipe(dev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
			usb_fill_पूर्णांक_urb(usbhid->urbin, dev, pipe, usbhid->inbuf, insize,
					 hid_irq_in, hid, पूर्णांकerval);
			usbhid->urbin->transfer_dma = usbhid->inbuf_dma;
			usbhid->urbin->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		पूर्ण अन्यथा अणु
			अगर (usbhid->urbout)
				जारी;
			अगर (!(usbhid->urbout = usb_alloc_urb(0, GFP_KERNEL)))
				जाओ fail;
			pipe = usb_sndपूर्णांकpipe(dev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
			usb_fill_पूर्णांक_urb(usbhid->urbout, dev, pipe, usbhid->outbuf, 0,
					 hid_irq_out, hid, पूर्णांकerval);
			usbhid->urbout->transfer_dma = usbhid->outbuf_dma;
			usbhid->urbout->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		पूर्ण
	पूर्ण

	usbhid->urbctrl = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!usbhid->urbctrl) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	usb_fill_control_urb(usbhid->urbctrl, dev, 0, (व्योम *) usbhid->cr,
			     usbhid->ctrlbuf, 1, hid_ctrl, hid);
	usbhid->urbctrl->transfer_dma = usbhid->ctrlbuf_dma;
	usbhid->urbctrl->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	set_bit(HID_STARTED, &usbhid->iofl);

	अगर (hid->quirks & HID_QUIRK_ALWAYS_POLL) अणु
		ret = usb_स्वतःpm_get_पूर्णांकerface(usbhid->पूर्णांकf);
		अगर (ret)
			जाओ fail;
		set_bit(HID_IN_POLLING, &usbhid->iofl);
		usbhid->पूर्णांकf->needs_remote_wakeup = 1;
		ret = hid_start_in(hid);
		अगर (ret) अणु
			dev_err(&hid->dev,
				"failed to start in urb: %d\n", ret);
		पूर्ण
		usb_स्वतःpm_put_पूर्णांकerface(usbhid->पूर्णांकf);
	पूर्ण

	/* Some keyboards करोn't work until their LEDs have been set.
	 * Since BIOSes करो set the LEDs, it must be safe क्रम any device
	 * that supports the keyboard boot protocol.
	 * In addition, enable remote wakeup by शेष क्रम all keyboard
	 * devices supporting the boot protocol.
	 */
	अगर (पूर्णांकerface->desc.bInterfaceSubClass == USB_INTERFACE_SUBCLASS_BOOT &&
			पूर्णांकerface->desc.bInterfaceProtocol ==
				USB_INTERFACE_PROTOCOL_KEYBOARD) अणु
		usbhid_set_leds(hid);
		device_set_wakeup_enable(&dev->dev, 1);
	पूर्ण

	mutex_unlock(&usbhid->mutex);
	वापस 0;

fail:
	usb_मुक्त_urb(usbhid->urbin);
	usb_मुक्त_urb(usbhid->urbout);
	usb_मुक्त_urb(usbhid->urbctrl);
	usbhid->urbin = शून्य;
	usbhid->urbout = शून्य;
	usbhid->urbctrl = शून्य;
	hid_मुक्त_buffers(dev, hid);
	mutex_unlock(&usbhid->mutex);
	वापस ret;
पूर्ण

अटल व्योम usbhid_stop(काष्ठा hid_device *hid)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	अगर (WARN_ON(!usbhid))
		वापस;

	अगर (hid->quirks & HID_QUIRK_ALWAYS_POLL) अणु
		clear_bit(HID_IN_POLLING, &usbhid->iofl);
		usbhid->पूर्णांकf->needs_remote_wakeup = 0;
	पूर्ण

	mutex_lock(&usbhid->mutex);

	clear_bit(HID_STARTED, &usbhid->iofl);
	spin_lock_irq(&usbhid->lock);	/* Sync with error and led handlers */
	set_bit(HID_DISCONNECTED, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);
	usb_समाप्त_urb(usbhid->urbin);
	usb_समाप्त_urb(usbhid->urbout);
	usb_समाप्त_urb(usbhid->urbctrl);

	hid_cancel_delayed_stuff(usbhid);

	hid->claimed = 0;

	usb_मुक्त_urb(usbhid->urbin);
	usb_मुक्त_urb(usbhid->urbctrl);
	usb_मुक्त_urb(usbhid->urbout);
	usbhid->urbin = शून्य; /* करोn't mess up next start */
	usbhid->urbctrl = शून्य;
	usbhid->urbout = शून्य;

	hid_मुक्त_buffers(hid_to_usb_dev(hid), hid);

	mutex_unlock(&usbhid->mutex);
पूर्ण

अटल पूर्णांक usbhid_घातer(काष्ठा hid_device *hid, पूर्णांक lvl)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	पूर्णांक r = 0;

	चयन (lvl) अणु
	हाल PM_HINT_FULLON:
		r = usb_स्वतःpm_get_पूर्णांकerface(usbhid->पूर्णांकf);
		अवरोध;

	हाल PM_HINT_NORMAL:
		usb_स्वतःpm_put_पूर्णांकerface(usbhid->पूर्णांकf);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम usbhid_request(काष्ठा hid_device *hid, काष्ठा hid_report *rep, पूर्णांक reqtype)
अणु
	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		usbhid_submit_report(hid, rep, USB_सूची_IN);
		अवरोध;
	हाल HID_REQ_SET_REPORT:
		usbhid_submit_report(hid, rep, USB_सूची_OUT);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक usbhid_raw_request(काष्ठा hid_device *hid, अचिन्हित अक्षर reportnum,
			      __u8 *buf, माप_प्रकार len, अचिन्हित अक्षर rtype,
			      पूर्णांक reqtype)
अणु
	चयन (reqtype) अणु
	हाल HID_REQ_GET_REPORT:
		वापस usbhid_get_raw_report(hid, reportnum, buf, len, rtype);
	हाल HID_REQ_SET_REPORT:
		वापस usbhid_set_raw_report(hid, reportnum, buf, len, rtype);
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक usbhid_idle(काष्ठा hid_device *hid, पूर्णांक report, पूर्णांक idle,
		पूर्णांक reqtype)
अणु
	काष्ठा usb_device *dev = hid_to_usb_dev(hid);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hid->dev.parent);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = पूर्णांकf->cur_altsetting;
	पूर्णांक अगरnum = पूर्णांकerface->desc.bInterfaceNumber;

	अगर (reqtype != HID_REQ_SET_IDLE)
		वापस -EINVAL;

	वापस hid_set_idle(dev, अगरnum, report, idle);
पूर्ण

काष्ठा hid_ll_driver usb_hid_driver = अणु
	.parse = usbhid_parse,
	.start = usbhid_start,
	.stop = usbhid_stop,
	.खोलो = usbhid_खोलो,
	.बंद = usbhid_बंद,
	.घातer = usbhid_घातer,
	.request = usbhid_request,
	.रुको = usbhid_रुको_io,
	.raw_request = usbhid_raw_request,
	.output_report = usbhid_output_report,
	.idle = usbhid_idle,
पूर्ण;
EXPORT_SYMBOL_GPL(usb_hid_driver);

अटल पूर्णांक usbhid_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = पूर्णांकf->cur_altsetting;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usbhid_device *usbhid;
	काष्ठा hid_device *hid;
	अचिन्हित पूर्णांक n, has_in = 0;
	माप_प्रकार len;
	पूर्णांक ret;

	dbg_hid("HID probe called for ifnum %d\n",
			पूर्णांकf->altsetting->desc.bInterfaceNumber);

	क्रम (n = 0; n < पूर्णांकerface->desc.bNumEndpoपूर्णांकs; n++)
		अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(&पूर्णांकerface->endpoपूर्णांक[n].desc))
			has_in++;
	अगर (!has_in) अणु
		hid_err(पूर्णांकf, "couldn't find an input interrupt endpoint\n");
		वापस -ENODEV;
	पूर्ण

	hid = hid_allocate_device();
	अगर (IS_ERR(hid))
		वापस PTR_ERR(hid);

	usb_set_पूर्णांकfdata(पूर्णांकf, hid);
	hid->ll_driver = &usb_hid_driver;
	hid->ff_init = hid_pidff_init;
#अगर_घोषित CONFIG_USB_HIDDEV
	hid->hiddev_connect = hiddev_connect;
	hid->hiddev_disconnect = hiddev_disconnect;
	hid->hiddev_hid_event = hiddev_hid_event;
	hid->hiddev_report_event = hiddev_report_event;
#पूर्ण_अगर
	hid->dev.parent = &पूर्णांकf->dev;
	hid->bus = BUS_USB;
	hid->venकरोr = le16_to_cpu(dev->descriptor.idVenकरोr);
	hid->product = le16_to_cpu(dev->descriptor.idProduct);
	hid->version = le16_to_cpu(dev->descriptor.bcdDevice);
	hid->name[0] = 0;
	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol ==
			USB_INTERFACE_PROTOCOL_MOUSE)
		hid->type = HID_TYPE_USBMOUSE;
	अन्यथा अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol == 0)
		hid->type = HID_TYPE_USBNONE;

	अगर (dev->manufacturer)
		strlcpy(hid->name, dev->manufacturer, माप(hid->name));

	अगर (dev->product) अणु
		अगर (dev->manufacturer)
			strlcat(hid->name, " ", माप(hid->name));
		strlcat(hid->name, dev->product, माप(hid->name));
	पूर्ण

	अगर (!म_माप(hid->name))
		snम_लिखो(hid->name, माप(hid->name), "HID %04x:%04x",
			 le16_to_cpu(dev->descriptor.idVenकरोr),
			 le16_to_cpu(dev->descriptor.idProduct));

	usb_make_path(dev, hid->phys, माप(hid->phys));
	strlcat(hid->phys, "/input", माप(hid->phys));
	len = म_माप(hid->phys);
	अगर (len < माप(hid->phys) - 1)
		snम_लिखो(hid->phys + len, माप(hid->phys) - len,
			 "%d", पूर्णांकf->altsetting[0].desc.bInterfaceNumber);

	अगर (usb_string(dev, dev->descriptor.iSerialNumber, hid->uniq, 64) <= 0)
		hid->uniq[0] = 0;

	usbhid = kzalloc(माप(*usbhid), GFP_KERNEL);
	अगर (usbhid == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	hid->driver_data = usbhid;
	usbhid->hid = hid;
	usbhid->पूर्णांकf = पूर्णांकf;
	usbhid->अगरnum = पूर्णांकerface->desc.bInterfaceNumber;

	init_रुकोqueue_head(&usbhid->रुको);
	INIT_WORK(&usbhid->reset_work, hid_reset);
	समयr_setup(&usbhid->io_retry, hid_retry_समयout, 0);
	spin_lock_init(&usbhid->lock);
	mutex_init(&usbhid->mutex);

	ret = hid_add_device(hid);
	अगर (ret) अणु
		अगर (ret != -ENODEV)
			hid_err(पूर्णांकf, "can't add hid device: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;
err_मुक्त:
	kमुक्त(usbhid);
err:
	hid_destroy_device(hid);
	वापस ret;
पूर्ण

अटल व्योम usbhid_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा hid_device *hid = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usbhid_device *usbhid;

	अगर (WARN_ON(!hid))
		वापस;

	usbhid = hid->driver_data;
	spin_lock_irq(&usbhid->lock);	/* Sync with error and led handlers */
	set_bit(HID_DISCONNECTED, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);
	hid_destroy_device(hid);
	kमुक्त(usbhid);
पूर्ण

अटल व्योम hid_cancel_delayed_stuff(काष्ठा usbhid_device *usbhid)
अणु
	del_समयr_sync(&usbhid->io_retry);
	cancel_work_sync(&usbhid->reset_work);
पूर्ण

अटल व्योम hid_cease_io(काष्ठा usbhid_device *usbhid)
अणु
	del_समयr_sync(&usbhid->io_retry);
	usb_समाप्त_urb(usbhid->urbin);
	usb_समाप्त_urb(usbhid->urbctrl);
	usb_समाप्त_urb(usbhid->urbout);
पूर्ण

अटल व्योम hid_restart_io(काष्ठा hid_device *hid)
अणु
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	पूर्णांक clear_halt = test_bit(HID_CLEAR_HALT, &usbhid->iofl);
	पूर्णांक reset_pending = test_bit(HID_RESET_PENDING, &usbhid->iofl);

	spin_lock_irq(&usbhid->lock);
	clear_bit(HID_SUSPENDED, &usbhid->iofl);
	usbhid_mark_busy(usbhid);

	अगर (clear_halt || reset_pending)
		schedule_work(&usbhid->reset_work);
	usbhid->retry_delay = 0;
	spin_unlock_irq(&usbhid->lock);

	अगर (reset_pending || !test_bit(HID_STARTED, &usbhid->iofl))
		वापस;

	अगर (!clear_halt) अणु
		अगर (hid_start_in(hid) < 0)
			hid_io_error(hid);
	पूर्ण

	spin_lock_irq(&usbhid->lock);
	अगर (usbhid->urbout && !test_bit(HID_OUT_RUNNING, &usbhid->iofl))
		usbhid_restart_out_queue(usbhid);
	अगर (!test_bit(HID_CTRL_RUNNING, &usbhid->iofl))
		usbhid_restart_ctrl_queue(usbhid);
	spin_unlock_irq(&usbhid->lock);
पूर्ण

/* Treat USB reset pretty much the same as suspend/resume */
अटल पूर्णांक hid_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा hid_device *hid = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usbhid_device *usbhid = hid->driver_data;

	spin_lock_irq(&usbhid->lock);
	set_bit(HID_RESET_PENDING, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);
	hid_cease_io(usbhid);

	वापस 0;
पूर्ण

/* Same routine used क्रम post_reset and reset_resume */
अटल पूर्णांक hid_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev (पूर्णांकf);
	काष्ठा hid_device *hid = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = पूर्णांकf->cur_altsetting;
	पूर्णांक status;
	अक्षर *rdesc;

	/* Fetch and examine the HID report descriptor. If this
	 * has changed, then rebind. Since usbcore's check of the
	 * configuration descriptors passed, we alपढ़ोy know that
	 * the size of the HID report descriptor has not changed.
	 */
	rdesc = kदो_स्मृति(hid->dev_rsize, GFP_KERNEL);
	अगर (!rdesc)
		वापस -ENOMEM;

	status = hid_get_class_descriptor(dev,
				पूर्णांकerface->desc.bInterfaceNumber,
				HID_DT_REPORT, rdesc, hid->dev_rsize);
	अगर (status < 0) अणु
		dbg_hid("reading report descriptor failed (post_reset)\n");
		kमुक्त(rdesc);
		वापस status;
	पूर्ण
	status = स_भेद(rdesc, hid->dev_rdesc, hid->dev_rsize);
	kमुक्त(rdesc);
	अगर (status != 0) अणु
		dbg_hid("report descriptor changed\n");
		वापस -EPERM;
	पूर्ण

	/* No need to करो another reset or clear a halted endpoपूर्णांक */
	spin_lock_irq(&usbhid->lock);
	clear_bit(HID_RESET_PENDING, &usbhid->iofl);
	clear_bit(HID_CLEAR_HALT, &usbhid->iofl);
	spin_unlock_irq(&usbhid->lock);
	hid_set_idle(dev, पूर्णांकf->cur_altsetting->desc.bInterfaceNumber, 0, 0);

	hid_restart_io(hid);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक hid_resume_common(काष्ठा hid_device *hid, bool driver_suspended)
अणु
	पूर्णांक status = 0;

	hid_restart_io(hid);
	अगर (driver_suspended && hid->driver && hid->driver->resume)
		status = hid->driver->resume(hid);
	वापस status;
पूर्ण

अटल पूर्णांक hid_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा hid_device *hid = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usbhid_device *usbhid = hid->driver_data;
	पूर्णांक status = 0;
	bool driver_suspended = false;
	अचिन्हित पूर्णांक ledcount;

	अगर (PMSG_IS_AUTO(message)) अणु
		ledcount = hidinput_count_leds(hid);
		spin_lock_irq(&usbhid->lock);	/* Sync with error handler */
		अगर (!test_bit(HID_RESET_PENDING, &usbhid->iofl)
		    && !test_bit(HID_CLEAR_HALT, &usbhid->iofl)
		    && !test_bit(HID_OUT_RUNNING, &usbhid->iofl)
		    && !test_bit(HID_CTRL_RUNNING, &usbhid->iofl)
		    && !test_bit(HID_KEYS_PRESSED, &usbhid->iofl)
		    && (!ledcount || ignoreled))
		अणु
			set_bit(HID_SUSPENDED, &usbhid->iofl);
			spin_unlock_irq(&usbhid->lock);
			अगर (hid->driver && hid->driver->suspend) अणु
				status = hid->driver->suspend(hid, message);
				अगर (status < 0)
					जाओ failed;
			पूर्ण
			driver_suspended = true;
		पूर्ण अन्यथा अणु
			usbhid_mark_busy(usbhid);
			spin_unlock_irq(&usbhid->lock);
			वापस -EBUSY;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* TODO: resume() might need to handle suspend failure */
		अगर (hid->driver && hid->driver->suspend)
			status = hid->driver->suspend(hid, message);
		driver_suspended = true;
		spin_lock_irq(&usbhid->lock);
		set_bit(HID_SUSPENDED, &usbhid->iofl);
		spin_unlock_irq(&usbhid->lock);
		अगर (usbhid_रुको_io(hid) < 0)
			status = -EIO;
	पूर्ण

	hid_cancel_delayed_stuff(usbhid);
	hid_cease_io(usbhid);

	अगर (PMSG_IS_AUTO(message) && test_bit(HID_KEYS_PRESSED, &usbhid->iofl)) अणु
		/* lost race against keypresses */
		status = -EBUSY;
		जाओ failed;
	पूर्ण
	dev_dbg(&पूर्णांकf->dev, "suspend\n");
	वापस status;

 failed:
	hid_resume_common(hid, driver_suspended);
	वापस status;
पूर्ण

अटल पूर्णांक hid_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा hid_device *hid = usb_get_पूर्णांकfdata (पूर्णांकf);
	पूर्णांक status;

	status = hid_resume_common(hid, true);
	dev_dbg(&पूर्णांकf->dev, "resume status %d\n", status);
	वापस 0;
पूर्ण

अटल पूर्णांक hid_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा hid_device *hid = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक status;

	status = hid_post_reset(पूर्णांकf);
	अगर (status >= 0 && hid->driver && hid->driver->reset_resume) अणु
		पूर्णांक ret = hid->driver->reset_resume(hid);
		अगर (ret < 0)
			status = ret;
	पूर्ण
	वापस status;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा usb_device_id hid_usb_ids[] = अणु
	अणु .match_flags = USB_DEVICE_ID_MATCH_INT_CLASS,
		.bInterfaceClass = USB_INTERFACE_CLASS_HID पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, hid_usb_ids);

अटल काष्ठा usb_driver hid_driver = अणु
	.name =		"usbhid",
	.probe =	usbhid_probe,
	.disconnect =	usbhid_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend =	hid_suspend,
	.resume =	hid_resume,
	.reset_resume =	hid_reset_resume,
#पूर्ण_अगर
	.pre_reset =	hid_pre_reset,
	.post_reset =	hid_post_reset,
	.id_table =	hid_usb_ids,
	.supports_स्वतःsuspend = 1,
पूर्ण;

काष्ठा usb_पूर्णांकerface *usbhid_find_पूर्णांकerface(पूर्णांक minor)
अणु
	वापस usb_find_पूर्णांकerface(&hid_driver, minor);
पूर्ण

अटल पूर्णांक __init hid_init(व्योम)
अणु
	पूर्णांक retval;

	retval = hid_quirks_init(quirks_param, BUS_USB, MAX_USBHID_BOOT_QUIRKS);
	अगर (retval)
		जाओ usbhid_quirks_init_fail;
	retval = usb_रेजिस्टर(&hid_driver);
	अगर (retval)
		जाओ usb_रेजिस्टर_fail;
	pr_info(KBUILD_MODNAME ": " DRIVER_DESC "\n");

	वापस 0;
usb_रेजिस्टर_fail:
	hid_quirks_निकास(BUS_USB);
usbhid_quirks_init_fail:
	वापस retval;
पूर्ण

अटल व्योम __निकास hid_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&hid_driver);
	hid_quirks_निकास(BUS_USB);
पूर्ण

module_init(hid_init);
module_निकास(hid_निकास);

MODULE_AUTHOR("Andreas Gal");
MODULE_AUTHOR("Vojtech Pavlik");
MODULE_AUTHOR("Jiri Kosina");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
