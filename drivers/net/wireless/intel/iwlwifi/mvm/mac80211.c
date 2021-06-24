<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/समय.स>
#समावेश <net/mac80211.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <net/tcp.h>

#समावेश "iwl-op-mode.h"
#समावेश "iwl-io.h"
#समावेश "mvm.h"
#समावेश "sta.h"
#समावेश "time-event.h"
#समावेश "iwl-eeprom-parse.h"
#समावेश "iwl-phy-db.h"
#समावेश "testmode.h"
#समावेश "fw/error-dump.h"
#समावेश "iwl-prph.h"
#समावेश "iwl-nvm-parse.h"

अटल स्थिर काष्ठा ieee80211_अगरace_limit iwl_mvm_limits[] = अणु
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_AP) |
			BIT(NL80211_IFTYPE_P2P_CLIENT) |
			BIT(NL80211_IFTYPE_P2P_GO),
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_P2P_DEVICE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination iwl_mvm_अगरace_combinations[] = अणु
	अणु
		.num_dअगरferent_channels = 2,
		.max_पूर्णांकerfaces = 3,
		.limits = iwl_mvm_limits,
		.n_limits = ARRAY_SIZE(iwl_mvm_limits),
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_IWLWIFI_BCAST_FILTERING
/*
 * Use the reserved field to indicate magic values.
 * these values will only be used पूर्णांकernally by the driver,
 * and won't make it to the fw (reserved will be 0).
 * BC_FILTER_MAGIC_IP - configure the val of this attribute to
 *	be the vअगर's ip address. in हाल there is not a single
 *	ip address (0, or more than 1), this attribute will
 *	be skipped.
 * BC_FILTER_MAGIC_MAC - set the val of this attribute to
 *	the LSB bytes of the vअगर's mac address
 */
क्रमागत अणु
	BC_FILTER_MAGIC_NONE = 0,
	BC_FILTER_MAGIC_IP,
	BC_FILTER_MAGIC_MAC,
पूर्ण;

अटल स्थिर काष्ठा iwl_fw_bcast_filter iwl_mvm_शेष_bcast_filters[] = अणु
	अणु
		/* arp */
		.discard = 0,
		.frame_type = BCAST_FILTER_FRAME_TYPE_ALL,
		.attrs = अणु
			अणु
				/* frame type - arp, hw type - ethernet */
				.offset_type =
					BCAST_FILTER_OFFSET_PAYLOAD_START,
				.offset = माप(rfc1042_header),
				.val = cpu_to_be32(0x08060001),
				.mask = cpu_to_be32(0xffffffff),
			पूर्ण,
			अणु
				/* arp dest ip */
				.offset_type =
					BCAST_FILTER_OFFSET_PAYLOAD_START,
				.offset = माप(rfc1042_header) + 2 +
					  माप(काष्ठा arphdr) +
					  ETH_ALEN + माप(__be32) +
					  ETH_ALEN,
				.mask = cpu_to_be32(0xffffffff),
				/* mark it as special field */
				.reserved1 = cpu_to_le16(BC_FILTER_MAGIC_IP),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		/* dhcp offer bcast */
		.discard = 0,
		.frame_type = BCAST_FILTER_FRAME_TYPE_IPV4,
		.attrs = अणु
			अणु
				/* udp dest port - 68 (bootp client)*/
				.offset_type = BCAST_FILTER_OFFSET_IP_END,
				.offset = दुरत्व(काष्ठा udphdr, dest),
				.val = cpu_to_be32(0x00440000),
				.mask = cpu_to_be32(0xffff0000),
			पूर्ण,
			अणु
				/* dhcp - lsb bytes of client hw address */
				.offset_type = BCAST_FILTER_OFFSET_IP_END,
				.offset = 38,
				.mask = cpu_to_be32(0xffffffff),
				/* mark it as special field */
				.reserved1 = cpu_to_le16(BC_FILTER_MAGIC_MAC),
			पूर्ण,
		पूर्ण,
	पूर्ण,
	/* last filter must be empty */
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा cfg80211_pmsr_capabilities iwl_mvm_pmsr_capa = अणु
	.max_peers = IWL_MVM_TOF_MAX_APS,
	.report_ap_tsf = 1,
	.अक्रमomize_mac_addr = 1,

	.fपंचांग = अणु
		.supported = 1,
		.asap = 1,
		.non_asap = 1,
		.request_lci = 1,
		.request_civicloc = 1,
		.trigger_based = 1,
		.non_trigger_based = 1,
		.max_bursts_exponent = -1, /* all supported */
		.max_fपंचांगs_per_burst = 0, /* no limits */
		.bandwidths = BIT(NL80211_CHAN_WIDTH_20_NOHT) |
			      BIT(NL80211_CHAN_WIDTH_20) |
			      BIT(NL80211_CHAN_WIDTH_40) |
			      BIT(NL80211_CHAN_WIDTH_80),
		.preambles = BIT(NL80211_PREAMBLE_LEGACY) |
			     BIT(NL80211_PREAMBLE_HT) |
			     BIT(NL80211_PREAMBLE_VHT) |
			     BIT(NL80211_PREAMBLE_HE),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __iwl_mvm_mac_set_key(काष्ठा ieee80211_hw *hw,
				 क्रमागत set_key_cmd cmd,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta,
				 काष्ठा ieee80211_key_conf *key);

अटल व्योम iwl_mvm_reset_phy_ctxts(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक i;

	स_रखो(mvm->phy_ctxts, 0, माप(mvm->phy_ctxts));
	क्रम (i = 0; i < NUM_PHY_CTX; i++) अणु
		mvm->phy_ctxts[i].id = i;
		mvm->phy_ctxts[i].ref = 0;
	पूर्ण
पूर्ण

काष्ठा ieee80211_regकरोमुख्य *iwl_mvm_get_regकरोमुख्य(काष्ठा wiphy *wiphy,
						  स्थिर अक्षर *alpha2,
						  क्रमागत iwl_mcc_source src_id,
						  bool *changed)
अणु
	काष्ठा ieee80211_regकरोमुख्य *regd = शून्य;
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mcc_update_resp *resp;
	u8 resp_ver;

	IWL_DEBUG_LAR(mvm, "Getting regdomain data for %s from FW\n", alpha2);

	lockdep_निश्चित_held(&mvm->mutex);

	resp = iwl_mvm_update_mcc(mvm, alpha2, src_id);
	अगर (IS_ERR_OR_शून्य(resp)) अणु
		IWL_DEBUG_LAR(mvm, "Could not get update from FW %d\n",
			      PTR_ERR_OR_ZERO(resp));
		जाओ out;
	पूर्ण

	अगर (changed) अणु
		u32 status = le32_to_cpu(resp->status);

		*changed = (status == MCC_RESP_NEW_CHAN_PROखाता ||
			    status == MCC_RESP_ILLEGAL);
	पूर्ण
	resp_ver = iwl_fw_lookup_notअगर_ver(mvm->fw, IWL_ALWAYS_LONG_GROUP,
					   MCC_UPDATE_CMD, 0);
	IWL_DEBUG_LAR(mvm, "MCC update response version: %d\n", resp_ver);

	regd = iwl_parse_nvm_mcc_info(mvm->trans->dev, mvm->cfg,
				      __le32_to_cpu(resp->n_channels),
				      resp->channels,
				      __le16_to_cpu(resp->mcc),
				      __le16_to_cpu(resp->geo_info),
				      __le16_to_cpu(resp->cap), resp_ver);
	/* Store the वापस source id */
	src_id = resp->source_id;
	kमुक्त(resp);
	अगर (IS_ERR_OR_शून्य(regd)) अणु
		IWL_DEBUG_LAR(mvm, "Could not get parse update from FW %d\n",
			      PTR_ERR_OR_ZERO(regd));
		जाओ out;
	पूर्ण

	IWL_DEBUG_LAR(mvm, "setting alpha2 from FW to %s (0x%x, 0x%x) src=%d\n",
		      regd->alpha2, regd->alpha2[0], regd->alpha2[1], src_id);
	mvm->lar_regकरोm_set = true;
	mvm->mcc_src = src_id;

out:
	वापस regd;
पूर्ण

व्योम iwl_mvm_update_changed_regकरोm(काष्ठा iwl_mvm *mvm)
अणु
	bool changed;
	काष्ठा ieee80211_regकरोमुख्य *regd;

	अगर (!iwl_mvm_is_lar_supported(mvm))
		वापस;

	regd = iwl_mvm_get_current_regकरोमुख्य(mvm, &changed);
	अगर (!IS_ERR_OR_शून्य(regd)) अणु
		/* only update the regulatory core अगर changed */
		अगर (changed)
			regulatory_set_wiphy_regd(mvm->hw->wiphy, regd);

		kमुक्त(regd);
	पूर्ण
पूर्ण

काष्ठा ieee80211_regकरोमुख्य *iwl_mvm_get_current_regकरोमुख्य(काष्ठा iwl_mvm *mvm,
							  bool *changed)
अणु
	वापस iwl_mvm_get_regकरोमुख्य(mvm->hw->wiphy, "ZZ",
				     iwl_mvm_is_wअगरi_mcc_supported(mvm) ?
				     MCC_SOURCE_GET_CURRENT :
				     MCC_SOURCE_OLD_FW, changed);
पूर्ण

पूर्णांक iwl_mvm_init_fw_regd(काष्ठा iwl_mvm *mvm)
अणु
	क्रमागत iwl_mcc_source used_src;
	काष्ठा ieee80211_regकरोमुख्य *regd;
	पूर्णांक ret;
	bool changed;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *r =
			wiphy_dereference(mvm->hw->wiphy, mvm->hw->wiphy->regd);

	अगर (!r)
		वापस -ENOENT;

	/* save the last source in हाल we overग_लिखो it below */
	used_src = mvm->mcc_src;
	अगर (iwl_mvm_is_wअगरi_mcc_supported(mvm)) अणु
		/* Notअगरy the firmware we support wअगरi location updates */
		regd = iwl_mvm_get_current_regकरोमुख्य(mvm, शून्य);
		अगर (!IS_ERR_OR_शून्य(regd))
			kमुक्त(regd);
	पूर्ण

	/* Now set our last stored MCC and source */
	regd = iwl_mvm_get_regकरोमुख्य(mvm->hw->wiphy, r->alpha2, used_src,
				     &changed);
	अगर (IS_ERR_OR_शून्य(regd))
		वापस -EIO;

	/* update cfg80211 अगर the regकरोमुख्य was changed */
	अगर (changed)
		ret = regulatory_set_wiphy_regd_sync(mvm->hw->wiphy, regd);
	अन्यथा
		ret = 0;

	kमुक्त(regd);
	वापस ret;
पूर्ण

अटल स्थिर u8 he_अगर_types_ext_capa_sta[] = अणु
	 [0] = WLAN_EXT_CAPA1_EXT_CHANNEL_SWITCHING,
	 [2] = WLAN_EXT_CAPA3_MULTI_BSSID_SUPPORT,
	 [7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
	 [9] = WLAN_EXT_CAPA10_TWT_REQUESTER_SUPPORT,
पूर्ण;

अटल स्थिर काष्ठा wiphy_अगरtype_ext_capab he_अगरtypes_ext_capa[] = अणु
	अणु
		.अगरtype = NL80211_IFTYPE_STATION,
		.extended_capabilities = he_अगर_types_ext_capa_sta,
		.extended_capabilities_mask = he_अगर_types_ext_capa_sta,
		.extended_capabilities_len = माप(he_अगर_types_ext_capa_sta),
	पूर्ण,
पूर्ण;

अटल पूर्णांक
iwl_mvm_op_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	*tx_ant = iwl_mvm_get_valid_tx_ant(mvm);
	*rx_ant = iwl_mvm_get_valid_rx_ant(mvm);
	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_mac_setup_रेजिस्टर(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा ieee80211_hw *hw = mvm->hw;
	पूर्णांक num_mac, ret, i;
	अटल स्थिर u32 mvm_ciphers[] = अणु
		WLAN_CIPHER_SUITE_WEP40,
		WLAN_CIPHER_SUITE_WEP104,
		WLAN_CIPHER_SUITE_TKIP,
		WLAN_CIPHER_SUITE_CCMP,
	पूर्ण;
#अगर_घोषित CONFIG_PM_SLEEP
	bool unअगरied = fw_has_capa(&mvm->fw->ucode_capa,
				   IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);
#पूर्ण_अगर

	/* Tell mac80211 our अक्षरacteristics */
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, SPECTRUM_MGMT);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, WANT_MONITOR_VIF);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, TIMING_BEACON_ONLY);
	ieee80211_hw_set(hw, CONNECTION_MONITOR);
	ieee80211_hw_set(hw, CHANCTX_STA_CSA);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPORTS_CLONED_SKBS);
	ieee80211_hw_set(hw, SUPPORTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, NEEDS_UNIQUE_STA_ADDR);
	ieee80211_hw_set(hw, DEAUTH_NEED_MGD_TX_PREP);
	ieee80211_hw_set(hw, SUPPORTS_VHT_EXT_NSS_BW);
	ieee80211_hw_set(hw, BUFF_MMPDU_TXQ);
	ieee80211_hw_set(hw, STA_MMPDU_TXQ);
	/*
	 * On older devices, enabling TX A-MSDU occasionally leads to
	 * something getting messed up, the command पढ़ो from the FIFO
	 * माला_लो out of sync and isn't a TX command, so that we have an
	 * निश्चित EDC.
	 *
	 * It's not clear where the bug is, but since we didn't used to
	 * support A-MSDU until moving the mac80211 iTXQs, just leave it
	 * क्रम older devices. We also करोn't see this issue on any newer
	 * devices.
	 */
	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_9000)
		ieee80211_hw_set(hw, TX_AMSDU);
	ieee80211_hw_set(hw, TX_FRAG_LIST);

	अगर (iwl_mvm_has_tlc_offload(mvm)) अणु
		ieee80211_hw_set(hw, TX_AMPDU_SETUP_IN_HW);
		ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	पूर्ण

	अगर (iwl_mvm_has_new_rx_api(mvm))
		ieee80211_hw_set(hw, SUPPORTS_REORDERING_BUFFER);

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_STA_PM_NOTIF)) अणु
		ieee80211_hw_set(hw, AP_LINK_PS);
	पूर्ण अन्यथा अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm))) अणु
		/*
		 * we असलolutely need this क्रम the new TX API since that comes
		 * with many more queues than the current code can deal with
		 * क्रम station घातersave
		 */
		वापस -EINVAL;
	पूर्ण

	अगर (mvm->trans->num_rx_queues > 1)
		ieee80211_hw_set(hw, USES_RSS);

	अगर (mvm->trans->max_skb_frags)
		hw->netdev_features = NETIF_F_HIGHDMA | NETIF_F_SG;

	hw->queues = IEEE80211_MAX_QUEUES;
	hw->offchannel_tx_hw_queue = IWL_MVM_OFFCHANNEL_QUEUE;
	hw->radiotap_mcs_details |= IEEE80211_RADIOTAP_MCS_HAVE_FEC |
				    IEEE80211_RADIOTAP_MCS_HAVE_STBC;
	hw->radiotap_vht_details |= IEEE80211_RADIOTAP_VHT_KNOWN_STBC |
		IEEE80211_RADIOTAP_VHT_KNOWN_BEAMFORMED;

	hw->radiotap_बारtamp.units_pos =
		IEEE80211_RADIOTAP_TIMESTAMP_UNIT_US |
		IEEE80211_RADIOTAP_TIMESTAMP_SPOS_PLCP_SIG_ACQ;
	/* this is the हाल क्रम CCK frames, it's better (only 8) क्रम OFDM */
	hw->radiotap_बारtamp.accuracy = 22;

	अगर (!iwl_mvm_has_tlc_offload(mvm))
		hw->rate_control_algorithm = RS_NAME;

	hw->uapsd_queues = IWL_MVM_UAPSD_QUEUES;
	hw->uapsd_max_sp_len = IWL_UAPSD_MAX_SP;
	hw->max_tx_fragments = mvm->trans->max_skb_frags;

	BUILD_BUG_ON(ARRAY_SIZE(mvm->ciphers) < ARRAY_SIZE(mvm_ciphers) + 6);
	स_नकल(mvm->ciphers, mvm_ciphers, माप(mvm_ciphers));
	hw->wiphy->n_cipher_suites = ARRAY_SIZE(mvm_ciphers);
	hw->wiphy->cipher_suites = mvm->ciphers;

	अगर (iwl_mvm_has_new_rx_api(mvm)) अणु
		mvm->ciphers[hw->wiphy->n_cipher_suites] =
			WLAN_CIPHER_SUITE_GCMP;
		hw->wiphy->n_cipher_suites++;
		mvm->ciphers[hw->wiphy->n_cipher_suites] =
			WLAN_CIPHER_SUITE_GCMP_256;
		hw->wiphy->n_cipher_suites++;
	पूर्ण

	अगर (iwlwअगरi_mod_params.swcrypto)
		IWL_ERR(mvm,
			"iwlmvm doesn't allow to disable HW crypto, check swcrypto module parameter\n");
	अगर (!iwlwअगरi_mod_params.bt_coex_active)
		IWL_ERR(mvm,
			"iwlmvm doesn't allow to disable BT Coex, check bt_coex_active module parameter\n");

	ieee80211_hw_set(hw, MFP_CAPABLE);
	mvm->ciphers[hw->wiphy->n_cipher_suites] = WLAN_CIPHER_SUITE_AES_CMAC;
	hw->wiphy->n_cipher_suites++;
	अगर (iwl_mvm_has_new_rx_api(mvm)) अणु
		mvm->ciphers[hw->wiphy->n_cipher_suites] =
			WLAN_CIPHER_SUITE_BIP_GMAC_128;
		hw->wiphy->n_cipher_suites++;
		mvm->ciphers[hw->wiphy->n_cipher_suites] =
			WLAN_CIPHER_SUITE_BIP_GMAC_256;
		hw->wiphy->n_cipher_suites++;
	पूर्ण

	/* currently FW API supports only one optional cipher scheme */
	अगर (mvm->fw->cs[0].cipher) अणु
		स्थिर काष्ठा iwl_fw_cipher_scheme *fwcs = &mvm->fw->cs[0];
		काष्ठा ieee80211_cipher_scheme *cs = &mvm->cs[0];

		mvm->hw->n_cipher_schemes = 1;

		cs->cipher = le32_to_cpu(fwcs->cipher);
		cs->अगरtype = BIT(NL80211_IFTYPE_STATION);
		cs->hdr_len = fwcs->hdr_len;
		cs->pn_len = fwcs->pn_len;
		cs->pn_off = fwcs->pn_off;
		cs->key_idx_off = fwcs->key_idx_off;
		cs->key_idx_mask = fwcs->key_idx_mask;
		cs->key_idx_shअगरt = fwcs->key_idx_shअगरt;
		cs->mic_len = fwcs->mic_len;

		mvm->hw->cipher_schemes = mvm->cs;
		mvm->ciphers[hw->wiphy->n_cipher_suites] = cs->cipher;
		hw->wiphy->n_cipher_suites++;
	पूर्ण

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_FTM_CALIBRATED)) अणु
		wiphy_ext_feature_set(hw->wiphy,
				      NL80211_EXT_FEATURE_ENABLE_FTM_RESPONDER);
		hw->wiphy->pmsr_capa = &iwl_mvm_pmsr_capa;
	पूर्ण

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_BIGTK_SUPPORT))
		wiphy_ext_feature_set(hw->wiphy,
				      NL80211_EXT_FEATURE_BEACON_PROTECTION_CLIENT);

	ieee80211_hw_set(hw, SINGLE_SCAN_ON_ALL_BANDS);
	hw->wiphy->features |=
		NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR |
		NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR |
		NL80211_FEATURE_ND_RANDOM_MAC_ADDR;

	hw->sta_data_size = माप(काष्ठा iwl_mvm_sta);
	hw->vअगर_data_size = माप(काष्ठा iwl_mvm_vअगर);
	hw->chanctx_data_size = माप(u16);
	hw->txq_data_size = माप(काष्ठा iwl_mvm_txq);

	hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_P2P_CLIENT) |
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_P2P_GO) |
		BIT(NL80211_IFTYPE_P2P_DEVICE) |
		BIT(NL80211_IFTYPE_ADHOC);

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;
	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_VHT_IBSS);

	/* The new Tx API करोes not allow to pass the key or keyid of a MPDU to
	 * the hw, preventing us to control which key(id) to use per MPDU.
	 * Till that's fixed we can't use Extended Key ID क्रम the newer cards.
	 */
	अगर (!iwl_mvm_has_new_tx_api(mvm))
		wiphy_ext_feature_set(hw->wiphy,
				      NL80211_EXT_FEATURE_EXT_KEY_ID);
	hw->wiphy->features |= NL80211_FEATURE_HT_IBSS;

	hw->wiphy->regulatory_flags |= REGULATORY_ENABLE_RELAX_NO_IR;
	अगर (iwl_mvm_is_lar_supported(mvm))
		hw->wiphy->regulatory_flags |= REGULATORY_WIPHY_SELF_MANAGED;
	अन्यथा
		hw->wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG |
					       REGULATORY_DISABLE_BEACON_HINTS;

	hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;
	hw->wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;
	hw->wiphy->flags |= WIPHY_FLAG_SPLIT_SCAN_6GHZ;

	hw->wiphy->अगरace_combinations = iwl_mvm_अगरace_combinations;
	hw->wiphy->n_अगरace_combinations =
		ARRAY_SIZE(iwl_mvm_अगरace_combinations);

	hw->wiphy->max_reमुख्य_on_channel_duration = 10000;
	hw->max_listen_पूर्णांकerval = IWL_CONN_MAX_LISTEN_INTERVAL;

	/* Extract MAC address */
	स_नकल(mvm->addresses[0].addr, mvm->nvm_data->hw_addr, ETH_ALEN);
	hw->wiphy->addresses = mvm->addresses;
	hw->wiphy->n_addresses = 1;

	/* Extract additional MAC addresses अगर available */
	num_mac = (mvm->nvm_data->n_hw_addrs > 1) ?
		min(IWL_MVM_MAX_ADDRESSES, mvm->nvm_data->n_hw_addrs) : 1;

	क्रम (i = 1; i < num_mac; i++) अणु
		स_नकल(mvm->addresses[i].addr, mvm->addresses[i-1].addr,
		       ETH_ALEN);
		mvm->addresses[i].addr[5]++;
		hw->wiphy->n_addresses++;
	पूर्ण

	iwl_mvm_reset_phy_ctxts(mvm);

	hw->wiphy->max_scan_ie_len = iwl_mvm_max_scan_ie_len(mvm);

	hw->wiphy->max_scan_ssids = PROBE_OPTION_MAX;

	BUILD_BUG_ON(IWL_MVM_SCAN_STOPPING_MASK & IWL_MVM_SCAN_MASK);
	BUILD_BUG_ON(IWL_MVM_MAX_UMAC_SCANS > HWEIGHT32(IWL_MVM_SCAN_MASK) ||
		     IWL_MVM_MAX_LMAC_SCANS > HWEIGHT32(IWL_MVM_SCAN_MASK));

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN))
		mvm->max_scans = IWL_MVM_MAX_UMAC_SCANS;
	अन्यथा
		mvm->max_scans = IWL_MVM_MAX_LMAC_SCANS;

	अगर (mvm->nvm_data->bands[NL80211_BAND_2GHZ].n_channels)
		hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&mvm->nvm_data->bands[NL80211_BAND_2GHZ];
	अगर (mvm->nvm_data->bands[NL80211_BAND_5GHZ].n_channels) अणु
		hw->wiphy->bands[NL80211_BAND_5GHZ] =
			&mvm->nvm_data->bands[NL80211_BAND_5GHZ];

		अगर (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_BEAMFORMER) &&
		    fw_has_api(&mvm->fw->ucode_capa,
			       IWL_UCODE_TLV_API_LQ_SS_PARAMS))
			hw->wiphy->bands[NL80211_BAND_5GHZ]->vht_cap.cap |=
				IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE;
	पूर्ण
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_PSC_CHAN_SUPPORT) &&
	    mvm->nvm_data->bands[NL80211_BAND_6GHZ].n_channels)
		hw->wiphy->bands[NL80211_BAND_6GHZ] =
			&mvm->nvm_data->bands[NL80211_BAND_6GHZ];

	hw->wiphy->hw_version = mvm->trans->hw_id;

	अगर (iwlmvm_mod_params.घातer_scheme != IWL_POWER_SCHEME_CAM)
		hw->wiphy->flags |= WIPHY_FLAG_PS_ON_BY_DEFAULT;
	अन्यथा
		hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->max_sched_scan_reqs = 1;
	hw->wiphy->max_sched_scan_ssids = PROBE_OPTION_MAX;
	hw->wiphy->max_match_sets = iwl_umac_scan_get_max_profiles(mvm->fw);
	/* we create the 802.11 header and zero length SSID IE. */
	hw->wiphy->max_sched_scan_ie_len =
		SCAN_OFFLOAD_PROBE_REQ_SIZE - 24 - 2;
	hw->wiphy->max_sched_scan_plans = IWL_MAX_SCHED_SCAN_PLANS;
	hw->wiphy->max_sched_scan_plan_पूर्णांकerval = U16_MAX;

	/*
	 * the firmware uses u8 क्रम num of iterations, but 0xff is saved क्रम
	 * infinite loop, so the maximum number of iterations is actually 254.
	 */
	hw->wiphy->max_sched_scan_plan_iterations = 254;

	hw->wiphy->features |= NL80211_FEATURE_P2P_GO_CTWIN |
			       NL80211_FEATURE_LOW_PRIORITY_SCAN |
			       NL80211_FEATURE_P2P_GO_OPPPS |
			       NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE |
			       NL80211_FEATURE_DYNAMIC_SMPS |
			       NL80211_FEATURE_STATIC_SMPS |
			       NL80211_FEATURE_SUPPORTS_WMM_ADMISSION;

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_TXPOWER_INSERTION_SUPPORT))
		hw->wiphy->features |= NL80211_FEATURE_TX_POWER_INSERTION;
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_QUIET_PERIOD_SUPPORT))
		hw->wiphy->features |= NL80211_FEATURE_QUIET;

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_DS_PARAM_SET_IE_SUPPORT))
		hw->wiphy->features |=
			NL80211_FEATURE_DS_PARAM_SET_IE_IN_PROBES;

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_WFA_TPC_REP_IE_SUPPORT))
		hw->wiphy->features |= NL80211_FEATURE_WFA_TPC_IE_IN_PROBES;

	अगर (iwl_fw_lookup_cmd_ver(mvm->fw, IWL_ALWAYS_LONG_GROUP,
				  WOWLAN_KEK_KCK_MATERIAL,
				  IWL_FW_CMD_VER_UNKNOWN) == 3)
		hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_EXT_KEK_KCK;

	अगर (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_SCAN_TSF_REPORT)) अणु
		wiphy_ext_feature_set(hw->wiphy,
				      NL80211_EXT_FEATURE_SCAN_START_TIME);
		wiphy_ext_feature_set(hw->wiphy,
				      NL80211_EXT_FEATURE_BSS_PARENT_TSF);
	पूर्ण

	अगर (iwl_mvm_is_oce_supported(mvm)) अणु
		wiphy_ext_feature_set(hw->wiphy,
			NL80211_EXT_FEATURE_ACCEPT_BCAST_PROBE_RESP);
		wiphy_ext_feature_set(hw->wiphy,
			NL80211_EXT_FEATURE_FILS_MAX_CHANNEL_TIME);
		wiphy_ext_feature_set(hw->wiphy,
			NL80211_EXT_FEATURE_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION);
		wiphy_ext_feature_set(hw->wiphy,
			NL80211_EXT_FEATURE_OCE_PROBE_REQ_HIGH_TX_RATE);
	पूर्ण

	अगर (mvm->nvm_data->sku_cap_11ax_enable &&
	    !iwlwअगरi_mod_params.disable_11ax) अणु
		hw->wiphy->अगरtype_ext_capab = he_अगरtypes_ext_capa;
		hw->wiphy->num_अगरtype_ext_capab =
			ARRAY_SIZE(he_अगरtypes_ext_capa);

		ieee80211_hw_set(hw, SUPPORTS_MULTI_BSSID);
		ieee80211_hw_set(hw, SUPPORTS_ONLY_HE_MULTI_BSSID);
	पूर्ण

	mvm->rts_threshold = IEEE80211_MAX_RTS_THRESHOLD;

#अगर_घोषित CONFIG_PM_SLEEP
	अगर ((unअगरied || mvm->fw->img[IWL_UCODE_WOWLAN].num_sec) &&
	    mvm->trans->ops->d3_suspend &&
	    mvm->trans->ops->d3_resume &&
	    device_can_wakeup(mvm->trans->dev)) अणु
		mvm->wowlan.flags |= WIPHY_WOWLAN_MAGIC_PKT |
				     WIPHY_WOWLAN_DISCONNECT |
				     WIPHY_WOWLAN_EAP_IDENTITY_REQ |
				     WIPHY_WOWLAN_RFKILL_RELEASE |
				     WIPHY_WOWLAN_NET_DETECT;
		mvm->wowlan.flags |= WIPHY_WOWLAN_SUPPORTS_GTK_REKEY |
				     WIPHY_WOWLAN_GTK_REKEY_FAILURE |
				     WIPHY_WOWLAN_4WAY_HANDSHAKE;

		mvm->wowlan.n_patterns = IWL_WOWLAN_MAX_PATTERNS;
		mvm->wowlan.pattern_min_len = IWL_WOWLAN_MIN_PATTERN_LEN;
		mvm->wowlan.pattern_max_len = IWL_WOWLAN_MAX_PATTERN_LEN;
		mvm->wowlan.max_nd_match_sets =
			iwl_umac_scan_get_max_profiles(mvm->fw);
		hw->wiphy->wowlan = &mvm->wowlan;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IWLWIFI_BCAST_FILTERING
	/* assign शेष bcast filtering configuration */
	mvm->bcast_filters = iwl_mvm_शेष_bcast_filters;
#पूर्ण_अगर

	ret = iwl_mvm_leds_init(mvm);
	अगर (ret)
		वापस ret;

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_TDLS_SUPPORT)) अणु
		IWL_DEBUG_TDLS(mvm, "TDLS supported\n");
		hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS;
		ieee80211_hw_set(hw, TDLS_WIDER_BW);
	पूर्ण

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_TDLS_CHANNEL_SWITCH)) अणु
		IWL_DEBUG_TDLS(mvm, "TDLS channel switch supported\n");
		hw->wiphy->features |= NL80211_FEATURE_TDLS_CHANNEL_SWITCH;
	पूर्ण

	hw->netdev_features |= mvm->cfg->features;
	अगर (!iwl_mvm_is_csum_supported(mvm))
		hw->netdev_features &= ~(IWL_TX_CSUM_NETIF_FLAGS |
					 NETIF_F_RXCSUM);

	अगर (mvm->cfg->vht_mu_mimo_supported)
		wiphy_ext_feature_set(hw->wiphy,
				      NL80211_EXT_FEATURE_MU_MIMO_AIR_SNIFFER);

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_PROTECTED_TWT))
		wiphy_ext_feature_set(hw->wiphy,
				      NL80211_EXT_FEATURE_PROTECTED_TWT);

	hw->wiphy->available_antennas_tx = iwl_mvm_get_valid_tx_ant(mvm);
	hw->wiphy->available_antennas_rx = iwl_mvm_get_valid_rx_ant(mvm);

	ret = ieee80211_रेजिस्टर_hw(mvm->hw);
	अगर (ret) अणु
		iwl_mvm_leds_निकास(mvm);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_tx_skb(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			   काष्ठा ieee80211_sta *sta)
अणु
	अगर (likely(sta)) अणु
		अगर (likely(iwl_mvm_tx_skb_sta(mvm, skb, sta) == 0))
			वापस;
	पूर्ण अन्यथा अणु
		अगर (likely(iwl_mvm_tx_skb_non_sta(mvm, skb) == 0))
			वापस;
	पूर्ण

	ieee80211_मुक्त_txskb(mvm->hw, skb);
पूर्ण

अटल व्योम iwl_mvm_mac_tx(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_tx_control *control,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा ieee80211_sta *sta = control->sta;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	bool offchannel = IEEE80211_SKB_CB(skb)->flags &
		IEEE80211_TX_CTL_TX_OFFCHAN;

	अगर (iwl_mvm_is_radio_समाप्तed(mvm)) अणु
		IWL_DEBUG_DROP(mvm, "Dropping - RF/CT KILL\n");
		जाओ drop;
	पूर्ण

	अगर (offchannel &&
	    !test_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status) &&
	    !test_bit(IWL_MVM_STATUS_ROC_AUX_RUNNING, &mvm->status))
		जाओ drop;

	/* treat non-bufferable MMPDUs on AP पूर्णांकerfaces as broadcast */
	अगर ((info->control.vअगर->type == NL80211_IFTYPE_AP ||
	     info->control.vअगर->type == NL80211_IFTYPE_ADHOC) &&
	    ieee80211_is_mgmt(hdr->frame_control) &&
	    !ieee80211_is_bufferable_mmpdu(hdr->frame_control))
		sta = शून्य;

	/* If there is no sta, and it's not offchannel - send through AP */
	अगर (!sta && info->control.vअगर->type == NL80211_IFTYPE_STATION &&
	    !offchannel) अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर =
			iwl_mvm_vअगर_from_mac80211(info->control.vअगर);
		u8 ap_sta_id = READ_ONCE(mvmvअगर->ap_sta_id);

		अगर (ap_sta_id < mvm->fw->ucode_capa.num_stations) अणु
			/* mac80211 holds rcu पढ़ो lock */
			sta = rcu_dereference(mvm->fw_id_to_mac_id[ap_sta_id]);
			अगर (IS_ERR_OR_शून्य(sta))
				जाओ drop;
		पूर्ण
	पूर्ण

	iwl_mvm_tx_skb(mvm, skb, sta);
	वापस;
 drop:
	ieee80211_मुक्त_txskb(hw, skb);
पूर्ण

व्योम iwl_mvm_mac_itxq_xmit(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_txq *mvmtxq = iwl_mvm_txq_from_mac80211(txq);
	काष्ठा sk_buff *skb = शून्य;

	/*
	 * No need क्रम thपढ़ोs to be pending here, they can leave the first
	 * taker all the work.
	 *
	 * mvmtxq->tx_request logic:
	 *
	 * If 0, no one is currently TXing, set to 1 to indicate current thपढ़ो
	 * will now start TX and other thपढ़ोs should quit.
	 *
	 * If 1, another thपढ़ो is currently TXing, set to 2 to indicate to
	 * that thपढ़ो that there was another request. Since that request may
	 * have raced with the check whether the queue is empty, the TXing
	 * thपढ़ो should check the queue's status one more समय beक्रमe leaving.
	 * This check is करोne in order to not leave any TX hanging in the queue
	 * until the next TX invocation (which may not even happen).
	 *
	 * If 2, another thपढ़ो is currently TXing, and it will alपढ़ोy द्विगुन
	 * check the queue, so करो nothing.
	 */
	अगर (atomic_fetch_add_unless(&mvmtxq->tx_request, 1, 2))
		वापस;

	rcu_पढ़ो_lock();
	करो अणु
		जबतक (likely(!mvmtxq->stopped &&
			      !test_bit(IWL_MVM_STATUS_IN_D3, &mvm->status))) अणु
			skb = ieee80211_tx_dequeue(hw, txq);

			अगर (!skb) अणु
				अगर (txq->sta)
					IWL_DEBUG_TX(mvm,
						     "TXQ of sta %pM tid %d is now empty\n",
						     txq->sta->addr,
						     txq->tid);
				अवरोध;
			पूर्ण

			iwl_mvm_tx_skb(mvm, skb, txq->sta);
		पूर्ण
	पूर्ण जबतक (atomic_dec_वापस(&mvmtxq->tx_request));
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम iwl_mvm_mac_wake_tx_queue(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_txq *mvmtxq = iwl_mvm_txq_from_mac80211(txq);

	/*
	 * Please note that racing is handled very carefully here:
	 * mvmtxq->txq_id is updated during allocation, and mvmtxq->list is
	 * deleted afterwards.
	 * This means that अगर:
	 * mvmtxq->txq_id != INVALID_QUEUE && list_empty(&mvmtxq->list):
	 *	queue is allocated and we can TX.
	 * mvmtxq->txq_id != INVALID_QUEUE && !list_empty(&mvmtxq->list):
	 *	a race, should defer the frame.
	 * mvmtxq->txq_id == INVALID_QUEUE && list_empty(&mvmtxq->list):
	 *	need to allocate the queue and defer the frame.
	 * mvmtxq->txq_id == INVALID_QUEUE && !list_empty(&mvmtxq->list):
	 *	queue is alपढ़ोy scheduled क्रम allocation, no need to allocate,
	 *	should defer the frame.
	 */

	/* If the queue is allocated TX and वापस. */
	अगर (!txq->sta || mvmtxq->txq_id != IWL_MVM_INVALID_QUEUE) अणु
		/*
		 * Check that list is empty to aव्योम a race where txq_id is
		 * alपढ़ोy updated, but the queue allocation work wasn't
		 * finished
		 */
		अगर (unlikely(txq->sta && !list_empty(&mvmtxq->list)))
			वापस;

		iwl_mvm_mac_itxq_xmit(hw, txq);
		वापस;
	पूर्ण

	/* The list is being deleted only after the queue is fully allocated. */
	अगर (!list_empty(&mvmtxq->list))
		वापस;

	list_add_tail(&mvmtxq->list, &mvm->add_stream_txqs);
	schedule_work(&mvm->add_stream_wk);
पूर्ण

#घोषणा CHECK_BA_TRIGGER(_mvm, _trig, _tid_bm, _tid, _fmt...)		\
	करो अणु								\
		अगर (!(le16_to_cpu(_tid_bm) & BIT(_tid)))		\
			अवरोध;						\
		iwl_fw_dbg_collect_trig(&(_mvm)->fwrt, _trig, _fmt);	\
	पूर्ण जबतक (0)

अटल व्योम
iwl_mvm_ampdu_check_trigger(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, u16 tid, u16 rx_ba_ssn,
			    क्रमागत ieee80211_ampdu_mlme_action action)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_ba *ba_trig;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vअगर_to_wdev(vअगर),
				     FW_DBG_TRIGGER_BA);
	अगर (!trig)
		वापस;

	ba_trig = (व्योम *)trig->data;

	चयन (action) अणु
	हाल IEEE80211_AMPDU_TX_OPERATIONAL: अणु
		काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
		काष्ठा iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];

		CHECK_BA_TRIGGER(mvm, trig, ba_trig->tx_ba_start, tid,
				 "TX AGG START: MAC %pM tid %d ssn %d\n",
				 sta->addr, tid, tid_data->ssn);
		अवरोध;
		पूर्ण
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		CHECK_BA_TRIGGER(mvm, trig, ba_trig->tx_ba_stop, tid,
				 "TX AGG STOP: MAC %pM tid %d\n",
				 sta->addr, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_START:
		CHECK_BA_TRIGGER(mvm, trig, ba_trig->rx_ba_start, tid,
				 "RX AGG START: MAC %pM tid %d ssn %d\n",
				 sta->addr, tid, rx_ba_ssn);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		CHECK_BA_TRIGGER(mvm, trig, ba_trig->rx_ba_stop, tid,
				 "RX AGG STOP: MAC %pM tid %d\n",
				 sta->addr, tid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ampdu_action(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;
	u16 buf_size = params->buf_size;
	bool amsdu = params->amsdu;
	u16 समयout = params->समयout;

	IWL_DEBUG_HT(mvm, "A-MPDU action on addr %pM tid %d: action %d\n",
		     sta->addr, tid, action);

	अगर (!(mvm->nvm_data->sku_cap_11n_enable))
		वापस -EACCES;

	mutex_lock(&mvm->mutex);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		अगर (iwl_mvm_vअगर_from_mac80211(vअगर)->ap_sta_id ==
				iwl_mvm_sta_from_mac80211(sta)->sta_id) अणु
			काष्ठा iwl_mvm_vअगर *mvmvअगर;
			u16 macid = iwl_mvm_vअगर_from_mac80211(vअगर)->id;
			काष्ठा iwl_mvm_tcm_mac *mdata = &mvm->tcm.data[macid];

			mdata->खोलोed_rx_ba_sessions = true;
			mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
			cancel_delayed_work(&mvmvअगर->uapsd_nonagg_detected_wk);
		पूर्ण
		अगर (!iwl_enable_rx_ampdu()) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = iwl_mvm_sta_rx_agg(mvm, sta, tid, *ssn, true, buf_size,
					 समयout);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		ret = iwl_mvm_sta_rx_agg(mvm, sta, tid, 0, false, buf_size,
					 समयout);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		अगर (!iwl_enable_tx_ampdu()) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = iwl_mvm_sta_tx_agg_start(mvm, vअगर, sta, tid, ssn);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		ret = iwl_mvm_sta_tx_agg_stop(mvm, vअगर, sta, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		ret = iwl_mvm_sta_tx_agg_flush(mvm, vअगर, sta, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		ret = iwl_mvm_sta_tx_agg_oper(mvm, vअगर, sta, tid,
					      buf_size, amsdu);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		u16 rx_ba_ssn = 0;

		अगर (action == IEEE80211_AMPDU_RX_START)
			rx_ba_ssn = *ssn;

		iwl_mvm_ampdu_check_trigger(mvm, vअगर, sta, tid,
					    rx_ba_ssn, action);
	पूर्ण
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_cleanup_iterator(व्योम *data, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	mvmvअगर->uploaded = false;
	mvmvअगर->ap_sta_id = IWL_MVM_INVALID_STA;

	spin_lock_bh(&mvm->समय_event_lock);
	iwl_mvm_te_clear_data(mvm, &mvmvअगर->समय_event_data);
	spin_unlock_bh(&mvm->समय_event_lock);

	mvmvअगर->phy_ctxt = शून्य;
	स_रखो(&mvmvअगर->bf_data, 0, माप(mvmvअगर->bf_data));
	स_रखो(&mvmvअगर->probe_resp_data, 0, माप(mvmvअगर->probe_resp_data));
पूर्ण

अटल व्योम iwl_mvm_restart_cleanup(काष्ठा iwl_mvm *mvm)
अणु
	iwl_mvm_stop_device(mvm);

	mvm->cur_aid = 0;

	mvm->scan_status = 0;
	mvm->ps_disabled = false;
	mvm->rfसमाप्त_safe_init_करोne = false;

	/* just in हाल one was running */
	iwl_mvm_cleanup_roc_te(mvm);
	ieee80211_reमुख्य_on_channel_expired(mvm->hw);

	iwl_mvm_fपंचांग_restart(mvm);

	/*
	 * cleanup all पूर्णांकerfaces, even inactive ones, as some might have
	 * gone करोwn during the HW restart
	 */
	ieee80211_iterate_पूर्णांकerfaces(mvm->hw, 0, iwl_mvm_cleanup_iterator, mvm);

	mvm->p2p_device_vअगर = शून्य;

	iwl_mvm_reset_phy_ctxts(mvm);
	स_रखो(mvm->fw_key_table, 0, माप(mvm->fw_key_table));
	स_रखो(&mvm->last_bt_notअगर, 0, माप(mvm->last_bt_notअगर));
	स_रखो(&mvm->last_bt_ci_cmd, 0, माप(mvm->last_bt_ci_cmd));

	ieee80211_wake_queues(mvm->hw);

	mvm->vअगर_count = 0;
	mvm->rx_ba_sessions = 0;
	mvm->fwrt.dump.conf = FW_DBG_INVALID;
	mvm->monitor_on = false;

	/* keep statistics ticking */
	iwl_mvm_accu_radio_stats(mvm);
पूर्ण

पूर्णांक __iwl_mvm_mac_start(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status)) अणु
		/*
		 * Now convert the HW_RESTART_REQUESTED flag to IN_HW_RESTART
		 * so later code will - from now on - see that we're करोing it.
		 */
		set_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);
		clear_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status);
		/* Clean up some पूर्णांकernal and mac80211 state on restart */
		iwl_mvm_restart_cleanup(mvm);
	पूर्ण
	ret = iwl_mvm_up(mvm);

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, IWL_FW_INI_TIME_POINT_POST_INIT,
			       शून्य);
	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt, IWL_FW_INI_TIME_POINT_PERIODIC,
			       शून्य);

	mvm->last_reset_or_resume_समय_jअगरfies = jअगरfies;

	अगर (ret && test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) अणु
		/* Something went wrong - we need to finish some cleanup
		 * that normally iwl_mvm_mac_restart_complete() below
		 * would करो.
		 */
		clear_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_mac_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);
	ret = __iwl_mvm_mac_start(mvm);
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_restart_complete(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);

	clear_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);

	ret = iwl_mvm_update_quotas(mvm, true, शून्य);
	अगर (ret)
		IWL_ERR(mvm, "Failed to update quotas after restart (%d)\n",
			ret);

	iwl_mvm_send_recovery_cmd(mvm, ERROR_RECOVERY_END_OF_RECOVERY);

	/*
	 * If we have TDLS peers, हटाओ them. We करोn't know the last seqno/PN
	 * of packets the FW sent out, so we must reconnect.
	 */
	iwl_mvm_tearकरोwn_tdls_peers(mvm);

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम
iwl_mvm_mac_reconfig_complete(काष्ठा ieee80211_hw *hw,
			      क्रमागत ieee80211_reconfig_type reconfig_type)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	चयन (reconfig_type) अणु
	हाल IEEE80211_RECONFIG_TYPE_RESTART:
		iwl_mvm_restart_complete(mvm);
		अवरोध;
	हाल IEEE80211_RECONFIG_TYPE_SUSPEND:
		अवरोध;
	पूर्ण
पूर्ण

व्योम __iwl_mvm_mac_stop(काष्ठा iwl_mvm *mvm)
अणु
	lockdep_निश्चित_held(&mvm->mutex);

	iwl_mvm_fपंचांग_initiator_smooth_stop(mvm);

	/* firmware counters are obviously reset now, but we shouldn't
	 * partially track so also clear the fw_reset_accu counters.
	 */
	स_रखो(&mvm->accu_radio_stats, 0, माप(mvm->accu_radio_stats));

	/* async_handlers_wk is now blocked */

	अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP, ADD_STA, 0) < 12)
		iwl_mvm_rm_aux_sta(mvm);

	iwl_mvm_stop_device(mvm);

	iwl_mvm_async_handlers_purge(mvm);
	/* async_handlers_list is empty and will stay empty: HW is stopped */

	/*
	 * Clear IN_HW_RESTART and HW_RESTART_REQUESTED flag when stopping the
	 * hw (as restart_complete() won't be called in this हाल) and mac80211
	 * won't execute the restart.
	 * But make sure to cleanup पूर्णांकerfaces that have gone करोwn beक्रमe/during
	 * HW restart was requested.
	 */
	अगर (test_and_clear_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) ||
	    test_and_clear_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED,
			       &mvm->status))
		ieee80211_iterate_पूर्णांकerfaces(mvm->hw, 0,
					     iwl_mvm_cleanup_iterator, mvm);

	/* We shouldn't have any UIDs still set.  Loop over all the UIDs to
	 * make sure there's nothing left there and warn अगर any is found.
	 */
	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < mvm->max_scans; i++) अणु
			अगर (WARN_ONCE(mvm->scan_uid_status[i],
				      "UMAC scan UID %d status was not cleaned\n",
				      i))
				mvm->scan_uid_status[i] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_mac_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	flush_work(&mvm->async_handlers_wk);
	flush_work(&mvm->add_stream_wk);

	/*
	 * Lock and clear the firmware running bit here alपढ़ोy, so that
	 * new commands coming in अन्यथाwhere, e.g. from debugfs, will not
	 * be able to proceed. This is important here because one of those
	 * debugfs files causes the firmware dump to be triggered, and अगर we
	 * करोn't stop debugfs accesses beक्रमe canceling that it could be
	 * retriggered after we flush it but beक्रमe we've cleared the bit.
	 */
	clear_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);

	cancel_delayed_work_sync(&mvm->cs_tx_unblock_dwork);
	cancel_delayed_work_sync(&mvm->scan_समयout_dwork);

	/*
	 * The work item could be running or queued अगर the
	 * ROC समय event stops just as we get here.
	 */
	flush_work(&mvm->roc_करोne_wk);

	mutex_lock(&mvm->mutex);
	__iwl_mvm_mac_stop(mvm);
	mutex_unlock(&mvm->mutex);

	/*
	 * The worker might have been रुकोing क्रम the mutex, let it run and
	 * discover that its list is now empty.
	 */
	cancel_work_sync(&mvm->async_handlers_wk);
पूर्ण

अटल काष्ठा iwl_mvm_phy_ctxt *iwl_mvm_get_मुक्त_phy_ctxt(काष्ठा iwl_mvm *mvm)
अणु
	u16 i;

	lockdep_निश्चित_held(&mvm->mutex);

	क्रम (i = 0; i < NUM_PHY_CTX; i++)
		अगर (!mvm->phy_ctxts[i].ref)
			वापस &mvm->phy_ctxts[i];

	IWL_ERR(mvm, "No available PHY context\n");
	वापस शून्य;
पूर्ण

अटल पूर्णांक iwl_mvm_set_tx_घातer(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				s16 tx_घातer)
अणु
	पूर्णांक len;
	काष्ठा iwl_dev_tx_घातer_cmd cmd = अणु
		.common.set_mode = cpu_to_le32(IWL_TX_POWER_MODE_SET_MAC),
		.common.mac_context_id =
			cpu_to_le32(iwl_mvm_vअगर_from_mac80211(vअगर)->id),
		.common.pwr_restriction = cpu_to_le16(8 * tx_घातer),
	पूर्ण;
	u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
					   REDUCE_TX_POWER_CMD,
					   IWL_FW_CMD_VER_UNKNOWN);

	अगर (tx_घातer == IWL_DEFAULT_MAX_TX_POWER)
		cmd.common.pwr_restriction = cpu_to_le16(IWL_DEV_MAX_TX_POWER);

	अगर (cmd_ver == 6)
		len = माप(cmd.v6);
	अन्यथा अगर (fw_has_api(&mvm->fw->ucode_capa,
			    IWL_UCODE_TLV_API_REDUCE_TX_POWER))
		len = माप(cmd.v5);
	अन्यथा अगर (fw_has_capa(&mvm->fw->ucode_capa,
			     IWL_UCODE_TLV_CAPA_TX_POWER_ACK))
		len = माप(cmd.v4);
	अन्यथा
		len = माप(cmd.v3);

	/* all काष्ठाs have the same common part, add it */
	len += माप(cmd.common);

	वापस iwl_mvm_send_cmd_pdu(mvm, REDUCE_TX_POWER_CMD, 0, len, &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_post_channel_चयन(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		काष्ठा iwl_mvm_sta *mvmsta;

		mvmvअगर->csa_bcn_pending = false;
		mvmsta = iwl_mvm_sta_from_staid_रक्षित(mvm,
							  mvmvअगर->ap_sta_id);

		अगर (WARN_ON(!mvmsta)) अणु
			ret = -EIO;
			जाओ out_unlock;
		पूर्ण

		iwl_mvm_sta_modअगरy_disable_tx(mvm, mvmsta, false);

		iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);

		अगर (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD)) अणु
			ret = iwl_mvm_enable_beacon_filter(mvm, vअगर, 0);
			अगर (ret)
				जाओ out_unlock;

			iwl_mvm_stop_session_protection(mvm, vअगर);
		पूर्ण
	पूर्ण

	mvmvअगर->ps_disabled = false;

	ret = iwl_mvm_घातer_update_ps(mvm);

out_unlock:
	अगर (mvmvअगर->csa_failed)
		ret = -EIO;
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_पात_channel_चयन(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_chan_चयन_te_cmd cmd = अणु
		.mac_id = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							  mvmvअगर->color)),
		.action = cpu_to_le32(FW_CTXT_ACTION_REMOVE),
	पूर्ण;

	IWL_DEBUG_MAC80211(mvm, "Abort CSA on mac %d\n", mvmvअगर->id);

	mutex_lock(&mvm->mutex);
	अगर (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD))
		iwl_mvm_हटाओ_csa_period(mvm, vअगर);
	अन्यथा
		WARN_ON(iwl_mvm_send_cmd_pdu(mvm,
					     WIDE_ID(MAC_CONF_GROUP,
						     CHANNEL_SWITCH_TIME_EVENT_CMD),
					     0, माप(cmd), &cmd));
	mvmvअगर->csa_failed = true;
	mutex_unlock(&mvm->mutex);

	iwl_mvm_post_channel_चयन(hw, vअगर);
पूर्ण

अटल व्योम iwl_mvm_channel_चयन_disconnect_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	काष्ठा ieee80211_vअगर *vअगर;

	mvmvअगर = container_of(wk, काष्ठा iwl_mvm_vअगर, csa_work.work);
	vअगर = container_of((व्योम *)mvmvअगर, काष्ठा ieee80211_vअगर, drv_priv);

	/* Trigger disconnect (should clear the CSA state) */
	ieee80211_chचयन_करोne(vअगर, false);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	mvmvअगर->mvm = mvm;
	RCU_INIT_POINTER(mvmvअगर->probe_resp_data, शून्य);

	/*
	 * Not much to करो here. The stack will not allow पूर्णांकerface
	 * types or combinations that we didn't advertise, so we
	 * करोn't really have to check the types.
	 */

	mutex_lock(&mvm->mutex);

	/* make sure that beacon statistics करोn't go backwards with FW reset */
	अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
		mvmvअगर->beacon_stats.accu_num_beacons +=
			mvmvअगर->beacon_stats.num_beacons;

	/* Allocate resources क्रम the MAC context, and add it to the fw  */
	ret = iwl_mvm_mac_ctxt_init(mvm, vअगर);
	अगर (ret)
		जाओ out_unlock;

	rcu_assign_poपूर्णांकer(mvm->vअगर_id_to_mac[mvmvअगर->id], vअगर);

	/* Counting number of पूर्णांकerfaces is needed क्रम legacy PM */
	अगर (vअगर->type != NL80211_IFTYPE_P2P_DEVICE)
		mvm->vअगर_count++;

	/*
	 * The AP binding flow can be करोne only after the beacon
	 * ढाँचा is configured (which happens only in the mac80211
	 * start_ap() flow), and adding the broadcast station can happen
	 * only after the binding.
	 * In addition, since modअगरying the MAC beक्रमe adding a bcast
	 * station is not allowed by the FW, delay the adding of MAC context to
	 * the poपूर्णांक where we can also add the bcast station.
	 * In लघु: there's not much we can करो at this poपूर्णांक, other than
	 * allocating resources :)
	 */
	अगर (vअगर->type == NL80211_IFTYPE_AP ||
	    vअगर->type == NL80211_IFTYPE_ADHOC) अणु
		ret = iwl_mvm_alloc_bcast_sta(mvm, vअगर);
		अगर (ret) अणु
			IWL_ERR(mvm, "Failed to allocate bcast sta\n");
			जाओ out_release;
		पूर्ण

		/*
		 * Only queue क्रम this station is the mcast queue,
		 * which shouldn't be in TFD mask anyway
		 */
		ret = iwl_mvm_allocate_पूर्णांक_sta(mvm, &mvmvअगर->mcast_sta,
					       0, vअगर->type,
					       IWL_STA_MULTICAST);
		अगर (ret)
			जाओ out_release;

		iwl_mvm_vअगर_dbgfs_रेजिस्टर(mvm, vअगर);
		जाओ out_unlock;
	पूर्ण

	mvmvअगर->features |= hw->netdev_features;

	ret = iwl_mvm_mac_ctxt_add(mvm, vअगर);
	अगर (ret)
		जाओ out_release;

	ret = iwl_mvm_घातer_update_mac(mvm);
	अगर (ret)
		जाओ out_हटाओ_mac;

	/* beacon filtering */
	ret = iwl_mvm_disable_beacon_filter(mvm, vअगर, 0);
	अगर (ret)
		जाओ out_हटाओ_mac;

	अगर (!mvm->bf_allowed_vअगर &&
	    vअगर->type == NL80211_IFTYPE_STATION && !vअगर->p2p) अणु
		mvm->bf_allowed_vअगर = mvmvअगर;
		vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER |
				     IEEE80211_VIF_SUPPORTS_CQM_RSSI;
	पूर्ण

	/*
	 * P2P_DEVICE पूर्णांकerface करोes not have a channel context asचिन्हित to it,
	 * so a dedicated PHY context is allocated to it and the corresponding
	 * MAC context is bound to it at this stage.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु

		mvmvअगर->phy_ctxt = iwl_mvm_get_मुक्त_phy_ctxt(mvm);
		अगर (!mvmvअगर->phy_ctxt) अणु
			ret = -ENOSPC;
			जाओ out_मुक्त_bf;
		पूर्ण

		iwl_mvm_phy_ctxt_ref(mvm, mvmvअगर->phy_ctxt);
		ret = iwl_mvm_binding_add_vअगर(mvm, vअगर);
		अगर (ret)
			जाओ out_unref_phy;

		ret = iwl_mvm_add_p2p_bcast_sta(mvm, vअगर);
		अगर (ret)
			जाओ out_unbind;

		/* Save a poपूर्णांकer to p2p device vअगर, so it can later be used to
		 * update the p2p device MAC when a GO is started/stopped */
		mvm->p2p_device_vअगर = vअगर;
	पूर्ण

	iwl_mvm_tcm_add_vअगर(mvm, vअगर);
	INIT_DELAYED_WORK(&mvmvअगर->csa_work,
			  iwl_mvm_channel_चयन_disconnect_wk);

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR)
		mvm->monitor_on = true;

	iwl_mvm_vअगर_dbgfs_रेजिस्टर(mvm, vअगर);
	जाओ out_unlock;

 out_unbind:
	iwl_mvm_binding_हटाओ_vअगर(mvm, vअगर);
 out_unref_phy:
	iwl_mvm_phy_ctxt_unref(mvm, mvmvअगर->phy_ctxt);
 out_मुक्त_bf:
	अगर (mvm->bf_allowed_vअगर == mvmvअगर) अणु
		mvm->bf_allowed_vअगर = शून्य;
		vअगर->driver_flags &= ~(IEEE80211_VIF_BEACON_FILTER |
				       IEEE80211_VIF_SUPPORTS_CQM_RSSI);
	पूर्ण
 out_हटाओ_mac:
	mvmvअगर->phy_ctxt = शून्य;
	iwl_mvm_mac_ctxt_हटाओ(mvm, vअगर);
 out_release:
	अगर (vअगर->type != NL80211_IFTYPE_P2P_DEVICE)
		mvm->vअगर_count--;
 out_unlock:
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_prepare_mac_removal(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
		/*
		 * Flush the ROC worker which will flush the OFFCHANNEL queue.
		 * We assume here that all the packets sent to the OFFCHANNEL
		 * queue are sent in ROC session.
		 */
		flush_work(&mvm->roc_करोne_wk);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_mac_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_probe_resp_data *probe_data;

	iwl_mvm_prepare_mac_removal(mvm, vअगर);

	अगर (!(vअगर->type == NL80211_IFTYPE_AP ||
	      vअगर->type == NL80211_IFTYPE_ADHOC))
		iwl_mvm_tcm_rm_vअगर(mvm, vअगर);

	mutex_lock(&mvm->mutex);

	probe_data = rcu_dereference_रक्षित(mvmvअगर->probe_resp_data,
					       lockdep_is_held(&mvm->mutex));
	RCU_INIT_POINTER(mvmvअगर->probe_resp_data, शून्य);
	अगर (probe_data)
		kमुक्त_rcu(probe_data, rcu_head);

	अगर (mvm->bf_allowed_vअगर == mvmvअगर) अणु
		mvm->bf_allowed_vअगर = शून्य;
		vअगर->driver_flags &= ~(IEEE80211_VIF_BEACON_FILTER |
				       IEEE80211_VIF_SUPPORTS_CQM_RSSI);
	पूर्ण

	अगर (vअगर->bss_conf.fपंचांग_responder)
		स_रखो(&mvm->fपंचांग_resp_stats, 0, माप(mvm->fपंचांग_resp_stats));

	iwl_mvm_vअगर_dbgfs_clean(mvm, vअगर);

	/*
	 * For AP/GO पूर्णांकerface, the tear करोwn of the resources allocated to the
	 * पूर्णांकerface is be handled as part of the stop_ap flow.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_AP ||
	    vअगर->type == NL80211_IFTYPE_ADHOC) अणु
#अगर_घोषित CONFIG_NL80211_TESTMODE
		अगर (vअगर == mvm->noa_vअगर) अणु
			mvm->noa_vअगर = शून्य;
			mvm->noa_duration = 0;
		पूर्ण
#पूर्ण_अगर
		iwl_mvm_dealloc_पूर्णांक_sta(mvm, &mvmvअगर->mcast_sta);
		iwl_mvm_dealloc_bcast_sta(mvm, vअगर);
		जाओ out_release;
	पूर्ण

	अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
		mvm->p2p_device_vअगर = शून्य;
		iwl_mvm_rm_p2p_bcast_sta(mvm, vअगर);
		iwl_mvm_binding_हटाओ_vअगर(mvm, vअगर);
		iwl_mvm_phy_ctxt_unref(mvm, mvmvअगर->phy_ctxt);
		mvmvअगर->phy_ctxt = शून्य;
	पूर्ण

	अगर (mvm->vअगर_count && vअगर->type != NL80211_IFTYPE_P2P_DEVICE)
		mvm->vअगर_count--;

	iwl_mvm_घातer_update_mac(mvm);
	iwl_mvm_mac_ctxt_हटाओ(mvm, vअगर);

	RCU_INIT_POINTER(mvm->vअगर_id_to_mac[mvmvअगर->id], शून्य);

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR)
		mvm->monitor_on = false;

out_release:
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	वापस 0;
पूर्ण

काष्ठा iwl_mvm_mc_iter_data अणु
	काष्ठा iwl_mvm *mvm;
	पूर्णांक port_id;
पूर्ण;

अटल व्योम iwl_mvm_mc_अगरace_iterator(व्योम *_data, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_mc_iter_data *data = _data;
	काष्ठा iwl_mvm *mvm = data->mvm;
	काष्ठा iwl_mcast_filter_cmd *cmd = mvm->mcast_filter_cmd;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = MCAST_FILTER_CMD,
		.flags = CMD_ASYNC,
		.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
	पूर्ण;
	पूर्णांक ret, len;

	/* अगर we करोn't have मुक्त ports, mcast frames will be dropped */
	अगर (WARN_ON_ONCE(data->port_id >= MAX_PORT_ID_NUM))
		वापस;

	अगर (vअगर->type != NL80211_IFTYPE_STATION ||
	    !vअगर->bss_conf.assoc)
		वापस;

	cmd->port_id = data->port_id++;
	स_नकल(cmd->bssid, vअगर->bss_conf.bssid, ETH_ALEN);
	len = roundup(माप(*cmd) + cmd->count * ETH_ALEN, 4);

	hcmd.len[0] = len;
	hcmd.data[0] = cmd;

	ret = iwl_mvm_send_cmd(mvm, &hcmd);
	अगर (ret)
		IWL_ERR(mvm, "mcast filter cmd error. ret=%d\n", ret);
पूर्ण

अटल व्योम iwl_mvm_recalc_multicast(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_mvm_mc_iter_data iter_data = अणु
		.mvm = mvm,
	पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON_ONCE(!mvm->mcast_filter_cmd))
		वापस;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_mc_अगरace_iterator, &iter_data);
पूर्ण

अटल u64 iwl_mvm_prepare_multicast(काष्ठा ieee80211_hw *hw,
				     काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mcast_filter_cmd *cmd;
	काष्ठा netdev_hw_addr *addr;
	पूर्णांक addr_count;
	bool pass_all;
	पूर्णांक len;

	addr_count = netdev_hw_addr_list_count(mc_list);
	pass_all = addr_count > MAX_MCAST_FILTERING_ADDRESSES ||
		   IWL_MVM_FW_MCAST_FILTER_PASS_ALL;
	अगर (pass_all)
		addr_count = 0;

	len = roundup(माप(*cmd) + addr_count * ETH_ALEN, 4);
	cmd = kzalloc(len, GFP_ATOMIC);
	अगर (!cmd)
		वापस 0;

	अगर (pass_all) अणु
		cmd->pass_all = 1;
		वापस (u64)(अचिन्हित दीर्घ)cmd;
	पूर्ण

	netdev_hw_addr_list_क्रम_each(addr, mc_list) अणु
		IWL_DEBUG_MAC80211(mvm, "mcast addr (%d): %pM\n",
				   cmd->count, addr->addr);
		स_नकल(&cmd->addr_list[cmd->count * ETH_ALEN],
		       addr->addr, ETH_ALEN);
		cmd->count++;
	पूर्ण

	वापस (u64)(अचिन्हित दीर्घ)cmd;
पूर्ण

अटल व्योम iwl_mvm_configure_filter(काष्ठा ieee80211_hw *hw,
				     अचिन्हित पूर्णांक changed_flags,
				     अचिन्हित पूर्णांक *total_flags,
				     u64 multicast)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mcast_filter_cmd *cmd = (व्योम *)(अचिन्हित दीर्घ)multicast;

	mutex_lock(&mvm->mutex);

	/* replace previous configuration */
	kमुक्त(mvm->mcast_filter_cmd);
	mvm->mcast_filter_cmd = cmd;

	अगर (!cmd)
		जाओ out;

	अगर (changed_flags & FIF_ALLMULTI)
		cmd->pass_all = !!(*total_flags & FIF_ALLMULTI);

	अगर (cmd->pass_all)
		cmd->count = 0;

	iwl_mvm_recalc_multicast(mvm);
out:
	mutex_unlock(&mvm->mutex);
	*total_flags = 0;
पूर्ण

अटल व्योम iwl_mvm_config_अगरace_filter(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					अचिन्हित पूर्णांक filter_flags,
					अचिन्हित पूर्णांक changed_flags)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	/* We support only filter क्रम probe requests */
	अगर (!(changed_flags & FIF_PROBE_REQ))
		वापस;

	/* Supported only क्रम p2p client पूर्णांकerfaces */
	अगर (vअगर->type != NL80211_IFTYPE_STATION || !vअगर->bss_conf.assoc ||
	    !vअगर->p2p)
		वापस;

	mutex_lock(&mvm->mutex);
	iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);
	mutex_unlock(&mvm->mutex);
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_BCAST_FILTERING
काष्ठा iwl_bcast_iter_data अणु
	काष्ठा iwl_mvm *mvm;
	काष्ठा iwl_bcast_filter_cmd *cmd;
	u8 current_filter;
पूर्ण;

अटल व्योम
iwl_mvm_set_bcast_filter(काष्ठा ieee80211_vअगर *vअगर,
			 स्थिर काष्ठा iwl_fw_bcast_filter *in_filter,
			 काष्ठा iwl_fw_bcast_filter *out_filter)
अणु
	काष्ठा iwl_fw_bcast_filter_attr *attr;
	पूर्णांक i;

	स_नकल(out_filter, in_filter, माप(*out_filter));

	क्रम (i = 0; i < ARRAY_SIZE(out_filter->attrs); i++) अणु
		attr = &out_filter->attrs[i];

		अगर (!attr->mask)
			अवरोध;

		चयन (attr->reserved1) अणु
		हाल cpu_to_le16(BC_FILTER_MAGIC_IP):
			अगर (vअगर->bss_conf.arp_addr_cnt != 1) अणु
				attr->mask = 0;
				जारी;
			पूर्ण

			attr->val = vअगर->bss_conf.arp_addr_list[0];
			अवरोध;
		हाल cpu_to_le16(BC_FILTER_MAGIC_MAC):
			attr->val = *(__be32 *)&vअगर->addr[2];
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		attr->reserved1 = 0;
		out_filter->num_attrs++;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_bcast_filter_iterator(व्योम *_data, u8 *mac,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_bcast_iter_data *data = _data;
	काष्ठा iwl_mvm *mvm = data->mvm;
	काष्ठा iwl_bcast_filter_cmd *cmd = data->cmd;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_fw_bcast_mac *bcast_mac;
	पूर्णांक i;

	अगर (WARN_ON(mvmvअगर->id >= ARRAY_SIZE(cmd->macs)))
		वापस;

	bcast_mac = &cmd->macs[mvmvअगर->id];

	/*
	 * enable filtering only क्रम associated stations, but not क्रम P2P
	 * Clients
	 */
	अगर (vअगर->type != NL80211_IFTYPE_STATION || vअगर->p2p ||
	    !vअगर->bss_conf.assoc)
		वापस;

	bcast_mac->शेष_discard = 1;

	/* copy all configured filters */
	क्रम (i = 0; mvm->bcast_filters[i].attrs[0].mask; i++) अणु
		/*
		 * Make sure we करोn't exceed our filters limit.
		 * अगर there is still a valid filter to be configured,
		 * be on the safe side and just allow bcast क्रम this mac.
		 */
		अगर (WARN_ON_ONCE(data->current_filter >=
				 ARRAY_SIZE(cmd->filters))) अणु
			bcast_mac->शेष_discard = 0;
			bcast_mac->attached_filters = 0;
			अवरोध;
		पूर्ण

		iwl_mvm_set_bcast_filter(vअगर,
					 &mvm->bcast_filters[i],
					 &cmd->filters[data->current_filter]);

		/* skip current filter अगर it contains no attributes */
		अगर (!cmd->filters[data->current_filter].num_attrs)
			जारी;

		/* attach the filter to current mac */
		bcast_mac->attached_filters |=
				cpu_to_le16(BIT(data->current_filter));

		data->current_filter++;
	पूर्ण
पूर्ण

bool iwl_mvm_bcast_filter_build_cmd(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_bcast_filter_cmd *cmd)
अणु
	काष्ठा iwl_bcast_iter_data iter_data = अणु
		.mvm = mvm,
		.cmd = cmd,
	पूर्ण;

	अगर (IWL_MVM_FW_BCAST_FILTER_PASS_ALL)
		वापस false;

	स_रखो(cmd, 0, माप(*cmd));
	cmd->max_bcast_filters = ARRAY_SIZE(cmd->filters);
	cmd->max_macs = ARRAY_SIZE(cmd->macs);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	/* use debugfs filters/macs अगर override is configured */
	अगर (mvm->dbgfs_bcast_filtering.override) अणु
		स_नकल(cmd->filters, &mvm->dbgfs_bcast_filtering.cmd.filters,
		       माप(cmd->filters));
		स_नकल(cmd->macs, &mvm->dbgfs_bcast_filtering.cmd.macs,
		       माप(cmd->macs));
		वापस true;
	पूर्ण
#पूर्ण_अगर

	/* अगर no filters are configured, करो nothing */
	अगर (!mvm->bcast_filters)
		वापस false;

	/* configure and attach these filters क्रम each associated sta vअगर */
	ieee80211_iterate_active_पूर्णांकerfaces(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_bcast_filter_iterator, &iter_data);

	वापस true;
पूर्ण

अटल पूर्णांक iwl_mvm_configure_bcast_filter(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_bcast_filter_cmd cmd;

	अगर (!(mvm->fw->ucode_capa.flags & IWL_UCODE_TLV_FLAGS_BCAST_FILTERING))
		वापस 0;

	अगर (!iwl_mvm_bcast_filter_build_cmd(mvm, &cmd))
		वापस 0;

	वापस iwl_mvm_send_cmd_pdu(mvm, BCAST_FILTER_CMD, 0,
				    माप(cmd), &cmd);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक iwl_mvm_configure_bcast_filter(काष्ठा iwl_mvm *mvm)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक iwl_mvm_update_mu_groups(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mu_group_mgmt_cmd cmd = अणुपूर्ण;

	स_नकल(cmd.membership_status, vअगर->bss_conf.mu_group.membership,
	       WLAN_MEMBERSHIP_LEN);
	स_नकल(cmd.user_position, vअगर->bss_conf.mu_group.position,
	       WLAN_USER_POSITION_LEN);

	वापस iwl_mvm_send_cmd_pdu(mvm,
				    WIDE_ID(DATA_PATH_GROUP,
					    UPDATE_MU_GROUPS_CMD),
				    0, माप(cmd), &cmd);
पूर्ण

अटल व्योम iwl_mvm_mu_mimo_अगरace_iterator(व्योम *_data, u8 *mac,
					   काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (vअगर->mu_mimo_owner) अणु
		काष्ठा iwl_mu_group_mgmt_notअगर *notअगर = _data;

		/*
		 * MU-MIMO Group Id action frame is little endian. We treat
		 * the data received from firmware as अगर it came from the
		 * action frame, so no conversion is needed.
		 */
		ieee80211_update_mu_groups(vअगर,
					   (u8 *)&notअगर->membership_status,
					   (u8 *)&notअगर->user_position);
	पूर्ण
पूर्ण

व्योम iwl_mvm_mu_mimo_grp_notअगर(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mu_group_mgmt_notअगर *notअगर = (व्योम *)pkt->data;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
			iwl_mvm_mu_mimo_अगरace_iterator, notअगर);
पूर्ण

अटल u8 iwl_mvm_he_get_ppe_val(u8 *ppe, u8 ppe_pos_bit)
अणु
	u8 byte_num = ppe_pos_bit / 8;
	u8 bit_num = ppe_pos_bit % 8;
	u8 residue_bits;
	u8 res;

	अगर (bit_num <= 5)
		वापस (ppe[byte_num] >> bit_num) &
		       (BIT(IEEE80211_PPE_THRES_INFO_PPET_SIZE) - 1);

	/*
	 * If bit_num > 5, we have to combine bits with next byte.
	 * Calculate how many bits we need to take from current byte (called
	 * here "residue_bits"), and add them to bits from next byte.
	 */

	residue_bits = 8 - bit_num;

	res = (ppe[byte_num + 1] &
	       (BIT(IEEE80211_PPE_THRES_INFO_PPET_SIZE - residue_bits) - 1)) <<
	      residue_bits;
	res += (ppe[byte_num] >> bit_num) & (BIT(residue_bits) - 1);

	वापस res;
पूर्ण

अटल व्योम iwl_mvm_cfg_he_sta(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_vअगर *vअगर, u8 sta_id)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_he_sta_context_cmd sta_ctxt_cmd = अणु
		.sta_id = sta_id,
		.tid_limit = IWL_MAX_TID_COUNT,
		.bss_color = vअगर->bss_conf.he_bss_color.color,
		.htc_trig_based_pkt_ext = vअगर->bss_conf.htc_trig_based_pkt_ext,
		.frame_समय_rts_th =
			cpu_to_le16(vअगर->bss_conf.frame_समय_rts_th),
	पूर्ण;
	पूर्णांक size = fw_has_api(&mvm->fw->ucode_capa,
			      IWL_UCODE_TLV_API_MBSSID_HE) ?
		   माप(sta_ctxt_cmd) :
		   माप(काष्ठा iwl_he_sta_context_cmd_v1);
	काष्ठा ieee80211_sta *sta;
	u32 flags;
	पूर्णांक i;
	स्थिर काष्ठा ieee80211_sta_he_cap *own_he_cap = शून्य;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	स्थिर काष्ठा ieee80211_supported_band *sband;

	rcu_पढ़ो_lock();

	chanctx_conf = rcu_dereference(vअगर->chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	sband = mvm->hw->wiphy->bands[chanctx_conf->def.chan->band];
	own_he_cap = ieee80211_get_he_अगरtype_cap(sband, vअगर->type);

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_ctxt_cmd.sta_id]);
	अगर (IS_ERR_OR_शून्य(sta)) अणु
		rcu_पढ़ो_unlock();
		WARN(1, "Can't find STA to configure HE\n");
		वापस;
	पूर्ण

	अगर (!sta->he_cap.has_he) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	flags = 0;

	/* Block 26-tone RU OFDMA transmissions */
	अगर (mvmvअगर->he_ru_2mhz_block)
		flags |= STA_CTXT_HE_RU_2MHZ_BLOCK;

	/* HTC flags */
	अगर (sta->he_cap.he_cap_elem.mac_cap_info[0] &
	    IEEE80211_HE_MAC_CAP0_HTC_HE)
		sta_ctxt_cmd.htc_flags |= cpu_to_le32(IWL_HE_HTC_SUPPORT);
	अगर ((sta->he_cap.he_cap_elem.mac_cap_info[1] &
	      IEEE80211_HE_MAC_CAP1_LINK_ADAPTATION) ||
	    (sta->he_cap.he_cap_elem.mac_cap_info[2] &
	      IEEE80211_HE_MAC_CAP2_LINK_ADAPTATION)) अणु
		u8 link_adap =
			((sta->he_cap.he_cap_elem.mac_cap_info[2] &
			  IEEE80211_HE_MAC_CAP2_LINK_ADAPTATION) << 1) +
			 (sta->he_cap.he_cap_elem.mac_cap_info[1] &
			  IEEE80211_HE_MAC_CAP1_LINK_ADAPTATION);

		अगर (link_adap == 2)
			sta_ctxt_cmd.htc_flags |=
				cpu_to_le32(IWL_HE_HTC_LINK_ADAP_UNSOLICITED);
		अन्यथा अगर (link_adap == 3)
			sta_ctxt_cmd.htc_flags |=
				cpu_to_le32(IWL_HE_HTC_LINK_ADAP_BOTH);
	पूर्ण
	अगर (sta->he_cap.he_cap_elem.mac_cap_info[2] & IEEE80211_HE_MAC_CAP2_BSR)
		sta_ctxt_cmd.htc_flags |= cpu_to_le32(IWL_HE_HTC_BSR_SUPP);
	अगर (sta->he_cap.he_cap_elem.mac_cap_info[3] &
	    IEEE80211_HE_MAC_CAP3_OMI_CONTROL)
		sta_ctxt_cmd.htc_flags |= cpu_to_le32(IWL_HE_HTC_OMI_SUPP);
	अगर (sta->he_cap.he_cap_elem.mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_BQR)
		sta_ctxt_cmd.htc_flags |= cpu_to_le32(IWL_HE_HTC_BQR_SUPP);

	/*
	 * Initialize the PPE thresholds to "None" (7), as described in Table
	 * 9-262ac of 80211.ax/D3.0.
	 */
	स_रखो(&sta_ctxt_cmd.pkt_ext, 7, माप(sta_ctxt_cmd.pkt_ext));

	/* If PPE Thresholds exist, parse them पूर्णांकo a FW-familiar क्रमmat. */
	अगर (sta->he_cap.he_cap_elem.phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT) अणु
		u8 nss = (sta->he_cap.ppe_thres[0] &
			  IEEE80211_PPE_THRES_NSS_MASK) + 1;
		u8 ru_index_biपंचांगap =
			(sta->he_cap.ppe_thres[0] &
			 IEEE80211_PPE_THRES_RU_INDEX_BITMASK_MASK) >>
			IEEE80211_PPE_THRES_RU_INDEX_BITMASK_POS;
		u8 *ppe = &sta->he_cap.ppe_thres[0];
		u8 ppe_pos_bit = 7; /* Starting after PPE header */

		/*
		 * FW currently supports only nss == MAX_HE_SUPP_NSS
		 *
		 * If nss > MAX: we can ignore values we करोn't support
		 * If nss < MAX: we can set zeros in other streams
		 */
		अगर (nss > MAX_HE_SUPP_NSS) अणु
			IWL_INFO(mvm, "Got NSS = %d - trimming to %d\n", nss,
				 MAX_HE_SUPP_NSS);
			nss = MAX_HE_SUPP_NSS;
		पूर्ण

		क्रम (i = 0; i < nss; i++) अणु
			u8 ru_index_पंचांगp = ru_index_biपंचांगap << 1;
			u8 bw;

			क्रम (bw = 0; bw < MAX_HE_CHANNEL_BW_INDX; bw++) अणु
				ru_index_पंचांगp >>= 1;
				अगर (!(ru_index_पंचांगp & 1))
					जारी;

				sta_ctxt_cmd.pkt_ext.pkt_ext_qam_th[i][bw][1] =
					iwl_mvm_he_get_ppe_val(ppe,
							       ppe_pos_bit);
				ppe_pos_bit +=
					IEEE80211_PPE_THRES_INFO_PPET_SIZE;
				sta_ctxt_cmd.pkt_ext.pkt_ext_qam_th[i][bw][0] =
					iwl_mvm_he_get_ppe_val(ppe,
							       ppe_pos_bit);
				ppe_pos_bit +=
					IEEE80211_PPE_THRES_INFO_PPET_SIZE;
			पूर्ण
		पूर्ण

		flags |= STA_CTXT_HE_PACKET_EXT;
	पूर्ण अन्यथा अगर ((sta->he_cap.he_cap_elem.phy_cap_info[9] &
		    IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_MASK) !=
		  IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_RESERVED) अणु
		पूर्णांक low_th = -1;
		पूर्णांक high_th = -1;

		/* Take the PPE thresholds from the nominal padding info */
		चयन (sta->he_cap.he_cap_elem.phy_cap_info[9] &
			IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_MASK) अणु
		हाल IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_0US:
			low_th = IWL_HE_PKT_EXT_NONE;
			high_th = IWL_HE_PKT_EXT_NONE;
			अवरोध;
		हाल IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_8US:
			low_th = IWL_HE_PKT_EXT_BPSK;
			high_th = IWL_HE_PKT_EXT_NONE;
			अवरोध;
		हाल IEEE80211_HE_PHY_CAP9_NOMIMAL_PKT_PADDING_16US:
			low_th = IWL_HE_PKT_EXT_NONE;
			high_th = IWL_HE_PKT_EXT_BPSK;
			अवरोध;
		पूर्ण

		/* Set the PPE thresholds accordingly */
		अगर (low_th >= 0 && high_th >= 0) अणु
			काष्ठा iwl_he_pkt_ext *pkt_ext =
				(काष्ठा iwl_he_pkt_ext *)&sta_ctxt_cmd.pkt_ext;

			क्रम (i = 0; i < MAX_HE_SUPP_NSS; i++) अणु
				u8 bw;

				क्रम (bw = 0; bw < MAX_HE_CHANNEL_BW_INDX;
				     bw++) अणु
					pkt_ext->pkt_ext_qam_th[i][bw][0] =
						low_th;
					pkt_ext->pkt_ext_qam_th[i][bw][1] =
						high_th;
				पूर्ण
			पूर्ण

			flags |= STA_CTXT_HE_PACKET_EXT;
		पूर्ण
	पूर्ण

	अगर (sta->he_cap.he_cap_elem.mac_cap_info[2] &
	    IEEE80211_HE_MAC_CAP2_32BIT_BA_BITMAP)
		flags |= STA_CTXT_HE_32BIT_BA_BITMAP;

	अगर (sta->he_cap.he_cap_elem.mac_cap_info[2] &
	    IEEE80211_HE_MAC_CAP2_ACK_EN)
		flags |= STA_CTXT_HE_ACK_ENABLED;

	rcu_पढ़ो_unlock();

	/* Mark MU EDCA as enabled, unless none detected on some AC */
	flags |= STA_CTXT_HE_MU_EDCA_CW;
	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		काष्ठा ieee80211_he_mu_edca_param_ac_rec *mu_edca =
			&mvmvअगर->queue_params[i].mu_edca_param_rec;
		u8 ac = iwl_mvm_mac80211_ac_to_ucode_ac(i);

		अगर (!mvmvअगर->queue_params[i].mu_edca) अणु
			flags &= ~STA_CTXT_HE_MU_EDCA_CW;
			अवरोध;
		पूर्ण

		sta_ctxt_cmd.trig_based_txf[ac].cwmin =
			cpu_to_le16(mu_edca->ecw_min_max & 0xf);
		sta_ctxt_cmd.trig_based_txf[ac].cwmax =
			cpu_to_le16((mu_edca->ecw_min_max & 0xf0) >> 4);
		sta_ctxt_cmd.trig_based_txf[ac].aअगरsn =
			cpu_to_le16(mu_edca->aअगरsn);
		sta_ctxt_cmd.trig_based_txf[ac].mu_समय =
			cpu_to_le16(mu_edca->mu_edca_समयr);
	पूर्ण


	अगर (vअगर->bss_conf.uora_exists) अणु
		flags |= STA_CTXT_HE_TRIG_RND_ALLOC;

		sta_ctxt_cmd.अक्रम_alloc_ecwmin =
			vअगर->bss_conf.uora_ocw_range & 0x7;
		sta_ctxt_cmd.अक्रम_alloc_ecwmax =
			(vअगर->bss_conf.uora_ocw_range >> 3) & 0x7;
	पूर्ण

	अगर (own_he_cap && !(own_he_cap->he_cap_elem.mac_cap_info[2] &
			    IEEE80211_HE_MAC_CAP2_ACK_EN))
		flags |= STA_CTXT_HE_NIC_NOT_ACK_ENABLED;

	अगर (vअगर->bss_conf.nontransmitted) अणु
		flags |= STA_CTXT_HE_REF_BSSID_VALID;
		ether_addr_copy(sta_ctxt_cmd.ref_bssid_addr,
				vअगर->bss_conf.transmitter_bssid);
		sta_ctxt_cmd.max_bssid_indicator =
			vअगर->bss_conf.bssid_indicator;
		sta_ctxt_cmd.bssid_index = vअगर->bss_conf.bssid_index;
		sta_ctxt_cmd.ema_ap = vअगर->bss_conf.ema_ap;
		sta_ctxt_cmd.profile_periodicity =
			vअगर->bss_conf.profile_periodicity;
	पूर्ण

	sta_ctxt_cmd.flags = cpu_to_le32(flags);

	अगर (iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(STA_HE_CTXT_CMD,
						 DATA_PATH_GROUP, 0),
				 0, size, &sta_ctxt_cmd))
		IWL_ERR(mvm, "Failed to config FW to work HE!\n");
पूर्ण

अटल व्योम iwl_mvm_bss_info_changed_station(काष्ठा iwl_mvm *mvm,
					     काष्ठा ieee80211_vअगर *vअगर,
					     काष्ठा ieee80211_bss_conf *bss_conf,
					     u32 changes)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	/*
	 * Re-calculate the tsf id, as the leader-follower relations depend
	 * on the beacon पूर्णांकerval, which was not known when the station
	 * पूर्णांकerface was added.
	 */
	अगर (changes & BSS_CHANGED_ASSOC && bss_conf->assoc) अणु
		अगर (vअगर->bss_conf.he_support &&
		    !iwlwअगरi_mod_params.disable_11ax)
			iwl_mvm_cfg_he_sta(mvm, vअगर, mvmvअगर->ap_sta_id);

		iwl_mvm_mac_ctxt_recalc_tsf_id(mvm, vअगर);
	पूर्ण

	/* Update MU EDCA params */
	अगर (changes & BSS_CHANGED_QOS && mvmvअगर->associated &&
	    bss_conf->assoc && vअगर->bss_conf.he_support &&
	    !iwlwअगरi_mod_params.disable_11ax)
		iwl_mvm_cfg_he_sta(mvm, vअगर, mvmvअगर->ap_sta_id);

	/*
	 * If we're not associated yet, take the (new) BSSID beक्रमe associating
	 * so the firmware knows. If we're alपढ़ोy associated, then use the old
	 * BSSID here, and we'll send a cleared one later in the CHANGED_ASSOC
	 * branch क्रम disassociation below.
	 */
	अगर (changes & BSS_CHANGED_BSSID && !mvmvअगर->associated)
		स_नकल(mvmvअगर->bssid, bss_conf->bssid, ETH_ALEN);

	ret = iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, mvmvअगर->bssid);
	अगर (ret)
		IWL_ERR(mvm, "failed to update MAC %pM\n", vअगर->addr);

	/* after sending it once, aकरोpt mac80211 data */
	स_नकल(mvmvअगर->bssid, bss_conf->bssid, ETH_ALEN);
	mvmvअगर->associated = bss_conf->assoc;

	अगर (changes & BSS_CHANGED_ASSOC) अणु
		अगर (bss_conf->assoc) अणु
			/* clear statistics to get clean beacon counter */
			iwl_mvm_request_statistics(mvm, true);
			स_रखो(&mvmvअगर->beacon_stats, 0,
			       माप(mvmvअगर->beacon_stats));

			/* add quota क्रम this पूर्णांकerface */
			ret = iwl_mvm_update_quotas(mvm, true, शून्य);
			अगर (ret) अणु
				IWL_ERR(mvm, "failed to update quotas\n");
				वापस;
			पूर्ण

			अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART,
				     &mvm->status) &&
			    !fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_SESSION_PROT_CMD)) अणु
				/*
				 * If we're restarting then the firmware will
				 * obviously have lost synchronisation with
				 * the AP. It will attempt to synchronise by
				 * itself, but we can make it more reliable by
				 * scheduling a session protection समय event.
				 *
				 * The firmware needs to receive a beacon to
				 * catch up with synchronisation, use 110% of
				 * the beacon पूर्णांकerval.
				 *
				 * Set a large maximum delay to allow क्रम more
				 * than a single पूर्णांकerface.
				 *
				 * For new firmware versions, rely on the
				 * firmware. This is relevant क्रम DCM scenarios
				 * only anyway.
				 */
				u32 dur = (11 * vअगर->bss_conf.beacon_पूर्णांक) / 10;
				iwl_mvm_protect_session(mvm, vअगर, dur, dur,
							5 * dur, false);
			पूर्ण

			iwl_mvm_sf_update(mvm, vअगर, false);
			iwl_mvm_घातer_vअगर_assoc(mvm, vअगर);
			अगर (vअगर->p2p) अणु
				iwl_mvm_update_smps(mvm, vअगर,
						    IWL_MVM_SMPS_REQ_PROT,
						    IEEE80211_SMPS_DYNAMIC);
			पूर्ण
		पूर्ण अन्यथा अगर (mvmvअगर->ap_sta_id != IWL_MVM_INVALID_STA) अणु
			/*
			 * If update fails - SF might be running in associated
			 * mode जबतक disassociated - which is क्रमbidden.
			 */
			ret = iwl_mvm_sf_update(mvm, vअगर, false);
			WARN_ONCE(ret &&
				  !test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED,
					    &mvm->status),
				  "Failed to update SF upon disassociation\n");

			/*
			 * If we get an निश्चित during the connection (after the
			 * station has been added, but beक्रमe the vअगर is set
			 * to associated), mac80211 will re-add the station and
			 * then configure the vअगर. Since the vअगर is not
			 * associated, we would हटाओ the station here and
			 * this would fail the recovery.
			 */
			अगर (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART,
				      &mvm->status)) अणु
				/*
				 * Remove AP station now that
				 * the MAC is unassoc
				 */
				ret = iwl_mvm_rm_sta_id(mvm, vअगर,
							mvmvअगर->ap_sta_id);
				अगर (ret)
					IWL_ERR(mvm,
						"failed to remove AP station\n");

				mvmvअगर->ap_sta_id = IWL_MVM_INVALID_STA;
			पूर्ण

			/* हटाओ quota क्रम this पूर्णांकerface */
			ret = iwl_mvm_update_quotas(mvm, false, शून्य);
			अगर (ret)
				IWL_ERR(mvm, "failed to update quotas\n");

			/* this will take the cleared BSSID from bss_conf */
			ret = iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);
			अगर (ret)
				IWL_ERR(mvm,
					"failed to update MAC %pM (clear after unassoc)\n",
					vअगर->addr);
		पूर्ण

		/*
		 * The firmware tracks the MU-MIMO group on its own.
		 * However, on HW restart we should restore this data.
		 */
		अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		    (changes & BSS_CHANGED_MU_GROUPS) && vअगर->mu_mimo_owner) अणु
			ret = iwl_mvm_update_mu_groups(mvm, vअगर);
			अगर (ret)
				IWL_ERR(mvm,
					"failed to update VHT MU_MIMO groups\n");
		पूर्ण

		iwl_mvm_recalc_multicast(mvm);
		iwl_mvm_configure_bcast_filter(mvm);

		/* reset rssi values */
		mvmvअगर->bf_data.ave_beacon_संकेत = 0;

		iwl_mvm_bt_coex_vअगर_change(mvm);
		iwl_mvm_update_smps(mvm, vअगर, IWL_MVM_SMPS_REQ_TT,
				    IEEE80211_SMPS_AUTOMATIC);
		अगर (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_UMAC_SCAN))
			iwl_mvm_config_scan(mvm);
	पूर्ण

	अगर (changes & BSS_CHANGED_BEACON_INFO) अणु
		/*
		 * We received a beacon from the associated AP so
		 * हटाओ the session protection.
		 * A firmware with the new API will हटाओ it स्वतःmatically.
		 */
		अगर (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_SESSION_PROT_CMD))
			iwl_mvm_stop_session_protection(mvm, vअगर);

		iwl_mvm_sf_update(mvm, vअगर, false);
		WARN_ON(iwl_mvm_enable_beacon_filter(mvm, vअगर, 0));
	पूर्ण

	अगर (changes & (BSS_CHANGED_PS | BSS_CHANGED_P2P_PS | BSS_CHANGED_QOS |
		       /*
			* Send घातer command on every beacon change,
			* because we may have not enabled beacon पात yet.
			*/
		       BSS_CHANGED_BEACON_INFO)) अणु
		ret = iwl_mvm_घातer_update_mac(mvm);
		अगर (ret)
			IWL_ERR(mvm, "failed to update power mode\n");
	पूर्ण

	अगर (changes & BSS_CHANGED_CQM) अणु
		IWL_DEBUG_MAC80211(mvm, "cqm info_changed\n");
		/* reset cqm events tracking */
		mvmvअगर->bf_data.last_cqm_event = 0;
		अगर (mvmvअगर->bf_data.bf_enabled) अणु
			ret = iwl_mvm_enable_beacon_filter(mvm, vअगर, 0);
			अगर (ret)
				IWL_ERR(mvm,
					"failed to update CQM thresholds\n");
		पूर्ण
	पूर्ण

	अगर (changes & BSS_CHANGED_ARP_FILTER) अणु
		IWL_DEBUG_MAC80211(mvm, "arp filter changed\n");
		iwl_mvm_configure_bcast_filter(mvm);
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_mvm_start_ap_ibss(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret, i;

	mutex_lock(&mvm->mutex);

	/* Send the beacon ढाँचा */
	ret = iwl_mvm_mac_ctxt_beacon_changed(mvm, vअगर);
	अगर (ret)
		जाओ out_unlock;

	/*
	 * Re-calculate the tsf id, as the leader-follower relations depend on
	 * the beacon पूर्णांकerval, which was not known when the AP पूर्णांकerface
	 * was added.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_AP)
		iwl_mvm_mac_ctxt_recalc_tsf_id(mvm, vअगर);

	mvmvअगर->ap_assoc_sta_count = 0;

	/* Add the mac context */
	ret = iwl_mvm_mac_ctxt_add(mvm, vअगर);
	अगर (ret)
		जाओ out_unlock;

	/* Perक्रमm the binding */
	ret = iwl_mvm_binding_add_vअगर(mvm, vअगर);
	अगर (ret)
		जाओ out_हटाओ;

	/*
	 * This is not very nice, but the simplest:
	 * For older FWs adding the mcast sta beक्रमe the bcast station may
	 * cause निश्चित 0x2b00.
	 * This is fixed in later FW so make the order of removal depend on
	 * the TLV
	 */
	अगर (fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE)) अणु
		ret = iwl_mvm_add_mcast_sta(mvm, vअगर);
		अगर (ret)
			जाओ out_unbind;
		/*
		 * Send the bcast station. At this stage the TBTT and DTIM समय
		 * events are added and applied to the scheduler
		 */
		ret = iwl_mvm_send_add_bcast_sta(mvm, vअगर);
		अगर (ret) अणु
			iwl_mvm_rm_mcast_sta(mvm, vअगर);
			जाओ out_unbind;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Send the bcast station. At this stage the TBTT and DTIM समय
		 * events are added and applied to the scheduler
		 */
		ret = iwl_mvm_send_add_bcast_sta(mvm, vअगर);
		अगर (ret)
			जाओ out_unbind;
		ret = iwl_mvm_add_mcast_sta(mvm, vअगर);
		अगर (ret) अणु
			iwl_mvm_send_rm_bcast_sta(mvm, vअगर);
			जाओ out_unbind;
		पूर्ण
	पूर्ण

	/* must be set beक्रमe quota calculations */
	mvmvअगर->ap_ibss_active = true;

	/* send all the early keys to the device now */
	क्रम (i = 0; i < ARRAY_SIZE(mvmvअगर->ap_early_keys); i++) अणु
		काष्ठा ieee80211_key_conf *key = mvmvअगर->ap_early_keys[i];

		अगर (!key)
			जारी;

		mvmvअगर->ap_early_keys[i] = शून्य;

		ret = __iwl_mvm_mac_set_key(hw, SET_KEY, vअगर, शून्य, key);
		अगर (ret)
			जाओ out_quota_failed;
	पूर्ण

	अगर (vअगर->type == NL80211_IFTYPE_AP && !vअगर->p2p) अणु
		iwl_mvm_vअगर_set_low_latency(mvmvअगर, true,
					    LOW_LATENCY_VIF_TYPE);
		iwl_mvm_send_low_latency_cmd(mvm, true, mvmvअगर->id);
	पूर्ण

	/* घातer updated needs to be करोne beक्रमe quotas */
	iwl_mvm_घातer_update_mac(mvm);

	ret = iwl_mvm_update_quotas(mvm, false, शून्य);
	अगर (ret)
		जाओ out_quota_failed;

	/* Need to update the P2P Device MAC (only GO, IBSS is single vअगर) */
	अगर (vअगर->p2p && mvm->p2p_device_vअगर)
		iwl_mvm_mac_ctxt_changed(mvm, mvm->p2p_device_vअगर, false, शून्य);

	iwl_mvm_bt_coex_vअगर_change(mvm);

	/* we करोn't support TDLS during DCM */
	अगर (iwl_mvm_phy_ctx_count(mvm) > 1)
		iwl_mvm_tearकरोwn_tdls_peers(mvm);

	iwl_mvm_fपंचांग_restart_responder(mvm, vअगर);

	जाओ out_unlock;

out_quota_failed:
	iwl_mvm_घातer_update_mac(mvm);
	mvmvअगर->ap_ibss_active = false;
	iwl_mvm_send_rm_bcast_sta(mvm, vअगर);
	iwl_mvm_rm_mcast_sta(mvm, vअगर);
out_unbind:
	iwl_mvm_binding_हटाओ_vअगर(mvm, vअगर);
out_हटाओ:
	iwl_mvm_mac_ctxt_हटाओ(mvm, vअगर);
out_unlock:
	mutex_unlock(&mvm->mutex);
	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_stop_ap_ibss(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	iwl_mvm_prepare_mac_removal(mvm, vअगर);

	mutex_lock(&mvm->mutex);

	/* Handle AP stop जबतक in CSA */
	अगर (rcu_access_poपूर्णांकer(mvm->csa_vअगर) == vअगर) अणु
		iwl_mvm_हटाओ_समय_event(mvm, mvmvअगर,
					  &mvmvअगर->समय_event_data);
		RCU_INIT_POINTER(mvm->csa_vअगर, शून्य);
		mvmvअगर->csa_countकरोwn = false;
	पूर्ण

	अगर (rcu_access_poपूर्णांकer(mvm->csa_tx_blocked_vअगर) == vअगर) अणु
		RCU_INIT_POINTER(mvm->csa_tx_blocked_vअगर, शून्य);
		mvm->csa_tx_block_bcn_समयout = 0;
	पूर्ण

	mvmvअगर->ap_ibss_active = false;
	mvm->ap_last_beacon_gp2 = 0;

	अगर (vअगर->type == NL80211_IFTYPE_AP && !vअगर->p2p) अणु
		iwl_mvm_vअगर_set_low_latency(mvmvअगर, false,
					    LOW_LATENCY_VIF_TYPE);
		iwl_mvm_send_low_latency_cmd(mvm, false,  mvmvअगर->id);
	पूर्ण

	iwl_mvm_bt_coex_vअगर_change(mvm);

	/* Need to update the P2P Device MAC (only GO, IBSS is single vअगर) */
	अगर (vअगर->p2p && mvm->p2p_device_vअगर)
		iwl_mvm_mac_ctxt_changed(mvm, mvm->p2p_device_vअगर, false, शून्य);

	iwl_mvm_update_quotas(mvm, false, शून्य);

	iwl_mvm_fपंचांग_responder_clear(mvm, vअगर);

	/*
	 * This is not very nice, but the simplest:
	 * For older FWs removing the mcast sta beक्रमe the bcast station may
	 * cause निश्चित 0x2b00.
	 * This is fixed in later FW (which will stop beaconing when removing
	 * bcast station).
	 * So make the order of removal depend on the TLV
	 */
	अगर (!fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE))
		iwl_mvm_rm_mcast_sta(mvm, vअगर);
	iwl_mvm_send_rm_bcast_sta(mvm, vअगर);
	अगर (fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE))
		iwl_mvm_rm_mcast_sta(mvm, vअगर);
	iwl_mvm_binding_हटाओ_vअगर(mvm, vअगर);

	iwl_mvm_घातer_update_mac(mvm);

	iwl_mvm_mac_ctxt_हटाओ(mvm, vअगर);

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम
iwl_mvm_bss_info_changed_ap_ibss(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_bss_conf *bss_conf,
				 u32 changes)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	/* Changes will be applied when the AP/IBSS is started */
	अगर (!mvmvअगर->ap_ibss_active)
		वापस;

	अगर (changes & (BSS_CHANGED_ERP_CTS_PROT | BSS_CHANGED_HT |
		       BSS_CHANGED_BANDWIDTH | BSS_CHANGED_QOS) &&
	    iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य))
		IWL_ERR(mvm, "failed to update MAC %pM\n", vअगर->addr);

	/* Need to send a new beacon ढाँचा to the FW */
	अगर (changes & BSS_CHANGED_BEACON &&
	    iwl_mvm_mac_ctxt_beacon_changed(mvm, vअगर))
		IWL_WARN(mvm, "Failed updating beacon data\n");

	अगर (changes & BSS_CHANGED_FTM_RESPONDER) अणु
		पूर्णांक ret = iwl_mvm_fपंचांग_start_responder(mvm, vअगर);

		अगर (ret)
			IWL_WARN(mvm, "Failed to enable FTM responder (%d)\n",
				 ret);
	पूर्ण

पूर्ण

अटल व्योम iwl_mvm_bss_info_changed(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_bss_conf *bss_conf,
				     u32 changes)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);

	अगर (changes & BSS_CHANGED_IDLE && !bss_conf->idle)
		iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_SCHED, true);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		iwl_mvm_bss_info_changed_station(mvm, vअगर, bss_conf, changes);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_ADHOC:
		iwl_mvm_bss_info_changed_ap_ibss(mvm, vअगर, bss_conf, changes);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (changes & BSS_CHANGED_MU_GROUPS)
			iwl_mvm_update_mu_groups(mvm, vअगर);
		अवरोध;
	शेष:
		/* shouldn't happen */
		WARN_ON_ONCE(1);
	पूर्ण

	अगर (changes & BSS_CHANGED_TXPOWER) अणु
		IWL_DEBUG_CALIB(mvm, "Changing TX Power to %d dBm\n",
				bss_conf->txघातer);
		iwl_mvm_set_tx_घातer(mvm, vअगर, bss_conf->txघातer);
	पूर्ण

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_hw_scan(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	अगर (hw_req->req.n_channels == 0 ||
	    hw_req->req.n_channels > mvm->fw->ucode_capa.n_scan_channels)
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_reg_scan_start(mvm, vअगर, &hw_req->req, &hw_req->ies);
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_mac_cancel_hw_scan(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);

	/* Due to a race condition, it's possible that mac80211 asks
	 * us to stop a hw_scan when it's alपढ़ोy stopped.  This can
	 * happen, क्रम instance, अगर we stopped the scan ourselves,
	 * called ieee80211_scan_completed() and the userspace called
	 * cancel scan scan beक्रमe ieee80211_scan_work() could run.
	 * To handle that, simply वापस अगर the scan is not running.
	*/
	अगर (mvm->scan_status & IWL_MVM_SCAN_REGULAR)
		iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_REGULAR, true);

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम
iwl_mvm_mac_allow_buffered_frames(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_sta *sta, u16 tids,
				  पूर्णांक num_frames,
				  क्रमागत ieee80211_frame_release_type reason,
				  bool more_data)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	/* Called when we need to transmit (a) frame(s) from mac80211 */

	iwl_mvm_sta_modअगरy_sleep_tx_count(mvm, sta, reason, num_frames,
					  tids, more_data, false);
पूर्ण

अटल व्योम
iwl_mvm_mac_release_buffered_frames(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_sta *sta, u16 tids,
				    पूर्णांक num_frames,
				    क्रमागत ieee80211_frame_release_type reason,
				    bool more_data)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	/* Called when we need to transmit (a) frame(s) from agg or dqa queue */

	iwl_mvm_sta_modअगरy_sleep_tx_count(mvm, sta, reason, num_frames,
					  tids, more_data, true);
पूर्ण

अटल व्योम __iwl_mvm_mac_sta_notअगरy(काष्ठा ieee80211_hw *hw,
				     क्रमागत sta_notअगरy_cmd cmd,
				     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	अचिन्हित दीर्घ txqs = 0, tids = 0;
	पूर्णांक tid;

	/*
	 * If we have TVQM then we get too high queue numbers - luckily
	 * we really shouldn't get here with that because such hardware
	 * should have firmware supporting buffer station offload.
	 */
	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस;

	spin_lock_bh(&mvmsta->lock);
	क्रम (tid = 0; tid < ARRAY_SIZE(mvmsta->tid_data); tid++) अणु
		काष्ठा iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];

		अगर (tid_data->txq_id == IWL_MVM_INVALID_QUEUE)
			जारी;

		__set_bit(tid_data->txq_id, &txqs);

		अगर (iwl_mvm_tid_queued(mvm, tid_data) == 0)
			जारी;

		__set_bit(tid, &tids);
	पूर्ण

	चयन (cmd) अणु
	हाल STA_NOTIFY_SLEEP:
		क्रम_each_set_bit(tid, &tids, IWL_MAX_TID_COUNT)
			ieee80211_sta_set_buffered(sta, tid, true);

		अगर (txqs)
			iwl_trans_मुक्तze_txq_समयr(mvm->trans, txqs, true);
		/*
		 * The fw updates the STA to be asleep. Tx packets on the Tx
		 * queues to this station will not be transmitted. The fw will
		 * send a Tx response with TX_STATUS_FAIL_DEST_PS.
		 */
		अवरोध;
	हाल STA_NOTIFY_AWAKE:
		अगर (WARN_ON(mvmsta->sta_id == IWL_MVM_INVALID_STA))
			अवरोध;

		अगर (txqs)
			iwl_trans_मुक्तze_txq_समयr(mvm->trans, txqs, false);
		iwl_mvm_sta_modअगरy_ps_wake(mvm, sta);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock_bh(&mvmsta->lock);
पूर्ण

अटल व्योम iwl_mvm_mac_sta_notअगरy(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   क्रमागत sta_notअगरy_cmd cmd,
				   काष्ठा ieee80211_sta *sta)
अणु
	__iwl_mvm_mac_sta_notअगरy(hw, cmd, sta);
पूर्ण

व्योम iwl_mvm_sta_pm_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mvm_pm_state_notअगरication *notअगर = (व्योम *)pkt->data;
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	bool sleeping = (notअगर->type != IWL_MVM_PM_EVENT_AWAKE);

	अगर (WARN_ON(notअगर->sta_id >= mvm->fw->ucode_capa.num_stations))
		वापस;

	rcu_पढ़ो_lock();
	sta = rcu_dereference(mvm->fw_id_to_mac_id[notअगर->sta_id]);
	अगर (WARN_ON(IS_ERR_OR_शून्य(sta))) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	अगर (!mvmsta->vअगर ||
	    mvmsta->vअगर->type != NL80211_IFTYPE_AP) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर (mvmsta->sleeping != sleeping) अणु
		mvmsta->sleeping = sleeping;
		__iwl_mvm_mac_sta_notअगरy(mvm->hw,
			sleeping ? STA_NOTIFY_SLEEP : STA_NOTIFY_AWAKE,
			sta);
		ieee80211_sta_ps_transition(sta, sleeping);
	पूर्ण

	अगर (sleeping) अणु
		चयन (notअगर->type) अणु
		हाल IWL_MVM_PM_EVENT_AWAKE:
		हाल IWL_MVM_PM_EVENT_ASLEEP:
			अवरोध;
		हाल IWL_MVM_PM_EVENT_UAPSD:
			ieee80211_sta_uapsd_trigger(sta, IEEE80211_NUM_TIDS);
			अवरोध;
		हाल IWL_MVM_PM_EVENT_PS_POLL:
			ieee80211_sta_pspoll(sta);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम iwl_mvm_sta_pre_rcu_हटाओ(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);

	/*
	 * This is called beक्रमe mac80211 करोes RCU synchronisation,
	 * so here we alपढ़ोy invalidate our पूर्णांकernal RCU-रक्षित
	 * station poपूर्णांकer. The rest of the code will thus no दीर्घer
	 * be able to find the station this way, and we करोn't rely
	 * on further RCU synchronisation after the sta_state()
	 * callback deleted the station.
	 */
	mutex_lock(&mvm->mutex);
	अगर (sta == rcu_access_poपूर्णांकer(mvm->fw_id_to_mac_id[mvm_sta->sta_id]))
		rcu_assign_poपूर्णांकer(mvm->fw_id_to_mac_id[mvm_sta->sta_id],
				   ERR_PTR(-ENOENT));

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम iwl_mvm_check_uapsd(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				स्थिर u8 *bssid)
अणु
	पूर्णांक i;

	अगर (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) अणु
		काष्ठा iwl_mvm_tcm_mac *mdata;

		mdata = &mvm->tcm.data[iwl_mvm_vअगर_from_mac80211(vअगर)->id];
		ewma_rate_init(&mdata->uapsd_nonagg_detect.rate);
		mdata->खोलोed_rx_ba_sessions = false;
	पूर्ण

	अगर (!(mvm->fw->ucode_capa.flags & IWL_UCODE_TLV_FLAGS_UAPSD_SUPPORT))
		वापस;

	अगर (vअगर->p2p && !iwl_mvm_is_p2p_scm_uapsd_supported(mvm)) अणु
		vअगर->driver_flags &= ~IEEE80211_VIF_SUPPORTS_UAPSD;
		वापस;
	पूर्ण

	अगर (!vअगर->p2p &&
	    (iwlwअगरi_mod_params.uapsd_disable & IWL_DISABLE_UAPSD_BSS)) अणु
		vअगर->driver_flags &= ~IEEE80211_VIF_SUPPORTS_UAPSD;
		वापस;
	पूर्ण

	क्रम (i = 0; i < IWL_MVM_UAPSD_NOAGG_LIST_LEN; i++) अणु
		अगर (ether_addr_equal(mvm->uapsd_noagg_bssids[i].addr, bssid)) अणु
			vअगर->driver_flags &= ~IEEE80211_VIF_SUPPORTS_UAPSD;
			वापस;
		पूर्ण
	पूर्ण

	vअगर->driver_flags |= IEEE80211_VIF_SUPPORTS_UAPSD;
पूर्ण

अटल व्योम
iwl_mvm_tdls_check_trigger(काष्ठा iwl_mvm *mvm,
			   काष्ठा ieee80211_vअगर *vअगर, u8 *peer_addr,
			   क्रमागत nl80211_tdls_operation action)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_tdls *tdls_trig;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vअगर_to_wdev(vअगर),
				     FW_DBG_TRIGGER_TDLS);
	अगर (!trig)
		वापस;

	tdls_trig = (व्योम *)trig->data;

	अगर (!(tdls_trig->action_biपंचांगap & BIT(action)))
		वापस;

	अगर (tdls_trig->peer_mode &&
	    स_भेद(tdls_trig->peer, peer_addr, ETH_ALEN) != 0)
		वापस;

	iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
				"TDLS event occurred, peer %pM, action %d",
				peer_addr, action);
पूर्ण

काष्ठा iwl_mvm_he_obss_narrow_bw_ru_data अणु
	bool tolerated;
पूर्ण;

अटल व्योम iwl_mvm_check_he_obss_narrow_bw_ru_iter(काष्ठा wiphy *wiphy,
						    काष्ठा cfg80211_bss *bss,
						    व्योम *_data)
अणु
	काष्ठा iwl_mvm_he_obss_narrow_bw_ru_data *data = _data;
	स्थिर काष्ठा element *elem;

	elem = cfg80211_find_elem(WLAN_EID_EXT_CAPABILITY, bss->ies->data,
				  bss->ies->len);

	अगर (!elem || elem->datalen < 10 ||
	    !(elem->data[10] &
	      WLAN_EXT_CAPA10_OBSS_NARROW_BW_RU_TOLERANCE_SUPPORT)) अणु
		data->tolerated = false;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_check_he_obss_narrow_bw_ru(काष्ठा ieee80211_hw *hw,
					       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_he_obss_narrow_bw_ru_data iter_data = अणु
		.tolerated = true,
	पूर्ण;

	अगर (!(vअगर->bss_conf.chandef.chan->flags & IEEE80211_CHAN_RADAR)) अणु
		mvmvअगर->he_ru_2mhz_block = false;
		वापस;
	पूर्ण

	cfg80211_bss_iter(hw->wiphy, &vअगर->bss_conf.chandef,
			  iwl_mvm_check_he_obss_narrow_bw_ru_iter,
			  &iter_data);

	/*
	 * If there is at least one AP on radar channel that cannot
	 * tolerate 26-tone RU UL OFDMA transmissions using HE TB PPDU.
	 */
	mvmvअगर->he_ru_2mhz_block = !iter_data.tolerated;
पूर्ण

अटल व्योम iwl_mvm_reset_cca_40mhz_workaround(काष्ठा iwl_mvm *mvm,
					       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	अगर (!mvm->cca_40mhz_workaround)
		वापस;

	/* decrement and check that we reached zero */
	mvm->cca_40mhz_workaround--;
	अगर (mvm->cca_40mhz_workaround)
		वापस;

	sband = mvm->hw->wiphy->bands[NL80211_BAND_2GHZ];

	sband->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;

	he_cap = ieee80211_get_he_अगरtype_cap(sband,
					     ieee80211_vअगर_type_p2p(vअगर));

	अगर (he_cap) अणु
		/* we know that ours is writable */
		काष्ठा ieee80211_sta_he_cap *he = (व्योम *)he_cap;

		he->he_cap_elem.phy_cap_info[0] |=
			IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G;
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_mvm_mac_sta_state(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta,
				 क्रमागत ieee80211_sta_state old_state,
				 क्रमागत ieee80211_sta_state new_state)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	पूर्णांक ret;

	IWL_DEBUG_MAC80211(mvm, "station %pM state change %d->%d\n",
			   sta->addr, old_state, new_state);

	/* this would be a mac80211 bug ... but करोn't crash */
	अगर (WARN_ON_ONCE(!mvmvअगर->phy_ctxt))
		वापस test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status) ? 0 : -EINVAL;

	/*
	 * If we are in a STA removal flow and in DQA mode:
	 *
	 * This is after the sync_rcu part, so the queues have alपढ़ोy been
	 * flushed. No more TXs on their way in mac80211's path, and no more in
	 * the queues.
	 * Also, we won't be getting any new TX frames क्रम this station.
	 * What we might have are deferred TX frames that need to be taken care
	 * of.
	 *
	 * Drop any still-queued deferred-frame beक्रमe removing the STA, and
	 * make sure the worker is no दीर्घer handling frames क्रम this STA.
	 */
	अगर (old_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST) अणु
		flush_work(&mvm->add_stream_wk);

		/*
		 * No need to make sure deferred TX indication is off since the
		 * worker will alपढ़ोy हटाओ it अगर it was on
		 */

		/*
		 * Additionally, reset the 40 MHz capability अगर we disconnected
		 * from the AP now.
		 */
		iwl_mvm_reset_cca_40mhz_workaround(mvm, vअगर);
	पूर्ण

	mutex_lock(&mvm->mutex);
	/* track whether or not the station is associated */
	mvm_sta->sta_state = new_state;

	अगर (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) अणु
		/*
		 * Firmware bug - it'll crash अगर the beacon पूर्णांकerval is less
		 * than 16. We can't aव्योम connecting at all, so refuse the
		 * station state change, this will cause mac80211 to abanकरोn
		 * attempts to connect to this AP, and eventually wpa_s will
		 * blocklist the AP...
		 */
		अगर (vअगर->type == NL80211_IFTYPE_STATION &&
		    vअगर->bss_conf.beacon_पूर्णांक < 16) अणु
			IWL_ERR(mvm,
				"AP %pM beacon interval is %d, refusing due to firmware bug!\n",
				sta->addr, vअगर->bss_conf.beacon_पूर्णांक);
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		अगर (vअगर->type == NL80211_IFTYPE_STATION)
			vअगर->bss_conf.he_support = sta->he_cap.has_he;

		अगर (sta->tdls &&
		    (vअगर->p2p ||
		     iwl_mvm_tdls_sta_count(mvm, शून्य) ==
						IWL_MVM_TDLS_STA_COUNT ||
		     iwl_mvm_phy_ctx_count(mvm) > 1)) अणु
			IWL_DEBUG_MAC80211(mvm, "refusing TDLS sta\n");
			ret = -EBUSY;
			जाओ out_unlock;
		पूर्ण

		ret = iwl_mvm_add_sta(mvm, vअगर, sta);
		अगर (sta->tdls && ret == 0) अणु
			iwl_mvm_recalc_tdls_state(mvm, vअगर, true);
			iwl_mvm_tdls_check_trigger(mvm, vअगर, sta->addr,
						   NL80211_TDLS_SETUP);
		पूर्ण

		sta->max_rc_amsdu_len = 1;
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_AUTH) अणु
		/*
		 * EBS may be disabled due to previous failures reported by FW.
		 * Reset EBS status here assuming environment has been changed.
		 */
		mvm->last_ebs_successful = true;
		iwl_mvm_check_uapsd(mvm, vअगर, sta->addr);
		ret = 0;
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC) अणु
		अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
			vअगर->bss_conf.he_support = sta->he_cap.has_he;
			mvmvअगर->ap_assoc_sta_count++;
			iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);
			अगर (vअगर->bss_conf.he_support &&
			    !iwlwअगरi_mod_params.disable_11ax)
				iwl_mvm_cfg_he_sta(mvm, vअगर, mvm_sta->sta_id);
		पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
			vअगर->bss_conf.he_support = sta->he_cap.has_he;

			mvmvअगर->he_ru_2mhz_block = false;
			अगर (sta->he_cap.has_he)
				iwl_mvm_check_he_obss_narrow_bw_ru(hw, vअगर);

			iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);
		पूर्ण

		iwl_mvm_rs_rate_init(mvm, sta, mvmvअगर->phy_ctxt->channel->band,
				     false);
		ret = iwl_mvm_update_sta(mvm, vअगर, sta);
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTHORIZED) अणु
		ret = 0;

		/* we करोn't support TDLS during DCM */
		अगर (iwl_mvm_phy_ctx_count(mvm) > 1)
			iwl_mvm_tearकरोwn_tdls_peers(mvm);

		अगर (sta->tdls)
			iwl_mvm_tdls_check_trigger(mvm, vअगर, sta->addr,
						   NL80211_TDLS_ENABLE_LINK);

		/* enable beacon filtering */
		WARN_ON(iwl_mvm_enable_beacon_filter(mvm, vअगर, 0));

		/*
		 * Now that the station is authorized, i.e., keys were alपढ़ोy
		 * installed, need to indicate to the FW that
		 * multicast data frames can be क्रमwarded to the driver
		 */
		iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);

		iwl_mvm_rs_rate_init(mvm, sta, mvmvअगर->phy_ctxt->channel->band,
				     true);
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_AUTHORIZED &&
		   new_state == IEEE80211_STA_ASSOC) अणु
		/* Multicast data frames are no दीर्घer allowed */
		iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);

		/* disable beacon filtering */
		ret = iwl_mvm_disable_beacon_filter(mvm, vअगर, 0);
		WARN_ON(ret &&
			!test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED,
				  &mvm->status));
		ret = 0;
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTH) अणु
		अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
			mvmvअगर->ap_assoc_sta_count--;
			iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);
		पूर्ण
		ret = 0;
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_NONE) अणु
		ret = 0;
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_NOTEXIST) अणु
		ret = iwl_mvm_rm_sta(mvm, vअगर, sta);
		अगर (sta->tdls) अणु
			iwl_mvm_recalc_tdls_state(mvm, vअगर, false);
			iwl_mvm_tdls_check_trigger(mvm, vअगर, sta->addr,
						   NL80211_TDLS_DISABLE_LINK);
		पूर्ण

		अगर (unlikely(ret &&
			     test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED,
				      &mvm->status)))
			ret = 0;
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण
 out_unlock:
	mutex_unlock(&mvm->mutex);

	अगर (sta->tdls && ret == 0) अणु
		अगर (old_state == IEEE80211_STA_NOTEXIST &&
		    new_state == IEEE80211_STA_NONE)
			ieee80211_reserve_tid(sta, IWL_MVM_TDLS_FW_TID);
		अन्यथा अगर (old_state == IEEE80211_STA_NONE &&
			 new_state == IEEE80211_STA_NOTEXIST)
			ieee80211_unreserve_tid(sta, IWL_MVM_TDLS_FW_TID);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_mac_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mvm->rts_threshold = value;

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_sta_rc_update(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_sta *sta, u32 changed)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (changed & (IEEE80211_RC_BW_CHANGED |
		       IEEE80211_RC_SUPP_RATES_CHANGED |
		       IEEE80211_RC_NSS_CHANGED))
		iwl_mvm_rs_rate_init(mvm, sta, mvmvअगर->phy_ctxt->channel->band,
				     true);

	अगर (vअगर->type == NL80211_IFTYPE_STATION &&
	    changed & IEEE80211_RC_NSS_CHANGED)
		iwl_mvm_sf_update(mvm, vअगर, false);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_conf_tx(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर, u16 ac,
			       स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	mvmvअगर->queue_params[ac] = *params;

	/*
	 * No need to update right away, we'll get BSS_CHANGED_QOS
	 * The exception is P2P_DEVICE पूर्णांकerface which needs immediate update.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
		पूर्णांक ret;

		mutex_lock(&mvm->mutex);
		ret = iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);
		mutex_unlock(&mvm->mutex);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_mac_mgd_prepare_tx(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       u16 req_duration)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	u32 duration = IWL_MVM_TE_SESSION_PROTECTION_MAX_TIME_MS;
	u32 min_duration = IWL_MVM_TE_SESSION_PROTECTION_MIN_TIME_MS;

	अगर (req_duration > duration)
		duration = req_duration;

	mutex_lock(&mvm->mutex);
	/* Try really hard to protect the session and hear a beacon
	 * The new session protection command allows us to protect the
	 * session क्रम a much दीर्घer समय since the firmware will पूर्णांकernally
	 * create two events: a 300TU one with a very high priority that
	 * won't be fragmented which should be enough क्रम 99% of the हालs,
	 * and another one (which we configure here to be 900TU दीर्घ) which
	 * will have a slightly lower priority, but more importantly, can be
	 * fragmented so that it'll allow other activities to run.
	 */
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_SESSION_PROT_CMD))
		iwl_mvm_schedule_session_protection(mvm, vअगर, 900,
						    min_duration, false);
	अन्यथा
		iwl_mvm_protect_session(mvm, vअगर, duration,
					min_duration, 500, false);
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_sched_scan_start(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा cfg80211_sched_scan_request *req,
					काष्ठा ieee80211_scan_ies *ies)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	पूर्णांक ret;

	mutex_lock(&mvm->mutex);

	अगर (!vअगर->bss_conf.idle) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = iwl_mvm_sched_scan_start(mvm, vअगर, req, ies, IWL_MVM_SCAN_SCHED);

out:
	mutex_unlock(&mvm->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_mac_sched_scan_stop(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);

	/* Due to a race condition, it's possible that mac80211 asks
	 * us to stop a sched_scan when it's alपढ़ोy stopped.  This
	 * can happen, क्रम instance, अगर we stopped the scan ourselves,
	 * called ieee80211_sched_scan_stopped() and the userspace called
	 * stop sched scan scan beक्रमe ieee80211_sched_scan_stopped_work()
	 * could run.  To handle this, simply वापस अगर the scan is
	 * not running.
	*/
	अगर (!(mvm->scan_status & IWL_MVM_SCAN_SCHED)) अणु
		mutex_unlock(&mvm->mutex);
		वापस 0;
	पूर्ण

	ret = iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_SCHED, false);
	mutex_unlock(&mvm->mutex);
	iwl_mvm_रुको_क्रम_async_handlers(mvm);

	वापस ret;
पूर्ण

अटल पूर्णांक __iwl_mvm_mac_set_key(काष्ठा ieee80211_hw *hw,
				 क्रमागत set_key_cmd cmd,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta,
				 काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा iwl_mvm_key_pn *ptk_pn;
	पूर्णांक keyidx = key->keyidx;
	पूर्णांक ret, i;
	u8 key_offset;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (!mvm->trans->trans_cfg->gen2) अणु
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
			key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
			key->flags |= IEEE80211_KEY_FLAG_PUT_MIC_SPACE;
		पूर्ण अन्यथा अणु
			IWL_DEBUG_MAC80211(mvm, "Use SW encryption for TKIP\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		अगर (!iwl_mvm_has_new_tx_api(mvm))
			key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		WARN_ON_ONCE(!ieee80211_hw_check(hw, MFP_CAPABLE));
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		अगर (vअगर->type == NL80211_IFTYPE_STATION)
			अवरोध;
		अगर (iwl_mvm_has_new_tx_api(mvm))
			वापस -EOPNOTSUPP;
		/* support HW crypto on TX */
		वापस 0;
	शेष:
		/* currently FW supports only one optional cipher scheme */
		अगर (hw->n_cipher_schemes &&
		    hw->cipher_schemes->cipher == key->cipher)
			key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		अन्यथा
			वापस -EOPNOTSUPP;
	पूर्ण

	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (keyidx == 6 || keyidx == 7)
			rcu_assign_poपूर्णांकer(mvmvअगर->bcn_prot.keys[keyidx - 6],
					   key);

		अगर ((vअगर->type == NL80211_IFTYPE_ADHOC ||
		     vअगर->type == NL80211_IFTYPE_AP) && !sta) अणु
			/*
			 * GTK on AP पूर्णांकerface is a TX-only key, वापस 0;
			 * on IBSS they're per-station and because we're lazy
			 * we करोn't support them क्रम RX, so करो the same.
			 * CMAC/GMAC in AP/IBSS modes must be करोne in software.
			 */
			अगर (key->cipher == WLAN_CIPHER_SUITE_AES_CMAC ||
			    key->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_128 ||
			    key->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_256) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण

			अगर (key->cipher != WLAN_CIPHER_SUITE_GCMP &&
			    key->cipher != WLAN_CIPHER_SUITE_GCMP_256 &&
			    !iwl_mvm_has_new_tx_api(mvm)) अणु
				key->hw_key_idx = STA_KEY_IDX_INVALID;
				ret = 0;
				अवरोध;
			पूर्ण

			अगर (!mvmvअगर->ap_ibss_active) अणु
				क्रम (i = 0;
				     i < ARRAY_SIZE(mvmvअगर->ap_early_keys);
				     i++) अणु
					अगर (!mvmvअगर->ap_early_keys[i]) अणु
						mvmvअगर->ap_early_keys[i] = key;
						अवरोध;
					पूर्ण
				पूर्ण

				अगर (i >= ARRAY_SIZE(mvmvअगर->ap_early_keys))
					ret = -ENOSPC;
				अन्यथा
					ret = 0;

				अवरोध;
			पूर्ण
		पूर्ण

		/* During FW restart, in order to restore the state as it was,
		 * करोn't try to reprogram keys we previously failed क्रम.
		 */
		अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		    key->hw_key_idx == STA_KEY_IDX_INVALID) अणु
			IWL_DEBUG_MAC80211(mvm,
					   "skip invalid idx key programming during restart\n");
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		    sta && iwl_mvm_has_new_rx_api(mvm) &&
		    key->flags & IEEE80211_KEY_FLAG_PAIRWISE &&
		    (key->cipher == WLAN_CIPHER_SUITE_CCMP ||
		     key->cipher == WLAN_CIPHER_SUITE_GCMP ||
		     key->cipher == WLAN_CIPHER_SUITE_GCMP_256)) अणु
			काष्ठा ieee80211_key_seq seq;
			पूर्णांक tid, q;

			mvmsta = iwl_mvm_sta_from_mac80211(sta);
			WARN_ON(rcu_access_poपूर्णांकer(mvmsta->ptk_pn[keyidx]));
			ptk_pn = kzalloc(काष्ठा_size(ptk_pn, q,
						     mvm->trans->num_rx_queues),
					 GFP_KERNEL);
			अगर (!ptk_pn) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण

			क्रम (tid = 0; tid < IWL_MAX_TID_COUNT; tid++) अणु
				ieee80211_get_key_rx_seq(key, tid, &seq);
				क्रम (q = 0; q < mvm->trans->num_rx_queues; q++)
					स_नकल(ptk_pn->q[q].pn[tid],
					       seq.ccmp.pn,
					       IEEE80211_CCMP_PN_LEN);
			पूर्ण

			rcu_assign_poपूर्णांकer(mvmsta->ptk_pn[keyidx], ptk_pn);
		पूर्ण

		/* in HW restart reuse the index, otherwise request a new one */
		अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
			key_offset = key->hw_key_idx;
		अन्यथा
			key_offset = STA_KEY_IDX_INVALID;

		IWL_DEBUG_MAC80211(mvm, "set hwcrypto key\n");
		ret = iwl_mvm_set_sta_key(mvm, vअगर, sta, key, key_offset);
		अगर (ret) अणु
			IWL_WARN(mvm, "set key failed\n");
			key->hw_key_idx = STA_KEY_IDX_INVALID;
			/*
			 * can't add key for RX, but we don't need it
			 * in the device क्रम TX so still वापस 0,
			 * unless we have new TX API where we cannot
			 * put key material पूर्णांकo the TX_CMD
			 */
			अगर (iwl_mvm_has_new_tx_api(mvm))
				ret = -EOPNOTSUPP;
			अन्यथा
				ret = 0;
		पूर्ण

		अवरोध;
	हाल DISABLE_KEY:
		अगर (keyidx == 6 || keyidx == 7)
			RCU_INIT_POINTER(mvmvअगर->bcn_prot.keys[keyidx - 6],
					 शून्य);

		ret = -ENOENT;
		क्रम (i = 0; i < ARRAY_SIZE(mvmvअगर->ap_early_keys); i++) अणु
			अगर (mvmvअगर->ap_early_keys[i] == key) अणु
				mvmvअगर->ap_early_keys[i] = शून्य;
				ret = 0;
			पूर्ण
		पूर्ण

		/* found in pending list - करोn't करो anything अन्यथा */
		अगर (ret == 0)
			अवरोध;

		अगर (key->hw_key_idx == STA_KEY_IDX_INVALID) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		अगर (sta && iwl_mvm_has_new_rx_api(mvm) &&
		    key->flags & IEEE80211_KEY_FLAG_PAIRWISE &&
		    (key->cipher == WLAN_CIPHER_SUITE_CCMP ||
		     key->cipher == WLAN_CIPHER_SUITE_GCMP ||
		     key->cipher == WLAN_CIPHER_SUITE_GCMP_256)) अणु
			mvmsta = iwl_mvm_sta_from_mac80211(sta);
			ptk_pn = rcu_dereference_रक्षित(
						mvmsta->ptk_pn[keyidx],
						lockdep_is_held(&mvm->mutex));
			RCU_INIT_POINTER(mvmsta->ptk_pn[keyidx], शून्य);
			अगर (ptk_pn)
				kमुक्त_rcu(ptk_pn, rcu_head);
		पूर्ण

		IWL_DEBUG_MAC80211(mvm, "disable hwcrypto key\n");
		ret = iwl_mvm_हटाओ_sta_key(mvm, vअगर, sta, key);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_mac_set_key(काष्ठा ieee80211_hw *hw,
			       क्रमागत set_key_cmd cmd,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);
	ret = __iwl_mvm_mac_set_key(hw, cmd, vअगर, sta, key);
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_mac_update_tkip_key(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_key_conf *keyconf,
					काष्ठा ieee80211_sta *sta,
					u32 iv32, u16 *phase1key)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	अगर (keyconf->hw_key_idx == STA_KEY_IDX_INVALID)
		वापस;

	iwl_mvm_update_tkip_key(mvm, vअगर, keyconf, sta, iv32, phase1key);
पूर्ण


अटल bool iwl_mvm_rx_aux_roc(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			       काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_mvm *mvm =
		container_of(notअगर_रुको, काष्ठा iwl_mvm, notअगर_रुको);
	काष्ठा iwl_hs20_roc_res *resp;
	पूर्णांक resp_len = iwl_rx_packet_payload_len(pkt);
	काष्ठा iwl_mvm_समय_event_data *te_data = data;

	अगर (WARN_ON(pkt->hdr.cmd != HOT_SPOT_CMD))
		वापस true;

	अगर (WARN_ON_ONCE(resp_len != माप(*resp))) अणु
		IWL_ERR(mvm, "Invalid HOT_SPOT_CMD response\n");
		वापस true;
	पूर्ण

	resp = (व्योम *)pkt->data;

	IWL_DEBUG_TE(mvm,
		     "Aux ROC: Received response from ucode: status=%d uid=%d\n",
		     resp->status, resp->event_unique_id);

	te_data->uid = le32_to_cpu(resp->event_unique_id);
	IWL_DEBUG_TE(mvm, "TIME_EVENT_CMD response - UID = 0x%x\n",
		     te_data->uid);

	spin_lock_bh(&mvm->समय_event_lock);
	list_add_tail(&te_data->list, &mvm->aux_roc_te_list);
	spin_unlock_bh(&mvm->समय_event_lock);

	वापस true;
पूर्ण

#घोषणा AUX_ROC_MIN_DURATION MSEC_TO_TU(100)
#घोषणा AUX_ROC_MIN_DELAY MSEC_TO_TU(200)
#घोषणा AUX_ROC_MAX_DELAY MSEC_TO_TU(600)
#घोषणा AUX_ROC_SAFETY_BUFFER MSEC_TO_TU(20)
#घोषणा AUX_ROC_MIN_SAFETY_BUFFER MSEC_TO_TU(10)
अटल पूर्णांक iwl_mvm_send_aux_roc_cmd(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_channel *channel,
				    काष्ठा ieee80211_vअगर *vअगर,
				    पूर्णांक duration)
अणु
	पूर्णांक res;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_समय_event_data *te_data = &mvmvअगर->hs_समय_event_data;
	अटल स्थिर u16 समय_event_response[] = अणु HOT_SPOT_CMD पूर्ण;
	काष्ठा iwl_notअगरication_रुको रुको_समय_event;
	u32 dtim_पूर्णांकerval = vअगर->bss_conf.dtim_period *
		vअगर->bss_conf.beacon_पूर्णांक;
	u32 req_dur, delay;
	काष्ठा iwl_hs20_roc_req aux_roc_req = अणु
		.action = cpu_to_le32(FW_CTXT_ACTION_ADD),
		.id_and_color =
			cpu_to_le32(FW_CMD_ID_AND_COLOR(MAC_INDEX_AUX, 0)),
		.sta_id_and_color = cpu_to_le32(mvm->aux_sta.sta_id),
	पूर्ण;
	काष्ठा iwl_hs20_roc_req_tail *tail = iwl_mvm_chan_info_cmd_tail(mvm,
		&aux_roc_req.channel_info);
	u16 len = माप(aux_roc_req) - iwl_mvm_chan_info_padding(mvm);

	/* Set the channel info data */
	iwl_mvm_set_chan_info(mvm, &aux_roc_req.channel_info, channel->hw_value,
			      iwl_mvm_phy_band_from_nl80211(channel->band),
			      PHY_VHT_CHANNEL_MODE20,
			      0);

	/* Set the समय and duration */
	tail->apply_समय = cpu_to_le32(iwl_mvm_get_sysसमय(mvm));

	delay = AUX_ROC_MIN_DELAY;
	req_dur = MSEC_TO_TU(duration);

	/*
	 * If we are associated we want the delay समय to be at least one
	 * dtim पूर्णांकerval so that the FW can रुको until after the DTIM and
	 * then start the समय event, this will potentially allow us to
	 * reमुख्य off-channel क्रम the max duration.
	 * Since we want to use almost a whole dtim पूर्णांकerval we would also
	 * like the delay to be क्रम 2-3 dtim पूर्णांकervals, in हाल there are
	 * other समय events with higher priority.
	 */
	अगर (vअगर->bss_conf.assoc) अणु
		delay = min_t(u32, dtim_पूर्णांकerval * 3, AUX_ROC_MAX_DELAY);
		/* We cannot reमुख्य off-channel दीर्घer than the DTIM पूर्णांकerval */
		अगर (dtim_पूर्णांकerval <= req_dur) अणु
			req_dur = dtim_पूर्णांकerval - AUX_ROC_SAFETY_BUFFER;
			अगर (req_dur <= AUX_ROC_MIN_DURATION)
				req_dur = dtim_पूर्णांकerval -
					AUX_ROC_MIN_SAFETY_BUFFER;
		पूर्ण
	पूर्ण

	tail->duration = cpu_to_le32(req_dur);
	tail->apply_समय_max_delay = cpu_to_le32(delay);

	IWL_DEBUG_TE(mvm,
		     "ROC: Requesting to remain on channel %u for %ums\n",
		     channel->hw_value, req_dur);
	IWL_DEBUG_TE(mvm,
		     "\t(requested = %ums, max_delay = %ums, dtim_interval = %ums)\n",
		     duration, delay, dtim_पूर्णांकerval);

	/* Set the node address */
	स_नकल(tail->node_addr, vअगर->addr, ETH_ALEN);

	lockdep_निश्चित_held(&mvm->mutex);

	spin_lock_bh(&mvm->समय_event_lock);

	अगर (WARN_ON(te_data->id == HOT_SPOT_CMD)) अणु
		spin_unlock_bh(&mvm->समय_event_lock);
		वापस -EIO;
	पूर्ण

	te_data->vअगर = vअगर;
	te_data->duration = duration;
	te_data->id = HOT_SPOT_CMD;

	spin_unlock_bh(&mvm->समय_event_lock);

	/*
	 * Use a notअगरication रुको, which really just processes the
	 * command response and करोesn't रुको क्रम anything, in order
	 * to be able to process the response and get the UID inside
	 * the RX path. Using CMD_WANT_SKB करोesn't work because it
	 * stores the buffer and then wakes up this thपढ़ो, by which
	 * समय another notअगरication (that the समय event started)
	 * might alपढ़ोy be processed unsuccessfully.
	 */
	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको, &रुको_समय_event,
				   समय_event_response,
				   ARRAY_SIZE(समय_event_response),
				   iwl_mvm_rx_aux_roc, te_data);

	res = iwl_mvm_send_cmd_pdu(mvm, HOT_SPOT_CMD, 0, len,
				   &aux_roc_req);

	अगर (res) अणु
		IWL_ERR(mvm, "Couldn't send HOT_SPOT_CMD: %d\n", res);
		iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &रुको_समय_event);
		जाओ out_clear_te;
	पूर्ण

	/* No need to रुको क्रम anything, so just pass 1 (0 isn't valid) */
	res = iwl_रुको_notअगरication(&mvm->notअगर_रुको, &रुको_समय_event, 1);
	/* should never fail */
	WARN_ON_ONCE(res);

	अगर (res) अणु
 out_clear_te:
		spin_lock_bh(&mvm->समय_event_lock);
		iwl_mvm_te_clear_data(mvm, te_data);
		spin_unlock_bh(&mvm->समय_event_lock);
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक iwl_mvm_roc(काष्ठा ieee80211_hw *hw,
		       काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_channel *channel,
		       पूर्णांक duration,
		       क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt;
	पूर्णांक ret, i;

	IWL_DEBUG_MAC80211(mvm, "enter (%d, %d, %d)\n", channel->hw_value,
			   duration, type);

	/*
	 * Flush the करोne work, just in हाल it's still pending, so that
	 * the work it करोes can complete and we can accept new frames.
	 */
	flush_work(&mvm->roc_करोne_wk);

	mutex_lock(&mvm->mutex);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_HOTSPOT_SUPPORT)) अणु
			/* Use aux roc framework (HS20) */
			अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
						  ADD_STA, 0) >= 12) अणु
				u32 lmac_id;

				lmac_id = iwl_mvm_get_lmac_id(mvm->fw,
							      channel->band);
				ret = iwl_mvm_add_aux_sta(mvm, lmac_id);
				अगर (WARN(ret,
					 "Failed to allocate aux station"))
					जाओ out_unlock;
			पूर्ण
			ret = iwl_mvm_send_aux_roc_cmd(mvm, channel,
						       vअगर, duration);
			जाओ out_unlock;
		पूर्ण
		IWL_ERR(mvm, "hotspot not supported\n");
		ret = -EINVAL;
		जाओ out_unlock;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		/* handle below */
		अवरोध;
	शेष:
		IWL_ERR(mvm, "vif isn't P2P_DEVICE: %d\n", vअगर->type);
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	क्रम (i = 0; i < NUM_PHY_CTX; i++) अणु
		phy_ctxt = &mvm->phy_ctxts[i];
		अगर (phy_ctxt->ref == 0 || mvmvअगर->phy_ctxt == phy_ctxt)
			जारी;

		अगर (phy_ctxt->ref && channel == phy_ctxt->channel) अणु
			/*
			 * Unbind the P2P_DEVICE from the current PHY context,
			 * and अगर the PHY context is not used हटाओ it.
			 */
			ret = iwl_mvm_binding_हटाओ_vअगर(mvm, vअगर);
			अगर (WARN(ret, "Failed unbinding P2P_DEVICE\n"))
				जाओ out_unlock;

			iwl_mvm_phy_ctxt_unref(mvm, mvmvअगर->phy_ctxt);

			/* Bind the P2P_DEVICE to the current PHY Context */
			mvmvअगर->phy_ctxt = phy_ctxt;

			ret = iwl_mvm_binding_add_vअगर(mvm, vअगर);
			अगर (WARN(ret, "Failed binding P2P_DEVICE\n"))
				जाओ out_unlock;

			iwl_mvm_phy_ctxt_ref(mvm, mvmvअगर->phy_ctxt);
			जाओ schedule_समय_event;
		पूर्ण
	पूर्ण

	/* Need to update the PHY context only अगर the ROC channel changed */
	अगर (channel == mvmvअगर->phy_ctxt->channel)
		जाओ schedule_समय_event;

	cfg80211_chandef_create(&chandef, channel, NL80211_CHAN_NO_HT);

	/*
	 * Change the PHY context configuration as it is currently referenced
	 * only by the P2P Device MAC
	 */
	अगर (mvmvअगर->phy_ctxt->ref == 1) अणु
		ret = iwl_mvm_phy_ctxt_changed(mvm, mvmvअगर->phy_ctxt,
					       &chandef, 1, 1);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		/*
		 * The PHY context is shared with other MACs. Need to हटाओ the
		 * P2P Device from the binding, allocate an new PHY context and
		 * create a new binding
		 */
		phy_ctxt = iwl_mvm_get_मुक्त_phy_ctxt(mvm);
		अगर (!phy_ctxt) अणु
			ret = -ENOSPC;
			जाओ out_unlock;
		पूर्ण

		ret = iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, &chandef,
					       1, 1);
		अगर (ret) अणु
			IWL_ERR(mvm, "Failed to change PHY context\n");
			जाओ out_unlock;
		पूर्ण

		/* Unbind the P2P_DEVICE from the current PHY context */
		ret = iwl_mvm_binding_हटाओ_vअगर(mvm, vअगर);
		अगर (WARN(ret, "Failed unbinding P2P_DEVICE\n"))
			जाओ out_unlock;

		iwl_mvm_phy_ctxt_unref(mvm, mvmvअगर->phy_ctxt);

		/* Bind the P2P_DEVICE to the new allocated PHY context */
		mvmvअगर->phy_ctxt = phy_ctxt;

		ret = iwl_mvm_binding_add_vअगर(mvm, vअगर);
		अगर (WARN(ret, "Failed binding P2P_DEVICE\n"))
			जाओ out_unlock;

		iwl_mvm_phy_ctxt_ref(mvm, mvmvअगर->phy_ctxt);
	पूर्ण

schedule_समय_event:
	/* Schedule the समय events */
	ret = iwl_mvm_start_p2p_roc(mvm, vअगर, duration, type);

out_unlock:
	mutex_unlock(&mvm->mutex);
	IWL_DEBUG_MAC80211(mvm, "leave\n");
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_cancel_roc(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	IWL_DEBUG_MAC80211(mvm, "enter\n");

	mutex_lock(&mvm->mutex);
	iwl_mvm_stop_roc(mvm, vअगर);
	mutex_unlock(&mvm->mutex);

	IWL_DEBUG_MAC80211(mvm, "leave\n");
	वापस 0;
पूर्ण

काष्ठा iwl_mvm_fपंचांग_responder_iter_data अणु
	bool responder;
	काष्ठा ieee80211_chanctx_conf *ctx;
पूर्ण;

अटल व्योम iwl_mvm_fपंचांग_responder_chanctx_iter(व्योम *_data, u8 *mac,
					       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_fपंचांग_responder_iter_data *data = _data;

	अगर (rcu_access_poपूर्णांकer(vअगर->chanctx_conf) == data->ctx &&
	    vअगर->type == NL80211_IFTYPE_AP && vअगर->bss_conf.fपंचांगr_params)
		data->responder = true;
पूर्ण

अटल bool iwl_mvm_is_fपंचांग_responder_chanctx(काष्ठा iwl_mvm *mvm,
					     काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा iwl_mvm_fपंचांग_responder_iter_data data = अणु
		.responder = false,
		.ctx = ctx,
	पूर्ण;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_fपंचांग_responder_chanctx_iter,
					&data);
	वापस data.responder;
पूर्ण

अटल पूर्णांक __iwl_mvm_add_chanctx(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	u16 *phy_ctxt_id = (u16 *)ctx->drv_priv;
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt;
	bool responder = iwl_mvm_is_fपंचांग_responder_chanctx(mvm, ctx);
	काष्ठा cfg80211_chan_def *def = responder ? &ctx->def : &ctx->min_def;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	IWL_DEBUG_MAC80211(mvm, "Add channel context\n");

	phy_ctxt = iwl_mvm_get_मुक्त_phy_ctxt(mvm);
	अगर (!phy_ctxt) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	ret = iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, def,
				       ctx->rx_chains_अटल,
				       ctx->rx_chains_dynamic);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to add PHY context\n");
		जाओ out;
	पूर्ण

	iwl_mvm_phy_ctxt_ref(mvm, phy_ctxt);
	*phy_ctxt_id = phy_ctxt->id;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_add_chanctx(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);
	ret = __iwl_mvm_add_chanctx(mvm, ctx);
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम __iwl_mvm_हटाओ_chanctx(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	u16 *phy_ctxt_id = (u16 *)ctx->drv_priv;
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];

	lockdep_निश्चित_held(&mvm->mutex);

	iwl_mvm_phy_ctxt_unref(mvm, phy_ctxt);
पूर्ण

अटल व्योम iwl_mvm_हटाओ_chanctx(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);
	__iwl_mvm_हटाओ_chanctx(mvm, ctx);
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम iwl_mvm_change_chanctx(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_chanctx_conf *ctx,
				   u32 changed)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	u16 *phy_ctxt_id = (u16 *)ctx->drv_priv;
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	bool responder = iwl_mvm_is_fपंचांग_responder_chanctx(mvm, ctx);
	काष्ठा cfg80211_chan_def *def = responder ? &ctx->def : &ctx->min_def;

	अगर (WARN_ONCE((phy_ctxt->ref > 1) &&
		      (changed & ~(IEEE80211_CHANCTX_CHANGE_WIDTH |
				   IEEE80211_CHANCTX_CHANGE_RX_CHAINS |
				   IEEE80211_CHANCTX_CHANGE_RADAR |
				   IEEE80211_CHANCTX_CHANGE_MIN_WIDTH)),
		      "Cannot change PHY. Ref=%d, changed=0x%X\n",
		      phy_ctxt->ref, changed))
		वापस;

	mutex_lock(&mvm->mutex);

	/* we are only changing the min_width, may be a noop */
	अगर (changed == IEEE80211_CHANCTX_CHANGE_MIN_WIDTH) अणु
		अगर (phy_ctxt->width == def->width)
			जाओ out_unlock;

		/* we are just toggling between 20_NOHT and 20 */
		अगर (phy_ctxt->width <= NL80211_CHAN_WIDTH_20 &&
		    def->width <= NL80211_CHAN_WIDTH_20)
			जाओ out_unlock;
	पूर्ण

	iwl_mvm_bt_coex_vअगर_change(mvm);
	iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, def,
				 ctx->rx_chains_अटल,
				 ctx->rx_chains_dynamic);

out_unlock:
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल पूर्णांक __iwl_mvm_assign_vअगर_chanctx(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_chanctx_conf *ctx,
					bool चयनing_chanctx)
अणु
	u16 *phy_ctxt_id = (u16 *)ctx->drv_priv;
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	mvmvअगर->phy_ctxt = phy_ctxt;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
		/* only needed अगर we're चयनing chanctx (i.e. during CSA) */
		अगर (चयनing_chanctx) अणु
			mvmvअगर->ap_ibss_active = true;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल NL80211_IFTYPE_ADHOC:
		/*
		 * The AP binding flow is handled as part of the start_ap flow
		 * (in bss_info_changed), similarly क्रम IBSS.
		 */
		ret = 0;
		जाओ out;
	हाल NL80211_IFTYPE_STATION:
		mvmvअगर->csa_bcn_pending = false;
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		/* always disable PS when a monitor पूर्णांकerface is active */
		mvmvअगर->ps_disabled = true;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = iwl_mvm_binding_add_vअगर(mvm, vअगर);
	अगर (ret)
		जाओ out;

	/*
	 * Power state must be updated beक्रमe quotas,
	 * otherwise fw will complain.
	 */
	iwl_mvm_घातer_update_mac(mvm);

	/* Setting the quota at this stage is only required क्रम monitor
	 * पूर्णांकerfaces. For the other types, the bss_info changed flow
	 * will handle quota settings.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_MONITOR) अणु
		mvmvअगर->monitor_active = true;
		ret = iwl_mvm_update_quotas(mvm, false, शून्य);
		अगर (ret)
			जाओ out_हटाओ_binding;

		ret = iwl_mvm_add_snअगर_sta(mvm, vअगर);
		अगर (ret)
			जाओ out_हटाओ_binding;

	पूर्ण

	/* Handle binding during CSA */
	अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
		iwl_mvm_update_quotas(mvm, false, शून्य);
		iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);
	पूर्ण

	अगर (चयनing_chanctx && vअगर->type == NL80211_IFTYPE_STATION) अणु
		mvmvअगर->csa_bcn_pending = true;

		अगर (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD)) अणु
			u32 duration = 3 * vअगर->bss_conf.beacon_पूर्णांक;

			/* Protect the session to make sure we hear the first
			 * beacon on the new channel.
			 */
			iwl_mvm_protect_session(mvm, vअगर, duration, duration,
						vअगर->bss_conf.beacon_पूर्णांक / 2,
						true);
		पूर्ण

		iwl_mvm_update_quotas(mvm, false, शून्य);
	पूर्ण

	जाओ out;

out_हटाओ_binding:
	iwl_mvm_binding_हटाओ_vअगर(mvm, vअगर);
	iwl_mvm_घातer_update_mac(mvm);
out:
	अगर (ret)
		mvmvअगर->phy_ctxt = शून्य;
	वापस ret;
पूर्ण
अटल पूर्णांक iwl_mvm_assign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);
	ret = __iwl_mvm_assign_vअगर_chanctx(mvm, vअगर, ctx, false);
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम __iwl_mvm_unassign_vअगर_chanctx(काष्ठा iwl_mvm *mvm,
					   काष्ठा ieee80211_vअगर *vअगर,
					   काष्ठा ieee80211_chanctx_conf *ctx,
					   bool चयनing_chanctx)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा ieee80211_vअगर *disabled_vअगर = शून्य;

	lockdep_निश्चित_held(&mvm->mutex);

	iwl_mvm_हटाओ_समय_event(mvm, mvmvअगर, &mvmvअगर->समय_event_data);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		जाओ out;
	हाल NL80211_IFTYPE_MONITOR:
		mvmvअगर->monitor_active = false;
		mvmvअगर->ps_disabled = false;
		iwl_mvm_rm_snअगर_sta(mvm, vअगर);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		/* This part is triggered only during CSA */
		अगर (!चयनing_chanctx || !mvmvअगर->ap_ibss_active)
			जाओ out;

		mvmvअगर->csa_countकरोwn = false;

		/* Set CS bit on all the stations */
		iwl_mvm_modअगरy_all_sta_disable_tx(mvm, mvmvअगर, true);

		/* Save blocked अगरace, the समयout is set on the next beacon */
		rcu_assign_poपूर्णांकer(mvm->csa_tx_blocked_vअगर, vअगर);

		mvmvअगर->ap_ibss_active = false;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (!चयनing_chanctx)
			अवरोध;

		disabled_vअगर = vअगर;

		अगर (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD))
			iwl_mvm_mac_ctxt_changed(mvm, vअगर, true, शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	iwl_mvm_update_quotas(mvm, false, disabled_vअगर);
	iwl_mvm_binding_हटाओ_vअगर(mvm, vअगर);

out:
	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD) &&
	    चयनing_chanctx)
		वापस;
	mvmvअगर->phy_ctxt = शून्य;
	iwl_mvm_घातer_update_mac(mvm);
पूर्ण

अटल व्योम iwl_mvm_unassign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);
	__iwl_mvm_unassign_vअगर_chanctx(mvm, vअगर, ctx, false);
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल पूर्णांक
iwl_mvm_चयन_vअगर_chanctx_swap(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs)
अणु
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);
	__iwl_mvm_unassign_vअगर_chanctx(mvm, vअगरs[0].vअगर, vअगरs[0].old_ctx, true);
	__iwl_mvm_हटाओ_chanctx(mvm, vअगरs[0].old_ctx);

	ret = __iwl_mvm_add_chanctx(mvm, vअगरs[0].new_ctx);
	अगर (ret) अणु
		IWL_ERR(mvm, "failed to add new_ctx during channel switch\n");
		जाओ out_reassign;
	पूर्ण

	ret = __iwl_mvm_assign_vअगर_chanctx(mvm, vअगरs[0].vअगर, vअगरs[0].new_ctx,
					   true);
	अगर (ret) अणु
		IWL_ERR(mvm,
			"failed to assign new_ctx during channel switch\n");
		जाओ out_हटाओ;
	पूर्ण

	/* we करोn't support TDLS during DCM - can be caused by channel चयन */
	अगर (iwl_mvm_phy_ctx_count(mvm) > 1)
		iwl_mvm_tearकरोwn_tdls_peers(mvm);

	जाओ out;

out_हटाओ:
	__iwl_mvm_हटाओ_chanctx(mvm, vअगरs[0].new_ctx);

out_reassign:
	अगर (__iwl_mvm_add_chanctx(mvm, vअगरs[0].old_ctx)) अणु
		IWL_ERR(mvm, "failed to add old_ctx back after failure.\n");
		जाओ out_restart;
	पूर्ण

	अगर (__iwl_mvm_assign_vअगर_chanctx(mvm, vअगरs[0].vअगर, vअगरs[0].old_ctx,
					 true)) अणु
		IWL_ERR(mvm, "failed to reassign old_ctx after failure.\n");
		जाओ out_restart;
	पूर्ण

	जाओ out;

out_restart:
	/* things keep failing, better restart the hw */
	iwl_mvm_nic_restart(mvm, false);

out:
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक
iwl_mvm_चयन_vअगर_chanctx_reassign(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs)
अणु
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);
	__iwl_mvm_unassign_vअगर_chanctx(mvm, vअगरs[0].vअगर, vअगरs[0].old_ctx, true);

	ret = __iwl_mvm_assign_vअगर_chanctx(mvm, vअगरs[0].vअगर, vअगरs[0].new_ctx,
					   true);
	अगर (ret) अणु
		IWL_ERR(mvm,
			"failed to assign new_ctx during channel switch\n");
		जाओ out_reassign;
	पूर्ण

	जाओ out;

out_reassign:
	अगर (__iwl_mvm_assign_vअगर_chanctx(mvm, vअगरs[0].vअगर, vअगरs[0].old_ctx,
					 true)) अणु
		IWL_ERR(mvm, "failed to reassign old_ctx after failure.\n");
		जाओ out_restart;
	पूर्ण

	जाओ out;

out_restart:
	/* things keep failing, better restart the hw */
	iwl_mvm_nic_restart(mvm, false);

out:
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_चयन_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
				      पूर्णांक n_vअगरs,
				      क्रमागत ieee80211_chanctx_चयन_mode mode)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	/* we only support a single-vअगर right now */
	अगर (n_vअगरs > 1)
		वापस -EOPNOTSUPP;

	चयन (mode) अणु
	हाल CHANCTX_SWMODE_SWAP_CONTEXTS:
		ret = iwl_mvm_चयन_vअगर_chanctx_swap(mvm, vअगरs);
		अवरोध;
	हाल CHANCTX_SWMODE_REASSIGN_VIF:
		ret = iwl_mvm_चयन_vअगर_chanctx_reassign(mvm, vअगरs);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_tx_last_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	वापस mvm->ibss_manager;
पूर्ण

अटल पूर्णांक iwl_mvm_set_tim(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_sta *sta,
			   bool set)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);

	अगर (!mvm_sta || !mvm_sta->vअगर) अणु
		IWL_ERR(mvm, "Station is not associated to a vif\n");
		वापस -EINVAL;
	पूर्ण

	वापस iwl_mvm_mac_ctxt_beacon_changed(mvm, mvm_sta->vअगर);
पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE
अटल स्थिर काष्ठा nla_policy iwl_mvm_पंचांग_policy[IWL_MVM_TM_ATTR_MAX + 1] = अणु
	[IWL_MVM_TM_ATTR_CMD] = अणु .type = NLA_U32 पूर्ण,
	[IWL_MVM_TM_ATTR_NOA_DURATION] = अणु .type = NLA_U32 पूर्ण,
	[IWL_MVM_TM_ATTR_BEACON_FILTER_STATE] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक __iwl_mvm_mac_tesपंचांगode_cmd(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_vअगर *vअगर,
				      व्योम *data, पूर्णांक len)
अणु
	काष्ठा nlattr *tb[IWL_MVM_TM_ATTR_MAX + 1];
	पूर्णांक err;
	u32 noa_duration;

	err = nla_parse_deprecated(tb, IWL_MVM_TM_ATTR_MAX, data, len,
				   iwl_mvm_पंचांग_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[IWL_MVM_TM_ATTR_CMD])
		वापस -EINVAL;

	चयन (nla_get_u32(tb[IWL_MVM_TM_ATTR_CMD])) अणु
	हाल IWL_MVM_TM_CMD_SET_NOA:
		अगर (!vअगर || vअगर->type != NL80211_IFTYPE_AP || !vअगर->p2p ||
		    !vअगर->bss_conf.enable_beacon ||
		    !tb[IWL_MVM_TM_ATTR_NOA_DURATION])
			वापस -EINVAL;

		noa_duration = nla_get_u32(tb[IWL_MVM_TM_ATTR_NOA_DURATION]);
		अगर (noa_duration >= vअगर->bss_conf.beacon_पूर्णांक)
			वापस -EINVAL;

		mvm->noa_duration = noa_duration;
		mvm->noa_vअगर = vअगर;

		वापस iwl_mvm_update_quotas(mvm, true, शून्य);
	हाल IWL_MVM_TM_CMD_SET_BEACON_FILTER:
		/* must be associated client vअगर - ignore authorized */
		अगर (!vअगर || vअगर->type != NL80211_IFTYPE_STATION ||
		    !vअगर->bss_conf.assoc || !vअगर->bss_conf.dtim_period ||
		    !tb[IWL_MVM_TM_ATTR_BEACON_FILTER_STATE])
			वापस -EINVAL;

		अगर (nla_get_u32(tb[IWL_MVM_TM_ATTR_BEACON_FILTER_STATE]))
			वापस iwl_mvm_enable_beacon_filter(mvm, vअगर, 0);
		वापस iwl_mvm_disable_beacon_filter(mvm, vअगर, 0);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक iwl_mvm_mac_tesपंचांगode_cmd(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    व्योम *data, पूर्णांक len)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक err;

	mutex_lock(&mvm->mutex);
	err = __iwl_mvm_mac_tesपंचांगode_cmd(mvm, vअगर, data, len);
	mutex_unlock(&mvm->mutex);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल व्योम iwl_mvm_channel_चयन(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_channel_चयन *chsw)
अणु
	/* By implementing this operation, we prevent mac80211 from
	 * starting its own channel चयन समयr, so that we can call
	 * ieee80211_chचयन_करोne() ourselves at the right समय
	 * (which is when the असलence समय event starts).
	 */

	IWL_DEBUG_MAC80211(IWL_MAC80211_GET_MVM(hw),
			   "dummy channel switch op\n");
पूर्ण

अटल पूर्णांक iwl_mvm_schedule_client_csa(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_channel_चयन *chsw)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_chan_चयन_te_cmd cmd = अणु
		.mac_id = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							  mvmvअगर->color)),
		.action = cpu_to_le32(FW_CTXT_ACTION_ADD),
		.tsf = cpu_to_le32(chsw->बारtamp),
		.cs_count = chsw->count,
		.cs_mode = chsw->block_tx,
	पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (chsw->delay)
		cmd.cs_delayed_bcn_count =
			DIV_ROUND_UP(chsw->delay, vअगर->bss_conf.beacon_पूर्णांक);

	वापस iwl_mvm_send_cmd_pdu(mvm,
				    WIDE_ID(MAC_CONF_GROUP,
					    CHANNEL_SWITCH_TIME_EVENT_CMD),
				    0, माप(cmd), &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_old_pre_chan_sw_sta(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_channel_चयन *chsw)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	u32 apply_समय;

	/* Schedule the समय event to a bit beक्रमe beacon 1,
	 * to make sure we're in the new channel when the
	 * GO/AP arrives. In हाल count <= 1 immediately schedule the
	 * TE (this might result with some packet loss or connection
	 * loss).
	 */
	अगर (chsw->count <= 1)
		apply_समय = 0;
	अन्यथा
		apply_समय = chsw->device_बारtamp +
			((vअगर->bss_conf.beacon_पूर्णांक * (chsw->count - 1) -
			  IWL_MVM_CHANNEL_SWITCH_TIME_CLIENT) * 1024);

	अगर (chsw->block_tx)
		iwl_mvm_csa_client_असलent(mvm, vअगर);

	अगर (mvmvअगर->bf_data.bf_enabled) अणु
		पूर्णांक ret = iwl_mvm_disable_beacon_filter(mvm, vअगर, 0);

		अगर (ret)
			वापस ret;
	पूर्ण

	iwl_mvm_schedule_csa_period(mvm, vअगर, vअगर->bss_conf.beacon_पूर्णांक,
				    apply_समय);

	वापस 0;
पूर्ण

#घोषणा IWL_MAX_CSA_BLOCK_TX 1500
अटल पूर्णांक iwl_mvm_pre_channel_चयन(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_channel_चयन *chsw)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा ieee80211_vअगर *csa_vअगर;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);

	mvmvअगर->csa_failed = false;

	IWL_DEBUG_MAC80211(mvm, "pre CSA to freq %d\n",
			   chsw->chandef.center_freq1);

	iwl_fw_dbg_trigger_simple_stop(&mvm->fwrt,
				       ieee80211_vअगर_to_wdev(vअगर),
				       FW_DBG_TRIGGER_CHANNEL_SWITCH);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
		csa_vअगर =
			rcu_dereference_रक्षित(mvm->csa_vअगर,
						  lockdep_is_held(&mvm->mutex));
		अगर (WARN_ONCE(csa_vअगर && csa_vअगर->csa_active,
			      "Another CSA is already in progress")) अणु
			ret = -EBUSY;
			जाओ out_unlock;
		पूर्ण

		/* we still didn't unblock tx. prevent new CS meanजबतक */
		अगर (rcu_dereference_रक्षित(mvm->csa_tx_blocked_vअगर,
					      lockdep_is_held(&mvm->mutex))) अणु
			ret = -EBUSY;
			जाओ out_unlock;
		पूर्ण

		rcu_assign_poपूर्णांकer(mvm->csa_vअगर, vअगर);

		अगर (WARN_ONCE(mvmvअगर->csa_countकरोwn,
			      "Previous CSA countdown didn't complete")) अणु
			ret = -EBUSY;
			जाओ out_unlock;
		पूर्ण

		mvmvअगर->csa_target_freq = chsw->chandef.chan->center_freq;

		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		/*
		 * We haven't configured the firmware to be associated yet since
		 * we करोn't know the dtim period. In this case, the firmware can't
		 * track the beacons.
		 */
		अगर (!vअगर->bss_conf.assoc || !vअगर->bss_conf.dtim_period) अणु
			ret = -EBUSY;
			जाओ out_unlock;
		पूर्ण

		अगर (chsw->delay > IWL_MAX_CSA_BLOCK_TX)
			schedule_delayed_work(&mvmvअगर->csa_work, 0);

		अगर (chsw->block_tx) अणु
			/*
			 * In हाल of undetermined / दीर्घ समय with immediate
			 * quiet monitor status to gracefully disconnect
			 */
			अगर (!chsw->count ||
			    chsw->count * vअगर->bss_conf.beacon_पूर्णांक >
			    IWL_MAX_CSA_BLOCK_TX)
				schedule_delayed_work(&mvmvअगर->csa_work,
						      msecs_to_jअगरfies(IWL_MAX_CSA_BLOCK_TX));
		पूर्ण

		अगर (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWL_UCODE_TLV_CAPA_CHANNEL_SWITCH_CMD)) अणु
			ret = iwl_mvm_old_pre_chan_sw_sta(mvm, vअगर, chsw);
			अगर (ret)
				जाओ out_unlock;
		पूर्ण अन्यथा अणु
			iwl_mvm_schedule_client_csa(mvm, vअगर, chsw);
		पूर्ण

		mvmvअगर->csa_count = chsw->count;
		mvmvअगर->csa_misbehave = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mvmvअगर->ps_disabled = true;

	ret = iwl_mvm_घातer_update_ps(mvm);
	अगर (ret)
		जाओ out_unlock;

	/* we won't be on this channel any दीर्घer */
	iwl_mvm_tearकरोwn_tdls_peers(mvm);

out_unlock:
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_channel_चयन_rx_beacon(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_vअगर *vअगर,
					     काष्ठा ieee80211_channel_चयन *chsw)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_chan_चयन_te_cmd cmd = अणु
		.mac_id = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							  mvmvअगर->color)),
		.action = cpu_to_le32(FW_CTXT_ACTION_MODIFY),
		.tsf = cpu_to_le32(chsw->बारtamp),
		.cs_count = chsw->count,
		.cs_mode = chsw->block_tx,
	पूर्ण;

	अगर (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_CS_MODIFY))
		वापस;

	अगर (chsw->count >= mvmvअगर->csa_count && chsw->block_tx) अणु
		अगर (mvmvअगर->csa_misbehave) अणु
			/* Second समय, give up on this AP*/
			iwl_mvm_पात_channel_चयन(hw, vअगर);
			ieee80211_chचयन_करोne(vअगर, false);
			mvmvअगर->csa_misbehave = false;
			वापस;
		पूर्ण
		mvmvअगर->csa_misbehave = true;
	पूर्ण
	mvmvअगर->csa_count = chsw->count;

	mutex_lock(&mvm->mutex);
	अगर (mvmvअगर->csa_failed)
		जाओ out_unlock;

	IWL_DEBUG_MAC80211(mvm, "Modify CSA on mac %d count = %d mode = %d\n",
			   mvmvअगर->id, chsw->count, chsw->block_tx);
	WARN_ON(iwl_mvm_send_cmd_pdu(mvm,
				     WIDE_ID(MAC_CONF_GROUP,
					     CHANNEL_SWITCH_TIME_EVENT_CMD),
				     0, माप(cmd), &cmd));
out_unlock:
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम iwl_mvm_flush_no_vअगर(काष्ठा iwl_mvm *mvm, u32 queues, bool drop)
अणु
	पूर्णांक i;

	अगर (!iwl_mvm_has_new_tx_api(mvm)) अणु
		अगर (drop) अणु
			mutex_lock(&mvm->mutex);
			iwl_mvm_flush_tx_path(mvm,
				iwl_mvm_flushable_queues(mvm) & queues);
			mutex_unlock(&mvm->mutex);
		पूर्ण अन्यथा अणु
			iwl_trans_रुको_tx_queues_empty(mvm->trans, queues);
		पूर्ण
		वापस;
	पूर्ण

	mutex_lock(&mvm->mutex);
	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) अणु
		काष्ठा ieee80211_sta *sta;

		sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		अगर (IS_ERR_OR_शून्य(sta))
			जारी;

		अगर (drop)
			iwl_mvm_flush_sta_tids(mvm, i, 0xFFFF);
		अन्यथा
			iwl_mvm_रुको_sta_queues_empty(mvm,
					iwl_mvm_sta_from_mac80211(sta));
	पूर्ण
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम iwl_mvm_mac_flush(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, u32 queues, bool drop)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा ieee80211_sta *sta;
	पूर्णांक i;
	u32 msk = 0;

	अगर (!vअगर) अणु
		iwl_mvm_flush_no_vअगर(mvm, queues, drop);
		वापस;
	पूर्ण

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	/* Make sure we're करोne with the deferred traffic beक्रमe flushing */
	flush_work(&mvm->add_stream_wk);

	mutex_lock(&mvm->mutex);
	mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	/* flush the AP-station and all TDLS peers */
	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) अणु
		sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		अगर (IS_ERR_OR_शून्य(sta))
			जारी;

		mvmsta = iwl_mvm_sta_from_mac80211(sta);
		अगर (mvmsta->vअगर != vअगर)
			जारी;

		/* make sure only TDLS peers or the AP are flushed */
		WARN_ON(i != mvmvअगर->ap_sta_id && !sta->tdls);

		अगर (drop) अणु
			अगर (iwl_mvm_flush_sta(mvm, mvmsta, false))
				IWL_ERR(mvm, "flush request fail\n");
		पूर्ण अन्यथा अणु
			msk |= mvmsta->tfd_queue_msk;
			अगर (iwl_mvm_has_new_tx_api(mvm))
				iwl_mvm_रुको_sta_queues_empty(mvm, mvmsta);
		पूर्ण
	पूर्ण

	mutex_unlock(&mvm->mutex);

	/* this can take a जबतक, and we may need/want other operations
	 * to succeed जबतक करोing this, so करो it without the mutex held
	 */
	अगर (!drop && !iwl_mvm_has_new_tx_api(mvm))
		iwl_trans_रुको_tx_queues_empty(mvm->trans, msk);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				  काष्ठा survey_info *survey)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	स_रखो(survey, 0, माप(*survey));

	/* only support global statistics right now */
	अगर (idx != 0)
		वापस -ENOENT;

	अगर (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_RADIO_BEACON_STATS))
		वापस -ENOENT;

	mutex_lock(&mvm->mutex);

	अगर (iwl_mvm_firmware_running(mvm)) अणु
		ret = iwl_mvm_request_statistics(mvm, false);
		अगर (ret)
			जाओ out;
	पूर्ण

	survey->filled = SURVEY_INFO_TIME |
			 SURVEY_INFO_TIME_RX |
			 SURVEY_INFO_TIME_TX |
			 SURVEY_INFO_TIME_SCAN;
	survey->समय = mvm->accu_radio_stats.on_समय_rf +
		       mvm->radio_stats.on_समय_rf;
	करो_भाग(survey->समय, USEC_PER_MSEC);

	survey->समय_rx = mvm->accu_radio_stats.rx_समय +
			  mvm->radio_stats.rx_समय;
	करो_भाग(survey->समय_rx, USEC_PER_MSEC);

	survey->समय_प्रकारx = mvm->accu_radio_stats.tx_समय +
			  mvm->radio_stats.tx_समय;
	करो_भाग(survey->समय_प्रकारx, USEC_PER_MSEC);

	survey->समय_scan = mvm->accu_radio_stats.on_समय_scan +
			    mvm->radio_stats.on_समय_scan;
	करो_भाग(survey->समय_scan, USEC_PER_MSEC);

	ret = 0;
 out:
	mutex_unlock(&mvm->mutex);
	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_set_sta_rate(u32 rate_n_flags, काष्ठा rate_info *rinfo)
अणु
	चयन (rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) अणु
	हाल RATE_MCS_CHAN_WIDTH_20:
		rinfo->bw = RATE_INFO_BW_20;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_40:
		rinfo->bw = RATE_INFO_BW_40;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_80:
		rinfo->bw = RATE_INFO_BW_80;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_160:
		rinfo->bw = RATE_INFO_BW_160;
		अवरोध;
	पूर्ण

	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		rinfo->flags |= RATE_INFO_FLAGS_MCS;
		rinfo->mcs = u32_get_bits(rate_n_flags, RATE_HT_MCS_INDEX_MSK);
		rinfo->nss = u32_get_bits(rate_n_flags,
					  RATE_HT_MCS_NSS_MSK) + 1;
		अगर (rate_n_flags & RATE_MCS_SGI_MSK)
			rinfo->flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अगर (rate_n_flags & RATE_MCS_VHT_MSK) अणु
		rinfo->flags |= RATE_INFO_FLAGS_VHT_MCS;
		rinfo->mcs = u32_get_bits(rate_n_flags,
					  RATE_VHT_MCS_RATE_CODE_MSK);
		rinfo->nss = u32_get_bits(rate_n_flags,
					  RATE_VHT_MCS_NSS_MSK) + 1;
		अगर (rate_n_flags & RATE_MCS_SGI_MSK)
			rinfo->flags |= RATE_INFO_FLAGS_SHORT_GI;
	पूर्ण अन्यथा अगर (rate_n_flags & RATE_MCS_HE_MSK) अणु
		u32 gi_ltf = u32_get_bits(rate_n_flags,
					  RATE_MCS_HE_GI_LTF_MSK);

		rinfo->flags |= RATE_INFO_FLAGS_HE_MCS;
		rinfo->mcs = u32_get_bits(rate_n_flags,
					  RATE_VHT_MCS_RATE_CODE_MSK);
		rinfo->nss = u32_get_bits(rate_n_flags,
					  RATE_VHT_MCS_NSS_MSK) + 1;

		अगर (rate_n_flags & RATE_MCS_HE_106T_MSK) अणु
			rinfo->bw = RATE_INFO_BW_HE_RU;
			rinfo->he_ru_alloc = NL80211_RATE_INFO_HE_RU_ALLOC_106;
		पूर्ण

		चयन (rate_n_flags & RATE_MCS_HE_TYPE_MSK) अणु
		हाल RATE_MCS_HE_TYPE_SU:
		हाल RATE_MCS_HE_TYPE_EXT_SU:
			अगर (gi_ltf == 0 || gi_ltf == 1)
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_0_8;
			अन्यथा अगर (gi_ltf == 2)
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_1_6;
			अन्यथा अगर (rate_n_flags & RATE_MCS_SGI_MSK)
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_0_8;
			अन्यथा
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_3_2;
			अवरोध;
		हाल RATE_MCS_HE_TYPE_MU:
			अगर (gi_ltf == 0 || gi_ltf == 1)
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_0_8;
			अन्यथा अगर (gi_ltf == 2)
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_1_6;
			अन्यथा
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_3_2;
			अवरोध;
		हाल RATE_MCS_HE_TYPE_TRIG:
			अगर (gi_ltf == 0 || gi_ltf == 1)
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_1_6;
			अन्यथा
				rinfo->he_gi = NL80211_RATE_INFO_HE_GI_3_2;
			अवरोध;
		पूर्ण

		अगर (rate_n_flags & RATE_HE_DUAL_CARRIER_MODE_MSK)
			rinfo->he_dcm = 1;
	पूर्ण अन्यथा अणु
		चयन (u32_get_bits(rate_n_flags, RATE_LEGACY_RATE_MSK)) अणु
		हाल IWL_RATE_1M_PLCP:
			rinfo->legacy = 10;
			अवरोध;
		हाल IWL_RATE_2M_PLCP:
			rinfo->legacy = 20;
			अवरोध;
		हाल IWL_RATE_5M_PLCP:
			rinfo->legacy = 55;
			अवरोध;
		हाल IWL_RATE_11M_PLCP:
			rinfo->legacy = 110;
			अवरोध;
		हाल IWL_RATE_6M_PLCP:
			rinfo->legacy = 60;
			अवरोध;
		हाल IWL_RATE_9M_PLCP:
			rinfo->legacy = 90;
			अवरोध;
		हाल IWL_RATE_12M_PLCP:
			rinfo->legacy = 120;
			अवरोध;
		हाल IWL_RATE_18M_PLCP:
			rinfo->legacy = 180;
			अवरोध;
		हाल IWL_RATE_24M_PLCP:
			rinfo->legacy = 240;
			अवरोध;
		हाल IWL_RATE_36M_PLCP:
			rinfo->legacy = 360;
			अवरोध;
		हाल IWL_RATE_48M_PLCP:
			rinfo->legacy = 480;
			अवरोध;
		हाल IWL_RATE_54M_PLCP:
			rinfo->legacy = 540;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_mac_sta_statistics(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta,
				       काष्ठा station_info *sinfo)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

	अगर (mvmsta->avg_energy) अणु
		sinfo->संकेत_avg = -(s8)mvmsta->avg_energy;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL_AVG);
	पूर्ण

	अगर (iwl_mvm_has_tlc_offload(mvm)) अणु
		काष्ठा iwl_lq_sta_rs_fw *lq_sta = &mvmsta->lq_sta.rs_fw;

		iwl_mvm_set_sta_rate(lq_sta->last_rate_n_flags, &sinfo->txrate);
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
	पूर्ण

	/* अगर beacon filtering isn't on mac80211 करोes it anyway */
	अगर (!(vअगर->driver_flags & IEEE80211_VIF_BEACON_FILTER))
		वापस;

	अगर (!vअगर->bss_conf.assoc)
		वापस;

	mutex_lock(&mvm->mutex);

	अगर (mvmvअगर->ap_sta_id != mvmsta->sta_id)
		जाओ unlock;

	अगर (iwl_mvm_request_statistics(mvm, false))
		जाओ unlock;

	sinfo->rx_beacon = mvmvअगर->beacon_stats.num_beacons +
			   mvmvअगर->beacon_stats.accu_num_beacons;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_BEACON_RX);
	अगर (mvmvअगर->beacon_stats.avg_संकेत) अणु
		/* firmware only reports a value after RXing a few beacons */
		sinfo->rx_beacon_संकेत_avg = mvmvअगर->beacon_stats.avg_संकेत;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_BEACON_SIGNAL_AVG);
	पूर्ण
 unlock:
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम iwl_mvm_event_mlme_callback_ini(काष्ठा iwl_mvm *mvm,
					    काष्ठा ieee80211_vअगर *vअगर,
					    स्थिर  काष्ठा ieee80211_mlme_event *mlme)
अणु
	अगर (mlme->data == ASSOC_EVENT && (mlme->status == MLME_DENIED ||
					  mlme->status == MLME_TIMEOUT)) अणु
		iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt,
				       IWL_FW_INI_TIME_POINT_ASSOC_FAILED,
				       शून्य);
		वापस;
	पूर्ण

	अगर (mlme->data == AUTH_EVENT && (mlme->status == MLME_DENIED ||
					 mlme->status == MLME_TIMEOUT)) अणु
		iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt,
				       IWL_FW_INI_TIME_POINT_EAPOL_FAILED,
				       शून्य);
		वापस;
	पूर्ण

	अगर (mlme->data == DEAUTH_RX_EVENT || mlme->data == DEAUTH_TX_EVENT) अणु
		iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt,
				       IWL_FW_INI_TIME_POINT_DEASSOC,
				       शून्य);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_event_mlme_callback(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_vअगर *vअगर,
					स्थिर काष्ठा ieee80211_event *event)
अणु
#घोषणा CHECK_MLME_TRIGGER(_cnt, _fmt...)				\
	करो अणु								\
		अगर ((trig_mlme->_cnt) && --(trig_mlme->_cnt))		\
			अवरोध;						\
		iwl_fw_dbg_collect_trig(&(mvm)->fwrt, trig, _fmt);	\
	पूर्ण जबतक (0)

	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_mlme *trig_mlme;

	अगर (iwl_trans_dbg_ini_valid(mvm->trans)) अणु
		iwl_mvm_event_mlme_callback_ini(mvm, vअगर, &event->u.mlme);
		वापस;
	पूर्ण

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vअगर_to_wdev(vअगर),
				     FW_DBG_TRIGGER_MLME);
	अगर (!trig)
		वापस;

	trig_mlme = (व्योम *)trig->data;

	अगर (event->u.mlme.data == ASSOC_EVENT) अणु
		अगर (event->u.mlme.status == MLME_DENIED)
			CHECK_MLME_TRIGGER(stop_assoc_denied,
					   "DENIED ASSOC: reason %d",
					    event->u.mlme.reason);
		अन्यथा अगर (event->u.mlme.status == MLME_TIMEOUT)
			CHECK_MLME_TRIGGER(stop_assoc_समयout,
					   "ASSOC TIMEOUT");
	पूर्ण अन्यथा अगर (event->u.mlme.data == AUTH_EVENT) अणु
		अगर (event->u.mlme.status == MLME_DENIED)
			CHECK_MLME_TRIGGER(stop_auth_denied,
					   "DENIED AUTH: reason %d",
					   event->u.mlme.reason);
		अन्यथा अगर (event->u.mlme.status == MLME_TIMEOUT)
			CHECK_MLME_TRIGGER(stop_auth_समयout,
					   "AUTH TIMEOUT");
	पूर्ण अन्यथा अगर (event->u.mlme.data == DEAUTH_RX_EVENT) अणु
		CHECK_MLME_TRIGGER(stop_rx_deauth,
				   "DEAUTH RX %d", event->u.mlme.reason);
	पूर्ण अन्यथा अगर (event->u.mlme.data == DEAUTH_TX_EVENT) अणु
		CHECK_MLME_TRIGGER(stop_tx_deauth,
				   "DEAUTH TX %d", event->u.mlme.reason);
	पूर्ण
#अघोषित CHECK_MLME_TRIGGER
पूर्ण

अटल व्योम iwl_mvm_event_bar_rx_callback(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर,
					  स्थिर काष्ठा ieee80211_event *event)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_ba *ba_trig;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vअगर_to_wdev(vअगर),
				     FW_DBG_TRIGGER_BA);
	अगर (!trig)
		वापस;

	ba_trig = (व्योम *)trig->data;

	अगर (!(le16_to_cpu(ba_trig->rx_bar) & BIT(event->u.ba.tid)))
		वापस;

	iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
				"BAR received from %pM, tid %d, ssn %d",
				event->u.ba.sta->addr, event->u.ba.tid,
				event->u.ba.ssn);
पूर्ण

अटल व्योम iwl_mvm_mac_event_callback(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       स्थिर काष्ठा ieee80211_event *event)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	चयन (event->type) अणु
	हाल MLME_EVENT:
		iwl_mvm_event_mlme_callback(mvm, vअगर, event);
		अवरोध;
	हाल BAR_RX_EVENT:
		iwl_mvm_event_bar_rx_callback(mvm, vअगर, event);
		अवरोध;
	हाल BA_FRAME_TIMEOUT:
		iwl_mvm_event_frame_समयout_callback(mvm, vअगर, event->u.ba.sta,
						     event->u.ba.tid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम iwl_mvm_sync_rx_queues_पूर्णांकernal(काष्ठा iwl_mvm *mvm,
				     क्रमागत iwl_mvm_rxq_notअगर_type type,
				     bool sync,
				     स्थिर व्योम *data, u32 size)
अणु
	काष्ठा अणु
		काष्ठा iwl_rxq_sync_cmd cmd;
		काष्ठा iwl_mvm_पूर्णांकernal_rxq_notअगर notअगर;
	पूर्ण __packed cmd = अणु
		.cmd.rxq_mask = cpu_to_le32(BIT(mvm->trans->num_rx_queues) - 1),
		.cmd.count =
			cpu_to_le32(माप(काष्ठा iwl_mvm_पूर्णांकernal_rxq_notअगर) +
				    size),
		.notअगर.type = type,
		.notअगर.sync = sync,
	पूर्ण;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = WIDE_ID(DATA_PATH_GROUP, TRIGGER_RX_QUEUES_NOTIF_CMD),
		.data[0] = &cmd,
		.len[0] = माप(cmd),
		.data[1] = data,
		.len[1] = size,
		.flags = sync ? 0 : CMD_ASYNC,
	पूर्ण;
	पूर्णांक ret;

	/* size must be a multiple of DWORD */
	अगर (WARN_ON(cmd.cmd.count & cpu_to_le32(3)))
		वापस;

	अगर (!iwl_mvm_has_new_rx_api(mvm))
		वापस;

	अगर (sync) अणु
		cmd.notअगर.cookie = mvm->queue_sync_cookie;
		mvm->queue_sync_state = (1 << mvm->trans->num_rx_queues) - 1;
	पूर्ण

	ret = iwl_mvm_send_cmd(mvm, &hcmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to trigger RX queues sync (%d)\n", ret);
		जाओ out;
	पूर्ण

	अगर (sync) अणु
		lockdep_निश्चित_held(&mvm->mutex);
		ret = रुको_event_समयout(mvm->rx_sync_रुकोq,
					 READ_ONCE(mvm->queue_sync_state) == 0 ||
					 iwl_mvm_is_radio_समाप्तed(mvm),
					 HZ);
		WARN_ONCE(!ret && !iwl_mvm_is_radio_समाप्तed(mvm),
			  "queue sync: failed to sync, state is 0x%lx\n",
			  mvm->queue_sync_state);
	पूर्ण

out:
	अगर (sync) अणु
		mvm->queue_sync_state = 0;
		mvm->queue_sync_cookie++;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_sync_rx_queues(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);
	iwl_mvm_sync_rx_queues_पूर्णांकernal(mvm, IWL_MVM_RXQ_EMPTY, true, शून्य, 0);
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल पूर्णांक
iwl_mvm_mac_get_fपंचांग_responder_stats(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा cfg80211_fपंचांग_responder_stats *stats)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (vअगर->p2p || vअगर->type != NL80211_IFTYPE_AP ||
	    !mvmvअगर->ap_ibss_active || !vअगर->bss_conf.fपंचांग_responder)
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);
	*stats = mvm->fपंचांग_resp_stats;
	mutex_unlock(&mvm->mutex);

	stats->filled = BIT(NL80211_FTM_STATS_SUCCESS_NUM) |
			BIT(NL80211_FTM_STATS_PARTIAL_NUM) |
			BIT(NL80211_FTM_STATS_FAILED_NUM) |
			BIT(NL80211_FTM_STATS_ASAP_NUM) |
			BIT(NL80211_FTM_STATS_NON_ASAP_NUM) |
			BIT(NL80211_FTM_STATS_TOTAL_DURATION_MSEC) |
			BIT(NL80211_FTM_STATS_UNKNOWN_TRIGGERS_NUM) |
			BIT(NL80211_FTM_STATS_RESCHEDULE_REQUESTS_NUM) |
			BIT(NL80211_FTM_STATS_OUT_OF_WINDOW_TRIGGERS_NUM);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_start_pmsr(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा cfg80211_pmsr_request *request)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);
	ret = iwl_mvm_fपंचांग_start(mvm, vअगर, request);
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_पात_pmsr(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा cfg80211_pmsr_request *request)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);
	iwl_mvm_fपंचांग_पात(mvm, request);
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल bool iwl_mvm_can_hw_csum(काष्ठा sk_buff *skb)
अणु
	u8 protocol = ip_hdr(skb)->protocol;

	अगर (!IS_ENABLED(CONFIG_INET))
		वापस false;

	वापस protocol == IPPROTO_TCP || protocol == IPPROTO_UDP;
पूर्ण

अटल bool iwl_mvm_mac_can_aggregate(काष्ठा ieee80211_hw *hw,
				      काष्ठा sk_buff *head,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	/* For now करोn't aggregate IPv6 in AMSDU */
	अगर (skb->protocol != htons(ETH_P_IP))
		वापस false;

	अगर (!iwl_mvm_is_csum_supported(mvm))
		वापस true;

	वापस iwl_mvm_can_hw_csum(skb) == iwl_mvm_can_hw_csum(head);
पूर्ण

स्थिर काष्ठा ieee80211_ops iwl_mvm_hw_ops = अणु
	.tx = iwl_mvm_mac_tx,
	.wake_tx_queue = iwl_mvm_mac_wake_tx_queue,
	.ampdu_action = iwl_mvm_mac_ampdu_action,
	.get_antenna = iwl_mvm_op_get_antenna,
	.start = iwl_mvm_mac_start,
	.reconfig_complete = iwl_mvm_mac_reconfig_complete,
	.stop = iwl_mvm_mac_stop,
	.add_पूर्णांकerface = iwl_mvm_mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = iwl_mvm_mac_हटाओ_पूर्णांकerface,
	.config = iwl_mvm_mac_config,
	.prepare_multicast = iwl_mvm_prepare_multicast,
	.configure_filter = iwl_mvm_configure_filter,
	.config_अगरace_filter = iwl_mvm_config_अगरace_filter,
	.bss_info_changed = iwl_mvm_bss_info_changed,
	.hw_scan = iwl_mvm_mac_hw_scan,
	.cancel_hw_scan = iwl_mvm_mac_cancel_hw_scan,
	.sta_pre_rcu_हटाओ = iwl_mvm_sta_pre_rcu_हटाओ,
	.sta_state = iwl_mvm_mac_sta_state,
	.sta_notअगरy = iwl_mvm_mac_sta_notअगरy,
	.allow_buffered_frames = iwl_mvm_mac_allow_buffered_frames,
	.release_buffered_frames = iwl_mvm_mac_release_buffered_frames,
	.set_rts_threshold = iwl_mvm_mac_set_rts_threshold,
	.sta_rc_update = iwl_mvm_sta_rc_update,
	.conf_tx = iwl_mvm_mac_conf_tx,
	.mgd_prepare_tx = iwl_mvm_mac_mgd_prepare_tx,
	.mgd_protect_tdls_discover = iwl_mvm_mac_mgd_protect_tdls_discover,
	.flush = iwl_mvm_mac_flush,
	.sched_scan_start = iwl_mvm_mac_sched_scan_start,
	.sched_scan_stop = iwl_mvm_mac_sched_scan_stop,
	.set_key = iwl_mvm_mac_set_key,
	.update_tkip_key = iwl_mvm_mac_update_tkip_key,
	.reमुख्य_on_channel = iwl_mvm_roc,
	.cancel_reमुख्य_on_channel = iwl_mvm_cancel_roc,
	.add_chanctx = iwl_mvm_add_chanctx,
	.हटाओ_chanctx = iwl_mvm_हटाओ_chanctx,
	.change_chanctx = iwl_mvm_change_chanctx,
	.assign_vअगर_chanctx = iwl_mvm_assign_vअगर_chanctx,
	.unassign_vअगर_chanctx = iwl_mvm_unassign_vअगर_chanctx,
	.चयन_vअगर_chanctx = iwl_mvm_चयन_vअगर_chanctx,

	.start_ap = iwl_mvm_start_ap_ibss,
	.stop_ap = iwl_mvm_stop_ap_ibss,
	.join_ibss = iwl_mvm_start_ap_ibss,
	.leave_ibss = iwl_mvm_stop_ap_ibss,

	.tx_last_beacon = iwl_mvm_tx_last_beacon,

	.set_tim = iwl_mvm_set_tim,

	.channel_चयन = iwl_mvm_channel_चयन,
	.pre_channel_चयन = iwl_mvm_pre_channel_चयन,
	.post_channel_चयन = iwl_mvm_post_channel_चयन,
	.पात_channel_चयन = iwl_mvm_पात_channel_चयन,
	.channel_चयन_rx_beacon = iwl_mvm_channel_चयन_rx_beacon,

	.tdls_channel_चयन = iwl_mvm_tdls_channel_चयन,
	.tdls_cancel_channel_चयन = iwl_mvm_tdls_cancel_channel_चयन,
	.tdls_recv_channel_चयन = iwl_mvm_tdls_recv_channel_चयन,

	.event_callback = iwl_mvm_mac_event_callback,

	.sync_rx_queues = iwl_mvm_sync_rx_queues,

	CFG80211_TESTMODE_CMD(iwl_mvm_mac_tesपंचांगode_cmd)

#अगर_घोषित CONFIG_PM_SLEEP
	/* look at d3.c */
	.suspend = iwl_mvm_suspend,
	.resume = iwl_mvm_resume,
	.set_wakeup = iwl_mvm_set_wakeup,
	.set_rekey_data = iwl_mvm_set_rekey_data,
#अगर IS_ENABLED(CONFIG_IPV6)
	.ipv6_addr_change = iwl_mvm_ipv6_addr_change,
#पूर्ण_अगर
	.set_शेष_unicast_key = iwl_mvm_set_शेष_unicast_key,
#पूर्ण_अगर
	.get_survey = iwl_mvm_mac_get_survey,
	.sta_statistics = iwl_mvm_mac_sta_statistics,
	.get_fपंचांग_responder_stats = iwl_mvm_mac_get_fपंचांग_responder_stats,
	.start_pmsr = iwl_mvm_start_pmsr,
	.पात_pmsr = iwl_mvm_पात_pmsr,

	.can_aggregate_in_amsdu = iwl_mvm_mac_can_aggregate,
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	.sta_add_debugfs = iwl_mvm_sta_add_debugfs,
#पूर्ण_अगर
पूर्ण;
