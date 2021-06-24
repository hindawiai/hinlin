<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2015 Intel Deutschland GmbH
 * Copyright(c) 2018, 2020 Intel Corporation
 *
 * Portions of this file are derived from the ipw3945 project, as well
 * as portionhelp of the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <net/mac80211.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "iwl-trans.h"
#समावेश "iwl-io.h"
#समावेश "dev.h"
#समावेश "calib.h"
#समावेश "agn.h"

/******************************************************************************
 *
 * Generic RX handler implementations
 *
 ******************************************************************************/

अटल व्योम iwlagn_rx_reply_error(काष्ठा iwl_priv *priv,
				  काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_error_resp *err_resp = (व्योम *)pkt->data;

	IWL_ERR(priv, "Error Reply type 0x%08X cmd REPLY_ERROR (0x%02X) "
		"seq 0x%04X ser 0x%08X\n",
		le32_to_cpu(err_resp->error_type),
		err_resp->cmd_id,
		le16_to_cpu(err_resp->bad_cmd_seq_num),
		le32_to_cpu(err_resp->error_info));
पूर्ण

अटल व्योम iwlagn_rx_csa(काष्ठा iwl_priv *priv, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_csa_notअगरication *csa = (व्योम *)pkt->data;
	/*
	 * MULTI-FIXME
	 * See iwlagn_mac_channel_चयन.
	 */
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	काष्ठा iwl_rxon_cmd *rxon = (व्योम *)&ctx->active;

	अगर (!test_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status))
		वापस;

	अगर (!le32_to_cpu(csa->status) && csa->channel == priv->चयन_channel) अणु
		rxon->channel = csa->channel;
		ctx->staging.channel = csa->channel;
		IWL_DEBUG_11H(priv, "CSA notif: channel %d\n",
			      le16_to_cpu(csa->channel));
		iwl_chचयन_करोne(priv, true);
	पूर्ण अन्यथा अणु
		IWL_ERR(priv, "CSA notif (fail) : channel %d\n",
			le16_to_cpu(csa->channel));
		iwl_chचयन_करोne(priv, false);
	पूर्ण
पूर्ण


अटल व्योम iwlagn_rx_spectrum_measure_notअगर(काष्ठा iwl_priv *priv,
					     काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_spectrum_notअगरication *report = (व्योम *)pkt->data;

	अगर (!report->state) अणु
		IWL_DEBUG_11H(priv,
			"Spectrum Measure Notification: Start\n");
		वापस;
	पूर्ण

	स_नकल(&priv->measure_report, report, माप(*report));
	priv->measurement_status |= MEASUREMENT_READY;
पूर्ण

अटल व्योम iwlagn_rx_pm_sleep_notअगर(काष्ठा iwl_priv *priv,
				     काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_sleep_notअगरication *sleep = (व्योम *)pkt->data;
	IWL_DEBUG_RX(priv, "sleep mode: %d, src: %d\n",
		     sleep->pm_sleep_mode, sleep->pm_wakeup_src);
#पूर्ण_अगर
पूर्ण

अटल व्योम iwlagn_rx_pm_debug_statistics_notअगर(काष्ठा iwl_priv *priv,
						काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	u32 __maybe_unused len = iwl_rx_packet_len(pkt);
	IWL_DEBUG_RADIO(priv, "Dumping %d bytes of unhandled "
			"notification for PM_DEBUG_STATISTIC_NOTIFIC:\n", len);
	iwl_prपूर्णांक_hex_dump(priv, IWL_DL_RADIO, pkt->data, len);
पूर्ण

अटल व्योम iwlagn_rx_beacon_notअगर(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwlagn_beacon_notअगर *beacon = (व्योम *)pkt->data;
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	u16 status = le16_to_cpu(beacon->beacon_notअगरy_hdr.status.status);
	u8 rate = iwl_hw_get_rate(beacon->beacon_notअगरy_hdr.rate_n_flags);

	IWL_DEBUG_RX(priv, "beacon status %#x, retries:%d ibssmgr:%d "
		"tsf:0x%.8x%.8x rate:%d\n",
		status & TX_STATUS_MSK,
		beacon->beacon_notअगरy_hdr.failure_frame,
		le32_to_cpu(beacon->ibss_mgr_status),
		le32_to_cpu(beacon->high_tsf),
		le32_to_cpu(beacon->low_tsf), rate);
#पूर्ण_अगर

	priv->ibss_manager = le32_to_cpu(beacon->ibss_mgr_status);
पूर्ण

/*
 * iwl_good_plcp_health - checks क्रम plcp error.
 *
 * When the plcp error is exceeding the thresholds, reset the radio
 * to improve the throughput.
 */
अटल bool iwlagn_good_plcp_health(काष्ठा iwl_priv *priv,
				 काष्ठा statistics_rx_phy *cur_ofdm,
				 काष्ठा statistics_rx_ht_phy *cur_ofdm_ht,
				 अचिन्हित पूर्णांक msecs)
अणु
	पूर्णांक delta;
	पूर्णांक threshold = priv->plcp_delta_threshold;

	अगर (threshold == IWL_MAX_PLCP_ERR_THRESHOLD_DISABLE) अणु
		IWL_DEBUG_RADIO(priv, "plcp_err check disabled\n");
		वापस true;
	पूर्ण

	delta = le32_to_cpu(cur_ofdm->plcp_err) -
		le32_to_cpu(priv->statistics.rx_ofdm.plcp_err) +
		le32_to_cpu(cur_ofdm_ht->plcp_err) -
		le32_to_cpu(priv->statistics.rx_ofdm_ht.plcp_err);

	/* Can be negative अगर firmware reset statistics */
	अगर (delta <= 0)
		वापस true;

	अगर ((delta * 100 / msecs) > threshold) अणु
		IWL_DEBUG_RADIO(priv,
				"plcp health threshold %u delta %d msecs %u\n",
				threshold, delta, msecs);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक iwl_क्रमce_rf_reset(काष्ठा iwl_priv *priv, bool बाह्यal)
अणु
	काष्ठा iwl_rf_reset *rf_reset;

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस -EAGAIN;

	अगर (!iwl_is_any_associated(priv)) अणु
		IWL_DEBUG_SCAN(priv, "force reset rejected: not associated\n");
		वापस -ENOLINK;
	पूर्ण

	rf_reset = &priv->rf_reset;
	rf_reset->reset_request_count++;
	अगर (!बाह्यal && rf_reset->last_reset_jअगरfies &&
	    समय_after(rf_reset->last_reset_jअगरfies +
		       IWL_DELAY_NEXT_FORCE_RF_RESET, jअगरfies)) अणु
		IWL_DEBUG_INFO(priv, "RF reset rejected\n");
		rf_reset->reset_reject_count++;
		वापस -EAGAIN;
	पूर्ण
	rf_reset->reset_success_count++;
	rf_reset->last_reset_jअगरfies = jअगरfies;

	/*
	 * There is no easy and better way to क्रमce reset the radio,
	 * the only known method is चयनing channel which will क्रमce to
	 * reset and tune the radio.
	 * Use पूर्णांकernal लघु scan (single channel) operation to should
	 * achieve this objective.
	 * Driver should reset the radio when number of consecutive missed
	 * beacon, or any other uCode error condition detected.
	 */
	IWL_DEBUG_INFO(priv, "perform radio reset.\n");
	iwl_पूर्णांकernal_लघु_hw_scan(priv);
	वापस 0;
पूर्ण


अटल व्योम iwlagn_recover_from_statistics(काष्ठा iwl_priv *priv,
				काष्ठा statistics_rx_phy *cur_ofdm,
				काष्ठा statistics_rx_ht_phy *cur_ofdm_ht,
				काष्ठा statistics_tx *tx,
				अचिन्हित दीर्घ stamp)
अणु
	अचिन्हित पूर्णांक msecs;

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	msecs = jअगरfies_to_msecs(stamp - priv->rx_statistics_jअगरfies);

	/* Only gather statistics and update समय stamp when not associated */
	अगर (!iwl_is_any_associated(priv))
		वापस;

	/* Do not check/recover when करो not have enough statistics data */
	अगर (msecs < 99)
		वापस;

	अगर (!iwlagn_good_plcp_health(priv, cur_ofdm, cur_ofdm_ht, msecs))
		iwl_क्रमce_rf_reset(priv, false);
पूर्ण

/* Calculate noise level, based on measurements during network silence just
 *   beक्रमe arriving beacon.  This measurement can be करोne only अगर we know
 *   exactly when to expect beacons, thereक्रमe only when we're associated. */
अटल व्योम iwlagn_rx_calc_noise(काष्ठा iwl_priv *priv)
अणु
	काष्ठा statistics_rx_non_phy *rx_info;
	पूर्णांक num_active_rx = 0;
	पूर्णांक total_silence = 0;
	पूर्णांक bcn_silence_a, bcn_silence_b, bcn_silence_c;
	पूर्णांक last_rx_noise;

	rx_info = &priv->statistics.rx_non_phy;

	bcn_silence_a =
		le32_to_cpu(rx_info->beacon_silence_rssi_a) & IN_BAND_FILTER;
	bcn_silence_b =
		le32_to_cpu(rx_info->beacon_silence_rssi_b) & IN_BAND_FILTER;
	bcn_silence_c =
		le32_to_cpu(rx_info->beacon_silence_rssi_c) & IN_BAND_FILTER;

	अगर (bcn_silence_a) अणु
		total_silence += bcn_silence_a;
		num_active_rx++;
	पूर्ण
	अगर (bcn_silence_b) अणु
		total_silence += bcn_silence_b;
		num_active_rx++;
	पूर्ण
	अगर (bcn_silence_c) अणु
		total_silence += bcn_silence_c;
		num_active_rx++;
	पूर्ण

	/* Average among active antennas */
	अगर (num_active_rx)
		last_rx_noise = (total_silence / num_active_rx) - 107;
	अन्यथा
		last_rx_noise = IWL_NOISE_MEAS_NOT_AVAILABLE;

	IWL_DEBUG_CALIB(priv, "inband silence a %u, b %u, c %u, dBm %d\n",
			bcn_silence_a, bcn_silence_b, bcn_silence_c,
			last_rx_noise);
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
/*
 *  based on the assumption of all statistics counter are in DWORD
 *  FIXME: This function is क्रम debugging, करो not deal with
 *  the हाल of counters roll-over.
 */
अटल व्योम accum_stats(__le32 *prev, __le32 *cur, __le32 *delta,
			__le32 *max_delta, __le32 *accum, पूर्णांक size)
अणु
	पूर्णांक i;

	क्रम (i = 0;
	     i < size / माप(__le32);
	     i++, prev++, cur++, delta++, max_delta++, accum++) अणु
		अगर (le32_to_cpu(*cur) > le32_to_cpu(*prev)) अणु
			*delta = cpu_to_le32(
				le32_to_cpu(*cur) - le32_to_cpu(*prev));
			le32_add_cpu(accum, le32_to_cpu(*delta));
			अगर (le32_to_cpu(*delta) > le32_to_cpu(*max_delta))
				*max_delta = *delta;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
iwlagn_accumulative_statistics(काष्ठा iwl_priv *priv,
			    काष्ठा statistics_general_common *common,
			    काष्ठा statistics_rx_non_phy *rx_non_phy,
			    काष्ठा statistics_rx_phy *rx_ofdm,
			    काष्ठा statistics_rx_ht_phy *rx_ofdm_ht,
			    काष्ठा statistics_rx_phy *rx_cck,
			    काष्ठा statistics_tx *tx,
			    काष्ठा statistics_bt_activity *bt_activity)
अणु
#घोषणा ACCUM(_name)	\
	accum_stats((__le32 *)&priv->statistics._name,		\
		    (__le32 *)_name,				\
		    (__le32 *)&priv->delta_stats._name,		\
		    (__le32 *)&priv->max_delta_stats._name,	\
		    (__le32 *)&priv->accum_stats._name,		\
		    माप(*_name));

	ACCUM(common);
	ACCUM(rx_non_phy);
	ACCUM(rx_ofdm);
	ACCUM(rx_ofdm_ht);
	ACCUM(rx_cck);
	ACCUM(tx);
	अगर (bt_activity)
		ACCUM(bt_activity);
#अघोषित ACCUM
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
iwlagn_accumulative_statistics(काष्ठा iwl_priv *priv,
			    काष्ठा statistics_general_common *common,
			    काष्ठा statistics_rx_non_phy *rx_non_phy,
			    काष्ठा statistics_rx_phy *rx_ofdm,
			    काष्ठा statistics_rx_ht_phy *rx_ofdm_ht,
			    काष्ठा statistics_rx_phy *rx_cck,
			    काष्ठा statistics_tx *tx,
			    काष्ठा statistics_bt_activity *bt_activity)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम iwlagn_rx_statistics(काष्ठा iwl_priv *priv,
				 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	अचिन्हित दीर्घ stamp = jअगरfies;
	स्थिर पूर्णांक reg_recalib_period = 60;
	पूर्णांक change;
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	u32 len = iwl_rx_packet_payload_len(pkt);
	__le32 *flag;
	काष्ठा statistics_general_common *common;
	काष्ठा statistics_rx_non_phy *rx_non_phy;
	काष्ठा statistics_rx_phy *rx_ofdm;
	काष्ठा statistics_rx_ht_phy *rx_ofdm_ht;
	काष्ठा statistics_rx_phy *rx_cck;
	काष्ठा statistics_tx *tx;
	काष्ठा statistics_bt_activity *bt_activity;

	IWL_DEBUG_RX(priv, "Statistics notification received (%d bytes).\n",
		     len);

	spin_lock(&priv->statistics.lock);

	अगर (len == माप(काष्ठा iwl_bt_notअगर_statistics)) अणु
		काष्ठा iwl_bt_notअगर_statistics *stats;
		stats = (व्योम *)&pkt->data;
		flag = &stats->flag;
		common = &stats->general.common;
		rx_non_phy = &stats->rx.general.common;
		rx_ofdm = &stats->rx.ofdm;
		rx_ofdm_ht = &stats->rx.ofdm_ht;
		rx_cck = &stats->rx.cck;
		tx = &stats->tx;
		bt_activity = &stats->general.activity;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
		/* handle this exception directly */
		priv->statistics.num_bt_समाप्तs = stats->rx.general.num_bt_समाप्तs;
		le32_add_cpu(&priv->statistics.accum_num_bt_समाप्तs,
			     le32_to_cpu(stats->rx.general.num_bt_समाप्तs));
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (len == माप(काष्ठा iwl_notअगर_statistics)) अणु
		काष्ठा iwl_notअगर_statistics *stats;
		stats = (व्योम *)&pkt->data;
		flag = &stats->flag;
		common = &stats->general.common;
		rx_non_phy = &stats->rx.general;
		rx_ofdm = &stats->rx.ofdm;
		rx_ofdm_ht = &stats->rx.ofdm_ht;
		rx_cck = &stats->rx.cck;
		tx = &stats->tx;
		bt_activity = शून्य;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "len %d doesn't match BT (%zu) or normal (%zu)\n",
			  len, माप(काष्ठा iwl_bt_notअगर_statistics),
			  माप(काष्ठा iwl_notअगर_statistics));
		spin_unlock(&priv->statistics.lock);
		वापस;
	पूर्ण

	change = common->temperature != priv->statistics.common.temperature ||
		 (*flag & STATISTICS_REPLY_FLG_HT40_MODE_MSK) !=
		 (priv->statistics.flag & STATISTICS_REPLY_FLG_HT40_MODE_MSK);

	iwlagn_accumulative_statistics(priv, common, rx_non_phy, rx_ofdm,
				    rx_ofdm_ht, rx_cck, tx, bt_activity);

	iwlagn_recover_from_statistics(priv, rx_ofdm, rx_ofdm_ht, tx, stamp);

	priv->statistics.flag = *flag;
	स_नकल(&priv->statistics.common, common, माप(*common));
	स_नकल(&priv->statistics.rx_non_phy, rx_non_phy, माप(*rx_non_phy));
	स_नकल(&priv->statistics.rx_ofdm, rx_ofdm, माप(*rx_ofdm));
	स_नकल(&priv->statistics.rx_ofdm_ht, rx_ofdm_ht, माप(*rx_ofdm_ht));
	स_नकल(&priv->statistics.rx_cck, rx_cck, माप(*rx_cck));
	स_नकल(&priv->statistics.tx, tx, माप(*tx));
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (bt_activity)
		स_नकल(&priv->statistics.bt_activity, bt_activity,
			माप(*bt_activity));
#पूर्ण_अगर

	priv->rx_statistics_jअगरfies = stamp;

	set_bit(STATUS_STATISTICS, &priv->status);

	/* Reschedule the statistics समयr to occur in
	 * reg_recalib_period seconds to ensure we get a
	 * thermal update even अगर the uCode करोesn't give
	 * us one */
	mod_समयr(&priv->statistics_periodic, jअगरfies +
		  msecs_to_jअगरfies(reg_recalib_period * 1000));

	अगर (unlikely(!test_bit(STATUS_SCANNING, &priv->status)) &&
	    (pkt->hdr.cmd == STATISTICS_NOTIFICATION)) अणु
		iwlagn_rx_calc_noise(priv);
		queue_work(priv->workqueue, &priv->run_समय_calib_work);
	पूर्ण
	अगर (priv->lib->temperature && change)
		priv->lib->temperature(priv);

	spin_unlock(&priv->statistics.lock);
पूर्ण

अटल व्योम iwlagn_rx_reply_statistics(काष्ठा iwl_priv *priv,
				       काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_notअगर_statistics *stats = (व्योम *)pkt->data;

	अगर (le32_to_cpu(stats->flag) & UCODE_STATISTICS_CLEAR_MSK) अणु
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
		स_रखो(&priv->accum_stats, 0,
			माप(priv->accum_stats));
		स_रखो(&priv->delta_stats, 0,
			माप(priv->delta_stats));
		स_रखो(&priv->max_delta_stats, 0,
			माप(priv->max_delta_stats));
#पूर्ण_अगर
		IWL_DEBUG_RX(priv, "Statistics have been cleared\n");
	पूर्ण

	iwlagn_rx_statistics(priv, rxb);
पूर्ण

/* Handle notअगरication from uCode that card's घातer state is changing
 * due to software, hardware, or critical temperature RFKILL */
अटल व्योम iwlagn_rx_card_state_notअगर(काष्ठा iwl_priv *priv,
				       काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_card_state_notअगर *card_state_notअगर = (व्योम *)pkt->data;
	u32 flags = le32_to_cpu(card_state_notअगर->flags);
	अचिन्हित दीर्घ status = priv->status;

	IWL_DEBUG_RF_KILL(priv, "Card state received: HW:%s SW:%s CT:%s\n",
			  (flags & HW_CARD_DISABLED) ? "Kill" : "On",
			  (flags & SW_CARD_DISABLED) ? "Kill" : "On",
			  (flags & CT_CARD_DISABLED) ?
			  "Reached" : "Not reached");

	अगर (flags & (SW_CARD_DISABLED | HW_CARD_DISABLED |
		     CT_CARD_DISABLED)) अणु

		iwl_ग_लिखो32(priv->trans, CSR_UCODE_DRV_GP1_SET,
			    CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);

		iwl_ग_लिखो_direct32(priv->trans, HBUS_TARG_MBX_C,
					HBUS_TARG_MBX_C_REG_BIT_CMD_BLOCKED);

		अगर (!(flags & RXON_CARD_DISABLED)) अणु
			iwl_ग_लिखो32(priv->trans, CSR_UCODE_DRV_GP1_CLR,
				    CSR_UCODE_DRV_GP1_BIT_CMD_BLOCKED);
			iwl_ग_लिखो_direct32(priv->trans, HBUS_TARG_MBX_C,
					HBUS_TARG_MBX_C_REG_BIT_CMD_BLOCKED);
		पूर्ण
		अगर (flags & CT_CARD_DISABLED)
			iwl_tt_enter_ct_समाप्त(priv);
	पूर्ण
	अगर (!(flags & CT_CARD_DISABLED))
		iwl_tt_निकास_ct_समाप्त(priv);

	अगर (flags & HW_CARD_DISABLED)
		set_bit(STATUS_RF_KILL_HW, &priv->status);
	अन्यथा
		clear_bit(STATUS_RF_KILL_HW, &priv->status);


	अगर (!(flags & RXON_CARD_DISABLED))
		iwl_scan_cancel(priv);

	अगर ((test_bit(STATUS_RF_KILL_HW, &status) !=
	     test_bit(STATUS_RF_KILL_HW, &priv->status)))
		wiphy_rfसमाप्त_set_hw_state(priv->hw->wiphy,
			test_bit(STATUS_RF_KILL_HW, &priv->status));
पूर्ण

अटल व्योम iwlagn_rx_missed_beacon_notअगर(काष्ठा iwl_priv *priv,
					  काष्ठा iwl_rx_cmd_buffer *rxb)

अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_missed_beacon_notअगर *missed_beacon = (व्योम *)pkt->data;

	अगर (le32_to_cpu(missed_beacon->consecutive_missed_beacons) >
	    priv->missed_beacon_threshold) अणु
		IWL_DEBUG_CALIB(priv,
		    "missed bcn cnsq %d totl %d rcd %d expctd %d\n",
		    le32_to_cpu(missed_beacon->consecutive_missed_beacons),
		    le32_to_cpu(missed_beacon->total_missed_becons),
		    le32_to_cpu(missed_beacon->num_recvd_beacons),
		    le32_to_cpu(missed_beacon->num_expected_beacons));
		अगर (!test_bit(STATUS_SCANNING, &priv->status))
			iwl_init_sensitivity(priv);
	पूर्ण
पूर्ण

/* Cache phy data (Rx संकेत strength, etc) क्रम HT frame (REPLY_RX_PHY_CMD).
 * This will be used later in iwl_rx_reply_rx() क्रम REPLY_RX_MPDU_CMD. */
अटल व्योम iwlagn_rx_reply_rx_phy(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);

	priv->last_phy_res_valid = true;
	priv->ampdu_ref++;
	स_नकल(&priv->last_phy_res, pkt->data,
	       माप(काष्ठा iwl_rx_phy_res));
पूर्ण

/*
 * वापसs non-zero अगर packet should be dropped
 */
अटल पूर्णांक iwlagn_set_decrypted_flag(काष्ठा iwl_priv *priv,
				  काष्ठा ieee80211_hdr *hdr,
				  u32 decrypt_res,
				  काष्ठा ieee80211_rx_status *stats)
अणु
	u16 fc = le16_to_cpu(hdr->frame_control);

	/*
	 * All contexts have the same setting here due to it being
	 * a module parameter, so OK to check any context.
	 */
	अगर (priv->contexts[IWL_RXON_CTX_BSS].active.filter_flags &
						RXON_FILTER_DIS_DECRYPT_MSK)
		वापस 0;

	अगर (!(fc & IEEE80211_FCTL_PROTECTED))
		वापस 0;

	IWL_DEBUG_RX(priv, "decrypt_res:0x%x\n", decrypt_res);
	चयन (decrypt_res & RX_RES_STATUS_SEC_TYPE_MSK) अणु
	हाल RX_RES_STATUS_SEC_TYPE_TKIP:
		/* The uCode has got a bad phase 1 Key, pushes the packet.
		 * Decryption will be करोne in SW. */
		अगर ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_BAD_KEY_TTAK)
			अवरोध;
		fallthrough;
	हाल RX_RES_STATUS_SEC_TYPE_WEP:
		अगर ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_BAD_ICV_MIC) अणु
			/* bad ICV, the packet is destroyed since the
			 * decryption is inplace, drop it */
			IWL_DEBUG_RX(priv, "Packet destroyed\n");
			वापस -1;
		पूर्ण
		fallthrough;
	हाल RX_RES_STATUS_SEC_TYPE_CCMP:
		अगर ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_DECRYPT_OK) अणु
			IWL_DEBUG_RX(priv, "hw decrypt successfully!!!\n");
			stats->flag |= RX_FLAG_DECRYPTED;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम iwlagn_pass_packet_to_mac80211(काष्ठा iwl_priv *priv,
					काष्ठा ieee80211_hdr *hdr,
					u16 len,
					u32 ampdu_status,
					काष्ठा iwl_rx_cmd_buffer *rxb,
					काष्ठा ieee80211_rx_status *stats)
अणु
	काष्ठा sk_buff *skb;
	__le16 fc = hdr->frame_control;
	काष्ठा iwl_rxon_context *ctx;
	अचिन्हित पूर्णांक hdrlen, fraglen;

	/* We only process data packets अगर the पूर्णांकerface is खोलो */
	अगर (unlikely(!priv->is_खोलो)) अणु
		IWL_DEBUG_DROP_LIMIT(priv,
		    "Dropping packet while interface is not open.\n");
		वापस;
	पूर्ण

	/* In हाल of HW accelerated crypto and bad decryption, drop */
	अगर (!iwlwअगरi_mod_params.swcrypto &&
	    iwlagn_set_decrypted_flag(priv, hdr, ampdu_status, stats))
		वापस;

	/* Dont use dev_alloc_skb(), we'll have enough headroom once
	 * ieee80211_hdr pulled.
	 */
	skb = alloc_skb(128, GFP_ATOMIC);
	अगर (!skb) अणु
		IWL_ERR(priv, "alloc_skb failed\n");
		वापस;
	पूर्ण
	/* If frame is small enough to fit in skb->head, pull it completely.
	 * If not, only pull ieee80211_hdr so that splice() or TCP coalesce
	 * are more efficient.
	 */
	hdrlen = (len <= skb_tailroom(skb)) ? len : माप(*hdr);

	skb_put_data(skb, hdr, hdrlen);
	fraglen = len - hdrlen;

	अगर (fraglen) अणु
		पूर्णांक offset = (व्योम *)hdr + hdrlen -
			     rxb_addr(rxb) + rxb_offset(rxb);

		skb_add_rx_frag(skb, 0, rxb_steal_page(rxb), offset,
				fraglen, rxb->truesize);
	पूर्ण

	/*
	* Wake any queues that were stopped due to a passive channel tx
	* failure. This can happen because the regulatory enक्रमcement in
	* the device रुकोs क्रम a beacon beक्रमe allowing transmission,
	* someबार even after alपढ़ोy having transmitted frames क्रम the
	* association because the new RXON may reset the inक्रमmation.
	*/
	अगर (unlikely(ieee80211_is_beacon(fc) && priv->passive_no_rx)) अणु
		क्रम_each_context(priv, ctx) अणु
			अगर (!ether_addr_equal(hdr->addr3,
					      ctx->active.bssid_addr))
				जारी;
			iwlagn_lअगरt_passive_no_rx(priv);
		पूर्ण
	पूर्ण

	स_नकल(IEEE80211_SKB_RXCB(skb), stats, माप(*stats));

	ieee80211_rx_napi(priv->hw, शून्य, skb, priv->napi);
पूर्ण

अटल u32 iwlagn_translate_rx_status(काष्ठा iwl_priv *priv, u32 decrypt_in)
अणु
	u32 decrypt_out = 0;

	अगर ((decrypt_in & RX_RES_STATUS_STATION_FOUND) ==
					RX_RES_STATUS_STATION_FOUND)
		decrypt_out |= (RX_RES_STATUS_STATION_FOUND |
				RX_RES_STATUS_NO_STATION_INFO_MISMATCH);

	decrypt_out |= (decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK);

	/* packet was not encrypted */
	अगर ((decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) ==
					RX_RES_STATUS_SEC_TYPE_NONE)
		वापस decrypt_out;

	/* packet was encrypted with unknown alg */
	अगर ((decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) ==
					RX_RES_STATUS_SEC_TYPE_ERR)
		वापस decrypt_out;

	/* decryption was not करोne in HW */
	अगर ((decrypt_in & RX_MPDU_RES_STATUS_DEC_DONE_MSK) !=
					RX_MPDU_RES_STATUS_DEC_DONE_MSK)
		वापस decrypt_out;

	चयन (decrypt_in & RX_RES_STATUS_SEC_TYPE_MSK) अणु

	हाल RX_RES_STATUS_SEC_TYPE_CCMP:
		/* alg is CCM: check MIC only */
		अगर (!(decrypt_in & RX_MPDU_RES_STATUS_MIC_OK))
			/* Bad MIC */
			decrypt_out |= RX_RES_STATUS_BAD_ICV_MIC;
		अन्यथा
			decrypt_out |= RX_RES_STATUS_DECRYPT_OK;

		अवरोध;

	हाल RX_RES_STATUS_SEC_TYPE_TKIP:
		अगर (!(decrypt_in & RX_MPDU_RES_STATUS_TTAK_OK)) अणु
			/* Bad TTAK */
			decrypt_out |= RX_RES_STATUS_BAD_KEY_TTAK;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		अगर (!(decrypt_in & RX_MPDU_RES_STATUS_ICV_OK))
			decrypt_out |= RX_RES_STATUS_BAD_ICV_MIC;
		अन्यथा
			decrypt_out |= RX_RES_STATUS_DECRYPT_OK;
		अवरोध;
	पूर्ण

	IWL_DEBUG_RX(priv, "decrypt_in:0x%x  decrypt_out = 0x%x\n",
					decrypt_in, decrypt_out);

	वापस decrypt_out;
पूर्ण

/* Calc max संकेत level (dBm) among 3 possible receivers */
अटल पूर्णांक iwlagn_calc_rssi(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_rx_phy_res *rx_resp)
अणु
	/* data from PHY/DSP regarding संकेत strength, etc.,
	 *   contents are always there, not configurable by host
	 */
	काष्ठा iwlagn_non_cfg_phy *ncphy =
		(काष्ठा iwlagn_non_cfg_phy *)rx_resp->non_cfg_phy_buf;
	u32 val, rssi_a, rssi_b, rssi_c, max_rssi;
	u8 agc;

	val  = le32_to_cpu(ncphy->non_cfg_phy[IWLAGN_RX_RES_AGC_IDX]);
	agc = (val & IWLAGN_OFDM_AGC_MSK) >> IWLAGN_OFDM_AGC_BIT_POS;

	/* Find max rssi among 3 possible receivers.
	 * These values are measured by the digital संकेत processor (DSP).
	 * They should stay fairly स्थिरant even as the संकेत strength varies,
	 *   अगर the radio's स्वतःmatic gain control (AGC) is working right.
	 * AGC value (see below) will provide the "interesting" info.
	 */
	val = le32_to_cpu(ncphy->non_cfg_phy[IWLAGN_RX_RES_RSSI_AB_IDX]);
	rssi_a = (val & IWLAGN_OFDM_RSSI_INBAND_A_BITMSK) >>
		IWLAGN_OFDM_RSSI_A_BIT_POS;
	rssi_b = (val & IWLAGN_OFDM_RSSI_INBAND_B_BITMSK) >>
		IWLAGN_OFDM_RSSI_B_BIT_POS;
	val = le32_to_cpu(ncphy->non_cfg_phy[IWLAGN_RX_RES_RSSI_C_IDX]);
	rssi_c = (val & IWLAGN_OFDM_RSSI_INBAND_C_BITMSK) >>
		IWLAGN_OFDM_RSSI_C_BIT_POS;

	max_rssi = max_t(u32, rssi_a, rssi_b);
	max_rssi = max_t(u32, max_rssi, rssi_c);

	IWL_DEBUG_STATS(priv, "Rssi In A %d B %d C %d Max %d AGC dB %d\n",
		rssi_a, rssi_b, rssi_c, max_rssi, agc);

	/* dBm = max_rssi dB - agc dB - स्थिरant.
	 * Higher AGC (higher radio gain) means lower संकेत. */
	वापस max_rssi - agc - IWLAGN_RSSI_OFFSET;
पूर्ण

/* Called क्रम REPLY_RX_MPDU_CMD */
अटल व्योम iwlagn_rx_reply_rx(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा ieee80211_hdr *header;
	काष्ठा ieee80211_rx_status rx_status = अणुपूर्ण;
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_rx_phy_res *phy_res;
	__le32 rx_pkt_status;
	काष्ठा iwl_rx_mpdu_res_start *amsdu;
	u32 len, pkt_len = iwl_rx_packet_len(pkt);
	u32 ampdu_status;
	u32 rate_n_flags;

	अगर (!priv->last_phy_res_valid) अणु
		IWL_ERR(priv, "MPDU frame without cached PHY data\n");
		वापस;
	पूर्ण

	अगर (unlikely(pkt_len < माप(*amsdu))) अणु
		IWL_DEBUG_DROP(priv, "Bad REPLY_RX_MPDU_CMD size\n");
		वापस;
	पूर्ण

	phy_res = &priv->last_phy_res;
	amsdu = (काष्ठा iwl_rx_mpdu_res_start *)pkt->data;
	header = (काष्ठा ieee80211_hdr *)(pkt->data + माप(*amsdu));
	len = le16_to_cpu(amsdu->byte_count);

	अगर (unlikely(len + माप(*amsdu) + माप(__le32) > pkt_len)) अणु
		IWL_DEBUG_DROP(priv, "FW lied about packet len\n");
		वापस;
	पूर्ण

	rx_pkt_status = *(__le32 *)(pkt->data + माप(*amsdu) + len);
	ampdu_status = iwlagn_translate_rx_status(priv,
						  le32_to_cpu(rx_pkt_status));

	अगर ((unlikely(phy_res->cfg_phy_cnt > 20))) अणु
		IWL_DEBUG_DROP(priv, "dsp size out of range [0,20]: %d\n",
				phy_res->cfg_phy_cnt);
		वापस;
	पूर्ण

	अगर (!(rx_pkt_status & RX_RES_STATUS_NO_CRC32_ERROR) ||
	    !(rx_pkt_status & RX_RES_STATUS_NO_RXE_OVERFLOW)) अणु
		IWL_DEBUG_RX(priv, "Bad CRC or FIFO: 0x%08X.\n",
				le32_to_cpu(rx_pkt_status));
		वापस;
	पूर्ण

	/* This will be used in several places later */
	rate_n_flags = le32_to_cpu(phy_res->rate_n_flags);

	/* rx_status carries inक्रमmation about the packet to mac80211 */
	rx_status.maस_समय = le64_to_cpu(phy_res->बारtamp);
	rx_status.band = (phy_res->phy_flags & RX_RES_PHY_FLAGS_BAND_24_MSK) ?
				NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
	rx_status.freq =
		ieee80211_channel_to_frequency(le16_to_cpu(phy_res->channel),
					       rx_status.band);
	rx_status.rate_idx =
		iwlagn_hwrate_to_mac80211_idx(rate_n_flags, rx_status.band);
	rx_status.flag = 0;

	/* TSF isn't reliable. In order to allow smooth user experience,
	 * this W/A करोesn't propagate it to the mac80211 */
	/*rx_status.flag |= RX_FLAG_MACTIME_START;*/

	priv->ucode_beacon_समय = le32_to_cpu(phy_res->beacon_समय_stamp);

	/* Find max संकेत strength (dBm) among 3 antenna/receiver chains */
	rx_status.संकेत = iwlagn_calc_rssi(priv, phy_res);

	IWL_DEBUG_STATS_LIMIT(priv, "Rssi %d, TSF %llu\n",
		rx_status.संकेत, (अचिन्हित दीर्घ दीर्घ)rx_status.maस_समय);

	/*
	 * "antenna number"
	 *
	 * It seems that the antenna field in the phy flags value
	 * is actually a bit field. This is undefined by radiotap,
	 * it wants an actual antenna number but I always get "7"
	 * क्रम most legacy frames I receive indicating that the
	 * same frame was received on all three RX chains.
	 *
	 * I think this field should be हटाओd in favor of a
	 * new 802.11n radiotap field "RX chains" that is defined
	 * as a biपंचांगask.
	 */
	rx_status.antenna =
		(le16_to_cpu(phy_res->phy_flags) & RX_RES_PHY_FLAGS_ANTENNA_MSK)
		>> RX_RES_PHY_FLAGS_ANTENNA_POS;

	/* set the preamble flag अगर appropriate */
	अगर (phy_res->phy_flags & RX_RES_PHY_FLAGS_SHORT_PREAMBLE_MSK)
		rx_status.enc_flags |= RX_ENC_FLAG_SHORTPRE;

	अगर (phy_res->phy_flags & RX_RES_PHY_FLAGS_AGG_MSK) अणु
		/*
		 * We know which subframes of an A-MPDU beदीर्घ
		 * together since we get a single PHY response
		 * from the firmware क्रम all of them
		 */
		rx_status.flag |= RX_FLAG_AMPDU_DETAILS;
		rx_status.ampdu_reference = priv->ampdu_ref;
	पूर्ण

	/* Set up the HT phy flags */
	अगर (rate_n_flags & RATE_MCS_HT_MSK)
		rx_status.encoding = RX_ENC_HT;
	अगर (rate_n_flags & RATE_MCS_HT40_MSK)
		rx_status.bw = RATE_INFO_BW_40;
	अन्यथा
		rx_status.bw = RATE_INFO_BW_20;
	अगर (rate_n_flags & RATE_MCS_SGI_MSK)
		rx_status.enc_flags |= RX_ENC_FLAG_SHORT_GI;
	अगर (rate_n_flags & RATE_MCS_GF_MSK)
		rx_status.enc_flags |= RX_ENC_FLAG_HT_GF;

	iwlagn_pass_packet_to_mac80211(priv, header, len, ampdu_status,
				    rxb, &rx_status);
पूर्ण

अटल व्योम iwlagn_rx_noa_notअगरication(काष्ठा iwl_priv *priv,
				       काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_wipan_noa_data *new_data, *old_data;
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_wipan_noa_notअगरication *noa_notअगर = (व्योम *)pkt->data;

	/* no condition -- we're in softirq */
	old_data = rcu_dereference_रक्षित(priv->noa_data, true);

	अगर (noa_notअगर->noa_active) अणु
		u32 len = le16_to_cpu(noa_notअगर->noa_attribute.length);
		u32 copylen = len;

		/* EID, len, OUI, subtype */
		len += 1 + 1 + 3 + 1;
		/* P2P id, P2P length */
		len += 1 + 2;
		copylen += 1 + 2;

		new_data = kदो_स्मृति(माप(*new_data) + len, GFP_ATOMIC);
		अगर (new_data) अणु
			new_data->length = len;
			new_data->data[0] = WLAN_EID_VENDOR_SPECIFIC;
			new_data->data[1] = len - 2; /* not counting EID, len */
			new_data->data[2] = (WLAN_OUI_WFA >> 16) & 0xff;
			new_data->data[3] = (WLAN_OUI_WFA >> 8) & 0xff;
			new_data->data[4] = (WLAN_OUI_WFA >> 0) & 0xff;
			new_data->data[5] = WLAN_OUI_TYPE_WFA_P2P;
			स_नकल(&new_data->data[6], &noa_notअगर->noa_attribute,
			       copylen);
		पूर्ण
	पूर्ण अन्यथा
		new_data = शून्य;

	rcu_assign_poपूर्णांकer(priv->noa_data, new_data);

	अगर (old_data)
		kमुक्त_rcu(old_data, rcu_head);
पूर्ण

/*
 * iwl_setup_rx_handlers - Initialize Rx handler callbacks
 *
 * Setup the RX handlers क्रम each of the reply types sent from the uCode
 * to the host.
 */
व्योम iwl_setup_rx_handlers(काष्ठा iwl_priv *priv)
अणु
	व्योम (**handlers)(काष्ठा iwl_priv *priv, काष्ठा iwl_rx_cmd_buffer *rxb);

	handlers = priv->rx_handlers;

	handlers[REPLY_ERROR]			= iwlagn_rx_reply_error;
	handlers[CHANNEL_SWITCH_NOTIFICATION]	= iwlagn_rx_csa;
	handlers[SPECTRUM_MEASURE_NOTIFICATION]	=
		iwlagn_rx_spectrum_measure_notअगर;
	handlers[PM_SLEEP_NOTIFICATION]		= iwlagn_rx_pm_sleep_notअगर;
	handlers[PM_DEBUG_STATISTIC_NOTIFIC]	=
		iwlagn_rx_pm_debug_statistics_notअगर;
	handlers[BEACON_NOTIFICATION]		= iwlagn_rx_beacon_notअगर;
	handlers[REPLY_ADD_STA]			= iwl_add_sta_callback;

	handlers[REPLY_WIPAN_NOA_NOTIFICATION]	= iwlagn_rx_noa_notअगरication;

	/*
	 * The same handler is used क्रम both the REPLY to a discrete
	 * statistics request from the host as well as क्रम the periodic
	 * statistics notअगरications (after received beacons) from the uCode.
	 */
	handlers[REPLY_STATISTICS_CMD]		= iwlagn_rx_reply_statistics;
	handlers[STATISTICS_NOTIFICATION]	= iwlagn_rx_statistics;

	iwl_setup_rx_scan_handlers(priv);

	handlers[CARD_STATE_NOTIFICATION]	= iwlagn_rx_card_state_notअगर;
	handlers[MISSED_BEACONS_NOTIFICATION]	=
		iwlagn_rx_missed_beacon_notअगर;

	/* Rx handlers */
	handlers[REPLY_RX_PHY_CMD]		= iwlagn_rx_reply_rx_phy;
	handlers[REPLY_RX_MPDU_CMD]		= iwlagn_rx_reply_rx;

	/* block ack */
	handlers[REPLY_COMPRESSED_BA]		=
		iwlagn_rx_reply_compressed_ba;

	priv->rx_handlers[REPLY_TX] = iwlagn_rx_reply_tx;

	/* set up notअगरication रुको support */
	iwl_notअगरication_रुको_init(&priv->notअगर_रुको);

	/* Set up BT Rx handlers */
	अगर (priv->lib->bt_params)
		iwlagn_bt_rx_handler_setup(priv);
पूर्ण

व्योम iwl_rx_dispatch(काष्ठा iwl_op_mode *op_mode, काष्ठा napi_काष्ठा *napi,
		     काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	/*
	 * Do the notअगरication रुको beक्रमe RX handlers so
	 * even अगर the RX handler consumes the RXB we have
	 * access to it in the notअगरication रुको entry.
	 */
	iwl_notअगरication_रुको_notअगरy(&priv->notअगर_रुको, pkt);

	/* Based on type of command response or notअगरication,
	 *   handle those that need handling via function in
	 *   rx_handlers table.  See iwl_setup_rx_handlers() */
	अगर (priv->rx_handlers[pkt->hdr.cmd]) अणु
		priv->rx_handlers_stats[pkt->hdr.cmd]++;
		priv->rx_handlers[pkt->hdr.cmd](priv, rxb);
	पूर्ण अन्यथा अणु
		/* No handling needed */
		IWL_DEBUG_RX(priv, "No handler needed for %s, 0x%02x\n",
			     iwl_get_cmd_string(priv->trans,
						iwl_cmd_id(pkt->hdr.cmd,
							   0, 0)),
			     pkt->hdr.cmd);
	पूर्ण
पूर्ण
