<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश "mac.h"

#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/bitfield.h>

#समावेश "hif.h"
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "wmi.h"
#समावेश "htt.h"
#समावेश "txrx.h"
#समावेश "testmode.h"
#समावेश "wmi-tlv.h"
#समावेश "wmi-ops.h"
#समावेश "wow.h"

/*********/
/* Rates */
/*********/

अटल काष्ठा ieee80211_rate ath10k_rates[] = अणु
	अणु .bitrate = 10,
	  .hw_value = ATH10K_HW_RATE_CCK_LP_1M पूर्ण,
	अणु .bitrate = 20,
	  .hw_value = ATH10K_HW_RATE_CCK_LP_2M,
	  .hw_value_लघु = ATH10K_HW_RATE_CCK_SP_2M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55,
	  .hw_value = ATH10K_HW_RATE_CCK_LP_5_5M,
	  .hw_value_लघु = ATH10K_HW_RATE_CCK_SP_5_5M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110,
	  .hw_value = ATH10K_HW_RATE_CCK_LP_11M,
	  .hw_value_लघु = ATH10K_HW_RATE_CCK_SP_11M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,

	अणु .bitrate = 60, .hw_value = ATH10K_HW_RATE_OFDM_6M पूर्ण,
	अणु .bitrate = 90, .hw_value = ATH10K_HW_RATE_OFDM_9M पूर्ण,
	अणु .bitrate = 120, .hw_value = ATH10K_HW_RATE_OFDM_12M पूर्ण,
	अणु .bitrate = 180, .hw_value = ATH10K_HW_RATE_OFDM_18M पूर्ण,
	अणु .bitrate = 240, .hw_value = ATH10K_HW_RATE_OFDM_24M पूर्ण,
	अणु .bitrate = 360, .hw_value = ATH10K_HW_RATE_OFDM_36M पूर्ण,
	अणु .bitrate = 480, .hw_value = ATH10K_HW_RATE_OFDM_48M पूर्ण,
	अणु .bitrate = 540, .hw_value = ATH10K_HW_RATE_OFDM_54M पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_rate ath10k_rates_rev2[] = अणु
	अणु .bitrate = 10,
	  .hw_value = ATH10K_HW_RATE_REV2_CCK_LP_1M पूर्ण,
	अणु .bitrate = 20,
	  .hw_value = ATH10K_HW_RATE_REV2_CCK_LP_2M,
	  .hw_value_लघु = ATH10K_HW_RATE_REV2_CCK_SP_2M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55,
	  .hw_value = ATH10K_HW_RATE_REV2_CCK_LP_5_5M,
	  .hw_value_लघु = ATH10K_HW_RATE_REV2_CCK_SP_5_5M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110,
	  .hw_value = ATH10K_HW_RATE_REV2_CCK_LP_11M,
	  .hw_value_लघु = ATH10K_HW_RATE_REV2_CCK_SP_11M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,

	अणु .bitrate = 60, .hw_value = ATH10K_HW_RATE_OFDM_6M पूर्ण,
	अणु .bitrate = 90, .hw_value = ATH10K_HW_RATE_OFDM_9M पूर्ण,
	अणु .bitrate = 120, .hw_value = ATH10K_HW_RATE_OFDM_12M पूर्ण,
	अणु .bitrate = 180, .hw_value = ATH10K_HW_RATE_OFDM_18M पूर्ण,
	अणु .bitrate = 240, .hw_value = ATH10K_HW_RATE_OFDM_24M पूर्ण,
	अणु .bitrate = 360, .hw_value = ATH10K_HW_RATE_OFDM_36M पूर्ण,
	अणु .bitrate = 480, .hw_value = ATH10K_HW_RATE_OFDM_48M पूर्ण,
	अणु .bitrate = 540, .hw_value = ATH10K_HW_RATE_OFDM_54M पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cfg80211_sar_freq_ranges ath10k_sar_freq_ranges[] = अणु
	अणु.start_freq = 2402, .end_freq = 2494 पूर्ण,
	अणु.start_freq = 5170, .end_freq = 5875 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cfg80211_sar_capa ath10k_sar_capa = अणु
	.type = NL80211_SAR_TYPE_POWER,
	.num_freq_ranges = (ARRAY_SIZE(ath10k_sar_freq_ranges)),
	.freq_ranges = &ath10k_sar_freq_ranges[0],
पूर्ण;

#घोषणा ATH10K_MAC_FIRST_OFDM_RATE_IDX 4

#घोषणा ath10k_a_rates (ath10k_rates + ATH10K_MAC_FIRST_OFDM_RATE_IDX)
#घोषणा ath10k_a_rates_size (ARRAY_SIZE(ath10k_rates) - \
			     ATH10K_MAC_FIRST_OFDM_RATE_IDX)
#घोषणा ath10k_g_rates (ath10k_rates + 0)
#घोषणा ath10k_g_rates_size (ARRAY_SIZE(ath10k_rates))

#घोषणा ath10k_g_rates_rev2 (ath10k_rates_rev2 + 0)
#घोषणा ath10k_g_rates_rev2_size (ARRAY_SIZE(ath10k_rates_rev2))

#घोषणा ath10k_wmi_legacy_rates ath10k_rates

अटल bool ath10k_mac_bitrate_is_cck(पूर्णांक bitrate)
अणु
	चयन (bitrate) अणु
	हाल 10:
	हाल 20:
	हाल 55:
	हाल 110:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल u8 ath10k_mac_bitrate_to_rate(पूर्णांक bitrate)
अणु
	वापस DIV_ROUND_UP(bitrate, 5) |
	       (ath10k_mac_bitrate_is_cck(bitrate) ? BIT(7) : 0);
पूर्ण

u8 ath10k_mac_hw_rate_to_idx(स्थिर काष्ठा ieee80211_supported_band *sband,
			     u8 hw_rate, bool cck)
अणु
	स्थिर काष्ठा ieee80211_rate *rate;
	पूर्णांक i;

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		rate = &sband->bitrates[i];

		अगर (ath10k_mac_bitrate_is_cck(rate->bitrate) != cck)
			जारी;

		अगर (rate->hw_value == hw_rate)
			वापस i;
		अन्यथा अगर (rate->flags & IEEE80211_RATE_SHORT_PREAMBLE &&
			 rate->hw_value_लघु == hw_rate)
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण

u8 ath10k_mac_bitrate_to_idx(स्थिर काष्ठा ieee80211_supported_band *sband,
			     u32 bitrate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sband->n_bitrates; i++)
		अगर (sband->bitrates[i].bitrate == bitrate)
			वापस i;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_get_rate_hw_value(पूर्णांक bitrate)
अणु
	पूर्णांक i;
	u8 hw_value_prefix = 0;

	अगर (ath10k_mac_bitrate_is_cck(bitrate))
		hw_value_prefix = WMI_RATE_PREAMBLE_CCK << 6;

	क्रम (i = 0; i < ARRAY_SIZE(ath10k_rates); i++) अणु
		अगर (ath10k_rates[i].bitrate == bitrate)
			वापस hw_value_prefix | ath10k_rates[i].hw_value;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ath10k_mac_get_max_vht_mcs_map(u16 mcs_map, पूर्णांक nss)
अणु
	चयन ((mcs_map >> (2 * nss)) & 0x3) अणु
	हाल IEEE80211_VHT_MCS_SUPPORT_0_7: वापस BIT(8) - 1;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_8: वापस BIT(9) - 1;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_9: वापस BIT(10) - 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल u32
ath10k_mac_max_ht_nss(स्थिर u8 ht_mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
अणु
	पूर्णांक nss;

	क्रम (nss = IEEE80211_HT_MCS_MASK_LEN - 1; nss >= 0; nss--)
		अगर (ht_mcs_mask[nss])
			वापस nss + 1;

	वापस 1;
पूर्ण

अटल u32
ath10k_mac_max_vht_nss(स्थिर u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
अणु
	पूर्णांक nss;

	क्रम (nss = NL80211_VHT_NSS_MAX - 1; nss >= 0; nss--)
		अगर (vht_mcs_mask[nss])
			वापस nss + 1;

	वापस 1;
पूर्ण

पूर्णांक ath10k_mac_ext_resource_config(काष्ठा ath10k *ar, u32 val)
अणु
	क्रमागत wmi_host_platक्रमm_type platक्रमm_type;
	पूर्णांक ret;

	अगर (test_bit(WMI_SERVICE_TX_MODE_DYNAMIC, ar->wmi.svc_map))
		platक्रमm_type = WMI_HOST_PLATFORM_LOW_PERF;
	अन्यथा
		platक्रमm_type = WMI_HOST_PLATFORM_HIGH_PERF;

	ret = ath10k_wmi_ext_resource_config(ar, platक्रमm_type, val);

	अगर (ret && ret != -EOPNOTSUPP) अणु
		ath10k_warn(ar, "failed to configure ext resource: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**********/
/* Crypto */
/**********/

अटल पूर्णांक ath10k_send_key(काष्ठा ath10k_vअगर *arvअगर,
			   काष्ठा ieee80211_key_conf *key,
			   क्रमागत set_key_cmd cmd,
			   स्थिर u8 *macaddr, u32 flags)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा wmi_vdev_install_key_arg arg = अणु
		.vdev_id = arvअगर->vdev_id,
		.key_idx = key->keyidx,
		.key_len = key->keylen,
		.key_data = key->key,
		.key_flags = flags,
		.macaddr = macaddr,
	पूर्ण;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_AES_CCM];
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV_MGMT;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_TKIP];
		arg.key_txmic_len = 8;
		arg.key_rxmic_len = 8;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_WEP];
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_AES_CCM];
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_AES_GCM];
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV_MGMT;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		WARN_ON(1);
		वापस -EINVAL;
	शेष:
		ath10k_warn(ar, "cipher %d is not supported\n", key->cipher);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags))
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

	अगर (cmd == DISABLE_KEY) अणु
		arg.key_cipher = ar->wmi_key_cipher[WMI_CIPHER_NONE];
		arg.key_data = शून्य;
	पूर्ण

	वापस ath10k_wmi_vdev_install_key(arvअगर->ar, &arg);
पूर्ण

अटल पूर्णांक ath10k_install_key(काष्ठा ath10k_vअगर *arvअगर,
			      काष्ठा ieee80211_key_conf *key,
			      क्रमागत set_key_cmd cmd,
			      स्थिर u8 *macaddr, u32 flags)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->install_key_करोne);

	अगर (arvअगर->nohwcrypt)
		वापस 1;

	ret = ath10k_send_key(arvअगर, key, cmd, macaddr, flags);
	अगर (ret)
		वापस ret;

	समय_left = रुको_क्रम_completion_समयout(&ar->install_key_करोne, 3 * HZ);
	अगर (समय_left == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_install_peer_wep_keys(काष्ठा ath10k_vअगर *arvअगर,
					स्थिर u8 *addr)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ath10k_peer *peer;
	पूर्णांक ret;
	पूर्णांक i;
	u32 flags;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(arvअगर->vअगर->type != NL80211_IFTYPE_AP &&
		    arvअगर->vअगर->type != NL80211_IFTYPE_ADHOC &&
		    arvअगर->vअगर->type != NL80211_IFTYPE_MESH_POINT))
		वापस -EINVAL;

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, arvअगर->vdev_id, addr);
	spin_unlock_bh(&ar->data_lock);

	अगर (!peer)
		वापस -ENOENT;

	क्रम (i = 0; i < ARRAY_SIZE(arvअगर->wep_keys); i++) अणु
		अगर (arvअगर->wep_keys[i] == शून्य)
			जारी;

		चयन (arvअगर->vअगर->type) अणु
		हाल NL80211_IFTYPE_AP:
			flags = WMI_KEY_PAIRWISE;

			अगर (arvअगर->def_wep_key_idx == i)
				flags |= WMI_KEY_TX_USAGE;

			ret = ath10k_install_key(arvअगर, arvअगर->wep_keys[i],
						 SET_KEY, addr, flags);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		हाल NL80211_IFTYPE_ADHOC:
			ret = ath10k_install_key(arvअगर, arvअगर->wep_keys[i],
						 SET_KEY, addr,
						 WMI_KEY_PAIRWISE);
			अगर (ret < 0)
				वापस ret;

			ret = ath10k_install_key(arvअगर, arvअगर->wep_keys[i],
						 SET_KEY, addr, WMI_KEY_GROUP);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		शेष:
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण

		spin_lock_bh(&ar->data_lock);
		peer->keys[i] = arvअगर->wep_keys[i];
		spin_unlock_bh(&ar->data_lock);
	पूर्ण

	/* In some हालs (notably with अटल WEP IBSS with multiple keys)
	 * multicast Tx becomes broken. Both pairwise and groupwise keys are
	 * installed alपढ़ोy. Using WMI_KEY_TX_USAGE in dअगरferent combinations
	 * didn't seem help. Using def_keyid vdev parameter seems to be
	 * effective so use that.
	 *
	 * FIXME: Revisit. Perhaps this can be करोne in a less hacky way.
	 */
	अगर (arvअगर->vअगर->type != NL80211_IFTYPE_ADHOC)
		वापस 0;

	अगर (arvअगर->def_wep_key_idx == -1)
		वापस 0;

	ret = ath10k_wmi_vdev_set_param(arvअगर->ar,
					arvअगर->vdev_id,
					arvअगर->ar->wmi.vdev_param->def_keyid,
					arvअगर->def_wep_key_idx);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to re-set def wpa key idxon vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_clear_peer_keys(काष्ठा ath10k_vअगर *arvअगर,
				  स्थिर u8 *addr)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ath10k_peer *peer;
	पूर्णांक first_त्रुटि_सं = 0;
	पूर्णांक ret;
	पूर्णांक i;
	u32 flags = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, arvअगर->vdev_id, addr);
	spin_unlock_bh(&ar->data_lock);

	अगर (!peer)
		वापस -ENOENT;

	क्रम (i = 0; i < ARRAY_SIZE(peer->keys); i++) अणु
		अगर (peer->keys[i] == शून्य)
			जारी;

		/* key flags are not required to delete the key */
		ret = ath10k_install_key(arvअगर, peer->keys[i],
					 DISABLE_KEY, addr, flags);
		अगर (ret < 0 && first_त्रुटि_सं == 0)
			first_त्रुटि_सं = ret;

		अगर (ret < 0)
			ath10k_warn(ar, "failed to remove peer wep key %d: %d\n",
				    i, ret);

		spin_lock_bh(&ar->data_lock);
		peer->keys[i] = शून्य;
		spin_unlock_bh(&ar->data_lock);
	पूर्ण

	वापस first_त्रुटि_सं;
पूर्ण

bool ath10k_mac_is_peer_wep_key_set(काष्ठा ath10k *ar, स्थिर u8 *addr,
				    u8 keyidx)
अणु
	काष्ठा ath10k_peer *peer;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->data_lock);

	/* We करोn't know which vdev this peer beदीर्घs to,
	 * since WMI करोesn't give us that inक्रमmation.
	 *
	 * FIXME: multi-bss needs to be handled.
	 */
	peer = ath10k_peer_find(ar, 0, addr);
	अगर (!peer)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(peer->keys); i++) अणु
		अगर (peer->keys[i] && peer->keys[i]->keyidx == keyidx)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ath10k_clear_vdev_key(काष्ठा ath10k_vअगर *arvअगर,
				 काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ath10k_peer *peer;
	u8 addr[ETH_ALEN];
	पूर्णांक first_त्रुटि_सं = 0;
	पूर्णांक ret;
	पूर्णांक i;
	u32 flags = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	क्रम (;;) अणु
		/* since ath10k_install_key we can't hold data_lock all the
		 * समय, so we try to हटाओ the keys incrementally
		 */
		spin_lock_bh(&ar->data_lock);
		i = 0;
		list_क्रम_each_entry(peer, &ar->peers, list) अणु
			क्रम (i = 0; i < ARRAY_SIZE(peer->keys); i++) अणु
				अगर (peer->keys[i] == key) अणु
					ether_addr_copy(addr, peer->addr);
					peer->keys[i] = शून्य;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (i < ARRAY_SIZE(peer->keys))
				अवरोध;
		पूर्ण
		spin_unlock_bh(&ar->data_lock);

		अगर (i == ARRAY_SIZE(peer->keys))
			अवरोध;
		/* key flags are not required to delete the key */
		ret = ath10k_install_key(arvअगर, key, DISABLE_KEY, addr, flags);
		अगर (ret < 0 && first_त्रुटि_सं == 0)
			first_त्रुटि_सं = ret;

		अगर (ret)
			ath10k_warn(ar, "failed to remove key for %pM: %d\n",
				    addr, ret);
	पूर्ण

	वापस first_त्रुटि_सं;
पूर्ण

अटल पूर्णांक ath10k_mac_vअगर_update_wep_key(काष्ठा ath10k_vअगर *arvअगर,
					 काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ath10k_peer *peer;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(peer, &ar->peers, list) अणु
		अगर (ether_addr_equal(peer->addr, arvअगर->vअगर->addr))
			जारी;

		अगर (ether_addr_equal(peer->addr, arvअगर->bssid))
			जारी;

		अगर (peer->keys[key->keyidx] == key)
			जारी;

		ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vif vdev %i update key %i needs update\n",
			   arvअगर->vdev_id, key->keyidx);

		ret = ath10k_install_peer_wep_keys(arvअगर, peer->addr);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to update wep keys on vdev %i for peer %pM: %d\n",
				    arvअगर->vdev_id, peer->addr, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*********************/
/* General utilities */
/*********************/

अटल अंतरभूत क्रमागत wmi_phy_mode
chan_to_phymode(स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	क्रमागत wmi_phy_mode phymode = MODE_UNKNOWN;

	चयन (chandef->chan->band) अणु
	हाल NL80211_BAND_2GHZ:
		चयन (chandef->width) अणु
		हाल NL80211_CHAN_WIDTH_20_NOHT:
			अगर (chandef->chan->flags & IEEE80211_CHAN_NO_OFDM)
				phymode = MODE_11B;
			अन्यथा
				phymode = MODE_11G;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_20:
			phymode = MODE_11NG_HT20;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_40:
			phymode = MODE_11NG_HT40;
			अवरोध;
		शेष:
			phymode = MODE_UNKNOWN;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		चयन (chandef->width) अणु
		हाल NL80211_CHAN_WIDTH_20_NOHT:
			phymode = MODE_11A;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_20:
			phymode = MODE_11NA_HT20;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_40:
			phymode = MODE_11NA_HT40;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_80:
			phymode = MODE_11AC_VHT80;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_160:
			phymode = MODE_11AC_VHT160;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_80P80:
			phymode = MODE_11AC_VHT80_80;
			अवरोध;
		शेष:
			phymode = MODE_UNKNOWN;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	WARN_ON(phymode == MODE_UNKNOWN);
	वापस phymode;
पूर्ण

अटल u8 ath10k_parse_mpdudensity(u8 mpdudensity)
अणु
/*
 * 802.11n D2.0 defined values क्रम "Minimum MPDU Start Spacing":
 *   0 क्रम no restriction
 *   1 क्रम 1/4 us
 *   2 क्रम 1/2 us
 *   3 क्रम 1 us
 *   4 क्रम 2 us
 *   5 क्रम 4 us
 *   6 क्रम 8 us
 *   7 क्रम 16 us
 */
	चयन (mpdudensity) अणु
	हाल 0:
		वापस 0;
	हाल 1:
	हाल 2:
	हाल 3:
	/* Our lower layer calculations limit our precision to
	 * 1 microsecond
	 */
		वापस 1;
	हाल 4:
		वापस 2;
	हाल 5:
		वापस 4;
	हाल 6:
		वापस 8;
	हाल 7:
		वापस 16;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक ath10k_mac_vअगर_chan(काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा cfg80211_chan_def *def)
अणु
	काष्ठा ieee80211_chanctx_conf *conf;

	rcu_पढ़ो_lock();
	conf = rcu_dereference(vअगर->chanctx_conf);
	अगर (!conf) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	*def = conf->def;
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल व्योम ath10k_mac_num_chanctxs_iter(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_chanctx_conf *conf,
					 व्योम *data)
अणु
	पूर्णांक *num = data;

	(*num)++;
पूर्ण

अटल पूर्णांक ath10k_mac_num_chanctxs(काष्ठा ath10k *ar)
अणु
	पूर्णांक num = 0;

	ieee80211_iter_chan_contexts_atomic(ar->hw,
					    ath10k_mac_num_chanctxs_iter,
					    &num);

	वापस num;
पूर्ण

अटल व्योम
ath10k_mac_get_any_chandef_iter(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_chanctx_conf *conf,
				व्योम *data)
अणु
	काष्ठा cfg80211_chan_def **def = data;

	*def = &conf->def;
पूर्ण

अटल व्योम ath10k_रुको_क्रम_peer_delete_करोne(काष्ठा ath10k *ar, u32 vdev_id,
					     स्थिर u8 *addr)
अणु
	अचिन्हित दीर्घ समय_left;
	पूर्णांक ret;

	अगर (test_bit(WMI_SERVICE_SYNC_DELETE_CMDS, ar->wmi.svc_map)) अणु
		ret = ath10k_रुको_क्रम_peer_deleted(ar, vdev_id, addr);
		अगर (ret) अणु
			ath10k_warn(ar, "failed wait for peer deleted");
			वापस;
		पूर्ण

		समय_left = रुको_क्रम_completion_समयout(&ar->peer_delete_करोne,
							5 * HZ);
		अगर (!समय_left)
			ath10k_warn(ar, "Timeout in receiving peer delete response\n");
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_peer_create(काष्ठा ath10k *ar,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta,
			      u32 vdev_id,
			      स्थिर u8 *addr,
			      क्रमागत wmi_peer_type peer_type)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	काष्ठा ath10k_peer *peer;
	पूर्णांक num_peers = 0;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	num_peers = ar->num_peers;

	/* Each vdev consumes a peer entry as well */
	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list)
		num_peers++;

	अगर (num_peers >= ar->max_num_peers)
		वापस -ENOBUFS;

	ret = ath10k_wmi_peer_create(ar, vdev_id, addr, peer_type);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to create wmi peer %pM on vdev %i: %i\n",
			    addr, vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_रुको_क्रम_peer_created(ar, vdev_id, addr);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to wait for created wmi peer %pM on vdev %i: %i\n",
			    addr, vdev_id, ret);
		वापस ret;
	पूर्ण

	spin_lock_bh(&ar->data_lock);

	peer = ath10k_peer_find(ar, vdev_id, addr);
	अगर (!peer) अणु
		spin_unlock_bh(&ar->data_lock);
		ath10k_warn(ar, "failed to find peer %pM on vdev %i after creation\n",
			    addr, vdev_id);
		ath10k_रुको_क्रम_peer_delete_करोne(ar, vdev_id, addr);
		वापस -ENOENT;
	पूर्ण

	peer->vअगर = vअगर;
	peer->sta = sta;

	spin_unlock_bh(&ar->data_lock);

	ar->num_peers++;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_set_kickout(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	u32 param;
	पूर्णांक ret;

	param = ar->wmi.pdev_param->sta_kickout_th;
	ret = ath10k_wmi_pdev_set_param(ar, param,
					ATH10K_KICKOUT_THRESHOLD);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set kickout threshold on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	param = ar->wmi.vdev_param->ap_keepalive_min_idle_inactive_समय_secs;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, param,
					ATH10K_KEEPALIVE_MIN_IDLE);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set keepalive minimum idle time on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	param = ar->wmi.vdev_param->ap_keepalive_max_idle_inactive_समय_secs;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, param,
					ATH10K_KEEPALIVE_MAX_IDLE);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set keepalive maximum idle time on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	param = ar->wmi.vdev_param->ap_keepalive_max_unresponsive_समय_secs;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, param,
					ATH10K_KEEPALIVE_MAX_UNRESPONSIVE);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set keepalive maximum unresponsive time on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_set_rts(काष्ठा ath10k_vअगर *arvअगर, u32 value)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	u32 vdev_param;

	vdev_param = ar->wmi.vdev_param->rts_threshold;
	वापस ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param, value);
पूर्ण

अटल पूर्णांक ath10k_peer_delete(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *addr)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_wmi_peer_delete(ar, vdev_id, addr);
	अगर (ret)
		वापस ret;

	ret = ath10k_रुको_क्रम_peer_deleted(ar, vdev_id, addr);
	अगर (ret)
		वापस ret;

	अगर (test_bit(WMI_SERVICE_SYNC_DELETE_CMDS, ar->wmi.svc_map)) अणु
		अचिन्हित दीर्घ समय_left;

		समय_left = रुको_क्रम_completion_समयout
			    (&ar->peer_delete_करोne, 5 * HZ);

		अगर (!समय_left) अणु
			ath10k_warn(ar, "Timeout in receiving peer delete response\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	ar->num_peers--;

	वापस 0;
पूर्ण

अटल व्योम ath10k_peer_cleanup(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा ath10k_peer *peer, *पंचांगp;
	पूर्णांक peer_id;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	list_क्रम_each_entry_safe(peer, पंचांगp, &ar->peers, list) अणु
		अगर (peer->vdev_id != vdev_id)
			जारी;

		ath10k_warn(ar, "removing stale peer %pM from vdev_id %d\n",
			    peer->addr, vdev_id);

		क्रम_each_set_bit(peer_id, peer->peer_ids,
				 ATH10K_MAX_NUM_PEER_IDS) अणु
			ar->peer_map[peer_id] = शून्य;
		पूर्ण

		/* Double check that peer is properly un-referenced from
		 * the peer_map
		 */
		क्रम (i = 0; i < ARRAY_SIZE(ar->peer_map); i++) अणु
			अगर (ar->peer_map[i] == peer) अणु
				ath10k_warn(ar, "removing stale peer_map entry for %pM (ptr %pK idx %d)\n",
					    peer->addr, peer, i);
				ar->peer_map[i] = शून्य;
			पूर्ण
		पूर्ण

		list_del(&peer->list);
		kमुक्त(peer);
		ar->num_peers--;
	पूर्ण
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल व्योम ath10k_peer_cleanup_all(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_peer *peer, *पंचांगp;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	list_क्रम_each_entry_safe(peer, पंचांगp, &ar->peers, list) अणु
		list_del(&peer->list);
		kमुक्त(peer);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ar->peer_map); i++)
		ar->peer_map[i] = शून्य;

	spin_unlock_bh(&ar->data_lock);

	ar->num_peers = 0;
	ar->num_stations = 0;
पूर्ण

अटल पूर्णांक ath10k_mac_tdls_peer_update(काष्ठा ath10k *ar, u32 vdev_id,
				       काष्ठा ieee80211_sta *sta,
				       क्रमागत wmi_tdls_peer_state state)
अणु
	पूर्णांक ret;
	काष्ठा wmi_tdls_peer_update_cmd_arg arg = अणुपूर्ण;
	काष्ठा wmi_tdls_peer_capab_arg cap = अणुपूर्ण;
	काष्ठा wmi_channel_arg chan_arg = अणुपूर्ण;

	lockdep_निश्चित_held(&ar->conf_mutex);

	arg.vdev_id = vdev_id;
	arg.peer_state = state;
	ether_addr_copy(arg.addr, sta->addr);

	cap.peer_max_sp = sta->max_sp;
	cap.peer_uapsd_queues = sta->uapsd_queues;

	अगर (state == WMI_TDLS_PEER_STATE_CONNECTED &&
	    !sta->tdls_initiator)
		cap.is_peer_responder = 1;

	ret = ath10k_wmi_tdls_peer_update(ar, &arg, &cap, &chan_arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to update tdls peer %pM on vdev %i: %i\n",
			    arg.addr, vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/************************/
/* Interface management */
/************************/

व्योम ath10k_mac_vअगर_beacon_मुक्त(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->data_lock);

	अगर (!arvअगर->beacon)
		वापस;

	अगर (!arvअगर->beacon_buf)
		dma_unmap_single(ar->dev, ATH10K_SKB_CB(arvअगर->beacon)->paddr,
				 arvअगर->beacon->len, DMA_TO_DEVICE);

	अगर (WARN_ON(arvअगर->beacon_state != ATH10K_BEACON_SCHEDULED &&
		    arvअगर->beacon_state != ATH10K_BEACON_SENT))
		वापस;

	dev_kमुक्त_skb_any(arvअगर->beacon);

	arvअगर->beacon = शून्य;
	arvअगर->beacon_state = ATH10K_BEACON_SCHEDULED;
पूर्ण

अटल व्योम ath10k_mac_vअगर_beacon_cleanup(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->data_lock);

	ath10k_mac_vअगर_beacon_मुक्त(arvअगर);

	अगर (arvअगर->beacon_buf) अणु
		dma_मुक्त_coherent(ar->dev, IEEE80211_MAX_FRAME_LEN,
				  arvअगर->beacon_buf, arvअगर->beacon_paddr);
		arvअगर->beacon_buf = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक ath10k_vdev_setup_sync(काष्ठा ath10k *ar)
अणु
	अचिन्हित दीर्घ समय_left;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags))
		वापस -ESHUTDOWN;

	समय_left = रुको_क्रम_completion_समयout(&ar->vdev_setup_करोne,
						ATH10K_VDEV_SETUP_TIMEOUT_HZ);
	अगर (समय_left == 0)
		वापस -ETIMEDOUT;

	वापस ar->last_wmi_vdev_start_status;
पूर्ण

अटल पूर्णांक ath10k_monitor_vdev_start(काष्ठा ath10k *ar, पूर्णांक vdev_id)
अणु
	काष्ठा cfg80211_chan_def *chandef = शून्य;
	काष्ठा ieee80211_channel *channel = शून्य;
	काष्ठा wmi_vdev_start_request_arg arg = अणुपूर्ण;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ieee80211_iter_chan_contexts_atomic(ar->hw,
					    ath10k_mac_get_any_chandef_iter,
					    &chandef);
	अगर (WARN_ON_ONCE(!chandef))
		वापस -ENOENT;

	channel = chandef->chan;

	arg.vdev_id = vdev_id;
	arg.channel.freq = channel->center_freq;
	arg.channel.band_center_freq1 = chandef->center_freq1;
	arg.channel.band_center_freq2 = chandef->center_freq2;

	/* TODO setup this dynamically, what in हाल we
	 * करोn't have any vअगरs?
	 */
	arg.channel.mode = chan_to_phymode(chandef);
	arg.channel.chan_radar =
			!!(channel->flags & IEEE80211_CHAN_RADAR);

	arg.channel.min_घातer = 0;
	arg.channel.max_घातer = channel->max_घातer * 2;
	arg.channel.max_reg_घातer = channel->max_reg_घातer * 2;
	arg.channel.max_antenna_gain = channel->max_antenna_gain * 2;

	reinit_completion(&ar->vdev_setup_करोne);
	reinit_completion(&ar->vdev_delete_करोne);

	ret = ath10k_wmi_vdev_start(ar, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request monitor vdev %i start: %d\n",
			    vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_vdev_setup_sync(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to synchronize setup for monitor vdev %i start: %d\n",
			    vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_wmi_vdev_up(ar, vdev_id, 0, ar->mac_addr);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to put up monitor vdev %i: %d\n",
			    vdev_id, ret);
		जाओ vdev_stop;
	पूर्ण

	ar->monitor_vdev_id = vdev_id;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor vdev %i started\n",
		   ar->monitor_vdev_id);
	वापस 0;

vdev_stop:
	ret = ath10k_wmi_vdev_stop(ar, ar->monitor_vdev_id);
	अगर (ret)
		ath10k_warn(ar, "failed to stop monitor vdev %i after start failure: %d\n",
			    ar->monitor_vdev_id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_monitor_vdev_stop(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_wmi_vdev_करोwn(ar, ar->monitor_vdev_id);
	अगर (ret)
		ath10k_warn(ar, "failed to put down monitor vdev %i: %d\n",
			    ar->monitor_vdev_id, ret);

	reinit_completion(&ar->vdev_setup_करोne);
	reinit_completion(&ar->vdev_delete_करोne);

	ret = ath10k_wmi_vdev_stop(ar, ar->monitor_vdev_id);
	अगर (ret)
		ath10k_warn(ar, "failed to request monitor vdev %i stop: %d\n",
			    ar->monitor_vdev_id, ret);

	ret = ath10k_vdev_setup_sync(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to synchronize monitor vdev %i stop: %d\n",
			    ar->monitor_vdev_id, ret);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor vdev %i stopped\n",
		   ar->monitor_vdev_id);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_monitor_vdev_create(काष्ठा ath10k *ar)
अणु
	पूर्णांक bit, ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (ar->मुक्त_vdev_map == 0) अणु
		ath10k_warn(ar, "failed to find free vdev id for monitor vdev\n");
		वापस -ENOMEM;
	पूर्ण

	bit = __ffs64(ar->मुक्त_vdev_map);

	ar->monitor_vdev_id = bit;

	ret = ath10k_wmi_vdev_create(ar, ar->monitor_vdev_id,
				     WMI_VDEV_TYPE_MONITOR,
				     0, ar->mac_addr);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request monitor vdev %i creation: %d\n",
			    ar->monitor_vdev_id, ret);
		वापस ret;
	पूर्ण

	ar->मुक्त_vdev_map &= ~(1LL << ar->monitor_vdev_id);
	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor vdev %d created\n",
		   ar->monitor_vdev_id);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_monitor_vdev_delete(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_wmi_vdev_delete(ar, ar->monitor_vdev_id);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to request wmi monitor vdev %i removal: %d\n",
			    ar->monitor_vdev_id, ret);
		वापस ret;
	पूर्ण

	ar->मुक्त_vdev_map |= 1LL << ar->monitor_vdev_id;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor vdev %d deleted\n",
		   ar->monitor_vdev_id);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_monitor_start(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_monitor_vdev_create(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to create monitor vdev: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_monitor_vdev_start(ar, ar->monitor_vdev_id);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to start monitor vdev: %d\n", ret);
		ath10k_monitor_vdev_delete(ar);
		वापस ret;
	पूर्ण

	ar->monitor_started = true;
	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor started\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_monitor_stop(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_monitor_vdev_stop(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to stop monitor vdev: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_monitor_vdev_delete(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to delete monitor vdev: %d\n", ret);
		वापस ret;
	पूर्ण

	ar->monitor_started = false;
	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor stopped\n");

	वापस 0;
पूर्ण

अटल bool ath10k_mac_monitor_vdev_is_needed(काष्ठा ath10k *ar)
अणु
	पूर्णांक num_ctx;

	/* At least one chanctx is required to derive a channel to start
	 * monitor vdev on.
	 */
	num_ctx = ath10k_mac_num_chanctxs(ar);
	अगर (num_ctx == 0)
		वापस false;

	/* If there's already an existing special monitor interface then don't
	 * bother creating another monitor vdev.
	 */
	अगर (ar->monitor_arvअगर)
		वापस false;

	वापस ar->monitor ||
	       (!test_bit(ATH10K_FW_FEATURE_ALLOWS_MESH_BCAST,
			  ar->running_fw->fw_file.fw_features) &&
		(ar->filter_flags & FIF_OTHER_BSS)) ||
	       test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags);
पूर्ण

अटल bool ath10k_mac_monitor_vdev_is_allowed(काष्ठा ath10k *ar)
अणु
	पूर्णांक num_ctx;

	num_ctx = ath10k_mac_num_chanctxs(ar);

	/* FIXME: Current पूर्णांकerface combinations and cfg80211/mac80211 code
	 * shouldn't allow this but make sure to prevent handling the following
	 * हाल anyway since multi-channel DFS hasn't been tested at all.
	 */
	अगर (test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags) && num_ctx > 1)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक ath10k_monitor_recalc(काष्ठा ath10k *ar)
अणु
	bool needed;
	bool allowed;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	needed = ath10k_mac_monitor_vdev_is_needed(ar);
	allowed = ath10k_mac_monitor_vdev_is_allowed(ar);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac monitor recalc started? %d needed? %d allowed? %d\n",
		   ar->monitor_started, needed, allowed);

	अगर (WARN_ON(needed && !allowed)) अणु
		अगर (ar->monitor_started) अणु
			ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor stopping disallowed monitor\n");

			ret = ath10k_monitor_stop(ar);
			अगर (ret)
				ath10k_warn(ar, "failed to stop disallowed monitor: %d\n",
					    ret);
				/* not serious */
		पूर्ण

		वापस -EPERM;
	पूर्ण

	अगर (needed == ar->monitor_started)
		वापस 0;

	अगर (needed)
		वापस ath10k_monitor_start(ar);
	अन्यथा
		वापस ath10k_monitor_stop(ar);
पूर्ण

अटल bool ath10k_mac_can_set_cts_prot(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (!arvअगर->is_started) अणु
		ath10k_dbg(ar, ATH10K_DBG_MAC, "defer cts setup, vdev is not ready yet\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक ath10k_mac_set_cts_prot(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	u32 vdev_param;

	lockdep_निश्चित_held(&ar->conf_mutex);

	vdev_param = ar->wmi.vdev_param->protection_mode;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d cts_protection %d\n",
		   arvअगर->vdev_id, arvअगर->use_cts_prot);

	वापस ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
					 arvअगर->use_cts_prot ? 1 : 0);
पूर्ण

अटल पूर्णांक ath10k_recalc_rtscts_prot(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	u32 vdev_param, rts_cts = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	vdev_param = ar->wmi.vdev_param->enable_rtscts;

	rts_cts |= SM(WMI_RTSCTS_ENABLED, WMI_RTSCTS_SET);

	अगर (arvअगर->num_legacy_stations > 0)
		rts_cts |= SM(WMI_RTSCTS_ACROSS_SW_RETRIES,
			      WMI_RTSCTS_PROखाता);
	अन्यथा
		rts_cts |= SM(WMI_RTSCTS_FOR_SECOND_RATESERIES,
			      WMI_RTSCTS_PROखाता);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d recalc rts/cts prot %d\n",
		   arvअगर->vdev_id, rts_cts);

	वापस ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
					 rts_cts);
पूर्ण

अटल पूर्णांक ath10k_start_cac(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	set_bit(ATH10K_CAC_RUNNING, &ar->dev_flags);

	ret = ath10k_monitor_recalc(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to start monitor (cac): %d\n", ret);
		clear_bit(ATH10K_CAC_RUNNING, &ar->dev_flags);
		वापस ret;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac cac start monitor vdev %d\n",
		   ar->monitor_vdev_id);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_stop_cac(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);

	/* CAC is not running - करो nothing */
	अगर (!test_bit(ATH10K_CAC_RUNNING, &ar->dev_flags))
		वापस 0;

	clear_bit(ATH10K_CAC_RUNNING, &ar->dev_flags);
	ath10k_monitor_stop(ar);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac cac finished\n");

	वापस 0;
पूर्ण

अटल व्योम ath10k_mac_has_radar_iter(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_chanctx_conf *conf,
				      व्योम *data)
अणु
	bool *ret = data;

	अगर (!*ret && conf->radar_enabled)
		*ret = true;
पूर्ण

अटल bool ath10k_mac_has_radar_enabled(काष्ठा ath10k *ar)
अणु
	bool has_radar = false;

	ieee80211_iter_chan_contexts_atomic(ar->hw,
					    ath10k_mac_has_radar_iter,
					    &has_radar);

	वापस has_radar;
पूर्ण

अटल व्योम ath10k_recalc_radar_detection(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ath10k_stop_cac(ar);

	अगर (!ath10k_mac_has_radar_enabled(ar))
		वापस;

	अगर (ar->num_started_vdevs > 0)
		वापस;

	ret = ath10k_start_cac(ar);
	अगर (ret) अणु
		/*
		 * Not possible to start CAC on current channel so starting
		 * radiation is not allowed, make this channel DFS_UNAVAILABLE
		 * by indicating that radar was detected.
		 */
		ath10k_warn(ar, "failed to start CAC: %d\n", ret);
		ieee80211_radar_detected(ar->hw);
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_vdev_stop(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_करोne);
	reinit_completion(&ar->vdev_delete_करोne);

	ret = ath10k_wmi_vdev_stop(ar, arvअगर->vdev_id);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to stop WMI vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_vdev_setup_sync(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to synchronize setup for vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	WARN_ON(ar->num_started_vdevs == 0);

	अगर (ar->num_started_vdevs != 0) अणु
		ar->num_started_vdevs--;
		ath10k_recalc_radar_detection(ar);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_vdev_start_restart(काष्ठा ath10k_vअगर *arvअगर,
				     स्थिर काष्ठा cfg80211_chan_def *chandef,
				     bool restart)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा wmi_vdev_start_request_arg arg = अणुपूर्ण;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_करोne);
	reinit_completion(&ar->vdev_delete_करोne);

	arg.vdev_id = arvअगर->vdev_id;
	arg.dtim_period = arvअगर->dtim_period;
	arg.bcn_पूर्णांकval = arvअगर->beacon_पूर्णांकerval;

	arg.channel.freq = chandef->chan->center_freq;
	arg.channel.band_center_freq1 = chandef->center_freq1;
	arg.channel.band_center_freq2 = chandef->center_freq2;
	arg.channel.mode = chan_to_phymode(chandef);

	arg.channel.min_घातer = 0;
	arg.channel.max_घातer = chandef->chan->max_घातer * 2;
	arg.channel.max_reg_घातer = chandef->chan->max_reg_घातer * 2;
	arg.channel.max_antenna_gain = chandef->chan->max_antenna_gain * 2;

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP) अणु
		arg.ssid = arvअगर->u.ap.ssid;
		arg.ssid_len = arvअगर->u.ap.ssid_len;
		arg.hidden_ssid = arvअगर->u.ap.hidden_ssid;

		/* For now allow DFS क्रम AP mode */
		arg.channel.chan_radar =
			!!(chandef->chan->flags & IEEE80211_CHAN_RADAR);
	पूर्ण अन्यथा अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_IBSS) अणु
		arg.ssid = arvअगर->vअगर->bss_conf.ssid;
		arg.ssid_len = arvअगर->vअगर->bss_conf.ssid_len;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac vdev %d start center_freq %d phymode %s\n",
		   arg.vdev_id, arg.channel.freq,
		   ath10k_wmi_phymode_str(arg.channel.mode));

	अगर (restart)
		ret = ath10k_wmi_vdev_restart(ar, &arg);
	अन्यथा
		ret = ath10k_wmi_vdev_start(ar, &arg);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to start WMI vdev %i: %d\n",
			    arg.vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_vdev_setup_sync(ar);
	अगर (ret) अणु
		ath10k_warn(ar,
			    "failed to synchronize setup for vdev %i restart %d: %d\n",
			    arg.vdev_id, restart, ret);
		वापस ret;
	पूर्ण

	ar->num_started_vdevs++;
	ath10k_recalc_radar_detection(ar);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_vdev_start(काष्ठा ath10k_vअगर *arvअगर,
			     स्थिर काष्ठा cfg80211_chan_def *def)
अणु
	वापस ath10k_vdev_start_restart(arvअगर, def, false);
पूर्ण

अटल पूर्णांक ath10k_vdev_restart(काष्ठा ath10k_vअगर *arvअगर,
			       स्थिर काष्ठा cfg80211_chan_def *def)
अणु
	वापस ath10k_vdev_start_restart(arvअगर, def, true);
पूर्ण

अटल पूर्णांक ath10k_mac_setup_bcn_p2p_ie(काष्ठा ath10k_vअगर *arvअगर,
				       काष्ठा sk_buff *bcn)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ieee80211_mgmt *mgmt;
	स्थिर u8 *p2p_ie;
	पूर्णांक ret;

	अगर (arvअगर->vअगर->type != NL80211_IFTYPE_AP || !arvअगर->vअगर->p2p)
		वापस 0;

	mgmt = (व्योम *)bcn->data;
	p2p_ie = cfg80211_find_venकरोr_ie(WLAN_OUI_WFA, WLAN_OUI_TYPE_WFA_P2P,
					 mgmt->u.beacon.variable,
					 bcn->len - (mgmt->u.beacon.variable -
						     bcn->data));
	अगर (!p2p_ie)
		वापस -ENOENT;

	ret = ath10k_wmi_p2p_go_bcn_ie(ar, arvअगर->vdev_id, p2p_ie);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit p2p go bcn ie for vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_हटाओ_venकरोr_ie(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक oui,
				       u8 oui_type, माप_प्रकार ie_offset)
अणु
	माप_प्रकार len;
	स्थिर u8 *next;
	स्थिर u8 *end;
	u8 *ie;

	अगर (WARN_ON(skb->len < ie_offset))
		वापस -EINVAL;

	ie = (u8 *)cfg80211_find_venकरोr_ie(oui, oui_type,
					   skb->data + ie_offset,
					   skb->len - ie_offset);
	अगर (!ie)
		वापस -ENOENT;

	len = ie[1] + 2;
	end = skb->data + skb->len;
	next = ie + len;

	अगर (WARN_ON(next > end))
		वापस -EINVAL;

	स_हटाओ(ie, next, end - next);
	skb_trim(skb, skb->len - len);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_setup_bcn_पंचांगpl(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ieee80211_hw *hw = ar->hw;
	काष्ठा ieee80211_vअगर *vअगर = arvअगर->vअगर;
	काष्ठा ieee80211_mutable_offsets offs = अणुपूर्ण;
	काष्ठा sk_buff *bcn;
	पूर्णांक ret;

	अगर (!test_bit(WMI_SERVICE_BEACON_OFFLOAD, ar->wmi.svc_map))
		वापस 0;

	अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_AP &&
	    arvअगर->vdev_type != WMI_VDEV_TYPE_IBSS)
		वापस 0;

	bcn = ieee80211_beacon_get_ढाँचा(hw, vअगर, &offs);
	अगर (!bcn) अणु
		ath10k_warn(ar, "failed to get beacon template from mac80211\n");
		वापस -EPERM;
	पूर्ण

	ret = ath10k_mac_setup_bcn_p2p_ie(arvअगर, bcn);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to setup p2p go bcn ie: %d\n", ret);
		kमुक्त_skb(bcn);
		वापस ret;
	पूर्ण

	/* P2P IE is inserted by firmware स्वतःmatically (as configured above)
	 * so हटाओ it from the base beacon ढाँचा to aव्योम duplicate P2P
	 * IEs in beacon frames.
	 */
	ath10k_mac_हटाओ_venकरोr_ie(bcn, WLAN_OUI_WFA, WLAN_OUI_TYPE_WFA_P2P,
				    दुरत्व(काष्ठा ieee80211_mgmt,
					     u.beacon.variable));

	ret = ath10k_wmi_bcn_पंचांगpl(ar, arvअगर->vdev_id, offs.tim_offset, bcn, 0,
				  0, शून्य, 0);
	kमुक्त_skb(bcn);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit beacon template command: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_setup_prb_पंचांगpl(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ieee80211_hw *hw = ar->hw;
	काष्ठा ieee80211_vअगर *vअगर = arvअगर->vअगर;
	काष्ठा sk_buff *prb;
	पूर्णांक ret;

	अगर (!test_bit(WMI_SERVICE_BEACON_OFFLOAD, ar->wmi.svc_map))
		वापस 0;

	अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_AP)
		वापस 0;

	 /* For mesh, probe response and beacon share the same ढाँचा */
	अगर (ieee80211_vअगर_is_mesh(vअगर))
		वापस 0;

	prb = ieee80211_proberesp_get(hw, vअगर);
	अगर (!prb) अणु
		ath10k_warn(ar, "failed to get probe resp template from mac80211\n");
		वापस -EPERM;
	पूर्ण

	ret = ath10k_wmi_prb_पंचांगpl(ar, arvअगर->vdev_id, prb);
	kमुक्त_skb(prb);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit probe resp template command: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_vअगर_fix_hidden_ssid(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा cfg80211_chan_def def;
	पूर्णांक ret;

	/* When originally vdev is started during assign_vअगर_chanctx() some
	 * inक्रमmation is missing, notably SSID. Firmware revisions with beacon
	 * offloading require the SSID to be provided during vdev (re)start to
	 * handle hidden SSID properly.
	 *
	 * Vdev restart must be करोne after vdev has been both started and
	 * upped. Otherwise some firmware revisions (at least 10.2) fail to
	 * deliver vdev restart response event causing समयouts during vdev
	 * syncing in ath10k.
	 *
	 * Note: The vdev करोwn/up and ढाँचा reinstallation could be skipped
	 * since only wmi-tlv firmware are known to have beacon offload and
	 * wmi-tlv करोesn't seem to misbehave like 10.2 wrt vdev restart
	 * response delivery. It's probably more robust to keep it as is.
	 */
	अगर (!test_bit(WMI_SERVICE_BEACON_OFFLOAD, ar->wmi.svc_map))
		वापस 0;

	अगर (WARN_ON(!arvअगर->is_started))
		वापस -EINVAL;

	अगर (WARN_ON(!arvअगर->is_up))
		वापस -EINVAL;

	अगर (WARN_ON(ath10k_mac_vअगर_chan(arvअगर->vअगर, &def)))
		वापस -EINVAL;

	ret = ath10k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to bring down ap vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	/* Vdev करोwn reset beacon & presp ढाँचाs. Reinstall them. Otherwise
	 * firmware will crash upon vdev up.
	 */

	ret = ath10k_mac_setup_bcn_पंचांगpl(arvअगर);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to update beacon template: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_mac_setup_prb_पंचांगpl(arvअगर);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to update presp template: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ath10k_vdev_restart(arvअगर, &def);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to restart ap vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_wmi_vdev_up(arvअगर->ar, arvअगर->vdev_id, arvअगर->aid,
				 arvअगर->bssid);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to bring up ap vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_control_beaconing(काष्ठा ath10k_vअगर *arvअगर,
				     काष्ठा ieee80211_bss_conf *info)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	अगर (!info->enable_beacon) अणु
		ret = ath10k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);
		अगर (ret)
			ath10k_warn(ar, "failed to down vdev_id %i: %d\n",
				    arvअगर->vdev_id, ret);

		arvअगर->is_up = false;

		spin_lock_bh(&arvअगर->ar->data_lock);
		ath10k_mac_vअगर_beacon_मुक्त(arvअगर);
		spin_unlock_bh(&arvअगर->ar->data_lock);

		वापस;
	पूर्ण

	arvअगर->tx_seq_no = 0x1000;

	arvअगर->aid = 0;
	ether_addr_copy(arvअगर->bssid, info->bssid);

	ret = ath10k_wmi_vdev_up(arvअगर->ar, arvअगर->vdev_id, arvअगर->aid,
				 arvअगर->bssid);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to bring up vdev %d: %i\n",
			    arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	arvअगर->is_up = true;

	ret = ath10k_mac_vअगर_fix_hidden_ssid(arvअगर);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to fix hidden ssid for vdev %i, expect trouble: %d\n",
			    arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d up\n", arvअगर->vdev_id);
पूर्ण

अटल व्योम ath10k_control_ibss(काष्ठा ath10k_vअगर *arvअगर,
				काष्ठा ieee80211_bss_conf *info,
				स्थिर u8 self_peer[ETH_ALEN])
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	u32 vdev_param;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	अगर (!info->ibss_joined) अणु
		अगर (is_zero_ether_addr(arvअगर->bssid))
			वापस;

		eth_zero_addr(arvअगर->bssid);

		वापस;
	पूर्ण

	vdev_param = arvअगर->ar->wmi.vdev_param->atim_winकरोw;
	ret = ath10k_wmi_vdev_set_param(arvअगर->ar, arvअगर->vdev_id, vdev_param,
					ATH10K_DEFAULT_ATIM);
	अगर (ret)
		ath10k_warn(ar, "failed to set IBSS ATIM for vdev %d: %d\n",
			    arvअगर->vdev_id, ret);
पूर्ण

अटल पूर्णांक ath10k_mac_vअगर_recalc_ps_wake_threshold(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	u32 param;
	u32 value;
	पूर्णांक ret;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	अगर (arvअगर->u.sta.uapsd)
		value = WMI_STA_PS_TX_WAKE_THRESHOLD_NEVER;
	अन्यथा
		value = WMI_STA_PS_TX_WAKE_THRESHOLD_ALWAYS;

	param = WMI_STA_PS_PARAM_TX_WAKE_THRESHOLD;
	ret = ath10k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id, param, value);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit ps wake threshold %u on vdev %i: %d\n",
			    value, arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_vअगर_recalc_ps_poll_count(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	u32 param;
	u32 value;
	पूर्णांक ret;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	अगर (arvअगर->u.sta.uapsd)
		value = WMI_STA_PS_PSPOLL_COUNT_UAPSD;
	अन्यथा
		value = WMI_STA_PS_PSPOLL_COUNT_NO_MAX;

	param = WMI_STA_PS_PARAM_PSPOLL_COUNT;
	ret = ath10k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
					  param, value);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit ps poll count %u on vdev %i: %d\n",
			    value, arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_num_vअगरs_started(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक num = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list)
		अगर (arvअगर->is_started)
			num++;

	वापस num;
पूर्ण

अटल पूर्णांक ath10k_mac_vअगर_setup_ps(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ieee80211_vअगर *vअगर = arvअगर->vअगर;
	काष्ठा ieee80211_conf *conf = &ar->hw->conf;
	क्रमागत wmi_sta_घातersave_param param;
	क्रमागत wmi_sta_ps_mode psmode;
	पूर्णांक ret;
	पूर्णांक ps_समयout;
	bool enable_ps;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	अगर (arvअगर->vअगर->type != NL80211_IFTYPE_STATION)
		वापस 0;

	enable_ps = arvअगर->ps;

	अगर (enable_ps && ath10k_mac_num_vअगरs_started(ar) > 1 &&
	    !test_bit(ATH10K_FW_FEATURE_MULTI_VIF_PS_SUPPORT,
		      ar->running_fw->fw_file.fw_features)) अणु
		ath10k_warn(ar, "refusing to enable ps on vdev %i: not supported by fw\n",
			    arvअगर->vdev_id);
		enable_ps = false;
	पूर्ण

	अगर (!arvअगर->is_started) अणु
		/* mac80211 can update vअगर घातersave state जबतक disconnected.
		 * Firmware करोesn't behave nicely and consumes more घातer than
		 * necessary अगर PS is disabled on a non-started vdev. Hence
		 * क्रमce-enable PS क्रम non-running vdevs.
		 */
		psmode = WMI_STA_PS_MODE_ENABLED;
	पूर्ण अन्यथा अगर (enable_ps) अणु
		psmode = WMI_STA_PS_MODE_ENABLED;
		param = WMI_STA_PS_PARAM_INACTIVITY_TIME;

		ps_समयout = conf->dynamic_ps_समयout;
		अगर (ps_समयout == 0) अणु
			/* Firmware करोesn't like 0 */
			ps_समयout = ieee80211_tu_to_usec(
				vअगर->bss_conf.beacon_पूर्णांक) / 1000;
		पूर्ण

		ret = ath10k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id, param,
						  ps_समयout);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set inactivity time for vdev %d: %i\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		psmode = WMI_STA_PS_MODE_DISABLED;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d psmode %s\n",
		   arvअगर->vdev_id, psmode ? "enable" : "disable");

	ret = ath10k_wmi_set_psmode(ar, arvअगर->vdev_id, psmode);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set PS Mode %d for vdev %d: %d\n",
			    psmode, arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_vअगर_disable_keepalive(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा wmi_sta_keepalive_arg arg = अणुपूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_STA)
		वापस 0;

	अगर (!test_bit(WMI_SERVICE_STA_KEEP_ALIVE, ar->wmi.svc_map))
		वापस 0;

	/* Some firmware revisions have a bug and ignore the `enabled` field.
	 * Instead use the पूर्णांकerval to disable the keepalive.
	 */
	arg.vdev_id = arvअगर->vdev_id;
	arg.enabled = 1;
	arg.method = WMI_STA_KEEPALIVE_METHOD_शून्य_FRAME;
	arg.पूर्णांकerval = WMI_STA_KEEPALIVE_INTERVAL_DISABLE;

	ret = ath10k_wmi_sta_keepalive(ar, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit keepalive on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_mac_vअगर_ap_csa_count_करोwn(काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ieee80211_vअगर *vअगर = arvअगर->vअगर;
	पूर्णांक ret;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	अगर (WARN_ON(!test_bit(WMI_SERVICE_BEACON_OFFLOAD, ar->wmi.svc_map)))
		वापस;

	अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_AP)
		वापस;

	अगर (!vअगर->csa_active)
		वापस;

	अगर (!arvअगर->is_up)
		वापस;

	अगर (!ieee80211_beacon_cntdwn_is_complete(vअगर)) अणु
		ieee80211_beacon_update_cntdwn(vअगर);

		ret = ath10k_mac_setup_bcn_पंचांगpl(arvअगर);
		अगर (ret)
			ath10k_warn(ar, "failed to update bcn tmpl during csa: %d\n",
				    ret);

		ret = ath10k_mac_setup_prb_पंचांगpl(arvअगर);
		अगर (ret)
			ath10k_warn(ar, "failed to update prb tmpl during csa: %d\n",
				    ret);
	पूर्ण अन्यथा अणु
		ieee80211_csa_finish(vअगर);
	पूर्ण
पूर्ण

अटल व्योम ath10k_mac_vअगर_ap_csa_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k_vअगर *arvअगर = container_of(work, काष्ठा ath10k_vअगर,
						ap_csa_work);
	काष्ठा ath10k *ar = arvअगर->ar;

	mutex_lock(&ar->conf_mutex);
	ath10k_mac_vअगर_ap_csa_count_करोwn(arvअगर);
	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल व्योम ath10k_mac_handle_beacon_iter(व्योम *data, u8 *mac,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *skb = data;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	अगर (!ether_addr_equal(mgmt->bssid, vअगर->bss_conf.bssid))
		वापस;

	cancel_delayed_work(&arvअगर->connection_loss_work);
पूर्ण

व्योम ath10k_mac_handle_beacon(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   ATH10K_ITER_NORMAL_FLAGS,
						   ath10k_mac_handle_beacon_iter,
						   skb);
पूर्ण

अटल व्योम ath10k_mac_handle_beacon_miss_iter(व्योम *data, u8 *mac,
					       काष्ठा ieee80211_vअगर *vअगर)
अणु
	u32 *vdev_id = data;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k *ar = arvअगर->ar;
	काष्ठा ieee80211_hw *hw = ar->hw;

	अगर (arvअगर->vdev_id != *vdev_id)
		वापस;

	अगर (!arvअगर->is_up)
		वापस;

	ieee80211_beacon_loss(vअगर);

	/* Firmware करोesn't report beacon loss events repeatedly. If AP probe
	 * (करोne by mac80211) succeeds but beacons करो not resume then it
	 * करोesn't make sense to जारी operation. Queue connection loss work
	 * which can be cancelled when beacon is received.
	 */
	ieee80211_queue_delayed_work(hw, &arvअगर->connection_loss_work,
				     ATH10K_CONNECTION_LOSS_HZ);
पूर्ण

व्योम ath10k_mac_handle_beacon_miss(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   ATH10K_ITER_NORMAL_FLAGS,
						   ath10k_mac_handle_beacon_miss_iter,
						   &vdev_id);
पूर्ण

अटल व्योम ath10k_mac_vअगर_sta_connection_loss_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k_vअगर *arvअगर = container_of(work, काष्ठा ath10k_vअगर,
						connection_loss_work.work);
	काष्ठा ieee80211_vअगर *vअगर = arvअगर->vअगर;

	अगर (!arvअगर->is_up)
		वापस;

	ieee80211_connection_loss(vअगर);
पूर्ण

/**********************/
/* Station management */
/**********************/

अटल u32 ath10k_peer_assoc_h_listen_पूर्णांकval(काष्ठा ath10k *ar,
					     काष्ठा ieee80211_vअगर *vअगर)
अणु
	/* Some firmware revisions have unstable STA घातersave when listen
	 * पूर्णांकerval is set too high (e.g. 5). The symptoms are firmware करोesn't
	 * generate NullFunc frames properly even अगर buffered frames have been
	 * indicated in Beacon TIM. Firmware would selकरोm wake up to pull
	 * buffered frames. Often pinging the device from AP would simply fail.
	 *
	 * As a workaround set it to 1.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		वापस 1;

	वापस ar->hw->conf.listen_पूर्णांकerval;
पूर्ण

अटल व्योम ath10k_peer_assoc_h_basic(काष्ठा ath10k *ar,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	u32 aid;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		aid = vअगर->bss_conf.aid;
	अन्यथा
		aid = sta->aid;

	ether_addr_copy(arg->addr, sta->addr);
	arg->vdev_id = arvअगर->vdev_id;
	arg->peer_aid = aid;
	arg->peer_flags |= arvअगर->ar->wmi.peer_flags->auth;
	arg->peer_listen_पूर्णांकval = ath10k_peer_assoc_h_listen_पूर्णांकval(ar, vअगर);
	arg->peer_num_spatial_streams = 1;
	arg->peer_caps = vअगर->bss_conf.assoc_capability;
पूर्ण

अटल व्योम ath10k_peer_assoc_h_crypto(काष्ठा ath10k *ar,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta,
				       काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा ieee80211_bss_conf *info = &vअगर->bss_conf;
	काष्ठा cfg80211_chan_def def;
	काष्ठा cfg80211_bss *bss;
	स्थिर u8 *rsnie = शून्य;
	स्थिर u8 *wpaie = शून्य;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(ath10k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	bss = cfg80211_get_bss(ar->hw->wiphy, def.chan, info->bssid,
			       info->ssid_len ? info->ssid : शून्य, info->ssid_len,
			       IEEE80211_BSS_TYPE_ANY, IEEE80211_PRIVACY_ANY);
	अगर (bss) अणु
		स्थिर काष्ठा cfg80211_bss_ies *ies;

		rcu_पढ़ो_lock();
		rsnie = ieee80211_bss_get_ie(bss, WLAN_EID_RSN);

		ies = rcu_dereference(bss->ies);

		wpaie = cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
						WLAN_OUI_TYPE_MICROSOFT_WPA,
						ies->data,
						ies->len);
		rcu_पढ़ो_unlock();
		cfg80211_put_bss(ar->hw->wiphy, bss);
	पूर्ण

	/* FIXME: base on RSN IE/WPA IE is a correct idea? */
	अगर (rsnie || wpaie) अणु
		ath10k_dbg(ar, ATH10K_DBG_WMI, "%s: rsn ie found\n", __func__);
		arg->peer_flags |= ar->wmi.peer_flags->need_ptk_4_way;
	पूर्ण

	अगर (wpaie) अणु
		ath10k_dbg(ar, ATH10K_DBG_WMI, "%s: wpa ie found\n", __func__);
		arg->peer_flags |= ar->wmi.peer_flags->need_gtk_2_way;
	पूर्ण

	अगर (sta->mfp &&
	    test_bit(ATH10K_FW_FEATURE_MFP_SUPPORT,
		     ar->running_fw->fw_file.fw_features)) अणु
		arg->peer_flags |= ar->wmi.peer_flags->pmf;
	पूर्ण
पूर्ण

अटल व्योम ath10k_peer_assoc_h_rates(काष्ठा ath10k *ar,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा wmi_rate_set_arg *rateset = &arg->peer_legacy_rates;
	काष्ठा cfg80211_chan_def def;
	स्थिर काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा ieee80211_rate *rates;
	क्रमागत nl80211_band band;
	u32 ratemask;
	u8 rate;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(ath10k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	band = def.chan->band;
	sband = ar->hw->wiphy->bands[band];
	ratemask = sta->supp_rates[band];
	ratemask &= arvअगर->bitrate_mask.control[band].legacy;
	rates = sband->bitrates;

	rateset->num_rates = 0;

	क्रम (i = 0; i < 32; i++, ratemask >>= 1, rates++) अणु
		अगर (!(ratemask & 1))
			जारी;

		rate = ath10k_mac_bitrate_to_rate(rates->bitrate);
		rateset->rates[rateset->num_rates] = rate;
		rateset->num_rates++;
	पूर्ण
पूर्ण

अटल bool
ath10k_peer_assoc_h_ht_masked(स्थिर u8 ht_mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
अणु
	पूर्णांक nss;

	क्रम (nss = 0; nss < IEEE80211_HT_MCS_MASK_LEN; nss++)
		अगर (ht_mcs_mask[nss])
			वापस false;

	वापस true;
पूर्ण

अटल bool
ath10k_peer_assoc_h_vht_masked(स्थिर u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
अणु
	पूर्णांक nss;

	क्रम (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++)
		अगर (vht_mcs_mask[nss])
			वापस false;

	वापस true;
पूर्ण

अटल व्योम ath10k_peer_assoc_h_ht(काष्ठा ath10k *ar,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	स्थिर काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	स्थिर u8 *ht_mcs_mask;
	स्थिर u16 *vht_mcs_mask;
	पूर्णांक i, n;
	u8 max_nss;
	u32 stbc;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(ath10k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	अगर (!ht_cap->ht_supported)
		वापस;

	band = def.chan->band;
	ht_mcs_mask = arvअगर->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvअगर->bitrate_mask.control[band].vht_mcs;

	अगर (ath10k_peer_assoc_h_ht_masked(ht_mcs_mask) &&
	    ath10k_peer_assoc_h_vht_masked(vht_mcs_mask))
		वापस;

	arg->peer_flags |= ar->wmi.peer_flags->ht;
	arg->peer_max_mpdu = (1 << (IEEE80211_HT_MAX_AMPDU_FACTOR +
				    ht_cap->ampdu_factor)) - 1;

	arg->peer_mpdu_density =
		ath10k_parse_mpdudensity(ht_cap->ampdu_density);

	arg->peer_ht_caps = ht_cap->cap;
	arg->peer_rate_caps |= WMI_RC_HT_FLAG;

	अगर (ht_cap->cap & IEEE80211_HT_CAP_LDPC_CODING)
		arg->peer_flags |= ar->wmi.peer_flags->ldbc;

	अगर (sta->bandwidth >= IEEE80211_STA_RX_BW_40) अणु
		arg->peer_flags |= ar->wmi.peer_flags->bw40;
		arg->peer_rate_caps |= WMI_RC_CW40_FLAG;
	पूर्ण

	अगर (arvअगर->bitrate_mask.control[band].gi != NL80211_TXRATE_FORCE_LGI) अणु
		अगर (ht_cap->cap & IEEE80211_HT_CAP_SGI_20)
			arg->peer_rate_caps |= WMI_RC_SGI_FLAG;

		अगर (ht_cap->cap & IEEE80211_HT_CAP_SGI_40)
			arg->peer_rate_caps |= WMI_RC_SGI_FLAG;
	पूर्ण

	अगर (ht_cap->cap & IEEE80211_HT_CAP_TX_STBC) अणु
		arg->peer_rate_caps |= WMI_RC_TX_STBC_FLAG;
		arg->peer_flags |= ar->wmi.peer_flags->stbc;
	पूर्ण

	अगर (ht_cap->cap & IEEE80211_HT_CAP_RX_STBC) अणु
		stbc = ht_cap->cap & IEEE80211_HT_CAP_RX_STBC;
		stbc = stbc >> IEEE80211_HT_CAP_RX_STBC_SHIFT;
		stbc = stbc << WMI_RC_RX_STBC_FLAG_S;
		arg->peer_rate_caps |= stbc;
		arg->peer_flags |= ar->wmi.peer_flags->stbc;
	पूर्ण

	अगर (ht_cap->mcs.rx_mask[1] && ht_cap->mcs.rx_mask[2])
		arg->peer_rate_caps |= WMI_RC_TS_FLAG;
	अन्यथा अगर (ht_cap->mcs.rx_mask[1])
		arg->peer_rate_caps |= WMI_RC_DS_FLAG;

	क्रम (i = 0, n = 0, max_nss = 0; i < IEEE80211_HT_MCS_MASK_LEN * 8; i++)
		अगर ((ht_cap->mcs.rx_mask[i / 8] & BIT(i % 8)) &&
		    (ht_mcs_mask[i / 8] & BIT(i % 8))) अणु
			max_nss = (i / 8) + 1;
			arg->peer_ht_rates.rates[n++] = i;
		पूर्ण

	/*
	 * This is a workaround क्रम HT-enabled STAs which अवरोध the spec
	 * and have no HT capabilities RX mask (no HT RX MCS map).
	 *
	 * As per spec, in section 20.3.5 Modulation and coding scheme (MCS),
	 * MCS 0 through 7 are mandatory in 20MHz with 800 ns GI at all STAs.
	 *
	 * Firmware निश्चितs अगर such situation occurs.
	 */
	अगर (n == 0) अणु
		arg->peer_ht_rates.num_rates = 8;
		क्रम (i = 0; i < arg->peer_ht_rates.num_rates; i++)
			arg->peer_ht_rates.rates[i] = i;
	पूर्ण अन्यथा अणु
		arg->peer_ht_rates.num_rates = n;
		arg->peer_num_spatial_streams = min(sta->rx_nss, max_nss);
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac ht peer %pM mcs cnt %d nss %d\n",
		   arg->addr,
		   arg->peer_ht_rates.num_rates,
		   arg->peer_num_spatial_streams);
पूर्ण

अटल पूर्णांक ath10k_peer_assoc_qos_ap(काष्ठा ath10k *ar,
				    काष्ठा ath10k_vअगर *arvअगर,
				    काष्ठा ieee80211_sta *sta)
अणु
	u32 uapsd = 0;
	u32 max_sp = 0;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (sta->wme && sta->uapsd_queues) अणु
		ath10k_dbg(ar, ATH10K_DBG_MAC, "mac uapsd_queues 0x%x max_sp %d\n",
			   sta->uapsd_queues, sta->max_sp);

		अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
			uapsd |= WMI_AP_PS_UAPSD_AC3_DELIVERY_EN |
				 WMI_AP_PS_UAPSD_AC3_TRIGGER_EN;
		अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI)
			uapsd |= WMI_AP_PS_UAPSD_AC2_DELIVERY_EN |
				 WMI_AP_PS_UAPSD_AC2_TRIGGER_EN;
		अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)
			uapsd |= WMI_AP_PS_UAPSD_AC1_DELIVERY_EN |
				 WMI_AP_PS_UAPSD_AC1_TRIGGER_EN;
		अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE)
			uapsd |= WMI_AP_PS_UAPSD_AC0_DELIVERY_EN |
				 WMI_AP_PS_UAPSD_AC0_TRIGGER_EN;

		अगर (sta->max_sp < MAX_WMI_AP_PS_PEER_PARAM_MAX_SP)
			max_sp = sta->max_sp;

		ret = ath10k_wmi_set_ap_ps_param(ar, arvअगर->vdev_id,
						 sta->addr,
						 WMI_AP_PS_PEER_PARAM_UAPSD,
						 uapsd);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set ap ps peer param uapsd for vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण

		ret = ath10k_wmi_set_ap_ps_param(ar, arvअगर->vdev_id,
						 sta->addr,
						 WMI_AP_PS_PEER_PARAM_MAX_SP,
						 max_sp);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set ap ps peer param max sp for vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण

		/* TODO setup this based on STA listen पूर्णांकerval and
		 * beacon पूर्णांकerval. Currently we करोn't know
		 * sta->listen_पूर्णांकerval - mac80211 patch required.
		 * Currently use 10 seconds
		 */
		ret = ath10k_wmi_set_ap_ps_param(ar, arvअगर->vdev_id, sta->addr,
						 WMI_AP_PS_PEER_PARAM_AGEOUT_TIME,
						 10);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set ap ps peer param ageout time for vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u16
ath10k_peer_assoc_h_vht_limit(u16 tx_mcs_set,
			      स्थिर u16 vht_mcs_limit[NL80211_VHT_NSS_MAX])
अणु
	पूर्णांक idx_limit;
	पूर्णांक nss;
	u16 mcs_map;
	u16 mcs;

	क्रम (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++) अणु
		mcs_map = ath10k_mac_get_max_vht_mcs_map(tx_mcs_set, nss) &
			  vht_mcs_limit[nss];

		अगर (mcs_map)
			idx_limit = fls(mcs_map) - 1;
		अन्यथा
			idx_limit = -1;

		चयन (idx_limit) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 6:
		शेष:
			/* see ath10k_mac_can_set_bitrate_mask() */
			WARN_ON(1);
			fallthrough;
		हाल -1:
			mcs = IEEE80211_VHT_MCS_NOT_SUPPORTED;
			अवरोध;
		हाल 7:
			mcs = IEEE80211_VHT_MCS_SUPPORT_0_7;
			अवरोध;
		हाल 8:
			mcs = IEEE80211_VHT_MCS_SUPPORT_0_8;
			अवरोध;
		हाल 9:
			mcs = IEEE80211_VHT_MCS_SUPPORT_0_9;
			अवरोध;
		पूर्ण

		tx_mcs_set &= ~(0x3 << (nss * 2));
		tx_mcs_set |= mcs << (nss * 2);
	पूर्ण

	वापस tx_mcs_set;
पूर्ण

अटल u32 get_160mhz_nss_from_maxrate(पूर्णांक rate)
अणु
	u32 nss;

	चयन (rate) अणु
	हाल 780:
		nss = 1;
		अवरोध;
	हाल 1560:
		nss = 2;
		अवरोध;
	हाल 2106:
		nss = 3; /* not support MCS9 from spec*/
		अवरोध;
	हाल 3120:
		nss = 4;
		अवरोध;
	शेष:
		 nss = 1;
	पूर्ण

	वापस nss;
पूर्ण

अटल व्योम ath10k_peer_assoc_h_vht(काष्ठा ath10k *ar,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta,
				    काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	स्थिर काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_hw_params *hw = &ar->hw_params;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	स्थिर u16 *vht_mcs_mask;
	u8 ampdu_factor;
	u8 max_nss, vht_mcs;
	पूर्णांक i;

	अगर (WARN_ON(ath10k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	अगर (!vht_cap->vht_supported)
		वापस;

	band = def.chan->band;
	vht_mcs_mask = arvअगर->bitrate_mask.control[band].vht_mcs;

	अगर (ath10k_peer_assoc_h_vht_masked(vht_mcs_mask))
		वापस;

	arg->peer_flags |= ar->wmi.peer_flags->vht;

	अगर (def.chan->band == NL80211_BAND_2GHZ)
		arg->peer_flags |= ar->wmi.peer_flags->vht_2g;

	arg->peer_vht_caps = vht_cap->cap;

	ampdu_factor = (vht_cap->cap &
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK) >>
		       IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;

	/* Workaround: Some Netgear/Linksys 11ac APs set Rx A-MPDU factor to
	 * zero in VHT IE. Using it would result in degraded throughput.
	 * arg->peer_max_mpdu at this poपूर्णांक contains HT max_mpdu so keep
	 * it अगर VHT max_mpdu is smaller.
	 */
	arg->peer_max_mpdu = max(arg->peer_max_mpdu,
				 (1U << (IEEE80211_HT_MAX_AMPDU_FACTOR +
					ampdu_factor)) - 1);

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_80)
		arg->peer_flags |= ar->wmi.peer_flags->bw80;

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_160)
		arg->peer_flags |= ar->wmi.peer_flags->bw160;

	/* Calculate peer NSS capability from VHT capabilities अगर STA
	 * supports VHT.
	 */
	क्रम (i = 0, max_nss = 0, vht_mcs = 0; i < NL80211_VHT_NSS_MAX; i++) अणु
		vht_mcs = __le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map) >>
			  (2 * i) & 3;

		अगर ((vht_mcs != IEEE80211_VHT_MCS_NOT_SUPPORTED) &&
		    vht_mcs_mask[i])
			max_nss = i + 1;
	पूर्ण
	arg->peer_num_spatial_streams = min(sta->rx_nss, max_nss);
	arg->peer_vht_rates.rx_max_rate =
		__le16_to_cpu(vht_cap->vht_mcs.rx_highest);
	arg->peer_vht_rates.rx_mcs_set =
		__le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map);
	arg->peer_vht_rates.tx_max_rate =
		__le16_to_cpu(vht_cap->vht_mcs.tx_highest);
	arg->peer_vht_rates.tx_mcs_set = ath10k_peer_assoc_h_vht_limit(
		__le16_to_cpu(vht_cap->vht_mcs.tx_mcs_map), vht_mcs_mask);

	/* Configure bandwidth-NSS mapping to FW
	 * क्रम the chip's tx chains setting on 160Mhz bw
	 */
	अगर (arg->peer_phymode == MODE_11AC_VHT160 ||
	    arg->peer_phymode == MODE_11AC_VHT80_80) अणु
		u32 rx_nss;
		u32 max_rate;

		max_rate = arg->peer_vht_rates.rx_max_rate;
		rx_nss = get_160mhz_nss_from_maxrate(max_rate);

		अगर (rx_nss == 0)
			rx_nss = arg->peer_num_spatial_streams;
		अन्यथा
			rx_nss = min(arg->peer_num_spatial_streams, rx_nss);

		max_rate = hw->vht160_mcs_tx_highest;
		rx_nss = min(rx_nss, get_160mhz_nss_from_maxrate(max_rate));

		arg->peer_bw_rxnss_override =
			FIELD_PREP(WMI_PEER_NSS_MAP_ENABLE, 1) |
			FIELD_PREP(WMI_PEER_NSS_160MHZ_MASK, (rx_nss - 1));

		अगर (arg->peer_phymode == MODE_11AC_VHT80_80) अणु
			arg->peer_bw_rxnss_override |=
			FIELD_PREP(WMI_PEER_NSS_80_80MHZ_MASK, (rx_nss - 1));
		पूर्ण
	पूर्ण
	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac vht peer %pM max_mpdu %d flags 0x%x peer_rx_nss_override 0x%x\n",
		   sta->addr, arg->peer_max_mpdu,
		   arg->peer_flags, arg->peer_bw_rxnss_override);
पूर्ण

अटल व्योम ath10k_peer_assoc_h_qos(काष्ठा ath10k *ar,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta,
				    काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	चयन (arvअगर->vdev_type) अणु
	हाल WMI_VDEV_TYPE_AP:
		अगर (sta->wme)
			arg->peer_flags |= arvअगर->ar->wmi.peer_flags->qos;

		अगर (sta->wme && sta->uapsd_queues) अणु
			arg->peer_flags |= arvअगर->ar->wmi.peer_flags->apsd;
			arg->peer_rate_caps |= WMI_RC_UAPSD_FLAG;
		पूर्ण
		अवरोध;
	हाल WMI_VDEV_TYPE_STA:
		अगर (sta->wme)
			arg->peer_flags |= arvअगर->ar->wmi.peer_flags->qos;
		अवरोध;
	हाल WMI_VDEV_TYPE_IBSS:
		अगर (sta->wme)
			arg->peer_flags |= arvअगर->ar->wmi.peer_flags->qos;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac peer %pM qos %d\n",
		   sta->addr, !!(arg->peer_flags &
		   arvअगर->ar->wmi.peer_flags->qos));
पूर्ण

अटल bool ath10k_mac_sta_has_ofdm_only(काष्ठा ieee80211_sta *sta)
अणु
	वापस sta->supp_rates[NL80211_BAND_2GHZ] >>
	       ATH10K_MAC_FIRST_OFDM_RATE_IDX;
पूर्ण

अटल क्रमागत wmi_phy_mode ath10k_mac_get_phymode_vht(काष्ठा ath10k *ar,
						    काष्ठा ieee80211_sta *sta)
अणु
	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_160) अणु
		चयन (sta->vht_cap.cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) अणु
		हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ:
			वापस MODE_11AC_VHT160;
		हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ:
			वापस MODE_11AC_VHT80_80;
		शेष:
			/* not sure अगर this is a valid हाल? */
			वापस MODE_11AC_VHT160;
		पूर्ण
	पूर्ण

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_80)
		वापस MODE_11AC_VHT80;

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_40)
		वापस MODE_11AC_VHT40;

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_20)
		वापस MODE_11AC_VHT20;

	वापस MODE_UNKNOWN;
पूर्ण

अटल व्योम ath10k_peer_assoc_h_phymode(काष्ठा ath10k *ar,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_sta *sta,
					काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	स्थिर u8 *ht_mcs_mask;
	स्थिर u16 *vht_mcs_mask;
	क्रमागत wmi_phy_mode phymode = MODE_UNKNOWN;

	अगर (WARN_ON(ath10k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	band = def.chan->band;
	ht_mcs_mask = arvअगर->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvअगर->bitrate_mask.control[band].vht_mcs;

	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		अगर (sta->vht_cap.vht_supported &&
		    !ath10k_peer_assoc_h_vht_masked(vht_mcs_mask)) अणु
			अगर (sta->bandwidth == IEEE80211_STA_RX_BW_40)
				phymode = MODE_11AC_VHT40;
			अन्यथा
				phymode = MODE_11AC_VHT20;
		पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported &&
			   !ath10k_peer_assoc_h_ht_masked(ht_mcs_mask)) अणु
			अगर (sta->bandwidth == IEEE80211_STA_RX_BW_40)
				phymode = MODE_11NG_HT40;
			अन्यथा
				phymode = MODE_11NG_HT20;
		पूर्ण अन्यथा अगर (ath10k_mac_sta_has_ofdm_only(sta)) अणु
			phymode = MODE_11G;
		पूर्ण अन्यथा अणु
			phymode = MODE_11B;
		पूर्ण

		अवरोध;
	हाल NL80211_BAND_5GHZ:
		/*
		 * Check VHT first.
		 */
		अगर (sta->vht_cap.vht_supported &&
		    !ath10k_peer_assoc_h_vht_masked(vht_mcs_mask)) अणु
			phymode = ath10k_mac_get_phymode_vht(ar, sta);
		पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported &&
			   !ath10k_peer_assoc_h_ht_masked(ht_mcs_mask)) अणु
			अगर (sta->bandwidth >= IEEE80211_STA_RX_BW_40)
				phymode = MODE_11NA_HT40;
			अन्यथा
				phymode = MODE_11NA_HT20;
		पूर्ण अन्यथा अणु
			phymode = MODE_11A;
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac peer %pM phymode %s\n",
		   sta->addr, ath10k_wmi_phymode_str(phymode));

	arg->peer_phymode = phymode;
	WARN_ON(phymode == MODE_UNKNOWN);
पूर्ण

अटल पूर्णांक ath10k_peer_assoc_prepare(काष्ठा ath10k *ar,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta,
				     काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);

	स_रखो(arg, 0, माप(*arg));

	ath10k_peer_assoc_h_basic(ar, vअगर, sta, arg);
	ath10k_peer_assoc_h_crypto(ar, vअगर, sta, arg);
	ath10k_peer_assoc_h_rates(ar, vअगर, sta, arg);
	ath10k_peer_assoc_h_ht(ar, vअगर, sta, arg);
	ath10k_peer_assoc_h_phymode(ar, vअगर, sta, arg);
	ath10k_peer_assoc_h_vht(ar, vअगर, sta, arg);
	ath10k_peer_assoc_h_qos(ar, vअगर, sta, arg);

	वापस 0;
पूर्ण

अटल स्थिर u32 ath10k_smps_map[] = अणु
	[WLAN_HT_CAP_SM_PS_STATIC] = WMI_PEER_SMPS_STATIC,
	[WLAN_HT_CAP_SM_PS_DYNAMIC] = WMI_PEER_SMPS_DYNAMIC,
	[WLAN_HT_CAP_SM_PS_INVALID] = WMI_PEER_SMPS_PS_NONE,
	[WLAN_HT_CAP_SM_PS_DISABLED] = WMI_PEER_SMPS_PS_NONE,
पूर्ण;

अटल पूर्णांक ath10k_setup_peer_smps(काष्ठा ath10k *ar, काष्ठा ath10k_vअगर *arvअगर,
				  स्थिर u8 *addr,
				  स्थिर काष्ठा ieee80211_sta_ht_cap *ht_cap)
अणु
	पूर्णांक smps;

	अगर (!ht_cap->ht_supported)
		वापस 0;

	smps = ht_cap->cap & IEEE80211_HT_CAP_SM_PS;
	smps >>= IEEE80211_HT_CAP_SM_PS_SHIFT;

	अगर (smps >= ARRAY_SIZE(ath10k_smps_map))
		वापस -EINVAL;

	वापस ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, addr,
					 ar->wmi.peer_param->smps_state,
					 ath10k_smps_map[smps]);
पूर्ण

अटल पूर्णांक ath10k_mac_vअगर_recalc_txbf(काष्ठा ath10k *ar,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta_vht_cap vht_cap)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;
	u32 param;
	u32 value;

	अगर (ath10k_wmi_get_txbf_conf_scheme(ar) != WMI_TXBF_CONF_AFTER_ASSOC)
		वापस 0;

	अगर (!(ar->vht_cap_info &
	      (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
	       IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE |
	       IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
	       IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)))
		वापस 0;

	param = ar->wmi.vdev_param->txbf;
	value = 0;

	अगर (WARN_ON(param == WMI_VDEV_PARAM_UNSUPPORTED))
		वापस 0;

	/* The following logic is correct. If a remote STA advertises support
	 * क्रम being a beamक्रमmer then we should enable us being a beamक्रमmee.
	 */

	अगर (ar->vht_cap_info &
	    (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
	     IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE)) अणु
		अगर (vht_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE)
			value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFEE;

		अगर (vht_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)
			value |= WMI_VDEV_PARAM_TXBF_MU_TX_BFEE;
	पूर्ण

	अगर (ar->vht_cap_info &
	    (IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
	     IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)) अणु
		अगर (vht_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE)
			value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFER;

		अगर (vht_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE)
			value |= WMI_VDEV_PARAM_TXBF_MU_TX_BFER;
	पूर्ण

	अगर (value & WMI_VDEV_PARAM_TXBF_MU_TX_BFEE)
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFEE;

	अगर (value & WMI_VDEV_PARAM_TXBF_MU_TX_BFER)
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFER;

	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, param, value);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit vdev param txbf 0x%x: %d\n",
			    value, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ath10k_mac_is_connected(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		अगर (arvअगर->is_up && arvअगर->vdev_type == WMI_VDEV_TYPE_STA)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ath10k_mac_txघातer_setup(काष्ठा ath10k *ar, पूर्णांक txघातer)
अणु
	पूर्णांक ret;
	u32 param;
	पूर्णांक tx_घातer_2g, tx_घातer_5g;
	bool connected;

	lockdep_निश्चित_held(&ar->conf_mutex);

	/* ath10k पूर्णांकernally uses unit of 0.5 dBm so multiply by 2 */
	tx_घातer_2g = txघातer * 2;
	tx_घातer_5g = txघातer * 2;

	connected = ath10k_mac_is_connected(ar);

	अगर (connected && ar->tx_घातer_2g_limit)
		अगर (tx_घातer_2g > ar->tx_घातer_2g_limit)
			tx_घातer_2g = ar->tx_घातer_2g_limit;

	अगर (connected && ar->tx_घातer_5g_limit)
		अगर (tx_घातer_5g > ar->tx_घातer_5g_limit)
			tx_घातer_5g = ar->tx_घातer_5g_limit;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac txpower 2g: %d, 5g: %d\n",
		   tx_घातer_2g, tx_घातer_5g);

	param = ar->wmi.pdev_param->txघातer_limit2g;
	ret = ath10k_wmi_pdev_set_param(ar, param, tx_घातer_2g);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set 2g txpower %d: %d\n",
			    tx_घातer_2g, ret);
		वापस ret;
	पूर्ण

	param = ar->wmi.pdev_param->txघातer_limit5g;
	ret = ath10k_wmi_pdev_set_param(ar, param, tx_घातer_5g);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set 5g txpower %d: %d\n",
			    tx_घातer_5g, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_txघातer_recalc(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक ret, txघातer = -1;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		/* txघातer not initialized yet? */
		अगर (arvअगर->txघातer == पूर्णांक_न्यून)
			जारी;

		अगर (txघातer == -1)
			txघातer = arvअगर->txघातer;
		अन्यथा
			txघातer = min(txघातer, arvअगर->txघातer);
	पूर्ण

	अगर (txघातer == -1)
		वापस 0;

	ret = ath10k_mac_txघातer_setup(ar, txघातer);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to setup tx power %d: %d\n",
			    txघातer, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_set_sar_घातer(काष्ठा ath10k *ar)
अणु
	अगर (!ar->hw_params.dynamic_sar_support)
		वापस -EOPNOTSUPP;

	अगर (!ath10k_mac_is_connected(ar))
		वापस 0;

	/* अगर connected, then arvअगर->txघातer must be valid */
	वापस ath10k_mac_txघातer_recalc(ar);
पूर्ण

अटल पूर्णांक ath10k_mac_set_sar_specs(काष्ठा ieee80211_hw *hw,
				    स्थिर काष्ठा cfg80211_sar_specs *sar)
अणु
	स्थिर काष्ठा cfg80211_sar_sub_specs *sub_specs;
	काष्ठा ath10k *ar = hw->priv;
	u32 i;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	अगर (!ar->hw_params.dynamic_sar_support) अणु
		ret = -EOPNOTSUPP;
		जाओ err;
	पूर्ण

	अगर (!sar || sar->type != NL80211_SAR_TYPE_POWER ||
	    sar->num_sub_specs == 0) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	sub_specs = sar->sub_specs;

	/* 0dbm is not a practical value क्रम ath10k, so use 0
	 * as no SAR limitation on it.
	 */
	ar->tx_घातer_2g_limit = 0;
	ar->tx_घातer_5g_limit = 0;

	/* note the घातer is in 0.25dbm unit, जबतक ath10k uses
	 * 0.5dbm unit.
	 */
	क्रम (i = 0; i < sar->num_sub_specs; i++) अणु
		अगर (sub_specs->freq_range_index == 0)
			ar->tx_घातer_2g_limit = sub_specs->घातer / 2;
		अन्यथा अगर (sub_specs->freq_range_index == 1)
			ar->tx_घातer_5g_limit = sub_specs->घातer / 2;

		sub_specs++;
	पूर्ण

	ret = ath10k_mac_set_sar_घातer(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set sar power: %d", ret);
		जाओ err;
	पूर्ण

err:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

/* can be called only in mac80211 callbacks due to `key_count` usage */
अटल व्योम ath10k_bss_assoc(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_bss_conf *bss_conf)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ieee80211_sta_ht_cap ht_cap;
	काष्ठा ieee80211_sta_vht_cap vht_cap;
	काष्ठा wmi_peer_assoc_complete_arg peer_arg;
	काष्ठा ieee80211_sta *ap_sta;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %i assoc bssid %pM aid %d\n",
		   arvअगर->vdev_id, arvअगर->bssid, arvअगर->aid);

	rcu_पढ़ो_lock();

	ap_sta = ieee80211_find_sta(vअगर, bss_conf->bssid);
	अगर (!ap_sta) अणु
		ath10k_warn(ar, "failed to find station entry for bss %pM vdev %i\n",
			    bss_conf->bssid, arvअगर->vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	/* ap_sta must be accessed only within rcu section which must be left
	 * beक्रमe calling ath10k_setup_peer_smps() which might sleep.
	 */
	ht_cap = ap_sta->ht_cap;
	vht_cap = ap_sta->vht_cap;

	ret = ath10k_peer_assoc_prepare(ar, vअगर, ap_sta, &peer_arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to prepare peer assoc for %pM vdev %i: %d\n",
			    bss_conf->bssid, arvअगर->vdev_id, ret);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	rcu_पढ़ो_unlock();

	ret = ath10k_wmi_peer_assoc(ar, &peer_arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to run peer assoc for %pM vdev %i: %d\n",
			    bss_conf->bssid, arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	ret = ath10k_setup_peer_smps(ar, arvअगर, bss_conf->bssid, &ht_cap);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to setup peer SMPS for vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	ret = ath10k_mac_vअगर_recalc_txbf(ar, vअगर, vht_cap);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to recalc txbf for vdev %i on bss %pM: %d\n",
			    arvअगर->vdev_id, bss_conf->bssid, ret);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac vdev %d up (associated) bssid %pM aid %d\n",
		   arvअगर->vdev_id, bss_conf->bssid, bss_conf->aid);

	WARN_ON(arvअगर->is_up);

	arvअगर->aid = bss_conf->aid;
	ether_addr_copy(arvअगर->bssid, bss_conf->bssid);

	ret = ath10k_wmi_pdev_set_param(ar,
					ar->wmi.pdev_param->peer_stats_info_enable, 1);
	अगर (ret)
		ath10k_warn(ar, "failed to enable peer stats info: %d\n", ret);

	ret = ath10k_wmi_vdev_up(ar, arvअगर->vdev_id, arvअगर->aid, arvअगर->bssid);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set vdev %d up: %d\n",
			    arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	arvअगर->is_up = true;

	ath10k_mac_set_sar_घातer(ar);

	/* Workaround: Some firmware revisions (tested with qca6174
	 * WLAN.RM.2.0-00073) have buggy घातersave state machine and must be
	 * poked with peer param command.
	 */
	ret = ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, arvअगर->bssid,
					ar->wmi.peer_param->dummy_var, 1);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to poke peer %pM param for ps workaround on vdev %i: %d\n",
			    arvअगर->bssid, arvअगर->vdev_id, ret);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम ath10k_bss_disassoc(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ieee80211_sta_vht_cap vht_cap = अणुपूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %i disassoc bssid %pM\n",
		   arvअगर->vdev_id, arvअगर->bssid);

	ret = ath10k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);
	अगर (ret)
		ath10k_warn(ar, "failed to down vdev %i: %d\n",
			    arvअगर->vdev_id, ret);

	arvअगर->def_wep_key_idx = -1;

	ret = ath10k_mac_vअगर_recalc_txbf(ar, vअगर, vht_cap);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to recalc txbf for vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	arvअगर->is_up = false;

	ath10k_mac_txघातer_recalc(ar);

	cancel_delayed_work_sync(&arvअगर->connection_loss_work);
पूर्ण

अटल पूर्णांक ath10k_new_peer_tid_config(काष्ठा ath10k *ar,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा ath10k_vअगर *arvअगर)
अणु
	काष्ठा wmi_per_peer_per_tid_cfg_arg arg = अणुपूर्ण;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	bool config_apply;
	पूर्णांक ret, i;

	क्रम (i = 0; i < ATH10K_TID_MAX; i++) अणु
		config_apply = false;
		अगर (arvअगर->retry_दीर्घ[i] || arvअगर->ampdu[i] ||
		    arvअगर->rate_ctrl[i] || arvअगर->rtscts[i]) अणु
			config_apply = true;
			arg.tid = i;
			arg.vdev_id = arvअगर->vdev_id;
			arg.retry_count = arvअगर->retry_दीर्घ[i];
			arg.aggr_control = arvअगर->ampdu[i];
			arg.rate_ctrl = arvअगर->rate_ctrl[i];
			arg.rcode_flags = arvअगर->rate_code[i];

			अगर (arvअगर->rtscts[i])
				arg.ext_tid_cfg_biपंचांगap =
					WMI_EXT_TID_RTS_CTS_CONFIG;
			अन्यथा
				arg.ext_tid_cfg_biपंचांगap = 0;

			arg.rtscts_ctrl = arvअगर->rtscts[i];
		पूर्ण

		अगर (arvअगर->noack[i]) अणु
			arg.ack_policy = arvअगर->noack[i];
			arg.rate_ctrl = WMI_TID_CONFIG_RATE_CONTROL_DEFAULT_LOWEST_RATE;
			arg.aggr_control = WMI_TID_CONFIG_AGGR_CONTROL_DISABLE;
			config_apply = true;
		पूर्ण

		/* Assign शेष value(-1) to newly connected station.
		 * This is to identअगरy station specअगरic tid configuration not
		 * configured क्रम the station.
		 */
		arsta->retry_दीर्घ[i] = -1;
		arsta->noack[i] = -1;
		arsta->ampdu[i] = -1;

		अगर (!config_apply)
			जारी;

		ether_addr_copy(arg.peer_macaddr.addr, sta->addr);

		ret = ath10k_wmi_set_per_peer_per_tid_cfg(ar, &arg);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set per tid retry/aggr config for sta %pM: %d\n",
				    sta->addr, ret);
			वापस ret;
		पूर्ण

		स_रखो(&arg, 0, माप(arg));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_station_assoc(काष्ठा ath10k *ar,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta,
				bool reassoc)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा wmi_peer_assoc_complete_arg peer_arg;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_peer_assoc_prepare(ar, vअगर, sta, &peer_arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to prepare WMI peer assoc for %pM vdev %i: %i\n",
			    sta->addr, arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_wmi_peer_assoc(ar, &peer_arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to run peer assoc for STA %pM vdev %i: %d\n",
			    sta->addr, arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	/* Re-assoc is run only to update supported rates क्रम given station. It
	 * करोesn't make much sense to reconfigure the peer completely.
	 */
	अगर (!reassoc) अणु
		ret = ath10k_setup_peer_smps(ar, arvअगर, sta->addr,
					     &sta->ht_cap);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to setup peer SMPS for vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण

		ret = ath10k_peer_assoc_qos_ap(ar, arvअगर, sta);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set qos params for STA %pM for vdev %i: %d\n",
				    sta->addr, arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण

		अगर (!sta->wme) अणु
			arvअगर->num_legacy_stations++;
			ret  = ath10k_recalc_rtscts_prot(arvअगर);
			अगर (ret) अणु
				ath10k_warn(ar, "failed to recalculate rts/cts prot for vdev %d: %d\n",
					    arvअगर->vdev_id, ret);
				वापस ret;
			पूर्ण
		पूर्ण

		/* Plumb cached keys only क्रम अटल WEP */
		अगर ((arvअगर->def_wep_key_idx != -1) && (!sta->tdls)) अणु
			ret = ath10k_install_peer_wep_keys(arvअगर, sta->addr);
			अगर (ret) अणु
				ath10k_warn(ar, "failed to install peer wep keys for vdev %i: %d\n",
					    arvअगर->vdev_id, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!test_bit(WMI_SERVICE_PEER_TID_CONFIGS_SUPPORT, ar->wmi.svc_map))
		वापस ret;

	वापस ath10k_new_peer_tid_config(ar, sta, arvअगर);
पूर्ण

अटल पूर्णांक ath10k_station_disassoc(काष्ठा ath10k *ar,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (!sta->wme) अणु
		arvअगर->num_legacy_stations--;
		ret = ath10k_recalc_rtscts_prot(arvअगर);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to recalculate rts/cts prot for vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = ath10k_clear_peer_keys(arvअगर, sta->addr);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to clear all peer wep keys for vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/**************/
/* Regulatory */
/**************/

अटल पूर्णांक ath10k_update_channel_list(काष्ठा ath10k *ar)
अणु
	काष्ठा ieee80211_hw *hw = ar->hw;
	काष्ठा ieee80211_supported_band **bands;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_channel *channel;
	काष्ठा wmi_scan_chan_list_arg arg = अणु0पूर्ण;
	काष्ठा wmi_channel_arg *ch;
	bool passive;
	पूर्णांक len;
	पूर्णांक ret;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->conf_mutex);

	bands = hw->wiphy->bands;
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!bands[band])
			जारी;

		क्रम (i = 0; i < bands[band]->n_channels; i++) अणु
			अगर (bands[band]->channels[i].flags &
			    IEEE80211_CHAN_DISABLED)
				जारी;

			arg.n_channels++;
		पूर्ण
	पूर्ण

	len = माप(काष्ठा wmi_channel_arg) * arg.n_channels;
	arg.channels = kzalloc(len, GFP_KERNEL);
	अगर (!arg.channels)
		वापस -ENOMEM;

	ch = arg.channels;
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!bands[band])
			जारी;

		क्रम (i = 0; i < bands[band]->n_channels; i++) अणु
			channel = &bands[band]->channels[i];

			अगर (channel->flags & IEEE80211_CHAN_DISABLED)
				जारी;

			ch->allow_ht = true;

			/* FIXME: when should we really allow VHT? */
			ch->allow_vht = true;

			ch->allow_ibss =
				!(channel->flags & IEEE80211_CHAN_NO_IR);

			ch->ht40plus =
				!(channel->flags & IEEE80211_CHAN_NO_HT40PLUS);

			ch->chan_radar =
				!!(channel->flags & IEEE80211_CHAN_RADAR);

			passive = channel->flags & IEEE80211_CHAN_NO_IR;
			ch->passive = passive;

			/* the firmware is ignoring the "radar" flag of the
			 * channel and is scanning actively using Probe Requests
			 * on "Radar detection"/DFS channels which are not
			 * marked as "available"
			 */
			ch->passive |= ch->chan_radar;

			ch->freq = channel->center_freq;
			ch->band_center_freq1 = channel->center_freq;
			ch->min_घातer = 0;
			ch->max_घातer = channel->max_घातer * 2;
			ch->max_reg_घातer = channel->max_reg_घातer * 2;
			ch->max_antenna_gain = channel->max_antenna_gain * 2;
			ch->reg_class_id = 0; /* FIXME */

			/* FIXME: why use only legacy modes, why not any
			 * HT/VHT modes? Would that even make any
			 * dअगरference?
			 */
			अगर (channel->band == NL80211_BAND_2GHZ)
				ch->mode = MODE_11G;
			अन्यथा
				ch->mode = MODE_11A;

			अगर (WARN_ON_ONCE(ch->mode == MODE_UNKNOWN))
				जारी;

			ath10k_dbg(ar, ATH10K_DBG_WMI,
				   "mac channel [%zd/%d] freq %d maxpower %d regpower %d antenna %d mode %d\n",
				    ch - arg.channels, arg.n_channels,
				   ch->freq, ch->max_घातer, ch->max_reg_घातer,
				   ch->max_antenna_gain, ch->mode);

			ch++;
		पूर्ण
	पूर्ण

	ret = ath10k_wmi_scan_chan_list(ar, &arg);
	kमुक्त(arg.channels);

	वापस ret;
पूर्ण

अटल क्रमागत wmi_dfs_region
ath10k_mac_get_dfs_region(क्रमागत nl80211_dfs_regions dfs_region)
अणु
	चयन (dfs_region) अणु
	हाल NL80211_DFS_UNSET:
		वापस WMI_UNINIT_DFS_DOMAIN;
	हाल NL80211_DFS_FCC:
		वापस WMI_FCC_DFS_DOMAIN;
	हाल NL80211_DFS_ETSI:
		वापस WMI_ETSI_DFS_DOMAIN;
	हाल NL80211_DFS_JP:
		वापस WMI_MKK4_DFS_DOMAIN;
	पूर्ण
	वापस WMI_UNINIT_DFS_DOMAIN;
पूर्ण

अटल व्योम ath10k_regd_update(काष्ठा ath10k *ar)
अणु
	काष्ठा reg_dmn_pair_mapping *regpair;
	पूर्णांक ret;
	क्रमागत wmi_dfs_region wmi_dfs_reg;
	क्रमागत nl80211_dfs_regions nl_dfs_reg;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_update_channel_list(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to update channel list: %d\n", ret);

	regpair = ar->ath_common.regulatory.regpair;

	अगर (IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED) && ar->dfs_detector) अणु
		nl_dfs_reg = ar->dfs_detector->region;
		wmi_dfs_reg = ath10k_mac_get_dfs_region(nl_dfs_reg);
	पूर्ण अन्यथा अणु
		wmi_dfs_reg = WMI_UNINIT_DFS_DOMAIN;
	पूर्ण

	/* Target allows setting up per-band regकरोमुख्य but ath_common provides
	 * a combined one only
	 */
	ret = ath10k_wmi_pdev_set_regकरोमुख्य(ar,
					    regpair->reg_करोमुख्य,
					    regpair->reg_करोमुख्य, /* 2ghz */
					    regpair->reg_करोमुख्य, /* 5ghz */
					    regpair->reg_2ghz_ctl,
					    regpair->reg_5ghz_ctl,
					    wmi_dfs_reg);
	अगर (ret)
		ath10k_warn(ar, "failed to set pdev regdomain: %d\n", ret);
पूर्ण

अटल व्योम ath10k_mac_update_channel_list(काष्ठा ath10k *ar,
					   काष्ठा ieee80211_supported_band *band)
अणु
	पूर्णांक i;

	अगर (ar->low_5ghz_chan && ar->high_5ghz_chan) अणु
		क्रम (i = 0; i < band->n_channels; i++) अणु
			अगर (band->channels[i].center_freq < ar->low_5ghz_chan ||
			    band->channels[i].center_freq > ar->high_5ghz_chan)
				band->channels[i].flags |=
					IEEE80211_CHAN_DISABLED;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath10k_reg_notअगरier(काष्ठा wiphy *wiphy,
				काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा ath10k *ar = hw->priv;
	bool result;

	ath_reg_notअगरier_apply(wiphy, request, &ar->ath_common.regulatory);

	अगर (IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED) && ar->dfs_detector) अणु
		ath10k_dbg(ar, ATH10K_DBG_REGULATORY, "dfs region 0x%x\n",
			   request->dfs_region);
		result = ar->dfs_detector->set_dfs_करोमुख्य(ar->dfs_detector,
							  request->dfs_region);
		अगर (!result)
			ath10k_warn(ar, "DFS region 0x%X not supported, will trigger radar for every pulse\n",
				    request->dfs_region);
	पूर्ण

	mutex_lock(&ar->conf_mutex);
	अगर (ar->state == ATH10K_STATE_ON)
		ath10k_regd_update(ar);
	mutex_unlock(&ar->conf_mutex);

	अगर (ar->phy_capability & WHAL_WLAN_11A_CAPABILITY)
		ath10k_mac_update_channel_list(ar,
					       ar->hw->wiphy->bands[NL80211_BAND_5GHZ]);
पूर्ण

अटल व्योम ath10k_stop_radar_confirmation(काष्ठा ath10k *ar)
अणु
	spin_lock_bh(&ar->data_lock);
	ar->radar_conf_state = ATH10K_RADAR_CONFIRMATION_STOPPED;
	spin_unlock_bh(&ar->data_lock);

	cancel_work_sync(&ar->radar_confirmation_work);
पूर्ण

/***************/
/* TX handlers */
/***************/

क्रमागत ath10k_mac_tx_path अणु
	ATH10K_MAC_TX_HTT,
	ATH10K_MAC_TX_HTT_MGMT,
	ATH10K_MAC_TX_WMI_MGMT,
	ATH10K_MAC_TX_UNKNOWN,
पूर्ण;

व्योम ath10k_mac_tx_lock(काष्ठा ath10k *ar, पूर्णांक reason)
अणु
	lockdep_निश्चित_held(&ar->htt.tx_lock);

	WARN_ON(reason >= ATH10K_TX_PAUSE_MAX);
	ar->tx_छोड़ोd |= BIT(reason);
	ieee80211_stop_queues(ar->hw);
पूर्ण

अटल व्योम ath10k_mac_tx_unlock_iter(व्योम *data, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k *ar = data;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	अगर (arvअगर->tx_छोड़ोd)
		वापस;

	ieee80211_wake_queue(ar->hw, arvअगर->vdev_id);
पूर्ण

व्योम ath10k_mac_tx_unlock(काष्ठा ath10k *ar, पूर्णांक reason)
अणु
	lockdep_निश्चित_held(&ar->htt.tx_lock);

	WARN_ON(reason >= ATH10K_TX_PAUSE_MAX);
	ar->tx_छोड़ोd &= ~BIT(reason);

	अगर (ar->tx_छोड़ोd)
		वापस;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   ATH10K_ITER_RESUME_FLAGS,
						   ath10k_mac_tx_unlock_iter,
						   ar);

	ieee80211_wake_queue(ar->hw, ar->hw->offchannel_tx_hw_queue);
पूर्ण

व्योम ath10k_mac_vअगर_tx_lock(काष्ठा ath10k_vअगर *arvअगर, पूर्णांक reason)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->htt.tx_lock);

	WARN_ON(reason >= BITS_PER_LONG);
	arvअगर->tx_छोड़ोd |= BIT(reason);
	ieee80211_stop_queue(ar->hw, arvअगर->vdev_id);
पूर्ण

व्योम ath10k_mac_vअगर_tx_unlock(काष्ठा ath10k_vअगर *arvअगर, पूर्णांक reason)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->htt.tx_lock);

	WARN_ON(reason >= BITS_PER_LONG);
	arvअगर->tx_छोड़ोd &= ~BIT(reason);

	अगर (ar->tx_छोड़ोd)
		वापस;

	अगर (arvअगर->tx_छोड़ोd)
		वापस;

	ieee80211_wake_queue(ar->hw, arvअगर->vdev_id);
पूर्ण

अटल व्योम ath10k_mac_vअगर_handle_tx_छोड़ो(काष्ठा ath10k_vअगर *arvअगर,
					   क्रमागत wmi_tlv_tx_छोड़ो_id छोड़ो_id,
					   क्रमागत wmi_tlv_tx_छोड़ो_action action)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->htt.tx_lock);

	चयन (action) अणु
	हाल WMI_TLV_TX_PAUSE_ACTION_STOP:
		ath10k_mac_vअगर_tx_lock(arvअगर, छोड़ो_id);
		अवरोध;
	हाल WMI_TLV_TX_PAUSE_ACTION_WAKE:
		ath10k_mac_vअगर_tx_unlock(arvअगर, छोड़ो_id);
		अवरोध;
	शेष:
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "received unknown tx pause action %d on vdev %i, ignoring\n",
			    action, arvअगर->vdev_id);
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा ath10k_mac_tx_छोड़ो अणु
	u32 vdev_id;
	क्रमागत wmi_tlv_tx_छोड़ो_id छोड़ो_id;
	क्रमागत wmi_tlv_tx_छोड़ो_action action;
पूर्ण;

अटल व्योम ath10k_mac_handle_tx_छोड़ो_iter(व्योम *data, u8 *mac,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_mac_tx_छोड़ो *arg = data;

	अगर (arvअगर->vdev_id != arg->vdev_id)
		वापस;

	ath10k_mac_vअगर_handle_tx_छोड़ो(arvअगर, arg->छोड़ो_id, arg->action);
पूर्ण

व्योम ath10k_mac_handle_tx_छोड़ो_vdev(काष्ठा ath10k *ar, u32 vdev_id,
				     क्रमागत wmi_tlv_tx_छोड़ो_id छोड़ो_id,
				     क्रमागत wmi_tlv_tx_छोड़ो_action action)
अणु
	काष्ठा ath10k_mac_tx_छोड़ो arg = अणु
		.vdev_id = vdev_id,
		.छोड़ो_id = छोड़ो_id,
		.action = action,
	पूर्ण;

	spin_lock_bh(&ar->htt.tx_lock);
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   ATH10K_ITER_RESUME_FLAGS,
						   ath10k_mac_handle_tx_छोड़ो_iter,
						   &arg);
	spin_unlock_bh(&ar->htt.tx_lock);
पूर्ण

अटल क्रमागत ath10k_hw_txrx_mode
ath10k_mac_tx_h_get_txmode(काष्ठा ath10k *ar,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	स्थिर काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);
	__le16 fc = hdr->frame_control;

	अगर (!vअगर || vअगर->type == NL80211_IFTYPE_MONITOR)
		वापस ATH10K_HW_TXRX_RAW;

	अगर (ieee80211_is_mgmt(fc))
		वापस ATH10K_HW_TXRX_MGMT;

	/* Workaround:
	 *
	 * NullFunc frames are mostly used to ping अगर a client or AP are still
	 * reachable and responsive. This implies tx status reports must be
	 * accurate - otherwise either mac80211 or userspace (e.g. hostapd) can
	 * come to a conclusion that the other end disappeared and tear करोwn
	 * BSS connection or it can never disconnect from BSS/client (which is
	 * the हाल).
	 *
	 * Firmware with HTT older than 3.0 delivers incorrect tx status क्रम
	 * NullFunc frames to driver. However there's a HTT Mgmt Tx command
	 * which seems to deliver correct tx reports क्रम NullFunc frames. The
	 * करोwnside of using it is it ignores client घातersave state so it can
	 * end up disconnecting sleeping clients in AP mode. It should fix STA
	 * mode though because AP करोn't sleep.
	 */
	अगर (ar->htt.target_version_major < 3 &&
	    (ieee80211_is_nullfunc(fc) || ieee80211_is_qos_nullfunc(fc)) &&
	    !test_bit(ATH10K_FW_FEATURE_HAS_WMI_MGMT_TX,
		      ar->running_fw->fw_file.fw_features))
		वापस ATH10K_HW_TXRX_MGMT;

	/* Workaround:
	 *
	 * Some wmi-tlv firmwares क्रम qca6174 have broken Tx key selection क्रम
	 * NativeWअगरi txmode - it selects AP key instead of peer key. It seems
	 * to work with Ethernet txmode so use it.
	 *
	 * FIXME: Check अगर raw mode works with TDLS.
	 */
	अगर (ieee80211_is_data_present(fc) && sta && sta->tdls)
		वापस ATH10K_HW_TXRX_ETHERNET;

	अगर (test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags) ||
	    skb_cb->flags & ATH10K_SKB_F_RAW_TX)
		वापस ATH10K_HW_TXRX_RAW;

	वापस ATH10K_HW_TXRX_NATIVE_WIFI;
पूर्ण

अटल bool ath10k_tx_h_use_hwcrypto(काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	स्थिर काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	स्थिर u32 mask = IEEE80211_TX_INTFL_DONT_ENCRYPT |
			 IEEE80211_TX_CTL_INJECTED;

	अगर (!ieee80211_has_रक्षित(hdr->frame_control))
		वापस false;

	अगर ((info->flags & mask) == mask)
		वापस false;

	अगर (vअगर)
		वापस !((काष्ठा ath10k_vअगर *)vअगर->drv_priv)->nohwcrypt;

	वापस true;
पूर्ण

/* HTT Tx uses Native Wअगरi tx mode which expects 802.11 frames without QoS
 * Control in the header.
 */
अटल व्योम ath10k_tx_h_nwअगरi(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);
	u8 *qos_ctl;

	अगर (!ieee80211_is_data_qos(hdr->frame_control))
		वापस;

	qos_ctl = ieee80211_get_qos_ctl(hdr);
	स_हटाओ(skb->data + IEEE80211_QOS_CTL_LEN,
		skb->data, (व्योम *)qos_ctl - (व्योम *)skb->data);
	skb_pull(skb, IEEE80211_QOS_CTL_LEN);

	/* Some firmware revisions करोn't handle sending QoS NullFunc well.
	 * These frames are मुख्यly used क्रम CQM purposes so it करोesn't really
	 * matter whether QoS NullFunc or NullFunc are sent.
	 */
	hdr = (व्योम *)skb->data;
	अगर (ieee80211_is_qos_nullfunc(hdr->frame_control))
		cb->flags &= ~ATH10K_SKB_F_QOS;

	hdr->frame_control &= ~__cpu_to_le16(IEEE80211_STYPE_QOS_DATA);
पूर्ण

अटल व्योम ath10k_tx_h_8023(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा rfc1042_hdr *rfc1042;
	काष्ठा ethhdr *eth;
	माप_प्रकार hdrlen;
	u8 da[ETH_ALEN];
	u8 sa[ETH_ALEN];
	__be16 type;

	hdr = (व्योम *)skb->data;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	rfc1042 = (व्योम *)skb->data + hdrlen;

	ether_addr_copy(da, ieee80211_get_DA(hdr));
	ether_addr_copy(sa, ieee80211_get_SA(hdr));
	type = rfc1042->snap_type;

	skb_pull(skb, hdrlen + माप(*rfc1042));
	skb_push(skb, माप(*eth));

	eth = (व्योम *)skb->data;
	ether_addr_copy(eth->h_dest, da);
	ether_addr_copy(eth->h_source, sa);
	eth->h_proto = type;
पूर्ण

अटल व्योम ath10k_tx_h_add_p2p_noa_ie(काष्ठा ath10k *ar,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	/* This is हाल only क्रम P2P_GO */
	अगर (vअगर->type != NL80211_IFTYPE_AP || !vअगर->p2p)
		वापस;

	अगर (unlikely(ieee80211_is_probe_resp(hdr->frame_control))) अणु
		spin_lock_bh(&ar->data_lock);
		अगर (arvअगर->u.ap.noa_data)
			अगर (!pskb_expand_head(skb, 0, arvअगर->u.ap.noa_len,
					      GFP_ATOMIC))
				skb_put_data(skb, arvअगर->u.ap.noa_data,
					     arvअगर->u.ap.noa_len);
		spin_unlock_bh(&ar->data_lock);
	पूर्ण
पूर्ण

अटल व्योम ath10k_mac_tx_h_fill_cb(काष्ठा ath10k *ar,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_txq *txq,
				    काष्ठा ieee80211_sta *sta,
				    काष्ठा sk_buff *skb, u16 airसमय)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	काष्ठा ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);
	स्थिर काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	bool is_data = ieee80211_is_data(hdr->frame_control) ||
			ieee80211_is_data_qos(hdr->frame_control);
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_sta *arsta;
	u8 tid, *qos_ctl;
	bool noack = false;

	cb->flags = 0;
	अगर (!ath10k_tx_h_use_hwcrypto(vअगर, skb))
		cb->flags |= ATH10K_SKB_F_NO_HWCRYPT;

	अगर (ieee80211_is_mgmt(hdr->frame_control))
		cb->flags |= ATH10K_SKB_F_MGMT;

	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		cb->flags |= ATH10K_SKB_F_QOS;
		qos_ctl = ieee80211_get_qos_ctl(hdr);
		tid = (*qos_ctl) & IEEE80211_QOS_CTL_TID_MASK;

		अगर (arvअगर->noack[tid] == WMI_PEER_TID_CONFIG_NOACK)
			noack = true;

		अगर (sta) अणु
			arsta = (काष्ठा ath10k_sta *)sta->drv_priv;

			अगर (arsta->noack[tid] == WMI_PEER_TID_CONFIG_NOACK)
				noack = true;

			अगर (arsta->noack[tid] == WMI_PEER_TID_CONFIG_ACK)
				noack = false;
		पूर्ण

		अगर (noack)
			cb->flags |= ATH10K_SKB_F_NOACK_TID;
	पूर्ण

	/* Data frames encrypted in software will be posted to firmware
	 * with tx encap mode set to RAW. Ex: Multicast traffic generated
	 * क्रम a specअगरic VLAN group will always be encrypted in software.
	 */
	अगर (is_data && ieee80211_has_रक्षित(hdr->frame_control) &&
	    !info->control.hw_key) अणु
		cb->flags |= ATH10K_SKB_F_NO_HWCRYPT;
		cb->flags |= ATH10K_SKB_F_RAW_TX;
	पूर्ण

	cb->vअगर = vअगर;
	cb->txq = txq;
	cb->airसमय_est = airसमय;
	अगर (sta) अणु
		arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
		spin_lock_bh(&ar->data_lock);
		cb->ucast_cipher = arsta->ucast_cipher;
		spin_unlock_bh(&ar->data_lock);
	पूर्ण
पूर्ण

bool ath10k_mac_tx_frm_has_freq(काष्ठा ath10k *ar)
अणु
	/* FIXME: Not really sure since when the behaviour changed. At some
	 * poपूर्णांक new firmware stopped requiring creation of peer entries क्रम
	 * offchannel tx (and actually creating them causes issues with wmi-htc
	 * tx credit replenishment and reliability). Assuming it's at least 3.4
	 * because that's when the `freq` was पूर्णांकroduced to TX_FRM HTT command.
	 */
	वापस (ar->htt.target_version_major >= 3 &&
		ar->htt.target_version_minor >= 4 &&
		ar->running_fw->fw_file.htt_op_version == ATH10K_FW_HTT_OP_VERSION_TLV);
पूर्ण

अटल पूर्णांक ath10k_mac_tx_wmi_mgmt(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff_head *q = &ar->wmi_mgmt_tx_queue;

	अगर (skb_queue_len_lockless(q) >= ATH10K_MAX_NUM_MGMT_PENDING) अणु
		ath10k_warn(ar, "wmi mgmt tx queue is full\n");
		वापस -ENOSPC;
	पूर्ण

	skb_queue_tail(q, skb);
	ieee80211_queue_work(ar->hw, &ar->wmi_mgmt_tx_work);

	वापस 0;
पूर्ण

अटल क्रमागत ath10k_mac_tx_path
ath10k_mac_tx_h_get_txpath(काष्ठा ath10k *ar,
			   काष्ठा sk_buff *skb,
			   क्रमागत ath10k_hw_txrx_mode txmode)
अणु
	चयन (txmode) अणु
	हाल ATH10K_HW_TXRX_RAW:
	हाल ATH10K_HW_TXRX_NATIVE_WIFI:
	हाल ATH10K_HW_TXRX_ETHERNET:
		वापस ATH10K_MAC_TX_HTT;
	हाल ATH10K_HW_TXRX_MGMT:
		अगर (test_bit(ATH10K_FW_FEATURE_HAS_WMI_MGMT_TX,
			     ar->running_fw->fw_file.fw_features) ||
			     test_bit(WMI_SERVICE_MGMT_TX_WMI,
				      ar->wmi.svc_map))
			वापस ATH10K_MAC_TX_WMI_MGMT;
		अन्यथा अगर (ar->htt.target_version_major >= 3)
			वापस ATH10K_MAC_TX_HTT;
		अन्यथा
			वापस ATH10K_MAC_TX_HTT_MGMT;
	पूर्ण

	वापस ATH10K_MAC_TX_UNKNOWN;
पूर्ण

अटल पूर्णांक ath10k_mac_tx_submit(काष्ठा ath10k *ar,
				क्रमागत ath10k_hw_txrx_mode txmode,
				क्रमागत ath10k_mac_tx_path txpath,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_htt *htt = &ar->htt;
	पूर्णांक ret = -EINVAL;

	चयन (txpath) अणु
	हाल ATH10K_MAC_TX_HTT:
		ret = ath10k_htt_tx(htt, txmode, skb);
		अवरोध;
	हाल ATH10K_MAC_TX_HTT_MGMT:
		ret = ath10k_htt_mgmt_tx(htt, skb);
		अवरोध;
	हाल ATH10K_MAC_TX_WMI_MGMT:
		ret = ath10k_mac_tx_wmi_mgmt(ar, skb);
		अवरोध;
	हाल ATH10K_MAC_TX_UNKNOWN:
		WARN_ON_ONCE(1);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret) अणु
		ath10k_warn(ar, "failed to transmit packet, dropping: %d\n",
			    ret);
		ieee80211_मुक्त_txskb(ar->hw, skb);
	पूर्ण

	वापस ret;
पूर्ण

/* This function consumes the sk_buff regardless of वापस value as far as
 * caller is concerned so no मुक्तing is necessary afterwards.
 */
अटल पूर्णांक ath10k_mac_tx(काष्ठा ath10k *ar,
			 काष्ठा ieee80211_vअगर *vअगर,
			 क्रमागत ath10k_hw_txrx_mode txmode,
			 क्रमागत ath10k_mac_tx_path txpath,
			 काष्ठा sk_buff *skb, bool noque_offchan)
अणु
	काष्ठा ieee80211_hw *hw = ar->hw;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	स्थिर काष्ठा ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);
	पूर्णांक ret;

	/* We should disable CCK RATE due to P2P */
	अगर (info->flags & IEEE80211_TX_CTL_NO_CCK_RATE)
		ath10k_dbg(ar, ATH10K_DBG_MAC, "IEEE80211_TX_CTL_NO_CCK_RATE\n");

	चयन (txmode) अणु
	हाल ATH10K_HW_TXRX_MGMT:
	हाल ATH10K_HW_TXRX_NATIVE_WIFI:
		ath10k_tx_h_nwअगरi(hw, skb);
		ath10k_tx_h_add_p2p_noa_ie(ar, vअगर, skb);
		ath10k_tx_h_seq_no(vअगर, skb);
		अवरोध;
	हाल ATH10K_HW_TXRX_ETHERNET:
		ath10k_tx_h_8023(skb);
		अवरोध;
	हाल ATH10K_HW_TXRX_RAW:
		अगर (!test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags) &&
		    !(skb_cb->flags & ATH10K_SKB_F_RAW_TX)) अणु
			WARN_ON_ONCE(1);
			ieee80211_मुक्त_txskb(hw, skb);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	अगर (!noque_offchan && info->flags & IEEE80211_TX_CTL_TX_OFFCHAN) अणु
		अगर (!ath10k_mac_tx_frm_has_freq(ar)) अणु
			ath10k_dbg(ar, ATH10K_DBG_MAC, "mac queued offchannel skb %pK len %d\n",
				   skb, skb->len);

			skb_queue_tail(&ar->offchan_tx_queue, skb);
			ieee80211_queue_work(hw, &ar->offchan_tx_work);
			वापस 0;
		पूर्ण
	पूर्ण

	ret = ath10k_mac_tx_submit(ar, txmode, txpath, skb);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to submit frame: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath10k_offchan_tx_purge(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	क्रम (;;) अणु
		skb = skb_dequeue(&ar->offchan_tx_queue);
		अगर (!skb)
			अवरोध;

		ieee80211_मुक्त_txskb(ar->hw, skb);
	पूर्ण
पूर्ण

व्योम ath10k_offchan_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k, offchan_tx_work);
	काष्ठा ath10k_peer *peer;
	काष्ठा ath10k_vअगर *arvअगर;
	क्रमागत ath10k_hw_txrx_mode txmode;
	क्रमागत ath10k_mac_tx_path txpath;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_sta *sta;
	काष्ठा sk_buff *skb;
	स्थिर u8 *peer_addr;
	पूर्णांक vdev_id;
	पूर्णांक ret;
	अचिन्हित दीर्घ समय_left;
	bool पंचांगp_peer_created = false;

	/* FW requirement: We must create a peer beक्रमe FW will send out
	 * an offchannel frame. Otherwise the frame will be stuck and
	 * never transmitted. We delete the peer upon tx completion.
	 * It is unlikely that a peer क्रम offchannel tx will alपढ़ोy be
	 * present. However it may be in some rare हालs so account क्रम that.
	 * Otherwise we might हटाओ a legitimate peer and अवरोध stuff.
	 */

	क्रम (;;) अणु
		skb = skb_dequeue(&ar->offchan_tx_queue);
		अगर (!skb)
			अवरोध;

		mutex_lock(&ar->conf_mutex);

		ath10k_dbg(ar, ATH10K_DBG_MAC, "mac offchannel skb %pK len %d\n",
			   skb, skb->len);

		hdr = (काष्ठा ieee80211_hdr *)skb->data;
		peer_addr = ieee80211_get_DA(hdr);

		spin_lock_bh(&ar->data_lock);
		vdev_id = ar->scan.vdev_id;
		peer = ath10k_peer_find(ar, vdev_id, peer_addr);
		spin_unlock_bh(&ar->data_lock);

		अगर (peer)
			ath10k_warn(ar, "peer %pM on vdev %d already present\n",
				    peer_addr, vdev_id);

		अगर (!peer) अणु
			ret = ath10k_peer_create(ar, शून्य, शून्य, vdev_id,
						 peer_addr,
						 WMI_PEER_TYPE_DEFAULT);
			अगर (ret)
				ath10k_warn(ar, "failed to create peer %pM on vdev %d: %d\n",
					    peer_addr, vdev_id, ret);
			पंचांगp_peer_created = (ret == 0);
		पूर्ण

		spin_lock_bh(&ar->data_lock);
		reinit_completion(&ar->offchan_tx_completed);
		ar->offchan_tx_skb = skb;
		spin_unlock_bh(&ar->data_lock);

		/* It's safe to access vअगर and sta - conf_mutex guarantees that
		 * sta_state() and हटाओ_पूर्णांकerface() are locked exclusively
		 * out wrt to this offchannel worker.
		 */
		arvअगर = ath10k_get_arvअगर(ar, vdev_id);
		अगर (arvअगर) अणु
			vअगर = arvअगर->vअगर;
			sta = ieee80211_find_sta(vअगर, peer_addr);
		पूर्ण अन्यथा अणु
			vअगर = शून्य;
			sta = शून्य;
		पूर्ण

		txmode = ath10k_mac_tx_h_get_txmode(ar, vअगर, sta, skb);
		txpath = ath10k_mac_tx_h_get_txpath(ar, skb, txmode);

		ret = ath10k_mac_tx(ar, vअगर, txmode, txpath, skb, true);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to transmit offchannel frame: %d\n",
				    ret);
			/* not serious */
		पूर्ण

		समय_left =
		रुको_क्रम_completion_समयout(&ar->offchan_tx_completed, 3 * HZ);
		अगर (समय_left == 0)
			ath10k_warn(ar, "timed out waiting for offchannel skb %pK, len: %d\n",
				    skb, skb->len);

		अगर (!peer && पंचांगp_peer_created) अणु
			ret = ath10k_peer_delete(ar, vdev_id, peer_addr);
			अगर (ret)
				ath10k_warn(ar, "failed to delete peer %pM on vdev %d: %d\n",
					    peer_addr, vdev_id, ret);
		पूर्ण

		mutex_unlock(&ar->conf_mutex);
	पूर्ण
पूर्ण

व्योम ath10k_mgmt_over_wmi_tx_purge(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;

	क्रम (;;) अणु
		skb = skb_dequeue(&ar->wmi_mgmt_tx_queue);
		अगर (!skb)
			अवरोध;

		ieee80211_मुक्त_txskb(ar->hw, skb);
	पूर्ण
पूर्ण

व्योम ath10k_mgmt_over_wmi_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k, wmi_mgmt_tx_work);
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	पूर्णांक ret;

	क्रम (;;) अणु
		skb = skb_dequeue(&ar->wmi_mgmt_tx_queue);
		अगर (!skb)
			अवरोध;

		अगर (test_bit(ATH10K_FW_FEATURE_MGMT_TX_BY_REF,
			     ar->running_fw->fw_file.fw_features)) अणु
			paddr = dma_map_single(ar->dev, skb->data,
					       skb->len, DMA_TO_DEVICE);
			अगर (dma_mapping_error(ar->dev, paddr)) अणु
				ieee80211_मुक्त_txskb(ar->hw, skb);
				जारी;
			पूर्ण
			ret = ath10k_wmi_mgmt_tx_send(ar, skb, paddr);
			अगर (ret) अणु
				ath10k_warn(ar, "failed to transmit management frame by ref via WMI: %d\n",
					    ret);
				/* हटाओ this msdu from idr tracking */
				ath10k_wmi_cleanup_mgmt_tx_send(ar, skb);

				dma_unmap_single(ar->dev, paddr, skb->len,
						 DMA_TO_DEVICE);
				ieee80211_मुक्त_txskb(ar->hw, skb);
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = ath10k_wmi_mgmt_tx(ar, skb);
			अगर (ret) अणु
				ath10k_warn(ar, "failed to transmit management frame via WMI: %d\n",
					    ret);
				ieee80211_मुक्त_txskb(ar->hw, skb);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath10k_mac_txq_init(काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ath10k_txq *artxq;

	अगर (!txq)
		वापस;

	artxq = (व्योम *)txq->drv_priv;
	INIT_LIST_HEAD(&artxq->list);
पूर्ण

अटल व्योम ath10k_mac_txq_unref(काष्ठा ath10k *ar, काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ath10k_skb_cb *cb;
	काष्ठा sk_buff *msdu;
	पूर्णांक msdu_id;

	अगर (!txq)
		वापस;

	spin_lock_bh(&ar->htt.tx_lock);
	idr_क्रम_each_entry(&ar->htt.pending_tx, msdu, msdu_id) अणु
		cb = ATH10K_SKB_CB(msdu);
		अगर (cb->txq == txq)
			cb->txq = शून्य;
	पूर्ण
	spin_unlock_bh(&ar->htt.tx_lock);
पूर्ण

काष्ठा ieee80211_txq *ath10k_mac_txq_lookup(काष्ठा ath10k *ar,
					    u16 peer_id,
					    u8 tid)
अणु
	काष्ठा ath10k_peer *peer;

	lockdep_निश्चित_held(&ar->data_lock);

	peer = ar->peer_map[peer_id];
	अगर (!peer)
		वापस शून्य;

	अगर (peer->हटाओd)
		वापस शून्य;

	अगर (peer->sta)
		वापस peer->sta->txq[tid];
	अन्यथा अगर (peer->vअगर)
		वापस peer->vअगर->txq;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल bool ath10k_mac_tx_can_push(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_txq *artxq = (व्योम *)txq->drv_priv;

	/* No need to get locks */
	अगर (ar->htt.tx_q_state.mode == HTT_TX_MODE_SWITCH_PUSH)
		वापस true;

	अगर (ar->htt.num_pending_tx < ar->htt.tx_q_state.num_push_allowed)
		वापस true;

	अगर (artxq->num_fw_queued < artxq->num_push_allowed)
		वापस true;

	वापस false;
पूर्ण

/* Return estimated airसमय in microsecond, which is calculated using last
 * reported TX rate. This is just a rough estimation because host driver has no
 * knowledge of the actual transmit rate, retries or aggregation. If actual
 * airसमय can be reported by firmware, then delta between estimated and actual
 * airसमय can be adjusted from deficit.
 */
#घोषणा IEEE80211_ATF_OVERHEAD		100	/* IFS + some slot समय */
#घोषणा IEEE80211_ATF_OVERHEAD_IFS	16	/* IFS only */
अटल u16 ath10k_mac_update_airसमय(काष्ठा ath10k *ar,
				     काष्ठा ieee80211_txq *txq,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k_sta *arsta;
	u32 pktlen;
	u16 airसमय = 0;

	अगर (!txq || !txq->sta)
		वापस airसमय;

	अगर (test_bit(WMI_SERVICE_REPORT_AIRTIME, ar->wmi.svc_map))
		वापस airसमय;

	spin_lock_bh(&ar->data_lock);
	arsta = (काष्ठा ath10k_sta *)txq->sta->drv_priv;

	pktlen = skb->len + 38; /* Assume MAC header 30, SNAP 8 क्रम most हाल */
	अगर (arsta->last_tx_bitrate) अणु
		/* airसमय in us, last_tx_bitrate in 100kbps */
		airसमय = (pktlen * 8 * (1000 / 100))
				/ arsta->last_tx_bitrate;
		/* overhead क्रम media access समय and IFS */
		airसमय += IEEE80211_ATF_OVERHEAD_IFS;
	पूर्ण अन्यथा अणु
		/* This is mostly क्रम throttle excessive BC/MC frames, and the
		 * airसमय/rate करोesn't need be exact. Airसमय of BC/MC frames
		 * in 2G get some discount, which helps prevent very low rate
		 * frames from being blocked क्रम too दीर्घ.
		 */
		airसमय = (pktlen * 8 * (1000 / 100)) / 60; /* 6M */
		airसमय += IEEE80211_ATF_OVERHEAD;
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	वापस airसमय;
पूर्ण

पूर्णांक ath10k_mac_tx_push_txq(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा ath10k_txq *artxq = (व्योम *)txq->drv_priv;
	काष्ठा ieee80211_vअगर *vअगर = txq->vअगर;
	काष्ठा ieee80211_sta *sta = txq->sta;
	क्रमागत ath10k_hw_txrx_mode txmode;
	क्रमागत ath10k_mac_tx_path txpath;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	माप_प्रकार skb_len;
	bool is_mgmt, is_presp;
	पूर्णांक ret;
	u16 airसमय;

	spin_lock_bh(&ar->htt.tx_lock);
	ret = ath10k_htt_tx_inc_pending(htt);
	spin_unlock_bh(&ar->htt.tx_lock);

	अगर (ret)
		वापस ret;

	skb = ieee80211_tx_dequeue_ni(hw, txq);
	अगर (!skb) अणु
		spin_lock_bh(&ar->htt.tx_lock);
		ath10k_htt_tx_dec_pending(htt);
		spin_unlock_bh(&ar->htt.tx_lock);

		वापस -ENOENT;
	पूर्ण

	airसमय = ath10k_mac_update_airसमय(ar, txq, skb);
	ath10k_mac_tx_h_fill_cb(ar, vअगर, txq, sta, skb, airसमय);

	skb_len = skb->len;
	txmode = ath10k_mac_tx_h_get_txmode(ar, vअगर, sta, skb);
	txpath = ath10k_mac_tx_h_get_txpath(ar, skb, txmode);
	is_mgmt = (txpath == ATH10K_MAC_TX_HTT_MGMT);

	अगर (is_mgmt) अणु
		hdr = (काष्ठा ieee80211_hdr *)skb->data;
		is_presp = ieee80211_is_probe_resp(hdr->frame_control);

		spin_lock_bh(&ar->htt.tx_lock);
		ret = ath10k_htt_tx_mgmt_inc_pending(htt, is_mgmt, is_presp);

		अगर (ret) अणु
			ath10k_htt_tx_dec_pending(htt);
			spin_unlock_bh(&ar->htt.tx_lock);
			वापस ret;
		पूर्ण
		spin_unlock_bh(&ar->htt.tx_lock);
	पूर्ण

	ret = ath10k_mac_tx(ar, vअगर, txmode, txpath, skb, false);
	अगर (unlikely(ret)) अणु
		ath10k_warn(ar, "failed to push frame: %d\n", ret);

		spin_lock_bh(&ar->htt.tx_lock);
		ath10k_htt_tx_dec_pending(htt);
		अगर (is_mgmt)
			ath10k_htt_tx_mgmt_dec_pending(htt);
		spin_unlock_bh(&ar->htt.tx_lock);

		वापस ret;
	पूर्ण

	spin_lock_bh(&ar->htt.tx_lock);
	artxq->num_fw_queued++;
	spin_unlock_bh(&ar->htt.tx_lock);

	वापस skb_len;
पूर्ण

अटल पूर्णांक ath10k_mac_schedule_txq(काष्ठा ieee80211_hw *hw, u32 ac)
अणु
	काष्ठा ieee80211_txq *txq;
	पूर्णांक ret = 0;

	ieee80211_txq_schedule_start(hw, ac);
	जबतक ((txq = ieee80211_next_txq(hw, ac))) अणु
		जबतक (ath10k_mac_tx_can_push(hw, txq)) अणु
			ret = ath10k_mac_tx_push_txq(hw, txq);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
		ieee80211_वापस_txq(hw, txq, false);
		ath10k_htt_tx_txq_update(hw, txq);
		अगर (ret == -EBUSY)
			अवरोध;
	पूर्ण
	ieee80211_txq_schedule_end(hw, ac);

	वापस ret;
पूर्ण

व्योम ath10k_mac_tx_push_pending(काष्ठा ath10k *ar)
अणु
	काष्ठा ieee80211_hw *hw = ar->hw;
	u32 ac;

	अगर (ar->htt.tx_q_state.mode != HTT_TX_MODE_SWITCH_PUSH)
		वापस;

	अगर (ar->htt.num_pending_tx >= (ar->htt.max_num_pending_tx / 2))
		वापस;

	rcu_पढ़ो_lock();
	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		अगर (ath10k_mac_schedule_txq(hw, ac) == -EBUSY)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ath10k_mac_tx_push_pending);

/************/
/* Scanning */
/************/

व्योम __ath10k_scan_finish(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
		अवरोध;
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		अगर (!ar->scan.is_roc) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = (ar->scan.state ==
					    ATH10K_SCAN_ABORTING),
			पूर्ण;

			ieee80211_scan_completed(ar->hw, &info);
		पूर्ण अन्यथा अगर (ar->scan.roc_notअगरy) अणु
			ieee80211_reमुख्य_on_channel_expired(ar->hw);
		पूर्ण
		fallthrough;
	हाल ATH10K_SCAN_STARTING:
		ar->scan.state = ATH10K_SCAN_IDLE;
		ar->scan_channel = शून्य;
		ar->scan.roc_freq = 0;
		ath10k_offchan_tx_purge(ar);
		cancel_delayed_work(&ar->scan.समयout);
		complete(&ar->scan.completed);
		अवरोध;
	पूर्ण
पूर्ण

व्योम ath10k_scan_finish(काष्ठा ath10k *ar)
अणु
	spin_lock_bh(&ar->data_lock);
	__ath10k_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल पूर्णांक ath10k_scan_stop(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_stop_scan_arg arg = अणु
		.req_id = 1, /* FIXME */
		.req_type = WMI_SCAN_STOP_ONE,
		.u.scan_id = ATH10K_SCAN_ID,
	पूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_wmi_stop_scan(ar, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to stop wmi scan: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ar->scan.completed, 3 * HZ);
	अगर (ret == 0) अणु
		ath10k_warn(ar, "failed to receive scan abortion completion: timed out\n");
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = 0;
	पूर्ण

out:
	/* Scan state should be updated upon scan completion but in हाल
	 * firmware fails to deliver the event (क्रम whatever reason) it is
	 * desired to clean up scan state anyway. Firmware may have just
	 * dropped the scan completion event delivery due to transport pipe
	 * being overflown with data and/or it can recover on its own beक्रमe
	 * next scan request is submitted.
	 */
	spin_lock_bh(&ar->data_lock);
	अगर (ar->scan.state != ATH10K_SCAN_IDLE)
		__ath10k_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);

	वापस ret;
पूर्ण

अटल व्योम ath10k_scan_पात(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
		/* This can happen अगर समयout worker kicked in and called
		 * पातion जबतक scan completion was being processed.
		 */
		अवरोध;
	हाल ATH10K_SCAN_STARTING:
	हाल ATH10K_SCAN_ABORTING:
		ath10k_warn(ar, "refusing scan abortion due to invalid scan state: %s (%d)\n",
			    ath10k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH10K_SCAN_RUNNING:
		ar->scan.state = ATH10K_SCAN_ABORTING;
		spin_unlock_bh(&ar->data_lock);

		ret = ath10k_scan_stop(ar);
		अगर (ret)
			ath10k_warn(ar, "failed to abort scan: %d\n", ret);

		spin_lock_bh(&ar->data_lock);
		अवरोध;
	पूर्ण

	spin_unlock_bh(&ar->data_lock);
पूर्ण

व्योम ath10k_scan_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath10k *ar = container_of(work, काष्ठा ath10k,
					 scan.समयout.work);

	mutex_lock(&ar->conf_mutex);
	ath10k_scan_पात(ar);
	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक ath10k_start_scan(काष्ठा ath10k *ar,
			     स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath10k_wmi_start_scan(ar, arg);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&ar->scan.started, 1 * HZ);
	अगर (ret == 0) अणु
		ret = ath10k_scan_stop(ar);
		अगर (ret)
			ath10k_warn(ar, "failed to stop scan: %d\n", ret);

		वापस -ETIMEDOUT;
	पूर्ण

	/* If we failed to start the scan, वापस error code at
	 * this poपूर्णांक.  This is probably due to some issue in the
	 * firmware, but no need to wedge the driver due to that...
	 */
	spin_lock_bh(&ar->data_lock);
	अगर (ar->scan.state == ATH10K_SCAN_IDLE) अणु
		spin_unlock_bh(&ar->data_lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	वापस 0;
पूर्ण

/**********************/
/* mac80211 callbacks */
/**********************/

अटल व्योम ath10k_mac_op_tx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_tx_control *control,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_htt *htt = &ar->htt;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा ieee80211_sta *sta = control->sta;
	काष्ठा ieee80211_txq *txq = शून्य;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	क्रमागत ath10k_hw_txrx_mode txmode;
	क्रमागत ath10k_mac_tx_path txpath;
	bool is_htt;
	bool is_mgmt;
	bool is_presp;
	पूर्णांक ret;
	u16 airसमय;

	airसमय = ath10k_mac_update_airसमय(ar, txq, skb);
	ath10k_mac_tx_h_fill_cb(ar, vअगर, txq, sta, skb, airसमय);

	txmode = ath10k_mac_tx_h_get_txmode(ar, vअगर, sta, skb);
	txpath = ath10k_mac_tx_h_get_txpath(ar, skb, txmode);
	is_htt = (txpath == ATH10K_MAC_TX_HTT ||
		  txpath == ATH10K_MAC_TX_HTT_MGMT);
	is_mgmt = (txpath == ATH10K_MAC_TX_HTT_MGMT);

	अगर (is_htt) अणु
		spin_lock_bh(&ar->htt.tx_lock);
		is_presp = ieee80211_is_probe_resp(hdr->frame_control);

		ret = ath10k_htt_tx_inc_pending(htt);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to increase tx pending count: %d, dropping\n",
				    ret);
			spin_unlock_bh(&ar->htt.tx_lock);
			ieee80211_मुक्त_txskb(ar->hw, skb);
			वापस;
		पूर्ण

		ret = ath10k_htt_tx_mgmt_inc_pending(htt, is_mgmt, is_presp);
		अगर (ret) अणु
			ath10k_dbg(ar, ATH10K_DBG_MAC, "failed to increase tx mgmt pending count: %d, dropping\n",
				   ret);
			ath10k_htt_tx_dec_pending(htt);
			spin_unlock_bh(&ar->htt.tx_lock);
			ieee80211_मुक्त_txskb(ar->hw, skb);
			वापस;
		पूर्ण
		spin_unlock_bh(&ar->htt.tx_lock);
	पूर्ण

	ret = ath10k_mac_tx(ar, vअगर, txmode, txpath, skb, false);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to transmit frame: %d\n", ret);
		अगर (is_htt) अणु
			spin_lock_bh(&ar->htt.tx_lock);
			ath10k_htt_tx_dec_pending(htt);
			अगर (is_mgmt)
				ath10k_htt_tx_mgmt_dec_pending(htt);
			spin_unlock_bh(&ar->htt.tx_lock);
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

अटल व्योम ath10k_mac_op_wake_tx_queue(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा ath10k *ar = hw->priv;
	पूर्णांक ret;
	u8 ac;

	ath10k_htt_tx_txq_update(hw, txq);
	अगर (ar->htt.tx_q_state.mode != HTT_TX_MODE_SWITCH_PUSH)
		वापस;

	ac = txq->ac;
	ieee80211_txq_schedule_start(hw, ac);
	txq = ieee80211_next_txq(hw, ac);
	अगर (!txq)
		जाओ out;

	जबतक (ath10k_mac_tx_can_push(hw, txq)) अणु
		ret = ath10k_mac_tx_push_txq(hw, txq);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	ieee80211_वापस_txq(hw, txq, false);
	ath10k_htt_tx_txq_update(hw, txq);
out:
	ieee80211_txq_schedule_end(hw, ac);
पूर्ण

/* Must not be called with conf_mutex held as workers can use that also. */
व्योम ath10k_drain_tx(काष्ठा ath10k *ar)
अणु
	lockdep_निश्चित_not_held(&ar->conf_mutex);

	/* make sure rcu-रक्षित mac80211 tx path itself is drained */
	synchronize_net();

	ath10k_offchan_tx_purge(ar);
	ath10k_mgmt_over_wmi_tx_purge(ar);

	cancel_work_sync(&ar->offchan_tx_work);
	cancel_work_sync(&ar->wmi_mgmt_tx_work);
पूर्ण

व्योम ath10k_halt(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;

	lockdep_निश्चित_held(&ar->conf_mutex);

	clear_bit(ATH10K_CAC_RUNNING, &ar->dev_flags);
	ar->filter_flags = 0;
	ar->monitor = false;
	ar->monitor_arvअगर = शून्य;

	अगर (ar->monitor_started)
		ath10k_monitor_stop(ar);

	ar->monitor_started = false;
	ar->tx_छोड़ोd = 0;

	ath10k_scan_finish(ar);
	ath10k_peer_cleanup_all(ar);
	ath10k_stop_radar_confirmation(ar);
	ath10k_core_stop(ar);
	ath10k_hअगर_घातer_करोwn(ar);

	spin_lock_bh(&ar->data_lock);
	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list)
		ath10k_mac_vअगर_beacon_cleanup(arvअगर);
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल पूर्णांक ath10k_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा ath10k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);

	*tx_ant = ar->cfg_tx_chainmask;
	*rx_ant = ar->cfg_rx_chainmask;

	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल bool ath10k_check_chain_mask(काष्ठा ath10k *ar, u32 cm, स्थिर अक्षर *dbg)
अणु
	/* It is not clear that allowing gaps in chainmask
	 * is helpful.  Probably it will not करो what user
	 * is hoping क्रम, so warn in that हाल.
	 */
	अगर (cm == 15 || cm == 7 || cm == 3 || cm == 1 || cm == 0)
		वापस true;

	ath10k_warn(ar, "mac %s antenna chainmask is invalid: 0x%x.  Suggested values: 15, 7, 3, 1 or 0.\n",
		    dbg, cm);
	वापस false;
पूर्ण

अटल पूर्णांक ath10k_mac_get_vht_cap_bf_sts(काष्ठा ath10k *ar)
अणु
	पूर्णांक nsts = ar->vht_cap_info;

	nsts &= IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK;
	nsts >>= IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT;

	/* If firmware करोes not deliver to host number of space-समय
	 * streams supported, assume it support up to 4 BF STS and वापस
	 * the value क्रम VHT CAP: nsts-1)
	 */
	अगर (nsts == 0)
		वापस 3;

	वापस nsts;
पूर्ण

अटल पूर्णांक ath10k_mac_get_vht_cap_bf_sound_dim(काष्ठा ath10k *ar)
अणु
	पूर्णांक sound_dim = ar->vht_cap_info;

	sound_dim &= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK;
	sound_dim >>= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT;

	/* If the sounding dimension is not advertised by the firmware,
	 * let's use a शेष value of 1
	 */
	अगर (sound_dim == 0)
		वापस 1;

	वापस sound_dim;
पूर्ण

अटल काष्ठा ieee80211_sta_vht_cap ath10k_create_vht_cap(काष्ठा ath10k *ar)
अणु
	काष्ठा ieee80211_sta_vht_cap vht_cap = अणु0पूर्ण;
	काष्ठा ath10k_hw_params *hw = &ar->hw_params;
	u16 mcs_map;
	u32 val;
	पूर्णांक i;

	vht_cap.vht_supported = 1;
	vht_cap.cap = ar->vht_cap_info;

	अगर (ar->vht_cap_info & (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
				IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE)) अणु
		val = ath10k_mac_get_vht_cap_bf_sts(ar);
		val <<= IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT;
		val &= IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK;

		vht_cap.cap |= val;
	पूर्ण

	अगर (ar->vht_cap_info & (IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
				IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)) अणु
		val = ath10k_mac_get_vht_cap_bf_sound_dim(ar);
		val <<= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT;
		val &= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK;

		vht_cap.cap |= val;
	पूर्ण

	mcs_map = 0;
	क्रम (i = 0; i < 8; i++) अणु
		अगर ((i < ar->num_rf_chains) && (ar->cfg_tx_chainmask & BIT(i)))
			mcs_map |= IEEE80211_VHT_MCS_SUPPORT_0_9 << (i * 2);
		अन्यथा
			mcs_map |= IEEE80211_VHT_MCS_NOT_SUPPORTED << (i * 2);
	पूर्ण

	अगर (ar->cfg_tx_chainmask <= 1)
		vht_cap.cap &= ~IEEE80211_VHT_CAP_TXSTBC;

	vht_cap.vht_mcs.rx_mcs_map = cpu_to_le16(mcs_map);
	vht_cap.vht_mcs.tx_mcs_map = cpu_to_le16(mcs_map);

	/* If we are supporting 160Mhz or 80+80, then the NIC may be able to करो
	 * a restricted NSS क्रम 160 or 80+80 vs what it can करो क्रम 80Mhz.  Give
	 * user-space a clue अगर that is the हाल.
	 */
	अगर ((vht_cap.cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) &&
	    (hw->vht160_mcs_rx_highest != 0 ||
	     hw->vht160_mcs_tx_highest != 0)) अणु
		vht_cap.vht_mcs.rx_highest = cpu_to_le16(hw->vht160_mcs_rx_highest);
		vht_cap.vht_mcs.tx_highest = cpu_to_le16(hw->vht160_mcs_tx_highest);
	पूर्ण

	वापस vht_cap;
पूर्ण

अटल काष्ठा ieee80211_sta_ht_cap ath10k_get_ht_cap(काष्ठा ath10k *ar)
अणु
	पूर्णांक i;
	काष्ठा ieee80211_sta_ht_cap ht_cap = अणु0पूर्ण;

	अगर (!(ar->ht_cap_info & WMI_HT_CAP_ENABLED))
		वापस ht_cap;

	ht_cap.ht_supported = 1;
	ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_8;
	ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	ht_cap.cap |= IEEE80211_HT_CAP_DSSSCCK40;
	ht_cap.cap |=
		WLAN_HT_CAP_SM_PS_DISABLED << IEEE80211_HT_CAP_SM_PS_SHIFT;

	अगर (ar->ht_cap_info & WMI_HT_CAP_HT20_SGI)
		ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;

	अगर (ar->ht_cap_info & WMI_HT_CAP_HT40_SGI)
		ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;

	अगर (ar->ht_cap_info & WMI_HT_CAP_DYNAMIC_SMPS) अणु
		u32 smps;

		smps   = WLAN_HT_CAP_SM_PS_DYNAMIC;
		smps <<= IEEE80211_HT_CAP_SM_PS_SHIFT;

		ht_cap.cap |= smps;
	पूर्ण

	अगर (ar->ht_cap_info & WMI_HT_CAP_TX_STBC && (ar->cfg_tx_chainmask > 1))
		ht_cap.cap |= IEEE80211_HT_CAP_TX_STBC;

	अगर (ar->ht_cap_info & WMI_HT_CAP_RX_STBC) अणु
		u32 stbc;

		stbc   = ar->ht_cap_info;
		stbc  &= WMI_HT_CAP_RX_STBC;
		stbc >>= WMI_HT_CAP_RX_STBC_MASK_SHIFT;
		stbc <<= IEEE80211_HT_CAP_RX_STBC_SHIFT;
		stbc  &= IEEE80211_HT_CAP_RX_STBC;

		ht_cap.cap |= stbc;
	पूर्ण

	अगर (ar->ht_cap_info & WMI_HT_CAP_LDPC || (ar->ht_cap_info &
	    WMI_HT_CAP_RX_LDPC && (ar->ht_cap_info & WMI_HT_CAP_TX_LDPC)))
		ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;

	अगर (ar->ht_cap_info & WMI_HT_CAP_L_SIG_TXOP_PROT)
		ht_cap.cap |= IEEE80211_HT_CAP_LSIG_TXOP_PROT;

	/* max AMSDU is implicitly taken from vht_cap_info */
	अगर (ar->vht_cap_info & WMI_VHT_CAP_MAX_MPDU_LEN_MASK)
		ht_cap.cap |= IEEE80211_HT_CAP_MAX_AMSDU;

	क्रम (i = 0; i < ar->num_rf_chains; i++) अणु
		अगर (ar->cfg_rx_chainmask & BIT(i))
			ht_cap.mcs.rx_mask[i] = 0xFF;
	पूर्ण

	ht_cap.mcs.tx_params |= IEEE80211_HT_MCS_TX_DEFINED;

	वापस ht_cap;
पूर्ण

अटल व्योम ath10k_mac_setup_ht_vht_cap(काष्ठा ath10k *ar)
अणु
	काष्ठा ieee80211_supported_band *band;
	काष्ठा ieee80211_sta_vht_cap vht_cap;
	काष्ठा ieee80211_sta_ht_cap ht_cap;

	ht_cap = ath10k_get_ht_cap(ar);
	vht_cap = ath10k_create_vht_cap(ar);

	अगर (ar->phy_capability & WHAL_WLAN_11G_CAPABILITY) अणु
		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		band->ht_cap = ht_cap;
	पूर्ण
	अगर (ar->phy_capability & WHAL_WLAN_11A_CAPABILITY) अणु
		band = &ar->mac.sbands[NL80211_BAND_5GHZ];
		band->ht_cap = ht_cap;
		band->vht_cap = vht_cap;
	पूर्ण
पूर्ण

अटल पूर्णांक __ath10k_set_antenna(काष्ठा ath10k *ar, u32 tx_ant, u32 rx_ant)
अणु
	पूर्णांक ret;
	bool is_valid_tx_chain_mask, is_valid_rx_chain_mask;

	lockdep_निश्चित_held(&ar->conf_mutex);

	is_valid_tx_chain_mask = ath10k_check_chain_mask(ar, tx_ant, "tx");
	is_valid_rx_chain_mask = ath10k_check_chain_mask(ar, rx_ant, "rx");

	अगर (!is_valid_tx_chain_mask || !is_valid_rx_chain_mask)
		वापस -EINVAL;

	ar->cfg_tx_chainmask = tx_ant;
	ar->cfg_rx_chainmask = rx_ant;

	अगर ((ar->state != ATH10K_STATE_ON) &&
	    (ar->state != ATH10K_STATE_RESTARTED))
		वापस 0;

	ret = ath10k_wmi_pdev_set_param(ar, ar->wmi.pdev_param->tx_chain_mask,
					tx_ant);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set tx-chainmask: %d, req 0x%x\n",
			    ret, tx_ant);
		वापस ret;
	पूर्ण

	ret = ath10k_wmi_pdev_set_param(ar, ar->wmi.pdev_param->rx_chain_mask,
					rx_ant);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set rx-chainmask: %d, req 0x%x\n",
			    ret, rx_ant);
		वापस ret;
	पूर्ण

	/* Reload HT/VHT capability */
	ath10k_mac_setup_ht_vht_cap(ar);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा ath10k *ar = hw->priv;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);
	ret = __ath10k_set_antenna(ar, tx_ant, rx_ant);
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक __ath10k_fetch_bb_timing_dt(काष्ठा ath10k *ar,
				       काष्ठा wmi_bb_timing_cfg_arg *bb_timing)
अणु
	काष्ठा device_node *node;
	स्थिर अक्षर *fem_name;
	पूर्णांक ret;

	node = ar->dev->of_node;
	अगर (!node)
		वापस -ENOENT;

	ret = of_property_पढ़ो_string_index(node, "ext-fem-name", 0, &fem_name);
	अगर (ret)
		वापस -ENOENT;

	/*
	 * If बाह्यal Front End module used in hardware, then शेष base band timing
	 * parameter cannot be used since they were fine tuned क्रम reference hardware,
	 * so choosing dअगरferent value suitable क्रम that बाह्यal FEM.
	 */
	अगर (!म_भेद("microsemi-lx5586", fem_name)) अणु
		bb_timing->bb_tx_timing = 0x00;
		bb_timing->bb_xpa_timing = 0x0101;
	पूर्ण अन्यथा अणु
		वापस -ENOENT;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot bb_tx_timing 0x%x bb_xpa_timing 0x%x\n",
		   bb_timing->bb_tx_timing, bb_timing->bb_xpa_timing);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_rfसमाप्त_config(काष्ठा ath10k *ar)
अणु
	u32 param;
	पूर्णांक ret;

	अगर (ar->hw_values->rfसमाप्त_pin == 0) अणु
		ath10k_warn(ar, "ath10k does not support hardware rfkill with this device\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac rfkill_pin %d rfkill_cfg %d rfkill_on_level %d",
		   ar->hw_values->rfसमाप्त_pin, ar->hw_values->rfसमाप्त_cfg,
		   ar->hw_values->rfसमाप्त_on_level);

	param = FIELD_PREP(WMI_TLV_RFKILL_CFG_RADIO_LEVEL,
			   ar->hw_values->rfसमाप्त_on_level) |
		FIELD_PREP(WMI_TLV_RFKILL_CFG_GPIO_PIN_NUM,
			   ar->hw_values->rfसमाप्त_pin) |
		FIELD_PREP(WMI_TLV_RFKILL_CFG_PIN_AS_GPIO,
			   ar->hw_values->rfसमाप्त_cfg);

	ret = ath10k_wmi_pdev_set_param(ar,
					ar->wmi.pdev_param->rfसमाप्त_config,
					param);
	अगर (ret) अणु
		ath10k_warn(ar,
			    "failed to set rfkill config 0x%x: %d\n",
			    param, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ath10k_mac_rfसमाप्त_enable_radio(काष्ठा ath10k *ar, bool enable)
अणु
	क्रमागत wmi_tlv_rfसमाप्त_enable_radio param;
	पूर्णांक ret;

	अगर (enable)
		param = WMI_TLV_RFKILL_ENABLE_RADIO_ON;
	अन्यथा
		param = WMI_TLV_RFKILL_ENABLE_RADIO_OFF;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac rfkill enable %d", param);

	ret = ath10k_wmi_pdev_set_param(ar, ar->wmi.pdev_param->rfसमाप्त_enable,
					param);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set rfkill enable param %d: %d\n",
			    param, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath10k *ar = hw->priv;
	u32 param;
	पूर्णांक ret = 0;
	काष्ठा wmi_bb_timing_cfg_arg bb_timing = अणु0पूर्ण;

	/*
	 * This makes sense only when restarting hw. It is harmless to call
	 * unconditionally. This is necessary to make sure no HTT/WMI tx
	 * commands will be submitted जबतक restarting.
	 */
	ath10k_drain_tx(ar);

	mutex_lock(&ar->conf_mutex);

	चयन (ar->state) अणु
	हाल ATH10K_STATE_OFF:
		ar->state = ATH10K_STATE_ON;
		अवरोध;
	हाल ATH10K_STATE_RESTARTING:
		ar->state = ATH10K_STATE_RESTARTED;
		अवरोध;
	हाल ATH10K_STATE_ON:
	हाल ATH10K_STATE_RESTARTED:
	हाल ATH10K_STATE_WEDGED:
		WARN_ON(1);
		ret = -EINVAL;
		जाओ err;
	हाल ATH10K_STATE_UTF:
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	spin_lock_bh(&ar->data_lock);

	अगर (ar->hw_rfसमाप्त_on) अणु
		ar->hw_rfसमाप्त_on = false;
		spin_unlock_bh(&ar->data_lock);
		जाओ err;
	पूर्ण

	spin_unlock_bh(&ar->data_lock);

	ret = ath10k_hअगर_घातer_up(ar, ATH10K_FIRMWARE_MODE_NORMAL);
	अगर (ret) अणु
		ath10k_err(ar, "Could not init hif: %d\n", ret);
		जाओ err_off;
	पूर्ण

	ret = ath10k_core_start(ar, ATH10K_FIRMWARE_MODE_NORMAL,
				&ar->normal_mode_fw);
	अगर (ret) अणु
		ath10k_err(ar, "Could not init core: %d\n", ret);
		जाओ err_घातer_करोwn;
	पूर्ण

	अगर (ar->sys_cap_info & WMI_TLV_SYS_CAP_INFO_RFKILL) अणु
		ret = ath10k_mac_rfसमाप्त_config(ar);
		अगर (ret && ret != -EOPNOTSUPP) अणु
			ath10k_warn(ar, "failed to configure rfkill: %d", ret);
			जाओ err_core_stop;
		पूर्ण
	पूर्ण

	param = ar->wmi.pdev_param->pmf_qos;
	ret = ath10k_wmi_pdev_set_param(ar, param, 1);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to enable PMF QOS: %d\n", ret);
		जाओ err_core_stop;
	पूर्ण

	param = ar->wmi.pdev_param->dynamic_bw;
	ret = ath10k_wmi_pdev_set_param(ar, param, 1);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to enable dynamic BW: %d\n", ret);
		जाओ err_core_stop;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_SPOOF_MAC_SUPPORT, ar->wmi.svc_map)) अणु
		ret = ath10k_wmi_scan_prob_req_oui(ar, ar->mac_addr);
		अगर (ret) अणु
			ath10k_err(ar, "failed to set prob req oui: %i\n", ret);
			जाओ err_core_stop;
		पूर्ण
	पूर्ण

	अगर (test_bit(WMI_SERVICE_ADAPTIVE_OCS, ar->wmi.svc_map)) अणु
		ret = ath10k_wmi_adaptive_qcs(ar, true);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to enable adaptive qcs: %d\n",
				    ret);
			जाओ err_core_stop;
		पूर्ण
	पूर्ण

	अगर (test_bit(WMI_SERVICE_BURST, ar->wmi.svc_map)) अणु
		param = ar->wmi.pdev_param->burst_enable;
		ret = ath10k_wmi_pdev_set_param(ar, param, 0);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to disable burst: %d\n", ret);
			जाओ err_core_stop;
		पूर्ण
	पूर्ण

	param = ar->wmi.pdev_param->idle_ps_config;
	ret = ath10k_wmi_pdev_set_param(ar, param, 1);
	अगर (ret && ret != -EOPNOTSUPP) अणु
		ath10k_warn(ar, "failed to enable idle_ps_config: %d\n", ret);
		जाओ err_core_stop;
	पूर्ण

	__ath10k_set_antenna(ar, ar->cfg_tx_chainmask, ar->cfg_rx_chainmask);

	/*
	 * By शेष FW set ARP frames ac to voice (6). In that हाल ARP
	 * exchange is not working properly क्रम UAPSD enabled AP. ARP requests
	 * which arrives with access category 0 are processed by network stack
	 * and send back with access category 0, but FW changes access category
	 * to 6. Set ARP frames access category to best efक्रमt (0) solves
	 * this problem.
	 */

	param = ar->wmi.pdev_param->arp_ac_override;
	ret = ath10k_wmi_pdev_set_param(ar, param, 0);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set arp ac override parameter: %d\n",
			    ret);
		जाओ err_core_stop;
	पूर्ण

	अगर (test_bit(ATH10K_FW_FEATURE_SUPPORTS_ADAPTIVE_CCA,
		     ar->running_fw->fw_file.fw_features)) अणु
		ret = ath10k_wmi_pdev_enable_adaptive_cca(ar, 1,
							  WMI_CCA_DETECT_LEVEL_AUTO,
							  WMI_CCA_DETECT_MARGIN_AUTO);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to enable adaptive cca: %d\n",
				    ret);
			जाओ err_core_stop;
		पूर्ण
	पूर्ण

	param = ar->wmi.pdev_param->ani_enable;
	ret = ath10k_wmi_pdev_set_param(ar, param, 1);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to enable ani by default: %d\n",
			    ret);
		जाओ err_core_stop;
	पूर्ण

	ar->ani_enabled = true;

	अगर (ath10k_peer_stats_enabled(ar)) अणु
		param = ar->wmi.pdev_param->peer_stats_update_period;
		ret = ath10k_wmi_pdev_set_param(ar, param,
						PEER_DEFAULT_STATS_UPDATE_PERIOD);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "failed to set peer stats period : %d\n",
				    ret);
			जाओ err_core_stop;
		पूर्ण
	पूर्ण

	param = ar->wmi.pdev_param->enable_btcoex;
	अगर (test_bit(WMI_SERVICE_COEX_GPIO, ar->wmi.svc_map) &&
	    test_bit(ATH10K_FW_FEATURE_BTCOEX_PARAM,
		     ar->running_fw->fw_file.fw_features) &&
	    ar->coex_support) अणु
		ret = ath10k_wmi_pdev_set_param(ar, param, 0);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "failed to set btcoex param: %d\n", ret);
			जाओ err_core_stop;
		पूर्ण
		clear_bit(ATH10K_FLAG_BTCOEX, &ar->dev_flags);
	पूर्ण

	अगर (test_bit(WMI_SERVICE_BB_TIMING_CONFIG_SUPPORT, ar->wmi.svc_map)) अणु
		ret = __ath10k_fetch_bb_timing_dt(ar, &bb_timing);
		अगर (!ret) अणु
			ret = ath10k_wmi_pdev_bb_timing(ar, &bb_timing);
			अगर (ret) अणु
				ath10k_warn(ar,
					    "failed to set bb timings: %d\n",
					    ret);
				जाओ err_core_stop;
			पूर्ण
		पूर्ण
	पूर्ण

	ar->num_started_vdevs = 0;
	ath10k_regd_update(ar);

	ath10k_spectral_start(ar);
	ath10k_thermal_set_throttling(ar);

	ar->radar_conf_state = ATH10K_RADAR_CONFIRMATION_IDLE;

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_core_stop:
	ath10k_core_stop(ar);

err_घातer_करोwn:
	ath10k_hअगर_घातer_करोwn(ar);

err_off:
	ar->state = ATH10K_STATE_OFF;

err:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम ath10k_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath10k *ar = hw->priv;

	ath10k_drain_tx(ar);

	mutex_lock(&ar->conf_mutex);
	अगर (ar->state != ATH10K_STATE_OFF) अणु
		अगर (!ar->hw_rfसमाप्त_on)
			ath10k_halt(ar);
		ar->state = ATH10K_STATE_OFF;
	पूर्ण
	mutex_unlock(&ar->conf_mutex);

	cancel_work_sync(&ar->set_coverage_class_work);
	cancel_delayed_work_sync(&ar->scan.समयout);
	cancel_work_sync(&ar->restart_work);
पूर्ण

अटल पूर्णांक ath10k_config_ps(काष्ठा ath10k *ar)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		ret = ath10k_mac_vअगर_setup_ps(arvअगर);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to setup powersave: %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	पूर्णांक ret = 0;

	mutex_lock(&ar->conf_mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_PS)
		ath10k_config_ps(ar);

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		ar->monitor = conf->flags & IEEE80211_CONF_MONITOR;
		ret = ath10k_monitor_recalc(ar);
		अगर (ret)
			ath10k_warn(ar, "failed to recalc monitor: %d\n", ret);
	पूर्ण

	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल u32 get_nss_from_chainmask(u16 chain_mask)
अणु
	अगर ((chain_mask & 0xf) == 0xf)
		वापस 4;
	अन्यथा अगर ((chain_mask & 0x7) == 0x7)
		वापस 3;
	अन्यथा अगर ((chain_mask & 0x3) == 0x3)
		वापस 2;
	वापस 1;
पूर्ण

अटल पूर्णांक ath10k_mac_set_txbf_conf(काष्ठा ath10k_vअगर *arvअगर)
अणु
	u32 value = 0;
	काष्ठा ath10k *ar = arvअगर->ar;
	पूर्णांक nsts;
	पूर्णांक sound_dim;

	अगर (ath10k_wmi_get_txbf_conf_scheme(ar) != WMI_TXBF_CONF_BEFORE_ASSOC)
		वापस 0;

	nsts = ath10k_mac_get_vht_cap_bf_sts(ar);
	अगर (ar->vht_cap_info & (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
				IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE))
		value |= SM(nsts, WMI_TXBF_STS_CAP_OFFSET);

	sound_dim = ath10k_mac_get_vht_cap_bf_sound_dim(ar);
	अगर (ar->vht_cap_info & (IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
				IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE))
		value |= SM(sound_dim, WMI_BF_SOUND_DIM_OFFSET);

	अगर (!value)
		वापस 0;

	अगर (ar->vht_cap_info & IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE)
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFER;

	अगर (ar->vht_cap_info & IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)
		value |= (WMI_VDEV_PARAM_TXBF_MU_TX_BFER |
			  WMI_VDEV_PARAM_TXBF_SU_TX_BFER);

	अगर (ar->vht_cap_info & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE)
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFEE;

	अगर (ar->vht_cap_info & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE)
		value |= (WMI_VDEV_PARAM_TXBF_MU_TX_BFEE |
			  WMI_VDEV_PARAM_TXBF_SU_TX_BFEE);

	वापस ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id,
					 ar->wmi.vdev_param->txbf, value);
पूर्ण

/*
 * TODO:
 * Figure out how to handle WMI_VDEV_SUBTYPE_P2P_DEVICE,
 * because we will send mgmt frames without CCK. This requirement
 * क्रम P2P_FIND/GO_NEG should be handled by checking CCK flag
 * in the TX packet.
 */
अटल पूर्णांक ath10k_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_peer *peer;
	क्रमागत wmi_sta_घातersave_param param;
	पूर्णांक ret = 0;
	u32 value;
	पूर्णांक bit;
	पूर्णांक i;
	u32 vdev_param;

	vअगर->driver_flags |= IEEE80211_VIF_SUPPORTS_UAPSD;

	mutex_lock(&ar->conf_mutex);

	स_रखो(arvअगर, 0, माप(*arvअगर));
	ath10k_mac_txq_init(vअगर->txq);

	arvअगर->ar = ar;
	arvअगर->vअगर = vअगर;

	INIT_LIST_HEAD(&arvअगर->list);
	INIT_WORK(&arvअगर->ap_csa_work, ath10k_mac_vअगर_ap_csa_work);
	INIT_DELAYED_WORK(&arvअगर->connection_loss_work,
			  ath10k_mac_vअगर_sta_connection_loss_work);

	क्रम (i = 0; i < ARRAY_SIZE(arvअगर->bitrate_mask.control); i++) अणु
		arvअगर->bitrate_mask.control[i].legacy = 0xffffffff;
		स_रखो(arvअगर->bitrate_mask.control[i].ht_mcs, 0xff,
		       माप(arvअगर->bitrate_mask.control[i].ht_mcs));
		स_रखो(arvअगर->bitrate_mask.control[i].vht_mcs, 0xff,
		       माप(arvअगर->bitrate_mask.control[i].vht_mcs));
	पूर्ण

	अगर (ar->num_peers >= ar->max_num_peers) अणु
		ath10k_warn(ar, "refusing vdev creation due to insufficient peer entry resources in firmware\n");
		ret = -ENOBUFS;
		जाओ err;
	पूर्ण

	अगर (ar->मुक्त_vdev_map == 0) अणु
		ath10k_warn(ar, "Free vdev map is empty, no more interfaces allowed.\n");
		ret = -EBUSY;
		जाओ err;
	पूर्ण
	bit = __ffs64(ar->मुक्त_vdev_map);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac create vdev %i map %llx\n",
		   bit, ar->मुक्त_vdev_map);

	arvअगर->vdev_id = bit;
	arvअगर->vdev_subtype =
		ath10k_wmi_get_vdev_subtype(ar, WMI_VDEV_SUBTYPE_NONE);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_P2P_DEVICE:
		arvअगर->vdev_type = WMI_VDEV_TYPE_STA;
		arvअगर->vdev_subtype = ath10k_wmi_get_vdev_subtype
					(ar, WMI_VDEV_SUBTYPE_P2P_DEVICE);
		अवरोध;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_STATION:
		arvअगर->vdev_type = WMI_VDEV_TYPE_STA;
		अगर (vअगर->p2p)
			arvअगर->vdev_subtype = ath10k_wmi_get_vdev_subtype
					(ar, WMI_VDEV_SUBTYPE_P2P_CLIENT);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		arvअगर->vdev_type = WMI_VDEV_TYPE_IBSS;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (test_bit(WMI_SERVICE_MESH_11S, ar->wmi.svc_map)) अणु
			arvअगर->vdev_subtype = ath10k_wmi_get_vdev_subtype
						(ar, WMI_VDEV_SUBTYPE_MESH_11S);
		पूर्ण अन्यथा अगर (!test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags)) अणु
			ret = -EINVAL;
			ath10k_warn(ar, "must load driver with rawmode=1 to add mesh interfaces\n");
			जाओ err;
		पूर्ण
		arvअगर->vdev_type = WMI_VDEV_TYPE_AP;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		arvअगर->vdev_type = WMI_VDEV_TYPE_AP;

		अगर (vअगर->p2p)
			arvअगर->vdev_subtype = ath10k_wmi_get_vdev_subtype
						(ar, WMI_VDEV_SUBTYPE_P2P_GO);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		arvअगर->vdev_type = WMI_VDEV_TYPE_MONITOR;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	/* Using vdev_id as queue number will make it very easy to करो per-vअगर
	 * tx queue locking. This shouldn't wrap due to पूर्णांकerface combinations
	 * but करो a modulo क्रम correctness sake and prevent using offchannel tx
	 * queues क्रम regular vअगर tx.
	 */
	vअगर->cab_queue = arvअगर->vdev_id % (IEEE80211_MAX_QUEUES - 1);
	क्रम (i = 0; i < ARRAY_SIZE(vअगर->hw_queue); i++)
		vअगर->hw_queue[i] = arvअगर->vdev_id % (IEEE80211_MAX_QUEUES - 1);

	/* Some firmware revisions करोn't रुको क्रम beacon tx completion beक्रमe
	 * sending another SWBA event. This could lead to hardware using old
	 * (मुक्तd) beacon data in some हालs, e.g. tx credit starvation
	 * combined with missed TBTT. This is very rare.
	 *
	 * On non-IOMMU-enabled hosts this could be a possible security issue
	 * because hw could beacon some अक्रमom data on the air.  On
	 * IOMMU-enabled hosts DMAR faults would occur in most हालs and target
	 * device would crash.
	 *
	 * Since there are no beacon tx completions (implicit nor explicit)
	 * propagated to host the only workaround क्रम this is to allocate a
	 * DMA-coherent buffer क्रम a lअगरeसमय of a vअगर and use it क्रम all
	 * beacon tx commands. Worst हाल क्रम this approach is some beacons may
	 * become corrupted, e.g. have garbled IEs or out-of-date TIM biपंचांगap.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC ||
	    vअगर->type == NL80211_IFTYPE_MESH_POINT ||
	    vअगर->type == NL80211_IFTYPE_AP) अणु
		arvअगर->beacon_buf = dma_alloc_coherent(ar->dev,
						       IEEE80211_MAX_FRAME_LEN,
						       &arvअगर->beacon_paddr,
						       GFP_ATOMIC);
		अगर (!arvअगर->beacon_buf) अणु
			ret = -ENOMEM;
			ath10k_warn(ar, "failed to allocate beacon buffer: %d\n",
				    ret);
			जाओ err;
		पूर्ण
	पूर्ण
	अगर (test_bit(ATH10K_FLAG_HW_CRYPTO_DISABLED, &ar->dev_flags))
		arvअगर->nohwcrypt = true;

	अगर (arvअगर->nohwcrypt &&
	    !test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags)) अणु
		ath10k_warn(ar, "cryptmode module param needed for sw crypto\n");
		जाओ err;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev create %d (add interface) type %d subtype %d bcnmode %s\n",
		   arvअगर->vdev_id, arvअगर->vdev_type, arvअगर->vdev_subtype,
		   arvअगर->beacon_buf ? "single-buf" : "per-skb");

	ret = ath10k_wmi_vdev_create(ar, arvअगर->vdev_id, arvअगर->vdev_type,
				     arvअगर->vdev_subtype, vअगर->addr);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to create WMI vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_VDEV_DISABLE_4_ADDR_SRC_LRN_SUPPORT,
		     ar->wmi.svc_map)) अणु
		vdev_param = ar->wmi.vdev_param->disable_4addr_src_lrn;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
						WMI_VDEV_DISABLE_4_ADDR_SRC_LRN);
		अगर (ret && ret != -EOPNOTSUPP) अणु
			ath10k_warn(ar, "failed to disable 4addr src lrn vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
		पूर्ण
	पूर्ण

	ar->मुक्त_vdev_map &= ~(1LL << arvअगर->vdev_id);
	spin_lock_bh(&ar->data_lock);
	list_add(&arvअगर->list, &ar->arvअगरs);
	spin_unlock_bh(&ar->data_lock);

	/* It makes no sense to have firmware करो keepalives. mac80211 alपढ़ोy
	 * takes care of this with idle connection polling.
	 */
	ret = ath10k_mac_vअगर_disable_keepalive(arvअगर);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to disable keepalive on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err_vdev_delete;
	पूर्ण

	arvअगर->def_wep_key_idx = -1;

	vdev_param = ar->wmi.vdev_param->tx_encap_type;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
					ATH10K_HW_TXRX_NATIVE_WIFI);
	/* 10.X firmware करोes not support this VDEV parameter. Do not warn */
	अगर (ret && ret != -EOPNOTSUPP) अणु
		ath10k_warn(ar, "failed to set vdev %i TX encapsulation: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err_vdev_delete;
	पूर्ण

	/* Configuring number of spatial stream क्रम monitor पूर्णांकerface is causing
	 * target निश्चित in qca9888 and qca6174.
	 */
	अगर (ar->cfg_tx_chainmask && (vअगर->type != NL80211_IFTYPE_MONITOR)) अणु
		u16 nss = get_nss_from_chainmask(ar->cfg_tx_chainmask);

		vdev_param = ar->wmi.vdev_param->nss;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
						nss);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set vdev %i chainmask 0x%x, nss %i: %d\n",
				    arvअगर->vdev_id, ar->cfg_tx_chainmask, nss,
				    ret);
			जाओ err_vdev_delete;
		पूर्ण
	पूर्ण

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP ||
	    arvअगर->vdev_type == WMI_VDEV_TYPE_IBSS) अणु
		ret = ath10k_peer_create(ar, vअगर, शून्य, arvअगर->vdev_id,
					 vअगर->addr, WMI_PEER_TYPE_DEFAULT);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to create vdev %i peer for AP/IBSS: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_vdev_delete;
		पूर्ण

		spin_lock_bh(&ar->data_lock);

		peer = ath10k_peer_find(ar, arvअगर->vdev_id, vअगर->addr);
		अगर (!peer) अणु
			ath10k_warn(ar, "failed to lookup peer %pM on vdev %i\n",
				    vअगर->addr, arvअगर->vdev_id);
			spin_unlock_bh(&ar->data_lock);
			ret = -ENOENT;
			जाओ err_peer_delete;
		पूर्ण

		arvअगर->peer_id = find_first_bit(peer->peer_ids,
						ATH10K_MAX_NUM_PEER_IDS);

		spin_unlock_bh(&ar->data_lock);
	पूर्ण अन्यथा अणु
		arvअगर->peer_id = HTT_INVALID_PEERID;
	पूर्ण

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP) अणु
		ret = ath10k_mac_set_kickout(arvअगर);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set vdev %i kickout parameters: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_delete;
		पूर्ण
	पूर्ण

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_STA) अणु
		param = WMI_STA_PS_PARAM_RX_WAKE_POLICY;
		value = WMI_STA_PS_RX_WAKE_POLICY_WAKE;
		ret = ath10k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
						  param, value);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set vdev %i RX wake policy: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_delete;
		पूर्ण

		ret = ath10k_mac_vअगर_recalc_ps_wake_threshold(arvअगर);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to recalc ps wake threshold on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_delete;
		पूर्ण

		ret = ath10k_mac_vअगर_recalc_ps_poll_count(arvअगर);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to recalc ps poll count on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_delete;
		पूर्ण
	पूर्ण

	ret = ath10k_mac_set_txbf_conf(arvअगर);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set txbf for vdev %d: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err_peer_delete;
	पूर्ण

	ret = ath10k_mac_set_rts(arvअगर, ar->hw->wiphy->rts_threshold);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set rts threshold for vdev %d: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err_peer_delete;
	पूर्ण

	arvअगर->txघातer = vअगर->bss_conf.txघातer;
	ret = ath10k_mac_txघातer_recalc(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to recalc tx power: %d\n", ret);
		जाओ err_peer_delete;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_RTT_RESPONDER_ROLE, ar->wmi.svc_map)) अणु
		vdev_param = ar->wmi.vdev_param->rtt_responder_role;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
						arvअगर->fपंचांग_responder);

		/* It is harmless to not set FTM role. Do not warn */
		अगर (ret && ret != -EOPNOTSUPP)
			ath10k_warn(ar, "failed to set vdev %i FTM Responder: %d\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR) अणु
		ar->monitor_arvअगर = arvअगर;
		ret = ath10k_monitor_recalc(ar);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to recalc monitor: %d\n", ret);
			जाओ err_peer_delete;
		पूर्ण
	पूर्ण

	spin_lock_bh(&ar->htt.tx_lock);
	अगर (!ar->tx_छोड़ोd)
		ieee80211_wake_queue(ar->hw, arvअगर->vdev_id);
	spin_unlock_bh(&ar->htt.tx_lock);

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_peer_delete:
	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP ||
	    arvअगर->vdev_type == WMI_VDEV_TYPE_IBSS) अणु
		ath10k_wmi_peer_delete(ar, arvअगर->vdev_id, vअगर->addr);
		ath10k_रुको_क्रम_peer_delete_करोne(ar, arvअगर->vdev_id,
						 vअगर->addr);
	पूर्ण

err_vdev_delete:
	ath10k_wmi_vdev_delete(ar, arvअगर->vdev_id);
	ar->मुक्त_vdev_map |= 1LL << arvअगर->vdev_id;
	spin_lock_bh(&ar->data_lock);
	list_del(&arvअगर->list);
	spin_unlock_bh(&ar->data_lock);

err:
	अगर (arvअगर->beacon_buf) अणु
		dma_मुक्त_coherent(ar->dev, IEEE80211_MAX_FRAME_LEN,
				  arvअगर->beacon_buf, arvअगर->beacon_paddr);
		arvअगर->beacon_buf = शून्य;
	पूर्ण

	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल व्योम ath10k_mac_vअगर_tx_unlock_all(काष्ठा ath10k_vअगर *arvअगर)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BITS_PER_LONG; i++)
		ath10k_mac_vअगर_tx_unlock(arvअगर, i);
पूर्ण

अटल व्योम ath10k_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_peer *peer;
	अचिन्हित दीर्घ समय_left;
	पूर्णांक ret;
	पूर्णांक i;

	cancel_work_sync(&arvअगर->ap_csa_work);
	cancel_delayed_work_sync(&arvअगर->connection_loss_work);

	mutex_lock(&ar->conf_mutex);

	ret = ath10k_spectral_vअगर_stop(arvअगर);
	अगर (ret)
		ath10k_warn(ar, "failed to stop spectral for vdev %i: %d\n",
			    arvअगर->vdev_id, ret);

	ar->मुक्त_vdev_map |= 1LL << arvअगर->vdev_id;
	spin_lock_bh(&ar->data_lock);
	list_del(&arvअगर->list);
	spin_unlock_bh(&ar->data_lock);

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP ||
	    arvअगर->vdev_type == WMI_VDEV_TYPE_IBSS) अणु
		ret = ath10k_wmi_peer_delete(arvअगर->ar, arvअगर->vdev_id,
					     vअगर->addr);
		अगर (ret)
			ath10k_warn(ar, "failed to submit AP/IBSS self-peer removal on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);

		ath10k_रुको_क्रम_peer_delete_करोne(ar, arvअगर->vdev_id,
						 vअगर->addr);
		kमुक्त(arvअगर->u.ap.noa_data);
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %i delete (remove interface)\n",
		   arvअगर->vdev_id);

	ret = ath10k_wmi_vdev_delete(ar, arvअगर->vdev_id);
	अगर (ret)
		ath10k_warn(ar, "failed to delete WMI vdev %i: %d\n",
			    arvअगर->vdev_id, ret);

	अगर (test_bit(WMI_SERVICE_SYNC_DELETE_CMDS, ar->wmi.svc_map)) अणु
		समय_left = रुको_क्रम_completion_समयout(&ar->vdev_delete_करोne,
							ATH10K_VDEV_DELETE_TIMEOUT_HZ);
		अगर (समय_left == 0) अणु
			ath10k_warn(ar, "Timeout in receiving vdev delete response\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Some firmware revisions करोn't notअगरy host about self-peer removal
	 * until after associated vdev is deleted.
	 */
	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP ||
	    arvअगर->vdev_type == WMI_VDEV_TYPE_IBSS) अणु
		ret = ath10k_रुको_क्रम_peer_deleted(ar, arvअगर->vdev_id,
						   vअगर->addr);
		अगर (ret)
			ath10k_warn(ar, "failed to remove AP self-peer on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);

		spin_lock_bh(&ar->data_lock);
		ar->num_peers--;
		spin_unlock_bh(&ar->data_lock);
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	क्रम (i = 0; i < ARRAY_SIZE(ar->peer_map); i++) अणु
		peer = ar->peer_map[i];
		अगर (!peer)
			जारी;

		अगर (peer->vअगर == vअगर) अणु
			ath10k_warn(ar, "found vif peer %pM entry on vdev %i after it was supposedly removed\n",
				    vअगर->addr, arvअगर->vdev_id);
			peer->vअगर = शून्य;
		पूर्ण
	पूर्ण

	/* Clean this up late, less opportunity क्रम firmware to access
	 * DMA memory we have deleted.
	 */
	ath10k_mac_vअगर_beacon_cleanup(arvअगर);
	spin_unlock_bh(&ar->data_lock);

	ath10k_peer_cleanup(ar, arvअगर->vdev_id);
	ath10k_mac_txq_unref(ar, vअगर->txq);

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR) अणु
		ar->monitor_arvअगर = शून्य;
		ret = ath10k_monitor_recalc(ar);
		अगर (ret)
			ath10k_warn(ar, "failed to recalc monitor: %d\n", ret);
	पूर्ण

	ret = ath10k_mac_txघातer_recalc(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to recalc tx power: %d\n", ret);

	spin_lock_bh(&ar->htt.tx_lock);
	ath10k_mac_vअगर_tx_unlock_all(arvअगर);
	spin_unlock_bh(&ar->htt.tx_lock);

	ath10k_mac_txq_unref(ar, vअगर->txq);

out:
	mutex_unlock(&ar->conf_mutex);
पूर्ण

/*
 * FIXME: Has to be verअगरied.
 */
#घोषणा SUPPORTED_FILTERS			\
	(FIF_ALLMULTI |				\
	FIF_CONTROL |				\
	FIF_PSPOLL |				\
	FIF_OTHER_BSS |				\
	FIF_BCN_PRBRESP_PROMISC |		\
	FIF_PROBE_REQ |				\
	FIF_FCSFAIL)

अटल व्योम ath10k_configure_filter(काष्ठा ieee80211_hw *hw,
				    अचिन्हित पूर्णांक changed_flags,
				    अचिन्हित पूर्णांक *total_flags,
				    u64 multicast)
अणु
	काष्ठा ath10k *ar = hw->priv;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	changed_flags &= SUPPORTED_FILTERS;
	*total_flags &= SUPPORTED_FILTERS;
	ar->filter_flags = *total_flags;

	ret = ath10k_monitor_recalc(ar);
	अगर (ret)
		ath10k_warn(ar, "failed to recalc monitor: %d\n", ret);

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल व्योम ath10k_recalculate_mgmt_rate(काष्ठा ath10k *ar,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा cfg80211_chan_def *def)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	स्थिर काष्ठा ieee80211_supported_band *sband;
	u8 basic_rate_idx;
	पूर्णांक hw_rate_code;
	u32 vdev_param;
	u16 bitrate;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	sband = ar->hw->wiphy->bands[def->chan->band];
	basic_rate_idx = ffs(vअगर->bss_conf.basic_rates) - 1;
	bitrate = sband->bitrates[basic_rate_idx].bitrate;

	hw_rate_code = ath10k_mac_get_rate_hw_value(bitrate);
	अगर (hw_rate_code < 0) अणु
		ath10k_warn(ar, "bitrate not supported %d\n", bitrate);
		वापस;
	पूर्ण

	vdev_param = ar->wmi.vdev_param->mgmt_rate;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
					hw_rate_code);
	अगर (ret)
		ath10k_warn(ar, "failed to set mgmt tx rate %d\n", ret);
पूर्ण

अटल व्योम ath10k_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *info,
				    u32 changed)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def def;
	u32 vdev_param, pdev_param, slotसमय, preamble;
	u16 bitrate, hw_value;
	u8 rate, rateidx;
	पूर्णांक ret = 0, mcast_rate;
	क्रमागत nl80211_band band;

	mutex_lock(&ar->conf_mutex);

	अगर (changed & BSS_CHANGED_IBSS)
		ath10k_control_ibss(arvअगर, info, vअगर->addr);

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		arvअगर->beacon_पूर्णांकerval = info->beacon_पूर्णांक;
		vdev_param = ar->wmi.vdev_param->beacon_पूर्णांकerval;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
						arvअगर->beacon_पूर्णांकerval);
		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac vdev %d beacon_interval %d\n",
			   arvअगर->vdev_id, arvअगर->beacon_पूर्णांकerval);

		अगर (ret)
			ath10k_warn(ar, "failed to set beacon interval for vdev %d: %i\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON) अणु
		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "vdev %d set beacon tx mode to staggered\n",
			   arvअगर->vdev_id);

		pdev_param = ar->wmi.pdev_param->beacon_tx_mode;
		ret = ath10k_wmi_pdev_set_param(ar, pdev_param,
						WMI_BEACON_STAGGERED_MODE);
		अगर (ret)
			ath10k_warn(ar, "failed to set beacon mode for vdev %d: %i\n",
				    arvअगर->vdev_id, ret);

		ret = ath10k_mac_setup_bcn_पंचांगpl(arvअगर);
		अगर (ret)
			ath10k_warn(ar, "failed to update beacon template: %d\n",
				    ret);

		अगर (ieee80211_vअगर_is_mesh(vअगर)) अणु
			/* mesh करोesn't use SSID but firmware needs it */
			म_नकलन(arvअगर->u.ap.ssid, "mesh",
				माप(arvअगर->u.ap.ssid));
			arvअगर->u.ap.ssid_len = 4;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_AP_PROBE_RESP) अणु
		ret = ath10k_mac_setup_prb_पंचांगpl(arvअगर);
		अगर (ret)
			ath10k_warn(ar, "failed to setup probe resp template on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	अगर (changed & (BSS_CHANGED_BEACON_INFO | BSS_CHANGED_BEACON)) अणु
		arvअगर->dtim_period = info->dtim_period;

		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac vdev %d dtim_period %d\n",
			   arvअगर->vdev_id, arvअगर->dtim_period);

		vdev_param = ar->wmi.vdev_param->dtim_period;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
						arvअगर->dtim_period);
		अगर (ret)
			ath10k_warn(ar, "failed to set dtim period for vdev %d: %i\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_SSID &&
	    vअगर->type == NL80211_IFTYPE_AP) अणु
		arvअगर->u.ap.ssid_len = info->ssid_len;
		अगर (info->ssid_len)
			स_नकल(arvअगर->u.ap.ssid, info->ssid, info->ssid_len);
		arvअगर->u.ap.hidden_ssid = info->hidden_ssid;
	पूर्ण

	अगर (changed & BSS_CHANGED_BSSID && !is_zero_ether_addr(info->bssid))
		ether_addr_copy(arvअगर->bssid, info->bssid);

	अगर (changed & BSS_CHANGED_FTM_RESPONDER &&
	    arvअगर->fपंचांग_responder != info->fपंचांग_responder &&
	    test_bit(WMI_SERVICE_RTT_RESPONDER_ROLE, ar->wmi.svc_map)) अणु
		arvअगर->fपंचांग_responder = info->fपंचांग_responder;

		vdev_param = ar->wmi.vdev_param->rtt_responder_role;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
						arvअगर->fपंचांग_responder);

		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac vdev %d ftm_responder %d:ret %d\n",
			   arvअगर->vdev_id, arvअगर->fपंचांग_responder, ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED)
		ath10k_control_beaconing(arvअगर, info);

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		arvअगर->use_cts_prot = info->use_cts_prot;

		ret = ath10k_recalc_rtscts_prot(arvअगर);
		अगर (ret)
			ath10k_warn(ar, "failed to recalculate rts/cts prot for vdev %d: %d\n",
				    arvअगर->vdev_id, ret);

		अगर (ath10k_mac_can_set_cts_prot(arvअगर)) अणु
			ret = ath10k_mac_set_cts_prot(arvअगर);
			अगर (ret)
				ath10k_warn(ar, "failed to set cts protection for vdev %d: %d\n",
					    arvअगर->vdev_id, ret);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		अगर (info->use_लघु_slot)
			slotसमय = WMI_VDEV_SLOT_TIME_SHORT; /* 9us */

		अन्यथा
			slotसमय = WMI_VDEV_SLOT_TIME_LONG; /* 20us */

		ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d slot_time %d\n",
			   arvअगर->vdev_id, slotसमय);

		vdev_param = ar->wmi.vdev_param->slot_समय;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
						slotसमय);
		अगर (ret)
			ath10k_warn(ar, "failed to set erp slot for vdev %d: %i\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		अगर (info->use_लघु_preamble)
			preamble = WMI_VDEV_PREAMBLE_SHORT;
		अन्यथा
			preamble = WMI_VDEV_PREAMBLE_LONG;

		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac vdev %d preamble %dn",
			   arvअगर->vdev_id, preamble);

		vdev_param = ar->wmi.vdev_param->preamble;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
						preamble);
		अगर (ret)
			ath10k_warn(ar, "failed to set preamble for vdev %d: %i\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		अगर (info->assoc) अणु
			/* Workaround: Make sure monitor vdev is not running
			 * when associating to prevent some firmware revisions
			 * (e.g. 10.1 and 10.2) from crashing.
			 */
			अगर (ar->monitor_started)
				ath10k_monitor_stop(ar);
			ath10k_bss_assoc(hw, vअगर, info);
			ath10k_monitor_recalc(ar);
		पूर्ण अन्यथा अणु
			ath10k_bss_disassoc(hw, vअगर);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_TXPOWER) अणु
		ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev_id %i txpower %d\n",
			   arvअगर->vdev_id, info->txघातer);

		arvअगर->txघातer = info->txघातer;
		ret = ath10k_mac_txघातer_recalc(ar);
		अगर (ret)
			ath10k_warn(ar, "failed to recalc tx power: %d\n", ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_PS) अणु
		arvअगर->ps = vअगर->bss_conf.ps;

		ret = ath10k_config_ps(ar);
		अगर (ret)
			ath10k_warn(ar, "failed to setup ps on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_MCAST_RATE &&
	    !ath10k_mac_vअगर_chan(arvअगर->vअगर, &def)) अणु
		band = def.chan->band;
		mcast_rate = vअगर->bss_conf.mcast_rate[band];
		अगर (mcast_rate > 0)
			rateidx = mcast_rate - 1;
		अन्यथा
			rateidx = ffs(vअगर->bss_conf.basic_rates) - 1;

		अगर (ar->phy_capability & WHAL_WLAN_11A_CAPABILITY)
			rateidx += ATH10K_MAC_FIRST_OFDM_RATE_IDX;

		bitrate = ath10k_wmi_legacy_rates[rateidx].bitrate;
		hw_value = ath10k_wmi_legacy_rates[rateidx].hw_value;
		अगर (ath10k_mac_bitrate_is_cck(bitrate))
			preamble = WMI_RATE_PREAMBLE_CCK;
		अन्यथा
			preamble = WMI_RATE_PREAMBLE_OFDM;

		rate = ATH10K_HW_RATECODE(hw_value, 0, preamble);

		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac vdev %d mcast_rate %x\n",
			   arvअगर->vdev_id, rate);

		vdev_param = ar->wmi.vdev_param->mcast_data_rate;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id,
						vdev_param, rate);
		अगर (ret)
			ath10k_warn(ar,
				    "failed to set mcast rate on vdev %i: %d\n",
				    arvअगर->vdev_id,  ret);

		vdev_param = ar->wmi.vdev_param->bcast_data_rate;
		ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id,
						vdev_param, rate);
		अगर (ret)
			ath10k_warn(ar,
				    "failed to set bcast rate on vdev %i: %d\n",
				    arvअगर->vdev_id,  ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES &&
	    !ath10k_mac_vअगर_chan(arvअगर->vअगर, &def))
		ath10k_recalculate_mgmt_rate(ar, vअगर, &def);

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल व्योम ath10k_mac_op_set_coverage_class(काष्ठा ieee80211_hw *hw, s16 value)
अणु
	काष्ठा ath10k *ar = hw->priv;

	/* This function should never be called अगर setting the coverage class
	 * is not supported on this hardware.
	 */
	अगर (!ar->hw_params.hw_ops->set_coverage_class) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण
	ar->hw_params.hw_ops->set_coverage_class(ar, value);
पूर्ण

काष्ठा ath10k_mac_tdls_iter_data अणु
	u32 num_tdls_stations;
	काष्ठा ieee80211_vअगर *curr_vअगर;
पूर्ण;

अटल व्योम ath10k_mac_tdls_vअगर_stations_count_iter(व्योम *data,
						    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k_mac_tdls_iter_data *iter_data = data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ieee80211_vअगर *sta_vअगर = arsta->arvअगर->vअगर;

	अगर (sta->tdls && sta_vअगर == iter_data->curr_vअगर)
		iter_data->num_tdls_stations++;
पूर्ण

अटल पूर्णांक ath10k_mac_tdls_vअगर_stations_count(काष्ठा ieee80211_hw *hw,
					      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k_mac_tdls_iter_data data = अणुपूर्ण;

	data.curr_vअगर = vअगर;

	ieee80211_iterate_stations_atomic(hw,
					  ath10k_mac_tdls_vअगर_stations_count_iter,
					  &data);
	वापस data.num_tdls_stations;
पूर्ण

अटल पूर्णांक ath10k_hw_scan(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	काष्ठा wmi_start_scan_arg arg;
	पूर्णांक ret = 0;
	पूर्णांक i;
	u32 scan_समयout;

	mutex_lock(&ar->conf_mutex);

	अगर (ath10k_mac_tdls_vअगर_stations_count(hw, vअगर) > 0) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
		reinit_completion(&ar->scan.started);
		reinit_completion(&ar->scan.completed);
		ar->scan.state = ATH10K_SCAN_STARTING;
		ar->scan.is_roc = false;
		ar->scan.vdev_id = arvअगर->vdev_id;
		ret = 0;
		अवरोध;
	हाल ATH10K_SCAN_STARTING:
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		ret = -EBUSY;
		अवरोध;
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	अगर (ret)
		जाओ निकास;

	स_रखो(&arg, 0, माप(arg));
	ath10k_wmi_start_scan_init(ar, &arg);
	arg.vdev_id = arvअगर->vdev_id;
	arg.scan_id = ATH10K_SCAN_ID;

	अगर (req->ie_len) अणु
		arg.ie_len = req->ie_len;
		स_नकल(arg.ie, req->ie, arg.ie_len);
	पूर्ण

	अगर (req->n_ssids) अणु
		arg.n_ssids = req->n_ssids;
		क्रम (i = 0; i < arg.n_ssids; i++) अणु
			arg.ssids[i].len  = req->ssids[i].ssid_len;
			arg.ssids[i].ssid = req->ssids[i].ssid;
		पूर्ण
	पूर्ण अन्यथा अणु
		arg.scan_ctrl_flags |= WMI_SCAN_FLAG_PASSIVE;
	पूर्ण

	अगर (req->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) अणु
		arg.scan_ctrl_flags |=  WMI_SCAN_ADD_SPOOFED_MAC_IN_PROBE_REQ;
		ether_addr_copy(arg.mac_addr.addr, req->mac_addr);
		ether_addr_copy(arg.mac_mask.addr, req->mac_addr_mask);
	पूर्ण

	अगर (req->n_channels) अणु
		arg.n_channels = req->n_channels;
		क्रम (i = 0; i < arg.n_channels; i++)
			arg.channels[i] = req->channels[i]->center_freq;
	पूर्ण

	/* अगर duration is set, शेष dwell बार will be overwritten */
	अगर (req->duration) अणु
		arg.dwell_समय_active = req->duration;
		arg.dwell_समय_passive = req->duration;
		arg.burst_duration_ms = req->duration;

		scan_समयout = min_t(u32, arg.max_rest_समय *
				(arg.n_channels - 1) + (req->duration +
				ATH10K_SCAN_CHANNEL_SWITCH_WMI_EVT_OVERHEAD) *
				arg.n_channels, arg.max_scan_समय + 200);

	पूर्ण अन्यथा अणु
		/* Add a 200ms margin to account क्रम event/command processing */
		scan_समयout = arg.max_scan_समय + 200;
	पूर्ण

	ret = ath10k_start_scan(ar, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to start hw scan: %d\n", ret);
		spin_lock_bh(&ar->data_lock);
		ar->scan.state = ATH10K_SCAN_IDLE;
		spin_unlock_bh(&ar->data_lock);
	पूर्ण

	ieee80211_queue_delayed_work(ar->hw, &ar->scan.समयout,
				     msecs_to_jअगरfies(scan_समयout));

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम ath10k_cancel_hw_scan(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);
	ath10k_scan_पात(ar);
	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.समयout);
पूर्ण

अटल व्योम ath10k_set_key_h_def_keyidx(काष्ठा ath10k *ar,
					काष्ठा ath10k_vअगर *arvअगर,
					क्रमागत set_key_cmd cmd,
					काष्ठा ieee80211_key_conf *key)
अणु
	u32 vdev_param = arvअगर->ar->wmi.vdev_param->def_keyid;
	पूर्णांक ret;

	/* 10.1 firmware branch requires शेष key index to be set to group
	 * key index after installing it. Otherwise FW/HW Txes corrupted
	 * frames with multi-vअगर APs. This is not required क्रम मुख्य firmware
	 * branch (e.g. 636).
	 *
	 * This is also needed क्रम 636 fw क्रम IBSS-RSN to work more reliably.
	 *
	 * FIXME: It reमुख्यs unknown अगर this is required क्रम multi-vअगर STA
	 * पूर्णांकerfaces on 10.1.
	 */

	अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_AP &&
	    arvअगर->vdev_type != WMI_VDEV_TYPE_IBSS)
		वापस;

	अगर (key->cipher == WLAN_CIPHER_SUITE_WEP40)
		वापस;

	अगर (key->cipher == WLAN_CIPHER_SUITE_WEP104)
		वापस;

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		वापस;

	अगर (cmd != SET_KEY)
		वापस;

	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param,
					key->keyidx);
	अगर (ret)
		ath10k_warn(ar, "failed to set vdev %i group key as default key: %d\n",
			    arvअगर->vdev_id, ret);
पूर्ण

अटल पूर्णांक ath10k_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			  काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_sta *arsta;
	काष्ठा ath10k_peer *peer;
	स्थिर u8 *peer_addr;
	bool is_wep = key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
		      key->cipher == WLAN_CIPHER_SUITE_WEP104;
	पूर्णांक ret = 0;
	पूर्णांक ret2;
	u32 flags = 0;
	u32 flags2;

	/* this one needs to be करोne in software */
	अगर (key->cipher == WLAN_CIPHER_SUITE_AES_CMAC ||
	    key->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_128 ||
	    key->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_256 ||
	    key->cipher == WLAN_CIPHER_SUITE_BIP_CMAC_256)
		वापस 1;

	अगर (arvअगर->nohwcrypt)
		वापस 1;

	अगर (key->keyidx > WMI_MAX_KEY_INDEX)
		वापस -ENOSPC;

	mutex_lock(&ar->conf_mutex);

	अगर (sta) अणु
		arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
		peer_addr = sta->addr;
		spin_lock_bh(&ar->data_lock);
		arsta->ucast_cipher = key->cipher;
		spin_unlock_bh(&ar->data_lock);
	पूर्ण अन्यथा अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_STA) अणु
		peer_addr = vअगर->bss_conf.bssid;
	पूर्ण अन्यथा अणु
		peer_addr = vअगर->addr;
	पूर्ण

	key->hw_key_idx = key->keyidx;

	अगर (is_wep) अणु
		अगर (cmd == SET_KEY)
			arvअगर->wep_keys[key->keyidx] = key;
		अन्यथा
			arvअगर->wep_keys[key->keyidx] = शून्य;
	पूर्ण

	/* the peer should not disappear in mid-way (unless FW goes awry) since
	 * we alपढ़ोy hold conf_mutex. we just make sure its there now.
	 */
	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, arvअगर->vdev_id, peer_addr);
	spin_unlock_bh(&ar->data_lock);

	अगर (!peer) अणु
		अगर (cmd == SET_KEY) अणु
			ath10k_warn(ar, "failed to install key for non-existent peer %pM\n",
				    peer_addr);
			ret = -EOPNOTSUPP;
			जाओ निकास;
		पूर्ण अन्यथा अणु
			/* अगर the peer करोesn't exist there is no key to disable anymore */
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		flags |= WMI_KEY_PAIRWISE;
	अन्यथा
		flags |= WMI_KEY_GROUP;

	अगर (is_wep) अणु
		अगर (cmd == DISABLE_KEY)
			ath10k_clear_vdev_key(arvअगर, key);

		/* When WEP keys are uploaded it's possible that there are
		 * stations associated alपढ़ोy (e.g. when merging) without any
		 * keys. Static WEP needs an explicit per-peer key upload.
		 */
		अगर (vअगर->type == NL80211_IFTYPE_ADHOC &&
		    cmd == SET_KEY)
			ath10k_mac_vअगर_update_wep_key(arvअगर, key);

		/* 802.1x never sets the def_wep_key_idx so each set_key()
		 * call changes शेष tx key.
		 *
		 * Static WEP sets def_wep_key_idx via .set_शेष_unicast_key
		 * after first set_key().
		 */
		अगर (cmd == SET_KEY && arvअगर->def_wep_key_idx == -1)
			flags |= WMI_KEY_TX_USAGE;
	पूर्ण

	ret = ath10k_install_key(arvअगर, key, cmd, peer_addr, flags);
	अगर (ret) अणु
		WARN_ON(ret > 0);
		ath10k_warn(ar, "failed to install key for vdev %i peer %pM: %d\n",
			    arvअगर->vdev_id, peer_addr, ret);
		जाओ निकास;
	पूर्ण

	/* mac80211 sets अटल WEP keys as groupwise जबतक firmware requires
	 * them to be installed twice as both pairwise and groupwise.
	 */
	अगर (is_wep && !sta && vअगर->type == NL80211_IFTYPE_STATION) अणु
		flags2 = flags;
		flags2 &= ~WMI_KEY_GROUP;
		flags2 |= WMI_KEY_PAIRWISE;

		ret = ath10k_install_key(arvअगर, key, cmd, peer_addr, flags2);
		अगर (ret) अणु
			WARN_ON(ret > 0);
			ath10k_warn(ar, "failed to install (ucast) key for vdev %i peer %pM: %d\n",
				    arvअगर->vdev_id, peer_addr, ret);
			ret2 = ath10k_install_key(arvअगर, key, DISABLE_KEY,
						  peer_addr, flags);
			अगर (ret2) अणु
				WARN_ON(ret2 > 0);
				ath10k_warn(ar, "failed to disable (mcast) key for vdev %i peer %pM: %d\n",
					    arvअगर->vdev_id, peer_addr, ret2);
			पूर्ण
			जाओ निकास;
		पूर्ण
	पूर्ण

	ath10k_set_key_h_def_keyidx(ar, arvअगर, cmd, key);

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, arvअगर->vdev_id, peer_addr);
	अगर (peer && cmd == SET_KEY)
		peer->keys[key->keyidx] = key;
	अन्यथा अगर (peer && cmd == DISABLE_KEY)
		peer->keys[key->keyidx] = शून्य;
	अन्यथा अगर (peer == शून्य)
		/* impossible unless FW goes crazy */
		ath10k_warn(ar, "Peer %pM disappeared!\n", peer_addr);
	spin_unlock_bh(&ar->data_lock);

	अगर (sta && sta->tdls)
		ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, sta->addr,
					  ar->wmi.peer_param->authorize, 1);
	अन्यथा अगर (sta && cmd == SET_KEY && (key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, peer_addr,
					  ar->wmi.peer_param->authorize, 1);

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम ath10k_set_शेष_unicast_key(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर,
					   पूर्णांक keyidx)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;

	mutex_lock(&arvअगर->ar->conf_mutex);

	अगर (arvअगर->ar->state != ATH10K_STATE_ON)
		जाओ unlock;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d set keyidx %d\n",
		   arvअगर->vdev_id, keyidx);

	ret = ath10k_wmi_vdev_set_param(arvअगर->ar,
					arvअगर->vdev_id,
					arvअगर->ar->wmi.vdev_param->def_keyid,
					keyidx);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to update wep key index for vdev %d: %d\n",
			    arvअगर->vdev_id,
			    ret);
		जाओ unlock;
	पूर्ण

	arvअगर->def_wep_key_idx = keyidx;

unlock:
	mutex_unlock(&arvअगर->ar->conf_mutex);
पूर्ण

अटल व्योम ath10k_sta_rc_update_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा ath10k *ar;
	काष्ठा ath10k_vअगर *arvअगर;
	काष्ठा ath10k_sta *arsta;
	काष्ठा ieee80211_sta *sta;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	स्थिर u8 *ht_mcs_mask;
	स्थिर u16 *vht_mcs_mask;
	u32 changed, bw, nss, smps;
	पूर्णांक err;

	arsta = container_of(wk, काष्ठा ath10k_sta, update_wk);
	sta = container_of((व्योम *)arsta, काष्ठा ieee80211_sta, drv_priv);
	arvअगर = arsta->arvअगर;
	ar = arvअगर->ar;

	अगर (WARN_ON(ath10k_mac_vअगर_chan(arvअगर->vअगर, &def)))
		वापस;

	band = def.chan->band;
	ht_mcs_mask = arvअगर->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvअगर->bitrate_mask.control[band].vht_mcs;

	spin_lock_bh(&ar->data_lock);

	changed = arsta->changed;
	arsta->changed = 0;

	bw = arsta->bw;
	nss = arsta->nss;
	smps = arsta->smps;

	spin_unlock_bh(&ar->data_lock);

	mutex_lock(&ar->conf_mutex);

	nss = max_t(u32, 1, nss);
	nss = min(nss, max(ath10k_mac_max_ht_nss(ht_mcs_mask),
			   ath10k_mac_max_vht_nss(vht_mcs_mask)));

	अगर (changed & IEEE80211_RC_BW_CHANGED) अणु
		क्रमागत wmi_phy_mode mode;

		mode = chan_to_phymode(&def);
		ath10k_dbg(ar, ATH10K_DBG_STA, "mac update sta %pM peer bw %d phymode %d\n",
			   sta->addr, bw, mode);

		err = ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, sta->addr,
						ar->wmi.peer_param->phymode, mode);
		अगर (err) अणु
			ath10k_warn(ar, "failed to update STA %pM peer phymode %d: %d\n",
				    sta->addr, mode, err);
			जाओ निकास;
		पूर्ण

		err = ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, sta->addr,
						ar->wmi.peer_param->chan_width, bw);
		अगर (err)
			ath10k_warn(ar, "failed to update STA %pM peer bw %d: %d\n",
				    sta->addr, bw, err);
	पूर्ण

	अगर (changed & IEEE80211_RC_NSS_CHANGED) अणु
		ath10k_dbg(ar, ATH10K_DBG_STA, "mac update sta %pM nss %d\n",
			   sta->addr, nss);

		err = ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, sta->addr,
						ar->wmi.peer_param->nss, nss);
		अगर (err)
			ath10k_warn(ar, "failed to update STA %pM nss %d: %d\n",
				    sta->addr, nss, err);
	पूर्ण

	अगर (changed & IEEE80211_RC_SMPS_CHANGED) अणु
		ath10k_dbg(ar, ATH10K_DBG_STA, "mac update sta %pM smps %d\n",
			   sta->addr, smps);

		err = ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, sta->addr,
						ar->wmi.peer_param->smps_state, smps);
		अगर (err)
			ath10k_warn(ar, "failed to update STA %pM smps %d: %d\n",
				    sta->addr, smps, err);
	पूर्ण

	अगर (changed & IEEE80211_RC_SUPP_RATES_CHANGED) अणु
		ath10k_dbg(ar, ATH10K_DBG_STA, "mac update sta %pM supp rates\n",
			   sta->addr);

		err = ath10k_station_assoc(ar, arvअगर->vअगर, sta, true);
		अगर (err)
			ath10k_warn(ar, "failed to reassociate station: %pM\n",
				    sta->addr);
	पूर्ण

निकास:
	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक ath10k_mac_inc_num_stations(काष्ठा ath10k_vअगर *arvअगर,
				       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_STA && !sta->tdls)
		वापस 0;

	अगर (ar->num_stations >= ar->max_num_stations)
		वापस -ENOBUFS;

	ar->num_stations++;

	वापस 0;
पूर्ण

अटल व्योम ath10k_mac_dec_num_stations(काष्ठा ath10k_vअगर *arvअगर,
					काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_STA && !sta->tdls)
		वापस;

	ar->num_stations--;
पूर्ण

अटल पूर्णांक ath10k_sta_set_txpwr(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret = 0;
	s16 txpwr;

	अगर (sta->txpwr.type == NL80211_TX_POWER_AUTOMATIC) अणु
		txpwr = 0;
	पूर्ण अन्यथा अणु
		txpwr = sta->txpwr.घातer;
		अगर (!txpwr)
			वापस -EINVAL;
	पूर्ण

	अगर (txpwr > ATH10K_TX_POWER_MAX_VAL || txpwr < ATH10K_TX_POWER_MIN_VAL)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	ret = ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, sta->addr,
					ar->wmi.peer_param->use_fixed_घातer, txpwr);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set tx power for station ret: %d\n",
			    ret);
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

काष्ठा ath10k_mac_iter_tid_conf_data अणु
	काष्ठा ieee80211_vअगर *curr_vअगर;
	काष्ठा ath10k *ar;
	bool reset_config;
पूर्ण;

अटल bool
ath10k_mac_bitrate_mask_has_single_rate(काष्ठा ath10k *ar,
					क्रमागत nl80211_band band,
					स्थिर काष्ठा cfg80211_bitrate_mask *mask,
					पूर्णांक *vht_num_rates)
अणु
	पूर्णांक num_rates = 0;
	पूर्णांक i, पंचांगp;

	num_rates += hweight32(mask->control[band].legacy);

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++)
		num_rates += hweight8(mask->control[band].ht_mcs[i]);

	*vht_num_rates = 0;
	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) अणु
		पंचांगp = hweight16(mask->control[band].vht_mcs[i]);
		num_rates += पंचांगp;
		*vht_num_rates += पंचांगp;
	पूर्ण

	वापस num_rates == 1;
पूर्ण

अटल पूर्णांक
ath10k_mac_bitrate_mask_get_single_rate(काष्ठा ath10k *ar,
					क्रमागत nl80211_band band,
					स्थिर काष्ठा cfg80211_bitrate_mask *mask,
					u8 *rate, u8 *nss, bool vht_only)
अणु
	पूर्णांक rate_idx;
	पूर्णांक i;
	u16 bitrate;
	u8 preamble;
	u8 hw_rate;

	अगर (vht_only)
		जाओ next;

	अगर (hweight32(mask->control[band].legacy) == 1) अणु
		rate_idx = ffs(mask->control[band].legacy) - 1;

		अगर (ar->phy_capability & WHAL_WLAN_11A_CAPABILITY)
			rate_idx += ATH10K_MAC_FIRST_OFDM_RATE_IDX;

		hw_rate = ath10k_wmi_legacy_rates[rate_idx].hw_value;
		bitrate = ath10k_wmi_legacy_rates[rate_idx].bitrate;

		अगर (ath10k_mac_bitrate_is_cck(bitrate))
			preamble = WMI_RATE_PREAMBLE_CCK;
		अन्यथा
			preamble = WMI_RATE_PREAMBLE_OFDM;

		*nss = 1;
		*rate = preamble << 6 |
			(*nss - 1) << 4 |
			hw_rate << 0;

		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++) अणु
		अगर (hweight8(mask->control[band].ht_mcs[i]) == 1) अणु
			*nss = i + 1;
			*rate = WMI_RATE_PREAMBLE_HT << 6 |
				(*nss - 1) << 4 |
				(ffs(mask->control[band].ht_mcs[i]) - 1);

			वापस 0;
		पूर्ण
	पूर्ण

next:
	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) अणु
		अगर (hweight16(mask->control[band].vht_mcs[i]) == 1) अणु
			*nss = i + 1;
			*rate = WMI_RATE_PREAMBLE_VHT << 6 |
				(*nss - 1) << 4 |
				(ffs(mask->control[band].vht_mcs[i]) - 1);

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ath10k_mac_validate_rate_mask(काष्ठा ath10k *ar,
					 काष्ठा ieee80211_sta *sta,
					 u32 rate_ctrl_flag, u8 nss)
अणु
	अगर (nss > sta->rx_nss) अणु
		ath10k_warn(ar, "Invalid nss field, configured %u limit %u\n",
			    nss, sta->rx_nss);
		वापस -EINVAL;
	पूर्ण

	अगर (ATH10K_HW_PREAMBLE(rate_ctrl_flag) == WMI_RATE_PREAMBLE_VHT) अणु
		अगर (!sta->vht_cap.vht_supported) अणु
			ath10k_warn(ar, "Invalid VHT rate for sta %pM\n",
				    sta->addr);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (ATH10K_HW_PREAMBLE(rate_ctrl_flag) == WMI_RATE_PREAMBLE_HT) अणु
		अगर (!sta->ht_cap.ht_supported || sta->vht_cap.vht_supported) अणु
			ath10k_warn(ar, "Invalid HT rate for sta %pM\n",
				    sta->addr);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (sta->ht_cap.ht_supported || sta->vht_cap.vht_supported)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_mac_tid_bitrate_config(काष्ठा ath10k *ar,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta,
			      u32 *rate_ctrl_flag, u8 *rate_ctrl,
			      क्रमागत nl80211_tx_rate_setting txrate_type,
			      स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	u8 nss, rate;
	पूर्णांक vht_num_rates, ret;

	अगर (WARN_ON(ath10k_mac_vअगर_chan(vअगर, &def)))
		वापस -EINVAL;

	अगर (txrate_type == NL80211_TX_RATE_AUTOMATIC) अणु
		*rate_ctrl = WMI_TID_CONFIG_RATE_CONTROL_AUTO;
		*rate_ctrl_flag = 0;
		वापस 0;
	पूर्ण

	band = def.chan->band;

	अगर (!ath10k_mac_bitrate_mask_has_single_rate(ar, band, mask,
						     &vht_num_rates)) अणु
		वापस -EINVAL;
	पूर्ण

	ret = ath10k_mac_bitrate_mask_get_single_rate(ar, band, mask,
						      &rate, &nss, false);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to get single rate: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	*rate_ctrl_flag = rate;

	अगर (sta && ath10k_mac_validate_rate_mask(ar, sta, *rate_ctrl_flag, nss))
		वापस -EINVAL;

	अगर (txrate_type == NL80211_TX_RATE_FIXED)
		*rate_ctrl = WMI_TID_CONFIG_RATE_CONTROL_FIXED_RATE;
	अन्यथा अगर (txrate_type == NL80211_TX_RATE_LIMITED &&
		 (test_bit(WMI_SERVICE_EXT_PEER_TID_CONFIGS_SUPPORT,
			   ar->wmi.svc_map)))
		*rate_ctrl = WMI_PEER_TID_CONFIG_RATE_UPPER_CAP;
	अन्यथा
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_set_tid_config(काष्ठा ath10k *ar, काष्ठा ieee80211_sta *sta,
				     काष्ठा ieee80211_vअगर *vअगर, u32 changed,
				     काष्ठा wmi_per_peer_per_tid_cfg_arg *arg)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_sta *arsta;
	पूर्णांक ret;

	अगर (sta) अणु
		अगर (!sta->wme)
			वापस -ENOTSUPP;

		arsta = (काष्ठा ath10k_sta *)sta->drv_priv;

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_NOACK)) अणु
			अगर ((arsta->retry_दीर्घ[arg->tid] > 0 ||
			     arsta->rate_code[arg->tid] > 0 ||
			     arsta->ampdu[arg->tid] ==
					WMI_TID_CONFIG_AGGR_CONTROL_ENABLE) &&
			     arg->ack_policy == WMI_PEER_TID_CONFIG_NOACK) अणु
				changed &= ~BIT(NL80211_TID_CONFIG_ATTR_NOACK);
				arg->ack_policy = 0;
				arg->aggr_control = 0;
				arg->rate_ctrl = 0;
				arg->rcode_flags = 0;
			पूर्ण
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_AMPDU_CTRL)) अणु
			अगर (arsta->noack[arg->tid] == WMI_PEER_TID_CONFIG_NOACK ||
			    arvअगर->noack[arg->tid] == WMI_PEER_TID_CONFIG_NOACK) अणु
				arg->aggr_control = 0;
				changed &= ~BIT(NL80211_TID_CONFIG_ATTR_RETRY_LONG);
			पूर्ण
		पूर्ण

		अगर (changed & (BIT(NL80211_TID_CONFIG_ATTR_TX_RATE) |
		    BIT(NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE))) अणु
			अगर (arsta->noack[arg->tid] == WMI_PEER_TID_CONFIG_NOACK ||
			    arvअगर->noack[arg->tid] == WMI_PEER_TID_CONFIG_NOACK) अणु
				arg->rate_ctrl = 0;
				arg->rcode_flags = 0;
			पूर्ण
		पूर्ण

		ether_addr_copy(arg->peer_macaddr.addr, sta->addr);

		ret = ath10k_wmi_set_per_peer_per_tid_cfg(ar, arg);
		अगर (ret)
			वापस ret;

		/* Store the configured parameters in success हाल */
		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_NOACK)) अणु
			arsta->noack[arg->tid] = arg->ack_policy;
			arg->ack_policy = 0;
			arg->aggr_control = 0;
			arg->rate_ctrl = 0;
			arg->rcode_flags = 0;
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_RETRY_LONG)) अणु
			arsta->retry_दीर्घ[arg->tid] = arg->retry_count;
			arg->retry_count = 0;
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_AMPDU_CTRL)) अणु
			arsta->ampdu[arg->tid] = arg->aggr_control;
			arg->aggr_control = 0;
		पूर्ण

		अगर (changed & (BIT(NL80211_TID_CONFIG_ATTR_TX_RATE) |
		    BIT(NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE))) अणु
			arsta->rate_ctrl[arg->tid] = arg->rate_ctrl;
			arg->rate_ctrl = 0;
			arg->rcode_flags = 0;
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL)) अणु
			arsta->rtscts[arg->tid] = arg->rtscts_ctrl;
			arg->ext_tid_cfg_biपंचांगap = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_NOACK)) अणु
			अगर ((arvअगर->retry_दीर्घ[arg->tid] ||
			     arvअगर->rate_code[arg->tid] ||
			     arvअगर->ampdu[arg->tid] ==
					WMI_TID_CONFIG_AGGR_CONTROL_ENABLE) &&
			     arg->ack_policy == WMI_PEER_TID_CONFIG_NOACK) अणु
				changed &= ~BIT(NL80211_TID_CONFIG_ATTR_NOACK);
			पूर्ण अन्यथा अणु
				arvअगर->noack[arg->tid] = arg->ack_policy;
				arvअगर->ampdu[arg->tid] = arg->aggr_control;
				arvअगर->rate_ctrl[arg->tid] = arg->rate_ctrl;
			पूर्ण
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_RETRY_LONG)) अणु
			अगर (arvअगर->noack[arg->tid] == WMI_PEER_TID_CONFIG_NOACK)
				changed &= ~BIT(NL80211_TID_CONFIG_ATTR_RETRY_LONG);
			अन्यथा
				arvअगर->retry_दीर्घ[arg->tid] = arg->retry_count;
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_AMPDU_CTRL)) अणु
			अगर (arvअगर->noack[arg->tid] == WMI_PEER_TID_CONFIG_NOACK)
				changed &= ~BIT(NL80211_TID_CONFIG_ATTR_AMPDU_CTRL);
			अन्यथा
				arvअगर->ampdu[arg->tid] = arg->aggr_control;
		पूर्ण

		अगर (changed & (BIT(NL80211_TID_CONFIG_ATTR_TX_RATE) |
		    BIT(NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE))) अणु
			अगर (arvअगर->noack[arg->tid] == WMI_PEER_TID_CONFIG_NOACK) अणु
				changed &= ~(BIT(NL80211_TID_CONFIG_ATTR_TX_RATE) |
					     BIT(NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE));
			पूर्ण अन्यथा अणु
				arvअगर->rate_ctrl[arg->tid] = arg->rate_ctrl;
				arvअगर->rate_code[arg->tid] = arg->rcode_flags;
			पूर्ण
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL)) अणु
			arvअगर->rtscts[arg->tid] = arg->rtscts_ctrl;
			arg->ext_tid_cfg_biपंचांगap = 0;
		पूर्ण

		अगर (changed)
			arvअगर->tid_conf_changed[arg->tid] |= changed;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_mac_parse_tid_config(काष्ठा ath10k *ar,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा cfg80211_tid_cfg *tid_conf,
			    काष्ठा wmi_per_peer_per_tid_cfg_arg *arg)
अणु
	u32 changed = tid_conf->mask;
	पूर्णांक ret = 0, i = 0;

	अगर (!changed)
		वापस -EINVAL;

	जबतक (i < ATH10K_TID_MAX) अणु
		अगर (!(tid_conf->tids & BIT(i))) अणु
			i++;
			जारी;
		पूर्ण

		arg->tid = i;

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_NOACK)) अणु
			अगर (tid_conf->noack == NL80211_TID_CONFIG_ENABLE) अणु
				arg->ack_policy = WMI_PEER_TID_CONFIG_NOACK;
				arg->rate_ctrl =
				WMI_TID_CONFIG_RATE_CONTROL_DEFAULT_LOWEST_RATE;
				arg->aggr_control =
					WMI_TID_CONFIG_AGGR_CONTROL_DISABLE;
			पूर्ण अन्यथा अणु
				arg->ack_policy =
					WMI_PEER_TID_CONFIG_ACK;
				arg->rate_ctrl =
					WMI_TID_CONFIG_RATE_CONTROL_AUTO;
				arg->aggr_control =
					WMI_TID_CONFIG_AGGR_CONTROL_ENABLE;
			पूर्ण
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_RETRY_LONG))
			arg->retry_count = tid_conf->retry_दीर्घ;

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_AMPDU_CTRL)) अणु
			अगर (tid_conf->noack == NL80211_TID_CONFIG_ENABLE)
				arg->aggr_control = WMI_TID_CONFIG_AGGR_CONTROL_ENABLE;
			अन्यथा
				arg->aggr_control = WMI_TID_CONFIG_AGGR_CONTROL_DISABLE;
		पूर्ण

		अगर (changed & (BIT(NL80211_TID_CONFIG_ATTR_TX_RATE) |
		    BIT(NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE))) अणु
			ret = ath10k_mac_tid_bitrate_config(ar, vअगर, sta,
							    &arg->rcode_flags,
							    &arg->rate_ctrl,
							    tid_conf->txrate_type,
							&tid_conf->txrate_mask);
			अगर (ret) अणु
				ath10k_warn(ar, "failed to configure bitrate mask %d\n",
					    ret);
				arg->rcode_flags = 0;
				arg->rate_ctrl = 0;
			पूर्ण
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL)) अणु
			अगर (tid_conf->rtscts)
				arg->rtscts_ctrl = tid_conf->rtscts;

			arg->ext_tid_cfg_biपंचांगap = WMI_EXT_TID_RTS_CTS_CONFIG;
		पूर्ण

		ret = ath10k_mac_set_tid_config(ar, sta, vअगर, changed, arg);
		अगर (ret)
			वापस ret;
		i++;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_mac_reset_tid_config(काष्ठा ath10k *ar,
				       काष्ठा ieee80211_sta *sta,
				       काष्ठा ath10k_vअगर *arvअगर,
				       u8 tids)
अणु
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा wmi_per_peer_per_tid_cfg_arg arg;
	पूर्णांक ret = 0, i = 0;

	arg.vdev_id = arvअगर->vdev_id;
	जबतक (i < ATH10K_TID_MAX) अणु
		अगर (!(tids & BIT(i))) अणु
			i++;
			जारी;
		पूर्ण

		arg.tid = i;
		arg.ack_policy = WMI_PEER_TID_CONFIG_ACK;
		arg.retry_count = ATH10K_MAX_RETRY_COUNT;
		arg.rate_ctrl = WMI_TID_CONFIG_RATE_CONTROL_AUTO;
		arg.aggr_control = WMI_TID_CONFIG_AGGR_CONTROL_ENABLE;
		arg.rtscts_ctrl = WMI_TID_CONFIG_RTSCTS_CONTROL_ENABLE;
		arg.ext_tid_cfg_biपंचांगap = WMI_EXT_TID_RTS_CTS_CONFIG;

		ether_addr_copy(arg.peer_macaddr.addr, sta->addr);

		ret = ath10k_wmi_set_per_peer_per_tid_cfg(ar, &arg);
		अगर (ret)
			वापस ret;

		अगर (!arvअगर->tids_rst) अणु
			arsta->retry_दीर्घ[i] = -1;
			arsta->noack[i] = -1;
			arsta->ampdu[i] = -1;
			arsta->rate_code[i] = -1;
			arsta->rate_ctrl[i] = 0;
			arsta->rtscts[i] = -1;
		पूर्ण अन्यथा अणु
			arvअगर->retry_दीर्घ[i] = 0;
			arvअगर->noack[i] = 0;
			arvअगर->ampdu[i] = 0;
			arvअगर->rate_code[i] = 0;
			arvअगर->rate_ctrl[i] = 0;
			arvअगर->rtscts[i] = 0;
		पूर्ण

		i++;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ath10k_sta_tid_cfg_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा wmi_per_peer_per_tid_cfg_arg arg = अणुपूर्ण;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath10k_sta *arsta;
	काष्ठा ath10k_vअगर *arvअगर;
	काष्ठा ath10k *ar;
	bool config_apply;
	पूर्णांक ret, i;
	u32 changed;
	u8 nss;

	arsta = container_of(wk, काष्ठा ath10k_sta, tid_config_wk);
	sta = container_of((व्योम *)arsta, काष्ठा ieee80211_sta, drv_priv);
	arvअगर = arsta->arvअगर;
	ar = arvअगर->ar;

	mutex_lock(&ar->conf_mutex);

	अगर (arvअगर->tids_rst) अणु
		ret = ath10k_mac_reset_tid_config(ar, sta, arvअगर,
						  arvअगर->tids_rst);
		जाओ निकास;
	पूर्ण

	ether_addr_copy(arg.peer_macaddr.addr, sta->addr);

	क्रम (i = 0; i < ATH10K_TID_MAX; i++) अणु
		config_apply = false;
		changed = arvअगर->tid_conf_changed[i];

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_NOACK)) अणु
			अगर (arsta->noack[i] != -1) अणु
				arg.ack_policy  = 0;
			पूर्ण अन्यथा अणु
				config_apply = true;
				arg.ack_policy = arvअगर->noack[i];
				arg.aggr_control = arvअगर->ampdu[i];
				arg.rate_ctrl = arvअगर->rate_ctrl[i];
			पूर्ण
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_RETRY_LONG)) अणु
			अगर (arsta->retry_दीर्घ[i] != -1 ||
			    arsta->noack[i] == WMI_PEER_TID_CONFIG_NOACK ||
			    arvअगर->noack[i] == WMI_PEER_TID_CONFIG_NOACK) अणु
				arg.retry_count = 0;
			पूर्ण अन्यथा अणु
				arg.retry_count = arvअगर->retry_दीर्घ[i];
				config_apply = true;
			पूर्ण
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_AMPDU_CTRL)) अणु
			अगर (arsta->ampdu[i] != -1 ||
			    arsta->noack[i] == WMI_PEER_TID_CONFIG_NOACK ||
			    arvअगर->noack[i] == WMI_PEER_TID_CONFIG_NOACK) अणु
				arg.aggr_control = 0;
			पूर्ण अन्यथा अणु
				arg.aggr_control = arvअगर->ampdu[i];
				config_apply = true;
			पूर्ण
		पूर्ण

		अगर (changed & (BIT(NL80211_TID_CONFIG_ATTR_TX_RATE) |
		    BIT(NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE))) अणु
			nss = ATH10K_HW_NSS(arvअगर->rate_code[i]);
			ret = ath10k_mac_validate_rate_mask(ar, sta,
							    arvअगर->rate_code[i],
							    nss);
			अगर (ret &&
			    arvअगर->rate_ctrl[i] > WMI_TID_CONFIG_RATE_CONTROL_AUTO) अणु
				arg.rate_ctrl = 0;
				arg.rcode_flags = 0;
			पूर्ण

			अगर (arsta->rate_ctrl[i] >
			    WMI_TID_CONFIG_RATE_CONTROL_AUTO ||
			    arsta->noack[i] == WMI_PEER_TID_CONFIG_NOACK ||
			    arvअगर->noack[i] == WMI_PEER_TID_CONFIG_NOACK) अणु
				arg.rate_ctrl = 0;
				arg.rcode_flags = 0;
			पूर्ण अन्यथा अणु
				arg.rate_ctrl = arvअगर->rate_ctrl[i];
				arg.rcode_flags = arvअगर->rate_code[i];
				config_apply = true;
			पूर्ण
		पूर्ण

		अगर (changed & BIT(NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL)) अणु
			अगर (arsta->rtscts[i]) अणु
				arg.rtscts_ctrl = 0;
				arg.ext_tid_cfg_biपंचांगap = 0;
			पूर्ण अन्यथा अणु
				arg.rtscts_ctrl = arvअगर->rtscts[i] - 1;
				arg.ext_tid_cfg_biपंचांगap =
					WMI_EXT_TID_RTS_CTS_CONFIG;
				config_apply = true;
			पूर्ण
		पूर्ण

		arg.tid = i;

		अगर (config_apply) अणु
			ret = ath10k_wmi_set_per_peer_per_tid_cfg(ar, &arg);
			अगर (ret)
				ath10k_warn(ar, "failed to set per tid config for sta %pM: %d\n",
					    sta->addr, ret);
		पूर्ण

		arg.ack_policy  = 0;
		arg.retry_count  = 0;
		arg.aggr_control  = 0;
		arg.rate_ctrl = 0;
		arg.rcode_flags = 0;
	पूर्ण

निकास:
	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल व्योम ath10k_mac_vअगर_stations_tid_conf(व्योम *data,
					     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k_mac_iter_tid_conf_data *iter_data = data;
	काष्ठा ieee80211_vअगर *sta_vअगर = arsta->arvअगर->vअगर;

	अगर (sta_vअगर != iter_data->curr_vअगर || !sta->wme)
		वापस;

	ieee80211_queue_work(iter_data->ar->hw, &arsta->tid_config_wk);
पूर्ण

अटल पूर्णांक ath10k_sta_state(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta,
			    क्रमागत ieee80211_sta_state old_state,
			    क्रमागत ieee80211_sta_state new_state)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k_peer *peer;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) अणु
		स_रखो(arsta, 0, माप(*arsta));
		arsta->arvअगर = arvअगर;
		arsta->peer_ps_state = WMI_PEER_PS_STATE_DISABLED;
		INIT_WORK(&arsta->update_wk, ath10k_sta_rc_update_wk);
		INIT_WORK(&arsta->tid_config_wk, ath10k_sta_tid_cfg_wk);

		क्रम (i = 0; i < ARRAY_SIZE(sta->txq); i++)
			ath10k_mac_txq_init(sta->txq[i]);
	पूर्ण

	/* cancel must be करोne outside the mutex to aव्योम deadlock */
	अगर ((old_state == IEEE80211_STA_NONE &&
	     new_state == IEEE80211_STA_NOTEXIST)) अणु
		cancel_work_sync(&arsta->update_wk);
		cancel_work_sync(&arsta->tid_config_wk);
	पूर्ण

	mutex_lock(&ar->conf_mutex);

	अगर (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) अणु
		/*
		 * New station addition.
		 */
		क्रमागत wmi_peer_type peer_type = WMI_PEER_TYPE_DEFAULT;
		u32 num_tdls_stations;

		ath10k_dbg(ar, ATH10K_DBG_STA,
			   "mac vdev %d peer create %pM (new sta) sta %d / %d peer %d / %d\n",
			   arvअगर->vdev_id, sta->addr,
			   ar->num_stations + 1, ar->max_num_stations,
			   ar->num_peers + 1, ar->max_num_peers);

		num_tdls_stations = ath10k_mac_tdls_vअगर_stations_count(hw, vअगर);

		अगर (sta->tdls) अणु
			अगर (num_tdls_stations >= ar->max_num_tdls_vdevs) अणु
				ath10k_warn(ar, "vdev %i exceeded maximum number of tdls vdevs %i\n",
					    arvअगर->vdev_id,
					    ar->max_num_tdls_vdevs);
				ret = -ELNRNG;
				जाओ निकास;
			पूर्ण
			peer_type = WMI_PEER_TYPE_TDLS;
		पूर्ण

		ret = ath10k_mac_inc_num_stations(arvअगर, sta);
		अगर (ret) अणु
			ath10k_warn(ar, "refusing to associate station: too many connected already (%d)\n",
				    ar->max_num_stations);
			जाओ निकास;
		पूर्ण

		अगर (ath10k_debug_is_extd_tx_stats_enabled(ar)) अणु
			arsta->tx_stats = kzalloc(माप(*arsta->tx_stats),
						  GFP_KERNEL);
			अगर (!arsta->tx_stats) अणु
				ath10k_mac_dec_num_stations(arvअगर, sta);
				ret = -ENOMEM;
				जाओ निकास;
			पूर्ण
		पूर्ण

		ret = ath10k_peer_create(ar, vअगर, sta, arvअगर->vdev_id,
					 sta->addr, peer_type);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to add peer %pM for vdev %d when adding a new sta: %i\n",
				    sta->addr, arvअगर->vdev_id, ret);
			ath10k_mac_dec_num_stations(arvअगर, sta);
			kमुक्त(arsta->tx_stats);
			जाओ निकास;
		पूर्ण

		spin_lock_bh(&ar->data_lock);

		peer = ath10k_peer_find(ar, arvअगर->vdev_id, sta->addr);
		अगर (!peer) अणु
			ath10k_warn(ar, "failed to lookup peer %pM on vdev %i\n",
				    vअगर->addr, arvअगर->vdev_id);
			spin_unlock_bh(&ar->data_lock);
			ath10k_peer_delete(ar, arvअगर->vdev_id, sta->addr);
			ath10k_mac_dec_num_stations(arvअगर, sta);
			kमुक्त(arsta->tx_stats);
			ret = -ENOENT;
			जाओ निकास;
		पूर्ण

		arsta->peer_id = find_first_bit(peer->peer_ids,
						ATH10K_MAX_NUM_PEER_IDS);

		spin_unlock_bh(&ar->data_lock);

		अगर (!sta->tdls)
			जाओ निकास;

		ret = ath10k_wmi_update_fw_tdls_state(ar, arvअगर->vdev_id,
						      WMI_TDLS_ENABLE_ACTIVE);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to update fw tdls state on vdev %i: %i\n",
				    arvअगर->vdev_id, ret);
			ath10k_peer_delete(ar, arvअगर->vdev_id,
					   sta->addr);
			ath10k_mac_dec_num_stations(arvअगर, sta);
			kमुक्त(arsta->tx_stats);
			जाओ निकास;
		पूर्ण

		ret = ath10k_mac_tdls_peer_update(ar, arvअगर->vdev_id, sta,
						  WMI_TDLS_PEER_STATE_PEERING);
		अगर (ret) अणु
			ath10k_warn(ar,
				    "failed to update tdls peer %pM for vdev %d when adding a new sta: %i\n",
				    sta->addr, arvअगर->vdev_id, ret);
			ath10k_peer_delete(ar, arvअगर->vdev_id, sta->addr);
			ath10k_mac_dec_num_stations(arvअगर, sta);
			kमुक्त(arsta->tx_stats);

			अगर (num_tdls_stations != 0)
				जाओ निकास;
			ath10k_wmi_update_fw_tdls_state(ar, arvअगर->vdev_id,
							WMI_TDLS_DISABLE);
		पूर्ण
	पूर्ण अन्यथा अगर ((old_state == IEEE80211_STA_NONE &&
		    new_state == IEEE80211_STA_NOTEXIST)) अणु
		/*
		 * Existing station deletion.
		 */
		ath10k_dbg(ar, ATH10K_DBG_STA,
			   "mac vdev %d peer delete %pM sta %pK (sta gone)\n",
			   arvअगर->vdev_id, sta->addr, sta);

		अगर (sta->tdls) अणु
			ret = ath10k_mac_tdls_peer_update(ar, arvअगर->vdev_id,
							  sta,
							  WMI_TDLS_PEER_STATE_TEARDOWN);
			अगर (ret)
				ath10k_warn(ar, "failed to update tdls peer state for %pM state %d: %i\n",
					    sta->addr,
					    WMI_TDLS_PEER_STATE_TEARDOWN, ret);
		पूर्ण

		ret = ath10k_peer_delete(ar, arvअगर->vdev_id, sta->addr);
		अगर (ret)
			ath10k_warn(ar, "failed to delete peer %pM for vdev %d: %i\n",
				    sta->addr, arvअगर->vdev_id, ret);

		ath10k_mac_dec_num_stations(arvअगर, sta);

		spin_lock_bh(&ar->data_lock);
		क्रम (i = 0; i < ARRAY_SIZE(ar->peer_map); i++) अणु
			peer = ar->peer_map[i];
			अगर (!peer)
				जारी;

			अगर (peer->sta == sta) अणु
				ath10k_warn(ar, "found sta peer %pM (ptr %pK id %d) entry on vdev %i after it was supposedly removed\n",
					    sta->addr, peer, i, arvअगर->vdev_id);
				peer->sta = शून्य;

				/* Clean up the peer object as well since we
				 * must have failed to करो this above.
				 */
				list_del(&peer->list);
				ar->peer_map[i] = शून्य;
				kमुक्त(peer);
				ar->num_peers--;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&ar->data_lock);

		अगर (ath10k_debug_is_extd_tx_stats_enabled(ar)) अणु
			kमुक्त(arsta->tx_stats);
			arsta->tx_stats = शून्य;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(sta->txq); i++)
			ath10k_mac_txq_unref(ar, sta->txq[i]);

		अगर (!sta->tdls)
			जाओ निकास;

		अगर (ath10k_mac_tdls_vअगर_stations_count(hw, vअगर))
			जाओ निकास;

		/* This was the last tdls peer in current vअगर */
		ret = ath10k_wmi_update_fw_tdls_state(ar, arvअगर->vdev_id,
						      WMI_TDLS_DISABLE);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to update fw tdls state on vdev %i: %i\n",
				    arvअगर->vdev_id, ret);
		पूर्ण
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC &&
		   (vअगर->type == NL80211_IFTYPE_AP ||
		    vअगर->type == NL80211_IFTYPE_MESH_POINT ||
		    vअगर->type == NL80211_IFTYPE_ADHOC)) अणु
		/*
		 * New association.
		 */
		ath10k_dbg(ar, ATH10K_DBG_STA, "mac sta %pM associated\n",
			   sta->addr);

		ret = ath10k_station_assoc(ar, vअगर, sta, false);
		अगर (ret)
			ath10k_warn(ar, "failed to associate station %pM for vdev %i: %i\n",
				    sta->addr, arvअगर->vdev_id, ret);
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTHORIZED &&
		   sta->tdls) अणु
		/*
		 * Tdls station authorized.
		 */
		ath10k_dbg(ar, ATH10K_DBG_STA, "mac tdls sta %pM authorized\n",
			   sta->addr);

		ret = ath10k_station_assoc(ar, vअगर, sta, false);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to associate tdls station %pM for vdev %i: %i\n",
				    sta->addr, arvअगर->vdev_id, ret);
			जाओ निकास;
		पूर्ण

		ret = ath10k_mac_tdls_peer_update(ar, arvअगर->vdev_id, sta,
						  WMI_TDLS_PEER_STATE_CONNECTED);
		अगर (ret)
			ath10k_warn(ar, "failed to update tdls peer %pM for vdev %i: %i\n",
				    sta->addr, arvअगर->vdev_id, ret);
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_ASSOC &&
		    new_state == IEEE80211_STA_AUTH &&
		    (vअगर->type == NL80211_IFTYPE_AP ||
		     vअगर->type == NL80211_IFTYPE_MESH_POINT ||
		     vअगर->type == NL80211_IFTYPE_ADHOC)) अणु
		/*
		 * Disassociation.
		 */
		ath10k_dbg(ar, ATH10K_DBG_STA, "mac sta %pM disassociated\n",
			   sta->addr);

		ret = ath10k_station_disassoc(ar, vअगर, sta);
		अगर (ret)
			ath10k_warn(ar, "failed to disassociate station: %pM vdev %i: %i\n",
				    sta->addr, arvअगर->vdev_id, ret);
	पूर्ण
निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_conf_tx_uapsd(काष्ठा ath10k *ar, काष्ठा ieee80211_vअगर *vअगर,
				u16 ac, bool enable)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा wmi_sta_uapsd_स्वतः_trig_arg arg = अणुपूर्ण;
	u32 prio = 0, acc = 0;
	u32 value = 0;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_STA)
		वापस 0;

	चयन (ac) अणु
	हाल IEEE80211_AC_VO:
		value = WMI_STA_PS_UAPSD_AC3_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC3_TRIGGER_EN;
		prio = 7;
		acc = 3;
		अवरोध;
	हाल IEEE80211_AC_VI:
		value = WMI_STA_PS_UAPSD_AC2_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC2_TRIGGER_EN;
		prio = 5;
		acc = 2;
		अवरोध;
	हाल IEEE80211_AC_BE:
		value = WMI_STA_PS_UAPSD_AC1_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC1_TRIGGER_EN;
		prio = 2;
		acc = 1;
		अवरोध;
	हाल IEEE80211_AC_BK:
		value = WMI_STA_PS_UAPSD_AC0_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC0_TRIGGER_EN;
		prio = 0;
		acc = 0;
		अवरोध;
	पूर्ण

	अगर (enable)
		arvअगर->u.sta.uapsd |= value;
	अन्यथा
		arvअगर->u.sta.uapsd &= ~value;

	ret = ath10k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
					  WMI_STA_PS_PARAM_UAPSD,
					  arvअगर->u.sta.uapsd);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set uapsd params: %d\n", ret);
		जाओ निकास;
	पूर्ण

	अगर (arvअगर->u.sta.uapsd)
		value = WMI_STA_PS_RX_WAKE_POLICY_POLL_UAPSD;
	अन्यथा
		value = WMI_STA_PS_RX_WAKE_POLICY_WAKE;

	ret = ath10k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
					  WMI_STA_PS_PARAM_RX_WAKE_POLICY,
					  value);
	अगर (ret)
		ath10k_warn(ar, "failed to set rx wake param: %d\n", ret);

	ret = ath10k_mac_vअगर_recalc_ps_wake_threshold(arvअगर);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to recalc ps wake threshold on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	ret = ath10k_mac_vअगर_recalc_ps_poll_count(arvअगर);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to recalc ps poll count on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_STA_UAPSD_BASIC_AUTO_TRIG, ar->wmi.svc_map) ||
	    test_bit(WMI_SERVICE_STA_UAPSD_VAR_AUTO_TRIG, ar->wmi.svc_map)) अणु
		/* Only userspace can make an educated decision when to send
		 * trigger frame. The following effectively disables u-UAPSD
		 * स्वतःtrigger in firmware (which is enabled by शेष
		 * provided the स्वतःtrigger service is available).
		 */

		arg.wmm_ac = acc;
		arg.user_priority = prio;
		arg.service_पूर्णांकerval = 0;
		arg.suspend_पूर्णांकerval = WMI_STA_UAPSD_MAX_INTERVAL_MSEC;
		arg.delay_पूर्णांकerval = WMI_STA_UAPSD_MAX_INTERVAL_MSEC;

		ret = ath10k_wmi_vdev_sta_uapsd(ar, arvअगर->vdev_id,
						arvअगर->bssid, &arg, 1);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set uapsd auto trigger %d\n",
				    ret);
			वापस ret;
		पूर्ण
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_conf_tx(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर, u16 ac,
			  स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा wmi_wmm_params_arg *p = शून्य;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	चयन (ac) अणु
	हाल IEEE80211_AC_VO:
		p = &arvअगर->wmm_params.ac_vo;
		अवरोध;
	हाल IEEE80211_AC_VI:
		p = &arvअगर->wmm_params.ac_vi;
		अवरोध;
	हाल IEEE80211_AC_BE:
		p = &arvअगर->wmm_params.ac_be;
		अवरोध;
	हाल IEEE80211_AC_BK:
		p = &arvअगर->wmm_params.ac_bk;
		अवरोध;
	पूर्ण

	अगर (WARN_ON(!p)) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	p->cwmin = params->cw_min;
	p->cwmax = params->cw_max;
	p->aअगरs = params->aअगरs;

	/*
	 * The channel समय duration programmed in the HW is in असलolute
	 * microseconds, जबतक mac80211 gives the txop in units of
	 * 32 microseconds.
	 */
	p->txop = params->txop * 32;

	अगर (ar->wmi.ops->gen_vdev_wmm_conf) अणु
		ret = ath10k_wmi_vdev_wmm_conf(ar, arvअगर->vdev_id,
					       &arvअगर->wmm_params);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set vdev wmm params on vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* This won't work well with multi-interface cases but it's
		 * better than nothing.
		 */
		ret = ath10k_wmi_pdev_set_wmm_params(ar, &arvअगर->wmm_params);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set wmm params: %d\n", ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

	ret = ath10k_conf_tx_uapsd(ar, vअगर, ac, params->uapsd);
	अगर (ret)
		ath10k_warn(ar, "failed to set sta uapsd: %d\n", ret);

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_reमुख्य_on_channel(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_channel *chan,
				    पूर्णांक duration,
				    क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा wmi_start_scan_arg arg;
	पूर्णांक ret = 0;
	u32 scan_समय_msec;

	mutex_lock(&ar->conf_mutex);

	अगर (ath10k_mac_tdls_vअगर_stations_count(hw, vअगर) > 0) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	चयन (ar->scan.state) अणु
	हाल ATH10K_SCAN_IDLE:
		reinit_completion(&ar->scan.started);
		reinit_completion(&ar->scan.completed);
		reinit_completion(&ar->scan.on_channel);
		ar->scan.state = ATH10K_SCAN_STARTING;
		ar->scan.is_roc = true;
		ar->scan.vdev_id = arvअगर->vdev_id;
		ar->scan.roc_freq = chan->center_freq;
		ar->scan.roc_notअगरy = true;
		ret = 0;
		अवरोध;
	हाल ATH10K_SCAN_STARTING:
	हाल ATH10K_SCAN_RUNNING:
	हाल ATH10K_SCAN_ABORTING:
		ret = -EBUSY;
		अवरोध;
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	अगर (ret)
		जाओ निकास;

	scan_समय_msec = ar->hw->wiphy->max_reमुख्य_on_channel_duration * 2;

	स_रखो(&arg, 0, माप(arg));
	ath10k_wmi_start_scan_init(ar, &arg);
	arg.vdev_id = arvअगर->vdev_id;
	arg.scan_id = ATH10K_SCAN_ID;
	arg.n_channels = 1;
	arg.channels[0] = chan->center_freq;
	arg.dwell_समय_active = scan_समय_msec;
	arg.dwell_समय_passive = scan_समय_msec;
	arg.max_scan_समय = scan_समय_msec;
	arg.scan_ctrl_flags |= WMI_SCAN_FLAG_PASSIVE;
	arg.scan_ctrl_flags |= WMI_SCAN_FILTER_PROBE_REQ;
	arg.burst_duration_ms = duration;

	ret = ath10k_start_scan(ar, &arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to start roc scan: %d\n", ret);
		spin_lock_bh(&ar->data_lock);
		ar->scan.state = ATH10K_SCAN_IDLE;
		spin_unlock_bh(&ar->data_lock);
		जाओ निकास;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ar->scan.on_channel, 3 * HZ);
	अगर (ret == 0) अणु
		ath10k_warn(ar, "failed to switch to channel for roc scan\n");

		ret = ath10k_scan_stop(ar);
		अगर (ret)
			ath10k_warn(ar, "failed to stop scan: %d\n", ret);

		ret = -ETIMEDOUT;
		जाओ निकास;
	पूर्ण

	ieee80211_queue_delayed_work(ar->hw, &ar->scan.समयout,
				     msecs_to_jअगरfies(duration));

	ret = 0;
निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_cancel_reमुख्य_on_channel(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	ar->scan.roc_notअगरy = false;
	spin_unlock_bh(&ar->data_lock);

	ath10k_scan_पात(ar);

	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.समयout);

	वापस 0;
पूर्ण

/*
 * Both RTS and Fragmentation threshold are पूर्णांकerface-specअगरic
 * in ath10k, but device-specअगरic in mac80211.
 */

अटल पूर्णांक ath10k_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक ret = 0;

	mutex_lock(&ar->conf_mutex);
	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d rts threshold %d\n",
			   arvअगर->vdev_id, value);

		ret = ath10k_mac_set_rts(arvअगर, value);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to set rts threshold for vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_mac_op_set_frag_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	/* Even though there's a WMI क्रमागत क्रम fragmentation threshold no known
	 * firmware actually implements it. Moreover it is not possible to rely
	 * frame fragmentation to mac80211 because firmware clears the "more
	 * fragments" bit in frame control making it impossible क्रम remote
	 * devices to reassemble frames.
	 *
	 * Hence implement a dummy callback just to say fragmentation isn't
	 * supported. This effectively prevents mac80211 from करोing frame
	 * fragmentation in software.
	 */
	वापस -EOPNOTSUPP;
पूर्ण

व्योम ath10k_mac_रुको_tx_complete(काष्ठा ath10k *ar)
अणु
	bool skip;
	दीर्घ समय_left;

	/* mac80211 करोesn't care अगर we really xmit queued frames or not
	 * we'll collect those frames either way अगर we stop/delete vdevs
	 */

	अगर (ar->state == ATH10K_STATE_WEDGED)
		वापस;

	समय_left = रुको_event_समयout(ar->htt.empty_tx_wq, (अणु
			bool empty;

			spin_lock_bh(&ar->htt.tx_lock);
			empty = (ar->htt.num_pending_tx == 0);
			spin_unlock_bh(&ar->htt.tx_lock);

			skip = (ar->state == ATH10K_STATE_WEDGED) ||
			       test_bit(ATH10K_FLAG_CRASH_FLUSH,
					&ar->dev_flags);

			(empty || skip);
		पूर्ण), ATH10K_FLUSH_TIMEOUT_HZ);

	अगर (समय_left == 0 || skip)
		ath10k_warn(ar, "failed to flush transmit queue (skip %i ar-state %i): %ld\n",
			    skip, ar->state, समय_left);
पूर्ण

अटल व्योम ath10k_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 u32 queues, bool drop)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर;
	u32 biपंचांगap;

	अगर (drop) अणु
		अगर (vअगर && vअगर->type == NL80211_IFTYPE_STATION) अणु
			biपंचांगap = ~(1 << WMI_MGMT_TID);
			list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
				अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_STA)
					ath10k_wmi_peer_flush(ar, arvअगर->vdev_id,
							      arvअगर->bssid, biपंचांगap);
			पूर्ण
			ath10k_htt_flush_tx(&ar->htt);
		पूर्ण
		वापस;
	पूर्ण

	mutex_lock(&ar->conf_mutex);
	ath10k_mac_रुको_tx_complete(ar);
	mutex_unlock(&ar->conf_mutex);
पूर्ण

/* TODO: Implement this function properly
 * For now it is needed to reply to Probe Requests in IBSS mode.
 * Propably we need this inक्रमmation from FW.
 */
अटल पूर्णांक ath10k_tx_last_beacon(काष्ठा ieee80211_hw *hw)
अणु
	वापस 1;
पूर्ण

अटल व्योम ath10k_reconfig_complete(काष्ठा ieee80211_hw *hw,
				     क्रमागत ieee80211_reconfig_type reconfig_type)
अणु
	काष्ठा ath10k *ar = hw->priv;

	अगर (reconfig_type != IEEE80211_RECONFIG_TYPE_RESTART)
		वापस;

	mutex_lock(&ar->conf_mutex);

	/* If device failed to restart it will be in a dअगरferent state, e.g.
	 * ATH10K_STATE_WEDGED
	 */
	अगर (ar->state == ATH10K_STATE_RESTARTED) अणु
		ath10k_info(ar, "device successfully recovered\n");
		ar->state = ATH10K_STATE_ON;
		ieee80211_wake_queues(ar->hw);
		clear_bit(ATH10K_FLAG_RESTARTING, &ar->dev_flags);
	पूर्ण

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल व्योम
ath10k_mac_update_bss_chan_survey(काष्ठा ath10k *ar,
				  काष्ठा ieee80211_channel *channel)
अणु
	पूर्णांक ret;
	क्रमागत wmi_bss_survey_req_type type = WMI_BSS_SURVEY_REQ_TYPE_READ;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (!test_bit(WMI_SERVICE_BSS_CHANNEL_INFO_64, ar->wmi.svc_map) ||
	    (ar->rx_channel != channel))
		वापस;

	अगर (ar->scan.state != ATH10K_SCAN_IDLE) अणु
		ath10k_dbg(ar, ATH10K_DBG_MAC, "ignoring bss chan info request while scanning..\n");
		वापस;
	पूर्ण

	reinit_completion(&ar->bss_survey_करोne);

	ret = ath10k_wmi_pdev_bss_chan_info_request(ar, type);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to send pdev bss chan info request\n");
		वापस;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ar->bss_survey_करोne, 3 * HZ);
	अगर (!ret) अणु
		ath10k_warn(ar, "bss channel survey timed out\n");
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक ath10k_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
			     काष्ठा survey_info *survey)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा survey_info *ar_survey = &ar->survey[idx];
	पूर्णांक ret = 0;

	mutex_lock(&ar->conf_mutex);

	sband = hw->wiphy->bands[NL80211_BAND_2GHZ];
	अगर (sband && idx >= sband->n_channels) अणु
		idx -= sband->n_channels;
		sband = शून्य;
	पूर्ण

	अगर (!sband)
		sband = hw->wiphy->bands[NL80211_BAND_5GHZ];

	अगर (!sband || idx >= sband->n_channels) अणु
		ret = -ENOENT;
		जाओ निकास;
	पूर्ण

	ath10k_mac_update_bss_chan_survey(ar, &sband->channels[idx]);

	spin_lock_bh(&ar->data_lock);
	स_नकल(survey, ar_survey, माप(*survey));
	spin_unlock_bh(&ar->data_lock);

	survey->channel = &sband->channels[idx];

	अगर (ar->rx_channel == survey->channel)
		survey->filled |= SURVEY_INFO_IN_USE;

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल bool
ath10k_mac_bitrate_mask_get_single_nss(काष्ठा ath10k *ar,
				       क्रमागत nl80211_band band,
				       स्थिर काष्ठा cfg80211_bitrate_mask *mask,
				       पूर्णांक *nss)
अणु
	काष्ठा ieee80211_supported_band *sband = &ar->mac.sbands[band];
	u16 vht_mcs_map = le16_to_cpu(sband->vht_cap.vht_mcs.tx_mcs_map);
	u8 ht_nss_mask = 0;
	u8 vht_nss_mask = 0;
	पूर्णांक i;

	अगर (mask->control[band].legacy)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++) अणु
		अगर (mask->control[band].ht_mcs[i] == 0)
			जारी;
		अन्यथा अगर (mask->control[band].ht_mcs[i] ==
			 sband->ht_cap.mcs.rx_mask[i])
			ht_nss_mask |= BIT(i);
		अन्यथा
			वापस false;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) अणु
		अगर (mask->control[band].vht_mcs[i] == 0)
			जारी;
		अन्यथा अगर (mask->control[band].vht_mcs[i] ==
			 ath10k_mac_get_max_vht_mcs_map(vht_mcs_map, i))
			vht_nss_mask |= BIT(i);
		अन्यथा
			वापस false;
	पूर्ण

	अगर (ht_nss_mask != vht_nss_mask)
		वापस false;

	अगर (ht_nss_mask == 0)
		वापस false;

	अगर (BIT(fls(ht_nss_mask)) - 1 != ht_nss_mask)
		वापस false;

	*nss = fls(ht_nss_mask);

	वापस true;
पूर्ण

अटल पूर्णांक ath10k_mac_set_fixed_rate_params(काष्ठा ath10k_vअगर *arvअगर,
					    u8 rate, u8 nss, u8 sgi, u8 ldpc)
अणु
	काष्ठा ath10k *ar = arvअगर->ar;
	u32 vdev_param;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac set fixed rate params vdev %i rate 0x%02x nss %u sgi %u\n",
		   arvअगर->vdev_id, rate, nss, sgi);

	vdev_param = ar->wmi.vdev_param->fixed_rate;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param, rate);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set fixed rate param 0x%02x: %d\n",
			    rate, ret);
		वापस ret;
	पूर्ण

	vdev_param = ar->wmi.vdev_param->nss;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param, nss);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set nss param %d: %d\n", nss, ret);
		वापस ret;
	पूर्ण

	vdev_param = ar->wmi.vdev_param->sgi;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param, sgi);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set sgi param %d: %d\n", sgi, ret);
		वापस ret;
	पूर्ण

	vdev_param = ar->wmi.vdev_param->ldpc;
	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id, vdev_param, ldpc);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set ldpc param %d: %d\n", ldpc, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
ath10k_mac_can_set_bitrate_mask(काष्ठा ath10k *ar,
				क्रमागत nl80211_band band,
				स्थिर काष्ठा cfg80211_bitrate_mask *mask,
				bool allow_pfr)
अणु
	पूर्णांक i;
	u16 vht_mcs;

	/* Due to firmware limitation in WMI_PEER_ASSOC_CMDID it is impossible
	 * to express all VHT MCS rate masks. Effectively only the following
	 * ranges can be used: none, 0-7, 0-8 and 0-9.
	 */
	क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++) अणु
		vht_mcs = mask->control[band].vht_mcs[i];

		चयन (vht_mcs) अणु
		हाल 0:
		हाल BIT(8) - 1:
		हाल BIT(9) - 1:
		हाल BIT(10) - 1:
			अवरोध;
		शेष:
			अगर (!allow_pfr)
				ath10k_warn(ar, "refusing bitrate mask with missing 0-7 VHT MCS rates\n");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool ath10k_mac_set_vht_bitrate_mask_fixup(काष्ठा ath10k *ar,
						  काष्ठा ath10k_vअगर *arvअगर,
						  काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक err;
	u8 rate = arvअगर->vht_pfr;

	/* skip non vht and multiple rate peers */
	अगर (!sta->vht_cap.vht_supported || arvअगर->vht_num_rates != 1)
		वापस false;

	err = ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, sta->addr,
					WMI_PEER_PARAM_FIXED_RATE, rate);
	अगर (err)
		ath10k_warn(ar, "failed to enable STA %pM peer fixed rate: %d\n",
			    sta->addr, err);

	वापस true;
पूर्ण

अटल व्योम ath10k_mac_set_bitrate_mask_iter(व्योम *data,
					     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k_vअगर *arvअगर = data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arvअगर->ar;

	अगर (arsta->arvअगर != arvअगर)
		वापस;

	अगर (ath10k_mac_set_vht_bitrate_mask_fixup(ar, arvअगर, sta))
		वापस;

	spin_lock_bh(&ar->data_lock);
	arsta->changed |= IEEE80211_RC_SUPP_RATES_CHANGED;
	spin_unlock_bh(&ar->data_lock);

	ieee80211_queue_work(ar->hw, &arsta->update_wk);
पूर्ण

अटल व्योम ath10k_mac_clr_bitrate_mask_iter(व्योम *data,
					     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k_vअगर *arvअगर = data;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arvअगर->ar;
	पूर्णांक err;

	/* clear vht peers only */
	अगर (arsta->arvअगर != arvअगर || !sta->vht_cap.vht_supported)
		वापस;

	err = ath10k_wmi_peer_set_param(ar, arvअगर->vdev_id, sta->addr,
					WMI_PEER_PARAM_FIXED_RATE,
					WMI_FIXED_RATE_NONE);
	अगर (err)
		ath10k_warn(ar, "failed to clear STA %pM peer fixed rate: %d\n",
			    sta->addr, err);
पूर्ण

अटल पूर्णांक ath10k_mac_op_set_bitrate_mask(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर,
					  स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def def;
	काष्ठा ath10k *ar = arvअगर->ar;
	क्रमागत nl80211_band band;
	स्थिर u8 *ht_mcs_mask;
	स्थिर u16 *vht_mcs_mask;
	u8 rate;
	u8 nss;
	u8 sgi;
	u8 ldpc;
	पूर्णांक single_nss;
	पूर्णांक ret;
	पूर्णांक vht_num_rates, allow_pfr;
	u8 vht_pfr;
	bool update_bitrate_mask = true;

	अगर (ath10k_mac_vअगर_chan(vअगर, &def))
		वापस -EPERM;

	band = def.chan->band;
	ht_mcs_mask = mask->control[band].ht_mcs;
	vht_mcs_mask = mask->control[band].vht_mcs;
	ldpc = !!(ar->ht_cap_info & WMI_HT_CAP_LDPC);

	sgi = mask->control[band].gi;
	अगर (sgi == NL80211_TXRATE_FORCE_LGI)
		वापस -EINVAL;

	allow_pfr = test_bit(ATH10K_FW_FEATURE_PEER_FIXED_RATE,
			     ar->normal_mode_fw.fw_file.fw_features);
	अगर (allow_pfr) अणु
		mutex_lock(&ar->conf_mutex);
		ieee80211_iterate_stations_atomic(ar->hw,
						  ath10k_mac_clr_bitrate_mask_iter,
						  arvअगर);
		mutex_unlock(&ar->conf_mutex);
	पूर्ण

	अगर (ath10k_mac_bitrate_mask_has_single_rate(ar, band, mask,
						    &vht_num_rates)) अणु
		ret = ath10k_mac_bitrate_mask_get_single_rate(ar, band, mask,
							      &rate, &nss,
							      false);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to get single rate for vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (ath10k_mac_bitrate_mask_get_single_nss(ar, band, mask,
							  &single_nss)) अणु
		rate = WMI_FIXED_RATE_NONE;
		nss = single_nss;
	पूर्ण अन्यथा अणु
		rate = WMI_FIXED_RATE_NONE;
		nss = min(ar->num_rf_chains,
			  max(ath10k_mac_max_ht_nss(ht_mcs_mask),
			      ath10k_mac_max_vht_nss(vht_mcs_mask)));

		अगर (!ath10k_mac_can_set_bitrate_mask(ar, band, mask,
						     allow_pfr)) अणु
			u8 vht_nss;

			अगर (!allow_pfr || vht_num_rates != 1)
				वापस -EINVAL;

			/* Reach here, firmware supports peer fixed rate and has
			 * single vht rate, and करोn't update vअगर birate_mask, as
			 * the rate only क्रम specअगरic peer.
			 */
			ath10k_mac_bitrate_mask_get_single_rate(ar, band, mask,
								&vht_pfr,
								&vht_nss,
								true);
			update_bitrate_mask = false;
		पूर्ण अन्यथा अणु
			vht_pfr = 0;
		पूर्ण

		mutex_lock(&ar->conf_mutex);

		अगर (update_bitrate_mask)
			arvअगर->bitrate_mask = *mask;
		arvअगर->vht_num_rates = vht_num_rates;
		arvअगर->vht_pfr = vht_pfr;
		ieee80211_iterate_stations_atomic(ar->hw,
						  ath10k_mac_set_bitrate_mask_iter,
						  arvअगर);

		mutex_unlock(&ar->conf_mutex);
	पूर्ण

	mutex_lock(&ar->conf_mutex);

	ret = ath10k_mac_set_fixed_rate_params(arvअगर, rate, nss, sgi, ldpc);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to set fixed rate params on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ निकास;
	पूर्ण

निकास:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल व्योम ath10k_sta_rc_update(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta,
				 u32 changed)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_peer *peer;
	u32 bw, smps;

	spin_lock_bh(&ar->data_lock);

	peer = ath10k_peer_find(ar, arvअगर->vdev_id, sta->addr);
	अगर (!peer) अणु
		spin_unlock_bh(&ar->data_lock);
		ath10k_warn(ar, "mac sta rc update failed to find peer %pM on vdev %i\n",
			    sta->addr, arvअगर->vdev_id);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_STA,
		   "mac sta rc update for %pM changed %08x bw %d nss %d smps %d\n",
		   sta->addr, changed, sta->bandwidth, sta->rx_nss,
		   sta->smps_mode);

	अगर (changed & IEEE80211_RC_BW_CHANGED) अणु
		bw = WMI_PEER_CHWIDTH_20MHZ;

		चयन (sta->bandwidth) अणु
		हाल IEEE80211_STA_RX_BW_20:
			bw = WMI_PEER_CHWIDTH_20MHZ;
			अवरोध;
		हाल IEEE80211_STA_RX_BW_40:
			bw = WMI_PEER_CHWIDTH_40MHZ;
			अवरोध;
		हाल IEEE80211_STA_RX_BW_80:
			bw = WMI_PEER_CHWIDTH_80MHZ;
			अवरोध;
		हाल IEEE80211_STA_RX_BW_160:
			bw = WMI_PEER_CHWIDTH_160MHZ;
			अवरोध;
		शेष:
			ath10k_warn(ar, "Invalid bandwidth %d in rc update for %pM\n",
				    sta->bandwidth, sta->addr);
			bw = WMI_PEER_CHWIDTH_20MHZ;
			अवरोध;
		पूर्ण

		arsta->bw = bw;
	पूर्ण

	अगर (changed & IEEE80211_RC_NSS_CHANGED)
		arsta->nss = sta->rx_nss;

	अगर (changed & IEEE80211_RC_SMPS_CHANGED) अणु
		smps = WMI_PEER_SMPS_PS_NONE;

		चयन (sta->smps_mode) अणु
		हाल IEEE80211_SMPS_AUTOMATIC:
		हाल IEEE80211_SMPS_OFF:
			smps = WMI_PEER_SMPS_PS_NONE;
			अवरोध;
		हाल IEEE80211_SMPS_STATIC:
			smps = WMI_PEER_SMPS_STATIC;
			अवरोध;
		हाल IEEE80211_SMPS_DYNAMIC:
			smps = WMI_PEER_SMPS_DYNAMIC;
			अवरोध;
		हाल IEEE80211_SMPS_NUM_MODES:
			ath10k_warn(ar, "Invalid smps %d in sta rc update for %pM\n",
				    sta->smps_mode, sta->addr);
			smps = WMI_PEER_SMPS_PS_NONE;
			अवरोध;
		पूर्ण

		arsta->smps = smps;
	पूर्ण

	arsta->changed |= changed;

	spin_unlock_bh(&ar->data_lock);

	ieee80211_queue_work(hw, &arsta->update_wk);
पूर्ण

अटल व्योम ath10k_offset_tsf(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, s64 tsf_offset)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	u32 offset, vdev_param;
	पूर्णांक ret;

	अगर (tsf_offset < 0) अणु
		vdev_param = ar->wmi.vdev_param->dec_tsf;
		offset = -tsf_offset;
	पूर्ण अन्यथा अणु
		vdev_param = ar->wmi.vdev_param->inc_tsf;
		offset = tsf_offset;
	पूर्ण

	ret = ath10k_wmi_vdev_set_param(ar, arvअगर->vdev_id,
					vdev_param, offset);

	अगर (ret && ret != -EOPNOTSUPP)
		ath10k_warn(ar, "failed to set tsf offset %d cmd %d: %d\n",
			    offset, vdev_param, ret);
पूर्ण

अटल पूर्णांक ath10k_ampdu_action(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac ampdu vdev_id %i sta %pM tid %u action %d\n",
		   arvअगर->vdev_id, sta->addr, tid, action);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
	हाल IEEE80211_AMPDU_RX_STOP:
		/* HTT AddBa/DelBa events trigger mac80211 Rx BA session
		 * creation/removal. Do we need to verअगरy this?
		 */
		वापस 0;
	हाल IEEE80211_AMPDU_TX_START:
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		/* Firmware offloads Tx aggregation entirely so deny mac80211
		 * Tx aggregation requests.
		 */
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम
ath10k_mac_update_rx_channel(काष्ठा ath10k *ar,
			     काष्ठा ieee80211_chanctx_conf *ctx,
			     काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
			     पूर्णांक n_vअगरs)
अणु
	काष्ठा cfg80211_chan_def *def = शून्य;

	/* Both locks are required because ar->rx_channel is modअगरied. This
	 * allows पढ़ोers to hold either lock.
	 */
	lockdep_निश्चित_held(&ar->conf_mutex);
	lockdep_निश्चित_held(&ar->data_lock);

	WARN_ON(ctx && vअगरs);
	WARN_ON(vअगरs && !n_vअगरs);

	/* FIXME: Sort of an optimization and a workaround. Peers and vअगरs are
	 * on a linked list now. Doing a lookup peer -> vअगर -> chanctx क्रम each
	 * ppdu on Rx may reduce perक्रमmance on low-end प्रणालीs. It should be
	 * possible to make tables/hashmaps to speed the lookup up (be vary of
	 * cpu data cache lines though regarding sizes) but to keep the initial
	 * implementation simple and less पूर्णांकrusive fallback to the slow lookup
	 * only क्रम multi-channel हालs. Single-channel हालs will reमुख्य to
	 * use the old channel derival and thus perक्रमmance should not be
	 * affected much.
	 */
	rcu_पढ़ो_lock();
	अगर (!ctx && ath10k_mac_num_chanctxs(ar) == 1) अणु
		ieee80211_iter_chan_contexts_atomic(ar->hw,
						    ath10k_mac_get_any_chandef_iter,
						    &def);

		अगर (vअगरs)
			def = &vअगरs[0].new_ctx->def;

		ar->rx_channel = def->chan;
	पूर्ण अन्यथा अगर ((ctx && ath10k_mac_num_chanctxs(ar) == 0) ||
		   (ctx && (ar->state == ATH10K_STATE_RESTARTED))) अणु
		/* During driver restart due to firmware निश्चित, since mac80211
		 * alपढ़ोy has valid channel context क्रम given radio, channel
		 * context iteration वापस num_chanctx > 0. So fix rx_channel
		 * when restart is in progress.
		 */
		ar->rx_channel = ctx->def.chan;
	पूर्ण अन्यथा अणु
		ar->rx_channel = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
ath10k_mac_update_vअगर_chan(काष्ठा ath10k *ar,
			   काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
			   पूर्णांक n_vअगरs)
अणु
	काष्ठा ath10k_vअगर *arvअगर;
	पूर्णांक ret;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->conf_mutex);

	/* First stop monitor पूर्णांकerface. Some FW versions crash अगर there's a
	 * lone monitor पूर्णांकerface.
	 */
	अगर (ar->monitor_started)
		ath10k_monitor_stop(ar);

	क्रम (i = 0; i < n_vअगरs; i++) अणु
		arvअगर = (व्योम *)vअगरs[i].vअगर->drv_priv;

		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac chanctx switch vdev_id %i freq %u->%u width %d->%d\n",
			   arvअगर->vdev_id,
			   vअगरs[i].old_ctx->def.chan->center_freq,
			   vअगरs[i].new_ctx->def.chan->center_freq,
			   vअगरs[i].old_ctx->def.width,
			   vअगरs[i].new_ctx->def.width);

		अगर (WARN_ON(!arvअगर->is_started))
			जारी;

		अगर (WARN_ON(!arvअगर->is_up))
			जारी;

		ret = ath10k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to down vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
			जारी;
		पूर्ण
	पूर्ण

	/* All relevant vdevs are करोwned and associated channel resources
	 * should be available क्रम the channel चयन now.
	 */

	spin_lock_bh(&ar->data_lock);
	ath10k_mac_update_rx_channel(ar, शून्य, vअगरs, n_vअगरs);
	spin_unlock_bh(&ar->data_lock);

	क्रम (i = 0; i < n_vअगरs; i++) अणु
		arvअगर = (व्योम *)vअगरs[i].vअगर->drv_priv;

		अगर (WARN_ON(!arvअगर->is_started))
			जारी;

		अगर (WARN_ON(!arvअगर->is_up))
			जारी;

		ret = ath10k_mac_setup_bcn_पंचांगpl(arvअगर);
		अगर (ret)
			ath10k_warn(ar, "failed to update bcn tmpl during csa: %d\n",
				    ret);

		ret = ath10k_mac_setup_prb_पंचांगpl(arvअगर);
		अगर (ret)
			ath10k_warn(ar, "failed to update prb tmpl during csa: %d\n",
				    ret);

		ret = ath10k_vdev_restart(arvअगर, &vअगरs[i].new_ctx->def);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to restart vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
			जारी;
		पूर्ण

		ret = ath10k_wmi_vdev_up(arvअगर->ar, arvअगर->vdev_id, arvअगर->aid,
					 arvअगर->bssid);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to bring vdev up %d: %d\n",
				    arvअगर->vdev_id, ret);
			जारी;
		पूर्ण
	पूर्ण

	ath10k_monitor_recalc(ar);
पूर्ण

अटल पूर्णांक
ath10k_mac_op_add_chanctx(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath10k *ar = hw->priv;

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx add freq %u width %d ptr %pK\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx);

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	ath10k_mac_update_rx_channel(ar, ctx, शून्य, 0);
	spin_unlock_bh(&ar->data_lock);

	ath10k_recalc_radar_detection(ar);
	ath10k_monitor_recalc(ar);

	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल व्योम
ath10k_mac_op_हटाओ_chanctx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath10k *ar = hw->priv;

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx remove freq %u width %d ptr %pK\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx);

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	ath10k_mac_update_rx_channel(ar, शून्य, शून्य, 0);
	spin_unlock_bh(&ar->data_lock);

	ath10k_recalc_radar_detection(ar);
	ath10k_monitor_recalc(ar);

	mutex_unlock(&ar->conf_mutex);
पूर्ण

काष्ठा ath10k_mac_change_chanctx_arg अणु
	काष्ठा ieee80211_chanctx_conf *ctx;
	काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs;
	पूर्णांक n_vअगरs;
	पूर्णांक next_vअगर;
पूर्ण;

अटल व्योम
ath10k_mac_change_chanctx_cnt_iter(व्योम *data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k_mac_change_chanctx_arg *arg = data;

	अगर (rcu_access_poपूर्णांकer(vअगर->chanctx_conf) != arg->ctx)
		वापस;

	arg->n_vअगरs++;
पूर्ण

अटल व्योम
ath10k_mac_change_chanctx_fill_iter(व्योम *data, u8 *mac,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k_mac_change_chanctx_arg *arg = data;
	काष्ठा ieee80211_chanctx_conf *ctx;

	ctx = rcu_access_poपूर्णांकer(vअगर->chanctx_conf);
	अगर (ctx != arg->ctx)
		वापस;

	अगर (WARN_ON(arg->next_vअगर == arg->n_vअगरs))
		वापस;

	arg->vअगरs[arg->next_vअगर].vअगर = vअगर;
	arg->vअगरs[arg->next_vअगर].old_ctx = ctx;
	arg->vअगरs[arg->next_vअगर].new_ctx = ctx;
	arg->next_vअगर++;
पूर्ण

अटल व्योम
ath10k_mac_op_change_chanctx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_chanctx_conf *ctx,
			     u32 changed)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_mac_change_chanctx_arg arg = अणु .ctx = ctx पूर्ण;

	mutex_lock(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx change freq %u width %d ptr %pK changed %x\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx, changed);

	/* This shouldn't really happen because channel चयनing should use
	 * चयन_vअगर_chanctx().
	 */
	अगर (WARN_ON(changed & IEEE80211_CHANCTX_CHANGE_CHANNEL))
		जाओ unlock;

	अगर (changed & IEEE80211_CHANCTX_CHANGE_WIDTH) अणु
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
					hw,
					ATH10K_ITER_NORMAL_FLAGS,
					ath10k_mac_change_chanctx_cnt_iter,
					&arg);
		अगर (arg.n_vअगरs == 0)
			जाओ radar;

		arg.vअगरs = kसुस्मृति(arg.n_vअगरs, माप(arg.vअगरs[0]),
				   GFP_KERNEL);
		अगर (!arg.vअगरs)
			जाओ radar;

		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
					hw,
					ATH10K_ITER_NORMAL_FLAGS,
					ath10k_mac_change_chanctx_fill_iter,
					&arg);
		ath10k_mac_update_vअगर_chan(ar, arg.vअगरs, arg.n_vअगरs);
		kमुक्त(arg.vअगरs);
	पूर्ण

radar:
	ath10k_recalc_radar_detection(ar);

	/* FIXME: How to configure Rx chains properly? */

	/* No other actions are actually necessary. Firmware मुख्यtains channel
	 * definitions per vdev पूर्णांकernally and there's no host-side channel
	 * context असलtraction to configure, e.g. channel width.
	 */

unlock:
	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक
ath10k_mac_op_assign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx assign ptr %pK vdev_id %i\n",
		   ctx, arvअगर->vdev_id);

	अगर (WARN_ON(arvअगर->is_started)) अणु
		mutex_unlock(&ar->conf_mutex);
		वापस -EBUSY;
	पूर्ण

	ret = ath10k_vdev_start(arvअगर, &ctx->def);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to start vdev %i addr %pM on freq %d: %d\n",
			    arvअगर->vdev_id, vअगर->addr,
			    ctx->def.chan->center_freq, ret);
		जाओ err;
	पूर्ण

	arvअगर->is_started = true;

	ret = ath10k_mac_vअगर_setup_ps(arvअगर);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to update vdev %i ps: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err_stop;
	पूर्ण

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR) अणु
		ret = ath10k_wmi_vdev_up(ar, arvअगर->vdev_id, 0, vअगर->addr);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to up monitor vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_stop;
		पूर्ण

		arvअगर->is_up = true;
	पूर्ण

	अगर (ath10k_mac_can_set_cts_prot(arvअगर)) अणु
		ret = ath10k_mac_set_cts_prot(arvअगर);
		अगर (ret)
			ath10k_warn(ar, "failed to set cts protection for vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	अगर (ath10k_peer_stats_enabled(ar) &&
	    ar->hw_params.tx_stats_over_pktlog) अणु
		ar->pktlog_filter |= ATH10K_PKTLOG_PEER_STATS;
		ret = ath10k_wmi_pdev_pktlog_enable(ar,
						    ar->pktlog_filter);
		अगर (ret) अणु
			ath10k_warn(ar, "failed to enable pktlog %d\n", ret);
			जाओ err_stop;
		पूर्ण
	पूर्ण

	mutex_unlock(&ar->conf_mutex);
	वापस 0;

err_stop:
	ath10k_vdev_stop(arvअगर);
	arvअगर->is_started = false;
	ath10k_mac_vअगर_setup_ps(arvअगर);

err:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम
ath10k_mac_op_unassign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx unassign ptr %pK vdev_id %i\n",
		   ctx, arvअगर->vdev_id);

	WARN_ON(!arvअगर->is_started);

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR) अणु
		WARN_ON(!arvअगर->is_up);

		ret = ath10k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);
		अगर (ret)
			ath10k_warn(ar, "failed to down monitor vdev %i: %d\n",
				    arvअगर->vdev_id, ret);

		arvअगर->is_up = false;
	पूर्ण

	ret = ath10k_vdev_stop(arvअगर);
	अगर (ret)
		ath10k_warn(ar, "failed to stop vdev %i: %d\n",
			    arvअगर->vdev_id, ret);

	arvअगर->is_started = false;

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक
ath10k_mac_op_चयन_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
				 पूर्णांक n_vअगरs,
				 क्रमागत ieee80211_chanctx_चयन_mode mode)
अणु
	काष्ठा ath10k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac chanctx switch n_vifs %d mode %d\n",
		   n_vअगरs, mode);
	ath10k_mac_update_vअगर_chan(ar, vअगरs, n_vअगरs);

	mutex_unlock(&ar->conf_mutex);
	वापस 0;
पूर्ण

अटल व्योम ath10k_mac_op_sta_pre_rcu_हटाओ(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_vअगर *vअगर,
					     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath10k *ar;
	काष्ठा ath10k_peer *peer;

	ar = hw->priv;

	list_क्रम_each_entry(peer, &ar->peers, list)
		अगर (peer->sta == sta)
			peer->हटाओd = true;
पूर्ण

/* HT MCS parameters with Nss = 1 */
अटल स्थिर काष्ठा ath10k_index_ht_data_rate_type supported_ht_mcs_rate_nss1[] = अणु
	/* MCS  L20   L40   S20  S40 */
	अणु0,  अणु 65,  135,  72,  150पूर्ण पूर्ण,
	अणु1,  अणु 130, 270,  144, 300पूर्ण पूर्ण,
	अणु2,  अणु 195, 405,  217, 450पूर्ण पूर्ण,
	अणु3,  अणु 260, 540,  289, 600पूर्ण पूर्ण,
	अणु4,  अणु 390, 810,  433, 900पूर्ण पूर्ण,
	अणु5,  अणु 520, 1080, 578, 1200पूर्ण पूर्ण,
	अणु6,  अणु 585, 1215, 650, 1350पूर्ण पूर्ण,
	अणु7,  अणु 650, 1350, 722, 1500पूर्ण पूर्ण
पूर्ण;

/* HT MCS parameters with Nss = 2 */
अटल स्थिर काष्ठा ath10k_index_ht_data_rate_type supported_ht_mcs_rate_nss2[] = अणु
	/* MCS  L20    L40   S20   S40 */
	अणु0,  अणु130,  270,  144,  300पूर्ण पूर्ण,
	अणु1,  अणु260,  540,  289,  600पूर्ण पूर्ण,
	अणु2,  अणु390,  810,  433,  900पूर्ण पूर्ण,
	अणु3,  अणु520,  1080, 578,  1200पूर्ण पूर्ण,
	अणु4,  अणु780,  1620, 867,  1800पूर्ण पूर्ण,
	अणु5,  अणु1040, 2160, 1156, 2400पूर्ण पूर्ण,
	अणु6,  अणु1170, 2430, 1300, 2700पूर्ण पूर्ण,
	अणु7,  अणु1300, 2700, 1444, 3000पूर्ण पूर्ण
पूर्ण;

/* MCS parameters with Nss = 1 */
अटल स्थिर काष्ठा ath10k_index_vht_data_rate_type supported_vht_mcs_rate_nss1[] = अणु
	/* MCS  L80    S80     L40   S40    L20   S20 */
	अणु0,  अणु293,  325पूर्ण,  अणु135,  150पूर्ण,  अणु65,   72पूर्ण पूर्ण,
	अणु1,  अणु585,  650पूर्ण,  अणु270,  300पूर्ण,  अणु130,  144पूर्ण पूर्ण,
	अणु2,  अणु878,  975पूर्ण,  अणु405,  450पूर्ण,  अणु195,  217पूर्ण पूर्ण,
	अणु3,  अणु1170, 1300पूर्ण, अणु540,  600पूर्ण,  अणु260,  289पूर्ण पूर्ण,
	अणु4,  अणु1755, 1950पूर्ण, अणु810,  900पूर्ण,  अणु390,  433पूर्ण पूर्ण,
	अणु5,  अणु2340, 2600पूर्ण, अणु1080, 1200पूर्ण, अणु520,  578पूर्ण पूर्ण,
	अणु6,  अणु2633, 2925पूर्ण, अणु1215, 1350पूर्ण, अणु585,  650पूर्ण पूर्ण,
	अणु7,  अणु2925, 3250पूर्ण, अणु1350, 1500पूर्ण, अणु650,  722पूर्ण पूर्ण,
	अणु8,  अणु3510, 3900पूर्ण, अणु1620, 1800पूर्ण, अणु780,  867पूर्ण पूर्ण,
	अणु9,  अणु3900, 4333पूर्ण, अणु1800, 2000पूर्ण, अणु780,  867पूर्ण पूर्ण
पूर्ण;

/*MCS parameters with Nss = 2 */
अटल स्थिर काष्ठा ath10k_index_vht_data_rate_type supported_vht_mcs_rate_nss2[] = अणु
	/* MCS  L80    S80     L40   S40    L20   S20 */
	अणु0,  अणु585,  650पूर्ण,  अणु270,  300पूर्ण,  अणु130,  144पूर्ण पूर्ण,
	अणु1,  अणु1170, 1300पूर्ण, अणु540,  600पूर्ण,  अणु260,  289पूर्ण पूर्ण,
	अणु2,  अणु1755, 1950पूर्ण, अणु810,  900पूर्ण,  अणु390,  433पूर्ण पूर्ण,
	अणु3,  अणु2340, 2600पूर्ण, अणु1080, 1200पूर्ण, अणु520,  578पूर्ण पूर्ण,
	अणु4,  अणु3510, 3900पूर्ण, अणु1620, 1800पूर्ण, अणु780,  867पूर्ण पूर्ण,
	अणु5,  अणु4680, 5200पूर्ण, अणु2160, 2400पूर्ण, अणु1040, 1156पूर्ण पूर्ण,
	अणु6,  अणु5265, 5850पूर्ण, अणु2430, 2700पूर्ण, अणु1170, 1300पूर्ण पूर्ण,
	अणु7,  अणु5850, 6500पूर्ण, अणु2700, 3000पूर्ण, अणु1300, 1444पूर्ण पूर्ण,
	अणु8,  अणु7020, 7800पूर्ण, अणु3240, 3600पूर्ण, अणु1560, 1733पूर्ण पूर्ण,
	अणु9,  अणु7800, 8667पूर्ण, अणु3600, 4000पूर्ण, अणु1560, 1733पूर्ण पूर्ण
पूर्ण;

अटल व्योम ath10k_mac_get_rate_flags_ht(काष्ठा ath10k *ar, u32 rate, u8 nss, u8 mcs,
					 u8 *flags, u8 *bw)
अणु
	काष्ठा ath10k_index_ht_data_rate_type *mcs_rate;
	u8 index;
	माप_प्रकार len_nss1 = ARRAY_SIZE(supported_ht_mcs_rate_nss1);
	माप_प्रकार len_nss2 = ARRAY_SIZE(supported_ht_mcs_rate_nss2);

	अगर (mcs >= (len_nss1 + len_nss2)) अणु
		ath10k_warn(ar, "not supported mcs %d in current rate table", mcs);
		वापस;
	पूर्ण

	mcs_rate = (काष्ठा ath10k_index_ht_data_rate_type *)
		   ((nss == 1) ? &supported_ht_mcs_rate_nss1 :
		   &supported_ht_mcs_rate_nss2);

	अगर (mcs >= len_nss1)
		index = mcs - len_nss1;
	अन्यथा
		index = mcs;

	अगर (rate == mcs_rate[index].supported_rate[0]) अणु
		*bw = RATE_INFO_BW_20;
	पूर्ण अन्यथा अगर (rate == mcs_rate[index].supported_rate[1]) अणु
		*bw |= RATE_INFO_BW_40;
	पूर्ण अन्यथा अगर (rate == mcs_rate[index].supported_rate[2]) अणु
		*bw |= RATE_INFO_BW_20;
		*flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अगर (rate == mcs_rate[index].supported_rate[3]) अणु
		*bw |= RATE_INFO_BW_40;
		*flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अणु
		ath10k_warn(ar, "invalid ht params rate %d 100kbps nss %d mcs %d",
			    rate, nss, mcs);
	पूर्ण
पूर्ण

अटल व्योम ath10k_mac_get_rate_flags_vht(काष्ठा ath10k *ar, u32 rate, u8 nss, u8 mcs,
					  u8 *flags, u8 *bw)
अणु
	काष्ठा ath10k_index_vht_data_rate_type *mcs_rate;

	mcs_rate = (काष्ठा ath10k_index_vht_data_rate_type *)
		   ((nss == 1) ? &supported_vht_mcs_rate_nss1 :
		   &supported_vht_mcs_rate_nss2);

	अगर (rate == mcs_rate[mcs].supported_VHT80_rate[0]) अणु
		*bw = RATE_INFO_BW_80;
	पूर्ण अन्यथा अगर (rate == mcs_rate[mcs].supported_VHT80_rate[1]) अणु
		*bw = RATE_INFO_BW_80;
		*flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अगर (rate == mcs_rate[mcs].supported_VHT40_rate[0]) अणु
		*bw = RATE_INFO_BW_40;
	पूर्ण अन्यथा अगर (rate == mcs_rate[mcs].supported_VHT40_rate[1]) अणु
		*bw = RATE_INFO_BW_40;
		*flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अगर (rate == mcs_rate[mcs].supported_VHT20_rate[0]) अणु
		*bw = RATE_INFO_BW_20;
	पूर्ण अन्यथा अगर (rate == mcs_rate[mcs].supported_VHT20_rate[1]) अणु
		*bw = RATE_INFO_BW_20;
		*flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अणु
		ath10k_warn(ar, "invalid vht params rate %d 100kbps nss %d mcs %d",
			    rate, nss, mcs);
	पूर्ण
पूर्ण

अटल व्योम ath10k_mac_get_rate_flags(काष्ठा ath10k *ar, u32 rate,
				      क्रमागत ath10k_phy_mode mode, u8 nss, u8 mcs,
				      u8 *flags, u8 *bw)
अणु
	अगर (mode == ATH10K_PHY_MODE_HT) अणु
		*flags = RATE_INFO_FLAGS_MCS;
		ath10k_mac_get_rate_flags_ht(ar, rate, nss, mcs, flags, bw);
	पूर्ण अन्यथा अगर (mode == ATH10K_PHY_MODE_VHT) अणु
		*flags = RATE_INFO_FLAGS_VHT_MCS;
		ath10k_mac_get_rate_flags_vht(ar, rate, nss, mcs, flags, bw);
	पूर्ण
पूर्ण

अटल व्योम ath10k_mac_parse_bitrate(काष्ठा ath10k *ar, u32 rate_code,
				     u32 bitrate_kbps, काष्ठा rate_info *rate)
अणु
	क्रमागत ath10k_phy_mode mode = ATH10K_PHY_MODE_LEGACY;
	क्रमागत wmi_rate_preamble preamble = WMI_TLV_GET_HW_RC_PREAM_V1(rate_code);
	u8 nss = WMI_TLV_GET_HW_RC_NSS_V1(rate_code) + 1;
	u8 mcs = WMI_TLV_GET_HW_RC_RATE_V1(rate_code);
	u8 flags = 0, bw = 0;

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac parse rate code 0x%x bitrate %d kbps\n",
		   rate_code, bitrate_kbps);

	अगर (preamble == WMI_RATE_PREAMBLE_HT)
		mode = ATH10K_PHY_MODE_HT;
	अन्यथा अगर (preamble == WMI_RATE_PREAMBLE_VHT)
		mode = ATH10K_PHY_MODE_VHT;

	ath10k_mac_get_rate_flags(ar, bitrate_kbps / 100, mode, nss, mcs, &flags, &bw);

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "mac parse bitrate preamble %d mode %d nss %d mcs %d flags %x bw %d\n",
		   preamble, mode, nss, mcs, flags, bw);

	rate->flags = flags;
	rate->bw = bw;
	rate->legacy = bitrate_kbps / 100;
	rate->nss = nss;
	rate->mcs = mcs;
पूर्ण

अटल व्योम ath10k_mac_sta_get_peer_stats_info(काष्ठा ath10k *ar,
					       काष्ठा ieee80211_sta *sta,
					       काष्ठा station_info *sinfo)
अणु
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k_peer *peer;
	अचिन्हित दीर्घ समय_left;
	पूर्णांक ret;

	अगर (!(ar->hw_params.supports_peer_stats_info &&
	      arsta->arvअगर->vdev_type == WMI_VDEV_TYPE_STA))
		वापस;

	spin_lock_bh(&ar->data_lock);
	peer = ath10k_peer_find(ar, arsta->arvअगर->vdev_id, sta->addr);
	spin_unlock_bh(&ar->data_lock);
	अगर (!peer)
		वापस;

	reinit_completion(&ar->peer_stats_info_complete);

	ret = ath10k_wmi_request_peer_stats_info(ar,
						 arsta->arvअगर->vdev_id,
						 WMI_REQUEST_ONE_PEER_STATS_INFO,
						 arsta->arvअगर->bssid,
						 0);
	अगर (ret && ret != -EOPNOTSUPP) अणु
		ath10k_warn(ar, "could not request peer stats info: %d\n", ret);
		वापस;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->peer_stats_info_complete, 3 * HZ);
	अगर (समय_left == 0) अणु
		ath10k_warn(ar, "timed out waiting peer stats info\n");
		वापस;
	पूर्ण

	अगर (arsta->rx_rate_code != 0 && arsta->rx_bitrate_kbps != 0) अणु
		ath10k_mac_parse_bitrate(ar, arsta->rx_rate_code,
					 arsta->rx_bitrate_kbps,
					 &sinfo->rxrate);

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BITRATE);
		arsta->rx_rate_code = 0;
		arsta->rx_bitrate_kbps = 0;
	पूर्ण

	अगर (arsta->tx_rate_code != 0 && arsta->tx_bitrate_kbps != 0) अणु
		ath10k_mac_parse_bitrate(ar, arsta->tx_rate_code,
					 arsta->tx_bitrate_kbps,
					 &sinfo->txrate);

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
		arsta->tx_rate_code = 0;
		arsta->tx_bitrate_kbps = 0;
	पूर्ण
पूर्ण

अटल व्योम ath10k_sta_statistics(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा station_info *sinfo)
अणु
	काष्ठा ath10k_sta *arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	काष्ठा ath10k *ar = arsta->arvअगर->ar;

	अगर (!ath10k_peer_stats_enabled(ar))
		वापस;

	mutex_lock(&ar->conf_mutex);
	ath10k_debug_fw_stats_request(ar);
	mutex_unlock(&ar->conf_mutex);

	sinfo->rx_duration = arsta->rx_duration;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_DURATION);

	अगर (arsta->txrate.legacy || arsta->txrate.nss) अणु
		अगर (arsta->txrate.legacy) अणु
			sinfo->txrate.legacy = arsta->txrate.legacy;
		पूर्ण अन्यथा अणु
			sinfo->txrate.mcs = arsta->txrate.mcs;
			sinfo->txrate.nss = arsta->txrate.nss;
			sinfo->txrate.bw = arsta->txrate.bw;
		पूर्ण
		sinfo->txrate.flags = arsta->txrate.flags;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
	पूर्ण

	अगर (ar->htt.disable_tx_comp) अणु
		sinfo->tx_failed = arsta->tx_failed;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_FAILED);
	पूर्ण

	sinfo->tx_retries = arsta->tx_retries;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_RETRIES);

	ath10k_mac_sta_get_peer_stats_info(ar, sta, sinfo);
पूर्ण

अटल पूर्णांक ath10k_mac_op_set_tid_config(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_sta *sta,
					काष्ठा cfg80211_tid_config *tid_config)
अणु
	काष्ठा ath10k *ar = hw->priv;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_mac_iter_tid_conf_data data = अणुपूर्ण;
	काष्ठा wmi_per_peer_per_tid_cfg_arg arg = अणुपूर्ण;
	पूर्णांक ret, i;

	mutex_lock(&ar->conf_mutex);
	arg.vdev_id = arvअगर->vdev_id;

	arvअगर->tids_rst = 0;
	स_रखो(arvअगर->tid_conf_changed, 0, माप(arvअगर->tid_conf_changed));

	क्रम (i = 0; i < tid_config->n_tid_conf; i++) अणु
		ret = ath10k_mac_parse_tid_config(ar, sta, vअगर,
						  &tid_config->tid_conf[i],
						  &arg);
		अगर (ret)
			जाओ निकास;
	पूर्ण

	ret = 0;

	अगर (sta)
		जाओ निकास;

	arvअगर->tids_rst = 0;
	data.curr_vअगर = vअगर;
	data.ar = ar;

	ieee80211_iterate_stations_atomic(hw, ath10k_mac_vअगर_stations_tid_conf,
					  &data);

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath10k_mac_op_reset_tid_config(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा ieee80211_sta *sta,
					  u8 tids)
अणु
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath10k_mac_iter_tid_conf_data data = अणुपूर्ण;
	काष्ठा ath10k *ar = hw->priv;
	पूर्णांक ret = 0;

	mutex_lock(&ar->conf_mutex);

	अगर (sta) अणु
		arvअगर->tids_rst = 0;
		ret = ath10k_mac_reset_tid_config(ar, sta, arvअगर, tids);
		जाओ निकास;
	पूर्ण

	arvअगर->tids_rst = tids;
	data.curr_vअगर = vअगर;
	data.ar = ar;
	ieee80211_iterate_stations_atomic(hw, ath10k_mac_vअगर_stations_tid_conf,
					  &data);

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops ath10k_ops = अणु
	.tx				= ath10k_mac_op_tx,
	.wake_tx_queue			= ath10k_mac_op_wake_tx_queue,
	.start				= ath10k_start,
	.stop				= ath10k_stop,
	.config				= ath10k_config,
	.add_पूर्णांकerface			= ath10k_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface		= ath10k_हटाओ_पूर्णांकerface,
	.configure_filter		= ath10k_configure_filter,
	.bss_info_changed		= ath10k_bss_info_changed,
	.set_coverage_class		= ath10k_mac_op_set_coverage_class,
	.hw_scan			= ath10k_hw_scan,
	.cancel_hw_scan			= ath10k_cancel_hw_scan,
	.set_key			= ath10k_set_key,
	.set_शेष_unicast_key        = ath10k_set_शेष_unicast_key,
	.sta_state			= ath10k_sta_state,
	.sta_set_txpwr			= ath10k_sta_set_txpwr,
	.conf_tx			= ath10k_conf_tx,
	.reमुख्य_on_channel		= ath10k_reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel	= ath10k_cancel_reमुख्य_on_channel,
	.set_rts_threshold		= ath10k_set_rts_threshold,
	.set_frag_threshold		= ath10k_mac_op_set_frag_threshold,
	.flush				= ath10k_flush,
	.tx_last_beacon			= ath10k_tx_last_beacon,
	.set_antenna			= ath10k_set_antenna,
	.get_antenna			= ath10k_get_antenna,
	.reconfig_complete		= ath10k_reconfig_complete,
	.get_survey			= ath10k_get_survey,
	.set_bitrate_mask		= ath10k_mac_op_set_bitrate_mask,
	.sta_rc_update			= ath10k_sta_rc_update,
	.offset_tsf			= ath10k_offset_tsf,
	.ampdu_action			= ath10k_ampdu_action,
	.get_et_sset_count		= ath10k_debug_get_et_sset_count,
	.get_et_stats			= ath10k_debug_get_et_stats,
	.get_et_strings			= ath10k_debug_get_et_strings,
	.add_chanctx			= ath10k_mac_op_add_chanctx,
	.हटाओ_chanctx			= ath10k_mac_op_हटाओ_chanctx,
	.change_chanctx			= ath10k_mac_op_change_chanctx,
	.assign_vअगर_chanctx		= ath10k_mac_op_assign_vअगर_chanctx,
	.unassign_vअगर_chanctx		= ath10k_mac_op_unassign_vअगर_chanctx,
	.चयन_vअगर_chanctx		= ath10k_mac_op_चयन_vअगर_chanctx,
	.sta_pre_rcu_हटाओ		= ath10k_mac_op_sta_pre_rcu_हटाओ,
	.sta_statistics			= ath10k_sta_statistics,
	.set_tid_config			= ath10k_mac_op_set_tid_config,
	.reset_tid_config		= ath10k_mac_op_reset_tid_config,

	CFG80211_TESTMODE_CMD(ath10k_पंचांग_cmd)

#अगर_घोषित CONFIG_PM
	.suspend			= ath10k_wow_op_suspend,
	.resume				= ath10k_wow_op_resume,
	.set_wakeup			= ath10k_wow_op_set_wakeup,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	.sta_add_debugfs		= ath10k_sta_add_debugfs,
#पूर्ण_अगर
	.set_sar_specs			= ath10k_mac_set_sar_specs,
पूर्ण;

#घोषणा CHAN2G(_channel, _freq, _flags) अणु \
	.band			= NL80211_BAND_2GHZ, \
	.hw_value		= (_channel), \
	.center_freq		= (_freq), \
	.flags			= (_flags), \
	.max_antenna_gain	= 0, \
	.max_घातer		= 30, \
पूर्ण

#घोषणा CHAN5G(_channel, _freq, _flags) अणु \
	.band			= NL80211_BAND_5GHZ, \
	.hw_value		= (_channel), \
	.center_freq		= (_freq), \
	.flags			= (_flags), \
	.max_antenna_gain	= 0, \
	.max_घातer		= 30, \
पूर्ण

अटल स्थिर काष्ठा ieee80211_channel ath10k_2ghz_channels[] = अणु
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

अटल स्थिर काष्ठा ieee80211_channel ath10k_5ghz_channels[] = अणु
	CHAN5G(36, 5180, 0),
	CHAN5G(40, 5200, 0),
	CHAN5G(44, 5220, 0),
	CHAN5G(48, 5240, 0),
	CHAN5G(52, 5260, 0),
	CHAN5G(56, 5280, 0),
	CHAN5G(60, 5300, 0),
	CHAN5G(64, 5320, 0),
	CHAN5G(100, 5500, 0),
	CHAN5G(104, 5520, 0),
	CHAN5G(108, 5540, 0),
	CHAN5G(112, 5560, 0),
	CHAN5G(116, 5580, 0),
	CHAN5G(120, 5600, 0),
	CHAN5G(124, 5620, 0),
	CHAN5G(128, 5640, 0),
	CHAN5G(132, 5660, 0),
	CHAN5G(136, 5680, 0),
	CHAN5G(140, 5700, 0),
	CHAN5G(144, 5720, 0),
	CHAN5G(149, 5745, 0),
	CHAN5G(153, 5765, 0),
	CHAN5G(157, 5785, 0),
	CHAN5G(161, 5805, 0),
	CHAN5G(165, 5825, 0),
	CHAN5G(169, 5845, 0),
	CHAN5G(173, 5865, 0),
	/* If you add more, you may need to change ATH10K_MAX_5G_CHAN */
	/* And you will definitely need to change ATH10K_NUM_CHANS in core.h */
पूर्ण;

काष्ठा ath10k *ath10k_mac_create(माप_प्रकार priv_size)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_ops *ops;
	काष्ठा ath10k *ar;

	ops = kmemdup(&ath10k_ops, माप(ath10k_ops), GFP_KERNEL);
	अगर (!ops)
		वापस शून्य;

	hw = ieee80211_alloc_hw(माप(काष्ठा ath10k) + priv_size, ops);
	अगर (!hw) अणु
		kमुक्त(ops);
		वापस शून्य;
	पूर्ण

	ar = hw->priv;
	ar->hw = hw;
	ar->ops = ops;

	वापस ar;
पूर्ण

व्योम ath10k_mac_destroy(काष्ठा ath10k *ar)
अणु
	काष्ठा ieee80211_ops *ops = ar->ops;

	ieee80211_मुक्त_hw(ar->hw);
	kमुक्त(ops);
पूर्ण

अटल स्थिर काष्ठा ieee80211_अगरace_limit ath10k_अगर_limits[] = अणु
	अणु
		.max	= 8,
		.types	= BIT(NL80211_IFTYPE_STATION)
			| BIT(NL80211_IFTYPE_P2P_CLIENT)
	पूर्ण,
	अणु
		.max	= 3,
		.types	= BIT(NL80211_IFTYPE_P2P_GO)
	पूर्ण,
	अणु
		.max	= 1,
		.types	= BIT(NL80211_IFTYPE_P2P_DEVICE)
	पूर्ण,
	अणु
		.max	= 7,
		.types	= BIT(NL80211_IFTYPE_AP)
#अगर_घोषित CONFIG_MAC80211_MESH
			| BIT(NL80211_IFTYPE_MESH_POINT)
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit ath10k_10x_अगर_limits[] = अणु
	अणु
		.max	= 8,
		.types	= BIT(NL80211_IFTYPE_AP)
#अगर_घोषित CONFIG_MAC80211_MESH
			| BIT(NL80211_IFTYPE_MESH_POINT)
#पूर्ण_अगर
	पूर्ण,
	अणु
		.max	= 1,
		.types	= BIT(NL80211_IFTYPE_STATION)
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination ath10k_अगर_comb[] = अणु
	अणु
		.limits = ath10k_अगर_limits,
		.n_limits = ARRAY_SIZE(ath10k_अगर_limits),
		.max_पूर्णांकerfaces = 8,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination ath10k_10x_अगर_comb[] = अणु
	अणु
		.limits = ath10k_10x_अगर_limits,
		.n_limits = ARRAY_SIZE(ath10k_10x_अगर_limits),
		.max_पूर्णांकerfaces = 8,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
		.beacon_पूर्णांक_min_gcd = 1,
#अगर_घोषित CONFIG_ATH10K_DFS_CERTIFIED
		.radar_detect_widths =	BIT(NL80211_CHAN_WIDTH_20_NOHT) |
					BIT(NL80211_CHAN_WIDTH_20) |
					BIT(NL80211_CHAN_WIDTH_40) |
					BIT(NL80211_CHAN_WIDTH_80),
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit ath10k_tlv_अगर_limit[] = अणु
	अणु
		.max = 2,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
	अणु
		.max = 2,
		.types = BIT(NL80211_IFTYPE_AP) |
#अगर_घोषित CONFIG_MAC80211_MESH
			 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
			 BIT(NL80211_IFTYPE_P2P_CLIENT) |
			 BIT(NL80211_IFTYPE_P2P_GO),
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_P2P_DEVICE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit ath10k_tlv_qcs_अगर_limit[] = अणु
	अणु
		.max = 2,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
	अणु
		.max = 2,
		.types = BIT(NL80211_IFTYPE_P2P_CLIENT),
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_AP) |
#अगर_घोषित CONFIG_MAC80211_MESH
			 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
			 BIT(NL80211_IFTYPE_P2P_GO),
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_P2P_DEVICE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit ath10k_tlv_अगर_limit_ibss[] = अणु
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_ADHOC),
	पूर्ण,
पूर्ण;

/* FIXME: This is not thouroughly tested. These combinations may over- or
 * underestimate hw/fw capabilities.
 */
अटल काष्ठा ieee80211_अगरace_combination ath10k_tlv_अगर_comb[] = अणु
	अणु
		.limits = ath10k_tlv_अगर_limit,
		.num_dअगरferent_channels = 1,
		.max_पूर्णांकerfaces = 4,
		.n_limits = ARRAY_SIZE(ath10k_tlv_अगर_limit),
	पूर्ण,
	अणु
		.limits = ath10k_tlv_अगर_limit_ibss,
		.num_dअगरferent_channels = 1,
		.max_पूर्णांकerfaces = 2,
		.n_limits = ARRAY_SIZE(ath10k_tlv_अगर_limit_ibss),
	पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_अगरace_combination ath10k_tlv_qcs_अगर_comb[] = अणु
	अणु
		.limits = ath10k_tlv_अगर_limit,
		.num_dअगरferent_channels = 1,
		.max_पूर्णांकerfaces = 4,
		.n_limits = ARRAY_SIZE(ath10k_tlv_अगर_limit),
	पूर्ण,
	अणु
		.limits = ath10k_tlv_qcs_अगर_limit,
		.num_dअगरferent_channels = 2,
		.max_पूर्णांकerfaces = 4,
		.n_limits = ARRAY_SIZE(ath10k_tlv_qcs_अगर_limit),
	पूर्ण,
	अणु
		.limits = ath10k_tlv_अगर_limit_ibss,
		.num_dअगरferent_channels = 1,
		.max_पूर्णांकerfaces = 2,
		.n_limits = ARRAY_SIZE(ath10k_tlv_अगर_limit_ibss),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit ath10k_10_4_अगर_limits[] = अणु
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
	अणु
		.max	= 16,
		.types	= BIT(NL80211_IFTYPE_AP)
#अगर_घोषित CONFIG_MAC80211_MESH
			| BIT(NL80211_IFTYPE_MESH_POINT)
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination ath10k_10_4_अगर_comb[] = अणु
	अणु
		.limits = ath10k_10_4_अगर_limits,
		.n_limits = ARRAY_SIZE(ath10k_10_4_अगर_limits),
		.max_पूर्णांकerfaces = 16,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
		.beacon_पूर्णांक_min_gcd = 1,
#अगर_घोषित CONFIG_ATH10K_DFS_CERTIFIED
		.radar_detect_widths =	BIT(NL80211_CHAN_WIDTH_20_NOHT) |
					BIT(NL80211_CHAN_WIDTH_20) |
					BIT(NL80211_CHAN_WIDTH_40) |
					BIT(NL80211_CHAN_WIDTH_80) |
					BIT(NL80211_CHAN_WIDTH_80P80) |
					BIT(NL80211_CHAN_WIDTH_160),
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
ieee80211_अगरace_combination ath10k_10_4_bcn_पूर्णांक_अगर_comb[] = अणु
	अणु
		.limits = ath10k_10_4_अगर_limits,
		.n_limits = ARRAY_SIZE(ath10k_10_4_अगर_limits),
		.max_पूर्णांकerfaces = 16,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
		.beacon_पूर्णांक_min_gcd = 100,
#अगर_घोषित CONFIG_ATH10K_DFS_CERTIFIED
		.radar_detect_widths =  BIT(NL80211_CHAN_WIDTH_20_NOHT) |
					BIT(NL80211_CHAN_WIDTH_20) |
					BIT(NL80211_CHAN_WIDTH_40) |
					BIT(NL80211_CHAN_WIDTH_80) |
					BIT(NL80211_CHAN_WIDTH_80P80) |
					BIT(NL80211_CHAN_WIDTH_160),
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल व्योम ath10k_get_arvअगर_iter(व्योम *data, u8 *mac,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath10k_vअगर_iter *arvअगर_iter = data;
	काष्ठा ath10k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	अगर (arvअगर->vdev_id == arvअगर_iter->vdev_id)
		arvअगर_iter->arvअगर = arvअगर;
पूर्ण

काष्ठा ath10k_vअगर *ath10k_get_arvअगर(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा ath10k_vअगर_iter arvअगर_iter;

	स_रखो(&arvअगर_iter, 0, माप(काष्ठा ath10k_vअगर_iter));
	arvअगर_iter.vdev_id = vdev_id;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   ATH10K_ITER_RESUME_FLAGS,
						   ath10k_get_arvअगर_iter,
						   &arvअगर_iter);
	अगर (!arvअगर_iter.arvअगर) अणु
		ath10k_warn(ar, "No VIF found for vdev %d\n", vdev_id);
		वापस शून्य;
	पूर्ण

	वापस arvअगर_iter.arvअगर;
पूर्ण

#घोषणा WRD_METHOD "WRDD"
#घोषणा WRDD_WIFI  (0x07)

अटल u32 ath10k_mac_wrdd_get_mcc(काष्ठा ath10k *ar, जोड़ acpi_object *wrdd)
अणु
	जोड़ acpi_object *mcc_pkg;
	जोड़ acpi_object *करोमुख्य_type;
	जोड़ acpi_object *mcc_value;
	u32 i;

	अगर (wrdd->type != ACPI_TYPE_PACKAGE ||
	    wrdd->package.count < 2 ||
	    wrdd->package.elements[0].type != ACPI_TYPE_INTEGER ||
	    wrdd->package.elements[0].पूर्णांकeger.value != 0) अणु
		ath10k_warn(ar, "ignoring malformed/unsupported wrdd structure\n");
		वापस 0;
	पूर्ण

	क्रम (i = 1; i < wrdd->package.count; ++i) अणु
		mcc_pkg = &wrdd->package.elements[i];

		अगर (mcc_pkg->type != ACPI_TYPE_PACKAGE)
			जारी;
		अगर (mcc_pkg->package.count < 2)
			जारी;
		अगर (mcc_pkg->package.elements[0].type != ACPI_TYPE_INTEGER ||
		    mcc_pkg->package.elements[1].type != ACPI_TYPE_INTEGER)
			जारी;

		करोमुख्य_type = &mcc_pkg->package.elements[0];
		अगर (करोमुख्य_type->पूर्णांकeger.value != WRDD_WIFI)
			जारी;

		mcc_value = &mcc_pkg->package.elements[1];
		वापस mcc_value->पूर्णांकeger.value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_get_wrdd_regulatory(काष्ठा ath10k *ar, u16 *rd)
अणु
	acpi_handle root_handle;
	acpi_handle handle;
	काष्ठा acpi_buffer wrdd = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	acpi_status status;
	u32 alpha2_code;
	अक्षर alpha2[3];

	root_handle = ACPI_HANDLE(ar->dev);
	अगर (!root_handle)
		वापस -EOPNOTSUPP;

	status = acpi_get_handle(root_handle, (acpi_string)WRD_METHOD, &handle);
	अगर (ACPI_FAILURE(status)) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "failed to get wrd method %d\n", status);
		वापस -EIO;
	पूर्ण

	status = acpi_evaluate_object(handle, शून्य, शून्य, &wrdd);
	अगर (ACPI_FAILURE(status)) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "failed to call wrdc %d\n", status);
		वापस -EIO;
	पूर्ण

	alpha2_code = ath10k_mac_wrdd_get_mcc(ar, wrdd.poपूर्णांकer);
	kमुक्त(wrdd.poपूर्णांकer);
	अगर (!alpha2_code)
		वापस -EIO;

	alpha2[0] = (alpha2_code >> 8) & 0xff;
	alpha2[1] = (alpha2_code >> 0) & 0xff;
	alpha2[2] = '\0';

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "regulatory hint from WRDD (alpha2-code): %s\n", alpha2);

	*rd = ath_regd_find_country_by_name(alpha2);
	अगर (*rd == 0xffff)
		वापस -EIO;

	*rd |= COUNTRY_ERD_FLAG;
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_mac_init_rd(काष्ठा ath10k *ar)
अणु
	पूर्णांक ret;
	u16 rd;

	ret = ath10k_mac_get_wrdd_regulatory(ar, &rd);
	अगर (ret) अणु
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "fallback to eeprom programmed regulatory settings\n");
		rd = ar->hw_eeprom_rd;
	पूर्ण

	ar->ath_common.regulatory.current_rd = rd;
	वापस 0;
पूर्ण

पूर्णांक ath10k_mac_रेजिस्टर(काष्ठा ath10k *ar)
अणु
	अटल स्थिर u32 cipher_suites[] = अणु
		WLAN_CIPHER_SUITE_WEP40,
		WLAN_CIPHER_SUITE_WEP104,
		WLAN_CIPHER_SUITE_TKIP,
		WLAN_CIPHER_SUITE_CCMP,

		/* Do not add hardware supported ciphers beक्रमe this line.
		 * Allow software encryption क्रम all chips. Don't क्रमget to
		 * update n_cipher_suites below.
		 */
		WLAN_CIPHER_SUITE_AES_CMAC,
		WLAN_CIPHER_SUITE_BIP_CMAC_256,
		WLAN_CIPHER_SUITE_BIP_GMAC_128,
		WLAN_CIPHER_SUITE_BIP_GMAC_256,

		/* Only QCA99x0 and QCA4019 varients support GCMP-128, GCMP-256
		 * and CCMP-256 in hardware.
		 */
		WLAN_CIPHER_SUITE_GCMP,
		WLAN_CIPHER_SUITE_GCMP_256,
		WLAN_CIPHER_SUITE_CCMP_256,
	पूर्ण;
	काष्ठा ieee80211_supported_band *band;
	व्योम *channels;
	पूर्णांक ret;

	अगर (!is_valid_ether_addr(ar->mac_addr)) अणु
		ath10k_warn(ar, "invalid MAC address; choosing random\n");
		eth_अक्रमom_addr(ar->mac_addr);
	पूर्ण
	SET_IEEE80211_PERM_ADDR(ar->hw, ar->mac_addr);

	SET_IEEE80211_DEV(ar->hw, ar->dev);

	BUILD_BUG_ON((ARRAY_SIZE(ath10k_2ghz_channels) +
		      ARRAY_SIZE(ath10k_5ghz_channels)) !=
		     ATH10K_NUM_CHANS);

	अगर (ar->phy_capability & WHAL_WLAN_11G_CAPABILITY) अणु
		channels = kmemdup(ath10k_2ghz_channels,
				   माप(ath10k_2ghz_channels),
				   GFP_KERNEL);
		अगर (!channels) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त;
		पूर्ण

		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		band->n_channels = ARRAY_SIZE(ath10k_2ghz_channels);
		band->channels = channels;

		अगर (ar->hw_params.cck_rate_map_rev2) अणु
			band->n_bitrates = ath10k_g_rates_rev2_size;
			band->bitrates = ath10k_g_rates_rev2;
		पूर्ण अन्यथा अणु
			band->n_bitrates = ath10k_g_rates_size;
			band->bitrates = ath10k_g_rates;
		पूर्ण

		ar->hw->wiphy->bands[NL80211_BAND_2GHZ] = band;
	पूर्ण

	अगर (ar->phy_capability & WHAL_WLAN_11A_CAPABILITY) अणु
		channels = kmemdup(ath10k_5ghz_channels,
				   माप(ath10k_5ghz_channels),
				   GFP_KERNEL);
		अगर (!channels) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त;
		पूर्ण

		band = &ar->mac.sbands[NL80211_BAND_5GHZ];
		band->n_channels = ARRAY_SIZE(ath10k_5ghz_channels);
		band->channels = channels;
		band->n_bitrates = ath10k_a_rates_size;
		band->bitrates = ath10k_a_rates;
		ar->hw->wiphy->bands[NL80211_BAND_5GHZ] = band;
	पूर्ण

	wiphy_पढ़ो_of_freq_limits(ar->hw->wiphy);
	ath10k_mac_setup_ht_vht_cap(ar);

	ar->hw->wiphy->पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_MESH_POINT);

	ar->hw->wiphy->available_antennas_rx = ar->cfg_rx_chainmask;
	ar->hw->wiphy->available_antennas_tx = ar->cfg_tx_chainmask;

	अगर (!test_bit(ATH10K_FW_FEATURE_NO_P2P, ar->normal_mode_fw.fw_file.fw_features))
		ar->hw->wiphy->पूर्णांकerface_modes |=
			BIT(NL80211_IFTYPE_P2P_DEVICE) |
			BIT(NL80211_IFTYPE_P2P_CLIENT) |
			BIT(NL80211_IFTYPE_P2P_GO);

	ieee80211_hw_set(ar->hw, SIGNAL_DBM);

	अगर (!test_bit(ATH10K_FW_FEATURE_NO_PS,
		      ar->running_fw->fw_file.fw_features)) अणु
		ieee80211_hw_set(ar->hw, SUPPORTS_PS);
		ieee80211_hw_set(ar->hw, SUPPORTS_DYNAMIC_PS);
	पूर्ण

	ieee80211_hw_set(ar->hw, MFP_CAPABLE);
	ieee80211_hw_set(ar->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(ar->hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(ar->hw, AP_LINK_PS);
	ieee80211_hw_set(ar->hw, SPECTRUM_MGMT);
	ieee80211_hw_set(ar->hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(ar->hw, CONNECTION_MONITOR);
	ieee80211_hw_set(ar->hw, SUPPORTS_PER_STA_GTK);
	ieee80211_hw_set(ar->hw, WANT_MONITOR_VIF);
	ieee80211_hw_set(ar->hw, CHANCTX_STA_CSA);
	ieee80211_hw_set(ar->hw, QUEUE_CONTROL);
	ieee80211_hw_set(ar->hw, SUPPORTS_TX_FRAG);
	ieee80211_hw_set(ar->hw, REPORTS_LOW_ACK);

	अगर (!test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags))
		ieee80211_hw_set(ar->hw, SW_CRYPTO_CONTROL);

	ar->hw->wiphy->features |= NL80211_FEATURE_STATIC_SMPS;
	ar->hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	अगर (ar->ht_cap_info & WMI_HT_CAP_DYNAMIC_SMPS)
		ar->hw->wiphy->features |= NL80211_FEATURE_DYNAMIC_SMPS;

	अगर (ar->ht_cap_info & WMI_HT_CAP_ENABLED) अणु
		ieee80211_hw_set(ar->hw, AMPDU_AGGREGATION);
		ieee80211_hw_set(ar->hw, TX_AMPDU_SETUP_IN_HW);
	पूर्ण

	ar->hw->wiphy->max_scan_ssids = WLAN_SCAN_PARAMS_MAX_SSID;
	ar->hw->wiphy->max_scan_ie_len = WLAN_SCAN_PARAMS_MAX_IE_LEN;

	अगर (test_bit(WMI_SERVICE_NLO, ar->wmi.svc_map)) अणु
		ar->hw->wiphy->max_sched_scan_ssids = WMI_PNO_MAX_SUPP_NETWORKS;
		ar->hw->wiphy->max_match_sets = WMI_PNO_MAX_SUPP_NETWORKS;
		ar->hw->wiphy->max_sched_scan_ie_len = WMI_PNO_MAX_IE_LENGTH;
		ar->hw->wiphy->max_sched_scan_plans = WMI_PNO_MAX_SCHED_SCAN_PLANS;
		ar->hw->wiphy->max_sched_scan_plan_पूर्णांकerval =
			WMI_PNO_MAX_SCHED_SCAN_PLAN_INT;
		ar->hw->wiphy->max_sched_scan_plan_iterations =
			WMI_PNO_MAX_SCHED_SCAN_PLAN_ITRNS;
		ar->hw->wiphy->features |= NL80211_FEATURE_ND_RANDOM_MAC_ADDR;
	पूर्ण

	ar->hw->vअगर_data_size = माप(काष्ठा ath10k_vअगर);
	ar->hw->sta_data_size = माप(काष्ठा ath10k_sta);
	ar->hw->txq_data_size = माप(काष्ठा ath10k_txq);

	ar->hw->max_listen_पूर्णांकerval = ATH10K_MAX_HW_LISTEN_INTERVAL;

	अगर (test_bit(WMI_SERVICE_BEACON_OFFLOAD, ar->wmi.svc_map)) अणु
		ar->hw->wiphy->flags |= WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD;

		/* Firmware delivers WPS/P2P Probe Requests frames to driver so
		 * that userspace (e.g. wpa_supplicant/hostapd) can generate
		 * correct Probe Responses. This is more of a hack advert..
		 */
		ar->hw->wiphy->probe_resp_offload |=
			NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
			NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 |
			NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_TDLS, ar->wmi.svc_map) ||
	    test_bit(WMI_SERVICE_TDLS_EXPLICIT_MODE_ONLY, ar->wmi.svc_map)) अणु
		ar->hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS;
		अगर (test_bit(WMI_SERVICE_TDLS_WIDER_BANDWIDTH, ar->wmi.svc_map))
			ieee80211_hw_set(ar->hw, TDLS_WIDER_BW);
	पूर्ण

	अगर (test_bit(WMI_SERVICE_TDLS_UAPSD_BUFFER_STA, ar->wmi.svc_map))
		ieee80211_hw_set(ar->hw, SUPPORTS_TDLS_BUFFER_STA);

	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;
	ar->hw->wiphy->max_reमुख्य_on_channel_duration = 5000;

	ar->hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;
	ar->hw->wiphy->features |= NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE |
				   NL80211_FEATURE_AP_SCAN;

	ar->hw->wiphy->max_ap_assoc_sta = ar->max_num_stations;

	ret = ath10k_wow_init(ar);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to init wow: %d\n", ret);
		जाओ err_मुक्त;
	पूर्ण

	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_VHT_IBSS);
	wiphy_ext_feature_set(ar->hw->wiphy,
			      NL80211_EXT_FEATURE_SET_SCAN_DWELL);
	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_AQL);

	अगर (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI, ar->wmi.svc_map) ||
	    test_bit(WMI_SERVICE_HTT_MGMT_TX_COMP_VALID_FLAGS, ar->wmi.svc_map))
		wiphy_ext_feature_set(ar->hw->wiphy,
				      NL80211_EXT_FEATURE_ACK_SIGNAL_SUPPORT);

	अगर (ath10k_peer_stats_enabled(ar) ||
	    test_bit(WMI_SERVICE_REPORT_AIRTIME, ar->wmi.svc_map))
		wiphy_ext_feature_set(ar->hw->wiphy,
				      NL80211_EXT_FEATURE_AIRTIME_FAIRNESS);

	अगर (test_bit(WMI_SERVICE_RTT_RESPONDER_ROLE, ar->wmi.svc_map))
		wiphy_ext_feature_set(ar->hw->wiphy,
				      NL80211_EXT_FEATURE_ENABLE_FTM_RESPONDER);

	अगर (test_bit(WMI_SERVICE_TX_PWR_PER_PEER, ar->wmi.svc_map))
		wiphy_ext_feature_set(ar->hw->wiphy,
				      NL80211_EXT_FEATURE_STA_TX_PWR);

	अगर (test_bit(WMI_SERVICE_PEER_TID_CONFIGS_SUPPORT, ar->wmi.svc_map)) अणु
		ar->hw->wiphy->tid_config_support.vअगर |=
				BIT(NL80211_TID_CONFIG_ATTR_NOACK) |
				BIT(NL80211_TID_CONFIG_ATTR_RETRY_SHORT) |
				BIT(NL80211_TID_CONFIG_ATTR_RETRY_LONG) |
				BIT(NL80211_TID_CONFIG_ATTR_AMPDU_CTRL) |
				BIT(NL80211_TID_CONFIG_ATTR_TX_RATE) |
				BIT(NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE);

		अगर (test_bit(WMI_SERVICE_EXT_PEER_TID_CONFIGS_SUPPORT,
			     ar->wmi.svc_map)) अणु
			ar->hw->wiphy->tid_config_support.vअगर |=
				BIT(NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL);
		पूर्ण

		ar->hw->wiphy->tid_config_support.peer =
				ar->hw->wiphy->tid_config_support.vअगर;
		ar->hw->wiphy->max_data_retry_count = ATH10K_MAX_RETRY_COUNT;
	पूर्ण अन्यथा अणु
		ar->ops->set_tid_config = शून्य;
	पूर्ण
	/*
	 * on LL hardware queues are managed entirely by the FW
	 * so we only advertise to mac we can करो the queues thing
	 */
	ar->hw->queues = IEEE80211_MAX_QUEUES;

	/* vdev_ids are used as hw queue numbers. Make sure offchan tx queue is
	 * something that vdev_ids can't reach so that we don't stop the queue
	 * accidentally.
	 */
	ar->hw->offchannel_tx_hw_queue = IEEE80211_MAX_QUEUES - 1;

	चयन (ar->running_fw->fw_file.wmi_op_version) अणु
	हाल ATH10K_FW_WMI_OP_VERSION_MAIN:
		ar->hw->wiphy->अगरace_combinations = ath10k_अगर_comb;
		ar->hw->wiphy->n_अगरace_combinations =
			ARRAY_SIZE(ath10k_अगर_comb);
		ar->hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_ADHOC);
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_TLV:
		अगर (test_bit(WMI_SERVICE_ADAPTIVE_OCS, ar->wmi.svc_map)) अणु
			ar->hw->wiphy->अगरace_combinations =
				ath10k_tlv_qcs_अगर_comb;
			ar->hw->wiphy->n_अगरace_combinations =
				ARRAY_SIZE(ath10k_tlv_qcs_अगर_comb);
		पूर्ण अन्यथा अणु
			ar->hw->wiphy->अगरace_combinations = ath10k_tlv_अगर_comb;
			ar->hw->wiphy->n_अगरace_combinations =
				ARRAY_SIZE(ath10k_tlv_अगर_comb);
		पूर्ण
		ar->hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_ADHOC);
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_10_1:
	हाल ATH10K_FW_WMI_OP_VERSION_10_2:
	हाल ATH10K_FW_WMI_OP_VERSION_10_2_4:
		ar->hw->wiphy->अगरace_combinations = ath10k_10x_अगर_comb;
		ar->hw->wiphy->n_अगरace_combinations =
			ARRAY_SIZE(ath10k_10x_अगर_comb);
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_10_4:
		ar->hw->wiphy->अगरace_combinations = ath10k_10_4_अगर_comb;
		ar->hw->wiphy->n_अगरace_combinations =
			ARRAY_SIZE(ath10k_10_4_अगर_comb);
		अगर (test_bit(WMI_SERVICE_VDEV_DIFFERENT_BEACON_INTERVAL_SUPPORT,
			     ar->wmi.svc_map)) अणु
			ar->hw->wiphy->अगरace_combinations =
				ath10k_10_4_bcn_पूर्णांक_अगर_comb;
			ar->hw->wiphy->n_अगरace_combinations =
				ARRAY_SIZE(ath10k_10_4_bcn_पूर्णांक_अगर_comb);
		पूर्ण
		अवरोध;
	हाल ATH10K_FW_WMI_OP_VERSION_UNSET:
	हाल ATH10K_FW_WMI_OP_VERSION_MAX:
		WARN_ON(1);
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	अगर (ar->hw_params.dynamic_sar_support)
		ar->hw->wiphy->sar_capa = &ath10k_sar_capa;

	अगर (!test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags))
		ar->hw->netdev_features = NETIF_F_HW_CSUM;

	अगर (IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED)) अणु
		/* Init ath dfs pattern detector */
		ar->ath_common.debug_mask = ATH_DBG_DFS;
		ar->dfs_detector = dfs_pattern_detector_init(&ar->ath_common,
							     NL80211_DFS_UNSET);

		अगर (!ar->dfs_detector)
			ath10k_warn(ar, "failed to initialise DFS pattern detector\n");
	पूर्ण

	ret = ath10k_mac_init_rd(ar);
	अगर (ret) अणु
		ath10k_err(ar, "failed to derive regdom: %d\n", ret);
		जाओ err_dfs_detector_निकास;
	पूर्ण

	/* Disable set_coverage_class क्रम chipsets that करो not support it. */
	अगर (!ar->hw_params.hw_ops->set_coverage_class)
		ar->ops->set_coverage_class = शून्य;

	ret = ath_regd_init(&ar->ath_common.regulatory, ar->hw->wiphy,
			    ath10k_reg_notअगरier);
	अगर (ret) अणु
		ath10k_err(ar, "failed to initialise regulatory: %i\n", ret);
		जाओ err_dfs_detector_निकास;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_SPOOF_MAC_SUPPORT, ar->wmi.svc_map)) अणु
		ar->hw->wiphy->features |=
			NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;
	पूर्ण

	ar->hw->wiphy->cipher_suites = cipher_suites;

	/* QCA988x and QCA6174 family chips करो not support CCMP-256, GCMP-128
	 * and GCMP-256 ciphers in hardware. Fetch number of ciphers supported
	 * from chip specअगरic hw_param table.
	 */
	अगर (!ar->hw_params.n_cipher_suites ||
	    ar->hw_params.n_cipher_suites > ARRAY_SIZE(cipher_suites)) अणु
		ath10k_err(ar, "invalid hw_params.n_cipher_suites %d\n",
			   ar->hw_params.n_cipher_suites);
		ar->hw_params.n_cipher_suites = 8;
	पूर्ण
	ar->hw->wiphy->n_cipher_suites = ar->hw_params.n_cipher_suites;

	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	ar->hw->weight_multiplier = ATH10K_AIRTIME_WEIGHT_MULTIPLIER;

	ret = ieee80211_रेजिस्टर_hw(ar->hw);
	अगर (ret) अणु
		ath10k_err(ar, "failed to register ieee80211: %d\n", ret);
		जाओ err_dfs_detector_निकास;
	पूर्ण

	अगर (test_bit(WMI_SERVICE_PER_PACKET_SW_ENCRYPT, ar->wmi.svc_map)) अणु
		ar->hw->wiphy->पूर्णांकerface_modes |= BIT(NL80211_IFTYPE_AP_VLAN);
		ar->hw->wiphy->software_अगरtypes |= BIT(NL80211_IFTYPE_AP_VLAN);
	पूर्ण

	अगर (!ath_is_world_regd(&ar->ath_common.regulatory)) अणु
		ret = regulatory_hपूर्णांक(ar->hw->wiphy,
				      ar->ath_common.regulatory.alpha2);
		अगर (ret)
			जाओ err_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_unरेजिस्टर:
	ieee80211_unरेजिस्टर_hw(ar->hw);

err_dfs_detector_निकास:
	अगर (IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED) && ar->dfs_detector)
		ar->dfs_detector->निकास(ar->dfs_detector);

err_मुक्त:
	kमुक्त(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
	kमुक्त(ar->mac.sbands[NL80211_BAND_5GHZ].channels);

	SET_IEEE80211_DEV(ar->hw, शून्य);
	वापस ret;
पूर्ण

व्योम ath10k_mac_unरेजिस्टर(काष्ठा ath10k *ar)
अणु
	ieee80211_unरेजिस्टर_hw(ar->hw);

	अगर (IS_ENABLED(CONFIG_ATH10K_DFS_CERTIFIED) && ar->dfs_detector)
		ar->dfs_detector->निकास(ar->dfs_detector);

	kमुक्त(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
	kमुक्त(ar->mac.sbands[NL80211_BAND_5GHZ].channels);

	SET_IEEE80211_DEV(ar->hw, शून्य);
पूर्ण
