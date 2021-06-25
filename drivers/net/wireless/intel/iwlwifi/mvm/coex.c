<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2013-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 */
#समावेश <linux/ieee80211.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>

#समावेश "fw/api/coex.h"
#समावेश "iwl-modparams.h"
#समावेश "mvm.h"
#समावेश "iwl-debug.h"

/* 20MHz / 40MHz below / 40Mhz above*/
अटल स्थिर __le64 iwl_ci_mask[][3] = अणु
	/* dummy entry क्रम channel 0 */
	अणुcpu_to_le64(0), cpu_to_le64(0), cpu_to_le64(0)पूर्ण,
	अणु
		cpu_to_le64(0x0000001FFFULL),
		cpu_to_le64(0x0ULL),
		cpu_to_le64(0x00007FFFFFULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x000000FFFFULL),
		cpu_to_le64(0x0ULL),
		cpu_to_le64(0x0003FFFFFFULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x000003FFFCULL),
		cpu_to_le64(0x0ULL),
		cpu_to_le64(0x000FFFFFFCULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x00001FFFE0ULL),
		cpu_to_le64(0x0ULL),
		cpu_to_le64(0x007FFFFFE0ULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x00007FFF80ULL),
		cpu_to_le64(0x00007FFFFFULL),
		cpu_to_le64(0x01FFFFFF80ULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x0003FFFC00ULL),
		cpu_to_le64(0x0003FFFFFFULL),
		cpu_to_le64(0x0FFFFFFC00ULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x000FFFF000ULL),
		cpu_to_le64(0x000FFFFFFCULL),
		cpu_to_le64(0x3FFFFFF000ULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x007FFF8000ULL),
		cpu_to_le64(0x007FFFFFE0ULL),
		cpu_to_le64(0xFFFFFF8000ULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x01FFFE0000ULL),
		cpu_to_le64(0x01FFFFFF80ULL),
		cpu_to_le64(0xFFFFFE0000ULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x0FFFF00000ULL),
		cpu_to_le64(0x0FFFFFFC00ULL),
		cpu_to_le64(0x0ULL),
	पूर्ण,
	अणु
		cpu_to_le64(0x3FFFC00000ULL),
		cpu_to_le64(0x3FFFFFF000ULL),
		cpu_to_le64(0x0)
	पूर्ण,
	अणु
		cpu_to_le64(0xFFFE000000ULL),
		cpu_to_le64(0xFFFFFF8000ULL),
		cpu_to_le64(0x0)
	पूर्ण,
	अणु
		cpu_to_le64(0xFFF8000000ULL),
		cpu_to_le64(0xFFFFFE0000ULL),
		cpu_to_le64(0x0)
	पूर्ण,
	अणु
		cpu_to_le64(0xFE00000000ULL),
		cpu_to_le64(0x0ULL),
		cpu_to_le64(0x0ULL)
	पूर्ण,
पूर्ण;

अटल क्रमागत iwl_bt_coex_lut_type
iwl_get_coex_type(काष्ठा iwl_mvm *mvm, स्थिर काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	क्रमागत iwl_bt_coex_lut_type ret;
	u16 phy_ctx_id;
	u32 primary_ch_phy_id, secondary_ch_phy_id;

	/*
	 * Checking that we hold mvm->mutex is a good idea, but the rate
	 * control can't acquire the mutex since it runs in Tx path.
	 * So this is racy in that हाल, but in the worst हाल, the AMPDU
	 * size limit will be wrong क्रम a लघु समय which is not a big
	 * issue.
	 */

	rcu_पढ़ो_lock();

	chanctx_conf = rcu_dereference(vअगर->chanctx_conf);

	अगर (!chanctx_conf ||
	     chanctx_conf->def.chan->band != NL80211_BAND_2GHZ) अणु
		rcu_पढ़ो_unlock();
		वापस BT_COEX_INVALID_LUT;
	पूर्ण

	ret = BT_COEX_TX_DIS_LUT;

	अगर (mvm->cfg->bt_shared_single_ant) अणु
		rcu_पढ़ो_unlock();
		वापस ret;
	पूर्ण

	phy_ctx_id = *((u16 *)chanctx_conf->drv_priv);
	primary_ch_phy_id = le32_to_cpu(mvm->last_bt_ci_cmd.primary_ch_phy_id);
	secondary_ch_phy_id =
		le32_to_cpu(mvm->last_bt_ci_cmd.secondary_ch_phy_id);

	अगर (primary_ch_phy_id == phy_ctx_id)
		ret = le32_to_cpu(mvm->last_bt_notअगर.primary_ch_lut);
	अन्यथा अगर (secondary_ch_phy_id == phy_ctx_id)
		ret = le32_to_cpu(mvm->last_bt_notअगर.secondary_ch_lut);
	/* अन्यथा - शेष = TX TX disallowed */

	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_send_bt_init_conf(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_bt_coex_cmd bt_cmd = अणुपूर्ण;
	u32 mode;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (unlikely(mvm->bt_क्रमce_ant_mode != BT_FORCE_ANT_DIS)) अणु
		चयन (mvm->bt_क्रमce_ant_mode) अणु
		हाल BT_FORCE_ANT_BT:
			mode = BT_COEX_BT;
			अवरोध;
		हाल BT_FORCE_ANT_WIFI:
			mode = BT_COEX_WIFI;
			अवरोध;
		शेष:
			WARN_ON(1);
			mode = 0;
		पूर्ण

		bt_cmd.mode = cpu_to_le32(mode);
		जाओ send_cmd;
	पूर्ण

	bt_cmd.mode = cpu_to_le32(BT_COEX_NW);

	अगर (IWL_MVM_BT_COEX_SYNC2SCO)
		bt_cmd.enabled_modules |=
			cpu_to_le32(BT_COEX_SYNC2SCO_ENABLED);

	अगर (iwl_mvm_is_mplut_supported(mvm))
		bt_cmd.enabled_modules |= cpu_to_le32(BT_COEX_MPLUT_ENABLED);

	bt_cmd.enabled_modules |= cpu_to_le32(BT_COEX_HIGH_BAND_RET);

send_cmd:
	स_रखो(&mvm->last_bt_notअगर, 0, माप(mvm->last_bt_notअगर));
	स_रखो(&mvm->last_bt_ci_cmd, 0, माप(mvm->last_bt_ci_cmd));

	वापस iwl_mvm_send_cmd_pdu(mvm, BT_CONFIG, 0, माप(bt_cmd), &bt_cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_bt_coex_reduced_txp(काष्ठा iwl_mvm *mvm, u8 sta_id,
				       bool enable)
अणु
	काष्ठा iwl_bt_coex_reduced_txp_update_cmd cmd = अणुपूर्ण;
	काष्ठा iwl_mvm_sta *mvmsta;
	u32 value;

	mvmsta = iwl_mvm_sta_from_staid_रक्षित(mvm, sta_id);
	अगर (!mvmsta)
		वापस 0;

	/* nothing to करो */
	अगर (mvmsta->bt_reduced_txघातer == enable)
		वापस 0;

	value = mvmsta->sta_id;

	अगर (enable)
		value |= BT_REDUCED_TX_POWER_BIT;

	IWL_DEBUG_COEX(mvm, "%sable reduced Tx Power for sta %d\n",
		       enable ? "en" : "dis", sta_id);

	cmd.reduced_txp = cpu_to_le32(value);
	mvmsta->bt_reduced_txघातer = enable;

	वापस iwl_mvm_send_cmd_pdu(mvm, BT_COEX_UPDATE_REDUCED_TXP,
				    CMD_ASYNC, माप(cmd), &cmd);
पूर्ण

काष्ठा iwl_bt_iterator_data अणु
	काष्ठा iwl_bt_coex_profile_notअगर *notअगर;
	काष्ठा iwl_mvm *mvm;
	काष्ठा ieee80211_chanctx_conf *primary;
	काष्ठा ieee80211_chanctx_conf *secondary;
	bool primary_ll;
	u8 primary_load;
	u8 secondary_load;
पूर्ण;

अटल अंतरभूत
व्योम iwl_mvm_bt_coex_enable_rssi_event(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_vअगर *vअगर,
				       bool enable, पूर्णांक rssi)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	mvmvअगर->bf_data.last_bt_coex_event = rssi;
	mvmvअगर->bf_data.bt_coex_max_thold =
		enable ? -IWL_MVM_BT_COEX_EN_RED_TXP_THRESH : 0;
	mvmvअगर->bf_data.bt_coex_min_thold =
		enable ? -IWL_MVM_BT_COEX_DIS_RED_TXP_THRESH : 0;
पूर्ण

#घोषणा MVM_COEX_TCM_PERIOD (HZ * 10)

अटल व्योम iwl_mvm_bt_coex_tcm_based_ci(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_bt_iterator_data *data)
अणु
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (!समय_after(now, mvm->bt_coex_last_tcm_ts + MVM_COEX_TCM_PERIOD))
		वापस;

	mvm->bt_coex_last_tcm_ts = now;

	/* We assume here that we करोn't have more than 2 vअगरs on 2.4GHz */

	/* अगर the primary is low latency, it will stay primary */
	अगर (data->primary_ll)
		वापस;

	अगर (data->primary_load >= data->secondary_load)
		वापस;

	swap(data->primary, data->secondary);
पूर्ण

/* must be called under rcu_पढ़ो_lock */
अटल व्योम iwl_mvm_bt_notअगर_iterator(व्योम *_data, u8 *mac,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_bt_iterator_data *data = _data;
	काष्ठा iwl_mvm *mvm = data->mvm;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	/* शेष smps_mode is AUTOMATIC - only used क्रम client modes */
	क्रमागत ieee80211_smps_mode smps_mode = IEEE80211_SMPS_AUTOMATIC;
	u32 bt_activity_grading, min_ag_क्रम_अटल_smps;
	पूर्णांक ave_rssi;

	lockdep_निश्चित_held(&mvm->mutex);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		अगर (!mvmvअगर->ap_ibss_active)
			वापस;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	chanctx_conf = rcu_dereference(vअगर->chanctx_conf);

	/* If channel context is invalid or not on 2.4GHz .. */
	अगर ((!chanctx_conf ||
	     chanctx_conf->def.chan->band != NL80211_BAND_2GHZ)) अणु
		अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
			/* ... relax स्थिरraपूर्णांकs and disable rssi events */
			iwl_mvm_update_smps(mvm, vअगर, IWL_MVM_SMPS_REQ_BT_COEX,
					    smps_mode);
			iwl_mvm_bt_coex_reduced_txp(mvm, mvmvअगर->ap_sta_id,
						    false);
			iwl_mvm_bt_coex_enable_rssi_event(mvm, vअगर, false, 0);
		पूर्ण
		वापस;
	पूर्ण

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_COEX_SCHEMA_2))
		min_ag_क्रम_अटल_smps = BT_VERY_HIGH_TRAFFIC;
	अन्यथा
		min_ag_क्रम_अटल_smps = BT_HIGH_TRAFFIC;

	bt_activity_grading = le32_to_cpu(data->notअगर->bt_activity_grading);
	अगर (bt_activity_grading >= min_ag_क्रम_अटल_smps)
		smps_mode = IEEE80211_SMPS_STATIC;
	अन्यथा अगर (bt_activity_grading >= BT_LOW_TRAFFIC)
		smps_mode = IEEE80211_SMPS_DYNAMIC;

	/* relax SMPS स्थिरraपूर्णांकs क्रम next association */
	अगर (!vअगर->bss_conf.assoc)
		smps_mode = IEEE80211_SMPS_AUTOMATIC;

	अगर (mvmvअगर->phy_ctxt &&
	    (mvm->last_bt_notअगर.rrc_status & BIT(mvmvअगर->phy_ctxt->id)))
		smps_mode = IEEE80211_SMPS_AUTOMATIC;

	IWL_DEBUG_COEX(data->mvm,
		       "mac %d: bt_activity_grading %d smps_req %d\n",
		       mvmvअगर->id, bt_activity_grading, smps_mode);

	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		iwl_mvm_update_smps(mvm, vअगर, IWL_MVM_SMPS_REQ_BT_COEX,
				    smps_mode);

	/* low latency is always primary */
	अगर (iwl_mvm_vअगर_low_latency(mvmvअगर)) अणु
		data->primary_ll = true;

		data->secondary = data->primary;
		data->primary = chanctx_conf;
	पूर्ण

	अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
		अगर (!mvmvअगर->ap_ibss_active)
			वापस;

		अगर (chanctx_conf == data->primary)
			वापस;

		अगर (!data->primary_ll) अणु
			/*
			 * करोwngrade the current primary no matter what its
			 * type is.
			 */
			data->secondary = data->primary;
			data->primary = chanctx_conf;
		पूर्ण अन्यथा अणु
			/* there is low latency vअगर - we will be secondary */
			data->secondary = chanctx_conf;
		पूर्ण

		अगर (data->primary == chanctx_conf)
			data->primary_load = mvm->tcm.result.load[mvmvअगर->id];
		अन्यथा अगर (data->secondary == chanctx_conf)
			data->secondary_load = mvm->tcm.result.load[mvmvअगर->id];
		वापस;
	पूर्ण

	/*
	 * STA / P2P Client, try to be primary अगर first vअगर. If we are in low
	 * latency mode, we are alपढ़ोy in primary and just करोn't करो much
	 */
	अगर (!data->primary || data->primary == chanctx_conf)
		data->primary = chanctx_conf;
	अन्यथा अगर (!data->secondary)
		/* अगर secondary is not शून्य, it might be a GO */
		data->secondary = chanctx_conf;

	अगर (data->primary == chanctx_conf)
		data->primary_load = mvm->tcm.result.load[mvmvअगर->id];
	अन्यथा अगर (data->secondary == chanctx_conf)
		data->secondary_load = mvm->tcm.result.load[mvmvअगर->id];
	/*
	 * करोn't reduce the Tx घातer अगर one of these is true:
	 *  we are in LOOSE
	 *  single share antenna product
	 *  BT is inactive
	 *  we are not associated
	 */
	अगर (iwl_get_coex_type(mvm, vअगर) == BT_COEX_LOOSE_LUT ||
	    mvm->cfg->bt_shared_single_ant || !vअगर->bss_conf.assoc ||
	    le32_to_cpu(mvm->last_bt_notअगर.bt_activity_grading) == BT_OFF) अणु
		iwl_mvm_bt_coex_reduced_txp(mvm, mvmvअगर->ap_sta_id, false);
		iwl_mvm_bt_coex_enable_rssi_event(mvm, vअगर, false, 0);
		वापस;
	पूर्ण

	/* try to get the avg rssi from fw */
	ave_rssi = mvmvअगर->bf_data.ave_beacon_संकेत;

	/* अगर the RSSI isn't valid, fake it is very low */
	अगर (!ave_rssi)
		ave_rssi = -100;
	अगर (ave_rssi > -IWL_MVM_BT_COEX_EN_RED_TXP_THRESH) अणु
		अगर (iwl_mvm_bt_coex_reduced_txp(mvm, mvmvअगर->ap_sta_id, true))
			IWL_ERR(mvm, "Couldn't send BT_CONFIG cmd\n");
	पूर्ण अन्यथा अगर (ave_rssi < -IWL_MVM_BT_COEX_DIS_RED_TXP_THRESH) अणु
		अगर (iwl_mvm_bt_coex_reduced_txp(mvm, mvmvअगर->ap_sta_id, false))
			IWL_ERR(mvm, "Couldn't send BT_CONFIG cmd\n");
	पूर्ण

	/* Begin to monitor the RSSI: it may influence the reduced Tx घातer */
	iwl_mvm_bt_coex_enable_rssi_event(mvm, vअगर, true, ave_rssi);
पूर्ण

अटल व्योम iwl_mvm_bt_coex_notअगर_handle(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_bt_iterator_data data = अणु
		.mvm = mvm,
		.notअगर = &mvm->last_bt_notअगर,
	पूर्ण;
	काष्ठा iwl_bt_coex_ci_cmd cmd = अणुपूर्ण;
	u8 ci_bw_idx;

	/* Ignore updates अगर we are in क्रमce mode */
	अगर (unlikely(mvm->bt_क्रमce_ant_mode != BT_FORCE_ANT_DIS))
		वापस;

	rcu_पढ़ो_lock();
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
					mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_bt_notअगर_iterator, &data);

	iwl_mvm_bt_coex_tcm_based_ci(mvm, &data);

	अगर (data.primary) अणु
		काष्ठा ieee80211_chanctx_conf *chan = data.primary;
		अगर (WARN_ON(!chan->def.chan)) अणु
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण

		अगर (chan->def.width < NL80211_CHAN_WIDTH_40) अणु
			ci_bw_idx = 0;
		पूर्ण अन्यथा अणु
			अगर (chan->def.center_freq1 >
			    chan->def.chan->center_freq)
				ci_bw_idx = 2;
			अन्यथा
				ci_bw_idx = 1;
		पूर्ण

		cmd.bt_primary_ci =
			iwl_ci_mask[chan->def.chan->hw_value][ci_bw_idx];
		cmd.primary_ch_phy_id =
			cpu_to_le32(*((u16 *)data.primary->drv_priv));
	पूर्ण

	अगर (data.secondary) अणु
		काष्ठा ieee80211_chanctx_conf *chan = data.secondary;
		अगर (WARN_ON(!data.secondary->def.chan)) अणु
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण

		अगर (chan->def.width < NL80211_CHAN_WIDTH_40) अणु
			ci_bw_idx = 0;
		पूर्ण अन्यथा अणु
			अगर (chan->def.center_freq1 >
			    chan->def.chan->center_freq)
				ci_bw_idx = 2;
			अन्यथा
				ci_bw_idx = 1;
		पूर्ण

		cmd.bt_secondary_ci =
			iwl_ci_mask[chan->def.chan->hw_value][ci_bw_idx];
		cmd.secondary_ch_phy_id =
			cpu_to_le32(*((u16 *)data.secondary->drv_priv));
	पूर्ण

	rcu_पढ़ो_unlock();

	/* Don't spam the fw with the same command over and over */
	अगर (स_भेद(&cmd, &mvm->last_bt_ci_cmd, माप(cmd))) अणु
		अगर (iwl_mvm_send_cmd_pdu(mvm, BT_COEX_CI, 0,
					 माप(cmd), &cmd))
			IWL_ERR(mvm, "Failed to send BT_CI cmd\n");
		स_नकल(&mvm->last_bt_ci_cmd, &cmd, माप(cmd));
	पूर्ण
पूर्ण

व्योम iwl_mvm_rx_bt_coex_notअगर(काष्ठा iwl_mvm *mvm,
			      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_bt_coex_profile_notअगर *notअगर = (व्योम *)pkt->data;

	IWL_DEBUG_COEX(mvm, "BT Coex Notification received\n");
	IWL_DEBUG_COEX(mvm, "\tBT ci compliance %d\n", notअगर->bt_ci_compliance);
	IWL_DEBUG_COEX(mvm, "\tBT primary_ch_lut %d\n",
		       le32_to_cpu(notअगर->primary_ch_lut));
	IWL_DEBUG_COEX(mvm, "\tBT secondary_ch_lut %d\n",
		       le32_to_cpu(notअगर->secondary_ch_lut));
	IWL_DEBUG_COEX(mvm, "\tBT activity grading %d\n",
		       le32_to_cpu(notअगर->bt_activity_grading));

	/* remember this notअगरication क्रम future use: rssi fluctuations */
	स_नकल(&mvm->last_bt_notअगर, notअगर, माप(mvm->last_bt_notअगर));

	iwl_mvm_bt_coex_notअगर_handle(mvm);
पूर्ण

व्योम iwl_mvm_bt_rssi_event(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			   क्रमागत ieee80211_rssi_event_data rssi_event)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	/* Ignore updates अगर we are in क्रमce mode */
	अगर (unlikely(mvm->bt_क्रमce_ant_mode != BT_FORCE_ANT_DIS))
		वापस;

	/*
	 * Rssi update जबतक not associated - can happen since the statistics
	 * are handled asynchronously
	 */
	अगर (mvmvअगर->ap_sta_id == IWL_MVM_INVALID_STA)
		वापस;

	/* No BT - reports should be disabled */
	अगर (le32_to_cpu(mvm->last_bt_notअगर.bt_activity_grading) == BT_OFF)
		वापस;

	IWL_DEBUG_COEX(mvm, "RSSI for %pM is now %s\n", vअगर->bss_conf.bssid,
		       rssi_event == RSSI_EVENT_HIGH ? "HIGH" : "LOW");

	/*
	 * Check अगर rssi is good enough क्रम reduced Tx घातer, but not in loose
	 * scheme.
	 */
	अगर (rssi_event == RSSI_EVENT_LOW || mvm->cfg->bt_shared_single_ant ||
	    iwl_get_coex_type(mvm, vअगर) == BT_COEX_LOOSE_LUT)
		ret = iwl_mvm_bt_coex_reduced_txp(mvm, mvmvअगर->ap_sta_id,
						  false);
	अन्यथा
		ret = iwl_mvm_bt_coex_reduced_txp(mvm, mvmvअगर->ap_sta_id, true);

	अगर (ret)
		IWL_ERR(mvm, "couldn't send BT_CONFIG HCMD upon RSSI event\n");
पूर्ण

#घोषणा LINK_QUAL_AGG_TIME_LIMIT_DEF	(4000)
#घोषणा LINK_QUAL_AGG_TIME_LIMIT_BT_ACT	(1200)

u16 iwl_mvm_coex_agg_समय_limit(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvmsta->vअगर);
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt = mvmvअगर->phy_ctxt;
	क्रमागत iwl_bt_coex_lut_type lut_type;

	अगर (mvm->last_bt_notअगर.ttc_status & BIT(phy_ctxt->id))
		वापस LINK_QUAL_AGG_TIME_LIMIT_DEF;

	अगर (le32_to_cpu(mvm->last_bt_notअगर.bt_activity_grading) <
	    BT_HIGH_TRAFFIC)
		वापस LINK_QUAL_AGG_TIME_LIMIT_DEF;

	lut_type = iwl_get_coex_type(mvm, mvmsta->vअगर);

	अगर (lut_type == BT_COEX_LOOSE_LUT || lut_type == BT_COEX_INVALID_LUT)
		वापस LINK_QUAL_AGG_TIME_LIMIT_DEF;

	/* tight coex, high bt traffic, reduce AGG समय limit */
	वापस LINK_QUAL_AGG_TIME_LIMIT_BT_ACT;
पूर्ण

bool iwl_mvm_bt_coex_is_mimo_allowed(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvmsta->vअगर);
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt = mvmvअगर->phy_ctxt;
	क्रमागत iwl_bt_coex_lut_type lut_type;

	अगर (mvm->last_bt_notअगर.ttc_status & BIT(phy_ctxt->id))
		वापस true;

	अगर (le32_to_cpu(mvm->last_bt_notअगर.bt_activity_grading) <
	    BT_HIGH_TRAFFIC)
		वापस true;

	/*
	 * In Tight / TxTxDis, BT can't Rx जबतक we Tx, so use both antennas
	 * since BT is alपढ़ोy समाप्तed.
	 * In Loose, BT can Rx जबतक we Tx, so क्रमbid MIMO to let BT Rx जबतक
	 * we Tx.
	 * When we are in 5GHz, we'll get BT_COEX_INVALID_LUT allowing MIMO.
	 */
	lut_type = iwl_get_coex_type(mvm, mvmsta->vअगर);
	वापस lut_type != BT_COEX_LOOSE_LUT;
पूर्ण

bool iwl_mvm_bt_coex_is_ant_avail(काष्ठा iwl_mvm *mvm, u8 ant)
अणु
	/* there is no other antenna, shared antenna is always available */
	अगर (mvm->cfg->bt_shared_single_ant)
		वापस true;

	अगर (ant & mvm->cfg->non_shared_ant)
		वापस true;

	वापस le32_to_cpu(mvm->last_bt_notअगर.bt_activity_grading) <
		BT_HIGH_TRAFFIC;
पूर्ण

bool iwl_mvm_bt_coex_is_shared_ant_avail(काष्ठा iwl_mvm *mvm)
अणु
	/* there is no other antenna, shared antenna is always available */
	अगर (mvm->cfg->bt_shared_single_ant)
		वापस true;

	वापस le32_to_cpu(mvm->last_bt_notअगर.bt_activity_grading) < BT_HIGH_TRAFFIC;
पूर्ण

bool iwl_mvm_bt_coex_is_tpc_allowed(काष्ठा iwl_mvm *mvm,
				    क्रमागत nl80211_band band)
अणु
	u32 bt_activity = le32_to_cpu(mvm->last_bt_notअगर.bt_activity_grading);

	अगर (band != NL80211_BAND_2GHZ)
		वापस false;

	वापस bt_activity >= BT_LOW_TRAFFIC;
पूर्ण

u8 iwl_mvm_bt_coex_get_single_ant_msk(काष्ठा iwl_mvm *mvm, u8 enabled_ants)
अणु
	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_COEX_SCHEMA_2) &&
	    (mvm->cfg->non_shared_ant & enabled_ants))
		वापस mvm->cfg->non_shared_ant;

	वापस first_antenna(enabled_ants);
पूर्ण

u8 iwl_mvm_bt_coex_tx_prio(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_hdr *hdr,
			   काष्ठा ieee80211_tx_info *info, u8 ac)
अणु
	__le16 fc = hdr->frame_control;
	bool mplut_enabled = iwl_mvm_is_mplut_supported(mvm);

	अगर (info->band != NL80211_BAND_2GHZ)
		वापस 0;

	अगर (unlikely(mvm->bt_tx_prio))
		वापस mvm->bt_tx_prio - 1;

	अगर (likely(ieee80211_is_data(fc))) अणु
		अगर (likely(ieee80211_is_data_qos(fc))) अणु
			चयन (ac) अणु
			हाल IEEE80211_AC_BE:
				वापस mplut_enabled ? 1 : 0;
			हाल IEEE80211_AC_VI:
				वापस mplut_enabled ? 2 : 3;
			हाल IEEE80211_AC_VO:
				वापस 3;
			शेष:
				वापस 0;
			पूर्ण
		पूर्ण अन्यथा अगर (is_multicast_ether_addr(hdr->addr1)) अणु
			वापस 3;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अगर (ieee80211_is_mgmt(fc)) अणु
		वापस ieee80211_is_disassoc(fc) ? 0 : 3;
	पूर्ण अन्यथा अगर (ieee80211_is_ctl(fc)) अणु
		/* ignore cfend and cfendack frames as we never send those */
		वापस 3;
	पूर्ण

	वापस 0;
पूर्ण

व्योम iwl_mvm_bt_coex_vअगर_change(काष्ठा iwl_mvm *mvm)
अणु
	iwl_mvm_bt_coex_notअगर_handle(mvm);
पूर्ण
