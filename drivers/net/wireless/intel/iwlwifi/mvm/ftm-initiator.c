<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/math64.h>
#समावेश <net/cfg80211.h>
#समावेश "mvm.h"
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"
#समावेश "constants.h"

काष्ठा iwl_mvm_loc_entry अणु
	काष्ठा list_head list;
	u8 addr[ETH_ALEN];
	u8 lci_len, civic_len;
	u8 buf[];
पूर्ण;

काष्ठा iwl_mvm_smooth_entry अणु
	काष्ठा list_head list;
	u8 addr[ETH_ALEN];
	s64 rtt_avg;
	u64 host_समय;
पूर्ण;

काष्ठा iwl_mvm_fपंचांग_pasn_entry अणु
	काष्ठा list_head list;
	u8 addr[ETH_ALEN];
	u8 hltk[HLTK_11AZ_LEN];
	u8 tk[TK_11AZ_LEN];
	u8 cipher;
	u8 tx_pn[IEEE80211_CCMP_PN_LEN];
	u8 rx_pn[IEEE80211_CCMP_PN_LEN];
पूर्ण;

पूर्णांक iwl_mvm_fपंचांग_add_pasn_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     u8 *addr, u32 cipher, u8 *tk, u32 tk_len,
			     u8 *hltk, u32 hltk_len)
अणु
	काष्ठा iwl_mvm_fपंचांग_pasn_entry *pasn = kzalloc(माप(*pasn),
						      GFP_KERNEL);
	u32 expected_tk_len;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (!pasn)
		वापस -ENOBUFS;

	pasn->cipher = iwl_mvm_cipher_to_location_cipher(cipher);

	चयन (pasn->cipher) अणु
	हाल IWL_LOCATION_CIPHER_CCMP_128:
	हाल IWL_LOCATION_CIPHER_GCMP_128:
		expected_tk_len = WLAN_KEY_LEN_CCMP;
		अवरोध;
	हाल IWL_LOCATION_CIPHER_GCMP_256:
		expected_tk_len = WLAN_KEY_LEN_GCMP_256;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	/*
	 * If associated to this AP and alपढ़ोy have security context,
	 * the TK is alपढ़ोy configured क्रम this station, so it
	 * shouldn't be set again here.
	 */
	अगर (vअगर->bss_conf.assoc &&
	    !स_भेद(addr, vअगर->bss_conf.bssid, ETH_ALEN)) अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
		काष्ठा ieee80211_sta *sta;

		rcu_पढ़ो_lock();
		sta = rcu_dereference(mvm->fw_id_to_mac_id[mvmvअगर->ap_sta_id]);
		अगर (!IS_ERR_OR_शून्य(sta) && sta->mfp)
			expected_tk_len = 0;
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (tk_len != expected_tk_len || hltk_len != माप(pasn->hltk)) अणु
		IWL_ERR(mvm, "Invalid key length: tk_len=%u hltk_len=%u\n",
			tk_len, hltk_len);
		जाओ out;
	पूर्ण

	स_नकल(pasn->addr, addr, माप(pasn->addr));
	स_नकल(pasn->hltk, hltk, माप(pasn->hltk));

	अगर (tk && tk_len)
		स_नकल(pasn->tk, tk, माप(pasn->tk));

	list_add_tail(&pasn->list, &mvm->fपंचांग_initiator.pasn_list);
	वापस 0;
out:
	kमुक्त(pasn);
	वापस -EINVAL;
पूर्ण

व्योम iwl_mvm_fपंचांग_हटाओ_pasn_sta(काष्ठा iwl_mvm *mvm, u8 *addr)
अणु
	काष्ठा iwl_mvm_fपंचांग_pasn_entry *entry, *prev;

	lockdep_निश्चित_held(&mvm->mutex);

	list_क्रम_each_entry_safe(entry, prev, &mvm->fपंचांग_initiator.pasn_list,
				 list) अणु
		अगर (स_भेद(entry->addr, addr, माप(entry->addr)))
			जारी;

		list_del(&entry->list);
		kमुक्त(entry);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_fपंचांग_reset(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_mvm_loc_entry *e, *t;

	mvm->fपंचांग_initiator.req = शून्य;
	mvm->fपंचांग_initiator.req_wdev = शून्य;
	स_रखो(mvm->fपंचांग_initiator.responses, 0,
	       माप(mvm->fपंचांग_initiator.responses));

	list_क्रम_each_entry_safe(e, t, &mvm->fपंचांग_initiator.loc_list, list) अणु
		list_del(&e->list);
		kमुक्त(e);
	पूर्ण
पूर्ण

व्योम iwl_mvm_fपंचांग_restart(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा cfg80211_pmsr_result result = अणु
		.status = NL80211_PMSR_STATUS_FAILURE,
		.final = 1,
		.host_समय = kसमय_get_bootसमय_ns(),
		.type = NL80211_PMSR_TYPE_FTM,
	पूर्ण;
	पूर्णांक i;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (!mvm->fपंचांग_initiator.req)
		वापस;

	क्रम (i = 0; i < mvm->fपंचांग_initiator.req->n_peers; i++) अणु
		स_नकल(result.addr, mvm->fपंचांग_initiator.req->peers[i].addr,
		       ETH_ALEN);
		result.fपंचांग.burst_index = mvm->fपंचांग_initiator.responses[i];

		cfg80211_pmsr_report(mvm->fपंचांग_initiator.req_wdev,
				     mvm->fपंचांग_initiator.req,
				     &result, GFP_KERNEL);
	पूर्ण

	cfg80211_pmsr_complete(mvm->fपंचांग_initiator.req_wdev,
			       mvm->fपंचांग_initiator.req, GFP_KERNEL);
	iwl_mvm_fपंचांग_reset(mvm);
पूर्ण

व्योम iwl_mvm_fपंचांग_initiator_smooth_config(काष्ठा iwl_mvm *mvm)
अणु
	INIT_LIST_HEAD(&mvm->fपंचांग_initiator.smooth.resp);

	IWL_DEBUG_INFO(mvm,
		       "enable=%u, alpha=%u, age_jiffies=%u, thresh=(%u:%u)\n",
			IWL_MVM_FTM_INITIATOR_ENABLE_SMOOTH,
			IWL_MVM_FTM_INITIATOR_SMOOTH_ALPHA,
			IWL_MVM_FTM_INITIATOR_SMOOTH_AGE_SEC * HZ,
			IWL_MVM_FTM_INITIATOR_SMOOTH_OVERSHOOT,
			IWL_MVM_FTM_INITIATOR_SMOOTH_UNDERSHOOT);
पूर्ण

व्योम iwl_mvm_fपंचांग_initiator_smooth_stop(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_mvm_smooth_entry *se, *st;

	list_क्रम_each_entry_safe(se, st, &mvm->fपंचांग_initiator.smooth.resp,
				 list) अणु
		list_del(&se->list);
		kमुक्त(se);
	पूर्ण
पूर्ण

अटल पूर्णांक
iwl_fपंचांग_range_request_status_to_err(क्रमागत iwl_tof_range_request_status s)
अणु
	चयन (s) अणु
	हाल IWL_TOF_RANGE_REQUEST_STATUS_SUCCESS:
		वापस 0;
	हाल IWL_TOF_RANGE_REQUEST_STATUS_BUSY:
		वापस -EBUSY;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EIO;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_fपंचांग_cmd_v5(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा iwl_tof_range_req_cmd_v5 *cmd,
			       काष्ठा cfg80211_pmsr_request *req)
अणु
	पूर्णांक i;

	cmd->request_id = req->cookie;
	cmd->num_of_ap = req->n_peers;

	/* use maximum क्रम "no timeout" or bigger than what we can करो */
	अगर (!req->समयout || req->समयout > 255 * 100)
		cmd->req_समयout = 255;
	अन्यथा
		cmd->req_समयout = DIV_ROUND_UP(req->समयout, 100);

	/*
	 * We treat it always as अक्रमom, since अगर not we'll
	 * have filled our local address there instead.
	 */
	cmd->macaddr_अक्रमom = 1;
	स_नकल(cmd->macaddr_ढाँचा, req->mac_addr, ETH_ALEN);
	क्रम (i = 0; i < ETH_ALEN; i++)
		cmd->macaddr_mask[i] = ~req->mac_addr_mask[i];

	अगर (vअगर->bss_conf.assoc)
		स_नकल(cmd->range_req_bssid, vअगर->bss_conf.bssid, ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(cmd->range_req_bssid);
पूर्ण

अटल व्योम iwl_mvm_fपंचांग_cmd_common(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा iwl_tof_range_req_cmd_v9 *cmd,
				   काष्ठा cfg80211_pmsr_request *req)
अणु
	पूर्णांक i;

	cmd->initiator_flags =
		cpu_to_le32(IWL_TOF_INITIATOR_FLAGS_MACADDR_RANDOM |
			    IWL_TOF_INITIATOR_FLAGS_NON_ASAP_SUPPORT);
	cmd->request_id = req->cookie;
	cmd->num_of_ap = req->n_peers;

	/*
	 * Use a large value क्रम "no timeout". Don't use the maximum value
	 * because of fw limitations.
	 */
	अगर (req->समयout)
		cmd->req_समयout_ms = cpu_to_le32(req->समयout);
	अन्यथा
		cmd->req_समयout_ms = cpu_to_le32(0xfffff);

	स_नकल(cmd->macaddr_ढाँचा, req->mac_addr, ETH_ALEN);
	क्रम (i = 0; i < ETH_ALEN; i++)
		cmd->macaddr_mask[i] = ~req->mac_addr_mask[i];

	अगर (vअगर->bss_conf.assoc) अणु
		स_नकल(cmd->range_req_bssid, vअगर->bss_conf.bssid, ETH_ALEN);

		/* AP's TSF is only relevant अगर associated */
		क्रम (i = 0; i < req->n_peers; i++) अणु
			अगर (req->peers[i].report_ap_tsf) अणु
				काष्ठा iwl_mvm_vअगर *mvmvअगर =
					iwl_mvm_vअगर_from_mac80211(vअगर);

				cmd->tsf_mac_id = cpu_to_le32(mvmvअगर->id);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		eth_broadcast_addr(cmd->range_req_bssid);
	पूर्ण

	/* Don't report AP's TSF */
	cmd->tsf_mac_id = cpu_to_le32(0xff);
पूर्ण

अटल व्योम iwl_mvm_fपंचांग_cmd_v8(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा iwl_tof_range_req_cmd_v8 *cmd,
			       काष्ठा cfg80211_pmsr_request *req)
अणु
	iwl_mvm_fपंचांग_cmd_common(mvm, vअगर, (व्योम *)cmd, req);
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_target_chandef_v1(काष्ठा iwl_mvm *mvm,
			      काष्ठा cfg80211_pmsr_request_peer *peer,
			      u8 *channel, u8 *bandwidth,
			      u8 *ctrl_ch_position)
अणु
	u32 freq = peer->chandef.chan->center_freq;

	*channel = ieee80211_frequency_to_channel(freq);

	चयन (peer->chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		*bandwidth = IWL_TOF_BW_20_LEGACY;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20:
		*bandwidth = IWL_TOF_BW_20_HT;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		*bandwidth = IWL_TOF_BW_40;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		*bandwidth = IWL_TOF_BW_80;
		अवरोध;
	शेष:
		IWL_ERR(mvm, "Unsupported BW in FTM request (%d)\n",
			peer->chandef.width);
		वापस -EINVAL;
	पूर्ण

	*ctrl_ch_position = (peer->chandef.width > NL80211_CHAN_WIDTH_20) ?
		iwl_mvm_get_ctrl_pos(&peer->chandef) : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_target_chandef_v2(काष्ठा iwl_mvm *mvm,
			      काष्ठा cfg80211_pmsr_request_peer *peer,
			      u8 *channel, u8 *क्रमmat_bw,
			      u8 *ctrl_ch_position)
अणु
	u32 freq = peer->chandef.chan->center_freq;

	*channel = ieee80211_frequency_to_channel(freq);

	चयन (peer->chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		*क्रमmat_bw = IWL_LOCATION_FRAME_FORMAT_LEGACY;
		*क्रमmat_bw |= IWL_LOCATION_BW_20MHZ << LOCATION_BW_POS;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20:
		*क्रमmat_bw = IWL_LOCATION_FRAME_FORMAT_HT;
		*क्रमmat_bw |= IWL_LOCATION_BW_20MHZ << LOCATION_BW_POS;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		*क्रमmat_bw = IWL_LOCATION_FRAME_FORMAT_HT;
		*क्रमmat_bw |= IWL_LOCATION_BW_40MHZ << LOCATION_BW_POS;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		*क्रमmat_bw = IWL_LOCATION_FRAME_FORMAT_VHT;
		*क्रमmat_bw |= IWL_LOCATION_BW_80MHZ << LOCATION_BW_POS;
		अवरोध;
	शेष:
		IWL_ERR(mvm, "Unsupported BW in FTM request (%d)\n",
			peer->chandef.width);
		वापस -EINVAL;
	पूर्ण

	/* non EDCA based measurement must use HE preamble */
	अगर (peer->fपंचांग.trigger_based || peer->fपंचांग.non_trigger_based)
		*क्रमmat_bw |= IWL_LOCATION_FRAME_FORMAT_HE;

	*ctrl_ch_position = (peer->chandef.width > NL80211_CHAN_WIDTH_20) ?
		iwl_mvm_get_ctrl_pos(&peer->chandef) : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_put_target_v2(काष्ठा iwl_mvm *mvm,
			  काष्ठा cfg80211_pmsr_request_peer *peer,
			  काष्ठा iwl_tof_range_req_ap_entry_v2 *target)
अणु
	पूर्णांक ret;

	ret = iwl_mvm_fपंचांग_target_chandef_v1(mvm, peer, &target->channel_num,
					    &target->bandwidth,
					    &target->ctrl_ch_position);
	अगर (ret)
		वापस ret;

	स_नकल(target->bssid, peer->addr, ETH_ALEN);
	target->burst_period =
		cpu_to_le16(peer->fपंचांग.burst_period);
	target->samples_per_burst = peer->fपंचांग.fपंचांगs_per_burst;
	target->num_of_bursts = peer->fपंचांग.num_bursts_exp;
	target->measure_type = 0; /* regular two-sided FTM */
	target->retries_per_sample = peer->fपंचांग.fपंचांगr_retries;
	target->asap_mode = peer->fपंचांग.asap;
	target->enable_dyn_ack = IWL_MVM_FTM_INITIATOR_DYNACK;

	अगर (peer->fपंचांग.request_lci)
		target->location_req |= IWL_TOF_LOC_LCI;
	अगर (peer->fपंचांग.request_civicloc)
		target->location_req |= IWL_TOF_LOC_CIVIC;

	target->algo_type = IWL_MVM_FTM_INITIATOR_ALGO;

	वापस 0;
पूर्ण

#घोषणा FTM_PUT_FLAG(flag)	(target->initiator_ap_flags |= \
				 cpu_to_le32(IWL_INITIATOR_AP_FLAGS_##flag))

अटल व्योम
iwl_mvm_fपंचांग_put_target_common(काष्ठा iwl_mvm *mvm,
			      काष्ठा cfg80211_pmsr_request_peer *peer,
			      काष्ठा iwl_tof_range_req_ap_entry_v6 *target)
अणु
	स_नकल(target->bssid, peer->addr, ETH_ALEN);
	target->burst_period =
		cpu_to_le16(peer->fपंचांग.burst_period);
	target->samples_per_burst = peer->fपंचांग.fपंचांगs_per_burst;
	target->num_of_bursts = peer->fपंचांग.num_bursts_exp;
	target->fपंचांगr_max_retries = peer->fपंचांग.fपंचांगr_retries;
	target->initiator_ap_flags = cpu_to_le32(0);

	अगर (peer->fपंचांग.asap)
		FTM_PUT_FLAG(ASAP);

	अगर (peer->fपंचांग.request_lci)
		FTM_PUT_FLAG(LCI_REQUEST);

	अगर (peer->fपंचांग.request_civicloc)
		FTM_PUT_FLAG(CIVIC_REQUEST);

	अगर (IWL_MVM_FTM_INITIATOR_DYNACK)
		FTM_PUT_FLAG(DYN_ACK);

	अगर (IWL_MVM_FTM_INITIATOR_ALGO == IWL_TOF_ALGO_TYPE_LINEAR_REG)
		FTM_PUT_FLAG(ALGO_LR);
	अन्यथा अगर (IWL_MVM_FTM_INITIATOR_ALGO == IWL_TOF_ALGO_TYPE_FFT)
		FTM_PUT_FLAG(ALGO_FFT);

	अगर (peer->fपंचांग.trigger_based)
		FTM_PUT_FLAG(TB);
	अन्यथा अगर (peer->fपंचांग.non_trigger_based)
		FTM_PUT_FLAG(NON_TB);
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_put_target_v3(काष्ठा iwl_mvm *mvm,
			  काष्ठा cfg80211_pmsr_request_peer *peer,
			  काष्ठा iwl_tof_range_req_ap_entry_v3 *target)
अणु
	पूर्णांक ret;

	ret = iwl_mvm_fपंचांग_target_chandef_v1(mvm, peer, &target->channel_num,
					    &target->bandwidth,
					    &target->ctrl_ch_position);
	अगर (ret)
		वापस ret;

	/*
	 * Versions 3 and 4 has some common fields, so
	 * iwl_mvm_fपंचांग_put_target_common() can be used क्रम version 7 too.
	 */
	iwl_mvm_fपंचांग_put_target_common(mvm, peer, (व्योम *)target);

	वापस 0;
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_put_target_v4(काष्ठा iwl_mvm *mvm,
			  काष्ठा cfg80211_pmsr_request_peer *peer,
			  काष्ठा iwl_tof_range_req_ap_entry_v4 *target)
अणु
	पूर्णांक ret;

	ret = iwl_mvm_fपंचांग_target_chandef_v2(mvm, peer, &target->channel_num,
					    &target->क्रमmat_bw,
					    &target->ctrl_ch_position);
	अगर (ret)
		वापस ret;

	iwl_mvm_fपंचांग_put_target_common(mvm, peer, (व्योम *)target);

	वापस 0;
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_put_target(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा cfg80211_pmsr_request_peer *peer,
		       काष्ठा iwl_tof_range_req_ap_entry_v6 *target)
अणु
	पूर्णांक ret;

	ret = iwl_mvm_fपंचांग_target_chandef_v2(mvm, peer, &target->channel_num,
					    &target->क्रमmat_bw,
					    &target->ctrl_ch_position);
	अगर (ret)
		वापस ret;

	iwl_mvm_fपंचांग_put_target_common(mvm, peer, target);

	अगर (vअगर->bss_conf.assoc &&
	    !स_भेद(peer->addr, vअगर->bss_conf.bssid, ETH_ALEN)) अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
		काष्ठा ieee80211_sta *sta;

		rcu_पढ़ो_lock();

		sta = rcu_dereference(mvm->fw_id_to_mac_id[mvmvअगर->ap_sta_id]);
		अगर (sta->mfp)
			FTM_PUT_FLAG(PMF);

		rcu_पढ़ो_unlock();

		target->sta_id = mvmvअगर->ap_sta_id;
	पूर्ण अन्यथा अणु
		target->sta_id = IWL_MVM_INVALID_STA;
	पूर्ण

	/*
	 * TODO: Beacon पूर्णांकerval is currently unknown, so use the common value
	 * of 100 TUs.
	 */
	target->beacon_पूर्णांकerval = cpu_to_le16(100);
	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_send_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_host_cmd *hcmd)
अणु
	u32 status;
	पूर्णांक err = iwl_mvm_send_cmd_status(mvm, hcmd, &status);

	अगर (!err && status) अणु
		IWL_ERR(mvm, "FTM range request command failure, status: %u\n",
			status);
		err = iwl_fपंचांग_range_request_status_to_err(status);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_start_v5(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा cfg80211_pmsr_request *req)
अणु
	काष्ठा iwl_tof_range_req_cmd_v5 cmd_v5;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(TOF_RANGE_REQ_CMD, LOCATION_GROUP, 0),
		.dataflags[0] = IWL_HCMD_DFL_DUP,
		.data[0] = &cmd_v5,
		.len[0] = माप(cmd_v5),
	पूर्ण;
	u8 i;
	पूर्णांक err;

	iwl_mvm_fपंचांग_cmd_v5(mvm, vअगर, &cmd_v5, req);

	क्रम (i = 0; i < cmd_v5.num_of_ap; i++) अणु
		काष्ठा cfg80211_pmsr_request_peer *peer = &req->peers[i];

		err = iwl_mvm_fपंचांग_put_target_v2(mvm, peer, &cmd_v5.ap[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस iwl_mvm_fपंचांग_send_cmd(mvm, &hcmd);
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_start_v7(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा cfg80211_pmsr_request *req)
अणु
	काष्ठा iwl_tof_range_req_cmd_v7 cmd_v7;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(TOF_RANGE_REQ_CMD, LOCATION_GROUP, 0),
		.dataflags[0] = IWL_HCMD_DFL_DUP,
		.data[0] = &cmd_v7,
		.len[0] = माप(cmd_v7),
	पूर्ण;
	u8 i;
	पूर्णांक err;

	/*
	 * Versions 7 and 8 has the same काष्ठाure except from the responders
	 * list, so iwl_mvm_fपंचांग_cmd() can be used क्रम version 7 too.
	 */
	iwl_mvm_fपंचांग_cmd_v8(mvm, vअगर, (व्योम *)&cmd_v7, req);

	क्रम (i = 0; i < cmd_v7.num_of_ap; i++) अणु
		काष्ठा cfg80211_pmsr_request_peer *peer = &req->peers[i];

		err = iwl_mvm_fपंचांग_put_target_v3(mvm, peer, &cmd_v7.ap[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस iwl_mvm_fपंचांग_send_cmd(mvm, &hcmd);
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_start_v8(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा cfg80211_pmsr_request *req)
अणु
	काष्ठा iwl_tof_range_req_cmd_v8 cmd;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(TOF_RANGE_REQ_CMD, LOCATION_GROUP, 0),
		.dataflags[0] = IWL_HCMD_DFL_DUP,
		.data[0] = &cmd,
		.len[0] = माप(cmd),
	पूर्ण;
	u8 i;
	पूर्णांक err;

	iwl_mvm_fपंचांग_cmd_v8(mvm, vअगर, (व्योम *)&cmd, req);

	क्रम (i = 0; i < cmd.num_of_ap; i++) अणु
		काष्ठा cfg80211_pmsr_request_peer *peer = &req->peers[i];

		err = iwl_mvm_fपंचांग_put_target_v4(mvm, peer, &cmd.ap[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस iwl_mvm_fपंचांग_send_cmd(mvm, &hcmd);
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_start_v9(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा cfg80211_pmsr_request *req)
अणु
	काष्ठा iwl_tof_range_req_cmd_v9 cmd;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(TOF_RANGE_REQ_CMD, LOCATION_GROUP, 0),
		.dataflags[0] = IWL_HCMD_DFL_DUP,
		.data[0] = &cmd,
		.len[0] = माप(cmd),
	पूर्ण;
	u8 i;
	पूर्णांक err;

	iwl_mvm_fपंचांग_cmd_common(mvm, vअगर, &cmd, req);

	क्रम (i = 0; i < cmd.num_of_ap; i++) अणु
		काष्ठा cfg80211_pmsr_request_peer *peer = &req->peers[i];
		काष्ठा iwl_tof_range_req_ap_entry_v6 *target = &cmd.ap[i];

		err = iwl_mvm_fपंचांग_put_target(mvm, vअगर, peer, target);
		अगर (err)
			वापस err;
	पूर्ण

	वापस iwl_mvm_fपंचांग_send_cmd(mvm, &hcmd);
पूर्ण

अटल व्योम iter(काष्ठा ieee80211_hw *hw,
		 काष्ठा ieee80211_vअगर *vअगर,
		 काष्ठा ieee80211_sta *sta,
		 काष्ठा ieee80211_key_conf *key,
		 व्योम *data)
अणु
	काष्ठा iwl_tof_range_req_ap_entry_v6 *target = data;

	अगर (!sta || स_भेद(sta->addr, target->bssid, ETH_ALEN))
		वापस;

	WARN_ON(!sta->mfp);

	अगर (WARN_ON(key->keylen > माप(target->tk)))
		वापस;

	स_नकल(target->tk, key->key, key->keylen);
	target->cipher = iwl_mvm_cipher_to_location_cipher(key->cipher);
	WARN_ON(target->cipher == IWL_LOCATION_CIPHER_INVALID);
पूर्ण

अटल व्योम
iwl_mvm_fपंचांग_set_secured_ranging(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा iwl_tof_range_req_ap_entry_v7 *target)
अणु
	काष्ठा iwl_mvm_fपंचांग_pasn_entry *entry;
	u32 flags = le32_to_cpu(target->initiator_ap_flags);

	अगर (!(flags & (IWL_INITIATOR_AP_FLAGS_NON_TB |
		       IWL_INITIATOR_AP_FLAGS_TB)))
		वापस;

	lockdep_निश्चित_held(&mvm->mutex);

	list_क्रम_each_entry(entry, &mvm->fपंचांग_initiator.pasn_list, list) अणु
		अगर (स_भेद(entry->addr, target->bssid, माप(entry->addr)))
			जारी;

		target->cipher = entry->cipher;
		स_नकल(target->hltk, entry->hltk, माप(target->hltk));

		अगर (vअगर->bss_conf.assoc &&
		    !स_भेद(vअगर->bss_conf.bssid, target->bssid,
			    माप(target->bssid)))
			ieee80211_iter_keys(mvm->hw, vअगर, iter, target);
		अन्यथा
			स_नकल(target->tk, entry->tk, माप(target->tk));

		स_नकल(target->rx_pn, entry->rx_pn, माप(target->rx_pn));
		स_नकल(target->tx_pn, entry->tx_pn, माप(target->tx_pn));

		target->initiator_ap_flags |=
			cpu_to_le32(IWL_INITIATOR_AP_FLAGS_SECURED);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_put_target_v7(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा cfg80211_pmsr_request_peer *peer,
			  काष्ठा iwl_tof_range_req_ap_entry_v7 *target)
अणु
	पूर्णांक err = iwl_mvm_fपंचांग_put_target(mvm, vअगर, peer, (व्योम *)target);
	अगर (err)
		वापस err;

	iwl_mvm_fपंचांग_set_secured_ranging(mvm, vअगर, target);
	वापस err;
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_start_v11(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा cfg80211_pmsr_request *req)
अणु
	काष्ठा iwl_tof_range_req_cmd_v11 cmd;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(TOF_RANGE_REQ_CMD, LOCATION_GROUP, 0),
		.dataflags[0] = IWL_HCMD_DFL_DUP,
		.data[0] = &cmd,
		.len[0] = माप(cmd),
	पूर्ण;
	u8 i;
	पूर्णांक err;

	iwl_mvm_fपंचांग_cmd_common(mvm, vअगर, (व्योम *)&cmd, req);

	क्रम (i = 0; i < cmd.num_of_ap; i++) अणु
		काष्ठा cfg80211_pmsr_request_peer *peer = &req->peers[i];
		काष्ठा iwl_tof_range_req_ap_entry_v7 *target = &cmd.ap[i];

		err = iwl_mvm_fपंचांग_put_target_v7(mvm, vअगर, peer, target);
		अगर (err)
			वापस err;
	पूर्ण

	वापस iwl_mvm_fपंचांग_send_cmd(mvm, &hcmd);
पूर्ण

अटल व्योम
iwl_mvm_fपंचांग_set_ndp_params(काष्ठा iwl_mvm *mvm,
			   काष्ठा iwl_tof_range_req_ap_entry_v8 *target)
अणु
	/* Only 2 STS are supported on Tx */
	u32 i2r_max_sts = IWL_MVM_FTM_I2R_MAX_STS > 1 ? 1 :
		IWL_MVM_FTM_I2R_MAX_STS;

	target->r2i_ndp_params = IWL_MVM_FTM_R2I_MAX_REP |
		(IWL_MVM_FTM_R2I_MAX_STS << IWL_LOCATION_MAX_STS_POS);
	target->i2r_ndp_params = IWL_MVM_FTM_I2R_MAX_REP |
		(i2r_max_sts << IWL_LOCATION_MAX_STS_POS);
	target->r2i_max_total_ltf = IWL_MVM_FTM_R2I_MAX_TOTAL_LTF;
	target->i2r_max_total_ltf = IWL_MVM_FTM_I2R_MAX_TOTAL_LTF;
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_start_v12(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा cfg80211_pmsr_request *req)
अणु
	काष्ठा iwl_tof_range_req_cmd_v12 cmd;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(TOF_RANGE_REQ_CMD, LOCATION_GROUP, 0),
		.dataflags[0] = IWL_HCMD_DFL_DUP,
		.data[0] = &cmd,
		.len[0] = माप(cmd),
	पूर्ण;
	u8 i;
	पूर्णांक err;

	iwl_mvm_fपंचांग_cmd_common(mvm, vअगर, (व्योम *)&cmd, req);

	क्रम (i = 0; i < cmd.num_of_ap; i++) अणु
		काष्ठा cfg80211_pmsr_request_peer *peer = &req->peers[i];
		काष्ठा iwl_tof_range_req_ap_entry_v8 *target = &cmd.ap[i];
		u32 flags;

		err = iwl_mvm_fपंचांग_put_target_v7(mvm, vअगर, peer, (व्योम *)target);
		अगर (err)
			वापस err;

		iwl_mvm_fपंचांग_set_ndp_params(mvm, target);

		/*
		 * If secure LTF is turned off, replace the flag with PMF only
		 */
		flags = le32_to_cpu(target->initiator_ap_flags);
		अगर ((flags & IWL_INITIATOR_AP_FLAGS_SECURED) &&
		    !IWL_MVM_FTM_INITIATOR_SECURE_LTF) अणु
			flags &= ~IWL_INITIATOR_AP_FLAGS_SECURED;
			flags |= IWL_INITIATOR_AP_FLAGS_PMF;
			target->initiator_ap_flags = cpu_to_le32(flags);
		पूर्ण
	पूर्ण

	वापस iwl_mvm_fपंचांग_send_cmd(mvm, &hcmd);
पूर्ण

पूर्णांक iwl_mvm_fपंचांग_start(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा cfg80211_pmsr_request *req)
अणु
	bool new_api = fw_has_api(&mvm->fw->ucode_capa,
				  IWL_UCODE_TLV_API_FTM_NEW_RANGE_REQ);
	पूर्णांक err;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (mvm->fपंचांग_initiator.req)
		वापस -EBUSY;

	अगर (new_api) अणु
		u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, LOCATION_GROUP,
						   TOF_RANGE_REQ_CMD,
						   IWL_FW_CMD_VER_UNKNOWN);

		चयन (cmd_ver) अणु
		हाल 12:
			err = iwl_mvm_fपंचांग_start_v12(mvm, vअगर, req);
			अवरोध;
		हाल 11:
			err = iwl_mvm_fपंचांग_start_v11(mvm, vअगर, req);
			अवरोध;
		हाल 9:
		हाल 10:
			err = iwl_mvm_fपंचांग_start_v9(mvm, vअगर, req);
			अवरोध;
		हाल 8:
			err = iwl_mvm_fपंचांग_start_v8(mvm, vअगर, req);
			अवरोध;
		शेष:
			err = iwl_mvm_fपंचांग_start_v7(mvm, vअगर, req);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = iwl_mvm_fपंचांग_start_v5(mvm, vअगर, req);
	पूर्ण

	अगर (!err) अणु
		mvm->fपंचांग_initiator.req = req;
		mvm->fपंचांग_initiator.req_wdev = ieee80211_vअगर_to_wdev(vअगर);
	पूर्ण

	वापस err;
पूर्ण

व्योम iwl_mvm_fपंचांग_पात(काष्ठा iwl_mvm *mvm, काष्ठा cfg80211_pmsr_request *req)
अणु
	काष्ठा iwl_tof_range_पात_cmd cmd = अणु
		.request_id = req->cookie,
	पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (req != mvm->fपंचांग_initiator.req)
		वापस;

	iwl_mvm_fपंचांग_reset(mvm);

	अगर (iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(TOF_RANGE_ABORT_CMD,
						 LOCATION_GROUP, 0),
				 0, माप(cmd), &cmd))
		IWL_ERR(mvm, "failed to abort FTM process\n");
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_find_peer(काष्ठा cfg80211_pmsr_request *req,
				 स्थिर u8 *addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < req->n_peers; i++) अणु
		काष्ठा cfg80211_pmsr_request_peer *peer = &req->peers[i];

		अगर (ether_addr_equal_unaligned(peer->addr, addr))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल u64 iwl_mvm_fपंचांग_get_host_समय(काष्ठा iwl_mvm *mvm, __le32 fw_gp2_ts)
अणु
	u32 gp2_ts = le32_to_cpu(fw_gp2_ts);
	u32 curr_gp2, dअगरf;
	u64 now_from_boot_ns;

	iwl_mvm_get_sync_समय(mvm, &curr_gp2, &now_from_boot_ns);

	अगर (curr_gp2 >= gp2_ts)
		dअगरf = curr_gp2 - gp2_ts;
	अन्यथा
		dअगरf = curr_gp2 + (U32_MAX - gp2_ts + 1);

	वापस now_from_boot_ns - (u64)dअगरf * 1000;
पूर्ण

अटल व्योम iwl_mvm_fपंचांग_get_lci_civic(काष्ठा iwl_mvm *mvm,
				      काष्ठा cfg80211_pmsr_result *res)
अणु
	काष्ठा iwl_mvm_loc_entry *entry;

	list_क्रम_each_entry(entry, &mvm->fपंचांग_initiator.loc_list, list) अणु
		अगर (!ether_addr_equal_unaligned(res->addr, entry->addr))
			जारी;

		अगर (entry->lci_len) अणु
			res->fपंचांग.lci_len = entry->lci_len;
			res->fपंचांग.lci = entry->buf;
		पूर्ण

		अगर (entry->civic_len) अणु
			res->fपंचांग.civicloc_len = entry->civic_len;
			res->fपंचांग.civicloc = entry->buf + entry->lci_len;
		पूर्ण

		/* we found the entry we needed */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_range_resp_valid(काष्ठा iwl_mvm *mvm, u8 request_id,
					u8 num_of_aps)
अणु
	lockdep_निश्चित_held(&mvm->mutex);

	अगर (request_id != (u8)mvm->fपंचांग_initiator.req->cookie) अणु
		IWL_ERR(mvm, "Request ID mismatch, got %u, active %u\n",
			request_id, (u8)mvm->fपंचांग_initiator.req->cookie);
		वापस -EINVAL;
	पूर्ण

	अगर (num_of_aps > mvm->fपंचांग_initiator.req->n_peers) अणु
		IWL_ERR(mvm, "FTM range response invalid\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_fपंचांग_rtt_smoothing(काष्ठा iwl_mvm *mvm,
				      काष्ठा cfg80211_pmsr_result *res)
अणु
	काष्ठा iwl_mvm_smooth_entry *resp;
	s64 rtt_avg, rtt = res->fपंचांग.rtt_avg;
	u32 undershoot, overshoot;
	u8 alpha;
	bool found;

	अगर (!IWL_MVM_FTM_INITIATOR_ENABLE_SMOOTH)
		वापस;

	WARN_ON(rtt < 0);

	अगर (res->status != NL80211_PMSR_STATUS_SUCCESS) अणु
		IWL_DEBUG_INFO(mvm,
			       ": %pM: ignore failed measurement. Status=%u\n",
			       res->addr, res->status);
		वापस;
	पूर्ण

	found = false;
	list_क्रम_each_entry(resp, &mvm->fपंचांग_initiator.smooth.resp, list) अणु
		अगर (!स_भेद(res->addr, resp->addr, ETH_ALEN)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		resp = kzalloc(माप(*resp), GFP_KERNEL);
		अगर (!resp)
			वापस;

		स_नकल(resp->addr, res->addr, ETH_ALEN);
		list_add_tail(&resp->list, &mvm->fपंचांग_initiator.smooth.resp);

		resp->rtt_avg = rtt;

		IWL_DEBUG_INFO(mvm, "new: %pM: rtt_avg=%lld\n",
			       resp->addr, resp->rtt_avg);
		जाओ update_समय;
	पूर्ण

	अगर (res->host_समय - resp->host_समय >
	    IWL_MVM_FTM_INITIATOR_SMOOTH_AGE_SEC * 1000000000) अणु
		resp->rtt_avg = rtt;

		IWL_DEBUG_INFO(mvm, "expired: %pM: rtt_avg=%lld\n",
			       resp->addr, resp->rtt_avg);
		जाओ update_समय;
	पूर्ण

	/* Smooth the results based on the tracked RTT average */
	undershoot = IWL_MVM_FTM_INITIATOR_SMOOTH_UNDERSHOOT;
	overshoot = IWL_MVM_FTM_INITIATOR_SMOOTH_OVERSHOOT;
	alpha = IWL_MVM_FTM_INITIATOR_SMOOTH_ALPHA;

	rtt_avg = (alpha * rtt + (100 - alpha) * resp->rtt_avg) / 100;

	IWL_DEBUG_INFO(mvm,
		       "%pM: prev rtt_avg=%lld, new rtt_avg=%lld, rtt=%lld\n",
		       resp->addr, resp->rtt_avg, rtt_avg, rtt);

	/*
	 * update the responder's average RTT results regardless of
	 * the under/over shoot logic below
	 */
	resp->rtt_avg = rtt_avg;

	/* smooth the results */
	अगर (rtt_avg > rtt && (rtt_avg - rtt) > undershoot) अणु
		res->fपंचांग.rtt_avg = rtt_avg;

		IWL_DEBUG_INFO(mvm,
			       "undershoot: val=%lld\n",
			       (rtt_avg - rtt));
	पूर्ण अन्यथा अगर (rtt_avg < rtt && (rtt - rtt_avg) >
		   overshoot) अणु
		res->fपंचांग.rtt_avg = rtt_avg;
		IWL_DEBUG_INFO(mvm,
			       "overshoot: val=%lld\n",
			       (rtt - rtt_avg));
	पूर्ण

update_समय:
	resp->host_समय = res->host_समय;
पूर्ण

अटल व्योम iwl_mvm_debug_range_resp(काष्ठा iwl_mvm *mvm, u8 index,
				     काष्ठा cfg80211_pmsr_result *res)
अणु
	s64 rtt_avg = भाग_s64(res->fपंचांग.rtt_avg * 100, 6666);

	IWL_DEBUG_INFO(mvm, "entry %d\n", index);
	IWL_DEBUG_INFO(mvm, "\tstatus: %d\n", res->status);
	IWL_DEBUG_INFO(mvm, "\tBSSID: %pM\n", res->addr);
	IWL_DEBUG_INFO(mvm, "\thost time: %llu\n", res->host_समय);
	IWL_DEBUG_INFO(mvm, "\tburst index: %hhu\n", res->fपंचांग.burst_index);
	IWL_DEBUG_INFO(mvm, "\tsuccess num: %u\n", res->fपंचांग.num_fपंचांगr_successes);
	IWL_DEBUG_INFO(mvm, "\trssi: %d\n", res->fपंचांग.rssi_avg);
	IWL_DEBUG_INFO(mvm, "\trssi spread: %hhu\n", res->fपंचांग.rssi_spपढ़ो);
	IWL_DEBUG_INFO(mvm, "\trtt: %lld\n", res->fपंचांग.rtt_avg);
	IWL_DEBUG_INFO(mvm, "\trtt var: %llu\n", res->fपंचांग.rtt_variance);
	IWL_DEBUG_INFO(mvm, "\trtt spread: %llu\n", res->fपंचांग.rtt_spपढ़ो);
	IWL_DEBUG_INFO(mvm, "\tdistance: %lld\n", rtt_avg);
पूर्ण

अटल व्योम
iwl_mvm_fपंचांग_pasn_update_pn(काष्ठा iwl_mvm *mvm,
			   काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v6 *fw_ap)
अणु
	काष्ठा iwl_mvm_fपंचांग_pasn_entry *entry;

	lockdep_निश्चित_held(&mvm->mutex);

	list_क्रम_each_entry(entry, &mvm->fपंचांग_initiator.pasn_list, list) अणु
		अगर (स_भेद(fw_ap->bssid, entry->addr, माप(entry->addr)))
			जारी;

		स_नकल(entry->rx_pn, fw_ap->rx_pn, माप(entry->rx_pn));
		स_नकल(entry->tx_pn, fw_ap->tx_pn, माप(entry->tx_pn));
		वापस;
	पूर्ण
पूर्ण

अटल u8 iwl_mvm_fपंचांग_get_range_resp_ver(काष्ठा iwl_mvm *mvm)
अणु
	अगर (!fw_has_api(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_API_FTM_NEW_RANGE_REQ))
		वापस 5;

	/* Starting from version 8, the FW advertises the version */
	अगर (mvm->cmd_ver.range_resp >= 8)
		वापस mvm->cmd_ver.range_resp;
	अन्यथा अगर (fw_has_api(&mvm->fw->ucode_capa,
			    IWL_UCODE_TLV_API_FTM_RTT_ACCURACY))
		वापस 7;

	/* The first version of the new range request API */
	वापस 6;
पूर्ण

अटल bool iwl_mvm_fपंचांग_resp_size_validation(u8 ver, अचिन्हित पूर्णांक pkt_len)
अणु
	चयन (ver) अणु
	हाल 8:
		वापस pkt_len == माप(काष्ठा iwl_tof_range_rsp_ntfy_v8);
	हाल 7:
		वापस pkt_len == माप(काष्ठा iwl_tof_range_rsp_ntfy_v7);
	हाल 6:
		वापस pkt_len == माप(काष्ठा iwl_tof_range_rsp_ntfy_v6);
	हाल 5:
		वापस pkt_len == माप(काष्ठा iwl_tof_range_rsp_ntfy_v5);
	शेष:
		WARN_ONCE(1, "FTM: unsupported range response version %u", ver);
		वापस false;
	पूर्ण
पूर्ण

व्योम iwl_mvm_fपंचांग_range_resp(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	अचिन्हित पूर्णांक pkt_len = iwl_rx_packet_payload_len(pkt);
	काष्ठा iwl_tof_range_rsp_ntfy_v5 *fw_resp_v5 = (व्योम *)pkt->data;
	काष्ठा iwl_tof_range_rsp_ntfy_v6 *fw_resp_v6 = (व्योम *)pkt->data;
	काष्ठा iwl_tof_range_rsp_ntfy_v7 *fw_resp_v7 = (व्योम *)pkt->data;
	काष्ठा iwl_tof_range_rsp_ntfy_v8 *fw_resp_v8 = (व्योम *)pkt->data;
	पूर्णांक i;
	bool new_api = fw_has_api(&mvm->fw->ucode_capa,
				  IWL_UCODE_TLV_API_FTM_NEW_RANGE_REQ);
	u8 num_of_aps, last_in_batch;
	u8 notअगर_ver = iwl_mvm_fपंचांग_get_range_resp_ver(mvm);

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (!mvm->fपंचांग_initiator.req) अणु
		वापस;
	पूर्ण

	अगर (unlikely(!iwl_mvm_fपंचांग_resp_size_validation(notअगर_ver, pkt_len)))
		वापस;

	अगर (new_api) अणु
		अगर (iwl_mvm_fपंचांग_range_resp_valid(mvm, fw_resp_v8->request_id,
						 fw_resp_v8->num_of_aps))
			वापस;

		num_of_aps = fw_resp_v8->num_of_aps;
		last_in_batch = fw_resp_v8->last_report;
	पूर्ण अन्यथा अणु
		अगर (iwl_mvm_fपंचांग_range_resp_valid(mvm, fw_resp_v5->request_id,
						 fw_resp_v5->num_of_aps))
			वापस;

		num_of_aps = fw_resp_v5->num_of_aps;
		last_in_batch = fw_resp_v5->last_in_batch;
	पूर्ण

	IWL_DEBUG_INFO(mvm, "Range response received\n");
	IWL_DEBUG_INFO(mvm, "request id: %lld, num of entries: %hhu\n",
		       mvm->fपंचांग_initiator.req->cookie, num_of_aps);

	क्रम (i = 0; i < num_of_aps && i < IWL_MVM_TOF_MAX_APS; i++) अणु
		काष्ठा cfg80211_pmsr_result result = अणुपूर्ण;
		काष्ठा iwl_tof_range_rsp_ap_entry_ntfy_v6 *fw_ap;
		पूर्णांक peer_idx;

		अगर (new_api) अणु
			अगर (notअगर_ver == 8) अणु
				fw_ap = &fw_resp_v8->ap[i];
				iwl_mvm_fपंचांग_pasn_update_pn(mvm, fw_ap);
			पूर्ण अन्यथा अगर (notअगर_ver == 7) अणु
				fw_ap = (व्योम *)&fw_resp_v7->ap[i];
			पूर्ण अन्यथा अणु
				fw_ap = (व्योम *)&fw_resp_v6->ap[i];
			पूर्ण

			result.final = fw_ap->last_burst;
			result.ap_tsf = le32_to_cpu(fw_ap->start_tsf);
			result.ap_tsf_valid = 1;
		पूर्ण अन्यथा अणु
			/* the first part is the same क्रम old and new APIs */
			fw_ap = (व्योम *)&fw_resp_v5->ap[i];
			/*
			 * FIXME: the firmware needs to report this, we करोn't
			 * even know the number of bursts the responder picked
			 * (अगर we asked it to)
			 */
			result.final = 0;
		पूर्ण

		peer_idx = iwl_mvm_fपंचांग_find_peer(mvm->fपंचांग_initiator.req,
						 fw_ap->bssid);
		अगर (peer_idx < 0) अणु
			IWL_WARN(mvm,
				 "Unknown address (%pM, target #%d) in FTM response\n",
				 fw_ap->bssid, i);
			जारी;
		पूर्ण

		चयन (fw_ap->measure_status) अणु
		हाल IWL_TOF_ENTRY_SUCCESS:
			result.status = NL80211_PMSR_STATUS_SUCCESS;
			अवरोध;
		हाल IWL_TOF_ENTRY_TIMING_MEASURE_TIMEOUT:
			result.status = NL80211_PMSR_STATUS_TIMEOUT;
			अवरोध;
		हाल IWL_TOF_ENTRY_NO_RESPONSE:
			result.status = NL80211_PMSR_STATUS_FAILURE;
			result.fपंचांग.failure_reason =
				NL80211_PMSR_FTM_FAILURE_NO_RESPONSE;
			अवरोध;
		हाल IWL_TOF_ENTRY_REQUEST_REJECTED:
			result.status = NL80211_PMSR_STATUS_FAILURE;
			result.fपंचांग.failure_reason =
				NL80211_PMSR_FTM_FAILURE_PEER_BUSY;
			result.fपंचांग.busy_retry_समय = fw_ap->refusal_period;
			अवरोध;
		शेष:
			result.status = NL80211_PMSR_STATUS_FAILURE;
			result.fपंचांग.failure_reason =
				NL80211_PMSR_FTM_FAILURE_UNSPECIFIED;
			अवरोध;
		पूर्ण
		स_नकल(result.addr, fw_ap->bssid, ETH_ALEN);
		result.host_समय = iwl_mvm_fपंचांग_get_host_समय(mvm,
							     fw_ap->बारtamp);
		result.type = NL80211_PMSR_TYPE_FTM;
		result.fपंचांग.burst_index = mvm->fपंचांग_initiator.responses[peer_idx];
		mvm->fपंचांग_initiator.responses[peer_idx]++;
		result.fपंचांग.rssi_avg = fw_ap->rssi;
		result.fपंचांग.rssi_avg_valid = 1;
		result.fपंचांग.rssi_spपढ़ो = fw_ap->rssi_spपढ़ो;
		result.fपंचांग.rssi_spपढ़ो_valid = 1;
		result.fपंचांग.rtt_avg = (s32)le32_to_cpu(fw_ap->rtt);
		result.fपंचांग.rtt_avg_valid = 1;
		result.fपंचांग.rtt_variance = le32_to_cpu(fw_ap->rtt_variance);
		result.fपंचांग.rtt_variance_valid = 1;
		result.fपंचांग.rtt_spपढ़ो = le32_to_cpu(fw_ap->rtt_spपढ़ो);
		result.fपंचांग.rtt_spपढ़ो_valid = 1;

		iwl_mvm_fपंचांग_get_lci_civic(mvm, &result);

		iwl_mvm_fपंचांग_rtt_smoothing(mvm, &result);

		cfg80211_pmsr_report(mvm->fपंचांग_initiator.req_wdev,
				     mvm->fपंचांग_initiator.req,
				     &result, GFP_KERNEL);

		अगर (fw_has_api(&mvm->fw->ucode_capa,
			       IWL_UCODE_TLV_API_FTM_RTT_ACCURACY))
			IWL_DEBUG_INFO(mvm, "RTT confidence: %hhu\n",
				       fw_ap->rttConfidence);

		iwl_mvm_debug_range_resp(mvm, i, &result);
	पूर्ण

	अगर (last_in_batch) अणु
		cfg80211_pmsr_complete(mvm->fपंचांग_initiator.req_wdev,
				       mvm->fपंचांग_initiator.req,
				       GFP_KERNEL);
		iwl_mvm_fपंचांग_reset(mvm);
	पूर्ण
पूर्ण

व्योम iwl_mvm_fपंचांग_lc_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	स्थिर काष्ठा ieee80211_mgmt *mgmt = (व्योम *)pkt->data;
	माप_प्रकार len = iwl_rx_packet_payload_len(pkt);
	काष्ठा iwl_mvm_loc_entry *entry;
	स्थिर u8 *ies, *lci, *civic, *msr_ie;
	माप_प्रकार ies_len, lci_len = 0, civic_len = 0;
	माप_प्रकार baselen = IEEE80211_MIN_ACTION_SIZE +
			 माप(mgmt->u.action.u.fपंचांग);
	अटल स्थिर u8 rprt_type_lci = IEEE80211_SPCT_MSR_RPRT_TYPE_LCI;
	अटल स्थिर u8 rprt_type_civic = IEEE80211_SPCT_MSR_RPRT_TYPE_CIVIC;

	अगर (len <= baselen)
		वापस;

	lockdep_निश्चित_held(&mvm->mutex);

	ies = mgmt->u.action.u.fपंचांग.variable;
	ies_len = len - baselen;

	msr_ie = cfg80211_find_ie_match(WLAN_EID_MEASURE_REPORT, ies, ies_len,
					&rprt_type_lci, 1, 4);
	अगर (msr_ie) अणु
		lci = msr_ie + 2;
		lci_len = msr_ie[1];
	पूर्ण

	msr_ie = cfg80211_find_ie_match(WLAN_EID_MEASURE_REPORT, ies, ies_len,
					&rprt_type_civic, 1, 4);
	अगर (msr_ie) अणु
		civic = msr_ie + 2;
		civic_len = msr_ie[1];
	पूर्ण

	entry = kदो_स्मृति(माप(*entry) + lci_len + civic_len, GFP_KERNEL);
	अगर (!entry)
		वापस;

	स_नकल(entry->addr, mgmt->bssid, ETH_ALEN);

	entry->lci_len = lci_len;
	अगर (lci_len)
		स_नकल(entry->buf, lci, lci_len);

	entry->civic_len = civic_len;
	अगर (civic_len)
		स_नकल(entry->buf + lci_len, civic, civic_len);

	list_add_tail(&entry->list, &mvm->fपंचांग_initiator.loc_list);
पूर्ण
