<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_acm.c -- USB CDC serial (ACM) function driver
 *
 * Copyright (C) 2003 Al Borchers (alborchers@steinerpoपूर्णांक.com)
 * Copyright (C) 2008 by David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 * Copyright (C) 2009 by Samsung Electronics
 * Author: Michal Nazarewicz (mina86@mina86.com)
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>

#समावेश "u_serial.h"


/*
 * This CDC ACM function support just wraps control functions and
 * notअगरications around the generic serial-over-usb code.
 *
 * Because CDC ACM is standardized by the USB-IF, many host operating
 * प्रणालीs have drivers क्रम it.  Accordingly, ACM is the preferred
 * पूर्णांकerop solution क्रम serial-port type connections.  The control
 * models are often not necessary, and in any हाल करोn't करो much in
 * this bare-bones implementation.
 *
 * Note that even MS-Winकरोws has some support क्रम ACM.  However, that
 * support is somewhat broken because when you use ACM in a composite
 * device, having multiple पूर्णांकerfaces confuses the poor OS.  It करोesn't
 * seem to understand CDC Union descriptors.  The new "association"
 * descriptors (roughly equivalent to CDC Unions) may someबार help.
 */

काष्ठा f_acm अणु
	काष्ठा gserial			port;
	u8				ctrl_id, data_id;
	u8				port_num;

	u8				pending;

	/* lock is mostly क्रम pending and notअगरy_req ... they get accessed
	 * by callbacks both from tty (खोलो/बंद/अवरोध) under its spinlock,
	 * and notअगरy_req.complete() which can't use that lock.
	 */
	spinlock_t			lock;

	काष्ठा usb_ep			*notअगरy;
	काष्ठा usb_request		*notअगरy_req;

	काष्ठा usb_cdc_line_coding	port_line_coding;	/* 8-N-1 etc */

	/* SetControlLineState request -- CDC 1.1 section 6.2.14 (INPUT) */
	u16				port_handshake_bits;
#घोषणा ACM_CTRL_RTS	(1 << 1)	/* unused with full duplex */
#घोषणा ACM_CTRL_DTR	(1 << 0)	/* host is पढ़ोy क्रम data r/w */

	/* SerialState notअगरication -- CDC 1.1 section 6.3.5 (OUTPUT) */
	u16				serial_state;
#घोषणा ACM_CTRL_OVERRUN	(1 << 6)
#घोषणा ACM_CTRL_PARITY		(1 << 5)
#घोषणा ACM_CTRL_FRAMING	(1 << 4)
#घोषणा ACM_CTRL_RI		(1 << 3)
#घोषणा ACM_CTRL_BRK		(1 << 2)
#घोषणा ACM_CTRL_DSR		(1 << 1)
#घोषणा ACM_CTRL_DCD		(1 << 0)
पूर्ण;

अटल अंतरभूत काष्ठा f_acm *func_to_acm(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_acm, port.func);
पूर्ण

अटल अंतरभूत काष्ठा f_acm *port_to_acm(काष्ठा gserial *p)
अणु
	वापस container_of(p, काष्ठा f_acm, port);
पूर्ण

/*-------------------------------------------------------------------------*/

/* notअगरication endpoपूर्णांक uses smallish and infrequent fixed-size messages */

#घोषणा GS_NOTIFY_INTERVAL_MS		32
#घोषणा GS_NOTIFY_MAXPACKET		10	/* notअगरication + 2 bytes */

/* पूर्णांकerface and class descriptors: */

अटल काष्ठा usb_पूर्णांकerface_assoc_descriptor
acm_iad_descriptor = अणु
	.bLength =		माप acm_iad_descriptor,
	.bDescriptorType =	USB_DT_INTERFACE_ASSOCIATION,

	/* .bFirstInterface =	DYNAMIC, */
	.bInterfaceCount = 	2,	// control + data
	.bFunctionClass =	USB_CLASS_COMM,
	.bFunctionSubClass =	USB_CDC_SUBCLASS_ACM,
	.bFunctionProtocol =	USB_CDC_ACM_PROTO_AT_V25TER,
	/* .iFunction =		DYNAMIC */
पूर्ण;


अटल काष्ठा usb_पूर्णांकerface_descriptor acm_control_पूर्णांकerface_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoपूर्णांकs =	1,
	.bInterfaceClass =	USB_CLASS_COMM,
	.bInterfaceSubClass =	USB_CDC_SUBCLASS_ACM,
	.bInterfaceProtocol =	USB_CDC_ACM_PROTO_AT_V25TER,
	/* .iInterface = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor acm_data_पूर्णांकerface_desc = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_CDC_DATA,
	.bInterfaceSubClass =	0,
	.bInterfaceProtocol =	0,
	/* .iInterface = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_cdc_header_desc acm_header_desc = अणु
	.bLength =		माप(acm_header_desc),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_HEADER_TYPE,
	.bcdCDC =		cpu_to_le16(0x0110),
पूर्ण;

अटल काष्ठा usb_cdc_call_mgmt_descriptor
acm_call_mgmt_descriptor = अणु
	.bLength =		माप(acm_call_mgmt_descriptor),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_CALL_MANAGEMENT_TYPE,
	.bmCapabilities =	0,
	/* .bDataInterface = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_cdc_acm_descriptor acm_descriptor = अणु
	.bLength =		माप(acm_descriptor),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_ACM_TYPE,
	.bmCapabilities =	USB_CDC_CAP_LINE,
पूर्ण;

अटल काष्ठा usb_cdc_जोड़_desc acm_जोड़_desc = अणु
	.bLength =		माप(acm_जोड़_desc),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_UNION_TYPE,
	/* .bMasterInterface0 =	DYNAMIC */
	/* .bSlaveInterface0 =	DYNAMIC */
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor acm_fs_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(GS_NOTIFY_MAXPACKET),
	.bInterval =		GS_NOTIFY_INTERVAL_MS,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor acm_fs_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor acm_fs_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *acm_fs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &acm_iad_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_control_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &acm_header_desc,
	(काष्ठा usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &acm_fs_notअगरy_desc,
	(काष्ठा usb_descriptor_header *) &acm_data_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &acm_fs_in_desc,
	(काष्ठा usb_descriptor_header *) &acm_fs_out_desc,
	शून्य,
पूर्ण;

/* high speed support: */
अटल काष्ठा usb_endpoपूर्णांक_descriptor acm_hs_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(GS_NOTIFY_MAXPACKET),
	.bInterval =		USB_MS_TO_HS_INTERVAL(GS_NOTIFY_INTERVAL_MS),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor acm_hs_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor acm_hs_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *acm_hs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &acm_iad_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_control_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &acm_header_desc,
	(काष्ठा usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &acm_hs_notअगरy_desc,
	(काष्ठा usb_descriptor_header *) &acm_data_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &acm_hs_in_desc,
	(काष्ठा usb_descriptor_header *) &acm_hs_out_desc,
	शून्य,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor acm_ss_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor acm_ss_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor acm_ss_bulk_comp_desc = अणु
	.bLength =              माप acm_ss_bulk_comp_desc,
	.bDescriptorType =      USB_DT_SS_ENDPOINT_COMP,
पूर्ण;

अटल काष्ठा usb_descriptor_header *acm_ss_function[] = अणु
	(काष्ठा usb_descriptor_header *) &acm_iad_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_control_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &acm_header_desc,
	(काष्ठा usb_descriptor_header *) &acm_call_mgmt_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_descriptor,
	(काष्ठा usb_descriptor_header *) &acm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &acm_hs_notअगरy_desc,
	(काष्ठा usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	(काष्ठा usb_descriptor_header *) &acm_data_पूर्णांकerface_desc,
	(काष्ठा usb_descriptor_header *) &acm_ss_in_desc,
	(काष्ठा usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	(काष्ठा usb_descriptor_header *) &acm_ss_out_desc,
	(काष्ठा usb_descriptor_header *) &acm_ss_bulk_comp_desc,
	शून्य,
पूर्ण;

/* string descriptors: */

#घोषणा ACM_CTRL_IDX	0
#घोषणा ACM_DATA_IDX	1
#घोषणा ACM_IAD_IDX	2

/* अटल strings, in UTF-8 */
अटल काष्ठा usb_string acm_string_defs[] = अणु
	[ACM_CTRL_IDX].s = "CDC Abstract Control Model (ACM)",
	[ACM_DATA_IDX].s = "CDC ACM Data",
	[ACM_IAD_IDX ].s = "CDC Serial",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings acm_string_table = अणु
	.language =		0x0409,	/* en-us */
	.strings =		acm_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *acm_strings[] = अणु
	&acm_string_table,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

/* ACM control ... data handling is delegated to tty library code.
 * The मुख्य task of this function is to activate and deactivate
 * that code based on device state; track parameters like line
 * speed, handshake state, and so on; and issue notअगरications.
 */

अटल व्योम acm_complete_set_line_coding(काष्ठा usb_ep *ep,
		काष्ठा usb_request *req)
अणु
	काष्ठा f_acm	*acm = ep->driver_data;
	काष्ठा usb_composite_dev *cdev = acm->port.func.config->cdev;

	अगर (req->status != 0) अणु
		dev_dbg(&cdev->gadget->dev, "acm ttyGS%d completion, err %d\n",
			acm->port_num, req->status);
		वापस;
	पूर्ण

	/* normal completion */
	अगर (req->actual != माप(acm->port_line_coding)) अणु
		dev_dbg(&cdev->gadget->dev, "acm ttyGS%d short resp, len %d\n",
			acm->port_num, req->actual);
		usb_ep_set_halt(ep);
	पूर्ण अन्यथा अणु
		काष्ठा usb_cdc_line_coding	*value = req->buf;

		/* REVISIT:  we currently just remember this data.
		 * If we change that, (a) validate it first, then
		 * (b) update whatever hardware needs updating,
		 * (c) worry about locking.  This is inक्रमmation on
		 * the order of 9600-8-N-1 ... most of which means
		 * nothing unless we control a real RS232 line.
		 */
		acm->port_line_coding = *value;
	पूर्ण
पूर्ण

अटल पूर्णांक acm_setup(काष्ठा usb_function *f, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_acm		*acm = func_to_acm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_request	*req = cdev->req;
	पूर्णांक			value = -EOPNOTSUPP;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	/* composite driver infraकाष्ठाure handles everything except
	 * CDC class messages; पूर्णांकerface activation uses set_alt().
	 *
	 * Note CDC spec table 4 lists the ACM request profile.  It requires
	 * encapsulated command support ... we करोn't handle any, and respond
	 * to them by stalling.  Options include get/set/clear comm features
	 * (not that useful) and SEND_BREAK.
	 */
	चयन ((ctrl->bRequestType << 8) | ctrl->bRequest) अणु

	/* SET_LINE_CODING ... just पढ़ो and save what the host sends */
	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_REQ_SET_LINE_CODING:
		अगर (w_length != माप(काष्ठा usb_cdc_line_coding)
				|| w_index != acm->ctrl_id)
			जाओ invalid;

		value = w_length;
		cdev->gadget->ep0->driver_data = acm;
		req->complete = acm_complete_set_line_coding;
		अवरोध;

	/* GET_LINE_CODING ... वापस what host sent, or initial value */
	हाल ((USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_REQ_GET_LINE_CODING:
		अगर (w_index != acm->ctrl_id)
			जाओ invalid;

		value = min_t(अचिन्हित, w_length,
				माप(काष्ठा usb_cdc_line_coding));
		स_नकल(req->buf, &acm->port_line_coding, value);
		अवरोध;

	/* SET_CONTROL_LINE_STATE ... save what the host sent */
	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_REQ_SET_CONTROL_LINE_STATE:
		अगर (w_index != acm->ctrl_id)
			जाओ invalid;

		value = 0;

		/* FIXME we should not allow data to flow until the
		 * host sets the ACM_CTRL_DTR bit; and when it clears
		 * that bit, we should वापस to that no-flow state.
		 */
		acm->port_handshake_bits = w_value;
		अवरोध;

	शेष:
invalid:
		dev_vdbg(&cdev->gadget->dev,
			 "invalid control req%02x.%02x v%04x i%04x l%d\n",
			 ctrl->bRequestType, ctrl->bRequest,
			 w_value, w_index, w_length);
	पूर्ण

	/* respond with data transfer or status phase? */
	अगर (value >= 0) अणु
		dev_dbg(&cdev->gadget->dev,
			"acm ttyGS%d req%02x.%02x v%04x i%04x l%d\n",
			acm->port_num, ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
		req->zero = 0;
		req->length = value;
		value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
		अगर (value < 0)
			ERROR(cdev, "acm response on ttyGS%d, err %d\n",
					acm->port_num, value);
	पूर्ण

	/* device either stalls (value < 0) or reports success */
	वापस value;
पूर्ण

अटल पूर्णांक acm_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_acm		*acm = func_to_acm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	/* we know alt == 0, so this is an activation or a reset */

	अगर (पूर्णांकf == acm->ctrl_id) अणु
		अगर (acm->notअगरy->enabled) अणु
			dev_vdbg(&cdev->gadget->dev,
					"reset acm control interface %d\n", पूर्णांकf);
			usb_ep_disable(acm->notअगरy);
		पूर्ण

		अगर (!acm->notअगरy->desc)
			अगर (config_ep_by_speed(cdev->gadget, f, acm->notअगरy))
				वापस -EINVAL;

		usb_ep_enable(acm->notअगरy);

	पूर्ण अन्यथा अगर (पूर्णांकf == acm->data_id) अणु
		अगर (acm->notअगरy->enabled) अणु
			dev_dbg(&cdev->gadget->dev,
				"reset acm ttyGS%d\n", acm->port_num);
			gserial_disconnect(&acm->port);
		पूर्ण
		अगर (!acm->port.in->desc || !acm->port.out->desc) अणु
			dev_dbg(&cdev->gadget->dev,
				"activate acm ttyGS%d\n", acm->port_num);
			अगर (config_ep_by_speed(cdev->gadget, f,
					       acm->port.in) ||
			    config_ep_by_speed(cdev->gadget, f,
					       acm->port.out)) अणु
				acm->port.in->desc = शून्य;
				acm->port.out->desc = शून्य;
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		gserial_connect(&acm->port, acm->port_num);

	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम acm_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_acm	*acm = func_to_acm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	dev_dbg(&cdev->gadget->dev, "acm ttyGS%d deactivated\n", acm->port_num);
	gserial_disconnect(&acm->port);
	usb_ep_disable(acm->notअगरy);
पूर्ण

/*-------------------------------------------------------------------------*/

/**
 * acm_cdc_notअगरy - issue CDC notअगरication to host
 * @acm: wraps host to be notअगरied
 * @type: notअगरication type
 * @value: Refer to cdc specs, wValue field.
 * @data: data to be sent
 * @length: size of data
 * Context: irqs blocked, acm->lock held, acm_notअगरy_req non-null
 *
 * Returns zero on success or a negative त्रुटि_सं.
 *
 * See section 6.3.5 of the CDC 1.1 specअगरication क्रम inक्रमmation
 * about the only notअगरication we issue:  SerialState change.
 */
अटल पूर्णांक acm_cdc_notअगरy(काष्ठा f_acm *acm, u8 type, u16 value,
		व्योम *data, अचिन्हित length)
अणु
	काष्ठा usb_ep			*ep = acm->notअगरy;
	काष्ठा usb_request		*req;
	काष्ठा usb_cdc_notअगरication	*notअगरy;
	स्थिर अचिन्हित			len = माप(*notअगरy) + length;
	व्योम				*buf;
	पूर्णांक				status;

	req = acm->notअगरy_req;
	acm->notअगरy_req = शून्य;
	acm->pending = false;

	req->length = len;
	notअगरy = req->buf;
	buf = notअगरy + 1;

	notअगरy->bmRequestType = USB_सूची_IN | USB_TYPE_CLASS
			| USB_RECIP_INTERFACE;
	notअगरy->bNotअगरicationType = type;
	notअगरy->wValue = cpu_to_le16(value);
	notअगरy->wIndex = cpu_to_le16(acm->ctrl_id);
	notअगरy->wLength = cpu_to_le16(length);
	स_नकल(buf, data, length);

	/* ep_queue() can complete immediately अगर it fills the fअगरo... */
	spin_unlock(&acm->lock);
	status = usb_ep_queue(ep, req, GFP_ATOMIC);
	spin_lock(&acm->lock);

	अगर (status < 0) अणु
		ERROR(acm->port.func.config->cdev,
				"acm ttyGS%d can't notify serial state, %d\n",
				acm->port_num, status);
		acm->notअगरy_req = req;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक acm_notअगरy_serial_state(काष्ठा f_acm *acm)
अणु
	काष्ठा usb_composite_dev *cdev = acm->port.func.config->cdev;
	पूर्णांक			status;
	__le16			serial_state;

	spin_lock(&acm->lock);
	अगर (acm->notअगरy_req) अणु
		dev_dbg(&cdev->gadget->dev, "acm ttyGS%d serial state %04x\n",
			acm->port_num, acm->serial_state);
		serial_state = cpu_to_le16(acm->serial_state);
		status = acm_cdc_notअगरy(acm, USB_CDC_NOTIFY_SERIAL_STATE,
				0, &serial_state, माप(acm->serial_state));
	पूर्ण अन्यथा अणु
		acm->pending = true;
		status = 0;
	पूर्ण
	spin_unlock(&acm->lock);
	वापस status;
पूर्ण

अटल व्योम acm_cdc_notअगरy_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_acm		*acm = req->context;
	u8			करोit = false;

	/* on this call path we करो NOT hold the port spinlock,
	 * which is why ACM needs its own spinlock
	 */
	spin_lock(&acm->lock);
	अगर (req->status != -ESHUTDOWN)
		करोit = acm->pending;
	acm->notअगरy_req = req;
	spin_unlock(&acm->lock);

	अगर (करोit)
		acm_notअगरy_serial_state(acm);
पूर्ण

/* connect == the TTY link is खोलो */

अटल व्योम acm_connect(काष्ठा gserial *port)
अणु
	काष्ठा f_acm		*acm = port_to_acm(port);

	acm->serial_state |= ACM_CTRL_DSR | ACM_CTRL_DCD;
	acm_notअगरy_serial_state(acm);
पूर्ण

अटल व्योम acm_disconnect(काष्ठा gserial *port)
अणु
	काष्ठा f_acm		*acm = port_to_acm(port);

	acm->serial_state &= ~(ACM_CTRL_DSR | ACM_CTRL_DCD);
	acm_notअगरy_serial_state(acm);
पूर्ण

अटल पूर्णांक acm_send_अवरोध(काष्ठा gserial *port, पूर्णांक duration)
अणु
	काष्ठा f_acm		*acm = port_to_acm(port);
	u16			state;

	state = acm->serial_state;
	state &= ~ACM_CTRL_BRK;
	अगर (duration)
		state |= ACM_CTRL_BRK;

	acm->serial_state = state;
	वापस acm_notअगरy_serial_state(acm);
पूर्ण

/*-------------------------------------------------------------------------*/

/* ACM function driver setup/binding */
अटल पूर्णांक
acm_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_acm		*acm = func_to_acm(f);
	काष्ठा usb_string	*us;
	पूर्णांक			status;
	काष्ठा usb_ep		*ep;

	/* REVISIT might want instance-specअगरic strings to help
	 * distinguish instances ...
	 */

	/* maybe allocate device-global string IDs, and patch descriptors */
	us = usb_gstrings_attach(cdev, acm_strings,
			ARRAY_SIZE(acm_string_defs));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);
	acm_control_पूर्णांकerface_desc.iInterface = us[ACM_CTRL_IDX].id;
	acm_data_पूर्णांकerface_desc.iInterface = us[ACM_DATA_IDX].id;
	acm_iad_descriptor.iFunction = us[ACM_IAD_IDX].id;

	/* allocate instance-specअगरic पूर्णांकerface IDs, and patch descriptors */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	acm->ctrl_id = status;
	acm_iad_descriptor.bFirstInterface = status;

	acm_control_पूर्णांकerface_desc.bInterfaceNumber = status;
	acm_जोड़_desc .bMasterInterface0 = status;

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	acm->data_id = status;

	acm_data_पूर्णांकerface_desc.bInterfaceNumber = status;
	acm_जोड़_desc.bSlaveInterface0 = status;
	acm_call_mgmt_descriptor.bDataInterface = status;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &acm_fs_in_desc);
	अगर (!ep)
		जाओ fail;
	acm->port.in = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &acm_fs_out_desc);
	अगर (!ep)
		जाओ fail;
	acm->port.out = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &acm_fs_notअगरy_desc);
	अगर (!ep)
		जाओ fail;
	acm->notअगरy = ep;

	/* allocate notअगरication */
	acm->notअगरy_req = gs_alloc_req(ep,
			माप(काष्ठा usb_cdc_notअगरication) + 2,
			GFP_KERNEL);
	अगर (!acm->notअगरy_req)
		जाओ fail;

	acm->notअगरy_req->complete = acm_cdc_notअगरy_complete;
	acm->notअगरy_req->context = acm;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */
	acm_hs_in_desc.bEndpoपूर्णांकAddress = acm_fs_in_desc.bEndpoपूर्णांकAddress;
	acm_hs_out_desc.bEndpoपूर्णांकAddress = acm_fs_out_desc.bEndpoपूर्णांकAddress;
	acm_hs_notअगरy_desc.bEndpoपूर्णांकAddress =
		acm_fs_notअगरy_desc.bEndpoपूर्णांकAddress;

	acm_ss_in_desc.bEndpoपूर्णांकAddress = acm_fs_in_desc.bEndpoपूर्णांकAddress;
	acm_ss_out_desc.bEndpoपूर्णांकAddress = acm_fs_out_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, acm_fs_function, acm_hs_function,
			acm_ss_function, acm_ss_function);
	अगर (status)
		जाओ fail;

	dev_dbg(&cdev->gadget->dev,
		"acm ttyGS%d: %s speed IN/%s OUT/%s NOTIFY/%s\n",
		acm->port_num,
		gadget_is_superspeed(c->cdev->gadget) ? "super" :
		gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
		acm->port.in->name, acm->port.out->name,
		acm->notअगरy->name);
	वापस 0;

fail:
	अगर (acm->notअगरy_req)
		gs_मुक्त_req(acm->notअगरy, acm->notअगरy_req);

	ERROR(cdev, "%s/%p: can't bind, err %d\n", f->name, f, status);

	वापस status;
पूर्ण

अटल व्योम acm_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा f_acm		*acm = func_to_acm(f);

	acm_string_defs[0].id = 0;
	usb_मुक्त_all_descriptors(f);
	अगर (acm->notअगरy_req)
		gs_मुक्त_req(acm->notअगरy, acm->notअगरy_req);
पूर्ण

अटल व्योम acm_मुक्त_func(काष्ठा usb_function *f)
अणु
	काष्ठा f_acm		*acm = func_to_acm(f);

	kमुक्त(acm);
पूर्ण

अटल व्योम acm_resume(काष्ठा usb_function *f)
अणु
	काष्ठा f_acm *acm = func_to_acm(f);

	gserial_resume(&acm->port);
पूर्ण

अटल व्योम acm_suspend(काष्ठा usb_function *f)
अणु
	काष्ठा f_acm *acm = func_to_acm(f);

	gserial_suspend(&acm->port);
पूर्ण

अटल काष्ठा usb_function *acm_alloc_func(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_serial_opts *opts;
	काष्ठा f_acm *acm;

	acm = kzalloc(माप(*acm), GFP_KERNEL);
	अगर (!acm)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&acm->lock);

	acm->port.connect = acm_connect;
	acm->port.disconnect = acm_disconnect;
	acm->port.send_अवरोध = acm_send_अवरोध;

	acm->port.func.name = "acm";
	acm->port.func.strings = acm_strings;
	/* descriptors are per-instance copies */
	acm->port.func.bind = acm_bind;
	acm->port.func.set_alt = acm_set_alt;
	acm->port.func.setup = acm_setup;
	acm->port.func.disable = acm_disable;

	opts = container_of(fi, काष्ठा f_serial_opts, func_inst);
	acm->port_num = opts->port_num;
	acm->port.func.unbind = acm_unbind;
	acm->port.func.मुक्त_func = acm_मुक्त_func;
	acm->port.func.resume = acm_resume;
	acm->port.func.suspend = acm_suspend;

	वापस &acm->port.func;
पूर्ण

अटल अंतरभूत काष्ठा f_serial_opts *to_f_serial_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_serial_opts,
			func_inst.group);
पूर्ण

अटल व्योम acm_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_serial_opts *opts = to_f_serial_opts(item);

	usb_put_function_instance(&opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations acm_item_ops = अणु
	.release                = acm_attr_release,
पूर्ण;

#अगर_घोषित CONFIG_U_SERIAL_CONSOLE

अटल sमाप_प्रकार f_acm_console_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	वापस gserial_set_console(to_f_serial_opts(item)->port_num,
				   page, count);
पूर्ण

अटल sमाप_प्रकार f_acm_console_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस gserial_get_console(to_f_serial_opts(item)->port_num, page);
पूर्ण

CONFIGFS_ATTR(f_acm_, console);

#पूर्ण_अगर /* CONFIG_U_SERIAL_CONSOLE */

अटल sमाप_प्रकार f_acm_port_num_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_f_serial_opts(item)->port_num);
पूर्ण

CONFIGFS_ATTR_RO(f_acm_, port_num);

अटल काष्ठा configfs_attribute *acm_attrs[] = अणु
#अगर_घोषित CONFIG_U_SERIAL_CONSOLE
	&f_acm_attr_console,
#पूर्ण_अगर
	&f_acm_attr_port_num,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type acm_func_type = अणु
	.ct_item_ops    = &acm_item_ops,
	.ct_attrs	= acm_attrs,
	.ct_owner       = THIS_MODULE,
पूर्ण;

अटल व्योम acm_मुक्त_instance(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_serial_opts *opts;

	opts = container_of(fi, काष्ठा f_serial_opts, func_inst);
	gserial_मुक्त_line(opts->port_num);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *acm_alloc_instance(व्योम)
अणु
	काष्ठा f_serial_opts *opts;
	पूर्णांक ret;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	opts->func_inst.मुक्त_func_inst = acm_मुक्त_instance;
	ret = gserial_alloc_line(&opts->port_num);
	अगर (ret) अणु
		kमुक्त(opts);
		वापस ERR_PTR(ret);
	पूर्ण
	config_group_init_type_name(&opts->func_inst.group, "",
			&acm_func_type);
	वापस &opts->func_inst;
पूर्ण
DECLARE_USB_FUNCTION_INIT(acm, acm_alloc_instance, acm_alloc_func);
MODULE_LICENSE("GPL");
