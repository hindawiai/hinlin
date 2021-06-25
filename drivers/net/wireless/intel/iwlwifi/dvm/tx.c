<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2014 Intel Corporation. All rights reserved.
 * Copyright (C) 2019 Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/ieee80211.h>
#समावेश "iwl-io.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-agn-hw.h"
#समावेश "dev.h"
#समावेश "agn.h"

अटल स्थिर u8 tid_to_ac[] = अणु
	IEEE80211_AC_BE,
	IEEE80211_AC_BK,
	IEEE80211_AC_BK,
	IEEE80211_AC_BE,
	IEEE80211_AC_VI,
	IEEE80211_AC_VI,
	IEEE80211_AC_VO,
	IEEE80211_AC_VO,
पूर्ण;

अटल व्योम iwlagn_tx_cmd_protection(काष्ठा iwl_priv *priv,
				     काष्ठा ieee80211_tx_info *info,
				     __le16 fc, __le32 *tx_flags)
अणु
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS ||
	    info->control.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT ||
	    info->flags & IEEE80211_TX_CTL_AMPDU)
		*tx_flags |= TX_CMD_FLG_PROT_REQUIRE_MSK;
पूर्ण

/*
 * handle build REPLY_TX command notअगरication.
 */
अटल व्योम iwlagn_tx_cmd_build_basic(काष्ठा iwl_priv *priv,
				      काष्ठा sk_buff *skb,
				      काष्ठा iwl_tx_cmd *tx_cmd,
				      काष्ठा ieee80211_tx_info *info,
				      काष्ठा ieee80211_hdr *hdr, u8 sta_id)
अणु
	__le16 fc = hdr->frame_control;
	__le32 tx_flags = tx_cmd->tx_flags;

	tx_cmd->stop_समय.lअगरe_समय = TX_CMD_LIFE_TIME_INFINITE;

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK))
		tx_flags |= TX_CMD_FLG_ACK_MSK;
	अन्यथा
		tx_flags &= ~TX_CMD_FLG_ACK_MSK;

	अगर (ieee80211_is_probe_resp(fc))
		tx_flags |= TX_CMD_FLG_TSF_MSK;
	अन्यथा अगर (ieee80211_is_back_req(fc))
		tx_flags |= TX_CMD_FLG_ACK_MSK | TX_CMD_FLG_IMM_BA_RSP_MASK;
	अन्यथा अगर (info->band == NL80211_BAND_2GHZ &&
		 priv->lib->bt_params &&
		 priv->lib->bt_params->advanced_bt_coexist &&
		 (ieee80211_is_auth(fc) || ieee80211_is_assoc_req(fc) ||
		 ieee80211_is_reassoc_req(fc) ||
		 info->control.flags & IEEE80211_TX_CTRL_PORT_CTRL_PROTO))
		tx_flags |= TX_CMD_FLG_IGNORE_BT;


	tx_cmd->sta_id = sta_id;
	अगर (ieee80211_has_morefrags(fc))
		tx_flags |= TX_CMD_FLG_MORE_FRAG_MSK;

	अगर (ieee80211_is_data_qos(fc)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		tx_cmd->tid_tspec = qc[0] & 0xf;
		tx_flags &= ~TX_CMD_FLG_SEQ_CTL_MSK;
	पूर्ण अन्यथा अणु
		tx_cmd->tid_tspec = IWL_TID_NON_QOS;
		अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ)
			tx_flags |= TX_CMD_FLG_SEQ_CTL_MSK;
		अन्यथा
			tx_flags &= ~TX_CMD_FLG_SEQ_CTL_MSK;
	पूर्ण

	iwlagn_tx_cmd_protection(priv, info, fc, &tx_flags);

	tx_flags &= ~(TX_CMD_FLG_ANT_SEL_MSK);
	अगर (ieee80211_is_mgmt(fc)) अणु
		अगर (ieee80211_is_assoc_req(fc) || ieee80211_is_reassoc_req(fc))
			tx_cmd->समयout.pm_frame_समयout = cpu_to_le16(3);
		अन्यथा
			tx_cmd->समयout.pm_frame_समयout = cpu_to_le16(2);
	पूर्ण अन्यथा अणु
		tx_cmd->समयout.pm_frame_समयout = 0;
	पूर्ण

	tx_cmd->driver_txop = 0;
	tx_cmd->tx_flags = tx_flags;
	tx_cmd->next_frame_len = 0;
पूर्ण

अटल व्योम iwlagn_tx_cmd_build_rate(काष्ठा iwl_priv *priv,
				     काष्ठा iwl_tx_cmd *tx_cmd,
				     काष्ठा ieee80211_tx_info *info,
				     काष्ठा ieee80211_sta *sta,
				     __le16 fc)
अणु
	u32 rate_flags;
	पूर्णांक rate_idx;
	u8 rts_retry_limit;
	u8 data_retry_limit;
	u8 rate_plcp;

	अगर (priv->wowlan) अणु
		rts_retry_limit = IWLAGN_LOW_RETRY_LIMIT;
		data_retry_limit = IWLAGN_LOW_RETRY_LIMIT;
	पूर्ण अन्यथा अणु
		/* Set retry limit on RTS packets */
		rts_retry_limit = IWLAGN_RTS_DFAULT_RETRY_LIMIT;

		/* Set retry limit on DATA packets and Probe Responses*/
		अगर (ieee80211_is_probe_resp(fc)) अणु
			data_retry_limit = IWLAGN_MGMT_DFAULT_RETRY_LIMIT;
			rts_retry_limit =
				min(data_retry_limit, rts_retry_limit);
		पूर्ण अन्यथा अगर (ieee80211_is_back_req(fc))
			data_retry_limit = IWLAGN_BAR_DFAULT_RETRY_LIMIT;
		अन्यथा
			data_retry_limit = IWLAGN_DEFAULT_TX_RETRY;
	पूर्ण

	tx_cmd->data_retry_limit = data_retry_limit;
	tx_cmd->rts_retry_limit = rts_retry_limit;

	/* DATA packets will use the uCode station table क्रम rate/antenna
	 * selection */
	अगर (ieee80211_is_data(fc)) अणु
		tx_cmd->initial_rate_index = 0;
		tx_cmd->tx_flags |= TX_CMD_FLG_STA_RATE_MSK;
		वापस;
	पूर्ण अन्यथा अगर (ieee80211_is_back_req(fc))
		tx_cmd->tx_flags |= TX_CMD_FLG_STA_RATE_MSK;

	/**
	 * If the current TX rate stored in mac80211 has the MCS bit set, it's
	 * not really a TX rate.  Thus, we use the lowest supported rate क्रम
	 * this band.  Also use the lowest supported rate अगर the stored rate
	 * index is invalid.
	 */
	rate_idx = info->control.rates[0].idx;
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_MCS ||
			(rate_idx < 0) || (rate_idx > IWL_RATE_COUNT_LEGACY))
		rate_idx = rate_lowest_index(
				&priv->nvm_data->bands[info->band], sta);
	/* For 5 GHZ band, remap mac80211 rate indices पूर्णांकo driver indices */
	अगर (info->band == NL80211_BAND_5GHZ)
		rate_idx += IWL_FIRST_OFDM_RATE;
	/* Get PLCP rate क्रम tx_cmd->rate_n_flags */
	rate_plcp = iwl_rates[rate_idx].plcp;
	/* Zero out flags क्रम this packet */
	rate_flags = 0;

	/* Set CCK flag as needed */
	अगर ((rate_idx >= IWL_FIRST_CCK_RATE) && (rate_idx <= IWL_LAST_CCK_RATE))
		rate_flags |= RATE_MCS_CCK_MSK;

	/* Set up antennas */
	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist &&
	    priv->bt_full_concurrent) अणु
		/* operated as 1x1 in full concurrency mode */
		priv->mgmt_tx_ant = iwl_toggle_tx_ant(priv, priv->mgmt_tx_ant,
				first_antenna(priv->nvm_data->valid_tx_ant));
	पूर्ण अन्यथा
		priv->mgmt_tx_ant = iwl_toggle_tx_ant(
					priv, priv->mgmt_tx_ant,
					priv->nvm_data->valid_tx_ant);
	rate_flags |= iwl_ant_idx_to_flags(priv->mgmt_tx_ant);

	/* Set the rate in the TX cmd */
	tx_cmd->rate_n_flags = iwl_hw_set_rate_n_flags(rate_plcp, rate_flags);
पूर्ण

अटल व्योम iwlagn_tx_cmd_build_hwcrypto(काष्ठा iwl_priv *priv,
					 काष्ठा ieee80211_tx_info *info,
					 काष्ठा iwl_tx_cmd *tx_cmd,
					 काष्ठा sk_buff *skb_frag)
अणु
	काष्ठा ieee80211_key_conf *keyconf = info->control.hw_key;

	चयन (keyconf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		tx_cmd->sec_ctl = TX_CMD_SEC_CCM;
		स_नकल(tx_cmd->key, keyconf->key, keyconf->keylen);
		अगर (info->flags & IEEE80211_TX_CTL_AMPDU)
			tx_cmd->tx_flags |= TX_CMD_FLG_AGG_CCMP_MSK;
		अवरोध;

	हाल WLAN_CIPHER_SUITE_TKIP:
		tx_cmd->sec_ctl = TX_CMD_SEC_TKIP;
		ieee80211_get_tkip_p2k(keyconf, skb_frag, tx_cmd->key);
		अवरोध;

	हाल WLAN_CIPHER_SUITE_WEP104:
		tx_cmd->sec_ctl |= TX_CMD_SEC_KEY128;
		fallthrough;
	हाल WLAN_CIPHER_SUITE_WEP40:
		tx_cmd->sec_ctl |= (TX_CMD_SEC_WEP |
			(keyconf->keyidx & TX_CMD_SEC_MSK) << TX_CMD_SEC_SHIFT);

		स_नकल(&tx_cmd->key[3], keyconf->key, keyconf->keylen);

		IWL_DEBUG_TX(priv, "Configuring packet for WEP encryption "
			     "with key %d\n", keyconf->keyidx);
		अवरोध;

	शेष:
		IWL_ERR(priv, "Unknown encode cipher %x\n", keyconf->cipher);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * iwl_sta_id_or_broadcast - वापस sta_id or broadcast sta
 * @context: the current context
 * @sta: mac80211 station
 *
 * In certain circumstances mac80211 passes a station poपूर्णांकer
 * that may be %शून्य, क्रम example during TX or key setup. In
 * that हाल, we need to use the broadcast station, so this
 * अंतरभूत wraps that pattern.
 */
अटल पूर्णांक iwl_sta_id_or_broadcast(काष्ठा iwl_rxon_context *context,
				   काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक sta_id;

	अगर (!sta)
		वापस context->bcast_sta_id;

	sta_id = iwl_sta_id(sta);

	/*
	 * mac80211 should not be passing a partially
	 * initialised station!
	 */
	WARN_ON(sta_id == IWL_INVALID_STATION);

	वापस sta_id;
पूर्ण

/*
 * start REPLY_TX command process
 */
पूर्णांक iwlagn_tx_skb(काष्ठा iwl_priv *priv,
		  काष्ठा ieee80211_sta *sta,
		  काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा iwl_station_priv *sta_priv = शून्य;
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	काष्ठा iwl_device_tx_cmd *dev_cmd;
	काष्ठा iwl_tx_cmd *tx_cmd;
	__le16 fc;
	u8 hdr_len;
	u16 len, seq_number = 0;
	u8 sta_id, tid = IWL_MAX_TID_COUNT;
	bool is_agg = false, is_data_qos = false;
	पूर्णांक txq_id;

	अगर (info->control.vअगर)
		ctx = iwl_rxon_ctx_from_vअगर(info->control.vअगर);

	अगर (iwl_is_rfसमाप्त(priv)) अणु
		IWL_DEBUG_DROP(priv, "Dropping - RF KILL\n");
		जाओ drop_unlock_priv;
	पूर्ण

	fc = hdr->frame_control;

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
	अगर (ieee80211_is_auth(fc))
		IWL_DEBUG_TX(priv, "Sending AUTH frame\n");
	अन्यथा अगर (ieee80211_is_assoc_req(fc))
		IWL_DEBUG_TX(priv, "Sending ASSOC frame\n");
	अन्यथा अगर (ieee80211_is_reassoc_req(fc))
		IWL_DEBUG_TX(priv, "Sending REASSOC frame\n");
#पूर्ण_अगर

	अगर (unlikely(ieee80211_is_probe_resp(fc))) अणु
		काष्ठा iwl_wipan_noa_data *noa_data =
			rcu_dereference(priv->noa_data);

		अगर (noa_data &&
		    pskb_expand_head(skb, 0, noa_data->length,
				     GFP_ATOMIC) == 0) अणु
			skb_put_data(skb, noa_data->data, noa_data->length);
			hdr = (काष्ठा ieee80211_hdr *)skb->data;
		पूर्ण
	पूर्ण

	hdr_len = ieee80211_hdrlen(fc);

	/* For management frames use broadcast id to करो not अवरोध aggregation */
	अगर (!ieee80211_is_data(fc))
		sta_id = ctx->bcast_sta_id;
	अन्यथा अणु
		/* Find index पूर्णांकo station table क्रम destination station */
		sta_id = iwl_sta_id_or_broadcast(ctx, sta);
		अगर (sta_id == IWL_INVALID_STATION) अणु
			IWL_DEBUG_DROP(priv, "Dropping - INVALID STATION: %pM\n",
				       hdr->addr1);
			जाओ drop_unlock_priv;
		पूर्ण
	पूर्ण

	अगर (sta)
		sta_priv = (व्योम *)sta->drv_priv;

	अगर (sta_priv && sta_priv->asleep &&
	    (info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER)) अणु
		/*
		 * This sends an asynchronous command to the device,
		 * but we can rely on it being processed beक्रमe the
		 * next frame is processed -- and the next frame to
		 * this station is the one that will consume this
		 * counter.
		 * For now set the counter to just 1 since we करो not
		 * support uAPSD yet.
		 *
		 * FIXME: If we get two non-bufferable frames one
		 * after the other, we might only send out one of
		 * them because this is racy.
		 */
		iwl_sta_modअगरy_sleep_tx_count(priv, sta_id, 1);
	पूर्ण

	dev_cmd = iwl_trans_alloc_tx_cmd(priv->trans);

	अगर (unlikely(!dev_cmd))
		जाओ drop_unlock_priv;

	dev_cmd->hdr.cmd = REPLY_TX;
	tx_cmd = (काष्ठा iwl_tx_cmd *) dev_cmd->payload;

	/* Total # bytes to be transmitted */
	len = (u16)skb->len;
	tx_cmd->len = cpu_to_le16(len);

	अगर (info->control.hw_key)
		iwlagn_tx_cmd_build_hwcrypto(priv, info, tx_cmd, skb);

	/* TODO need this क्रम burst mode later on */
	iwlagn_tx_cmd_build_basic(priv, skb, tx_cmd, info, hdr, sta_id);

	iwlagn_tx_cmd_build_rate(priv, tx_cmd, info, sta, fc);

	स_रखो(&info->status, 0, माप(info->status));
	स_रखो(info->driver_data, 0, माप(info->driver_data));

	info->driver_data[0] = ctx;
	info->driver_data[1] = dev_cmd;
	/* From now on, we cannot access info->control */

	spin_lock(&priv->sta_lock);

	अगर (ieee80211_is_data_qos(fc) && !ieee80211_is_qos_nullfunc(fc)) अणु
		u8 *qc = शून्य;
		काष्ठा iwl_tid_data *tid_data;
		qc = ieee80211_get_qos_ctl(hdr);
		tid = qc[0] & IEEE80211_QOS_CTL_TID_MASK;
		अगर (WARN_ON_ONCE(tid >= IWL_MAX_TID_COUNT))
			जाओ drop_unlock_sta;
		tid_data = &priv->tid_data[sta_id][tid];

		/* aggregation is on क्रम this <sta,tid> */
		अगर (info->flags & IEEE80211_TX_CTL_AMPDU &&
		    tid_data->agg.state != IWL_AGG_ON) अणु
			IWL_ERR(priv,
				"TX_CTL_AMPDU while not in AGG: Tx flags = 0x%08x, agg.state = %d\n",
				info->flags, tid_data->agg.state);
			IWL_ERR(priv, "sta_id = %d, tid = %d seq_num = %d\n",
				sta_id, tid,
				IEEE80211_SEQ_TO_SN(tid_data->seq_number));
			जाओ drop_unlock_sta;
		पूर्ण

		/* We can receive packets from the stack in IWL_AGG_अणुON,OFFपूर्ण
		 * only. Check this here.
		 */
		अगर (WARN_ONCE(tid_data->agg.state != IWL_AGG_ON &&
			      tid_data->agg.state != IWL_AGG_OFF,
			      "Tx while agg.state = %d\n", tid_data->agg.state))
			जाओ drop_unlock_sta;

		seq_number = tid_data->seq_number;
		seq_number &= IEEE80211_SCTL_SEQ;
		hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(seq_number);
		seq_number += 0x10;

		अगर (info->flags & IEEE80211_TX_CTL_AMPDU)
			is_agg = true;
		is_data_qos = true;
	पूर्ण

	/* Copy MAC header from skb पूर्णांकo command buffer */
	स_नकल(tx_cmd->hdr, hdr, hdr_len);

	txq_id = info->hw_queue;

	अगर (is_agg)
		txq_id = priv->tid_data[sta_id][tid].agg.txq_id;
	अन्यथा अगर (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) अणु
		/*
		 * The microcode will clear the more data
		 * bit in the last frame it transmits.
		 */
		hdr->frame_control |=
			cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	पूर्ण

	WARN_ON_ONCE(is_agg &&
		     priv->queue_to_mac80211[txq_id] != info->hw_queue);

	IWL_DEBUG_TX(priv, "TX to [%d|%d] Q:%d - seq: 0x%x\n", sta_id, tid,
		     txq_id, seq_number);

	अगर (iwl_trans_tx(priv->trans, skb, dev_cmd, txq_id))
		जाओ drop_unlock_sta;

	अगर (is_data_qos && !ieee80211_has_morefrags(fc))
		priv->tid_data[sta_id][tid].seq_number = seq_number;

	spin_unlock(&priv->sta_lock);

	/*
	 * Aव्योम atomic ops अगर it isn't an associated client.
	 * Also, अगर this is a packet क्रम aggregation, करोn't
	 * increase the counter because the ucode will stop
	 * aggregation queues when their respective station
	 * goes to sleep.
	 */
	अगर (sta_priv && sta_priv->client && !is_agg)
		atomic_inc(&sta_priv->pending_frames);

	वापस 0;

drop_unlock_sta:
	अगर (dev_cmd)
		iwl_trans_मुक्त_tx_cmd(priv->trans, dev_cmd);
	spin_unlock(&priv->sta_lock);
drop_unlock_priv:
	वापस -1;
पूर्ण

अटल पूर्णांक iwlagn_alloc_agg_txq(काष्ठा iwl_priv *priv, पूर्णांक mq)
अणु
	पूर्णांक q;

	क्रम (q = IWLAGN_FIRST_AMPDU_QUEUE;
	     q < priv->trans->trans_cfg->base_params->num_of_queues; q++) अणु
		अगर (!test_and_set_bit(q, priv->agg_q_alloc)) अणु
			priv->queue_to_mac80211[q] = mq;
			वापस q;
		पूर्ण
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल व्योम iwlagn_dealloc_agg_txq(काष्ठा iwl_priv *priv, पूर्णांक q)
अणु
	clear_bit(q, priv->agg_q_alloc);
	priv->queue_to_mac80211[q] = IWL_INVALID_MAC80211_QUEUE;
पूर्ण

पूर्णांक iwlagn_tx_agg_stop(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा iwl_tid_data *tid_data;
	पूर्णांक sta_id, txq_id;
	क्रमागत iwl_agg_state agg_state;

	sta_id = iwl_sta_id(sta);

	अगर (sta_id == IWL_INVALID_STATION) अणु
		IWL_ERR(priv, "Invalid station for AGG tid %d\n", tid);
		वापस -ENXIO;
	पूर्ण

	spin_lock_bh(&priv->sta_lock);

	tid_data = &priv->tid_data[sta_id][tid];
	txq_id = tid_data->agg.txq_id;

	चयन (tid_data->agg.state) अणु
	हाल IWL_EMPTYING_HW_QUEUE_ADDBA:
		/*
		* This can happen अगर the peer stops aggregation
		* again beक्रमe we've had a chance to drain the
		* queue we selected previously, i.e. beक्रमe the
		* session was really started completely.
		*/
		IWL_DEBUG_HT(priv, "AGG stop before setup done\n");
		जाओ turn_off;
	हाल IWL_AGG_STARTING:
		/*
		 * This can happen when the session is stopped beक्रमe
		 * we receive ADDBA response
		 */
		IWL_DEBUG_HT(priv, "AGG stop before AGG became operational\n");
		जाओ turn_off;
	हाल IWL_AGG_ON:
		अवरोध;
	शेष:
		IWL_WARN(priv,
			 "Stopping AGG while state not ON or starting for %d on %d (%d)\n",
			 sta_id, tid, tid_data->agg.state);
		spin_unlock_bh(&priv->sta_lock);
		वापस 0;
	पूर्ण

	tid_data->agg.ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);

	/* There are still packets क्रम this RA / TID in the HW */
	अगर (!test_bit(txq_id, priv->agg_q_alloc)) अणु
		IWL_DEBUG_TX_QUEUES(priv,
			"stopping AGG on STA/TID %d/%d but hwq %d not used\n",
			sta_id, tid, txq_id);
	पूर्ण अन्यथा अगर (tid_data->agg.ssn != tid_data->next_reclaimed) अणु
		IWL_DEBUG_TX_QUEUES(priv,
				    "Can't proceed: ssn %d, next_recl = %d\n",
				    tid_data->agg.ssn,
				    tid_data->next_reclaimed);
		tid_data->agg.state = IWL_EMPTYING_HW_QUEUE_DELBA;
		spin_unlock_bh(&priv->sta_lock);
		वापस 0;
	पूर्ण

	IWL_DEBUG_TX_QUEUES(priv, "Can proceed: ssn = next_recl = %d\n",
			    tid_data->agg.ssn);
turn_off:
	agg_state = tid_data->agg.state;
	tid_data->agg.state = IWL_AGG_OFF;

	spin_unlock_bh(&priv->sta_lock);

	अगर (test_bit(txq_id, priv->agg_q_alloc)) अणु
		/*
		 * If the transport didn't know that we wanted to start
		 * agreggation, करोn't tell it that we want to stop them.
		 * This can happen when we करोn't get the addBA response on
		 * समय, or we hadn't समय to drain the AC queues.
		 */
		अगर (agg_state == IWL_AGG_ON)
			iwl_trans_txq_disable(priv->trans, txq_id, true);
		अन्यथा
			IWL_DEBUG_TX_QUEUES(priv, "Don't disable tx agg: %d\n",
					    agg_state);
		iwlagn_dealloc_agg_txq(priv, txq_id);
	पूर्ण

	ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);

	वापस 0;
पूर्ण

पूर्णांक iwlagn_tx_agg_start(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid, u16 *ssn)
अणु
	काष्ठा iwl_rxon_context *ctx = iwl_rxon_ctx_from_vअगर(vअगर);
	काष्ठा iwl_tid_data *tid_data;
	पूर्णांक sta_id, txq_id, ret;

	IWL_DEBUG_HT(priv, "TX AGG request on ra = %pM tid = %d\n",
		     sta->addr, tid);

	sta_id = iwl_sta_id(sta);
	अगर (sta_id == IWL_INVALID_STATION) अणु
		IWL_ERR(priv, "Start AGG on invalid station\n");
		वापस -ENXIO;
	पूर्ण
	अगर (unlikely(tid >= IWL_MAX_TID_COUNT))
		वापस -EINVAL;

	अगर (priv->tid_data[sta_id][tid].agg.state != IWL_AGG_OFF) अणु
		IWL_ERR(priv, "Start AGG when state is not IWL_AGG_OFF !\n");
		वापस -ENXIO;
	पूर्ण

	txq_id = iwlagn_alloc_agg_txq(priv, ctx->ac_to_queue[tid_to_ac[tid]]);
	अगर (txq_id < 0) अणु
		IWL_DEBUG_TX_QUEUES(priv,
			"No free aggregation queue for %pM/%d\n",
			sta->addr, tid);
		वापस txq_id;
	पूर्ण

	ret = iwl_sta_tx_modअगरy_enable_tid(priv, sta_id, tid);
	अगर (ret)
		वापस ret;

	spin_lock_bh(&priv->sta_lock);
	tid_data = &priv->tid_data[sta_id][tid];
	tid_data->agg.ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);
	tid_data->agg.txq_id = txq_id;

	*ssn = tid_data->agg.ssn;

	अगर (*ssn == tid_data->next_reclaimed) अणु
		IWL_DEBUG_TX_QUEUES(priv, "Can proceed: ssn = next_recl = %d\n",
				    tid_data->agg.ssn);
		tid_data->agg.state = IWL_AGG_STARTING;
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
	पूर्ण अन्यथा अणु
		IWL_DEBUG_TX_QUEUES(priv, "Can't proceed: ssn %d, "
				    "next_reclaimed = %d\n",
				    tid_data->agg.ssn,
				    tid_data->next_reclaimed);
		tid_data->agg.state = IWL_EMPTYING_HW_QUEUE_ADDBA;
	पूर्ण
	spin_unlock_bh(&priv->sta_lock);

	वापस ret;
पूर्ण

पूर्णांक iwlagn_tx_agg_flush(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा iwl_tid_data *tid_data;
	क्रमागत iwl_agg_state agg_state;
	पूर्णांक sta_id, txq_id;
	sta_id = iwl_sta_id(sta);

	/*
	 * First set the agg state to OFF to aव्योम calling
	 * ieee80211_stop_tx_ba_cb in iwlagn_check_ratid_empty.
	 */
	spin_lock_bh(&priv->sta_lock);

	tid_data = &priv->tid_data[sta_id][tid];
	txq_id = tid_data->agg.txq_id;
	agg_state = tid_data->agg.state;
	IWL_DEBUG_TX_QUEUES(priv, "Flush AGG: sta %d tid %d q %d state %d\n",
			    sta_id, tid, txq_id, tid_data->agg.state);

	tid_data->agg.state = IWL_AGG_OFF;

	spin_unlock_bh(&priv->sta_lock);

	अगर (iwlagn_txfअगरo_flush(priv, BIT(txq_id)))
		IWL_ERR(priv, "Couldn't flush the AGG queue\n");

	अगर (test_bit(txq_id, priv->agg_q_alloc)) अणु
		/*
		 * If the transport didn't know that we wanted to start
		 * agreggation, करोn't tell it that we want to stop them.
		 * This can happen when we करोn't get the addBA response on
		 * समय, or we hadn't समय to drain the AC queues.
		 */
		अगर (agg_state == IWL_AGG_ON)
			iwl_trans_txq_disable(priv->trans, txq_id, true);
		अन्यथा
			IWL_DEBUG_TX_QUEUES(priv, "Don't disable tx agg: %d\n",
					    agg_state);
		iwlagn_dealloc_agg_txq(priv, txq_id);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwlagn_tx_agg_oper(काष्ठा iwl_priv *priv, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid, u8 buf_size)
अणु
	काष्ठा iwl_station_priv *sta_priv = (व्योम *) sta->drv_priv;
	काष्ठा iwl_rxon_context *ctx = iwl_rxon_ctx_from_vअगर(vअगर);
	पूर्णांक q, fअगरo;
	u16 ssn;

	buf_size = min_t(पूर्णांक, buf_size, LINK_QUAL_AGG_FRAME_LIMIT_DEF);

	spin_lock_bh(&priv->sta_lock);
	ssn = priv->tid_data[sta_priv->sta_id][tid].agg.ssn;
	q = priv->tid_data[sta_priv->sta_id][tid].agg.txq_id;
	priv->tid_data[sta_priv->sta_id][tid].agg.state = IWL_AGG_ON;
	spin_unlock_bh(&priv->sta_lock);

	fअगरo = ctx->ac_to_fअगरo[tid_to_ac[tid]];

	iwl_trans_txq_enable(priv->trans, q, fअगरo, sta_priv->sta_id, tid,
			     buf_size, ssn, 0);

	/*
	 * If the limit is 0, then it wasn't initialised yet,
	 * use the शेष. We can करो that since we take the
	 * minimum below, and we करोn't want to go above our
	 * शेष due to hardware restrictions.
	 */
	अगर (sta_priv->max_agg_bufsize == 0)
		sta_priv->max_agg_bufsize =
			LINK_QUAL_AGG_FRAME_LIMIT_DEF;

	/*
	 * Even though in theory the peer could have dअगरferent
	 * aggregation reorder buffer sizes क्रम dअगरferent sessions,
	 * our ucode करोesn't allow क्रम that and has a global limit
	 * क्रम each station. Thereक्रमe, use the minimum of all the
	 * aggregation sessions and our शेष value.
	 */
	sta_priv->max_agg_bufsize =
		min(sta_priv->max_agg_bufsize, buf_size);

	अगर (priv->hw_params.use_rts_क्रम_aggregation) अणु
		/*
		 * चयन to RTS/CTS अगर it is the prefer protection
		 * method क्रम HT traffic
		 */

		sta_priv->lq_sta.lq.general_params.flags |=
			LINK_QUAL_FLAGS_SET_STA_TLC_RTS_MSK;
	पूर्ण
	priv->agg_tids_count++;
	IWL_DEBUG_HT(priv, "priv->agg_tids_count = %u\n",
		     priv->agg_tids_count);

	sta_priv->lq_sta.lq.agg_params.agg_frame_cnt_limit =
		sta_priv->max_agg_bufsize;

	IWL_DEBUG_HT(priv, "Tx aggregation enabled on ra = %pM tid = %d\n",
		 sta->addr, tid);

	वापस iwl_send_lq_cmd(priv, ctx,
			&sta_priv->lq_sta.lq, CMD_ASYNC, false);
पूर्ण

अटल व्योम iwlagn_check_ratid_empty(काष्ठा iwl_priv *priv, पूर्णांक sta_id, u8 tid)
अणु
	काष्ठा iwl_tid_data *tid_data = &priv->tid_data[sta_id][tid];
	क्रमागत iwl_rxon_context_id ctx;
	काष्ठा ieee80211_vअगर *vअगर;
	u8 *addr;

	lockdep_निश्चित_held(&priv->sta_lock);

	addr = priv->stations[sta_id].sta.sta.addr;
	ctx = priv->stations[sta_id].ctxid;
	vअगर = priv->contexts[ctx].vअगर;

	चयन (priv->tid_data[sta_id][tid].agg.state) अणु
	हाल IWL_EMPTYING_HW_QUEUE_DELBA:
		/* There are no packets क्रम this RA / TID in the HW any more */
		अगर (tid_data->agg.ssn == tid_data->next_reclaimed) अणु
			IWL_DEBUG_TX_QUEUES(priv,
				"Can continue DELBA flow ssn = next_recl = %d\n",
				tid_data->next_reclaimed);
			iwl_trans_txq_disable(priv->trans,
					      tid_data->agg.txq_id, true);
			iwlagn_dealloc_agg_txq(priv, tid_data->agg.txq_id);
			tid_data->agg.state = IWL_AGG_OFF;
			ieee80211_stop_tx_ba_cb_irqsafe(vअगर, addr, tid);
		पूर्ण
		अवरोध;
	हाल IWL_EMPTYING_HW_QUEUE_ADDBA:
		/* There are no packets क्रम this RA / TID in the HW any more */
		अगर (tid_data->agg.ssn == tid_data->next_reclaimed) अणु
			IWL_DEBUG_TX_QUEUES(priv,
				"Can continue ADDBA flow ssn = next_recl = %d\n",
				tid_data->next_reclaimed);
			tid_data->agg.state = IWL_AGG_STARTING;
			ieee80211_start_tx_ba_cb_irqsafe(vअगर, addr, tid);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम iwlagn_non_agg_tx_status(काष्ठा iwl_priv *priv,
				     काष्ठा iwl_rxon_context *ctx,
				     स्थिर u8 *addr1)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_station_priv *sta_priv;

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(ctx->vअगर, addr1);
	अगर (sta) अणु
		sta_priv = (व्योम *)sta->drv_priv;
		/* aव्योम atomic ops अगर this isn't a client */
		अगर (sta_priv->client &&
		    atomic_dec_वापस(&sta_priv->pending_frames) == 0)
			ieee80211_sta_block_awake(priv->hw, sta, false);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * translate ucode response to mac80211 tx status control values
 */
अटल व्योम iwlagn_hwrate_to_tx_control(काष्ठा iwl_priv *priv, u32 rate_n_flags,
				  काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा ieee80211_tx_rate *r = &info->status.rates[0];

	info->status.antenna =
		((rate_n_flags & RATE_MCS_ANT_ABC_MSK) >> RATE_MCS_ANT_POS);
	अगर (rate_n_flags & RATE_MCS_HT_MSK)
		r->flags |= IEEE80211_TX_RC_MCS;
	अगर (rate_n_flags & RATE_MCS_GF_MSK)
		r->flags |= IEEE80211_TX_RC_GREEN_FIELD;
	अगर (rate_n_flags & RATE_MCS_HT40_MSK)
		r->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
	अगर (rate_n_flags & RATE_MCS_DUP_MSK)
		r->flags |= IEEE80211_TX_RC_DUP_DATA;
	अगर (rate_n_flags & RATE_MCS_SGI_MSK)
		r->flags |= IEEE80211_TX_RC_SHORT_GI;
	r->idx = iwlagn_hwrate_to_mac80211_idx(rate_n_flags, info->band);
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
स्थिर अक्षर *iwl_get_tx_fail_reason(u32 status)
अणु
#घोषणा TX_STATUS_FAIL(x) हाल TX_STATUS_FAIL_ ## x: वापस #x
#घोषणा TX_STATUS_POSTPONE(x) हाल TX_STATUS_POSTPONE_ ## x: वापस #x

	चयन (status & TX_STATUS_MSK) अणु
	हाल TX_STATUS_SUCCESS:
		वापस "SUCCESS";
	TX_STATUS_POSTPONE(DELAY);
	TX_STATUS_POSTPONE(FEW_BYTES);
	TX_STATUS_POSTPONE(BT_PRIO);
	TX_STATUS_POSTPONE(QUIET_PERIOD);
	TX_STATUS_POSTPONE(CALC_TTAK);
	TX_STATUS_FAIL(INTERNAL_CROSSED_RETRY);
	TX_STATUS_FAIL(SHORT_LIMIT);
	TX_STATUS_FAIL(LONG_LIMIT);
	TX_STATUS_FAIL(FIFO_UNDERRUN);
	TX_STATUS_FAIL(DRAIN_FLOW);
	TX_STATUS_FAIL(RFKILL_FLUSH);
	TX_STATUS_FAIL(LIFE_EXPIRE);
	TX_STATUS_FAIL(DEST_PS);
	TX_STATUS_FAIL(HOST_ABORTED);
	TX_STATUS_FAIL(BT_RETRY);
	TX_STATUS_FAIL(STA_INVALID);
	TX_STATUS_FAIL(FRAG_DROPPED);
	TX_STATUS_FAIL(TID_DISABLE);
	TX_STATUS_FAIL(FIFO_FLUSHED);
	TX_STATUS_FAIL(INSUFFICIENT_CF_POLL);
	TX_STATUS_FAIL(PASSIVE_NO_RX);
	TX_STATUS_FAIL(NO_BEACON_ON_RADAR);
	पूर्ण

	वापस "UNKNOWN";

#अघोषित TX_STATUS_FAIL
#अघोषित TX_STATUS_POSTPONE
पूर्ण
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUG */

अटल व्योम iwlagn_count_agg_tx_err_status(काष्ठा iwl_priv *priv, u16 status)
अणु
	status &= AGG_TX_STATUS_MSK;

	चयन (status) अणु
	हाल AGG_TX_STATE_UNDERRUN_MSK:
		priv->reply_agg_tx_stats.underrun++;
		अवरोध;
	हाल AGG_TX_STATE_BT_PRIO_MSK:
		priv->reply_agg_tx_stats.bt_prio++;
		अवरोध;
	हाल AGG_TX_STATE_FEW_BYTES_MSK:
		priv->reply_agg_tx_stats.few_bytes++;
		अवरोध;
	हाल AGG_TX_STATE_ABORT_MSK:
		priv->reply_agg_tx_stats.पात++;
		अवरोध;
	हाल AGG_TX_STATE_LAST_SENT_TTL_MSK:
		priv->reply_agg_tx_stats.last_sent_ttl++;
		अवरोध;
	हाल AGG_TX_STATE_LAST_SENT_TRY_CNT_MSK:
		priv->reply_agg_tx_stats.last_sent_try++;
		अवरोध;
	हाल AGG_TX_STATE_LAST_SENT_BT_KILL_MSK:
		priv->reply_agg_tx_stats.last_sent_bt_समाप्त++;
		अवरोध;
	हाल AGG_TX_STATE_SCD_QUERY_MSK:
		priv->reply_agg_tx_stats.scd_query++;
		अवरोध;
	हाल AGG_TX_STATE_TEST_BAD_CRC32_MSK:
		priv->reply_agg_tx_stats.bad_crc32++;
		अवरोध;
	हाल AGG_TX_STATE_RESPONSE_MSK:
		priv->reply_agg_tx_stats.response++;
		अवरोध;
	हाल AGG_TX_STATE_DUMP_TX_MSK:
		priv->reply_agg_tx_stats.dump_tx++;
		अवरोध;
	हाल AGG_TX_STATE_DELAY_TX_MSK:
		priv->reply_agg_tx_stats.delay_tx++;
		अवरोध;
	शेष:
		priv->reply_agg_tx_stats.unknown++;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u32 iwlagn_get_scd_ssn(काष्ठा iwlagn_tx_resp *tx_resp)
अणु
	वापस le32_to_cpup((__le32 *)&tx_resp->status +
			    tx_resp->frame_count) & IEEE80211_MAX_SN;
पूर्ण

अटल व्योम iwl_rx_reply_tx_agg(काष्ठा iwl_priv *priv,
				काष्ठा iwlagn_tx_resp *tx_resp)
अणु
	काष्ठा agg_tx_status *frame_status = &tx_resp->status;
	पूर्णांक tid = (tx_resp->ra_tid & IWLAGN_TX_RES_TID_MSK) >>
		IWLAGN_TX_RES_TID_POS;
	पूर्णांक sta_id = (tx_resp->ra_tid & IWLAGN_TX_RES_RA_MSK) >>
		IWLAGN_TX_RES_RA_POS;
	काष्ठा iwl_ht_agg *agg = &priv->tid_data[sta_id][tid].agg;
	u32 status = le16_to_cpu(tx_resp->status.status);
	पूर्णांक i;

	WARN_ON(tid == IWL_TID_NON_QOS);

	अगर (agg->रुको_क्रम_ba)
		IWL_DEBUG_TX_REPLY(priv,
			"got tx response w/o block-ack\n");

	agg->rate_n_flags = le32_to_cpu(tx_resp->rate_n_flags);
	agg->रुको_क्रम_ba = (tx_resp->frame_count > 1);

	/*
	 * If the BT समाप्त count is non-zero, we'll get this
	 * notअगरication again.
	 */
	अगर (tx_resp->bt_समाप्त_count && tx_resp->frame_count == 1 &&
	    priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) अणु
		IWL_DEBUG_COEX(priv, "receive reply tx w/ bt_kill\n");
	पूर्ण

	अगर (tx_resp->frame_count == 1)
		वापस;

	IWL_DEBUG_TX_REPLY(priv, "TXQ %d initial_rate 0x%x ssn %d frm_cnt %d\n",
			   agg->txq_id,
			   le32_to_cpu(tx_resp->rate_n_flags),
			   iwlagn_get_scd_ssn(tx_resp), tx_resp->frame_count);

	/* Conकाष्ठा bit-map of pending frames within Tx winकरोw */
	क्रम (i = 0; i < tx_resp->frame_count; i++) अणु
		u16 ख_स्थितिus = le16_to_cpu(frame_status[i].status);
		u8 retry_cnt = (ख_स्थितिus & AGG_TX_TRY_MSK) >> AGG_TX_TRY_POS;

		अगर (status & AGG_TX_STATUS_MSK)
			iwlagn_count_agg_tx_err_status(priv, ख_स्थितिus);

		अगर (status & (AGG_TX_STATE_FEW_BYTES_MSK |
			      AGG_TX_STATE_ABORT_MSK))
			जारी;

		अगर (status & AGG_TX_STATUS_MSK || retry_cnt > 1)
			IWL_DEBUG_TX_REPLY(priv,
					   "%d: status %s (0x%04x), try-count (0x%01x)\n",
					   i,
					   iwl_get_agg_tx_fail_reason(ख_स्थितिus),
					   ख_स्थितिus & AGG_TX_STATUS_MSK,
					   retry_cnt);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
#घोषणा AGG_TX_STATE_FAIL(x) हाल AGG_TX_STATE_ ## x: वापस #x

स्थिर अक्षर *iwl_get_agg_tx_fail_reason(u16 status)
अणु
	status &= AGG_TX_STATUS_MSK;
	चयन (status) अणु
	हाल AGG_TX_STATE_TRANSMITTED:
		वापस "SUCCESS";
		AGG_TX_STATE_FAIL(UNDERRUN_MSK);
		AGG_TX_STATE_FAIL(BT_PRIO_MSK);
		AGG_TX_STATE_FAIL(FEW_BYTES_MSK);
		AGG_TX_STATE_FAIL(ABORT_MSK);
		AGG_TX_STATE_FAIL(LAST_SENT_TTL_MSK);
		AGG_TX_STATE_FAIL(LAST_SENT_TRY_CNT_MSK);
		AGG_TX_STATE_FAIL(LAST_SENT_BT_KILL_MSK);
		AGG_TX_STATE_FAIL(SCD_QUERY_MSK);
		AGG_TX_STATE_FAIL(TEST_BAD_CRC32_MSK);
		AGG_TX_STATE_FAIL(RESPONSE_MSK);
		AGG_TX_STATE_FAIL(DUMP_TX_MSK);
		AGG_TX_STATE_FAIL(DELAY_TX_MSK);
	पूर्ण

	वापस "UNKNOWN";
पूर्ण
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUG */

अटल व्योम iwlagn_count_tx_err_status(काष्ठा iwl_priv *priv, u16 status)
अणु
	status &= TX_STATUS_MSK;

	चयन (status) अणु
	हाल TX_STATUS_POSTPONE_DELAY:
		priv->reply_tx_stats.pp_delay++;
		अवरोध;
	हाल TX_STATUS_POSTPONE_FEW_BYTES:
		priv->reply_tx_stats.pp_few_bytes++;
		अवरोध;
	हाल TX_STATUS_POSTPONE_BT_PRIO:
		priv->reply_tx_stats.pp_bt_prio++;
		अवरोध;
	हाल TX_STATUS_POSTPONE_QUIET_PERIOD:
		priv->reply_tx_stats.pp_quiet_period++;
		अवरोध;
	हाल TX_STATUS_POSTPONE_CALC_TTAK:
		priv->reply_tx_stats.pp_calc_ttak++;
		अवरोध;
	हाल TX_STATUS_FAIL_INTERNAL_CROSSED_RETRY:
		priv->reply_tx_stats.पूर्णांक_crossed_retry++;
		अवरोध;
	हाल TX_STATUS_FAIL_SHORT_LIMIT:
		priv->reply_tx_stats.लघु_limit++;
		अवरोध;
	हाल TX_STATUS_FAIL_LONG_LIMIT:
		priv->reply_tx_stats.दीर्घ_limit++;
		अवरोध;
	हाल TX_STATUS_FAIL_FIFO_UNDERRUN:
		priv->reply_tx_stats.fअगरo_underrun++;
		अवरोध;
	हाल TX_STATUS_FAIL_DRAIN_FLOW:
		priv->reply_tx_stats.drain_flow++;
		अवरोध;
	हाल TX_STATUS_FAIL_RFKILL_FLUSH:
		priv->reply_tx_stats.rfसमाप्त_flush++;
		अवरोध;
	हाल TX_STATUS_FAIL_LIFE_EXPIRE:
		priv->reply_tx_stats.lअगरe_expire++;
		अवरोध;
	हाल TX_STATUS_FAIL_DEST_PS:
		priv->reply_tx_stats.dest_ps++;
		अवरोध;
	हाल TX_STATUS_FAIL_HOST_ABORTED:
		priv->reply_tx_stats.host_पात++;
		अवरोध;
	हाल TX_STATUS_FAIL_BT_RETRY:
		priv->reply_tx_stats.bt_retry++;
		अवरोध;
	हाल TX_STATUS_FAIL_STA_INVALID:
		priv->reply_tx_stats.sta_invalid++;
		अवरोध;
	हाल TX_STATUS_FAIL_FRAG_DROPPED:
		priv->reply_tx_stats.frag_drop++;
		अवरोध;
	हाल TX_STATUS_FAIL_TID_DISABLE:
		priv->reply_tx_stats.tid_disable++;
		अवरोध;
	हाल TX_STATUS_FAIL_FIFO_FLUSHED:
		priv->reply_tx_stats.fअगरo_flush++;
		अवरोध;
	हाल TX_STATUS_FAIL_INSUFFICIENT_CF_POLL:
		priv->reply_tx_stats.insuff_cf_poll++;
		अवरोध;
	हाल TX_STATUS_FAIL_PASSIVE_NO_RX:
		priv->reply_tx_stats.fail_hw_drop++;
		अवरोध;
	हाल TX_STATUS_FAIL_NO_BEACON_ON_RADAR:
		priv->reply_tx_stats.sta_color_mismatch++;
		अवरोध;
	शेष:
		priv->reply_tx_stats.unknown++;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम iwlagn_set_tx_status(काष्ठा iwl_priv *priv,
				 काष्ठा ieee80211_tx_info *info,
				 काष्ठा iwlagn_tx_resp *tx_resp)
अणु
	u16 status = le16_to_cpu(tx_resp->status.status);

	info->flags &= ~IEEE80211_TX_CTL_AMPDU;

	info->status.rates[0].count = tx_resp->failure_frame + 1;
	info->flags |= iwl_tx_status_to_mac80211(status);
	iwlagn_hwrate_to_tx_control(priv, le32_to_cpu(tx_resp->rate_n_flags),
				    info);
	अगर (!iwl_is_tx_success(status))
		iwlagn_count_tx_err_status(priv, status);
पूर्ण

अटल व्योम iwl_check_पात_status(काष्ठा iwl_priv *priv,
			    u8 frame_count, u32 status)
अणु
	अगर (frame_count == 1 && status == TX_STATUS_FAIL_RFKILL_FLUSH) अणु
		IWL_ERR(priv, "Tx flush command to flush out all frames\n");
		अगर (!test_bit(STATUS_EXIT_PENDING, &priv->status))
			queue_work(priv->workqueue, &priv->tx_flush);
	पूर्ण
पूर्ण

व्योम iwlagn_rx_reply_tx(काष्ठा iwl_priv *priv, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	पूर्णांक txq_id = SEQ_TO_QUEUE(sequence);
	पूर्णांक cmd_index __maybe_unused = SEQ_TO_INDEX(sequence);
	काष्ठा iwlagn_tx_resp *tx_resp = (व्योम *)pkt->data;
	काष्ठा ieee80211_hdr *hdr;
	u32 status = le16_to_cpu(tx_resp->status.status);
	u16 ssn = iwlagn_get_scd_ssn(tx_resp);
	पूर्णांक tid;
	पूर्णांक sta_id;
	पूर्णांक मुक्तd;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff_head skbs;
	काष्ठा sk_buff *skb;
	काष्ठा iwl_rxon_context *ctx;
	bool is_agg = (txq_id >= IWLAGN_FIRST_AMPDU_QUEUE);

	tid = (tx_resp->ra_tid & IWLAGN_TX_RES_TID_MSK) >>
		IWLAGN_TX_RES_TID_POS;
	sta_id = (tx_resp->ra_tid & IWLAGN_TX_RES_RA_MSK) >>
		IWLAGN_TX_RES_RA_POS;

	spin_lock_bh(&priv->sta_lock);

	अगर (is_agg) अणु
		WARN_ON_ONCE(sta_id >= IWLAGN_STATION_COUNT ||
			     tid >= IWL_MAX_TID_COUNT);
		अगर (txq_id != priv->tid_data[sta_id][tid].agg.txq_id)
			IWL_ERR(priv, "txq_id mismatch: %d %d\n", txq_id,
				priv->tid_data[sta_id][tid].agg.txq_id);
		iwl_rx_reply_tx_agg(priv, tx_resp);
	पूर्ण

	__skb_queue_head_init(&skbs);

	अगर (tx_resp->frame_count == 1) अणु
		u16 next_reclaimed = le16_to_cpu(tx_resp->seq_ctl);
		next_reclaimed = IEEE80211_SEQ_TO_SN(next_reclaimed + 0x10);

		अगर (is_agg) अणु
			/* If this is an aggregation queue, we can rely on the
			 * ssn since the wअगरi sequence number corresponds to
			 * the index in the TFD ring (%256).
			 * The seq_ctl is the sequence control of the packet
			 * to which this Tx response relates. But अगर there is a
			 * hole in the biपंचांगap of the BA we received, this Tx
			 * response may allow to reclaim the hole and all the
			 * subsequent packets that were alपढ़ोy acked.
			 * In that हाल, seq_ctl != ssn, and the next packet
			 * to be reclaimed will be ssn and not seq_ctl.
			 */
			next_reclaimed = ssn;
		पूर्ण

		अगर (tid != IWL_TID_NON_QOS) अणु
			priv->tid_data[sta_id][tid].next_reclaimed =
				next_reclaimed;
			IWL_DEBUG_TX_REPLY(priv, "Next reclaimed packet:%d\n",
						  next_reclaimed);
			iwlagn_check_ratid_empty(priv, sta_id, tid);
		पूर्ण

		iwl_trans_reclaim(priv->trans, txq_id, ssn, &skbs);

		मुक्तd = 0;

		/* process frames */
		skb_queue_walk(&skbs, skb) अणु
			hdr = (काष्ठा ieee80211_hdr *)skb->data;

			अगर (!ieee80211_is_data_qos(hdr->frame_control))
				priv->last_seq_ctl = tx_resp->seq_ctl;

			info = IEEE80211_SKB_CB(skb);
			ctx = info->driver_data[0];
			iwl_trans_मुक्त_tx_cmd(priv->trans,
					      info->driver_data[1]);

			स_रखो(&info->status, 0, माप(info->status));

			अगर (status == TX_STATUS_FAIL_PASSIVE_NO_RX &&
			    ctx->vअगर &&
			    ctx->vअगर->type == NL80211_IFTYPE_STATION) अणु
				/* block and stop all queues */
				priv->passive_no_rx = true;
				IWL_DEBUG_TX_QUEUES(priv,
					"stop all queues: passive channel\n");
				ieee80211_stop_queues(priv->hw);

				IWL_DEBUG_TX_REPLY(priv,
					   "TXQ %d status %s (0x%08x) "
					   "rate_n_flags 0x%x retries %d\n",
					   txq_id,
					   iwl_get_tx_fail_reason(status),
					   status,
					   le32_to_cpu(tx_resp->rate_n_flags),
					   tx_resp->failure_frame);

				IWL_DEBUG_TX_REPLY(priv,
					   "FrameCnt = %d, idx=%d\n",
					   tx_resp->frame_count, cmd_index);
			पूर्ण

			/* check अगर BAR is needed */
			अगर (is_agg && !iwl_is_tx_success(status))
				info->flags |= IEEE80211_TX_STAT_AMPDU_NO_BACK;
			iwlagn_set_tx_status(priv, IEEE80211_SKB_CB(skb),
				     tx_resp);
			अगर (!is_agg)
				iwlagn_non_agg_tx_status(priv, ctx, hdr->addr1);

			मुक्तd++;
		पूर्ण

		अगर (tid != IWL_TID_NON_QOS) अणु
			priv->tid_data[sta_id][tid].next_reclaimed =
				next_reclaimed;
			IWL_DEBUG_TX_REPLY(priv, "Next reclaimed packet:%d\n",
					   next_reclaimed);
		पूर्ण

		अगर (!is_agg && मुक्तd != 1)
			IWL_ERR(priv, "Q: %d, freed %d\n", txq_id, मुक्तd);

		IWL_DEBUG_TX_REPLY(priv, "TXQ %d status %s (0x%08x)\n", txq_id,
				   iwl_get_tx_fail_reason(status), status);

		IWL_DEBUG_TX_REPLY(priv,
				   "\t\t\t\tinitial_rate 0x%x retries %d, idx=%d ssn=%d seq_ctl=0x%x\n",
				   le32_to_cpu(tx_resp->rate_n_flags),
				   tx_resp->failure_frame,
				   SEQ_TO_INDEX(sequence), ssn,
				   le16_to_cpu(tx_resp->seq_ctl));
	पूर्ण

	iwl_check_पात_status(priv, tx_resp->frame_count, status);
	spin_unlock_bh(&priv->sta_lock);

	जबतक (!skb_queue_empty(&skbs)) अणु
		skb = __skb_dequeue(&skbs);
		ieee80211_tx_status(priv->hw, skb);
	पूर्ण
पूर्ण

/*
 * iwlagn_rx_reply_compressed_ba - Handler क्रम REPLY_COMPRESSED_BA
 *
 * Handles block-acknowledge notअगरication from device, which reports success
 * of frames sent via aggregation.
 */
व्योम iwlagn_rx_reply_compressed_ba(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_compressed_ba_resp *ba_resp = (व्योम *)pkt->data;
	काष्ठा iwl_ht_agg *agg;
	काष्ठा sk_buff_head reclaimed_skbs;
	काष्ठा sk_buff *skb;
	पूर्णांक sta_id;
	पूर्णांक tid;
	पूर्णांक मुक्तd;

	/* "flow" corresponds to Tx queue */
	u16 scd_flow = le16_to_cpu(ba_resp->scd_flow);

	/* "ssn" is start of block-ack Tx winकरोw, corresponds to index
	 * (in Tx queue's circular buffer) of first TFD/frame in winकरोw */
	u16 ba_resp_scd_ssn = le16_to_cpu(ba_resp->scd_ssn);

	अगर (scd_flow >= priv->trans->trans_cfg->base_params->num_of_queues) अणु
		IWL_ERR(priv,
			"BUG_ON scd_flow is bigger than number of queues\n");
		वापस;
	पूर्ण

	sta_id = ba_resp->sta_id;
	tid = ba_resp->tid;
	agg = &priv->tid_data[sta_id][tid].agg;

	spin_lock_bh(&priv->sta_lock);

	अगर (unlikely(!agg->रुको_क्रम_ba)) अणु
		अगर (unlikely(ba_resp->biपंचांगap))
			IWL_ERR(priv, "Received BA when not expected\n");
		spin_unlock_bh(&priv->sta_lock);
		वापस;
	पूर्ण

	अगर (unlikely(scd_flow != agg->txq_id)) अणु
		/*
		 * FIXME: this is a uCode bug which need to be addressed,
		 * log the inक्रमmation and वापस क्रम now.
		 * Since it is can possibly happen very often and in order
		 * not to fill the syslog, करोn't use IWL_ERR or IWL_WARN
		 */
		IWL_DEBUG_TX_QUEUES(priv,
				    "Bad queue mapping txq_id=%d, agg_txq[sta:%d,tid:%d]=%d\n",
				    scd_flow, sta_id, tid, agg->txq_id);
		spin_unlock_bh(&priv->sta_lock);
		वापस;
	पूर्ण

	__skb_queue_head_init(&reclaimed_skbs);

	/* Release all TFDs beक्रमe the SSN, i.e. all TFDs in front of
	 * block-ack winकरोw (we assume that they've been successfully
	 * transmitted ... अगर not, it's too late anyway). */
	iwl_trans_reclaim(priv->trans, scd_flow, ba_resp_scd_ssn,
			  &reclaimed_skbs);

	IWL_DEBUG_TX_REPLY(priv, "REPLY_COMPRESSED_BA [%d] Received from %pM, "
			   "sta_id = %d\n",
			   agg->रुको_क्रम_ba,
			   (u8 *) &ba_resp->sta_addr_lo32,
			   ba_resp->sta_id);
	IWL_DEBUG_TX_REPLY(priv, "TID = %d, SeqCtl = %d, bitmap = 0x%llx, "
			   "scd_flow = %d, scd_ssn = %d sent:%d, acked:%d\n",
			   ba_resp->tid, le16_to_cpu(ba_resp->seq_ctl),
			   (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(ba_resp->biपंचांगap),
			   scd_flow, ba_resp_scd_ssn, ba_resp->txed,
			   ba_resp->txed_2_करोne);

	/* Mark that the expected block-ack response arrived */
	agg->रुको_क्रम_ba = false;

	/* Sanity check values reported by uCode */
	अगर (ba_resp->txed_2_करोne > ba_resp->txed) अणु
		IWL_DEBUG_TX_REPLY(priv,
			"bogus sent(%d) and ack(%d) count\n",
			ba_resp->txed, ba_resp->txed_2_करोne);
		/*
		 * set txed_2_करोne = txed,
		 * so it won't impact rate scale
		 */
		ba_resp->txed = ba_resp->txed_2_करोne;
	पूर्ण

	priv->tid_data[sta_id][tid].next_reclaimed = ba_resp_scd_ssn;

	iwlagn_check_ratid_empty(priv, sta_id, tid);
	मुक्तd = 0;

	skb_queue_walk(&reclaimed_skbs, skb) अणु
		काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		अगर (ieee80211_is_data_qos(hdr->frame_control))
			मुक्तd++;
		अन्यथा
			WARN_ON_ONCE(1);

		iwl_trans_मुक्त_tx_cmd(priv->trans, info->driver_data[1]);

		स_रखो(&info->status, 0, माप(info->status));
		/* Packet was transmitted successfully, failures come as single
		 * frames because beक्रमe failing a frame the firmware transmits
		 * it without aggregation at least once.
		 */
		info->flags |= IEEE80211_TX_STAT_ACK;

		अगर (मुक्तd == 1) अणु
			/* this is the first skb we deliver in this batch */
			/* put the rate scaling data there */
			info = IEEE80211_SKB_CB(skb);
			स_रखो(&info->status, 0, माप(info->status));
			info->flags |= IEEE80211_TX_STAT_AMPDU;
			info->status.ampdu_ack_len = ba_resp->txed_2_करोne;
			info->status.ampdu_len = ba_resp->txed;
			iwlagn_hwrate_to_tx_control(priv, agg->rate_n_flags,
						    info);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&priv->sta_lock);

	जबतक (!skb_queue_empty(&reclaimed_skbs)) अणु
		skb = __skb_dequeue(&reclaimed_skbs);
		ieee80211_tx_status(priv->hw, skb);
	पूर्ण
पूर्ण
