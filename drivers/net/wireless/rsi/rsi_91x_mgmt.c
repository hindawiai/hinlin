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

#समावेश <linux/etherdevice.h>
#समावेश <linux/समयr.h>
#समावेश "rsi_mgmt.h"
#समावेश "rsi_common.h"
#समावेश "rsi_ps.h"
#समावेश "rsi_hal.h"

अटल काष्ठा bootup_params boot_params_20 = अणु
	.magic_number = cpu_to_le16(0x5aa5),
	.crystal_good_समय = 0x0,
	.valid = cpu_to_le32(VALID_20),
	.reserved_क्रम_valids = 0x0,
	.bootup_mode_info = 0x0,
	.digital_loop_back_params = 0x0,
	.rtls_बारtamp_en = 0x0,
	.host_spi_पूर्णांकr_cfg = 0x0,
	.device_clk_info = अणुअणु
		.pll_config_g = अणु
			.tapll_info_g = अणु
				.pll_reg_1 = cpu_to_le16((TA_PLL_N_VAL_20 << 8)|
					      (TA_PLL_M_VAL_20)),
				.pll_reg_2 = cpu_to_le16(TA_PLL_P_VAL_20),
			पूर्ण,
			.pll960_info_g = अणु
				.pll_reg_1 = cpu_to_le16((PLL960_P_VAL_20 << 8)|
							 (PLL960_N_VAL_20)),
				.pll_reg_2 = cpu_to_le16(PLL960_M_VAL_20),
				.pll_reg_3 = 0x0,
			पूर्ण,
			.afepll_info_g = अणु
				.pll_reg = cpu_to_le16(0x9f0),
			पूर्ण
		पूर्ण,
		.चयन_clk_g = अणु
			.चयन_clk_info = cpu_to_le16(0xb),
			.bbp_lmac_clk_reg_val = cpu_to_le16(0x111),
			.umac_घड़ी_reg_config = cpu_to_le16(0x48),
			.qspi_uart_घड़ी_reg_config = cpu_to_le16(0x1211)
		पूर्ण
	पूर्ण,
	अणु
		.pll_config_g = अणु
			.tapll_info_g = अणु
				.pll_reg_1 = cpu_to_le16((TA_PLL_N_VAL_20 << 8)|
							 (TA_PLL_M_VAL_20)),
				.pll_reg_2 = cpu_to_le16(TA_PLL_P_VAL_20),
			पूर्ण,
			.pll960_info_g = अणु
				.pll_reg_1 = cpu_to_le16((PLL960_P_VAL_20 << 8)|
							 (PLL960_N_VAL_20)),
				.pll_reg_2 = cpu_to_le16(PLL960_M_VAL_20),
				.pll_reg_3 = 0x0,
			पूर्ण,
			.afepll_info_g = अणु
				.pll_reg = cpu_to_le16(0x9f0),
			पूर्ण
		पूर्ण,
		.चयन_clk_g = अणु
			.चयन_clk_info = 0x0,
			.bbp_lmac_clk_reg_val = 0x0,
			.umac_घड़ी_reg_config = 0x0,
			.qspi_uart_घड़ी_reg_config = 0x0
		पूर्ण
	पूर्ण,
	अणु
		.pll_config_g = अणु
			.tapll_info_g = अणु
				.pll_reg_1 = cpu_to_le16((TA_PLL_N_VAL_20 << 8)|
							 (TA_PLL_M_VAL_20)),
				.pll_reg_2 = cpu_to_le16(TA_PLL_P_VAL_20),
			पूर्ण,
			.pll960_info_g = अणु
				.pll_reg_1 = cpu_to_le16((PLL960_P_VAL_20 << 8)|
							 (PLL960_N_VAL_20)),
				.pll_reg_2 = cpu_to_le16(PLL960_M_VAL_20),
				.pll_reg_3 = 0x0,
			पूर्ण,
			.afepll_info_g = अणु
				.pll_reg = cpu_to_le16(0x9f0),
			पूर्ण
		पूर्ण,
		.चयन_clk_g = अणु
			.चयन_clk_info = 0x0,
			.bbp_lmac_clk_reg_val = 0x0,
			.umac_घड़ी_reg_config = 0x0,
			.qspi_uart_घड़ी_reg_config = 0x0
		पूर्ण
	पूर्ण पूर्ण,
	.buckboost_wakeup_cnt = 0x0,
	.pmu_wakeup_रुको = 0x0,
	.shutकरोwn_रुको_समय = 0x0,
	.pmu_slp_clkout_sel = 0x0,
	.wdt_prog_value = 0x0,
	.wdt_soc_rst_delay = 0x0,
	.dcdc_operation_mode = 0x0,
	.soc_reset_रुको_cnt = 0x0,
	.रुकोing_समय_at_fresh_sleep = 0x0,
	.max_threshold_to_aव्योम_sleep = 0x0,
	.beacon_resedue_alg_en = 0,
पूर्ण;

अटल काष्ठा bootup_params boot_params_40 = अणु
	.magic_number = cpu_to_le16(0x5aa5),
	.crystal_good_समय = 0x0,
	.valid = cpu_to_le32(VALID_40),
	.reserved_क्रम_valids = 0x0,
	.bootup_mode_info = 0x0,
	.digital_loop_back_params = 0x0,
	.rtls_बारtamp_en = 0x0,
	.host_spi_पूर्णांकr_cfg = 0x0,
	.device_clk_info = अणुअणु
		.pll_config_g = अणु
			.tapll_info_g = अणु
				.pll_reg_1 = cpu_to_le16((TA_PLL_N_VAL_40 << 8)|
							 (TA_PLL_M_VAL_40)),
				.pll_reg_2 = cpu_to_le16(TA_PLL_P_VAL_40),
			पूर्ण,
			.pll960_info_g = अणु
				.pll_reg_1 = cpu_to_le16((PLL960_P_VAL_40 << 8)|
							 (PLL960_N_VAL_40)),
				.pll_reg_2 = cpu_to_le16(PLL960_M_VAL_40),
				.pll_reg_3 = 0x0,
			पूर्ण,
			.afepll_info_g = अणु
				.pll_reg = cpu_to_le16(0x9f0),
			पूर्ण
		पूर्ण,
		.चयन_clk_g = अणु
			.चयन_clk_info = cpu_to_le16(0x09),
			.bbp_lmac_clk_reg_val = cpu_to_le16(0x1121),
			.umac_घड़ी_reg_config = cpu_to_le16(0x48),
			.qspi_uart_घड़ी_reg_config = cpu_to_le16(0x1211)
		पूर्ण
	पूर्ण,
	अणु
		.pll_config_g = अणु
			.tapll_info_g = अणु
				.pll_reg_1 = cpu_to_le16((TA_PLL_N_VAL_40 << 8)|
							 (TA_PLL_M_VAL_40)),
				.pll_reg_2 = cpu_to_le16(TA_PLL_P_VAL_40),
			पूर्ण,
			.pll960_info_g = अणु
				.pll_reg_1 = cpu_to_le16((PLL960_P_VAL_40 << 8)|
							 (PLL960_N_VAL_40)),
				.pll_reg_2 = cpu_to_le16(PLL960_M_VAL_40),
				.pll_reg_3 = 0x0,
			पूर्ण,
			.afepll_info_g = अणु
				.pll_reg = cpu_to_le16(0x9f0),
			पूर्ण
		पूर्ण,
		.चयन_clk_g = अणु
			.चयन_clk_info = 0x0,
			.bbp_lmac_clk_reg_val = 0x0,
			.umac_घड़ी_reg_config = 0x0,
			.qspi_uart_घड़ी_reg_config = 0x0
		पूर्ण
	पूर्ण,
	अणु
		.pll_config_g = अणु
			.tapll_info_g = अणु
				.pll_reg_1 = cpu_to_le16((TA_PLL_N_VAL_40 << 8)|
							 (TA_PLL_M_VAL_40)),
				.pll_reg_2 = cpu_to_le16(TA_PLL_P_VAL_40),
			पूर्ण,
			.pll960_info_g = अणु
				.pll_reg_1 = cpu_to_le16((PLL960_P_VAL_40 << 8)|
							 (PLL960_N_VAL_40)),
				.pll_reg_2 = cpu_to_le16(PLL960_M_VAL_40),
				.pll_reg_3 = 0x0,
			पूर्ण,
			.afepll_info_g = अणु
				.pll_reg = cpu_to_le16(0x9f0),
			पूर्ण
		पूर्ण,
		.चयन_clk_g = अणु
			.चयन_clk_info = 0x0,
			.bbp_lmac_clk_reg_val = 0x0,
			.umac_घड़ी_reg_config = 0x0,
			.qspi_uart_घड़ी_reg_config = 0x0
		पूर्ण
	पूर्ण पूर्ण,
	.buckboost_wakeup_cnt = 0x0,
	.pmu_wakeup_रुको = 0x0,
	.shutकरोwn_रुको_समय = 0x0,
	.pmu_slp_clkout_sel = 0x0,
	.wdt_prog_value = 0x0,
	.wdt_soc_rst_delay = 0x0,
	.dcdc_operation_mode = 0x0,
	.soc_reset_रुको_cnt = 0x0,
	.रुकोing_समय_at_fresh_sleep = 0x0,
	.max_threshold_to_aव्योम_sleep = 0x0,
	.beacon_resedue_alg_en = 0,
पूर्ण;

अटल काष्ठा bootup_params_9116 boot_params_9116_20 = अणु
	.magic_number = cpu_to_le16(LOADED_TOKEN),
	.valid = cpu_to_le32(VALID_20),
	.device_clk_info_9116 = अणुअणु
		.pll_config_9116_g = अणु
			.pll_ctrl_set_reg = cpu_to_le16(0xd518),
			.pll_ctrl_clr_reg = cpu_to_le16(0x2ae7),
			.pll_modem_conig_reg = cpu_to_le16(0x2000),
			.soc_clk_config_reg = cpu_to_le16(0x0c18),
			.adc_dac_strm1_config_reg = cpu_to_le16(0x1100),
			.adc_dac_strm2_config_reg = cpu_to_le16(0x6600),
		पूर्ण,
		.चयन_clk_9116_g = अणु
			.चयन_clk_info =
				cpu_to_le32((RSI_SWITCH_TASS_CLK |
					    RSI_SWITCH_WLAN_BBP_LMAC_CLK_REG |
					    RSI_SWITCH_BBP_LMAC_CLK_REG)),
			.tass_घड़ी_reg = cpu_to_le32(0x083C0503),
			.wlan_bbp_lmac_clk_reg_val = cpu_to_le32(0x01042001),
			.zbbt_bbp_lmac_clk_reg_val = cpu_to_le32(0x02010001),
			.bbp_lmac_clk_en_val = cpu_to_le32(0x0000003b),
		पूर्ण
	पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा bootup_params_9116 boot_params_9116_40 = अणु
	.magic_number = cpu_to_le16(LOADED_TOKEN),
	.valid = cpu_to_le32(VALID_40),
	.device_clk_info_9116 = अणुअणु
		.pll_config_9116_g = अणु
			.pll_ctrl_set_reg = cpu_to_le16(0xd518),
			.pll_ctrl_clr_reg = cpu_to_le16(0x2ae7),
			.pll_modem_conig_reg = cpu_to_le16(0x3000),
			.soc_clk_config_reg = cpu_to_le16(0x0c18),
			.adc_dac_strm1_config_reg = cpu_to_le16(0x0000),
			.adc_dac_strm2_config_reg = cpu_to_le16(0x6600),
		पूर्ण,
		.चयन_clk_9116_g = अणु
			.चयन_clk_info =
				cpu_to_le32((RSI_SWITCH_TASS_CLK |
					    RSI_SWITCH_WLAN_BBP_LMAC_CLK_REG |
					    RSI_SWITCH_BBP_LMAC_CLK_REG |
					    RSI_MODEM_CLK_160MHZ)),
			.tass_घड़ी_reg = cpu_to_le32(0x083C0503),
			.wlan_bbp_lmac_clk_reg_val = cpu_to_le32(0x01042002),
			.zbbt_bbp_lmac_clk_reg_val = cpu_to_le32(0x04010002),
			.bbp_lmac_clk_en_val = cpu_to_le32(0x0000003b),
		पूर्ण
	पूर्ण,
	पूर्ण,
पूर्ण;

अटल u16 mcs[] = अणु13, 26, 39, 52, 78, 104, 117, 130पूर्ण;

/**
 * rsi_set_शेष_parameters() - This function sets शेष parameters.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: none
 */
अटल व्योम rsi_set_शेष_parameters(काष्ठा rsi_common *common)
अणु
	common->band = NL80211_BAND_2GHZ;
	common->channel_width = BW_20MHZ;
	common->rts_threshold = IEEE80211_MAX_RTS_THRESHOLD;
	common->channel = 1;
	common->min_rate = 0xffff;
	common->fsm_state = FSM_CARD_NOT_READY;
	common->अगरace_करोwn = true;
	common->endpoपूर्णांक = EP_2GHZ_20MHZ;
	common->driver_mode = 1; /* End to end mode */
	common->lp_ps_handshake_mode = 0; /* Default no handShake mode*/
	common->ulp_ps_handshake_mode = 2; /* Default PKT handShake mode*/
	common->rf_घातer_val = 0; /* Default 1.9V */
	common->wlan_rf_घातer_mode = 0;
	common->obm_ant_sel_val = 2;
	common->beacon_पूर्णांकerval = RSI_BEACON_INTERVAL;
	common->dtim_cnt = RSI_DTIM_COUNT;
	common->w9116_features.pll_mode = 0x0;
	common->w9116_features.rf_type = 1;
	common->w9116_features.wireless_mode = 0;
	common->w9116_features.enable_ppe = 0;
	common->w9116_features.afe_type = 1;
	common->w9116_features.dpd = 0;
	common->w9116_features.sअगरs_tx_enable = 0;
	common->w9116_features.ps_options = 0;
पूर्ण

व्योम init_bgscan_params(काष्ठा rsi_common *common)
अणु
	स_रखो((u8 *)&common->bgscan, 0, माप(काष्ठा rsi_bgscan_params));
	common->bgscan.bgscan_threshold = RSI_DEF_BGSCAN_THRLD;
	common->bgscan.roam_threshold = RSI_DEF_ROAM_THRLD;
	common->bgscan.bgscan_periodicity = RSI_BGSCAN_PERIODICITY;
	common->bgscan.num_bgscan_channels = 0;
	common->bgscan.two_probe = 1;
	common->bgscan.active_scan_duration = RSI_ACTIVE_SCAN_TIME;
	common->bgscan.passive_scan_duration = RSI_PASSIVE_SCAN_TIME;
पूर्ण

/**
 * rsi_set_contention_vals() - This function sets the contention values क्रम the
 *			       backoff procedure.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: None.
 */
अटल व्योम rsi_set_contention_vals(काष्ठा rsi_common *common)
अणु
	u8 ii = 0;

	क्रम (; ii < NUM_EDCA_QUEUES; ii++) अणु
		common->tx_qinfo[ii].wme_params =
			(((common->edca_params[ii].cw_min / 2) +
			  (common->edca_params[ii].aअगरs)) *
			  WMM_SHORT_SLOT_TIME + SIFS_DURATION);
		common->tx_qinfo[ii].weight = common->tx_qinfo[ii].wme_params;
		common->tx_qinfo[ii].pkt_contended = 0;
	पूर्ण
पूर्ण

/**
 * rsi_send_पूर्णांकernal_mgmt_frame() - This function sends management frames to
 *				    firmware.Also schedules packet to queue
 *				    क्रम transmission.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @skb: Poपूर्णांकer to the socket buffer काष्ठाure.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_send_पूर्णांकernal_mgmt_frame(काष्ठा rsi_common *common,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा skb_info *tx_params;
	काष्ठा rsi_cmd_desc *desc;

	अगर (skb == शून्य) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to allocate skb\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	desc = (काष्ठा rsi_cmd_desc *)skb->data;
	desc->desc_dword0.len_qno |= cpu_to_le16(DESC_IMMEDIATE_WAKEUP);
	skb->priority = MGMT_SOFT_Q;
	tx_params = (काष्ठा skb_info *)&IEEE80211_SKB_CB(skb)->driver_data;
	tx_params->flags |= INTERNAL_MGMT_PKT;
	skb_queue_tail(&common->tx_queue[MGMT_SOFT_Q], skb);
	rsi_set_event(&common->tx_thपढ़ो.event);
	वापस 0;
पूर्ण

/**
 * rsi_load_radio_caps() - This function is used to send radio capabilities
 *			   values to firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: 0 on success, corresponding negative error code on failure.
 */
अटल पूर्णांक rsi_load_radio_caps(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_radio_caps *radio_caps;
	काष्ठा rsi_hw *adapter = common->priv;
	u16 inx = 0;
	u8 ii;
	u8 radio_id = 0;
	u16 gc[20] = अणु0xf0, 0xf0, 0xf0, 0xf0,
		      0xf0, 0xf0, 0xf0, 0xf0,
		      0xf0, 0xf0, 0xf0, 0xf0,
		      0xf0, 0xf0, 0xf0, 0xf0,
		      0xf0, 0xf0, 0xf0, 0xf0पूर्ण;
	काष्ठा sk_buff *skb;
	u16 frame_len = माप(काष्ठा rsi_radio_caps);

	rsi_dbg(INFO_ZONE, "%s: Sending rate symbol req frame\n", __func__);

	skb = dev_alloc_skb(frame_len);

	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, frame_len);
	radio_caps = (काष्ठा rsi_radio_caps *)skb->data;

	radio_caps->desc_dword0.frame_type = RADIO_CAPABILITIES;
	radio_caps->channel_num = common->channel;
	radio_caps->rf_model = RSI_RF_TYPE;

	radio_caps->radio_cfg_info = RSI_LMAC_CLOCK_80MHZ;
	अगर (common->channel_width == BW_40MHZ) अणु
		radio_caps->radio_cfg_info |= RSI_ENABLE_40MHZ;

		अगर (common->fsm_state == FSM_MAC_INIT_DONE) अणु
			काष्ठा ieee80211_hw *hw = adapter->hw;
			काष्ठा ieee80211_conf *conf = &hw->conf;

			अगर (conf_is_ht40_plus(conf)) अणु
				radio_caps->ppe_ack_rate =
					cpu_to_le16(LOWER_20_ENABLE |
						    (LOWER_20_ENABLE >> 12));
			पूर्ण अन्यथा अगर (conf_is_ht40_minus(conf)) अणु
				radio_caps->ppe_ack_rate =
					cpu_to_le16(UPPER_20_ENABLE |
						    (UPPER_20_ENABLE >> 12));
			पूर्ण अन्यथा अणु
				radio_caps->ppe_ack_rate =
					cpu_to_le16((BW_40MHZ << 12) |
						    FULL40M_ENABLE);
			पूर्ण
		पूर्ण
	पूर्ण
	radio_caps->radio_info |= radio_id;

	अगर (adapter->device_model == RSI_DEV_9116 &&
	    common->channel_width == BW_20MHZ)
		radio_caps->radio_cfg_info &= ~0x3;

	radio_caps->sअगरs_tx_11n = cpu_to_le16(SIFS_TX_11N_VALUE);
	radio_caps->sअगरs_tx_11b = cpu_to_le16(SIFS_TX_11B_VALUE);
	radio_caps->slot_rx_11n = cpu_to_le16(SHORT_SLOT_VALUE);
	radio_caps->ofdm_ack_tout = cpu_to_le16(OFDM_ACK_TOUT_VALUE);
	radio_caps->cck_ack_tout = cpu_to_le16(CCK_ACK_TOUT_VALUE);
	radio_caps->preamble_type = cpu_to_le16(LONG_PREAMBLE);

	क्रम (ii = 0; ii < MAX_HW_QUEUES; ii++) अणु
		radio_caps->qos_params[ii].cont_win_min_q = cpu_to_le16(3);
		radio_caps->qos_params[ii].cont_win_max_q = cpu_to_le16(0x3f);
		radio_caps->qos_params[ii].aअगरsn_val_q = cpu_to_le16(2);
		radio_caps->qos_params[ii].txop_q = 0;
	पूर्ण

	क्रम (ii = 0; ii < NUM_EDCA_QUEUES; ii++) अणु
		अगर (common->edca_params[ii].cw_max > 0) अणु
			radio_caps->qos_params[ii].cont_win_min_q =
				cpu_to_le16(common->edca_params[ii].cw_min);
			radio_caps->qos_params[ii].cont_win_max_q =
				cpu_to_le16(common->edca_params[ii].cw_max);
			radio_caps->qos_params[ii].aअगरsn_val_q =
				cpu_to_le16(common->edca_params[ii].aअगरs << 8);
			radio_caps->qos_params[ii].txop_q =
				cpu_to_le16(common->edca_params[ii].txop);
		पूर्ण
	पूर्ण

	radio_caps->qos_params[BROADCAST_HW_Q].txop_q = cpu_to_le16(0xffff);
	radio_caps->qos_params[MGMT_HW_Q].txop_q = 0;
	radio_caps->qos_params[BEACON_HW_Q].txop_q = cpu_to_le16(0xffff);

	स_नकल(&common->rate_pwr[0], &gc[0], 40);
	क्रम (ii = 0; ii < 20; ii++)
		radio_caps->gcpd_per_rate[inx++] =
			cpu_to_le16(common->rate_pwr[ii]  & 0x00FF);

	rsi_set_len_qno(&radio_caps->desc_dword0.len_qno,
			(frame_len - FRAME_DESC_SZ), RSI_WIFI_MGMT_Q);

	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_mgmt_pkt_to_core() - This function is the entry poपूर्णांक क्रम Mgmt module.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @msg: Poपूर्णांकer to received packet.
 * @msg_len: Length of the received packet.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_mgmt_pkt_to_core(काष्ठा rsi_common *common,
				u8 *msg,
				s32 msg_len)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा skb_info *rx_params;
	u8 pad_bytes = msg[4];
	काष्ठा sk_buff *skb;

	अगर (!adapter->sc_nvअगरs)
		वापस -ENOLINK;

	msg_len -= pad_bytes;
	अगर (msg_len <= 0) अणु
		rsi_dbg(MGMT_RX_ZONE,
			"%s: Invalid rx msg of len = %d\n",
			__func__, msg_len);
		वापस -EINVAL;
	पूर्ण

	skb = dev_alloc_skb(msg_len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb,
		     (u8 *)(msg + FRAME_DESC_SZ + pad_bytes),
		     msg_len);

	info = IEEE80211_SKB_CB(skb);
	rx_params = (काष्ठा skb_info *)info->driver_data;
	rx_params->rssi = rsi_get_rssi(msg);
	rx_params->channel = rsi_get_channel(msg);
	rsi_indicate_pkt_to_os(common, skb);

	वापस 0;
पूर्ण

/**
 * rsi_hal_send_sta_notअगरy_frame() - This function sends the station notअगरy
 *				     frame to firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @opmode: Operating mode of device.
 * @notअगरy_event: Notअगरication about station connection.
 * @bssid: bssid.
 * @qos_enable: Qos is enabled.
 * @aid: Aid (unique क्रम all STA).
 * @sta_id: station id.
 * @vअगर: Poपूर्णांकer to the ieee80211_vअगर काष्ठाure.
 *
 * Return: status: 0 on success, corresponding negative error code on failure.
 */
पूर्णांक rsi_hal_send_sta_notअगरy_frame(काष्ठा rsi_common *common, क्रमागत opmode opmode,
				  u8 notअगरy_event, स्थिर अचिन्हित अक्षर *bssid,
				  u8 qos_enable, u16 aid, u16 sta_id,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rsi_peer_notअगरy *peer_notअगरy;
	u16 vap_id = ((काष्ठा vअगर_priv *)vअगर->drv_priv)->vap_id;
	पूर्णांक status;
	u16 frame_len = माप(काष्ठा rsi_peer_notअगरy);

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending sta notify frame\n", __func__);

	skb = dev_alloc_skb(frame_len);

	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, frame_len);
	peer_notअगरy = (काष्ठा rsi_peer_notअगरy *)skb->data;

	अगर (opmode == RSI_OPMODE_STA)
		peer_notअगरy->command = cpu_to_le16(PEER_TYPE_AP << 1);
	अन्यथा अगर (opmode == RSI_OPMODE_AP)
		peer_notअगरy->command = cpu_to_le16(PEER_TYPE_STA << 1);

	चयन (notअगरy_event) अणु
	हाल STA_CONNECTED:
		peer_notअगरy->command |= cpu_to_le16(RSI_ADD_PEER);
		अवरोध;
	हाल STA_DISCONNECTED:
		peer_notअगरy->command |= cpu_to_le16(RSI_DELETE_PEER);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	peer_notअगरy->command |= cpu_to_le16((aid & 0xfff) << 4);
	ether_addr_copy(peer_notअगरy->mac_addr, bssid);
	peer_notअगरy->mpdu_density = cpu_to_le16(RSI_MPDU_DENSITY);
	peer_notअगरy->sta_flags = cpu_to_le32((qos_enable) ? 1 : 0);

	rsi_set_len_qno(&peer_notअगरy->desc.desc_dword0.len_qno,
			(frame_len - FRAME_DESC_SZ),
			RSI_WIFI_MGMT_Q);
	peer_notअगरy->desc.desc_dword0.frame_type = PEER_NOTIFY;
	peer_notअगरy->desc.desc_dword3.qid_tid = sta_id;
	peer_notअगरy->desc.desc_dword3.sta_id = vap_id;

	skb_put(skb, frame_len);

	status = rsi_send_पूर्णांकernal_mgmt_frame(common, skb);

	अगर ((vअगर->type == NL80211_IFTYPE_STATION) &&
	    (!status && qos_enable)) अणु
		rsi_set_contention_vals(common);
		status = rsi_load_radio_caps(common);
	पूर्ण
	वापस status;
पूर्ण

/**
 * rsi_send_aggregation_params_frame() - This function sends the ampdu
 *					 indication frame to firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @tid: traffic identअगरier.
 * @ssn: ssn.
 * @buf_size: buffer size.
 * @event: notअगरication about station connection.
 * @sta_id: station id.
 *
 * Return: 0 on success, corresponding negative error code on failure.
 */
पूर्णांक rsi_send_aggregation_params_frame(काष्ठा rsi_common *common,
				      u16 tid,
				      u16 ssn,
				      u8 buf_size,
				      u8 event,
				      u8 sta_id)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rsi_aggr_params *aggr_params;
	u16 frame_len = माप(काष्ठा rsi_aggr_params);

	skb = dev_alloc_skb(frame_len);

	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, frame_len);
	aggr_params = (काष्ठा rsi_aggr_params *)skb->data;

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending AMPDU indication frame\n", __func__);

	rsi_set_len_qno(&aggr_params->desc_dword0.len_qno, 0, RSI_WIFI_MGMT_Q);
	aggr_params->desc_dword0.frame_type = AMPDU_IND;

	aggr_params->aggr_params = tid & RSI_AGGR_PARAMS_TID_MASK;
	aggr_params->peer_id = sta_id;
	अगर (event == STA_TX_ADDBA_DONE) अणु
		aggr_params->seq_start = cpu_to_le16(ssn);
		aggr_params->baw_size = cpu_to_le16(buf_size);
		aggr_params->aggr_params |= RSI_AGGR_PARAMS_START;
	पूर्ण अन्यथा अगर (event == STA_RX_ADDBA_DONE) अणु
		aggr_params->seq_start = cpu_to_le16(ssn);
		aggr_params->aggr_params |= (RSI_AGGR_PARAMS_START |
					     RSI_AGGR_PARAMS_RX_AGGR);
	पूर्ण अन्यथा अगर (event == STA_RX_DELBA) अणु
		aggr_params->aggr_params |= RSI_AGGR_PARAMS_RX_AGGR;
	पूर्ण

	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_program_bb_rf() - This function starts base band and RF programming.
 *			 This is called after initial configurations are करोne.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: 0 on success, corresponding negative error code on failure.
 */
अटल पूर्णांक rsi_program_bb_rf(काष्ठा rsi_common *common)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rsi_bb_rf_prog *bb_rf_prog;
	u16 frame_len = माप(काष्ठा rsi_bb_rf_prog);

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending program BB/RF frame\n", __func__);

	skb = dev_alloc_skb(frame_len);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, frame_len);
	bb_rf_prog = (काष्ठा rsi_bb_rf_prog *)skb->data;

	rsi_set_len_qno(&bb_rf_prog->desc_dword0.len_qno, 0, RSI_WIFI_MGMT_Q);
	bb_rf_prog->desc_dword0.frame_type = BBP_PROG_IN_TA;
	bb_rf_prog->endpoपूर्णांक = common->endpoपूर्णांक;
	bb_rf_prog->rf_घातer_mode = common->wlan_rf_घातer_mode;

	अगर (common->rf_reset) अणु
		bb_rf_prog->flags =  cpu_to_le16(RF_RESET_ENABLE);
		rsi_dbg(MGMT_TX_ZONE, "%s: ===> RF RESET REQUEST SENT <===\n",
			__func__);
		common->rf_reset = 0;
	पूर्ण
	common->bb_rf_prog_count = 1;
	bb_rf_prog->flags |= cpu_to_le16(PUT_BBP_RESET | BBP_REG_WRITE |
					 (RSI_RF_TYPE << 4));
	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_set_vap_capabilities() - This function send vap capability to firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @mode: Operating mode of device.
 * @mac_addr: MAC address
 * @vap_id: Rate inक्रमmation - offset and mask
 * @vap_status: VAP status - ADD, DELETE or UPDATE
 *
 * Return: 0 on success, corresponding negative error code on failure.
 */
पूर्णांक rsi_set_vap_capabilities(काष्ठा rsi_common *common,
			     क्रमागत opmode mode,
			     u8 *mac_addr,
			     u8 vap_id,
			     u8 vap_status)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rsi_vap_caps *vap_caps;
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा ieee80211_hw *hw = adapter->hw;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	u16 frame_len = माप(काष्ठा rsi_vap_caps);

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending VAP capabilities frame\n", __func__);

	skb = dev_alloc_skb(frame_len);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, frame_len);
	vap_caps = (काष्ठा rsi_vap_caps *)skb->data;

	rsi_set_len_qno(&vap_caps->desc_dword0.len_qno,
			(frame_len - FRAME_DESC_SZ), RSI_WIFI_MGMT_Q);
	vap_caps->desc_dword0.frame_type = VAP_CAPABILITIES;
	vap_caps->status = vap_status;
	vap_caps->vअगर_type = mode;
	vap_caps->channel_bw = common->channel_width;
	vap_caps->vap_id = vap_id;
	vap_caps->radioid_macid = ((common->mac_id & 0xf) << 4) |
				   (common->radio_id & 0xf);

	स_नकल(vap_caps->mac_addr, mac_addr, IEEE80211_ADDR_LEN);
	vap_caps->keep_alive_period = cpu_to_le16(90);
	vap_caps->frag_threshold = cpu_to_le16(IEEE80211_MAX_FRAG_THRESHOLD);

	vap_caps->rts_threshold = cpu_to_le16(common->rts_threshold);

	अगर (common->band == NL80211_BAND_5GHZ) अणु
		vap_caps->शेष_ctrl_rate = cpu_to_le16(RSI_RATE_6);
		vap_caps->शेष_mgmt_rate = cpu_to_le32(RSI_RATE_6);
	पूर्ण अन्यथा अणु
		vap_caps->शेष_ctrl_rate = cpu_to_le16(RSI_RATE_1);
		vap_caps->शेष_mgmt_rate = cpu_to_le32(RSI_RATE_1);
	पूर्ण
	अगर (conf_is_ht40(conf)) अणु
		अगर (conf_is_ht40_minus(conf))
			vap_caps->ctrl_rate_flags =
				cpu_to_le16(UPPER_20_ENABLE);
		अन्यथा अगर (conf_is_ht40_plus(conf))
			vap_caps->ctrl_rate_flags =
				cpu_to_le16(LOWER_20_ENABLE);
		अन्यथा
			vap_caps->ctrl_rate_flags =
				cpu_to_le16(FULL40M_ENABLE);
	पूर्ण

	vap_caps->शेष_data_rate = 0;
	vap_caps->beacon_पूर्णांकerval = cpu_to_le16(common->beacon_पूर्णांकerval);
	vap_caps->dtim_period = cpu_to_le16(common->dtim_cnt);

	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_hal_load_key() - This function is used to load keys within the firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @data: Poपूर्णांकer to the key data.
 * @key_len: Key length to be loaded.
 * @key_type: Type of key: GROUP/PAIRWISE.
 * @key_id: Key index.
 * @cipher: Type of cipher used.
 * @sta_id: Station id.
 * @vअगर: Poपूर्णांकer to the ieee80211_vअगर काष्ठाure.
 *
 * Return: 0 on success, -1 on failure.
 */
पूर्णांक rsi_hal_load_key(काष्ठा rsi_common *common,
		     u8 *data,
		     u16 key_len,
		     u8 key_type,
		     u8 key_id,
		     u32 cipher,
		     s16 sta_id,
		     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rsi_set_key *set_key;
	u16 key_descriptor = 0;
	u16 frame_len = माप(काष्ठा rsi_set_key);

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending load key frame\n", __func__);

	skb = dev_alloc_skb(frame_len);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, frame_len);
	set_key = (काष्ठा rsi_set_key *)skb->data;

	अगर (key_type == RSI_GROUP_KEY) अणु
		key_descriptor = RSI_KEY_TYPE_BROADCAST;
		अगर (vअगर->type == NL80211_IFTYPE_AP)
			key_descriptor |= RSI_KEY_MODE_AP;
	पूर्ण
	अगर ((cipher == WLAN_CIPHER_SUITE_WEP40) ||
	    (cipher == WLAN_CIPHER_SUITE_WEP104)) अणु
		key_id = 0;
		key_descriptor |= RSI_WEP_KEY;
		अगर (key_len >= 13)
			key_descriptor |= RSI_WEP_KEY_104;
	पूर्ण अन्यथा अगर (cipher != KEY_TYPE_CLEAR) अणु
		key_descriptor |= RSI_CIPHER_WPA;
		अगर (cipher == WLAN_CIPHER_SUITE_TKIP)
			key_descriptor |= RSI_CIPHER_TKIP;
	पूर्ण
	key_descriptor |= RSI_PROTECT_DATA_FRAMES;
	key_descriptor |= (key_id << RSI_KEY_ID_OFFSET);

	rsi_set_len_qno(&set_key->desc_dword0.len_qno,
			(frame_len - FRAME_DESC_SZ), RSI_WIFI_MGMT_Q);
	set_key->desc_dword0.frame_type = SET_KEY_REQ;
	set_key->key_desc = cpu_to_le16(key_descriptor);
	set_key->sta_id = sta_id;

	अगर (data) अणु
		अगर ((cipher == WLAN_CIPHER_SUITE_WEP40) ||
		    (cipher == WLAN_CIPHER_SUITE_WEP104)) अणु
			स_नकल(&set_key->key[key_id][1], data, key_len * 2);
		पूर्ण अन्यथा अणु
			स_नकल(&set_key->key[0][0], data, key_len);
		पूर्ण
		स_नकल(set_key->tx_mic_key, &data[16], 8);
		स_नकल(set_key->rx_mic_key, &data[24], 8);
	पूर्ण अन्यथा अणु
		स_रखो(&set_key[FRAME_DESC_SZ], 0, frame_len - FRAME_DESC_SZ);
	पूर्ण

	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/*
 * This function sends the common device configuration parameters to device.
 * This frame includes the useful inक्रमmation to make device works on
 * specअगरic operating mode.
 */
अटल पूर्णांक rsi_send_common_dev_params(काष्ठा rsi_common *common)
अणु
	काष्ठा sk_buff *skb;
	u16 frame_len;
	काष्ठा rsi_config_vals *dev_cfgs;

	frame_len = माप(काष्ठा rsi_config_vals);

	rsi_dbg(MGMT_TX_ZONE, "Sending common device config params\n");
	skb = dev_alloc_skb(frame_len);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Unable to allocate skb\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, frame_len);

	dev_cfgs = (काष्ठा rsi_config_vals *)skb->data;
	स_रखो(dev_cfgs, 0, (माप(काष्ठा rsi_config_vals)));

	rsi_set_len_qno(&dev_cfgs->len_qno, (frame_len - FRAME_DESC_SZ),
			RSI_COEX_Q);
	dev_cfgs->pkt_type = COMMON_DEV_CONFIG;

	dev_cfgs->lp_ps_handshake = common->lp_ps_handshake_mode;
	dev_cfgs->ulp_ps_handshake = common->ulp_ps_handshake_mode;

	dev_cfgs->unused_ulp_gpio = RSI_UNUSED_ULP_GPIO_BITMAP;
	dev_cfgs->unused_soc_gpio_biपंचांगap =
				cpu_to_le32(RSI_UNUSED_SOC_GPIO_BITMAP);

	dev_cfgs->opermode = common->oper_mode;
	dev_cfgs->wlan_rf_pwr_mode = common->wlan_rf_घातer_mode;
	dev_cfgs->driver_mode = common->driver_mode;
	dev_cfgs->region_code = NL80211_DFS_FCC;
	dev_cfgs->antenna_sel_val = common->obm_ant_sel_val;

	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/*
 * rsi_load_bootup_params() - This function send bootup params to the firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: 0 on success, corresponding error code on failure.
 */
अटल पूर्णांक rsi_load_bootup_params(काष्ठा rsi_common *common)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rsi_boot_params *boot_params;

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending boot params frame\n", __func__);
	skb = dev_alloc_skb(माप(काष्ठा rsi_boot_params));
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, माप(काष्ठा rsi_boot_params));
	boot_params = (काष्ठा rsi_boot_params *)skb->data;

	rsi_dbg(MGMT_TX_ZONE, "%s:\n", __func__);

	अगर (common->channel_width == BW_40MHZ) अणु
		स_नकल(&boot_params->bootup_params,
		       &boot_params_40,
		       माप(काष्ठा bootup_params));
		rsi_dbg(MGMT_TX_ZONE, "%s: Packet 40MHZ <=== %d\n", __func__,
			UMAC_CLK_40BW);
		boot_params->desc_word[7] = cpu_to_le16(UMAC_CLK_40BW);
	पूर्ण अन्यथा अणु
		स_नकल(&boot_params->bootup_params,
		       &boot_params_20,
		       माप(काष्ठा bootup_params));
		अगर (boot_params_20.valid != cpu_to_le32(VALID_20)) अणु
			boot_params->desc_word[7] = cpu_to_le16(UMAC_CLK_20BW);
			rsi_dbg(MGMT_TX_ZONE,
				"%s: Packet 20MHZ <=== %d\n", __func__,
				UMAC_CLK_20BW);
		पूर्ण अन्यथा अणु
			boot_params->desc_word[7] = cpu_to_le16(UMAC_CLK_40MHZ);
			rsi_dbg(MGMT_TX_ZONE,
				"%s: Packet 20MHZ <=== %d\n", __func__,
				UMAC_CLK_40MHZ);
		पूर्ण
	पूर्ण

	/**
	 * Bitअणु0:11पूर्ण indicates length of the Packet
	 * Bitअणु12:15पूर्ण indicates host queue number
	 */
	boot_params->desc_word[0] = cpu_to_le16(माप(काष्ठा bootup_params) |
				    (RSI_WIFI_MGMT_Q << 12));
	boot_params->desc_word[1] = cpu_to_le16(BOOTUP_PARAMS_REQUEST);

	skb_put(skb, माप(काष्ठा rsi_boot_params));

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

अटल पूर्णांक rsi_load_9116_bootup_params(काष्ठा rsi_common *common)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rsi_boot_params_9116 *boot_params;

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending boot params frame\n", __func__);

	skb = dev_alloc_skb(माप(काष्ठा rsi_boot_params_9116));
	अगर (!skb)
		वापस -ENOMEM;
	स_रखो(skb->data, 0, माप(काष्ठा rsi_boot_params));
	boot_params = (काष्ठा rsi_boot_params_9116 *)skb->data;

	अगर (common->channel_width == BW_40MHZ) अणु
		स_नकल(&boot_params->bootup_params,
		       &boot_params_9116_40,
		       माप(काष्ठा bootup_params_9116));
		rsi_dbg(MGMT_TX_ZONE, "%s: Packet 40MHZ <=== %d\n", __func__,
			UMAC_CLK_40BW);
		boot_params->umac_clk = cpu_to_le16(UMAC_CLK_40BW);
	पूर्ण अन्यथा अणु
		स_नकल(&boot_params->bootup_params,
		       &boot_params_9116_20,
		       माप(काष्ठा bootup_params_9116));
		अगर (boot_params_20.valid != cpu_to_le32(VALID_20)) अणु
			boot_params->umac_clk = cpu_to_le16(UMAC_CLK_20BW);
			rsi_dbg(MGMT_TX_ZONE,
				"%s: Packet 20MHZ <=== %d\n", __func__,
				UMAC_CLK_20BW);
		पूर्ण अन्यथा अणु
			boot_params->umac_clk = cpu_to_le16(UMAC_CLK_40MHZ);
			rsi_dbg(MGMT_TX_ZONE,
				"%s: Packet 20MHZ <=== %d\n", __func__,
				UMAC_CLK_40MHZ);
		पूर्ण
	पूर्ण
	rsi_set_len_qno(&boot_params->desc_dword0.len_qno,
			माप(काष्ठा bootup_params_9116), RSI_WIFI_MGMT_Q);
	boot_params->desc_dword0.frame_type = BOOTUP_PARAMS_REQUEST;
	skb_put(skb, माप(काष्ठा rsi_boot_params_9116));

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_send_reset_mac() - This function prepares reset MAC request and sends an
 *			  पूर्णांकernal management frame to indicate it to firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: 0 on success, corresponding error code on failure.
 */
अटल पूर्णांक rsi_send_reset_mac(काष्ठा rsi_common *common)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rsi_mac_frame *mgmt_frame;

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending reset MAC frame\n", __func__);

	skb = dev_alloc_skb(FRAME_DESC_SZ);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, FRAME_DESC_SZ);
	mgmt_frame = (काष्ठा rsi_mac_frame *)skb->data;

	mgmt_frame->desc_word[0] = cpu_to_le16(RSI_WIFI_MGMT_Q << 12);
	mgmt_frame->desc_word[1] = cpu_to_le16(RESET_MAC_REQ);
	mgmt_frame->desc_word[4] = cpu_to_le16(RETRY_COUNT << 8);

#घोषणा RSI_9116_DEF_TA_AGGR	3
	अगर (common->priv->device_model == RSI_DEV_9116)
		mgmt_frame->desc_word[3] |=
			cpu_to_le16(RSI_9116_DEF_TA_AGGR << 8);

	skb_put(skb, FRAME_DESC_SZ);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_band_check() - This function programs the band
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @curchan: Poपूर्णांकer to the current channel काष्ठाure.
 *
 * Return: 0 on success, corresponding error code on failure.
 */
पूर्णांक rsi_band_check(काष्ठा rsi_common *common,
		   काष्ठा ieee80211_channel *curchan)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा ieee80211_hw *hw = adapter->hw;
	u8 prev_bw = common->channel_width;
	u8 prev_ep = common->endpoपूर्णांक;
	पूर्णांक status = 0;

	अगर (common->band != curchan->band) अणु
		common->rf_reset = 1;
		common->band = curchan->band;
	पूर्ण

	अगर ((hw->conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT) ||
	    (hw->conf.chandef.width == NL80211_CHAN_WIDTH_20))
		common->channel_width = BW_20MHZ;
	अन्यथा
		common->channel_width = BW_40MHZ;

	अगर (common->band == NL80211_BAND_2GHZ) अणु
		अगर (common->channel_width)
			common->endpoपूर्णांक = EP_2GHZ_40MHZ;
		अन्यथा
			common->endpoपूर्णांक = EP_2GHZ_20MHZ;
	पूर्ण अन्यथा अणु
		अगर (common->channel_width)
			common->endpoपूर्णांक = EP_5GHZ_40MHZ;
		अन्यथा
			common->endpoपूर्णांक = EP_5GHZ_20MHZ;
	पूर्ण

	अगर (common->endpoपूर्णांक != prev_ep) अणु
		status = rsi_program_bb_rf(common);
		अगर (status)
			वापस status;
	पूर्ण

	अगर (common->channel_width != prev_bw) अणु
		अगर (adapter->device_model == RSI_DEV_9116)
			status = rsi_load_9116_bootup_params(common);
		अन्यथा
			status = rsi_load_bootup_params(common);
		अगर (status)
			वापस status;

		status = rsi_load_radio_caps(common);
		अगर (status)
			वापस status;
	पूर्ण

	वापस status;
पूर्ण

/**
 * rsi_set_channel() - This function programs the channel.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @channel: Channel value to be set.
 *
 * Return: 0 on success, corresponding error code on failure.
 */
पूर्णांक rsi_set_channel(काष्ठा rsi_common *common,
		    काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rsi_chan_config *chan_cfg;
	u16 frame_len = माप(काष्ठा rsi_chan_config);

	rsi_dbg(MGMT_TX_ZONE,
		"%s: Sending scan req frame\n", __func__);

	skb = dev_alloc_skb(frame_len);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (!channel) अणु
		dev_kमुक्त_skb(skb);
		वापस 0;
	पूर्ण
	स_रखो(skb->data, 0, frame_len);
	chan_cfg = (काष्ठा rsi_chan_config *)skb->data;

	rsi_set_len_qno(&chan_cfg->desc_dword0.len_qno, 0, RSI_WIFI_MGMT_Q);
	chan_cfg->desc_dword0.frame_type = SCAN_REQUEST;
	chan_cfg->channel_number = channel->hw_value;
	chan_cfg->antenna_gain_offset_2g = channel->max_antenna_gain;
	chan_cfg->antenna_gain_offset_5g = channel->max_antenna_gain;
	chan_cfg->region_rftype = (RSI_RF_TYPE & 0xf) << 4;

	अगर ((channel->flags & IEEE80211_CHAN_NO_IR) ||
	    (channel->flags & IEEE80211_CHAN_RADAR)) अणु
		chan_cfg->antenna_gain_offset_2g |= RSI_CHAN_RADAR;
	पूर्ण अन्यथा अणु
		अगर (common->tx_घातer < channel->max_घातer)
			chan_cfg->tx_घातer = cpu_to_le16(common->tx_घातer);
		अन्यथा
			chan_cfg->tx_घातer = cpu_to_le16(channel->max_घातer);
	पूर्ण
	chan_cfg->region_rftype |= (common->priv->dfs_region & 0xf);

	अगर (common->channel_width == BW_40MHZ)
		chan_cfg->channel_width = 0x1;

	common->channel = channel->hw_value;

	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_send_radio_params_update() - This function sends the radio
 *				parameters update to device
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: 0 on success, corresponding error code on failure.
 */
पूर्णांक rsi_send_radio_params_update(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_mac_frame *cmd_frame;
	काष्ठा sk_buff *skb = शून्य;

	rsi_dbg(MGMT_TX_ZONE,
		"%s: Sending Radio Params update frame\n", __func__);

	skb = dev_alloc_skb(FRAME_DESC_SZ);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, FRAME_DESC_SZ);
	cmd_frame = (काष्ठा rsi_mac_frame *)skb->data;

	cmd_frame->desc_word[0] = cpu_to_le16(RSI_WIFI_MGMT_Q << 12);
	cmd_frame->desc_word[1] = cpu_to_le16(RADIO_PARAMS_UPDATE);
	cmd_frame->desc_word[3] = cpu_to_le16(BIT(0));

	cmd_frame->desc_word[3] |= cpu_to_le16(common->tx_घातer << 8);

	skb_put(skb, FRAME_DESC_SZ);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/* This function programs the threshold. */
पूर्णांक rsi_send_vap_dynamic_update(काष्ठा rsi_common *common)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rsi_dynamic_s *dynamic_frame;

	rsi_dbg(MGMT_TX_ZONE,
		"%s: Sending vap update indication frame\n", __func__);

	skb = dev_alloc_skb(माप(काष्ठा rsi_dynamic_s));
	अगर (!skb)
		वापस -ENOMEM;

	स_रखो(skb->data, 0, माप(काष्ठा rsi_dynamic_s));
	dynamic_frame = (काष्ठा rsi_dynamic_s *)skb->data;
	rsi_set_len_qno(&dynamic_frame->desc_dword0.len_qno,
			माप(dynamic_frame->frame_body), RSI_WIFI_MGMT_Q);

	dynamic_frame->desc_dword0.frame_type = VAP_DYNAMIC_UPDATE;
	dynamic_frame->desc_dword2.pkt_info =
					cpu_to_le32(common->rts_threshold);

	अगर (common->wow_flags & RSI_WOW_ENABLED) अणु
		/* Beacon miss threshold */
		dynamic_frame->desc_dword3.token =
					cpu_to_le16(RSI_BCN_MISS_THRESHOLD);
		dynamic_frame->frame_body.keep_alive_period =
					cpu_to_le16(RSI_WOW_KEEPALIVE);
	पूर्ण अन्यथा अणु
		dynamic_frame->frame_body.keep_alive_period =
					cpu_to_le16(RSI_DEF_KEEPALIVE);
	पूर्ण

	dynamic_frame->desc_dword3.sta_id = 0; /* vap id */

	skb_put(skb, माप(काष्ठा rsi_dynamic_s));

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_compare() - This function is used to compare two पूर्णांकegers
 * @a: poपूर्णांकer to the first पूर्णांकeger
 * @b: poपूर्णांकer to the second पूर्णांकeger
 *
 * Return: 0 अगर both are equal, -1 अगर the first is smaller, अन्यथा 1
 */
अटल पूर्णांक rsi_compare(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	u16 _a = *(स्थिर u16 *)(a);
	u16 _b = *(स्थिर u16 *)(b);

	अगर (_a > _b)
		वापस -1;

	अगर (_a < _b)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * rsi_map_rates() - This function is used to map selected rates to hw rates.
 * @rate: The standard rate to be mapped.
 * @offset: Offset that will be वापसed.
 *
 * Return: 0 अगर it is a mcs rate, अन्यथा 1
 */
अटल bool rsi_map_rates(u16 rate, पूर्णांक *offset)
अणु
	पूर्णांक kk;
	क्रम (kk = 0; kk < ARRAY_SIZE(rsi_mcsrates); kk++) अणु
		अगर (rate == mcs[kk]) अणु
			*offset = kk;
			वापस false;
		पूर्ण
	पूर्ण

	क्रम (kk = 0; kk < ARRAY_SIZE(rsi_rates); kk++) अणु
		अगर (rate == rsi_rates[kk].bitrate / 5) अणु
			*offset = kk;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/**
 * rsi_send_स्वतः_rate_request() - This function is to set rates क्रम connection
 *				  and send स्वतःrate request to firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @sta: mac80211 station.
 * @sta_id: station id.
 * @vअगर: Poपूर्णांकer to the ieee80211_vअगर काष्ठाure.
 *
 * Return: 0 on success, corresponding error code on failure.
 */
अटल पूर्णांक rsi_send_स्वतः_rate_request(काष्ठा rsi_common *common,
				      काष्ठा ieee80211_sta *sta,
				      u16 sta_id,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rsi_स्वतः_rate *स्वतः_rate;
	पूर्णांक ii = 0, jj = 0, kk = 0;
	काष्ठा ieee80211_hw *hw = common->priv->hw;
	u8 band = hw->conf.chandef.chan->band;
	u8 num_supported_rates = 0;
	u8 rate_table_offset, rate_offset = 0;
	u32 rate_biपंचांगap;
	u16 *selected_rates, min_rate;
	bool is_ht = false, is_sgi = false;
	u16 frame_len = माप(काष्ठा rsi_स्वतः_rate);

	rsi_dbg(MGMT_TX_ZONE,
		"%s: Sending auto rate request frame\n", __func__);

	skb = dev_alloc_skb(frame_len);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, frame_len);
	selected_rates = kzalloc(2 * RSI_TBL_SZ, GFP_KERNEL);
	अगर (!selected_rates) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of mem\n",
			__func__);
		dev_kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	स्वतः_rate = (काष्ठा rsi_स्वतः_rate *)skb->data;

	स्वतः_rate->aarf_rssi = cpu_to_le16(((u16)3 << 6) | (u16)(18 & 0x3f));
	स्वतः_rate->collision_tolerance = cpu_to_le16(3);
	स्वतः_rate->failure_limit = cpu_to_le16(3);
	स्वतः_rate->initial_boundary = cpu_to_le16(3);
	स्वतः_rate->max_threshold_limt = cpu_to_le16(27);

	स्वतः_rate->desc.desc_dword0.frame_type = AUTO_RATE_IND;

	अगर (common->channel_width == BW_40MHZ)
		स्वतः_rate->desc.desc_dword3.qid_tid = BW_40MHZ;
	स्वतः_rate->desc.desc_dword3.sta_id = sta_id;

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		rate_biपंचांगap = common->bitrate_mask[band];
		is_ht = common->vअगर_info[0].is_ht;
		is_sgi = common->vअगर_info[0].sgi;
	पूर्ण अन्यथा अणु
		rate_biपंचांगap = sta->supp_rates[band];
		is_ht = sta->ht_cap.ht_supported;
		अगर ((sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ||
		    (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40))
			is_sgi = true;
	पूर्ण

	अगर (band == NL80211_BAND_2GHZ) अणु
		अगर ((rate_biपंचांगap == 0) && (is_ht))
			min_rate = RSI_RATE_MCS0;
		अन्यथा
			min_rate = RSI_RATE_1;
		rate_table_offset = 0;
	पूर्ण अन्यथा अणु
		अगर ((rate_biपंचांगap == 0) && (is_ht))
			min_rate = RSI_RATE_MCS0;
		अन्यथा
			min_rate = RSI_RATE_6;
		rate_table_offset = 4;
	पूर्ण

	क्रम (ii = 0, jj = 0;
	     ii < (ARRAY_SIZE(rsi_rates) - rate_table_offset); ii++) अणु
		अगर (rate_biपंचांगap & BIT(ii)) अणु
			selected_rates[jj++] =
			(rsi_rates[ii + rate_table_offset].bitrate / 5);
			rate_offset++;
		पूर्ण
	पूर्ण
	num_supported_rates = jj;

	अगर (is_ht) अणु
		क्रम (ii = 0; ii < ARRAY_SIZE(mcs); ii++)
			selected_rates[jj++] = mcs[ii];
		num_supported_rates += ARRAY_SIZE(mcs);
		rate_offset += ARRAY_SIZE(mcs);
	पूर्ण

	sort(selected_rates, jj, माप(u16), &rsi_compare, शून्य);

	/* mapping the rates to RSI rates */
	क्रम (ii = 0; ii < jj; ii++) अणु
		अगर (rsi_map_rates(selected_rates[ii], &kk)) अणु
			स्वतः_rate->supported_rates[ii] =
				cpu_to_le16(rsi_rates[kk].hw_value);
		पूर्ण अन्यथा अणु
			स्वतः_rate->supported_rates[ii] =
				cpu_to_le16(rsi_mcsrates[kk]);
		पूर्ण
	पूर्ण

	/* loading HT rates in the bottom half of the स्वतः rate table */
	अगर (is_ht) अणु
		क्रम (ii = rate_offset, kk = ARRAY_SIZE(rsi_mcsrates) - 1;
		     ii < rate_offset + 2 * ARRAY_SIZE(rsi_mcsrates); ii++) अणु
			अगर (is_sgi || conf_is_ht40(&common->priv->hw->conf))
				स्वतः_rate->supported_rates[ii++] =
					cpu_to_le16(rsi_mcsrates[kk] | BIT(9));
			अन्यथा
				स्वतः_rate->supported_rates[ii++] =
					cpu_to_le16(rsi_mcsrates[kk]);
			स्वतः_rate->supported_rates[ii] =
				cpu_to_le16(rsi_mcsrates[kk--]);
		पूर्ण

		क्रम (; ii < (RSI_TBL_SZ - 1); ii++) अणु
			स्वतः_rate->supported_rates[ii] =
				cpu_to_le16(rsi_mcsrates[0]);
		पूर्ण
	पूर्ण

	क्रम (; ii < RSI_TBL_SZ; ii++)
		स्वतः_rate->supported_rates[ii] = cpu_to_le16(min_rate);

	स्वतः_rate->num_supported_rates = cpu_to_le16(num_supported_rates * 2);
	स्वतः_rate->moderate_rate_inx = cpu_to_le16(num_supported_rates / 2);
	num_supported_rates *= 2;

	rsi_set_len_qno(&स्वतः_rate->desc.desc_dword0.len_qno,
			(frame_len - FRAME_DESC_SZ), RSI_WIFI_MGMT_Q);

	skb_put(skb, frame_len);
	kमुक्त(selected_rates);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_inक्रमm_bss_status() - This function inक्रमms about bss status with the
 *			     help of sta notअगरy params by sending an पूर्णांकernal
 *			     management frame to firmware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @opmode: Operating mode of device.
 * @status: Bss status type.
 * @addr: Address of the रेजिस्टर.
 * @qos_enable: Qos is enabled.
 * @aid: Aid (unique क्रम all STAs).
 * @sta: mac80211 station.
 * @sta_id: station id.
 * @assoc_cap: capabilities.
 * @vअगर: Poपूर्णांकer to the ieee80211_vअगर काष्ठाure.
 *
 * Return: None.
 */
व्योम rsi_inक्रमm_bss_status(काष्ठा rsi_common *common,
			   क्रमागत opmode opmode,
			   u8 status,
			   स्थिर u8 *addr,
			   u8 qos_enable,
			   u16 aid,
			   काष्ठा ieee80211_sta *sta,
			   u16 sta_id,
			   u16 assoc_cap,
			   काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (status) अणु
		अगर (opmode == RSI_OPMODE_STA)
			common->hw_data_qs_blocked = true;
		rsi_hal_send_sta_notअगरy_frame(common,
					      opmode,
					      STA_CONNECTED,
					      addr,
					      qos_enable,
					      aid, sta_id,
					      vअगर);
		अगर (common->min_rate == 0xffff)
			rsi_send_स्वतः_rate_request(common, sta, sta_id, vअगर);
		अगर (opmode == RSI_OPMODE_STA &&
		    !(assoc_cap & WLAN_CAPABILITY_PRIVACY) &&
		    !rsi_send_block_unblock_frame(common, false))
			common->hw_data_qs_blocked = false;
	पूर्ण अन्यथा अणु
		अगर (opmode == RSI_OPMODE_STA)
			common->hw_data_qs_blocked = true;

		अगर (!(common->wow_flags & RSI_WOW_ENABLED))
			rsi_hal_send_sta_notअगरy_frame(common, opmode,
						      STA_DISCONNECTED, addr,
						      qos_enable, aid, sta_id,
						      vअगर);
		अगर (opmode == RSI_OPMODE_STA)
			rsi_send_block_unblock_frame(common, true);
	पूर्ण
पूर्ण

/**
 * rsi_eeprom_पढ़ो() - This function sends a frame to पढ़ो the mac address
 *		       from the eeprom.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_eeprom_पढ़ो(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_eeprom_पढ़ो_frame *mgmt_frame;
	काष्ठा rsi_hw *adapter = common->priv;
	काष्ठा sk_buff *skb;

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending EEPROM read req frame\n", __func__);

	skb = dev_alloc_skb(FRAME_DESC_SZ);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, FRAME_DESC_SZ);
	mgmt_frame = (काष्ठा rsi_eeprom_पढ़ो_frame *)skb->data;

	/* FrameType */
	rsi_set_len_qno(&mgmt_frame->len_qno, 0, RSI_WIFI_MGMT_Q);
	mgmt_frame->pkt_type = EEPROM_READ;

	/* Number of bytes to पढ़ो */
	mgmt_frame->pkt_info =
		cpu_to_le32((adapter->eeprom.length << RSI_EEPROM_LEN_OFFSET) &
			    RSI_EEPROM_LEN_MASK);
	mgmt_frame->pkt_info |= cpu_to_le32((3 << RSI_EEPROM_HDR_SIZE_OFFSET) &
					    RSI_EEPROM_HDR_SIZE_MASK);

	/* Address to पढ़ो */
	mgmt_frame->eeprom_offset = cpu_to_le32(adapter->eeprom.offset);

	skb_put(skb, FRAME_DESC_SZ);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * This function sends a frame to block/unblock
 * data queues in the firmware
 *
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @block_event: Event block अगर true, unblock अगर false
 * वापसs 0 on success, -1 on failure.
 */
पूर्णांक rsi_send_block_unblock_frame(काष्ठा rsi_common *common, bool block_event)
अणु
	काष्ठा rsi_block_unblock_data *mgmt_frame;
	काष्ठा sk_buff *skb;

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending block/unblock frame\n", __func__);

	skb = dev_alloc_skb(FRAME_DESC_SZ);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, FRAME_DESC_SZ);
	mgmt_frame = (काष्ठा rsi_block_unblock_data *)skb->data;

	rsi_set_len_qno(&mgmt_frame->desc_dword0.len_qno, 0, RSI_WIFI_MGMT_Q);
	mgmt_frame->desc_dword0.frame_type = BLOCK_HW_QUEUE;
	mgmt_frame->host_quiet_info = QUIET_INFO_VALID;

	अगर (block_event) अणु
		rsi_dbg(INFO_ZONE, "blocking the data qs\n");
		mgmt_frame->block_q_biपंचांगap = cpu_to_le16(0xf);
		mgmt_frame->block_q_biपंचांगap |= cpu_to_le16(0xf << 4);
	पूर्ण अन्यथा अणु
		rsi_dbg(INFO_ZONE, "unblocking the data qs\n");
		mgmt_frame->unblock_q_biपंचांगap = cpu_to_le16(0xf);
		mgmt_frame->unblock_q_biपंचांगap |= cpu_to_le16(0xf << 4);
	पूर्ण

	skb_put(skb, FRAME_DESC_SZ);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_send_rx_filter_frame() - Sends a frame to filter the RX packets
 *
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @rx_filter_word: Flags of filter packets
 *
 * Returns 0 on success, -1 on failure.
 */
पूर्णांक rsi_send_rx_filter_frame(काष्ठा rsi_common *common, u16 rx_filter_word)
अणु
	काष्ठा rsi_mac_frame *cmd_frame;
	काष्ठा sk_buff *skb;

	rsi_dbg(MGMT_TX_ZONE, "Sending RX filter frame\n");

	skb = dev_alloc_skb(FRAME_DESC_SZ);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, FRAME_DESC_SZ);
	cmd_frame = (काष्ठा rsi_mac_frame *)skb->data;

	cmd_frame->desc_word[0] = cpu_to_le16(RSI_WIFI_MGMT_Q << 12);
	cmd_frame->desc_word[1] = cpu_to_le16(SET_RX_FILTER);
	cmd_frame->desc_word[4] = cpu_to_le16(rx_filter_word);

	skb_put(skb, FRAME_DESC_SZ);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

पूर्णांक rsi_send_ps_request(काष्ठा rsi_hw *adapter, bool enable,
			काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rsi_common *common = adapter->priv;
	काष्ठा ieee80211_bss_conf *bss = &vअगर->bss_conf;
	काष्ठा rsi_request_ps *ps;
	काष्ठा rsi_ps_info *ps_info;
	काष्ठा sk_buff *skb;
	पूर्णांक frame_len = माप(*ps);

	skb = dev_alloc_skb(frame_len);
	अगर (!skb)
		वापस -ENOMEM;
	स_रखो(skb->data, 0, frame_len);

	ps = (काष्ठा rsi_request_ps *)skb->data;
	ps_info = &adapter->ps_info;

	rsi_set_len_qno(&ps->desc.desc_dword0.len_qno,
			(frame_len - FRAME_DESC_SZ), RSI_WIFI_MGMT_Q);
	ps->desc.desc_dword0.frame_type = WAKEUP_SLEEP_REQUEST;
	अगर (enable) अणु
		ps->ps_sleep.enable = RSI_PS_ENABLE;
		ps->desc.desc_dword3.token = cpu_to_le16(RSI_SLEEP_REQUEST);
	पूर्ण अन्यथा अणु
		ps->ps_sleep.enable = RSI_PS_DISABLE;
		ps->desc.desc_dword0.len_qno |= cpu_to_le16(RSI_PS_DISABLE_IND);
		ps->desc.desc_dword3.token = cpu_to_le16(RSI_WAKEUP_REQUEST);
	पूर्ण

	ps->ps_uapsd_acs = common->uapsd_biपंचांगap;

	ps->ps_sleep.sleep_type = ps_info->sleep_type;
	ps->ps_sleep.num_bcns_per_lis_पूर्णांक =
		cpu_to_le16(ps_info->num_bcns_per_lis_पूर्णांक);
	ps->ps_sleep.sleep_duration =
		cpu_to_le32(ps_info->deep_sleep_wakeup_period);

	अगर (bss->assoc)
		ps->ps_sleep.connected_sleep = RSI_CONNECTED_SLEEP;
	अन्यथा
		ps->ps_sleep.connected_sleep = RSI_DEEP_SLEEP;

	ps->ps_listen_पूर्णांकerval = cpu_to_le32(ps_info->listen_पूर्णांकerval);
	ps->ps_dtim_पूर्णांकerval_duration =
		cpu_to_le32(ps_info->dtim_पूर्णांकerval_duration);

	अगर (ps_info->listen_पूर्णांकerval > ps_info->dtim_पूर्णांकerval_duration)
		ps->ps_listen_पूर्णांकerval = cpu_to_le32(RSI_PS_DISABLE);

	ps->ps_num_dtim_पूर्णांकervals = cpu_to_le16(ps_info->num_dtims_per_sleep);
	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

अटल पूर्णांक rsi_send_w9116_features(काष्ठा rsi_common *common)
अणु
	काष्ठा rsi_wlan_9116_features *w9116_features;
	u16 frame_len = माप(काष्ठा rsi_wlan_9116_features);
	काष्ठा sk_buff *skb;

	rsi_dbg(MGMT_TX_ZONE,
		"%s: Sending wlan 9116 features\n", __func__);

	skb = dev_alloc_skb(frame_len);
	अगर (!skb)
		वापस -ENOMEM;
	स_रखो(skb->data, 0, frame_len);

	w9116_features = (काष्ठा rsi_wlan_9116_features *)skb->data;

	w9116_features->pll_mode = common->w9116_features.pll_mode;
	w9116_features->rf_type = common->w9116_features.rf_type;
	w9116_features->wireless_mode = common->w9116_features.wireless_mode;
	w9116_features->enable_ppe = common->w9116_features.enable_ppe;
	w9116_features->afe_type = common->w9116_features.afe_type;
	अगर (common->w9116_features.dpd)
		w9116_features->feature_enable |= cpu_to_le32(RSI_DPD);
	अगर (common->w9116_features.sअगरs_tx_enable)
		w9116_features->feature_enable |=
			cpu_to_le32(RSI_SIFS_TX_ENABLE);
	अगर (common->w9116_features.ps_options & RSI_DUTY_CYCLING)
		w9116_features->feature_enable |= cpu_to_le32(RSI_DUTY_CYCLING);
	अगर (common->w9116_features.ps_options & RSI_END_OF_FRAME)
		w9116_features->feature_enable |= cpu_to_le32(RSI_END_OF_FRAME);
	w9116_features->feature_enable |=
		cpu_to_le32((common->w9116_features.ps_options & ~0x3) << 2);

	rsi_set_len_qno(&w9116_features->desc.desc_dword0.len_qno,
			frame_len - FRAME_DESC_SZ, RSI_WIFI_MGMT_Q);
	w9116_features->desc.desc_dword0.frame_type = FEATURES_ENABLE;
	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_set_antenna() - This function send antenna configuration request
 *		       to device
 *
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @antenna: biपंचांगap क्रम tx antenna selection
 *
 * Return: 0 on Success, negative error code on failure
 */
पूर्णांक rsi_set_antenna(काष्ठा rsi_common *common, u8 antenna)
अणु
	काष्ठा rsi_ant_sel_frame *ant_sel_frame;
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(FRAME_DESC_SZ);
	अगर (!skb) अणु
		rsi_dbg(ERR_ZONE, "%s: Failed in allocation of skb\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(skb->data, 0, FRAME_DESC_SZ);

	ant_sel_frame = (काष्ठा rsi_ant_sel_frame *)skb->data;
	ant_sel_frame->desc_dword0.frame_type = ANT_SEL_FRAME;
	ant_sel_frame->sub_frame_type = ANTENNA_SEL_TYPE;
	ant_sel_frame->ant_value = cpu_to_le16(antenna & ANTENNA_MASK_VALUE);
	rsi_set_len_qno(&ant_sel_frame->desc_dword0.len_qno,
			0, RSI_WIFI_MGMT_Q);
	skb_put(skb, FRAME_DESC_SZ);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

अटल पूर्णांक rsi_send_beacon(काष्ठा rsi_common *common)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u8 dword_align_bytes = 0;

	skb = dev_alloc_skb(MAX_MGMT_PKT_SIZE);
	अगर (!skb)
		वापस -ENOMEM;

	स_रखो(skb->data, 0, MAX_MGMT_PKT_SIZE);

	dword_align_bytes = ((अचिन्हित दीर्घ)skb->data & 0x3f);
	अगर (dword_align_bytes)
		skb_pull(skb, (64 - dword_align_bytes));
	अगर (rsi_prepare_beacon(common, skb)) अणु
		rsi_dbg(ERR_ZONE, "Failed to prepare beacon\n");
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	skb_queue_tail(&common->tx_queue[MGMT_BEACON_Q], skb);
	rsi_set_event(&common->tx_thपढ़ो.event);
	rsi_dbg(DATA_TX_ZONE, "%s: Added to beacon queue\n", __func__);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक rsi_send_wowlan_request(काष्ठा rsi_common *common, u16 flags,
			    u16 sleep_status)
अणु
	काष्ठा rsi_wowlan_req *cmd_frame;
	काष्ठा sk_buff *skb;
	u8 length;

	rsi_dbg(ERR_ZONE, "%s: Sending wowlan request frame\n", __func__);

	length = माप(*cmd_frame);
	skb = dev_alloc_skb(length);
	अगर (!skb)
		वापस -ENOMEM;
	स_रखो(skb->data, 0, length);
	cmd_frame = (काष्ठा rsi_wowlan_req *)skb->data;

	rsi_set_len_qno(&cmd_frame->desc.desc_dword0.len_qno,
			(length - FRAME_DESC_SZ),
			RSI_WIFI_MGMT_Q);
	cmd_frame->desc.desc_dword0.frame_type = WOWLAN_CONFIG_PARAMS;
	cmd_frame->host_sleep_status = sleep_status;
	अगर (common->secinfo.security_enable &&
	    common->secinfo.gtk_cipher)
		flags |= RSI_WOW_GTK_REKEY;
	अगर (sleep_status)
		cmd_frame->wow_flags = flags;
	rsi_dbg(INFO_ZONE, "Host_Sleep_Status : %d Flags : %d\n",
		cmd_frame->host_sleep_status, cmd_frame->wow_flags);

	skb_put(skb, length);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण
#पूर्ण_अगर

पूर्णांक rsi_send_bgscan_params(काष्ठा rsi_common *common, पूर्णांक enable)
अणु
	काष्ठा rsi_bgscan_params *params = &common->bgscan;
	काष्ठा cfg80211_scan_request *scan_req = common->hwscan;
	काष्ठा rsi_bgscan_config *bgscan;
	काष्ठा sk_buff *skb;
	u16 frame_len = माप(*bgscan);
	u8 i;

	rsi_dbg(MGMT_TX_ZONE, "%s: Sending bgscan params frame\n", __func__);

	skb = dev_alloc_skb(frame_len);
	अगर (!skb)
		वापस -ENOMEM;
	स_रखो(skb->data, 0, frame_len);

	bgscan = (काष्ठा rsi_bgscan_config *)skb->data;
	rsi_set_len_qno(&bgscan->desc_dword0.len_qno,
			(frame_len - FRAME_DESC_SZ), RSI_WIFI_MGMT_Q);
	bgscan->desc_dword0.frame_type = BG_SCAN_PARAMS;
	bgscan->bgscan_threshold = cpu_to_le16(params->bgscan_threshold);
	bgscan->roam_threshold = cpu_to_le16(params->roam_threshold);
	अगर (enable)
		bgscan->bgscan_periodicity =
			cpu_to_le16(params->bgscan_periodicity);
	bgscan->active_scan_duration =
			cpu_to_le16(params->active_scan_duration);
	bgscan->passive_scan_duration =
			cpu_to_le16(params->passive_scan_duration);
	bgscan->two_probe = params->two_probe;

	bgscan->num_bgscan_channels = scan_req->n_channels;
	क्रम (i = 0; i < bgscan->num_bgscan_channels; i++)
		bgscan->channels2scan[i] =
			cpu_to_le16(scan_req->channels[i]->hw_value);

	skb_put(skb, frame_len);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/* This function sends the probe request to be used by firmware in
 * background scan
 */
पूर्णांक rsi_send_bgscan_probe_req(काष्ठा rsi_common *common,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा cfg80211_scan_request *scan_req = common->hwscan;
	काष्ठा rsi_bgscan_probe *bgscan;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *probereq_skb;
	u16 frame_len = माप(*bgscan);
	माप_प्रकार ssid_len = 0;
	u8 *ssid = शून्य;

	rsi_dbg(MGMT_TX_ZONE,
		"%s: Sending bgscan probe req frame\n", __func__);

	अगर (common->priv->sc_nvअगरs <= 0)
		वापस -ENODEV;

	अगर (scan_req->n_ssids) अणु
		ssid = scan_req->ssids[0].ssid;
		ssid_len = scan_req->ssids[0].ssid_len;
	पूर्ण

	skb = dev_alloc_skb(frame_len + MAX_BGSCAN_PROBE_REQ_LEN);
	अगर (!skb)
		वापस -ENOMEM;
	स_रखो(skb->data, 0, frame_len + MAX_BGSCAN_PROBE_REQ_LEN);

	bgscan = (काष्ठा rsi_bgscan_probe *)skb->data;
	bgscan->desc_dword0.frame_type = BG_SCAN_PROBE_REQ;
	bgscan->flags = cpu_to_le16(HOST_BG_SCAN_TRIG);
	अगर (common->band == NL80211_BAND_5GHZ) अणु
		bgscan->mgmt_rate = cpu_to_le16(RSI_RATE_6);
		bgscan->def_chan = cpu_to_le16(40);
	पूर्ण अन्यथा अणु
		bgscan->mgmt_rate = cpu_to_le16(RSI_RATE_1);
		bgscan->def_chan = cpu_to_le16(11);
	पूर्ण
	bgscan->channel_scan_समय = cpu_to_le16(RSI_CHANNEL_SCAN_TIME);

	probereq_skb = ieee80211_probereq_get(common->priv->hw, vअगर->addr, ssid,
					      ssid_len, scan_req->ie_len);
	अगर (!probereq_skb) अणु
		dev_kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&skb->data[frame_len], probereq_skb->data, probereq_skb->len);

	bgscan->probe_req_length = cpu_to_le16(probereq_skb->len);

	rsi_set_len_qno(&bgscan->desc_dword0.len_qno,
			(frame_len - FRAME_DESC_SZ + probereq_skb->len),
			RSI_WIFI_MGMT_Q);

	skb_put(skb, frame_len + probereq_skb->len);

	dev_kमुक्त_skb(probereq_skb);

	वापस rsi_send_पूर्णांकernal_mgmt_frame(common, skb);
पूर्ण

/**
 * rsi_handle_ta_confirm_type() - This function handles the confirm frames.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @msg: Poपूर्णांकer to received packet.
 *
 * Return: 0 on success, -1 on failure.
 */
अटल पूर्णांक rsi_handle_ta_confirm_type(काष्ठा rsi_common *common,
				      u8 *msg)
अणु
	काष्ठा rsi_hw *adapter = common->priv;
	u8 sub_type = (msg[15] & 0xff);
	u16 msg_len = ((u16 *)msg)[0] & 0xfff;
	u8 offset;

	चयन (sub_type) अणु
	हाल BOOTUP_PARAMS_REQUEST:
		rsi_dbg(FSM_ZONE, "%s: Boot up params confirm received\n",
			__func__);
		अगर (common->fsm_state == FSM_BOOT_PARAMS_SENT) अणु
			अगर (adapter->device_model == RSI_DEV_9116) अणु
				common->band = NL80211_BAND_5GHZ;
				common->num_supp_bands = 2;

				अगर (rsi_send_reset_mac(common))
					जाओ out;
				अन्यथा
					common->fsm_state = FSM_RESET_MAC_SENT;
			पूर्ण अन्यथा अणु
				adapter->eeprom.length =
					(IEEE80211_ADDR_LEN +
					 WLAN_MAC_MAGIC_WORD_LEN +
					 WLAN_HOST_MODE_LEN);
				adapter->eeprom.offset = WLAN_MAC_EEPROM_ADDR;
				अगर (rsi_eeprom_पढ़ो(common)) अणु
					common->fsm_state = FSM_CARD_NOT_READY;
					जाओ out;
				पूर्ण
				common->fsm_state = FSM_EEPROM_READ_MAC_ADDR;
			पूर्ण
		पूर्ण अन्यथा अणु
			rsi_dbg(INFO_ZONE,
				"%s: Received bootup params cfm in %d state\n",
				 __func__, common->fsm_state);
			वापस 0;
		पूर्ण
		अवरोध;

	हाल EEPROM_READ:
		rsi_dbg(FSM_ZONE, "EEPROM READ confirm received\n");
		अगर (msg_len <= 0) अणु
			rsi_dbg(FSM_ZONE,
				"%s: [EEPROM_READ] Invalid len %d\n",
				__func__, msg_len);
			जाओ out;
		पूर्ण
		अगर (msg[16] != MAGIC_WORD) अणु
			rsi_dbg(FSM_ZONE,
				"%s: [EEPROM_READ] Invalid token\n", __func__);
			common->fsm_state = FSM_CARD_NOT_READY;
			जाओ out;
		पूर्ण
		अगर (common->fsm_state == FSM_EEPROM_READ_MAC_ADDR) अणु
			offset = (FRAME_DESC_SZ + WLAN_HOST_MODE_LEN +
				  WLAN_MAC_MAGIC_WORD_LEN);
			स_नकल(common->mac_addr, &msg[offset], ETH_ALEN);
			adapter->eeprom.length =
				((WLAN_MAC_MAGIC_WORD_LEN + 3) & (~3));
			adapter->eeprom.offset = WLAN_EEPROM_RFTYPE_ADDR;
			अगर (rsi_eeprom_पढ़ो(common)) अणु
				rsi_dbg(ERR_ZONE,
					"%s: Failed reading RF band\n",
					__func__);
				common->fsm_state = FSM_CARD_NOT_READY;
				जाओ out;
			पूर्ण
			common->fsm_state = FSM_EEPROM_READ_RF_TYPE;
		पूर्ण अन्यथा अगर (common->fsm_state == FSM_EEPROM_READ_RF_TYPE) अणु
			अगर ((msg[17] & 0x3) == 0x3) अणु
				rsi_dbg(INIT_ZONE, "Dual band supported\n");
				common->band = NL80211_BAND_5GHZ;
				common->num_supp_bands = 2;
			पूर्ण अन्यथा अगर ((msg[17] & 0x3) == 0x1) अणु
				rsi_dbg(INIT_ZONE,
					"Only 2.4Ghz band supported\n");
				common->band = NL80211_BAND_2GHZ;
				common->num_supp_bands = 1;
			पूर्ण
			अगर (rsi_send_reset_mac(common))
				जाओ out;
			common->fsm_state = FSM_RESET_MAC_SENT;
		पूर्ण अन्यथा अणु
			rsi_dbg(ERR_ZONE, "%s: Invalid EEPROM read type\n",
				__func__);
			वापस 0;
		पूर्ण
		अवरोध;

	हाल RESET_MAC_REQ:
		अगर (common->fsm_state == FSM_RESET_MAC_SENT) अणु
			rsi_dbg(FSM_ZONE, "%s: Reset MAC cfm received\n",
				__func__);

			अगर (rsi_load_radio_caps(common))
				जाओ out;
			अन्यथा
				common->fsm_state = FSM_RADIO_CAPS_SENT;
		पूर्ण अन्यथा अणु
			rsi_dbg(ERR_ZONE,
				"%s: Received reset mac cfm in %d state\n",
				 __func__, common->fsm_state);
			वापस 0;
		पूर्ण
		अवरोध;

	हाल RADIO_CAPABILITIES:
		अगर (common->fsm_state == FSM_RADIO_CAPS_SENT) अणु
			common->rf_reset = 1;
			अगर (adapter->device_model == RSI_DEV_9116 &&
			    rsi_send_w9116_features(common)) अणु
				rsi_dbg(ERR_ZONE,
					"Failed to send 9116 features\n");
				जाओ out;
			पूर्ण
			अगर (rsi_program_bb_rf(common)) अणु
				जाओ out;
			पूर्ण अन्यथा अणु
				common->fsm_state = FSM_BB_RF_PROG_SENT;
				rsi_dbg(FSM_ZONE, "%s: Radio cap cfm received\n",
					__func__);
			पूर्ण
		पूर्ण अन्यथा अणु
			rsi_dbg(INFO_ZONE,
				"%s: Received radio caps cfm in %d state\n",
				 __func__, common->fsm_state);
			वापस 0;
		पूर्ण
		अवरोध;

	हाल BB_PROG_VALUES_REQUEST:
	हाल RF_PROG_VALUES_REQUEST:
	हाल BBP_PROG_IN_TA:
		rsi_dbg(FSM_ZONE, "%s: BB/RF cfm received\n", __func__);
		अगर (common->fsm_state == FSM_BB_RF_PROG_SENT) अणु
			common->bb_rf_prog_count--;
			अगर (!common->bb_rf_prog_count) अणु
				common->fsm_state = FSM_MAC_INIT_DONE;
				अगर (common->reinit_hw) अणु
					complete(&common->wlan_init_completion);
				पूर्ण अन्यथा अणु
					वापस rsi_mac80211_attach(common);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			rsi_dbg(INFO_ZONE,
				"%s: Received bbb_rf cfm in %d state\n",
				 __func__, common->fsm_state);
			वापस 0;
		पूर्ण
		अवरोध;

	हाल SCAN_REQUEST:
		rsi_dbg(INFO_ZONE, "Set channel confirm\n");
		अवरोध;

	हाल WAKEUP_SLEEP_REQUEST:
		rsi_dbg(INFO_ZONE, "Wakeup/Sleep confirmation.\n");
		वापस rsi_handle_ps_confirm(adapter, msg);

	हाल BG_SCAN_PROBE_REQ:
		rsi_dbg(INFO_ZONE, "BG scan complete event\n");
		अगर (common->bgscan_en) अणु
			काष्ठा cfg80211_scan_info info;

			अगर (!rsi_send_bgscan_params(common, RSI_STOP_BGSCAN))
				common->bgscan_en = 0;
			info.पातed = false;
			ieee80211_scan_completed(adapter->hw, &info);
		पूर्ण
		rsi_dbg(INFO_ZONE, "Background scan completed\n");
		अवरोध;

	शेष:
		rsi_dbg(INFO_ZONE, "%s: Invalid TA confirm pkt received\n",
			__func__);
		अवरोध;
	पूर्ण
	वापस 0;
out:
	rsi_dbg(ERR_ZONE, "%s: Unable to send pkt/Invalid frame received\n",
		__func__);
	वापस -EINVAL;
पूर्ण

पूर्णांक rsi_handle_card_पढ़ोy(काष्ठा rsi_common *common, u8 *msg)
अणु
	पूर्णांक status;

	चयन (common->fsm_state) अणु
	हाल FSM_CARD_NOT_READY:
		rsi_dbg(INIT_ZONE, "Card ready indication from Common HAL\n");
		rsi_set_शेष_parameters(common);
		अगर (rsi_send_common_dev_params(common) < 0)
			वापस -EINVAL;
		common->fsm_state = FSM_COMMON_DEV_PARAMS_SENT;
		अवरोध;
	हाल FSM_COMMON_DEV_PARAMS_SENT:
		rsi_dbg(INIT_ZONE, "Card ready indication from WLAN HAL\n");

		अगर (common->priv->device_model == RSI_DEV_9116) अणु
			अगर (msg[16] != MAGIC_WORD) अणु
				rsi_dbg(FSM_ZONE,
					"%s: [EEPROM_READ] Invalid token\n",
					__func__);
				common->fsm_state = FSM_CARD_NOT_READY;
				वापस -EINVAL;
			पूर्ण
			स_नकल(common->mac_addr, &msg[20], ETH_ALEN);
			rsi_dbg(INIT_ZONE, "MAC Addr %pM", common->mac_addr);
		पूर्ण
		/* Get usb buffer status रेजिस्टर address */
		common->priv->usb_buffer_status_reg = *(u32 *)&msg[8];
		rsi_dbg(INFO_ZONE, "USB buffer status register = %x\n",
			common->priv->usb_buffer_status_reg);

		अगर (common->priv->device_model == RSI_DEV_9116)
			status = rsi_load_9116_bootup_params(common);
		अन्यथा
			status = rsi_load_bootup_params(common);
		अगर (status < 0) अणु
			common->fsm_state = FSM_CARD_NOT_READY;
			वापस status;
		पूर्ण
		common->fsm_state = FSM_BOOT_PARAMS_SENT;
		अवरोध;
	शेष:
		rsi_dbg(ERR_ZONE,
			"%s: card ready indication in invalid state %d.\n",
			__func__, common->fsm_state);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * rsi_mgmt_pkt_recv() - This function processes the management packets
 *			 received from the hardware.
 * @common: Poपूर्णांकer to the driver निजी काष्ठाure.
 * @msg: Poपूर्णांकer to the received packet.
 *
 * Return: 0 on success, -1 on failure.
 */
पूर्णांक rsi_mgmt_pkt_recv(काष्ठा rsi_common *common, u8 *msg)
अणु
	s32 msg_len = (le16_to_cpu(*(__le16 *)&msg[0]) & 0x0fff);
	u16 msg_type = (msg[2]);

	rsi_dbg(FSM_ZONE, "%s: Msg Len: %d, Msg Type: %4x\n",
		__func__, msg_len, msg_type);

	चयन (msg_type) अणु
	हाल TA_CONFIRM_TYPE:
		वापस rsi_handle_ta_confirm_type(common, msg);
	हाल CARD_READY_IND:
		common->hibernate_resume = false;
		rsi_dbg(FSM_ZONE, "%s: Card ready indication received\n",
			__func__);
		वापस rsi_handle_card_पढ़ोy(common, msg);
	हाल TX_STATUS_IND:
		चयन (msg[RSI_TX_STATUS_TYPE]) अणु
		हाल PROBEREQ_CONFIRM:
			common->mgmt_q_block = false;
			rsi_dbg(FSM_ZONE, "%s: Probe confirm received\n",
				__func__);
			अवरोध;
		हाल EAPOL4_CONFIRM:
			अगर (msg[RSI_TX_STATUS]) अणु
				common->eapol4_confirm = true;
				अगर (!rsi_send_block_unblock_frame(common,
								  false))
					common->hw_data_qs_blocked = false;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल BEACON_EVENT_IND:
		rsi_dbg(INFO_ZONE, "Beacon event\n");
		अगर (common->fsm_state != FSM_MAC_INIT_DONE)
			वापस -1;
		अगर (common->अगरace_करोwn)
			वापस -1;
		अगर (!common->beacon_enabled)
			वापस -1;
		rsi_send_beacon(common);
		अवरोध;
	हाल WOWLAN_WAKEUP_REASON:
		rsi_dbg(ERR_ZONE, "\n\nWakeup Type: %x\n", msg[15]);
		चयन (msg[15]) अणु
		हाल RSI_UNICAST_MAGIC_PKT:
			rsi_dbg(ERR_ZONE,
				"*** Wakeup for Unicast magic packet ***\n");
			अवरोध;
		हाल RSI_BROADCAST_MAGICPKT:
			rsi_dbg(ERR_ZONE,
				"*** Wakeup for Broadcast magic packet ***\n");
			अवरोध;
		हाल RSI_EAPOL_PKT:
			rsi_dbg(ERR_ZONE,
				"*** Wakeup for GTK renewal ***\n");
			अवरोध;
		हाल RSI_DISCONNECT_PKT:
			rsi_dbg(ERR_ZONE,
				"*** Wakeup for Disconnect ***\n");
			अवरोध;
		हाल RSI_HW_BMISS_PKT:
			rsi_dbg(ERR_ZONE,
				"*** Wakeup for HW Beacon miss ***\n");
			अवरोध;
		शेष:
			rsi_dbg(ERR_ZONE,
				"##### Un-intentional Wakeup #####\n");
			अवरोध;
	पूर्ण
	अवरोध;
	हाल RX_DOT11_MGMT:
		वापस rsi_mgmt_pkt_to_core(common, msg, msg_len);
	शेष:
		rsi_dbg(INFO_ZONE, "Received packet type: 0x%x\n", msg_type);
	पूर्ण
	वापस 0;
पूर्ण
