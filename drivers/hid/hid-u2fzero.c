<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * U2F Zero LED and RNG driver
 *
 * Copyright 2018 Andrej Shadura <andrew@shadura.me>
 * Loosely based on drivers/hid/hid-led.c
 *              and drivers/usb/misc/chaoskey.c
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 */

#समावेश <linux/hid.h>
#समावेश <linux/hidraw.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb.h>

#समावेश "usbhid/usbhid.h"
#समावेश "hid-ids.h"

#घोषणा DRIVER_SHORT		"u2fzero"

#घोषणा HID_REPORT_SIZE		64

/* We only use broadcast (CID-less) messages */
#घोषणा CID_BROADCAST		0xffffffff

काष्ठा u2f_hid_msg अणु
	u32 cid;
	जोड़ अणु
		काष्ठा अणु
			u8 cmd;
			u8 bcnth;
			u8 bcntl;
			u8 data[HID_REPORT_SIZE - 7];
		पूर्ण init;
		काष्ठा अणु
			u8 seq;
			u8 data[HID_REPORT_SIZE - 5];
		पूर्ण cont;
	पूर्ण;
पूर्ण __packed;

काष्ठा u2f_hid_report अणु
	u8 report_type;
	काष्ठा u2f_hid_msg msg;
पूर्ण __packed;

#घोषणा U2F_HID_MSG_LEN(f)	(माप_प्रकार)(((f).init.bcnth << 8) + (f).init.bcntl)

/* Custom extensions to the U2FHID protocol */
#घोषणा U2F_CUSTOM_GET_RNG	0x21
#घोषणा U2F_CUSTOM_WINK		0x24

काष्ठा u2fzero_device अणु
	काष्ठा hid_device	*hdev;
	काष्ठा urb		*urb;	    /* URB क्रम the RNG data */
	काष्ठा led_classdev	ldev;	    /* Embedded काष्ठा क्रम led */
	काष्ठा hwrng		hwrng;	    /* Embedded काष्ठा क्रम hwrng */
	अक्षर			*led_name;
	अक्षर			*rng_name;
	u8			*buf_out;
	u8			*buf_in;
	काष्ठा mutex		lock;
	bool			present;
पूर्ण;

अटल पूर्णांक u2fzero_send(काष्ठा u2fzero_device *dev, काष्ठा u2f_hid_report *req)
अणु
	पूर्णांक ret;

	mutex_lock(&dev->lock);

	स_नकल(dev->buf_out, req, माप(काष्ठा u2f_hid_report));

	ret = hid_hw_output_report(dev->hdev, dev->buf_out,
				   माप(काष्ठा u2f_hid_msg));

	mutex_unlock(&dev->lock);

	अगर (ret < 0)
		वापस ret;

	वापस ret == माप(काष्ठा u2f_hid_msg) ? 0 : -EMSGSIZE;
पूर्ण

काष्ठा u2fzero_transfer_context अणु
	काष्ठा completion करोne;
	पूर्णांक status;
पूर्ण;

अटल व्योम u2fzero_पढ़ो_callback(काष्ठा urb *urb)
अणु
	काष्ठा u2fzero_transfer_context *ctx = urb->context;

	ctx->status = urb->status;
	complete(&ctx->करोne);
पूर्ण

अटल पूर्णांक u2fzero_recv(काष्ठा u2fzero_device *dev,
			काष्ठा u2f_hid_report *req,
			काष्ठा u2f_hid_msg *resp)
अणु
	पूर्णांक ret;
	काष्ठा hid_device *hdev = dev->hdev;
	काष्ठा u2fzero_transfer_context ctx;

	mutex_lock(&dev->lock);

	स_नकल(dev->buf_out, req, माप(काष्ठा u2f_hid_report));

	dev->urb->context = &ctx;
	init_completion(&ctx.करोne);

	ret = usb_submit_urb(dev->urb, GFP_NOIO);
	अगर (unlikely(ret)) अणु
		hid_err(hdev, "usb_submit_urb failed: %d", ret);
		जाओ err;
	पूर्ण

	ret = hid_hw_output_report(dev->hdev, dev->buf_out,
				   माप(काष्ठा u2f_hid_msg));

	अगर (ret < 0) अणु
		hid_err(hdev, "hid_hw_output_report failed: %d", ret);
		जाओ err;
	पूर्ण

	ret = (रुको_क्रम_completion_समयout(
		&ctx.करोne, msecs_to_jअगरfies(USB_CTRL_SET_TIMEOUT)));
	अगर (ret < 0) अणु
		usb_समाप्त_urb(dev->urb);
		hid_err(hdev, "urb submission timed out");
	पूर्ण अन्यथा अणु
		ret = dev->urb->actual_length;
		स_नकल(resp, dev->buf_in, ret);
	पूर्ण

err:
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक u2fzero_blink(काष्ठा led_classdev *ldev)
अणु
	काष्ठा u2fzero_device *dev = container_of(ldev,
		काष्ठा u2fzero_device, ldev);
	काष्ठा u2f_hid_report req = अणु
		.report_type = 0,
		.msg.cid = CID_BROADCAST,
		.msg.init = अणु
			.cmd = U2F_CUSTOM_WINK,
			.bcnth = 0,
			.bcntl = 0,
			.data  = अणु0पूर्ण,
		पूर्ण
	पूर्ण;
	वापस u2fzero_send(dev, &req);
पूर्ण

अटल पूर्णांक u2fzero_brightness_set(काष्ठा led_classdev *ldev,
				  क्रमागत led_brightness brightness)
अणु
	ldev->brightness = LED_OFF;
	अगर (brightness)
		वापस u2fzero_blink(ldev);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक u2fzero_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data,
			    माप_प्रकार max, bool रुको)
अणु
	काष्ठा u2fzero_device *dev = container_of(rng,
		काष्ठा u2fzero_device, hwrng);
	काष्ठा u2f_hid_report req = अणु
		.report_type = 0,
		.msg.cid = CID_BROADCAST,
		.msg.init = अणु
			.cmd = U2F_CUSTOM_GET_RNG,
			.bcnth = 0,
			.bcntl = 0,
			.data  = अणु0पूर्ण,
		पूर्ण
	पूर्ण;
	काष्ठा u2f_hid_msg resp;
	पूर्णांक ret;
	माप_प्रकार actual_length;

	अगर (!dev->present) अणु
		hid_dbg(dev->hdev, "device not present");
		वापस 0;
	पूर्ण

	ret = u2fzero_recv(dev, &req, &resp);
	अगर (ret < 0)
		वापस 0;

	/* only take the minimum amount of data it is safe to take */
	actual_length = min3((माप_प्रकार)ret - दुरत्व(काष्ठा u2f_hid_msg,
		init.data), U2F_HID_MSG_LEN(resp), max);

	स_नकल(data, resp.init.data, actual_length);

	वापस actual_length;
पूर्ण

अटल पूर्णांक u2fzero_init_led(काष्ठा u2fzero_device *dev,
			    अचिन्हित पूर्णांक minor)
अणु
	dev->led_name = devm_kaप्र_लिखो(&dev->hdev->dev, GFP_KERNEL,
		"%s%u", DRIVER_SHORT, minor);
	अगर (dev->led_name == शून्य)
		वापस -ENOMEM;

	dev->ldev.name = dev->led_name;
	dev->ldev.max_brightness = LED_ON;
	dev->ldev.flags = LED_HW_PLUGGABLE;
	dev->ldev.brightness_set_blocking = u2fzero_brightness_set;

	वापस devm_led_classdev_रेजिस्टर(&dev->hdev->dev, &dev->ldev);
पूर्ण

अटल पूर्णांक u2fzero_init_hwrng(काष्ठा u2fzero_device *dev,
			      अचिन्हित पूर्णांक minor)
अणु
	dev->rng_name = devm_kaप्र_लिखो(&dev->hdev->dev, GFP_KERNEL,
		"%s-rng%u", DRIVER_SHORT, minor);
	अगर (dev->rng_name == शून्य)
		वापस -ENOMEM;

	dev->hwrng.name = dev->rng_name;
	dev->hwrng.पढ़ो = u2fzero_rng_पढ़ो;
	dev->hwrng.quality = 1;

	वापस devm_hwrng_रेजिस्टर(&dev->hdev->dev, &dev->hwrng);
पूर्ण

अटल पूर्णांक u2fzero_fill_in_urb(काष्ठा u2fzero_device *dev)
अणु
	काष्ठा hid_device *hdev = dev->hdev;
	काष्ठा usb_device *udev;
	काष्ठा usbhid_device *usbhid = hdev->driver_data;
	अचिन्हित पूर्णांक pipe_in;
	काष्ठा usb_host_endpoपूर्णांक *ep;

	अगर (dev->hdev->bus != BUS_USB)
		वापस -EINVAL;

	udev = hid_to_usb_dev(hdev);

	अगर (!usbhid->urbout || !usbhid->urbin)
		वापस -ENODEV;

	ep = usb_pipe_endpoपूर्णांक(udev, usbhid->urbin->pipe);
	अगर (!ep)
		वापस -ENODEV;

	dev->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->urb)
		वापस -ENOMEM;

	pipe_in = (usbhid->urbin->pipe & ~(3 << 30)) | (PIPE_INTERRUPT << 30);

	usb_fill_पूर्णांक_urb(dev->urb,
		udev,
		pipe_in,
		dev->buf_in,
		HID_REPORT_SIZE,
		u2fzero_पढ़ो_callback,
		शून्य,
		ep->desc.bInterval);

	वापस 0;
पूर्ण

अटल पूर्णांक u2fzero_probe(काष्ठा hid_device *hdev,
			 स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा u2fzero_device *dev;
	अचिन्हित पूर्णांक minor;
	पूर्णांक ret;

	अगर (!hid_is_using_ll_driver(hdev, &usb_hid_driver))
		वापस -EINVAL;

	dev = devm_kzalloc(&hdev->dev, माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य)
		वापस -ENOMEM;

	dev->buf_out = devm_kदो_स्मृति(&hdev->dev,
		माप(काष्ठा u2f_hid_report), GFP_KERNEL);
	अगर (dev->buf_out == शून्य)
		वापस -ENOMEM;

	dev->buf_in = devm_kदो_स्मृति(&hdev->dev,
		माप(काष्ठा u2f_hid_msg), GFP_KERNEL);
	अगर (dev->buf_in == शून्य)
		वापस -ENOMEM;

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	dev->hdev = hdev;
	hid_set_drvdata(hdev, dev);
	mutex_init(&dev->lock);

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret)
		वापस ret;

	u2fzero_fill_in_urb(dev);

	dev->present = true;

	minor = ((काष्ठा hidraw *) hdev->hidraw)->minor;

	ret = u2fzero_init_led(dev, minor);
	अगर (ret) अणु
		hid_hw_stop(hdev);
		वापस ret;
	पूर्ण

	hid_info(hdev, "U2F Zero LED initialised\n");

	ret = u2fzero_init_hwrng(dev, minor);
	अगर (ret) अणु
		hid_hw_stop(hdev);
		वापस ret;
	पूर्ण

	hid_info(hdev, "U2F Zero RNG initialised\n");

	वापस 0;
पूर्ण

अटल व्योम u2fzero_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा u2fzero_device *dev = hid_get_drvdata(hdev);

	mutex_lock(&dev->lock);
	dev->present = false;
	mutex_unlock(&dev->lock);

	hid_hw_stop(hdev);
	usb_poison_urb(dev->urb);
	usb_मुक्त_urb(dev->urb);
पूर्ण

अटल स्थिर काष्ठा hid_device_id u2fzero_table[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CYGNAL,
	  USB_DEVICE_ID_U2F_ZERO) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, u2fzero_table);

अटल काष्ठा hid_driver u2fzero_driver = अणु
	.name = "hid-" DRIVER_SHORT,
	.probe = u2fzero_probe,
	.हटाओ = u2fzero_हटाओ,
	.id_table = u2fzero_table,
पूर्ण;

module_hid_driver(u2fzero_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrej Shadura <andrew@shadura.me>");
MODULE_DESCRIPTION("U2F Zero LED and RNG driver");
