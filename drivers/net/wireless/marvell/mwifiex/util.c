<शैली गुरु>
/*
 * NXP Wireless LAN device driver: utility functions
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

अटल काष्ठा mwअगरiex_debug_data items[] = अणु
	अणु"debug_mask", item_size(debug_mask),
	 item_addr(debug_mask), 1पूर्ण,
	अणु"int_counter", item_size(पूर्णांक_counter),
	 item_addr(पूर्णांक_counter), 1पूर्ण,
	अणु"wmm_ac_vo", item_size(packets_out[WMM_AC_VO]),
	 item_addr(packets_out[WMM_AC_VO]), 1पूर्ण,
	अणु"wmm_ac_vi", item_size(packets_out[WMM_AC_VI]),
	 item_addr(packets_out[WMM_AC_VI]), 1पूर्ण,
	अणु"wmm_ac_be", item_size(packets_out[WMM_AC_BE]),
	 item_addr(packets_out[WMM_AC_BE]), 1पूर्ण,
	अणु"wmm_ac_bk", item_size(packets_out[WMM_AC_BK]),
	 item_addr(packets_out[WMM_AC_BK]), 1पूर्ण,
	अणु"tx_buf_size", item_size(tx_buf_size),
	 item_addr(tx_buf_size), 1पूर्ण,
	अणु"curr_tx_buf_size", item_size(curr_tx_buf_size),
	 item_addr(curr_tx_buf_size), 1पूर्ण,
	अणु"ps_mode", item_size(ps_mode),
	 item_addr(ps_mode), 1पूर्ण,
	अणु"ps_state", item_size(ps_state),
	 item_addr(ps_state), 1पूर्ण,
	अणु"is_deep_sleep", item_size(is_deep_sleep),
	 item_addr(is_deep_sleep), 1पूर्ण,
	अणु"wakeup_dev_req", item_size(pm_wakeup_card_req),
	 item_addr(pm_wakeup_card_req), 1पूर्ण,
	अणु"wakeup_tries", item_size(pm_wakeup_fw_try),
	 item_addr(pm_wakeup_fw_try), 1पूर्ण,
	अणु"hs_configured", item_size(is_hs_configured),
	 item_addr(is_hs_configured), 1पूर्ण,
	अणु"hs_activated", item_size(hs_activated),
	 item_addr(hs_activated), 1पूर्ण,
	अणु"num_tx_timeout", item_size(num_tx_समयout),
	 item_addr(num_tx_समयout), 1पूर्ण,
	अणु"is_cmd_timedout", item_size(is_cmd_समयकरोut),
	 item_addr(is_cmd_समयकरोut), 1पूर्ण,
	अणु"timeout_cmd_id", item_size(समयout_cmd_id),
	 item_addr(समयout_cmd_id), 1पूर्ण,
	अणु"timeout_cmd_act", item_size(समयout_cmd_act),
	 item_addr(समयout_cmd_act), 1पूर्ण,
	अणु"last_cmd_id", item_size(last_cmd_id),
	 item_addr(last_cmd_id), DBG_CMD_NUMपूर्ण,
	अणु"last_cmd_act", item_size(last_cmd_act),
	 item_addr(last_cmd_act), DBG_CMD_NUMपूर्ण,
	अणु"last_cmd_index", item_size(last_cmd_index),
	 item_addr(last_cmd_index), 1पूर्ण,
	अणु"last_cmd_resp_id", item_size(last_cmd_resp_id),
	 item_addr(last_cmd_resp_id), DBG_CMD_NUMपूर्ण,
	अणु"last_cmd_resp_index", item_size(last_cmd_resp_index),
	 item_addr(last_cmd_resp_index), 1पूर्ण,
	अणु"last_event", item_size(last_event),
	 item_addr(last_event), DBG_CMD_NUMपूर्ण,
	अणु"last_event_index", item_size(last_event_index),
	 item_addr(last_event_index), 1पूर्ण,
	अणु"last_mp_wr_bitmap", item_size(last_mp_wr_biपंचांगap),
	 item_addr(last_mp_wr_biपंचांगap), MWIFIEX_DBG_SDIO_MP_NUMपूर्ण,
	अणु"last_mp_wr_ports", item_size(last_mp_wr_ports),
	 item_addr(last_mp_wr_ports), MWIFIEX_DBG_SDIO_MP_NUMपूर्ण,
	अणु"last_mp_wr_len", item_size(last_mp_wr_len),
	 item_addr(last_mp_wr_len), MWIFIEX_DBG_SDIO_MP_NUMपूर्ण,
	अणु"last_mp_curr_wr_port", item_size(last_mp_curr_wr_port),
	 item_addr(last_mp_curr_wr_port), MWIFIEX_DBG_SDIO_MP_NUMपूर्ण,
	अणु"last_sdio_mp_index", item_size(last_sdio_mp_index),
	 item_addr(last_sdio_mp_index), 1पूर्ण,
	अणु"num_cmd_h2c_fail", item_size(num_cmd_host_to_card_failure),
	 item_addr(num_cmd_host_to_card_failure), 1पूर्ण,
	अणु"num_cmd_sleep_cfm_fail",
	 item_size(num_cmd_sleep_cfm_host_to_card_failure),
	 item_addr(num_cmd_sleep_cfm_host_to_card_failure), 1पूर्ण,
	अणु"num_tx_h2c_fail", item_size(num_tx_host_to_card_failure),
	 item_addr(num_tx_host_to_card_failure), 1पूर्ण,
	अणु"num_evt_deauth", item_size(num_event_deauth),
	 item_addr(num_event_deauth), 1पूर्ण,
	अणु"num_evt_disassoc", item_size(num_event_disassoc),
	 item_addr(num_event_disassoc), 1पूर्ण,
	अणु"num_evt_link_lost", item_size(num_event_link_lost),
	 item_addr(num_event_link_lost), 1पूर्ण,
	अणु"num_cmd_deauth", item_size(num_cmd_deauth),
	 item_addr(num_cmd_deauth), 1पूर्ण,
	अणु"num_cmd_assoc_ok", item_size(num_cmd_assoc_success),
	 item_addr(num_cmd_assoc_success), 1पूर्ण,
	अणु"num_cmd_assoc_fail", item_size(num_cmd_assoc_failure),
	 item_addr(num_cmd_assoc_failure), 1पूर्ण,
	अणु"cmd_sent", item_size(cmd_sent),
	 item_addr(cmd_sent), 1पूर्ण,
	अणु"data_sent", item_size(data_sent),
	 item_addr(data_sent), 1पूर्ण,
	अणु"cmd_resp_received", item_size(cmd_resp_received),
	 item_addr(cmd_resp_received), 1पूर्ण,
	अणु"event_received", item_size(event_received),
	 item_addr(event_received), 1पूर्ण,

	/* variables defined in काष्ठा mwअगरiex_adapter */
	अणु"cmd_pending", adapter_item_size(cmd_pending),
	 adapter_item_addr(cmd_pending), 1पूर्ण,
	अणु"tx_pending", adapter_item_size(tx_pending),
	 adapter_item_addr(tx_pending), 1पूर्ण,
	अणु"rx_pending", adapter_item_size(rx_pending),
	 adapter_item_addr(rx_pending), 1पूर्ण,
पूर्ण;

अटल पूर्णांक num_of_items = ARRAY_SIZE(items);

/*
 * Firmware initialization complete callback handler.
 *
 * This function wakes up the function रुकोing on the init
 * रुको queue क्रम the firmware initialization to complete.
 */
पूर्णांक mwअगरiex_init_fw_complete(काष्ठा mwअगरiex_adapter *adapter)
अणु

	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_READY)
		अगर (adapter->अगर_ops.init_fw_port)
			adapter->अगर_ops.init_fw_port(adapter);

	adapter->init_रुको_q_woken = true;
	wake_up_पूर्णांकerruptible(&adapter->init_रुको_q);
	वापस 0;
पूर्ण

/*
 * This function sends init/shutकरोwn command
 * to firmware.
 */
पूर्णांक mwअगरiex_init_shutकरोwn_fw(काष्ठा mwअगरiex_निजी *priv,
			     u32 func_init_shutकरोwn)
अणु
	u16 cmd;

	अगर (func_init_shutकरोwn == MWIFIEX_FUNC_INIT) अणु
		cmd = HostCmd_CMD_FUNC_INIT;
	पूर्ण अन्यथा अगर (func_init_shutकरोwn == MWIFIEX_FUNC_SHUTDOWN) अणु
		cmd = HostCmd_CMD_FUNC_SHUTDOWN;
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "unsupported parameter\n");
		वापस -1;
	पूर्ण

	वापस mwअगरiex_send_cmd(priv, cmd, HostCmd_ACT_GEN_SET, 0, शून्य, true);
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_init_shutकरोwn_fw);

/*
 * IOCTL request handler to set/get debug inक्रमmation.
 *
 * This function collates/sets the inक्रमmation from/to dअगरferent driver
 * काष्ठाures.
 */
पूर्णांक mwअगरiex_get_debug_info(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा mwअगरiex_debug_info *info)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	अगर (info) अणु
		info->debug_mask = adapter->debug_mask;
		स_नकल(info->packets_out,
		       priv->wmm.packets_out,
		       माप(priv->wmm.packets_out));
		info->curr_tx_buf_size = (u32) adapter->curr_tx_buf_size;
		info->tx_buf_size = (u32) adapter->tx_buf_size;
		info->rx_tbl_num = mwअगरiex_get_rx_reorder_tbl(priv,
							      info->rx_tbl);
		info->tx_tbl_num = mwअगरiex_get_tx_ba_stream_tbl(priv,
								info->tx_tbl);
		info->tdls_peer_num = mwअगरiex_get_tdls_list(priv,
							    info->tdls_list);
		info->ps_mode = adapter->ps_mode;
		info->ps_state = adapter->ps_state;
		info->is_deep_sleep = adapter->is_deep_sleep;
		info->pm_wakeup_card_req = adapter->pm_wakeup_card_req;
		info->pm_wakeup_fw_try = adapter->pm_wakeup_fw_try;
		info->is_hs_configured = test_bit(MWIFIEX_IS_HS_CONFIGURED,
						  &adapter->work_flags);
		info->hs_activated = adapter->hs_activated;
		info->is_cmd_समयकरोut = test_bit(MWIFIEX_IS_CMD_TIMEDOUT,
						 &adapter->work_flags);
		info->num_cmd_host_to_card_failure
				= adapter->dbg.num_cmd_host_to_card_failure;
		info->num_cmd_sleep_cfm_host_to_card_failure
			= adapter->dbg.num_cmd_sleep_cfm_host_to_card_failure;
		info->num_tx_host_to_card_failure
				= adapter->dbg.num_tx_host_to_card_failure;
		info->num_event_deauth = adapter->dbg.num_event_deauth;
		info->num_event_disassoc = adapter->dbg.num_event_disassoc;
		info->num_event_link_lost = adapter->dbg.num_event_link_lost;
		info->num_cmd_deauth = adapter->dbg.num_cmd_deauth;
		info->num_cmd_assoc_success =
					adapter->dbg.num_cmd_assoc_success;
		info->num_cmd_assoc_failure =
					adapter->dbg.num_cmd_assoc_failure;
		info->num_tx_समयout = adapter->dbg.num_tx_समयout;
		info->समयout_cmd_id = adapter->dbg.समयout_cmd_id;
		info->समयout_cmd_act = adapter->dbg.समयout_cmd_act;
		स_नकल(info->last_cmd_id, adapter->dbg.last_cmd_id,
		       माप(adapter->dbg.last_cmd_id));
		स_नकल(info->last_cmd_act, adapter->dbg.last_cmd_act,
		       माप(adapter->dbg.last_cmd_act));
		info->last_cmd_index = adapter->dbg.last_cmd_index;
		स_नकल(info->last_cmd_resp_id, adapter->dbg.last_cmd_resp_id,
		       माप(adapter->dbg.last_cmd_resp_id));
		info->last_cmd_resp_index = adapter->dbg.last_cmd_resp_index;
		स_नकल(info->last_event, adapter->dbg.last_event,
		       माप(adapter->dbg.last_event));
		info->last_event_index = adapter->dbg.last_event_index;
		स_नकल(info->last_mp_wr_biपंचांगap, adapter->dbg.last_mp_wr_biपंचांगap,
		       माप(adapter->dbg.last_mp_wr_biपंचांगap));
		स_नकल(info->last_mp_wr_ports, adapter->dbg.last_mp_wr_ports,
		       माप(adapter->dbg.last_mp_wr_ports));
		स_नकल(info->last_mp_curr_wr_port,
		       adapter->dbg.last_mp_curr_wr_port,
		       माप(adapter->dbg.last_mp_curr_wr_port));
		स_नकल(info->last_mp_wr_len, adapter->dbg.last_mp_wr_len,
		       माप(adapter->dbg.last_mp_wr_len));
		info->last_sdio_mp_index = adapter->dbg.last_sdio_mp_index;
		info->data_sent = adapter->data_sent;
		info->cmd_sent = adapter->cmd_sent;
		info->cmd_resp_received = adapter->cmd_resp_received;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mwअगरiex_debug_info_to_buffer(काष्ठा mwअगरiex_निजी *priv, अक्षर *buf,
				 काष्ठा mwअगरiex_debug_info *info)
अणु
	अक्षर *p = buf;
	काष्ठा mwअगरiex_debug_data *d = &items[0];
	माप_प्रकार size, addr;
	दीर्घ val;
	पूर्णांक i, j;

	अगर (!info)
		वापस 0;

	क्रम (i = 0; i < num_of_items; i++) अणु
		p += प्र_लिखो(p, "%s=", d[i].name);

		size = d[i].size / d[i].num;

		अगर (i < (num_of_items - 3))
			addr = d[i].addr + (माप_प्रकार)info;
		अन्यथा /* The last 3 items are काष्ठा mwअगरiex_adapter variables */
			addr = d[i].addr + (माप_प्रकार)priv->adapter;

		क्रम (j = 0; j < d[i].num; j++) अणु
			चयन (size) अणु
			हाल 1:
				val = *((u8 *)addr);
				अवरोध;
			हाल 2:
				val = get_unaligned((u16 *)addr);
				अवरोध;
			हाल 4:
				val = get_unaligned((u32 *)addr);
				अवरोध;
			हाल 8:
				val = get_unaligned((दीर्घ दीर्घ *)addr);
				अवरोध;
			शेष:
				val = -1;
				अवरोध;
			पूर्ण

			p += प्र_लिखो(p, "%#lx ", val);
			addr += size;
		पूर्ण

		p += प्र_लिखो(p, "\n");
	पूर्ण

	अगर (info->tx_tbl_num) अणु
		p += प्र_लिखो(p, "Tx BA stream table:\n");
		क्रम (i = 0; i < info->tx_tbl_num; i++)
			p += प्र_लिखो(p, "tid = %d, ra = %pM\n",
				     info->tx_tbl[i].tid, info->tx_tbl[i].ra);
	पूर्ण

	अगर (info->rx_tbl_num) अणु
		p += प्र_लिखो(p, "Rx reorder table:\n");
		क्रम (i = 0; i < info->rx_tbl_num; i++) अणु
			p += प्र_लिखो(p, "tid = %d, ta = %pM, ",
				     info->rx_tbl[i].tid,
				     info->rx_tbl[i].ta);
			p += प्र_लिखो(p, "start_win = %d, ",
				     info->rx_tbl[i].start_win);
			p += प्र_लिखो(p, "win_size = %d, buffer: ",
				     info->rx_tbl[i].win_size);

			क्रम (j = 0; j < info->rx_tbl[i].win_size; j++)
				p += प्र_लिखो(p, "%c ",
					     info->rx_tbl[i].buffer[j] ?
					     '1' : '0');

			p += प्र_लिखो(p, "\n");
		पूर्ण
	पूर्ण

	अगर (info->tdls_peer_num) अणु
		p += प्र_लिखो(p, "TDLS peer table:\n");
		क्रम (i = 0; i < info->tdls_peer_num; i++) अणु
			p += प्र_लिखो(p, "peer = %pM",
				     info->tdls_list[i].peer_addr);
			p += प्र_लिखो(p, "\n");
		पूर्ण
	पूर्ण

	वापस p - buf;
पूर्ण

अटल पूर्णांक
mwअगरiex_parse_mgmt_packet(काष्ठा mwअगरiex_निजी *priv, u8 *payload, u16 len,
			  काष्ठा rxpd *rx_pd)
अणु
	u16 stype;
	u8 category, action_code, *addr2;
	काष्ठा ieee80211_hdr *ieee_hdr = (व्योम *)payload;

	stype = (le16_to_cpu(ieee_hdr->frame_control) & IEEE80211_FCTL_STYPE);

	चयन (stype) अणु
	हाल IEEE80211_STYPE_ACTION:
		category = *(payload + माप(काष्ठा ieee80211_hdr));
		चयन (category) अणु
		हाल WLAN_CATEGORY_PUBLIC:
			action_code = *(payload + माप(काष्ठा ieee80211_hdr)
					+ 1);
			अगर (action_code == WLAN_PUB_ACTION_TDLS_DISCOVER_RES) अणु
				addr2 = ieee_hdr->addr2;
				mwअगरiex_dbg(priv->adapter, INFO,
					    "TDLS discovery response %pM nf=%d, snr=%d\n",
					    addr2, rx_pd->nf, rx_pd->snr);
				mwअगरiex_स्वतः_tdls_update_peer_संकेत(priv,
								     addr2,
								     rx_pd->snr,
								     rx_pd->nf);
			पूर्ण
			अवरोध;
		हाल WLAN_CATEGORY_BACK:
			/*we करोnt indicate BACK action frames to cfg80211*/
			mwअगरiex_dbg(priv->adapter, INFO,
				    "drop BACK action frames");
			वापस -1;
		शेष:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "unknown public action frame category %d\n",
				    category);
		पूर्ण
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, INFO,
		    "unknown mgmt frame subtype %#x\n", stype);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण
/*
 * This function processes the received management packet and send it
 * to the kernel.
 */
पूर्णांक
mwअगरiex_process_mgmt_packet(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा rxpd *rx_pd;
	u16 pkt_len;
	काष्ठा ieee80211_hdr *ieee_hdr;

	अगर (!skb)
		वापस -1;

	अगर (!priv->mgmt_frame_mask ||
	    priv->wdev.अगरtype == NL80211_IFTYPE_UNSPECIFIED) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "do not receive mgmt frames on uninitialized intf");
		वापस -1;
	पूर्ण

	rx_pd = (काष्ठा rxpd *)skb->data;

	skb_pull(skb, le16_to_cpu(rx_pd->rx_pkt_offset));
	skb_pull(skb, माप(pkt_len));

	pkt_len = le16_to_cpu(rx_pd->rx_pkt_length);

	ieee_hdr = (व्योम *)skb->data;
	अगर (ieee80211_is_mgmt(ieee_hdr->frame_control)) अणु
		अगर (mwअगरiex_parse_mgmt_packet(priv, (u8 *)ieee_hdr,
					      pkt_len, rx_pd))
			वापस -1;
	पूर्ण
	/* Remove address4 */
	स_हटाओ(skb->data + माप(काष्ठा ieee80211_hdr_3addr),
		skb->data + माप(काष्ठा ieee80211_hdr),
		pkt_len - माप(काष्ठा ieee80211_hdr));

	pkt_len -= ETH_ALEN + माप(pkt_len);
	rx_pd->rx_pkt_length = cpu_to_le16(pkt_len);

	cfg80211_rx_mgmt(&priv->wdev, priv->roc_cfg.chan.center_freq,
			 CAL_RSSI(rx_pd->snr, rx_pd->nf), skb->data, pkt_len,
			 0);

	वापस 0;
पूर्ण

/*
 * This function processes the received packet beक्रमe sending it to the
 * kernel.
 *
 * It extracts the SKB from the received buffer and sends it to kernel.
 * In हाल the received buffer करोes not contain the data in SKB क्रमmat,
 * the function creates a blank SKB, fills it with the data from the
 * received buffer and then sends this new SKB to the kernel.
 */
पूर्णांक mwअगरiex_recv_packet(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_sta_node *src_node;
	काष्ठा ethhdr *p_ethhdr;

	अगर (!skb)
		वापस -1;

	priv->stats.rx_bytes += skb->len;
	priv->stats.rx_packets++;

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
		p_ethhdr = (व्योम *)skb->data;
		src_node = mwअगरiex_get_sta_entry(priv, p_ethhdr->h_source);
		अगर (src_node) अणु
			src_node->stats.last_rx = jअगरfies;
			src_node->stats.rx_bytes += skb->len;
			src_node->stats.rx_packets++;
		पूर्ण
	पूर्ण

	skb->dev = priv->netdev;
	skb->protocol = eth_type_trans(skb, priv->netdev);
	skb->ip_summed = CHECKSUM_NONE;

	/* This is required only in हाल of 11n and USB/PCIE as we alloc
	 * a buffer of 4K only अगर its 11N (to be able to receive 4K
	 * AMSDU packets). In हाल of SD we allocate buffers based
	 * on the size of packet and hence this is not needed.
	 *
	 * Modअगरying the truesize here as our allocation क्रम each
	 * skb is 4K but we only receive 2K packets and this cause
	 * the kernel to start dropping packets in हाल where
	 * application has allocated buffer based on 2K size i.e.
	 * अगर there a 64K packet received (in IP fragments and
	 * application allocates 64K to receive this packet but
	 * this packet would almost द्विगुन up because we allocate
	 * each 1.5K fragment in 4K and pass it up. As soon as the
	 * 64K limit hits kernel will start to drop rest of the
	 * fragments. Currently we fail the Filesndl-ht.scr script
	 * क्रम UDP, hence this fix
	 */
	अगर ((priv->adapter->अगरace_type == MWIFIEX_USB ||
	     priv->adapter->अगरace_type == MWIFIEX_PCIE) &&
	    (skb->truesize > MWIFIEX_RX_DATA_BUF_SIZE))
		skb->truesize += (skb->len - MWIFIEX_RX_DATA_BUF_SIZE);

	netअगर_rx_any_context(skb);
	वापस 0;
पूर्ण

/*
 * IOCTL completion callback handler.
 *
 * This function is called when a pending IOCTL is completed.
 *
 * If work queue support is enabled, the function wakes up the
 * corresponding रुकोing function. Otherwise, it processes the
 * IOCTL response and मुक्तs the response buffer.
 */
पूर्णांक mwअगरiex_complete_cmd(काष्ठा mwअगरiex_adapter *adapter,
			 काष्ठा cmd_ctrl_node *cmd_node)
अणु
	WARN_ON(!cmd_node->रुको_q_enabled);
	mwअगरiex_dbg(adapter, CMD, "cmd completed: status=%d\n",
		    adapter->cmd_रुको_q.status);

	*cmd_node->condition = true;
	wake_up_पूर्णांकerruptible(&adapter->cmd_रुको_q.रुको);

	वापस 0;
पूर्ण

/* This function will वापस the poपूर्णांकer to station entry in station list
 * table which matches specअगरied mac address.
 * This function should be called after acquiring RA list spinlock.
 * शून्य is वापसed अगर station entry is not found in associated STA list.
 */
काष्ठा mwअगरiex_sta_node *
mwअगरiex_get_sta_entry(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac)
अणु
	काष्ठा mwअगरiex_sta_node *node;

	अगर (!mac)
		वापस शून्य;

	list_क्रम_each_entry(node, &priv->sta_list, list) अणु
		अगर (!स_भेद(node->mac_addr, mac, ETH_ALEN))
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mwअगरiex_sta_node *
mwअगरiex_get_tdls_sta_entry(काष्ठा mwअगरiex_निजी *priv, u8 status)
अणु
	काष्ठा mwअगरiex_sta_node *node;

	list_क्रम_each_entry(node, &priv->sta_list, list) अणु
		अगर (node->tdls_status == status)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

/* If tdls channel चयनing is on-going, tx data traffic should be
 * blocked until the चयनing stage completed.
 */
u8 mwअगरiex_is_tdls_chan_चयनing(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;

	अगर (!priv || !ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info))
		वापस false;

	sta_ptr = mwअगरiex_get_tdls_sta_entry(priv, TDLS_CHAN_SWITCHING);
	अगर (sta_ptr)
		वापस true;

	वापस false;
पूर्ण

u8 mwअगरiex_is_tdls_off_chan(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;

	अगर (!priv || !ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info))
		वापस false;

	sta_ptr = mwअगरiex_get_tdls_sta_entry(priv, TDLS_IN_OFF_CHAN);
	अगर (sta_ptr)
		वापस true;

	वापस false;
पूर्ण

/* If tdls channel चयनing is on-going or tdls operate on off-channel,
 * cmd path should be blocked until tdls चयनed to base-channel.
 */
u8 mwअगरiex_is_send_cmd_allowed(काष्ठा mwअगरiex_निजी *priv)
अणु
	अगर (!priv || !ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info))
		वापस true;

	अगर (mwअगरiex_is_tdls_chan_चयनing(priv) ||
	    mwअगरiex_is_tdls_off_chan(priv))
		वापस false;

	वापस true;
पूर्ण

/* This function will add a sta_node entry to associated station list
 * table with the given mac address.
 * If entry exist alपढ़ोy, existing entry is वापसed.
 * If received mac address is शून्य, शून्य is वापसed.
 */
काष्ठा mwअगरiex_sta_node *
mwअगरiex_add_sta_entry(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac)
अणु
	काष्ठा mwअगरiex_sta_node *node;

	अगर (!mac)
		वापस शून्य;

	spin_lock_bh(&priv->sta_list_spinlock);
	node = mwअगरiex_get_sta_entry(priv, mac);
	अगर (node)
		जाओ करोne;

	node = kzalloc(माप(*node), GFP_ATOMIC);
	अगर (!node)
		जाओ करोne;

	स_नकल(node->mac_addr, mac, ETH_ALEN);
	list_add_tail(&node->list, &priv->sta_list);

करोne:
	spin_unlock_bh(&priv->sta_list_spinlock);
	वापस node;
पूर्ण

/* This function will search क्रम HT IE in association request IEs
 * and set station HT parameters accordingly.
 */
व्योम
mwअगरiex_set_sta_ht_cap(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *ies,
		       पूर्णांक ies_len, काष्ठा mwअगरiex_sta_node *node)
अणु
	काष्ठा ieee_types_header *ht_cap_ie;
	स्थिर काष्ठा ieee80211_ht_cap *ht_cap;

	अगर (!ies)
		वापस;

	ht_cap_ie = (व्योम *)cfg80211_find_ie(WLAN_EID_HT_CAPABILITY, ies,
					     ies_len);
	अगर (ht_cap_ie) अणु
		ht_cap = (व्योम *)(ht_cap_ie + 1);
		node->is_11n_enabled = 1;
		node->max_amsdu = le16_to_cpu(ht_cap->cap_info) &
				  IEEE80211_HT_CAP_MAX_AMSDU ?
				  MWIFIEX_TX_DATA_BUF_SIZE_8K :
				  MWIFIEX_TX_DATA_BUF_SIZE_4K;
	पूर्ण अन्यथा अणु
		node->is_11n_enabled = 0;
	पूर्ण

	वापस;
पूर्ण

/* This function will delete a station entry from station list */
व्योम mwअगरiex_del_sta_entry(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac)
अणु
	काष्ठा mwअगरiex_sta_node *node;

	spin_lock_bh(&priv->sta_list_spinlock);

	node = mwअगरiex_get_sta_entry(priv, mac);
	अगर (node) अणु
		list_del(&node->list);
		kमुक्त(node);
	पूर्ण

	spin_unlock_bh(&priv->sta_list_spinlock);
	वापस;
पूर्ण

/* This function will delete all stations from associated station list. */
व्योम mwअगरiex_del_all_sta_list(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_sta_node *node, *पंचांगp;

	spin_lock_bh(&priv->sta_list_spinlock);

	list_क्रम_each_entry_safe(node, पंचांगp, &priv->sta_list, list) अणु
		list_del(&node->list);
		kमुक्त(node);
	पूर्ण

	INIT_LIST_HEAD(&priv->sta_list);
	spin_unlock_bh(&priv->sta_list_spinlock);
	वापस;
पूर्ण

/* This function adds histogram data to histogram array*/
व्योम mwअगरiex_hist_data_add(काष्ठा mwअगरiex_निजी *priv,
			   u8 rx_rate, s8 snr, s8 nflr)
अणु
	काष्ठा mwअगरiex_histogram_data *phist_data = priv->hist_data;

	अगर (atomic_पढ़ो(&phist_data->num_samples) > MWIFIEX_HIST_MAX_SAMPLES)
		mwअगरiex_hist_data_reset(priv);
	mwअगरiex_hist_data_set(priv, rx_rate, snr, nflr);
पूर्ण

/* function to add histogram record */
व्योम mwअगरiex_hist_data_set(काष्ठा mwअगरiex_निजी *priv, u8 rx_rate, s8 snr,
			   s8 nflr)
अणु
	काष्ठा mwअगरiex_histogram_data *phist_data = priv->hist_data;
	s8 nf   = -nflr;
	s8 rssi = snr - nflr;

	atomic_inc(&phist_data->num_samples);
	atomic_inc(&phist_data->rx_rate[rx_rate]);
	atomic_inc(&phist_data->snr[snr + 128]);
	atomic_inc(&phist_data->noise_flr[nf + 128]);
	atomic_inc(&phist_data->sig_str[rssi + 128]);
पूर्ण

/* function to reset histogram data during init/reset */
व्योम mwअगरiex_hist_data_reset(काष्ठा mwअगरiex_निजी *priv)
अणु
	पूर्णांक ix;
	काष्ठा mwअगरiex_histogram_data *phist_data = priv->hist_data;

	atomic_set(&phist_data->num_samples, 0);
	क्रम (ix = 0; ix < MWIFIEX_MAX_AC_RX_RATES; ix++)
		atomic_set(&phist_data->rx_rate[ix], 0);
	क्रम (ix = 0; ix < MWIFIEX_MAX_SNR; ix++)
		atomic_set(&phist_data->snr[ix], 0);
	क्रम (ix = 0; ix < MWIFIEX_MAX_NOISE_FLR; ix++)
		atomic_set(&phist_data->noise_flr[ix], 0);
	क्रम (ix = 0; ix < MWIFIEX_MAX_SIG_STRENGTH; ix++)
		atomic_set(&phist_data->sig_str[ix], 0);
पूर्ण

व्योम *mwअगरiex_alloc_dma_align_buf(पूर्णांक rx_len, gfp_t flags)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक buf_len, pad;

	buf_len = rx_len + MWIFIEX_RX_HEADROOM + MWIFIEX_DMA_ALIGN_SZ;

	skb = __dev_alloc_skb(buf_len, flags);

	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, MWIFIEX_RX_HEADROOM);

	pad = MWIFIEX_ALIGN_ADDR(skb->data, MWIFIEX_DMA_ALIGN_SZ) -
	      (दीर्घ)skb->data;

	skb_reserve(skb, pad);

	वापस skb;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_alloc_dma_align_buf);

व्योम mwअगरiex_fw_dump_event(काष्ठा mwअगरiex_निजी *priv)
अणु
	mwअगरiex_send_cmd(priv, HostCmd_CMD_FW_DUMP_EVENT, HostCmd_ACT_GEN_SET,
			 0, शून्य, true);
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_fw_dump_event);
