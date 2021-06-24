<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Kernel Timer Trigger
 *
 * Copyright 2005-2006 Openedhand Ltd.
 *
 * Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <linux/leds.h>

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
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &state);
	अगर (ret)
		वापस ret;

	led_blink_set(led_cdev, &state, &led_cdev->blink_delay_off);
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
	sमाप_प्रकार ret;

	ret = kम_से_अदीर्घ(buf, 10, &state);
	अगर (ret)
		वापस ret;

	led_blink_set(led_cdev, &led_cdev->blink_delay_on, &state);
	led_cdev->blink_delay_off = state;

	वापस size;
पूर्ण

अटल DEVICE_ATTR(delay_on, 0644, led_delay_on_show, led_delay_on_store);
अटल DEVICE_ATTR(delay_off, 0644, led_delay_off_show, led_delay_off_store);

अटल काष्ठा attribute *समयr_trig_attrs[] = अणु
	&dev_attr_delay_on.attr,
	&dev_attr_delay_off.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(समयr_trig);

अटल व्योम pattern_init(काष्ठा led_classdev *led_cdev)
अणु
	u32 *pattern;
	अचिन्हित पूर्णांक size = 0;

	pattern = led_get_शेष_pattern(led_cdev, &size);
	अगर (!pattern)
		वापस;

	अगर (size != 2) अणु
		dev_warn(led_cdev->dev,
			 "Expected 2 but got %u values for delays pattern\n",
			 size);
		जाओ out;
	पूर्ण

	led_cdev->blink_delay_on = pattern[0];
	led_cdev->blink_delay_off = pattern[1];
	/* led_blink_set() called by caller */

out:
	kमुक्त(pattern);
पूर्ण

अटल पूर्णांक समयr_trig_activate(काष्ठा led_classdev *led_cdev)
अणु
	अगर (led_cdev->flags & LED_INIT_DEFAULT_TRIGGER) अणु
		pattern_init(led_cdev);
		/*
		 * Mark as initialized even on pattern_init() error because
		 * any consecutive call to it would produce the same error.
		 */
		led_cdev->flags &= ~LED_INIT_DEFAULT_TRIGGER;
	पूर्ण

	/*
	 * If "set brightness to 0" is pending in workqueue, we करोn't
	 * want that to be reordered after blink_set()
	 */
	flush_work(&led_cdev->set_brightness_work);
	led_blink_set(led_cdev, &led_cdev->blink_delay_on,
		      &led_cdev->blink_delay_off);

	वापस 0;
पूर्ण

अटल व्योम समयr_trig_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	/* Stop blinking */
	led_set_brightness(led_cdev, LED_OFF);
पूर्ण

अटल काष्ठा led_trigger समयr_led_trigger = अणु
	.name     = "timer",
	.activate = समयr_trig_activate,
	.deactivate = समयr_trig_deactivate,
	.groups = समयr_trig_groups,
पूर्ण;
module_led_trigger(समयr_led_trigger);

MODULE_AUTHOR("Richard Purdie <rpurdie@openedhand.com>");
MODULE_DESCRIPTION("Timer LED trigger");
MODULE_LICENSE("GPL v2");
