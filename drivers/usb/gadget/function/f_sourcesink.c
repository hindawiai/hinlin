<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * f_sourcesink.c - USB peripheral source/sink configuration driver
 *
 * Copyright (C) 2003-2008 David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

/* #घोषणा VERBOSE_DEBUG */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/composite.h>
#समावेश <linux/err.h>

#समावेश "g_zero.h"
#समावेश "u_f.h"

/*
 * SOURCE/SINK FUNCTION ... a primary testing vehicle क्रम USB peripheral
 * controller drivers.
 *
 * This just sinks bulk packets OUT to the peripheral and sources them IN
 * to the host, optionally with specअगरic data patterns क्रम पूर्णांकegrity tests.
 * As such it supports basic functionality and load tests.
 *
 * In terms of control messaging, this supports all the standard requests
 * plus two that support control-OUT tests.  If the optional "autoresume"
 * mode is enabled, it provides good functional coverage क्रम the "USBCV"
 * test harness from USB-IF.
 */
काष्ठा f_sourcesink अणु
	काष्ठा usb_function	function;

	काष्ठा usb_ep		*in_ep;
	काष्ठा usb_ep		*out_ep;
	काष्ठा usb_ep		*iso_in_ep;
	काष्ठा usb_ep		*iso_out_ep;
	पूर्णांक			cur_alt;

	अचिन्हित pattern;
	अचिन्हित isoc_पूर्णांकerval;
	अचिन्हित isoc_maxpacket;
	अचिन्हित isoc_mult;
	अचिन्हित isoc_maxburst;
	अचिन्हित buflen;
	अचिन्हित bulk_qlen;
	अचिन्हित iso_qlen;
पूर्ण;

अटल अंतरभूत काष्ठा f_sourcesink *func_to_ss(काष्ठा usb_function *f)
अणु
	वापस container_of(f, काष्ठा f_sourcesink, function);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल काष्ठा usb_पूर्णांकerface_descriptor source_sink_पूर्णांकf_alt0 = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,

	.bAlternateSetting =	0,
	.bNumEndpoपूर्णांकs =	2,
	.bInterfaceClass =	USB_CLASS_VENDOR_SPEC,
	/* .iInterface		= DYNAMIC */
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor source_sink_पूर्णांकf_alt1 = अणु
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,

	.bAlternateSetting =	1,
	.bNumEndpoपूर्णांकs =	4,
	.bInterfaceClass =	USB_CLASS_VENDOR_SPEC,
	/* .iInterface		= DYNAMIC */
पूर्ण;

/* full speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_iso_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize =	cpu_to_le16(1023),
	.bInterval =		4,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor fs_iso_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress =	USB_सूची_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize =	cpu_to_le16(1023),
	.bInterval =		4,
पूर्ण;

अटल काष्ठा usb_descriptor_header *fs_source_sink_descs[] = अणु
	(काष्ठा usb_descriptor_header *) &source_sink_पूर्णांकf_alt0,
	(काष्ठा usb_descriptor_header *) &fs_sink_desc,
	(काष्ठा usb_descriptor_header *) &fs_source_desc,
	(काष्ठा usb_descriptor_header *) &source_sink_पूर्णांकf_alt1,
#घोषणा FS_ALT_IFC_1_OFFSET	3
	(काष्ठा usb_descriptor_header *) &fs_sink_desc,
	(काष्ठा usb_descriptor_header *) &fs_source_desc,
	(काष्ठा usb_descriptor_header *) &fs_iso_sink_desc,
	(काष्ठा usb_descriptor_header *) &fs_iso_source_desc,
	शून्य,
पूर्ण;

/* high speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_iso_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize =	cpu_to_le16(1024),
	.bInterval =		4,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor hs_iso_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize =	cpu_to_le16(1024),
	.bInterval =		4,
पूर्ण;

अटल काष्ठा usb_descriptor_header *hs_source_sink_descs[] = अणु
	(काष्ठा usb_descriptor_header *) &source_sink_पूर्णांकf_alt0,
	(काष्ठा usb_descriptor_header *) &hs_source_desc,
	(काष्ठा usb_descriptor_header *) &hs_sink_desc,
	(काष्ठा usb_descriptor_header *) &source_sink_पूर्णांकf_alt1,
#घोषणा HS_ALT_IFC_1_OFFSET	3
	(काष्ठा usb_descriptor_header *) &hs_source_desc,
	(काष्ठा usb_descriptor_header *) &hs_sink_desc,
	(काष्ठा usb_descriptor_header *) &hs_iso_source_desc,
	(काष्ठा usb_descriptor_header *) &hs_iso_sink_desc,
	शून्य,
पूर्ण;

/* super speed support: */

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_source_comp_desc = अणु
	.bLength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	.bMaxBurst =		0,
	.bmAttributes =		0,
	.wBytesPerInterval =	0,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_sink_comp_desc = अणु
	.bLength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	.bMaxBurst =		0,
	.bmAttributes =		0,
	.wBytesPerInterval =	0,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_iso_source_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize =	cpu_to_le16(1024),
	.bInterval =		4,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_iso_source_comp_desc = अणु
	.bLength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	.bMaxBurst =		0,
	.bmAttributes =		0,
	.wBytesPerInterval =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor ss_iso_sink_desc = अणु
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,

	.bmAttributes =		USB_ENDPOINT_XFER_ISOC,
	.wMaxPacketSize =	cpu_to_le16(1024),
	.bInterval =		4,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor ss_iso_sink_comp_desc = अणु
	.bLength =		USB_DT_SS_EP_COMP_SIZE,
	.bDescriptorType =	USB_DT_SS_ENDPOINT_COMP,

	.bMaxBurst =		0,
	.bmAttributes =		0,
	.wBytesPerInterval =	cpu_to_le16(1024),
पूर्ण;

अटल काष्ठा usb_descriptor_header *ss_source_sink_descs[] = अणु
	(काष्ठा usb_descriptor_header *) &source_sink_पूर्णांकf_alt0,
	(काष्ठा usb_descriptor_header *) &ss_source_desc,
	(काष्ठा usb_descriptor_header *) &ss_source_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_sink_desc,
	(काष्ठा usb_descriptor_header *) &ss_sink_comp_desc,
	(काष्ठा usb_descriptor_header *) &source_sink_पूर्णांकf_alt1,
#घोषणा SS_ALT_IFC_1_OFFSET	5
	(काष्ठा usb_descriptor_header *) &ss_source_desc,
	(काष्ठा usb_descriptor_header *) &ss_source_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_sink_desc,
	(काष्ठा usb_descriptor_header *) &ss_sink_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_iso_source_desc,
	(काष्ठा usb_descriptor_header *) &ss_iso_source_comp_desc,
	(काष्ठा usb_descriptor_header *) &ss_iso_sink_desc,
	(काष्ठा usb_descriptor_header *) &ss_iso_sink_comp_desc,
	शून्य,
पूर्ण;

/* function-specअगरic strings: */

अटल काष्ठा usb_string strings_sourcesink[] = अणु
	[0].s = "source and sink data",
	अणु  पूर्ण			/* end of list */
पूर्ण;

अटल काष्ठा usb_gadget_strings stringtab_sourcesink = अणु
	.language	= 0x0409,	/* en-us */
	.strings	= strings_sourcesink,
पूर्ण;

अटल काष्ठा usb_gadget_strings *sourcesink_strings[] = अणु
	&stringtab_sourcesink,
	शून्य,
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल अंतरभूत काष्ठा usb_request *ss_alloc_ep_req(काष्ठा usb_ep *ep, पूर्णांक len)
अणु
	वापस alloc_ep_req(ep, len);
पूर्ण

अटल व्योम disable_ep(काष्ठा usb_composite_dev *cdev, काष्ठा usb_ep *ep)
अणु
	पूर्णांक			value;

	value = usb_ep_disable(ep);
	अगर (value < 0)
		DBG(cdev, "disable %s --> %d\n", ep->name, value);
पूर्ण

व्योम disable_endpoपूर्णांकs(काष्ठा usb_composite_dev *cdev,
		काष्ठा usb_ep *in, काष्ठा usb_ep *out,
		काष्ठा usb_ep *iso_in, काष्ठा usb_ep *iso_out)
अणु
	disable_ep(cdev, in);
	disable_ep(cdev, out);
	अगर (iso_in)
		disable_ep(cdev, iso_in);
	अगर (iso_out)
		disable_ep(cdev, iso_out);
पूर्ण

अटल पूर्णांक
sourcesink_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा f_sourcesink	*ss = func_to_ss(f);
	पूर्णांक	id;
	पूर्णांक ret;

	/* allocate पूर्णांकerface ID(s) */
	id = usb_पूर्णांकerface_id(c, f);
	अगर (id < 0)
		वापस id;
	source_sink_पूर्णांकf_alt0.bInterfaceNumber = id;
	source_sink_पूर्णांकf_alt1.bInterfaceNumber = id;

	/* allocate bulk endpoपूर्णांकs */
	ss->in_ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_source_desc);
	अगर (!ss->in_ep) अणु
स्वतःconf_fail:
		ERROR(cdev, "%s: can't autoconfigure on %s\n",
			f->name, cdev->gadget->name);
		वापस -ENODEV;
	पूर्ण

	ss->out_ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_sink_desc);
	अगर (!ss->out_ep)
		जाओ स्वतःconf_fail;

	/* sanity check the isoc module parameters */
	अगर (ss->isoc_पूर्णांकerval < 1)
		ss->isoc_पूर्णांकerval = 1;
	अगर (ss->isoc_पूर्णांकerval > 16)
		ss->isoc_पूर्णांकerval = 16;
	अगर (ss->isoc_mult > 2)
		ss->isoc_mult = 2;
	अगर (ss->isoc_maxburst > 15)
		ss->isoc_maxburst = 15;

	/* fill in the FS isoc descriptors from the module parameters */
	fs_iso_source_desc.wMaxPacketSize = ss->isoc_maxpacket > 1023 ?
						1023 : ss->isoc_maxpacket;
	fs_iso_source_desc.bInterval = ss->isoc_पूर्णांकerval;
	fs_iso_sink_desc.wMaxPacketSize = ss->isoc_maxpacket > 1023 ?
						1023 : ss->isoc_maxpacket;
	fs_iso_sink_desc.bInterval = ss->isoc_पूर्णांकerval;

	/* allocate iso endpoपूर्णांकs */
	ss->iso_in_ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_iso_source_desc);
	अगर (!ss->iso_in_ep)
		जाओ no_iso;

	ss->iso_out_ep = usb_ep_स्वतःconfig(cdev->gadget, &fs_iso_sink_desc);
	अगर (!ss->iso_out_ep) अणु
		usb_ep_स्वतःconfig_release(ss->iso_in_ep);
		ss->iso_in_ep = शून्य;
no_iso:
		/*
		 * We still want to work even अगर the UDC करोesn't have isoc
		 * endpoपूर्णांकs, so null out the alt पूर्णांकerface that contains
		 * them and जारी.
		 */
		fs_source_sink_descs[FS_ALT_IFC_1_OFFSET] = शून्य;
		hs_source_sink_descs[HS_ALT_IFC_1_OFFSET] = शून्य;
		ss_source_sink_descs[SS_ALT_IFC_1_OFFSET] = शून्य;
	पूर्ण

	अगर (ss->isoc_maxpacket > 1024)
		ss->isoc_maxpacket = 1024;

	/* support high speed hardware */
	hs_source_desc.bEndpoपूर्णांकAddress = fs_source_desc.bEndpoपूर्णांकAddress;
	hs_sink_desc.bEndpoपूर्णांकAddress = fs_sink_desc.bEndpoपूर्णांकAddress;

	/*
	 * Fill in the HS isoc descriptors from the module parameters.
	 * We assume that the user knows what they are करोing and won't
	 * give parameters that their UDC करोesn't support.
	 */
	hs_iso_source_desc.wMaxPacketSize = ss->isoc_maxpacket;
	hs_iso_source_desc.wMaxPacketSize |= ss->isoc_mult << 11;
	hs_iso_source_desc.bInterval = ss->isoc_पूर्णांकerval;
	hs_iso_source_desc.bEndpoपूर्णांकAddress =
		fs_iso_source_desc.bEndpoपूर्णांकAddress;

	hs_iso_sink_desc.wMaxPacketSize = ss->isoc_maxpacket;
	hs_iso_sink_desc.wMaxPacketSize |= ss->isoc_mult << 11;
	hs_iso_sink_desc.bInterval = ss->isoc_पूर्णांकerval;
	hs_iso_sink_desc.bEndpoपूर्णांकAddress = fs_iso_sink_desc.bEndpoपूर्णांकAddress;

	/* support super speed hardware */
	ss_source_desc.bEndpoपूर्णांकAddress =
		fs_source_desc.bEndpoपूर्णांकAddress;
	ss_sink_desc.bEndpoपूर्णांकAddress =
		fs_sink_desc.bEndpoपूर्णांकAddress;

	/*
	 * Fill in the SS isoc descriptors from the module parameters.
	 * We assume that the user knows what they are करोing and won't
	 * give parameters that their UDC करोesn't support.
	 */
	ss_iso_source_desc.wMaxPacketSize = ss->isoc_maxpacket;
	ss_iso_source_desc.bInterval = ss->isoc_पूर्णांकerval;
	ss_iso_source_comp_desc.bmAttributes = ss->isoc_mult;
	ss_iso_source_comp_desc.bMaxBurst = ss->isoc_maxburst;
	ss_iso_source_comp_desc.wBytesPerInterval = ss->isoc_maxpacket *
		(ss->isoc_mult + 1) * (ss->isoc_maxburst + 1);
	ss_iso_source_desc.bEndpoपूर्णांकAddress =
		fs_iso_source_desc.bEndpoपूर्णांकAddress;

	ss_iso_sink_desc.wMaxPacketSize = ss->isoc_maxpacket;
	ss_iso_sink_desc.bInterval = ss->isoc_पूर्णांकerval;
	ss_iso_sink_comp_desc.bmAttributes = ss->isoc_mult;
	ss_iso_sink_comp_desc.bMaxBurst = ss->isoc_maxburst;
	ss_iso_sink_comp_desc.wBytesPerInterval = ss->isoc_maxpacket *
		(ss->isoc_mult + 1) * (ss->isoc_maxburst + 1);
	ss_iso_sink_desc.bEndpoपूर्णांकAddress = fs_iso_sink_desc.bEndpoपूर्णांकAddress;

	ret = usb_assign_descriptors(f, fs_source_sink_descs,
			hs_source_sink_descs, ss_source_sink_descs,
			ss_source_sink_descs);
	अगर (ret)
		वापस ret;

	DBG(cdev, "%s speed %s: IN/%s, OUT/%s, ISO-IN/%s, ISO-OUT/%s\n",
	    (gadget_is_superspeed(c->cdev->gadget) ? "super" :
	     (gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full")),
			f->name, ss->in_ep->name, ss->out_ep->name,
			ss->iso_in_ep ? ss->iso_in_ep->name : "<none>",
			ss->iso_out_ep ? ss->iso_out_ep->name : "<none>");
	वापस 0;
पूर्ण

अटल व्योम
sourcesink_मुक्त_func(काष्ठा usb_function *f)
अणु
	काष्ठा f_ss_opts *opts;

	opts = container_of(f->fi, काष्ठा f_ss_opts, func_inst);

	mutex_lock(&opts->lock);
	opts->refcnt--;
	mutex_unlock(&opts->lock);

	usb_मुक्त_all_descriptors(f);
	kमुक्त(func_to_ss(f));
पूर्ण

/* optionally require specअगरic source/sink data patterns  */
अटल पूर्णांक check_पढ़ो_data(काष्ठा f_sourcesink *ss, काष्ठा usb_request *req)
अणु
	अचिन्हित		i;
	u8			*buf = req->buf;
	काष्ठा usb_composite_dev *cdev = ss->function.config->cdev;
	पूर्णांक max_packet_size = le16_to_cpu(ss->out_ep->desc->wMaxPacketSize);

	अगर (ss->pattern == 2)
		वापस 0;

	क्रम (i = 0; i < req->actual; i++, buf++) अणु
		चयन (ss->pattern) अणु

		/* all-zeroes has no synchronization issues */
		हाल 0:
			अगर (*buf == 0)
				जारी;
			अवरोध;

		/* "mod63" stays in sync with लघु-terminated transfers,
		 * OR otherwise when host and gadget agree on how large
		 * each usb transfer request should be.  Resync is करोne
		 * with set_पूर्णांकerface or set_config.  (We *WANT* it to
		 * get quickly out of sync अगर controllers or their drivers
		 * stutter क्रम any reason, including buffer duplication...)
		 */
		हाल 1:
			अगर (*buf == (u8)((i % max_packet_size) % 63))
				जारी;
			अवरोध;
		पूर्ण
		ERROR(cdev, "bad OUT byte, buf[%d] = %d\n", i, *buf);
		usb_ep_set_halt(ss->out_ep);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम reinit_ग_लिखो_data(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	अचिन्हित	i;
	u8		*buf = req->buf;
	पूर्णांक max_packet_size = le16_to_cpu(ep->desc->wMaxPacketSize);
	काष्ठा f_sourcesink *ss = ep->driver_data;

	चयन (ss->pattern) अणु
	हाल 0:
		स_रखो(req->buf, 0, req->length);
		अवरोध;
	हाल 1:
		क्रम  (i = 0; i < req->length; i++)
			*buf++ = (u8) ((i % max_packet_size) % 63);
		अवरोध;
	हाल 2:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम source_sink_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा usb_composite_dev	*cdev;
	काष्ठा f_sourcesink		*ss = ep->driver_data;
	पूर्णांक				status = req->status;

	/* driver_data will be null अगर ep has been disabled */
	अगर (!ss)
		वापस;

	cdev = ss->function.config->cdev;

	चयन (status) अणु

	हाल 0:				/* normal completion? */
		अगर (ep == ss->out_ep) अणु
			check_पढ़ो_data(ss, req);
			अगर (ss->pattern != 2)
				स_रखो(req->buf, 0x55, req->length);
		पूर्ण
		अवरोध;

	/* this endpoपूर्णांक is normally active जबतक we're configured */
	हाल -ECONNABORTED:		/* hardware क्रमced ep reset */
	हाल -ECONNRESET:		/* request dequeued */
	हाल -ESHUTDOWN:		/* disconnect from host */
		VDBG(cdev, "%s gone (%d), %d/%d\n", ep->name, status,
				req->actual, req->length);
		अगर (ep == ss->out_ep)
			check_पढ़ो_data(ss, req);
		मुक्त_ep_req(ep, req);
		वापस;

	हाल -EOVERFLOW:		/* buffer overrun on पढ़ो means that
					 * we didn't provide a big enough
					 * buffer.
					 */
	शेष:
#अगर 1
		DBG(cdev, "%s complete --> %d, %d/%d\n", ep->name,
				status, req->actual, req->length);
		अवरोध;
#पूर्ण_अगर
	हाल -EREMOTEIO:		/* लघु पढ़ो */
		अवरोध;
	पूर्ण

	status = usb_ep_queue(ep, req, GFP_ATOMIC);
	अगर (status) अणु
		ERROR(cdev, "kill %s:  resubmit %d bytes --> %d\n",
				ep->name, req->length, status);
		usb_ep_set_halt(ep);
		/* FIXME recover later ... somehow */
	पूर्ण
पूर्ण

अटल पूर्णांक source_sink_start_ep(काष्ठा f_sourcesink *ss, bool is_in,
		bool is_iso, पूर्णांक speed)
अणु
	काष्ठा usb_ep		*ep;
	काष्ठा usb_request	*req;
	पूर्णांक			i, size, qlen, status = 0;

	अगर (is_iso) अणु
		चयन (speed) अणु
		हाल USB_SPEED_SUPER:
			size = ss->isoc_maxpacket *
					(ss->isoc_mult + 1) *
					(ss->isoc_maxburst + 1);
			अवरोध;
		हाल USB_SPEED_HIGH:
			size = ss->isoc_maxpacket * (ss->isoc_mult + 1);
			अवरोध;
		शेष:
			size = ss->isoc_maxpacket > 1023 ?
					1023 : ss->isoc_maxpacket;
			अवरोध;
		पूर्ण
		ep = is_in ? ss->iso_in_ep : ss->iso_out_ep;
		qlen = ss->iso_qlen;
	पूर्ण अन्यथा अणु
		ep = is_in ? ss->in_ep : ss->out_ep;
		qlen = ss->bulk_qlen;
		size = ss->buflen;
	पूर्ण

	क्रम (i = 0; i < qlen; i++) अणु
		req = ss_alloc_ep_req(ep, size);
		अगर (!req)
			वापस -ENOMEM;

		req->complete = source_sink_complete;
		अगर (is_in)
			reinit_ग_लिखो_data(ep, req);
		अन्यथा अगर (ss->pattern != 2)
			स_रखो(req->buf, 0x55, req->length);

		status = usb_ep_queue(ep, req, GFP_ATOMIC);
		अगर (status) अणु
			काष्ठा usb_composite_dev	*cdev;

			cdev = ss->function.config->cdev;
			ERROR(cdev, "start %s%s %s --> %d\n",
			      is_iso ? "ISO-" : "", is_in ? "IN" : "OUT",
			      ep->name, status);
			मुक्त_ep_req(ep, req);
			वापस status;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम disable_source_sink(काष्ठा f_sourcesink *ss)
अणु
	काष्ठा usb_composite_dev	*cdev;

	cdev = ss->function.config->cdev;
	disable_endpoपूर्णांकs(cdev, ss->in_ep, ss->out_ep, ss->iso_in_ep,
			ss->iso_out_ep);
	VDBG(cdev, "%s disabled\n", ss->function.name);
पूर्ण

अटल पूर्णांक
enable_source_sink(काष्ठा usb_composite_dev *cdev, काष्ठा f_sourcesink *ss,
		पूर्णांक alt)
अणु
	पूर्णांक					result = 0;
	पूर्णांक					speed = cdev->gadget->speed;
	काष्ठा usb_ep				*ep;

	/* one bulk endpoपूर्णांक ग_लिखोs (sources) zeroes IN (to the host) */
	ep = ss->in_ep;
	result = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
	अगर (result)
		वापस result;
	result = usb_ep_enable(ep);
	अगर (result < 0)
		वापस result;
	ep->driver_data = ss;

	result = source_sink_start_ep(ss, true, false, speed);
	अगर (result < 0) अणु
fail:
		ep = ss->in_ep;
		usb_ep_disable(ep);
		वापस result;
	पूर्ण

	/* one bulk endpoपूर्णांक पढ़ोs (sinks) anything OUT (from the host) */
	ep = ss->out_ep;
	result = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
	अगर (result)
		जाओ fail;
	result = usb_ep_enable(ep);
	अगर (result < 0)
		जाओ fail;
	ep->driver_data = ss;

	result = source_sink_start_ep(ss, false, false, speed);
	अगर (result < 0) अणु
fail2:
		ep = ss->out_ep;
		usb_ep_disable(ep);
		जाओ fail;
	पूर्ण

	अगर (alt == 0)
		जाओ out;

	/* one iso endpoपूर्णांक ग_लिखोs (sources) zeroes IN (to the host) */
	ep = ss->iso_in_ep;
	अगर (ep) अणु
		result = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
		अगर (result)
			जाओ fail2;
		result = usb_ep_enable(ep);
		अगर (result < 0)
			जाओ fail2;
		ep->driver_data = ss;

		result = source_sink_start_ep(ss, true, true, speed);
		अगर (result < 0) अणु
fail3:
			ep = ss->iso_in_ep;
			अगर (ep)
				usb_ep_disable(ep);
			जाओ fail2;
		पूर्ण
	पूर्ण

	/* one iso endpoपूर्णांक पढ़ोs (sinks) anything OUT (from the host) */
	ep = ss->iso_out_ep;
	अगर (ep) अणु
		result = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
		अगर (result)
			जाओ fail3;
		result = usb_ep_enable(ep);
		अगर (result < 0)
			जाओ fail3;
		ep->driver_data = ss;

		result = source_sink_start_ep(ss, false, true, speed);
		अगर (result < 0) अणु
			usb_ep_disable(ep);
			जाओ fail3;
		पूर्ण
	पूर्ण
out:
	ss->cur_alt = alt;

	DBG(cdev, "%s enabled, alt intf %d\n", ss->function.name, alt);
	वापस result;
पूर्ण

अटल पूर्णांक sourcesink_set_alt(काष्ठा usb_function *f,
		अचिन्हित पूर्णांकf, अचिन्हित alt)
अणु
	काष्ठा f_sourcesink		*ss = func_to_ss(f);
	काष्ठा usb_composite_dev	*cdev = f->config->cdev;

	disable_source_sink(ss);
	वापस enable_source_sink(cdev, ss, alt);
पूर्ण

अटल पूर्णांक sourcesink_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकf)
अणु
	काष्ठा f_sourcesink		*ss = func_to_ss(f);

	वापस ss->cur_alt;
पूर्ण

अटल व्योम sourcesink_disable(काष्ठा usb_function *f)
अणु
	काष्ठा f_sourcesink	*ss = func_to_ss(f);

	disable_source_sink(ss);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक sourcesink_setup(काष्ठा usb_function *f,
		स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा usb_configuration        *c = f->config;
	काष्ठा usb_request	*req = c->cdev->req;
	पूर्णांक			value = -EOPNOTSUPP;
	u16			w_index = le16_to_cpu(ctrl->wIndex);
	u16			w_value = le16_to_cpu(ctrl->wValue);
	u16			w_length = le16_to_cpu(ctrl->wLength);

	req->length = USB_COMP_EP0_बफ_मान;

	/* composite driver infraकाष्ठाure handles everything except
	 * the two control test requests.
	 */
	चयन (ctrl->bRequest) अणु

	/*
	 * These are the same venकरोr-specअगरic requests supported by
	 * Intel's USB 2.0 compliance test devices.  We exceed that
	 * device spec by allowing multiple-packet requests.
	 *
	 * NOTE:  the Control-OUT data stays in req->buf ... better
	 * would be copying it पूर्णांकo a scratch buffer, so that other
	 * requests may safely पूर्णांकervene.
	 */
	हाल 0x5b:	/* control WRITE test -- fill the buffer */
		अगर (ctrl->bRequestType != (USB_सूची_OUT|USB_TYPE_VENDOR))
			जाओ unknown;
		अगर (w_value || w_index)
			अवरोध;
		/* just पढ़ो that many bytes पूर्णांकo the buffer */
		अगर (w_length > req->length)
			अवरोध;
		value = w_length;
		अवरोध;
	हाल 0x5c:	/* control READ test -- वापस the buffer */
		अगर (ctrl->bRequestType != (USB_सूची_IN|USB_TYPE_VENDOR))
			जाओ unknown;
		अगर (w_value || w_index)
			अवरोध;
		/* expect those bytes are still in the buffer; send back */
		अगर (w_length > req->length)
			अवरोध;
		value = w_length;
		अवरोध;

	शेष:
unknown:
		VDBG(c->cdev,
			"unknown control req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
	पूर्ण

	/* respond with data transfer or status phase? */
	अगर (value >= 0) अणु
		VDBG(c->cdev, "source/sink req%02x.%02x v%04x i%04x l%d\n",
			ctrl->bRequestType, ctrl->bRequest,
			w_value, w_index, w_length);
		req->zero = 0;
		req->length = value;
		value = usb_ep_queue(c->cdev->gadget->ep0, req, GFP_ATOMIC);
		अगर (value < 0)
			ERROR(c->cdev, "source/sink response, err %d\n",
					value);
	पूर्ण

	/* device either stalls (value < 0) or reports success */
	वापस value;
पूर्ण

अटल काष्ठा usb_function *source_sink_alloc_func(
		काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_sourcesink     *ss;
	काष्ठा f_ss_opts	*ss_opts;

	ss = kzalloc(माप(*ss), GFP_KERNEL);
	अगर (!ss)
		वापस ERR_PTR(-ENOMEM);

	ss_opts =  container_of(fi, काष्ठा f_ss_opts, func_inst);

	mutex_lock(&ss_opts->lock);
	ss_opts->refcnt++;
	mutex_unlock(&ss_opts->lock);

	ss->pattern = ss_opts->pattern;
	ss->isoc_पूर्णांकerval = ss_opts->isoc_पूर्णांकerval;
	ss->isoc_maxpacket = ss_opts->isoc_maxpacket;
	ss->isoc_mult = ss_opts->isoc_mult;
	ss->isoc_maxburst = ss_opts->isoc_maxburst;
	ss->buflen = ss_opts->bulk_buflen;
	ss->bulk_qlen = ss_opts->bulk_qlen;
	ss->iso_qlen = ss_opts->iso_qlen;

	ss->function.name = "source/sink";
	ss->function.bind = sourcesink_bind;
	ss->function.set_alt = sourcesink_set_alt;
	ss->function.get_alt = sourcesink_get_alt;
	ss->function.disable = sourcesink_disable;
	ss->function.setup = sourcesink_setup;
	ss->function.strings = sourcesink_strings;

	ss->function.मुक्त_func = sourcesink_मुक्त_func;

	वापस &ss->function;
पूर्ण

अटल अंतरभूत काष्ठा f_ss_opts *to_f_ss_opts(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा f_ss_opts,
			    func_inst.group);
पूर्ण

अटल व्योम ss_attr_release(काष्ठा config_item *item)
अणु
	काष्ठा f_ss_opts *ss_opts = to_f_ss_opts(item);

	usb_put_function_instance(&ss_opts->func_inst);
पूर्ण

अटल काष्ठा configfs_item_operations ss_item_ops = अणु
	.release		= ss_attr_release,
पूर्ण;

अटल sमाप_प्रकार f_ss_opts_pattern_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", opts->pattern);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_ss_opts_pattern_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक ret;
	u8 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou8(page, 0, &num);
	अगर (ret)
		जाओ end;

	अगर (num != 0 && num != 1 && num != 2) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	opts->pattern = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_ss_opts_, pattern);

अटल sमाप_प्रकार f_ss_opts_isoc_पूर्णांकerval_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", opts->isoc_पूर्णांकerval);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_ss_opts_isoc_पूर्णांकerval_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक ret;
	u8 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou8(page, 0, &num);
	अगर (ret)
		जाओ end;

	अगर (num > 16) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	opts->isoc_पूर्णांकerval = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_ss_opts_, isoc_पूर्णांकerval);

अटल sमाप_प्रकार f_ss_opts_isoc_maxpacket_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", opts->isoc_maxpacket);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_ss_opts_isoc_maxpacket_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक ret;
	u16 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou16(page, 0, &num);
	अगर (ret)
		जाओ end;

	अगर (num > 1024) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	opts->isoc_maxpacket = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_ss_opts_, isoc_maxpacket);

अटल sमाप_प्रकार f_ss_opts_isoc_mult_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", opts->isoc_mult);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_ss_opts_isoc_mult_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक ret;
	u8 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou8(page, 0, &num);
	अगर (ret)
		जाओ end;

	अगर (num > 2) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	opts->isoc_mult = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_ss_opts_, isoc_mult);

अटल sमाप_प्रकार f_ss_opts_isoc_maxburst_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", opts->isoc_maxburst);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_ss_opts_isoc_maxburst_store(काष्ठा config_item *item,
				       स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक ret;
	u8 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou8(page, 0, &num);
	अगर (ret)
		जाओ end;

	अगर (num > 15) अणु
		ret = -EINVAL;
		जाओ end;
	पूर्ण

	opts->isoc_maxburst = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_ss_opts_, isoc_maxburst);

अटल sमाप_प्रकार f_ss_opts_bulk_buflen_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", opts->bulk_buflen);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_ss_opts_bulk_buflen_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक ret;
	u32 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou32(page, 0, &num);
	अगर (ret)
		जाओ end;

	opts->bulk_buflen = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_ss_opts_, bulk_buflen);

अटल sमाप_प्रकार f_ss_opts_bulk_qlen_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", opts->bulk_qlen);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_ss_opts_bulk_qlen_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक ret;
	u32 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou32(page, 0, &num);
	अगर (ret)
		जाओ end;

	opts->bulk_qlen = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_ss_opts_, bulk_qlen);

अटल sमाप_प्रकार f_ss_opts_iso_qlen_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक result;

	mutex_lock(&opts->lock);
	result = प्र_लिखो(page, "%u\n", opts->iso_qlen);
	mutex_unlock(&opts->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार f_ss_opts_iso_qlen_store(काष्ठा config_item *item,
					   स्थिर अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा f_ss_opts *opts = to_f_ss_opts(item);
	पूर्णांक ret;
	u32 num;

	mutex_lock(&opts->lock);
	अगर (opts->refcnt) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	ret = kstrtou32(page, 0, &num);
	अगर (ret)
		जाओ end;

	opts->iso_qlen = num;
	ret = len;
end:
	mutex_unlock(&opts->lock);
	वापस ret;
पूर्ण

CONFIGFS_ATTR(f_ss_opts_, iso_qlen);

अटल काष्ठा configfs_attribute *ss_attrs[] = अणु
	&f_ss_opts_attr_pattern,
	&f_ss_opts_attr_isoc_पूर्णांकerval,
	&f_ss_opts_attr_isoc_maxpacket,
	&f_ss_opts_attr_isoc_mult,
	&f_ss_opts_attr_isoc_maxburst,
	&f_ss_opts_attr_bulk_buflen,
	&f_ss_opts_attr_bulk_qlen,
	&f_ss_opts_attr_iso_qlen,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा config_item_type ss_func_type = अणु
	.ct_item_ops    = &ss_item_ops,
	.ct_attrs	= ss_attrs,
	.ct_owner       = THIS_MODULE,
पूर्ण;

अटल व्योम source_sink_मुक्त_instance(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा f_ss_opts *ss_opts;

	ss_opts = container_of(fi, काष्ठा f_ss_opts, func_inst);
	kमुक्त(ss_opts);
पूर्ण

अटल काष्ठा usb_function_instance *source_sink_alloc_inst(व्योम)
अणु
	काष्ठा f_ss_opts *ss_opts;

	ss_opts = kzalloc(माप(*ss_opts), GFP_KERNEL);
	अगर (!ss_opts)
		वापस ERR_PTR(-ENOMEM);
	mutex_init(&ss_opts->lock);
	ss_opts->func_inst.मुक्त_func_inst = source_sink_मुक्त_instance;
	ss_opts->isoc_पूर्णांकerval = GZERO_ISOC_INTERVAL;
	ss_opts->isoc_maxpacket = GZERO_ISOC_MAXPACKET;
	ss_opts->bulk_buflen = GZERO_BULK_BUFLEN;
	ss_opts->bulk_qlen = GZERO_SS_BULK_QLEN;
	ss_opts->iso_qlen = GZERO_SS_ISO_QLEN;

	config_group_init_type_name(&ss_opts->func_inst.group, "",
				    &ss_func_type);

	वापस &ss_opts->func_inst;
पूर्ण
DECLARE_USB_FUNCTION(SourceSink, source_sink_alloc_inst,
		source_sink_alloc_func);

अटल पूर्णांक __init sslb_modinit(व्योम)
अणु
	पूर्णांक ret;

	ret = usb_function_रेजिस्टर(&SourceSinkusb_func);
	अगर (ret)
		वापस ret;
	ret = lb_modinit();
	अगर (ret)
		usb_function_unरेजिस्टर(&SourceSinkusb_func);
	वापस ret;
पूर्ण
अटल व्योम __निकास sslb_modनिकास(व्योम)
अणु
	usb_function_unरेजिस्टर(&SourceSinkusb_func);
	lb_modनिकास();
पूर्ण
module_init(sslb_modinit);
module_निकास(sslb_modनिकास);

MODULE_LICENSE("GPL");
