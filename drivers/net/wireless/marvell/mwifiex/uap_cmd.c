<शैली गुरु>
/*
 * NXP Wireless LAN device driver: AP specअगरic command handling
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

#समावेश "main.h"
#समावेश "11ac.h"
#समावेश "11n.h"

/* This function parses security related parameters from cfg80211_ap_settings
 * and sets पूर्णांकo FW understandable bss_config काष्ठाure.
 */
पूर्णांक mwअगरiex_set_secure_params(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_uap_bss_param *bss_config,
			      काष्ठा cfg80211_ap_settings *params) अणु
	पूर्णांक i;
	काष्ठा mwअगरiex_wep_key wep_key;

	अगर (!params->privacy) अणु
		bss_config->protocol = PROTOCOL_NO_SECURITY;
		bss_config->key_mgmt = KEY_MGMT_NONE;
		bss_config->wpa_cfg.length = 0;
		priv->sec_info.wep_enabled = 0;
		priv->sec_info.wpa_enabled = 0;
		priv->sec_info.wpa2_enabled = 0;

		वापस 0;
	पूर्ण

	चयन (params->auth_type) अणु
	हाल NL80211_AUTHTYPE_OPEN_SYSTEM:
		bss_config->auth_mode = WLAN_AUTH_OPEN;
		अवरोध;
	हाल NL80211_AUTHTYPE_SHARED_KEY:
		bss_config->auth_mode = WLAN_AUTH_SHARED_KEY;
		अवरोध;
	हाल NL80211_AUTHTYPE_NETWORK_EAP:
		bss_config->auth_mode = WLAN_AUTH_LEAP;
		अवरोध;
	शेष:
		bss_config->auth_mode = MWIFIEX_AUTH_MODE_AUTO;
		अवरोध;
	पूर्ण

	bss_config->key_mgmt_operation |= KEY_MGMT_ON_HOST;

	क्रम (i = 0; i < params->crypto.n_akm_suites; i++) अणु
		चयन (params->crypto.akm_suites[i]) अणु
		हाल WLAN_AKM_SUITE_8021X:
			अगर (params->crypto.wpa_versions &
			    NL80211_WPA_VERSION_1) अणु
				bss_config->protocol = PROTOCOL_WPA;
				bss_config->key_mgmt = KEY_MGMT_EAP;
			पूर्ण
			अगर (params->crypto.wpa_versions &
			    NL80211_WPA_VERSION_2) अणु
				bss_config->protocol |= PROTOCOL_WPA2;
				bss_config->key_mgmt = KEY_MGMT_EAP;
			पूर्ण
			अवरोध;
		हाल WLAN_AKM_SUITE_PSK:
			अगर (params->crypto.wpa_versions &
			    NL80211_WPA_VERSION_1) अणु
				bss_config->protocol = PROTOCOL_WPA;
				bss_config->key_mgmt = KEY_MGMT_PSK;
			पूर्ण
			अगर (params->crypto.wpa_versions &
			    NL80211_WPA_VERSION_2) अणु
				bss_config->protocol |= PROTOCOL_WPA2;
				bss_config->key_mgmt = KEY_MGMT_PSK;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < params->crypto.n_ciphers_pairwise; i++) अणु
		चयन (params->crypto.ciphers_pairwise[i]) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			अगर (params->crypto.wpa_versions & NL80211_WPA_VERSION_1)
				bss_config->wpa_cfg.pairwise_cipher_wpa |=
								CIPHER_TKIP;
			अगर (params->crypto.wpa_versions & NL80211_WPA_VERSION_2)
				bss_config->wpa_cfg.pairwise_cipher_wpa2 |=
								CIPHER_TKIP;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			अगर (params->crypto.wpa_versions & NL80211_WPA_VERSION_1)
				bss_config->wpa_cfg.pairwise_cipher_wpa |=
								CIPHER_AES_CCMP;
			अगर (params->crypto.wpa_versions & NL80211_WPA_VERSION_2)
				bss_config->wpa_cfg.pairwise_cipher_wpa2 |=
								CIPHER_AES_CCMP;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (params->crypto.cipher_group) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		अगर (priv->sec_info.wep_enabled) अणु
			bss_config->protocol = PROTOCOL_STATIC_WEP;
			bss_config->key_mgmt = KEY_MGMT_NONE;
			bss_config->wpa_cfg.length = 0;

			क्रम (i = 0; i < NUM_WEP_KEYS; i++) अणु
				wep_key = priv->wep_key[i];
				bss_config->wep_cfg[i].key_index = i;

				अगर (priv->wep_key_curr_index == i)
					bss_config->wep_cfg[i].is_शेष = 1;
				अन्यथा
					bss_config->wep_cfg[i].is_शेष = 0;

				bss_config->wep_cfg[i].length =
							     wep_key.key_length;
				स_नकल(&bss_config->wep_cfg[i].key,
				       &wep_key.key_material,
				       wep_key.key_length);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		bss_config->wpa_cfg.group_cipher = CIPHER_TKIP;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		bss_config->wpa_cfg.group_cipher = CIPHER_AES_CCMP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* This function updates 11n related parameters from IE and sets them पूर्णांकo
 * bss_config काष्ठाure.
 */
व्योम
mwअगरiex_set_ht_params(काष्ठा mwअगरiex_निजी *priv,
		      काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
		      काष्ठा cfg80211_ap_settings *params)
अणु
	स्थिर u8 *ht_ie;

	अगर (!ISSUPP_11NENABLED(priv->adapter->fw_cap_info))
		वापस;

	ht_ie = cfg80211_find_ie(WLAN_EID_HT_CAPABILITY, params->beacon.tail,
				 params->beacon.tail_len);
	अगर (ht_ie) अणु
		स_नकल(&bss_cfg->ht_cap, ht_ie + 2,
		       माप(काष्ठा ieee80211_ht_cap));
		priv->ap_11n_enabled = 1;
	पूर्ण अन्यथा अणु
		स_रखो(&bss_cfg->ht_cap, 0, माप(काष्ठा ieee80211_ht_cap));
		bss_cfg->ht_cap.cap_info = cpu_to_le16(MWIFIEX_DEF_HT_CAP);
		bss_cfg->ht_cap.ampdu_params_info = MWIFIEX_DEF_AMPDU;
	पूर्ण

	वापस;
पूर्ण

/* This function updates 11ac related parameters from IE
 * and sets them पूर्णांकo bss_config काष्ठाure.
 */
व्योम mwअगरiex_set_vht_params(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
			    काष्ठा cfg80211_ap_settings *params)
अणु
	स्थिर u8 *vht_ie;

	vht_ie = cfg80211_find_ie(WLAN_EID_VHT_CAPABILITY, params->beacon.tail,
				  params->beacon.tail_len);
	अगर (vht_ie) अणु
		स_नकल(&bss_cfg->vht_cap, vht_ie + 2,
		       माप(काष्ठा ieee80211_vht_cap));
		priv->ap_11ac_enabled = 1;
	पूर्ण अन्यथा अणु
		priv->ap_11ac_enabled = 0;
	पूर्ण

	वापस;
पूर्ण

/* This function updates 11ac related parameters from IE
 * and sets them पूर्णांकo bss_config काष्ठाure.
 */
व्योम mwअगरiex_set_tpc_params(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
			    काष्ठा cfg80211_ap_settings *params)
अणु
	स्थिर u8 *tpc_ie;

	tpc_ie = cfg80211_find_ie(WLAN_EID_TPC_REQUEST, params->beacon.tail,
				  params->beacon.tail_len);
	अगर (tpc_ie)
		bss_cfg->घातer_स्थिरraपूर्णांक = *(tpc_ie + 2);
	अन्यथा
		bss_cfg->घातer_स्थिरraपूर्णांक = 0;
पूर्ण

/* Enable VHT only when cfg80211_ap_settings has VHT IE.
 * Otherwise disable VHT.
 */
व्योम mwअगरiex_set_vht_width(काष्ठा mwअगरiex_निजी *priv,
			   क्रमागत nl80211_chan_width width,
			   bool ap_11ac_enable)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_11ac_vht_cfg vht_cfg;

	vht_cfg.band_config = VHT_CFG_5GHZ;
	vht_cfg.cap_info = adapter->hw_करोt_11ac_dev_cap;

	अगर (!ap_11ac_enable) अणु
		vht_cfg.mcs_tx_set = DISABLE_VHT_MCS_SET;
		vht_cfg.mcs_rx_set = DISABLE_VHT_MCS_SET;
	पूर्ण अन्यथा अणु
		vht_cfg.mcs_tx_set = DEFAULT_VHT_MCS_SET;
		vht_cfg.mcs_rx_set = DEFAULT_VHT_MCS_SET;
	पूर्ण

	vht_cfg.misc_config  = VHT_CAP_UAP_ONLY;

	अगर (ap_11ac_enable && width >= NL80211_CHAN_WIDTH_80)
		vht_cfg.misc_config |= VHT_BW_80_160_80P80;

	mwअगरiex_send_cmd(priv, HostCmd_CMD_11AC_CFG,
			 HostCmd_ACT_GEN_SET, 0, &vht_cfg, true);

	वापस;
पूर्ण

/* This function finds supported rates IE from beacon parameter and sets
 * these rates पूर्णांकo bss_config काष्ठाure.
 */
व्योम
mwअगरiex_set_uap_rates(काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
		      काष्ठा cfg80211_ap_settings *params)
अणु
	काष्ठा ieee_types_header *rate_ie;
	पूर्णांक var_offset = दुरत्व(काष्ठा ieee80211_mgmt, u.beacon.variable);
	स्थिर u8 *var_pos = params->beacon.head + var_offset;
	पूर्णांक len = params->beacon.head_len - var_offset;
	u8 rate_len = 0;

	rate_ie = (व्योम *)cfg80211_find_ie(WLAN_EID_SUPP_RATES, var_pos, len);
	अगर (rate_ie) अणु
		अगर (rate_ie->len > MWIFIEX_SUPPORTED_RATES)
			वापस;
		स_नकल(bss_cfg->rates, rate_ie + 1, rate_ie->len);
		rate_len = rate_ie->len;
	पूर्ण

	rate_ie = (व्योम *)cfg80211_find_ie(WLAN_EID_EXT_SUPP_RATES,
					   params->beacon.tail,
					   params->beacon.tail_len);
	अगर (rate_ie) अणु
		अगर (rate_ie->len > MWIFIEX_SUPPORTED_RATES - rate_len)
			वापस;
		स_नकल(bss_cfg->rates + rate_len, rate_ie + 1, rate_ie->len);
	पूर्ण

	वापस;
पूर्ण

/* This function initializes some of mwअगरiex_uap_bss_param variables.
 * This helps FW in ignoring invalid values. These values may or may not
 * be get updated to valid ones at later stage.
 */
व्योम mwअगरiex_set_sys_config_invalid_data(काष्ठा mwअगरiex_uap_bss_param *config)
अणु
	config->bcast_ssid_ctl = 0x7F;
	config->radio_ctl = 0x7F;
	config->dtim_period = 0x7F;
	config->beacon_period = 0x7FFF;
	config->auth_mode = 0x7F;
	config->rts_threshold = 0x7FFF;
	config->frag_threshold = 0x7FFF;
	config->retry_limit = 0x7F;
	config->qos_info = 0xFF;
पूर्ण

/* This function parses BSS related parameters from काष्ठाure
 * and prepares TLVs specअगरic to WPA/WPA2 security.
 * These TLVs are appended to command buffer.
 */
अटल व्योम
mwअगरiex_uap_bss_wpa(u8 **tlv_buf, व्योम *cmd_buf, u16 *param_size)
अणु
	काष्ठा host_cmd_tlv_pwk_cipher *pwk_cipher;
	काष्ठा host_cmd_tlv_gwk_cipher *gwk_cipher;
	काष्ठा host_cmd_tlv_passphrase *passphrase;
	काष्ठा host_cmd_tlv_akmp *tlv_akmp;
	काष्ठा mwअगरiex_uap_bss_param *bss_cfg = cmd_buf;
	u16 cmd_size = *param_size;
	u8 *tlv = *tlv_buf;

	tlv_akmp = (काष्ठा host_cmd_tlv_akmp *)tlv;
	tlv_akmp->header.type = cpu_to_le16(TLV_TYPE_UAP_AKMP);
	tlv_akmp->header.len = cpu_to_le16(माप(काष्ठा host_cmd_tlv_akmp) -
					माप(काष्ठा mwअगरiex_ie_types_header));
	tlv_akmp->key_mgmt_operation = cpu_to_le16(bss_cfg->key_mgmt_operation);
	tlv_akmp->key_mgmt = cpu_to_le16(bss_cfg->key_mgmt);
	cmd_size += माप(काष्ठा host_cmd_tlv_akmp);
	tlv += माप(काष्ठा host_cmd_tlv_akmp);

	अगर (bss_cfg->wpa_cfg.pairwise_cipher_wpa & VALID_CIPHER_BITMAP) अणु
		pwk_cipher = (काष्ठा host_cmd_tlv_pwk_cipher *)tlv;
		pwk_cipher->header.type = cpu_to_le16(TLV_TYPE_PWK_CIPHER);
		pwk_cipher->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_pwk_cipher) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		pwk_cipher->proto = cpu_to_le16(PROTOCOL_WPA);
		pwk_cipher->cipher = bss_cfg->wpa_cfg.pairwise_cipher_wpa;
		cmd_size += माप(काष्ठा host_cmd_tlv_pwk_cipher);
		tlv += माप(काष्ठा host_cmd_tlv_pwk_cipher);
	पूर्ण

	अगर (bss_cfg->wpa_cfg.pairwise_cipher_wpa2 & VALID_CIPHER_BITMAP) अणु
		pwk_cipher = (काष्ठा host_cmd_tlv_pwk_cipher *)tlv;
		pwk_cipher->header.type = cpu_to_le16(TLV_TYPE_PWK_CIPHER);
		pwk_cipher->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_pwk_cipher) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		pwk_cipher->proto = cpu_to_le16(PROTOCOL_WPA2);
		pwk_cipher->cipher = bss_cfg->wpa_cfg.pairwise_cipher_wpa2;
		cmd_size += माप(काष्ठा host_cmd_tlv_pwk_cipher);
		tlv += माप(काष्ठा host_cmd_tlv_pwk_cipher);
	पूर्ण

	अगर (bss_cfg->wpa_cfg.group_cipher & VALID_CIPHER_BITMAP) अणु
		gwk_cipher = (काष्ठा host_cmd_tlv_gwk_cipher *)tlv;
		gwk_cipher->header.type = cpu_to_le16(TLV_TYPE_GWK_CIPHER);
		gwk_cipher->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_gwk_cipher) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		gwk_cipher->cipher = bss_cfg->wpa_cfg.group_cipher;
		cmd_size += माप(काष्ठा host_cmd_tlv_gwk_cipher);
		tlv += माप(काष्ठा host_cmd_tlv_gwk_cipher);
	पूर्ण

	अगर (bss_cfg->wpa_cfg.length) अणु
		passphrase = (काष्ठा host_cmd_tlv_passphrase *)tlv;
		passphrase->header.type =
				cpu_to_le16(TLV_TYPE_UAP_WPA_PASSPHRASE);
		passphrase->header.len = cpu_to_le16(bss_cfg->wpa_cfg.length);
		स_नकल(passphrase->passphrase, bss_cfg->wpa_cfg.passphrase,
		       bss_cfg->wpa_cfg.length);
		cmd_size += माप(काष्ठा mwअगरiex_ie_types_header) +
			    bss_cfg->wpa_cfg.length;
		tlv += माप(काष्ठा mwअगरiex_ie_types_header) +
				bss_cfg->wpa_cfg.length;
	पूर्ण

	*param_size = cmd_size;
	*tlv_buf = tlv;

	वापस;
पूर्ण

/* This function parses WMM related parameters from cfg80211_ap_settings
 * काष्ठाure and updates bss_config काष्ठाure.
 */
व्योम
mwअगरiex_set_wmm_params(काष्ठा mwअगरiex_निजी *priv,
		       काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
		       काष्ठा cfg80211_ap_settings *params)
अणु
	स्थिर u8 *venकरोr_ie;
	स्थिर u8 *wmm_ie;
	u8 wmm_oui[] = अणु0x00, 0x50, 0xf2, 0x02पूर्ण;

	venकरोr_ie = cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
					    WLAN_OUI_TYPE_MICROSOFT_WMM,
					    params->beacon.tail,
					    params->beacon.tail_len);
	अगर (venकरोr_ie) अणु
		wmm_ie = venकरोr_ie;
		अगर (*(wmm_ie + 1) > माप(काष्ठा mwअगरiex_types_wmm_info))
			वापस;
		स_नकल(&bss_cfg->wmm_info, wmm_ie +
		       माप(काष्ठा ieee_types_header), *(wmm_ie + 1));
		priv->wmm_enabled = 1;
	पूर्ण अन्यथा अणु
		स_रखो(&bss_cfg->wmm_info, 0, माप(bss_cfg->wmm_info));
		स_नकल(&bss_cfg->wmm_info.oui, wmm_oui, माप(wmm_oui));
		bss_cfg->wmm_info.subtype = MWIFIEX_WMM_SUBTYPE;
		bss_cfg->wmm_info.version = MWIFIEX_WMM_VERSION;
		priv->wmm_enabled = 0;
	पूर्ण

	bss_cfg->qos_info = 0x00;
	वापस;
पूर्ण
/* This function parses BSS related parameters from काष्ठाure
 * and prepares TLVs specअगरic to WEP encryption.
 * These TLVs are appended to command buffer.
 */
अटल व्योम
mwअगरiex_uap_bss_wep(u8 **tlv_buf, व्योम *cmd_buf, u16 *param_size)
अणु
	काष्ठा host_cmd_tlv_wep_key *wep_key;
	u16 cmd_size = *param_size;
	पूर्णांक i;
	u8 *tlv = *tlv_buf;
	काष्ठा mwअगरiex_uap_bss_param *bss_cfg = cmd_buf;

	क्रम (i = 0; i < NUM_WEP_KEYS; i++) अणु
		अगर (bss_cfg->wep_cfg[i].length &&
		    (bss_cfg->wep_cfg[i].length == WLAN_KEY_LEN_WEP40 ||
		     bss_cfg->wep_cfg[i].length == WLAN_KEY_LEN_WEP104)) अणु
			wep_key = (काष्ठा host_cmd_tlv_wep_key *)tlv;
			wep_key->header.type =
				cpu_to_le16(TLV_TYPE_UAP_WEP_KEY);
			wep_key->header.len =
				cpu_to_le16(bss_cfg->wep_cfg[i].length + 2);
			wep_key->key_index = bss_cfg->wep_cfg[i].key_index;
			wep_key->is_शेष = bss_cfg->wep_cfg[i].is_शेष;
			स_नकल(wep_key->key, bss_cfg->wep_cfg[i].key,
			       bss_cfg->wep_cfg[i].length);
			cmd_size += माप(काष्ठा mwअगरiex_ie_types_header) + 2 +
				    bss_cfg->wep_cfg[i].length;
			tlv += माप(काष्ठा mwअगरiex_ie_types_header) + 2 +
				    bss_cfg->wep_cfg[i].length;
		पूर्ण
	पूर्ण

	*param_size = cmd_size;
	*tlv_buf = tlv;

	वापस;
पूर्ण

/* This function enable 11D अगर userspace set the country IE.
 */
व्योम mwअगरiex_config_uap_11d(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा cfg80211_beacon_data *beacon_data)
अणु
	क्रमागत state_11d_t state_11d;
	स्थिर u8 *country_ie;

	country_ie = cfg80211_find_ie(WLAN_EID_COUNTRY, beacon_data->tail,
				      beacon_data->tail_len);
	अगर (country_ie) अणु
		/* Send cmd to FW to enable 11D function */
		state_11d = ENABLE_11D;
		अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
				     HostCmd_ACT_GEN_SET, DOT11D_I,
				     &state_11d, true)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "11D: failed to enable 11D\n");
		पूर्ण
	पूर्ण
पूर्ण

/* This function parses BSS related parameters from काष्ठाure
 * and prepares TLVs. These TLVs are appended to command buffer.
*/
अटल पूर्णांक
mwअगरiex_uap_bss_param_prepare(u8 *tlv, व्योम *cmd_buf, u16 *param_size)
अणु
	काष्ठा host_cmd_tlv_dtim_period *dtim_period;
	काष्ठा host_cmd_tlv_beacon_period *beacon_period;
	काष्ठा host_cmd_tlv_ssid *ssid;
	काष्ठा host_cmd_tlv_bcast_ssid *bcast_ssid;
	काष्ठा host_cmd_tlv_channel_band *chan_band;
	काष्ठा host_cmd_tlv_frag_threshold *frag_threshold;
	काष्ठा host_cmd_tlv_rts_threshold *rts_threshold;
	काष्ठा host_cmd_tlv_retry_limit *retry_limit;
	काष्ठा host_cmd_tlv_encrypt_protocol *encrypt_protocol;
	काष्ठा host_cmd_tlv_auth_type *auth_type;
	काष्ठा host_cmd_tlv_rates *tlv_rates;
	काष्ठा host_cmd_tlv_ageout_समयr *ao_समयr, *ps_ao_समयr;
	काष्ठा host_cmd_tlv_घातer_स्थिरraपूर्णांक *pwr_ct;
	काष्ठा mwअगरiex_ie_types_htcap *htcap;
	काष्ठा mwअगरiex_ie_types_wmmcap *wmm_cap;
	काष्ठा mwअगरiex_uap_bss_param *bss_cfg = cmd_buf;
	पूर्णांक i;
	u16 cmd_size = *param_size;

	अगर (bss_cfg->ssid.ssid_len) अणु
		ssid = (काष्ठा host_cmd_tlv_ssid *)tlv;
		ssid->header.type = cpu_to_le16(TLV_TYPE_UAP_SSID);
		ssid->header.len = cpu_to_le16((u16)bss_cfg->ssid.ssid_len);
		स_नकल(ssid->ssid, bss_cfg->ssid.ssid, bss_cfg->ssid.ssid_len);
		cmd_size += माप(काष्ठा mwअगरiex_ie_types_header) +
			    bss_cfg->ssid.ssid_len;
		tlv += माप(काष्ठा mwअगरiex_ie_types_header) +
				bss_cfg->ssid.ssid_len;

		bcast_ssid = (काष्ठा host_cmd_tlv_bcast_ssid *)tlv;
		bcast_ssid->header.type = cpu_to_le16(TLV_TYPE_UAP_BCAST_SSID);
		bcast_ssid->header.len =
				cpu_to_le16(माप(bcast_ssid->bcast_ctl));
		bcast_ssid->bcast_ctl = bss_cfg->bcast_ssid_ctl;
		cmd_size += माप(काष्ठा host_cmd_tlv_bcast_ssid);
		tlv += माप(काष्ठा host_cmd_tlv_bcast_ssid);
	पूर्ण
	अगर (bss_cfg->rates[0]) अणु
		tlv_rates = (काष्ठा host_cmd_tlv_rates *)tlv;
		tlv_rates->header.type = cpu_to_le16(TLV_TYPE_UAP_RATES);

		क्रम (i = 0; i < MWIFIEX_SUPPORTED_RATES && bss_cfg->rates[i];
		     i++)
			tlv_rates->rates[i] = bss_cfg->rates[i];

		tlv_rates->header.len = cpu_to_le16(i);
		cmd_size += माप(काष्ठा host_cmd_tlv_rates) + i;
		tlv += माप(काष्ठा host_cmd_tlv_rates) + i;
	पूर्ण
	अगर (bss_cfg->channel &&
	    (((bss_cfg->band_cfg & BIT(0)) == BAND_CONFIG_BG &&
	      bss_cfg->channel <= MAX_CHANNEL_BAND_BG) ||
	    ((bss_cfg->band_cfg & BIT(0)) == BAND_CONFIG_A &&
	     bss_cfg->channel <= MAX_CHANNEL_BAND_A))) अणु
		chan_band = (काष्ठा host_cmd_tlv_channel_band *)tlv;
		chan_band->header.type = cpu_to_le16(TLV_TYPE_CHANNELBANDLIST);
		chan_band->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_channel_band) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		chan_band->band_config = bss_cfg->band_cfg;
		chan_band->channel = bss_cfg->channel;
		cmd_size += माप(काष्ठा host_cmd_tlv_channel_band);
		tlv += माप(काष्ठा host_cmd_tlv_channel_band);
	पूर्ण
	अगर (bss_cfg->beacon_period >= MIN_BEACON_PERIOD &&
	    bss_cfg->beacon_period <= MAX_BEACON_PERIOD) अणु
		beacon_period = (काष्ठा host_cmd_tlv_beacon_period *)tlv;
		beacon_period->header.type =
					cpu_to_le16(TLV_TYPE_UAP_BEACON_PERIOD);
		beacon_period->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_beacon_period) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		beacon_period->period = cpu_to_le16(bss_cfg->beacon_period);
		cmd_size += माप(काष्ठा host_cmd_tlv_beacon_period);
		tlv += माप(काष्ठा host_cmd_tlv_beacon_period);
	पूर्ण
	अगर (bss_cfg->dtim_period >= MIN_DTIM_PERIOD &&
	    bss_cfg->dtim_period <= MAX_DTIM_PERIOD) अणु
		dtim_period = (काष्ठा host_cmd_tlv_dtim_period *)tlv;
		dtim_period->header.type =
			cpu_to_le16(TLV_TYPE_UAP_DTIM_PERIOD);
		dtim_period->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_dtim_period) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		dtim_period->period = bss_cfg->dtim_period;
		cmd_size += माप(काष्ठा host_cmd_tlv_dtim_period);
		tlv += माप(काष्ठा host_cmd_tlv_dtim_period);
	पूर्ण
	अगर (bss_cfg->rts_threshold <= MWIFIEX_RTS_MAX_VALUE) अणु
		rts_threshold = (काष्ठा host_cmd_tlv_rts_threshold *)tlv;
		rts_threshold->header.type =
					cpu_to_le16(TLV_TYPE_UAP_RTS_THRESHOLD);
		rts_threshold->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_rts_threshold) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		rts_threshold->rts_thr = cpu_to_le16(bss_cfg->rts_threshold);
		cmd_size += माप(काष्ठा host_cmd_tlv_frag_threshold);
		tlv += माप(काष्ठा host_cmd_tlv_frag_threshold);
	पूर्ण
	अगर ((bss_cfg->frag_threshold >= MWIFIEX_FRAG_MIN_VALUE) &&
	    (bss_cfg->frag_threshold <= MWIFIEX_FRAG_MAX_VALUE)) अणु
		frag_threshold = (काष्ठा host_cmd_tlv_frag_threshold *)tlv;
		frag_threshold->header.type =
				cpu_to_le16(TLV_TYPE_UAP_FRAG_THRESHOLD);
		frag_threshold->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_frag_threshold) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		frag_threshold->frag_thr = cpu_to_le16(bss_cfg->frag_threshold);
		cmd_size += माप(काष्ठा host_cmd_tlv_frag_threshold);
		tlv += माप(काष्ठा host_cmd_tlv_frag_threshold);
	पूर्ण
	अगर (bss_cfg->retry_limit <= MWIFIEX_RETRY_LIMIT) अणु
		retry_limit = (काष्ठा host_cmd_tlv_retry_limit *)tlv;
		retry_limit->header.type =
			cpu_to_le16(TLV_TYPE_UAP_RETRY_LIMIT);
		retry_limit->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_retry_limit) -
				    माप(काष्ठा mwअगरiex_ie_types_header));
		retry_limit->limit = (u8)bss_cfg->retry_limit;
		cmd_size += माप(काष्ठा host_cmd_tlv_retry_limit);
		tlv += माप(काष्ठा host_cmd_tlv_retry_limit);
	पूर्ण
	अगर ((bss_cfg->protocol & PROTOCOL_WPA) ||
	    (bss_cfg->protocol & PROTOCOL_WPA2) ||
	    (bss_cfg->protocol & PROTOCOL_EAP))
		mwअगरiex_uap_bss_wpa(&tlv, cmd_buf, &cmd_size);
	अन्यथा
		mwअगरiex_uap_bss_wep(&tlv, cmd_buf, &cmd_size);

	अगर ((bss_cfg->auth_mode <= WLAN_AUTH_SHARED_KEY) ||
	    (bss_cfg->auth_mode == MWIFIEX_AUTH_MODE_AUTO)) अणु
		auth_type = (काष्ठा host_cmd_tlv_auth_type *)tlv;
		auth_type->header.type = cpu_to_le16(TLV_TYPE_AUTH_TYPE);
		auth_type->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_auth_type) -
			माप(काष्ठा mwअगरiex_ie_types_header));
		auth_type->auth_type = (u8)bss_cfg->auth_mode;
		cmd_size += माप(काष्ठा host_cmd_tlv_auth_type);
		tlv += माप(काष्ठा host_cmd_tlv_auth_type);
	पूर्ण
	अगर (bss_cfg->protocol) अणु
		encrypt_protocol = (काष्ठा host_cmd_tlv_encrypt_protocol *)tlv;
		encrypt_protocol->header.type =
			cpu_to_le16(TLV_TYPE_UAP_ENCRY_PROTOCOL);
		encrypt_protocol->header.len =
			cpu_to_le16(माप(काष्ठा host_cmd_tlv_encrypt_protocol)
			- माप(काष्ठा mwअगरiex_ie_types_header));
		encrypt_protocol->proto = cpu_to_le16(bss_cfg->protocol);
		cmd_size += माप(काष्ठा host_cmd_tlv_encrypt_protocol);
		tlv += माप(काष्ठा host_cmd_tlv_encrypt_protocol);
	पूर्ण

	अगर (bss_cfg->ht_cap.cap_info) अणु
		htcap = (काष्ठा mwअगरiex_ie_types_htcap *)tlv;
		htcap->header.type = cpu_to_le16(WLAN_EID_HT_CAPABILITY);
		htcap->header.len =
				cpu_to_le16(माप(काष्ठा ieee80211_ht_cap));
		htcap->ht_cap.cap_info = bss_cfg->ht_cap.cap_info;
		htcap->ht_cap.ampdu_params_info =
					     bss_cfg->ht_cap.ampdu_params_info;
		स_नकल(&htcap->ht_cap.mcs, &bss_cfg->ht_cap.mcs,
		       माप(काष्ठा ieee80211_mcs_info));
		htcap->ht_cap.extended_ht_cap_info =
					bss_cfg->ht_cap.extended_ht_cap_info;
		htcap->ht_cap.tx_BF_cap_info = bss_cfg->ht_cap.tx_BF_cap_info;
		htcap->ht_cap.antenna_selection_info =
					bss_cfg->ht_cap.antenna_selection_info;
		cmd_size += माप(काष्ठा mwअगरiex_ie_types_htcap);
		tlv += माप(काष्ठा mwअगरiex_ie_types_htcap);
	पूर्ण

	अगर (bss_cfg->wmm_info.qos_info != 0xFF) अणु
		wmm_cap = (काष्ठा mwअगरiex_ie_types_wmmcap *)tlv;
		wmm_cap->header.type = cpu_to_le16(WLAN_EID_VENDOR_SPECIFIC);
		wmm_cap->header.len = cpu_to_le16(माप(wmm_cap->wmm_info));
		स_नकल(&wmm_cap->wmm_info, &bss_cfg->wmm_info,
		       माप(wmm_cap->wmm_info));
		cmd_size += माप(काष्ठा mwअगरiex_ie_types_wmmcap);
		tlv += माप(काष्ठा mwअगरiex_ie_types_wmmcap);
	पूर्ण

	अगर (bss_cfg->sta_ao_समयr) अणु
		ao_समयr = (काष्ठा host_cmd_tlv_ageout_समयr *)tlv;
		ao_समयr->header.type = cpu_to_le16(TLV_TYPE_UAP_AO_TIMER);
		ao_समयr->header.len = cpu_to_le16(माप(*ao_समयr) -
					माप(काष्ठा mwअगरiex_ie_types_header));
		ao_समयr->sta_ao_समयr = cpu_to_le32(bss_cfg->sta_ao_समयr);
		cmd_size += माप(*ao_समयr);
		tlv += माप(*ao_समयr);
	पूर्ण

	अगर (bss_cfg->घातer_स्थिरraपूर्णांक) अणु
		pwr_ct = (व्योम *)tlv;
		pwr_ct->header.type = cpu_to_le16(TLV_TYPE_PWR_CONSTRAINT);
		pwr_ct->header.len = cpu_to_le16(माप(u8));
		pwr_ct->स्थिरraपूर्णांक = bss_cfg->घातer_स्थिरraपूर्णांक;
		cmd_size += माप(*pwr_ct);
		tlv += माप(*pwr_ct);
	पूर्ण

	अगर (bss_cfg->ps_sta_ao_समयr) अणु
		ps_ao_समयr = (काष्ठा host_cmd_tlv_ageout_समयr *)tlv;
		ps_ao_समयr->header.type =
				cpu_to_le16(TLV_TYPE_UAP_PS_AO_TIMER);
		ps_ao_समयr->header.len = cpu_to_le16(माप(*ps_ao_समयr) -
				माप(काष्ठा mwअगरiex_ie_types_header));
		ps_ao_समयr->sta_ao_समयr =
					cpu_to_le32(bss_cfg->ps_sta_ao_समयr);
		cmd_size += माप(*ps_ao_समयr);
		tlv += माप(*ps_ao_समयr);
	पूर्ण

	*param_size = cmd_size;

	वापस 0;
पूर्ण

/* This function parses custom IEs from IE list and prepares command buffer */
अटल पूर्णांक mwअगरiex_uap_custom_ie_prepare(u8 *tlv, व्योम *cmd_buf, u16 *ie_size)
अणु
	काष्ठा mwअगरiex_ie_list *ap_ie = cmd_buf;
	काष्ठा mwअगरiex_ie_types_header *tlv_ie = (व्योम *)tlv;

	अगर (!ap_ie || !ap_ie->len)
		वापस -1;

	*ie_size += le16_to_cpu(ap_ie->len) +
			माप(काष्ठा mwअगरiex_ie_types_header);

	tlv_ie->type = cpu_to_le16(TLV_TYPE_MGMT_IE);
	tlv_ie->len = ap_ie->len;
	tlv += माप(काष्ठा mwअगरiex_ie_types_header);

	स_नकल(tlv, ap_ie->ie_list, le16_to_cpu(ap_ie->len));

	वापस 0;
पूर्ण

/* Parse AP config काष्ठाure and prepare TLV based command काष्ठाure
 * to be sent to FW क्रम uAP configuration
 */
अटल पूर्णांक
mwअगरiex_cmd_uap_sys_config(काष्ठा host_cmd_ds_command *cmd, u16 cmd_action,
			   u32 type, व्योम *cmd_buf)
अणु
	u8 *tlv;
	u16 cmd_size, param_size, ie_size;
	काष्ठा host_cmd_ds_sys_config *sys_cfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_UAP_SYS_CONFIG);
	cmd_size = (u16)(माप(काष्ठा host_cmd_ds_sys_config) + S_DS_GEN);
	sys_cfg = (काष्ठा host_cmd_ds_sys_config *)&cmd->params.uap_sys_config;
	sys_cfg->action = cpu_to_le16(cmd_action);
	tlv = sys_cfg->tlv;

	चयन (type) अणु
	हाल UAP_BSS_PARAMS_I:
		param_size = cmd_size;
		अगर (mwअगरiex_uap_bss_param_prepare(tlv, cmd_buf, &param_size))
			वापस -1;
		cmd->size = cpu_to_le16(param_size);
		अवरोध;
	हाल UAP_CUSTOM_IE_I:
		ie_size = cmd_size;
		अगर (mwअगरiex_uap_custom_ie_prepare(tlv, cmd_buf, &ie_size))
			वापस -1;
		cmd->size = cpu_to_le16(ie_size);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* This function prepares AP specअगरic deauth command with mac supplied in
 * function parameter.
 */
अटल पूर्णांक mwअगरiex_cmd_uap_sta_deauth(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा host_cmd_ds_command *cmd, u8 *mac)
अणु
	काष्ठा host_cmd_ds_sta_deauth *sta_deauth = &cmd->params.sta_deauth;

	cmd->command = cpu_to_le16(HostCmd_CMD_UAP_STA_DEAUTH);
	स_नकल(sta_deauth->mac, mac, ETH_ALEN);
	sta_deauth->reason = cpu_to_le16(WLAN_REASON_DEAUTH_LEAVING);

	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_sta_deauth) +
				S_DS_GEN);
	वापस 0;
पूर्ण

/* This function prepares the AP specअगरic commands beक्रमe sending them
 * to the firmware.
 * This is a generic function which calls specअगरic command preparation
 * routines based upon the command number.
 */
पूर्णांक mwअगरiex_uap_prepare_cmd(काष्ठा mwअगरiex_निजी *priv, u16 cmd_no,
			    u16 cmd_action, u32 type,
			    व्योम *data_buf, व्योम *cmd_buf)
अणु
	काष्ठा host_cmd_ds_command *cmd = cmd_buf;

	चयन (cmd_no) अणु
	हाल HostCmd_CMD_UAP_SYS_CONFIG:
		अगर (mwअगरiex_cmd_uap_sys_config(cmd, cmd_action, type, data_buf))
			वापस -1;
		अवरोध;
	हाल HostCmd_CMD_UAP_BSS_START:
	हाल HostCmd_CMD_UAP_BSS_STOP:
	हाल HOST_CMD_APCMD_SYS_RESET:
	हाल HOST_CMD_APCMD_STA_LIST:
		cmd->command = cpu_to_le16(cmd_no);
		cmd->size = cpu_to_le16(S_DS_GEN);
		अवरोध;
	हाल HostCmd_CMD_UAP_STA_DEAUTH:
		अगर (mwअगरiex_cmd_uap_sta_deauth(priv, cmd, data_buf))
			वापस -1;
		अवरोध;
	हाल HostCmd_CMD_CHAN_REPORT_REQUEST:
		अगर (mwअगरiex_cmd_issue_chan_report_request(priv, cmd_buf,
							  data_buf))
			वापस -1;
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "PREP_CMD: unknown cmd %#x\n", cmd_no);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mwअगरiex_uap_set_channel(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा mwअगरiex_uap_bss_param *bss_cfg,
			     काष्ठा cfg80211_chan_def chandef)
अणु
	u8 config_bands = 0, old_bands = priv->adapter->config_bands;

	priv->bss_chandef = chandef;

	bss_cfg->channel = ieee80211_frequency_to_channel(
						     chandef.chan->center_freq);

	/* Set appropriate bands */
	अगर (chandef.chan->band == NL80211_BAND_2GHZ) अणु
		bss_cfg->band_cfg = BAND_CONFIG_BG;
		config_bands = BAND_B | BAND_G;

		अगर (chandef.width > NL80211_CHAN_WIDTH_20_NOHT)
			config_bands |= BAND_GN;
	पूर्ण अन्यथा अणु
		bss_cfg->band_cfg = BAND_CONFIG_A;
		config_bands = BAND_A;

		अगर (chandef.width > NL80211_CHAN_WIDTH_20_NOHT)
			config_bands |= BAND_AN;

		अगर (chandef.width > NL80211_CHAN_WIDTH_40)
			config_bands |= BAND_AAC;
	पूर्ण

	चयन (chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		अगर (chandef.center_freq1 < chandef.chan->center_freq)
			bss_cfg->band_cfg |= MWIFIEX_SEC_CHAN_BELOW;
		अन्यथा
			bss_cfg->band_cfg |= MWIFIEX_SEC_CHAN_ABOVE;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
		bss_cfg->band_cfg |=
		    mwअगरiex_get_sec_chan_offset(bss_cfg->channel) << 4;
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter,
			    WARN, "Unknown channel width: %d\n",
			    chandef.width);
		अवरोध;
	पूर्ण

	priv->adapter->config_bands = config_bands;

	अगर (old_bands != config_bands) अणु
		mwअगरiex_send_करोमुख्य_info_cmd_fw(priv->adapter->wiphy);
		mwअगरiex_dnld_txpwr_table(priv);
	पूर्ण
पूर्ण

पूर्णांक mwअगरiex_config_start_uap(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा mwअगरiex_uap_bss_param *bss_cfg)
अणु
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_UAP_SYS_CONFIG,
			     HostCmd_ACT_GEN_SET,
			     UAP_BSS_PARAMS_I, bss_cfg, true)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to set AP configuration\n");
		वापस -1;
	पूर्ण

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_UAP_BSS_START,
			     HostCmd_ACT_GEN_SET, 0, शून्य, true)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Failed to start the BSS\n");
		वापस -1;
	पूर्ण

	अगर (priv->sec_info.wep_enabled)
		priv->curr_pkt_filter |= HostCmd_ACT_MAC_WEP_ENABLE;
	अन्यथा
		priv->curr_pkt_filter &= ~HostCmd_ACT_MAC_WEP_ENABLE;

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_MAC_CONTROL,
			     HostCmd_ACT_GEN_SET, 0,
			     &priv->curr_pkt_filter, true))
		वापस -1;

	वापस 0;
पूर्ण
