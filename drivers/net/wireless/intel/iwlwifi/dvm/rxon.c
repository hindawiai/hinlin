<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2015 Intel Deutschland GmbH
 *
 * Contact Inक्रमmation:
 * Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#समावेश <linux/etherdevice.h>
#समावेश "iwl-trans.h"
#समावेश "iwl-modparams.h"
#समावेश "dev.h"
#समावेश "agn.h"
#समावेश "calib.h"

/*
 * initialize rxon काष्ठाure with शेष values from eeprom
 */
व्योम iwl_connection_init_rx_config(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_rxon_context *ctx)
अणु
	स_रखो(&ctx->staging, 0, माप(ctx->staging));

	अगर (!ctx->vअगर) अणु
		ctx->staging.dev_type = ctx->unused_devtype;
	पूर्ण अन्यथा
	चयन (ctx->vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
		ctx->staging.dev_type = ctx->ap_devtype;
		अवरोध;

	हाल NL80211_IFTYPE_STATION:
		ctx->staging.dev_type = ctx->station_devtype;
		ctx->staging.filter_flags = RXON_FILTER_ACCEPT_GRP_MSK;
		अवरोध;

	हाल NL80211_IFTYPE_ADHOC:
		ctx->staging.dev_type = ctx->ibss_devtype;
		ctx->staging.flags = RXON_FLG_SHORT_PREAMBLE_MSK;
		ctx->staging.filter_flags = RXON_FILTER_BCON_AWARE_MSK |
						  RXON_FILTER_ACCEPT_GRP_MSK;
		अवरोध;

	हाल NL80211_IFTYPE_MONITOR:
		ctx->staging.dev_type = RXON_DEV_TYPE_SNIFFER;
		अवरोध;

	शेष:
		IWL_ERR(priv, "Unsupported interface type %d\n",
			ctx->vअगर->type);
		अवरोध;
	पूर्ण

#अगर 0
	/* TODO:  Figure out when लघु_preamble would be set and cache from
	 * that */
	अगर (!hw_to_local(priv->hw)->लघु_preamble)
		ctx->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;
	अन्यथा
		ctx->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
#पूर्ण_अगर

	ctx->staging.channel =
		cpu_to_le16(priv->hw->conf.chandef.chan->hw_value);
	priv->band = priv->hw->conf.chandef.chan->band;

	iwl_set_flags_क्रम_band(priv, ctx, priv->band, ctx->vअगर);

	/* clear both MIX and PURE40 mode flag */
	ctx->staging.flags &= ~(RXON_FLG_CHANNEL_MODE_MIXED |
					RXON_FLG_CHANNEL_MODE_PURE_40);
	अगर (ctx->vअगर)
		स_नकल(ctx->staging.node_addr, ctx->vअगर->addr, ETH_ALEN);

	ctx->staging.ofdm_ht_single_stream_basic_rates = 0xff;
	ctx->staging.ofdm_ht_dual_stream_basic_rates = 0xff;
	ctx->staging.ofdm_ht_triple_stream_basic_rates = 0xff;
पूर्ण

अटल पूर्णांक iwlagn_disable_bss(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rxon_context *ctx,
			      काष्ठा iwl_rxon_cmd *send)
अणु
	__le32 old_filter = send->filter_flags;
	पूर्णांक ret;

	send->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	ret = iwl_dvm_send_cmd_pdu(priv, ctx->rxon_cmd,
				0, माप(*send), send);

	send->filter_flags = old_filter;

	अगर (ret)
		IWL_DEBUG_QUIET_RFKILL(priv,
			"Error clearing ASSOC_MSK on BSS (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iwlagn_disable_pan(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rxon_context *ctx,
			      काष्ठा iwl_rxon_cmd *send)
अणु
	काष्ठा iwl_notअगरication_रुको disable_रुको;
	__le32 old_filter = send->filter_flags;
	u8 old_dev_type = send->dev_type;
	पूर्णांक ret;
	अटल स्थिर u16 deactivate_cmd[] = अणु
		REPLY_WIPAN_DEACTIVATION_COMPLETE
	पूर्ण;

	iwl_init_notअगरication_रुको(&priv->notअगर_रुको, &disable_रुको,
				   deactivate_cmd, ARRAY_SIZE(deactivate_cmd),
				   शून्य, शून्य);

	send->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	send->dev_type = RXON_DEV_TYPE_P2P;
	ret = iwl_dvm_send_cmd_pdu(priv, ctx->rxon_cmd,
				0, माप(*send), send);

	send->filter_flags = old_filter;
	send->dev_type = old_dev_type;

	अगर (ret) अणु
		IWL_ERR(priv, "Error disabling PAN (%d)\n", ret);
		iwl_हटाओ_notअगरication(&priv->notअगर_रुको, &disable_रुको);
	पूर्ण अन्यथा अणु
		ret = iwl_रुको_notअगरication(&priv->notअगर_रुको,
					    &disable_रुको, HZ);
		अगर (ret)
			IWL_ERR(priv, "Timed out waiting for PAN disable\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iwlagn_disconn_pan(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rxon_context *ctx,
			      काष्ठा iwl_rxon_cmd *send)
अणु
	__le32 old_filter = send->filter_flags;
	पूर्णांक ret;

	send->filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	ret = iwl_dvm_send_cmd_pdu(priv, ctx->rxon_cmd, 0,
				माप(*send), send);

	send->filter_flags = old_filter;

	वापस ret;
पूर्ण

अटल व्योम iwlagn_update_qos(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rxon_context *ctx)
अणु
	पूर्णांक ret;

	अगर (!ctx->is_active)
		वापस;

	ctx->qos_data.def_qos_parm.qos_flags = 0;

	अगर (ctx->qos_data.qos_active)
		ctx->qos_data.def_qos_parm.qos_flags |=
			QOS_PARAM_FLG_UPDATE_EDCA_MSK;

	अगर (ctx->ht.enabled)
		ctx->qos_data.def_qos_parm.qos_flags |= QOS_PARAM_FLG_TGN_MSK;

	IWL_DEBUG_INFO(priv, "send QoS cmd with Qos active=%d FLAGS=0x%X\n",
		      ctx->qos_data.qos_active,
		      ctx->qos_data.def_qos_parm.qos_flags);

	ret = iwl_dvm_send_cmd_pdu(priv, ctx->qos_cmd, 0,
			       माप(काष्ठा iwl_qosparam_cmd),
			       &ctx->qos_data.def_qos_parm);
	अगर (ret)
		IWL_DEBUG_QUIET_RFKILL(priv, "Failed to update QoS\n");
पूर्ण

अटल पूर्णांक iwlagn_update_beacon(काष्ठा iwl_priv *priv,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	lockdep_निश्चित_held(&priv->mutex);

	dev_kमुक्त_skb(priv->beacon_skb);
	priv->beacon_skb = ieee80211_beacon_get(priv->hw, vअगर);
	अगर (!priv->beacon_skb)
		वापस -ENOMEM;
	वापस iwlagn_send_beacon_cmd(priv);
पूर्ण

अटल पूर्णांक iwlagn_send_rxon_assoc(काष्ठा iwl_priv *priv,
				  काष्ठा iwl_rxon_context *ctx)
अणु
	पूर्णांक ret = 0;
	काष्ठा iwl_rxon_assoc_cmd rxon_assoc;
	स्थिर काष्ठा iwl_rxon_cmd *rxon1 = &ctx->staging;
	स्थिर काष्ठा iwl_rxon_cmd *rxon2 = &ctx->active;

	अगर ((rxon1->flags == rxon2->flags) &&
	    (rxon1->filter_flags == rxon2->filter_flags) &&
	    (rxon1->cck_basic_rates == rxon2->cck_basic_rates) &&
	    (rxon1->ofdm_ht_single_stream_basic_rates ==
	     rxon2->ofdm_ht_single_stream_basic_rates) &&
	    (rxon1->ofdm_ht_dual_stream_basic_rates ==
	     rxon2->ofdm_ht_dual_stream_basic_rates) &&
	    (rxon1->ofdm_ht_triple_stream_basic_rates ==
	     rxon2->ofdm_ht_triple_stream_basic_rates) &&
	    (rxon1->acquisition_data == rxon2->acquisition_data) &&
	    (rxon1->rx_chain == rxon2->rx_chain) &&
	    (rxon1->ofdm_basic_rates == rxon2->ofdm_basic_rates)) अणु
		IWL_DEBUG_INFO(priv, "Using current RXON_ASSOC.  Not resending.\n");
		वापस 0;
	पूर्ण

	rxon_assoc.flags = ctx->staging.flags;
	rxon_assoc.filter_flags = ctx->staging.filter_flags;
	rxon_assoc.ofdm_basic_rates = ctx->staging.ofdm_basic_rates;
	rxon_assoc.cck_basic_rates = ctx->staging.cck_basic_rates;
	rxon_assoc.reserved1 = 0;
	rxon_assoc.reserved2 = 0;
	rxon_assoc.reserved3 = 0;
	rxon_assoc.ofdm_ht_single_stream_basic_rates =
	    ctx->staging.ofdm_ht_single_stream_basic_rates;
	rxon_assoc.ofdm_ht_dual_stream_basic_rates =
	    ctx->staging.ofdm_ht_dual_stream_basic_rates;
	rxon_assoc.rx_chain_select_flags = ctx->staging.rx_chain;
	rxon_assoc.ofdm_ht_triple_stream_basic_rates =
		 ctx->staging.ofdm_ht_triple_stream_basic_rates;
	rxon_assoc.acquisition_data = ctx->staging.acquisition_data;

	ret = iwl_dvm_send_cmd_pdu(priv, ctx->rxon_assoc_cmd,
				CMD_ASYNC, माप(rxon_assoc), &rxon_assoc);
	वापस ret;
पूर्ण

अटल u16 iwl_adjust_beacon_पूर्णांकerval(u16 beacon_val, u16 max_beacon_val)
अणु
	u16 new_val;
	u16 beacon_factor;

	/*
	 * If mac80211 hasn't given us a beacon पूर्णांकerval, program
	 * the शेष पूर्णांकo the device (not checking this here
	 * would cause the adjusपंचांगent below to वापस the maximum
	 * value, which may अवरोध PAN.)
	 */
	अगर (!beacon_val)
		वापस DEFAULT_BEACON_INTERVAL;

	/*
	 * If the beacon पूर्णांकerval we obtained from the peer
	 * is too large, we'll have to wake up more often
	 * (and in IBSS हाल, we'll beacon too much)
	 *
	 * For example, अगर max_beacon_val is 4096, and the
	 * requested beacon पूर्णांकerval is 7000, we'll have to
	 * use 3500 to be able to wake up on the beacons.
	 *
	 * This could badly influence beacon detection stats.
	 */

	beacon_factor = (beacon_val + max_beacon_val) / max_beacon_val;
	new_val = beacon_val / beacon_factor;

	अगर (!new_val)
		new_val = max_beacon_val;

	वापस new_val;
पूर्ण

अटल पूर्णांक iwl_send_rxon_timing(काष्ठा iwl_priv *priv,
				काष्ठा iwl_rxon_context *ctx)
अणु
	u64 tsf;
	s32 पूर्णांकerval_पंचांग, rem;
	काष्ठा ieee80211_conf *conf = शून्य;
	u16 beacon_पूर्णांक;
	काष्ठा ieee80211_vअगर *vअगर = ctx->vअगर;

	conf = &priv->hw->conf;

	lockdep_निश्चित_held(&priv->mutex);

	स_रखो(&ctx->timing, 0, माप(काष्ठा iwl_rxon_समय_cmd));

	ctx->timing.बारtamp = cpu_to_le64(priv->बारtamp);
	ctx->timing.listen_पूर्णांकerval = cpu_to_le16(conf->listen_पूर्णांकerval);

	beacon_पूर्णांक = vअगर ? vअगर->bss_conf.beacon_पूर्णांक : 0;

	/*
	 * TODO: For IBSS we need to get atim_winकरोw from mac80211,
	 *	 क्रम now just always use 0
	 */
	ctx->timing.atim_winकरोw = 0;

	अगर (ctx->ctxid == IWL_RXON_CTX_PAN &&
	    (!ctx->vअगर || ctx->vअगर->type != NL80211_IFTYPE_STATION) &&
	    iwl_is_associated(priv, IWL_RXON_CTX_BSS) &&
	    priv->contexts[IWL_RXON_CTX_BSS].vअगर &&
	    priv->contexts[IWL_RXON_CTX_BSS].vअगर->bss_conf.beacon_पूर्णांक) अणु
		ctx->timing.beacon_पूर्णांकerval =
			priv->contexts[IWL_RXON_CTX_BSS].timing.beacon_पूर्णांकerval;
		beacon_पूर्णांक = le16_to_cpu(ctx->timing.beacon_पूर्णांकerval);
	पूर्ण अन्यथा अगर (ctx->ctxid == IWL_RXON_CTX_BSS &&
		   iwl_is_associated(priv, IWL_RXON_CTX_PAN) &&
		   priv->contexts[IWL_RXON_CTX_PAN].vअगर &&
		   priv->contexts[IWL_RXON_CTX_PAN].vअगर->bss_conf.beacon_पूर्णांक &&
		   (!iwl_is_associated_ctx(ctx) || !ctx->vअगर ||
		    !ctx->vअगर->bss_conf.beacon_पूर्णांक)) अणु
		ctx->timing.beacon_पूर्णांकerval =
			priv->contexts[IWL_RXON_CTX_PAN].timing.beacon_पूर्णांकerval;
		beacon_पूर्णांक = le16_to_cpu(ctx->timing.beacon_पूर्णांकerval);
	पूर्ण अन्यथा अणु
		beacon_पूर्णांक = iwl_adjust_beacon_पूर्णांकerval(beacon_पूर्णांक,
			IWL_MAX_UCODE_BEACON_INTERVAL * TIME_UNIT);
		ctx->timing.beacon_पूर्णांकerval = cpu_to_le16(beacon_पूर्णांक);
	पूर्ण

	ctx->beacon_पूर्णांक = beacon_पूर्णांक;

	tsf = priv->बारtamp; /* tsf is modअगरed by करो_भाग: copy it */
	पूर्णांकerval_पंचांग = beacon_पूर्णांक * TIME_UNIT;
	rem = करो_भाग(tsf, पूर्णांकerval_पंचांग);
	ctx->timing.beacon_init_val = cpu_to_le32(पूर्णांकerval_पंचांग - rem);

	ctx->timing.dtim_period = vअगर ? (vअगर->bss_conf.dtim_period ?: 1) : 1;

	IWL_DEBUG_ASSOC(priv,
			"beacon interval %d beacon timer %d beacon tim %d\n",
			le16_to_cpu(ctx->timing.beacon_पूर्णांकerval),
			le32_to_cpu(ctx->timing.beacon_init_val),
			le16_to_cpu(ctx->timing.atim_winकरोw));

	वापस iwl_dvm_send_cmd_pdu(priv, ctx->rxon_timing_cmd,
				0, माप(ctx->timing), &ctx->timing);
पूर्ण

अटल पूर्णांक iwlagn_rxon_disconn(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rxon_context *ctx)
अणु
	पूर्णांक ret;
	काष्ठा iwl_rxon_cmd *active = (व्योम *)&ctx->active;

	अगर (ctx->ctxid == IWL_RXON_CTX_BSS) अणु
		ret = iwlagn_disable_bss(priv, ctx, &ctx->staging);
	पूर्ण अन्यथा अणु
		ret = iwlagn_disable_pan(priv, ctx, &ctx->staging);
		अगर (ret)
			वापस ret;
		अगर (ctx->vअगर) अणु
			ret = iwl_send_rxon_timing(priv, ctx);
			अगर (ret) अणु
				IWL_ERR(priv, "Failed to send timing (%d)!\n", ret);
				वापस ret;
			पूर्ण
			ret = iwlagn_disconn_pan(priv, ctx, &ctx->staging);
		पूर्ण
	पूर्ण
	अगर (ret)
		वापस ret;

	/*
	 * Un-assoc RXON clears the station table and WEP
	 * keys, so we have to restore those afterwards.
	 */
	iwl_clear_ucode_stations(priv, ctx);
	/* update -- might need P2P now */
	iwl_update_bcast_station(priv, ctx);
	iwl_restore_stations(priv, ctx);
	ret = iwl_restore_शेष_wep_keys(priv, ctx);
	अगर (ret) अणु
		IWL_ERR(priv, "Failed to restore WEP keys (%d)\n", ret);
		वापस ret;
	पूर्ण

	स_नकल(active, &ctx->staging, माप(*active));
	वापस 0;
पूर्ण

अटल पूर्णांक iwl_set_tx_घातer(काष्ठा iwl_priv *priv, s8 tx_घातer, bool क्रमce)
अणु
	पूर्णांक ret;
	s8 prev_tx_घातer;
	bool defer;
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];

	अगर (priv->calib_disabled & IWL_TX_POWER_CALIB_DISABLED)
		वापस 0;

	lockdep_निश्चित_held(&priv->mutex);

	अगर (priv->tx_घातer_user_lmt == tx_घातer && !क्रमce)
		वापस 0;

	अगर (tx_घातer < IWLAGN_TX_POWER_TARGET_POWER_MIN) अणु
		IWL_WARN(priv,
			 "Requested user TXPOWER %d below lower limit %d.\n",
			 tx_घातer,
			 IWLAGN_TX_POWER_TARGET_POWER_MIN);
		वापस -EINVAL;
	पूर्ण

	अगर (tx_घातer > DIV_ROUND_UP(priv->nvm_data->max_tx_pwr_half_dbm, 2)) अणु
		IWL_WARN(priv,
			"Requested user TXPOWER %d above upper limit %d.\n",
			 tx_घातer, priv->nvm_data->max_tx_pwr_half_dbm);
		वापस -EINVAL;
	पूर्ण

	अगर (!iwl_is_पढ़ोy_rf(priv))
		वापस -EIO;

	/* scan complete and commit_rxon use tx_घातer_next value,
	 * it always need to be updated क्रम newest request */
	priv->tx_घातer_next = tx_घातer;

	/* करो not set tx घातer when scanning or channel changing */
	defer = test_bit(STATUS_SCANNING, &priv->status) ||
		स_भेद(&ctx->active, &ctx->staging, माप(ctx->staging));
	अगर (defer && !क्रमce) अणु
		IWL_DEBUG_INFO(priv, "Deferring tx power set\n");
		वापस 0;
	पूर्ण

	prev_tx_घातer = priv->tx_घातer_user_lmt;
	priv->tx_घातer_user_lmt = tx_घातer;

	ret = iwlagn_send_tx_घातer(priv);

	/* अगर fail to set tx_घातer, restore the orig. tx घातer */
	अगर (ret) अणु
		priv->tx_घातer_user_lmt = prev_tx_घातer;
		priv->tx_घातer_next = prev_tx_घातer;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक iwlagn_rxon_connect(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rxon_context *ctx)
अणु
	पूर्णांक ret;
	काष्ठा iwl_rxon_cmd *active = (व्योम *)&ctx->active;

	/* RXON timing must be beक्रमe associated RXON */
	अगर (ctx->ctxid == IWL_RXON_CTX_BSS) अणु
		ret = iwl_send_rxon_timing(priv, ctx);
		अगर (ret) अणु
			IWL_ERR(priv, "Failed to send timing (%d)!\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण
	/* QoS info may be cleared by previous un-assoc RXON */
	iwlagn_update_qos(priv, ctx);

	/*
	 * We'll run पूर्णांकo this code path when beaconing is
	 * enabled, but then we also need to send the beacon
	 * to the device.
	 */
	अगर (ctx->vअगर && (ctx->vअगर->type == NL80211_IFTYPE_AP)) अणु
		ret = iwlagn_update_beacon(priv, ctx->vअगर);
		अगर (ret) अणु
			IWL_ERR(priv,
				"Error sending required beacon (%d)!\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	priv->start_calib = 0;
	/*
	 * Apply the new configuration.
	 *
	 * Associated RXON करोesn't clear the station table in uCode,
	 * so we करोn't need to restore stations etc. after this.
	 */
	ret = iwl_dvm_send_cmd_pdu(priv, ctx->rxon_cmd, 0,
		      माप(काष्ठा iwl_rxon_cmd), &ctx->staging);
	अगर (ret) अणु
		IWL_ERR(priv, "Error setting new RXON (%d)\n", ret);
		वापस ret;
	पूर्ण
	स_नकल(active, &ctx->staging, माप(*active));

	/* IBSS beacon needs to be sent after setting assoc */
	अगर (ctx->vअगर && (ctx->vअगर->type == NL80211_IFTYPE_ADHOC))
		अगर (iwlagn_update_beacon(priv, ctx->vअगर))
			IWL_ERR(priv, "Error sending IBSS beacon\n");
	iwl_init_sensitivity(priv);

	/*
	 * If we issue a new RXON command which required a tune then
	 * we must send a new TXPOWER command or we won't be able to
	 * Tx any frames.
	 *
	 * It's expected we set घातer here अगर channel is changing.
	 */
	ret = iwl_set_tx_घातer(priv, priv->tx_घातer_next, true);
	अगर (ret) अणु
		IWL_ERR(priv, "Error sending TX power (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwlagn_set_pan_params(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_wipan_params_cmd cmd;
	काष्ठा iwl_rxon_context *ctx_bss, *ctx_pan;
	पूर्णांक slot0 = 300, slot1 = 0;
	पूर्णांक ret;

	अगर (priv->valid_contexts == BIT(IWL_RXON_CTX_BSS))
		वापस 0;

	BUILD_BUG_ON(NUM_IWL_RXON_CTX != 2);

	lockdep_निश्चित_held(&priv->mutex);

	ctx_bss = &priv->contexts[IWL_RXON_CTX_BSS];
	ctx_pan = &priv->contexts[IWL_RXON_CTX_PAN];

	/*
	 * If the PAN context is inactive, then we करोn't need
	 * to update the PAN parameters, the last thing we'll
	 * have करोne beक्रमe it goes inactive is making the PAN
	 * parameters be WLAN-only.
	 */
	अगर (!ctx_pan->is_active)
		वापस 0;

	स_रखो(&cmd, 0, माप(cmd));

	/* only 2 slots are currently allowed */
	cmd.num_slots = 2;

	cmd.slots[0].type = 0; /* BSS */
	cmd.slots[1].type = 1; /* PAN */

	अगर (ctx_bss->vअगर && ctx_pan->vअगर) अणु
		पूर्णांक bcnपूर्णांक = ctx_pan->beacon_पूर्णांक;
		पूर्णांक dtim = ctx_pan->vअगर->bss_conf.dtim_period ?: 1;

		/* should be set, but seems unused?? */
		cmd.flags |= cpu_to_le16(IWL_WIPAN_PARAMS_FLG_SLOTTED_MODE);

		अगर (ctx_pan->vअगर->type == NL80211_IFTYPE_AP &&
		    bcnपूर्णांक &&
		    bcnपूर्णांक != ctx_bss->beacon_पूर्णांक) अणु
			IWL_ERR(priv,
				"beacon intervals don't match (%d, %d)\n",
				ctx_bss->beacon_पूर्णांक, ctx_pan->beacon_पूर्णांक);
		पूर्ण अन्यथा
			bcnपूर्णांक = max_t(पूर्णांक, bcnपूर्णांक,
				       ctx_bss->beacon_पूर्णांक);
		अगर (!bcnपूर्णांक)
			bcnपूर्णांक = DEFAULT_BEACON_INTERVAL;
		slot0 = bcnपूर्णांक / 2;
		slot1 = bcnपूर्णांक - slot0;

		अगर (test_bit(STATUS_SCAN_HW, &priv->status) ||
		    (!ctx_bss->vअगर->bss_conf.idle &&
		     !ctx_bss->vअगर->bss_conf.assoc)) अणु
			slot0 = dtim * bcnपूर्णांक * 3 - IWL_MIN_SLOT_TIME;
			slot1 = IWL_MIN_SLOT_TIME;
		पूर्ण अन्यथा अगर (!ctx_pan->vअगर->bss_conf.idle &&
			   !ctx_pan->vअगर->bss_conf.assoc) अणु
			slot1 = dtim * bcnपूर्णांक * 3 - IWL_MIN_SLOT_TIME;
			slot0 = IWL_MIN_SLOT_TIME;
		पूर्ण
	पूर्ण अन्यथा अगर (ctx_pan->vअगर) अणु
		slot0 = 0;
		slot1 = max_t(पूर्णांक, 1, ctx_pan->vअगर->bss_conf.dtim_period) *
					ctx_pan->beacon_पूर्णांक;
		slot1 = max_t(पूर्णांक, DEFAULT_BEACON_INTERVAL, slot1);

		अगर (test_bit(STATUS_SCAN_HW, &priv->status)) अणु
			slot0 = slot1 * 3 - IWL_MIN_SLOT_TIME;
			slot1 = IWL_MIN_SLOT_TIME;
		पूर्ण
	पूर्ण

	cmd.slots[0].width = cpu_to_le16(slot0);
	cmd.slots[1].width = cpu_to_le16(slot1);

	ret = iwl_dvm_send_cmd_pdu(priv, REPLY_WIPAN_PARAMS, 0,
			माप(cmd), &cmd);
	अगर (ret)
		IWL_ERR(priv, "Error setting PAN parameters (%d)\n", ret);

	वापस ret;
पूर्ण

अटल व्योम _iwl_set_rxon_ht(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_ht_config *ht_conf,
			     काष्ठा iwl_rxon_context *ctx)
अणु
	काष्ठा iwl_rxon_cmd *rxon = &ctx->staging;

	अगर (!ctx->ht.enabled) अणु
		rxon->flags &= ~(RXON_FLG_CHANNEL_MODE_MSK |
			RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK |
			RXON_FLG_HT40_PROT_MSK |
			RXON_FLG_HT_PROT_MSK);
		वापस;
	पूर्ण

	/* FIXME: अगर the definition of ht.protection changed, the "translation"
	 * will be needed क्रम rxon->flags
	 */
	rxon->flags |= cpu_to_le32(ctx->ht.protection <<
				   RXON_FLG_HT_OPERATING_MODE_POS);

	/* Set up channel bandwidth:
	 * 20 MHz only, 20/40 mixed or pure 40 अगर ht40 ok */
	/* clear the HT channel mode beक्रमe set the mode */
	rxon->flags &= ~(RXON_FLG_CHANNEL_MODE_MSK |
			 RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK);
	अगर (iwl_is_ht40_tx_allowed(priv, ctx, शून्य)) अणु
		/* pure ht40 */
		अगर (ctx->ht.protection ==
		    IEEE80211_HT_OP_MODE_PROTECTION_20MHZ) अणु
			rxon->flags |= RXON_FLG_CHANNEL_MODE_PURE_40;
			/*
			 * Note: control channel is opposite of extension
			 * channel
			 */
			चयन (ctx->ht.extension_chan_offset) अणु
			हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				rxon->flags &=
					~RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				अवरोध;
			हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				rxon->flags |=
					RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Note: control channel is opposite of extension
			 * channel
			 */
			चयन (ctx->ht.extension_chan_offset) अणु
			हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				rxon->flags &=
					~(RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK);
				rxon->flags |= RXON_FLG_CHANNEL_MODE_MIXED;
				अवरोध;
			हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				rxon->flags |= RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				rxon->flags |= RXON_FLG_CHANNEL_MODE_MIXED;
				अवरोध;
			हाल IEEE80211_HT_PARAM_CHA_SEC_NONE:
			शेष:
				/*
				 * channel location only valid अगर in Mixed
				 * mode
				 */
				IWL_ERR(priv,
					"invalid extension channel offset\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rxon->flags |= RXON_FLG_CHANNEL_MODE_LEGACY;
	पूर्ण

	iwlagn_set_rxon_chain(priv, ctx);

	IWL_DEBUG_ASSOC(priv, "rxon flags 0x%X operation mode :0x%X "
			"extension channel offset 0x%x\n",
			le32_to_cpu(rxon->flags), ctx->ht.protection,
			ctx->ht.extension_chan_offset);
पूर्ण

व्योम iwl_set_rxon_ht(काष्ठा iwl_priv *priv, काष्ठा iwl_ht_config *ht_conf)
अणु
	काष्ठा iwl_rxon_context *ctx;

	क्रम_each_context(priv, ctx)
		_iwl_set_rxon_ht(priv, ht_conf, ctx);
पूर्ण

/*
 * iwl_set_rxon_channel - Set the band and channel values in staging RXON
 * @ch: requested channel as a poपूर्णांकer to काष्ठा ieee80211_channel

 * NOTE:  Does not commit to the hardware; it sets appropriate bit fields
 * in the staging RXON flag काष्ठाure based on the ch->band
 */
व्योम iwl_set_rxon_channel(काष्ठा iwl_priv *priv, काष्ठा ieee80211_channel *ch,
			 काष्ठा iwl_rxon_context *ctx)
अणु
	क्रमागत nl80211_band band = ch->band;
	u16 channel = ch->hw_value;

	अगर ((le16_to_cpu(ctx->staging.channel) == channel) &&
	    (priv->band == band))
		वापस;

	ctx->staging.channel = cpu_to_le16(channel);
	अगर (band == NL80211_BAND_5GHZ)
		ctx->staging.flags &= ~RXON_FLG_BAND_24G_MSK;
	अन्यथा
		ctx->staging.flags |= RXON_FLG_BAND_24G_MSK;

	priv->band = band;

	IWL_DEBUG_INFO(priv, "Staging channel set to %d [%d]\n", channel, band);

पूर्ण

व्योम iwl_set_flags_क्रम_band(काष्ठा iwl_priv *priv,
			    काष्ठा iwl_rxon_context *ctx,
			    क्रमागत nl80211_band band,
			    काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (band == NL80211_BAND_5GHZ) अणु
		ctx->staging.flags &=
		    ~(RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK
		      | RXON_FLG_CCK_MSK);
		ctx->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
	पूर्ण अन्यथा अणु
		/* Copied from iwl_post_associate() */
		अगर (vअगर && vअगर->bss_conf.use_लघु_slot)
			ctx->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
		अन्यथा
			ctx->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;

		ctx->staging.flags |= RXON_FLG_BAND_24G_MSK;
		ctx->staging.flags |= RXON_FLG_AUTO_DETECT_MSK;
		ctx->staging.flags &= ~RXON_FLG_CCK_MSK;
	पूर्ण
पूर्ण

अटल व्योम iwl_set_rxon_hwcrypto(काष्ठा iwl_priv *priv,
				  काष्ठा iwl_rxon_context *ctx, पूर्णांक hw_decrypt)
अणु
	काष्ठा iwl_rxon_cmd *rxon = &ctx->staging;

	अगर (hw_decrypt)
		rxon->filter_flags &= ~RXON_FILTER_DIS_DECRYPT_MSK;
	अन्यथा
		rxon->filter_flags |= RXON_FILTER_DIS_DECRYPT_MSK;

पूर्ण

/* validate RXON काष्ठाure is valid */
अटल पूर्णांक iwl_check_rxon_cmd(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rxon_context *ctx)
अणु
	काष्ठा iwl_rxon_cmd *rxon = &ctx->staging;
	u32 errors = 0;

	अगर (rxon->flags & RXON_FLG_BAND_24G_MSK) अणु
		अगर (rxon->flags & RXON_FLG_TGJ_NARROW_BAND_MSK) अणु
			IWL_WARN(priv, "check 2.4G: wrong narrow\n");
			errors |= BIT(0);
		पूर्ण
		अगर (rxon->flags & RXON_FLG_RADAR_DETECT_MSK) अणु
			IWL_WARN(priv, "check 2.4G: wrong radar\n");
			errors |= BIT(1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(rxon->flags & RXON_FLG_SHORT_SLOT_MSK)) अणु
			IWL_WARN(priv, "check 5.2G: not short slot!\n");
			errors |= BIT(2);
		पूर्ण
		अगर (rxon->flags & RXON_FLG_CCK_MSK) अणु
			IWL_WARN(priv, "check 5.2G: CCK!\n");
			errors |= BIT(3);
		पूर्ण
	पूर्ण
	अगर ((rxon->node_addr[0] | rxon->bssid_addr[0]) & 0x1) अणु
		IWL_WARN(priv, "mac/bssid mcast!\n");
		errors |= BIT(4);
	पूर्ण

	/* make sure basic rates 6Mbps and 1Mbps are supported */
	अगर ((rxon->ofdm_basic_rates & IWL_RATE_6M_MASK) == 0 &&
	    (rxon->cck_basic_rates & IWL_RATE_1M_MASK) == 0) अणु
		IWL_WARN(priv, "neither 1 nor 6 are basic\n");
		errors |= BIT(5);
	पूर्ण

	अगर (le16_to_cpu(rxon->assoc_id) > 2007) अणु
		IWL_WARN(priv, "aid > 2007\n");
		errors |= BIT(6);
	पूर्ण

	अगर ((rxon->flags & (RXON_FLG_CCK_MSK | RXON_FLG_SHORT_SLOT_MSK))
			== (RXON_FLG_CCK_MSK | RXON_FLG_SHORT_SLOT_MSK)) अणु
		IWL_WARN(priv, "CCK and short slot\n");
		errors |= BIT(7);
	पूर्ण

	अगर ((rxon->flags & (RXON_FLG_CCK_MSK | RXON_FLG_AUTO_DETECT_MSK))
			== (RXON_FLG_CCK_MSK | RXON_FLG_AUTO_DETECT_MSK)) अणु
		IWL_WARN(priv, "CCK and auto detect\n");
		errors |= BIT(8);
	पूर्ण

	अगर ((rxon->flags & (RXON_FLG_AUTO_DETECT_MSK |
			    RXON_FLG_TGG_PROTECT_MSK)) ==
			    RXON_FLG_TGG_PROTECT_MSK) अणु
		IWL_WARN(priv, "TGg but no auto-detect\n");
		errors |= BIT(9);
	पूर्ण

	अगर (rxon->channel == 0) अणु
		IWL_WARN(priv, "zero channel is invalid\n");
		errors |= BIT(10);
	पूर्ण

	WARN(errors, "Invalid RXON (%#x), channel %d",
	     errors, le16_to_cpu(rxon->channel));

	वापस errors ? -EINVAL : 0;
पूर्ण

/*
 * iwl_full_rxon_required - check अगर full RXON (vs RXON_ASSOC) cmd is needed
 * @priv: staging_rxon is compared to active_rxon
 *
 * If the RXON काष्ठाure is changing enough to require a new tune,
 * or is clearing the RXON_FILTER_ASSOC_MSK, then वापस 1 to indicate that
 * a new tune (full RXON command, rather than RXON_ASSOC cmd) is required.
 */
अटल पूर्णांक iwl_full_rxon_required(काष्ठा iwl_priv *priv,
				  काष्ठा iwl_rxon_context *ctx)
अणु
	स्थिर काष्ठा iwl_rxon_cmd *staging = &ctx->staging;
	स्थिर काष्ठा iwl_rxon_cmd *active = &ctx->active;

#घोषणा CHK(cond)							\
	अगर ((cond)) अणु							\
		IWL_DEBUG_INFO(priv, "need full RXON - " #cond "\n");	\
		वापस 1;						\
	पूर्ण

#घोषणा CHK_NEQ(c1, c2)						\
	अगर ((c1) != (c2)) अणु					\
		IWL_DEBUG_INFO(priv, "need full RXON - "	\
			       #c1 " != " #c2 " - %d != %d\n",	\
			       (c1), (c2));			\
		वापस 1;					\
	पूर्ण

	/* These items are only settable from the full RXON command */
	CHK(!iwl_is_associated_ctx(ctx));
	CHK(!ether_addr_equal(staging->bssid_addr, active->bssid_addr));
	CHK(!ether_addr_equal(staging->node_addr, active->node_addr));
	CHK(!ether_addr_equal(staging->wlap_bssid_addr,
			      active->wlap_bssid_addr));
	CHK_NEQ(staging->dev_type, active->dev_type);
	CHK_NEQ(staging->channel, active->channel);
	CHK_NEQ(staging->air_propagation, active->air_propagation);
	CHK_NEQ(staging->ofdm_ht_single_stream_basic_rates,
		active->ofdm_ht_single_stream_basic_rates);
	CHK_NEQ(staging->ofdm_ht_dual_stream_basic_rates,
		active->ofdm_ht_dual_stream_basic_rates);
	CHK_NEQ(staging->ofdm_ht_triple_stream_basic_rates,
		active->ofdm_ht_triple_stream_basic_rates);
	CHK_NEQ(staging->assoc_id, active->assoc_id);

	/* flags, filter_flags, ofdm_basic_rates, and cck_basic_rates can
	 * be updated with the RXON_ASSOC command -- however only some
	 * flag transitions are allowed using RXON_ASSOC */

	/* Check अगर we are not चयनing bands */
	CHK_NEQ(staging->flags & RXON_FLG_BAND_24G_MSK,
		active->flags & RXON_FLG_BAND_24G_MSK);

	/* Check अगर we are चयनing association toggle */
	CHK_NEQ(staging->filter_flags & RXON_FILTER_ASSOC_MSK,
		active->filter_flags & RXON_FILTER_ASSOC_MSK);

#अघोषित CHK
#अघोषित CHK_NEQ

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
व्योम iwl_prपूर्णांक_rx_config_cmd(काष्ठा iwl_priv *priv,
			     क्रमागत iwl_rxon_context_id ctxid)
अणु
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[ctxid];
	काष्ठा iwl_rxon_cmd *rxon = &ctx->staging;

	IWL_DEBUG_RADIO(priv, "RX CONFIG:\n");
	iwl_prपूर्णांक_hex_dump(priv, IWL_DL_RADIO, (u8 *) rxon, माप(*rxon));
	IWL_DEBUG_RADIO(priv, "u16 channel: 0x%x\n",
			le16_to_cpu(rxon->channel));
	IWL_DEBUG_RADIO(priv, "u32 flags: 0x%08X\n",
			le32_to_cpu(rxon->flags));
	IWL_DEBUG_RADIO(priv, "u32 filter_flags: 0x%08x\n",
			le32_to_cpu(rxon->filter_flags));
	IWL_DEBUG_RADIO(priv, "u8 dev_type: 0x%x\n", rxon->dev_type);
	IWL_DEBUG_RADIO(priv, "u8 ofdm_basic_rates: 0x%02x\n",
			rxon->ofdm_basic_rates);
	IWL_DEBUG_RADIO(priv, "u8 cck_basic_rates: 0x%02x\n",
			rxon->cck_basic_rates);
	IWL_DEBUG_RADIO(priv, "u8[6] node_addr: %pM\n", rxon->node_addr);
	IWL_DEBUG_RADIO(priv, "u8[6] bssid_addr: %pM\n", rxon->bssid_addr);
	IWL_DEBUG_RADIO(priv, "u16 assoc_id: 0x%x\n",
			le16_to_cpu(rxon->assoc_id));
पूर्ण
#पूर्ण_अगर

अटल व्योम iwl_calc_basic_rates(काष्ठा iwl_priv *priv,
				 काष्ठा iwl_rxon_context *ctx)
अणु
	पूर्णांक lowest_present_ofdm = 100;
	पूर्णांक lowest_present_cck = 100;
	u8 cck = 0;
	u8 ofdm = 0;

	अगर (ctx->vअगर) अणु
		काष्ठा ieee80211_supported_band *sband;
		अचिन्हित दीर्घ basic = ctx->vअगर->bss_conf.basic_rates;
		पूर्णांक i;

		sband = priv->hw->wiphy->bands[priv->hw->conf.chandef.chan->band];

		क्रम_each_set_bit(i, &basic, BITS_PER_LONG) अणु
			पूर्णांक hw = sband->bitrates[i].hw_value;
			अगर (hw >= IWL_FIRST_OFDM_RATE) अणु
				ofdm |= BIT(hw - IWL_FIRST_OFDM_RATE);
				अगर (lowest_present_ofdm > hw)
					lowest_present_ofdm = hw;
			पूर्ण अन्यथा अणु
				BUILD_BUG_ON(IWL_FIRST_CCK_RATE != 0);

				cck |= BIT(hw);
				अगर (lowest_present_cck > hw)
					lowest_present_cck = hw;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Now we've got the basic rates as biपंचांगaps in the ofdm and cck
	 * variables. This isn't sufficient though, as there might not
	 * be all the right rates in the biपंचांगap. E.g. अगर the only basic
	 * rates are 5.5 Mbps and 11 Mbps, we still need to add 1 Mbps
	 * and 6 Mbps because the 802.11-2007 standard says in 9.6:
	 *
	 *    [...] a STA responding to a received frame shall transmit
	 *    its Control Response frame [...] at the highest rate in the
	 *    BSSBasicRateSet parameter that is less than or equal to the
	 *    rate of the immediately previous frame in the frame exchange
	 *    sequence ([...]) and that is of the same modulation class
	 *    ([...]) as the received frame. If no rate contained in the
	 *    BSSBasicRateSet parameter meets these conditions, then the
	 *    control frame sent in response to a received frame shall be
	 *    transmitted at the highest mandatory rate of the PHY that is
	 *    less than or equal to the rate of the received frame, and
	 *    that is of the same modulation class as the received frame.
	 *
	 * As a consequence, we need to add all mandatory rates that are
	 * lower than all of the basic rates to these biपंचांगaps.
	 */

	अगर (IWL_RATE_24M_INDEX < lowest_present_ofdm)
		ofdm |= IWL_RATE_24M_MASK >> IWL_FIRST_OFDM_RATE;
	अगर (IWL_RATE_12M_INDEX < lowest_present_ofdm)
		ofdm |= IWL_RATE_12M_MASK >> IWL_FIRST_OFDM_RATE;
	/* 6M alपढ़ोy there or needed so always add */
	ofdm |= IWL_RATE_6M_MASK >> IWL_FIRST_OFDM_RATE;

	/*
	 * CCK is a bit more complex with DSSS vs. HR/DSSS vs. ERP.
	 * Note, however:
	 *  - अगर no CCK rates are basic, it must be ERP since there must
	 *    be some basic rates at all, so they're OFDM => ERP PHY
	 *    (or we're in 5 GHz, and the cck biपंचांगap will never be used)
	 *  - अगर 11M is a basic rate, it must be ERP as well, so add 5.5M
	 *  - अगर 5.5M is basic, 1M and 2M are mandatory
	 *  - अगर 2M is basic, 1M is mandatory
	 *  - अगर 1M is basic, that's the only valid ACK rate.
	 * As a consequence, it's not as complicated as it sounds, just add
	 * any lower rates to the ACK rate biपंचांगap.
	 */
	अगर (IWL_RATE_11M_INDEX < lowest_present_cck)
		cck |= IWL_RATE_11M_MASK >> IWL_FIRST_CCK_RATE;
	अगर (IWL_RATE_5M_INDEX < lowest_present_cck)
		cck |= IWL_RATE_5M_MASK >> IWL_FIRST_CCK_RATE;
	अगर (IWL_RATE_2M_INDEX < lowest_present_cck)
		cck |= IWL_RATE_2M_MASK >> IWL_FIRST_CCK_RATE;
	/* 1M alपढ़ोy there or needed so always add */
	cck |= IWL_RATE_1M_MASK >> IWL_FIRST_CCK_RATE;

	IWL_DEBUG_RATE(priv, "Set basic rates cck:0x%.2x ofdm:0x%.2x\n",
		       cck, ofdm);

	/* "basic_rates" is a misnomer here -- should be called ACK rates */
	ctx->staging.cck_basic_rates = cck;
	ctx->staging.ofdm_basic_rates = ofdm;
पूर्ण

/*
 * iwlagn_commit_rxon - commit staging_rxon to hardware
 *
 * The RXON command in staging_rxon is committed to the hardware and
 * the active_rxon काष्ठाure is updated with the new data.  This
 * function correctly transitions out of the RXON_ASSOC_MSK state अगर
 * a HW tune is required based on the RXON काष्ठाure changes.
 *
 * The connect/disconnect flow should be as the following:
 *
 * 1. make sure send RXON command with association bit unset अगर not connect
 *	this should include the channel and the band क्रम the candidate
 *	to be connected to
 * 2. Add Station beक्रमe RXON association with the AP
 * 3. RXON_timing has to send beक्रमe RXON क्रम connection
 * 4. full RXON command - associated bit set
 * 5. use RXON_ASSOC command to update any flags changes
 */
पूर्णांक iwlagn_commit_rxon(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx)
अणु
	/* cast away the स्थिर क्रम active_rxon in this function */
	काष्ठा iwl_rxon_cmd *active = (व्योम *)&ctx->active;
	bool new_assoc = !!(ctx->staging.filter_flags & RXON_FILTER_ASSOC_MSK);
	पूर्णांक ret;

	lockdep_निश्चित_held(&priv->mutex);

	अगर (!iwl_is_alive(priv))
		वापस -EBUSY;

	/* This function hardcodes a bunch of dual-mode assumptions */
	BUILD_BUG_ON(NUM_IWL_RXON_CTX != 2);

	अगर (!ctx->is_active)
		वापस 0;

	/* always get बारtamp with Rx frame */
	ctx->staging.flags |= RXON_FLG_TSF2HOST_MSK;

	/* recalculate basic rates */
	iwl_calc_basic_rates(priv, ctx);

	/*
	 * क्रमce CTS-to-self frames protection अगर RTS-CTS is not preferred
	 * one aggregation protection method
	 */
	अगर (!priv->hw_params.use_rts_क्रम_aggregation)
		ctx->staging.flags |= RXON_FLG_SELF_CTS_EN;

	अगर ((ctx->vअगर && ctx->vअगर->bss_conf.use_लघु_slot) ||
	    !(ctx->staging.flags & RXON_FLG_BAND_24G_MSK))
		ctx->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
	अन्यथा
		ctx->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;

	iwl_prपूर्णांक_rx_config_cmd(priv, ctx->ctxid);
	ret = iwl_check_rxon_cmd(priv, ctx);
	अगर (ret) अणु
		IWL_ERR(priv, "Invalid RXON configuration. Not committing.\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * receive commit_rxon request
	 * पात any previous channel चयन अगर still in process
	 */
	अगर (test_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status) &&
	    (priv->चयन_channel != ctx->staging.channel)) अणु
		IWL_DEBUG_11H(priv, "abort channel switch on %d\n",
			      le16_to_cpu(priv->चयन_channel));
		iwl_chचयन_करोne(priv, false);
	पूर्ण

	/*
	 * If we करोn't need to send a full RXON, we can use
	 * iwl_rxon_assoc_cmd which is used to reconfigure filter
	 * and other flags क्रम the current radio configuration.
	 */
	अगर (!iwl_full_rxon_required(priv, ctx)) अणु
		ret = iwlagn_send_rxon_assoc(priv, ctx);
		अगर (ret) अणु
			IWL_ERR(priv, "Error setting RXON_ASSOC (%d)\n", ret);
			वापस ret;
		पूर्ण

		स_नकल(active, &ctx->staging, माप(*active));
		/*
		 * We करो not commit tx घातer settings जबतक channel changing,
		 * करो it now अगर after settings changed.
		 */
		iwl_set_tx_घातer(priv, priv->tx_घातer_next, false);

		/* make sure we are in the right PS state */
		iwl_घातer_update_mode(priv, true);

		वापस 0;
	पूर्ण

	iwl_set_rxon_hwcrypto(priv, ctx, !iwlwअगरi_mod_params.swcrypto);

	IWL_DEBUG_INFO(priv,
		       "Going to commit RXON\n"
		       "  * with%s RXON_FILTER_ASSOC_MSK\n"
		       "  * channel = %d\n"
		       "  * bssid = %pM\n",
		       (new_assoc ? "" : "out"),
		       le16_to_cpu(ctx->staging.channel),
		       ctx->staging.bssid_addr);

	/*
	 * Always clear associated first, but with the correct config.
	 * This is required as क्रम example station addition क्रम the
	 * AP station must be करोne after the BSSID is set to correctly
	 * set up filters in the device.
	 */
	ret = iwlagn_rxon_disconn(priv, ctx);
	अगर (ret)
		वापस ret;

	ret = iwlagn_set_pan_params(priv);
	अगर (ret)
		वापस ret;

	अगर (new_assoc)
		वापस iwlagn_rxon_connect(priv, ctx);

	वापस 0;
पूर्ण

व्योम iwlagn_config_ht40(काष्ठा ieee80211_conf *conf,
			काष्ठा iwl_rxon_context *ctx)
अणु
	अगर (conf_is_ht40_minus(conf)) अणु
		ctx->ht.extension_chan_offset =
			IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		ctx->ht.is_40mhz = true;
	पूर्ण अन्यथा अगर (conf_is_ht40_plus(conf)) अणु
		ctx->ht.extension_chan_offset =
			IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		ctx->ht.is_40mhz = true;
	पूर्ण अन्यथा अणु
		ctx->ht.extension_chan_offset =
			IEEE80211_HT_PARAM_CHA_SEC_NONE;
		ctx->ht.is_40mhz = false;
	पूर्ण
पूर्ण

पूर्णांक iwlagn_mac_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_rxon_context *ctx;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ieee80211_channel *channel = conf->chandef.chan;
	पूर्णांक ret = 0;

	IWL_DEBUG_MAC80211(priv, "enter: changed %#x\n", changed);

	mutex_lock(&priv->mutex);

	अगर (unlikely(test_bit(STATUS_SCANNING, &priv->status))) अणु
		IWL_DEBUG_MAC80211(priv, "leave - scanning\n");
		जाओ out;
	पूर्ण

	अगर (!iwl_is_पढ़ोy(priv)) अणु
		IWL_DEBUG_MAC80211(priv, "leave - not ready\n");
		जाओ out;
	पूर्ण

	अगर (changed & (IEEE80211_CONF_CHANGE_SMPS |
		       IEEE80211_CONF_CHANGE_CHANNEL)) अणु
		/* mac80211 uses अटल क्रम non-HT which is what we want */
		priv->current_ht_config.smps = conf->smps_mode;

		/*
		 * Recalculate chain counts.
		 *
		 * If monitor mode is enabled then mac80211 will
		 * set up the SM PS mode to OFF अगर an HT channel is
		 * configured.
		 */
		क्रम_each_context(priv, ctx)
			iwlagn_set_rxon_chain(priv, ctx);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		क्रम_each_context(priv, ctx) अणु
			/* Configure HT40 channels */
			अगर (ctx->ht.enabled != conf_is_ht(conf))
				ctx->ht.enabled = conf_is_ht(conf);

			अगर (ctx->ht.enabled) अणु
				/* अगर HT40 is used, it should not change
				 * after associated except channel चयन */
				अगर (!ctx->ht.is_40mhz ||
						!iwl_is_associated_ctx(ctx))
					iwlagn_config_ht40(conf, ctx);
			पूर्ण अन्यथा
				ctx->ht.is_40mhz = false;

			/*
			 * Default to no protection. Protection mode will
			 * later be set from BSS config in iwl_ht_conf
			 */
			ctx->ht.protection = IEEE80211_HT_OP_MODE_PROTECTION_NONE;

			/* अगर we are चयनing from ht to 2.4 clear flags
			 * from any ht related info since 2.4 करोes not
			 * support ht */
			अगर (le16_to_cpu(ctx->staging.channel) !=
			    channel->hw_value)
				ctx->staging.flags = 0;

			iwl_set_rxon_channel(priv, channel, ctx);
			iwl_set_rxon_ht(priv, &priv->current_ht_config);

			iwl_set_flags_क्रम_band(priv, ctx, channel->band,
					       ctx->vअगर);
		पूर्ण

		iwl_update_bcast_stations(priv);
	पूर्ण

	अगर (changed & (IEEE80211_CONF_CHANGE_PS |
			IEEE80211_CONF_CHANGE_IDLE)) अणु
		ret = iwl_घातer_update_mode(priv, false);
		अगर (ret)
			IWL_DEBUG_MAC80211(priv, "Error setting sleep level\n");
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		IWL_DEBUG_MAC80211(priv, "TX Power old=%d new=%d\n",
			priv->tx_घातer_user_lmt, conf->घातer_level);

		iwl_set_tx_घातer(priv, conf->घातer_level, false);
	पूर्ण

	क्रम_each_context(priv, ctx) अणु
		अगर (!स_भेद(&ctx->staging, &ctx->active, माप(ctx->staging)))
			जारी;
		iwlagn_commit_rxon(priv, ctx);
	पूर्ण
 out:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	वापस ret;
पूर्ण

अटल व्योम iwlagn_check_needed_chains(काष्ठा iwl_priv *priv,
				       काष्ठा iwl_rxon_context *ctx,
				       काष्ठा ieee80211_bss_conf *bss_conf)
अणु
	काष्ठा ieee80211_vअगर *vअगर = ctx->vअगर;
	काष्ठा iwl_rxon_context *पंचांगp;
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_ht_config *ht_conf = &priv->current_ht_config;
	काष्ठा ieee80211_sta_ht_cap *ht_cap;
	bool need_multiple;

	lockdep_निश्चित_held(&priv->mutex);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		rcu_पढ़ो_lock();
		sta = ieee80211_find_sta(vअगर, bss_conf->bssid);
		अगर (!sta) अणु
			/*
			 * If at all, this can only happen through a race
			 * when the AP disconnects us जबतक we're still
			 * setting up the connection, in that हाल mac80211
			 * will soon tell us about that.
			 */
			need_multiple = false;
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण

		ht_cap = &sta->ht_cap;

		need_multiple = true;

		/*
		 * If the peer advertises no support क्रम receiving 2 and 3
		 * stream MCS rates, it can't be transmitting them either.
		 */
		अगर (ht_cap->mcs.rx_mask[1] == 0 &&
		    ht_cap->mcs.rx_mask[2] == 0) अणु
			need_multiple = false;
		पूर्ण अन्यथा अगर (!(ht_cap->mcs.tx_params &
						IEEE80211_HT_MCS_TX_DEFINED)) अणु
			/* If it can't TX MCS at all ... */
			need_multiple = false;
		पूर्ण अन्यथा अगर (ht_cap->mcs.tx_params &
						IEEE80211_HT_MCS_TX_RX_DIFF) अणु
			पूर्णांक maxstreams;

			/*
			 * But अगर it can receive them, it might still not
			 * be able to transmit them, which is what we need
			 * to check here -- so check the number of streams
			 * it advertises क्रम TX (अगर dअगरferent from RX).
			 */

			maxstreams = (ht_cap->mcs.tx_params &
				 IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK);
			maxstreams >>=
				IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT;
			maxstreams += 1;

			अगर (maxstreams <= 1)
				need_multiple = false;
		पूर्ण

		rcu_पढ़ो_unlock();
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		/* currently */
		need_multiple = false;
		अवरोध;
	शेष:
		/* only AP really */
		need_multiple = true;
		अवरोध;
	पूर्ण

	ctx->ht_need_multiple_chains = need_multiple;

	अगर (!need_multiple) अणु
		/* check all contexts */
		क्रम_each_context(priv, पंचांगp) अणु
			अगर (!पंचांगp->vअगर)
				जारी;
			अगर (पंचांगp->ht_need_multiple_chains) अणु
				need_multiple = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	ht_conf->single_chain_sufficient = !need_multiple;
पूर्ण

अटल व्योम iwlagn_chain_noise_reset(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_chain_noise_data *data = &priv->chain_noise_data;
	पूर्णांक ret;

	अगर (priv->calib_disabled & IWL_CHAIN_NOISE_CALIB_DISABLED)
		वापस;

	अगर ((data->state == IWL_CHAIN_NOISE_ALIVE) &&
	    iwl_is_any_associated(priv)) अणु
		काष्ठा iwl_calib_chain_noise_reset_cmd cmd;

		/* clear data क्रम chain noise calibration algorithm */
		data->chain_noise_a = 0;
		data->chain_noise_b = 0;
		data->chain_noise_c = 0;
		data->chain_संकेत_a = 0;
		data->chain_संकेत_b = 0;
		data->chain_संकेत_c = 0;
		data->beacon_count = 0;

		स_रखो(&cmd, 0, माप(cmd));
		iwl_set_calib_hdr(&cmd.hdr,
			priv->phy_calib_chain_noise_reset_cmd);
		ret = iwl_dvm_send_cmd_pdu(priv,
					REPLY_PHY_CALIBRATION_CMD,
					0, माप(cmd), &cmd);
		अगर (ret)
			IWL_ERR(priv,
				"Could not send REPLY_PHY_CALIBRATION_CMD\n");
		data->state = IWL_CHAIN_NOISE_ACCUMULATE;
		IWL_DEBUG_CALIB(priv, "Run chain_noise_calibrate\n");
	पूर्ण
पूर्ण

व्योम iwlagn_bss_info_changed(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_bss_conf *bss_conf,
			     u32 changes)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_rxon_context *ctx = iwl_rxon_ctx_from_vअगर(vअगर);
	पूर्णांक ret;
	bool क्रमce = false;

	mutex_lock(&priv->mutex);

	अगर (changes & BSS_CHANGED_IDLE && bss_conf->idle) अणु
		/*
		 * If we go idle, then clearly no "passive-no-rx"
		 * workaround is needed any more, this is a reset.
		 */
		iwlagn_lअगरt_passive_no_rx(priv);
	पूर्ण

	अगर (unlikely(!iwl_is_पढ़ोy(priv))) अणु
		IWL_DEBUG_MAC80211(priv, "leave - not ready\n");
		mutex_unlock(&priv->mutex);
		वापस;
        पूर्ण

	अगर (unlikely(!ctx->vअगर)) अणु
		IWL_DEBUG_MAC80211(priv, "leave - vif is NULL\n");
		mutex_unlock(&priv->mutex);
		वापस;
	पूर्ण

	अगर (changes & BSS_CHANGED_BEACON_INT)
		क्रमce = true;

	अगर (changes & BSS_CHANGED_QOS) अणु
		ctx->qos_data.qos_active = bss_conf->qos;
		iwlagn_update_qos(priv, ctx);
	पूर्ण

	ctx->staging.assoc_id = cpu_to_le16(vअगर->bss_conf.aid);
	अगर (vअगर->bss_conf.use_लघु_preamble)
		ctx->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
	अन्यथा
		ctx->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;

	अगर (changes & BSS_CHANGED_ASSOC) अणु
		अगर (bss_conf->assoc) अणु
			priv->बारtamp = bss_conf->sync_tsf;
			ctx->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
		पूर्ण अन्यथा अणु
			ctx->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;

			अगर (ctx->ctxid == IWL_RXON_CTX_BSS)
				priv->have_rekey_data = false;
		पूर्ण

		iwlagn_bt_coex_rssi_monitor(priv);
	पूर्ण

	अगर (ctx->ht.enabled) अणु
		ctx->ht.protection = bss_conf->ht_operation_mode &
					IEEE80211_HT_OP_MODE_PROTECTION;
		ctx->ht.non_gf_sta_present = !!(bss_conf->ht_operation_mode &
					IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
		iwlagn_check_needed_chains(priv, ctx, bss_conf);
		iwl_set_rxon_ht(priv, &priv->current_ht_config);
	पूर्ण

	iwlagn_set_rxon_chain(priv, ctx);

	अगर (bss_conf->use_cts_prot && (priv->band != NL80211_BAND_5GHZ))
		ctx->staging.flags |= RXON_FLG_TGG_PROTECT_MSK;
	अन्यथा
		ctx->staging.flags &= ~RXON_FLG_TGG_PROTECT_MSK;

	अगर (bss_conf->use_cts_prot)
		ctx->staging.flags |= RXON_FLG_SELF_CTS_EN;
	अन्यथा
		ctx->staging.flags &= ~RXON_FLG_SELF_CTS_EN;

	स_नकल(ctx->staging.bssid_addr, bss_conf->bssid, ETH_ALEN);

	अगर (vअगर->type == NL80211_IFTYPE_AP ||
	    vअगर->type == NL80211_IFTYPE_ADHOC) अणु
		अगर (vअगर->bss_conf.enable_beacon) अणु
			ctx->staging.filter_flags |= RXON_FILTER_ASSOC_MSK;
			priv->beacon_ctx = ctx;
		पूर्ण अन्यथा अणु
			ctx->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
			priv->beacon_ctx = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * If the ucode decides to करो beacon filtering beक्रमe
	 * association, it will lose beacons that are needed
	 * beक्रमe sending frames out on passive channels. This
	 * causes association failures on those channels. Enable
	 * receiving beacons in such हालs.
	 */

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		अगर (!bss_conf->assoc)
			ctx->staging.filter_flags |= RXON_FILTER_BCON_AWARE_MSK;
		अन्यथा
			ctx->staging.filter_flags &=
						    ~RXON_FILTER_BCON_AWARE_MSK;
	पूर्ण

	अगर (क्रमce || स_भेद(&ctx->staging, &ctx->active, माप(ctx->staging)))
		iwlagn_commit_rxon(priv, ctx);

	अगर (changes & BSS_CHANGED_ASSOC && bss_conf->assoc) अणु
		/*
		 * The chain noise calibration will enable PM upon
		 * completion. If calibration has alपढ़ोy been run
		 * then we need to enable घातer management here.
		 */
		अगर (priv->chain_noise_data.state == IWL_CHAIN_NOISE_DONE)
			iwl_घातer_update_mode(priv, false);

		/* Enable RX dअगरferential gain and sensitivity calibrations */
		iwlagn_chain_noise_reset(priv);
		priv->start_calib = 1;
	पूर्ण

	अगर (changes & BSS_CHANGED_IBSS) अणु
		ret = iwlagn_manage_ibss_station(priv, vअगर,
						 bss_conf->ibss_joined);
		अगर (ret)
			IWL_ERR(priv, "failed to %s IBSS station %pM\n",
				bss_conf->ibss_joined ? "add" : "remove",
				bss_conf->bssid);
	पूर्ण

	अगर (changes & BSS_CHANGED_BEACON && priv->beacon_ctx == ctx) अणु
		अगर (iwlagn_update_beacon(priv, vअगर))
			IWL_ERR(priv, "Error updating beacon\n");
	पूर्ण

	mutex_unlock(&priv->mutex);
पूर्ण

व्योम iwlagn_post_scan(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_rxon_context *ctx;

	/*
	 * We करो not commit घातer settings जबतक scan is pending,
	 * करो it now अगर the settings changed.
	 */
	iwl_घातer_set_mode(priv, &priv->घातer_data.sleep_cmd_next, false);
	iwl_set_tx_घातer(priv, priv->tx_घातer_next, false);

	/*
	 * Since setting the RXON may have been deferred जबतक
	 * perक्रमming the scan, fire one off अगर needed
	 */
	क्रम_each_context(priv, ctx)
		अगर (स_भेद(&ctx->staging, &ctx->active, माप(ctx->staging)))
			iwlagn_commit_rxon(priv, ctx);

	iwlagn_set_pan_params(priv);
पूर्ण
