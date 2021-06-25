<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight emulation LED trigger
 *
 * Copyright 2008 (C) Roकरोlfo Giometti <giometti@linux.it>
 * Copyright 2008 (C) Eurotech S.p.A. <info@eurotech.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/fb.h>
#समावेश <linux/leds.h>
#समावेश "../leds.h"

#घोषणा BLANK		1
#घोषणा UNBLANK		0

काष्ठा bl_trig_notअगरier अणु
	काष्ठा led_classdev *led;
	पूर्णांक brightness;
	पूर्णांक old_status;
	काष्ठा notअगरier_block notअगरier;
	अचिन्हित invert;
पूर्ण;

अटल पूर्णांक fb_notअगरier_callback(काष्ठा notअगरier_block *p,
				अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा bl_trig_notअगरier *n = container_of(p,
					काष्ठा bl_trig_notअगरier, notअगरier);
	काष्ठा led_classdev *led = n->led;
	काष्ठा fb_event *fb_event = data;
	पूर्णांक *blank;
	पूर्णांक new_status;

	/* If we aren't पूर्णांकerested in this event, skip it immediately ... */
	अगर (event != FB_EVENT_BLANK)
		वापस 0;

	blank = fb_event->data;
	new_status = *blank ? BLANK : UNBLANK;

	अगर (new_status == n->old_status)
		वापस 0;

	अगर ((n->old_status == UNBLANK) ^ n->invert) अणु
		n->brightness = led->brightness;
		led_set_brightness_nosleep(led, LED_OFF);
	पूर्ण अन्यथा अणु
		led_set_brightness_nosleep(led, n->brightness);
	पूर्ण

	n->old_status = new_status;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार bl_trig_invert_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bl_trig_notअगरier *n = led_trigger_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", n->invert);
पूर्ण

अटल sमाप_प्रकार bl_trig_invert_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार num)
अणु
	काष्ठा led_classdev *led = led_trigger_get_led(dev);
	काष्ठा bl_trig_notअगरier *n = led_trigger_get_drvdata(dev);
	अचिन्हित दीर्घ invert;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &invert);
	अगर (ret < 0)
		वापस ret;

	अगर (invert > 1)
		वापस -EINVAL;

	n->invert = invert;

	/* After inverting, we need to update the LED. */
	अगर ((n->old_status == BLANK) ^ n->invert)
		led_set_brightness_nosleep(led, LED_OFF);
	अन्यथा
		led_set_brightness_nosleep(led, n->brightness);

	वापस num;
पूर्ण
अटल DEVICE_ATTR(inverted, 0644, bl_trig_invert_show, bl_trig_invert_store);

अटल काष्ठा attribute *bl_trig_attrs[] = अणु
	&dev_attr_inverted.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(bl_trig);

अटल पूर्णांक bl_trig_activate(काष्ठा led_classdev *led)
अणु
	पूर्णांक ret;

	काष्ठा bl_trig_notअगरier *n;

	n = kzalloc(माप(काष्ठा bl_trig_notअगरier), GFP_KERNEL);
	अगर (!n)
		वापस -ENOMEM;
	led_set_trigger_data(led, n);

	n->led = led;
	n->brightness = led->brightness;
	n->old_status = UNBLANK;
	n->notअगरier.notअगरier_call = fb_notअगरier_callback;

	ret = fb_रेजिस्टर_client(&n->notअगरier);
	अगर (ret)
		dev_err(led->dev, "unable to register backlight trigger\n");

	वापस 0;
पूर्ण

अटल व्योम bl_trig_deactivate(काष्ठा led_classdev *led)
अणु
	काष्ठा bl_trig_notअगरier *n = led_get_trigger_data(led);

	fb_unरेजिस्टर_client(&n->notअगरier);
	kमुक्त(n);
पूर्ण

अटल काष्ठा led_trigger bl_led_trigger = अणु
	.name		= "backlight",
	.activate	= bl_trig_activate,
	.deactivate	= bl_trig_deactivate,
	.groups		= bl_trig_groups,
पूर्ण;
module_led_trigger(bl_led_trigger);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("Backlight emulation LED trigger");
MODULE_LICENSE("GPL v2");
