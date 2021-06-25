<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dbgp.c -- EHCI Debug Port device gadget
 *
 * Copyright (C) 2010 Stephane Duverger
 *
 * Released under the GPLv2.
 */

/* verbose messages */
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>

#समावेश "u_serial.h"

#घोषणा DRIVER_VENDOR_ID	0x0525 /* NetChip */
#घोषणा DRIVER_PRODUCT_ID	0xc0de /* undefined */

#घोषणा USB_DEBUG_MAX_PACKET_SIZE     8
#घोषणा DBGP_REQ_EP0_LEN              128
#घोषणा DBGP_REQ_LEN                  512

अटल काष्ठा dbgp अणु
	काष्ठा usb_gadget  *gadget;
	काष्ठा usb_request *req;
	काष्ठा usb_ep      *i_ep;
	काष्ठा usb_ep      *o_ep;
#अगर_घोषित CONFIG_USB_G_DBGP_SERIAL
	काष्ठा gserial     *serial;
#पूर्ण_अगर
पूर्ण dbgp;

अटल काष्ठा usb_device_descriptor device_desc = अणु
	.bLength = माप device_desc,
	.bDescriptorType = USB_DT_DEVICE,
	.bcdUSB = cpu_to_le16(0x0200),
	.bDeviceClass =	USB_CLASS_VENDOR_SPEC,
	.idVenकरोr = cpu_to_le16(DRIVER_VENDOR_ID),
	.idProduct = cpu_to_le16(DRIVER_PRODUCT_ID),
	.bNumConfigurations = 1,
पूर्ण;

अटल काष्ठा usb_debug_descriptor dbg_desc = अणु
	.bLength = माप dbg_desc,
	.bDescriptorType = USB_DT_DEBUG,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor i_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bmAttributes = USB_ENDPOINT_XFER_BULK,
	.bEndpoपूर्णांकAddress = USB_सूची_IN,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor o_desc = अणु
	.bLength = USB_DT_ENDPOINT_SIZE,
	.bDescriptorType = USB_DT_ENDPOINT,
	.bmAttributes = USB_ENDPOINT_XFER_BULK,
	.bEndpoपूर्णांकAddress = USB_सूची_OUT,
पूर्ण;

#अगर_घोषित CONFIG_USB_G_DBGP_PRINTK
अटल पूर्णांक dbgp_consume(अक्षर *buf, अचिन्हित len)
अणु
	अक्षर c;

	अगर (!len)
		वापस 0;

	c = buf[len-1];
	अगर (c != 0)
		buf[len-1] = 0;

	prपूर्णांकk(KERN_NOTICE "%s%c", buf, c);
	वापस 0;
पूर्ण

अटल व्योम __disable_ep(काष्ठा usb_ep *ep)
अणु
	usb_ep_disable(ep);
पूर्ण

अटल व्योम dbgp_disable_ep(व्योम)
अणु
	__disable_ep(dbgp.i_ep);
	__disable_ep(dbgp.o_ep);
पूर्ण

अटल व्योम dbgp_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	पूर्णांक stp;
	पूर्णांक err = 0;
	पूर्णांक status = req->status;

	अगर (ep == dbgp.i_ep) अणु
		stp = 1;
		जाओ fail;
	पूर्ण

	अगर (status != 0) अणु
		stp = 2;
		जाओ release_req;
	पूर्ण

	dbgp_consume(req->buf, req->actual);

	req->length = DBGP_REQ_LEN;
	err = usb_ep_queue(ep, req, GFP_ATOMIC);
	अगर (err < 0) अणु
		stp = 3;
		जाओ release_req;
	पूर्ण

	वापस;

release_req:
	kमुक्त(req->buf);
	usb_ep_मुक्त_request(dbgp.o_ep, req);
	dbgp_disable_ep();
fail:
	dev_dbg(&dbgp.gadget->dev,
		"complete: failure (%d:%d) ==> %d\n", stp, err, status);
पूर्ण

अटल पूर्णांक dbgp_enable_ep_req(काष्ठा usb_ep *ep)
अणु
	पूर्णांक err, stp;
	काष्ठा usb_request *req;

	req = usb_ep_alloc_request(ep, GFP_KERNEL);
	अगर (!req) अणु
		err = -ENOMEM;
		stp = 1;
		जाओ fail_1;
	पूर्ण

	req->buf = kदो_स्मृति(DBGP_REQ_LEN, GFP_KERNEL);
	अगर (!req->buf) अणु
		err = -ENOMEM;
		stp = 2;
		जाओ fail_2;
	पूर्ण

	req->complete = dbgp_complete;
	req->length = DBGP_REQ_LEN;
	err = usb_ep_queue(ep, req, GFP_ATOMIC);
	अगर (err < 0) अणु
		stp = 3;
		जाओ fail_3;
	पूर्ण

	वापस 0;

fail_3:
	kमुक्त(req->buf);
fail_2:
	usb_ep_मुक्त_request(dbgp.o_ep, req);
fail_1:
	dev_dbg(&dbgp.gadget->dev,
		"enable ep req: failure (%d:%d)\n", stp, err);
	वापस err;
पूर्ण

अटल पूर्णांक __enable_ep(काष्ठा usb_ep *ep, काष्ठा usb_endpoपूर्णांक_descriptor *desc)
अणु
	पूर्णांक err;
	ep->desc = desc;
	err = usb_ep_enable(ep);
	वापस err;
पूर्ण

अटल पूर्णांक dbgp_enable_ep(व्योम)
अणु
	पूर्णांक err, stp;

	err = __enable_ep(dbgp.i_ep, &i_desc);
	अगर (err < 0) अणु
		stp = 1;
		जाओ fail_1;
	पूर्ण

	err = __enable_ep(dbgp.o_ep, &o_desc);
	अगर (err < 0) अणु
		stp = 2;
		जाओ fail_2;
	पूर्ण

	err = dbgp_enable_ep_req(dbgp.o_ep);
	अगर (err < 0) अणु
		stp = 3;
		जाओ fail_3;
	पूर्ण

	वापस 0;

fail_3:
	__disable_ep(dbgp.o_ep);
fail_2:
	__disable_ep(dbgp.i_ep);
fail_1:
	dev_dbg(&dbgp.gadget->dev, "enable ep: failure (%d:%d)\n", stp, err);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल व्योम dbgp_disconnect(काष्ठा usb_gadget *gadget)
अणु
#अगर_घोषित CONFIG_USB_G_DBGP_PRINTK
	dbgp_disable_ep();
#अन्यथा
	gserial_disconnect(dbgp.serial);
#पूर्ण_अगर
पूर्ण

अटल व्योम dbgp_unbind(काष्ठा usb_gadget *gadget)
अणु
#अगर_घोषित CONFIG_USB_G_DBGP_SERIAL
	kमुक्त(dbgp.serial);
	dbgp.serial = शून्य;
#पूर्ण_अगर
	अगर (dbgp.req) अणु
		kमुक्त(dbgp.req->buf);
		usb_ep_मुक्त_request(gadget->ep0, dbgp.req);
		dbgp.req = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_USB_G_DBGP_SERIAL
अटल अचिन्हित अक्षर tty_line;
#पूर्ण_अगर

अटल पूर्णांक dbgp_configure_endpoपूर्णांकs(काष्ठा usb_gadget *gadget)
अणु
	पूर्णांक stp;

	usb_ep_स्वतःconfig_reset(gadget);

	dbgp.i_ep = usb_ep_स्वतःconfig(gadget, &i_desc);
	अगर (!dbgp.i_ep) अणु
		stp = 1;
		जाओ fail_1;
	पूर्ण

	i_desc.wMaxPacketSize =
		cpu_to_le16(USB_DEBUG_MAX_PACKET_SIZE);

	dbgp.o_ep = usb_ep_स्वतःconfig(gadget, &o_desc);
	अगर (!dbgp.o_ep) अणु
		stp = 2;
		जाओ fail_1;
	पूर्ण

	o_desc.wMaxPacketSize =
		cpu_to_le16(USB_DEBUG_MAX_PACKET_SIZE);

	dbg_desc.bDebugInEndpoपूर्णांक = i_desc.bEndpoपूर्णांकAddress;
	dbg_desc.bDebugOutEndpoपूर्णांक = o_desc.bEndpoपूर्णांकAddress;

#अगर_घोषित CONFIG_USB_G_DBGP_SERIAL
	dbgp.serial->in = dbgp.i_ep;
	dbgp.serial->out = dbgp.o_ep;

	dbgp.serial->in->desc = &i_desc;
	dbgp.serial->out->desc = &o_desc;
#पूर्ण_अगर

	वापस 0;

fail_1:
	dev_dbg(&dbgp.gadget->dev, "ep config: failure (%d)\n", stp);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक dbgp_bind(काष्ठा usb_gadget *gadget,
		काष्ठा usb_gadget_driver *driver)
अणु
	पूर्णांक err, stp;

	dbgp.gadget = gadget;

	dbgp.req = usb_ep_alloc_request(gadget->ep0, GFP_KERNEL);
	अगर (!dbgp.req) अणु
		err = -ENOMEM;
		stp = 1;
		जाओ fail;
	पूर्ण

	dbgp.req->buf = kदो_स्मृति(DBGP_REQ_EP0_LEN, GFP_KERNEL);
	अगर (!dbgp.req->buf) अणु
		err = -ENOMEM;
		stp = 2;
		जाओ fail;
	पूर्ण

	dbgp.req->length = DBGP_REQ_EP0_LEN;

#अगर_घोषित CONFIG_USB_G_DBGP_SERIAL
	dbgp.serial = kzalloc(माप(काष्ठा gserial), GFP_KERNEL);
	अगर (!dbgp.serial) अणु
		stp = 3;
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	अगर (gserial_alloc_line(&tty_line)) अणु
		stp = 4;
		err = -ENODEV;
		जाओ fail;
	पूर्ण
#पूर्ण_अगर

	err = dbgp_configure_endpoपूर्णांकs(gadget);
	अगर (err < 0) अणु
		stp = 5;
		जाओ fail;
	पूर्ण

	dev_dbg(&dbgp.gadget->dev, "bind: success\n");
	वापस 0;

fail:
	dev_dbg(&gadget->dev, "bind: failure (%d:%d)\n", stp, err);
	dbgp_unbind(gadget);
	वापस err;
पूर्ण

अटल व्योम dbgp_setup_complete(काष्ठा usb_ep *ep,
				काष्ठा usb_request *req)
अणु
	dev_dbg(&dbgp.gadget->dev, "setup complete: %d, %d/%d\n",
		req->status, req->actual, req->length);
पूर्ण

अटल पूर्णांक dbgp_setup(काष्ठा usb_gadget *gadget,
		      स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usb_request *req = dbgp.req;
	u8 request = ctrl->bRequest;
	u16 value = le16_to_cpu(ctrl->wValue);
	u16 length = le16_to_cpu(ctrl->wLength);
	पूर्णांक err = -EOPNOTSUPP;
	व्योम *data = शून्य;
	u16 len = 0;

	अगर (request == USB_REQ_GET_DESCRIPTOR) अणु
		चयन (value>>8) अणु
		हाल USB_DT_DEVICE:
			dev_dbg(&dbgp.gadget->dev, "setup: desc device\n");
			len = माप device_desc;
			data = &device_desc;
			device_desc.bMaxPacketSize0 = gadget->ep0->maxpacket;
			अवरोध;
		हाल USB_DT_DEBUG:
			dev_dbg(&dbgp.gadget->dev, "setup: desc debug\n");
			len = माप dbg_desc;
			data = &dbg_desc;
			अवरोध;
		शेष:
			जाओ fail;
		पूर्ण
		err = 0;
	पूर्ण अन्यथा अगर (request == USB_REQ_SET_FEATURE &&
		   value == USB_DEVICE_DEBUG_MODE) अणु
		dev_dbg(&dbgp.gadget->dev, "setup: feat debug\n");
#अगर_घोषित CONFIG_USB_G_DBGP_PRINTK
		err = dbgp_enable_ep();
#अन्यथा
		err = dbgp_configure_endpoपूर्णांकs(gadget);
		अगर (err < 0) अणु
			जाओ fail;
		पूर्ण
		err = gserial_connect(dbgp.serial, tty_line);
#पूर्ण_अगर
		अगर (err < 0)
			जाओ fail;
	पूर्ण अन्यथा
		जाओ fail;

	req->length = min(length, len);
	req->zero = len < req->length;
	अगर (data && req->length)
		स_नकल(req->buf, data, req->length);

	req->complete = dbgp_setup_complete;
	वापस usb_ep_queue(gadget->ep0, req, GFP_ATOMIC);

fail:
	dev_dbg(&dbgp.gadget->dev,
		"setup: failure req %x v %x\n", request, value);
	वापस err;
पूर्ण

अटल काष्ठा usb_gadget_driver dbgp_driver = अणु
	.function = "dbgp",
	.max_speed = USB_SPEED_HIGH,
	.bind = dbgp_bind,
	.unbind = dbgp_unbind,
	.setup = dbgp_setup,
	.reset = dbgp_disconnect,
	.disconnect = dbgp_disconnect,
	.driver	= अणु
		.owner = THIS_MODULE,
		.name = "dbgp"
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dbgp_init(व्योम)
अणु
	वापस usb_gadget_probe_driver(&dbgp_driver);
पूर्ण

अटल व्योम __निकास dbgp_निकास(व्योम)
अणु
	usb_gadget_unरेजिस्टर_driver(&dbgp_driver);
#अगर_घोषित CONFIG_USB_G_DBGP_SERIAL
	gserial_मुक्त_line(tty_line);
#पूर्ण_अगर
पूर्ण

MODULE_AUTHOR("Stephane Duverger");
MODULE_LICENSE("GPL");
module_init(dbgp_init);
module_निकास(dbgp_निकास);
