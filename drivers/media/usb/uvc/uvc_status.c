<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      uvc_status.c  --  USB Video Class driver - Status endpoपूर्णांक
 *
 *      Copyright (C) 2005-2009
 *          Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>

#समावेश "uvcvideo.h"

/* --------------------------------------------------------------------------
 * Input device
 */
#अगर_घोषित CONFIG_USB_VIDEO_CLASS_INPUT_EVDEV
अटल पूर्णांक uvc_input_init(काष्ठा uvc_device *dev)
अणु
	काष्ठा input_dev *input;
	पूर्णांक ret;

	input = input_allocate_device();
	अगर (input == शून्य)
		वापस -ENOMEM;

	usb_make_path(dev->udev, dev->input_phys, माप(dev->input_phys));
	strlcat(dev->input_phys, "/button", माप(dev->input_phys));

	input->name = dev->name;
	input->phys = dev->input_phys;
	usb_to_input_id(dev->udev, &input->id);
	input->dev.parent = &dev->पूर्णांकf->dev;

	__set_bit(EV_KEY, input->evbit);
	__set_bit(KEY_CAMERA, input->keybit);

	अगर ((ret = input_रेजिस्टर_device(input)) < 0)
		जाओ error;

	dev->input = input;
	वापस 0;

error:
	input_मुक्त_device(input);
	वापस ret;
पूर्ण

अटल व्योम uvc_input_unरेजिस्टर(काष्ठा uvc_device *dev)
अणु
	अगर (dev->input)
		input_unरेजिस्टर_device(dev->input);
पूर्ण

अटल व्योम uvc_input_report_key(काष्ठा uvc_device *dev, अचिन्हित पूर्णांक code,
	पूर्णांक value)
अणु
	अगर (dev->input) अणु
		input_report_key(dev->input, code, value);
		input_sync(dev->input);
	पूर्ण
पूर्ण

#अन्यथा
#घोषणा uvc_input_init(dev)
#घोषणा uvc_input_unरेजिस्टर(dev)
#घोषणा uvc_input_report_key(dev, code, value)
#पूर्ण_अगर /* CONFIG_USB_VIDEO_CLASS_INPUT_EVDEV */

/* --------------------------------------------------------------------------
 * Status पूर्णांकerrupt endpoपूर्णांक
 */
काष्ठा uvc_streaming_status अणु
	u8	bStatusType;
	u8	bOriginator;
	u8	bEvent;
	u8	bValue[];
पूर्ण __packed;

काष्ठा uvc_control_status अणु
	u8	bStatusType;
	u8	bOriginator;
	u8	bEvent;
	u8	bSelector;
	u8	bAttribute;
	u8	bValue[];
पूर्ण __packed;

अटल व्योम uvc_event_streaming(काष्ठा uvc_device *dev,
				काष्ठा uvc_streaming_status *status, पूर्णांक len)
अणु
	अगर (len < 3) अणु
		uvc_dbg(dev, STATUS,
			"Invalid streaming status event received\n");
		वापस;
	पूर्ण

	अगर (status->bEvent == 0) अणु
		अगर (len < 4)
			वापस;
		uvc_dbg(dev, STATUS, "Button (intf %u) %s len %d\n",
			status->bOriginator,
			status->bValue[0] ? "pressed" : "released", len);
		uvc_input_report_key(dev, KEY_CAMERA, status->bValue[0]);
	पूर्ण अन्यथा अणु
		uvc_dbg(dev, STATUS, "Stream %u error event %02x len %d\n",
			status->bOriginator, status->bEvent, len);
	पूर्ण
पूर्ण

#घोषणा UVC_CTRL_VALUE_CHANGE	0
#घोषणा UVC_CTRL_INFO_CHANGE	1
#घोषणा UVC_CTRL_FAILURE_CHANGE	2
#घोषणा UVC_CTRL_MIN_CHANGE	3
#घोषणा UVC_CTRL_MAX_CHANGE	4

अटल काष्ठा uvc_control *uvc_event_entity_find_ctrl(काष्ठा uvc_entity *entity,
						      u8 selector)
अणु
	काष्ठा uvc_control *ctrl;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0, ctrl = entity->controls; i < entity->ncontrols; i++, ctrl++)
		अगर (ctrl->info.selector == selector)
			वापस ctrl;

	वापस शून्य;
पूर्ण

अटल काष्ठा uvc_control *uvc_event_find_ctrl(काष्ठा uvc_device *dev,
					स्थिर काष्ठा uvc_control_status *status,
					काष्ठा uvc_video_chain **chain)
अणु
	list_क्रम_each_entry((*chain), &dev->chains, list) अणु
		काष्ठा uvc_entity *entity;
		काष्ठा uvc_control *ctrl;

		list_क्रम_each_entry(entity, &(*chain)->entities, chain) अणु
			अगर (entity->id != status->bOriginator)
				जारी;

			ctrl = uvc_event_entity_find_ctrl(entity,
							  status->bSelector);
			अगर (ctrl)
				वापस ctrl;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool uvc_event_control(काष्ठा urb *urb,
			      स्थिर काष्ठा uvc_control_status *status, पूर्णांक len)
अणु
	अटल स्थिर अक्षर *attrs[] = अणु "value", "info", "failure", "min", "max" पूर्ण;
	काष्ठा uvc_device *dev = urb->context;
	काष्ठा uvc_video_chain *chain;
	काष्ठा uvc_control *ctrl;

	अगर (len < 6 || status->bEvent != 0 ||
	    status->bAttribute >= ARRAY_SIZE(attrs)) अणु
		uvc_dbg(dev, STATUS, "Invalid control status event received\n");
		वापस false;
	पूर्ण

	uvc_dbg(dev, STATUS, "Control %u/%u %s change len %d\n",
		status->bOriginator, status->bSelector,
		attrs[status->bAttribute], len);

	/* Find the control. */
	ctrl = uvc_event_find_ctrl(dev, status, &chain);
	अगर (!ctrl)
		वापस false;

	चयन (status->bAttribute) अणु
	हाल UVC_CTRL_VALUE_CHANGE:
		वापस uvc_ctrl_status_event_async(urb, chain, ctrl,
						   status->bValue);

	हाल UVC_CTRL_INFO_CHANGE:
	हाल UVC_CTRL_FAILURE_CHANGE:
	हाल UVC_CTRL_MIN_CHANGE:
	हाल UVC_CTRL_MAX_CHANGE:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम uvc_status_complete(काष्ठा urb *urb)
अणु
	काष्ठा uvc_device *dev = urb->context;
	पूर्णांक len, ret;

	चयन (urb->status) अणु
	हाल 0:
		अवरोध;

	हाल -ENOENT:		/* usb_समाप्त_urb() called. */
	हाल -ECONNRESET:	/* usb_unlink_urb() called. */
	हाल -ESHUTDOWN:	/* The endpoपूर्णांक is being disabled. */
	हाल -EPROTO:		/* Device is disconnected (reported by some
				 * host controller). */
		वापस;

	शेष:
		dev_warn(&dev->udev->dev,
			 "Non-zero status (%d) in status completion handler.\n",
			 urb->status);
		वापस;
	पूर्ण

	len = urb->actual_length;
	अगर (len > 0) अणु
		चयन (dev->status[0] & 0x0f) अणु
		हाल UVC_STATUS_TYPE_CONTROL: अणु
			काष्ठा uvc_control_status *status =
				(काष्ठा uvc_control_status *)dev->status;

			अगर (uvc_event_control(urb, status, len))
				/* The URB will be resubmitted in work context. */
				वापस;
			अवरोध;
		पूर्ण

		हाल UVC_STATUS_TYPE_STREAMING: अणु
			काष्ठा uvc_streaming_status *status =
				(काष्ठा uvc_streaming_status *)dev->status;

			uvc_event_streaming(dev, status, len);
			अवरोध;
		पूर्ण

		शेष:
			uvc_dbg(dev, STATUS, "Unknown status event type %u\n",
				dev->status[0]);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Resubmit the URB. */
	urb->पूर्णांकerval = dev->पूर्णांक_ep->desc.bInterval;
	ret = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (ret < 0)
		dev_err(&dev->udev->dev,
			"Failed to resubmit status URB (%d).\n", ret);
पूर्ण

पूर्णांक uvc_status_init(काष्ठा uvc_device *dev)
अणु
	काष्ठा usb_host_endpoपूर्णांक *ep = dev->पूर्णांक_ep;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक पूर्णांकerval;

	अगर (ep == शून्य)
		वापस 0;

	uvc_input_init(dev);

	dev->status = kzalloc(UVC_MAX_STATUS_SIZE, GFP_KERNEL);
	अगर (dev->status == शून्य)
		वापस -ENOMEM;

	dev->पूर्णांक_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (dev->पूर्णांक_urb == शून्य) अणु
		kमुक्त(dev->status);
		वापस -ENOMEM;
	पूर्ण

	pipe = usb_rcvपूर्णांकpipe(dev->udev, ep->desc.bEndpoपूर्णांकAddress);

	/* For high-speed पूर्णांकerrupt endpoपूर्णांकs, the bInterval value is used as
	 * an exponent of two. Some developers क्रमgot about it.
	 */
	पूर्णांकerval = ep->desc.bInterval;
	अगर (पूर्णांकerval > 16 && dev->udev->speed == USB_SPEED_HIGH &&
	    (dev->quirks & UVC_QUIRK_STATUS_INTERVAL))
		पूर्णांकerval = fls(पूर्णांकerval) - 1;

	usb_fill_पूर्णांक_urb(dev->पूर्णांक_urb, dev->udev, pipe,
		dev->status, UVC_MAX_STATUS_SIZE, uvc_status_complete,
		dev, पूर्णांकerval);

	वापस 0;
पूर्ण

व्योम uvc_status_unरेजिस्टर(काष्ठा uvc_device *dev)
अणु
	usb_समाप्त_urb(dev->पूर्णांक_urb);
	uvc_input_unरेजिस्टर(dev);
पूर्ण

व्योम uvc_status_cleanup(काष्ठा uvc_device *dev)
अणु
	usb_मुक्त_urb(dev->पूर्णांक_urb);
	kमुक्त(dev->status);
पूर्ण

पूर्णांक uvc_status_start(काष्ठा uvc_device *dev, gfp_t flags)
अणु
	अगर (dev->पूर्णांक_urb == शून्य)
		वापस 0;

	वापस usb_submit_urb(dev->पूर्णांक_urb, flags);
पूर्ण

व्योम uvc_status_stop(काष्ठा uvc_device *dev)
अणु
	usb_समाप्त_urb(dev->पूर्णांक_urb);
पूर्ण
