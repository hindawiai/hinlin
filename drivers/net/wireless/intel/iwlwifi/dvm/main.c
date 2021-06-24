<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014, 2018 - 2020  Intel Corporation. All rights reserved.
 * Copyright(c) 2015 Intel Deutschland GmbH
 *
 * Portions of this file are derived from the ipw3945 project, as well
 * as portions of the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>

#समावेश <net/mac80211.h>

#समावेश <यंत्र/भाग64.h>

#समावेश "iwl-eeprom-read.h"
#समावेश "iwl-eeprom-parse.h"
#समावेश "iwl-io.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-op-mode.h"
#समावेश "iwl-drv.h"
#समावेश "iwl-modparams.h"
#समावेश "iwl-prph.h"

#समावेश "dev.h"
#समावेश "calib.h"
#समावेश "agn.h"


/******************************************************************************
 *
 * module boiler plate
 *
 ******************************************************************************/

#घोषणा DRV_DESCRIPTION	"Intel(R) Wireless WiFi Link AGN driver for Linux"
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_LICENSE("GPL");

/* Please keep this array *SORTED* by hex value.
 * Access is करोne through binary search.
 * A warning will be triggered on violation.
 */
अटल स्थिर काष्ठा iwl_hcmd_names iwl_dvm_cmd_names[] = अणु
	HCMD_NAME(REPLY_ALIVE),
	HCMD_NAME(REPLY_ERROR),
	HCMD_NAME(REPLY_ECHO),
	HCMD_NAME(REPLY_RXON),
	HCMD_NAME(REPLY_RXON_ASSOC),
	HCMD_NAME(REPLY_QOS_PARAM),
	HCMD_NAME(REPLY_RXON_TIMING),
	HCMD_NAME(REPLY_ADD_STA),
	HCMD_NAME(REPLY_REMOVE_STA),
	HCMD_NAME(REPLY_REMOVE_ALL_STA),
	HCMD_NAME(REPLY_TX),
	HCMD_NAME(REPLY_TXFIFO_FLUSH),
	HCMD_NAME(REPLY_WEPKEY),
	HCMD_NAME(REPLY_LEDS_CMD),
	HCMD_NAME(REPLY_TX_LINK_QUALITY_CMD),
	HCMD_NAME(COEX_PRIORITY_TABLE_CMD),
	HCMD_NAME(COEX_MEDIUM_NOTIFICATION),
	HCMD_NAME(COEX_EVENT_CMD),
	HCMD_NAME(TEMPERATURE_NOTIFICATION),
	HCMD_NAME(CALIBRATION_CFG_CMD),
	HCMD_NAME(CALIBRATION_RES_NOTIFICATION),
	HCMD_NAME(CALIBRATION_COMPLETE_NOTIFICATION),
	HCMD_NAME(REPLY_QUIET_CMD),
	HCMD_NAME(REPLY_CHANNEL_SWITCH),
	HCMD_NAME(CHANNEL_SWITCH_NOTIFICATION),
	HCMD_NAME(REPLY_SPECTRUM_MEASUREMENT_CMD),
	HCMD_NAME(SPECTRUM_MEASURE_NOTIFICATION),
	HCMD_NAME(POWER_TABLE_CMD),
	HCMD_NAME(PM_SLEEP_NOTIFICATION),
	HCMD_NAME(PM_DEBUG_STATISTIC_NOTIFIC),
	HCMD_NAME(REPLY_SCAN_CMD),
	HCMD_NAME(REPLY_SCAN_ABORT_CMD),
	HCMD_NAME(SCAN_START_NOTIFICATION),
	HCMD_NAME(SCAN_RESULTS_NOTIFICATION),
	HCMD_NAME(SCAN_COMPLETE_NOTIFICATION),
	HCMD_NAME(BEACON_NOTIFICATION),
	HCMD_NAME(REPLY_TX_BEACON),
	HCMD_NAME(WHO_IS_AWAKE_NOTIFICATION),
	HCMD_NAME(REPLY_TX_POWER_DBM_CMD),
	HCMD_NAME(QUIET_NOTIFICATION),
	HCMD_NAME(REPLY_TX_PWR_TABLE_CMD),
	HCMD_NAME(REPLY_TX_POWER_DBM_CMD_V1),
	HCMD_NAME(TX_ANT_CONFIGURATION_CMD),
	HCMD_NAME(MEASURE_ABORT_NOTIFICATION),
	HCMD_NAME(REPLY_BT_CONFIG),
	HCMD_NAME(REPLY_STATISTICS_CMD),
	HCMD_NAME(STATISTICS_NOTIFICATION),
	HCMD_NAME(REPLY_CARD_STATE_CMD),
	HCMD_NAME(CARD_STATE_NOTIFICATION),
	HCMD_NAME(MISSED_BEACONS_NOTIFICATION),
	HCMD_NAME(REPLY_CT_KILL_CONFIG_CMD),
	HCMD_NAME(SENSITIVITY_CMD),
	HCMD_NAME(REPLY_PHY_CALIBRATION_CMD),
	HCMD_NAME(REPLY_WIPAN_PARAMS),
	HCMD_NAME(REPLY_WIPAN_RXON),
	HCMD_NAME(REPLY_WIPAN_RXON_TIMING),
	HCMD_NAME(REPLY_WIPAN_RXON_ASSOC),
	HCMD_NAME(REPLY_WIPAN_QOS_PARAM),
	HCMD_NAME(REPLY_WIPAN_WEPKEY),
	HCMD_NAME(REPLY_WIPAN_P2P_CHANNEL_SWITCH),
	HCMD_NAME(REPLY_WIPAN_NOA_NOTIFICATION),
	HCMD_NAME(REPLY_WIPAN_DEACTIVATION_COMPLETE),
	HCMD_NAME(REPLY_RX_PHY_CMD),
	HCMD_NAME(REPLY_RX_MPDU_CMD),
	HCMD_NAME(REPLY_RX),
	HCMD_NAME(REPLY_COMPRESSED_BA),
	HCMD_NAME(REPLY_BT_COEX_PRIO_TABLE),
	HCMD_NAME(REPLY_BT_COEX_PROT_ENV),
	HCMD_NAME(REPLY_BT_COEX_PROखाता_NOTIF),
	HCMD_NAME(REPLY_D3_CONFIG),
	HCMD_NAME(REPLY_WOWLAN_PATTERNS),
	HCMD_NAME(REPLY_WOWLAN_WAKEUP_FILTER),
	HCMD_NAME(REPLY_WOWLAN_TSC_RSC_PARAMS),
	HCMD_NAME(REPLY_WOWLAN_TKIP_PARAMS),
	HCMD_NAME(REPLY_WOWLAN_KEK_KCK_MATERIAL),
	HCMD_NAME(REPLY_WOWLAN_GET_STATUS),
पूर्ण;

अटल स्थिर काष्ठा iwl_hcmd_arr iwl_dvm_groups[] = अणु
	[0x0] = HCMD_ARR(iwl_dvm_cmd_names),
पूर्ण;

अटल स्थिर काष्ठा iwl_op_mode_ops iwl_dvm_ops;

व्योम iwl_update_chain_flags(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_rxon_context *ctx;

	क्रम_each_context(priv, ctx) अणु
		iwlagn_set_rxon_chain(priv, ctx);
		अगर (ctx->active.rx_chain != ctx->staging.rx_chain)
			iwlagn_commit_rxon(priv, ctx);
	पूर्ण
पूर्ण

/* Parse the beacon frame to find the TIM element and set tim_idx & tim_size */
अटल व्योम iwl_set_beacon_tim(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_tx_beacon_cmd *tx_beacon_cmd,
			       u8 *beacon, u32 frame_size)
अणु
	u16 tim_idx;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)beacon;

	/*
	 * The index is relative to frame start but we start looking at the
	 * variable-length part of the beacon.
	 */
	tim_idx = mgmt->u.beacon.variable - beacon;

	/* Parse variable-length elements of beacon to find WLAN_EID_TIM */
	जबतक ((tim_idx < (frame_size - 2)) &&
			(beacon[tim_idx] != WLAN_EID_TIM))
		tim_idx += beacon[tim_idx+1] + 2;

	/* If TIM field was found, set variables */
	अगर ((tim_idx < (frame_size - 1)) && (beacon[tim_idx] == WLAN_EID_TIM)) अणु
		tx_beacon_cmd->tim_idx = cpu_to_le16(tim_idx);
		tx_beacon_cmd->tim_size = beacon[tim_idx+1];
	पूर्ण अन्यथा
		IWL_WARN(priv, "Unable to find TIM Element in beacon\n");
पूर्ण

पूर्णांक iwlagn_send_beacon_cmd(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_tx_beacon_cmd *tx_beacon_cmd;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_TX_BEACON,
	पूर्ण;
	काष्ठा ieee80211_tx_info *info;
	u32 frame_size;
	u32 rate_flags;
	u32 rate;

	/*
	 * We have to set up the TX command, the TX Beacon command, and the
	 * beacon contents.
	 */

	lockdep_निश्चित_held(&priv->mutex);

	अगर (!priv->beacon_ctx) अणु
		IWL_ERR(priv, "trying to build beacon w/o beacon context!\n");
		वापस 0;
	पूर्ण

	अगर (WARN_ON(!priv->beacon_skb))
		वापस -EINVAL;

	/* Allocate beacon command */
	अगर (!priv->beacon_cmd)
		priv->beacon_cmd = kzalloc(माप(*tx_beacon_cmd), GFP_KERNEL);
	tx_beacon_cmd = priv->beacon_cmd;
	अगर (!tx_beacon_cmd)
		वापस -ENOMEM;

	frame_size = priv->beacon_skb->len;

	/* Set up TX command fields */
	tx_beacon_cmd->tx.len = cpu_to_le16((u16)frame_size);
	tx_beacon_cmd->tx.sta_id = priv->beacon_ctx->bcast_sta_id;
	tx_beacon_cmd->tx.stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;
	tx_beacon_cmd->tx.tx_flags = TX_CMD_FLG_SEQ_CTL_MSK |
		TX_CMD_FLG_TSF_MSK | TX_CMD_FLG_STA_RATE_MSK;

	/* Set up TX beacon command fields */
	iwl_set_beacon_tim(priv, tx_beacon_cmd, priv->beacon_skb->data,
			   frame_size);

	/* Set up packet rate and flags */
	info = IEEE80211_SKB_CB(priv->beacon_skb);

	/*
	 * Let's set up the rate at least somewhat correctly;
	 * it will currently not actually be used by the uCode,
	 * it uses the broadcast station's rate instead.
	 */
	अगर (info->control.rates[0].idx < 0 ||
	    info->control.rates[0].flags & IEEE80211_TX_RC_MCS)
		rate = 0;
	अन्यथा
		rate = info->control.rates[0].idx;

	priv->mgmt_tx_ant = iwl_toggle_tx_ant(priv, priv->mgmt_tx_ant,
					      priv->nvm_data->valid_tx_ant);
	rate_flags = iwl_ant_idx_to_flags(priv->mgmt_tx_ant);

	/* In mac80211, rates क्रम 5 GHz start at 0 */
	अगर (info->band == NL80211_BAND_5GHZ)
		rate += IWL_FIRST_OFDM_RATE;
	अन्यथा अगर (rate >= IWL_FIRST_CCK_RATE && rate <= IWL_LAST_CCK_RATE)
		rate_flags |= RATE_MCS_CCK_MSK;

	tx_beacon_cmd->tx.rate_n_flags =
			iwl_hw_set_rate_n_flags(rate, rate_flags);

	/* Submit command */
	cmd.len[0] = माप(*tx_beacon_cmd);
	cmd.data[0] = tx_beacon_cmd;
	cmd.dataflags[0] = IWL_HCMD_DFL_NOCOPY;
	cmd.len[1] = frame_size;
	cmd.data[1] = priv->beacon_skb->data;
	cmd.dataflags[1] = IWL_HCMD_DFL_NOCOPY;

	वापस iwl_dvm_send_cmd(priv, &cmd);
पूर्ण

अटल व्योम iwl_bg_beacon_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv =
		container_of(work, काष्ठा iwl_priv, beacon_update);
	काष्ठा sk_buff *beacon;

	mutex_lock(&priv->mutex);
	अगर (!priv->beacon_ctx) अणु
		IWL_ERR(priv, "updating beacon w/o beacon context!\n");
		जाओ out;
	पूर्ण

	अगर (priv->beacon_ctx->vअगर->type != NL80211_IFTYPE_AP) अणु
		/*
		 * The ucode will send beacon notअगरications even in
		 * IBSS mode, but we करोn't want to process them. But
		 * we need to defer the type check to here due to
		 * requiring locking around the beacon_ctx access.
		 */
		जाओ out;
	पूर्ण

	/* Pull updated AP beacon from mac80211. will fail अगर not in AP mode */
	beacon = ieee80211_beacon_get(priv->hw, priv->beacon_ctx->vअगर);
	अगर (!beacon) अणु
		IWL_ERR(priv, "update beacon failed -- keeping old\n");
		जाओ out;
	पूर्ण

	/* new beacon skb is allocated every समय; dispose previous.*/
	dev_kमुक्त_skb(priv->beacon_skb);

	priv->beacon_skb = beacon;

	iwlagn_send_beacon_cmd(priv);
 out:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम iwl_bg_bt_runसमय_config(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv =
		container_of(work, काष्ठा iwl_priv, bt_runसमय_config);

	mutex_lock(&priv->mutex);
	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		जाओ out;

	/* करोnt send host command अगर rf-समाप्त is on */
	अगर (!iwl_is_पढ़ोy_rf(priv))
		जाओ out;

	iwlagn_send_advance_bt_config(priv);
out:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल व्योम iwl_bg_bt_full_concurrency(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv =
		container_of(work, काष्ठा iwl_priv, bt_full_concurrency);
	काष्ठा iwl_rxon_context *ctx;

	mutex_lock(&priv->mutex);

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		जाओ out;

	/* करोnt send host command अगर rf-समाप्त is on */
	अगर (!iwl_is_पढ़ोy_rf(priv))
		जाओ out;

	IWL_DEBUG_INFO(priv, "BT coex in %s mode\n",
		       priv->bt_full_concurrent ?
		       "full concurrency" : "3-wire");

	/*
	 * LQ & RXON updated cmds must be sent beक्रमe BT Config cmd
	 * to aव्योम 3-wire collisions
	 */
	क्रम_each_context(priv, ctx) अणु
		iwlagn_set_rxon_chain(priv, ctx);
		iwlagn_commit_rxon(priv, ctx);
	पूर्ण

	iwlagn_send_advance_bt_config(priv);
out:
	mutex_unlock(&priv->mutex);
पूर्ण

पूर्णांक iwl_send_statistics_request(काष्ठा iwl_priv *priv, u8 flags, bool clear)
अणु
	काष्ठा iwl_statistics_cmd statistics_cmd = अणु
		.configuration_flags =
			clear ? IWL_STATS_CONF_CLEAR_STATS : 0,
	पूर्ण;

	अगर (flags & CMD_ASYNC)
		वापस iwl_dvm_send_cmd_pdu(priv, REPLY_STATISTICS_CMD,
					CMD_ASYNC,
					माप(काष्ठा iwl_statistics_cmd),
					&statistics_cmd);
	अन्यथा
		वापस iwl_dvm_send_cmd_pdu(priv, REPLY_STATISTICS_CMD, 0,
					माप(काष्ठा iwl_statistics_cmd),
					&statistics_cmd);
पूर्ण

/*
 * iwl_bg_statistics_periodic - Timer callback to queue statistics
 *
 * This callback is provided in order to send a statistics request.
 *
 * This समयr function is continually reset to execute within
 * REG_RECALIB_PERIOD seconds since the last STATISTICS_NOTIFICATION
 * was received.  We need to ensure we receive the statistics in order
 * to update the temperature used क्रम calibrating the TXPOWER.
 */
अटल व्योम iwl_bg_statistics_periodic(काष्ठा समयr_list *t)
अणु
	काष्ठा iwl_priv *priv = from_समयr(priv, t, statistics_periodic);

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	/* करोnt send host command अगर rf-समाप्त is on */
	अगर (!iwl_is_पढ़ोy_rf(priv))
		वापस;

	iwl_send_statistics_request(priv, CMD_ASYNC, false);
पूर्ण


अटल व्योम iwl_prपूर्णांक_cont_event_trace(काष्ठा iwl_priv *priv, u32 base,
					u32 start_idx, u32 num_events,
					u32 capacity, u32 mode)
अणु
	u32 i;
	u32 ptr;        /* SRAM byte address of log data */
	u32 ev, समय, data; /* event log data */

	अगर (mode == 0)
		ptr = base + (4 * माप(u32)) + (start_idx * 2 * माप(u32));
	अन्यथा
		ptr = base + (4 * माप(u32)) + (start_idx * 3 * माप(u32));

	/* Make sure device is घातered up क्रम SRAM पढ़ोs */
	अगर (!iwl_trans_grab_nic_access(priv->trans))
		वापस;

	/* Set starting address; पढ़ोs will स्वतः-increment */
	iwl_ग_लिखो32(priv->trans, HBUS_TARG_MEM_RADDR, ptr);

	/*
	 * Refuse to पढ़ो more than would have fit पूर्णांकo the log from
	 * the current start_idx. This used to happen due to the race
	 * described below, but now WARN because the code below should
	 * prevent it from happening here.
	 */
	अगर (WARN_ON(num_events > capacity - start_idx))
		num_events = capacity - start_idx;

	/*
	 * "time" is actually "data" क्रम mode 0 (no बारtamp).
	 * place event id # at far right क्रम easier visual parsing.
	 */
	क्रम (i = 0; i < num_events; i++) अणु
		ev = iwl_पढ़ो32(priv->trans, HBUS_TARG_MEM_RDAT);
		समय = iwl_पढ़ो32(priv->trans, HBUS_TARG_MEM_RDAT);
		अगर (mode == 0) अणु
			trace_iwlwअगरi_dev_ucode_cont_event(
					priv->trans->dev, 0, समय, ev);
		पूर्ण अन्यथा अणु
			data = iwl_पढ़ो32(priv->trans, HBUS_TARG_MEM_RDAT);
			trace_iwlwअगरi_dev_ucode_cont_event(
					priv->trans->dev, समय, data, ev);
		पूर्ण
	पूर्ण
	/* Allow device to घातer करोwn */
	iwl_trans_release_nic_access(priv->trans);
पूर्ण

अटल व्योम iwl_continuous_event_trace(काष्ठा iwl_priv *priv)
अणु
	u32 capacity;   /* event log capacity in # entries */
	काष्ठा अणु
		u32 capacity;
		u32 mode;
		u32 wrap_counter;
		u32 ग_लिखो_counter;
	पूर्ण __packed पढ़ो;
	u32 base;       /* SRAM byte address of event log header */
	u32 mode;       /* 0 - no बारtamp, 1 - बारtamp recorded */
	u32 num_wraps;  /* # बार uCode wrapped to top of log */
	u32 next_entry; /* index of next entry to be written by uCode */

	base = priv->device_poपूर्णांकers.log_event_table;
	अगर (iwlagn_hw_valid_rtc_data_addr(base)) अणु
		iwl_trans_पढ़ो_mem_bytes(priv->trans, base,
					 &पढ़ो, माप(पढ़ो));
		capacity = पढ़ो.capacity;
		mode = पढ़ो.mode;
		num_wraps = पढ़ो.wrap_counter;
		next_entry = पढ़ो.ग_लिखो_counter;
	पूर्ण अन्यथा
		वापस;

	/*
	 * Unक्रमtunately, the uCode करोesn't use temporary variables.
	 * Thereक्रमe, it can happen that we पढ़ो next_entry == capacity,
	 * which really means next_entry == 0.
	 */
	अगर (unlikely(next_entry == capacity))
		next_entry = 0;
	/*
	 * Additionally, the uCode increases the ग_लिखो poपूर्णांकer beक्रमe
	 * the wraps counter, so अगर the ग_लिखो poपूर्णांकer is smaller than
	 * the old ग_लिखो poपूर्णांकer (wrap occurred) but we पढ़ो that no
	 * wrap occurred, we actually पढ़ो between the next_entry and
	 * num_wraps update (this करोes happen in practice!!) -- take
	 * that पूर्णांकo account by increasing num_wraps.
	 */
	अगर (unlikely(next_entry < priv->event_log.next_entry &&
		     num_wraps == priv->event_log.num_wraps))
		num_wraps++;

	अगर (num_wraps == priv->event_log.num_wraps) अणु
		iwl_prपूर्णांक_cont_event_trace(
			priv, base, priv->event_log.next_entry,
			next_entry - priv->event_log.next_entry,
			capacity, mode);

		priv->event_log.non_wraps_count++;
	पूर्ण अन्यथा अणु
		अगर (num_wraps - priv->event_log.num_wraps > 1)
			priv->event_log.wraps_more_count++;
		अन्यथा
			priv->event_log.wraps_once_count++;

		trace_iwlwअगरi_dev_ucode_wrap_event(priv->trans->dev,
				num_wraps - priv->event_log.num_wraps,
				next_entry, priv->event_log.next_entry);

		अगर (next_entry < priv->event_log.next_entry) अणु
			iwl_prपूर्णांक_cont_event_trace(
				priv, base, priv->event_log.next_entry,
				capacity - priv->event_log.next_entry,
				capacity, mode);

			iwl_prपूर्णांक_cont_event_trace(
				priv, base, 0, next_entry, capacity, mode);
		पूर्ण अन्यथा अणु
			iwl_prपूर्णांक_cont_event_trace(
				priv, base, next_entry,
				capacity - next_entry,
				capacity, mode);

			iwl_prपूर्णांक_cont_event_trace(
				priv, base, 0, next_entry, capacity, mode);
		पूर्ण
	पूर्ण

	priv->event_log.num_wraps = num_wraps;
	priv->event_log.next_entry = next_entry;
पूर्ण

/*
 * iwl_bg_ucode_trace - Timer callback to log ucode event
 *
 * The समयr is continually set to execute every
 * UCODE_TRACE_PERIOD milliseconds after the last समयr expired
 * this function is to perक्रमm continuous uCode event logging operation
 * अगर enabled
 */
अटल व्योम iwl_bg_ucode_trace(काष्ठा समयr_list *t)
अणु
	काष्ठा iwl_priv *priv = from_समयr(priv, t, ucode_trace);

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	अगर (priv->event_log.ucode_trace) अणु
		iwl_continuous_event_trace(priv);
		/* Reschedule the समयr to occur in UCODE_TRACE_PERIOD */
		mod_समयr(&priv->ucode_trace,
			 jअगरfies + msecs_to_jअगरfies(UCODE_TRACE_PERIOD));
	पूर्ण
पूर्ण

अटल व्योम iwl_bg_tx_flush(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv =
		container_of(work, काष्ठा iwl_priv, tx_flush);

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	/* करो nothing अगर rf-समाप्त is on */
	अगर (!iwl_is_पढ़ोy_rf(priv))
		वापस;

	IWL_DEBUG_INFO(priv, "device request: flush all tx frames\n");
	iwlagn_dev_txfअगरo_flush(priv);
पूर्ण

/*
 * queue/FIFO/AC mapping definitions
 */

अटल स्थिर u8 iwlagn_bss_ac_to_fअगरo[] = अणु
	IWL_TX_FIFO_VO,
	IWL_TX_FIFO_VI,
	IWL_TX_FIFO_BE,
	IWL_TX_FIFO_BK,
पूर्ण;

अटल स्थिर u8 iwlagn_bss_ac_to_queue[] = अणु
	0, 1, 2, 3,
पूर्ण;

अटल स्थिर u8 iwlagn_pan_ac_to_fअगरo[] = अणु
	IWL_TX_FIFO_VO_IPAN,
	IWL_TX_FIFO_VI_IPAN,
	IWL_TX_FIFO_BE_IPAN,
	IWL_TX_FIFO_BK_IPAN,
पूर्ण;

अटल स्थिर u8 iwlagn_pan_ac_to_queue[] = अणु
	7, 6, 5, 4,
पूर्ण;

अटल व्योम iwl_init_context(काष्ठा iwl_priv *priv, u32 ucode_flags)
अणु
	पूर्णांक i;

	/*
	 * The शेष context is always valid,
	 * the PAN context depends on uCode.
	 */
	priv->valid_contexts = BIT(IWL_RXON_CTX_BSS);
	अगर (ucode_flags & IWL_UCODE_TLV_FLAGS_PAN)
		priv->valid_contexts |= BIT(IWL_RXON_CTX_PAN);

	क्रम (i = 0; i < NUM_IWL_RXON_CTX; i++)
		priv->contexts[i].ctxid = i;

	priv->contexts[IWL_RXON_CTX_BSS].always_active = true;
	priv->contexts[IWL_RXON_CTX_BSS].is_active = true;
	priv->contexts[IWL_RXON_CTX_BSS].rxon_cmd = REPLY_RXON;
	priv->contexts[IWL_RXON_CTX_BSS].rxon_timing_cmd = REPLY_RXON_TIMING;
	priv->contexts[IWL_RXON_CTX_BSS].rxon_assoc_cmd = REPLY_RXON_ASSOC;
	priv->contexts[IWL_RXON_CTX_BSS].qos_cmd = REPLY_QOS_PARAM;
	priv->contexts[IWL_RXON_CTX_BSS].ap_sta_id = IWL_AP_ID;
	priv->contexts[IWL_RXON_CTX_BSS].wep_key_cmd = REPLY_WEPKEY;
	priv->contexts[IWL_RXON_CTX_BSS].bcast_sta_id = IWLAGN_BROADCAST_ID;
	priv->contexts[IWL_RXON_CTX_BSS].exclusive_पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_ADHOC) | BIT(NL80211_IFTYPE_MONITOR);
	priv->contexts[IWL_RXON_CTX_BSS].पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_STATION);
	priv->contexts[IWL_RXON_CTX_BSS].ap_devtype = RXON_DEV_TYPE_AP;
	priv->contexts[IWL_RXON_CTX_BSS].ibss_devtype = RXON_DEV_TYPE_IBSS;
	priv->contexts[IWL_RXON_CTX_BSS].station_devtype = RXON_DEV_TYPE_ESS;
	priv->contexts[IWL_RXON_CTX_BSS].unused_devtype = RXON_DEV_TYPE_ESS;
	स_नकल(priv->contexts[IWL_RXON_CTX_BSS].ac_to_queue,
	       iwlagn_bss_ac_to_queue, माप(iwlagn_bss_ac_to_queue));
	स_नकल(priv->contexts[IWL_RXON_CTX_BSS].ac_to_fअगरo,
	       iwlagn_bss_ac_to_fअगरo, माप(iwlagn_bss_ac_to_fअगरo));

	priv->contexts[IWL_RXON_CTX_PAN].rxon_cmd = REPLY_WIPAN_RXON;
	priv->contexts[IWL_RXON_CTX_PAN].rxon_timing_cmd =
		REPLY_WIPAN_RXON_TIMING;
	priv->contexts[IWL_RXON_CTX_PAN].rxon_assoc_cmd =
		REPLY_WIPAN_RXON_ASSOC;
	priv->contexts[IWL_RXON_CTX_PAN].qos_cmd = REPLY_WIPAN_QOS_PARAM;
	priv->contexts[IWL_RXON_CTX_PAN].ap_sta_id = IWL_AP_ID_PAN;
	priv->contexts[IWL_RXON_CTX_PAN].wep_key_cmd = REPLY_WIPAN_WEPKEY;
	priv->contexts[IWL_RXON_CTX_PAN].bcast_sta_id = IWLAGN_PAN_BCAST_ID;
	priv->contexts[IWL_RXON_CTX_PAN].station_flags = STA_FLG_PAN_STATION;
	priv->contexts[IWL_RXON_CTX_PAN].पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_STATION) | BIT(NL80211_IFTYPE_AP);

	priv->contexts[IWL_RXON_CTX_PAN].ap_devtype = RXON_DEV_TYPE_CP;
	priv->contexts[IWL_RXON_CTX_PAN].station_devtype = RXON_DEV_TYPE_2STA;
	priv->contexts[IWL_RXON_CTX_PAN].unused_devtype = RXON_DEV_TYPE_P2P;
	स_नकल(priv->contexts[IWL_RXON_CTX_PAN].ac_to_queue,
	       iwlagn_pan_ac_to_queue, माप(iwlagn_pan_ac_to_queue));
	स_नकल(priv->contexts[IWL_RXON_CTX_PAN].ac_to_fअगरo,
	       iwlagn_pan_ac_to_fअगरo, माप(iwlagn_pan_ac_to_fअगरo));
	priv->contexts[IWL_RXON_CTX_PAN].mcast_queue = IWL_IPAN_MCAST_QUEUE;

	BUILD_BUG_ON(NUM_IWL_RXON_CTX != 2);
पूर्ण

अटल व्योम iwl_rf_समाप्त_ct_config(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_ct_समाप्त_config cmd;
	काष्ठा iwl_ct_समाप्त_throttling_config adv_cmd;
	पूर्णांक ret = 0;

	iwl_ग_लिखो32(priv->trans, CSR_UCODE_DRV_GP1_CLR,
		    CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);

	priv->thermal_throttle.ct_समाप्त_toggle = false;

	अगर (priv->lib->support_ct_समाप्त_निकास) अणु
		adv_cmd.critical_temperature_enter =
			cpu_to_le32(priv->hw_params.ct_समाप्त_threshold);
		adv_cmd.critical_temperature_निकास =
			cpu_to_le32(priv->hw_params.ct_समाप्त_निकास_threshold);

		ret = iwl_dvm_send_cmd_pdu(priv,
				       REPLY_CT_KILL_CONFIG_CMD,
				       0, माप(adv_cmd), &adv_cmd);
		अगर (ret)
			IWL_ERR(priv, "REPLY_CT_KILL_CONFIG_CMD failed\n");
		अन्यथा
			IWL_DEBUG_INFO(priv, "REPLY_CT_KILL_CONFIG_CMD "
				"succeeded, critical temperature enter is %d,"
				"exit is %d\n",
				priv->hw_params.ct_समाप्त_threshold,
				priv->hw_params.ct_समाप्त_निकास_threshold);
	पूर्ण अन्यथा अणु
		cmd.critical_temperature_R =
			cpu_to_le32(priv->hw_params.ct_समाप्त_threshold);

		ret = iwl_dvm_send_cmd_pdu(priv,
				       REPLY_CT_KILL_CONFIG_CMD,
				       0, माप(cmd), &cmd);
		अगर (ret)
			IWL_ERR(priv, "REPLY_CT_KILL_CONFIG_CMD failed\n");
		अन्यथा
			IWL_DEBUG_INFO(priv, "REPLY_CT_KILL_CONFIG_CMD "
				"succeeded, "
				"critical temperature is %d\n",
				priv->hw_params.ct_समाप्त_threshold);
	पूर्ण
पूर्ण

अटल पूर्णांक iwlagn_send_calib_cfg_rt(काष्ठा iwl_priv *priv, u32 cfg)
अणु
	काष्ठा iwl_calib_cfg_cmd calib_cfg_cmd;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = CALIBRATION_CFG_CMD,
		.len = अणु माप(काष्ठा iwl_calib_cfg_cmd), पूर्ण,
		.data = अणु &calib_cfg_cmd, पूर्ण,
	पूर्ण;

	स_रखो(&calib_cfg_cmd, 0, माप(calib_cfg_cmd));
	calib_cfg_cmd.ucd_calib_cfg.once.is_enable = IWL_CALIB_RT_CFG_ALL;
	calib_cfg_cmd.ucd_calib_cfg.once.start = cpu_to_le32(cfg);

	वापस iwl_dvm_send_cmd(priv, &cmd);
पूर्ण


अटल पूर्णांक iwlagn_send_tx_ant_config(काष्ठा iwl_priv *priv, u8 valid_tx_ant)
अणु
	काष्ठा iwl_tx_ant_config_cmd tx_ant_cmd = अणु
	  .valid = cpu_to_le32(valid_tx_ant),
	पूर्ण;

	अगर (IWL_UCODE_API(priv->fw->ucode_ver) > 1) अणु
		IWL_DEBUG_HC(priv, "select valid tx ant: %u\n", valid_tx_ant);
		वापस iwl_dvm_send_cmd_pdu(priv, TX_ANT_CONFIGURATION_CMD, 0,
					माप(काष्ठा iwl_tx_ant_config_cmd),
					&tx_ant_cmd);
	पूर्ण अन्यथा अणु
		IWL_DEBUG_HC(priv, "TX_ANT_CONFIGURATION_CMD not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम iwl_send_bt_config(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_bt_cmd bt_cmd = अणु
		.lead_समय = BT_LEAD_TIME_DEF,
		.max_समाप्त = BT_MAX_KILL_DEF,
		.समाप्त_ack_mask = 0,
		.समाप्त_cts_mask = 0,
	पूर्ण;

	अगर (!iwlwअगरi_mod_params.bt_coex_active)
		bt_cmd.flags = BT_COEX_DISABLE;
	अन्यथा
		bt_cmd.flags = BT_COEX_ENABLE;

	priv->bt_enable_flag = bt_cmd.flags;
	IWL_DEBUG_INFO(priv, "BT coex %s\n",
		(bt_cmd.flags == BT_COEX_DISABLE) ? "disable" : "active");

	अगर (iwl_dvm_send_cmd_pdu(priv, REPLY_BT_CONFIG,
			     0, माप(काष्ठा iwl_bt_cmd), &bt_cmd))
		IWL_ERR(priv, "failed to send BT Coex Config\n");
पूर्ण

/*
 * iwl_alive_start - called after REPLY_ALIVE notअगरication received
 *                   from protocol/runसमय uCode (initialization uCode's
 *                   Alive माला_लो handled by iwl_init_alive_start()).
 */
पूर्णांक iwl_alive_start(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक ret = 0;
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];

	IWL_DEBUG_INFO(priv, "Runtime Alive received.\n");

	/* After the ALIVE response, we can send host commands to the uCode */
	set_bit(STATUS_ALIVE, &priv->status);

	अगर (iwl_is_rfसमाप्त(priv))
		वापस -ERFKILL;

	अगर (priv->event_log.ucode_trace) अणु
		/* start collecting data now */
		mod_समयr(&priv->ucode_trace, jअगरfies);
	पूर्ण

	/* करोwnload priority table beक्रमe any calibration request */
	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) अणु
		/* Configure Bluetooth device coexistence support */
		अगर (priv->lib->bt_params->bt_sco_disable)
			priv->bt_enable_pspoll = false;
		अन्यथा
			priv->bt_enable_pspoll = true;

		priv->bt_valid = IWLAGN_BT_ALL_VALID_MSK;
		priv->समाप्त_ack_mask = IWLAGN_BT_KILL_ACK_MASK_DEFAULT;
		priv->समाप्त_cts_mask = IWLAGN_BT_KILL_CTS_MASK_DEFAULT;
		iwlagn_send_advance_bt_config(priv);
		priv->bt_valid = IWLAGN_BT_VALID_ENABLE_FLAGS;
		priv->cur_rssi_ctx = शून्य;

		iwl_send_prio_tbl(priv);

		/* FIXME: w/a to क्रमce change uCode BT state machine */
		ret = iwl_send_bt_env(priv, IWL_BT_COEX_ENV_OPEN,
					 BT_COEX_PRIO_TBL_EVT_INIT_CALIB2);
		अगर (ret)
			वापस ret;
		ret = iwl_send_bt_env(priv, IWL_BT_COEX_ENV_CLOSE,
					 BT_COEX_PRIO_TBL_EVT_INIT_CALIB2);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (priv->lib->bt_params) अणु
		/*
		 * शेष is 2-wire BT coexexistence support
		 */
		iwl_send_bt_config(priv);
	पूर्ण

	/*
	 * Perक्रमm runसमय calibrations, including DC calibration.
	 */
	iwlagn_send_calib_cfg_rt(priv, IWL_CALIB_CFG_DC_IDX);

	ieee80211_wake_queues(priv->hw);

	/* Configure Tx antenna selection based on H/W config */
	iwlagn_send_tx_ant_config(priv, priv->nvm_data->valid_tx_ant);

	अगर (iwl_is_associated_ctx(ctx) && !priv->wowlan) अणु
		काष्ठा iwl_rxon_cmd *active_rxon =
				(काष्ठा iwl_rxon_cmd *)&ctx->active;
		/* apply any changes in staging */
		ctx->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		active_rxon->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	पूर्ण अन्यथा अणु
		काष्ठा iwl_rxon_context *पंचांगp;
		/* Initialize our rx_config data */
		क्रम_each_context(priv, पंचांगp)
			iwl_connection_init_rx_config(priv, पंचांगp);

		iwlagn_set_rxon_chain(priv, ctx);
	पूर्ण

	अगर (!priv->wowlan) अणु
		/* WoWLAN ucode will not reply in the same way, skip it */
		iwl_reset_run_समय_calib(priv);
	पूर्ण

	set_bit(STATUS_READY, &priv->status);

	/* Configure the adapter क्रम unassociated operation */
	ret = iwlagn_commit_rxon(priv, ctx);
	अगर (ret)
		वापस ret;

	/* At this poपूर्णांक, the NIC is initialized and operational */
	iwl_rf_समाप्त_ct_config(priv);

	IWL_DEBUG_INFO(priv, "ALIVE processing complete.\n");

	वापस iwl_घातer_update_mode(priv, true);
पूर्ण

/**
 * iwl_clear_driver_stations - clear knowledge of all stations from driver
 * @priv: iwl priv काष्ठा
 *
 * This is called during iwl_करोwn() to make sure that in the हाल
 * we're coming there from a hardware restart mac80211 will be
 * able to reconfigure stations -- अगर we're getting there in the
 * normal करोwn flow then the stations will alपढ़ोy be cleared.
 */
अटल व्योम iwl_clear_driver_stations(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_rxon_context *ctx;

	spin_lock_bh(&priv->sta_lock);
	स_रखो(priv->stations, 0, माप(priv->stations));
	priv->num_stations = 0;

	priv->ucode_key_table = 0;

	क्रम_each_context(priv, ctx) अणु
		/*
		 * Remove all key inक्रमmation that is not stored as part
		 * of station inक्रमmation since mac80211 may not have had
		 * a chance to हटाओ all the keys. When device is
		 * reconfigured by mac80211 after an error all keys will
		 * be reconfigured.
		 */
		स_रखो(ctx->wep_keys, 0, माप(ctx->wep_keys));
		ctx->key_mapping_keys = 0;
	पूर्ण

	spin_unlock_bh(&priv->sta_lock);
पूर्ण

व्योम iwl_करोwn(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक निकास_pending;

	IWL_DEBUG_INFO(priv, DRV_NAME " is going down\n");

	lockdep_निश्चित_held(&priv->mutex);

	iwl_scan_cancel_समयout(priv, 200);

	निकास_pending =
		test_and_set_bit(STATUS_EXIT_PENDING, &priv->status);

	iwl_clear_ucode_stations(priv, शून्य);
	iwl_dealloc_bcast_stations(priv);
	iwl_clear_driver_stations(priv);

	/* reset BT coex data */
	priv->bt_status = 0;
	priv->cur_rssi_ctx = शून्य;
	priv->bt_is_sco = 0;
	अगर (priv->lib->bt_params)
		priv->bt_traffic_load =
			 priv->lib->bt_params->bt_init_traffic_load;
	अन्यथा
		priv->bt_traffic_load = 0;
	priv->bt_full_concurrent = false;
	priv->bt_ci_compliance = 0;

	/* Wipe out the EXIT_PENDING status bit अगर we are not actually
	 * निकासing the module */
	अगर (!निकास_pending)
		clear_bit(STATUS_EXIT_PENDING, &priv->status);

	अगर (priv->mac80211_रेजिस्टरed)
		ieee80211_stop_queues(priv->hw);

	priv->ucode_loaded = false;
	iwl_trans_stop_device(priv->trans);

	/* Set num_aux_in_flight must be करोne after the transport is stopped */
	atomic_set(&priv->num_aux_in_flight, 0);

	/* Clear out all status bits but a few that are stable across reset */
	priv->status &= test_bit(STATUS_RF_KILL_HW, &priv->status) <<
				STATUS_RF_KILL_HW |
			test_bit(STATUS_FW_ERROR, &priv->status) <<
				STATUS_FW_ERROR |
			test_bit(STATUS_EXIT_PENDING, &priv->status) <<
				STATUS_EXIT_PENDING;

	dev_kमुक्त_skb(priv->beacon_skb);
	priv->beacon_skb = शून्य;
पूर्ण

/*****************************************************************************
 *
 * Workqueue callbacks
 *
 *****************************************************************************/

अटल व्योम iwl_bg_run_समय_calib_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_priv *priv = container_of(work, काष्ठा iwl_priv,
			run_समय_calib_work);

	mutex_lock(&priv->mutex);

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status) ||
	    test_bit(STATUS_SCANNING, &priv->status)) अणु
		mutex_unlock(&priv->mutex);
		वापस;
	पूर्ण

	अगर (priv->start_calib) अणु
		iwl_chain_noise_calibration(priv);
		iwl_sensitivity_calibration(priv);
	पूर्ण

	mutex_unlock(&priv->mutex);
पूर्ण

व्योम iwlagn_prepare_restart(काष्ठा iwl_priv *priv)
अणु
	bool bt_full_concurrent;
	u8 bt_ci_compliance;
	u8 bt_load;
	u8 bt_status;
	bool bt_is_sco;
	पूर्णांक i;

	lockdep_निश्चित_held(&priv->mutex);

	priv->is_खोलो = 0;

	/*
	 * __iwl_करोwn() will clear the BT status variables,
	 * which is correct, but when we restart we really
	 * want to keep them so restore them afterwards.
	 *
	 * The restart process will later pick them up and
	 * re-configure the hw when we reconfigure the BT
	 * command.
	 */
	bt_full_concurrent = priv->bt_full_concurrent;
	bt_ci_compliance = priv->bt_ci_compliance;
	bt_load = priv->bt_traffic_load;
	bt_status = priv->bt_status;
	bt_is_sco = priv->bt_is_sco;

	iwl_करोwn(priv);

	priv->bt_full_concurrent = bt_full_concurrent;
	priv->bt_ci_compliance = bt_ci_compliance;
	priv->bt_traffic_load = bt_load;
	priv->bt_status = bt_status;
	priv->bt_is_sco = bt_is_sco;

	/* reset aggregation queues */
	क्रम (i = IWLAGN_FIRST_AMPDU_QUEUE; i < IWL_MAX_HW_QUEUES; i++)
		priv->queue_to_mac80211[i] = IWL_INVALID_MAC80211_QUEUE;
	/* and stop counts */
	क्रम (i = 0; i < IWL_MAX_HW_QUEUES; i++)
		atomic_set(&priv->queue_stop_count[i], 0);

	स_रखो(priv->agg_q_alloc, 0, माप(priv->agg_q_alloc));
पूर्ण

अटल व्योम iwl_bg_restart(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा iwl_priv *priv = container_of(data, काष्ठा iwl_priv, restart);

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	अगर (test_and_clear_bit(STATUS_FW_ERROR, &priv->status)) अणु
		mutex_lock(&priv->mutex);
		iwlagn_prepare_restart(priv);
		mutex_unlock(&priv->mutex);
		iwl_cancel_deferred_work(priv);
		अगर (priv->mac80211_रेजिस्टरed)
			ieee80211_restart_hw(priv->hw);
		अन्यथा
			IWL_ERR(priv,
				"Cannot request restart before registering with mac80211\n");
	पूर्ण अन्यथा अणु
		WARN_ON(1);
	पूर्ण
पूर्ण

/*****************************************************************************
 *
 * driver setup and tearकरोwn
 *
 *****************************************************************************/

अटल व्योम iwl_setup_deferred_work(काष्ठा iwl_priv *priv)
अणु
	priv->workqueue = alloc_ordered_workqueue(DRV_NAME, 0);

	INIT_WORK(&priv->restart, iwl_bg_restart);
	INIT_WORK(&priv->beacon_update, iwl_bg_beacon_update);
	INIT_WORK(&priv->run_समय_calib_work, iwl_bg_run_समय_calib_work);
	INIT_WORK(&priv->tx_flush, iwl_bg_tx_flush);
	INIT_WORK(&priv->bt_full_concurrency, iwl_bg_bt_full_concurrency);
	INIT_WORK(&priv->bt_runसमय_config, iwl_bg_bt_runसमय_config);

	iwl_setup_scan_deferred_work(priv);

	अगर (priv->lib->bt_params)
		iwlagn_bt_setup_deferred_work(priv);

	समयr_setup(&priv->statistics_periodic, iwl_bg_statistics_periodic, 0);

	समयr_setup(&priv->ucode_trace, iwl_bg_ucode_trace, 0);
पूर्ण

व्योम iwl_cancel_deferred_work(काष्ठा iwl_priv *priv)
अणु
	अगर (priv->lib->bt_params)
		iwlagn_bt_cancel_deferred_work(priv);

	cancel_work_sync(&priv->run_समय_calib_work);
	cancel_work_sync(&priv->beacon_update);

	iwl_cancel_scan_deferred_work(priv);

	cancel_work_sync(&priv->bt_full_concurrency);
	cancel_work_sync(&priv->bt_runसमय_config);

	del_समयr_sync(&priv->statistics_periodic);
	del_समयr_sync(&priv->ucode_trace);
पूर्ण

अटल पूर्णांक iwl_init_drv(काष्ठा iwl_priv *priv)
अणु
	spin_lock_init(&priv->sta_lock);

	mutex_init(&priv->mutex);

	INIT_LIST_HEAD(&priv->calib_results);

	priv->band = NL80211_BAND_2GHZ;

	priv->plcp_delta_threshold = priv->lib->plcp_delta_threshold;

	priv->iw_mode = NL80211_IFTYPE_STATION;
	priv->current_ht_config.smps = IEEE80211_SMPS_STATIC;
	priv->missed_beacon_threshold = IWL_MISSED_BEACON_THRESHOLD_DEF;
	priv->agg_tids_count = 0;

	priv->rx_statistics_jअगरfies = jअगरfies;

	/* Choose which receivers/antennas to use */
	iwlagn_set_rxon_chain(priv, &priv->contexts[IWL_RXON_CTX_BSS]);

	iwl_init_scan_params(priv);

	/* init bt coex */
	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) अणु
		priv->समाप्त_ack_mask = IWLAGN_BT_KILL_ACK_MASK_DEFAULT;
		priv->समाप्त_cts_mask = IWLAGN_BT_KILL_CTS_MASK_DEFAULT;
		priv->bt_valid = IWLAGN_BT_ALL_VALID_MSK;
		priv->bt_on_thresh = BT_ON_THRESHOLD_DEF;
		priv->bt_duration = BT_DURATION_LIMIT_DEF;
		priv->dynamic_frag_thresh = BT_FRAG_THRESHOLD_DEF;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_uninit_drv(काष्ठा iwl_priv *priv)
अणु
	kमुक्त(priv->scan_cmd);
	kमुक्त(priv->beacon_cmd);
	kमुक्त(rcu_dereference_raw(priv->noa_data));
	iwl_calib_मुक्त_results(priv);
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	kमुक्त(priv->wowlan_sram);
#पूर्ण_अगर
पूर्ण

अटल व्योम iwl_set_hw_params(काष्ठा iwl_priv *priv)
अणु
	अगर (priv->cfg->ht_params)
		priv->hw_params.use_rts_क्रम_aggregation =
			priv->cfg->ht_params->use_rts_क्रम_aggregation;

	/* Device-specअगरic setup */
	priv->lib->set_hw_params(priv);
पूर्ण



/* show what optional capabilities we have */
अटल व्योम iwl_option_config(काष्ठा iwl_priv *priv)
अणु
#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	IWL_INFO(priv, "CONFIG_IWLWIFI_DEBUG enabled\n");
#अन्यथा
	IWL_INFO(priv, "CONFIG_IWLWIFI_DEBUG disabled\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	IWL_INFO(priv, "CONFIG_IWLWIFI_DEBUGFS enabled\n");
#अन्यथा
	IWL_INFO(priv, "CONFIG_IWLWIFI_DEBUGFS disabled\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_IWLWIFI_DEVICE_TRACING
	IWL_INFO(priv, "CONFIG_IWLWIFI_DEVICE_TRACING enabled\n");
#अन्यथा
	IWL_INFO(priv, "CONFIG_IWLWIFI_DEVICE_TRACING disabled\n");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक iwl_eeprom_init_hw_params(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_nvm_data *data = priv->nvm_data;

	अगर (data->sku_cap_11n_enable &&
	    !priv->cfg->ht_params) अणु
		IWL_ERR(priv, "Invalid 11n configuration\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!data->sku_cap_11n_enable && !data->sku_cap_band_24ghz_enable &&
	    !data->sku_cap_band_52ghz_enable) अणु
		IWL_ERR(priv, "Invalid device sku\n");
		वापस -EINVAL;
	पूर्ण

	IWL_DEBUG_INFO(priv,
		       "Device SKU: 24GHz %s %s, 52GHz %s %s, 11.n %s %s\n",
		       data->sku_cap_band_24ghz_enable ? "" : "NOT", "enabled",
		       data->sku_cap_band_52ghz_enable ? "" : "NOT", "enabled",
		       data->sku_cap_11n_enable ? "" : "NOT", "enabled");

	priv->hw_params.tx_chains_num =
		num_of_ant(data->valid_tx_ant);
	अगर (priv->cfg->rx_with_siso_भागersity)
		priv->hw_params.rx_chains_num = 1;
	अन्यथा
		priv->hw_params.rx_chains_num =
			num_of_ant(data->valid_rx_ant);

	IWL_DEBUG_INFO(priv, "Valid Tx ant: 0x%X, Valid Rx ant: 0x%X\n",
		       data->valid_tx_ant,
		       data->valid_rx_ant);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_nvm_check_version(काष्ठा iwl_nvm_data *data,
				 काष्ठा iwl_trans *trans)
अणु
	अगर (data->nvm_version >= trans->cfg->nvm_ver ||
	    data->calib_version >= trans->cfg->nvm_calib_ver) अणु
		IWL_DEBUG_INFO(trans, "device EEPROM VER=0x%x, CALIB=0x%x\n",
			       data->nvm_version, data->calib_version);
		वापस 0;
	पूर्ण

	IWL_ERR(trans,
		"Unsupported (too old) EEPROM VER=0x%x < 0x%x CALIB=0x%x < 0x%x\n",
		data->nvm_version, trans->cfg->nvm_ver,
		data->calib_version,  trans->cfg->nvm_calib_ver);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा iwl_op_mode *iwl_op_mode_dvm_start(काष्ठा iwl_trans *trans,
						 स्थिर काष्ठा iwl_cfg *cfg,
						 स्थिर काष्ठा iwl_fw *fw,
						 काष्ठा dentry *dbgfs_dir)
अणु
	काष्ठा iwl_priv *priv;
	काष्ठा ieee80211_hw *hw;
	काष्ठा iwl_op_mode *op_mode;
	u16 num_mac;
	u32 ucode_flags;
	काष्ठा iwl_trans_config trans_cfg = अणुपूर्ण;
	अटल स्थिर u8 no_reclaim_cmds[] = अणु
		REPLY_RX_PHY_CMD,
		REPLY_RX_MPDU_CMD,
		REPLY_COMPRESSED_BA,
		STATISTICS_NOTIFICATION,
		REPLY_TX,
	पूर्ण;
	पूर्णांक i;

	/************************
	 * 1. Allocating HW data
	 ************************/
	hw = iwl_alloc_all();
	अगर (!hw) अणु
		pr_err("%s: Cannot allocate network device\n", trans->name);
		जाओ out;
	पूर्ण

	op_mode = hw->priv;
	op_mode->ops = &iwl_dvm_ops;
	priv = IWL_OP_MODE_GET_DVM(op_mode);
	priv->trans = trans;
	priv->dev = trans->dev;
	priv->cfg = cfg;
	priv->fw = fw;

	चयन (priv->trans->trans_cfg->device_family) अणु
	हाल IWL_DEVICE_FAMILY_1000:
	हाल IWL_DEVICE_FAMILY_100:
		priv->lib = &iwl_dvm_1000_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_2000:
		priv->lib = &iwl_dvm_2000_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_105:
		priv->lib = &iwl_dvm_105_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_2030:
	हाल IWL_DEVICE_FAMILY_135:
		priv->lib = &iwl_dvm_2030_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_5000:
		priv->lib = &iwl_dvm_5000_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_5150:
		priv->lib = &iwl_dvm_5150_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_6000:
	हाल IWL_DEVICE_FAMILY_6000i:
		priv->lib = &iwl_dvm_6000_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_6005:
		priv->lib = &iwl_dvm_6005_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_6050:
	हाल IWL_DEVICE_FAMILY_6150:
		priv->lib = &iwl_dvm_6050_cfg;
		अवरोध;
	हाल IWL_DEVICE_FAMILY_6030:
		priv->lib = &iwl_dvm_6030_cfg;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (WARN_ON(!priv->lib))
		जाओ out_मुक्त_hw;

	/*
	 * Populate the state variables that the transport layer needs
	 * to know about.
	 */
	trans_cfg.op_mode = op_mode;
	trans_cfg.no_reclaim_cmds = no_reclaim_cmds;
	trans_cfg.n_no_reclaim_cmds = ARRAY_SIZE(no_reclaim_cmds);

	चयन (iwlwअगरi_mod_params.amsdu_size) अणु
	हाल IWL_AMSDU_DEF:
	हाल IWL_AMSDU_4K:
		trans_cfg.rx_buf_size = IWL_AMSDU_4K;
		अवरोध;
	हाल IWL_AMSDU_8K:
		trans_cfg.rx_buf_size = IWL_AMSDU_8K;
		अवरोध;
	हाल IWL_AMSDU_12K:
	शेष:
		trans_cfg.rx_buf_size = IWL_AMSDU_4K;
		pr_err("Unsupported amsdu_size: %d\n",
		       iwlwअगरi_mod_params.amsdu_size);
	पूर्ण

	trans_cfg.cmd_q_wdg_समयout = IWL_WATCHDOG_DISABLED;

	trans_cfg.command_groups = iwl_dvm_groups;
	trans_cfg.command_groups_size = ARRAY_SIZE(iwl_dvm_groups);

	trans_cfg.cmd_fअगरo = IWLAGN_CMD_FIFO_NUM;
	trans_cfg.cb_data_offs = दुरत्व(काष्ठा ieee80211_tx_info,
					  driver_data[2]);

	WARN_ON(माप(priv->transport_queue_stop) * BITS_PER_BYTE <
		priv->trans->trans_cfg->base_params->num_of_queues);

	ucode_flags = fw->ucode_capa.flags;

	अगर (ucode_flags & IWL_UCODE_TLV_FLAGS_PAN) अणु
		priv->sta_key_max_num = STA_KEY_MAX_NUM_PAN;
		trans_cfg.cmd_queue = IWL_IPAN_CMD_QUEUE_NUM;
	पूर्ण अन्यथा अणु
		priv->sta_key_max_num = STA_KEY_MAX_NUM;
		trans_cfg.cmd_queue = IWL_DEFAULT_CMD_QUEUE_NUM;
	पूर्ण

	/* Configure transport layer */
	iwl_trans_configure(priv->trans, &trans_cfg);

	trans->rx_mpdu_cmd = REPLY_RX_MPDU_CMD;
	trans->rx_mpdu_cmd_hdr_size = माप(काष्ठा iwl_rx_mpdu_res_start);
	trans->command_groups = trans_cfg.command_groups;
	trans->command_groups_size = trans_cfg.command_groups_size;

	/* At this poपूर्णांक both hw and priv are allocated. */

	SET_IEEE80211_DEV(priv->hw, priv->trans->dev);

	iwl_option_config(priv);

	IWL_DEBUG_INFO(priv, "*** LOAD DRIVER ***\n");

	/* bt channel inhibition enabled*/
	priv->bt_ch_announce = true;
	IWL_DEBUG_INFO(priv, "BT channel inhibition is %s\n",
		       (priv->bt_ch_announce) ? "On" : "Off");

	/* these spin locks will be used in apm_ops.init and EEPROM access
	 * we should init now
	 */
	spin_lock_init(&priv->statistics.lock);

	/***********************
	 * 2. Read REV रेजिस्टर
	 ***********************/
	IWL_INFO(priv, "Detected %s, REV=0x%X\n",
		priv->trans->name, priv->trans->hw_rev);

	अगर (iwl_trans_start_hw(priv->trans))
		जाओ out_मुक्त_hw;

	/* Read the EEPROM */
	अगर (iwl_पढ़ो_eeprom(priv->trans, &priv->eeprom_blob,
			    &priv->eeprom_blob_size)) अणु
		IWL_ERR(priv, "Unable to init EEPROM\n");
		जाओ out_मुक्त_hw;
	पूर्ण

	/* Reset chip to save घातer until we load uCode during "up". */
	iwl_trans_stop_device(priv->trans);

	priv->nvm_data = iwl_parse_eeprom_data(priv->trans, priv->cfg,
					       priv->eeprom_blob,
					       priv->eeprom_blob_size);
	अगर (!priv->nvm_data)
		जाओ out_मुक्त_eeprom_blob;

	अगर (iwl_nvm_check_version(priv->nvm_data, priv->trans))
		जाओ out_मुक्त_eeprom;

	अगर (iwl_eeprom_init_hw_params(priv))
		जाओ out_मुक्त_eeprom;

	/* extract MAC Address */
	स_नकल(priv->addresses[0].addr, priv->nvm_data->hw_addr, ETH_ALEN);
	IWL_DEBUG_INFO(priv, "MAC address: %pM\n", priv->addresses[0].addr);
	priv->hw->wiphy->addresses = priv->addresses;
	priv->hw->wiphy->n_addresses = 1;
	num_mac = priv->nvm_data->n_hw_addrs;
	अगर (num_mac > 1) अणु
		स_नकल(priv->addresses[1].addr, priv->addresses[0].addr,
		       ETH_ALEN);
		priv->addresses[1].addr[5]++;
		priv->hw->wiphy->n_addresses++;
	पूर्ण

	/************************
	 * 4. Setup HW स्थिरants
	 ************************/
	iwl_set_hw_params(priv);

	अगर (!(priv->nvm_data->sku_cap_ipan_enable)) अणु
		IWL_DEBUG_INFO(priv, "Your EEPROM disabled PAN\n");
		ucode_flags &= ~IWL_UCODE_TLV_FLAGS_PAN;
		/*
		 * अगर not PAN, then करोn't support P2P -- might be a uCode
		 * packaging bug or due to the eeprom check above
		 */
		priv->sta_key_max_num = STA_KEY_MAX_NUM;
		trans_cfg.cmd_queue = IWL_DEFAULT_CMD_QUEUE_NUM;

		/* Configure transport layer again*/
		iwl_trans_configure(priv->trans, &trans_cfg);
	पूर्ण

	/*******************
	 * 5. Setup priv
	 *******************/
	क्रम (i = 0; i < IWL_MAX_HW_QUEUES; i++) अणु
		priv->queue_to_mac80211[i] = IWL_INVALID_MAC80211_QUEUE;
		अगर (i < IWLAGN_FIRST_AMPDU_QUEUE &&
		    i != IWL_DEFAULT_CMD_QUEUE_NUM &&
		    i != IWL_IPAN_CMD_QUEUE_NUM)
			priv->queue_to_mac80211[i] = i;
		atomic_set(&priv->queue_stop_count[i], 0);
	पूर्ण

	अगर (iwl_init_drv(priv))
		जाओ out_मुक्त_eeprom;

	/* At this poपूर्णांक both hw and priv are initialized. */

	/********************
	 * 6. Setup services
	 ********************/
	iwl_setup_deferred_work(priv);
	iwl_setup_rx_handlers(priv);

	iwl_घातer_initialize(priv);
	iwl_tt_initialize(priv);

	snम_लिखो(priv->hw->wiphy->fw_version,
		 माप(priv->hw->wiphy->fw_version),
		 "%s", fw->fw_version);

	priv->new_scan_threshold_behaviour =
		!!(ucode_flags & IWL_UCODE_TLV_FLAGS_NEWSCAN);

	priv->phy_calib_chain_noise_reset_cmd =
		fw->ucode_capa.standard_phy_calibration_size;
	priv->phy_calib_chain_noise_gain_cmd =
		fw->ucode_capa.standard_phy_calibration_size + 1;

	/* initialize all valid contexts */
	iwl_init_context(priv, ucode_flags);

	/**************************************************
	 * This is still part of probe() in a sense...
	 *
	 * 7. Setup and रेजिस्टर with mac80211 and debugfs
	 **************************************************/
	अगर (iwlagn_mac_setup_रेजिस्टर(priv, &fw->ucode_capa))
		जाओ out_destroy_workqueue;

	iwl_dbgfs_रेजिस्टर(priv, dbgfs_dir);

	वापस op_mode;

out_destroy_workqueue:
	iwl_tt_निकास(priv);
	iwl_cancel_deferred_work(priv);
	destroy_workqueue(priv->workqueue);
	priv->workqueue = शून्य;
	iwl_uninit_drv(priv);
out_मुक्त_eeprom_blob:
	kमुक्त(priv->eeprom_blob);
out_मुक्त_eeprom:
	kमुक्त(priv->nvm_data);
out_मुक्त_hw:
	ieee80211_मुक्त_hw(priv->hw);
out:
	op_mode = शून्य;
	वापस op_mode;
पूर्ण

अटल व्योम iwl_op_mode_dvm_stop(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	IWL_DEBUG_INFO(priv, "*** UNLOAD DRIVER ***\n");

	iwlagn_mac_unरेजिस्टर(priv);

	iwl_tt_निकास(priv);

	kमुक्त(priv->eeprom_blob);
	kमुक्त(priv->nvm_data);

	/*netअगर_stop_queue(dev); */
	flush_workqueue(priv->workqueue);

	/* ieee80211_unरेजिस्टर_hw calls iwlagn_mac_stop, which flushes
	 * priv->workqueue... so we can't take करोwn the workqueue
	 * until now... */
	destroy_workqueue(priv->workqueue);
	priv->workqueue = शून्य;

	iwl_uninit_drv(priv);

	dev_kमुक्त_skb(priv->beacon_skb);

	iwl_trans_op_mode_leave(priv->trans);
	ieee80211_मुक्त_hw(priv->hw);
पूर्ण

अटल स्थिर अक्षर * स्थिर desc_lookup_text[] = अणु
	"OK",
	"FAIL",
	"BAD_PARAM",
	"BAD_CHECKSUM",
	"NMI_INTERRUPT_WDG",
	"SYSASSERT",
	"FATAL_ERROR",
	"BAD_COMMAND",
	"HW_ERROR_TUNE_LOCK",
	"HW_ERROR_TEMPERATURE",
	"ILLEGAL_CHAN_FREQ",
	"VCC_NOT_STABLE",
	"FH_ERROR",
	"NMI_INTERRUPT_HOST",
	"NMI_INTERRUPT_ACTION_PT",
	"NMI_INTERRUPT_UNKNOWN",
	"UCODE_VERSION_MISMATCH",
	"HW_ERROR_ABS_LOCK",
	"HW_ERROR_CAL_LOCK_FAIL",
	"NMI_INTERRUPT_INST_ACTION_PT",
	"NMI_INTERRUPT_DATA_ACTION_PT",
	"NMI_TRM_HW_ER",
	"NMI_INTERRUPT_TRM",
	"NMI_INTERRUPT_BREAK_POINT",
	"DEBUG_0",
	"DEBUG_1",
	"DEBUG_2",
	"DEBUG_3",
पूर्ण;

अटल काष्ठा अणु अक्षर *name; u8 num; पूर्ण advanced_lookup[] = अणु
	अणु "NMI_INTERRUPT_WDG", 0x34 पूर्ण,
	अणु "SYSASSERT", 0x35 पूर्ण,
	अणु "UCODE_VERSION_MISMATCH", 0x37 पूर्ण,
	अणु "BAD_COMMAND", 0x38 पूर्ण,
	अणु "NMI_INTERRUPT_DATA_ACTION_PT", 0x3C पूर्ण,
	अणु "FATAL_ERROR", 0x3D पूर्ण,
	अणु "NMI_TRM_HW_ERR", 0x46 पूर्ण,
	अणु "NMI_INTERRUPT_TRM", 0x4C पूर्ण,
	अणु "NMI_INTERRUPT_BREAK_POINT", 0x54 पूर्ण,
	अणु "NMI_INTERRUPT_WDG_RXF_FULL", 0x5C पूर्ण,
	अणु "NMI_INTERRUPT_WDG_NO_RBD_RXF_FULL", 0x64 पूर्ण,
	अणु "NMI_INTERRUPT_HOST", 0x66 पूर्ण,
	अणु "NMI_INTERRUPT_ACTION_PT", 0x7C पूर्ण,
	अणु "NMI_INTERRUPT_UNKNOWN", 0x84 पूर्ण,
	अणु "NMI_INTERRUPT_INST_ACTION_PT", 0x86 पूर्ण,
	अणु "ADVANCED_SYSASSERT", 0 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *desc_lookup(u32 num)
अणु
	पूर्णांक i;
	पूर्णांक max = ARRAY_SIZE(desc_lookup_text);

	अगर (num < max)
		वापस desc_lookup_text[num];

	max = ARRAY_SIZE(advanced_lookup) - 1;
	क्रम (i = 0; i < max; i++) अणु
		अगर (advanced_lookup[i].num == num)
			अवरोध;
	पूर्ण
	वापस advanced_lookup[i].name;
पूर्ण

#घोषणा ERROR_START_OFFSET  (1 * माप(u32))
#घोषणा ERROR_ELEM_SIZE     (7 * माप(u32))

अटल व्योम iwl_dump_nic_error_log(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_trans *trans = priv->trans;
	u32 base;
	काष्ठा iwl_error_event_table table;

	base = priv->device_poपूर्णांकers.error_event_table;
	अगर (priv->cur_ucode == IWL_UCODE_INIT) अणु
		अगर (!base)
			base = priv->fw->init_errlog_ptr;
	पूर्ण अन्यथा अणु
		अगर (!base)
			base = priv->fw->inst_errlog_ptr;
	पूर्ण

	अगर (!iwlagn_hw_valid_rtc_data_addr(base)) अणु
		IWL_ERR(priv,
			"Not valid error log pointer 0x%08X for %s uCode\n",
			base,
			(priv->cur_ucode == IWL_UCODE_INIT)
					? "Init" : "RT");
		वापस;
	पूर्ण

	/*TODO: Update dbgfs with ISR error stats obtained below */
	iwl_trans_पढ़ो_mem_bytes(trans, base, &table, माप(table));

	अगर (ERROR_START_OFFSET <= table.valid * ERROR_ELEM_SIZE) अणु
		IWL_ERR(trans, "Start IWL Error Log Dump:\n");
		IWL_ERR(trans, "Status: 0x%08lX, count: %d\n",
			priv->status, table.valid);
	पूर्ण

	IWL_ERR(priv, "0x%08X | %-28s\n", table.error_id,
		desc_lookup(table.error_id));
	IWL_ERR(priv, "0x%08X | uPc\n", table.pc);
	IWL_ERR(priv, "0x%08X | branchlink1\n", table.blink1);
	IWL_ERR(priv, "0x%08X | branchlink2\n", table.blink2);
	IWL_ERR(priv, "0x%08X | interruptlink1\n", table.ilink1);
	IWL_ERR(priv, "0x%08X | interruptlink2\n", table.ilink2);
	IWL_ERR(priv, "0x%08X | data1\n", table.data1);
	IWL_ERR(priv, "0x%08X | data2\n", table.data2);
	IWL_ERR(priv, "0x%08X | line\n", table.line);
	IWL_ERR(priv, "0x%08X | beacon time\n", table.bcon_समय);
	IWL_ERR(priv, "0x%08X | tsf low\n", table.tsf_low);
	IWL_ERR(priv, "0x%08X | tsf hi\n", table.tsf_hi);
	IWL_ERR(priv, "0x%08X | time gp1\n", table.gp1);
	IWL_ERR(priv, "0x%08X | time gp2\n", table.gp2);
	IWL_ERR(priv, "0x%08X | time gp3\n", table.gp3);
	IWL_ERR(priv, "0x%08X | uCode version\n", table.ucode_ver);
	IWL_ERR(priv, "0x%08X | hw version\n", table.hw_ver);
	IWL_ERR(priv, "0x%08X | board version\n", table.brd_ver);
	IWL_ERR(priv, "0x%08X | hcmd\n", table.hcmd);
	IWL_ERR(priv, "0x%08X | isr0\n", table.isr0);
	IWL_ERR(priv, "0x%08X | isr1\n", table.isr1);
	IWL_ERR(priv, "0x%08X | isr2\n", table.isr2);
	IWL_ERR(priv, "0x%08X | isr3\n", table.isr3);
	IWL_ERR(priv, "0x%08X | isr4\n", table.isr4);
	IWL_ERR(priv, "0x%08X | isr_pref\n", table.isr_pref);
	IWL_ERR(priv, "0x%08X | wait_event\n", table.रुको_event);
	IWL_ERR(priv, "0x%08X | l2p_control\n", table.l2p_control);
	IWL_ERR(priv, "0x%08X | l2p_duration\n", table.l2p_duration);
	IWL_ERR(priv, "0x%08X | l2p_mhvalid\n", table.l2p_mhvalid);
	IWL_ERR(priv, "0x%08X | l2p_addr_match\n", table.l2p_addr_match);
	IWL_ERR(priv, "0x%08X | lmpm_pmg_sel\n", table.lmpm_pmg_sel);
	IWL_ERR(priv, "0x%08X | timestamp\n", table.u_बारtamp);
	IWL_ERR(priv, "0x%08X | flow_handler\n", table.flow_handler);
पूर्ण

#घोषणा EVENT_START_OFFSET  (4 * माप(u32))

/*
 * iwl_prपूर्णांक_event_log - Dump error event log to syslog
 */
अटल पूर्णांक iwl_prपूर्णांक_event_log(काष्ठा iwl_priv *priv, u32 start_idx,
			       u32 num_events, u32 mode,
			       पूर्णांक pos, अक्षर **buf, माप_प्रकार bufsz)
अणु
	u32 i;
	u32 base;       /* SRAM byte address of event log header */
	u32 event_size; /* 2 u32s, or 3 u32s अगर बारtamp recorded */
	u32 ptr;        /* SRAM byte address of log data */
	u32 ev, समय, data; /* event log data */

	काष्ठा iwl_trans *trans = priv->trans;

	अगर (num_events == 0)
		वापस pos;

	base = priv->device_poपूर्णांकers.log_event_table;
	अगर (priv->cur_ucode == IWL_UCODE_INIT) अणु
		अगर (!base)
			base = priv->fw->init_evtlog_ptr;
	पूर्ण अन्यथा अणु
		अगर (!base)
			base = priv->fw->inst_evtlog_ptr;
	पूर्ण

	अगर (mode == 0)
		event_size = 2 * माप(u32);
	अन्यथा
		event_size = 3 * माप(u32);

	ptr = base + EVENT_START_OFFSET + (start_idx * event_size);

	/* Make sure device is घातered up क्रम SRAM पढ़ोs */
	अगर (!iwl_trans_grab_nic_access(trans))
		वापस pos;

	/* Set starting address; पढ़ोs will स्वतः-increment */
	iwl_ग_लिखो32(trans, HBUS_TARG_MEM_RADDR, ptr);

	/* "time" is actually "data" क्रम mode 0 (no बारtamp).
	* place event id # at far right क्रम easier visual parsing. */
	क्रम (i = 0; i < num_events; i++) अणु
		ev = iwl_पढ़ो32(trans, HBUS_TARG_MEM_RDAT);
		समय = iwl_पढ़ो32(trans, HBUS_TARG_MEM_RDAT);
		अगर (mode == 0) अणु
			/* data, ev */
			अगर (bufsz) अणु
				pos += scnम_लिखो(*buf + pos, bufsz - pos,
						"EVT_LOG:0x%08x:%04u\n",
						समय, ev);
			पूर्ण अन्यथा अणु
				trace_iwlwअगरi_dev_ucode_event(trans->dev, 0,
					समय, ev);
				IWL_ERR(priv, "EVT_LOG:0x%08x:%04u\n",
					समय, ev);
			पूर्ण
		पूर्ण अन्यथा अणु
			data = iwl_पढ़ो32(trans, HBUS_TARG_MEM_RDAT);
			अगर (bufsz) अणु
				pos += scnम_लिखो(*buf + pos, bufsz - pos,
						"EVT_LOGT:%010u:0x%08x:%04u\n",
						 समय, data, ev);
			पूर्ण अन्यथा अणु
				IWL_ERR(priv, "EVT_LOGT:%010u:0x%08x:%04u\n",
					समय, data, ev);
				trace_iwlwअगरi_dev_ucode_event(trans->dev, समय,
					data, ev);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Allow device to घातer करोwn */
	iwl_trans_release_nic_access(trans);
	वापस pos;
पूर्ण

/*
 * iwl_prपूर्णांक_last_event_logs - Dump the newest # of event log to syslog
 */
अटल पूर्णांक iwl_prपूर्णांक_last_event_logs(काष्ठा iwl_priv *priv, u32 capacity,
				    u32 num_wraps, u32 next_entry,
				    u32 size, u32 mode,
				    पूर्णांक pos, अक्षर **buf, माप_प्रकार bufsz)
अणु
	/*
	 * display the newest DEFAULT_LOG_ENTRIES entries
	 * i.e the entries just beक्रमe the next ont that uCode would fill.
	 */
	अगर (num_wraps) अणु
		अगर (next_entry < size) अणु
			pos = iwl_prपूर्णांक_event_log(priv,
						capacity - (size - next_entry),
						size - next_entry, mode,
						pos, buf, bufsz);
			pos = iwl_prपूर्णांक_event_log(priv, 0,
						  next_entry, mode,
						  pos, buf, bufsz);
		पूर्ण अन्यथा
			pos = iwl_prपूर्णांक_event_log(priv, next_entry - size,
						  size, mode, pos, buf, bufsz);
	पूर्ण अन्यथा अणु
		अगर (next_entry < size) अणु
			pos = iwl_prपूर्णांक_event_log(priv, 0, next_entry,
						  mode, pos, buf, bufsz);
		पूर्ण अन्यथा अणु
			pos = iwl_prपूर्णांक_event_log(priv, next_entry - size,
						  size, mode, pos, buf, bufsz);
		पूर्ण
	पूर्ण
	वापस pos;
पूर्ण

#घोषणा DEFAULT_DUMP_EVENT_LOG_ENTRIES (20)

पूर्णांक iwl_dump_nic_event_log(काष्ठा iwl_priv *priv, bool full_log,
			    अक्षर **buf)
अणु
	u32 base;       /* SRAM byte address of event log header */
	u32 capacity;   /* event log capacity in # entries */
	u32 mode;       /* 0 - no बारtamp, 1 - बारtamp recorded */
	u32 num_wraps;  /* # बार uCode wrapped to top of log */
	u32 next_entry; /* index of next entry to be written by uCode */
	u32 size;       /* # entries that we'll prपूर्णांक */
	u32 logsize;
	पूर्णांक pos = 0;
	माप_प्रकार bufsz = 0;
	काष्ठा iwl_trans *trans = priv->trans;

	base = priv->device_poपूर्णांकers.log_event_table;
	अगर (priv->cur_ucode == IWL_UCODE_INIT) अणु
		logsize = priv->fw->init_evtlog_size;
		अगर (!base)
			base = priv->fw->init_evtlog_ptr;
	पूर्ण अन्यथा अणु
		logsize = priv->fw->inst_evtlog_size;
		अगर (!base)
			base = priv->fw->inst_evtlog_ptr;
	पूर्ण

	अगर (!iwlagn_hw_valid_rtc_data_addr(base)) अणु
		IWL_ERR(priv,
			"Invalid event log pointer 0x%08X for %s uCode\n",
			base,
			(priv->cur_ucode == IWL_UCODE_INIT)
					? "Init" : "RT");
		वापस -EINVAL;
	पूर्ण

	/* event log header */
	capacity = iwl_trans_पढ़ो_mem32(trans, base);
	mode = iwl_trans_पढ़ो_mem32(trans, base + (1 * माप(u32)));
	num_wraps = iwl_trans_पढ़ो_mem32(trans, base + (2 * माप(u32)));
	next_entry = iwl_trans_पढ़ो_mem32(trans, base + (3 * माप(u32)));

	अगर (capacity > logsize) अणु
		IWL_ERR(priv, "Log capacity %d is bogus, limit to %d "
			"entries\n", capacity, logsize);
		capacity = logsize;
	पूर्ण

	अगर (next_entry > logsize) अणु
		IWL_ERR(priv, "Log write index %d is bogus, limit to %d\n",
			next_entry, logsize);
		next_entry = logsize;
	पूर्ण

	size = num_wraps ? capacity : next_entry;

	/* bail out अगर nothing in log */
	अगर (size == 0) अणु
		IWL_ERR(trans, "Start IWL Event Log Dump: nothing in log\n");
		वापस pos;
	पूर्ण

	अगर (!(iwl_have_debug_level(IWL_DL_FW)) && !full_log)
		size = (size > DEFAULT_DUMP_EVENT_LOG_ENTRIES)
			? DEFAULT_DUMP_EVENT_LOG_ENTRIES : size;
	IWL_ERR(priv, "Start IWL Event Log Dump: display last %u entries\n",
		size);

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	अगर (buf) अणु
		अगर (full_log)
			bufsz = capacity * 48;
		अन्यथा
			bufsz = size * 48;
		*buf = kदो_स्मृति(bufsz, GFP_KERNEL);
		अगर (!*buf)
			वापस -ENOMEM;
	पूर्ण
	अगर (iwl_have_debug_level(IWL_DL_FW) || full_log) अणु
		/*
		 * अगर uCode has wrapped back to top of log,
		 * start at the oldest entry,
		 * i.e the next one that uCode would fill.
		 */
		अगर (num_wraps)
			pos = iwl_prपूर्णांक_event_log(priv, next_entry,
						capacity - next_entry, mode,
						pos, buf, bufsz);
		/* (then/अन्यथा) start at top of log */
		pos = iwl_prपूर्णांक_event_log(priv, 0,
					  next_entry, mode, pos, buf, bufsz);
	पूर्ण अन्यथा
		pos = iwl_prपूर्णांक_last_event_logs(priv, capacity, num_wraps,
						next_entry, size, mode,
						pos, buf, bufsz);
#अन्यथा
	pos = iwl_prपूर्णांक_last_event_logs(priv, capacity, num_wraps,
					next_entry, size, mode,
					pos, buf, bufsz);
#पूर्ण_अगर
	वापस pos;
पूर्ण

अटल व्योम iwlagn_fw_error(काष्ठा iwl_priv *priv, bool ondemand)
अणु
	अचिन्हित पूर्णांक reload_msec;
	अचिन्हित दीर्घ reload_jअगरfies;

	अगर (iwl_have_debug_level(IWL_DL_FW))
		iwl_prपूर्णांक_rx_config_cmd(priv, IWL_RXON_CTX_BSS);

	/* uCode is no दीर्घer loaded. */
	priv->ucode_loaded = false;

	/* Set the FW error flag -- cleared on iwl_करोwn */
	set_bit(STATUS_FW_ERROR, &priv->status);

	iwl_पात_notअगरication_रुकोs(&priv->notअगर_रुको);

	/* Keep the restart process from trying to send host
	 * commands by clearing the पढ़ोy bit */
	clear_bit(STATUS_READY, &priv->status);

	अगर (!ondemand) अणु
		/*
		 * If firmware keep reloading, then it indicate something
		 * serious wrong and firmware having problem to recover
		 * from it. Instead of keep trying which will fill the syslog
		 * and hang the प्रणाली, let's just stop it
		 */
		reload_jअगरfies = jअगरfies;
		reload_msec = jअगरfies_to_msecs((दीर्घ) reload_jअगरfies -
					(दीर्घ) priv->reload_jअगरfies);
		priv->reload_jअगरfies = reload_jअगरfies;
		अगर (reload_msec <= IWL_MIN_RELOAD_DURATION) अणु
			priv->reload_count++;
			अगर (priv->reload_count >= IWL_MAX_CONTINUE_RELOAD_CNT) अणु
				IWL_ERR(priv, "BUG_ON, Stop restarting\n");
				वापस;
			पूर्ण
		पूर्ण अन्यथा
			priv->reload_count = 0;
	पूर्ण

	अगर (!test_bit(STATUS_EXIT_PENDING, &priv->status)) अणु
		अगर (iwlwअगरi_mod_params.fw_restart) अणु
			IWL_DEBUG_FW(priv,
				     "Restarting adapter due to uCode error.\n");
			queue_work(priv->workqueue, &priv->restart);
		पूर्ण अन्यथा
			IWL_DEBUG_FW(priv,
				     "Detected FW error, but not restarting\n");
	पूर्ण
पूर्ण

अटल व्योम iwl_nic_error(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	IWL_ERR(priv, "Loaded firmware version: %s\n",
		priv->fw->fw_version);

	iwl_dump_nic_error_log(priv);
	iwl_dump_nic_event_log(priv, false, शून्य);

	iwlagn_fw_error(priv, false);
पूर्ण

अटल व्योम iwl_cmd_queue_full(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	अगर (!iwl_check_क्रम_ct_समाप्त(priv)) अणु
		IWL_ERR(priv, "Restarting adapter queue is full\n");
		iwlagn_fw_error(priv, false);
	पूर्ण
पूर्ण

#घोषणा EEPROM_RF_CONFIG_TYPE_MAX      0x3

अटल व्योम iwl_nic_config(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	/* SKU Control */
	iwl_trans_set_bits_mask(priv->trans, CSR_HW_IF_CONFIG_REG,
				CSR_HW_IF_CONFIG_REG_MSK_MAC_DASH |
				CSR_HW_IF_CONFIG_REG_MSK_MAC_STEP,
				(CSR_HW_REV_STEP(priv->trans->hw_rev) <<
					CSR_HW_IF_CONFIG_REG_POS_MAC_STEP) |
				(CSR_HW_REV_DASH(priv->trans->hw_rev) <<
					CSR_HW_IF_CONFIG_REG_POS_MAC_DASH));

	/* ग_लिखो radio config values to रेजिस्टर */
	अगर (priv->nvm_data->radio_cfg_type <= EEPROM_RF_CONFIG_TYPE_MAX) अणु
		u32 reg_val =
			priv->nvm_data->radio_cfg_type <<
				CSR_HW_IF_CONFIG_REG_POS_PHY_TYPE |
			priv->nvm_data->radio_cfg_step <<
				CSR_HW_IF_CONFIG_REG_POS_PHY_STEP |
			priv->nvm_data->radio_cfg_dash <<
				CSR_HW_IF_CONFIG_REG_POS_PHY_DASH;

		iwl_trans_set_bits_mask(priv->trans, CSR_HW_IF_CONFIG_REG,
					CSR_HW_IF_CONFIG_REG_MSK_PHY_TYPE |
					CSR_HW_IF_CONFIG_REG_MSK_PHY_STEP |
					CSR_HW_IF_CONFIG_REG_MSK_PHY_DASH,
					reg_val);

		IWL_INFO(priv, "Radio type=0x%x-0x%x-0x%x\n",
			 priv->nvm_data->radio_cfg_type,
			 priv->nvm_data->radio_cfg_step,
			 priv->nvm_data->radio_cfg_dash);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
	पूर्ण

	/* set CSR_HW_CONFIG_REG क्रम uCode use */
	iwl_set_bit(priv->trans, CSR_HW_IF_CONFIG_REG,
		    CSR_HW_IF_CONFIG_REG_BIT_RADIO_SI |
		    CSR_HW_IF_CONFIG_REG_BIT_MAC_SI);

	/* W/A : NIC is stuck in a reset state after Early PCIe घातer off
	 * (PCIe घातer is lost beक्रमe PERST# is निश्चितed),
	 * causing ME FW to lose ownership and not being able to obtain it back.
	 */
	iwl_set_bits_mask_prph(priv->trans, APMG_PS_CTRL_REG,
			       APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS,
			       ~APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS);

	अगर (priv->lib->nic_config)
		priv->lib->nic_config(priv);
पूर्ण

अटल व्योम iwl_wimax_active(काष्ठा iwl_op_mode *op_mode)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	clear_bit(STATUS_READY, &priv->status);
	IWL_ERR(priv, "RF is used by WiMAX\n");
पूर्ण

अटल व्योम iwl_stop_sw_queue(काष्ठा iwl_op_mode *op_mode, पूर्णांक queue)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);
	पूर्णांक mq = priv->queue_to_mac80211[queue];

	अगर (WARN_ON_ONCE(mq == IWL_INVALID_MAC80211_QUEUE))
		वापस;

	अगर (atomic_inc_वापस(&priv->queue_stop_count[mq]) > 1) अणु
		IWL_DEBUG_TX_QUEUES(priv,
			"queue %d (mac80211 %d) already stopped\n",
			queue, mq);
		वापस;
	पूर्ण

	set_bit(mq, &priv->transport_queue_stop);
	ieee80211_stop_queue(priv->hw, mq);
पूर्ण

अटल व्योम iwl_wake_sw_queue(काष्ठा iwl_op_mode *op_mode, पूर्णांक queue)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);
	पूर्णांक mq = priv->queue_to_mac80211[queue];

	अगर (WARN_ON_ONCE(mq == IWL_INVALID_MAC80211_QUEUE))
		वापस;

	अगर (atomic_dec_वापस(&priv->queue_stop_count[mq]) > 0) अणु
		IWL_DEBUG_TX_QUEUES(priv,
			"queue %d (mac80211 %d) already awake\n",
			queue, mq);
		वापस;
	पूर्ण

	clear_bit(mq, &priv->transport_queue_stop);

	अगर (!priv->passive_no_rx)
		ieee80211_wake_queue(priv->hw, mq);
पूर्ण

व्योम iwlagn_lअगरt_passive_no_rx(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक mq;

	अगर (!priv->passive_no_rx)
		वापस;

	क्रम (mq = 0; mq < IWLAGN_FIRST_AMPDU_QUEUE; mq++) अणु
		अगर (!test_bit(mq, &priv->transport_queue_stop)) अणु
			IWL_DEBUG_TX_QUEUES(priv, "Wake queue %d\n", mq);
			ieee80211_wake_queue(priv->hw, mq);
		पूर्ण अन्यथा अणु
			IWL_DEBUG_TX_QUEUES(priv, "Don't wake queue %d\n", mq);
		पूर्ण
	पूर्ण

	priv->passive_no_rx = false;
पूर्ण

अटल व्योम iwl_मुक्त_skb(काष्ठा iwl_op_mode *op_mode, काष्ठा sk_buff *skb)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);
	काष्ठा ieee80211_tx_info *info;

	info = IEEE80211_SKB_CB(skb);
	iwl_trans_मुक्त_tx_cmd(priv->trans, info->driver_data[1]);
	ieee80211_मुक्त_txskb(priv->hw, skb);
पूर्ण

अटल bool iwl_set_hw_rfसमाप्त_state(काष्ठा iwl_op_mode *op_mode, bool state)
अणु
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);

	अगर (state)
		set_bit(STATUS_RF_KILL_HW, &priv->status);
	अन्यथा
		clear_bit(STATUS_RF_KILL_HW, &priv->status);

	wiphy_rfसमाप्त_set_hw_state(priv->hw->wiphy, state);

	वापस false;
पूर्ण

अटल स्थिर काष्ठा iwl_op_mode_ops iwl_dvm_ops = अणु
	.start = iwl_op_mode_dvm_start,
	.stop = iwl_op_mode_dvm_stop,
	.rx = iwl_rx_dispatch,
	.queue_full = iwl_stop_sw_queue,
	.queue_not_full = iwl_wake_sw_queue,
	.hw_rf_समाप्त = iwl_set_hw_rfसमाप्त_state,
	.मुक्त_skb = iwl_मुक्त_skb,
	.nic_error = iwl_nic_error,
	.cmd_queue_full = iwl_cmd_queue_full,
	.nic_config = iwl_nic_config,
	.wimax_active = iwl_wimax_active,
पूर्ण;

/*****************************************************************************
 *
 * driver and module entry poपूर्णांक
 *
 *****************************************************************************/
अटल पूर्णांक __init iwl_init(व्योम)
अणु

	पूर्णांक ret;

	ret = iwlagn_rate_control_रेजिस्टर();
	अगर (ret) अणु
		pr_err("Unable to register rate control algorithm: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = iwl_opmode_रेजिस्टर("iwldvm", &iwl_dvm_ops);
	अगर (ret) अणु
		pr_err("Unable to register op_mode: %d\n", ret);
		iwlagn_rate_control_unरेजिस्टर();
	पूर्ण

	वापस ret;
पूर्ण
module_init(iwl_init);

अटल व्योम __निकास iwl_निकास(व्योम)
अणु
	iwl_opmode_deरेजिस्टर("iwldvm");
	iwlagn_rate_control_unरेजिस्टर();
पूर्ण
module_निकास(iwl_निकास);
