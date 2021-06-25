<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	uvc_gadget.c  --  USB Video Class Gadget driver
 *
 *	Copyright (C) 2009-2010
 *	    Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/g_uvc.h>
#समावेश <linux/usb/video.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-event.h>

#समावेश "u_uvc.h"
#समावेश "uvc.h"
#समावेश "uvc_configfs.h"
#समावेश "uvc_v4l2.h"
#समावेश "uvc_video.h"

अचिन्हित पूर्णांक uvc_gadget_trace_param;
module_param_named(trace, uvc_gadget_trace_param, uपूर्णांक, 0644);
MODULE_PARM_DESC(trace, "Trace level bitmask");

/* --------------------------------------------------------------------------
 * Function descriptors
 */

/* string IDs are asचिन्हित dynamically */

#घोषणा UVC_STRING_CONTROL_IDX			0
#घोषणा UVC_STRING_STREAMING_IDX		1

अटल काष्ठा usb_string uvc_en_us_strings[] = अणु
	[UVC_STRING_CONTROL_IDX].s = "UVC Camera",
	[UVC_STRING_STREAMING_IDX].s = "Video Streaming",
	अणु  पूर्ण
पूर्ण;

अटल काष्ठा usb_gadget_strings uvc_stringtab = अणु
	.language = 0x0409,	/* en-us */
	.strings = uvc_en_us_strings,
पूर्ण;

अटल काष्ठा usb_gadget_strings *uvc_function_strings[] = अणु
	&uvc_stringtab,
	शून्य,
पूर्ण;

#घोषणा UVC_INTF_VIDEO_CONTROL			0
#घोषणा UVC_INTF_VIDEO_STREAMING		1

#घोषणा UVC_STATUS_MAX_PACKET_SIZE		16	/* 16 bytes status */

अटल काष्ठा usb_पूर्णांकerface_assoc_descriptor uvc_iad = अणु
	.bLength		= माप(uvc_iad),
	.bDescriptorType	= USB_DT_INTERFACE_ASSOCIATION,
	.bFirstInterface	= 0,
	.bInterfaceCount	= 2,
	.bFunctionClass		= USB_CLASS_VIDEO,
	.bFunctionSubClass	= UVC_SC_VIDEO_INTERFACE_COLLECTION,
	.bFunctionProtocol	= 0x00,
	.iFunction		= 0,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor uvc_control_पूर्णांकf = अणु
	.bLength		= USB_DT_INTERFACE_SIZE,
	.bDescriptorType	= USB_DT_INTERFACE,
	.bInterfaceNumber	= UVC_INTF_VIDEO_CONTROL,
	.bAlternateSetting	= 0,
	.bNumEndpoपूर्णांकs		= 1,
	.bInterfaceClass	= USB_CLASS_VIDEO,
	.bInterfaceSubClass	= UVC_SC_VIDEOCONTROL,
	.bInterfaceProtocol	= 0x00,
	.iInterface		= 0,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uvc_control_ep = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_XFER_INT,
	.wMaxPacketSize		= cpu_to_le16(UVC_STATUS_MAX_PACKET_SIZE),
	.bInterval		= 8,
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor uvc_ss_control_comp = अणु
	.bLength		= माप(uvc_ss_control_comp),
	.bDescriptorType	= USB_DT_SS_ENDPOINT_COMP,
	/* The following 3 values can be tweaked अगर necessary. */
	.bMaxBurst		= 0,
	.bmAttributes		= 0,
	.wBytesPerInterval	= cpu_to_le16(UVC_STATUS_MAX_PACKET_SIZE),
पूर्ण;

अटल काष्ठा uvc_control_endpoपूर्णांक_descriptor uvc_control_cs_ep = अणु
	.bLength		= UVC_DT_CONTROL_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_CS_ENDPOINT,
	.bDescriptorSubType	= UVC_EP_INTERRUPT,
	.wMaxTransferSize	= cpu_to_le16(UVC_STATUS_MAX_PACKET_SIZE),
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor uvc_streaming_पूर्णांकf_alt0 = अणु
	.bLength		= USB_DT_INTERFACE_SIZE,
	.bDescriptorType	= USB_DT_INTERFACE,
	.bInterfaceNumber	= UVC_INTF_VIDEO_STREAMING,
	.bAlternateSetting	= 0,
	.bNumEndpoपूर्णांकs		= 0,
	.bInterfaceClass	= USB_CLASS_VIDEO,
	.bInterfaceSubClass	= UVC_SC_VIDEOSTREAMING,
	.bInterfaceProtocol	= 0x00,
	.iInterface		= 0,
पूर्ण;

अटल काष्ठा usb_पूर्णांकerface_descriptor uvc_streaming_पूर्णांकf_alt1 = अणु
	.bLength		= USB_DT_INTERFACE_SIZE,
	.bDescriptorType	= USB_DT_INTERFACE,
	.bInterfaceNumber	= UVC_INTF_VIDEO_STREAMING,
	.bAlternateSetting	= 1,
	.bNumEndpoपूर्णांकs		= 1,
	.bInterfaceClass	= USB_CLASS_VIDEO,
	.bInterfaceSubClass	= UVC_SC_VIDEOSTREAMING,
	.bInterfaceProtocol	= 0x00,
	.iInterface		= 0,
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uvc_fs_streaming_ep = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFER_ISOC,
	/* The wMaxPacketSize and bInterval values will be initialized from
	 * module parameters.
	 */
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uvc_hs_streaming_ep = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,
	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFER_ISOC,
	/* The wMaxPacketSize and bInterval values will be initialized from
	 * module parameters.
	 */
पूर्ण;

अटल काष्ठा usb_endpoपूर्णांक_descriptor uvc_ss_streaming_ep = अणु
	.bLength		= USB_DT_ENDPOINT_SIZE,
	.bDescriptorType	= USB_DT_ENDPOINT,

	.bEndpoपूर्णांकAddress	= USB_सूची_IN,
	.bmAttributes		= USB_ENDPOINT_SYNC_ASYNC
				| USB_ENDPOINT_XFER_ISOC,
	/* The wMaxPacketSize and bInterval values will be initialized from
	 * module parameters.
	 */
पूर्ण;

अटल काष्ठा usb_ss_ep_comp_descriptor uvc_ss_streaming_comp = अणु
	.bLength		= माप(uvc_ss_streaming_comp),
	.bDescriptorType	= USB_DT_SS_ENDPOINT_COMP,
	/* The bMaxBurst, bmAttributes and wBytesPerInterval values will be
	 * initialized from module parameters.
	 */
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header * स्थिर uvc_fs_streaming[] = अणु
	(काष्ठा usb_descriptor_header *) &uvc_streaming_पूर्णांकf_alt1,
	(काष्ठा usb_descriptor_header *) &uvc_fs_streaming_ep,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header * स्थिर uvc_hs_streaming[] = अणु
	(काष्ठा usb_descriptor_header *) &uvc_streaming_पूर्णांकf_alt1,
	(काष्ठा usb_descriptor_header *) &uvc_hs_streaming_ep,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा usb_descriptor_header * स्थिर uvc_ss_streaming[] = अणु
	(काष्ठा usb_descriptor_header *) &uvc_streaming_पूर्णांकf_alt1,
	(काष्ठा usb_descriptor_header *) &uvc_ss_streaming_ep,
	(काष्ठा usb_descriptor_header *) &uvc_ss_streaming_comp,
	शून्य,
पूर्ण;

/* --------------------------------------------------------------------------
 * Control requests
 */

अटल व्योम
uvc_function_ep0_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	काष्ठा uvc_device *uvc = req->context;
	काष्ठा v4l2_event v4l2_event;
	काष्ठा uvc_event *uvc_event = (व्योम *)&v4l2_event.u.data;

	अगर (uvc->event_setup_out) अणु
		uvc->event_setup_out = 0;

		स_रखो(&v4l2_event, 0, माप(v4l2_event));
		v4l2_event.type = UVC_EVENT_DATA;
		uvc_event->data.length = req->actual;
		स_नकल(&uvc_event->data.data, req->buf, req->actual);
		v4l2_event_queue(&uvc->vdev, &v4l2_event);
	पूर्ण
पूर्ण

अटल पूर्णांक
uvc_function_setup(काष्ठा usb_function *f, स्थिर काष्ठा usb_ctrlrequest *ctrl)
अणु
	काष्ठा uvc_device *uvc = to_uvc(f);
	काष्ठा v4l2_event v4l2_event;
	काष्ठा uvc_event *uvc_event = (व्योम *)&v4l2_event.u.data;

	अगर ((ctrl->bRequestType & USB_TYPE_MASK) != USB_TYPE_CLASS) अणु
		uvcg_info(f, "invalid request type\n");
		वापस -EINVAL;
	पूर्ण

	/* Stall too big requests. */
	अगर (le16_to_cpu(ctrl->wLength) > UVC_MAX_REQUEST_SIZE)
		वापस -EINVAL;

	/* Tell the complete callback to generate an event क्रम the next request
	 * that will be enqueued by UVCIOC_SEND_RESPONSE.
	 */
	uvc->event_setup_out = !(ctrl->bRequestType & USB_सूची_IN);
	uvc->event_length = le16_to_cpu(ctrl->wLength);

	स_रखो(&v4l2_event, 0, माप(v4l2_event));
	v4l2_event.type = UVC_EVENT_SETUP;
	स_नकल(&uvc_event->req, ctrl, माप(uvc_event->req));
	v4l2_event_queue(&uvc->vdev, &v4l2_event);

	वापस 0;
पूर्ण

व्योम uvc_function_setup_जारी(काष्ठा uvc_device *uvc)
अणु
	काष्ठा usb_composite_dev *cdev = uvc->func.config->cdev;

	usb_composite_setup_जारी(cdev);
पूर्ण

अटल पूर्णांक
uvc_function_get_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकerface)
अणु
	काष्ठा uvc_device *uvc = to_uvc(f);

	uvcg_info(f, "%s(%u)\n", __func__, पूर्णांकerface);

	अगर (पूर्णांकerface == uvc->control_पूर्णांकf)
		वापस 0;
	अन्यथा अगर (पूर्णांकerface != uvc->streaming_पूर्णांकf)
		वापस -EINVAL;
	अन्यथा
		वापस uvc->video.ep->enabled ? 1 : 0;
पूर्ण

अटल पूर्णांक
uvc_function_set_alt(काष्ठा usb_function *f, अचिन्हित पूर्णांकerface, अचिन्हित alt)
अणु
	काष्ठा uvc_device *uvc = to_uvc(f);
	काष्ठा usb_composite_dev *cdev = f->config->cdev;
	काष्ठा v4l2_event v4l2_event;
	काष्ठा uvc_event *uvc_event = (व्योम *)&v4l2_event.u.data;
	पूर्णांक ret;

	uvcg_info(f, "%s(%u, %u)\n", __func__, पूर्णांकerface, alt);

	अगर (पूर्णांकerface == uvc->control_पूर्णांकf) अणु
		अगर (alt)
			वापस -EINVAL;

		uvcg_info(f, "reset UVC Control\n");
		usb_ep_disable(uvc->control_ep);

		अगर (!uvc->control_ep->desc)
			अगर (config_ep_by_speed(cdev->gadget, f, uvc->control_ep))
				वापस -EINVAL;

		usb_ep_enable(uvc->control_ep);

		अगर (uvc->state == UVC_STATE_DISCONNECTED) अणु
			स_रखो(&v4l2_event, 0, माप(v4l2_event));
			v4l2_event.type = UVC_EVENT_CONNECT;
			uvc_event->speed = cdev->gadget->speed;
			v4l2_event_queue(&uvc->vdev, &v4l2_event);

			uvc->state = UVC_STATE_CONNECTED;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (पूर्णांकerface != uvc->streaming_पूर्णांकf)
		वापस -EINVAL;

	/* TODO
	अगर (usb_endpoपूर्णांक_xfer_bulk(&uvc->desc.vs_ep))
		वापस alt ? -EINVAL : 0;
	*/

	चयन (alt) अणु
	हाल 0:
		अगर (uvc->state != UVC_STATE_STREAMING)
			वापस 0;

		अगर (uvc->video.ep)
			usb_ep_disable(uvc->video.ep);

		स_रखो(&v4l2_event, 0, माप(v4l2_event));
		v4l2_event.type = UVC_EVENT_STREAMOFF;
		v4l2_event_queue(&uvc->vdev, &v4l2_event);

		uvc->state = UVC_STATE_CONNECTED;
		वापस 0;

	हाल 1:
		अगर (uvc->state != UVC_STATE_CONNECTED)
			वापस 0;

		अगर (!uvc->video.ep)
			वापस -EINVAL;

		uvcg_info(f, "reset UVC\n");
		usb_ep_disable(uvc->video.ep);

		ret = config_ep_by_speed(f->config->cdev->gadget,
				&(uvc->func), uvc->video.ep);
		अगर (ret)
			वापस ret;
		usb_ep_enable(uvc->video.ep);

		स_रखो(&v4l2_event, 0, माप(v4l2_event));
		v4l2_event.type = UVC_EVENT_STREAMON;
		v4l2_event_queue(&uvc->vdev, &v4l2_event);
		वापस USB_GADGET_DELAYED_STATUS;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम
uvc_function_disable(काष्ठा usb_function *f)
अणु
	काष्ठा uvc_device *uvc = to_uvc(f);
	काष्ठा v4l2_event v4l2_event;

	uvcg_info(f, "%s()\n", __func__);

	स_रखो(&v4l2_event, 0, माप(v4l2_event));
	v4l2_event.type = UVC_EVENT_DISCONNECT;
	v4l2_event_queue(&uvc->vdev, &v4l2_event);

	uvc->state = UVC_STATE_DISCONNECTED;

	usb_ep_disable(uvc->video.ep);
	usb_ep_disable(uvc->control_ep);
पूर्ण

/* --------------------------------------------------------------------------
 * Connection / disconnection
 */

व्योम
uvc_function_connect(काष्ठा uvc_device *uvc)
अणु
	पूर्णांक ret;

	अगर ((ret = usb_function_activate(&uvc->func)) < 0)
		uvcg_info(&uvc->func, "UVC connect failed with %d\n", ret);
पूर्ण

व्योम
uvc_function_disconnect(काष्ठा uvc_device *uvc)
अणु
	पूर्णांक ret;

	अगर ((ret = usb_function_deactivate(&uvc->func)) < 0)
		uvcg_info(&uvc->func, "UVC disconnect failed with %d\n", ret);
पूर्ण

/* --------------------------------------------------------------------------
 * USB probe and disconnect
 */

अटल sमाप_प्रकार function_name_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uvc_device *uvc = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", uvc->func.fi->group.cg_item.ci_name);
पूर्ण

अटल DEVICE_ATTR_RO(function_name);

अटल पूर्णांक
uvc_रेजिस्टर_video(काष्ठा uvc_device *uvc)
अणु
	काष्ठा usb_composite_dev *cdev = uvc->func.config->cdev;
	पूर्णांक ret;

	/* TODO reference counting. */
	uvc->vdev.v4l2_dev = &uvc->v4l2_dev;
	uvc->vdev.fops = &uvc_v4l2_fops;
	uvc->vdev.ioctl_ops = &uvc_v4l2_ioctl_ops;
	uvc->vdev.release = video_device_release_empty;
	uvc->vdev.vfl_dir = VFL_सूची_TX;
	uvc->vdev.lock = &uvc->video.mutex;
	uvc->vdev.device_caps = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_STREAMING;
	strlcpy(uvc->vdev.name, cdev->gadget->name, माप(uvc->vdev.name));

	video_set_drvdata(&uvc->vdev, uvc);

	ret = video_रेजिस्टर_device(&uvc->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0)
		वापस ret;

	ret = device_create_file(&uvc->vdev.dev, &dev_attr_function_name);
	अगर (ret < 0) अणु
		video_unरेजिस्टर_device(&uvc->vdev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा UVC_COPY_DESCRIPTOR(mem, dst, desc) \
	करो अणु \
		स_नकल(mem, desc, (desc)->bLength); \
		*(dst)++ = mem; \
		mem += (desc)->bLength; \
	पूर्ण जबतक (0);

#घोषणा UVC_COPY_DESCRIPTORS(mem, dst, src) \
	करो अणु \
		स्थिर काष्ठा usb_descriptor_header * स्थिर *__src; \
		क्रम (__src = src; *__src; ++__src) अणु \
			स_नकल(mem, *__src, (*__src)->bLength); \
			*dst++ = mem; \
			mem += (*__src)->bLength; \
		पूर्ण \
	पूर्ण जबतक (0)

अटल काष्ठा usb_descriptor_header **
uvc_copy_descriptors(काष्ठा uvc_device *uvc, क्रमागत usb_device_speed speed)
अणु
	काष्ठा uvc_input_header_descriptor *uvc_streaming_header;
	काष्ठा uvc_header_descriptor *uvc_control_header;
	स्थिर काष्ठा uvc_descriptor_header * स्थिर *uvc_control_desc;
	स्थिर काष्ठा uvc_descriptor_header * स्थिर *uvc_streaming_cls;
	स्थिर काष्ठा usb_descriptor_header * स्थिर *uvc_streaming_std;
	स्थिर काष्ठा usb_descriptor_header * स्थिर *src;
	काष्ठा usb_descriptor_header **dst;
	काष्ठा usb_descriptor_header **hdr;
	अचिन्हित पूर्णांक control_size;
	अचिन्हित पूर्णांक streaming_size;
	अचिन्हित पूर्णांक n_desc;
	अचिन्हित पूर्णांक bytes;
	व्योम *mem;

	चयन (speed) अणु
	हाल USB_SPEED_SUPER:
		uvc_control_desc = uvc->desc.ss_control;
		uvc_streaming_cls = uvc->desc.ss_streaming;
		uvc_streaming_std = uvc_ss_streaming;
		अवरोध;

	हाल USB_SPEED_HIGH:
		uvc_control_desc = uvc->desc.fs_control;
		uvc_streaming_cls = uvc->desc.hs_streaming;
		uvc_streaming_std = uvc_hs_streaming;
		अवरोध;

	हाल USB_SPEED_FULL:
	शेष:
		uvc_control_desc = uvc->desc.fs_control;
		uvc_streaming_cls = uvc->desc.fs_streaming;
		uvc_streaming_std = uvc_fs_streaming;
		अवरोध;
	पूर्ण

	अगर (!uvc_control_desc || !uvc_streaming_cls)
		वापस ERR_PTR(-ENODEV);

	/* Descriptors layout
	 *
	 * uvc_iad
	 * uvc_control_पूर्णांकf
	 * Class-specअगरic UVC control descriptors
	 * uvc_control_ep
	 * uvc_control_cs_ep
	 * uvc_ss_control_comp (क्रम SS only)
	 * uvc_streaming_पूर्णांकf_alt0
	 * Class-specअगरic UVC streaming descriptors
	 * uvc_अणुfs|hsपूर्ण_streaming
	 */

	/* Count descriptors and compute their size. */
	control_size = 0;
	streaming_size = 0;
	bytes = uvc_iad.bLength + uvc_control_पूर्णांकf.bLength
	      + uvc_control_ep.bLength + uvc_control_cs_ep.bLength
	      + uvc_streaming_पूर्णांकf_alt0.bLength;

	अगर (speed == USB_SPEED_SUPER) अणु
		bytes += uvc_ss_control_comp.bLength;
		n_desc = 6;
	पूर्ण अन्यथा अणु
		n_desc = 5;
	पूर्ण

	क्रम (src = (स्थिर काष्ठा usb_descriptor_header **)uvc_control_desc;
	     *src; ++src) अणु
		control_size += (*src)->bLength;
		bytes += (*src)->bLength;
		n_desc++;
	पूर्ण
	क्रम (src = (स्थिर काष्ठा usb_descriptor_header **)uvc_streaming_cls;
	     *src; ++src) अणु
		streaming_size += (*src)->bLength;
		bytes += (*src)->bLength;
		n_desc++;
	पूर्ण
	क्रम (src = uvc_streaming_std; *src; ++src) अणु
		bytes += (*src)->bLength;
		n_desc++;
	पूर्ण

	mem = kदो_स्मृति((n_desc + 1) * माप(*src) + bytes, GFP_KERNEL);
	अगर (mem == शून्य)
		वापस शून्य;

	hdr = mem;
	dst = mem;
	mem += (n_desc + 1) * माप(*src);

	/* Copy the descriptors. */
	UVC_COPY_DESCRIPTOR(mem, dst, &uvc_iad);
	UVC_COPY_DESCRIPTOR(mem, dst, &uvc_control_पूर्णांकf);

	uvc_control_header = mem;
	UVC_COPY_DESCRIPTORS(mem, dst,
		(स्थिर काष्ठा usb_descriptor_header **)uvc_control_desc);
	uvc_control_header->wTotalLength = cpu_to_le16(control_size);
	uvc_control_header->bInCollection = 1;
	uvc_control_header->baInterfaceNr[0] = uvc->streaming_पूर्णांकf;

	UVC_COPY_DESCRIPTOR(mem, dst, &uvc_control_ep);
	अगर (speed == USB_SPEED_SUPER)
		UVC_COPY_DESCRIPTOR(mem, dst, &uvc_ss_control_comp);

	UVC_COPY_DESCRIPTOR(mem, dst, &uvc_control_cs_ep);
	UVC_COPY_DESCRIPTOR(mem, dst, &uvc_streaming_पूर्णांकf_alt0);

	uvc_streaming_header = mem;
	UVC_COPY_DESCRIPTORS(mem, dst,
		(स्थिर काष्ठा usb_descriptor_header**)uvc_streaming_cls);
	uvc_streaming_header->wTotalLength = cpu_to_le16(streaming_size);
	uvc_streaming_header->bEndpoपूर्णांकAddress = uvc->video.ep->address;

	UVC_COPY_DESCRIPTORS(mem, dst, uvc_streaming_std);

	*dst = शून्य;
	वापस hdr;
पूर्ण

अटल पूर्णांक
uvc_function_bind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा uvc_device *uvc = to_uvc(f);
	काष्ठा usb_string *us;
	अचिन्हित पूर्णांक max_packet_mult;
	अचिन्हित पूर्णांक max_packet_size;
	काष्ठा usb_ep *ep;
	काष्ठा f_uvc_opts *opts;
	पूर्णांक ret = -EINVAL;

	uvcg_info(f, "%s()\n", __func__);

	opts = fi_to_f_uvc_opts(f->fi);
	/* Sanity check the streaming endpoपूर्णांक module parameters.
	 */
	opts->streaming_पूर्णांकerval = clamp(opts->streaming_पूर्णांकerval, 1U, 16U);
	opts->streaming_maxpacket = clamp(opts->streaming_maxpacket, 1U, 3072U);
	opts->streaming_maxburst = min(opts->streaming_maxburst, 15U);

	/* For SS, wMaxPacketSize has to be 1024 अगर bMaxBurst is not 0 */
	अगर (opts->streaming_maxburst &&
	    (opts->streaming_maxpacket % 1024) != 0) अणु
		opts->streaming_maxpacket = roundup(opts->streaming_maxpacket, 1024);
		uvcg_info(f, "overriding streaming_maxpacket to %d\n",
			  opts->streaming_maxpacket);
	पूर्ण

	/* Fill in the FS/HS/SS Video Streaming specअगरic descriptors from the
	 * module parameters.
	 *
	 * NOTE: We assume that the user knows what they are करोing and won't
	 * give parameters that their UDC करोesn't support.
	 */
	अगर (opts->streaming_maxpacket <= 1024) अणु
		max_packet_mult = 1;
		max_packet_size = opts->streaming_maxpacket;
	पूर्ण अन्यथा अगर (opts->streaming_maxpacket <= 2048) अणु
		max_packet_mult = 2;
		max_packet_size = opts->streaming_maxpacket / 2;
	पूर्ण अन्यथा अणु
		max_packet_mult = 3;
		max_packet_size = opts->streaming_maxpacket / 3;
	पूर्ण

	uvc_fs_streaming_ep.wMaxPacketSize =
		cpu_to_le16(min(opts->streaming_maxpacket, 1023U));
	uvc_fs_streaming_ep.bInterval = opts->streaming_पूर्णांकerval;

	uvc_hs_streaming_ep.wMaxPacketSize =
		cpu_to_le16(max_packet_size | ((max_packet_mult - 1) << 11));

	/* A high-bandwidth endpoपूर्णांक must specअगरy a bInterval value of 1 */
	अगर (max_packet_mult > 1)
		uvc_hs_streaming_ep.bInterval = 1;
	अन्यथा
		uvc_hs_streaming_ep.bInterval = opts->streaming_पूर्णांकerval;

	uvc_ss_streaming_ep.wMaxPacketSize = cpu_to_le16(max_packet_size);
	uvc_ss_streaming_ep.bInterval = opts->streaming_पूर्णांकerval;
	uvc_ss_streaming_comp.bmAttributes = max_packet_mult - 1;
	uvc_ss_streaming_comp.bMaxBurst = opts->streaming_maxburst;
	uvc_ss_streaming_comp.wBytesPerInterval =
		cpu_to_le16(max_packet_size * max_packet_mult *
			    (opts->streaming_maxburst + 1));

	/* Allocate endpoपूर्णांकs. */
	ep = usb_ep_स्वतःconfig(cdev->gadget, &uvc_control_ep);
	अगर (!ep) अणु
		uvcg_info(f, "Unable to allocate control EP\n");
		जाओ error;
	पूर्ण
	uvc->control_ep = ep;

	अगर (gadget_is_superspeed(c->cdev->gadget))
		ep = usb_ep_स्वतःconfig_ss(cdev->gadget, &uvc_ss_streaming_ep,
					  &uvc_ss_streaming_comp);
	अन्यथा अगर (gadget_is_dualspeed(cdev->gadget))
		ep = usb_ep_स्वतःconfig(cdev->gadget, &uvc_hs_streaming_ep);
	अन्यथा
		ep = usb_ep_स्वतःconfig(cdev->gadget, &uvc_fs_streaming_ep);

	अगर (!ep) अणु
		uvcg_info(f, "Unable to allocate streaming EP\n");
		जाओ error;
	पूर्ण
	uvc->video.ep = ep;

	uvc_fs_streaming_ep.bEndpoपूर्णांकAddress = uvc->video.ep->address;
	uvc_hs_streaming_ep.bEndpoपूर्णांकAddress = uvc->video.ep->address;
	uvc_ss_streaming_ep.bEndpoपूर्णांकAddress = uvc->video.ep->address;

	us = usb_gstrings_attach(cdev, uvc_function_strings,
				 ARRAY_SIZE(uvc_en_us_strings));
	अगर (IS_ERR(us)) अणु
		ret = PTR_ERR(us);
		जाओ error;
	पूर्ण
	uvc_iad.iFunction = us[UVC_STRING_CONTROL_IDX].id;
	uvc_control_पूर्णांकf.iInterface = us[UVC_STRING_CONTROL_IDX].id;
	ret = us[UVC_STRING_STREAMING_IDX].id;
	uvc_streaming_पूर्णांकf_alt0.iInterface = ret;
	uvc_streaming_पूर्णांकf_alt1.iInterface = ret;

	/* Allocate पूर्णांकerface IDs. */
	अगर ((ret = usb_पूर्णांकerface_id(c, f)) < 0)
		जाओ error;
	uvc_iad.bFirstInterface = ret;
	uvc_control_पूर्णांकf.bInterfaceNumber = ret;
	uvc->control_पूर्णांकf = ret;
	opts->control_पूर्णांकerface = ret;

	अगर ((ret = usb_पूर्णांकerface_id(c, f)) < 0)
		जाओ error;
	uvc_streaming_पूर्णांकf_alt0.bInterfaceNumber = ret;
	uvc_streaming_पूर्णांकf_alt1.bInterfaceNumber = ret;
	uvc->streaming_पूर्णांकf = ret;
	opts->streaming_पूर्णांकerface = ret;

	/* Copy descriptors */
	f->fs_descriptors = uvc_copy_descriptors(uvc, USB_SPEED_FULL);
	अगर (IS_ERR(f->fs_descriptors)) अणु
		ret = PTR_ERR(f->fs_descriptors);
		f->fs_descriptors = शून्य;
		जाओ error;
	पूर्ण
	अगर (gadget_is_dualspeed(cdev->gadget)) अणु
		f->hs_descriptors = uvc_copy_descriptors(uvc, USB_SPEED_HIGH);
		अगर (IS_ERR(f->hs_descriptors)) अणु
			ret = PTR_ERR(f->hs_descriptors);
			f->hs_descriptors = शून्य;
			जाओ error;
		पूर्ण
	पूर्ण
	अगर (gadget_is_superspeed(c->cdev->gadget)) अणु
		f->ss_descriptors = uvc_copy_descriptors(uvc, USB_SPEED_SUPER);
		अगर (IS_ERR(f->ss_descriptors)) अणु
			ret = PTR_ERR(f->ss_descriptors);
			f->ss_descriptors = शून्य;
			जाओ error;
		पूर्ण
	पूर्ण

	/* Pपुनः_स्मृतिate control endpoपूर्णांक request. */
	uvc->control_req = usb_ep_alloc_request(cdev->gadget->ep0, GFP_KERNEL);
	uvc->control_buf = kदो_स्मृति(UVC_MAX_REQUEST_SIZE, GFP_KERNEL);
	अगर (uvc->control_req == शून्य || uvc->control_buf == शून्य) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	uvc->control_req->buf = uvc->control_buf;
	uvc->control_req->complete = uvc_function_ep0_complete;
	uvc->control_req->context = uvc;

	अगर (v4l2_device_रेजिस्टर(&cdev->gadget->dev, &uvc->v4l2_dev)) अणु
		uvcg_err(f, "failed to register V4L2 device\n");
		जाओ error;
	पूर्ण

	/* Initialise video. */
	ret = uvcg_video_init(&uvc->video, uvc);
	अगर (ret < 0)
		जाओ v4l2_error;

	/* Register a V4L2 device. */
	ret = uvc_रेजिस्टर_video(uvc);
	अगर (ret < 0) अणु
		uvcg_err(f, "failed to register video device\n");
		जाओ v4l2_error;
	पूर्ण

	वापस 0;

v4l2_error:
	v4l2_device_unरेजिस्टर(&uvc->v4l2_dev);
error:
	अगर (uvc->control_req)
		usb_ep_मुक्त_request(cdev->gadget->ep0, uvc->control_req);
	kमुक्त(uvc->control_buf);

	usb_मुक्त_all_descriptors(f);
	वापस ret;
पूर्ण

/* --------------------------------------------------------------------------
 * USB gadget function
 */

अटल व्योम uvc_मुक्त_inst(काष्ठा usb_function_instance *f)
अणु
	काष्ठा f_uvc_opts *opts = fi_to_f_uvc_opts(f);

	mutex_destroy(&opts->lock);
	kमुक्त(opts);
पूर्ण

अटल काष्ठा usb_function_instance *uvc_alloc_inst(व्योम)
अणु
	काष्ठा f_uvc_opts *opts;
	काष्ठा uvc_camera_terminal_descriptor *cd;
	काष्ठा uvc_processing_unit_descriptor *pd;
	काष्ठा uvc_output_terminal_descriptor *od;
	काष्ठा uvc_color_matching_descriptor *md;
	काष्ठा uvc_descriptor_header **ctl_cls;
	पूर्णांक ret;

	opts = kzalloc(माप(*opts), GFP_KERNEL);
	अगर (!opts)
		वापस ERR_PTR(-ENOMEM);
	opts->func_inst.मुक्त_func_inst = uvc_मुक्त_inst;
	mutex_init(&opts->lock);

	cd = &opts->uvc_camera_terminal;
	cd->bLength			= UVC_DT_CAMERA_TERMINAL_SIZE(3);
	cd->bDescriptorType		= USB_DT_CS_INTERFACE;
	cd->bDescriptorSubType		= UVC_VC_INPUT_TERMINAL;
	cd->bTerminalID			= 1;
	cd->wTerminalType		= cpu_to_le16(0x0201);
	cd->bAssocTerminal		= 0;
	cd->iTerminal			= 0;
	cd->wObjectiveFocalLengthMin	= cpu_to_le16(0);
	cd->wObjectiveFocalLengthMax	= cpu_to_le16(0);
	cd->wOcularFocalLength		= cpu_to_le16(0);
	cd->bControlSize		= 3;
	cd->bmControls[0]		= 2;
	cd->bmControls[1]		= 0;
	cd->bmControls[2]		= 0;

	pd = &opts->uvc_processing;
	pd->bLength			= UVC_DT_PROCESSING_UNIT_SIZE(2);
	pd->bDescriptorType		= USB_DT_CS_INTERFACE;
	pd->bDescriptorSubType		= UVC_VC_PROCESSING_UNIT;
	pd->bUnitID			= 2;
	pd->bSourceID			= 1;
	pd->wMaxMultiplier		= cpu_to_le16(16*1024);
	pd->bControlSize		= 2;
	pd->bmControls[0]		= 1;
	pd->bmControls[1]		= 0;
	pd->iProcessing			= 0;
	pd->bmVideoStandards		= 0;

	od = &opts->uvc_output_terminal;
	od->bLength			= UVC_DT_OUTPUT_TERMINAL_SIZE;
	od->bDescriptorType		= USB_DT_CS_INTERFACE;
	od->bDescriptorSubType		= UVC_VC_OUTPUT_TERMINAL;
	od->bTerminalID			= 3;
	od->wTerminalType		= cpu_to_le16(0x0101);
	od->bAssocTerminal		= 0;
	od->bSourceID			= 2;
	od->iTerminal			= 0;

	md = &opts->uvc_color_matching;
	md->bLength			= UVC_DT_COLOR_MATCHING_SIZE;
	md->bDescriptorType		= USB_DT_CS_INTERFACE;
	md->bDescriptorSubType		= UVC_VS_COLORFORMAT;
	md->bColorPrimaries		= 1;
	md->bTransferCharacteristics	= 1;
	md->bMatrixCoefficients		= 4;

	/* Prepare fs control class descriptors क्रम configfs-based gadमाला_लो */
	ctl_cls = opts->uvc_fs_control_cls;
	ctl_cls[0] = शून्य;	/* asचिन्हित अन्यथाwhere by configfs */
	ctl_cls[1] = (काष्ठा uvc_descriptor_header *)cd;
	ctl_cls[2] = (काष्ठा uvc_descriptor_header *)pd;
	ctl_cls[3] = (काष्ठा uvc_descriptor_header *)od;
	ctl_cls[4] = शून्य;	/* शून्य-terminate */
	opts->fs_control =
		(स्थिर काष्ठा uvc_descriptor_header * स्थिर *)ctl_cls;

	/* Prepare hs control class descriptors क्रम configfs-based gadमाला_लो */
	ctl_cls = opts->uvc_ss_control_cls;
	ctl_cls[0] = शून्य;	/* asचिन्हित अन्यथाwhere by configfs */
	ctl_cls[1] = (काष्ठा uvc_descriptor_header *)cd;
	ctl_cls[2] = (काष्ठा uvc_descriptor_header *)pd;
	ctl_cls[3] = (काष्ठा uvc_descriptor_header *)od;
	ctl_cls[4] = शून्य;	/* शून्य-terminate */
	opts->ss_control =
		(स्थिर काष्ठा uvc_descriptor_header * स्थिर *)ctl_cls;

	opts->streaming_पूर्णांकerval = 1;
	opts->streaming_maxpacket = 1024;

	ret = uvcg_attach_configfs(opts);
	अगर (ret < 0) अणु
		kमुक्त(opts);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस &opts->func_inst;
पूर्ण

अटल व्योम uvc_मुक्त(काष्ठा usb_function *f)
अणु
	काष्ठा uvc_device *uvc = to_uvc(f);
	काष्ठा f_uvc_opts *opts = container_of(f->fi, काष्ठा f_uvc_opts,
					       func_inst);
	--opts->refcnt;
	kमुक्त(uvc);
पूर्ण

अटल व्योम uvc_unbind(काष्ठा usb_configuration *c, काष्ठा usb_function *f)
अणु
	काष्ठा usb_composite_dev *cdev = c->cdev;
	काष्ठा uvc_device *uvc = to_uvc(f);

	uvcg_info(f, "%s\n", __func__);

	device_हटाओ_file(&uvc->vdev.dev, &dev_attr_function_name);
	video_unरेजिस्टर_device(&uvc->vdev);
	v4l2_device_unरेजिस्टर(&uvc->v4l2_dev);

	usb_ep_मुक्त_request(cdev->gadget->ep0, uvc->control_req);
	kमुक्त(uvc->control_buf);

	usb_मुक्त_all_descriptors(f);
पूर्ण

अटल काष्ठा usb_function *uvc_alloc(काष्ठा usb_function_instance *fi)
अणु
	काष्ठा uvc_device *uvc;
	काष्ठा f_uvc_opts *opts;
	काष्ठा uvc_descriptor_header **strm_cls;

	uvc = kzalloc(माप(*uvc), GFP_KERNEL);
	अगर (uvc == शून्य)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&uvc->video.mutex);
	uvc->state = UVC_STATE_DISCONNECTED;
	opts = fi_to_f_uvc_opts(fi);

	mutex_lock(&opts->lock);
	अगर (opts->uvc_fs_streaming_cls) अणु
		strm_cls = opts->uvc_fs_streaming_cls;
		opts->fs_streaming =
			(स्थिर काष्ठा uvc_descriptor_header * स्थिर *)strm_cls;
	पूर्ण
	अगर (opts->uvc_hs_streaming_cls) अणु
		strm_cls = opts->uvc_hs_streaming_cls;
		opts->hs_streaming =
			(स्थिर काष्ठा uvc_descriptor_header * स्थिर *)strm_cls;
	पूर्ण
	अगर (opts->uvc_ss_streaming_cls) अणु
		strm_cls = opts->uvc_ss_streaming_cls;
		opts->ss_streaming =
			(स्थिर काष्ठा uvc_descriptor_header * स्थिर *)strm_cls;
	पूर्ण

	uvc->desc.fs_control = opts->fs_control;
	uvc->desc.ss_control = opts->ss_control;
	uvc->desc.fs_streaming = opts->fs_streaming;
	uvc->desc.hs_streaming = opts->hs_streaming;
	uvc->desc.ss_streaming = opts->ss_streaming;
	++opts->refcnt;
	mutex_unlock(&opts->lock);

	/* Register the function. */
	uvc->func.name = "uvc";
	uvc->func.bind = uvc_function_bind;
	uvc->func.unbind = uvc_unbind;
	uvc->func.get_alt = uvc_function_get_alt;
	uvc->func.set_alt = uvc_function_set_alt;
	uvc->func.disable = uvc_function_disable;
	uvc->func.setup = uvc_function_setup;
	uvc->func.मुक्त_func = uvc_मुक्त;
	uvc->func.bind_deactivated = true;

	वापस &uvc->func;
पूर्ण

DECLARE_USB_FUNCTION_INIT(uvc, uvc_alloc_inst, uvc_alloc);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Laurent Pinchart");
