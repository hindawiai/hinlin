<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IgorPlug-USB IR Receiver
 *
 * Copyright (C) 2014 Sean Young <sean@mess.org>
 *
 * Supports the standard homebrew IgorPlugUSB receiver with Igor's firmware.
 * See http://www.cesko.host.sk/IgorPlugUSB/IgorPlug-USB%20(AVR)_eng.hपंचांग
 *
 * Based on the lirc_igorplugusb.c driver:
 *	Copyright (C) 2004 Jan M. Hochstein
 *	<hochstein@algo.inक्रमmatik.tu-darmstadt.de>
 */
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <media/rc-core.h>

#घोषणा DRIVER_DESC		"IgorPlug-USB IR Receiver"
#घोषणा DRIVER_NAME		"igorplugusb"

#घोषणा HEADERLEN		3
#घोषणा BUFLEN			36
#घोषणा MAX_PACKET		(HEADERLEN + BUFLEN)

#घोषणा SET_INFRABUFFER_EMPTY	1
#घोषणा GET_INFRACODE		2


काष्ठा igorplugusb अणु
	काष्ठा rc_dev *rc;
	काष्ठा device *dev;

	काष्ठा urb *urb;
	काष्ठा usb_ctrlrequest request;

	काष्ठा समयr_list समयr;

	uपूर्णांक8_t buf_in[MAX_PACKET];

	अक्षर phys[64];
पूर्ण;

अटल व्योम igorplugusb_cmd(काष्ठा igorplugusb *ir, पूर्णांक cmd);

अटल व्योम igorplugusb_irdata(काष्ठा igorplugusb *ir, अचिन्हित len)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	अचिन्हित i, start, overflow;

	dev_dbg(ir->dev, "irdata: %*ph (len=%u)", len, ir->buf_in, len);

	/*
	 * If more than 36 pulses and spaces follow each other, the igorplugusb
	 * overग_लिखोs its buffer from the beginning. The overflow value is the
	 * last offset which was not overwritten. Everything from this offset
	 * onwards occurred beक्रमe everything until this offset.
	 */
	overflow = ir->buf_in[2];
	i = start = overflow + HEADERLEN;

	अगर (start >= len) अणु
		dev_err(ir->dev, "receive overflow invalid: %u", overflow);
	पूर्ण अन्यथा अणु
		अगर (overflow > 0)
			dev_warn(ir->dev, "receive overflow, at least %u lost",
								overflow);

		करो अणु
			rawir.duration = ir->buf_in[i] * 85;
			rawir.pulse = i & 1;

			ir_raw_event_store_with_filter(ir->rc, &rawir);

			अगर (++i == len)
				i = HEADERLEN;
		पूर्ण जबतक (i != start);

		/* add a trailing space */
		rawir.duration = ir->rc->समयout;
		rawir.pulse = false;
		ir_raw_event_store_with_filter(ir->rc, &rawir);

		ir_raw_event_handle(ir->rc);
	पूर्ण

	igorplugusb_cmd(ir, SET_INFRABUFFER_EMPTY);
पूर्ण

अटल व्योम igorplugusb_callback(काष्ठा urb *urb)
अणु
	काष्ठा usb_ctrlrequest *req;
	काष्ठा igorplugusb *ir = urb->context;

	req = (काष्ठा usb_ctrlrequest *)urb->setup_packet;

	चयन (urb->status) अणु
	हाल 0:
		अगर (req->bRequest == GET_INFRACODE &&
					urb->actual_length > HEADERLEN)
			igorplugusb_irdata(ir, urb->actual_length);
		अन्यथा /* request IR */
			mod_समयr(&ir->समयr, jअगरfies + msecs_to_jअगरfies(50));
		अवरोध;
	हाल -EPROTO:
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		usb_unlink_urb(urb);
		वापस;
	शेष:
		dev_warn(ir->dev, "Error: urb status = %d\n", urb->status);
		igorplugusb_cmd(ir, SET_INFRABUFFER_EMPTY);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम igorplugusb_cmd(काष्ठा igorplugusb *ir, पूर्णांक cmd)
अणु
	पूर्णांक ret;

	ir->request.bRequest = cmd;
	ir->urb->transfer_flags = 0;
	ret = usb_submit_urb(ir->urb, GFP_ATOMIC);
	अगर (ret)
		dev_err(ir->dev, "submit urb failed: %d", ret);
पूर्ण

अटल व्योम igorplugusb_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा igorplugusb *ir = from_समयr(ir, t, समयr);

	igorplugusb_cmd(ir, GET_INFRACODE);
पूर्ण

अटल पूर्णांक igorplugusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
					स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_host_पूर्णांकerface *idesc;
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	काष्ठा igorplugusb *ir;
	काष्ठा rc_dev *rc;
	पूर्णांक ret = -ENOMEM;

	udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	idesc = पूर्णांकf->cur_altsetting;

	अगर (idesc->desc.bNumEndpoपूर्णांकs != 1) अणु
		dev_err(&पूर्णांकf->dev, "incorrect number of endpoints");
		वापस -ENODEV;
	पूर्ण

	ep = &idesc->endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_dir_in(ep) || !usb_endpoपूर्णांक_xfer_control(ep)) अणु
		dev_err(&पूर्णांकf->dev, "endpoint incorrect");
		वापस -ENODEV;
	पूर्ण

	ir = devm_kzalloc(&पूर्णांकf->dev, माप(*ir), GFP_KERNEL);
	अगर (!ir)
		वापस -ENOMEM;

	ir->dev = &पूर्णांकf->dev;

	समयr_setup(&ir->समयr, igorplugusb_समयr, 0);

	ir->request.bRequest = GET_INFRACODE;
	ir->request.bRequestType = USB_TYPE_VENDOR | USB_सूची_IN;
	ir->request.wLength = cpu_to_le16(माप(ir->buf_in));

	ir->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!ir->urb)
		जाओ fail;

	usb_fill_control_urb(ir->urb, udev,
		usb_rcvctrlpipe(udev, 0), (uपूर्णांक8_t *)&ir->request,
		ir->buf_in, माप(ir->buf_in), igorplugusb_callback, ir);

	usb_make_path(udev, ir->phys, माप(ir->phys));

	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rc)
		जाओ fail;

	rc->device_name = DRIVER_DESC;
	rc->input_phys = ir->phys;
	usb_to_input_id(udev, &rc->input_id);
	rc->dev.parent = &पूर्णांकf->dev;
	/*
	 * This device can only store 36 pulses + spaces, which is not enough
	 * क्रम the NEC protocol and many others.
	 */
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER &
		~(RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32 |
		  RC_PROTO_BIT_RC6_6A_20 | RC_PROTO_BIT_RC6_6A_24 |
		  RC_PROTO_BIT_RC6_6A_32 | RC_PROTO_BIT_RC6_MCE |
		  RC_PROTO_BIT_SONY20 | RC_PROTO_BIT_SANYO);

	rc->priv = ir;
	rc->driver_name = DRIVER_NAME;
	rc->map_name = RC_MAP_HAUPPAUGE;
	rc->समयout = MS_TO_US(100);
	rc->rx_resolution = 85;

	ir->rc = rc;
	ret = rc_रेजिस्टर_device(rc);
	अगर (ret) अणु
		dev_err(&पूर्णांकf->dev, "failed to register rc device: %d", ret);
		जाओ fail;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, ir);

	igorplugusb_cmd(ir, SET_INFRABUFFER_EMPTY);

	वापस 0;
fail:
	rc_मुक्त_device(ir->rc);
	usb_मुक्त_urb(ir->urb);
	del_समयr(&ir->समयr);

	वापस ret;
पूर्ण

अटल व्योम igorplugusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा igorplugusb *ir = usb_get_पूर्णांकfdata(पूर्णांकf);

	rc_unरेजिस्टर_device(ir->rc);
	del_समयr_sync(&ir->समयr);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	usb_समाप्त_urb(ir->urb);
	usb_मुक्त_urb(ir->urb);
पूर्ण

अटल स्थिर काष्ठा usb_device_id igorplugusb_table[] = अणु
	/* Igor Plug USB (Aपंचांगel's Manufact. ID) */
	अणु USB_DEVICE(0x03eb, 0x0002) पूर्ण,
	/* Fit PC2 Infrared Adapter */
	अणु USB_DEVICE(0x03eb, 0x21fe) पूर्ण,
	/* Terminating entry */
	अणु पूर्ण
पूर्ण;

अटल काष्ठा usb_driver igorplugusb_driver = अणु
	.name =	DRIVER_NAME,
	.probe = igorplugusb_probe,
	.disconnect = igorplugusb_disconnect,
	.id_table = igorplugusb_table
पूर्ण;

module_usb_driver(igorplugusb_driver);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(usb, igorplugusb_table);
