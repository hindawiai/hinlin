<शैली गुरु>
/*
 * Copyright (c) 2014 Redpine Signals Inc.
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

#समावेश <linux/firmware.h>
#समावेश <net/bluetooth/bluetooth.h>
#समावेश "rsi_mgmt.h"
#समावेश "rsi_hal.h"
#समावेश "rsi_sdio.h"
#समावेश "rsi_common.h"

/* FLASH Firmware */
अटल काष्ठा ta_metadata metadata_flash_content[] = अणु
	अणु"flash_content", 0x00010000पूर्ण,
	अणु"rsi/rs9113_wlan_qspi.rps", 0x00010000पूर्ण,
	अणु"rsi/rs9113_wlan_bt_dual_mode.rps", 0x00010000पूर्ण,
	अणु"flash_content", 0x00010000पूर्ण,
	अणु"rsi/rs9113_ap_bt_dual_mode.rps", 0x00010000पूर्ण,

पूर्ण;

अटल काष्ठा ta_metadata metadata[] = अणुअणु"pmemdata_dummy", 0x00000000पूर्ण,
	अणु"rsi/rs9116_wlan.rps", 0x00000000पूर्ण,
	अणु"rsi/rs9116_wlan_bt_classic.rps", 0x00000000पूर्ण,
	अणु"rsi/pmemdata_dummy", 0x00000000पूर्ण,
	अणु"rsi/rs9116_wlan_bt_classic.rps", 0x00000000पूर्ण
पूर्ण;

पूर्णांक rsi_send_pkt_to_bus(काष्ठा rsi_common *common, काष्ठा sk_buff *skb)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	पूर्णांक status;

	अगर (common->coex_mode > 1)
		mutex_lock(&common->tx_bus_mutex);

	status = adapter->host_पूर्णांकf_ops->ग_लिखो_pkt(common->priv,
						   skb->data, skb->len);

	अगर (common->coex_mode > 1)
		mutex_unlock(&common->tx_bus_mutex);

	वापस status;
पूर्ण

पूर्णांक rsi_prepare_mgmt_desc(काष्ठा rsi_common *common, काष्ठा sk_buff *skb)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा ieee80211_hdr *wh = शून्य;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_conf *conf = &adapter->hw->conf;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा rsi_mgmt_desc *mgmt_desc;
	काष्ठा skb_info *tx_params;
	काष्ठा rsi_xtended_desc *xtend_desc = शून्य;
	u8 header_size;
	u32 dword_align_bytes = 0;

	अगर (skb->len > MAX_MGMT_PKT_SIZE) अणु
		rsi_dbg(INFO_ZONE, "%s: Dropping mgmt pkt > 512\n", __func__);
		वापस -EINVAL;
	पूर्ण

	info = IEEE80211_SKB_CB(skb);
	tx_params = (काष्ठा skb_info *)info->driver_data;
	vअगर = tx_params->vअगर;

	/* Update header size */
	header_size = FRAME_DESC_SZ + माप(काष्ठा rsi_xtended_desc);
	अगर (header_size > skb_headroom(skb)) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to add extended descriptor\n",
			__func__);
		वापस -ENOSPC;
	पूर्ण
	skb_push(skb, header_size);
	dword_align_bytes = ((अचिन्हित दीर्घ)skb->data & 0x3f);
	अगर (dword_align_bytes > skb_headroom(skb)) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Failed to add dword align\n", __func__);
		वापस -ENOSPC;
	पूर्ण
	skb_push(skb, dword_align_bytes);
	header_size += dword_align_bytes;

	tx_params->पूर्णांकernal_hdr_size = header_size;
	स_रखो(&skb->data[0], 0, header_size);
	wh = (काष्ठा ieee80211_hdr *)&skb->data[header_size];

	mgmt_desc = (काष्ठा rsi_mgmt_desc *)skb->data;
	xtend_desc = (काष्ठा rsi_xtended_desc *)&skb->data[FRAME_DESC_SZ];

	rsi_set_len_qno(&mgmt_desc->len_qno, (skb->len - FRAME_DESC_SZ),
			RSI_WIFI_MGMT_Q);
	mgmt_desc->frame_type = TX_DOT11_MGMT;
	mgmt_desc->header_len = MIN_802_11_HDR_LEN;
	mgmt_desc->xtend_desc_size = header_size - FRAME_DESC_SZ;

	अगर (ieee80211_is_probe_req(wh->frame_control))
		mgmt_desc->frame_info = cpu_to_le16(RSI_INSERT_SEQ_IN_FW);
	mgmt_desc->frame_info |= cpu_to_le16(RATE_INFO_ENABLE);
	अगर (is_broadcast_ether_addr(wh->addr1))
		mgmt_desc->frame_info |= cpu_to_le16(RSI_BROADCAST_PKT);

	mgmt_desc->seq_ctrl =
		cpu_to_le16(IEEE80211_SEQ_TO_SN(le16_to_cpu(wh->seq_ctrl)));
	अगर ((common->band == NL80211_BAND_2GHZ) && !common->p2p_enabled)
		mgmt_desc->rate_info = cpu_to_le16(RSI_RATE_1);
	अन्यथा
		mgmt_desc->rate_info = cpu_to_le16(RSI_RATE_6);

	अगर (conf_is_ht40(conf))
		mgmt_desc->bbp_info = cpu_to_le16(FULL40M_ENABLE);

	अगर (ieee80211_is_probe_resp(wh->frame_control)) अणु
		mgmt_desc->misc_flags |= (RSI_ADD_DELTA_TSF_VAP_ID |
					  RSI_FETCH_RETRY_CNT_FRM_HST);
#घोषणा PROBE_RESP_RETRY_CNT	3
		xtend_desc->retry_cnt = PROBE_RESP_RETRY_CNT;
	पूर्ण

	अगर (((vअगर->type == NL80211_IFTYPE_AP) ||
	     (vअगर->type == NL80211_IFTYPE_P2P_GO)) &&
	    (ieee80211_is_action(wh->frame_control))) अणु
		काष्ठा rsi_sta *rsta = rsi_find_sta(common, wh->addr1);

		अगर (rsta)
			mgmt_desc->sta_id = tx_params->sta_id;
		अन्यथा
			वापस -EINVAL;
	पूर्ण
	mgmt_desc->rate_info |=
		cpu_to_le16((tx_params->vap_id << RSI_DESC_VAP_ID_OFST) &
			    RSI_DESC_VAP_ID_MASK);

	वापस 0;
पूर्ण

/* This function prepares descriptor क्रम given data packet */
पूर्णांक rsi_prepare_data_desc(काष्ठा rsi_common *common, काष्ठा sk_buff *skb)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_hdr *wh = शून्य;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा skb_info *tx_params;
	काष्ठा rsi_data_desc *data_desc;
	काष्ठा rsi_xtended_desc *xtend_desc;
	u8 ieee80211_size = MIN_802_11_HDR_LEN;
	u8 header_size;
	u8 vap_id = 0;
	u8 dword_align_bytes;
	u16 seq_num;

	info = IEEE80211_SKB_CB(skb);
	vअगर = info->control.vअगर;
	tx_params = (काष्ठा skb_info *)info->driver_data;

	header_size = FRAME_DESC_SZ + माप(काष्ठा rsi_xtended_desc);
	अगर (header_size > skb_headroom(skb)) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to send pkt\n", __func__);
		वापस -ENOSPC;
	पूर्ण
	skb_push(skb, header_size);
	dword_align_bytes = ((अचिन्हित दीर्घ)skb->data & 0x3f);
	अगर (header_size > skb_headroom(skb)) अणु
		rsi_dbg(ERR_ZONE, "%s: Not enough headroom\n", __func__);
		वापस -ENOSPC;
	पूर्ण
	skb_push(skb, dword_align_bytes);
	header_size += dword_align_bytes;

	tx_params->पूर्णांकernal_hdr_size = header_size;
	data_desc = (काष्ठा rsi_data_desc *)skb->data;
	स_रखो(data_desc, 0, header_size);

	xtend_desc = (काष्ठा rsi_xtended_desc *)&skb->data[FRAME_DESC_SZ];
	wh = (काष्ठा ieee80211_hdr *)&skb->data[header_size];
	seq_num = IEEE80211_SEQ_TO_SN(le16_to_cpu(wh->seq_ctrl));

	data_desc->xtend_desc_size = header_size - FRAME_DESC_SZ;

	अगर (ieee80211_is_data_qos(wh->frame_control)) अणु
		ieee80211_size += 2;
		data_desc->mac_flags |= cpu_to_le16(RSI_QOS_ENABLE);
	पूर्ण

	अगर (((vअगर->type == NL80211_IFTYPE_STATION) ||
	     (vअगर->type == NL80211_IFTYPE_P2P_CLIENT)) &&
	    (adapter->ps_state == PS_ENABLED))
		wh->frame_control |= cpu_to_le16(RSI_SET_PS_ENABLE);

	अगर ((!(info->flags & IEEE80211_TX_INTFL_DONT_ENCRYPT)) &&
	    (common->secinfo.security_enable)) अणु
		अगर (rsi_is_cipher_wep(common))
			ieee80211_size += 4;
		अन्यथा
			ieee80211_size += 8;
		data_desc->mac_flags |= cpu_to_le16(RSI_ENCRYPT_PKT);
	पूर्ण
	rsi_set_len_qno(&data_desc->len_qno, (skb->len - FRAME_DESC_SZ),
			RSI_WIFI_DATA_Q);
	data_desc->header_len = ieee80211_size;

	अगर (common->min_rate != RSI_RATE_AUTO) अणु
		/* Send fixed rate */
		data_desc->frame_info = cpu_to_le16(RATE_INFO_ENABLE);
		data_desc->rate_info = cpu_to_le16(common->min_rate);

		अगर (conf_is_ht40(&common->priv->hw->conf))
			data_desc->bbp_info = cpu_to_le16(FULL40M_ENABLE);

		अगर ((common->vअगर_info[0].sgi) && (common->min_rate & 0x100)) अणु
		       /* Only MCS rates */
			data_desc->rate_info |=
				cpu_to_le16(ENABLE_SHORTGI_RATE);
		पूर्ण
	पूर्ण

	अगर (skb->protocol == cpu_to_be16(ETH_P_PAE)) अणु
		rsi_dbg(INFO_ZONE, "*** Tx EAPOL ***\n");

		data_desc->frame_info = cpu_to_le16(RATE_INFO_ENABLE);
		अगर (common->band == NL80211_BAND_5GHZ)
			data_desc->rate_info = cpu_to_le16(RSI_RATE_6);
		अन्यथा
			data_desc->rate_info = cpu_to_le16(RSI_RATE_1);
		data_desc->mac_flags |= cpu_to_le16(RSI_REKEY_PURPOSE);
		data_desc->misc_flags |= RSI_FETCH_RETRY_CNT_FRM_HST;
#घोषणा EAPOL_RETRY_CNT 15
		xtend_desc->retry_cnt = EAPOL_RETRY_CNT;

		अगर (common->eapol4_confirm)
			skb->priority = VO_Q;
		अन्यथा
			rsi_set_len_qno(&data_desc->len_qno,
					(skb->len - FRAME_DESC_SZ),
					RSI_WIFI_MGMT_Q);
		अगर (((skb->len - header_size) == EAPOL4_PACKET_LEN) ||
		    ((skb->len - header_size) == EAPOL4_PACKET_LEN - 2)) अणु
			data_desc->misc_flags |=
				RSI_DESC_REQUIRE_CFM_TO_HOST;
			xtend_desc->confirm_frame_type = EAPOL4_CONFIRM;
		पूर्ण
	पूर्ण

	data_desc->mac_flags |= cpu_to_le16(seq_num & 0xfff);
	data_desc->qid_tid = ((skb->priority & 0xf) |
			      ((tx_params->tid & 0xf) << 4));
	data_desc->sta_id = tx_params->sta_id;

	अगर ((is_broadcast_ether_addr(wh->addr1)) ||
	    (is_multicast_ether_addr(wh->addr1))) अणु
		data_desc->frame_info = cpu_to_le16(RATE_INFO_ENABLE);
		data_desc->frame_info |= cpu_to_le16(RSI_BROADCAST_PKT);
		data_desc->sta_id = vap_id;

		अगर ((vअगर->type == NL80211_IFTYPE_AP) ||
		    (vअगर->type == NL80211_IFTYPE_P2P_GO)) अणु
			अगर (common->band == NL80211_BAND_5GHZ)
				data_desc->rate_info = cpu_to_le16(RSI_RATE_6);
			अन्यथा
				data_desc->rate_info = cpu_to_le16(RSI_RATE_1);
		पूर्ण
	पूर्ण
	अगर (((vअगर->type == NL80211_IFTYPE_AP) ||
	     (vअगर->type == NL80211_IFTYPE_P2P_GO)) &&
	    (ieee80211_has_moredata(wh->frame_control)))
		data_desc->frame_info |= cpu_to_le16(MORE_DATA_PRESENT);

	data_desc->rate_info |=
		cpu_to_le16((tx_params->vap_id << RSI_DESC_VAP_ID_OFST) &
			    RSI_DESC_VAP_ID_MASK);

	वापस 0;
पूर्ण

/* This function sends received data packet from driver to device */
पूर्णांक rsi_send_data_pkt(काष्ठा rsi_common *common, काष्ठा sk_buff *skb)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_bss_conf *bss;
	पूर्णांक status = -EINVAL;

	अगर (!skb)
		वापस 0;
	अगर (common->अगरace_करोwn)
		जाओ err;

	info = IEEE80211_SKB_CB(skb);
	अगर (!info->control.vअगर)
		जाओ err;
	vअगर = info->control.vअगर;
	bss = &vअगर->bss_conf;

	अगर (((vअगर->type == NL80211_IFTYPE_STATION) ||
	     (vअगर->type == NL80211_IFTYPE_P2P_CLIENT)) &&
	    (!bss->assoc))
		जाओ err;

	status = rsi_send_pkt_to_bus(common, skb);
	अगर (status)
		rsi_dbg(ERR_ZONE, "%s: Failed to write pkt\n", __func__);

err:
	++common->tx_stats.total_tx_pkt_मुक्तd[skb->priority];
	rsi_indicate_tx_status(adapter, skb, status);
	वापस status;
पूर्ण

/**
 * rsi_send_mgmt_pkt() - This functions sends the received management packet
 *			 from driver to device.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @skb: Poपूर्णांकer to the socket buffer काष्ठाure.
 *
 * Return: status: 0 on success, -1 on failure.
 */
पूर्णांक rsi_send_mgmt_pkt(काष्ठा rsi_common *common,
		      काष्ठा sk_buff *skb)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा ieee80211_bss_conf *bss;
	काष्ठा ieee80211_hdr *wh;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा skb_info *tx_params;
	काष्ठा rsi_mgmt_desc *mgmt_desc;
	काष्ठा rsi_xtended_desc *xtend_desc;
	पूर्णांक status = -E2BIG;
	u8 header_size;

	info = IEEE80211_SKB_CB(skb);
	tx_params = (काष्ठा skb_info *)info->driver_data;
	header_size = tx_params->पूर्णांकernal_hdr_size;

	अगर (tx_params->flags & INTERNAL_MGMT_PKT) अणु
		status = adapter->host_पूर्णांकf_ops->ग_लिखो_pkt(common->priv,
							   (u8 *)skb->data,
							   skb->len);
		अगर (status) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to write the packet\n", __func__);
		पूर्ण
		dev_kमुक्त_skb(skb);
		वापस status;
	पूर्ण

	bss = &info->control.vअगर->bss_conf;
	wh = (काष्ठा ieee80211_hdr *)&skb->data[header_size];
	mgmt_desc = (काष्ठा rsi_mgmt_desc *)skb->data;
	xtend_desc = (काष्ठा rsi_xtended_desc *)&skb->data[FRAME_DESC_SZ];

	/* Indicate to firmware to give cfm क्रम probe */
	अगर (ieee80211_is_probe_req(wh->frame_control) && !bss->assoc) अणु
		rsi_dbg(INFO_ZONE,
			"%s: blocking mgmt queue\n", __func__);
		mgmt_desc->misc_flags = RSI_DESC_REQUIRE_CFM_TO_HOST;
		xtend_desc->confirm_frame_type = PROBEREQ_CONFIRM;
		common->mgmt_q_block = true;
		rsi_dbg(INFO_ZONE, "Mgmt queue blocked\n");
	पूर्ण

	status = rsi_send_pkt_to_bus(common, skb);
	अगर (status)
		rsi_dbg(ERR_ZONE, "%s: Failed to write the packet\n", __func__);

	rsi_indicate_tx_status(common->priv, skb, status);
	वापस status;
पूर्ण

पूर्णांक rsi_send_bt_pkt(काष्ठा rsi_common *common, काष्ठा sk_buff *skb)
अणु
	पूर्णांक status = -EINVAL;
	u8 header_size = 0;
	काष्ठा rsi_bt_desc *bt_desc;
	u8 queueno = ((skb->data[1] >> 4) & 0xf);

	अगर (queueno == RSI_BT_MGMT_Q) अणु
		status = rsi_send_pkt_to_bus(common, skb);
		अगर (status)
			rsi_dbg(ERR_ZONE, "%s: Failed to write bt mgmt pkt\n",
				__func__);
		जाओ out;
	पूर्ण
	header_size = FRAME_DESC_SZ;
	अगर (header_size > skb_headroom(skb)) अणु
		rsi_dbg(ERR_ZONE, "%s: Not enough headroom\n", __func__);
		status = -ENOSPC;
		जाओ out;
	पूर्ण
	skb_push(skb, header_size);
	स_रखो(skb->data, 0, header_size);
	bt_desc = (काष्ठा rsi_bt_desc *)skb->data;

	rsi_set_len_qno(&bt_desc->len_qno, (skb->len - FRAME_DESC_SZ),
			RSI_BT_DATA_Q);
	bt_desc->bt_pkt_type = cpu_to_le16(bt_cb(skb)->pkt_type);

	status = rsi_send_pkt_to_bus(common, skb);
	अगर (status)
		rsi_dbg(ERR_ZONE, "%s: Failed to write bt pkt\n", __func__);

out:
	dev_kमुक्त_skb(skb);
	वापस status;
पूर्ण

पूर्णांक rsi_prepare_beacon(काष्ठा rsi_common *common, काष्ठा sk_buff *skb)
अणु
	काष्ठा rsi_hw *adapter = (काष्ठा rsi_hw *)common->priv;
	काष्ठा rsi_data_desc *bcn_frm;
	काष्ठा ieee80211_hw *hw = common->priv->hw;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा sk_buff *mac_bcn;
	u8 vap_id = 0, i;
	u16 tim_offset = 0;

	क्रम (i = 0; i < RSI_MAX_VIFS; i++) अणु
		vअगर = adapter->vअगरs[i];
		अगर (!vअगर)
			जारी;
		अगर ((vअगर->type == NL80211_IFTYPE_AP) ||
		    (vअगर->type == NL80211_IFTYPE_P2P_GO))
			अवरोध;
	पूर्ण
	अगर (!vअगर)
		वापस -EINVAL;
	mac_bcn = ieee80211_beacon_get_tim(adapter->hw,
					   vअगर,
					   &tim_offset, शून्य);
	अगर (!mac_bcn) अणु
		rsi_dbg(ERR_ZONE, "Failed to get beacon from mac80211\n");
		वापस -EINVAL;
	पूर्ण

	common->beacon_cnt++;
	bcn_frm = (काष्ठा rsi_data_desc *)skb->data;
	rsi_set_len_qno(&bcn_frm->len_qno, mac_bcn->len, RSI_WIFI_DATA_Q);
	bcn_frm->header_len = MIN_802_11_HDR_LEN;
	bcn_frm->frame_info = cpu_to_le16(RSI_DATA_DESC_MAC_BBP_INFO |
					  RSI_DATA_DESC_NO_ACK_IND |
					  RSI_DATA_DESC_BEACON_FRAME |
					  RSI_DATA_DESC_INSERT_TSF |
					  RSI_DATA_DESC_INSERT_SEQ_NO |
					  RATE_INFO_ENABLE);
	bcn_frm->rate_info = cpu_to_le16(vap_id << 14);
	bcn_frm->qid_tid = BEACON_HW_Q;

	अगर (conf_is_ht40_plus(conf)) अणु
		bcn_frm->bbp_info = cpu_to_le16(LOWER_20_ENABLE);
		bcn_frm->bbp_info |= cpu_to_le16(LOWER_20_ENABLE >> 12);
	पूर्ण अन्यथा अगर (conf_is_ht40_minus(conf)) अणु
		bcn_frm->bbp_info = cpu_to_le16(UPPER_20_ENABLE);
		bcn_frm->bbp_info |= cpu_to_le16(UPPER_20_ENABLE >> 12);
	पूर्ण

	अगर (common->band == NL80211_BAND_2GHZ)
		bcn_frm->bbp_info |= cpu_to_le16(RSI_RATE_1);
	अन्यथा
		bcn_frm->bbp_info |= cpu_to_le16(RSI_RATE_6);

	अगर (mac_bcn->data[tim_offset + 2] == 0)
		bcn_frm->frame_info |= cpu_to_le16(RSI_DATA_DESC_DTIM_BEACON);

	स_नकल(&skb->data[FRAME_DESC_SZ], mac_bcn->data, mac_bcn->len);
	skb_put(skb, mac_bcn->len + FRAME_DESC_SZ);

	dev_kमुक्त_skb(mac_bcn);

	वापस 0;
पूर्ण

अटल व्योम bl_cmd_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा rsi_hw *adapter = from_समयr(adapter, t, bl_cmd_समयr);

	adapter->blcmd_समयr_expired = true;
	del_समयr(&adapter->bl_cmd_समयr);
पूर्ण

अटल पूर्णांक bl_start_cmd_समयr(काष्ठा rsi_hw *adapter, u32 समयout)
अणु
	समयr_setup(&adapter->bl_cmd_समयr, bl_cmd_समयout, 0);
	adapter->bl_cmd_समयr.expires = (msecs_to_jअगरfies(समयout) + jअगरfies);

	adapter->blcmd_समयr_expired = false;
	add_समयr(&adapter->bl_cmd_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक bl_stop_cmd_समयr(काष्ठा rsi_hw *adapter)
अणु
	adapter->blcmd_समयr_expired = false;
	अगर (समयr_pending(&adapter->bl_cmd_समयr))
		del_समयr(&adapter->bl_cmd_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक bl_ग_लिखो_cmd(काष्ठा rsi_hw *adapter, u8 cmd, u8 exp_resp,
			u16 *cmd_resp)
अणु
	काष्ठा rsi_host_पूर्णांकf_ops *hअगर_ops = adapter->host_पूर्णांकf_ops;
	u32 regin_val = 0, regout_val = 0;
	u32 regin_input = 0;
	u8 output = 0;
	पूर्णांक status;

	regin_input = (REGIN_INPUT | adapter->priv->coex_mode);

	जबतक (!adapter->blcmd_समयr_expired) अणु
		regin_val = 0;
		status = hअगर_ops->master_reg_पढ़ो(adapter, SWBL_REGIN,
						  &regin_val, 2);
		अगर (status < 0) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Command %0x REGIN reading failed..\n",
				__func__, cmd);
			वापस status;
		पूर्ण
		mdelay(1);
		अगर ((regin_val >> 12) != REGIN_VALID)
			अवरोध;
	पूर्ण
	अगर (adapter->blcmd_समयr_expired) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Command %0x REGIN reading timed out..\n",
			__func__, cmd);
		वापस -ETIMEDOUT;
	पूर्ण

	rsi_dbg(INFO_ZONE,
		"Issuing write to Regin val:%0x sending cmd:%0x\n",
		regin_val, (cmd | regin_input << 8));
	status = hअगर_ops->master_reg_ग_लिखो(adapter, SWBL_REGIN,
					   (cmd | regin_input << 8), 2);
	अगर (status < 0)
		वापस status;
	mdelay(1);

	अगर (cmd == LOAD_HOSTED_FW || cmd == JUMP_TO_ZERO_PC) अणु
		/* JUMP_TO_ZERO_PC करोesn't expect
		 * any response. So वापस from here
		 */
		वापस 0;
	पूर्ण

	जबतक (!adapter->blcmd_समयr_expired) अणु
		regout_val = 0;
		status = hअगर_ops->master_reg_पढ़ो(adapter, SWBL_REGOUT,
					     &regout_val, 2);
		अगर (status < 0) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Command %0x REGOUT reading failed..\n",
				__func__, cmd);
			वापस status;
		पूर्ण
		mdelay(1);
		अगर ((regout_val >> 8) == REGOUT_VALID)
			अवरोध;
	पूर्ण
	अगर (adapter->blcmd_समयr_expired) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Command %0x REGOUT reading timed out..\n",
			__func__, cmd);
		वापस status;
	पूर्ण

	*cmd_resp = ((u16 *)&regout_val)[0] & 0xffff;

	output = ((u8 *)&regout_val)[0] & 0xff;

	status = hअगर_ops->master_reg_ग_लिखो(adapter, SWBL_REGOUT,
					   (cmd | REGOUT_INVALID << 8), 2);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Command %0x REGOUT writing failed..\n",
			__func__, cmd);
		वापस status;
	पूर्ण
	mdelay(1);

	अगर (output != exp_resp) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Recvd resp %x for cmd %0x\n",
			__func__, output, cmd);
		वापस -EINVAL;
	पूर्ण
	rsi_dbg(INFO_ZONE,
		"%s: Recvd Expected resp %x for cmd %0x\n",
		__func__, output, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक bl_cmd(काष्ठा rsi_hw *adapter, u8 cmd, u8 exp_resp, अक्षर *str)
अणु
	u16 regout_val = 0;
	u32 समयout;
	पूर्णांक status;

	अगर ((cmd == खातापूर्ण_REACHED) || (cmd == PING_VALID) || (cmd == PONG_VALID))
		समयout = BL_BURN_TIMEOUT;
	अन्यथा
		समयout = BL_CMD_TIMEOUT;

	bl_start_cmd_समयr(adapter, समयout);
	status = bl_ग_लिखो_cmd(adapter, cmd, exp_resp, &regout_val);
	अगर (status < 0) अणु
		bl_stop_cmd_समयr(adapter);
		rsi_dbg(ERR_ZONE,
			"%s: Command %s (%0x) writing failed..\n",
			__func__, str, cmd);
		वापस status;
	पूर्ण
	bl_stop_cmd_समयr(adapter);
	वापस 0;
पूर्ण

#घोषणा CHECK_SUM_OFFSET 20
#घोषणा LEN_OFFSET 8
#घोषणा ADDR_OFFSET 16
अटल पूर्णांक bl_ग_लिखो_header(काष्ठा rsi_hw *adapter, u8 *flash_content,
			   u32 content_size)
अणु
	काष्ठा rsi_host_पूर्णांकf_ops *hअगर_ops = adapter->host_पूर्णांकf_ops;
	काष्ठा bl_header *bl_hdr;
	u32 ग_लिखो_addr, ग_लिखो_len;
	पूर्णांक status;

	bl_hdr = kzalloc(माप(*bl_hdr), GFP_KERNEL);
	अगर (!bl_hdr)
		वापस -ENOMEM;

	bl_hdr->flags = 0;
	bl_hdr->image_no = cpu_to_le32(adapter->priv->coex_mode);
	bl_hdr->check_sum =
		cpu_to_le32(*(u32 *)&flash_content[CHECK_SUM_OFFSET]);
	bl_hdr->flash_start_address =
		cpu_to_le32(*(u32 *)&flash_content[ADDR_OFFSET]);
	bl_hdr->flash_len = cpu_to_le32(*(u32 *)&flash_content[LEN_OFFSET]);
	ग_लिखो_len = माप(काष्ठा bl_header);

	अगर (adapter->rsi_host_पूर्णांकf == RSI_HOST_INTF_USB) अणु
		ग_लिखो_addr = PING_BUFFER_ADDRESS;
		status = hअगर_ops->ग_लिखो_reg_multiple(adapter, ग_लिखो_addr,
						 (u8 *)bl_hdr, ग_लिखो_len);
		अगर (status < 0) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to load Version/CRC structure\n",
				__func__);
			जाओ fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखो_addr = PING_BUFFER_ADDRESS >> 16;
		status = hअगर_ops->master_access_msword(adapter, ग_लिखो_addr);
		अगर (status < 0) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Unable to set ms word to common reg\n",
				__func__);
			जाओ fail;
		पूर्ण
		ग_लिखो_addr = RSI_SD_REQUEST_MASTER |
			     (PING_BUFFER_ADDRESS & 0xFFFF);
		status = hअगर_ops->ग_लिखो_reg_multiple(adapter, ग_लिखो_addr,
						 (u8 *)bl_hdr, ग_लिखो_len);
		अगर (status < 0) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to load Version/CRC structure\n",
				__func__);
			जाओ fail;
		पूर्ण
	पूर्ण
	status = 0;
fail:
	kमुक्त(bl_hdr);
	वापस status;
पूर्ण

अटल u32 पढ़ो_flash_capacity(काष्ठा rsi_hw *adapter)
अणु
	u32 flash_sz = 0;

	अगर ((adapter->host_पूर्णांकf_ops->master_reg_पढ़ो(adapter, FLASH_SIZE_ADDR,
						     &flash_sz, 2)) < 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Flash size reading failed..\n",
			__func__);
		वापस 0;
	पूर्ण
	rsi_dbg(INIT_ZONE, "Flash capacity: %d KiloBytes\n", flash_sz);

	वापस (flash_sz * 1024); /* Return size in kbytes */
पूर्ण

अटल पूर्णांक ping_pong_ग_लिखो(काष्ठा rsi_hw *adapter, u8 cmd, u8 *addr, u32 size)
अणु
	काष्ठा rsi_host_पूर्णांकf_ops *hअगर_ops = adapter->host_पूर्णांकf_ops;
	u32 block_size = adapter->block_size;
	u32 cmd_addr;
	u16 cmd_resp, cmd_req;
	u8 *str;
	पूर्णांक status;

	अगर (cmd == PING_WRITE) अणु
		cmd_addr = PING_BUFFER_ADDRESS;
		cmd_resp = PONG_AVAIL;
		cmd_req = PING_VALID;
		str = "PING_VALID";
	पूर्ण अन्यथा अणु
		cmd_addr = PONG_BUFFER_ADDRESS;
		cmd_resp = PING_AVAIL;
		cmd_req = PONG_VALID;
		str = "PONG_VALID";
	पूर्ण

	status = hअगर_ops->load_data_master_ग_लिखो(adapter, cmd_addr, size,
					    block_size, addr);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to write blk at addr %0x\n",
			__func__, *addr);
		वापस status;
	पूर्ण

	status = bl_cmd(adapter, cmd_req, cmd_resp, str);
	अगर (status)
		वापस status;

	वापस 0;
पूर्ण

अटल पूर्णांक स्वतः_fw_upgrade(काष्ठा rsi_hw *adapter, u8 *flash_content,
			   u32 content_size)
अणु
	u8 cmd;
	u32 temp_content_size, num_flash, index;
	u32 flash_start_address;
	पूर्णांक status;

	अगर (content_size > MAX_FLASH_खाता_SIZE) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Flash Content size is more than 400K %u\n",
			__func__, MAX_FLASH_खाता_SIZE);
		वापस -EINVAL;
	पूर्ण

	flash_start_address = *(u32 *)&flash_content[FLASH_START_ADDRESS];
	rsi_dbg(INFO_ZONE, "flash start address: %08x\n", flash_start_address);

	अगर (flash_start_address < FW_IMAGE_MIN_ADDRESS) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Fw image Flash Start Address is less than 64K\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर (flash_start_address % FLASH_SECTOR_SIZE) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Flash Start Address is not multiple of 4K\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	अगर ((flash_start_address + content_size) > adapter->flash_capacity) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Flash Content will cross max flash size\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	temp_content_size  = content_size;
	num_flash = content_size / FLASH_WRITE_CHUNK_SIZE;

	rsi_dbg(INFO_ZONE, "content_size: %d, num_flash: %d\n",
		content_size, num_flash);

	क्रम (index = 0; index <= num_flash; index++) अणु
		rsi_dbg(INFO_ZONE, "flash index: %d\n", index);
		अगर (index != num_flash) अणु
			content_size = FLASH_WRITE_CHUNK_SIZE;
			rsi_dbg(INFO_ZONE, "QSPI content_size:%d\n",
				content_size);
		पूर्ण अन्यथा अणु
			content_size =
				temp_content_size % FLASH_WRITE_CHUNK_SIZE;
			rsi_dbg(INFO_ZONE,
				"Writing last sector content_size:%d\n",
				content_size);
			अगर (!content_size) अणु
				rsi_dbg(INFO_ZONE, "instruction size zero\n");
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (index % 2)
			cmd = PING_WRITE;
		अन्यथा
			cmd = PONG_WRITE;

		status = ping_pong_ग_लिखो(adapter, cmd, flash_content,
					 content_size);
		अगर (status) अणु
			rsi_dbg(ERR_ZONE, "%s: Unable to load %d block\n",
				__func__, index);
			वापस status;
		पूर्ण

		rsi_dbg(INFO_ZONE,
			"%s: Successfully loaded %d instructions\n",
			__func__, index);
		flash_content += content_size;
	पूर्ण

	status = bl_cmd(adapter, खातापूर्ण_REACHED, FW_LOADING_SUCCESSFUL,
			"EOF_REACHED");
	अगर (status)
		वापस status;

	rsi_dbg(INFO_ZONE, "FW loading is done and FW is running..\n");
	वापस 0;
पूर्ण

अटल पूर्णांक rsi_hal_prepare_fwload(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_host_पूर्णांकf_ops *hअगर_ops = adapter->host_पूर्णांकf_ops;
	u32 regout_val = 0;
	पूर्णांक status;

	bl_start_cmd_समयr(adapter, BL_CMD_TIMEOUT);

	जबतक (!adapter->blcmd_समयr_expired) अणु
		status = hअगर_ops->master_reg_पढ़ो(adapter, SWBL_REGOUT,
						  &regout_val,
						  RSI_COMMON_REG_SIZE);
		अगर (status < 0) अणु
			bl_stop_cmd_समयr(adapter);
			rsi_dbg(ERR_ZONE,
				"%s: REGOUT read failed\n", __func__);
			वापस status;
		पूर्ण
		mdelay(1);
		अगर ((regout_val >> 8) == REGOUT_VALID)
			अवरोध;
	पूर्ण
	अगर (adapter->blcmd_समयr_expired) अणु
		rsi_dbg(ERR_ZONE, "%s: REGOUT read timedout\n", __func__);
		rsi_dbg(ERR_ZONE,
			"%s: Soft boot loader not present\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण
	bl_stop_cmd_समयr(adapter);

	rsi_dbg(INFO_ZONE, "Received Board Version Number: %x\n",
		(regout_val & 0xff));

	status = hअगर_ops->master_reg_ग_लिखो(adapter, SWBL_REGOUT,
					   (REGOUT_INVALID |
					    REGOUT_INVALID << 8),
					   RSI_COMMON_REG_SIZE);
	अगर (status < 0)
		rsi_dbg(ERR_ZONE, "%s: REGOUT writing failed..\n", __func__);
	अन्यथा
		rsi_dbg(INFO_ZONE,
			"===> Device is ready to load firmware <===\n");

	वापस status;
पूर्ण

अटल पूर्णांक rsi_load_9113_firmware(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_common *common = adapter->priv;
	स्थिर काष्ठा firmware *fw_entry = शून्य;
	u32 content_size;
	u16 पंचांगp_regout_val = 0;
	काष्ठा ta_metadata *metadata_p;
	पूर्णांक status;

	status = bl_cmd(adapter, CONFIG_AUTO_READ_MODE, CMD_PASS,
			"AUTO_READ_CMD");
	अगर (status < 0)
		वापस status;

	adapter->flash_capacity = पढ़ो_flash_capacity(adapter);
	अगर (adapter->flash_capacity <= 0) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Unable to read flash size from EEPROM\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	metadata_p = &metadata_flash_content[adapter->priv->coex_mode];

	rsi_dbg(INIT_ZONE, "%s: Loading file %s\n", __func__, metadata_p->name);
	adapter->fw_file_name = metadata_p->name;

	status = request_firmware(&fw_entry, metadata_p->name, adapter->device);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to open file %s\n",
			__func__, metadata_p->name);
		वापस status;
	पूर्ण
	content_size = fw_entry->size;
	rsi_dbg(INFO_ZONE, "FW Length = %d bytes\n", content_size);

	/* Get the firmware version */
	common->lmac_ver.ver.info.fw_ver[0] =
		fw_entry->data[LMAC_VER_OFFSET_9113] & 0xFF;
	common->lmac_ver.ver.info.fw_ver[1] =
		fw_entry->data[LMAC_VER_OFFSET_9113 + 1] & 0xFF;
	common->lmac_ver.major =
		fw_entry->data[LMAC_VER_OFFSET_9113 + 2] & 0xFF;
	common->lmac_ver.release_num =
		fw_entry->data[LMAC_VER_OFFSET_9113 + 3] & 0xFF;
	common->lmac_ver.minor =
		fw_entry->data[LMAC_VER_OFFSET_9113 + 4] & 0xFF;
	common->lmac_ver.patch_num = 0;
	rsi_prपूर्णांक_version(common);

	status = bl_ग_लिखो_header(adapter, (u8 *)fw_entry->data, content_size);
	अगर (status) अणु
		rsi_dbg(ERR_ZONE,
			"%s: RPS Image header loading failed\n",
			__func__);
		जाओ fail;
	पूर्ण

	bl_start_cmd_समयr(adapter, BL_CMD_TIMEOUT);
	status = bl_ग_लिखो_cmd(adapter, CHECK_CRC, CMD_PASS, &पंचांगp_regout_val);
	अगर (status) अणु
		bl_stop_cmd_समयr(adapter);
		rsi_dbg(ERR_ZONE,
			"%s: CHECK_CRC Command writing failed..\n",
			__func__);
		अगर ((पंचांगp_regout_val & 0xff) == CMD_FAIL) अणु
			rsi_dbg(ERR_ZONE,
				"CRC Fail.. Proceeding to Upgrade mode\n");
			जाओ fw_upgrade;
		पूर्ण
	पूर्ण
	bl_stop_cmd_समयr(adapter);

	status = bl_cmd(adapter, POLLING_MODE, CMD_PASS, "POLLING_MODE");
	अगर (status)
		जाओ fail;

load_image_cmd:
	status = bl_cmd(adapter, LOAD_HOSTED_FW, LOADING_INITIATED,
			"LOAD_HOSTED_FW");
	अगर (status)
		जाओ fail;
	rsi_dbg(INFO_ZONE, "Load Image command passed..\n");
	जाओ success;

fw_upgrade:
	status = bl_cmd(adapter, BURN_HOSTED_FW, SEND_RPS_खाता, "FW_UPGRADE");
	अगर (status)
		जाओ fail;

	rsi_dbg(INFO_ZONE, "Burn Command Pass.. Upgrading the firmware\n");

	status = स्वतः_fw_upgrade(adapter, (u8 *)fw_entry->data, content_size);
	अगर (status == 0) अणु
		rsi_dbg(ERR_ZONE, "Firmware upgradation Done\n");
		जाओ load_image_cmd;
	पूर्ण
	rsi_dbg(ERR_ZONE, "Firmware upgrade failed\n");

	status = bl_cmd(adapter, CONFIG_AUTO_READ_MODE, CMD_PASS,
			"AUTO_READ_MODE");
	अगर (status)
		जाओ fail;

success:
	rsi_dbg(ERR_ZONE, "***** Firmware Loading successful *****\n");
	release_firmware(fw_entry);
	वापस 0;

fail:
	rsi_dbg(ERR_ZONE, "##### Firmware loading failed #####\n");
	release_firmware(fw_entry);
	वापस status;
पूर्ण

अटल पूर्णांक rsi_load_9116_firmware(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_common *common = adapter->priv;
	काष्ठा rsi_host_पूर्णांकf_ops *hअगर_ops = adapter->host_पूर्णांकf_ops;
	स्थिर काष्ठा firmware *fw_entry;
	काष्ठा ta_metadata *metadata_p;
	u8 *ta_firmware, *fw_p;
	काष्ठा bootload_ds bootload_ds;
	u32 inकाष्ठाions_sz, base_address;
	u16 block_size = adapter->block_size;
	u32 dest, len;
	पूर्णांक status, cnt;

	rsi_dbg(INIT_ZONE, "***** Load 9116 TA Instructions *****\n");

	अगर (adapter->rsi_host_पूर्णांकf == RSI_HOST_INTF_USB) अणु
		status = bl_cmd(adapter, POLLING_MODE, CMD_PASS,
				"POLLING_MODE");
		अगर (status < 0)
			वापस status;
	पूर्ण

	status = hअगर_ops->master_reg_ग_लिखो(adapter, MEM_ACCESS_CTRL_FROM_HOST,
					   RAM_384K_ACCESS_FROM_TA,
					   RSI_9116_REG_SIZE);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to access full RAM memory\n",
			__func__);
		वापस status;
	पूर्ण

	metadata_p = &metadata[adapter->priv->coex_mode];
	rsi_dbg(INIT_ZONE, "%s: loading file %s\n", __func__, metadata_p->name);
	status = request_firmware(&fw_entry, metadata_p->name, adapter->device);
	अगर (status < 0) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed to open file %s\n",
			__func__, metadata_p->name);
		वापस status;
	पूर्ण

	ta_firmware = kmemdup(fw_entry->data, fw_entry->size, GFP_KERNEL);
	अगर (!ta_firmware)
		जाओ fail_release_fw;
	fw_p = ta_firmware;
	inकाष्ठाions_sz = fw_entry->size;
	rsi_dbg(INFO_ZONE, "FW Length = %d bytes\n", inकाष्ठाions_sz);

	common->lmac_ver.major = ta_firmware[LMAC_VER_OFFSET_9116];
	common->lmac_ver.minor = ta_firmware[LMAC_VER_OFFSET_9116 + 1];
	common->lmac_ver.release_num = ta_firmware[LMAC_VER_OFFSET_9116 + 2];
	common->lmac_ver.patch_num = ta_firmware[LMAC_VER_OFFSET_9116 + 3];
	common->lmac_ver.ver.info.fw_ver[0] =
		ta_firmware[LMAC_VER_OFFSET_9116 + 4];

	अगर (inकाष्ठाions_sz % FW_ALIGN_SIZE)
		inकाष्ठाions_sz +=
			(FW_ALIGN_SIZE - (inकाष्ठाions_sz % FW_ALIGN_SIZE));
	rsi_dbg(INFO_ZONE, "instructions_sz : %d\n", inकाष्ठाions_sz);

	अगर (*(u16 *)fw_p == RSI_9116_FW_MAGIC_WORD) अणु
		स_नकल(&bootload_ds, fw_p, माप(काष्ठा bootload_ds));
		fw_p += le16_to_cpu(bootload_ds.offset);
		rsi_dbg(INFO_ZONE, "FW start = %x\n", *(u32 *)fw_p);

		cnt = 0;
		करो अणु
			rsi_dbg(ERR_ZONE, "%s: Loading chunk %d\n",
				__func__, cnt);

			dest = le32_to_cpu(bootload_ds.bl_entry[cnt].dst_addr);
			len = le32_to_cpu(bootload_ds.bl_entry[cnt].control) &
			      RSI_BL_CTRL_LEN_MASK;
			rsi_dbg(INFO_ZONE, "length %d destination %x\n",
				len, dest);

			status = hअगर_ops->load_data_master_ग_लिखो(adapter, dest,
								 len,
								 block_size,
								 fw_p);
			अगर (status < 0) अणु
				rsi_dbg(ERR_ZONE,
					"Failed to load chunk %d\n", cnt);
				अवरोध;
			पूर्ण
			fw_p += len;
			अगर (le32_to_cpu(bootload_ds.bl_entry[cnt].control) &
			    RSI_BL_CTRL_LAST_ENTRY)
				अवरोध;
			cnt++;
		पूर्ण जबतक (1);
	पूर्ण अन्यथा अणु
		base_address = metadata_p->address;
		status = hअगर_ops->load_data_master_ग_लिखो(adapter,
							 base_address,
							 inकाष्ठाions_sz,
							 block_size,
							 ta_firmware);
	पूर्ण
	अगर (status) अणु
		rsi_dbg(ERR_ZONE,
			"%s: Unable to load %s blk\n",
			__func__, metadata_p->name);
		जाओ fail_मुक्त_fw;
	पूर्ण

	rsi_dbg(INIT_ZONE, "%s: Successfully loaded %s instructions\n",
		__func__, metadata_p->name);

	अगर (adapter->rsi_host_पूर्णांकf == RSI_HOST_INTF_SDIO) अणु
		अगर (hअगर_ops->ta_reset(adapter))
			rsi_dbg(ERR_ZONE, "Unable to put ta in reset\n");
	पूर्ण अन्यथा अणु
		अगर (bl_cmd(adapter, JUMP_TO_ZERO_PC,
			   CMD_PASS, "JUMP_TO_ZERO") < 0)
			rsi_dbg(INFO_ZONE, "Jump to zero command failed\n");
		अन्यथा
			rsi_dbg(INFO_ZONE, "Jump to zero command successful\n");
	पूर्ण

fail_मुक्त_fw:
	kमुक्त(ta_firmware);
fail_release_fw:
	release_firmware(fw_entry);

	वापस status;
पूर्ण

पूर्णांक rsi_hal_device_init(काष्ठा rsi_hw *adapter)
अणु
	काष्ठा rsi_common *common = adapter->priv;
	पूर्णांक status;

	चयन (adapter->device_model) अणु
	हाल RSI_DEV_9113:
		status = rsi_hal_prepare_fwload(adapter);
		अगर (status < 0)
			वापस status;
		अगर (rsi_load_9113_firmware(adapter)) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to load TA instructions\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल RSI_DEV_9116:
		status = rsi_hal_prepare_fwload(adapter);
		अगर (status < 0)
			वापस status;
		अगर (rsi_load_9116_firmware(adapter)) अणु
			rsi_dbg(ERR_ZONE,
				"%s: Failed to load firmware to 9116 device\n",
				__func__);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	common->fsm_state = FSM_CARD_NOT_READY;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rsi_hal_device_init);

