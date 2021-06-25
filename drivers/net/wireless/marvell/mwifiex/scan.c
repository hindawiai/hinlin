<शैली गुरु>
/*
 * NXP Wireless LAN device driver: scan ioctl and command handling
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
#समावेश "11n.h"
#समावेश "cfg80211.h"

/* The maximum number of channels the firmware can scan per command */
#घोषणा MWIFIEX_MAX_CHANNELS_PER_SPECIFIC_SCAN   14

#घोषणा MWIFIEX_DEF_CHANNELS_PER_SCAN_CMD	4

/* Memory needed to store a max sized Channel List TLV क्रम a firmware scan */
#घोषणा CHAN_TLV_MAX_SIZE  (माप(काष्ठा mwअगरiex_ie_types_header)         \
				+ (MWIFIEX_MAX_CHANNELS_PER_SPECIFIC_SCAN     \
				*माप(काष्ठा mwअगरiex_chan_scan_param_set)))

/* Memory needed to store supported rate */
#घोषणा RATE_TLV_MAX_SIZE   (माप(काष्ठा mwअगरiex_ie_types_rates_param_set) \
				+ HOSTCMD_SUPPORTED_RATES)

/* Memory needed to store a max number/size WildCard SSID TLV क्रम a firmware
	scan */
#घोषणा WILDCARD_SSID_TLV_MAX_SIZE  \
	(MWIFIEX_MAX_SSID_LIST_LENGTH *					\
		(माप(काष्ठा mwअगरiex_ie_types_wildcard_ssid_params)	\
			+ IEEE80211_MAX_SSID_LEN))

/* Maximum memory needed क्रम a mwअगरiex_scan_cmd_config with all TLVs at max */
#घोषणा MAX_SCAN_CFG_ALLOC (माप(काष्ठा mwअगरiex_scan_cmd_config)        \
				+ माप(काष्ठा mwअगरiex_ie_types_num_probes)   \
				+ माप(काष्ठा mwअगरiex_ie_types_htcap)       \
				+ CHAN_TLV_MAX_SIZE                 \
				+ RATE_TLV_MAX_SIZE                 \
				+ WILDCARD_SSID_TLV_MAX_SIZE)


जोड़ mwअगरiex_scan_cmd_config_tlv अणु
	/* Scan configuration (variable length) */
	काष्ठा mwअगरiex_scan_cmd_config config;
	/* Max allocated block */
	u8 config_alloc_buf[MAX_SCAN_CFG_ALLOC];
पूर्ण;

क्रमागत cipher_suite अणु
	CIPHER_SUITE_TKIP,
	CIPHER_SUITE_CCMP,
	CIPHER_SUITE_MAX
पूर्ण;
अटल u8 mwअगरiex_wpa_oui[CIPHER_SUITE_MAX][4] = अणु
	अणु 0x00, 0x50, 0xf2, 0x02 पूर्ण,	/* TKIP */
	अणु 0x00, 0x50, 0xf2, 0x04 पूर्ण,	/* AES  */
पूर्ण;
अटल u8 mwअगरiex_rsn_oui[CIPHER_SUITE_MAX][4] = अणु
	अणु 0x00, 0x0f, 0xac, 0x02 पूर्ण,	/* TKIP */
	अणु 0x00, 0x0f, 0xac, 0x04 पूर्ण,	/* AES  */
पूर्ण;

अटल व्योम
_dbg_security_flags(पूर्णांक log_level, स्थिर अक्षर *func, स्थिर अक्षर *desc,
		    काष्ठा mwअगरiex_निजी *priv,
		    काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	_mwअगरiex_dbg(priv->adapter, log_level,
		     "info: %s: %s:\twpa_ie=%#x wpa2_ie=%#x WEP=%s WPA=%s WPA2=%s\tEncMode=%#x privacy=%#x\n",
		     func, desc,
		     bss_desc->bcn_wpa_ie ?
		     bss_desc->bcn_wpa_ie->vend_hdr.element_id : 0,
		     bss_desc->bcn_rsn_ie ?
		     bss_desc->bcn_rsn_ie->ieee_hdr.element_id : 0,
		     priv->sec_info.wep_enabled ? "e" : "d",
		     priv->sec_info.wpa_enabled ? "e" : "d",
		     priv->sec_info.wpa2_enabled ? "e" : "d",
		     priv->sec_info.encryption_mode,
		     bss_desc->privacy);
पूर्ण
#घोषणा dbg_security_flags(mask, desc, priv, bss_desc) \
	_dbg_security_flags(MWIFIEX_DBG_##mask, desc, __func__, priv, bss_desc)

अटल bool
has_ieee_hdr(काष्ठा ieee_types_generic *ie, u8 key)
अणु
	वापस (ie && ie->ieee_hdr.element_id == key);
पूर्ण

अटल bool
has_venकरोr_hdr(काष्ठा ieee_types_venकरोr_specअगरic *ie, u8 key)
अणु
	वापस (ie && ie->vend_hdr.element_id == key);
पूर्ण

/*
 * This function parses a given IE क्रम a given OUI.
 *
 * This is used to parse a WPA/RSN IE to find अगर it has
 * a given oui in PTK.
 */
अटल u8
mwअगरiex_search_oui_in_ie(काष्ठा ie_body *iebody, u8 *oui)
अणु
	u8 count;

	count = iebody->ptk_cnt[0];

	/* There could be multiple OUIs क्रम PTK hence
	   1) Take the length.
	   2) Check all the OUIs क्रम AES.
	   3) If one of them is AES then pass success. */
	जबतक (count) अणु
		अगर (!स_भेद(iebody->ptk_body, oui, माप(iebody->ptk_body)))
			वापस MWIFIEX_OUI_PRESENT;

		--count;
		अगर (count)
			iebody = (काष्ठा ie_body *) ((u8 *) iebody +
						माप(iebody->ptk_body));
	पूर्ण

	pr_debug("info: %s: OUI is not found in PTK\n", __func__);
	वापस MWIFIEX_OUI_NOT_PRESENT;
पूर्ण

/*
 * This function checks अगर a given OUI is present in a RSN IE.
 *
 * The function first checks अगर a RSN IE is present or not in the
 * BSS descriptor. It tries to locate the OUI only अगर such an IE is
 * present.
 */
अटल u8
mwअगरiex_is_rsn_oui_present(काष्ठा mwअगरiex_bssdescriptor *bss_desc, u32 cipher)
अणु
	u8 *oui;
	काष्ठा ie_body *iebody;
	u8 ret = MWIFIEX_OUI_NOT_PRESENT;

	अगर (has_ieee_hdr(bss_desc->bcn_rsn_ie, WLAN_EID_RSN)) अणु
		iebody = (काष्ठा ie_body *)
			 (((u8 *) bss_desc->bcn_rsn_ie->data) +
			  RSN_GTK_OUI_OFFSET);
		oui = &mwअगरiex_rsn_oui[cipher][0];
		ret = mwअगरiex_search_oui_in_ie(iebody, oui);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This function checks अगर a given OUI is present in a WPA IE.
 *
 * The function first checks अगर a WPA IE is present or not in the
 * BSS descriptor. It tries to locate the OUI only अगर such an IE is
 * present.
 */
अटल u8
mwअगरiex_is_wpa_oui_present(काष्ठा mwअगरiex_bssdescriptor *bss_desc, u32 cipher)
अणु
	u8 *oui;
	काष्ठा ie_body *iebody;
	u8 ret = MWIFIEX_OUI_NOT_PRESENT;

	अगर (has_venकरोr_hdr(bss_desc->bcn_wpa_ie, WLAN_EID_VENDOR_SPECIFIC)) अणु
		iebody = (काष्ठा ie_body *)((u8 *)bss_desc->bcn_wpa_ie->data +
					    WPA_GTK_OUI_OFFSET);
		oui = &mwअगरiex_wpa_oui[cipher][0];
		ret = mwअगरiex_search_oui_in_ie(iebody, oui);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This function compares two SSIDs and checks अगर they match.
 */
s32
mwअगरiex_ssid_cmp(काष्ठा cfg80211_ssid *ssid1, काष्ठा cfg80211_ssid *ssid2)
अणु
	अगर (!ssid1 || !ssid2 || (ssid1->ssid_len != ssid2->ssid_len))
		वापस -1;
	वापस स_भेद(ssid1->ssid, ssid2->ssid, ssid1->ssid_len);
पूर्ण

/*
 * This function checks अगर wapi is enabled in driver and scanned network is
 * compatible with it.
 */
अटल bool
mwअगरiex_is_bss_wapi(काष्ठा mwअगरiex_निजी *priv,
		    काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	अगर (priv->sec_info.wapi_enabled &&
	    has_ieee_hdr(bss_desc->bcn_wapi_ie, WLAN_EID_BSS_AC_ACCESS_DELAY))
		वापस true;
	वापस false;
पूर्ण

/*
 * This function checks अगर driver is configured with no security mode and
 * scanned network is compatible with it.
 */
अटल bool
mwअगरiex_is_bss_no_sec(काष्ठा mwअगरiex_निजी *priv,
		      काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	अगर (!priv->sec_info.wep_enabled && !priv->sec_info.wpa_enabled &&
	    !priv->sec_info.wpa2_enabled &&
	    !has_venकरोr_hdr(bss_desc->bcn_wpa_ie, WLAN_EID_VENDOR_SPECIFIC) &&
	    !has_ieee_hdr(bss_desc->bcn_rsn_ie, WLAN_EID_RSN) &&
	    !priv->sec_info.encryption_mode && !bss_desc->privacy) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * This function checks अगर अटल WEP is enabled in driver and scanned network
 * is compatible with it.
 */
अटल bool
mwअगरiex_is_bss_अटल_wep(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	अगर (priv->sec_info.wep_enabled && !priv->sec_info.wpa_enabled &&
	    !priv->sec_info.wpa2_enabled && bss_desc->privacy) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * This function checks अगर wpa is enabled in driver and scanned network is
 * compatible with it.
 */
अटल bool
mwअगरiex_is_bss_wpa(काष्ठा mwअगरiex_निजी *priv,
		   काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	अगर (!priv->sec_info.wep_enabled && priv->sec_info.wpa_enabled &&
	    !priv->sec_info.wpa2_enabled &&
	    has_venकरोr_hdr(bss_desc->bcn_wpa_ie, WLAN_EID_VENDOR_SPECIFIC)
	   /*
	    * Privacy bit may NOT be set in some APs like
	    * LinkSys WRT54G && bss_desc->privacy
	    */
	 ) अणु
		dbg_security_flags(INFO, "WPA", priv, bss_desc);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * This function checks अगर wpa2 is enabled in driver and scanned network is
 * compatible with it.
 */
अटल bool
mwअगरiex_is_bss_wpa2(काष्ठा mwअगरiex_निजी *priv,
		    काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	अगर (!priv->sec_info.wep_enabled && !priv->sec_info.wpa_enabled &&
	    priv->sec_info.wpa2_enabled &&
	    has_ieee_hdr(bss_desc->bcn_rsn_ie, WLAN_EID_RSN)) अणु
		/*
		 * Privacy bit may NOT be set in some APs like
		 * LinkSys WRT54G && bss_desc->privacy
		 */
		dbg_security_flags(INFO, "WAP2", priv, bss_desc);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * This function checks अगर adhoc AES is enabled in driver and scanned network is
 * compatible with it.
 */
अटल bool
mwअगरiex_is_bss_adhoc_aes(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	अगर (!priv->sec_info.wep_enabled && !priv->sec_info.wpa_enabled &&
	    !priv->sec_info.wpa2_enabled &&
	    !has_venकरोr_hdr(bss_desc->bcn_wpa_ie, WLAN_EID_VENDOR_SPECIFIC) &&
	    !has_ieee_hdr(bss_desc->bcn_rsn_ie, WLAN_EID_RSN) &&
	    !priv->sec_info.encryption_mode && bss_desc->privacy) अणु
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * This function checks अगर dynamic WEP is enabled in driver and scanned network
 * is compatible with it.
 */
अटल bool
mwअगरiex_is_bss_dynamic_wep(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	अगर (!priv->sec_info.wep_enabled && !priv->sec_info.wpa_enabled &&
	    !priv->sec_info.wpa2_enabled &&
	    !has_venकरोr_hdr(bss_desc->bcn_wpa_ie, WLAN_EID_VENDOR_SPECIFIC) &&
	    !has_ieee_hdr(bss_desc->bcn_rsn_ie, WLAN_EID_RSN) &&
	    priv->sec_info.encryption_mode && bss_desc->privacy) अणु
		dbg_security_flags(INFO, "dynamic", priv, bss_desc);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * This function checks अगर a scanned network is compatible with the driver
 * settings.
 *
 *   WEP     WPA    WPA2   ad-hoc encrypt                  Network
 * enabled enabled enabled  AES    mode   Privacy WPA WPA2 Compatible
 *    0       0       0      0     NONE      0     0   0   yes No security
 *    0       1       0      0      x        1x    1   x   yes WPA (disable
 *                                                         HT अगर no AES)
 *    0       0       1      0      x        1x    x   1   yes WPA2 (disable
 *                                                         HT अगर no AES)
 *    0       0       0      1     NONE      1     0   0   yes Ad-hoc AES
 *    1       0       0      0     NONE      1     0   0   yes Static WEP
 *                                                         (disable HT)
 *    0       0       0      0    !=NONE     1     0   0   yes Dynamic WEP
 *
 * Compatibility is not matched जबतक roaming, except क्रम mode.
 */
अटल s32
mwअगरiex_is_network_compatible(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_bssdescriptor *bss_desc, u32 mode)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	bss_desc->disable_11n = false;

	/* Don't check क्रम compatibility अगर roaming */
	अगर (priv->media_connected &&
	    (priv->bss_mode == NL80211_IFTYPE_STATION) &&
	    (bss_desc->bss_mode == NL80211_IFTYPE_STATION))
		वापस 0;

	अगर (priv->wps.session_enable) अणु
		mwअगरiex_dbg(adapter, IOCTL,
			    "info: return success directly in WPS period\n");
		वापस 0;
	पूर्ण

	अगर (bss_desc->chan_sw_ie_present) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "Don't connect to AP with WLAN_EID_CHANNEL_SWITCH\n");
		वापस -1;
	पूर्ण

	अगर (mwअगरiex_is_bss_wapi(priv, bss_desc)) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "info: return success for WAPI AP\n");
		वापस 0;
	पूर्ण

	अगर (bss_desc->bss_mode == mode) अणु
		अगर (mwअगरiex_is_bss_no_sec(priv, bss_desc)) अणु
			/* No security */
			वापस 0;
		पूर्ण अन्यथा अगर (mwअगरiex_is_bss_अटल_wep(priv, bss_desc)) अणु
			/* Static WEP enabled */
			mwअगरiex_dbg(adapter, INFO,
				    "info: Disable 11n in WEP mode.\n");
			bss_desc->disable_11n = true;
			वापस 0;
		पूर्ण अन्यथा अगर (mwअगरiex_is_bss_wpa(priv, bss_desc)) अणु
			/* WPA enabled */
			अगर (((priv->adapter->config_bands & BAND_GN ||
			      priv->adapter->config_bands & BAND_AN) &&
			     bss_desc->bcn_ht_cap) &&
			    !mwअगरiex_is_wpa_oui_present(bss_desc,
							 CIPHER_SUITE_CCMP)) अणु

				अगर (mwअगरiex_is_wpa_oui_present
						(bss_desc, CIPHER_SUITE_TKIP)) अणु
					mwअगरiex_dbg(adapter, INFO,
						    "info: Disable 11n if AES\t"
						    "is not supported by AP\n");
					bss_desc->disable_11n = true;
				पूर्ण अन्यथा अणु
					वापस -1;
				पूर्ण
			पूर्ण
			वापस 0;
		पूर्ण अन्यथा अगर (mwअगरiex_is_bss_wpa2(priv, bss_desc)) अणु
			/* WPA2 enabled */
			अगर (((priv->adapter->config_bands & BAND_GN ||
			      priv->adapter->config_bands & BAND_AN) &&
			     bss_desc->bcn_ht_cap) &&
			    !mwअगरiex_is_rsn_oui_present(bss_desc,
							CIPHER_SUITE_CCMP)) अणु

				अगर (mwअगरiex_is_rsn_oui_present
						(bss_desc, CIPHER_SUITE_TKIP)) अणु
					mwअगरiex_dbg(adapter, INFO,
						    "info: Disable 11n if AES\t"
						    "is not supported by AP\n");
					bss_desc->disable_11n = true;
				पूर्ण अन्यथा अणु
					वापस -1;
				पूर्ण
			पूर्ण
			वापस 0;
		पूर्ण अन्यथा अगर (mwअगरiex_is_bss_adhoc_aes(priv, bss_desc)) अणु
			/* Ad-hoc AES enabled */
			वापस 0;
		पूर्ण अन्यथा अगर (mwअगरiex_is_bss_dynamic_wep(priv, bss_desc)) अणु
			/* Dynamic WEP enabled */
			वापस 0;
		पूर्ण

		/* Security करोesn't match */
		dbg_security_flags(ERROR, "failed", priv, bss_desc);
		वापस -1;
	पूर्ण

	/* Mode करोesn't match */
	वापस -1;
पूर्ण

/*
 * This function creates a channel list क्रम the driver to scan, based
 * on region/band inक्रमmation.
 *
 * This routine is used क्रम any scan that is not provided with a
 * specअगरic channel list to scan.
 */
अटल पूर्णांक
mwअगरiex_scan_create_channel_list(काष्ठा mwअगरiex_निजी *priv,
				 स्थिर काष्ठा mwअगरiex_user_scan_cfg
							*user_scan_in,
				 काष्ठा mwअगरiex_chan_scan_param_set
							*scan_chan_list,
				 u8 filtered_scan)
अणु
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक chan_idx = 0, i;

	क्रम (band = 0; (band < NUM_NL80211_BANDS) ; band++) अणु

		अगर (!priv->wdev.wiphy->bands[band])
			जारी;

		sband = priv->wdev.wiphy->bands[band];

		क्रम (i = 0; (i < sband->n_channels) ; i++) अणु
			ch = &sband->channels[i];
			अगर (ch->flags & IEEE80211_CHAN_DISABLED)
				जारी;
			scan_chan_list[chan_idx].radio_type = band;

			अगर (user_scan_in &&
			    user_scan_in->chan_list[0].scan_समय)
				scan_chan_list[chan_idx].max_scan_समय =
					cpu_to_le16((u16) user_scan_in->
					chan_list[0].scan_समय);
			अन्यथा अगर ((ch->flags & IEEE80211_CHAN_NO_IR) ||
				 (ch->flags & IEEE80211_CHAN_RADAR))
				scan_chan_list[chan_idx].max_scan_समय =
					cpu_to_le16(adapter->passive_scan_समय);
			अन्यथा
				scan_chan_list[chan_idx].max_scan_समय =
					cpu_to_le16(adapter->active_scan_समय);

			अगर (ch->flags & IEEE80211_CHAN_NO_IR)
				scan_chan_list[chan_idx].chan_scan_mode_biपंचांगap
					|= (MWIFIEX_PASSIVE_SCAN |
					    MWIFIEX_HIDDEN_SSID_REPORT);
			अन्यथा
				scan_chan_list[chan_idx].chan_scan_mode_biपंचांगap
					&= ~MWIFIEX_PASSIVE_SCAN;
			scan_chan_list[chan_idx].chan_number =
							(u32) ch->hw_value;

			scan_chan_list[chan_idx].chan_scan_mode_biपंचांगap
					|= MWIFIEX_DISABLE_CHAN_FILT;

			अगर (filtered_scan &&
			    !((ch->flags & IEEE80211_CHAN_NO_IR) ||
			      (ch->flags & IEEE80211_CHAN_RADAR)))
				scan_chan_list[chan_idx].max_scan_समय =
				cpu_to_le16(adapter->specअगरic_scan_समय);

			chan_idx++;
		पूर्ण

	पूर्ण
	वापस chan_idx;
पूर्ण

/* This function creates a channel list tlv क्रम bgscan config, based
 * on region/band inक्रमmation.
 */
अटल पूर्णांक
mwअगरiex_bgscan_create_channel_list(काष्ठा mwअगरiex_निजी *priv,
				   स्थिर काष्ठा mwअगरiex_bg_scan_cfg
						*bgscan_cfg_in,
				   काष्ठा mwअगरiex_chan_scan_param_set
						*scan_chan_list)
अणु
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक chan_idx = 0, i;

	क्रम (band = 0; (band < NUM_NL80211_BANDS); band++) अणु
		अगर (!priv->wdev.wiphy->bands[band])
			जारी;

		sband = priv->wdev.wiphy->bands[band];

		क्रम (i = 0; (i < sband->n_channels) ; i++) अणु
			ch = &sband->channels[i];
			अगर (ch->flags & IEEE80211_CHAN_DISABLED)
				जारी;
			scan_chan_list[chan_idx].radio_type = band;

			अगर (bgscan_cfg_in->chan_list[0].scan_समय)
				scan_chan_list[chan_idx].max_scan_समय =
					cpu_to_le16((u16)bgscan_cfg_in->
					chan_list[0].scan_समय);
			अन्यथा अगर (ch->flags & IEEE80211_CHAN_NO_IR)
				scan_chan_list[chan_idx].max_scan_समय =
					cpu_to_le16(adapter->passive_scan_समय);
			अन्यथा
				scan_chan_list[chan_idx].max_scan_समय =
					cpu_to_le16(adapter->
						    specअगरic_scan_समय);

			अगर (ch->flags & IEEE80211_CHAN_NO_IR)
				scan_chan_list[chan_idx].chan_scan_mode_biपंचांगap
					|= MWIFIEX_PASSIVE_SCAN;
			अन्यथा
				scan_chan_list[chan_idx].chan_scan_mode_biपंचांगap
					&= ~MWIFIEX_PASSIVE_SCAN;

			scan_chan_list[chan_idx].chan_number =
							(u32)ch->hw_value;
			chan_idx++;
		पूर्ण
	पूर्ण
	वापस chan_idx;
पूर्ण

/* This function appends rate TLV to scan config command. */
अटल पूर्णांक
mwअगरiex_append_rate_tlv(काष्ठा mwअगरiex_निजी *priv,
			काष्ठा mwअगरiex_scan_cmd_config *scan_cfg_out,
			u8 radio)
अणु
	काष्ठा mwअगरiex_ie_types_rates_param_set *rates_tlv;
	u8 rates[MWIFIEX_SUPPORTED_RATES], *tlv_pos;
	u32 rates_size;

	स_रखो(rates, 0, माप(rates));

	tlv_pos = (u8 *)scan_cfg_out->tlv_buf + scan_cfg_out->tlv_buf_len;

	अगर (priv->scan_request)
		rates_size = mwअगरiex_get_rates_from_cfg80211(priv, rates,
							     radio);
	अन्यथा
		rates_size = mwअगरiex_get_supported_rates(priv, rates);

	mwअगरiex_dbg(priv->adapter, CMD,
		    "info: SCAN_CMD: Rates size = %d\n",
		rates_size);
	rates_tlv = (काष्ठा mwअगरiex_ie_types_rates_param_set *)tlv_pos;
	rates_tlv->header.type = cpu_to_le16(WLAN_EID_SUPP_RATES);
	rates_tlv->header.len = cpu_to_le16((u16) rates_size);
	स_नकल(rates_tlv->rates, rates, rates_size);
	scan_cfg_out->tlv_buf_len += माप(rates_tlv->header) + rates_size;

	वापस rates_size;
पूर्ण

/*
 * This function स्थिरructs and sends multiple scan config commands to
 * the firmware.
 *
 * Previous routines in the code flow have created a scan command configuration
 * with any requested TLVs.  This function splits the channel TLV पूर्णांकo maximum
 * channels supported per scan lists and sends the portion of the channel TLV,
 * aदीर्घ with the other TLVs, to the firmware.
 */
अटल पूर्णांक
mwअगरiex_scan_channel_list(काष्ठा mwअगरiex_निजी *priv,
			  u32 max_chan_per_scan, u8 filtered_scan,
			  काष्ठा mwअगरiex_scan_cmd_config *scan_cfg_out,
			  काष्ठा mwअगरiex_ie_types_chan_list_param_set
			  *chan_tlv_out,
			  काष्ठा mwअगरiex_chan_scan_param_set *scan_chan_list)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret = 0;
	काष्ठा mwअगरiex_chan_scan_param_set *पंचांगp_chan_list;
	काष्ठा mwअगरiex_chan_scan_param_set *start_chan;
	u32 tlv_idx, rates_size, cmd_no;
	u32 total_scan_समय;
	u32 करोne_early;
	u8 radio_type;

	अगर (!scan_cfg_out || !chan_tlv_out || !scan_chan_list) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "info: Scan: Null detect: %p, %p, %p\n",
			    scan_cfg_out, chan_tlv_out, scan_chan_list);
		वापस -1;
	पूर्ण

	/* Check csa channel expiry beक्रमe preparing scan list */
	mwअगरiex_11h_get_csa_बंदd_channel(priv);

	chan_tlv_out->header.type = cpu_to_le16(TLV_TYPE_CHANLIST);

	/* Set the temp channel काष्ठा poपूर्णांकer to the start of the desired
	   list */
	पंचांगp_chan_list = scan_chan_list;

	/* Loop through the desired channel list, sending a new firmware scan
	   commands क्रम each max_chan_per_scan channels (or क्रम 1,6,11
	   inभागidually अगर configured accordingly) */
	जबतक (पंचांगp_chan_list->chan_number) अणु

		tlv_idx = 0;
		total_scan_समय = 0;
		radio_type = 0;
		chan_tlv_out->header.len = 0;
		start_chan = पंचांगp_chan_list;
		करोne_early = false;

		/*
		 * Conकाष्ठा the Channel TLV क्रम the scan command.  Continue to
		 * insert channel TLVs until:
		 *   - the tlv_idx hits the maximum configured per scan command
		 *   - the next channel to insert is 0 (end of desired channel
		 *     list)
		 *   - करोne_early is set (controlling inभागidual scanning of
		 *     1,6,11)
		 */
		जबतक (tlv_idx < max_chan_per_scan &&
		       पंचांगp_chan_list->chan_number && !करोne_early) अणु

			अगर (पंचांगp_chan_list->chan_number == priv->csa_chan) अणु
				पंचांगp_chan_list++;
				जारी;
			पूर्ण

			radio_type = पंचांगp_chan_list->radio_type;
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: Scan: Chan(%3d), Radio(%d),\t"
				    "Mode(%d, %d), Dur(%d)\n",
				    पंचांगp_chan_list->chan_number,
				    पंचांगp_chan_list->radio_type,
				    पंचांगp_chan_list->chan_scan_mode_biपंचांगap
				    & MWIFIEX_PASSIVE_SCAN,
				    (पंचांगp_chan_list->chan_scan_mode_biपंचांगap
				    & MWIFIEX_DISABLE_CHAN_FILT) >> 1,
				    le16_to_cpu(पंचांगp_chan_list->max_scan_समय));

			/* Copy the current channel TLV to the command being
			   prepared */
			स_नकल(chan_tlv_out->chan_scan_param + tlv_idx,
			       पंचांगp_chan_list,
			       माप(chan_tlv_out->chan_scan_param));

			/* Increment the TLV header length by the size
			   appended */
			le16_unaligned_add_cpu(&chan_tlv_out->header.len,
					       माप(
						chan_tlv_out->chan_scan_param));

			/*
			 * The tlv buffer length is set to the number of bytes
			 * of the between the channel tlv poपूर्णांकer and the start
			 * of the tlv buffer.  This compensates क्रम any TLVs
			 * that were appended beक्रमe the channel list.
			 */
			scan_cfg_out->tlv_buf_len = (u32) ((u8 *) chan_tlv_out -
							scan_cfg_out->tlv_buf);

			/* Add the size of the channel tlv header and the data
			   length */
			scan_cfg_out->tlv_buf_len +=
				(माप(chan_tlv_out->header)
				 + le16_to_cpu(chan_tlv_out->header.len));

			/* Increment the index to the channel tlv we are
			   स्थिरructing */
			tlv_idx++;

			/* Count the total scan समय per command */
			total_scan_समय +=
				le16_to_cpu(पंचांगp_chan_list->max_scan_समय);

			करोne_early = false;

			/* Stop the loop अगर the *current* channel is in the
			   1,6,11 set and we are not filtering on a BSSID
			   or SSID. */
			अगर (!filtered_scan &&
			    (पंचांगp_chan_list->chan_number == 1 ||
			     पंचांगp_chan_list->chan_number == 6 ||
			     पंचांगp_chan_list->chan_number == 11))
				करोne_early = true;

			/* Increment the पंचांगp poपूर्णांकer to the next channel to
			   be scanned */
			पंचांगp_chan_list++;

			/* Stop the loop अगर the *next* channel is in the 1,6,11
			   set.  This will cause it to be the only channel
			   scanned on the next पूर्णांकeration */
			अगर (!filtered_scan &&
			    (पंचांगp_chan_list->chan_number == 1 ||
			     पंचांगp_chan_list->chan_number == 6 ||
			     पंचांगp_chan_list->chan_number == 11))
				करोne_early = true;
		पूर्ण

		/* The total scan समय should be less than scan command समयout
		   value */
		अगर (total_scan_समय > MWIFIEX_MAX_TOTAL_SCAN_TIME) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "total scan time %dms\t"
				    "is over limit (%dms), scan skipped\n",
				    total_scan_समय,
				    MWIFIEX_MAX_TOTAL_SCAN_TIME);
			ret = -1;
			अवरोध;
		पूर्ण

		rates_size = mwअगरiex_append_rate_tlv(priv, scan_cfg_out,
						     radio_type);

		priv->adapter->scan_channels = start_chan;

		/* Send the scan command to the firmware with the specअगरied
		   cfg */
		अगर (priv->adapter->ext_scan)
			cmd_no = HostCmd_CMD_802_11_SCAN_EXT;
		अन्यथा
			cmd_no = HostCmd_CMD_802_11_SCAN;

		ret = mwअगरiex_send_cmd(priv, cmd_no, HostCmd_ACT_GEN_SET,
				       0, scan_cfg_out, false);

		/* rate IE is updated per scan command but same starting
		 * poपूर्णांकer is used each समय so that rate IE from earlier
		 * scan_cfg_out->buf is overwritten with new one.
		 */
		scan_cfg_out->tlv_buf_len -=
			    माप(काष्ठा mwअगरiex_ie_types_header) + rates_size;

		अगर (ret) अणु
			mwअगरiex_cancel_pending_scan_cmd(adapter);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * This function स्थिरructs a scan command configuration काष्ठाure to use
 * in scan commands.
 *
 * Application layer or other functions can invoke network scanning
 * with a scan configuration supplied in a user scan configuration काष्ठाure.
 * This काष्ठाure is used as the basis of one or many scan command configuration
 * commands that are sent to the command processing module and eventually to the
 * firmware.
 *
 * This function creates a scan command configuration काष्ठाure  based on the
 * following user supplied parameters (अगर present):
 *      - SSID filter
 *      - BSSID filter
 *      - Number of Probes to be sent
 *      - Channel list
 *
 * If the SSID or BSSID filter is not present, the filter is disabled/cleared.
 * If the number of probes is not set, adapter शेष setting is used.
 */
अटल व्योम
mwअगरiex_config_scan(काष्ठा mwअगरiex_निजी *priv,
		    स्थिर काष्ठा mwअगरiex_user_scan_cfg *user_scan_in,
		    काष्ठा mwअगरiex_scan_cmd_config *scan_cfg_out,
		    काष्ठा mwअगरiex_ie_types_chan_list_param_set **chan_list_out,
		    काष्ठा mwअगरiex_chan_scan_param_set *scan_chan_list,
		    u8 *max_chan_per_scan, u8 *filtered_scan,
		    u8 *scan_current_only)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_ie_types_num_probes *num_probes_tlv;
	काष्ठा mwअगरiex_ie_types_scan_chan_gap *chan_gap_tlv;
	काष्ठा mwअगरiex_ie_types_अक्रमom_mac *अक्रमom_mac_tlv;
	काष्ठा mwअगरiex_ie_types_wildcard_ssid_params *wildcard_ssid_tlv;
	काष्ठा mwअगरiex_ie_types_bssid_list *bssid_tlv;
	u8 *tlv_pos;
	u32 num_probes;
	u32 ssid_len;
	u32 chan_idx;
	u32 scan_type;
	u16 scan_dur;
	u8 channel;
	u8 radio_type;
	पूर्णांक i;
	u8 ssid_filter;
	काष्ठा mwअगरiex_ie_types_htcap *ht_cap;
	काष्ठा mwअगरiex_ie_types_bss_mode *bss_mode;
	स्थिर u8 zero_mac[6] = अणु0, 0, 0, 0, 0, 0पूर्ण;

	/* The tlv_buf_len is calculated क्रम each scan command.  The TLVs added
	   in this routine will be preserved since the routine that sends the
	   command will append channelTLVs at *chan_list_out.  The dअगरference
	   between the *chan_list_out and the tlv_buf start will be used to
	   calculate the size of anything we add in this routine. */
	scan_cfg_out->tlv_buf_len = 0;

	/* Running tlv poपूर्णांकer.  Asचिन्हित to chan_list_out at end of function
	   so later routines know where channels can be added to the command
	   buf */
	tlv_pos = scan_cfg_out->tlv_buf;

	/* Initialize the scan as un-filtered; the flag is later set to TRUE
	   below अगर a SSID or BSSID filter is sent in the command */
	*filtered_scan = false;

	/* Initialize the scan as not being only on the current channel.  If
	   the channel list is customized, only contains one channel, and is
	   the active channel, this is set true and data flow is not halted. */
	*scan_current_only = false;

	अगर (user_scan_in) अणु
		u8 पंचांगpaddr[ETH_ALEN];

		/* Default the ssid_filter flag to TRUE, set false under
		   certain wildcard conditions and qualअगरied by the existence
		   of an SSID list beक्रमe marking the scan as filtered */
		ssid_filter = true;

		/* Set the BSS type scan filter, use Adapter setting अगर
		   unset */
		scan_cfg_out->bss_mode =
			(u8)(user_scan_in->bss_mode ?: adapter->scan_mode);

		/* Set the number of probes to send, use Adapter setting
		   अगर unset */
		num_probes = user_scan_in->num_probes ?: adapter->scan_probes;

		/*
		 * Set the BSSID filter to the incoming configuration,
		 * अगर non-zero.  If not set, it will reमुख्य disabled
		 * (all zeros).
		 */
		स_नकल(scan_cfg_out->specअगरic_bssid,
		       user_scan_in->specअगरic_bssid,
		       माप(scan_cfg_out->specअगरic_bssid));

		स_नकल(पंचांगpaddr, scan_cfg_out->specअगरic_bssid, ETH_ALEN);

		अगर (adapter->ext_scan &&
		    !is_zero_ether_addr(पंचांगpaddr)) अणु
			bssid_tlv =
				(काष्ठा mwअगरiex_ie_types_bssid_list *)tlv_pos;
			bssid_tlv->header.type = cpu_to_le16(TLV_TYPE_BSSID);
			bssid_tlv->header.len = cpu_to_le16(ETH_ALEN);
			स_नकल(bssid_tlv->bssid, user_scan_in->specअगरic_bssid,
			       ETH_ALEN);
			tlv_pos += माप(काष्ठा mwअगरiex_ie_types_bssid_list);
		पूर्ण

		क्रम (i = 0; i < user_scan_in->num_ssids; i++) अणु
			ssid_len = user_scan_in->ssid_list[i].ssid_len;

			wildcard_ssid_tlv =
				(काष्ठा mwअगरiex_ie_types_wildcard_ssid_params *)
				tlv_pos;
			wildcard_ssid_tlv->header.type =
				cpu_to_le16(TLV_TYPE_WILDCARDSSID);
			wildcard_ssid_tlv->header.len = cpu_to_le16(
				(u16) (ssid_len + माप(wildcard_ssid_tlv->
							 max_ssid_length)));

			/*
			 * max_ssid_length = 0 tells firmware to perक्रमm
			 * specअगरic scan क्रम the SSID filled, whereas
			 * max_ssid_length = IEEE80211_MAX_SSID_LEN is क्रम
			 * wildcard scan.
			 */
			अगर (ssid_len)
				wildcard_ssid_tlv->max_ssid_length = 0;
			अन्यथा
				wildcard_ssid_tlv->max_ssid_length =
							IEEE80211_MAX_SSID_LEN;

			अगर (!स_भेद(user_scan_in->ssid_list[i].ssid,
				    "DIRECT-", 7))
				wildcard_ssid_tlv->max_ssid_length = 0xfe;

			स_नकल(wildcard_ssid_tlv->ssid,
			       user_scan_in->ssid_list[i].ssid, ssid_len);

			tlv_pos += (माप(wildcard_ssid_tlv->header)
				+ le16_to_cpu(wildcard_ssid_tlv->header.len));

			mwअगरiex_dbg(adapter, INFO,
				    "info: scan: ssid[%d]: %s, %d\n",
				    i, wildcard_ssid_tlv->ssid,
				    wildcard_ssid_tlv->max_ssid_length);

			/* Empty wildcard ssid with a maxlen will match many or
			   potentially all SSIDs (maxlen == 32), thereक्रमe करो
			   not treat the scan as
			   filtered. */
			अगर (!ssid_len && wildcard_ssid_tlv->max_ssid_length)
				ssid_filter = false;
		पूर्ण

		/*
		 *  The शेष number of channels sent in the command is low to
		 *  ensure the response buffer from the firmware करोes not
		 *  truncate scan results.  That is not an issue with an SSID
		 *  or BSSID filter applied to the scan results in the firmware.
		 */
		स_नकल(पंचांगpaddr, scan_cfg_out->specअगरic_bssid, ETH_ALEN);
		अगर ((i && ssid_filter) ||
		    !is_zero_ether_addr(पंचांगpaddr))
			*filtered_scan = true;

		अगर (user_scan_in->scan_chan_gap) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "info: scan: channel gap = %d\n",
				    user_scan_in->scan_chan_gap);
			*max_chan_per_scan =
					MWIFIEX_MAX_CHANNELS_PER_SPECIFIC_SCAN;

			chan_gap_tlv = (व्योम *)tlv_pos;
			chan_gap_tlv->header.type =
					 cpu_to_le16(TLV_TYPE_SCAN_CHANNEL_GAP);
			chan_gap_tlv->header.len =
				    cpu_to_le16(माप(chan_gap_tlv->chan_gap));
			chan_gap_tlv->chan_gap =
				     cpu_to_le16((user_scan_in->scan_chan_gap));
			tlv_pos +=
				  माप(काष्ठा mwअगरiex_ie_types_scan_chan_gap);
		पूर्ण

		अगर (!ether_addr_equal(user_scan_in->अक्रमom_mac, zero_mac)) अणु
			अक्रमom_mac_tlv = (व्योम *)tlv_pos;
			अक्रमom_mac_tlv->header.type =
					 cpu_to_le16(TLV_TYPE_RANDOM_MAC);
			अक्रमom_mac_tlv->header.len =
				    cpu_to_le16(माप(अक्रमom_mac_tlv->mac));
			ether_addr_copy(अक्रमom_mac_tlv->mac,
					user_scan_in->अक्रमom_mac);
			tlv_pos +=
				  माप(काष्ठा mwअगरiex_ie_types_अक्रमom_mac);
		पूर्ण
	पूर्ण अन्यथा अणु
		scan_cfg_out->bss_mode = (u8) adapter->scan_mode;
		num_probes = adapter->scan_probes;
	पूर्ण

	/*
	 *  If a specअगरic BSSID or SSID is used, the number of channels in the
	 *  scan command will be increased to the असलolute maximum.
	 */
	अगर (*filtered_scan) अणु
		*max_chan_per_scan = MWIFIEX_MAX_CHANNELS_PER_SPECIFIC_SCAN;
	पूर्ण अन्यथा अणु
		अगर (!priv->media_connected)
			*max_chan_per_scan = MWIFIEX_DEF_CHANNELS_PER_SCAN_CMD;
		अन्यथा
			*max_chan_per_scan =
					MWIFIEX_DEF_CHANNELS_PER_SCAN_CMD / 2;
	पूर्ण

	अगर (adapter->ext_scan) अणु
		bss_mode = (काष्ठा mwअगरiex_ie_types_bss_mode *)tlv_pos;
		bss_mode->header.type = cpu_to_le16(TLV_TYPE_BSS_MODE);
		bss_mode->header.len = cpu_to_le16(माप(bss_mode->bss_mode));
		bss_mode->bss_mode = scan_cfg_out->bss_mode;
		tlv_pos += माप(bss_mode->header) +
			   le16_to_cpu(bss_mode->header.len);
	पूर्ण

	/* If the input config or adapter has the number of Probes set,
	   add tlv */
	अगर (num_probes) अणु

		mwअगरiex_dbg(adapter, INFO,
			    "info: scan: num_probes = %d\n",
			    num_probes);

		num_probes_tlv = (काष्ठा mwअगरiex_ie_types_num_probes *) tlv_pos;
		num_probes_tlv->header.type = cpu_to_le16(TLV_TYPE_NUMPROBES);
		num_probes_tlv->header.len =
			cpu_to_le16(माप(num_probes_tlv->num_probes));
		num_probes_tlv->num_probes = cpu_to_le16((u16) num_probes);

		tlv_pos += माप(num_probes_tlv->header) +
			le16_to_cpu(num_probes_tlv->header.len);

	पूर्ण

	अगर (ISSUPP_11NENABLED(priv->adapter->fw_cap_info) &&
	    (priv->adapter->config_bands & BAND_GN ||
	     priv->adapter->config_bands & BAND_AN)) अणु
		ht_cap = (काष्ठा mwअगरiex_ie_types_htcap *) tlv_pos;
		स_रखो(ht_cap, 0, माप(काष्ठा mwअगरiex_ie_types_htcap));
		ht_cap->header.type = cpu_to_le16(WLAN_EID_HT_CAPABILITY);
		ht_cap->header.len =
				cpu_to_le16(माप(काष्ठा ieee80211_ht_cap));
		radio_type =
			mwअगरiex_band_to_radio_type(priv->adapter->config_bands);
		mwअगरiex_fill_cap_info(priv, radio_type, &ht_cap->ht_cap);
		tlv_pos += माप(काष्ठा mwअगरiex_ie_types_htcap);
	पूर्ण

	/* Append venकरोr specअगरic IE TLV */
	mwअगरiex_cmd_append_vsie_tlv(priv, MWIFIEX_VSIE_MASK_SCAN, &tlv_pos);

	/*
	 * Set the output क्रम the channel TLV to the address in the tlv buffer
	 *   past any TLVs that were added in this function (SSID, num_probes).
	 *   Channel TLVs will be added past this क्रम each scan command,
	 *   preserving the TLVs that were previously added.
	 */
	*chan_list_out =
		(काष्ठा mwअगरiex_ie_types_chan_list_param_set *) tlv_pos;

	अगर (user_scan_in && user_scan_in->chan_list[0].chan_number) अणु

		mwअगरiex_dbg(adapter, INFO,
			    "info: Scan: Using supplied channel list\n");

		क्रम (chan_idx = 0;
		     chan_idx < MWIFIEX_USER_SCAN_CHAN_MAX &&
		     user_scan_in->chan_list[chan_idx].chan_number;
		     chan_idx++) अणु

			channel = user_scan_in->chan_list[chan_idx].chan_number;
			scan_chan_list[chan_idx].chan_number = channel;

			radio_type =
				user_scan_in->chan_list[chan_idx].radio_type;
			scan_chan_list[chan_idx].radio_type = radio_type;

			scan_type = user_scan_in->chan_list[chan_idx].scan_type;

			अगर (scan_type == MWIFIEX_SCAN_TYPE_PASSIVE)
				scan_chan_list[chan_idx].chan_scan_mode_biपंचांगap
					|= (MWIFIEX_PASSIVE_SCAN |
					    MWIFIEX_HIDDEN_SSID_REPORT);
			अन्यथा
				scan_chan_list[chan_idx].chan_scan_mode_biपंचांगap
					&= ~MWIFIEX_PASSIVE_SCAN;

			scan_chan_list[chan_idx].chan_scan_mode_biपंचांगap
				|= MWIFIEX_DISABLE_CHAN_FILT;

			अगर (user_scan_in->chan_list[chan_idx].scan_समय) अणु
				scan_dur = (u16) user_scan_in->
					chan_list[chan_idx].scan_समय;
			पूर्ण अन्यथा अणु
				अगर (scan_type == MWIFIEX_SCAN_TYPE_PASSIVE)
					scan_dur = adapter->passive_scan_समय;
				अन्यथा अगर (*filtered_scan)
					scan_dur = adapter->specअगरic_scan_समय;
				अन्यथा
					scan_dur = adapter->active_scan_समय;
			पूर्ण

			scan_chan_list[chan_idx].min_scan_समय =
				cpu_to_le16(scan_dur);
			scan_chan_list[chan_idx].max_scan_समय =
				cpu_to_le16(scan_dur);
		पूर्ण

		/* Check अगर we are only scanning the current channel */
		अगर ((chan_idx == 1) &&
		    (user_scan_in->chan_list[0].chan_number ==
		     priv->curr_bss_params.bss_descriptor.channel)) अणु
			*scan_current_only = true;
			mwअगरiex_dbg(adapter, INFO,
				    "info: Scan: Scanning current channel only\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, INFO,
			    "info: Scan: Creating full region channel list\n");
		mwअगरiex_scan_create_channel_list(priv, user_scan_in,
						 scan_chan_list,
						 *filtered_scan);
	पूर्ण

पूर्ण

/*
 * This function inspects the scan response buffer क्रम poपूर्णांकers to
 * expected TLVs.
 *
 * TLVs can be included at the end of the scan response BSS inक्रमmation.
 *
 * Data in the buffer is parsed poपूर्णांकers to TLVs that can potentially
 * be passed back in the response.
 */
अटल व्योम
mwअगरiex_ret_802_11_scan_get_tlv_ptrs(काष्ठा mwअगरiex_adapter *adapter,
				     काष्ठा mwअगरiex_ie_types_data *tlv,
				     u32 tlv_buf_size, u32 req_tlv_type,
				     काष्ठा mwअगरiex_ie_types_data **tlv_data)
अणु
	काष्ठा mwअगरiex_ie_types_data *current_tlv;
	u32 tlv_buf_left;
	u32 tlv_type;
	u32 tlv_len;

	current_tlv = tlv;
	tlv_buf_left = tlv_buf_size;
	*tlv_data = शून्य;

	mwअगरiex_dbg(adapter, INFO,
		    "info: SCAN_RESP: tlv_buf_size = %d\n",
		    tlv_buf_size);

	जबतक (tlv_buf_left >= माप(काष्ठा mwअगरiex_ie_types_header)) अणु

		tlv_type = le16_to_cpu(current_tlv->header.type);
		tlv_len = le16_to_cpu(current_tlv->header.len);

		अगर (माप(tlv->header) + tlv_len > tlv_buf_left) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "SCAN_RESP: TLV buffer corrupt\n");
			अवरोध;
		पूर्ण

		अगर (req_tlv_type == tlv_type) अणु
			चयन (tlv_type) अणु
			हाल TLV_TYPE_TSFTIMESTAMP:
				mwअगरiex_dbg(adapter, INFO,
					    "info: SCAN_RESP: TSF\t"
					    "timestamp TLV, len = %d\n",
					    tlv_len);
				*tlv_data = current_tlv;
				अवरोध;
			हाल TLV_TYPE_CHANNELBANDLIST:
				mwअगरiex_dbg(adapter, INFO,
					    "info: SCAN_RESP: channel\t"
					    "band list TLV, len = %d\n",
					    tlv_len);
				*tlv_data = current_tlv;
				अवरोध;
			शेष:
				mwअगरiex_dbg(adapter, ERROR,
					    "SCAN_RESP: unhandled TLV = %d\n",
					    tlv_type);
				/* Give up, this seems corrupted */
				वापस;
			पूर्ण
		पूर्ण

		अगर (*tlv_data)
			अवरोध;


		tlv_buf_left -= (माप(tlv->header) + tlv_len);
		current_tlv =
			(काष्ठा mwअगरiex_ie_types_data *) (current_tlv->data +
							  tlv_len);

	पूर्ण			/* जबतक */
पूर्ण

/*
 * This function parses provided beacon buffer and updates
 * respective fields in bss descriptor काष्ठाure.
 */
पूर्णांक mwअगरiex_update_bss_desc_with_ie(काष्ठा mwअगरiex_adapter *adapter,
				    काष्ठा mwअगरiex_bssdescriptor *bss_entry)
अणु
	u8 element_id;
	काष्ठा ieee_types_fh_param_set *fh_param_set;
	काष्ठा ieee_types_ds_param_set *ds_param_set;
	काष्ठा ieee_types_cf_param_set *cf_param_set;
	काष्ठा ieee_types_ibss_param_set *ibss_param_set;
	u8 *current_ptr;
	u8 *rate;
	u8 element_len;
	u16 total_ie_len;
	u8 bytes_to_copy;
	u8 rate_size;
	u8 found_data_rate_ie;
	u32 bytes_left;
	काष्ठा ieee_types_venकरोr_specअगरic *venकरोr_ie;
	स्थिर u8 wpa_oui[4] = अणु 0x00, 0x50, 0xf2, 0x01 पूर्ण;
	स्थिर u8 wmm_oui[4] = अणु 0x00, 0x50, 0xf2, 0x02 पूर्ण;

	found_data_rate_ie = false;
	rate_size = 0;
	current_ptr = bss_entry->beacon_buf;
	bytes_left = bss_entry->beacon_buf_size;

	/* Process variable IE */
	जबतक (bytes_left >= 2) अणु
		element_id = *current_ptr;
		element_len = *(current_ptr + 1);
		total_ie_len = element_len + माप(काष्ठा ieee_types_header);

		अगर (bytes_left < total_ie_len) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "err: InterpretIE: in processing\t"
				    "IE, bytes left < IE length\n");
			वापस -EINVAL;
		पूर्ण
		चयन (element_id) अणु
		हाल WLAN_EID_SSID:
			अगर (element_len > IEEE80211_MAX_SSID_LEN)
				वापस -EINVAL;
			bss_entry->ssid.ssid_len = element_len;
			स_नकल(bss_entry->ssid.ssid, (current_ptr + 2),
			       element_len);
			mwअगरiex_dbg(adapter, INFO,
				    "info: InterpretIE: ssid: %-32s\n",
				    bss_entry->ssid.ssid);
			अवरोध;

		हाल WLAN_EID_SUPP_RATES:
			अगर (element_len > MWIFIEX_SUPPORTED_RATES)
				वापस -EINVAL;
			स_नकल(bss_entry->data_rates, current_ptr + 2,
			       element_len);
			स_नकल(bss_entry->supported_rates, current_ptr + 2,
			       element_len);
			rate_size = element_len;
			found_data_rate_ie = true;
			अवरोध;

		हाल WLAN_EID_FH_PARAMS:
			अगर (total_ie_len < माप(*fh_param_set))
				वापस -EINVAL;
			fh_param_set =
				(काष्ठा ieee_types_fh_param_set *) current_ptr;
			स_नकल(&bss_entry->phy_param_set.fh_param_set,
			       fh_param_set,
			       माप(काष्ठा ieee_types_fh_param_set));
			अवरोध;

		हाल WLAN_EID_DS_PARAMS:
			अगर (total_ie_len < माप(*ds_param_set))
				वापस -EINVAL;
			ds_param_set =
				(काष्ठा ieee_types_ds_param_set *) current_ptr;

			bss_entry->channel = ds_param_set->current_chan;

			स_नकल(&bss_entry->phy_param_set.ds_param_set,
			       ds_param_set,
			       माप(काष्ठा ieee_types_ds_param_set));
			अवरोध;

		हाल WLAN_EID_CF_PARAMS:
			अगर (total_ie_len < माप(*cf_param_set))
				वापस -EINVAL;
			cf_param_set =
				(काष्ठा ieee_types_cf_param_set *) current_ptr;
			स_नकल(&bss_entry->ss_param_set.cf_param_set,
			       cf_param_set,
			       माप(काष्ठा ieee_types_cf_param_set));
			अवरोध;

		हाल WLAN_EID_IBSS_PARAMS:
			अगर (total_ie_len < माप(*ibss_param_set))
				वापस -EINVAL;
			ibss_param_set =
				(काष्ठा ieee_types_ibss_param_set *)
				current_ptr;
			स_नकल(&bss_entry->ss_param_set.ibss_param_set,
			       ibss_param_set,
			       माप(काष्ठा ieee_types_ibss_param_set));
			अवरोध;

		हाल WLAN_EID_ERP_INFO:
			अगर (!element_len)
				वापस -EINVAL;
			bss_entry->erp_flags = *(current_ptr + 2);
			अवरोध;

		हाल WLAN_EID_PWR_CONSTRAINT:
			अगर (!element_len)
				वापस -EINVAL;
			bss_entry->local_स्थिरraपूर्णांक = *(current_ptr + 2);
			bss_entry->sensed_11h = true;
			अवरोध;

		हाल WLAN_EID_CHANNEL_SWITCH:
			bss_entry->chan_sw_ie_present = true;
			fallthrough;
		हाल WLAN_EID_PWR_CAPABILITY:
		हाल WLAN_EID_TPC_REPORT:
		हाल WLAN_EID_QUIET:
			bss_entry->sensed_11h = true;
		    अवरोध;

		हाल WLAN_EID_EXT_SUPP_RATES:
			/*
			 * Only process extended supported rate
			 * अगर data rate is alपढ़ोy found.
			 * Data rate IE should come beक्रमe
			 * extended supported rate IE
			 */
			अगर (found_data_rate_ie) अणु
				अगर ((element_len + rate_size) >
				    MWIFIEX_SUPPORTED_RATES)
					bytes_to_copy =
						(MWIFIEX_SUPPORTED_RATES -
						 rate_size);
				अन्यथा
					bytes_to_copy = element_len;

				rate = (u8 *) bss_entry->data_rates;
				rate += rate_size;
				स_नकल(rate, current_ptr + 2, bytes_to_copy);

				rate = (u8 *) bss_entry->supported_rates;
				rate += rate_size;
				स_नकल(rate, current_ptr + 2, bytes_to_copy);
			पूर्ण
			अवरोध;

		हाल WLAN_EID_VENDOR_SPECIFIC:
			venकरोr_ie = (काष्ठा ieee_types_venकरोr_specअगरic *)
					current_ptr;

			/* 802.11 requires at least 3-byte OUI. */
			अगर (element_len < माप(venकरोr_ie->vend_hdr.oui.oui))
				वापस -EINVAL;

			/* Not दीर्घ enough क्रम a match? Skip it. */
			अगर (element_len < माप(wpa_oui))
				अवरोध;

			अगर (!स_भेद(&venकरोr_ie->vend_hdr.oui, wpa_oui,
				    माप(wpa_oui))) अणु
				bss_entry->bcn_wpa_ie =
					(काष्ठा ieee_types_venकरोr_specअगरic *)
					current_ptr;
				bss_entry->wpa_offset = (u16)
					(current_ptr - bss_entry->beacon_buf);
			पूर्ण अन्यथा अगर (!स_भेद(&venकरोr_ie->vend_hdr.oui, wmm_oui,
				    माप(wmm_oui))) अणु
				अगर (total_ie_len ==
				    माप(काष्ठा ieee_types_wmm_parameter) ||
				    total_ie_len ==
				    माप(काष्ठा ieee_types_wmm_info))
					/*
					 * Only accept and copy the WMM IE अगर
					 * it matches the size expected क्रम the
					 * WMM Info IE or the WMM Parameter IE.
					 */
					स_नकल((u8 *) &bss_entry->wmm_ie,
					       current_ptr, total_ie_len);
			पूर्ण
			अवरोध;
		हाल WLAN_EID_RSN:
			bss_entry->bcn_rsn_ie =
				(काष्ठा ieee_types_generic *) current_ptr;
			bss_entry->rsn_offset = (u16) (current_ptr -
							bss_entry->beacon_buf);
			अवरोध;
		हाल WLAN_EID_BSS_AC_ACCESS_DELAY:
			bss_entry->bcn_wapi_ie =
				(काष्ठा ieee_types_generic *) current_ptr;
			bss_entry->wapi_offset = (u16) (current_ptr -
							bss_entry->beacon_buf);
			अवरोध;
		हाल WLAN_EID_HT_CAPABILITY:
			bss_entry->bcn_ht_cap = (काष्ठा ieee80211_ht_cap *)
					(current_ptr +
					माप(काष्ठा ieee_types_header));
			bss_entry->ht_cap_offset = (u16) (current_ptr +
					माप(काष्ठा ieee_types_header) -
					bss_entry->beacon_buf);
			अवरोध;
		हाल WLAN_EID_HT_OPERATION:
			bss_entry->bcn_ht_oper =
				(काष्ठा ieee80211_ht_operation *)(current_ptr +
					माप(काष्ठा ieee_types_header));
			bss_entry->ht_info_offset = (u16) (current_ptr +
					माप(काष्ठा ieee_types_header) -
					bss_entry->beacon_buf);
			अवरोध;
		हाल WLAN_EID_VHT_CAPABILITY:
			bss_entry->disable_11ac = false;
			bss_entry->bcn_vht_cap =
				(व्योम *)(current_ptr +
					 माप(काष्ठा ieee_types_header));
			bss_entry->vht_cap_offset =
					(u16)((u8 *)bss_entry->bcn_vht_cap -
					      bss_entry->beacon_buf);
			अवरोध;
		हाल WLAN_EID_VHT_OPERATION:
			bss_entry->bcn_vht_oper =
				(व्योम *)(current_ptr +
					 माप(काष्ठा ieee_types_header));
			bss_entry->vht_info_offset =
					(u16)((u8 *)bss_entry->bcn_vht_oper -
					      bss_entry->beacon_buf);
			अवरोध;
		हाल WLAN_EID_BSS_COEX_2040:
			bss_entry->bcn_bss_co_2040 = current_ptr;
			bss_entry->bss_co_2040_offset =
				(u16) (current_ptr - bss_entry->beacon_buf);
			अवरोध;
		हाल WLAN_EID_EXT_CAPABILITY:
			bss_entry->bcn_ext_cap = current_ptr;
			bss_entry->ext_cap_offset =
				(u16) (current_ptr - bss_entry->beacon_buf);
			अवरोध;
		हाल WLAN_EID_OPMODE_NOTIF:
			bss_entry->oper_mode = (व्योम *)current_ptr;
			bss_entry->oper_mode_offset =
					(u16)((u8 *)bss_entry->oper_mode -
					      bss_entry->beacon_buf);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		current_ptr += total_ie_len;
		bytes_left -= total_ie_len;

	पूर्ण	/* जबतक (bytes_left > 2) */
	वापस 0;
पूर्ण

/*
 * This function converts radio type scan parameter to a band configuration
 * to be used in join command.
 */
अटल u8
mwअगरiex_radio_type_to_band(u8 radio_type)
अणु
	चयन (radio_type) अणु
	हाल HostCmd_SCAN_RADIO_TYPE_A:
		वापस BAND_A;
	हाल HostCmd_SCAN_RADIO_TYPE_BG:
	शेष:
		वापस BAND_G;
	पूर्ण
पूर्ण

/*
 * This is an पूर्णांकernal function used to start a scan based on an input
 * configuration.
 *
 * This uses the input user scan configuration inक्रमmation when provided in
 * order to send the appropriate scan commands to firmware to populate or
 * update the पूर्णांकernal driver scan table.
 */
पूर्णांक mwअगरiex_scan_networks(काष्ठा mwअगरiex_निजी *priv,
			  स्थिर काष्ठा mwअगरiex_user_scan_cfg *user_scan_in)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा cmd_ctrl_node *cmd_node;
	जोड़ mwअगरiex_scan_cmd_config_tlv *scan_cfg_out;
	काष्ठा mwअगरiex_ie_types_chan_list_param_set *chan_list_out;
	काष्ठा mwअगरiex_chan_scan_param_set *scan_chan_list;
	u8 filtered_scan;
	u8 scan_current_chan_only;
	u8 max_chan_per_scan;

	अगर (adapter->scan_processing) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "cmd: Scan already in process...\n");
		वापस -EBUSY;
	पूर्ण

	अगर (priv->scan_block) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "cmd: Scan is blocked during association...\n");
		वापस -EBUSY;
	पूर्ण

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags) ||
	    test_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Ignore scan. Card removed or firmware in bad state\n");
		वापस -EFAULT;
	पूर्ण

	spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
	adapter->scan_processing = true;
	spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);

	scan_cfg_out = kzalloc(माप(जोड़ mwअगरiex_scan_cmd_config_tlv),
			       GFP_KERNEL);
	अगर (!scan_cfg_out) अणु
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	scan_chan_list = kसुस्मृति(MWIFIEX_USER_SCAN_CHAN_MAX,
				 माप(काष्ठा mwअगरiex_chan_scan_param_set),
				 GFP_KERNEL);
	अगर (!scan_chan_list) अणु
		kमुक्त(scan_cfg_out);
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण

	mwअगरiex_config_scan(priv, user_scan_in, &scan_cfg_out->config,
			    &chan_list_out, scan_chan_list, &max_chan_per_scan,
			    &filtered_scan, &scan_current_chan_only);

	ret = mwअगरiex_scan_channel_list(priv, max_chan_per_scan, filtered_scan,
					&scan_cfg_out->config, chan_list_out,
					scan_chan_list);

	/* Get scan command from scan_pending_q and put to cmd_pending_q */
	अगर (!ret) अणु
		spin_lock_bh(&adapter->scan_pending_q_lock);
		अगर (!list_empty(&adapter->scan_pending_q)) अणु
			cmd_node = list_first_entry(&adapter->scan_pending_q,
						    काष्ठा cmd_ctrl_node, list);
			list_del(&cmd_node->list);
			spin_unlock_bh(&adapter->scan_pending_q_lock);
			mwअगरiex_insert_cmd_to_pending_q(adapter, cmd_node);
			queue_work(adapter->workqueue, &adapter->मुख्य_work);

			/* Perक्रमm पूर्णांकernal scan synchronously */
			अगर (!priv->scan_request) अणु
				mwअगरiex_dbg(adapter, INFO,
					    "wait internal scan\n");
				mwअगरiex_रुको_queue_complete(adapter, cmd_node);
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&adapter->scan_pending_q_lock);
		पूर्ण
	पूर्ण

	kमुक्त(scan_cfg_out);
	kमुक्त(scan_chan_list);
करोne:
	अगर (ret) अणु
		spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
		adapter->scan_processing = false;
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This function prepares a scan command to be sent to the firmware.
 *
 * This uses the scan command configuration sent to the command processing
 * module in command preparation stage to configure a scan command काष्ठाure
 * to send to firmware.
 *
 * The fixed fields specअगरying the BSS type and BSSID filters as well as a
 * variable number/length of TLVs are sent in the command to firmware.
 *
 * Preparation also includes -
 *      - Setting command ID, and proper size
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_802_11_scan(काष्ठा host_cmd_ds_command *cmd,
			    काष्ठा mwअगरiex_scan_cmd_config *scan_cfg)
अणु
	काष्ठा host_cmd_ds_802_11_scan *scan_cmd = &cmd->params.scan;

	/* Set fixed field variables in scan command */
	scan_cmd->bss_mode = scan_cfg->bss_mode;
	स_नकल(scan_cmd->bssid, scan_cfg->specअगरic_bssid,
	       माप(scan_cmd->bssid));
	स_नकल(scan_cmd->tlv_buffer, scan_cfg->tlv_buf, scan_cfg->tlv_buf_len);

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_SCAN);

	/* Size is equal to the माप(fixed portions) + the TLV len + header */
	cmd->size = cpu_to_le16((u16) (माप(scan_cmd->bss_mode)
					  + माप(scan_cmd->bssid)
					  + scan_cfg->tlv_buf_len + S_DS_GEN));

	वापस 0;
पूर्ण

/*
 * This function checks compatibility of requested network with current
 * driver settings.
 */
पूर्णांक mwअगरiex_check_network_compatibility(काष्ठा mwअगरiex_निजी *priv,
					काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	पूर्णांक ret = -1;

	अगर (!bss_desc)
		वापस -1;

	अगर ((mwअगरiex_get_cfp(priv, (u8) bss_desc->bss_band,
			     (u16) bss_desc->channel, 0))) अणु
		चयन (priv->bss_mode) अणु
		हाल NL80211_IFTYPE_STATION:
		हाल NL80211_IFTYPE_ADHOC:
			ret = mwअगरiex_is_network_compatible(priv, bss_desc,
							    priv->bss_mode);
			अगर (ret)
				mwअगरiex_dbg(priv->adapter, ERROR,
					    "Incompatible network settings\n");
			अवरोध;
		शेष:
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* This function checks अगर SSID string contains all zeroes or length is zero */
अटल bool mwअगरiex_is_hidden_ssid(काष्ठा cfg80211_ssid *ssid)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < ssid->ssid_len; idx++) अणु
		अगर (ssid->ssid[idx])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* This function checks अगर any hidden SSID found in passive scan channels
 * and save those channels क्रम specअगरic SSID active scan
 */
अटल पूर्णांक mwअगरiex_save_hidden_ssid_channels(काष्ठा mwअगरiex_निजी *priv,
					     काष्ठा cfg80211_bss *bss)
अणु
	काष्ठा mwअगरiex_bssdescriptor *bss_desc;
	पूर्णांक ret;
	पूर्णांक chid;

	/* Allocate and fill new bss descriptor */
	bss_desc = kzalloc(माप(*bss_desc), GFP_KERNEL);
	अगर (!bss_desc)
		वापस -ENOMEM;

	ret = mwअगरiex_fill_new_bss_desc(priv, bss, bss_desc);
	अगर (ret)
		जाओ करोne;

	अगर (mwअगरiex_is_hidden_ssid(&bss_desc->ssid)) अणु
		mwअगरiex_dbg(priv->adapter, INFO, "found hidden SSID\n");
		क्रम (chid = 0 ; chid < MWIFIEX_USER_SCAN_CHAN_MAX; chid++) अणु
			अगर (priv->hidden_chan[chid].chan_number ==
			    bss->channel->hw_value)
				अवरोध;

			अगर (!priv->hidden_chan[chid].chan_number) अणु
				priv->hidden_chan[chid].chan_number =
					bss->channel->hw_value;
				priv->hidden_chan[chid].radio_type =
					bss->channel->band;
				priv->hidden_chan[chid].scan_type =
					MWIFIEX_SCAN_TYPE_ACTIVE;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	/* beacon_ie buffer was allocated in function
	 * mwअगरiex_fill_new_bss_desc(). Free it now.
	 */
	kमुक्त(bss_desc->beacon_buf);
	kमुक्त(bss_desc);
	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_update_curr_bss_params(काष्ठा mwअगरiex_निजी *priv,
					  काष्ठा cfg80211_bss *bss)
अणु
	काष्ठा mwअगरiex_bssdescriptor *bss_desc;
	पूर्णांक ret;

	/* Allocate and fill new bss descriptor */
	bss_desc = kzalloc(माप(काष्ठा mwअगरiex_bssdescriptor), GFP_KERNEL);
	अगर (!bss_desc)
		वापस -ENOMEM;

	ret = mwअगरiex_fill_new_bss_desc(priv, bss, bss_desc);
	अगर (ret)
		जाओ करोne;

	ret = mwअगरiex_check_network_compatibility(priv, bss_desc);
	अगर (ret)
		जाओ करोne;

	spin_lock_bh(&priv->curr_bcn_buf_lock);
	/* Make a copy of current BSSID descriptor */
	स_नकल(&priv->curr_bss_params.bss_descriptor, bss_desc,
	       माप(priv->curr_bss_params.bss_descriptor));

	/* The contents of beacon_ie will be copied to its own buffer
	 * in mwअगरiex_save_curr_bcn()
	 */
	mwअगरiex_save_curr_bcn(priv);
	spin_unlock_bh(&priv->curr_bcn_buf_lock);

करोne:
	/* beacon_ie buffer was allocated in function
	 * mwअगरiex_fill_new_bss_desc(). Free it now.
	 */
	kमुक्त(bss_desc->beacon_buf);
	kमुक्त(bss_desc);
	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_parse_single_response_buf(काष्ठा mwअगरiex_निजी *priv, u8 **bss_info,
				  u32 *bytes_left, u64 fw_tsf, u8 *radio_type,
				  bool ext_scan, s32 rssi_val)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_chan_freq_घातer *cfp;
	काष्ठा cfg80211_bss *bss;
	u8 bssid[ETH_ALEN];
	s32 rssi;
	स्थिर u8 *ie_buf;
	माप_प्रकार ie_len;
	u16 channel = 0;
	u16 beacon_size = 0;
	u32 curr_bcn_bytes;
	u32 freq;
	u16 beacon_period;
	u16 cap_info_biपंचांगap;
	u8 *current_ptr;
	u64 बारtamp;
	काष्ठा mwअगरiex_fixed_bcn_param *bcn_param;
	काष्ठा mwअगरiex_bss_priv *bss_priv;

	अगर (*bytes_left >= माप(beacon_size)) अणु
		/* Extract & convert beacon size from command buffer */
		beacon_size = get_unaligned_le16((*bss_info));
		*bytes_left -= माप(beacon_size);
		*bss_info += माप(beacon_size);
	पूर्ण

	अगर (!beacon_size || beacon_size > *bytes_left) अणु
		*bss_info += *bytes_left;
		*bytes_left = 0;
		वापस -EFAULT;
	पूर्ण

	/* Initialize the current working beacon poपूर्णांकer क्रम this BSS
	 * iteration
	 */
	current_ptr = *bss_info;

	/* Advance the वापस beacon poपूर्णांकer past the current beacon */
	*bss_info += beacon_size;
	*bytes_left -= beacon_size;

	curr_bcn_bytes = beacon_size;

	/* First 5 fields are bssid, RSSI(क्रम legacy scan only),
	 * समय stamp, beacon पूर्णांकerval, and capability inक्रमmation
	 */
	अगर (curr_bcn_bytes < ETH_ALEN + माप(u8) +
	    माप(काष्ठा mwअगरiex_fixed_bcn_param)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "InterpretIE: not enough bytes left\n");
		वापस -EFAULT;
	पूर्ण

	स_नकल(bssid, current_ptr, ETH_ALEN);
	current_ptr += ETH_ALEN;
	curr_bcn_bytes -= ETH_ALEN;

	अगर (!ext_scan) अणु
		rssi = (s32) *current_ptr;
		rssi = (-rssi) * 100;		/* Convert dBm to mBm */
		current_ptr += माप(u8);
		curr_bcn_bytes -= माप(u8);
		mwअगरiex_dbg(adapter, INFO,
			    "info: InterpretIE: RSSI=%d\n", rssi);
	पूर्ण अन्यथा अणु
		rssi = rssi_val;
	पूर्ण

	bcn_param = (काष्ठा mwअगरiex_fixed_bcn_param *)current_ptr;
	current_ptr += माप(*bcn_param);
	curr_bcn_bytes -= माप(*bcn_param);

	बारtamp = le64_to_cpu(bcn_param->बारtamp);
	beacon_period = le16_to_cpu(bcn_param->beacon_period);

	cap_info_biपंचांगap = le16_to_cpu(bcn_param->cap_info_biपंचांगap);
	mwअगरiex_dbg(adapter, INFO,
		    "info: InterpretIE: capabilities=0x%X\n",
		    cap_info_biपंचांगap);

	/* Rest of the current buffer are IE's */
	ie_buf = current_ptr;
	ie_len = curr_bcn_bytes;
	mwअगरiex_dbg(adapter, INFO,
		    "info: InterpretIE: IELength for this AP = %d\n",
		    curr_bcn_bytes);

	जबतक (curr_bcn_bytes >= माप(काष्ठा ieee_types_header)) अणु
		u8 element_id, element_len;

		element_id = *current_ptr;
		element_len = *(current_ptr + 1);
		अगर (curr_bcn_bytes < element_len +
				माप(काष्ठा ieee_types_header)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "%s: bytes left < IE length\n", __func__);
			वापस -EFAULT;
		पूर्ण
		अगर (element_id == WLAN_EID_DS_PARAMS) अणु
			channel = *(current_ptr +
				    माप(काष्ठा ieee_types_header));
			अवरोध;
		पूर्ण

		current_ptr += element_len + माप(काष्ठा ieee_types_header);
		curr_bcn_bytes -= element_len +
					माप(काष्ठा ieee_types_header);
	पूर्ण

	अगर (channel) अणु
		काष्ठा ieee80211_channel *chan;
		u8 band;

		/* Skip entry अगर on csa बंदd channel */
		अगर (channel == priv->csa_chan) अणु
			mwअगरiex_dbg(adapter, WARN,
				    "Dropping entry on csa closed channel\n");
			वापस 0;
		पूर्ण

		band = BAND_G;
		अगर (radio_type)
			band = mwअगरiex_radio_type_to_band(*radio_type &
							  (BIT(0) | BIT(1)));

		cfp = mwअगरiex_get_cfp(priv, band, channel, 0);

		freq = cfp ? cfp->freq : 0;

		chan = ieee80211_get_channel(priv->wdev.wiphy, freq);

		अगर (chan && !(chan->flags & IEEE80211_CHAN_DISABLED)) अणु
			bss = cfg80211_inक्रमm_bss(priv->wdev.wiphy,
					    chan, CFG80211_BSS_FTYPE_UNKNOWN,
					    bssid, बारtamp,
					    cap_info_biपंचांगap, beacon_period,
					    ie_buf, ie_len, rssi, GFP_ATOMIC);
			अगर (bss) अणु
				bss_priv = (काष्ठा mwअगरiex_bss_priv *)bss->priv;
				bss_priv->band = band;
				bss_priv->fw_tsf = fw_tsf;
				अगर (priv->media_connected &&
				    !स_भेद(bssid, priv->curr_bss_params.
					    bss_descriptor.mac_address,
					    ETH_ALEN))
					mwअगरiex_update_curr_bss_params(priv,
								       bss);

				अगर ((chan->flags & IEEE80211_CHAN_RADAR) ||
				    (chan->flags & IEEE80211_CHAN_NO_IR)) अणु
					mwअगरiex_dbg(adapter, INFO,
						    "radar or passive channel %d\n",
						    channel);
					mwअगरiex_save_hidden_ssid_channels(priv,
									  bss);
				पूर्ण

				cfg80211_put_bss(priv->wdev.wiphy, bss);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, WARN, "missing BSS channel IE\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_complete_scan(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	adapter->survey_idx = 0;
	अगर (adapter->curr_cmd->रुको_q_enabled) अणु
		adapter->cmd_रुको_q.status = 0;
		अगर (!priv->scan_request) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "complete internal scan\n");
			mwअगरiex_complete_cmd(adapter, adapter->curr_cmd);
		पूर्ण
	पूर्ण
पूर्ण

/* This function checks अगर any hidden SSID found in passive scan channels
 * and करो specअगरic SSID active scan क्रम those channels
 */
अटल पूर्णांक
mwअगरiex_active_scan_req_क्रम_passive_chan(काष्ठा mwअगरiex_निजी *priv)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u8 id = 0;
	काष्ठा mwअगरiex_user_scan_cfg  *user_scan_cfg;

	अगर (adapter->active_scan_triggered || !priv->scan_request ||
	    priv->scan_पातing) अणु
		adapter->active_scan_triggered = false;
		वापस 0;
	पूर्ण

	अगर (!priv->hidden_chan[0].chan_number) अणु
		mwअगरiex_dbg(adapter, INFO, "No BSS with hidden SSID found on DFS channels\n");
		वापस 0;
	पूर्ण
	user_scan_cfg = kzalloc(माप(*user_scan_cfg), GFP_KERNEL);

	अगर (!user_scan_cfg)
		वापस -ENOMEM;

	क्रम (id = 0; id < MWIFIEX_USER_SCAN_CHAN_MAX; id++) अणु
		अगर (!priv->hidden_chan[id].chan_number)
			अवरोध;
		स_नकल(&user_scan_cfg->chan_list[id],
		       &priv->hidden_chan[id],
		       माप(काष्ठा mwअगरiex_user_scan_chan));
	पूर्ण

	adapter->active_scan_triggered = true;
	अगर (priv->scan_request->flags & NL80211_SCAN_FLAG_RANDOM_ADDR)
		ether_addr_copy(user_scan_cfg->अक्रमom_mac,
				priv->scan_request->mac_addr);
	user_scan_cfg->num_ssids = priv->scan_request->n_ssids;
	user_scan_cfg->ssid_list = priv->scan_request->ssids;

	ret = mwअगरiex_scan_networks(priv, user_scan_cfg);
	kमुक्त(user_scan_cfg);

	स_रखो(&priv->hidden_chan, 0, माप(priv->hidden_chan));

	अगर (ret) अणु
		dev_err(priv->adapter->dev, "scan failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
अटल व्योम mwअगरiex_check_next_scan_command(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा cmd_ctrl_node *cmd_node;

	spin_lock_bh(&adapter->scan_pending_q_lock);
	अगर (list_empty(&adapter->scan_pending_q)) अणु
		spin_unlock_bh(&adapter->scan_pending_q_lock);

		spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
		adapter->scan_processing = false;
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);

		mwअगरiex_active_scan_req_क्रम_passive_chan(priv);

		अगर (!adapter->ext_scan)
			mwअगरiex_complete_scan(priv);

		अगर (priv->scan_request) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = false,
			पूर्ण;

			mwअगरiex_dbg(adapter, INFO,
				    "info: notifying scan done\n");
			cfg80211_scan_करोne(priv->scan_request, &info);
			priv->scan_request = शून्य;
			priv->scan_पातing = false;
		पूर्ण अन्यथा अणु
			priv->scan_पातing = false;
			mwअगरiex_dbg(adapter, INFO,
				    "info: scan already aborted\n");
		पूर्ण
	पूर्ण अन्यथा अगर ((priv->scan_पातing && !priv->scan_request) ||
		   priv->scan_block) अणु
		spin_unlock_bh(&adapter->scan_pending_q_lock);

		mwअगरiex_cancel_pending_scan_cmd(adapter);

		spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
		adapter->scan_processing = false;
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);

		अगर (!adapter->active_scan_triggered) अणु
			अगर (priv->scan_request) अणु
				काष्ठा cfg80211_scan_info info = अणु
					.पातed = true,
				पूर्ण;

				mwअगरiex_dbg(adapter, INFO,
					    "info: aborting scan\n");
				cfg80211_scan_करोne(priv->scan_request, &info);
				priv->scan_request = शून्य;
				priv->scan_पातing = false;
			पूर्ण अन्यथा अणु
				priv->scan_पातing = false;
				mwअगरiex_dbg(adapter, INFO,
					    "info: scan already aborted\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Get scan command from scan_pending_q and put to
		 * cmd_pending_q
		 */
		cmd_node = list_first_entry(&adapter->scan_pending_q,
					    काष्ठा cmd_ctrl_node, list);
		list_del(&cmd_node->list);
		spin_unlock_bh(&adapter->scan_pending_q_lock);
		mwअगरiex_insert_cmd_to_pending_q(adapter, cmd_node);
	पूर्ण

	वापस;
पूर्ण

व्योम mwअगरiex_cancel_scan(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	पूर्णांक i;

	mwअगरiex_cancel_pending_scan_cmd(adapter);

	अगर (adapter->scan_processing) अणु
		spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
		adapter->scan_processing = false;
		spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);
		क्रम (i = 0; i < adapter->priv_num; i++) अणु
			priv = adapter->priv[i];
			अगर (!priv)
				जारी;
			अगर (priv->scan_request) अणु
				काष्ठा cfg80211_scan_info info = अणु
					.पातed = true,
				पूर्ण;

				mwअगरiex_dbg(adapter, INFO,
					    "info: aborting scan\n");
				cfg80211_scan_करोne(priv->scan_request, &info);
				priv->scan_request = शून्य;
				priv->scan_पातing = false;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function handles the command response of scan.
 *
 * The response buffer क्रम the scan command has the following
 * memory layout:
 *
 *      .-------------------------------------------------------------.
 *      |  Header (4 * माप(t_u16)):  Standard command response hdr |
 *      .-------------------------------------------------------------.
 *      |  BufSize (t_u16) : माप the BSS Description data          |
 *      .-------------------------------------------------------------.
 *      |  NumOfSet (t_u8) : Number of BSS Descs वापसed             |
 *      .-------------------------------------------------------------.
 *      |  BSSDescription data (variable, size given in BufSize)      |
 *      .-------------------------------------------------------------.
 *      |  TLV data (variable, size calculated using Header->Size,    |
 *      |            BufSize and माप the fixed fields above)       |
 *      .-------------------------------------------------------------.
 */
पूर्णांक mwअगरiex_ret_802_11_scan(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा host_cmd_ds_command *resp)
अणु
	पूर्णांक ret = 0;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11_scan_rsp *scan_rsp;
	काष्ठा mwअगरiex_ie_types_data *tlv_data;
	काष्ठा mwअगरiex_ie_types_tsf_बारtamp *tsf_tlv;
	u8 *bss_info;
	u32 scan_resp_size;
	u32 bytes_left;
	u32 idx;
	u32 tlv_buf_size;
	काष्ठा mwअगरiex_ie_types_chan_band_list_param_set *chan_band_tlv;
	काष्ठा chan_band_param_set *chan_band;
	u8 is_bgscan_resp;
	__le64 fw_tsf = 0;
	u8 *radio_type;
	काष्ठा cfg80211_wowlan_nd_match *pmatch;
	काष्ठा cfg80211_sched_scan_request *nd_config = शून्य;

	is_bgscan_resp = (le16_to_cpu(resp->command)
			  == HostCmd_CMD_802_11_BG_SCAN_QUERY);
	अगर (is_bgscan_resp)
		scan_rsp = &resp->params.bg_scan_query_resp.scan_resp;
	अन्यथा
		scan_rsp = &resp->params.scan_resp;


	अगर (scan_rsp->number_of_sets > MWIFIEX_MAX_AP) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "SCAN_RESP: too many AP returned (%d)\n",
			    scan_rsp->number_of_sets);
		ret = -1;
		जाओ check_next_scan;
	पूर्ण

	/* Check csa channel expiry beक्रमe parsing scan response */
	mwअगरiex_11h_get_csa_बंदd_channel(priv);

	bytes_left = le16_to_cpu(scan_rsp->bss_descript_size);
	mwअगरiex_dbg(adapter, INFO,
		    "info: SCAN_RESP: bss_descript_size %d\n",
		    bytes_left);

	scan_resp_size = le16_to_cpu(resp->size);

	mwअगरiex_dbg(adapter, INFO,
		    "info: SCAN_RESP: returned %d APs before parsing\n",
		    scan_rsp->number_of_sets);

	bss_info = scan_rsp->bss_desc_and_tlv_buffer;

	/*
	 * The size of the TLV buffer is equal to the entire command response
	 *   size (scan_resp_size) minus the fixed fields (माप()'s), the
	 *   BSS Descriptions (bss_descript_size as bytesLef) and the command
	 *   response header (S_DS_GEN)
	 */
	tlv_buf_size = scan_resp_size - (bytes_left
					 + माप(scan_rsp->bss_descript_size)
					 + माप(scan_rsp->number_of_sets)
					 + S_DS_GEN);

	tlv_data = (काष्ठा mwअगरiex_ie_types_data *) (scan_rsp->
						 bss_desc_and_tlv_buffer +
						 bytes_left);

	/* Search the TLV buffer space in the scan response क्रम any valid
	   TLVs */
	mwअगरiex_ret_802_11_scan_get_tlv_ptrs(adapter, tlv_data, tlv_buf_size,
					     TLV_TYPE_TSFTIMESTAMP,
					     (काष्ठा mwअगरiex_ie_types_data **)
					     &tsf_tlv);

	/* Search the TLV buffer space in the scan response क्रम any valid
	   TLVs */
	mwअगरiex_ret_802_11_scan_get_tlv_ptrs(adapter, tlv_data, tlv_buf_size,
					     TLV_TYPE_CHANNELBANDLIST,
					     (काष्ठा mwअगरiex_ie_types_data **)
					     &chan_band_tlv);

#अगर_घोषित CONFIG_PM
	अगर (priv->wdev.wiphy->wowlan_config)
		nd_config = priv->wdev.wiphy->wowlan_config->nd_config;
#पूर्ण_अगर

	अगर (nd_config) अणु
		adapter->nd_info =
			kzalloc(माप(काष्ठा cfg80211_wowlan_nd_match) +
				माप(काष्ठा cfg80211_wowlan_nd_match *) *
				scan_rsp->number_of_sets, GFP_ATOMIC);

		अगर (adapter->nd_info)
			adapter->nd_info->n_matches = scan_rsp->number_of_sets;
	पूर्ण

	क्रम (idx = 0; idx < scan_rsp->number_of_sets && bytes_left; idx++) अणु
		/*
		 * If the TSF TLV was appended to the scan results, save this
		 * entry's TSF value in the fw_tsf field. It is the firmware's
		 * TSF value at the समय the beacon or probe response was
		 * received.
		 */
		अगर (tsf_tlv)
			स_नकल(&fw_tsf, &tsf_tlv->tsf_data[idx * TSF_DATA_SIZE],
			       माप(fw_tsf));

		अगर (chan_band_tlv) अणु
			chan_band = &chan_band_tlv->chan_band_param[idx];
			radio_type = &chan_band->radio_type;
		पूर्ण अन्यथा अणु
			radio_type = शून्य;
		पूर्ण

		अगर (chan_band_tlv && adapter->nd_info) अणु
			adapter->nd_info->matches[idx] =
				kzalloc(माप(*pmatch) + माप(u32),
					GFP_ATOMIC);

			pmatch = adapter->nd_info->matches[idx];

			अगर (pmatch) अणु
				pmatch->n_channels = 1;
				pmatch->channels[0] = chan_band->chan_number;
			पूर्ण
		पूर्ण

		ret = mwअगरiex_parse_single_response_buf(priv, &bss_info,
							&bytes_left,
							le64_to_cpu(fw_tsf),
							radio_type, false, 0);
		अगर (ret)
			जाओ check_next_scan;
	पूर्ण

check_next_scan:
	mwअगरiex_check_next_scan_command(priv);
	वापस ret;
पूर्ण

/*
 * This function prepares an extended scan command to be sent to the firmware
 *
 * This uses the scan command configuration sent to the command processing
 * module in command preparation stage to configure a extended scan command
 * काष्ठाure to send to firmware.
 */
पूर्णांक mwअगरiex_cmd_802_11_scan_ext(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *cmd,
				व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_802_11_scan_ext *ext_scan = &cmd->params.ext_scan;
	काष्ठा mwअगरiex_scan_cmd_config *scan_cfg = data_buf;

	स_नकल(ext_scan->tlv_buffer, scan_cfg->tlv_buf, scan_cfg->tlv_buf_len);

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_SCAN_EXT);

	/* Size is equal to the माप(fixed portions) + the TLV len + header */
	cmd->size = cpu_to_le16((u16)(माप(ext_scan->reserved)
				      + scan_cfg->tlv_buf_len + S_DS_GEN));

	वापस 0;
पूर्ण

/* This function prepares an background scan config command to be sent
 * to the firmware
 */
पूर्णांक mwअगरiex_cmd_802_11_bg_scan_config(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा host_cmd_ds_command *cmd,
				      व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_802_11_bg_scan_config *bgscan_config =
					&cmd->params.bg_scan_config;
	काष्ठा mwअगरiex_bg_scan_cfg *bgscan_cfg_in = data_buf;
	u8 *tlv_pos = bgscan_config->tlv;
	u8 num_probes;
	u32 ssid_len, chan_idx, scan_type, scan_dur, chan_num;
	पूर्णांक i;
	काष्ठा mwअगरiex_ie_types_num_probes *num_probes_tlv;
	काष्ठा mwअगरiex_ie_types_repeat_count *repeat_count_tlv;
	काष्ठा mwअगरiex_ie_types_min_rssi_threshold *rssi_threshold_tlv;
	काष्ठा mwअगरiex_ie_types_bgscan_start_later *start_later_tlv;
	काष्ठा mwअगरiex_ie_types_wildcard_ssid_params *wildcard_ssid_tlv;
	काष्ठा mwअगरiex_ie_types_chan_list_param_set *chan_list_tlv;
	काष्ठा mwअगरiex_chan_scan_param_set *temp_chan;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_BG_SCAN_CONFIG);
	cmd->size = cpu_to_le16(माप(*bgscan_config) + S_DS_GEN);

	bgscan_config->action = cpu_to_le16(bgscan_cfg_in->action);
	bgscan_config->enable = bgscan_cfg_in->enable;
	bgscan_config->bss_type = bgscan_cfg_in->bss_type;
	bgscan_config->scan_पूर्णांकerval =
		cpu_to_le32(bgscan_cfg_in->scan_पूर्णांकerval);
	bgscan_config->report_condition =
		cpu_to_le32(bgscan_cfg_in->report_condition);

	/*  stop sched scan  */
	अगर (!bgscan_config->enable)
		वापस 0;

	bgscan_config->chan_per_scan = bgscan_cfg_in->chan_per_scan;

	num_probes = (bgscan_cfg_in->num_probes ? bgscan_cfg_in->
		      num_probes : priv->adapter->scan_probes);

	अगर (num_probes) अणु
		num_probes_tlv = (काष्ठा mwअगरiex_ie_types_num_probes *)tlv_pos;
		num_probes_tlv->header.type = cpu_to_le16(TLV_TYPE_NUMPROBES);
		num_probes_tlv->header.len =
			cpu_to_le16(माप(num_probes_tlv->num_probes));
		num_probes_tlv->num_probes = cpu_to_le16((u16)num_probes);

		tlv_pos += माप(num_probes_tlv->header) +
			le16_to_cpu(num_probes_tlv->header.len);
	पूर्ण

	अगर (bgscan_cfg_in->repeat_count) अणु
		repeat_count_tlv =
			(काष्ठा mwअगरiex_ie_types_repeat_count *)tlv_pos;
		repeat_count_tlv->header.type =
			cpu_to_le16(TLV_TYPE_REPEAT_COUNT);
		repeat_count_tlv->header.len =
			cpu_to_le16(माप(repeat_count_tlv->repeat_count));
		repeat_count_tlv->repeat_count =
			cpu_to_le16(bgscan_cfg_in->repeat_count);

		tlv_pos += माप(repeat_count_tlv->header) +
			le16_to_cpu(repeat_count_tlv->header.len);
	पूर्ण

	अगर (bgscan_cfg_in->rssi_threshold) अणु
		rssi_threshold_tlv =
			(काष्ठा mwअगरiex_ie_types_min_rssi_threshold *)tlv_pos;
		rssi_threshold_tlv->header.type =
			cpu_to_le16(TLV_TYPE_RSSI_LOW);
		rssi_threshold_tlv->header.len =
			cpu_to_le16(माप(rssi_threshold_tlv->rssi_threshold));
		rssi_threshold_tlv->rssi_threshold =
			cpu_to_le16(bgscan_cfg_in->rssi_threshold);

		tlv_pos += माप(rssi_threshold_tlv->header) +
			le16_to_cpu(rssi_threshold_tlv->header.len);
	पूर्ण

	क्रम (i = 0; i < bgscan_cfg_in->num_ssids; i++) अणु
		ssid_len = bgscan_cfg_in->ssid_list[i].ssid.ssid_len;

		wildcard_ssid_tlv =
			(काष्ठा mwअगरiex_ie_types_wildcard_ssid_params *)tlv_pos;
		wildcard_ssid_tlv->header.type =
				cpu_to_le16(TLV_TYPE_WILDCARDSSID);
		wildcard_ssid_tlv->header.len = cpu_to_le16(
				(u16)(ssid_len + माप(wildcard_ssid_tlv->
							 max_ssid_length)));

		/* max_ssid_length = 0 tells firmware to perक्रमm
		 * specअगरic scan क्रम the SSID filled, whereas
		 * max_ssid_length = IEEE80211_MAX_SSID_LEN is क्रम
		 * wildcard scan.
		 */
		अगर (ssid_len)
			wildcard_ssid_tlv->max_ssid_length = 0;
		अन्यथा
			wildcard_ssid_tlv->max_ssid_length =
						IEEE80211_MAX_SSID_LEN;

		स_नकल(wildcard_ssid_tlv->ssid,
		       bgscan_cfg_in->ssid_list[i].ssid.ssid, ssid_len);

		tlv_pos += (माप(wildcard_ssid_tlv->header)
				+ le16_to_cpu(wildcard_ssid_tlv->header.len));
	पूर्ण

	chan_list_tlv = (काष्ठा mwअगरiex_ie_types_chan_list_param_set *)tlv_pos;

	अगर (bgscan_cfg_in->chan_list[0].chan_number) अणु
		dev_dbg(priv->adapter->dev, "info: bgscan: Using supplied channel list\n");

		chan_list_tlv->header.type = cpu_to_le16(TLV_TYPE_CHANLIST);

		क्रम (chan_idx = 0;
		     chan_idx < MWIFIEX_BG_SCAN_CHAN_MAX &&
		     bgscan_cfg_in->chan_list[chan_idx].chan_number;
		     chan_idx++) अणु
			temp_chan = chan_list_tlv->chan_scan_param + chan_idx;

			/* Increment the TLV header length by size appended */
			le16_unaligned_add_cpu(&chan_list_tlv->header.len,
					       माप(
					       chan_list_tlv->chan_scan_param));

			temp_chan->chan_number =
				bgscan_cfg_in->chan_list[chan_idx].chan_number;
			temp_chan->radio_type =
				bgscan_cfg_in->chan_list[chan_idx].radio_type;

			scan_type =
				bgscan_cfg_in->chan_list[chan_idx].scan_type;

			अगर (scan_type == MWIFIEX_SCAN_TYPE_PASSIVE)
				temp_chan->chan_scan_mode_biपंचांगap
					|= MWIFIEX_PASSIVE_SCAN;
			अन्यथा
				temp_chan->chan_scan_mode_biपंचांगap
					&= ~MWIFIEX_PASSIVE_SCAN;

			अगर (bgscan_cfg_in->chan_list[chan_idx].scan_समय) अणु
				scan_dur = (u16)bgscan_cfg_in->
					chan_list[chan_idx].scan_समय;
			पूर्ण अन्यथा अणु
				scan_dur = (scan_type ==
					    MWIFIEX_SCAN_TYPE_PASSIVE) ?
					    priv->adapter->passive_scan_समय :
					    priv->adapter->specअगरic_scan_समय;
			पूर्ण

			temp_chan->min_scan_समय = cpu_to_le16(scan_dur);
			temp_chan->max_scan_समय = cpu_to_le16(scan_dur);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(priv->adapter->dev,
			"info: bgscan: Creating full region channel list\n");
		chan_num =
			mwअगरiex_bgscan_create_channel_list(priv, bgscan_cfg_in,
							   chan_list_tlv->
							   chan_scan_param);
		le16_unaligned_add_cpu(&chan_list_tlv->header.len,
				       chan_num *
			     माप(chan_list_tlv->chan_scan_param[0]));
	पूर्ण

	tlv_pos += (माप(chan_list_tlv->header)
			+ le16_to_cpu(chan_list_tlv->header.len));

	अगर (bgscan_cfg_in->start_later) अणु
		start_later_tlv =
			(काष्ठा mwअगरiex_ie_types_bgscan_start_later *)tlv_pos;
		start_later_tlv->header.type =
			cpu_to_le16(TLV_TYPE_BGSCAN_START_LATER);
		start_later_tlv->header.len =
			cpu_to_le16(माप(start_later_tlv->start_later));
		start_later_tlv->start_later =
			cpu_to_le16(bgscan_cfg_in->start_later);

		tlv_pos += माप(start_later_tlv->header) +
			le16_to_cpu(start_later_tlv->header.len);
	पूर्ण

	/* Append venकरोr specअगरic IE TLV */
	mwअगरiex_cmd_append_vsie_tlv(priv, MWIFIEX_VSIE_MASK_BGSCAN, &tlv_pos);

	le16_unaligned_add_cpu(&cmd->size, tlv_pos - bgscan_config->tlv);

	वापस 0;
पूर्ण

पूर्णांक mwअगरiex_stop_bg_scan(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_bg_scan_cfg *bgscan_cfg;

	अगर (!priv->sched_scanning) अणु
		dev_dbg(priv->adapter->dev, "bgscan already stopped!\n");
		वापस 0;
	पूर्ण

	bgscan_cfg = kzalloc(माप(*bgscan_cfg), GFP_KERNEL);
	अगर (!bgscan_cfg)
		वापस -ENOMEM;

	bgscan_cfg->bss_type = MWIFIEX_BSS_MODE_INFRA;
	bgscan_cfg->action = MWIFIEX_BGSCAN_ACT_SET;
	bgscan_cfg->enable = false;

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_BG_SCAN_CONFIG,
			     HostCmd_ACT_GEN_SET, 0, bgscan_cfg, true)) अणु
		kमुक्त(bgscan_cfg);
		वापस -EFAULT;
	पूर्ण

	kमुक्त(bgscan_cfg);
	priv->sched_scanning = false;

	वापस 0;
पूर्ण

अटल व्योम
mwअगरiex_update_chan_statistics(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा mwअगरiex_ietypes_chanstats *tlv_stat)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u8 i, num_chan;
	काष्ठा mwअगरiex_fw_chan_stats *fw_chan_stats;
	काष्ठा mwअगरiex_chan_stats chan_stats;

	fw_chan_stats = (व्योम *)((u8 *)tlv_stat +
			      माप(काष्ठा mwअगरiex_ie_types_header));
	num_chan = le16_to_cpu(tlv_stat->header.len) /
					      माप(काष्ठा mwअगरiex_chan_stats);

	क्रम (i = 0 ; i < num_chan; i++) अणु
		अगर (adapter->survey_idx >= adapter->num_in_chan_stats) अणु
			mwअगरiex_dbg(adapter, WARN,
				    "FW reported too many channel results (max %d)\n",
				    adapter->num_in_chan_stats);
			वापस;
		पूर्ण
		chan_stats.chan_num = fw_chan_stats->chan_num;
		chan_stats.bandcfg = fw_chan_stats->bandcfg;
		chan_stats.flags = fw_chan_stats->flags;
		chan_stats.noise = fw_chan_stats->noise;
		chan_stats.total_bss = le16_to_cpu(fw_chan_stats->total_bss);
		chan_stats.cca_scan_dur =
				       le16_to_cpu(fw_chan_stats->cca_scan_dur);
		chan_stats.cca_busy_dur =
				       le16_to_cpu(fw_chan_stats->cca_busy_dur);
		mwअगरiex_dbg(adapter, INFO,
			    "chan=%d, noise=%d, total_network=%d scan_duration=%d, busy_duration=%d\n",
			    chan_stats.chan_num,
			    chan_stats.noise,
			    chan_stats.total_bss,
			    chan_stats.cca_scan_dur,
			    chan_stats.cca_busy_dur);
		स_नकल(&adapter->chan_stats[adapter->survey_idx++], &chan_stats,
		       माप(काष्ठा mwअगरiex_chan_stats));
		fw_chan_stats++;
	पूर्ण
पूर्ण

/* This function handles the command response of extended scan */
पूर्णांक mwअगरiex_ret_802_11_scan_ext(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11_scan_ext *ext_scan_resp;
	काष्ठा mwअगरiex_ie_types_header *tlv;
	काष्ठा mwअगरiex_ietypes_chanstats *tlv_stat;
	u16 buf_left, type, len;

	काष्ठा host_cmd_ds_command *cmd_ptr;
	काष्ठा cmd_ctrl_node *cmd_node;
	bool complete_scan = false;

	mwअगरiex_dbg(adapter, INFO, "info: EXT scan returns successfully\n");

	ext_scan_resp = &resp->params.ext_scan;

	tlv = (व्योम *)ext_scan_resp->tlv_buffer;
	buf_left = le16_to_cpu(resp->size) - (माप(*ext_scan_resp) + S_DS_GEN
					      - 1);

	जबतक (buf_left >= माप(काष्ठा mwअगरiex_ie_types_header)) अणु
		type = le16_to_cpu(tlv->type);
		len = le16_to_cpu(tlv->len);

		अगर (buf_left < (माप(काष्ठा mwअगरiex_ie_types_header) + len)) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "error processing scan response TLVs");
			अवरोध;
		पूर्ण

		चयन (type) अणु
		हाल TLV_TYPE_CHANNEL_STATS:
			tlv_stat = (व्योम *)tlv;
			mwअगरiex_update_chan_statistics(priv, tlv_stat);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		buf_left -= len + माप(काष्ठा mwअगरiex_ie_types_header);
		tlv = (व्योम *)((u8 *)tlv + len +
			       माप(काष्ठा mwअगरiex_ie_types_header));
	पूर्ण

	spin_lock_bh(&adapter->cmd_pending_q_lock);
	spin_lock_bh(&adapter->scan_pending_q_lock);
	अगर (list_empty(&adapter->scan_pending_q)) अणु
		complete_scan = true;
		list_क्रम_each_entry(cmd_node, &adapter->cmd_pending_q, list) अणु
			cmd_ptr = (व्योम *)cmd_node->cmd_skb->data;
			अगर (le16_to_cpu(cmd_ptr->command) ==
			    HostCmd_CMD_802_11_SCAN_EXT) अणु
				mwअगरiex_dbg(adapter, INFO,
					    "Scan pending in command pending list");
				complete_scan = false;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&adapter->scan_pending_q_lock);
	spin_unlock_bh(&adapter->cmd_pending_q_lock);

	अगर (complete_scan)
		mwअगरiex_complete_scan(priv);

	वापस 0;
पूर्ण

/* This function This function handles the event extended scan report. It
 * parses extended scan results and inक्रमms to cfg80211 stack.
 */
पूर्णांक mwअगरiex_handle_event_ext_scan_report(काष्ठा mwअगरiex_निजी *priv,
					 व्योम *buf)
अणु
	पूर्णांक ret = 0;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u8 *bss_info;
	u32 bytes_left, bytes_left_क्रम_tlv, idx;
	u16 type, len;
	काष्ठा mwअगरiex_ie_types_data *tlv;
	काष्ठा mwअगरiex_ie_types_bss_scan_rsp *scan_rsp_tlv;
	काष्ठा mwअगरiex_ie_types_bss_scan_info *scan_info_tlv;
	u8 *radio_type;
	u64 fw_tsf = 0;
	s32 rssi = 0;
	काष्ठा mwअगरiex_event_scan_result *event_scan = buf;
	u8 num_of_set = event_scan->num_of_set;
	u8 *scan_resp = buf + माप(काष्ठा mwअगरiex_event_scan_result);
	u16 scan_resp_size = le16_to_cpu(event_scan->buf_size);

	अगर (num_of_set > MWIFIEX_MAX_AP) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "EXT_SCAN: Invalid number of AP returned (%d)!!\n",
			    num_of_set);
		ret = -1;
		जाओ check_next_scan;
	पूर्ण

	bytes_left = scan_resp_size;
	mwअगरiex_dbg(adapter, INFO,
		    "EXT_SCAN: size %d, returned %d APs...",
		    scan_resp_size, num_of_set);
	mwअगरiex_dbg_dump(adapter, CMD_D, "EXT_SCAN buffer:", buf,
			 scan_resp_size +
			 माप(काष्ठा mwअगरiex_event_scan_result));

	tlv = (काष्ठा mwअगरiex_ie_types_data *)scan_resp;

	क्रम (idx = 0; idx < num_of_set && bytes_left; idx++) अणु
		type = le16_to_cpu(tlv->header.type);
		len = le16_to_cpu(tlv->header.len);
		अगर (bytes_left < माप(काष्ठा mwअगरiex_ie_types_header) + len) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "EXT_SCAN: Error bytes left < TLV length\n");
			अवरोध;
		पूर्ण
		scan_rsp_tlv = शून्य;
		scan_info_tlv = शून्य;
		bytes_left_क्रम_tlv = bytes_left;

		/* BSS response TLV with beacon or probe response buffer
		 * at the initial position of each descriptor
		 */
		अगर (type != TLV_TYPE_BSS_SCAN_RSP)
			अवरोध;

		bss_info = (u8 *)tlv;
		scan_rsp_tlv = (काष्ठा mwअगरiex_ie_types_bss_scan_rsp *)tlv;
		tlv = (काष्ठा mwअगरiex_ie_types_data *)(tlv->data + len);
		bytes_left_क्रम_tlv -=
				(len + माप(काष्ठा mwअगरiex_ie_types_header));

		जबतक (bytes_left_क्रम_tlv >=
		       माप(काष्ठा mwअगरiex_ie_types_header) &&
		       le16_to_cpu(tlv->header.type) != TLV_TYPE_BSS_SCAN_RSP) अणु
			type = le16_to_cpu(tlv->header.type);
			len = le16_to_cpu(tlv->header.len);
			अगर (bytes_left_क्रम_tlv <
			    माप(काष्ठा mwअगरiex_ie_types_header) + len) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "EXT_SCAN: Error in processing TLV,\t"
					    "bytes left < TLV length\n");
				scan_rsp_tlv = शून्य;
				bytes_left_क्रम_tlv = 0;
				जारी;
			पूर्ण
			चयन (type) अणु
			हाल TLV_TYPE_BSS_SCAN_INFO:
				scan_info_tlv =
				  (काष्ठा mwअगरiex_ie_types_bss_scan_info *)tlv;
				अगर (len !=
				 माप(काष्ठा mwअगरiex_ie_types_bss_scan_info) -
				 माप(काष्ठा mwअगरiex_ie_types_header)) अणु
					bytes_left_क्रम_tlv = 0;
					जारी;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			tlv = (काष्ठा mwअगरiex_ie_types_data *)(tlv->data + len);
			bytes_left -=
				(len + माप(काष्ठा mwअगरiex_ie_types_header));
			bytes_left_क्रम_tlv -=
				(len + माप(काष्ठा mwअगरiex_ie_types_header));
		पूर्ण

		अगर (!scan_rsp_tlv)
			अवरोध;

		/* Advance poपूर्णांकer to the beacon buffer length and
		 * update the bytes count so that the function
		 * wlan_पूर्णांकerpret_bss_desc_with_ie() can handle the
		 * scan buffer withut any change
		 */
		bss_info += माप(u16);
		bytes_left -= माप(u16);

		अगर (scan_info_tlv) अणु
			rssi = (s32)(s16)(le16_to_cpu(scan_info_tlv->rssi));
			rssi *= 100;           /* Convert dBm to mBm */
			mwअगरiex_dbg(adapter, INFO,
				    "info: InterpretIE: RSSI=%d\n", rssi);
			fw_tsf = le64_to_cpu(scan_info_tlv->tsf);
			radio_type = &scan_info_tlv->radio_type;
		पूर्ण अन्यथा अणु
			radio_type = शून्य;
		पूर्ण
		ret = mwअगरiex_parse_single_response_buf(priv, &bss_info,
							&bytes_left, fw_tsf,
							radio_type, true, rssi);
		अगर (ret)
			जाओ check_next_scan;
	पूर्ण

check_next_scan:
	अगर (!event_scan->more_event)
		mwअगरiex_check_next_scan_command(priv);

	वापस ret;
पूर्ण

/*
 * This function prepares command क्रम background scan query.
 *
 * Preparation includes -
 *      - Setting command ID and proper size
 *      - Setting background scan flush parameter
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_802_11_bg_scan_query(काष्ठा host_cmd_ds_command *cmd)
अणु
	काष्ठा host_cmd_ds_802_11_bg_scan_query *bg_query =
		&cmd->params.bg_scan_query;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_BG_SCAN_QUERY);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_802_11_bg_scan_query)
				+ S_DS_GEN);

	bg_query->flush = 1;

	वापस 0;
पूर्ण

/*
 * This function inserts scan command node to the scan pending queue.
 */
व्योम
mwअगरiex_queue_scan_cmd(काष्ठा mwअगरiex_निजी *priv,
		       काष्ठा cmd_ctrl_node *cmd_node)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	cmd_node->रुको_q_enabled = true;
	cmd_node->condition = &adapter->scan_रुको_q_woken;
	spin_lock_bh(&adapter->scan_pending_q_lock);
	list_add_tail(&cmd_node->list, &adapter->scan_pending_q);
	spin_unlock_bh(&adapter->scan_pending_q_lock);
पूर्ण

/*
 * This function sends a scan command क्रम all available channels to the
 * firmware, filtered on a specअगरic SSID.
 */
अटल पूर्णांक mwअगरiex_scan_specअगरic_ssid(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा cfg80211_ssid *req_ssid)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret;
	काष्ठा mwअगरiex_user_scan_cfg *scan_cfg;

	अगर (adapter->scan_processing) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "cmd: Scan already in process...\n");
		वापस -EBUSY;
	पूर्ण

	अगर (priv->scan_block) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "cmd: Scan is blocked during association...\n");
		वापस -EBUSY;
	पूर्ण

	scan_cfg = kzalloc(माप(काष्ठा mwअगरiex_user_scan_cfg), GFP_KERNEL);
	अगर (!scan_cfg)
		वापस -ENOMEM;

	scan_cfg->ssid_list = req_ssid;
	scan_cfg->num_ssids = 1;

	ret = mwअगरiex_scan_networks(priv, scan_cfg);

	kमुक्त(scan_cfg);
	वापस ret;
पूर्ण

/*
 * Sends IOCTL request to start a scan.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 *
 * Scan command can be issued क्रम both normal scan and specअगरic SSID
 * scan, depending upon whether an SSID is provided or not.
 */
पूर्णांक mwअगरiex_request_scan(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा cfg80211_ssid *req_ssid)
अणु
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&priv->async_mutex)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: acquire semaphore fail\n",
			    __func__);
		वापस -1;
	पूर्ण

	priv->adapter->scan_रुको_q_woken = false;

	अगर (req_ssid && req_ssid->ssid_len != 0)
		/* Specअगरic SSID scan */
		ret = mwअगरiex_scan_specअगरic_ssid(priv, req_ssid);
	अन्यथा
		/* Normal scan */
		ret = mwअगरiex_scan_networks(priv, शून्य);

	mutex_unlock(&priv->async_mutex);

	वापस ret;
पूर्ण

/*
 * This function appends the venकरोr specअगरic IE TLV to a buffer.
 */
पूर्णांक
mwअगरiex_cmd_append_vsie_tlv(काष्ठा mwअगरiex_निजी *priv,
			    u16 vsie_mask, u8 **buffer)
अणु
	पूर्णांक id, ret_len = 0;
	काष्ठा mwअगरiex_ie_types_venकरोr_param_set *vs_param_set;

	अगर (!buffer)
		वापस 0;
	अगर (!(*buffer))
		वापस 0;

	/*
	 * Traverse through the saved venकरोr specअगरic IE array and append
	 * the selected(scan/assoc/adhoc) IE as TLV to the command
	 */
	क्रम (id = 0; id < MWIFIEX_MAX_VSIE_NUM; id++) अणु
		अगर (priv->vs_ie[id].mask & vsie_mask) अणु
			vs_param_set =
				(काष्ठा mwअगरiex_ie_types_venकरोr_param_set *)
				*buffer;
			vs_param_set->header.type =
				cpu_to_le16(TLV_TYPE_PASSTHROUGH);
			vs_param_set->header.len =
				cpu_to_le16((((u16) priv->vs_ie[id].ie[1])
				& 0x00FF) + 2);
			अगर (le16_to_cpu(vs_param_set->header.len) >
				MWIFIEX_MAX_VSIE_LEN) अणु
				mwअगरiex_dbg(priv->adapter, ERROR,
					    "Invalid param length!\n");
				अवरोध;
			पूर्ण

			स_नकल(vs_param_set->ie, priv->vs_ie[id].ie,
			       le16_to_cpu(vs_param_set->header.len));
			*buffer += le16_to_cpu(vs_param_set->header.len) +
				   माप(काष्ठा mwअगरiex_ie_types_header);
			ret_len += le16_to_cpu(vs_param_set->header.len) +
				   माप(काष्ठा mwअगरiex_ie_types_header);
		पूर्ण
	पूर्ण
	वापस ret_len;
पूर्ण

/*
 * This function saves a beacon buffer of the current BSS descriptor.
 *
 * The current beacon buffer is saved so that it can be restored in the
 * following हालs that makes the beacon buffer not to contain the current
 * ssid's beacon buffer.
 *      - The current ssid was not found somehow in the last scan.
 *      - The current ssid was the last entry of the scan table and overloaded.
 */
व्योम
mwअगरiex_save_curr_bcn(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_bssdescriptor *curr_bss =
		&priv->curr_bss_params.bss_descriptor;

	अगर (!curr_bss->beacon_buf_size)
		वापस;

	/* allocate beacon buffer at 1st समय; or अगर it's size has changed */
	अगर (!priv->curr_bcn_buf ||
	    priv->curr_bcn_size != curr_bss->beacon_buf_size) अणु
		priv->curr_bcn_size = curr_bss->beacon_buf_size;

		kमुक्त(priv->curr_bcn_buf);
		priv->curr_bcn_buf = kदो_स्मृति(curr_bss->beacon_buf_size,
					     GFP_ATOMIC);
		अगर (!priv->curr_bcn_buf)
			वापस;
	पूर्ण

	स_नकल(priv->curr_bcn_buf, curr_bss->beacon_buf,
	       curr_bss->beacon_buf_size);
	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: current beacon saved %d\n",
		    priv->curr_bcn_size);

	curr_bss->beacon_buf = priv->curr_bcn_buf;

	/* adjust the poपूर्णांकers in the current BSS descriptor */
	अगर (curr_bss->bcn_wpa_ie)
		curr_bss->bcn_wpa_ie =
			(काष्ठा ieee_types_venकरोr_specअगरic *)
			(curr_bss->beacon_buf +
			 curr_bss->wpa_offset);

	अगर (curr_bss->bcn_rsn_ie)
		curr_bss->bcn_rsn_ie = (काष्ठा ieee_types_generic *)
			(curr_bss->beacon_buf +
			 curr_bss->rsn_offset);

	अगर (curr_bss->bcn_ht_cap)
		curr_bss->bcn_ht_cap = (काष्ठा ieee80211_ht_cap *)
			(curr_bss->beacon_buf +
			 curr_bss->ht_cap_offset);

	अगर (curr_bss->bcn_ht_oper)
		curr_bss->bcn_ht_oper = (काष्ठा ieee80211_ht_operation *)
			(curr_bss->beacon_buf +
			 curr_bss->ht_info_offset);

	अगर (curr_bss->bcn_vht_cap)
		curr_bss->bcn_vht_cap = (व्योम *)(curr_bss->beacon_buf +
						 curr_bss->vht_cap_offset);

	अगर (curr_bss->bcn_vht_oper)
		curr_bss->bcn_vht_oper = (व्योम *)(curr_bss->beacon_buf +
						  curr_bss->vht_info_offset);

	अगर (curr_bss->bcn_bss_co_2040)
		curr_bss->bcn_bss_co_2040 =
			(curr_bss->beacon_buf + curr_bss->bss_co_2040_offset);

	अगर (curr_bss->bcn_ext_cap)
		curr_bss->bcn_ext_cap = curr_bss->beacon_buf +
			curr_bss->ext_cap_offset;

	अगर (curr_bss->oper_mode)
		curr_bss->oper_mode = (व्योम *)(curr_bss->beacon_buf +
					       curr_bss->oper_mode_offset);
पूर्ण

/*
 * This function मुक्तs the current BSS descriptor beacon buffer.
 */
व्योम
mwअगरiex_मुक्त_curr_bcn(काष्ठा mwअगरiex_निजी *priv)
अणु
	kमुक्त(priv->curr_bcn_buf);
	priv->curr_bcn_buf = शून्य;
पूर्ण
