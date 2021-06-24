<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2006, Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/leds.h>
#समावेश "ieee80211_i.h"

#घोषणा MAC80211_BLINK_DELAY 50 /* ms */

अटल अंतरभूत व्योम ieee80211_led_rx(काष्ठा ieee80211_local *local)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	अचिन्हित दीर्घ led_delay = MAC80211_BLINK_DELAY;

	अगर (!atomic_पढ़ो(&local->rx_led_active))
		वापस;
	led_trigger_blink_oneshot(&local->rx_led, &led_delay, &led_delay, 0);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ieee80211_led_tx(काष्ठा ieee80211_local *local)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	अचिन्हित दीर्घ led_delay = MAC80211_BLINK_DELAY;

	अगर (!atomic_पढ़ो(&local->tx_led_active))
		वापस;
	led_trigger_blink_oneshot(&local->tx_led, &led_delay, &led_delay, 0);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_MAC80211_LEDS
व्योम ieee80211_led_assoc(काष्ठा ieee80211_local *local,
			 bool associated);
व्योम ieee80211_led_radio(काष्ठा ieee80211_local *local,
			 bool enabled);
व्योम ieee80211_alloc_led_names(काष्ठा ieee80211_local *local);
व्योम ieee80211_मुक्त_led_names(काष्ठा ieee80211_local *local);
व्योम ieee80211_led_init(काष्ठा ieee80211_local *local);
व्योम ieee80211_led_निकास(काष्ठा ieee80211_local *local);
व्योम ieee80211_mod_tpt_led_trig(काष्ठा ieee80211_local *local,
				अचिन्हित पूर्णांक types_on, अचिन्हित पूर्णांक types_off);
#अन्यथा
अटल अंतरभूत व्योम ieee80211_led_assoc(काष्ठा ieee80211_local *local,
				       bool associated)
अणु
पूर्ण
अटल अंतरभूत व्योम ieee80211_led_radio(काष्ठा ieee80211_local *local,
				       bool enabled)
अणु
पूर्ण
अटल अंतरभूत व्योम ieee80211_alloc_led_names(काष्ठा ieee80211_local *local)
अणु
पूर्ण
अटल अंतरभूत व्योम ieee80211_मुक्त_led_names(काष्ठा ieee80211_local *local)
अणु
पूर्ण
अटल अंतरभूत व्योम ieee80211_led_init(काष्ठा ieee80211_local *local)
अणु
पूर्ण
अटल अंतरभूत व्योम ieee80211_led_निकास(काष्ठा ieee80211_local *local)
अणु
पूर्ण
अटल अंतरभूत व्योम ieee80211_mod_tpt_led_trig(काष्ठा ieee80211_local *local,
					      अचिन्हित पूर्णांक types_on,
					      अचिन्हित पूर्णांक types_off)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम
ieee80211_tpt_led_trig_tx(काष्ठा ieee80211_local *local, __le16 fc, पूर्णांक bytes)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	अगर (ieee80211_is_data(fc) && atomic_पढ़ो(&local->tpt_led_active))
		local->tpt_led_trigger->tx_bytes += bytes;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम
ieee80211_tpt_led_trig_rx(काष्ठा ieee80211_local *local, __le16 fc, पूर्णांक bytes)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	अगर (ieee80211_is_data(fc) && atomic_पढ़ो(&local->tpt_led_active))
		local->tpt_led_trigger->rx_bytes += bytes;
#पूर्ण_अगर
पूर्ण
