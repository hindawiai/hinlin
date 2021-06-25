<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * One-shot LED Trigger
 *
 * Copyright 2012, Fabio Baltieri <fabio.baltieri@gmail.com>
 *
 * Based on ledtrig-समयr.c by Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>
#समावेश "../leds.h"

#घोषणा DEFAULT_DELAY 100

काष्ठा oneshot_trig_data अणु
	अचिन्हित पूर्णांक invert;
पूर्ण;

अटल sमाप_प्रकार led_shot(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = led_trigger_get_led(dev);
	काष्ठा oneshot_trig_data *oneshot_data = led_trigger_get_drvdata(dev);

	led_blink_set_oneshot(led_cdev,
			&led_cdev->blink_delay_on, &led_cdev->blink_delay_off,
			oneshot_data->invert);

	/* content is ignored */
	वापस size;
पूर्ण
अटल sमाप_प्रकार led_invert_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा oneshot_trig_data *oneshot_data = led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", oneshot_data->invert);
पूर्ण

अटल sमाप_प्रकार led_invert_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = led_trigger_get_led(dev);
	काष्ठा oneshot_trig_data *oneshot_data = led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &state);
	अगर (ret)
		वापस ret;

	oneshot_data->invert = !!state;

	अगर (oneshot_data->invert)
		led_set_brightness_nosleep(led_cdev, LED_FULL);
	अन्यथा
		led_set_brightness_nosleep(led_cdev, LED_OFF);

	वापस size;
पूर्ण

अटल sमाप_प्रकार led_delay_on_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = led_trigger_get_led(dev);

	वापस प्र_लिखो(buf, "%lu\n", led_cdev->blink_delay_on);
पूर्ण

अटल sमाप_प्रकार led_delay_on_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = led_trigger_get_led(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &state);
	अगर (ret)
		वापस ret;

	led_cdev->blink_delay_on = state;

	वापस size;
पूर्ण

अटल sमाप_प्रकार led_delay_off_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = led_trigger_get_led(dev);

	वापस प्र_लिखो(buf, "%lu\n", led_cdev->blink_delay_off);
पूर्ण

अटल sमाप_प्रकार led_delay_off_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा led_classdev *led_cdev = led_trigger_get_led(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &state);
	अगर (ret)
		वापस ret;

	led_cdev->blink_delay_off = state;

	वापस size;
पूर्ण

अटल DEVICE_ATTR(delay_on, 0644, led_delay_on_show, led_delay_on_store);
अटल DEVICE_ATTR(delay_off, 0644, led_delay_off_show, led_delay_off_store);
अटल DEVICE_ATTR(invert, 0644, led_invert_show, led_invert_store);
अटल DEVICE_ATTR(shot, 0200, शून्य, led_shot);

अटल काष्ठा attribute *oneshot_trig_attrs[] = अणु
	&dev_attr_delay_on.attr,
	&dev_attr_delay_off.attr,
	&dev_attr_invert.attr,
	&dev_attr_shot.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(oneshot_trig);

अटल व्योम pattern_init(काष्ठा led_classdev *led_cdev)
अणु
	u32 *pattern;
	अचिन्हित पूर्णांक size = 0;

	pattern = led_get_शेष_pattern(led_cdev, &size);
	अगर (!pattern)
		जाओ out_शेष;

	अगर (size != 2) अणु
		dev_warn(led_cdev->dev,
			 "Expected 2 but got %u values for delays pattern\n",
			 size);
		जाओ out_शेष;
	पूर्ण

	led_cdev->blink_delay_on = pattern[0];
	led_cdev->blink_delay_off = pattern[1];
	kमुक्त(pattern);

	वापस;

out_शेष:
	kमुक्त(pattern);
	led_cdev->blink_delay_on = DEFAULT_DELAY;
	led_cdev->blink_delay_off = DEFAULT_DELAY;
पूर्ण

अटल पूर्णांक oneshot_trig_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा oneshot_trig_data *oneshot_data;

	oneshot_data = kzalloc(माप(*oneshot_data), GFP_KERNEL);
	अगर (!oneshot_data)
		वापस -ENOMEM;

	led_set_trigger_data(led_cdev, oneshot_data);

	अगर (led_cdev->flags & LED_INIT_DEFAULT_TRIGGER) अणु
		pattern_init(led_cdev);
		/*
		 * Mark as initialized even on pattern_init() error because
		 * any consecutive call to it would produce the same error.
		 */
		led_cdev->flags &= ~LED_INIT_DEFAULT_TRIGGER;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम oneshot_trig_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा oneshot_trig_data *oneshot_data = led_get_trigger_data(led_cdev);

	kमुक्त(oneshot_data);

	/* Stop blinking */
	led_set_brightness(led_cdev, LED_OFF);
पूर्ण

अटल काष्ठा led_trigger oneshot_led_trigger = अणु
	.name     = "oneshot",
	.activate = oneshot_trig_activate,
	.deactivate = oneshot_trig_deactivate,
	.groups = oneshot_trig_groups,
पूर्ण;
module_led_trigger(oneshot_led_trigger);

MODULE_AUTHOR("Fabio Baltieri <fabio.baltieri@gmail.com>");
MODULE_DESCRIPTION("One-shot LED trigger");
MODULE_LICENSE("GPL v2");
