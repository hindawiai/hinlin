<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#समावेश <net/cfg80211.h>
#समावेश <linux/etherdevice.h>
#समावेश "mvm.h"
#समावेश "constants.h"

काष्ठा iwl_mvm_pasn_sta अणु
	काष्ठा list_head list;
	काष्ठा iwl_mvm_पूर्णांक_sta पूर्णांक_sta;
	u8 addr[ETH_ALEN];
पूर्ण;

काष्ठा iwl_mvm_pasn_hltk_data अणु
	u8 *addr;
	u8 cipher;
	u8 *hltk;
पूर्ण;

अटल पूर्णांक iwl_mvm_fपंचांग_responder_set_bw_v1(काष्ठा cfg80211_chan_def *chandef,
					   u8 *bw, u8 *ctrl_ch_position)
अणु
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		*bw = IWL_TOF_BW_20_LEGACY;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20:
		*bw = IWL_TOF_BW_20_HT;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		*bw = IWL_TOF_BW_40;
		*ctrl_ch_position = iwl_mvm_get_ctrl_pos(chandef);
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		*bw = IWL_TOF_BW_80;
		*ctrl_ch_position = iwl_mvm_get_ctrl_pos(chandef);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_fपंचांग_responder_set_bw_v2(काष्ठा cfg80211_chan_def *chandef,
					   u8 *क्रमmat_bw,
					   u8 *ctrl_ch_position)
अणु
	चयन (chandef->width) अणु
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
		*ctrl_ch_position = iwl_mvm_get_ctrl_pos(chandef);
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		*क्रमmat_bw = IWL_LOCATION_FRAME_FORMAT_VHT;
		*क्रमmat_bw |= IWL_LOCATION_BW_80MHZ << LOCATION_BW_POS;
		*ctrl_ch_position = iwl_mvm_get_ctrl_pos(chandef);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
iwl_mvm_fपंचांग_responder_set_ndp(काष्ठा iwl_mvm *mvm,
			      काष्ठा iwl_tof_responder_config_cmd_v8 *cmd)
अणु
	/* Up to 2 R2I STS are allowed on the responder */
	u32 r2i_max_sts = IWL_MVM_FTM_R2I_MAX_STS < 2 ?
		IWL_MVM_FTM_R2I_MAX_STS : 1;

	cmd->r2i_ndp_params = IWL_MVM_FTM_R2I_MAX_REP |
		(r2i_max_sts << IWL_RESPONDER_STS_POS) |
		(IWL_MVM_FTM_R2I_MAX_TOTAL_LTF << IWL_RESPONDER_TOTAL_LTF_POS);
	cmd->i2r_ndp_params = IWL_MVM_FTM_I2R_MAX_REP |
		(IWL_MVM_FTM_I2R_MAX_STS << IWL_RESPONDER_STS_POS) |
		(IWL_MVM_FTM_I2R_MAX_TOTAL_LTF << IWL_RESPONDER_TOTAL_LTF_POS);
	cmd->cmd_valid_fields |=
		cpu_to_le32(IWL_TOF_RESPONDER_CMD_VALID_NDP_PARAMS);
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_responder_cmd(काष्ठा iwl_mvm *mvm,
			  काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	/*
	 * The command काष्ठाure is the same क्रम versions 6, 7 and 8 (only the
	 * field पूर्णांकerpretation is dअगरferent), so the same काष्ठा can be use
	 * क्रम all हालs.
	 */
	काष्ठा iwl_tof_responder_config_cmd_v8 cmd = अणु
		.channel_num = chandef->chan->hw_value,
		.cmd_valid_fields =
			cpu_to_le32(IWL_TOF_RESPONDER_CMD_VALID_CHAN_INFO |
				    IWL_TOF_RESPONDER_CMD_VALID_BSSID |
				    IWL_TOF_RESPONDER_CMD_VALID_STA_ID),
		.sta_id = mvmvअगर->bcast_sta.sta_id,
	पूर्ण;
	u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, LOCATION_GROUP,
					   TOF_RESPONDER_CONFIG_CMD, 6);
	पूर्णांक err;

	lockdep_निश्चित_held(&mvm->mutex);

अगर (cmd_ver == 8)
		iwl_mvm_fपंचांग_responder_set_ndp(mvm, &cmd);

	अगर (cmd_ver >= 7)
		err = iwl_mvm_fपंचांग_responder_set_bw_v2(chandef, &cmd.क्रमmat_bw,
						      &cmd.ctrl_ch_position);
	अन्यथा
		err = iwl_mvm_fपंचांग_responder_set_bw_v1(chandef, &cmd.क्रमmat_bw,
						      &cmd.ctrl_ch_position);

	अगर (err) अणु
		IWL_ERR(mvm, "Failed to set responder bandwidth\n");
		वापस err;
	पूर्ण

	स_नकल(cmd.bssid, vअगर->addr, ETH_ALEN);

	वापस iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(TOF_RESPONDER_CONFIG_CMD,
						    LOCATION_GROUP, 0),
				    0, माप(cmd), &cmd);
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_responder_dyn_cfg_v2(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_fपंचांग_responder_params *params)
अणु
	काष्ठा iwl_tof_responder_dyn_config_cmd_v2 cmd = अणु
		.lci_len = cpu_to_le32(params->lci_len + 2),
		.civic_len = cpu_to_le32(params->civicloc_len + 2),
	पूर्ण;
	u8 data[IWL_LCI_CIVIC_IE_MAX_SIZE] = अणु0पूर्ण;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(TOF_RESPONDER_DYN_CONFIG_CMD,
				 LOCATION_GROUP, 0),
		.data[0] = &cmd,
		.len[0] = माप(cmd),
		.data[1] = &data,
		/* .len[1] set later */
		/* may not be able to DMA from stack */
		.dataflags[1] = IWL_HCMD_DFL_DUP,
	पूर्ण;
	u32 aligned_lci_len = ALIGN(params->lci_len + 2, 4);
	u32 aligned_civicloc_len = ALIGN(params->civicloc_len + 2, 4);
	u8 *pos = data;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (aligned_lci_len + aligned_civicloc_len > माप(data)) अणु
		IWL_ERR(mvm, "LCI/civicloc data too big (%zd + %zd)\n",
			params->lci_len, params->civicloc_len);
		वापस -ENOBUFS;
	पूर्ण

	pos[0] = WLAN_EID_MEASURE_REPORT;
	pos[1] = params->lci_len;
	स_नकल(pos + 2, params->lci, params->lci_len);

	pos += aligned_lci_len;
	pos[0] = WLAN_EID_MEASURE_REPORT;
	pos[1] = params->civicloc_len;
	स_नकल(pos + 2, params->civicloc, params->civicloc_len);

	hcmd.len[1] = aligned_lci_len + aligned_civicloc_len;

	वापस iwl_mvm_send_cmd(mvm, &hcmd);
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_responder_dyn_cfg_v3(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_fपंचांग_responder_params *params,
				 काष्ठा iwl_mvm_pasn_hltk_data *hltk_data)
अणु
	काष्ठा iwl_tof_responder_dyn_config_cmd cmd;
	काष्ठा iwl_host_cmd hcmd = अणु
		.id = iwl_cmd_id(TOF_RESPONDER_DYN_CONFIG_CMD,
				 LOCATION_GROUP, 0),
		.data[0] = &cmd,
		.len[0] = माप(cmd),
		/* may not be able to DMA from stack */
		.dataflags[0] = IWL_HCMD_DFL_DUP,
	पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	cmd.valid_flags = 0;

	अगर (params) अणु
		अगर (params->lci_len + 2 > माप(cmd.lci_buf) ||
		    params->civicloc_len + 2 > माप(cmd.civic_buf)) अणु
			IWL_ERR(mvm,
				"LCI/civic data too big (lci=%zd, civic=%zd)\n",
				params->lci_len, params->civicloc_len);
			वापस -ENOBUFS;
		पूर्ण

		cmd.lci_buf[0] = WLAN_EID_MEASURE_REPORT;
		cmd.lci_buf[1] = params->lci_len;
		स_नकल(cmd.lci_buf + 2, params->lci, params->lci_len);
		cmd.lci_len = params->lci_len + 2;

		cmd.civic_buf[0] = WLAN_EID_MEASURE_REPORT;
		cmd.civic_buf[1] = params->civicloc_len;
		स_नकल(cmd.civic_buf + 2, params->civicloc,
		       params->civicloc_len);
		cmd.civic_len = params->civicloc_len + 2;

		cmd.valid_flags |= IWL_RESPONDER_DYN_CFG_VALID_LCI |
			IWL_RESPONDER_DYN_CFG_VALID_CIVIC;
	पूर्ण

	अगर (hltk_data) अणु
		अगर (hltk_data->cipher > IWL_LOCATION_CIPHER_GCMP_256) अणु
			IWL_ERR(mvm, "invalid cipher: %u\n",
				hltk_data->cipher);
			वापस -EINVAL;
		पूर्ण

		cmd.cipher = hltk_data->cipher;
		स_नकल(cmd.addr, hltk_data->addr, माप(cmd.addr));
		स_नकल(cmd.hltk_buf, hltk_data->hltk, माप(cmd.hltk_buf));
		cmd.valid_flags |= IWL_RESPONDER_DYN_CFG_VALID_PASN_STA;
	पूर्ण

	वापस iwl_mvm_send_cmd(mvm, &hcmd);
पूर्ण

अटल पूर्णांक
iwl_mvm_fपंचांग_responder_dyn_cfg_cmd(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_fपंचांग_responder_params *params)
अणु
	पूर्णांक ret;
	u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, LOCATION_GROUP,
					   TOF_RESPONDER_DYN_CONFIG_CMD, 2);

	चयन (cmd_ver) अणु
	हाल 2:
		ret = iwl_mvm_fपंचांग_responder_dyn_cfg_v2(mvm, vअगर,
						       params);
		अवरोध;
	हाल 3:
		ret = iwl_mvm_fपंचांग_responder_dyn_cfg_v3(mvm, vअगर,
						       params, शून्य);
		अवरोध;
	शेष:
		IWL_ERR(mvm, "Unsupported DYN_CONFIG_CMD version %u\n",
			cmd_ver);
		ret = -ENOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_resp_del_pasn_sta(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा iwl_mvm_pasn_sta *sta)
अणु
	list_del(&sta->list);
	iwl_mvm_rm_sta_id(mvm, vअगर, sta->पूर्णांक_sta.sta_id);
	iwl_mvm_dealloc_पूर्णांक_sta(mvm, &sta->पूर्णांक_sta);
	kमुक्त(sta);
पूर्ण

पूर्णांक iwl_mvm_fपंचांग_respoder_add_pasn_sta(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_vअगर *vअगर,
				      u8 *addr, u32 cipher, u8 *tk, u32 tk_len,
				      u8 *hltk, u32 hltk_len)
अणु
	पूर्णांक ret;
	काष्ठा iwl_mvm_pasn_sta *sta = शून्य;
	काष्ठा iwl_mvm_pasn_hltk_data hltk_data = अणु
		.addr = addr,
		.hltk = hltk,
	पूर्ण;
	u8 cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw, LOCATION_GROUP,
					   TOF_RESPONDER_DYN_CONFIG_CMD, 2);

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (cmd_ver < 3) अणु
		IWL_ERR(mvm, "Adding PASN station not supported by FW\n");
		वापस -ENOTSUPP;
	पूर्ण

	hltk_data.cipher = iwl_mvm_cipher_to_location_cipher(cipher);
	अगर (hltk_data.cipher == IWL_LOCATION_CIPHER_INVALID) अणु
		IWL_ERR(mvm, "invalid cipher: %u\n", cipher);
		वापस -EINVAL;
	पूर्ण

	अगर (tk && tk_len) अणु
		sta = kzalloc(माप(*sta), GFP_KERNEL);
		अगर (!sta)
			वापस -ENOBUFS;

		ret = iwl_mvm_add_pasn_sta(mvm, vअगर, &sta->पूर्णांक_sta, addr,
					   cipher, tk, tk_len);
		अगर (ret) अणु
			kमुक्त(sta);
			वापस ret;
		पूर्ण

		स_नकल(sta->addr, addr, ETH_ALEN);
		list_add_tail(&sta->list, &mvm->resp_pasn_list);
	पूर्ण

	ret = iwl_mvm_fपंचांग_responder_dyn_cfg_v3(mvm, vअगर, शून्य, &hltk_data);
	अगर (ret && sta)
		iwl_mvm_resp_del_pasn_sta(mvm, vअगर, sta);

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_fपंचांग_resp_हटाओ_pasn_sta(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_vअगर *vअगर, u8 *addr)
अणु
	काष्ठा iwl_mvm_pasn_sta *sta, *prev;

	lockdep_निश्चित_held(&mvm->mutex);

	list_क्रम_each_entry_safe(sta, prev, &mvm->resp_pasn_list, list) अणु
		अगर (!स_भेद(sta->addr, addr, ETH_ALEN)) अणु
			iwl_mvm_resp_del_pasn_sta(mvm, vअगर, sta);
			वापस 0;
		पूर्ण
	पूर्ण

	IWL_ERR(mvm, "FTM: PASN station %pM not found\n", addr);
	वापस -EINVAL;
पूर्ण

पूर्णांक iwl_mvm_fपंचांग_start_responder(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा ieee80211_fपंचांग_responder_params *params;
	काष्ठा ieee80211_chanctx_conf ctx, *pctx;
	u16 *phy_ctxt_id;
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt;
	पूर्णांक ret;

	params = vअगर->bss_conf.fपंचांगr_params;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON_ONCE(!vअगर->bss_conf.fपंचांग_responder))
		वापस -EINVAL;

	अगर (vअगर->p2p || vअगर->type != NL80211_IFTYPE_AP ||
	    !mvmvअगर->ap_ibss_active) अणु
		IWL_ERR(mvm, "Cannot start responder, not in AP mode\n");
		वापस -EIO;
	पूर्ण

	rcu_पढ़ो_lock();
	pctx = rcu_dereference(vअगर->chanctx_conf);
	/* Copy the ctx to unlock the rcu and send the phy ctxt. We करोn't care
	 * about changes in the ctx after releasing the lock because the driver
	 * is still रक्षित by the mutex. */
	ctx = *pctx;
	phy_ctxt_id  = (u16 *)pctx->drv_priv;
	rcu_पढ़ो_unlock();

	phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	ret = iwl_mvm_phy_ctxt_changed(mvm, phy_ctxt, &ctx.def,
				       ctx.rx_chains_अटल,
				       ctx.rx_chains_dynamic);
	अगर (ret)
		वापस ret;

	ret = iwl_mvm_fपंचांग_responder_cmd(mvm, vअगर, &ctx.def);
	अगर (ret)
		वापस ret;

	अगर (params)
		ret = iwl_mvm_fपंचांग_responder_dyn_cfg_cmd(mvm, vअगर, params);

	वापस ret;
पूर्ण

व्योम iwl_mvm_fपंचांग_responder_clear(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_pasn_sta *sta, *prev;

	lockdep_निश्चित_held(&mvm->mutex);

	list_क्रम_each_entry_safe(sta, prev, &mvm->resp_pasn_list, list)
		iwl_mvm_resp_del_pasn_sta(mvm, vअगर, sta);
पूर्ण

व्योम iwl_mvm_fपंचांग_restart_responder(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (!vअगर->bss_conf.fपंचांग_responder)
		वापस;

	iwl_mvm_fपंचांग_responder_clear(mvm, vअगर);
	iwl_mvm_fपंचांग_start_responder(mvm, vअगर);
पूर्ण

व्योम iwl_mvm_fपंचांग_responder_stats(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_fपंचांग_responder_stats *resp = (व्योम *)pkt->data;
	काष्ठा cfg80211_fपंचांग_responder_stats *stats = &mvm->fपंचांग_resp_stats;
	u32 flags = le32_to_cpu(resp->flags);

	अगर (resp->success_fपंचांग == resp->fपंचांग_per_burst)
		stats->success_num++;
	अन्यथा अगर (resp->success_fपंचांग >= 2)
		stats->partial_num++;
	अन्यथा
		stats->failed_num++;

	अगर ((flags & FTM_RESP_STAT_ASAP_REQ) &&
	    (flags & FTM_RESP_STAT_ASAP_RESP))
		stats->asap_num++;

	अगर (flags & FTM_RESP_STAT_NON_ASAP_RESP)
		stats->non_asap_num++;

	stats->total_duration_ms += le32_to_cpu(resp->duration) / USEC_PER_MSEC;

	अगर (flags & FTM_RESP_STAT_TRIGGER_UNKNOWN)
		stats->unknown_triggers_num++;

	अगर (flags & FTM_RESP_STAT_DUP)
		stats->reschedule_requests_num++;

	अगर (flags & FTM_RESP_STAT_NON_ASAP_OUT_WIN)
		stats->out_of_winकरोw_triggers_num++;
पूर्ण
