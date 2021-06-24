<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  LED control

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
  Copyright (c) 2005 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (c) 2005-2007 Michael Buesch <m@bues.ch>
  Copyright (c) 2005 Danny van Dyk <kugelfang@gentoo.org>
  Copyright (c) 2005 Andreas Jaggi <andreas.jaggi@waterwave.ch>


*/

#समावेश "b43.h"
#समावेश "leds.h"
#समावेश "rfkill.h"


अटल व्योम b43_led_turn_on(काष्ठा b43_wldev *dev, u8 led_index,
			    bool activelow)
अणु
	u16 ctl;

	ctl = b43_पढ़ो16(dev, B43_MMIO_GPIO_CONTROL);
	अगर (activelow)
		ctl &= ~(1 << led_index);
	अन्यथा
		ctl |= (1 << led_index);
	b43_ग_लिखो16(dev, B43_MMIO_GPIO_CONTROL, ctl);
पूर्ण

अटल व्योम b43_led_turn_off(काष्ठा b43_wldev *dev, u8 led_index,
			     bool activelow)
अणु
	u16 ctl;

	ctl = b43_पढ़ो16(dev, B43_MMIO_GPIO_CONTROL);
	अगर (activelow)
		ctl |= (1 << led_index);
	अन्यथा
		ctl &= ~(1 << led_index);
	b43_ग_लिखो16(dev, B43_MMIO_GPIO_CONTROL, ctl);
पूर्ण

अटल व्योम b43_led_update(काष्ठा b43_wldev *dev,
			   काष्ठा b43_led *led)
अणु
	bool radio_enabled;
	bool turn_on;

	अगर (!led->wl)
		वापस;

	radio_enabled = (dev->phy.radio_on && dev->radio_hw_enable);

	/* The led->state पढ़ो is racy, but we करोn't care. In हाल we raced
	 * with the brightness_set handler, we will be called again soon
	 * to fixup our state. */
	अगर (radio_enabled)
		turn_on = atomic_पढ़ो(&led->state) != LED_OFF;
	अन्यथा
		turn_on = false;
	अगर (turn_on == led->hw_state)
		वापस;
	led->hw_state = turn_on;

	अगर (turn_on)
		b43_led_turn_on(dev, led->index, led->activelow);
	अन्यथा
		b43_led_turn_off(dev, led->index, led->activelow);
पूर्ण

अटल व्योम b43_leds_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43_leds *leds = container_of(work, काष्ठा b43_leds, work);
	काष्ठा b43_wl *wl = container_of(leds, काष्ठा b43_wl, leds);
	काष्ठा b43_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	अगर (unlikely(!dev || b43_status(dev) < B43_STAT_STARTED))
		जाओ out_unlock;

	b43_led_update(dev, &wl->leds.led_tx);
	b43_led_update(dev, &wl->leds.led_rx);
	b43_led_update(dev, &wl->leds.led_radio);
	b43_led_update(dev, &wl->leds.led_assoc);

out_unlock:
	mutex_unlock(&wl->mutex);
पूर्ण

/* Callback from the LED subप्रणाली. */
अटल व्योम b43_led_brightness_set(काष्ठा led_classdev *led_dev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा b43_led *led = container_of(led_dev, काष्ठा b43_led, led_dev);
	काष्ठा b43_wl *wl = led->wl;

	अगर (likely(!wl->leds.stop)) अणु
		atomic_set(&led->state, brightness);
		ieee80211_queue_work(wl->hw, &wl->leds.work);
	पूर्ण
पूर्ण

अटल पूर्णांक b43_रेजिस्टर_led(काष्ठा b43_wldev *dev, काष्ठा b43_led *led,
			    स्थिर अक्षर *name, स्थिर अक्षर *शेष_trigger,
			    u8 led_index, bool activelow)
अणु
	पूर्णांक err;

	अगर (led->wl)
		वापस -EEXIST;
	अगर (!शेष_trigger)
		वापस -EINVAL;
	led->wl = dev->wl;
	led->index = led_index;
	led->activelow = activelow;
	strlcpy(led->name, name, माप(led->name));
	atomic_set(&led->state, 0);

	led->led_dev.name = led->name;
	led->led_dev.शेष_trigger = शेष_trigger;
	led->led_dev.brightness_set = b43_led_brightness_set;

	err = led_classdev_रेजिस्टर(dev->dev->dev, &led->led_dev);
	अगर (err) अणु
		b43warn(dev->wl, "LEDs: Failed to register %s\n", name);
		led->wl = शून्य;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम b43_unरेजिस्टर_led(काष्ठा b43_led *led)
अणु
	अगर (!led->wl)
		वापस;
	led_classdev_unरेजिस्टर(&led->led_dev);
	led->wl = शून्य;
पूर्ण

अटल व्योम b43_map_led(काष्ठा b43_wldev *dev,
			u8 led_index,
			क्रमागत b43_led_behaviour behaviour,
			bool activelow)
अणु
	काष्ठा ieee80211_hw *hw = dev->wl->hw;
	अक्षर name[B43_LED_MAX_NAME_LEN + 1];

	/* Map the b43 specअगरic LED behaviour value to the
	 * generic LED triggers. */
	चयन (behaviour) अणु
	हाल B43_LED_INACTIVE:
	हाल B43_LED_OFF:
	हाल B43_LED_ON:
		अवरोध;
	हाल B43_LED_ACTIVITY:
	हाल B43_LED_TRANSFER:
	हाल B43_LED_APTRANSFER:
		snम_लिखो(name, माप(name),
			 "b43-%s::tx", wiphy_name(hw->wiphy));
		b43_रेजिस्टर_led(dev, &dev->wl->leds.led_tx, name,
				 ieee80211_get_tx_led_name(hw),
				 led_index, activelow);
		snम_लिखो(name, माप(name),
			 "b43-%s::rx", wiphy_name(hw->wiphy));
		b43_रेजिस्टर_led(dev, &dev->wl->leds.led_rx, name,
				 ieee80211_get_rx_led_name(hw),
				 led_index, activelow);
		अवरोध;
	हाल B43_LED_RADIO_ALL:
	हाल B43_LED_RADIO_A:
	हाल B43_LED_RADIO_B:
	हाल B43_LED_MODE_BG:
		snम_लिखो(name, माप(name),
			 "b43-%s::radio", wiphy_name(hw->wiphy));
		b43_रेजिस्टर_led(dev, &dev->wl->leds.led_radio, name,
				 ieee80211_get_radio_led_name(hw),
				 led_index, activelow);
		अवरोध;
	हाल B43_LED_WEIRD:
	हाल B43_LED_ASSOC:
		snम_लिखो(name, माप(name),
			 "b43-%s::assoc", wiphy_name(hw->wiphy));
		b43_रेजिस्टर_led(dev, &dev->wl->leds.led_assoc, name,
				 ieee80211_get_assoc_led_name(hw),
				 led_index, activelow);
		अवरोध;
	शेष:
		b43warn(dev->wl, "LEDs: Unknown behaviour 0x%02X\n",
			behaviour);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम b43_led_get_sprominfo(काष्ठा b43_wldev *dev,
				  अचिन्हित पूर्णांक led_index,
				  क्रमागत b43_led_behaviour *behaviour,
				  bool *activelow)
अणु
	u8 sprom[4];

	sprom[0] = dev->dev->bus_sprom->gpio0;
	sprom[1] = dev->dev->bus_sprom->gpio1;
	sprom[2] = dev->dev->bus_sprom->gpio2;
	sprom[3] = dev->dev->bus_sprom->gpio3;

	अगर ((sprom[0] & sprom[1] & sprom[2] & sprom[3]) == 0xff) अणु
		/* There is no LED inक्रमmation in the SPROM
		 * क्रम this LED. Hardcode it here. */
		*activelow = false;
		चयन (led_index) अणु
		हाल 0:
			*behaviour = B43_LED_ACTIVITY;
			*activelow = true;
			अगर (dev->dev->board_venकरोr == PCI_VENDOR_ID_COMPAQ)
				*behaviour = B43_LED_RADIO_ALL;
			अवरोध;
		हाल 1:
			*behaviour = B43_LED_RADIO_B;
			अगर (dev->dev->board_venकरोr == PCI_VENDOR_ID_ASUSTEK)
				*behaviour = B43_LED_ASSOC;
			अवरोध;
		हाल 2:
			*behaviour = B43_LED_RADIO_A;
			अवरोध;
		हाल 3:
			*behaviour = B43_LED_OFF;
			अवरोध;
		शेष:
			*behaviour = B43_LED_OFF;
			B43_WARN_ON(1);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* keep LED disabled अगर no mapping is defined */
		अगर (sprom[led_index] == 0xff)
			*behaviour = B43_LED_OFF;
		अन्यथा
			*behaviour = sprom[led_index] & B43_LED_BEHAVIOUR;
		*activelow = !!(sprom[led_index] & B43_LED_ACTIVELOW);
	पूर्ण
पूर्ण

व्योम b43_leds_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_led *led;
	अचिन्हित पूर्णांक i;
	क्रमागत b43_led_behaviour behaviour;
	bool activelow;

	/* Sync the RF-समाप्त LED state (अगर we have one) with radio and चयन states. */
	led = &dev->wl->leds.led_radio;
	अगर (led->wl) अणु
		अगर (dev->phy.radio_on && b43_is_hw_radio_enabled(dev)) अणु
			b43_led_turn_on(dev, led->index, led->activelow);
			led->hw_state = true;
			atomic_set(&led->state, 1);
		पूर्ण अन्यथा अणु
			b43_led_turn_off(dev, led->index, led->activelow);
			led->hw_state = false;
			atomic_set(&led->state, 0);
		पूर्ण
	पूर्ण

	/* Initialize TX/RX/ASSOC leds */
	led = &dev->wl->leds.led_tx;
	अगर (led->wl) अणु
		b43_led_turn_off(dev, led->index, led->activelow);
		led->hw_state = false;
		atomic_set(&led->state, 0);
	पूर्ण
	led = &dev->wl->leds.led_rx;
	अगर (led->wl) अणु
		b43_led_turn_off(dev, led->index, led->activelow);
		led->hw_state = false;
		atomic_set(&led->state, 0);
	पूर्ण
	led = &dev->wl->leds.led_assoc;
	अगर (led->wl) अणु
		b43_led_turn_off(dev, led->index, led->activelow);
		led->hw_state = false;
		atomic_set(&led->state, 0);
	पूर्ण

	/* Initialize other LED states. */
	क्रम (i = 0; i < B43_MAX_NR_LEDS; i++) अणु
		b43_led_get_sprominfo(dev, i, &behaviour, &activelow);
		चयन (behaviour) अणु
		हाल B43_LED_OFF:
			b43_led_turn_off(dev, i, activelow);
			अवरोध;
		हाल B43_LED_ON:
			b43_led_turn_on(dev, i, activelow);
			अवरोध;
		शेष:
			/* Leave others as-is. */
			अवरोध;
		पूर्ण
	पूर्ण

	dev->wl->leds.stop = 0;
पूर्ण

व्योम b43_leds_निकास(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_leds *leds = &dev->wl->leds;

	b43_led_turn_off(dev, leds->led_tx.index, leds->led_tx.activelow);
	b43_led_turn_off(dev, leds->led_rx.index, leds->led_rx.activelow);
	b43_led_turn_off(dev, leds->led_assoc.index, leds->led_assoc.activelow);
	b43_led_turn_off(dev, leds->led_radio.index, leds->led_radio.activelow);
पूर्ण

व्योम b43_leds_stop(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_leds *leds = &dev->wl->leds;

	leds->stop = 1;
	cancel_work_sync(&leds->work);
पूर्ण

व्योम b43_leds_रेजिस्टर(काष्ठा b43_wldev *dev)
अणु
	अचिन्हित पूर्णांक i;
	क्रमागत b43_led_behaviour behaviour;
	bool activelow;

	INIT_WORK(&dev->wl->leds.work, b43_leds_work);

	/* Register the LEDs to the LED subप्रणाली. */
	क्रम (i = 0; i < B43_MAX_NR_LEDS; i++) अणु
		b43_led_get_sprominfo(dev, i, &behaviour, &activelow);
		b43_map_led(dev, i, behaviour, activelow);
	पूर्ण
पूर्ण

व्योम b43_leds_unरेजिस्टर(काष्ठा b43_wl *wl)
अणु
	काष्ठा b43_leds *leds = &wl->leds;

	b43_unरेजिस्टर_led(&leds->led_tx);
	b43_unरेजिस्टर_led(&leds->led_rx);
	b43_unरेजिस्टर_led(&leds->led_assoc);
	b43_unरेजिस्टर_led(&leds->led_radio);
पूर्ण
