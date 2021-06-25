<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_ecm.c -- USB CDC Ethernet (ECM) link function driver
 *
 * Copyright (C) 2003-2005,2008 David Brownell
 * Copyright (C) 2008 Nokia Corporation
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/etherdevice.h>

#समावेश "u_ether.h"
#समावेश "u_ether_configfs.h"
#समावेश "u_ecm.h"


/*
 * This function is a "CDC Ethernet Networking Control Model" (CDC ECM)
 * Ethernet link.  The data transfer model is simple (packets sent and
 * received over bulk endpoपूर्णांकs using normal लघु packet termination),
 * and the control model exposes various data and optional notअगरications.
 *
 * ECM is well standardized and (except क्रम Microsoft) supported by most
 * operating प्रणालीs with USB host support.  It's the preferred पूर्णांकerop
 * solution क्रम Ethernet over USB, at least क्रम firmware based solutions.
 * (Hardware solutions tend to be more minimalist.)  A newer and simpler
 * "Ethernet Emulation Model" (CDC EEM) hasn't yet caught on.
 *
 * Note that ECM requires the use of "alternate settings" क्रम its data
 * पूर्णांकerface.  This means that the set_alt() method has real work to करो,
 * and also means that a get_alt() method is required.
 */


क्रमागत ecm_notअगरy_state अणु
	ECM_NOTIFY_NONE,		/* करोn't notअगरy */
	ECM_NOTIFY_CONNECT,		/* issue CONNECT next */
	ECM_NOTIFY_SPEED,		/* issue SPEED_CHANGE next */
पूर्ण;

काष्ठा f_ecm अणु
	काष्ठा gether			port;
	u8				ctrl_id, data_id;

	अक्षर				ethaddr[14];

	काष्ठा usb_ep			*notअगरy;
	काष्ठा usb_request		*notअगरy_req;
	u8				notअगरy_state;
	atomic_t			notअगरy_count;
	bool				is_खोलो;

	/* FIXME is_खोलो needs some irq-ish locking
	 * ... possibly the same as port.ioport
	 */
पूर्ण;

अटल अंतरभूत काष्ठा f_ecm *func_to_ecm(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_ecm, port.func);
पूर्ण

/* peak (theoretical) bulk transfer rate in bits-per-second */
अटल अंतरभूत अचिन्हित ecm_bitrate(काष्ठा usb_gadget *g)
अणु
	अगर (gadget_is_superspeed(g) && g->speed == USB_SPEED_SUPER)
		वापस 13 * 1024 * 8 * 1000 * 8;
	अन्यथा अगर (gadget_is_dualspeed(g) && g->speed == USB_SPEED_HIGH)
		वापस 13 * 512 * 8 * 1000 * 8;
	अन्यथा
		वापस 19 * 64 * 1 * 1000 * 8;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Include the status endpoपूर्णांक अगर we can, even though it's optional.
 *
 * Use wMaxPacketSize big enough to fit CDC_NOTIFY_SPEED_CHANGE in one
 * packet, to simplअगरy cancellation; and a big transfer पूर्णांकerval, to
 * waste less bandwidth.
 *
 * Some drivers (like Linux 2.4 cdc-ether!) "need" it to exist even
 * अगर they ignore the connect/disconnect notअगरications that real aether
 * can provide.  More advanced cdc configurations might want to support
 * encapsulated commands (venकरोr-specअगरic, using control-OUT).
 */

#घोषणा ECM_STATUS_INTERVAL_MS		32
#घोषणा ECM_STATUS_BYTECOUNT		16	/* 8 byte header + data */


/* पूर्णांकerface descriptor: */

अटल काष्ठा usb_पूर्णांकerface_assoc_descriptor
ecm_iad_descriptor = अणु
	.bLength =		माप ecm_iad_descriptor,
	.bDescriptorType =	USB_DT_INTERFACE_ASSOCIATION,

	/* .bFirstInterface =	DYNAMIC, */
	.bInterfaceCount =	2,	/* control + data */
	.bFunctionClass =	USB_CLASS_COMM,
	.bFunctionSubClass =	USB_CDC_SUBCLASS_ETHERNET,
	.bFunctionProtocol =	USB_CDC_PROTO_NONE,
	/* .iFunction =		DYNAMIC */
पूर्ण;


अटल काष्ठा usb_पूर्णांकerface_descriptor ecm_control_पूर्णांकf = अणु
	.bLength =		माप ecm_control_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	/* .bInterfaceNumber = DYNAMIC */
	/* status endpoपूर्णांक is optional; this could be patched later */
	.bNumEndpoपूर्णांकs =	1,
	.bInterfaceClass =	USB_CLASS_COMM,
	.bInterfaceSubClass =	USB_CDC_SUBCLASS_ETHERNET,
	.bInterfaceProtocol =	USB_CDC_PROTO_NONE,
	/* .iInterface = DYNAMIC */
पूर्ण;

अटल काष्ठा usb_cdc_header_desc ecm_header_desc = अणु
	.bLength =		माप ecm_header_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_HEADER_TYPE,

	.bcdCDC =		cpu_to_le16(0x0110),
पूर्ण;

अटल काष्ठा usb_cdc_जोड़_desc ecm_जोड़_desc = अणु
	.bLength =		माप(ecm_जोड़_desc),
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_UNION_TYPE,
	/* .bMasterInterface0 =	DYNAMIC */
	/* .bSlaveInterface0 =	DYNAMIC */
पूर्ण;

अटल काष्ठा usb_cdc_ether_desc ecm_desc = अणु
	.bLength =		माप ecm_desc,
	.bDescriptorType =	USB_DT_CS_INTERFACE,
	.bDescriptorSubType =	USB_CDC_ETHERNET_TYPE,

	/* this descriptor actually adds value, surprise! */
	/* .iMACAddress = DYNAMIC */
	.bmEthernetStatistics =	cpu_to_le32(0), /* no statistics */
	.wMaxSegmentSize =	cpu_to_le16(ETH_FRAME_LEN),
	.wNumberMCFilters =	cpu_to_le16(0),
	.bNumberPowerFilters =	0,
पूर्ण;

/* the शेष data पूर्णांकerface has no endpoपूर्णांकs ... */

अटल काष्ठा usb_पूर्णांकerface_descriptor ecm_data_nop_पूर्णांकf = अणु
	.bLength =		माप ecm_data_nop_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	.bInterfaceNumber =	1,
	.bAlternateSetting =	0,
	.bNumEndpoपूर्णांकs =	0,
	.bInterfaceClass =	USB_CLASS_CDC_DATA,
	.bInterfaceSubClass =	0,
	.bInterfaceProtocol =	0,
	/* .iInterface = DYNAMIC */
पूर्ण;

/* ... but the "real" data पूर्णांकerface has two bulk endpoपूर्णांकs */

अटल काष्ठा usb_पूर्णांकerface_descriptor ecm_data_पूर्णांकf = अणु
	.bLength =		माप ecm_data_पूर्णांकf,
	.bDescriptorType =	USB_DT_INTERFACE,

	.bInterfaceNumber =	1,
	.bAlternateSetting =	1,
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_CDC_DATA,
	.bInterfaceSubClass =	0,
	.bInterfaceProtocol =	0,
	/* .iInterface = DYNAMIC */
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_ecm_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(ECM_STATUS_BYTECOUNT),
	.bInterval =		ECM_STATUS_INTERVAL_MS,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_ecm_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_ecm_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_descriptor_header *ecm_fs_function[] = अणु
	/* CDC ECM control descriptors */
	(काष्ठा usb_descriptor_header *) &ecm_iad_descriptor,
	(काष्ठा usb_descriptor_header *) &ecm_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ecm_header_desc,
	(काष्ठा usb_descriptor_header *) &ecm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &ecm_desc,

	/* NOTE: status endpoपूर्णांक might need to be हटाओd */
	(काष्ठा usb_descriptor_header *) &fs_ecm_notअगरy_desc,

	/* data पूर्णांकerface, altsettings 0 and 1 */
	(काष्ठा usb_descriptor_header *) &ecm_data_nop_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ecm_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &fs_ecm_in_desc,
	(काष्ठा usb_descriptor_header *) &fs_ecm_out_desc,
	शून्य,
पूर्ण;

/* high speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_ecm_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(ECM_STATUS_BYTECOUNT),
	.bInterval =		USB_MS_TO_HS_INTERVAL(ECM_STATUS_INTERVAL_MS),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_ecm_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_ecm_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_descriptor_header *ecm_hs_function[] = अणु
	/* CDC ECM control descriptors */
	(काष्ठा usb_descriptor_header *) &ecm_iad_descriptor,
	(काष्ठा usb_descriptor_header *) &ecm_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ecm_header_desc,
	(काष्ठा usb_descriptor_header *) &ecm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &ecm_desc,

	/* NOTE: status endpoपूर्णांक might need to be हटाओd */
	(काष्ठा usb_descriptor_header *) &hs_ecm_notअगरy_desc,

	/* data पूर्णांकerface, altsettings 0 and 1 */
	(काष्ठा usb_descriptor_header *) &ecm_data_nop_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ecm_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &hs_ecm_in_desc,
	(काष्ठा usb_descriptor_header *) &hs_ecm_out_desc,
	शून्य,
पूर्ण;

/* super speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_ecm_notअगरy_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize =	cpu_to_le16(ECM_STATUS_BYTECOUNT),
	.bInterval =		USB_MS_TO_HS_INTERVAL(ECM_STATUS_INTERVAL_MS),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_ecm_पूर्णांकr_comp_desc = अणु
	.bLength =		माप ss_ecm_पूर्णांकr_comp_desc,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/* the following 3 values can be tweaked अगर necessary */
	/* .bMaxBurst =		0, */
	/* .bmAttributes =	0, */
	.wBytesPerInterval =	cpu_to_le16(ECM_STATUS_BYTECOUNT),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_ecm_in_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_ecm_out_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_ecm_bulk_comp_desc = अणु
	.bLength =		माप ss_ecm_bulk_comp_desc,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	/* the following 2 values can be tweaked अगर necessary */
	/* .bMaxBurst =		0, */
	/* .bmAttributes =	0, */
पूर्ण;

अटल काष्ठा usb_descriptor_header *ecm_ss_function[] = अणु
	/* CDC ECM control descriptors */
	(काष्ठा usb_descriptor_header *) &ecm_iad_descriptor,
	(काष्ठा usb_descriptor_header *) &ecm_control_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ecm_header_desc,
	(काष्ठा usb_descriptor_header *) &ecm_जोड़_desc,
	(काष्ठा usb_descriptor_header *) &ecm_desc,

	/* NOTE: status endpoपूर्णांक might need to be हटाओd */
	(काष्ठा usb_descriptor_header *) &ss_ecm_notअगरy_desc,
	(काष्ठा usb_descriptor_header *) &ss_ecm_पूर्णांकr_comp_desc,

	/* data पूर्णांकerface, altsettings 0 and 1 */
	(काष्ठा usb_descriptor_header *) &ecm_data_nop_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ecm_data_पूर्णांकf,
	(काष्ठा usb_descriptor_header *) &ss_ecm_in_desc,
	(काष्ठा usb_descriptor_header *) &ss_ecm_bulk_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_ecm_out_desc,
	(काष्ठा usb_descriptor_header *) &ss_ecm_bulk_comp_desc,
	शून्य,
पूर्ण;

/* string descriptors: */

अटल काष्ठा usb_string ecm_string_defs[] = अणु
	[0].s = "CDC Ethernet Control Model (ECM)",
	[1].s = "",
	[2].s = "CDC Ethernet Data",
	[3].s = "CDC ECM",
	अणु  पूर्ण /* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings ecm_string_table = अणु
	.language =		0x0409,	/* en-us */
	.strings =		ecm_string_defs,
पूर्ण;

अटल काष्ठा usb_gadget_strings *ecm_strings[] = अणु
	&ecm_string_table,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल व्योम ecm_करो_notअगरy(काष्ठा f_ecm *ecm)
अणु
	काष्ठा usb_request		*req = ecm->notअगरy_req;
	काष्ठा usb_cdc_notअगरication	*event;
	काष्ठा usb_composite_dev	*cdev = ecm->port.func.config->cdev;
	__le32				*data;
	पूर्णांक				status;

	/* notअगरication alपढ़ोy in flight? */
	अगर (atomic_पढ़ो(&ecm->notअगरy_count))
		वापस;

	event = req->buf;
	चयन (ecm->notअगरy_state) अणु
	हाल ECM_NOTIFY_NONE:
		वापस;

	हाल ECM_NOTIFY_CONNECT:
		event->bNotअगरicationType = USB_CDC_NOTIFY_NETWORK_CONNECTION;
		अगर (ecm->is_खोलो)
			event->wValue = cpu_to_le16(1);
		अन्यथा
			event->wValue = cpu_to_le16(0);
		event->wLength = 0;
		req->length = माप *event;

		DBG(cdev, "notify connect %s\n",
				ecm->is_खोलो ? "true" : "false");
		ecm->notअगरy_state = ECM_NOTIFY_SPEED;
		अवरोध;

	हाल ECM_NOTIFY_SPEED:
		event->bNotअगरicationType = USB_CDC_NOTIFY_SPEED_CHANGE;
		event->wValue = cpu_to_le16(0);
		event->wLength = cpu_to_le16(8);
		req->length = ECM_STATUS_BYTECOUNT;

		/* SPEED_CHANGE data is up/करोwn speeds in bits/sec */
		data = req->buf + माप *event;
		data[0] = cpu_to_le32(ecm_bitrate(cdev->gadget));
		data[1] = data[0];

		DBG(cdev, "notify speed %d\n", ecm_bitrate(cdev->gadget));
		ecm->notअगरy_state = ECM_NOTIFY_NONE;
		अवरोध;
	पूर्ण
	event->bmRequestType = 0xA1;
	event->wIndex = cpu_to_le16(ecm->ctrl_id);

	atomic_inc(&ecm->notअगरy_count);
	status = usb_ep_queue(ecm->notअगरy, req, GFP_ATOMIC);
	अगर (status < 0) अणु
		atomic_dec(&ecm->notअगरy_count);
		DBG(cdev, "notify --> %d\n", status);
	पूर्ण
पूर्ण

अटल व्योम ecm_notअगरy(काष्ठा f_ecm *ecm)
अणु
	/* NOTE on most versions of Linux, host side cdc-ethernet
	 * won't listen क्रम notअगरications until its netdevice खोलोs.
	 * The first notअगरication then sits in the FIFO क्रम a दीर्घ
	 * समय, and the second one is queued.
	 */
	ecm->notअगरy_state = ECM_NOTIFY_CONNECT;
	ecm_करो_notअगरy(ecm);
पूर्ण

अटल व्योम ecm_notअगरy_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा f_ecm			*ecm = req->context;
	काष्ठा usb_composite_dev	*cdev = ecm->port.func.config->cdev;
	काष्ठा usb_cdc_notअगरication	*event = req->buf;

	चयन (req->status) अणु
	हाल 0:
		/* no fault */
		atomic_dec(&ecm->notअगरy_count);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		atomic_set(&ecm->notअगरy_count, 0);
		ecm->notअगरy_state = ECM_NOTIFY_NONE;
		अवरोध;
	शेष:
		DBG(cdev, "event %02x --> %d\n",
			event->bNotअगरicationType, req->status);
		atomic_dec(&ecm->notअगरy_count);
		अवरोध;
	पूर्ण
	ecm_करो_notअगरy(ecm);
पूर्ण

अटल पूर्णांक ecm_setup(काष्ठा usb_function *f, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा f_ecm		*ecm = func_to_ecm(f);
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
	हाल ((USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE) << 8)
			| USB_CDC_SET_ETHERNET_PACKET_FILTER:
		/* see 6.2.30: no data, wIndex = पूर्णांकerface,
		 * wValue = packet filter biपंचांगap
		 */
		अगर (w_length != 0 || w_index != ecm->ctrl_id)
			जाओ invalid;
		DBG(cdev, "packet filter %02x\n", w_value);
		/* REVISIT locking of cdc_filter.  This assumes the UDC
		 * driver won't have a concurrent packet TX irq running on
		 * another CPU; or that अगर it करोes, this ग_लिखो is atomic...
		 */
		ecm->port.cdc_filter = w_value;
		value = 0;
		अवरोध;

	/* and optionally:
	 * हाल USB_CDC_SEND_ENCAPSULATED_COMMAND:
	 * हाल USB_CDC_GET_ENCAPSULATED_RESPONSE:
	 * हाल USB_CDC_SET_ETHERNET_MULTICAST_FILTERS:
	 * हाल USB_CDC_SET_ETHERNET_PM_PATTERN_FILTER:
	 * हाल USB_CDC_GET_ETHERNET_PM_PATTERN_FILTER:
	 * हाल USB_CDC_GET_ETHERNET_STATISTIC:
	 */

	शेष:
invalid:
		DBG(cdev, "invalid control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
	पूर्ण

	/* respond with data transfer or status phase? */
	अगर (value >= 0) अणु
		DBG(cdev, "ecm req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
		req->zero = 0;
		req->length = value;
		value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
		अगर (value < 0)
			ERROR(cdev, "ecm req %02x.%02x response err %d\n",
					ctrl->bRequestType, ctrl->bRequest,
					value);
	पूर्ण

	/* device either stalls (value < 0) or reports success */
	वापस value;
पूर्ण


अटल पूर्णांक ecm_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_ecm		*ecm = func_to_ecm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	/* Control पूर्णांकerface has only altsetting 0 */
	अगर (पूर्णांकf == ecm->ctrl_id) अणु
		अगर (alt != 0)
			जाओ fail;

		VDBG(cdev, "reset ecm control %d\n", पूर्णांकf);
		usb_ep_disable(ecm->notअगरy);
		अगर (!(ecm->notअगरy->desc)) अणु
			VDBG(cdev, "init ecm ctrl %d\n", पूर्णांकf);
			अगर (config_ep_by_speed(cdev->gadget, f, ecm->notअगरy))
				जाओ fail;
		पूर्ण
		usb_ep_enable(ecm->notअगरy);

	/* Data पूर्णांकerface has two altsettings, 0 and 1 */
	पूर्ण अन्यथा अगर (पूर्णांकf == ecm->data_id) अणु
		अगर (alt > 1)
			जाओ fail;

		अगर (ecm->port.in_ep->enabled) अणु
			DBG(cdev, "reset ecm\n");
			gether_disconnect(&ecm->port);
		पूर्ण

		अगर (!ecm->port.in_ep->desc ||
		    !ecm->port.out_ep->desc) अणु
			DBG(cdev, "init ecm\n");
			अगर (config_ep_by_speed(cdev->gadget, f,
					       ecm->port.in_ep) ||
			    config_ep_by_speed(cdev->gadget, f,
					       ecm->port.out_ep)) अणु
				ecm->port.in_ep->desc = शून्य;
				ecm->port.out_ep->desc = शून्य;
				जाओ fail;
			पूर्ण
		पूर्ण

		/* CDC Ethernet only sends data in non-शेष altsettings.
		 * Changing altsettings resets filters, statistics, etc.
		 */
		अगर (alt == 1) अणु
			काष्ठा net_device	*net;

			/* Enable zlps by शेष क्रम ECM conक्रमmance;
			 * override क्रम musb_hdrc (aव्योमs txdma ovhead).
			 */
			ecm->port.is_zlp_ok =
				gadget_is_zlp_supported(cdev->gadget);
			ecm->port.cdc_filter = DEFAULT_FILTER;
			DBG(cdev, "activate ecm\n");
			net = gether_connect(&ecm->port);
			अगर (IS_ERR(net))
				वापस PTR_ERR(net);
		पूर्ण

		/* NOTE this can be a minor disagreement with the ECM spec,
		 * which says speed notअगरications will "always" follow
		 * connection notअगरications.  But we allow one connect to
		 * follow another (अगर the first is in flight), and instead
		 * just guarantee that a speed notअगरication is always sent.
		 */
		ecm_notअगरy(ecm);
	पूर्ण अन्यथा
		जाओ fail;

	वापस 0;
fail:
	वापस -EINVAL;
पूर्ण

/* Because the data पूर्णांकerface supports multiple altsettings,
 * this ECM function *MUST* implement a get_alt() method.
 */
अटल पूर्णांक ecm_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf)
अणु
	काष्ठा f_ecm		*ecm = func_to_ecm(f);

	अगर (पूर्णांकf == ecm->ctrl_id)
		वापस 0;
	वापस ecm->port.in_ep->enabled ? 1 : 0;
पूर्ण

अटल व्योम ecm_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_ecm		*ecm = func_to_ecm(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "ecm deactivated\n");

	अगर (ecm->port.in_ep->enabled) अणु
		gether_disconnect(&ecm->port);
	पूर्ण अन्यथा अणु
		ecm->port.in_ep->desc = शून्य;
		ecm->port.out_ep->desc = शून्य;
	पूर्ण

	usb_ep_disable(ecm->notअगरy);
	ecm->notअगरy->desc = शून्य;
पूर्ण

/*-------------------------------------------------------------------------*/

/*
 * Callbacks let us notअगरy the host about connect/disconnect when the
 * net device is खोलोed or बंदd.
 *
 * For testing, note that link states on this side include both खोलोed
 * and बंदd variants of:
 *
 *   - disconnected/unconfigured
 *   - configured but inactive (data alt 0)
 *   - configured and active (data alt 1)
 *
 * Each needs to be tested with unplug, rmmod, SET_CONFIGURATION, and
 * SET_INTERFACE (altsetting).  Remember also that "configured" करोesn't
 * imply the host is actually polling the notअगरication endpoपूर्णांक, and
 * likewise that "active" करोesn't imply it's actually using the data
 * endpoपूर्णांकs क्रम traffic.
 */

अटल व्योम ecm_खोलो(काष्ठा gether *geth)
अणु
	काष्ठा f_ecm		*ecm = func_to_ecm(&geth->func);

	DBG(ecm->port.func.config->cdev, "%s\n", __func__);

	ecm->is_खोलो = true;
	ecm_notअगरy(ecm);
पूर्ण

अटल व्योम ecm_बंद(काष्ठा gether *geth)
अणु
	काष्ठा f_ecm		*ecm = func_to_ecm(&geth->func);

	DBG(ecm->port.func.config->cdev, "%s\n", __func__);

	ecm->is_खोलो = false;
	ecm_notअगरy(ecm);
पूर्ण

/*-------------------------------------------------------------------------*/

/* ethernet function driver setup/binding */

अटल पूर्णांक
ecm_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_ecm		*ecm = func_to_ecm(f);
	काष्ठा usb_string	*us;
	पूर्णांक			status;
	काष्ठा usb_ep		*ep;

	काष्ठा f_ecm_opts	*ecm_opts;

	अगर (!can_support_ecm(cdev->gadget))
		वापस -EINVAL;

	ecm_opts = container_of(f->fi, काष्ठा f_ecm_opts, func_inst);

	/*
	 * in drivers/usb/gadget/configfs.c:configfs_composite_bind()
	 * configurations are bound in sequence with list_क्रम_each_entry,
	 * in each configuration its functions are bound in sequence
	 * with list_क्रम_each_entry, so we assume no race condition
	 * with regard to ecm_opts->bound access
	 */
	अगर (!ecm_opts->bound) अणु
		mutex_lock(&ecm_opts->lock);
		gether_set_gadget(ecm_opts->net, cdev->gadget);
		status = gether_रेजिस्टर_netdev(ecm_opts->net);
		mutex_unlock(&ecm_opts->lock);
		अगर (status)
			वापस status;
		ecm_opts->bound = true;
	पूर्ण

	ecm_string_defs[1].s = ecm->ethaddr;

	us = usb_gstrings_attach(cdev, ecm_strings,
				 ARRAY_SIZE(ecm_string_defs));
	अगर (IS_ERR(us))
		वापस PTR_ERR(us);
	ecm_control_पूर्णांकf.iInterface = us[0].id;
	ecm_data_पूर्णांकf.iInterface = us[2].id;
	ecm_desc.iMACAddress = us[1].id;
	ecm_iad_descriptor.iFunction = us[3].id;

	/* allocate instance-specअगरic पूर्णांकerface IDs */
	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	ecm->ctrl_id = status;
	ecm_iad_descriptor.bFirstInterface = status;

	ecm_control_पूर्णांकf.bInterfaceNumber = status;
	ecm_जोड़_desc.bMasterInterface0 = status;

	status = usb_पूर्णांकerface_id(c, f);
	अगर (status < 0)
		जाओ fail;
	ecm->data_id = status;

	ecm_data_nop_पूर्णांकf.bInterfaceNumber = status;
	ecm_data_पूर्णांकf.bInterfaceNumber = status;
	ecm_जोड़_desc.bSlaveInterface0 = status;

	status = -ENODEV;

	/* allocate instance-specअगरic endpoपूर्णांकs */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_ecm_in_desc);
	अगर (!ep)
		जाओ fail;
	ecm->port.in_ep = ep;

	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_ecm_out_desc);
	अगर (!ep)
		जाओ fail;
	ecm->port.out_ep = ep;

	/* NOTE:  a status/notअगरication endpoपूर्णांक is *OPTIONAL* but we
	 * करोn't treat it that way.  It's simpler, and some newer CDC
	 * profiles (wireless handsets) no दीर्घer treat it as optional.
	 */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_ecm_notअगरy_desc);
	अगर (!ep)
		जाओ fail;
	ecm->notअगरy = ep;

	status = -ENOMEM;

	/* allocate notअगरication request and buffer */
	ecm->notअगरy_req = usb_ep_alloc_request(ep, GFP_KERNEL);
	अगर (!ecm->notअगरy_req)
		जाओ fail;
	ecm->notअगरy_req->buf = kदो_स्मृति(ECM_STATUS_BYTECOUNT, GFP_KERNEL);
	अगर (!ecm->notअगरy_req->buf)
		जाओ fail;
	ecm->notअगरy_req->context = ecm;
	ecm->notअगरy_req->complete = ecm_notअगरy_complete;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoपूर्णांकs work at
	 * both speeds
	 */
	hs_ecm_in_desc.bEndpoपूर्णांकAddress = fs_ecm_in_desc.bEndpoपूर्णांकAddress;
	hs_ecm_out_desc.bEndpoपूर्णांकAddress = fs_ecm_out_desc.bEndpoपूर्णांकAddress;
	hs_ecm_notअगरy_desc.bEndpoपूर्णांकAddress =
		fs_ecm_notअगरy_desc.bEndpoपूर्णांकAddress;

	ss_ecm_in_desc.bEndpoपूर्णांकAddress = fs_ecm_in_desc.bEndpoपूर्णांकAddress;
	ss_ecm_out_desc.bEndpoपूर्णांकAddress = fs_ecm_out_desc.bEndpoपूर्णांकAddress;
	ss_ecm_notअगरy_desc.bEndpoपूर्णांकAddress =
		fs_ecm_notअगरy_desc.bEndpoपूर्णांकAddress;

	status = usb_assign_descriptors(f, ecm_fs_function, ecm_hs_function,
			ecm_ss_function, ecm_ss_function);
	अगर (status)
		जाओ fail;

	/* NOTE:  all that is करोne without knowing or caring about
	 * the network link ... which is unavailable to this code
	 * until we're activated via set_alt().
	 */

	ecm->port.खोलो = ecm_खोलो;
	ecm->port.बंद = ecm_बंद;

	DBG(cdev, "CDC Ethernet: %s speed IN/%s OUT/%s NOTIFY/%s\n",
			gadget_is_superspeed(c->cdev->gadget) ? "super" :
			gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
			ecm->port.in_ep->name, ecm->port.out_ep->name,
			ecm->notअगरy->name);
	वापस 0;

fail:
	अगर (ecm->notअगरy_req) अणु
		kमुक्त(ecm->notअगरy_req->buf);
		usb_ep_मुक्त_request(ecm->notअगरy, ecm->notअगरy_req);
	पूर्ण

	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	वापस status;
पूर्ण

अटल अंतरभूत काष्ठा f_ecm_opts *to_f_ecm_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_ecm_opts,
			    func_inst.group);
पूर्ण

/* f_ecm_item_ops */
USB_ETHERNET_CONFIGFS_ITEM(ecm);

/* f_ecm_opts_dev_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_DEV_ADDR(ecm);

/* f_ecm_opts_host_addr */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_HOST_ADDR(ecm);

/* f_ecm_opts_qmult */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_QMULT(ecm);

/* f_ecm_opts_अगरname */
USB_ETHERNET_CONFIGFS_ITEM_ATTR_IFNAME(ecm);

अटल काष्ठा configfs_attribute *ecm_attrs[] = अणु
	&ecm_opts_attr_dev_addr,
	&ecm_opts_attr_host_addr,
	&ecm_opts_attr_qmult,
	&ecm_opts_attr_अगरname,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type ecm_func_type = अणु
	.ct_item_ops	= &ecm_item_ops,
	.ct_attrs	= ecm_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम ecm_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_ecm_opts *opts;

	opts = container_of(f, काष्ठा f_ecm_opts, func_inst);
	अगर (opts->bound)
		gether_cleanup(netdev_priv(opts->net));
	अन्यथा
		मुक्त_netdev(opts->net);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *ecm_alloc_inst(व्योम)
अणु
	काष्ठा f_ecm_opts *opts;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	mutex_init(&opts->lock);
	opts->func_inst.मुक्त_func_inst = ecm_मुक्त_inst;
	opts->net = gether_setup_शेष();
	अगर (IS_ERR(opts->net)) अणु
		काष्ठा net_device *net = opts->net;
		kमुक्त(opts);
		वापस ERR_CAST(net);
	पूर्ण

	config_group_init_type_name(&opts->func_inst.group, "", &ecm_func_type);

	वापस &opts->func_inst;
पूर्ण

अटल व्योम ecm_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा f_ecm *ecm;
	काष्ठा f_ecm_opts *opts;

	ecm = func_to_ecm(f);
	opts = container_of(f->fi, काष्ठा f_ecm_opts, func_inst);
	kमुक्त(ecm);
	mutex_lock(&opts->lock);
	opts->refcnt--;
	mutex_unlock(&opts->lock);
पूर्ण

अटल व्योम ecm_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा f_ecm		*ecm = func_to_ecm(f);

	DBG(c->cdev, "ecm unbind\n");

	usb_मुक्त_all_descriptors(f);

	अगर (atomic_पढ़ो(&ecm->notअगरy_count)) अणु
		usb_ep_dequeue(ecm->notअगरy, ecm->notअगरy_req);
		atomic_set(&ecm->notअगरy_count, 0);
	पूर्ण

	kमुक्त(ecm->notअगरy_req->buf);
	usb_ep_मुक्त_request(ecm->notअगरy, ecm->notअगरy_req);
पूर्ण

अटल काष्ठा usb_function *ecm_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_ecm	*ecm;
	काष्ठा f_ecm_opts *opts;
	पूर्णांक status;

	/* allocate and initialize one new instance */
	ecm = kzalloc(माप(*ecm), GFP_KERNEL);
	अगर (!ecm)
		वापस ERR_PTR(-ENOMEM);

	opts = container_of(fi, काष्ठा f_ecm_opts, func_inst);
	mutex_lock(&opts->lock);
	opts->refcnt++;

	/* export host's Ethernet address in CDC क्रमmat */
	status = gether_get_host_addr_cdc(opts->net, ecm->ethaddr,
					  माप(ecm->ethaddr));
	अगर (status < 12) अणु
		kमुक्त(ecm);
		mutex_unlock(&opts->lock);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ecm->port.ioport = netdev_priv(opts->net);
	mutex_unlock(&opts->lock);
	ecm->port.cdc_filter = DEFAULT_FILTER;

	ecm->port.func.name = "cdc_ethernet";
	/* descriptors are per-instance copies */
	ecm->port.func.bind = ecm_bind;
	ecm->port.func.unbind = ecm_unbind;
	ecm->port.func.set_alt = ecm_set_alt;
	ecm->port.func.get_alt = ecm_get_alt;
	ecm->port.func.setup = ecm_setup;
	ecm->port.func.disable = ecm_disable;
	ecm->port.func.मुक्त_func = ecm_मुक्त;

	वापस &ecm->port.func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(ecm, ecm_alloc_inst, ecm_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Brownell");
