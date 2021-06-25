<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/etherdevice.h>

#समावेश <net/mac80211.h>

#समावेश "iwl-debug.h"
#समावेश "mvm.h"
#समावेश "iwl-modparams.h"
#समावेश "fw/api/power.h"

#घोषणा POWER_KEEP_ALIVE_PERIOD_SEC    25

अटल
पूर्णांक iwl_mvm_beacon_filter_send_cmd(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_beacon_filter_cmd *cmd,
				   u32 flags)
अणु
	u16 len;

	IWL_DEBUG_POWER(mvm, "ba_enable_beacon_abort is: %d\n",
			le32_to_cpu(cmd->ba_enable_beacon_पात));
	IWL_DEBUG_POWER(mvm, "ba_escape_timer is: %d\n",
			le32_to_cpu(cmd->ba_escape_समयr));
	IWL_DEBUG_POWER(mvm, "bf_debug_flag is: %d\n",
			le32_to_cpu(cmd->bf_debug_flag));
	IWL_DEBUG_POWER(mvm, "bf_enable_beacon_filter is: %d\n",
			le32_to_cpu(cmd->bf_enable_beacon_filter));
	IWL_DEBUG_POWER(mvm, "bf_energy_delta is: %d\n",
			le32_to_cpu(cmd->bf_energy_delta));
	IWL_DEBUG_POWER(mvm, "bf_escape_timer is: %d\n",
			le32_to_cpu(cmd->bf_escape_समयr));
	IWL_DEBUG_POWER(mvm, "bf_roaming_energy_delta is: %d\n",
			le32_to_cpu(cmd->bf_roaming_energy_delta));
	IWL_DEBUG_POWER(mvm, "bf_roaming_state is: %d\n",
			le32_to_cpu(cmd->bf_roaming_state));
	IWL_DEBUG_POWER(mvm, "bf_temp_threshold is: %d\n",
			le32_to_cpu(cmd->bf_temp_threshold));
	IWL_DEBUG_POWER(mvm, "bf_temp_fast_filter is: %d\n",
			le32_to_cpu(cmd->bf_temp_fast_filter));
	IWL_DEBUG_POWER(mvm, "bf_temp_slow_filter is: %d\n",
			le32_to_cpu(cmd->bf_temp_slow_filter));
	IWL_DEBUG_POWER(mvm, "bf_threshold_absolute_low is: %d, %d\n",
			le32_to_cpu(cmd->bf_threshold_असलolute_low[0]),
			le32_to_cpu(cmd->bf_threshold_असलolute_low[1]));

	IWL_DEBUG_POWER(mvm, "bf_threshold_absolute_high is: %d, %d\n",
			le32_to_cpu(cmd->bf_threshold_असलolute_high[0]),
			le32_to_cpu(cmd->bf_threshold_असलolute_high[1]));

	अगर (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_BEACON_FILTER_V4))
		len = माप(काष्ठा iwl_beacon_filter_cmd);
	अन्यथा
		len = दुरत्व(काष्ठा iwl_beacon_filter_cmd,
			       bf_threshold_असलolute_low);

	वापस iwl_mvm_send_cmd_pdu(mvm, REPLY_BEACON_FILTERING_CMD, flags,
				    len, cmd);
पूर्ण

अटल
व्योम iwl_mvm_beacon_filter_set_cqm_params(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा iwl_beacon_filter_cmd *cmd)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (vअगर->bss_conf.cqm_rssi_thold) अणु
		cmd->bf_energy_delta =
			cpu_to_le32(vअगर->bss_conf.cqm_rssi_hyst);
		/* fw uses an असलolute value क्रम this */
		cmd->bf_roaming_state =
			cpu_to_le32(-vअगर->bss_conf.cqm_rssi_thold);
	पूर्ण
	cmd->ba_enable_beacon_पात = cpu_to_le32(mvmvअगर->bf_data.ba_enabled);
पूर्ण

अटल व्योम iwl_mvm_घातer_log(काष्ठा iwl_mvm *mvm,
			      काष्ठा iwl_mac_घातer_cmd *cmd)
अणु
	IWL_DEBUG_POWER(mvm,
			"Sending power table command on mac id 0x%X for power level %d, flags = 0x%X\n",
			cmd->id_and_color, iwlmvm_mod_params.घातer_scheme,
			le16_to_cpu(cmd->flags));
	IWL_DEBUG_POWER(mvm, "Keep alive = %u sec\n",
			le16_to_cpu(cmd->keep_alive_seconds));

	अगर (!(cmd->flags & cpu_to_le16(POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK))) अणु
		IWL_DEBUG_POWER(mvm, "Disable power management\n");
		वापस;
	पूर्ण

	IWL_DEBUG_POWER(mvm, "Rx timeout = %u usec\n",
			le32_to_cpu(cmd->rx_data_समयout));
	IWL_DEBUG_POWER(mvm, "Tx timeout = %u usec\n",
			le32_to_cpu(cmd->tx_data_समयout));
	अगर (cmd->flags & cpu_to_le16(POWER_FLAGS_SKIP_OVER_DTIM_MSK))
		IWL_DEBUG_POWER(mvm, "DTIM periods to skip = %u\n",
				cmd->skip_dtim_periods);
	अगर (cmd->flags & cpu_to_le16(POWER_FLAGS_LPRX_ENA_MSK))
		IWL_DEBUG_POWER(mvm, "LP RX RSSI threshold = %u\n",
				cmd->lprx_rssi_threshold);
	अगर (cmd->flags & cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK)) अणु
		IWL_DEBUG_POWER(mvm, "uAPSD enabled\n");
		IWL_DEBUG_POWER(mvm, "Rx timeout (uAPSD) = %u usec\n",
				le32_to_cpu(cmd->rx_data_समयout_uapsd));
		IWL_DEBUG_POWER(mvm, "Tx timeout (uAPSD) = %u usec\n",
				le32_to_cpu(cmd->tx_data_समयout_uapsd));
		IWL_DEBUG_POWER(mvm, "QNDP TID = %d\n", cmd->qndp_tid);
		IWL_DEBUG_POWER(mvm, "ACs flags = 0x%x\n", cmd->uapsd_ac_flags);
		IWL_DEBUG_POWER(mvm, "Max SP = %d\n", cmd->uapsd_max_sp);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_घातer_configure_uapsd(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा iwl_mac_घातer_cmd *cmd)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	क्रमागत ieee80211_ac_numbers ac;
	bool tid_found = false;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	/* set advanced pm flag with no uapsd ACs to enable ps-poll */
	अगर (mvmvअगर->dbgfs_pm.use_ps_poll) अणु
		cmd->flags |= cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK);
		वापस;
	पूर्ण
#पूर्ण_अगर

	क्रम (ac = IEEE80211_AC_VO; ac <= IEEE80211_AC_BK; ac++) अणु
		अगर (!mvmvअगर->queue_params[ac].uapsd)
			जारी;

		अगर (!test_bit(IWL_MVM_STATUS_IN_D3, &mvm->status))
			cmd->flags |=
				cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK);

		cmd->uapsd_ac_flags |= BIT(ac);

		/* QNDP TID - the highest TID with no admission control */
		अगर (!tid_found && !mvmvअगर->queue_params[ac].acm) अणु
			tid_found = true;
			चयन (ac) अणु
			हाल IEEE80211_AC_VO:
				cmd->qndp_tid = 6;
				अवरोध;
			हाल IEEE80211_AC_VI:
				cmd->qndp_tid = 5;
				अवरोध;
			हाल IEEE80211_AC_BE:
				cmd->qndp_tid = 0;
				अवरोध;
			हाल IEEE80211_AC_BK:
				cmd->qndp_tid = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	cmd->flags |= cpu_to_le16(POWER_FLAGS_UAPSD_MISBEHAVING_ENA_MSK);

	अगर (cmd->uapsd_ac_flags == (BIT(IEEE80211_AC_VO) |
				    BIT(IEEE80211_AC_VI) |
				    BIT(IEEE80211_AC_BE) |
				    BIT(IEEE80211_AC_BK))) अणु
		cmd->flags |= cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK);
		cmd->snooze_पूर्णांकerval = cpu_to_le16(IWL_MVM_PS_SNOOZE_INTERVAL);
		cmd->snooze_winकरोw =
			test_bit(IWL_MVM_STATUS_IN_D3, &mvm->status) ?
				cpu_to_le16(IWL_MVM_WOWLAN_PS_SNOOZE_WINDOW) :
				cpu_to_le16(IWL_MVM_PS_SNOOZE_WINDOW);
	पूर्ण

	cmd->uapsd_max_sp = mvm->hw->uapsd_max_sp_len;

	अगर (test_bit(IWL_MVM_STATUS_IN_D3, &mvm->status) ||
	    cmd->flags & cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK)) अणु
		cmd->rx_data_समयout_uapsd =
			cpu_to_le32(IWL_MVM_WOWLAN_PS_RX_DATA_TIMEOUT);
		cmd->tx_data_समयout_uapsd =
			cpu_to_le32(IWL_MVM_WOWLAN_PS_TX_DATA_TIMEOUT);
	पूर्ण अन्यथा अणु
		cmd->rx_data_समयout_uapsd =
			cpu_to_le32(IWL_MVM_UAPSD_RX_DATA_TIMEOUT);
		cmd->tx_data_समयout_uapsd =
			cpu_to_le32(IWL_MVM_UAPSD_TX_DATA_TIMEOUT);
	पूर्ण

	अगर (cmd->flags & cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK)) अणु
		cmd->heavy_tx_thld_packets =
			IWL_MVM_PS_SNOOZE_HEAVY_TX_THLD_PACKETS;
		cmd->heavy_rx_thld_packets =
			IWL_MVM_PS_SNOOZE_HEAVY_RX_THLD_PACKETS;
	पूर्ण अन्यथा अणु
		cmd->heavy_tx_thld_packets =
			IWL_MVM_PS_HEAVY_TX_THLD_PACKETS;
		cmd->heavy_rx_thld_packets =
			IWL_MVM_PS_HEAVY_RX_THLD_PACKETS;
	पूर्ण
	cmd->heavy_tx_thld_percentage =
		IWL_MVM_PS_HEAVY_TX_THLD_PERCENT;
	cmd->heavy_rx_thld_percentage =
		IWL_MVM_PS_HEAVY_RX_THLD_PERCENT;
पूर्ण

अटल व्योम iwl_mvm_p2p_standalone_iterator(व्योम *_data, u8 *mac,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	bool *is_p2p_standalone = _data;

	चयन (ieee80211_vअगर_type_p2p(vअगर)) अणु
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_AP:
		*is_p2p_standalone = false;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (vअगर->bss_conf.assoc)
			*is_p2p_standalone = false;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool iwl_mvm_घातer_allow_uapsd(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (!स_भेद(mvmvअगर->uapsd_misbehaving_bssid, vअगर->bss_conf.bssid,
		    ETH_ALEN))
		वापस false;

	/*
	 * Aव्योम using uAPSD अगर P2P client is associated to GO that uses
	 * opportunistic घातer save. This is due to current FW limitation.
	 */
	अगर (vअगर->p2p &&
	    (vअगर->bss_conf.p2p_noa_attr.oppps_ctwinकरोw &
	    IEEE80211_P2P_OPPPS_ENABLE_BIT))
		वापस false;

	/*
	 * Aव्योम using uAPSD अगर client is in DCM -
	 * low latency issue in Miracast
	 */
	अगर (iwl_mvm_phy_ctx_count(mvm) >= 2)
		वापस false;

	अगर (vअगर->p2p) अणु
		/* Allow U-APSD only अगर p2p is stand alone */
		bool is_p2p_standalone = true;

		अगर (!iwl_mvm_is_p2p_scm_uapsd_supported(mvm))
			वापस false;

		ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_p2p_standalone_iterator,
					&is_p2p_standalone);

		अगर (!is_p2p_standalone)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool iwl_mvm_घातer_is_radar(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_channel *chan;
	bool radar_detect = false;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(vअगर->chanctx_conf);
	WARN_ON(!chanctx_conf);
	अगर (chanctx_conf) अणु
		chan = chanctx_conf->def.chan;
		radar_detect = chan->flags & IEEE80211_CHAN_RADAR;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस radar_detect;
पूर्ण

अटल व्योम iwl_mvm_घातer_config_skip_dtim(काष्ठा iwl_mvm *mvm,
					   काष्ठा ieee80211_vअगर *vअगर,
					   काष्ठा iwl_mac_घातer_cmd *cmd)
अणु
	पूर्णांक dtimper = vअगर->bss_conf.dtim_period ?: 1;
	पूर्णांक skip;

	/* disable, in हाल we're supposed to override */
	cmd->skip_dtim_periods = 0;
	cmd->flags &= ~cpu_to_le16(POWER_FLAGS_SKIP_OVER_DTIM_MSK);

	अगर (iwl_mvm_घातer_is_radar(vअगर))
		वापस;

	अगर (dtimper >= 10)
		वापस;

	अगर (!test_bit(IWL_MVM_STATUS_IN_D3, &mvm->status)) अणु
		अगर (iwlmvm_mod_params.घातer_scheme != IWL_POWER_SCHEME_LP)
			वापस;
		skip = 2;
	पूर्ण अन्यथा अणु
		पूर्णांक dtimper_tu = dtimper * vअगर->bss_conf.beacon_पूर्णांक;

		अगर (WARN_ON(!dtimper_tu))
			वापस;
		/* configure skip over dtim up to 306TU - 314 msec */
		skip = max_t(u8, 1, 306 / dtimper_tu);
	पूर्ण

	/* the firmware really expects "look at every X DTIMs", so add 1 */
	cmd->skip_dtim_periods = 1 + skip;
	cmd->flags |= cpu_to_le16(POWER_FLAGS_SKIP_OVER_DTIM_MSK);
पूर्ण

अटल व्योम iwl_mvm_घातer_build_cmd(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा iwl_mac_घातer_cmd *cmd)
अणु
	पूर्णांक dtimper, bi;
	पूर्णांक keep_alive;
	काष्ठा iwl_mvm_vअगर *mvmvअगर __maybe_unused =
		iwl_mvm_vअगर_from_mac80211(vअगर);

	cmd->id_and_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							    mvmvअगर->color));
	dtimper = vअगर->bss_conf.dtim_period;
	bi = vअगर->bss_conf.beacon_पूर्णांक;

	/*
	 * Regardless of घातer management state the driver must set
	 * keep alive period. FW will use it क्रम sending keep alive NDPs
	 * immediately after association. Check that keep alive period
	 * is at least 3 * DTIM
	 */
	keep_alive = DIV_ROUND_UP(ieee80211_tu_to_usec(3 * dtimper * bi),
				  USEC_PER_SEC);
	keep_alive = max(keep_alive, POWER_KEEP_ALIVE_PERIOD_SEC);
	cmd->keep_alive_seconds = cpu_to_le16(keep_alive);

	अगर (mvm->ps_disabled)
		वापस;

	cmd->flags |= cpu_to_le16(POWER_FLAGS_POWER_SAVE_ENA_MSK);

	अगर (!vअगर->bss_conf.ps || !mvmvअगर->pm_enabled)
		वापस;

	अगर (iwl_mvm_vअगर_low_latency(mvmvअगर) && vअगर->p2p &&
	    (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_SHORT_PM_TIMEOUTS) ||
	     !IWL_MVM_P2P_LOWLATENCY_PS_ENABLE))
		वापस;

	cmd->flags |= cpu_to_le16(POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK);

	अगर (vअगर->bss_conf.beacon_rate &&
	    (vअगर->bss_conf.beacon_rate->bitrate == 10 ||
	     vअगर->bss_conf.beacon_rate->bitrate == 60)) अणु
		cmd->flags |= cpu_to_le16(POWER_FLAGS_LPRX_ENA_MSK);
		cmd->lprx_rssi_threshold = POWER_LPRX_RSSI_THRESHOLD;
	पूर्ण

	iwl_mvm_घातer_config_skip_dtim(mvm, vअगर, cmd);

	अगर (test_bit(IWL_MVM_STATUS_IN_D3, &mvm->status)) अणु
		cmd->rx_data_समयout =
			cpu_to_le32(IWL_MVM_WOWLAN_PS_RX_DATA_TIMEOUT);
		cmd->tx_data_समयout =
			cpu_to_le32(IWL_MVM_WOWLAN_PS_TX_DATA_TIMEOUT);
	पूर्ण अन्यथा अगर (iwl_mvm_vअगर_low_latency(mvmvअगर) && vअगर->p2p &&
		   fw_has_capa(&mvm->fw->ucode_capa,
			       IWL_UCODE_TLV_CAPA_SHORT_PM_TIMEOUTS)) अणु
		cmd->tx_data_समयout =
			cpu_to_le32(IWL_MVM_SHORT_PS_TX_DATA_TIMEOUT);
		cmd->rx_data_समयout =
			cpu_to_le32(IWL_MVM_SHORT_PS_RX_DATA_TIMEOUT);
	पूर्ण अन्यथा अणु
		cmd->rx_data_समयout =
			cpu_to_le32(IWL_MVM_DEFAULT_PS_RX_DATA_TIMEOUT);
		cmd->tx_data_समयout =
			cpu_to_le32(IWL_MVM_DEFAULT_PS_TX_DATA_TIMEOUT);
	पूर्ण

	अगर (iwl_mvm_घातer_allow_uapsd(mvm, vअगर))
		iwl_mvm_घातer_configure_uapsd(mvm, vअगर, cmd);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_KEEP_ALIVE)
		cmd->keep_alive_seconds =
			cpu_to_le16(mvmvअगर->dbgfs_pm.keep_alive_seconds);
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_SKIP_OVER_DTIM) अणु
		अगर (mvmvअगर->dbgfs_pm.skip_over_dtim)
			cmd->flags |=
				cpu_to_le16(POWER_FLAGS_SKIP_OVER_DTIM_MSK);
		अन्यथा
			cmd->flags &=
				cpu_to_le16(~POWER_FLAGS_SKIP_OVER_DTIM_MSK);
	पूर्ण
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_RX_DATA_TIMEOUT)
		cmd->rx_data_समयout =
			cpu_to_le32(mvmvअगर->dbgfs_pm.rx_data_समयout);
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_TX_DATA_TIMEOUT)
		cmd->tx_data_समयout =
			cpu_to_le32(mvmvअगर->dbgfs_pm.tx_data_समयout);
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_SKIP_DTIM_PERIODS)
		cmd->skip_dtim_periods = mvmvअगर->dbgfs_pm.skip_dtim_periods;
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_LPRX_ENA) अणु
		अगर (mvmvअगर->dbgfs_pm.lprx_ena)
			cmd->flags |= cpu_to_le16(POWER_FLAGS_LPRX_ENA_MSK);
		अन्यथा
			cmd->flags &= cpu_to_le16(~POWER_FLAGS_LPRX_ENA_MSK);
	पूर्ण
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_LPRX_RSSI_THRESHOLD)
		cmd->lprx_rssi_threshold = mvmvअगर->dbgfs_pm.lprx_rssi_threshold;
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_SNOOZE_ENABLE) अणु
		अगर (mvmvअगर->dbgfs_pm.snooze_ena)
			cmd->flags |=
				cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK);
		अन्यथा
			cmd->flags &=
				cpu_to_le16(~POWER_FLAGS_SNOOZE_ENA_MSK);
	पूर्ण
	अगर (mvmvअगर->dbgfs_pm.mask & MVM_DEBUGFS_PM_UAPSD_MISBEHAVING) अणु
		u16 flag = POWER_FLAGS_UAPSD_MISBEHAVING_ENA_MSK;
		अगर (mvmvअगर->dbgfs_pm.uapsd_misbehaving)
			cmd->flags |= cpu_to_le16(flag);
		अन्यथा
			cmd->flags &= cpu_to_le16(flag);
	पूर्ण
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUGFS */
पूर्ण

अटल पूर्णांक iwl_mvm_घातer_send_cmd(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mac_घातer_cmd cmd = अणुपूर्ण;

	iwl_mvm_घातer_build_cmd(mvm, vअगर, &cmd);
	iwl_mvm_घातer_log(mvm, &cmd);
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	स_नकल(&iwl_mvm_vअगर_from_mac80211(vअगर)->mac_pwr_cmd, &cmd, माप(cmd));
#पूर्ण_अगर

	वापस iwl_mvm_send_cmd_pdu(mvm, MAC_PM_POWER_TABLE, 0,
				    माप(cmd), &cmd);
पूर्ण

पूर्णांक iwl_mvm_घातer_update_device(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_device_घातer_cmd cmd = अणु
		.flags = 0,
	पूर्ण;

	अगर (iwlmvm_mod_params.घातer_scheme == IWL_POWER_SCHEME_CAM)
		mvm->ps_disabled = true;

	अगर (!mvm->ps_disabled)
		cmd.flags |= cpu_to_le16(DEVICE_POWER_FLAGS_POWER_SAVE_ENA_MSK);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (test_bit(IWL_MVM_STATUS_IN_D3, &mvm->status) ?
			mvm->disable_घातer_off_d3 : mvm->disable_घातer_off)
		cmd.flags &=
			cpu_to_le16(~DEVICE_POWER_FLAGS_POWER_SAVE_ENA_MSK);
#पूर्ण_अगर
	अगर (mvm->ext_घड़ी_valid)
		cmd.flags |= cpu_to_le16(DEVICE_POWER_FLAGS_32K_CLK_VALID_MSK);

	IWL_DEBUG_POWER(mvm,
			"Sending device power command with flags = 0x%X\n",
			cmd.flags);

	वापस iwl_mvm_send_cmd_pdu(mvm, POWER_TABLE_CMD, 0, माप(cmd),
				    &cmd);
पूर्ण

व्योम iwl_mvm_घातer_vअगर_assoc(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (स_भेद(vअगर->bss_conf.bssid, mvmvअगर->uapsd_misbehaving_bssid,
		   ETH_ALEN))
		eth_zero_addr(mvmvअगर->uapsd_misbehaving_bssid);
पूर्ण

अटल व्योम iwl_mvm_घातer_uapsd_misbehav_ap_iterator(व्योम *_data, u8 *mac,
						     काष्ठा ieee80211_vअगर *vअगर)
अणु
	u8 *ap_sta_id = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	/* The ap_sta_id is not expected to change during current association
	 * so no explicit protection is needed
	 */
	अगर (mvmvअगर->ap_sta_id == *ap_sta_id)
		स_नकल(mvmvअगर->uapsd_misbehaving_bssid, vअगर->bss_conf.bssid,
		       ETH_ALEN);
पूर्ण

व्योम iwl_mvm_घातer_uapsd_misbehaving_ap_notअगर(काष्ठा iwl_mvm *mvm,
					      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_uapsd_misbehaving_ap_notअगर *notअगर = (व्योम *)pkt->data;
	u8 ap_sta_id = le32_to_cpu(notअगर->sta_id);

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_घातer_uapsd_misbehav_ap_iterator, &ap_sta_id);
पूर्ण

काष्ठा iwl_घातer_vअगरs अणु
	काष्ठा iwl_mvm *mvm;
	काष्ठा ieee80211_vअगर *bss_vअगर;
	काष्ठा ieee80211_vअगर *p2p_vअगर;
	काष्ठा ieee80211_vअगर *ap_vअगर;
	काष्ठा ieee80211_vअगर *monitor_vअगर;
	bool p2p_active;
	bool bss_active;
	bool ap_active;
	bool monitor_active;
पूर्ण;

अटल व्योम iwl_mvm_घातer_disable_pm_iterator(व्योम *_data, u8* mac,
					      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	mvmvअगर->pm_enabled = false;
पूर्ण

अटल व्योम iwl_mvm_घातer_ps_disabled_iterator(व्योम *_data, u8* mac,
					       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	bool *disable_ps = _data;

	अगर (mvmvअगर->phy_ctxt && mvmvअगर->phy_ctxt->id < NUM_PHY_CTX)
		*disable_ps |= mvmvअगर->ps_disabled;
पूर्ण

अटल व्योम iwl_mvm_घातer_get_vअगरs_iterator(व्योम *_data, u8 *mac,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_घातer_vअगरs *घातer_iterator = _data;
	bool active = mvmvअगर->phy_ctxt && mvmvअगर->phy_ctxt->id < NUM_PHY_CTX;

	चयन (ieee80211_vअगर_type_p2p(vअगर)) अणु
	हाल NL80211_IFTYPE_P2P_DEVICE:
		अवरोध;

	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_AP:
		/* only a single MAC of the same type */
		WARN_ON(घातer_iterator->ap_vअगर);
		घातer_iterator->ap_vअगर = vअगर;
		अगर (active)
			घातer_iterator->ap_active = true;
		अवरोध;

	हाल NL80211_IFTYPE_MONITOR:
		/* only a single MAC of the same type */
		WARN_ON(घातer_iterator->monitor_vअगर);
		घातer_iterator->monitor_vअगर = vअगर;
		अगर (active)
			घातer_iterator->monitor_active = true;
		अवरोध;

	हाल NL80211_IFTYPE_P2P_CLIENT:
		/* only a single MAC of the same type */
		WARN_ON(घातer_iterator->p2p_vअगर);
		घातer_iterator->p2p_vअगर = vअगर;
		अगर (active)
			घातer_iterator->p2p_active = true;
		अवरोध;

	हाल NL80211_IFTYPE_STATION:
		घातer_iterator->bss_vअगर = vअगर;
		अगर (active)
			घातer_iterator->bss_active = true;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_घातer_set_pm(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_घातer_vअगरs *vअगरs)
अणु
	काष्ठा iwl_mvm_vअगर *bss_mvmvअगर = शून्य;
	काष्ठा iwl_mvm_vअगर *p2p_mvmvअगर = शून्य;
	काष्ठा iwl_mvm_vअगर *ap_mvmvअगर = शून्य;
	bool client_same_channel = false;
	bool ap_same_channel = false;

	lockdep_निश्चित_held(&mvm->mutex);

	/* set pm_enable to false */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_घातer_disable_pm_iterator,
					शून्य);

	अगर (vअगरs->bss_vअगर)
		bss_mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगरs->bss_vअगर);

	अगर (vअगरs->p2p_vअगर)
		p2p_mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगरs->p2p_vअगर);

	अगर (vअगरs->ap_vअगर)
		ap_mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगरs->ap_vअगर);

	/* करोn't allow PM अगर any TDLS stations exist */
	अगर (iwl_mvm_tdls_sta_count(mvm, शून्य))
		वापस;

	/* enable PM on bss अगर bss stand alone */
	अगर (vअगरs->bss_active && !vअगरs->p2p_active && !vअगरs->ap_active) अणु
		bss_mvmvअगर->pm_enabled = true;
		वापस;
	पूर्ण

	/* enable PM on p2p अगर p2p stand alone */
	अगर (vअगरs->p2p_active && !vअगरs->bss_active && !vअगरs->ap_active) अणु
		p2p_mvmvअगर->pm_enabled = true;
		वापस;
	पूर्ण

	अगर (vअगरs->bss_active && vअगरs->p2p_active)
		client_same_channel = (bss_mvmvअगर->phy_ctxt->id ==
				       p2p_mvmvअगर->phy_ctxt->id);
	अगर (vअगरs->bss_active && vअगरs->ap_active)
		ap_same_channel = (bss_mvmvअगर->phy_ctxt->id ==
				   ap_mvmvअगर->phy_ctxt->id);

	/* clients are not stand alone: enable PM अगर DCM */
	अगर (!(client_same_channel || ap_same_channel)) अणु
		अगर (vअगरs->bss_active)
			bss_mvmvअगर->pm_enabled = true;
		अगर (vअगरs->p2p_active)
			p2p_mvmvअगर->pm_enabled = true;
		वापस;
	पूर्ण

	/*
	 * There is only one channel in the प्रणाली and there are only
	 * bss and p2p clients that share it
	 */
	अगर (client_same_channel && !vअगरs->ap_active) अणु
		/* share same channel*/
		bss_mvmvअगर->pm_enabled = true;
		p2p_mvmvअगर->pm_enabled = true;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
पूर्णांक iwl_mvm_घातer_mac_dbgfs_पढ़ो(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर, अक्षर *buf,
				 पूर्णांक bufsz)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mac_घातer_cmd cmd = अणुपूर्ण;
	पूर्णांक pos = 0;

	mutex_lock(&mvm->mutex);
	स_नकल(&cmd, &mvmvअगर->mac_pwr_cmd, माप(cmd));
	mutex_unlock(&mvm->mutex);

	pos += scnम_लिखो(buf+pos, bufsz-pos, "power_scheme = %d\n",
			 iwlmvm_mod_params.घातer_scheme);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "flags = 0x%x\n",
			 le16_to_cpu(cmd.flags));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "keep_alive = %d\n",
			 le16_to_cpu(cmd.keep_alive_seconds));

	अगर (!(cmd.flags & cpu_to_le16(POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK)))
		वापस pos;

	pos += scnम_लिखो(buf+pos, bufsz-pos, "skip_over_dtim = %d\n",
			 (cmd.flags &
			 cpu_to_le16(POWER_FLAGS_SKIP_OVER_DTIM_MSK)) ? 1 : 0);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "skip_dtim_periods = %d\n",
			 cmd.skip_dtim_periods);
	अगर (!(cmd.flags & cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK))) अणु
		pos += scnम_लिखो(buf+pos, bufsz-pos, "rx_data_timeout = %d\n",
				 le32_to_cpu(cmd.rx_data_समयout));
		pos += scnम_लिखो(buf+pos, bufsz-pos, "tx_data_timeout = %d\n",
				 le32_to_cpu(cmd.tx_data_समयout));
	पूर्ण
	अगर (cmd.flags & cpu_to_le16(POWER_FLAGS_LPRX_ENA_MSK))
		pos += scnम_लिखो(buf+pos, bufsz-pos,
				 "lprx_rssi_threshold = %d\n",
				 cmd.lprx_rssi_threshold);

	अगर (!(cmd.flags & cpu_to_le16(POWER_FLAGS_ADVANCE_PM_ENA_MSK)))
		वापस pos;

	pos += scnम_लिखो(buf+pos, bufsz-pos, "rx_data_timeout_uapsd = %d\n",
			 le32_to_cpu(cmd.rx_data_समयout_uapsd));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "tx_data_timeout_uapsd = %d\n",
			 le32_to_cpu(cmd.tx_data_समयout_uapsd));
	pos += scnम_लिखो(buf+pos, bufsz-pos, "qndp_tid = %d\n", cmd.qndp_tid);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "uapsd_ac_flags = 0x%x\n",
			 cmd.uapsd_ac_flags);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "uapsd_max_sp = %d\n",
			 cmd.uapsd_max_sp);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "heavy_tx_thld_packets = %d\n",
			 cmd.heavy_tx_thld_packets);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "heavy_rx_thld_packets = %d\n",
			 cmd.heavy_rx_thld_packets);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "heavy_tx_thld_percentage = %d\n",
			 cmd.heavy_tx_thld_percentage);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "heavy_rx_thld_percentage = %d\n",
			 cmd.heavy_rx_thld_percentage);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "uapsd_misbehaving_enable = %d\n",
			 (cmd.flags &
			  cpu_to_le16(POWER_FLAGS_UAPSD_MISBEHAVING_ENA_MSK)) ?
			 1 : 0);

	अगर (!(cmd.flags & cpu_to_le16(POWER_FLAGS_SNOOZE_ENA_MSK)))
		वापस pos;

	pos += scnम_लिखो(buf+pos, bufsz-pos, "snooze_interval = %d\n",
			 cmd.snooze_पूर्णांकerval);
	pos += scnम_लिखो(buf+pos, bufsz-pos, "snooze_window = %d\n",
			 cmd.snooze_winकरोw);

	वापस pos;
पूर्ण

व्योम
iwl_mvm_beacon_filter_debugfs_parameters(काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा iwl_beacon_filter_cmd *cmd)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_dbgfs_bf *dbgfs_bf = &mvmvअगर->dbgfs_bf;

	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BF_ENERGY_DELTA)
		cmd->bf_energy_delta = cpu_to_le32(dbgfs_bf->bf_energy_delta);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BF_ROAMING_ENERGY_DELTA)
		cmd->bf_roaming_energy_delta =
				cpu_to_le32(dbgfs_bf->bf_roaming_energy_delta);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BF_ROAMING_STATE)
		cmd->bf_roaming_state = cpu_to_le32(dbgfs_bf->bf_roaming_state);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BF_TEMP_THRESHOLD)
		cmd->bf_temp_threshold =
				cpu_to_le32(dbgfs_bf->bf_temp_threshold);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BF_TEMP_FAST_FILTER)
		cmd->bf_temp_fast_filter =
				cpu_to_le32(dbgfs_bf->bf_temp_fast_filter);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BF_TEMP_SLOW_FILTER)
		cmd->bf_temp_slow_filter =
				cpu_to_le32(dbgfs_bf->bf_temp_slow_filter);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BF_DEBUG_FLAG)
		cmd->bf_debug_flag = cpu_to_le32(dbgfs_bf->bf_debug_flag);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BF_ESCAPE_TIMER)
		cmd->bf_escape_समयr = cpu_to_le32(dbgfs_bf->bf_escape_समयr);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BA_ESCAPE_TIMER)
		cmd->ba_escape_समयr = cpu_to_le32(dbgfs_bf->ba_escape_समयr);
	अगर (dbgfs_bf->mask & MVM_DEBUGFS_BA_ENABLE_BEACON_ABORT)
		cmd->ba_enable_beacon_पात =
				cpu_to_le32(dbgfs_bf->ba_enable_beacon_पात);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक _iwl_mvm_enable_beacon_filter(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा iwl_beacon_filter_cmd *cmd,
					 u32 cmd_flags)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	अगर (mvmvअगर != mvm->bf_allowed_vअगर || !vअगर->bss_conf.dtim_period ||
	    vअगर->type != NL80211_IFTYPE_STATION || vअगर->p2p)
		वापस 0;

	iwl_mvm_beacon_filter_set_cqm_params(mvm, vअगर, cmd);
	iwl_mvm_beacon_filter_debugfs_parameters(vअगर, cmd);
	ret = iwl_mvm_beacon_filter_send_cmd(mvm, cmd, cmd_flags);

	अगर (!ret)
		mvmvअगर->bf_data.bf_enabled = true;

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_enable_beacon_filter(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 u32 flags)
अणु
	काष्ठा iwl_beacon_filter_cmd cmd = अणु
		IWL_BF_CMD_CONFIG_DEFAULTS,
		.bf_enable_beacon_filter = cpu_to_le32(1),
	पूर्ण;

	वापस _iwl_mvm_enable_beacon_filter(mvm, vअगर, &cmd, flags);
पूर्ण

अटल पूर्णांक _iwl_mvm_disable_beacon_filter(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर,
					  u32 flags)
अणु
	काष्ठा iwl_beacon_filter_cmd cmd = अणुपूर्ण;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	अगर (vअगर->type != NL80211_IFTYPE_STATION || vअगर->p2p)
		वापस 0;

	ret = iwl_mvm_beacon_filter_send_cmd(mvm, &cmd, flags);

	अगर (!ret)
		mvmvअगर->bf_data.bf_enabled = false;

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_disable_beacon_filter(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_vअगर *vअगर,
				  u32 flags)
अणु
	वापस _iwl_mvm_disable_beacon_filter(mvm, vअगर, flags);
पूर्ण

अटल पूर्णांक iwl_mvm_घातer_set_ps(काष्ठा iwl_mvm *mvm)
अणु
	bool disable_ps;
	पूर्णांक ret;

	/* disable PS अगर CAM */
	disable_ps = (iwlmvm_mod_params.घातer_scheme == IWL_POWER_SCHEME_CAM);
	/* ...or अगर any of the vअगरs require PS to be off */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_घातer_ps_disabled_iterator,
					&disable_ps);

	/* update device घातer state अगर it has changed */
	अगर (mvm->ps_disabled != disable_ps) अणु
		bool old_ps_disabled = mvm->ps_disabled;

		mvm->ps_disabled = disable_ps;
		ret = iwl_mvm_घातer_update_device(mvm);
		अगर (ret) अणु
			mvm->ps_disabled = old_ps_disabled;
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_घातer_set_ba(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_beacon_filter_cmd cmd = अणु
		IWL_BF_CMD_CONFIG_DEFAULTS,
		.bf_enable_beacon_filter = cpu_to_le32(1),
	पूर्ण;

	अगर (!mvmvअगर->bf_data.bf_enabled)
		वापस 0;

	अगर (test_bit(IWL_MVM_STATUS_IN_D3, &mvm->status))
		cmd.ba_escape_समयr = cpu_to_le32(IWL_BA_ESCAPE_TIMER_D3);

	mvmvअगर->bf_data.ba_enabled = !(!mvmvअगर->pm_enabled ||
				       mvm->ps_disabled ||
				       !vअगर->bss_conf.ps ||
				       iwl_mvm_vअगर_low_latency(mvmvअगर));

	वापस _iwl_mvm_enable_beacon_filter(mvm, vअगर, &cmd, 0);
पूर्ण

पूर्णांक iwl_mvm_घातer_update_ps(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_घातer_vअगरs vअगरs = अणु
		.mvm = mvm,
	पूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	/* get vअगरs info */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_घातer_get_vअगरs_iterator, &vअगरs);

	ret = iwl_mvm_घातer_set_ps(mvm);
	अगर (ret)
		वापस ret;

	अगर (vअगरs.bss_vअगर)
		वापस iwl_mvm_घातer_set_ba(mvm, vअगरs.bss_vअगर);

	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_घातer_update_mac(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_घातer_vअगरs vअगरs = अणु
		.mvm = mvm,
	पूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	/* get vअगरs info */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITER_NORMAL,
					iwl_mvm_घातer_get_vअगरs_iterator, &vअगरs);

	iwl_mvm_घातer_set_pm(mvm, &vअगरs);

	ret = iwl_mvm_घातer_set_ps(mvm);
	अगर (ret)
		वापस ret;

	अगर (vअगरs.bss_vअगर) अणु
		ret = iwl_mvm_घातer_send_cmd(mvm, vअगरs.bss_vअगर);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (vअगरs.p2p_vअगर) अणु
		ret = iwl_mvm_घातer_send_cmd(mvm, vअगरs.p2p_vअगर);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (vअगरs.bss_vअगर)
		वापस iwl_mvm_घातer_set_ba(mvm, vअगरs.bss_vअगर);

	वापस 0;
पूर्ण
