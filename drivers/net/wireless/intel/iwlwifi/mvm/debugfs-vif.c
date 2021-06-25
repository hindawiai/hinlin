<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश "mvm.h"
#समावेश "debugfs.h"

अटल व्योम iwl_dbgfs_update_pm(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 क्रमागत iwl_dbgfs_pm_mask param, पूर्णांक val)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_dbgfs_pm *dbgfs_pm = &mvmvअगर->dbgfs_pm;

	dbgfs_pm->mask |= param;

	चयन (param) अणु
	हाल MVM_DEBUGFS_PM_KEEP_ALIVE: अणु
		पूर्णांक dtimper = vअगर->bss_conf.dtim_period ?: 1;
		पूर्णांक dtimper_msec = dtimper * vअगर->bss_conf.beacon_पूर्णांक;

		IWL_DEBUG_POWER(mvm, "debugfs: set keep_alive= %d sec\n", val);
		अगर (val * MSEC_PER_SEC < 3 * dtimper_msec)
			IWL_WARN(mvm,
				 "debugfs: keep alive period (%ld msec) is less than minimum required (%d msec)\n",
				 val * MSEC_PER_SEC, 3 * dtimper_msec);
		dbgfs_pm->keep_alive_seconds = val;
		अवरोध;
	पूर्ण
	हाल MVM_DEBUGFS_PM_SKIP_OVER_DTIM:
		IWL_DEBUG_POWER(mvm, "skip_over_dtim %s\n",
				val ? "enabled" : "disabled");
		dbgfs_pm->skip_over_dtim = val;
		अवरोध;
	हाल MVM_DEBUGFS_PM_SKIP_DTIM_PERIODS:
		IWL_DEBUG_POWER(mvm, "skip_dtim_periods=%d\n", val);
		dbgfs_pm->skip_dtim_periods = val;
		अवरोध;
	हाल MVM_DEBUGFS_PM_RX_DATA_TIMEOUT:
		IWL_DEBUG_POWER(mvm, "rx_data_timeout=%d\n", val);
		dbgfs_pm->rx_data_समयout = val;
		अवरोध;
	हाल MVM_DEBUGFS_PM_TX_DATA_TIMEOUT:
		IWL_DEBUG_POWER(mvm, "tx_data_timeout=%d\n", val);
		dbgfs_pm->tx_data_समयout = val;
		अवरोध;
	हाल MVM_DEBUGFS_PM_LPRX_ENA:
		IWL_DEBUG_POWER(mvm, "lprx %s\n", val ? "enabled" : "disabled");
		dbgfs_pm->lprx_ena = val;
		अवरोध;
	हाल MVM_DEBUGFS_PM_LPRX_RSSI_THRESHOLD:
		IWL_DEBUG_POWER(mvm, "lprx_rssi_threshold=%d\n", val);
		dbgfs_pm->lprx_rssi_threshold = val;
		अवरोध;
	हाल MVM_DEBUGFS_PM_SNOOZE_ENABLE:
		IWL_DEBUG_POWER(mvm, "snooze_enable=%d\n", val);
		dbgfs_pm->snooze_ena = val;
		अवरोध;
	हाल MVM_DEBUGFS_PM_UAPSD_MISBEHAVING:
		IWL_DEBUG_POWER(mvm, "uapsd_misbehaving_enable=%d\n", val);
		dbgfs_pm->uapsd_misbehaving = val;
		अवरोध;
	हाल MVM_DEBUGFS_PM_USE_PS_POLL:
		IWL_DEBUG_POWER(mvm, "use_ps_poll=%d\n", val);
		dbgfs_pm->use_ps_poll = val;
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_pm_params_ग_लिखो(काष्ठा ieee80211_vअगर *vअगर, अक्षर *buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	क्रमागत iwl_dbgfs_pm_mask param;
	पूर्णांक val, ret;

	अगर (!म_भेदन("keep_alive=", buf, 11)) अणु
		अगर (माला_पूछो(buf + 11, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_KEEP_ALIVE;
	पूर्ण अन्यथा अगर (!म_भेदन("skip_over_dtim=", buf, 15)) अणु
		अगर (माला_पूछो(buf + 15, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_SKIP_OVER_DTIM;
	पूर्ण अन्यथा अगर (!म_भेदन("skip_dtim_periods=", buf, 18)) अणु
		अगर (माला_पूछो(buf + 18, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_SKIP_DTIM_PERIODS;
	पूर्ण अन्यथा अगर (!म_भेदन("rx_data_timeout=", buf, 16)) अणु
		अगर (माला_पूछो(buf + 16, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_RX_DATA_TIMEOUT;
	पूर्ण अन्यथा अगर (!म_भेदन("tx_data_timeout=", buf, 16)) अणु
		अगर (माला_पूछो(buf + 16, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_TX_DATA_TIMEOUT;
	पूर्ण अन्यथा अगर (!म_भेदन("lprx=", buf, 5)) अणु
		अगर (माला_पूछो(buf + 5, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_LPRX_ENA;
	पूर्ण अन्यथा अगर (!म_भेदन("lprx_rssi_threshold=", buf, 20)) अणु
		अगर (माला_पूछो(buf + 20, "%d", &val) != 1)
			वापस -EINVAL;
		अगर (val > POWER_LPRX_RSSI_THRESHOLD_MAX || val <
		    POWER_LPRX_RSSI_THRESHOLD_MIN)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_LPRX_RSSI_THRESHOLD;
	पूर्ण अन्यथा अगर (!म_भेदन("snooze_enable=", buf, 14)) अणु
		अगर (माला_पूछो(buf + 14, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_SNOOZE_ENABLE;
	पूर्ण अन्यथा अगर (!म_भेदन("uapsd_misbehaving=", buf, 18)) अणु
		अगर (माला_पूछो(buf + 18, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_UAPSD_MISBEHAVING;
	पूर्ण अन्यथा अगर (!म_भेदन("use_ps_poll=", buf, 12)) अणु
		अगर (माला_पूछो(buf + 12, "%d", &val) != 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_PM_USE_PS_POLL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&mvm->mutex);
	iwl_dbgfs_update_pm(mvm, vअगर, param, val);
	ret = iwl_mvm_घातer_update_mac(mvm);
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_tx_pwr_lmt_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	अक्षर buf[64];
	पूर्णांक bufsz = माप(buf);
	पूर्णांक pos;

	pos = scnम_लिखो(buf, bufsz, "bss limit = %d\n",
			vअगर->bss_conf.txघातer);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_pm_params_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	अक्षर buf[512];
	पूर्णांक bufsz = माप(buf);
	पूर्णांक pos;

	pos = iwl_mvm_घातer_mac_dbgfs_पढ़ो(mvm, vअगर, buf, bufsz);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_mac_params_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	u8 ap_sta_id;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	अक्षर buf[512];
	पूर्णांक bufsz = माप(buf);
	पूर्णांक pos = 0;
	पूर्णांक i;

	mutex_lock(&mvm->mutex);

	ap_sta_id = mvmvअगर->ap_sta_id;

	चयन (ieee80211_vअगर_type_p2p(vअगर)) अणु
	हाल NL80211_IFTYPE_ADHOC:
		pos += scnम_लिखो(buf+pos, bufsz-pos, "type: ibss\n");
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		pos += scnम_लिखो(buf+pos, bufsz-pos, "type: bss\n");
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		pos += scnम_लिखो(buf+pos, bufsz-pos, "type: ap\n");
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		pos += scnम_लिखो(buf+pos, bufsz-pos, "type: p2p client\n");
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		pos += scnम_लिखो(buf+pos, bufsz-pos, "type: p2p go\n");
		अवरोध;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		pos += scnम_लिखो(buf+pos, bufsz-pos, "type: p2p dev\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	pos += scnम_लिखो(buf+pos, bufsz-pos, "mac id/color: %d / %d\n",
			 mvmvअगर->id, mvmvअगर->color);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bssid: %pM\n",
			 vअगर->bss_conf.bssid);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "Load: %d\n",
			 mvm->tcm.result.load[mvmvअगर->id]);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "QoS:\n");
	क्रम (i = 0; i < ARRAY_SIZE(mvmvअगर->queue_params); i++)
		pos += scnम_लिखो(buf+pos, bufsz-pos,
				 "\t%d: txop:%d - cw_min:%d - cw_max = %d - aifs = %d upasd = %d\n",
				 i, mvmvअगर->queue_params[i].txop,
				 mvmvअगर->queue_params[i].cw_min,
				 mvmvअगर->queue_params[i].cw_max,
				 mvmvअगर->queue_params[i].aअगरs,
				 mvmvअगर->queue_params[i].uapsd);

	अगर (vअगर->type == NL80211_IFTYPE_STATION &&
	    ap_sta_id != IWL_MVM_INVALID_STA) अणु
		काष्ठा iwl_mvm_sta *mvm_sta;

		mvm_sta = iwl_mvm_sta_from_staid_रक्षित(mvm, ap_sta_id);
		अगर (mvm_sta) अणु
			pos += scnम_लिखो(buf+pos, bufsz-pos,
					 "ap_sta_id %d - reduced Tx power %d\n",
					 ap_sta_id,
					 mvm_sta->bt_reduced_txघातer);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(vअगर->chanctx_conf);
	अगर (chanctx_conf)
		pos += scnम_लिखो(buf+pos, bufsz-pos,
				 "idle rx chains %d, active rx chains: %d\n",
				 chanctx_conf->rx_chains_अटल,
				 chanctx_conf->rx_chains_dynamic);
	rcu_पढ़ो_unlock();

	mutex_unlock(&mvm->mutex);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल व्योम iwl_dbgfs_update_bf(काष्ठा ieee80211_vअगर *vअगर,
				क्रमागत iwl_dbgfs_bf_mask param, पूर्णांक value)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_dbgfs_bf *dbgfs_bf = &mvmvअगर->dbgfs_bf;

	dbgfs_bf->mask |= param;

	चयन (param) अणु
	हाल MVM_DEBUGFS_BF_ENERGY_DELTA:
		dbgfs_bf->bf_energy_delta = value;
		अवरोध;
	हाल MVM_DEBUGFS_BF_ROAMING_ENERGY_DELTA:
		dbgfs_bf->bf_roaming_energy_delta = value;
		अवरोध;
	हाल MVM_DEBUGFS_BF_ROAMING_STATE:
		dbgfs_bf->bf_roaming_state = value;
		अवरोध;
	हाल MVM_DEBUGFS_BF_TEMP_THRESHOLD:
		dbgfs_bf->bf_temp_threshold = value;
		अवरोध;
	हाल MVM_DEBUGFS_BF_TEMP_FAST_FILTER:
		dbgfs_bf->bf_temp_fast_filter = value;
		अवरोध;
	हाल MVM_DEBUGFS_BF_TEMP_SLOW_FILTER:
		dbgfs_bf->bf_temp_slow_filter = value;
		अवरोध;
	हाल MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER:
		dbgfs_bf->bf_enable_beacon_filter = value;
		अवरोध;
	हाल MVM_DEBUGFS_BF_DEBUG_FLAG:
		dbgfs_bf->bf_debug_flag = value;
		अवरोध;
	हाल MVM_DEBUGFS_BF_ESCAPE_TIMER:
		dbgfs_bf->bf_escape_समयr = value;
		अवरोध;
	हाल MVM_DEBUGFS_BA_ENABLE_BEACON_ABORT:
		dbgfs_bf->ba_enable_beacon_पात = value;
		अवरोध;
	हाल MVM_DEBUGFS_BA_ESCAPE_TIMER:
		dbgfs_bf->ba_escape_समयr = value;
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_bf_params_ग_लिखो(काष्ठा ieee80211_vअगर *vअगर, अक्षर *buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	क्रमागत iwl_dbgfs_bf_mask param;
	पूर्णांक value, ret = 0;

	अगर (!म_भेदन("bf_energy_delta=", buf, 16)) अणु
		अगर (माला_पूछो(buf+16, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < IWL_BF_ENERGY_DELTA_MIN ||
		    value > IWL_BF_ENERGY_DELTA_MAX)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_ENERGY_DELTA;
	पूर्ण अन्यथा अगर (!म_भेदन("bf_roaming_energy_delta=", buf, 24)) अणु
		अगर (माला_पूछो(buf+24, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < IWL_BF_ROAMING_ENERGY_DELTA_MIN ||
		    value > IWL_BF_ROAMING_ENERGY_DELTA_MAX)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_ROAMING_ENERGY_DELTA;
	पूर्ण अन्यथा अगर (!म_भेदन("bf_roaming_state=", buf, 17)) अणु
		अगर (माला_पूछो(buf+17, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < IWL_BF_ROAMING_STATE_MIN ||
		    value > IWL_BF_ROAMING_STATE_MAX)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_ROAMING_STATE;
	पूर्ण अन्यथा अगर (!म_भेदन("bf_temp_threshold=", buf, 18)) अणु
		अगर (माला_पूछो(buf+18, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < IWL_BF_TEMP_THRESHOLD_MIN ||
		    value > IWL_BF_TEMP_THRESHOLD_MAX)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_TEMP_THRESHOLD;
	पूर्ण अन्यथा अगर (!म_भेदन("bf_temp_fast_filter=", buf, 20)) अणु
		अगर (माला_पूछो(buf+20, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < IWL_BF_TEMP_FAST_FILTER_MIN ||
		    value > IWL_BF_TEMP_FAST_FILTER_MAX)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_TEMP_FAST_FILTER;
	पूर्ण अन्यथा अगर (!म_भेदन("bf_temp_slow_filter=", buf, 20)) अणु
		अगर (माला_पूछो(buf+20, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < IWL_BF_TEMP_SLOW_FILTER_MIN ||
		    value > IWL_BF_TEMP_SLOW_FILTER_MAX)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_TEMP_SLOW_FILTER;
	पूर्ण अन्यथा अगर (!म_भेदन("bf_enable_beacon_filter=", buf, 24)) अणु
		अगर (माला_पूछो(buf+24, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < 0 || value > 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER;
	पूर्ण अन्यथा अगर (!म_भेदन("bf_debug_flag=", buf, 14)) अणु
		अगर (माला_पूछो(buf+14, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < 0 || value > 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_DEBUG_FLAG;
	पूर्ण अन्यथा अगर (!म_भेदन("bf_escape_timer=", buf, 16)) अणु
		अगर (माला_पूछो(buf+16, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < IWL_BF_ESCAPE_TIMER_MIN ||
		    value > IWL_BF_ESCAPE_TIMER_MAX)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BF_ESCAPE_TIMER;
	पूर्ण अन्यथा अगर (!म_भेदन("ba_escape_timer=", buf, 16)) अणु
		अगर (माला_पूछो(buf+16, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < IWL_BA_ESCAPE_TIMER_MIN ||
		    value > IWL_BA_ESCAPE_TIMER_MAX)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BA_ESCAPE_TIMER;
	पूर्ण अन्यथा अगर (!म_भेदन("ba_enable_beacon_abort=", buf, 23)) अणु
		अगर (माला_पूछो(buf+23, "%d", &value) != 1)
			वापस -EINVAL;
		अगर (value < 0 || value > 1)
			वापस -EINVAL;
		param = MVM_DEBUGFS_BA_ENABLE_BEACON_ABORT;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&mvm->mutex);
	iwl_dbgfs_update_bf(vअगर, param, value);
	अगर (param == MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER && !value)
		ret = iwl_mvm_disable_beacon_filter(mvm, vअगर, 0);
	अन्यथा
		ret = iwl_mvm_enable_beacon_filter(mvm, vअगर, 0);
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_bf_params_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	अक्षर buf[256];
	पूर्णांक pos = 0;
	स्थिर माप_प्रकार bufsz = माप(buf);
	काष्ठा iwl_beacon_filter_cmd cmd = अणु
		IWL_BF_CMD_CONFIG_DEFAULTS,
		.bf_enable_beacon_filter =
			cpu_to_le32(IWL_BF_ENABLE_BEACON_FILTER_DEFAULT),
		.ba_enable_beacon_पात =
			cpu_to_le32(IWL_BA_ENABLE_BEACON_ABORT_DEFAULT),
	पूर्ण;

	iwl_mvm_beacon_filter_debugfs_parameters(vअगर, &cmd);
	अगर (mvmvअगर->bf_data.bf_enabled)
		cmd.bf_enable_beacon_filter = cpu_to_le32(1);
	अन्यथा
		cmd.bf_enable_beacon_filter = 0;

	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_energy_delta = %d\n",
			 le32_to_cpu(cmd.bf_energy_delta));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_roaming_energy_delta = %d\n",
			 le32_to_cpu(cmd.bf_roaming_energy_delta));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_roaming_state = %d\n",
			 le32_to_cpu(cmd.bf_roaming_state));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_temp_threshold = %d\n",
			 le32_to_cpu(cmd.bf_temp_threshold));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_temp_fast_filter = %d\n",
			 le32_to_cpu(cmd.bf_temp_fast_filter));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_temp_slow_filter = %d\n",
			 le32_to_cpu(cmd.bf_temp_slow_filter));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_enable_beacon_filter = %d\n",
			 le32_to_cpu(cmd.bf_enable_beacon_filter));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_debug_flag = %d\n",
			 le32_to_cpu(cmd.bf_debug_flag));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "bf_escape_timer = %d\n",
			 le32_to_cpu(cmd.bf_escape_समयr));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "ba_escape_timer = %d\n",
			 le32_to_cpu(cmd.ba_escape_समयr));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "ba_enable_beacon_abort = %d\n",
			 le32_to_cpu(cmd.ba_enable_beacon_पात));

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल अंतरभूत अक्षर *iwl_dbgfs_is_match(अक्षर *name, अक्षर *buf)
अणु
	पूर्णांक len = म_माप(name);

	वापस !म_भेदन(name, buf, len) ? buf + len : शून्य;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_os_device_समयdअगरf_पढ़ो(काष्ठा file *file,
						 अक्षर __user *user_buf,
						 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	u32 curr_gp2;
	u64 curr_os;
	s64 dअगरf;
	अक्षर buf[64];
	स्थिर माप_प्रकार bufsz = माप(buf);
	पूर्णांक pos = 0;

	mutex_lock(&mvm->mutex);
	iwl_mvm_get_sync_समय(mvm, &curr_gp2, &curr_os);
	mutex_unlock(&mvm->mutex);

	करो_भाग(curr_os, NSEC_PER_USEC);
	dअगरf = curr_os - curr_gp2;
	pos += scnम_लिखो(buf + pos, bufsz - pos, "diff=%lld\n", dअगरf);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_low_latency_ग_लिखो(काष्ठा ieee80211_vअगर *vअगर, अक्षर *buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	u8 value;
	पूर्णांक ret;

	ret = kstrtou8(buf, 0, &value);
	अगर (ret)
		वापस ret;
	अगर (value > 1)
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);
	iwl_mvm_update_low_latency(mvm, vअगर, value, LOW_LATENCY_DEBUGFS);
	mutex_unlock(&mvm->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
iwl_dbgfs_low_latency_क्रमce_ग_लिखो(काष्ठा ieee80211_vअगर *vअगर, अक्षर *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	u8 value;
	पूर्णांक ret;

	ret = kstrtou8(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर (value > NUM_LOW_LATENCY_FORCE)
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);
	अगर (value == LOW_LATENCY_FORCE_UNSET) अणु
		iwl_mvm_update_low_latency(mvm, vअगर, false,
					   LOW_LATENCY_DEBUGFS_FORCE);
		iwl_mvm_update_low_latency(mvm, vअगर, false,
					   LOW_LATENCY_DEBUGFS_FORCE_ENABLE);
	पूर्ण अन्यथा अणु
		iwl_mvm_update_low_latency(mvm, vअगर,
					   value == LOW_LATENCY_FORCE_ON,
					   LOW_LATENCY_DEBUGFS_FORCE);
		iwl_mvm_update_low_latency(mvm, vअगर, true,
					   LOW_LATENCY_DEBUGFS_FORCE_ENABLE);
	पूर्ण
	mutex_unlock(&mvm->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_low_latency_पढ़ो(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	अक्षर क्रमmat[] = "traffic=%d\ndbgfs=%d\nvcmd=%d\nvif_type=%d\n"
			"dbgfs_force_enable=%d\ndbgfs_force=%d\nactual=%d\n";

	/*
	 * all values in क्रमmat are boolean so the size of क्रमmat is enough
	 * क्रम holding the result string
	 */
	अक्षर buf[माप(क्रमmat) + 1] = अणुपूर्ण;
	पूर्णांक len;

	len = scnम_लिखो(buf, माप(buf) - 1, क्रमmat,
			!!(mvmvअगर->low_latency & LOW_LATENCY_TRAFFIC),
			!!(mvmvअगर->low_latency & LOW_LATENCY_DEBUGFS),
			!!(mvmvअगर->low_latency & LOW_LATENCY_VCMD),
			!!(mvmvअगर->low_latency & LOW_LATENCY_VIF_TYPE),
			!!(mvmvअगर->low_latency &
			   LOW_LATENCY_DEBUGFS_FORCE_ENABLE),
			!!(mvmvअगर->low_latency & LOW_LATENCY_DEBUGFS_FORCE),
			!!(mvmvअगर->low_latency_actual));
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_uapsd_misbehaving_पढ़ो(काष्ठा file *file,
						अक्षर __user *user_buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	अक्षर buf[20];
	पूर्णांक len;

	len = प्र_लिखो(buf, "%pM\n", mvmvअगर->uapsd_misbehaving_bssid);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_uapsd_misbehaving_ग_लिखो(काष्ठा ieee80211_vअगर *vअगर,
						 अक्षर *buf, माप_प्रकार count,
						 loff_t *ppos)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	bool ret;

	mutex_lock(&mvm->mutex);
	ret = mac_pton(buf, mvmvअगर->uapsd_misbehaving_bssid);
	mutex_unlock(&mvm->mutex);

	वापस ret ? count : -EINVAL;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rx_phyinfo_ग_लिखो(काष्ठा ieee80211_vअगर *vअगर, अक्षर *buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt;
	u16 value;
	पूर्णांक ret;

	ret = kstrtou16(buf, 0, &value);
	अगर (ret)
		वापस ret;

	mutex_lock(&mvm->mutex);
	rcu_पढ़ो_lock();

	chanctx_conf = rcu_dereference(vअगर->chanctx_conf);
	/* make sure the channel context is asचिन्हित */
	अगर (!chanctx_conf) अणु
		rcu_पढ़ो_unlock();
		mutex_unlock(&mvm->mutex);
		वापस -EINVAL;
	पूर्ण

	phy_ctxt = &mvm->phy_ctxts[*(u16 *)chanctx_conf->drv_priv];
	rcu_पढ़ो_unlock();

	mvm->dbgfs_rx_phyinfo = value;

	ret = iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, &chanctx_conf->min_def,
				       chanctx_conf->rx_chains_अटल,
				       chanctx_conf->rx_chains_dynamic);
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_rx_phyinfo_पढ़ो(काष्ठा file *file,
					 अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	अक्षर buf[8];
	पूर्णांक len;

	len = scnम_लिखो(buf, माप(buf), "0x%04x\n",
			mvmvअगर->mvm->dbgfs_rx_phyinfo);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

अटल व्योम iwl_dbgfs_quota_check(व्योम *data, u8 *mac,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक *ret = data;

	अगर (mvmvअगर->dbgfs_quota_min)
		*ret = -EINVAL;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_quota_min_ग_लिखो(काष्ठा ieee80211_vअगर *vअगर, अक्षर *buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm *mvm = mvmvअगर->mvm;
	u16 value;
	पूर्णांक ret;

	ret = kstrtou16(buf, 0, &value);
	अगर (ret)
		वापस ret;

	अगर (value > 95)
		वापस -EINVAL;

	mutex_lock(&mvm->mutex);

	mvmvअगर->dbgfs_quota_min = 0;
	ieee80211_iterate_पूर्णांकerfaces(mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
				     iwl_dbgfs_quota_check, &ret);
	अगर (ret == 0) अणु
		mvmvअगर->dbgfs_quota_min = value;
		iwl_mvm_update_quotas(mvm, false, शून्य);
	पूर्ण
	mutex_unlock(&mvm->mutex);

	वापस ret ?: count;
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_quota_min_पढ़ो(काष्ठा file *file,
					अक्षर __user *user_buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा ieee80211_vअगर *vअगर = file->निजी_data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	अक्षर buf[10];
	पूर्णांक len;

	len = scnम_लिखो(buf, माप(buf), "%d\n", mvmvअगर->dbgfs_quota_min);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, len);
पूर्ण

#घोषणा MVM_DEBUGFS_WRITE_खाता_OPS(name, bufsz) \
	_MVM_DEBUGFS_WRITE_खाता_OPS(name, bufsz, काष्ठा ieee80211_vअगर)
#घोषणा MVM_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz) \
	_MVM_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz, काष्ठा ieee80211_vअगर)
#घोषणा MVM_DEBUGFS_ADD_खाता_VIF(name, parent, mode) करो अणु		\
		debugfs_create_file(#name, mode, parent, vअगर,		\
				    &iwl_dbgfs_##name##_ops);		\
	पूर्ण जबतक (0)

MVM_DEBUGFS_READ_खाता_OPS(mac_params);
MVM_DEBUGFS_READ_खाता_OPS(tx_pwr_lmt);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(pm_params, 32);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(bf_params, 256);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(low_latency, 10);
MVM_DEBUGFS_WRITE_खाता_OPS(low_latency_क्रमce, 10);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(uapsd_misbehaving, 20);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(rx_phyinfo, 10);
MVM_DEBUGFS_READ_WRITE_खाता_OPS(quota_min, 32);
MVM_DEBUGFS_READ_खाता_OPS(os_device_समयdअगरf);


व्योम iwl_mvm_vअगर_dbgfs_रेजिस्टर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा dentry *dbgfs_dir = vअगर->debugfs_dir;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	अक्षर buf[100];

	/*
	 * Check अगर debugfs directory alपढ़ोy exist beक्रमe creating it.
	 * This may happen when, क्रम example, resetting hw or suspend-resume
	 */
	अगर (!dbgfs_dir || mvmvअगर->dbgfs_dir)
		वापस;

	mvmvअगर->dbgfs_dir = debugfs_create_dir("iwlmvm", dbgfs_dir);
	अगर (IS_ERR_OR_शून्य(mvmvअगर->dbgfs_dir)) अणु
		IWL_ERR(mvm, "Failed to create debugfs directory under %pd\n",
			dbgfs_dir);
		वापस;
	पूर्ण

	अगर (iwlmvm_mod_params.घातer_scheme != IWL_POWER_SCHEME_CAM &&
	    ((vअगर->type == NL80211_IFTYPE_STATION && !vअगर->p2p) ||
	     (vअगर->type == NL80211_IFTYPE_STATION && vअगर->p2p)))
		MVM_DEBUGFS_ADD_खाता_VIF(pm_params, mvmvअगर->dbgfs_dir, 0600);

	MVM_DEBUGFS_ADD_खाता_VIF(tx_pwr_lmt, mvmvअगर->dbgfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता_VIF(mac_params, mvmvअगर->dbgfs_dir, 0400);
	MVM_DEBUGFS_ADD_खाता_VIF(low_latency, mvmvअगर->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता_VIF(low_latency_क्रमce, mvmvअगर->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता_VIF(uapsd_misbehaving, mvmvअगर->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता_VIF(rx_phyinfo, mvmvअगर->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता_VIF(quota_min, mvmvअगर->dbgfs_dir, 0600);
	MVM_DEBUGFS_ADD_खाता_VIF(os_device_समयdअगरf, mvmvअगर->dbgfs_dir, 0400);

	अगर (vअगर->type == NL80211_IFTYPE_STATION && !vअगर->p2p &&
	    mvmvअगर == mvm->bf_allowed_vअगर)
		MVM_DEBUGFS_ADD_खाता_VIF(bf_params, mvmvअगर->dbgfs_dir, 0600);

	/*
	 * Create symlink क्रम convenience poपूर्णांकing to पूर्णांकerface specअगरic
	 * debugfs entries क्रम the driver. For example, under
	 * /sys/kernel/debug/iwlwअगरi/0000\:02\:00.0/iwlmvm/
	 * find
	 * netdev:wlan0 -> ../../../ieee80211/phy0/netdev:wlan0/iwlmvm/
	 */
	snम_लिखो(buf, 100, "../../../%pd3/%pd",
		 dbgfs_dir,
		 mvmvअगर->dbgfs_dir);

	mvmvअगर->dbgfs_slink = debugfs_create_symlink(dbgfs_dir->d_name.name,
						     mvm->debugfs_dir, buf);
पूर्ण

व्योम iwl_mvm_vअगर_dbgfs_clean(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	debugfs_हटाओ(mvmvअगर->dbgfs_slink);
	mvmvअगर->dbgfs_slink = शून्य;

	debugfs_हटाओ_recursive(mvmvअगर->dbgfs_dir);
	mvmvअगर->dbgfs_dir = शून्य;
पूर्ण
