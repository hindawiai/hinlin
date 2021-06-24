<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018 Intel Corporation
 * Copyright (C) 2015 Intel Mobile Communications GmbH
 */
#अगर_अघोषित __iwl_eeprom_parse_h__
#घोषणा __iwl_eeprom_parse_h__

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/cfg80211.h>
#समावेश "iwl-trans.h"

काष्ठा iwl_nvm_data अणु
	पूर्णांक n_hw_addrs;
	u8 hw_addr[ETH_ALEN];

	u8 calib_version;
	__le16 calib_voltage;

	__le16 raw_temperature;
	__le16 kelvin_temperature;
	__le16 kelvin_voltage;
	__le16 xtal_calib[2];

	bool sku_cap_band_24ghz_enable;
	bool sku_cap_band_52ghz_enable;
	bool sku_cap_11n_enable;
	bool sku_cap_11ac_enable;
	bool sku_cap_11ax_enable;
	bool sku_cap_amt_enable;
	bool sku_cap_ipan_enable;
	bool sku_cap_mimo_disabled;

	u16 radio_cfg_type;
	u8 radio_cfg_step;
	u8 radio_cfg_dash;
	u8 radio_cfg_pnum;
	u8 valid_tx_ant, valid_rx_ant;

	u32 nvm_version;
	s8 max_tx_pwr_half_dbm;

	bool lar_enabled;
	bool vht160_supported;
	काष्ठा ieee80211_supported_band bands[NUM_NL80211_BANDS];

	/*
	 * अगरtype data क्रम low (2.4 GHz) and high (5 and 6 GHz) bands,
	 * we can use the same क्रम 5 and 6 GHz bands because they have
	 * the same data
	 */
	काष्ठा अणु
		काष्ठा ieee80211_sband_अगरtype_data low[2];
		काष्ठा ieee80211_sband_अगरtype_data high[2];
	पूर्ण अगरtd;

	काष्ठा ieee80211_channel channels[];
पूर्ण;

/**
 * iwl_parse_eeprom_data - parse EEPROM data and वापस values
 *
 * @dev: device poपूर्णांकer we're parsing क्रम, क्रम debug only
 * @cfg: device configuration क्रम parsing and overrides
 * @eeprom: the EEPROM data
 * @eeprom_size: length of the EEPROM data
 *
 * This function parses all EEPROM values we need and then
 * वापसs a (newly allocated) काष्ठा containing all the
 * relevant values क्रम driver use. The काष्ठा must be मुक्तd
 * later with iwl_मुक्त_nvm_data().
 */
काष्ठा iwl_nvm_data *
iwl_parse_eeprom_data(काष्ठा iwl_trans *trans, स्थिर काष्ठा iwl_cfg *cfg,
		      स्थिर u8 *eeprom, माप_प्रकार eeprom_size);

पूर्णांक iwl_init_sband_channels(काष्ठा iwl_nvm_data *data,
			    काष्ठा ieee80211_supported_band *sband,
			    पूर्णांक n_channels, क्रमागत nl80211_band band);

व्योम iwl_init_ht_hw_capab(काष्ठा iwl_trans *trans,
			  काष्ठा iwl_nvm_data *data,
			  काष्ठा ieee80211_sta_ht_cap *ht_info,
			  क्रमागत nl80211_band band,
			  u8 tx_chains, u8 rx_chains);

#पूर्ण_अगर /* __iwl_eeprom_parse_h__ */
