<शैली गुरु>
/*
 * NXP Wireless LAN device driver: HW/FW Initialization
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

/*
 * This function adds a BSS priority table to the table list.
 *
 * The function allocates a new BSS priority table node and adds it to
 * the end of BSS priority table list, kept in driver memory.
 */
अटल पूर्णांक mwअगरiex_add_bss_prio_tbl(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_bss_prio_node *bss_prio;
	काष्ठा mwअगरiex_bss_prio_tbl *tbl = adapter->bss_prio_tbl;

	bss_prio = kzalloc(माप(काष्ठा mwअगरiex_bss_prio_node), GFP_KERNEL);
	अगर (!bss_prio)
		वापस -ENOMEM;

	bss_prio->priv = priv;
	INIT_LIST_HEAD(&bss_prio->list);

	spin_lock_bh(&tbl[priv->bss_priority].bss_prio_lock);
	list_add_tail(&bss_prio->list, &tbl[priv->bss_priority].bss_prio_head);
	spin_unlock_bh(&tbl[priv->bss_priority].bss_prio_lock);

	वापस 0;
पूर्ण

अटल व्योम wakeup_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा mwअगरiex_adapter *adapter = from_समयr(adapter, t, wakeup_समयr);

	mwअगरiex_dbg(adapter, ERROR, "Firmware wakeup failed\n");
	adapter->hw_status = MWIFIEX_HW_STATUS_RESET;
	mwअगरiex_cancel_all_pending_cmd(adapter);

	अगर (adapter->अगर_ops.card_reset)
		adapter->अगर_ops.card_reset(adapter);
पूर्ण

अटल व्योम fw_dump_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा mwअगरiex_adapter *adapter = from_समयr(adapter, t, devdump_समयr);

	mwअगरiex_upload_device_dump(adapter);
पूर्ण

/*
 * This function initializes the निजी काष्ठाure and sets शेष
 * values to the members.
 *
 * Additionally, it also initializes all the locks and sets up all the
 * lists.
 */
पूर्णांक mwअगरiex_init_priv(काष्ठा mwअगरiex_निजी *priv)
अणु
	u32 i;

	priv->media_connected = false;
	eth_broadcast_addr(priv->curr_addr);
	priv->port_खोलो = false;
	priv->usb_port = MWIFIEX_USB_EP_DATA;
	priv->pkt_tx_ctrl = 0;
	priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->data_rate = 0;	/* Initially indicate the rate as स्वतः */
	priv->is_data_rate_स्वतः = true;
	priv->bcn_avg_factor = DEFAULT_BCN_AVG_FACTOR;
	priv->data_avg_factor = DEFAULT_DATA_AVG_FACTOR;

	priv->sec_info.wep_enabled = 0;
	priv->sec_info.authentication_mode = NL80211_AUTHTYPE_OPEN_SYSTEM;
	priv->sec_info.encryption_mode = 0;
	क्रम (i = 0; i < ARRAY_SIZE(priv->wep_key); i++)
		स_रखो(&priv->wep_key[i], 0, माप(काष्ठा mwअगरiex_wep_key));
	priv->wep_key_curr_index = 0;
	priv->curr_pkt_filter = HostCmd_ACT_MAC_DYNAMIC_BW_ENABLE |
				HostCmd_ACT_MAC_RX_ON | HostCmd_ACT_MAC_TX_ON |
				HostCmd_ACT_MAC_ETHERNETII_ENABLE;

	priv->beacon_period = 100; /* beacon पूर्णांकerval */
	priv->attempted_bss_desc = शून्य;
	स_रखो(&priv->curr_bss_params, 0, माप(priv->curr_bss_params));
	priv->listen_पूर्णांकerval = MWIFIEX_DEFAULT_LISTEN_INTERVAL;

	स_रखो(&priv->prev_ssid, 0, माप(priv->prev_ssid));
	स_रखो(&priv->prev_bssid, 0, माप(priv->prev_bssid));
	स_रखो(&priv->assoc_rsp_buf, 0, माप(priv->assoc_rsp_buf));
	priv->assoc_rsp_size = 0;
	priv->adhoc_channel = DEFAULT_AD_HOC_CHANNEL;
	priv->atim_winकरोw = 0;
	priv->adhoc_state = ADHOC_IDLE;
	priv->tx_घातer_level = 0;
	priv->max_tx_घातer_level = 0;
	priv->min_tx_घातer_level = 0;
	priv->tx_ant = 0;
	priv->rx_ant = 0;
	priv->tx_rate = 0;
	priv->rxpd_htinfo = 0;
	priv->rxpd_rate = 0;
	priv->rate_biपंचांगap = 0;
	priv->data_rssi_last = 0;
	priv->data_rssi_avg = 0;
	priv->data_nf_avg = 0;
	priv->data_nf_last = 0;
	priv->bcn_rssi_last = 0;
	priv->bcn_rssi_avg = 0;
	priv->bcn_nf_avg = 0;
	priv->bcn_nf_last = 0;
	स_रखो(&priv->wpa_ie, 0, माप(priv->wpa_ie));
	स_रखो(&priv->aes_key, 0, माप(priv->aes_key));
	priv->wpa_ie_len = 0;
	priv->wpa_is_gtk_set = false;

	स_रखो(&priv->assoc_tlv_buf, 0, माप(priv->assoc_tlv_buf));
	priv->assoc_tlv_buf_len = 0;
	स_रखो(&priv->wps, 0, माप(priv->wps));
	स_रखो(&priv->gen_ie_buf, 0, माप(priv->gen_ie_buf));
	priv->gen_ie_buf_len = 0;
	स_रखो(priv->vs_ie, 0, माप(priv->vs_ie));

	priv->wmm_required = true;
	priv->wmm_enabled = false;
	priv->wmm_qosinfo = 0;
	priv->curr_bcn_buf = शून्य;
	priv->curr_bcn_size = 0;
	priv->wps_ie = शून्य;
	priv->wps_ie_len = 0;
	priv->ap_11n_enabled = 0;
	स_रखो(&priv->roc_cfg, 0, माप(priv->roc_cfg));

	priv->scan_block = false;

	priv->csa_chan = 0;
	priv->csa_expire_समय = 0;
	priv->del_list_idx = 0;
	priv->hs2_enabled = false;
	priv->check_tdls_tx = false;
	स_नकल(priv->tos_to_tid_inv, tos_to_tid_inv, MAX_NUM_TID);

	mwअगरiex_init_11h_params(priv);

	वापस mwअगरiex_add_bss_prio_tbl(priv);
पूर्ण

/*
 * This function allocates buffers क्रम members of the adapter
 * काष्ठाure.
 *
 * The memory allocated includes scan table, command buffers, and
 * sleep confirm command buffer. In addition, the queues are
 * also initialized.
 */
अटल पूर्णांक mwअगरiex_allocate_adapter(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret;

	/* Allocate command buffer */
	ret = mwअगरiex_alloc_cmd_buffer(adapter);
	अगर (ret) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: failed to alloc cmd buffer\n",
			    __func__);
		वापस -1;
	पूर्ण

	adapter->sleep_cfm =
		dev_alloc_skb(माप(काष्ठा mwअगरiex_opt_sleep_confirm)
			      + INTF_HEADER_LEN);

	अगर (!adapter->sleep_cfm) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: failed to alloc sleep cfm\t"
			    " cmd buffer\n", __func__);
		वापस -1;
	पूर्ण
	skb_reserve(adapter->sleep_cfm, INTF_HEADER_LEN);

	वापस 0;
पूर्ण

/*
 * This function initializes the adapter काष्ठाure and sets शेष
 * values to the members of adapter.
 *
 * This also initializes the WMM related parameters in the driver निजी
 * काष्ठाures.
 */
अटल व्योम mwअगरiex_init_adapter(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_opt_sleep_confirm *sleep_cfm_buf = शून्य;

	skb_put(adapter->sleep_cfm, माप(काष्ठा mwअगरiex_opt_sleep_confirm));

	adapter->cmd_sent = false;

	अगर (adapter->अगरace_type == MWIFIEX_SDIO)
		adapter->data_sent = true;
	अन्यथा
		adapter->data_sent = false;

	अगर (adapter->अगरace_type == MWIFIEX_USB)
		adapter->पूर्णांकf_hdr_len = 0;
	अन्यथा
		adapter->पूर्णांकf_hdr_len = INTF_HEADER_LEN;

	adapter->cmd_resp_received = false;
	adapter->event_received = false;
	adapter->data_received = false;

	clear_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags);

	adapter->hw_status = MWIFIEX_HW_STATUS_INITIALIZING;

	adapter->ps_mode = MWIFIEX_802_11_POWER_MODE_CAM;
	adapter->ps_state = PS_STATE_AWAKE;
	adapter->need_to_wakeup = false;

	adapter->scan_mode = HostCmd_BSS_MODE_ANY;
	adapter->specअगरic_scan_समय = MWIFIEX_SPECIFIC_SCAN_CHAN_TIME;
	adapter->active_scan_समय = MWIFIEX_ACTIVE_SCAN_CHAN_TIME;
	adapter->passive_scan_समय = MWIFIEX_PASSIVE_SCAN_CHAN_TIME;
	adapter->scan_chan_gap_समय = MWIFIEX_DEF_SCAN_CHAN_GAP_TIME;

	adapter->scan_probes = 1;

	adapter->multiple_dtim = 1;

	adapter->local_listen_पूर्णांकerval = 0;	/* शेष value in firmware
						   will be used */

	adapter->is_deep_sleep = false;

	adapter->delay_null_pkt = false;
	adapter->delay_to_ps = 1000;
	adapter->enhanced_ps_mode = PS_MODE_AUTO;

	adapter->gen_null_pkt = false;	/* Disable शून्य Pkg generation by
					   शेष */
	adapter->pps_uapsd_mode = false; /* Disable pps/uapsd mode by
					   शेष */
	adapter->pm_wakeup_card_req = false;

	adapter->pm_wakeup_fw_try = false;

	adapter->curr_tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;

	clear_bit(MWIFIEX_IS_HS_CONFIGURED, &adapter->work_flags);
	adapter->hs_cfg.conditions = cpu_to_le32(HS_CFG_COND_DEF);
	adapter->hs_cfg.gpio = HS_CFG_GPIO_DEF;
	adapter->hs_cfg.gap = HS_CFG_GAP_DEF;
	adapter->hs_activated = false;

	स_रखो(adapter->event_body, 0, माप(adapter->event_body));
	adapter->hw_करोt_11n_dev_cap = 0;
	adapter->hw_dev_mcs_support = 0;
	adapter->sec_chan_offset = 0;
	adapter->adhoc_11n_enabled = false;

	mwअगरiex_wmm_init(adapter);
	atomic_set(&adapter->tx_hw_pending, 0);

	sleep_cfm_buf = (काष्ठा mwअगरiex_opt_sleep_confirm *)
					adapter->sleep_cfm->data;
	स_रखो(sleep_cfm_buf, 0, adapter->sleep_cfm->len);
	sleep_cfm_buf->command = cpu_to_le16(HostCmd_CMD_802_11_PS_MODE_ENH);
	sleep_cfm_buf->size = cpu_to_le16(adapter->sleep_cfm->len);
	sleep_cfm_buf->result = 0;
	sleep_cfm_buf->action = cpu_to_le16(SLEEP_CONFIRM);
	sleep_cfm_buf->resp_ctrl = cpu_to_le16(RESP_NEEDED);

	स_रखो(&adapter->sleep_params, 0, माप(adapter->sleep_params));
	स_रखो(&adapter->sleep_period, 0, माप(adapter->sleep_period));
	adapter->tx_lock_flag = false;
	adapter->null_pkt_पूर्णांकerval = 0;
	adapter->fw_bands = 0;
	adapter->config_bands = 0;
	adapter->adhoc_start_band = 0;
	adapter->scan_channels = शून्य;
	adapter->fw_release_number = 0;
	adapter->fw_cap_info = 0;
	स_रखो(&adapter->upld_buf, 0, माप(adapter->upld_buf));
	adapter->event_cause = 0;
	adapter->region_code = 0;
	adapter->bcn_miss_समय_out = DEFAULT_BCN_MISS_TIMEOUT;
	adapter->adhoc_awake_period = 0;
	स_रखो(&adapter->arp_filter, 0, माप(adapter->arp_filter));
	adapter->arp_filter_size = 0;
	adapter->max_mgmt_ie_index = MAX_MGMT_IE_INDEX;
	adapter->mfg_mode = mfg_mode;
	adapter->key_api_major_ver = 0;
	adapter->key_api_minor_ver = 0;
	eth_broadcast_addr(adapter->perm_addr);
	adapter->अगरace_limit.sta_पूर्णांकf = MWIFIEX_MAX_STA_NUM;
	adapter->अगरace_limit.uap_पूर्णांकf = MWIFIEX_MAX_UAP_NUM;
	adapter->अगरace_limit.p2p_पूर्णांकf = MWIFIEX_MAX_P2P_NUM;
	adapter->active_scan_triggered = false;
	समयr_setup(&adapter->wakeup_समयr, wakeup_समयr_fn, 0);
	adapter->devdump_len = 0;
	समयr_setup(&adapter->devdump_समयr, fw_dump_समयr_fn, 0);
पूर्ण

/*
 * This function sets trans_start per tx_queue
 */
व्योम mwअगरiex_set_trans_start(काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++)
		netdev_get_tx_queue(dev, i)->trans_start = jअगरfies;

	netअगर_trans_update(dev);
पूर्ण

/*
 * This function wakes up all queues in net_device
 */
व्योम mwअगरiex_wake_up_net_dev_queue(काष्ठा net_device *netdev,
					काष्ठा mwअगरiex_adapter *adapter)
अणु
	spin_lock_bh(&adapter->queue_lock);
	netअगर_tx_wake_all_queues(netdev);
	spin_unlock_bh(&adapter->queue_lock);
पूर्ण

/*
 * This function stops all queues in net_device
 */
व्योम mwअगरiex_stop_net_dev_queue(काष्ठा net_device *netdev,
					काष्ठा mwअगरiex_adapter *adapter)
अणु
	spin_lock_bh(&adapter->queue_lock);
	netअगर_tx_stop_all_queues(netdev);
	spin_unlock_bh(&adapter->queue_lock);
पूर्ण

/*
 * This function invalidates the list heads.
 */
अटल व्योम mwअगरiex_invalidate_lists(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	s32 i, j;

	list_del(&adapter->cmd_मुक्त_q);
	list_del(&adapter->cmd_pending_q);
	list_del(&adapter->scan_pending_q);

	क्रम (i = 0; i < adapter->priv_num; i++)
		list_del(&adapter->bss_prio_tbl[i].bss_prio_head);

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i]) अणु
			priv = adapter->priv[i];
			क्रम (j = 0; j < MAX_NUM_TID; ++j)
				list_del(&priv->wmm.tid_tbl_ptr[j].ra_list);
			list_del(&priv->tx_ba_stream_tbl_ptr);
			list_del(&priv->rx_reorder_tbl_ptr);
			list_del(&priv->sta_list);
			list_del(&priv->स्वतः_tdls_list);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function perक्रमms cleanup क्रम adapter काष्ठाure.
 *
 * The cleanup is करोne recursively, by canceling all pending
 * commands, मुक्तing the member buffers previously allocated
 * (command buffers, scan table buffer, sleep confirm command
 * buffer), stopping the समयrs and calling the cleanup routines
 * क्रम every पूर्णांकerface.
 */
अटल व्योम
mwअगरiex_adapter_cleanup(काष्ठा mwअगरiex_adapter *adapter)
अणु
	del_समयr(&adapter->wakeup_समयr);
	del_समयr_sync(&adapter->devdump_समयr);
	mwअगरiex_cancel_all_pending_cmd(adapter);
	wake_up_पूर्णांकerruptible(&adapter->cmd_रुको_q.रुको);
	wake_up_पूर्णांकerruptible(&adapter->hs_activate_रुको_q);
पूर्ण

व्योम mwअगरiex_मुक्त_cmd_buffers(काष्ठा mwअगरiex_adapter *adapter)
अणु
	mwअगरiex_invalidate_lists(adapter);

	/* Free command buffer */
	mwअगरiex_dbg(adapter, INFO, "info: free cmd buffer\n");
	mwअगरiex_मुक्त_cmd_buffer(adapter);

	अगर (adapter->sleep_cfm)
		dev_kमुक्त_skb_any(adapter->sleep_cfm);
पूर्ण

/*
 *  This function पूर्णांकializes the lock variables and
 *  the list heads.
 */
पूर्णांक mwअगरiex_init_lock_list(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	s32 i, j;

	spin_lock_init(&adapter->पूर्णांक_lock);
	spin_lock_init(&adapter->मुख्य_proc_lock);
	spin_lock_init(&adapter->mwअगरiex_cmd_lock);
	spin_lock_init(&adapter->queue_lock);
	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i]) अणु
			priv = adapter->priv[i];
			spin_lock_init(&priv->wmm.ra_list_spinlock);
			spin_lock_init(&priv->curr_bcn_buf_lock);
			spin_lock_init(&priv->sta_list_spinlock);
			spin_lock_init(&priv->स्वतः_tdls_lock);
		पूर्ण
	पूर्ण

	/* Initialize cmd_मुक्त_q */
	INIT_LIST_HEAD(&adapter->cmd_मुक्त_q);
	/* Initialize cmd_pending_q */
	INIT_LIST_HEAD(&adapter->cmd_pending_q);
	/* Initialize scan_pending_q */
	INIT_LIST_HEAD(&adapter->scan_pending_q);

	spin_lock_init(&adapter->cmd_मुक्त_q_lock);
	spin_lock_init(&adapter->cmd_pending_q_lock);
	spin_lock_init(&adapter->scan_pending_q_lock);
	spin_lock_init(&adapter->rx_proc_lock);

	skb_queue_head_init(&adapter->rx_data_q);
	skb_queue_head_init(&adapter->tx_data_q);

	क्रम (i = 0; i < adapter->priv_num; ++i) अणु
		INIT_LIST_HEAD(&adapter->bss_prio_tbl[i].bss_prio_head);
		spin_lock_init(&adapter->bss_prio_tbl[i].bss_prio_lock);
	पूर्ण

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (!adapter->priv[i])
			जारी;
		priv = adapter->priv[i];
		क्रम (j = 0; j < MAX_NUM_TID; ++j)
			INIT_LIST_HEAD(&priv->wmm.tid_tbl_ptr[j].ra_list);
		INIT_LIST_HEAD(&priv->tx_ba_stream_tbl_ptr);
		INIT_LIST_HEAD(&priv->rx_reorder_tbl_ptr);
		INIT_LIST_HEAD(&priv->sta_list);
		INIT_LIST_HEAD(&priv->स्वतः_tdls_list);
		skb_queue_head_init(&priv->tdls_txq);
		skb_queue_head_init(&priv->bypass_txq);

		spin_lock_init(&priv->tx_ba_stream_tbl_lock);
		spin_lock_init(&priv->rx_reorder_tbl_lock);

		spin_lock_init(&priv->ack_status_lock);
		idr_init(&priv->ack_status_frames);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function initializes the firmware.
 *
 * The following operations are perक्रमmed sequentially -
 *      - Allocate adapter काष्ठाure
 *      - Initialize the adapter काष्ठाure
 *      - Initialize the निजी काष्ठाure
 *      - Add BSS priority tables to the adapter काष्ठाure
 *      - For each पूर्णांकerface, send the init commands to firmware
 *      - Send the first command in command pending queue, अगर available
 */
पूर्णांक mwअगरiex_init_fw(काष्ठा mwअगरiex_adapter *adapter)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_निजी *priv;
	u8 i, first_sta = true;
	पूर्णांक is_cmd_pend_q_empty;

	adapter->hw_status = MWIFIEX_HW_STATUS_INITIALIZING;

	/* Allocate memory क्रम member of adapter काष्ठाure */
	ret = mwअगरiex_allocate_adapter(adapter);
	अगर (ret)
		वापस -1;

	/* Initialize adapter काष्ठाure */
	mwअगरiex_init_adapter(adapter);

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i]) अणु
			priv = adapter->priv[i];

			/* Initialize निजी काष्ठाure */
			ret = mwअगरiex_init_priv(priv);
			अगर (ret)
				वापस -1;
		पूर्ण
	पूर्ण
	अगर (adapter->mfg_mode) अणु
		adapter->hw_status = MWIFIEX_HW_STATUS_READY;
		ret = -EINPROGRESS;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adapter->priv_num; i++) अणु
			अगर (adapter->priv[i]) अणु
				ret = mwअगरiex_sta_init_cmd(adapter->priv[i],
							   first_sta, true);
				अगर (ret == -1)
					वापस -1;

				first_sta = false;
			पूर्ण



		पूर्ण
	पूर्ण

	spin_lock_bh(&adapter->cmd_pending_q_lock);
	is_cmd_pend_q_empty = list_empty(&adapter->cmd_pending_q);
	spin_unlock_bh(&adapter->cmd_pending_q_lock);
	अगर (!is_cmd_pend_q_empty) अणु
		/* Send the first command in queue and वापस */
		अगर (mwअगरiex_मुख्य_process(adapter) != -1)
			ret = -EINPROGRESS;
	पूर्ण अन्यथा अणु
		adapter->hw_status = MWIFIEX_HW_STATUS_READY;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function deletes the BSS priority tables.
 *
 * The function traverses through all the allocated BSS priority nodes
 * in every BSS priority table and मुक्तs them.
 */
अटल व्योम mwअगरiex_delete_bss_prio_tbl(काष्ठा mwअगरiex_निजी *priv)
अणु
	पूर्णांक i;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_bss_prio_node *bssprio_node, *पंचांगp_node;
	काष्ठा list_head *head;
	spinlock_t *lock; /* bss priority lock */

	क्रम (i = 0; i < adapter->priv_num; ++i) अणु
		head = &adapter->bss_prio_tbl[i].bss_prio_head;
		lock = &adapter->bss_prio_tbl[i].bss_prio_lock;
		mwअगरiex_dbg(adapter, INFO,
			    "info: delete BSS priority table,\t"
			    "bss_type = %d, bss_num = %d, i = %d,\t"
			    "head = %p\n",
			    priv->bss_type, priv->bss_num, i, head);

		अणु
			spin_lock_bh(lock);
			list_क्रम_each_entry_safe(bssprio_node, पंचांगp_node, head,
						 list) अणु
				अगर (bssprio_node->priv == priv) अणु
					mwअगरiex_dbg(adapter, INFO,
						    "info: Delete\t"
						    "node %p, next = %p\n",
						    bssprio_node, पंचांगp_node);
					list_del(&bssprio_node->list);
					kमुक्त(bssprio_node);
				पूर्ण
			पूर्ण
			spin_unlock_bh(lock);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This function मुक्तs the निजी काष्ठाure, including cleans
 * up the TX and RX queues and मुक्तs the BSS priority tables.
 */
व्योम mwअगरiex_मुक्त_priv(काष्ठा mwअगरiex_निजी *priv)
अणु
	mwअगरiex_clean_txrx(priv);
	mwअगरiex_delete_bss_prio_tbl(priv);
	mwअगरiex_मुक्त_curr_bcn(priv);
पूर्ण

/*
 * This function is used to shutकरोwn the driver.
 *
 * The following operations are perक्रमmed sequentially -
 *      - Check अगर alपढ़ोy shut करोwn
 *      - Make sure the मुख्य process has stopped
 *      - Clean up the Tx and Rx queues
 *      - Delete BSS priority tables
 *      - Free the adapter
 *      - Notअगरy completion
 */
व्योम
mwअगरiex_shutकरोwn_drv(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	s32 i;
	काष्ठा sk_buff *skb;

	/* mwअगरiex alपढ़ोy shutकरोwn */
	अगर (adapter->hw_status == MWIFIEX_HW_STATUS_NOT_READY)
		वापस;

	/* cancel current command */
	अगर (adapter->curr_cmd) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "curr_cmd is still in processing\n");
		del_समयr_sync(&adapter->cmd_समयr);
		mwअगरiex_recycle_cmd_node(adapter, adapter->curr_cmd);
		adapter->curr_cmd = शून्य;
	पूर्ण

	/* shut करोwn mwअगरiex */
	mwअगरiex_dbg(adapter, MSG,
		    "info: shutdown mwifiex...\n");

	/* Clean up Tx/Rx queues and delete BSS priority table */
	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i]) अणु
			priv = adapter->priv[i];

			mwअगरiex_clean_स्वतः_tdls(priv);
			mwअगरiex_पात_cac(priv);
			mwअगरiex_मुक्त_priv(priv);
		पूर्ण
	पूर्ण

	atomic_set(&adapter->tx_queued, 0);
	जबतक ((skb = skb_dequeue(&adapter->tx_data_q)))
		mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0, 0);

	spin_lock_bh(&adapter->rx_proc_lock);

	जबतक ((skb = skb_dequeue(&adapter->rx_data_q))) अणु
		काष्ठा mwअगरiex_rxinfo *rx_info = MWIFIEX_SKB_RXCB(skb);

		atomic_dec(&adapter->rx_pending);
		priv = adapter->priv[rx_info->bss_num];
		अगर (priv)
			priv->stats.rx_dropped++;

		dev_kमुक्त_skb_any(skb);
	पूर्ण

	spin_unlock_bh(&adapter->rx_proc_lock);

	mwअगरiex_adapter_cleanup(adapter);

	adapter->hw_status = MWIFIEX_HW_STATUS_NOT_READY;
पूर्ण

/*
 * This function करोwnloads the firmware to the card.
 *
 * The actual करोwnload is preceded by two sanity checks -
 *      - Check अगर firmware is alपढ़ोy running
 *      - Check अगर the पूर्णांकerface is the winner to करोwnload the firmware
 *
 * ...and followed by another -
 *      - Check अगर the firmware is करोwnloaded successfully
 *
 * After करोwnload is successfully completed, the host पूर्णांकerrupts are enabled.
 */
पूर्णांक mwअगरiex_dnld_fw(काष्ठा mwअगरiex_adapter *adapter,
		    काष्ठा mwअगरiex_fw_image *pmfw)
अणु
	पूर्णांक ret;
	u32 poll_num = 1;

	/* check अगर firmware is alपढ़ोy running */
	ret = adapter->अगर_ops.check_fw_status(adapter, poll_num);
	अगर (!ret) अणु
		mwअगरiex_dbg(adapter, MSG,
			    "WLAN FW already running! Skip FW dnld\n");
		वापस 0;
	पूर्ण

	/* check अगर we are the winner क्रम करोwnloading FW */
	अगर (adapter->अगर_ops.check_winner_status) अणु
		adapter->winner = 0;
		ret = adapter->अगर_ops.check_winner_status(adapter);

		poll_num = MAX_FIRMWARE_POLL_TRIES;
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, MSG,
				    "WLAN read winner status failed!\n");
			वापस ret;
		पूर्ण

		अगर (!adapter->winner) अणु
			mwअगरiex_dbg(adapter, MSG,
				    "WLAN is not the winner! Skip FW dnld\n");
			जाओ poll_fw;
		पूर्ण
	पूर्ण

	अगर (pmfw) अणु
		/* Download firmware with helper */
		ret = adapter->अगर_ops.prog_fw(adapter, pmfw);
		अगर (ret) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "prog_fw failed ret=%#x\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

poll_fw:
	/* Check अगर the firmware is करोwnloaded successfully or not */
	ret = adapter->अगर_ops.check_fw_status(adapter, poll_num);
	अगर (ret)
		mwअगरiex_dbg(adapter, ERROR,
			    "FW failed to be active in time\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_dnld_fw);
