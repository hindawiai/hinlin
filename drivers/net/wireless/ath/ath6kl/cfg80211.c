<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "core.h"
#समावेश "cfg80211.h"
#समावेश "debug.h"
#समावेश "hif-ops.h"
#समावेश "testmode.h"

#घोषणा RATETAB_ENT(_rate, _rateid, _flags) अणु   \
	.bitrate    = (_rate),                  \
	.flags      = (_flags),                 \
	.hw_value   = (_rateid),                \
पूर्ण

#घोषणा CHAN2G(_channel, _freq, _flags) अणु   \
	.band           = NL80211_BAND_2GHZ,  \
	.hw_value       = (_channel),           \
	.center_freq    = (_freq),              \
	.flags          = (_flags),             \
	.max_antenna_gain   = 0,                \
	.max_घातer      = 30,                   \
पूर्ण

#घोषणा CHAN5G(_channel, _flags) अणु		    \
	.band           = NL80211_BAND_5GHZ,      \
	.hw_value       = (_channel),               \
	.center_freq    = 5000 + (5 * (_channel)),  \
	.flags          = (_flags),                 \
	.max_antenna_gain   = 0,                    \
	.max_घातer      = 30,                       \
पूर्ण

#घोषणा DEFAULT_BG_SCAN_PERIOD 60

काष्ठा ath6kl_cfg80211_match_probe_ssid अणु
	काष्ठा cfg80211_ssid ssid;
	u8 flag;
पूर्ण;

अटल काष्ठा ieee80211_rate ath6kl_rates[] = अणु
	RATETAB_ENT(10, 0x1, 0),
	RATETAB_ENT(20, 0x2, 0),
	RATETAB_ENT(55, 0x4, 0),
	RATETAB_ENT(110, 0x8, 0),
	RATETAB_ENT(60, 0x10, 0),
	RATETAB_ENT(90, 0x20, 0),
	RATETAB_ENT(120, 0x40, 0),
	RATETAB_ENT(180, 0x80, 0),
	RATETAB_ENT(240, 0x100, 0),
	RATETAB_ENT(360, 0x200, 0),
	RATETAB_ENT(480, 0x400, 0),
	RATETAB_ENT(540, 0x800, 0),
पूर्ण;

#घोषणा ath6kl_a_rates     (ath6kl_rates + 4)
#घोषणा ath6kl_a_rates_size    8
#घोषणा ath6kl_g_rates     (ath6kl_rates + 0)
#घोषणा ath6kl_g_rates_size    12

#घोषणा ath6kl_g_htcap IEEE80211_HT_CAP_SGI_20
#घोषणा ath6kl_a_htcap (IEEE80211_HT_CAP_SUP_WIDTH_20_40 | \
			IEEE80211_HT_CAP_SGI_20		 | \
			IEEE80211_HT_CAP_SGI_40)

अटल काष्ठा ieee80211_channel ath6kl_2ghz_channels[] = अणु
	CHAN2G(1, 2412, 0),
	CHAN2G(2, 2417, 0),
	CHAN2G(3, 2422, 0),
	CHAN2G(4, 2427, 0),
	CHAN2G(5, 2432, 0),
	CHAN2G(6, 2437, 0),
	CHAN2G(7, 2442, 0),
	CHAN2G(8, 2447, 0),
	CHAN2G(9, 2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
पूर्ण;

अटल काष्ठा ieee80211_channel ath6kl_5ghz_a_channels[] = अणु
	CHAN5G(36, 0), CHAN5G(40, 0),
	CHAN5G(44, 0), CHAN5G(48, 0),
	CHAN5G(52, 0), CHAN5G(56, 0),
	CHAN5G(60, 0), CHAN5G(64, 0),
	CHAN5G(100, 0), CHAN5G(104, 0),
	CHAN5G(108, 0), CHAN5G(112, 0),
	CHAN5G(116, 0), CHAN5G(120, 0),
	CHAN5G(124, 0), CHAN5G(128, 0),
	CHAN5G(132, 0), CHAN5G(136, 0),
	CHAN5G(140, 0), CHAN5G(149, 0),
	CHAN5G(153, 0), CHAN5G(157, 0),
	CHAN5G(161, 0), CHAN5G(165, 0),
	CHAN5G(184, 0), CHAN5G(188, 0),
	CHAN5G(192, 0), CHAN5G(196, 0),
	CHAN5G(200, 0), CHAN5G(204, 0),
	CHAN5G(208, 0), CHAN5G(212, 0),
	CHAN5G(216, 0),
पूर्ण;

अटल काष्ठा ieee80211_supported_band ath6kl_band_2ghz = अणु
	.n_channels = ARRAY_SIZE(ath6kl_2ghz_channels),
	.channels = ath6kl_2ghz_channels,
	.n_bitrates = ath6kl_g_rates_size,
	.bitrates = ath6kl_g_rates,
	.ht_cap.cap = ath6kl_g_htcap,
	.ht_cap.ht_supported = true,
पूर्ण;

अटल काष्ठा ieee80211_supported_band ath6kl_band_5ghz = अणु
	.n_channels = ARRAY_SIZE(ath6kl_5ghz_a_channels),
	.channels = ath6kl_5ghz_a_channels,
	.n_bitrates = ath6kl_a_rates_size,
	.bitrates = ath6kl_a_rates,
	.ht_cap.cap = ath6kl_a_htcap,
	.ht_cap.ht_supported = true,
पूर्ण;

#घोषणा CCKM_KRK_CIPHER_SUITE 0x004096ff /* use क्रम KRK */

/* वापसs true अगर scheduled scan was stopped */
अटल bool __ath6kl_cfg80211_sscan_stop(काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;

	अगर (!test_and_clear_bit(SCHED_SCANNING, &vअगर->flags))
		वापस false;

	del_समयr_sync(&vअगर->sched_scan_समयr);

	अगर (ar->state == ATH6KL_STATE_RECOVERY)
		वापस true;

	ath6kl_wmi_enable_sched_scan_cmd(ar->wmi, vअगर->fw_vअगर_idx, false);

	वापस true;
पूर्ण

अटल व्योम ath6kl_cfg80211_sscan_disable(काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	bool stopped;

	stopped = __ath6kl_cfg80211_sscan_stop(vअगर);

	अगर (!stopped)
		वापस;

	cfg80211_sched_scan_stopped(ar->wiphy, 0);
पूर्ण

अटल पूर्णांक ath6kl_set_wpa_version(काष्ठा ath6kl_vअगर *vअगर,
				  क्रमागत nl80211_wpa_versions wpa_version)
अणु
	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: %u\n", __func__, wpa_version);

	अगर (!wpa_version) अणु
		vअगर->auth_mode = NONE_AUTH;
	पूर्ण अन्यथा अगर (wpa_version & NL80211_WPA_VERSION_2) अणु
		vअगर->auth_mode = WPA2_AUTH;
	पूर्ण अन्यथा अगर (wpa_version & NL80211_WPA_VERSION_1) अणु
		vअगर->auth_mode = WPA_AUTH;
	पूर्ण अन्यथा अणु
		ath6kl_err("%s: %u not supported\n", __func__, wpa_version);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_set_auth_type(काष्ठा ath6kl_vअगर *vअगर,
				क्रमागत nl80211_auth_type auth_type)
अणु
	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: 0x%x\n", __func__, auth_type);

	चयन (auth_type) अणु
	हाल NL80211_AUTHTYPE_OPEN_SYSTEM:
		vअगर->करोt11_auth_mode = OPEN_AUTH;
		अवरोध;
	हाल NL80211_AUTHTYPE_SHARED_KEY:
		vअगर->करोt11_auth_mode = SHARED_AUTH;
		अवरोध;
	हाल NL80211_AUTHTYPE_NETWORK_EAP:
		vअगर->करोt11_auth_mode = LEAP_AUTH;
		अवरोध;

	हाल NL80211_AUTHTYPE_AUTOMATIC:
		vअगर->करोt11_auth_mode = OPEN_AUTH | SHARED_AUTH;
		अवरोध;

	शेष:
		ath6kl_err("%s: 0x%x not supported\n", __func__, auth_type);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_set_cipher(काष्ठा ath6kl_vअगर *vअगर, u32 cipher, bool ucast)
अणु
	u8 *ar_cipher = ucast ? &vअगर->prwise_crypto : &vअगर->grp_crypto;
	u8 *ar_cipher_len = ucast ? &vअगर->prwise_crypto_len :
		&vअगर->grp_crypto_len;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: cipher 0x%x, ucast %u\n",
		   __func__, cipher, ucast);

	चयन (cipher) अणु
	हाल 0:
		/* our own hack to use value 0 as no crypto used */
		*ar_cipher = NONE_CRYPT;
		*ar_cipher_len = 0;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
		*ar_cipher = WEP_CRYPT;
		*ar_cipher_len = 5;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		*ar_cipher = WEP_CRYPT;
		*ar_cipher_len = 13;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		*ar_cipher = TKIP_CRYPT;
		*ar_cipher_len = 0;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		*ar_cipher = AES_CRYPT;
		*ar_cipher_len = 0;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_SMS4:
		*ar_cipher = WAPI_CRYPT;
		*ar_cipher_len = 0;
		अवरोध;
	शेष:
		ath6kl_err("cipher 0x%x not supported\n", cipher);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath6kl_set_key_mgmt(काष्ठा ath6kl_vअगर *vअगर, u32 key_mgmt)
अणु
	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: 0x%x\n", __func__, key_mgmt);

	अगर (key_mgmt == WLAN_AKM_SUITE_PSK) अणु
		अगर (vअगर->auth_mode == WPA_AUTH)
			vअगर->auth_mode = WPA_PSK_AUTH;
		अन्यथा अगर (vअगर->auth_mode == WPA2_AUTH)
			vअगर->auth_mode = WPA2_PSK_AUTH;
	पूर्ण अन्यथा अगर (key_mgmt == 0x00409600) अणु
		अगर (vअगर->auth_mode == WPA_AUTH)
			vअगर->auth_mode = WPA_AUTH_CCKM;
		अन्यथा अगर (vअगर->auth_mode == WPA2_AUTH)
			vअगर->auth_mode = WPA2_AUTH_CCKM;
	पूर्ण अन्यथा अगर (key_mgmt != WLAN_AKM_SUITE_8021X) अणु
		vअगर->auth_mode = NONE_AUTH;
	पूर्ण
पूर्ण

अटल bool ath6kl_cfg80211_पढ़ोy(काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;

	अगर (!test_bit(WMI_READY, &ar->flag)) अणु
		ath6kl_err("wmi is not ready\n");
		वापस false;
	पूर्ण

	अगर (!test_bit(WLAN_ENABLED, &vअगर->flags)) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "wlan disabled\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool ath6kl_is_wpa_ie(स्थिर u8 *pos)
अणु
	वापस pos[0] == WLAN_EID_VENDOR_SPECIFIC && pos[1] >= 4 &&
		pos[2] == 0x00 && pos[3] == 0x50 &&
		pos[4] == 0xf2 && pos[5] == 0x01;
पूर्ण

अटल bool ath6kl_is_rsn_ie(स्थिर u8 *pos)
अणु
	वापस pos[0] == WLAN_EID_RSN;
पूर्ण

अटल bool ath6kl_is_wps_ie(स्थिर u8 *pos)
अणु
	वापस (pos[0] == WLAN_EID_VENDOR_SPECIFIC &&
		pos[1] >= 4 &&
		pos[2] == 0x00 && pos[3] == 0x50 && pos[4] == 0xf2 &&
		pos[5] == 0x04);
पूर्ण

अटल पूर्णांक ath6kl_set_assoc_req_ies(काष्ठा ath6kl_vअगर *vअगर, स्थिर u8 *ies,
				    माप_प्रकार ies_len)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	स्थिर u8 *pos;
	u8 *buf = शून्य;
	माप_प्रकार len = 0;
	पूर्णांक ret;

	/*
	 * Clear previously set flag
	 */

	ar->connect_ctrl_flags &= ~CONNECT_WPS_FLAG;

	/*
	 * Filter out RSN/WPA IE(s)
	 */

	अगर (ies && ies_len) अणु
		buf = kदो_स्मृति(ies_len, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;
		pos = ies;

		जबतक (pos + 1 < ies + ies_len) अणु
			अगर (pos + 2 + pos[1] > ies + ies_len)
				अवरोध;
			अगर (!(ath6kl_is_wpa_ie(pos) || ath6kl_is_rsn_ie(pos))) अणु
				स_नकल(buf + len, pos, 2 + pos[1]);
				len += 2 + pos[1];
			पूर्ण

			अगर (ath6kl_is_wps_ie(pos))
				ar->connect_ctrl_flags |= CONNECT_WPS_FLAG;

			pos += 2 + pos[1];
		पूर्ण
	पूर्ण

	ret = ath6kl_wmi_set_appie_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				       WMI_FRAME_ASSOC_REQ, buf, len);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_nlअगरtype_to_drv_अगरtype(क्रमागत nl80211_अगरtype type, u8 *nw_type)
अणु
	चयन (type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		*nw_type = INFRA_NETWORK;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		*nw_type = ADHOC_NETWORK;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		*nw_type = AP_NETWORK;
		अवरोध;
	शेष:
		ath6kl_err("invalid interface type %u\n", type);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ath6kl_is_valid_अगरtype(काष्ठा ath6kl *ar, क्रमागत nl80211_अगरtype type,
				   u8 *अगर_idx, u8 *nw_type)
अणु
	पूर्णांक i;

	अगर (ath6kl_nlअगरtype_to_drv_अगरtype(type, nw_type))
		वापस false;

	अगर (ar->ibss_अगर_active || ((type == NL80211_IFTYPE_ADHOC) &&
				   ar->num_vअगर))
		वापस false;

	अगर (type == NL80211_IFTYPE_STATION ||
	    type == NL80211_IFTYPE_AP || type == NL80211_IFTYPE_ADHOC) अणु
		क्रम (i = 0; i < ar->vअगर_max; i++) अणु
			अगर ((ar->avail_idx_map) & BIT(i)) अणु
				*अगर_idx = i;
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (type == NL80211_IFTYPE_P2P_CLIENT ||
	    type == NL80211_IFTYPE_P2P_GO) अणु
		क्रम (i = ar->max_norm_अगरace; i < ar->vअगर_max; i++) अणु
			अगर ((ar->avail_idx_map) & BIT(i)) अणु
				*अगर_idx = i;
				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool ath6kl_is_tx_pending(काष्ठा ath6kl *ar)
अणु
	वापस ar->tx_pending[ath6kl_wmi_get_control_ep(ar->wmi)] == 0;
पूर्ण

अटल व्योम ath6kl_cfg80211_sta_bmiss_enhance(काष्ठा ath6kl_vअगर *vअगर,
					      bool enable)
अणु
	पूर्णांक err;

	अगर (WARN_ON(!test_bit(WMI_READY, &vअगर->ar->flag)))
		वापस;

	अगर (vअगर->nw_type != INFRA_NETWORK)
		वापस;

	अगर (!test_bit(ATH6KL_FW_CAPABILITY_BMISS_ENHANCE,
		      vअगर->ar->fw_capabilities))
		वापस;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s fw bmiss enhance\n",
		   enable ? "enable" : "disable");

	err = ath6kl_wmi_sta_bmiss_enhance_cmd(vअगर->ar->wmi,
					       vअगर->fw_vअगर_idx, enable);
	अगर (err)
		ath6kl_err("failed to %s enhanced bmiss detection: %d\n",
			   enable ? "enable" : "disable", err);
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				   काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	पूर्णांक status;
	u8 nw_subtype = (ar->p2p) ? SUBTYPE_P2PDEV : SUBTYPE_NONE;
	u16 पूर्णांकerval;

	ath6kl_cfg80211_sscan_disable(vअगर);

	vअगर->sme_state = SME_CONNECTING;

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (test_bit(DESTROY_IN_PROGRESS, &ar->flag)) अणु
		ath6kl_err("destroy in progress\n");
		वापस -EBUSY;
	पूर्ण

	अगर (test_bit(SKIP_SCAN, &ar->flag) &&
	    ((sme->channel && sme->channel->center_freq == 0) ||
	     (sme->bssid && is_zero_ether_addr(sme->bssid)))) अणु
		ath6kl_err("SkipScan: channel or bssid invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (करोwn_पूर्णांकerruptible(&ar->sem)) अणु
		ath6kl_err("busy, couldn't get access\n");
		वापस -ERESTARTSYS;
	पूर्ण

	अगर (test_bit(DESTROY_IN_PROGRESS, &ar->flag)) अणु
		ath6kl_err("busy, destroy in progress\n");
		up(&ar->sem);
		वापस -EBUSY;
	पूर्ण

	अगर (ar->tx_pending[ath6kl_wmi_get_control_ep(ar->wmi)]) अणु
		/*
		 * sleep until the command queue drains
		 */
		रुको_event_पूर्णांकerruptible_समयout(ar->event_wq,
						 ath6kl_is_tx_pending(ar),
						 WMI_TIMEOUT);
		अगर (संकेत_pending(current)) अणु
			ath6kl_err("cmd queue drain timeout\n");
			up(&ar->sem);
			वापस -EINTR;
		पूर्ण
	पूर्ण

	status = ath6kl_set_assoc_req_ies(vअगर, sme->ie, sme->ie_len);
	अगर (status) अणु
		up(&ar->sem);
		वापस status;
	पूर्ण

	अगर (sme->ie == शून्य || sme->ie_len == 0)
		ar->connect_ctrl_flags &= ~CONNECT_WPS_FLAG;

	अगर (test_bit(CONNECTED, &vअगर->flags) &&
	    vअगर->ssid_len == sme->ssid_len &&
	    !स_भेद(vअगर->ssid, sme->ssid, vअगर->ssid_len)) अणु
		vअगर->reconnect_flag = true;
		status = ath6kl_wmi_reconnect_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						  vअगर->req_bssid,
						  vअगर->ch_hपूर्णांक);

		up(&ar->sem);
		अगर (status) अणु
			ath6kl_err("wmi_reconnect_cmd failed\n");
			वापस -EIO;
		पूर्ण
		वापस 0;
	पूर्ण अन्यथा अगर (vअगर->ssid_len == sme->ssid_len &&
		   !स_भेद(vअगर->ssid, sme->ssid, vअगर->ssid_len)) अणु
		ath6kl_disconnect(vअगर);
	पूर्ण

	स_रखो(vअगर->ssid, 0, माप(vअगर->ssid));
	vअगर->ssid_len = sme->ssid_len;
	स_नकल(vअगर->ssid, sme->ssid, sme->ssid_len);

	अगर (sme->channel)
		vअगर->ch_hपूर्णांक = sme->channel->center_freq;

	स_रखो(vअगर->req_bssid, 0, माप(vअगर->req_bssid));
	अगर (sme->bssid && !is_broadcast_ether_addr(sme->bssid))
		स_नकल(vअगर->req_bssid, sme->bssid, माप(vअगर->req_bssid));

	ath6kl_set_wpa_version(vअगर, sme->crypto.wpa_versions);

	status = ath6kl_set_auth_type(vअगर, sme->auth_type);
	अगर (status) अणु
		up(&ar->sem);
		वापस status;
	पूर्ण

	अगर (sme->crypto.n_ciphers_pairwise)
		ath6kl_set_cipher(vअगर, sme->crypto.ciphers_pairwise[0], true);
	अन्यथा
		ath6kl_set_cipher(vअगर, 0, true);

	ath6kl_set_cipher(vअगर, sme->crypto.cipher_group, false);

	अगर (sme->crypto.n_akm_suites)
		ath6kl_set_key_mgmt(vअगर, sme->crypto.akm_suites[0]);

	अगर ((sme->key_len) &&
	    (vअगर->auth_mode == NONE_AUTH) &&
	    (vअगर->prwise_crypto == WEP_CRYPT)) अणु
		काष्ठा ath6kl_key *key = शून्य;

		अगर (sme->key_idx > WMI_MAX_KEY_INDEX) अणु
			ath6kl_err("key index %d out of bounds\n",
				   sme->key_idx);
			up(&ar->sem);
			वापस -ENOENT;
		पूर्ण

		key = &vअगर->keys[sme->key_idx];
		key->key_len = sme->key_len;
		स_नकल(key->key, sme->key, key->key_len);
		key->cipher = vअगर->prwise_crypto;
		vअगर->def_txkey_index = sme->key_idx;

		ath6kl_wmi_addkey_cmd(ar->wmi, vअगर->fw_vअगर_idx, sme->key_idx,
				      vअगर->prwise_crypto,
				      GROUP_USAGE | TX_USAGE,
				      key->key_len,
				      शून्य, 0,
				      key->key, KEY_OP_INIT_VAL, शून्य,
				      NO_SYNC_WMIFLAG);
	पूर्ण

	अगर (!ar->usr_bss_filter) अणु
		clear_bit(CLEAR_BSSFILTER_ON_BEACON, &vअगर->flags);
		अगर (ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					     ALL_BSS_FILTER, 0) != 0) अणु
			ath6kl_err("couldn't set bss filtering\n");
			up(&ar->sem);
			वापस -EIO;
		पूर्ण
	पूर्ण

	vअगर->nw_type = vअगर->next_mode;

	/* enable enhanced bmiss detection अगर applicable */
	ath6kl_cfg80211_sta_bmiss_enhance(vअगर, true);

	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_CLIENT)
		nw_subtype = SUBTYPE_P2PCLIENT;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
		   "%s: connect called with authmode %d dot11 auth %d"
		   " PW crypto %d PW crypto len %d GRP crypto %d"
		   " GRP crypto len %d channel hint %u\n",
		   __func__,
		   vअगर->auth_mode, vअगर->करोt11_auth_mode, vअगर->prwise_crypto,
		   vअगर->prwise_crypto_len, vअगर->grp_crypto,
		   vअगर->grp_crypto_len, vअगर->ch_hपूर्णांक);

	vअगर->reconnect_flag = 0;

	अगर (vअगर->nw_type == INFRA_NETWORK) अणु
		पूर्णांकerval = max_t(u16, vअगर->listen_पूर्णांकvl_t,
				 ATH6KL_MAX_WOW_LISTEN_INTL);
		status = ath6kl_wmi_listenपूर्णांकerval_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						       पूर्णांकerval,
						       0);
		अगर (status) अणु
			ath6kl_err("couldn't set listen intervel\n");
			up(&ar->sem);
			वापस status;
		पूर्ण
	पूर्ण

	status = ath6kl_wmi_connect_cmd(ar->wmi, vअगर->fw_vअगर_idx, vअगर->nw_type,
					vअगर->करोt11_auth_mode, vअगर->auth_mode,
					vअगर->prwise_crypto,
					vअगर->prwise_crypto_len,
					vअगर->grp_crypto, vअगर->grp_crypto_len,
					vअगर->ssid_len, vअगर->ssid,
					vअगर->req_bssid, vअगर->ch_hपूर्णांक,
					ar->connect_ctrl_flags, nw_subtype);

	अगर (sme->bg_scan_period == 0) अणु
		/* disable background scan अगर period is 0 */
		sme->bg_scan_period = 0xffff;
	पूर्ण अन्यथा अगर (sme->bg_scan_period == -1) अणु
		/* configure शेष value अगर not specअगरied */
		sme->bg_scan_period = DEFAULT_BG_SCAN_PERIOD;
	पूर्ण

	ath6kl_wmi_scanparams_cmd(ar->wmi, vअगर->fw_vअगर_idx, 0, 0,
				  sme->bg_scan_period, 0, 0, 0, 3, 0, 0, 0);

	up(&ar->sem);

	अगर (status == -EINVAL) अणु
		स_रखो(vअगर->ssid, 0, माप(vअगर->ssid));
		vअगर->ssid_len = 0;
		ath6kl_err("invalid request\n");
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (status) अणु
		ath6kl_err("ath6kl_wmi_connect_cmd failed\n");
		वापस -EIO;
	पूर्ण

	अगर ((!(ar->connect_ctrl_flags & CONNECT_DO_WPA_OFFLOAD)) &&
	    ((vअगर->auth_mode == WPA_PSK_AUTH) ||
	     (vअगर->auth_mode == WPA2_PSK_AUTH))) अणु
		mod_समयr(&vअगर->disconnect_समयr,
			  jअगरfies + msecs_to_jअगरfies(DISCON_TIMER_INTVAL));
	पूर्ण

	ar->connect_ctrl_flags &= ~CONNECT_DO_WPA_OFFLOAD;
	set_bit(CONNECT_PEND, &vअगर->flags);

	वापस 0;
पूर्ण

अटल काष्ठा cfg80211_bss *
ath6kl_add_bss_अगर_needed(काष्ठा ath6kl_vअगर *vअगर,
			 क्रमागत network_type nw_type,
			 स्थिर u8 *bssid,
			 काष्ठा ieee80211_channel *chan,
			 स्थिर u8 *beacon_ie,
			 माप_प्रकार beacon_ie_len)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा cfg80211_bss *bss;
	u16 cap_val;
	क्रमागत ieee80211_bss_type bss_type;
	u8 *ie;

	अगर (nw_type & ADHOC_NETWORK) अणु
		cap_val = WLAN_CAPABILITY_IBSS;
		bss_type = IEEE80211_BSS_TYPE_IBSS;
	पूर्ण अन्यथा अणु
		cap_val = WLAN_CAPABILITY_ESS;
		bss_type = IEEE80211_BSS_TYPE_ESS;
	पूर्ण

	bss = cfg80211_get_bss(ar->wiphy, chan, bssid,
			       vअगर->ssid, vअगर->ssid_len,
			       bss_type, IEEE80211_PRIVACY_ANY);
	अगर (bss == शून्य) अणु
		/*
		 * Since cfg80211 may not yet know about the BSS,
		 * generate a partial entry until the first BSS info
		 * event becomes available.
		 *
		 * Prepend SSID element since it is not included in the Beacon
		 * IEs from the target.
		 */
		ie = kदो_स्मृति(2 + vअगर->ssid_len + beacon_ie_len, GFP_KERNEL);
		अगर (ie == शून्य)
			वापस शून्य;
		ie[0] = WLAN_EID_SSID;
		ie[1] = vअगर->ssid_len;
		स_नकल(ie + 2, vअगर->ssid, vअगर->ssid_len);
		स_नकल(ie + 2 + vअगर->ssid_len, beacon_ie, beacon_ie_len);
		bss = cfg80211_inक्रमm_bss(ar->wiphy, chan,
					  CFG80211_BSS_FTYPE_UNKNOWN,
					  bssid, 0, cap_val, 100,
					  ie, 2 + vअगर->ssid_len + beacon_ie_len,
					  0, GFP_KERNEL);
		अगर (bss)
			ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
				   "added bss %pM to cfg80211\n", bssid);
		kमुक्त(ie);
	पूर्ण अन्यथा अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "cfg80211 already has a bss\n");
	पूर्ण

	वापस bss;
पूर्ण

व्योम ath6kl_cfg80211_connect_event(काष्ठा ath6kl_vअगर *vअगर, u16 channel,
				   u8 *bssid, u16 listen_पूर्णांकvl,
				   u16 beacon_पूर्णांकvl,
				   क्रमागत network_type nw_type,
				   u8 beacon_ie_len, u8 assoc_req_len,
				   u8 assoc_resp_len, u8 *assoc_info)
अणु
	काष्ठा ieee80211_channel *chan;
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा cfg80211_bss *bss;

	/* capinfo + listen पूर्णांकerval */
	u8 assoc_req_ie_offset = माप(u16) + माप(u16);

	/* capinfo + status code +  associd */
	u8 assoc_resp_ie_offset = माप(u16) + माप(u16) + माप(u16);

	u8 *assoc_req_ie = assoc_info + beacon_ie_len + assoc_req_ie_offset;
	u8 *assoc_resp_ie = assoc_info + beacon_ie_len + assoc_req_len +
	    assoc_resp_ie_offset;

	assoc_req_len -= assoc_req_ie_offset;
	assoc_resp_len -= assoc_resp_ie_offset;

	/*
	 * Store Beacon पूर्णांकerval here; DTIM period will be available only once
	 * a Beacon frame from the AP is seen.
	 */
	vअगर->assoc_bss_beacon_पूर्णांक = beacon_पूर्णांकvl;
	clear_bit(DTIM_PERIOD_AVAIL, &vअगर->flags);

	अगर (nw_type & ADHOC_NETWORK) अणु
		अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_ADHOC) अणु
			ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
				   "%s: ath6k not in ibss mode\n", __func__);
			वापस;
		पूर्ण
	पूर्ण

	अगर (nw_type & INFRA_NETWORK) अणु
		अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_STATION &&
		    vअगर->wdev.अगरtype != NL80211_IFTYPE_P2P_CLIENT) अणु
			ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
				   "%s: ath6k not in station mode\n", __func__);
			वापस;
		पूर्ण
	पूर्ण

	chan = ieee80211_get_channel(ar->wiphy, (पूर्णांक) channel);

	bss = ath6kl_add_bss_अगर_needed(vअगर, nw_type, bssid, chan,
				       assoc_info, beacon_ie_len);
	अगर (!bss) अणु
		ath6kl_err("could not add cfg80211 bss entry\n");
		वापस;
	पूर्ण

	अगर (nw_type & ADHOC_NETWORK) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "ad-hoc %s selected\n",
			   nw_type & ADHOC_CREATOR ? "creator" : "joiner");
		cfg80211_ibss_joined(vअगर->ndev, bssid, chan, GFP_KERNEL);
		cfg80211_put_bss(ar->wiphy, bss);
		वापस;
	पूर्ण

	अगर (vअगर->sme_state == SME_CONNECTING) अणु
		/* inक्रमm connect result to cfg80211 */
		vअगर->sme_state = SME_CONNECTED;
		cfg80211_connect_result(vअगर->ndev, bssid,
					assoc_req_ie, assoc_req_len,
					assoc_resp_ie, assoc_resp_len,
					WLAN_STATUS_SUCCESS, GFP_KERNEL);
		cfg80211_put_bss(ar->wiphy, bss);
	पूर्ण अन्यथा अगर (vअगर->sme_state == SME_CONNECTED) अणु
		काष्ठा cfg80211_roam_info roam_info = अणु
			.bss = bss,
			.req_ie = assoc_req_ie,
			.req_ie_len = assoc_req_len,
			.resp_ie = assoc_resp_ie,
			.resp_ie_len = assoc_resp_len,
		पूर्ण;
		/* inक्रमm roam event to cfg80211 */
		cfg80211_roamed(vअगर->ndev, &roam_info, GFP_KERNEL);
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_disconnect(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev, u16 reason_code)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: reason=%u\n", __func__,
		   reason_code);

	ath6kl_cfg80211_sscan_disable(vअगर);

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (test_bit(DESTROY_IN_PROGRESS, &ar->flag)) अणु
		ath6kl_err("busy, destroy in progress\n");
		वापस -EBUSY;
	पूर्ण

	अगर (करोwn_पूर्णांकerruptible(&ar->sem)) अणु
		ath6kl_err("busy, couldn't get access\n");
		वापस -ERESTARTSYS;
	पूर्ण

	vअगर->reconnect_flag = 0;
	ath6kl_disconnect(vअगर);
	स_रखो(vअगर->ssid, 0, माप(vअगर->ssid));
	vअगर->ssid_len = 0;

	अगर (!test_bit(SKIP_SCAN, &ar->flag))
		स_रखो(vअगर->req_bssid, 0, माप(vअगर->req_bssid));

	up(&ar->sem);

	वापस 0;
पूर्ण

व्योम ath6kl_cfg80211_disconnect_event(काष्ठा ath6kl_vअगर *vअगर, u8 reason,
				      u8 *bssid, u8 assoc_resp_len,
				      u8 *assoc_info, u16 proto_reason)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;

	अगर (vअगर->scan_req) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = true,
		पूर्ण;

		cfg80211_scan_करोne(vअगर->scan_req, &info);
		vअगर->scan_req = शून्य;
	पूर्ण

	अगर (vअगर->nw_type & ADHOC_NETWORK) अणु
		अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_ADHOC)
			ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
				   "%s: ath6k not in ibss mode\n", __func__);
		वापस;
	पूर्ण

	अगर (vअगर->nw_type & INFRA_NETWORK) अणु
		अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_STATION &&
		    vअगर->wdev.अगरtype != NL80211_IFTYPE_P2P_CLIENT) अणु
			ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
				   "%s: ath6k not in station mode\n", __func__);
			वापस;
		पूर्ण
	पूर्ण

	clear_bit(CONNECT_PEND, &vअगर->flags);

	अगर (vअगर->sme_state == SME_CONNECTING) अणु
		cfg80211_connect_result(vअगर->ndev,
					bssid, शून्य, 0,
					शून्य, 0,
					WLAN_STATUS_UNSPECIFIED_FAILURE,
					GFP_KERNEL);
	पूर्ण अन्यथा अगर (vअगर->sme_state == SME_CONNECTED) अणु
		cfg80211_disconnected(vअगर->ndev, proto_reason,
				      शून्य, 0, false, GFP_KERNEL);
	पूर्ण

	vअगर->sme_state = SME_DISCONNECTED;

	/*
	 * Send a disconnect command to target when a disconnect event is
	 * received with reason code other than 3 (DISCONNECT_CMD - disconnect
	 * request from host) to make the firmware stop trying to connect even
	 * after giving disconnect event. There will be one more disconnect
	 * event क्रम this disconnect command with reason code DISCONNECT_CMD
	 * which won't be notअगरied to cfg80211.
	 */
	अगर (reason != DISCONNECT_CMD)
		ath6kl_wmi_disconnect_cmd(ar->wmi, vअगर->fw_vअगर_idx);
पूर्ण

अटल पूर्णांक ath6kl_set_probed_ssids(काष्ठा ath6kl *ar,
				   काष्ठा ath6kl_vअगर *vअगर,
				   काष्ठा cfg80211_ssid *ssids, पूर्णांक n_ssids,
				   काष्ठा cfg80211_match_set *match_set,
				   पूर्णांक n_match_ssid)
अणु
	u8 i, j, index_to_add, ssid_found = false;
	काष्ठा ath6kl_cfg80211_match_probe_ssid ssid_list[MAX_PROBED_SSIDS];

	स_रखो(ssid_list, 0, माप(ssid_list));

	अगर (n_ssids > MAX_PROBED_SSIDS ||
	    n_match_ssid > MAX_PROBED_SSIDS)
		वापस -EINVAL;

	क्रम (i = 0; i < n_ssids; i++) अणु
		स_नकल(ssid_list[i].ssid.ssid,
		       ssids[i].ssid,
		       ssids[i].ssid_len);
		ssid_list[i].ssid.ssid_len = ssids[i].ssid_len;

		अगर (ssids[i].ssid_len)
			ssid_list[i].flag = SPECIFIC_SSID_FLAG;
		अन्यथा
			ssid_list[i].flag = ANY_SSID_FLAG;

		अगर (ar->wiphy->max_match_sets != 0 && n_match_ssid == 0)
			ssid_list[i].flag |= MATCH_SSID_FLAG;
	पूर्ण

	index_to_add = i;

	क्रम (i = 0; i < n_match_ssid; i++) अणु
		ssid_found = false;

		क्रम (j = 0; j < n_ssids; j++) अणु
			अगर ((match_set[i].ssid.ssid_len ==
			     ssid_list[j].ssid.ssid_len) &&
			    (!स_भेद(ssid_list[j].ssid.ssid,
				     match_set[i].ssid.ssid,
				     match_set[i].ssid.ssid_len))) अणु
				ssid_list[j].flag |= MATCH_SSID_FLAG;
				ssid_found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ssid_found)
			जारी;

		अगर (index_to_add >= MAX_PROBED_SSIDS)
			जारी;

		ssid_list[index_to_add].ssid.ssid_len =
			match_set[i].ssid.ssid_len;
		स_नकल(ssid_list[index_to_add].ssid.ssid,
		       match_set[i].ssid.ssid,
		       match_set[i].ssid.ssid_len);
		ssid_list[index_to_add].flag |= MATCH_SSID_FLAG;
		index_to_add++;
	पूर्ण

	क्रम (i = 0; i < index_to_add; i++) अणु
		ath6kl_wmi_probedssid_cmd(ar->wmi, vअगर->fw_vअगर_idx, i,
					  ssid_list[i].flag,
					  ssid_list[i].ssid.ssid_len,
					  ssid_list[i].ssid.ssid);
	पूर्ण

	/* Make sure no old entries are left behind */
	क्रम (i = index_to_add; i < MAX_PROBED_SSIDS; i++) अणु
		ath6kl_wmi_probedssid_cmd(ar->wmi, vअगर->fw_vअगर_idx, i,
					  DISABLE_SSID_FLAG, 0, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_scan(काष्ठा wiphy *wiphy,
				काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा ath6kl_vअगर *vअगर = ath6kl_vअगर_from_wdev(request->wdev);
	काष्ठा ath6kl *ar = ath6kl_priv(vअगर->ndev);
	s8 n_channels = 0;
	u16 *channels = शून्य;
	पूर्णांक ret = 0;
	u32 क्रमce_fg_scan = 0;

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	ath6kl_cfg80211_sscan_disable(vअगर);

	अगर (!ar->usr_bss_filter) अणु
		clear_bit(CLEAR_BSSFILTER_ON_BEACON, &vअगर->flags);
		ret = ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					       ALL_BSS_FILTER, 0);
		अगर (ret) अणु
			ath6kl_err("couldn't set bss filtering\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = ath6kl_set_probed_ssids(ar, vअगर, request->ssids,
				      request->n_ssids, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	/* this also clears IE in fw अगर it's not set */
	ret = ath6kl_wmi_set_appie_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				       WMI_FRAME_PROBE_REQ,
				       request->ie, request->ie_len);
	अगर (ret) अणु
		ath6kl_err("failed to set Probe Request appie for scan\n");
		वापस ret;
	पूर्ण

	/*
	 * Scan only the requested channels अगर the request specअगरies a set of
	 * channels. If the list is दीर्घer than the target supports, करो not
	 * configure the list and instead, scan all available channels.
	 */
	अगर (request->n_channels > 0 &&
	    request->n_channels <= WMI_MAX_CHANNELS) अणु
		u8 i;

		n_channels = request->n_channels;

		channels = kसुस्मृति(n_channels, माप(u16), GFP_KERNEL);
		अगर (channels == शून्य) अणु
			ath6kl_warn("failed to set scan channels, scan all channels");
			n_channels = 0;
		पूर्ण

		क्रम (i = 0; i < n_channels; i++)
			channels[i] = request->channels[i]->center_freq;
	पूर्ण

	अगर (test_bit(CONNECTED, &vअगर->flags))
		क्रमce_fg_scan = 1;

	vअगर->scan_req = request;

	ret = ath6kl_wmi_beginscan_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				       WMI_LONG_SCAN, क्रमce_fg_scan,
				       false, 0,
				       ATH6KL_FG_SCAN_INTERVAL,
				       n_channels, channels,
				       request->no_cck,
				       request->rates);
	अगर (ret) अणु
		ath6kl_err("failed to start scan: %d\n", ret);
		vअगर->scan_req = शून्य;
	पूर्ण

	kमुक्त(channels);

	वापस ret;
पूर्ण

व्योम ath6kl_cfg80211_scan_complete_event(काष्ठा ath6kl_vअगर *vअगर, bool पातed)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = पातed,
	पूर्ण;
	पूर्णांक i;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: status%s\n", __func__,
		   पातed ? " aborted" : "");

	अगर (!vअगर->scan_req)
		वापस;

	अगर (पातed)
		जाओ out;

	अगर (vअगर->scan_req->n_ssids && vअगर->scan_req->ssids[0].ssid_len) अणु
		क्रम (i = 0; i < vअगर->scan_req->n_ssids; i++) अणु
			ath6kl_wmi_probedssid_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						  i, DISABLE_SSID_FLAG,
						  0, शून्य);
		पूर्ण
	पूर्ण

out:
	cfg80211_scan_करोne(vअगर->scan_req, &info);
	vअगर->scan_req = शून्य;
पूर्ण

व्योम ath6kl_cfg80211_ch_चयन_notअगरy(काष्ठा ath6kl_vअगर *vअगर, पूर्णांक freq,
				      क्रमागत wmi_phy_mode mode)
अणु
	काष्ठा cfg80211_chan_def chandef;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
		   "channel switch notify nw_type %d freq %d mode %d\n",
		   vअगर->nw_type, freq, mode);

	cfg80211_chandef_create(&chandef,
				ieee80211_get_channel(vअगर->ar->wiphy, freq),
				(mode == WMI_11G_HT20 &&
				 ath6kl_band_2ghz.ht_cap.ht_supported) ?
					NL80211_CHAN_HT20 : NL80211_CHAN_NO_HT);

	mutex_lock(&vअगर->wdev.mtx);
	cfg80211_ch_चयन_notअगरy(vअगर->ndev, &chandef);
	mutex_unlock(&vअगर->wdev.mtx);
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				   u8 key_index, bool pairwise,
				   स्थिर u8 *mac_addr,
				   काष्ठा key_params *params)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(ndev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(ndev);
	काष्ठा ath6kl_key *key = शून्य;
	पूर्णांक seq_len;
	u8 key_usage;
	u8 key_type;

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (params->cipher == CCKM_KRK_CIPHER_SUITE) अणु
		अगर (params->key_len != WMI_KRK_LEN)
			वापस -EINVAL;
		वापस ath6kl_wmi_add_krk_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					      params->key);
	पूर्ण

	अगर (key_index > WMI_MAX_KEY_INDEX) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "%s: key index %d out of bounds\n", __func__,
			   key_index);
		वापस -ENOENT;
	पूर्ण

	key = &vअगर->keys[key_index];
	स_रखो(key, 0, माप(काष्ठा ath6kl_key));

	अगर (pairwise)
		key_usage = PAIRWISE_USAGE;
	अन्यथा
		key_usage = GROUP_USAGE;

	seq_len = params->seq_len;
	अगर (params->cipher == WLAN_CIPHER_SUITE_SMS4 &&
	    seq_len > ATH6KL_KEY_SEQ_LEN) अणु
		/* Only first half of the WPI PN is configured */
		seq_len = ATH6KL_KEY_SEQ_LEN;
	पूर्ण
	अगर (params->key_len > WLAN_MAX_KEY_LEN ||
	    seq_len > माप(key->seq))
		वापस -EINVAL;

	key->key_len = params->key_len;
	स_नकल(key->key, params->key, key->key_len);
	key->seq_len = seq_len;
	स_नकल(key->seq, params->seq, key->seq_len);
	key->cipher = params->cipher;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		key_type = WEP_CRYPT;
		अवरोध;

	हाल WLAN_CIPHER_SUITE_TKIP:
		key_type = TKIP_CRYPT;
		अवरोध;

	हाल WLAN_CIPHER_SUITE_CCMP:
		key_type = AES_CRYPT;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_SMS4:
		key_type = WAPI_CRYPT;
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	अगर (((vअगर->auth_mode == WPA_PSK_AUTH) ||
	     (vअगर->auth_mode == WPA2_PSK_AUTH)) &&
	    (key_usage & GROUP_USAGE))
		del_समयr(&vअगर->disconnect_समयr);

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
		   "%s: index %d, key_len %d, key_type 0x%x, key_usage 0x%x, seq_len %d\n",
		   __func__, key_index, key->key_len, key_type,
		   key_usage, key->seq_len);

	अगर (vअगर->nw_type == AP_NETWORK && !pairwise &&
	    (key_type == TKIP_CRYPT || key_type == AES_CRYPT ||
	     key_type == WAPI_CRYPT)) अणु
		ar->ap_mode_bkey.valid = true;
		ar->ap_mode_bkey.key_index = key_index;
		ar->ap_mode_bkey.key_type = key_type;
		ar->ap_mode_bkey.key_len = key->key_len;
		स_नकल(ar->ap_mode_bkey.key, key->key, key->key_len);
		अगर (!test_bit(CONNECTED, &vअगर->flags)) अणु
			ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
				   "Delay initial group key configuration until AP mode has been started\n");
			/*
			 * The key will be set in ath6kl_connect_ap_mode() once
			 * the connected event is received from the target.
			 */
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (vअगर->next_mode == AP_NETWORK && key_type == WEP_CRYPT &&
	    !test_bit(CONNECTED, &vअगर->flags)) अणु
		/*
		 * Store the key locally so that it can be re-configured after
		 * the AP mode has properly started
		 * (ath6kl_install_statioc_wep_keys).
		 */
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "Delay WEP key configuration until AP mode has been started\n");
		vअगर->wep_key_list[key_index].key_len = key->key_len;
		स_नकल(vअगर->wep_key_list[key_index].key, key->key,
		       key->key_len);
		वापस 0;
	पूर्ण

	वापस ath6kl_wmi_addkey_cmd(ar->wmi, vअगर->fw_vअगर_idx, key_index,
				     key_type, key_usage, key->key_len,
				     key->seq, key->seq_len, key->key,
				     KEY_OP_INIT_VAL,
				     (u8 *) mac_addr, SYNC_BOTH_WMIFLAG);
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				   u8 key_index, bool pairwise,
				   स्थिर u8 *mac_addr)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(ndev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(ndev);

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: index %d\n", __func__, key_index);

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (key_index > WMI_MAX_KEY_INDEX) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "%s: key index %d out of bounds\n", __func__,
			   key_index);
		वापस -ENOENT;
	पूर्ण

	अगर (!vअगर->keys[key_index].key_len) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "%s: index %d is empty\n", __func__, key_index);
		वापस 0;
	पूर्ण

	vअगर->keys[key_index].key_len = 0;

	वापस ath6kl_wmi_deletekey_cmd(ar->wmi, vअगर->fw_vअगर_idx, key_index);
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_get_key(काष्ठा wiphy *wiphy, काष्ठा net_device *ndev,
				   u8 key_index, bool pairwise,
				   स्थिर u8 *mac_addr, व्योम *cookie,
				   व्योम (*callback) (व्योम *cookie,
						     काष्ठा key_params *))
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(ndev);
	काष्ठा ath6kl_key *key = शून्य;
	काष्ठा key_params params;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: index %d\n", __func__, key_index);

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (key_index > WMI_MAX_KEY_INDEX) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "%s: key index %d out of bounds\n", __func__,
			   key_index);
		वापस -ENOENT;
	पूर्ण

	key = &vअगर->keys[key_index];
	स_रखो(&params, 0, माप(params));
	params.cipher = key->cipher;
	params.key_len = key->key_len;
	params.seq_len = key->seq_len;
	params.seq = key->seq;
	params.key = key->key;

	callback(cookie, &params);

	वापस key->key_len ? 0 : -ENOENT;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_set_शेष_key(काष्ठा wiphy *wiphy,
					   काष्ठा net_device *ndev,
					   u8 key_index, bool unicast,
					   bool multicast)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(ndev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(ndev);
	काष्ठा ath6kl_key *key = शून्य;
	u8 key_usage;
	क्रमागत ath6kl_crypto_type key_type = NONE_CRYPT;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: index %d\n", __func__, key_index);

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (key_index > WMI_MAX_KEY_INDEX) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "%s: key index %d out of bounds\n",
			   __func__, key_index);
		वापस -ENOENT;
	पूर्ण

	अगर (!vअगर->keys[key_index].key_len) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: invalid key index %d\n",
			   __func__, key_index);
		वापस -EINVAL;
	पूर्ण

	vअगर->def_txkey_index = key_index;
	key = &vअगर->keys[vअगर->def_txkey_index];
	key_usage = GROUP_USAGE;
	अगर (vअगर->prwise_crypto == WEP_CRYPT)
		key_usage |= TX_USAGE;
	अगर (unicast)
		key_type = vअगर->prwise_crypto;
	अगर (multicast)
		key_type = vअगर->grp_crypto;

	अगर (vअगर->next_mode == AP_NETWORK && !test_bit(CONNECTED, &vअगर->flags))
		वापस 0; /* Delay until AP mode has been started */

	वापस ath6kl_wmi_addkey_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				     vअगर->def_txkey_index,
				     key_type, key_usage,
				     key->key_len, key->seq, key->seq_len,
				     key->key,
				     KEY_OP_INIT_VAL, शून्य,
				     SYNC_BOTH_WMIFLAG);
पूर्ण

व्योम ath6kl_cfg80211_tkip_micerr_event(काष्ठा ath6kl_vअगर *vअगर, u8 keyid,
				       bool ismcast)
अणु
	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
		   "%s: keyid %d, ismcast %d\n", __func__, keyid, ismcast);

	cfg80211_michael_mic_failure(vअगर->ndev, vअगर->bssid,
				     (ismcast ? NL80211_KEYTYPE_GROUP :
				      NL80211_KEYTYPE_PAIRWISE), keyid, शून्य,
				     GFP_KERNEL);
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा ath6kl *ar = (काष्ठा ath6kl *)wiphy_priv(wiphy);
	काष्ठा ath6kl_vअगर *vअगर;
	पूर्णांक ret;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: changed 0x%x\n", __func__,
		   changed);

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (changed & WIPHY_PARAM_RTS_THRESHOLD) अणु
		ret = ath6kl_wmi_set_rts_cmd(ar->wmi, wiphy->rts_threshold);
		अगर (ret != 0) अणु
			ath6kl_err("ath6kl_wmi_set_rts_cmd failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_set_txघातer(काष्ठा wiphy *wiphy,
				       काष्ठा wireless_dev *wdev,
				       क्रमागत nl80211_tx_घातer_setting type,
				       पूर्णांक mbm)
अणु
	काष्ठा ath6kl *ar = (काष्ठा ath6kl *)wiphy_priv(wiphy);
	काष्ठा ath6kl_vअगर *vअगर;
	पूर्णांक dbm = MBM_TO_DBM(mbm);

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: type 0x%x, dbm %d\n", __func__,
		   type, dbm);

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	चयन (type) अणु
	हाल NL80211_TX_POWER_AUTOMATIC:
		वापस 0;
	हाल NL80211_TX_POWER_LIMITED:
		ar->tx_pwr = dbm;
		अवरोध;
	शेष:
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: type 0x%x not supported\n",
			   __func__, type);
		वापस -EOPNOTSUPP;
	पूर्ण

	ath6kl_wmi_set_tx_pwr_cmd(ar->wmi, vअगर->fw_vअगर_idx, dbm);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_get_txघातer(काष्ठा wiphy *wiphy,
				       काष्ठा wireless_dev *wdev,
				       पूर्णांक *dbm)
अणु
	काष्ठा ath6kl *ar = (काष्ठा ath6kl *)wiphy_priv(wiphy);
	काष्ठा ath6kl_vअगर *vअगर;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (test_bit(CONNECTED, &vअगर->flags)) अणु
		ar->tx_pwr = 255;

		अगर (ath6kl_wmi_get_tx_pwr_cmd(ar->wmi, vअगर->fw_vअगर_idx) != 0) अणु
			ath6kl_err("ath6kl_wmi_get_tx_pwr_cmd failed\n");
			वापस -EIO;
		पूर्ण

		रुको_event_पूर्णांकerruptible_समयout(ar->event_wq, ar->tx_pwr != 255,
						 5 * HZ);

		अगर (संकेत_pending(current)) अणु
			ath6kl_err("target did not respond\n");
			वापस -EINTR;
		पूर्ण
	पूर्ण

	*dbm = ar->tx_pwr;
	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_set_घातer_mgmt(काष्ठा wiphy *wiphy,
					  काष्ठा net_device *dev,
					  bool pmgmt, पूर्णांक समयout)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा wmi_घातer_mode_cmd mode;
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: pmgmt %d, timeout %d\n",
		   __func__, pmgmt, समयout);

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (pmgmt) अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: rec power\n", __func__);
		mode.pwr_mode = REC_POWER;
	पूर्ण अन्यथा अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: max perf\n", __func__);
		mode.pwr_mode = MAX_PERF_POWER;
	पूर्ण

	अगर (ath6kl_wmi_घातermode_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				     mode.pwr_mode) != 0) अणु
		ath6kl_err("wmi_powermode_cmd failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा wireless_dev *ath6kl_cfg80211_add_अगरace(काष्ठा wiphy *wiphy,
						      स्थिर अक्षर *name,
						      अचिन्हित अक्षर name_assign_type,
						      क्रमागत nl80211_अगरtype type,
						      काष्ठा vअगर_params *params)
अणु
	काष्ठा ath6kl *ar = wiphy_priv(wiphy);
	काष्ठा wireless_dev *wdev;
	u8 अगर_idx, nw_type;

	अगर (ar->num_vअगर == ar->vअगर_max) अणु
		ath6kl_err("Reached maximum number of supported vif\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!ath6kl_is_valid_अगरtype(ar, type, &अगर_idx, &nw_type)) अणु
		ath6kl_err("Not a supported interface type\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	wdev = ath6kl_पूर्णांकerface_add(ar, name, name_assign_type, type, अगर_idx, nw_type);
	अगर (!wdev)
		वापस ERR_PTR(-ENOMEM);

	ar->num_vअगर++;

	वापस wdev;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_del_अगरace(काष्ठा wiphy *wiphy,
				     काष्ठा wireless_dev *wdev)
अणु
	काष्ठा ath6kl *ar = wiphy_priv(wiphy);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(wdev->netdev);

	spin_lock_bh(&ar->list_lock);
	list_del(&vअगर->list);
	spin_unlock_bh(&ar->list_lock);

	ath6kl_cfg80211_vअगर_stop(vअगर, test_bit(WMI_READY, &ar->flag));

	rtnl_lock();
	ath6kl_cfg80211_vअगर_cleanup(vअगर);
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_change_अगरace(काष्ठा wiphy *wiphy,
					काष्ठा net_device *ndev,
					क्रमागत nl80211_अगरtype type,
					काष्ठा vअगर_params *params)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(ndev);
	पूर्णांक i;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s: type %u\n", __func__, type);

	/*
	 * Don't bring up p2p on an पूर्णांकerface which is not initialized
	 * क्रम p2p operation where fw करोes not have capability to चयन
	 * dynamically between non-p2p and p2p type पूर्णांकerface.
	 */
	अगर (!test_bit(ATH6KL_FW_CAPABILITY_STA_P2PDEV_DUPLEX,
		      vअगर->ar->fw_capabilities) &&
	    (type == NL80211_IFTYPE_P2P_CLIENT ||
	     type == NL80211_IFTYPE_P2P_GO)) अणु
		अगर (vअगर->ar->vअगर_max == 1) अणु
			अगर (vअगर->fw_vअगर_idx != 0)
				वापस -EINVAL;
			अन्यथा
				जाओ set_अगरace_type;
		पूर्ण

		क्रम (i = vअगर->ar->max_norm_अगरace; i < vअगर->ar->vअगर_max; i++) अणु
			अगर (i == vअगर->fw_vअगर_idx)
				अवरोध;
		पूर्ण

		अगर (i == vअगर->ar->vअगर_max) अणु
			ath6kl_err("Invalid interface to bring up P2P\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* need to clean up enhanced bmiss detection fw state */
	ath6kl_cfg80211_sta_bmiss_enhance(vअगर, false);

set_अगरace_type:
	चयन (type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		vअगर->next_mode = INFRA_NETWORK;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		vअगर->next_mode = ADHOC_NETWORK;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		vअगर->next_mode = AP_NETWORK;
		अवरोध;
	शेष:
		ath6kl_err("invalid interface type %u\n", type);
		वापस -EOPNOTSUPP;
	पूर्ण

	vअगर->wdev.अगरtype = type;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_join_ibss(काष्ठा wiphy *wiphy,
				     काष्ठा net_device *dev,
				     काष्ठा cfg80211_ibss_params *ibss_param)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	पूर्णांक status;

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	vअगर->ssid_len = ibss_param->ssid_len;
	स_नकल(vअगर->ssid, ibss_param->ssid, vअगर->ssid_len);

	अगर (ibss_param->chandef.chan)
		vअगर->ch_hपूर्णांक = ibss_param->chandef.chan->center_freq;

	अगर (ibss_param->channel_fixed) अणु
		/*
		 * TODO: channel_fixed: The channel should be fixed, करो not
		 * search क्रम IBSSs to join on other channels. Target
		 * firmware करोes not support this feature, needs to be
		 * updated.
		 */
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(vअगर->req_bssid, 0, माप(vअगर->req_bssid));
	अगर (ibss_param->bssid && !is_broadcast_ether_addr(ibss_param->bssid))
		स_नकल(vअगर->req_bssid, ibss_param->bssid,
		       माप(vअगर->req_bssid));

	ath6kl_set_wpa_version(vअगर, 0);

	status = ath6kl_set_auth_type(vअगर, NL80211_AUTHTYPE_OPEN_SYSTEM);
	अगर (status)
		वापस status;

	अगर (ibss_param->privacy) अणु
		ath6kl_set_cipher(vअगर, WLAN_CIPHER_SUITE_WEP40, true);
		ath6kl_set_cipher(vअगर, WLAN_CIPHER_SUITE_WEP40, false);
	पूर्ण अन्यथा अणु
		ath6kl_set_cipher(vअगर, 0, true);
		ath6kl_set_cipher(vअगर, 0, false);
	पूर्ण

	vअगर->nw_type = vअगर->next_mode;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
		   "%s: connect called with authmode %d dot11 auth %d"
		   " PW crypto %d PW crypto len %d GRP crypto %d"
		   " GRP crypto len %d channel hint %u\n",
		   __func__,
		   vअगर->auth_mode, vअगर->करोt11_auth_mode, vअगर->prwise_crypto,
		   vअगर->prwise_crypto_len, vअगर->grp_crypto,
		   vअगर->grp_crypto_len, vअगर->ch_hपूर्णांक);

	status = ath6kl_wmi_connect_cmd(ar->wmi, vअगर->fw_vअगर_idx, vअगर->nw_type,
					vअगर->करोt11_auth_mode, vअगर->auth_mode,
					vअगर->prwise_crypto,
					vअगर->prwise_crypto_len,
					vअगर->grp_crypto, vअगर->grp_crypto_len,
					vअगर->ssid_len, vअगर->ssid,
					vअगर->req_bssid, vअगर->ch_hपूर्णांक,
					ar->connect_ctrl_flags, SUBTYPE_NONE);
	set_bit(CONNECT_PEND, &vअगर->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_leave_ibss(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	ath6kl_disconnect(vअगर);
	स_रखो(vअगर->ssid, 0, माप(vअगर->ssid));
	vअगर->ssid_len = 0;

	वापस 0;
पूर्ण

अटल स्थिर u32 cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_WEP40,
	WLAN_CIPHER_SUITE_WEP104,
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
	CCKM_KRK_CIPHER_SUITE,
	WLAN_CIPHER_SUITE_SMS4,
पूर्ण;

अटल bool is_rate_legacy(s32 rate)
अणु
	अटल स्थिर s32 legacy[] = अणु 1000, 2000, 5500, 11000,
		6000, 9000, 12000, 18000, 24000,
		36000, 48000, 54000
	पूर्ण;
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(legacy); i++)
		अगर (rate == legacy[i])
			वापस true;

	वापस false;
पूर्ण

अटल bool is_rate_ht20(s32 rate, u8 *mcs, bool *sgi)
अणु
	अटल स्थिर s32 ht20[] = अणु 6500, 13000, 19500, 26000, 39000,
		52000, 58500, 65000, 72200
	पूर्ण;
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(ht20); i++) अणु
		अगर (rate == ht20[i]) अणु
			अगर (i == ARRAY_SIZE(ht20) - 1)
				/* last rate uses sgi */
				*sgi = true;
			अन्यथा
				*sgi = false;

			*mcs = i;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool is_rate_ht40(s32 rate, u8 *mcs, bool *sgi)
अणु
	अटल स्थिर s32 ht40[] = अणु 13500, 27000, 40500, 54000,
		81000, 108000, 121500, 135000,
		150000
	पूर्ण;
	u8 i;

	क्रम (i = 0; i < ARRAY_SIZE(ht40); i++) अणु
		अगर (rate == ht40[i]) अणु
			अगर (i == ARRAY_SIZE(ht40) - 1)
				/* last rate uses sgi */
				*sgi = true;
			अन्यथा
				*sgi = false;

			*mcs = i;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ath6kl_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	दीर्घ left;
	bool sgi;
	s32 rate;
	पूर्णांक ret;
	u8 mcs;

	अगर (स_भेद(mac, vअगर->bssid, ETH_ALEN) != 0)
		वापस -ENOENT;

	अगर (करोwn_पूर्णांकerruptible(&ar->sem))
		वापस -EBUSY;

	set_bit(STATS_UPDATE_PEND, &vअगर->flags);

	ret = ath6kl_wmi_get_stats_cmd(ar->wmi, vअगर->fw_vअगर_idx);

	अगर (ret != 0) अणु
		up(&ar->sem);
		वापस -EIO;
	पूर्ण

	left = रुको_event_पूर्णांकerruptible_समयout(ar->event_wq,
						!test_bit(STATS_UPDATE_PEND,
							  &vअगर->flags),
						WMI_TIMEOUT);

	up(&ar->sem);

	अगर (left == 0)
		वापस -ETIMEDOUT;
	अन्यथा अगर (left < 0)
		वापस left;

	अगर (vअगर->target_stats.rx_byte) अणु
		sinfo->rx_bytes = vअगर->target_stats.rx_byte;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BYTES64);
		sinfo->rx_packets = vअगर->target_stats.rx_pkt;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_PACKETS);
	पूर्ण

	अगर (vअगर->target_stats.tx_byte) अणु
		sinfo->tx_bytes = vअगर->target_stats.tx_byte;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BYTES64);
		sinfo->tx_packets = vअगर->target_stats.tx_pkt;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_PACKETS);
	पूर्ण

	sinfo->संकेत = vअगर->target_stats.cs_rssi;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);

	rate = vअगर->target_stats.tx_ucast_rate;

	अगर (is_rate_legacy(rate)) अणु
		sinfo->txrate.legacy = rate / 100;
	पूर्ण अन्यथा अगर (is_rate_ht20(rate, &mcs, &sgi)) अणु
		अगर (sgi) अणु
			sinfo->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;
			sinfo->txrate.mcs = mcs - 1;
		पूर्ण अन्यथा अणु
			sinfo->txrate.mcs = mcs;
		पूर्ण

		sinfo->txrate.flags |= RATE_INFO_FLAGS_MCS;
		sinfo->txrate.bw = RATE_INFO_BW_20;
	पूर्ण अन्यथा अगर (is_rate_ht40(rate, &mcs, &sgi)) अणु
		अगर (sgi) अणु
			sinfo->txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;
			sinfo->txrate.mcs = mcs - 1;
		पूर्ण अन्यथा अणु
			sinfo->txrate.mcs = mcs;
		पूर्ण

		sinfo->txrate.bw = RATE_INFO_BW_40;
		sinfo->txrate.flags |= RATE_INFO_FLAGS_MCS;
	पूर्ण अन्यथा अणु
		ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
			   "invalid rate from stats: %d\n", rate);
		ath6kl_debug_war(ar, ATH6KL_WAR_INVALID_RATE);
		वापस 0;
	पूर्ण

	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);

	अगर (test_bit(CONNECTED, &vअगर->flags) &&
	    test_bit(DTIM_PERIOD_AVAIL, &vअगर->flags) &&
	    vअगर->nw_type == INFRA_NETWORK) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_BSS_PARAM);
		sinfo->bss_param.flags = 0;
		sinfo->bss_param.dtim_period = vअगर->assoc_bss_dtim_period;
		sinfo->bss_param.beacon_पूर्णांकerval = vअगर->assoc_bss_beacon_पूर्णांक;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_set_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			    काष्ठा cfg80211_pmksa *pmksa)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(netdev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(netdev);

	वापस ath6kl_wmi_setpmkid_cmd(ar->wmi, vअगर->fw_vअगर_idx, pmksa->bssid,
				       pmksa->pmkid, true);
पूर्ण

अटल पूर्णांक ath6kl_del_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			    काष्ठा cfg80211_pmksa *pmksa)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(netdev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(netdev);

	वापस ath6kl_wmi_setpmkid_cmd(ar->wmi, vअगर->fw_vअगर_idx, pmksa->bssid,
				       pmksa->pmkid, false);
पूर्ण

अटल पूर्णांक ath6kl_flush_pmksa(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(netdev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(netdev);

	अगर (test_bit(CONNECTED, &vअगर->flags))
		वापस ath6kl_wmi_setpmkid_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					       vअगर->bssid, शून्य, false);
	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wow_usr(काष्ठा ath6kl *ar, काष्ठा ath6kl_vअगर *vअगर,
			  काष्ठा cfg80211_wowlan *wow, u32 *filter)
अणु
	पूर्णांक ret, pos;
	u8 mask[WOW_PATTERN_SIZE];
	u16 i;

	/* Configure the patterns that we received from the user. */
	क्रम (i = 0; i < wow->n_patterns; i++) अणु
		/*
		 * Convert given nl80211 specअगरic mask value to equivalent
		 * driver specअगरic mask value and send it to the chip aदीर्घ
		 * with patterns. For example, If the mask value defined in
		 * काष्ठा cfg80211_wowlan is 0xA (equivalent binary is 1010),
		 * then equivalent driver specअगरic mask value is
		 * "0xFF 0x00 0xFF 0x00".
		 */
		स_रखो(&mask, 0, माप(mask));
		क्रम (pos = 0; pos < wow->patterns[i].pattern_len; pos++) अणु
			अगर (wow->patterns[i].mask[pos / 8] & (0x1 << (pos % 8)))
				mask[pos] = 0xFF;
		पूर्ण
		/*
		 * Note: Pattern's offset is not passed as part of wowlan
		 * parameter from CFG layer. So it's always passed as ZERO
		 * to the firmware. It means, given WOW patterns are always
		 * matched from the first byte of received pkt in the firmware.
		 */
		ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
				vअगर->fw_vअगर_idx, WOW_LIST_ID,
				wow->patterns[i].pattern_len,
				0 /* pattern offset */,
				wow->patterns[i].pattern, mask);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (wow->disconnect)
		*filter |= WOW_FILTER_OPTION_NWK_DISASSOC;

	अगर (wow->magic_pkt)
		*filter |= WOW_FILTER_OPTION_MAGIC_PACKET;

	अगर (wow->gtk_rekey_failure)
		*filter |= WOW_FILTER_OPTION_GTK_ERROR;

	अगर (wow->eap_identity_req)
		*filter |= WOW_FILTER_OPTION_EAP_REQ;

	अगर (wow->four_way_handshake)
		*filter |= WOW_FILTER_OPTION_8021X_4WAYHS;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wow_ap(काष्ठा ath6kl *ar, काष्ठा ath6kl_vअगर *vअगर)
अणु
	अटल स्थिर u8 unicst_pattern[] = अणु 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x08 पूर्ण;
	अटल स्थिर u8 unicst_mask[] = अणु 0x01, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x7f पूर्ण;
	u8 unicst_offset = 0;
	अटल स्थिर u8 arp_pattern[] = अणु 0x08, 0x06 पूर्ण;
	अटल स्थिर u8 arp_mask[] = अणु 0xff, 0xff पूर्ण;
	u8 arp_offset = 20;
	अटल स्थिर u8 discvr_pattern[] = अणु 0xe0, 0x00, 0x00, 0xf8 पूर्ण;
	अटल स्थिर u8 discvr_mask[] = अणु 0xf0, 0x00, 0x00, 0xf8 पूर्ण;
	u8 discvr_offset = 38;
	अटल स्थिर u8 dhcp_pattern[] = अणु 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x43 /* port 67 */ पूर्ण;
	अटल स्थिर u8 dhcp_mask[] = अणु 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0xff, 0xff /* port 67 */ पूर्ण;
	u8 dhcp_offset = 0;
	पूर्णांक ret;

	/* Setup unicast IP, EAPOL-like and ARP pkt pattern */
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
			vअगर->fw_vअगर_idx, WOW_LIST_ID,
			माप(unicst_pattern), unicst_offset,
			unicst_pattern, unicst_mask);
	अगर (ret) अणु
		ath6kl_err("failed to add WOW unicast IP pattern\n");
		वापस ret;
	पूर्ण

	/* Setup all ARP pkt pattern */
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
			vअगर->fw_vअगर_idx, WOW_LIST_ID,
			माप(arp_pattern), arp_offset,
			arp_pattern, arp_mask);
	अगर (ret) अणु
		ath6kl_err("failed to add WOW ARP pattern\n");
		वापस ret;
	पूर्ण

	/*
	 * Setup multicast pattern क्रम mDNS 224.0.0.251,
	 * SSDP 239.255.255.250 and LLMNR  224.0.0.252
	 */
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
			vअगर->fw_vअगर_idx, WOW_LIST_ID,
			माप(discvr_pattern), discvr_offset,
			discvr_pattern, discvr_mask);
	अगर (ret) अणु
		ath6kl_err("failed to add WOW mDNS/SSDP/LLMNR pattern\n");
		वापस ret;
	पूर्ण

	/* Setup all DHCP broadcast pkt pattern */
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
			vअगर->fw_vअगर_idx, WOW_LIST_ID,
			माप(dhcp_pattern), dhcp_offset,
			dhcp_pattern, dhcp_mask);
	अगर (ret) अणु
		ath6kl_err("failed to add WOW DHCP broadcast pattern\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wow_sta(काष्ठा ath6kl *ar, काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा net_device *ndev = vअगर->ndev;
	अटल स्थिर u8 discvr_pattern[] = अणु 0xe0, 0x00, 0x00, 0xf8 पूर्ण;
	अटल स्थिर u8 discvr_mask[] = अणु 0xf0, 0x00, 0x00, 0xf8 पूर्ण;
	u8 discvr_offset = 38;
	u8 mac_mask[ETH_ALEN];
	पूर्णांक ret;

	/* Setup unicast pkt pattern */
	eth_broadcast_addr(mac_mask);
	ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
				vअगर->fw_vअगर_idx, WOW_LIST_ID,
				ETH_ALEN, 0, ndev->dev_addr,
				mac_mask);
	अगर (ret) अणु
		ath6kl_err("failed to add WOW unicast pattern\n");
		वापस ret;
	पूर्ण

	/*
	 * Setup multicast pattern क्रम mDNS 224.0.0.251,
	 * SSDP 239.255.255.250 and LLMNR 224.0.0.252
	 */
	अगर ((ndev->flags & IFF_ALLMULTI) ||
	    (ndev->flags & IFF_MULTICAST && netdev_mc_count(ndev) > 0)) अणु
		ret = ath6kl_wmi_add_wow_pattern_cmd(ar->wmi,
				vअगर->fw_vअगर_idx, WOW_LIST_ID,
				माप(discvr_pattern), discvr_offset,
				discvr_pattern, discvr_mask);
		अगर (ret) अणु
			ath6kl_err("failed to add WOW mDNS/SSDP/LLMNR pattern\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is_hsleep_mode_procsed(काष्ठा ath6kl_vअगर *vअगर)
अणु
	वापस test_bit(HOST_SLEEP_MODE_CMD_PROCESSED, &vअगर->flags);
पूर्ण

अटल bool is_ctrl_ep_empty(काष्ठा ath6kl *ar)
अणु
	वापस !ar->tx_pending[ar->ctrl_ep];
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_host_sleep(काष्ठा ath6kl *ar, काष्ठा ath6kl_vअगर *vअगर)
अणु
	पूर्णांक ret, left;

	clear_bit(HOST_SLEEP_MODE_CMD_PROCESSED, &vअगर->flags);

	ret = ath6kl_wmi_set_host_sleep_mode_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						 ATH6KL_HOST_MODE_ASLEEP);
	अगर (ret)
		वापस ret;

	left = रुको_event_पूर्णांकerruptible_समयout(ar->event_wq,
						is_hsleep_mode_procsed(vअगर),
						WMI_TIMEOUT);
	अगर (left == 0) अणु
		ath6kl_warn("timeout, didn't get host sleep cmd processed event\n");
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (left < 0) अणु
		ath6kl_warn("error while waiting for host sleep cmd processed event %d\n",
			    left);
		ret = left;
	पूर्ण

	अगर (ar->tx_pending[ar->ctrl_ep]) अणु
		left = रुको_event_पूर्णांकerruptible_समयout(ar->event_wq,
							is_ctrl_ep_empty(ar),
							WMI_TIMEOUT);
		अगर (left == 0) अणु
			ath6kl_warn("clear wmi ctrl data timeout\n");
			ret = -ETIMEDOUT;
		पूर्ण अन्यथा अगर (left < 0) अणु
			ath6kl_warn("clear wmi ctrl data failed: %d\n", left);
			ret = left;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wow_suspend_vअगर(काष्ठा ath6kl_vअगर *vअगर,
				  काष्ठा cfg80211_wowlan *wow, u32 *filter)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा in_device *in_dev;
	काष्ठा in_अगरaddr *अगरa;
	पूर्णांक ret;
	u16 i, bmiss_समय;
	__be32 ips[MAX_IP_ADDRS];
	u8 index = 0;

	अगर (!test_bit(NETDEV_MCAST_ALL_ON, &vअगर->flags) &&
	    test_bit(ATH6KL_FW_CAPABILITY_WOW_MULTICAST_FILTER,
		     ar->fw_capabilities)) अणु
		ret = ath6kl_wmi_mcast_filter_cmd(vअगर->ar->wmi,
						vअगर->fw_vअगर_idx, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Clear existing WOW patterns */
	क्रम (i = 0; i < WOW_MAX_FILTERS_PER_LIST; i++)
		ath6kl_wmi_del_wow_pattern_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					       WOW_LIST_ID, i);

	/*
	 * Skip the शेष WOW pattern configuration
	 * अगर the driver receives any WOW patterns from
	 * the user.
	 */
	अगर (wow)
		ret = ath6kl_wow_usr(ar, vअगर, wow, filter);
	अन्यथा अगर (vअगर->nw_type == AP_NETWORK)
		ret = ath6kl_wow_ap(ar, vअगर);
	अन्यथा
		ret = ath6kl_wow_sta(ar, vअगर);

	अगर (ret)
		वापस ret;

	netअगर_stop_queue(vअगर->ndev);

	अगर (vअगर->nw_type != AP_NETWORK) अणु
		ret = ath6kl_wmi_listenपूर्णांकerval_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						    ATH6KL_MAX_WOW_LISTEN_INTL,
						    0);
		अगर (ret)
			वापस ret;

		/* Set listen पूर्णांकerval x 15 बार as bmiss समय */
		bmiss_समय = ATH6KL_MAX_WOW_LISTEN_INTL * 15;
		अगर (bmiss_समय > ATH6KL_MAX_BMISS_TIME)
			bmiss_समय = ATH6KL_MAX_BMISS_TIME;

		ret = ath6kl_wmi_bmissसमय_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					       bmiss_समय, 0);
		अगर (ret)
			वापस ret;

		ret = ath6kl_wmi_scanparams_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						0xFFFF, 0, 0xFFFF, 0, 0, 0,
						0, 0, 0, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Setup own IP addr क्रम ARP agent. */
	in_dev = __in_dev_get_rtnl(vअगर->ndev);
	अगर (!in_dev)
		वापस 0;

	अगरa = rtnl_dereference(in_dev->अगरa_list);
	स_रखो(&ips, 0, माप(ips));

	/* Configure IP addr only अगर IP address count < MAX_IP_ADDRS */
	जबतक (index < MAX_IP_ADDRS && अगरa) अणु
		ips[index] = अगरa->अगरa_local;
		अगरa = rtnl_dereference(अगरa->अगरa_next);
		index++;
	पूर्ण

	अगर (अगरa) अणु
		ath6kl_err("total IP addr count is exceeding fw limit\n");
		वापस -EINVAL;
	पूर्ण

	ret = ath6kl_wmi_set_ip_cmd(ar->wmi, vअगर->fw_vअगर_idx, ips[0], ips[1]);
	अगर (ret) अणु
		ath6kl_err("fail to setup ip for arp agent\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_wow_suspend(काष्ठा ath6kl *ar, काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा ath6kl_vअगर *first_vअगर, *vअगर;
	पूर्णांक ret = 0;
	u32 filter = 0;
	bool connected = false;

	/* enter / leave wow suspend on first vअगर always */
	first_vअगर = ath6kl_vअगर_first(ar);
	अगर (WARN_ON(!first_vअगर) ||
	    !ath6kl_cfg80211_पढ़ोy(first_vअगर))
		वापस -EIO;

	अगर (wow && (wow->n_patterns > WOW_MAX_FILTERS_PER_LIST))
		वापस -EINVAL;

	/* install filters क्रम each connected vअगर */
	spin_lock_bh(&ar->list_lock);
	list_क्रम_each_entry(vअगर, &ar->vअगर_list, list) अणु
		अगर (!test_bit(CONNECTED, &vअगर->flags) ||
		    !ath6kl_cfg80211_पढ़ोy(vअगर))
			जारी;
		connected = true;

		ret = ath6kl_wow_suspend_vअगर(vअगर, wow, &filter);
		अगर (ret)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&ar->list_lock);

	अगर (!connected)
		वापस -ENOTCONN;
	अन्यथा अगर (ret)
		वापस ret;

	ar->state = ATH6KL_STATE_SUSPENDING;

	ret = ath6kl_wmi_set_wow_mode_cmd(ar->wmi, first_vअगर->fw_vअगर_idx,
					  ATH6KL_WOW_MODE_ENABLE,
					  filter,
					  WOW_HOST_REQ_DELAY);
	अगर (ret)
		वापस ret;

	वापस ath6kl_cfg80211_host_sleep(ar, first_vअगर);
पूर्ण

अटल पूर्णांक ath6kl_wow_resume_vअगर(काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	पूर्णांक ret;

	अगर (vअगर->nw_type != AP_NETWORK) अणु
		ret = ath6kl_wmi_scanparams_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						0, 0, 0, 0, 0, 0, 3, 0, 0, 0);
		अगर (ret)
			वापस ret;

		ret = ath6kl_wmi_listenपूर्णांकerval_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						    vअगर->listen_पूर्णांकvl_t, 0);
		अगर (ret)
			वापस ret;

		ret = ath6kl_wmi_bmissसमय_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					       vअगर->bmiss_समय_प्रकार, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!test_bit(NETDEV_MCAST_ALL_OFF, &vअगर->flags) &&
	    test_bit(ATH6KL_FW_CAPABILITY_WOW_MULTICAST_FILTER,
		     ar->fw_capabilities)) अणु
		ret = ath6kl_wmi_mcast_filter_cmd(vअगर->ar->wmi,
						  vअगर->fw_vअगर_idx, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	netअगर_wake_queue(vअगर->ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_wow_resume(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_vअगर *vअगर;
	पूर्णांक ret;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (WARN_ON(!vअगर) ||
	    !ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	ar->state = ATH6KL_STATE_RESUMING;

	ret = ath6kl_wmi_set_host_sleep_mode_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						 ATH6KL_HOST_MODE_AWAKE);
	अगर (ret) अणु
		ath6kl_warn("Failed to configure host sleep mode for wow resume: %d\n",
			    ret);
		जाओ cleanup;
	पूर्ण

	spin_lock_bh(&ar->list_lock);
	list_क्रम_each_entry(vअगर, &ar->vअगर_list, list) अणु
		अगर (!test_bit(CONNECTED, &vअगर->flags) ||
		    !ath6kl_cfg80211_पढ़ोy(vअगर))
			जारी;
		ret = ath6kl_wow_resume_vअगर(vअगर);
		अगर (ret)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&ar->list_lock);

	अगर (ret)
		जाओ cleanup;

	ar->state = ATH6KL_STATE_ON;
	वापस 0;

cleanup:
	ar->state = ATH6KL_STATE_WOW;
	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_deepsleep_suspend(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_vअगर *vअगर;
	पूर्णांक ret;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर)
		वापस -EIO;

	अगर (!test_bit(WMI_READY, &ar->flag)) अणु
		ath6kl_err("deepsleep failed as wmi is not ready\n");
		वापस -EIO;
	पूर्ण

	ath6kl_cfg80211_stop_all(ar);

	/* Save the current घातer mode beक्रमe enabling घातer save */
	ar->wmi->saved_pwr_mode = ar->wmi->pwr_mode;

	ret = ath6kl_wmi_घातermode_cmd(ar->wmi, 0, REC_POWER);
	अगर (ret)
		वापस ret;

	/* Disable WOW mode */
	ret = ath6kl_wmi_set_wow_mode_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					  ATH6KL_WOW_MODE_DISABLE,
					  0, 0);
	अगर (ret)
		वापस ret;

	/* Flush all non control pkts in TX path */
	ath6kl_tx_data_cleanup(ar);

	ret = ath6kl_cfg80211_host_sleep(ar, vअगर);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_deepsleep_resume(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_vअगर *vअगर;
	पूर्णांक ret;

	vअगर = ath6kl_vअगर_first(ar);

	अगर (!vअगर)
		वापस -EIO;

	अगर (ar->wmi->pwr_mode != ar->wmi->saved_pwr_mode) अणु
		ret = ath6kl_wmi_घातermode_cmd(ar->wmi, 0,
					       ar->wmi->saved_pwr_mode);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = ath6kl_wmi_set_host_sleep_mode_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						 ATH6KL_HOST_MODE_AWAKE);
	अगर (ret)
		वापस ret;

	ar->state = ATH6KL_STATE_ON;

	/* Reset scan parameter to शेष values */
	ret = ath6kl_wmi_scanparams_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					0, 0, 0, 0, 0, 0, 3, 0, 0, 0);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक ath6kl_cfg80211_suspend(काष्ठा ath6kl *ar,
			    क्रमागत ath6kl_cfg_suspend_mode mode,
			    काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा ath6kl_vअगर *vअगर;
	क्रमागत ath6kl_state prev_state;
	पूर्णांक ret;

	चयन (mode) अणु
	हाल ATH6KL_CFG_SUSPEND_WOW:

		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "wow mode suspend\n");

		/* Flush all non control pkts in TX path */
		ath6kl_tx_data_cleanup(ar);

		prev_state = ar->state;

		ret = ath6kl_wow_suspend(ar, wow);
		अगर (ret) अणु
			ar->state = prev_state;
			वापस ret;
		पूर्ण

		ar->state = ATH6KL_STATE_WOW;
		अवरोध;

	हाल ATH6KL_CFG_SUSPEND_DEEPSLEEP:

		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "deep sleep suspend\n");

		ret = ath6kl_cfg80211_deepsleep_suspend(ar);
		अगर (ret) अणु
			ath6kl_err("deepsleep suspend failed: %d\n", ret);
			वापस ret;
		पूर्ण

		ar->state = ATH6KL_STATE_DEEPSLEEP;

		अवरोध;

	हाल ATH6KL_CFG_SUSPEND_CUTPOWER:

		ath6kl_cfg80211_stop_all(ar);

		अगर (ar->state == ATH6KL_STATE_OFF) अणु
			ath6kl_dbg(ATH6KL_DBG_SUSPEND,
				   "suspend hw off, no action for cutpower\n");
			अवरोध;
		पूर्ण

		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "suspend cutting power\n");

		ret = ath6kl_init_hw_stop(ar);
		अगर (ret) अणु
			ath6kl_warn("failed to stop hw during suspend: %d\n",
				    ret);
		पूर्ण

		ar->state = ATH6KL_STATE_CUTPOWER;

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	list_क्रम_each_entry(vअगर, &ar->vअगर_list, list)
		ath6kl_cfg80211_scan_complete_event(vअगर, true);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath6kl_cfg80211_suspend);

पूर्णांक ath6kl_cfg80211_resume(काष्ठा ath6kl *ar)
अणु
	पूर्णांक ret;

	चयन (ar->state) अणु
	हाल  ATH6KL_STATE_WOW:
		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "wow mode resume\n");

		ret = ath6kl_wow_resume(ar);
		अगर (ret) अणु
			ath6kl_warn("wow mode resume failed: %d\n", ret);
			वापस ret;
		पूर्ण

		अवरोध;

	हाल ATH6KL_STATE_DEEPSLEEP:
		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "deep sleep resume\n");

		ret = ath6kl_cfg80211_deepsleep_resume(ar);
		अगर (ret) अणु
			ath6kl_warn("deep sleep resume failed: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;

	हाल ATH6KL_STATE_CUTPOWER:
		ath6kl_dbg(ATH6KL_DBG_SUSPEND, "resume restoring power\n");

		ret = ath6kl_init_hw_start(ar);
		अगर (ret) अणु
			ath6kl_warn("Failed to boot hw in resume: %d\n", ret);
			वापस ret;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath6kl_cfg80211_resume);

#अगर_घोषित CONFIG_PM

/* hअगर layer decides what suspend mode to use */
अटल पूर्णांक __ath6kl_cfg80211_suspend(काष्ठा wiphy *wiphy,
				 काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा ath6kl *ar = wiphy_priv(wiphy);

	ath6kl_recovery_suspend(ar);

	वापस ath6kl_hअगर_suspend(ar, wow);
पूर्ण

अटल पूर्णांक __ath6kl_cfg80211_resume(काष्ठा wiphy *wiphy)
अणु
	काष्ठा ath6kl *ar = wiphy_priv(wiphy);
	पूर्णांक err;

	err = ath6kl_hअगर_resume(ar);
	अगर (err)
		वापस err;

	ath6kl_recovery_resume(ar);

	वापस 0;
पूर्ण

/*
 * FIXME: WOW suspend mode is selected अगर the host sdio controller supports
 * both sdio irq wake up and keep घातer. The target pulls sdio data line to
 * wake up the host when WOW pattern matches. This causes sdio irq handler
 * is being called in the host side which पूर्णांकernally hits ath6kl's RX path.
 *
 * Since sdio पूर्णांकerrupt is not disabled, RX path executes even beक्रमe
 * the host executes the actual resume operation from PM module.
 *
 * In the current scenario, WOW resume should happen beक्रमe start processing
 * any data from the target. So It's required to perक्रमm WOW resume in RX path.
 * Ideally we should perक्रमm WOW resume only in the actual platक्रमm
 * resume path. This area needs bit rework to aव्योम WOW resume in RX path.
 *
 * ath6kl_check_wow_status() is called from ath6kl_rx().
 */
व्योम ath6kl_check_wow_status(काष्ठा ath6kl *ar)
अणु
	अगर (ar->state == ATH6KL_STATE_SUSPENDING)
		वापस;

	अगर (ar->state == ATH6KL_STATE_WOW)
		ath6kl_cfg80211_resume(ar);
पूर्ण

#अन्यथा

व्योम ath6kl_check_wow_status(काष्ठा ath6kl *ar)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ath6kl_set_htcap(काष्ठा ath6kl_vअगर *vअगर, क्रमागत nl80211_band band,
			    bool ht_enable)
अणु
	काष्ठा ath6kl_htcap *htcap = &vअगर->htcap[band];

	अगर (htcap->ht_enable == ht_enable)
		वापस 0;

	अगर (ht_enable) अणु
		/* Set शेष ht capabilities */
		htcap->ht_enable = true;
		htcap->cap_info = (band == NL80211_BAND_2GHZ) ?
				   ath6kl_g_htcap : ath6kl_a_htcap;
		htcap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_16K;
	पूर्ण अन्यथा /* Disable ht */
		स_रखो(htcap, 0, माप(*htcap));

	वापस ath6kl_wmi_set_htcap_cmd(vअगर->ar->wmi, vअगर->fw_vअगर_idx,
					band, htcap);
पूर्ण

अटल पूर्णांक ath6kl_restore_htcap(काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा wiphy *wiphy = vअगर->ar->wiphy;
	पूर्णांक band, ret = 0;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!wiphy->bands[band])
			जारी;

		ret = ath6kl_set_htcap(vअगर, band,
				wiphy->bands[band]->ht_cap.ht_supported);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool ath6kl_is_p2p_ie(स्थिर u8 *pos)
अणु
	वापस pos[0] == WLAN_EID_VENDOR_SPECIFIC && pos[1] >= 4 &&
		pos[2] == 0x50 && pos[3] == 0x6f &&
		pos[4] == 0x9a && pos[5] == 0x09;
पूर्ण

अटल पूर्णांक ath6kl_set_ap_probe_resp_ies(काष्ठा ath6kl_vअगर *vअगर,
					स्थिर u8 *ies, माप_प्रकार ies_len)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	स्थिर u8 *pos;
	u8 *buf = शून्य;
	माप_प्रकार len = 0;
	पूर्णांक ret;

	/*
	 * Filter out P2P IE(s) since they will be included depending on
	 * the Probe Request frame in ath6kl_send_go_probe_resp().
	 */

	अगर (ies && ies_len) अणु
		buf = kदो_स्मृति(ies_len, GFP_KERNEL);
		अगर (buf == शून्य)
			वापस -ENOMEM;
		pos = ies;
		जबतक (pos + 1 < ies + ies_len) अणु
			अगर (pos + 2 + pos[1] > ies + ies_len)
				अवरोध;
			अगर (!ath6kl_is_p2p_ie(pos)) अणु
				स_नकल(buf + len, pos, 2 + pos[1]);
				len += 2 + pos[1];
			पूर्ण
			pos += 2 + pos[1];
		पूर्ण
	पूर्ण

	ret = ath6kl_wmi_set_appie_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				       WMI_FRAME_PROBE_RESP, buf, len);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक ath6kl_set_ies(काष्ठा ath6kl_vअगर *vअगर,
			  काष्ठा cfg80211_beacon_data *info)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	पूर्णांक res;

	/* this also clears IE in fw अगर it's not set */
	res = ath6kl_wmi_set_appie_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				       WMI_FRAME_BEACON,
				       info->beacon_ies,
				       info->beacon_ies_len);
	अगर (res)
		वापस res;

	/* this also clears IE in fw अगर it's not set */
	res = ath6kl_set_ap_probe_resp_ies(vअगर, info->proberesp_ies,
					   info->proberesp_ies_len);
	अगर (res)
		वापस res;

	/* this also clears IE in fw अगर it's not set */
	res = ath6kl_wmi_set_appie_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				       WMI_FRAME_ASSOC_RESP,
				       info->assocresp_ies,
				       info->assocresp_ies_len);
	अगर (res)
		वापस res;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_get_rsn_capab(काष्ठा cfg80211_beacon_data *beacon,
				u8 *rsn_capab)
अणु
	स्थिर u8 *rsn_ie;
	माप_प्रकार rsn_ie_len;
	u16 cnt;

	अगर (!beacon->tail)
		वापस -EINVAL;

	rsn_ie = cfg80211_find_ie(WLAN_EID_RSN, beacon->tail, beacon->tail_len);
	अगर (!rsn_ie)
		वापस -EINVAL;

	rsn_ie_len = *(rsn_ie + 1);
	/* skip element id and length */
	rsn_ie += 2;

	/* skip version */
	अगर (rsn_ie_len < 2)
		वापस -EINVAL;
	rsn_ie +=  2;
	rsn_ie_len -= 2;

	/* skip group cipher suite */
	अगर (rsn_ie_len < 4)
		वापस 0;
	rsn_ie +=  4;
	rsn_ie_len -= 4;

	/* skip pairwise cipher suite */
	अगर (rsn_ie_len < 2)
		वापस 0;
	cnt = get_unaligned_le16(rsn_ie);
	rsn_ie += (2 + cnt * 4);
	rsn_ie_len -= (2 + cnt * 4);

	/* skip akm suite */
	अगर (rsn_ie_len < 2)
		वापस 0;
	cnt = get_unaligned_le16(rsn_ie);
	rsn_ie += (2 + cnt * 4);
	rsn_ie_len -= (2 + cnt * 4);

	अगर (rsn_ie_len < 2)
		वापस 0;

	स_नकल(rsn_capab, rsn_ie, 2);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_start_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   काष्ठा cfg80211_ap_settings *info)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	काष्ठा ieee80211_mgmt *mgmt;
	bool hidden = false;
	u8 *ies;
	काष्ठा wmi_connect_cmd p;
	पूर्णांक res;
	पूर्णांक i, ret;
	u16 rsn_capab = 0;
	पूर्णांक inactivity_समयout = 0;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG, "%s:\n", __func__);

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (vअगर->next_mode != AP_NETWORK)
		वापस -EOPNOTSUPP;

	res = ath6kl_set_ies(vअगर, &info->beacon);

	ar->ap_mode_bkey.valid = false;

	ret = ath6kl_wmi_ap_set_beacon_पूर्णांकvl_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						 info->beacon_पूर्णांकerval);

	अगर (ret)
		ath6kl_warn("Failed to set beacon interval: %d\n", ret);

	ret = ath6kl_wmi_ap_set_dtim_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					 info->dtim_period);

	/* ignore error, just prपूर्णांक a warning and जारी normally */
	अगर (ret)
		ath6kl_warn("Failed to set dtim_period in beacon: %d\n", ret);

	अगर (info->beacon.head == शून्य)
		वापस -EINVAL;
	mgmt = (काष्ठा ieee80211_mgmt *) info->beacon.head;
	ies = mgmt->u.beacon.variable;
	अगर (ies > info->beacon.head + info->beacon.head_len)
		वापस -EINVAL;

	अगर (info->ssid == शून्य)
		वापस -EINVAL;
	स_नकल(vअगर->ssid, info->ssid, info->ssid_len);
	vअगर->ssid_len = info->ssid_len;
	अगर (info->hidden_ssid != NL80211_HIDDEN_SSID_NOT_IN_USE)
		hidden = true;

	res = ath6kl_wmi_ap_hidden_ssid(ar->wmi, vअगर->fw_vअगर_idx, hidden);
	अगर (res)
		वापस res;

	ret = ath6kl_set_auth_type(vअगर, info->auth_type);
	अगर (ret)
		वापस ret;

	स_रखो(&p, 0, माप(p));

	क्रम (i = 0; i < info->crypto.n_akm_suites; i++) अणु
		चयन (info->crypto.akm_suites[i]) अणु
		हाल WLAN_AKM_SUITE_8021X:
			अगर (info->crypto.wpa_versions & NL80211_WPA_VERSION_1)
				p.auth_mode |= WPA_AUTH;
			अगर (info->crypto.wpa_versions & NL80211_WPA_VERSION_2)
				p.auth_mode |= WPA2_AUTH;
			अवरोध;
		हाल WLAN_AKM_SUITE_PSK:
			अगर (info->crypto.wpa_versions & NL80211_WPA_VERSION_1)
				p.auth_mode |= WPA_PSK_AUTH;
			अगर (info->crypto.wpa_versions & NL80211_WPA_VERSION_2)
				p.auth_mode |= WPA2_PSK_AUTH;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (p.auth_mode == 0)
		p.auth_mode = NONE_AUTH;
	vअगर->auth_mode = p.auth_mode;

	क्रम (i = 0; i < info->crypto.n_ciphers_pairwise; i++) अणु
		चयन (info->crypto.ciphers_pairwise[i]) अणु
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			p.prwise_crypto_type |= WEP_CRYPT;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			p.prwise_crypto_type |= TKIP_CRYPT;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			p.prwise_crypto_type |= AES_CRYPT;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_SMS4:
			p.prwise_crypto_type |= WAPI_CRYPT;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (p.prwise_crypto_type == 0) अणु
		p.prwise_crypto_type = NONE_CRYPT;
		ath6kl_set_cipher(vअगर, 0, true);
	पूर्ण अन्यथा अगर (info->crypto.n_ciphers_pairwise == 1) अणु
		ath6kl_set_cipher(vअगर, info->crypto.ciphers_pairwise[0], true);
	पूर्ण

	चयन (info->crypto.cipher_group) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		p.grp_crypto_type = WEP_CRYPT;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		p.grp_crypto_type = TKIP_CRYPT;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		p.grp_crypto_type = AES_CRYPT;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_SMS4:
		p.grp_crypto_type = WAPI_CRYPT;
		अवरोध;
	शेष:
		p.grp_crypto_type = NONE_CRYPT;
		अवरोध;
	पूर्ण
	ath6kl_set_cipher(vअगर, info->crypto.cipher_group, false);

	p.nw_type = AP_NETWORK;
	vअगर->nw_type = vअगर->next_mode;

	p.ssid_len = vअगर->ssid_len;
	स_नकल(p.ssid, vअगर->ssid, vअगर->ssid_len);
	p.करोt11_auth_mode = vअगर->करोt11_auth_mode;
	p.ch = cpu_to_le16(info->chandef.chan->center_freq);

	/* Enable uAPSD support by शेष */
	res = ath6kl_wmi_ap_set_apsd(ar->wmi, vअगर->fw_vअगर_idx, true);
	अगर (res < 0)
		वापस res;

	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_P2P_GO) अणु
		p.nw_subtype = SUBTYPE_P2PGO;
	पूर्ण अन्यथा अणु
		/*
		 * Due to firmware limitation, it is not possible to
		 * करो P2P mgmt operations in AP mode
		 */
		p.nw_subtype = SUBTYPE_NONE;
	पूर्ण

	अगर (info->inactivity_समयout) अणु
		inactivity_समयout = info->inactivity_समयout;

		अगर (test_bit(ATH6KL_FW_CAPABILITY_AP_INACTIVITY_MINS,
			     ar->fw_capabilities))
			inactivity_समयout = DIV_ROUND_UP(inactivity_समयout,
							  60);

		res = ath6kl_wmi_set_inact_period(ar->wmi, vअगर->fw_vअगर_idx,
						  inactivity_समयout);
		अगर (res < 0)
			वापस res;
	पूर्ण

	अगर (ath6kl_set_htcap(vअगर, info->chandef.chan->band,
			     cfg80211_get_chandef_type(&info->chandef)
					!= NL80211_CHAN_NO_HT))
		वापस -EIO;

	/*
	 * Get the PTKSA replay counter in the RSN IE. Supplicant
	 * will use the RSN IE in M3 message and firmware has to
	 * advertise the same in beacon/probe response. Send
	 * the complete RSN IE capability field to firmware
	 */
	अगर (!ath6kl_get_rsn_capab(&info->beacon, (u8 *) &rsn_capab) &&
	    test_bit(ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE,
		     ar->fw_capabilities)) अणु
		res = ath6kl_wmi_set_ie_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					    WLAN_EID_RSN, WMI_RSN_IE_CAPB,
					    (स्थिर u8 *) &rsn_capab,
					    माप(rsn_capab));
		vअगर->rsn_capab = rsn_capab;
		अगर (res < 0)
			वापस res;
	पूर्ण

	स_नकल(&vअगर->profile, &p, माप(p));
	res = ath6kl_wmi_ap_profile_commit(ar->wmi, vअगर->fw_vअगर_idx, &p);
	अगर (res < 0)
		वापस res;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_change_beacon(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				काष्ठा cfg80211_beacon_data *beacon)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	अगर (!ath6kl_cfg80211_पढ़ोy(vअगर))
		वापस -EIO;

	अगर (vअगर->next_mode != AP_NETWORK)
		वापस -EOPNOTSUPP;

	वापस ath6kl_set_ies(vअगर, beacon);
पूर्ण

अटल पूर्णांक ath6kl_stop_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	अगर (vअगर->nw_type != AP_NETWORK)
		वापस -EOPNOTSUPP;
	अगर (!test_bit(CONNECTED, &vअगर->flags))
		वापस -ENOTCONN;

	ath6kl_wmi_disconnect_cmd(ar->wmi, vअगर->fw_vअगर_idx);
	clear_bit(CONNECTED, &vअगर->flags);
	netअगर_carrier_off(vअगर->ndev);

	/* Restore ht setting in firmware */
	वापस ath6kl_restore_htcap(vअगर);
पूर्ण

अटल स्थिर u8 bcast_addr[ETH_ALEN] = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

अटल पूर्णांक ath6kl_del_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      काष्ठा station_del_parameters *params)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	स्थिर u8 *addr = params->mac ? params->mac : bcast_addr;

	वापस ath6kl_wmi_ap_set_mlme(ar->wmi, vअगर->fw_vअगर_idx, WMI_AP_DEAUTH,
				      addr, WLAN_REASON_PREV_AUTH_NOT_VALID);
पूर्ण

अटल पूर्णांक ath6kl_change_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 स्थिर u8 *mac,
				 काष्ठा station_parameters *params)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	पूर्णांक err;

	अगर (vअगर->nw_type != AP_NETWORK)
		वापस -EOPNOTSUPP;

	err = cfg80211_check_station_change(wiphy, params,
					    CFG80211_STA_AP_MLME_CLIENT);
	अगर (err)
		वापस err;

	अगर (params->sta_flags_set & BIT(NL80211_STA_FLAG_AUTHORIZED))
		वापस ath6kl_wmi_ap_set_mlme(ar->wmi, vअगर->fw_vअगर_idx,
					      WMI_AP_MLME_AUTHORIZE, mac, 0);
	वापस ath6kl_wmi_ap_set_mlme(ar->wmi, vअगर->fw_vअगर_idx,
				      WMI_AP_MLME_UNAUTHORIZE, mac, 0);
पूर्ण

अटल पूर्णांक ath6kl_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
				    काष्ठा wireless_dev *wdev,
				    काष्ठा ieee80211_channel *chan,
				    अचिन्हित पूर्णांक duration,
				    u64 *cookie)
अणु
	काष्ठा ath6kl_vअगर *vअगर = ath6kl_vअगर_from_wdev(wdev);
	काष्ठा ath6kl *ar = ath6kl_priv(vअगर->ndev);
	u32 id;

	/* TODO: अगर alपढ़ोy pending or ongoing reमुख्य-on-channel,
	 * वापस -EBUSY */
	id = ++vअगर->last_roc_id;
	अगर (id == 0) अणु
		/* Do not use 0 as the cookie value */
		id = ++vअगर->last_roc_id;
	पूर्ण
	*cookie = id;

	वापस ath6kl_wmi_reमुख्य_on_chnl_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					     chan->center_freq, duration);
पूर्ण

अटल पूर्णांक ath6kl_cancel_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
					   काष्ठा wireless_dev *wdev,
					   u64 cookie)
अणु
	काष्ठा ath6kl_vअगर *vअगर = ath6kl_vअगर_from_wdev(wdev);
	काष्ठा ath6kl *ar = ath6kl_priv(vअगर->ndev);

	अगर (cookie != vअगर->last_roc_id)
		वापस -ENOENT;
	vअगर->last_cancel_roc_id = cookie;

	वापस ath6kl_wmi_cancel_reमुख्य_on_chnl_cmd(ar->wmi, vअगर->fw_vअगर_idx);
पूर्ण

अटल पूर्णांक ath6kl_send_go_probe_resp(काष्ठा ath6kl_vअगर *vअगर,
				     स्थिर u8 *buf, माप_प्रकार len,
				     अचिन्हित पूर्णांक freq)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	स्थिर u8 *pos;
	u8 *p2p;
	पूर्णांक p2p_len;
	पूर्णांक ret;
	स्थिर काष्ठा ieee80211_mgmt *mgmt;

	mgmt = (स्थिर काष्ठा ieee80211_mgmt *) buf;

	/* Include P2P IE(s) from the frame generated in user space. */

	p2p = kदो_स्मृति(len, GFP_KERNEL);
	अगर (p2p == शून्य)
		वापस -ENOMEM;
	p2p_len = 0;

	pos = mgmt->u.probe_resp.variable;
	जबतक (pos + 1 < buf + len) अणु
		अगर (pos + 2 + pos[1] > buf + len)
			अवरोध;
		अगर (ath6kl_is_p2p_ie(pos)) अणु
			स_नकल(p2p + p2p_len, pos, 2 + pos[1]);
			p2p_len += 2 + pos[1];
		पूर्ण
		pos += 2 + pos[1];
	पूर्ण

	ret = ath6kl_wmi_send_probe_response_cmd(ar->wmi, vअगर->fw_vअगर_idx, freq,
						 mgmt->da, p2p, p2p_len);
	kमुक्त(p2p);
	वापस ret;
पूर्ण

अटल bool ath6kl_mgmt_घातersave_ap(काष्ठा ath6kl_vअगर *vअगर,
				     u32 id,
				     u32 freq,
				     u32 रुको,
				     स्थिर u8 *buf,
				     माप_प्रकार len,
				     bool *more_data,
				     bool no_cck)
अणु
	काष्ठा ieee80211_mgmt *mgmt;
	काष्ठा ath6kl_sta *conn;
	bool is_psq_empty = false;
	काष्ठा ath6kl_mgmt_buff *mgmt_buf;
	माप_प्रकार mgmt_buf_size;
	काष्ठा ath6kl *ar = vअगर->ar;

	mgmt = (काष्ठा ieee80211_mgmt *) buf;
	अगर (is_multicast_ether_addr(mgmt->da))
		वापस false;

	conn = ath6kl_find_sta(vअगर, mgmt->da);
	अगर (!conn)
		वापस false;

	अगर (conn->sta_flags & STA_PS_SLEEP) अणु
		अगर (!(conn->sta_flags & STA_PS_POLLED)) अणु
			/* Queue the frames अगर the STA is sleeping */
			mgmt_buf_size = len + माप(काष्ठा ath6kl_mgmt_buff);
			mgmt_buf = kदो_स्मृति(mgmt_buf_size, GFP_KERNEL);
			अगर (!mgmt_buf)
				वापस false;

			INIT_LIST_HEAD(&mgmt_buf->list);
			mgmt_buf->id = id;
			mgmt_buf->freq = freq;
			mgmt_buf->रुको = रुको;
			mgmt_buf->len = len;
			mgmt_buf->no_cck = no_cck;
			स_नकल(mgmt_buf->buf, buf, len);
			spin_lock_bh(&conn->psq_lock);
			is_psq_empty = skb_queue_empty(&conn->psq) &&
					(conn->mgmt_psq_len == 0);
			list_add_tail(&mgmt_buf->list, &conn->mgmt_psq);
			conn->mgmt_psq_len++;
			spin_unlock_bh(&conn->psq_lock);

			/*
			 * If this is the first pkt getting queued
			 * क्रम this STA, update the PVB क्रम this
			 * STA.
			 */
			अगर (is_psq_empty)
				ath6kl_wmi_set_pvb_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						       conn->aid, 1);
			वापस true;
		पूर्ण

		/*
		 * This tx is because of a PsPoll.
		 * Determine अगर MoreData bit has to be set.
		 */
		spin_lock_bh(&conn->psq_lock);
		अगर (!skb_queue_empty(&conn->psq) || (conn->mgmt_psq_len != 0))
			*more_data = true;
		spin_unlock_bh(&conn->psq_lock);
	पूर्ण

	वापस false;
पूर्ण

/* Check अगर SSID length is greater than सूचीECT- */
अटल bool ath6kl_is_p2p_go_ssid(स्थिर u8 *buf, माप_प्रकार len)
अणु
	स्थिर काष्ठा ieee80211_mgmt *mgmt;
	mgmt = (स्थिर काष्ठा ieee80211_mgmt *) buf;

	/* variable[1] contains the SSID tag length */
	अगर (buf + len >= &mgmt->u.probe_resp.variable[1] &&
	    (mgmt->u.probe_resp.variable[1] > P2P_WILDCARD_SSID_LEN)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ath6kl_mgmt_tx(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			  काष्ठा cfg80211_mgmt_tx_params *params, u64 *cookie)
अणु
	काष्ठा ath6kl_vअगर *vअगर = ath6kl_vअगर_from_wdev(wdev);
	काष्ठा ath6kl *ar = ath6kl_priv(vअगर->ndev);
	काष्ठा ieee80211_channel *chan = params->chan;
	स्थिर u8 *buf = params->buf;
	माप_प्रकार len = params->len;
	अचिन्हित पूर्णांक रुको = params->रुको;
	bool no_cck = params->no_cck;
	u32 id, freq;
	स्थिर काष्ठा ieee80211_mgmt *mgmt;
	bool more_data, queued;

	/* शेष to the current channel, but use the one specअगरied as argument
	 * अगर any
	 */
	freq = vअगर->ch_hपूर्णांक;
	अगर (chan)
		freq = chan->center_freq;

	/* never send freq zero to the firmware */
	अगर (WARN_ON(freq == 0))
		वापस -EINVAL;

	mgmt = (स्थिर काष्ठा ieee80211_mgmt *) buf;
	अगर (vअगर->nw_type == AP_NETWORK && test_bit(CONNECTED, &vअगर->flags) &&
	    ieee80211_is_probe_resp(mgmt->frame_control) &&
	    ath6kl_is_p2p_go_ssid(buf, len)) अणु
		/*
		 * Send Probe Response frame in GO mode using a separate WMI
		 * command to allow the target to fill in the generic IEs.
		 */
		*cookie = 0; /* TX status not supported */
		वापस ath6kl_send_go_probe_resp(vअगर, buf, len, freq);
	पूर्ण

	id = vअगर->send_action_id++;
	अगर (id == 0) अणु
		/*
		 * 0 is a reserved value in the WMI command and shall not be
		 * used क्रम the command.
		 */
		id = vअगर->send_action_id++;
	पूर्ण

	*cookie = id;

	/* AP mode Power saving processing */
	अगर (vअगर->nw_type == AP_NETWORK) अणु
		queued = ath6kl_mgmt_घातersave_ap(vअगर, id, freq, रुको, buf, len,
						  &more_data, no_cck);
		अगर (queued)
			वापस 0;
	पूर्ण

	वापस ath6kl_wmi_send_mgmt_cmd(ar->wmi, vअगर->fw_vअगर_idx, id, freq,
					रुको, buf, len, no_cck);
पूर्ण

अटल पूर्णांक ath6kl_get_antenna(काष्ठा wiphy *wiphy,
			      u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा ath6kl *ar = wiphy_priv(wiphy);
	*tx_ant = ar->hw.tx_ant;
	*rx_ant = ar->hw.rx_ant;
	वापस 0;
पूर्ण

अटल व्योम ath6kl_update_mgmt_frame_registrations(काष्ठा wiphy *wiphy,
						   काष्ठा wireless_dev *wdev,
						   काष्ठा mgmt_frame_regs *upd)
अणु
	काष्ठा ath6kl_vअगर *vअगर = ath6kl_vअगर_from_wdev(wdev);

	/*
	 * FIXME: send WMI_PROBE_REQ_REPORT_CMD here instead of hardcoding
	 *	  the reporting in the target all the समय, this callback
	 *	  *is* allowed to sleep after all.
	 */
	vअगर->probe_req_report =
		upd->पूर्णांकerface_stypes & BIT(IEEE80211_STYPE_PROBE_REQ >> 4);
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_sscan_start(काष्ठा wiphy *wiphy,
			काष्ठा net_device *dev,
			काष्ठा cfg80211_sched_scan_request *request)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	u16 पूर्णांकerval;
	पूर्णांक ret, rssi_thold;
	पूर्णांक n_match_sets = request->n_match_sets;

	/*
	 * If there's a matchset w/o an SSID, then assume it's just क्रम
	 * the RSSI (nothing अन्यथा is currently supported) and ignore it.
	 * The device only supports a global RSSI filter that we set below.
	 */
	अगर (n_match_sets == 1 && !request->match_sets[0].ssid.ssid_len)
		n_match_sets = 0;

	अगर (ar->state != ATH6KL_STATE_ON)
		वापस -EIO;

	अगर (vअगर->sme_state != SME_DISCONNECTED)
		वापस -EBUSY;

	ath6kl_cfg80211_scan_complete_event(vअगर, true);

	ret = ath6kl_set_probed_ssids(ar, vअगर, request->ssids,
				      request->n_ssids,
				      request->match_sets,
				      n_match_sets);
	अगर (ret < 0)
		वापस ret;

	अगर (!n_match_sets) अणु
		ret = ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
					       ALL_BSS_FILTER, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		 ret = ath6kl_wmi_bssfilter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						MATCHED_SSID_FILTER, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (test_bit(ATH6KL_FW_CAPABILITY_RSSI_SCAN_THOLD,
		     ar->fw_capabilities)) अणु
		अगर (request->min_rssi_thold <= NL80211_SCAN_RSSI_THOLD_OFF)
			rssi_thold = 0;
		अन्यथा अगर (request->min_rssi_thold < -127)
			rssi_thold = -127;
		अन्यथा
			rssi_thold = request->min_rssi_thold;

		ret = ath6kl_wmi_set_rssi_filter_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						     rssi_thold);
		अगर (ret) अणु
			ath6kl_err("failed to set RSSI threshold for scan\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* fw uses seconds, also make sure that it's >0 */
	पूर्णांकerval = max_t(u16, 1, request->scan_plans[0].पूर्णांकerval);

	ath6kl_wmi_scanparams_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				  पूर्णांकerval, पूर्णांकerval,
				  vअगर->bg_scan_period, 0, 0, 0, 3, 0, 0, 0);

	/* this also clears IE in fw अगर it's not set */
	ret = ath6kl_wmi_set_appie_cmd(ar->wmi, vअगर->fw_vअगर_idx,
				       WMI_FRAME_PROBE_REQ,
				       request->ie, request->ie_len);
	अगर (ret) अणु
		ath6kl_warn("Failed to set probe request IE for scheduled scan: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	ret = ath6kl_wmi_enable_sched_scan_cmd(ar->wmi, vअगर->fw_vअगर_idx, true);
	अगर (ret)
		वापस ret;

	set_bit(SCHED_SCANNING, &vअगर->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_sscan_stop(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev, u64 reqid)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	bool stopped;

	stopped = __ath6kl_cfg80211_sscan_stop(vअगर);

	अगर (!stopped)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_set_bitrate(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *dev,
				       स्थिर u8 *addr,
				       स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	वापस ath6kl_wmi_set_bitrate_mask(ar->wmi, vअगर->fw_vअगर_idx,
					   mask);
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_set_txe_config(काष्ठा wiphy *wiphy,
					  काष्ठा net_device *dev,
					  u32 rate, u32 pkts, u32 पूर्णांकvl)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);

	अगर (vअगर->nw_type != INFRA_NETWORK ||
	    !test_bit(ATH6KL_FW_CAPABILITY_TX_ERR_NOTIFY, ar->fw_capabilities))
		वापस -EOPNOTSUPP;

	अगर (vअगर->sme_state != SME_CONNECTED)
		वापस -ENOTCONN;

	/* save this since the firmware won't report the पूर्णांकerval */
	vअगर->txe_पूर्णांकvl = पूर्णांकvl;

	वापस ath6kl_wmi_set_txe_notअगरy(ar->wmi, vअगर->fw_vअगर_idx,
					 rate, pkts, पूर्णांकvl);
पूर्ण

अटल स्थिर काष्ठा ieee80211_txrx_stypes
ath6kl_mgmt_stypes[NUM_NL80211_IFTYPES] = अणु
	[NL80211_IFTYPE_STATION] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_AP] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_CLIENT] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_GO] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
पूर्ण;

अटल काष्ठा cfg80211_ops ath6kl_cfg80211_ops = अणु
	.add_भव_पूर्णांकf = ath6kl_cfg80211_add_अगरace,
	.del_भव_पूर्णांकf = ath6kl_cfg80211_del_अगरace,
	.change_भव_पूर्णांकf = ath6kl_cfg80211_change_अगरace,
	.scan = ath6kl_cfg80211_scan,
	.connect = ath6kl_cfg80211_connect,
	.disconnect = ath6kl_cfg80211_disconnect,
	.add_key = ath6kl_cfg80211_add_key,
	.get_key = ath6kl_cfg80211_get_key,
	.del_key = ath6kl_cfg80211_del_key,
	.set_शेष_key = ath6kl_cfg80211_set_शेष_key,
	.set_wiphy_params = ath6kl_cfg80211_set_wiphy_params,
	.set_tx_घातer = ath6kl_cfg80211_set_txघातer,
	.get_tx_घातer = ath6kl_cfg80211_get_txघातer,
	.set_घातer_mgmt = ath6kl_cfg80211_set_घातer_mgmt,
	.join_ibss = ath6kl_cfg80211_join_ibss,
	.leave_ibss = ath6kl_cfg80211_leave_ibss,
	.get_station = ath6kl_get_station,
	.set_pmksa = ath6kl_set_pmksa,
	.del_pmksa = ath6kl_del_pmksa,
	.flush_pmksa = ath6kl_flush_pmksa,
	CFG80211_TESTMODE_CMD(ath6kl_पंचांग_cmd)
#अगर_घोषित CONFIG_PM
	.suspend = __ath6kl_cfg80211_suspend,
	.resume = __ath6kl_cfg80211_resume,
#पूर्ण_अगर
	.start_ap = ath6kl_start_ap,
	.change_beacon = ath6kl_change_beacon,
	.stop_ap = ath6kl_stop_ap,
	.del_station = ath6kl_del_station,
	.change_station = ath6kl_change_station,
	.reमुख्य_on_channel = ath6kl_reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel = ath6kl_cancel_reमुख्य_on_channel,
	.mgmt_tx = ath6kl_mgmt_tx,
	.update_mgmt_frame_registrations =
		ath6kl_update_mgmt_frame_registrations,
	.get_antenna = ath6kl_get_antenna,
	.sched_scan_start = ath6kl_cfg80211_sscan_start,
	.sched_scan_stop = ath6kl_cfg80211_sscan_stop,
	.set_bitrate_mask = ath6kl_cfg80211_set_bitrate,
	.set_cqm_txe_config = ath6kl_cfg80211_set_txe_config,
पूर्ण;

व्योम ath6kl_cfg80211_stop(काष्ठा ath6kl_vअगर *vअगर)
अणु
	ath6kl_cfg80211_sscan_disable(vअगर);

	चयन (vअगर->sme_state) अणु
	हाल SME_DISCONNECTED:
		अवरोध;
	हाल SME_CONNECTING:
		cfg80211_connect_result(vअगर->ndev, vअगर->bssid, शून्य, 0,
					शून्य, 0,
					WLAN_STATUS_UNSPECIFIED_FAILURE,
					GFP_KERNEL);
		अवरोध;
	हाल SME_CONNECTED:
		cfg80211_disconnected(vअगर->ndev, 0, शून्य, 0, true, GFP_KERNEL);
		अवरोध;
	पूर्ण

	अगर (vअगर->ar->state != ATH6KL_STATE_RECOVERY &&
	    (test_bit(CONNECTED, &vअगर->flags) ||
	    test_bit(CONNECT_PEND, &vअगर->flags)))
		ath6kl_wmi_disconnect_cmd(vअगर->ar->wmi, vअगर->fw_vअगर_idx);

	vअगर->sme_state = SME_DISCONNECTED;
	clear_bit(CONNECTED, &vअगर->flags);
	clear_bit(CONNECT_PEND, &vअगर->flags);

	/* Stop netdev queues, needed during recovery */
	netअगर_stop_queue(vअगर->ndev);
	netअगर_carrier_off(vअगर->ndev);

	/* disable scanning */
	अगर (vअगर->ar->state != ATH6KL_STATE_RECOVERY &&
	    ath6kl_wmi_scanparams_cmd(vअगर->ar->wmi, vअगर->fw_vअगर_idx, 0xFFFF,
				      0, 0, 0, 0, 0, 0, 0, 0, 0) != 0)
		ath6kl_warn("failed to disable scan during stop\n");

	ath6kl_cfg80211_scan_complete_event(vअगर, true);
पूर्ण

व्योम ath6kl_cfg80211_stop_all(काष्ठा ath6kl *ar)
अणु
	काष्ठा ath6kl_vअगर *vअगर;

	vअगर = ath6kl_vअगर_first(ar);
	अगर (!vअगर && ar->state != ATH6KL_STATE_RECOVERY) अणु
		/* save the current घातer mode beक्रमe enabling घातer save */
		ar->wmi->saved_pwr_mode = ar->wmi->pwr_mode;

		अगर (ath6kl_wmi_घातermode_cmd(ar->wmi, 0, REC_POWER) != 0)
			ath6kl_warn("ath6kl_deep_sleep_enable: wmi_powermode_cmd failed\n");
		वापस;
	पूर्ण

	/*
	 * FIXME: we should take ar->list_lock to protect changes in the
	 * vअगर_list, but that's not trivial to करो as ath6kl_cfg80211_stop()
	 * sleeps.
	 */
	list_क्रम_each_entry(vअगर, &ar->vअगर_list, list)
		ath6kl_cfg80211_stop(vअगर);
पूर्ण

अटल व्योम ath6kl_cfg80211_reg_notअगरy(काष्ठा wiphy *wiphy,
				       काष्ठा regulatory_request *request)
अणु
	काष्ठा ath6kl *ar = wiphy_priv(wiphy);
	u32 rates[NUM_NL80211_BANDS];
	पूर्णांक ret, i;

	ath6kl_dbg(ATH6KL_DBG_WLAN_CFG,
		   "cfg reg_notify %c%c%s%s initiator %d hint_type %d\n",
		   request->alpha2[0], request->alpha2[1],
		   request->पूर्णांकersect ? " intersect" : "",
		   request->processed ? " processed" : "",
		   request->initiator, request->user_reg_hपूर्णांक_type);

	अगर (request->user_reg_hपूर्णांक_type != NL80211_USER_REG_HINT_CELL_BASE)
		वापस;

	ret = ath6kl_wmi_set_regकरोमुख्य_cmd(ar->wmi, request->alpha2);
	अगर (ret) अणु
		ath6kl_err("failed to set regdomain: %d\n", ret);
		वापस;
	पूर्ण

	/*
	 * Firmware will apply the regकरोमुख्य change only after a scan is
	 * issued and it will send a WMI_REGDOMAIN_EVENTID when it has been
	 * changed.
	 */

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++)
		अगर (wiphy->bands[i])
			rates[i] = (1 << wiphy->bands[i]->n_bitrates) - 1;


	ret = ath6kl_wmi_beginscan_cmd(ar->wmi, 0, WMI_LONG_SCAN, false,
				       false, 0, ATH6KL_FG_SCAN_INTERVAL,
				       0, शून्य, false, rates);
	अगर (ret) अणु
		ath6kl_err("failed to start scan for a regdomain change: %d\n",
			   ret);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_cfg80211_vअगर_init(काष्ठा ath6kl_vअगर *vअगर)
अणु
	vअगर->aggr_cntxt = aggr_init(vअगर);
	अगर (!vअगर->aggr_cntxt) अणु
		ath6kl_err("failed to initialize aggr\n");
		वापस -ENOMEM;
	पूर्ण

	समयr_setup(&vअगर->disconnect_समयr, disconnect_समयr_handler, 0);
	समयr_setup(&vअगर->sched_scan_समयr, ath6kl_wmi_sscan_समयr, 0);

	set_bit(WMM_ENABLED, &vअगर->flags);
	spin_lock_init(&vअगर->अगर_lock);

	INIT_LIST_HEAD(&vअगर->mc_filter);

	वापस 0;
पूर्ण

व्योम ath6kl_cfg80211_vअगर_stop(काष्ठा ath6kl_vअगर *vअगर, bool wmi_पढ़ोy)
अणु
	अटल u8 bcast_mac[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	bool discon_issued;

	netअगर_stop_queue(vअगर->ndev);

	clear_bit(WLAN_ENABLED, &vअगर->flags);

	अगर (wmi_पढ़ोy) अणु
		discon_issued = test_bit(CONNECTED, &vअगर->flags) ||
				test_bit(CONNECT_PEND, &vअगर->flags);
		ath6kl_disconnect(vअगर);
		del_समयr(&vअगर->disconnect_समयr);

		अगर (discon_issued)
			ath6kl_disconnect_event(vअगर, DISCONNECT_CMD,
						(vअगर->nw_type & AP_NETWORK) ?
						bcast_mac : vअगर->bssid,
						0, शून्य, 0);
	पूर्ण

	अगर (vअगर->scan_req) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = true,
		पूर्ण;

		cfg80211_scan_करोne(vअगर->scan_req, &info);
		vअगर->scan_req = शून्य;
	पूर्ण

	/* need to clean up enhanced bmiss detection fw state */
	ath6kl_cfg80211_sta_bmiss_enhance(vअगर, false);
पूर्ण

व्योम ath6kl_cfg80211_vअगर_cleanup(काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	काष्ठा ath6kl_mc_filter *mc_filter, *पंचांगp;

	aggr_module_destroy(vअगर->aggr_cntxt);

	ar->avail_idx_map |= BIT(vअगर->fw_vअगर_idx);

	अगर (vअगर->nw_type == ADHOC_NETWORK)
		ar->ibss_अगर_active = false;

	list_क्रम_each_entry_safe(mc_filter, पंचांगp, &vअगर->mc_filter, list) अणु
		list_del(&mc_filter->list);
		kमुक्त(mc_filter);
	पूर्ण

	cfg80211_unरेजिस्टर_netdevice(vअगर->ndev);

	ar->num_vअगर--;
पूर्ण

अटल स्थिर अक्षर ath6kl_gstrings_sta_stats[][ETH_GSTRING_LEN] = अणु
	/* Common stats names used by many drivers. */
	"tx_pkts_nic", "tx_bytes_nic", "rx_pkts_nic", "rx_bytes_nic",

	/* TX stats. */
	"d_tx_ucast_pkts", "d_tx_bcast_pkts",
	"d_tx_ucast_bytes", "d_tx_bcast_bytes",
	"d_tx_rts_ok", "d_tx_error", "d_tx_fail",
	"d_tx_retry", "d_tx_multi_retry", "d_tx_rts_fail",
	"d_tx_tkip_counter_measures",

	/* RX Stats. */
	"d_rx_ucast_pkts", "d_rx_ucast_rate", "d_rx_bcast_pkts",
	"d_rx_ucast_bytes", "d_rx_bcast_bytes", "d_rx_frag_pkt",
	"d_rx_error", "d_rx_crc_err", "d_rx_keycache_miss",
	"d_rx_decrypt_crc_err", "d_rx_duplicate_frames",
	"d_rx_mic_err", "d_rx_tkip_format_err", "d_rx_ccmp_format_err",
	"d_rx_ccmp_replay_err",

	/* Misc stats. */
	"d_beacon_miss", "d_num_connects", "d_num_disconnects",
	"d_beacon_avg_rssi", "d_arp_received", "d_arp_matched",
	"d_arp_replied"
पूर्ण;

#घोषणा ATH6KL_STATS_LEN	ARRAY_SIZE(ath6kl_gstrings_sta_stats)

अटल पूर्णांक ath6kl_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	पूर्णांक rv = 0;

	अगर (sset == ETH_SS_STATS)
		rv += ATH6KL_STATS_LEN;

	अगर (rv == 0)
		वापस -EOPNOTSUPP;
	वापस rv;
पूर्ण

अटल व्योम ath6kl_get_stats(काष्ठा net_device *dev,
			    काष्ठा ethtool_stats *stats,
			    u64 *data)
अणु
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	काष्ठा ath6kl *ar = vअगर->ar;
	पूर्णांक i = 0;
	काष्ठा target_stats *tgt_stats;

	स_रखो(data, 0, माप(u64) * ATH6KL_STATS_LEN);

	ath6kl_पढ़ो_tgt_stats(ar, vअगर);

	tgt_stats = &vअगर->target_stats;

	data[i++] = tgt_stats->tx_ucast_pkt + tgt_stats->tx_bcast_pkt;
	data[i++] = tgt_stats->tx_ucast_byte + tgt_stats->tx_bcast_byte;
	data[i++] = tgt_stats->rx_ucast_pkt + tgt_stats->rx_bcast_pkt;
	data[i++] = tgt_stats->rx_ucast_byte + tgt_stats->rx_bcast_byte;

	data[i++] = tgt_stats->tx_ucast_pkt;
	data[i++] = tgt_stats->tx_bcast_pkt;
	data[i++] = tgt_stats->tx_ucast_byte;
	data[i++] = tgt_stats->tx_bcast_byte;
	data[i++] = tgt_stats->tx_rts_success_cnt;
	data[i++] = tgt_stats->tx_err;
	data[i++] = tgt_stats->tx_fail_cnt;
	data[i++] = tgt_stats->tx_retry_cnt;
	data[i++] = tgt_stats->tx_mult_retry_cnt;
	data[i++] = tgt_stats->tx_rts_fail_cnt;
	data[i++] = tgt_stats->tkip_cnter_measures_invoked;

	data[i++] = tgt_stats->rx_ucast_pkt;
	data[i++] = tgt_stats->rx_ucast_rate;
	data[i++] = tgt_stats->rx_bcast_pkt;
	data[i++] = tgt_stats->rx_ucast_byte;
	data[i++] = tgt_stats->rx_bcast_byte;
	data[i++] = tgt_stats->rx_frgment_pkt;
	data[i++] = tgt_stats->rx_err;
	data[i++] = tgt_stats->rx_crc_err;
	data[i++] = tgt_stats->rx_key_cache_miss;
	data[i++] = tgt_stats->rx_decrypt_err;
	data[i++] = tgt_stats->rx_dupl_frame;
	data[i++] = tgt_stats->tkip_local_mic_fail;
	data[i++] = tgt_stats->tkip_fmt_err;
	data[i++] = tgt_stats->ccmp_fmt_err;
	data[i++] = tgt_stats->ccmp_replays;

	data[i++] = tgt_stats->cs_bmiss_cnt;
	data[i++] = tgt_stats->cs_connect_cnt;
	data[i++] = tgt_stats->cs_discon_cnt;
	data[i++] = tgt_stats->cs_ave_beacon_rssi;
	data[i++] = tgt_stats->arp_received;
	data[i++] = tgt_stats->arp_matched;
	data[i++] = tgt_stats->arp_replied;

	अगर (i !=  ATH6KL_STATS_LEN) अणु
		WARN_ON_ONCE(1);
		ath6kl_err("ethtool stats error, i: %d  STATS_LEN: %d\n",
			   i, (पूर्णांक)ATH6KL_STATS_LEN);
	पूर्ण
पूर्ण

/* These stats are per NIC, not really per vdev, so we just ignore dev. */
अटल व्योम ath6kl_get_strings(काष्ठा net_device *dev, u32 sset, u8 *data)
अणु
	पूर्णांक sz_sta_stats = 0;

	अगर (sset == ETH_SS_STATS) अणु
		sz_sta_stats = माप(ath6kl_gstrings_sta_stats);
		स_नकल(data, ath6kl_gstrings_sta_stats, sz_sta_stats);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ath6kl_ethtool_ops = अणु
	.get_drvinfo = cfg80211_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_strings = ath6kl_get_strings,
	.get_ethtool_stats = ath6kl_get_stats,
	.get_sset_count = ath6kl_get_sset_count,
पूर्ण;

काष्ठा wireless_dev *ath6kl_पूर्णांकerface_add(काष्ठा ath6kl *ar, स्थिर अक्षर *name,
					  अचिन्हित अक्षर name_assign_type,
					  क्रमागत nl80211_अगरtype type,
					  u8 fw_vअगर_idx, u8 nw_type)
अणु
	काष्ठा net_device *ndev;
	काष्ठा ath6kl_vअगर *vअगर;

	ndev = alloc_netdev(माप(*vअगर), name, name_assign_type, ether_setup);
	अगर (!ndev)
		वापस शून्य;

	vअगर = netdev_priv(ndev);
	ndev->ieee80211_ptr = &vअगर->wdev;
	vअगर->wdev.wiphy = ar->wiphy;
	vअगर->ar = ar;
	vअगर->ndev = ndev;
	SET_NETDEV_DEV(ndev, wiphy_dev(vअगर->wdev.wiphy));
	vअगर->wdev.netdev = ndev;
	vअगर->wdev.अगरtype = type;
	vअगर->fw_vअगर_idx = fw_vअगर_idx;
	vअगर->nw_type = nw_type;
	vअगर->next_mode = nw_type;
	vअगर->listen_पूर्णांकvl_t = ATH6KL_DEFAULT_LISTEN_INTVAL;
	vअगर->bmiss_समय_प्रकार = ATH6KL_DEFAULT_BMISS_TIME;
	vअगर->bg_scan_period = 0;
	vअगर->htcap[NL80211_BAND_2GHZ].ht_enable = true;
	vअगर->htcap[NL80211_BAND_5GHZ].ht_enable = true;

	स_नकल(ndev->dev_addr, ar->mac_addr, ETH_ALEN);
	अगर (fw_vअगर_idx != 0) अणु
		ndev->dev_addr[0] = (ndev->dev_addr[0] ^ (1 << fw_vअगर_idx)) |
				     0x2;
		अगर (test_bit(ATH6KL_FW_CAPABILITY_CUSTOM_MAC_ADDR,
			     ar->fw_capabilities))
			ndev->dev_addr[4] ^= 0x80;
	पूर्ण

	init_netdev(ndev);

	ath6kl_init_control_info(vअगर);

	अगर (ath6kl_cfg80211_vअगर_init(vअगर))
		जाओ err;

	netdev_set_शेष_ethtool_ops(ndev, &ath6kl_ethtool_ops);

	अगर (cfg80211_रेजिस्टर_netdevice(ndev))
		जाओ err;

	ar->avail_idx_map &= ~BIT(fw_vअगर_idx);
	vअगर->sme_state = SME_DISCONNECTED;
	set_bit(WLAN_ENABLED, &vअगर->flags);
	ar->wlan_pwr_state = WLAN_POWER_STATE_ON;

	अगर (type == NL80211_IFTYPE_ADHOC)
		ar->ibss_अगर_active = true;

	spin_lock_bh(&ar->list_lock);
	list_add_tail(&vअगर->list, &ar->vअगर_list);
	spin_unlock_bh(&ar->list_lock);

	वापस &vअगर->wdev;

err:
	aggr_module_destroy(vअगर->aggr_cntxt);
	मुक्त_netdev(ndev);
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा wiphy_wowlan_support ath6kl_wowlan_support = अणु
	.flags = WIPHY_WOWLAN_MAGIC_PKT |
		 WIPHY_WOWLAN_DISCONNECT |
		 WIPHY_WOWLAN_GTK_REKEY_FAILURE  |
		 WIPHY_WOWLAN_SUPPORTS_GTK_REKEY |
		 WIPHY_WOWLAN_EAP_IDENTITY_REQ   |
		 WIPHY_WOWLAN_4WAY_HANDSHAKE,
	.n_patterns = WOW_MAX_FILTERS_PER_LIST,
	.pattern_min_len = 1,
	.pattern_max_len = WOW_PATTERN_SIZE,
पूर्ण;
#पूर्ण_अगर

पूर्णांक ath6kl_cfg80211_init(काष्ठा ath6kl *ar)
अणु
	काष्ठा wiphy *wiphy = ar->wiphy;
	bool band_2gig = false, band_5gig = false, ht = false;
	पूर्णांक ret;

	wiphy->mgmt_stypes = ath6kl_mgmt_stypes;

	wiphy->max_reमुख्य_on_channel_duration = 5000;

	/* set device poपूर्णांकer क्रम wiphy */
	set_wiphy_dev(wiphy, ar->dev);

	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				 BIT(NL80211_IFTYPE_ADHOC) |
				 BIT(NL80211_IFTYPE_AP);
	अगर (ar->p2p) अणु
		wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_P2P_GO) |
					  BIT(NL80211_IFTYPE_P2P_CLIENT);
	पूर्ण

	अगर (IS_ENABLED(CONFIG_ATH6KL_REGDOMAIN) &&
	    test_bit(ATH6KL_FW_CAPABILITY_REGDOMAIN, ar->fw_capabilities)) अणु
		wiphy->reg_notअगरier = ath6kl_cfg80211_reg_notअगरy;
		ar->wiphy->features |= NL80211_FEATURE_CELL_BASE_REG_HINTS;
	पूर्ण

	/* max num of ssids that can be probed during scanning */
	wiphy->max_scan_ssids = MAX_PROBED_SSIDS;

	/* max num of ssids that can be matched after scan */
	अगर (test_bit(ATH6KL_FW_CAPABILITY_SCHED_SCAN_MATCH_LIST,
		     ar->fw_capabilities))
		wiphy->max_match_sets = MAX_PROBED_SSIDS;

	wiphy->max_scan_ie_len = 1000; /* FIX: what is correct limit? */
	चयन (ar->hw.cap) अणु
	हाल WMI_11AN_CAP:
		ht = true;
		fallthrough;
	हाल WMI_11A_CAP:
		band_5gig = true;
		अवरोध;
	हाल WMI_11GN_CAP:
		ht = true;
		fallthrough;
	हाल WMI_11G_CAP:
		band_2gig = true;
		अवरोध;
	हाल WMI_11AGN_CAP:
		ht = true;
		fallthrough;
	हाल WMI_11AG_CAP:
		band_2gig = true;
		band_5gig = true;
		अवरोध;
	शेष:
		ath6kl_err("invalid phy capability!\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Even अगर the fw has HT support, advertise HT cap only when
	 * the firmware has support to override RSN capability, otherwise
	 * 4-way handshake would fail.
	 */
	अगर (!(ht &&
	      test_bit(ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE,
		       ar->fw_capabilities))) अणु
		ath6kl_band_2ghz.ht_cap.cap = 0;
		ath6kl_band_2ghz.ht_cap.ht_supported = false;
		ath6kl_band_5ghz.ht_cap.cap = 0;
		ath6kl_band_5ghz.ht_cap.ht_supported = false;

		अगर (ht)
			ath6kl_err("Firmware lacks RSN-CAP-OVERRIDE, so HT (802.11n) is disabled.");
	पूर्ण

	अगर (test_bit(ATH6KL_FW_CAPABILITY_64BIT_RATES,
		     ar->fw_capabilities)) अणु
		ath6kl_band_2ghz.ht_cap.mcs.rx_mask[0] = 0xff;
		ath6kl_band_5ghz.ht_cap.mcs.rx_mask[0] = 0xff;
		ath6kl_band_2ghz.ht_cap.mcs.rx_mask[1] = 0xff;
		ath6kl_band_5ghz.ht_cap.mcs.rx_mask[1] = 0xff;
		ar->hw.tx_ant = 0x3; /* mask, 2 antenna */
		ar->hw.rx_ant = 0x3;
	पूर्ण अन्यथा अणु
		ath6kl_band_2ghz.ht_cap.mcs.rx_mask[0] = 0xff;
		ath6kl_band_5ghz.ht_cap.mcs.rx_mask[0] = 0xff;
		ar->hw.tx_ant = 1;
		ar->hw.rx_ant = 1;
	पूर्ण

	wiphy->available_antennas_tx = ar->hw.tx_ant;
	wiphy->available_antennas_rx = ar->hw.rx_ant;

	अगर (band_2gig)
		wiphy->bands[NL80211_BAND_2GHZ] = &ath6kl_band_2ghz;
	अगर (band_5gig)
		wiphy->bands[NL80211_BAND_5GHZ] = &ath6kl_band_5ghz;

	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;

	wiphy->cipher_suites = cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

#अगर_घोषित CONFIG_PM
	wiphy->wowlan = &ath6kl_wowlan_support;
#पूर्ण_अगर

	wiphy->max_sched_scan_ssids = MAX_PROBED_SSIDS;

	ar->wiphy->flags |= WIPHY_FLAG_SUPPORTS_FW_ROAM |
			    WIPHY_FLAG_HAVE_AP_SME |
			    WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
			    WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD;

	अगर (test_bit(ATH6KL_FW_CAPABILITY_SCHED_SCAN_V2, ar->fw_capabilities))
		ar->wiphy->max_sched_scan_reqs = 1;

	अगर (test_bit(ATH6KL_FW_CAPABILITY_INACTIVITY_TIMEOUT,
		     ar->fw_capabilities))
		ar->wiphy->features |= NL80211_FEATURE_INACTIVITY_TIMER;

	ar->wiphy->probe_resp_offload =
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 |
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P;

	ret = wiphy_रेजिस्टर(wiphy);
	अगर (ret < 0) अणु
		ath6kl_err("couldn't register wiphy device\n");
		वापस ret;
	पूर्ण

	ar->wiphy_रेजिस्टरed = true;

	वापस 0;
पूर्ण

व्योम ath6kl_cfg80211_cleanup(काष्ठा ath6kl *ar)
अणु
	wiphy_unरेजिस्टर(ar->wiphy);

	ar->wiphy_रेजिस्टरed = false;
पूर्ण

काष्ठा ath6kl *ath6kl_cfg80211_create(व्योम)
अणु
	काष्ठा ath6kl *ar;
	काष्ठा wiphy *wiphy;

	/* create a new wiphy क्रम use with cfg80211 */
	wiphy = wiphy_new(&ath6kl_cfg80211_ops, माप(काष्ठा ath6kl));

	अगर (!wiphy) अणु
		ath6kl_err("couldn't allocate wiphy device\n");
		वापस शून्य;
	पूर्ण

	ar = wiphy_priv(wiphy);
	ar->wiphy = wiphy;

	वापस ar;
पूर्ण

/* Note: ar variable must not be accessed after calling this! */
व्योम ath6kl_cfg80211_destroy(काष्ठा ath6kl *ar)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AP_MAX_NUM_STA; i++)
		kमुक्त(ar->sta_list[i].aggr_conn);

	wiphy_मुक्त(ar->wiphy);
पूर्ण

