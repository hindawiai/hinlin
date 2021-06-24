<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "acx.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "wl1251.h"
#समावेश "reg.h"
#समावेश "cmd.h"
#समावेश "ps.h"

पूर्णांक wl1251_acx_frame_rates(काष्ठा wl1251 *wl, u8 ctrl_rate, u8 ctrl_mod,
			   u8 mgt_rate, u8 mgt_mod)
अणु
	काष्ठा acx_fw_gen_frame_rates *rates;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx frame rates");

	rates = kzalloc(माप(*rates), GFP_KERNEL);
	अगर (!rates)
		वापस -ENOMEM;

	rates->tx_ctrl_frame_rate = ctrl_rate;
	rates->tx_ctrl_frame_mod = ctrl_mod;
	rates->tx_mgt_frame_rate = mgt_rate;
	rates->tx_mgt_frame_mod = mgt_mod;

	ret = wl1251_cmd_configure(wl, ACX_FW_GEN_FRAME_RATES,
				   rates, माप(*rates));
	अगर (ret < 0) अणु
		wl1251_error("Failed to set FW rates and modulation");
		जाओ out;
	पूर्ण

out:
	kमुक्त(rates);
	वापस ret;
पूर्ण


पूर्णांक wl1251_acx_station_id(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_करोt11_station_id *mac;
	पूर्णांक ret, i;

	wl1251_debug(DEBUG_ACX, "acx dot11_station_id");

	mac = kzalloc(माप(*mac), GFP_KERNEL);
	अगर (!mac)
		वापस -ENOMEM;

	क्रम (i = 0; i < ETH_ALEN; i++)
		mac->mac[i] = wl->mac_addr[ETH_ALEN - 1 - i];

	ret = wl1251_cmd_configure(wl, DOT11_STATION_ID, mac, माप(*mac));

	kमुक्त(mac);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_शेष_key(काष्ठा wl1251 *wl, u8 key_id)
अणु
	काष्ठा acx_करोt11_शेष_key *शेष_key;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx dot11_default_key (%d)", key_id);

	शेष_key = kzalloc(माप(*शेष_key), GFP_KERNEL);
	अगर (!शेष_key)
		वापस -ENOMEM;

	शेष_key->id = key_id;

	ret = wl1251_cmd_configure(wl, DOT11_DEFAULT_KEY,
				   शेष_key, माप(*शेष_key));
	अगर (ret < 0) अणु
		wl1251_error("Couldn't set default key");
		जाओ out;
	पूर्ण

	wl->शेष_key = key_id;

out:
	kमुक्त(शेष_key);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_wake_up_conditions(काष्ठा wl1251 *wl, u8 wake_up_event,
				  u8 listen_पूर्णांकerval)
अणु
	काष्ठा acx_wake_up_condition *wake_up;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx wake up conditions");

	wake_up = kzalloc(माप(*wake_up), GFP_KERNEL);
	अगर (!wake_up)
		वापस -ENOMEM;

	wake_up->wake_up_event = wake_up_event;
	wake_up->listen_पूर्णांकerval = listen_पूर्णांकerval;

	ret = wl1251_cmd_configure(wl, ACX_WAKE_UP_CONDITIONS,
				   wake_up, माप(*wake_up));
	अगर (ret < 0) अणु
		wl1251_warning("could not set wake up conditions: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(wake_up);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_sleep_auth(काष्ठा wl1251 *wl, u8 sleep_auth)
अणु
	काष्ठा acx_sleep_auth *auth;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx sleep auth");

	auth = kzalloc(माप(*auth), GFP_KERNEL);
	अगर (!auth)
		वापस -ENOMEM;

	auth->sleep_auth = sleep_auth;

	ret = wl1251_cmd_configure(wl, ACX_SLEEP_AUTH, auth, माप(*auth));

	kमुक्त(auth);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_fw_version(काष्ठा wl1251 *wl, अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा acx_revision *rev;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx fw rev");

	rev = kzalloc(माप(*rev), GFP_KERNEL);
	अगर (!rev)
		वापस -ENOMEM;

	ret = wl1251_cmd_पूर्णांकerrogate(wl, ACX_FW_REV, rev, माप(*rev));
	अगर (ret < 0) अणु
		wl1251_warning("ACX_FW_REV interrogate failed");
		जाओ out;
	पूर्ण

	/* be careful with the buffer sizes */
	म_नकलन(buf, rev->fw_version, min(len, माप(rev->fw_version)));

	/*
	 * अगर the firmware version string is exactly
	 * माप(rev->fw_version) दीर्घ or fw_len is less than
	 * माप(rev->fw_version) it won't be null terminated
	 */
	buf[min(len, माप(rev->fw_version)) - 1] = '\0';

out:
	kमुक्त(rev);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_tx_घातer(काष्ठा wl1251 *wl, पूर्णांक घातer)
अणु
	काष्ठा acx_current_tx_घातer *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx dot11_cur_tx_pwr");

	अगर (घातer < 0 || घातer > 25)
		वापस -EINVAL;

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->current_tx_घातer = घातer * 10;

	ret = wl1251_cmd_configure(wl, DOT11_CUR_TX_PWR, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("configure of tx power failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_feature_cfg(काष्ठा wl1251 *wl, u32 data_flow_options)
अणु
	काष्ठा acx_feature_config *feature;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx feature cfg");

	feature = kzalloc(माप(*feature), GFP_KERNEL);
	अगर (!feature)
		वापस -ENOMEM;

	/* DF_ENCRYPTION_DISABLE and DF_SNIFF_MODE_ENABLE can be set */
	feature->data_flow_options = data_flow_options;
	feature->options = 0;

	ret = wl1251_cmd_configure(wl, ACX_FEATURE_CFG,
				   feature, माप(*feature));
	अगर (ret < 0) अणु
		wl1251_error("Couldn't set HW encryption");
		जाओ out;
	पूर्ण

out:
	kमुक्त(feature);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_mem_map(काष्ठा wl1251 *wl, काष्ठा acx_header *mem_map,
		       माप_प्रकार len)
अणु
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx mem map");

	ret = wl1251_cmd_पूर्णांकerrogate(wl, ACX_MEM_MAP, mem_map, len);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1251_acx_data_path_params(काष्ठा wl1251 *wl,
				काष्ठा acx_data_path_params_resp *resp)
अणु
	काष्ठा acx_data_path_params *params;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx data path params");

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस -ENOMEM;

	params->rx_packet_ring_chunk_size = DP_RX_PACKET_RING_CHUNK_SIZE;
	params->tx_packet_ring_chunk_size = DP_TX_PACKET_RING_CHUNK_SIZE;

	params->rx_packet_ring_chunk_num = DP_RX_PACKET_RING_CHUNK_NUM;
	params->tx_packet_ring_chunk_num = DP_TX_PACKET_RING_CHUNK_NUM;

	params->tx_complete_threshold = 1;

	params->tx_complete_ring_depth = FW_TX_CMPLT_BLOCK_SIZE;

	params->tx_complete_समयout = DP_TX_COMPLETE_TIME_OUT;

	ret = wl1251_cmd_configure(wl, ACX_DATA_PATH_PARAMS,
				   params, माप(*params));
	अगर (ret < 0)
		जाओ out;

	/* FIXME: shouldn't this be ACX_DATA_PATH_RESP_PARAMS? */
	ret = wl1251_cmd_पूर्णांकerrogate(wl, ACX_DATA_PATH_PARAMS,
				     resp, माप(*resp));

	अगर (ret < 0) अणु
		wl1251_warning("failed to read data path parameters: %d", ret);
		जाओ out;
	पूर्ण अन्यथा अगर (resp->header.cmd.status != CMD_STATUS_SUCCESS) अणु
		wl1251_warning("data path parameter acx status failed");
		ret = -EIO;
		जाओ out;
	पूर्ण

out:
	kमुक्त(params);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_rx_msdu_lअगरe_समय(काष्ठा wl1251 *wl, u32 lअगरe_समय)
अणु
	काष्ठा acx_rx_msdu_lअगरeसमय *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx rx msdu life time");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->lअगरeसमय = lअगरe_समय;
	ret = wl1251_cmd_configure(wl, DOT11_RX_MSDU_LIFE_TIME,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set rx msdu life time: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_rx_config(काष्ठा wl1251 *wl, u32 config, u32 filter)
अणु
	काष्ठा acx_rx_config *rx_config;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx rx config");

	rx_config = kzalloc(माप(*rx_config), GFP_KERNEL);
	अगर (!rx_config)
		वापस -ENOMEM;

	rx_config->config_options = config;
	rx_config->filter_options = filter;

	ret = wl1251_cmd_configure(wl, ACX_RX_CFG,
				   rx_config, माप(*rx_config));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set rx config: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(rx_config);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_pd_threshold(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_packet_detection *pd;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx data pd threshold");

	pd = kzalloc(माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	/* FIXME: threshold value not set */

	ret = wl1251_cmd_configure(wl, ACX_PD_THRESHOLD, pd, माप(*pd));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set pd threshold: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(pd);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_slot(काष्ठा wl1251 *wl, क्रमागत acx_slot_type slot_समय)
अणु
	काष्ठा acx_slot *slot;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx slot");

	slot = kzalloc(माप(*slot), GFP_KERNEL);
	अगर (!slot)
		वापस -ENOMEM;

	slot->wone_index = STATION_WONE_INDEX;
	slot->slot_समय = slot_समय;

	ret = wl1251_cmd_configure(wl, ACX_SLOT, slot, माप(*slot));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set slot time: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(slot);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_group_address_tbl(काष्ठा wl1251 *wl, bool enable,
				 व्योम *mc_list, u32 mc_list_len)
अणु
	काष्ठा acx_करोt11_grp_addr_tbl *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx group address tbl");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	/* MAC filtering */
	acx->enabled = enable;
	acx->num_groups = mc_list_len;
	स_नकल(acx->mac_table, mc_list, mc_list_len * ETH_ALEN);

	ret = wl1251_cmd_configure(wl, DOT11_GROUP_ADDRESS_TBL,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set group addr table: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_service_period_समयout(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_rx_समयout *rx_समयout;
	पूर्णांक ret;

	rx_समयout = kzalloc(माप(*rx_समयout), GFP_KERNEL);
	अगर (!rx_समयout)
		वापस -ENOMEM;

	wl1251_debug(DEBUG_ACX, "acx service period timeout");

	rx_समयout->ps_poll_समयout = RX_TIMEOUT_PS_POLL_DEF;
	rx_समयout->upsd_समयout = RX_TIMEOUT_UPSD_DEF;

	ret = wl1251_cmd_configure(wl, ACX_SERVICE_PERIOD_TIMEOUT,
				   rx_समयout, माप(*rx_समयout));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set service period timeout: %d",
			       ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(rx_समयout);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_rts_threshold(काष्ठा wl1251 *wl, u16 rts_threshold)
अणु
	काष्ठा acx_rts_threshold *rts;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx rts threshold");

	rts = kzalloc(माप(*rts), GFP_KERNEL);
	अगर (!rts)
		वापस -ENOMEM;

	rts->threshold = rts_threshold;

	ret = wl1251_cmd_configure(wl, DOT11_RTS_THRESHOLD, rts, माप(*rts));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set rts threshold: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(rts);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_beacon_filter_opt(काष्ठा wl1251 *wl, bool enable_filter)
अणु
	काष्ठा acx_beacon_filter_option *beacon_filter;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx beacon filter opt");

	beacon_filter = kzalloc(माप(*beacon_filter), GFP_KERNEL);
	अगर (!beacon_filter)
		वापस -ENOMEM;

	beacon_filter->enable = enable_filter;
	beacon_filter->max_num_beacons = 0;

	ret = wl1251_cmd_configure(wl, ACX_BEACON_FILTER_OPT,
				   beacon_filter, माप(*beacon_filter));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set beacon filter opt: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(beacon_filter);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_beacon_filter_table(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_beacon_filter_ie_table *ie_table;
	पूर्णांक idx = 0;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx beacon filter table");

	ie_table = kzalloc(माप(*ie_table), GFP_KERNEL);
	अगर (!ie_table)
		वापस -ENOMEM;

	/* configure शेष beacon pass-through rules */
	ie_table->num_ie = 1;
	ie_table->table[idx++] = BEACON_FILTER_IE_ID_CHANNEL_SWITCH_ANN;
	ie_table->table[idx++] = BEACON_RULE_PASS_ON_APPEARANCE;

	ret = wl1251_cmd_configure(wl, ACX_BEACON_FILTER_TABLE,
				   ie_table, माप(*ie_table));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set beacon filter table: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(ie_table);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_conn_monit_params(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_conn_monit_params *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx connection monitor parameters");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->synch_fail_thold = SYNCH_FAIL_DEFAULT_THRESHOLD;
	acx->bss_lose_समयout = NO_BEACON_DEFAULT_TIMEOUT;

	ret = wl1251_cmd_configure(wl, ACX_CONN_MONIT_PARAMS,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set connection monitor "
			       "parameters: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_sg_enable(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_bt_wlan_coex *pta;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx sg enable");

	pta = kzalloc(माप(*pta), GFP_KERNEL);
	अगर (!pta)
		वापस -ENOMEM;

	pta->enable = SG_ENABLE;

	ret = wl1251_cmd_configure(wl, ACX_SG_ENABLE, pta, माप(*pta));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set softgemini enable: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(pta);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_sg_cfg(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_bt_wlan_coex_param *param;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx sg cfg");

	param = kzalloc(माप(*param), GFP_KERNEL);
	अगर (!param)
		वापस -ENOMEM;

	/* BT-WLAN coext parameters */
	param->min_rate = RATE_INDEX_24MBPS;
	param->bt_hp_max_समय = PTA_BT_HP_MAXTIME_DEF;
	param->wlan_hp_max_समय = PTA_WLAN_HP_MAX_TIME_DEF;
	param->sense_disable_समयr = PTA_SENSE_DISABLE_TIMER_DEF;
	param->rx_समय_bt_hp = PTA_PROTECTIVE_RX_TIME_DEF;
	param->tx_समय_bt_hp = PTA_PROTECTIVE_TX_TIME_DEF;
	param->rx_समय_bt_hp_fast = PTA_PROTECTIVE_RX_TIME_FAST_DEF;
	param->tx_समय_bt_hp_fast = PTA_PROTECTIVE_TX_TIME_FAST_DEF;
	param->wlan_cycle_fast = PTA_CYCLE_TIME_FAST_DEF;
	param->bt_anti_starvation_period = PTA_ANTI_STARVE_PERIOD_DEF;
	param->next_bt_lp_packet = PTA_TIMEOUT_NEXT_BT_LP_PACKET_DEF;
	param->wake_up_beacon = PTA_TIME_BEFORE_BEACON_DEF;
	param->hp_dm_max_guard_समय = PTA_HPDM_MAX_TIME_DEF;
	param->next_wlan_packet = PTA_TIME_OUT_NEXT_WLAN_DEF;
	param->antenna_type = PTA_ANTENNA_TYPE_DEF;
	param->संकेत_type = PTA_SIGNALING_TYPE_DEF;
	param->afh_leverage_on = PTA_AFH_LEVERAGE_ON_DEF;
	param->quiet_cycle_num = PTA_NUMBER_QUIET_CYCLE_DEF;
	param->max_cts = PTA_MAX_NUM_CTS_DEF;
	param->wlan_packets_num = PTA_NUMBER_OF_WLAN_PACKETS_DEF;
	param->bt_packets_num = PTA_NUMBER_OF_BT_PACKETS_DEF;
	param->missed_rx_avalanche = PTA_RX_FOR_AVALANCHE_DEF;
	param->wlan_elp_hp = PTA_ELP_HP_DEF;
	param->bt_anti_starvation_cycles = PTA_ANTI_STARVE_NUM_CYCLE_DEF;
	param->ack_mode_dual_ant = PTA_ACK_MODE_DEF;
	param->pa_sd_enable = PTA_ALLOW_PA_SD_DEF;
	param->pta_स्वतः_mode_enable = PTA_AUTO_MODE_NO_CTS_DEF;
	param->bt_hp_respected_num = PTA_BT_HP_RESPECTED_DEF;

	ret = wl1251_cmd_configure(wl, ACX_SG_CFG, param, माप(*param));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set sg config: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(param);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_cca_threshold(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_energy_detection *detection;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx cca threshold");

	detection = kzalloc(माप(*detection), GFP_KERNEL);
	अगर (!detection)
		वापस -ENOMEM;

	detection->rx_cca_threshold = CCA_THRSH_DISABLE_ENERGY_D;
	detection->tx_energy_detection = 0;

	ret = wl1251_cmd_configure(wl, ACX_CCA_THRESHOLD,
				   detection, माप(*detection));
	अगर (ret < 0)
		wl1251_warning("failed to set cca threshold: %d", ret);

	kमुक्त(detection);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_bcn_dtim_options(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_beacon_broadcast *bb;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx bcn dtim options");

	bb = kzalloc(माप(*bb), GFP_KERNEL);
	अगर (!bb)
		वापस -ENOMEM;

	bb->beacon_rx_समयout = BCN_RX_TIMEOUT_DEF_VALUE;
	bb->broadcast_समयout = BROADCAST_RX_TIMEOUT_DEF_VALUE;
	bb->rx_broadcast_in_ps = RX_BROADCAST_IN_PS_DEF_VALUE;
	bb->ps_poll_threshold = CONSECUTIVE_PS_POLL_FAILURE_DEF;

	ret = wl1251_cmd_configure(wl, ACX_BCN_DTIM_OPTIONS, bb, माप(*bb));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set rx config: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(bb);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_aid(काष्ठा wl1251 *wl, u16 aid)
अणु
	काष्ठा acx_aid *acx_aid;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx aid");

	acx_aid = kzalloc(माप(*acx_aid), GFP_KERNEL);
	अगर (!acx_aid)
		वापस -ENOMEM;

	acx_aid->aid = aid;

	ret = wl1251_cmd_configure(wl, ACX_AID, acx_aid, माप(*acx_aid));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set aid: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx_aid);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_event_mbox_mask(काष्ठा wl1251 *wl, u32 event_mask)
अणु
	काष्ठा acx_event_mask *mask;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx event mbox mask");

	mask = kzalloc(माप(*mask), GFP_KERNEL);
	अगर (!mask)
		वापस -ENOMEM;

	/* high event mask is unused */
	mask->high_event_mask = 0xffffffff;

	mask->event_mask = event_mask;

	ret = wl1251_cmd_configure(wl, ACX_EVENT_MBOX_MASK,
				   mask, माप(*mask));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set acx_event_mbox_mask: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(mask);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_low_rssi(काष्ठा wl1251 *wl, s8 threshold, u8 weight,
			u8 depth, क्रमागत wl1251_acx_low_rssi_type type)
अणु
	काष्ठा acx_low_rssi *rssi;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx low rssi");

	rssi = kzalloc(माप(*rssi), GFP_KERNEL);
	अगर (!rssi)
		वापस -ENOMEM;

	rssi->threshold = threshold;
	rssi->weight = weight;
	rssi->depth = depth;
	rssi->type = type;

	ret = wl1251_cmd_configure(wl, ACX_LOW_RSSI, rssi, माप(*rssi));
	अगर (ret < 0)
		wl1251_warning("failed to set low rssi threshold: %d", ret);

	kमुक्त(rssi);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_set_preamble(काष्ठा wl1251 *wl, क्रमागत acx_preamble_type preamble)
अणु
	काष्ठा acx_preamble *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx_set_preamble");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->preamble = preamble;

	ret = wl1251_cmd_configure(wl, ACX_PREAMBLE_TYPE, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("Setting of preamble failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_cts_protect(काष्ठा wl1251 *wl,
			   क्रमागत acx_ctsprotect_type ctsprotect)
अणु
	काष्ठा acx_ctsprotect *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx_set_ctsprotect");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->ctsprotect = ctsprotect;

	ret = wl1251_cmd_configure(wl, ACX_CTS_PROTECTION, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("Setting of ctsprotect failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_tsf_info(काष्ठा wl1251 *wl, u64 *maस_समय)
अणु
	काष्ठा acx_tsf_info *tsf_info;
	पूर्णांक ret;

	tsf_info = kzalloc(माप(*tsf_info), GFP_KERNEL);
	अगर (!tsf_info)
		वापस -ENOMEM;

	ret = wl1251_cmd_पूर्णांकerrogate(wl, ACX_TSF_INFO,
				     tsf_info, माप(*tsf_info));
	अगर (ret < 0) अणु
		wl1251_warning("ACX_FW_REV interrogate failed");
		जाओ out;
	पूर्ण

	*maस_समय = tsf_info->current_tsf_lsb |
		((u64)tsf_info->current_tsf_msb << 32);

out:
	kमुक्त(tsf_info);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_statistics(काष्ठा wl1251 *wl, काष्ठा acx_statistics *stats)
अणु
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx statistics");

	ret = wl1251_cmd_पूर्णांकerrogate(wl, ACX_STATISTICS, stats,
				     माप(*stats));
	अगर (ret < 0) अणु
		wl1251_warning("acx statistics failed: %d", ret);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wl1251_acx_rate_policies(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_rate_policy *acx;
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_ACX, "acx rate policies");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	/* configure one शेष (one-size-fits-all) rate class */
	acx->rate_class_cnt = 2;
	acx->rate_class[0].enabled_rates = ACX_RATE_MASK_UNSPECIFIED;
	acx->rate_class[0].लघु_retry_limit = ACX_RATE_RETRY_LIMIT;
	acx->rate_class[0].दीर्घ_retry_limit = ACX_RATE_RETRY_LIMIT;
	acx->rate_class[0].aflags = 0;

	/* no-retry rate class */
	acx->rate_class[1].enabled_rates = ACX_RATE_MASK_UNSPECIFIED;
	acx->rate_class[1].लघु_retry_limit = 0;
	acx->rate_class[1].दीर्घ_retry_limit = 0;
	acx->rate_class[1].aflags = 0;

	ret = wl1251_cmd_configure(wl, ACX_RATE_POLICY, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("Setting of rate policies failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_mem_cfg(काष्ठा wl1251 *wl)
अणु
	काष्ठा wl1251_acx_config_memory *mem_conf;
	पूर्णांक ret, i;

	wl1251_debug(DEBUG_ACX, "acx mem cfg");

	mem_conf = kzalloc(माप(*mem_conf), GFP_KERNEL);
	अगर (!mem_conf)
		वापस -ENOMEM;

	/* memory config */
	mem_conf->mem_config.num_stations = cpu_to_le16(DEFAULT_NUM_STATIONS);
	mem_conf->mem_config.rx_mem_block_num = 35;
	mem_conf->mem_config.tx_min_mem_block_num = 64;
	mem_conf->mem_config.num_tx_queues = MAX_TX_QUEUES;
	mem_conf->mem_config.host_अगर_options = HOSTIF_PKT_RING;
	mem_conf->mem_config.num_ssid_profiles = 1;
	mem_conf->mem_config.debug_buffer_size =
		cpu_to_le16(TRACE_BUFFER_MAX_SIZE);

	/* RX queue config */
	mem_conf->rx_queue_config.dma_address = 0;
	mem_conf->rx_queue_config.num_descs = ACX_RX_DESC_DEF;
	mem_conf->rx_queue_config.priority = DEFAULT_RXQ_PRIORITY;
	mem_conf->rx_queue_config.type = DEFAULT_RXQ_TYPE;

	/* TX queue config */
	क्रम (i = 0; i < MAX_TX_QUEUES; i++) अणु
		mem_conf->tx_queue_config[i].num_descs = ACX_TX_DESC_DEF;
		mem_conf->tx_queue_config[i].attributes = i;
	पूर्ण

	ret = wl1251_cmd_configure(wl, ACX_MEM_CFG, mem_conf,
				   माप(*mem_conf));
	अगर (ret < 0) अणु
		wl1251_warning("wl1251 mem config failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(mem_conf);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_wr_tbtt_and_dtim(काष्ठा wl1251 *wl, u16 tbtt, u8 dtim)
अणु
	काष्ठा wl1251_acx_wr_tbtt_and_dtim *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx tbtt and dtim");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->tbtt = tbtt;
	acx->dtim = dtim;

	ret = wl1251_cmd_configure(wl, ACX_WR_TBTT_AND_DTIM,
				   acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("failed to set tbtt and dtim: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_bet_enable(काष्ठा wl1251 *wl, क्रमागत wl1251_acx_bet_mode mode,
			  u8 max_consecutive)
अणु
	काष्ठा wl1251_acx_bet_enable *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx bet enable");

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->enable = mode;
	acx->max_consecutive = max_consecutive;

	ret = wl1251_cmd_configure(wl, ACX_BET_ENABLE, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("wl1251 acx bet enable failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_arp_ip_filter(काष्ठा wl1251 *wl, bool enable, __be32 address)
अणु
	काष्ठा wl1251_acx_arp_filter *acx;
	पूर्णांक ret;

	wl1251_debug(DEBUG_ACX, "acx arp ip filter, enable: %d", enable);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->version = ACX_IPV4_VERSION;
	acx->enable = enable;

	अगर (enable)
		स_नकल(acx->address, &address, ACX_IPV4_ADDR_SIZE);

	ret = wl1251_cmd_configure(wl, ACX_ARP_IP_FILTER,
				   acx, माप(*acx));
	अगर (ret < 0)
		wl1251_warning("failed to set arp ip filter: %d", ret);

	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_ac_cfg(काष्ठा wl1251 *wl, u8 ac, u8 cw_min, u16 cw_max,
		      u8 aअगरs, u16 txop)
अणु
	काष्ठा wl1251_acx_ac_cfg *acx;
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_ACX, "acx ac cfg %d cw_ming %d cw_max %d "
		     "aifs %d txop %d", ac, cw_min, cw_max, aअगरs, txop);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->ac = ac;
	acx->cw_min = cw_min;
	acx->cw_max = cw_max;
	acx->aअगरsn = aअगरs;
	acx->txop_limit = txop;

	ret = wl1251_cmd_configure(wl, ACX_AC_CFG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("acx ac cfg failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण

पूर्णांक wl1251_acx_tid_cfg(काष्ठा wl1251 *wl, u8 queue,
		       क्रमागत wl1251_acx_channel_type type,
		       u8 tsid, क्रमागत wl1251_acx_ps_scheme ps_scheme,
		       क्रमागत wl1251_acx_ack_policy ack_policy)
अणु
	काष्ठा wl1251_acx_tid_cfg *acx;
	पूर्णांक ret = 0;

	wl1251_debug(DEBUG_ACX, "acx tid cfg %d type %d tsid %d "
		     "ps_scheme %d ack_policy %d", queue, type, tsid,
		     ps_scheme, ack_policy);

	acx = kzalloc(माप(*acx), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;

	acx->queue = queue;
	acx->type = type;
	acx->tsid = tsid;
	acx->ps_scheme = ps_scheme;
	acx->ack_policy = ack_policy;

	ret = wl1251_cmd_configure(wl, ACX_TID_CFG, acx, माप(*acx));
	अगर (ret < 0) अणु
		wl1251_warning("acx tid cfg failed: %d", ret);
		जाओ out;
	पूर्ण

out:
	kमुक्त(acx);
	वापस ret;
पूर्ण
