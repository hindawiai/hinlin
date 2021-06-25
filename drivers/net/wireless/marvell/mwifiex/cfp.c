<शैली गुरु>
/*
 * NXP Wireless LAN device driver: Channel, Frequence and Power
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "cfg80211.h"

/* 100mW */
#घोषणा MWIFIEX_TX_PWR_DEFAULT     20
/* 100mW */
#घोषणा MWIFIEX_TX_PWR_US_DEFAULT      20
/* 50mW */
#घोषणा MWIFIEX_TX_PWR_JP_DEFAULT      16
/* 100mW */
#घोषणा MWIFIEX_TX_PWR_FR_100MW        20
/* 10mW */
#घोषणा MWIFIEX_TX_PWR_FR_10MW         10
/* 100mW */
#घोषणा MWIFIEX_TX_PWR_EMEA_DEFAULT    20

अटल u8 adhoc_rates_b[B_SUPPORTED_RATES] = अणु 0x82, 0x84, 0x8b, 0x96, 0 पूर्ण;

अटल u8 adhoc_rates_g[G_SUPPORTED_RATES] = अणु 0x8c, 0x12, 0x98, 0x24,
					       0xb0, 0x48, 0x60, 0x6c, 0 पूर्ण;

अटल u8 adhoc_rates_bg[BG_SUPPORTED_RATES] = अणु 0x82, 0x84, 0x8b, 0x96,
						 0x0c, 0x12, 0x18, 0x24,
						 0x30, 0x48, 0x60, 0x6c, 0 पूर्ण;

अटल u8 adhoc_rates_a[A_SUPPORTED_RATES] = अणु 0x8c, 0x12, 0x98, 0x24,
					       0xb0, 0x48, 0x60, 0x6c, 0 पूर्ण;
अटल u8 supported_rates_a[A_SUPPORTED_RATES] = अणु 0x0c, 0x12, 0x18, 0x24,
					0xb0, 0x48, 0x60, 0x6c, 0 पूर्ण;
अटल u16 mwअगरiex_data_rates[MWIFIEX_SUPPORTED_RATES_EXT] = अणु 0x02, 0x04,
					0x0B, 0x16, 0x00, 0x0C, 0x12, 0x18,
					0x24, 0x30, 0x48, 0x60, 0x6C, 0x90,
					0x0D, 0x1A, 0x27, 0x34, 0x4E, 0x68,
					0x75, 0x82, 0x0C, 0x1B, 0x36, 0x51,
					0x6C, 0xA2, 0xD8, 0xF3, 0x10E, 0x00 पूर्ण;

अटल u8 supported_rates_b[B_SUPPORTED_RATES] = अणु 0x02, 0x04, 0x0b, 0x16, 0 पूर्ण;

अटल u8 supported_rates_g[G_SUPPORTED_RATES] = अणु 0x0c, 0x12, 0x18, 0x24,
					0x30, 0x48, 0x60, 0x6c, 0 पूर्ण;

अटल u8 supported_rates_bg[BG_SUPPORTED_RATES] = अणु 0x02, 0x04, 0x0b, 0x0c,
					0x12, 0x16, 0x18, 0x24, 0x30, 0x48,
					0x60, 0x6c, 0 पूर्ण;

u16 region_code_index[MWIFIEX_MAX_REGION_CODE] = अणु 0x00, 0x10, 0x20, 0x30,
						0x31, 0x32, 0x40, 0x41, 0x50 पूर्ण;

अटल u8 supported_rates_n[N_SUPPORTED_RATES] = अणु 0x02, 0x04, 0 पूर्ण;

/* For every mcs_rate line, the first 8 bytes are क्रम stream 1x1,
 * and all 16 bytes are क्रम stream 2x2.
 */
अटल स्थिर u16 mcs_rate[4][16] = अणु
	/* LGI 40M */
	अणु 0x1b, 0x36, 0x51, 0x6c, 0xa2, 0xd8, 0xf3, 0x10e,
	  0x36, 0x6c, 0xa2, 0xd8, 0x144, 0x1b0, 0x1e6, 0x21c पूर्ण,

	/* SGI 40M */
	अणु 0x1e, 0x3c, 0x5a, 0x78, 0xb4, 0xf0, 0x10e, 0x12c,
	  0x3c, 0x78, 0xb4, 0xf0, 0x168, 0x1e0, 0x21c, 0x258 पूर्ण,

	/* LGI 20M */
	अणु 0x0d, 0x1a, 0x27, 0x34, 0x4e, 0x68, 0x75, 0x82,
	  0x1a, 0x34, 0x4e, 0x68, 0x9c, 0xd0, 0xea, 0x104 पूर्ण,

	/* SGI 20M */
	अणु 0x0e, 0x1c, 0x2b, 0x39, 0x56, 0x73, 0x82, 0x90,
	  0x1c, 0x39, 0x56, 0x73, 0xad, 0xe7, 0x104, 0x120 पूर्ण
पूर्ण;

/* AC rates */
अटल स्थिर u16 ac_mcs_rate_nss1[8][10] = अणु
	/* LG 160M */
	अणु 0x75, 0xEA, 0x15F, 0x1D4, 0x2BE, 0x3A8, 0x41D,
	  0x492, 0x57C, 0x618 पूर्ण,

	/* SG 160M */
	अणु 0x82, 0x104, 0x186, 0x208, 0x30C, 0x410, 0x492,
	  0x514, 0x618, 0x6C6 पूर्ण,

	/* LG 80M */
	अणु 0x3B, 0x75, 0xB0, 0xEA, 0x15F, 0x1D4, 0x20F,
	  0x249, 0x2BE, 0x30C पूर्ण,

	/* SG 80M */
	अणु 0x41, 0x82, 0xC3, 0x104, 0x186, 0x208, 0x249,
	  0x28A, 0x30C, 0x363 पूर्ण,

	/* LG 40M */
	अणु 0x1B, 0x36, 0x51, 0x6C, 0xA2, 0xD8, 0xF3,
	  0x10E, 0x144, 0x168 पूर्ण,

	/* SG 40M */
	अणु 0x1E, 0x3C, 0x5A, 0x78, 0xB4, 0xF0, 0x10E,
	  0x12C, 0x168, 0x190 पूर्ण,

	/* LG 20M */
	अणु 0xD, 0x1A, 0x27, 0x34, 0x4E, 0x68, 0x75, 0x82, 0x9C, 0x00 पूर्ण,

	/* SG 20M */
	अणु 0xF, 0x1D, 0x2C, 0x3A, 0x57, 0x74, 0x82, 0x91, 0xAE, 0x00 पूर्ण,
पूर्ण;

/* NSS2 note: the value in the table is 2 multiplier of the actual rate */
अटल स्थिर u16 ac_mcs_rate_nss2[8][10] = अणु
	/* LG 160M */
	अणु 0xEA, 0x1D4, 0x2BE, 0x3A8, 0x57C, 0x750, 0x83A,
	  0x924, 0xAF8, 0xC30 पूर्ण,

	/* SG 160M */
	अणु 0x104, 0x208, 0x30C, 0x410, 0x618, 0x820, 0x924,
	  0xA28, 0xC30, 0xD8B पूर्ण,

	/* LG 80M */
	अणु 0x75, 0xEA, 0x15F, 0x1D4, 0x2BE, 0x3A8, 0x41D,
	  0x492, 0x57C, 0x618 पूर्ण,

	/* SG 80M */
	अणु 0x82, 0x104, 0x186, 0x208, 0x30C, 0x410, 0x492,
	  0x514, 0x618, 0x6C6 पूर्ण,

	/* LG 40M */
	अणु 0x36, 0x6C, 0xA2, 0xD8, 0x144, 0x1B0, 0x1E6,
	  0x21C, 0x288, 0x2D0 पूर्ण,

	/* SG 40M */
	अणु 0x3C, 0x78, 0xB4, 0xF0, 0x168, 0x1E0, 0x21C,
	  0x258, 0x2D0, 0x320 पूर्ण,

	/* LG 20M */
	अणु 0x1A, 0x34, 0x4A, 0x68, 0x9C, 0xD0, 0xEA, 0x104,
	  0x138, 0x00 पूर्ण,

	/* SG 20M */
	अणु 0x1D, 0x3A, 0x57, 0x74, 0xAE, 0xE6, 0x104, 0x121,
	  0x15B, 0x00 पूर्ण,
पूर्ण;

काष्ठा region_code_mapping अणु
	u8 code;
	u8 region[IEEE80211_COUNTRY_STRING_LEN];
पूर्ण;

अटल काष्ठा region_code_mapping region_code_mapping_t[] = अणु
	अणु 0x10, "US " पूर्ण, /* US FCC */
	अणु 0x20, "CA " पूर्ण, /* IC Canada */
	अणु 0x30, "FR " पूर्ण, /* France */
	अणु 0x31, "ES " पूर्ण, /* Spain */
	अणु 0x32, "FR " पूर्ण, /* France */
	अणु 0x40, "JP " पूर्ण, /* Japan */
	अणु 0x41, "JP " पूर्ण, /* Japan */
	अणु 0x50, "CN " पूर्ण, /* China */
पूर्ण;

/* This function converts पूर्णांकeger code to region string */
u8 *mwअगरiex_11d_code_2_region(u8 code)
अणु
	u8 i;

	/* Look क्रम code in mapping table */
	क्रम (i = 0; i < ARRAY_SIZE(region_code_mapping_t); i++)
		अगर (region_code_mapping_t[i].code == code)
			वापस region_code_mapping_t[i].region;

	वापस शून्य;
पूर्ण

/*
 * This function maps an index in supported rates table पूर्णांकo
 * the corresponding data rate.
 */
u32 mwअगरiex_index_to_acs_data_rate(काष्ठा mwअगरiex_निजी *priv,
				   u8 index, u8 ht_info)
अणु
	u32 rate = 0;
	u8 mcs_index = 0;
	u8 bw = 0;
	u8 gi = 0;

	अगर ((ht_info & 0x3) == MWIFIEX_RATE_FORMAT_VHT) अणु
		mcs_index = min(index & 0xF, 9);

		/* 20M: bw=0, 40M: bw=1, 80M: bw=2, 160M: bw=3 */
		bw = (ht_info & 0xC) >> 2;

		/* LGI: gi =0, SGI: gi = 1 */
		gi = (ht_info & 0x10) >> 4;

		अगर ((index >> 4) == 1)	/* NSS = 2 */
			rate = ac_mcs_rate_nss2[2 * (3 - bw) + gi][mcs_index];
		अन्यथा			/* NSS = 1 */
			rate = ac_mcs_rate_nss1[2 * (3 - bw) + gi][mcs_index];
	पूर्ण अन्यथा अगर ((ht_info & 0x3) == MWIFIEX_RATE_FORMAT_HT) अणु
		/* 20M: bw=0, 40M: bw=1 */
		bw = (ht_info & 0xC) >> 2;

		/* LGI: gi =0, SGI: gi = 1 */
		gi = (ht_info & 0x10) >> 4;

		अगर (index == MWIFIEX_RATE_BITMAP_MCS0) अणु
			अगर (gi == 1)
				rate = 0x0D;    /* MCS 32 SGI rate */
			अन्यथा
				rate = 0x0C;    /* MCS 32 LGI rate */
		पूर्ण अन्यथा अगर (index < 16) अणु
			अगर ((bw == 1) || (bw == 0))
				rate = mcs_rate[2 * (1 - bw) + gi][index];
			अन्यथा
				rate = mwअगरiex_data_rates[0];
		पूर्ण अन्यथा अणु
			rate = mwअगरiex_data_rates[0];
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 11n non-HT rates */
		अगर (index >= MWIFIEX_SUPPORTED_RATES_EXT)
			index = 0;
		rate = mwअगरiex_data_rates[index];
	पूर्ण

	वापस rate;
पूर्ण

/* This function maps an index in supported rates table पूर्णांकo
 * the corresponding data rate.
 */
u32 mwअगरiex_index_to_data_rate(काष्ठा mwअगरiex_निजी *priv,
			       u8 index, u8 ht_info)
अणु
	u32 mcs_num_supp =
		(priv->adapter->user_dev_mcs_support == HT_STREAM_2X2) ? 16 : 8;
	u32 rate;

	अगर (priv->adapter->is_hw_11ac_capable)
		वापस mwअगरiex_index_to_acs_data_rate(priv, index, ht_info);

	अगर (ht_info & BIT(0)) अणु
		अगर (index == MWIFIEX_RATE_BITMAP_MCS0) अणु
			अगर (ht_info & BIT(2))
				rate = 0x0D;	/* MCS 32 SGI rate */
			अन्यथा
				rate = 0x0C;	/* MCS 32 LGI rate */
		पूर्ण अन्यथा अगर (index < mcs_num_supp) अणु
			अगर (ht_info & BIT(1)) अणु
				अगर (ht_info & BIT(2))
					/* SGI, 40M */
					rate = mcs_rate[1][index];
				अन्यथा
					/* LGI, 40M */
					rate = mcs_rate[0][index];
			पूर्ण अन्यथा अणु
				अगर (ht_info & BIT(2))
					/* SGI, 20M */
					rate = mcs_rate[3][index];
				अन्यथा
					/* LGI, 20M */
					rate = mcs_rate[2][index];
			पूर्ण
		पूर्ण अन्यथा
			rate = mwअगरiex_data_rates[0];
	पूर्ण अन्यथा अणु
		अगर (index >= MWIFIEX_SUPPORTED_RATES_EXT)
			index = 0;
		rate = mwअगरiex_data_rates[index];
	पूर्ण
	वापस rate;
पूर्ण

/*
 * This function वापसs the current active data rates.
 *
 * The result may vary depending upon connection status.
 */
u32 mwअगरiex_get_active_data_rates(काष्ठा mwअगरiex_निजी *priv, u8 *rates)
अणु
	अगर (!priv->media_connected)
		वापस mwअगरiex_get_supported_rates(priv, rates);
	अन्यथा
		वापस mwअगरiex_copy_rates(rates, 0,
					  priv->curr_bss_params.data_rates,
					  priv->curr_bss_params.num_of_rates);
पूर्ण

/*
 * This function locates the Channel-Frequency-Power triplet based upon
 * band and channel/frequency parameters.
 */
काष्ठा mwअगरiex_chan_freq_घातer *
mwअगरiex_get_cfp(काष्ठा mwअगरiex_निजी *priv, u8 band, u16 channel, u32 freq)
अणु
	काष्ठा mwअगरiex_chan_freq_घातer *cfp = शून्य;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch = शून्य;
	पूर्णांक i;

	अगर (!channel && !freq)
		वापस cfp;

	अगर (mwअगरiex_band_to_radio_type(band) == HostCmd_SCAN_RADIO_TYPE_BG)
		sband = priv->wdev.wiphy->bands[NL80211_BAND_2GHZ];
	अन्यथा
		sband = priv->wdev.wiphy->bands[NL80211_BAND_5GHZ];

	अगर (!sband) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: cannot find cfp by band %d\n",
			    __func__, band);
		वापस cfp;
	पूर्ण

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		ch = &sband->channels[i];

		अगर (ch->flags & IEEE80211_CHAN_DISABLED)
			जारी;

		अगर (freq) अणु
			अगर (ch->center_freq == freq)
				अवरोध;
		पूर्ण अन्यथा अणु
			/* find by valid channel*/
			अगर (ch->hw_value == channel ||
			    channel == FIRST_VALID_CHANNEL)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == sband->n_channels) अणु
		mwअगरiex_dbg(priv->adapter, WARN,
			    "%s: cannot find cfp by band %d\t"
			    "& channel=%d freq=%d\n",
			    __func__, band, channel, freq);
	पूर्ण अन्यथा अणु
		अगर (!ch)
			वापस cfp;

		priv->cfp.channel = ch->hw_value;
		priv->cfp.freq = ch->center_freq;
		priv->cfp.max_tx_घातer = ch->max_घातer;
		cfp = &priv->cfp;
	पूर्ण

	वापस cfp;
पूर्ण

/*
 * This function checks अगर the data rate is set to स्वतः.
 */
u8
mwअगरiex_is_rate_स्वतः(काष्ठा mwअगरiex_निजी *priv)
अणु
	u32 i;
	पूर्णांक rate_num = 0;

	क्रम (i = 0; i < ARRAY_SIZE(priv->biपंचांगap_rates); i++)
		अगर (priv->biपंचांगap_rates[i])
			rate_num++;

	अगर (rate_num > 1)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/* This function माला_लो the supported data rates from biपंचांगask inside
 * cfg80211_scan_request.
 */
u32 mwअगरiex_get_rates_from_cfg80211(काष्ठा mwअगरiex_निजी *priv,
				    u8 *rates, u8 radio_type)
अणु
	काष्ठा wiphy *wiphy = priv->adapter->wiphy;
	काष्ठा cfg80211_scan_request *request = priv->scan_request;
	u32 num_rates, rate_mask;
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक i;

	अगर (radio_type) अणु
		sband = wiphy->bands[NL80211_BAND_5GHZ];
		अगर (WARN_ON_ONCE(!sband))
			वापस 0;
		rate_mask = request->rates[NL80211_BAND_5GHZ];
	पूर्ण अन्यथा अणु
		sband = wiphy->bands[NL80211_BAND_2GHZ];
		अगर (WARN_ON_ONCE(!sband))
			वापस 0;
		rate_mask = request->rates[NL80211_BAND_2GHZ];
	पूर्ण

	num_rates = 0;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर ((BIT(i) & rate_mask) == 0)
			जारी; /* skip rate */
		rates[num_rates++] = (u8)(sband->bitrates[i].bitrate / 5);
	पूर्ण

	वापस num_rates;
पूर्ण

/* This function माला_लो the supported data rates. The function works in
 * both Ad-Hoc and infra mode by prपूर्णांकing the band and वापसing the
 * data rates.
 */
u32 mwअगरiex_get_supported_rates(काष्ठा mwअगरiex_निजी *priv, u8 *rates)
अणु
	u32 k = 0;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	अगर (priv->bss_mode == NL80211_IFTYPE_STATION ||
	    priv->bss_mode == NL80211_IFTYPE_P2P_CLIENT) अणु
		चयन (adapter->config_bands) अणु
		हाल BAND_B:
			mwअगरiex_dbg(adapter, INFO, "info: infra band=%d\t"
				    "supported_rates_b\n",
				    adapter->config_bands);
			k = mwअगरiex_copy_rates(rates, k, supported_rates_b,
					       माप(supported_rates_b));
			अवरोध;
		हाल BAND_G:
		हाल BAND_G | BAND_GN:
			mwअगरiex_dbg(adapter, INFO, "info: infra band=%d\t"
				    "supported_rates_g\n",
				    adapter->config_bands);
			k = mwअगरiex_copy_rates(rates, k, supported_rates_g,
					       माप(supported_rates_g));
			अवरोध;
		हाल BAND_B | BAND_G:
		हाल BAND_A | BAND_B | BAND_G:
		हाल BAND_A | BAND_B:
		हाल BAND_A | BAND_B | BAND_G | BAND_GN | BAND_AN:
		हाल BAND_A | BAND_B | BAND_G | BAND_GN | BAND_AN | BAND_AAC:
		हाल BAND_B | BAND_G | BAND_GN:
			mwअगरiex_dbg(adapter, INFO, "info: infra band=%d\t"
				    "supported_rates_bg\n",
				    adapter->config_bands);
			k = mwअगरiex_copy_rates(rates, k, supported_rates_bg,
					       माप(supported_rates_bg));
			अवरोध;
		हाल BAND_A:
		हाल BAND_A | BAND_G:
			mwअगरiex_dbg(adapter, INFO, "info: infra band=%d\t"
				    "supported_rates_a\n",
				    adapter->config_bands);
			k = mwअगरiex_copy_rates(rates, k, supported_rates_a,
					       माप(supported_rates_a));
			अवरोध;
		हाल BAND_AN:
		हाल BAND_A | BAND_AN:
		हाल BAND_A | BAND_AN | BAND_AAC:
		हाल BAND_A | BAND_G | BAND_AN | BAND_GN:
		हाल BAND_A | BAND_G | BAND_AN | BAND_GN | BAND_AAC:
			mwअगरiex_dbg(adapter, INFO, "info: infra band=%d\t"
				    "supported_rates_a\n",
				    adapter->config_bands);
			k = mwअगरiex_copy_rates(rates, k, supported_rates_a,
					       माप(supported_rates_a));
			अवरोध;
		हाल BAND_GN:
			mwअगरiex_dbg(adapter, INFO, "info: infra band=%d\t"
				    "supported_rates_n\n",
				    adapter->config_bands);
			k = mwअगरiex_copy_rates(rates, k, supported_rates_n,
					       माप(supported_rates_n));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Ad-hoc mode */
		चयन (adapter->adhoc_start_band) अणु
		हाल BAND_B:
			mwअगरiex_dbg(adapter, INFO, "info: adhoc B\n");
			k = mwअगरiex_copy_rates(rates, k, adhoc_rates_b,
					       माप(adhoc_rates_b));
			अवरोध;
		हाल BAND_G:
		हाल BAND_G | BAND_GN:
			mwअगरiex_dbg(adapter, INFO, "info: adhoc G only\n");
			k = mwअगरiex_copy_rates(rates, k, adhoc_rates_g,
					       माप(adhoc_rates_g));
			अवरोध;
		हाल BAND_B | BAND_G:
		हाल BAND_B | BAND_G | BAND_GN:
			mwअगरiex_dbg(adapter, INFO, "info: adhoc BG\n");
			k = mwअगरiex_copy_rates(rates, k, adhoc_rates_bg,
					       माप(adhoc_rates_bg));
			अवरोध;
		हाल BAND_A:
		हाल BAND_A | BAND_AN:
			mwअगरiex_dbg(adapter, INFO, "info: adhoc A\n");
			k = mwअगरiex_copy_rates(rates, k, adhoc_rates_a,
					       माप(adhoc_rates_a));
			अवरोध;
		पूर्ण
	पूर्ण

	वापस k;
पूर्ण

u8 mwअगरiex_adjust_data_rate(काष्ठा mwअगरiex_निजी *priv,
			    u8 rx_rate, u8 rate_info)
अणु
	u8 rate_index = 0;

	/* HT40 */
	अगर ((rate_info & BIT(0)) && (rate_info & BIT(1)))
		rate_index = MWIFIEX_RATE_INDEX_MCS0 +
			     MWIFIEX_BW20_MCS_NUM + rx_rate;
	अन्यथा अगर (rate_info & BIT(0)) /* HT20 */
		rate_index = MWIFIEX_RATE_INDEX_MCS0 + rx_rate;
	अन्यथा
		rate_index = (rx_rate > MWIFIEX_RATE_INDEX_OFDM0) ?
			      rx_rate - 1 : rx_rate;

	अगर (rate_index >= MWIFIEX_MAX_AC_RX_RATES)
		rate_index = MWIFIEX_MAX_AC_RX_RATES - 1;

	वापस rate_index;
पूर्ण
