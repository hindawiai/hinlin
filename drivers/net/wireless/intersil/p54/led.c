<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common code क्रम mac80211 Prism54 drivers
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2007-2009, Christian Lamparter <chunkeey@web.de>
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 *
 * Based on:
 * - the islsm (sofपंचांगac prism54) driver, which is:
 *   Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 * - stlc45xx driver
 *   Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 */

#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>

#समावेश <net/mac80211.h>
#अगर_घोषित CONFIG_P54_LEDS
#समावेश <linux/leds.h>
#पूर्ण_अगर /* CONFIG_P54_LEDS */

#समावेश "p54.h"
#समावेश "lmac.h"

अटल व्योम p54_update_leds(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा p54_common *priv = container_of(work, काष्ठा p54_common,
					       led_work.work);
	पूर्णांक err, i, पंचांगp, blink_delay = 400;
	bool rerun = false;

	/* Don't toggle the LED, when the device is करोwn. */
	अगर (priv->mode == NL80211_IFTYPE_UNSPECIFIED)
		वापस ;

	क्रम (i = 0; i < ARRAY_SIZE(priv->leds); i++)
		अगर (priv->leds[i].toggled) अणु
			priv->softled_state |= BIT(i);

			पंचांगp = 70 + 200 / (priv->leds[i].toggled);
			अगर (पंचांगp < blink_delay)
				blink_delay = पंचांगp;

			अगर (priv->leds[i].led_dev.brightness == LED_OFF)
				rerun = true;

			priv->leds[i].toggled =
				!!priv->leds[i].led_dev.brightness;
		पूर्ण अन्यथा
			priv->softled_state &= ~BIT(i);

	err = p54_set_leds(priv);
	अगर (err && net_ratelimit())
		wiphy_err(priv->hw->wiphy,
			  "failed to update LEDs (%d).\n", err);

	अगर (rerun)
		ieee80211_queue_delayed_work(priv->hw, &priv->led_work,
			msecs_to_jअगरfies(blink_delay));
पूर्ण

अटल व्योम p54_led_brightness_set(काष्ठा led_classdev *led_dev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा p54_led_dev *led = container_of(led_dev, काष्ठा p54_led_dev,
					       led_dev);
	काष्ठा ieee80211_hw *dev = led->hw_dev;
	काष्ठा p54_common *priv = dev->priv;

	अगर (priv->mode == NL80211_IFTYPE_UNSPECIFIED)
		वापस ;

	अगर ((brightness) && (led->रेजिस्टरed)) अणु
		led->toggled++;
		ieee80211_queue_delayed_work(priv->hw, &priv->led_work, HZ/10);
	पूर्ण
पूर्ण

अटल पूर्णांक p54_रेजिस्टर_led(काष्ठा p54_common *priv,
			    अचिन्हित पूर्णांक led_index,
			    अक्षर *name, स्थिर अक्षर *trigger)
अणु
	काष्ठा p54_led_dev *led = &priv->leds[led_index];
	पूर्णांक err;

	अगर (led->रेजिस्टरed)
		वापस -EEXIST;

	snम_लिखो(led->name, माप(led->name), "p54-%s::%s",
		 wiphy_name(priv->hw->wiphy), name);
	led->hw_dev = priv->hw;
	led->index = led_index;
	led->led_dev.name = led->name;
	led->led_dev.शेष_trigger = trigger;
	led->led_dev.brightness_set = p54_led_brightness_set;

	err = led_classdev_रेजिस्टर(wiphy_dev(priv->hw->wiphy), &led->led_dev);
	अगर (err)
		wiphy_err(priv->hw->wiphy,
			  "Failed to register %s LED.\n", name);
	अन्यथा
		led->रेजिस्टरed = 1;

	वापस err;
पूर्ण

पूर्णांक p54_init_leds(काष्ठा p54_common *priv)
अणु
	पूर्णांक err;

	/*
	 * TODO:
	 * Figure out अगर the EEPROM contains some hपूर्णांकs about the number
	 * of available/programmable LEDs of the device.
	 */

	INIT_DELAYED_WORK(&priv->led_work, p54_update_leds);

	err = p54_रेजिस्टर_led(priv, 0, "assoc",
			       ieee80211_get_assoc_led_name(priv->hw));
	अगर (err)
		वापस err;

	err = p54_रेजिस्टर_led(priv, 1, "tx",
			       ieee80211_get_tx_led_name(priv->hw));
	अगर (err)
		वापस err;

	err = p54_रेजिस्टर_led(priv, 2, "rx",
			       ieee80211_get_rx_led_name(priv->hw));
	अगर (err)
		वापस err;

	err = p54_रेजिस्टर_led(priv, 3, "radio",
			       ieee80211_get_radio_led_name(priv->hw));
	अगर (err)
		वापस err;

	err = p54_set_leds(priv);
	वापस err;
पूर्ण

व्योम p54_unरेजिस्टर_leds(काष्ठा p54_common *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->leds); i++) अणु
		अगर (priv->leds[i].रेजिस्टरed) अणु
			priv->leds[i].रेजिस्टरed = false;
			priv->leds[i].toggled = 0;
			led_classdev_unरेजिस्टर(&priv->leds[i].led_dev);
		पूर्ण
	पूर्ण

	cancel_delayed_work_sync(&priv->led_work);
पूर्ण
