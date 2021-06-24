<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/firmware.h>

#समावेश "iwl-drv.h"
#समावेश "iwl-modparams.h"
#समावेश "iwl-nvm-parse.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-io.h"
#समावेश "iwl-csr.h"
#समावेश "fw/acpi.h"
#समावेश "fw/api/nvm-reg.h"
#समावेश "fw/api/commands.h"
#समावेश "fw/api/cmdhdr.h"
#समावेश "fw/img.h"

/* NVM offsets (in words) definitions */
क्रमागत nvm_offsets अणु
	/* NVM HW-Section offset (in words) definitions */
	SUBSYSTEM_ID = 0x0A,
	HW_ADDR = 0x15,

	/* NVM SW-Section offset (in words) definitions */
	NVM_SW_SECTION = 0x1C0,
	NVM_VERSION = 0,
	RADIO_CFG = 1,
	SKU = 2,
	N_HW_ADDRS = 3,
	NVM_CHANNELS = 0x1E0 - NVM_SW_SECTION,

	/* NVM calibration section offset (in words) definitions */
	NVM_CALIB_SECTION = 0x2B8,
	XTAL_CALIB = 0x316 - NVM_CALIB_SECTION,

	/* NVM REGULATORY -Section offset (in words) definitions */
	NVM_CHANNELS_SDP = 0,
पूर्ण;

क्रमागत ext_nvm_offsets अणु
	/* NVM HW-Section offset (in words) definitions */
	MAC_ADDRESS_OVERRIDE_EXT_NVM = 1,

	/* NVM SW-Section offset (in words) definitions */
	NVM_VERSION_EXT_NVM = 0,
	N_HW_ADDRS_FAMILY_8000 = 3,

	/* NVM PHY_SKU-Section offset (in words) definitions */
	RADIO_CFG_FAMILY_EXT_NVM = 0,
	SKU_FAMILY_8000 = 2,

	/* NVM REGULATORY -Section offset (in words) definitions */
	NVM_CHANNELS_EXTENDED = 0,
	NVM_LAR_OFFSET_OLD = 0x4C7,
	NVM_LAR_OFFSET = 0x507,
	NVM_LAR_ENABLED = 0x7,
पूर्ण;

/* SKU Capabilities (actual values from NVM definition) */
क्रमागत nvm_sku_bits अणु
	NVM_SKU_CAP_BAND_24GHZ		= BIT(0),
	NVM_SKU_CAP_BAND_52GHZ		= BIT(1),
	NVM_SKU_CAP_11N_ENABLE		= BIT(2),
	NVM_SKU_CAP_11AC_ENABLE		= BIT(3),
	NVM_SKU_CAP_MIMO_DISABLE	= BIT(5),
पूर्ण;

/*
 * These are the channel numbers in the order that they are stored in the NVM
 */
अटल स्थिर u16 iwl_nvm_channels[] = अणु
	/* 2.4 GHz */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	/* 5 GHz */
	36, 40, 44 , 48, 52, 56, 60, 64,
	100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144,
	149, 153, 157, 161, 165
पूर्ण;

अटल स्थिर u16 iwl_ext_nvm_channels[] = अणु
	/* 2.4 GHz */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	/* 5 GHz */
	36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92,
	96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144,
	149, 153, 157, 161, 165, 169, 173, 177, 181
पूर्ण;

अटल स्थिर u16 iwl_uhb_nvm_channels[] = अणु
	/* 2.4 GHz */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	/* 5 GHz */
	36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92,
	96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144,
	149, 153, 157, 161, 165, 169, 173, 177, 181,
	/* 6-7 GHz */
	1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69,
	73, 77, 81, 85, 89, 93, 97, 101, 105, 109, 113, 117, 121, 125, 129,
	133, 137, 141, 145, 149, 153, 157, 161, 165, 169, 173, 177, 181, 185,
	189, 193, 197, 201, 205, 209, 213, 217, 221, 225, 229, 233
पूर्ण;

#घोषणा IWL_NVM_NUM_CHANNELS		ARRAY_SIZE(iwl_nvm_channels)
#घोषणा IWL_NVM_NUM_CHANNELS_EXT	ARRAY_SIZE(iwl_ext_nvm_channels)
#घोषणा IWL_NVM_NUM_CHANNELS_UHB	ARRAY_SIZE(iwl_uhb_nvm_channels)
#घोषणा NUM_2GHZ_CHANNELS		14
#घोषणा NUM_5GHZ_CHANNELS		37
#घोषणा FIRST_2GHZ_HT_MINUS		5
#घोषणा LAST_2GHZ_HT_PLUS		9
#घोषणा N_HW_ADDR_MASK			0xF

/* rate data (अटल) */
अटल काष्ठा ieee80211_rate iwl_cfg80211_rates[] = अणु
	अणु .bitrate = 1 * 10, .hw_value = 0, .hw_value_लघु = 0, पूर्ण,
	अणु .bitrate = 2 * 10, .hw_value = 1, .hw_value_लघु = 1,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE, पूर्ण,
	अणु .bitrate = 5.5 * 10, .hw_value = 2, .hw_value_लघु = 2,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE, पूर्ण,
	अणु .bitrate = 11 * 10, .hw_value = 3, .hw_value_लघु = 3,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE, पूर्ण,
	अणु .bitrate = 6 * 10, .hw_value = 4, .hw_value_लघु = 4, पूर्ण,
	अणु .bitrate = 9 * 10, .hw_value = 5, .hw_value_लघु = 5, पूर्ण,
	अणु .bitrate = 12 * 10, .hw_value = 6, .hw_value_लघु = 6, पूर्ण,
	अणु .bitrate = 18 * 10, .hw_value = 7, .hw_value_लघु = 7, पूर्ण,
	अणु .bitrate = 24 * 10, .hw_value = 8, .hw_value_लघु = 8, पूर्ण,
	अणु .bitrate = 36 * 10, .hw_value = 9, .hw_value_लघु = 9, पूर्ण,
	अणु .bitrate = 48 * 10, .hw_value = 10, .hw_value_लघु = 10, पूर्ण,
	अणु .bitrate = 54 * 10, .hw_value = 11, .hw_value_लघु = 11, पूर्ण,
पूर्ण;
#घोषणा RATES_24_OFFS	0
#घोषणा N_RATES_24	ARRAY_SIZE(iwl_cfg80211_rates)
#घोषणा RATES_52_OFFS	4
#घोषणा N_RATES_52	(N_RATES_24 - RATES_52_OFFS)

/**
 * क्रमागत iwl_nvm_channel_flags - channel flags in NVM
 * @NVM_CHANNEL_VALID: channel is usable क्रम this SKU/geo
 * @NVM_CHANNEL_IBSS: usable as an IBSS channel
 * @NVM_CHANNEL_ACTIVE: active scanning allowed
 * @NVM_CHANNEL_RADAR: radar detection required
 * @NVM_CHANNEL_INDOOR_ONLY: only inकरोor use is allowed
 * @NVM_CHANNEL_GO_CONCURRENT: GO operation is allowed when connected to BSS
 *	on same channel on 2.4 or same UNII band on 5.2
 * @NVM_CHANNEL_UNIFORM: unअगरorm spपढ़ोing required
 * @NVM_CHANNEL_20MHZ: 20 MHz channel okay
 * @NVM_CHANNEL_40MHZ: 40 MHz channel okay
 * @NVM_CHANNEL_80MHZ: 80 MHz channel okay
 * @NVM_CHANNEL_160MHZ: 160 MHz channel okay
 * @NVM_CHANNEL_DC_HIGH: DC HIGH required/allowed (?)
 */
क्रमागत iwl_nvm_channel_flags अणु
	NVM_CHANNEL_VALID		= BIT(0),
	NVM_CHANNEL_IBSS		= BIT(1),
	NVM_CHANNEL_ACTIVE		= BIT(3),
	NVM_CHANNEL_RADAR		= BIT(4),
	NVM_CHANNEL_INDOOR_ONLY		= BIT(5),
	NVM_CHANNEL_GO_CONCURRENT	= BIT(6),
	NVM_CHANNEL_UNIFORM		= BIT(7),
	NVM_CHANNEL_20MHZ		= BIT(8),
	NVM_CHANNEL_40MHZ		= BIT(9),
	NVM_CHANNEL_80MHZ		= BIT(10),
	NVM_CHANNEL_160MHZ		= BIT(11),
	NVM_CHANNEL_DC_HIGH		= BIT(12),
पूर्ण;

/**
 * क्रमागत iwl_reg_capa_flags - global flags applied क्रम the whole regulatory
 * करोमुख्य.
 * @REG_CAPA_BF_CCD_LOW_BAND: Beam-क्रमming or Cyclic Delay Diversity in the
 *	2.4Ghz band is allowed.
 * @REG_CAPA_BF_CCD_HIGH_BAND: Beam-क्रमming or Cyclic Delay Diversity in the
 *	5Ghz band is allowed.
 * @REG_CAPA_160MHZ_ALLOWED: 11ac channel with a width of 160Mhz is allowed
 *	क्रम this regulatory करोमुख्य (valid only in 5Ghz).
 * @REG_CAPA_80MHZ_ALLOWED: 11ac channel with a width of 80Mhz is allowed
 *	क्रम this regulatory करोमुख्य (valid only in 5Ghz).
 * @REG_CAPA_MCS_8_ALLOWED: 11ac with MCS 8 is allowed.
 * @REG_CAPA_MCS_9_ALLOWED: 11ac with MCS 9 is allowed.
 * @REG_CAPA_40MHZ_FORBIDDEN: 11n channel with a width of 40Mhz is क्रमbidden
 *	क्रम this regulatory करोमुख्य (valid only in 5Ghz).
 * @REG_CAPA_DC_HIGH_ENABLED: DC HIGH allowed.
 * @REG_CAPA_11AX_DISABLED: 11ax is क्रमbidden क्रम this regulatory करोमुख्य.
 */
क्रमागत iwl_reg_capa_flags अणु
	REG_CAPA_BF_CCD_LOW_BAND	= BIT(0),
	REG_CAPA_BF_CCD_HIGH_BAND	= BIT(1),
	REG_CAPA_160MHZ_ALLOWED		= BIT(2),
	REG_CAPA_80MHZ_ALLOWED		= BIT(3),
	REG_CAPA_MCS_8_ALLOWED		= BIT(4),
	REG_CAPA_MCS_9_ALLOWED		= BIT(5),
	REG_CAPA_40MHZ_FORBIDDEN	= BIT(7),
	REG_CAPA_DC_HIGH_ENABLED	= BIT(9),
	REG_CAPA_11AX_DISABLED		= BIT(10),
पूर्ण;

/**
 * क्रमागत iwl_reg_capa_flags_v2 - global flags applied क्रम the whole regulatory
 * करोमुख्य (version 2).
 * @REG_CAPA_V2_STRADDLE_DISABLED: Straddle channels (144, 142, 138) are
 *	disabled.
 * @REG_CAPA_V2_BF_CCD_LOW_BAND: Beam-क्रमming or Cyclic Delay Diversity in the
 *	2.4Ghz band is allowed.
 * @REG_CAPA_V2_BF_CCD_HIGH_BAND: Beam-क्रमming or Cyclic Delay Diversity in the
 *	5Ghz band is allowed.
 * @REG_CAPA_V2_160MHZ_ALLOWED: 11ac channel with a width of 160Mhz is allowed
 *	क्रम this regulatory करोमुख्य (valid only in 5Ghz).
 * @REG_CAPA_V2_80MHZ_ALLOWED: 11ac channel with a width of 80Mhz is allowed
 *	क्रम this regulatory करोमुख्य (valid only in 5Ghz).
 * @REG_CAPA_V2_MCS_8_ALLOWED: 11ac with MCS 8 is allowed.
 * @REG_CAPA_V2_MCS_9_ALLOWED: 11ac with MCS 9 is allowed.
 * @REG_CAPA_V2_WEATHER_DISABLED: Weather radar channels (120, 124, 128, 118,
 *	126, 122) are disabled.
 * @REG_CAPA_V2_40MHZ_ALLOWED: 11n channel with a width of 40Mhz is allowed
 *	क्रम this regulatory करोमुख्य (uvalid only in 5Ghz).
 * @REG_CAPA_V2_11AX_DISABLED: 11ax is क्रमbidden क्रम this regulatory करोमुख्य.
 */
क्रमागत iwl_reg_capa_flags_v2 अणु
	REG_CAPA_V2_STRADDLE_DISABLED	= BIT(0),
	REG_CAPA_V2_BF_CCD_LOW_BAND	= BIT(1),
	REG_CAPA_V2_BF_CCD_HIGH_BAND	= BIT(2),
	REG_CAPA_V2_160MHZ_ALLOWED	= BIT(3),
	REG_CAPA_V2_80MHZ_ALLOWED	= BIT(4),
	REG_CAPA_V2_MCS_8_ALLOWED	= BIT(5),
	REG_CAPA_V2_MCS_9_ALLOWED	= BIT(6),
	REG_CAPA_V2_WEATHER_DISABLED	= BIT(7),
	REG_CAPA_V2_40MHZ_ALLOWED	= BIT(8),
	REG_CAPA_V2_11AX_DISABLED	= BIT(10),
पूर्ण;

/*
* API v2 क्रम reg_capa_flags is relevant from version 6 and onwards of the
* MCC update command response.
*/
#घोषणा REG_CAPA_V2_RESP_VER	6

/**
 * काष्ठा iwl_reg_capa - काष्ठा क्रम global regulatory capabilities, Used क्रम
 * handling the dअगरferent APIs of reg_capa_flags.
 *
 * @allow_40mhz: 11n channel with a width of 40Mhz is allowed
 *	क्रम this regulatory करोमुख्य (valid only in 5Ghz).
 * @allow_80mhz: 11ac channel with a width of 80Mhz is allowed
 *	क्रम this regulatory करोमुख्य (valid only in 5Ghz).
 * @allow_160mhz: 11ac channel with a width of 160Mhz is allowed
 *	क्रम this regulatory करोमुख्य (valid only in 5Ghz).
 * @disable_11ax: 11ax is क्रमbidden क्रम this regulatory करोमुख्य.
 */
काष्ठा iwl_reg_capa अणु
	u16 allow_40mhz;
	u16 allow_80mhz;
	u16 allow_160mhz;
	u16 disable_11ax;
पूर्ण;

अटल अंतरभूत व्योम iwl_nvm_prपूर्णांक_channel_flags(काष्ठा device *dev, u32 level,
					       पूर्णांक chan, u32 flags)
अणु
#घोषणा CHECK_AND_PRINT_I(x)	\
	((flags & NVM_CHANNEL_##x) ? " " #x : "")

	अगर (!(flags & NVM_CHANNEL_VALID)) अणु
		IWL_DEBUG_DEV(dev, level, "Ch. %d: 0x%x: No traffic\n",
			      chan, flags);
		वापस;
	पूर्ण

	/* Note: alपढ़ोy can prपूर्णांक up to 101 अक्षरacters, 110 is the limit! */
	IWL_DEBUG_DEV(dev, level,
		      "Ch. %d: 0x%x:%s%s%s%s%s%s%s%s%s%s%s%s\n",
		      chan, flags,
		      CHECK_AND_PRINT_I(VALID),
		      CHECK_AND_PRINT_I(IBSS),
		      CHECK_AND_PRINT_I(ACTIVE),
		      CHECK_AND_PRINT_I(RADAR),
		      CHECK_AND_PRINT_I(INDOOR_ONLY),
		      CHECK_AND_PRINT_I(GO_CONCURRENT),
		      CHECK_AND_PRINT_I(UNIFORM),
		      CHECK_AND_PRINT_I(20MHZ),
		      CHECK_AND_PRINT_I(40MHZ),
		      CHECK_AND_PRINT_I(80MHZ),
		      CHECK_AND_PRINT_I(160MHZ),
		      CHECK_AND_PRINT_I(DC_HIGH));
#अघोषित CHECK_AND_PRINT_I
पूर्ण

अटल u32 iwl_get_channel_flags(u8 ch_num, पूर्णांक ch_idx, क्रमागत nl80211_band band,
				 u32 nvm_flags, स्थिर काष्ठा iwl_cfg *cfg)
अणु
	u32 flags = IEEE80211_CHAN_NO_HT40;

	अगर (band == NL80211_BAND_2GHZ && (nvm_flags & NVM_CHANNEL_40MHZ)) अणु
		अगर (ch_num <= LAST_2GHZ_HT_PLUS)
			flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
		अगर (ch_num >= FIRST_2GHZ_HT_MINUS)
			flags &= ~IEEE80211_CHAN_NO_HT40MINUS;
	पूर्ण अन्यथा अगर (nvm_flags & NVM_CHANNEL_40MHZ) अणु
		अगर ((ch_idx - NUM_2GHZ_CHANNELS) % 2 == 0)
			flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
		अन्यथा
			flags &= ~IEEE80211_CHAN_NO_HT40MINUS;
	पूर्ण
	अगर (!(nvm_flags & NVM_CHANNEL_80MHZ))
		flags |= IEEE80211_CHAN_NO_80MHZ;
	अगर (!(nvm_flags & NVM_CHANNEL_160MHZ))
		flags |= IEEE80211_CHAN_NO_160MHZ;

	अगर (!(nvm_flags & NVM_CHANNEL_IBSS))
		flags |= IEEE80211_CHAN_NO_IR;

	अगर (!(nvm_flags & NVM_CHANNEL_ACTIVE))
		flags |= IEEE80211_CHAN_NO_IR;

	अगर (nvm_flags & NVM_CHANNEL_RADAR)
		flags |= IEEE80211_CHAN_RADAR;

	अगर (nvm_flags & NVM_CHANNEL_INDOOR_ONLY)
		flags |= IEEE80211_CHAN_INDOOR_ONLY;

	/* Set the GO concurrent flag only in हाल that NO_IR is set.
	 * Otherwise it is meaningless
	 */
	अगर ((nvm_flags & NVM_CHANNEL_GO_CONCURRENT) &&
	    (flags & IEEE80211_CHAN_NO_IR))
		flags |= IEEE80211_CHAN_IR_CONCURRENT;

	वापस flags;
पूर्ण

अटल क्रमागत nl80211_band iwl_nl80211_band_from_channel_idx(पूर्णांक ch_idx)
अणु
	अगर (ch_idx >= NUM_2GHZ_CHANNELS + NUM_5GHZ_CHANNELS) अणु
		वापस NL80211_BAND_6GHZ;
	पूर्ण

	अगर (ch_idx >= NUM_2GHZ_CHANNELS)
		वापस NL80211_BAND_5GHZ;
	वापस NL80211_BAND_2GHZ;
पूर्ण

अटल पूर्णांक iwl_init_channel_map(काष्ठा device *dev, स्थिर काष्ठा iwl_cfg *cfg,
				काष्ठा iwl_nvm_data *data,
				स्थिर व्योम * स्थिर nvm_ch_flags,
				u32 sbands_flags, bool v4)
अणु
	पूर्णांक ch_idx;
	पूर्णांक n_channels = 0;
	काष्ठा ieee80211_channel *channel;
	u32 ch_flags;
	पूर्णांक num_of_ch;
	स्थिर u16 *nvm_chan;

	अगर (cfg->uhb_supported) अणु
		num_of_ch = IWL_NVM_NUM_CHANNELS_UHB;
		nvm_chan = iwl_uhb_nvm_channels;
	पूर्ण अन्यथा अगर (cfg->nvm_type == IWL_NVM_EXT) अणु
		num_of_ch = IWL_NVM_NUM_CHANNELS_EXT;
		nvm_chan = iwl_ext_nvm_channels;
	पूर्ण अन्यथा अणु
		num_of_ch = IWL_NVM_NUM_CHANNELS;
		nvm_chan = iwl_nvm_channels;
	पूर्ण

	क्रम (ch_idx = 0; ch_idx < num_of_ch; ch_idx++) अणु
		क्रमागत nl80211_band band =
			iwl_nl80211_band_from_channel_idx(ch_idx);

		अगर (v4)
			ch_flags =
				__le32_to_cpup((__le32 *)nvm_ch_flags + ch_idx);
		अन्यथा
			ch_flags =
				__le16_to_cpup((__le16 *)nvm_ch_flags + ch_idx);

		अगर (band == NL80211_BAND_5GHZ &&
		    !data->sku_cap_band_52ghz_enable)
			जारी;

		/* workaround to disable wide channels in 5GHz */
		अगर ((sbands_flags & IWL_NVM_SBANDS_FLAGS_NO_WIDE_IN_5GHZ) &&
		    band == NL80211_BAND_5GHZ) अणु
			ch_flags &= ~(NVM_CHANNEL_40MHZ |
				     NVM_CHANNEL_80MHZ |
				     NVM_CHANNEL_160MHZ);
		पूर्ण

		अगर (ch_flags & NVM_CHANNEL_160MHZ)
			data->vht160_supported = true;

		अगर (!(sbands_flags & IWL_NVM_SBANDS_FLAGS_LAR) &&
		    !(ch_flags & NVM_CHANNEL_VALID)) अणु
			/*
			 * Channels might become valid later अगर lar is
			 * supported, hence we still want to add them to
			 * the list of supported channels to cfg80211.
			 */
			iwl_nvm_prपूर्णांक_channel_flags(dev, IWL_DL_EEPROM,
						    nvm_chan[ch_idx], ch_flags);
			जारी;
		पूर्ण

		channel = &data->channels[n_channels];
		n_channels++;

		channel->hw_value = nvm_chan[ch_idx];
		channel->band = band;
		channel->center_freq =
			ieee80211_channel_to_frequency(
				channel->hw_value, channel->band);

		/* Initialize regulatory-based run-समय data */

		/*
		 * Default value - highest tx घातer value.  max_घातer
		 * is not used in mvm, and is used क्रम backwards compatibility
		 */
		channel->max_घातer = IWL_DEFAULT_MAX_TX_POWER;

		/* करोn't put limitations in case we're using LAR */
		अगर (!(sbands_flags & IWL_NVM_SBANDS_FLAGS_LAR))
			channel->flags = iwl_get_channel_flags(nvm_chan[ch_idx],
							       ch_idx, band,
							       ch_flags, cfg);
		अन्यथा
			channel->flags = 0;

		/* TODO: Don't put limitations on UHB devices as we still don't
		 * have NVM क्रम them
		 */
		अगर (cfg->uhb_supported)
			channel->flags = 0;
		iwl_nvm_prपूर्णांक_channel_flags(dev, IWL_DL_EEPROM,
					    channel->hw_value, ch_flags);
		IWL_DEBUG_EEPROM(dev, "Ch. %d: %ddBm\n",
				 channel->hw_value, channel->max_घातer);
	पूर्ण

	वापस n_channels;
पूर्ण

अटल व्योम iwl_init_vht_hw_capab(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_nvm_data *data,
				  काष्ठा ieee80211_sta_vht_cap *vht_cap,
				  u8 tx_chains, u8 rx_chains)
अणु
	स्थिर काष्ठा iwl_cfg *cfg = trans->cfg;
	पूर्णांक num_rx_ants = num_of_ant(rx_chains);
	पूर्णांक num_tx_ants = num_of_ant(tx_chains);

	vht_cap->vht_supported = true;

	vht_cap->cap = IEEE80211_VHT_CAP_SHORT_GI_80 |
		       IEEE80211_VHT_CAP_RXSTBC_1 |
		       IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
		       3 << IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT |
		       IEEE80211_VHT_MAX_AMPDU_1024K <<
		       IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;

	अगर (data->vht160_supported)
		vht_cap->cap |= IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ |
				IEEE80211_VHT_CAP_SHORT_GI_160;

	अगर (cfg->vht_mu_mimo_supported)
		vht_cap->cap |= IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE;

	अगर (cfg->ht_params->ldpc)
		vht_cap->cap |= IEEE80211_VHT_CAP_RXLDPC;

	अगर (data->sku_cap_mimo_disabled) अणु
		num_rx_ants = 1;
		num_tx_ants = 1;
	पूर्ण

	अगर (num_tx_ants > 1)
		vht_cap->cap |= IEEE80211_VHT_CAP_TXSTBC;
	अन्यथा
		vht_cap->cap |= IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN;

	चयन (iwlwअगरi_mod_params.amsdu_size) अणु
	हाल IWL_AMSDU_DEF:
		अगर (trans->trans_cfg->mq_rx_supported)
			vht_cap->cap |=
				IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454;
		अन्यथा
			vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895;
		अवरोध;
	हाल IWL_AMSDU_2K:
		अगर (trans->trans_cfg->mq_rx_supported)
			vht_cap->cap |=
				IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454;
		अन्यथा
			WARN(1, "RB size of 2K is not supported by this device\n");
		अवरोध;
	हाल IWL_AMSDU_4K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895;
		अवरोध;
	हाल IWL_AMSDU_8K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991;
		अवरोध;
	हाल IWL_AMSDU_12K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	vht_cap->vht_mcs.rx_mcs_map =
		cpu_to_le16(IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 |
			    IEEE80211_VHT_MCS_SUPPORT_0_9 << 2 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 4 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 6 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 8 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 10 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 12 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 14);

	अगर (num_rx_ants == 1 || cfg->rx_with_siso_भागersity) अणु
		vht_cap->cap |= IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN;
		/* this works because NOT_SUPPORTED == 3 */
		vht_cap->vht_mcs.rx_mcs_map |=
			cpu_to_le16(IEEE80211_VHT_MCS_NOT_SUPPORTED << 2);
	पूर्ण

	vht_cap->vht_mcs.tx_mcs_map = vht_cap->vht_mcs.rx_mcs_map;

	vht_cap->vht_mcs.tx_highest |=
		cpu_to_le16(IEEE80211_VHT_EXT_NSS_BW_CAPABLE);
पूर्ण

अटल स्थिर काष्ठा ieee80211_sband_अगरtype_data iwl_he_capa[] = अणु
	अणु
		.types_mask = BIT(NL80211_IFTYPE_STATION),
		.he_cap = अणु
			.has_he = true,
			.he_cap_elem = अणु
				.mac_cap_info[0] =
					IEEE80211_HE_MAC_CAP0_HTC_HE |
					IEEE80211_HE_MAC_CAP0_TWT_REQ,
				.mac_cap_info[1] =
					IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUR_16US |
					IEEE80211_HE_MAC_CAP1_MULTI_TID_AGG_RX_QOS_8,
				.mac_cap_info[2] =
					IEEE80211_HE_MAC_CAP2_32BIT_BA_BITMAP,
				.mac_cap_info[3] =
					IEEE80211_HE_MAC_CAP3_OMI_CONTROL |
					IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_2,
				.mac_cap_info[4] =
					IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU |
					IEEE80211_HE_MAC_CAP4_MULTI_TID_AGG_TX_QOS_B39,
				.mac_cap_info[5] =
					IEEE80211_HE_MAC_CAP5_MULTI_TID_AGG_TX_QOS_B40 |
					IEEE80211_HE_MAC_CAP5_MULTI_TID_AGG_TX_QOS_B41 |
					IEEE80211_HE_MAC_CAP5_UL_2x996_TONE_RU |
					IEEE80211_HE_MAC_CAP5_HE_DYNAMIC_SM_PS |
					IEEE80211_HE_MAC_CAP5_HT_VHT_TRIG_FRAME_RX,
				.phy_cap_info[0] =
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G |
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G |
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G,
				.phy_cap_info[1] =
					IEEE80211_HE_PHY_CAP1_PREAMBLE_PUNC_RX_MASK |
					IEEE80211_HE_PHY_CAP1_DEVICE_CLASS_A |
					IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD,
				.phy_cap_info[2] =
					IEEE80211_HE_PHY_CAP2_NDP_4x_LTF_AND_3_2US,
				.phy_cap_info[3] =
					IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_NO_DCM |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_TX_NSS_1 |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_NO_DCM |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_RX_NSS_1,
				.phy_cap_info[4] =
					IEEE80211_HE_PHY_CAP4_SU_BEAMFORMEE |
					IEEE80211_HE_PHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_8 |
					IEEE80211_HE_PHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_8,
				.phy_cap_info[5] =
					IEEE80211_HE_PHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_2 |
					IEEE80211_HE_PHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_2,
				.phy_cap_info[6] =
					IEEE80211_HE_PHY_CAP6_TRIG_SU_BEAMFORMING_FB |
					IEEE80211_HE_PHY_CAP6_TRIG_MU_BEAMFORMING_PARTIAL_BW_FB |
					IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT,
				.phy_cap_info[7] =
					IEEE80211_HE_PHY_CAP7_POWER_BOOST_FACTOR_SUPP |
					IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XLTF_AND_08_US_GI |
					IEEE80211_HE_PHY_CAP7_MAX_NC_1,
				.phy_cap_info[8] =
					IEEE80211_HE_PHY_CAP8_HE_ER_SU_PPDU_4XLTF_AND_08_US_GI |
					IEEE80211_HE_PHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
					IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
					IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU |
					IEEE80211_HE_PHY_CAP8_DCM_MAX_RU_2x996,
				.phy_cap_info[9] =
					IEEE80211_HE_PHY_CAP9_NON_TRIGGERED_CQI_FEEDBACK |
					IEEE80211_HE_PHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_COMP_SIGB |
					IEEE80211_HE_PHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_NON_COMP_SIGB |
					IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_RESERVED,
			पूर्ण,
			/*
			 * Set शेष Tx/Rx HE MCS NSS Support field.
			 * Indicate support क्रम up to 2 spatial streams and all
			 * MCS, without any special हालs
			 */
			.he_mcs_nss_supp = अणु
				.rx_mcs_80 = cpu_to_le16(0xfffa),
				.tx_mcs_80 = cpu_to_le16(0xfffa),
				.rx_mcs_160 = cpu_to_le16(0xfffa),
				.tx_mcs_160 = cpu_to_le16(0xfffa),
				.rx_mcs_80p80 = cpu_to_le16(0xffff),
				.tx_mcs_80p80 = cpu_to_le16(0xffff),
			पूर्ण,
			/*
			 * Set शेष PPE thresholds, with PPET16 set to 0,
			 * PPET8 set to 7
			 */
			.ppe_thres = अणु0x61, 0x1c, 0xc7, 0x71पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.types_mask = BIT(NL80211_IFTYPE_AP),
		.he_cap = अणु
			.has_he = true,
			.he_cap_elem = अणु
				.mac_cap_info[0] =
					IEEE80211_HE_MAC_CAP0_HTC_HE,
				.mac_cap_info[1] =
					IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUR_16US |
					IEEE80211_HE_MAC_CAP1_MULTI_TID_AGG_RX_QOS_8,
				.mac_cap_info[2] =
					IEEE80211_HE_MAC_CAP2_BSR,
				.mac_cap_info[3] =
					IEEE80211_HE_MAC_CAP3_OMI_CONTROL |
					IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_EXT_2,
				.mac_cap_info[4] =
					IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU,
				.mac_cap_info[5] =
					IEEE80211_HE_MAC_CAP5_UL_2x996_TONE_RU,
				.phy_cap_info[0] =
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G |
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G |
					IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G,
				.phy_cap_info[1] =
					IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD,
				.phy_cap_info[2] =
					IEEE80211_HE_PHY_CAP2_NDP_4x_LTF_AND_3_2US,
				.phy_cap_info[3] =
					IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_NO_DCM |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_TX_NSS_1 |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_NO_DCM |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_RX_NSS_1,
				.phy_cap_info[4] =
					IEEE80211_HE_PHY_CAP4_SU_BEAMFORMEE |
					IEEE80211_HE_PHY_CAP4_BEAMFORMEE_MAX_STS_ABOVE_80MHZ_8 |
					IEEE80211_HE_PHY_CAP4_BEAMFORMEE_MAX_STS_UNDER_80MHZ_8,
				.phy_cap_info[5] =
					IEEE80211_HE_PHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_2 |
					IEEE80211_HE_PHY_CAP5_BEAMFORMEE_NUM_SND_DIM_ABOVE_80MHZ_2,
				.phy_cap_info[6] =
					IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT,
				.phy_cap_info[7] =
					IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XLTF_AND_08_US_GI |
					IEEE80211_HE_PHY_CAP7_MAX_NC_1,
				.phy_cap_info[8] =
					IEEE80211_HE_PHY_CAP8_HE_ER_SU_PPDU_4XLTF_AND_08_US_GI |
					IEEE80211_HE_PHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
					IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
					IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU |
					IEEE80211_HE_PHY_CAP8_DCM_MAX_RU_2x996,
				.phy_cap_info[9] =
					IEEE80211_HE_PHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_COMP_SIGB |
					IEEE80211_HE_PHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_NON_COMP_SIGB |
					IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_RESERVED,
			पूर्ण,
			/*
			 * Set शेष Tx/Rx HE MCS NSS Support field.
			 * Indicate support क्रम up to 2 spatial streams and all
			 * MCS, without any special हालs
			 */
			.he_mcs_nss_supp = अणु
				.rx_mcs_80 = cpu_to_le16(0xfffa),
				.tx_mcs_80 = cpu_to_le16(0xfffa),
				.rx_mcs_160 = cpu_to_le16(0xfffa),
				.tx_mcs_160 = cpu_to_le16(0xfffa),
				.rx_mcs_80p80 = cpu_to_le16(0xffff),
				.tx_mcs_80p80 = cpu_to_le16(0xffff),
			पूर्ण,
			/*
			 * Set शेष PPE thresholds, with PPET16 set to 0,
			 * PPET8 set to 7
			 */
			.ppe_thres = अणु0x61, 0x1c, 0xc7, 0x71पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम iwl_init_he_6ghz_capa(काष्ठा iwl_trans *trans,
				  काष्ठा iwl_nvm_data *data,
				  काष्ठा ieee80211_supported_band *sband,
				  u8 tx_chains, u8 rx_chains)
अणु
	काष्ठा ieee80211_sta_ht_cap ht_cap;
	काष्ठा ieee80211_sta_vht_cap vht_cap = अणुपूर्ण;
	काष्ठा ieee80211_sband_अगरtype_data *अगरtype_data;
	u16 he_6ghz_capa = 0;
	u32 exp;
	पूर्णांक i;

	अगर (sband->band != NL80211_BAND_6GHZ)
		वापस;

	/* grab HT/VHT capabilities and calculate HE 6 GHz capabilities */
	iwl_init_ht_hw_capab(trans, data, &ht_cap, NL80211_BAND_5GHZ,
			     tx_chains, rx_chains);
	WARN_ON(!ht_cap.ht_supported);
	iwl_init_vht_hw_capab(trans, data, &vht_cap, tx_chains, rx_chains);
	WARN_ON(!vht_cap.vht_supported);

	he_6ghz_capa |=
		u16_encode_bits(ht_cap.ampdu_density,
				IEEE80211_HE_6GHZ_CAP_MIN_MPDU_START);
	exp = u32_get_bits(vht_cap.cap,
			   IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK);
	he_6ghz_capa |=
		u16_encode_bits(exp, IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_LEN_EXP);
	exp = u32_get_bits(vht_cap.cap, IEEE80211_VHT_CAP_MAX_MPDU_MASK);
	he_6ghz_capa |=
		u16_encode_bits(exp, IEEE80211_HE_6GHZ_CAP_MAX_MPDU_LEN);
	/* we करोn't support extended_ht_cap_info anywhere, so no RD_RESPONDER */
	अगर (vht_cap.cap & IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN)
		he_6ghz_capa |= IEEE80211_HE_6GHZ_CAP_TX_ANTPAT_CONS;
	अगर (vht_cap.cap & IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN)
		he_6ghz_capa |= IEEE80211_HE_6GHZ_CAP_RX_ANTPAT_CONS;

	IWL_DEBUG_EEPROM(trans->dev, "he_6ghz_capa=0x%x\n", he_6ghz_capa);

	/* we know it's writable - we set it beक्रमe ourselves */
	अगरtype_data = (व्योम *)sband->अगरtype_data;
	क्रम (i = 0; i < sband->n_अगरtype_data; i++)
		अगरtype_data[i].he_6ghz_capa.capa = cpu_to_le16(he_6ghz_capa);
पूर्ण

अटल व्योम iwl_init_he_hw_capab(काष्ठा iwl_trans *trans,
				 काष्ठा iwl_nvm_data *data,
				 काष्ठा ieee80211_supported_band *sband,
				 u8 tx_chains, u8 rx_chains)
अणु
	काष्ठा ieee80211_sband_अगरtype_data *अगरtype_data;

	/* should only initialize once */
	अगर (WARN_ON(sband->अगरtype_data))
		वापस;

	BUILD_BUG_ON(माप(data->अगरtd.low) != माप(iwl_he_capa));
	BUILD_BUG_ON(माप(data->अगरtd.high) != माप(iwl_he_capa));

	चयन (sband->band) अणु
	हाल NL80211_BAND_2GHZ:
		अगरtype_data = data->अगरtd.low;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
	हाल NL80211_BAND_6GHZ:
		अगरtype_data = data->अगरtd.high;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	स_नकल(अगरtype_data, iwl_he_capa, माप(iwl_he_capa));

	sband->अगरtype_data = अगरtype_data;
	sband->n_अगरtype_data = ARRAY_SIZE(iwl_he_capa);

	/* If not 2x2, we need to indicate 1x1 in the Midamble RX Max NSTS */
	अगर ((tx_chains & rx_chains) != ANT_AB) अणु
		पूर्णांक i;

		क्रम (i = 0; i < sband->n_अगरtype_data; i++) अणु
			अगरtype_data[i].he_cap.he_cap_elem.phy_cap_info[1] &=
				~IEEE80211_HE_PHY_CAP1_MIDAMBLE_RX_TX_MAX_NSTS;
			अगरtype_data[i].he_cap.he_cap_elem.phy_cap_info[2] &=
				~IEEE80211_HE_PHY_CAP2_MIDAMBLE_RX_TX_MAX_NSTS;
			अगरtype_data[i].he_cap.he_cap_elem.phy_cap_info[7] &=
				~IEEE80211_HE_PHY_CAP7_MAX_NC_MASK;
		पूर्ण
	पूर्ण
	iwl_init_he_6ghz_capa(trans, data, sband, tx_chains, rx_chains);
पूर्ण

अटल व्योम iwl_init_sbands(काष्ठा iwl_trans *trans,
			    काष्ठा iwl_nvm_data *data,
			    स्थिर व्योम *nvm_ch_flags, u8 tx_chains,
			    u8 rx_chains, u32 sbands_flags, bool v4)
अणु
	काष्ठा device *dev = trans->dev;
	स्थिर काष्ठा iwl_cfg *cfg = trans->cfg;
	पूर्णांक n_channels;
	पूर्णांक n_used = 0;
	काष्ठा ieee80211_supported_band *sband;

	n_channels = iwl_init_channel_map(dev, cfg, data, nvm_ch_flags,
					  sbands_flags, v4);
	sband = &data->bands[NL80211_BAND_2GHZ];
	sband->band = NL80211_BAND_2GHZ;
	sband->bitrates = &iwl_cfg80211_rates[RATES_24_OFFS];
	sband->n_bitrates = N_RATES_24;
	n_used += iwl_init_sband_channels(data, sband, n_channels,
					  NL80211_BAND_2GHZ);
	iwl_init_ht_hw_capab(trans, data, &sband->ht_cap, NL80211_BAND_2GHZ,
			     tx_chains, rx_chains);

	अगर (data->sku_cap_11ax_enable && !iwlwअगरi_mod_params.disable_11ax)
		iwl_init_he_hw_capab(trans, data, sband, tx_chains, rx_chains);

	sband = &data->bands[NL80211_BAND_5GHZ];
	sband->band = NL80211_BAND_5GHZ;
	sband->bitrates = &iwl_cfg80211_rates[RATES_52_OFFS];
	sband->n_bitrates = N_RATES_52;
	n_used += iwl_init_sband_channels(data, sband, n_channels,
					  NL80211_BAND_5GHZ);
	iwl_init_ht_hw_capab(trans, data, &sband->ht_cap, NL80211_BAND_5GHZ,
			     tx_chains, rx_chains);
	अगर (data->sku_cap_11ac_enable && !iwlwअगरi_mod_params.disable_11ac)
		iwl_init_vht_hw_capab(trans, data, &sband->vht_cap,
				      tx_chains, rx_chains);

	अगर (data->sku_cap_11ax_enable && !iwlwअगरi_mod_params.disable_11ax)
		iwl_init_he_hw_capab(trans, data, sband, tx_chains, rx_chains);

	/* 6GHz band. */
	sband = &data->bands[NL80211_BAND_6GHZ];
	sband->band = NL80211_BAND_6GHZ;
	/* use the same rates as 5GHz band */
	sband->bitrates = &iwl_cfg80211_rates[RATES_52_OFFS];
	sband->n_bitrates = N_RATES_52;
	n_used += iwl_init_sband_channels(data, sband, n_channels,
					  NL80211_BAND_6GHZ);

	अगर (data->sku_cap_11ax_enable && !iwlwअगरi_mod_params.disable_11ax)
		iwl_init_he_hw_capab(trans, data, sband, tx_chains, rx_chains);
	अन्यथा
		sband->n_channels = 0;
	अगर (n_channels != n_used)
		IWL_ERR_DEV(dev, "NVM: used only %d of %d channels\n",
			    n_used, n_channels);
पूर्ण

अटल पूर्णांक iwl_get_sku(स्थिर काष्ठा iwl_cfg *cfg, स्थिर __le16 *nvm_sw,
		       स्थिर __le16 *phy_sku)
अणु
	अगर (cfg->nvm_type != IWL_NVM_EXT)
		वापस le16_to_cpup(nvm_sw + SKU);

	वापस le32_to_cpup((__le32 *)(phy_sku + SKU_FAMILY_8000));
पूर्ण

अटल पूर्णांक iwl_get_nvm_version(स्थिर काष्ठा iwl_cfg *cfg, स्थिर __le16 *nvm_sw)
अणु
	अगर (cfg->nvm_type != IWL_NVM_EXT)
		वापस le16_to_cpup(nvm_sw + NVM_VERSION);
	अन्यथा
		वापस le32_to_cpup((__le32 *)(nvm_sw +
					       NVM_VERSION_EXT_NVM));
पूर्ण

अटल पूर्णांक iwl_get_radio_cfg(स्थिर काष्ठा iwl_cfg *cfg, स्थिर __le16 *nvm_sw,
			     स्थिर __le16 *phy_sku)
अणु
	अगर (cfg->nvm_type != IWL_NVM_EXT)
		वापस le16_to_cpup(nvm_sw + RADIO_CFG);

	वापस le32_to_cpup((__le32 *)(phy_sku + RADIO_CFG_FAMILY_EXT_NVM));

पूर्ण

अटल पूर्णांक iwl_get_n_hw_addrs(स्थिर काष्ठा iwl_cfg *cfg, स्थिर __le16 *nvm_sw)
अणु
	पूर्णांक n_hw_addr;

	अगर (cfg->nvm_type != IWL_NVM_EXT)
		वापस le16_to_cpup(nvm_sw + N_HW_ADDRS);

	n_hw_addr = le32_to_cpup((__le32 *)(nvm_sw + N_HW_ADDRS_FAMILY_8000));

	वापस n_hw_addr & N_HW_ADDR_MASK;
पूर्ण

अटल व्योम iwl_set_radio_cfg(स्थिर काष्ठा iwl_cfg *cfg,
			      काष्ठा iwl_nvm_data *data,
			      u32 radio_cfg)
अणु
	अगर (cfg->nvm_type != IWL_NVM_EXT) अणु
		data->radio_cfg_type = NVM_RF_CFG_TYPE_MSK(radio_cfg);
		data->radio_cfg_step = NVM_RF_CFG_STEP_MSK(radio_cfg);
		data->radio_cfg_dash = NVM_RF_CFG_DASH_MSK(radio_cfg);
		data->radio_cfg_pnum = NVM_RF_CFG_PNUM_MSK(radio_cfg);
		वापस;
	पूर्ण

	/* set the radio configuration क्रम family 8000 */
	data->radio_cfg_type = EXT_NVM_RF_CFG_TYPE_MSK(radio_cfg);
	data->radio_cfg_step = EXT_NVM_RF_CFG_STEP_MSK(radio_cfg);
	data->radio_cfg_dash = EXT_NVM_RF_CFG_DASH_MSK(radio_cfg);
	data->radio_cfg_pnum = EXT_NVM_RF_CFG_FLAVOR_MSK(radio_cfg);
	data->valid_tx_ant = EXT_NVM_RF_CFG_TX_ANT_MSK(radio_cfg);
	data->valid_rx_ant = EXT_NVM_RF_CFG_RX_ANT_MSK(radio_cfg);
पूर्ण

अटल व्योम iwl_flip_hw_address(__le32 mac_addr0, __le32 mac_addr1, u8 *dest)
अणु
	स्थिर u8 *hw_addr;

	hw_addr = (स्थिर u8 *)&mac_addr0;
	dest[0] = hw_addr[3];
	dest[1] = hw_addr[2];
	dest[2] = hw_addr[1];
	dest[3] = hw_addr[0];

	hw_addr = (स्थिर u8 *)&mac_addr1;
	dest[4] = hw_addr[1];
	dest[5] = hw_addr[0];
पूर्ण

अटल व्योम iwl_set_hw_address_from_csr(काष्ठा iwl_trans *trans,
					काष्ठा iwl_nvm_data *data)
अणु
	__le32 mac_addr0 = cpu_to_le32(iwl_पढ़ो32(trans, CSR_MAC_ADDR0_STRAP));
	__le32 mac_addr1 = cpu_to_le32(iwl_पढ़ो32(trans, CSR_MAC_ADDR1_STRAP));

	iwl_flip_hw_address(mac_addr0, mac_addr1, data->hw_addr);
	/*
	 * If the OEM fused a valid address, use it instead of the one in the
	 * OTP
	 */
	अगर (is_valid_ether_addr(data->hw_addr))
		वापस;

	mac_addr0 = cpu_to_le32(iwl_पढ़ो32(trans, CSR_MAC_ADDR0_OTP));
	mac_addr1 = cpu_to_le32(iwl_पढ़ो32(trans, CSR_MAC_ADDR1_OTP));

	iwl_flip_hw_address(mac_addr0, mac_addr1, data->hw_addr);
पूर्ण

अटल व्योम iwl_set_hw_address_family_8000(काष्ठा iwl_trans *trans,
					   स्थिर काष्ठा iwl_cfg *cfg,
					   काष्ठा iwl_nvm_data *data,
					   स्थिर __le16 *mac_override,
					   स्थिर __be16 *nvm_hw)
अणु
	स्थिर u8 *hw_addr;

	अगर (mac_override) अणु
		अटल स्थिर u8 reserved_mac[] = अणु
			0x02, 0xcc, 0xaa, 0xff, 0xee, 0x00
		पूर्ण;

		hw_addr = (स्थिर u8 *)(mac_override +
				 MAC_ADDRESS_OVERRIDE_EXT_NVM);

		/*
		 * Store the MAC address from MAO section.
		 * No byte swapping is required in MAO section
		 */
		स_नकल(data->hw_addr, hw_addr, ETH_ALEN);

		/*
		 * Force the use of the OTP MAC address in हाल of reserved MAC
		 * address in the NVM, or अगर address is given but invalid.
		 */
		अगर (is_valid_ether_addr(data->hw_addr) &&
		    स_भेद(reserved_mac, hw_addr, ETH_ALEN) != 0)
			वापस;

		IWL_ERR(trans,
			"mac address from nvm override section is not valid\n");
	पूर्ण

	अगर (nvm_hw) अणु
		/* पढ़ो the mac address from WFMP रेजिस्टरs */
		__le32 mac_addr0 = cpu_to_le32(iwl_trans_पढ़ो_prph(trans,
						WFMP_MAC_ADDR_0));
		__le32 mac_addr1 = cpu_to_le32(iwl_trans_पढ़ो_prph(trans,
						WFMP_MAC_ADDR_1));

		iwl_flip_hw_address(mac_addr0, mac_addr1, data->hw_addr);

		वापस;
	पूर्ण

	IWL_ERR(trans, "mac address is not found\n");
पूर्ण

अटल पूर्णांक iwl_set_hw_address(काष्ठा iwl_trans *trans,
			      स्थिर काष्ठा iwl_cfg *cfg,
			      काष्ठा iwl_nvm_data *data, स्थिर __be16 *nvm_hw,
			      स्थिर __le16 *mac_override)
अणु
	अगर (cfg->mac_addr_from_csr) अणु
		iwl_set_hw_address_from_csr(trans, data);
	पूर्ण अन्यथा अगर (cfg->nvm_type != IWL_NVM_EXT) अणु
		स्थिर u8 *hw_addr = (स्थिर u8 *)(nvm_hw + HW_ADDR);

		/* The byte order is little endian 16 bit, meaning 214365 */
		data->hw_addr[0] = hw_addr[1];
		data->hw_addr[1] = hw_addr[0];
		data->hw_addr[2] = hw_addr[3];
		data->hw_addr[3] = hw_addr[2];
		data->hw_addr[4] = hw_addr[5];
		data->hw_addr[5] = hw_addr[4];
	पूर्ण अन्यथा अणु
		iwl_set_hw_address_family_8000(trans, cfg, data,
					       mac_override, nvm_hw);
	पूर्ण

	अगर (!is_valid_ether_addr(data->hw_addr)) अणु
		IWL_ERR(trans, "no valid mac address was found\n");
		वापस -EINVAL;
	पूर्ण

	IWL_INFO(trans, "base HW address: %pM\n", data->hw_addr);

	वापस 0;
पूर्ण

अटल bool
iwl_nvm_no_wide_in_5ghz(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_cfg *cfg,
			स्थिर __be16 *nvm_hw)
अणु
	/*
	 * Workaround a bug in Inकरोnesia SKUs where the regulatory in
	 * some 7000-family OTPs erroneously allow wide channels in
	 * 5GHz.  To check क्रम Inकरोnesia, we take the SKU value from
	 * bits 1-4 in the subप्रणाली ID and check अगर it is either 5 or
	 * 9.  In those हालs, we need to क्रमce-disable wide channels
	 * in 5GHz otherwise the FW will throw a sysनिश्चित when we try
	 * to use them.
	 */
	अगर (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_7000) अणु
		/*
		 * Unlike the other sections in the NVM, the hw
		 * section uses big-endian.
		 */
		u16 subप्रणाली_id = be16_to_cpup(nvm_hw + SUBSYSTEM_ID);
		u8 sku = (subप्रणाली_id & 0x1e) >> 1;

		अगर (sku == 5 || sku == 9) अणु
			IWL_DEBUG_EEPROM(trans->dev,
					 "disabling wide channels in 5GHz (0x%0x %d)\n",
					 subप्रणाली_id, sku);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

काष्ठा iwl_nvm_data *
iwl_parse_nvm_data(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_cfg *cfg,
		   स्थिर काष्ठा iwl_fw *fw,
		   स्थिर __be16 *nvm_hw, स्थिर __le16 *nvm_sw,
		   स्थिर __le16 *nvm_calib, स्थिर __le16 *regulatory,
		   स्थिर __le16 *mac_override, स्थिर __le16 *phy_sku,
		   u8 tx_chains, u8 rx_chains)
अणु
	काष्ठा iwl_nvm_data *data;
	bool lar_enabled;
	u32 sku, radio_cfg;
	u32 sbands_flags = 0;
	u16 lar_config;
	स्थिर __le16 *ch_section;

	अगर (cfg->uhb_supported)
		data = kzalloc(काष्ठा_size(data, channels,
					   IWL_NVM_NUM_CHANNELS_UHB),
					   GFP_KERNEL);
	अन्यथा अगर (cfg->nvm_type != IWL_NVM_EXT)
		data = kzalloc(काष्ठा_size(data, channels,
					   IWL_NVM_NUM_CHANNELS),
					   GFP_KERNEL);
	अन्यथा
		data = kzalloc(काष्ठा_size(data, channels,
					   IWL_NVM_NUM_CHANNELS_EXT),
					   GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	data->nvm_version = iwl_get_nvm_version(cfg, nvm_sw);

	radio_cfg = iwl_get_radio_cfg(cfg, nvm_sw, phy_sku);
	iwl_set_radio_cfg(cfg, data, radio_cfg);
	अगर (data->valid_tx_ant)
		tx_chains &= data->valid_tx_ant;
	अगर (data->valid_rx_ant)
		rx_chains &= data->valid_rx_ant;

	sku = iwl_get_sku(cfg, nvm_sw, phy_sku);
	data->sku_cap_band_24ghz_enable = sku & NVM_SKU_CAP_BAND_24GHZ;
	data->sku_cap_band_52ghz_enable = sku & NVM_SKU_CAP_BAND_52GHZ;
	data->sku_cap_11n_enable = sku & NVM_SKU_CAP_11N_ENABLE;
	अगर (iwlwअगरi_mod_params.disable_11n & IWL_DISABLE_HT_ALL)
		data->sku_cap_11n_enable = false;
	data->sku_cap_11ac_enable = data->sku_cap_11n_enable &&
				    (sku & NVM_SKU_CAP_11AC_ENABLE);
	data->sku_cap_mimo_disabled = sku & NVM_SKU_CAP_MIMO_DISABLE;

	data->n_hw_addrs = iwl_get_n_hw_addrs(cfg, nvm_sw);

	अगर (cfg->nvm_type != IWL_NVM_EXT) अणु
		/* Checking क्रम required sections */
		अगर (!nvm_calib) अणु
			IWL_ERR(trans,
				"Can't parse empty Calib NVM sections\n");
			kमुक्त(data);
			वापस शून्य;
		पूर्ण

		ch_section = cfg->nvm_type == IWL_NVM_SDP ?
			     &regulatory[NVM_CHANNELS_SDP] :
			     &nvm_sw[NVM_CHANNELS];

		/* in family 8000 Xtal calibration values moved to OTP */
		data->xtal_calib[0] = *(nvm_calib + XTAL_CALIB);
		data->xtal_calib[1] = *(nvm_calib + XTAL_CALIB + 1);
		lar_enabled = true;
	पूर्ण अन्यथा अणु
		u16 lar_offset = data->nvm_version < 0xE39 ?
				 NVM_LAR_OFFSET_OLD :
				 NVM_LAR_OFFSET;

		lar_config = le16_to_cpup(regulatory + lar_offset);
		data->lar_enabled = !!(lar_config &
				       NVM_LAR_ENABLED);
		lar_enabled = data->lar_enabled;
		ch_section = &regulatory[NVM_CHANNELS_EXTENDED];
	पूर्ण

	/* If no valid mac address was found - bail out */
	अगर (iwl_set_hw_address(trans, cfg, data, nvm_hw, mac_override)) अणु
		kमुक्त(data);
		वापस शून्य;
	पूर्ण

	अगर (lar_enabled &&
	    fw_has_capa(&fw->ucode_capa, IWL_UCODE_TLV_CAPA_LAR_SUPPORT))
		sbands_flags |= IWL_NVM_SBANDS_FLAGS_LAR;

	अगर (iwl_nvm_no_wide_in_5ghz(trans, cfg, nvm_hw))
		sbands_flags |= IWL_NVM_SBANDS_FLAGS_NO_WIDE_IN_5GHZ;

	iwl_init_sbands(trans, data, ch_section, tx_chains, rx_chains,
			sbands_flags, false);
	data->calib_version = 255;

	वापस data;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_parse_nvm_data);

अटल u32 iwl_nvm_get_regकरोm_bw_flags(स्थिर u16 *nvm_chan,
				       पूर्णांक ch_idx, u16 nvm_flags,
				       काष्ठा iwl_reg_capa reg_capa,
				       स्थिर काष्ठा iwl_cfg *cfg)
अणु
	u32 flags = NL80211_RRF_NO_HT40;

	अगर (ch_idx < NUM_2GHZ_CHANNELS &&
	    (nvm_flags & NVM_CHANNEL_40MHZ)) अणु
		अगर (nvm_chan[ch_idx] <= LAST_2GHZ_HT_PLUS)
			flags &= ~NL80211_RRF_NO_HT40PLUS;
		अगर (nvm_chan[ch_idx] >= FIRST_2GHZ_HT_MINUS)
			flags &= ~NL80211_RRF_NO_HT40MINUS;
	पूर्ण अन्यथा अगर (nvm_flags & NVM_CHANNEL_40MHZ) अणु
		अगर ((ch_idx - NUM_2GHZ_CHANNELS) % 2 == 0)
			flags &= ~NL80211_RRF_NO_HT40PLUS;
		अन्यथा
			flags &= ~NL80211_RRF_NO_HT40MINUS;
	पूर्ण

	अगर (!(nvm_flags & NVM_CHANNEL_80MHZ))
		flags |= NL80211_RRF_NO_80MHZ;
	अगर (!(nvm_flags & NVM_CHANNEL_160MHZ))
		flags |= NL80211_RRF_NO_160MHZ;

	अगर (!(nvm_flags & NVM_CHANNEL_ACTIVE))
		flags |= NL80211_RRF_NO_IR;

	अगर (nvm_flags & NVM_CHANNEL_RADAR)
		flags |= NL80211_RRF_DFS;

	अगर (nvm_flags & NVM_CHANNEL_INDOOR_ONLY)
		flags |= NL80211_RRF_NO_OUTDOOR;

	/* Set the GO concurrent flag only in हाल that NO_IR is set.
	 * Otherwise it is meaningless
	 */
	अगर ((nvm_flags & NVM_CHANNEL_GO_CONCURRENT) &&
	    (flags & NL80211_RRF_NO_IR))
		flags |= NL80211_RRF_GO_CONCURRENT;

	/*
	 * reg_capa is per regulatory करोमुख्य so apply it क्रम every channel
	 */
	अगर (ch_idx >= NUM_2GHZ_CHANNELS) अणु
		अगर (!reg_capa.allow_40mhz)
			flags |= NL80211_RRF_NO_HT40;

		अगर (!reg_capa.allow_80mhz)
			flags |= NL80211_RRF_NO_80MHZ;

		अगर (!reg_capa.allow_160mhz)
			flags |= NL80211_RRF_NO_160MHZ;
	पूर्ण
	अगर (reg_capa.disable_11ax)
		flags |= NL80211_RRF_NO_HE;

	वापस flags;
पूर्ण

अटल काष्ठा iwl_reg_capa iwl_get_reg_capa(u16 flags, u8 resp_ver)
अणु
	काष्ठा iwl_reg_capa reg_capa;

	अगर (resp_ver >= REG_CAPA_V2_RESP_VER) अणु
		reg_capa.allow_40mhz = flags & REG_CAPA_V2_40MHZ_ALLOWED;
		reg_capa.allow_80mhz = flags & REG_CAPA_V2_80MHZ_ALLOWED;
		reg_capa.allow_160mhz = flags & REG_CAPA_V2_160MHZ_ALLOWED;
		reg_capa.disable_11ax = flags & REG_CAPA_V2_11AX_DISABLED;
	पूर्ण अन्यथा अणु
		reg_capa.allow_40mhz = !(flags & REG_CAPA_40MHZ_FORBIDDEN);
		reg_capa.allow_80mhz = flags & REG_CAPA_80MHZ_ALLOWED;
		reg_capa.allow_160mhz = flags & REG_CAPA_160MHZ_ALLOWED;
		reg_capa.disable_11ax = flags & REG_CAPA_11AX_DISABLED;
	पूर्ण
	वापस reg_capa;
पूर्ण

काष्ठा ieee80211_regकरोमुख्य *
iwl_parse_nvm_mcc_info(काष्ठा device *dev, स्थिर काष्ठा iwl_cfg *cfg,
		       पूर्णांक num_of_ch, __le32 *channels, u16 fw_mcc,
		       u16 geo_info, u16 cap, u8 resp_ver)
अणु
	पूर्णांक ch_idx;
	u16 ch_flags;
	u32 reg_rule_flags, prev_reg_rule_flags = 0;
	स्थिर u16 *nvm_chan;
	काष्ठा ieee80211_regकरोमुख्य *regd, *copy_rd;
	काष्ठा ieee80211_reg_rule *rule;
	क्रमागत nl80211_band band;
	पूर्णांक center_freq, prev_center_freq = 0;
	पूर्णांक valid_rules = 0;
	bool new_rule;
	पूर्णांक max_num_ch;
	काष्ठा iwl_reg_capa reg_capa;

	अगर (cfg->uhb_supported) अणु
		max_num_ch = IWL_NVM_NUM_CHANNELS_UHB;
		nvm_chan = iwl_uhb_nvm_channels;
	पूर्ण अन्यथा अगर (cfg->nvm_type == IWL_NVM_EXT) अणु
		max_num_ch = IWL_NVM_NUM_CHANNELS_EXT;
		nvm_chan = iwl_ext_nvm_channels;
	पूर्ण अन्यथा अणु
		max_num_ch = IWL_NVM_NUM_CHANNELS;
		nvm_chan = iwl_nvm_channels;
	पूर्ण

	अगर (WARN_ON(num_of_ch > max_num_ch))
		num_of_ch = max_num_ch;

	अगर (WARN_ON_ONCE(num_of_ch > NL80211_MAX_SUPP_REG_RULES))
		वापस ERR_PTR(-EINVAL);

	IWL_DEBUG_DEV(dev, IWL_DL_LAR, "building regdom for %d channels\n",
		      num_of_ch);

	/* build a regकरोमुख्य rule क्रम every valid channel */
	regd = kzalloc(काष्ठा_size(regd, reg_rules, num_of_ch), GFP_KERNEL);
	अगर (!regd)
		वापस ERR_PTR(-ENOMEM);

	/* set alpha2 from FW. */
	regd->alpha2[0] = fw_mcc >> 8;
	regd->alpha2[1] = fw_mcc & 0xff;

	/* parse regulatory capability flags */
	reg_capa = iwl_get_reg_capa(cap, resp_ver);

	क्रम (ch_idx = 0; ch_idx < num_of_ch; ch_idx++) अणु
		ch_flags = (u16)__le32_to_cpup(channels + ch_idx);
		band = iwl_nl80211_band_from_channel_idx(ch_idx);
		center_freq = ieee80211_channel_to_frequency(nvm_chan[ch_idx],
							     band);
		new_rule = false;

		अगर (!(ch_flags & NVM_CHANNEL_VALID)) अणु
			iwl_nvm_prपूर्णांक_channel_flags(dev, IWL_DL_LAR,
						    nvm_chan[ch_idx], ch_flags);
			जारी;
		पूर्ण

		reg_rule_flags = iwl_nvm_get_regकरोm_bw_flags(nvm_chan, ch_idx,
							     ch_flags, reg_capa,
							     cfg);

		/* we can't जारी the same rule */
		अगर (ch_idx == 0 || prev_reg_rule_flags != reg_rule_flags ||
		    center_freq - prev_center_freq > 20) अणु
			valid_rules++;
			new_rule = true;
		पूर्ण

		rule = &regd->reg_rules[valid_rules - 1];

		अगर (new_rule)
			rule->freq_range.start_freq_khz =
						MHZ_TO_KHZ(center_freq - 10);

		rule->freq_range.end_freq_khz = MHZ_TO_KHZ(center_freq + 10);

		/* this करोesn't matter - not used by FW */
		rule->घातer_rule.max_antenna_gain = DBI_TO_MBI(6);
		rule->घातer_rule.max_eirp =
			DBM_TO_MBM(IWL_DEFAULT_MAX_TX_POWER);

		rule->flags = reg_rule_flags;

		/* rely on स्वतः-calculation to merge BW of contiguous chans */
		rule->flags |= NL80211_RRF_AUTO_BW;
		rule->freq_range.max_bandwidth_khz = 0;

		prev_center_freq = center_freq;
		prev_reg_rule_flags = reg_rule_flags;

		iwl_nvm_prपूर्णांक_channel_flags(dev, IWL_DL_LAR,
					    nvm_chan[ch_idx], ch_flags);

		अगर (!(geo_info & GEO_WMM_ETSI_5GHZ_INFO) ||
		    band == NL80211_BAND_2GHZ)
			जारी;

		reg_query_regdb_wmm(regd->alpha2, center_freq, rule);
	पूर्ण

	regd->n_reg_rules = valid_rules;

	/*
	 * Narrow करोwn regकरोm क्रम unused regulatory rules to prevent hole
	 * between reg rules to wmm rules.
	 */
	copy_rd = kmemdup(regd, काष्ठा_size(regd, reg_rules, valid_rules),
			  GFP_KERNEL);
	अगर (!copy_rd)
		copy_rd = ERR_PTR(-ENOMEM);

	kमुक्त(regd);
	वापस copy_rd;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_parse_nvm_mcc_info);

#घोषणा IWL_MAX_NVM_SECTION_SIZE	0x1b58
#घोषणा IWL_MAX_EXT_NVM_SECTION_SIZE	0x1ffc
#घोषणा MAX_NVM_खाता_LEN	16384

व्योम iwl_nvm_fixups(u32 hw_id, अचिन्हित पूर्णांक section, u8 *data,
		    अचिन्हित पूर्णांक len)
अणु
#घोषणा IWL_4165_DEVICE_ID	0x5501
#घोषणा NVM_SKU_CAP_MIMO_DISABLE BIT(5)

	अगर (section == NVM_SECTION_TYPE_PHY_SKU &&
	    hw_id == IWL_4165_DEVICE_ID && data && len >= 5 &&
	    (data[4] & NVM_SKU_CAP_MIMO_DISABLE))
		/* OTP 0x52 bug work around: it's a 1x1 device */
		data[3] = ANT_B | (ANT_B << 4);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_nvm_fixups);

/*
 * Reads बाह्यal NVM from a file पूर्णांकo mvm->nvm_sections
 *
 * HOW TO CREATE THE NVM खाता FORMAT:
 * ------------------------------
 * 1. create hex file, क्रमmat:
 *      3800 -> header
 *      0000 -> header
 *      5a40 -> data
 *
 *   rev - 6 bit (word1)
 *   len - 10 bit (word1)
 *   id - 4 bit (word2)
 *   rsv - 12 bit (word2)
 *
 * 2. flip 8bits with 8 bits per line to get the right NVM file क्रमmat
 *
 * 3. create binary file from the hex file
 *
 * 4. save as "iNVM_xxx.bin" under /lib/firmware
 */
पूर्णांक iwl_पढ़ो_बाह्यal_nvm(काष्ठा iwl_trans *trans,
			  स्थिर अक्षर *nvm_file_name,
			  काष्ठा iwl_nvm_section *nvm_sections)
अणु
	पूर्णांक ret, section_size;
	u16 section_id;
	स्थिर काष्ठा firmware *fw_entry;
	स्थिर काष्ठा अणु
		__le16 word1;
		__le16 word2;
		u8 data[];
	पूर्ण *file_sec;
	स्थिर u8 *eof;
	u8 *temp;
	पूर्णांक max_section_size;
	स्थिर __le32 *dword_buff;

#घोषणा NVM_WORD1_LEN(x) (8 * (x & 0x03FF))
#घोषणा NVM_WORD2_ID(x) (x >> 12)
#घोषणा EXT_NVM_WORD2_LEN(x) (2 * (((x) & 0xFF) << 8 | (x) >> 8))
#घोषणा EXT_NVM_WORD1_ID(x) ((x) >> 4)
#घोषणा NVM_HEADER_0	(0x2A504C54)
#घोषणा NVM_HEADER_1	(0x4E564D2A)
#घोषणा NVM_HEADER_SIZE	(4 * माप(u32))

	IWL_DEBUG_EEPROM(trans->dev, "Read from external NVM\n");

	/* Maximal size depends on NVM version */
	अगर (trans->cfg->nvm_type != IWL_NVM_EXT)
		max_section_size = IWL_MAX_NVM_SECTION_SIZE;
	अन्यथा
		max_section_size = IWL_MAX_EXT_NVM_SECTION_SIZE;

	/*
	 * Obtain NVM image via request_firmware. Since we alपढ़ोy used
	 * request_firmware_noरुको() क्रम the firmware binary load and only
	 * get here after that we assume the NVM request can be satisfied
	 * synchronously.
	 */
	ret = request_firmware(&fw_entry, nvm_file_name, trans->dev);
	अगर (ret) अणु
		IWL_ERR(trans, "ERROR: %s isn't available %d\n",
			nvm_file_name, ret);
		वापस ret;
	पूर्ण

	IWL_INFO(trans, "Loaded NVM file %s (%zu bytes)\n",
		 nvm_file_name, fw_entry->size);

	अगर (fw_entry->size > MAX_NVM_खाता_LEN) अणु
		IWL_ERR(trans, "NVM file too large\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	eof = fw_entry->data + fw_entry->size;
	dword_buff = (__le32 *)fw_entry->data;

	/* some NVM file will contain a header.
	 * The header is identअगरied by 2 dwords header as follow:
	 * dword[0] = 0x2A504C54
	 * dword[1] = 0x4E564D2A
	 *
	 * This header must be skipped when providing the NVM data to the FW.
	 */
	अगर (fw_entry->size > NVM_HEADER_SIZE &&
	    dword_buff[0] == cpu_to_le32(NVM_HEADER_0) &&
	    dword_buff[1] == cpu_to_le32(NVM_HEADER_1)) अणु
		file_sec = (व्योम *)(fw_entry->data + NVM_HEADER_SIZE);
		IWL_INFO(trans, "NVM Version %08X\n", le32_to_cpu(dword_buff[2]));
		IWL_INFO(trans, "NVM Manufacturing date %08X\n",
			 le32_to_cpu(dword_buff[3]));

		/* nvm file validation, dword_buff[2] holds the file version */
		अगर (trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_8000 &&
		    CSR_HW_REV_STEP(trans->hw_rev) == SILICON_C_STEP &&
		    le32_to_cpu(dword_buff[2]) < 0xE4A) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		file_sec = (व्योम *)fw_entry->data;
	पूर्ण

	जबतक (true) अणु
		अगर (file_sec->data > eof) अणु
			IWL_ERR(trans,
				"ERROR - NVM file too short for section header\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* check क्रम खातापूर्ण marker */
		अगर (!file_sec->word1 && !file_sec->word2) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (trans->cfg->nvm_type != IWL_NVM_EXT) अणु
			section_size =
				2 * NVM_WORD1_LEN(le16_to_cpu(file_sec->word1));
			section_id = NVM_WORD2_ID(le16_to_cpu(file_sec->word2));
		पूर्ण अन्यथा अणु
			section_size = 2 * EXT_NVM_WORD2_LEN(
						le16_to_cpu(file_sec->word2));
			section_id = EXT_NVM_WORD1_ID(
						le16_to_cpu(file_sec->word1));
		पूर्ण

		अगर (section_size > max_section_size) अणु
			IWL_ERR(trans, "ERROR - section too large (%d)\n",
				section_size);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (!section_size) अणु
			IWL_ERR(trans, "ERROR - section empty\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (file_sec->data + section_size > eof) अणु
			IWL_ERR(trans,
				"ERROR - NVM file too short for section (%d bytes)\n",
				section_size);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (WARN(section_id >= NVM_MAX_NUM_SECTIONS,
			 "Invalid NVM section ID %d\n", section_id)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		temp = kmemdup(file_sec->data, section_size, GFP_KERNEL);
		अगर (!temp) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		iwl_nvm_fixups(trans->hw_id, section_id, temp, section_size);

		kमुक्त(nvm_sections[section_id].data);
		nvm_sections[section_id].data = temp;
		nvm_sections[section_id].length = section_size;

		/* advance to the next section */
		file_sec = (व्योम *)(file_sec->data + section_size);
	पूर्ण
out:
	release_firmware(fw_entry);
	वापस ret;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_पढ़ो_बाह्यal_nvm);

काष्ठा iwl_nvm_data *iwl_get_nvm(काष्ठा iwl_trans *trans,
				 स्थिर काष्ठा iwl_fw *fw)
अणु
	काष्ठा iwl_nvm_get_info cmd = अणुपूर्ण;
	काष्ठा iwl_nvm_data *nvm;
	काष्ठा iwl_host_cmd hcmd = अणु
		.flags = CMD_WANT_SKB | CMD_SEND_IN_RFKILL,
		.data = अणु &cmd, पूर्ण,
		.len = अणु माप(cmd) पूर्ण,
		.id = WIDE_ID(REGULATORY_AND_NVM_GROUP, NVM_GET_INFO)
	पूर्ण;
	पूर्णांक  ret;
	bool empty_otp;
	u32 mac_flags;
	u32 sbands_flags = 0;
	/*
	 * All the values in iwl_nvm_get_info_rsp v4 are the same as
	 * in v3, except क्रम the channel profile part of the
	 * regulatory.  So we can just access the new काष्ठा, with the
	 * exception of the latter.
	 */
	काष्ठा iwl_nvm_get_info_rsp *rsp;
	काष्ठा iwl_nvm_get_info_rsp_v3 *rsp_v3;
	bool v4 = fw_has_api(&fw->ucode_capa,
			     IWL_UCODE_TLV_API_REGULATORY_NVM_INFO);
	माप_प्रकार rsp_size = v4 ? माप(*rsp) : माप(*rsp_v3);
	व्योम *channel_profile;

	ret = iwl_trans_send_cmd(trans, &hcmd);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (WARN(iwl_rx_packet_payload_len(hcmd.resp_pkt) != rsp_size,
		 "Invalid payload len in NVM response from FW %d",
		 iwl_rx_packet_payload_len(hcmd.resp_pkt))) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	rsp = (व्योम *)hcmd.resp_pkt->data;
	empty_otp = !!(le32_to_cpu(rsp->general.flags) &
		       NVM_GENERAL_FLAGS_EMPTY_OTP);
	अगर (empty_otp)
		IWL_INFO(trans, "OTP is empty\n");

	nvm = kzalloc(काष्ठा_size(nvm, channels, IWL_NUM_CHANNELS), GFP_KERNEL);
	अगर (!nvm) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	iwl_set_hw_address_from_csr(trans, nvm);
	/* TODO: अगर platक्रमm NVM has MAC address - override it here */

	अगर (!is_valid_ether_addr(nvm->hw_addr)) अणु
		IWL_ERR(trans, "no valid mac address was found\n");
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	IWL_INFO(trans, "base HW address: %pM\n", nvm->hw_addr);

	/* Initialize general data */
	nvm->nvm_version = le16_to_cpu(rsp->general.nvm_version);
	nvm->n_hw_addrs = rsp->general.n_hw_addrs;
	अगर (nvm->n_hw_addrs == 0)
		IWL_WARN(trans,
			 "Firmware declares no reserved mac addresses. OTP is empty: %d\n",
			 empty_otp);

	/* Initialize MAC sku data */
	mac_flags = le32_to_cpu(rsp->mac_sku.mac_sku_flags);
	nvm->sku_cap_11ac_enable =
		!!(mac_flags & NVM_MAC_SKU_FLAGS_802_11AC_ENABLED);
	nvm->sku_cap_11n_enable =
		!!(mac_flags & NVM_MAC_SKU_FLAGS_802_11N_ENABLED);
	nvm->sku_cap_11ax_enable =
		!!(mac_flags & NVM_MAC_SKU_FLAGS_802_11AX_ENABLED);
	nvm->sku_cap_band_24ghz_enable =
		!!(mac_flags & NVM_MAC_SKU_FLAGS_BAND_2_4_ENABLED);
	nvm->sku_cap_band_52ghz_enable =
		!!(mac_flags & NVM_MAC_SKU_FLAGS_BAND_5_2_ENABLED);
	nvm->sku_cap_mimo_disabled =
		!!(mac_flags & NVM_MAC_SKU_FLAGS_MIMO_DISABLED);

	/* Initialize PHY sku data */
	nvm->valid_tx_ant = (u8)le32_to_cpu(rsp->phy_sku.tx_chains);
	nvm->valid_rx_ant = (u8)le32_to_cpu(rsp->phy_sku.rx_chains);

	अगर (le32_to_cpu(rsp->regulatory.lar_enabled) &&
	    fw_has_capa(&fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_LAR_SUPPORT)) अणु
		nvm->lar_enabled = true;
		sbands_flags |= IWL_NVM_SBANDS_FLAGS_LAR;
	पूर्ण

	rsp_v3 = (व्योम *)rsp;
	channel_profile = v4 ? (व्योम *)rsp->regulatory.channel_profile :
			  (व्योम *)rsp_v3->regulatory.channel_profile;

	iwl_init_sbands(trans, nvm,
			channel_profile,
			nvm->valid_tx_ant & fw->valid_tx_ant,
			nvm->valid_rx_ant & fw->valid_rx_ant,
			sbands_flags, v4);

	iwl_मुक्त_resp(&hcmd);
	वापस nvm;

err_मुक्त:
	kमुक्त(nvm);
out:
	iwl_मुक्त_resp(&hcmd);
	वापस ERR_PTR(ret);
पूर्ण
IWL_EXPORT_SYMBOL(iwl_get_nvm);
