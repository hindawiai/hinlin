<शैली गुरु>
/*
 * NXP Wireless LAN device driver: station command response handling
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
#समावेश "11ac.h"


/*
 * This function handles the command response error हाल.
 *
 * For scan response error, the function cancels all the pending
 * scan commands and generates an event to inक्रमm the applications
 * of the scan completion.
 *
 * For Power Save command failure, we करो not retry enter PS
 * command in हाल of Ad-hoc mode.
 *
 * For all other response errors, the current command buffer is मुक्तd
 * and वापसed to the मुक्त command queue.
 */
अटल व्योम
mwअगरiex_process_cmdresp_error(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11_ps_mode_enh *pm;

	mwअगरiex_dbg(adapter, ERROR,
		    "CMD_RESP: cmd %#x error, result=%#x\n",
		    resp->command, resp->result);

	अगर (adapter->curr_cmd->रुको_q_enabled)
		adapter->cmd_रुको_q.status = -1;

	चयन (le16_to_cpu(resp->command)) अणु
	हाल HostCmd_CMD_802_11_PS_MODE_ENH:
		pm = &resp->params.psmode_enh;
		mwअगरiex_dbg(adapter, ERROR,
			    "PS_MODE_ENH cmd failed: result=0x%x action=0x%X\n",
			    resp->result, le16_to_cpu(pm->action));
		/* We करो not re-try enter-ps command in ad-hoc mode. */
		अगर (le16_to_cpu(pm->action) == EN_AUTO_PS &&
		    (le16_to_cpu(pm->params.ps_biपंचांगap) & BITMAP_STA_PS) &&
		    priv->bss_mode == NL80211_IFTYPE_ADHOC)
			adapter->ps_mode = MWIFIEX_802_11_POWER_MODE_CAM;

		अवरोध;
	हाल HostCmd_CMD_802_11_SCAN:
	हाल HostCmd_CMD_802_11_SCAN_EXT:
		mwअगरiex_cancel_scan(adapter);
		अवरोध;

	हाल HostCmd_CMD_MAC_CONTROL:
		अवरोध;

	हाल HostCmd_CMD_SDIO_SP_RX_AGGR_CFG:
		mwअगरiex_dbg(adapter, MSG,
			    "SDIO RX single-port aggregation Not support\n");
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	/* Handling errors here */
	mwअगरiex_recycle_cmd_node(adapter, adapter->curr_cmd);

	spin_lock_bh(&adapter->mwअगरiex_cmd_lock);
	adapter->curr_cmd = शून्य;
	spin_unlock_bh(&adapter->mwअगरiex_cmd_lock);
पूर्ण

/*
 * This function handles the command response of get RSSI info.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and saving the following parameters in driver -
 *      - Last data and beacon RSSI value
 *      - Average data and beacon RSSI value
 *      - Last data and beacon NF value
 *      - Average data and beacon NF value
 *
 * The parameters are send to the application as well, aदीर्घ with
 * calculated SNR values.
 */
अटल पूर्णांक mwअगरiex_ret_802_11_rssi_info(काष्ठा mwअगरiex_निजी *priv,
					काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_802_11_rssi_info_rsp *rssi_info_rsp =
						&resp->params.rssi_info_rsp;
	काष्ठा mwअगरiex_ds_misc_subsc_evt *subsc_evt =
						&priv->async_subsc_evt_storage;

	priv->data_rssi_last = le16_to_cpu(rssi_info_rsp->data_rssi_last);
	priv->data_nf_last = le16_to_cpu(rssi_info_rsp->data_nf_last);

	priv->data_rssi_avg = le16_to_cpu(rssi_info_rsp->data_rssi_avg);
	priv->data_nf_avg = le16_to_cpu(rssi_info_rsp->data_nf_avg);

	priv->bcn_rssi_last = le16_to_cpu(rssi_info_rsp->bcn_rssi_last);
	priv->bcn_nf_last = le16_to_cpu(rssi_info_rsp->bcn_nf_last);

	priv->bcn_rssi_avg = le16_to_cpu(rssi_info_rsp->bcn_rssi_avg);
	priv->bcn_nf_avg = le16_to_cpu(rssi_info_rsp->bcn_nf_avg);

	अगर (priv->subsc_evt_rssi_state == EVENT_HANDLED)
		वापस 0;

	स_रखो(subsc_evt, 0x00, माप(काष्ठा mwअगरiex_ds_misc_subsc_evt));

	/* Resubscribe low and high rssi events with new thresholds */
	subsc_evt->events = BITMASK_BCN_RSSI_LOW | BITMASK_BCN_RSSI_HIGH;
	subsc_evt->action = HostCmd_ACT_BITWISE_SET;
	अगर (priv->subsc_evt_rssi_state == RSSI_LOW_RECVD) अणु
		subsc_evt->bcn_l_rssi_cfg.असल_value = असल(priv->bcn_rssi_avg -
				priv->cqm_rssi_hyst);
		subsc_evt->bcn_h_rssi_cfg.असल_value = असल(priv->cqm_rssi_thold);
	पूर्ण अन्यथा अगर (priv->subsc_evt_rssi_state == RSSI_HIGH_RECVD) अणु
		subsc_evt->bcn_l_rssi_cfg.असल_value = असल(priv->cqm_rssi_thold);
		subsc_evt->bcn_h_rssi_cfg.असल_value = असल(priv->bcn_rssi_avg +
				priv->cqm_rssi_hyst);
	पूर्ण
	subsc_evt->bcn_l_rssi_cfg.evt_freq = 1;
	subsc_evt->bcn_h_rssi_cfg.evt_freq = 1;

	priv->subsc_evt_rssi_state = EVENT_HANDLED;

	mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SUBSCRIBE_EVENT,
			 0, 0, subsc_evt, false);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of set/get SNMP
 * MIB parameters.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and saving the parameter in driver.
 *
 * The following parameters are supported -
 *      - Fragmentation threshold
 *      - RTS threshold
 *      - Short retry limit
 */
अटल पूर्णांक mwअगरiex_ret_802_11_snmp_mib(काष्ठा mwअगरiex_निजी *priv,
				       काष्ठा host_cmd_ds_command *resp,
				       u32 *data_buf)
अणु
	काष्ठा host_cmd_ds_802_11_snmp_mib *smib = &resp->params.smib;
	u16 oid = le16_to_cpu(smib->oid);
	u16 query_type = le16_to_cpu(smib->query_type);
	u32 ul_temp;

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: SNMP_RESP: oid value = %#x,\t"
		    "query_type = %#x, buf size = %#x\n",
		    oid, query_type, le16_to_cpu(smib->buf_size));
	अगर (query_type == HostCmd_ACT_GEN_GET) अणु
		ul_temp = get_unaligned_le16(smib->value);
		अगर (data_buf)
			*data_buf = ul_temp;
		चयन (oid) अणु
		हाल FRAG_THRESH_I:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: SNMP_RESP: FragThsd =%u\n",
				    ul_temp);
			अवरोध;
		हाल RTS_THRESH_I:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: SNMP_RESP: RTSThsd =%u\n",
				    ul_temp);
			अवरोध;
		हाल SHORT_RETRY_LIM_I:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: SNMP_RESP: TxRetryCount=%u\n",
				    ul_temp);
			अवरोध;
		हाल DTIM_PERIOD_I:
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: SNMP_RESP: DTIM period=%u\n",
				    ul_temp);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function handles the command response of get log request
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and sending the received parameters to application.
 */
अटल पूर्णांक mwअगरiex_ret_get_log(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command *resp,
			       काष्ठा mwअगरiex_ds_get_stats *stats)
अणु
	काष्ठा host_cmd_ds_802_11_get_log *get_log =
		&resp->params.get_log;

	अगर (stats) अणु
		stats->mcast_tx_frame = le32_to_cpu(get_log->mcast_tx_frame);
		stats->failed = le32_to_cpu(get_log->failed);
		stats->retry = le32_to_cpu(get_log->retry);
		stats->multi_retry = le32_to_cpu(get_log->multi_retry);
		stats->frame_dup = le32_to_cpu(get_log->frame_dup);
		stats->rts_success = le32_to_cpu(get_log->rts_success);
		stats->rts_failure = le32_to_cpu(get_log->rts_failure);
		stats->ack_failure = le32_to_cpu(get_log->ack_failure);
		stats->rx_frag = le32_to_cpu(get_log->rx_frag);
		stats->mcast_rx_frame = le32_to_cpu(get_log->mcast_rx_frame);
		stats->fcs_error = le32_to_cpu(get_log->fcs_error);
		stats->tx_frame = le32_to_cpu(get_log->tx_frame);
		stats->wep_icv_error[0] =
			le32_to_cpu(get_log->wep_icv_err_cnt[0]);
		stats->wep_icv_error[1] =
			le32_to_cpu(get_log->wep_icv_err_cnt[1]);
		stats->wep_icv_error[2] =
			le32_to_cpu(get_log->wep_icv_err_cnt[2]);
		stats->wep_icv_error[3] =
			le32_to_cpu(get_log->wep_icv_err_cnt[3]);
		stats->bcn_rcv_cnt = le32_to_cpu(get_log->bcn_rcv_cnt);
		stats->bcn_miss_cnt = le32_to_cpu(get_log->bcn_miss_cnt);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function handles the command response of set/get Tx rate
 * configurations.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and saving the following parameters in driver -
 *      - DSSS rate biपंचांगap
 *      - OFDM rate biपंचांगap
 *      - HT MCS rate biपंचांगaps
 *
 * Based on the new rate biपंचांगaps, the function re-evaluates अगर
 * स्वतः data rate has been activated. If not, it sends another
 * query to the firmware to get the current Tx data rate.
 */
अटल पूर्णांक mwअगरiex_ret_tx_rate_cfg(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_tx_rate_cfg *rate_cfg = &resp->params.tx_rate_cfg;
	काष्ठा mwअगरiex_rate_scope *rate_scope;
	काष्ठा mwअगरiex_ie_types_header *head;
	u16 tlv, tlv_buf_len, tlv_buf_left;
	u8 *tlv_buf;
	u32 i;

	tlv_buf = ((u8 *)rate_cfg) + माप(काष्ठा host_cmd_ds_tx_rate_cfg);
	tlv_buf_left = le16_to_cpu(resp->size) - S_DS_GEN - माप(*rate_cfg);

	जबतक (tlv_buf_left >= माप(*head)) अणु
		head = (काष्ठा mwअगरiex_ie_types_header *)tlv_buf;
		tlv = le16_to_cpu(head->type);
		tlv_buf_len = le16_to_cpu(head->len);

		अगर (tlv_buf_left < (माप(*head) + tlv_buf_len))
			अवरोध;

		चयन (tlv) अणु
		हाल TLV_TYPE_RATE_SCOPE:
			rate_scope = (काष्ठा mwअगरiex_rate_scope *) tlv_buf;
			priv->biपंचांगap_rates[0] =
				le16_to_cpu(rate_scope->hr_dsss_rate_biपंचांगap);
			priv->biपंचांगap_rates[1] =
				le16_to_cpu(rate_scope->ofdm_rate_biपंचांगap);
			क्रम (i = 0;
			     i < ARRAY_SIZE(rate_scope->ht_mcs_rate_biपंचांगap);
			     i++)
				priv->biपंचांगap_rates[2 + i] =
					le16_to_cpu(rate_scope->
						    ht_mcs_rate_biपंचांगap[i]);

			अगर (priv->adapter->fw_api_ver == MWIFIEX_FW_V15) अणु
				क्रम (i = 0; i < ARRAY_SIZE(rate_scope->
							   vht_mcs_rate_biपंचांगap);
				     i++)
					priv->biपंचांगap_rates[10 + i] =
					    le16_to_cpu(rate_scope->
							vht_mcs_rate_biपंचांगap[i]);
			पूर्ण
			अवरोध;
			/* Add RATE_DROP tlv here */
		पूर्ण

		tlv_buf += (माप(*head) + tlv_buf_len);
		tlv_buf_left -= (माप(*head) + tlv_buf_len);
	पूर्ण

	priv->is_data_rate_स्वतः = mwअगरiex_is_rate_स्वतः(priv);

	अगर (priv->is_data_rate_स्वतः)
		priv->data_rate = 0;
	अन्यथा
		वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_TX_RATE_QUERY,
					HostCmd_ACT_GEN_GET, 0, शून्य, false);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of get Tx घातer level.
 *
 * Handling includes saving the maximum and minimum Tx घातer levels
 * in driver, as well as sending the values to user.
 */
अटल पूर्णांक mwअगरiex_get_घातer_level(काष्ठा mwअगरiex_निजी *priv, व्योम *data_buf)
अणु
	पूर्णांक length, max_घातer = -1, min_घातer = -1;
	काष्ठा mwअगरiex_types_घातer_group *pg_tlv_hdr;
	काष्ठा mwअगरiex_घातer_group *pg;

	अगर (!data_buf)
		वापस -1;

	pg_tlv_hdr = (काष्ठा mwअगरiex_types_घातer_group *)((u8 *)data_buf);
	pg = (काष्ठा mwअगरiex_घातer_group *)
		((u8 *) pg_tlv_hdr + माप(काष्ठा mwअगरiex_types_घातer_group));
	length = le16_to_cpu(pg_tlv_hdr->length);

	/* At least one काष्ठाure required to update घातer */
	अगर (length < माप(काष्ठा mwअगरiex_घातer_group))
		वापस 0;

	max_घातer = pg->घातer_max;
	min_घातer = pg->घातer_min;
	length -= माप(काष्ठा mwअगरiex_घातer_group);

	जबतक (length >= माप(काष्ठा mwअगरiex_घातer_group)) अणु
		pg++;
		अगर (max_घातer < pg->घातer_max)
			max_घातer = pg->घातer_max;

		अगर (min_घातer > pg->घातer_min)
			min_घातer = pg->घातer_min;

		length -= माप(काष्ठा mwअगरiex_घातer_group);
	पूर्ण
	priv->min_tx_घातer_level = (u8) min_घातer;
	priv->max_tx_घातer_level = (u8) max_घातer;

	वापस 0;
पूर्ण

/*
 * This function handles the command response of set/get Tx घातer
 * configurations.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and saving the current Tx घातer level in driver.
 */
अटल पूर्णांक mwअगरiex_ret_tx_घातer_cfg(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_txpwr_cfg *txp_cfg = &resp->params.txp_cfg;
	काष्ठा mwअगरiex_types_घातer_group *pg_tlv_hdr;
	काष्ठा mwअगरiex_घातer_group *pg;
	u16 action = le16_to_cpu(txp_cfg->action);
	u16 tlv_buf_left;

	pg_tlv_hdr = (काष्ठा mwअगरiex_types_घातer_group *)
		((u8 *)txp_cfg +
		 माप(काष्ठा host_cmd_ds_txpwr_cfg));

	pg = (काष्ठा mwअगरiex_घातer_group *)
		((u8 *)pg_tlv_hdr +
		 माप(काष्ठा mwअगरiex_types_घातer_group));

	tlv_buf_left = le16_to_cpu(resp->size) - S_DS_GEN - माप(*txp_cfg);
	अगर (tlv_buf_left <
			le16_to_cpu(pg_tlv_hdr->length) + माप(*pg_tlv_hdr))
		वापस 0;

	चयन (action) अणु
	हाल HostCmd_ACT_GEN_GET:
		अगर (adapter->hw_status == MWIFIEX_HW_STATUS_INITIALIZING)
			mwअगरiex_get_घातer_level(priv, pg_tlv_hdr);

		priv->tx_घातer_level = (u16) pg->घातer_min;
		अवरोध;

	हाल HostCmd_ACT_GEN_SET:
		अगर (!le32_to_cpu(txp_cfg->mode))
			अवरोध;

		अगर (pg->घातer_max == pg->घातer_min)
			priv->tx_घातer_level = (u16) pg->घातer_min;
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR,
			    "CMD_RESP: unknown cmd action %d\n",
			    action);
		वापस 0;
	पूर्ण
	mwअगरiex_dbg(adapter, INFO,
		    "info: Current TxPower Level = %d, Max Power=%d, Min Power=%d\n",
		    priv->tx_घातer_level, priv->max_tx_घातer_level,
		    priv->min_tx_घातer_level);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of get RF Tx घातer.
 */
अटल पूर्णांक mwअगरiex_ret_rf_tx_घातer(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_rf_tx_pwr *txp = &resp->params.txp;
	u16 action = le16_to_cpu(txp->action);

	priv->tx_घातer_level = le16_to_cpu(txp->cur_level);

	अगर (action == HostCmd_ACT_GEN_GET) अणु
		priv->max_tx_घातer_level = txp->max_घातer;
		priv->min_tx_घातer_level = txp->min_घातer;
	पूर्ण

	mwअगरiex_dbg(priv->adapter, INFO,
		    "Current TxPower Level=%d, Max Power=%d, Min Power=%d\n",
		    priv->tx_घातer_level, priv->max_tx_घातer_level,
		    priv->min_tx_घातer_level);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of set rf antenna
 */
अटल पूर्णांक mwअगरiex_ret_rf_antenna(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_rf_ant_mimo *ant_mimo = &resp->params.ant_mimo;
	काष्ठा host_cmd_ds_rf_ant_siso *ant_siso = &resp->params.ant_siso;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	अगर (adapter->hw_dev_mcs_support == HT_STREAM_2X2) अणु
		priv->tx_ant = le16_to_cpu(ant_mimo->tx_ant_mode);
		priv->rx_ant = le16_to_cpu(ant_mimo->rx_ant_mode);
		mwअगरiex_dbg(adapter, INFO,
			    "RF_ANT_RESP: Tx action = 0x%x, Tx Mode = 0x%04x\t"
			    "Rx action = 0x%x, Rx Mode = 0x%04x\n",
			    le16_to_cpu(ant_mimo->action_tx),
			    le16_to_cpu(ant_mimo->tx_ant_mode),
			    le16_to_cpu(ant_mimo->action_rx),
			    le16_to_cpu(ant_mimo->rx_ant_mode));
	पूर्ण अन्यथा अणु
		priv->tx_ant = le16_to_cpu(ant_siso->ant_mode);
		priv->rx_ant = le16_to_cpu(ant_siso->ant_mode);
		mwअगरiex_dbg(adapter, INFO,
			    "RF_ANT_RESP: action = 0x%x, Mode = 0x%04x\n",
			    le16_to_cpu(ant_siso->action),
			    le16_to_cpu(ant_siso->ant_mode));
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function handles the command response of set/get MAC address.
 *
 * Handling includes saving the MAC address in driver.
 */
अटल पूर्णांक mwअगरiex_ret_802_11_mac_address(काष्ठा mwअगरiex_निजी *priv,
					  काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_802_11_mac_address *cmd_mac_addr =
							&resp->params.mac_addr;

	स_नकल(priv->curr_addr, cmd_mac_addr->mac_addr, ETH_ALEN);

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: set mac address: %pM\n", priv->curr_addr);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of set/get MAC multicast
 * address.
 */
अटल पूर्णांक mwअगरiex_ret_mac_multicast_adr(काष्ठा mwअगरiex_निजी *priv,
					 काष्ठा host_cmd_ds_command *resp)
अणु
	वापस 0;
पूर्ण

/*
 * This function handles the command response of get Tx rate query.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat
 * and saving the Tx rate and HT inक्रमmation parameters in driver.
 *
 * Both rate configuration and current data rate can be retrieved
 * with this request.
 */
अटल पूर्णांक mwअगरiex_ret_802_11_tx_rate_query(काष्ठा mwअगरiex_निजी *priv,
					    काष्ठा host_cmd_ds_command *resp)
अणु
	priv->tx_rate = resp->params.tx_rate.tx_rate;
	priv->tx_htinfo = resp->params.tx_rate.ht_info;
	अगर (!priv->is_data_rate_स्वतः)
		priv->data_rate =
			mwअगरiex_index_to_data_rate(priv, priv->tx_rate,
						   priv->tx_htinfo);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of a deauthenticate
 * command.
 *
 * If the deauthenticated MAC matches the current BSS MAC, the connection
 * state is reset.
 */
अटल पूर्णांक mwअगरiex_ret_802_11_deauthenticate(काष्ठा mwअगरiex_निजी *priv,
					     काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	adapter->dbg.num_cmd_deauth++;
	अगर (!स_भेद(resp->params.deauth.mac_addr,
		    &priv->curr_bss_params.bss_descriptor.mac_address,
		    माप(resp->params.deauth.mac_addr)))
		mwअगरiex_reset_connect_state(priv, WLAN_REASON_DEAUTH_LEAVING,
					    false);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of ad-hoc stop.
 *
 * The function resets the connection state in driver.
 */
अटल पूर्णांक mwअगरiex_ret_802_11_ad_hoc_stop(काष्ठा mwअगरiex_निजी *priv,
					  काष्ठा host_cmd_ds_command *resp)
अणु
	mwअगरiex_reset_connect_state(priv, WLAN_REASON_DEAUTH_LEAVING, false);
	वापस 0;
पूर्ण

/*
 * This function handles the command response of set/get v1 key material.
 *
 * Handling includes updating the driver parameters to reflect the
 * changes.
 */
अटल पूर्णांक mwअगरiex_ret_802_11_key_material_v1(काष्ठा mwअगरiex_निजी *priv,
					      काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_802_11_key_material *key =
						&resp->params.key_material;
	पूर्णांक len;

	len = le16_to_cpu(key->key_param_set.key_len);
	अगर (len > माप(key->key_param_set.key))
		वापस -EINVAL;

	अगर (le16_to_cpu(key->action) == HostCmd_ACT_GEN_SET) अणु
		अगर ((le16_to_cpu(key->key_param_set.key_info) & KEY_MCAST)) अणु
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: key: GTK is set\n");
			priv->wpa_is_gtk_set = true;
			priv->scan_block = false;
			priv->port_खोलो = true;
		पूर्ण
	पूर्ण

	स_रखो(priv->aes_key.key_param_set.key, 0,
	       माप(key->key_param_set.key));
	priv->aes_key.key_param_set.key_len = cpu_to_le16(len);
	स_नकल(priv->aes_key.key_param_set.key, key->key_param_set.key, len);

	वापस 0;
पूर्ण

/*
 * This function handles the command response of set/get v2 key material.
 *
 * Handling includes updating the driver parameters to reflect the
 * changes.
 */
अटल पूर्णांक mwअगरiex_ret_802_11_key_material_v2(काष्ठा mwअगरiex_निजी *priv,
					      काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_802_11_key_material_v2 *key_v2;
	पूर्णांक len;

	key_v2 = &resp->params.key_material_v2;

	len = le16_to_cpu(key_v2->key_param_set.key_params.aes.key_len);
	अगर (len > माप(key_v2->key_param_set.key_params.aes.key))
		वापस -EINVAL;

	अगर (le16_to_cpu(key_v2->action) == HostCmd_ACT_GEN_SET) अणु
		अगर ((le16_to_cpu(key_v2->key_param_set.key_info) & KEY_MCAST)) अणु
			mwअगरiex_dbg(priv->adapter, INFO, "info: key: GTK is set\n");
			priv->wpa_is_gtk_set = true;
			priv->scan_block = false;
			priv->port_खोलो = true;
		पूर्ण
	पूर्ण

	अगर (key_v2->key_param_set.key_type != KEY_TYPE_ID_AES)
		वापस 0;

	स_रखो(priv->aes_key_v2.key_param_set.key_params.aes.key, 0,
	       माप(key_v2->key_param_set.key_params.aes.key));
	priv->aes_key_v2.key_param_set.key_params.aes.key_len =
				cpu_to_le16(len);
	स_नकल(priv->aes_key_v2.key_param_set.key_params.aes.key,
	       key_v2->key_param_set.key_params.aes.key, len);

	वापस 0;
पूर्ण

/* Wrapper function क्रम processing response of key material command */
अटल पूर्णांक mwअगरiex_ret_802_11_key_material(काष्ठा mwअगरiex_निजी *priv,
					   काष्ठा host_cmd_ds_command *resp)
अणु
	अगर (priv->adapter->key_api_major_ver == KEY_API_VER_MAJOR_V2)
		वापस mwअगरiex_ret_802_11_key_material_v2(priv, resp);
	अन्यथा
		वापस mwअगरiex_ret_802_11_key_material_v1(priv, resp);
पूर्ण

/*
 * This function handles the command response of get 11d करोमुख्य inक्रमmation.
 */
अटल पूर्णांक mwअगरiex_ret_802_11d_करोमुख्य_info(काष्ठा mwअगरiex_निजी *priv,
					   काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_802_11d_करोमुख्य_info_rsp *करोमुख्य_info =
		&resp->params.करोमुख्य_info_resp;
	काष्ठा mwअगरiex_ietypes_करोमुख्य_param_set *करोमुख्य = &करोमुख्य_info->करोमुख्य;
	u16 action = le16_to_cpu(करोमुख्य_info->action);
	u8 no_of_triplet;

	no_of_triplet = (u8) ((le16_to_cpu(करोमुख्य->header.len)
				- IEEE80211_COUNTRY_STRING_LEN)
			      / माप(काष्ठा ieee80211_country_ie_triplet));

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: 11D Domain Info Resp: no_of_triplet=%d\n",
		    no_of_triplet);

	अगर (no_of_triplet > MWIFIEX_MAX_TRIPLET_802_11D) अणु
		mwअगरiex_dbg(priv->adapter, FATAL,
			    "11D: invalid number of triplets %d returned\n",
			    no_of_triplet);
		वापस -1;
	पूर्ण

	चयन (action) अणु
	हाल HostCmd_ACT_GEN_SET:  /* Proc Set Action */
		अवरोध;
	हाल HostCmd_ACT_GEN_GET:
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "11D: invalid action:%d\n", करोमुख्य_info->action);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function handles the command response of get extended version.
 *
 * Handling includes क्रमming the extended version string and sending it
 * to application.
 */
अटल पूर्णांक mwअगरiex_ret_ver_ext(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command *resp,
			       काष्ठा host_cmd_ds_version_ext *version_ext)
अणु
	काष्ठा host_cmd_ds_version_ext *ver_ext = &resp->params.verext;

	अगर (version_ext) अणु
		version_ext->version_str_sel = ver_ext->version_str_sel;
		स_नकल(version_ext->version_str, ver_ext->version_str,
		       माप(अक्षर) * 128);
		स_नकल(priv->version_str, ver_ext->version_str, 128);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function handles the command response of reमुख्य on channel.
 */
अटल पूर्णांक
mwअगरiex_ret_reमुख्य_on_chan(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा host_cmd_ds_command *resp,
			   काष्ठा host_cmd_ds_reमुख्य_on_chan *roc_cfg)
अणु
	काष्ठा host_cmd_ds_reमुख्य_on_chan *resp_cfg = &resp->params.roc_cfg;

	अगर (roc_cfg)
		स_नकल(roc_cfg, resp_cfg, माप(*roc_cfg));

	वापस 0;
पूर्ण

/*
 * This function handles the command response of P2P mode cfg.
 */
अटल पूर्णांक
mwअगरiex_ret_p2p_mode_cfg(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा host_cmd_ds_command *resp,
			 व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_p2p_mode_cfg *mode_cfg = &resp->params.mode_cfg;

	अगर (data_buf)
		put_unaligned_le16(le16_to_cpu(mode_cfg->mode), data_buf);

	वापस 0;
पूर्ण

/* This function handles the command response of mem_access command
 */
अटल पूर्णांक
mwअगरiex_ret_mem_access(काष्ठा mwअगरiex_निजी *priv,
		       काष्ठा host_cmd_ds_command *resp, व्योम *pioctl_buf)
अणु
	काष्ठा host_cmd_ds_mem_access *mem = (व्योम *)&resp->params.mem;

	priv->mem_rw.addr = le32_to_cpu(mem->addr);
	priv->mem_rw.value = le32_to_cpu(mem->value);

	वापस 0;
पूर्ण
/*
 * This function handles the command response of रेजिस्टर access.
 *
 * The रेजिस्टर value and offset are वापसed to the user. For EEPROM
 * access, the byte count is also वापसed.
 */
अटल पूर्णांक mwअगरiex_ret_reg_access(u16 type, काष्ठा host_cmd_ds_command *resp,
				  व्योम *data_buf)
अणु
	काष्ठा mwअगरiex_ds_reg_rw *reg_rw;
	काष्ठा mwअगरiex_ds_पढ़ो_eeprom *eeprom;
	जोड़ reg अणु
		काष्ठा host_cmd_ds_mac_reg_access *mac;
		काष्ठा host_cmd_ds_bbp_reg_access *bbp;
		काष्ठा host_cmd_ds_rf_reg_access *rf;
		काष्ठा host_cmd_ds_pmic_reg_access *pmic;
		काष्ठा host_cmd_ds_802_11_eeprom_access *eeprom;
	पूर्ण r;

	अगर (!data_buf)
		वापस 0;

	reg_rw = data_buf;
	eeprom = data_buf;
	चयन (type) अणु
	हाल HostCmd_CMD_MAC_REG_ACCESS:
		r.mac = &resp->params.mac_reg;
		reg_rw->offset = (u32) le16_to_cpu(r.mac->offset);
		reg_rw->value = le32_to_cpu(r.mac->value);
		अवरोध;
	हाल HostCmd_CMD_BBP_REG_ACCESS:
		r.bbp = &resp->params.bbp_reg;
		reg_rw->offset = (u32) le16_to_cpu(r.bbp->offset);
		reg_rw->value = (u32) r.bbp->value;
		अवरोध;

	हाल HostCmd_CMD_RF_REG_ACCESS:
		r.rf = &resp->params.rf_reg;
		reg_rw->offset = (u32) le16_to_cpu(r.rf->offset);
		reg_rw->value = (u32) r.bbp->value;
		अवरोध;
	हाल HostCmd_CMD_PMIC_REG_ACCESS:
		r.pmic = &resp->params.pmic_reg;
		reg_rw->offset = (u32) le16_to_cpu(r.pmic->offset);
		reg_rw->value = (u32) r.pmic->value;
		अवरोध;
	हाल HostCmd_CMD_CAU_REG_ACCESS:
		r.rf = &resp->params.rf_reg;
		reg_rw->offset = (u32) le16_to_cpu(r.rf->offset);
		reg_rw->value = (u32) r.rf->value;
		अवरोध;
	हाल HostCmd_CMD_802_11_EEPROM_ACCESS:
		r.eeprom = &resp->params.eeprom;
		pr_debug("info: EEPROM read len=%x\n",
				le16_to_cpu(r.eeprom->byte_count));
		अगर (eeprom->byte_count < le16_to_cpu(r.eeprom->byte_count)) अणु
			eeprom->byte_count = 0;
			pr_debug("info: EEPROM read length is too big\n");
			वापस -1;
		पूर्ण
		eeprom->offset = le16_to_cpu(r.eeprom->offset);
		eeprom->byte_count = le16_to_cpu(r.eeprom->byte_count);
		अगर (eeprom->byte_count > 0)
			स_नकल(&eeprom->value, &r.eeprom->value,
			       min((u16)MAX_EEPROM_DATA, eeprom->byte_count));
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function handles the command response of get IBSS coalescing status.
 *
 * If the received BSSID is dअगरferent than the current one, the current BSSID,
 * beacon पूर्णांकerval, ATIM winकरोw and ERP inक्रमmation are updated, aदीर्घ with
 * changing the ad-hoc state accordingly.
 */
अटल पूर्णांक mwअगरiex_ret_ibss_coalescing_status(काष्ठा mwअगरiex_निजी *priv,
					      काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_802_11_ibss_status *ibss_coal_resp =
					&(resp->params.ibss_coalescing);

	अगर (le16_to_cpu(ibss_coal_resp->action) == HostCmd_ACT_GEN_SET)
		वापस 0;

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: new BSSID %pM\n", ibss_coal_resp->bssid);

	/* If rsp has शून्य BSSID, Just वापस..... No Action */
	अगर (is_zero_ether_addr(ibss_coal_resp->bssid)) अणु
		mwअगरiex_dbg(priv->adapter, FATAL, "new BSSID is NULL\n");
		वापस 0;
	पूर्ण

	/* If BSSID is dअगरf, modअगरy current BSS parameters */
	अगर (!ether_addr_equal(priv->curr_bss_params.bss_descriptor.mac_address, ibss_coal_resp->bssid)) अणु
		/* BSSID */
		स_नकल(priv->curr_bss_params.bss_descriptor.mac_address,
		       ibss_coal_resp->bssid, ETH_ALEN);

		/* Beacon Interval */
		priv->curr_bss_params.bss_descriptor.beacon_period
			= le16_to_cpu(ibss_coal_resp->beacon_पूर्णांकerval);

		/* ERP Inक्रमmation */
		priv->curr_bss_params.bss_descriptor.erp_flags =
			(u8) le16_to_cpu(ibss_coal_resp->use_g_rate_protect);

		priv->adhoc_state = ADHOC_COALESCED;
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक mwअगरiex_ret_tdls_oper(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_tdls_oper *cmd_tdls_oper = &resp->params.tdls_oper;
	u16 reason = le16_to_cpu(cmd_tdls_oper->reason);
	u16 action = le16_to_cpu(cmd_tdls_oper->tdls_action);
	काष्ठा mwअगरiex_sta_node *node =
			   mwअगरiex_get_sta_entry(priv, cmd_tdls_oper->peer_mac);

	चयन (action) अणु
	हाल ACT_TDLS_DELETE:
		अगर (reason) अणु
			अगर (!node || reason == TDLS_ERR_LINK_NONEXISTENT)
				mwअगरiex_dbg(priv->adapter, MSG,
					    "TDLS link delete for %pM failed: reason %d\n",
					    cmd_tdls_oper->peer_mac, reason);
			अन्यथा
				mwअगरiex_dbg(priv->adapter, ERROR,
					    "TDLS link delete for %pM failed: reason %d\n",
					    cmd_tdls_oper->peer_mac, reason);
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(priv->adapter, MSG,
				    "TDLS link delete for %pM successful\n",
				    cmd_tdls_oper->peer_mac);
		पूर्ण
		अवरोध;
	हाल ACT_TDLS_CREATE:
		अगर (reason) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "TDLS link creation for %pM failed: reason %d",
				    cmd_tdls_oper->peer_mac, reason);
			अगर (node && reason != TDLS_ERR_LINK_EXISTS)
				node->tdls_status = TDLS_SETUP_FAILURE;
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(priv->adapter, MSG,
				    "TDLS link creation for %pM successful",
				    cmd_tdls_oper->peer_mac);
		पूर्ण
		अवरोध;
	हाल ACT_TDLS_CONFIG:
		अगर (reason) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "TDLS link config for %pM failed, reason %d\n",
				    cmd_tdls_oper->peer_mac, reason);
			अगर (node)
				node->tdls_status = TDLS_SETUP_FAILURE;
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(priv->adapter, MSG,
				    "TDLS link config for %pM successful\n",
				    cmd_tdls_oper->peer_mac);
		पूर्ण
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Unknown TDLS command action response %d", action);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
/*
 * This function handles the command response क्रम subscribe event command.
 */
अटल पूर्णांक mwअगरiex_ret_subsc_evt(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_802_11_subsc_evt *cmd_sub_event =
		&resp->params.subsc_evt;

	/* For every subscribe event command (Get/Set/Clear), FW reports the
	 * current set of subscribed events*/
	mwअगरiex_dbg(priv->adapter, EVENT,
		    "Bitmap of currently subscribed events: %16x\n",
		    le16_to_cpu(cmd_sub_event->events));

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_ret_uap_sta_list(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_sta_list *sta_list =
		&resp->params.sta_list;
	काष्ठा mwअगरiex_ie_types_sta_info *sta_info = (व्योम *)&sta_list->tlv;
	पूर्णांक i;
	काष्ठा mwअगरiex_sta_node *sta_node;

	क्रम (i = 0; i < (le16_to_cpu(sta_list->sta_count)); i++) अणु
		sta_node = mwअगरiex_get_sta_entry(priv, sta_info->mac);
		अगर (unlikely(!sta_node))
			जारी;

		sta_node->stats.rssi = sta_info->rssi;
		sta_info++;
	पूर्ण

	वापस 0;
पूर्ण

/* This function handles the command response of set_cfg_data */
अटल पूर्णांक mwअगरiex_ret_cfg_data(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *resp)
अणु
	अगर (resp->result != HostCmd_RESULT_OK) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "Cal data cmd resp failed\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/** This Function handles the command response of sdio rx aggr */
अटल पूर्णांक mwअगरiex_ret_sdio_rx_aggr_cfg(काष्ठा mwअगरiex_निजी *priv,
					काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_sdio_sp_rx_aggr_cfg *cfg =
				&resp->params.sdio_rx_aggr_cfg;

	adapter->sdio_rx_aggr_enable = cfg->enable;
	adapter->sdio_rx_block_size = le16_to_cpu(cfg->block_size);

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_ret_robust_coex(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *resp,
				   bool *is_बारhare)
अणु
	काष्ठा host_cmd_ds_robust_coex *coex = &resp->params.coex;
	काष्ठा mwअगरiex_ie_types_robust_coex *coex_tlv;
	u16 action = le16_to_cpu(coex->action);
	u32 mode;

	coex_tlv = (काष्ठा mwअगरiex_ie_types_robust_coex
		    *)((u8 *)coex + माप(काष्ठा host_cmd_ds_robust_coex));
	अगर (action == HostCmd_ACT_GEN_GET) अणु
		mode = le32_to_cpu(coex_tlv->mode);
		अगर (mode == MWIFIEX_COEX_MODE_TIMESHARE)
			*is_बारhare = true;
		अन्यथा
			*is_बारhare = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ieee80211_regकरोमुख्य *
mwअगरiex_create_custom_regकरोमुख्य(काष्ठा mwअगरiex_निजी *priv,
				u8 *buf, u16 buf_len)
अणु
	u16 num_chan = buf_len / 2;
	काष्ठा ieee80211_regकरोमुख्य *regd;
	काष्ठा ieee80211_reg_rule *rule;
	bool new_rule;
	पूर्णांक idx, freq, prev_freq = 0;
	u32 bw, prev_bw = 0;
	u8 chflags, prev_chflags = 0, valid_rules = 0;

	अगर (WARN_ON_ONCE(num_chan > NL80211_MAX_SUPP_REG_RULES))
		वापस ERR_PTR(-EINVAL);

	regd = kzalloc(काष्ठा_size(regd, reg_rules, num_chan), GFP_KERNEL);
	अगर (!regd)
		वापस ERR_PTR(-ENOMEM);

	क्रम (idx = 0; idx < num_chan; idx++) अणु
		u8 chan;
		क्रमागत nl80211_band band;

		chan = *buf++;
		अगर (!chan) अणु
			kमुक्त(regd);
			वापस शून्य;
		पूर्ण
		chflags = *buf++;
		band = (chan <= 14) ? NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
		freq = ieee80211_channel_to_frequency(chan, band);
		new_rule = false;

		अगर (chflags & MWIFIEX_CHANNEL_DISABLED)
			जारी;

		अगर (band == NL80211_BAND_5GHZ) अणु
			अगर (!(chflags & MWIFIEX_CHANNEL_NOHT80))
				bw = MHZ_TO_KHZ(80);
			अन्यथा अगर (!(chflags & MWIFIEX_CHANNEL_NOHT40))
				bw = MHZ_TO_KHZ(40);
			अन्यथा
				bw = MHZ_TO_KHZ(20);
		पूर्ण अन्यथा अणु
			अगर (!(chflags & MWIFIEX_CHANNEL_NOHT40))
				bw = MHZ_TO_KHZ(40);
			अन्यथा
				bw = MHZ_TO_KHZ(20);
		पूर्ण

		अगर (idx == 0 || prev_chflags != chflags || prev_bw != bw ||
		    freq - prev_freq > 20) अणु
			valid_rules++;
			new_rule = true;
		पूर्ण

		rule = &regd->reg_rules[valid_rules - 1];

		rule->freq_range.end_freq_khz = MHZ_TO_KHZ(freq + 10);

		prev_chflags = chflags;
		prev_freq = freq;
		prev_bw = bw;

		अगर (!new_rule)
			जारी;

		rule->freq_range.start_freq_khz = MHZ_TO_KHZ(freq - 10);
		rule->घातer_rule.max_eirp = DBM_TO_MBM(19);

		अगर (chflags & MWIFIEX_CHANNEL_PASSIVE)
			rule->flags = NL80211_RRF_NO_IR;

		अगर (chflags & MWIFIEX_CHANNEL_DFS)
			rule->flags = NL80211_RRF_DFS;

		rule->freq_range.max_bandwidth_khz = bw;
	पूर्ण

	regd->n_reg_rules = valid_rules;
	regd->alpha2[0] = '9';
	regd->alpha2[1] = '9';

	वापस regd;
पूर्ण

अटल पूर्णांक mwअगरiex_ret_chan_region_cfg(काष्ठा mwअगरiex_निजी *priv,
				       काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_chan_region_cfg *reg = &resp->params.reg_cfg;
	u16 action = le16_to_cpu(reg->action);
	u16 tlv, tlv_buf_len, tlv_buf_left;
	काष्ठा mwअगरiex_ie_types_header *head;
	काष्ठा ieee80211_regकरोमुख्य *regd;
	u8 *tlv_buf;

	अगर (action != HostCmd_ACT_GEN_GET)
		वापस 0;

	tlv_buf = (u8 *)reg + माप(*reg);
	tlv_buf_left = le16_to_cpu(resp->size) - S_DS_GEN - माप(*reg);

	जबतक (tlv_buf_left >= माप(*head)) अणु
		head = (काष्ठा mwअगरiex_ie_types_header *)tlv_buf;
		tlv = le16_to_cpu(head->type);
		tlv_buf_len = le16_to_cpu(head->len);

		अगर (tlv_buf_left < (माप(*head) + tlv_buf_len))
			अवरोध;

		चयन (tlv) अणु
		हाल TLV_TYPE_CHAN_ATTR_CFG:
			mwअगरiex_dbg_dump(priv->adapter, CMD_D, "CHAN:",
					 (u8 *)head + माप(*head),
					 tlv_buf_len);
			regd = mwअगरiex_create_custom_regकरोमुख्य(priv,
				(u8 *)head + माप(*head), tlv_buf_len);
			अगर (!IS_ERR(regd))
				priv->adapter->regd = regd;
			अवरोध;
		पूर्ण

		tlv_buf += (माप(*head) + tlv_buf_len);
		tlv_buf_left -= (माप(*head) + tlv_buf_len);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_ret_pkt_aggr_ctrl(काष्ठा mwअगरiex_निजी *priv,
				     काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_pkt_aggr_ctrl *pkt_aggr_ctrl =
					&resp->params.pkt_aggr_ctrl;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	adapter->bus_aggr.enable = le16_to_cpu(pkt_aggr_ctrl->enable);
	अगर (adapter->bus_aggr.enable)
		adapter->पूर्णांकf_hdr_len = INTF_HEADER_LEN;
	adapter->bus_aggr.mode = MWIFIEX_BUS_AGGR_MODE_LEN_V2;
	adapter->bus_aggr.tx_aggr_max_size =
				le16_to_cpu(pkt_aggr_ctrl->tx_aggr_max_size);
	adapter->bus_aggr.tx_aggr_max_num =
				le16_to_cpu(pkt_aggr_ctrl->tx_aggr_max_num);
	adapter->bus_aggr.tx_aggr_align =
				le16_to_cpu(pkt_aggr_ctrl->tx_aggr_align);

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_ret_get_chan_info(काष्ठा mwअगरiex_निजी *priv,
				     काष्ठा host_cmd_ds_command *resp,
				     काष्ठा mwअगरiex_channel_band *channel_band)
अणु
	काष्ठा host_cmd_ds_sta_configure *sta_cfg_cmd = &resp->params.sta_cfg;
	काष्ठा host_cmd_tlv_channel_band *tlv_band_channel;

	tlv_band_channel =
	(काष्ठा host_cmd_tlv_channel_band *)sta_cfg_cmd->tlv_buffer;
	स_नकल(&channel_band->band_config, &tlv_band_channel->band_config,
	       माप(काष्ठा mwअगरiex_band_config));
	channel_band->channel = tlv_band_channel->channel;

	वापस 0;
पूर्ण

/*
 * This function handles the command responses.
 *
 * This is a generic function, which calls command specअगरic
 * response handlers based on the command ID.
 */
पूर्णांक mwअगरiex_process_sta_cmdresp(काष्ठा mwअगरiex_निजी *priv, u16 cmdresp_no,
				काष्ठा host_cmd_ds_command *resp)
अणु
	पूर्णांक ret = 0;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	व्योम *data_buf = adapter->curr_cmd->data_buf;

	/* If the command is not successful, cleanup and वापस failure */
	अगर (resp->result != HostCmd_RESULT_OK) अणु
		mwअगरiex_process_cmdresp_error(priv, resp);
		वापस -1;
	पूर्ण
	/* Command successful, handle response */
	चयन (cmdresp_no) अणु
	हाल HostCmd_CMD_GET_HW_SPEC:
		ret = mwअगरiex_ret_get_hw_spec(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_CFG_DATA:
		ret = mwअगरiex_ret_cfg_data(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_MAC_CONTROL:
		अवरोध;
	हाल HostCmd_CMD_802_11_MAC_ADDRESS:
		ret = mwअगरiex_ret_802_11_mac_address(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_MAC_MULTICAST_ADR:
		ret = mwअगरiex_ret_mac_multicast_adr(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_TX_RATE_CFG:
		ret = mwअगरiex_ret_tx_rate_cfg(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_SCAN:
		ret = mwअगरiex_ret_802_11_scan(priv, resp);
		adapter->curr_cmd->रुको_q_enabled = false;
		अवरोध;
	हाल HostCmd_CMD_802_11_SCAN_EXT:
		ret = mwअगरiex_ret_802_11_scan_ext(priv, resp);
		adapter->curr_cmd->रुको_q_enabled = false;
		अवरोध;
	हाल HostCmd_CMD_802_11_BG_SCAN_QUERY:
		ret = mwअगरiex_ret_802_11_scan(priv, resp);
		cfg80211_sched_scan_results(priv->wdev.wiphy, 0);
		mwअगरiex_dbg(adapter, CMD,
			    "info: CMD_RESP: BG_SCAN result is ready!\n");
		अवरोध;
	हाल HostCmd_CMD_802_11_BG_SCAN_CONFIG:
		अवरोध;
	हाल HostCmd_CMD_TXPWR_CFG:
		ret = mwअगरiex_ret_tx_घातer_cfg(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_RF_TX_PWR:
		ret = mwअगरiex_ret_rf_tx_घातer(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_RF_ANTENNA:
		ret = mwअगरiex_ret_rf_antenna(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_PS_MODE_ENH:
		ret = mwअगरiex_ret_enh_घातer_mode(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_HS_CFG_ENH:
		ret = mwअगरiex_ret_802_11_hs_cfg(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_ASSOCIATE:
		ret = mwअगरiex_ret_802_11_associate(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_DEAUTHENTICATE:
		ret = mwअगरiex_ret_802_11_deauthenticate(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_AD_HOC_START:
	हाल HostCmd_CMD_802_11_AD_HOC_JOIN:
		ret = mwअगरiex_ret_802_11_ad_hoc(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_AD_HOC_STOP:
		ret = mwअगरiex_ret_802_11_ad_hoc_stop(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_GET_LOG:
		ret = mwअगरiex_ret_get_log(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_RSSI_INFO:
		ret = mwअगरiex_ret_802_11_rssi_info(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_SNMP_MIB:
		ret = mwअगरiex_ret_802_11_snmp_mib(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_TX_RATE_QUERY:
		ret = mwअगरiex_ret_802_11_tx_rate_query(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_VERSION_EXT:
		ret = mwअगरiex_ret_ver_ext(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_REMAIN_ON_CHAN:
		ret = mwअगरiex_ret_reमुख्य_on_chan(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_11AC_CFG:
		अवरोध;
	हाल HostCmd_CMD_PACKET_AGGR_CTRL:
		ret = mwअगरiex_ret_pkt_aggr_ctrl(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_P2P_MODE_CFG:
		ret = mwअगरiex_ret_p2p_mode_cfg(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_MGMT_FRAME_REG:
	हाल HostCmd_CMD_FUNC_INIT:
	हाल HostCmd_CMD_FUNC_SHUTDOWN:
		अवरोध;
	हाल HostCmd_CMD_802_11_KEY_MATERIAL:
		ret = mwअगरiex_ret_802_11_key_material(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11D_DOMAIN_INFO:
		ret = mwअगरiex_ret_802_11d_करोमुख्य_info(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_11N_ADDBA_REQ:
		ret = mwअगरiex_ret_11n_addba_req(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_11N_DELBA:
		ret = mwअगरiex_ret_11n_delba(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_11N_ADDBA_RSP:
		ret = mwअगरiex_ret_11n_addba_resp(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_RECONFIGURE_TX_BUFF:
		अगर (0xffff == (u16)le16_to_cpu(resp->params.tx_buf.buff_size)) अणु
			अगर (adapter->अगरace_type == MWIFIEX_USB &&
			    adapter->usb_mc_setup) अणु
				अगर (adapter->अगर_ops.multi_port_resync)
					adapter->अगर_ops.
						multi_port_resync(adapter);
				adapter->usb_mc_setup = false;
				adapter->tx_lock_flag = false;
			पूर्ण
			अवरोध;
		पूर्ण
		adapter->tx_buf_size = (u16) le16_to_cpu(resp->params.
							     tx_buf.buff_size);
		adapter->tx_buf_size = (adapter->tx_buf_size
					/ MWIFIEX_SDIO_BLOCK_SIZE)
				       * MWIFIEX_SDIO_BLOCK_SIZE;
		adapter->curr_tx_buf_size = adapter->tx_buf_size;
		mwअगरiex_dbg(adapter, CMD, "cmd: curr_tx_buf_size=%d\n",
			    adapter->curr_tx_buf_size);

		अगर (adapter->अगर_ops.update_mp_end_port)
			adapter->अगर_ops.update_mp_end_port(adapter,
				le16_to_cpu(resp->params.tx_buf.mp_end_port));
		अवरोध;
	हाल HostCmd_CMD_AMSDU_AGGR_CTRL:
		अवरोध;
	हाल HostCmd_CMD_WMM_GET_STATUS:
		ret = mwअगरiex_ret_wmm_get_status(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_802_11_IBSS_COALESCING_STATUS:
		ret = mwअगरiex_ret_ibss_coalescing_status(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_MEM_ACCESS:
		ret = mwअगरiex_ret_mem_access(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_MAC_REG_ACCESS:
	हाल HostCmd_CMD_BBP_REG_ACCESS:
	हाल HostCmd_CMD_RF_REG_ACCESS:
	हाल HostCmd_CMD_PMIC_REG_ACCESS:
	हाल HostCmd_CMD_CAU_REG_ACCESS:
	हाल HostCmd_CMD_802_11_EEPROM_ACCESS:
		ret = mwअगरiex_ret_reg_access(cmdresp_no, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_SET_BSS_MODE:
		अवरोध;
	हाल HostCmd_CMD_11N_CFG:
		अवरोध;
	हाल HostCmd_CMD_PCIE_DESC_DETAILS:
		अवरोध;
	हाल HostCmd_CMD_802_11_SUBSCRIBE_EVENT:
		ret = mwअगरiex_ret_subsc_evt(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_UAP_SYS_CONFIG:
		अवरोध;
	हाल HOST_CMD_APCMD_STA_LIST:
		ret = mwअगरiex_ret_uap_sta_list(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_UAP_BSS_START:
		adapter->tx_lock_flag = false;
		adapter->pps_uapsd_mode = false;
		adapter->delay_null_pkt = false;
		priv->bss_started = 1;
		अवरोध;
	हाल HostCmd_CMD_UAP_BSS_STOP:
		priv->bss_started = 0;
		अवरोध;
	हाल HostCmd_CMD_UAP_STA_DEAUTH:
		अवरोध;
	हाल HOST_CMD_APCMD_SYS_RESET:
		अवरोध;
	हाल HostCmd_CMD_MEF_CFG:
		अवरोध;
	हाल HostCmd_CMD_COALESCE_CFG:
		अवरोध;
	हाल HostCmd_CMD_TDLS_OPER:
		ret = mwअगरiex_ret_tdls_oper(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_MC_POLICY:
		अवरोध;
	हाल HostCmd_CMD_CHAN_REPORT_REQUEST:
		अवरोध;
	हाल HostCmd_CMD_SDIO_SP_RX_AGGR_CFG:
		ret = mwअगरiex_ret_sdio_rx_aggr_cfg(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_HS_WAKEUP_REASON:
		ret = mwअगरiex_ret_wakeup_reason(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_TDLS_CONFIG:
		अवरोध;
	हाल HostCmd_CMD_ROBUST_COEX:
		ret = mwअगरiex_ret_robust_coex(priv, resp, data_buf);
		अवरोध;
	हाल HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG:
		अवरोध;
	हाल HostCmd_CMD_CHAN_REGION_CFG:
		ret = mwअगरiex_ret_chan_region_cfg(priv, resp);
		अवरोध;
	हाल HostCmd_CMD_STA_CONFIGURE:
		ret = mwअगरiex_ret_get_chan_info(priv, resp, data_buf);
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR,
			    "CMD_RESP: unknown cmd response %#x\n",
			    resp->command);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
