<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <net/mac80211.h>
#समावेश <linux/bcma/bcma_driver_chipcommon.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "mac80211_if.h"
#समावेश "pub.h"
#समावेश "main.h"
#समावेश "led.h"

	/* number of leds */
#घोषणा  BRCMS_LED_NO		4
	/* behavior mask */
#घोषणा  BRCMS_LED_BEH_MASK	0x7f
	/* activelow (polarity) bit */
#घोषणा  BRCMS_LED_AL_MASK	0x80
	/* radio enabled */
#घोषणा  BRCMS_LED_RADIO	3

अटल व्योम brcms_radio_led_ctrl(काष्ठा brcms_info *wl, bool state)
अणु
	अगर (!wl->radio_led.gpiod)
		वापस;

	अगर (state)
		gpiod_set_value(wl->radio_led.gpiod, 1);
	अन्यथा
		gpiod_set_value(wl->radio_led.gpiod, 0);
पूर्ण


/* Callback from the LED subप्रणाली. */
अटल व्योम brcms_led_brightness_set(काष्ठा led_classdev *led_dev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा brcms_info *wl = container_of(led_dev,
		काष्ठा brcms_info, led_dev);
	brcms_radio_led_ctrl(wl, brightness);
पूर्ण

व्योम brcms_led_unरेजिस्टर(काष्ठा brcms_info *wl)
अणु
	अगर (wl->led_dev.dev)
		led_classdev_unरेजिस्टर(&wl->led_dev);
	अगर (wl->radio_led.gpiod)
		gpiochip_मुक्त_own_desc(wl->radio_led.gpiod);
पूर्ण

पूर्णांक brcms_led_रेजिस्टर(काष्ठा brcms_info *wl)
अणु
	पूर्णांक i, err;
	काष्ठा brcms_led *radio_led = &wl->radio_led;
	/* get CC core */
	काष्ठा bcma_drv_cc *cc_drv  = &wl->wlc->hw->d11core->bus->drv_cc;
	काष्ठा gpio_chip *bcma_gpio = &cc_drv->gpio;
	काष्ठा ssb_sprom *sprom = &wl->wlc->hw->d11core->bus->sprom;
	u8 *leds[] = अणु &sprom->gpio0,
		&sprom->gpio1,
		&sprom->gpio2,
		&sprom->gpio3 पूर्ण;
	पूर्णांक hwnum = -1;
	क्रमागत gpio_lookup_flags lflags = GPIO_ACTIVE_HIGH;

	अगर (!bcma_gpio || !gpio_is_valid(bcma_gpio->base))
		वापस -ENODEV;

	/* find radio enabled LED */
	क्रम (i = 0; i < BRCMS_LED_NO; i++) अणु
		u8 led = *leds[i];
		अगर ((led & BRCMS_LED_BEH_MASK) == BRCMS_LED_RADIO) अणु
			hwnum = i;
			अगर (led & BRCMS_LED_AL_MASK)
				lflags = GPIO_ACTIVE_LOW;
			अवरोध;
		पूर्ण
	पूर्ण

	/* No LED, bail out */
	अगर (hwnum == -1)
		वापस -ENODEV;

	/* Try to obtain this LED GPIO line */
	radio_led->gpiod = gpiochip_request_own_desc(bcma_gpio, hwnum,
						     "radio on", lflags,
						     GPIOD_OUT_LOW);

	अगर (IS_ERR(radio_led->gpiod)) अणु
		err = PTR_ERR(radio_led->gpiod);
		wiphy_err(wl->wiphy, "requesting led GPIO failed (err: %d)\n",
			  err);
		वापस err;
	पूर्ण

	snम_लिखो(wl->radio_led.name, माप(wl->radio_led.name),
		 "brcmsmac-%s:radio", wiphy_name(wl->wiphy));

	wl->led_dev.name = wl->radio_led.name;
	wl->led_dev.शेष_trigger =
		ieee80211_get_radio_led_name(wl->pub->ieee_hw);
	wl->led_dev.brightness_set = brcms_led_brightness_set;
	err = led_classdev_रेजिस्टर(wiphy_dev(wl->wiphy), &wl->led_dev);

	अगर (err) अणु
		wiphy_err(wl->wiphy, "cannot register led device: %s (err: %d)\n",
			  wl->radio_led.name, err);
		वापस err;
	पूर्ण

	wiphy_info(wl->wiphy, "registered radio enabled led device: %s\n",
		   wl->radio_led.name);

	वापस 0;
पूर्ण
