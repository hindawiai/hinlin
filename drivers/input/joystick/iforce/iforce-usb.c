<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /*
 *  Copyright (c) 2000-2002 Vojtech Pavlik <vojtech@ucw.cz>
 *  Copyright (c) 2001-2002, 2007 Johann Deneux <johann.deneux@gmail.com>
 *
 *  USB/RS232 I-Force joysticks and wheels.
 */

#समावेश <linux/usb.h>
#समावेश "iforce.h"

काष्ठा अगरorce_usb अणु
	काष्ठा अगरorce अगरorce;

	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा urb *irq, *out;

	u8 data_in[IFORCE_MAX_LENGTH] ____cacheline_aligned;
	u8 data_out[IFORCE_MAX_LENGTH] ____cacheline_aligned;
पूर्ण;

अटल व्योम __अगरorce_usb_xmit(काष्ठा अगरorce *अगरorce)
अणु
	काष्ठा अगरorce_usb *अगरorce_usb = container_of(अगरorce, काष्ठा अगरorce_usb,
						     अगरorce);
	पूर्णांक n, c;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&अगरorce->xmit_lock, flags);

	अगर (अगरorce->xmit.head == अगरorce->xmit.tail) अणु
		clear_bit(IFORCE_XMIT_RUNNING, अगरorce->xmit_flags);
		spin_unlock_irqrestore(&अगरorce->xmit_lock, flags);
		वापस;
	पूर्ण

	((अक्षर *)अगरorce_usb->out->transfer_buffer)[0] = अगरorce->xmit.buf[अगरorce->xmit.tail];
	XMIT_INC(अगरorce->xmit.tail, 1);
	n = अगरorce->xmit.buf[अगरorce->xmit.tail];
	XMIT_INC(अगरorce->xmit.tail, 1);

	अगरorce_usb->out->transfer_buffer_length = n + 1;
	अगरorce_usb->out->dev = अगरorce_usb->usbdev;

	/* Copy rest of data then */
	c = CIRC_CNT_TO_END(अगरorce->xmit.head, अगरorce->xmit.tail, XMIT_SIZE);
	अगर (n < c) c=n;

	स_नकल(अगरorce_usb->out->transfer_buffer + 1,
	       &अगरorce->xmit.buf[अगरorce->xmit.tail],
	       c);
	अगर (n != c) अणु
		स_नकल(अगरorce_usb->out->transfer_buffer + 1 + c,
		       &अगरorce->xmit.buf[0],
		       n-c);
	पूर्ण
	XMIT_INC(अगरorce->xmit.tail, n);

	अगर ( (n=usb_submit_urb(अगरorce_usb->out, GFP_ATOMIC)) ) अणु
		clear_bit(IFORCE_XMIT_RUNNING, अगरorce->xmit_flags);
		dev_warn(&अगरorce_usb->पूर्णांकf->dev,
			 "usb_submit_urb failed %d\n", n);
	पूर्ण

	/* The IFORCE_XMIT_RUNNING bit is not cleared here. That's पूर्णांकended.
	 * As दीर्घ as the urb completion handler is not called, the transmiting
	 * is considered to be running */
	spin_unlock_irqrestore(&अगरorce->xmit_lock, flags);
पूर्ण

अटल व्योम अगरorce_usb_xmit(काष्ठा अगरorce *अगरorce)
अणु
	अगर (!test_and_set_bit(IFORCE_XMIT_RUNNING, अगरorce->xmit_flags))
		__अगरorce_usb_xmit(अगरorce);
पूर्ण

अटल पूर्णांक अगरorce_usb_get_id(काष्ठा अगरorce *अगरorce, u8 id,
			     u8 *response_data, माप_प्रकार *response_len)
अणु
	काष्ठा अगरorce_usb *अगरorce_usb = container_of(अगरorce, काष्ठा अगरorce_usb,
						     अगरorce);
	u8 *buf;
	पूर्णांक status;

	buf = kदो_स्मृति(IFORCE_MAX_LENGTH, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	status = usb_control_msg(अगरorce_usb->usbdev,
				 usb_rcvctrlpipe(अगरorce_usb->usbdev, 0),
				 id,
				 USB_TYPE_VENDOR | USB_सूची_IN |
					USB_RECIP_INTERFACE,
				 0, 0, buf, IFORCE_MAX_LENGTH, HZ);
	अगर (status < 0) अणु
		dev_err(&अगरorce_usb->पूर्णांकf->dev,
			"usb_submit_urb failed: %d\n", status);
	पूर्ण अन्यथा अगर (buf[0] != id) अणु
		status = -EIO;
	पूर्ण अन्यथा अणु
		स_नकल(response_data, buf, status);
		*response_len = status;
		status = 0;
	पूर्ण

	kमुक्त(buf);
	वापस status;
पूर्ण

अटल पूर्णांक अगरorce_usb_start_io(काष्ठा अगरorce *अगरorce)
अणु
	काष्ठा अगरorce_usb *अगरorce_usb = container_of(अगरorce, काष्ठा अगरorce_usb,
						     अगरorce);

	अगर (usb_submit_urb(अगरorce_usb->irq, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम अगरorce_usb_stop_io(काष्ठा अगरorce *अगरorce)
अणु
	काष्ठा अगरorce_usb *अगरorce_usb = container_of(अगरorce, काष्ठा अगरorce_usb,
						     अगरorce);

	usb_समाप्त_urb(अगरorce_usb->irq);
	usb_समाप्त_urb(अगरorce_usb->out);
पूर्ण

अटल स्थिर काष्ठा अगरorce_xport_ops अगरorce_usb_xport_ops = अणु
	.xmit		= अगरorce_usb_xmit,
	.get_id		= अगरorce_usb_get_id,
	.start_io	= अगरorce_usb_start_io,
	.stop_io	= अगरorce_usb_stop_io,
पूर्ण;

अटल व्योम अगरorce_usb_irq(काष्ठा urb *urb)
अणु
	काष्ठा अगरorce_usb *अगरorce_usb = urb->context;
	काष्ठा अगरorce *अगरorce = &अगरorce_usb->अगरorce;
	काष्ठा device *dev = &अगरorce_usb->पूर्णांकf->dev;
	पूर्णांक status;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d\n",
			__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(dev, "%s - urb has status of: %d\n",
			__func__, urb->status);
		जाओ निकास;
	पूर्ण

	अगरorce_process_packet(अगरorce, अगरorce_usb->data_in[0],
			      अगरorce_usb->data_in + 1, urb->actual_length - 1);

निकास:
	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status)
		dev_err(dev, "%s - usb_submit_urb failed with result %d\n",
			__func__, status);
पूर्ण

अटल व्योम अगरorce_usb_out(काष्ठा urb *urb)
अणु
	काष्ठा अगरorce_usb *अगरorce_usb = urb->context;
	काष्ठा अगरorce *अगरorce = &अगरorce_usb->अगरorce;

	अगर (urb->status) अणु
		clear_bit(IFORCE_XMIT_RUNNING, अगरorce->xmit_flags);
		dev_dbg(&अगरorce_usb->पूर्णांकf->dev, "urb->status %d, exiting\n",
			urb->status);
		वापस;
	पूर्ण

	__अगरorce_usb_xmit(अगरorce);

	wake_up(&अगरorce->रुको);
पूर्ण

अटल पूर्णांक अगरorce_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *epirq, *epout;
	काष्ठा अगरorce_usb *अगरorce_usb;
	पूर्णांक err = -ENOMEM;

	पूर्णांकerface = पूर्णांकf->cur_altsetting;

	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs < 2)
		वापस -ENODEV;

	epirq = &पूर्णांकerface->endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(epirq))
		वापस -ENODEV;

	epout = &पूर्णांकerface->endpoपूर्णांक[1].desc;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_out(epout))
		वापस -ENODEV;

	अगरorce_usb = kzalloc(माप(*अगरorce_usb), GFP_KERNEL);
	अगर (!अगरorce_usb)
		जाओ fail;

	अगरorce_usb->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!अगरorce_usb->irq)
		जाओ fail;

	अगरorce_usb->out = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!अगरorce_usb->out)
		जाओ fail;

	अगरorce_usb->अगरorce.xport_ops = &अगरorce_usb_xport_ops;

	अगरorce_usb->usbdev = dev;
	अगरorce_usb->पूर्णांकf = पूर्णांकf;

	usb_fill_पूर्णांक_urb(अगरorce_usb->irq, dev,
			 usb_rcvपूर्णांकpipe(dev, epirq->bEndpoपूर्णांकAddress),
			 अगरorce_usb->data_in, माप(अगरorce_usb->data_in),
			 अगरorce_usb_irq, अगरorce_usb, epirq->bInterval);

	usb_fill_पूर्णांक_urb(अगरorce_usb->out, dev,
			 usb_sndपूर्णांकpipe(dev, epout->bEndpoपूर्णांकAddress),
			 अगरorce_usb->data_out, माप(अगरorce_usb->data_out),
			 अगरorce_usb_out, अगरorce_usb, epout->bInterval);

	err = अगरorce_init_device(&पूर्णांकf->dev, BUS_USB, &अगरorce_usb->अगरorce);
	अगर (err)
		जाओ fail;

	usb_set_पूर्णांकfdata(पूर्णांकf, अगरorce_usb);
	वापस 0;

fail:
	अगर (अगरorce_usb) अणु
		usb_मुक्त_urb(अगरorce_usb->irq);
		usb_मुक्त_urb(अगरorce_usb->out);
		kमुक्त(अगरorce_usb);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम अगरorce_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा अगरorce_usb *अगरorce_usb = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	input_unरेजिस्टर_device(अगरorce_usb->अगरorce.dev);

	usb_मुक्त_urb(अगरorce_usb->irq);
	usb_मुक्त_urb(अगरorce_usb->out);

	kमुक्त(अगरorce_usb);
पूर्ण

अटल स्थिर काष्ठा usb_device_id अगरorce_usb_ids[] = अणु
	अणु USB_DEVICE(0x044f, 0xa01c) पूर्ण,		/* Thrusपंचांगaster Motor Sport GT */
	अणु USB_DEVICE(0x046d, 0xc281) पूर्ण,		/* Logitech WingMan Force */
	अणु USB_DEVICE(0x046d, 0xc291) पूर्ण,		/* Logitech WingMan Formula Force */
	अणु USB_DEVICE(0x05ef, 0x020a) पूर्ण,		/* AVB Top Shot Pegasus */
	अणु USB_DEVICE(0x05ef, 0x8884) पूर्ण,		/* AVB Mag Turbo Force */
	अणु USB_DEVICE(0x05ef, 0x8888) पूर्ण,		/* AVB Top Shot FFB Racing Wheel */
	अणु USB_DEVICE(0x061c, 0xc0a4) पूर्ण,         /* ACT LABS Force RS */
	अणु USB_DEVICE(0x061c, 0xc084) पूर्ण,         /* ACT LABS Force RS */
	अणु USB_DEVICE(0x06a3, 0xff04) पूर्ण,		/* Saitek R440 Force Wheel */
	अणु USB_DEVICE(0x06f8, 0x0001) पूर्ण,		/* Guillemot Race Leader Force Feedback */
	अणु USB_DEVICE(0x06f8, 0x0003) पूर्ण,		/* Guillemot Jet Leader Force Feedback */
	अणु USB_DEVICE(0x06f8, 0x0004) पूर्ण,		/* Guillemot Force Feedback Racing Wheel */
	अणु USB_DEVICE(0x06f8, 0xa302) पूर्ण,		/* Guillemot Jet Leader 3D */
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, अगरorce_usb_ids);

काष्ठा usb_driver अगरorce_usb_driver = अणु
	.name =		"iforce",
	.probe =	अगरorce_usb_probe,
	.disconnect =	अगरorce_usb_disconnect,
	.id_table =	अगरorce_usb_ids,
पूर्ण;

module_usb_driver(अगरorce_usb_driver);

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>, Johann Deneux <johann.deneux@gmail.com>");
MODULE_DESCRIPTION("USB I-Force joysticks and wheels driver");
MODULE_LICENSE("GPL");
