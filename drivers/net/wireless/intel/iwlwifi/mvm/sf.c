<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2013-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 */
#समावेश "mvm.h"

/* For counting bound पूर्णांकerfaces */
काष्ठा iwl_mvm_active_अगरace_iterator_data अणु
	काष्ठा ieee80211_vअगर *ignore_vअगर;
	u8 sta_vअगर_ap_sta_id;
	क्रमागत iwl_sf_state sta_vअगर_state;
	u32 num_active_macs;
पूर्ण;

/*
 * Count bound पूर्णांकerfaces which are not p2p, besides data->ignore_vअगर.
 * data->station_vअगर will poपूर्णांक to one bound vअगर of type station, अगर exists.
 */
अटल व्योम iwl_mvm_bound_अगरace_iterator(व्योम *_data, u8 *mac,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_active_अगरace_iterator_data *data = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (vअगर == data->ignore_vअगर || !mvmvअगर->phy_ctxt ||
	    vअगर->type == NL80211_IFTYPE_P2P_DEVICE)
		वापस;

	data->num_active_macs++;

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		data->sta_vअगर_ap_sta_id = mvmvअगर->ap_sta_id;
		अगर (vअगर->bss_conf.assoc)
			data->sta_vअगर_state = SF_FULL_ON;
		अन्यथा
			data->sta_vअगर_state = SF_INIT_OFF;
	पूर्ण
पूर्ण

/*
 * Aging and idle समयouts क्रम the dअगरferent possible scenarios
 * in शेष configuration
 */
अटल स्थिर
__le32 sf_full_समयout_def[SF_NUM_SCENARIO][SF_NUM_TIMEOUT_TYPES] = अणु
	अणु
		cpu_to_le32(SF_SINGLE_UNICAST_AGING_TIMER_DEF),
		cpu_to_le32(SF_SINGLE_UNICAST_IDLE_TIMER_DEF)
	पूर्ण,
	अणु
		cpu_to_le32(SF_AGG_UNICAST_AGING_TIMER_DEF),
		cpu_to_le32(SF_AGG_UNICAST_IDLE_TIMER_DEF)
	पूर्ण,
	अणु
		cpu_to_le32(SF_MCAST_AGING_TIMER_DEF),
		cpu_to_le32(SF_MCAST_IDLE_TIMER_DEF)
	पूर्ण,
	अणु
		cpu_to_le32(SF_BA_AGING_TIMER_DEF),
		cpu_to_le32(SF_BA_IDLE_TIMER_DEF)
	पूर्ण,
	अणु
		cpu_to_le32(SF_TX_RE_AGING_TIMER_DEF),
		cpu_to_le32(SF_TX_RE_IDLE_TIMER_DEF)
	पूर्ण,
पूर्ण;

/*
 * Aging and idle समयouts क्रम the dअगरferent possible scenarios
 * in single BSS MAC configuration.
 */
अटल स्थिर __le32 sf_full_समयout[SF_NUM_SCENARIO][SF_NUM_TIMEOUT_TYPES] = अणु
	अणु
		cpu_to_le32(SF_SINGLE_UNICAST_AGING_TIMER),
		cpu_to_le32(SF_SINGLE_UNICAST_IDLE_TIMER)
	पूर्ण,
	अणु
		cpu_to_le32(SF_AGG_UNICAST_AGING_TIMER),
		cpu_to_le32(SF_AGG_UNICAST_IDLE_TIMER)
	पूर्ण,
	अणु
		cpu_to_le32(SF_MCAST_AGING_TIMER),
		cpu_to_le32(SF_MCAST_IDLE_TIMER)
	पूर्ण,
	अणु
		cpu_to_le32(SF_BA_AGING_TIMER),
		cpu_to_le32(SF_BA_IDLE_TIMER)
	पूर्ण,
	अणु
		cpu_to_le32(SF_TX_RE_AGING_TIMER),
		cpu_to_le32(SF_TX_RE_IDLE_TIMER)
	पूर्ण,
पूर्ण;

अटल व्योम iwl_mvm_fill_sf_command(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_sf_cfg_cmd *sf_cmd,
				    काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक i, j, watermark;

	sf_cmd->watermark[SF_LONG_DELAY_ON] = cpu_to_le32(SF_W_MARK_SCAN);

	/*
	 * If we are in association flow - check antenna configuration
	 * capabilities of the AP station, and choose the watermark accordingly.
	 */
	अगर (sta) अणु
		अगर (sta->ht_cap.ht_supported ||
		    sta->vht_cap.vht_supported ||
		    sta->he_cap.has_he) अणु
			चयन (sta->rx_nss) अणु
			हाल 1:
				watermark = SF_W_MARK_SISO;
				अवरोध;
			हाल 2:
				watermark = SF_W_MARK_MIMO2;
				अवरोध;
			शेष:
				watermark = SF_W_MARK_MIMO3;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			watermark = SF_W_MARK_LEGACY;
		पूर्ण
	/* शेष watermark value क्रम unassociated mode. */
	पूर्ण अन्यथा अणु
		watermark = SF_W_MARK_MIMO2;
	पूर्ण
	sf_cmd->watermark[SF_FULL_ON] = cpu_to_le32(watermark);

	क्रम (i = 0; i < SF_NUM_SCENARIO; i++) अणु
		क्रम (j = 0; j < SF_NUM_TIMEOUT_TYPES; j++) अणु
			sf_cmd->दीर्घ_delay_समयouts[i][j] =
					cpu_to_le32(SF_LONG_DELAY_AGING_TIMER);
		पूर्ण
	पूर्ण

	अगर (sta) अणु
		BUILD_BUG_ON(माप(sf_full_समयout) !=
			     माप(__le32) * SF_NUM_SCENARIO *
			     SF_NUM_TIMEOUT_TYPES);

		स_नकल(sf_cmd->full_on_समयouts, sf_full_समयout,
		       माप(sf_full_समयout));
	पूर्ण अन्यथा अणु
		BUILD_BUG_ON(माप(sf_full_समयout_def) !=
			     माप(__le32) * SF_NUM_SCENARIO *
			     SF_NUM_TIMEOUT_TYPES);

		स_नकल(sf_cmd->full_on_समयouts, sf_full_समयout_def,
		       माप(sf_full_समयout_def));
	पूर्ण

पूर्ण

अटल पूर्णांक iwl_mvm_sf_config(काष्ठा iwl_mvm *mvm, u8 sta_id,
			     क्रमागत iwl_sf_state new_state)
अणु
	काष्ठा iwl_sf_cfg_cmd sf_cmd = अणु
		.state = cpu_to_le32(new_state),
	पूर्ण;
	काष्ठा ieee80211_sta *sta;
	पूर्णांक ret = 0;

	अगर (mvm->cfg->disable_dummy_notअगरication)
		sf_cmd.state |= cpu_to_le32(SF_CFG_DUMMY_NOTIF_OFF);

	/*
	 * If an associated AP sta changed its antenna configuration, the state
	 * will reमुख्य FULL_ON but SF parameters need to be reconsidered.
	 */
	अगर (new_state != SF_FULL_ON && mvm->sf_state == new_state)
		वापस 0;

	चयन (new_state) अणु
	हाल SF_UNINIT:
		iwl_mvm_fill_sf_command(mvm, &sf_cmd, शून्य);
		अवरोध;
	हाल SF_FULL_ON:
		अगर (sta_id == IWL_MVM_INVALID_STA) अणु
			IWL_ERR(mvm,
				"No station: Cannot switch SF to FULL_ON\n");
			वापस -EINVAL;
		पूर्ण
		rcu_पढ़ो_lock();
		sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);
		अगर (IS_ERR_OR_शून्य(sta)) अणु
			IWL_ERR(mvm, "Invalid station id\n");
			rcu_पढ़ो_unlock();
			वापस -EINVAL;
		पूर्ण
		iwl_mvm_fill_sf_command(mvm, &sf_cmd, sta);
		rcu_पढ़ो_unlock();
		अवरोध;
	हाल SF_INIT_OFF:
		iwl_mvm_fill_sf_command(mvm, &sf_cmd, शून्य);
		अवरोध;
	शेष:
		WARN_ONCE(1, "Invalid state: %d. not sending Smart Fifo cmd\n",
			  new_state);
		वापस -EINVAL;
	पूर्ण

	ret = iwl_mvm_send_cmd_pdu(mvm, REPLY_SF_CFG_CMD, CMD_ASYNC,
				   माप(sf_cmd), &sf_cmd);
	अगर (!ret)
		mvm->sf_state = new_state;

	वापस ret;
पूर्ण

/*
 * Update Smart fअगरo:
 * Count bound पूर्णांकerfaces that are not to be हटाओd, ignoring p2p devices,
 * and set new state accordingly.
 */
पूर्णांक iwl_mvm_sf_update(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *changed_vअगर,
		      bool हटाओ_vअगर)
अणु
	क्रमागत iwl_sf_state new_state;
	u8 sta_id = IWL_MVM_INVALID_STA;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = शून्य;
	काष्ठा iwl_mvm_active_अगरace_iterator_data data = अणु
		.ignore_vअगर = changed_vअगर,
		.sta_vअगर_state = SF_UNINIT,
		.sta_vअगर_ap_sta_id = IWL_MVM_INVALID_STA,
	पूर्ण;

	/*
	 * Ignore the call अगर we are in HW Restart flow, or अगर the handled
	 * vअगर is a p2p device.
	 */
	अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) ||
	    (changed_vअगर && changed_vअगर->type == NL80211_IFTYPE_P2P_DEVICE))
		वापस 0;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_bound_अगरace_iterator,
						   &data);

	/* If changed_vअगर exists and is not to be हटाओd, add to the count */
	अगर (changed_vअगर && !हटाओ_vअगर)
		data.num_active_macs++;

	चयन (data.num_active_macs) अणु
	हाल 0:
		/* If there are no active macs - change state to SF_INIT_OFF */
		new_state = SF_INIT_OFF;
		अवरोध;
	हाल 1:
		अगर (हटाओ_vअगर) अणु
			/* The one active mac left is of type station
			 * and we filled the relevant data during iteration
			 */
			new_state = data.sta_vअगर_state;
			sta_id = data.sta_vअगर_ap_sta_id;
		पूर्ण अन्यथा अणु
			अगर (WARN_ON(!changed_vअगर))
				वापस -EINVAL;
			अगर (changed_vअगर->type != NL80211_IFTYPE_STATION) अणु
				new_state = SF_UNINIT;
			पूर्ण अन्यथा अगर (changed_vअगर->bss_conf.assoc &&
				   changed_vअगर->bss_conf.dtim_period) अणु
				mvmvअगर = iwl_mvm_vअगर_from_mac80211(changed_vअगर);
				sta_id = mvmvअगर->ap_sta_id;
				new_state = SF_FULL_ON;
			पूर्ण अन्यथा अणु
				new_state = SF_INIT_OFF;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		/* If there are multiple active macs - change to SF_UNINIT */
		new_state = SF_UNINIT;
	पूर्ण
	वापस iwl_mvm_sf_config(mvm, sta_id, new_state);
पूर्ण
