<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/etherdevice.h>
#समावेश <net/mac80211.h>
#समावेश <linux/crc32.h>

#समावेश "mvm.h"
#समावेश "fw/api/scan.h"
#समावेश "iwl-io.h"

#घोषणा IWL_DENSE_EBS_SCAN_RATIO 5
#घोषणा IWL_SPARSE_EBS_SCAN_RATIO 1

#घोषणा IWL_SCAN_DWELL_ACTIVE		10
#घोषणा IWL_SCAN_DWELL_PASSIVE		110
#घोषणा IWL_SCAN_DWELL_FRAGMENTED	44
#घोषणा IWL_SCAN_DWELL_EXTENDED		90
#घोषणा IWL_SCAN_NUM_OF_FRAGS		3
#घोषणा IWL_SCAN_LAST_2_4_CHN		14

/* adaptive dwell max budget समय [TU] क्रम full scan */
#घोषणा IWL_SCAN_ADWELL_MAX_BUDGET_FULL_SCAN 300
/* adaptive dwell max budget समय [TU] क्रम directed scan */
#घोषणा IWL_SCAN_ADWELL_MAX_BUDGET_सूचीECTED_SCAN 100
/* adaptive dwell शेष high band APs number */
#घोषणा IWL_SCAN_ADWELL_DEFAULT_HB_N_APS 8
/* adaptive dwell शेष low band APs number */
#घोषणा IWL_SCAN_ADWELL_DEFAULT_LB_N_APS 2
/* adaptive dwell शेष APs number in social channels (1, 6, 11) */
#घोषणा IWL_SCAN_ADWELL_DEFAULT_N_APS_SOCIAL 10
/* number of scan channels */
#घोषणा IWL_SCAN_NUM_CHANNELS 112
/* adaptive dwell number of APs override mask क्रम p2p मित्रly GO */
#घोषणा IWL_SCAN_ADWELL_N_APS_GO_FRIENDLY_BIT BIT(20)
/* adaptive dwell number of APs override mask क्रम social channels */
#घोषणा IWL_SCAN_ADWELL_N_APS_SOCIAL_CHS_BIT BIT(21)
/* adaptive dwell number of APs override क्रम p2p मित्रly GO channels */
#घोषणा IWL_SCAN_ADWELL_N_APS_GO_FRIENDLY 10
/* adaptive dwell number of APs override क्रम social channels */
#घोषणा IWL_SCAN_ADWELL_N_APS_SOCIAL_CHS 2

/* minimal number of 2GHz and 5GHz channels in the regular scan request */
#घोषणा IWL_MVM_6GHZ_PASSIVE_SCAN_MIN_CHANS 4

काष्ठा iwl_mvm_scan_timing_params अणु
	u32 suspend_समय;
	u32 max_out_समय;
पूर्ण;

अटल काष्ठा iwl_mvm_scan_timing_params scan_timing[] = अणु
	[IWL_SCAN_TYPE_UNASSOC] = अणु
		.suspend_समय = 0,
		.max_out_समय = 0,
	पूर्ण,
	[IWL_SCAN_TYPE_WILD] = अणु
		.suspend_समय = 30,
		.max_out_समय = 120,
	पूर्ण,
	[IWL_SCAN_TYPE_MILD] = अणु
		.suspend_समय = 120,
		.max_out_समय = 120,
	पूर्ण,
	[IWL_SCAN_TYPE_FRAGMENTED] = अणु
		.suspend_समय = 95,
		.max_out_समय = 44,
	पूर्ण,
	[IWL_SCAN_TYPE_FAST_BALANCE] = अणु
		.suspend_समय = 30,
		.max_out_समय = 37,
	पूर्ण,
पूर्ण;

काष्ठा iwl_mvm_scan_params अणु
	/* For CDB this is low band scan type, क्रम non-CDB - type. */
	क्रमागत iwl_mvm_scan_type type;
	क्रमागत iwl_mvm_scan_type hb_type;
	u32 n_channels;
	u16 delay;
	पूर्णांक n_ssids;
	काष्ठा cfg80211_ssid *ssids;
	काष्ठा ieee80211_channel **channels;
	u32 flags;
	u8 *mac_addr;
	u8 *mac_addr_mask;
	bool no_cck;
	bool pass_all;
	पूर्णांक n_match_sets;
	काष्ठा iwl_scan_probe_req preq;
	काष्ठा cfg80211_match_set *match_sets;
	पूर्णांक n_scan_plans;
	काष्ठा cfg80211_sched_scan_plan *scan_plans;
	bool iter_notअगर;
	काष्ठा cfg80211_scan_6ghz_params *scan_6ghz_params;
	u32 n_6ghz_params;
	bool scan_6ghz;
	bool enable_6ghz_passive;
पूर्ण;

अटल अंतरभूत व्योम *iwl_mvm_get_scan_req_umac_data(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_scan_req_umac *cmd = mvm->scan_cmd;

	अगर (iwl_mvm_is_adaptive_dwell_v2_supported(mvm))
		वापस (व्योम *)&cmd->v8.data;

	अगर (iwl_mvm_is_adaptive_dwell_supported(mvm))
		वापस (व्योम *)&cmd->v7.data;

	अगर (iwl_mvm_cdb_scan_api(mvm))
		वापस (व्योम *)&cmd->v6.data;

	वापस (व्योम *)&cmd->v1.data;
पूर्ण

अटल अंतरभूत काष्ठा iwl_scan_umac_chan_param *
iwl_mvm_get_scan_req_umac_channel(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_scan_req_umac *cmd = mvm->scan_cmd;

	अगर (iwl_mvm_is_adaptive_dwell_v2_supported(mvm))
		वापस &cmd->v8.channel;

	अगर (iwl_mvm_is_adaptive_dwell_supported(mvm))
		वापस &cmd->v7.channel;

	अगर (iwl_mvm_cdb_scan_api(mvm))
		वापस &cmd->v6.channel;

	वापस &cmd->v1.channel;
पूर्ण

अटल u8 iwl_mvm_scan_rx_ant(काष्ठा iwl_mvm *mvm)
अणु
	अगर (mvm->scan_rx_ant != ANT_NONE)
		वापस mvm->scan_rx_ant;
	वापस iwl_mvm_get_valid_rx_ant(mvm);
पूर्ण

अटल अंतरभूत __le16 iwl_mvm_scan_rx_chain(काष्ठा iwl_mvm *mvm)
अणु
	u16 rx_chain;
	u8 rx_ant;

	rx_ant = iwl_mvm_scan_rx_ant(mvm);
	rx_chain = rx_ant << PHY_RX_CHAIN_VALID_POS;
	rx_chain |= rx_ant << PHY_RX_CHAIN_FORCE_MIMO_SEL_POS;
	rx_chain |= rx_ant << PHY_RX_CHAIN_FORCE_SEL_POS;
	rx_chain |= 0x1 << PHY_RX_CHAIN_DRIVER_FORCE_POS;
	वापस cpu_to_le16(rx_chain);
पूर्ण

अटल अंतरभूत __le32
iwl_mvm_scan_rate_n_flags(काष्ठा iwl_mvm *mvm, क्रमागत nl80211_band band,
			  bool no_cck)
अणु
	u32 tx_ant;

	iwl_mvm_toggle_tx_ant(mvm, &mvm->scan_last_antenna_idx);
	tx_ant = BIT(mvm->scan_last_antenna_idx) << RATE_MCS_ANT_POS;

	अगर (band == NL80211_BAND_2GHZ && !no_cck)
		वापस cpu_to_le32(IWL_RATE_1M_PLCP | RATE_MCS_CCK_MSK |
				   tx_ant);
	अन्यथा
		वापस cpu_to_le32(IWL_RATE_6M_PLCP | tx_ant);
पूर्ण

अटल व्योम iwl_mvm_scan_condition_iterator(व्योम *data, u8 *mac,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक *global_cnt = data;

	अगर (vअगर->type != NL80211_IFTYPE_P2P_DEVICE && mvmvअगर->phy_ctxt &&
	    mvmvअगर->phy_ctxt->id < NUM_PHY_CTX)
		*global_cnt += 1;
पूर्ण

अटल क्रमागत iwl_mvm_traffic_load iwl_mvm_get_traffic_load(काष्ठा iwl_mvm *mvm)
अणु
	वापस mvm->tcm.result.global_load;
पूर्ण

अटल क्रमागत iwl_mvm_traffic_load
iwl_mvm_get_traffic_load_band(काष्ठा iwl_mvm *mvm, क्रमागत nl80211_band band)
अणु
	वापस mvm->tcm.result.band_load[band];
पूर्ण

काष्ठा iwl_is_dcm_with_go_iterator_data अणु
	काष्ठा ieee80211_vअगर *current_vअगर;
	bool is_dcm_with_p2p_go;
पूर्ण;

अटल व्योम iwl_mvm_is_dcm_with_go_iterator(व्योम *_data, u8 *mac,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_is_dcm_with_go_iterator_data *data = _data;
	काष्ठा iwl_mvm_vअगर *other_mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_vअगर *curr_mvmvअगर =
		iwl_mvm_vअगर_from_mac80211(data->current_vअगर);

	/* exclude the given vअगर */
	अगर (vअगर == data->current_vअगर)
		वापस;

	अगर (vअगर->type == NL80211_IFTYPE_AP && vअगर->p2p &&
	    other_mvmvअगर->phy_ctxt && curr_mvmvअगर->phy_ctxt &&
	    other_mvmvअगर->phy_ctxt->id != curr_mvmvअगर->phy_ctxt->id)
		data->is_dcm_with_p2p_go = true;
पूर्ण

अटल क्रमागत
iwl_mvm_scan_type _iwl_mvm_get_scan_type(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर,
					 क्रमागत iwl_mvm_traffic_load load,
					 bool low_latency)
अणु
	पूर्णांक global_cnt = 0;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
					    IEEE80211_IFACE_ITER_NORMAL,
					    iwl_mvm_scan_condition_iterator,
					    &global_cnt);
	अगर (!global_cnt)
		वापस IWL_SCAN_TYPE_UNASSOC;

	अगर (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_FRAGMENTED_SCAN)) अणु
		अगर ((load == IWL_MVM_TRAFFIC_HIGH || low_latency) &&
		    (!vअगर || vअगर->type != NL80211_IFTYPE_P2P_DEVICE))
			वापस IWL_SCAN_TYPE_FRAGMENTED;

		/* in हाल of DCM with GO where BSS DTIM पूर्णांकerval < 220msec
		 * set all scan requests as fast-balance scan
		 * */
		अगर (vअगर && vअगर->type == NL80211_IFTYPE_STATION &&
		    vअगर->bss_conf.dtim_period < 220) अणु
			काष्ठा iwl_is_dcm_with_go_iterator_data data = अणु
				.current_vअगर = vअगर,
				.is_dcm_with_p2p_go = false,
			पूर्ण;

			ieee80211_iterate_active_पूर्णांकerfaces_atomic(mvm->hw,
						IEEE80211_IFACE_ITER_NORMAL,
						iwl_mvm_is_dcm_with_go_iterator,
						&data);
			अगर (data.is_dcm_with_p2p_go)
				वापस IWL_SCAN_TYPE_FAST_BALANCE;
		पूर्ण
	पूर्ण

	अगर (load >= IWL_MVM_TRAFFIC_MEDIUM || low_latency)
		वापस IWL_SCAN_TYPE_MILD;

	वापस IWL_SCAN_TYPE_WILD;
पूर्ण

अटल क्रमागत
iwl_mvm_scan_type iwl_mvm_get_scan_type(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_vअगर *vअगर)
अणु
	क्रमागत iwl_mvm_traffic_load load;
	bool low_latency;

	load = iwl_mvm_get_traffic_load(mvm);
	low_latency = iwl_mvm_low_latency(mvm);

	वापस _iwl_mvm_get_scan_type(mvm, vअगर, load, low_latency);
पूर्ण

अटल क्रमागत
iwl_mvm_scan_type iwl_mvm_get_scan_type_band(काष्ठा iwl_mvm *mvm,
					     काष्ठा ieee80211_vअगर *vअगर,
					     क्रमागत nl80211_band band)
अणु
	क्रमागत iwl_mvm_traffic_load load;
	bool low_latency;

	load = iwl_mvm_get_traffic_load_band(mvm, band);
	low_latency = iwl_mvm_low_latency_band(mvm, band);

	वापस _iwl_mvm_get_scan_type(mvm, vअगर, load, low_latency);
पूर्ण

अटल अंतरभूत bool iwl_mvm_rrm_scan_needed(काष्ठा iwl_mvm *mvm)
अणु
	/* require rrm scan whenever the fw supports it */
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_DS_PARAM_SET_IE_SUPPORT);
पूर्ण

अटल पूर्णांक iwl_mvm_max_scan_ie_fw_cmd_room(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक max_probe_len;

	max_probe_len = SCAN_OFFLOAD_PROBE_REQ_SIZE;

	/* we create the 802.11 header and SSID element */
	max_probe_len -= 24 + 2;

	/* DS parameter set element is added on 2.4GHZ band अगर required */
	अगर (iwl_mvm_rrm_scan_needed(mvm))
		max_probe_len -= 3;

	वापस max_probe_len;
पूर्ण

पूर्णांक iwl_mvm_max_scan_ie_len(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक max_ie_len = iwl_mvm_max_scan_ie_fw_cmd_room(mvm);

	/* TODO: [BUG] This function should वापस the maximum allowed size of
	 * scan IEs, however the LMAC scan api contains both 2GHZ and 5GHZ IEs
	 * in the same command. So the correct implementation of this function
	 * is just iwl_mvm_max_scan_ie_fw_cmd_room() / 2. Currently the scan
	 * command has only 512 bytes and it would leave us with about 240
	 * bytes क्रम scan IEs, which is clearly not enough. So meanजबतक
	 * we will report an incorrect value. This may result in a failure to
	 * issue a scan in unअगरied_scan_lmac and unअगरied_sched_scan_lmac
	 * functions with -ENOBUFS, अगर a large enough probe will be provided.
	 */
	वापस max_ie_len;
पूर्ण

व्योम iwl_mvm_rx_lmac_scan_iter_complete_notअगर(काष्ठा iwl_mvm *mvm,
					      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_lmac_scan_complete_notअगर *notअगर = (व्योम *)pkt->data;

	IWL_DEBUG_SCAN(mvm,
		       "Scan offload iteration complete: status=0x%x scanned channels=%d\n",
		       notअगर->status, notअगर->scanned_channels);

	अगर (mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_FOUND) अणु
		IWL_DEBUG_SCAN(mvm, "Pass all scheduled scan results found\n");
		ieee80211_sched_scan_results(mvm->hw);
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_ENABLED;
	पूर्ण
पूर्ण

व्योम iwl_mvm_rx_scan_match_found(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	IWL_DEBUG_SCAN(mvm, "Scheduled scan results\n");
	ieee80211_sched_scan_results(mvm->hw);
पूर्ण

अटल स्थिर अक्षर *iwl_mvm_ebs_status_str(क्रमागत iwl_scan_ebs_status status)
अणु
	चयन (status) अणु
	हाल IWL_SCAN_EBS_SUCCESS:
		वापस "successful";
	हाल IWL_SCAN_EBS_INACTIVE:
		वापस "inactive";
	हाल IWL_SCAN_EBS_FAILED:
	हाल IWL_SCAN_EBS_CHAN_NOT_FOUND:
	शेष:
		वापस "failed";
	पूर्ण
पूर्ण

व्योम iwl_mvm_rx_lmac_scan_complete_notअगर(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_periodic_scan_complete *scan_notअगर = (व्योम *)pkt->data;
	bool पातed = (scan_notअगर->status == IWL_SCAN_OFFLOAD_ABORTED);

	/* If this happens, the firmware has mistakenly sent an LMAC
	 * notअगरication during UMAC scans -- warn and ignore it.
	 */
	अगर (WARN_ON_ONCE(fw_has_capa(&mvm->fw->ucode_capa,
				     IWL_UCODE_TLV_CAPA_UMAC_SCAN)))
		वापस;

	/* scan status must be locked क्रम proper checking */
	lockdep_निश्चित_held(&mvm->mutex);

	/* We first check अगर we were stopping a scan, in which हाल we
	 * just clear the stopping flag.  Then we check अगर it was a
	 * firmware initiated stop, in which हाल we need to inक्रमm
	 * mac80211.
	 * Note that we can have a stopping and a running scan
	 * simultaneously, but we can't have two dअगरferent types of
	 * scans stopping or running at the same समय (since LMAC
	 * करोesn't support it).
	 */

	अगर (mvm->scan_status & IWL_MVM_SCAN_STOPPING_SCHED) अणु
		WARN_ON_ONCE(mvm->scan_status & IWL_MVM_SCAN_STOPPING_REGULAR);

		IWL_DEBUG_SCAN(mvm, "Scheduled scan %s, EBS status %s\n",
			       पातed ? "aborted" : "completed",
			       iwl_mvm_ebs_status_str(scan_notअगर->ebs_status));
		IWL_DEBUG_SCAN(mvm,
			       "Last line %d, Last iteration %d, Time after last iteration %d\n",
			       scan_notअगर->last_schedule_line,
			       scan_notअगर->last_schedule_iteration,
			       __le32_to_cpu(scan_notअगर->समय_after_last_iter));

		mvm->scan_status &= ~IWL_MVM_SCAN_STOPPING_SCHED;
	पूर्ण अन्यथा अगर (mvm->scan_status & IWL_MVM_SCAN_STOPPING_REGULAR) अणु
		IWL_DEBUG_SCAN(mvm, "Regular scan %s, EBS status %s\n",
			       पातed ? "aborted" : "completed",
			       iwl_mvm_ebs_status_str(scan_notअगर->ebs_status));

		mvm->scan_status &= ~IWL_MVM_SCAN_STOPPING_REGULAR;
	पूर्ण अन्यथा अगर (mvm->scan_status & IWL_MVM_SCAN_SCHED) अणु
		WARN_ON_ONCE(mvm->scan_status & IWL_MVM_SCAN_REGULAR);

		IWL_DEBUG_SCAN(mvm, "Scheduled scan %s, EBS status %s\n",
			       पातed ? "aborted" : "completed",
			       iwl_mvm_ebs_status_str(scan_notअगर->ebs_status));
		IWL_DEBUG_SCAN(mvm,
			       "Last line %d, Last iteration %d, Time after last iteration %d (FW)\n",
			       scan_notअगर->last_schedule_line,
			       scan_notअगर->last_schedule_iteration,
			       __le32_to_cpu(scan_notअगर->समय_after_last_iter));

		mvm->scan_status &= ~IWL_MVM_SCAN_SCHED;
		ieee80211_sched_scan_stopped(mvm->hw);
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_DISABLED;
	पूर्ण अन्यथा अगर (mvm->scan_status & IWL_MVM_SCAN_REGULAR) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = पातed,
		पूर्ण;

		IWL_DEBUG_SCAN(mvm, "Regular scan %s, EBS status %s (FW)\n",
			       पातed ? "aborted" : "completed",
			       iwl_mvm_ebs_status_str(scan_notअगर->ebs_status));

		mvm->scan_status &= ~IWL_MVM_SCAN_REGULAR;
		ieee80211_scan_completed(mvm->hw, &info);
		cancel_delayed_work(&mvm->scan_समयout_dwork);
		iwl_mvm_resume_tcm(mvm);
	पूर्ण अन्यथा अणु
		IWL_ERR(mvm,
			"got scan complete notification but no scan is running\n");
	पूर्ण

	mvm->last_ebs_successful =
			scan_notअगर->ebs_status == IWL_SCAN_EBS_SUCCESS ||
			scan_notअगर->ebs_status == IWL_SCAN_EBS_INACTIVE;
पूर्ण

अटल पूर्णांक iwl_ssid_exist(u8 *ssid, u8 ssid_len, काष्ठा iwl_ssid_ie *ssid_list)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PROBE_OPTION_MAX; i++) अणु
		अगर (!ssid_list[i].len)
			अवरोध;
		अगर (ssid_list[i].len == ssid_len &&
		    !स_भेद(ssid_list->ssid, ssid, ssid_len))
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

/* We insert the SSIDs in an inverted order, because the FW will
 * invert it back.
 */
अटल व्योम iwl_scan_build_ssids(काष्ठा iwl_mvm_scan_params *params,
				 काष्ठा iwl_ssid_ie *ssids,
				 u32 *ssid_biपंचांगap)
अणु
	पूर्णांक i, j;
	पूर्णांक index;
	u32 पंचांगp_biपंचांगap = 0;

	/*
	 * copy SSIDs from match list.
	 * iwl_config_sched_scan_profiles() uses the order of these ssids to
	 * config match list.
	 */
	क्रम (i = 0, j = params->n_match_sets - 1;
	     j >= 0 && i < PROBE_OPTION_MAX;
	     i++, j--) अणु
		/* skip empty SSID matchsets */
		अगर (!params->match_sets[j].ssid.ssid_len)
			जारी;
		ssids[i].id = WLAN_EID_SSID;
		ssids[i].len = params->match_sets[j].ssid.ssid_len;
		स_नकल(ssids[i].ssid, params->match_sets[j].ssid.ssid,
		       ssids[i].len);
	पूर्ण

	/* add SSIDs from scan SSID list */
	क्रम (j = params->n_ssids - 1;
	     j >= 0 && i < PROBE_OPTION_MAX;
	     i++, j--) अणु
		index = iwl_ssid_exist(params->ssids[j].ssid,
				       params->ssids[j].ssid_len,
				       ssids);
		अगर (index < 0) अणु
			ssids[i].id = WLAN_EID_SSID;
			ssids[i].len = params->ssids[j].ssid_len;
			स_नकल(ssids[i].ssid, params->ssids[j].ssid,
			       ssids[i].len);
			पंचांगp_biपंचांगap |= BIT(i);
		पूर्ण अन्यथा अणु
			पंचांगp_biपंचांगap |= BIT(index);
		पूर्ण
	पूर्ण
	अगर (ssid_biपंचांगap)
		*ssid_biपंचांगap = पंचांगp_biपंचांगap;
पूर्ण

अटल पूर्णांक
iwl_mvm_config_sched_scan_profiles(काष्ठा iwl_mvm *mvm,
				   काष्ठा cfg80211_sched_scan_request *req)
अणु
	काष्ठा iwl_scan_offload_profile *profile;
	काष्ठा iwl_scan_offload_profile_cfg_v1 *profile_cfg_v1;
	काष्ठा iwl_scan_offload_blocklist *blocklist;
	काष्ठा iwl_scan_offload_profile_cfg_data *data;
	पूर्णांक max_profiles = iwl_umac_scan_get_max_profiles(mvm->fw);
	पूर्णांक profile_cfg_size = माप(*data) +
		माप(*profile) * max_profiles;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = SCAN_OFFLOAD_UPDATE_PROखाताS_CMD,
		.len[1] = profile_cfg_size,
		.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
		.dataflags[1] = IWL_HCMD_DFL_NOCOPY,
	पूर्ण;
	पूर्णांक blocklist_len;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (WARN_ON(req->n_match_sets > max_profiles))
		वापस -EIO;

	अगर (mvm->fw->ucode_capa.flags & IWL_UCODE_TLV_FLAGS_SHORT_BL)
		blocklist_len = IWL_SCAN_SHORT_BLACKLIST_LEN;
	अन्यथा
		blocklist_len = IWL_SCAN_MAX_BLACKLIST_LEN;

	blocklist = kसुस्मृति(blocklist_len, माप(*blocklist), GFP_KERNEL);
	अगर (!blocklist)
		वापस -ENOMEM;

	profile_cfg_v1 = kzalloc(profile_cfg_size, GFP_KERNEL);
	अगर (!profile_cfg_v1) अणु
		ret = -ENOMEM;
		जाओ मुक्त_blocklist;
	पूर्ण

	cmd.data[0] = blocklist;
	cmd.len[0] = माप(*blocklist) * blocklist_len;
	cmd.data[1] = profile_cfg_v1;

	/* अगर max_profile is MAX_PROखाताS_V2, we have the new API */
	अगर (max_profiles == IWL_SCAN_MAX_PROखाताS_V2) अणु
		काष्ठा iwl_scan_offload_profile_cfg *profile_cfg =
			(काष्ठा iwl_scan_offload_profile_cfg *)profile_cfg_v1;

		data = &profile_cfg->data;
	पूर्ण अन्यथा अणु
		data = &profile_cfg_v1->data;
	पूर्ण

	/* No blocklist configuration */
	data->num_profiles = req->n_match_sets;
	data->active_clients = SCAN_CLIENT_SCHED_SCAN;
	data->pass_match = SCAN_CLIENT_SCHED_SCAN;
	data->match_notअगरy = SCAN_CLIENT_SCHED_SCAN;

	अगर (!req->n_match_sets || !req->match_sets[0].ssid.ssid_len)
		data->any_beacon_notअगरy = SCAN_CLIENT_SCHED_SCAN;

	क्रम (i = 0; i < req->n_match_sets; i++) अणु
		profile = &profile_cfg_v1->profiles[i];
		profile->ssid_index = i;
		/* Support any cipher and auth algorithm */
		profile->unicast_cipher = 0xff;
		profile->auth_alg = 0xff;
		profile->network_type = IWL_NETWORK_TYPE_ANY;
		profile->band_selection = IWL_SCAN_OFFLOAD_SELECT_ANY;
		profile->client_biपंचांगap = SCAN_CLIENT_SCHED_SCAN;
	पूर्ण

	IWL_DEBUG_SCAN(mvm, "Sending scheduled scan profile config\n");

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	kमुक्त(profile_cfg_v1);
मुक्त_blocklist:
	kमुक्त(blocklist);

	वापस ret;
पूर्ण

अटल bool iwl_mvm_scan_pass_all(काष्ठा iwl_mvm *mvm,
				  काष्ठा cfg80211_sched_scan_request *req)
अणु
	अगर (req->n_match_sets && req->match_sets[0].ssid.ssid_len) अणु
		IWL_DEBUG_SCAN(mvm,
			       "Sending scheduled scan with filtering, n_match_sets %d\n",
			       req->n_match_sets);
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_DISABLED;
		वापस false;
	पूर्ण

	IWL_DEBUG_SCAN(mvm, "Sending Scheduled scan without filtering\n");

	mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_ENABLED;
	वापस true;
पूर्ण

अटल पूर्णांक iwl_mvm_lmac_scan_पात(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = SCAN_OFFLOAD_ABORT_CMD,
	पूर्ण;
	u32 status = CAN_ABORT_STATUS;

	ret = iwl_mvm_send_cmd_status(mvm, &cmd, &status);
	अगर (ret)
		वापस ret;

	अगर (status != CAN_ABORT_STATUS) अणु
		/*
		 * The scan पात will वापस 1 क्रम success or
		 * 2 क्रम "failure".  A failure condition can be
		 * due to simply not being in an active scan which
		 * can occur अगर we send the scan पात beक्रमe the
		 * microcode has notअगरied us that a scan is completed.
		 */
		IWL_DEBUG_SCAN(mvm, "SCAN OFFLOAD ABORT ret %d.\n", status);
		ret = -ENOENT;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_scan_fill_tx_cmd(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_scan_req_tx_cmd *tx_cmd,
				     bool no_cck)
अणु
	tx_cmd[0].tx_flags = cpu_to_le32(TX_CMD_FLG_SEQ_CTL |
					 TX_CMD_FLG_BT_DIS);
	tx_cmd[0].rate_n_flags = iwl_mvm_scan_rate_n_flags(mvm,
							   NL80211_BAND_2GHZ,
							   no_cck);

	अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
				  ADD_STA,
				  0) < 12) अणु
		tx_cmd[0].sta_id = mvm->aux_sta.sta_id;
		tx_cmd[1].sta_id = mvm->aux_sta.sta_id;

	/*
	 * Fw करोesn't use this sta anymore, pending deprecation via HOST API
	 * change
	 */
	पूर्ण अन्यथा अणु
		tx_cmd[0].sta_id = 0xff;
		tx_cmd[1].sta_id = 0xff;
	पूर्ण

	tx_cmd[1].tx_flags = cpu_to_le32(TX_CMD_FLG_SEQ_CTL |
					 TX_CMD_FLG_BT_DIS);

	tx_cmd[1].rate_n_flags = iwl_mvm_scan_rate_n_flags(mvm,
							   NL80211_BAND_5GHZ,
							   no_cck);
पूर्ण

अटल व्योम
iwl_mvm_lmac_scan_cfg_channels(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_channel **channels,
			       पूर्णांक n_channels, u32 ssid_biपंचांगap,
			       काष्ठा iwl_scan_req_lmac *cmd)
अणु
	काष्ठा iwl_scan_channel_cfg_lmac *channel_cfg = (व्योम *)&cmd->data;
	पूर्णांक i;

	क्रम (i = 0; i < n_channels; i++) अणु
		channel_cfg[i].channel_num =
			cpu_to_le16(channels[i]->hw_value);
		channel_cfg[i].iter_count = cpu_to_le16(1);
		channel_cfg[i].iter_पूर्णांकerval = 0;
		channel_cfg[i].flags =
			cpu_to_le32(IWL_UNIFIED_SCAN_CHANNEL_PARTIAL |
				    ssid_biपंचांगap);
	पूर्ण
पूर्ण

अटल u8 *iwl_mvm_copy_and_insert_ds_elem(काष्ठा iwl_mvm *mvm, स्थिर u8 *ies,
					   माप_प्रकार len, u8 *स्थिर pos)
अणु
	अटल स्थिर u8 beक्रमe_ds_params[] = अणु
			WLAN_EID_SSID,
			WLAN_EID_SUPP_RATES,
			WLAN_EID_REQUEST,
			WLAN_EID_EXT_SUPP_RATES,
	पूर्ण;
	माप_प्रकार offs;
	u8 *newpos = pos;

	अगर (!iwl_mvm_rrm_scan_needed(mvm)) अणु
		स_नकल(newpos, ies, len);
		वापस newpos + len;
	पूर्ण

	offs = ieee80211_ie_split(ies, len,
				  beक्रमe_ds_params,
				  ARRAY_SIZE(beक्रमe_ds_params),
				  0);

	स_नकल(newpos, ies, offs);
	newpos += offs;

	/* Add a placeholder क्रम DS Parameter Set element */
	*newpos++ = WLAN_EID_DS_PARAMS;
	*newpos++ = 1;
	*newpos++ = 0;

	स_नकल(newpos, ies + offs, len - offs);
	newpos += len - offs;

	वापस newpos;
पूर्ण

#घोषणा WFA_TPC_IE_LEN	9

अटल व्योम iwl_mvm_add_tpc_report_ie(u8 *pos)
अणु
	pos[0] = WLAN_EID_VENDOR_SPECIFIC;
	pos[1] = WFA_TPC_IE_LEN - 2;
	pos[2] = (WLAN_OUI_MICROSOFT >> 16) & 0xff;
	pos[3] = (WLAN_OUI_MICROSOFT >> 8) & 0xff;
	pos[4] = WLAN_OUI_MICROSOFT & 0xff;
	pos[5] = WLAN_OUI_TYPE_MICROSOFT_TPC;
	pos[6] = 0;
	/* pos[7] - tx घातer will be inserted by the FW */
	pos[7] = 0;
	pos[8] = 0;
पूर्ण

अटल व्योम
iwl_mvm_build_scan_probe(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_scan_ies *ies,
			 काष्ठा iwl_mvm_scan_params *params)
अणु
	काष्ठा ieee80211_mgmt *frame = (व्योम *)params->preq.buf;
	u8 *pos, *newpos;
	स्थिर u8 *mac_addr = params->flags & NL80211_SCAN_FLAG_RANDOM_ADDR ?
		params->mac_addr : शून्य;

	/*
	 * Unक्रमtunately, right now the offload scan करोesn't support अक्रमomising
	 * within the firmware, so until the firmware API is पढ़ोy we implement
	 * it in the driver. This means that the scan iterations won't really be
	 * अक्रमom, only when it's restarted, but at least that helps a bit.
	 */
	अगर (mac_addr)
		get_अक्रमom_mask_addr(frame->sa, mac_addr,
				     params->mac_addr_mask);
	अन्यथा
		स_नकल(frame->sa, vअगर->addr, ETH_ALEN);

	frame->frame_control = cpu_to_le16(IEEE80211_STYPE_PROBE_REQ);
	eth_broadcast_addr(frame->da);
	eth_broadcast_addr(frame->bssid);
	frame->seq_ctrl = 0;

	pos = frame->u.probe_req.variable;
	*pos++ = WLAN_EID_SSID;
	*pos++ = 0;

	params->preq.mac_header.offset = 0;
	params->preq.mac_header.len = cpu_to_le16(24 + 2);

	/* Insert ds parameter set element on 2.4 GHz band */
	newpos = iwl_mvm_copy_and_insert_ds_elem(mvm,
						 ies->ies[NL80211_BAND_2GHZ],
						 ies->len[NL80211_BAND_2GHZ],
						 pos);
	params->preq.band_data[0].offset = cpu_to_le16(pos - params->preq.buf);
	params->preq.band_data[0].len = cpu_to_le16(newpos - pos);
	pos = newpos;

	स_नकल(pos, ies->ies[NL80211_BAND_5GHZ],
	       ies->len[NL80211_BAND_5GHZ]);
	params->preq.band_data[1].offset = cpu_to_le16(pos - params->preq.buf);
	params->preq.band_data[1].len =
		cpu_to_le16(ies->len[NL80211_BAND_5GHZ]);
	pos += ies->len[NL80211_BAND_5GHZ];

	स_नकल(pos, ies->ies[NL80211_BAND_6GHZ],
	       ies->len[NL80211_BAND_6GHZ]);
	params->preq.band_data[2].offset = cpu_to_le16(pos - params->preq.buf);
	params->preq.band_data[2].len =
		cpu_to_le16(ies->len[NL80211_BAND_6GHZ]);
	pos += ies->len[NL80211_BAND_6GHZ];
	स_नकल(pos, ies->common_ies, ies->common_ie_len);
	params->preq.common_data.offset = cpu_to_le16(pos - params->preq.buf);

	अगर (iwl_mvm_rrm_scan_needed(mvm) &&
	    !fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_WFA_TPC_REP_IE_SUPPORT)) अणु
		iwl_mvm_add_tpc_report_ie(pos + ies->common_ie_len);
		params->preq.common_data.len = cpu_to_le16(ies->common_ie_len +
							   WFA_TPC_IE_LEN);
	पूर्ण अन्यथा अणु
		params->preq.common_data.len = cpu_to_le16(ies->common_ie_len);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_scan_lmac_dwell(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_scan_req_lmac *cmd,
				    काष्ठा iwl_mvm_scan_params *params)
अणु
	cmd->active_dwell = IWL_SCAN_DWELL_ACTIVE;
	cmd->passive_dwell = IWL_SCAN_DWELL_PASSIVE;
	cmd->fragmented_dwell = IWL_SCAN_DWELL_FRAGMENTED;
	cmd->extended_dwell = IWL_SCAN_DWELL_EXTENDED;
	cmd->max_out_समय = cpu_to_le32(scan_timing[params->type].max_out_समय);
	cmd->suspend_समय = cpu_to_le32(scan_timing[params->type].suspend_समय);
	cmd->scan_prio = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
पूर्ण

अटल अंतरभूत bool iwl_mvm_scan_fits(काष्ठा iwl_mvm *mvm, पूर्णांक n_ssids,
				     काष्ठा ieee80211_scan_ies *ies,
				     पूर्णांक n_channels)
अणु
	वापस ((n_ssids <= PROBE_OPTION_MAX) &&
		(n_channels <= mvm->fw->ucode_capa.n_scan_channels) &
		(ies->common_ie_len +
		 ies->len[NL80211_BAND_2GHZ] +
		 ies->len[NL80211_BAND_5GHZ] <=
		 iwl_mvm_max_scan_ie_fw_cmd_room(mvm)));
पूर्ण

अटल अंतरभूत bool iwl_mvm_scan_use_ebs(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_vअगर *vअगर)
अणु
	स्थिर काष्ठा iwl_ucode_capabilities *capa = &mvm->fw->ucode_capa;
	bool low_latency;

	अगर (iwl_mvm_is_cdb_supported(mvm))
		low_latency = iwl_mvm_low_latency_band(mvm, NL80211_BAND_5GHZ);
	अन्यथा
		low_latency = iwl_mvm_low_latency(mvm);

	/* We can only use EBS अगर:
	 *	1. the feature is supported;
	 *	2. the last EBS was successful;
	 *	3. अगर only single scan, the single scan EBS API is supported;
	 *	4. it's not a p2p find operation.
	 *	5. we are not in low latency mode,
	 *	   or अगर fragmented ebs is supported by the FW
	 */
	वापस ((capa->flags & IWL_UCODE_TLV_FLAGS_EBS_SUPPORT) &&
		mvm->last_ebs_successful && IWL_MVM_ENABLE_EBS &&
		vअगर->type != NL80211_IFTYPE_P2P_DEVICE &&
		(!low_latency || iwl_mvm_is_frag_ebs_supported(mvm)));
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_regular_scan(काष्ठा iwl_mvm_scan_params *params)
अणु
	वापस params->n_scan_plans == 1 &&
		params->scan_plans[0].iterations == 1;
पूर्ण

अटल bool iwl_mvm_is_scan_fragmented(क्रमागत iwl_mvm_scan_type type)
अणु
	वापस (type == IWL_SCAN_TYPE_FRAGMENTED ||
		type == IWL_SCAN_TYPE_FAST_BALANCE);
पूर्ण

अटल पूर्णांक iwl_mvm_scan_lmac_flags(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_mvm_scan_params *params,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक flags = 0;

	अगर (params->n_ssids == 0)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_PASSIVE;

	अगर (params->n_ssids == 1 && params->ssids[0].ssid_len != 0)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_PRE_CONNECTION;

	अगर (iwl_mvm_is_scan_fragmented(params->type))
		flags |= IWL_MVM_LMAC_SCAN_FLAG_FRAGMENTED;

	अगर (iwl_mvm_rrm_scan_needed(mvm) &&
	    fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_WFA_TPC_REP_IE_SUPPORT))
		flags |= IWL_MVM_LMAC_SCAN_FLAGS_RRM_ENABLED;

	अगर (params->pass_all)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_PASS_ALL;
	अन्यथा
		flags |= IWL_MVM_LMAC_SCAN_FLAG_MATCH;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (mvm->scan_iter_notअगर_enabled)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_ITER_COMPLETE;
#पूर्ण_अगर

	अगर (mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_ENABLED)
		flags |= IWL_MVM_LMAC_SCAN_FLAG_ITER_COMPLETE;

	अगर (iwl_mvm_is_regular_scan(params) &&
	    vअगर->type != NL80211_IFTYPE_P2P_DEVICE &&
	    !iwl_mvm_is_scan_fragmented(params->type))
		flags |= IWL_MVM_LMAC_SCAN_FLAG_EXTENDED_DWELL;

	वापस flags;
पूर्ण

अटल व्योम
iwl_mvm_scan_set_legacy_probe_req(काष्ठा iwl_scan_probe_req_v1 *p_req,
				  काष्ठा iwl_scan_probe_req *src_p_req)
अणु
	पूर्णांक i;

	p_req->mac_header = src_p_req->mac_header;
	क्रम (i = 0; i < SCAN_NUM_BAND_PROBE_DATA_V_1; i++)
		p_req->band_data[i] = src_p_req->band_data[i];
	p_req->common_data = src_p_req->common_data;
	स_नकल(p_req->buf, src_p_req->buf, माप(p_req->buf));
पूर्ण

अटल पूर्णांक iwl_mvm_scan_lmac(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा iwl_mvm_scan_params *params)
अणु
	काष्ठा iwl_scan_req_lmac *cmd = mvm->scan_cmd;
	काष्ठा iwl_scan_probe_req_v1 *preq =
		(व्योम *)(cmd->data + माप(काष्ठा iwl_scan_channel_cfg_lmac) *
			 mvm->fw->ucode_capa.n_scan_channels);
	u32 ssid_biपंचांगap = 0;
	पूर्णांक i;
	u8 band;

	अगर (WARN_ON(params->n_scan_plans > IWL_MAX_SCHED_SCAN_PLANS))
		वापस -EINVAL;

	iwl_mvm_scan_lmac_dwell(mvm, cmd, params);

	cmd->rx_chain_select = iwl_mvm_scan_rx_chain(mvm);
	cmd->iter_num = cpu_to_le32(1);
	cmd->n_channels = (u8)params->n_channels;

	cmd->delay = cpu_to_le32(params->delay);

	cmd->scan_flags = cpu_to_le32(iwl_mvm_scan_lmac_flags(mvm, params,
							      vअगर));

	band = iwl_mvm_phy_band_from_nl80211(params->channels[0]->band);
	cmd->flags = cpu_to_le32(band);
	cmd->filter_flags = cpu_to_le32(MAC_FILTER_ACCEPT_GRP |
					MAC_FILTER_IN_BEACON);
	iwl_mvm_scan_fill_tx_cmd(mvm, cmd->tx_cmd, params->no_cck);
	iwl_scan_build_ssids(params, cmd->direct_scan, &ssid_biपंचांगap);

	/* this API uses bits 1-20 instead of 0-19 */
	ssid_biपंचांगap <<= 1;

	क्रम (i = 0; i < params->n_scan_plans; i++) अणु
		काष्ठा cfg80211_sched_scan_plan *scan_plan =
			&params->scan_plans[i];

		cmd->schedule[i].delay =
			cpu_to_le16(scan_plan->पूर्णांकerval);
		cmd->schedule[i].iterations = scan_plan->iterations;
		cmd->schedule[i].full_scan_mul = 1;
	पूर्ण

	/*
	 * If the number of iterations of the last scan plan is set to
	 * zero, it should run infinitely. However, this is not always the हाल.
	 * For example, when regular scan is requested the driver sets one scan
	 * plan with one iteration.
	 */
	अगर (!cmd->schedule[i - 1].iterations)
		cmd->schedule[i - 1].iterations = 0xff;

	अगर (iwl_mvm_scan_use_ebs(mvm, vअगर)) अणु
		cmd->channel_opt[0].flags =
			cpu_to_le16(IWL_SCAN_CHANNEL_FLAG_EBS |
				    IWL_SCAN_CHANNEL_FLAG_EBS_ACCURATE |
				    IWL_SCAN_CHANNEL_FLAG_CACHE_ADD);
		cmd->channel_opt[0].non_ebs_ratio =
			cpu_to_le16(IWL_DENSE_EBS_SCAN_RATIO);
		cmd->channel_opt[1].flags =
			cpu_to_le16(IWL_SCAN_CHANNEL_FLAG_EBS |
				    IWL_SCAN_CHANNEL_FLAG_EBS_ACCURATE |
				    IWL_SCAN_CHANNEL_FLAG_CACHE_ADD);
		cmd->channel_opt[1].non_ebs_ratio =
			cpu_to_le16(IWL_SPARSE_EBS_SCAN_RATIO);
	पूर्ण

	iwl_mvm_lmac_scan_cfg_channels(mvm, params->channels,
				       params->n_channels, ssid_biपंचांगap, cmd);

	iwl_mvm_scan_set_legacy_probe_req(preq, &params->preq);

	वापस 0;
पूर्ण

अटल पूर्णांक rate_to_scan_rate_flag(अचिन्हित पूर्णांक rate)
अणु
	अटल स्थिर पूर्णांक rate_to_scan_rate[IWL_RATE_COUNT] = अणु
		[IWL_RATE_1M_INDEX]	= SCAN_CONFIG_RATE_1M,
		[IWL_RATE_2M_INDEX]	= SCAN_CONFIG_RATE_2M,
		[IWL_RATE_5M_INDEX]	= SCAN_CONFIG_RATE_5M,
		[IWL_RATE_11M_INDEX]	= SCAN_CONFIG_RATE_11M,
		[IWL_RATE_6M_INDEX]	= SCAN_CONFIG_RATE_6M,
		[IWL_RATE_9M_INDEX]	= SCAN_CONFIG_RATE_9M,
		[IWL_RATE_12M_INDEX]	= SCAN_CONFIG_RATE_12M,
		[IWL_RATE_18M_INDEX]	= SCAN_CONFIG_RATE_18M,
		[IWL_RATE_24M_INDEX]	= SCAN_CONFIG_RATE_24M,
		[IWL_RATE_36M_INDEX]	= SCAN_CONFIG_RATE_36M,
		[IWL_RATE_48M_INDEX]	= SCAN_CONFIG_RATE_48M,
		[IWL_RATE_54M_INDEX]	= SCAN_CONFIG_RATE_54M,
	पूर्ण;

	वापस rate_to_scan_rate[rate];
पूर्ण

अटल __le32 iwl_mvm_scan_config_rates(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा ieee80211_supported_band *band;
	अचिन्हित पूर्णांक rates = 0;
	पूर्णांक i;

	band = &mvm->nvm_data->bands[NL80211_BAND_2GHZ];
	क्रम (i = 0; i < band->n_bitrates; i++)
		rates |= rate_to_scan_rate_flag(band->bitrates[i].hw_value);
	band = &mvm->nvm_data->bands[NL80211_BAND_5GHZ];
	क्रम (i = 0; i < band->n_bitrates; i++)
		rates |= rate_to_scan_rate_flag(band->bitrates[i].hw_value);

	/* Set both basic rates and supported rates */
	rates |= SCAN_CONFIG_SUPPORTED_RATE(rates);

	वापस cpu_to_le32(rates);
पूर्ण

अटल व्योम iwl_mvm_fill_scan_dwell(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_scan_dwell *dwell)
अणु
	dwell->active = IWL_SCAN_DWELL_ACTIVE;
	dwell->passive = IWL_SCAN_DWELL_PASSIVE;
	dwell->fragmented = IWL_SCAN_DWELL_FRAGMENTED;
	dwell->extended = IWL_SCAN_DWELL_EXTENDED;
पूर्ण

अटल व्योम iwl_mvm_fill_channels(काष्ठा iwl_mvm *mvm, u8 *channels,
				  u32 max_channels)
अणु
	काष्ठा ieee80211_supported_band *band;
	पूर्णांक i, j = 0;

	band = &mvm->nvm_data->bands[NL80211_BAND_2GHZ];
	क्रम (i = 0; i < band->n_channels && j < max_channels; i++, j++)
		channels[j] = band->channels[i].hw_value;
	band = &mvm->nvm_data->bands[NL80211_BAND_5GHZ];
	क्रम (i = 0; i < band->n_channels && j < max_channels; i++, j++)
		channels[j] = band->channels[i].hw_value;
पूर्ण

अटल व्योम iwl_mvm_fill_scan_config_v1(काष्ठा iwl_mvm *mvm, व्योम *config,
					u32 flags, u8 channel_flags,
					u32 max_channels)
अणु
	क्रमागत iwl_mvm_scan_type type = iwl_mvm_get_scan_type(mvm, शून्य);
	काष्ठा iwl_scan_config_v1 *cfg = config;

	cfg->flags = cpu_to_le32(flags);
	cfg->tx_chains = cpu_to_le32(iwl_mvm_get_valid_tx_ant(mvm));
	cfg->rx_chains = cpu_to_le32(iwl_mvm_scan_rx_ant(mvm));
	cfg->legacy_rates = iwl_mvm_scan_config_rates(mvm);
	cfg->out_of_channel_समय = cpu_to_le32(scan_timing[type].max_out_समय);
	cfg->suspend_समय = cpu_to_le32(scan_timing[type].suspend_समय);

	iwl_mvm_fill_scan_dwell(mvm, &cfg->dwell);

	स_नकल(&cfg->mac_addr, &mvm->addresses[0].addr, ETH_ALEN);

	/* This function should not be called when using ADD_STA ver >=12 */
	WARN_ON_ONCE(iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
					   ADD_STA, 0) >= 12);

	cfg->bcast_sta_id = mvm->aux_sta.sta_id;
	cfg->channel_flags = channel_flags;

	iwl_mvm_fill_channels(mvm, cfg->channel_array, max_channels);
पूर्ण

अटल व्योम iwl_mvm_fill_scan_config_v2(काष्ठा iwl_mvm *mvm, व्योम *config,
					u32 flags, u8 channel_flags,
					u32 max_channels)
अणु
	काष्ठा iwl_scan_config_v2 *cfg = config;

	cfg->flags = cpu_to_le32(flags);
	cfg->tx_chains = cpu_to_le32(iwl_mvm_get_valid_tx_ant(mvm));
	cfg->rx_chains = cpu_to_le32(iwl_mvm_scan_rx_ant(mvm));
	cfg->legacy_rates = iwl_mvm_scan_config_rates(mvm);

	अगर (iwl_mvm_is_cdb_supported(mvm)) अणु
		क्रमागत iwl_mvm_scan_type lb_type, hb_type;

		lb_type = iwl_mvm_get_scan_type_band(mvm, शून्य,
						     NL80211_BAND_2GHZ);
		hb_type = iwl_mvm_get_scan_type_band(mvm, शून्य,
						     NL80211_BAND_5GHZ);

		cfg->out_of_channel_समय[SCAN_LB_LMAC_IDX] =
			cpu_to_le32(scan_timing[lb_type].max_out_समय);
		cfg->suspend_समय[SCAN_LB_LMAC_IDX] =
			cpu_to_le32(scan_timing[lb_type].suspend_समय);

		cfg->out_of_channel_समय[SCAN_HB_LMAC_IDX] =
			cpu_to_le32(scan_timing[hb_type].max_out_समय);
		cfg->suspend_समय[SCAN_HB_LMAC_IDX] =
			cpu_to_le32(scan_timing[hb_type].suspend_समय);
	पूर्ण अन्यथा अणु
		क्रमागत iwl_mvm_scan_type type =
			iwl_mvm_get_scan_type(mvm, शून्य);

		cfg->out_of_channel_समय[SCAN_LB_LMAC_IDX] =
			cpu_to_le32(scan_timing[type].max_out_समय);
		cfg->suspend_समय[SCAN_LB_LMAC_IDX] =
			cpu_to_le32(scan_timing[type].suspend_समय);
	पूर्ण

	iwl_mvm_fill_scan_dwell(mvm, &cfg->dwell);

	स_नकल(&cfg->mac_addr, &mvm->addresses[0].addr, ETH_ALEN);

	/* This function should not be called when using ADD_STA ver >=12 */
	WARN_ON_ONCE(iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
					   ADD_STA, 0) >= 12);

	cfg->bcast_sta_id = mvm->aux_sta.sta_id;
	cfg->channel_flags = channel_flags;

	iwl_mvm_fill_channels(mvm, cfg->channel_array, max_channels);
पूर्ण

अटल पूर्णांक iwl_mvm_legacy_config_scan(काष्ठा iwl_mvm *mvm)
अणु
	व्योम *cfg;
	पूर्णांक ret, cmd_size;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = iwl_cmd_id(SCAN_CFG_CMD, IWL_ALWAYS_LONG_GROUP, 0),
	पूर्ण;
	क्रमागत iwl_mvm_scan_type type;
	क्रमागत iwl_mvm_scan_type hb_type = IWL_SCAN_TYPE_NOT_SET;
	पूर्णांक num_channels =
		mvm->nvm_data->bands[NL80211_BAND_2GHZ].n_channels +
		mvm->nvm_data->bands[NL80211_BAND_5GHZ].n_channels;
	u32 flags;
	u8 channel_flags;

	अगर (WARN_ON(num_channels > mvm->fw->ucode_capa.n_scan_channels))
		num_channels = mvm->fw->ucode_capa.n_scan_channels;

	अगर (iwl_mvm_is_cdb_supported(mvm)) अणु
		type = iwl_mvm_get_scan_type_band(mvm, शून्य,
						  NL80211_BAND_2GHZ);
		hb_type = iwl_mvm_get_scan_type_band(mvm, शून्य,
						     NL80211_BAND_5GHZ);
		अगर (type == mvm->scan_type && hb_type == mvm->hb_scan_type)
			वापस 0;
	पूर्ण अन्यथा अणु
		type = iwl_mvm_get_scan_type(mvm, शून्य);
		अगर (type == mvm->scan_type)
			वापस 0;
	पूर्ण

	अगर (iwl_mvm_cdb_scan_api(mvm))
		cmd_size = माप(काष्ठा iwl_scan_config_v2);
	अन्यथा
		cmd_size = माप(काष्ठा iwl_scan_config_v1);
	cmd_size += mvm->fw->ucode_capa.n_scan_channels;

	cfg = kzalloc(cmd_size, GFP_KERNEL);
	अगर (!cfg)
		वापस -ENOMEM;

	flags = SCAN_CONFIG_FLAG_ACTIVATE |
		 SCAN_CONFIG_FLAG_ALLOW_CHUB_REQS |
		 SCAN_CONFIG_FLAG_SET_TX_CHAINS |
		 SCAN_CONFIG_FLAG_SET_RX_CHAINS |
		 SCAN_CONFIG_FLAG_SET_AUX_STA_ID |
		 SCAN_CONFIG_FLAG_SET_ALL_TIMES |
		 SCAN_CONFIG_FLAG_SET_LEGACY_RATES |
		 SCAN_CONFIG_FLAG_SET_MAC_ADDR |
		 SCAN_CONFIG_FLAG_SET_CHANNEL_FLAGS |
		 SCAN_CONFIG_N_CHANNELS(num_channels) |
		 (iwl_mvm_is_scan_fragmented(type) ?
		  SCAN_CONFIG_FLAG_SET_FRAGMENTED :
		  SCAN_CONFIG_FLAG_CLEAR_FRAGMENTED);

	channel_flags = IWL_CHANNEL_FLAG_EBS |
			IWL_CHANNEL_FLAG_ACCURATE_EBS |
			IWL_CHANNEL_FLAG_EBS_ADD |
			IWL_CHANNEL_FLAG_PRE_SCAN_PASSIVE2ACTIVE;

	/*
	 * Check क्रम fragmented scan on LMAC2 - high band.
	 * LMAC1 - low band is checked above.
	 */
	अगर (iwl_mvm_cdb_scan_api(mvm)) अणु
		अगर (iwl_mvm_is_cdb_supported(mvm))
			flags |= (iwl_mvm_is_scan_fragmented(hb_type)) ?
				 SCAN_CONFIG_FLAG_SET_LMAC2_FRAGMENTED :
				 SCAN_CONFIG_FLAG_CLEAR_LMAC2_FRAGMENTED;
		iwl_mvm_fill_scan_config_v2(mvm, cfg, flags, channel_flags,
					    num_channels);
	पूर्ण अन्यथा अणु
		iwl_mvm_fill_scan_config_v1(mvm, cfg, flags, channel_flags,
					    num_channels);
	पूर्ण

	cmd.data[0] = cfg;
	cmd.len[0] = cmd_size;
	cmd.dataflags[0] = IWL_HCMD_DFL_NOCOPY;

	IWL_DEBUG_SCAN(mvm, "Sending UMAC scan config\n");

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (!ret) अणु
		mvm->scan_type = type;
		mvm->hb_scan_type = hb_type;
	पूर्ण

	kमुक्त(cfg);
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_config_scan(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_scan_config cfg;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = iwl_cmd_id(SCAN_CFG_CMD, IWL_ALWAYS_LONG_GROUP, 0),
		.len[0] = माप(cfg),
		.data[0] = &cfg,
		.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
	पूर्ण;

	अगर (!iwl_mvm_is_reduced_config_scan_supported(mvm))
		वापस iwl_mvm_legacy_config_scan(mvm);

	स_रखो(&cfg, 0, माप(cfg));

	अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
				  ADD_STA, 0) < 12) अणु
		cfg.bcast_sta_id = mvm->aux_sta.sta_id;
	पूर्ण अन्यथा अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
					 SCAN_CFG_CMD, 0) < 5) अणु
		/*
		 * Fw करोesn't use this sta anymore. Deprecated on SCAN_CFG_CMD
		 * version 5.
		 */
		cfg.bcast_sta_id = 0xff;
	पूर्ण

	cfg.tx_chains = cpu_to_le32(iwl_mvm_get_valid_tx_ant(mvm));
	cfg.rx_chains = cpu_to_le32(iwl_mvm_scan_rx_ant(mvm));

	IWL_DEBUG_SCAN(mvm, "Sending UMAC scan config\n");

	वापस iwl_mvm_send_cmd(mvm, &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_scan_uid_by_status(काष्ठा iwl_mvm *mvm, पूर्णांक status)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mvm->max_scans; i++)
		अगर (mvm->scan_uid_status[i] == status)
			वापस i;

	वापस -ENOENT;
पूर्ण

अटल व्योम iwl_mvm_scan_umac_dwell(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_scan_req_umac *cmd,
				    काष्ठा iwl_mvm_scan_params *params)
अणु
	काष्ठा iwl_mvm_scan_timing_params *timing, *hb_timing;
	u8 active_dwell, passive_dwell;

	timing = &scan_timing[params->type];
	active_dwell = IWL_SCAN_DWELL_ACTIVE;
	passive_dwell = IWL_SCAN_DWELL_PASSIVE;

	अगर (iwl_mvm_is_adaptive_dwell_supported(mvm)) अणु
		cmd->v7.adwell_शेष_n_aps_social =
			IWL_SCAN_ADWELL_DEFAULT_N_APS_SOCIAL;
		cmd->v7.adwell_शेष_n_aps =
			IWL_SCAN_ADWELL_DEFAULT_LB_N_APS;

		अगर (iwl_mvm_is_adwell_hb_ap_num_supported(mvm))
			cmd->v9.adwell_शेष_hb_n_aps =
				IWL_SCAN_ADWELL_DEFAULT_HB_N_APS;

		/* अगर custom max budget was configured with debugfs */
		अगर (IWL_MVM_ADWELL_MAX_BUDGET)
			cmd->v7.adwell_max_budget =
				cpu_to_le16(IWL_MVM_ADWELL_MAX_BUDGET);
		अन्यथा अगर (params->ssids && params->ssids[0].ssid_len)
			cmd->v7.adwell_max_budget =
				cpu_to_le16(IWL_SCAN_ADWELL_MAX_BUDGET_सूचीECTED_SCAN);
		अन्यथा
			cmd->v7.adwell_max_budget =
				cpu_to_le16(IWL_SCAN_ADWELL_MAX_BUDGET_FULL_SCAN);

		cmd->v7.scan_priority = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
		cmd->v7.max_out_समय[SCAN_LB_LMAC_IDX] =
			cpu_to_le32(timing->max_out_समय);
		cmd->v7.suspend_समय[SCAN_LB_LMAC_IDX] =
			cpu_to_le32(timing->suspend_समय);

		अगर (iwl_mvm_is_cdb_supported(mvm)) अणु
			hb_timing = &scan_timing[params->hb_type];

			cmd->v7.max_out_समय[SCAN_HB_LMAC_IDX] =
				cpu_to_le32(hb_timing->max_out_समय);
			cmd->v7.suspend_समय[SCAN_HB_LMAC_IDX] =
				cpu_to_le32(hb_timing->suspend_समय);
		पूर्ण

		अगर (!iwl_mvm_is_adaptive_dwell_v2_supported(mvm)) अणु
			cmd->v7.active_dwell = active_dwell;
			cmd->v7.passive_dwell = passive_dwell;
			cmd->v7.fragmented_dwell = IWL_SCAN_DWELL_FRAGMENTED;
		पूर्ण अन्यथा अणु
			cmd->v8.active_dwell[SCAN_LB_LMAC_IDX] = active_dwell;
			cmd->v8.passive_dwell[SCAN_LB_LMAC_IDX] = passive_dwell;
			अगर (iwl_mvm_is_cdb_supported(mvm)) अणु
				cmd->v8.active_dwell[SCAN_HB_LMAC_IDX] =
					active_dwell;
				cmd->v8.passive_dwell[SCAN_HB_LMAC_IDX] =
					passive_dwell;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		cmd->v1.extended_dwell = IWL_SCAN_DWELL_EXTENDED;
		cmd->v1.active_dwell = active_dwell;
		cmd->v1.passive_dwell = passive_dwell;
		cmd->v1.fragmented_dwell = IWL_SCAN_DWELL_FRAGMENTED;

		अगर (iwl_mvm_is_cdb_supported(mvm)) अणु
			hb_timing = &scan_timing[params->hb_type];

			cmd->v6.max_out_समय[SCAN_HB_LMAC_IDX] =
					cpu_to_le32(hb_timing->max_out_समय);
			cmd->v6.suspend_समय[SCAN_HB_LMAC_IDX] =
					cpu_to_le32(hb_timing->suspend_समय);
		पूर्ण

		अगर (iwl_mvm_cdb_scan_api(mvm)) अणु
			cmd->v6.scan_priority =
				cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
			cmd->v6.max_out_समय[SCAN_LB_LMAC_IDX] =
				cpu_to_le32(timing->max_out_समय);
			cmd->v6.suspend_समय[SCAN_LB_LMAC_IDX] =
				cpu_to_le32(timing->suspend_समय);
		पूर्ण अन्यथा अणु
			cmd->v1.scan_priority =
				cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
			cmd->v1.max_out_समय =
				cpu_to_le32(timing->max_out_समय);
			cmd->v1.suspend_समय =
				cpu_to_le32(timing->suspend_समय);
		पूर्ण
	पूर्ण

	अगर (iwl_mvm_is_regular_scan(params))
		cmd->ooc_priority = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
	अन्यथा
		cmd->ooc_priority = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_2);
पूर्ण

अटल u32 iwl_mvm_scan_umac_ooc_priority(काष्ठा iwl_mvm_scan_params *params)
अणु
	वापस iwl_mvm_is_regular_scan(params) ?
		IWL_SCAN_PRIORITY_EXT_6 :
		IWL_SCAN_PRIORITY_EXT_2;
पूर्ण

अटल व्योम
iwl_mvm_scan_umac_dwell_v10(काष्ठा iwl_mvm *mvm,
			    काष्ठा iwl_scan_general_params_v10 *general_params,
			    काष्ठा iwl_mvm_scan_params *params)
अणु
	काष्ठा iwl_mvm_scan_timing_params *timing, *hb_timing;
	u8 active_dwell, passive_dwell;

	timing = &scan_timing[params->type];
	active_dwell = IWL_SCAN_DWELL_ACTIVE;
	passive_dwell = IWL_SCAN_DWELL_PASSIVE;

	general_params->adwell_शेष_social_chn =
		IWL_SCAN_ADWELL_DEFAULT_N_APS_SOCIAL;
	general_params->adwell_शेष_2g = IWL_SCAN_ADWELL_DEFAULT_LB_N_APS;
	general_params->adwell_शेष_5g = IWL_SCAN_ADWELL_DEFAULT_HB_N_APS;

	/* अगर custom max budget was configured with debugfs */
	अगर (IWL_MVM_ADWELL_MAX_BUDGET)
		general_params->adwell_max_budget =
			cpu_to_le16(IWL_MVM_ADWELL_MAX_BUDGET);
	अन्यथा अगर (params->ssids && params->ssids[0].ssid_len)
		general_params->adwell_max_budget =
			cpu_to_le16(IWL_SCAN_ADWELL_MAX_BUDGET_सूचीECTED_SCAN);
	अन्यथा
		general_params->adwell_max_budget =
			cpu_to_le16(IWL_SCAN_ADWELL_MAX_BUDGET_FULL_SCAN);

	general_params->scan_priority = cpu_to_le32(IWL_SCAN_PRIORITY_EXT_6);
	general_params->max_out_of_समय[SCAN_LB_LMAC_IDX] =
		cpu_to_le32(timing->max_out_समय);
	general_params->suspend_समय[SCAN_LB_LMAC_IDX] =
		cpu_to_le32(timing->suspend_समय);

	hb_timing = &scan_timing[params->hb_type];

	general_params->max_out_of_समय[SCAN_HB_LMAC_IDX] =
		cpu_to_le32(hb_timing->max_out_समय);
	general_params->suspend_समय[SCAN_HB_LMAC_IDX] =
		cpu_to_le32(hb_timing->suspend_समय);

	general_params->active_dwell[SCAN_LB_LMAC_IDX] = active_dwell;
	general_params->passive_dwell[SCAN_LB_LMAC_IDX] = passive_dwell;
	general_params->active_dwell[SCAN_HB_LMAC_IDX] = active_dwell;
	general_params->passive_dwell[SCAN_HB_LMAC_IDX] = passive_dwell;
पूर्ण

काष्ठा iwl_mvm_scan_channel_segment अणु
	u8 start_idx;
	u8 end_idx;
	u8 first_channel_id;
	u8 last_channel_id;
	u8 channel_spacing_shअगरt;
	u8 band;
पूर्ण;

अटल स्थिर काष्ठा iwl_mvm_scan_channel_segment scan_channel_segments[] = अणु
	अणु
		.start_idx = 0,
		.end_idx = 13,
		.first_channel_id = 1,
		.last_channel_id = 14,
		.channel_spacing_shअगरt = 0,
		.band = PHY_BAND_24
	पूर्ण,
	अणु
		.start_idx = 14,
		.end_idx = 41,
		.first_channel_id = 36,
		.last_channel_id = 144,
		.channel_spacing_shअगरt = 2,
		.band = PHY_BAND_5
	पूर्ण,
	अणु
		.start_idx = 42,
		.end_idx = 50,
		.first_channel_id = 149,
		.last_channel_id = 181,
		.channel_spacing_shअगरt = 2,
		.band = PHY_BAND_5
	पूर्ण,
	अणु
		.start_idx = 51,
		.end_idx = 111,
		.first_channel_id = 1,
		.last_channel_id = 241,
		.channel_spacing_shअगरt = 2,
		.band = PHY_BAND_6
	पूर्ण,
पूर्ण;

अटल पूर्णांक iwl_mvm_scan_ch_and_band_to_idx(u8 channel_id, u8 band)
अणु
	पूर्णांक i, index;

	अगर (!channel_id)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(scan_channel_segments); i++) अणु
		स्थिर काष्ठा iwl_mvm_scan_channel_segment *ch_segment =
			&scan_channel_segments[i];
		u32 ch_offset;

		अगर (ch_segment->band != band ||
		    ch_segment->first_channel_id > channel_id ||
		    ch_segment->last_channel_id < channel_id)
			जारी;

		ch_offset = (channel_id - ch_segment->first_channel_id) >>
			ch_segment->channel_spacing_shअगरt;

		index = scan_channel_segments[i].start_idx + ch_offset;
		अगर (index < IWL_SCAN_NUM_CHANNELS)
			वापस index;

		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर u8 p2p_go_मित्रly_chs[] = अणु
	36, 40, 44, 48, 149, 153, 157, 161, 165,
पूर्ण;

अटल स्थिर u8 social_chs[] = अणु
	1, 6, 11
पूर्ण;

अटल व्योम iwl_mvm_scan_ch_add_n_aps_override(क्रमागत nl80211_अगरtype vअगर_type,
					       u8 ch_id, u8 band, u8 *ch_biपंचांगap,
					       माप_प्रकार biपंचांगap_n_entries)
अणु
	पूर्णांक i;

	अगर (vअगर_type != NL80211_IFTYPE_P2P_DEVICE)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(p2p_go_मित्रly_chs); i++) अणु
		अगर (p2p_go_मित्रly_chs[i] == ch_id) अणु
			पूर्णांक ch_idx, biपंचांगap_idx;

			ch_idx = iwl_mvm_scan_ch_and_band_to_idx(ch_id, band);
			अगर (ch_idx < 0)
				वापस;

			biपंचांगap_idx = ch_idx / 8;
			अगर (biपंचांगap_idx >= biपंचांगap_n_entries)
				वापस;

			ch_idx = ch_idx % 8;
			ch_biपंचांगap[biपंचांगap_idx] |= BIT(ch_idx);

			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 iwl_mvm_scan_ch_n_aps_flag(क्रमागत nl80211_अगरtype vअगर_type, u8 ch_id)
अणु
	पूर्णांक i;
	u32 flags = 0;

	अगर (vअगर_type != NL80211_IFTYPE_P2P_DEVICE)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(p2p_go_मित्रly_chs); i++) अणु
		अगर (p2p_go_मित्रly_chs[i] == ch_id) अणु
			flags |= IWL_SCAN_ADWELL_N_APS_GO_FRIENDLY_BIT;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (flags)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(social_chs); i++) अणु
		अगर (social_chs[i] == ch_id) अणु
			flags |= IWL_SCAN_ADWELL_N_APS_SOCIAL_CHS_BIT;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस flags;
पूर्ण

अटल व्योम
iwl_mvm_umac_scan_cfg_channels(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_channel **channels,
			       पूर्णांक n_channels, u32 flags,
			       काष्ठा iwl_scan_channel_cfg_umac *channel_cfg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_channels; i++) अणु
		channel_cfg[i].flags = cpu_to_le32(flags);
		channel_cfg[i].v1.channel_num = channels[i]->hw_value;
		अगर (iwl_mvm_is_scan_ext_chan_supported(mvm)) अणु
			क्रमागत nl80211_band band = channels[i]->band;

			channel_cfg[i].v2.band =
				iwl_mvm_phy_band_from_nl80211(band);
			channel_cfg[i].v2.iter_count = 1;
			channel_cfg[i].v2.iter_पूर्णांकerval = 0;
		पूर्ण अन्यथा अणु
			channel_cfg[i].v1.iter_count = 1;
			channel_cfg[i].v1.iter_पूर्णांकerval = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
iwl_mvm_umac_scan_cfg_channels_v4(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_channel **channels,
				  काष्ठा iwl_scan_channel_params_v4 *cp,
				  पूर्णांक n_channels, u32 flags,
				  क्रमागत nl80211_अगरtype vअगर_type)
अणु
	u8 *biपंचांगap = cp->adwell_ch_override_biपंचांगap;
	माप_प्रकार biपंचांगap_n_entries = ARRAY_SIZE(cp->adwell_ch_override_biपंचांगap);
	पूर्णांक i;

	क्रम (i = 0; i < n_channels; i++) अणु
		क्रमागत nl80211_band band = channels[i]->band;
		काष्ठा iwl_scan_channel_cfg_umac *cfg =
			&cp->channel_config[i];

		cfg->flags = cpu_to_le32(flags);
		cfg->v2.channel_num = channels[i]->hw_value;
		cfg->v2.band = iwl_mvm_phy_band_from_nl80211(band);
		cfg->v2.iter_count = 1;
		cfg->v2.iter_पूर्णांकerval = 0;

		iwl_mvm_scan_ch_add_n_aps_override(vअगर_type,
						   cfg->v2.channel_num,
						   cfg->v2.band, biपंचांगap,
						   biपंचांगap_n_entries);
	पूर्ण
पूर्ण

अटल व्योम
iwl_mvm_umac_scan_cfg_channels_v6(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_channel **channels,
				  काष्ठा iwl_scan_channel_params_v6 *cp,
				  पूर्णांक n_channels, u32 flags,
				  क्रमागत nl80211_अगरtype vअगर_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n_channels; i++) अणु
		क्रमागत nl80211_band band = channels[i]->band;
		काष्ठा iwl_scan_channel_cfg_umac *cfg = &cp->channel_config[i];
		u32 n_aps_flag =
			iwl_mvm_scan_ch_n_aps_flag(vअगर_type,
						   cfg->v2.channel_num);

		cfg->flags = cpu_to_le32(flags | n_aps_flag);
		cfg->v2.channel_num = channels[i]->hw_value;
		cfg->v2.band = iwl_mvm_phy_band_from_nl80211(band);
		अगर (cfg80211_channel_is_psc(channels[i]))
			cfg->flags = 0;
		cfg->v2.iter_count = 1;
		cfg->v2.iter_पूर्णांकerval = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
iwl_mvm_umac_scan_fill_6g_chan_list(काष्ठा iwl_mvm_scan_params *params,
				    __le32 *cmd_लघु_ssid, u8 *cmd_bssid,
				    u8 *scan_ssid_num, u8 *bssid_num)
अणु
	पूर्णांक j, idex_s = 0, idex_b = 0;
	काष्ठा cfg80211_scan_6ghz_params *scan_6ghz_params =
		params->scan_6ghz_params;

	अगर (!params->n_6ghz_params) अणु
		क्रम (j = 0; j < params->n_ssids; j++) अणु
			cmd_लघु_ssid[idex_s++] =
				cpu_to_le32(~crc32_le(~0, params->ssids[j].ssid,
						      params->ssids[j].ssid_len));
			(*scan_ssid_num)++;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * Populate the arrays of the लघु SSIDs and the BSSIDs using the 6GHz
	 * collocated parameters. This might not be optimal, as this processing
	 * करोes not (yet) correspond to the actual channels, so it is possible
	 * that some entries would be left out.
	 *
	 * TODO: improve this logic.
	 */
	क्रम (j = 0; j < params->n_6ghz_params; j++) अणु
		पूर्णांक k;

		/* First, try to place the लघु SSID */
		अगर (scan_6ghz_params[j].लघु_ssid_valid) अणु
			क्रम (k = 0; k < idex_s; k++) अणु
				अगर (cmd_लघु_ssid[k] ==
				    cpu_to_le32(scan_6ghz_params[j].लघु_ssid))
					अवरोध;
			पूर्ण

			अगर (k == idex_s && idex_s < SCAN_SHORT_SSID_MAX_SIZE) अणु
				cmd_लघु_ssid[idex_s++] =
					cpu_to_le32(scan_6ghz_params[j].लघु_ssid);
				(*scan_ssid_num)++;
			पूर्ण
		पूर्ण

		/* try to place BSSID क्रम the same entry */
		क्रम (k = 0; k < idex_b; k++) अणु
			अगर (!स_भेद(&cmd_bssid[ETH_ALEN * k],
				    scan_6ghz_params[j].bssid, ETH_ALEN))
				अवरोध;
		पूर्ण

		अगर (k == idex_b && idex_b < SCAN_BSSID_MAX_SIZE) अणु
			स_नकल(&cmd_bssid[ETH_ALEN * idex_b++],
			       scan_6ghz_params[j].bssid, ETH_ALEN);
			(*bssid_num)++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* TODO: this function can be merged with iwl_mvm_scan_umac_fill_ch_p_v6 */
अटल व्योम
iwl_mvm_umac_scan_cfg_channels_v6_6g(काष्ठा iwl_mvm_scan_params *params,
				     u32 n_channels, __le32 *cmd_लघु_ssid,
				     u8 *cmd_bssid, u8 scan_ssid_num,
				     u8 bssid_num,
				     काष्ठा iwl_scan_channel_params_v6 *cp,
				     क्रमागत nl80211_अगरtype vअगर_type)
अणु
	काष्ठा iwl_scan_channel_cfg_umac *channel_cfg = cp->channel_config;
	पूर्णांक i;
	काष्ठा cfg80211_scan_6ghz_params *scan_6ghz_params =
		params->scan_6ghz_params;

	क्रम (i = 0; i < params->n_channels; i++) अणु
		काष्ठा iwl_scan_channel_cfg_umac *cfg =
			&cp->channel_config[i];

		u32 s_ssid_biपंचांगap = 0, bssid_biपंचांगap = 0, flags = 0;
		u8 j, k, s_max = 0, b_max = 0, n_used_bssid_entries;
		bool क्रमce_passive, found = false,
		     unsolicited_probe_on_chan = false, psc_no_listen = false;

		cfg->v1.channel_num = params->channels[i]->hw_value;
		cfg->v2.band = 2;
		cfg->v2.iter_count = 1;
		cfg->v2.iter_पूर्णांकerval = 0;

		/*
		 * The optimize the scan समय, i.e., reduce the scan dwell समय
		 * on each channel, the below logic tries to set 3 direct BSSID
		 * probe requests क्रम each broadcast probe request with a लघु
		 * SSID.
		 * TODO: improve this logic
		 */
		n_used_bssid_entries = 3;
		क्रम (j = 0; j < params->n_6ghz_params; j++) अणु
			अगर (!(scan_6ghz_params[j].channel_idx == i))
				जारी;

			found = false;
			unsolicited_probe_on_chan |=
				scan_6ghz_params[j].unsolicited_probe;
			psc_no_listen |= scan_6ghz_params[j].psc_no_listen;

			क्रम (k = 0; k < scan_ssid_num; k++) अणु
				अगर (!scan_6ghz_params[j].unsolicited_probe &&
				    le32_to_cpu(cmd_लघु_ssid[k]) ==
				    scan_6ghz_params[j].लघु_ssid) अणु
					/* Relevant लघु SSID bit set */
					अगर (s_ssid_biपंचांगap & BIT(k)) अणु
						found = true;
						अवरोध;
					पूर्ण

					/*
					 * Use लघु SSID only to create a new
					 * iteration during channel dwell.
					 */
					अगर (n_used_bssid_entries >= 3) अणु
						s_ssid_biपंचांगap |= BIT(k);
						s_max++;
						n_used_bssid_entries -= 3;
						found = true;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (found)
				जारी;

			क्रम (k = 0; k < bssid_num; k++) अणु
				अगर (!स_भेद(&cmd_bssid[ETH_ALEN * k],
					    scan_6ghz_params[j].bssid,
					    ETH_ALEN)) अणु
					अगर (!(bssid_biपंचांगap & BIT(k))) अणु
						bssid_biपंचांगap |= BIT(k);
						b_max++;
						n_used_bssid_entries++;
					पूर्ण
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		flags = bssid_biपंचांगap | (s_ssid_biपंचांगap << 16);

		अगर (cfg80211_channel_is_psc(params->channels[i]) &&
		    psc_no_listen)
			flags |= IWL_UHB_CHAN_CFG_FLAG_PSC_CHAN_NO_LISTEN;

		अगर (unsolicited_probe_on_chan)
			flags |= IWL_UHB_CHAN_CFG_FLAG_UNSOLICITED_PROBE_RES;

		/*
		 * In the following हालs apply passive scan:
		 * 1. Non fragmented scan:
		 *	- PSC channel with NO_LISTEN_FLAG on should be treated
		 *	  like non PSC channel
		 *	- Non PSC channel with more than 3 लघु SSIDs or more
		 *	  than 9 BSSIDs.
		 *	- Non PSC Channel with unsolicited probe response and
		 *	  more than 2 लघु SSIDs or more than 6 BSSIDs.
		 *	- PSC channel with more than 2 लघु SSIDs or more than
		 *	  6 BSSIDs.
		 * 3. Fragmented scan:
		 *	- PSC channel with more than 1 SSID or 3 BSSIDs.
		 *	- Non PSC channel with more than 2 SSIDs or 6 BSSIDs.
		 *	- Non PSC channel with unsolicited probe response and
		 *	  more than 1 SSID or more than 3 BSSIDs.
		 */
		अगर (!iwl_mvm_is_scan_fragmented(params->type)) अणु
			अगर (!cfg80211_channel_is_psc(params->channels[i]) ||
			    flags & IWL_UHB_CHAN_CFG_FLAG_PSC_CHAN_NO_LISTEN) अणु
				क्रमce_passive = (s_max > 3 || b_max > 9);
				क्रमce_passive |= (unsolicited_probe_on_chan &&
						  (s_max > 2 || b_max > 6));
			पूर्ण अन्यथा अणु
				क्रमce_passive = (s_max > 2 || b_max > 6);
			पूर्ण
		पूर्ण अन्यथा अगर (cfg80211_channel_is_psc(params->channels[i])) अणु
			क्रमce_passive = (s_max > 1 || b_max > 3);
		पूर्ण अन्यथा अणु
			क्रमce_passive = (s_max > 2 || b_max > 6);
			क्रमce_passive |= (unsolicited_probe_on_chan &&
					  (s_max > 1 || b_max > 3));
		पूर्ण
		अगर (क्रमce_passive ||
		    (!flags && !cfg80211_channel_is_psc(params->channels[i])))
			flags |= IWL_UHB_CHAN_CFG_FLAG_FORCE_PASSIVE;

		channel_cfg[i].flags |= cpu_to_le32(flags);
	पूर्ण
पूर्ण

अटल u8 iwl_mvm_scan_umac_chan_flags_v2(काष्ठा iwl_mvm *mvm,
					  काष्ठा iwl_mvm_scan_params *params,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	u8 flags = 0;

	flags |= IWL_SCAN_CHANNEL_FLAG_ENABLE_CHAN_ORDER;

	अगर (iwl_mvm_scan_use_ebs(mvm, vअगर))
		flags |= IWL_SCAN_CHANNEL_FLAG_EBS |
			IWL_SCAN_CHANNEL_FLAG_EBS_ACCURATE |
			IWL_SCAN_CHANNEL_FLAG_CACHE_ADD;

	/* set fragmented ebs क्रम fragmented scan on HB channels */
	अगर (iwl_mvm_is_scan_fragmented(params->hb_type))
		flags |= IWL_SCAN_CHANNEL_FLAG_EBS_FRAG;

	वापस flags;
पूर्ण

अटल व्योम iwl_mvm_scan_6ghz_passive_scan(काष्ठा iwl_mvm *mvm,
					   काष्ठा iwl_mvm_scan_params *params,
					   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_supported_band *sband =
		&mvm->nvm_data->bands[NL80211_BAND_6GHZ];
	u32 n_disabled, i;

	params->enable_6ghz_passive = false;

	अगर (params->scan_6ghz)
		वापस;

	अगर (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_PASSIVE_6GHZ_SCAN)) अणु
		IWL_DEBUG_SCAN(mvm,
			       "6GHz passive scan: Not supported by FW\n");
		वापस;
	पूर्ण

	/* 6GHz passive scan allowed only on station पूर्णांकerface  */
	अगर (vअगर->type != NL80211_IFTYPE_STATION) अणु
		IWL_DEBUG_SCAN(mvm,
			       "6GHz passive scan: not station interface\n");
		वापस;
	पूर्ण

	/*
	 * 6GHz passive scan is allowed जबतक associated in a defined समय
	 * पूर्णांकerval following HW reset or resume flow
	 */
	अगर (vअगर->bss_conf.assoc &&
	    (समय_beक्रमe(mvm->last_reset_or_resume_समय_jअगरfies +
			 (IWL_MVM_6GHZ_PASSIVE_SCAN_ASSOC_TIMEOUT * HZ),
			 jअगरfies))) अणु
		IWL_DEBUG_SCAN(mvm, "6GHz passive scan: associated\n");
		वापस;
	पूर्ण

	/* No need क्रम 6GHz passive scan अगर not enough समय elapsed */
	अगर (समय_after(mvm->last_6ghz_passive_scan_jअगरfies +
		       (IWL_MVM_6GHZ_PASSIVE_SCAN_TIMEOUT * HZ), jअगरfies)) अणु
		IWL_DEBUG_SCAN(mvm,
			       "6GHz passive scan: timeout did not expire\n");
		वापस;
	पूर्ण

	/* not enough channels in the regular scan request */
	अगर (params->n_channels < IWL_MVM_6GHZ_PASSIVE_SCAN_MIN_CHANS) अणु
		IWL_DEBUG_SCAN(mvm,
			       "6GHz passive scan: not enough channels\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < params->n_ssids; i++) अणु
		अगर (!params->ssids[i].ssid_len)
			अवरोध;
	पूर्ण

	/* not a wildcard scan, so cannot enable passive 6GHz scan */
	अगर (i == params->n_ssids) अणु
		IWL_DEBUG_SCAN(mvm,
			       "6GHz passive scan: no wildcard SSID\n");
		वापस;
	पूर्ण

	अगर (!sband || !sband->n_channels) अणु
		IWL_DEBUG_SCAN(mvm,
			       "6GHz passive scan: no 6GHz channels\n");
		वापस;
	पूर्ण

	क्रम (i = 0, n_disabled = 0; i < sband->n_channels; i++) अणु
		अगर (sband->channels[i].flags & (IEEE80211_CHAN_DISABLED))
			n_disabled++;
	पूर्ण

	/*
	 * Not all the 6GHz channels are disabled, so no need क्रम 6GHz passive
	 * scan
	 */
	अगर (n_disabled != sband->n_channels) अणु
		IWL_DEBUG_SCAN(mvm,
			       "6GHz passive scan: 6GHz channels enabled\n");
		वापस;
	पूर्ण

	/* all conditions to enable 6ghz passive scan are satisfied */
	IWL_DEBUG_SCAN(mvm, "6GHz passive scan: can be enabled\n");
	params->enable_6ghz_passive = true;
पूर्ण

अटल u16 iwl_mvm_scan_umac_flags_v2(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_mvm_scan_params *params,
				      काष्ठा ieee80211_vअगर *vअगर,
				      पूर्णांक type)
अणु
	u16 flags = 0;

	अगर (params->n_ssids == 0)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_FORCE_PASSIVE;

	अगर (iwl_mvm_is_scan_fragmented(params->type))
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_FRAGMENTED_LMAC1;

	अगर (iwl_mvm_is_scan_fragmented(params->hb_type))
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_FRAGMENTED_LMAC2;

	अगर (params->pass_all)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_PASS_ALL;
	अन्यथा
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_MATCH;

	अगर (!iwl_mvm_is_regular_scan(params))
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_PERIODIC;

	अगर (params->iter_notअगर ||
	    mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_ENABLED)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_NTFY_ITER_COMPLETE;

	अगर (IWL_MVM_ADWELL_ENABLE)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_ADAPTIVE_DWELL;

	अगर (type == IWL_MVM_SCAN_SCHED || type == IWL_MVM_SCAN_NETDETECT)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_PREEMPTIVE;

	अगर ((type == IWL_MVM_SCAN_SCHED || type == IWL_MVM_SCAN_NETDETECT) &&
	    params->flags & NL80211_SCAN_FLAG_COLOCATED_6GHZ)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_TRIGGER_UHB_SCAN;

	अगर (params->enable_6ghz_passive)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_V2_6GHZ_PASSIVE_SCAN;

	वापस flags;
पूर्ण

अटल u16 iwl_mvm_scan_umac_flags(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_mvm_scan_params *params,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	u16 flags = 0;

	अगर (params->n_ssids == 0)
		flags = IWL_UMAC_SCAN_GEN_FLAGS_PASSIVE;

	अगर (params->n_ssids == 1 && params->ssids[0].ssid_len != 0)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_PRE_CONNECT;

	अगर (iwl_mvm_is_scan_fragmented(params->type))
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_FRAGMENTED;

	अगर (iwl_mvm_is_cdb_supported(mvm) &&
	    iwl_mvm_is_scan_fragmented(params->hb_type))
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_LMAC2_FRAGMENTED;

	अगर (iwl_mvm_rrm_scan_needed(mvm) &&
	    fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_WFA_TPC_REP_IE_SUPPORT))
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_RRM_ENABLED;

	अगर (params->pass_all)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_PASS_ALL;
	अन्यथा
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_MATCH;

	अगर (!iwl_mvm_is_regular_scan(params))
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_PERIODIC;

	अगर (params->iter_notअगर)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_ITER_COMPLETE;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (mvm->scan_iter_notअगर_enabled)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_ITER_COMPLETE;
#पूर्ण_अगर

	अगर (mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_ENABLED)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_ITER_COMPLETE;

	अगर (iwl_mvm_is_adaptive_dwell_supported(mvm) && IWL_MVM_ADWELL_ENABLE)
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_ADAPTIVE_DWELL;

	/*
	 * Extended dwell is relevant only क्रम low band to start with, as it is
	 * being used क्रम social channles only (1, 6, 11), so we can check
	 * only scan type on low band also क्रम CDB.
	 */
	अगर (iwl_mvm_is_regular_scan(params) &&
	    vअगर->type != NL80211_IFTYPE_P2P_DEVICE &&
	    !iwl_mvm_is_scan_fragmented(params->type) &&
	    !iwl_mvm_is_adaptive_dwell_supported(mvm) &&
	    !iwl_mvm_is_oce_supported(mvm))
		flags |= IWL_UMAC_SCAN_GEN_FLAGS_EXTENDED_DWELL;

	अगर (iwl_mvm_is_oce_supported(mvm)) अणु
		अगर ((params->flags &
		     NL80211_SCAN_FLAG_OCE_PROBE_REQ_HIGH_TX_RATE))
			flags |= IWL_UMAC_SCAN_GEN_FLAGS_PROB_REQ_HIGH_TX_RATE;
		/* Since IWL_UMAC_SCAN_GEN_FLAGS_EXTENDED_DWELL and
		 * NL80211_SCAN_FLAG_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION shares
		 * the same bit, we need to make sure that we use this bit here
		 * only when IWL_UMAC_SCAN_GEN_FLAGS_EXTENDED_DWELL cannot be
		 * used. */
		अगर ((params->flags &
		     NL80211_SCAN_FLAG_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION) &&
		     !WARN_ON_ONCE(!iwl_mvm_is_adaptive_dwell_supported(mvm)))
			flags |= IWL_UMAC_SCAN_GEN_FLAGS_PROB_REQ_DEFER_SUPP;
		अगर ((params->flags & NL80211_SCAN_FLAG_FILS_MAX_CHANNEL_TIME))
			flags |= IWL_UMAC_SCAN_GEN_FLAGS_MAX_CHNL_TIME;
	पूर्ण

	वापस flags;
पूर्ण

अटल पूर्णांक
iwl_mvm_fill_scan_sched_params(काष्ठा iwl_mvm_scan_params *params,
			       काष्ठा iwl_scan_umac_schedule *schedule,
			       __le16 *delay)
अणु
	पूर्णांक i;
	अगर (WARN_ON(!params->n_scan_plans ||
		    params->n_scan_plans > IWL_MAX_SCHED_SCAN_PLANS))
		वापस -EINVAL;

	क्रम (i = 0; i < params->n_scan_plans; i++) अणु
		काष्ठा cfg80211_sched_scan_plan *scan_plan =
			&params->scan_plans[i];

		schedule[i].iter_count = scan_plan->iterations;
		schedule[i].पूर्णांकerval =
			cpu_to_le16(scan_plan->पूर्णांकerval);
	पूर्ण

	/*
	 * If the number of iterations of the last scan plan is set to
	 * zero, it should run infinitely. However, this is not always the हाल.
	 * For example, when regular scan is requested the driver sets one scan
	 * plan with one iteration.
	 */
	अगर (!schedule[params->n_scan_plans - 1].iter_count)
		schedule[params->n_scan_plans - 1].iter_count = 0xff;

	*delay = cpu_to_le16(params->delay);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_scan_umac(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा iwl_mvm_scan_params *params,
			     पूर्णांक type, पूर्णांक uid)
अणु
	काष्ठा iwl_scan_req_umac *cmd = mvm->scan_cmd;
	काष्ठा iwl_scan_umac_chan_param *chan_param;
	व्योम *cmd_data = iwl_mvm_get_scan_req_umac_data(mvm);
	व्योम *sec_part = cmd_data + माप(काष्ठा iwl_scan_channel_cfg_umac) *
		mvm->fw->ucode_capa.n_scan_channels;
	काष्ठा iwl_scan_req_umac_tail_v2 *tail_v2 =
		(काष्ठा iwl_scan_req_umac_tail_v2 *)sec_part;
	काष्ठा iwl_scan_req_umac_tail_v1 *tail_v1;
	काष्ठा iwl_ssid_ie *direct_scan;
	पूर्णांक ret = 0;
	u32 ssid_biपंचांगap = 0;
	u8 channel_flags = 0;
	u16 gen_flags;
	काष्ठा iwl_mvm_vअगर *scan_vअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	chan_param = iwl_mvm_get_scan_req_umac_channel(mvm);

	iwl_mvm_scan_umac_dwell(mvm, cmd, params);

	mvm->scan_uid_status[uid] = type;

	cmd->uid = cpu_to_le32(uid);
	gen_flags = iwl_mvm_scan_umac_flags(mvm, params, vअगर);
	cmd->general_flags = cpu_to_le16(gen_flags);
	अगर (iwl_mvm_is_adaptive_dwell_v2_supported(mvm)) अणु
		अगर (gen_flags & IWL_UMAC_SCAN_GEN_FLAGS_FRAGMENTED)
			cmd->v8.num_of_fragments[SCAN_LB_LMAC_IDX] =
							IWL_SCAN_NUM_OF_FRAGS;
		अगर (gen_flags & IWL_UMAC_SCAN_GEN_FLAGS_LMAC2_FRAGMENTED)
			cmd->v8.num_of_fragments[SCAN_HB_LMAC_IDX] =
							IWL_SCAN_NUM_OF_FRAGS;

		cmd->v8.general_flags2 =
			IWL_UMAC_SCAN_GEN_FLAGS2_ALLOW_CHNL_REORDER;
	पूर्ण

	cmd->scan_start_mac_id = scan_vअगर->id;

	अगर (type == IWL_MVM_SCAN_SCHED || type == IWL_MVM_SCAN_NETDETECT)
		cmd->flags = cpu_to_le32(IWL_UMAC_SCAN_FLAG_PREEMPTIVE);

	अगर (iwl_mvm_scan_use_ebs(mvm, vअगर)) अणु
		channel_flags = IWL_SCAN_CHANNEL_FLAG_EBS |
				IWL_SCAN_CHANNEL_FLAG_EBS_ACCURATE |
				IWL_SCAN_CHANNEL_FLAG_CACHE_ADD;

		/* set fragmented ebs क्रम fragmented scan on HB channels */
		अगर (iwl_mvm_is_frag_ebs_supported(mvm)) अणु
			अगर (gen_flags &
			    IWL_UMAC_SCAN_GEN_FLAGS_LMAC2_FRAGMENTED ||
			    (!iwl_mvm_is_cdb_supported(mvm) &&
			     gen_flags & IWL_UMAC_SCAN_GEN_FLAGS_FRAGMENTED))
				channel_flags |= IWL_SCAN_CHANNEL_FLAG_EBS_FRAG;
		पूर्ण
	पूर्ण

	chan_param->flags = channel_flags;
	chan_param->count = params->n_channels;

	ret = iwl_mvm_fill_scan_sched_params(params, tail_v2->schedule,
					     &tail_v2->delay);
	अगर (ret) अणु
		mvm->scan_uid_status[uid] = 0;
		वापस ret;
	पूर्ण

	अगर (iwl_mvm_is_scan_ext_chan_supported(mvm)) अणु
		tail_v2->preq = params->preq;
		direct_scan = tail_v2->direct_scan;
	पूर्ण अन्यथा अणु
		tail_v1 = (काष्ठा iwl_scan_req_umac_tail_v1 *)sec_part;
		iwl_mvm_scan_set_legacy_probe_req(&tail_v1->preq,
						  &params->preq);
		direct_scan = tail_v1->direct_scan;
	पूर्ण
	iwl_scan_build_ssids(params, direct_scan, &ssid_biपंचांगap);
	iwl_mvm_umac_scan_cfg_channels(mvm, params->channels,
				       params->n_channels, ssid_biपंचांगap,
				       cmd_data);
	वापस 0;
पूर्ण

अटल व्योम
iwl_mvm_scan_umac_fill_general_p_v10(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_mvm_scan_params *params,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा iwl_scan_general_params_v10 *gp,
				     u16 gen_flags)
अणु
	काष्ठा iwl_mvm_vअगर *scan_vअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	iwl_mvm_scan_umac_dwell_v10(mvm, gp, params);

	gp->flags = cpu_to_le16(gen_flags);

	अगर (gen_flags & IWL_UMAC_SCAN_GEN_FLAGS_V2_FRAGMENTED_LMAC1)
		gp->num_of_fragments[SCAN_LB_LMAC_IDX] = IWL_SCAN_NUM_OF_FRAGS;
	अगर (gen_flags & IWL_UMAC_SCAN_GEN_FLAGS_V2_FRAGMENTED_LMAC2)
		gp->num_of_fragments[SCAN_HB_LMAC_IDX] = IWL_SCAN_NUM_OF_FRAGS;

	gp->scan_start_mac_id = scan_vअगर->id;
पूर्ण

अटल व्योम
iwl_mvm_scan_umac_fill_probe_p_v3(काष्ठा iwl_mvm_scan_params *params,
				  काष्ठा iwl_scan_probe_params_v3 *pp)
अणु
	pp->preq = params->preq;
	pp->ssid_num = params->n_ssids;
	iwl_scan_build_ssids(params, pp->direct_scan, शून्य);
पूर्ण

अटल व्योम
iwl_mvm_scan_umac_fill_probe_p_v4(काष्ठा iwl_mvm_scan_params *params,
				  काष्ठा iwl_scan_probe_params_v4 *pp,
				  u32 *biपंचांगap_ssid)
अणु
	pp->preq = params->preq;
	iwl_scan_build_ssids(params, pp->direct_scan, biपंचांगap_ssid);
पूर्ण

अटल व्योम
iwl_mvm_scan_umac_fill_ch_p_v4(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_mvm_scan_params *params,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा iwl_scan_channel_params_v4 *cp,
			       u32 channel_cfg_flags)
अणु
	cp->flags = iwl_mvm_scan_umac_chan_flags_v2(mvm, params, vअगर);
	cp->count = params->n_channels;
	cp->num_of_aps_override = IWL_SCAN_ADWELL_N_APS_GO_FRIENDLY;

	iwl_mvm_umac_scan_cfg_channels_v4(mvm, params->channels, cp,
					  params->n_channels,
					  channel_cfg_flags,
					  vअगर->type);
पूर्ण

अटल व्योम
iwl_mvm_scan_umac_fill_ch_p_v6(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_mvm_scan_params *params,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा iwl_scan_channel_params_v6 *cp,
			       u32 channel_cfg_flags)
अणु
	cp->flags = iwl_mvm_scan_umac_chan_flags_v2(mvm, params, vअगर);
	cp->count = params->n_channels;
	cp->n_aps_override[0] = IWL_SCAN_ADWELL_N_APS_GO_FRIENDLY;
	cp->n_aps_override[1] = IWL_SCAN_ADWELL_N_APS_SOCIAL_CHS;

	iwl_mvm_umac_scan_cfg_channels_v6(mvm, params->channels, cp,
					  params->n_channels,
					  channel_cfg_flags,
					  vअगर->type);

	अगर (params->enable_6ghz_passive) अणु
		काष्ठा ieee80211_supported_band *sband =
			&mvm->nvm_data->bands[NL80211_BAND_6GHZ];
		u32 i;

		क्रम (i = 0; i < sband->n_channels; i++) अणु
			काष्ठा ieee80211_channel *channel =
				&sband->channels[i];

			काष्ठा iwl_scan_channel_cfg_umac *cfg =
				&cp->channel_config[cp->count];

			अगर (!cfg80211_channel_is_psc(channel))
				जारी;

			cfg->flags = 0;
			cfg->v2.channel_num = channel->hw_value;
			cfg->v2.band = PHY_BAND_6;
			cfg->v2.iter_count = 1;
			cfg->v2.iter_पूर्णांकerval = 0;
			cp->count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_mvm_scan_umac_v12(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा iwl_mvm_scan_params *params, पूर्णांक type,
				 पूर्णांक uid)
अणु
	काष्ठा iwl_scan_req_umac_v12 *cmd = mvm->scan_cmd;
	काष्ठा iwl_scan_req_params_v12 *scan_p = &cmd->scan_params;
	पूर्णांक ret;
	u16 gen_flags;

	mvm->scan_uid_status[uid] = type;

	cmd->ooc_priority = cpu_to_le32(iwl_mvm_scan_umac_ooc_priority(params));
	cmd->uid = cpu_to_le32(uid);

	gen_flags = iwl_mvm_scan_umac_flags_v2(mvm, params, vअगर, type);
	iwl_mvm_scan_umac_fill_general_p_v10(mvm, params, vअगर,
					     &scan_p->general_params,
					     gen_flags);

	 ret = iwl_mvm_fill_scan_sched_params(params,
					      scan_p->periodic_params.schedule,
					      &scan_p->periodic_params.delay);
	अगर (ret)
		वापस ret;

	iwl_mvm_scan_umac_fill_probe_p_v3(params, &scan_p->probe_params);
	iwl_mvm_scan_umac_fill_ch_p_v4(mvm, params, vअगर,
				       &scan_p->channel_params, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_scan_umac_v14(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा iwl_mvm_scan_params *params, पूर्णांक type,
				 पूर्णांक uid)
अणु
	काष्ठा iwl_scan_req_umac_v14 *cmd = mvm->scan_cmd;
	काष्ठा iwl_scan_req_params_v14 *scan_p = &cmd->scan_params;
	काष्ठा iwl_scan_channel_params_v6 *cp = &scan_p->channel_params;
	काष्ठा iwl_scan_probe_params_v4 *pb = &scan_p->probe_params;
	पूर्णांक ret;
	u16 gen_flags;
	u32 biपंचांगap_ssid = 0;

	mvm->scan_uid_status[uid] = type;

	cmd->ooc_priority = cpu_to_le32(iwl_mvm_scan_umac_ooc_priority(params));
	cmd->uid = cpu_to_le32(uid);

	gen_flags = iwl_mvm_scan_umac_flags_v2(mvm, params, vअगर, type);
	iwl_mvm_scan_umac_fill_general_p_v10(mvm, params, vअगर,
					     &scan_p->general_params,
					     gen_flags);

	 ret = iwl_mvm_fill_scan_sched_params(params,
					      scan_p->periodic_params.schedule,
					      &scan_p->periodic_params.delay);
	अगर (ret)
		वापस ret;

	iwl_mvm_scan_umac_fill_probe_p_v4(params, &scan_p->probe_params,
					  &biपंचांगap_ssid);
	अगर (!params->scan_6ghz) अणु
		iwl_mvm_scan_umac_fill_ch_p_v6(mvm, params, vअगर,
					       &scan_p->channel_params, biपंचांगap_ssid);

		वापस 0;
	पूर्ण
	cp->flags = iwl_mvm_scan_umac_chan_flags_v2(mvm, params, vअगर);
	cp->n_aps_override[0] = IWL_SCAN_ADWELL_N_APS_GO_FRIENDLY;
	cp->n_aps_override[1] = IWL_SCAN_ADWELL_N_APS_SOCIAL_CHS;

	ret = iwl_mvm_umac_scan_fill_6g_chan_list(params, pb->लघु_ssid,
						  pb->bssid_array[0],
						  &pb->लघु_ssid_num,
						  &pb->bssid_num);
	अगर (ret)
		वापस ret;

	iwl_mvm_umac_scan_cfg_channels_v6_6g(params,
					     params->n_channels,
					     pb->लघु_ssid,
					     pb->bssid_array[0],
					     pb->लघु_ssid_num,
					     pb->bssid_num, cp,
					     vअगर->type);
	cp->count = params->n_channels;
	अगर (!params->n_ssids ||
	    (params->n_ssids == 1 && !params->ssids[0].ssid_len))
		cp->flags |= IWL_SCAN_CHANNEL_FLAG_6G_PSC_NO_FILTER;

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_num_scans(काष्ठा iwl_mvm *mvm)
अणु
	वापस hweight32(mvm->scan_status & IWL_MVM_SCAN_MASK);
पूर्ण

अटल पूर्णांक iwl_mvm_check_running_scans(काष्ठा iwl_mvm *mvm, पूर्णांक type)
अणु
	bool unअगरied_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);

	/* This looks a bit arbitrary, but the idea is that अगर we run
	 * out of possible simultaneous scans and the userspace is
	 * trying to run a scan type that is alपढ़ोy running, we
	 * वापस -EBUSY.  But अगर the userspace wants to start a
	 * dअगरferent type of scan, we stop the opposite type to make
	 * space क्रम the new request.  The reason is backwards
	 * compatibility with old wpa_supplicant that wouldn't stop a
	 * scheduled scan beक्रमe starting a normal scan.
	 */

	/* FW supports only a single periodic scan */
	अगर ((type == IWL_MVM_SCAN_SCHED || type == IWL_MVM_SCAN_NETDETECT) &&
	    mvm->scan_status & (IWL_MVM_SCAN_SCHED | IWL_MVM_SCAN_NETDETECT))
		वापस -EBUSY;

	अगर (iwl_mvm_num_scans(mvm) < mvm->max_scans)
		वापस 0;

	/* Use a चयन, even though this is a biपंचांगask, so that more
	 * than one bits set will fall in शेष and we will warn.
	 */
	चयन (type) अणु
	हाल IWL_MVM_SCAN_REGULAR:
		अगर (mvm->scan_status & IWL_MVM_SCAN_REGULAR_MASK)
			वापस -EBUSY;
		वापस iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_SCHED, true);
	हाल IWL_MVM_SCAN_SCHED:
		अगर (mvm->scan_status & IWL_MVM_SCAN_SCHED_MASK)
			वापस -EBUSY;
		वापस iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_REGULAR, true);
	हाल IWL_MVM_SCAN_NETDETECT:
		/* For non-unअगरied images, there's no need to stop
		 * anything क्रम net-detect since the firmware is
		 * restarted anyway.  This way, any sched scans that
		 * were running will be restarted when we resume.
		 */
		अगर (!unअगरied_image)
			वापस 0;

		/* If this is a unअगरied image and we ran out of scans,
		 * we need to stop something.  Prefer stopping regular
		 * scans, because the results are useless at this
		 * poपूर्णांक, and we should be able to keep running
		 * another scheduled scan जबतक suspended.
		 */
		अगर (mvm->scan_status & IWL_MVM_SCAN_REGULAR_MASK)
			वापस iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_REGULAR,
						 true);
		अगर (mvm->scan_status & IWL_MVM_SCAN_SCHED_MASK)
			वापस iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_SCHED,
						 true);
		/* Something is wrong अगर no scan was running but we
		 * ran out of scans.
		 */
		fallthrough;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस -EIO;
पूर्ण

#घोषणा SCAN_TIMEOUT 20000

व्योम iwl_mvm_scan_समयout_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा iwl_mvm *mvm = container_of(delayed_work, काष्ठा iwl_mvm,
					   scan_समयout_dwork);

	IWL_ERR(mvm, "regular scan timed out\n");

	iwl_क्रमce_nmi(mvm->trans);
पूर्ण

अटल व्योम iwl_mvm_fill_scan_type(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_mvm_scan_params *params,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (iwl_mvm_is_cdb_supported(mvm)) अणु
		params->type =
			iwl_mvm_get_scan_type_band(mvm, vअगर,
						   NL80211_BAND_2GHZ);
		params->hb_type =
			iwl_mvm_get_scan_type_band(mvm, vअगर,
						   NL80211_BAND_5GHZ);
	पूर्ण अन्यथा अणु
		params->type = iwl_mvm_get_scan_type(mvm, vअगर);
	पूर्ण
पूर्ण

काष्ठा iwl_scan_umac_handler अणु
	u8 version;
	पूर्णांक (*handler)(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा iwl_mvm_scan_params *params, पूर्णांक type, पूर्णांक uid);
पूर्ण;

#घोषणा IWL_SCAN_UMAC_HANDLER(_ver) अणु		\
	.version = _ver,			\
	.handler = iwl_mvm_scan_umac_v##_ver,	\
पूर्ण

अटल स्थिर काष्ठा iwl_scan_umac_handler iwl_scan_umac_handlers[] = अणु
	/* set the newest version first to लघुen the list traverse समय */
	IWL_SCAN_UMAC_HANDLER(14),
	IWL_SCAN_UMAC_HANDLER(12),
पूर्ण;

अटल पूर्णांक iwl_mvm_build_scan_cmd(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा iwl_host_cmd *hcmd,
				  काष्ठा iwl_mvm_scan_params *params,
				  पूर्णांक type)
अणु
	पूर्णांक uid, i, err;
	u8 scan_ver;

	lockdep_निश्चित_held(&mvm->mutex);
	स_रखो(mvm->scan_cmd, 0, ksize(mvm->scan_cmd));

	अगर (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN)) अणु
		hcmd->id = SCAN_OFFLOAD_REQUEST_CMD;

		वापस iwl_mvm_scan_lmac(mvm, vअगर, params);
	पूर्ण

	uid = iwl_mvm_scan_uid_by_status(mvm, 0);
	अगर (uid < 0)
		वापस uid;

	hcmd->id = iwl_cmd_id(SCAN_REQ_UMAC, IWL_ALWAYS_LONG_GROUP, 0);

	scan_ver = iwl_fw_lookup_cmd_ver(mvm->fw, IWL_ALWAYS_LONG_GROUP,
					 SCAN_REQ_UMAC,
					 IWL_FW_CMD_VER_UNKNOWN);

	क्रम (i = 0; i < ARRAY_SIZE(iwl_scan_umac_handlers); i++) अणु
		स्थिर काष्ठा iwl_scan_umac_handler *ver_handler =
			&iwl_scan_umac_handlers[i];

		अगर (ver_handler->version != scan_ver)
			जारी;

		वापस ver_handler->handler(mvm, vअगर, params, type, uid);
	पूर्ण

	err = iwl_mvm_scan_umac(mvm, vअगर, params, type, uid);
	अगर (err)
		वापस err;

	वापस uid;
पूर्ण

पूर्णांक iwl_mvm_reg_scan_start(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा cfg80211_scan_request *req,
			   काष्ठा ieee80211_scan_ies *ies)
अणु
	काष्ठा iwl_host_cmd hcmd = अणु
		.len = अणु iwl_mvm_scan_size(mvm), पूर्ण,
		.data = अणु mvm->scan_cmd, पूर्ण,
		.dataflags = अणु IWL_HCMD_DFL_NOCOPY, पूर्ण,
	पूर्ण;
	काष्ठा iwl_mvm_scan_params params = अणुपूर्ण;
	पूर्णांक ret, uid;
	काष्ठा cfg80211_sched_scan_plan scan_plan = अणु .iterations = 1 पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (iwl_mvm_is_lar_supported(mvm) && !mvm->lar_regकरोm_set) अणु
		IWL_ERR(mvm, "scan while LAR regdomain is not set\n");
		वापस -EBUSY;
	पूर्ण

	ret = iwl_mvm_check_running_scans(mvm, IWL_MVM_SCAN_REGULAR);
	अगर (ret)
		वापस ret;

	/* we should have failed registration अगर scan_cmd was शून्य */
	अगर (WARN_ON(!mvm->scan_cmd))
		वापस -ENOMEM;

	अगर (!iwl_mvm_scan_fits(mvm, req->n_ssids, ies, req->n_channels))
		वापस -ENOBUFS;

	params.n_ssids = req->n_ssids;
	params.flags = req->flags;
	params.n_channels = req->n_channels;
	params.delay = 0;
	params.ssids = req->ssids;
	params.channels = req->channels;
	params.mac_addr = req->mac_addr;
	params.mac_addr_mask = req->mac_addr_mask;
	params.no_cck = req->no_cck;
	params.pass_all = true;
	params.n_match_sets = 0;
	params.match_sets = शून्य;

	params.scan_plans = &scan_plan;
	params.n_scan_plans = 1;

	params.n_6ghz_params = req->n_6ghz_params;
	params.scan_6ghz_params = req->scan_6ghz_params;
	params.scan_6ghz = req->scan_6ghz;
	iwl_mvm_fill_scan_type(mvm, &params, vअगर);

	अगर (req->duration)
		params.iter_notअगर = true;

	iwl_mvm_build_scan_probe(mvm, vअगर, ies, &params);

	iwl_mvm_scan_6ghz_passive_scan(mvm, &params, vअगर);

	uid = iwl_mvm_build_scan_cmd(mvm, vअगर, &hcmd, &params,
				     IWL_MVM_SCAN_REGULAR);

	अगर (uid < 0)
		वापस uid;

	iwl_mvm_छोड़ो_tcm(mvm, false);

	ret = iwl_mvm_send_cmd(mvm, &hcmd);
	अगर (ret) अणु
		/* If the scan failed, it usually means that the FW was unable
		 * to allocate the समय events. Warn on it, but maybe we
		 * should try to send the command again with dअगरferent params.
		 */
		IWL_ERR(mvm, "Scan failed! ret %d\n", ret);
		iwl_mvm_resume_tcm(mvm);
		mvm->scan_uid_status[uid] = 0;
		वापस ret;
	पूर्ण

	IWL_DEBUG_SCAN(mvm, "Scan request was sent successfully\n");
	mvm->scan_status |= IWL_MVM_SCAN_REGULAR;
	mvm->scan_vअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (params.enable_6ghz_passive)
		mvm->last_6ghz_passive_scan_jअगरfies = jअगरfies;

	schedule_delayed_work(&mvm->scan_समयout_dwork,
			      msecs_to_jअगरfies(SCAN_TIMEOUT));

	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_sched_scan_start(काष्ठा iwl_mvm *mvm,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा cfg80211_sched_scan_request *req,
			     काष्ठा ieee80211_scan_ies *ies,
			     पूर्णांक type)
अणु
	काष्ठा iwl_host_cmd hcmd = अणु
		.len = अणु iwl_mvm_scan_size(mvm), पूर्ण,
		.data = अणु mvm->scan_cmd, पूर्ण,
		.dataflags = अणु IWL_HCMD_DFL_NOCOPY, पूर्ण,
	पूर्ण;
	काष्ठा iwl_mvm_scan_params params = अणुपूर्ण;
	पूर्णांक ret, uid;
	पूर्णांक i, j;
	bool non_psc_included = false;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (iwl_mvm_is_lar_supported(mvm) && !mvm->lar_regकरोm_set) अणु
		IWL_ERR(mvm, "sched-scan while LAR regdomain is not set\n");
		वापस -EBUSY;
	पूर्ण

	ret = iwl_mvm_check_running_scans(mvm, type);
	अगर (ret)
		वापस ret;

	/* we should have failed registration अगर scan_cmd was शून्य */
	अगर (WARN_ON(!mvm->scan_cmd))
		वापस -ENOMEM;


	params.n_ssids = req->n_ssids;
	params.flags = req->flags;
	params.n_channels = req->n_channels;
	params.ssids = req->ssids;
	params.channels = req->channels;
	params.mac_addr = req->mac_addr;
	params.mac_addr_mask = req->mac_addr_mask;
	params.no_cck = false;
	params.pass_all =  iwl_mvm_scan_pass_all(mvm, req);
	params.n_match_sets = req->n_match_sets;
	params.match_sets = req->match_sets;
	अगर (!req->n_scan_plans)
		वापस -EINVAL;

	params.n_scan_plans = req->n_scan_plans;
	params.scan_plans = req->scan_plans;

	iwl_mvm_fill_scan_type(mvm, &params, vअगर);

	/* In theory, LMAC scans can handle a 32-bit delay, but since
	 * रुकोing क्रम over 18 hours to start the scan is a bit silly
	 * and to keep it aligned with UMAC scans (which only support
	 * 16-bit delays), trim it करोwn to 16-bits.
	 */
	अगर (req->delay > U16_MAX) अणु
		IWL_DEBUG_SCAN(mvm,
			       "delay value is > 16-bits, set to max possible\n");
		params.delay = U16_MAX;
	पूर्ण अन्यथा अणु
		params.delay = req->delay;
	पूर्ण

	ret = iwl_mvm_config_sched_scan_profiles(mvm, req);
	अगर (ret)
		वापस ret;

	iwl_mvm_build_scan_probe(mvm, vअगर, ies, &params);

	/* क्रम 6 GHZ band only PSC channels need to be added */
	क्रम (i = 0; i < params.n_channels; i++) अणु
		काष्ठा ieee80211_channel *channel = params.channels[i];

		अगर (channel->band == NL80211_BAND_6GHZ &&
		    !cfg80211_channel_is_psc(channel)) अणु
			non_psc_included = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (non_psc_included) अणु
		params.channels = kmemdup(params.channels,
					  माप(params.channels[0]) *
					  params.n_channels,
					  GFP_KERNEL);
		अगर (!params.channels)
			वापस -ENOMEM;

		क्रम (i = j = 0; i < params.n_channels; i++) अणु
			अगर (params.channels[i]->band == NL80211_BAND_6GHZ &&
			    !cfg80211_channel_is_psc(params.channels[i]))
				जारी;
			params.channels[j++] = params.channels[i];
		पूर्ण
		params.n_channels = j;
	पूर्ण

	अगर (non_psc_included &&
	    !iwl_mvm_scan_fits(mvm, req->n_ssids, ies, params.n_channels)) अणु
		kमुक्त(params.channels);
		वापस -ENOBUFS;
	पूर्ण

	uid = iwl_mvm_build_scan_cmd(mvm, vअगर, &hcmd, &params, type);

	अगर (non_psc_included)
		kमुक्त(params.channels);
	अगर (uid < 0)
		वापस uid;

	ret = iwl_mvm_send_cmd(mvm, &hcmd);
	अगर (!ret) अणु
		IWL_DEBUG_SCAN(mvm,
			       "Sched scan request was sent successfully\n");
		mvm->scan_status |= type;
	पूर्ण अन्यथा अणु
		/* If the scan failed, it usually means that the FW was unable
		 * to allocate the समय events. Warn on it, but maybe we
		 * should try to send the command again with dअगरferent params.
		 */
		IWL_ERR(mvm, "Sched scan failed! ret %d\n", ret);
		mvm->scan_uid_status[uid] = 0;
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_DISABLED;
	पूर्ण

	वापस ret;
पूर्ण

व्योम iwl_mvm_rx_umac_scan_complete_notअगर(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_umac_scan_complete *notअगर = (व्योम *)pkt->data;
	u32 uid = __le32_to_cpu(notअगर->uid);
	bool पातed = (notअगर->status == IWL_SCAN_OFFLOAD_ABORTED);

	अगर (WARN_ON(!(mvm->scan_uid_status[uid] & mvm->scan_status)))
		वापस;

	/* अगर the scan is alपढ़ोy stopping, we करोn't need to notअगरy mac80211 */
	अगर (mvm->scan_uid_status[uid] == IWL_MVM_SCAN_REGULAR) अणु
		काष्ठा cfg80211_scan_info info = अणु
			.पातed = पातed,
			.scan_start_tsf = mvm->scan_start,
		पूर्ण;

		स_नकल(info.tsf_bssid, mvm->scan_vअगर->bssid, ETH_ALEN);
		ieee80211_scan_completed(mvm->hw, &info);
		mvm->scan_vअगर = शून्य;
		cancel_delayed_work(&mvm->scan_समयout_dwork);
		iwl_mvm_resume_tcm(mvm);
	पूर्ण अन्यथा अगर (mvm->scan_uid_status[uid] == IWL_MVM_SCAN_SCHED) अणु
		ieee80211_sched_scan_stopped(mvm->hw);
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_DISABLED;
	पूर्ण

	mvm->scan_status &= ~mvm->scan_uid_status[uid];
	IWL_DEBUG_SCAN(mvm,
		       "Scan completed, uid %u type %u, status %s, EBS status %s\n",
		       uid, mvm->scan_uid_status[uid],
		       notअगर->status == IWL_SCAN_OFFLOAD_COMPLETED ?
				"completed" : "aborted",
		       iwl_mvm_ebs_status_str(notअगर->ebs_status));
	IWL_DEBUG_SCAN(mvm,
		       "Last line %d, Last iteration %d, Time from last iteration %d\n",
		       notअगर->last_schedule, notअगर->last_iter,
		       __le32_to_cpu(notअगर->समय_from_last_iter));

	अगर (notअगर->ebs_status != IWL_SCAN_EBS_SUCCESS &&
	    notअगर->ebs_status != IWL_SCAN_EBS_INACTIVE)
		mvm->last_ebs_successful = false;

	mvm->scan_uid_status[uid] = 0;
पूर्ण

व्योम iwl_mvm_rx_umac_scan_iter_complete_notअगर(काष्ठा iwl_mvm *mvm,
					      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_umac_scan_iter_complete_notअगर *notअगर = (व्योम *)pkt->data;

	mvm->scan_start = le64_to_cpu(notअगर->start_tsf);

	IWL_DEBUG_SCAN(mvm,
		       "UMAC Scan iteration complete: status=0x%x scanned_channels=%d\n",
		       notअगर->status, notअगर->scanned_channels);

	अगर (mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_FOUND) अणु
		IWL_DEBUG_SCAN(mvm, "Pass all scheduled scan results found\n");
		ieee80211_sched_scan_results(mvm->hw);
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_ENABLED;
	पूर्ण

	IWL_DEBUG_SCAN(mvm,
		       "UMAC Scan iteration complete: scan started at %llu (TSF)\n",
		       mvm->scan_start);
पूर्ण

अटल पूर्णांक iwl_mvm_umac_scan_पात(काष्ठा iwl_mvm *mvm, पूर्णांक type)
अणु
	काष्ठा iwl_umac_scan_पात cmd = अणुपूर्ण;
	पूर्णांक uid, ret;

	lockdep_निश्चित_held(&mvm->mutex);

	/* We should always get a valid index here, because we alपढ़ोy
	 * checked that this type of scan was running in the generic
	 * code.
	 */
	uid = iwl_mvm_scan_uid_by_status(mvm, type);
	अगर (WARN_ON_ONCE(uid < 0))
		वापस uid;

	cmd.uid = cpu_to_le32(uid);

	IWL_DEBUG_SCAN(mvm, "Sending scan abort, uid %u\n", uid);

	ret = iwl_mvm_send_cmd_pdu(mvm,
				   iwl_cmd_id(SCAN_ABORT_UMAC,
					      IWL_ALWAYS_LONG_GROUP, 0),
				   0, माप(cmd), &cmd);
	अगर (!ret)
		mvm->scan_uid_status[uid] = type << IWL_MVM_SCAN_STOPPING_SHIFT;

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_scan_stop_रुको(काष्ठा iwl_mvm *mvm, पूर्णांक type)
अणु
	काष्ठा iwl_notअगरication_रुको रुको_scan_करोne;
	अटल स्थिर u16 scan_करोne_notअगर[] = अणु SCAN_COMPLETE_UMAC,
					      SCAN_OFFLOAD_COMPLETE, पूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको, &रुको_scan_करोne,
				   scan_करोne_notअगर,
				   ARRAY_SIZE(scan_करोne_notअगर),
				   शून्य, शून्य);

	IWL_DEBUG_SCAN(mvm, "Preparing to stop scan, type %x\n", type);

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN))
		ret = iwl_mvm_umac_scan_पात(mvm, type);
	अन्यथा
		ret = iwl_mvm_lmac_scan_पात(mvm);

	अगर (ret) अणु
		IWL_DEBUG_SCAN(mvm, "couldn't stop scan type %d\n", type);
		iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &रुको_scan_करोne);
		वापस ret;
	पूर्ण

	वापस iwl_रुको_notअगरication(&mvm->notअगर_रुको, &रुको_scan_करोne,
				     1 * HZ);
पूर्ण

#घोषणा IWL_SCAN_REQ_UMAC_HANDLE_SIZE(_ver) अणु				\
	हाल (_ver): वापस माप(काष्ठा iwl_scan_req_umac_v##_ver);	\
पूर्ण

अटल पूर्णांक iwl_scan_req_umac_get_size(u8 scan_ver)
अणु
	चयन (scan_ver) अणु
		IWL_SCAN_REQ_UMAC_HANDLE_SIZE(14);
		IWL_SCAN_REQ_UMAC_HANDLE_SIZE(12);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_scan_size(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक base_size, tail_size;
	u8 scan_ver = iwl_fw_lookup_cmd_ver(mvm->fw, IWL_ALWAYS_LONG_GROUP,
					    SCAN_REQ_UMAC,
					    IWL_FW_CMD_VER_UNKNOWN);

	base_size = iwl_scan_req_umac_get_size(scan_ver);
	अगर (base_size)
		वापस base_size;


	अगर (iwl_mvm_is_adaptive_dwell_v2_supported(mvm))
		base_size = IWL_SCAN_REQ_UMAC_SIZE_V8;
	अन्यथा अगर (iwl_mvm_is_adaptive_dwell_supported(mvm))
		base_size = IWL_SCAN_REQ_UMAC_SIZE_V7;
	अन्यथा अगर (iwl_mvm_cdb_scan_api(mvm))
		base_size = IWL_SCAN_REQ_UMAC_SIZE_V6;
	अन्यथा
		base_size = IWL_SCAN_REQ_UMAC_SIZE_V1;

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN)) अणु
		अगर (iwl_mvm_is_scan_ext_chan_supported(mvm))
			tail_size = माप(काष्ठा iwl_scan_req_umac_tail_v2);
		अन्यथा
			tail_size = माप(काष्ठा iwl_scan_req_umac_tail_v1);

		वापस base_size +
			माप(काष्ठा iwl_scan_channel_cfg_umac) *
				mvm->fw->ucode_capa.n_scan_channels +
			tail_size;
	पूर्ण
	वापस माप(काष्ठा iwl_scan_req_lmac) +
		माप(काष्ठा iwl_scan_channel_cfg_lmac) *
		mvm->fw->ucode_capa.n_scan_channels +
		माप(काष्ठा iwl_scan_probe_req_v1);
पूर्ण

/*
 * This function is used in nic restart flow, to inक्रमm mac80211 about scans
 * that was पातed by restart flow or by an निश्चित.
 */
व्योम iwl_mvm_report_scan_पातed(काष्ठा iwl_mvm *mvm)
अणु
	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN)) अणु
		पूर्णांक uid, i;

		uid = iwl_mvm_scan_uid_by_status(mvm, IWL_MVM_SCAN_REGULAR);
		अगर (uid >= 0) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = true,
			पूर्ण;

			cancel_delayed_work(&mvm->scan_समयout_dwork);

			ieee80211_scan_completed(mvm->hw, &info);
			mvm->scan_uid_status[uid] = 0;
		पूर्ण
		uid = iwl_mvm_scan_uid_by_status(mvm, IWL_MVM_SCAN_SCHED);
		अगर (uid >= 0) अणु
			/* Sched scan will be restarted by mac80211 in
			 * restart_hw, so करो not report अगर FW is about to be
			 * restarted.
			 */
			अगर (!mvm->fw_restart)
				ieee80211_sched_scan_stopped(mvm->hw);
			mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_DISABLED;
			mvm->scan_uid_status[uid] = 0;
		पूर्ण
		uid = iwl_mvm_scan_uid_by_status(mvm,
						 IWL_MVM_SCAN_STOPPING_REGULAR);
		अगर (uid >= 0)
			mvm->scan_uid_status[uid] = 0;

		uid = iwl_mvm_scan_uid_by_status(mvm,
						 IWL_MVM_SCAN_STOPPING_SCHED);
		अगर (uid >= 0)
			mvm->scan_uid_status[uid] = 0;

		/* We shouldn't have any UIDs still set.  Loop over all the
		 * UIDs to make sure there's nothing left there and warn अगर
		 * any is found.
		 */
		क्रम (i = 0; i < mvm->max_scans; i++) अणु
			अगर (WARN_ONCE(mvm->scan_uid_status[i],
				      "UMAC scan UID %d status was not cleaned\n",
				      i))
				mvm->scan_uid_status[i] = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mvm->scan_status & IWL_MVM_SCAN_REGULAR) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = true,
			पूर्ण;

			cancel_delayed_work(&mvm->scan_समयout_dwork);
			ieee80211_scan_completed(mvm->hw, &info);
		पूर्ण

		/* Sched scan will be restarted by mac80211 in
		 * restart_hw, so करो not report अगर FW is about to be
		 * restarted.
		 */
		अगर ((mvm->scan_status & IWL_MVM_SCAN_SCHED) &&
		    !mvm->fw_restart) अणु
			ieee80211_sched_scan_stopped(mvm->hw);
			mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_DISABLED;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक iwl_mvm_scan_stop(काष्ठा iwl_mvm *mvm, पूर्णांक type, bool notअगरy)
अणु
	पूर्णांक ret;

	अगर (!(mvm->scan_status & type))
		वापस 0;

	अगर (iwl_mvm_is_radio_समाप्तed(mvm)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	ret = iwl_mvm_scan_stop_रुको(mvm, type);
	अगर (!ret)
		mvm->scan_status |= type << IWL_MVM_SCAN_STOPPING_SHIFT;
out:
	/* Clear the scan status so the next scan requests will
	 * succeed and mark the scan as stopping, so that the Rx
	 * handler करोesn't करो anything, as the scan was stopped from
	 * above.
	 */
	mvm->scan_status &= ~type;

	अगर (type == IWL_MVM_SCAN_REGULAR) अणु
		cancel_delayed_work(&mvm->scan_समयout_dwork);
		अगर (notअगरy) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = true,
			पूर्ण;

			ieee80211_scan_completed(mvm->hw, &info);
		पूर्ण
	पूर्ण अन्यथा अगर (notअगरy) अणु
		ieee80211_sched_scan_stopped(mvm->hw);
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_DISABLED;
	पूर्ण

	वापस ret;
पूर्ण
