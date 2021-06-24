<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2014 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <net/mac80211.h>

#समावेश "iwl-io.h"
#समावेश "iwl-agn-hw.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-modparams.h"

#समावेश "dev.h"
#समावेश "agn.h"

पूर्णांक iwlagn_hw_valid_rtc_data_addr(u32 addr)
अणु
	वापस (addr >= IWLAGN_RTC_DATA_LOWER_BOUND) &&
		(addr < IWLAGN_RTC_DATA_UPPER_BOUND);
पूर्ण

पूर्णांक iwlagn_send_tx_घातer(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwlagn_tx_घातer_dbm_cmd tx_घातer_cmd;
	u8 tx_ant_cfg_cmd;

	अगर (WARN_ONCE(test_bit(STATUS_SCAN_HW, &priv->status),
		      "TX Power requested while scanning!\n"))
		वापस -EAGAIN;

	/* half dBm need to multiply */
	tx_घातer_cmd.global_lmt = (s8)(2 * priv->tx_घातer_user_lmt);

	अगर (tx_घातer_cmd.global_lmt > priv->nvm_data->max_tx_pwr_half_dbm) अणु
		/*
		 * For the newer devices which using enhanced/extend tx घातer
		 * table in EEPROM, the क्रमmat is in half dBm. driver need to
		 * convert to dBm क्रमmat beक्रमe report to mac80211.
		 * By करोing so, there is a possibility of 1/2 dBm resolution
		 * lost. driver will perक्रमm "round-up" operation beक्रमe
		 * reporting, but it will cause 1/2 dBm tx घातer over the
		 * regulatory limit. Perक्रमm the checking here, अगर the
		 * "tx_power_user_lmt" is higher than EEPROM value (in
		 * half-dBm क्रमmat), lower the tx घातer based on EEPROM
		 */
		tx_घातer_cmd.global_lmt =
			priv->nvm_data->max_tx_pwr_half_dbm;
	पूर्ण
	tx_घातer_cmd.flags = IWLAGN_TX_POWER_NO_CLOSED;
	tx_घातer_cmd.srv_chan_lmt = IWLAGN_TX_POWER_AUTO;

	अगर (IWL_UCODE_API(priv->fw->ucode_ver) == 1)
		tx_ant_cfg_cmd = REPLY_TX_POWER_DBM_CMD_V1;
	अन्यथा
		tx_ant_cfg_cmd = REPLY_TX_POWER_DBM_CMD;

	वापस iwl_dvm_send_cmd_pdu(priv, tx_ant_cfg_cmd, 0,
			माप(tx_घातer_cmd), &tx_घातer_cmd);
पूर्ण

व्योम iwlagn_temperature(काष्ठा iwl_priv *priv)
अणु
	lockdep_निश्चित_held(&priv->statistics.lock);

	/* store temperature from correct statistics (in Celsius) */
	priv->temperature = le32_to_cpu(priv->statistics.common.temperature);
	iwl_tt_handler(priv);
पूर्ण

पूर्णांक iwlagn_hwrate_to_mac80211_idx(u32 rate_n_flags, क्रमागत nl80211_band band)
अणु
	पूर्णांक idx = 0;
	पूर्णांक band_offset = 0;

	/* HT rate क्रमmat: mac80211 wants an MCS number, which is just LSB */
	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		idx = (rate_n_flags & 0xff);
		वापस idx;
	/* Legacy rate क्रमmat, search क्रम match in table */
	पूर्ण अन्यथा अणु
		अगर (band == NL80211_BAND_5GHZ)
			band_offset = IWL_FIRST_OFDM_RATE;
		क्रम (idx = band_offset; idx < IWL_RATE_COUNT_LEGACY; idx++)
			अगर (iwl_rates[idx].plcp == (rate_n_flags & 0xFF))
				वापस idx - band_offset;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक iwlagn_manage_ibss_station(काष्ठा iwl_priv *priv,
			       काष्ठा ieee80211_vअगर *vअगर, bool add)
अणु
	काष्ठा iwl_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;

	अगर (add)
		वापस iwlagn_add_bssid_station(priv, vअगर_priv->ctx,
						vअगर->bss_conf.bssid,
						&vअगर_priv->ibss_bssid_sta_id);
	वापस iwl_हटाओ_station(priv, vअगर_priv->ibss_bssid_sta_id,
				  vअगर->bss_conf.bssid);
पूर्ण

/*
 * iwlagn_txfअगरo_flush: send REPLY_TXFIFO_FLUSH command to uCode
 *
 * pre-requirements:
 *  1. acquire mutex beक्रमe calling
 *  2. make sure rf is on and not in निकास state
 */
पूर्णांक iwlagn_txfअगरo_flush(काष्ठा iwl_priv *priv, u32 scd_q_msk)
अणु
	काष्ठा iwl_txfअगरo_flush_cmd_v3 flush_cmd_v3 = अणु
		.flush_control = cpu_to_le16(IWL_DROP_ALL),
	पूर्ण;
	काष्ठा iwl_txfअगरo_flush_cmd_v2 flush_cmd_v2 = अणु
		.flush_control = cpu_to_le16(IWL_DROP_ALL),
	पूर्ण;

	u32 queue_control = IWL_SCD_VO_MSK | IWL_SCD_VI_MSK |
			    IWL_SCD_BE_MSK | IWL_SCD_BK_MSK | IWL_SCD_MGMT_MSK;

	अगर ((priv->valid_contexts != BIT(IWL_RXON_CTX_BSS)))
		queue_control |= IWL_PAN_SCD_VO_MSK | IWL_PAN_SCD_VI_MSK |
				 IWL_PAN_SCD_BE_MSK | IWL_PAN_SCD_BK_MSK |
				 IWL_PAN_SCD_MGMT_MSK |
				 IWL_PAN_SCD_MULTICAST_MSK;

	अगर (priv->nvm_data->sku_cap_11n_enable)
		queue_control |= IWL_AGG_TX_QUEUE_MSK;

	अगर (scd_q_msk)
		queue_control = scd_q_msk;

	IWL_DEBUG_INFO(priv, "queue control: 0x%x\n", queue_control);
	flush_cmd_v3.queue_control = cpu_to_le32(queue_control);
	flush_cmd_v2.queue_control = cpu_to_le16((u16)queue_control);

	अगर (IWL_UCODE_API(priv->fw->ucode_ver) > 2)
		वापस iwl_dvm_send_cmd_pdu(priv, REPLY_TXFIFO_FLUSH, 0,
					    माप(flush_cmd_v3),
					    &flush_cmd_v3);
	वापस iwl_dvm_send_cmd_pdu(priv, REPLY_TXFIFO_FLUSH, 0,
				    माप(flush_cmd_v2), &flush_cmd_v2);
पूर्ण

व्योम iwlagn_dev_txfअगरo_flush(काष्ठा iwl_priv *priv)
अणु
	mutex_lock(&priv->mutex);
	ieee80211_stop_queues(priv->hw);
	अगर (iwlagn_txfअगरo_flush(priv, 0)) अणु
		IWL_ERR(priv, "flush request fail\n");
		जाओ करोne;
	पूर्ण
	IWL_DEBUG_INFO(priv, "wait transmit/flush all frames\n");
	iwl_trans_रुको_tx_queues_empty(priv->trans, 0xffffffff);
करोne:
	ieee80211_wake_queues(priv->hw);
	mutex_unlock(&priv->mutex);
पूर्ण

/*
 * BT coex
 */
/* Noपंचांगal TDM */
अटल स्थिर __le32 iwlagn_def_3w_lookup[IWLAGN_BT_DECISION_LUT_SIZE] = अणु
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaeaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xcc00ff28),
	cpu_to_le32(0x0000aaaa),
	cpu_to_le32(0xcc00aaaa),
	cpu_to_le32(0x0000aaaa),
	cpu_to_le32(0xc0004000),
	cpu_to_le32(0x00004000),
	cpu_to_le32(0xf0005000),
	cpu_to_le32(0xf0005000),
पूर्ण;

/* Full concurrency */
अटल स्थिर __le32 iwlagn_concurrent_lookup[IWLAGN_BT_DECISION_LUT_SIZE] = अणु
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0xaaaaaaaa),
	cpu_to_le32(0x00000000),
	cpu_to_le32(0x00000000),
	cpu_to_le32(0x00000000),
	cpu_to_le32(0x00000000),
पूर्ण;

व्योम iwlagn_send_advance_bt_config(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_basic_bt_cmd basic = अणु
		.max_समाप्त = IWLAGN_BT_MAX_KILL_DEFAULT,
		.bt3_समयr_t7_value = IWLAGN_BT3_T7_DEFAULT,
		.bt3_prio_sample_समय = IWLAGN_BT3_PRIO_SAMPLE_DEFAULT,
		.bt3_समयr_t2_value = IWLAGN_BT3_T2_DEFAULT,
	पूर्ण;
	काष्ठा iwl_bt_cmd_v1 bt_cmd_v1;
	काष्ठा iwl_bt_cmd_v2 bt_cmd_v2;
	पूर्णांक ret;

	BUILD_BUG_ON(माप(iwlagn_def_3w_lookup) !=
			माप(basic.bt3_lookup_table));

	अगर (priv->lib->bt_params) अणु
		/*
		 * newer generation of devices (2000 series and newer)
		 * use the version 2 of the bt command
		 * we need to make sure sending the host command
		 * with correct data काष्ठाure to aव्योम uCode निश्चित
		 */
		अगर (priv->lib->bt_params->bt_session_2) अणु
			bt_cmd_v2.prio_boost = cpu_to_le32(
				priv->lib->bt_params->bt_prio_boost);
			bt_cmd_v2.tx_prio_boost = 0;
			bt_cmd_v2.rx_prio_boost = 0;
		पूर्ण अन्यथा अणु
			/* older version only has 8 bits */
			WARN_ON(priv->lib->bt_params->bt_prio_boost & ~0xFF);
			bt_cmd_v1.prio_boost =
				priv->lib->bt_params->bt_prio_boost;
			bt_cmd_v1.tx_prio_boost = 0;
			bt_cmd_v1.rx_prio_boost = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		IWL_ERR(priv, "failed to construct BT Coex Config\n");
		वापस;
	पूर्ण

	/*
	 * Possible situations when BT needs to take over क्रम receive,
	 * at the same समय where STA needs to response to AP's frame(s),
	 * reduce the tx घातer of the required response frames, by that,
	 * allow the concurrent BT receive & WiFi transmit
	 * (BT - ANT A, WiFi -ANT B), without पूर्णांकerference to one another
	 *
	 * Reduced tx घातer apply to control frames only (ACK/Back/CTS)
	 * when indicated by the BT config command
	 */
	basic.समाप्त_ack_mask = priv->समाप्त_ack_mask;
	basic.समाप्त_cts_mask = priv->समाप्त_cts_mask;
	अगर (priv->reduced_txघातer)
		basic.reduce_txघातer = IWLAGN_BT_REDUCED_TX_PWR;
	basic.valid = priv->bt_valid;

	/*
	 * Configure BT coex mode to "no coexistence" when the
	 * user disabled BT coexistence, we have no पूर्णांकerface
	 * (might be in monitor mode), or the पूर्णांकerface is in
	 * IBSS mode (no proper uCode support क्रम coex then).
	 */
	अगर (!iwlwअगरi_mod_params.bt_coex_active ||
	    priv->iw_mode == NL80211_IFTYPE_ADHOC) अणु
		basic.flags = IWLAGN_BT_FLAG_COEX_MODE_DISABLED;
	पूर्ण अन्यथा अणु
		basic.flags = IWLAGN_BT_FLAG_COEX_MODE_3W <<
					IWLAGN_BT_FLAG_COEX_MODE_SHIFT;

		अगर (!priv->bt_enable_pspoll)
			basic.flags |= IWLAGN_BT_FLAG_SYNC_2_BT_DISABLE;
		अन्यथा
			basic.flags &= ~IWLAGN_BT_FLAG_SYNC_2_BT_DISABLE;

		अगर (priv->bt_ch_announce)
			basic.flags |= IWLAGN_BT_FLAG_CHANNEL_INHIBITION;
		IWL_DEBUG_COEX(priv, "BT coex flag: 0X%x\n", basic.flags);
	पूर्ण
	priv->bt_enable_flag = basic.flags;
	अगर (priv->bt_full_concurrent)
		स_नकल(basic.bt3_lookup_table, iwlagn_concurrent_lookup,
			माप(iwlagn_concurrent_lookup));
	अन्यथा
		स_नकल(basic.bt3_lookup_table, iwlagn_def_3w_lookup,
			माप(iwlagn_def_3w_lookup));

	IWL_DEBUG_COEX(priv, "BT coex %s in %s mode\n",
		       basic.flags ? "active" : "disabled",
		       priv->bt_full_concurrent ?
		       "full concurrency" : "3-wire");

	अगर (priv->lib->bt_params->bt_session_2) अणु
		स_नकल(&bt_cmd_v2.basic, &basic,
			माप(basic));
		ret = iwl_dvm_send_cmd_pdu(priv, REPLY_BT_CONFIG,
			0, माप(bt_cmd_v2), &bt_cmd_v2);
	पूर्ण अन्यथा अणु
		स_नकल(&bt_cmd_v1.basic, &basic,
			माप(basic));
		ret = iwl_dvm_send_cmd_pdu(priv, REPLY_BT_CONFIG,
			0, माप(bt_cmd_v1), &bt_cmd_v1);
	पूर्ण
	अगर (ret)
		IWL_ERR(priv, "failed to send BT Coex Config\n");

पूर्ण

व्योम iwlagn_bt_adjust_rssi_monitor(काष्ठा iwl_priv *priv, bool rssi_ena)
अणु
	काष्ठा iwl_rxon_context *ctx, *found_ctx = शून्य;
	bool found_ap = false;

	lockdep_निश्चित_held(&priv->mutex);

	/* Check whether AP or GO mode is active. */
	अगर (rssi_ena) अणु
		क्रम_each_context(priv, ctx) अणु
			अगर (ctx->vअगर && ctx->vअगर->type == NL80211_IFTYPE_AP &&
			    iwl_is_associated_ctx(ctx)) अणु
				found_ap = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * If disable was received or If GO/AP mode, disable RSSI
	 * measurements.
	 */
	अगर (!rssi_ena || found_ap) अणु
		अगर (priv->cur_rssi_ctx) अणु
			ctx = priv->cur_rssi_ctx;
			ieee80211_disable_rssi_reports(ctx->vअगर);
			priv->cur_rssi_ctx = शून्य;
		पूर्ण
		वापस;
	पूर्ण

	/*
	 * If rssi measurements need to be enabled, consider all हालs now.
	 * Figure out how many contexts are active.
	 */
	क्रम_each_context(priv, ctx) अणु
		अगर (ctx->vअगर && ctx->vअगर->type == NL80211_IFTYPE_STATION &&
		    iwl_is_associated_ctx(ctx)) अणु
			found_ctx = ctx;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * rssi monitor alपढ़ोy enabled क्रम the correct पूर्णांकerface...nothing
	 * to करो.
	 */
	अगर (found_ctx == priv->cur_rssi_ctx)
		वापस;

	/*
	 * Figure out अगर rssi monitor is currently enabled, and needs
	 * to be changed. If rssi monitor is alपढ़ोy enabled, disable
	 * it first अन्यथा just enable rssi measurements on the
	 * पूर्णांकerface found above.
	 */
	अगर (priv->cur_rssi_ctx) अणु
		ctx = priv->cur_rssi_ctx;
		अगर (ctx->vअगर)
			ieee80211_disable_rssi_reports(ctx->vअगर);
	पूर्ण

	priv->cur_rssi_ctx = found_ctx;

	अगर (!found_ctx)
		वापस;

	ieee80211_enable_rssi_reports(found_ctx->vअगर,
			IWLAGN_BT_PSP_MIN_RSSI_THRESHOLD,
			IWLAGN_BT_PSP_MAX_RSSI_THRESHOLD);
पूर्ण

अटल bool iwlagn_bt_traffic_is_sco(काष्ठा iwl_bt_uart_msg *uart_msg)
अणु
	वापस (BT_UART_MSG_FRAME3SCOESCO_MSK & uart_msg->frame3) >>
		BT_UART_MSG_FRAME3SCOESCO_POS;
पूर्ण

अटल व्योम iwlagn_bt_traffic_change_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv =
		container_of(work, काष्ठा iwl_priv, bt_traffic_change_work);
	काष्ठा iwl_rxon_context *ctx;
	पूर्णांक smps_request = -1;

	अगर (priv->bt_enable_flag == IWLAGN_BT_FLAG_COEX_MODE_DISABLED) अणु
		/* bt coex disabled */
		वापस;
	पूर्ण

	/*
	 * Note: bt_traffic_load can be overridden by scan complete and
	 * coex profile notअगरications. Ignore that since only bad consequence
	 * can be not matching debug prपूर्णांक with actual state.
	 */
	IWL_DEBUG_COEX(priv, "BT traffic load changes: %d\n",
		       priv->bt_traffic_load);

	चयन (priv->bt_traffic_load) अणु
	हाल IWL_BT_COEX_TRAFFIC_LOAD_NONE:
		अगर (priv->bt_status)
			smps_request = IEEE80211_SMPS_DYNAMIC;
		अन्यथा
			smps_request = IEEE80211_SMPS_AUTOMATIC;
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_LOW:
		smps_request = IEEE80211_SMPS_DYNAMIC;
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_HIGH:
	हाल IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS:
		smps_request = IEEE80211_SMPS_STATIC;
		अवरोध;
	शेष:
		IWL_ERR(priv, "Invalid BT traffic load: %d\n",
			priv->bt_traffic_load);
		अवरोध;
	पूर्ण

	mutex_lock(&priv->mutex);

	/*
	 * We can not send command to firmware जबतक scanning. When the scan
	 * complete we will schedule this work again. We करो check with mutex
	 * locked to prevent new scan request to arrive. We करो not check
	 * STATUS_SCANNING to aव्योम race when queue_work two बार from
	 * dअगरferent notअगरications, but quit and not perक्रमm any work at all.
	 */
	अगर (test_bit(STATUS_SCAN_HW, &priv->status))
		जाओ out;

	iwl_update_chain_flags(priv);

	अगर (smps_request != -1) अणु
		priv->current_ht_config.smps = smps_request;
		क्रम_each_context(priv, ctx) अणु
			अगर (ctx->vअगर && ctx->vअगर->type == NL80211_IFTYPE_STATION)
				ieee80211_request_smps(ctx->vअगर, smps_request);
		पूर्ण
	पूर्ण

	/*
	 * Dynamic PS poll related functionality. Adjust RSSI measurements अगर
	 * necessary.
	 */
	iwlagn_bt_coex_rssi_monitor(priv);
out:
	mutex_unlock(&priv->mutex);
पूर्ण

/*
 * If BT sco traffic, and RSSI monitor is enabled, move measurements to the
 * correct पूर्णांकerface or disable it अगर this is the last पूर्णांकerface to be
 * हटाओd.
 */
व्योम iwlagn_bt_coex_rssi_monitor(काष्ठा iwl_priv *priv)
अणु
	अगर (priv->bt_is_sco &&
	    priv->bt_traffic_load == IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS)
		iwlagn_bt_adjust_rssi_monitor(priv, true);
	अन्यथा
		iwlagn_bt_adjust_rssi_monitor(priv, false);
पूर्ण

अटल व्योम iwlagn_prपूर्णांक_uarपंचांगsg(काष्ठा iwl_priv *priv,
				काष्ठा iwl_bt_uart_msg *uart_msg)
अणु
	IWL_DEBUG_COEX(priv, "Message Type = 0x%X, SSN = 0x%X, "
			"Update Req = 0x%X\n",
		(BT_UART_MSG_FRAME1MSGTYPE_MSK & uart_msg->frame1) >>
			BT_UART_MSG_FRAME1MSGTYPE_POS,
		(BT_UART_MSG_FRAME1SSN_MSK & uart_msg->frame1) >>
			BT_UART_MSG_FRAME1SSN_POS,
		(BT_UART_MSG_FRAME1UPDATEREQ_MSK & uart_msg->frame1) >>
			BT_UART_MSG_FRAME1UPDATEREQ_POS);

	IWL_DEBUG_COEX(priv, "Open connections = 0x%X, Traffic load = 0x%X, "
			"Chl_SeqN = 0x%X, In band = 0x%X\n",
		(BT_UART_MSG_FRAME2OPENCONNECTIONS_MSK & uart_msg->frame2) >>
			BT_UART_MSG_FRAME2OPENCONNECTIONS_POS,
		(BT_UART_MSG_FRAME2TRAFFICLOAD_MSK & uart_msg->frame2) >>
			BT_UART_MSG_FRAME2TRAFFICLOAD_POS,
		(BT_UART_MSG_FRAME2CHLSEQN_MSK & uart_msg->frame2) >>
			BT_UART_MSG_FRAME2CHLSEQN_POS,
		(BT_UART_MSG_FRAME2INBAND_MSK & uart_msg->frame2) >>
			BT_UART_MSG_FRAME2INBAND_POS);

	IWL_DEBUG_COEX(priv, "SCO/eSCO = 0x%X, Sniff = 0x%X, A2DP = 0x%X, "
			"ACL = 0x%X, Master = 0x%X, OBEX = 0x%X\n",
		(BT_UART_MSG_FRAME3SCOESCO_MSK & uart_msg->frame3) >>
			BT_UART_MSG_FRAME3SCOESCO_POS,
		(BT_UART_MSG_FRAME3SNIFF_MSK & uart_msg->frame3) >>
			BT_UART_MSG_FRAME3SNIFF_POS,
		(BT_UART_MSG_FRAME3A2DP_MSK & uart_msg->frame3) >>
			BT_UART_MSG_FRAME3A2DP_POS,
		(BT_UART_MSG_FRAME3ACL_MSK & uart_msg->frame3) >>
			BT_UART_MSG_FRAME3ACL_POS,
		(BT_UART_MSG_FRAME3MASTER_MSK & uart_msg->frame3) >>
			BT_UART_MSG_FRAME3MASTER_POS,
		(BT_UART_MSG_FRAME3OBEX_MSK & uart_msg->frame3) >>
			BT_UART_MSG_FRAME3OBEX_POS);

	IWL_DEBUG_COEX(priv, "Idle duration = 0x%X\n",
		(BT_UART_MSG_FRAME4IDLEDURATION_MSK & uart_msg->frame4) >>
			BT_UART_MSG_FRAME4IDLEDURATION_POS);

	IWL_DEBUG_COEX(priv, "Tx Activity = 0x%X, Rx Activity = 0x%X, "
			"eSCO Retransmissions = 0x%X\n",
		(BT_UART_MSG_FRAME5TXACTIVITY_MSK & uart_msg->frame5) >>
			BT_UART_MSG_FRAME5TXACTIVITY_POS,
		(BT_UART_MSG_FRAME5RXACTIVITY_MSK & uart_msg->frame5) >>
			BT_UART_MSG_FRAME5RXACTIVITY_POS,
		(BT_UART_MSG_FRAME5ESCORETRANSMIT_MSK & uart_msg->frame5) >>
			BT_UART_MSG_FRAME5ESCORETRANSMIT_POS);

	IWL_DEBUG_COEX(priv, "Sniff Interval = 0x%X, Discoverable = 0x%X\n",
		(BT_UART_MSG_FRAME6SNIFFINTERVAL_MSK & uart_msg->frame6) >>
			BT_UART_MSG_FRAME6SNIFFINTERVAL_POS,
		(BT_UART_MSG_FRAME6DISCOVERABLE_MSK & uart_msg->frame6) >>
			BT_UART_MSG_FRAME6DISCOVERABLE_POS);

	IWL_DEBUG_COEX(priv, "Sniff Activity = 0x%X, Page = "
			"0x%X, Inquiry = 0x%X, Connectable = 0x%X\n",
		(BT_UART_MSG_FRAME7SNIFFACTIVITY_MSK & uart_msg->frame7) >>
			BT_UART_MSG_FRAME7SNIFFACTIVITY_POS,
		(BT_UART_MSG_FRAME7PAGE_MSK & uart_msg->frame7) >>
			BT_UART_MSG_FRAME7PAGE_POS,
		(BT_UART_MSG_FRAME7INQUIRY_MSK & uart_msg->frame7) >>
			BT_UART_MSG_FRAME7INQUIRY_POS,
		(BT_UART_MSG_FRAME7CONNECTABLE_MSK & uart_msg->frame7) >>
			BT_UART_MSG_FRAME7CONNECTABLE_POS);
पूर्ण

अटल bool iwlagn_set_समाप्त_msk(काष्ठा iwl_priv *priv,
				काष्ठा iwl_bt_uart_msg *uart_msg)
अणु
	bool need_update = false;
	u8 समाप्त_msk = IWL_BT_KILL_REDUCE;
	अटल स्थिर __le32 bt_समाप्त_ack_msg[3] = अणु
		IWLAGN_BT_KILL_ACK_MASK_DEFAULT,
		IWLAGN_BT_KILL_ACK_CTS_MASK_SCO,
		IWLAGN_BT_KILL_ACK_CTS_MASK_REDUCEपूर्ण;
	अटल स्थिर __le32 bt_समाप्त_cts_msg[3] = अणु
		IWLAGN_BT_KILL_CTS_MASK_DEFAULT,
		IWLAGN_BT_KILL_ACK_CTS_MASK_SCO,
		IWLAGN_BT_KILL_ACK_CTS_MASK_REDUCEपूर्ण;

	अगर (!priv->reduced_txघातer)
		समाप्त_msk = (BT_UART_MSG_FRAME3SCOESCO_MSK & uart_msg->frame3)
			? IWL_BT_KILL_OVERRIDE : IWL_BT_KILL_DEFAULT;
	अगर (priv->समाप्त_ack_mask != bt_समाप्त_ack_msg[समाप्त_msk] ||
	    priv->समाप्त_cts_mask != bt_समाप्त_cts_msg[समाप्त_msk]) अणु
		priv->bt_valid |= IWLAGN_BT_VALID_KILL_ACK_MASK;
		priv->समाप्त_ack_mask = bt_समाप्त_ack_msg[समाप्त_msk];
		priv->bt_valid |= IWLAGN_BT_VALID_KILL_CTS_MASK;
		priv->समाप्त_cts_mask = bt_समाप्त_cts_msg[समाप्त_msk];
		need_update = true;
	पूर्ण
	वापस need_update;
पूर्ण

/*
 * Upon RSSI changes, sends a bt config command with following changes
 *  1. enable/disable "reduced control frames tx घातer
 *  2. update the "kill)ack_mask" and "kill_cts_mask"
 *
 * If "reduced tx power" is enabled, uCode shall
 *  1. ACK/Back/CTS rate shall reduced to 6Mbps
 *  2. not use duplciate 20/40MHz mode
 */
अटल bool iwlagn_fill_txघातer_mode(काष्ठा iwl_priv *priv,
				काष्ठा iwl_bt_uart_msg *uart_msg)
अणु
	bool need_update = false;
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	पूर्णांक ave_rssi;

	अगर (!ctx->vअगर || (ctx->vअगर->type != NL80211_IFTYPE_STATION)) अणु
		IWL_DEBUG_INFO(priv, "BSS ctx not active or not in sta mode\n");
		वापस false;
	पूर्ण

	ave_rssi = ieee80211_ave_rssi(ctx->vअगर);
	अगर (!ave_rssi) अणु
		/* no rssi data, no changes to reduce tx घातer */
		IWL_DEBUG_COEX(priv, "no rssi data available\n");
		वापस need_update;
	पूर्ण
	अगर (!priv->reduced_txघातer &&
	    !iwl_is_associated(priv, IWL_RXON_CTX_PAN) &&
	    (ave_rssi > BT_ENABLE_REDUCED_TXPOWER_THRESHOLD) &&
	    (uart_msg->frame3 & (BT_UART_MSG_FRAME3ACL_MSK |
	    BT_UART_MSG_FRAME3OBEX_MSK)) &&
	    !(uart_msg->frame3 & (BT_UART_MSG_FRAME3SCOESCO_MSK |
	    BT_UART_MSG_FRAME3SNIFF_MSK | BT_UART_MSG_FRAME3A2DP_MSK))) अणु
		/* enabling reduced tx घातer */
		priv->reduced_txघातer = true;
		priv->bt_valid |= IWLAGN_BT_VALID_REDUCED_TX_PWR;
		need_update = true;
	पूर्ण अन्यथा अगर (priv->reduced_txघातer &&
		   (iwl_is_associated(priv, IWL_RXON_CTX_PAN) ||
		   (ave_rssi < BT_DISABLE_REDUCED_TXPOWER_THRESHOLD) ||
		   (uart_msg->frame3 & (BT_UART_MSG_FRAME3SCOESCO_MSK |
		   BT_UART_MSG_FRAME3SNIFF_MSK | BT_UART_MSG_FRAME3A2DP_MSK)) ||
		   !(uart_msg->frame3 & (BT_UART_MSG_FRAME3ACL_MSK |
		   BT_UART_MSG_FRAME3OBEX_MSK)))) अणु
		/* disable reduced tx घातer */
		priv->reduced_txघातer = false;
		priv->bt_valid |= IWLAGN_BT_VALID_REDUCED_TX_PWR;
		need_update = true;
	पूर्ण

	वापस need_update;
पूर्ण

अटल व्योम iwlagn_bt_coex_profile_notअगर(काष्ठा iwl_priv *priv,
					 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_bt_coex_profile_notअगर *coex = (व्योम *)pkt->data;
	काष्ठा iwl_bt_uart_msg *uart_msg = &coex->last_bt_uart_msg;

	अगर (priv->bt_enable_flag == IWLAGN_BT_FLAG_COEX_MODE_DISABLED) अणु
		/* bt coex disabled */
		वापस;
	पूर्ण

	IWL_DEBUG_COEX(priv, "BT Coex notification:\n");
	IWL_DEBUG_COEX(priv, "    status: %d\n", coex->bt_status);
	IWL_DEBUG_COEX(priv, "    traffic load: %d\n", coex->bt_traffic_load);
	IWL_DEBUG_COEX(priv, "    CI compliance: %d\n",
			coex->bt_ci_compliance);
	iwlagn_prपूर्णांक_uarपंचांगsg(priv, uart_msg);

	priv->last_bt_traffic_load = priv->bt_traffic_load;
	priv->bt_is_sco = iwlagn_bt_traffic_is_sco(uart_msg);

	अगर (priv->iw_mode != NL80211_IFTYPE_ADHOC) अणु
		अगर (priv->bt_status != coex->bt_status ||
		    priv->last_bt_traffic_load != coex->bt_traffic_load) अणु
			अगर (coex->bt_status) अणु
				/* BT on */
				अगर (!priv->bt_ch_announce)
					priv->bt_traffic_load =
						IWL_BT_COEX_TRAFFIC_LOAD_HIGH;
				अन्यथा
					priv->bt_traffic_load =
						coex->bt_traffic_load;
			पूर्ण अन्यथा अणु
				/* BT off */
				priv->bt_traffic_load =
					IWL_BT_COEX_TRAFFIC_LOAD_NONE;
			पूर्ण
			priv->bt_status = coex->bt_status;
			queue_work(priv->workqueue,
				   &priv->bt_traffic_change_work);
		पूर्ण
	पूर्ण

	/* schedule to send runसमय bt_config */
	/* check reduce घातer beक्रमe change ack/cts समाप्त mask */
	अगर (iwlagn_fill_txघातer_mode(priv, uart_msg) ||
	    iwlagn_set_समाप्त_msk(priv, uart_msg))
		queue_work(priv->workqueue, &priv->bt_runसमय_config);


	/* FIXME: based on notअगरication, adjust the prio_boost */

	priv->bt_ci_compliance = coex->bt_ci_compliance;
पूर्ण

व्योम iwlagn_bt_rx_handler_setup(काष्ठा iwl_priv *priv)
अणु
	priv->rx_handlers[REPLY_BT_COEX_PROखाता_NOTIF] =
		iwlagn_bt_coex_profile_notअगर;
पूर्ण

व्योम iwlagn_bt_setup_deferred_work(काष्ठा iwl_priv *priv)
अणु
	INIT_WORK(&priv->bt_traffic_change_work,
		  iwlagn_bt_traffic_change_work);
पूर्ण

व्योम iwlagn_bt_cancel_deferred_work(काष्ठा iwl_priv *priv)
अणु
	cancel_work_sync(&priv->bt_traffic_change_work);
पूर्ण

अटल bool is_single_rx_stream(काष्ठा iwl_priv *priv)
अणु
	वापस priv->current_ht_config.smps == IEEE80211_SMPS_STATIC ||
	       priv->current_ht_config.single_chain_sufficient;
पूर्ण

#घोषणा IWL_NUM_RX_CHAINS_MULTIPLE	3
#घोषणा IWL_NUM_RX_CHAINS_SINGLE	2
#घोषणा IWL_NUM_IDLE_CHAINS_DUAL	2
#घोषणा IWL_NUM_IDLE_CHAINS_SINGLE	1

/*
 * Determine how many receiver/antenna chains to use.
 *
 * More provides better reception via भागersity.  Fewer saves घातer
 * at the expense of throughput, but only when not in घातersave to
 * start with.
 *
 * MIMO (dual stream) requires at least 2, but works better with 3.
 * This करोes not determine *which* chains to use, just how many.
 */
अटल पूर्णांक iwl_get_active_rx_chain_count(काष्ठा iwl_priv *priv)
अणु
	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist &&
	    (priv->bt_full_concurrent ||
	     priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH)) अणु
		/*
		 * only use chain 'A' in bt high traffic load or
		 * full concurrency mode
		 */
		वापस IWL_NUM_RX_CHAINS_SINGLE;
	पूर्ण
	/* # of Rx chains to use when expecting MIMO. */
	अगर (is_single_rx_stream(priv))
		वापस IWL_NUM_RX_CHAINS_SINGLE;
	अन्यथा
		वापस IWL_NUM_RX_CHAINS_MULTIPLE;
पूर्ण

/*
 * When we are in घातer saving mode, unless device support spatial
 * multiplexing घातer save, use the active count क्रम rx chain count.
 */
अटल पूर्णांक iwl_get_idle_rx_chain_count(काष्ठा iwl_priv *priv, पूर्णांक active_cnt)
अणु
	/* # Rx chains when idling, depending on SMPS mode */
	चयन (priv->current_ht_config.smps) अणु
	हाल IEEE80211_SMPS_STATIC:
	हाल IEEE80211_SMPS_DYNAMIC:
		वापस IWL_NUM_IDLE_CHAINS_SINGLE;
	हाल IEEE80211_SMPS_AUTOMATIC:
	हाल IEEE80211_SMPS_OFF:
		वापस active_cnt;
	शेष:
		WARN(1, "invalid SMPS mode %d",
		     priv->current_ht_config.smps);
		वापस active_cnt;
	पूर्ण
पूर्ण

/* up to 4 chains */
अटल u8 iwl_count_chain_biपंचांगap(u32 chain_biपंचांगap)
अणु
	u8 res;
	res = (chain_biपंचांगap & BIT(0)) >> 0;
	res += (chain_biपंचांगap & BIT(1)) >> 1;
	res += (chain_biपंचांगap & BIT(2)) >> 2;
	res += (chain_biपंचांगap & BIT(3)) >> 3;
	वापस res;
पूर्ण

/*
 * iwlagn_set_rxon_chain - Set up Rx chain usage in "staging" RXON image
 *
 * Selects how many and which Rx receivers/antennas/chains to use.
 * This should not be used क्रम scan command ... it माला_दो data in wrong place.
 */
व्योम iwlagn_set_rxon_chain(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx)
अणु
	bool is_single = is_single_rx_stream(priv);
	bool is_cam = !test_bit(STATUS_POWER_PMI, &priv->status);
	u8 idle_rx_cnt, active_rx_cnt, valid_rx_cnt;
	u32 active_chains;
	u16 rx_chain;

	/* Tell uCode which antennas are actually connected.
	 * Beक्रमe first association, we assume all antennas are connected.
	 * Just after first association, iwl_chain_noise_calibration()
	 *    checks which antennas actually *are* connected. */
	अगर (priv->chain_noise_data.active_chains)
		active_chains = priv->chain_noise_data.active_chains;
	अन्यथा
		active_chains = priv->nvm_data->valid_rx_ant;

	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist &&
	    (priv->bt_full_concurrent ||
	     priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH)) अणु
		/*
		 * only use chain 'A' in bt high traffic load or
		 * full concurrency mode
		 */
		active_chains = first_antenna(active_chains);
	पूर्ण

	rx_chain = active_chains << RXON_RX_CHAIN_VALID_POS;

	/* How many receivers should we use? */
	active_rx_cnt = iwl_get_active_rx_chain_count(priv);
	idle_rx_cnt = iwl_get_idle_rx_chain_count(priv, active_rx_cnt);


	/* correct rx chain count according hw settings
	 * and chain noise calibration
	 */
	valid_rx_cnt = iwl_count_chain_biपंचांगap(active_chains);
	अगर (valid_rx_cnt < active_rx_cnt)
		active_rx_cnt = valid_rx_cnt;

	अगर (valid_rx_cnt < idle_rx_cnt)
		idle_rx_cnt = valid_rx_cnt;

	rx_chain |= active_rx_cnt << RXON_RX_CHAIN_MIMO_CNT_POS;
	rx_chain |= idle_rx_cnt  << RXON_RX_CHAIN_CNT_POS;

	ctx->staging.rx_chain = cpu_to_le16(rx_chain);

	अगर (!is_single && (active_rx_cnt >= IWL_NUM_RX_CHAINS_SINGLE) && is_cam)
		ctx->staging.rx_chain |= RXON_RX_CHAIN_MIMO_FORCE_MSK;
	अन्यथा
		ctx->staging.rx_chain &= ~RXON_RX_CHAIN_MIMO_FORCE_MSK;

	IWL_DEBUG_ASSOC(priv, "rx_chain=0x%X active=%d idle=%d\n",
			ctx->staging.rx_chain,
			active_rx_cnt, idle_rx_cnt);

	WARN_ON(active_rx_cnt == 0 || idle_rx_cnt == 0 ||
		active_rx_cnt < idle_rx_cnt);
पूर्ण

u8 iwl_toggle_tx_ant(काष्ठा iwl_priv *priv, u8 ant, u8 valid)
अणु
	पूर्णांक i;
	u8 ind = ant;

	अगर (priv->band == NL80211_BAND_2GHZ &&
	    priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH)
		वापस 0;

	क्रम (i = 0; i < RATE_ANT_NUM - 1; i++) अणु
		ind = (ind + 1) < RATE_ANT_NUM ?  ind + 1 : 0;
		अगर (valid & BIT(ind))
			वापस ind;
	पूर्ण
	वापस ant;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम iwlagn_convert_p1k(u16 *p1k, __le16 *out)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IWLAGN_P1K_SIZE; i++)
		out[i] = cpu_to_le16(p1k[i]);
पूर्ण

काष्ठा wowlan_key_data अणु
	काष्ठा iwl_rxon_context *ctx;
	काष्ठा iwlagn_wowlan_rsc_tsc_params_cmd *rsc_tsc;
	काष्ठा iwlagn_wowlan_tkip_params_cmd *tkip;
	स्थिर u8 *bssid;
	bool error, use_rsc_tsc, use_tkip;
पूर्ण;


अटल व्योम iwlagn_wowlan_program_keys(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा ieee80211_key_conf *key,
			       व्योम *_data)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा wowlan_key_data *data = _data;
	काष्ठा iwl_rxon_context *ctx = data->ctx;
	काष्ठा aes_sc *aes_sc, *aes_tx_sc = शून्य;
	काष्ठा tkip_sc *tkip_sc, *tkip_tx_sc = शून्य;
	काष्ठा iwlagn_p1k_cache *rx_p1ks;
	u8 *rx_mic_key;
	काष्ठा ieee80211_key_seq seq;
	u32 cur_rx_iv32 = 0;
	u16 p1k[IWLAGN_P1K_SIZE];
	पूर्णांक ret, i;

	mutex_lock(&priv->mutex);

	अगर ((key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	     key->cipher == WLAN_CIPHER_SUITE_WEP104) &&
	     !sta && !ctx->key_mapping_keys)
		ret = iwl_set_शेष_wep_key(priv, ctx, key);
	अन्यथा
		ret = iwl_set_dynamic_key(priv, ctx, key, sta);

	अगर (ret) अणु
		IWL_ERR(priv, "Error setting key during suspend!\n");
		data->error = true;
	पूर्ण

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (sta) अणु
			u64 pn64;

			tkip_sc = data->rsc_tsc->all_tsc_rsc.tkip.unicast_rsc;
			tkip_tx_sc = &data->rsc_tsc->all_tsc_rsc.tkip.tsc;

			rx_p1ks = data->tkip->rx_uni;

			pn64 = atomic64_पढ़ो(&key->tx_pn);
			tkip_tx_sc->iv16 = cpu_to_le16(TKIP_PN_TO_IV16(pn64));
			tkip_tx_sc->iv32 = cpu_to_le32(TKIP_PN_TO_IV32(pn64));

			ieee80211_get_tkip_p1k_iv(key, seq.tkip.iv32, p1k);
			iwlagn_convert_p1k(p1k, data->tkip->tx.p1k);

			स_नकल(data->tkip->mic_keys.tx,
			       &key->key[NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY],
			       IWLAGN_MIC_KEY_SIZE);

			rx_mic_key = data->tkip->mic_keys.rx_unicast;
		पूर्ण अन्यथा अणु
			tkip_sc =
				data->rsc_tsc->all_tsc_rsc.tkip.multicast_rsc;
			rx_p1ks = data->tkip->rx_multi;
			rx_mic_key = data->tkip->mic_keys.rx_mcast;
		पूर्ण

		/*
		 * For non-QoS this relies on the fact that both the uCode and
		 * mac80211 use TID 0 (as they need to to aव्योम replay attacks)
		 * क्रम checking the IV in the frames.
		 */
		क्रम (i = 0; i < IWLAGN_NUM_RSC; i++) अणु
			ieee80211_get_key_rx_seq(key, i, &seq);
			tkip_sc[i].iv16 = cpu_to_le16(seq.tkip.iv16);
			tkip_sc[i].iv32 = cpu_to_le32(seq.tkip.iv32);
			/* wrapping isn't allowed, AP must rekey */
			अगर (seq.tkip.iv32 > cur_rx_iv32)
				cur_rx_iv32 = seq.tkip.iv32;
		पूर्ण

		ieee80211_get_tkip_rx_p1k(key, data->bssid, cur_rx_iv32, p1k);
		iwlagn_convert_p1k(p1k, rx_p1ks[0].p1k);
		ieee80211_get_tkip_rx_p1k(key, data->bssid,
					  cur_rx_iv32 + 1, p1k);
		iwlagn_convert_p1k(p1k, rx_p1ks[1].p1k);

		स_नकल(rx_mic_key,
		       &key->key[NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY],
		       IWLAGN_MIC_KEY_SIZE);

		data->use_tkip = true;
		data->use_rsc_tsc = true;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		अगर (sta) अणु
			u64 pn64;

			aes_sc = data->rsc_tsc->all_tsc_rsc.aes.unicast_rsc;
			aes_tx_sc = &data->rsc_tsc->all_tsc_rsc.aes.tsc;

			pn64 = atomic64_पढ़ो(&key->tx_pn);
			aes_tx_sc->pn = cpu_to_le64(pn64);
		पूर्ण अन्यथा
			aes_sc = data->rsc_tsc->all_tsc_rsc.aes.multicast_rsc;

		/*
		 * For non-QoS this relies on the fact that both the uCode and
		 * mac80211 use TID 0 क्रम checking the IV in the frames.
		 */
		क्रम (i = 0; i < IWLAGN_NUM_RSC; i++) अणु
			u8 *pn = seq.ccmp.pn;

			ieee80211_get_key_rx_seq(key, i, &seq);
			aes_sc[i].pn = cpu_to_le64(
					(u64)pn[5] |
					((u64)pn[4] << 8) |
					((u64)pn[3] << 16) |
					((u64)pn[2] << 24) |
					((u64)pn[1] << 32) |
					((u64)pn[0] << 40));
		पूर्ण
		data->use_rsc_tsc = true;
		अवरोध;
	पूर्ण

	mutex_unlock(&priv->mutex);
पूर्ण

पूर्णांक iwlagn_send_patterns(काष्ठा iwl_priv *priv,
			काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा iwlagn_wowlan_patterns_cmd *pattern_cmd;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_WOWLAN_PATTERNS,
		.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
	पूर्ण;
	पूर्णांक i, err;

	अगर (!wowlan->n_patterns)
		वापस 0;

	cmd.len[0] = काष्ठा_size(pattern_cmd, patterns, wowlan->n_patterns);

	pattern_cmd = kदो_स्मृति(cmd.len[0], GFP_KERNEL);
	अगर (!pattern_cmd)
		वापस -ENOMEM;

	pattern_cmd->n_patterns = cpu_to_le32(wowlan->n_patterns);

	क्रम (i = 0; i < wowlan->n_patterns; i++) अणु
		पूर्णांक mask_len = DIV_ROUND_UP(wowlan->patterns[i].pattern_len, 8);

		स_नकल(&pattern_cmd->patterns[i].mask,
			wowlan->patterns[i].mask, mask_len);
		स_नकल(&pattern_cmd->patterns[i].pattern,
			wowlan->patterns[i].pattern,
			wowlan->patterns[i].pattern_len);
		pattern_cmd->patterns[i].mask_size = mask_len;
		pattern_cmd->patterns[i].pattern_size =
			wowlan->patterns[i].pattern_len;
	पूर्ण

	cmd.data[0] = pattern_cmd;
	err = iwl_dvm_send_cmd(priv, &cmd);
	kमुक्त(pattern_cmd);
	वापस err;
पूर्ण

पूर्णांक iwlagn_suspend(काष्ठा iwl_priv *priv, काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा iwlagn_wowlan_wakeup_filter_cmd wakeup_filter_cmd;
	काष्ठा iwl_rxon_cmd rxon;
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	काष्ठा iwlagn_wowlan_kek_kck_material_cmd kek_kck_cmd;
	काष्ठा iwlagn_wowlan_tkip_params_cmd tkip_cmd = अणुपूर्ण;
	काष्ठा iwlagn_d3_config_cmd d3_cfg_cmd = अणु
		/*
		 * Program the minimum sleep समय to 10 seconds, as many
		 * platक्रमms have issues processing a wakeup संकेत जबतक
		 * still being in the process of suspending.
		 */
		.min_sleep_समय = cpu_to_le32(10 * 1000 * 1000),
	पूर्ण;
	काष्ठा wowlan_key_data key_data = अणु
		.ctx = ctx,
		.bssid = ctx->active.bssid_addr,
		.use_rsc_tsc = false,
		.tkip = &tkip_cmd,
		.use_tkip = false,
	पूर्ण;
	पूर्णांक ret, i;
	u16 seq;

	key_data.rsc_tsc = kzalloc(माप(*key_data.rsc_tsc), GFP_KERNEL);
	अगर (!key_data.rsc_tsc)
		वापस -ENOMEM;

	स_रखो(&wakeup_filter_cmd, 0, माप(wakeup_filter_cmd));

	/*
	 * We know the last used seqno, and the uCode expects to know that
	 * one, it will increment beक्रमe TX.
	 */
	seq = le16_to_cpu(priv->last_seq_ctl) & IEEE80211_SCTL_SEQ;
	wakeup_filter_cmd.non_qos_seq = cpu_to_le16(seq);

	/*
	 * For QoS counters, we store the one to use next, so subtract 0x10
	 * since the uCode will add 0x10 beक्रमe using the value.
	 */
	क्रम (i = 0; i < IWL_MAX_TID_COUNT; i++) अणु
		seq = priv->tid_data[IWL_AP_ID][i].seq_number;
		seq -= 0x10;
		wakeup_filter_cmd.qos_seq[i] = cpu_to_le16(seq);
	पूर्ण

	अगर (wowlan->disconnect)
		wakeup_filter_cmd.enabled |=
			cpu_to_le32(IWLAGN_WOWLAN_WAKEUP_BEACON_MISS |
				    IWLAGN_WOWLAN_WAKEUP_LINK_CHANGE);
	अगर (wowlan->magic_pkt)
		wakeup_filter_cmd.enabled |=
			cpu_to_le32(IWLAGN_WOWLAN_WAKEUP_MAGIC_PACKET);
	अगर (wowlan->gtk_rekey_failure)
		wakeup_filter_cmd.enabled |=
			cpu_to_le32(IWLAGN_WOWLAN_WAKEUP_GTK_REKEY_FAIL);
	अगर (wowlan->eap_identity_req)
		wakeup_filter_cmd.enabled |=
			cpu_to_le32(IWLAGN_WOWLAN_WAKEUP_EAP_IDENT_REQ);
	अगर (wowlan->four_way_handshake)
		wakeup_filter_cmd.enabled |=
			cpu_to_le32(IWLAGN_WOWLAN_WAKEUP_4WAY_HANDSHAKE);
	अगर (wowlan->n_patterns)
		wakeup_filter_cmd.enabled |=
			cpu_to_le32(IWLAGN_WOWLAN_WAKEUP_PATTERN_MATCH);

	अगर (wowlan->rfसमाप्त_release)
		d3_cfg_cmd.wakeup_flags |=
			cpu_to_le32(IWLAGN_D3_WAKEUP_RFKILL);

	iwl_scan_cancel_समयout(priv, 200);

	स_नकल(&rxon, &ctx->active, माप(rxon));

	priv->ucode_loaded = false;
	iwl_trans_stop_device(priv->trans);
	ret = iwl_trans_start_hw(priv->trans);
	अगर (ret)
		जाओ out;

	priv->wowlan = true;

	ret = iwl_load_ucode_रुको_alive(priv, IWL_UCODE_WOWLAN);
	अगर (ret)
		जाओ out;

	/* now configure WoWLAN ucode */
	ret = iwl_alive_start(priv);
	अगर (ret)
		जाओ out;

	स_नकल(&ctx->staging, &rxon, माप(rxon));
	ret = iwlagn_commit_rxon(priv, ctx);
	अगर (ret)
		जाओ out;

	ret = iwl_घातer_update_mode(priv, true);
	अगर (ret)
		जाओ out;

	अगर (!iwlwअगरi_mod_params.swcrypto) अणु
		/* mark all keys clear */
		priv->ucode_key_table = 0;
		ctx->key_mapping_keys = 0;

		/*
		 * This needs to be unlocked due to lock ordering
		 * स्थिरraपूर्णांकs. Since we're in the suspend path
		 * that isn't really a problem though.
		 */
		mutex_unlock(&priv->mutex);
		ieee80211_iter_keys(priv->hw, ctx->vअगर,
				    iwlagn_wowlan_program_keys,
				    &key_data);
		mutex_lock(&priv->mutex);
		अगर (key_data.error) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण

		अगर (key_data.use_rsc_tsc) अणु
			काष्ठा iwl_host_cmd rsc_tsc_cmd = अणु
				.id = REPLY_WOWLAN_TSC_RSC_PARAMS,
				.data[0] = key_data.rsc_tsc,
				.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
				.len[0] = माप(*key_data.rsc_tsc),
			पूर्ण;

			ret = iwl_dvm_send_cmd(priv, &rsc_tsc_cmd);
			अगर (ret)
				जाओ out;
		पूर्ण

		अगर (key_data.use_tkip) अणु
			ret = iwl_dvm_send_cmd_pdu(priv,
						 REPLY_WOWLAN_TKIP_PARAMS,
						 0, माप(tkip_cmd),
						 &tkip_cmd);
			अगर (ret)
				जाओ out;
		पूर्ण

		अगर (priv->have_rekey_data) अणु
			स_रखो(&kek_kck_cmd, 0, माप(kek_kck_cmd));
			स_नकल(kek_kck_cmd.kck, priv->kck, NL80211_KCK_LEN);
			kek_kck_cmd.kck_len = cpu_to_le16(NL80211_KCK_LEN);
			स_नकल(kek_kck_cmd.kek, priv->kek, NL80211_KEK_LEN);
			kek_kck_cmd.kek_len = cpu_to_le16(NL80211_KEK_LEN);
			kek_kck_cmd.replay_ctr = priv->replay_ctr;

			ret = iwl_dvm_send_cmd_pdu(priv,
						 REPLY_WOWLAN_KEK_KCK_MATERIAL,
						 0, माप(kek_kck_cmd),
						 &kek_kck_cmd);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

	ret = iwl_dvm_send_cmd_pdu(priv, REPLY_D3_CONFIG, 0,
				     माप(d3_cfg_cmd), &d3_cfg_cmd);
	अगर (ret)
		जाओ out;

	ret = iwl_dvm_send_cmd_pdu(priv, REPLY_WOWLAN_WAKEUP_FILTER,
				 0, माप(wakeup_filter_cmd),
				 &wakeup_filter_cmd);
	अगर (ret)
		जाओ out;

	ret = iwlagn_send_patterns(priv, wowlan);
 out:
	kमुक्त(key_data.rsc_tsc);
	वापस ret;
पूर्ण
#पूर्ण_अगर

पूर्णांक iwl_dvm_send_cmd(काष्ठा iwl_priv *priv, काष्ठा iwl_host_cmd *cmd)
अणु
	अगर (iwl_is_rfसमाप्त(priv) || iwl_is_ctसमाप्त(priv)) अणु
		IWL_WARN(priv, "Not sending command - %s KILL\n",
			 iwl_is_rfसमाप्त(priv) ? "RF" : "CT");
		वापस -EIO;
	पूर्ण

	अगर (test_bit(STATUS_FW_ERROR, &priv->status)) अणु
		IWL_ERR(priv, "Command %s failed: FW Error\n",
			iwl_get_cmd_string(priv->trans, cmd->id));
		वापस -EIO;
	पूर्ण

	/*
	 * This can happen upon FW ASSERT: we clear the STATUS_FW_ERROR flag
	 * in iwl_करोwn but cancel the workers only later.
	 */
	अगर (!priv->ucode_loaded) अणु
		IWL_ERR(priv, "Fw not loaded - dropping CMD: %x\n", cmd->id);
		वापस -EIO;
	पूर्ण

	/*
	 * Synchronous commands from this op-mode must hold
	 * the mutex, this ensures we करोn't try to send two
	 * (or more) synchronous commands at a समय.
	 */
	अगर (!(cmd->flags & CMD_ASYNC))
		lockdep_निश्चित_held(&priv->mutex);

	वापस iwl_trans_send_cmd(priv->trans, cmd);
पूर्ण

पूर्णांक iwl_dvm_send_cmd_pdu(काष्ठा iwl_priv *priv, u8 id,
			 u32 flags, u16 len, स्थिर व्योम *data)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.id = id,
		.len = अणु len, पूर्ण,
		.data = अणु data, पूर्ण,
		.flags = flags,
	पूर्ण;

	वापस iwl_dvm_send_cmd(priv, &cmd);
पूर्ण
