<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PlayStation 2 Trance Vibrator driver
 *
 * Copyright (C) 2006 Sam Hocevar <sam@zoy.org>
 */

/* Standard include files */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#घोषणा DRIVER_AUTHOR "Sam Hocevar, sam@zoy.org"
#घोषणा DRIVER_DESC "PlayStation 2 Trance Vibrator driver"

#घोषणा TRANCEVIBRATOR_VENDOR_ID	0x0b49	/* ASCII Corporation */
#घोषणा TRANCEVIBRATOR_PRODUCT_ID	0x064f	/* Trance Vibrator */

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(TRANCEVIBRATOR_VENDOR_ID, TRANCEVIBRATOR_PRODUCT_ID) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE (usb, id_table);

/* Driver-local specअगरic stuff */
काष्ठा trancevibrator अणु
	काष्ठा usb_device *udev;
	अचिन्हित पूर्णांक speed;
पूर्ण;

अटल sमाप_प्रकार speed_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा trancevibrator *tv = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस प्र_लिखो(buf, "%d\n", tv->speed);
पूर्ण

अटल sमाप_प्रकार speed_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा trancevibrator *tv = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक temp, retval, old;

	retval = kstrtoपूर्णांक(buf, 10, &temp);
	अगर (retval)
		वापस retval;
	अगर (temp > 255)
		temp = 255;
	अन्यथा अगर (temp < 0)
		temp = 0;
	old = tv->speed;
	tv->speed = temp;

	dev_dbg(&tv->udev->dev, "speed = %d\n", tv->speed);

	/* Set speed */
	retval = usb_control_msg(tv->udev, usb_sndctrlpipe(tv->udev, 0),
				 0x01, /* venकरोr request: set speed */
				 USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
				 tv->speed, /* speed value */
				 0, शून्य, 0, USB_CTRL_SET_TIMEOUT);
	अगर (retval) अणु
		tv->speed = old;
		dev_dbg(&tv->udev->dev, "retval = %d\n", retval);
		वापस retval;
	पूर्ण
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(speed);

अटल काष्ठा attribute *tv_attrs[] = अणु
	&dev_attr_speed.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(tv);

अटल पूर्णांक tv_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
		    स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा trancevibrator *dev;
	पूर्णांक retval;

	dev = kzalloc(माप(काष्ठा trancevibrator), GFP_KERNEL);
	अगर (!dev) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	dev->udev = usb_get_dev(udev);
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);

	वापस 0;

error:
	kमुक्त(dev);
	वापस retval;
पूर्ण

अटल व्योम tv_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा trancevibrator *dev;

	dev = usb_get_पूर्णांकfdata (पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	usb_put_dev(dev->udev);
	kमुक्त(dev);
पूर्ण

/* USB subप्रणाली object */
अटल काष्ठा usb_driver tv_driver = अणु
	.name =		"trancevibrator",
	.probe =	tv_probe,
	.disconnect =	tv_disconnect,
	.id_table =	id_table,
	.dev_groups =	tv_groups,
पूर्ण;

module_usb_driver(tv_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
