<शैली गुरु>
/*-
 * Copyright (c) 2002-2005 Sam Leffler, Errno Consulting
 * Copyright (c) 2004-2005 Atheros Communications, Inc.
 * Copyright (c) 2006 Devicescape Software, Inc.
 * Copyright (c) 2007 Jiri Slaby <jirislaby@gmail.com>
 * Copyright (c) 2007 Luis R. Rodriguez <mcgrof@winlab.rutgers.edu>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    similar to the "NO WARRANTY" disclaimer below ("Disclaimer") and any
 *    redistribution must be conditioned upon including a substantially
 *    similar Disclaimer requirement क्रम further binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTIBILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/अगर.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/cache.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/nl80211.h>

#समावेश <net/cfg80211.h>
#समावेश <net/ieee80211_radiotap.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <net/mac80211.h>
#समावेश "base.h"
#समावेश "reg.h"
#समावेश "debug.h"
#समावेश "ani.h"
#समावेश "ath5k.h"
#समावेश "../regd.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

bool ath5k_modparam_nohwcrypt;
module_param_named(nohwcrypt, ath5k_modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");

अटल bool modparam_fastchanचयन;
module_param_named(fastchanचयन, modparam_fastchanचयन, bool, 0444);
MODULE_PARM_DESC(fastchanचयन, "Enable fast channel switching for AR2413/AR5413 radios.");

अटल bool ath5k_modparam_no_hw_rfसमाप्त_चयन;
module_param_named(no_hw_rfसमाप्त_चयन, ath5k_modparam_no_hw_rfसमाप्त_चयन,
		   bool, 0444);
MODULE_PARM_DESC(no_hw_rfसमाप्त_चयन, "Ignore the GPIO RFKill switch state");


/* Module info */
MODULE_AUTHOR("Jiri Slaby");
MODULE_AUTHOR("Nick Kossifidis");
MODULE_DESCRIPTION("Support for 5xxx series of Atheros 802.11 wireless LAN cards.");
MODULE_LICENSE("Dual BSD/GPL");

अटल पूर्णांक ath5k_init(काष्ठा ieee80211_hw *hw);
अटल पूर्णांक ath5k_reset(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *chan,
								bool skip_pcu);

/* Known SREVs */
अटल स्थिर काष्ठा ath5k_srev_name srev_names[] = अणु
#अगर_घोषित CONFIG_ATH5K_AHB
	अणु "5312",	AR5K_VERSION_MAC,	AR5K_SREV_AR5312_R2 पूर्ण,
	अणु "5312",	AR5K_VERSION_MAC,	AR5K_SREV_AR5312_R7 पूर्ण,
	अणु "2313",	AR5K_VERSION_MAC,	AR5K_SREV_AR2313_R8 पूर्ण,
	अणु "2315",	AR5K_VERSION_MAC,	AR5K_SREV_AR2315_R6 पूर्ण,
	अणु "2315",	AR5K_VERSION_MAC,	AR5K_SREV_AR2315_R7 पूर्ण,
	अणु "2317",	AR5K_VERSION_MAC,	AR5K_SREV_AR2317_R1 पूर्ण,
	अणु "2317",	AR5K_VERSION_MAC,	AR5K_SREV_AR2317_R2 पूर्ण,
#अन्यथा
	अणु "5210",	AR5K_VERSION_MAC,	AR5K_SREV_AR5210 पूर्ण,
	अणु "5311",	AR5K_VERSION_MAC,	AR5K_SREV_AR5311 पूर्ण,
	अणु "5311A",	AR5K_VERSION_MAC,	AR5K_SREV_AR5311A पूर्ण,
	अणु "5311B",	AR5K_VERSION_MAC,	AR5K_SREV_AR5311B पूर्ण,
	अणु "5211",	AR5K_VERSION_MAC,	AR5K_SREV_AR5211 पूर्ण,
	अणु "5212",	AR5K_VERSION_MAC,	AR5K_SREV_AR5212 पूर्ण,
	अणु "5213",	AR5K_VERSION_MAC,	AR5K_SREV_AR5213 पूर्ण,
	अणु "5213A",	AR5K_VERSION_MAC,	AR5K_SREV_AR5213A पूर्ण,
	अणु "2413",	AR5K_VERSION_MAC,	AR5K_SREV_AR2413 पूर्ण,
	अणु "2414",	AR5K_VERSION_MAC,	AR5K_SREV_AR2414 पूर्ण,
	अणु "5424",	AR5K_VERSION_MAC,	AR5K_SREV_AR5424 पूर्ण,
	अणु "5413",	AR5K_VERSION_MAC,	AR5K_SREV_AR5413 पूर्ण,
	अणु "5414",	AR5K_VERSION_MAC,	AR5K_SREV_AR5414 पूर्ण,
	अणु "2415",	AR5K_VERSION_MAC,	AR5K_SREV_AR2415 पूर्ण,
	अणु "5416",	AR5K_VERSION_MAC,	AR5K_SREV_AR5416 पूर्ण,
	अणु "5418",	AR5K_VERSION_MAC,	AR5K_SREV_AR5418 पूर्ण,
	अणु "2425",	AR5K_VERSION_MAC,	AR5K_SREV_AR2425 पूर्ण,
	अणु "2417",	AR5K_VERSION_MAC,	AR5K_SREV_AR2417 पूर्ण,
#पूर्ण_अगर
	अणु "xxxxx",	AR5K_VERSION_MAC,	AR5K_SREV_UNKNOWN पूर्ण,
	अणु "5110",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5110 पूर्ण,
	अणु "5111",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5111 पूर्ण,
	अणु "5111A",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5111A पूर्ण,
	अणु "2111",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_2111 पूर्ण,
	अणु "5112",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5112 पूर्ण,
	अणु "5112A",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5112A पूर्ण,
	अणु "5112B",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5112B पूर्ण,
	अणु "2112",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_2112 पूर्ण,
	अणु "2112A",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_2112A पूर्ण,
	अणु "2112B",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_2112B पूर्ण,
	अणु "2413",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_2413 पूर्ण,
	अणु "5413",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5413 पूर्ण,
	अणु "5424",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5424 पूर्ण,
	अणु "5133",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_5133 पूर्ण,
#अगर_घोषित CONFIG_ATH5K_AHB
	अणु "2316",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_2316 पूर्ण,
	अणु "2317",	AR5K_VERSION_RAD,	AR5K_SREV_RAD_2317 पूर्ण,
#पूर्ण_अगर
	अणु "xxxxx",	AR5K_VERSION_RAD,	AR5K_SREV_UNKNOWN पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_rate ath5k_rates[] = अणु
	अणु .bitrate = 10,
	  .hw_value = ATH5K_RATE_CODE_1M, पूर्ण,
	अणु .bitrate = 20,
	  .hw_value = ATH5K_RATE_CODE_2M,
	  .hw_value_लघु = ATH5K_RATE_CODE_2M | AR5K_SET_SHORT_PREAMBLE,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55,
	  .hw_value = ATH5K_RATE_CODE_5_5M,
	  .hw_value_लघु = ATH5K_RATE_CODE_5_5M | AR5K_SET_SHORT_PREAMBLE,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110,
	  .hw_value = ATH5K_RATE_CODE_11M,
	  .hw_value_लघु = ATH5K_RATE_CODE_11M | AR5K_SET_SHORT_PREAMBLE,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60,
	  .hw_value = ATH5K_RATE_CODE_6M,
	  .flags = IEEE80211_RATE_SUPPORTS_5MHZ |
		   IEEE80211_RATE_SUPPORTS_10MHZ पूर्ण,
	अणु .bitrate = 90,
	  .hw_value = ATH5K_RATE_CODE_9M,
	  .flags = IEEE80211_RATE_SUPPORTS_5MHZ |
		   IEEE80211_RATE_SUPPORTS_10MHZ पूर्ण,
	अणु .bitrate = 120,
	  .hw_value = ATH5K_RATE_CODE_12M,
	  .flags = IEEE80211_RATE_SUPPORTS_5MHZ |
		   IEEE80211_RATE_SUPPORTS_10MHZ पूर्ण,
	अणु .bitrate = 180,
	  .hw_value = ATH5K_RATE_CODE_18M,
	  .flags = IEEE80211_RATE_SUPPORTS_5MHZ |
		   IEEE80211_RATE_SUPPORTS_10MHZ पूर्ण,
	अणु .bitrate = 240,
	  .hw_value = ATH5K_RATE_CODE_24M,
	  .flags = IEEE80211_RATE_SUPPORTS_5MHZ |
		   IEEE80211_RATE_SUPPORTS_10MHZ पूर्ण,
	अणु .bitrate = 360,
	  .hw_value = ATH5K_RATE_CODE_36M,
	  .flags = IEEE80211_RATE_SUPPORTS_5MHZ |
		   IEEE80211_RATE_SUPPORTS_10MHZ पूर्ण,
	अणु .bitrate = 480,
	  .hw_value = ATH5K_RATE_CODE_48M,
	  .flags = IEEE80211_RATE_SUPPORTS_5MHZ |
		   IEEE80211_RATE_SUPPORTS_10MHZ पूर्ण,
	अणु .bitrate = 540,
	  .hw_value = ATH5K_RATE_CODE_54M,
	  .flags = IEEE80211_RATE_SUPPORTS_5MHZ |
		   IEEE80211_RATE_SUPPORTS_10MHZ पूर्ण,
पूर्ण;

अटल अंतरभूत u64 ath5k_extend_tsf(काष्ठा ath5k_hw *ah, u32 rstamp)
अणु
	u64 tsf = ath5k_hw_get_tsf64(ah);

	अगर ((tsf & 0x7fff) < rstamp)
		tsf -= 0x8000;

	वापस (tsf & ~0x7fff) | rstamp;
पूर्ण

स्थिर अक्षर *
ath5k_chip_name(क्रमागत ath5k_srev_type type, u_पूर्णांक16_t val)
अणु
	स्थिर अक्षर *name = "xxxxx";
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(srev_names); i++) अणु
		अगर (srev_names[i].sr_type != type)
			जारी;

		अगर ((val & 0xf0) == srev_names[i].sr_val)
			name = srev_names[i].sr_name;

		अगर ((val & 0xff) == srev_names[i].sr_val) अणु
			name = srev_names[i].sr_name;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस name;
पूर्ण
अटल अचिन्हित पूर्णांक ath5k_ioपढ़ो32(व्योम *hw_priv, u32 reg_offset)
अणु
	काष्ठा ath5k_hw *ah = (काष्ठा ath5k_hw *) hw_priv;
	वापस ath5k_hw_reg_पढ़ो(ah, reg_offset);
पूर्ण

अटल व्योम ath5k_ioग_लिखो32(व्योम *hw_priv, u32 val, u32 reg_offset)
अणु
	काष्ठा ath5k_hw *ah = (काष्ठा ath5k_hw *) hw_priv;
	ath5k_hw_reg_ग_लिखो(ah, val, reg_offset);
पूर्ण

अटल स्थिर काष्ठा ath_ops ath5k_common_ops = अणु
	.पढ़ो = ath5k_ioपढ़ो32,
	.ग_लिखो = ath5k_ioग_लिखो32,
पूर्ण;

/***********************\
* Driver Initialization *
\***********************/

अटल व्योम ath5k_reg_notअगरier(काष्ठा wiphy *wiphy,
			       काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath_regulatory *regulatory = ath5k_hw_regulatory(ah);

	ath_reg_notअगरier_apply(wiphy, request, regulatory);
पूर्ण

/********************\
* Channel/mode setup *
\********************/

/*
 * Returns true क्रम the channel numbers used.
 */
#अगर_घोषित CONFIG_ATH5K_TEST_CHANNELS
अटल bool ath5k_is_standard_channel(लघु chan, क्रमागत nl80211_band band)
अणु
	वापस true;
पूर्ण

#अन्यथा
अटल bool ath5k_is_standard_channel(लघु chan, क्रमागत nl80211_band band)
अणु
	अगर (band == NL80211_BAND_2GHZ && chan <= 14)
		वापस true;

	वापस	/* UNII 1,2 */
		(((chan & 3) == 0 && chan >= 36 && chan <= 64) ||
		/* midband */
		((chan & 3) == 0 && chan >= 100 && chan <= 140) ||
		/* UNII-3 */
		((chan & 3) == 1 && chan >= 149 && chan <= 165) ||
		/* 802.11j 5.030-5.080 GHz (20MHz) */
		(chan == 8 || chan == 12 || chan == 16) ||
		/* 802.11j 4.9GHz (20MHz) */
		(chan == 184 || chan == 188 || chan == 192 || chan == 196));
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक
ath5k_setup_channels(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *channels,
		अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक count, size, freq, ch;
	क्रमागत nl80211_band band;

	चयन (mode) अणु
	हाल AR5K_MODE_11A:
		/* 1..220, but 2GHz frequencies are filtered by check_channel */
		size = 220;
		band = NL80211_BAND_5GHZ;
		अवरोध;
	हाल AR5K_MODE_11B:
	हाल AR5K_MODE_11G:
		size = 26;
		band = NL80211_BAND_2GHZ;
		अवरोध;
	शेष:
		ATH5K_WARN(ah, "bad mode, not copying channels\n");
		वापस 0;
	पूर्ण

	count = 0;
	क्रम (ch = 1; ch <= size && count < max; ch++) अणु
		freq = ieee80211_channel_to_frequency(ch, band);

		अगर (freq == 0) /* mapping failed - not a standard channel */
			जारी;

		/* Write channel info, needed क्रम ath5k_channel_ok() */
		channels[count].center_freq = freq;
		channels[count].band = band;
		channels[count].hw_value = mode;

		/* Check अगर channel is supported by the chipset */
		अगर (!ath5k_channel_ok(ah, &channels[count]))
			जारी;

		अगर (!ath5k_is_standard_channel(ch, band))
			जारी;

		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम
ath5k_setup_rate_idx(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_supported_band *b)
अणु
	u8 i;

	क्रम (i = 0; i < AR5K_MAX_RATES; i++)
		ah->rate_idx[b->band][i] = -1;

	क्रम (i = 0; i < b->n_bitrates; i++) अणु
		ah->rate_idx[b->band][b->bitrates[i].hw_value] = i;
		अगर (b->bitrates[i].hw_value_लघु)
			ah->rate_idx[b->band][b->bitrates[i].hw_value_लघु] = i;
	पूर्ण
पूर्ण

अटल पूर्णांक
ath5k_setup_bands(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक max_c, count_c = 0;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(ah->sbands) < NUM_NL80211_BANDS);
	max_c = ARRAY_SIZE(ah->channels);

	/* 2GHz band */
	sband = &ah->sbands[NL80211_BAND_2GHZ];
	sband->band = NL80211_BAND_2GHZ;
	sband->bitrates = &ah->rates[NL80211_BAND_2GHZ][0];

	अगर (test_bit(AR5K_MODE_11G, ah->ah_capabilities.cap_mode)) अणु
		/* G mode */
		स_नकल(sband->bitrates, &ath5k_rates[0],
		       माप(काष्ठा ieee80211_rate) * 12);
		sband->n_bitrates = 12;

		sband->channels = ah->channels;
		sband->n_channels = ath5k_setup_channels(ah, sband->channels,
					AR5K_MODE_11G, max_c);

		hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;
		count_c = sband->n_channels;
		max_c -= count_c;
	पूर्ण अन्यथा अगर (test_bit(AR5K_MODE_11B, ah->ah_capabilities.cap_mode)) अणु
		/* B mode */
		स_नकल(sband->bitrates, &ath5k_rates[0],
		       माप(काष्ठा ieee80211_rate) * 4);
		sband->n_bitrates = 4;

		/* 5211 only supports B rates and uses 4bit rate codes
		 * (e.g normally we have 0x1B क्रम 1M, but on 5211 we have 0x0B)
		 * fix them up here:
		 */
		अगर (ah->ah_version == AR5K_AR5211) अणु
			क्रम (i = 0; i < 4; i++) अणु
				sband->bitrates[i].hw_value =
					sband->bitrates[i].hw_value & 0xF;
				sband->bitrates[i].hw_value_लघु =
					sband->bitrates[i].hw_value_लघु & 0xF;
			पूर्ण
		पूर्ण

		sband->channels = ah->channels;
		sband->n_channels = ath5k_setup_channels(ah, sband->channels,
					AR5K_MODE_11B, max_c);

		hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;
		count_c = sband->n_channels;
		max_c -= count_c;
	पूर्ण
	ath5k_setup_rate_idx(ah, sband);

	/* 5GHz band, A mode */
	अगर (test_bit(AR5K_MODE_11A, ah->ah_capabilities.cap_mode)) अणु
		sband = &ah->sbands[NL80211_BAND_5GHZ];
		sband->band = NL80211_BAND_5GHZ;
		sband->bitrates = &ah->rates[NL80211_BAND_5GHZ][0];

		स_नकल(sband->bitrates, &ath5k_rates[4],
		       माप(काष्ठा ieee80211_rate) * 8);
		sband->n_bitrates = 8;

		sband->channels = &ah->channels[count_c];
		sband->n_channels = ath5k_setup_channels(ah, sband->channels,
					AR5K_MODE_11A, max_c);

		hw->wiphy->bands[NL80211_BAND_5GHZ] = sband;
	पूर्ण
	ath5k_setup_rate_idx(ah, sband);

	ath5k_debug_dump_bands(ah);

	वापस 0;
पूर्ण

/*
 * Set/change channels. We always reset the chip.
 * To accomplish this we must first cleanup any pending DMA,
 * then restart stuff after a la  ath5k_init.
 *
 * Called with ah->lock.
 */
पूर्णांक
ath5k_chan_set(काष्ठा ath5k_hw *ah, काष्ठा cfg80211_chan_def *chandef)
अणु
	ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
		  "channel set, resetting (%u -> %u MHz)\n",
		  ah->curchan->center_freq, chandef->chan->center_freq);

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		ah->ah_bwmode = AR5K_BWMODE_DEFAULT;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_5:
		ah->ah_bwmode = AR5K_BWMODE_5MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_10:
		ah->ah_bwmode = AR5K_BWMODE_10MHZ;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	/*
	 * To चयन channels clear any pending DMA operations;
	 * रुको दीर्घ enough क्रम the RX fअगरo to drain, reset the
	 * hardware at the new frequency, and then re-enable
	 * the relevant bits of the h/w.
	 */
	वापस ath5k_reset(ah, chandef->chan, true);
पूर्ण

व्योम ath5k_vअगर_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath5k_vअगर_iter_data *iter_data = data;
	पूर्णांक i;
	काष्ठा ath5k_vअगर *avf = (व्योम *)vअगर->drv_priv;

	अगर (iter_data->hw_macaddr)
		क्रम (i = 0; i < ETH_ALEN; i++)
			iter_data->mask[i] &=
				~(iter_data->hw_macaddr[i] ^ mac[i]);

	अगर (!iter_data->found_active) अणु
		iter_data->found_active = true;
		स_नकल(iter_data->active_mac, mac, ETH_ALEN);
	पूर्ण

	अगर (iter_data->need_set_hw_addr && iter_data->hw_macaddr)
		अगर (ether_addr_equal(iter_data->hw_macaddr, mac))
			iter_data->need_set_hw_addr = false;

	अगर (!iter_data->any_assoc) अणु
		अगर (avf->assoc)
			iter_data->any_assoc = true;
	पूर्ण

	/* Calculate combined mode - when APs are active, operate in AP mode.
	 * Otherwise use the mode of the new पूर्णांकerface. This can currently
	 * only deal with combinations of APs and STAs. Only one ad-hoc
	 * पूर्णांकerfaces is allowed.
	 */
	अगर (avf->opmode == NL80211_IFTYPE_AP)
		iter_data->opmode = NL80211_IFTYPE_AP;
	अन्यथा अणु
		अगर (avf->opmode == NL80211_IFTYPE_STATION)
			iter_data->n_stas++;
		अगर (iter_data->opmode == NL80211_IFTYPE_UNSPECIFIED)
			iter_data->opmode = avf->opmode;
	पूर्ण
पूर्ण

व्योम
ath5k_update_bssid_mask_and_opmode(काष्ठा ath5k_hw *ah,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	काष्ठा ath5k_vअगर_iter_data iter_data;
	u32 rfilt;

	/*
	 * Use the hardware MAC address as reference, the hardware uses it
	 * together with the BSSID mask when matching addresses.
	 */
	iter_data.hw_macaddr = common->macaddr;
	eth_broadcast_addr(iter_data.mask);
	iter_data.found_active = false;
	iter_data.need_set_hw_addr = true;
	iter_data.opmode = NL80211_IFTYPE_UNSPECIFIED;
	iter_data.n_stas = 0;

	अगर (vअगर)
		ath5k_vअगर_iter(&iter_data, vअगर->addr, vअगर);

	/* Get list of all active MAC addresses */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		ah->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		ath5k_vअगर_iter, &iter_data);
	स_नकल(ah->bssidmask, iter_data.mask, ETH_ALEN);

	ah->opmode = iter_data.opmode;
	अगर (ah->opmode == NL80211_IFTYPE_UNSPECIFIED)
		/* Nothing active, शेष to station mode */
		ah->opmode = NL80211_IFTYPE_STATION;

	ath5k_hw_set_opmode(ah, ah->opmode);
	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "mode setup opmode %d (%s)\n",
		  ah->opmode, ath_opmode_to_string(ah->opmode));

	अगर (iter_data.need_set_hw_addr && iter_data.found_active)
		ath5k_hw_set_lladdr(ah, iter_data.active_mac);

	अगर (ath5k_hw_hasbssidmask(ah))
		ath5k_hw_set_bssid_mask(ah, ah->bssidmask);

	/* Set up RX Filter */
	अगर (iter_data.n_stas > 1) अणु
		/* If you have multiple STA पूर्णांकerfaces connected to
		 * dअगरferent APs, ARPs are not received (most of the समय?)
		 * Enabling PROMISC appears to fix that problem.
		 */
		ah->filter_flags |= AR5K_RX_FILTER_PROM;
	पूर्ण

	rfilt = ah->filter_flags;
	ath5k_hw_set_rx_filter(ah, rfilt);
	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "RX filter 0x%x\n", rfilt);
पूर्ण

अटल अंतरभूत पूर्णांक
ath5k_hw_to_driver_rix(काष्ठा ath5k_hw *ah, पूर्णांक hw_rix)
अणु
	पूर्णांक rix;

	/* वापस base rate on errors */
	अगर (WARN(hw_rix < 0 || hw_rix >= AR5K_MAX_RATES,
			"hw_rix out of bounds: %x\n", hw_rix))
		वापस 0;

	rix = ah->rate_idx[ah->curchan->band][hw_rix];
	अगर (WARN(rix < 0, "invalid hw_rix: %x\n", hw_rix))
		rix = 0;

	वापस rix;
पूर्ण

/***************\
* Buffers setup *
\***************/

अटल
काष्ठा sk_buff *ath5k_rx_skb_alloc(काष्ठा ath5k_hw *ah, dma_addr_t *skb_addr)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	काष्ठा sk_buff *skb;

	/*
	 * Allocate buffer with headroom_needed space क्रम the
	 * fake physical layer header at the start.
	 */
	skb = ath_rxbuf_alloc(common,
			      common->rx_bufsize,
			      GFP_ATOMIC);

	अगर (!skb) अणु
		ATH5K_ERR(ah, "can't alloc skbuff of size %u\n",
				common->rx_bufsize);
		वापस शून्य;
	पूर्ण

	*skb_addr = dma_map_single(ah->dev,
				   skb->data, common->rx_bufsize,
				   DMA_FROM_DEVICE);

	अगर (unlikely(dma_mapping_error(ah->dev, *skb_addr))) अणु
		ATH5K_ERR(ah, "%s: DMA mapping failed\n", __func__);
		dev_kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक
ath5k_rxbuf_setup(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf)
अणु
	काष्ठा sk_buff *skb = bf->skb;
	काष्ठा ath5k_desc *ds;
	पूर्णांक ret;

	अगर (!skb) अणु
		skb = ath5k_rx_skb_alloc(ah, &bf->skbaddr);
		अगर (!skb)
			वापस -ENOMEM;
		bf->skb = skb;
	पूर्ण

	/*
	 * Setup descriptors.  For receive we always terminate
	 * the descriptor list with a self-linked entry so we'll
	 * not get overrun under high load (as can happen with a
	 * 5212 when ANI processing enables PHY error frames).
	 *
	 * To ensure the last descriptor is self-linked we create
	 * each descriptor as self-linked and add it to the end.  As
	 * each additional descriptor is added the previous self-linked
	 * entry is "fixed" naturally.  This should be safe even
	 * अगर DMA is happening.  When processing RX पूर्णांकerrupts we
	 * never हटाओ/process the last, self-linked, entry on the
	 * descriptor list.  This ensures the hardware always has
	 * someplace to ग_लिखो a new frame.
	 */
	ds = bf->desc;
	ds->ds_link = bf->daddr;	/* link to self */
	ds->ds_data = bf->skbaddr;
	ret = ath5k_hw_setup_rx_desc(ah, ds, ah->common.rx_bufsize, 0);
	अगर (ret) अणु
		ATH5K_ERR(ah, "%s: could not setup RX desc\n", __func__);
		वापस ret;
	पूर्ण

	अगर (ah->rxlink != शून्य)
		*ah->rxlink = bf->daddr;
	ah->rxlink = &ds->ds_link;
	वापस 0;
पूर्ण

अटल क्रमागत ath5k_pkt_type get_hw_packet_type(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	क्रमागत ath5k_pkt_type htype;
	__le16 fc;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	fc = hdr->frame_control;

	अगर (ieee80211_is_beacon(fc))
		htype = AR5K_PKT_TYPE_BEACON;
	अन्यथा अगर (ieee80211_is_probe_resp(fc))
		htype = AR5K_PKT_TYPE_PROBE_RESP;
	अन्यथा अगर (ieee80211_is_atim(fc))
		htype = AR5K_PKT_TYPE_ATIM;
	अन्यथा अगर (ieee80211_is_pspoll(fc))
		htype = AR5K_PKT_TYPE_PSPOLL;
	अन्यथा
		htype = AR5K_PKT_TYPE_NORMAL;

	वापस htype;
पूर्ण

अटल काष्ठा ieee80211_rate *
ath5k_get_rate(स्थिर काष्ठा ieee80211_hw *hw,
	       स्थिर काष्ठा ieee80211_tx_info *info,
	       काष्ठा ath5k_buf *bf, पूर्णांक idx)
अणु
	/*
	* convert a ieee80211_tx_rate RC-table entry to
	* the respective ieee80211_rate काष्ठा
	*/
	अगर (bf->rates[idx].idx < 0) अणु
		वापस शून्य;
	पूर्ण

	वापस &hw->wiphy->bands[info->band]->bitrates[ bf->rates[idx].idx ];
पूर्ण

अटल u16
ath5k_get_rate_hw_value(स्थिर काष्ठा ieee80211_hw *hw,
			स्थिर काष्ठा ieee80211_tx_info *info,
			काष्ठा ath5k_buf *bf, पूर्णांक idx)
अणु
	काष्ठा ieee80211_rate *rate;
	u16 hw_rate;
	u8 rc_flags;

	rate = ath5k_get_rate(hw, info, bf, idx);
	अगर (!rate)
		वापस 0;

	rc_flags = bf->rates[idx].flags;
	hw_rate = (rc_flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE) ?
		   rate->hw_value_लघु : rate->hw_value;

	वापस hw_rate;
पूर्ण

अटल पूर्णांक
ath5k_txbuf_setup(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf,
		  काष्ठा ath5k_txq *txq, पूर्णांक padsize,
		  काष्ठा ieee80211_tx_control *control)
अणु
	काष्ठा ath5k_desc *ds = bf->desc;
	काष्ठा sk_buff *skb = bf->skb;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	अचिन्हित पूर्णांक pktlen, flags, keyidx = AR5K_TXKEYIX_INVALID;
	काष्ठा ieee80211_rate *rate;
	अचिन्हित पूर्णांक mrr_rate[3], mrr_tries[3];
	पूर्णांक i, ret;
	u16 hw_rate;
	u16 cts_rate = 0;
	u16 duration = 0;
	u8 rc_flags;

	flags = AR5K_TXDESC_INTREQ | AR5K_TXDESC_CLRDMASK;

	/* XXX endianness */
	bf->skbaddr = dma_map_single(ah->dev, skb->data, skb->len,
			DMA_TO_DEVICE);

	अगर (dma_mapping_error(ah->dev, bf->skbaddr))
		वापस -ENOSPC;

	ieee80211_get_tx_rates(info->control.vअगर, (control) ? control->sta : शून्य, skb, bf->rates,
			       ARRAY_SIZE(bf->rates));

	rate = ath5k_get_rate(ah->hw, info, bf, 0);

	अगर (!rate) अणु
		ret = -EINVAL;
		जाओ err_unmap;
	पूर्ण

	अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
		flags |= AR5K_TXDESC_NOACK;

	rc_flags = bf->rates[0].flags;

	hw_rate = ath5k_get_rate_hw_value(ah->hw, info, bf, 0);

	pktlen = skb->len;

	/* FIXME: If we are in g mode and rate is a CCK rate
	 * subtract ah->ah_txघातer.txp_cck_ofdm_pwr_delta
	 * from tx घातer (value is in dB units alपढ़ोy) */
	अगर (info->control.hw_key) अणु
		keyidx = info->control.hw_key->hw_key_idx;
		pktlen += info->control.hw_key->icv_len;
	पूर्ण
	अगर (rc_flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
		flags |= AR5K_TXDESC_RTSENA;
		cts_rate = ieee80211_get_rts_cts_rate(ah->hw, info)->hw_value;
		duration = le16_to_cpu(ieee80211_rts_duration(ah->hw,
			info->control.vअगर, pktlen, info));
	पूर्ण
	अगर (rc_flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
		flags |= AR5K_TXDESC_CTSENA;
		cts_rate = ieee80211_get_rts_cts_rate(ah->hw, info)->hw_value;
		duration = le16_to_cpu(ieee80211_ctstoself_duration(ah->hw,
			info->control.vअगर, pktlen, info));
	पूर्ण

	ret = ah->ah_setup_tx_desc(ah, ds, pktlen,
		ieee80211_get_hdrlen_from_skb(skb), padsize,
		get_hw_packet_type(skb),
		(ah->ah_txघातer.txp_requested * 2),
		hw_rate,
		bf->rates[0].count, keyidx, ah->ah_tx_ant, flags,
		cts_rate, duration);
	अगर (ret)
		जाओ err_unmap;

	/* Set up MRR descriptor */
	अगर (ah->ah_capabilities.cap_has_mrr_support) अणु
		स_रखो(mrr_rate, 0, माप(mrr_rate));
		स_रखो(mrr_tries, 0, माप(mrr_tries));

		क्रम (i = 0; i < 3; i++) अणु

			rate = ath5k_get_rate(ah->hw, info, bf, i);
			अगर (!rate)
				अवरोध;

			mrr_rate[i] = ath5k_get_rate_hw_value(ah->hw, info, bf, i);
			mrr_tries[i] = bf->rates[i].count;
		पूर्ण

		ath5k_hw_setup_mrr_tx_desc(ah, ds,
			mrr_rate[0], mrr_tries[0],
			mrr_rate[1], mrr_tries[1],
			mrr_rate[2], mrr_tries[2]);
	पूर्ण

	ds->ds_link = 0;
	ds->ds_data = bf->skbaddr;

	spin_lock_bh(&txq->lock);
	list_add_tail(&bf->list, &txq->q);
	txq->txq_len++;
	अगर (txq->link == शून्य) /* is this first packet? */
		ath5k_hw_set_txdp(ah, txq->qnum, bf->daddr);
	अन्यथा /* no, so only link it */
		*txq->link = bf->daddr;

	txq->link = &ds->ds_link;
	ath5k_hw_start_tx_dma(ah, txq->qnum);
	spin_unlock_bh(&txq->lock);

	वापस 0;
err_unmap:
	dma_unmap_single(ah->dev, bf->skbaddr, skb->len, DMA_TO_DEVICE);
	वापस ret;
पूर्ण

/*******************\
* Descriptors setup *
\*******************/

अटल पूर्णांक
ath5k_desc_alloc(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_desc *ds;
	काष्ठा ath5k_buf *bf;
	dma_addr_t da;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* allocate descriptors */
	ah->desc_len = माप(काष्ठा ath5k_desc) *
			(ATH_TXBUF + ATH_RXBUF + ATH_BCBUF + 1);

	ah->desc = dma_alloc_coherent(ah->dev, ah->desc_len,
				&ah->desc_daddr, GFP_KERNEL);
	अगर (ah->desc == शून्य) अणु
		ATH5K_ERR(ah, "can't allocate descriptors\n");
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	ds = ah->desc;
	da = ah->desc_daddr;
	ATH5K_DBG(ah, ATH5K_DEBUG_ANY, "DMA map: %p (%zu) -> %llx\n",
		ds, ah->desc_len, (अचिन्हित दीर्घ दीर्घ)ah->desc_daddr);

	bf = kसुस्मृति(1 + ATH_TXBUF + ATH_RXBUF + ATH_BCBUF,
			माप(काष्ठा ath5k_buf), GFP_KERNEL);
	अगर (bf == शून्य) अणु
		ATH5K_ERR(ah, "can't allocate bufptr\n");
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण
	ah->bufptr = bf;

	INIT_LIST_HEAD(&ah->rxbuf);
	क्रम (i = 0; i < ATH_RXBUF; i++, bf++, ds++, da += माप(*ds)) अणु
		bf->desc = ds;
		bf->daddr = da;
		list_add_tail(&bf->list, &ah->rxbuf);
	पूर्ण

	INIT_LIST_HEAD(&ah->txbuf);
	ah->txbuf_len = ATH_TXBUF;
	क्रम (i = 0; i < ATH_TXBUF; i++, bf++, ds++, da += माप(*ds)) अणु
		bf->desc = ds;
		bf->daddr = da;
		list_add_tail(&bf->list, &ah->txbuf);
	पूर्ण

	/* beacon buffers */
	INIT_LIST_HEAD(&ah->bcbuf);
	क्रम (i = 0; i < ATH_BCBUF; i++, bf++, ds++, da += माप(*ds)) अणु
		bf->desc = ds;
		bf->daddr = da;
		list_add_tail(&bf->list, &ah->bcbuf);
	पूर्ण

	वापस 0;
err_मुक्त:
	dma_मुक्त_coherent(ah->dev, ah->desc_len, ah->desc, ah->desc_daddr);
err:
	ah->desc = शून्य;
	वापस ret;
पूर्ण

व्योम
ath5k_txbuf_मुक्त_skb(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf)
अणु
	BUG_ON(!bf);
	अगर (!bf->skb)
		वापस;
	dma_unmap_single(ah->dev, bf->skbaddr, bf->skb->len,
			DMA_TO_DEVICE);
	ieee80211_मुक्त_txskb(ah->hw, bf->skb);
	bf->skb = शून्य;
	bf->skbaddr = 0;
	bf->desc->ds_data = 0;
पूर्ण

व्योम
ath5k_rxbuf_मुक्त_skb(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);

	BUG_ON(!bf);
	अगर (!bf->skb)
		वापस;
	dma_unmap_single(ah->dev, bf->skbaddr, common->rx_bufsize,
			DMA_FROM_DEVICE);
	dev_kमुक्त_skb_any(bf->skb);
	bf->skb = शून्य;
	bf->skbaddr = 0;
	bf->desc->ds_data = 0;
पूर्ण

अटल व्योम
ath5k_desc_मुक्त(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_buf *bf;

	list_क्रम_each_entry(bf, &ah->txbuf, list)
		ath5k_txbuf_मुक्त_skb(ah, bf);
	list_क्रम_each_entry(bf, &ah->rxbuf, list)
		ath5k_rxbuf_मुक्त_skb(ah, bf);
	list_क्रम_each_entry(bf, &ah->bcbuf, list)
		ath5k_txbuf_मुक्त_skb(ah, bf);

	/* Free memory associated with all descriptors */
	dma_मुक्त_coherent(ah->dev, ah->desc_len, ah->desc, ah->desc_daddr);
	ah->desc = शून्य;
	ah->desc_daddr = 0;

	kमुक्त(ah->bufptr);
	ah->bufptr = शून्य;
पूर्ण


/**************\
* Queues setup *
\**************/

अटल काष्ठा ath5k_txq *
ath5k_txq_setup(काष्ठा ath5k_hw *ah,
		पूर्णांक qtype, पूर्णांक subtype)
अणु
	काष्ठा ath5k_txq *txq;
	काष्ठा ath5k_txq_info qi = अणु
		.tqi_subtype = subtype,
		/* XXX: शेष values not correct क्रम B and XR channels,
		 * but who cares? */
		.tqi_aअगरs = AR5K_TUNE_AIFS,
		.tqi_cw_min = AR5K_TUNE_CWMIN,
		.tqi_cw_max = AR5K_TUNE_CWMAX
	पूर्ण;
	पूर्णांक qnum;

	/*
	 * Enable पूर्णांकerrupts only क्रम EOL and DESC conditions.
	 * We mark tx descriptors to receive a DESC पूर्णांकerrupt
	 * when a tx queue माला_लो deep; otherwise we रुको क्रम the
	 * EOL to reap descriptors.  Note that this is करोne to
	 * reduce पूर्णांकerrupt load and this only defers reaping
	 * descriptors, never transmitting frames.  Aside from
	 * reducing पूर्णांकerrupts this also permits more concurrency.
	 * The only potential करोwnside is अगर the tx queue backs
	 * up in which हाल the top half of the kernel may backup
	 * due to a lack of tx descriptors.
	 */
	qi.tqi_flags = AR5K_TXQ_FLAG_TXEOLINT_ENABLE |
				AR5K_TXQ_FLAG_TXDESCINT_ENABLE;
	qnum = ath5k_hw_setup_tx_queue(ah, qtype, &qi);
	अगर (qnum < 0) अणु
		/*
		 * NB: करोn't prपूर्णांक a message, this happens
		 * normally on parts with too few tx queues
		 */
		वापस ERR_PTR(qnum);
	पूर्ण
	txq = &ah->txqs[qnum];
	अगर (!txq->setup) अणु
		txq->qnum = qnum;
		txq->link = शून्य;
		INIT_LIST_HEAD(&txq->q);
		spin_lock_init(&txq->lock);
		txq->setup = true;
		txq->txq_len = 0;
		txq->txq_max = ATH5K_TXQ_LEN_MAX;
		txq->txq_poll_mark = false;
		txq->txq_stuck = 0;
	पूर्ण
	वापस &ah->txqs[qnum];
पूर्ण

अटल पूर्णांक
ath5k_beaconq_setup(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_txq_info qi = अणु
		/* XXX: शेष values not correct क्रम B and XR channels,
		 * but who cares? */
		.tqi_aअगरs = AR5K_TUNE_AIFS,
		.tqi_cw_min = AR5K_TUNE_CWMIN,
		.tqi_cw_max = AR5K_TUNE_CWMAX,
		/* NB: क्रम dynamic turbo, करोn't enable any other पूर्णांकerrupts */
		.tqi_flags = AR5K_TXQ_FLAG_TXDESCINT_ENABLE
	पूर्ण;

	वापस ath5k_hw_setup_tx_queue(ah, AR5K_TX_QUEUE_BEACON, &qi);
पूर्ण

अटल पूर्णांक
ath5k_beaconq_config(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_txq_info qi;
	पूर्णांक ret;

	ret = ath5k_hw_get_tx_queueprops(ah, ah->bhalq, &qi);
	अगर (ret)
		जाओ err;

	अगर (ah->opmode == NL80211_IFTYPE_AP ||
	    ah->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		/*
		 * Always burst out beacon and CAB traffic
		 * (aअगरs = cwmin = cwmax = 0)
		 */
		qi.tqi_aअगरs = 0;
		qi.tqi_cw_min = 0;
		qi.tqi_cw_max = 0;
	पूर्ण अन्यथा अगर (ah->opmode == NL80211_IFTYPE_ADHOC) अणु
		/*
		 * Adhoc mode; backoff between 0 and (2 * cw_min).
		 */
		qi.tqi_aअगरs = 0;
		qi.tqi_cw_min = 0;
		qi.tqi_cw_max = 2 * AR5K_TUNE_CWMIN;
	पूर्ण

	ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
		"beacon queueprops tqi_aifs:%d tqi_cw_min:%d tqi_cw_max:%d\n",
		qi.tqi_aअगरs, qi.tqi_cw_min, qi.tqi_cw_max);

	ret = ath5k_hw_set_tx_queueprops(ah, ah->bhalq, &qi);
	अगर (ret) अणु
		ATH5K_ERR(ah, "%s: unable to update parameters for beacon "
			"hardware queue!\n", __func__);
		जाओ err;
	पूर्ण
	ret = ath5k_hw_reset_tx_queue(ah, ah->bhalq); /* push to h/w */
	अगर (ret)
		जाओ err;

	/* reconfigure cabq with पढ़ोy समय to 80% of beacon_पूर्णांकerval */
	ret = ath5k_hw_get_tx_queueprops(ah, AR5K_TX_QUEUE_ID_CAB, &qi);
	अगर (ret)
		जाओ err;

	qi.tqi_पढ़ोy_समय = (ah->bपूर्णांकval * 80) / 100;
	ret = ath5k_hw_set_tx_queueprops(ah, AR5K_TX_QUEUE_ID_CAB, &qi);
	अगर (ret)
		जाओ err;

	ret = ath5k_hw_reset_tx_queue(ah, AR5K_TX_QUEUE_ID_CAB);
err:
	वापस ret;
पूर्ण

/**
 * ath5k_drain_tx_buffs - Empty tx buffers
 *
 * @ah: The &काष्ठा ath5k_hw
 *
 * Empty tx buffers from all queues in preparation
 * of a reset or during shutकरोwn.
 *
 * NB:	this assumes output has been stopped and
 *	we करो not need to block ath5k_tx_tasklet
 */
अटल व्योम
ath5k_drain_tx_buffs(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_txq *txq;
	काष्ठा ath5k_buf *bf, *bf0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ah->txqs); i++) अणु
		अगर (ah->txqs[i].setup) अणु
			txq = &ah->txqs[i];
			spin_lock_bh(&txq->lock);
			list_क्रम_each_entry_safe(bf, bf0, &txq->q, list) अणु
				ath5k_debug_prपूर्णांकtxbuf(ah, bf);

				ath5k_txbuf_मुक्त_skb(ah, bf);

				spin_lock(&ah->txbuflock);
				list_move_tail(&bf->list, &ah->txbuf);
				ah->txbuf_len++;
				txq->txq_len--;
				spin_unlock(&ah->txbuflock);
			पूर्ण
			txq->link = शून्य;
			txq->txq_poll_mark = false;
			spin_unlock_bh(&txq->lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ath5k_txq_release(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_txq *txq = ah->txqs;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ah->txqs); i++, txq++)
		अगर (txq->setup) अणु
			ath5k_hw_release_tx_queue(ah, txq->qnum);
			txq->setup = false;
		पूर्ण
पूर्ण


/*************\
* RX Handling *
\*************/

/*
 * Enable the receive h/w following a reset.
 */
अटल पूर्णांक
ath5k_rx_start(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	काष्ठा ath5k_buf *bf;
	पूर्णांक ret;

	common->rx_bufsize = roundup(IEEE80211_MAX_FRAME_LEN, common->cachelsz);

	ATH5K_DBG(ah, ATH5K_DEBUG_RESET, "cachelsz %u rx_bufsize %u\n",
		  common->cachelsz, common->rx_bufsize);

	spin_lock_bh(&ah->rxbuflock);
	ah->rxlink = शून्य;
	list_क्रम_each_entry(bf, &ah->rxbuf, list) अणु
		ret = ath5k_rxbuf_setup(ah, bf);
		अगर (ret != 0) अणु
			spin_unlock_bh(&ah->rxbuflock);
			जाओ err;
		पूर्ण
	पूर्ण
	bf = list_first_entry(&ah->rxbuf, काष्ठा ath5k_buf, list);
	ath5k_hw_set_rxdp(ah, bf->daddr);
	spin_unlock_bh(&ah->rxbuflock);

	ath5k_hw_start_rx_dma(ah);	/* enable recv descriptors */
	ath5k_update_bssid_mask_and_opmode(ah, शून्य); /* set filters, etc. */
	ath5k_hw_start_rx_pcu(ah);	/* re-enable PCU/DMA engine */

	वापस 0;
err:
	वापस ret;
पूर्ण

/*
 * Disable the receive logic on PCU (DRU)
 * In preparation क्रम a shutकरोwn.
 *
 * Note: Doesn't stop rx DMA, ath5k_hw_dma_stop
 * करोes.
 */
अटल व्योम
ath5k_rx_stop(काष्ठा ath5k_hw *ah)
अणु

	ath5k_hw_set_rx_filter(ah, 0);	/* clear recv filter */
	ath5k_hw_stop_rx_pcu(ah);	/* disable PCU */

	ath5k_debug_prपूर्णांकrxbuffs(ah);
पूर्ण

अटल अचिन्हित पूर्णांक
ath5k_rx_decrypted(काष्ठा ath5k_hw *ah, काष्ठा sk_buff *skb,
		   काष्ठा ath5k_rx_status *rs)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	अचिन्हित पूर्णांक keyix, hlen;

	अगर (!(rs->rs_status & AR5K_RXERR_DECRYPT) &&
			rs->rs_keyix != AR5K_RXKEYIX_INVALID)
		वापस RX_FLAG_DECRYPTED;

	/* Apparently when a शेष key is used to decrypt the packet
	   the hw करोes not set the index used to decrypt.  In such हालs
	   get the index from the packet. */
	hlen = ieee80211_hdrlen(hdr->frame_control);
	अगर (ieee80211_has_रक्षित(hdr->frame_control) &&
	    !(rs->rs_status & AR5K_RXERR_DECRYPT) &&
	    skb->len >= hlen + 4) अणु
		keyix = skb->data[hlen + 3] >> 6;

		अगर (test_bit(keyix, common->keymap))
			वापस RX_FLAG_DECRYPTED;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम
ath5k_check_ibss_tsf(काष्ठा ath5k_hw *ah, काष्ठा sk_buff *skb,
		     काष्ठा ieee80211_rx_status *rxs)
अणु
	u64 tsf, bc_tstamp;
	u32 hw_tu;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)skb->data;

	अगर (le16_to_cpu(mgmt->u.beacon.capab_info) & WLAN_CAPABILITY_IBSS) अणु
		/*
		 * Received an IBSS beacon with the same BSSID. Hardware *must*
		 * have updated the local TSF. We have to work around various
		 * hardware bugs, though...
		 */
		tsf = ath5k_hw_get_tsf64(ah);
		bc_tstamp = le64_to_cpu(mgmt->u.beacon.बारtamp);
		hw_tu = TSF_TO_TU(tsf);

		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"beacon %llx mactime %llx (diff %lld) tsf now %llx\n",
			(अचिन्हित दीर्घ दीर्घ)bc_tstamp,
			(अचिन्हित दीर्घ दीर्घ)rxs->maस_समय,
			(अचिन्हित दीर्घ दीर्घ)(rxs->maस_समय - bc_tstamp),
			(अचिन्हित दीर्घ दीर्घ)tsf);

		/*
		 * Someबार the HW will give us a wrong tstamp in the rx
		 * status, causing the बारtamp extension to go wrong.
		 * (This seems to happen especially with beacon frames bigger
		 * than 78 byte (incl. FCS))
		 * But we know that the receive बारtamp must be later than the
		 * बारtamp of the beacon since HW must have synced to that.
		 *
		 * NOTE: here we assume maस_समय to be after the frame was
		 * received, not like mac80211 which defines it at the start.
		 */
		अगर (bc_tstamp > rxs->maस_समय) अणु
			ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
				"fixing mactime from %llx to %llx\n",
				(अचिन्हित दीर्घ दीर्घ)rxs->maस_समय,
				(अचिन्हित दीर्घ दीर्घ)tsf);
			rxs->maस_समय = tsf;
		पूर्ण

		/*
		 * Local TSF might have moved higher than our beacon समयrs,
		 * in that हाल we have to update them to जारी sending
		 * beacons. This also takes care of synchronizing beacon sending
		 * बार with other stations.
		 */
		अगर (hw_tu >= ah->nexttbtt)
			ath5k_beacon_update_समयrs(ah, bc_tstamp);

		/* Check अगर the beacon समयrs are still correct, because a TSF
		 * update might have created a winकरोw between them - क्रम a
		 * दीर्घer description see the comment of this function: */
		अगर (!ath5k_hw_check_beacon_समयrs(ah, ah->bपूर्णांकval)) अणु
			ath5k_beacon_update_समयrs(ah, bc_tstamp);
			ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
				"fixed beacon timers after beacon receive\n");
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Compute padding position. skb must contain an IEEE 802.11 frame
 */
अटल पूर्णांक ath5k_common_padpos(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	__le16 frame_control = hdr->frame_control;
	पूर्णांक padpos = 24;

	अगर (ieee80211_has_a4(frame_control))
		padpos += ETH_ALEN;

	अगर (ieee80211_is_data_qos(frame_control))
		padpos += IEEE80211_QOS_CTL_LEN;

	वापस padpos;
पूर्ण

/*
 * This function expects an 802.11 frame and वापसs the number of
 * bytes added, or -1 अगर we करोn't have enough header room.
 */
अटल पूर्णांक ath5k_add_padding(काष्ठा sk_buff *skb)
अणु
	पूर्णांक padpos = ath5k_common_padpos(skb);
	पूर्णांक padsize = padpos & 3;

	अगर (padsize && skb->len > padpos) अणु

		अगर (skb_headroom(skb) < padsize)
			वापस -1;

		skb_push(skb, padsize);
		स_हटाओ(skb->data, skb->data + padsize, padpos);
		वापस padsize;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The MAC header is padded to have 32-bit boundary अगर the
 * packet payload is non-zero. The general calculation क्रम
 * padsize would take पूर्णांकo account odd header lengths:
 * padsize = 4 - (hdrlen & 3); however, since only
 * even-length headers are used, padding can only be 0 or 2
 * bytes and we can optimize this a bit.  We must not try to
 * हटाओ padding from लघु control frames that करो not have a
 * payload.
 *
 * This function expects an 802.11 frame and वापसs the number of
 * bytes हटाओd.
 */
अटल पूर्णांक ath5k_हटाओ_padding(काष्ठा sk_buff *skb)
अणु
	पूर्णांक padpos = ath5k_common_padpos(skb);
	पूर्णांक padsize = padpos & 3;

	अगर (padsize && skb->len >= padpos + padsize) अणु
		स_हटाओ(skb->data + padsize, skb->data, padpos);
		skb_pull(skb, padsize);
		वापस padsize;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
ath5k_receive_frame(काष्ठा ath5k_hw *ah, काष्ठा sk_buff *skb,
		    काष्ठा ath5k_rx_status *rs)
अणु
	काष्ठा ieee80211_rx_status *rxs;
	काष्ठा ath_common *common = ath5k_hw_common(ah);

	ath5k_हटाओ_padding(skb);

	rxs = IEEE80211_SKB_RXCB(skb);

	rxs->flag = 0;
	अगर (unlikely(rs->rs_status & AR5K_RXERR_MIC))
		rxs->flag |= RX_FLAG_MMIC_ERROR;
	अगर (unlikely(rs->rs_status & AR5K_RXERR_CRC))
		rxs->flag |= RX_FLAG_FAILED_FCS_CRC;


	/*
	 * always extend the mac बारtamp, since this inक्रमmation is
	 * also needed क्रम proper IBSS merging.
	 *
	 * XXX: it might be too late to करो it here, since rs_tstamp is
	 * 15bit only. that means TSF extension has to be करोne within
	 * 32768usec (about 32ms). it might be necessary to move this to
	 * the पूर्णांकerrupt handler, like it is करोne in madwअगरi.
	 */
	rxs->maस_समय = ath5k_extend_tsf(ah, rs->rs_tstamp);
	rxs->flag |= RX_FLAG_MACTIME_END;

	rxs->freq = ah->curchan->center_freq;
	rxs->band = ah->curchan->band;

	rxs->संकेत = ah->ah_noise_न्यूनमान + rs->rs_rssi;

	rxs->antenna = rs->rs_antenna;

	अगर (rs->rs_antenna > 0 && rs->rs_antenna < 5)
		ah->stats.antenna_rx[rs->rs_antenna]++;
	अन्यथा
		ah->stats.antenna_rx[0]++; /* invalid */

	rxs->rate_idx = ath5k_hw_to_driver_rix(ah, rs->rs_rate);
	rxs->flag |= ath5k_rx_decrypted(ah, skb, rs);
	चयन (ah->ah_bwmode) अणु
	हाल AR5K_BWMODE_5MHZ:
		rxs->bw = RATE_INFO_BW_5;
		अवरोध;
	हाल AR5K_BWMODE_10MHZ:
		rxs->bw = RATE_INFO_BW_10;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (rs->rs_rate ==
	    ah->sbands[ah->curchan->band].bitrates[rxs->rate_idx].hw_value_लघु)
		rxs->enc_flags |= RX_ENC_FLAG_SHORTPRE;

	trace_ath5k_rx(ah, skb);

	अगर (ath_is_mybeacon(common, (काष्ठा ieee80211_hdr *)skb->data)) अणु
		ewma_beacon_rssi_add(&ah->ah_beacon_rssi_avg, rs->rs_rssi);

		/* check beacons in IBSS mode */
		अगर (ah->opmode == NL80211_IFTYPE_ADHOC)
			ath5k_check_ibss_tsf(ah, skb, rxs);
	पूर्ण

	ieee80211_rx(ah->hw, skb);
पूर्ण

/** ath5k_frame_receive_ok() - Do we want to receive this frame or not?
 *
 * Check अगर we want to further process this frame or not. Also update
 * statistics. Return true अगर we want this frame, false अगर not.
 */
अटल bool
ath5k_receive_frame_ok(काष्ठा ath5k_hw *ah, काष्ठा ath5k_rx_status *rs)
अणु
	ah->stats.rx_all_count++;
	ah->stats.rx_bytes_count += rs->rs_datalen;

	अगर (unlikely(rs->rs_status)) अणु
		अचिन्हित पूर्णांक filters;

		अगर (rs->rs_status & AR5K_RXERR_CRC)
			ah->stats.rxerr_crc++;
		अगर (rs->rs_status & AR5K_RXERR_FIFO)
			ah->stats.rxerr_fअगरo++;
		अगर (rs->rs_status & AR5K_RXERR_PHY) अणु
			ah->stats.rxerr_phy++;
			अगर (rs->rs_phyerr > 0 && rs->rs_phyerr < 32)
				ah->stats.rxerr_phy_code[rs->rs_phyerr]++;

			/*
			 * Treat packets that underwent a CCK or OFDM reset as having a bad CRC.
			 * These restarts happen when the radio resynchronizes to a stronger frame
			 * जबतक receiving a weaker frame. Here we receive the prefix of the weak
			 * frame. Since these are incomplete packets, mark their CRC as invalid.
			 */
			अगर (rs->rs_phyerr == AR5K_RX_PHY_ERROR_OFDM_RESTART ||
			    rs->rs_phyerr == AR5K_RX_PHY_ERROR_CCK_RESTART) अणु
				rs->rs_status |= AR5K_RXERR_CRC;
				rs->rs_status &= ~AR5K_RXERR_PHY;
			पूर्ण अन्यथा अणु
				वापस false;
			पूर्ण
		पूर्ण
		अगर (rs->rs_status & AR5K_RXERR_DECRYPT) अणु
			/*
			 * Decrypt error.  If the error occurred
			 * because there was no hardware key, then
			 * let the frame through so the upper layers
			 * can process it.  This is necessary क्रम 5210
			 * parts which have no way to setup a ``clear''
			 * key cache entry.
			 *
			 * XXX करो key cache faulting
			 */
			ah->stats.rxerr_decrypt++;
			अगर (rs->rs_keyix == AR5K_RXKEYIX_INVALID &&
			    !(rs->rs_status & AR5K_RXERR_CRC))
				वापस true;
		पूर्ण
		अगर (rs->rs_status & AR5K_RXERR_MIC) अणु
			ah->stats.rxerr_mic++;
			वापस true;
		पूर्ण

		/*
		 * Reject any frames with non-crypto errors, and take पूर्णांकo account the
		 * current FIF_* filters.
		 */
		filters = AR5K_RXERR_DECRYPT;
		अगर (ah->fअगर_filter_flags & FIF_FCSFAIL)
			filters |= AR5K_RXERR_CRC;

		अगर (rs->rs_status & ~filters)
			वापस false;
	पूर्ण

	अगर (unlikely(rs->rs_more)) अणु
		ah->stats.rxerr_jumbo++;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम
ath5k_set_current_imask(काष्ठा ath5k_hw *ah)
अणु
	क्रमागत ath5k_पूर्णांक imask;
	अचिन्हित दीर्घ flags;

	अगर (test_bit(ATH_STAT_RESET, ah->status))
		वापस;

	spin_lock_irqsave(&ah->irqlock, flags);
	imask = ah->imask;
	अगर (ah->rx_pending)
		imask &= ~AR5K_INT_RX_ALL;
	अगर (ah->tx_pending)
		imask &= ~AR5K_INT_TX_ALL;
	ath5k_hw_set_imr(ah, imask);
	spin_unlock_irqrestore(&ah->irqlock, flags);
पूर्ण

अटल व्योम
ath5k_tasklet_rx(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath5k_rx_status rs = अणुपूर्ण;
	काष्ठा sk_buff *skb, *next_skb;
	dma_addr_t next_skb_addr;
	काष्ठा ath5k_hw *ah = from_tasklet(ah, t, rxtq);
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	काष्ठा ath5k_buf *bf;
	काष्ठा ath5k_desc *ds;
	पूर्णांक ret;

	spin_lock(&ah->rxbuflock);
	अगर (list_empty(&ah->rxbuf)) अणु
		ATH5K_WARN(ah, "empty rx buf pool\n");
		जाओ unlock;
	पूर्ण
	करो अणु
		bf = list_first_entry(&ah->rxbuf, काष्ठा ath5k_buf, list);
		BUG_ON(bf->skb == शून्य);
		skb = bf->skb;
		ds = bf->desc;

		/* bail अगर HW is still using self-linked descriptor */
		अगर (ath5k_hw_get_rxdp(ah) == bf->daddr)
			अवरोध;

		ret = ah->ah_proc_rx_desc(ah, ds, &rs);
		अगर (unlikely(ret == -EINPROGRESS))
			अवरोध;
		अन्यथा अगर (unlikely(ret)) अणु
			ATH5K_ERR(ah, "error in processing rx descriptor\n");
			ah->stats.rxerr_proc++;
			अवरोध;
		पूर्ण

		अगर (ath5k_receive_frame_ok(ah, &rs)) अणु
			next_skb = ath5k_rx_skb_alloc(ah, &next_skb_addr);

			/*
			 * If we can't replace bf->skb with a new skb under
			 * memory pressure, just skip this packet
			 */
			अगर (!next_skb)
				जाओ next;

			dma_unmap_single(ah->dev, bf->skbaddr,
					 common->rx_bufsize,
					 DMA_FROM_DEVICE);

			skb_put(skb, rs.rs_datalen);

			ath5k_receive_frame(ah, skb, &rs);

			bf->skb = next_skb;
			bf->skbaddr = next_skb_addr;
		पूर्ण
next:
		list_move_tail(&bf->list, &ah->rxbuf);
	पूर्ण जबतक (ath5k_rxbuf_setup(ah, bf) == 0);
unlock:
	spin_unlock(&ah->rxbuflock);
	ah->rx_pending = false;
	ath5k_set_current_imask(ah);
पूर्ण


/*************\
* TX Handling *
\*************/

व्योम
ath5k_tx_queue(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
	       काष्ठा ath5k_txq *txq, काष्ठा ieee80211_tx_control *control)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath5k_buf *bf;
	अचिन्हित दीर्घ flags;
	पूर्णांक padsize;

	trace_ath5k_tx(ah, skb, txq);

	/*
	 * The hardware expects the header padded to 4 byte boundaries.
	 * If this is not the हाल, we add the padding after the header.
	 */
	padsize = ath5k_add_padding(skb);
	अगर (padsize < 0) अणु
		ATH5K_ERR(ah, "tx hdrlen not %%4: not enough"
			  " headroom to pad");
		जाओ drop_packet;
	पूर्ण

	अगर (txq->txq_len >= txq->txq_max &&
	    txq->qnum <= AR5K_TX_QUEUE_ID_DATA_MAX)
		ieee80211_stop_queue(hw, txq->qnum);

	spin_lock_irqsave(&ah->txbuflock, flags);
	अगर (list_empty(&ah->txbuf)) अणु
		ATH5K_ERR(ah, "no further txbuf available, dropping packet\n");
		spin_unlock_irqrestore(&ah->txbuflock, flags);
		ieee80211_stop_queues(hw);
		जाओ drop_packet;
	पूर्ण
	bf = list_first_entry(&ah->txbuf, काष्ठा ath5k_buf, list);
	list_del(&bf->list);
	ah->txbuf_len--;
	अगर (list_empty(&ah->txbuf))
		ieee80211_stop_queues(hw);
	spin_unlock_irqrestore(&ah->txbuflock, flags);

	bf->skb = skb;

	अगर (ath5k_txbuf_setup(ah, bf, txq, padsize, control)) अणु
		bf->skb = शून्य;
		spin_lock_irqsave(&ah->txbuflock, flags);
		list_add_tail(&bf->list, &ah->txbuf);
		ah->txbuf_len++;
		spin_unlock_irqrestore(&ah->txbuflock, flags);
		जाओ drop_packet;
	पूर्ण
	वापस;

drop_packet:
	ieee80211_मुक्त_txskb(hw, skb);
पूर्ण

अटल व्योम
ath5k_tx_frame_completed(काष्ठा ath5k_hw *ah, काष्ठा sk_buff *skb,
			 काष्ठा ath5k_txq *txq, काष्ठा ath5k_tx_status *ts,
			 काष्ठा ath5k_buf *bf)
अणु
	काष्ठा ieee80211_tx_info *info;
	u8 tries[3];
	पूर्णांक i;
	पूर्णांक size = 0;

	ah->stats.tx_all_count++;
	ah->stats.tx_bytes_count += skb->len;
	info = IEEE80211_SKB_CB(skb);

	size = min_t(पूर्णांक, माप(info->status.rates), माप(bf->rates));
	स_नकल(info->status.rates, bf->rates, size);

	tries[0] = info->status.rates[0].count;
	tries[1] = info->status.rates[1].count;
	tries[2] = info->status.rates[2].count;

	ieee80211_tx_info_clear_status(info);

	क्रम (i = 0; i < ts->ts_final_idx; i++) अणु
		काष्ठा ieee80211_tx_rate *r =
			&info->status.rates[i];

		r->count = tries[i];
	पूर्ण

	info->status.rates[ts->ts_final_idx].count = ts->ts_final_retry;
	info->status.rates[ts->ts_final_idx + 1].idx = -1;

	अगर (unlikely(ts->ts_status)) अणु
		ah->stats.ack_fail++;
		अगर (ts->ts_status & AR5K_TXERR_FILT) अणु
			info->flags |= IEEE80211_TX_STAT_TX_FILTERED;
			ah->stats.txerr_filt++;
		पूर्ण
		अगर (ts->ts_status & AR5K_TXERR_XRETRY)
			ah->stats.txerr_retry++;
		अगर (ts->ts_status & AR5K_TXERR_FIFO)
			ah->stats.txerr_fअगरo++;
	पूर्ण अन्यथा अणु
		info->flags |= IEEE80211_TX_STAT_ACK;
		info->status.ack_संकेत = ts->ts_rssi;

		/* count the successful attempt as well */
		info->status.rates[ts->ts_final_idx].count++;
	पूर्ण

	/*
	* Remove MAC header padding beक्रमe giving the frame
	* back to mac80211.
	*/
	ath5k_हटाओ_padding(skb);

	अगर (ts->ts_antenna > 0 && ts->ts_antenna < 5)
		ah->stats.antenna_tx[ts->ts_antenna]++;
	अन्यथा
		ah->stats.antenna_tx[0]++; /* invalid */

	trace_ath5k_tx_complete(ah, skb, txq, ts);
	ieee80211_tx_status(ah->hw, skb);
पूर्ण

अटल व्योम
ath5k_tx_processq(काष्ठा ath5k_hw *ah, काष्ठा ath5k_txq *txq)
अणु
	काष्ठा ath5k_tx_status ts = अणुपूर्ण;
	काष्ठा ath5k_buf *bf, *bf0;
	काष्ठा ath5k_desc *ds;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	spin_lock(&txq->lock);
	list_क्रम_each_entry_safe(bf, bf0, &txq->q, list) अणु

		txq->txq_poll_mark = false;

		/* skb might alपढ़ोy have been processed last समय. */
		अगर (bf->skb != शून्य) अणु
			ds = bf->desc;

			ret = ah->ah_proc_tx_desc(ah, ds, &ts);
			अगर (unlikely(ret == -EINPROGRESS))
				अवरोध;
			अन्यथा अगर (unlikely(ret)) अणु
				ATH5K_ERR(ah,
					"error %d while processing "
					"queue %u\n", ret, txq->qnum);
				अवरोध;
			पूर्ण

			skb = bf->skb;
			bf->skb = शून्य;

			dma_unmap_single(ah->dev, bf->skbaddr, skb->len,
					DMA_TO_DEVICE);
			ath5k_tx_frame_completed(ah, skb, txq, &ts, bf);
		पूर्ण

		/*
		 * It's possible that the hardware can say the buffer is
		 * completed when it hasn't yet loaded the ds_link from
		 * host memory and moved on.
		 * Always keep the last descriptor to aव्योम HW races...
		 */
		अगर (ath5k_hw_get_txdp(ah, txq->qnum) != bf->daddr) अणु
			spin_lock(&ah->txbuflock);
			list_move_tail(&bf->list, &ah->txbuf);
			ah->txbuf_len++;
			txq->txq_len--;
			spin_unlock(&ah->txbuflock);
		पूर्ण
	पूर्ण
	spin_unlock(&txq->lock);
	अगर (txq->txq_len < ATH5K_TXQ_LEN_LOW && txq->qnum < 4)
		ieee80211_wake_queue(ah->hw, txq->qnum);
पूर्ण

अटल व्योम
ath5k_tasklet_tx(काष्ठा tasklet_काष्ठा *t)
अणु
	पूर्णांक i;
	काष्ठा ath5k_hw *ah = from_tasklet(ah, t, txtq);

	क्रम (i = 0; i < AR5K_NUM_TX_QUEUES; i++)
		अगर (ah->txqs[i].setup && (ah->ah_txq_isr_txok_all & BIT(i)))
			ath5k_tx_processq(ah, &ah->txqs[i]);

	ah->tx_pending = false;
	ath5k_set_current_imask(ah);
पूर्ण


/*****************\
* Beacon handling *
\*****************/

/*
 * Setup the beacon frame क्रम transmit.
 */
अटल पूर्णांक
ath5k_beacon_setup(काष्ठा ath5k_hw *ah, काष्ठा ath5k_buf *bf)
अणु
	काष्ठा sk_buff *skb = bf->skb;
	काष्ठा	ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ath5k_desc *ds;
	पूर्णांक ret = 0;
	u8 antenna;
	u32 flags;
	स्थिर पूर्णांक padsize = 0;

	bf->skbaddr = dma_map_single(ah->dev, skb->data, skb->len,
			DMA_TO_DEVICE);
	ATH5K_DBG(ah, ATH5K_DEBUG_BEACON, "skb %p [data %p len %u] "
			"skbaddr %llx\n", skb, skb->data, skb->len,
			(अचिन्हित दीर्घ दीर्घ)bf->skbaddr);

	अगर (dma_mapping_error(ah->dev, bf->skbaddr)) अणु
		ATH5K_ERR(ah, "beacon DMA mapping failed\n");
		dev_kमुक्त_skb_any(skb);
		bf->skb = शून्य;
		वापस -EIO;
	पूर्ण

	ds = bf->desc;
	antenna = ah->ah_tx_ant;

	flags = AR5K_TXDESC_NOACK;
	अगर (ah->opmode == NL80211_IFTYPE_ADHOC && ath5k_hw_hasveol(ah)) अणु
		ds->ds_link = bf->daddr;	/* self-linked */
		flags |= AR5K_TXDESC_VEOL;
	पूर्ण अन्यथा
		ds->ds_link = 0;

	/*
	 * If we use multiple antennas on AP and use
	 * the Sectored AP scenario, चयन antenna every
	 * 4 beacons to make sure everybody hears our AP.
	 * When a client tries to associate, hw will keep
	 * track of the tx antenna to be used क्रम this client
	 * स्वतःmatically, based on ACKed packets.
	 *
	 * Note: AP still listens and transmits RTS on the
	 * शेष antenna which is supposed to be an omni.
	 *
	 * Note2: On sectored scenarios it's possible to have
	 * multiple antennas (1 omni -- the शेष -- and 14
	 * sectors), so अगर we choose to actually support this
	 * mode, we need to allow the user to set how many antennas
	 * we have and tweak the code below to send beacons
	 * on all of them.
	 */
	अगर (ah->ah_ant_mode == AR5K_ANTMODE_SECTOR_AP)
		antenna = ah->bsent & 4 ? 2 : 1;


	/* FIXME: If we are in g mode and rate is a CCK rate
	 * subtract ah->ah_txघातer.txp_cck_ofdm_pwr_delta
	 * from tx घातer (value is in dB units alपढ़ोy) */
	ds->ds_data = bf->skbaddr;
	ret = ah->ah_setup_tx_desc(ah, ds, skb->len,
			ieee80211_get_hdrlen_from_skb(skb), padsize,
			AR5K_PKT_TYPE_BEACON,
			(ah->ah_txघातer.txp_requested * 2),
			ieee80211_get_tx_rate(ah->hw, info)->hw_value,
			1, AR5K_TXKEYIX_INVALID,
			antenna, flags, 0, 0);
	अगर (ret)
		जाओ err_unmap;

	वापस 0;
err_unmap:
	dma_unmap_single(ah->dev, bf->skbaddr, skb->len, DMA_TO_DEVICE);
	वापस ret;
पूर्ण

/*
 * Updates the beacon that is sent by ath5k_beacon_send.  For adhoc,
 * this is called only once at config_bss समय, क्रम AP we करो it every
 * SWBA पूर्णांकerrupt so that the TIM will reflect buffered frames.
 *
 * Called with the beacon lock.
 */
पूर्णांक
ath5k_beacon_update(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक ret;
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath5k_vअगर *avf;
	काष्ठा sk_buff *skb;

	अगर (WARN_ON(!vअगर)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	skb = ieee80211_beacon_get(hw, vअगर);

	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	avf = (व्योम *)vअगर->drv_priv;
	ath5k_txbuf_मुक्त_skb(ah, avf->bbuf);
	avf->bbuf->skb = skb;
	ret = ath5k_beacon_setup(ah, avf->bbuf);
out:
	वापस ret;
पूर्ण

/*
 * Transmit a beacon frame at SWBA.  Dynamic updates to the
 * frame contents are करोne as needed and the slot समय is
 * also adjusted based on current state.
 *
 * This is called from software irq context (beacontq tasklets)
 * or user context from ath5k_beacon_config.
 */
अटल व्योम
ath5k_beacon_send(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ath5k_vअगर *avf;
	काष्ठा ath5k_buf *bf;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON, "in beacon_send\n");

	/*
	 * Check अगर the previous beacon has gone out.  If
	 * not, करोn't don't try to post another: skip this
	 * period and रुको क्रम the next.  Missed beacons
	 * indicate a problem and should not occur.  If we
	 * miss too many consecutive beacons reset the device.
	 */
	अगर (unlikely(ath5k_hw_num_tx_pending(ah, ah->bhalq) != 0)) अणु
		ah->bmisscount++;
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"missed %u consecutive beacons\n", ah->bmisscount);
		अगर (ah->bmisscount > 10) अणु	/* NB: 10 is a guess */
			ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
				"stuck beacon time (%u missed)\n",
				ah->bmisscount);
			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				  "stuck beacon, resetting\n");
			ieee80211_queue_work(ah->hw, &ah->reset_work);
		पूर्ण
		वापस;
	पूर्ण
	अगर (unlikely(ah->bmisscount != 0)) अणु
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"resume beacon xmit after %u misses\n",
			ah->bmisscount);
		ah->bmisscount = 0;
	पूर्ण

	अगर ((ah->opmode == NL80211_IFTYPE_AP && ah->num_ap_vअगरs +
			ah->num_mesh_vअगरs > 1) ||
			ah->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		u64 tsf = ath5k_hw_get_tsf64(ah);
		u32 tsftu = TSF_TO_TU(tsf);
		पूर्णांक slot = ((tsftu % ah->bपूर्णांकval) * ATH_BCBUF) / ah->bपूर्णांकval;
		vअगर = ah->bslot[(slot + 1) % ATH_BCBUF];
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"tsf %llx tsftu %x intval %u slot %u vif %p\n",
			(अचिन्हित दीर्घ दीर्घ)tsf, tsftu, ah->bपूर्णांकval, slot, vअगर);
	पूर्ण अन्यथा /* only one पूर्णांकerface */
		vअगर = ah->bslot[0];

	अगर (!vअगर)
		वापस;

	avf = (व्योम *)vअगर->drv_priv;
	bf = avf->bbuf;

	/*
	 * Stop any current dma and put the new frame on the queue.
	 * This should never fail since we check above that no frames
	 * are still pending on the queue.
	 */
	अगर (unlikely(ath5k_hw_stop_beacon_queue(ah, ah->bhalq))) अणु
		ATH5K_WARN(ah, "beacon queue %u didn't start/stop ?\n", ah->bhalq);
		/* NB: hw still stops DMA, so proceed */
	पूर्ण

	/* refresh the beacon क्रम AP or MESH mode */
	अगर (ah->opmode == NL80211_IFTYPE_AP ||
	    ah->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		err = ath5k_beacon_update(ah->hw, vअगर);
		अगर (err)
			वापस;
	पूर्ण

	अगर (unlikely(bf->skb == शून्य || ah->opmode == NL80211_IFTYPE_STATION ||
		     ah->opmode == NL80211_IFTYPE_MONITOR)) अणु
		ATH5K_WARN(ah, "bf=%p bf_skb=%p\n", bf, bf->skb);
		वापस;
	पूर्ण

	trace_ath5k_tx(ah, bf->skb, &ah->txqs[ah->bhalq]);

	ath5k_hw_set_txdp(ah, ah->bhalq, bf->daddr);
	ath5k_hw_start_tx_dma(ah, ah->bhalq);
	ATH5K_DBG(ah, ATH5K_DEBUG_BEACON, "TXDP[%u] = %llx (%p)\n",
		ah->bhalq, (अचिन्हित दीर्घ दीर्घ)bf->daddr, bf->desc);

	skb = ieee80211_get_buffered_bc(ah->hw, vअगर);
	जबतक (skb) अणु
		ath5k_tx_queue(ah->hw, skb, ah->cabq, शून्य);

		अगर (ah->cabq->txq_len >= ah->cabq->txq_max)
			अवरोध;

		skb = ieee80211_get_buffered_bc(ah->hw, vअगर);
	पूर्ण

	ah->bsent++;
पूर्ण

/**
 * ath5k_beacon_update_समयrs - update beacon समयrs
 *
 * @ah: काष्ठा ath5k_hw poपूर्णांकer we are operating on
 * @bc_tsf: the बारtamp of the beacon. 0 to reset the TSF. -1 to perक्रमm a
 *          beacon समयr update based on the current HW TSF.
 *
 * Calculate the next target beacon transmit समय (TBTT) based on the बारtamp
 * of a received beacon or the current local hardware TSF and ग_लिखो it to the
 * beacon समयr रेजिस्टरs.
 *
 * This is called in a variety of situations, e.g. when a beacon is received,
 * when a TSF update has been detected, but also when an new IBSS is created or
 * when we otherwise know we have to update the समयrs, but we keep it in this
 * function to have it all together in one place.
 */
व्योम
ath5k_beacon_update_समयrs(काष्ठा ath5k_hw *ah, u64 bc_tsf)
अणु
	u32 nexttbtt, पूर्णांकval, hw_tu, bc_tu;
	u64 hw_tsf;

	पूर्णांकval = ah->bपूर्णांकval & AR5K_BEACON_PERIOD;
	अगर (ah->opmode == NL80211_IFTYPE_AP && ah->num_ap_vअगरs
		+ ah->num_mesh_vअगरs > 1) अणु
		पूर्णांकval /= ATH_BCBUF;	/* staggered multi-bss beacons */
		अगर (पूर्णांकval < 15)
			ATH5K_WARN(ah, "intval %u is too low, min 15\n",
				   पूर्णांकval);
	पूर्ण
	अगर (WARN_ON(!पूर्णांकval))
		वापस;

	/* beacon TSF converted to TU */
	bc_tu = TSF_TO_TU(bc_tsf);

	/* current TSF converted to TU */
	hw_tsf = ath5k_hw_get_tsf64(ah);
	hw_tu = TSF_TO_TU(hw_tsf);

#घोषणा FUDGE (AR5K_TUNE_SW_BEACON_RESP + 3)
	/* We use FUDGE to make sure the next TBTT is ahead of the current TU.
	 * Since we later subtract AR5K_TUNE_SW_BEACON_RESP (10) in the समयr
	 * configuration we need to make sure it is bigger than that. */

	अगर (bc_tsf == -1) अणु
		/*
		 * no beacons received, called पूर्णांकernally.
		 * just need to refresh समयrs based on HW TSF.
		 */
		nexttbtt = roundup(hw_tu + FUDGE, पूर्णांकval);
	पूर्ण अन्यथा अगर (bc_tsf == 0) अणु
		/*
		 * no beacon received, probably called by ath5k_reset_tsf().
		 * reset TSF to start with 0.
		 */
		nexttbtt = पूर्णांकval;
		पूर्णांकval |= AR5K_BEACON_RESET_TSF;
	पूर्ण अन्यथा अगर (bc_tsf > hw_tsf) अणु
		/*
		 * beacon received, SW merge happened but HW TSF not yet updated.
		 * not possible to reconfigure समयrs yet, but next समय we
		 * receive a beacon with the same BSSID, the hardware will
		 * स्वतःmatically update the TSF and then we need to reconfigure
		 * the समयrs.
		 */
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"need to wait for HW TSF sync\n");
		वापस;
	पूर्ण अन्यथा अणु
		/*
		 * most important हाल क्रम beacon synchronization between STA.
		 *
		 * beacon received and HW TSF has been alपढ़ोy updated by HW.
		 * update next TBTT based on the TSF of the beacon, but make
		 * sure it is ahead of our local TSF समयr.
		 */
		nexttbtt = bc_tu + roundup(hw_tu + FUDGE - bc_tu, पूर्णांकval);
	पूर्ण
#अघोषित FUDGE

	ah->nexttbtt = nexttbtt;

	पूर्णांकval |= AR5K_BEACON_ENA;
	ath5k_hw_init_beacon_समयrs(ah, nexttbtt, पूर्णांकval);

	/*
	 * debugging output last in order to preserve the समय critical aspect
	 * of this function
	 */
	अगर (bc_tsf == -1)
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"reconfigured timers based on HW TSF\n");
	अन्यथा अगर (bc_tsf == 0)
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"reset HW TSF and timers\n");
	अन्यथा
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"updated timers based on beacon TSF\n");

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			  "bc_tsf %llx hw_tsf %llx bc_tu %u hw_tu %u nexttbtt %u\n",
			  (अचिन्हित दीर्घ दीर्घ) bc_tsf,
			  (अचिन्हित दीर्घ दीर्घ) hw_tsf, bc_tu, hw_tu, nexttbtt);
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON, "intval %u %s %s\n",
		पूर्णांकval & AR5K_BEACON_PERIOD,
		पूर्णांकval & AR5K_BEACON_ENA ? "AR5K_BEACON_ENA" : "",
		पूर्णांकval & AR5K_BEACON_RESET_TSF ? "AR5K_BEACON_RESET_TSF" : "");
पूर्ण

/**
 * ath5k_beacon_config - Configure the beacon queues and पूर्णांकerrupts
 *
 * @ah: काष्ठा ath5k_hw poपूर्णांकer we are operating on
 *
 * In IBSS mode we use a self-linked tx descriptor अगर possible. We enable SWBA
 * पूर्णांकerrupts to detect TSF updates only.
 */
व्योम
ath5k_beacon_config(काष्ठा ath5k_hw *ah)
अणु
	spin_lock_bh(&ah->block);
	ah->bmisscount = 0;
	ah->imask &= ~(AR5K_INT_BMISS | AR5K_INT_SWBA);

	अगर (ah->enable_beacon) अणु
		/*
		 * In IBSS mode we use a self-linked tx descriptor and let the
		 * hardware send the beacons स्वतःmatically. We have to load it
		 * only once here.
		 * We use the SWBA पूर्णांकerrupt only to keep track of the beacon
		 * समयrs in order to detect स्वतःmatic TSF updates.
		 */
		ath5k_beaconq_config(ah);

		ah->imask |= AR5K_INT_SWBA;

		अगर (ah->opmode == NL80211_IFTYPE_ADHOC) अणु
			अगर (ath5k_hw_hasveol(ah))
				ath5k_beacon_send(ah);
		पूर्ण अन्यथा
			ath5k_beacon_update_समयrs(ah, -1);
	पूर्ण अन्यथा अणु
		ath5k_hw_stop_beacon_queue(ah, ah->bhalq);
	पूर्ण

	ath5k_hw_set_imr(ah, ah->imask);
	spin_unlock_bh(&ah->block);
पूर्ण

अटल व्योम ath5k_tasklet_beacon(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath5k_hw *ah = from_tasklet(ah, t, beacontq);

	/*
	 * Software beacon alert--समय to send a beacon.
	 *
	 * In IBSS mode we use this पूर्णांकerrupt just to
	 * keep track of the next TBTT (target beacon
	 * transmission समय) in order to detect whether
	 * स्वतःmatic TSF updates happened.
	 */
	अगर (ah->opmode == NL80211_IFTYPE_ADHOC) अणु
		/* XXX: only अगर VEOL supported */
		u64 tsf = ath5k_hw_get_tsf64(ah);
		ah->nexttbtt += ah->bपूर्णांकval;
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
				"SWBA nexttbtt: %x hw_tu: %x "
				"TSF: %llx\n",
				ah->nexttbtt,
				TSF_TO_TU(tsf),
				(अचिन्हित दीर्घ दीर्घ) tsf);
	पूर्ण अन्यथा अणु
		spin_lock(&ah->block);
		ath5k_beacon_send(ah);
		spin_unlock(&ah->block);
	पूर्ण
पूर्ण


/********************\
* Interrupt handling *
\********************/

अटल व्योम
ath5k_पूर्णांकr_calibration_poll(काष्ठा ath5k_hw *ah)
अणु
	अगर (समय_is_beक्रमe_eq_jअगरfies(ah->ah_cal_next_ani) &&
	   !(ah->ah_cal_mask & AR5K_CALIBRATION_FULL) &&
	   !(ah->ah_cal_mask & AR5K_CALIBRATION_SHORT)) अणु

		/* Run ANI only when calibration is not active */

		ah->ah_cal_next_ani = jअगरfies +
			msecs_to_jअगरfies(ATH5K_TUNE_CALIBRATION_INTERVAL_ANI);
		tasklet_schedule(&ah->ani_tasklet);

	पूर्ण अन्यथा अगर (समय_is_beक्रमe_eq_jअगरfies(ah->ah_cal_next_लघु) &&
		!(ah->ah_cal_mask & AR5K_CALIBRATION_FULL) &&
		!(ah->ah_cal_mask & AR5K_CALIBRATION_SHORT)) अणु

		/* Run calibration only when another calibration
		 * is not running.
		 *
		 * Note: This is क्रम both full/लघु calibration,
		 * अगर it's समय क्रम a full one, ath5k_calibrate_work will deal
		 * with it. */

		ah->ah_cal_next_लघु = jअगरfies +
			msecs_to_jअगरfies(ATH5K_TUNE_CALIBRATION_INTERVAL_SHORT);
		ieee80211_queue_work(ah->hw, &ah->calib_work);
	पूर्ण
	/* we could use SWI to generate enough पूर्णांकerrupts to meet our
	 * calibration पूर्णांकerval requirements, अगर necessary:
	 * AR5K_REG_ENABLE_BITS(ah, AR5K_CR, AR5K_CR_SWI); */
पूर्ण

अटल व्योम
ath5k_schedule_rx(काष्ठा ath5k_hw *ah)
अणु
	ah->rx_pending = true;
	tasklet_schedule(&ah->rxtq);
पूर्ण

अटल व्योम
ath5k_schedule_tx(काष्ठा ath5k_hw *ah)
अणु
	ah->tx_pending = true;
	tasklet_schedule(&ah->txtq);
पूर्ण

अटल irqवापस_t
ath5k_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ath5k_hw *ah = dev_id;
	क्रमागत ath5k_पूर्णांक status;
	अचिन्हित पूर्णांक counter = 1000;


	/*
	 * If hw is not पढ़ोy (or detached) and we get an
	 * पूर्णांकerrupt, or अगर we have no पूर्णांकerrupts pending
	 * (that means it's not क्रम us) skip it.
	 *
	 * NOTE: Group 0/1 PCI पूर्णांकerface रेजिस्टरs are not
	 * supported on WiSOCs, so we can't check क्रम pending
	 * पूर्णांकerrupts (ISR beदीर्घs to another रेजिस्टर group
	 * so we are ok).
	 */
	अगर (unlikely(test_bit(ATH_STAT_INVALID, ah->status) ||
			((ath5k_get_bus_type(ah) != ATH_AHB) &&
			!ath5k_hw_is_पूर्णांकr_pending(ah))))
		वापस IRQ_NONE;

	/** Main loop **/
	करो अणु
		ath5k_hw_get_isr(ah, &status);	/* NB: clears IRQ too */

		ATH5K_DBG(ah, ATH5K_DEBUG_INTR, "status 0x%x/0x%x\n",
				status, ah->imask);

		/*
		 * Fatal hw error -> Log and reset
		 *
		 * Fatal errors are unrecoverable so we have to
		 * reset the card. These errors include bus and
		 * dma errors.
		 */
		अगर (unlikely(status & AR5K_INT_FATAL)) अणु

			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				  "fatal int, resetting\n");
			ieee80211_queue_work(ah->hw, &ah->reset_work);

		/*
		 * RX Overrun -> Count and reset अगर needed
		 *
		 * Receive buffers are full. Either the bus is busy or
		 * the CPU is not fast enough to process all received
		 * frames.
		 */
		पूर्ण अन्यथा अगर (unlikely(status & AR5K_INT_RXORN)) अणु

			/*
			 * Older chipsets need a reset to come out of this
			 * condition, but we treat it as RX क्रम newer chips.
			 * We करोn't know exactly which versions need a reset
			 * this guess is copied from the HAL.
			 */
			ah->stats.rxorn_पूर्णांकr++;

			अगर (ah->ah_mac_srev < AR5K_SREV_AR5212) अणु
				ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
					  "rx overrun, resetting\n");
				ieee80211_queue_work(ah->hw, &ah->reset_work);
			पूर्ण अन्यथा
				ath5k_schedule_rx(ah);

		पूर्ण अन्यथा अणु

			/* Software Beacon Alert -> Schedule beacon tasklet */
			अगर (status & AR5K_INT_SWBA)
				tasklet_hi_schedule(&ah->beacontq);

			/*
			 * No more RX descriptors -> Just count
			 *
			 * NB: the hardware should re-पढ़ो the link when
			 *     RXE bit is written, but it करोesn't work at
			 *     least on older hardware revs.
			 */
			अगर (status & AR5K_INT_RXEOL)
				ah->stats.rxeol_पूर्णांकr++;


			/* TX Underrun -> Bump tx trigger level */
			अगर (status & AR5K_INT_TXURN)
				ath5k_hw_update_tx_triglevel(ah, true);

			/* RX -> Schedule rx tasklet */
			अगर (status & (AR5K_INT_RXOK | AR5K_INT_RXERR))
				ath5k_schedule_rx(ah);

			/* TX -> Schedule tx tasklet */
			अगर (status & (AR5K_INT_TXOK
					| AR5K_INT_TXDESC
					| AR5K_INT_TXERR
					| AR5K_INT_TXEOL))
				ath5k_schedule_tx(ah);

			/* Missed beacon -> TODO
			अगर (status & AR5K_INT_BMISS)
			*/

			/* MIB event -> Update counters and notअगरy ANI */
			अगर (status & AR5K_INT_MIB) अणु
				ah->stats.mib_पूर्णांकr++;
				ath5k_hw_update_mib_counters(ah);
				ath5k_ani_mib_पूर्णांकr(ah);
			पूर्ण

			/* GPIO -> Notअगरy RFKill layer */
			अगर (status & AR5K_INT_GPIO)
				tasklet_schedule(&ah->rf_समाप्त.toggleq);

		पूर्ण

		अगर (ath5k_get_bus_type(ah) == ATH_AHB)
			अवरोध;

	पूर्ण जबतक (ath5k_hw_is_पूर्णांकr_pending(ah) && --counter > 0);

	/*
	 * Until we handle rx/tx पूर्णांकerrupts mask them on IMR
	 *
	 * NOTE: ah->(rx/tx)_pending are set when scheduling the tasklets
	 * and unset after we 've handled the पूर्णांकerrupts.
	 */
	अगर (ah->rx_pending || ah->tx_pending)
		ath5k_set_current_imask(ah);

	अगर (unlikely(!counter))
		ATH5K_WARN(ah, "too many interrupts, giving up for now\n");

	/* Fire up calibration poll */
	ath5k_पूर्णांकr_calibration_poll(ah);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Periodically recalibrate the PHY to account
 * क्रम temperature/environment changes.
 */
अटल व्योम
ath5k_calibrate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath5k_hw *ah = container_of(work, काष्ठा ath5k_hw,
		calib_work);

	/* Should we run a full calibration ? */
	अगर (समय_is_beक्रमe_eq_jअगरfies(ah->ah_cal_next_full)) अणु

		ah->ah_cal_next_full = jअगरfies +
			msecs_to_jअगरfies(ATH5K_TUNE_CALIBRATION_INTERVAL_FULL);
		ah->ah_cal_mask |= AR5K_CALIBRATION_FULL;

		ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
				"running full calibration\n");

		अगर (ath5k_hw_gainf_calibrate(ah) == AR5K_RFGAIN_NEED_CHANGE) अणु
			/*
			 * Rfgain is out of bounds, reset the chip
			 * to load new gain values.
			 */
			ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
					"got new rfgain, resetting\n");
			ieee80211_queue_work(ah->hw, &ah->reset_work);
		पूर्ण
	पूर्ण अन्यथा
		ah->ah_cal_mask |= AR5K_CALIBRATION_SHORT;


	ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE, "channel %u/%x\n",
		ieee80211_frequency_to_channel(ah->curchan->center_freq),
		ah->curchan->hw_value);

	अगर (ath5k_hw_phy_calibrate(ah, ah->curchan))
		ATH5K_ERR(ah, "calibration of channel %u failed\n",
			ieee80211_frequency_to_channel(
				ah->curchan->center_freq));

	/* Clear calibration flags */
	अगर (ah->ah_cal_mask & AR5K_CALIBRATION_FULL)
		ah->ah_cal_mask &= ~AR5K_CALIBRATION_FULL;
	अन्यथा अगर (ah->ah_cal_mask & AR5K_CALIBRATION_SHORT)
		ah->ah_cal_mask &= ~AR5K_CALIBRATION_SHORT;
पूर्ण


अटल व्योम
ath5k_tasklet_ani(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath5k_hw *ah = from_tasklet(ah, t, ani_tasklet);

	ah->ah_cal_mask |= AR5K_CALIBRATION_ANI;
	ath5k_ani_calibration(ah);
	ah->ah_cal_mask &= ~AR5K_CALIBRATION_ANI;
पूर्ण


अटल व्योम
ath5k_tx_complete_poll_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath5k_hw *ah = container_of(work, काष्ठा ath5k_hw,
			tx_complete_work.work);
	काष्ठा ath5k_txq *txq;
	पूर्णांक i;
	bool needreset = false;

	अगर (!test_bit(ATH_STAT_STARTED, ah->status))
		वापस;

	mutex_lock(&ah->lock);

	क्रम (i = 0; i < ARRAY_SIZE(ah->txqs); i++) अणु
		अगर (ah->txqs[i].setup) अणु
			txq = &ah->txqs[i];
			spin_lock_bh(&txq->lock);
			अगर (txq->txq_len > 1) अणु
				अगर (txq->txq_poll_mark) अणु
					ATH5K_DBG(ah, ATH5K_DEBUG_XMIT,
						  "TX queue stuck %d\n",
						  txq->qnum);
					needreset = true;
					txq->txq_stuck++;
					spin_unlock_bh(&txq->lock);
					अवरोध;
				पूर्ण अन्यथा अणु
					txq->txq_poll_mark = true;
				पूर्ण
			पूर्ण
			spin_unlock_bh(&txq->lock);
		पूर्ण
	पूर्ण

	अगर (needreset) अणु
		ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
			  "TX queues stuck, resetting\n");
		ath5k_reset(ah, शून्य, true);
	पूर्ण

	mutex_unlock(&ah->lock);

	ieee80211_queue_delayed_work(ah->hw, &ah->tx_complete_work,
		msecs_to_jअगरfies(ATH5K_TX_COMPLETE_POLL_INT));
पूर्ण


/*************************\
* Initialization routines *
\*************************/

अटल स्थिर काष्ठा ieee80211_अगरace_limit अगर_limits[] = अणु
	अणु .max = 2048,	.types = BIT(NL80211_IFTYPE_STATION) पूर्ण,
	अणु .max = 4,	.types =
#अगर_घोषित CONFIG_MAC80211_MESH
				 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
				 BIT(NL80211_IFTYPE_AP) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb = अणु
	.limits = अगर_limits,
	.n_limits = ARRAY_SIZE(अगर_limits),
	.max_पूर्णांकerfaces = 2048,
	.num_dअगरferent_channels = 1,
पूर्ण;

पूर्णांक
ath5k_init_ah(काष्ठा ath5k_hw *ah, स्थिर काष्ठा ath_bus_ops *bus_ops)
अणु
	काष्ठा ieee80211_hw *hw = ah->hw;
	काष्ठा ath_common *common;
	पूर्णांक ret;
	पूर्णांक csz;

	/* Initialize driver निजी data */
	SET_IEEE80211_DEV(hw, ah->dev);
	ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);

	hw->wiphy->पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) |
		BIT(NL80211_IFTYPE_MESH_POINT);

	hw->wiphy->अगरace_combinations = &अगर_comb;
	hw->wiphy->n_अगरace_combinations = 1;

	/* SW support क्रम IBSS_RSN is provided by mac80211 */
	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_5_10_MHZ;

	/* both antennas can be configured as RX or TX */
	hw->wiphy->available_antennas_tx = 0x3;
	hw->wiphy->available_antennas_rx = 0x3;

	hw->extra_tx_headroom = 2;

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	/*
	 * Mark the device as detached to aव्योम processing
	 * पूर्णांकerrupts until setup is complete.
	 */
	__set_bit(ATH_STAT_INVALID, ah->status);

	ah->opmode = NL80211_IFTYPE_STATION;
	ah->bपूर्णांकval = 1000;
	mutex_init(&ah->lock);
	spin_lock_init(&ah->rxbuflock);
	spin_lock_init(&ah->txbuflock);
	spin_lock_init(&ah->block);
	spin_lock_init(&ah->irqlock);

	/* Setup पूर्णांकerrupt handler */
	ret = request_irq(ah->irq, ath5k_पूर्णांकr, IRQF_SHARED, "ath", ah);
	अगर (ret) अणु
		ATH5K_ERR(ah, "request_irq failed\n");
		जाओ err;
	पूर्ण

	common = ath5k_hw_common(ah);
	common->ops = &ath5k_common_ops;
	common->bus_ops = bus_ops;
	common->ah = ah;
	common->hw = hw;
	common->priv = ah;
	common->घड़ीrate = 40;

	/*
	 * Cache line size is used to size and align various
	 * काष्ठाures used to communicate with the hardware.
	 */
	ath5k_पढ़ो_cachesize(common, &csz);
	common->cachelsz = csz << 2; /* convert to bytes */

	spin_lock_init(&common->cc_lock);

	/* Initialize device */
	ret = ath5k_hw_init(ah);
	अगर (ret)
		जाओ err_irq;

	/* Set up multi-rate retry capabilities */
	अगर (ah->ah_capabilities.cap_has_mrr_support) अणु
		hw->max_rates = 4;
		hw->max_rate_tries = max(AR5K_INIT_RETRY_SHORT,
					 AR5K_INIT_RETRY_LONG);
	पूर्ण

	hw->vअगर_data_size = माप(काष्ठा ath5k_vअगर);

	/* Finish निजी driver data initialization */
	ret = ath5k_init(hw);
	अगर (ret)
		जाओ err_ah;

	ATH5K_INFO(ah, "Atheros AR%s chip found (MAC: 0x%x, PHY: 0x%x)\n",
			ath5k_chip_name(AR5K_VERSION_MAC, ah->ah_mac_srev),
					ah->ah_mac_srev,
					ah->ah_phy_revision);

	अगर (!ah->ah_single_chip) अणु
		/* Single chip radio (!RF5111) */
		अगर (ah->ah_radio_5ghz_revision &&
			!ah->ah_radio_2ghz_revision) अणु
			/* No 5GHz support -> report 2GHz radio */
			अगर (!test_bit(AR5K_MODE_11A,
				ah->ah_capabilities.cap_mode)) अणु
				ATH5K_INFO(ah, "RF%s 2GHz radio found (0x%x)\n",
					ath5k_chip_name(AR5K_VERSION_RAD,
						ah->ah_radio_5ghz_revision),
						ah->ah_radio_5ghz_revision);
			/* No 2GHz support (5110 and some
			 * 5GHz only cards) -> report 5GHz radio */
			पूर्ण अन्यथा अगर (!test_bit(AR5K_MODE_11B,
				ah->ah_capabilities.cap_mode)) अणु
				ATH5K_INFO(ah, "RF%s 5GHz radio found (0x%x)\n",
					ath5k_chip_name(AR5K_VERSION_RAD,
						ah->ah_radio_5ghz_revision),
						ah->ah_radio_5ghz_revision);
			/* Multiband radio */
			पूर्ण अन्यथा अणु
				ATH5K_INFO(ah, "RF%s multiband radio found"
					" (0x%x)\n",
					ath5k_chip_name(AR5K_VERSION_RAD,
						ah->ah_radio_5ghz_revision),
						ah->ah_radio_5ghz_revision);
			पूर्ण
		पूर्ण
		/* Multi chip radio (RF5111 - RF2111) ->
		 * report both 2GHz/5GHz radios */
		अन्यथा अगर (ah->ah_radio_5ghz_revision &&
				ah->ah_radio_2ghz_revision) अणु
			ATH5K_INFO(ah, "RF%s 5GHz radio found (0x%x)\n",
				ath5k_chip_name(AR5K_VERSION_RAD,
					ah->ah_radio_5ghz_revision),
					ah->ah_radio_5ghz_revision);
			ATH5K_INFO(ah, "RF%s 2GHz radio found (0x%x)\n",
				ath5k_chip_name(AR5K_VERSION_RAD,
					ah->ah_radio_2ghz_revision),
					ah->ah_radio_2ghz_revision);
		पूर्ण
	पूर्ण

	ath5k_debug_init_device(ah);

	/* पढ़ोy to process पूर्णांकerrupts */
	__clear_bit(ATH_STAT_INVALID, ah->status);

	वापस 0;
err_ah:
	ath5k_hw_deinit(ah);
err_irq:
	मुक्त_irq(ah->irq, ah);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक
ath5k_stop_locked(काष्ठा ath5k_hw *ah)
अणु

	ATH5K_DBG(ah, ATH5K_DEBUG_RESET, "invalid %u\n",
			test_bit(ATH_STAT_INVALID, ah->status));

	/*
	 * Shutकरोwn the hardware and driver:
	 *    stop output from above
	 *    disable पूर्णांकerrupts
	 *    turn off समयrs
	 *    turn off the radio
	 *    clear transmit machinery
	 *    clear receive machinery
	 *    drain and release tx queues
	 *    reclaim beacon resources
	 *    घातer करोwn hardware
	 *
	 * Note that some of this work is not possible अगर the
	 * hardware is gone (invalid).
	 */
	ieee80211_stop_queues(ah->hw);

	अगर (!test_bit(ATH_STAT_INVALID, ah->status)) अणु
		ath5k_led_off(ah);
		ath5k_hw_set_imr(ah, 0);
		synchronize_irq(ah->irq);
		ath5k_rx_stop(ah);
		ath5k_hw_dma_stop(ah);
		ath5k_drain_tx_buffs(ah);
		ath5k_hw_phy_disable(ah);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath5k_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	पूर्णांक ret, i;

	mutex_lock(&ah->lock);

	ATH5K_DBG(ah, ATH5K_DEBUG_RESET, "mode %d\n", ah->opmode);

	/*
	 * Stop anything previously setup.  This is safe
	 * no matter this is the first समय through or not.
	 */
	ath5k_stop_locked(ah);

	/*
	 * The basic पूर्णांकerface to setting the hardware in a good
	 * state is ``reset''.  On वापस the hardware is known to
	 * be घातered up and with पूर्णांकerrupts disabled.  This must
	 * be followed by initialization of the appropriate bits
	 * and then setup of the पूर्णांकerrupt mask.
	 */
	ah->curchan = ah->hw->conf.chandef.chan;
	ah->imask = AR5K_INT_RXOK
		| AR5K_INT_RXERR
		| AR5K_INT_RXEOL
		| AR5K_INT_RXORN
		| AR5K_INT_TXDESC
		| AR5K_INT_TXEOL
		| AR5K_INT_FATAL
		| AR5K_INT_GLOBAL
		| AR5K_INT_MIB;

	ret = ath5k_reset(ah, शून्य, false);
	अगर (ret)
		जाओ करोne;

	अगर (!ath5k_modparam_no_hw_rfसमाप्त_चयन)
		ath5k_rfसमाप्त_hw_start(ah);

	/*
	 * Reset the key cache since some parts करो not reset the
	 * contents on initial घातer up or resume from suspend.
	 */
	क्रम (i = 0; i < common->keymax; i++)
		ath_hw_keyreset(common, (u16) i);

	/* Use higher rates क्रम acks instead of base
	 * rate */
	ah->ah_ack_bitrate_high = true;

	क्रम (i = 0; i < ARRAY_SIZE(ah->bslot); i++)
		ah->bslot[i] = शून्य;

	ret = 0;
करोne:
	mutex_unlock(&ah->lock);

	set_bit(ATH_STAT_STARTED, ah->status);
	ieee80211_queue_delayed_work(ah->hw, &ah->tx_complete_work,
			msecs_to_jअगरfies(ATH5K_TX_COMPLETE_POLL_INT));

	वापस ret;
पूर्ण

अटल व्योम ath5k_stop_tasklets(काष्ठा ath5k_hw *ah)
अणु
	ah->rx_pending = false;
	ah->tx_pending = false;
	tasklet_समाप्त(&ah->rxtq);
	tasklet_समाप्त(&ah->txtq);
	tasklet_समाप्त(&ah->beacontq);
	tasklet_समाप्त(&ah->ani_tasklet);
पूर्ण

/*
 * Stop the device, grabbing the top-level lock to protect
 * against concurrent entry through ath5k_init (which can happen
 * अगर another thपढ़ो करोes a प्रणाली call and the thपढ़ो करोing the
 * stop is preempted).
 */
व्योम ath5k_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	पूर्णांक ret;

	mutex_lock(&ah->lock);
	ret = ath5k_stop_locked(ah);
	अगर (ret == 0 && !test_bit(ATH_STAT_INVALID, ah->status)) अणु
		/*
		 * Don't set the card in full sleep mode!
		 *
		 * a) When the device is in this state it must be carefully
		 * woken up or references to रेजिस्टरs in the PCI घड़ी
		 * करोमुख्य may मुक्तze the bus (and प्रणाली).  This varies
		 * by chip and is mostly an issue with newer parts
		 * (madwअगरi sources mentioned srev >= 0x78) that go to
		 * sleep more quickly.
		 *
		 * b) On older chips full sleep results a weird behaviour
		 * during wakeup. I tested various cards with srev < 0x78
		 * and they करोn't wake up after module reload, a second
		 * module reload is needed to bring the card up again.
		 *
		 * Until we figure out what's going on don't enable
		 * full chip reset on any chip (this is what Legacy HAL
		 * and Sam's HAL करो anyway). Instead Perक्रमm a full reset
		 * on the device (same as initial state after attach) and
		 * leave it idle (keep MAC/BB on warm reset) */
		ret = ath5k_hw_on_hold(ah);

		ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
				"putting device to sleep\n");
	पूर्ण

	mutex_unlock(&ah->lock);

	ath5k_stop_tasklets(ah);

	clear_bit(ATH_STAT_STARTED, ah->status);
	cancel_delayed_work_sync(&ah->tx_complete_work);

	अगर (!ath5k_modparam_no_hw_rfसमाप्त_चयन)
		ath5k_rfसमाप्त_hw_stop(ah);
पूर्ण

/*
 * Reset the hardware.  If chan is not शून्य, then also छोड़ो rx/tx
 * and change to the given channel.
 *
 * This should be called with ah->lock.
 */
अटल पूर्णांक
ath5k_reset(काष्ठा ath5k_hw *ah, काष्ठा ieee80211_channel *chan,
							bool skip_pcu)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	पूर्णांक ret, ani_mode;
	bool fast = chan && modparam_fastchanचयन ? 1 : 0;

	ATH5K_DBG(ah, ATH5K_DEBUG_RESET, "resetting\n");

	__set_bit(ATH_STAT_RESET, ah->status);

	ath5k_hw_set_imr(ah, 0);
	synchronize_irq(ah->irq);
	ath5k_stop_tasklets(ah);

	/* Save ani mode and disable ANI during
	 * reset. If we करोn't we might get false
	 * PHY error पूर्णांकerrupts. */
	ani_mode = ah->ani_state.ani_mode;
	ath5k_ani_init(ah, ATH5K_ANI_MODE_OFF);

	/* We are going to empty hw queues
	 * so we should also मुक्त any reमुख्यing
	 * tx buffers */
	ath5k_drain_tx_buffs(ah);

	/* Stop PCU */
	ath5k_hw_stop_rx_pcu(ah);

	/* Stop DMA
	 *
	 * Note: If DMA didn't stop जारी
	 * since only a reset will fix it.
	 */
	ret = ath5k_hw_dma_stop(ah);

	/* RF Bus grant won't work अगर we have pending
	 * frames
	 */
	अगर (ret && fast) अणु
		ATH5K_DBG(ah, ATH5K_DEBUG_RESET,
			  "DMA didn't stop, falling back to normal reset\n");
		fast = false;
	पूर्ण

	अगर (chan)
		ah->curchan = chan;

	ret = ath5k_hw_reset(ah, ah->opmode, ah->curchan, fast, skip_pcu);
	अगर (ret) अणु
		ATH5K_ERR(ah, "can't reset hardware (%d)\n", ret);
		जाओ err;
	पूर्ण

	ret = ath5k_rx_start(ah);
	अगर (ret) अणु
		ATH5K_ERR(ah, "can't start recv logic\n");
		जाओ err;
	पूर्ण

	ath5k_ani_init(ah, ani_mode);

	/*
	 * Set calibration पूर्णांकervals
	 *
	 * Note: We करोn't need to run calibration imediately
	 * since some initial calibration is करोne on reset
	 * even क्रम fast channel चयनing. Also on scanning
	 * this will get set again and again and it won't get
	 * executed unless we connect somewhere and spend some
	 * समय on the channel (that's what calibration needs
	 * anyway to be accurate).
	 */
	ah->ah_cal_next_full = jअगरfies +
		msecs_to_jअगरfies(ATH5K_TUNE_CALIBRATION_INTERVAL_FULL);
	ah->ah_cal_next_ani = jअगरfies +
		msecs_to_jअगरfies(ATH5K_TUNE_CALIBRATION_INTERVAL_ANI);
	ah->ah_cal_next_लघु = jअगरfies +
		msecs_to_jअगरfies(ATH5K_TUNE_CALIBRATION_INTERVAL_SHORT);

	ewma_beacon_rssi_init(&ah->ah_beacon_rssi_avg);

	/* clear survey data and cycle counters */
	स_रखो(&ah->survey, 0, माप(ah->survey));
	spin_lock_bh(&common->cc_lock);
	ath_hw_cycle_counters_update(common);
	स_रखो(&common->cc_survey, 0, माप(common->cc_survey));
	स_रखो(&common->cc_ani, 0, माप(common->cc_ani));
	spin_unlock_bh(&common->cc_lock);

	/*
	 * Change channels and update the h/w rate map अगर we're चयनing;
	 * e.g. 11a to 11b/g.
	 *
	 * We may be करोing a reset in response to an ioctl that changes the
	 * channel so update any state that might change as a result.
	 *
	 * XXX needed?
	 */
/*	ath5k_chan_change(ah, c); */

	__clear_bit(ATH_STAT_RESET, ah->status);

	ath5k_beacon_config(ah);
	/* पूर्णांकrs are enabled by ath5k_beacon_config */

	ieee80211_wake_queues(ah->hw);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल व्योम ath5k_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath5k_hw *ah = container_of(work, काष्ठा ath5k_hw,
		reset_work);

	mutex_lock(&ah->lock);
	ath5k_reset(ah, शून्य, true);
	mutex_unlock(&ah->lock);
पूर्ण

अटल पूर्णांक
ath5k_init(काष्ठा ieee80211_hw *hw)
अणु

	काष्ठा ath5k_hw *ah = hw->priv;
	काष्ठा ath_regulatory *regulatory = ath5k_hw_regulatory(ah);
	काष्ठा ath5k_txq *txq;
	u8 mac[ETH_ALEN] = अणुपूर्ण;
	पूर्णांक ret;


	/*
	 * Collect the channel list.  The 802.11 layer
	 * is responsible क्रम filtering this list based
	 * on settings like the phy mode and regulatory
	 * करोमुख्य restrictions.
	 */
	ret = ath5k_setup_bands(hw);
	अगर (ret) अणु
		ATH5K_ERR(ah, "can't get channels\n");
		जाओ err;
	पूर्ण

	/*
	 * Allocate tx+rx descriptors and populate the lists.
	 */
	ret = ath5k_desc_alloc(ah);
	अगर (ret) अणु
		ATH5K_ERR(ah, "can't allocate descriptors\n");
		जाओ err;
	पूर्ण

	/*
	 * Allocate hardware transmit queues: one queue क्रम
	 * beacon frames and one data queue क्रम each QoS
	 * priority.  Note that hw functions handle resetting
	 * these queues at the needed समय.
	 */
	ret = ath5k_beaconq_setup(ah);
	अगर (ret < 0) अणु
		ATH5K_ERR(ah, "can't setup a beacon xmit queue\n");
		जाओ err_desc;
	पूर्ण
	ah->bhalq = ret;
	ah->cabq = ath5k_txq_setup(ah, AR5K_TX_QUEUE_CAB, 0);
	अगर (IS_ERR(ah->cabq)) अणु
		ATH5K_ERR(ah, "can't setup cab queue\n");
		ret = PTR_ERR(ah->cabq);
		जाओ err_bhal;
	पूर्ण

	/* 5211 and 5212 usually support 10 queues but we better rely on the
	 * capability inक्रमmation */
	अगर (ah->ah_capabilities.cap_queues.q_tx_num >= 6) अणु
		/* This order matches mac80211's queue priority, so we can
		* directly use the mac80211 queue number without any mapping */
		txq = ath5k_txq_setup(ah, AR5K_TX_QUEUE_DATA, AR5K_WME_AC_VO);
		अगर (IS_ERR(txq)) अणु
			ATH5K_ERR(ah, "can't setup xmit queue\n");
			ret = PTR_ERR(txq);
			जाओ err_queues;
		पूर्ण
		txq = ath5k_txq_setup(ah, AR5K_TX_QUEUE_DATA, AR5K_WME_AC_VI);
		अगर (IS_ERR(txq)) अणु
			ATH5K_ERR(ah, "can't setup xmit queue\n");
			ret = PTR_ERR(txq);
			जाओ err_queues;
		पूर्ण
		txq = ath5k_txq_setup(ah, AR5K_TX_QUEUE_DATA, AR5K_WME_AC_BE);
		अगर (IS_ERR(txq)) अणु
			ATH5K_ERR(ah, "can't setup xmit queue\n");
			ret = PTR_ERR(txq);
			जाओ err_queues;
		पूर्ण
		txq = ath5k_txq_setup(ah, AR5K_TX_QUEUE_DATA, AR5K_WME_AC_BK);
		अगर (IS_ERR(txq)) अणु
			ATH5K_ERR(ah, "can't setup xmit queue\n");
			ret = PTR_ERR(txq);
			जाओ err_queues;
		पूर्ण
		hw->queues = 4;
	पूर्ण अन्यथा अणु
		/* older hardware (5210) can only support one data queue */
		txq = ath5k_txq_setup(ah, AR5K_TX_QUEUE_DATA, AR5K_WME_AC_BE);
		अगर (IS_ERR(txq)) अणु
			ATH5K_ERR(ah, "can't setup xmit queue\n");
			ret = PTR_ERR(txq);
			जाओ err_queues;
		पूर्ण
		hw->queues = 1;
	पूर्ण

	tasklet_setup(&ah->rxtq, ath5k_tasklet_rx);
	tasklet_setup(&ah->txtq, ath5k_tasklet_tx);
	tasklet_setup(&ah->beacontq, ath5k_tasklet_beacon);
	tasklet_setup(&ah->ani_tasklet, ath5k_tasklet_ani);

	INIT_WORK(&ah->reset_work, ath5k_reset_work);
	INIT_WORK(&ah->calib_work, ath5k_calibrate_work);
	INIT_DELAYED_WORK(&ah->tx_complete_work, ath5k_tx_complete_poll_work);

	ret = ath5k_hw_common(ah)->bus_ops->eeprom_पढ़ो_mac(ah, mac);
	अगर (ret) अणु
		ATH5K_ERR(ah, "unable to read address from EEPROM\n");
		जाओ err_queues;
	पूर्ण

	SET_IEEE80211_PERM_ADDR(hw, mac);
	/* All MAC address bits matter क्रम ACKs */
	ath5k_update_bssid_mask_and_opmode(ah, शून्य);

	regulatory->current_rd = ah->ah_capabilities.cap_eeprom.ee_regकरोमुख्य;
	ret = ath_regd_init(regulatory, hw->wiphy, ath5k_reg_notअगरier);
	अगर (ret) अणु
		ATH5K_ERR(ah, "can't initialize regulatory system\n");
		जाओ err_queues;
	पूर्ण

	ret = ieee80211_रेजिस्टर_hw(hw);
	अगर (ret) अणु
		ATH5K_ERR(ah, "can't register ieee80211 hw\n");
		जाओ err_queues;
	पूर्ण

	अगर (!ath_is_world_regd(regulatory))
		regulatory_hपूर्णांक(hw->wiphy, regulatory->alpha2);

	ath5k_init_leds(ah);

	ath5k_sysfs_रेजिस्टर(ah);

	वापस 0;
err_queues:
	ath5k_txq_release(ah);
err_bhal:
	ath5k_hw_release_tx_queue(ah, ah->bhalq);
err_desc:
	ath5k_desc_मुक्त(ah);
err:
	वापस ret;
पूर्ण

व्योम
ath5k_deinit_ah(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ieee80211_hw *hw = ah->hw;

	/*
	 * NB: the order of these is important:
	 * o call the 802.11 layer beक्रमe detaching ath5k_hw to
	 *   ensure callbacks पूर्णांकo the driver to delete global
	 *   key cache entries can be handled
	 * o reclaim the tx queue data काष्ठाures after calling
	 *   the 802.11 layer as we'll get called back to reclaim
	 *   node state and potentially want to use them
	 * o to cleanup the tx queues the hal is called, so detach
	 *   it last
	 * XXX: ??? detach ath5k_hw ???
	 * Other than that, it's straightक्रमward...
	 */
	ieee80211_unरेजिस्टर_hw(hw);
	ath5k_desc_मुक्त(ah);
	ath5k_txq_release(ah);
	ath5k_hw_release_tx_queue(ah, ah->bhalq);
	ath5k_unरेजिस्टर_leds(ah);

	ath5k_sysfs_unरेजिस्टर(ah);
	/*
	 * NB: can't reclaim these until after ieee80211_अगरdetach
	 * वापसs because we'll get called back to reclaim node
	 * state and potentially want to use them.
	 */
	ath5k_hw_deinit(ah);
	मुक्त_irq(ah->irq, ah);
पूर्ण

bool
ath5k_any_vअगर_assoc(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_vअगर_iter_data iter_data;
	iter_data.hw_macaddr = शून्य;
	iter_data.any_assoc = false;
	iter_data.need_set_hw_addr = false;
	iter_data.found_active = true;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		ah->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		ath5k_vअगर_iter, &iter_data);
	वापस iter_data.any_assoc;
पूर्ण

व्योम
ath5k_set_beacon_filter(काष्ठा ieee80211_hw *hw, bool enable)
अणु
	काष्ठा ath5k_hw *ah = hw->priv;
	u32 rfilt;
	rfilt = ath5k_hw_get_rx_filter(ah);
	अगर (enable)
		rfilt |= AR5K_RX_FILTER_BEACON;
	अन्यथा
		rfilt &= ~AR5K_RX_FILTER_BEACON;
	ath5k_hw_set_rx_filter(ah, rfilt);
	ah->filter_flags = rfilt;
पूर्ण

व्योम _ath5k_prपूर्णांकk(स्थिर काष्ठा ath5k_hw *ah, स्थिर अक्षर *level,
		   स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (ah && ah->hw)
		prपूर्णांकk("%s" pr_fmt("%s: %pV"),
		       level, wiphy_name(ah->hw->wiphy), &vaf);
	अन्यथा
		prपूर्णांकk("%s" pr_fmt("%pV"), level, &vaf);

	बहु_पूर्ण(args);
पूर्ण
