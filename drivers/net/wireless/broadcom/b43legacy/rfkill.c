<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  RFKILL support

  Copyright (c) 2007 Michael Buesch <m@bues.ch>


*/

#समावेश "radio.h"
#समावेश "b43legacy.h"


/* Returns TRUE, अगर the radio is enabled in hardware. */
bool b43legacy_is_hw_radio_enabled(काष्ठा b43legacy_wldev *dev)
अणु
	अगर (dev->dev->id.revision >= 3) अणु
		अगर (!(b43legacy_पढ़ो32(dev, B43legacy_MMIO_RADIO_HWENABLED_HI)
		      & B43legacy_MMIO_RADIO_HWENABLED_HI_MASK))
			वापस true;
	पूर्ण अन्यथा अणु
		/* To prevent CPU fault on PPC, करो not पढ़ो a रेजिस्टर
		 * unless the पूर्णांकerface is started; however, on resume
		 * क्रम hibernation, this routine is entered early. When
		 * that happens, unconditionally वापस TRUE.
		 */
		अगर (b43legacy_status(dev) < B43legacy_STAT_STARTED)
			वापस true;
		अगर (b43legacy_पढ़ो16(dev, B43legacy_MMIO_RADIO_HWENABLED_LO)
		    & B43legacy_MMIO_RADIO_HWENABLED_LO_MASK)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* The poll callback क्रम the hardware button. */
व्योम b43legacy_rfसमाप्त_poll(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	काष्ठा b43legacy_wldev *dev = wl->current_dev;
	काष्ठा ssb_bus *bus = dev->dev->bus;
	bool enabled;
	bool brought_up = false;

	mutex_lock(&wl->mutex);
	अगर (unlikely(b43legacy_status(dev) < B43legacy_STAT_INITIALIZED)) अणु
		अगर (ssb_bus_घातerup(bus, 0)) अणु
			mutex_unlock(&wl->mutex);
			वापस;
		पूर्ण
		ssb_device_enable(dev->dev, 0);
		brought_up = true;
	पूर्ण

	enabled = b43legacy_is_hw_radio_enabled(dev);

	अगर (unlikely(enabled != dev->radio_hw_enable)) अणु
		dev->radio_hw_enable = enabled;
		b43legacyinfo(wl, "Radio hardware status changed to %s\n",
			enabled ? "ENABLED" : "DISABLED");
		wiphy_rfसमाप्त_set_hw_state(hw->wiphy, !enabled);
		अगर (enabled != dev->phy.radio_on) अणु
			अगर (enabled)
				b43legacy_radio_turn_on(dev);
			अन्यथा
				b43legacy_radio_turn_off(dev, 0);
		पूर्ण
	पूर्ण

	अगर (brought_up) अणु
		ssb_device_disable(dev->dev, 0);
		ssb_bus_may_घातerकरोwn(bus);
	पूर्ण

	mutex_unlock(&wl->mutex);
पूर्ण
