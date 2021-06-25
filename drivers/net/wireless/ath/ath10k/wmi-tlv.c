<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "mac.h"
#समावेश "hw.h"
#समावेश "wmi.h"
#समावेश "wmi-ops.h"
#समावेश "wmi-tlv.h"
#समावेश "p2p.h"
#समावेश "testmode.h"
#समावेश <linux/bitfield.h>

/***************/
/* TLV helpers */
/**************/

काष्ठा wmi_tlv_policy अणु
	माप_प्रकार min_len;
पूर्ण;

अटल स्थिर काष्ठा wmi_tlv_policy wmi_tlv_policies[] = अणु
	[WMI_TLV_TAG_ARRAY_BYTE]
		= अणु .min_len = 0 पूर्ण,
	[WMI_TLV_TAG_ARRAY_UINT32]
		= अणु .min_len = 0 पूर्ण,
	[WMI_TLV_TAG_STRUCT_SCAN_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_scan_event) पूर्ण,
	[WMI_TLV_TAG_STRUCT_MGMT_RX_HDR]
		= अणु .min_len = माप(काष्ठा wmi_tlv_mgmt_rx_ev) पूर्ण,
	[WMI_TLV_TAG_STRUCT_CHAN_INFO_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_chan_info_event) पूर्ण,
	[WMI_TLV_TAG_STRUCT_VDEV_START_RESPONSE_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_vdev_start_response_event) पूर्ण,
	[WMI_TLV_TAG_STRUCT_PEER_STA_KICKOUT_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_peer_sta_kickout_event) पूर्ण,
	[WMI_TLV_TAG_STRUCT_HOST_SWBA_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_host_swba_event) पूर्ण,
	[WMI_TLV_TAG_STRUCT_TIM_INFO]
		= अणु .min_len = माप(काष्ठा wmi_tim_info) पूर्ण,
	[WMI_TLV_TAG_STRUCT_P2P_NOA_INFO]
		= अणु .min_len = माप(काष्ठा wmi_p2p_noa_info) पूर्ण,
	[WMI_TLV_TAG_STRUCT_SERVICE_READY_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_tlv_svc_rdy_ev) पूर्ण,
	[WMI_TLV_TAG_STRUCT_HAL_REG_CAPABILITIES]
		= अणु .min_len = माप(काष्ठा hal_reg_capabilities) पूर्ण,
	[WMI_TLV_TAG_STRUCT_WLAN_HOST_MEM_REQ]
		= अणु .min_len = माप(काष्ठा wlan_host_mem_req) पूर्ण,
	[WMI_TLV_TAG_STRUCT_READY_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_tlv_rdy_ev) पूर्ण,
	[WMI_TLV_TAG_STRUCT_OFFLOAD_BCN_TX_STATUS_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_tlv_bcn_tx_status_ev) पूर्ण,
	[WMI_TLV_TAG_STRUCT_DIAG_DATA_CONTAINER_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_tlv_diag_data_ev) पूर्ण,
	[WMI_TLV_TAG_STRUCT_P2P_NOA_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_tlv_p2p_noa_ev) पूर्ण,
	[WMI_TLV_TAG_STRUCT_ROAM_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_tlv_roam_ev) पूर्ण,
	[WMI_TLV_TAG_STRUCT_WOW_EVENT_INFO]
		= अणु .min_len = माप(काष्ठा wmi_tlv_wow_event_info) पूर्ण,
	[WMI_TLV_TAG_STRUCT_TX_PAUSE_EVENT]
		= अणु .min_len = माप(काष्ठा wmi_tlv_tx_छोड़ो_ev) पूर्ण,
पूर्ण;

अटल पूर्णांक
ath10k_wmi_tlv_iter(काष्ठा ath10k *ar, स्थिर व्योम *ptr, माप_प्रकार len,
		    पूर्णांक (*iter)(काष्ठा ath10k *ar, u16 tag, u16 len,
				स्थिर व्योम *ptr, व्योम *data),
		    व्योम *data)
अणु
	स्थिर व्योम *begin = ptr;
	स्थिर काष्ठा wmi_tlv *tlv;
	u16 tlv_tag, tlv_len;
	पूर्णांक ret;

	जबतक (len > 0) अणु
		अगर (len < माप(*tlv)) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI,
				   "wmi tlv parse failure at byte %zd (%zu bytes left, %zu expected)\n",
				   ptr - begin, len, माप(*tlv));
			वापस -EINVAL;
		पूर्ण

		tlv = ptr;
		tlv_tag = __le16_to_cpu(tlv->tag);
		tlv_len = __le16_to_cpu(tlv->len);
		ptr += माप(*tlv);
		len -= माप(*tlv);

		अगर (tlv_len > len) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI,
				   "wmi tlv parse failure of tag %u at byte %zd (%zu bytes left, %u expected)\n",
				   tlv_tag, ptr - begin, len, tlv_len);
			वापस -EINVAL;
		पूर्ण

		अगर (tlv_tag < ARRAY_SIZE(wmi_tlv_policies) &&
		    wmi_tlv_policies[tlv_tag].min_len &&
		    wmi_tlv_policies[tlv_tag].min_len > tlv_len) अणु
			ath10k_dbg(ar, ATH10K_DBG_WMI,
				   "wmi tlv parse failure of tag %u at byte %zd (%u bytes is less than min length %zu)\n",
				   tlv_tag, ptr - begin, tlv_len,
				   wmi_tlv_policies[tlv_tag].min_len);
			वापस -EINVAL;
		पूर्ण

		ret = iter(ar, tlv_tag, tlv_len, ptr, data);
		अगर (ret)
			वापस ret;

		ptr += tlv_len;
		len -= tlv_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_iter_parse(काष्ठा ath10k *ar, u16 tag, u16 len,
				     स्थिर व्योम *ptr, व्योम *data)
अणु
	स्थिर व्योम **tb = data;

	अगर (tag < WMI_TLV_TAG_MAX)
		tb[tag] = ptr;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_parse(काष्ठा ath10k *ar, स्थिर व्योम **tb,
				स्थिर व्योम *ptr, माप_प्रकार len)
अणु
	वापस ath10k_wmi_tlv_iter(ar, ptr, len, ath10k_wmi_tlv_iter_parse,
				   (व्योम *)tb);
पूर्ण

अटल स्थिर व्योम **
ath10k_wmi_tlv_parse_alloc(काष्ठा ath10k *ar, स्थिर व्योम *ptr,
			   माप_प्रकार len, gfp_t gfp)
अणु
	स्थिर व्योम **tb;
	पूर्णांक ret;

	tb = kसुस्मृति(WMI_TLV_TAG_MAX, माप(*tb), gfp);
	अगर (!tb)
		वापस ERR_PTR(-ENOMEM);

	ret = ath10k_wmi_tlv_parse(ar, tb, ptr, len);
	अगर (ret) अणु
		kमुक्त(tb);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस tb;
पूर्ण

अटल u16 ath10k_wmi_tlv_len(स्थिर व्योम *ptr)
अणु
	वापस __le16_to_cpu((((स्थिर काष्ठा wmi_tlv *)ptr) - 1)->len);
पूर्ण

/**************/
/* TLV events */
/**************/
अटल पूर्णांक ath10k_wmi_tlv_event_bcn_tx_status(काष्ठा ath10k *ar,
					      काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_bcn_tx_status_ev *ev;
	काष्ठा ath10k_vअगर *arvअगर;
	u32 vdev_id, tx_status;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_OFFLOAD_BCN_TX_STATUS_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	tx_status = __le32_to_cpu(ev->tx_status);
	vdev_id = __le32_to_cpu(ev->vdev_id);

	चयन (tx_status) अणु
	हाल WMI_TLV_BCN_TX_STATUS_OK:
		अवरोध;
	हाल WMI_TLV_BCN_TX_STATUS_XRETRY:
	हाल WMI_TLV_BCN_TX_STATUS_DROP:
	हाल WMI_TLV_BCN_TX_STATUS_FILTERED:
		/* FIXME: It's probably worth telling mac80211 to stop the
		 * पूर्णांकerface as it is crippled.
		 */
		ath10k_warn(ar, "received bcn tmpl tx status on vdev %i: %d",
			    vdev_id, tx_status);
		अवरोध;
	पूर्ण

	arvअगर = ath10k_get_arvअगर(ar, vdev_id);
	अगर (arvअगर && arvअगर->is_up && arvअगर->vअगर->csa_active)
		ieee80211_queue_work(ar->hw, &arvअगर->ap_csa_work);

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल व्योम ath10k_wmi_tlv_event_vdev_delete_resp(काष्ठा ath10k *ar,
						  काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_VDEV_DELETE_RESP_EVENTID\n");
	complete(&ar->vdev_delete_करोne);
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_parse_peer_stats_info(काष्ठा ath10k *ar, u16 tag, u16 len,
						स्थिर व्योम *ptr, व्योम *data)
अणु
	स्थिर काष्ठा wmi_tlv_peer_stats_info *stat = ptr;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath10k_sta *arsta;

	अगर (tag != WMI_TLV_TAG_STRUCT_PEER_STATS_INFO)
		वापस -EPROTO;

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv stats peer addr %pMF rx rate code 0x%x bit rate %d kbps\n",
		   stat->peer_macaddr.addr,
		   __le32_to_cpu(stat->last_rx_rate_code),
		   __le32_to_cpu(stat->last_rx_bitrate_kbps));

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv stats tx rate code 0x%x bit rate %d kbps\n",
		   __le32_to_cpu(stat->last_tx_rate_code),
		   __le32_to_cpu(stat->last_tx_bitrate_kbps));

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta_by_अगरaddr(ar->hw, stat->peer_macaddr.addr, शून्य);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		ath10k_warn(ar, "not found station for peer stats\n");
		वापस -EINVAL;
	पूर्ण

	arsta = (काष्ठा ath10k_sta *)sta->drv_priv;
	arsta->rx_rate_code = __le32_to_cpu(stat->last_rx_rate_code);
	arsta->rx_bitrate_kbps = __le32_to_cpu(stat->last_rx_bitrate_kbps);
	arsta->tx_rate_code = __le32_to_cpu(stat->last_tx_rate_code);
	arsta->tx_bitrate_kbps = __le32_to_cpu(stat->last_tx_bitrate_kbps);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_peer_stats_info(काष्ठा ath10k *ar,
						  काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_peer_stats_info_ev *ev;
	स्थिर व्योम *data;
	u32 num_peer_stats;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_PEER_STATS_INFO_EVENT];
	data = tb[WMI_TLV_TAG_ARRAY_STRUCT];

	अगर (!ev || !data) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	num_peer_stats = __le32_to_cpu(ev->num_peers);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv peer stats info update peer vdev id %d peers %i more data %d\n",
		   __le32_to_cpu(ev->vdev_id),
		   num_peer_stats,
		   __le32_to_cpu(ev->more_data));

	ret = ath10k_wmi_tlv_iter(ar, data, ath10k_wmi_tlv_len(data),
				  ath10k_wmi_tlv_parse_peer_stats_info, शून्य);
	अगर (ret)
		ath10k_warn(ar, "failed to parse stats info tlv: %d\n", ret);

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल व्योम ath10k_wmi_tlv_event_peer_stats_info(काष्ठा ath10k *ar,
						 काष्ठा sk_buff *skb)
अणु
	ath10k_dbg(ar, ATH10K_DBG_WMI, "WMI_PEER_STATS_INFO_EVENTID\n");
	ath10k_wmi_tlv_op_pull_peer_stats_info(ar, skb);
	complete(&ar->peer_stats_info_complete);
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_event_diag_data(काष्ठा ath10k *ar,
					  काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_diag_data_ev *ev;
	स्थिर काष्ठा wmi_tlv_diag_item *item;
	स्थिर व्योम *data;
	पूर्णांक ret, num_items, len;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_DIAG_DATA_CONTAINER_EVENT];
	data = tb[WMI_TLV_TAG_ARRAY_BYTE];
	अगर (!ev || !data) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	num_items = __le32_to_cpu(ev->num_items);
	len = ath10k_wmi_tlv_len(data);

	जबतक (num_items--) अणु
		अगर (len == 0)
			अवरोध;
		अगर (len < माप(*item)) अणु
			ath10k_warn(ar, "failed to parse diag data: can't fit item header\n");
			अवरोध;
		पूर्ण

		item = data;

		अगर (len < माप(*item) + __le16_to_cpu(item->len)) अणु
			ath10k_warn(ar, "failed to parse diag data: item is too long\n");
			अवरोध;
		पूर्ण

		trace_ath10k_wmi_diag_container(ar,
						item->type,
						__le32_to_cpu(item->बारtamp),
						__le32_to_cpu(item->code),
						__le16_to_cpu(item->len),
						item->payload);

		len -= माप(*item);
		len -= roundup(__le16_to_cpu(item->len), 4);

		data += माप(*item);
		data += roundup(__le16_to_cpu(item->len), 4);
	पूर्ण

	अगर (num_items != -1 || len != 0)
		ath10k_warn(ar, "failed to parse diag data event: num_items %d len %d\n",
			    num_items, len);

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_event_diag(काष्ठा ath10k *ar,
				     काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर व्योम *data;
	पूर्णांक ret, len;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	data = tb[WMI_TLV_TAG_ARRAY_BYTE];
	अगर (!data) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण
	len = ath10k_wmi_tlv_len(data);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv diag event len %d\n", len);
	trace_ath10k_wmi_diag(ar, data, len);

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_event_p2p_noa(काष्ठा ath10k *ar,
					काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_p2p_noa_ev *ev;
	स्थिर काष्ठा wmi_p2p_noa_info *noa;
	पूर्णांक ret, vdev_id;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_P2P_NOA_EVENT];
	noa = tb[WMI_TLV_TAG_STRUCT_P2P_NOA_INFO];

	अगर (!ev || !noa) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	vdev_id = __le32_to_cpu(ev->vdev_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv p2p noa vdev_id %i descriptors %u\n",
		   vdev_id, noa->num_descriptors);

	ath10k_p2p_noa_update_by_vdev_id(ar, vdev_id, noa);
	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_event_tx_छोड़ो(काष्ठा ath10k *ar,
					 काष्ठा sk_buff *skb)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_tx_छोड़ो_ev *ev;
	पूर्णांक ret, vdev_id;
	u32 छोड़ो_id, action, vdev_map, peer_id, tid_map;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_TX_PAUSE_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	छोड़ो_id = __le32_to_cpu(ev->छोड़ो_id);
	action = __le32_to_cpu(ev->action);
	vdev_map = __le32_to_cpu(ev->vdev_map);
	peer_id = __le32_to_cpu(ev->peer_id);
	tid_map = __le32_to_cpu(ev->tid_map);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv tx pause pause_id %u action %u vdev_map 0x%08x peer_id %u tid_map 0x%08x\n",
		   छोड़ो_id, action, vdev_map, peer_id, tid_map);

	चयन (छोड़ो_id) अणु
	हाल WMI_TLV_TX_PAUSE_ID_MCC:
	हाल WMI_TLV_TX_PAUSE_ID_P2P_CLI_NOA:
	हाल WMI_TLV_TX_PAUSE_ID_P2P_GO_PS:
	हाल WMI_TLV_TX_PAUSE_ID_AP_PS:
	हाल WMI_TLV_TX_PAUSE_ID_IBSS_PS:
		क्रम (vdev_id = 0; vdev_map; vdev_id++) अणु
			अगर (!(vdev_map & BIT(vdev_id)))
				जारी;

			vdev_map &= ~BIT(vdev_id);
			ath10k_mac_handle_tx_छोड़ो_vdev(ar, vdev_id, छोड़ो_id,
							action);
		पूर्ण
		अवरोध;
	हाल WMI_TLV_TX_PAUSE_ID_AP_PEER_PS:
	हाल WMI_TLV_TX_PAUSE_ID_AP_PEER_UAPSD:
	हाल WMI_TLV_TX_PAUSE_ID_STA_ADD_BA:
	हाल WMI_TLV_TX_PAUSE_ID_HOST:
		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac ignoring unsupported tx pause id %d\n",
			   छोड़ो_id);
		अवरोध;
	शेष:
		ath10k_dbg(ar, ATH10K_DBG_MAC,
			   "mac ignoring unknown tx pause vdev %d\n",
			   छोड़ो_id);
		अवरोध;
	पूर्ण

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल व्योम ath10k_wmi_tlv_event_rfसमाप्त_state_change(काष्ठा ath10k *ar,
						     काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा wmi_tlv_rfसमाप्त_state_change_ev *ev;
	स्थिर व्योम **tb;
	bool radio;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar,
			    "failed to parse rfkill state change event: %d\n",
			    ret);
		वापस;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_RFKILL_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस;
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_MAC,
		   "wmi tlv rfkill state change gpio %d type %d radio_state %d\n",
		   __le32_to_cpu(ev->gpio_pin_num),
		   __le32_to_cpu(ev->पूर्णांक_type),
		   __le32_to_cpu(ev->radio_state));

	radio = (__le32_to_cpu(ev->radio_state) == WMI_TLV_RFKILL_RADIO_STATE_ON);

	spin_lock_bh(&ar->data_lock);

	अगर (!radio)
		ar->hw_rfसमाप्त_on = true;

	spin_unlock_bh(&ar->data_lock);

	/* notअगरy cfg80211 radio state change */
	ath10k_mac_rfसमाप्त_enable_radio(ar, radio);
	wiphy_rfसमाप्त_set_hw_state(ar->hw->wiphy, !radio);
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_event_temperature(काष्ठा ath10k *ar,
					    काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा wmi_tlv_pdev_temperature_event *ev;

	ev = (काष्ठा wmi_tlv_pdev_temperature_event *)skb->data;
	अगर (WARN_ON(skb->len < माप(*ev)))
		वापस -EPROTO;

	ath10k_thermal_event_temperature(ar, __le32_to_cpu(ev->temperature));
	वापस 0;
पूर्ण

अटल व्योम ath10k_wmi_event_tdls_peer(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_sta *station;
	स्थिर काष्ठा wmi_tlv_tdls_peer_event *ev;
	स्थिर व्योम **tb;
	काष्ठा ath10k_vअगर *arvअगर;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ath10k_warn(ar, "tdls peer failed to parse tlv");
		वापस;
	पूर्ण
	ev = tb[WMI_TLV_TAG_STRUCT_TDLS_PEER_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		ath10k_warn(ar, "tdls peer NULL event");
		वापस;
	पूर्ण

	चयन (__le32_to_cpu(ev->peer_reason)) अणु
	हाल WMI_TDLS_TEARDOWN_REASON_TX:
	हाल WMI_TDLS_TEARDOWN_REASON_RSSI:
	हाल WMI_TDLS_TEARDOWN_REASON_PTR_TIMEOUT:
		rcu_पढ़ो_lock();
		station = ieee80211_find_sta_by_अगरaddr(ar->hw,
						       ev->peer_macaddr.addr,
						       शून्य);
		अगर (!station) अणु
			ath10k_warn(ar, "did not find station from tdls peer event");
			जाओ निकास;
		पूर्ण
		arvअगर = ath10k_get_arvअगर(ar, __le32_to_cpu(ev->vdev_id));
		ieee80211_tdls_oper_request(
					arvअगर->vअगर, station->addr,
					NL80211_TDLS_TEARDOWN,
					WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE,
					GFP_ATOMIC
					);
		अवरोध;
	शेष:
		kमुक्त(tb);
		वापस;
	पूर्ण

निकास:
	rcu_पढ़ो_unlock();
	kमुक्त(tb);
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_event_peer_delete_resp(काष्ठा ath10k *ar,
						 काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_peer_delete_resp_ev_arg *arg;
	काष्ठा wmi_tlv *tlv_hdr;

	tlv_hdr = (काष्ठा wmi_tlv *)skb->data;
	arg = (काष्ठा wmi_peer_delete_resp_ev_arg *)tlv_hdr->value;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "vdev id %d", arg->vdev_id);
	ath10k_dbg(ar, ATH10K_DBG_WMI, "peer mac addr %pM", &arg->peer_addr);
	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv peer delete response\n");

	complete(&ar->peer_delete_करोne);

	वापस 0;
पूर्ण

/***********/
/* TLV ops */
/***********/

अटल व्योम ath10k_wmi_tlv_op_rx(काष्ठा ath10k *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा wmi_cmd_hdr *cmd_hdr;
	क्रमागत wmi_tlv_event_id id;
	bool consumed;

	cmd_hdr = (काष्ठा wmi_cmd_hdr *)skb->data;
	id = MS(__le32_to_cpu(cmd_hdr->cmd_id), WMI_CMD_HDR_CMD_ID);

	अगर (skb_pull(skb, माप(काष्ठा wmi_cmd_hdr)) == शून्य)
		जाओ out;

	trace_ath10k_wmi_event(ar, id, skb->data, skb->len);

	consumed = ath10k_पंचांग_event_wmi(ar, id, skb);

	/* Ready event must be handled normally also in UTF mode so that we
	 * know the UTF firmware has booted, others we are just bypass WMI
	 * events to tesपंचांगode.
	 */
	अगर (consumed && id != WMI_TLV_READY_EVENTID) अणु
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi tlv testmode consumed 0x%x\n", id);
		जाओ out;
	पूर्ण

	चयन (id) अणु
	हाल WMI_TLV_MGMT_RX_EVENTID:
		ath10k_wmi_event_mgmt_rx(ar, skb);
		/* mgmt_rx() owns the skb now! */
		वापस;
	हाल WMI_TLV_SCAN_EVENTID:
		ath10k_wmi_event_scan(ar, skb);
		अवरोध;
	हाल WMI_TLV_CHAN_INFO_EVENTID:
		ath10k_wmi_event_chan_info(ar, skb);
		अवरोध;
	हाल WMI_TLV_ECHO_EVENTID:
		ath10k_wmi_event_echo(ar, skb);
		अवरोध;
	हाल WMI_TLV_DEBUG_MESG_EVENTID:
		ath10k_wmi_event_debug_mesg(ar, skb);
		अवरोध;
	हाल WMI_TLV_UPDATE_STATS_EVENTID:
		ath10k_wmi_event_update_stats(ar, skb);
		अवरोध;
	हाल WMI_TLV_PEER_STATS_INFO_EVENTID:
		ath10k_wmi_tlv_event_peer_stats_info(ar, skb);
		अवरोध;
	हाल WMI_TLV_VDEV_START_RESP_EVENTID:
		ath10k_wmi_event_vdev_start_resp(ar, skb);
		अवरोध;
	हाल WMI_TLV_VDEV_STOPPED_EVENTID:
		ath10k_wmi_event_vdev_stopped(ar, skb);
		अवरोध;
	हाल WMI_TLV_VDEV_DELETE_RESP_EVENTID:
		ath10k_wmi_tlv_event_vdev_delete_resp(ar, skb);
		अवरोध;
	हाल WMI_TLV_PEER_STA_KICKOUT_EVENTID:
		ath10k_wmi_event_peer_sta_kickout(ar, skb);
		अवरोध;
	हाल WMI_TLV_HOST_SWBA_EVENTID:
		ath10k_wmi_event_host_swba(ar, skb);
		अवरोध;
	हाल WMI_TLV_TBTTOFFSET_UPDATE_EVENTID:
		ath10k_wmi_event_tbttoffset_update(ar, skb);
		अवरोध;
	हाल WMI_TLV_PHYERR_EVENTID:
		ath10k_wmi_event_phyerr(ar, skb);
		अवरोध;
	हाल WMI_TLV_ROAM_EVENTID:
		ath10k_wmi_event_roam(ar, skb);
		अवरोध;
	हाल WMI_TLV_PROखाता_MATCH:
		ath10k_wmi_event_profile_match(ar, skb);
		अवरोध;
	हाल WMI_TLV_DEBUG_PRINT_EVENTID:
		ath10k_wmi_event_debug_prपूर्णांक(ar, skb);
		अवरोध;
	हाल WMI_TLV_PDEV_QVIT_EVENTID:
		ath10k_wmi_event_pdev_qvit(ar, skb);
		अवरोध;
	हाल WMI_TLV_WLAN_PROखाता_DATA_EVENTID:
		ath10k_wmi_event_wlan_profile_data(ar, skb);
		अवरोध;
	हाल WMI_TLV_RTT_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_rtt_measurement_report(ar, skb);
		अवरोध;
	हाल WMI_TLV_TSF_MEASUREMENT_REPORT_EVENTID:
		ath10k_wmi_event_tsf_measurement_report(ar, skb);
		अवरोध;
	हाल WMI_TLV_RTT_ERROR_REPORT_EVENTID:
		ath10k_wmi_event_rtt_error_report(ar, skb);
		अवरोध;
	हाल WMI_TLV_WOW_WAKEUP_HOST_EVENTID:
		ath10k_wmi_event_wow_wakeup_host(ar, skb);
		अवरोध;
	हाल WMI_TLV_DCS_INTERFERENCE_EVENTID:
		ath10k_wmi_event_dcs_पूर्णांकerference(ar, skb);
		अवरोध;
	हाल WMI_TLV_PDEV_TPC_CONFIG_EVENTID:
		ath10k_wmi_event_pdev_tpc_config(ar, skb);
		अवरोध;
	हाल WMI_TLV_PDEV_FTM_INTG_EVENTID:
		ath10k_wmi_event_pdev_fपंचांग_पूर्णांकg(ar, skb);
		अवरोध;
	हाल WMI_TLV_GTK_OFFLOAD_STATUS_EVENTID:
		ath10k_wmi_event_gtk_offload_status(ar, skb);
		अवरोध;
	हाल WMI_TLV_GTK_REKEY_FAIL_EVENTID:
		ath10k_wmi_event_gtk_rekey_fail(ar, skb);
		अवरोध;
	हाल WMI_TLV_TX_DELBA_COMPLETE_EVENTID:
		ath10k_wmi_event_delba_complete(ar, skb);
		अवरोध;
	हाल WMI_TLV_TX_ADDBA_COMPLETE_EVENTID:
		ath10k_wmi_event_addba_complete(ar, skb);
		अवरोध;
	हाल WMI_TLV_VDEV_INSTALL_KEY_COMPLETE_EVENTID:
		ath10k_wmi_event_vdev_install_key_complete(ar, skb);
		अवरोध;
	हाल WMI_TLV_SERVICE_READY_EVENTID:
		ath10k_wmi_event_service_पढ़ोy(ar, skb);
		वापस;
	हाल WMI_TLV_READY_EVENTID:
		ath10k_wmi_event_पढ़ोy(ar, skb);
		अवरोध;
	हाल WMI_TLV_SERVICE_AVAILABLE_EVENTID:
		ath10k_wmi_event_service_available(ar, skb);
		अवरोध;
	हाल WMI_TLV_OFFLOAD_BCN_TX_STATUS_EVENTID:
		ath10k_wmi_tlv_event_bcn_tx_status(ar, skb);
		अवरोध;
	हाल WMI_TLV_DIAG_DATA_CONTAINER_EVENTID:
		ath10k_wmi_tlv_event_diag_data(ar, skb);
		अवरोध;
	हाल WMI_TLV_DIAG_EVENTID:
		ath10k_wmi_tlv_event_diag(ar, skb);
		अवरोध;
	हाल WMI_TLV_P2P_NOA_EVENTID:
		ath10k_wmi_tlv_event_p2p_noa(ar, skb);
		अवरोध;
	हाल WMI_TLV_TX_PAUSE_EVENTID:
		ath10k_wmi_tlv_event_tx_छोड़ो(ar, skb);
		अवरोध;
	हाल WMI_TLV_RFKILL_STATE_CHANGE_EVENTID:
		ath10k_wmi_tlv_event_rfसमाप्त_state_change(ar, skb);
		अवरोध;
	हाल WMI_TLV_PDEV_TEMPERATURE_EVENTID:
		ath10k_wmi_tlv_event_temperature(ar, skb);
		अवरोध;
	हाल WMI_TLV_TDLS_PEER_EVENTID:
		ath10k_wmi_event_tdls_peer(ar, skb);
		अवरोध;
	हाल WMI_TLV_PEER_DELETE_RESP_EVENTID:
		ath10k_wmi_tlv_event_peer_delete_resp(ar, skb);
		अवरोध;
	हाल WMI_TLV_MGMT_TX_COMPLETION_EVENTID:
		ath10k_wmi_event_mgmt_tx_compl(ar, skb);
		अवरोध;
	हाल WMI_TLV_MGMT_TX_BUNDLE_COMPLETION_EVENTID:
		ath10k_wmi_event_mgmt_tx_bundle_compl(ar, skb);
		अवरोध;
	शेष:
		ath10k_dbg(ar, ATH10K_DBG_WMI, "Unknown eventid: %d\n", id);
		अवरोध;
	पूर्ण

out:
	dev_kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_scan_ev(काष्ठा ath10k *ar,
					  काष्ठा sk_buff *skb,
					  काष्ठा wmi_scan_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_scan_event *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_SCAN_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->event_type = ev->event_type;
	arg->reason = ev->reason;
	arg->channel_freq = ev->channel_freq;
	arg->scan_req_id = ev->scan_req_id;
	arg->scan_id = ev->scan_id;
	arg->vdev_id = ev->vdev_id;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_wmi_tlv_op_pull_mgmt_tx_compl_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
					काष्ठा wmi_tlv_mgmt_tx_compl_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_mgmt_tx_compl_ev *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_MGMT_TX_COMPL_EVENT];

	arg->desc_id = ev->desc_id;
	arg->status = ev->status;
	arg->pdev_id = ev->pdev_id;
	arg->ppdu_id = ev->ppdu_id;

	अगर (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI, ar->wmi.svc_map))
		arg->ack_rssi = ev->ack_rssi;

	kमुक्त(tb);
	वापस 0;
पूर्ण

काष्ठा wmi_tlv_tx_bundle_compl_parse अणु
	स्थिर __le32 *num_reports;
	स्थिर __le32 *desc_ids;
	स्थिर __le32 *status;
	स्थिर __le32 *ppdu_ids;
	स्थिर __le32 *ack_rssi;
	bool desc_ids_करोne;
	bool status_करोne;
	bool ppdu_ids_करोne;
	bool ack_rssi_करोne;
पूर्ण;

अटल पूर्णांक
ath10k_wmi_tlv_mgmt_tx_bundle_compl_parse(काष्ठा ath10k *ar, u16 tag, u16 len,
					  स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_tx_bundle_compl_parse *bundle_tx_compl = data;

	चयन (tag) अणु
	हाल WMI_TLV_TAG_STRUCT_MGMT_TX_COMPL_BUNDLE_EVENT:
		bundle_tx_compl->num_reports = ptr;
		अवरोध;
	हाल WMI_TLV_TAG_ARRAY_UINT32:
		अगर (!bundle_tx_compl->desc_ids_करोne) अणु
			bundle_tx_compl->desc_ids_करोne = true;
			bundle_tx_compl->desc_ids = ptr;
		पूर्ण अन्यथा अगर (!bundle_tx_compl->status_करोne) अणु
			bundle_tx_compl->status_करोne = true;
			bundle_tx_compl->status = ptr;
		पूर्ण अन्यथा अगर (!bundle_tx_compl->ppdu_ids_करोne) अणु
			bundle_tx_compl->ppdu_ids_करोne = true;
			bundle_tx_compl->ppdu_ids = ptr;
		पूर्ण अन्यथा अगर (!bundle_tx_compl->ack_rssi_करोne) अणु
			bundle_tx_compl->ack_rssi_करोne = true;
			bundle_tx_compl->ack_rssi = ptr;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_mgmt_tx_bundle_compl_ev(
				काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				काष्ठा wmi_tlv_mgmt_tx_bundle_compl_ev_arg *arg)
अणु
	काष्ठा wmi_tlv_tx_bundle_compl_parse bundle_tx_compl = अणु पूर्ण;
	पूर्णांक ret;

	ret = ath10k_wmi_tlv_iter(ar, skb->data, skb->len,
				  ath10k_wmi_tlv_mgmt_tx_bundle_compl_parse,
				  &bundle_tx_compl);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!bundle_tx_compl.num_reports || !bundle_tx_compl.desc_ids ||
	    !bundle_tx_compl.status)
		वापस -EPROTO;

	arg->num_reports = *bundle_tx_compl.num_reports;
	arg->desc_ids = bundle_tx_compl.desc_ids;
	arg->status = bundle_tx_compl.status;
	arg->ppdu_ids = bundle_tx_compl.ppdu_ids;

	अगर (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI, ar->wmi.svc_map))
		arg->ack_rssi = bundle_tx_compl.ack_rssi;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_mgmt_rx_ev(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb,
					     काष्ठा wmi_mgmt_rx_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_mgmt_rx_ev *ev;
	स्थिर u8 *frame;
	u32 msdu_len;
	पूर्णांक ret, i;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_MGMT_RX_HDR];
	frame = tb[WMI_TLV_TAG_ARRAY_BYTE];

	अगर (!ev || !frame) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->channel = ev->channel;
	arg->buf_len = ev->buf_len;
	arg->status = ev->status;
	arg->snr = ev->snr;
	arg->phy_mode = ev->phy_mode;
	arg->rate = ev->rate;

	क्रम (i = 0; i < ARRAY_SIZE(ev->rssi); i++)
		arg->rssi[i] = ev->rssi[i];

	msdu_len = __le32_to_cpu(arg->buf_len);

	अगर (skb->len < (frame - skb->data) + msdu_len) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	/* shअगरt the sk_buff to poपूर्णांक to `frame` */
	skb_trim(skb, 0);
	skb_put(skb, frame - skb->data);
	skb_pull(skb, frame - skb->data);
	skb_put(skb, msdu_len);

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_ch_info_ev(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb,
					     काष्ठा wmi_ch_info_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_chan_info_event *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_CHAN_INFO_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->err_code = ev->err_code;
	arg->freq = ev->freq;
	arg->cmd_flags = ev->cmd_flags;
	arg->noise_न्यूनमान = ev->noise_न्यूनमान;
	arg->rx_clear_count = ev->rx_clear_count;
	arg->cycle_count = ev->cycle_count;
	अगर (test_bit(ATH10K_FW_FEATURE_SINGLE_CHAN_INFO_PER_CHANNEL,
		     ar->running_fw->fw_file.fw_features))
		arg->mac_clk_mhz = ev->mac_clk_mhz;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_wmi_tlv_op_pull_vdev_start_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				     काष्ठा wmi_vdev_start_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_vdev_start_response_event *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_VDEV_START_RESPONSE_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	skb_pull(skb, माप(*ev));
	arg->vdev_id = ev->vdev_id;
	arg->req_id = ev->req_id;
	arg->resp_type = ev->resp_type;
	arg->status = ev->status;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_peer_kick_ev(काष्ठा ath10k *ar,
					       काष्ठा sk_buff *skb,
					       काष्ठा wmi_peer_kick_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_peer_sta_kickout_event *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_PEER_STA_KICKOUT_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->mac_addr = ev->peer_macaddr.addr;

	kमुक्त(tb);
	वापस 0;
पूर्ण

काष्ठा wmi_tlv_swba_parse अणु
	स्थिर काष्ठा wmi_host_swba_event *ev;
	bool tim_करोne;
	bool noa_करोne;
	माप_प्रकार n_tim;
	माप_प्रकार n_noa;
	काष्ठा wmi_swba_ev_arg *arg;
पूर्ण;

अटल पूर्णांक ath10k_wmi_tlv_swba_tim_parse(काष्ठा ath10k *ar, u16 tag, u16 len,
					 स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_swba_parse *swba = data;
	काष्ठा wmi_tim_info_arg *tim_info_arg;
	स्थिर काष्ठा wmi_tim_info *tim_info_ev = ptr;

	अगर (tag != WMI_TLV_TAG_STRUCT_TIM_INFO)
		वापस -EPROTO;

	अगर (swba->n_tim >= ARRAY_SIZE(swba->arg->tim_info))
		वापस -ENOBUFS;

	अगर (__le32_to_cpu(tim_info_ev->tim_len) >
	     माप(tim_info_ev->tim_biपंचांगap)) अणु
		ath10k_warn(ar, "refusing to parse invalid swba structure\n");
		वापस -EPROTO;
	पूर्ण

	tim_info_arg = &swba->arg->tim_info[swba->n_tim];
	tim_info_arg->tim_len = tim_info_ev->tim_len;
	tim_info_arg->tim_mcast = tim_info_ev->tim_mcast;
	tim_info_arg->tim_biपंचांगap = tim_info_ev->tim_biपंचांगap;
	tim_info_arg->tim_changed = tim_info_ev->tim_changed;
	tim_info_arg->tim_num_ps_pending = tim_info_ev->tim_num_ps_pending;

	swba->n_tim++;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_swba_noa_parse(काष्ठा ath10k *ar, u16 tag, u16 len,
					 स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_swba_parse *swba = data;

	अगर (tag != WMI_TLV_TAG_STRUCT_P2P_NOA_INFO)
		वापस -EPROTO;

	अगर (swba->n_noa >= ARRAY_SIZE(swba->arg->noa_info))
		वापस -ENOBUFS;

	swba->arg->noa_info[swba->n_noa++] = ptr;
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_swba_parse(काष्ठा ath10k *ar, u16 tag, u16 len,
				     स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_swba_parse *swba = data;
	पूर्णांक ret;

	चयन (tag) अणु
	हाल WMI_TLV_TAG_STRUCT_HOST_SWBA_EVENT:
		swba->ev = ptr;
		अवरोध;
	हाल WMI_TLV_TAG_ARRAY_STRUCT:
		अगर (!swba->tim_करोne) अणु
			swba->tim_करोne = true;
			ret = ath10k_wmi_tlv_iter(ar, ptr, len,
						  ath10k_wmi_tlv_swba_tim_parse,
						  swba);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अगर (!swba->noa_करोne) अणु
			swba->noa_करोne = true;
			ret = ath10k_wmi_tlv_iter(ar, ptr, len,
						  ath10k_wmi_tlv_swba_noa_parse,
						  swba);
			अगर (ret)
				वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_swba_ev(काष्ठा ath10k *ar,
					  काष्ठा sk_buff *skb,
					  काष्ठा wmi_swba_ev_arg *arg)
अणु
	काष्ठा wmi_tlv_swba_parse swba = अणु .arg = arg पूर्ण;
	u32 map;
	माप_प्रकार n_vdevs;
	पूर्णांक ret;

	ret = ath10k_wmi_tlv_iter(ar, skb->data, skb->len,
				  ath10k_wmi_tlv_swba_parse, &swba);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!swba.ev)
		वापस -EPROTO;

	arg->vdev_map = swba.ev->vdev_map;

	क्रम (map = __le32_to_cpu(arg->vdev_map), n_vdevs = 0; map; map >>= 1)
		अगर (map & BIT(0))
			n_vdevs++;

	अगर (n_vdevs != swba.n_tim ||
	    n_vdevs != swba.n_noa)
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_phyerr_ev_hdr(काष्ठा ath10k *ar,
						काष्ठा sk_buff *skb,
						काष्ठा wmi_phyerr_hdr_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_phyerr_ev *ev;
	स्थिर व्योम *phyerrs;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_COMB_PHYERR_RX_HDR];
	phyerrs = tb[WMI_TLV_TAG_ARRAY_BYTE];

	अगर (!ev || !phyerrs) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->num_phyerrs  = __le32_to_cpu(ev->num_phyerrs);
	arg->tsf_l32 = __le32_to_cpu(ev->tsf_l32);
	arg->tsf_u32 = __le32_to_cpu(ev->tsf_u32);
	arg->buf_len = __le32_to_cpu(ev->buf_len);
	arg->phyerrs = phyerrs;

	kमुक्त(tb);
	वापस 0;
पूर्ण

#घोषणा WMI_TLV_ABI_VER_NS0 0x5F414351
#घोषणा WMI_TLV_ABI_VER_NS1 0x00004C4D
#घोषणा WMI_TLV_ABI_VER_NS2 0x00000000
#घोषणा WMI_TLV_ABI_VER_NS3 0x00000000

#घोषणा WMI_TLV_ABI_VER0_MAJOR 1
#घोषणा WMI_TLV_ABI_VER0_MINOR 0
#घोषणा WMI_TLV_ABI_VER0 ((((WMI_TLV_ABI_VER0_MAJOR) << 24) & 0xFF000000) | \
			  (((WMI_TLV_ABI_VER0_MINOR) <<  0) & 0x00FFFFFF))
#घोषणा WMI_TLV_ABI_VER1 53

अटल पूर्णांक
ath10k_wmi_tlv_parse_mem_reqs(काष्ठा ath10k *ar, u16 tag, u16 len,
			      स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_svc_rdy_ev_arg *arg = data;
	पूर्णांक i;

	अगर (tag != WMI_TLV_TAG_STRUCT_WLAN_HOST_MEM_REQ)
		वापस -EPROTO;

	क्रम (i = 0; i < ARRAY_SIZE(arg->mem_reqs); i++) अणु
		अगर (!arg->mem_reqs[i]) अणु
			arg->mem_reqs[i] = ptr;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOMEM;
पूर्ण

काष्ठा wmi_tlv_svc_rdy_parse अणु
	स्थिर काष्ठा hal_reg_capabilities *reg;
	स्थिर काष्ठा wmi_tlv_svc_rdy_ev *ev;
	स्थिर __le32 *svc_bmap;
	स्थिर काष्ठा wlan_host_mem_req *mem_reqs;
	bool svc_bmap_करोne;
	bool dbs_hw_mode_करोne;
पूर्ण;

अटल पूर्णांक ath10k_wmi_tlv_svc_rdy_parse(काष्ठा ath10k *ar, u16 tag, u16 len,
					स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_tlv_svc_rdy_parse *svc_rdy = data;

	चयन (tag) अणु
	हाल WMI_TLV_TAG_STRUCT_SERVICE_READY_EVENT:
		svc_rdy->ev = ptr;
		अवरोध;
	हाल WMI_TLV_TAG_STRUCT_HAL_REG_CAPABILITIES:
		svc_rdy->reg = ptr;
		अवरोध;
	हाल WMI_TLV_TAG_ARRAY_STRUCT:
		svc_rdy->mem_reqs = ptr;
		अवरोध;
	हाल WMI_TLV_TAG_ARRAY_UINT32:
		अगर (!svc_rdy->svc_bmap_करोne) अणु
			svc_rdy->svc_bmap_करोne = true;
			svc_rdy->svc_bmap = ptr;
		पूर्ण अन्यथा अगर (!svc_rdy->dbs_hw_mode_करोne) अणु
			svc_rdy->dbs_hw_mode_करोne = true;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_svc_rdy_ev(काष्ठा ath10k *ar,
					     काष्ठा sk_buff *skb,
					     काष्ठा wmi_svc_rdy_ev_arg *arg)
अणु
	स्थिर काष्ठा hal_reg_capabilities *reg;
	स्थिर काष्ठा wmi_tlv_svc_rdy_ev *ev;
	स्थिर __le32 *svc_bmap;
	स्थिर काष्ठा wlan_host_mem_req *mem_reqs;
	काष्ठा wmi_tlv_svc_rdy_parse svc_rdy = अणु पूर्ण;
	पूर्णांक ret;

	ret = ath10k_wmi_tlv_iter(ar, skb->data, skb->len,
				  ath10k_wmi_tlv_svc_rdy_parse, &svc_rdy);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = svc_rdy.ev;
	reg = svc_rdy.reg;
	svc_bmap = svc_rdy.svc_bmap;
	mem_reqs = svc_rdy.mem_reqs;

	अगर (!ev || !reg || !svc_bmap || !mem_reqs)
		वापस -EPROTO;

	/* This is an पूर्णांकernal ABI compatibility check क्रम WMI TLV so check it
	 * here instead of the generic WMI code.
	 */
	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv abi 0x%08x ?= 0x%08x, 0x%08x ?= 0x%08x, 0x%08x ?= 0x%08x, 0x%08x ?= 0x%08x, 0x%08x ?= 0x%08x\n",
		   __le32_to_cpu(ev->abi.abi_ver0), WMI_TLV_ABI_VER0,
		   __le32_to_cpu(ev->abi.abi_ver_ns0), WMI_TLV_ABI_VER_NS0,
		   __le32_to_cpu(ev->abi.abi_ver_ns1), WMI_TLV_ABI_VER_NS1,
		   __le32_to_cpu(ev->abi.abi_ver_ns2), WMI_TLV_ABI_VER_NS2,
		   __le32_to_cpu(ev->abi.abi_ver_ns3), WMI_TLV_ABI_VER_NS3);

	अगर (__le32_to_cpu(ev->abi.abi_ver0) != WMI_TLV_ABI_VER0 ||
	    __le32_to_cpu(ev->abi.abi_ver_ns0) != WMI_TLV_ABI_VER_NS0 ||
	    __le32_to_cpu(ev->abi.abi_ver_ns1) != WMI_TLV_ABI_VER_NS1 ||
	    __le32_to_cpu(ev->abi.abi_ver_ns2) != WMI_TLV_ABI_VER_NS2 ||
	    __le32_to_cpu(ev->abi.abi_ver_ns3) != WMI_TLV_ABI_VER_NS3) अणु
		वापस -ENOTSUPP;
	पूर्ण

	arg->min_tx_घातer = ev->hw_min_tx_घातer;
	arg->max_tx_घातer = ev->hw_max_tx_घातer;
	arg->ht_cap = ev->ht_cap_info;
	arg->vht_cap = ev->vht_cap_info;
	arg->vht_supp_mcs = ev->vht_supp_mcs;
	arg->sw_ver0 = ev->abi.abi_ver0;
	arg->sw_ver1 = ev->abi.abi_ver1;
	arg->fw_build = ev->fw_build_vers;
	arg->phy_capab = ev->phy_capability;
	arg->num_rf_chains = ev->num_rf_chains;
	arg->eeprom_rd = reg->eeprom_rd;
	arg->low_2ghz_chan = reg->low_2ghz_chan;
	arg->high_2ghz_chan = reg->high_2ghz_chan;
	arg->low_5ghz_chan = reg->low_5ghz_chan;
	arg->high_5ghz_chan = reg->high_5ghz_chan;
	arg->num_mem_reqs = ev->num_mem_reqs;
	arg->service_map = svc_bmap;
	arg->service_map_len = ath10k_wmi_tlv_len(svc_bmap);
	arg->sys_cap_info = ev->sys_cap_info;

	ret = ath10k_wmi_tlv_iter(ar, mem_reqs, ath10k_wmi_tlv_len(mem_reqs),
				  ath10k_wmi_tlv_parse_mem_reqs, arg);
	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse mem_reqs tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_rdy_ev(काष्ठा ath10k *ar,
					 काष्ठा sk_buff *skb,
					 काष्ठा wmi_rdy_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_rdy_ev *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_READY_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->sw_version = ev->abi.abi_ver0;
	arg->abi_version = ev->abi.abi_ver1;
	arg->status = ev->status;
	arg->mac_addr = ev->mac_addr.addr;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_svc_avail_parse(काष्ठा ath10k *ar, u16 tag, u16 len,
					  स्थिर व्योम *ptr, व्योम *data)
अणु
	काष्ठा wmi_svc_avail_ev_arg *arg = data;

	चयन (tag) अणु
	हाल WMI_TLV_TAG_STRUCT_SERVICE_AVAILABLE_EVENT:
		arg->service_map_ext_valid = true;
		arg->service_map_ext_len = *(__le32 *)ptr;
		arg->service_map_ext = ptr + माप(__le32);
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_svc_avail(काष्ठा ath10k *ar,
					    काष्ठा sk_buff *skb,
					    काष्ठा wmi_svc_avail_ev_arg *arg)
अणु
	पूर्णांक ret;

	ret = ath10k_wmi_tlv_iter(ar, skb->data, skb->len,
				  ath10k_wmi_tlv_svc_avail_parse, arg);

	अगर (ret) अणु
		ath10k_warn(ar, "failed to parse svc_avail tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath10k_wmi_tlv_pull_vdev_stats(स्थिर काष्ठा wmi_tlv_vdev_stats *src,
					   काष्ठा ath10k_fw_stats_vdev *dst)
अणु
	पूर्णांक i;

	dst->vdev_id = __le32_to_cpu(src->vdev_id);
	dst->beacon_snr = __le32_to_cpu(src->beacon_snr);
	dst->data_snr = __le32_to_cpu(src->data_snr);
	dst->num_rx_frames = __le32_to_cpu(src->num_rx_frames);
	dst->num_rts_fail = __le32_to_cpu(src->num_rts_fail);
	dst->num_rts_success = __le32_to_cpu(src->num_rts_success);
	dst->num_rx_err = __le32_to_cpu(src->num_rx_err);
	dst->num_rx_discard = __le32_to_cpu(src->num_rx_discard);
	dst->num_tx_not_acked = __le32_to_cpu(src->num_tx_not_acked);

	क्रम (i = 0; i < ARRAY_SIZE(src->num_tx_frames); i++)
		dst->num_tx_frames[i] =
			__le32_to_cpu(src->num_tx_frames[i]);

	क्रम (i = 0; i < ARRAY_SIZE(src->num_tx_frames_retries); i++)
		dst->num_tx_frames_retries[i] =
			__le32_to_cpu(src->num_tx_frames_retries[i]);

	क्रम (i = 0; i < ARRAY_SIZE(src->num_tx_frames_failures); i++)
		dst->num_tx_frames_failures[i] =
			__le32_to_cpu(src->num_tx_frames_failures[i]);

	क्रम (i = 0; i < ARRAY_SIZE(src->tx_rate_history); i++)
		dst->tx_rate_history[i] =
			__le32_to_cpu(src->tx_rate_history[i]);

	क्रम (i = 0; i < ARRAY_SIZE(src->beacon_rssi_history); i++)
		dst->beacon_rssi_history[i] =
			__le32_to_cpu(src->beacon_rssi_history[i]);
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_fw_stats(काष्ठा ath10k *ar,
					   काष्ठा sk_buff *skb,
					   काष्ठा ath10k_fw_stats *stats)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_stats_ev *ev;
	u32 num_peer_stats_extd;
	स्थिर व्योम *data;
	u32 num_pdev_stats;
	u32 num_vdev_stats;
	u32 num_peer_stats;
	u32 num_bcnflt_stats;
	u32 num_chan_stats;
	माप_प्रकार data_len;
	u32 stats_id;
	पूर्णांक ret;
	पूर्णांक i;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_STATS_EVENT];
	data = tb[WMI_TLV_TAG_ARRAY_BYTE];

	अगर (!ev || !data) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	data_len = ath10k_wmi_tlv_len(data);
	num_pdev_stats = __le32_to_cpu(ev->num_pdev_stats);
	num_vdev_stats = __le32_to_cpu(ev->num_vdev_stats);
	num_peer_stats = __le32_to_cpu(ev->num_peer_stats);
	num_bcnflt_stats = __le32_to_cpu(ev->num_bcnflt_stats);
	num_chan_stats = __le32_to_cpu(ev->num_chan_stats);
	stats_id = __le32_to_cpu(ev->stats_id);
	num_peer_stats_extd = __le32_to_cpu(ev->num_peer_stats_extd);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv stats update pdev %i vdev %i peer %i bcnflt %i chan %i peer_extd %i\n",
		   num_pdev_stats, num_vdev_stats, num_peer_stats,
		   num_bcnflt_stats, num_chan_stats, num_peer_stats_extd);

	क्रम (i = 0; i < num_pdev_stats; i++) अणु
		स्थिर काष्ठा wmi_pdev_stats *src;
		काष्ठा ath10k_fw_stats_pdev *dst;

		src = data;
		अगर (data_len < माप(*src)) अणु
			kमुक्त(tb);
			वापस -EPROTO;
		पूर्ण

		data += माप(*src);
		data_len -= माप(*src);

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_pdev_stats_base(&src->base, dst);
		ath10k_wmi_pull_pdev_stats_tx(&src->tx, dst);
		ath10k_wmi_pull_pdev_stats_rx(&src->rx, dst);
		list_add_tail(&dst->list, &stats->pdevs);
	पूर्ण

	क्रम (i = 0; i < num_vdev_stats; i++) अणु
		स्थिर काष्ठा wmi_tlv_vdev_stats *src;
		काष्ठा ath10k_fw_stats_vdev *dst;

		src = data;
		अगर (data_len < माप(*src)) अणु
			kमुक्त(tb);
			वापस -EPROTO;
		पूर्ण

		data += माप(*src);
		data_len -= माप(*src);

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_tlv_pull_vdev_stats(src, dst);
		list_add_tail(&dst->list, &stats->vdevs);
	पूर्ण

	क्रम (i = 0; i < num_peer_stats; i++) अणु
		स्थिर काष्ठा wmi_10x_peer_stats *src;
		काष्ठा ath10k_fw_stats_peer *dst;

		src = data;
		अगर (data_len < माप(*src)) अणु
			kमुक्त(tb);
			वापस -EPROTO;
		पूर्ण

		data += माप(*src);
		data_len -= माप(*src);

		dst = kzalloc(माप(*dst), GFP_ATOMIC);
		अगर (!dst)
			जारी;

		ath10k_wmi_pull_peer_stats(&src->old, dst);
		dst->peer_rx_rate = __le32_to_cpu(src->peer_rx_rate);

		अगर (stats_id & WMI_TLV_STAT_PEER_EXTD) अणु
			स्थिर काष्ठा wmi_tlv_peer_stats_extd *extd;
			अचिन्हित दीर्घ rx_duration_high;

			extd = data + माप(*src) * (num_peer_stats - i - 1)
			       + माप(*extd) * i;

			dst->rx_duration = __le32_to_cpu(extd->rx_duration);
			rx_duration_high = __le32_to_cpu
						(extd->rx_duration_high);

			अगर (test_bit(WMI_TLV_PEER_RX_DURATION_HIGH_VALID_BIT,
				     &rx_duration_high)) अणु
				rx_duration_high =
					FIELD_GET(WMI_TLV_PEER_RX_DURATION_HIGH_MASK,
						  rx_duration_high);
				dst->rx_duration |= (u64)rx_duration_high <<
						    WMI_TLV_PEER_RX_DURATION_SHIFT;
			पूर्ण
		पूर्ण

		list_add_tail(&dst->list, &stats->peers);
	पूर्ण

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_roam_ev(काष्ठा ath10k *ar,
					  काष्ठा sk_buff *skb,
					  काष्ठा wmi_roam_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_roam_ev *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_ROAM_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->vdev_id = ev->vdev_id;
	arg->reason = ev->reason;
	arg->rssi = ev->rssi;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_wmi_tlv_op_pull_wow_ev(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
			      काष्ठा wmi_wow_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_tlv_wow_event_info *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_WOW_EVENT_INFO];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->vdev_id = __le32_to_cpu(ev->vdev_id);
	arg->flag = __le32_to_cpu(ev->flag);
	arg->wake_reason = __le32_to_cpu(ev->wake_reason);
	arg->data_len = __le32_to_cpu(ev->data_len);

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_pull_echo_ev(काष्ठा ath10k *ar,
					  काष्ठा sk_buff *skb,
					  काष्ठा wmi_echo_ev_arg *arg)
अणु
	स्थिर व्योम **tb;
	स्थिर काष्ठा wmi_echo_event *ev;
	पूर्णांक ret;

	tb = ath10k_wmi_tlv_parse_alloc(ar, skb->data, skb->len, GFP_ATOMIC);
	अगर (IS_ERR(tb)) अणु
		ret = PTR_ERR(tb);
		ath10k_warn(ar, "failed to parse tlv: %d\n", ret);
		वापस ret;
	पूर्ण

	ev = tb[WMI_TLV_TAG_STRUCT_ECHO_EVENT];
	अगर (!ev) अणु
		kमुक्त(tb);
		वापस -EPROTO;
	पूर्ण

	arg->value = ev->value;

	kमुक्त(tb);
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pdev_suspend(काष्ठा ath10k *ar, u32 opt)
अणु
	काष्ठा wmi_tlv_pdev_suspend *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_SUSPEND_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->opt = __cpu_to_le32(opt);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv pdev suspend\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pdev_resume(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_tlv_resume_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_RESUME_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->reserved = __cpu_to_le32(0);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv pdev resume\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pdev_set_rd(काष्ठा ath10k *ar,
				  u16 rd, u16 rd2g, u16 rd5g,
				  u16 ctl2g, u16 ctl5g,
				  क्रमागत wmi_dfs_region dfs_reg)
अणु
	काष्ठा wmi_tlv_pdev_set_rd_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_SET_REGDOMAIN_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->regd = __cpu_to_le32(rd);
	cmd->regd_2ghz = __cpu_to_le32(rd2g);
	cmd->regd_5ghz = __cpu_to_le32(rd5g);
	cmd->conक्रमm_limit_2ghz = __cpu_to_le32(ctl2g);
	cmd->conक्रमm_limit_5ghz = __cpu_to_le32(ctl5g);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv pdev set rd\n");
	वापस skb;
पूर्ण

अटल क्रमागत wmi_txbf_conf ath10k_wmi_tlv_txbf_conf_scheme(काष्ठा ath10k *ar)
अणु
	वापस WMI_TXBF_CONF_AFTER_ASSOC;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pdev_set_param(काष्ठा ath10k *ar, u32 param_id,
				     u32 param_value)
अणु
	काष्ठा wmi_tlv_pdev_set_param_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_SET_PARAM_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->param_id = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(param_value);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv pdev set param %d value 0x%x\n",
		   param_id, param_value);
	वापस skb;
पूर्ण

अटल व्योम
ath10k_wmi_tlv_put_host_mem_chunks(काष्ठा ath10k *ar, व्योम *host_mem_chunks)
अणु
	काष्ठा host_memory_chunk_tlv *chunk;
	काष्ठा wmi_tlv *tlv;
	dma_addr_t paddr;
	पूर्णांक i;
	__le16 tlv_len, tlv_tag;

	tlv_tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WLAN_HOST_MEMORY_CHUNK);
	tlv_len = __cpu_to_le16(माप(*chunk));
	क्रम (i = 0; i < ar->wmi.num_mem_chunks; i++) अणु
		tlv = host_mem_chunks;
		tlv->tag = tlv_tag;
		tlv->len = tlv_len;
		chunk = (व्योम *)tlv->value;

		chunk->ptr = __cpu_to_le32(ar->wmi.mem_chunks[i].paddr);
		chunk->size = __cpu_to_le32(ar->wmi.mem_chunks[i].len);
		chunk->req_id = __cpu_to_le32(ar->wmi.mem_chunks[i].req_id);

		अगर (test_bit(WMI_SERVICE_SUPPORT_EXTEND_ADDRESS,
			     ar->wmi.svc_map)) अणु
			paddr = ar->wmi.mem_chunks[i].paddr;
			chunk->ptr_high = __cpu_to_le32(upper_32_bits(paddr));
		पूर्ण

		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi-tlv chunk %d len %d, addr 0x%llx, id 0x%x\n",
			   i,
			   ar->wmi.mem_chunks[i].len,
			   (अचिन्हित दीर्घ दीर्घ)ar->wmi.mem_chunks[i].paddr,
			   ar->wmi.mem_chunks[i].req_id);

		host_mem_chunks += माप(*tlv);
		host_mem_chunks += माप(*chunk);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *ath10k_wmi_tlv_op_gen_init(काष्ठा ath10k *ar)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा wmi_tlv *tlv;
	काष्ठा wmi_tlv_init_cmd *cmd;
	काष्ठा wmi_tlv_resource_config *cfg;
	व्योम *chunks;
	माप_प्रकार len, chunks_len;
	व्योम *ptr;

	chunks_len = ar->wmi.num_mem_chunks *
		     (माप(काष्ठा host_memory_chunk_tlv) + माप(*tlv));
	len = (माप(*tlv) + माप(*cmd)) +
	      (माप(*tlv) + माप(*cfg)) +
	      (माप(*tlv) + chunks_len);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = skb->data;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_INIT_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_RESOURCE_CONFIG);
	tlv->len = __cpu_to_le16(माप(*cfg));
	cfg = (व्योम *)tlv->value;
	ptr += माप(*tlv);
	ptr += माप(*cfg);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(chunks_len);
	chunks = (व्योम *)tlv->value;

	ptr += माप(*tlv);
	ptr += chunks_len;

	cmd->abi.abi_ver0 = __cpu_to_le32(WMI_TLV_ABI_VER0);
	cmd->abi.abi_ver1 = __cpu_to_le32(WMI_TLV_ABI_VER1);
	cmd->abi.abi_ver_ns0 = __cpu_to_le32(WMI_TLV_ABI_VER_NS0);
	cmd->abi.abi_ver_ns1 = __cpu_to_le32(WMI_TLV_ABI_VER_NS1);
	cmd->abi.abi_ver_ns2 = __cpu_to_le32(WMI_TLV_ABI_VER_NS2);
	cmd->abi.abi_ver_ns3 = __cpu_to_le32(WMI_TLV_ABI_VER_NS3);
	cmd->num_host_mem_chunks = __cpu_to_le32(ar->wmi.num_mem_chunks);

	cfg->num_vdevs = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);

	अगर (ar->hw_params.num_peers)
		cfg->num_peers = __cpu_to_le32(ar->hw_params.num_peers);
	अन्यथा
		cfg->num_peers = __cpu_to_le32(TARGET_TLV_NUM_PEERS);
	cfg->ast_skid_limit = __cpu_to_le32(ar->hw_params.ast_skid_limit);
	cfg->num_wds_entries = __cpu_to_le32(ar->hw_params.num_wds_entries);

	अगर (test_bit(WMI_SERVICE_RX_FULL_REORDER, ar->wmi.svc_map)) अणु
		cfg->num_offload_peers = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);
		cfg->num_offload_reorder_bufs = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);
	पूर्ण अन्यथा अणु
		cfg->num_offload_peers = __cpu_to_le32(0);
		cfg->num_offload_reorder_bufs = __cpu_to_le32(0);
	पूर्ण

	cfg->num_peer_keys = __cpu_to_le32(2);
	अगर (ar->hw_params.num_peers)
		cfg->num_tids = __cpu_to_le32(ar->hw_params.num_peers * 2);
	अन्यथा
		cfg->num_tids = __cpu_to_le32(TARGET_TLV_NUM_TIDS);
	cfg->tx_chain_mask = __cpu_to_le32(0x7);
	cfg->rx_chain_mask = __cpu_to_le32(0x7);
	cfg->rx_समयout_pri[0] = __cpu_to_le32(0x64);
	cfg->rx_समयout_pri[1] = __cpu_to_le32(0x64);
	cfg->rx_समयout_pri[2] = __cpu_to_le32(0x64);
	cfg->rx_समयout_pri[3] = __cpu_to_le32(0x28);
	cfg->rx_decap_mode = __cpu_to_le32(ar->wmi.rx_decap_mode);
	cfg->scan_max_pending_reqs = __cpu_to_le32(4);
	cfg->bmiss_offload_max_vdev = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);
	cfg->roam_offload_max_vdev = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);
	cfg->roam_offload_max_ap_profiles = __cpu_to_le32(8);
	cfg->num_mcast_groups = __cpu_to_le32(0);
	cfg->num_mcast_table_elems = __cpu_to_le32(0);
	cfg->mcast2ucast_mode = __cpu_to_le32(0);
	cfg->tx_dbg_log_size = __cpu_to_le32(0x400);
	cfg->dma_burst_size = __cpu_to_le32(0);
	cfg->mac_aggr_delim = __cpu_to_le32(0);
	cfg->rx_skip_defrag_समयout_dup_detection_check = __cpu_to_le32(0);
	cfg->vow_config = __cpu_to_le32(0);
	cfg->gtk_offload_max_vdev = __cpu_to_le32(2);
	cfg->num_msdu_desc = __cpu_to_le32(ar->htt.max_num_pending_tx);
	cfg->max_frag_entries = __cpu_to_le32(2);
	cfg->num_tdls_vdevs = __cpu_to_le32(TARGET_TLV_NUM_TDLS_VDEVS);
	cfg->num_tdls_conn_table_entries = __cpu_to_le32(0x20);
	cfg->beacon_tx_offload_max_vdev = __cpu_to_le32(2);
	cfg->num_multicast_filter_entries = __cpu_to_le32(5);
	cfg->num_wow_filters = __cpu_to_le32(ar->wow.max_num_patterns);
	cfg->num_keep_alive_pattern = __cpu_to_le32(6);
	cfg->keep_alive_pattern_size = __cpu_to_le32(0);
	cfg->max_tdls_concurrent_sleep_sta = __cpu_to_le32(1);
	cfg->max_tdls_concurrent_buffer_sta = __cpu_to_le32(1);
	cfg->wmi_send_separate = __cpu_to_le32(0);
	cfg->num_ocb_vdevs = __cpu_to_le32(0);
	cfg->num_ocb_channels = __cpu_to_le32(0);
	cfg->num_ocb_schedules = __cpu_to_le32(0);
	cfg->host_capab = __cpu_to_le32(WMI_TLV_FLAG_MGMT_BUNDLE_TX_COMPL);

	अगर (test_bit(WMI_SERVICE_TX_DATA_ACK_RSSI, ar->wmi.svc_map))
		cfg->host_capab |= __cpu_to_le32(WMI_RSRC_CFG_FLAG_TX_ACK_RSSI);

	ath10k_wmi_tlv_put_host_mem_chunks(ar, chunks);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv init\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_start_scan(काष्ठा ath10k *ar,
				 स्थिर काष्ठा wmi_start_scan_arg *arg)
अणु
	काष्ठा wmi_tlv_start_scan_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len, chan_len, ssid_len, bssid_len, ie_len;
	__le32 *chans;
	काष्ठा wmi_ssid *ssids;
	काष्ठा wmi_mac_addr *addrs;
	व्योम *ptr;
	पूर्णांक i, ret;

	ret = ath10k_wmi_start_scan_verअगरy(arg);
	अगर (ret)
		वापस ERR_PTR(ret);

	chan_len = arg->n_channels * माप(__le32);
	ssid_len = arg->n_ssids * माप(काष्ठा wmi_ssid);
	bssid_len = arg->n_bssids * माप(काष्ठा wmi_mac_addr);
	ie_len = roundup(arg->ie_len, 4);
	len = (माप(*tlv) + माप(*cmd)) +
	      माप(*tlv) + chan_len +
	      माप(*tlv) + ssid_len +
	      माप(*tlv) + bssid_len +
	      माप(*tlv) + ie_len;

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_START_SCAN_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	ath10k_wmi_put_start_scan_common(&cmd->common, arg);
	cmd->burst_duration_ms = __cpu_to_le32(arg->burst_duration_ms);
	cmd->num_channels = __cpu_to_le32(arg->n_channels);
	cmd->num_ssids = __cpu_to_le32(arg->n_ssids);
	cmd->num_bssids = __cpu_to_le32(arg->n_bssids);
	cmd->ie_len = __cpu_to_le32(arg->ie_len);
	cmd->num_probes = __cpu_to_le32(3);
	ether_addr_copy(cmd->mac_addr.addr, arg->mac_addr.addr);
	ether_addr_copy(cmd->mac_mask.addr, arg->mac_mask.addr);

	/* FIXME: There are some scan flag inconsistencies across firmwares,
	 * e.g. WMI-TLV inverts the logic behind the following flag.
	 */
	cmd->common.scan_ctrl_flags ^= __cpu_to_le32(WMI_SCAN_FILTER_PROBE_REQ);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_UINT32);
	tlv->len = __cpu_to_le16(chan_len);
	chans = (व्योम *)tlv->value;
	क्रम (i = 0; i < arg->n_channels; i++)
		chans[i] = __cpu_to_le32(arg->channels[i]);

	ptr += माप(*tlv);
	ptr += chan_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_FIXED_STRUCT);
	tlv->len = __cpu_to_le16(ssid_len);
	ssids = (व्योम *)tlv->value;
	क्रम (i = 0; i < arg->n_ssids; i++) अणु
		ssids[i].ssid_len = __cpu_to_le32(arg->ssids[i].len);
		स_नकल(ssids[i].ssid, arg->ssids[i].ssid, arg->ssids[i].len);
	पूर्ण

	ptr += माप(*tlv);
	ptr += ssid_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_FIXED_STRUCT);
	tlv->len = __cpu_to_le16(bssid_len);
	addrs = (व्योम *)tlv->value;
	क्रम (i = 0; i < arg->n_bssids; i++)
		ether_addr_copy(addrs[i].addr, arg->bssids[i].bssid);

	ptr += माप(*tlv);
	ptr += bssid_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(ie_len);
	स_नकल(tlv->value, arg->ie, arg->ie_len);

	ptr += माप(*tlv);
	ptr += ie_len;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv start scan\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_stop_scan(काष्ठा ath10k *ar,
				स्थिर काष्ठा wmi_stop_scan_arg *arg)
अणु
	काष्ठा wmi_stop_scan_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	u32 scan_id;
	u32 req_id;

	अगर (arg->req_id > 0xFFF)
		वापस ERR_PTR(-EINVAL);
	अगर (arg->req_type == WMI_SCAN_STOP_ONE && arg->u.scan_id > 0xFFF)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	scan_id = arg->u.scan_id;
	scan_id |= WMI_HOST_SCAN_REQ_ID_PREFIX;

	req_id = arg->req_id;
	req_id |= WMI_HOST_SCAN_REQUESTOR_ID_PREFIX;

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STOP_SCAN_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->req_type = __cpu_to_le32(arg->req_type);
	cmd->vdev_id = __cpu_to_le32(arg->u.vdev_id);
	cmd->scan_id = __cpu_to_le32(scan_id);
	cmd->scan_req_id = __cpu_to_le32(req_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv stop scan\n");
	वापस skb;
पूर्ण

अटल पूर्णांक ath10k_wmi_tlv_op_get_vdev_subtype(काष्ठा ath10k *ar,
					      क्रमागत wmi_vdev_subtype subtype)
अणु
	चयन (subtype) अणु
	हाल WMI_VDEV_SUBTYPE_NONE:
		वापस WMI_TLV_VDEV_SUBTYPE_NONE;
	हाल WMI_VDEV_SUBTYPE_P2P_DEVICE:
		वापस WMI_TLV_VDEV_SUBTYPE_P2P_DEV;
	हाल WMI_VDEV_SUBTYPE_P2P_CLIENT:
		वापस WMI_TLV_VDEV_SUBTYPE_P2P_CLI;
	हाल WMI_VDEV_SUBTYPE_P2P_GO:
		वापस WMI_TLV_VDEV_SUBTYPE_P2P_GO;
	हाल WMI_VDEV_SUBTYPE_PROXY_STA:
		वापस WMI_TLV_VDEV_SUBTYPE_PROXY_STA;
	हाल WMI_VDEV_SUBTYPE_MESH_11S:
		वापस WMI_TLV_VDEV_SUBTYPE_MESH_11S;
	हाल WMI_VDEV_SUBTYPE_MESH_NON_11S:
		वापस -ENOTSUPP;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_create(काष्ठा ath10k *ar,
				  u32 vdev_id,
				  क्रमागत wmi_vdev_type vdev_type,
				  क्रमागत wmi_vdev_subtype vdev_subtype,
				  स्थिर u8 mac_addr[ETH_ALEN])
अणु
	काष्ठा wmi_vdev_create_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_CREATE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->vdev_type = __cpu_to_le32(vdev_type);
	cmd->vdev_subtype = __cpu_to_le32(vdev_subtype);
	ether_addr_copy(cmd->vdev_macaddr.addr, mac_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev create\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_delete(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा wmi_vdev_delete_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_DELETE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev delete\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_start(काष्ठा ath10k *ar,
				 स्थिर काष्ठा wmi_vdev_start_request_arg *arg,
				 bool restart)
अणु
	काष्ठा wmi_tlv_vdev_start_cmd *cmd;
	काष्ठा wmi_channel *ch;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	व्योम *ptr;
	u32 flags = 0;

	अगर (WARN_ON(arg->hidden_ssid && !arg->ssid))
		वापस ERR_PTR(-EINVAL);
	अगर (WARN_ON(arg->ssid_len > माप(cmd->ssid.ssid)))
		वापस ERR_PTR(-EINVAL);

	len = (माप(*tlv) + माप(*cmd)) +
	      (माप(*tlv) + माप(*ch)) +
	      (माप(*tlv) + 0);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	अगर (arg->hidden_ssid)
		flags |= WMI_VDEV_START_HIDDEN_SSID;
	अगर (arg->pmf_enabled)
		flags |= WMI_VDEV_START_PMF_ENABLED;

	ptr = (व्योम *)skb->data;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_START_REQUEST_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->bcn_पूर्णांकval = __cpu_to_le32(arg->bcn_पूर्णांकval);
	cmd->dtim_period = __cpu_to_le32(arg->dtim_period);
	cmd->flags = __cpu_to_le32(flags);
	cmd->bcn_tx_rate = __cpu_to_le32(arg->bcn_tx_rate);
	cmd->bcn_tx_घातer = __cpu_to_le32(arg->bcn_tx_घातer);
	cmd->disable_hw_ack = __cpu_to_le32(arg->disable_hw_ack);

	अगर (arg->ssid) अणु
		cmd->ssid.ssid_len = __cpu_to_le32(arg->ssid_len);
		स_नकल(cmd->ssid.ssid, arg->ssid, arg->ssid_len);
	पूर्ण

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_CHANNEL);
	tlv->len = __cpu_to_le16(माप(*ch));
	ch = (व्योम *)tlv->value;
	ath10k_wmi_put_wmi_channel(ar, ch, &arg->channel);

	ptr += माप(*tlv);
	ptr += माप(*ch);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = 0;

	/* Note: This is a nested TLV containing:
	 * [wmi_tlv][wmi_p2p_noa_descriptor][wmi_tlv]..
	 */

	ptr += माप(*tlv);
	ptr += 0;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev start\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_stop(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा wmi_vdev_stop_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_STOP_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev stop\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_up(काष्ठा ath10k *ar, u32 vdev_id, u32 aid,
			      स्थिर u8 *bssid)

अणु
	काष्ठा wmi_vdev_up_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_UP_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->vdev_assoc_id = __cpu_to_le32(aid);
	ether_addr_copy(cmd->vdev_bssid.addr, bssid);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev up\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_करोwn(काष्ठा ath10k *ar, u32 vdev_id)
अणु
	काष्ठा wmi_vdev_करोwn_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_DOWN_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev down\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_set_param(काष्ठा ath10k *ar, u32 vdev_id,
				     u32 param_id, u32 param_value)
अणु
	काष्ठा wmi_vdev_set_param_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_SET_PARAM_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->param_id = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(param_value);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev %d set param %d value 0x%x\n",
		   vdev_id, param_id, param_value);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_install_key(काष्ठा ath10k *ar,
				       स्थिर काष्ठा wmi_vdev_install_key_arg *arg)
अणु
	काष्ठा wmi_vdev_install_key_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	व्योम *ptr;

	अगर (arg->key_cipher == ar->wmi_key_cipher[WMI_CIPHER_NONE] &&
	    arg->key_data)
		वापस ERR_PTR(-EINVAL);
	अगर (arg->key_cipher != ar->wmi_key_cipher[WMI_CIPHER_NONE] &&
	    !arg->key_data)
		वापस ERR_PTR(-EINVAL);

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) + roundup(arg->key_len, माप(__le32));
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_INSTALL_KEY_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->key_idx = __cpu_to_le32(arg->key_idx);
	cmd->key_flags = __cpu_to_le32(arg->key_flags);
	cmd->key_cipher = __cpu_to_le32(arg->key_cipher);
	cmd->key_len = __cpu_to_le32(arg->key_len);
	cmd->key_txmic_len = __cpu_to_le32(arg->key_txmic_len);
	cmd->key_rxmic_len = __cpu_to_le32(arg->key_rxmic_len);

	अगर (arg->macaddr)
		ether_addr_copy(cmd->peer_macaddr.addr, arg->macaddr);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(roundup(arg->key_len, माप(__le32)));
	अगर (arg->key_data)
		स_नकल(tlv->value, arg->key_data, arg->key_len);

	ptr += माप(*tlv);
	ptr += roundup(arg->key_len, माप(__le32));

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev install key\n");
	वापस skb;
पूर्ण

अटल व्योम *ath10k_wmi_tlv_put_uapsd_ac(काष्ठा ath10k *ar, व्योम *ptr,
					 स्थिर काष्ठा wmi_sta_uapsd_स्वतः_trig_arg *arg)
अणु
	काष्ठा wmi_sta_uapsd_स्वतः_trig_param *ac;
	काष्ठा wmi_tlv *tlv;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_UAPSD_AUTO_TRIG_PARAM);
	tlv->len = __cpu_to_le16(माप(*ac));
	ac = (व्योम *)tlv->value;

	ac->wmm_ac = __cpu_to_le32(arg->wmm_ac);
	ac->user_priority = __cpu_to_le32(arg->user_priority);
	ac->service_पूर्णांकerval = __cpu_to_le32(arg->service_पूर्णांकerval);
	ac->suspend_पूर्णांकerval = __cpu_to_le32(arg->suspend_पूर्णांकerval);
	ac->delay_पूर्णांकerval = __cpu_to_le32(arg->delay_पूर्णांकerval);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv vdev sta uapsd auto trigger ac %d prio %d svc int %d susp int %d delay int %d\n",
		   ac->wmm_ac, ac->user_priority, ac->service_पूर्णांकerval,
		   ac->suspend_पूर्णांकerval, ac->delay_पूर्णांकerval);

	वापस ptr + माप(*tlv) + माप(*ac);
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_sta_uapsd(काष्ठा ath10k *ar, u32 vdev_id,
				     स्थिर u8 peer_addr[ETH_ALEN],
				     स्थिर काष्ठा wmi_sta_uapsd_स्वतः_trig_arg *args,
				     u32 num_ac)
अणु
	काष्ठा wmi_sta_uapsd_स्वतः_trig_cmd_fixed_param *cmd;
	काष्ठा wmi_sta_uapsd_स्वतः_trig_param *ac;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	माप_प्रकार ac_tlv_len;
	व्योम *ptr;
	पूर्णांक i;

	ac_tlv_len = num_ac * (माप(*tlv) + माप(*ac));
	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) + ac_tlv_len;
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_UAPSD_AUTO_TRIG_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->num_ac = __cpu_to_le32(num_ac);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(ac_tlv_len);
	ac = (व्योम *)tlv->value;

	ptr += माप(*tlv);
	क्रम (i = 0; i < num_ac; i++)
		ptr = ath10k_wmi_tlv_put_uapsd_ac(ar, ptr, &args[i]);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev sta uapsd auto trigger\n");
	वापस skb;
पूर्ण

अटल व्योम *ath10k_wmi_tlv_put_wmm(व्योम *ptr,
				    स्थिर काष्ठा wmi_wmm_params_arg *arg)
अणु
	काष्ठा wmi_wmm_params *wmm;
	काष्ठा wmi_tlv *tlv;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WMM_PARAMS);
	tlv->len = __cpu_to_le16(माप(*wmm));
	wmm = (व्योम *)tlv->value;
	ath10k_wmi_set_wmm_param(wmm, arg);

	वापस ptr + माप(*tlv) + माप(*wmm);
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_wmm_conf(काष्ठा ath10k *ar, u32 vdev_id,
				    स्थिर काष्ठा wmi_wmm_params_all_arg *arg)
अणु
	काष्ठा wmi_tlv_vdev_set_wmm_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	व्योम *ptr;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_SET_WMM_PARAMS_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);

	ath10k_wmi_set_wmm_param(&cmd->vdev_wmm_params[0].params, &arg->ac_be);
	ath10k_wmi_set_wmm_param(&cmd->vdev_wmm_params[1].params, &arg->ac_bk);
	ath10k_wmi_set_wmm_param(&cmd->vdev_wmm_params[2].params, &arg->ac_vi);
	ath10k_wmi_set_wmm_param(&cmd->vdev_wmm_params[3].params, &arg->ac_vo);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv vdev wmm conf\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_sta_keepalive(काष्ठा ath10k *ar,
				    स्थिर काष्ठा wmi_sta_keepalive_arg *arg)
अणु
	काष्ठा wmi_tlv_sta_keepalive_cmd *cmd;
	काष्ठा wmi_sta_keepalive_arp_resp *arp;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) + माप(*arp);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_KEEPALIVE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->enabled = __cpu_to_le32(arg->enabled);
	cmd->method = __cpu_to_le32(arg->method);
	cmd->पूर्णांकerval = __cpu_to_le32(arg->पूर्णांकerval);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_KEEPALVE_ARP_RESPONSE);
	tlv->len = __cpu_to_le16(माप(*arp));
	arp = (व्योम *)tlv->value;

	arp->src_ip4_addr = arg->src_ip4_addr;
	arp->dest_ip4_addr = arg->dest_ip4_addr;
	ether_addr_copy(arp->dest_mac_addr.addr, arg->dest_mac_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv sta keepalive vdev %d enabled %d method %d interval %d\n",
		   arg->vdev_id, arg->enabled, arg->method, arg->पूर्णांकerval);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_peer_create(काष्ठा ath10k *ar, u32 vdev_id,
				  स्थिर u8 peer_addr[ETH_ALEN],
				  क्रमागत wmi_peer_type peer_type)
अणु
	काष्ठा wmi_tlv_peer_create_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PEER_CREATE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->peer_type = __cpu_to_le32(peer_type);
	ether_addr_copy(cmd->peer_addr.addr, peer_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv peer create\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_peer_delete(काष्ठा ath10k *ar, u32 vdev_id,
				  स्थिर u8 peer_addr[ETH_ALEN])
अणु
	काष्ठा wmi_peer_delete_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PEER_DELETE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv peer delete\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_peer_flush(काष्ठा ath10k *ar, u32 vdev_id,
				 स्थिर u8 peer_addr[ETH_ALEN], u32 tid_biपंचांगap)
अणु
	काष्ठा wmi_peer_flush_tids_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PEER_FLUSH_TIDS_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->peer_tid_biपंचांगap = __cpu_to_le32(tid_biपंचांगap);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv peer flush\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_peer_set_param(काष्ठा ath10k *ar, u32 vdev_id,
				     स्थिर u8 *peer_addr,
				     क्रमागत wmi_peer_param param_id,
				     u32 param_value)
अणु
	काष्ठा wmi_peer_set_param_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PEER_SET_PARAM_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->param_id = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(param_value);
	ether_addr_copy(cmd->peer_macaddr.addr, peer_addr);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv vdev %d peer %pM set param %d value 0x%x\n",
		   vdev_id, peer_addr, param_id, param_value);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_peer_assoc(काष्ठा ath10k *ar,
				 स्थिर काष्ठा wmi_peer_assoc_complete_arg *arg)
अणु
	काष्ठा wmi_tlv_peer_assoc_cmd *cmd;
	काष्ठा wmi_vht_rate_set *vht_rate;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len, legacy_rate_len, ht_rate_len;
	व्योम *ptr;

	अगर (arg->peer_mpdu_density > 16)
		वापस ERR_PTR(-EINVAL);
	अगर (arg->peer_legacy_rates.num_rates > MAX_SUPPORTED_RATES)
		वापस ERR_PTR(-EINVAL);
	अगर (arg->peer_ht_rates.num_rates > MAX_SUPPORTED_RATES)
		वापस ERR_PTR(-EINVAL);

	legacy_rate_len = roundup(arg->peer_legacy_rates.num_rates,
				  माप(__le32));
	ht_rate_len = roundup(arg->peer_ht_rates.num_rates, माप(__le32));
	len = (माप(*tlv) + माप(*cmd)) +
	      (माप(*tlv) + legacy_rate_len) +
	      (माप(*tlv) + ht_rate_len) +
	      (माप(*tlv) + माप(*vht_rate));
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PEER_ASSOC_COMPLETE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->new_assoc = __cpu_to_le32(arg->peer_reassoc ? 0 : 1);
	cmd->assoc_id = __cpu_to_le32(arg->peer_aid);
	cmd->flags = __cpu_to_le32(arg->peer_flags);
	cmd->caps = __cpu_to_le32(arg->peer_caps);
	cmd->listen_पूर्णांकval = __cpu_to_le32(arg->peer_listen_पूर्णांकval);
	cmd->ht_caps = __cpu_to_le32(arg->peer_ht_caps);
	cmd->max_mpdu = __cpu_to_le32(arg->peer_max_mpdu);
	cmd->mpdu_density = __cpu_to_le32(arg->peer_mpdu_density);
	cmd->rate_caps = __cpu_to_le32(arg->peer_rate_caps);
	cmd->nss = __cpu_to_le32(arg->peer_num_spatial_streams);
	cmd->vht_caps = __cpu_to_le32(arg->peer_vht_caps);
	cmd->phy_mode = __cpu_to_le32(arg->peer_phymode);
	cmd->num_legacy_rates = __cpu_to_le32(arg->peer_legacy_rates.num_rates);
	cmd->num_ht_rates = __cpu_to_le32(arg->peer_ht_rates.num_rates);
	ether_addr_copy(cmd->mac_addr.addr, arg->addr);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(legacy_rate_len);
	स_नकल(tlv->value, arg->peer_legacy_rates.rates,
	       arg->peer_legacy_rates.num_rates);

	ptr += माप(*tlv);
	ptr += legacy_rate_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(ht_rate_len);
	स_नकल(tlv->value, arg->peer_ht_rates.rates,
	       arg->peer_ht_rates.num_rates);

	ptr += माप(*tlv);
	ptr += ht_rate_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VHT_RATE_SET);
	tlv->len = __cpu_to_le16(माप(*vht_rate));
	vht_rate = (व्योम *)tlv->value;

	vht_rate->rx_max_rate = __cpu_to_le32(arg->peer_vht_rates.rx_max_rate);
	vht_rate->rx_mcs_set = __cpu_to_le32(arg->peer_vht_rates.rx_mcs_set);
	vht_rate->tx_max_rate = __cpu_to_le32(arg->peer_vht_rates.tx_max_rate);
	vht_rate->tx_mcs_set = __cpu_to_le32(arg->peer_vht_rates.tx_mcs_set);

	ptr += माप(*tlv);
	ptr += माप(*vht_rate);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv peer assoc\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_set_psmode(काष्ठा ath10k *ar, u32 vdev_id,
				 क्रमागत wmi_sta_ps_mode psmode)
अणु
	काष्ठा wmi_sta_घातersave_mode_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_POWERSAVE_MODE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->sta_ps_mode = __cpu_to_le32(psmode);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv set psmode\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_set_sta_ps(काष्ठा ath10k *ar, u32 vdev_id,
				 क्रमागत wmi_sta_घातersave_param param_id,
				 u32 param_value)
अणु
	काष्ठा wmi_sta_घातersave_param_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_STA_POWERSAVE_PARAM_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->param_id = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(param_value);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv set sta ps\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_set_ap_ps(काष्ठा ath10k *ar, u32 vdev_id, स्थिर u8 *mac,
				क्रमागत wmi_ap_ps_peer_param param_id, u32 value)
अणु
	काष्ठा wmi_ap_ps_peer_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	अगर (!mac)
		वापस ERR_PTR(-EINVAL);

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_AP_PS_PEER_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->param_id = __cpu_to_le32(param_id);
	cmd->param_value = __cpu_to_le32(value);
	ether_addr_copy(cmd->peer_macaddr.addr, mac);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv ap ps param\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_scan_chan_list(काष्ठा ath10k *ar,
				     स्थिर काष्ठा wmi_scan_chan_list_arg *arg)
अणु
	काष्ठा wmi_tlv_scan_chan_list_cmd *cmd;
	काष्ठा wmi_channel *ci;
	काष्ठा wmi_channel_arg *ch;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार chans_len, len;
	पूर्णांक i;
	व्योम *ptr, *chans;

	chans_len = arg->n_channels * (माप(*tlv) + माप(*ci));
	len = (माप(*tlv) + माप(*cmd)) +
	      (माप(*tlv) + chans_len);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_SCAN_CHAN_LIST_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->num_scan_chans = __cpu_to_le32(arg->n_channels);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(chans_len);
	chans = (व्योम *)tlv->value;

	क्रम (i = 0; i < arg->n_channels; i++) अणु
		ch = &arg->channels[i];

		tlv = chans;
		tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_CHANNEL);
		tlv->len = __cpu_to_le16(माप(*ci));
		ci = (व्योम *)tlv->value;

		ath10k_wmi_put_wmi_channel(ar, ci, ch);

		chans += माप(*tlv);
		chans += माप(*ci);
	पूर्ण

	ptr += माप(*tlv);
	ptr += chans_len;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv scan chan list\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_scan_prob_req_oui(काष्ठा ath10k *ar, u32 prob_req_oui)
अणु
	काष्ठा wmi_scan_prob_req_oui_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_SCAN_PROB_REQ_OUI_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->prob_req_oui = __cpu_to_le32(prob_req_oui);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv scan prob req oui\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_beacon_dma(काष्ठा ath10k *ar, u32 vdev_id,
				 स्थिर व्योम *bcn, माप_प्रकार bcn_len,
				 u32 bcn_paddr, bool dtim_zero,
				 bool deliver_cab)

अणु
	काष्ठा wmi_bcn_tx_ref_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	u16 fc;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	hdr = (काष्ठा ieee80211_hdr *)bcn;
	fc = le16_to_cpu(hdr->frame_control);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_BCN_SEND_FROM_HOST_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->data_len = __cpu_to_le32(bcn_len);
	cmd->data_ptr = __cpu_to_le32(bcn_paddr);
	cmd->msdu_id = 0;
	cmd->frame_control = __cpu_to_le32(fc);
	cmd->flags = 0;

	अगर (dtim_zero)
		cmd->flags |= __cpu_to_le32(WMI_BCN_TX_REF_FLAG_DTIM_ZERO);

	अगर (deliver_cab)
		cmd->flags |= __cpu_to_le32(WMI_BCN_TX_REF_FLAG_DELIVER_CAB);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv beacon dma\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pdev_set_wmm(काष्ठा ath10k *ar,
				   स्थिर काष्ठा wmi_wmm_params_all_arg *arg)
अणु
	काष्ठा wmi_tlv_pdev_set_wmm_cmd *cmd;
	काष्ठा wmi_wmm_params *wmm;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;
	व्योम *ptr;

	len = (माप(*tlv) + माप(*cmd)) +
	      (4 * (माप(*tlv) + माप(*wmm)));
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_SET_WMM_PARAMS_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	/* nothing to set here */

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	ptr = ath10k_wmi_tlv_put_wmm(ptr, &arg->ac_be);
	ptr = ath10k_wmi_tlv_put_wmm(ptr, &arg->ac_bk);
	ptr = ath10k_wmi_tlv_put_wmm(ptr, &arg->ac_vi);
	ptr = ath10k_wmi_tlv_put_wmm(ptr, &arg->ac_vo);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv pdev set wmm\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_request_stats(काष्ठा ath10k *ar, u32 stats_mask)
अणु
	काष्ठा wmi_request_stats_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_REQUEST_STATS_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->stats_id = __cpu_to_le32(stats_mask);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv request stats\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_request_peer_stats_info(काष्ठा ath10k *ar,
					      u32 vdev_id,
					      क्रमागत wmi_peer_stats_info_request_type type,
					      u8 *addr,
					      u32 reset)
अणु
	काष्ठा wmi_tlv_request_peer_stats_info *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_REQUEST_PEER_STATS_INFO_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->request_type = __cpu_to_le32(type);

	अगर (type == WMI_REQUEST_ONE_PEER_STATS_INFO)
		ether_addr_copy(cmd->peer_macaddr.addr, addr);

	cmd->reset_after_request = __cpu_to_le32(reset);
	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv request peer stats info\n");
	वापस skb;
पूर्ण

अटल पूर्णांक
ath10k_wmi_tlv_op_cleanup_mgmt_tx_send(काष्ठा ath10k *ar,
				       काष्ठा sk_buff *msdu)
अणु
	काष्ठा ath10k_skb_cb *cb = ATH10K_SKB_CB(msdu);
	काष्ठा ath10k_wmi *wmi = &ar->wmi;

	idr_हटाओ(&wmi->mgmt_pending_tx, cb->msdu_id);

	वापस 0;
पूर्ण

अटल पूर्णांक
ath10k_wmi_mgmt_tx_alloc_msdu_id(काष्ठा ath10k *ar, काष्ठा sk_buff *skb,
				 dma_addr_t paddr)
अणु
	काष्ठा ath10k_wmi *wmi = &ar->wmi;
	काष्ठा ath10k_mgmt_tx_pkt_addr *pkt_addr;
	पूर्णांक ret;

	pkt_addr = kदो_स्मृति(माप(*pkt_addr), GFP_ATOMIC);
	अगर (!pkt_addr)
		वापस -ENOMEM;

	pkt_addr->vaddr = skb;
	pkt_addr->paddr = paddr;

	spin_lock_bh(&ar->data_lock);
	ret = idr_alloc(&wmi->mgmt_pending_tx, pkt_addr, 0,
			wmi->mgmt_max_num_pending_tx, GFP_ATOMIC);
	spin_unlock_bh(&ar->data_lock);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi mgmt tx alloc msdu_id ret %d\n", ret);
	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_mgmt_tx_send(काष्ठा ath10k *ar, काष्ठा sk_buff *msdu,
				   dma_addr_t paddr)
अणु
	काष्ठा ath10k_skb_cb *cb = ATH10K_SKB_CB(msdu);
	काष्ठा wmi_tlv_mgmt_tx_cmd *cmd;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath10k_vअगर *arvअगर;
	u32 buf_len = msdu->len;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	पूर्णांक len, desc_id;
	u32 vdev_id;
	व्योम *ptr;

	अगर (!cb->vअगर)
		वापस ERR_PTR(-EINVAL);

	hdr = (काष्ठा ieee80211_hdr *)msdu->data;
	arvअगर = (व्योम *)cb->vअगर->drv_priv;
	vdev_id = arvअगर->vdev_id;

	अगर (WARN_ON_ONCE(!ieee80211_is_mgmt(hdr->frame_control) &&
			 (!(ieee80211_is_nullfunc(hdr->frame_control) ||
			 ieee80211_is_qos_nullfunc(hdr->frame_control)))))
		वापस ERR_PTR(-EINVAL);

	len = माप(*cmd) + 2 * माप(*tlv);

	अगर ((ieee80211_is_action(hdr->frame_control) ||
	     ieee80211_is_deauth(hdr->frame_control) ||
	     ieee80211_is_disassoc(hdr->frame_control)) &&
	     ieee80211_has_रक्षित(hdr->frame_control)) अणु
		skb_put(msdu, IEEE80211_CCMP_MIC_LEN);
		buf_len += IEEE80211_CCMP_MIC_LEN;
	पूर्ण

	buf_len = min_t(u32, buf_len, WMI_TLV_MGMT_TX_FRAME_MAX_LEN);
	buf_len = round_up(buf_len, 4);

	len += buf_len;
	len = round_up(len, 4);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	desc_id = ath10k_wmi_mgmt_tx_alloc_msdu_id(ar, msdu, paddr);
	अगर (desc_id < 0)
		जाओ err_मुक्त_skb;

	cb->msdu_id = desc_id;

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_MGMT_TX_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->desc_id = __cpu_to_le32(desc_id);
	cmd->chanfreq = 0;
	cmd->buf_len = __cpu_to_le32(buf_len);
	cmd->frame_len = __cpu_to_le32(msdu->len);
	cmd->paddr = __cpu_to_le64(paddr);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(buf_len);

	ptr += माप(*tlv);
	स_नकल(ptr, msdu->data, buf_len);

	वापस skb;

err_मुक्त_skb:
	dev_kमुक्त_skb(skb);
	वापस ERR_PTR(desc_id);
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_क्रमce_fw_hang(काष्ठा ath10k *ar,
				    क्रमागत wmi_क्रमce_fw_hang_type type,
				    u32 delay_ms)
अणु
	काष्ठा wmi_क्रमce_fw_hang_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_FORCE_FW_HANG_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->type = __cpu_to_le32(type);
	cmd->delay_ms = __cpu_to_le32(delay_ms);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv force fw hang\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_dbglog_cfg(काष्ठा ath10k *ar, u64 module_enable,
				 u32 log_level)
अणु
	काष्ठा wmi_tlv_dbglog_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len, bmap_len;
	u32 value;
	व्योम *ptr;

	अगर (module_enable) अणु
		value = WMI_TLV_DBGLOG_LOG_LEVEL_VALUE(
				module_enable,
				WMI_TLV_DBGLOG_LOG_LEVEL_VERBOSE);
	पूर्ण अन्यथा अणु
		value = WMI_TLV_DBGLOG_LOG_LEVEL_VALUE(
				WMI_TLV_DBGLOG_ALL_MODULES,
				WMI_TLV_DBGLOG_LOG_LEVEL_WARN);
	पूर्ण

	bmap_len = 0;
	len = माप(*tlv) + माप(*cmd) + माप(*tlv) + bmap_len;
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_DEBUG_LOG_CONFIG_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->param = __cpu_to_le32(WMI_TLV_DBGLOG_PARAM_LOG_LEVEL);
	cmd->value = __cpu_to_le32(value);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_UINT32);
	tlv->len = __cpu_to_le16(bmap_len);

	/* nothing to करो here */

	ptr += माप(*tlv);
	ptr += माप(bmap_len);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv dbglog value 0x%08x\n", value);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pktlog_enable(काष्ठा ath10k *ar, u32 filter)
अणु
	काष्ठा wmi_tlv_pktlog_enable *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_PKTLOG_ENABLE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->filter = __cpu_to_le32(filter);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv pktlog enable filter 0x%08x\n",
		   filter);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pdev_get_temperature(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_tlv_pdev_get_temp_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_GET_TEMPERATURE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi pdev get temperature tlv\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pktlog_disable(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_tlv_pktlog_disable *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_PKTLOG_DISABLE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv pktlog disable\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_bcn_पंचांगpl(काष्ठा ath10k *ar, u32 vdev_id,
			       u32 tim_ie_offset, काष्ठा sk_buff *bcn,
			       u32 prb_caps, u32 prb_erp, व्योम *prb_ies,
			       माप_प्रकार prb_ies_len)
अणु
	काष्ठा wmi_tlv_bcn_पंचांगpl_cmd *cmd;
	काष्ठा wmi_tlv_bcn_prb_info *info;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	अगर (WARN_ON(prb_ies_len > 0 && !prb_ies))
		वापस ERR_PTR(-EINVAL);

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) + माप(*info) + prb_ies_len +
	      माप(*tlv) + roundup(bcn->len, 4);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_BCN_TMPL_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->tim_ie_offset = __cpu_to_le32(tim_ie_offset);
	cmd->buf_len = __cpu_to_le32(bcn->len);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	/* FIXME: prb_ies_len should be probably aligned to 4byte boundary but
	 * then it is then impossible to pass original ie len.
	 * This chunk is not used yet so अगर setting probe resp ढाँचा yields
	 * problems with beaconing or crashes firmware look here.
	 */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_BCN_PRB_INFO);
	tlv->len = __cpu_to_le16(माप(*info) + prb_ies_len);
	info = (व्योम *)tlv->value;
	info->caps = __cpu_to_le32(prb_caps);
	info->erp = __cpu_to_le32(prb_erp);
	स_नकल(info->ies, prb_ies, prb_ies_len);

	ptr += माप(*tlv);
	ptr += माप(*info);
	ptr += prb_ies_len;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(roundup(bcn->len, 4));
	स_नकल(tlv->value, bcn->data, bcn->len);

	/* FIXME: Adjust TSF? */

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv bcn tmpl vdev_id %i\n",
		   vdev_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_prb_पंचांगpl(काष्ठा ath10k *ar, u32 vdev_id,
			       काष्ठा sk_buff *prb)
अणु
	काष्ठा wmi_tlv_prb_पंचांगpl_cmd *cmd;
	काष्ठा wmi_tlv_bcn_prb_info *info;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) + माप(*info) +
	      माप(*tlv) + roundup(prb->len, 4);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PRB_TMPL_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->buf_len = __cpu_to_le32(prb->len);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_BCN_PRB_INFO);
	tlv->len = __cpu_to_le16(माप(*info));
	info = (व्योम *)tlv->value;
	info->caps = 0;
	info->erp = 0;

	ptr += माप(*tlv);
	ptr += माप(*info);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(roundup(prb->len, 4));
	स_नकल(tlv->value, prb->data, prb->len);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv prb tmpl vdev_id %i\n",
		   vdev_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_p2p_go_bcn_ie(काष्ठा ath10k *ar, u32 vdev_id,
				    स्थिर u8 *p2p_ie)
अणु
	काष्ठा wmi_tlv_p2p_go_bcn_ie *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) + roundup(p2p_ie[1] + 2, 4);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_P2P_GO_SET_BEACON_IE);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->ie_len = __cpu_to_le32(p2p_ie[1] + 2);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
	tlv->len = __cpu_to_le16(roundup(p2p_ie[1] + 2, 4));
	स_नकल(tlv->value, p2p_ie, p2p_ie[1] + 2);

	ptr += माप(*tlv);
	ptr += roundup(p2p_ie[1] + 2, 4);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv p2p go bcn ie for vdev %i\n",
		   vdev_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_update_fw_tdls_state(काष्ठा ath10k *ar, u32 vdev_id,
					   क्रमागत wmi_tdls_state state)
अणु
	काष्ठा wmi_tdls_set_state_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;
	/* Set to options from wmi_tlv_tdls_options,
	 * क्रम now none of them are enabled.
	 */
	u32 options = 0;

	अगर (test_bit(WMI_SERVICE_TDLS_UAPSD_BUFFER_STA, ar->wmi.svc_map))
		options |=  WMI_TLV_TDLS_BUFFER_STA_EN;

	/* WMI_TDLS_ENABLE_ACTIVE_EXTERNAL_CONTROL means firm will handle TDLS
	 * link inactivity detecting logic.
	 */
	अगर (state == WMI_TDLS_ENABLE_ACTIVE)
		state = WMI_TDLS_ENABLE_ACTIVE_EXTERNAL_CONTROL;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_TDLS_SET_STATE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));

	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->state = __cpu_to_le32(state);
	cmd->notअगरication_पूर्णांकerval_ms = __cpu_to_le32(5000);
	cmd->tx_discovery_threshold = __cpu_to_le32(100);
	cmd->tx_tearकरोwn_threshold = __cpu_to_le32(5);
	cmd->rssi_tearकरोwn_threshold = __cpu_to_le32(-75);
	cmd->rssi_delta = __cpu_to_le32(-20);
	cmd->tdls_options = __cpu_to_le32(options);
	cmd->tdls_peer_traffic_ind_winकरोw = __cpu_to_le32(2);
	cmd->tdls_peer_traffic_response_समयout_ms = __cpu_to_le32(5000);
	cmd->tdls_puapsd_mask = __cpu_to_le32(0xf);
	cmd->tdls_puapsd_inactivity_समय_ms = __cpu_to_le32(0);
	cmd->tdls_puapsd_rx_frame_threshold = __cpu_to_le32(10);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv update fw tdls state %d for vdev %i\n",
		   state, vdev_id);
	वापस skb;
पूर्ण

अटल u32 ath10k_wmi_tlv_prepare_peer_qos(u8 uapsd_queues, u8 sp)
अणु
	u32 peer_qos = 0;

	अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
		peer_qos |= WMI_TLV_TDLS_PEER_QOS_AC_VO;
	अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI)
		peer_qos |= WMI_TLV_TDLS_PEER_QOS_AC_VI;
	अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)
		peer_qos |= WMI_TLV_TDLS_PEER_QOS_AC_BK;
	अगर (uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE)
		peer_qos |= WMI_TLV_TDLS_PEER_QOS_AC_BE;

	peer_qos |= SM(sp, WMI_TLV_TDLS_PEER_SP);

	वापस peer_qos;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_tdls_peer_update(काष्ठा ath10k *ar,
				       स्थिर काष्ठा wmi_tdls_peer_update_cmd_arg *arg,
				       स्थिर काष्ठा wmi_tdls_peer_capab_arg *cap,
				       स्थिर काष्ठा wmi_channel_arg *chan_arg)
अणु
	काष्ठा wmi_tdls_peer_update_cmd *cmd;
	काष्ठा wmi_tdls_peer_capab *peer_cap;
	काष्ठा wmi_channel *chan;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	u32 peer_qos;
	व्योम *ptr;
	पूर्णांक len;
	पूर्णांक i;

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) + माप(*peer_cap) +
	      माप(*tlv) + cap->peer_chan_len * माप(*chan);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_TDLS_PEER_UPDATE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));

	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	ether_addr_copy(cmd->peer_macaddr.addr, arg->addr);
	cmd->peer_state = __cpu_to_le32(arg->peer_state);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_TDLS_PEER_CAPABILITIES);
	tlv->len = __cpu_to_le16(माप(*peer_cap));
	peer_cap = (व्योम *)tlv->value;
	peer_qos = ath10k_wmi_tlv_prepare_peer_qos(cap->peer_uapsd_queues,
						   cap->peer_max_sp);
	peer_cap->peer_qos = __cpu_to_le32(peer_qos);
	peer_cap->buff_sta_support = __cpu_to_le32(cap->buff_sta_support);
	peer_cap->off_chan_support = __cpu_to_le32(cap->off_chan_support);
	peer_cap->peer_curr_operclass = __cpu_to_le32(cap->peer_curr_operclass);
	peer_cap->self_curr_operclass = __cpu_to_le32(cap->self_curr_operclass);
	peer_cap->peer_chan_len = __cpu_to_le32(cap->peer_chan_len);
	peer_cap->peer_operclass_len = __cpu_to_le32(cap->peer_operclass_len);

	क्रम (i = 0; i < WMI_TDLS_MAX_SUPP_OPER_CLASSES; i++)
		peer_cap->peer_operclass[i] = cap->peer_operclass[i];

	peer_cap->is_peer_responder = __cpu_to_le32(cap->is_peer_responder);
	peer_cap->pref_offchan_num = __cpu_to_le32(cap->pref_offchan_num);
	peer_cap->pref_offchan_bw = __cpu_to_le32(cap->pref_offchan_bw);

	ptr += माप(*tlv);
	ptr += माप(*peer_cap);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(cap->peer_chan_len * माप(*chan));

	ptr += माप(*tlv);

	क्रम (i = 0; i < cap->peer_chan_len; i++) अणु
		tlv = ptr;
		tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_CHANNEL);
		tlv->len = __cpu_to_le16(माप(*chan));
		chan = (व्योम *)tlv->value;
		ath10k_wmi_put_wmi_channel(ar, chan, &chan_arg[i]);

		ptr += माप(*tlv);
		ptr += माप(*chan);
	पूर्ण

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv tdls peer update vdev %i state %d n_chans %u\n",
		   arg->vdev_id, arg->peer_state, cap->peer_chan_len);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_pdev_set_quiet_mode(काष्ठा ath10k *ar, u32 period,
					  u32 duration, u32 next_offset,
					  u32 enabled)
अणु
	काष्ठा wmi_tlv_set_quiet_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, माप(*tlv) + माप(*cmd));
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (व्योम *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_PDEV_SET_QUIET_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	/* vdev_id is not in use, set to 0 */
	cmd->vdev_id = __cpu_to_le32(0);
	cmd->period = __cpu_to_le32(period);
	cmd->duration = __cpu_to_le32(duration);
	cmd->next_start = __cpu_to_le32(next_offset);
	cmd->enabled = __cpu_to_le32(enabled);

	ath10k_dbg(ar, ATH10K_DBG_WMI,
		   "wmi tlv quiet param: period %u duration %u enabled %d\n",
		   period, duration, enabled);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_wow_enable(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_tlv_wow_enable_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (काष्ठा wmi_tlv *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WOW_ENABLE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	cmd->enable = __cpu_to_le32(1);
	अगर (!ar->bus_param.link_can_suspend)
		cmd->छोड़ो_अगरace_config = __cpu_to_le32(WOW_IFACE_PAUSE_DISABLED);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv wow enable\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_wow_add_wakeup_event(काष्ठा ath10k *ar,
					   u32 vdev_id,
					   क्रमागत wmi_wow_wakeup_event event,
					   u32 enable)
अणु
	काष्ठा wmi_tlv_wow_add_del_event_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (काष्ठा wmi_tlv *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WOW_ADD_DEL_EVT_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->is_add = __cpu_to_le32(enable);
	cmd->event_biपंचांगap = __cpu_to_le32(1 << event);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv wow add wakeup event %s enable %d vdev_id %d\n",
		   wow_wakeup_event(event), enable, vdev_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_gen_wow_host_wakeup_ind(काष्ठा ath10k *ar)
अणु
	काष्ठा wmi_tlv_wow_host_wakeup_ind *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (काष्ठा wmi_tlv *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WOW_HOSTWAKEUP_FROM_SLEEP_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv wow host wakeup ind\n");
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_wow_add_pattern(काष्ठा ath10k *ar, u32 vdev_id,
				      u32 pattern_id, स्थिर u8 *pattern,
				      स्थिर u8 *biपंचांगask, पूर्णांक pattern_len,
				      पूर्णांक pattern_offset)
अणु
	काष्ठा wmi_tlv_wow_add_pattern_cmd *cmd;
	काष्ठा wmi_tlv_wow_biपंचांगap_pattern *biपंचांगap;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) +			/* array काष्ठा */
	      माप(*tlv) + माप(*biपंचांगap) +  /* biपंचांगap */
	      माप(*tlv) +			/* empty ipv4 sync */
	      माप(*tlv) +			/* empty ipv6 sync */
	      माप(*tlv) +			/* empty magic */
	      माप(*tlv) +			/* empty info समयout */
	      माप(*tlv) + माप(u32);	/* ratelimit पूर्णांकerval */

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	/* cmd */
	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WOW_ADD_PATTERN_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->pattern_id = __cpu_to_le32(pattern_id);
	cmd->pattern_type = __cpu_to_le32(WOW_BITMAP_PATTERN);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	/* biपंचांगap */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(माप(*tlv) + माप(*biपंचांगap));

	ptr += माप(*tlv);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WOW_BITMAP_PATTERN_T);
	tlv->len = __cpu_to_le16(माप(*biपंचांगap));
	biपंचांगap = (व्योम *)tlv->value;

	स_नकल(biपंचांगap->patternbuf, pattern, pattern_len);
	स_नकल(biपंचांगap->biपंचांगaskbuf, biपंचांगask, pattern_len);
	biपंचांगap->pattern_offset = __cpu_to_le32(pattern_offset);
	biपंचांगap->pattern_len = __cpu_to_le32(pattern_len);
	biपंचांगap->biपंचांगask_len = __cpu_to_le32(pattern_len);
	biपंचांगap->pattern_id = __cpu_to_le32(pattern_id);

	ptr += माप(*tlv);
	ptr += माप(*biपंचांगap);

	/* ipv4 sync */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(0);

	ptr += माप(*tlv);

	/* ipv6 sync */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(0);

	ptr += माप(*tlv);

	/* magic */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(0);

	ptr += माप(*tlv);

	/* pattern info समयout */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_UINT32);
	tlv->len = __cpu_to_le16(0);

	ptr += माप(*tlv);

	/* ratelimit पूर्णांकerval */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_UINT32);
	tlv->len = __cpu_to_le16(माप(u32));

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv wow add pattern vdev_id %d pattern_id %d, pattern_offset %d\n",
		   vdev_id, pattern_id, pattern_offset);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_wow_del_pattern(काष्ठा ath10k *ar, u32 vdev_id,
				      u32 pattern_id)
अणु
	काष्ठा wmi_tlv_wow_del_pattern_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	tlv = (काष्ठा wmi_tlv *)skb->data;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_WOW_DEL_PATTERN_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->pattern_id = __cpu_to_le32(pattern_id);
	cmd->pattern_type = __cpu_to_le32(WOW_BITMAP_PATTERN);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv wow del pattern vdev_id %d pattern_id %d\n",
		   vdev_id, pattern_id);
	वापस skb;
पूर्ण

/* Request FW to start PNO operation */
अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_config_pno_start(काष्ठा ath10k *ar,
				       u32 vdev_id,
				       काष्ठा wmi_pno_scan_req *pno)
अणु
	काष्ठा nlo_configured_parameters *nlo_list;
	काष्ठा wmi_tlv_wow_nlo_config_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	__le32 *channel_list;
	u16 tlv_len;
	माप_प्रकार len;
	व्योम *ptr;
	u32 i;

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) +
	      /* TLV place holder क्रम array of काष्ठाures
	       * nlo_configured_parameters(nlo_list)
	       */
	      माप(*tlv);
	      /* TLV place holder क्रम array of uपूर्णांक32 channel_list */

	len += माप(u32) * min_t(u8, pno->a_networks[0].channel_count,
				   WMI_NLO_MAX_CHAN);
	len += माप(काष्ठा nlo_configured_parameters) *
				min_t(u8, pno->uc_networks_count, WMI_NLO_MAX_SSIDS);

	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_NLO_CONFIG_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	/* wmi_tlv_wow_nlo_config_cmd parameters*/
	cmd->vdev_id = __cpu_to_le32(pno->vdev_id);
	cmd->flags = __cpu_to_le32(WMI_NLO_CONFIG_START | WMI_NLO_CONFIG_SSID_HIDE_EN);

	/* current FW करोes not support min-max range क्रम dwell समय */
	cmd->active_dwell_समय = __cpu_to_le32(pno->active_max_समय);
	cmd->passive_dwell_समय = __cpu_to_le32(pno->passive_max_समय);

	अगर (pno->करो_passive_scan)
		cmd->flags |= __cpu_to_le32(WMI_NLO_CONFIG_SCAN_PASSIVE);

	/* copy scan पूर्णांकerval */
	cmd->fast_scan_period = __cpu_to_le32(pno->fast_scan_period);
	cmd->slow_scan_period = __cpu_to_le32(pno->slow_scan_period);
	cmd->fast_scan_max_cycles = __cpu_to_le32(pno->fast_scan_max_cycles);
	cmd->delay_start_समय = __cpu_to_le32(pno->delay_start_समय);

	अगर (pno->enable_pno_scan_अक्रमomization) अणु
		cmd->flags |= __cpu_to_le32(WMI_NLO_CONFIG_SPOOFED_MAC_IN_PROBE_REQ |
				WMI_NLO_CONFIG_RANDOM_SEQ_NO_IN_PROBE_REQ);
		ether_addr_copy(cmd->mac_addr.addr, pno->mac_addr);
		ether_addr_copy(cmd->mac_mask.addr, pno->mac_addr_mask);
	पूर्ण

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	/* nlo_configured_parameters(nlo_list) */
	cmd->no_of_ssids = __cpu_to_le32(min_t(u8, pno->uc_networks_count,
					       WMI_NLO_MAX_SSIDS));
	tlv_len = __le32_to_cpu(cmd->no_of_ssids) *
		माप(काष्ठा nlo_configured_parameters);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(tlv_len);

	ptr += माप(*tlv);
	nlo_list = ptr;
	क्रम (i = 0; i < __le32_to_cpu(cmd->no_of_ssids); i++) अणु
		tlv = (काष्ठा wmi_tlv *)(&nlo_list[i].tlv_header);
		tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_BYTE);
		tlv->len = __cpu_to_le16(माप(काष्ठा nlo_configured_parameters) -
					 माप(*tlv));

		/* copy ssid and it's length */
		nlo_list[i].ssid.valid = __cpu_to_le32(true);
		nlo_list[i].ssid.ssid.ssid_len = pno->a_networks[i].ssid.ssid_len;
		स_नकल(nlo_list[i].ssid.ssid.ssid,
		       pno->a_networks[i].ssid.ssid,
		       __le32_to_cpu(nlo_list[i].ssid.ssid.ssid_len));

		/* copy rssi threshold */
		अगर (pno->a_networks[i].rssi_threshold &&
		    pno->a_networks[i].rssi_threshold > -300) अणु
			nlo_list[i].rssi_cond.valid = __cpu_to_le32(true);
			nlo_list[i].rssi_cond.rssi =
				__cpu_to_le32(pno->a_networks[i].rssi_threshold);
		पूर्ण

		nlo_list[i].bcast_nw_type.valid = __cpu_to_le32(true);
		nlo_list[i].bcast_nw_type.bcast_nw_type =
			__cpu_to_le32(pno->a_networks[i].bcast_nw_type);
	पूर्ण

	ptr += __le32_to_cpu(cmd->no_of_ssids) * माप(काष्ठा nlo_configured_parameters);

	/* copy channel info */
	cmd->num_of_channels = __cpu_to_le32(min_t(u8,
						   pno->a_networks[0].channel_count,
						   WMI_NLO_MAX_CHAN));

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_UINT32);
	tlv->len = __cpu_to_le16(__le32_to_cpu(cmd->num_of_channels) *
				 माप(u_पूर्णांक32_t));
	ptr += माप(*tlv);

	channel_list = (__le32 *)ptr;
	क्रम (i = 0; i < __le32_to_cpu(cmd->num_of_channels); i++)
		channel_list[i] = __cpu_to_le32(pno->a_networks[0].channels[i]);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv start pno config vdev_id %d\n",
		   vdev_id);

	वापस skb;
पूर्ण

/* Request FW to stop ongoing PNO operation */
अटल काष्ठा sk_buff *ath10k_wmi_tlv_op_gen_config_pno_stop(काष्ठा ath10k *ar,
							     u32 vdev_id)
अणु
	काष्ठा wmi_tlv_wow_nlo_config_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd) +
	      माप(*tlv) +
	      /* TLV place holder क्रम array of काष्ठाures
	       * nlo_configured_parameters(nlo_list)
	       */
	      माप(*tlv);
	      /* TLV place holder क्रम array of uपूर्णांक32 channel_list */
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_NLO_CONFIG_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;

	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->flags = __cpu_to_le32(WMI_NLO_CONFIG_STOP);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	/* nlo_configured_parameters(nlo_list) */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(0);

	ptr += माप(*tlv);

	/* channel list */
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_UINT32);
	tlv->len = __cpu_to_le16(0);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv stop pno config vdev_id %d\n", vdev_id);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_config_pno(काष्ठा ath10k *ar, u32 vdev_id,
				 काष्ठा wmi_pno_scan_req *pno_scan)
अणु
	अगर (pno_scan->enable)
		वापस ath10k_wmi_tlv_op_gen_config_pno_start(ar, vdev_id, pno_scan);
	अन्यथा
		वापस ath10k_wmi_tlv_op_gen_config_pno_stop(ar, vdev_id);
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_adaptive_qcs(काष्ठा ath10k *ar, bool enable)
अणु
	काष्ठा wmi_tlv_adaptive_qcs *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_RESMGR_ADAPTIVE_OCS_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->enable = __cpu_to_le32(enable ? 1 : 0);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv adaptive qcs %d\n", enable);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_echo(काष्ठा ath10k *ar, u32 value)
अणु
	काष्ठा wmi_echo_cmd *cmd;
	काष्ठा wmi_tlv *tlv;
	काष्ठा sk_buff *skb;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_ECHO_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->value = cpu_to_le32(value);

	ptr += माप(*tlv);
	ptr += माप(*cmd);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv echo value 0x%08x\n", value);
	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_spectral_conf(काष्ठा ath10k *ar,
					 स्थिर काष्ठा wmi_vdev_spectral_conf_arg *arg)
अणु
	काष्ठा wmi_vdev_spectral_conf_cmd *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_SPECTRAL_CONFIGURE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(arg->vdev_id);
	cmd->scan_count = __cpu_to_le32(arg->scan_count);
	cmd->scan_period = __cpu_to_le32(arg->scan_period);
	cmd->scan_priority = __cpu_to_le32(arg->scan_priority);
	cmd->scan_fft_size = __cpu_to_le32(arg->scan_fft_size);
	cmd->scan_gc_ena = __cpu_to_le32(arg->scan_gc_ena);
	cmd->scan_restart_ena = __cpu_to_le32(arg->scan_restart_ena);
	cmd->scan_noise_न्यूनमान_ref = __cpu_to_le32(arg->scan_noise_न्यूनमान_ref);
	cmd->scan_init_delay = __cpu_to_le32(arg->scan_init_delay);
	cmd->scan_nb_tone_thr = __cpu_to_le32(arg->scan_nb_tone_thr);
	cmd->scan_str_bin_thr = __cpu_to_le32(arg->scan_str_bin_thr);
	cmd->scan_wb_rpt_mode = __cpu_to_le32(arg->scan_wb_rpt_mode);
	cmd->scan_rssi_rpt_mode = __cpu_to_le32(arg->scan_rssi_rpt_mode);
	cmd->scan_rssi_thr = __cpu_to_le32(arg->scan_rssi_thr);
	cmd->scan_pwr_क्रमmat = __cpu_to_le32(arg->scan_pwr_क्रमmat);
	cmd->scan_rpt_mode = __cpu_to_le32(arg->scan_rpt_mode);
	cmd->scan_bin_scale = __cpu_to_le32(arg->scan_bin_scale);
	cmd->scan_dbm_adj = __cpu_to_le32(arg->scan_dbm_adj);
	cmd->scan_chn_mask = __cpu_to_le32(arg->scan_chn_mask);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
ath10k_wmi_tlv_op_gen_vdev_spectral_enable(काष्ठा ath10k *ar, u32 vdev_id,
					   u32 trigger, u32 enable)
अणु
	काष्ठा wmi_vdev_spectral_enable_cmd *cmd;
	काष्ठा sk_buff *skb;
	काष्ठा wmi_tlv *tlv;
	व्योम *ptr;
	माप_प्रकार len;

	len = माप(*tlv) + माप(*cmd);
	skb = ath10k_wmi_alloc_skb(ar, len);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ptr = (व्योम *)skb->data;
	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_VDEV_SPECTRAL_ENABLE_CMD);
	tlv->len = __cpu_to_le16(माप(*cmd));
	cmd = (व्योम *)tlv->value;
	cmd->vdev_id = __cpu_to_le32(vdev_id);
	cmd->trigger_cmd = __cpu_to_le32(trigger);
	cmd->enable_cmd = __cpu_to_le32(enable);

	वापस skb;
पूर्ण

/****************/
/* TLV mappings */
/****************/

अटल काष्ठा wmi_cmd_map wmi_tlv_cmd_map = अणु
	.init_cmdid = WMI_TLV_INIT_CMDID,
	.start_scan_cmdid = WMI_TLV_START_SCAN_CMDID,
	.stop_scan_cmdid = WMI_TLV_STOP_SCAN_CMDID,
	.scan_chan_list_cmdid = WMI_TLV_SCAN_CHAN_LIST_CMDID,
	.scan_sch_prio_tbl_cmdid = WMI_TLV_SCAN_SCH_PRIO_TBL_CMDID,
	.scan_prob_req_oui_cmdid = WMI_TLV_SCAN_PROB_REQ_OUI_CMDID,
	.pdev_set_regकरोमुख्य_cmdid = WMI_TLV_PDEV_SET_REGDOMAIN_CMDID,
	.pdev_set_channel_cmdid = WMI_TLV_PDEV_SET_CHANNEL_CMDID,
	.pdev_set_param_cmdid = WMI_TLV_PDEV_SET_PARAM_CMDID,
	.pdev_pktlog_enable_cmdid = WMI_TLV_PDEV_PKTLOG_ENABLE_CMDID,
	.pdev_pktlog_disable_cmdid = WMI_TLV_PDEV_PKTLOG_DISABLE_CMDID,
	.pdev_set_wmm_params_cmdid = WMI_TLV_PDEV_SET_WMM_PARAMS_CMDID,
	.pdev_set_ht_cap_ie_cmdid = WMI_TLV_PDEV_SET_HT_CAP_IE_CMDID,
	.pdev_set_vht_cap_ie_cmdid = WMI_TLV_PDEV_SET_VHT_CAP_IE_CMDID,
	.pdev_set_dscp_tid_map_cmdid = WMI_TLV_PDEV_SET_DSCP_TID_MAP_CMDID,
	.pdev_set_quiet_mode_cmdid = WMI_TLV_PDEV_SET_QUIET_MODE_CMDID,
	.pdev_green_ap_ps_enable_cmdid = WMI_TLV_PDEV_GREEN_AP_PS_ENABLE_CMDID,
	.pdev_get_tpc_config_cmdid = WMI_TLV_PDEV_GET_TPC_CONFIG_CMDID,
	.pdev_set_base_macaddr_cmdid = WMI_TLV_PDEV_SET_BASE_MACADDR_CMDID,
	.vdev_create_cmdid = WMI_TLV_VDEV_CREATE_CMDID,
	.vdev_delete_cmdid = WMI_TLV_VDEV_DELETE_CMDID,
	.vdev_start_request_cmdid = WMI_TLV_VDEV_START_REQUEST_CMDID,
	.vdev_restart_request_cmdid = WMI_TLV_VDEV_RESTART_REQUEST_CMDID,
	.vdev_up_cmdid = WMI_TLV_VDEV_UP_CMDID,
	.vdev_stop_cmdid = WMI_TLV_VDEV_STOP_CMDID,
	.vdev_करोwn_cmdid = WMI_TLV_VDEV_DOWN_CMDID,
	.vdev_set_param_cmdid = WMI_TLV_VDEV_SET_PARAM_CMDID,
	.vdev_install_key_cmdid = WMI_TLV_VDEV_INSTALL_KEY_CMDID,
	.peer_create_cmdid = WMI_TLV_PEER_CREATE_CMDID,
	.peer_delete_cmdid = WMI_TLV_PEER_DELETE_CMDID,
	.peer_flush_tids_cmdid = WMI_TLV_PEER_FLUSH_TIDS_CMDID,
	.peer_set_param_cmdid = WMI_TLV_PEER_SET_PARAM_CMDID,
	.peer_assoc_cmdid = WMI_TLV_PEER_ASSOC_CMDID,
	.peer_add_wds_entry_cmdid = WMI_TLV_PEER_ADD_WDS_ENTRY_CMDID,
	.peer_हटाओ_wds_entry_cmdid = WMI_TLV_PEER_REMOVE_WDS_ENTRY_CMDID,
	.peer_mcast_group_cmdid = WMI_TLV_PEER_MCAST_GROUP_CMDID,
	.bcn_tx_cmdid = WMI_TLV_BCN_TX_CMDID,
	.pdev_send_bcn_cmdid = WMI_TLV_PDEV_SEND_BCN_CMDID,
	.bcn_पंचांगpl_cmdid = WMI_TLV_BCN_TMPL_CMDID,
	.bcn_filter_rx_cmdid = WMI_TLV_BCN_FILTER_RX_CMDID,
	.prb_req_filter_rx_cmdid = WMI_TLV_PRB_REQ_FILTER_RX_CMDID,
	.mgmt_tx_cmdid = WMI_TLV_MGMT_TX_CMDID,
	.mgmt_tx_send_cmdid = WMI_TLV_MGMT_TX_SEND_CMD,
	.prb_पंचांगpl_cmdid = WMI_TLV_PRB_TMPL_CMDID,
	.addba_clear_resp_cmdid = WMI_TLV_ADDBA_CLEAR_RESP_CMDID,
	.addba_send_cmdid = WMI_TLV_ADDBA_SEND_CMDID,
	.addba_status_cmdid = WMI_TLV_ADDBA_STATUS_CMDID,
	.delba_send_cmdid = WMI_TLV_DELBA_SEND_CMDID,
	.addba_set_resp_cmdid = WMI_TLV_ADDBA_SET_RESP_CMDID,
	.send_singleamsdu_cmdid = WMI_TLV_SEND_SINGLEAMSDU_CMDID,
	.sta_घातersave_mode_cmdid = WMI_TLV_STA_POWERSAVE_MODE_CMDID,
	.sta_घातersave_param_cmdid = WMI_TLV_STA_POWERSAVE_PARAM_CMDID,
	.sta_mimo_ps_mode_cmdid = WMI_TLV_STA_MIMO_PS_MODE_CMDID,
	.pdev_dfs_enable_cmdid = WMI_TLV_PDEV_DFS_ENABLE_CMDID,
	.pdev_dfs_disable_cmdid = WMI_TLV_PDEV_DFS_DISABLE_CMDID,
	.roam_scan_mode = WMI_TLV_ROAM_SCAN_MODE,
	.roam_scan_rssi_threshold = WMI_TLV_ROAM_SCAN_RSSI_THRESHOLD,
	.roam_scan_period = WMI_TLV_ROAM_SCAN_PERIOD,
	.roam_scan_rssi_change_threshold =
				WMI_TLV_ROAM_SCAN_RSSI_CHANGE_THRESHOLD,
	.roam_ap_profile = WMI_TLV_ROAM_AP_PROखाता,
	.ofl_scan_add_ap_profile = WMI_TLV_ROAM_AP_PROखाता,
	.ofl_scan_हटाओ_ap_profile = WMI_TLV_OFL_SCAN_REMOVE_AP_PROखाता,
	.ofl_scan_period = WMI_TLV_OFL_SCAN_PERIOD,
	.p2p_dev_set_device_info = WMI_TLV_P2P_DEV_SET_DEVICE_INFO,
	.p2p_dev_set_discoverability = WMI_TLV_P2P_DEV_SET_DISCOVERABILITY,
	.p2p_go_set_beacon_ie = WMI_TLV_P2P_GO_SET_BEACON_IE,
	.p2p_go_set_probe_resp_ie = WMI_TLV_P2P_GO_SET_PROBE_RESP_IE,
	.p2p_set_venकरोr_ie_data_cmdid = WMI_TLV_P2P_SET_VENDOR_IE_DATA_CMDID,
	.ap_ps_peer_param_cmdid = WMI_TLV_AP_PS_PEER_PARAM_CMDID,
	.ap_ps_peer_uapsd_coex_cmdid = WMI_TLV_AP_PS_PEER_UAPSD_COEX_CMDID,
	.peer_rate_retry_sched_cmdid = WMI_TLV_PEER_RATE_RETRY_SCHED_CMDID,
	.wlan_profile_trigger_cmdid = WMI_TLV_WLAN_PROखाता_TRIGGER_CMDID,
	.wlan_profile_set_hist_पूर्णांकvl_cmdid =
				WMI_TLV_WLAN_PROखाता_SET_HIST_INTVL_CMDID,
	.wlan_profile_get_profile_data_cmdid =
				WMI_TLV_WLAN_PROखाता_GET_PROखाता_DATA_CMDID,
	.wlan_profile_enable_profile_id_cmdid =
				WMI_TLV_WLAN_PROखाता_ENABLE_PROखाता_ID_CMDID,
	.wlan_profile_list_profile_id_cmdid =
				WMI_TLV_WLAN_PROखाता_LIST_PROखाता_ID_CMDID,
	.pdev_suspend_cmdid = WMI_TLV_PDEV_SUSPEND_CMDID,
	.pdev_resume_cmdid = WMI_TLV_PDEV_RESUME_CMDID,
	.add_bcn_filter_cmdid = WMI_TLV_ADD_BCN_FILTER_CMDID,
	.rmv_bcn_filter_cmdid = WMI_TLV_RMV_BCN_FILTER_CMDID,
	.wow_add_wake_pattern_cmdid = WMI_TLV_WOW_ADD_WAKE_PATTERN_CMDID,
	.wow_del_wake_pattern_cmdid = WMI_TLV_WOW_DEL_WAKE_PATTERN_CMDID,
	.wow_enable_disable_wake_event_cmdid =
				WMI_TLV_WOW_ENABLE_DISABLE_WAKE_EVENT_CMDID,
	.wow_enable_cmdid = WMI_TLV_WOW_ENABLE_CMDID,
	.wow_hostwakeup_from_sleep_cmdid =
				WMI_TLV_WOW_HOSTWAKEUP_FROM_SLEEP_CMDID,
	.rtt_measreq_cmdid = WMI_TLV_RTT_MEASREQ_CMDID,
	.rtt_tsf_cmdid = WMI_TLV_RTT_TSF_CMDID,
	.vdev_spectral_scan_configure_cmdid = WMI_TLV_SPECTRAL_SCAN_CONF_CMDID,
	.vdev_spectral_scan_enable_cmdid = WMI_TLV_SPECTRAL_SCAN_ENABLE_CMDID,
	.request_stats_cmdid = WMI_TLV_REQUEST_STATS_CMDID,
	.request_peer_stats_info_cmdid = WMI_TLV_REQUEST_PEER_STATS_INFO_CMDID,
	.set_arp_ns_offload_cmdid = WMI_TLV_SET_ARP_NS_OFFLOAD_CMDID,
	.network_list_offload_config_cmdid =
				WMI_TLV_NETWORK_LIST_OFFLOAD_CONFIG_CMDID,
	.gtk_offload_cmdid = WMI_TLV_GTK_OFFLOAD_CMDID,
	.csa_offload_enable_cmdid = WMI_TLV_CSA_OFFLOAD_ENABLE_CMDID,
	.csa_offload_chanचयन_cmdid = WMI_TLV_CSA_OFFLOAD_CHANSWITCH_CMDID,
	.chatter_set_mode_cmdid = WMI_TLV_CHATTER_SET_MODE_CMDID,
	.peer_tid_addba_cmdid = WMI_TLV_PEER_TID_ADDBA_CMDID,
	.peer_tid_delba_cmdid = WMI_TLV_PEER_TID_DELBA_CMDID,
	.sta_dtim_ps_method_cmdid = WMI_TLV_STA_DTIM_PS_METHOD_CMDID,
	.sta_uapsd_स्वतः_trig_cmdid = WMI_TLV_STA_UAPSD_AUTO_TRIG_CMDID,
	.sta_keepalive_cmd = WMI_TLV_STA_KEEPALIVE_CMDID,
	.echo_cmdid = WMI_TLV_ECHO_CMDID,
	.pdev_utf_cmdid = WMI_TLV_PDEV_UTF_CMDID,
	.dbglog_cfg_cmdid = WMI_TLV_DBGLOG_CFG_CMDID,
	.pdev_qvit_cmdid = WMI_TLV_PDEV_QVIT_CMDID,
	.pdev_fपंचांग_पूर्णांकg_cmdid = WMI_TLV_PDEV_FTM_INTG_CMDID,
	.vdev_set_keepalive_cmdid = WMI_TLV_VDEV_SET_KEEPALIVE_CMDID,
	.vdev_get_keepalive_cmdid = WMI_TLV_VDEV_GET_KEEPALIVE_CMDID,
	.क्रमce_fw_hang_cmdid = WMI_TLV_FORCE_FW_HANG_CMDID,
	.gpio_config_cmdid = WMI_TLV_GPIO_CONFIG_CMDID,
	.gpio_output_cmdid = WMI_TLV_GPIO_OUTPUT_CMDID,
	.pdev_get_temperature_cmdid = WMI_TLV_PDEV_GET_TEMPERATURE_CMDID,
	.vdev_set_wmm_params_cmdid = WMI_TLV_VDEV_SET_WMM_PARAMS_CMDID,
	.tdls_set_state_cmdid = WMI_TLV_TDLS_SET_STATE_CMDID,
	.tdls_peer_update_cmdid = WMI_TLV_TDLS_PEER_UPDATE_CMDID,
	.adaptive_qcs_cmdid = WMI_TLV_RESMGR_ADAPTIVE_OCS_CMDID,
	.scan_update_request_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_standby_response_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_resume_response_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_add_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_evict_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_restore_peer_cmdid = WMI_CMD_UNSUPPORTED,
	.wlan_peer_caching_prपूर्णांक_all_peers_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_update_wds_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_add_proxy_sta_entry_cmdid = WMI_CMD_UNSUPPORTED,
	.rtt_keepalive_cmdid = WMI_CMD_UNSUPPORTED,
	.oem_req_cmdid = WMI_CMD_UNSUPPORTED,
	.nan_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_ratemask_cmdid = WMI_CMD_UNSUPPORTED,
	.qboost_cfg_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_enable_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_smart_ant_set_rx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_tx_antenna_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_train_info_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_smart_ant_set_node_config_ops_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_antenna_चयन_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_ctl_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_set_mimogain_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_ratepwr_chainmsk_table_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_fips_cmdid = WMI_CMD_UNSUPPORTED,
	.tt_set_conf_cmdid = WMI_CMD_UNSUPPORTED,
	.fwtest_cmdid = WMI_CMD_UNSUPPORTED,
	.vdev_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.peer_atf_request_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_cck_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_get_ani_ofdm_config_cmdid = WMI_CMD_UNSUPPORTED,
	.pdev_reserve_ast_entry_cmdid = WMI_CMD_UNSUPPORTED,
पूर्ण;

अटल काष्ठा wmi_pdev_param_map wmi_tlv_pdev_param_map = अणु
	.tx_chain_mask = WMI_TLV_PDEV_PARAM_TX_CHAIN_MASK,
	.rx_chain_mask = WMI_TLV_PDEV_PARAM_RX_CHAIN_MASK,
	.txघातer_limit2g = WMI_TLV_PDEV_PARAM_TXPOWER_LIMIT2G,
	.txघातer_limit5g = WMI_TLV_PDEV_PARAM_TXPOWER_LIMIT5G,
	.txघातer_scale = WMI_TLV_PDEV_PARAM_TXPOWER_SCALE,
	.beacon_gen_mode = WMI_TLV_PDEV_PARAM_BEACON_GEN_MODE,
	.beacon_tx_mode = WMI_TLV_PDEV_PARAM_BEACON_TX_MODE,
	.resmgr_offchan_mode = WMI_TLV_PDEV_PARAM_RESMGR_OFFCHAN_MODE,
	.protection_mode = WMI_TLV_PDEV_PARAM_PROTECTION_MODE,
	.dynamic_bw = WMI_TLV_PDEV_PARAM_DYNAMIC_BW,
	.non_agg_sw_retry_th = WMI_TLV_PDEV_PARAM_NON_AGG_SW_RETRY_TH,
	.agg_sw_retry_th = WMI_TLV_PDEV_PARAM_AGG_SW_RETRY_TH,
	.sta_kickout_th = WMI_TLV_PDEV_PARAM_STA_KICKOUT_TH,
	.ac_aggrsize_scaling = WMI_TLV_PDEV_PARAM_AC_AGGRSIZE_SCALING,
	.ltr_enable = WMI_TLV_PDEV_PARAM_LTR_ENABLE,
	.ltr_ac_latency_be = WMI_TLV_PDEV_PARAM_LTR_AC_LATENCY_BE,
	.ltr_ac_latency_bk = WMI_TLV_PDEV_PARAM_LTR_AC_LATENCY_BK,
	.ltr_ac_latency_vi = WMI_TLV_PDEV_PARAM_LTR_AC_LATENCY_VI,
	.ltr_ac_latency_vo = WMI_TLV_PDEV_PARAM_LTR_AC_LATENCY_VO,
	.ltr_ac_latency_समयout = WMI_TLV_PDEV_PARAM_LTR_AC_LATENCY_TIMEOUT,
	.ltr_sleep_override = WMI_TLV_PDEV_PARAM_LTR_SLEEP_OVERRIDE,
	.ltr_rx_override = WMI_TLV_PDEV_PARAM_LTR_RX_OVERRIDE,
	.ltr_tx_activity_समयout = WMI_TLV_PDEV_PARAM_LTR_TX_ACTIVITY_TIMEOUT,
	.l1ss_enable = WMI_TLV_PDEV_PARAM_L1SS_ENABLE,
	.dsleep_enable = WMI_TLV_PDEV_PARAM_DSLEEP_ENABLE,
	.pcielp_txbuf_flush = WMI_TLV_PDEV_PARAM_PCIELP_TXBUF_FLUSH,
	.pcielp_txbuf_watermark = WMI_TLV_PDEV_PARAM_PCIELP_TXBUF_TMO_EN,
	.pcielp_txbuf_पंचांगo_en = WMI_TLV_PDEV_PARAM_PCIELP_TXBUF_TMO_EN,
	.pcielp_txbuf_पंचांगo_value = WMI_TLV_PDEV_PARAM_PCIELP_TXBUF_TMO_VALUE,
	.pdev_stats_update_period = WMI_TLV_PDEV_PARAM_PDEV_STATS_UPDATE_PERIOD,
	.vdev_stats_update_period = WMI_TLV_PDEV_PARAM_VDEV_STATS_UPDATE_PERIOD,
	.peer_stats_update_period = WMI_TLV_PDEV_PARAM_PEER_STATS_UPDATE_PERIOD,
	.bcnflt_stats_update_period =
				WMI_TLV_PDEV_PARAM_BCNFLT_STATS_UPDATE_PERIOD,
	.pmf_qos = WMI_TLV_PDEV_PARAM_PMF_QOS,
	.arp_ac_override = WMI_TLV_PDEV_PARAM_ARP_AC_OVERRIDE,
	.dcs = WMI_TLV_PDEV_PARAM_DCS,
	.ani_enable = WMI_TLV_PDEV_PARAM_ANI_ENABLE,
	.ani_poll_period = WMI_TLV_PDEV_PARAM_ANI_POLL_PERIOD,
	.ani_listen_period = WMI_TLV_PDEV_PARAM_ANI_LISTEN_PERIOD,
	.ani_ofdm_level = WMI_TLV_PDEV_PARAM_ANI_OFDM_LEVEL,
	.ani_cck_level = WMI_TLV_PDEV_PARAM_ANI_CCK_LEVEL,
	.dyntxchain = WMI_TLV_PDEV_PARAM_DYNTXCHAIN,
	.proxy_sta = WMI_TLV_PDEV_PARAM_PROXY_STA,
	.idle_ps_config = WMI_TLV_PDEV_PARAM_IDLE_PS_CONFIG,
	.घातer_gating_sleep = WMI_TLV_PDEV_PARAM_POWER_GATING_SLEEP,
	.fast_channel_reset = WMI_TLV_PDEV_PARAM_UNSUPPORTED,
	.burst_dur = WMI_TLV_PDEV_PARAM_BURST_DUR,
	.burst_enable = WMI_TLV_PDEV_PARAM_BURST_ENABLE,
	.cal_period = WMI_PDEV_PARAM_UNSUPPORTED,
	.aggr_burst = WMI_PDEV_PARAM_UNSUPPORTED,
	.rx_decap_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.smart_antenna_शेष_antenna = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_override = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_tid = WMI_PDEV_PARAM_UNSUPPORTED,
	.antenna_gain = WMI_PDEV_PARAM_UNSUPPORTED,
	.rx_filter = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast_to_ucast_tid = WMI_PDEV_PARAM_UNSUPPORTED,
	.proxy_sta_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast2ucast_mode = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast2ucast_buffer = WMI_PDEV_PARAM_UNSUPPORTED,
	.हटाओ_mcast2ucast_buffer = WMI_PDEV_PARAM_UNSUPPORTED,
	.peer_sta_ps_statechg_enable = WMI_PDEV_PARAM_UNSUPPORTED,
	.igmpmld_ac_override = WMI_PDEV_PARAM_UNSUPPORTED,
	.block_पूर्णांकerbss = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_disable_reset_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_msdu_ttl_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_ppdu_duration_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.txbf_sound_period_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_promisc_mode_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_burst_mode_cmdid = WMI_PDEV_PARAM_UNSUPPORTED,
	.en_stats = WMI_PDEV_PARAM_UNSUPPORTED,
	.mu_group_policy = WMI_PDEV_PARAM_UNSUPPORTED,
	.noise_detection = WMI_PDEV_PARAM_UNSUPPORTED,
	.noise_threshold = WMI_PDEV_PARAM_UNSUPPORTED,
	.dpd_enable = WMI_PDEV_PARAM_UNSUPPORTED,
	.set_mcast_bcast_echo = WMI_PDEV_PARAM_UNSUPPORTED,
	.atf_strict_sch = WMI_PDEV_PARAM_UNSUPPORTED,
	.atf_sched_duration = WMI_PDEV_PARAM_UNSUPPORTED,
	.ant_plzn = WMI_PDEV_PARAM_UNSUPPORTED,
	.mgmt_retry_limit = WMI_PDEV_PARAM_UNSUPPORTED,
	.sensitivity_level = WMI_PDEV_PARAM_UNSUPPORTED,
	.चिन्हित_txघातer_2g = WMI_PDEV_PARAM_UNSUPPORTED,
	.चिन्हित_txघातer_5g = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_per_tid_amsdu = WMI_PDEV_PARAM_UNSUPPORTED,
	.enable_per_tid_ampdu = WMI_PDEV_PARAM_UNSUPPORTED,
	.cca_threshold = WMI_PDEV_PARAM_UNSUPPORTED,
	.rts_fixed_rate = WMI_PDEV_PARAM_UNSUPPORTED,
	.pdev_reset = WMI_PDEV_PARAM_UNSUPPORTED,
	.wapi_mbssid_offset = WMI_PDEV_PARAM_UNSUPPORTED,
	.arp_srcaddr = WMI_PDEV_PARAM_UNSUPPORTED,
	.arp_dstaddr = WMI_PDEV_PARAM_UNSUPPORTED,
	.rfसमाप्त_config = WMI_TLV_PDEV_PARAM_HW_RFKILL_CONFIG,
	.rfसमाप्त_enable = WMI_TLV_PDEV_PARAM_RFKILL_ENABLE,
	.peer_stats_info_enable = WMI_TLV_PDEV_PARAM_PEER_STATS_INFO_ENABLE,
पूर्ण;

अटल काष्ठा wmi_peer_param_map wmi_tlv_peer_param_map = अणु
	.smps_state = WMI_TLV_PEER_SMPS_STATE,
	.ampdu = WMI_TLV_PEER_AMPDU,
	.authorize = WMI_TLV_PEER_AUTHORIZE,
	.chan_width = WMI_TLV_PEER_CHAN_WIDTH,
	.nss = WMI_TLV_PEER_NSS,
	.use_4addr = WMI_TLV_PEER_USE_4ADDR,
	.membership = WMI_TLV_PEER_MEMBERSHIP,
	.user_pos = WMI_TLV_PEER_USERPOS,
	.crit_proto_hपूर्णांक_enabled = WMI_TLV_PEER_CRIT_PROTO_HINT_ENABLED,
	.tx_fail_cnt_thr = WMI_TLV_PEER_TX_FAIL_CNT_THR,
	.set_hw_retry_cts2s = WMI_TLV_PEER_SET_HW_RETRY_CTS2S,
	.ibss_atim_win_len = WMI_TLV_PEER_IBSS_ATIM_WINDOW_LENGTH,
	.phymode = WMI_TLV_PEER_PHYMODE,
	.use_fixed_घातer = WMI_TLV_PEER_USE_FIXED_PWR,
	.dummy_var = WMI_TLV_PEER_DUMMY_VAR,
पूर्ण;

अटल काष्ठा wmi_vdev_param_map wmi_tlv_vdev_param_map = अणु
	.rts_threshold = WMI_TLV_VDEV_PARAM_RTS_THRESHOLD,
	.fragmentation_threshold = WMI_TLV_VDEV_PARAM_FRAGMENTATION_THRESHOLD,
	.beacon_पूर्णांकerval = WMI_TLV_VDEV_PARAM_BEACON_INTERVAL,
	.listen_पूर्णांकerval = WMI_TLV_VDEV_PARAM_LISTEN_INTERVAL,
	.multicast_rate = WMI_TLV_VDEV_PARAM_MULTICAST_RATE,
	.mgmt_tx_rate = WMI_TLV_VDEV_PARAM_MGMT_TX_RATE,
	.slot_समय = WMI_TLV_VDEV_PARAM_SLOT_TIME,
	.preamble = WMI_TLV_VDEV_PARAM_PREAMBLE,
	.swba_समय = WMI_TLV_VDEV_PARAM_SWBA_TIME,
	.wmi_vdev_stats_update_period = WMI_TLV_VDEV_STATS_UPDATE_PERIOD,
	.wmi_vdev_pwrsave_ageout_समय = WMI_TLV_VDEV_PWRSAVE_AGEOUT_TIME,
	.wmi_vdev_host_swba_पूर्णांकerval = WMI_TLV_VDEV_HOST_SWBA_INTERVAL,
	.dtim_period = WMI_TLV_VDEV_PARAM_DTIM_PERIOD,
	.wmi_vdev_oc_scheduler_air_समय_limit =
				WMI_TLV_VDEV_OC_SCHEDULER_AIR_TIME_LIMIT,
	.wds = WMI_TLV_VDEV_PARAM_WDS,
	.atim_winकरोw = WMI_TLV_VDEV_PARAM_ATIM_WINDOW,
	.bmiss_count_max = WMI_TLV_VDEV_PARAM_BMISS_COUNT_MAX,
	.bmiss_first_bcnt = WMI_TLV_VDEV_PARAM_BMISS_FIRST_BCNT,
	.bmiss_final_bcnt = WMI_TLV_VDEV_PARAM_BMISS_FINAL_BCNT,
	.feature_wmm = WMI_TLV_VDEV_PARAM_FEATURE_WMM,
	.chwidth = WMI_TLV_VDEV_PARAM_CHWIDTH,
	.chextoffset = WMI_TLV_VDEV_PARAM_CHEXTOFFSET,
	.disable_htprotection =	WMI_TLV_VDEV_PARAM_DISABLE_HTPROTECTION,
	.sta_quickkickout = WMI_TLV_VDEV_PARAM_STA_QUICKKICKOUT,
	.mgmt_rate = WMI_TLV_VDEV_PARAM_MGMT_RATE,
	.protection_mode = WMI_TLV_VDEV_PARAM_PROTECTION_MODE,
	.fixed_rate = WMI_TLV_VDEV_PARAM_FIXED_RATE,
	.sgi = WMI_TLV_VDEV_PARAM_SGI,
	.ldpc = WMI_TLV_VDEV_PARAM_LDPC,
	.tx_stbc = WMI_TLV_VDEV_PARAM_TX_STBC,
	.rx_stbc = WMI_TLV_VDEV_PARAM_RX_STBC,
	.पूर्णांकra_bss_fwd = WMI_TLV_VDEV_PARAM_INTRA_BSS_FWD,
	.def_keyid = WMI_TLV_VDEV_PARAM_DEF_KEYID,
	.nss = WMI_TLV_VDEV_PARAM_NSS,
	.bcast_data_rate = WMI_TLV_VDEV_PARAM_BCAST_DATA_RATE,
	.mcast_data_rate = WMI_TLV_VDEV_PARAM_MCAST_DATA_RATE,
	.mcast_indicate = WMI_TLV_VDEV_PARAM_MCAST_INDICATE,
	.dhcp_indicate = WMI_TLV_VDEV_PARAM_DHCP_INDICATE,
	.unknown_dest_indicate = WMI_TLV_VDEV_PARAM_UNKNOWN_DEST_INDICATE,
	.ap_keepalive_min_idle_inactive_समय_secs =
		WMI_TLV_VDEV_PARAM_AP_KEEPALIVE_MIN_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_idle_inactive_समय_secs =
		WMI_TLV_VDEV_PARAM_AP_KEEPALIVE_MAX_IDLE_INACTIVE_TIME_SECS,
	.ap_keepalive_max_unresponsive_समय_secs =
		WMI_TLV_VDEV_PARAM_AP_KEEPALIVE_MAX_UNRESPONSIVE_TIME_SECS,
	.ap_enable_nawds = WMI_TLV_VDEV_PARAM_AP_ENABLE_NAWDS,
	.mcast2ucast_set = WMI_TLV_VDEV_PARAM_UNSUPPORTED,
	.enable_rtscts = WMI_TLV_VDEV_PARAM_ENABLE_RTSCTS,
	.txbf = WMI_TLV_VDEV_PARAM_TXBF,
	.packet_घातersave = WMI_TLV_VDEV_PARAM_PACKET_POWERSAVE,
	.drop_unencry = WMI_TLV_VDEV_PARAM_DROP_UNENCRY,
	.tx_encap_type = WMI_TLV_VDEV_PARAM_TX_ENCAP_TYPE,
	.ap_detect_out_of_sync_sleeping_sta_समय_secs =
					WMI_TLV_VDEV_PARAM_UNSUPPORTED,
	.rc_num_retries = WMI_VDEV_PARAM_UNSUPPORTED,
	.cabq_maxdur = WMI_VDEV_PARAM_UNSUPPORTED,
	.mfptest_set = WMI_VDEV_PARAM_UNSUPPORTED,
	.rts_fixed_rate = WMI_VDEV_PARAM_UNSUPPORTED,
	.vht_sgimask = WMI_VDEV_PARAM_UNSUPPORTED,
	.vht80_ratemask = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_adjust_enable = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_tgt_bmiss_num = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_bmiss_sample_cycle = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_slop_step = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_init_slop = WMI_VDEV_PARAM_UNSUPPORTED,
	.early_rx_adjust_छोड़ो = WMI_VDEV_PARAM_UNSUPPORTED,
	.proxy_sta = WMI_VDEV_PARAM_UNSUPPORTED,
	.meru_vc = WMI_VDEV_PARAM_UNSUPPORTED,
	.rx_decap_type = WMI_VDEV_PARAM_UNSUPPORTED,
	.bw_nss_ratemask = WMI_VDEV_PARAM_UNSUPPORTED,
पूर्ण;

अटल स्थिर काष्ठा wmi_ops wmi_tlv_ops = अणु
	.rx = ath10k_wmi_tlv_op_rx,
	.map_svc = wmi_tlv_svc_map,
	.map_svc_ext = wmi_tlv_svc_map_ext,

	.pull_scan = ath10k_wmi_tlv_op_pull_scan_ev,
	.pull_mgmt_rx = ath10k_wmi_tlv_op_pull_mgmt_rx_ev,
	.pull_mgmt_tx_compl = ath10k_wmi_tlv_op_pull_mgmt_tx_compl_ev,
	.pull_mgmt_tx_bundle_compl = ath10k_wmi_tlv_op_pull_mgmt_tx_bundle_compl_ev,
	.pull_ch_info = ath10k_wmi_tlv_op_pull_ch_info_ev,
	.pull_vdev_start = ath10k_wmi_tlv_op_pull_vdev_start_ev,
	.pull_peer_kick = ath10k_wmi_tlv_op_pull_peer_kick_ev,
	.pull_swba = ath10k_wmi_tlv_op_pull_swba_ev,
	.pull_phyerr_hdr = ath10k_wmi_tlv_op_pull_phyerr_ev_hdr,
	.pull_phyerr = ath10k_wmi_op_pull_phyerr_ev,
	.pull_svc_rdy = ath10k_wmi_tlv_op_pull_svc_rdy_ev,
	.pull_rdy = ath10k_wmi_tlv_op_pull_rdy_ev,
	.pull_svc_avail = ath10k_wmi_tlv_op_pull_svc_avail,
	.pull_fw_stats = ath10k_wmi_tlv_op_pull_fw_stats,
	.pull_roam_ev = ath10k_wmi_tlv_op_pull_roam_ev,
	.pull_wow_event = ath10k_wmi_tlv_op_pull_wow_ev,
	.pull_echo_ev = ath10k_wmi_tlv_op_pull_echo_ev,
	.get_txbf_conf_scheme = ath10k_wmi_tlv_txbf_conf_scheme,

	.gen_pdev_suspend = ath10k_wmi_tlv_op_gen_pdev_suspend,
	.gen_pdev_resume = ath10k_wmi_tlv_op_gen_pdev_resume,
	.gen_pdev_set_rd = ath10k_wmi_tlv_op_gen_pdev_set_rd,
	.gen_pdev_set_param = ath10k_wmi_tlv_op_gen_pdev_set_param,
	.gen_init = ath10k_wmi_tlv_op_gen_init,
	.gen_start_scan = ath10k_wmi_tlv_op_gen_start_scan,
	.gen_stop_scan = ath10k_wmi_tlv_op_gen_stop_scan,
	.gen_vdev_create = ath10k_wmi_tlv_op_gen_vdev_create,
	.gen_vdev_delete = ath10k_wmi_tlv_op_gen_vdev_delete,
	.gen_vdev_start = ath10k_wmi_tlv_op_gen_vdev_start,
	.gen_vdev_stop = ath10k_wmi_tlv_op_gen_vdev_stop,
	.gen_vdev_up = ath10k_wmi_tlv_op_gen_vdev_up,
	.gen_vdev_करोwn = ath10k_wmi_tlv_op_gen_vdev_करोwn,
	.gen_vdev_set_param = ath10k_wmi_tlv_op_gen_vdev_set_param,
	.gen_vdev_install_key = ath10k_wmi_tlv_op_gen_vdev_install_key,
	.gen_vdev_wmm_conf = ath10k_wmi_tlv_op_gen_vdev_wmm_conf,
	.gen_peer_create = ath10k_wmi_tlv_op_gen_peer_create,
	.gen_peer_delete = ath10k_wmi_tlv_op_gen_peer_delete,
	.gen_peer_flush = ath10k_wmi_tlv_op_gen_peer_flush,
	.gen_peer_set_param = ath10k_wmi_tlv_op_gen_peer_set_param,
	.gen_peer_assoc = ath10k_wmi_tlv_op_gen_peer_assoc,
	.gen_set_psmode = ath10k_wmi_tlv_op_gen_set_psmode,
	.gen_set_sta_ps = ath10k_wmi_tlv_op_gen_set_sta_ps,
	.gen_set_ap_ps = ath10k_wmi_tlv_op_gen_set_ap_ps,
	.gen_scan_chan_list = ath10k_wmi_tlv_op_gen_scan_chan_list,
	.gen_scan_prob_req_oui = ath10k_wmi_tlv_op_gen_scan_prob_req_oui,
	.gen_beacon_dma = ath10k_wmi_tlv_op_gen_beacon_dma,
	.gen_pdev_set_wmm = ath10k_wmi_tlv_op_gen_pdev_set_wmm,
	.gen_request_stats = ath10k_wmi_tlv_op_gen_request_stats,
	.gen_request_peer_stats_info = ath10k_wmi_tlv_op_gen_request_peer_stats_info,
	.gen_क्रमce_fw_hang = ath10k_wmi_tlv_op_gen_क्रमce_fw_hang,
	/* .gen_mgmt_tx = not implemented; HTT is used */
	.gen_mgmt_tx_send = ath10k_wmi_tlv_op_gen_mgmt_tx_send,
	.cleanup_mgmt_tx_send = ath10k_wmi_tlv_op_cleanup_mgmt_tx_send,
	.gen_dbglog_cfg = ath10k_wmi_tlv_op_gen_dbglog_cfg,
	.gen_pktlog_enable = ath10k_wmi_tlv_op_gen_pktlog_enable,
	.gen_pktlog_disable = ath10k_wmi_tlv_op_gen_pktlog_disable,
	.gen_pdev_set_quiet_mode = ath10k_wmi_tlv_op_gen_pdev_set_quiet_mode,
	.gen_pdev_get_temperature = ath10k_wmi_tlv_op_gen_pdev_get_temperature,
	/* .gen_addba_clear_resp not implemented */
	/* .gen_addba_send not implemented */
	/* .gen_addba_set_resp not implemented */
	/* .gen_delba_send not implemented */
	.gen_bcn_पंचांगpl = ath10k_wmi_tlv_op_gen_bcn_पंचांगpl,
	.gen_prb_पंचांगpl = ath10k_wmi_tlv_op_gen_prb_पंचांगpl,
	.gen_p2p_go_bcn_ie = ath10k_wmi_tlv_op_gen_p2p_go_bcn_ie,
	.gen_vdev_sta_uapsd = ath10k_wmi_tlv_op_gen_vdev_sta_uapsd,
	.gen_sta_keepalive = ath10k_wmi_tlv_op_gen_sta_keepalive,
	.gen_wow_enable = ath10k_wmi_tlv_op_gen_wow_enable,
	.gen_wow_add_wakeup_event = ath10k_wmi_tlv_op_gen_wow_add_wakeup_event,
	.gen_wow_host_wakeup_ind = ath10k_wmi_tlv_gen_wow_host_wakeup_ind,
	.gen_wow_add_pattern = ath10k_wmi_tlv_op_gen_wow_add_pattern,
	.gen_wow_del_pattern = ath10k_wmi_tlv_op_gen_wow_del_pattern,
	.gen_wow_config_pno = ath10k_wmi_tlv_op_gen_config_pno,
	.gen_update_fw_tdls_state = ath10k_wmi_tlv_op_gen_update_fw_tdls_state,
	.gen_tdls_peer_update = ath10k_wmi_tlv_op_gen_tdls_peer_update,
	.gen_adaptive_qcs = ath10k_wmi_tlv_op_gen_adaptive_qcs,
	.fw_stats_fill = ath10k_wmi_मुख्य_op_fw_stats_fill,
	.get_vdev_subtype = ath10k_wmi_tlv_op_get_vdev_subtype,
	.gen_echo = ath10k_wmi_tlv_op_gen_echo,
	.gen_vdev_spectral_conf = ath10k_wmi_tlv_op_gen_vdev_spectral_conf,
	.gen_vdev_spectral_enable = ath10k_wmi_tlv_op_gen_vdev_spectral_enable,
पूर्ण;

अटल स्थिर काष्ठा wmi_peer_flags_map wmi_tlv_peer_flags_map = अणु
	.auth = WMI_TLV_PEER_AUTH,
	.qos = WMI_TLV_PEER_QOS,
	.need_ptk_4_way = WMI_TLV_PEER_NEED_PTK_4_WAY,
	.need_gtk_2_way = WMI_TLV_PEER_NEED_GTK_2_WAY,
	.apsd = WMI_TLV_PEER_APSD,
	.ht = WMI_TLV_PEER_HT,
	.bw40 = WMI_TLV_PEER_40MHZ,
	.stbc = WMI_TLV_PEER_STBC,
	.ldbc = WMI_TLV_PEER_LDPC,
	.dyn_mimops = WMI_TLV_PEER_DYN_MIMOPS,
	.अटल_mimops = WMI_TLV_PEER_STATIC_MIMOPS,
	.spatial_mux = WMI_TLV_PEER_SPATIAL_MUX,
	.vht = WMI_TLV_PEER_VHT,
	.bw80 = WMI_TLV_PEER_80MHZ,
	.pmf = WMI_TLV_PEER_PMF,
	.bw160 = WMI_TLV_PEER_160MHZ,
पूर्ण;

/************/
/* TLV init */
/************/

व्योम ath10k_wmi_tlv_attach(काष्ठा ath10k *ar)
अणु
	ar->wmi.cmd = &wmi_tlv_cmd_map;
	ar->wmi.vdev_param = &wmi_tlv_vdev_param_map;
	ar->wmi.pdev_param = &wmi_tlv_pdev_param_map;
	ar->wmi.peer_param = &wmi_tlv_peer_param_map;
	ar->wmi.ops = &wmi_tlv_ops;
	ar->wmi.peer_flags = &wmi_tlv_peer_flags_map;
पूर्ण
