<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Apple Cinema Display driver
 *
 * Copyright (C) 2006  Michael Hanselmann (linux-kernel@hansmi.ch)
 *
 * Thanks to Caskey L. Dickson क्रम his work with acdctl.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/atomic.h>

#घोषणा APPLE_VENDOR_ID		0x05AC

#घोषणा USB_REQ_GET_REPORT	0x01
#घोषणा USB_REQ_SET_REPORT	0x09

#घोषणा ACD_USB_TIMEOUT		250

#घोषणा ACD_USB_EDID		0x0302
#घोषणा ACD_USB_BRIGHTNESS	0x0310

#घोषणा ACD_BTN_NONE		0
#घोषणा ACD_BTN_BRIGHT_UP	3
#घोषणा ACD_BTN_BRIGHT_DOWN	4

#घोषणा ACD_URB_BUFFER_LEN	2
#घोषणा ACD_MSG_BUFFER_LEN	2

#घोषणा APPLEDISPLAY_DEVICE(prod)				\
	.match_flags = USB_DEVICE_ID_MATCH_DEVICE |		\
		       USB_DEVICE_ID_MATCH_INT_CLASS |		\
		       USB_DEVICE_ID_MATCH_INT_PROTOCOL,	\
	.idVenकरोr = APPLE_VENDOR_ID,				\
	.idProduct = (prod),					\
	.bInterfaceClass = USB_CLASS_HID,			\
	.bInterfaceProtocol = 0x00

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id appledisplay_table[] = अणु
	अणु APPLEDISPLAY_DEVICE(0x9218) पूर्ण,
	अणु APPLEDISPLAY_DEVICE(0x9219) पूर्ण,
	अणु APPLEDISPLAY_DEVICE(0x921c) पूर्ण,
	अणु APPLEDISPLAY_DEVICE(0x921d) पूर्ण,
	अणु APPLEDISPLAY_DEVICE(0x9222) पूर्ण,
	अणु APPLEDISPLAY_DEVICE(0x9226) पूर्ण,
	अणु APPLEDISPLAY_DEVICE(0x9236) पूर्ण,

	/* Terminating entry */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, appledisplay_table);

/* Structure to hold all of our device specअगरic stuff */
काष्ठा appledisplay अणु
	काष्ठा usb_device *udev;	/* usb device */
	काष्ठा urb *urb;		/* usb request block */
	काष्ठा backlight_device *bd;	/* backlight device */
	u8 *urbdata;			/* पूर्णांकerrupt URB data buffer */
	u8 *msgdata;			/* control message data buffer */

	काष्ठा delayed_work work;
	पूर्णांक button_pressed;
	काष्ठा mutex sysfslock;		/* concurrent पढ़ो and ग_लिखो */
पूर्ण;

अटल atomic_t count_displays = ATOMIC_INIT(0);

अटल व्योम appledisplay_complete(काष्ठा urb *urb)
अणु
	काष्ठा appledisplay *pdata = urb->context;
	काष्ठा device *dev = &pdata->udev->dev;
	पूर्णांक status = urb->status;
	पूर्णांक retval;

	चयन (status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -EOVERFLOW:
		dev_err(dev,
			"OVERFLOW with data length %d, actual length is %d\n",
			ACD_URB_BUFFER_LEN, pdata->urb->actual_length);
		fallthrough;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* This urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shuttingdown with status: %d\n",
			__func__, status);
		वापस;
	शेष:
		dev_dbg(dev, "%s - nonzero urb status received: %d\n",
			__func__, status);
		जाओ निकास;
	पूर्ण

	चयन(pdata->urbdata[1]) अणु
	हाल ACD_BTN_BRIGHT_UP:
	हाल ACD_BTN_BRIGHT_DOWN:
		pdata->button_pressed = 1;
		schedule_delayed_work(&pdata->work, 0);
		अवरोध;
	हाल ACD_BTN_NONE:
	शेष:
		pdata->button_pressed = 0;
		अवरोध;
	पूर्ण

निकास:
	retval = usb_submit_urb(pdata->urb, GFP_ATOMIC);
	अगर (retval) अणु
		dev_err(dev, "%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
	पूर्ण
पूर्ण

अटल पूर्णांक appledisplay_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा appledisplay *pdata = bl_get_data(bd);
	पूर्णांक retval;

	mutex_lock(&pdata->sysfslock);
	pdata->msgdata[0] = 0x10;
	pdata->msgdata[1] = bd->props.brightness;

	retval = usb_control_msg(
		pdata->udev,
		usb_sndctrlpipe(pdata->udev, 0),
		USB_REQ_SET_REPORT,
		USB_सूची_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		ACD_USB_BRIGHTNESS,
		0,
		pdata->msgdata, 2,
		ACD_USB_TIMEOUT);
	mutex_unlock(&pdata->sysfslock);

	अगर (retval < 0)
		वापस retval;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक appledisplay_bl_get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा appledisplay *pdata = bl_get_data(bd);
	पूर्णांक retval, brightness;

	mutex_lock(&pdata->sysfslock);
	retval = usb_control_msg(
		pdata->udev,
		usb_rcvctrlpipe(pdata->udev, 0),
		USB_REQ_GET_REPORT,
		USB_सूची_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		ACD_USB_BRIGHTNESS,
		0,
		pdata->msgdata, 2,
		ACD_USB_TIMEOUT);
	अगर (retval < 2) अणु
		अगर (retval >= 0)
			retval = -EMSGSIZE;
	पूर्ण अन्यथा अणु
		brightness = pdata->msgdata[1];
	पूर्ण
	mutex_unlock(&pdata->sysfslock);

	अगर (retval < 0)
		वापस retval;
	अन्यथा
		वापस brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops appledisplay_bl_data = अणु
	.get_brightness	= appledisplay_bl_get_brightness,
	.update_status	= appledisplay_bl_update_status,
पूर्ण;

अटल व्योम appledisplay_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा appledisplay *pdata =
		container_of(work, काष्ठा appledisplay, work.work);
	पूर्णांक retval;

	retval = appledisplay_bl_get_brightness(pdata->bd);
	अगर (retval >= 0)
		pdata->bd->props.brightness = retval;

	/* Poll again in about 125ms अगर there's still a button pressed */
	अगर (pdata->button_pressed)
		schedule_delayed_work(&pdata->work, HZ / 8);
पूर्ण

अटल पूर्णांक appledisplay_probe(काष्ठा usb_पूर्णांकerface *अगरace,
	स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा backlight_properties props;
	काष्ठा appledisplay *pdata;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(अगरace);
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक पूर्णांक_in_endpoपूर्णांकAddr = 0;
	पूर्णांक retval, brightness;
	अक्षर bl_name[20];

	/* set up the endpoपूर्णांक inक्रमmation */
	/* use only the first पूर्णांकerrupt-in endpoपूर्णांक */
	retval = usb_find_पूर्णांक_in_endpoपूर्णांक(अगरace->cur_altsetting, &endpoपूर्णांक);
	अगर (retval) अणु
		dev_err(&अगरace->dev, "Could not find int-in endpoint\n");
		वापस retval;
	पूर्ण

	पूर्णांक_in_endpoपूर्णांकAddr = endpoपूर्णांक->bEndpoपूर्णांकAddress;

	/* allocate memory क्रम our device state and initialize it */
	pdata = kzalloc(माप(काष्ठा appledisplay), GFP_KERNEL);
	अगर (!pdata) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	pdata->udev = udev;

	INIT_DELAYED_WORK(&pdata->work, appledisplay_work);
	mutex_init(&pdata->sysfslock);

	/* Allocate buffer क्रम control messages */
	pdata->msgdata = kदो_स्मृति(ACD_MSG_BUFFER_LEN, GFP_KERNEL);
	अगर (!pdata->msgdata) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	/* Allocate पूर्णांकerrupt URB */
	pdata->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pdata->urb) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	/* Allocate buffer क्रम पूर्णांकerrupt data */
	pdata->urbdata = usb_alloc_coherent(pdata->udev, ACD_URB_BUFFER_LEN,
		GFP_KERNEL, &pdata->urb->transfer_dma);
	अगर (!pdata->urbdata) अणु
		retval = -ENOMEM;
		dev_err(&अगरace->dev, "Allocating URB buffer failed\n");
		जाओ error;
	पूर्ण

	/* Configure पूर्णांकerrupt URB */
	usb_fill_पूर्णांक_urb(pdata->urb, udev,
		usb_rcvपूर्णांकpipe(udev, पूर्णांक_in_endpoपूर्णांकAddr),
		pdata->urbdata, ACD_URB_BUFFER_LEN, appledisplay_complete,
		pdata, 1);
	pdata->urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
	अगर (usb_submit_urb(pdata->urb, GFP_KERNEL)) अणु
		retval = -EIO;
		dev_err(&अगरace->dev, "Submitting URB failed\n");
		जाओ error;
	पूर्ण

	/* Register backlight device */
	snम_लिखो(bl_name, माप(bl_name), "appledisplay%d",
		atomic_inc_वापस(&count_displays) - 1);
	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = 0xff;
	pdata->bd = backlight_device_रेजिस्टर(bl_name, शून्य, pdata,
					      &appledisplay_bl_data, &props);
	अगर (IS_ERR(pdata->bd)) अणु
		dev_err(&अगरace->dev, "Backlight registration failed\n");
		retval = PTR_ERR(pdata->bd);
		जाओ error;
	पूर्ण

	/* Try to get brightness */
	brightness = appledisplay_bl_get_brightness(pdata->bd);

	अगर (brightness < 0) अणु
		retval = brightness;
		dev_err(&अगरace->dev,
			"Error while getting initial brightness: %d\n", retval);
		जाओ error;
	पूर्ण

	/* Set brightness in backlight device */
	pdata->bd->props.brightness = brightness;

	/* save our data poपूर्णांकer in the पूर्णांकerface device */
	usb_set_पूर्णांकfdata(अगरace, pdata);

	prपूर्णांकk(KERN_INFO "appledisplay: Apple Cinema Display connected\n");

	वापस 0;

error:
	अगर (pdata) अणु
		अगर (pdata->urb) अणु
			usb_समाप्त_urb(pdata->urb);
			cancel_delayed_work_sync(&pdata->work);
			usb_मुक्त_coherent(pdata->udev, ACD_URB_BUFFER_LEN,
					pdata->urbdata, pdata->urb->transfer_dma);
			usb_मुक्त_urb(pdata->urb);
		पूर्ण
		अगर (!IS_ERR(pdata->bd))
			backlight_device_unरेजिस्टर(pdata->bd);
		kमुक्त(pdata->msgdata);
	पूर्ण
	usb_set_पूर्णांकfdata(अगरace, शून्य);
	kमुक्त(pdata);
	वापस retval;
पूर्ण

अटल व्योम appledisplay_disconnect(काष्ठा usb_पूर्णांकerface *अगरace)
अणु
	काष्ठा appledisplay *pdata = usb_get_पूर्णांकfdata(अगरace);

	अगर (pdata) अणु
		usb_समाप्त_urb(pdata->urb);
		cancel_delayed_work_sync(&pdata->work);
		backlight_device_unरेजिस्टर(pdata->bd);
		usb_मुक्त_coherent(pdata->udev, ACD_URB_BUFFER_LEN,
			pdata->urbdata, pdata->urb->transfer_dma);
		usb_मुक्त_urb(pdata->urb);
		kमुक्त(pdata->msgdata);
		kमुक्त(pdata);
	पूर्ण

	prपूर्णांकk(KERN_INFO "appledisplay: Apple Cinema Display disconnected\n");
पूर्ण

अटल काष्ठा usb_driver appledisplay_driver = अणु
	.name		= "appledisplay",
	.probe		= appledisplay_probe,
	.disconnect	= appledisplay_disconnect,
	.id_table	= appledisplay_table,
पूर्ण;
module_usb_driver(appledisplay_driver);

MODULE_AUTHOR("Michael Hanselmann");
MODULE_DESCRIPTION("Apple Cinema Display driver");
MODULE_LICENSE("GPL");
