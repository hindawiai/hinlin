<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/***************************************************************************
 *   Copyright (C) 2010-2012 by Bruno Prथऊmont <bonbons@linux-vserver.org>  *
 *                                                                         *
 *   Based on Logitech G13 driver (v0.4)                                   *
 *     Copyright (C) 2009 by Rick L. Vinyard, Jr. <rvinyard@cs.nmsu.edu>   *
 *                                                                         *
 ***************************************************************************/

#समावेश <linux/hid.h>
#समावेश <linux/hid-debug.h>
#समावेश <linux/input.h>
#समावेश "hid-ids.h"

#समावेश <linux/fb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/backlight.h>
#समावेश <linux/lcd.h>

#समावेश <linux/leds.h>

#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/completion.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>

#समावेश "hid-picolcd.h"


व्योम picolcd_leds_set(काष्ठा picolcd_data *data)
अणु
	काष्ठा hid_report *report;
	अचिन्हित दीर्घ flags;

	अगर (!data->led[0])
		वापस;
	report = picolcd_out_report(REPORT_LED_STATE, data->hdev);
	अगर (!report || report->maxfield != 1 || report->field[0]->report_count != 1)
		वापस;

	spin_lock_irqsave(&data->lock, flags);
	hid_set_field(report->field[0], 0, data->led_state);
	अगर (!(data->status & PICOLCD_FAILED))
		hid_hw_request(data->hdev, report, HID_REQ_SET_REPORT);
	spin_unlock_irqrestore(&data->lock, flags);
पूर्ण

अटल व्योम picolcd_led_set_brightness(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness value)
अणु
	काष्ठा device *dev;
	काष्ठा hid_device *hdev;
	काष्ठा picolcd_data *data;
	पूर्णांक i, state = 0;

	dev  = led_cdev->dev->parent;
	hdev = to_hid_device(dev);
	data = hid_get_drvdata(hdev);
	अगर (!data)
		वापस;
	क्रम (i = 0; i < 8; i++) अणु
		अगर (led_cdev != data->led[i])
			जारी;
		state = (data->led_state >> i) & 1;
		अगर (value == LED_OFF && state) अणु
			data->led_state &= ~(1 << i);
			picolcd_leds_set(data);
		पूर्ण अन्यथा अगर (value != LED_OFF && !state) अणु
			data->led_state |= 1 << i;
			picolcd_leds_set(data);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत led_brightness picolcd_led_get_brightness(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा device *dev;
	काष्ठा hid_device *hdev;
	काष्ठा picolcd_data *data;
	पूर्णांक i, value = 0;

	dev  = led_cdev->dev->parent;
	hdev = to_hid_device(dev);
	data = hid_get_drvdata(hdev);
	क्रम (i = 0; i < 8; i++)
		अगर (led_cdev == data->led[i]) अणु
			value = (data->led_state >> i) & 1;
			अवरोध;
		पूर्ण
	वापस value ? LED_FULL : LED_OFF;
पूर्ण

पूर्णांक picolcd_init_leds(काष्ठा picolcd_data *data, काष्ठा hid_report *report)
अणु
	काष्ठा device *dev = &data->hdev->dev;
	काष्ठा led_classdev *led;
	माप_प्रकार name_sz = म_माप(dev_name(dev)) + 8;
	अक्षर *name;
	पूर्णांक i, ret = 0;

	अगर (!report)
		वापस -ENODEV;
	अगर (report->maxfield != 1 || report->field[0]->report_count != 1 ||
			report->field[0]->report_size != 8) अणु
		dev_err(dev, "unsupported LED_STATE report");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		led = kzalloc(माप(काष्ठा led_classdev)+name_sz, GFP_KERNEL);
		अगर (!led) अणु
			dev_err(dev, "can't allocate memory for LED %d\n", i);
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
		name = (व्योम *)(&led[1]);
		snम_लिखो(name, name_sz, "%s::GPO%d", dev_name(dev), i);
		led->name = name;
		led->brightness = 0;
		led->max_brightness = 1;
		led->brightness_get = picolcd_led_get_brightness;
		led->brightness_set = picolcd_led_set_brightness;

		data->led[i] = led;
		ret = led_classdev_रेजिस्टर(dev, data->led[i]);
		अगर (ret) अणु
			data->led[i] = शून्य;
			kमुक्त(led);
			dev_err(dev, "can't register LED %d\n", i);
			जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;
err:
	क्रम (i = 0; i < 8; i++)
		अगर (data->led[i]) अणु
			led = data->led[i];
			data->led[i] = शून्य;
			led_classdev_unरेजिस्टर(led);
			kमुक्त(led);
		पूर्ण
	वापस ret;
पूर्ण

व्योम picolcd_निकास_leds(काष्ठा picolcd_data *data)
अणु
	काष्ठा led_classdev *led;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		led = data->led[i];
		data->led[i] = शून्य;
		अगर (!led)
			जारी;
		led_classdev_unरेजिस्टर(led);
		kमुक्त(led);
	पूर्ण
पूर्ण


