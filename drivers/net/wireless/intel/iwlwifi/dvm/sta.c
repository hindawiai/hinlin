<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 *
 * Portions of this file are derived from the ipw3945 project, as well
 * as portions of the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>
#समावेश "iwl-trans.h"
#समावेश "dev.h"
#समावेश "agn.h"

स्थिर u8 iwl_bcast_addr[ETH_ALEN] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;

अटल पूर्णांक iwl_sta_ucode_activate(काष्ठा iwl_priv *priv, u8 sta_id)
अणु
	lockdep_निश्चित_held(&priv->sta_lock);

	अगर (sta_id >= IWLAGN_STATION_COUNT) अणु
		IWL_ERR(priv, "invalid sta_id %u\n", sta_id);
		वापस -EINVAL;
	पूर्ण
	अगर (!(priv->stations[sta_id].used & IWL_STA_DRIVER_ACTIVE))
		IWL_ERR(priv, "ACTIVATE a non DRIVER active station id %u "
			"addr %pM\n",
			sta_id, priv->stations[sta_id].sta.sta.addr);

	अगर (priv->stations[sta_id].used & IWL_STA_UCODE_ACTIVE) अणु
		IWL_DEBUG_ASSOC(priv,
				"STA id %u addr %pM already present in uCode "
				"(according to driver)\n",
				sta_id, priv->stations[sta_id].sta.sta.addr);
	पूर्ण अन्यथा अणु
		priv->stations[sta_id].used |= IWL_STA_UCODE_ACTIVE;
		IWL_DEBUG_ASSOC(priv, "Added STA id %u addr %pM to uCode\n",
				sta_id, priv->stations[sta_id].sta.sta.addr);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम iwl_process_add_sta_resp(काष्ठा iwl_priv *priv,
				     काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_add_sta_resp *add_sta_resp = (व्योम *)pkt->data;

	IWL_DEBUG_INFO(priv, "Processing response for adding station\n");

	spin_lock_bh(&priv->sta_lock);

	चयन (add_sta_resp->status) अणु
	हाल ADD_STA_SUCCESS_MSK:
		IWL_DEBUG_INFO(priv, "REPLY_ADD_STA PASSED\n");
		अवरोध;
	हाल ADD_STA_NO_ROOM_IN_TABLE:
		IWL_ERR(priv, "Adding station failed, no room in table.\n");
		अवरोध;
	हाल ADD_STA_NO_BLOCK_ACK_RESOURCE:
		IWL_ERR(priv,
			"Adding station failed, no block ack resource.\n");
		अवरोध;
	हाल ADD_STA_MODIFY_NON_EXIST_STA:
		IWL_ERR(priv, "Attempting to modify non-existing station\n");
		अवरोध;
	शेष:
		IWL_DEBUG_ASSOC(priv, "Received REPLY_ADD_STA:(0x%08X)\n",
				add_sta_resp->status);
		अवरोध;
	पूर्ण

	spin_unlock_bh(&priv->sta_lock);
पूर्ण

व्योम iwl_add_sta_callback(काष्ठा iwl_priv *priv, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);

	iwl_process_add_sta_resp(priv, pkt);
पूर्ण

पूर्णांक iwl_send_add_sta(काष्ठा iwl_priv *priv,
		     काष्ठा iwl_addsta_cmd *sta, u8 flags)
अणु
	पूर्णांक ret = 0;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_ADD_STA,
		.flags = flags,
		.data = अणु sta, पूर्ण,
		.len = अणु माप(*sta), पूर्ण,
	पूर्ण;
	u8 sta_id __maybe_unused = sta->sta.sta_id;
	काष्ठा iwl_rx_packet *pkt;
	काष्ठा iwl_add_sta_resp *add_sta_resp;

	IWL_DEBUG_INFO(priv, "Adding sta %u (%pM) %ssynchronously\n",
		       sta_id, sta->sta.addr, flags & CMD_ASYNC ?  "a" : "");

	अगर (!(flags & CMD_ASYNC)) अणु
		cmd.flags |= CMD_WANT_SKB;
		might_sleep();
	पूर्ण

	ret = iwl_dvm_send_cmd(priv, &cmd);

	अगर (ret || (flags & CMD_ASYNC))
		वापस ret;

	pkt = cmd.resp_pkt;
	add_sta_resp = (व्योम *)pkt->data;

	/* debug messages are prपूर्णांकed in the handler */
	अगर (add_sta_resp->status == ADD_STA_SUCCESS_MSK) अणु
		spin_lock_bh(&priv->sta_lock);
		ret = iwl_sta_ucode_activate(priv, sta_id);
		spin_unlock_bh(&priv->sta_lock);
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण

	iwl_मुक्त_resp(&cmd);

	वापस ret;
पूर्ण

bool iwl_is_ht40_tx_allowed(काष्ठा iwl_priv *priv,
			    काष्ठा iwl_rxon_context *ctx,
			    काष्ठा ieee80211_sta *sta)
अणु
	अगर (!ctx->ht.enabled || !ctx->ht.is_40mhz)
		वापस false;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (priv->disable_ht40)
		वापस false;
#पूर्ण_अगर

	/* special हाल क्रम RXON */
	अगर (!sta)
		वापस true;

	वापस sta->bandwidth >= IEEE80211_STA_RX_BW_40;
पूर्ण

अटल व्योम iwl_sta_calc_ht_flags(काष्ठा iwl_priv *priv,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा iwl_rxon_context *ctx,
				  __le32 *flags, __le32 *mask)
अणु
	काष्ठा ieee80211_sta_ht_cap *sta_ht_inf = &sta->ht_cap;

	*mask = STA_FLG_RTS_MIMO_PROT_MSK |
		STA_FLG_MIMO_DIS_MSK |
		STA_FLG_HT40_EN_MSK |
		STA_FLG_MAX_AGG_SIZE_MSK |
		STA_FLG_AGG_MPDU_DENSITY_MSK;
	*flags = 0;

	अगर (!sta || !sta_ht_inf->ht_supported)
		वापस;

	IWL_DEBUG_INFO(priv, "STA %pM SM PS mode: %s\n",
			sta->addr,
			(sta->smps_mode == IEEE80211_SMPS_STATIC) ?
			"static" :
			(sta->smps_mode == IEEE80211_SMPS_DYNAMIC) ?
			"dynamic" : "disabled");

	चयन (sta->smps_mode) अणु
	हाल IEEE80211_SMPS_STATIC:
		*flags |= STA_FLG_MIMO_DIS_MSK;
		अवरोध;
	हाल IEEE80211_SMPS_DYNAMIC:
		*flags |= STA_FLG_RTS_MIMO_PROT_MSK;
		अवरोध;
	हाल IEEE80211_SMPS_OFF:
		अवरोध;
	शेष:
		IWL_WARN(priv, "Invalid MIMO PS mode %d\n", sta->smps_mode);
		अवरोध;
	पूर्ण

	*flags |= cpu_to_le32(
		(u32)sta_ht_inf->ampdu_factor << STA_FLG_MAX_AGG_SIZE_POS);

	*flags |= cpu_to_le32(
		(u32)sta_ht_inf->ampdu_density << STA_FLG_AGG_MPDU_DENSITY_POS);

	अगर (iwl_is_ht40_tx_allowed(priv, ctx, sta))
		*flags |= STA_FLG_HT40_EN_MSK;
पूर्ण

पूर्णांक iwl_sta_update_ht(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
		      काष्ठा ieee80211_sta *sta)
अणु
	u8 sta_id = iwl_sta_id(sta);
	__le32 flags, mask;
	काष्ठा iwl_addsta_cmd cmd;

	अगर (WARN_ON_ONCE(sta_id == IWL_INVALID_STATION))
		वापस -EINVAL;

	iwl_sta_calc_ht_flags(priv, sta, ctx, &flags, &mask);

	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].sta.station_flags &= ~mask;
	priv->stations[sta_id].sta.station_flags |= flags;
	spin_unlock_bh(&priv->sta_lock);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.mode = STA_CONTROL_MODIFY_MSK;
	cmd.station_flags_msk = mask;
	cmd.station_flags = flags;
	cmd.sta.sta_id = sta_id;

	वापस iwl_send_add_sta(priv, &cmd, 0);
पूर्ण

अटल व्योम iwl_set_ht_add_station(काष्ठा iwl_priv *priv, u8 index,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा iwl_rxon_context *ctx)
अणु
	__le32 flags, mask;

	iwl_sta_calc_ht_flags(priv, sta, ctx, &flags, &mask);

	lockdep_निश्चित_held(&priv->sta_lock);
	priv->stations[index].sta.station_flags &= ~mask;
	priv->stations[index].sta.station_flags |= flags;
पूर्ण

/*
 * iwl_prep_station - Prepare station inक्रमmation क्रम addition
 *
 * should be called with sta_lock held
 */
u8 iwl_prep_station(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
		    स्थिर u8 *addr, bool is_ap, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_station_entry *station;
	पूर्णांक i;
	u8 sta_id = IWL_INVALID_STATION;

	अगर (is_ap)
		sta_id = ctx->ap_sta_id;
	अन्यथा अगर (is_broadcast_ether_addr(addr))
		sta_id = ctx->bcast_sta_id;
	अन्यथा
		क्रम (i = IWL_STA_ID; i < IWLAGN_STATION_COUNT; i++) अणु
			अगर (ether_addr_equal(priv->stations[i].sta.sta.addr,
					     addr)) अणु
				sta_id = i;
				अवरोध;
			पूर्ण

			अगर (!priv->stations[i].used &&
			    sta_id == IWL_INVALID_STATION)
				sta_id = i;
		पूर्ण

	/*
	 * These two conditions have the same outcome, but keep them
	 * separate
	 */
	अगर (unlikely(sta_id == IWL_INVALID_STATION))
		वापस sta_id;

	/*
	 * uCode is not able to deal with multiple requests to add a
	 * station. Keep track अगर one is in progress so that we करो not send
	 * another.
	 */
	अगर (priv->stations[sta_id].used & IWL_STA_UCODE_INPROGRESS) अणु
		IWL_DEBUG_INFO(priv, "STA %d already in process of being "
			       "added.\n", sta_id);
		वापस sta_id;
	पूर्ण

	अगर ((priv->stations[sta_id].used & IWL_STA_DRIVER_ACTIVE) &&
	    (priv->stations[sta_id].used & IWL_STA_UCODE_ACTIVE) &&
	    ether_addr_equal(priv->stations[sta_id].sta.sta.addr, addr)) अणु
		IWL_DEBUG_ASSOC(priv, "STA %d (%pM) already added, not "
				"adding again.\n", sta_id, addr);
		वापस sta_id;
	पूर्ण

	station = &priv->stations[sta_id];
	station->used = IWL_STA_DRIVER_ACTIVE;
	IWL_DEBUG_ASSOC(priv, "Add STA to driver ID %d: %pM\n",
			sta_id, addr);
	priv->num_stations++;

	/* Set up the REPLY_ADD_STA command to send to device */
	स_रखो(&station->sta, 0, माप(काष्ठा iwl_addsta_cmd));
	स_नकल(station->sta.sta.addr, addr, ETH_ALEN);
	station->sta.mode = 0;
	station->sta.sta.sta_id = sta_id;
	station->sta.station_flags = ctx->station_flags;
	station->ctxid = ctx->ctxid;

	अगर (sta) अणु
		काष्ठा iwl_station_priv *sta_priv;

		sta_priv = (व्योम *)sta->drv_priv;
		sta_priv->ctx = ctx;
	पूर्ण

	/*
	 * OK to call unconditionally, since local stations (IBSS BSSID
	 * STA and broadcast STA) pass in a शून्य sta, and mac80211
	 * करोesn't allow HT IBSS.
	 */
	iwl_set_ht_add_station(priv, sta_id, sta, ctx);

	वापस sta_id;

पूर्ण

#घोषणा STA_WAIT_TIMEOUT (HZ/2)

/*
 * iwl_add_station_common -
 */
पूर्णांक iwl_add_station_common(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
			   स्थिर u8 *addr, bool is_ap,
			   काष्ठा ieee80211_sta *sta, u8 *sta_id_r)
अणु
	पूर्णांक ret = 0;
	u8 sta_id;
	काष्ठा iwl_addsta_cmd sta_cmd;

	*sta_id_r = 0;
	spin_lock_bh(&priv->sta_lock);
	sta_id = iwl_prep_station(priv, ctx, addr, is_ap, sta);
	अगर (sta_id == IWL_INVALID_STATION) अणु
		IWL_ERR(priv, "Unable to prepare station %pM for addition\n",
			addr);
		spin_unlock_bh(&priv->sta_lock);
		वापस -EINVAL;
	पूर्ण

	/*
	 * uCode is not able to deal with multiple requests to add a
	 * station. Keep track अगर one is in progress so that we करो not send
	 * another.
	 */
	अगर (priv->stations[sta_id].used & IWL_STA_UCODE_INPROGRESS) अणु
		IWL_DEBUG_INFO(priv, "STA %d already in process of being "
			       "added.\n", sta_id);
		spin_unlock_bh(&priv->sta_lock);
		वापस -EEXIST;
	पूर्ण

	अगर ((priv->stations[sta_id].used & IWL_STA_DRIVER_ACTIVE) &&
	    (priv->stations[sta_id].used & IWL_STA_UCODE_ACTIVE)) अणु
		IWL_DEBUG_ASSOC(priv, "STA %d (%pM) already added, not "
				"adding again.\n", sta_id, addr);
		spin_unlock_bh(&priv->sta_lock);
		वापस -EEXIST;
	पूर्ण

	priv->stations[sta_id].used |= IWL_STA_UCODE_INPROGRESS;
	स_नकल(&sta_cmd, &priv->stations[sta_id].sta,
	       माप(काष्ठा iwl_addsta_cmd));
	spin_unlock_bh(&priv->sta_lock);

	/* Add station to device's station table */
	ret = iwl_send_add_sta(priv, &sta_cmd, 0);
	अगर (ret) अणु
		spin_lock_bh(&priv->sta_lock);
		IWL_ERR(priv, "Adding station %pM failed.\n",
			priv->stations[sta_id].sta.sta.addr);
		priv->stations[sta_id].used &= ~IWL_STA_DRIVER_ACTIVE;
		priv->stations[sta_id].used &= ~IWL_STA_UCODE_INPROGRESS;
		spin_unlock_bh(&priv->sta_lock);
	पूर्ण
	*sta_id_r = sta_id;
	वापस ret;
पूर्ण

/*
 * iwl_sta_ucode_deactivate - deactivate ucode status क्रम a station
 */
अटल व्योम iwl_sta_ucode_deactivate(काष्ठा iwl_priv *priv, u8 sta_id)
अणु
	lockdep_निश्चित_held(&priv->sta_lock);

	/* Ucode must be active and driver must be non active */
	अगर ((priv->stations[sta_id].used &
	     (IWL_STA_UCODE_ACTIVE | IWL_STA_DRIVER_ACTIVE)) !=
	      IWL_STA_UCODE_ACTIVE)
		IWL_ERR(priv, "removed non active STA %u\n", sta_id);

	priv->stations[sta_id].used &= ~IWL_STA_UCODE_ACTIVE;

	स_रखो(&priv->stations[sta_id], 0, माप(काष्ठा iwl_station_entry));
	IWL_DEBUG_ASSOC(priv, "Removed STA %u\n", sta_id);
पूर्ण

अटल पूर्णांक iwl_send_हटाओ_station(काष्ठा iwl_priv *priv,
				   स्थिर u8 *addr, पूर्णांक sta_id,
				   bool temporary)
अणु
	काष्ठा iwl_rx_packet *pkt;
	पूर्णांक ret;
	काष्ठा iwl_rem_sta_cmd rm_sta_cmd;
	काष्ठा iwl_rem_sta_resp *rem_sta_resp;

	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_REMOVE_STA,
		.len = अणु माप(काष्ठा iwl_rem_sta_cmd), पूर्ण,
		.data = अणु &rm_sta_cmd, पूर्ण,
	पूर्ण;

	स_रखो(&rm_sta_cmd, 0, माप(rm_sta_cmd));
	rm_sta_cmd.num_sta = 1;
	स_नकल(&rm_sta_cmd.addr, addr, ETH_ALEN);

	cmd.flags |= CMD_WANT_SKB;

	ret = iwl_dvm_send_cmd(priv, &cmd);

	अगर (ret)
		वापस ret;

	pkt = cmd.resp_pkt;
	rem_sta_resp = (व्योम *)pkt->data;

	चयन (rem_sta_resp->status) अणु
	हाल REM_STA_SUCCESS_MSK:
		अगर (!temporary) अणु
			spin_lock_bh(&priv->sta_lock);
			iwl_sta_ucode_deactivate(priv, sta_id);
			spin_unlock_bh(&priv->sta_lock);
		पूर्ण
		IWL_DEBUG_ASSOC(priv, "REPLY_REMOVE_STA PASSED\n");
		अवरोध;
	शेष:
		ret = -EIO;
		IWL_ERR(priv, "REPLY_REMOVE_STA failed\n");
		अवरोध;
	पूर्ण

	iwl_मुक्त_resp(&cmd);

	वापस ret;
पूर्ण

/*
 * iwl_हटाओ_station - Remove driver's knowledge of station.
 */
पूर्णांक iwl_हटाओ_station(काष्ठा iwl_priv *priv, स्थिर u8 sta_id,
		       स्थिर u8 *addr)
अणु
	u8 tid;

	अगर (!iwl_is_पढ़ोy(priv)) अणु
		IWL_DEBUG_INFO(priv,
			"Unable to remove station %pM, device not ready.\n",
			addr);
		/*
		 * It is typical क्रम stations to be हटाओd when we are
		 * going करोwn. Return success since device will be करोwn
		 * soon anyway
		 */
		वापस 0;
	पूर्ण

	IWL_DEBUG_ASSOC(priv, "Removing STA from driver:%d  %pM\n",
			sta_id, addr);

	अगर (WARN_ON(sta_id == IWL_INVALID_STATION))
		वापस -EINVAL;

	spin_lock_bh(&priv->sta_lock);

	अगर (!(priv->stations[sta_id].used & IWL_STA_DRIVER_ACTIVE)) अणु
		IWL_DEBUG_INFO(priv, "Removing %pM but non DRIVER active\n",
				addr);
		जाओ out_err;
	पूर्ण

	अगर (!(priv->stations[sta_id].used & IWL_STA_UCODE_ACTIVE)) अणु
		IWL_DEBUG_INFO(priv, "Removing %pM but non UCODE active\n",
				addr);
		जाओ out_err;
	पूर्ण

	अगर (priv->stations[sta_id].used & IWL_STA_LOCAL) अणु
		kमुक्त(priv->stations[sta_id].lq);
		priv->stations[sta_id].lq = शून्य;
	पूर्ण

	क्रम (tid = 0; tid < IWL_MAX_TID_COUNT; tid++)
		स_रखो(&priv->tid_data[sta_id][tid], 0,
			माप(priv->tid_data[sta_id][tid]));

	priv->stations[sta_id].used &= ~IWL_STA_DRIVER_ACTIVE;

	priv->num_stations--;

	अगर (WARN_ON(priv->num_stations < 0))
		priv->num_stations = 0;

	spin_unlock_bh(&priv->sta_lock);

	वापस iwl_send_हटाओ_station(priv, addr, sta_id, false);
out_err:
	spin_unlock_bh(&priv->sta_lock);
	वापस -EINVAL;
पूर्ण

व्योम iwl_deactivate_station(काष्ठा iwl_priv *priv, स्थिर u8 sta_id,
			    स्थिर u8 *addr)
अणु
	u8 tid;

	अगर (!iwl_is_पढ़ोy(priv)) अणु
		IWL_DEBUG_INFO(priv,
			"Unable to remove station %pM, device not ready.\n",
			addr);
		वापस;
	पूर्ण

	IWL_DEBUG_ASSOC(priv, "Deactivating STA: %pM (%d)\n", addr, sta_id);

	अगर (WARN_ON_ONCE(sta_id == IWL_INVALID_STATION))
		वापस;

	spin_lock_bh(&priv->sta_lock);

	WARN_ON_ONCE(!(priv->stations[sta_id].used & IWL_STA_DRIVER_ACTIVE));

	क्रम (tid = 0; tid < IWL_MAX_TID_COUNT; tid++)
		स_रखो(&priv->tid_data[sta_id][tid], 0,
			माप(priv->tid_data[sta_id][tid]));

	priv->stations[sta_id].used &= ~IWL_STA_DRIVER_ACTIVE;
	priv->stations[sta_id].used &= ~IWL_STA_UCODE_INPROGRESS;

	priv->num_stations--;

	अगर (WARN_ON_ONCE(priv->num_stations < 0))
		priv->num_stations = 0;

	spin_unlock_bh(&priv->sta_lock);
पूर्ण

अटल व्योम iwl_sta_fill_lq(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
			    u8 sta_id, काष्ठा iwl_link_quality_cmd *link_cmd)
अणु
	पूर्णांक i, r;
	u32 rate_flags = 0;
	__le32 rate_n_flags;

	lockdep_निश्चित_held(&priv->mutex);

	स_रखो(link_cmd, 0, माप(*link_cmd));

	/* Set up the rate scaling to start at selected rate, fall back
	 * all the way करोwn to 1M in IEEE order, and then spin on 1M */
	अगर (priv->band == NL80211_BAND_5GHZ)
		r = IWL_RATE_6M_INDEX;
	अन्यथा अगर (ctx && ctx->vअगर && ctx->vअगर->p2p)
		r = IWL_RATE_6M_INDEX;
	अन्यथा
		r = IWL_RATE_1M_INDEX;

	अगर (r >= IWL_FIRST_CCK_RATE && r <= IWL_LAST_CCK_RATE)
		rate_flags |= RATE_MCS_CCK_MSK;

	rate_flags |= first_antenna(priv->nvm_data->valid_tx_ant) <<
				RATE_MCS_ANT_POS;
	rate_n_flags = iwl_hw_set_rate_n_flags(iwl_rates[r].plcp, rate_flags);
	क्रम (i = 0; i < LINK_QUAL_MAX_RETRY_NUM; i++)
		link_cmd->rs_table[i].rate_n_flags = rate_n_flags;

	link_cmd->general_params.single_stream_ant_msk =
			first_antenna(priv->nvm_data->valid_tx_ant);

	link_cmd->general_params.dual_stream_ant_msk =
		priv->nvm_data->valid_tx_ant &
		~first_antenna(priv->nvm_data->valid_tx_ant);
	अगर (!link_cmd->general_params.dual_stream_ant_msk) अणु
		link_cmd->general_params.dual_stream_ant_msk = ANT_AB;
	पूर्ण अन्यथा अगर (num_of_ant(priv->nvm_data->valid_tx_ant) == 2) अणु
		link_cmd->general_params.dual_stream_ant_msk =
			priv->nvm_data->valid_tx_ant;
	पूर्ण

	link_cmd->agg_params.agg_dis_start_th =
		LINK_QUAL_AGG_DISABLE_START_DEF;
	link_cmd->agg_params.agg_समय_limit =
		cpu_to_le16(LINK_QUAL_AGG_TIME_LIMIT_DEF);

	link_cmd->sta_id = sta_id;
पूर्ण

/*
 * iwl_clear_ucode_stations - clear ucode station table bits
 *
 * This function clears all the bits in the driver indicating
 * which stations are active in the ucode. Call when something
 * other than explicit station management would cause this in
 * the ucode, e.g. unassociated RXON.
 */
व्योम iwl_clear_ucode_stations(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rxon_context *ctx)
अणु
	पूर्णांक i;
	bool cleared = false;

	IWL_DEBUG_INFO(priv, "Clearing ucode stations in driver\n");

	spin_lock_bh(&priv->sta_lock);
	क्रम (i = 0; i < IWLAGN_STATION_COUNT; i++) अणु
		अगर (ctx && ctx->ctxid != priv->stations[i].ctxid)
			जारी;

		अगर (priv->stations[i].used & IWL_STA_UCODE_ACTIVE) अणु
			IWL_DEBUG_INFO(priv,
				"Clearing ucode active for station %d\n", i);
			priv->stations[i].used &= ~IWL_STA_UCODE_ACTIVE;
			cleared = true;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->sta_lock);

	अगर (!cleared)
		IWL_DEBUG_INFO(priv,
			       "No active stations found to be cleared\n");
पूर्ण

/*
 * iwl_restore_stations() - Restore driver known stations to device
 *
 * All stations considered active by driver, but not present in ucode, is
 * restored.
 *
 * Function sleeps.
 */
व्योम iwl_restore_stations(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx)
अणु
	काष्ठा iwl_addsta_cmd sta_cmd;
	अटल स्थिर काष्ठा iwl_link_quality_cmd zero_lq = अणुपूर्ण;
	काष्ठा iwl_link_quality_cmd lq;
	पूर्णांक i;
	bool found = false;
	पूर्णांक ret;
	bool send_lq;

	अगर (!iwl_is_पढ़ोy(priv)) अणु
		IWL_DEBUG_INFO(priv,
			       "Not ready yet, not restoring any stations.\n");
		वापस;
	पूर्ण

	IWL_DEBUG_ASSOC(priv, "Restoring all known stations ... start.\n");
	spin_lock_bh(&priv->sta_lock);
	क्रम (i = 0; i < IWLAGN_STATION_COUNT; i++) अणु
		अगर (ctx->ctxid != priv->stations[i].ctxid)
			जारी;
		अगर ((priv->stations[i].used & IWL_STA_DRIVER_ACTIVE) &&
			    !(priv->stations[i].used & IWL_STA_UCODE_ACTIVE)) अणु
			IWL_DEBUG_ASSOC(priv, "Restoring sta %pM\n",
					priv->stations[i].sta.sta.addr);
			priv->stations[i].sta.mode = 0;
			priv->stations[i].used |= IWL_STA_UCODE_INPROGRESS;
			found = true;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < IWLAGN_STATION_COUNT; i++) अणु
		अगर ((priv->stations[i].used & IWL_STA_UCODE_INPROGRESS)) अणु
			स_नकल(&sta_cmd, &priv->stations[i].sta,
			       माप(काष्ठा iwl_addsta_cmd));
			send_lq = false;
			अगर (priv->stations[i].lq) अणु
				अगर (priv->wowlan)
					iwl_sta_fill_lq(priv, ctx, i, &lq);
				अन्यथा
					स_नकल(&lq, priv->stations[i].lq,
					       माप(काष्ठा iwl_link_quality_cmd));

				अगर (स_भेद(&lq, &zero_lq, माप(lq)))
					send_lq = true;
			पूर्ण
			spin_unlock_bh(&priv->sta_lock);
			ret = iwl_send_add_sta(priv, &sta_cmd, 0);
			अगर (ret) अणु
				spin_lock_bh(&priv->sta_lock);
				IWL_ERR(priv, "Adding station %pM failed.\n",
					priv->stations[i].sta.sta.addr);
				priv->stations[i].used &=
						~IWL_STA_DRIVER_ACTIVE;
				priv->stations[i].used &=
						~IWL_STA_UCODE_INPROGRESS;
				जारी;
			पूर्ण
			/*
			 * Rate scaling has alपढ़ोy been initialized, send
			 * current LQ command
			 */
			अगर (send_lq)
				iwl_send_lq_cmd(priv, ctx, &lq, 0, true);
			spin_lock_bh(&priv->sta_lock);
			priv->stations[i].used &= ~IWL_STA_UCODE_INPROGRESS;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&priv->sta_lock);
	अगर (!found)
		IWL_DEBUG_INFO(priv, "Restoring all known stations .... "
			"no stations to be restored.\n");
	अन्यथा
		IWL_DEBUG_INFO(priv, "Restoring all known stations .... "
			"complete.\n");
पूर्ण

पूर्णांक iwl_get_मुक्त_ucode_key_offset(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->sta_key_max_num; i++)
		अगर (!test_and_set_bit(i, &priv->ucode_key_table))
			वापस i;

	वापस WEP_INVALID_OFFSET;
पूर्ण

व्योम iwl_dealloc_bcast_stations(काष्ठा iwl_priv *priv)
अणु
	पूर्णांक i;

	spin_lock_bh(&priv->sta_lock);
	क्रम (i = 0; i < IWLAGN_STATION_COUNT; i++) अणु
		अगर (!(priv->stations[i].used & IWL_STA_BCAST))
			जारी;

		priv->stations[i].used &= ~IWL_STA_UCODE_ACTIVE;
		priv->num_stations--;
		अगर (WARN_ON(priv->num_stations < 0))
			priv->num_stations = 0;
		kमुक्त(priv->stations[i].lq);
		priv->stations[i].lq = शून्य;
	पूर्ण
	spin_unlock_bh(&priv->sta_lock);
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
अटल व्योम iwl_dump_lq_cmd(काष्ठा iwl_priv *priv,
			   काष्ठा iwl_link_quality_cmd *lq)
अणु
	पूर्णांक i;
	IWL_DEBUG_RATE(priv, "lq station id 0x%x\n", lq->sta_id);
	IWL_DEBUG_RATE(priv, "lq ant 0x%X 0x%X\n",
		       lq->general_params.single_stream_ant_msk,
		       lq->general_params.dual_stream_ant_msk);

	क्रम (i = 0; i < LINK_QUAL_MAX_RETRY_NUM; i++)
		IWL_DEBUG_RATE(priv, "lq index %d 0x%X\n",
			       i, lq->rs_table[i].rate_n_flags);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम iwl_dump_lq_cmd(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_link_quality_cmd *lq)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * is_lq_table_valid() - Test one aspect of LQ cmd क्रम validity
 *
 * It someबार happens when a HT rate has been in use and we
 * loose connectivity with AP then mac80211 will first tell us that the
 * current channel is not HT anymore beक्रमe removing the station. In such a
 * scenario the RXON flags will be updated to indicate we are not
 * communicating HT anymore, but the LQ command may still contain HT rates.
 * Test क्रम this to prevent driver from sending LQ command between the समय
 * RXON flags are updated and when LQ command is updated.
 */
अटल bool is_lq_table_valid(काष्ठा iwl_priv *priv,
			      काष्ठा iwl_rxon_context *ctx,
			      काष्ठा iwl_link_quality_cmd *lq)
अणु
	पूर्णांक i;

	अगर (ctx->ht.enabled)
		वापस true;

	IWL_DEBUG_INFO(priv, "Channel %u is not an HT channel\n",
		       ctx->active.channel);
	क्रम (i = 0; i < LINK_QUAL_MAX_RETRY_NUM; i++) अणु
		अगर (le32_to_cpu(lq->rs_table[i].rate_n_flags) &
		    RATE_MCS_HT_MSK) अणु
			IWL_DEBUG_INFO(priv,
				       "index %d of LQ expects HT channel\n",
				       i);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/*
 * iwl_send_lq_cmd() - Send link quality command
 * @init: This command is sent as part of station initialization right
 *        after station has been added.
 *
 * The link quality command is sent as the last step of station creation.
 * This is the special हाल in which init is set and we call a callback in
 * this हाल to clear the state indicating that station creation is in
 * progress.
 */
पूर्णांक iwl_send_lq_cmd(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
		    काष्ठा iwl_link_quality_cmd *lq, u8 flags, bool init)
अणु
	पूर्णांक ret = 0;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = REPLY_TX_LINK_QUALITY_CMD,
		.len = अणु माप(काष्ठा iwl_link_quality_cmd), पूर्ण,
		.flags = flags,
		.data = अणु lq, पूर्ण,
	पूर्ण;

	अगर (WARN_ON(lq->sta_id == IWL_INVALID_STATION))
		वापस -EINVAL;


	spin_lock_bh(&priv->sta_lock);
	अगर (!(priv->stations[lq->sta_id].used & IWL_STA_DRIVER_ACTIVE)) अणु
		spin_unlock_bh(&priv->sta_lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_bh(&priv->sta_lock);

	iwl_dump_lq_cmd(priv, lq);
	अगर (WARN_ON(init && (cmd.flags & CMD_ASYNC)))
		वापस -EINVAL;

	अगर (is_lq_table_valid(priv, ctx, lq))
		ret = iwl_dvm_send_cmd(priv, &cmd);
	अन्यथा
		ret = -EINVAL;

	अगर (cmd.flags & CMD_ASYNC)
		वापस ret;

	अगर (init) अणु
		IWL_DEBUG_INFO(priv, "init LQ command complete, "
			       "clearing sta addition status for sta %d\n",
			       lq->sta_id);
		spin_lock_bh(&priv->sta_lock);
		priv->stations[lq->sta_id].used &= ~IWL_STA_UCODE_INPROGRESS;
		spin_unlock_bh(&priv->sta_lock);
	पूर्ण
	वापस ret;
पूर्ण


अटल काष्ठा iwl_link_quality_cmd *
iwl_sta_alloc_lq(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
		 u8 sta_id)
अणु
	काष्ठा iwl_link_quality_cmd *link_cmd;

	link_cmd = kzalloc(माप(काष्ठा iwl_link_quality_cmd), GFP_KERNEL);
	अगर (!link_cmd) अणु
		IWL_ERR(priv, "Unable to allocate memory for LQ cmd.\n");
		वापस शून्य;
	पूर्ण

	iwl_sta_fill_lq(priv, ctx, sta_id, link_cmd);

	वापस link_cmd;
पूर्ण

/*
 * iwlagn_add_bssid_station - Add the special IBSS BSSID station
 *
 * Function sleeps.
 */
पूर्णांक iwlagn_add_bssid_station(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_rxon_context *ctx,
			     स्थिर u8 *addr, u8 *sta_id_r)
अणु
	पूर्णांक ret;
	u8 sta_id;
	काष्ठा iwl_link_quality_cmd *link_cmd;

	अगर (sta_id_r)
		*sta_id_r = IWL_INVALID_STATION;

	ret = iwl_add_station_common(priv, ctx, addr, 0, शून्य, &sta_id);
	अगर (ret) अणु
		IWL_ERR(priv, "Unable to add station %pM\n", addr);
		वापस ret;
	पूर्ण

	अगर (sta_id_r)
		*sta_id_r = sta_id;

	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].used |= IWL_STA_LOCAL;
	spin_unlock_bh(&priv->sta_lock);

	/* Set up शेष rate scaling table in device's station table */
	link_cmd = iwl_sta_alloc_lq(priv, ctx, sta_id);
	अगर (!link_cmd) अणु
		IWL_ERR(priv,
			"Unable to initialize rate scaling for station %pM.\n",
			addr);
		वापस -ENOMEM;
	पूर्ण

	ret = iwl_send_lq_cmd(priv, ctx, link_cmd, 0, true);
	अगर (ret)
		IWL_ERR(priv, "Link quality command failed (%d)\n", ret);

	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].lq = link_cmd;
	spin_unlock_bh(&priv->sta_lock);

	वापस 0;
पूर्ण

/*
 * अटल WEP keys
 *
 * For each context, the device has a table of 4 अटल WEP keys
 * (one क्रम each key index) that is updated with the following
 * commands.
 */

अटल पूर्णांक iwl_send_अटल_wepkey_cmd(काष्ठा iwl_priv *priv,
				      काष्ठा iwl_rxon_context *ctx,
				      bool send_अगर_empty)
अणु
	पूर्णांक i, not_empty = 0;
	u8 buff[माप(काष्ठा iwl_wep_cmd) +
		माप(काष्ठा iwl_wep_key) * WEP_KEYS_MAX];
	काष्ठा iwl_wep_cmd *wep_cmd = (काष्ठा iwl_wep_cmd *)buff;
	माप_प्रकार cmd_size  = माप(काष्ठा iwl_wep_cmd);
	काष्ठा iwl_host_cmd cmd = अणु
		.id = ctx->wep_key_cmd,
		.data = अणु wep_cmd, पूर्ण,
	पूर्ण;

	might_sleep();

	स_रखो(wep_cmd, 0, cmd_size +
			(माप(काष्ठा iwl_wep_key) * WEP_KEYS_MAX));

	क्रम (i = 0; i < WEP_KEYS_MAX ; i++) अणु
		wep_cmd->key[i].key_index = i;
		अगर (ctx->wep_keys[i].key_size) अणु
			wep_cmd->key[i].key_offset = i;
			not_empty = 1;
		पूर्ण अन्यथा अणु
			wep_cmd->key[i].key_offset = WEP_INVALID_OFFSET;
		पूर्ण

		wep_cmd->key[i].key_size = ctx->wep_keys[i].key_size;
		स_नकल(&wep_cmd->key[i].key[3], ctx->wep_keys[i].key,
				ctx->wep_keys[i].key_size);
	पूर्ण

	wep_cmd->global_key_type = WEP_KEY_WEP_TYPE;
	wep_cmd->num_keys = WEP_KEYS_MAX;

	cmd_size += माप(काष्ठा iwl_wep_key) * WEP_KEYS_MAX;

	cmd.len[0] = cmd_size;

	अगर (not_empty || send_अगर_empty)
		वापस iwl_dvm_send_cmd(priv, &cmd);
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक iwl_restore_शेष_wep_keys(काष्ठा iwl_priv *priv,
				 काष्ठा iwl_rxon_context *ctx)
अणु
	lockdep_निश्चित_held(&priv->mutex);

	वापस iwl_send_अटल_wepkey_cmd(priv, ctx, false);
पूर्ण

पूर्णांक iwl_हटाओ_शेष_wep_key(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rxon_context *ctx,
			       काष्ठा ieee80211_key_conf *keyconf)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&priv->mutex);

	IWL_DEBUG_WEP(priv, "Removing default WEP key: idx=%d\n",
		      keyconf->keyidx);

	स_रखो(&ctx->wep_keys[keyconf->keyidx], 0, माप(ctx->wep_keys[0]));
	अगर (iwl_is_rfसमाप्त(priv)) अणु
		IWL_DEBUG_WEP(priv,
			"Not sending REPLY_WEPKEY command due to RFKILL.\n");
		/* but keys in device are clear anyway so वापस success */
		वापस 0;
	पूर्ण
	ret = iwl_send_अटल_wepkey_cmd(priv, ctx, 1);
	IWL_DEBUG_WEP(priv, "Remove default WEP key: idx=%d ret=%d\n",
		      keyconf->keyidx, ret);

	वापस ret;
पूर्ण

पूर्णांक iwl_set_शेष_wep_key(काष्ठा iwl_priv *priv,
			    काष्ठा iwl_rxon_context *ctx,
			    काष्ठा ieee80211_key_conf *keyconf)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&priv->mutex);

	अगर (keyconf->keylen != WEP_KEY_LEN_128 &&
	    keyconf->keylen != WEP_KEY_LEN_64) अणु
		IWL_DEBUG_WEP(priv,
			      "Bad WEP key length %d\n", keyconf->keylen);
		वापस -EINVAL;
	पूर्ण

	keyconf->hw_key_idx = IWLAGN_HW_KEY_DEFAULT;

	ctx->wep_keys[keyconf->keyidx].key_size = keyconf->keylen;
	स_नकल(&ctx->wep_keys[keyconf->keyidx].key, &keyconf->key,
							keyconf->keylen);

	ret = iwl_send_अटल_wepkey_cmd(priv, ctx, false);
	IWL_DEBUG_WEP(priv, "Set default WEP key: len=%d idx=%d ret=%d\n",
		keyconf->keylen, keyconf->keyidx, ret);

	वापस ret;
पूर्ण

/*
 * dynamic (per-station) keys
 *
 * The dynamic keys are a little more complicated. The device has
 * a key cache of up to STA_KEY_MAX_NUM/STA_KEY_MAX_NUM_PAN keys.
 * These are linked to stations by a table that contains an index
 * पूर्णांकo the key table क्रम each station/key index/अणुmcast,unicastपूर्ण,
 * i.e. it's basically an array of poपूर्णांकers like this:
 *	key_offset_t key_mapping[NUM_STATIONS][4][2];
 * (it really works dअगरferently, but you can think of it as such)
 *
 * The key uploading and linking happens in the same command, the
 * add station command with STA_MODIFY_KEY_MASK.
 */

अटल u8 iwlagn_key_sta_id(काष्ठा iwl_priv *priv,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;

	अगर (sta)
		वापस iwl_sta_id(sta);

	/*
	 * The device expects GTKs क्रम station पूर्णांकerfaces to be
	 * installed as GTKs क्रम the AP station. If we have no
	 * station ID, then use the ap_sta_id in that हाल.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_STATION && vअगर_priv->ctx)
		वापस vअगर_priv->ctx->ap_sta_id;

	वापस IWL_INVALID_STATION;
पूर्ण

अटल पूर्णांक iwlagn_send_sta_key(काष्ठा iwl_priv *priv,
			       काष्ठा ieee80211_key_conf *keyconf,
			       u8 sta_id, u32 tkip_iv32, u16 *tkip_p1k,
			       u32 cmd_flags)
अणु
	__le16 key_flags;
	काष्ठा iwl_addsta_cmd sta_cmd;
	पूर्णांक i;

	spin_lock_bh(&priv->sta_lock);
	स_नकल(&sta_cmd, &priv->stations[sta_id].sta, माप(sta_cmd));
	spin_unlock_bh(&priv->sta_lock);

	key_flags = cpu_to_le16(keyconf->keyidx << STA_KEY_FLG_KEYID_POS);
	key_flags |= STA_KEY_FLG_MAP_KEY_MSK;

	चयन (keyconf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		key_flags |= STA_KEY_FLG_CCMP;
		स_नकल(sta_cmd.key.key, keyconf->key, keyconf->keylen);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		key_flags |= STA_KEY_FLG_TKIP;
		sta_cmd.key.tkip_rx_tsc_byte2 = tkip_iv32;
		क्रम (i = 0; i < 5; i++)
			sta_cmd.key.tkip_rx_ttak[i] = cpu_to_le16(tkip_p1k[i]);
		स_नकल(sta_cmd.key.key, keyconf->key, keyconf->keylen);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		key_flags |= STA_KEY_FLG_KEY_SIZE_MSK;
		fallthrough;
	हाल WLAN_CIPHER_SUITE_WEP40:
		key_flags |= STA_KEY_FLG_WEP;
		स_नकल(&sta_cmd.key.key[3], keyconf->key, keyconf->keylen);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	अगर (!(keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		key_flags |= STA_KEY_MULTICAST_MSK;

	/* key poपूर्णांकer (offset) */
	sta_cmd.key.key_offset = keyconf->hw_key_idx;

	sta_cmd.key.key_flags = key_flags;
	sta_cmd.mode = STA_CONTROL_MODIFY_MSK;
	sta_cmd.sta.modअगरy_mask = STA_MODIFY_KEY_MASK;

	वापस iwl_send_add_sta(priv, &sta_cmd, cmd_flags);
पूर्ण

व्योम iwl_update_tkip_key(काष्ठा iwl_priv *priv,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_key_conf *keyconf,
			 काष्ठा ieee80211_sta *sta, u32 iv32, u16 *phase1key)
अणु
	u8 sta_id = iwlagn_key_sta_id(priv, vअगर, sta);

	अगर (sta_id == IWL_INVALID_STATION)
		वापस;

	अगर (iwl_scan_cancel(priv)) अणु
		/* cancel scan failed, just live w/ bad key and rely
		   briefly on SW decryption */
		वापस;
	पूर्ण

	iwlagn_send_sta_key(priv, keyconf, sta_id,
			    iv32, phase1key, CMD_ASYNC);
पूर्ण

पूर्णांक iwl_हटाओ_dynamic_key(काष्ठा iwl_priv *priv,
			   काष्ठा iwl_rxon_context *ctx,
			   काष्ठा ieee80211_key_conf *keyconf,
			   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_addsta_cmd sta_cmd;
	u8 sta_id = iwlagn_key_sta_id(priv, ctx->vअगर, sta);
	__le16 key_flags;

	/* अगर station isn't there, neither is the key */
	अगर (sta_id == IWL_INVALID_STATION)
		वापस -ENOENT;

	spin_lock_bh(&priv->sta_lock);
	स_नकल(&sta_cmd, &priv->stations[sta_id].sta, माप(sta_cmd));
	अगर (!(priv->stations[sta_id].used & IWL_STA_UCODE_ACTIVE))
		sta_id = IWL_INVALID_STATION;
	spin_unlock_bh(&priv->sta_lock);

	अगर (sta_id == IWL_INVALID_STATION)
		वापस 0;

	lockdep_निश्चित_held(&priv->mutex);

	ctx->key_mapping_keys--;

	IWL_DEBUG_WEP(priv, "Remove dynamic key: idx=%d sta=%d\n",
		      keyconf->keyidx, sta_id);

	अगर (!test_and_clear_bit(keyconf->hw_key_idx, &priv->ucode_key_table))
		IWL_ERR(priv, "offset %d not used in uCode key table.\n",
			keyconf->hw_key_idx);

	key_flags = cpu_to_le16(keyconf->keyidx << STA_KEY_FLG_KEYID_POS);
	key_flags |= STA_KEY_FLG_MAP_KEY_MSK | STA_KEY_FLG_NO_ENC |
		     STA_KEY_FLG_INVALID;

	अगर (!(keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		key_flags |= STA_KEY_MULTICAST_MSK;

	sta_cmd.key.key_flags = key_flags;
	sta_cmd.key.key_offset = keyconf->hw_key_idx;
	sta_cmd.sta.modअगरy_mask = STA_MODIFY_KEY_MASK;
	sta_cmd.mode = STA_CONTROL_MODIFY_MSK;

	वापस iwl_send_add_sta(priv, &sta_cmd, 0);
पूर्ण

पूर्णांक iwl_set_dynamic_key(काष्ठा iwl_priv *priv,
			काष्ठा iwl_rxon_context *ctx,
			काष्ठा ieee80211_key_conf *keyconf,
			काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_key_seq seq;
	u16 p1k[5];
	पूर्णांक ret;
	u8 sta_id = iwlagn_key_sta_id(priv, ctx->vअगर, sta);
	स्थिर u8 *addr;

	अगर (sta_id == IWL_INVALID_STATION)
		वापस -EINVAL;

	lockdep_निश्चित_held(&priv->mutex);

	keyconf->hw_key_idx = iwl_get_मुक्त_ucode_key_offset(priv);
	अगर (keyconf->hw_key_idx == WEP_INVALID_OFFSET)
		वापस -ENOSPC;

	ctx->key_mapping_keys++;

	चयन (keyconf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (sta)
			addr = sta->addr;
		अन्यथा /* station mode हाल only */
			addr = ctx->active.bssid_addr;

		/* pre-fill phase 1 key पूर्णांकo device cache */
		ieee80211_get_key_rx_seq(keyconf, 0, &seq);
		ieee80211_get_tkip_rx_p1k(keyconf, addr, seq.tkip.iv32, p1k);
		ret = iwlagn_send_sta_key(priv, keyconf, sta_id,
					  seq.tkip.iv32, p1k, 0);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		ret = iwlagn_send_sta_key(priv, keyconf, sta_id,
					  0, शून्य, 0);
		अवरोध;
	शेष:
		IWL_ERR(priv, "Unknown cipher %x\n", keyconf->cipher);
		ret = -EINVAL;
	पूर्ण

	अगर (ret) अणु
		ctx->key_mapping_keys--;
		clear_bit(keyconf->hw_key_idx, &priv->ucode_key_table);
	पूर्ण

	IWL_DEBUG_WEP(priv, "Set dynamic key: cipher=%x len=%d idx=%d sta=%pM ret=%d\n",
		      keyconf->cipher, keyconf->keylen, keyconf->keyidx,
		      sta ? sta->addr : शून्य, ret);

	वापस ret;
पूर्ण

/*
 * iwlagn_alloc_bcast_station - add broadcast station पूर्णांकo driver's station table.
 *
 * This adds the broadcast station पूर्णांकo the driver's station table
 * and marks it driver active, so that it will be restored to the
 * device at the next best समय.
 */
पूर्णांक iwlagn_alloc_bcast_station(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rxon_context *ctx)
अणु
	काष्ठा iwl_link_quality_cmd *link_cmd;
	u8 sta_id;

	spin_lock_bh(&priv->sta_lock);
	sta_id = iwl_prep_station(priv, ctx, iwl_bcast_addr, false, शून्य);
	अगर (sta_id == IWL_INVALID_STATION) अणु
		IWL_ERR(priv, "Unable to prepare broadcast station\n");
		spin_unlock_bh(&priv->sta_lock);

		वापस -EINVAL;
	पूर्ण

	priv->stations[sta_id].used |= IWL_STA_DRIVER_ACTIVE;
	priv->stations[sta_id].used |= IWL_STA_BCAST;
	spin_unlock_bh(&priv->sta_lock);

	link_cmd = iwl_sta_alloc_lq(priv, ctx, sta_id);
	अगर (!link_cmd) अणु
		IWL_ERR(priv,
			"Unable to initialize rate scaling for bcast station.\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].lq = link_cmd;
	spin_unlock_bh(&priv->sta_lock);

	वापस 0;
पूर्ण

/*
 * iwl_update_bcast_station - update broadcast station's LQ command
 *
 * Only used by iwlagn. Placed here to have all bcast station management
 * code together.
 */
पूर्णांक iwl_update_bcast_station(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_rxon_context *ctx)
अणु
	काष्ठा iwl_link_quality_cmd *link_cmd;
	u8 sta_id = ctx->bcast_sta_id;

	link_cmd = iwl_sta_alloc_lq(priv, ctx, sta_id);
	अगर (!link_cmd) अणु
		IWL_ERR(priv, "Unable to initialize rate scaling for bcast station.\n");
		वापस -ENOMEM;
	पूर्ण

	spin_lock_bh(&priv->sta_lock);
	अगर (priv->stations[sta_id].lq)
		kमुक्त(priv->stations[sta_id].lq);
	अन्यथा
		IWL_DEBUG_INFO(priv, "Bcast station rate scaling has not been initialized yet.\n");
	priv->stations[sta_id].lq = link_cmd;
	spin_unlock_bh(&priv->sta_lock);

	वापस 0;
पूर्ण

पूर्णांक iwl_update_bcast_stations(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_rxon_context *ctx;
	पूर्णांक ret = 0;

	क्रम_each_context(priv, ctx) अणु
		ret = iwl_update_bcast_station(priv, ctx);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * iwl_sta_tx_modअगरy_enable_tid - Enable Tx क्रम this TID in station table
 */
पूर्णांक iwl_sta_tx_modअगरy_enable_tid(काष्ठा iwl_priv *priv, पूर्णांक sta_id, पूर्णांक tid)
अणु
	काष्ठा iwl_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&priv->mutex);

	/* Remove "disable" flag, to enable Tx क्रम this TID */
	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_TID_DISABLE_TX;
	priv->stations[sta_id].sta.tid_disable_tx &= cpu_to_le16(~(1 << tid));
	priv->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	स_नकल(&sta_cmd, &priv->stations[sta_id].sta, माप(काष्ठा iwl_addsta_cmd));
	spin_unlock_bh(&priv->sta_lock);

	वापस iwl_send_add_sta(priv, &sta_cmd, 0);
पूर्ण

पूर्णांक iwl_sta_rx_agg_start(काष्ठा iwl_priv *priv, काष्ठा ieee80211_sta *sta,
			 पूर्णांक tid, u16 ssn)
अणु
	पूर्णांक sta_id;
	काष्ठा iwl_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&priv->mutex);

	sta_id = iwl_sta_id(sta);
	अगर (sta_id == IWL_INVALID_STATION)
		वापस -ENXIO;

	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].sta.station_flags_msk = 0;
	priv->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_ADDBA_TID_MSK;
	priv->stations[sta_id].sta.add_immediate_ba_tid = (u8)tid;
	priv->stations[sta_id].sta.add_immediate_ba_ssn = cpu_to_le16(ssn);
	priv->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	स_नकल(&sta_cmd, &priv->stations[sta_id].sta, माप(काष्ठा iwl_addsta_cmd));
	spin_unlock_bh(&priv->sta_lock);

	वापस iwl_send_add_sta(priv, &sta_cmd, 0);
पूर्ण

पूर्णांक iwl_sta_rx_agg_stop(काष्ठा iwl_priv *priv, काष्ठा ieee80211_sta *sta,
			पूर्णांक tid)
अणु
	पूर्णांक sta_id;
	काष्ठा iwl_addsta_cmd sta_cmd;

	lockdep_निश्चित_held(&priv->mutex);

	sta_id = iwl_sta_id(sta);
	अगर (sta_id == IWL_INVALID_STATION) अणु
		IWL_ERR(priv, "Invalid station for AGG tid %d\n", tid);
		वापस -ENXIO;
	पूर्ण

	spin_lock_bh(&priv->sta_lock);
	priv->stations[sta_id].sta.station_flags_msk = 0;
	priv->stations[sta_id].sta.sta.modअगरy_mask = STA_MODIFY_DELBA_TID_MSK;
	priv->stations[sta_id].sta.हटाओ_immediate_ba_tid = (u8)tid;
	priv->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	स_नकल(&sta_cmd, &priv->stations[sta_id].sta, माप(काष्ठा iwl_addsta_cmd));
	spin_unlock_bh(&priv->sta_lock);

	वापस iwl_send_add_sta(priv, &sta_cmd, 0);
पूर्ण



व्योम iwl_sta_modअगरy_sleep_tx_count(काष्ठा iwl_priv *priv, पूर्णांक sta_id, पूर्णांक cnt)
अणु
	काष्ठा iwl_addsta_cmd cmd = अणु
		.mode = STA_CONTROL_MODIFY_MSK,
		.station_flags = STA_FLG_PWR_SAVE_MSK,
		.station_flags_msk = STA_FLG_PWR_SAVE_MSK,
		.sta.sta_id = sta_id,
		.sta.modअगरy_mask = STA_MODIFY_SLEEP_TX_COUNT_MSK,
		.sleep_tx_count = cpu_to_le16(cnt),
	पूर्ण;

	iwl_send_add_sta(priv, &cmd, CMD_ASYNC);
पूर्ण
