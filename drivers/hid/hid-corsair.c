<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HID driver क्रम Corsair devices
 *
 * Supported devices:
 *  - Vengeance K70 Keyboard
 *  - K70 RAPIDFIRE Keyboard
 *  - Vengeance K90 Keyboard
 *  - Scimitar PRO RGB Gaming Mouse
 *
 * Copyright (c) 2015 Clement Vuchener
 * Copyright (c) 2017 Oscar Campos
 * Copyright (c) 2017 Aaron Bottegal
 */

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/leds.h>

#समावेश "hid-ids.h"

#घोषणा CORSAIR_USE_K90_MACRO	(1<<0)
#घोषणा CORSAIR_USE_K90_BACKLIGHT	(1<<1)

काष्ठा k90_led अणु
	काष्ठा led_classdev cdev;
	पूर्णांक brightness;
	काष्ठा work_काष्ठा work;
	bool हटाओd;
पूर्ण;

काष्ठा k90_drvdata अणु
	काष्ठा k90_led record_led;
पूर्ण;

काष्ठा corsair_drvdata अणु
	अचिन्हित दीर्घ quirks;
	काष्ठा k90_drvdata *k90;
	काष्ठा k90_led *backlight;
पूर्ण;

#घोषणा K90_GKEY_COUNT	18

अटल पूर्णांक corsair_usage_to_gkey(अचिन्हित पूर्णांक usage)
अणु
	/* G1 (0xd0) to G16 (0xdf) */
	अगर (usage >= 0xd0 && usage <= 0xdf)
		वापस usage - 0xd0 + 1;
	/* G17 (0xe8) to G18 (0xe9) */
	अगर (usage >= 0xe8 && usage <= 0xe9)
		वापस usage - 0xe8 + 17;
	वापस 0;
पूर्ण

अटल अचिन्हित लघु corsair_gkey_map[K90_GKEY_COUNT] = अणु
	BTN_TRIGGER_HAPPY1,
	BTN_TRIGGER_HAPPY2,
	BTN_TRIGGER_HAPPY3,
	BTN_TRIGGER_HAPPY4,
	BTN_TRIGGER_HAPPY5,
	BTN_TRIGGER_HAPPY6,
	BTN_TRIGGER_HAPPY7,
	BTN_TRIGGER_HAPPY8,
	BTN_TRIGGER_HAPPY9,
	BTN_TRIGGER_HAPPY10,
	BTN_TRIGGER_HAPPY11,
	BTN_TRIGGER_HAPPY12,
	BTN_TRIGGER_HAPPY13,
	BTN_TRIGGER_HAPPY14,
	BTN_TRIGGER_HAPPY15,
	BTN_TRIGGER_HAPPY16,
	BTN_TRIGGER_HAPPY17,
	BTN_TRIGGER_HAPPY18,
पूर्ण;

module_param_array_named(gkey_codes, corsair_gkey_map, uलघु, शून्य, S_IRUGO);
MODULE_PARM_DESC(gkey_codes, "Key codes for the G-keys");

अटल अचिन्हित लघु corsair_record_keycodes[2] = अणु
	BTN_TRIGGER_HAPPY19,
	BTN_TRIGGER_HAPPY20
पूर्ण;

module_param_array_named(recordkey_codes, corsair_record_keycodes, uलघु,
			 शून्य, S_IRUGO);
MODULE_PARM_DESC(recordkey_codes, "Key codes for the MR (start and stop record) button");

अटल अचिन्हित लघु corsair_profile_keycodes[3] = अणु
	BTN_TRIGGER_HAPPY21,
	BTN_TRIGGER_HAPPY22,
	BTN_TRIGGER_HAPPY23
पूर्ण;

module_param_array_named(profilekey_codes, corsair_profile_keycodes, uलघु,
			 शून्य, S_IRUGO);
MODULE_PARM_DESC(profilekey_codes, "Key codes for the profile buttons");

#घोषणा CORSAIR_USAGE_SPECIAL_MIN 0xf0
#घोषणा CORSAIR_USAGE_SPECIAL_MAX 0xff

#घोषणा CORSAIR_USAGE_MACRO_RECORD_START 0xf6
#घोषणा CORSAIR_USAGE_MACRO_RECORD_STOP 0xf7

#घोषणा CORSAIR_USAGE_PROखाता 0xf1
#घोषणा CORSAIR_USAGE_M1 0xf1
#घोषणा CORSAIR_USAGE_M2 0xf2
#घोषणा CORSAIR_USAGE_M3 0xf3
#घोषणा CORSAIR_USAGE_PROखाता_MAX 0xf3

#घोषणा CORSAIR_USAGE_META_OFF 0xf4
#घोषणा CORSAIR_USAGE_META_ON  0xf5

#घोषणा CORSAIR_USAGE_LIGHT 0xfa
#घोषणा CORSAIR_USAGE_LIGHT_OFF 0xfa
#घोषणा CORSAIR_USAGE_LIGHT_DIM 0xfb
#घोषणा CORSAIR_USAGE_LIGHT_MEDIUM 0xfc
#घोषणा CORSAIR_USAGE_LIGHT_BRIGHT 0xfd
#घोषणा CORSAIR_USAGE_LIGHT_MAX 0xfd

/* USB control protocol */

#घोषणा K90_REQUEST_BRIGHTNESS 49
#घोषणा K90_REQUEST_MACRO_MODE 2
#घोषणा K90_REQUEST_STATUS 4
#घोषणा K90_REQUEST_GET_MODE 5
#घोषणा K90_REQUEST_PROखाता 20

#घोषणा K90_MACRO_MODE_SW 0x0030
#घोषणा K90_MACRO_MODE_HW 0x0001

#घोषणा K90_MACRO_LED_ON  0x0020
#घोषणा K90_MACRO_LED_OFF 0x0040

/*
 * LED class devices
 */

#घोषणा K90_BACKLIGHT_LED_SUFFIX "::backlight"
#घोषणा K90_RECORD_LED_SUFFIX "::record"

अटल क्रमागत led_brightness k90_backlight_get(काष्ठा led_classdev *led_cdev)
अणु
	पूर्णांक ret;
	काष्ठा k90_led *led = container_of(led_cdev, काष्ठा k90_led, cdev);
	काष्ठा device *dev = led->cdev.dev->parent;
	काष्ठा usb_पूर्णांकerface *usbअगर = to_usb_पूर्णांकerface(dev->parent);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);
	पूर्णांक brightness;
	अक्षर *data;

	data = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0),
			      K90_REQUEST_STATUS,
			      USB_सूची_IN | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, 0, 0, data, 8,
			      USB_CTRL_SET_TIMEOUT);
	अगर (ret < 5) अणु
		dev_warn(dev, "Failed to get K90 initial state (error %d).\n",
			 ret);
		ret = -EIO;
		जाओ out;
	पूर्ण
	brightness = data[4];
	अगर (brightness < 0 || brightness > 3) अणु
		dev_warn(dev,
			 "Read invalid backlight brightness: %02hhx.\n",
			 data[4]);
		ret = -EIO;
		जाओ out;
	पूर्ण
	ret = brightness;
out:
	kमुक्त(data);

	वापस ret;
पूर्ण

अटल क्रमागत led_brightness k90_record_led_get(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा k90_led *led = container_of(led_cdev, काष्ठा k90_led, cdev);

	वापस led->brightness;
पूर्ण

अटल व्योम k90_brightness_set(काष्ठा led_classdev *led_cdev,
			       क्रमागत led_brightness brightness)
अणु
	काष्ठा k90_led *led = container_of(led_cdev, काष्ठा k90_led, cdev);

	led->brightness = brightness;
	schedule_work(&led->work);
पूर्ण

अटल व्योम k90_backlight_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा k90_led *led = container_of(work, काष्ठा k90_led, work);
	काष्ठा device *dev;
	काष्ठा usb_पूर्णांकerface *usbअगर;
	काष्ठा usb_device *usbdev;

	अगर (led->हटाओd)
		वापस;

	dev = led->cdev.dev->parent;
	usbअगर = to_usb_पूर्णांकerface(dev->parent);
	usbdev = पूर्णांकerface_to_usbdev(usbअगर);

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
			      K90_REQUEST_BRIGHTNESS,
			      USB_सूची_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, led->brightness, 0,
			      शून्य, 0, USB_CTRL_SET_TIMEOUT);
	अगर (ret != 0)
		dev_warn(dev, "Failed to set backlight brightness (error: %d).\n",
			 ret);
पूर्ण

अटल व्योम k90_record_led_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा k90_led *led = container_of(work, काष्ठा k90_led, work);
	काष्ठा device *dev;
	काष्ठा usb_पूर्णांकerface *usbअगर;
	काष्ठा usb_device *usbdev;
	पूर्णांक value;

	अगर (led->हटाओd)
		वापस;

	dev = led->cdev.dev->parent;
	usbअगर = to_usb_पूर्णांकerface(dev->parent);
	usbdev = पूर्णांकerface_to_usbdev(usbअगर);

	अगर (led->brightness > 0)
		value = K90_MACRO_LED_ON;
	अन्यथा
		value = K90_MACRO_LED_OFF;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
			      K90_REQUEST_MACRO_MODE,
			      USB_सूची_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, 0, शून्य, 0,
			      USB_CTRL_SET_TIMEOUT);
	अगर (ret != 0)
		dev_warn(dev, "Failed to set record LED state (error: %d).\n",
			 ret);
पूर्ण

/*
 * Keyboard attributes
 */

अटल sमाप_प्रकार k90_show_macro_mode(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा usb_पूर्णांकerface *usbअगर = to_usb_पूर्णांकerface(dev->parent);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);
	स्थिर अक्षर *macro_mode;
	अक्षर *data;

	data = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0),
			      K90_REQUEST_GET_MODE,
			      USB_सूची_IN | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, 0, 0, data, 2,
			      USB_CTRL_SET_TIMEOUT);
	अगर (ret < 1) अणु
		dev_warn(dev, "Failed to get K90 initial mode (error %d).\n",
			 ret);
		ret = -EIO;
		जाओ out;
	पूर्ण

	चयन (data[0]) अणु
	हाल K90_MACRO_MODE_HW:
		macro_mode = "HW";
		अवरोध;

	हाल K90_MACRO_MODE_SW:
		macro_mode = "SW";
		अवरोध;
	शेष:
		dev_warn(dev, "K90 in unknown mode: %02hhx.\n",
			 data[0]);
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = snम_लिखो(buf, PAGE_SIZE, "%s\n", macro_mode);
out:
	kमुक्त(data);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार k90_store_macro_mode(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा usb_पूर्णांकerface *usbअगर = to_usb_पूर्णांकerface(dev->parent);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);
	__u16 value;

	अगर (म_भेदन(buf, "SW", 2) == 0)
		value = K90_MACRO_MODE_SW;
	अन्यथा अगर (म_भेदन(buf, "HW", 2) == 0)
		value = K90_MACRO_MODE_HW;
	अन्यथा
		वापस -EINVAL;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
			      K90_REQUEST_MACRO_MODE,
			      USB_सूची_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, 0, शून्य, 0,
			      USB_CTRL_SET_TIMEOUT);
	अगर (ret != 0) अणु
		dev_warn(dev, "Failed to set macro mode.\n");
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार k90_show_current_profile(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा usb_पूर्णांकerface *usbअगर = to_usb_पूर्णांकerface(dev->parent);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);
	पूर्णांक current_profile;
	अक्षर *data;

	data = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ret = usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0),
			      K90_REQUEST_STATUS,
			      USB_सूची_IN | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, 0, 0, data, 8,
			      USB_CTRL_SET_TIMEOUT);
	अगर (ret < 8) अणु
		dev_warn(dev, "Failed to get K90 initial state (error %d).\n",
			 ret);
		ret = -EIO;
		जाओ out;
	पूर्ण
	current_profile = data[7];
	अगर (current_profile < 1 || current_profile > 3) अणु
		dev_warn(dev, "Read invalid current profile: %02hhx.\n",
			 data[7]);
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = snम_लिखो(buf, PAGE_SIZE, "%d\n", current_profile);
out:
	kमुक्त(data);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार k90_store_current_profile(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा usb_पूर्णांकerface *usbअगर = to_usb_पूर्णांकerface(dev->parent);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);
	पूर्णांक profile;

	अगर (kstrtoपूर्णांक(buf, 10, &profile))
		वापस -EINVAL;
	अगर (profile < 1 || profile > 3)
		वापस -EINVAL;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
			      K90_REQUEST_PROखाता,
			      USB_सूची_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, profile, 0, शून्य, 0,
			      USB_CTRL_SET_TIMEOUT);
	अगर (ret != 0) अणु
		dev_warn(dev, "Failed to change current profile (error %d).\n",
			 ret);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR(macro_mode, 0644, k90_show_macro_mode, k90_store_macro_mode);
अटल DEVICE_ATTR(current_profile, 0644, k90_show_current_profile,
		   k90_store_current_profile);

अटल काष्ठा attribute *k90_attrs[] = अणु
	&dev_attr_macro_mode.attr,
	&dev_attr_current_profile.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group k90_attr_group = अणु
	.attrs = k90_attrs,
पूर्ण;

/*
 * Driver functions
 */

अटल पूर्णांक k90_init_backlight(काष्ठा hid_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा corsair_drvdata *drvdata = hid_get_drvdata(dev);
	माप_प्रकार name_sz;
	अक्षर *name;

	drvdata->backlight = kzalloc(माप(काष्ठा k90_led), GFP_KERNEL);
	अगर (!drvdata->backlight) अणु
		ret = -ENOMEM;
		जाओ fail_backlight_alloc;
	पूर्ण

	name_sz =
	    म_माप(dev_name(&dev->dev)) + माप(K90_BACKLIGHT_LED_SUFFIX);
	name = kzalloc(name_sz, GFP_KERNEL);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ fail_name_alloc;
	पूर्ण
	snम_लिखो(name, name_sz, "%s" K90_BACKLIGHT_LED_SUFFIX,
		 dev_name(&dev->dev));
	drvdata->backlight->हटाओd = false;
	drvdata->backlight->cdev.name = name;
	drvdata->backlight->cdev.max_brightness = 3;
	drvdata->backlight->cdev.brightness_set = k90_brightness_set;
	drvdata->backlight->cdev.brightness_get = k90_backlight_get;
	INIT_WORK(&drvdata->backlight->work, k90_backlight_work);
	ret = led_classdev_रेजिस्टर(&dev->dev, &drvdata->backlight->cdev);
	अगर (ret != 0)
		जाओ fail_रेजिस्टर_cdev;

	वापस 0;

fail_रेजिस्टर_cdev:
	kमुक्त(drvdata->backlight->cdev.name);
fail_name_alloc:
	kमुक्त(drvdata->backlight);
	drvdata->backlight = शून्य;
fail_backlight_alloc:
	वापस ret;
पूर्ण

अटल पूर्णांक k90_init_macro_functions(काष्ठा hid_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा corsair_drvdata *drvdata = hid_get_drvdata(dev);
	काष्ठा k90_drvdata *k90;
	माप_प्रकार name_sz;
	अक्षर *name;

	k90 = kzalloc(माप(काष्ठा k90_drvdata), GFP_KERNEL);
	अगर (!k90) अणु
		ret = -ENOMEM;
		जाओ fail_drvdata;
	पूर्ण
	drvdata->k90 = k90;

	/* Init LED device क्रम record LED */
	name_sz = म_माप(dev_name(&dev->dev)) + माप(K90_RECORD_LED_SUFFIX);
	name = kzalloc(name_sz, GFP_KERNEL);
	अगर (!name) अणु
		ret = -ENOMEM;
		जाओ fail_record_led_alloc;
	पूर्ण
	snम_लिखो(name, name_sz, "%s" K90_RECORD_LED_SUFFIX,
		 dev_name(&dev->dev));
	k90->record_led.हटाओd = false;
	k90->record_led.cdev.name = name;
	k90->record_led.cdev.max_brightness = 1;
	k90->record_led.cdev.brightness_set = k90_brightness_set;
	k90->record_led.cdev.brightness_get = k90_record_led_get;
	INIT_WORK(&k90->record_led.work, k90_record_led_work);
	k90->record_led.brightness = 0;
	ret = led_classdev_रेजिस्टर(&dev->dev, &k90->record_led.cdev);
	अगर (ret != 0)
		जाओ fail_record_led;

	/* Init attributes */
	ret = sysfs_create_group(&dev->dev.kobj, &k90_attr_group);
	अगर (ret != 0)
		जाओ fail_sysfs;

	वापस 0;

fail_sysfs:
	k90->record_led.हटाओd = true;
	led_classdev_unरेजिस्टर(&k90->record_led.cdev);
	cancel_work_sync(&k90->record_led.work);
fail_record_led:
	kमुक्त(k90->record_led.cdev.name);
fail_record_led_alloc:
	kमुक्त(k90);
fail_drvdata:
	drvdata->k90 = शून्य;
	वापस ret;
पूर्ण

अटल व्योम k90_cleanup_backlight(काष्ठा hid_device *dev)
अणु
	काष्ठा corsair_drvdata *drvdata = hid_get_drvdata(dev);

	अगर (drvdata->backlight) अणु
		drvdata->backlight->हटाओd = true;
		led_classdev_unरेजिस्टर(&drvdata->backlight->cdev);
		cancel_work_sync(&drvdata->backlight->work);
		kमुक्त(drvdata->backlight->cdev.name);
		kमुक्त(drvdata->backlight);
	पूर्ण
पूर्ण

अटल व्योम k90_cleanup_macro_functions(काष्ठा hid_device *dev)
अणु
	काष्ठा corsair_drvdata *drvdata = hid_get_drvdata(dev);
	काष्ठा k90_drvdata *k90 = drvdata->k90;

	अगर (k90) अणु
		sysfs_हटाओ_group(&dev->dev.kobj, &k90_attr_group);

		k90->record_led.हटाओd = true;
		led_classdev_unरेजिस्टर(&k90->record_led.cdev);
		cancel_work_sync(&k90->record_led.work);
		kमुक्त(k90->record_led.cdev.name);

		kमुक्त(k90);
	पूर्ण
पूर्ण

अटल पूर्णांक corsair_probe(काष्ठा hid_device *dev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ quirks = id->driver_data;
	काष्ठा corsair_drvdata *drvdata;
	काष्ठा usb_पूर्णांकerface *usbअगर = to_usb_पूर्णांकerface(dev->dev.parent);

	drvdata = devm_kzalloc(&dev->dev, माप(काष्ठा corsair_drvdata),
			       GFP_KERNEL);
	अगर (drvdata == शून्य)
		वापस -ENOMEM;
	drvdata->quirks = quirks;
	hid_set_drvdata(dev, drvdata);

	ret = hid_parse(dev);
	अगर (ret != 0) अणु
		hid_err(dev, "parse failed\n");
		वापस ret;
	पूर्ण
	ret = hid_hw_start(dev, HID_CONNECT_DEFAULT);
	अगर (ret != 0) अणु
		hid_err(dev, "hw start failed\n");
		वापस ret;
	पूर्ण

	अगर (usbअगर->cur_altsetting->desc.bInterfaceNumber == 0) अणु
		अगर (quirks & CORSAIR_USE_K90_MACRO) अणु
			ret = k90_init_macro_functions(dev);
			अगर (ret != 0)
				hid_warn(dev, "Failed to initialize K90 macro functions.\n");
		पूर्ण
		अगर (quirks & CORSAIR_USE_K90_BACKLIGHT) अणु
			ret = k90_init_backlight(dev);
			अगर (ret != 0)
				hid_warn(dev, "Failed to initialize K90 backlight.\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम corsair_हटाओ(काष्ठा hid_device *dev)
अणु
	k90_cleanup_macro_functions(dev);
	k90_cleanup_backlight(dev);

	hid_hw_stop(dev);
पूर्ण

अटल पूर्णांक corsair_event(काष्ठा hid_device *dev, काष्ठा hid_field *field,
			 काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा corsair_drvdata *drvdata = hid_get_drvdata(dev);

	अगर (!drvdata->k90)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल CORSAIR_USAGE_MACRO_RECORD_START:
		drvdata->k90->record_led.brightness = 1;
		अवरोध;
	हाल CORSAIR_USAGE_MACRO_RECORD_STOP:
		drvdata->k90->record_led.brightness = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक corsair_input_mapping(काष्ठा hid_device *dev,
				 काष्ठा hid_input *input,
				 काष्ठा hid_field *field,
				 काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit,
				 पूर्णांक *max)
अणु
	पूर्णांक gkey;

	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_KEYBOARD)
		वापस 0;

	gkey = corsair_usage_to_gkey(usage->hid & HID_USAGE);
	अगर (gkey != 0) अणु
		hid_map_usage_clear(input, usage, bit, max, EV_KEY,
				    corsair_gkey_map[gkey - 1]);
		वापस 1;
	पूर्ण
	अगर ((usage->hid & HID_USAGE) >= CORSAIR_USAGE_SPECIAL_MIN &&
	    (usage->hid & HID_USAGE) <= CORSAIR_USAGE_SPECIAL_MAX) अणु
		चयन (usage->hid & HID_USAGE) अणु
		हाल CORSAIR_USAGE_MACRO_RECORD_START:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_record_keycodes[0]);
			वापस 1;

		हाल CORSAIR_USAGE_MACRO_RECORD_STOP:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_record_keycodes[1]);
			वापस 1;

		हाल CORSAIR_USAGE_M1:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[0]);
			वापस 1;

		हाल CORSAIR_USAGE_M2:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[1]);
			वापस 1;

		हाल CORSAIR_USAGE_M3:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[2]);
			वापस 1;

		शेष:
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The report descriptor of some of the Corsair gaming mice is
 * non parseable as they define two consecutive Logical Minimum क्रम
 * the Usage Page (Consumer) in rdescs bytes 75 and 77 being 77 0x16
 * that should be obviousy 0x26 क्रम Logical Magimum of 16 bits. This
 * prevents poper parsing of the report descriptor due Logical
 * Minimum being larger than Logical Maximum.
 *
 * This driver fixes the report descriptor क्रम:
 * - USB ID 1b1c:1b34, sold as GLAIVE RGB Gaming mouse
 * - USB ID 1b1c:1b3e, sold as Scimitar RGB Pro Gaming mouse
 */

अटल __u8 *corsair_mouse_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
        अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber == 1) अणु
		/*
		 * Corsair GLAIVE RGB and Scimitar RGB Pro report descriptor is
		 * broken and defines two dअगरferent Logical Minimum क्रम the
		 * Consumer Application. The byte 77 should be a 0x26 defining
		 * a 16 bits पूर्णांकeger क्रम the Logical Maximum but it is a 0x16
		 * instead (Logical Minimum)
		 */
		चयन (hdev->product) अणु
		हाल USB_DEVICE_ID_CORSAIR_GLAIVE_RGB:
		हाल USB_DEVICE_ID_CORSAIR_SCIMITAR_PRO_RGB:
			अगर (*rsize >= 172 && rdesc[75] == 0x15 && rdesc[77] == 0x16
			&& rdesc[78] == 0xff && rdesc[79] == 0x0f) अणु
				hid_info(hdev, "Fixing up report descriptor\n");
				rdesc[77] = 0x26;
			पूर्ण
			अवरोध;
		पूर्ण

	पूर्ण
	वापस rdesc;
पूर्ण

अटल स्थिर काष्ठा hid_device_id corsair_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CORSAIR, USB_DEVICE_ID_CORSAIR_K90),
		.driver_data = CORSAIR_USE_K90_MACRO |
			       CORSAIR_USE_K90_BACKLIGHT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CORSAIR,
            USB_DEVICE_ID_CORSAIR_GLAIVE_RGB) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CORSAIR,
            USB_DEVICE_ID_CORSAIR_SCIMITAR_PRO_RGB) पूर्ण,
	/*
	 * Vengeance K70 and K70 RAPIDFIRE share product IDs.
	 */
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CORSAIR,
            USB_DEVICE_ID_CORSAIR_K70R) पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, corsair_devices);

अटल काष्ठा hid_driver corsair_driver = अणु
	.name = "corsair",
	.id_table = corsair_devices,
	.probe = corsair_probe,
	.event = corsair_event,
	.हटाओ = corsair_हटाओ,
	.input_mapping = corsair_input_mapping,
	.report_fixup = corsair_mouse_report_fixup,
पूर्ण;

module_hid_driver(corsair_driver);

MODULE_LICENSE("GPL");
/* Original K90 driver author */
MODULE_AUTHOR("Clement Vuchener");
/* Scimitar PRO RGB driver author */
MODULE_AUTHOR("Oscar Campos");
MODULE_DESCRIPTION("HID driver for Corsair devices");
