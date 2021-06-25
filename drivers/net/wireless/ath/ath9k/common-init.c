<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* We use the hw_value as an index पूर्णांकo our निजी channel काष्ठाure */

#समावेश "common.h"

#घोषणा CHAN2G(_freq, _idx)  अणु \
	.band = NL80211_BAND_2GHZ, \
	.center_freq = (_freq), \
	.hw_value = (_idx), \
	.max_घातer = 20, \
पूर्ण

#घोषणा CHAN5G(_freq, _idx) अणु \
	.band = NL80211_BAND_5GHZ, \
	.center_freq = (_freq), \
	.hw_value = (_idx), \
	.max_घातer = 20, \
पूर्ण

/* Some 2 GHz radios are actually tunable on 2312-2732
 * on 5 MHz steps, we support the channels which we know
 * we have calibration data क्रम all cards though to make
 * this अटल */
अटल स्थिर काष्ठा ieee80211_channel ath9k_2ghz_chantable[] = अणु
	CHAN2G(2412, 0), /* Channel 1 */
	CHAN2G(2417, 1), /* Channel 2 */
	CHAN2G(2422, 2), /* Channel 3 */
	CHAN2G(2427, 3), /* Channel 4 */
	CHAN2G(2432, 4), /* Channel 5 */
	CHAN2G(2437, 5), /* Channel 6 */
	CHAN2G(2442, 6), /* Channel 7 */
	CHAN2G(2447, 7), /* Channel 8 */
	CHAN2G(2452, 8), /* Channel 9 */
	CHAN2G(2457, 9), /* Channel 10 */
	CHAN2G(2462, 10), /* Channel 11 */
	CHAN2G(2467, 11), /* Channel 12 */
	CHAN2G(2472, 12), /* Channel 13 */
	CHAN2G(2484, 13), /* Channel 14 */
पूर्ण;

/* Some 5 GHz radios are actually tunable on XXXX-YYYY
 * on 5 MHz steps, we support the channels which we know
 * we have calibration data क्रम all cards though to make
 * this अटल */
अटल स्थिर काष्ठा ieee80211_channel ath9k_5ghz_chantable[] = अणु
	/* _We_ call this UNII 1 */
	CHAN5G(5180, 14), /* Channel 36 */
	CHAN5G(5200, 15), /* Channel 40 */
	CHAN5G(5220, 16), /* Channel 44 */
	CHAN5G(5240, 17), /* Channel 48 */
	/* _We_ call this UNII 2 */
	CHAN5G(5260, 18), /* Channel 52 */
	CHAN5G(5280, 19), /* Channel 56 */
	CHAN5G(5300, 20), /* Channel 60 */
	CHAN5G(5320, 21), /* Channel 64 */
	/* _We_ call this "Middle band" */
	CHAN5G(5500, 22), /* Channel 100 */
	CHAN5G(5520, 23), /* Channel 104 */
	CHAN5G(5540, 24), /* Channel 108 */
	CHAN5G(5560, 25), /* Channel 112 */
	CHAN5G(5580, 26), /* Channel 116 */
	CHAN5G(5600, 27), /* Channel 120 */
	CHAN5G(5620, 28), /* Channel 124 */
	CHAN5G(5640, 29), /* Channel 128 */
	CHAN5G(5660, 30), /* Channel 132 */
	CHAN5G(5680, 31), /* Channel 136 */
	CHAN5G(5700, 32), /* Channel 140 */
	/* _We_ call this UNII 3 */
	CHAN5G(5745, 33), /* Channel 149 */
	CHAN5G(5765, 34), /* Channel 153 */
	CHAN5G(5785, 35), /* Channel 157 */
	CHAN5G(5805, 36), /* Channel 161 */
	CHAN5G(5825, 37), /* Channel 165 */
पूर्ण;

/* Atheros hardware rate code addition क्रम लघु preamble */
#घोषणा SHPCHECK(__hw_rate, __flags) \
	((__flags & IEEE80211_RATE_SHORT_PREAMBLE) ? (__hw_rate | 0x04 ) : 0)

#घोषणा RATE(_bitrate, _hw_rate, _flags) अणु              \
	.bitrate        = (_bitrate),                   \
	.flags          = (_flags),                     \
	.hw_value       = (_hw_rate),                   \
	.hw_value_लघु = (SHPCHECK(_hw_rate, _flags))  \
पूर्ण

अटल काष्ठा ieee80211_rate ath9k_legacy_rates[] = अणु
	RATE(10, 0x1b, 0),
	RATE(20, 0x1a, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(55, 0x19, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(110, 0x18, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(60, 0x0b, (IEEE80211_RATE_SUPPORTS_5MHZ |
			IEEE80211_RATE_SUPPORTS_10MHZ)),
	RATE(90, 0x0f, (IEEE80211_RATE_SUPPORTS_5MHZ |
			IEEE80211_RATE_SUPPORTS_10MHZ)),
	RATE(120, 0x0a, (IEEE80211_RATE_SUPPORTS_5MHZ |
			 IEEE80211_RATE_SUPPORTS_10MHZ)),
	RATE(180, 0x0e, (IEEE80211_RATE_SUPPORTS_5MHZ |
			 IEEE80211_RATE_SUPPORTS_10MHZ)),
	RATE(240, 0x09, (IEEE80211_RATE_SUPPORTS_5MHZ |
			 IEEE80211_RATE_SUPPORTS_10MHZ)),
	RATE(360, 0x0d, (IEEE80211_RATE_SUPPORTS_5MHZ |
			 IEEE80211_RATE_SUPPORTS_10MHZ)),
	RATE(480, 0x08, (IEEE80211_RATE_SUPPORTS_5MHZ |
			 IEEE80211_RATE_SUPPORTS_10MHZ)),
	RATE(540, 0x0c, (IEEE80211_RATE_SUPPORTS_5MHZ |
			 IEEE80211_RATE_SUPPORTS_10MHZ)),
पूर्ण;

पूर्णांक ath9k_cmn_init_channels_rates(काष्ठा ath_common *common)
अणु
	काष्ठा ath_hw *ah = (काष्ठा ath_hw *)common->ah;
	व्योम *channels;

	BUILD_BUG_ON(ARRAY_SIZE(ath9k_2ghz_chantable) +
		     ARRAY_SIZE(ath9k_5ghz_chantable) !=
		     ATH9K_NUM_CHANNELS);

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ) अणु
		channels = devm_kzalloc(ah->dev,
			माप(ath9k_2ghz_chantable), GFP_KERNEL);
		अगर (!channels)
		    वापस -ENOMEM;

		स_नकल(channels, ath9k_2ghz_chantable,
		       माप(ath9k_2ghz_chantable));
		common->sbands[NL80211_BAND_2GHZ].channels = channels;
		common->sbands[NL80211_BAND_2GHZ].band = NL80211_BAND_2GHZ;
		common->sbands[NL80211_BAND_2GHZ].n_channels =
			ARRAY_SIZE(ath9k_2ghz_chantable);
		common->sbands[NL80211_BAND_2GHZ].bitrates = ath9k_legacy_rates;
		common->sbands[NL80211_BAND_2GHZ].n_bitrates =
			ARRAY_SIZE(ath9k_legacy_rates);
	पूर्ण

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ) अणु
		channels = devm_kzalloc(ah->dev,
			माप(ath9k_5ghz_chantable), GFP_KERNEL);
		अगर (!channels)
			वापस -ENOMEM;

		स_नकल(channels, ath9k_5ghz_chantable,
		       माप(ath9k_5ghz_chantable));
		common->sbands[NL80211_BAND_5GHZ].channels = channels;
		common->sbands[NL80211_BAND_5GHZ].band = NL80211_BAND_5GHZ;
		common->sbands[NL80211_BAND_5GHZ].n_channels =
			ARRAY_SIZE(ath9k_5ghz_chantable);
		common->sbands[NL80211_BAND_5GHZ].bitrates =
			ath9k_legacy_rates + 4;
		common->sbands[NL80211_BAND_5GHZ].n_bitrates =
			ARRAY_SIZE(ath9k_legacy_rates) - 4;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_init_channels_rates);

व्योम ath9k_cmn_setup_ht_cap(काष्ठा ath_hw *ah,
			    काष्ठा ieee80211_sta_ht_cap *ht_info)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u8 tx_streams, rx_streams;
	पूर्णांक i, max_streams;

	ht_info->ht_supported = true;
	ht_info->cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_SM_PS |
		       IEEE80211_HT_CAP_SGI_40 |
		       IEEE80211_HT_CAP_DSSSCCK40;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_LDPC)
		ht_info->cap |= IEEE80211_HT_CAP_LDPC_CODING;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_SGI_20)
		ht_info->cap |= IEEE80211_HT_CAP_SGI_20;

	ht_info->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_info->ampdu_density = IEEE80211_HT_MPDU_DENSITY_8;

	अगर (AR_SREV_9271(ah) || AR_SREV_9330(ah) || AR_SREV_9485(ah) || AR_SREV_9565(ah))
		max_streams = 1;
	अन्यथा अगर (AR_SREV_9462(ah))
		max_streams = 2;
	अन्यथा अगर (AR_SREV_9300_20_OR_LATER(ah))
		max_streams = 3;
	अन्यथा
		max_streams = 2;

	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		अगर (max_streams >= 2)
			ht_info->cap |= IEEE80211_HT_CAP_TX_STBC;
		ht_info->cap |= (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);
	पूर्ण

	/* set up supported mcs set */
	स_रखो(&ht_info->mcs, 0, माप(ht_info->mcs));
	tx_streams = ath9k_cmn_count_streams(ah->txchainmask, max_streams);
	rx_streams = ath9k_cmn_count_streams(ah->rxchainmask, max_streams);

	ath_dbg(common, CONFIG, "TX streams %d, RX streams: %d\n",
		tx_streams, rx_streams);

	अगर (tx_streams != rx_streams) अणु
		ht_info->mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		ht_info->mcs.tx_params |= ((tx_streams - 1) <<
				IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT);
	पूर्ण

	क्रम (i = 0; i < rx_streams; i++)
		ht_info->mcs.rx_mask[i] = 0xff;

	ht_info->mcs.tx_params |= IEEE80211_HT_MCS_TX_DEFINED;
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_setup_ht_cap);

व्योम ath9k_cmn_reload_chainmask(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!(ah->caps.hw_caps & ATH9K_HW_CAP_HT))
		वापस;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		ath9k_cmn_setup_ht_cap(ah,
			&common->sbands[NL80211_BAND_2GHZ].ht_cap);
	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		ath9k_cmn_setup_ht_cap(ah,
			&common->sbands[NL80211_BAND_5GHZ].ht_cap);
पूर्ण
EXPORT_SYMBOL(ath9k_cmn_reload_chainmask);
