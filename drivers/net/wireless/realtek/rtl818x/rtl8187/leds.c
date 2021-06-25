<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux LED driver क्रम RTL8187
 *
 * Copyright 2009 Larry Finger <Larry.Finger@lwfinger.net>
 *
 * Based on the LED handling in the r8187 driver, which is:
 * Copyright (c) Realtek Semiconductor Corp. All rights reserved.
 *
 * Thanks to Realtek क्रम their support!
 */

#अगर_घोषित CONFIG_RTL8187_LEDS

#समावेश <net/mac80211.h>
#समावेश <linux/usb.h>
#समावेश <linux/eeprom_93cx6.h>

#समावेश "rtl8187.h"
#समावेश "leds.h"

अटल व्योम led_turn_on(काष्ठा work_काष्ठा *work)
अणु
	/* As this routine करोes पढ़ो/ग_लिखो operations on the hardware, it must
	 * be run from a work queue.
	 */
	u8 reg;
	काष्ठा rtl8187_priv *priv = container_of(work, काष्ठा rtl8187_priv,
				    led_on.work);
	काष्ठा rtl8187_led *led = &priv->led_tx;

	/* Don't change the LED, when the device is करोwn. */
	अगर (!priv->vअगर || priv->vअगर->type == NL80211_IFTYPE_UNSPECIFIED)
		वापस ;

	/* Skip अगर the LED is not रेजिस्टरed. */
	अगर (!led->dev)
		वापस;
	mutex_lock(&priv->conf_mutex);
	चयन (led->ledpin) अणु
	हाल LED_PIN_GPIO0:
		rtl818x_ioग_लिखो8(priv, &priv->map->GPIO0, 0x01);
		rtl818x_ioग_लिखो8(priv, &priv->map->GP_ENABLE, 0x00);
		अवरोध;
	हाल LED_PIN_LED0:
		reg = rtl818x_ioपढ़ो8(priv, &priv->map->PGSELECT) & ~(1 << 4);
		rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg);
		अवरोध;
	हाल LED_PIN_LED1:
		reg = rtl818x_ioपढ़ो8(priv, &priv->map->PGSELECT) & ~(1 << 5);
		rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg);
		अवरोध;
	हाल LED_PIN_HW:
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&priv->conf_mutex);
पूर्ण

अटल व्योम led_turn_off(काष्ठा work_काष्ठा *work)
अणु
	/* As this routine करोes पढ़ो/ग_लिखो operations on the hardware, it must
	 * be run from a work queue.
	 */
	u8 reg;
	काष्ठा rtl8187_priv *priv = container_of(work, काष्ठा rtl8187_priv,
				    led_off.work);
	काष्ठा rtl8187_led *led = &priv->led_tx;

	/* Don't change the LED, when the device is करोwn. */
	अगर (!priv->vअगर || priv->vअगर->type == NL80211_IFTYPE_UNSPECIFIED)
		वापस ;

	/* Skip अगर the LED is not रेजिस्टरed. */
	अगर (!led->dev)
		वापस;
	mutex_lock(&priv->conf_mutex);
	चयन (led->ledpin) अणु
	हाल LED_PIN_GPIO0:
		rtl818x_ioग_लिखो8(priv, &priv->map->GPIO0, 0x01);
		rtl818x_ioग_लिखो8(priv, &priv->map->GP_ENABLE, 0x01);
		अवरोध;
	हाल LED_PIN_LED0:
		reg = rtl818x_ioपढ़ो8(priv, &priv->map->PGSELECT) | (1 << 4);
		rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg);
		अवरोध;
	हाल LED_PIN_LED1:
		reg = rtl818x_ioपढ़ो8(priv, &priv->map->PGSELECT) | (1 << 5);
		rtl818x_ioग_लिखो8(priv, &priv->map->PGSELECT, reg);
		अवरोध;
	हाल LED_PIN_HW:
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&priv->conf_mutex);
पूर्ण

/* Callback from the LED subप्रणाली. */
अटल व्योम rtl8187_led_brightness_set(काष्ठा led_classdev *led_dev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा rtl8187_led *led = container_of(led_dev, काष्ठा rtl8187_led,
					       led_dev);
	काष्ठा ieee80211_hw *hw = led->dev;
	काष्ठा rtl8187_priv *priv;
	अटल bool radio_on;

	अगर (!hw)
		वापस;
	priv = hw->priv;
	अगर (led->is_radio) अणु
		अगर (brightness == LED_FULL) अणु
			ieee80211_queue_delayed_work(hw, &priv->led_on, 0);
			radio_on = true;
		पूर्ण अन्यथा अगर (radio_on) अणु
			radio_on = false;
			cancel_delayed_work(&priv->led_on);
			ieee80211_queue_delayed_work(hw, &priv->led_off, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (radio_on) अणु
		अगर (brightness == LED_OFF) अणु
			ieee80211_queue_delayed_work(hw, &priv->led_off, 0);
			/* The LED is off क्रम 1/20 sec - it just blinks. */
			ieee80211_queue_delayed_work(hw, &priv->led_on,
						     HZ / 20);
		पूर्ण अन्यथा
			ieee80211_queue_delayed_work(hw, &priv->led_on, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक rtl8187_रेजिस्टर_led(काष्ठा ieee80211_hw *dev,
				काष्ठा rtl8187_led *led, स्थिर अक्षर *name,
				स्थिर अक्षर *शेष_trigger, u8 ledpin,
				bool is_radio)
अणु
	पूर्णांक err;
	काष्ठा rtl8187_priv *priv = dev->priv;

	अगर (led->dev)
		वापस -EEXIST;
	अगर (!शेष_trigger)
		वापस -EINVAL;
	led->dev = dev;
	led->ledpin = ledpin;
	led->is_radio = is_radio;
	strlcpy(led->name, name, माप(led->name));

	led->led_dev.name = led->name;
	led->led_dev.शेष_trigger = शेष_trigger;
	led->led_dev.brightness_set = rtl8187_led_brightness_set;

	err = led_classdev_रेजिस्टर(&priv->udev->dev, &led->led_dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_INFO "LEDs: Failed to register %s\n", name);
		led->dev = शून्य;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम rtl8187_unरेजिस्टर_led(काष्ठा rtl8187_led *led)
अणु
	काष्ठा ieee80211_hw *hw = led->dev;
	काष्ठा rtl8187_priv *priv = hw->priv;

	led_classdev_unरेजिस्टर(&led->led_dev);
	flush_delayed_work(&priv->led_off);
	led->dev = शून्य;
पूर्ण

व्योम rtl8187_leds_init(काष्ठा ieee80211_hw *dev, u16 custid)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;
	अक्षर name[RTL8187_LED_MAX_NAME_LEN + 1];
	u8 ledpin;
	पूर्णांक err;

	/* According to the venकरोr driver, the LED operation depends on the
	 * customer ID encoded in the EEPROM
	 */
	prपूर्णांकk(KERN_INFO "rtl8187: Customer ID is 0x%02X\n", custid);
	चयन (custid) अणु
	हाल EEPROM_CID_RSVD0:
	हाल EEPROM_CID_RSVD1:
	हाल EEPROM_CID_SERCOMM_PS:
	हाल EEPROM_CID_QMI:
	हाल EEPROM_CID_DELL:
	हाल EEPROM_CID_TOSHIBA:
		ledpin = LED_PIN_GPIO0;
		अवरोध;
	हाल EEPROM_CID_ALPHA0:
		ledpin = LED_PIN_LED0;
		अवरोध;
	हाल EEPROM_CID_HW:
		ledpin = LED_PIN_HW;
		अवरोध;
	शेष:
		ledpin = LED_PIN_GPIO0;
	पूर्ण

	INIT_DELAYED_WORK(&priv->led_on, led_turn_on);
	INIT_DELAYED_WORK(&priv->led_off, led_turn_off);

	snम_लिखो(name, माप(name),
		 "rtl8187-%s::radio", wiphy_name(dev->wiphy));
	err = rtl8187_रेजिस्टर_led(dev, &priv->led_radio, name,
			 ieee80211_get_radio_led_name(dev), ledpin, true);
	अगर (err)
		वापस;

	snम_लिखो(name, माप(name),
		 "rtl8187-%s::tx", wiphy_name(dev->wiphy));
	err = rtl8187_रेजिस्टर_led(dev, &priv->led_tx, name,
			 ieee80211_get_tx_led_name(dev), ledpin, false);
	अगर (err)
		जाओ err_tx;

	snम_लिखो(name, माप(name),
		 "rtl8187-%s::rx", wiphy_name(dev->wiphy));
	err = rtl8187_रेजिस्टर_led(dev, &priv->led_rx, name,
			 ieee80211_get_rx_led_name(dev), ledpin, false);
	अगर (!err)
		वापस;

	/* registration of RX LED failed - unरेजिस्टर */
	rtl8187_unरेजिस्टर_led(&priv->led_tx);
err_tx:
	rtl8187_unरेजिस्टर_led(&priv->led_radio);
पूर्ण

व्योम rtl8187_leds_निकास(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा rtl8187_priv *priv = dev->priv;

	rtl8187_unरेजिस्टर_led(&priv->led_radio);
	rtl8187_unरेजिस्टर_led(&priv->led_rx);
	rtl8187_unरेजिस्टर_led(&priv->led_tx);
	cancel_delayed_work_sync(&priv->led_off);
	cancel_delayed_work_sync(&priv->led_on);
पूर्ण
#पूर्ण_अगर /* def CONFIG_RTL8187_LEDS */

