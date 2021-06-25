<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  RFKILL support

  Copyright (c) 2007 Michael Buesch <m@bues.ch>


*/

#समावेश "b43.h"


/* Returns TRUE, अगर the radio is enabled in hardware. */
bool b43_is_hw_radio_enabled(काष्ठा b43_wldev *dev)
अणु
	वापस !(b43_पढ़ो32(dev, B43_MMIO_RADIO_HWENABLED_HI)
		& B43_MMIO_RADIO_HWENABLED_HI_MASK);
पूर्ण

/* The poll callback क्रम the hardware button. */
व्योम b43_rfसमाप्त_poll(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा b43_wl *wl = hw_to_b43_wl(hw);
	काष्ठा b43_wldev *dev = wl->current_dev;
	bool enabled;
	bool brought_up = false;

	mutex_lock(&wl->mutex);
	अगर (unlikely(b43_status(dev) < B43_STAT_INITIALIZED)) अणु
		अगर (b43_bus_घातerup(dev, 0)) अणु
			mutex_unlock(&wl->mutex);
			वापस;
		पूर्ण
		b43_device_enable(dev, 0);
		brought_up = true;
	पूर्ण

	enabled = b43_is_hw_radio_enabled(dev);

	अगर (unlikely(enabled != dev->radio_hw_enable)) अणु
		dev->radio_hw_enable = enabled;
		b43info(wl, "Radio hardware status changed to %s\n",
			enabled ? "ENABLED" : "DISABLED");
		wiphy_rfसमाप्त_set_hw_state(hw->wiphy, !enabled);
		अगर (enabled != dev->phy.radio_on)
			b43_software_rfसमाप्त(dev, !enabled);
	पूर्ण

	अगर (brought_up) अणु
		b43_device_disable(dev, 0);
		b43_bus_may_घातerकरोwn(dev);
	पूर्ण

	mutex_unlock(&wl->mutex);
पूर्ण
