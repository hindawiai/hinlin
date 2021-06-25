<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: channel.c
 *
 * Purpose: Channel number mapping
 *
 * Author: Lucas Lin
 *
 * Date: Dec 24, 2004
 *
 *
 *
 * Revision History:
 *	01-18-2005	RobertYu:	हटाओ the क्रम loop searching in
 *					ChannelValid, change ChannelRuleTab
 *					to lookup-type, reorder table items.
 *
 *
 */

#समावेश "device.h"
#समावेश "channel.h"
#समावेश "rf.h"

अटल काष्ठा ieee80211_rate vnt_rates_bg[] = अणु
	अणु .bitrate = 10,  .hw_value = RATE_1M पूर्ण,
	अणु .bitrate = 20,  .hw_value = RATE_2M पूर्ण,
	अणु .bitrate = 55,  .hw_value = RATE_5M पूर्ण,
	अणु .bitrate = 110, .hw_value = RATE_11M पूर्ण,
	अणु .bitrate = 60,  .hw_value = RATE_6M पूर्ण,
	अणु .bitrate = 90,  .hw_value = RATE_9M पूर्ण,
	अणु .bitrate = 120, .hw_value = RATE_12M पूर्ण,
	अणु .bitrate = 180, .hw_value = RATE_18M पूर्ण,
	अणु .bitrate = 240, .hw_value = RATE_24M पूर्ण,
	अणु .bitrate = 360, .hw_value = RATE_36M पूर्ण,
	अणु .bitrate = 480, .hw_value = RATE_48M पूर्ण,
	अणु .bitrate = 540, .hw_value = RATE_54M पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_rate vnt_rates_a[] = अणु
	अणु .bitrate = 60,  .hw_value = RATE_6M पूर्ण,
	अणु .bitrate = 90,  .hw_value = RATE_9M पूर्ण,
	अणु .bitrate = 120, .hw_value = RATE_12M पूर्ण,
	अणु .bitrate = 180, .hw_value = RATE_18M पूर्ण,
	अणु .bitrate = 240, .hw_value = RATE_24M पूर्ण,
	अणु .bitrate = 360, .hw_value = RATE_36M पूर्ण,
	अणु .bitrate = 480, .hw_value = RATE_48M पूर्ण,
	अणु .bitrate = 540, .hw_value = RATE_54M पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_channel vnt_channels_2ghz[] = अणु
	अणु .center_freq = 2412, .hw_value = 1 पूर्ण,
	अणु .center_freq = 2417, .hw_value = 2 पूर्ण,
	अणु .center_freq = 2422, .hw_value = 3 पूर्ण,
	अणु .center_freq = 2427, .hw_value = 4 पूर्ण,
	अणु .center_freq = 2432, .hw_value = 5 पूर्ण,
	अणु .center_freq = 2437, .hw_value = 6 पूर्ण,
	अणु .center_freq = 2442, .hw_value = 7 पूर्ण,
	अणु .center_freq = 2447, .hw_value = 8 पूर्ण,
	अणु .center_freq = 2452, .hw_value = 9 पूर्ण,
	अणु .center_freq = 2457, .hw_value = 10 पूर्ण,
	अणु .center_freq = 2462, .hw_value = 11 पूर्ण,
	अणु .center_freq = 2467, .hw_value = 12 पूर्ण,
	अणु .center_freq = 2472, .hw_value = 13 पूर्ण,
	अणु .center_freq = 2484, .hw_value = 14 पूर्ण
पूर्ण;

अटल काष्ठा ieee80211_channel vnt_channels_5ghz[] = अणु
	अणु .center_freq = 4915, .hw_value = 15 पूर्ण,
	अणु .center_freq = 4920, .hw_value = 16 पूर्ण,
	अणु .center_freq = 4925, .hw_value = 17 पूर्ण,
	अणु .center_freq = 4935, .hw_value = 18 पूर्ण,
	अणु .center_freq = 4940, .hw_value = 19 पूर्ण,
	अणु .center_freq = 4945, .hw_value = 20 पूर्ण,
	अणु .center_freq = 4960, .hw_value = 21 पूर्ण,
	अणु .center_freq = 4980, .hw_value = 22 पूर्ण,
	अणु .center_freq = 5035, .hw_value = 23 पूर्ण,
	अणु .center_freq = 5040, .hw_value = 24 पूर्ण,
	अणु .center_freq = 5045, .hw_value = 25 पूर्ण,
	अणु .center_freq = 5055, .hw_value = 26 पूर्ण,
	अणु .center_freq = 5060, .hw_value = 27 पूर्ण,
	अणु .center_freq = 5080, .hw_value = 28 पूर्ण,
	अणु .center_freq = 5170, .hw_value = 29 पूर्ण,
	अणु .center_freq = 5180, .hw_value = 30 पूर्ण,
	अणु .center_freq = 5190, .hw_value = 31 पूर्ण,
	अणु .center_freq = 5200, .hw_value = 32 पूर्ण,
	अणु .center_freq = 5210, .hw_value = 33 पूर्ण,
	अणु .center_freq = 5220, .hw_value = 34 पूर्ण,
	अणु .center_freq = 5230, .hw_value = 35 पूर्ण,
	अणु .center_freq = 5240, .hw_value = 36 पूर्ण,
	अणु .center_freq = 5260, .hw_value = 37 पूर्ण,
	अणु .center_freq = 5280, .hw_value = 38 पूर्ण,
	अणु .center_freq = 5300, .hw_value = 39 पूर्ण,
	अणु .center_freq = 5320, .hw_value = 40 पूर्ण,
	अणु .center_freq = 5500, .hw_value = 41 पूर्ण,
	अणु .center_freq = 5520, .hw_value = 42 पूर्ण,
	अणु .center_freq = 5540, .hw_value = 43 पूर्ण,
	अणु .center_freq = 5560, .hw_value = 44 पूर्ण,
	अणु .center_freq = 5580, .hw_value = 45 पूर्ण,
	अणु .center_freq = 5600, .hw_value = 46 पूर्ण,
	अणु .center_freq = 5620, .hw_value = 47 पूर्ण,
	अणु .center_freq = 5640, .hw_value = 48 पूर्ण,
	अणु .center_freq = 5660, .hw_value = 49 पूर्ण,
	अणु .center_freq = 5680, .hw_value = 50 पूर्ण,
	अणु .center_freq = 5700, .hw_value = 51 पूर्ण,
	अणु .center_freq = 5745, .hw_value = 52 पूर्ण,
	अणु .center_freq = 5765, .hw_value = 53 पूर्ण,
	अणु .center_freq = 5785, .hw_value = 54 पूर्ण,
	अणु .center_freq = 5805, .hw_value = 55 पूर्ण,
	अणु .center_freq = 5825, .hw_value = 56 पूर्ण
पूर्ण;

अटल काष्ठा ieee80211_supported_band vnt_supported_2ghz_band = अणु
	.channels = vnt_channels_2ghz,
	.n_channels = ARRAY_SIZE(vnt_channels_2ghz),
	.bitrates = vnt_rates_bg,
	.n_bitrates = ARRAY_SIZE(vnt_rates_bg),
पूर्ण;

अटल काष्ठा ieee80211_supported_band vnt_supported_5ghz_band = अणु
	.channels = vnt_channels_5ghz,
	.n_channels = ARRAY_SIZE(vnt_channels_5ghz),
	.bitrates = vnt_rates_a,
	.n_bitrates = ARRAY_SIZE(vnt_rates_a),
पूर्ण;

व्योम vnt_init_bands(काष्ठा vnt_निजी *priv)
अणु
	काष्ठा ieee80211_channel *ch;
	पूर्णांक i;

	चयन (priv->rf_type) अणु
	हाल RF_AIROHA7230:
	हाल RF_VT3342A0:
	शेष:
		ch = vnt_channels_5ghz;

		क्रम (i = 0; i < ARRAY_SIZE(vnt_channels_5ghz); i++) अणु
			ch[i].max_घातer = VNT_RF_MAX_POWER;
			ch[i].flags = IEEE80211_CHAN_NO_HT40;
		पूर्ण

		priv->hw->wiphy->bands[NL80211_BAND_5GHZ] =
						&vnt_supported_5ghz_band;
		fallthrough;
	हाल RF_AL2230:
	हाल RF_AL2230S:
	हाल RF_VT3226:
	हाल RF_VT3226D0:
		ch = vnt_channels_2ghz;

		क्रम (i = 0; i < ARRAY_SIZE(vnt_channels_2ghz); i++) अणु
			ch[i].max_घातer = VNT_RF_MAX_POWER;
			ch[i].flags = IEEE80211_CHAN_NO_HT40;
		पूर्ण

		priv->hw->wiphy->bands[NL80211_BAND_2GHZ] =
						&vnt_supported_2ghz_band;
		अवरोध;
	पूर्ण
पूर्ण
