<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MSI GT683R led driver
 *
 * Copyright (c) 2014 Janne Kanniainen <janne.kanniainen@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा GT683R_BUFFER_SIZE			8

/*
 * GT683R_LED_OFF: all LEDs are off
 * GT683R_LED_AUDIO: LEDs brightness depends on sound level
 * GT683R_LED_BREATHING: LEDs brightness varies at human breathing rate
 * GT683R_LED_NORMAL: LEDs are fully on when enabled
 */
क्रमागत gt683r_led_mode अणु
	GT683R_LED_OFF = 0,
	GT683R_LED_AUDIO = 2,
	GT683R_LED_BREATHING = 3,
	GT683R_LED_NORMAL = 5
पूर्ण;

क्रमागत gt683r_panels अणु
	GT683R_LED_BACK = 0,
	GT683R_LED_SIDE = 1,
	GT683R_LED_FRONT = 2,
	GT683R_LED_COUNT,
पूर्ण;

अटल स्थिर अक्षर * स्थिर gt683r_panel_names[] = अणु
	"back",
	"side",
	"front",
पूर्ण;

काष्ठा gt683r_led अणु
	काष्ठा hid_device *hdev;
	काष्ठा led_classdev led_devs[GT683R_LED_COUNT];
	काष्ठा mutex lock;
	काष्ठा work_काष्ठा work;
	क्रमागत led_brightness brightnesses[GT683R_LED_COUNT];
	क्रमागत gt683r_led_mode mode;
पूर्ण;

अटल स्थिर काष्ठा hid_device_id gt683r_led_id[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MSI, USB_DEVICE_ID_MSI_GT683R_LED_PANEL) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, gt683r_led_id);

अटल व्योम gt683r_brightness_set(काष्ठा led_classdev *led_cdev,
				क्रमागत led_brightness brightness)
अणु
	पूर्णांक i;
	काष्ठा device *dev = led_cdev->dev->parent;
	काष्ठा hid_device *hdev = to_hid_device(dev);
	काष्ठा gt683r_led *led = hid_get_drvdata(hdev);

	क्रम (i = 0; i < GT683R_LED_COUNT; i++) अणु
		अगर (led_cdev == &led->led_devs[i])
			अवरोध;
	पूर्ण

	अगर (i < GT683R_LED_COUNT) अणु
		led->brightnesses[i] = brightness;
		schedule_work(&led->work);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	u8 sysfs_mode;
	काष्ठा hid_device *hdev = to_hid_device(dev->parent);
	काष्ठा gt683r_led *led = hid_get_drvdata(hdev);

	अगर (led->mode == GT683R_LED_NORMAL)
		sysfs_mode = 0;
	अन्यथा अगर (led->mode == GT683R_LED_AUDIO)
		sysfs_mode = 1;
	अन्यथा
		sysfs_mode = 2;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", sysfs_mode);
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u8 sysfs_mode;
	काष्ठा hid_device *hdev = to_hid_device(dev->parent);
	काष्ठा gt683r_led *led = hid_get_drvdata(hdev);


	अगर (kstrtou8(buf, 10, &sysfs_mode) || sysfs_mode > 2)
		वापस -EINVAL;

	mutex_lock(&led->lock);

	अगर (sysfs_mode == 0)
		led->mode = GT683R_LED_NORMAL;
	अन्यथा अगर (sysfs_mode == 1)
		led->mode = GT683R_LED_AUDIO;
	अन्यथा
		led->mode = GT683R_LED_BREATHING;

	mutex_unlock(&led->lock);
	schedule_work(&led->work);

	वापस count;
पूर्ण

अटल पूर्णांक gt683r_led_snd_msg(काष्ठा gt683r_led *led, u8 *msg)
अणु
	पूर्णांक ret;

	ret = hid_hw_raw_request(led->hdev, msg[0], msg, GT683R_BUFFER_SIZE,
				HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
	अगर (ret != GT683R_BUFFER_SIZE) अणु
		hid_err(led->hdev,
			"failed to send set report request: %i\n", ret);
		अगर (ret < 0)
			वापस ret;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gt683r_leds_set(काष्ठा gt683r_led *led, u8 leds)
अणु
	पूर्णांक ret;
	u8 *buffer;

	buffer = kzalloc(GT683R_BUFFER_SIZE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer[0] = 0x01;
	buffer[1] = 0x02;
	buffer[2] = 0x30;
	buffer[3] = leds;
	ret = gt683r_led_snd_msg(led, buffer);

	kमुक्त(buffer);
	वापस ret;
पूर्ण

अटल पूर्णांक gt683r_mode_set(काष्ठा gt683r_led *led, u8 mode)
अणु
	पूर्णांक ret;
	u8 *buffer;

	buffer = kzalloc(GT683R_BUFFER_SIZE, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	buffer[0] = 0x01;
	buffer[1] = 0x02;
	buffer[2] = 0x20;
	buffer[3] = mode;
	buffer[4] = 0x01;
	ret = gt683r_led_snd_msg(led, buffer);

	kमुक्त(buffer);
	वापस ret;
पूर्ण

अटल व्योम gt683r_led_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;
	u8 leds = 0;
	u8 mode;
	काष्ठा gt683r_led *led = container_of(work, काष्ठा gt683r_led, work);

	mutex_lock(&led->lock);

	क्रम (i = 0; i < GT683R_LED_COUNT; i++) अणु
		अगर (led->brightnesses[i])
			leds |= BIT(i);
	पूर्ण

	अगर (gt683r_leds_set(led, leds))
		जाओ fail;

	अगर (leds)
		mode = led->mode;
	अन्यथा
		mode = GT683R_LED_OFF;

	gt683r_mode_set(led, mode);
fail:
	mutex_unlock(&led->lock);
पूर्ण

अटल DEVICE_ATTR_RW(mode);

अटल काष्ठा attribute *gt683r_led_attrs[] = अणु
	&dev_attr_mode.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group gt683r_led_group = अणु
	.name = "gt683r",
	.attrs = gt683r_led_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *gt683r_led_groups[] = अणु
	&gt683r_led_group,
	शून्य
पूर्ण;

अटल पूर्णांक gt683r_led_probe(काष्ठा hid_device *hdev,
			स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक name_sz;
	अक्षर *name;
	काष्ठा gt683r_led *led;

	led = devm_kzalloc(&hdev->dev, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	mutex_init(&led->lock);
	INIT_WORK(&led->work, gt683r_led_work);

	led->mode = GT683R_LED_NORMAL;
	led->hdev = hdev;
	hid_set_drvdata(hdev, led);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "hid parsing failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_HIDRAW);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < GT683R_LED_COUNT; i++) अणु
		name_sz = म_माप(dev_name(&hdev->dev)) +
				म_माप(gt683r_panel_names[i]) + 3;

		name = devm_kzalloc(&hdev->dev, name_sz, GFP_KERNEL);
		अगर (!name) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		snम_लिखो(name, name_sz, "%s::%s",
				dev_name(&hdev->dev), gt683r_panel_names[i]);
		led->led_devs[i].name = name;
		led->led_devs[i].max_brightness = 1;
		led->led_devs[i].brightness_set = gt683r_brightness_set;
		led->led_devs[i].groups = gt683r_led_groups;

		ret = led_classdev_रेजिस्टर(&hdev->dev, &led->led_devs[i]);
		अगर (ret) अणु
			hid_err(hdev, "could not register led device\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	क्रम (i = i - 1; i >= 0; i--)
		led_classdev_unरेजिस्टर(&led->led_devs[i]);
	hid_hw_stop(hdev);
	वापस ret;
पूर्ण

अटल व्योम gt683r_led_हटाओ(काष्ठा hid_device *hdev)
अणु
	पूर्णांक i;
	काष्ठा gt683r_led *led = hid_get_drvdata(hdev);

	क्रम (i = 0; i < GT683R_LED_COUNT; i++)
		led_classdev_unरेजिस्टर(&led->led_devs[i]);
	flush_work(&led->work);
	hid_hw_stop(hdev);
पूर्ण

अटल काष्ठा hid_driver gt683r_led_driver = अणु
	.probe = gt683r_led_probe,
	.हटाओ = gt683r_led_हटाओ,
	.name = "gt683r_led",
	.id_table = gt683r_led_id,
पूर्ण;

module_hid_driver(gt683r_led_driver);

MODULE_AUTHOR("Janne Kanniainen");
MODULE_DESCRIPTION("MSI GT683R led driver");
MODULE_LICENSE("GPL");
