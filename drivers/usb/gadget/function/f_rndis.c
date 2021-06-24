<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_rndis.c -- RNDIS link function driver
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2003-2004 Robert Schwebel, Benedikt Spranger
 * Copyright (C) 2008 Nokia Corporation
 * Copyright (C) 2009 Samsung Electronics
 *                    Author: Michal Nazarewicz (mina86@mina86.com)
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>

#समावेश <linux/atomic.h>

#समावेश "u_ether.h"
#समावेश "u_ether_configfs.h"
#समावेश "u_rndis.h"
#समावेश "rndis.h"
#समावेश "configfs.h"

/*
 * This function is an RNDIS Ethernet port -- a Microsoft protocol that's
 * been promoted instead of the standard CDC Ethernet.  The published RNDIS
 * spec is ambiguous, incomplete, and needlessly complex.  Variants such as
 * ActiveSync have even worse status in terms of specअगरication.
 *
 * In लघु:  it's a protocol controlled by (and क्रम) Microsoft, not क्रम an
 * Open ecoप्रणाली or markets.  Linux supports it *only* because Microsoft
 * करोesn't support the CDC Ethernet standard.
 *
 * The RNDIS data transfer model is complex, with multiple Ethernet packets
 * per USB message, and out of band data.  The control model is built around
 * what's essentially an "RNDIS RPC" protocol.  It's all wrapped in a CDC ACM
 * (modem, not Ethernet) veneer, with those ACM descriptors being entirely
 * useless (they're ignored).  RNDIS expects to be the only function in its
 * configuration, so it's no real help अगर you need composite devices; and
 * it expects to be the first configuration too.
 *
 * There is a single technical advantage of RNDIS over CDC Ethernet, अगर you
 * discount the fluff that its RPC can be made to deliver: it करोesn't need
 * a NOP altsetting क्रम the data पूर्णांकerface.  That lets it work on some of the
 * "so smart it's stupid" hardware which takes over configuration changes
 * from the software, and adds restrictions like "no altsettings".
 *
 * Unक्रमtunately MSFT's RNDIS drivers are buggy.  They hang or oops, and
 * have all sorts of contrary-to-specअगरication oddities that can prevent
 * them from working sanely.  Since bugfixes (or accurate specs, letting
 * Linux work around those bugs) are unlikely to ever come from MSFT, you
 * may want to aव्योम using RNDIS on purely operational grounds.
 *
 * Omissions from the RNDIS 1.0 specअगरication include:
 *
 *   - Power management ... references data that's scattered around lots
 *     of other करोcumentation, which is incorrect/incomplete there too.
 *
 *   - There are various unकरोcumented protocol requirements, like the need
 *     to send garbage in some control-OUT messages.
 *
 *   - MS-Winकरोws drivers someबार emit unकरोcumented requests.
 */

काष्ठा f_rndis अणु
	काष्ठा gether			port;
	u8				ctrl_id, data_id;
	u8				ethaddr[ETH_ALEN];
	u32				venकरोrID;
	स्थिर अक्षर			*manufacturer;
	काष्ठा rndis_params		*params;

	काष्ठा usb_ep			*notअगरy;
	काष्ठा usb_request		*notअगरy_req;
	atomic_t			notअगरy_count;
पूर्ण;

अटल अंतरभूत काष्ठा f_rndis *func_to_rndis(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_rndis, port.func);
पूर्ण

/* peak (theoretical) bulk transfer rate in bits-per-second */
अटल अचिन्हित पूर्णांक bitrate(काष्ठा usb_gadget *g)
अणु
	अगर (gadget_is_superspeed(g) && g->speed >= USB_SPEED_SUPER_PLUS)
		वापस 4250000000U;
	अगर (gadget_is_superspeed(g) && g->speed == USB_SPEED_SUPER)
		वापस 3750000000U;
	अन्यथा अगर (gadget_is_dualspeed(g) && g->speed == USB_SPEED_HIGH)
		वापस 13 * 512 * 8 * 1000 * 8;
	अन्यथा
		वापस 19 * 64 * 1 * 1000 * 8;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 */

#घोषणा RNDIS_STATUS_INTERVAL_MS	32
#घोषणा STATUS_BYTECOUNT		8	/* 8 bytes data */


/* पूर्णांकerface descriptor: */

अटल काष्ठा usb_पूर्णांकerface_descriptor rndis_control_पूर्णांकf = अणु
	.bLength =		माप rndis_control_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber = DYNAMIC */
	/* status endpoपूर्णांक is optional; this could be patched later */
	.bNumEndpoपूर्णांकs =	1,
	.bInterfaceClass =	USB_CLASS_COMM,
	.bInterfaceSubClass =   USB_CDC_SUBCLASS_ACM,
	.bInterfaceProtocol =   USB_CDC_ACM_PROTO_VENDOR,
	/* .iInterface = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_cdc_header_desc header_desc = अणु
	.bLength =		माप header_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_HEADER_TYPE,

	.bcdCDC =		cpu_to_le16(0x0110),
पूर्ण;

अटल काष्ठा usb_cdc_call_mgmt_descriptor call_mgmt_descriptor = अणु
	.bLength =		माप call_mgmt_descriptor,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_CALL_MANAGEMENT_TYPE,

	.bmCapabilities =	0x00,
	.bDataInterface =	0x01,
पूर्ण;

अटल काष्ठा usb_cdc_acm_descriptor rndis_acm_descriptor = अणु
	.bLength =		माप rndis_acm_descriptor,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_ACM_TYPE,

	.bmCapabilities =	0x00,
पूर्ण;

अटल काष्ठा usb_cdc_जोड़_desc rndis_जोड़_desc = अणु
	.bLength =		माप(rndis_जोड़_desc),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_UNION_TYPE,
	/* .bMasterInterface0 =	DYNAMIC */
	/* .bSlaveInterface0 =	DYNAMIC */
पूर्ण;

/* the data पूर्णांकerface has two bulk endpoपूर्णांकs */

अटल काष्ठा usb_पूर्णांकerface_descriptor rndis_data_पूर्णांकf = अणु
	.bLength =		माप rndis_data_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_CDC_DATA,
	.bInterfaceSubClass =	0,
	.bInterfaceProtocol =	0,
	/* .iInterface = DYNAMIC */
पूर्ण;


अटल काष्ठा usb_पूर्णांकerface_assoc_descriptor
rndis_iad_descriptor = अणु
	.bLength =		माप rndis_iad_descriptor,
	.bDescriptorType =	USB_DT_INTERFACE_ASSOCIATION,

	.bFirstInterface =	0, /* XXX, hardcoded */
	.bInterfaceCount = 	2,	// control + data
	.bFunctionClass =	USB_CLASS_COMM,
	.bFunctionSubClass =	USB_CDC_SUBCLASS_ETHERNET,
	.bFunctionProtocol =	USB_CDC_PROTO_NONE,
	/* .iFunction = DYNAMIC */
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(STATUS_BYTECOUNT),
	.bInterval =		RNDIS_STATUS_INTERVAL_MS,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *eth_fs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &rndis_iad_descriptor,

	/* control पूर्णांकerface matches ACM, not Ethernet */
	(काष्ठा usb_descriptor_header *) &rndis_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &header_desc,
	(काष्ठा usb_descriptor_header *) &call_mgmt_descriptor,
	(काष्ठा usb_descriptor_header *) &rndis_acm_descriptor,
	(काष्ठा usb_descriptor_header *) &rndis_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &fs_notअगरy_desc,

	/* data पूर्णांकerface has no altsetting */
	(काष्ठा usb_descriptor_header *) &rndis_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &fs_in_desc,
	(काष्ठा usb_descriptor_header *) &fs_out_desc,
	शून्य,
पूर्ण;

/* high speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(STATUS_BYTECOUNT),
	.bInterval =		USB_MS_TO_HS_INTERVAL(RNDIS_STATUS_INTERVAL_MS)
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *eth_hs_function[] = अणु
	(काष्ठा usb_descriptor_header *) &rndis_iad_descriptor,

	/* control पूर्णांकerface matches ACM, not Ethernet */
	(काष्ठा usb_descriptor_header *) &rndis_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &header_desc,
	(काष्ठा usb_descriptor_header *) &call_mgmt_descriptor,
	(काष्ठा usb_descriptor_header *) &rndis_acm_descriptor,
	(काष्ठा usb_descriptor_header *) &rndis_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &hs_notअगरy_desc,

	/* data पूर्णांकerface has no altsetting */
	(काष्ठा usb_descriptor_header *) &rndis_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &hs_in_desc,
	(काष्ठा usb_descriptor_header *) &hs_out_desc,
	शून्य,
पूर्ण;

/* super speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(STATUS_BYTECOUNT),
	.bInterval =		USB_MS_TO_HS_INTERVAL(RNDIS_STATUS_INTERVAL_MS)
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_पूर्णांकr_comp_desc = अणु
	.bLength =		माप ss_पूर्णांकr_comp_desc,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/* the following 3 values can be tweaked अगर necessary */
	/* .bMaxBurst =		0, */
	/* .bmAttributes =	0, */
	.wBytesPerInterval =	cpu_to_le16(STATUS_BYTECOUNT),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_bulk_comp_desc = अणु
	.bLength =		माप ss_bulk_comp_desc,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/* the following 2 values can be tweaked अगर necessary */
	/* .bMaxBurst =		0, */
	/* .bmAttributes =	0, */
पूर्ण;

अटल काष्ठा usb_descriptor_header *eth_ss_function[] = अणु
	(काष्ठा usb_descriptor_header *) &rndis_iad_descriptor,

	/* control पूर्णांकerface matches ACM, not Ethernet */
	(काष्ठा usb_descriptor_header *) &rndis_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &header_desc,
	(काष्ठा usb_descriptor_header *) &call_mgmt_descriptor,
	(काष्ठा usb_descriptor_header *) &rndis_acm_descriptor,
	(काष्ठा usb_descriptor_header *) &rndis_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &ss_notअगरy_desc,
	(काष्ठा usb_descriptor_header *) &ss_पूर्णांकr_comp_desc,

	/* data पूर्णांकerface has no altsetting */
	(काष्ठा usb_descriptor_header *) &rndis_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ss_in_desc,
	(काष्ठा usb_descriptor_header *) &ss_bulk_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_out_desc,
	(काष्ठा usb_descriptor_header *) &ss_bulk_comp_desc,
	शून्य,
पूर्ण;

/* string descriptors: */

अटल काष्ठा usb_string rndis_string_defs[] = अणु
	[0].s = "RNDIS Communications Control",
	[1].s = "RNDIS Ethernet Data",
	[2].s = "RNDIS",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings rndis_string_table = अणु
	.language =		0x0409,	/* en-us */
	.strings =		rndis_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *rndis_strings[] = अणु
	&rndis_string_table,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल काष्ठा sk_buff *rndis_add_header(काष्ठा gether *port,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *skb2;

	अगर (!skb)
		वापस शून्य;

	skb2 = skb_पुनः_स्मृति_headroom(skb, माप(काष्ठा rndis_packet_msg_type));
	rndis_add_hdr(skb2);

	dev_kमुक्त_skb(skb);
	वापस skb2;
पूर्ण

अटल व्योम rndis_response_available(व्योम *_rndis)
अणु
	काष्ठा f_rndis			*rndis = _rndis;
	काष्ठा usb_request		*req = rndis->notअगरy_req;
	काष्ठा usb_composite_dev	*cdev = rndis->port.func.config->cdev;
	__le32				*data = req->buf;
	पूर्णांक				status;

	अगर (atomic_inc_वापस(&rndis->notअगरy_count) != 1)
		वापस;

	/* Send RNDIS RESPONSE_AVAILABLE notअगरication; a
	 * USB_CDC_NOTIFY_RESPONSE_AVAILABLE "should" work too
	 *
	 * This is the only notअगरication defined by RNDIS.
	 */
	data[0] = cpu_to_le32(1);
	data[1] = cpu_to_le32(0);

	status = usb_ep_queue(rndis->notअगरy, req, GFP_ATOMIC);
	अगर (status) अणु
		atomic_dec(&rndis->notअगरy_count);
		DBG(cdev, "notify/0 --> %d\n", status);
	पूर्ण
पूर्ण

अटल व्योम rndis_response_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_rndis			*rndis = req->context;
	काष्ठा usb_composite_dev	*cdev = rndis->port.func.config->cdev;
	पूर्णांक				status = req->status;

	/* after TX:
	 *  - USB_CDC_GET_ENCAPSULATED_RESPONSE (ep0/control)
	 *  - RNDIS_RESPONSE_AVAILABLE (status/irq)
	 */
	चयन (status) अणु
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		/* connection gone */
		atomic_set(&rndis->notअगरy_count, 0);
		अवरोध;
	शेष:
		DBG(cdev, "RNDIS %s response error %d, %d/%d\n",
			ep->name, status,
			req->actual, req->length);
		fallthrough;
	हाल 0:
		अगर (ep != rndis->notअगरy)
			अवरोध;

		/* handle multiple pending RNDIS_RESPONSE_AVAILABLE
		 * notअगरications by resending until we're करोne
		 */
		अगर (atomic_dec_and_test(&rndis->notअगरy_count))
			अवरोध;
		status = usb_ep_queue(rndis->notअगरy, req, GFP_ATOMIC);
		अगर (status) अणु
			atomic_dec(&rndis->notअगरy_count);
			DBG(cdev, "notify/1 --> %d\n", status);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rndis_command_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_rndis			*rndis = req->context;
	पूर्णांक				status;

	/* received RNDIS command from USB_CDC_SEND_ENCAPSULATED_COMMAND */
//	spin_lock(&dev->lock);
	status = rndis_msg_parser(rndis->params, (u8 *) req->buf);
	अगर (status < 0)
		pr_err("RNDIS command error %d, %d/%d\n",
			status, req->actual, req->length);
//	spin_unlock(&dev->lock);
पूर्ण

अटल पूर्णांक
rndis_setup(काष्ठा usb_function *f, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_rndis		*rndis = func_to_rndis(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा usb_request	*req = cdev->req;
	पूर्णांक			value = -EOPNOTSUPP;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	/* composite driver infraकाष्ठाure handles everything except
	 * CDC class messages; पूर्णांकerface activation uses set_alt().
	 */
	चयन ((ctrl->bRequestType << 8) | ctrl->bRequest) अणु

	/* RNDIS uses the CDC command encapsulation mechanism to implement
	 * an RPC scheme, with much getting/setting of attributes by OID.
	 */
	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_SEND_ENCAPSULATED_COMMAND:
		अगर (w_value || w_index != rndis->ctrl_id)
			जाओ invalid;
		/* पढ़ो the request; process it later */
		value = w_length;
		req->complete = rndis_command_complete;
		req->context = rndis;
		/* later, rndis_response_available() sends a notअगरication */
		अवरोध;

	हाल ((USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_GET_ENCAPSULATED_RESPONSE:
		अगर (w_value || w_index != rndis->ctrl_id)
			जाओ invalid;
		अन्यथा अणु
			u8 *buf;
			u32 n;

			/* वापस the result */
			buf = rndis_get_next_response(rndis->params, &n);
			अगर (buf) अणु
				स_नकल(req->buf, buf, n);
				req->complete = rndis_response_complete;
				req->context = rndis;
				rndis_मुक्त_response(rndis->params, buf);
				value = n;
			पूर्ण
			/* अन्यथा stalls ... spec says to aव्योम that */
		पूर्ण
		अवरोध;

	शेष:
invalid:
		VDBG(cdev, "invalid control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
	पूर्ण

	/* respond with data transfer or status phase? */
	अगर (value >= 0) अणु
		DBG(cdev, "rndis req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
		req->zero = (value < w_length);
		req->length = value;
		value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
		अगर (value < 0)
			ERROR(cdev, "rndis response on err %d\n", value);
	पूर्ण

	/* device either stalls (value < 0) or reports success */
	वापस value;
पूर्ण


अटल पूर्णांक rndis_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_rndis		*rndis = func_to_rndis(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	/* we know alt == 0 */

	अगर (पूर्णांकf == rndis->ctrl_id) अणु
		VDBG(cdev, "reset rndis control %d\n", पूर्णांकf);
		usb_ep_disable(rndis->notअगरy);

		अगर (!rndis->notअगरy->desc) अणु
			VDBG(cdev, "init rndis ctrl %d\n", पूर्णांकf);
			अगर (config_ep_by_speed(cdev->gadget, f, rndis->notअगरy))
				जाओ fail;
		पूर्ण
		usb_ep_enable(rndis->notअगरy);

	पूर्ण अन्यथा अगर (पूर्णांकf == rndis->data_id) अणु
		काष्ठा net_device	*net;

		अगर (rndis->port.in_ep->enabled) अणु
			DBG(cdev, "reset rndis\n");
			gether_disconnect(&rndis->port);
		पूर्ण

		अगर (!rndis->port.in_ep->desc || !rndis->port.out_ep->desc) अणु
			DBG(cdev, "init rndis\n");
			अगर (config_ep_by_speed(cdev->gadget, f,
					       rndis->port.in_ep) ||
			    config_ep_by_speed(cdev->gadget, f,
					       rndis->port.out_ep)) अणु
				rndis->port.in_ep->desc = शून्य;
				rndis->port.out_ep->desc = शून्य;
				जाओ fail;
			पूर्ण
		पूर्ण

		/* Aव्योम ZLPs; they can be troublesome. */
		rndis->port.is_zlp_ok = false;

		/* RNDIS should be in the "RNDIS uninitialized" state,
		 * either never activated or after rndis_uninit().
		 *
		 * We करोn't want data to flow here until a nonzero packet
		 * filter is set, at which poपूर्णांक it enters "RNDIS data
		 * initialized" state ... but we करो want the endpoपूर्णांकs
		 * to be activated.  It's a strange little state.
		 *
		 * REVISIT the RNDIS gadget code has करोne this wrong क्रम a
		 * very दीर्घ समय.  We need another call to the link layer
		 * code -- gether_upकरोwn(...bool) maybe -- to करो it right.
		 */
		rndis->port.cdc_filter = 0;

		DBG(cdev, "RNDIS RX/TX early activation ... \n");
		net = gether_connect(&rndis->port);
		अगर (IS_ERR(net))
			वापस PTR_ERR(net);

		rndis_set_param_dev(rndis->params, net,
				&rndis->port.cdc_filter);
	पूर्ण अन्यथा
		जाओ fail;

	वापस 0;
fail:
	वापस -EINVAL;
पूर्ण

अटल व्योम rndis_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_rndis		*rndis = func_to_rndis(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	अगर (!rndis->notअगरy->enabled)
		वापस;

	DBG(cdev, "rndis deactivated\n");

	rndis_uninit(rndis->params);
	gether_disconnect(&rndis->port);

	usb_ep_disable(rndis->notअगरy);
	rndis->notअगरy->desc = शून्य;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * This isn't quite the same mechanism as CDC Ethernet, since the
 * notअगरication scheme passes less data, but the same set of link
 * states must be tested.  A key dअगरference is that altsettings are
 * not used to tell whether the link should send packets or not.
 */

अटल व्योम rndis_खोलो(काष्ठा gether *geth)
अणु
	काष्ठा f_rndis		*rndis = func_to_rndis(&geth->func);
	काष्ठा usb_composite_dev *cdev = geth->func.config->cdev;

	DBG(cdev, "%s\n", __func__);

	rndis_set_param_medium(rndis->params, RNDIS_MEDIUM_802_3,
				bitrate(cdev->gadget) / 100);
	rndis_संकेत_connect(rndis->params);
पूर्ण

अटल व्योम rndis_बंद(काष्ठा gether *geth)
अणु
	काष्ठा f_rndis		*rndis = func_to_rndis(&geth->func);

	DBG(geth->func.config->cdev, "%s\n", __func__);

	rndis_set_param_medium(rndis->params, RNDIS_MEDIUM_802_3, 0);
	rndis_संकेत_disconnect(rndis->params);
पूर्ण

/*-------------------------------------------------------------------------*/

/* Some controllers can't support RNDIS ... */
अटल अंतरभूत bool can_support_rndis(काष्ठा usb_configuration *c)
अणु
	/* everything अन्यथा is *presumably* fine */
	वापस true;
पूर्ण

/* ethernet function driver setup/binding */

अटल पूर्णांक
rndis_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_rndis		*rndis = func_to_rndis(f);
	काष्ठा usb_string	*us;
	पूर्णांक			status;
	काष्ठा usb_ep		*ep;

	काष्ठा f_rndis_opts *rndis_opts;

	अगर (!can_support_rndis(c))
		वापस -EINVAL;

	rndis_opts = container_of(f->fi, काष्ठा f_rndis_opts, func_inst);

	अगर (cdev->use_os_string) अणु
		f->os_desc_table = kzalloc(माप(*f->os_desc_table),
					   GFP_KERNEL);
		अगर (!f->os_desc_table)
			वापस -ENOMEM;
		f->os_desc_n = 1;
		f->os_desc_table[0].os_desc = &rndis_opts->rndis_os_desc;
	पूर्ण

	rndis_iad_descriptor.bFunctionClass = rndis_opts->class;
	rndis_iad_descriptor.bFunctionSubClass = rndis_opts->subclass;
	rndis_iad_descriptor.bFunctionProtocol = rndis_opts->protocol;

	/*
	 * in drivers/usb/gadget/configfs.c:configfs_composite_bind()
	 * configurations are bound in sequence with list_क्रम_each_entry,
	 * in each configuration its functions are bound in sequence
	 * with list_क्रम_each_entry, so we assume no race condition
	 * with regard to rndis_opts->bound access
	 */
	अगर (!rndis_opts->bound) अणु
		gether_set_gadget(rndis_opts->net, cdev->gadget);
		status = gether_रेजिस्टर_netdev(rndis_opts->net);
		अगर (status)
			जाओ fail;
		rndis_opts->bound = true;
	पूर्ण

	us = usb_gstrings_attach(cdev, rndis_strings,
				 ARRAY_SIZE(rndis_string_defs));
	अगर (IS_ERR(us)) अणु
		status = PTR_ERR(us);
		जाओ fail;
	पूर्ण
	rndis_control_पूर्णांकf.iInterface = us[0].id;
	rndis_data_पूर्णांकf.iInterface = us[1].id;
	rndis_iad_descriptor.iFunction = us[2].id;

	/* allocate instance-specअगरic पूर्णांकerface IDs */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	rndis->ctrl_id = status;
	rndis_iad_descriptor.bFirstInterface = status;

	rndis_control_पूर्णांकf.bInterfaceNumber = status;
	rndis_जोड़_desc.bMasterInterface0 = status;

	अगर (cdev->use_os_string)
		f->os_desc_table[0].अगर_id =
			rndis_iad_descriptor.bFirstInterface;

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	rndis->data_id = status;

	rndis_data_पूर्णांकf.bInterfaceNumber = status;
	rndis_जोड़_desc.bSlaveInterface0 = status;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_in_desc);
	अगर (!ep)
		जाओ fail;
	rndis->port.in_ep = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_out_desc);
	अगर (!ep)
		जाओ fail;
	rndis->port.out_ep = ep;

	/* NOTE:  a status/notअगरication endpoपूर्णांक is, strictly speaking,
	 * optional.  We करोn't treat it that way though!  It's simpler,
	 * and some newer profiles करोn't treat it as optional.
	 */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_notअगरy_desc);
	अगर (!ep)
		जाओ fail;
	rndis->notअगरy = ep;

	status = -ENOMEM;

	/* allocate notअगरication request and buffer */
	rndis->notअगरy_req = usb_ep_alloc_request(ep, GFP_KERNEL);
	अगर (!rndis->notअगरy_req)
		जाओ fail;
	rndis->notअगरy_req->buf = kदो_स्मृति(STATUS_BYTECOUNT, GFP_KERNEL);
	अगर (!rndis->notअगरy_req->buf)
		जाओ fail;
	rndis->notअगरy_req->length = STATUS_BYTECOUNT;
	rndis->notअगरy_req->context = rndis;
	rndis->notअगरy_req->complete = rndis_response_complete;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */
	hs_in_desc.bEndpoपूर्णांकAddress = fs_in_desc.bEndpoपूर्णांकAddress;
	hs_out_desc.bEndpoपूर्णांकAddress = fs_out_desc.bEndpoपूर्णांकAddress;
	hs_notअगरy_desc.bEndpoपूर्णांकAddress = fs_notअगरy_desc.bEndpoपूर्णांकAddress;

	ss_in_desc.bEndpoपूर्णांकAddress = fs_in_desc.bEndpoपूर्णांकAddress;
	ss_out_desc.bEndpoपूर्णांकAddress = fs_out_desc.bEndpoपूर्णांकAddress;
	ss_notअगरy_desc.bEndpoपूर्णांकAddress = fs_notअगरy_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, eth_fs_function, eth_hs_function,
			eth_ss_function, eth_ss_function);
	अगर (status)
		जाओ fail;

	rndis->port.खोलो = rndis_खोलो;
	rndis->port.बंद = rndis_बंद;

	rndis_set_param_medium(rndis->params, RNDIS_MEDIUM_802_3, 0);
	rndis_set_host_mac(rndis->params, rndis->ethaddr);

	अगर (rndis->manufacturer && rndis->venकरोrID &&
			rndis_set_param_venकरोr(rndis->params, rndis->venकरोrID,
					       rndis->manufacturer)) अणु
		status = -EINVAL;
		जाओ fail_मुक्त_descs;
	पूर्ण

	/* NOTE:  all that is करोne without knowing or caring about
	 * the network link ... which is unavailable to this code
	 * until we're activated via set_alt().
	 */

	DBG(cdev, "RNDIS: %s speed IN/%s OUT/%s NOTIFY/%s\n",
			gadget_is_superspeed(c->cdev->gadget) ? "super" :
			gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
			rndis->port.in_ep->name, rndis->port.out_ep->name,
			rndis->notअगरy->name);
	वापस 0;

fail_मुक्त_descs:
	usb_मुक्त_all_descriptors(f);
fail:
	kमुक्त(f->os_desc_table);
	f->os_desc_n = 0;

	अगर (rndis->notअगरy_req) अणु
		kमुक्त(rndis->notअगरy_req->buf);
		usb_ep_मुक्त_request(rndis->notअगरy, rndis->notअगरy_req);
	पूर्ण

	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	वापस status;
पूर्ण

व्योम rndis_borrow_net(काष्ठा usb_function_instance *f, काष्ठा net_device *net)
अणु
	काष्ठा f_rndis_opts *opts;

	opts = container_of(f, काष्ठा f_rndis_opts, func_inst);
	अगर (opts->bound)
		gether_cleanup(netdev_priv(opts->net));
	अन्यथा
		मुक्त_netdev(opts->net);
	opts->borrowed_net = opts->bound = true;
	opts->net = net;
पूर्ण
EXPORT_SYMBOL_GPL(rndis_borrow_net);

अटल अंतरभूत काष्ठा f_rndis_opts *to_f_rndis_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_rndis_opts,
			    func_inst.group);
पूर्ण

/* f_rndis_item_ops */
USB_ETHERNET_CONFIGFS_ITEM(rndis);

/* f_rndis_opts_dev_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_DEV_ADDR(rndis);

/* f_rndis_opts_host_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_HOST_ADDR(rndis);

/* f_rndis_opts_qmult */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_QMULT(rndis);

/* f_rndis_opts_अगरname */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_IFNAME(rndis);

/* f_rndis_opts_class */
USB_ETHER_CONFIGFS_ITEM_ATTR_U8_RW(rndis, class);

/* f_rndis_opts_subclass */
USB_ETHER_CONFIGFS_ITEM_ATTR_U8_RW(rndis, subclass);

/* f_rndis_opts_protocol */
USB_ETHER_CONFIGFS_ITEM_ATTR_U8_RW(rndis, protocol);

अटल काष्ठा configfs_attribute *rndis_attrs[] = अणु
	&rndis_opts_attr_dev_addr,
	&rndis_opts_attr_host_addr,
	&rndis_opts_attr_qmult,
	&rndis_opts_attr_अगरname,
	&rndis_opts_attr_class,
	&rndis_opts_attr_subclass,
	&rndis_opts_attr_protocol,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type rndis_func_type = अणु
	.ct_item_ops	= &rndis_item_ops,
	.ct_attrs	= rndis_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम rndis_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_rndis_opts *opts;

	opts = container_of(f, काष्ठा f_rndis_opts, func_inst);
	अगर (!opts->borrowed_net) अणु
		अगर (opts->bound)
			gether_cleanup(netdev_priv(opts->net));
		अन्यथा
			मुक्त_netdev(opts->net);
	पूर्ण

	kमुक्त(opts->rndis_पूर्णांकerf_group);	/* single VLA chunk */
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *rndis_alloc_inst(व्योम)
अणु
	काष्ठा f_rndis_opts *opts;
	काष्ठा usb_os_desc *descs[1];
	अक्षर *names[1];
	काष्ठा config_group *rndis_पूर्णांकerf_group;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	opts->rndis_os_desc.ext_compat_id = opts->rndis_ext_compat_id;

	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = rndis_मुक्त_inst;
	opts->net = gether_setup_शेष();
	अगर (IS_ERR(opts->net)) अणु
		काष्ठा net_device *net = opts->net;
		kमुक्त(opts);
		वापस ERR_CAST(net);
	पूर्ण
	INIT_LIST_HEAD(&opts->rndis_os_desc.ext_prop);

	opts->class = rndis_iad_descriptor.bFunctionClass;
	opts->subclass = rndis_iad_descriptor.bFunctionSubClass;
	opts->protocol = rndis_iad_descriptor.bFunctionProtocol;

	descs[0] = &opts->rndis_os_desc;
	names[0] = "rndis";
	config_group_init_type_name(&opts->func_inst.group, "",
				    &rndis_func_type);
	rndis_पूर्णांकerf_group =
		usb_os_desc_prepare_पूर्णांकerf_dir(&opts->func_inst.group, 1, descs,
					       names, THIS_MODULE);
	अगर (IS_ERR(rndis_पूर्णांकerf_group)) अणु
		rndis_मुक्त_inst(&opts->func_inst);
		वापस ERR_CAST(rndis_पूर्णांकerf_group);
	पूर्ण
	opts->rndis_पूर्णांकerf_group = rndis_पूर्णांकerf_group;

	वापस &opts->func_inst;
पूर्ण

अटल व्योम rndis_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_rndis *rndis;
	काष्ठा f_rndis_opts *opts;

	rndis = func_to_rndis(f);
	rndis_deरेजिस्टर(rndis->params);
	opts = container_of(f->fi, काष्ठा f_rndis_opts, func_inst);
	kमुक्त(rndis);
	mutex_lock(&opts->lock);
	opts->refcnt--;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम rndis_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा f_rndis		*rndis = func_to_rndis(f);

	kमुक्त(f->os_desc_table);
	f->os_desc_n = 0;
	usb_मुक्त_all_descriptors(f);

	kमुक्त(rndis->notअगरy_req->buf);
	usb_ep_मुक्त_request(rndis->notअगरy, rndis->notअगरy_req);
पूर्ण

अटल काष्ठा usb_function *rndis_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_rndis	*rndis;
	काष्ठा f_rndis_opts *opts;
	काष्ठा rndis_params *params;

	/* allocate and initialize one new instance */
	rndis = kzalloc(माप(*rndis), GFP_KERNEL);
	अगर (!rndis)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_rndis_opts, func_inst);
	mutex_lock(&opts->lock);
	opts->refcnt++;

	gether_get_host_addr_u8(opts->net, rndis->ethaddr);
	rndis->venकरोrID = opts->venकरोr_id;
	rndis->manufacturer = opts->manufacturer;

	rndis->port.ioport = netdev_priv(opts->net);
	mutex_unlock(&opts->lock);
	/* RNDIS activates when the host changes this filter */
	rndis->port.cdc_filter = 0;

	/* RNDIS has special (and complex) framing */
	rndis->port.header_len = माप(काष्ठा rndis_packet_msg_type);
	rndis->port.wrap = rndis_add_header;
	rndis->port.unwrap = rndis_rm_hdr;

	rndis->port.func.name = "rndis";
	/* descriptors are per-instance copies */
	rndis->port.func.bind = rndis_bind;
	rndis->port.func.unbind = rndis_unbind;
	rndis->port.func.set_alt = rndis_set_alt;
	rndis->port.func.setup = rndis_setup;
	rndis->port.func.disable = rndis_disable;
	rndis->port.func.मुक्त_func = rndis_मुक्त;

	params = rndis_रेजिस्टर(rndis_response_available, rndis);
	अगर (IS_ERR(params)) अणु
		kमुक्त(rndis);
		वापस ERR_CAST(params);
	पूर्ण
	rndis->params = params;

	वापस &rndis->port.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(rndis, rndis_alloc_inst, rndis_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Brownell");
