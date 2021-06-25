<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00lib
	Abstract: rt2x00 led specअगरic routines.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "rt2x00.h"
#समावेश "rt2x00lib.h"

व्योम rt2x00leds_led_quality(काष्ठा rt2x00_dev *rt2x00dev, पूर्णांक rssi)
अणु
	काष्ठा rt2x00_led *led = &rt2x00dev->led_qual;
	अचिन्हित पूर्णांक brightness;

	अगर ((led->type != LED_TYPE_QUALITY) || !(led->flags & LED_REGISTERED))
		वापस;

	/*
	 * Led handling requires a positive value क्रम the rssi,
	 * to करो that correctly we need to add the correction.
	 */
	rssi += rt2x00dev->rssi_offset;

	/*
	 * Get the rssi level, this is used to convert the rssi
	 * to a LED value inside the range LED_OFF - LED_FULL.
	 */
	अगर (rssi <= 30)
		rssi = 0;
	अन्यथा अगर (rssi <= 39)
		rssi = 1;
	अन्यथा अगर (rssi <= 49)
		rssi = 2;
	अन्यथा अगर (rssi <= 53)
		rssi = 3;
	अन्यथा अगर (rssi <= 63)
		rssi = 4;
	अन्यथा
		rssi = 5;

	/*
	 * Note that we must _not_ send LED_OFF since the driver
	 * is going to calculate the value and might use it in a
	 * भागision.
	 */
	brightness = ((LED_FULL / 6) * rssi) + 1;
	अगर (brightness != led->led_dev.brightness) अणु
		led->led_dev.brightness_set(&led->led_dev, brightness);
		led->led_dev.brightness = brightness;
	पूर्ण
पूर्ण

अटल व्योम rt2x00led_led_simple(काष्ठा rt2x00_led *led, bool enabled)
अणु
	अचिन्हित पूर्णांक brightness = enabled ? LED_FULL : LED_OFF;

	अगर (!(led->flags & LED_REGISTERED))
		वापस;

	led->led_dev.brightness_set(&led->led_dev, brightness);
	led->led_dev.brightness = brightness;
पूर्ण

व्योम rt2x00led_led_activity(काष्ठा rt2x00_dev *rt2x00dev, bool enabled)
अणु
	अगर (rt2x00dev->led_qual.type == LED_TYPE_ACTIVITY)
		rt2x00led_led_simple(&rt2x00dev->led_qual, enabled);
पूर्ण

व्योम rt2x00leds_led_assoc(काष्ठा rt2x00_dev *rt2x00dev, bool enabled)
अणु
	अगर (rt2x00dev->led_assoc.type == LED_TYPE_ASSOC)
		rt2x00led_led_simple(&rt2x00dev->led_assoc, enabled);
पूर्ण

व्योम rt2x00leds_led_radio(काष्ठा rt2x00_dev *rt2x00dev, bool enabled)
अणु
	अगर (rt2x00dev->led_radio.type == LED_TYPE_RADIO)
		rt2x00led_led_simple(&rt2x00dev->led_radio, enabled);
पूर्ण

अटल पूर्णांक rt2x00leds_रेजिस्टर_led(काष्ठा rt2x00_dev *rt2x00dev,
				   काष्ठा rt2x00_led *led,
				   स्थिर अक्षर *name)
अणु
	काष्ठा device *device = wiphy_dev(rt2x00dev->hw->wiphy);
	पूर्णांक retval;

	led->led_dev.name = name;
	led->led_dev.brightness = LED_OFF;

	retval = led_classdev_रेजिस्टर(device, &led->led_dev);
	अगर (retval) अणु
		rt2x00_err(rt2x00dev, "Failed to register led handler\n");
		वापस retval;
	पूर्ण

	led->flags |= LED_REGISTERED;

	वापस 0;
पूर्ण

व्योम rt2x00leds_रेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अक्षर name[36];
	पूर्णांक retval;
	अचिन्हित दीर्घ on_period;
	अचिन्हित दीर्घ off_period;
	स्थिर अक्षर *phy_name = wiphy_name(rt2x00dev->hw->wiphy);

	अगर (rt2x00dev->led_radio.flags & LED_INITIALIZED) अणु
		snम_लिखो(name, माप(name), "%s-%s::radio",
			 rt2x00dev->ops->name, phy_name);

		retval = rt2x00leds_रेजिस्टर_led(rt2x00dev,
						 &rt2x00dev->led_radio,
						 name);
		अगर (retval)
			जाओ निकास_fail;
	पूर्ण

	अगर (rt2x00dev->led_assoc.flags & LED_INITIALIZED) अणु
		snम_लिखो(name, माप(name), "%s-%s::assoc",
			 rt2x00dev->ops->name, phy_name);

		retval = rt2x00leds_रेजिस्टर_led(rt2x00dev,
						 &rt2x00dev->led_assoc,
						 name);
		अगर (retval)
			जाओ निकास_fail;
	पूर्ण

	अगर (rt2x00dev->led_qual.flags & LED_INITIALIZED) अणु
		snम_लिखो(name, माप(name), "%s-%s::quality",
			 rt2x00dev->ops->name, phy_name);

		retval = rt2x00leds_रेजिस्टर_led(rt2x00dev,
						 &rt2x00dev->led_qual,
						 name);
		अगर (retval)
			जाओ निकास_fail;
	पूर्ण

	/*
	 * Initialize blink समय to शेष value:
	 * On period: 70ms
	 * Off period: 30ms
	 */
	अगर (rt2x00dev->led_radio.led_dev.blink_set) अणु
		on_period = 70;
		off_period = 30;
		rt2x00dev->led_radio.led_dev.blink_set(
		    &rt2x00dev->led_radio.led_dev, &on_period, &off_period);
	पूर्ण

	वापस;

निकास_fail:
	rt2x00leds_unरेजिस्टर(rt2x00dev);
पूर्ण

अटल व्योम rt2x00leds_unरेजिस्टर_led(काष्ठा rt2x00_led *led)
अणु
	led_classdev_unरेजिस्टर(&led->led_dev);

	/*
	 * This might look weird, but when we are unरेजिस्टरing जबतक
	 * suspended the led is alपढ़ोy off, and since we haven't
	 * fully resumed yet, access to the device might not be
	 * possible yet.
	 */
	अगर (!(led->led_dev.flags & LED_SUSPENDED))
		led->led_dev.brightness_set(&led->led_dev, LED_OFF);

	led->flags &= ~LED_REGISTERED;
पूर्ण

व्योम rt2x00leds_unरेजिस्टर(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (rt2x00dev->led_qual.flags & LED_REGISTERED)
		rt2x00leds_unरेजिस्टर_led(&rt2x00dev->led_qual);
	अगर (rt2x00dev->led_assoc.flags & LED_REGISTERED)
		rt2x00leds_unरेजिस्टर_led(&rt2x00dev->led_assoc);
	अगर (rt2x00dev->led_radio.flags & LED_REGISTERED)
		rt2x00leds_unरेजिस्टर_led(&rt2x00dev->led_radio);
पूर्ण

अटल अंतरभूत व्योम rt2x00leds_suspend_led(काष्ठा rt2x00_led *led)
अणु
	led_classdev_suspend(&led->led_dev);

	/* This shouldn't be needed, but just to be safe */
	led->led_dev.brightness_set(&led->led_dev, LED_OFF);
	led->led_dev.brightness = LED_OFF;
पूर्ण

व्योम rt2x00leds_suspend(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (rt2x00dev->led_qual.flags & LED_REGISTERED)
		rt2x00leds_suspend_led(&rt2x00dev->led_qual);
	अगर (rt2x00dev->led_assoc.flags & LED_REGISTERED)
		rt2x00leds_suspend_led(&rt2x00dev->led_assoc);
	अगर (rt2x00dev->led_radio.flags & LED_REGISTERED)
		rt2x00leds_suspend_led(&rt2x00dev->led_radio);
पूर्ण

अटल अंतरभूत व्योम rt2x00leds_resume_led(काष्ठा rt2x00_led *led)
अणु
	led_classdev_resume(&led->led_dev);

	/* Device might have enabled the LEDS during resume */
	led->led_dev.brightness_set(&led->led_dev, LED_OFF);
	led->led_dev.brightness = LED_OFF;
पूर्ण

व्योम rt2x00leds_resume(काष्ठा rt2x00_dev *rt2x00dev)
अणु
	अगर (rt2x00dev->led_radio.flags & LED_REGISTERED)
		rt2x00leds_resume_led(&rt2x00dev->led_radio);
	अगर (rt2x00dev->led_assoc.flags & LED_REGISTERED)
		rt2x00leds_resume_led(&rt2x00dev->led_assoc);
	अगर (rt2x00dev->led_qual.flags & LED_REGISTERED)
		rt2x00leds_resume_led(&rt2x00dev->led_qual);
पूर्ण
