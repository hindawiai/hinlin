<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2005-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2015 Intel Mobile Communications GmbH
 */
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश "iwl-drv.h"
#समावेश "iwl-modparams.h"
#समावेश "iwl-eeprom-parse.h"

/* EEPROM offset definitions */

/* indirect access definitions */
#घोषणा ADDRESS_MSK                 0x0000FFFF
#घोषणा INसूचीECT_TYPE_MSK           0x000F0000
#घोषणा INसूचीECT_HOST               0x00010000
#घोषणा INसूचीECT_GENERAL            0x00020000
#घोषणा INसूचीECT_REGULATORY         0x00030000
#घोषणा INसूचीECT_CALIBRATION        0x00040000
#घोषणा INसूचीECT_PROCESS_ADJST      0x00050000
#घोषणा INसूचीECT_OTHERS             0x00060000
#घोषणा INसूचीECT_TXP_LIMIT          0x00070000
#घोषणा INसूचीECT_TXP_LIMIT_SIZE     0x00080000
#घोषणा INसूचीECT_ADDRESS            0x00100000

/* corresponding link offsets in EEPROM */
#घोषणा EEPROM_LINK_HOST             (2*0x64)
#घोषणा EEPROM_LINK_GENERAL          (2*0x65)
#घोषणा EEPROM_LINK_REGULATORY       (2*0x66)
#घोषणा EEPROM_LINK_CALIBRATION      (2*0x67)
#घोषणा EEPROM_LINK_PROCESS_ADJST    (2*0x68)
#घोषणा EEPROM_LINK_OTHERS           (2*0x69)
#घोषणा EEPROM_LINK_TXP_LIMIT        (2*0x6a)
#घोषणा EEPROM_LINK_TXP_LIMIT_SIZE   (2*0x6b)

/* General */
#घोषणा EEPROM_DEVICE_ID                    (2*0x08)	/* 2 bytes */
#घोषणा EEPROM_SUBSYSTEM_ID		    (2*0x0A)	/* 2 bytes */
#घोषणा EEPROM_MAC_ADDRESS                  (2*0x15)	/* 6  bytes */
#घोषणा EEPROM_BOARD_REVISION               (2*0x35)	/* 2  bytes */
#घोषणा EEPROM_BOARD_PBA_NUMBER             (2*0x3B+1)	/* 9  bytes */
#घोषणा EEPROM_VERSION                      (2*0x44)	/* 2  bytes */
#घोषणा EEPROM_SKU_CAP                      (2*0x45)	/* 2  bytes */
#घोषणा EEPROM_OEM_MODE                     (2*0x46)	/* 2  bytes */
#घोषणा EEPROM_RADIO_CONFIG                 (2*0x48)	/* 2  bytes */
#घोषणा EEPROM_NUM_MAC_ADDRESS              (2*0x4C)	/* 2  bytes */

/* calibration */
काष्ठा iwl_eeprom_calib_hdr अणु
	u8 version;
	u8 pa_type;
	__le16 voltage;
पूर्ण __packed;

#घोषणा EEPROM_CALIB_ALL	(INसूचीECT_ADDRESS | INसूचीECT_CALIBRATION)
#घोषणा EEPROM_XTAL		((2*0x128) | EEPROM_CALIB_ALL)

/* temperature */
#घोषणा EEPROM_KELVIN_TEMPERATURE	((2*0x12A) | EEPROM_CALIB_ALL)
#घोषणा EEPROM_RAW_TEMPERATURE		((2*0x12B) | EEPROM_CALIB_ALL)

/* SKU Capabilities (actual values from EEPROM definition) */
क्रमागत eeprom_sku_bits अणु
	EEPROM_SKU_CAP_BAND_24GHZ	= BIT(4),
	EEPROM_SKU_CAP_BAND_52GHZ	= BIT(5),
	EEPROM_SKU_CAP_11N_ENABLE	= BIT(6),
	EEPROM_SKU_CAP_AMT_ENABLE	= BIT(7),
	EEPROM_SKU_CAP_IPAN_ENABLE	= BIT(8)
पूर्ण;

/* radio config bits (actual values from EEPROM definition) */
#घोषणा EEPROM_RF_CFG_TYPE_MSK(x)   (x & 0x3)         /* bits 0-1   */
#घोषणा EEPROM_RF_CFG_STEP_MSK(x)   ((x >> 2)  & 0x3) /* bits 2-3   */
#घोषणा EEPROM_RF_CFG_DASH_MSK(x)   ((x >> 4)  & 0x3) /* bits 4-5   */
#घोषणा EEPROM_RF_CFG_PNUM_MSK(x)   ((x >> 6)  & 0x3) /* bits 6-7   */
#घोषणा EEPROM_RF_CFG_TX_ANT_MSK(x) ((x >> 8)  & 0xF) /* bits 8-11  */
#घोषणा EEPROM_RF_CFG_RX_ANT_MSK(x) ((x >> 12) & 0xF) /* bits 12-15 */


/*
 * EEPROM bands
 * These are the channel numbers from each band in the order
 * that they are stored in the EEPROM band inक्रमmation. Note
 * that EEPROM bands aren't the same as mac80211 bands, and
 * there are even special "ht40 bands" in the EEPROM.
 */
अटल स्थिर u8 iwl_eeprom_band_1[14] = अणु /* 2.4 GHz */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
पूर्ण;

अटल स्थिर u8 iwl_eeprom_band_2[] = अणु	/* 4915-5080MHz */
	183, 184, 185, 187, 188, 189, 192, 196, 7, 8, 11, 12, 16
पूर्ण;

अटल स्थिर u8 iwl_eeprom_band_3[] = अणु	/* 5170-5320MHz */
	34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64
पूर्ण;

अटल स्थिर u8 iwl_eeprom_band_4[] = अणु	/* 5500-5700MHz */
	100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140
पूर्ण;

अटल स्थिर u8 iwl_eeprom_band_5[] = अणु	/* 5725-5825MHz */
	145, 149, 153, 157, 161, 165
पूर्ण;

अटल स्थिर u8 iwl_eeprom_band_6[] = अणु	/* 2.4 ht40 channel */
	1, 2, 3, 4, 5, 6, 7
पूर्ण;

अटल स्थिर u8 iwl_eeprom_band_7[] = अणु	/* 5.2 ht40 channel */
	36, 44, 52, 60, 100, 108, 116, 124, 132, 149, 157
पूर्ण;

#घोषणा IWL_NUM_CHANNELS	(ARRAY_SIZE(iwl_eeprom_band_1) + \
				 ARRAY_SIZE(iwl_eeprom_band_2) + \
				 ARRAY_SIZE(iwl_eeprom_band_3) + \
				 ARRAY_SIZE(iwl_eeprom_band_4) + \
				 ARRAY_SIZE(iwl_eeprom_band_5))

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

/* EEPROM पढ़ोing functions */

अटल u16 iwl_eeprom_query16(स्थिर u8 *eeprom, माप_प्रकार eeprom_size, पूर्णांक offset)
अणु
	अगर (WARN_ON(offset + माप(u16) > eeprom_size))
		वापस 0;
	वापस le16_to_cpup((__le16 *)(eeprom + offset));
पूर्ण

अटल u32 eeprom_indirect_address(स्थिर u8 *eeprom, माप_प्रकार eeprom_size,
				   u32 address)
अणु
	u16 offset = 0;

	अगर ((address & INसूचीECT_ADDRESS) == 0)
		वापस address;

	चयन (address & INसूचीECT_TYPE_MSK) अणु
	हाल INसूचीECT_HOST:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_HOST);
		अवरोध;
	हाल INसूचीECT_GENERAL:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_GENERAL);
		अवरोध;
	हाल INसूचीECT_REGULATORY:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_REGULATORY);
		अवरोध;
	हाल INसूचीECT_TXP_LIMIT:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_TXP_LIMIT);
		अवरोध;
	हाल INसूचीECT_TXP_LIMIT_SIZE:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_TXP_LIMIT_SIZE);
		अवरोध;
	हाल INसूचीECT_CALIBRATION:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_CALIBRATION);
		अवरोध;
	हाल INसूचीECT_PROCESS_ADJST:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_PROCESS_ADJST);
		अवरोध;
	हाल INसूचीECT_OTHERS:
		offset = iwl_eeprom_query16(eeprom, eeprom_size,
					    EEPROM_LINK_OTHERS);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	/* translate the offset from words to byte */
	वापस (address & ADDRESS_MSK) + (offset << 1);
पूर्ण

अटल स्थिर u8 *iwl_eeprom_query_addr(स्थिर u8 *eeprom, माप_प्रकार eeprom_size,
				       u32 offset)
अणु
	u32 address = eeprom_indirect_address(eeprom, eeprom_size, offset);

	अगर (WARN_ON(address >= eeprom_size))
		वापस शून्य;

	वापस &eeprom[address];
पूर्ण

अटल पूर्णांक iwl_eeprom_पढ़ो_calib(स्थिर u8 *eeprom, माप_प्रकार eeprom_size,
				 काष्ठा iwl_nvm_data *data)
अणु
	काष्ठा iwl_eeprom_calib_hdr *hdr;

	hdr = (व्योम *)iwl_eeprom_query_addr(eeprom, eeprom_size,
					    EEPROM_CALIB_ALL);
	अगर (!hdr)
		वापस -ENODATA;
	data->calib_version = hdr->version;
	data->calib_voltage = hdr->voltage;

	वापस 0;
पूर्ण

/**
 * क्रमागत iwl_eeprom_channel_flags - channel flags in EEPROM
 * @EEPROM_CHANNEL_VALID: channel is usable क्रम this SKU/geo
 * @EEPROM_CHANNEL_IBSS: usable as an IBSS channel
 * @EEPROM_CHANNEL_ACTIVE: active scanning allowed
 * @EEPROM_CHANNEL_RADAR: radar detection required
 * @EEPROM_CHANNEL_WIDE: 20 MHz channel okay (?)
 * @EEPROM_CHANNEL_DFS: dynamic freq selection candidate
 */
क्रमागत iwl_eeprom_channel_flags अणु
	EEPROM_CHANNEL_VALID = BIT(0),
	EEPROM_CHANNEL_IBSS = BIT(1),
	EEPROM_CHANNEL_ACTIVE = BIT(3),
	EEPROM_CHANNEL_RADAR = BIT(4),
	EEPROM_CHANNEL_WIDE = BIT(5),
	EEPROM_CHANNEL_DFS = BIT(7),
पूर्ण;

/**
 * काष्ठा iwl_eeprom_channel - EEPROM channel data
 * @flags: %EEPROM_CHANNEL_* flags
 * @max_घातer_avg: max घातer (in dBm) on this channel, at most 31 dBm
 */
काष्ठा iwl_eeprom_channel अणु
	u8 flags;
	s8 max_घातer_avg;
पूर्ण __packed;


क्रमागत iwl_eeprom_enhanced_txpwr_flags अणु
	IWL_EEPROM_ENH_TXP_FL_VALID = BIT(0),
	IWL_EEPROM_ENH_TXP_FL_BAND_52G = BIT(1),
	IWL_EEPROM_ENH_TXP_FL_OFDM = BIT(2),
	IWL_EEPROM_ENH_TXP_FL_40MHZ = BIT(3),
	IWL_EEPROM_ENH_TXP_FL_HT_AP = BIT(4),
	IWL_EEPROM_ENH_TXP_FL_RES1 = BIT(5),
	IWL_EEPROM_ENH_TXP_FL_RES2 = BIT(6),
	IWL_EEPROM_ENH_TXP_FL_COMMON_TYPE = BIT(7),
पूर्ण;

/**
 * काष्ठा iwl_eeprom_enhanced_txpwr
 * @flags: entry flags
 * @channel: channel number
 * @chain_a_max: chain a max घातer in 1/2 dBm
 * @chain_b_max: chain b max घातer in 1/2 dBm
 * @chain_c_max: chain c max घातer in 1/2 dBm
 * @delta_20_in_40: 20-in-40 deltas (hi/lo)
 * @mimo2_max: mimo2 max घातer in 1/2 dBm
 * @mimo3_max: mimo3 max घातer in 1/2 dBm
 *
 * This काष्ठाure presents the enhanced regulatory tx घातer limit layout
 * in an EEPROM image.
 */
काष्ठा iwl_eeprom_enhanced_txpwr अणु
	u8 flags;
	u8 channel;
	s8 chain_a_max;
	s8 chain_b_max;
	s8 chain_c_max;
	u8 delta_20_in_40;
	s8 mimo2_max;
	s8 mimo3_max;
पूर्ण __packed;

अटल s8 iwl_get_max_txpwr_half_dbm(स्थिर काष्ठा iwl_nvm_data *data,
				     काष्ठा iwl_eeprom_enhanced_txpwr *txp)
अणु
	s8 result = 0; /* (.5 dBm) */

	/* Take the highest tx घातer from any valid chains */
	अगर (data->valid_tx_ant & ANT_A && txp->chain_a_max > result)
		result = txp->chain_a_max;

	अगर (data->valid_tx_ant & ANT_B && txp->chain_b_max > result)
		result = txp->chain_b_max;

	अगर (data->valid_tx_ant & ANT_C && txp->chain_c_max > result)
		result = txp->chain_c_max;

	अगर ((data->valid_tx_ant == ANT_AB ||
	     data->valid_tx_ant == ANT_BC ||
	     data->valid_tx_ant == ANT_AC) && txp->mimo2_max > result)
		result = txp->mimo2_max;

	अगर (data->valid_tx_ant == ANT_ABC && txp->mimo3_max > result)
		result = txp->mimo3_max;

	वापस result;
पूर्ण

#घोषणा EEPROM_TXP_OFFS	(0x00 | INसूचीECT_ADDRESS | INसूचीECT_TXP_LIMIT)
#घोषणा EEPROM_TXP_ENTRY_LEN माप(काष्ठा iwl_eeprom_enhanced_txpwr)
#घोषणा EEPROM_TXP_SZ_OFFS (0x00 | INसूचीECT_ADDRESS | INसूचीECT_TXP_LIMIT_SIZE)

#घोषणा TXP_CHECK_AND_PRINT(x) \
	((txp->flags & IWL_EEPROM_ENH_TXP_FL_##x) ? # x " " : "")

अटल व्योम
iwl_eeprom_enh_txp_पढ़ो_element(काष्ठा iwl_nvm_data *data,
				काष्ठा iwl_eeprom_enhanced_txpwr *txp,
				पूर्णांक n_channels, s8 max_txघातer_avg)
अणु
	पूर्णांक ch_idx;
	क्रमागत nl80211_band band;

	band = txp->flags & IWL_EEPROM_ENH_TXP_FL_BAND_52G ?
		NL80211_BAND_5GHZ : NL80211_BAND_2GHZ;

	क्रम (ch_idx = 0; ch_idx < n_channels; ch_idx++) अणु
		काष्ठा ieee80211_channel *chan = &data->channels[ch_idx];

		/* update matching channel or from common data only */
		अगर (txp->channel != 0 && chan->hw_value != txp->channel)
			जारी;

		/* update matching band only */
		अगर (band != chan->band)
			जारी;

		अगर (chan->max_घातer < max_txघातer_avg &&
		    !(txp->flags & IWL_EEPROM_ENH_TXP_FL_40MHZ))
			chan->max_घातer = max_txघातer_avg;
	पूर्ण
पूर्ण

अटल व्योम iwl_eeprom_enhanced_txघातer(काष्ठा device *dev,
					काष्ठा iwl_nvm_data *data,
					स्थिर u8 *eeprom, माप_प्रकार eeprom_size,
					पूर्णांक n_channels)
अणु
	काष्ठा iwl_eeprom_enhanced_txpwr *txp_array, *txp;
	पूर्णांक idx, entries;
	__le16 *txp_len;
	s8 max_txp_avg_halfdbm;

	BUILD_BUG_ON(माप(काष्ठा iwl_eeprom_enhanced_txpwr) != 8);

	/* the length is in 16-bit words, but we want entries */
	txp_len = (__le16 *)iwl_eeprom_query_addr(eeprom, eeprom_size,
						  EEPROM_TXP_SZ_OFFS);
	entries = le16_to_cpup(txp_len) * 2 / EEPROM_TXP_ENTRY_LEN;

	txp_array = (व्योम *)iwl_eeprom_query_addr(eeprom, eeprom_size,
						  EEPROM_TXP_OFFS);

	क्रम (idx = 0; idx < entries; idx++) अणु
		txp = &txp_array[idx];
		/* skip invalid entries */
		अगर (!(txp->flags & IWL_EEPROM_ENH_TXP_FL_VALID))
			जारी;

		IWL_DEBUG_EEPROM(dev, "%s %d:\t %s%s%s%s%s%s%s%s (0x%02x)\n",
				 (txp->channel && (txp->flags &
					IWL_EEPROM_ENH_TXP_FL_COMMON_TYPE)) ?
					"Common " : (txp->channel) ?
					"Channel" : "Common",
				 (txp->channel),
				 TXP_CHECK_AND_PRINT(VALID),
				 TXP_CHECK_AND_PRINT(BAND_52G),
				 TXP_CHECK_AND_PRINT(OFDM),
				 TXP_CHECK_AND_PRINT(40MHZ),
				 TXP_CHECK_AND_PRINT(HT_AP),
				 TXP_CHECK_AND_PRINT(RES1),
				 TXP_CHECK_AND_PRINT(RES2),
				 TXP_CHECK_AND_PRINT(COMMON_TYPE),
				 txp->flags);
		IWL_DEBUG_EEPROM(dev,
				 "\t\t chain_A: %d chain_B: %d chain_C: %d\n",
				 txp->chain_a_max, txp->chain_b_max,
				 txp->chain_c_max);
		IWL_DEBUG_EEPROM(dev,
				 "\t\t MIMO2: %d MIMO3: %d High 20_on_40: 0x%02x Low 20_on_40: 0x%02x\n",
				 txp->mimo2_max, txp->mimo3_max,
				 ((txp->delta_20_in_40 & 0xf0) >> 4),
				 (txp->delta_20_in_40 & 0x0f));

		max_txp_avg_halfdbm = iwl_get_max_txpwr_half_dbm(data, txp);

		iwl_eeprom_enh_txp_पढ़ो_element(data, txp, n_channels,
				DIV_ROUND_UP(max_txp_avg_halfdbm, 2));

		अगर (max_txp_avg_halfdbm > data->max_tx_pwr_half_dbm)
			data->max_tx_pwr_half_dbm = max_txp_avg_halfdbm;
	पूर्ण
पूर्ण

अटल व्योम iwl_init_band_reference(स्थिर काष्ठा iwl_cfg *cfg,
				    स्थिर u8 *eeprom, माप_प्रकार eeprom_size,
				    पूर्णांक eeprom_band, पूर्णांक *eeprom_ch_count,
				    स्थिर काष्ठा iwl_eeprom_channel **ch_info,
				    स्थिर u8 **eeprom_ch_array)
अणु
	u32 offset = cfg->eeprom_params->regulatory_bands[eeprom_band - 1];

	offset |= INसूचीECT_ADDRESS | INसूचीECT_REGULATORY;

	*ch_info = (व्योम *)iwl_eeprom_query_addr(eeprom, eeprom_size, offset);

	चयन (eeprom_band) अणु
	हाल 1:		/* 2.4GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_1);
		*eeprom_ch_array = iwl_eeprom_band_1;
		अवरोध;
	हाल 2:		/* 4.9GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_2);
		*eeprom_ch_array = iwl_eeprom_band_2;
		अवरोध;
	हाल 3:		/* 5.2GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_3);
		*eeprom_ch_array = iwl_eeprom_band_3;
		अवरोध;
	हाल 4:		/* 5.5GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_4);
		*eeprom_ch_array = iwl_eeprom_band_4;
		अवरोध;
	हाल 5:		/* 5.7GHz band */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_5);
		*eeprom_ch_array = iwl_eeprom_band_5;
		अवरोध;
	हाल 6:		/* 2.4GHz ht40 channels */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_6);
		*eeprom_ch_array = iwl_eeprom_band_6;
		अवरोध;
	हाल 7:		/* 5 GHz ht40 channels */
		*eeprom_ch_count = ARRAY_SIZE(iwl_eeprom_band_7);
		*eeprom_ch_array = iwl_eeprom_band_7;
		अवरोध;
	शेष:
		*eeprom_ch_count = 0;
		*eeprom_ch_array = शून्य;
		WARN_ON(1);
	पूर्ण
पूर्ण

#घोषणा CHECK_AND_PRINT(x) \
	((eeprom_ch->flags & EEPROM_CHANNEL_##x) ? # x " " : "")

अटल व्योम iwl_mod_ht40_chan_info(काष्ठा device *dev,
				   काष्ठा iwl_nvm_data *data, पूर्णांक n_channels,
				   क्रमागत nl80211_band band, u16 channel,
				   स्थिर काष्ठा iwl_eeprom_channel *eeprom_ch,
				   u8 clear_ht40_extension_channel)
अणु
	काष्ठा ieee80211_channel *chan = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < n_channels; i++) अणु
		अगर (data->channels[i].band != band)
			जारी;
		अगर (data->channels[i].hw_value != channel)
			जारी;
		chan = &data->channels[i];
		अवरोध;
	पूर्ण

	अगर (!chan)
		वापस;

	IWL_DEBUG_EEPROM(dev,
			 "HT40 Ch. %d [%sGHz] %s%s%s%s%s(0x%02x %ddBm): Ad-Hoc %ssupported\n",
			 channel,
			 band == NL80211_BAND_5GHZ ? "5.2" : "2.4",
			 CHECK_AND_PRINT(IBSS),
			 CHECK_AND_PRINT(ACTIVE),
			 CHECK_AND_PRINT(RADAR),
			 CHECK_AND_PRINT(WIDE),
			 CHECK_AND_PRINT(DFS),
			 eeprom_ch->flags,
			 eeprom_ch->max_घातer_avg,
			 ((eeprom_ch->flags & EEPROM_CHANNEL_IBSS) &&
			  !(eeprom_ch->flags & EEPROM_CHANNEL_RADAR)) ? ""
								      : "not ");

	अगर (eeprom_ch->flags & EEPROM_CHANNEL_VALID)
		chan->flags &= ~clear_ht40_extension_channel;
पूर्ण

#घोषणा CHECK_AND_PRINT_I(x)	\
	((eeprom_ch_info[ch_idx].flags & EEPROM_CHANNEL_##x) ? # x " " : "")

अटल पूर्णांक iwl_init_channel_map(काष्ठा device *dev, स्थिर काष्ठा iwl_cfg *cfg,
				काष्ठा iwl_nvm_data *data,
				स्थिर u8 *eeprom, माप_प्रकार eeprom_size)
अणु
	पूर्णांक band, ch_idx;
	स्थिर काष्ठा iwl_eeprom_channel *eeprom_ch_info;
	स्थिर u8 *eeprom_ch_array;
	पूर्णांक eeprom_ch_count;
	पूर्णांक n_channels = 0;

	/*
	 * Loop through the 5 EEPROM bands and add them to the parse list
	 */
	क्रम (band = 1; band <= 5; band++) अणु
		काष्ठा ieee80211_channel *channel;

		iwl_init_band_reference(cfg, eeprom, eeprom_size, band,
					&eeprom_ch_count, &eeprom_ch_info,
					&eeprom_ch_array);

		/* Loop through each band adding each of the channels */
		क्रम (ch_idx = 0; ch_idx < eeprom_ch_count; ch_idx++) अणु
			स्थिर काष्ठा iwl_eeprom_channel *eeprom_ch;

			eeprom_ch = &eeprom_ch_info[ch_idx];

			अगर (!(eeprom_ch->flags & EEPROM_CHANNEL_VALID)) अणु
				IWL_DEBUG_EEPROM(dev,
						 "Ch. %d Flags %x [%sGHz] - No traffic\n",
						 eeprom_ch_array[ch_idx],
						 eeprom_ch_info[ch_idx].flags,
						 (band != 1) ? "5.2" : "2.4");
				जारी;
			पूर्ण

			channel = &data->channels[n_channels];
			n_channels++;

			channel->hw_value = eeprom_ch_array[ch_idx];
			channel->band = (band == 1) ? NL80211_BAND_2GHZ
						    : NL80211_BAND_5GHZ;
			channel->center_freq =
				ieee80211_channel_to_frequency(
					channel->hw_value, channel->band);

			/* set no-HT40, will enable as appropriate later */
			channel->flags = IEEE80211_CHAN_NO_HT40;

			अगर (!(eeprom_ch->flags & EEPROM_CHANNEL_IBSS))
				channel->flags |= IEEE80211_CHAN_NO_IR;

			अगर (!(eeprom_ch->flags & EEPROM_CHANNEL_ACTIVE))
				channel->flags |= IEEE80211_CHAN_NO_IR;

			अगर (eeprom_ch->flags & EEPROM_CHANNEL_RADAR)
				channel->flags |= IEEE80211_CHAN_RADAR;

			/* Initialize regulatory-based run-समय data */
			channel->max_घातer =
				eeprom_ch_info[ch_idx].max_घातer_avg;
			IWL_DEBUG_EEPROM(dev,
					 "Ch. %d [%sGHz] %s%s%s%s%s%s(0x%02x %ddBm): Ad-Hoc %ssupported\n",
					 channel->hw_value,
					 (band != 1) ? "5.2" : "2.4",
					 CHECK_AND_PRINT_I(VALID),
					 CHECK_AND_PRINT_I(IBSS),
					 CHECK_AND_PRINT_I(ACTIVE),
					 CHECK_AND_PRINT_I(RADAR),
					 CHECK_AND_PRINT_I(WIDE),
					 CHECK_AND_PRINT_I(DFS),
					 eeprom_ch_info[ch_idx].flags,
					 eeprom_ch_info[ch_idx].max_घातer_avg,
					 ((eeprom_ch_info[ch_idx].flags &
							EEPROM_CHANNEL_IBSS) &&
					  !(eeprom_ch_info[ch_idx].flags &
							EEPROM_CHANNEL_RADAR))
						? "" : "not ");
		पूर्ण
	पूर्ण

	अगर (cfg->eeprom_params->enhanced_txघातer) अणु
		/*
		 * क्रम newer device (6000 series and up)
		 * EEPROM contain enhanced tx घातer inक्रमmation
		 * driver need to process addition inक्रमmation
		 * to determine the max channel tx घातer limits
		 */
		iwl_eeprom_enhanced_txघातer(dev, data, eeprom, eeprom_size,
					    n_channels);
	पूर्ण अन्यथा अणु
		/* All others use data from channel map */
		पूर्णांक i;

		data->max_tx_pwr_half_dbm = -128;

		क्रम (i = 0; i < n_channels; i++)
			data->max_tx_pwr_half_dbm =
				max_t(s8, data->max_tx_pwr_half_dbm,
				      data->channels[i].max_घातer * 2);
	पूर्ण

	/* Check अगर we करो have HT40 channels */
	अगर (cfg->eeprom_params->regulatory_bands[5] ==
				EEPROM_REGULATORY_BAND_NO_HT40 &&
	    cfg->eeprom_params->regulatory_bands[6] ==
				EEPROM_REGULATORY_BAND_NO_HT40)
		वापस n_channels;

	/* Two additional EEPROM bands क्रम 2.4 and 5 GHz HT40 channels */
	क्रम (band = 6; band <= 7; band++) अणु
		क्रमागत nl80211_band ieeeband;

		iwl_init_band_reference(cfg, eeprom, eeprom_size, band,
					&eeprom_ch_count, &eeprom_ch_info,
					&eeprom_ch_array);

		/* EEPROM band 6 is 2.4, band 7 is 5 GHz */
		ieeeband = (band == 6) ? NL80211_BAND_2GHZ
				       : NL80211_BAND_5GHZ;

		/* Loop through each band adding each of the channels */
		क्रम (ch_idx = 0; ch_idx < eeprom_ch_count; ch_idx++) अणु
			/* Set up driver's info क्रम lower half */
			iwl_mod_ht40_chan_info(dev, data, n_channels, ieeeband,
					       eeprom_ch_array[ch_idx],
					       &eeprom_ch_info[ch_idx],
					       IEEE80211_CHAN_NO_HT40PLUS);

			/* Set up driver's info क्रम upper half */
			iwl_mod_ht40_chan_info(dev, data, n_channels, ieeeband,
					       eeprom_ch_array[ch_idx] + 4,
					       &eeprom_ch_info[ch_idx],
					       IEEE80211_CHAN_NO_HT40MINUS);
		पूर्ण
	पूर्ण

	वापस n_channels;
पूर्ण

पूर्णांक iwl_init_sband_channels(काष्ठा iwl_nvm_data *data,
			    काष्ठा ieee80211_supported_band *sband,
			    पूर्णांक n_channels, क्रमागत nl80211_band band)
अणु
	काष्ठा ieee80211_channel *chan = &data->channels[0];
	पूर्णांक n = 0, idx = 0;

	जबतक (idx < n_channels && chan->band != band)
		chan = &data->channels[++idx];

	sband->channels = &data->channels[idx];

	जबतक (idx < n_channels && chan->band == band) अणु
		chan = &data->channels[++idx];
		n++;
	पूर्ण

	sband->n_channels = n;

	वापस n;
पूर्ण

#घोषणा MAX_BIT_RATE_40_MHZ	150 /* Mbps */
#घोषणा MAX_BIT_RATE_20_MHZ	72 /* Mbps */

व्योम iwl_init_ht_hw_capab(काष्ठा iwl_trans *trans,
			  काष्ठा iwl_nvm_data *data,
			  काष्ठा ieee80211_sta_ht_cap *ht_info,
			  क्रमागत nl80211_band band,
			  u8 tx_chains, u8 rx_chains)
अणु
	स्थिर काष्ठा iwl_cfg *cfg = trans->cfg;
	पूर्णांक max_bit_rate = 0;

	tx_chains = hweight8(tx_chains);
	अगर (cfg->rx_with_siso_भागersity)
		rx_chains = 1;
	अन्यथा
		rx_chains = hweight8(rx_chains);

	अगर (!(data->sku_cap_11n_enable) ||
	    (iwlwअगरi_mod_params.disable_11n & IWL_DISABLE_HT_ALL) ||
	    !cfg->ht_params) अणु
		ht_info->ht_supported = false;
		वापस;
	पूर्ण

	अगर (data->sku_cap_mimo_disabled)
		rx_chains = 1;

	ht_info->ht_supported = true;
	ht_info->cap = IEEE80211_HT_CAP_DSSSCCK40;

	अगर (cfg->ht_params->stbc) अणु
		ht_info->cap |= (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);

		अगर (tx_chains > 1)
			ht_info->cap |= IEEE80211_HT_CAP_TX_STBC;
	पूर्ण

	अगर (cfg->ht_params->ldpc)
		ht_info->cap |= IEEE80211_HT_CAP_LDPC_CODING;

	अगर (trans->trans_cfg->mq_rx_supported ||
	    iwlwअगरi_mod_params.amsdu_size >= IWL_AMSDU_8K)
		ht_info->cap |= IEEE80211_HT_CAP_MAX_AMSDU;

	ht_info->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_info->ampdu_density = IEEE80211_HT_MPDU_DENSITY_4;

	ht_info->mcs.rx_mask[0] = 0xFF;
	अगर (rx_chains >= 2)
		ht_info->mcs.rx_mask[1] = 0xFF;
	अगर (rx_chains >= 3)
		ht_info->mcs.rx_mask[2] = 0xFF;

	अगर (cfg->ht_params->ht_greenfield_support)
		ht_info->cap |= IEEE80211_HT_CAP_GRN_FLD;
	ht_info->cap |= IEEE80211_HT_CAP_SGI_20;

	max_bit_rate = MAX_BIT_RATE_20_MHZ;

	अगर (cfg->ht_params->ht40_bands & BIT(band)) अणु
		ht_info->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		ht_info->cap |= IEEE80211_HT_CAP_SGI_40;
		max_bit_rate = MAX_BIT_RATE_40_MHZ;
	पूर्ण

	/* Highest supported Rx data rate */
	max_bit_rate *= rx_chains;
	WARN_ON(max_bit_rate & ~IEEE80211_HT_MCS_RX_HIGHEST_MASK);
	ht_info->mcs.rx_highest = cpu_to_le16(max_bit_rate);

	/* Tx MCS capabilities */
	ht_info->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	अगर (tx_chains != rx_chains) अणु
		ht_info->mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		ht_info->mcs.tx_params |= ((tx_chains - 1) <<
				IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT);
	पूर्ण
पूर्ण

अटल व्योम iwl_init_sbands(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_cfg *cfg,
			    काष्ठा iwl_nvm_data *data,
			    स्थिर u8 *eeprom, माप_प्रकार eeprom_size)
अणु
	काष्ठा device *dev = trans->dev;
	पूर्णांक n_channels = iwl_init_channel_map(dev, cfg, data,
					      eeprom, eeprom_size);
	पूर्णांक n_used = 0;
	काष्ठा ieee80211_supported_band *sband;

	sband = &data->bands[NL80211_BAND_2GHZ];
	sband->band = NL80211_BAND_2GHZ;
	sband->bitrates = &iwl_cfg80211_rates[RATES_24_OFFS];
	sband->n_bitrates = N_RATES_24;
	n_used += iwl_init_sband_channels(data, sband, n_channels,
					  NL80211_BAND_2GHZ);
	iwl_init_ht_hw_capab(trans, data, &sband->ht_cap, NL80211_BAND_2GHZ,
			     data->valid_tx_ant, data->valid_rx_ant);

	sband = &data->bands[NL80211_BAND_5GHZ];
	sband->band = NL80211_BAND_5GHZ;
	sband->bitrates = &iwl_cfg80211_rates[RATES_52_OFFS];
	sband->n_bitrates = N_RATES_52;
	n_used += iwl_init_sband_channels(data, sband, n_channels,
					  NL80211_BAND_5GHZ);
	iwl_init_ht_hw_capab(trans, data, &sband->ht_cap, NL80211_BAND_5GHZ,
			     data->valid_tx_ant, data->valid_rx_ant);

	अगर (n_channels != n_used)
		IWL_ERR_DEV(dev, "EEPROM: used only %d of %d channels\n",
			    n_used, n_channels);
पूर्ण

/* EEPROM data functions */

काष्ठा iwl_nvm_data *
iwl_parse_eeprom_data(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_cfg *cfg,
		      स्थिर u8 *eeprom, माप_प्रकार eeprom_size)
अणु
	काष्ठा iwl_nvm_data *data;
	काष्ठा device *dev = trans->dev;
	स्थिर व्योम *पंचांगp;
	u16 radio_cfg, sku;

	अगर (WARN_ON(!cfg || !cfg->eeprom_params))
		वापस शून्य;

	data = kzalloc(काष्ठा_size(data, channels, IWL_NUM_CHANNELS),
		       GFP_KERNEL);
	अगर (!data)
		वापस शून्य;

	/* get MAC address(es) */
	पंचांगp = iwl_eeprom_query_addr(eeprom, eeprom_size, EEPROM_MAC_ADDRESS);
	अगर (!पंचांगp)
		जाओ err_मुक्त;
	स_नकल(data->hw_addr, पंचांगp, ETH_ALEN);
	data->n_hw_addrs = iwl_eeprom_query16(eeprom, eeprom_size,
					      EEPROM_NUM_MAC_ADDRESS);

	अगर (iwl_eeprom_पढ़ो_calib(eeprom, eeprom_size, data))
		जाओ err_मुक्त;

	पंचांगp = iwl_eeprom_query_addr(eeprom, eeprom_size, EEPROM_XTAL);
	अगर (!पंचांगp)
		जाओ err_मुक्त;
	स_नकल(data->xtal_calib, पंचांगp, माप(data->xtal_calib));

	पंचांगp = iwl_eeprom_query_addr(eeprom, eeprom_size,
				    EEPROM_RAW_TEMPERATURE);
	अगर (!पंचांगp)
		जाओ err_मुक्त;
	data->raw_temperature = *(__le16 *)पंचांगp;

	पंचांगp = iwl_eeprom_query_addr(eeprom, eeprom_size,
				    EEPROM_KELVIN_TEMPERATURE);
	अगर (!पंचांगp)
		जाओ err_मुक्त;
	data->kelvin_temperature = *(__le16 *)पंचांगp;
	data->kelvin_voltage = *((__le16 *)पंचांगp + 1);

	radio_cfg = iwl_eeprom_query16(eeprom, eeprom_size,
					     EEPROM_RADIO_CONFIG);
	data->radio_cfg_dash = EEPROM_RF_CFG_DASH_MSK(radio_cfg);
	data->radio_cfg_pnum = EEPROM_RF_CFG_PNUM_MSK(radio_cfg);
	data->radio_cfg_step = EEPROM_RF_CFG_STEP_MSK(radio_cfg);
	data->radio_cfg_type = EEPROM_RF_CFG_TYPE_MSK(radio_cfg);
	data->valid_rx_ant = EEPROM_RF_CFG_RX_ANT_MSK(radio_cfg);
	data->valid_tx_ant = EEPROM_RF_CFG_TX_ANT_MSK(radio_cfg);

	sku = iwl_eeprom_query16(eeprom, eeprom_size,
				 EEPROM_SKU_CAP);
	data->sku_cap_11n_enable = sku & EEPROM_SKU_CAP_11N_ENABLE;
	data->sku_cap_amt_enable = sku & EEPROM_SKU_CAP_AMT_ENABLE;
	data->sku_cap_band_24ghz_enable = sku & EEPROM_SKU_CAP_BAND_24GHZ;
	data->sku_cap_band_52ghz_enable = sku & EEPROM_SKU_CAP_BAND_52GHZ;
	data->sku_cap_ipan_enable = sku & EEPROM_SKU_CAP_IPAN_ENABLE;
	अगर (iwlwअगरi_mod_params.disable_11n & IWL_DISABLE_HT_ALL)
		data->sku_cap_11n_enable = false;

	data->nvm_version = iwl_eeprom_query16(eeprom, eeprom_size,
					       EEPROM_VERSION);

	/* check overrides (some devices have wrong EEPROM) */
	अगर (cfg->valid_tx_ant)
		data->valid_tx_ant = cfg->valid_tx_ant;
	अगर (cfg->valid_rx_ant)
		data->valid_rx_ant = cfg->valid_rx_ant;

	अगर (!data->valid_tx_ant || !data->valid_rx_ant) अणु
		IWL_ERR_DEV(dev, "invalid antennas (0x%x, 0x%x)\n",
			    data->valid_tx_ant, data->valid_rx_ant);
		जाओ err_मुक्त;
	पूर्ण

	iwl_init_sbands(trans, cfg, data, eeprom, eeprom_size);

	वापस data;
 err_मुक्त:
	kमुक्त(data);
	वापस शून्य;
पूर्ण
IWL_EXPORT_SYMBOL(iwl_parse_eeprom_data);
