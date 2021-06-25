<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/प्रकार.स>
#समावेश <net/mac80211.h>
#समावेश <net/cfg80211.h>
#समावेश <linux/completion.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/uuid.h>
#समावेश <linux/समय.स>
#समावेश <linux/of.h>
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "mac.h"
#समावेश "hw.h"
#समावेश "peer.h"

काष्ठा wmi_tlv_policy अणु
	माप_प्रकार min_len;
पूर्ण;

काष्ठा wmi_tlv_svc_पढ़ोy_parse अणु
	bool wmi_svc_biपंचांगap_करोne;
पूर्ण;

काष्ठा wmi_tlv_dma_ring_caps_parse अणु
	काष्ठा wmi_dma_ring_capabilities *dma_ring_caps;
	u32 n_dma_ring_caps;
पूर्ण;

काष्ठा wmi_tlv_svc_rdy_ext_parse अणु
	काष्ठा ath11k_service_ext_param param;
	काष्ठा wmi_soc_mac_phy_hw_mode_caps *hw_caps;
	काष्ठा wmi_hw_mode_capabilities *hw_mode_caps;
	u32 n_hw_mode_caps;
	u32 tot_phy_id;
	काष्ठा wmi_hw_mode_capabilities pref_hw_mode_caps;
	काष्ठा wmi_mac_phy_capabilities *mac_phy_caps;
	u32 n_mac_phy_caps;
	काष्ठा wmi_soc_hal_reg_capabilities *soc_hal_reg_caps;
	काष्ठा wmi_hal_reg_capabilities_ext *ext_hal_reg_caps;
	u32 n_ext_hal_reg_caps;
	काष्ठा wmi_tlv_dma_ring_caps_parse dma_caps_parse;
	bool hw_mode_करोne;
	bool mac_phy_करोne;
	bool ext_hal_reg_करोne;
	bool mac_phy_chainmask_combo_करोne;
	bool mac_phy_chainmask_cap_करोne;
	bool oem_dma_ring_cap_करोne;
	bool dma_ring_cap_करोne;
पूर्ण;

काष्ठा wmi_tlv_svc_rdy_ext2_parse अणु
	काष्ठा wmi_tlv_dma_ring_caps_parse dma_caps_parse;
	bool dma_ring_cap_करोne;
पूर्ण;

काष्ठा wmi_tlv_rdy_parse अणु
	u32 num_extra_mac_addr;
पूर्ण;

काष्ठा wmi_tlv_dma_buf_release_parse अणु
	काष्ठा ath11k_wmi_dma_buf_release_fixed_param fixed;
	काष्ठा wmi_dma_buf_release_entry *buf_entry;
	काष्ठा wmi_dma_buf_release_meta_data *meta_data;
	u32 num_buf_entry;
	u32 num_meta;
	bool buf_entry_करोne;
	bool meta_data_करोne;
पूर्ण;

अटल स्थिर काष्ठा wmi_tlv_policy wmi_tlv_policies[] = अणु
	[WMI_TAG_ARRAY_BYTE]
		= अणु .min_len = 0 पूर्ण,
	[WMI_TAG_ARRAY_UINT32]
		= अणु .min_len = 0 पूर्ण,
	[WMI_TAG_SERVICE_READY_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_service_पढ़ोy_event) पूर्ण,
	[WMI_TAG_SERVICE_READY_EXT_EVENT]
		= अणु .min_len =  माप(काष्ठा wmi_service_पढ़ोy_ext_event) पूर्ण,
	[WMI_TAG_SOC_MAC_PHY_HW_MODE_CAPS]
		= अणु .min_len = माप(काष्ठा wmi_soc_mac_phy_hw_mode_caps) पूर्ण,
	[WMI_TAG_SOC_HAL_REG_CAPABILITIES]
		= अणु .min_len = माप(काष्ठा wmi_soc_hal_reg_capabilities) पूर्ण,
	[WMI_TAG_VDEV_START_RESPONSE_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_vdev_start_resp_event) पूर्ण,
	[WMI_TAG_PEER_DELETE_RESP_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_peer_delete_resp_event) पूर्ण,
	[WMI_TAG_OFFLOAD_BCN_TX_STATUS_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_bcn_tx_status_event) पूर्ण,
	[WMI_TAG_VDEV_STOPPED_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_vdev_stopped_event) पूर्ण,
	[WMI_TAG_REG_CHAN_LIST_CC_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_reg_chan_list_cc_event) पूर्ण,
	[WMI_TAG_MGMT_RX_HDR]
		= अणु .min_len = माप(काष्ठा wmi_mgmt_rx_hdr) पूर्ण,
	[WMI_TAG_MGMT_TX_COMPL_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_mgmt_tx_compl_event) पूर्ण,
	[WMI_TAG_SCAN_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_scan_event) पूर्ण,
	[WMI_TAG_PEER_STA_KICKOUT_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_peer_sta_kickout_event) पूर्ण,
	[WMI_TAG_ROAM_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_roam_event) पूर्ण,
	[WMI_TAG_CHAN_INFO_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_chan_info_event) पूर्ण,
	[WMI_TAG_PDEV_BSS_CHAN_INFO_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_pdev_bss_chan_info_event) पूर्ण,
	[WMI_TAG_VDEV_INSTALL_KEY_COMPLETE_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_vdev_install_key_compl_event) पूर्ण,
	[WMI_TAG_READY_EVENT] = अणु
		.min_len = माप(काष्ठा wmi_पढ़ोy_event_min) पूर्ण,
	[WMI_TAG_SERVICE_AVAILABLE_EVENT]
		= अणु.min_len = माप(काष्ठा wmi_service_available_event) पूर्ण,
	[WMI_TAG_PEER_ASSOC_CONF_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_peer_assoc_conf_event) पूर्ण,
	[WMI_TAG_STATS_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_stats_event) पूर्ण,
	[WMI_TAG_PDEV_CTL_FAILSAFE_CHECK_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_pdev_ctl_failsafe_chk_event) पूर्ण,
	[WMI_TAG_HOST_SWFDA_EVENT] = अणु
		.min_len = माप(काष्ठा wmi_fils_discovery_event) पूर्ण,
	[WMI_TAG_OFFLOAD_PRB_RSP_TX_STATUS_EVENT] = अणु
		.min_len = माप(काष्ठा wmi_probe_resp_tx_status_event) पूर्ण,
	[WMI_TAG_VDEV_DELETE_RESP_EVENT] = अणु
		.min_len = माप(काष्ठा wmi_vdev_delete_resp_event) पूर्ण,
पूर्ण;

#घोषणा PRIMAP(_hw_mode_) \
	[_hw_mode_] = _hw_mode_##_PRI

अटल स्थिर पूर्णांक ath11k_hw_mode_pri_map[] = अणु
	PRIMAP(WMI_HOST_HW_MODE_SINGLE),
	PRIMAP(WMI_HOST_HW_MODE_DBS),
	PRIMAP(WMI_HOST_HW_MODE_SBS_PASSIVE),
	PRIMAP(WMI_HOST_HW_MODE_SBS),
	PRIMAP(WMI_HOST_HW_MODE_DBS_SBS),
	PRIMAP(WMI_HOST_HW_MODE_DBS_OR_SBS),
	/* keep last */
	PRIMAP(WMI_HOST_HW_MODE_MAX),
पूर्ण;

अटल पूर्णांक
ath11k_wmi_tlv_iter(काष्ठा ath11k_base *ab, स्थिर व्योम *ptr, माप_प्रकार len,
		    पूर्णांक (*iter)(काष्ठा ath11k_base *ab, u16 tag, u16 len,
				स्थिर व्योम *ptr, व्योम *data),
		    व्योम *data)
अणु
	स्थिर व्योम *begin = ptr;
	स्थिर काष्ठा wmi_tlv *tlv;
	u16 tlv_tag, tlv_len;
	पूर्णांक ret;

	जबतक (len > 0) अणु
		अगर (len < माप(*tlv)) अणु
			ath11k_err(ab, "wmi tlv parse failure at byte %zd (%zu bytes left, %zu expected)\n",
				   ptr - begin, len, माप(*tlv));
			वापस -EINVAL;
		पूर्ण

		tlv = ptr;
		tlv_tag = FIELD_GET(WMI_TLV_TAG, tlv->header);
		tlv_len = FIELD_GET(WMI_TLV_LEN, tlv->header);
		ptr += माप(*tlv);
		len -= माप(*tlv);

		अगर (tlv_len > len) अणु
			ath11k_err(ab, "wmi tlv parse failure of tag %u at byte %zd (%zu bytes left, %u expected)\n",
				   tlv_tag, ptr - begin, len, tlv_len);
			वापस -EINVAL;
		पूर्ण

		अगर (tlv_tag < ARRAY_SIZE(wmi_tlv_policies) &&
		    wmi_tlv_policies[tlv_tag].min_len &&
		    wmi_tlv_policies[tlv_tag].min_len > tlv_len) अणु
			ath11k_err(ab, "wmi tlv parse failure of tag %u at byte %zd (%u bytes is less than min length %zu)\n",
				   tlv_tag, ptr - begin, tlv_len,
				   wmi_tlv_policies[tlv_tag].min_len);
			वापस -EINVAL;
		पूर्ण

		ret = iter(ab, tlv_tag, tlv_len, ptr, data);
		अगर (ret)
			वापस ret;

		ptr += tlv_len;
		len -= tlv_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_iter_parse(काष्ठा ath11k_base *ab, u16 tag, u16 len,
				     स्थिर व्योम *ptr, व्योम *data)
अणु
	स्थिर व्योम **tb = data;

	अगर (tag < WMI_TAG_MAX)
		tb[tag] = ptr;

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_parse(काष्ठा ath11k_base *ar, स्थिर व्योम **tb,
				स्थिर व्योम *ptr, माप_प्रकार len)
अणु
	वापस ath11k_wmi_tlv_iter(ar, ptr, len, ath11k_wmi_tlv_iter_parse,
				   (व्योम *)tb);
पूर्ण

अटल स्थिर व्योम **
ath11k_wmi_tlv_parse_alloc(काष्ठा ath11k_base *ab, स्थिर व्योम *ptr,
			   माप_प्रकार len, gfp_t gfp)
अणु
	स्थिर व्योम **tb;
	पूर्णांक ret;

	tb = kसुस्मृति(WMI_TAG_MAX, माप(*tb), gfp);
	अगर (!tb)
		वापस ERR_PTR(-ENOMEM);

	ret = ath11k_wmi_tlv_parse(ab, tb, ptr, len);
	अगर (ret) अणु
		kमुक्त(tb);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस tb;
पूर्ण

अटल पूर्णांक ath11k_wmi_cmd_send_noरुको(काष्ठा ath11k_pdev_wmi *wmi, काष्ठा sk_buff *skb,
				      u32 cmd_id)
अणु
	काष्ठा ath11k_skb_cb *skb_cb = ATH11K_SKB_CB(skb);
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	पूर्णांक ret;
	u32 cmd = 0;

	अगर (skb_push(skb, माप(काष्ठा wmi_cmd_hdr)) == शून्य)
		वापस -ENOMEM;

	cmd |= FIELD_PREP(WMI_CMD_HDR_CMD_ID, cmd_id);

	cmd_hdr = (काष्ठा wmi_cmd_hdr *)skb->data;
	cmd_hdr->cmd_id = cmd;

	स_रखो(skb_cb, 0, माप(*skb_cb));
	ret = ath11k_htc_send(&ab->htc, wmi->eid, skb);

	अगर (ret)
		जाओ err_pull;

	वापस 0;

err_pull:
	skb_pull(skb, माप(काष्ठा wmi_cmd_hdr));
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_cmd_send(काष्ठा ath11k_pdev_wmi *wmi, काष्ठा sk_buff *skb,
			u32 cmd_id)
अणु
	काष्ठा ath11k_wmi_base *wmi_sc = wmi->wmi_ab;
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	रुको_event_समयout(wmi_sc->tx_credits_wq, (अणु
		ret = ath11k_wmi_cmd_send_noरुको(wmi, skb, cmd_id);

		अगर (ret && test_bit(ATH11K_FLAG_CRASH_FLUSH, &wmi_sc->ab->dev_flags))
			ret = -ESHUTDOWN;

		(ret != -EAGAIN);
	पूर्ण), WMI_SEND_TIMEOUT_HZ);

	अगर (ret == -EAGAIN)
		ath11k_warn(wmi_sc->ab, "wmi command %d timeout\n", cmd_id);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_pull_svc_पढ़ोy_ext(काष्ठा ath11k_pdev_wmi *wmi_handle,
				     स्थिर व्योम *ptr,
				     काष्ठा ath11k_service_ext_param *param)
अणु
	स्थिर काष्ठा wmi_service_पढ़ोy_ext_event *ev = ptr;

	अगर (!ev)
		वापस -EINVAL;

	/* Move this to host based biपंचांगap */
	param->शेष_conc_scan_config_bits = ev->शेष_conc_scan_config_bits;
	param->शेष_fw_config_bits =	ev->शेष_fw_config_bits;
	param->he_cap_info = ev->he_cap_info;
	param->mpdu_density = ev->mpdu_density;
	param->max_bssid_rx_filters = ev->max_bssid_rx_filters;
	स_नकल(&param->ppet, &ev->ppet, माप(param->ppet));

	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_pull_mac_phy_cap_svc_पढ़ोy_ext(काष्ठा ath11k_pdev_wmi *wmi_handle,
				      काष्ठा wmi_soc_mac_phy_hw_mode_caps *hw_caps,
				      काष्ठा wmi_hw_mode_capabilities *wmi_hw_mode_caps,
				      काष्ठा wmi_soc_hal_reg_capabilities *hal_reg_caps,
				      काष्ठा wmi_mac_phy_capabilities *wmi_mac_phy_caps,
				      u8 hw_mode_id, u8 phy_id,
				      काष्ठा ath11k_pdev *pdev)
अणु
	काष्ठा wmi_mac_phy_capabilities *mac_phy_caps;
	काष्ठा ath11k_band_cap *cap_band;
	काष्ठा ath11k_pdev_cap *pdev_cap = &pdev->cap;
	u32 phy_map;
	u32 hw_idx, phy_idx = 0;

	अगर (!hw_caps || !wmi_hw_mode_caps || !hal_reg_caps)
		वापस -EINVAL;

	क्रम (hw_idx = 0; hw_idx < hw_caps->num_hw_modes; hw_idx++) अणु
		अगर (hw_mode_id == wmi_hw_mode_caps[hw_idx].hw_mode_id)
			अवरोध;

		phy_map = wmi_hw_mode_caps[hw_idx].phy_id_map;
		जबतक (phy_map) अणु
			phy_map >>= 1;
			phy_idx++;
		पूर्ण
	पूर्ण

	अगर (hw_idx == hw_caps->num_hw_modes)
		वापस -EINVAL;

	phy_idx += phy_id;
	अगर (phy_id >= hal_reg_caps->num_phy)
		वापस -EINVAL;

	mac_phy_caps = wmi_mac_phy_caps + phy_idx;

	pdev->pdev_id = mac_phy_caps->pdev_id;
	pdev_cap->supported_bands |= mac_phy_caps->supported_bands;
	pdev_cap->ampdu_density = mac_phy_caps->ampdu_density;

	/* Take non-zero tx/rx chainmask. If tx/rx chainmask dअगरfers from
	 * band to band क्रम a single radio, need to see how this should be
	 * handled.
	 */
	अगर (mac_phy_caps->supported_bands & WMI_HOST_WLAN_2G_CAP) अणु
		pdev_cap->tx_chain_mask = mac_phy_caps->tx_chain_mask_2g;
		pdev_cap->rx_chain_mask = mac_phy_caps->rx_chain_mask_2g;
	पूर्ण अन्यथा अगर (mac_phy_caps->supported_bands & WMI_HOST_WLAN_5G_CAP) अणु
		pdev_cap->vht_cap = mac_phy_caps->vht_cap_info_5g;
		pdev_cap->vht_mcs = mac_phy_caps->vht_supp_mcs_5g;
		pdev_cap->he_mcs = mac_phy_caps->he_supp_mcs_5g;
		pdev_cap->tx_chain_mask = mac_phy_caps->tx_chain_mask_5g;
		pdev_cap->rx_chain_mask = mac_phy_caps->rx_chain_mask_5g;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	/* tx/rx chainmask reported from fw depends on the actual hw chains used,
	 * For example, क्रम 4x4 capable macphys, first 4 chains can be used क्रम first
	 * mac and the reमुख्यg 4 chains can be used क्रम the second mac or vice-versa.
	 * In this हाल, tx/rx chainmask 0xf will be advertised क्रम first mac and 0xf0
	 * will be advertised क्रम second mac or vice-versa. Compute the shअगरt value
	 * क्रम tx/rx chainmask which will be used to advertise supported ht/vht rates to
	 * mac80211.
	 */
	pdev_cap->tx_chain_mask_shअगरt =
			find_first_bit((अचिन्हित दीर्घ *)&pdev_cap->tx_chain_mask, 32);
	pdev_cap->rx_chain_mask_shअगरt =
			find_first_bit((अचिन्हित दीर्घ *)&pdev_cap->rx_chain_mask, 32);

	अगर (mac_phy_caps->supported_bands & WMI_HOST_WLAN_2G_CAP) अणु
		cap_band = &pdev_cap->band[NL80211_BAND_2GHZ];
		cap_band->phy_id = mac_phy_caps->phy_id;
		cap_band->max_bw_supported = mac_phy_caps->max_bw_supported_2g;
		cap_band->ht_cap_info = mac_phy_caps->ht_cap_info_2g;
		cap_band->he_cap_info[0] = mac_phy_caps->he_cap_info_2g;
		cap_band->he_cap_info[1] = mac_phy_caps->he_cap_info_2g_ext;
		cap_band->he_mcs = mac_phy_caps->he_supp_mcs_2g;
		स_नकल(cap_band->he_cap_phy_info, &mac_phy_caps->he_cap_phy_info_2g,
		       माप(u32) * PSOC_HOST_MAX_PHY_SIZE);
		स_नकल(&cap_band->he_ppet, &mac_phy_caps->he_ppet2g,
		       माप(काष्ठा ath11k_ppe_threshold));
	पूर्ण

	अगर (mac_phy_caps->supported_bands & WMI_HOST_WLAN_5G_CAP) अणु
		cap_band = &pdev_cap->band[NL80211_BAND_5GHZ];
		cap_band->phy_id = mac_phy_caps->phy_id;
		cap_band->max_bw_supported = mac_phy_caps->max_bw_supported_5g;
		cap_band->ht_cap_info = mac_phy_caps->ht_cap_info_5g;
		cap_band->he_cap_info[0] = mac_phy_caps->he_cap_info_5g;
		cap_band->he_cap_info[1] = mac_phy_caps->he_cap_info_5g_ext;
		cap_band->he_mcs = mac_phy_caps->he_supp_mcs_5g;
		स_नकल(cap_band->he_cap_phy_info, &mac_phy_caps->he_cap_phy_info_5g,
		       माप(u32) * PSOC_HOST_MAX_PHY_SIZE);
		स_नकल(&cap_band->he_ppet, &mac_phy_caps->he_ppet5g,
		       माप(काष्ठा ath11k_ppe_threshold));
	पूर्ण

	cap_band = &pdev_cap->band[NL80211_BAND_6GHZ];
	cap_band->max_bw_supported = mac_phy_caps->max_bw_supported_5g;
	cap_band->ht_cap_info = mac_phy_caps->ht_cap_info_5g;
	cap_band->he_cap_info[0] = mac_phy_caps->he_cap_info_5g;
	cap_band->he_cap_info[1] = mac_phy_caps->he_cap_info_5g_ext;
	cap_band->he_mcs = mac_phy_caps->he_supp_mcs_5g;
	स_नकल(cap_band->he_cap_phy_info, &mac_phy_caps->he_cap_phy_info_5g,
	       माप(u32) * PSOC_HOST_MAX_PHY_SIZE);
	स_नकल(&cap_band->he_ppet, &mac_phy_caps->he_ppet5g,
	       माप(काष्ठा ath11k_ppe_threshold));

	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_pull_reg_cap_svc_rdy_ext(काष्ठा ath11k_pdev_wmi *wmi_handle,
				काष्ठा wmi_soc_hal_reg_capabilities *reg_caps,
				काष्ठा wmi_hal_reg_capabilities_ext *wmi_ext_reg_cap,
				u8 phy_idx,
				काष्ठा ath11k_hal_reg_capabilities_ext *param)
अणु
	काष्ठा wmi_hal_reg_capabilities_ext *ext_reg_cap;

	अगर (!reg_caps || !wmi_ext_reg_cap)
		वापस -EINVAL;

	अगर (phy_idx >= reg_caps->num_phy)
		वापस -EINVAL;

	ext_reg_cap = &wmi_ext_reg_cap[phy_idx];

	param->phy_id = ext_reg_cap->phy_id;
	param->eeprom_reg_करोमुख्य = ext_reg_cap->eeprom_reg_करोमुख्य;
	param->eeprom_reg_करोमुख्य_ext =
			      ext_reg_cap->eeprom_reg_करोमुख्य_ext;
	param->regcap1 = ext_reg_cap->regcap1;
	param->regcap2 = ext_reg_cap->regcap2;
	/* check अगर param->wireless_mode is needed */
	param->low_2ghz_chan = ext_reg_cap->low_2ghz_chan;
	param->high_2ghz_chan = ext_reg_cap->high_2ghz_chan;
	param->low_5ghz_chan = ext_reg_cap->low_5ghz_chan;
	param->high_5ghz_chan = ext_reg_cap->high_5ghz_chan;

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_service_पढ़ोy_tlv(काष्ठा ath11k_base *ab,
					 स्थिर व्योम *evt_buf,
					 काष्ठा ath11k_targ_cap *cap)
अणु
	स्थिर काष्ठा wmi_service_पढ़ोy_event *ev = evt_buf;

	अगर (!ev) अणु
		ath11k_err(ab, "%s: failed by NULL param\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण

	cap->phy_capability = ev->phy_capability;
	cap->max_frag_entry = ev->max_frag_entry;
	cap->num_rf_chains = ev->num_rf_chains;
	cap->ht_cap_info = ev->ht_cap_info;
	cap->vht_cap_info = ev->vht_cap_info;
	cap->vht_supp_mcs = ev->vht_supp_mcs;
	cap->hw_min_tx_घातer = ev->hw_min_tx_घातer;
	cap->hw_max_tx_घातer = ev->hw_max_tx_घातer;
	cap->sys_cap_info = ev->sys_cap_info;
	cap->min_pkt_size_enable = ev->min_pkt_size_enable;
	cap->max_bcn_ie_size = ev->max_bcn_ie_size;
	cap->max_num_scan_channels = ev->max_num_scan_channels;
	cap->max_supported_macs = ev->max_supported_macs;
	cap->wmi_fw_sub_feat_caps = ev->wmi_fw_sub_feat_caps;
	cap->txrx_chainmask = ev->txrx_chainmask;
	cap->शेष_dbs_hw_mode_index = ev->शेष_dbs_hw_mode_index;
	cap->num_msdu_desc = ev->num_msdu_desc;

	वापस 0;
पूर्ण

/* Save the wmi_service_biपंचांगap पूर्णांकo a linear biपंचांगap. The wmi_services in
 * wmi_service पढ़ोy event are advertised in b0-b3 (LSB 4-bits) of each
 * 4-byte word.
 */
अटल व्योम ath11k_wmi_service_biपंचांगap_copy(काष्ठा ath11k_pdev_wmi *wmi,
					   स्थिर u32 *wmi_svc_bm)
अणु
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < WMI_SERVICE_BM_SIZE && j < WMI_MAX_SERVICE; i++) अणु
		करो अणु
			अगर (wmi_svc_bm[i] & BIT(j % WMI_SERVICE_BITS_IN_SIZE32))
				set_bit(j, wmi->wmi_ab->svc_map);
		पूर्ण जबतक (++j % WMI_SERVICE_BITS_IN_SIZE32);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_svc_rdy_parse(काष्ठा ath11k_base *ab, u16 tag, u16 len,
					स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_svc_पढ़ोy_parse *svc_पढ़ोy = data;
	काष्ठा ath11k_pdev_wmi *wmi_handle = &ab->wmi_ab.wmi[0];
	u16 expect_len;

	चयन (tag) अणु
	हाल WMI_TAG_SERVICE_READY_EVENT:
		अगर (ath11k_pull_service_पढ़ोy_tlv(ab, ptr, &ab->target_caps))
			वापस -EINVAL;
		अवरोध;

	हाल WMI_TAG_ARRAY_UINT32:
		अगर (!svc_पढ़ोy->wmi_svc_biपंचांगap_करोne) अणु
			expect_len = WMI_SERVICE_BM_SIZE * माप(u32);
			अगर (len < expect_len) अणु
				ath11k_warn(ab, "invalid len %d for the tag 0x%x\n",
					    len, tag);
				वापस -EINVAL;
			पूर्ण

			ath11k_wmi_service_biपंचांगap_copy(wmi_handle, ptr);

			svc_पढ़ोy->wmi_svc_biपंचांगap_करोne = true;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_service_पढ़ोy_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_tlv_svc_पढ़ोy_parse svc_पढ़ोy = अणु पूर्ण;
	पूर्णांक ret;

	ret = ath11k_wmi_tlv_iter(ab, skb->data, skb->len,
				  ath11k_wmi_tlv_svc_rdy_parse,
				  &svc_पढ़ोy);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to parse tlv %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा sk_buff *ath11k_wmi_alloc_skb(काष्ठा ath11k_wmi_base *wmi_sc, u32 len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ath11k_base *ab = wmi_sc->ab;
	u32 round_len = roundup(len, 4);

	skb = ath11k_htc_alloc_skb(ab, WMI_SKB_HEADROOM + round_len);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, WMI_SKB_HEADROOM);
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, 4))
		ath11k_warn(ab, "unaligned WMI skb data\n");

	skb_put(skb, round_len);
	स_रखो(skb->data, 0, round_len);

	वापस skb;
पूर्ण

पूर्णांक ath11k_wmi_mgmt_send(काष्ठा ath11k *ar, u32 vdev_id, u32 buf_id,
			 काष्ठा sk_buff *frame)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_mgmt_send_cmd *cmd;
	काष्ठा wmi_tlv *frame_tlv;
	काष्ठा sk_buff *skb;
	u32 buf_len;
	पूर्णांक ret, len;

	buf_len = frame->len < WMI_MGMT_SEND_DOWNLD_LEN ?
		  frame->len : WMI_MGMT_SEND_DOWNLD_LEN;

	len = माप(*cmd) + माप(*frame_tlv) + roundup(buf_len, 4);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_mgmt_send_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_MGMT_TX_SEND_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->desc_id = buf_id;
	cmd->chanfreq = 0;
	cmd->paddr_lo = lower_32_bits(ATH11K_SKB_CB(frame)->paddr);
	cmd->paddr_hi = upper_32_bits(ATH11K_SKB_CB(frame)->paddr);
	cmd->frame_len = frame->len;
	cmd->buf_len = buf_len;
	cmd->tx_params_valid = 0;

	frame_tlv = (काष्ठा wmi_tlv *)(skb->data + माप(*cmd));
	frame_tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_BYTE) |
			    FIELD_PREP(WMI_TLV_LEN, buf_len);

	स_नकल(frame_tlv->value, frame->data, buf_len);

	ath11k_ce_byte_swap(frame_tlv->value, buf_len);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_MGMT_TX_SEND_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to submit WMI_MGMT_TX_SEND_CMDID cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_vdev_create(काष्ठा ath11k *ar, u8 *macaddr,
			   काष्ठा vdev_create_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_create_cmd *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_vdev_txrx_streams *txrx_streams;
	काष्ठा wmi_tlv *tlv;
	पूर्णांक ret, len;
	व्योम *ptr;

	/* It can be optimized my sending tx/rx chain configuration
	 * only क्रम supported bands instead of always sending it क्रम
	 * both the bands.
	 */
	len = माप(*cmd) + TLV_HDR_SIZE +
		(WMI_NUM_SUPPORTED_BAND_MAX * माप(*txrx_streams));

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_create_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_CREATE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = param->अगर_id;
	cmd->vdev_type = param->type;
	cmd->vdev_subtype = param->subtype;
	cmd->num_cfg_txrx_streams = WMI_NUM_SUPPORTED_BAND_MAX;
	cmd->pdev_id = param->pdev_id;
	ether_addr_copy(cmd->vdev_macaddr.addr, macaddr);

	ptr = skb->data + माप(*cmd);
	len = WMI_NUM_SUPPORTED_BAND_MAX * माप(*txrx_streams);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_STRUCT) |
		      FIELD_PREP(WMI_TLV_LEN, len);

	ptr += TLV_HDR_SIZE;
	txrx_streams = ptr;
	len = माप(*txrx_streams);
	txrx_streams->tlv_header =
		FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_TXRX_STREAMS) |
		FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	txrx_streams->band = WMI_TPC_CHAINMASK_CONFIG_BAND_2G;
	txrx_streams->supported_tx_streams =
				 param->chains[NL80211_BAND_2GHZ].tx;
	txrx_streams->supported_rx_streams =
				 param->chains[NL80211_BAND_2GHZ].rx;

	txrx_streams++;
	txrx_streams->tlv_header =
		FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_TXRX_STREAMS) |
		FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	txrx_streams->band = WMI_TPC_CHAINMASK_CONFIG_BAND_5G;
	txrx_streams->supported_tx_streams =
				 param->chains[NL80211_BAND_5GHZ].tx;
	txrx_streams->supported_rx_streams =
				 param->chains[NL80211_BAND_5GHZ].rx;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_VDEV_CREATE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to submit WMI_VDEV_CREATE_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev create: id %d type %d subtype %d macaddr %pM pdevid %d\n",
		   param->अगर_id, param->type, param->subtype,
		   macaddr, param->pdev_id);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_vdev_delete(काष्ठा ath11k *ar, u8 vdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_delete_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_delete_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_DELETE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_VDEV_DELETE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to submit WMI_VDEV_DELETE_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "WMI vdev delete id %d\n", vdev_id);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_vdev_stop(काष्ठा ath11k *ar, u8 vdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_stop_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_stop_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_STOP_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_VDEV_STOP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to submit WMI_VDEV_STOP cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "WMI vdev stop id 0x%x\n", vdev_id);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_vdev_करोwn(काष्ठा ath11k *ar, u8 vdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_करोwn_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_करोwn_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_DOWN_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_VDEV_DOWN_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to submit WMI_VDEV_DOWN cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "WMI vdev down id 0x%x\n", vdev_id);

	वापस ret;
पूर्ण

अटल व्योम ath11k_wmi_put_wmi_channel(काष्ठा wmi_channel *chan,
				       काष्ठा wmi_vdev_start_req_arg *arg)
अणु
	स_रखो(chan, 0, माप(*chan));

	chan->mhz = arg->channel.freq;
	chan->band_center_freq1 = arg->channel.band_center_freq1;
	अगर (arg->channel.mode == MODE_11AC_VHT80_80)
		chan->band_center_freq2 = arg->channel.band_center_freq2;
	अन्यथा
		chan->band_center_freq2 = 0;

	chan->info |= FIELD_PREP(WMI_CHAN_INFO_MODE, arg->channel.mode);
	अगर (arg->channel.passive)
		chan->info |= WMI_CHAN_INFO_PASSIVE;
	अगर (arg->channel.allow_ibss)
		chan->info |= WMI_CHAN_INFO_ADHOC_ALLOWED;
	अगर (arg->channel.allow_ht)
		chan->info |= WMI_CHAN_INFO_ALLOW_HT;
	अगर (arg->channel.allow_vht)
		chan->info |= WMI_CHAN_INFO_ALLOW_VHT;
	अगर (arg->channel.allow_he)
		chan->info |= WMI_CHAN_INFO_ALLOW_HE;
	अगर (arg->channel.ht40plus)
		chan->info |= WMI_CHAN_INFO_HT40_PLUS;
	अगर (arg->channel.chan_radar)
		chan->info |= WMI_CHAN_INFO_DFS;
	अगर (arg->channel.freq2_radar)
		chan->info |= WMI_CHAN_INFO_DFS_FREQ2;

	chan->reg_info_1 = FIELD_PREP(WMI_CHAN_REG_INFO1_MAX_PWR,
				      arg->channel.max_घातer) |
		FIELD_PREP(WMI_CHAN_REG_INFO1_MAX_REG_PWR,
			   arg->channel.max_reg_घातer);

	chan->reg_info_2 = FIELD_PREP(WMI_CHAN_REG_INFO2_ANT_MAX,
				      arg->channel.max_antenna_gain) |
		FIELD_PREP(WMI_CHAN_REG_INFO2_MAX_TX_PWR,
			   arg->channel.max_घातer);
पूर्ण

पूर्णांक ath11k_wmi_vdev_start(काष्ठा ath11k *ar, काष्ठा wmi_vdev_start_req_arg *arg,
			  bool restart)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_start_request_cmd *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_channel *chan;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	पूर्णांक ret, len;

	अगर (WARN_ON(arg->ssid_len > माप(cmd->ssid.ssid)))
		वापस -EINVAL;

	len = माप(*cmd) + माप(*chan) + TLV_HDR_SIZE;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_start_request_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_VDEV_START_REQUEST_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = arg->vdev_id;
	cmd->beacon_पूर्णांकerval = arg->bcn_पूर्णांकval;
	cmd->bcn_tx_rate = arg->bcn_tx_rate;
	cmd->dtim_period = arg->dtim_period;
	cmd->num_noa_descriptors = arg->num_noa_descriptors;
	cmd->preferred_rx_streams = arg->pref_rx_streams;
	cmd->preferred_tx_streams = arg->pref_tx_streams;
	cmd->cac_duration_ms = arg->cac_duration_ms;
	cmd->regकरोमुख्य = arg->regकरोमुख्य;
	cmd->he_ops = arg->he_ops;

	अगर (!restart) अणु
		अगर (arg->ssid) अणु
			cmd->ssid.ssid_len = arg->ssid_len;
			स_नकल(cmd->ssid.ssid, arg->ssid, arg->ssid_len);
		पूर्ण
		अगर (arg->hidden_ssid)
			cmd->flags |= WMI_VDEV_START_HIDDEN_SSID;
		अगर (arg->pmf_enabled)
			cmd->flags |= WMI_VDEV_START_PMF_ENABLED;
	पूर्ण

	cmd->flags |= WMI_VDEV_START_LDPC_RX_ENABLED;

	ptr = skb->data + माप(*cmd);
	chan = ptr;

	ath11k_wmi_put_wmi_channel(chan, arg);

	chan->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_CHANNEL) |
			   FIELD_PREP(WMI_TLV_LEN,
				      माप(*chan) - TLV_HDR_SIZE);
	ptr += माप(*chan);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_STRUCT) |
		      FIELD_PREP(WMI_TLV_LEN, 0);

	/* Note: This is a nested TLV containing:
	 * [wmi_tlv][wmi_p2p_noa_descriptor][wmi_tlv]..
	 */

	ptr += माप(*tlv);

	अगर (restart)
		ret = ath11k_wmi_cmd_send(wmi, skb,
					  WMI_VDEV_RESTART_REQUEST_CMDID);
	अन्यथा
		ret = ath11k_wmi_cmd_send(wmi, skb,
					  WMI_VDEV_START_REQUEST_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to submit vdev_%s cmd\n",
			    restart ? "restart" : "start");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "vdev %s id 0x%x freq 0x%x mode 0x%x\n",
		   restart ? "restart" : "start", arg->vdev_id,
		   arg->channel.freq, arg->channel.mode);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_vdev_up(काष्ठा ath11k *ar, u32 vdev_id, u32 aid, स्थिर u8 *bssid)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_up_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_up_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_UP_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->vdev_assoc_id = aid;

	ether_addr_copy(cmd->vdev_bssid.addr, bssid);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_VDEV_UP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to submit WMI_VDEV_UP cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI mgmt vdev up id 0x%x assoc id %d bssid %pM\n",
		   vdev_id, aid, bssid);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_peer_create_cmd(काष्ठा ath11k *ar,
				    काष्ठा peer_create_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_peer_create_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_peer_create_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PEER_CREATE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	ether_addr_copy(cmd->peer_macaddr.addr, param->peer_addr);
	cmd->peer_type = param->peer_type;
	cmd->vdev_id = param->vdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PEER_CREATE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to submit WMI_PEER_CREATE cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI peer create vdev_id %d peer_addr %pM\n",
		   param->vdev_id, param->peer_addr);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_peer_delete_cmd(काष्ठा ath11k *ar,
				    स्थिर u8 *peer_addr, u8 vdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_peer_delete_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_peer_delete_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PEER_DELETE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);
	cmd->vdev_id = vdev_id;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI peer delete vdev_id %d peer_addr %pM\n",
		   vdev_id,  peer_addr);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PEER_DELETE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PEER_DELETE cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_pdev_set_regकरोमुख्य(काष्ठा ath11k *ar,
				       काष्ठा pdev_set_regकरोमुख्य_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pdev_set_regकरोमुख्य_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_set_regकरोमुख्य_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_PDEV_SET_REGDOMAIN_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->reg_करोमुख्य = param->current_rd_in_use;
	cmd->reg_करोमुख्य_2g = param->current_rd_2g;
	cmd->reg_करोमुख्य_5g = param->current_rd_5g;
	cmd->conक्रमmance_test_limit_2g = param->ctl_2g;
	cmd->conक्रमmance_test_limit_5g = param->ctl_5g;
	cmd->dfs_करोमुख्य = param->dfs_करोमुख्य;
	cmd->pdev_id = param->pdev_id;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI pdev regd rd %d rd2g %d rd5g %d domain %d pdev id %d\n",
		   param->current_rd_in_use, param->current_rd_2g,
		   param->current_rd_5g, param->dfs_करोमुख्य, param->pdev_id);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PDEV_SET_REGDOMAIN_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_PDEV_SET_REGDOMAIN cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_set_peer_param(काष्ठा ath11k *ar, स्थिर u8 *peer_addr,
			      u32 vdev_id, u32 param_id, u32 param_val)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_peer_set_param_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_peer_set_param_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PEER_SET_PARAM_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);
	cmd->vdev_id = vdev_id;
	cmd->param_id = param_id;
	cmd->param_value = param_val;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PEER_SET_PARAM_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PEER_SET_PARAM cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev %d peer 0x%pM set param %d value %d\n",
		   vdev_id, peer_addr, param_id, param_val);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_peer_flush_tids_cmd(काष्ठा ath11k *ar,
					u8 peer_addr[ETH_ALEN],
					काष्ठा peer_flush_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_peer_flush_tids_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_peer_flush_tids_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PEER_FLUSH_TIDS_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);
	cmd->peer_tid_biपंचांगap = param->peer_tid_biपंचांगap;
	cmd->vdev_id = param->vdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PEER_FLUSH_TIDS_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_PEER_FLUSH_TIDS cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI peer flush vdev_id %d peer_addr %pM tids %08x\n",
		   param->vdev_id, peer_addr, param->peer_tid_biपंचांगap);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_peer_rx_reorder_queue_setup(काष्ठा ath11k *ar,
					   पूर्णांक vdev_id, स्थिर u8 *addr,
					   dma_addr_t paddr, u8 tid,
					   u8 ba_winकरोw_size_valid,
					   u32 ba_winकरोw_size)
अणु
	काष्ठा wmi_peer_reorder_queue_setup_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_peer_reorder_queue_setup_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_REORDER_QUEUE_SETUP_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	ether_addr_copy(cmd->peer_macaddr.addr, addr);
	cmd->vdev_id = vdev_id;
	cmd->tid = tid;
	cmd->queue_ptr_lo = lower_32_bits(paddr);
	cmd->queue_ptr_hi = upper_32_bits(paddr);
	cmd->queue_no = tid;
	cmd->ba_winकरोw_size_valid = ba_winकरोw_size_valid;
	cmd->ba_winकरोw_size = ba_winकरोw_size;

	ret = ath11k_wmi_cmd_send(ar->wmi, skb,
				  WMI_PEER_REORDER_QUEUE_SETUP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_PEER_REORDER_QUEUE_SETUP\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "wmi rx reorder queue setup addr %pM vdev_id %d tid %d\n",
		   addr, vdev_id, tid);

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_rx_reord_queue_हटाओ(काष्ठा ath11k *ar,
				 काष्ठा rx_reorder_queue_हटाओ_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_peer_reorder_queue_हटाओ_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_peer_reorder_queue_हटाओ_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_REORDER_QUEUE_REMOVE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	ether_addr_copy(cmd->peer_macaddr.addr, param->peer_macaddr);
	cmd->vdev_id = param->vdev_id;
	cmd->tid_mask = param->peer_tid_biपंचांगap;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "%s: peer_macaddr %pM vdev_id %d, tid_map %d", __func__,
		   param->peer_macaddr, param->vdev_id, param->peer_tid_biपंचांगap);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PEER_REORDER_QUEUE_REMOVE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_PEER_REORDER_QUEUE_REMOVE_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_set_param(काष्ठा ath11k *ar, u32 param_id,
			      u32 param_value, u8 pdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pdev_set_param_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_set_param_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_SET_PARAM_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->pdev_id = pdev_id;
	cmd->param_id = param_id;
	cmd->param_value = param_value;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PDEV_SET_PARAM_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PDEV_SET_PARAM cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI pdev set param %d pdev id %d value %d\n",
		   param_id, pdev_id, param_value);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_set_ps_mode(काष्ठा ath11k *ar, पूर्णांक vdev_id, u32 enable)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pdev_set_ps_mode_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_set_ps_mode_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_STA_POWERSAVE_MODE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->sta_ps_mode = enable;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_STA_POWERSAVE_MODE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PDEV_SET_PARAM cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev set psmode %d vdev id %d\n",
		   enable, vdev_id);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_suspend(काष्ठा ath11k *ar, u32 suspend_opt,
			    u32 pdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pdev_suspend_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_suspend_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_SUSPEND_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->suspend_opt = suspend_opt;
	cmd->pdev_id = pdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PDEV_SUSPEND_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PDEV_SUSPEND cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI pdev suspend pdev_id %d\n", pdev_id);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_resume(काष्ठा ath11k *ar, u32 pdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pdev_resume_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_resume_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_RESUME_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->pdev_id = pdev_id;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI pdev resume pdev id %d\n", pdev_id);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PDEV_RESUME_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PDEV_RESUME cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

/* TODO FW Support क्रम the cmd is not available yet.
 * Can be tested once the command and corresponding
 * event is implemented in FW
 */
पूर्णांक ath11k_wmi_pdev_bss_chan_info_request(काष्ठा ath11k *ar,
					  क्रमागत wmi_bss_chan_info_req_type type)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pdev_bss_chan_info_req_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_bss_chan_info_req_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_PDEV_BSS_CHAN_INFO_REQUEST) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->req_type = type;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI bss chan info req type %d\n", type);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_BSS_CHAN_INFO_REQUEST_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_PDEV_BSS_CHAN_INFO_REQUEST cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_set_ap_ps_param_cmd(काष्ठा ath11k *ar, u8 *peer_addr,
					काष्ठा ap_ps_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_ap_ps_peer_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_ap_ps_peer_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_AP_PS_PEER_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = param->vdev_id;
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);
	cmd->param = param->param;
	cmd->value = param->value;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_AP_PS_PEER_PARAM_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_AP_PS_PEER_PARAM_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI set ap ps vdev id %d peer %pM param %d value %d\n",
		   param->vdev_id, peer_addr, param->param, param->value);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_set_sta_ps_param(काष्ठा ath11k *ar, u32 vdev_id,
				u32 param, u32 param_value)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_sta_घातersave_param_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_sta_घातersave_param_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_STA_POWERSAVE_PARAM_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = vdev_id;
	cmd->param = param;
	cmd->value = param_value;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI set sta ps vdev_id %d param %d value %d\n",
		   vdev_id, param, param_value);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_STA_POWERSAVE_PARAM_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_STA_POWERSAVE_PARAM_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_क्रमce_fw_hang_cmd(काष्ठा ath11k *ar, u32 type, u32 delay_समय_ms)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_क्रमce_fw_hang_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_क्रमce_fw_hang_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_FORCE_FW_HANG_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);

	cmd->type = type;
	cmd->delay_समय_ms = delay_समय_ms;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_FORCE_FW_HANG_CMDID);

	अगर (ret) अणु
		ath11k_warn(ar->ab, "Failed to send WMI_FORCE_FW_HANG_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_vdev_set_param_cmd(काष्ठा ath11k *ar, u32 vdev_id,
				  u32 param_id, u32 param_value)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_set_param_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_set_param_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_SET_PARAM_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = vdev_id;
	cmd->param_id = param_id;
	cmd->param_value = param_value;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_VDEV_SET_PARAM_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_VDEV_SET_PARAM_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev id 0x%x set param %d value %d\n",
		   vdev_id, param_id, param_value);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_stats_request_cmd(काष्ठा ath11k *ar,
				      काष्ठा stats_request_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_request_stats_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_request_stats_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_REQUEST_STATS_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->stats_id = param->stats_id;
	cmd->vdev_id = param->vdev_id;
	cmd->pdev_id = param->pdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_REQUEST_STATS_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_REQUEST_STATS cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI request stats 0x%x vdev id %d pdev id %d\n",
		   param->stats_id, param->vdev_id, param->pdev_id);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_pdev_temperature_cmd(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_get_pdev_temperature_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_get_pdev_temperature_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_GET_TEMPERATURE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->pdev_id = ar->pdev->pdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PDEV_GET_TEMPERATURE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PDEV_GET_TEMPERATURE cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI pdev get temperature for pdev_id %d\n", ar->pdev->pdev_id);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_bcn_offload_control_cmd(काष्ठा ath11k *ar,
					    u32 vdev_id, u32 bcn_ctrl_op)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_bcn_offload_ctrl_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_bcn_offload_ctrl_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_BCN_OFFLOAD_CTRL_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = vdev_id;
	cmd->bcn_ctrl_op = bcn_ctrl_op;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI bcn ctrl offload vdev id %d ctrl_op %d\n",
		   vdev_id, bcn_ctrl_op);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_BCN_OFFLOAD_CTRL_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_BCN_OFFLOAD_CTRL_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_bcn_पंचांगpl(काष्ठा ath11k *ar, u32 vdev_id,
			काष्ठा ieee80211_mutable_offsets *offs,
			काष्ठा sk_buff *bcn)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_bcn_पंचांगpl_cmd *cmd;
	काष्ठा wmi_bcn_prb_info *bcn_prb_info;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	पूर्णांक ret, len;
	माप_प्रकार aligned_len = roundup(bcn->len, 4);

	len = माप(*cmd) + माप(*bcn_prb_info) + TLV_HDR_SIZE + aligned_len;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_bcn_पंचांगpl_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_BCN_TMPL_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->tim_ie_offset = offs->tim_offset;
	cmd->csa_चयन_count_offset = offs->cntdwn_counter_offs[0];
	cmd->ext_csa_चयन_count_offset = offs->cntdwn_counter_offs[1];
	cmd->buf_len = bcn->len;

	ptr = skb->data + माप(*cmd);

	bcn_prb_info = ptr;
	len = माप(*bcn_prb_info);
	bcn_prb_info->tlv_header = FIELD_PREP(WMI_TLV_TAG,
					      WMI_TAG_BCN_PRB_INFO) |
				   FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	bcn_prb_info->caps = 0;
	bcn_prb_info->erp = 0;

	ptr += माप(*bcn_prb_info);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_BYTE) |
		      FIELD_PREP(WMI_TLV_LEN, aligned_len);
	स_नकल(tlv->value, bcn->data, bcn->len);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_BCN_TMPL_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_BCN_TMPL_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_vdev_install_key(काष्ठा ath11k *ar,
				काष्ठा wmi_vdev_install_key_arg *arg)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_install_key_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;
	पूर्णांक key_len_aligned = roundup(arg->key_len, माप(uपूर्णांक32_t));

	len = माप(*cmd) + TLV_HDR_SIZE + key_len_aligned;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_install_key_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VDEV_INSTALL_KEY_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = arg->vdev_id;
	ether_addr_copy(cmd->peer_macaddr.addr, arg->macaddr);
	cmd->key_idx = arg->key_idx;
	cmd->key_flags = arg->key_flags;
	cmd->key_cipher = arg->key_cipher;
	cmd->key_len = arg->key_len;
	cmd->key_txmic_len = arg->key_txmic_len;
	cmd->key_rxmic_len = arg->key_rxmic_len;

	अगर (arg->key_rsc_counter)
		स_नकल(&cmd->key_rsc_counter, &arg->key_rsc_counter,
		       माप(काष्ठा wmi_key_seq_counter));

	tlv = (काष्ठा wmi_tlv *)(skb->data + माप(*cmd));
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_BYTE) |
		      FIELD_PREP(WMI_TLV_LEN, key_len_aligned);
	स_नकल(tlv->value, (u8 *)arg->key_data, key_len_aligned);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_VDEV_INSTALL_KEY_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_VDEV_INSTALL_KEY cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev install key idx %d cipher %d len %d\n",
		   arg->key_idx, arg->key_cipher, arg->key_len);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
ath11k_wmi_copy_peer_flags(काष्ठा wmi_peer_assoc_complete_cmd *cmd,
			   काष्ठा peer_assoc_params *param,
			   bool hw_crypto_disabled)
अणु
	cmd->peer_flags = 0;

	अगर (param->is_wme_set) अणु
		अगर (param->qos_flag)
			cmd->peer_flags |= WMI_PEER_QOS;
		अगर (param->apsd_flag)
			cmd->peer_flags |= WMI_PEER_APSD;
		अगर (param->ht_flag)
			cmd->peer_flags |= WMI_PEER_HT;
		अगर (param->bw_40)
			cmd->peer_flags |= WMI_PEER_40MHZ;
		अगर (param->bw_80)
			cmd->peer_flags |= WMI_PEER_80MHZ;
		अगर (param->bw_160)
			cmd->peer_flags |= WMI_PEER_160MHZ;

		/* Typically अगर STBC is enabled क्रम VHT it should be enabled
		 * क्रम HT as well
		 **/
		अगर (param->stbc_flag)
			cmd->peer_flags |= WMI_PEER_STBC;

		/* Typically अगर LDPC is enabled क्रम VHT it should be enabled
		 * क्रम HT as well
		 **/
		अगर (param->ldpc_flag)
			cmd->peer_flags |= WMI_PEER_LDPC;

		अगर (param->अटल_mimops_flag)
			cmd->peer_flags |= WMI_PEER_STATIC_MIMOPS;
		अगर (param->dynamic_mimops_flag)
			cmd->peer_flags |= WMI_PEER_DYN_MIMOPS;
		अगर (param->spatial_mux_flag)
			cmd->peer_flags |= WMI_PEER_SPATIAL_MUX;
		अगर (param->vht_flag)
			cmd->peer_flags |= WMI_PEER_VHT;
		अगर (param->he_flag)
			cmd->peer_flags |= WMI_PEER_HE;
		अगर (param->twt_requester)
			cmd->peer_flags |= WMI_PEER_TWT_REQ;
		अगर (param->twt_responder)
			cmd->peer_flags |= WMI_PEER_TWT_RESP;
	पूर्ण

	/* Suppress authorization क्रम all AUTH modes that need 4-way handshake
	 * (during re-association).
	 * Authorization will be करोne क्रम these modes on key installation.
	 */
	अगर (param->auth_flag)
		cmd->peer_flags |= WMI_PEER_AUTH;
	अगर (param->need_ptk_4_way) अणु
		cmd->peer_flags |= WMI_PEER_NEED_PTK_4_WAY;
		अगर (!hw_crypto_disabled)
			cmd->peer_flags &= ~WMI_PEER_AUTH;
	पूर्ण
	अगर (param->need_gtk_2_way)
		cmd->peer_flags |= WMI_PEER_NEED_GTK_2_WAY;
	/* safe mode bypass the 4-way handshake */
	अगर (param->safe_mode_enabled)
		cmd->peer_flags &= ~(WMI_PEER_NEED_PTK_4_WAY |
				     WMI_PEER_NEED_GTK_2_WAY);

	अगर (param->is_pmf_enabled)
		cmd->peer_flags |= WMI_PEER_PMF;

	/* Disable AMSDU क्रम station transmit, अगर user configures it */
	/* Disable AMSDU क्रम AP transmit to 11n Stations, अगर user configures
	 * it
	 * अगर (param->amsdu_disable) Add after FW support
	 **/

	/* Target निश्चितs अगर node is marked HT and all MCS is set to 0.
	 * Mark the node as non-HT अगर all the mcs rates are disabled through
	 * iwpriv
	 **/
	अगर (param->peer_ht_rates.num_rates == 0)
		cmd->peer_flags &= ~WMI_PEER_HT;
पूर्ण

पूर्णांक ath11k_wmi_send_peer_assoc_cmd(काष्ठा ath11k *ar,
				   काष्ठा peer_assoc_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_peer_assoc_complete_cmd *cmd;
	काष्ठा wmi_vht_rate_set *mcs;
	काष्ठा wmi_he_rate_set *he_mcs;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	u32 peer_legacy_rates_align;
	u32 peer_ht_rates_align;
	पूर्णांक i, ret, len;

	peer_legacy_rates_align = roundup(param->peer_legacy_rates.num_rates,
					  माप(u32));
	peer_ht_rates_align = roundup(param->peer_ht_rates.num_rates,
				      माप(u32));

	len = माप(*cmd) +
	      TLV_HDR_SIZE + (peer_legacy_rates_align * माप(u8)) +
	      TLV_HDR_SIZE + (peer_ht_rates_align * माप(u8)) +
	      माप(*mcs) + TLV_HDR_SIZE +
	      (माप(*he_mcs) * param->peer_he_mcs_count);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	ptr = skb->data;

	cmd = ptr;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_PEER_ASSOC_COMPLETE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = param->vdev_id;

	cmd->peer_new_assoc = param->peer_new_assoc;
	cmd->peer_associd = param->peer_associd;

	ath11k_wmi_copy_peer_flags(cmd, param,
				   test_bit(ATH11K_FLAG_HW_CRYPTO_DISABLED,
					    &ar->ab->dev_flags));

	ether_addr_copy(cmd->peer_macaddr.addr, param->peer_mac);

	cmd->peer_rate_caps = param->peer_rate_caps;
	cmd->peer_caps = param->peer_caps;
	cmd->peer_listen_पूर्णांकval = param->peer_listen_पूर्णांकval;
	cmd->peer_ht_caps = param->peer_ht_caps;
	cmd->peer_max_mpdu = param->peer_max_mpdu;
	cmd->peer_mpdu_density = param->peer_mpdu_density;
	cmd->peer_vht_caps = param->peer_vht_caps;
	cmd->peer_phymode = param->peer_phymode;

	/* Update 11ax capabilities */
	cmd->peer_he_cap_info = param->peer_he_cap_macinfo[0];
	cmd->peer_he_cap_info_ext = param->peer_he_cap_macinfo[1];
	cmd->peer_he_cap_info_पूर्णांकernal = param->peer_he_cap_macinfo_पूर्णांकernal;
	cmd->peer_he_caps_6ghz = param->peer_he_caps_6ghz;
	cmd->peer_he_ops = param->peer_he_ops;
	स_नकल(&cmd->peer_he_cap_phy, &param->peer_he_cap_phyinfo,
	       माप(param->peer_he_cap_phyinfo));
	स_नकल(&cmd->peer_ppet, &param->peer_ppet,
	       माप(param->peer_ppet));

	/* Update peer legacy rate inक्रमmation */
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_BYTE) |
		      FIELD_PREP(WMI_TLV_LEN, peer_legacy_rates_align);

	ptr += TLV_HDR_SIZE;

	cmd->num_peer_legacy_rates = param->peer_legacy_rates.num_rates;
	स_नकल(ptr, param->peer_legacy_rates.rates,
	       param->peer_legacy_rates.num_rates);

	/* Update peer HT rate inक्रमmation */
	ptr += peer_legacy_rates_align;

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_BYTE) |
		      FIELD_PREP(WMI_TLV_LEN, peer_ht_rates_align);
	ptr += TLV_HDR_SIZE;
	cmd->num_peer_ht_rates = param->peer_ht_rates.num_rates;
	स_नकल(ptr, param->peer_ht_rates.rates,
	       param->peer_ht_rates.num_rates);

	/* VHT Rates */
	ptr += peer_ht_rates_align;

	mcs = ptr;

	mcs->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_VHT_RATE_SET) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*mcs) - TLV_HDR_SIZE);

	cmd->peer_nss = param->peer_nss;

	/* Update bandwidth-NSS mapping */
	cmd->peer_bw_rxnss_override = 0;
	cmd->peer_bw_rxnss_override |= param->peer_bw_rxnss_override;

	अगर (param->vht_capable) अणु
		mcs->rx_max_rate = param->rx_max_rate;
		mcs->rx_mcs_set = param->rx_mcs_set;
		mcs->tx_max_rate = param->tx_max_rate;
		mcs->tx_mcs_set = param->tx_mcs_set;
	पूर्ण

	/* HE Rates */
	cmd->peer_he_mcs = param->peer_he_mcs_count;
	cmd->min_data_rate = param->min_data_rate;

	ptr += माप(*mcs);

	len = param->peer_he_mcs_count * माप(*he_mcs);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_STRUCT) |
		      FIELD_PREP(WMI_TLV_LEN, len);
	ptr += TLV_HDR_SIZE;

	/* Loop through the HE rate set */
	क्रम (i = 0; i < param->peer_he_mcs_count; i++) अणु
		he_mcs = ptr;
		he_mcs->tlv_header = FIELD_PREP(WMI_TLV_TAG,
						WMI_TAG_HE_RATE_SET) |
				     FIELD_PREP(WMI_TLV_LEN,
						माप(*he_mcs) - TLV_HDR_SIZE);

		he_mcs->rx_mcs_set = param->peer_he_rx_mcs_set[i];
		he_mcs->tx_mcs_set = param->peer_he_tx_mcs_set[i];
		ptr += माप(*he_mcs);
	पूर्ण

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_PEER_ASSOC_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_PEER_ASSOC_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "wmi peer assoc vdev id %d assoc id %d peer mac %pM peer_flags %x rate_caps %x peer_caps %x listen_intval %d ht_caps %x max_mpdu %d nss %d phymode %d peer_mpdu_density %d vht_caps %x he cap_info %x he ops %x he cap_info_ext %x he phy %x %x %x peer_bw_rxnss_override %x\n",
		   cmd->vdev_id, cmd->peer_associd, param->peer_mac,
		   cmd->peer_flags, cmd->peer_rate_caps, cmd->peer_caps,
		   cmd->peer_listen_पूर्णांकval, cmd->peer_ht_caps,
		   cmd->peer_max_mpdu, cmd->peer_nss, cmd->peer_phymode,
		   cmd->peer_mpdu_density,
		   cmd->peer_vht_caps, cmd->peer_he_cap_info,
		   cmd->peer_he_ops, cmd->peer_he_cap_info_ext,
		   cmd->peer_he_cap_phy[0], cmd->peer_he_cap_phy[1],
		   cmd->peer_he_cap_phy[2],
		   cmd->peer_bw_rxnss_override);

	वापस ret;
पूर्ण

व्योम ath11k_wmi_start_scan_init(काष्ठा ath11k *ar,
				काष्ठा scan_req_params *arg)
अणु
	/* setup commonly used values */
	arg->scan_req_id = 1;
	arg->scan_priority = WMI_SCAN_PRIORITY_LOW;
	arg->dwell_समय_active = 50;
	arg->dwell_समय_active_2g = 0;
	arg->dwell_समय_passive = 150;
	arg->dwell_समय_active_6g = 40;
	arg->dwell_समय_passive_6g = 30;
	arg->min_rest_समय = 50;
	arg->max_rest_समय = 500;
	arg->repeat_probe_समय = 0;
	arg->probe_spacing_समय = 0;
	arg->idle_समय = 0;
	arg->max_scan_समय = 20000;
	arg->probe_delay = 5;
	arg->notअगरy_scan_events = WMI_SCAN_EVENT_STARTED |
				  WMI_SCAN_EVENT_COMPLETED |
				  WMI_SCAN_EVENT_BSS_CHANNEL |
				  WMI_SCAN_EVENT_FOREIGN_CHAN |
				  WMI_SCAN_EVENT_DEQUEUED;
	arg->scan_flags |= WMI_SCAN_CHAN_STAT_EVENT;
	arg->num_bssid = 1;

	/* fill bssid_list[0] with 0xff, otherwise bssid and RA will be
	 * ZEROs in probe request
	 */
	eth_broadcast_addr(arg->bssid_list[0].addr);
पूर्ण

अटल अंतरभूत व्योम
ath11k_wmi_copy_scan_event_cntrl_flags(काष्ठा wmi_start_scan_cmd *cmd,
				       काष्ठा scan_req_params *param)
अणु
	/* Scan events subscription */
	अगर (param->scan_ev_started)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_STARTED;
	अगर (param->scan_ev_completed)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_COMPLETED;
	अगर (param->scan_ev_bss_chan)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_BSS_CHANNEL;
	अगर (param->scan_ev_क्रमeign_chan)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_FOREIGN_CHAN;
	अगर (param->scan_ev_dequeued)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_DEQUEUED;
	अगर (param->scan_ev_preempted)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_PREEMPTED;
	अगर (param->scan_ev_start_failed)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_START_FAILED;
	अगर (param->scan_ev_restarted)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_RESTARTED;
	अगर (param->scan_ev_क्रमeign_chn_निकास)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_FOREIGN_CHAN_EXIT;
	अगर (param->scan_ev_suspended)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_SUSPENDED;
	अगर (param->scan_ev_resumed)
		cmd->notअगरy_scan_events |=  WMI_SCAN_EVENT_RESUMED;

	/** Set scan control flags */
	cmd->scan_ctrl_flags = 0;
	अगर (param->scan_f_passive)
		cmd->scan_ctrl_flags |=  WMI_SCAN_FLAG_PASSIVE;
	अगर (param->scan_f_strict_passive_pch)
		cmd->scan_ctrl_flags |=  WMI_SCAN_FLAG_STRICT_PASSIVE_ON_PCHN;
	अगर (param->scan_f_promisc_mode)
		cmd->scan_ctrl_flags |=  WMI_SCAN_FILTER_PROMISCUOS;
	अगर (param->scan_f_capture_phy_err)
		cmd->scan_ctrl_flags |=  WMI_SCAN_CAPTURE_PHY_ERROR;
	अगर (param->scan_f_half_rate)
		cmd->scan_ctrl_flags |=  WMI_SCAN_FLAG_HALF_RATE_SUPPORT;
	अगर (param->scan_f_quarter_rate)
		cmd->scan_ctrl_flags |=  WMI_SCAN_FLAG_QUARTER_RATE_SUPPORT;
	अगर (param->scan_f_cck_rates)
		cmd->scan_ctrl_flags |=  WMI_SCAN_ADD_CCK_RATES;
	अगर (param->scan_f_ofdm_rates)
		cmd->scan_ctrl_flags |=  WMI_SCAN_ADD_OFDM_RATES;
	अगर (param->scan_f_chan_stat_evnt)
		cmd->scan_ctrl_flags |=  WMI_SCAN_CHAN_STAT_EVENT;
	अगर (param->scan_f_filter_prb_req)
		cmd->scan_ctrl_flags |=  WMI_SCAN_FILTER_PROBE_REQ;
	अगर (param->scan_f_bcast_probe)
		cmd->scan_ctrl_flags |=  WMI_SCAN_ADD_BCAST_PROBE_REQ;
	अगर (param->scan_f_offchan_mgmt_tx)
		cmd->scan_ctrl_flags |=  WMI_SCAN_OFFCHAN_MGMT_TX;
	अगर (param->scan_f_offchan_data_tx)
		cmd->scan_ctrl_flags |=  WMI_SCAN_OFFCHAN_DATA_TX;
	अगर (param->scan_f_क्रमce_active_dfs_chn)
		cmd->scan_ctrl_flags |=  WMI_SCAN_FLAG_FORCE_ACTIVE_ON_DFS;
	अगर (param->scan_f_add_tpc_ie_in_probe)
		cmd->scan_ctrl_flags |=  WMI_SCAN_ADD_TPC_IE_IN_PROBE_REQ;
	अगर (param->scan_f_add_ds_ie_in_probe)
		cmd->scan_ctrl_flags |=  WMI_SCAN_ADD_DS_IE_IN_PROBE_REQ;
	अगर (param->scan_f_add_spoofed_mac_in_probe)
		cmd->scan_ctrl_flags |=  WMI_SCAN_ADD_SPOOF_MAC_IN_PROBE_REQ;
	अगर (param->scan_f_add_अक्रम_seq_in_probe)
		cmd->scan_ctrl_flags |=  WMI_SCAN_RANDOM_SEQ_NO_IN_PROBE_REQ;
	अगर (param->scan_f_en_ie_whitelist_in_probe)
		cmd->scan_ctrl_flags |=
			 WMI_SCAN_ENABLE_IE_WHTELIST_IN_PROBE_REQ;

	/* क्रम adaptive scan mode using 3 bits (21 - 23 bits) */
	WMI_SCAN_SET_DWELL_MODE(cmd->scan_ctrl_flags,
				param->adaptive_dwell_समय_mode);
पूर्ण

पूर्णांक ath11k_wmi_send_scan_start_cmd(काष्ठा ath11k *ar,
				   काष्ठा scan_req_params *params)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_start_scan_cmd *cmd;
	काष्ठा wmi_ssid *ssid = शून्य;
	काष्ठा wmi_mac_addr *bssid;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	पूर्णांक i, ret, len;
	u32 *पंचांगp_ptr;
	u8 extraie_len_with_pad = 0;
	काष्ठा hपूर्णांक_लघु_ssid *s_ssid = शून्य;
	काष्ठा hपूर्णांक_bssid *hपूर्णांक_bssid = शून्य;

	len = माप(*cmd);

	len += TLV_HDR_SIZE;
	अगर (params->num_chan)
		len += params->num_chan * माप(u32);

	len += TLV_HDR_SIZE;
	अगर (params->num_ssids)
		len += params->num_ssids * माप(*ssid);

	len += TLV_HDR_SIZE;
	अगर (params->num_bssid)
		len += माप(*bssid) * params->num_bssid;

	len += TLV_HDR_SIZE;
	अगर (params->extraie.len)
		extraie_len_with_pad =
			roundup(params->extraie.len, माप(u32));
	len += extraie_len_with_pad;

	अगर (params->num_hपूर्णांक_bssid)
		len += TLV_HDR_SIZE +
		       params->num_hपूर्णांक_bssid * माप(काष्ठा hपूर्णांक_bssid);

	अगर (params->num_hपूर्णांक_s_ssid)
		len += TLV_HDR_SIZE +
		       params->num_hपूर्णांक_s_ssid * माप(काष्ठा hपूर्णांक_लघु_ssid);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	ptr = skb->data;

	cmd = ptr;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_START_SCAN_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->scan_id = params->scan_id;
	cmd->scan_req_id = params->scan_req_id;
	cmd->vdev_id = params->vdev_id;
	cmd->scan_priority = params->scan_priority;
	cmd->notअगरy_scan_events = params->notअगरy_scan_events;

	ath11k_wmi_copy_scan_event_cntrl_flags(cmd, params);

	cmd->dwell_समय_active = params->dwell_समय_active;
	cmd->dwell_समय_active_2g = params->dwell_समय_active_2g;
	cmd->dwell_समय_passive = params->dwell_समय_passive;
	cmd->dwell_समय_active_6g = params->dwell_समय_active_6g;
	cmd->dwell_समय_passive_6g = params->dwell_समय_passive_6g;
	cmd->min_rest_समय = params->min_rest_समय;
	cmd->max_rest_समय = params->max_rest_समय;
	cmd->repeat_probe_समय = params->repeat_probe_समय;
	cmd->probe_spacing_समय = params->probe_spacing_समय;
	cmd->idle_समय = params->idle_समय;
	cmd->max_scan_समय = params->max_scan_समय;
	cmd->probe_delay = params->probe_delay;
	cmd->burst_duration = params->burst_duration;
	cmd->num_chan = params->num_chan;
	cmd->num_bssid = params->num_bssid;
	cmd->num_ssids = params->num_ssids;
	cmd->ie_len = params->extraie.len;
	cmd->n_probes = params->n_probes;

	ptr += माप(*cmd);

	len = params->num_chan * माप(u32);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_UINT32) |
		      FIELD_PREP(WMI_TLV_LEN, len);
	ptr += TLV_HDR_SIZE;
	पंचांगp_ptr = (u32 *)ptr;

	क्रम (i = 0; i < params->num_chan; ++i)
		पंचांगp_ptr[i] = params->chan_list[i];

	ptr += len;

	len = params->num_ssids * माप(*ssid);
	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_FIXED_STRUCT) |
		      FIELD_PREP(WMI_TLV_LEN, len);

	ptr += TLV_HDR_SIZE;

	अगर (params->num_ssids) अणु
		ssid = ptr;
		क्रम (i = 0; i < params->num_ssids; ++i) अणु
			ssid->ssid_len = params->ssid[i].length;
			स_नकल(ssid->ssid, params->ssid[i].ssid,
			       params->ssid[i].length);
			ssid++;
		पूर्ण
	पूर्ण

	ptr += (params->num_ssids * माप(*ssid));
	len = params->num_bssid * माप(*bssid);
	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_FIXED_STRUCT) |
		      FIELD_PREP(WMI_TLV_LEN, len);

	ptr += TLV_HDR_SIZE;
	bssid = ptr;

	अगर (params->num_bssid) अणु
		क्रम (i = 0; i < params->num_bssid; ++i) अणु
			ether_addr_copy(bssid->addr,
					params->bssid_list[i].addr);
			bssid++;
		पूर्ण
	पूर्ण

	ptr += params->num_bssid * माप(*bssid);

	len = extraie_len_with_pad;
	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_BYTE) |
		      FIELD_PREP(WMI_TLV_LEN, len);
	ptr += TLV_HDR_SIZE;

	अगर (params->extraie.len)
		स_नकल(ptr, params->extraie.ptr,
		       params->extraie.len);

	ptr += extraie_len_with_pad;

	अगर (params->num_hपूर्णांक_s_ssid) अणु
		len = params->num_hपूर्णांक_s_ssid * माप(काष्ठा hपूर्णांक_लघु_ssid);
		tlv = ptr;
		tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_FIXED_STRUCT) |
			      FIELD_PREP(WMI_TLV_LEN, len);
		ptr += TLV_HDR_SIZE;
		s_ssid = ptr;
		क्रम (i = 0; i < params->num_hपूर्णांक_s_ssid; ++i) अणु
			s_ssid->freq_flags = params->hपूर्णांक_s_ssid[i].freq_flags;
			s_ssid->लघु_ssid = params->hपूर्णांक_s_ssid[i].लघु_ssid;
			s_ssid++;
		पूर्ण
		ptr += len;
	पूर्ण

	अगर (params->num_hपूर्णांक_bssid) अणु
		len = params->num_hपूर्णांक_bssid * माप(काष्ठा hपूर्णांक_bssid);
		tlv = ptr;
		tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_FIXED_STRUCT) |
			      FIELD_PREP(WMI_TLV_LEN, len);
		ptr += TLV_HDR_SIZE;
		hपूर्णांक_bssid = ptr;
		क्रम (i = 0; i < params->num_hपूर्णांक_bssid; ++i) अणु
			hपूर्णांक_bssid->freq_flags =
				params->hपूर्णांक_bssid[i].freq_flags;
			ether_addr_copy(&params->hपूर्णांक_bssid[i].bssid.addr[0],
					&hपूर्णांक_bssid->bssid.addr[0]);
			hपूर्णांक_bssid++;
		पूर्ण
	पूर्ण

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_START_SCAN_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_START_SCAN_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_scan_stop_cmd(काष्ठा ath11k *ar,
				  काष्ठा scan_cancel_param *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_stop_scan_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_stop_scan_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_STOP_SCAN_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = param->vdev_id;
	cmd->requestor = param->requester;
	cmd->scan_id = param->scan_id;
	cmd->pdev_id = param->pdev_id;
	/* stop the scan with the corresponding scan_id */
	अगर (param->req_type == WLAN_SCAN_CANCEL_PDEV_ALL) अणु
		/* Cancelling all scans */
		cmd->req_type =  WMI_SCAN_STOP_ALL;
	पूर्ण अन्यथा अगर (param->req_type == WLAN_SCAN_CANCEL_VDEV_ALL) अणु
		/* Cancelling VAP scans */
		cmd->req_type =  WMI_SCN_STOP_VAP_ALL;
	पूर्ण अन्यथा अगर (param->req_type == WLAN_SCAN_CANCEL_SINGLE) अणु
		/* Cancelling specअगरic scan */
		cmd->req_type =  WMI_SCAN_STOP_ONE;
	पूर्ण अन्यथा अणु
		ath11k_warn(ar->ab, "invalid scan cancel param %d",
			    param->req_type);
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_STOP_SCAN_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_STOP_SCAN_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_scan_chan_list_cmd(काष्ठा ath11k *ar,
				       काष्ठा scan_chan_list_params *chan_list)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_scan_chan_list_cmd *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_channel *chan_info;
	काष्ठा channel_param *tchan_info;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	पूर्णांक i, ret, len;
	u16 num_send_chans, num_sends = 0, max_chan_limit = 0;
	u32 *reg1, *reg2;

	tchan_info = &chan_list->ch_param[0];
	जबतक (chan_list->nallchans) अणु
		len = माप(*cmd) + TLV_HDR_SIZE;
		max_chan_limit = (wmi->wmi_ab->max_msg_len[ar->pdev_idx] - len) /
			माप(*chan_info);

		अगर (chan_list->nallchans > max_chan_limit)
			num_send_chans = max_chan_limit;
		अन्यथा
			num_send_chans = chan_list->nallchans;

		chan_list->nallchans -= num_send_chans;
		len += माप(*chan_info) * num_send_chans;

		skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
		अगर (!skb)
			वापस -ENOMEM;

		cmd = (काष्ठा wmi_scan_chan_list_cmd *)skb->data;
		cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_SCAN_CHAN_LIST_CMD) |
			FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
		cmd->pdev_id = chan_list->pdev_id;
		cmd->num_scan_chans = num_send_chans;
		अगर (num_sends)
			cmd->flags |= WMI_APPEND_TO_EXISTING_CHAN_LIST_FLAG;

		ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
			   "WMI no.of chan = %d len = %d pdev_id = %d num_sends = %d\n",
			   num_send_chans, len, cmd->pdev_id, num_sends);

		ptr = skb->data + माप(*cmd);

		len = माप(*chan_info) * num_send_chans;
		tlv = ptr;
		tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_STRUCT) |
			      FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
		ptr += TLV_HDR_SIZE;

		क्रम (i = 0; i < num_send_chans; ++i) अणु
			chan_info = ptr;
			स_रखो(chan_info, 0, माप(*chan_info));
			len = माप(*chan_info);
			chan_info->tlv_header = FIELD_PREP(WMI_TLV_TAG,
							   WMI_TAG_CHANNEL) |
						FIELD_PREP(WMI_TLV_LEN,
							   len - TLV_HDR_SIZE);

			reg1 = &chan_info->reg_info_1;
			reg2 = &chan_info->reg_info_2;
			chan_info->mhz = tchan_info->mhz;
			chan_info->band_center_freq1 = tchan_info->cfreq1;
			chan_info->band_center_freq2 = tchan_info->cfreq2;

			अगर (tchan_info->is_chan_passive)
				chan_info->info |= WMI_CHAN_INFO_PASSIVE;
			अगर (tchan_info->allow_he)
				chan_info->info |= WMI_CHAN_INFO_ALLOW_HE;
			अन्यथा अगर (tchan_info->allow_vht)
				chan_info->info |= WMI_CHAN_INFO_ALLOW_VHT;
			अन्यथा अगर (tchan_info->allow_ht)
				chan_info->info |= WMI_CHAN_INFO_ALLOW_HT;
			अगर (tchan_info->half_rate)
				chan_info->info |= WMI_CHAN_INFO_HALF_RATE;
			अगर (tchan_info->quarter_rate)
				chan_info->info |= WMI_CHAN_INFO_QUARTER_RATE;
			अगर (tchan_info->psc_channel)
				chan_info->info |= WMI_CHAN_INFO_PSC;

			chan_info->info |= FIELD_PREP(WMI_CHAN_INFO_MODE,
						      tchan_info->phy_mode);
			*reg1 |= FIELD_PREP(WMI_CHAN_REG_INFO1_MIN_PWR,
					    tchan_info->minघातer);
			*reg1 |= FIELD_PREP(WMI_CHAN_REG_INFO1_MAX_PWR,
					    tchan_info->maxघातer);
			*reg1 |= FIELD_PREP(WMI_CHAN_REG_INFO1_MAX_REG_PWR,
					    tchan_info->maxregघातer);
			*reg1 |= FIELD_PREP(WMI_CHAN_REG_INFO1_REG_CLS,
					    tchan_info->reg_class_id);
			*reg2 |= FIELD_PREP(WMI_CHAN_REG_INFO2_ANT_MAX,
					    tchan_info->antennamax);

			ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
				   "WMI chan scan list chan[%d] = %u, chan_info->info %8x\n",
				   i, chan_info->mhz, chan_info->info);

			ptr += माप(*chan_info);

			tchan_info++;
		पूर्ण

		ret = ath11k_wmi_cmd_send(wmi, skb, WMI_SCAN_CHAN_LIST_CMDID);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to send WMI_SCAN_CHAN_LIST cmd\n");
			dev_kमुक्त_skb(skb);
			वापस ret;
		पूर्ण

		num_sends++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath11k_wmi_send_wmm_update_cmd_tlv(काष्ठा ath11k *ar, u32 vdev_id,
				       काष्ठा wmi_wmm_params_all_arg *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_vdev_set_wmm_params_cmd *cmd;
	काष्ठा wmi_wmm_params *wmm_param;
	काष्ठा wmi_wmm_params_arg *wmi_wmm_arg;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, ac;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_vdev_set_wmm_params_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_VDEV_SET_WMM_PARAMS_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = vdev_id;
	cmd->wmm_param_type = 0;

	क्रम (ac = 0; ac < WME_NUM_AC; ac++) अणु
		चयन (ac) अणु
		हाल WME_AC_BE:
			wmi_wmm_arg = &param->ac_be;
			अवरोध;
		हाल WME_AC_BK:
			wmi_wmm_arg = &param->ac_bk;
			अवरोध;
		हाल WME_AC_VI:
			wmi_wmm_arg = &param->ac_vi;
			अवरोध;
		हाल WME_AC_VO:
			wmi_wmm_arg = &param->ac_vo;
			अवरोध;
		पूर्ण

		wmm_param = (काष्ठा wmi_wmm_params *)&cmd->wmm_params[ac];
		wmm_param->tlv_header =
				FIELD_PREP(WMI_TLV_TAG,
					   WMI_TAG_VDEV_SET_WMM_PARAMS_CMD) |
				FIELD_PREP(WMI_TLV_LEN,
					   माप(*wmm_param) - TLV_HDR_SIZE);

		wmm_param->aअगरs = wmi_wmm_arg->aअगरs;
		wmm_param->cwmin = wmi_wmm_arg->cwmin;
		wmm_param->cwmax = wmi_wmm_arg->cwmax;
		wmm_param->txoplimit = wmi_wmm_arg->txop;
		wmm_param->acm = wmi_wmm_arg->acm;
		wmm_param->no_ack = wmi_wmm_arg->no_ack;

		ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
			   "wmi wmm set ac %d aifs %d cwmin %d cwmax %d txop %d acm %d no_ack %d\n",
			   ac, wmm_param->aअगरs, wmm_param->cwmin,
			   wmm_param->cwmax, wmm_param->txoplimit,
			   wmm_param->acm, wmm_param->no_ack);
	पूर्ण
	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_VDEV_SET_WMM_PARAMS_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_VDEV_SET_WMM_PARAMS_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_dfs_phyerr_offload_enable_cmd(काष्ठा ath11k *ar,
						  u32 pdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_dfs_phyerr_offload_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_dfs_phyerr_offload_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG,
			   WMI_TAG_PDEV_DFS_PHYERR_OFFLOAD_ENABLE_CMD) |
		FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->pdev_id = pdev_id;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI dfs phy err offload enable pdev id %d\n", pdev_id);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_DFS_PHYERR_OFFLOAD_ENABLE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_PDEV_DFS_PHYERR_OFFLOAD_ENABLE cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_delba_send(काष्ठा ath11k *ar, u32 vdev_id, स्थिर u8 *mac,
			  u32 tid, u32 initiator, u32 reason)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_delba_send_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_delba_send_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_DELBA_SEND_CMD) |
			FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	ether_addr_copy(cmd->peer_macaddr.addr, mac);
	cmd->tid = tid;
	cmd->initiator = initiator;
	cmd->reasoncode = reason;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "wmi delba send vdev_id 0x%X mac_addr %pM tid %u initiator %u reason %u\n",
		   vdev_id, mac, tid, initiator, reason);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_DELBA_SEND_CMDID);

	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_DELBA_SEND_CMDID cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_addba_set_resp(काष्ठा ath11k *ar, u32 vdev_id, स्थिर u8 *mac,
			      u32 tid, u32 status)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_addba_setresponse_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_addba_setresponse_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ADDBA_SETRESPONSE_CMD) |
		FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	ether_addr_copy(cmd->peer_macaddr.addr, mac);
	cmd->tid = tid;
	cmd->statuscode = status;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "wmi addba set resp vdev_id 0x%X mac_addr %pM tid %u status %u\n",
		   vdev_id, mac, tid, status);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_ADDBA_SET_RESP_CMDID);

	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_ADDBA_SET_RESP_CMDID cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_addba_send(काष्ठा ath11k *ar, u32 vdev_id, स्थिर u8 *mac,
			  u32 tid, u32 buf_size)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_addba_send_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_addba_send_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ADDBA_SEND_CMD) |
		FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	ether_addr_copy(cmd->peer_macaddr.addr, mac);
	cmd->tid = tid;
	cmd->buffersize = buf_size;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "wmi addba send vdev_id 0x%X mac_addr %pM tid %u bufsize %u\n",
		   vdev_id, mac, tid, buf_size);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_ADDBA_SEND_CMDID);

	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_ADDBA_SEND_CMDID cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_addba_clear_resp(काष्ठा ath11k *ar, u32 vdev_id, स्थिर u8 *mac)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_addba_clear_resp_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_addba_clear_resp_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ADDBA_CLEAR_RESP_CMD) |
		FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	ether_addr_copy(cmd->peer_macaddr.addr, mac);

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "wmi addba clear resp vdev_id 0x%X mac_addr %pM\n",
		   vdev_id, mac);

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_ADDBA_CLEAR_RESP_CMDID);

	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_ADDBA_CLEAR_RESP_CMDID cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_peer_pktlog_filter(काष्ठा ath11k *ar, u8 *addr, u8 enable)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pdev_pktlog_filter_cmd *cmd;
	काष्ठा wmi_pdev_pktlog_filter_info *info;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	पूर्णांक ret, len;

	len = माप(*cmd) + माप(*info) + TLV_HDR_SIZE;
	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_pktlog_filter_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_PEER_PKTLOG_FILTER_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->pdev_id = DP_HW2SW_MACID(ar->pdev->pdev_id);
	cmd->num_mac = 1;
	cmd->enable = enable;

	ptr = skb->data + माप(*cmd);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_STRUCT) |
		      FIELD_PREP(WMI_TLV_LEN, माप(*info));

	ptr += TLV_HDR_SIZE;
	info = ptr;

	ether_addr_copy(info->peer_macaddr.addr, addr);
	info->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_PEER_PKTLOG_FILTER_INFO) |
			   FIELD_PREP(WMI_TLV_LEN,
				      माप(*info) - TLV_HDR_SIZE);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_PKTLOG_FILTER_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PDEV_PKTLOG_ENABLE_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_send_init_country_cmd(काष्ठा ath11k *ar,
				 काष्ठा wmi_init_country_params init_cc_params)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_init_country_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_init_country_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG,
			   WMI_TAG_SET_INIT_COUNTRY_CMD) |
		FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->pdev_id = ar->pdev->pdev_id;

	चयन (init_cc_params.flags) अणु
	हाल ALPHA_IS_SET:
		cmd->init_cc_type = WMI_COUNTRY_INFO_TYPE_ALPHA;
		स_नकल((u8 *)&cmd->cc_info.alpha2,
		       init_cc_params.cc_info.alpha2, 3);
		अवरोध;
	हाल CC_IS_SET:
		cmd->init_cc_type = WMI_COUNTRY_INFO_TYPE_COUNTRY_CODE;
		cmd->cc_info.country_code = init_cc_params.cc_info.country_code;
		अवरोध;
	हाल REGDMN_IS_SET:
		cmd->init_cc_type = WMI_COUNTRY_INFO_TYPE_REGDOMAIN;
		cmd->cc_info.regकरोm_id = init_cc_params.cc_info.regकरोm_id;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_SET_INIT_COUNTRY_CMDID);

out:
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send WMI_SET_INIT_COUNTRY CMD :%d\n",
			    ret);
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_send_thermal_mitigation_param_cmd(काष्ठा ath11k *ar,
					     काष्ठा thermal_mitigation_params *param)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_therm_throt_config_request_cmd *cmd;
	काष्ठा wmi_therm_throt_level_config_info *lvl_conf;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	पूर्णांक i, ret, len;

	len = माप(*cmd) + TLV_HDR_SIZE +
	      THERMAL_LEVELS * माप(काष्ठा wmi_therm_throt_level_config_info);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_therm_throt_config_request_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_THERM_THROT_CONFIG_REQUEST) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->pdev_id = ar->pdev->pdev_id;
	cmd->enable = param->enable;
	cmd->dc = param->dc;
	cmd->dc_per_event = param->dc_per_event;
	cmd->therm_throt_levels = THERMAL_LEVELS;

	tlv = (काष्ठा wmi_tlv *)(skb->data + माप(*cmd));
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_STRUCT) |
		      FIELD_PREP(WMI_TLV_LEN,
				 (THERMAL_LEVELS *
				  माप(काष्ठा wmi_therm_throt_level_config_info)));

	lvl_conf = (काष्ठा wmi_therm_throt_level_config_info *)(skb->data +
								माप(*cmd) +
								TLV_HDR_SIZE);
	क्रम (i = 0; i < THERMAL_LEVELS; i++) अणु
		lvl_conf->tlv_header =
			FIELD_PREP(WMI_TLV_TAG, WMI_TAG_THERM_THROT_LEVEL_CONFIG_INFO) |
			FIELD_PREP(WMI_TLV_LEN, माप(*lvl_conf) - TLV_HDR_SIZE);

		lvl_conf->temp_lwm = param->levelconf[i].पंचांगplwm;
		lvl_conf->temp_hwm = param->levelconf[i].पंचांगphwm;
		lvl_conf->dc_off_percent = param->levelconf[i].dcoffpercent;
		lvl_conf->prio = param->levelconf[i].priority;
		lvl_conf++;
	पूर्ण

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_THERM_THROT_SET_CONF_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send THERM_THROT_SET_CONF cmd\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev set thermal throt pdev_id %d enable %d dc %d dc_per_event %x levels %d\n",
		   ar->pdev->pdev_id, param->enable, param->dc,
		   param->dc_per_event, THERMAL_LEVELS);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_pktlog_enable(काष्ठा ath11k *ar, u32 pktlog_filter)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pktlog_enable_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pktlog_enable_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_PKTLOG_ENABLE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->pdev_id = DP_HW2SW_MACID(ar->pdev->pdev_id);
	cmd->evlist = pktlog_filter;
	cmd->enable = ATH11K_WMI_PKTLOG_ENABLE_FORCE;

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_PKTLOG_ENABLE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PDEV_PKTLOG_ENABLE_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_pktlog_disable(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_pktlog_disable_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pktlog_disable_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_PKTLOG_DISABLE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->pdev_id = DP_HW2SW_MACID(ar->pdev->pdev_id);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_PKTLOG_DISABLE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_PDEV_PKTLOG_ENABLE_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_send_twt_enable_cmd(काष्ठा ath11k *ar, u32 pdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_twt_enable_params_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_twt_enable_params_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_TWT_ENABLE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->pdev_id = pdev_id;
	cmd->sta_cong_समयr_ms = ATH11K_TWT_DEF_STA_CONG_TIMER_MS;
	cmd->शेष_slot_size = ATH11K_TWT_DEF_DEFAULT_SLOT_SIZE;
	cmd->congestion_thresh_setup = ATH11K_TWT_DEF_CONGESTION_THRESH_SETUP;
	cmd->congestion_thresh_tearकरोwn =
		ATH11K_TWT_DEF_CONGESTION_THRESH_TEARDOWN;
	cmd->congestion_thresh_critical =
		ATH11K_TWT_DEF_CONGESTION_THRESH_CRITICAL;
	cmd->पूर्णांकerference_thresh_tearकरोwn =
		ATH11K_TWT_DEF_INTERFERENCE_THRESH_TEARDOWN;
	cmd->पूर्णांकerference_thresh_setup =
		ATH11K_TWT_DEF_INTERFERENCE_THRESH_SETUP;
	cmd->min_no_sta_setup = ATH11K_TWT_DEF_MIN_NO_STA_SETUP;
	cmd->min_no_sta_tearकरोwn = ATH11K_TWT_DEF_MIN_NO_STA_TEARDOWN;
	cmd->no_of_bcast_mcast_slots = ATH11K_TWT_DEF_NO_OF_BCAST_MCAST_SLOTS;
	cmd->min_no_twt_slots = ATH11K_TWT_DEF_MIN_NO_TWT_SLOTS;
	cmd->max_no_sta_twt = ATH11K_TWT_DEF_MAX_NO_STA_TWT;
	cmd->mode_check_पूर्णांकerval = ATH11K_TWT_DEF_MODE_CHECK_INTERVAL;
	cmd->add_sta_slot_पूर्णांकerval = ATH11K_TWT_DEF_ADD_STA_SLOT_INTERVAL;
	cmd->हटाओ_sta_slot_पूर्णांकerval =
		ATH11K_TWT_DEF_REMOVE_STA_SLOT_INTERVAL;
	/* TODO add MBSSID support */
	cmd->mbss_support = 0;

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_TWT_ENABLE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab, "Failed to send WMI_TWT_ENABLE_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_send_twt_disable_cmd(काष्ठा ath11k *ar, u32 pdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_twt_disable_params_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_twt_disable_params_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_TWT_DISABLE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->pdev_id = pdev_id;

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_TWT_DISABLE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab, "Failed to send WMI_TWT_DISABLE_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_send_obss_spr_cmd(काष्ठा ath11k *ar, u32 vdev_id,
			     काष्ठा ieee80211_he_obss_pd *he_obss_pd)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_obss_spatial_reuse_params_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_obss_spatial_reuse_params_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_OBSS_SPATIAL_REUSE_SET_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->enable = he_obss_pd->enable;
	cmd->obss_min = he_obss_pd->min_offset;
	cmd->obss_max = he_obss_pd->max_offset;

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_OBSS_PD_SPATIAL_REUSE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab,
			    "Failed to send WMI_PDEV_OBSS_PD_SPATIAL_REUSE_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_pdev_set_srg_bss_color_biपंचांगap(काष्ठा ath11k *ar, u32 *biपंचांगap)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_PDEV_SRG_BSS_COLOR_BITMAP_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->pdev_id = ar->pdev->pdev_id;
	स_नकल(cmd->biपंचांगap, biपंचांगap, माप(cmd->biपंचांगap));

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "obss pd pdev_id %d bss color bitmap %08x %08x\n",
		   cmd->pdev_id, cmd->biपंचांगap[0], cmd->biपंचांगap[1]);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_SET_SRG_BSS_COLOR_BITMAP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab,
			    "failed to send WMI_PDEV_SET_SRG_BSS_COLOR_BITMAP_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_pdev_set_srg_patial_bssid_biपंचांगap(काष्ठा ath11k *ar, u32 *biपंचांगap)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG,
			   WMI_TAG_PDEV_SRG_PARTIAL_BSSID_BITMAP_CMD) |
		FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->pdev_id = ar->pdev->pdev_id;
	स_नकल(cmd->biपंचांगap, biपंचांगap, माप(cmd->biपंचांगap));

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "obss pd pdev_id %d partial bssid bitmap %08x %08x\n",
		   cmd->pdev_id, cmd->biपंचांगap[0], cmd->biपंचांगap[1]);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_SET_SRG_PARTIAL_BSSID_BITMAP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab,
			    "failed to send WMI_PDEV_SET_SRG_PARTIAL_BSSID_BITMAP_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_pdev_srg_obss_color_enable_biपंचांगap(काष्ठा ath11k *ar, u32 *biपंचांगap)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG,
			   WMI_TAG_PDEV_SRG_OBSS_COLOR_ENABLE_BITMAP_CMD) |
		FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->pdev_id = ar->pdev->pdev_id;
	स_नकल(cmd->biपंचांगap, biपंचांगap, माप(cmd->biपंचांगap));

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "obss pd srg pdev_id %d bss color enable bitmap %08x %08x\n",
		   cmd->pdev_id, cmd->biपंचांगap[0], cmd->biपंचांगap[1]);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_SET_SRG_OBSS_COLOR_ENABLE_BITMAP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab,
			    "failed to send WMI_PDEV_SET_SRG_OBSS_COLOR_ENABLE_BITMAP_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_pdev_srg_obss_bssid_enable_biपंचांगap(काष्ठा ath11k *ar, u32 *biपंचांगap)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG,
			   WMI_TAG_PDEV_SRG_OBSS_BSSID_ENABLE_BITMAP_CMD) |
		FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->pdev_id = ar->pdev->pdev_id;
	स_नकल(cmd->biपंचांगap, biपंचांगap, माप(cmd->biपंचांगap));

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "obss pd srg pdev_id %d bssid enable bitmap %08x %08x\n",
		   cmd->pdev_id, cmd->biपंचांगap[0], cmd->biपंचांगap[1]);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_SET_SRG_OBSS_BSSID_ENABLE_BITMAP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab,
			    "failed to send WMI_PDEV_SET_SRG_OBSS_BSSID_ENABLE_BITMAP_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_pdev_non_srg_obss_color_enable_biपंचांगap(काष्ठा ath11k *ar, u32 *biपंचांगap)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG,
			   WMI_TAG_PDEV_NON_SRG_OBSS_COLOR_ENABLE_BITMAP_CMD) |
		FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->pdev_id = ar->pdev->pdev_id;
	स_नकल(cmd->biपंचांगap, biपंचांगap, माप(cmd->biपंचांगap));

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "obss pd non_srg pdev_id %d bss color enable bitmap %08x %08x\n",
		   cmd->pdev_id, cmd->biपंचांगap[0], cmd->biपंचांगap[1]);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_SET_NON_SRG_OBSS_COLOR_ENABLE_BITMAP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab,
			    "failed to send WMI_PDEV_SET_NON_SRG_OBSS_COLOR_ENABLE_BITMAP_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_pdev_non_srg_obss_bssid_enable_biपंचांगap(काष्ठा ath11k *ar, u32 *biपंचांगap)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_obss_pd_biपंचांगap_cmd *)skb->data;
	cmd->tlv_header =
		FIELD_PREP(WMI_TLV_TAG,
			   WMI_TAG_PDEV_NON_SRG_OBSS_BSSID_ENABLE_BITMAP_CMD) |
		FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->pdev_id = ar->pdev->pdev_id;
	स_नकल(cmd->biपंचांगap, biपंचांगap, माप(cmd->biपंचांगap));

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "obss pd non_srg pdev_id %d bssid enable bitmap %08x %08x\n",
		   cmd->pdev_id, cmd->biपंचांगap[0], cmd->biपंचांगap[1]);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_PDEV_SET_NON_SRG_OBSS_BSSID_ENABLE_BITMAP_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab,
			    "failed to send WMI_PDEV_SET_NON_SRG_OBSS_BSSID_ENABLE_BITMAP_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
ath11k_wmi_send_obss_color_collision_cfg_cmd(काष्ठा ath11k *ar, u32 vdev_id,
					     u8 bss_color, u32 period,
					     bool enable)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_obss_color_collision_cfg_params_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_obss_color_collision_cfg_params_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_OBSS_COLOR_COLLISION_DET_CONFIG) |
			  FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->evt_type = enable ? ATH11K_OBSS_COLOR_COLLISION_DETECTION :
				 ATH11K_OBSS_COLOR_COLLISION_DETECTION_DISABLE;
	cmd->current_bss_color = bss_color;
	cmd->detection_period_ms = period;
	cmd->scan_period_ms = ATH11K_BSS_COLOR_COLLISION_SCAN_PERIOD_MS;
	cmd->मुक्त_slot_expiry_समय_ms = 0;
	cmd->flags = 0;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "wmi_send_obss_color_collision_cfg id %d type %d bss_color %d detect_period %d scan_period %d\n",
		   cmd->vdev_id, cmd->evt_type, cmd->current_bss_color,
		   cmd->detection_period_ms, cmd->scan_period_ms);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_OBSS_COLOR_COLLISION_DET_CONFIG_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab, "Failed to send WMI_OBSS_COLOR_COLLISION_DET_CONFIG_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_send_bss_color_change_enable_cmd(काष्ठा ath11k *ar, u32 vdev_id,
						bool enable)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा wmi_bss_color_change_enable_params_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_bss_color_change_enable_params_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_BSS_COLOR_CHANGE_ENABLE) |
			  FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->enable = enable ? 1 : 0;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "wmi_send_bss_color_change_enable id %d enable %d\n",
		   cmd->vdev_id, cmd->enable);

	ret = ath11k_wmi_cmd_send(wmi, skb,
				  WMI_BSS_COLOR_CHANGE_ENABLE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab, "Failed to send WMI_BSS_COLOR_CHANGE_ENABLE_CMDID");
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_fils_discovery_पंचांगpl(काष्ठा ath11k *ar, u32 vdev_id,
				   काष्ठा sk_buff *पंचांगpl)
अणु
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	पूर्णांक ret, len;
	माप_प्रकार aligned_len;
	काष्ठा wmi_fils_discovery_पंचांगpl_cmd *cmd;

	aligned_len = roundup(पंचांगpl->len, 4);
	len = माप(*cmd) + TLV_HDR_SIZE + aligned_len;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev %i set FILS discovery template\n", vdev_id);

	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_fils_discovery_पंचांगpl_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_FILS_DISCOVERY_TMPL_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->buf_len = पंचांगpl->len;
	ptr = skb->data + माप(*cmd);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_BYTE) |
		      FIELD_PREP(WMI_TLV_LEN, aligned_len);
	स_नकल(tlv->value, पंचांगpl->data, पंचांगpl->len);

	ret = ath11k_wmi_cmd_send(ar->wmi, skb, WMI_FILS_DISCOVERY_TMPL_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "WMI vdev %i failed to send FILS discovery template command\n",
			    vdev_id);
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_probe_resp_पंचांगpl(काष्ठा ath11k *ar, u32 vdev_id,
			       काष्ठा sk_buff *पंचांगpl)
अणु
	काष्ठा wmi_probe_पंचांगpl_cmd *cmd;
	काष्ठा wmi_bcn_prb_info *probe_info;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	पूर्णांक ret, len;
	माप_प्रकार aligned_len = roundup(पंचांगpl->len, 4);

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev %i set probe response template\n", vdev_id);

	len = माप(*cmd) + माप(*probe_info) + TLV_HDR_SIZE + aligned_len;

	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_probe_पंचांगpl_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PRB_TMPL_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->buf_len = पंचांगpl->len;

	ptr = skb->data + माप(*cmd);

	probe_info = ptr;
	len = माप(*probe_info);
	probe_info->tlv_header = FIELD_PREP(WMI_TLV_TAG,
					    WMI_TAG_BCN_PRB_INFO) |
				 FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	probe_info->caps = 0;
	probe_info->erp = 0;

	ptr += माप(*probe_info);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_BYTE) |
		      FIELD_PREP(WMI_TLV_LEN, aligned_len);
	स_नकल(tlv->value, पंचांगpl->data, पंचांगpl->len);

	ret = ath11k_wmi_cmd_send(ar->wmi, skb, WMI_PRB_TMPL_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "WMI vdev %i failed to send probe response template command\n",
			    vdev_id);
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_fils_discovery(काष्ठा ath11k *ar, u32 vdev_id, u32 पूर्णांकerval,
			      bool unsol_bcast_probe_resp_enabled)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret, len;
	काष्ठा wmi_fils_discovery_cmd *cmd;

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI vdev %i set %s interval to %u TU\n",
		   vdev_id, unsol_bcast_probe_resp_enabled ?
		   "unsolicited broadcast probe response" : "FILS discovery",
		   पूर्णांकerval);

	len = माप(*cmd);
	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_fils_discovery_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ENABLE_FILS_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, len - TLV_HDR_SIZE);
	cmd->vdev_id = vdev_id;
	cmd->पूर्णांकerval = पूर्णांकerval;
	cmd->config = unsol_bcast_probe_resp_enabled;

	ret = ath11k_wmi_cmd_send(ar->wmi, skb, WMI_ENABLE_FILS_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "WMI vdev %i failed to send FILS discovery enable/disable command\n",
			    vdev_id);
		dev_kमुक्त_skb(skb);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
ath11k_fill_band_to_mac_param(काष्ठा ath11k_base  *soc,
			      काष्ठा wmi_host_pdev_band_to_mac *band_to_mac)
अणु
	u8 i;
	काष्ठा ath11k_hal_reg_capabilities_ext *hal_reg_cap;
	काष्ठा ath11k_pdev *pdev;

	क्रम (i = 0; i < soc->num_radios; i++) अणु
		pdev = &soc->pdevs[i];
		hal_reg_cap = &soc->hal_reg_cap[i];
		band_to_mac[i].pdev_id = pdev->pdev_id;

		चयन (pdev->cap.supported_bands) अणु
		हाल WMI_HOST_WLAN_2G_5G_CAP:
			band_to_mac[i].start_freq = hal_reg_cap->low_2ghz_chan;
			band_to_mac[i].end_freq = hal_reg_cap->high_5ghz_chan;
			अवरोध;
		हाल WMI_HOST_WLAN_2G_CAP:
			band_to_mac[i].start_freq = hal_reg_cap->low_2ghz_chan;
			band_to_mac[i].end_freq = hal_reg_cap->high_2ghz_chan;
			अवरोध;
		हाल WMI_HOST_WLAN_5G_CAP:
			band_to_mac[i].start_freq = hal_reg_cap->low_5ghz_chan;
			band_to_mac[i].end_freq = hal_reg_cap->high_5ghz_chan;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ath11k_wmi_copy_resource_config(काष्ठा wmi_resource_config *wmi_cfg,
				काष्ठा target_resource_config *tg_cfg)
अणु
	wmi_cfg->num_vdevs = tg_cfg->num_vdevs;
	wmi_cfg->num_peers = tg_cfg->num_peers;
	wmi_cfg->num_offload_peers = tg_cfg->num_offload_peers;
	wmi_cfg->num_offload_reorder_buffs = tg_cfg->num_offload_reorder_buffs;
	wmi_cfg->num_peer_keys = tg_cfg->num_peer_keys;
	wmi_cfg->num_tids = tg_cfg->num_tids;
	wmi_cfg->ast_skid_limit = tg_cfg->ast_skid_limit;
	wmi_cfg->tx_chain_mask = tg_cfg->tx_chain_mask;
	wmi_cfg->rx_chain_mask = tg_cfg->rx_chain_mask;
	wmi_cfg->rx_समयout_pri[0] = tg_cfg->rx_समयout_pri[0];
	wmi_cfg->rx_समयout_pri[1] = tg_cfg->rx_समयout_pri[1];
	wmi_cfg->rx_समयout_pri[2] = tg_cfg->rx_समयout_pri[2];
	wmi_cfg->rx_समयout_pri[3] = tg_cfg->rx_समयout_pri[3];
	wmi_cfg->rx_decap_mode = tg_cfg->rx_decap_mode;
	wmi_cfg->scan_max_pending_req = tg_cfg->scan_max_pending_req;
	wmi_cfg->bmiss_offload_max_vdev = tg_cfg->bmiss_offload_max_vdev;
	wmi_cfg->roam_offload_max_vdev = tg_cfg->roam_offload_max_vdev;
	wmi_cfg->roam_offload_max_ap_profiles =
		tg_cfg->roam_offload_max_ap_profiles;
	wmi_cfg->num_mcast_groups = tg_cfg->num_mcast_groups;
	wmi_cfg->num_mcast_table_elems = tg_cfg->num_mcast_table_elems;
	wmi_cfg->mcast2ucast_mode = tg_cfg->mcast2ucast_mode;
	wmi_cfg->tx_dbg_log_size = tg_cfg->tx_dbg_log_size;
	wmi_cfg->num_wds_entries = tg_cfg->num_wds_entries;
	wmi_cfg->dma_burst_size = tg_cfg->dma_burst_size;
	wmi_cfg->mac_aggr_delim = tg_cfg->mac_aggr_delim;
	wmi_cfg->rx_skip_defrag_समयout_dup_detection_check =
		tg_cfg->rx_skip_defrag_समयout_dup_detection_check;
	wmi_cfg->vow_config = tg_cfg->vow_config;
	wmi_cfg->gtk_offload_max_vdev = tg_cfg->gtk_offload_max_vdev;
	wmi_cfg->num_msdu_desc = tg_cfg->num_msdu_desc;
	wmi_cfg->max_frag_entries = tg_cfg->max_frag_entries;
	wmi_cfg->num_tdls_vdevs = tg_cfg->num_tdls_vdevs;
	wmi_cfg->num_tdls_conn_table_entries =
		tg_cfg->num_tdls_conn_table_entries;
	wmi_cfg->beacon_tx_offload_max_vdev =
		tg_cfg->beacon_tx_offload_max_vdev;
	wmi_cfg->num_multicast_filter_entries =
		tg_cfg->num_multicast_filter_entries;
	wmi_cfg->num_wow_filters = tg_cfg->num_wow_filters;
	wmi_cfg->num_keep_alive_pattern = tg_cfg->num_keep_alive_pattern;
	wmi_cfg->keep_alive_pattern_size = tg_cfg->keep_alive_pattern_size;
	wmi_cfg->max_tdls_concurrent_sleep_sta =
		tg_cfg->max_tdls_concurrent_sleep_sta;
	wmi_cfg->max_tdls_concurrent_buffer_sta =
		tg_cfg->max_tdls_concurrent_buffer_sta;
	wmi_cfg->wmi_send_separate = tg_cfg->wmi_send_separate;
	wmi_cfg->num_ocb_vdevs = tg_cfg->num_ocb_vdevs;
	wmi_cfg->num_ocb_channels = tg_cfg->num_ocb_channels;
	wmi_cfg->num_ocb_schedules = tg_cfg->num_ocb_schedules;
	wmi_cfg->bpf_inकाष्ठाion_size = tg_cfg->bpf_inकाष्ठाion_size;
	wmi_cfg->max_bssid_rx_filters = tg_cfg->max_bssid_rx_filters;
	wmi_cfg->use_pdev_id = tg_cfg->use_pdev_id;
	wmi_cfg->flag1 = tg_cfg->atf_config;
	wmi_cfg->peer_map_unmap_v2_support = tg_cfg->peer_map_unmap_v2_support;
	wmi_cfg->sched_params = tg_cfg->sched_params;
	wmi_cfg->twt_ap_pdev_count = tg_cfg->twt_ap_pdev_count;
	wmi_cfg->twt_ap_sta_count = tg_cfg->twt_ap_sta_count;
पूर्ण

अटल पूर्णांक ath11k_init_cmd_send(काष्ठा ath11k_pdev_wmi *wmi,
				काष्ठा wmi_init_cmd_param *param)
अणु
	काष्ठा ath11k_base *ab = wmi->wmi_ab->ab;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_init_cmd *cmd;
	काष्ठा wmi_resource_config *cfg;
	काष्ठा wmi_pdev_set_hw_mode_cmd_param *hw_mode;
	काष्ठा wmi_pdev_band_to_mac *band_to_mac;
	काष्ठा wlan_host_mem_chunk *host_mem_chunks;
	काष्ठा wmi_tlv *tlv;
	माप_प्रकार ret, len;
	व्योम *ptr;
	u32 hw_mode_len = 0;
	u16 idx;

	अगर (param->hw_mode_id != WMI_HOST_HW_MODE_MAX)
		hw_mode_len = माप(*hw_mode) + TLV_HDR_SIZE +
			      (param->num_band_to_mac * माप(*band_to_mac));

	len = माप(*cmd) + TLV_HDR_SIZE + माप(*cfg) + hw_mode_len +
	      (param->num_mem_chunks ? (माप(*host_mem_chunks) * WMI_MAX_MEM_REQS) : 0);

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_init_cmd *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_INIT_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	ptr = skb->data + माप(*cmd);
	cfg = ptr;

	ath11k_wmi_copy_resource_config(cfg, param->res_cfg);

	cfg->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_RESOURCE_CONFIG) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cfg) - TLV_HDR_SIZE);

	ptr += माप(*cfg);
	host_mem_chunks = ptr + TLV_HDR_SIZE;
	len = माप(काष्ठा wlan_host_mem_chunk);

	क्रम (idx = 0; idx < param->num_mem_chunks; ++idx) अणु
		host_mem_chunks[idx].tlv_header =
				FIELD_PREP(WMI_TLV_TAG,
					   WMI_TAG_WLAN_HOST_MEMORY_CHUNK) |
				FIELD_PREP(WMI_TLV_LEN, len);

		host_mem_chunks[idx].ptr = param->mem_chunks[idx].paddr;
		host_mem_chunks[idx].size = param->mem_chunks[idx].len;
		host_mem_chunks[idx].req_id = param->mem_chunks[idx].req_id;

		ath11k_dbg(ab, ATH11K_DBG_WMI,
			   "WMI host mem chunk req_id %d paddr 0x%llx len %d\n",
			   param->mem_chunks[idx].req_id,
			   (u64)param->mem_chunks[idx].paddr,
			   param->mem_chunks[idx].len);
	पूर्ण
	cmd->num_host_mem_chunks = param->num_mem_chunks;
	len = माप(काष्ठा wlan_host_mem_chunk) * param->num_mem_chunks;

	/* num_mem_chunks is zero */
	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_STRUCT) |
		      FIELD_PREP(WMI_TLV_LEN, len);
	ptr += TLV_HDR_SIZE + len;

	अगर (param->hw_mode_id != WMI_HOST_HW_MODE_MAX) अणु
		hw_mode = (काष्ठा wmi_pdev_set_hw_mode_cmd_param *)ptr;
		hw_mode->tlv_header = FIELD_PREP(WMI_TLV_TAG,
						 WMI_TAG_PDEV_SET_HW_MODE_CMD) |
				      FIELD_PREP(WMI_TLV_LEN,
						 माप(*hw_mode) - TLV_HDR_SIZE);

		hw_mode->hw_mode_index = param->hw_mode_id;
		hw_mode->num_band_to_mac = param->num_band_to_mac;

		ptr += माप(*hw_mode);

		len = param->num_band_to_mac * माप(*band_to_mac);
		tlv = ptr;
		tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_STRUCT) |
			      FIELD_PREP(WMI_TLV_LEN, len);

		ptr += TLV_HDR_SIZE;
		len = माप(*band_to_mac);

		क्रम (idx = 0; idx < param->num_band_to_mac; idx++) अणु
			band_to_mac = (व्योम *)ptr;

			band_to_mac->tlv_header = FIELD_PREP(WMI_TLV_TAG,
							     WMI_TAG_PDEV_BAND_TO_MAC) |
						  FIELD_PREP(WMI_TLV_LEN,
							     len - TLV_HDR_SIZE);
			band_to_mac->pdev_id = param->band_to_mac[idx].pdev_id;
			band_to_mac->start_freq =
				param->band_to_mac[idx].start_freq;
			band_to_mac->end_freq =
				param->band_to_mac[idx].end_freq;
			ptr += माप(*band_to_mac);
		पूर्ण
	पूर्ण

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_INIT_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to send WMI_INIT_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_lro_cfg(काष्ठा ath11k *ar,
			    पूर्णांक pdev_id)
अणु
	काष्ठा ath11k_wmi_pdev_lro_config_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा ath11k_wmi_pdev_lro_config_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_LRO_INFO_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	get_अक्रमom_bytes(cmd->th_4, माप(uपूर्णांक32_t) * ATH11K_IPV4_TH_SEED_SIZE);
	get_अक्रमom_bytes(cmd->th_6, माप(uपूर्णांक32_t) * ATH11K_IPV6_TH_SEED_SIZE);

	cmd->pdev_id = pdev_id;

	ret = ath11k_wmi_cmd_send(ar->wmi, skb, WMI_LRO_CONFIG_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send lro cfg req wmi cmd\n");
		जाओ err;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI lro cfg cmd pdev_id 0x%x\n", pdev_id);
	वापस 0;
err:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_रुको_क्रम_service_पढ़ोy(काष्ठा ath11k_base *ab)
अणु
	अचिन्हित दीर्घ समय_left;

	समय_left = रुको_क्रम_completion_समयout(&ab->wmi_ab.service_पढ़ोy,
						WMI_SERVICE_READY_TIMEOUT_HZ);
	अगर (!समय_left)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

पूर्णांक ath11k_wmi_रुको_क्रम_unअगरied_पढ़ोy(काष्ठा ath11k_base *ab)
अणु
	अचिन्हित दीर्घ समय_left;

	समय_left = रुको_क्रम_completion_समयout(&ab->wmi_ab.unअगरied_पढ़ोy,
						WMI_SERVICE_READY_TIMEOUT_HZ);
	अगर (!समय_left)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

पूर्णांक ath11k_wmi_set_hw_mode(काष्ठा ath11k_base *ab,
			   क्रमागत wmi_host_hw_mode_config_type mode)
अणु
	काष्ठा wmi_pdev_set_hw_mode_cmd_param *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा ath11k_wmi_base *wmi_ab = &ab->wmi_ab;
	पूर्णांक len;
	पूर्णांक ret;

	len = माप(*cmd);

	skb = ath11k_wmi_alloc_skb(wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_pdev_set_hw_mode_cmd_param *)skb->data;

	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_PDEV_SET_HW_MODE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->pdev_id = WMI_PDEV_ID_SOC;
	cmd->hw_mode_index = mode;

	ret = ath11k_wmi_cmd_send(&wmi_ab->wmi[0], skb, WMI_PDEV_SET_HW_MODE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to send WMI_PDEV_SET_HW_MODE_CMDID\n");
		dev_kमुक्त_skb(skb);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_cmd_init(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k_wmi_base *wmi_sc = &ab->wmi_ab;
	काष्ठा wmi_init_cmd_param init_param;
	काष्ठा target_resource_config  config;

	स_रखो(&init_param, 0, माप(init_param));
	स_रखो(&config, 0, माप(config));

	ab->hw_params.hw_ops->wmi_init_config(ab, &config);

	स_नकल(&wmi_sc->wlan_resource_config, &config, माप(config));

	init_param.res_cfg = &wmi_sc->wlan_resource_config;
	init_param.num_mem_chunks = wmi_sc->num_mem_chunks;
	init_param.hw_mode_id = wmi_sc->preferred_hw_mode;
	init_param.mem_chunks = wmi_sc->mem_chunks;

	अगर (ab->hw_params.single_pdev_only)
		init_param.hw_mode_id = WMI_HOST_HW_MODE_MAX;

	init_param.num_band_to_mac = ab->num_radios;
	ath11k_fill_band_to_mac_param(ab, init_param.band_to_mac);

	वापस ath11k_init_cmd_send(&wmi_sc->wmi[0], &init_param);
पूर्ण

पूर्णांक ath11k_wmi_vdev_spectral_conf(काष्ठा ath11k *ar,
				  काष्ठा ath11k_wmi_vdev_spectral_conf_param *param)
अणु
	काष्ठा ath11k_wmi_vdev_spectral_conf_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा ath11k_wmi_vdev_spectral_conf_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_VDEV_SPECTRAL_CONFIGURE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	स_नकल(&cmd->param, param, माप(*param));

	ret = ath11k_wmi_cmd_send(ar->wmi, skb,
				  WMI_VDEV_SPECTRAL_SCAN_CONFIGURE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send spectral scan config wmi cmd\n");
		जाओ err;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI spectral scan config cmd vdev_id 0x%x\n",
		   param->vdev_id);

	वापस 0;
err:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_vdev_spectral_enable(काष्ठा ath11k *ar, u32 vdev_id,
				    u32 trigger, u32 enable)
अणु
	काष्ठा ath11k_wmi_vdev_spectral_enable_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा ath11k_wmi_vdev_spectral_enable_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_VDEV_SPECTRAL_ENABLE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = vdev_id;
	cmd->trigger_cmd = trigger;
	cmd->enable_cmd = enable;

	ret = ath11k_wmi_cmd_send(ar->wmi, skb,
				  WMI_VDEV_SPECTRAL_SCAN_ENABLE_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send spectral enable wmi cmd\n");
		जाओ err;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI spectral enable cmd vdev id 0x%x\n",
		   vdev_id);

	वापस 0;
err:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_pdev_dma_ring_cfg(काष्ठा ath11k *ar,
				 काष्ठा ath11k_wmi_pdev_dma_ring_cfg_req_cmd *param)
अणु
	काष्ठा ath11k_wmi_pdev_dma_ring_cfg_req_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, माप(*cmd));
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा ath11k_wmi_pdev_dma_ring_cfg_req_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_DMA_RING_CFG_REQ) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->pdev_id		= param->pdev_id;
	cmd->module_id		= param->module_id;
	cmd->base_paddr_lo	= param->base_paddr_lo;
	cmd->base_paddr_hi	= param->base_paddr_hi;
	cmd->head_idx_paddr_lo	= param->head_idx_paddr_lo;
	cmd->head_idx_paddr_hi	= param->head_idx_paddr_hi;
	cmd->tail_idx_paddr_lo	= param->tail_idx_paddr_lo;
	cmd->tail_idx_paddr_hi	= param->tail_idx_paddr_hi;
	cmd->num_elems		= param->num_elems;
	cmd->buf_size		= param->buf_size;
	cmd->num_resp_per_event	= param->num_resp_per_event;
	cmd->event_समयout_ms	= param->event_समयout_ms;

	ret = ath11k_wmi_cmd_send(ar->wmi, skb,
				  WMI_PDEV_DMA_RING_CFG_REQ_CMDID);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to send dma ring cfg req wmi cmd\n");
		जाओ err;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI DMA ring cfg req cmd pdev_id 0x%x\n",
		   param->pdev_id);

	वापस 0;
err:
	dev_kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_dma_buf_entry_parse(काष्ठा ath11k_base *soc,
					      u16 tag, u16 len,
					      स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_dma_buf_release_parse *parse = data;

	अगर (tag != WMI_TAG_DMA_BUF_RELEASE_ENTRY)
		वापस -EPROTO;

	अगर (parse->num_buf_entry >= parse->fixed.num_buf_release_entry)
		वापस -ENOBUFS;

	parse->num_buf_entry++;
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_dma_buf_meta_parse(काष्ठा ath11k_base *soc,
					     u16 tag, u16 len,
					     स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_dma_buf_release_parse *parse = data;

	अगर (tag != WMI_TAG_DMA_BUF_RELEASE_SPECTRAL_META_DATA)
		वापस -EPROTO;

	अगर (parse->num_meta >= parse->fixed.num_meta_data_entry)
		वापस -ENOBUFS;

	parse->num_meta++;
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_dma_buf_parse(काष्ठा ath11k_base *ab,
					u16 tag, u16 len,
					स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_dma_buf_release_parse *parse = data;
	पूर्णांक ret;

	चयन (tag) अणु
	हाल WMI_TAG_DMA_BUF_RELEASE:
		स_नकल(&parse->fixed, ptr,
		       माप(काष्ठा ath11k_wmi_dma_buf_release_fixed_param));
		parse->fixed.pdev_id = DP_HW2SW_MACID(parse->fixed.pdev_id);
		अवरोध;
	हाल WMI_TAG_ARRAY_STRUCT:
		अगर (!parse->buf_entry_करोne) अणु
			parse->num_buf_entry = 0;
			parse->buf_entry = (काष्ठा wmi_dma_buf_release_entry *)ptr;

			ret = ath11k_wmi_tlv_iter(ab, ptr, len,
						  ath11k_wmi_tlv_dma_buf_entry_parse,
						  parse);
			अगर (ret) अणु
				ath11k_warn(ab, "failed to parse dma buf entry tlv %d\n",
					    ret);
				वापस ret;
			पूर्ण

			parse->buf_entry_करोne = true;
		पूर्ण अन्यथा अगर (!parse->meta_data_करोne) अणु
			parse->num_meta = 0;
			parse->meta_data = (काष्ठा wmi_dma_buf_release_meta_data *)ptr;

			ret = ath11k_wmi_tlv_iter(ab, ptr, len,
						  ath11k_wmi_tlv_dma_buf_meta_parse,
						  parse);
			अगर (ret) अणु
				ath11k_warn(ab, "failed to parse dma buf meta tlv %d\n",
					    ret);
				वापस ret;
			पूर्ण

			parse->meta_data_करोne = true;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ath11k_wmi_pdev_dma_ring_buf_release_event(काष्ठा ath11k_base *ab,
						       काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_tlv_dma_buf_release_parse parse = अणु पूर्ण;
	काष्ठा ath11k_dbring_buf_release_event param;
	पूर्णांक ret;

	ret = ath11k_wmi_tlv_iter(ab, skb->data, skb->len,
				  ath11k_wmi_tlv_dma_buf_parse,
				  &parse);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to parse dma buf release tlv %d\n", ret);
		वापस;
	पूर्ण

	param.fixed		= parse.fixed;
	param.buf_entry		= parse.buf_entry;
	param.num_buf_entry	= parse.num_buf_entry;
	param.meta_data		= parse.meta_data;
	param.num_meta		= parse.num_meta;

	ret = ath11k_dbring_buffer_release_event(ab, &param);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to handle dma buf release event %d\n", ret);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_hw_mode_caps_parse(काष्ठा ath11k_base *soc,
					     u16 tag, u16 len,
					     स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_svc_rdy_ext_parse *svc_rdy_ext = data;
	काष्ठा wmi_hw_mode_capabilities *hw_mode_cap;
	u32 phy_map = 0;

	अगर (tag != WMI_TAG_HW_MODE_CAPABILITIES)
		वापस -EPROTO;

	अगर (svc_rdy_ext->n_hw_mode_caps >= svc_rdy_ext->param.num_hw_modes)
		वापस -ENOBUFS;

	hw_mode_cap = container_of(ptr, काष्ठा wmi_hw_mode_capabilities,
				   hw_mode_id);
	svc_rdy_ext->n_hw_mode_caps++;

	phy_map = hw_mode_cap->phy_id_map;
	जबतक (phy_map) अणु
		svc_rdy_ext->tot_phy_id++;
		phy_map = phy_map >> 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_hw_mode_caps(काष्ठा ath11k_base *soc,
				       u16 len, स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_svc_rdy_ext_parse *svc_rdy_ext = data;
	काष्ठा wmi_hw_mode_capabilities *hw_mode_caps;
	क्रमागत wmi_host_hw_mode_config_type mode, pref;
	u32 i;
	पूर्णांक ret;

	svc_rdy_ext->n_hw_mode_caps = 0;
	svc_rdy_ext->hw_mode_caps = (काष्ठा wmi_hw_mode_capabilities *)ptr;

	ret = ath11k_wmi_tlv_iter(soc, ptr, len,
				  ath11k_wmi_tlv_hw_mode_caps_parse,
				  svc_rdy_ext);
	अगर (ret) अणु
		ath11k_warn(soc, "failed to parse tlv %d\n", ret);
		वापस ret;
	पूर्ण

	i = 0;
	जबतक (i < svc_rdy_ext->n_hw_mode_caps) अणु
		hw_mode_caps = &svc_rdy_ext->hw_mode_caps[i];
		mode = hw_mode_caps->hw_mode_id;
		pref = soc->wmi_ab.preferred_hw_mode;

		अगर (ath11k_hw_mode_pri_map[mode] < ath11k_hw_mode_pri_map[pref]) अणु
			svc_rdy_ext->pref_hw_mode_caps = *hw_mode_caps;
			soc->wmi_ab.preferred_hw_mode = mode;
		पूर्ण
		i++;
	पूर्ण

	ath11k_dbg(soc, ATH11K_DBG_WMI, "preferred_hw_mode:%d\n",
		   soc->wmi_ab.preferred_hw_mode);
	अगर (soc->wmi_ab.preferred_hw_mode == WMI_HOST_HW_MODE_MAX)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_mac_phy_caps_parse(काष्ठा ath11k_base *soc,
					     u16 tag, u16 len,
					     स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_svc_rdy_ext_parse *svc_rdy_ext = data;

	अगर (tag != WMI_TAG_MAC_PHY_CAPABILITIES)
		वापस -EPROTO;

	अगर (svc_rdy_ext->n_mac_phy_caps >= svc_rdy_ext->tot_phy_id)
		वापस -ENOBUFS;

	len = min_t(u16, len, माप(काष्ठा wmi_mac_phy_capabilities));
	अगर (!svc_rdy_ext->n_mac_phy_caps) अणु
		svc_rdy_ext->mac_phy_caps = kzalloc((svc_rdy_ext->tot_phy_id) * len,
						    GFP_ATOMIC);
		अगर (!svc_rdy_ext->mac_phy_caps)
			वापस -ENOMEM;
	पूर्ण

	स_नकल(svc_rdy_ext->mac_phy_caps + svc_rdy_ext->n_mac_phy_caps, ptr, len);
	svc_rdy_ext->n_mac_phy_caps++;
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_ext_hal_reg_caps_parse(काष्ठा ath11k_base *soc,
						 u16 tag, u16 len,
						 स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_svc_rdy_ext_parse *svc_rdy_ext = data;

	अगर (tag != WMI_TAG_HAL_REG_CAPABILITIES_EXT)
		वापस -EPROTO;

	अगर (svc_rdy_ext->n_ext_hal_reg_caps >= svc_rdy_ext->param.num_phy)
		वापस -ENOBUFS;

	svc_rdy_ext->n_ext_hal_reg_caps++;
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_ext_hal_reg_caps(काष्ठा ath11k_base *soc,
					   u16 len, स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा ath11k_pdev_wmi *wmi_handle = &soc->wmi_ab.wmi[0];
	काष्ठा wmi_tlv_svc_rdy_ext_parse *svc_rdy_ext = data;
	काष्ठा ath11k_hal_reg_capabilities_ext reg_cap;
	पूर्णांक ret;
	u32 i;

	svc_rdy_ext->n_ext_hal_reg_caps = 0;
	svc_rdy_ext->ext_hal_reg_caps = (काष्ठा wmi_hal_reg_capabilities_ext *)ptr;
	ret = ath11k_wmi_tlv_iter(soc, ptr, len,
				  ath11k_wmi_tlv_ext_hal_reg_caps_parse,
				  svc_rdy_ext);
	अगर (ret) अणु
		ath11k_warn(soc, "failed to parse tlv %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < svc_rdy_ext->param.num_phy; i++) अणु
		ret = ath11k_pull_reg_cap_svc_rdy_ext(wmi_handle,
						      svc_rdy_ext->soc_hal_reg_caps,
						      svc_rdy_ext->ext_hal_reg_caps, i,
						      &reg_cap);
		अगर (ret) अणु
			ath11k_warn(soc, "failed to extract reg cap %d\n", i);
			वापस ret;
		पूर्ण

		स_नकल(&soc->hal_reg_cap[reg_cap.phy_id],
		       &reg_cap, माप(reg_cap));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_ext_soc_hal_reg_caps_parse(काष्ठा ath11k_base *soc,
						     u16 len, स्थिर व्योम *ptr,
						     व्योम *data)
अणु
	काष्ठा ath11k_pdev_wmi *wmi_handle = &soc->wmi_ab.wmi[0];
	काष्ठा wmi_tlv_svc_rdy_ext_parse *svc_rdy_ext = data;
	u8 hw_mode_id = svc_rdy_ext->pref_hw_mode_caps.hw_mode_id;
	u32 phy_id_map;
	पूर्णांक pdev_index = 0;
	पूर्णांक ret;

	svc_rdy_ext->soc_hal_reg_caps = (काष्ठा wmi_soc_hal_reg_capabilities *)ptr;
	svc_rdy_ext->param.num_phy = svc_rdy_ext->soc_hal_reg_caps->num_phy;

	soc->num_radios = 0;
	phy_id_map = svc_rdy_ext->pref_hw_mode_caps.phy_id_map;

	जबतक (phy_id_map && soc->num_radios < MAX_RADIOS) अणु
		ret = ath11k_pull_mac_phy_cap_svc_पढ़ोy_ext(wmi_handle,
							    svc_rdy_ext->hw_caps,
							    svc_rdy_ext->hw_mode_caps,
							    svc_rdy_ext->soc_hal_reg_caps,
							    svc_rdy_ext->mac_phy_caps,
							    hw_mode_id, soc->num_radios,
							    &soc->pdevs[pdev_index]);
		अगर (ret) अणु
			ath11k_warn(soc, "failed to extract mac caps, idx :%d\n",
				    soc->num_radios);
			वापस ret;
		पूर्ण

		soc->num_radios++;

		/* For QCA6390, save mac_phy capability in the same pdev */
		अगर (soc->hw_params.single_pdev_only)
			pdev_index = 0;
		अन्यथा
			pdev_index = soc->num_radios;

		/* TODO: mac_phy_cap prपूर्णांकs */
		phy_id_map >>= 1;
	पूर्ण

	/* For QCA6390, set num_radios to 1 because host manages
	 * both 2G and 5G radio in one pdev.
	 * Set pdev_id = 0 and 0 means soc level.
	 */
	अगर (soc->hw_params.single_pdev_only) अणु
		soc->num_radios = 1;
		soc->pdevs[0].pdev_id = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_dma_ring_caps_parse(काष्ठा ath11k_base *soc,
					      u16 tag, u16 len,
					      स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_dma_ring_caps_parse *parse = data;

	अगर (tag != WMI_TAG_DMA_RING_CAPABILITIES)
		वापस -EPROTO;

	parse->n_dma_ring_caps++;
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_wmi_alloc_dbring_caps(काष्ठा ath11k_base *ab,
					u32 num_cap)
अणु
	माप_प्रकार sz;
	व्योम *ptr;

	sz = num_cap * माप(काष्ठा ath11k_dbring_cap);
	ptr = kzalloc(sz, GFP_ATOMIC);
	अगर (!ptr)
		वापस -ENOMEM;

	ab->db_caps = ptr;
	ab->num_db_cap = num_cap;

	वापस 0;
पूर्ण

अटल व्योम ath11k_wmi_मुक्त_dbring_caps(काष्ठा ath11k_base *ab)
अणु
	kमुक्त(ab->db_caps);
	ab->db_caps = शून्य;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_dma_ring_caps(काष्ठा ath11k_base *ab,
					u16 len, स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_dma_ring_caps_parse *dma_caps_parse = data;
	काष्ठा wmi_dma_ring_capabilities *dma_caps;
	काष्ठा ath11k_dbring_cap *dir_buff_caps;
	पूर्णांक ret;
	u32 i;

	dma_caps_parse->n_dma_ring_caps = 0;
	dma_caps = (काष्ठा wmi_dma_ring_capabilities *)ptr;
	ret = ath11k_wmi_tlv_iter(ab, ptr, len,
				  ath11k_wmi_tlv_dma_ring_caps_parse,
				  dma_caps_parse);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to parse dma ring caps tlv %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!dma_caps_parse->n_dma_ring_caps)
		वापस 0;

	अगर (ab->num_db_cap) अणु
		ath11k_warn(ab, "Already processed, so ignoring dma ring caps\n");
		वापस 0;
	पूर्ण

	ret = ath11k_wmi_alloc_dbring_caps(ab, dma_caps_parse->n_dma_ring_caps);
	अगर (ret)
		वापस ret;

	dir_buff_caps = ab->db_caps;
	क्रम (i = 0; i < dma_caps_parse->n_dma_ring_caps; i++) अणु
		अगर (dma_caps[i].module_id >= WMI_सूचीECT_BUF_MAX) अणु
			ath11k_warn(ab, "Invalid module id %d\n", dma_caps[i].module_id);
			ret = -EINVAL;
			जाओ मुक्त_dir_buff;
		पूर्ण

		dir_buff_caps[i].id = dma_caps[i].module_id;
		dir_buff_caps[i].pdev_id = DP_HW2SW_MACID(dma_caps[i].pdev_id);
		dir_buff_caps[i].min_elem = dma_caps[i].min_elem;
		dir_buff_caps[i].min_buf_sz = dma_caps[i].min_buf_sz;
		dir_buff_caps[i].min_buf_align = dma_caps[i].min_buf_align;
	पूर्ण

	वापस 0;

मुक्त_dir_buff:
	ath11k_wmi_मुक्त_dbring_caps(ab);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_svc_rdy_ext_parse(काष्ठा ath11k_base *ab,
					    u16 tag, u16 len,
					    स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा ath11k_pdev_wmi *wmi_handle = &ab->wmi_ab.wmi[0];
	काष्ठा wmi_tlv_svc_rdy_ext_parse *svc_rdy_ext = data;
	पूर्णांक ret;

	चयन (tag) अणु
	हाल WMI_TAG_SERVICE_READY_EXT_EVENT:
		ret = ath11k_pull_svc_पढ़ोy_ext(wmi_handle, ptr,
						&svc_rdy_ext->param);
		अगर (ret) अणु
			ath11k_warn(ab, "unable to extract ext params\n");
			वापस ret;
		पूर्ण
		अवरोध;

	हाल WMI_TAG_SOC_MAC_PHY_HW_MODE_CAPS:
		svc_rdy_ext->hw_caps = (काष्ठा wmi_soc_mac_phy_hw_mode_caps *)ptr;
		svc_rdy_ext->param.num_hw_modes = svc_rdy_ext->hw_caps->num_hw_modes;
		अवरोध;

	हाल WMI_TAG_SOC_HAL_REG_CAPABILITIES:
		ret = ath11k_wmi_tlv_ext_soc_hal_reg_caps_parse(ab, len, ptr,
								svc_rdy_ext);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल WMI_TAG_ARRAY_STRUCT:
		अगर (!svc_rdy_ext->hw_mode_करोne) अणु
			ret = ath11k_wmi_tlv_hw_mode_caps(ab, len, ptr,
							  svc_rdy_ext);
			अगर (ret)
				वापस ret;

			svc_rdy_ext->hw_mode_करोne = true;
		पूर्ण अन्यथा अगर (!svc_rdy_ext->mac_phy_करोne) अणु
			svc_rdy_ext->n_mac_phy_caps = 0;
			ret = ath11k_wmi_tlv_iter(ab, ptr, len,
						  ath11k_wmi_tlv_mac_phy_caps_parse,
						  svc_rdy_ext);
			अगर (ret) अणु
				ath11k_warn(ab, "failed to parse tlv %d\n", ret);
				वापस ret;
			पूर्ण

			svc_rdy_ext->mac_phy_करोne = true;
		पूर्ण अन्यथा अगर (!svc_rdy_ext->ext_hal_reg_करोne) अणु
			ret = ath11k_wmi_tlv_ext_hal_reg_caps(ab, len, ptr,
							      svc_rdy_ext);
			अगर (ret)
				वापस ret;

			svc_rdy_ext->ext_hal_reg_करोne = true;
		पूर्ण अन्यथा अगर (!svc_rdy_ext->mac_phy_chainmask_combo_करोne) अणु
			svc_rdy_ext->mac_phy_chainmask_combo_करोne = true;
		पूर्ण अन्यथा अगर (!svc_rdy_ext->mac_phy_chainmask_cap_करोne) अणु
			svc_rdy_ext->mac_phy_chainmask_cap_करोne = true;
		पूर्ण अन्यथा अगर (!svc_rdy_ext->oem_dma_ring_cap_करोne) अणु
			svc_rdy_ext->oem_dma_ring_cap_करोne = true;
		पूर्ण अन्यथा अगर (!svc_rdy_ext->dma_ring_cap_करोne) अणु
			ret = ath11k_wmi_tlv_dma_ring_caps(ab, len, ptr,
							   &svc_rdy_ext->dma_caps_parse);
			अगर (ret)
				वापस ret;

			svc_rdy_ext->dma_ring_cap_करोne = true;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_service_पढ़ोy_ext_event(काष्ठा ath11k_base *ab,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_tlv_svc_rdy_ext_parse svc_rdy_ext = अणु पूर्ण;
	पूर्णांक ret;

	ret = ath11k_wmi_tlv_iter(ab, skb->data, skb->len,
				  ath11k_wmi_tlv_svc_rdy_ext_parse,
				  &svc_rdy_ext);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to parse tlv %d\n", ret);
		जाओ err;
	पूर्ण

	अगर (!test_bit(WMI_TLV_SERVICE_EXT2_MSG, ab->wmi_ab.svc_map))
		complete(&ab->wmi_ab.service_पढ़ोy);

	kमुक्त(svc_rdy_ext.mac_phy_caps);
	वापस 0;

err:
	ath11k_wmi_मुक्त_dbring_caps(ab);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_svc_rdy_ext2_parse(काष्ठा ath11k_base *ab,
					     u16 tag, u16 len,
					     स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_svc_rdy_ext2_parse *parse = data;
	पूर्णांक ret;

	चयन (tag) अणु
	हाल WMI_TAG_ARRAY_STRUCT:
		अगर (!parse->dma_ring_cap_करोne) अणु
			ret = ath11k_wmi_tlv_dma_ring_caps(ab, len, ptr,
							   &parse->dma_caps_parse);
			अगर (ret)
				वापस ret;

			parse->dma_ring_cap_करोne = true;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_service_पढ़ोy_ext2_event(काष्ठा ath11k_base *ab,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_tlv_svc_rdy_ext2_parse svc_rdy_ext2 = अणु पूर्ण;
	पूर्णांक ret;

	ret = ath11k_wmi_tlv_iter(ab, skb->data, skb->len,
				  ath11k_wmi_tlv_svc_rdy_ext2_parse,
				  &svc_rdy_ext2);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to parse ext2 event tlv %d\n", ret);
		जाओ err;
	पूर्ण

	complete(&ab->wmi_ab.service_पढ़ोy);

	वापस 0;

err:
	ath11k_wmi_मुक्त_dbring_caps(ab);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_pull_vdev_start_resp_tlv(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
					   काष्ठा wmi_vdev_start_resp_event *vdev_rsp)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_vdev_start_resp_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_VDEV_START_RESPONSE_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch vdev start resp ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	स_रखो(vdev_rsp, 0, माप(*vdev_rsp));

	vdev_rsp->vdev_id = ev->vdev_id;
	vdev_rsp->requestor_id = ev->requestor_id;
	vdev_rsp->resp_type = ev->resp_type;
	vdev_rsp->status = ev->status;
	vdev_rsp->chain_mask = ev->chain_mask;
	vdev_rsp->smps_mode = ev->smps_mode;
	vdev_rsp->mac_id = ev->mac_id;
	vdev_rsp->cfgd_tx_streams = ev->cfgd_tx_streams;
	vdev_rsp->cfgd_rx_streams = ev->cfgd_rx_streams;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल काष्ठा cur_reg_rule
*create_reg_rules_from_wmi(u32 num_reg_rules,
			   काष्ठा wmi_regulatory_rule_काष्ठा *wmi_reg_rule)
अणु
	काष्ठा cur_reg_rule *reg_rule_ptr;
	u32 count;

	reg_rule_ptr =  kzalloc((num_reg_rules * माप(*reg_rule_ptr)),
				GFP_ATOMIC);

	अगर (!reg_rule_ptr)
		वापस शून्य;

	क्रम (count = 0; count < num_reg_rules; count++) अणु
		reg_rule_ptr[count].start_freq =
			FIELD_GET(REG_RULE_START_FREQ,
				  wmi_reg_rule[count].freq_info);
		reg_rule_ptr[count].end_freq =
			FIELD_GET(REG_RULE_END_FREQ,
				  wmi_reg_rule[count].freq_info);
		reg_rule_ptr[count].max_bw =
			FIELD_GET(REG_RULE_MAX_BW,
				  wmi_reg_rule[count].bw_pwr_info);
		reg_rule_ptr[count].reg_घातer =
			FIELD_GET(REG_RULE_REG_PWR,
				  wmi_reg_rule[count].bw_pwr_info);
		reg_rule_ptr[count].ant_gain =
			FIELD_GET(REG_RULE_ANT_GAIN,
				  wmi_reg_rule[count].bw_pwr_info);
		reg_rule_ptr[count].flags =
			FIELD_GET(REG_RULE_FLAGS,
				  wmi_reg_rule[count].flag_info);
	पूर्ण

	वापस reg_rule_ptr;
पूर्ण

अटल पूर्णांक ath11k_pull_reg_chan_list_update_ev(काष्ठा ath11k_base *ab,
					       काष्ठा sk_buff *skb,
					       काष्ठा cur_regulatory_info *reg_info)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_reg_chan_list_cc_event *chan_list_event_hdr;
	काष्ठा wmi_regulatory_rule_काष्ठा *wmi_reg_rule;
	u32 num_2g_reg_rules, num_5g_reg_rules;
	पूर्णांक ret;

	ath11k_dbg(ab, ATH11K_DBG_WMI, "processing regulatory channel list\n");

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	chan_list_event_hdr = tb[WMI_TAG_REG_CHAN_LIST_CC_EVENT];
	अगर (!chan_list_event_hdr) अणु
		ath11k_warn(ab, "failed to fetch reg chan list update ev\n");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	reg_info->num_2g_reg_rules = chan_list_event_hdr->num_2g_reg_rules;
	reg_info->num_5g_reg_rules = chan_list_event_hdr->num_5g_reg_rules;

	अगर (!(reg_info->num_2g_reg_rules + reg_info->num_5g_reg_rules)) अणु
		ath11k_warn(ab, "No regulatory rules available in the event info\n");
		kमुक्त(tb);
		वापस -EINVAL;
	पूर्ण

	स_नकल(reg_info->alpha2, &chan_list_event_hdr->alpha2,
	       REG_ALPHA2_LEN);
	reg_info->dfs_region = chan_list_event_hdr->dfs_region;
	reg_info->phybiपंचांगap = chan_list_event_hdr->phybiपंचांगap;
	reg_info->num_phy = chan_list_event_hdr->num_phy;
	reg_info->phy_id = chan_list_event_hdr->phy_id;
	reg_info->ctry_code = chan_list_event_hdr->country_id;
	reg_info->reg_dmn_pair = chan_list_event_hdr->करोमुख्य_code;
	अगर (chan_list_event_hdr->status_code == WMI_REG_SET_CC_STATUS_PASS)
		reg_info->status_code = REG_SET_CC_STATUS_PASS;
	अन्यथा अगर (chan_list_event_hdr->status_code == WMI_REG_CURRENT_ALPHA2_NOT_FOUND)
		reg_info->status_code = REG_CURRENT_ALPHA2_NOT_FOUND;
	अन्यथा अगर (chan_list_event_hdr->status_code == WMI_REG_INIT_ALPHA2_NOT_FOUND)
		reg_info->status_code = REG_INIT_ALPHA2_NOT_FOUND;
	अन्यथा अगर (chan_list_event_hdr->status_code == WMI_REG_SET_CC_CHANGE_NOT_ALLOWED)
		reg_info->status_code = REG_SET_CC_CHANGE_NOT_ALLOWED;
	अन्यथा अगर (chan_list_event_hdr->status_code == WMI_REG_SET_CC_STATUS_NO_MEMORY)
		reg_info->status_code = REG_SET_CC_STATUS_NO_MEMORY;
	अन्यथा अगर (chan_list_event_hdr->status_code == WMI_REG_SET_CC_STATUS_FAIL)
		reg_info->status_code = REG_SET_CC_STATUS_FAIL;

	reg_info->min_bw_2g = chan_list_event_hdr->min_bw_2g;
	reg_info->max_bw_2g = chan_list_event_hdr->max_bw_2g;
	reg_info->min_bw_5g = chan_list_event_hdr->min_bw_5g;
	reg_info->max_bw_5g = chan_list_event_hdr->max_bw_5g;

	num_2g_reg_rules = reg_info->num_2g_reg_rules;
	num_5g_reg_rules = reg_info->num_5g_reg_rules;

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "%s:cc %s dsf %d BW: min_2g %d max_2g %d min_5g %d max_5g %d",
		   __func__, reg_info->alpha2, reg_info->dfs_region,
		   reg_info->min_bw_2g, reg_info->max_bw_2g,
		   reg_info->min_bw_5g, reg_info->max_bw_5g);

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "%s: num_2g_reg_rules %d num_5g_reg_rules %d", __func__,
		   num_2g_reg_rules, num_5g_reg_rules);

	wmi_reg_rule =
		(काष्ठा wmi_regulatory_rule_काष्ठा *)((u8 *)chan_list_event_hdr
						+ माप(*chan_list_event_hdr)
						+ माप(काष्ठा wmi_tlv));

	अगर (num_2g_reg_rules) अणु
		reg_info->reg_rules_2g_ptr = create_reg_rules_from_wmi(num_2g_reg_rules,
								       wmi_reg_rule);
		अगर (!reg_info->reg_rules_2g_ptr) अणु
			kमुक्त(tb);
			ath11k_warn(ab, "Unable to Allocate memory for 2g rules\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (num_5g_reg_rules) अणु
		wmi_reg_rule += num_2g_reg_rules;
		reg_info->reg_rules_5g_ptr = create_reg_rules_from_wmi(num_5g_reg_rules,
								       wmi_reg_rule);
		अगर (!reg_info->reg_rules_5g_ptr) अणु
			kमुक्त(tb);
			ath11k_warn(ab, "Unable to Allocate memory for 5g rules\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI, "processed regulatory channel list\n");

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_peer_del_resp_ev(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
					काष्ठा wmi_peer_delete_resp_event *peer_del_resp)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_peer_delete_resp_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_PEER_DELETE_RESP_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch peer delete resp ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	स_रखो(peer_del_resp, 0, माप(*peer_del_resp));

	peer_del_resp->vdev_id = ev->vdev_id;
	ether_addr_copy(peer_del_resp->peer_macaddr.addr,
			ev->peer_macaddr.addr);

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_vdev_del_resp_ev(काष्ठा ath11k_base *ab,
					काष्ठा sk_buff *skb,
					u32 *vdev_id)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_vdev_delete_resp_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_VDEV_DELETE_RESP_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch vdev delete resp ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	*vdev_id = ev->vdev_id;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_bcn_tx_status_ev(काष्ठा ath11k_base *ab, व्योम *evt_buf,
					u32 len, u32 *vdev_id,
					u32 *tx_status)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_bcn_tx_status_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, evt_buf, len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_OFFLOAD_BCN_TX_STATUS_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch bcn tx status ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	*vdev_id   = ev->vdev_id;
	*tx_status = ev->tx_status;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_vdev_stopped_param_tlv(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
					      u32 *vdev_id)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_vdev_stopped_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_VDEV_STOPPED_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch vdev stop ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	*vdev_id =  ev->vdev_id;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_mgmt_rx_params_tlv(काष्ठा ath11k_base *ab,
					  काष्ठा sk_buff *skb,
					  काष्ठा mgmt_rx_event_params *hdr)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_mgmt_rx_hdr *ev;
	स्थिर u8 *frame;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_MGMT_RX_HDR];
	frame = tb[WMI_TAG_ARRAY_BYTE];

	अगर (!ev || !frame) अणु
		ath11k_warn(ab, "failed to fetch mgmt rx hdr");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	hdr->pdev_id =  ev->pdev_id;
	hdr->chan_freq = ev->chan_freq;
	hdr->channel =  ev->channel;
	hdr->snr =  ev->snr;
	hdr->rate =  ev->rate;
	hdr->phy_mode =  ev->phy_mode;
	hdr->buf_len =  ev->buf_len;
	hdr->status =  ev->status;
	hdr->flags =  ev->flags;
	hdr->rssi =  ev->rssi;
	hdr->tsf_delta =  ev->tsf_delta;
	स_नकल(hdr->rssi_ctl, ev->rssi_ctl, माप(hdr->rssi_ctl));

	अगर (skb->len < (frame - skb->data) + hdr->buf_len) अणु
		ath11k_warn(ab, "invalid length in mgmt rx hdr ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	/* shअगरt the sk_buff to poपूर्णांक to `frame` */
	skb_trim(skb, 0);
	skb_put(skb, frame - skb->data);
	skb_pull(skb, frame - skb->data);
	skb_put(skb, hdr->buf_len);

	ath11k_ce_byte_swap(skb->data, hdr->buf_len);

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक wmi_process_mgmt_tx_comp(काष्ठा ath11k *ar, u32 desc_id,
				    u32 status)
अणु
	काष्ठा sk_buff *msdu;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ath11k_skb_cb *skb_cb;

	spin_lock_bh(&ar->txmgmt_idr_lock);
	msdu = idr_find(&ar->txmgmt_idr, desc_id);

	अगर (!msdu) अणु
		ath11k_warn(ar->ab, "received mgmt tx compl for invalid msdu_id: %d\n",
			    desc_id);
		spin_unlock_bh(&ar->txmgmt_idr_lock);
		वापस -ENOENT;
	पूर्ण

	idr_हटाओ(&ar->txmgmt_idr, desc_id);
	spin_unlock_bh(&ar->txmgmt_idr_lock);

	skb_cb = ATH11K_SKB_CB(msdu);
	dma_unmap_single(ar->ab->dev, skb_cb->paddr, msdu->len, DMA_TO_DEVICE);

	info = IEEE80211_SKB_CB(msdu);
	अगर ((!(info->flags & IEEE80211_TX_CTL_NO_ACK)) && !status)
		info->flags |= IEEE80211_TX_STAT_ACK;

	ieee80211_tx_status_irqsafe(ar->hw, msdu);

	/* WARN when we received this event without करोing any mgmt tx */
	अगर (atomic_dec_अगर_positive(&ar->num_pending_mgmt_tx) < 0)
		WARN_ON_ONCE(1);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_mgmt_tx_compl_param_tlv(काष्ठा ath11k_base *ab,
					       काष्ठा sk_buff *skb,
					       काष्ठा wmi_mgmt_tx_compl_event *param)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_mgmt_tx_compl_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_MGMT_TX_COMPL_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch mgmt tx compl ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	param->pdev_id = ev->pdev_id;
	param->desc_id = ev->desc_id;
	param->status = ev->status;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल व्योम ath11k_wmi_event_scan_started(काष्ठा ath11k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
	हाल ATH11K_SCAN_RUNNING:
	हाल ATH11K_SCAN_ABORTING:
		ath11k_warn(ar->ab, "received scan started event in an invalid scan state: %s (%d)\n",
			    ath11k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH11K_SCAN_STARTING:
		ar->scan.state = ATH11K_SCAN_RUNNING;
		complete(&ar->scan.started);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_wmi_event_scan_start_failed(काष्ठा ath11k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
	हाल ATH11K_SCAN_RUNNING:
	हाल ATH11K_SCAN_ABORTING:
		ath11k_warn(ar->ab, "received scan start failed event in an invalid scan state: %s (%d)\n",
			    ath11k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH11K_SCAN_STARTING:
		complete(&ar->scan.started);
		__ath11k_mac_scan_finish(ar);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_wmi_event_scan_completed(काष्ठा ath11k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
	हाल ATH11K_SCAN_STARTING:
		/* One suspected reason scan can be completed जबतक starting is
		 * अगर firmware fails to deliver all scan events to the host,
		 * e.g. when transport pipe is full. This has been observed
		 * with spectral scan phyerr events starving wmi transport
		 * pipe. In such हाल the "scan completed" event should be (and
		 * is) ignored by the host as it may be just firmware's scan
		 * state machine recovering.
		 */
		ath11k_warn(ar->ab, "received scan completed event in an invalid scan state: %s (%d)\n",
			    ath11k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH11K_SCAN_RUNNING:
	हाल ATH11K_SCAN_ABORTING:
		__ath11k_mac_scan_finish(ar);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_wmi_event_scan_bss_chan(काष्ठा ath11k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
	हाल ATH11K_SCAN_STARTING:
		ath11k_warn(ar->ab, "received scan bss chan event in an invalid scan state: %s (%d)\n",
			    ath11k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH11K_SCAN_RUNNING:
	हाल ATH11K_SCAN_ABORTING:
		ar->scan_channel = शून्य;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_wmi_event_scan_क्रमeign_chan(काष्ठा ath11k *ar, u32 freq)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
	हाल ATH11K_SCAN_STARTING:
		ath11k_warn(ar->ab, "received scan foreign chan event in an invalid scan state: %s (%d)\n",
			    ath11k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		अवरोध;
	हाल ATH11K_SCAN_RUNNING:
	हाल ATH11K_SCAN_ABORTING:
		ar->scan_channel = ieee80211_get_channel(ar->hw->wiphy, freq);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *
ath11k_wmi_event_scan_type_str(क्रमागत wmi_scan_event_type type,
			       क्रमागत wmi_scan_completion_reason reason)
अणु
	चयन (type) अणु
	हाल WMI_SCAN_EVENT_STARTED:
		वापस "started";
	हाल WMI_SCAN_EVENT_COMPLETED:
		चयन (reason) अणु
		हाल WMI_SCAN_REASON_COMPLETED:
			वापस "completed";
		हाल WMI_SCAN_REASON_CANCELLED:
			वापस "completed [cancelled]";
		हाल WMI_SCAN_REASON_PREEMPTED:
			वापस "completed [preempted]";
		हाल WMI_SCAN_REASON_TIMEDOUT:
			वापस "completed [timedout]";
		हाल WMI_SCAN_REASON_INTERNAL_FAILURE:
			वापस "completed [internal err]";
		हाल WMI_SCAN_REASON_MAX:
			अवरोध;
		पूर्ण
		वापस "completed [unknown]";
	हाल WMI_SCAN_EVENT_BSS_CHANNEL:
		वापस "bss channel";
	हाल WMI_SCAN_EVENT_FOREIGN_CHAN:
		वापस "foreign channel";
	हाल WMI_SCAN_EVENT_DEQUEUED:
		वापस "dequeued";
	हाल WMI_SCAN_EVENT_PREEMPTED:
		वापस "preempted";
	हाल WMI_SCAN_EVENT_START_FAILED:
		वापस "start failed";
	हाल WMI_SCAN_EVENT_RESTARTED:
		वापस "restarted";
	हाल WMI_SCAN_EVENT_FOREIGN_CHAN_EXIT:
		वापस "foreign channel exit";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_pull_scan_ev(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
			       काष्ठा wmi_scan_event *scan_evt_param)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_scan_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_SCAN_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch scan ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	scan_evt_param->event_type = ev->event_type;
	scan_evt_param->reason = ev->reason;
	scan_evt_param->channel_freq = ev->channel_freq;
	scan_evt_param->scan_req_id = ev->scan_req_id;
	scan_evt_param->scan_id = ev->scan_id;
	scan_evt_param->vdev_id = ev->vdev_id;
	scan_evt_param->tsf_बारtamp = ev->tsf_बारtamp;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_peer_sta_kickout_ev(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
					   काष्ठा wmi_peer_sta_kickout_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_peer_sta_kickout_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_PEER_STA_KICKOUT_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch peer sta kickout ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->mac_addr = ev->peer_macaddr.addr;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_roam_ev(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
			       काष्ठा wmi_roam_event *roam_ev)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_roam_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_ROAM_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch roam ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	roam_ev->vdev_id = ev->vdev_id;
	roam_ev->reason = ev->reason;
	roam_ev->rssi = ev->rssi;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक freq_to_idx(काष्ठा ath11k *ar, पूर्णांक freq)
अणु
	काष्ठा ieee80211_supported_band *sband;
	पूर्णांक band, ch, idx = 0;

	क्रम (band = NL80211_BAND_2GHZ; band < NUM_NL80211_BANDS; band++) अणु
		sband = ar->hw->wiphy->bands[band];
		अगर (!sband)
			जारी;

		क्रम (ch = 0; ch < sband->n_channels; ch++, idx++)
			अगर (sband->channels[ch].center_freq == freq)
				जाओ निकास;
	पूर्ण

निकास:
	वापस idx;
पूर्ण

अटल पूर्णांक ath11k_pull_chan_info_ev(काष्ठा ath11k_base *ab, u8 *evt_buf,
				    u32 len, काष्ठा wmi_chan_info_event *ch_info_ev)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_chan_info_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, evt_buf, len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_CHAN_INFO_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch chan info ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	ch_info_ev->err_code = ev->err_code;
	ch_info_ev->freq = ev->freq;
	ch_info_ev->cmd_flags = ev->cmd_flags;
	ch_info_ev->noise_न्यूनमान = ev->noise_न्यूनमान;
	ch_info_ev->rx_clear_count = ev->rx_clear_count;
	ch_info_ev->cycle_count = ev->cycle_count;
	ch_info_ev->chan_tx_pwr_range = ev->chan_tx_pwr_range;
	ch_info_ev->chan_tx_pwr_tp = ev->chan_tx_pwr_tp;
	ch_info_ev->rx_frame_count = ev->rx_frame_count;
	ch_info_ev->tx_frame_cnt = ev->tx_frame_cnt;
	ch_info_ev->mac_clk_mhz = ev->mac_clk_mhz;
	ch_info_ev->vdev_id = ev->vdev_id;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_pull_pdev_bss_chan_info_ev(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
				  काष्ठा wmi_pdev_bss_chan_info_event *bss_ch_info_ev)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_pdev_bss_chan_info_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_PDEV_BSS_CHAN_INFO_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch pdev bss chan info ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	bss_ch_info_ev->pdev_id = ev->pdev_id;
	bss_ch_info_ev->freq = ev->freq;
	bss_ch_info_ev->noise_न्यूनमान = ev->noise_न्यूनमान;
	bss_ch_info_ev->rx_clear_count_low = ev->rx_clear_count_low;
	bss_ch_info_ev->rx_clear_count_high = ev->rx_clear_count_high;
	bss_ch_info_ev->cycle_count_low = ev->cycle_count_low;
	bss_ch_info_ev->cycle_count_high = ev->cycle_count_high;
	bss_ch_info_ev->tx_cycle_count_low = ev->tx_cycle_count_low;
	bss_ch_info_ev->tx_cycle_count_high = ev->tx_cycle_count_high;
	bss_ch_info_ev->rx_cycle_count_low = ev->rx_cycle_count_low;
	bss_ch_info_ev->rx_cycle_count_high = ev->rx_cycle_count_high;
	bss_ch_info_ev->rx_bss_cycle_count_low = ev->rx_bss_cycle_count_low;
	bss_ch_info_ev->rx_bss_cycle_count_high = ev->rx_bss_cycle_count_high;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_pull_vdev_install_key_compl_ev(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
				      काष्ठा wmi_vdev_install_key_complete_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_vdev_install_key_compl_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_VDEV_INSTALL_KEY_COMPLETE_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch vdev install key compl ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->vdev_id = ev->vdev_id;
	arg->macaddr = ev->peer_macaddr.addr;
	arg->key_idx = ev->key_idx;
	arg->key_flags = ev->key_flags;
	arg->status = ev->status;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_pull_peer_assoc_conf_ev(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
					  काष्ठा wmi_peer_assoc_conf_arg *peer_assoc_conf)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_peer_assoc_conf_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_PEER_ASSOC_CONF_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch peer assoc conf ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	peer_assoc_conf->vdev_id = ev->vdev_id;
	peer_assoc_conf->macaddr = ev->peer_macaddr.addr;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल व्योम ath11k_wmi_pull_pdev_stats_base(स्थिर काष्ठा wmi_pdev_stats_base *src,
					    काष्ठा ath11k_fw_stats_pdev *dst)
अणु
	dst->ch_noise_न्यूनमान = src->chan_nf;
	dst->tx_frame_count = src->tx_frame_count;
	dst->rx_frame_count = src->rx_frame_count;
	dst->rx_clear_count = src->rx_clear_count;
	dst->cycle_count = src->cycle_count;
	dst->phy_err_count = src->phy_err_count;
	dst->chan_tx_घातer = src->chan_tx_pwr;
पूर्ण

अटल व्योम
ath11k_wmi_pull_pdev_stats_tx(स्थिर काष्ठा wmi_pdev_stats_tx *src,
			      काष्ठा ath11k_fw_stats_pdev *dst)
अणु
	dst->comp_queued = src->comp_queued;
	dst->comp_delivered = src->comp_delivered;
	dst->msdu_enqued = src->msdu_enqued;
	dst->mpdu_enqued = src->mpdu_enqued;
	dst->wmm_drop = src->wmm_drop;
	dst->local_enqued = src->local_enqued;
	dst->local_मुक्तd = src->local_मुक्तd;
	dst->hw_queued = src->hw_queued;
	dst->hw_reaped = src->hw_reaped;
	dst->underrun = src->underrun;
	dst->tx_पात = src->tx_पात;
	dst->mpdus_requed = src->mpdus_requed;
	dst->tx_ko = src->tx_ko;
	dst->data_rc = src->data_rc;
	dst->self_triggers = src->self_triggers;
	dst->sw_retry_failure = src->sw_retry_failure;
	dst->illgl_rate_phy_err = src->illgl_rate_phy_err;
	dst->pdev_cont_xretry = src->pdev_cont_xretry;
	dst->pdev_tx_समयout = src->pdev_tx_समयout;
	dst->pdev_resets = src->pdev_resets;
	dst->stateless_tid_alloc_failure = src->stateless_tid_alloc_failure;
	dst->phy_underrun = src->phy_underrun;
	dst->txop_ovf = src->txop_ovf;
पूर्ण

अटल व्योम ath11k_wmi_pull_pdev_stats_rx(स्थिर काष्ठा wmi_pdev_stats_rx *src,
					  काष्ठा ath11k_fw_stats_pdev *dst)
अणु
	dst->mid_ppdu_route_change = src->mid_ppdu_route_change;
	dst->status_rcvd = src->status_rcvd;
	dst->r0_frags = src->r0_frags;
	dst->r1_frags = src->r1_frags;
	dst->r2_frags = src->r2_frags;
	dst->r3_frags = src->r3_frags;
	dst->htt_msdus = src->htt_msdus;
	dst->htt_mpdus = src->htt_mpdus;
	dst->loc_msdus = src->loc_msdus;
	dst->loc_mpdus = src->loc_mpdus;
	dst->oversize_amsdu = src->oversize_amsdu;
	dst->phy_errs = src->phy_errs;
	dst->phy_err_drop = src->phy_err_drop;
	dst->mpdu_errs = src->mpdu_errs;
पूर्ण

अटल व्योम
ath11k_wmi_pull_vdev_stats(स्थिर काष्ठा wmi_vdev_stats *src,
			   काष्ठा ath11k_fw_stats_vdev *dst)
अणु
	पूर्णांक i;

	dst->vdev_id = src->vdev_id;
	dst->beacon_snr = src->beacon_snr;
	dst->data_snr = src->data_snr;
	dst->num_rx_frames = src->num_rx_frames;
	dst->num_rts_fail = src->num_rts_fail;
	dst->num_rts_success = src->num_rts_success;
	dst->num_rx_err = src->num_rx_err;
	dst->num_rx_discard = src->num_rx_discard;
	dst->num_tx_not_acked = src->num_tx_not_acked;

	क्रम (i = 0; i < ARRAY_SIZE(src->num_tx_frames); i++)
		dst->num_tx_frames[i] = src->num_tx_frames[i];

	क्रम (i = 0; i < ARRAY_SIZE(src->num_tx_frames_retries); i++)
		dst->num_tx_frames_retries[i] = src->num_tx_frames_retries[i];

	क्रम (i = 0; i < ARRAY_SIZE(src->num_tx_frames_failures); i++)
		dst->num_tx_frames_failures[i] = src->num_tx_frames_failures[i];

	क्रम (i = 0; i < ARRAY_SIZE(src->tx_rate_history); i++)
		dst->tx_rate_history[i] = src->tx_rate_history[i];

	क्रम (i = 0; i < ARRAY_SIZE(src->beacon_rssi_history); i++)
		dst->beacon_rssi_history[i] = src->beacon_rssi_history[i];
पूर्ण

अटल व्योम
ath11k_wmi_pull_bcn_stats(स्थिर काष्ठा wmi_bcn_stats *src,
			  काष्ठा ath11k_fw_stats_bcn *dst)
अणु
	dst->vdev_id = src->vdev_id;
	dst->tx_bcn_succ_cnt = src->tx_bcn_succ_cnt;
	dst->tx_bcn_outage_cnt = src->tx_bcn_outage_cnt;
पूर्ण

पूर्णांक ath11k_wmi_pull_fw_stats(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb,
			     काष्ठा ath11k_fw_stats *stats)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_stats_event *ev;
	स्थिर व्योम *data;
	पूर्णांक i, ret;
	u32 len = skb->len;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TAG_STATS_EVENT];
	data = tb[WMI_TAG_ARRAY_BYTE];
	अगर (!ev || !data) अणु
		ath11k_warn(ab, "failed to fetch update stats ev");
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "wmi stats update ev pdev_id %d pdev %i vdev %i bcn %i\n",
		   ev->pdev_id,
		   ev->num_pdev_stats, ev->num_vdev_stats,
		   ev->num_bcn_stats);

	stats->pdev_id = ev->pdev_id;
	stats->stats_id = 0;

	क्रम (i = 0; i < ev->num_pdev_stats; i++) अणु
		स्थिर काष्ठा wmi_pdev_stats *src;
		काष्ठा ath11k_fw_stats_pdev *dst;

		src = data;
		अगर (len < माप(*src)) अणु
			kमुक्त(tb);
			वापस -EPROTO;
		पूर्ण

		stats->stats_id = WMI_REQUEST_PDEV_STAT;

		data += माप(*src);
		len -= माप(*src);

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath11k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath11k_wmi_pull_pdev_stats_tx(&src->tx, dst);
		ath11k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		list_add_tail(&dst->list, &stats->pdevs);
	पूर्ण

	क्रम (i = 0; i < ev->num_vdev_stats; i++) अणु
		स्थिर काष्ठा wmi_vdev_stats *src;
		काष्ठा ath11k_fw_stats_vdev *dst;

		src = data;
		अगर (len < माप(*src)) अणु
			kमुक्त(tb);
			वापस -EPROTO;
		पूर्ण

		stats->stats_id = WMI_REQUEST_VDEV_STAT;

		data += माप(*src);
		len -= माप(*src);

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath11k_wmi_pull_vdev_stats(src, dst);
		list_add_tail(&dst->list, &stats->vdevs);
	पूर्ण

	क्रम (i = 0; i < ev->num_bcn_stats; i++) अणु
		स्थिर काष्ठा wmi_bcn_stats *src;
		काष्ठा ath11k_fw_stats_bcn *dst;

		src = data;
		अगर (len < माप(*src)) अणु
			kमुक्त(tb);
			वापस -EPROTO;
		पूर्ण

		stats->stats_id = WMI_REQUEST_BCN_STAT;

		data += माप(*src);
		len -= माप(*src);

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath11k_wmi_pull_bcn_stats(src, dst);
		list_add_tail(&dst->list, &stats->bcn);
	पूर्ण

	kमुक्त(tb);
	वापस 0;
पूर्ण

माप_प्रकार ath11k_wmi_fw_stats_num_vdevs(काष्ठा list_head *head)
अणु
	काष्ठा ath11k_fw_stats_vdev *i;
	माप_प्रकार num = 0;

	list_क्रम_each_entry(i, head, list)
		++num;

	वापस num;
पूर्ण

अटल माप_प्रकार ath11k_wmi_fw_stats_num_bcn(काष्ठा list_head *head)
अणु
	काष्ठा ath11k_fw_stats_bcn *i;
	माप_प्रकार num = 0;

	list_क्रम_each_entry(i, head, list)
		++num;

	वापस num;
पूर्ण

अटल व्योम
ath11k_wmi_fw_pdev_base_stats_fill(स्थिर काष्ठा ath11k_fw_stats_pdev *pdev,
				   अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH11K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n",
			"ath11k PDEV stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
			"=================");

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			"Channel noise floor", pdev->ch_noise_न्यूनमान);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"Channel TX power", pdev->chan_tx_घातer);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"TX frame count", pdev->tx_frame_count);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"RX frame count", pdev->rx_frame_count);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"RX clear count", pdev->rx_clear_count);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"Cycle count", pdev->cycle_count);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			"PHY error count", pdev->phy_err_count);

	*length = len;
पूर्ण

अटल व्योम
ath11k_wmi_fw_pdev_tx_stats_fill(स्थिर काष्ठा ath11k_fw_stats_pdev *pdev,
				 अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH11K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "\n%30s\n",
			 "ath11k PDEV TX stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
			 "====================");

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "HTT cookies queued", pdev->comp_queued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "HTT cookies disp.", pdev->comp_delivered);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MSDU queued", pdev->msdu_enqued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDU queued", pdev->mpdu_enqued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MSDUs dropped", pdev->wmm_drop);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Local enqued", pdev->local_enqued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Local freed", pdev->local_मुक्तd);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "HW queued", pdev->hw_queued);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PPDUs reaped", pdev->hw_reaped);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Num underruns", pdev->underrun);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PPDUs cleaned", pdev->tx_पात);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDUs requed", pdev->mpdus_requed);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "Excessive retries", pdev->tx_ko);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "HW rate", pdev->data_rc);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "Sched self triggers", pdev->self_triggers);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "Dropped due to SW retries",
			 pdev->sw_retry_failure);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "Illegal rate phy errors",
			 pdev->illgl_rate_phy_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "PDEV continuous xretry", pdev->pdev_cont_xretry);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "TX timeout", pdev->pdev_tx_समयout);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "PDEV resets", pdev->pdev_resets);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "Stateless TIDs alloc failures",
			 pdev->stateless_tid_alloc_failure);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "PHY underrun", pdev->phy_underrun);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10u\n",
			 "MPDU is more than txop limit", pdev->txop_ovf);
	*length = len;
पूर्ण

अटल व्योम
ath11k_wmi_fw_pdev_rx_stats_fill(स्थिर काष्ठा ath11k_fw_stats_pdev *pdev,
				 अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH11K_FW_STATS_BUF_SIZE;

	len += scnम_लिखो(buf + len, buf_len - len, "\n%30s\n",
			 "ath11k PDEV RX stats");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
			 "====================");

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Mid PPDU route change",
			 pdev->mid_ppdu_route_change);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Tot. number of statuses", pdev->status_rcvd);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Extra frags on rings 0", pdev->r0_frags);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Extra frags on rings 1", pdev->r1_frags);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Extra frags on rings 2", pdev->r2_frags);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Extra frags on rings 3", pdev->r3_frags);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MSDUs delivered to HTT", pdev->htt_msdus);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDUs delivered to HTT", pdev->htt_mpdus);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MSDUs delivered to stack", pdev->loc_msdus);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDUs delivered to stack", pdev->loc_mpdus);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "Oversized AMSUs", pdev->oversize_amsdu);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PHY errors", pdev->phy_errs);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "PHY errors drops", pdev->phy_err_drop);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %10d\n",
			 "MPDU errors (FCS, MIC, ENC)", pdev->mpdu_errs);
	*length = len;
पूर्ण

अटल व्योम
ath11k_wmi_fw_vdev_stats_fill(काष्ठा ath11k *ar,
			      स्थिर काष्ठा ath11k_fw_stats_vdev *vdev,
			      अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH11K_FW_STATS_BUF_SIZE;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_mac_get_arvअगर(ar, vdev->vdev_id);
	u8 *vअगर_macaddr;
	पूर्णांक i;

	/* VDEV stats has all the active VDEVs of other PDEVs as well,
	 * ignoring those not part of requested PDEV
	 */
	अगर (!arvअगर)
		वापस;

	vअगर_macaddr = arvअगर->vअगर->addr;

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "VDEV ID", vdev->vdev_id);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %pM\n",
			 "VDEV MAC address", vअगर_macaddr);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "beacon snr", vdev->beacon_snr);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "data snr", vdev->data_snr);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "num rx frames", vdev->num_rx_frames);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "num rts fail", vdev->num_rts_fail);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "num rts success", vdev->num_rts_success);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "num rx err", vdev->num_rx_err);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "num rx discard", vdev->num_rx_discard);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "num tx not acked", vdev->num_tx_not_acked);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames", i,
				vdev->num_tx_frames[i]);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames_retries); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames retries", i,
				vdev->num_tx_frames_retries[i]);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->num_tx_frames_failures); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"num tx frames failures", i,
				vdev->num_tx_frames_failures[i]);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->tx_rate_history); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] 0x%08x\n",
				"tx rate history", i,
				vdev->tx_rate_history[i]);

	क्रम (i = 0 ; i < ARRAY_SIZE(vdev->beacon_rssi_history); i++)
		len += scnम_लिखो(buf + len, buf_len - len,
				"%25s [%02d] %u\n",
				"beacon rssi history", i,
				vdev->beacon_rssi_history[i]);

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	*length = len;
पूर्ण

अटल व्योम
ath11k_wmi_fw_bcn_stats_fill(काष्ठा ath11k *ar,
			     स्थिर काष्ठा ath11k_fw_stats_bcn *bcn,
			     अक्षर *buf, u32 *length)
अणु
	u32 len = *length;
	u32 buf_len = ATH11K_FW_STATS_BUF_SIZE;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_mac_get_arvअगर(ar, bcn->vdev_id);
	u8 *vdev_macaddr;

	अगर (!arvअगर) अणु
		ath11k_warn(ar->ab, "invalid vdev id %d in bcn stats",
			    bcn->vdev_id);
		वापस;
	पूर्ण

	vdev_macaddr = arvअगर->vअगर->addr;

	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "VDEV ID", bcn->vdev_id);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %pM\n",
			 "VDEV MAC address", vdev_macaddr);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
			 "================");
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "Num of beacon tx success", bcn->tx_bcn_succ_cnt);
	len += scnम_लिखो(buf + len, buf_len - len, "%30s %u\n",
			 "Num of beacon tx failures", bcn->tx_bcn_outage_cnt);

	len += scnम_लिखो(buf + len, buf_len - len, "\n");
	*length = len;
पूर्ण

व्योम ath11k_wmi_fw_stats_fill(काष्ठा ath11k *ar,
			      काष्ठा ath11k_fw_stats *fw_stats,
			      u32 stats_id, अक्षर *buf)
अणु
	u32 len = 0;
	u32 buf_len = ATH11K_FW_STATS_BUF_SIZE;
	स्थिर काष्ठा ath11k_fw_stats_pdev *pdev;
	स्थिर काष्ठा ath11k_fw_stats_vdev *vdev;
	स्थिर काष्ठा ath11k_fw_stats_bcn *bcn;
	माप_प्रकार num_bcn;

	spin_lock_bh(&ar->data_lock);

	अगर (stats_id == WMI_REQUEST_PDEV_STAT) अणु
		pdev = list_first_entry_or_null(&fw_stats->pdevs,
						काष्ठा ath11k_fw_stats_pdev, list);
		अगर (!pdev) अणु
			ath11k_warn(ar->ab, "failed to get pdev stats\n");
			जाओ unlock;
		पूर्ण

		ath11k_wmi_fw_pdev_base_stats_fill(pdev, buf, &len);
		ath11k_wmi_fw_pdev_tx_stats_fill(pdev, buf, &len);
		ath11k_wmi_fw_pdev_rx_stats_fill(pdev, buf, &len);
	पूर्ण

	अगर (stats_id == WMI_REQUEST_VDEV_STAT) अणु
		len += scnम_लिखो(buf + len, buf_len - len, "\n");
		len += scnम_लिखो(buf + len, buf_len - len, "%30s\n",
				 "ath11k VDEV stats");
		len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				 "=================");

		list_क्रम_each_entry(vdev, &fw_stats->vdevs, list)
			ath11k_wmi_fw_vdev_stats_fill(ar, vdev, buf, &len);
	पूर्ण

	अगर (stats_id == WMI_REQUEST_BCN_STAT) अणु
		num_bcn = ath11k_wmi_fw_stats_num_bcn(&fw_stats->bcn);

		len += scnम_लिखो(buf + len, buf_len - len, "\n");
		len += scnम_लिखो(buf + len, buf_len - len, "%30s (%zu)\n",
				 "ath11k Beacon stats", num_bcn);
		len += scnम_लिखो(buf + len, buf_len - len, "%30s\n\n",
				 "===================");

		list_क्रम_each_entry(bcn, &fw_stats->bcn, list)
			ath11k_wmi_fw_bcn_stats_fill(ar, bcn, buf, &len);
	पूर्ण

unlock:
	spin_unlock_bh(&ar->data_lock);

	अगर (len >= buf_len)
		buf[len - 1] = 0;
	अन्यथा
		buf[len] = 0;
पूर्ण

अटल व्योम ath11k_wmi_op_ep_tx_credits(काष्ठा ath11k_base *ab)
अणु
	/* try to send pending beacons first. they take priority */
	wake_up(&ab->wmi_ab.tx_credits_wq);
पूर्ण

अटल व्योम ath11k_wmi_htc_tx_complete(काष्ठा ath11k_base *ab,
				       काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb(skb);
पूर्ण

अटल bool ath11k_reg_is_world_alpha(अक्षर *alpha)
अणु
	वापस alpha[0] == '0' && alpha[1] == '0';
पूर्ण

अटल पूर्णांक ath11k_reg_chan_list_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा cur_regulatory_info *reg_info = शून्य;
	काष्ठा ieee80211_regकरोमुख्य *regd = शून्य;
	bool पूर्णांकersect = false;
	पूर्णांक ret = 0, pdev_idx;
	काष्ठा ath11k *ar;

	reg_info = kzalloc(माप(*reg_info), GFP_ATOMIC);
	अगर (!reg_info) अणु
		ret = -ENOMEM;
		जाओ fallback;
	पूर्ण

	ret = ath11k_pull_reg_chan_list_update_ev(ab, skb, reg_info);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to extract regulatory info from received event\n");
		जाओ fallback;
	पूर्ण

	अगर (reg_info->status_code != REG_SET_CC_STATUS_PASS) अणु
		/* In हाल of failure to set the requested ctry,
		 * fw retains the current regd. We prपूर्णांक a failure info
		 * and वापस from here.
		 */
		ath11k_warn(ab, "Failed to set the requested Country regulatory setting\n");
		जाओ mem_मुक्त;
	पूर्ण

	pdev_idx = reg_info->phy_id;

	अगर (pdev_idx >= ab->num_radios) अणु
		/* Process the event क्रम phy0 only अगर single_pdev_only
		 * is true. If pdev_idx is valid but not 0, discard the
		 * event. Otherwise, it goes to fallback.
		 */
		अगर (ab->hw_params.single_pdev_only &&
		    pdev_idx < ab->hw_params.num_rxmda_per_pdev)
			जाओ mem_मुक्त;
		अन्यथा
			जाओ fallback;
	पूर्ण

	/* Aव्योम multiple overग_लिखोs to शेष regd, during core
	 * stop-start after mac registration.
	 */
	अगर (ab->शेष_regd[pdev_idx] && !ab->new_regd[pdev_idx] &&
	    !स_भेद((अक्षर *)ab->शेष_regd[pdev_idx]->alpha2,
		    (अक्षर *)reg_info->alpha2, 2))
		जाओ mem_मुक्त;

	/* Intersect new rules with शेष regd अगर a new country setting was
	 * requested, i.e a शेष regd was alपढ़ोy set during initialization
	 * and the regd coming from this event has a valid country info.
	 */
	अगर (ab->शेष_regd[pdev_idx] &&
	    !ath11k_reg_is_world_alpha((अक्षर *)
		ab->शेष_regd[pdev_idx]->alpha2) &&
	    !ath11k_reg_is_world_alpha((अक्षर *)reg_info->alpha2))
		पूर्णांकersect = true;

	regd = ath11k_reg_build_regd(ab, reg_info, पूर्णांकersect);
	अगर (!regd) अणु
		ath11k_warn(ab, "failed to build regd from reg_info\n");
		जाओ fallback;
	पूर्ण

	spin_lock(&ab->base_lock);
	अगर (test_bit(ATH11K_FLAG_REGISTERED, &ab->dev_flags)) अणु
		/* Once mac is रेजिस्टरed, ar is valid and all CC events from
		 * fw is considered to be received due to user requests
		 * currently.
		 * Free previously built regd beक्रमe assigning the newly
		 * generated regd to ar. शून्य poपूर्णांकer handling will be
		 * taken care by kमुक्त itself.
		 */
		ar = ab->pdevs[pdev_idx].ar;
		kमुक्त(ab->new_regd[pdev_idx]);
		ab->new_regd[pdev_idx] = regd;
		ieee80211_queue_work(ar->hw, &ar->regd_update_work);
	पूर्ण अन्यथा अणु
		/* Multiple events क्रम the same *ar is not expected. But we
		 * can still clear any previously stored शेष_regd अगर we
		 * are receiving this event क्रम the same radio by mistake.
		 * शून्य poपूर्णांकer handling will be taken care by kमुक्त itself.
		 */
		kमुक्त(ab->शेष_regd[pdev_idx]);
		/* This regd would be applied during mac registration */
		ab->शेष_regd[pdev_idx] = regd;
	पूर्ण
	ab->dfs_region = reg_info->dfs_region;
	spin_unlock(&ab->base_lock);

	जाओ mem_मुक्त;

fallback:
	/* Fallback to older reg (by sending previous country setting
	 * again अगर fw has succeded and we failed to process here.
	 * The Regकरोमुख्य should be unअगरorm across driver and fw. Since the
	 * FW has processed the command and sent a success status, we expect
	 * this function to succeed as well. If it करोesn't, CTRY needs to be
	 * reverted at the fw and the old SCAN_CHAN_LIST cmd needs to be sent.
	 */
	/* TODO: This is rare, but still should also be handled */
	WARN_ON(1);
mem_मुक्त:
	अगर (reg_info) अणु
		kमुक्त(reg_info->reg_rules_2g_ptr);
		kमुक्त(reg_info->reg_rules_5g_ptr);
		kमुक्त(reg_info);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_rdy_parse(काष्ठा ath11k_base *ab, u16 tag, u16 len,
				    स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_rdy_parse *rdy_parse = data;
	काष्ठा wmi_पढ़ोy_event fixed_param;
	काष्ठा wmi_mac_addr *addr_list;
	काष्ठा ath11k_pdev *pdev;
	u32 num_mac_addr;
	पूर्णांक i;

	चयन (tag) अणु
	हाल WMI_TAG_READY_EVENT:
		स_रखो(&fixed_param, 0, माप(fixed_param));
		स_नकल(&fixed_param, (काष्ठा wmi_पढ़ोy_event *)ptr,
		       min_t(u16, माप(fixed_param), len));
		ab->wlan_init_status = fixed_param.पढ़ोy_event_min.status;
		rdy_parse->num_extra_mac_addr =
			fixed_param.पढ़ोy_event_min.num_extra_mac_addr;

		ether_addr_copy(ab->mac_addr,
				fixed_param.पढ़ोy_event_min.mac_addr.addr);
		ab->pktlog_defs_checksum = fixed_param.pktlog_defs_checksum;
		ab->wmi_पढ़ोy = true;
		अवरोध;
	हाल WMI_TAG_ARRAY_FIXED_STRUCT:
		addr_list = (काष्ठा wmi_mac_addr *)ptr;
		num_mac_addr = rdy_parse->num_extra_mac_addr;

		अगर (!(ab->num_radios > 1 && num_mac_addr >= ab->num_radios))
			अवरोध;

		क्रम (i = 0; i < ab->num_radios; i++) अणु
			pdev = &ab->pdevs[i];
			ether_addr_copy(pdev->mac_addr, addr_list[i].addr);
		पूर्ण
		ab->pdevs_macaddr_valid = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_पढ़ोy_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_tlv_rdy_parse rdy_parse = अणु पूर्ण;
	पूर्णांक ret;

	ret = ath11k_wmi_tlv_iter(ab, skb->data, skb->len,
				  ath11k_wmi_tlv_rdy_parse, &rdy_parse);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to parse tlv %d\n", ret);
		वापस ret;
	पूर्ण

	complete(&ab->wmi_ab.unअगरied_पढ़ोy);
	वापस 0;
पूर्ण

अटल व्योम ath11k_peer_delete_resp_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_peer_delete_resp_event peer_del_resp;
	काष्ठा ath11k *ar;

	अगर (ath11k_pull_peer_del_resp_ev(ab, skb, &peer_del_resp) != 0) अणु
		ath11k_warn(ab, "failed to extract peer delete resp");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_vdev_id(ab, peer_del_resp.vdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in peer delete resp ev %d",
			    peer_del_resp.vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	complete(&ar->peer_delete_करोne);
	rcu_पढ़ो_unlock();
	ath11k_dbg(ab, ATH11K_DBG_WMI, "peer delete resp for vdev id %d addr %pM\n",
		   peer_del_resp.vdev_id, peer_del_resp.peer_macaddr.addr);
पूर्ण

अटल व्योम ath11k_vdev_delete_resp_event(काष्ठा ath11k_base *ab,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k *ar;
	u32 vdev_id = 0;

	अगर (ath11k_pull_vdev_del_resp_ev(ab, skb, &vdev_id) != 0) अणु
		ath11k_warn(ab, "failed to extract vdev delete resp");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_vdev_id(ab, vdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in vdev delete resp ev %d",
			    vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	complete(&ar->vdev_delete_करोne);

	rcu_पढ़ो_unlock();

	ath11k_dbg(ab, ATH11K_DBG_WMI, "vdev delete resp for vdev id %d\n",
		   vdev_id);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *ath11k_wmi_vdev_resp_prपूर्णांक(u32 vdev_resp_status)
अणु
	चयन (vdev_resp_status) अणु
	हाल WMI_VDEV_START_RESPONSE_INVALID_VDEVID:
		वापस "invalid vdev id";
	हाल WMI_VDEV_START_RESPONSE_NOT_SUPPORTED:
		वापस "not supported";
	हाल WMI_VDEV_START_RESPONSE_DFS_VIOLATION:
		वापस "dfs violation";
	हाल WMI_VDEV_START_RESPONSE_INVALID_REGDOMAIN:
		वापस "invalid regdomain";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल व्योम ath11k_vdev_start_resp_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_vdev_start_resp_event vdev_start_resp;
	काष्ठा ath11k *ar;
	u32 status;

	अगर (ath11k_pull_vdev_start_resp_tlv(ab, skb, &vdev_start_resp) != 0) अणु
		ath11k_warn(ab, "failed to extract vdev start resp");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_vdev_id(ab, vdev_start_resp.vdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in vdev start resp ev %d",
			    vdev_start_resp.vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	ar->last_wmi_vdev_start_status = 0;

	status = vdev_start_resp.status;

	अगर (WARN_ON_ONCE(status)) अणु
		ath11k_warn(ab, "vdev start resp error status %d (%s)\n",
			    status, ath11k_wmi_vdev_resp_prपूर्णांक(status));
		ar->last_wmi_vdev_start_status = status;
	पूर्ण

	complete(&ar->vdev_setup_करोne);

	rcu_पढ़ो_unlock();

	ath11k_dbg(ab, ATH11K_DBG_WMI, "vdev start resp for vdev id %d",
		   vdev_start_resp.vdev_id);
पूर्ण

अटल व्योम ath11k_bcn_tx_status_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	u32 vdev_id, tx_status;

	अगर (ath11k_pull_bcn_tx_status_ev(ab, skb->data, skb->len,
					 &vdev_id, &tx_status) != 0) अणु
		ath11k_warn(ab, "failed to extract bcn tx status");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम ath11k_vdev_stopped_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k *ar;
	u32 vdev_id = 0;

	अगर (ath11k_pull_vdev_stopped_param_tlv(ab, skb, &vdev_id) != 0) अणु
		ath11k_warn(ab, "failed to extract vdev stopped event");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_vdev_id(ab, vdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in vdev stopped ev %d",
			    vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	complete(&ar->vdev_setup_करोne);

	rcu_पढ़ो_unlock();

	ath11k_dbg(ab, ATH11K_DBG_WMI, "vdev stopped for vdev id %d", vdev_id);
पूर्ण

अटल व्योम ath11k_mgmt_rx_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा mgmt_rx_event_params rx_ev = अणु0पूर्ण;
	काष्ठा ath11k *ar;
	काष्ठा ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;
	काष्ठा ieee80211_supported_band *sband;

	अगर (ath11k_pull_mgmt_rx_params_tlv(ab, skb, &rx_ev) != 0) अणु
		ath11k_warn(ab, "failed to extract mgmt rx event");
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	स_रखो(status, 0, माप(*status));

	ath11k_dbg(ab, ATH11K_DBG_MGMT, "mgmt rx event status %08x\n",
		   rx_ev.status);

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_pdev_id(ab, rx_ev.pdev_id);

	अगर (!ar) अणु
		ath11k_warn(ab, "invalid pdev_id %d in mgmt_rx_event\n",
			    rx_ev.pdev_id);
		dev_kमुक्त_skb(skb);
		जाओ निकास;
	पूर्ण

	अगर ((test_bit(ATH11K_CAC_RUNNING, &ar->dev_flags)) ||
	    (rx_ev.status & (WMI_RX_STATUS_ERR_DECRYPT |
	    WMI_RX_STATUS_ERR_KEY_CACHE_MISS | WMI_RX_STATUS_ERR_CRC))) अणु
		dev_kमुक्त_skb(skb);
		जाओ निकास;
	पूर्ण

	अगर (rx_ev.status & WMI_RX_STATUS_ERR_MIC)
		status->flag |= RX_FLAG_MMIC_ERROR;

	अगर (rx_ev.chan_freq >= ATH11K_MIN_6G_FREQ) अणु
		status->band = NL80211_BAND_6GHZ;
	पूर्ण अन्यथा अगर (rx_ev.channel >= 1 && rx_ev.channel <= 14) अणु
		status->band = NL80211_BAND_2GHZ;
	पूर्ण अन्यथा अगर (rx_ev.channel >= 36 && rx_ev.channel <= ATH11K_MAX_5G_CHAN) अणु
		status->band = NL80211_BAND_5GHZ;
	पूर्ण अन्यथा अणु
		/* Shouldn't happen unless list of advertised channels to
		 * mac80211 has been changed.
		 */
		WARN_ON_ONCE(1);
		dev_kमुक्त_skb(skb);
		जाओ निकास;
	पूर्ण

	अगर (rx_ev.phy_mode == MODE_11B &&
	    (status->band == NL80211_BAND_5GHZ || status->band == NL80211_BAND_6GHZ))
		ath11k_dbg(ab, ATH11K_DBG_WMI,
			   "wmi mgmt rx 11b (CCK) on 5/6GHz, band = %d\n", status->band);

	sband = &ar->mac.sbands[status->band];

	status->freq = ieee80211_channel_to_frequency(rx_ev.channel,
						      status->band);
	status->संकेत = rx_ev.snr + ATH11K_DEFAULT_NOISE_FLOOR;
	status->rate_idx = ath11k_mac_bitrate_to_idx(sband, rx_ev.rate / 100);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	fc = le16_to_cpu(hdr->frame_control);

	/* Firmware is guaranteed to report all essential management frames via
	 * WMI जबतक it can deliver some extra via HTT. Since there can be
	 * duplicates split the reporting wrt monitor/snअगरfing.
	 */
	status->flag |= RX_FLAG_SKIP_MONITOR;

	/* In हाल of PMF, FW delivers decrypted frames with Protected Bit set.
	 * Don't clear that. Also, FW delivers broadcast management frames
	 * (ex: group privacy action frames in mesh) as encrypted payload.
	 */
	अगर (ieee80211_has_रक्षित(hdr->frame_control) &&
	    !is_multicast_ether_addr(ieee80211_get_DA(hdr))) अणु
		status->flag |= RX_FLAG_DECRYPTED;

		अगर (!ieee80211_is_robust_mgmt_frame(skb)) अणु
			status->flag |= RX_FLAG_IV_STRIPPED |
					RX_FLAG_MMIC_STRIPPED;
			hdr->frame_control = __cpu_to_le16(fc &
					     ~IEEE80211_FCTL_PROTECTED);
		पूर्ण
	पूर्ण

	अगर (ieee80211_is_beacon(hdr->frame_control))
		ath11k_mac_handle_beacon(ar, skb);

	ath11k_dbg(ab, ATH11K_DBG_MGMT,
		   "event mgmt rx skb %pK len %d ftype %02x stype %02x\n",
		   skb, skb->len,
		   fc & IEEE80211_FCTL_FTYPE, fc & IEEE80211_FCTL_STYPE);

	ath11k_dbg(ab, ATH11K_DBG_MGMT,
		   "event mgmt rx freq %d band %d snr %d, rate_idx %d\n",
		   status->freq, status->band, status->संकेत,
		   status->rate_idx);

	ieee80211_rx_ni(ar->hw, skb);

निकास:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath11k_mgmt_tx_compl_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_mgmt_tx_compl_event tx_compl_param = अणु0पूर्ण;
	काष्ठा ath11k *ar;

	अगर (ath11k_pull_mgmt_tx_compl_param_tlv(ab, skb, &tx_compl_param) != 0) अणु
		ath11k_warn(ab, "failed to extract mgmt tx compl event");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_pdev_id(ab, tx_compl_param.pdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid pdev id %d in mgmt_tx_compl_event\n",
			    tx_compl_param.pdev_id);
		जाओ निकास;
	पूर्ण

	wmi_process_mgmt_tx_comp(ar, tx_compl_param.desc_id,
				 tx_compl_param.status);

	ath11k_dbg(ab, ATH11K_DBG_MGMT,
		   "mgmt tx compl ev pdev_id %d, desc_id %d, status %d",
		   tx_compl_param.pdev_id, tx_compl_param.desc_id,
		   tx_compl_param.status);

निकास:
	rcu_पढ़ो_unlock();
पूर्ण

अटल काष्ठा ath11k *ath11k_get_ar_on_scan_पात(काष्ठा ath11k_base *ab,
						  u32 vdev_id)
अणु
	पूर्णांक i;
	काष्ठा ath11k_pdev *pdev;
	काष्ठा ath11k *ar;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = rcu_dereference(ab->pdevs_active[i]);
		अगर (pdev && pdev->ar) अणु
			ar = pdev->ar;

			spin_lock_bh(&ar->data_lock);
			अगर (ar->scan.state == ATH11K_SCAN_ABORTING &&
			    ar->scan.vdev_id == vdev_id) अणु
				spin_unlock_bh(&ar->data_lock);
				वापस ar;
			पूर्ण
			spin_unlock_bh(&ar->data_lock);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम ath11k_scan_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k *ar;
	काष्ठा wmi_scan_event scan_ev = अणु0पूर्ण;

	अगर (ath11k_pull_scan_ev(ab, skb, &scan_ev) != 0) अणु
		ath11k_warn(ab, "failed to extract scan event");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();

	/* In हाल the scan was cancelled, ex. during पूर्णांकerface tearकरोwn,
	 * the पूर्णांकerface will not be found in active पूर्णांकerfaces.
	 * Rather, in such scenarios, iterate over the active pdev's to
	 * search 'ar' if the corresponding 'ar' scan is ABORTING and the
	 * पातing scan's vdev id matches this event info.
	 */
	अगर (scan_ev.event_type == WMI_SCAN_EVENT_COMPLETED &&
	    scan_ev.reason == WMI_SCAN_REASON_CANCELLED)
		ar = ath11k_get_ar_on_scan_पात(ab, scan_ev.vdev_id);
	अन्यथा
		ar = ath11k_mac_get_ar_by_vdev_id(ab, scan_ev.vdev_id);

	अगर (!ar) अणु
		ath11k_warn(ab, "Received scan event for unknown vdev");
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	spin_lock_bh(&ar->data_lock);

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "scan event %s type %d reason %d freq %d req_id %d scan_id %d vdev_id %d state %s (%d)\n",
		   ath11k_wmi_event_scan_type_str(scan_ev.event_type, scan_ev.reason),
		   scan_ev.event_type, scan_ev.reason, scan_ev.channel_freq,
		   scan_ev.scan_req_id, scan_ev.scan_id, scan_ev.vdev_id,
		   ath11k_scan_state_str(ar->scan.state), ar->scan.state);

	चयन (scan_ev.event_type) अणु
	हाल WMI_SCAN_EVENT_STARTED:
		ath11k_wmi_event_scan_started(ar);
		अवरोध;
	हाल WMI_SCAN_EVENT_COMPLETED:
		ath11k_wmi_event_scan_completed(ar);
		अवरोध;
	हाल WMI_SCAN_EVENT_BSS_CHANNEL:
		ath11k_wmi_event_scan_bss_chan(ar);
		अवरोध;
	हाल WMI_SCAN_EVENT_FOREIGN_CHAN:
		ath11k_wmi_event_scan_क्रमeign_chan(ar, scan_ev.channel_freq);
		अवरोध;
	हाल WMI_SCAN_EVENT_START_FAILED:
		ath11k_warn(ab, "received scan start failure event\n");
		ath11k_wmi_event_scan_start_failed(ar);
		अवरोध;
	हाल WMI_SCAN_EVENT_DEQUEUED:
	हाल WMI_SCAN_EVENT_PREEMPTED:
	हाल WMI_SCAN_EVENT_RESTARTED:
	हाल WMI_SCAN_EVENT_FOREIGN_CHAN_EXIT:
	शेष:
		अवरोध;
	पूर्ण

	spin_unlock_bh(&ar->data_lock);

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath11k_peer_sta_kickout_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_peer_sta_kickout_arg arg = अणुपूर्ण;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath11k_peer *peer;
	काष्ठा ath11k *ar;

	अगर (ath11k_pull_peer_sta_kickout_ev(ab, skb, &arg) != 0) अणु
		ath11k_warn(ab, "failed to extract peer sta kickout event");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();

	spin_lock_bh(&ab->base_lock);

	peer = ath11k_peer_find_by_addr(ab, arg.mac_addr);

	अगर (!peer) अणु
		ath11k_warn(ab, "peer not found %pM\n",
			    arg.mac_addr);
		जाओ निकास;
	पूर्ण

	ar = ath11k_mac_get_ar_by_vdev_id(ab, peer->vdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in peer sta kickout ev %d",
			    peer->vdev_id);
		जाओ निकास;
	पूर्ण

	sta = ieee80211_find_sta_by_अगरaddr(ar->hw,
					   arg.mac_addr, शून्य);
	अगर (!sta) अणु
		ath11k_warn(ab, "Spurious quick kickout for STA %pM\n",
			    arg.mac_addr);
		जाओ निकास;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI, "peer sta kickout event %pM",
		   arg.mac_addr);

	ieee80211_report_low_ack(sta, 10);

निकास:
	spin_unlock_bh(&ab->base_lock);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath11k_roam_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_roam_event roam_ev = अणुपूर्ण;
	काष्ठा ath11k *ar;

	अगर (ath11k_pull_roam_ev(ab, skb, &roam_ev) != 0) अणु
		ath11k_warn(ab, "failed to extract roam event");
		वापस;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "wmi roam event vdev %u reason 0x%08x rssi %d\n",
		   roam_ev.vdev_id, roam_ev.reason, roam_ev.rssi);

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_vdev_id(ab, roam_ev.vdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in roam ev %d",
			    roam_ev.vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर (roam_ev.reason >= WMI_ROAM_REASON_MAX)
		ath11k_warn(ab, "ignoring unknown roam event reason %d on vdev %i\n",
			    roam_ev.reason, roam_ev.vdev_id);

	चयन (roam_ev.reason) अणु
	हाल WMI_ROAM_REASON_BEACON_MISS:
		ath11k_mac_handle_beacon_miss(ar, roam_ev.vdev_id);
		अवरोध;
	हाल WMI_ROAM_REASON_BETTER_AP:
	हाल WMI_ROAM_REASON_LOW_RSSI:
	हाल WMI_ROAM_REASON_SUITABLE_AP_FOUND:
	हाल WMI_ROAM_REASON_HO_FAILED:
		ath11k_warn(ab, "ignoring not implemented roam event reason %d on vdev %i\n",
			    roam_ev.reason, roam_ev.vdev_id);
		अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath11k_chan_info_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_chan_info_event ch_info_ev = अणु0पूर्ण;
	काष्ठा ath11k *ar;
	काष्ठा survey_info *survey;
	पूर्णांक idx;
	/* HW channel counters frequency value in hertz */
	u32 cc_freq_hz = ab->cc_freq_hz;

	अगर (ath11k_pull_chan_info_ev(ab, skb->data, skb->len, &ch_info_ev) != 0) अणु
		ath11k_warn(ab, "failed to extract chan info event");
		वापस;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "chan info vdev_id %d err_code %d freq %d cmd_flags %d noise_floor %d rx_clear_count %d cycle_count %d mac_clk_mhz %d\n",
		   ch_info_ev.vdev_id, ch_info_ev.err_code, ch_info_ev.freq,
		   ch_info_ev.cmd_flags, ch_info_ev.noise_न्यूनमान,
		   ch_info_ev.rx_clear_count, ch_info_ev.cycle_count,
		   ch_info_ev.mac_clk_mhz);

	अगर (ch_info_ev.cmd_flags == WMI_CHAN_INFO_END_RESP) अणु
		ath11k_dbg(ab, ATH11K_DBG_WMI, "chan info report completed\n");
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_vdev_id(ab, ch_info_ev.vdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in chan info ev %d",
			    ch_info_ev.vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	spin_lock_bh(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
	हाल ATH11K_SCAN_STARTING:
		ath11k_warn(ab, "received chan info event without a scan request, ignoring\n");
		जाओ निकास;
	हाल ATH11K_SCAN_RUNNING:
	हाल ATH11K_SCAN_ABORTING:
		अवरोध;
	पूर्ण

	idx = freq_to_idx(ar, ch_info_ev.freq);
	अगर (idx >= ARRAY_SIZE(ar->survey)) अणु
		ath11k_warn(ab, "chan info: invalid frequency %d (idx %d out of bounds)\n",
			    ch_info_ev.freq, idx);
		जाओ निकास;
	पूर्ण

	/* If FW provides MAC घड़ी frequency in Mhz, overriding the initialized
	 * HW channel counters frequency value
	 */
	अगर (ch_info_ev.mac_clk_mhz)
		cc_freq_hz = (ch_info_ev.mac_clk_mhz * 1000);

	अगर (ch_info_ev.cmd_flags == WMI_CHAN_INFO_START_RESP) अणु
		survey = &ar->survey[idx];
		स_रखो(survey, 0, माप(*survey));
		survey->noise = ch_info_ev.noise_न्यूनमान;
		survey->filled = SURVEY_INFO_NOISE_DBM | SURVEY_INFO_TIME |
				 SURVEY_INFO_TIME_BUSY;
		survey->समय = भाग_u64(ch_info_ev.cycle_count, cc_freq_hz);
		survey->समय_busy = भाग_u64(ch_info_ev.rx_clear_count, cc_freq_hz);
	पूर्ण
निकास:
	spin_unlock_bh(&ar->data_lock);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
ath11k_pdev_bss_chan_info_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_pdev_bss_chan_info_event bss_ch_info_ev = अणुपूर्ण;
	काष्ठा survey_info *survey;
	काष्ठा ath11k *ar;
	u32 cc_freq_hz = ab->cc_freq_hz;
	u64 busy, total, tx, rx, rx_bss;
	पूर्णांक idx;

	अगर (ath11k_pull_pdev_bss_chan_info_ev(ab, skb, &bss_ch_info_ev) != 0) अणु
		ath11k_warn(ab, "failed to extract pdev bss chan info event");
		वापस;
	पूर्ण

	busy = (u64)(bss_ch_info_ev.rx_clear_count_high) << 32 |
			bss_ch_info_ev.rx_clear_count_low;

	total = (u64)(bss_ch_info_ev.cycle_count_high) << 32 |
			bss_ch_info_ev.cycle_count_low;

	tx = (u64)(bss_ch_info_ev.tx_cycle_count_high) << 32 |
			bss_ch_info_ev.tx_cycle_count_low;

	rx = (u64)(bss_ch_info_ev.rx_cycle_count_high) << 32 |
			bss_ch_info_ev.rx_cycle_count_low;

	rx_bss = (u64)(bss_ch_info_ev.rx_bss_cycle_count_high) << 32 |
			bss_ch_info_ev.rx_bss_cycle_count_low;

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "pdev bss chan info:\n pdev_id: %d freq: %d noise: %d cycle: busy %llu total %llu tx %llu rx %llu rx_bss %llu\n",
		   bss_ch_info_ev.pdev_id, bss_ch_info_ev.freq,
		   bss_ch_info_ev.noise_न्यूनमान, busy, total,
		   tx, rx, rx_bss);

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_pdev_id(ab, bss_ch_info_ev.pdev_id);

	अगर (!ar) अणु
		ath11k_warn(ab, "invalid pdev id %d in bss_chan_info event\n",
			    bss_ch_info_ev.pdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	spin_lock_bh(&ar->data_lock);
	idx = freq_to_idx(ar, bss_ch_info_ev.freq);
	अगर (idx >= ARRAY_SIZE(ar->survey)) अणु
		ath11k_warn(ab, "bss chan info: invalid frequency %d (idx %d out of bounds)\n",
			    bss_ch_info_ev.freq, idx);
		जाओ निकास;
	पूर्ण

	survey = &ar->survey[idx];

	survey->noise     = bss_ch_info_ev.noise_न्यूनमान;
	survey->समय      = भाग_u64(total, cc_freq_hz);
	survey->समय_busy = भाग_u64(busy, cc_freq_hz);
	survey->समय_rx   = भाग_u64(rx_bss, cc_freq_hz);
	survey->समय_प्रकारx   = भाग_u64(tx, cc_freq_hz);
	survey->filled   |= (SURVEY_INFO_NOISE_DBM |
			     SURVEY_INFO_TIME |
			     SURVEY_INFO_TIME_BUSY |
			     SURVEY_INFO_TIME_RX |
			     SURVEY_INFO_TIME_TX);
निकास:
	spin_unlock_bh(&ar->data_lock);
	complete(&ar->bss_survey_करोne);

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath11k_vdev_install_key_compl_event(काष्ठा ath11k_base *ab,
						काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_vdev_install_key_complete_arg install_key_compl = अणु0पूर्ण;
	काष्ठा ath11k *ar;

	अगर (ath11k_pull_vdev_install_key_compl_ev(ab, skb, &install_key_compl) != 0) अणु
		ath11k_warn(ab, "failed to extract install key compl event");
		वापस;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "vdev install key ev idx %d flags %08x macaddr %pM status %d\n",
		   install_key_compl.key_idx, install_key_compl.key_flags,
		   install_key_compl.macaddr, install_key_compl.status);

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_vdev_id(ab, install_key_compl.vdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in install key compl ev %d",
			    install_key_compl.vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	ar->install_key_status = 0;

	अगर (install_key_compl.status != WMI_VDEV_INSTALL_KEY_COMPL_STATUS_SUCCESS) अणु
		ath11k_warn(ab, "install key failed for %pM status %d\n",
			    install_key_compl.macaddr, install_key_compl.status);
		ar->install_key_status = install_key_compl.status;
	पूर्ण

	complete(&ar->install_key_करोne);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath11k_service_available_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_service_available_event *ev;
	पूर्णांक ret;
	पूर्णांक i, j;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस;
	पूर्ण

	ev = tb[WMI_TAG_SERVICE_AVAILABLE_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch svc available ev");
		kमुक्त(tb);
		वापस;
	पूर्ण

	/* TODO: Use wmi_service_segment_offset inक्रमmation to get the service
	 * especially when more services are advertised in multiple sevice
	 * available events.
	 */
	क्रम (i = 0, j = WMI_MAX_SERVICE;
	     i < WMI_SERVICE_SEGMENT_BM_SIZE32 && j < WMI_MAX_EXT_SERVICE;
	     i++) अणु
		करो अणु
			अगर (ev->wmi_service_segment_biपंचांगap[i] &
			    BIT(j % WMI_AVAIL_SERVICE_BITS_IN_SIZE32))
				set_bit(j, ab->wmi_ab.svc_map);
		पूर्ण जबतक (++j % WMI_AVAIL_SERVICE_BITS_IN_SIZE32);
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "wmi_ext_service_bitmap 0:0x%x, 1:0x%x, 2:0x%x, 3:0x%x",
		   ev->wmi_service_segment_biपंचांगap[0], ev->wmi_service_segment_biपंचांगap[1],
		   ev->wmi_service_segment_biपंचांगap[2], ev->wmi_service_segment_biपंचांगap[3]);

	kमुक्त(tb);
पूर्ण

अटल व्योम ath11k_peer_assoc_conf_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_peer_assoc_conf_arg peer_assoc_conf = अणु0पूर्ण;
	काष्ठा ath11k *ar;

	अगर (ath11k_pull_peer_assoc_conf_ev(ab, skb, &peer_assoc_conf) != 0) अणु
		ath11k_warn(ab, "failed to extract peer assoc conf event");
		वापस;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "peer assoc conf ev vdev id %d macaddr %pM\n",
		   peer_assoc_conf.vdev_id, peer_assoc_conf.macaddr);

	rcu_पढ़ो_lock();
	ar = ath11k_mac_get_ar_by_vdev_id(ab, peer_assoc_conf.vdev_id);

	अगर (!ar) अणु
		ath11k_warn(ab, "invalid vdev id in peer assoc conf ev %d",
			    peer_assoc_conf.vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	complete(&ar->peer_assoc_करोne);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ath11k_update_stats_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	ath11k_debugfs_fw_stats_process(ab, skb);
पूर्ण

/* PDEV_CTL_FAILSAFE_CHECK_EVENT is received from FW when the frequency scanned
 * is not part of BDF CTL(Conक्रमmance test limits) table entries.
 */
अटल व्योम ath11k_pdev_ctl_failsafe_check_event(काष्ठा ath11k_base *ab,
						 काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_pdev_ctl_failsafe_chk_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस;
	पूर्ण

	ev = tb[WMI_TAG_PDEV_CTL_FAILSAFE_CHECK_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch pdev ctl failsafe check ev");
		kमुक्त(tb);
		वापस;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "pdev ctl failsafe check ev status %d\n",
		   ev->ctl_failsafe_status);

	/* If ctl_failsafe_status is set to 1 FW will max out the Transmit घातer
	 * to 10 dBm अन्यथा the CTL घातer entry in the BDF would be picked up.
	 */
	अगर (ev->ctl_failsafe_status != 0)
		ath11k_warn(ab, "pdev ctl failsafe failure status %d",
			    ev->ctl_failsafe_status);

	kमुक्त(tb);
पूर्ण

अटल व्योम
ath11k_wmi_process_csa_चयन_count_event(काष्ठा ath11k_base *ab,
					  स्थिर काष्ठा wmi_pdev_csa_चयन_ev *ev,
					  स्थिर u32 *vdev_ids)
अणु
	पूर्णांक i;
	काष्ठा ath11k_vअगर *arvअगर;

	/* Finish CSA once the चयन count becomes शून्य */
	अगर (ev->current_चयन_count)
		वापस;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < ev->num_vdevs; i++) अणु
		arvअगर = ath11k_mac_get_arvअगर_by_vdev_id(ab, vdev_ids[i]);

		अगर (!arvअगर) अणु
			ath11k_warn(ab, "Recvd csa status for unknown vdev %d",
				    vdev_ids[i]);
			जारी;
		पूर्ण

		अगर (arvअगर->is_up && arvअगर->vअगर->csa_active)
			ieee80211_csa_finish(arvअगर->vअगर);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
ath11k_wmi_pdev_csa_चयन_count_status_event(काष्ठा ath11k_base *ab,
					      काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_pdev_csa_चयन_ev *ev;
	स्थिर u32 *vdev_ids;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस;
	पूर्ण

	ev = tb[WMI_TAG_PDEV_CSA_SWITCH_COUNT_STATUS_EVENT];
	vdev_ids = tb[WMI_TAG_ARRAY_UINT32];

	अगर (!ev || !vdev_ids) अणु
		ath11k_warn(ab, "failed to fetch pdev csa switch count ev");
		kमुक्त(tb);
		वापस;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "pdev csa switch count %d for pdev %d, num_vdevs %d",
		   ev->current_चयन_count, ev->pdev_id,
		   ev->num_vdevs);

	ath11k_wmi_process_csa_चयन_count_event(ab, ev, vdev_ids);

	kमुक्त(tb);
पूर्ण

अटल व्योम
ath11k_wmi_pdev_dfs_radar_detected_event(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_pdev_radar_ev *ev;
	काष्ठा ath11k *ar;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस;
	पूर्ण

	ev = tb[WMI_TAG_PDEV_DFS_RADAR_DETECTION_EVENT];

	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch pdev dfs radar detected ev");
		kमुक्त(tb);
		वापस;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "pdev dfs radar detected on pdev %d, detection mode %d, chan freq %d, chan_width %d, detector id %d, seg id %d, timestamp %d, chirp %d, freq offset %d, sidx %d",
		   ev->pdev_id, ev->detection_mode, ev->chan_freq, ev->chan_width,
		   ev->detector_id, ev->segment_id, ev->बारtamp, ev->is_chirp,
		   ev->freq_offset, ev->sidx);

	ar = ath11k_mac_get_ar_by_pdev_id(ab, ev->pdev_id);

	अगर (!ar) अणु
		ath11k_warn(ab, "radar detected in invalid pdev %d\n",
			    ev->pdev_id);
		जाओ निकास;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_REG, "DFS Radar Detected in pdev %d\n",
		   ev->pdev_id);

	अगर (ar->dfs_block_radar_events)
		ath11k_info(ab, "DFS Radar detected, but ignored as requested\n");
	अन्यथा
		ieee80211_radar_detected(ar->hw);

निकास:
	kमुक्त(tb);
पूर्ण

अटल व्योम
ath11k_wmi_pdev_temperature_event(काष्ठा ath11k_base *ab,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k *ar;
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_pdev_temperature_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab, "failed to parse tlv: %d\n", ret);
		वापस;
	पूर्ण

	ev = tb[WMI_TAG_PDEV_TEMPERATURE_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch pdev temp ev");
		kमुक्त(tb);
		वापस;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_WMI,
		   "pdev temperature ev temp %d pdev_id %d\n", ev->temp, ev->pdev_id);

	ar = ath11k_mac_get_ar_by_pdev_id(ab, ev->pdev_id);
	अगर (!ar) अणु
		ath11k_warn(ab, "invalid pdev id in pdev temperature ev %d", ev->pdev_id);
		kमुक्त(tb);
		वापस;
	पूर्ण

	ath11k_thermal_event_temperature(ar, ev->temp);

	kमुक्त(tb);
पूर्ण

अटल व्योम ath11k_fils_discovery_event(काष्ठा ath11k_base *ab,
					काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_fils_discovery_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab,
			    "failed to parse FILS discovery event tlv %d\n",
			    ret);
		वापस;
	पूर्ण

	ev = tb[WMI_TAG_HOST_SWFDA_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab, "failed to fetch FILS discovery event\n");
		kमुक्त(tb);
		वापस;
	पूर्ण

	ath11k_warn(ab,
		    "FILS discovery frame expected from host for vdev_id: %u, transmission scheduled at %u, next TBTT: %u\n",
		    ev->vdev_id, ev->fils_tt, ev->tbtt);

	kमुक्त(tb);
पूर्ण

अटल व्योम ath11k_probe_resp_tx_status_event(काष्ठा ath11k_base *ab,
					      काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_probe_resp_tx_status_event *ev;
	पूर्णांक ret;

	tb = ath11k_wmi_tlv_parse_alloc(ab, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath11k_warn(ab,
			    "failed to parse probe response transmission status event tlv: %d\n",
			    ret);
		वापस;
	पूर्ण

	ev = tb[WMI_TAG_OFFLOAD_PRB_RSP_TX_STATUS_EVENT];
	अगर (!ev) अणु
		ath11k_warn(ab,
			    "failed to fetch probe response transmission status event");
		kमुक्त(tb);
		वापस;
	पूर्ण

	अगर (ev->tx_status)
		ath11k_warn(ab,
			    "Probe response transmission failed for vdev_id %u, status %u\n",
			    ev->vdev_id, ev->tx_status);

	kमुक्त(tb);
पूर्ण

अटल पूर्णांक ath11k_wmi_tlv_wow_wakeup_host_parse(काष्ठा ath11k_base *ab,
						u16 tag, u16 len,
						स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_wow_ev_arg *ev = data;
	स्थिर अक्षर *wow_pg_fault;
	पूर्णांक wow_pg_len;

	चयन (tag) अणु
	हाल WMI_TAG_WOW_EVENT_INFO:
		स_नकल(ev, ptr, माप(*ev));
		ath11k_dbg(ab, ATH11K_DBG_WMI, "wow wakeup host reason %d %s\n",
			   ev->wake_reason, wow_reason(ev->wake_reason));
		अवरोध;

	हाल WMI_TAG_ARRAY_BYTE:
		अगर (ev && ev->wake_reason == WOW_REASON_PAGE_FAULT) अणु
			wow_pg_fault = ptr;
			/* the first 4 bytes are length */
			wow_pg_len = *(पूर्णांक *)wow_pg_fault;
			wow_pg_fault += माप(पूर्णांक);
			ath11k_dbg(ab, ATH11K_DBG_WMI, "wow data_len = %d\n",
				   wow_pg_len);
			ath11k_dbg_dump(ab, ATH11K_DBG_WMI,
					"wow_event_info_type packet present",
					"wow_pg_fault ",
					wow_pg_fault,
					wow_pg_len);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath11k_wmi_event_wow_wakeup_host(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_wow_ev_arg ev = अणु पूर्ण;
	पूर्णांक ret;

	ret = ath11k_wmi_tlv_iter(ab, skb->data, skb->len,
				  ath11k_wmi_tlv_wow_wakeup_host_parse,
				  &ev);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to parse wmi wow tlv: %d\n", ret);
		वापस;
	पूर्ण

	complete(&ab->wow.wakeup_completed);
पूर्ण

अटल व्योम ath11k_wmi_tlv_op_rx(काष्ठा ath11k_base *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	क्रमागत wmi_tlv_event_id id;

	cmd_hdr = (काष्ठा wmi_cmd_hdr *)skb->data;
	id = FIELD_GET(WMI_CMD_HDR_CMD_ID, (cmd_hdr->cmd_id));

	अगर (skb_pull(skb, माप(काष्ठा wmi_cmd_hdr)) == शून्य)
		जाओ out;

	चयन (id) अणु
		/* Process all the WMI events here */
	हाल WMI_SERVICE_READY_EVENTID:
		ath11k_service_पढ़ोy_event(ab, skb);
		अवरोध;
	हाल WMI_SERVICE_READY_EXT_EVENTID:
		ath11k_service_पढ़ोy_ext_event(ab, skb);
		अवरोध;
	हाल WMI_SERVICE_READY_EXT2_EVENTID:
		ath11k_service_पढ़ोy_ext2_event(ab, skb);
		अवरोध;
	हाल WMI_REG_CHAN_LIST_CC_EVENTID:
		ath11k_reg_chan_list_event(ab, skb);
		अवरोध;
	हाल WMI_READY_EVENTID:
		ath11k_पढ़ोy_event(ab, skb);
		अवरोध;
	हाल WMI_PEER_DELETE_RESP_EVENTID:
		ath11k_peer_delete_resp_event(ab, skb);
		अवरोध;
	हाल WMI_VDEV_START_RESP_EVENTID:
		ath11k_vdev_start_resp_event(ab, skb);
		अवरोध;
	हाल WMI_OFFLOAD_BCN_TX_STATUS_EVENTID:
		ath11k_bcn_tx_status_event(ab, skb);
		अवरोध;
	हाल WMI_VDEV_STOPPED_EVENTID:
		ath11k_vdev_stopped_event(ab, skb);
		अवरोध;
	हाल WMI_MGMT_RX_EVENTID:
		ath11k_mgmt_rx_event(ab, skb);
		/* mgmt_rx_event() owns the skb now! */
		वापस;
	हाल WMI_MGMT_TX_COMPLETION_EVENTID:
		ath11k_mgmt_tx_compl_event(ab, skb);
		अवरोध;
	हाल WMI_SCAN_EVENTID:
		ath11k_scan_event(ab, skb);
		अवरोध;
	हाल WMI_PEER_STA_KICKOUT_EVENTID:
		ath11k_peer_sta_kickout_event(ab, skb);
		अवरोध;
	हाल WMI_ROAM_EVENTID:
		ath11k_roam_event(ab, skb);
		अवरोध;
	हाल WMI_CHAN_INFO_EVENTID:
		ath11k_chan_info_event(ab, skb);
		अवरोध;
	हाल WMI_PDEV_BSS_CHAN_INFO_EVENTID:
		ath11k_pdev_bss_chan_info_event(ab, skb);
		अवरोध;
	हाल WMI_VDEV_INSTALL_KEY_COMPLETE_EVENTID:
		ath11k_vdev_install_key_compl_event(ab, skb);
		अवरोध;
	हाल WMI_SERVICE_AVAILABLE_EVENTID:
		ath11k_service_available_event(ab, skb);
		अवरोध;
	हाल WMI_PEER_ASSOC_CONF_EVENTID:
		ath11k_peer_assoc_conf_event(ab, skb);
		अवरोध;
	हाल WMI_UPDATE_STATS_EVENTID:
		ath11k_update_stats_event(ab, skb);
		अवरोध;
	हाल WMI_PDEV_CTL_FAILSAFE_CHECK_EVENTID:
		ath11k_pdev_ctl_failsafe_check_event(ab, skb);
		अवरोध;
	हाल WMI_PDEV_CSA_SWITCH_COUNT_STATUS_EVENTID:
		ath11k_wmi_pdev_csa_चयन_count_status_event(ab, skb);
		अवरोध;
	हाल WMI_PDEV_TEMPERATURE_EVENTID:
		ath11k_wmi_pdev_temperature_event(ab, skb);
		अवरोध;
	हाल WMI_PDEV_DMA_RING_BUF_RELEASE_EVENTID:
		ath11k_wmi_pdev_dma_ring_buf_release_event(ab, skb);
		अवरोध;
	हाल WMI_HOST_FILS_DISCOVERY_EVENTID:
		ath11k_fils_discovery_event(ab, skb);
		अवरोध;
	हाल WMI_OFFLOAD_PROB_RESP_TX_STATUS_EVENTID:
		ath11k_probe_resp_tx_status_event(ab, skb);
		अवरोध;
	/* add Unsupported events here */
	हाल WMI_TBTTOFFSET_EXT_UPDATE_EVENTID:
	हाल WMI_PEER_OPER_MODE_CHANGE_EVENTID:
	हाल WMI_TWT_ENABLE_EVENTID:
	हाल WMI_TWT_DISABLE_EVENTID:
	हाल WMI_PDEV_DMA_RING_CFG_RSP_EVENTID:
		ath11k_dbg(ab, ATH11K_DBG_WMI,
			   "ignoring unsupported event 0x%x\n", id);
		अवरोध;
	हाल WMI_PDEV_DFS_RADAR_DETECTION_EVENTID:
		ath11k_wmi_pdev_dfs_radar_detected_event(ab, skb);
		अवरोध;
	हाल WMI_VDEV_DELETE_RESP_EVENTID:
		ath11k_vdev_delete_resp_event(ab, skb);
		अवरोध;
	हाल WMI_WOW_WAKEUP_HOST_EVENTID:
		ath11k_wmi_event_wow_wakeup_host(ab, skb);
		अवरोध;
	/* TODO: Add reमुख्यing events */
	शेष:
		ath11k_dbg(ab, ATH11K_DBG_WMI, "Unknown eventid: 0x%x\n", id);
		अवरोध;
	पूर्ण

out:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक ath11k_connect_pdev_htc_service(काष्ठा ath11k_base *ab,
					   u32 pdev_idx)
अणु
	पूर्णांक status;
	u32 svc_id[] = अणु ATH11K_HTC_SVC_ID_WMI_CONTROL,
			 ATH11K_HTC_SVC_ID_WMI_CONTROL_MAC1,
			 ATH11K_HTC_SVC_ID_WMI_CONTROL_MAC2 पूर्ण;

	काष्ठा ath11k_htc_svc_conn_req conn_req;
	काष्ठा ath11k_htc_svc_conn_resp conn_resp;

	स_रखो(&conn_req, 0, माप(conn_req));
	स_रखो(&conn_resp, 0, माप(conn_resp));

	/* these fields are the same क्रम all service endpoपूर्णांकs */
	conn_req.ep_ops.ep_tx_complete = ath11k_wmi_htc_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath11k_wmi_tlv_op_rx;
	conn_req.ep_ops.ep_tx_credits = ath11k_wmi_op_ep_tx_credits;

	/* connect to control service */
	conn_req.service_id = svc_id[pdev_idx];

	status = ath11k_htc_connect_service(&ab->htc, &conn_req, &conn_resp);
	अगर (status) अणु
		ath11k_warn(ab, "failed to connect to WMI CONTROL service status: %d\n",
			    status);
		वापस status;
	पूर्ण

	ab->wmi_ab.wmi_endpoपूर्णांक_id[pdev_idx] = conn_resp.eid;
	ab->wmi_ab.wmi[pdev_idx].eid = conn_resp.eid;
	ab->wmi_ab.max_msg_len[pdev_idx] = conn_resp.max_msg_len;

	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_wmi_send_unit_test_cmd(काष्ठा ath11k *ar,
			      काष्ठा wmi_unit_test_cmd ut_cmd,
			      u32 *test_args)
अणु
	काष्ठा ath11k_pdev_wmi *wmi = ar->wmi;
	काष्ठा wmi_unit_test_cmd *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	u32 *ut_cmd_args;
	पूर्णांक buf_len, arg_len;
	पूर्णांक ret;
	पूर्णांक i;

	arg_len = माप(u32) * ut_cmd.num_args;
	buf_len = माप(ut_cmd) + arg_len + TLV_HDR_SIZE;

	skb = ath11k_wmi_alloc_skb(wmi->wmi_ab, buf_len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_unit_test_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_UNIT_TEST_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(ut_cmd) - TLV_HDR_SIZE);

	cmd->vdev_id = ut_cmd.vdev_id;
	cmd->module_id = ut_cmd.module_id;
	cmd->num_args = ut_cmd.num_args;
	cmd->diag_token = ut_cmd.diag_token;

	ptr = skb->data + माप(ut_cmd);

	tlv = ptr;
	tlv->header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_ARRAY_UINT32) |
		      FIELD_PREP(WMI_TLV_LEN, arg_len);

	ptr += TLV_HDR_SIZE;

	ut_cmd_args = ptr;
	क्रम (i = 0; i < ut_cmd.num_args; i++)
		ut_cmd_args[i] = test_args[i];

	ret = ath11k_wmi_cmd_send(wmi, skb, WMI_UNIT_TEST_CMDID);

	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send WMI_UNIT_TEST CMD :%d\n",
			    ret);
		dev_kमुक्त_skb(skb);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
		   "WMI unit test : module %d vdev %d n_args %d token %d\n",
		   cmd->module_id, cmd->vdev_id, cmd->num_args,
		   cmd->diag_token);

	वापस ret;
पूर्ण

पूर्णांक ath11k_wmi_simulate_radar(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_vअगर *arvअगर;
	u32 dfs_args[DFS_MAX_TEST_ARGS];
	काष्ठा wmi_unit_test_cmd wmi_ut;
	bool arvअगर_found = false;

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		अगर (arvअगर->is_started && arvअगर->vdev_type == WMI_VDEV_TYPE_AP) अणु
			arvअगर_found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!arvअगर_found)
		वापस -EINVAL;

	dfs_args[DFS_TEST_CMDID] = 0;
	dfs_args[DFS_TEST_PDEV_ID] = ar->pdev->pdev_id;
	/* Currently we could pass segment_id(b0 - b1), chirp(b2)
	 * freq offset (b3 - b10) to unit test. For simulation
	 * purpose this can be set to 0 which is valid.
	 */
	dfs_args[DFS_TEST_RADAR_PARAM] = 0;

	wmi_ut.vdev_id = arvअगर->vdev_id;
	wmi_ut.module_id = DFS_UNIT_TEST_MODULE;
	wmi_ut.num_args = DFS_MAX_TEST_ARGS;
	wmi_ut.diag_token = DFS_UNIT_TEST_TOKEN;

	ath11k_dbg(ar->ab, ATH11K_DBG_REG, "Triggering Radar Simulation\n");

	वापस ath11k_wmi_send_unit_test_cmd(ar, wmi_ut, dfs_args);
पूर्ण

पूर्णांक ath11k_wmi_connect(काष्ठा ath11k_base *ab)
अणु
	u32 i;
	u8 wmi_ep_count;

	wmi_ep_count = ab->htc.wmi_ep_count;
	अगर (wmi_ep_count > ab->hw_params.max_radios)
		वापस -1;

	क्रम (i = 0; i < wmi_ep_count; i++)
		ath11k_connect_pdev_htc_service(ab, i);

	वापस 0;
पूर्ण

अटल व्योम ath11k_wmi_pdev_detach(काष्ठा ath11k_base *ab, u8 pdev_id)
अणु
	अगर (WARN_ON(pdev_id >= MAX_RADIOS))
		वापस;

	/* TODO: Deinit any pdev specअगरic wmi resource */
पूर्ण

पूर्णांक ath11k_wmi_pdev_attach(काष्ठा ath11k_base *ab,
			   u8 pdev_id)
अणु
	काष्ठा ath11k_pdev_wmi *wmi_handle;

	अगर (pdev_id >= ab->hw_params.max_radios)
		वापस -EINVAL;

	wmi_handle = &ab->wmi_ab.wmi[pdev_id];

	wmi_handle->wmi_ab = &ab->wmi_ab;

	ab->wmi_ab.ab = ab;
	/* TODO: Init reमुख्यing resource specअगरic to pdev */

	वापस 0;
पूर्ण

पूर्णांक ath11k_wmi_attach(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक ret;

	ret = ath11k_wmi_pdev_attach(ab, 0);
	अगर (ret)
		वापस ret;

	ab->wmi_ab.ab = ab;
	ab->wmi_ab.preferred_hw_mode = WMI_HOST_HW_MODE_MAX;

	/* It's overwritten when service_ext_पढ़ोy is handled */
	अगर (ab->hw_params.single_pdev_only)
		ab->wmi_ab.preferred_hw_mode = WMI_HOST_HW_MODE_SINGLE;

	/* TODO: Init reमुख्यing wmi soc resources required */
	init_completion(&ab->wmi_ab.service_पढ़ोy);
	init_completion(&ab->wmi_ab.unअगरied_पढ़ोy);

	वापस 0;
पूर्ण

व्योम ath11k_wmi_detach(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	/* TODO: Deinit wmi resource specअगरic to SOC as required */

	क्रम (i = 0; i < ab->htc.wmi_ep_count; i++)
		ath11k_wmi_pdev_detach(ab, i);

	ath11k_wmi_मुक्त_dbring_caps(ab);
पूर्ण

पूर्णांक ath11k_wmi_wow_host_wakeup_ind(काष्ठा ath11k *ar)
अणु
	काष्ठा wmi_wow_host_wakeup_ind *cmd;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;

	len = माप(*cmd);
	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_wow_host_wakeup_ind *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG,
				     WMI_TAG_WOW_HOSTWAKEUP_FROM_SLEEP_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "wmi tlv wow host wakeup ind\n");

	वापस ath11k_wmi_cmd_send(ar->wmi, skb, WMI_WOW_HOSTWAKEUP_FROM_SLEEP_CMDID);
पूर्ण

पूर्णांक ath11k_wmi_wow_enable(काष्ठा ath11k *ar)
अणु
	काष्ठा wmi_wow_enable_cmd *cmd;
	काष्ठा sk_buff *skb;
	पूर्णांक len;

	len = माप(*cmd);
	skb = ath11k_wmi_alloc_skb(ar->wmi->wmi_ab, len);
	अगर (!skb)
		वापस -ENOMEM;

	cmd = (काष्ठा wmi_wow_enable_cmd *)skb->data;
	cmd->tlv_header = FIELD_PREP(WMI_TLV_TAG, WMI_TAG_WOW_ENABLE_CMD) |
			  FIELD_PREP(WMI_TLV_LEN, माप(*cmd) - TLV_HDR_SIZE);

	cmd->enable = 1;
	cmd->छोड़ो_अगरace_config = WOW_IFACE_PAUSE_ENABLED;
	ath11k_dbg(ar->ab, ATH11K_DBG_WMI, "wmi tlv wow enable\n");

	वापस ath11k_wmi_cmd_send(ar->wmi, skb, WMI_WOW_ENABLE_CMDID);
पूर्ण
