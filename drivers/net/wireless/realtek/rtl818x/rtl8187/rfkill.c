<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux RFKILL support क्रम RTL8187
 *
 * Copyright (c) 2009 Herton Ronalकरो Krzesinski <herton@mandriva.com.br>
 *
 * Based on the RFKILL handling in the r8187 driver, which is:
 * Copyright (c) Realtek Semiconductor Corp. All rights reserved.
 *
 * Thanks to Realtek क्रम their support!
 */

#समावेश <linux/types.h>
#समावेश <linux/usb.h>
#समावेश <net/mac80211.h>

#समावेश "rtl8187.h"
#समावेश "rfkill.h"

अटल bool rtl8187_is_radio_enabled(काष्ठा rtl8187_priv *priv)
अणु
	u8 gpio;

	gpio = rtl818x_ioपढ़ो8(priv, &priv->map->GPIO0);
	rtl818x_ioग_लिखो8(priv, &priv->map->GPIO0, gpio & ~priv->rfसमाप्त_mask);
	gpio = rtl818x_ioपढ़ो8(priv, &priv->map->GPIO1);

	वापस gpio & priv->rfसमाप्त_mask;
पूर्ण

व्योम rtl8187_rfसमाप्त_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl8187_priv *priv = hw->priv;

	priv->rfसमाप्त_off = rtl8187_is_radio_enabled(priv);
	prपूर्णांकk(KERN_INFO "rtl8187: wireless switch is %s\n",
	       priv->rfसमाप्त_off ? "on" : "off");
	wiphy_rfसमाप्त_set_hw_state(hw->wiphy, !priv->rfसमाप्त_off);
	wiphy_rfसमाप्त_start_polling(hw->wiphy);
पूर्ण

व्योम rtl8187_rfसमाप्त_poll(काष्ठा ieee80211_hw *hw)
अणु
	bool enabled;
	काष्ठा rtl8187_priv *priv = hw->priv;

	mutex_lock(&priv->conf_mutex);
	enabled = rtl8187_is_radio_enabled(priv);
	अगर (unlikely(enabled != priv->rfसमाप्त_off)) अणु
		priv->rfसमाप्त_off = enabled;
		prपूर्णांकk(KERN_INFO "rtl8187: wireless radio switch turned %s\n",
		       enabled ? "on" : "off");
		wiphy_rfसमाप्त_set_hw_state(hw->wiphy, !enabled);
	पूर्ण
	mutex_unlock(&priv->conf_mutex);
पूर्ण

व्योम rtl8187_rfसमाप्त_निकास(काष्ठा ieee80211_hw *hw)
अणु
	wiphy_rfसमाप्त_stop_polling(hw->wiphy);
पूर्ण
