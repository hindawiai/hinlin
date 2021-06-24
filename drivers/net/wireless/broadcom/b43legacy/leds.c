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

#समावेश "b43legacy.h"
#समावेश "leds.h"
#समावेश "rfkill.h"


अटल व्योम b43legacy_led_turn_on(काष्ठा b43legacy_wldev *dev, u8 led_index,
			    bool activelow)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;
	अचिन्हित दीर्घ flags;
	u16 ctl;

	spin_lock_irqsave(&wl->leds_lock, flags);
	ctl = b43legacy_पढ़ो16(dev, B43legacy_MMIO_GPIO_CONTROL);
	अगर (activelow)
		ctl &= ~(1 << led_index);
	अन्यथा
		ctl |= (1 << led_index);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_GPIO_CONTROL, ctl);
	spin_unlock_irqrestore(&wl->leds_lock, flags);
पूर्ण

अटल व्योम b43legacy_led_turn_off(काष्ठा b43legacy_wldev *dev, u8 led_index,
			     bool activelow)
अणु
	काष्ठा b43legacy_wl *wl = dev->wl;
	अचिन्हित दीर्घ flags;
	u16 ctl;

	spin_lock_irqsave(&wl->leds_lock, flags);
	ctl = b43legacy_पढ़ो16(dev, B43legacy_MMIO_GPIO_CONTROL);
	अगर (activelow)
		ctl |= (1 << led_index);
	अन्यथा
		ctl &= ~(1 << led_index);
	b43legacy_ग_लिखो16(dev, B43legacy_MMIO_GPIO_CONTROL, ctl);
	spin_unlock_irqrestore(&wl->leds_lock, flags);
पूर्ण

/* Callback from the LED subप्रणाली. */
अटल व्योम b43legacy_led_brightness_set(काष्ठा led_classdev *led_dev,
				   क्रमागत led_brightness brightness)
अणु
	काष्ठा b43legacy_led *led = container_of(led_dev, काष्ठा b43legacy_led,
				    led_dev);
	काष्ठा b43legacy_wldev *dev = led->dev;
	bool radio_enabled;

	/* Checking the radio-enabled status here is slightly racy,
	 * but we want to aव्योम the locking overhead and we करोn't care
	 * whether the LED has the wrong state क्रम a second. */
	radio_enabled = (dev->phy.radio_on && dev->radio_hw_enable);

	अगर (brightness == LED_OFF || !radio_enabled)
		b43legacy_led_turn_off(dev, led->index, led->activelow);
	अन्यथा
		b43legacy_led_turn_on(dev, led->index, led->activelow);
पूर्ण

अटल पूर्णांक b43legacy_रेजिस्टर_led(काष्ठा b43legacy_wldev *dev,
				  काष्ठा b43legacy_led *led,
				  स्थिर अक्षर *name,
				  स्थिर अक्षर *शेष_trigger,
				  u8 led_index, bool activelow)
अणु
	पूर्णांक err;

	b43legacy_led_turn_off(dev, led_index, activelow);
	अगर (led->dev)
		वापस -EEXIST;
	अगर (!शेष_trigger)
		वापस -EINVAL;
	led->dev = dev;
	led->index = led_index;
	led->activelow = activelow;
	strlcpy(led->name, name, माप(led->name));

	led->led_dev.name = led->name;
	led->led_dev.शेष_trigger = शेष_trigger;
	led->led_dev.brightness_set = b43legacy_led_brightness_set;

	err = led_classdev_रेजिस्टर(dev->dev->dev, &led->led_dev);
	अगर (err) अणु
		b43legacywarn(dev->wl, "LEDs: Failed to register %s\n", name);
		led->dev = शून्य;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम b43legacy_unरेजिस्टर_led(काष्ठा b43legacy_led *led)
अणु
	अगर (!led->dev)
		वापस;
	led_classdev_unरेजिस्टर(&led->led_dev);
	b43legacy_led_turn_off(led->dev, led->index, led->activelow);
	led->dev = शून्य;
पूर्ण

अटल व्योम b43legacy_map_led(काष्ठा b43legacy_wldev *dev,
			u8 led_index,
			क्रमागत b43legacy_led_behaviour behaviour,
			bool activelow)
अणु
	काष्ठा ieee80211_hw *hw = dev->wl->hw;
	अक्षर name[B43legacy_LED_MAX_NAME_LEN + 1];

	/* Map the b43 specअगरic LED behaviour value to the
	 * generic LED triggers. */
	चयन (behaviour) अणु
	हाल B43legacy_LED_INACTIVE:
		अवरोध;
	हाल B43legacy_LED_OFF:
		b43legacy_led_turn_off(dev, led_index, activelow);
		अवरोध;
	हाल B43legacy_LED_ON:
		b43legacy_led_turn_on(dev, led_index, activelow);
		अवरोध;
	हाल B43legacy_LED_ACTIVITY:
	हाल B43legacy_LED_TRANSFER:
	हाल B43legacy_LED_APTRANSFER:
		snम_लिखो(name, माप(name),
			 "b43legacy-%s::tx", wiphy_name(hw->wiphy));
		b43legacy_रेजिस्टर_led(dev, &dev->led_tx, name,
				 ieee80211_get_tx_led_name(hw),
				 led_index, activelow);
		snम_लिखो(name, माप(name),
			 "b43legacy-%s::rx", wiphy_name(hw->wiphy));
		b43legacy_रेजिस्टर_led(dev, &dev->led_rx, name,
				 ieee80211_get_rx_led_name(hw),
				 led_index, activelow);
		अवरोध;
	हाल B43legacy_LED_RADIO_ALL:
	हाल B43legacy_LED_RADIO_A:
	हाल B43legacy_LED_RADIO_B:
	हाल B43legacy_LED_MODE_BG:
		snम_लिखो(name, माप(name),
			 "b43legacy-%s::radio", wiphy_name(hw->wiphy));
		b43legacy_रेजिस्टर_led(dev, &dev->led_radio, name,
				 ieee80211_get_radio_led_name(hw),
				 led_index, activelow);
		/* Sync the RF-समाप्त LED state with radio and चयन states. */
		अगर (dev->phy.radio_on && b43legacy_is_hw_radio_enabled(dev))
			b43legacy_led_turn_on(dev, led_index, activelow);
		अवरोध;
	हाल B43legacy_LED_WEIRD:
	हाल B43legacy_LED_ASSOC:
		snम_लिखो(name, माप(name),
			 "b43legacy-%s::assoc", wiphy_name(hw->wiphy));
		b43legacy_रेजिस्टर_led(dev, &dev->led_assoc, name,
				 ieee80211_get_assoc_led_name(hw),
				 led_index, activelow);
		अवरोध;
	शेष:
		b43legacywarn(dev->wl, "LEDs: Unknown behaviour 0x%02X\n",
			behaviour);
		अवरोध;
	पूर्ण
पूर्ण

व्योम b43legacy_leds_init(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा ssb_bus *bus = dev->dev->bus;
	u8 sprom[4];
	पूर्णांक i;
	क्रमागत b43legacy_led_behaviour behaviour;
	bool activelow;

	sprom[0] = bus->sprom.gpio0;
	sprom[1] = bus->sprom.gpio1;
	sprom[2] = bus->sprom.gpio2;
	sprom[3] = bus->sprom.gpio3;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (sprom[i] == 0xFF) अणु
			/* There is no LED inक्रमmation in the SPROM
			 * क्रम this LED. Hardcode it here. */
			activelow = false;
			चयन (i) अणु
			हाल 0:
				behaviour = B43legacy_LED_ACTIVITY;
				activelow = true;
				अगर (bus->boardinfo.venकरोr == PCI_VENDOR_ID_COMPAQ)
					behaviour = B43legacy_LED_RADIO_ALL;
				अवरोध;
			हाल 1:
				behaviour = B43legacy_LED_RADIO_B;
				अगर (bus->boardinfo.venकरोr == PCI_VENDOR_ID_ASUSTEK)
					behaviour = B43legacy_LED_ASSOC;
				अवरोध;
			हाल 2:
				behaviour = B43legacy_LED_RADIO_A;
				अवरोध;
			हाल 3:
				behaviour = B43legacy_LED_OFF;
				अवरोध;
			शेष:
				B43legacy_WARN_ON(1);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			behaviour = sprom[i] & B43legacy_LED_BEHAVIOUR;
			activelow = !!(sprom[i] & B43legacy_LED_ACTIVELOW);
		पूर्ण
		b43legacy_map_led(dev, i, behaviour, activelow);
	पूर्ण
पूर्ण

व्योम b43legacy_leds_निकास(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_unरेजिस्टर_led(&dev->led_tx);
	b43legacy_unरेजिस्टर_led(&dev->led_rx);
	b43legacy_unरेजिस्टर_led(&dev->led_assoc);
	b43legacy_unरेजिस्टर_led(&dev->led_radio);
पूर्ण
