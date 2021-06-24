<शैली गुरु>
/*
 * NXP Wireless LAN device driver: station event handling
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
#समावेश "wmm.h"
#समावेश "11n.h"

#घोषणा MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE    12

अटल पूर्णांक mwअगरiex_check_ibss_peer_capabilities(काष्ठा mwअगरiex_निजी *priv,
					        काष्ठा mwअगरiex_sta_node *sta_ptr,
					        काष्ठा sk_buff *event)
अणु
	पूर्णांक evt_len, ele_len;
	u8 *curr;
	काष्ठा ieee_types_header *ele_hdr;
	काष्ठा mwअगरiex_ie_types_mgmt_frame *tlv_mgmt_frame;
	स्थिर काष्ठा ieee80211_ht_cap *ht_cap;
	स्थिर काष्ठा ieee80211_vht_cap *vht_cap;

	skb_pull(event, MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE);
	evt_len = event->len;
	curr = event->data;

	mwअगरiex_dbg_dump(priv->adapter, EVT_D, "ibss peer capabilities:",
			 event->data, event->len);

	skb_push(event, MWIFIEX_IBSS_CONNECT_EVT_FIX_SIZE);

	tlv_mgmt_frame = (व्योम *)curr;
	अगर (evt_len >= माप(*tlv_mgmt_frame) &&
	    le16_to_cpu(tlv_mgmt_frame->header.type) ==
	    TLV_TYPE_UAP_MGMT_FRAME) अणु
		/* Locate curr poपूर्णांकer to the start of beacon tlv,
		 * बारtamp 8 bytes, beacon पूर्णांकervel 2 bytes,
		 * capability info 2 bytes, totally 12 byte beacon header
		 */
		evt_len = le16_to_cpu(tlv_mgmt_frame->header.len);
		curr += (माप(*tlv_mgmt_frame) + 12);
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(priv->adapter, MSG,
			    "management frame tlv not found!\n");
		वापस 0;
	पूर्ण

	जबतक (evt_len >= माप(*ele_hdr)) अणु
		ele_hdr = (काष्ठा ieee_types_header *)curr;
		ele_len = ele_hdr->len;

		अगर (evt_len < ele_len + माप(*ele_hdr))
			अवरोध;

		चयन (ele_hdr->element_id) अणु
		हाल WLAN_EID_HT_CAPABILITY:
			sta_ptr->is_11n_enabled = true;
			ht_cap = (व्योम *)(ele_hdr + 2);
			sta_ptr->max_amsdu = le16_to_cpu(ht_cap->cap_info) &
				IEEE80211_HT_CAP_MAX_AMSDU ?
				MWIFIEX_TX_DATA_BUF_SIZE_8K :
				MWIFIEX_TX_DATA_BUF_SIZE_4K;
			mwअगरiex_dbg(priv->adapter, INFO,
				    "11n enabled!, max_amsdu : %d\n",
				    sta_ptr->max_amsdu);
			अवरोध;

		हाल WLAN_EID_VHT_CAPABILITY:
			sta_ptr->is_11ac_enabled = true;
			vht_cap = (व्योम *)(ele_hdr + 2);
			/* check VHT MAXMPDU capability */
			चयन (le32_to_cpu(vht_cap->vht_cap_info) & 0x3) अणु
			हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454:
				sta_ptr->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_12K;
				अवरोध;
			हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991:
				sta_ptr->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_8K;
				अवरोध;
			हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895:
				sta_ptr->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_4K;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			mwअगरiex_dbg(priv->adapter, INFO,
				    "11ac enabled!, max_amsdu : %d\n",
				    sta_ptr->max_amsdu);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		curr += (ele_len + माप(*ele_hdr));
		evt_len -= (ele_len + माप(*ele_hdr));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function resets the connection state.
 *
 * The function is invoked after receiving a disconnect event from firmware,
 * and perक्रमms the following actions -
 *      - Set media status to disconnected
 *      - Clean up Tx and Rx packets
 *      - Resets SNR/NF/RSSI value in driver
 *      - Resets security configurations in driver
 *      - Enables स्वतः data rate
 *      - Saves the previous SSID and BSSID so that they can
 *        be used क्रम re-association, अगर required
 *      - Erases current SSID and BSSID inक्रमmation
 *      - Sends a disconnect event to upper layers/applications.
 */
व्योम mwअगरiex_reset_connect_state(काष्ठा mwअगरiex_निजी *priv, u16 reason_code,
				 bool from_ap)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	अगर (!priv->media_connected)
		वापस;

	mwअगरiex_dbg(adapter, INFO,
		    "info: handles disconnect event\n");

	priv->media_connected = false;

	priv->scan_block = false;
	priv->port_खोलो = false;

	अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) &&
	    ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info)) अणु
		mwअगरiex_disable_all_tdls_links(priv);

		अगर (priv->adapter->स्वतः_tdls)
			mwअगरiex_clean_स्वतः_tdls(priv);
	पूर्ण

	/* Free Tx and Rx packets, report disconnect to upper layer */
	mwअगरiex_clean_txrx(priv);

	/* Reset SNR/NF/RSSI values */
	priv->data_rssi_last = 0;
	priv->data_nf_last = 0;
	priv->data_rssi_avg = 0;
	priv->data_nf_avg = 0;
	priv->bcn_rssi_last = 0;
	priv->bcn_nf_last = 0;
	priv->bcn_rssi_avg = 0;
	priv->bcn_nf_avg = 0;
	priv->rxpd_rate = 0;
	priv->rxpd_htinfo = 0;
	priv->sec_info.wpa_enabled = false;
	priv->sec_info.wpa2_enabled = false;
	priv->wpa_ie_len = 0;

	priv->sec_info.wapi_enabled = false;
	priv->wapi_ie_len = 0;
	priv->sec_info.wapi_key_on = false;

	priv->sec_info.encryption_mode = 0;

	/* Enable स्वतः data rate */
	priv->is_data_rate_स्वतः = true;
	priv->data_rate = 0;

	priv->assoc_resp_ht_param = 0;
	priv->ht_param_present = false;

	अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA ||
	     GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) && priv->hist_data)
		mwअगरiex_hist_data_reset(priv);

	अगर (priv->bss_mode == NL80211_IFTYPE_ADHOC) अणु
		priv->adhoc_state = ADHOC_IDLE;
		priv->adhoc_is_link_sensed = false;
	पूर्ण

	/*
	 * Memorize the previous SSID and BSSID so
	 * it could be used क्रम re-assoc
	 */

	mwअगरiex_dbg(adapter, INFO,
		    "info: previous SSID=%s, SSID len=%u\n",
		    priv->prev_ssid.ssid, priv->prev_ssid.ssid_len);

	mwअगरiex_dbg(adapter, INFO,
		    "info: current SSID=%s, SSID len=%u\n",
		    priv->curr_bss_params.bss_descriptor.ssid.ssid,
		    priv->curr_bss_params.bss_descriptor.ssid.ssid_len);

	स_नकल(&priv->prev_ssid,
	       &priv->curr_bss_params.bss_descriptor.ssid,
	       माप(काष्ठा cfg80211_ssid));

	स_नकल(priv->prev_bssid,
	       priv->curr_bss_params.bss_descriptor.mac_address, ETH_ALEN);

	/* Need to erase the current SSID and BSSID info */
	स_रखो(&priv->curr_bss_params, 0x00, माप(priv->curr_bss_params));

	adapter->tx_lock_flag = false;
	adapter->pps_uapsd_mode = false;

	अगर (test_bit(MWIFIEX_IS_CMD_TIMEDOUT, &adapter->work_flags) &&
	    adapter->curr_cmd)
		वापस;
	priv->media_connected = false;
	mwअगरiex_dbg(adapter, MSG,
		    "info: successfully disconnected from %pM: reason code %d\n",
		    priv->cfg_bssid, reason_code);
	अगर (priv->bss_mode == NL80211_IFTYPE_STATION ||
	    priv->bss_mode == NL80211_IFTYPE_P2P_CLIENT) अणु
		cfg80211_disconnected(priv->netdev, reason_code, शून्य, 0,
				      !from_ap, GFP_KERNEL);
	पूर्ण
	eth_zero_addr(priv->cfg_bssid);

	mwअगरiex_stop_net_dev_queue(priv->netdev, adapter);
	अगर (netअगर_carrier_ok(priv->netdev))
		netअगर_carrier_off(priv->netdev);

	अगर (!ISSUPP_FIRMWARE_SUPPLICANT(priv->adapter->fw_cap_info))
		वापस;

	mwअगरiex_send_cmd(priv, HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG,
			 HostCmd_ACT_GEN_REMOVE, 0, शून्य, false);
पूर्ण

अटल पूर्णांक mwअगरiex_parse_tdls_event(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा sk_buff *event_skb)
अणु
	पूर्णांक ret = 0;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा mwअगरiex_tdls_generic_event *tdls_evt =
			(व्योम *)event_skb->data + माप(adapter->event_cause);
	u8 *mac = tdls_evt->peer_mac;

	/* reserved 2 bytes are not mandatory in tdls event */
	अगर (event_skb->len < (माप(काष्ठा mwअगरiex_tdls_generic_event) -
			      माप(u16) - माप(adapter->event_cause))) अणु
		mwअगरiex_dbg(adapter, ERROR, "Invalid event length!\n");
		वापस -1;
	पूर्ण

	sta_ptr = mwअगरiex_get_sta_entry(priv, tdls_evt->peer_mac);
	अगर (!sta_ptr) अणु
		mwअगरiex_dbg(adapter, ERROR, "cannot get sta entry!\n");
		वापस -1;
	पूर्ण

	चयन (le16_to_cpu(tdls_evt->type)) अणु
	हाल TDLS_EVENT_LINK_TEAR_DOWN:
		cfg80211_tdls_oper_request(priv->netdev,
					   tdls_evt->peer_mac,
					   NL80211_TDLS_TEARDOWN,
					   le16_to_cpu(tdls_evt->u.reason_code),
					   GFP_KERNEL);
		अवरोध;
	हाल TDLS_EVENT_CHAN_SWITCH_RESULT:
		mwअगरiex_dbg(adapter, EVENT, "tdls channel switch result :\n");
		mwअगरiex_dbg(adapter, EVENT,
			    "status=0x%x, reason=0x%x cur_chan=%d\n",
			    tdls_evt->u.चयन_result.status,
			    tdls_evt->u.चयन_result.reason,
			    tdls_evt->u.चयन_result.cur_chan);

		/* tdls channel चयन failed */
		अगर (tdls_evt->u.चयन_result.status != 0) अणु
			चयन (tdls_evt->u.चयन_result.cur_chan) अणु
			हाल TDLS_BASE_CHANNEL:
				sta_ptr->tdls_status = TDLS_IN_BASE_CHAN;
				अवरोध;
			हाल TDLS_OFF_CHANNEL:
				sta_ptr->tdls_status = TDLS_IN_OFF_CHAN;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			वापस ret;
		पूर्ण

		/* tdls channel चयन success */
		चयन (tdls_evt->u.चयन_result.cur_chan) अणु
		हाल TDLS_BASE_CHANNEL:
			अगर (sta_ptr->tdls_status == TDLS_IN_BASE_CHAN)
				अवरोध;
			mwअगरiex_update_ralist_tx_छोड़ो_in_tdls_cs(priv, mac,
								  false);
			sta_ptr->tdls_status = TDLS_IN_BASE_CHAN;
			अवरोध;
		हाल TDLS_OFF_CHANNEL:
			अगर (sta_ptr->tdls_status == TDLS_IN_OFF_CHAN)
				अवरोध;
			mwअगरiex_update_ralist_tx_छोड़ो_in_tdls_cs(priv, mac,
								  true);
			sta_ptr->tdls_status = TDLS_IN_OFF_CHAN;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	हाल TDLS_EVENT_START_CHAN_SWITCH:
		mwअगरiex_dbg(adapter, EVENT, "tdls start channel switch...\n");
		sta_ptr->tdls_status = TDLS_CHAN_SWITCHING;
		अवरोध;
	हाल TDLS_EVENT_CHAN_SWITCH_STOPPED:
		mwअगरiex_dbg(adapter, EVENT,
			    "tdls chan switch stopped, reason=%d\n",
			    tdls_evt->u.cs_stop_reason);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mwअगरiex_process_uap_tx_छोड़ो(काष्ठा mwअगरiex_निजी *priv,
					 काष्ठा mwअगरiex_ie_types_header *tlv)
अणु
	काष्ठा mwअगरiex_tx_छोड़ो_tlv *tp;
	काष्ठा mwअगरiex_sta_node *sta_ptr;

	tp = (व्योम *)tlv;
	mwअगरiex_dbg(priv->adapter, EVENT,
		    "uap tx_pause: %pM pause=%d, pkts=%d\n",
		    tp->peermac, tp->tx_छोड़ो,
		    tp->pkt_cnt);

	अगर (ether_addr_equal(tp->peermac, priv->netdev->dev_addr)) अणु
		अगर (tp->tx_छोड़ो)
			priv->port_खोलो = false;
		अन्यथा
			priv->port_खोलो = true;
	पूर्ण अन्यथा अगर (is_multicast_ether_addr(tp->peermac)) अणु
		mwअगरiex_update_ralist_tx_छोड़ो(priv, tp->peermac, tp->tx_छोड़ो);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&priv->sta_list_spinlock);
		sta_ptr = mwअगरiex_get_sta_entry(priv, tp->peermac);
		अगर (sta_ptr && sta_ptr->tx_छोड़ो != tp->tx_छोड़ो) अणु
			sta_ptr->tx_छोड़ो = tp->tx_छोड़ो;
			mwअगरiex_update_ralist_tx_छोड़ो(priv, tp->peermac,
						       tp->tx_छोड़ो);
		पूर्ण
		spin_unlock_bh(&priv->sta_list_spinlock);
	पूर्ण
पूर्ण

अटल व्योम mwअगरiex_process_sta_tx_छोड़ो(काष्ठा mwअगरiex_निजी *priv,
					 काष्ठा mwअगरiex_ie_types_header *tlv)
अणु
	काष्ठा mwअगरiex_tx_छोड़ो_tlv *tp;
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	पूर्णांक status;

	tp = (व्योम *)tlv;
	mwअगरiex_dbg(priv->adapter, EVENT,
		    "sta tx_pause: %pM pause=%d, pkts=%d\n",
		    tp->peermac, tp->tx_छोड़ो,
		    tp->pkt_cnt);

	अगर (ether_addr_equal(tp->peermac, priv->cfg_bssid)) अणु
		अगर (tp->tx_छोड़ो)
			priv->port_खोलो = false;
		अन्यथा
			priv->port_खोलो = true;
	पूर्ण अन्यथा अणु
		अगर (!ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info))
			वापस;

		status = mwअगरiex_get_tdls_link_status(priv, tp->peermac);
		अगर (mwअगरiex_is_tdls_link_setup(status)) अणु
			spin_lock_bh(&priv->sta_list_spinlock);
			sta_ptr = mwअगरiex_get_sta_entry(priv, tp->peermac);
			अगर (sta_ptr && sta_ptr->tx_छोड़ो != tp->tx_छोड़ो) अणु
				sta_ptr->tx_छोड़ो = tp->tx_छोड़ो;
				mwअगरiex_update_ralist_tx_छोड़ो(priv,
							       tp->peermac,
							       tp->tx_छोड़ो);
			पूर्ण
			spin_unlock_bh(&priv->sta_list_spinlock);
		पूर्ण
	पूर्ण
पूर्ण

व्योम mwअगरiex_process_multi_chan_event(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा sk_buff *event_skb)
अणु
	काष्ठा mwअगरiex_ie_types_multi_chan_info *chan_info;
	काष्ठा mwअगरiex_ie_types_mc_group_info *grp_info;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_ie_types_header *tlv;
	u16 tlv_buf_left, tlv_type, tlv_len;
	पूर्णांक पूर्णांकf_num, bss_type, bss_num, i;
	काष्ठा mwअगरiex_निजी *पूर्णांकf_priv;

	tlv_buf_left = event_skb->len - माप(u32);
	chan_info = (व्योम *)event_skb->data + माप(u32);

	अगर (le16_to_cpu(chan_info->header.type) != TLV_TYPE_MULTI_CHAN_INFO ||
	    tlv_buf_left < माप(काष्ठा mwअगरiex_ie_types_multi_chan_info)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "unknown TLV in chan_info event\n");
		वापस;
	पूर्ण

	adapter->usb_mc_status = le16_to_cpu(chan_info->status);
	mwअगरiex_dbg(adapter, EVENT, "multi chan operation %s\n",
		    adapter->usb_mc_status ? "started" : "over");

	tlv_buf_left -= माप(काष्ठा mwअगरiex_ie_types_multi_chan_info);
	tlv = (काष्ठा mwअगरiex_ie_types_header *)chan_info->tlv_buffer;

	जबतक (tlv_buf_left >= (पूर्णांक)माप(काष्ठा mwअगरiex_ie_types_header)) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_len  = le16_to_cpu(tlv->len);
		अगर ((माप(काष्ठा mwअगरiex_ie_types_header) + tlv_len) >
		    tlv_buf_left) अणु
			mwअगरiex_dbg(adapter, ERROR, "wrong tlv: tlvLen=%d,\t"
				    "tlvBufLeft=%d\n", tlv_len, tlv_buf_left);
			अवरोध;
		पूर्ण
		अगर (tlv_type != TLV_TYPE_MC_GROUP_INFO) अणु
			mwअगरiex_dbg(adapter, ERROR, "wrong tlv type: 0x%x\n",
				    tlv_type);
			अवरोध;
		पूर्ण

		grp_info = (काष्ठा mwअगरiex_ie_types_mc_group_info *)tlv;
		पूर्णांकf_num = grp_info->पूर्णांकf_num;
		क्रम (i = 0; i < पूर्णांकf_num; i++) अणु
			bss_type = grp_info->bss_type_numlist[i] >> 4;
			bss_num = grp_info->bss_type_numlist[i] & BSS_NUM_MASK;
			पूर्णांकf_priv = mwअगरiex_get_priv_by_id(adapter, bss_num,
							   bss_type);
			अगर (!पूर्णांकf_priv) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "Invalid bss_type bss_num\t"
					    "in multi channel event\n");
				जारी;
			पूर्ण
			अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
				u8 ep;

				ep = grp_info->hid_num.usb_ep_num;
				अगर (ep == MWIFIEX_USB_EP_DATA ||
				    ep == MWIFIEX_USB_EP_DATA_CH2)
					पूर्णांकf_priv->usb_port = ep;
			पूर्ण
		पूर्ण

		tlv_buf_left -= माप(काष्ठा mwअगरiex_ie_types_header) +
				tlv_len;
		tlv = (व्योम *)((u8 *)tlv + tlv_len +
			       माप(काष्ठा mwअगरiex_ie_types_header));
	पूर्ण

	अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
		adapter->tx_lock_flag = true;
		adapter->usb_mc_setup = true;
		mwअगरiex_multi_chan_resync(adapter);
	पूर्ण
पूर्ण

व्योम mwअगरiex_process_tx_छोड़ो_event(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा sk_buff *event_skb)
अणु
	काष्ठा mwअगरiex_ie_types_header *tlv;
	u16 tlv_type, tlv_len;
	पूर्णांक tlv_buf_left;

	अगर (!priv->media_connected) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "tx_pause event while disconnected; bss_role=%d\n",
			    priv->bss_role);
		वापस;
	पूर्ण

	tlv_buf_left = event_skb->len - माप(u32);
	tlv = (व्योम *)event_skb->data + माप(u32);

	जबतक (tlv_buf_left >= (पूर्णांक)माप(काष्ठा mwअगरiex_ie_types_header)) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_len  = le16_to_cpu(tlv->len);
		अगर ((माप(काष्ठा mwअगरiex_ie_types_header) + tlv_len) >
		    tlv_buf_left) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "wrong tlv: tlvLen=%d, tlvBufLeft=%d\n",
				    tlv_len, tlv_buf_left);
			अवरोध;
		पूर्ण
		अगर (tlv_type == TLV_TYPE_TX_PAUSE) अणु
			अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA)
				mwअगरiex_process_sta_tx_छोड़ो(priv, tlv);
			अन्यथा
				mwअगरiex_process_uap_tx_छोड़ो(priv, tlv);
		पूर्ण

		tlv_buf_left -= माप(काष्ठा mwअगरiex_ie_types_header) +
				tlv_len;
		tlv = (व्योम *)((u8 *)tlv + tlv_len +
			       माप(काष्ठा mwअगरiex_ie_types_header));
	पूर्ण

पूर्ण

/*
* This function handles coex events generated by firmware
*/
व्योम mwअगरiex_bt_coex_wlan_param_update_event(काष्ठा mwअगरiex_निजी *priv,
					     काष्ठा sk_buff *event_skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_ie_types_header *tlv;
	काष्ठा mwअगरiex_ie_types_btcoex_aggr_win_size *winsizetlv;
	काष्ठा mwअगरiex_ie_types_btcoex_scan_समय *scantlv;
	s32 len = event_skb->len - माप(u32);
	u8 *cur_ptr = event_skb->data + माप(u32);
	u16 tlv_type, tlv_len;

	जबतक (len >= माप(काष्ठा mwअगरiex_ie_types_header)) अणु
		tlv = (काष्ठा mwअगरiex_ie_types_header *)cur_ptr;
		tlv_len = le16_to_cpu(tlv->len);
		tlv_type = le16_to_cpu(tlv->type);

		अगर ((tlv_len + माप(काष्ठा mwअगरiex_ie_types_header)) > len)
			अवरोध;
		चयन (tlv_type) अणु
		हाल TLV_BTCOEX_WL_AGGR_WINSIZE:
			winsizetlv =
			    (काष्ठा mwअगरiex_ie_types_btcoex_aggr_win_size *)tlv;
			adapter->coex_win_size = winsizetlv->coex_win_size;
			adapter->coex_tx_win_size =
				winsizetlv->tx_win_size;
			adapter->coex_rx_win_size =
				winsizetlv->rx_win_size;
			mwअगरiex_coex_ampdu_rxwinsize(adapter);
			mwअगरiex_update_ampdu_txwinsize(adapter);
			अवरोध;

		हाल TLV_BTCOEX_WL_SCANTIME:
			scantlv =
			    (काष्ठा mwअगरiex_ie_types_btcoex_scan_समय *)tlv;
			adapter->coex_scan = scantlv->coex_scan;
			adapter->coex_min_scan_समय = le16_to_cpu(scantlv->min_scan_समय);
			adapter->coex_max_scan_समय = le16_to_cpu(scantlv->max_scan_समय);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

		len -= tlv_len + माप(काष्ठा mwअगरiex_ie_types_header);
		cur_ptr += tlv_len +
			माप(काष्ठा mwअगरiex_ie_types_header);
	पूर्ण

	dev_dbg(adapter->dev, "coex_scan=%d min_scan=%d coex_win=%d, tx_win=%d rx_win=%d\n",
		adapter->coex_scan, adapter->coex_min_scan_समय,
		adapter->coex_win_size, adapter->coex_tx_win_size,
		adapter->coex_rx_win_size);
पूर्ण

अटल व्योम
mwअगरiex_fw_dump_info_event(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा sk_buff *event_skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_fw_dump_header *fw_dump_hdr =
				(व्योम *)adapter->event_body;

	अगर (adapter->अगरace_type != MWIFIEX_USB) अणु
		mwअगरiex_dbg(adapter, MSG,
			    "event is not on usb interface, ignore it\n");
		वापस;
	पूर्ण

	अगर (!adapter->devdump_data) अणु
		/* When receive the first event, allocate device dump
		 * buffer, dump driver info.
		 */
		adapter->devdump_data = vzalloc(MWIFIEX_FW_DUMP_SIZE);
		अगर (!adapter->devdump_data) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "vzalloc devdump data failure!\n");
			वापस;
		पूर्ण

		mwअगरiex_drv_info_dump(adapter);

		/* If no proceeded event arrive in 10s, upload device
		 * dump data, this will be useful अगर the end of
		 * transmission event get lost, in this cornel हाल,
		 * user would still get partial of the dump.
		 */
		mod_समयr(&adapter->devdump_समयr,
			  jअगरfies + msecs_to_jअगरfies(MWIFIEX_TIMER_10S));
	पूर्ण

	/* Overflow check */
	अगर (adapter->devdump_len + event_skb->len >= MWIFIEX_FW_DUMP_SIZE)
		जाओ upload_dump;

	स_हटाओ(adapter->devdump_data + adapter->devdump_len,
		adapter->event_skb->data, event_skb->len);
	adapter->devdump_len += event_skb->len;

	अगर (le16_to_cpu(fw_dump_hdr->type == FW_DUMP_INFO_ENDED)) अणु
		mwअगरiex_dbg(adapter, MSG,
			    "receive end of transmission flag event!\n");
		जाओ upload_dump;
	पूर्ण
	वापस;

upload_dump:
	del_समयr_sync(&adapter->devdump_समयr);
	mwअगरiex_upload_device_dump(adapter);
पूर्ण

/*
 * This function handles events generated by firmware.
 *
 * This is a generic function and handles all events.
 *
 * Event specअगरic routines are called by this function based
 * upon the generated event cause.
 *
 * For the following events, the function just क्रमwards them to upper
 * layers, optionally recording the change -
 *      - EVENT_LINK_SENSED
 *      - EVENT_MIC_ERR_UNICAST
 *      - EVENT_MIC_ERR_MULTICAST
 *      - EVENT_PORT_RELEASE
 *      - EVENT_RSSI_LOW
 *      - EVENT_SNR_LOW
 *      - EVENT_MAX_FAIL
 *      - EVENT_RSSI_HIGH
 *      - EVENT_SNR_HIGH
 *      - EVENT_DATA_RSSI_LOW
 *      - EVENT_DATA_SNR_LOW
 *      - EVENT_DATA_RSSI_HIGH
 *      - EVENT_DATA_SNR_HIGH
 *      - EVENT_LINK_QUALITY
 *      - EVENT_PRE_BEACON_LOST
 *      - EVENT_IBSS_COALESCED
 *      - EVENT_IBSS_STA_CONNECT
 *      - EVENT_IBSS_STA_DISCONNECT
 *      - EVENT_WEP_ICV_ERR
 *      - EVENT_BW_CHANGE
 *      - EVENT_HOSTWAKE_STAIE
  *
 * For the following events, no action is taken -
 *      - EVENT_MIB_CHANGED
 *      - EVENT_INIT_DONE
 *      - EVENT_DUMMY_HOST_WAKEUP_SIGNAL
 *
 * Rest of the supported events requires driver handling -
 *      - EVENT_DEAUTHENTICATED
 *      - EVENT_DISASSOCIATED
 *      - EVENT_LINK_LOST
 *      - EVENT_PS_SLEEP
 *      - EVENT_PS_AWAKE
 *      - EVENT_DEEP_SLEEP_AWAKE
 *      - EVENT_HS_ACT_REQ
 *      - EVENT_ADHOC_BCN_LOST
 *      - EVENT_BG_SCAN_REPORT
 *      - EVENT_WMM_STATUS_CHANGE
 *      - EVENT_ADDBA
 *      - EVENT_DELBA
 *      - EVENT_BA_STREAM_TIEMOUT
 *      - EVENT_AMSDU_AGGR_CTRL
 *      - EVENT_FW_DUMP_INFO
 */
पूर्णांक mwअगरiex_process_sta_event(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret = 0, i;
	u32 eventcause = adapter->event_cause;
	u16 ctrl, reason_code;
	u8 ibss_sta_addr[ETH_ALEN];
	काष्ठा mwअगरiex_sta_node *sta_ptr;

	चयन (eventcause) अणु
	हाल EVENT_DUMMY_HOST_WAKEUP_SIGNAL:
		mwअगरiex_dbg(adapter, ERROR,
			    "invalid EVENT: DUMMY_HOST_WAKEUP_SIGNAL, ignore it\n");
		अवरोध;
	हाल EVENT_LINK_SENSED:
		mwअगरiex_dbg(adapter, EVENT, "event: LINK_SENSED\n");
		अगर (!netअगर_carrier_ok(priv->netdev))
			netअगर_carrier_on(priv->netdev);
		mwअगरiex_wake_up_net_dev_queue(priv->netdev, adapter);
		अवरोध;

	हाल EVENT_DEAUTHENTICATED:
		mwअगरiex_dbg(adapter, EVENT, "event: Deauthenticated\n");
		अगर (priv->wps.session_enable) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "info: receive deauth event in wps session\n");
			अवरोध;
		पूर्ण
		adapter->dbg.num_event_deauth++;
		अगर (priv->media_connected) अणु
			reason_code =
				get_unaligned_le16(adapter->event_body);
			mwअगरiex_reset_connect_state(priv, reason_code, true);
		पूर्ण
		अवरोध;

	हाल EVENT_DISASSOCIATED:
		mwअगरiex_dbg(adapter, EVENT, "event: Disassociated\n");
		अगर (priv->wps.session_enable) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "info: receive disassoc event in wps session\n");
			अवरोध;
		पूर्ण
		adapter->dbg.num_event_disassoc++;
		अगर (priv->media_connected) अणु
			reason_code =
				get_unaligned_le16(adapter->event_body);
			mwअगरiex_reset_connect_state(priv, reason_code, true);
		पूर्ण
		अवरोध;

	हाल EVENT_LINK_LOST:
		mwअगरiex_dbg(adapter, EVENT, "event: Link lost\n");
		adapter->dbg.num_event_link_lost++;
		अगर (priv->media_connected) अणु
			reason_code =
				get_unaligned_le16(adapter->event_body);
			mwअगरiex_reset_connect_state(priv, reason_code, true);
		पूर्ण
		अवरोध;

	हाल EVENT_PS_SLEEP:
		mwअगरiex_dbg(adapter, EVENT, "info: EVENT: SLEEP\n");

		adapter->ps_state = PS_STATE_PRE_SLEEP;

		mwअगरiex_check_ps_cond(adapter);
		अवरोध;

	हाल EVENT_PS_AWAKE:
		mwअगरiex_dbg(adapter, EVENT, "info: EVENT: AWAKE\n");
		अगर (!adapter->pps_uapsd_mode &&
		    (priv->port_खोलो ||
		     (priv->bss_mode == NL80211_IFTYPE_ADHOC)) &&
		    priv->media_connected && adapter->sleep_period.period) अणु
			adapter->pps_uapsd_mode = true;
			mwअगरiex_dbg(adapter, EVENT,
				    "event: PPS/UAPSD mode activated\n");
		पूर्ण
		adapter->tx_lock_flag = false;
		अगर (adapter->pps_uapsd_mode && adapter->gen_null_pkt) अणु
			अगर (mwअगरiex_check_last_packet_indication(priv)) अणु
				अगर (adapter->data_sent ||
				    (adapter->अगर_ops.is_port_पढ़ोy &&
				     !adapter->अगर_ops.is_port_पढ़ोy(priv))) अणु
					adapter->ps_state = PS_STATE_AWAKE;
					adapter->pm_wakeup_card_req = false;
					adapter->pm_wakeup_fw_try = false;
					del_समयr(&adapter->wakeup_समयr);
					अवरोध;
				पूर्ण
				अगर (!mwअगरiex_send_null_packet
					(priv,
					 MWIFIEX_TxPD_POWER_MGMT_शून्य_PACKET |
					 MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET))
						adapter->ps_state =
							PS_STATE_SLEEP;
					वापस 0;
			पूर्ण
		पूर्ण
		adapter->ps_state = PS_STATE_AWAKE;
		adapter->pm_wakeup_card_req = false;
		adapter->pm_wakeup_fw_try = false;
		del_समयr(&adapter->wakeup_समयr);

		अवरोध;

	हाल EVENT_DEEP_SLEEP_AWAKE:
		adapter->अगर_ops.wakeup_complete(adapter);
		mwअगरiex_dbg(adapter, EVENT, "event: DS_AWAKE\n");
		अगर (adapter->is_deep_sleep)
			adapter->is_deep_sleep = false;
		अवरोध;

	हाल EVENT_HS_ACT_REQ:
		mwअगरiex_dbg(adapter, EVENT, "event: HS_ACT_REQ\n");
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_HS_CFG_ENH,
				       0, 0, शून्य, false);
		अवरोध;

	हाल EVENT_MIC_ERR_UNICAST:
		mwअगरiex_dbg(adapter, EVENT, "event: UNICAST MIC ERROR\n");
		cfg80211_michael_mic_failure(priv->netdev, priv->cfg_bssid,
					     NL80211_KEYTYPE_PAIRWISE,
					     -1, शून्य, GFP_KERNEL);
		अवरोध;

	हाल EVENT_MIC_ERR_MULTICAST:
		mwअगरiex_dbg(adapter, EVENT, "event: MULTICAST MIC ERROR\n");
		cfg80211_michael_mic_failure(priv->netdev, priv->cfg_bssid,
					     NL80211_KEYTYPE_GROUP,
					     -1, शून्य, GFP_KERNEL);
		अवरोध;
	हाल EVENT_MIB_CHANGED:
	हाल EVENT_INIT_DONE:
		अवरोध;

	हाल EVENT_ADHOC_BCN_LOST:
		mwअगरiex_dbg(adapter, EVENT, "event: ADHOC_BCN_LOST\n");
		priv->adhoc_is_link_sensed = false;
		mwअगरiex_clean_txrx(priv);
		mwअगरiex_stop_net_dev_queue(priv->netdev, adapter);
		अगर (netअगर_carrier_ok(priv->netdev))
			netअगर_carrier_off(priv->netdev);
		अवरोध;

	हाल EVENT_BG_SCAN_REPORT:
		mwअगरiex_dbg(adapter, EVENT, "event: BGS_REPORT\n");
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_BG_SCAN_QUERY,
				       HostCmd_ACT_GEN_GET, 0, शून्य, false);
		अवरोध;

	हाल EVENT_BG_SCAN_STOPPED:
		dev_dbg(adapter->dev, "event: BGS_STOPPED\n");
		cfg80211_sched_scan_stopped(priv->wdev.wiphy, 0);
		अगर (priv->sched_scanning)
			priv->sched_scanning = false;
		अवरोध;

	हाल EVENT_PORT_RELEASE:
		mwअगरiex_dbg(adapter, EVENT, "event: PORT RELEASE\n");
		priv->port_खोलो = true;
		अवरोध;

	हाल EVENT_EXT_SCAN_REPORT:
		mwअगरiex_dbg(adapter, EVENT, "event: EXT_SCAN Report\n");
		/* We पूर्णांकend to skip this event during suspend, but handle
		 * it in पूर्णांकerface disabled हाल
		 */
		अगर (adapter->ext_scan && (!priv->scan_पातing ||
					  !netअगर_running(priv->netdev)))
			ret = mwअगरiex_handle_event_ext_scan_report(priv,
						adapter->event_skb->data);

		अवरोध;

	हाल EVENT_WMM_STATUS_CHANGE:
		mwअगरiex_dbg(adapter, EVENT, "event: WMM status changed\n");
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_WMM_GET_STATUS,
				       0, 0, शून्य, false);
		अवरोध;

	हाल EVENT_RSSI_LOW:
		cfg80211_cqm_rssi_notअगरy(priv->netdev,
					 NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
					 0, GFP_KERNEL);
		mwअगरiex_send_cmd(priv, HostCmd_CMD_RSSI_INFO,
				 HostCmd_ACT_GEN_GET, 0, शून्य, false);
		priv->subsc_evt_rssi_state = RSSI_LOW_RECVD;
		mwअगरiex_dbg(adapter, EVENT, "event: Beacon RSSI_LOW\n");
		अवरोध;
	हाल EVENT_SNR_LOW:
		mwअगरiex_dbg(adapter, EVENT, "event: Beacon SNR_LOW\n");
		अवरोध;
	हाल EVENT_MAX_FAIL:
		mwअगरiex_dbg(adapter, EVENT, "event: MAX_FAIL\n");
		अवरोध;
	हाल EVENT_RSSI_HIGH:
		cfg80211_cqm_rssi_notअगरy(priv->netdev,
					 NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
					 0, GFP_KERNEL);
		mwअगरiex_send_cmd(priv, HostCmd_CMD_RSSI_INFO,
				 HostCmd_ACT_GEN_GET, 0, शून्य, false);
		priv->subsc_evt_rssi_state = RSSI_HIGH_RECVD;
		mwअगरiex_dbg(adapter, EVENT, "event: Beacon RSSI_HIGH\n");
		अवरोध;
	हाल EVENT_SNR_HIGH:
		mwअगरiex_dbg(adapter, EVENT, "event: Beacon SNR_HIGH\n");
		अवरोध;
	हाल EVENT_DATA_RSSI_LOW:
		mwअगरiex_dbg(adapter, EVENT, "event: Data RSSI_LOW\n");
		अवरोध;
	हाल EVENT_DATA_SNR_LOW:
		mwअगरiex_dbg(adapter, EVENT, "event: Data SNR_LOW\n");
		अवरोध;
	हाल EVENT_DATA_RSSI_HIGH:
		mwअगरiex_dbg(adapter, EVENT, "event: Data RSSI_HIGH\n");
		अवरोध;
	हाल EVENT_DATA_SNR_HIGH:
		mwअगरiex_dbg(adapter, EVENT, "event: Data SNR_HIGH\n");
		अवरोध;
	हाल EVENT_LINK_QUALITY:
		mwअगरiex_dbg(adapter, EVENT, "event: Link Quality\n");
		अवरोध;
	हाल EVENT_PRE_BEACON_LOST:
		mwअगरiex_dbg(adapter, EVENT, "event: Pre-Beacon Lost\n");
		अवरोध;
	हाल EVENT_IBSS_COALESCED:
		mwअगरiex_dbg(adapter, EVENT, "event: IBSS_COALESCED\n");
		ret = mwअगरiex_send_cmd(priv,
				HostCmd_CMD_802_11_IBSS_COALESCING_STATUS,
				HostCmd_ACT_GEN_GET, 0, शून्य, false);
		अवरोध;
	हाल EVENT_IBSS_STA_CONNECT:
		ether_addr_copy(ibss_sta_addr, adapter->event_body + 2);
		mwअगरiex_dbg(adapter, EVENT, "event: IBSS_STA_CONNECT %pM\n",
			    ibss_sta_addr);
		sta_ptr = mwअगरiex_add_sta_entry(priv, ibss_sta_addr);
		अगर (sta_ptr && adapter->adhoc_11n_enabled) अणु
			mwअगरiex_check_ibss_peer_capabilities(priv, sta_ptr,
							     adapter->event_skb);
			अगर (sta_ptr->is_11n_enabled)
				क्रम (i = 0; i < MAX_NUM_TID; i++)
					sta_ptr->ampdu_sta[i] =
					priv->aggr_prio_tbl[i].ampdu_user;
			अन्यथा
				क्रम (i = 0; i < MAX_NUM_TID; i++)
					sta_ptr->ampdu_sta[i] =
						BA_STREAM_NOT_ALLOWED;
			स_रखो(sta_ptr->rx_seq, 0xff, माप(sta_ptr->rx_seq));
		पूर्ण

		अवरोध;
	हाल EVENT_IBSS_STA_DISCONNECT:
		ether_addr_copy(ibss_sta_addr, adapter->event_body + 2);
		mwअगरiex_dbg(adapter, EVENT, "event: IBSS_STA_DISCONNECT %pM\n",
			    ibss_sta_addr);
		sta_ptr = mwअगरiex_get_sta_entry(priv, ibss_sta_addr);
		अगर (sta_ptr && sta_ptr->is_11n_enabled) अणु
			mwअगरiex_11n_del_rx_reorder_tbl_by_ta(priv,
							     ibss_sta_addr);
			mwअगरiex_del_tx_ba_stream_tbl_by_ra(priv, ibss_sta_addr);
		पूर्ण
		mwअगरiex_wmm_del_peer_ra_list(priv, ibss_sta_addr);
		mwअगरiex_del_sta_entry(priv, ibss_sta_addr);
		अवरोध;
	हाल EVENT_ADDBA:
		mwअगरiex_dbg(adapter, EVENT, "event: ADDBA Request\n");
		mwअगरiex_send_cmd(priv, HostCmd_CMD_11N_ADDBA_RSP,
				 HostCmd_ACT_GEN_SET, 0,
				 adapter->event_body, false);
		अवरोध;
	हाल EVENT_DELBA:
		mwअगरiex_dbg(adapter, EVENT, "event: DELBA Request\n");
		mwअगरiex_11n_delete_ba_stream(priv, adapter->event_body);
		अवरोध;
	हाल EVENT_BA_STREAM_TIEMOUT:
		mwअगरiex_dbg(adapter, EVENT, "event:  BA Stream timeout\n");
		mwअगरiex_11n_ba_stream_समयout(priv,
					      (काष्ठा host_cmd_ds_11n_baसमयout
					       *)
					      adapter->event_body);
		अवरोध;
	हाल EVENT_AMSDU_AGGR_CTRL:
		ctrl = get_unaligned_le16(adapter->event_body);
		mwअगरiex_dbg(adapter, EVENT,
			    "event: AMSDU_AGGR_CTRL %d\n", ctrl);

		adapter->tx_buf_size =
				min_t(u16, adapter->curr_tx_buf_size, ctrl);
		mwअगरiex_dbg(adapter, EVENT, "event: tx_buf_size %d\n",
			    adapter->tx_buf_size);
		अवरोध;

	हाल EVENT_WEP_ICV_ERR:
		mwअगरiex_dbg(adapter, EVENT, "event: WEP ICV error\n");
		अवरोध;

	हाल EVENT_BW_CHANGE:
		mwअगरiex_dbg(adapter, EVENT, "event: BW Change\n");
		अवरोध;

	हाल EVENT_HOSTWAKE_STAIE:
		mwअगरiex_dbg(adapter, EVENT,
			    "event: HOSTWAKE_STAIE %d\n", eventcause);
		अवरोध;

	हाल EVENT_REMAIN_ON_CHAN_EXPIRED:
		mwअगरiex_dbg(adapter, EVENT,
			    "event: Remain on channel expired\n");
		cfg80211_reमुख्य_on_channel_expired(&priv->wdev,
						   priv->roc_cfg.cookie,
						   &priv->roc_cfg.chan,
						   GFP_ATOMIC);

		स_रखो(&priv->roc_cfg, 0x00, माप(काष्ठा mwअगरiex_roc_cfg));

		अवरोध;

	हाल EVENT_CHANNEL_SWITCH_ANN:
		mwअगरiex_dbg(adapter, EVENT, "event: Channel Switch Announcement\n");
		priv->csa_expire_समय =
				jअगरfies + msecs_to_jअगरfies(DFS_CHAN_MOVE_TIME);
		priv->csa_chan = priv->curr_bss_params.bss_descriptor.channel;
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_DEAUTHENTICATE,
			HostCmd_ACT_GEN_SET, 0,
			priv->curr_bss_params.bss_descriptor.mac_address,
			false);
		अवरोध;

	हाल EVENT_TDLS_GENERIC_EVENT:
		ret = mwअगरiex_parse_tdls_event(priv, adapter->event_skb);
		अवरोध;

	हाल EVENT_TX_DATA_PAUSE:
		mwअगरiex_dbg(adapter, EVENT, "event: TX DATA PAUSE\n");
		mwअगरiex_process_tx_छोड़ो_event(priv, adapter->event_skb);
		अवरोध;

	हाल EVENT_MULTI_CHAN_INFO:
		mwअगरiex_dbg(adapter, EVENT, "event: multi-chan info\n");
		mwअगरiex_process_multi_chan_event(priv, adapter->event_skb);
		अवरोध;

	हाल EVENT_TX_STATUS_REPORT:
		mwअगरiex_dbg(adapter, EVENT, "event: TX_STATUS Report\n");
		mwअगरiex_parse_tx_status_event(priv, adapter->event_body);
		अवरोध;

	हाल EVENT_CHANNEL_REPORT_RDY:
		mwअगरiex_dbg(adapter, EVENT, "event: Channel Report\n");
		ret = mwअगरiex_11h_handle_chanrpt_पढ़ोy(priv,
						       adapter->event_skb);
		अवरोध;
	हाल EVENT_RADAR_DETECTED:
		mwअगरiex_dbg(adapter, EVENT, "event: Radar detected\n");
		ret = mwअगरiex_11h_handle_radar_detected(priv,
							adapter->event_skb);
		अवरोध;
	हाल EVENT_BT_COEX_WLAN_PARA_CHANGE:
		dev_dbg(adapter->dev, "EVENT: BT coex wlan param update\n");
		mwअगरiex_bt_coex_wlan_param_update_event(priv,
							adapter->event_skb);
		अवरोध;
	हाल EVENT_RXBA_SYNC:
		dev_dbg(adapter->dev, "EVENT: RXBA_SYNC\n");
		mwअगरiex_11n_rxba_sync_event(priv, adapter->event_body,
					    adapter->event_skb->len -
					    माप(eventcause));
		अवरोध;
	हाल EVENT_FW_DUMP_INFO:
		mwअगरiex_dbg(adapter, EVENT, "event: firmware debug info\n");
		mwअगरiex_fw_dump_info_event(priv, adapter->event_skb);
		अवरोध;
	/* Debugging event; not used, but let's not prपूर्णांक an ERROR क्रम it. */
	हाल EVENT_UNKNOWN_DEBUG:
		mwअगरiex_dbg(adapter, EVENT, "event: debug\n");
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR, "event: unknown event id: %#x\n",
			    eventcause);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
