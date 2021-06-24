<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * S1G handling
 * Copyright(c) 2020 Adapt-IP
 */
#समावेश <linux/ieee80211.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"

व्योम ieee80211_s1g_sta_rate_init(काष्ठा sta_info *sta)
अणु
	/* aव्योम indicating legacy bitrates क्रम S1G STAs */
	sta->tx_stats.last_rate.flags |= IEEE80211_TX_RC_S1G_MCS;
	sta->rx_stats.last_rate =
			STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_S1G);
पूर्ण
