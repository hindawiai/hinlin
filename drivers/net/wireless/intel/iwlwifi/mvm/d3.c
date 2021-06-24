<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/fs.h>
#समावेश <net/cfg80211.h>
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>
#समावेश <net/addrconf.h>
#समावेश "iwl-modparams.h"
#समावेश "fw-api.h"
#समावेश "mvm.h"
#समावेश "fw/img.h"

व्योम iwl_mvm_set_rekey_data(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	mutex_lock(&mvm->mutex);

	mvmvअगर->rekey_data.kek_len = data->kek_len;
	mvmvअगर->rekey_data.kck_len = data->kck_len;
	स_नकल(mvmvअगर->rekey_data.kek, data->kek, data->kek_len);
	स_नकल(mvmvअगर->rekey_data.kck, data->kck, data->kck_len);
	mvmvअगर->rekey_data.akm = data->akm & 0xFF;
	mvmvअगर->rekey_data.replay_ctr =
		cpu_to_le64(be64_to_cpup((__be64 *)data->replay_ctr));
	mvmvअगर->rekey_data.valid = true;

	mutex_unlock(&mvm->mutex);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
व्योम iwl_mvm_ipv6_addr_change(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा inet6_dev *idev)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा inet6_अगरaddr *अगरa;
	पूर्णांक idx = 0;

	स_रखो(mvmvअगर->tentative_addrs, 0, माप(mvmvअगर->tentative_addrs));

	पढ़ो_lock_bh(&idev->lock);
	list_क्रम_each_entry(अगरa, &idev->addr_list, अगर_list) अणु
		mvmvअगर->target_ipv6_addrs[idx] = अगरa->addr;
		अगर (अगरa->flags & IFA_F_TENTATIVE)
			__set_bit(idx, mvmvअगर->tentative_addrs);
		idx++;
		अगर (idx >= IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_MAX)
			अवरोध;
	पूर्ण
	पढ़ो_unlock_bh(&idev->lock);

	mvmvअगर->num_target_ipv6_addrs = idx;
पूर्ण
#पूर्ण_अगर

व्योम iwl_mvm_set_शेष_unicast_key(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर, पूर्णांक idx)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	mvmvअगर->tx_key_idx = idx;
पूर्ण

अटल व्योम iwl_mvm_convert_p1k(u16 *p1k, __le16 *out)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IWL_P1K_SIZE; i++)
		out[i] = cpu_to_le16(p1k[i]);
पूर्ण

अटल स्थिर u8 *iwl_mvm_find_max_pn(काष्ठा ieee80211_key_conf *key,
				     काष्ठा iwl_mvm_key_pn *ptk_pn,
				     काष्ठा ieee80211_key_seq *seq,
				     पूर्णांक tid, पूर्णांक queues)
अणु
	स्थिर u8 *ret = seq->ccmp.pn;
	पूर्णांक i;

	/* get the PN from mac80211, used on the शेष queue */
	ieee80211_get_key_rx_seq(key, tid, seq);

	/* and use the पूर्णांकernal data क्रम the other queues */
	क्रम (i = 1; i < queues; i++) अणु
		स्थिर u8 *पंचांगp = ptk_pn->q[i].pn[tid];

		अगर (स_भेद(ret, पंचांगp, IEEE80211_CCMP_PN_LEN) <= 0)
			ret = पंचांगp;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा wowlan_key_data अणु
	काष्ठा iwl_wowlan_rsc_tsc_params_cmd *rsc_tsc;
	काष्ठा iwl_wowlan_tkip_params_cmd *tkip;
	काष्ठा iwl_wowlan_kek_kck_material_cmd_v3 *kek_kck_cmd;
	bool error, use_rsc_tsc, use_tkip, configure_keys;
	पूर्णांक wep_key_idx;
पूर्ण;

अटल व्योम iwl_mvm_wowlan_program_keys(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_sta *sta,
					काष्ठा ieee80211_key_conf *key,
					व्योम *_data)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा wowlan_key_data *data = _data;
	काष्ठा aes_sc *aes_sc, *aes_tx_sc = शून्य;
	काष्ठा tkip_sc *tkip_sc, *tkip_tx_sc = शून्य;
	काष्ठा iwl_p1k_cache *rx_p1ks;
	u8 *rx_mic_key;
	काष्ठा ieee80211_key_seq seq;
	u32 cur_rx_iv32 = 0;
	u16 p1k[IWL_P1K_SIZE];
	पूर्णांक ret, i;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104: अणु /* hack it क्रम now */
		काष्ठा अणु
			काष्ठा iwl_mvm_wep_key_cmd wep_key_cmd;
			काष्ठा iwl_mvm_wep_key wep_key;
		पूर्ण __packed wkc = अणु
			.wep_key_cmd.mac_id_n_color =
				cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
								mvmvअगर->color)),
			.wep_key_cmd.num_keys = 1,
			/* firmware sets STA_KEY_FLG_WEP_13BYTES */
			.wep_key_cmd.decryption_type = STA_KEY_FLG_WEP,
			.wep_key.key_index = key->keyidx,
			.wep_key.key_size = key->keylen,
		पूर्ण;

		/*
		 * This will fail -- the key functions करोn't set support
		 * pairwise WEP keys. However, that's better than silently
		 * failing WoWLAN. Or maybe not?
		 */
		अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
			अवरोध;

		स_नकल(&wkc.wep_key.key[3], key->key, key->keylen);
		अगर (key->keyidx == mvmvअगर->tx_key_idx) अणु
			/* TX key must be at offset 0 */
			wkc.wep_key.key_offset = 0;
		पूर्ण अन्यथा अणु
			/* others start at 1 */
			data->wep_key_idx++;
			wkc.wep_key.key_offset = data->wep_key_idx;
		पूर्ण

		अगर (data->configure_keys) अणु
			mutex_lock(&mvm->mutex);
			ret = iwl_mvm_send_cmd_pdu(mvm, WEP_KEY, 0,
						   माप(wkc), &wkc);
			data->error = ret != 0;

			mvm->ptk_ivlen = key->iv_len;
			mvm->ptk_icvlen = key->icv_len;
			mvm->gtk_ivlen = key->iv_len;
			mvm->gtk_icvlen = key->icv_len;
			mutex_unlock(&mvm->mutex);
		पूर्ण

		/* करोn't upload key again */
		वापस;
	पूर्ण
	शेष:
		data->error = true;
		वापस;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
		data->kek_kck_cmd->igtk_cipher = cpu_to_le32(STA_KEY_FLG_GCMP);
		वापस;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
		data->kek_kck_cmd->igtk_cipher = cpu_to_le32(STA_KEY_FLG_CCM);
		/*
		 * Ignore CMAC keys -- the WoWLAN firmware करोesn't support them
		 * but we also shouldn't पात suspend due to that. It करोes have
		 * support क्रम the IGTK key renewal, but करोesn't really use the
		 * IGTK क्रम anything. This means we could spuriously wake up or
		 * be deauthenticated, but that was considered acceptable.
		 */
		वापस;
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (sta) अणु
			u64 pn64;

			tkip_sc =
			   data->rsc_tsc->params.all_tsc_rsc.tkip.unicast_rsc;
			tkip_tx_sc =
				&data->rsc_tsc->params.all_tsc_rsc.tkip.tsc;

			rx_p1ks = data->tkip->rx_uni;

			pn64 = atomic64_पढ़ो(&key->tx_pn);
			tkip_tx_sc->iv16 = cpu_to_le16(TKIP_PN_TO_IV16(pn64));
			tkip_tx_sc->iv32 = cpu_to_le32(TKIP_PN_TO_IV32(pn64));

			ieee80211_get_tkip_p1k_iv(key, TKIP_PN_TO_IV32(pn64),
						  p1k);
			iwl_mvm_convert_p1k(p1k, data->tkip->tx.p1k);

			स_नकल(data->tkip->mic_keys.tx,
			       &key->key[NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY],
			       IWL_MIC_KEY_SIZE);

			rx_mic_key = data->tkip->mic_keys.rx_unicast;
		पूर्ण अन्यथा अणु
			tkip_sc =
			  data->rsc_tsc->params.all_tsc_rsc.tkip.multicast_rsc;
			rx_p1ks = data->tkip->rx_multi;
			rx_mic_key = data->tkip->mic_keys.rx_mcast;
			data->kek_kck_cmd->gtk_cipher =
				cpu_to_le32(STA_KEY_FLG_TKIP);
		पूर्ण

		/*
		 * For non-QoS this relies on the fact that both the uCode and
		 * mac80211 use TID 0 (as they need to to aव्योम replay attacks)
		 * क्रम checking the IV in the frames.
		 */
		क्रम (i = 0; i < IWL_NUM_RSC; i++) अणु
			ieee80211_get_key_rx_seq(key, i, &seq);
			tkip_sc[i].iv16 = cpu_to_le16(seq.tkip.iv16);
			tkip_sc[i].iv32 = cpu_to_le32(seq.tkip.iv32);
			/* wrapping isn't allowed, AP must rekey */
			अगर (seq.tkip.iv32 > cur_rx_iv32)
				cur_rx_iv32 = seq.tkip.iv32;
		पूर्ण

		ieee80211_get_tkip_rx_p1k(key, vअगर->bss_conf.bssid,
					  cur_rx_iv32, p1k);
		iwl_mvm_convert_p1k(p1k, rx_p1ks[0].p1k);
		ieee80211_get_tkip_rx_p1k(key, vअगर->bss_conf.bssid,
					  cur_rx_iv32 + 1, p1k);
		iwl_mvm_convert_p1k(p1k, rx_p1ks[1].p1k);

		स_नकल(rx_mic_key,
		       &key->key[NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY],
		       IWL_MIC_KEY_SIZE);

		data->use_tkip = true;
		data->use_rsc_tsc = true;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		अगर (sta) अणु
			u64 pn64;

			aes_sc =
			   data->rsc_tsc->params.all_tsc_rsc.aes.unicast_rsc;
			aes_tx_sc =
				&data->rsc_tsc->params.all_tsc_rsc.aes.tsc;

			pn64 = atomic64_पढ़ो(&key->tx_pn);
			aes_tx_sc->pn = cpu_to_le64(pn64);
		पूर्ण अन्यथा अणु
			aes_sc =
			   data->rsc_tsc->params.all_tsc_rsc.aes.multicast_rsc;
			data->kek_kck_cmd->gtk_cipher =
				key->cipher == WLAN_CIPHER_SUITE_CCMP ?
				cpu_to_le32(STA_KEY_FLG_CCM) :
				cpu_to_le32(STA_KEY_FLG_GCMP);
		पूर्ण

		/*
		 * For non-QoS this relies on the fact that both the uCode and
		 * mac80211/our RX code use TID 0 क्रम checking the PN.
		 */
		अगर (sta && iwl_mvm_has_new_rx_api(mvm)) अणु
			काष्ठा iwl_mvm_sta *mvmsta;
			काष्ठा iwl_mvm_key_pn *ptk_pn;
			स्थिर u8 *pn;

			mvmsta = iwl_mvm_sta_from_mac80211(sta);
			rcu_पढ़ो_lock();
			ptk_pn = rcu_dereference(mvmsta->ptk_pn[key->keyidx]);
			अगर (WARN_ON(!ptk_pn)) अणु
				rcu_पढ़ो_unlock();
				अवरोध;
			पूर्ण

			क्रम (i = 0; i < IWL_MAX_TID_COUNT; i++) अणु
				pn = iwl_mvm_find_max_pn(key, ptk_pn, &seq, i,
						mvm->trans->num_rx_queues);
				aes_sc[i].pn = cpu_to_le64((u64)pn[5] |
							   ((u64)pn[4] << 8) |
							   ((u64)pn[3] << 16) |
							   ((u64)pn[2] << 24) |
							   ((u64)pn[1] << 32) |
							   ((u64)pn[0] << 40));
			पूर्ण

			rcu_पढ़ो_unlock();
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < IWL_NUM_RSC; i++) अणु
				u8 *pn = seq.ccmp.pn;

				ieee80211_get_key_rx_seq(key, i, &seq);
				aes_sc[i].pn = cpu_to_le64((u64)pn[5] |
							   ((u64)pn[4] << 8) |
							   ((u64)pn[3] << 16) |
							   ((u64)pn[2] << 24) |
							   ((u64)pn[1] << 32) |
							   ((u64)pn[0] << 40));
			पूर्ण
		पूर्ण
		data->use_rsc_tsc = true;
		अवरोध;
	पूर्ण

	IWL_DEBUG_WOWLAN(mvm, "GTK cipher %d\n", data->kek_kck_cmd->gtk_cipher);

	अगर (data->configure_keys) अणु
		mutex_lock(&mvm->mutex);
		/*
		 * The D3 firmware hardcodes the key offset 0 as the key it
		 * uses to transmit packets to the AP, i.e. the PTK.
		 */
		अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
			mvm->ptk_ivlen = key->iv_len;
			mvm->ptk_icvlen = key->icv_len;
			ret = iwl_mvm_set_sta_key(mvm, vअगर, sta, key, 0);
		पूर्ण अन्यथा अणु
			/*
			 * firmware only supports TSC/RSC क्रम a single key,
			 * so अगर there are multiple keep overwriting them
			 * with new ones -- this relies on mac80211 करोing
			 * list_add_tail().
			 */
			mvm->gtk_ivlen = key->iv_len;
			mvm->gtk_icvlen = key->icv_len;
			ret = iwl_mvm_set_sta_key(mvm, vअगर, sta, key, 1);
		पूर्ण
		mutex_unlock(&mvm->mutex);
		data->error = ret != 0;
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_mvm_send_patterns_v1(काष्ठा iwl_mvm *mvm,
				    काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा iwl_wowlan_patterns_cmd_v1 *pattern_cmd;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = WOWLAN_PATTERNS,
		.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
	पूर्ण;
	पूर्णांक i, err;

	अगर (!wowlan->n_patterns)
		वापस 0;

	cmd.len[0] = काष्ठा_size(pattern_cmd, patterns, wowlan->n_patterns);

	pattern_cmd = kदो_स्मृति(cmd.len[0], GFP_KERNEL);
	अगर (!pattern_cmd)
		वापस -ENOMEM;

	pattern_cmd->n_patterns = cpu_to_le32(wowlan->n_patterns);

	क्रम (i = 0; i < wowlan->n_patterns; i++) अणु
		पूर्णांक mask_len = DIV_ROUND_UP(wowlan->patterns[i].pattern_len, 8);

		स_नकल(&pattern_cmd->patterns[i].mask,
		       wowlan->patterns[i].mask, mask_len);
		स_नकल(&pattern_cmd->patterns[i].pattern,
		       wowlan->patterns[i].pattern,
		       wowlan->patterns[i].pattern_len);
		pattern_cmd->patterns[i].mask_size = mask_len;
		pattern_cmd->patterns[i].pattern_size =
			wowlan->patterns[i].pattern_len;
	पूर्ण

	cmd.data[0] = pattern_cmd;
	err = iwl_mvm_send_cmd(mvm, &cmd);
	kमुक्त(pattern_cmd);
	वापस err;
पूर्ण

अटल पूर्णांक iwl_mvm_send_patterns(काष्ठा iwl_mvm *mvm,
				 काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा iwl_wowlan_patterns_cmd *pattern_cmd;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = WOWLAN_PATTERNS,
		.dataflags[0] = IWL_HCMD_DFL_NOCOPY,
	पूर्ण;
	पूर्णांक i, err;

	अगर (!wowlan->n_patterns)
		वापस 0;

	cmd.len[0] = माप(*pattern_cmd) +
		wowlan->n_patterns * माप(काष्ठा iwl_wowlan_pattern_v2);

	pattern_cmd = kदो_स्मृति(cmd.len[0], GFP_KERNEL);
	अगर (!pattern_cmd)
		वापस -ENOMEM;

	pattern_cmd->n_patterns = cpu_to_le32(wowlan->n_patterns);

	क्रम (i = 0; i < wowlan->n_patterns; i++) अणु
		पूर्णांक mask_len = DIV_ROUND_UP(wowlan->patterns[i].pattern_len, 8);

		pattern_cmd->patterns[i].pattern_type =
			WOWLAN_PATTERN_TYPE_BITMASK;

		स_नकल(&pattern_cmd->patterns[i].u.biपंचांगask.mask,
		       wowlan->patterns[i].mask, mask_len);
		स_नकल(&pattern_cmd->patterns[i].u.biपंचांगask.pattern,
		       wowlan->patterns[i].pattern,
		       wowlan->patterns[i].pattern_len);
		pattern_cmd->patterns[i].u.biपंचांगask.mask_size = mask_len;
		pattern_cmd->patterns[i].u.biपंचांगask.pattern_size =
			wowlan->patterns[i].pattern_len;
	पूर्ण

	cmd.data[0] = pattern_cmd;
	err = iwl_mvm_send_cmd(mvm, &cmd);
	kमुक्त(pattern_cmd);
	वापस err;
पूर्ण

अटल पूर्णांक iwl_mvm_d3_reprogram(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *ap_sta)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा ieee80211_chanctx_conf *ctx;
	u8 chains_अटल, chains_dynamic;
	काष्ठा cfg80211_chan_def chandef;
	पूर्णांक ret, i;
	काष्ठा iwl_binding_cmd_v1 binding_cmd = अणुपूर्ण;
	काष्ठा iwl_समय_quota_cmd quota_cmd = अणुपूर्ण;
	काष्ठा iwl_समय_quota_data *quota;
	u32 status;

	अगर (WARN_ON_ONCE(iwl_mvm_is_cdb_supported(mvm)))
		वापस -EINVAL;

	/* add back the PHY */
	अगर (WARN_ON(!mvmvअगर->phy_ctxt))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	ctx = rcu_dereference(vअगर->chanctx_conf);
	अगर (WARN_ON(!ctx)) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण
	chandef = ctx->def;
	chains_अटल = ctx->rx_chains_अटल;
	chains_dynamic = ctx->rx_chains_dynamic;
	rcu_पढ़ो_unlock();

	ret = iwl_mvm_phy_ctxt_add(mvm, mvmvअगर->phy_ctxt, &chandef,
				   chains_अटल, chains_dynamic);
	अगर (ret)
		वापस ret;

	/* add back the MAC */
	mvmvअगर->uploaded = false;

	अगर (WARN_ON(!vअगर->bss_conf.assoc))
		वापस -EINVAL;

	ret = iwl_mvm_mac_ctxt_add(mvm, vअगर);
	अगर (ret)
		वापस ret;

	/* add back binding - XXX refactor? */
	binding_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->phy_ctxt->id,
						mvmvअगर->phy_ctxt->color));
	binding_cmd.action = cpu_to_le32(FW_CTXT_ACTION_ADD);
	binding_cmd.phy =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->phy_ctxt->id,
						mvmvअगर->phy_ctxt->color));
	binding_cmd.macs[0] = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							      mvmvअगर->color));
	क्रम (i = 1; i < MAX_MACS_IN_BINDING; i++)
		binding_cmd.macs[i] = cpu_to_le32(FW_CTXT_INVALID);

	status = 0;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, BINDING_CONTEXT_CMD,
					  IWL_BINDING_CMD_SIZE_V1, &binding_cmd,
					  &status);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to add binding: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (status) अणु
		IWL_ERR(mvm, "Binding command failed: %u\n", status);
		वापस -EIO;
	पूर्ण

	ret = iwl_mvm_sta_send_to_fw(mvm, ap_sta, false, 0);
	अगर (ret)
		वापस ret;
	rcu_assign_poपूर्णांकer(mvm->fw_id_to_mac_id[mvmvअगर->ap_sta_id], ap_sta);

	ret = iwl_mvm_mac_ctxt_changed(mvm, vअगर, false, शून्य);
	अगर (ret)
		वापस ret;

	/* and some quota */
	quota = iwl_mvm_quota_cmd_get_quota(mvm, &quota_cmd, 0);
	quota->id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->phy_ctxt->id,
						mvmvअगर->phy_ctxt->color));
	quota->quota = cpu_to_le32(IWL_MVM_MAX_QUOTA);
	quota->max_duration = cpu_to_le32(IWL_MVM_MAX_QUOTA);

	क्रम (i = 1; i < MAX_BINDINGS; i++) अणु
		quota = iwl_mvm_quota_cmd_get_quota(mvm, &quota_cmd, i);
		quota->id_and_color = cpu_to_le32(FW_CTXT_INVALID);
	पूर्ण

	ret = iwl_mvm_send_cmd_pdu(mvm, TIME_QUOTA_CMD, 0,
				   iwl_mvm_quota_cmd_size(mvm), &quota_cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send quota: %d\n", ret);

	अगर (iwl_mvm_is_lar_supported(mvm) && iwl_mvm_init_fw_regd(mvm))
		IWL_ERR(mvm, "Failed to initialize D3 LAR information\n");

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_get_last_nonqos_seq(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_nonqos_seq_query_cmd query_cmd = अणु
		.get_set_flag = cpu_to_le32(IWL_NONQOS_SEQ_GET),
		.mac_id_n_color =
			cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							mvmvअगर->color)),
	पूर्ण;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = NON_QOS_TX_COUNTER_CMD,
		.flags = CMD_WANT_SKB,
	पूर्ण;
	पूर्णांक err;
	u32 size;

	cmd.data[0] = &query_cmd;
	cmd.len[0] = माप(query_cmd);

	err = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (err)
		वापस err;

	size = iwl_rx_packet_payload_len(cmd.resp_pkt);
	अगर (size < माप(__le16)) अणु
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = le16_to_cpup((__le16 *)cmd.resp_pkt->data);
		/* firmware वापसs next, not last-used seqno */
		err = (u16) (err - 0x10);
	पूर्ण

	iwl_मुक्त_resp(&cmd);
	वापस err;
पूर्ण

व्योम iwl_mvm_set_last_nonqos_seq(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_nonqos_seq_query_cmd query_cmd = अणु
		.get_set_flag = cpu_to_le32(IWL_NONQOS_SEQ_SET),
		.mac_id_n_color =
			cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							mvmvअगर->color)),
		.value = cpu_to_le16(mvmvअगर->seqno),
	पूर्ण;

	/* वापस अगर called during restart, not resume from D3 */
	अगर (!mvmvअगर->seqno_valid)
		वापस;

	mvmvअगर->seqno_valid = false;

	अगर (iwl_mvm_send_cmd_pdu(mvm, NON_QOS_TX_COUNTER_CMD, 0,
				 माप(query_cmd), &query_cmd))
		IWL_ERR(mvm, "failed to set non-QoS seqno\n");
पूर्ण

अटल पूर्णांक iwl_mvm_चयन_to_d3(काष्ठा iwl_mvm *mvm)
अणु
	iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_REGULAR, true);

	iwl_mvm_stop_device(mvm);
	/*
	 * Set the HW restart bit -- this is mostly true as we're
	 * going to load new firmware and reprogram that, though
	 * the reprogramming is going to be manual to aव्योम adding
	 * all the MACs that aren't support.
	 * We करोn't have to clear up everything though because the
	 * reprogramming is manual. When we resume, we'll actually
	 * go through a proper restart sequence again to चयन
	 * back to the runसमय firmware image.
	 */
	set_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);

	/* the fw is reset, so all the keys are cleared */
	स_रखो(mvm->fw_key_table, 0, माप(mvm->fw_key_table));

	mvm->ptk_ivlen = 0;
	mvm->ptk_icvlen = 0;
	mvm->ptk_ivlen = 0;
	mvm->ptk_icvlen = 0;

	वापस iwl_mvm_load_d3_fw(mvm);
पूर्ण

अटल पूर्णांक
iwl_mvm_get_wowlan_config(काष्ठा iwl_mvm *mvm,
			  काष्ठा cfg80211_wowlan *wowlan,
			  काष्ठा iwl_wowlan_config_cmd *wowlan_config_cmd,
			  काष्ठा ieee80211_vअगर *vअगर, काष्ठा iwl_mvm_vअगर *mvmvअगर,
			  काष्ठा ieee80211_sta *ap_sta)
अणु
	पूर्णांक ret;
	काष्ठा iwl_mvm_sta *mvm_ap_sta = iwl_mvm_sta_from_mac80211(ap_sta);

	/* TODO: wowlan_config_cmd->wowlan_ba_tearकरोwn_tids */

	wowlan_config_cmd->is_11n_connection =
					ap_sta->ht_cap.ht_supported;
	wowlan_config_cmd->flags = ENABLE_L3_FILTERING |
		ENABLE_NBNS_FILTERING | ENABLE_DHCP_FILTERING;

	/* Query the last used seqno and set it */
	ret = iwl_mvm_get_last_nonqos_seq(mvm, vअगर);
	अगर (ret < 0)
		वापस ret;

	wowlan_config_cmd->non_qos_seq = cpu_to_le16(ret);

	iwl_mvm_set_wowlan_qos_seq(mvm_ap_sta, wowlan_config_cmd);

	अगर (wowlan->disconnect)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_BEACON_MISS |
				    IWL_WOWLAN_WAKEUP_LINK_CHANGE);
	अगर (wowlan->magic_pkt)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_MAGIC_PACKET);
	अगर (wowlan->gtk_rekey_failure)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_GTK_REKEY_FAIL);
	अगर (wowlan->eap_identity_req)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_EAP_IDENT_REQ);
	अगर (wowlan->four_way_handshake)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_4WAY_HANDSHAKE);
	अगर (wowlan->n_patterns)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_PATTERN_MATCH);

	अगर (wowlan->rfसमाप्त_release)
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_RF_KILL_DEASSERT);

	अगर (wowlan->tcp) अणु
		/*
		 * Set the "link change" (really "link lost") flag as well
		 * since that implies losing the TCP connection.
		 */
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_REMOTE_LINK_LOSS |
				    IWL_WOWLAN_WAKEUP_REMOTE_SIGNATURE_TABLE |
				    IWL_WOWLAN_WAKEUP_REMOTE_WAKEUP_PACKET |
				    IWL_WOWLAN_WAKEUP_LINK_CHANGE);
	पूर्ण

	अगर (wowlan->any) अणु
		wowlan_config_cmd->wakeup_filter |=
			cpu_to_le32(IWL_WOWLAN_WAKEUP_BEACON_MISS |
				    IWL_WOWLAN_WAKEUP_LINK_CHANGE |
				    IWL_WOWLAN_WAKEUP_RX_FRAME |
				    IWL_WOWLAN_WAKEUP_BCN_FILTERING);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_wowlan_config_key_params(काष्ठा iwl_mvm *mvm,
					    काष्ठा ieee80211_vअगर *vअगर,
					    u32 cmd_flags)
अणु
	काष्ठा iwl_wowlan_kek_kck_material_cmd_v3 kek_kck_cmd = अणुपूर्ण;
	काष्ठा iwl_wowlan_tkip_params_cmd tkip_cmd = अणुपूर्ण;
	bool unअगरied = fw_has_capa(&mvm->fw->ucode_capa,
				   IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);
	काष्ठा wowlan_key_data key_data = अणु
		.configure_keys = !unअगरied,
		.use_rsc_tsc = false,
		.tkip = &tkip_cmd,
		.use_tkip = false,
		.kek_kck_cmd = &kek_kck_cmd,
	पूर्ण;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;
	u8 cmd_ver;
	माप_प्रकार cmd_size;

	key_data.rsc_tsc = kzalloc(माप(*key_data.rsc_tsc), GFP_KERNEL);
	अगर (!key_data.rsc_tsc)
		वापस -ENOMEM;

	/*
	 * अगर we have to configure keys, call ieee80211_iter_keys(),
	 * as we need non-atomic context in order to take the
	 * required locks.
	 */
	/*
	 * Note that currently we करोn't propagate cmd_flags
	 * to the iterator. In हाल of key_data.configure_keys,
	 * all the configured commands are SYNC, and
	 * iwl_mvm_wowlan_program_keys() will take care of
	 * locking/unlocking mvm->mutex.
	 */
	ieee80211_iter_keys(mvm->hw, vअगर, iwl_mvm_wowlan_program_keys,
			    &key_data);

	अगर (key_data.error) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (key_data.use_rsc_tsc) अणु
		पूर्णांक ver = iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
						WOWLAN_TSC_RSC_PARAM,
						IWL_FW_CMD_VER_UNKNOWN);
		पूर्णांक size;

		अगर (ver == 4) अणु
			size = माप(*key_data.rsc_tsc);
			key_data.rsc_tsc->sta_id =
				cpu_to_le32(mvmvअगर->ap_sta_id);

		पूर्ण अन्यथा अगर (ver == 2 || ver == IWL_FW_CMD_VER_UNKNOWN) अणु
			size = माप(key_data.rsc_tsc->params);
		पूर्ण अन्यथा अणु
			ret = 0;
			WARN_ON_ONCE(1);
			जाओ out;
		पूर्ण

		ret = iwl_mvm_send_cmd_pdu(mvm, WOWLAN_TSC_RSC_PARAM,
					   cmd_flags,
					   size,
					   key_data.rsc_tsc);

		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (key_data.use_tkip &&
	    !fw_has_api(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_API_TKIP_MIC_KEYS)) अणु
		पूर्णांक ver = iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
						WOWLAN_TKIP_PARAM,
						IWL_FW_CMD_VER_UNKNOWN);
		पूर्णांक size;

		अगर (ver == 2) अणु
			size = माप(tkip_cmd);
			key_data.tkip->sta_id =
				cpu_to_le32(mvmvअगर->ap_sta_id);
		पूर्ण अन्यथा अगर (ver == 1 || ver == IWL_FW_CMD_VER_UNKNOWN) अणु
			size = माप(काष्ठा iwl_wowlan_tkip_params_cmd_ver_1);
		पूर्ण अन्यथा अणु
			ret =  -EINVAL;
			WARN_ON_ONCE(1);
			जाओ out;
		पूर्ण

		/* send relevant data according to CMD version */
		ret = iwl_mvm_send_cmd_pdu(mvm,
					   WOWLAN_TKIP_PARAM,
					   cmd_flags, size,
					   &tkip_cmd);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* configure rekey data only अगर offloaded rekey is supported (d3) */
	अगर (mvmvअगर->rekey_data.valid) अणु
		cmd_ver = iwl_fw_lookup_cmd_ver(mvm->fw,
						IWL_ALWAYS_LONG_GROUP,
						WOWLAN_KEK_KCK_MATERIAL,
						IWL_FW_CMD_VER_UNKNOWN);
		अगर (WARN_ON(cmd_ver != 2 && cmd_ver != 3 &&
			    cmd_ver != IWL_FW_CMD_VER_UNKNOWN))
			वापस -EINVAL;
		अगर (cmd_ver == 3)
			cmd_size = माप(काष्ठा iwl_wowlan_kek_kck_material_cmd_v3);
		अन्यथा
			cmd_size = माप(काष्ठा iwl_wowlan_kek_kck_material_cmd_v2);

		स_नकल(kek_kck_cmd.kck, mvmvअगर->rekey_data.kck,
		       mvmvअगर->rekey_data.kck_len);
		kek_kck_cmd.kck_len = cpu_to_le16(mvmvअगर->rekey_data.kck_len);
		स_नकल(kek_kck_cmd.kek, mvmvअगर->rekey_data.kek,
		       mvmvअगर->rekey_data.kek_len);
		kek_kck_cmd.kek_len = cpu_to_le16(mvmvअगर->rekey_data.kek_len);
		kek_kck_cmd.replay_ctr = mvmvअगर->rekey_data.replay_ctr;
		kek_kck_cmd.akm = cpu_to_le32(mvmvअगर->rekey_data.akm);

		IWL_DEBUG_WOWLAN(mvm, "setting akm %d\n",
				 mvmvअगर->rekey_data.akm);

		ret = iwl_mvm_send_cmd_pdu(mvm,
					   WOWLAN_KEK_KCK_MATERIAL, cmd_flags,
					   cmd_size,
					   &kek_kck_cmd);
		अगर (ret)
			जाओ out;
	पूर्ण
	ret = 0;
out:
	kमुक्त(key_data.rsc_tsc);
	वापस ret;
पूर्ण

अटल पूर्णांक
iwl_mvm_wowlan_config(काष्ठा iwl_mvm *mvm,
		      काष्ठा cfg80211_wowlan *wowlan,
		      काष्ठा iwl_wowlan_config_cmd *wowlan_config_cmd,
		      काष्ठा ieee80211_vअगर *vअगर, काष्ठा iwl_mvm_vअगर *mvmvअगर,
		      काष्ठा ieee80211_sta *ap_sta)
अणु
	पूर्णांक ret;
	bool unअगरied_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);

	mvm->offload_tid = wowlan_config_cmd->offloading_tid;

	अगर (!unअगरied_image) अणु
		ret = iwl_mvm_चयन_to_d3(mvm);
		अगर (ret)
			वापस ret;

		ret = iwl_mvm_d3_reprogram(mvm, vअगर, ap_sta);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * This needs to be unlocked due to lock ordering
	 * स्थिरraपूर्णांकs. Since we're in the suspend path
	 * that isn't really a problem though.
	 */
	mutex_unlock(&mvm->mutex);
	ret = iwl_mvm_wowlan_config_key_params(mvm, vअगर, CMD_ASYNC);
	mutex_lock(&mvm->mutex);
	अगर (ret)
		वापस ret;

	ret = iwl_mvm_send_cmd_pdu(mvm, WOWLAN_CONFIGURATION, 0,
				   माप(*wowlan_config_cmd),
				   wowlan_config_cmd);
	अगर (ret)
		वापस ret;

	अगर (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_WOWLAN_TCP_SYN_WAKE))
		ret = iwl_mvm_send_patterns(mvm, wowlan);
	अन्यथा
		ret = iwl_mvm_send_patterns_v1(mvm, wowlan);
	अगर (ret)
		वापस ret;

	वापस iwl_mvm_send_proto_offload(mvm, vअगर, false, true, 0);
पूर्ण

अटल पूर्णांक
iwl_mvm_netdetect_config(काष्ठा iwl_mvm *mvm,
			 काष्ठा cfg80211_wowlan *wowlan,
			 काष्ठा cfg80211_sched_scan_request *nd_config,
			 काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक ret;
	bool unअगरied_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);

	अगर (!unअगरied_image) अणु
		ret = iwl_mvm_चयन_to_d3(mvm);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* In theory, we wouldn't have to stop a running sched
		 * scan in order to start another one (क्रम
		 * net-detect).  But in practice this करोesn't seem to
		 * work properly, so stop any running sched_scan now.
		 */
		ret = iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_SCHED, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = iwl_mvm_sched_scan_start(mvm, vअगर, nd_config, &mvm->nd_ies,
				       IWL_MVM_SCAN_NETDETECT);
	अगर (ret)
		वापस ret;

	अगर (WARN_ON(mvm->nd_match_sets || mvm->nd_channels))
		वापस -EBUSY;

	/* save the sched scan matchsets... */
	अगर (nd_config->n_match_sets) अणु
		mvm->nd_match_sets = kmemdup(nd_config->match_sets,
					     माप(*nd_config->match_sets) *
					     nd_config->n_match_sets,
					     GFP_KERNEL);
		अगर (mvm->nd_match_sets)
			mvm->n_nd_match_sets = nd_config->n_match_sets;
	पूर्ण

	/* ...and the sched scan channels क्रम later reporting */
	mvm->nd_channels = kmemdup(nd_config->channels,
				   माप(*nd_config->channels) *
				   nd_config->n_channels,
				   GFP_KERNEL);
	अगर (mvm->nd_channels)
		mvm->n_nd_channels = nd_config->n_channels;

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_मुक्त_nd(काष्ठा iwl_mvm *mvm)
अणु
	kमुक्त(mvm->nd_match_sets);
	mvm->nd_match_sets = शून्य;
	mvm->n_nd_match_sets = 0;
	kमुक्त(mvm->nd_channels);
	mvm->nd_channels = शून्य;
	mvm->n_nd_channels = 0;
पूर्ण

अटल पूर्णांक __iwl_mvm_suspend(काष्ठा ieee80211_hw *hw,
			     काष्ठा cfg80211_wowlan *wowlan,
			     bool test)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = शून्य;
	काष्ठा ieee80211_sta *ap_sta = शून्य;
	काष्ठा iwl_d3_manager_config d3_cfg_cmd_data = अणु
		/*
		 * Program the minimum sleep समय to 10 seconds, as many
		 * platक्रमms have issues processing a wakeup संकेत जबतक
		 * still being in the process of suspending.
		 */
		.min_sleep_समय = cpu_to_le32(10 * 1000 * 1000),
	पूर्ण;
	काष्ठा iwl_host_cmd d3_cfg_cmd = अणु
		.id = D3_CONFIG_CMD,
		.flags = CMD_WANT_SKB | CMD_SEND_IN_D3,
		.data[0] = &d3_cfg_cmd_data,
		.len[0] = माप(d3_cfg_cmd_data),
	पूर्ण;
	पूर्णांक ret;
	पूर्णांक len __maybe_unused;
	bool unअगरied_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);

	अगर (!wowlan) अणु
		/*
		 * mac80211 shouldn't get here, but क्रम D3 test
		 * it करोesn't warrant a warning
		 */
		WARN_ON(!test);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&mvm->mutex);

	set_bit(IWL_MVM_STATUS_IN_D3, &mvm->status);

	synchronize_net();

	vअगर = iwl_mvm_get_bss_vअगर(mvm);
	अगर (IS_ERR_OR_शून्य(vअगर)) अणु
		ret = 1;
		जाओ out_noreset;
	पूर्ण

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (mvmvअगर->ap_sta_id == IWL_MVM_INVALID_STA) अणु
		/* अगर we're not associated, this must be netdetect */
		अगर (!wowlan->nd_config) अणु
			ret = 1;
			जाओ out_noreset;
		पूर्ण

		ret = iwl_mvm_netdetect_config(
			mvm, wowlan, wowlan->nd_config, vअगर);
		अगर (ret)
			जाओ out;

		mvm->net_detect = true;
	पूर्ण अन्यथा अणु
		काष्ठा iwl_wowlan_config_cmd wowlan_config_cmd = अणुपूर्ण;

		wowlan_config_cmd.sta_id = mvmvअगर->ap_sta_id;

		ap_sta = rcu_dereference_रक्षित(
			mvm->fw_id_to_mac_id[mvmvअगर->ap_sta_id],
			lockdep_is_held(&mvm->mutex));
		अगर (IS_ERR_OR_शून्य(ap_sta)) अणु
			ret = -EINVAL;
			जाओ out_noreset;
		पूर्ण

		ret = iwl_mvm_get_wowlan_config(mvm, wowlan, &wowlan_config_cmd,
						vअगर, mvmvअगर, ap_sta);
		अगर (ret)
			जाओ out_noreset;
		ret = iwl_mvm_wowlan_config(mvm, wowlan, &wowlan_config_cmd,
					    vअगर, mvmvअगर, ap_sta);
		अगर (ret)
			जाओ out;

		mvm->net_detect = false;
	पूर्ण

	ret = iwl_mvm_घातer_update_device(mvm);
	अगर (ret)
		जाओ out;

	ret = iwl_mvm_घातer_update_mac(mvm);
	अगर (ret)
		जाओ out;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (mvm->d3_wake_sysनिश्चित)
		d3_cfg_cmd_data.wakeup_flags |=
			cpu_to_le32(IWL_WAKEUP_D3_CONFIG_FW_ERROR);
#पूर्ण_अगर

	/*
	 * Prior to 9000 device family the driver needs to stop the dbg
	 * recording beक्रमe entering D3. In later devices the FW stops the
	 * recording स्वतःmatically.
	 */
	अगर (mvm->trans->trans_cfg->device_family < IWL_DEVICE_FAMILY_9000)
		iwl_fw_dbg_stop_restart_recording(&mvm->fwrt, शून्य, true);

	mvm->trans->प्रणाली_pm_mode = IWL_PLAT_PM_MODE_D3;

	/* must be last -- this चयनes firmware state */
	ret = iwl_mvm_send_cmd(mvm, &d3_cfg_cmd);
	अगर (ret)
		जाओ out;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	len = iwl_rx_packet_payload_len(d3_cfg_cmd.resp_pkt);
	अगर (len >= माप(u32)) अणु
		mvm->d3_test_pme_ptr =
			le32_to_cpup((__le32 *)d3_cfg_cmd.resp_pkt->data);
	पूर्ण
#पूर्ण_अगर
	iwl_मुक्त_resp(&d3_cfg_cmd);

	clear_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);

	ret = iwl_trans_d3_suspend(mvm->trans, test, !unअगरied_image);
 out:
	अगर (ret < 0) अणु
		iwl_mvm_मुक्त_nd(mvm);

		अगर (!unअगरied_image) अणु
			अगर (mvm->fw_restart > 0) अणु
				mvm->fw_restart--;
				ieee80211_restart_hw(mvm->hw);
			पूर्ण
		पूर्ण

		clear_bit(IWL_MVM_STATUS_IN_D3, &mvm->status);
	पूर्ण
 out_noreset:
	mutex_unlock(&mvm->mutex);

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_suspend(काष्ठा ieee80211_hw *hw, काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	iwl_mvm_छोड़ो_tcm(mvm, true);

	iwl_fw_runसमय_suspend(&mvm->fwrt);

	वापस __iwl_mvm_suspend(hw, wowlan, false);
पूर्ण

/* converted data from the dअगरferent status responses */
काष्ठा iwl_wowlan_status_data अणु
	u16 pattern_number;
	u16 qos_seq_ctr[8];
	u32 wakeup_reasons;
	u32 wake_packet_length;
	u32 wake_packet_bufsize;
	स्थिर u8 *wake_packet;
पूर्ण;

अटल व्योम iwl_mvm_report_wakeup_reasons(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा iwl_wowlan_status_data *status)
अणु
	काष्ठा sk_buff *pkt = शून्य;
	काष्ठा cfg80211_wowlan_wakeup wakeup = अणु
		.pattern_idx = -1,
	पूर्ण;
	काष्ठा cfg80211_wowlan_wakeup *wakeup_report = &wakeup;
	u32 reasons = status->wakeup_reasons;

	अगर (reasons == IWL_WOWLAN_WAKEUP_BY_NON_WIRELESS) अणु
		wakeup_report = शून्य;
		जाओ report;
	पूर्ण

	pm_wakeup_event(mvm->dev, 0);

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_MAGIC_PACKET)
		wakeup.magic_pkt = true;

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_PATTERN)
		wakeup.pattern_idx =
			status->pattern_number;

	अगर (reasons & (IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON |
		       IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH))
		wakeup.disconnect = true;

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_GTK_REKEY_FAILURE)
		wakeup.gtk_rekey_failure = true;

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_RFKILL_DEASSERTED)
		wakeup.rfसमाप्त_release = true;

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_EAPOL_REQUEST)
		wakeup.eap_identity_req = true;

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_FOUR_WAY_HANDSHAKE)
		wakeup.four_way_handshake = true;

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_REM_WAKE_LINK_LOSS)
		wakeup.tcp_connlost = true;

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_REM_WAKE_SIGNATURE_TABLE)
		wakeup.tcp_nomoretokens = true;

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_REM_WAKE_WAKEUP_PACKET)
		wakeup.tcp_match = true;

	अगर (status->wake_packet_bufsize) अणु
		पूर्णांक pktsize = status->wake_packet_bufsize;
		पूर्णांक pktlen = status->wake_packet_length;
		स्थिर u8 *pktdata = status->wake_packet;
		काष्ठा ieee80211_hdr *hdr = (व्योम *)pktdata;
		पूर्णांक truncated = pktlen - pktsize;

		/* this would be a firmware bug */
		अगर (WARN_ON_ONCE(truncated < 0))
			truncated = 0;

		अगर (ieee80211_is_data(hdr->frame_control)) अणु
			पूर्णांक hdrlen = ieee80211_hdrlen(hdr->frame_control);
			पूर्णांक ivlen = 0, icvlen = 4; /* also FCS */

			pkt = alloc_skb(pktsize, GFP_KERNEL);
			अगर (!pkt)
				जाओ report;

			skb_put_data(pkt, pktdata, hdrlen);
			pktdata += hdrlen;
			pktsize -= hdrlen;

			अगर (ieee80211_has_रक्षित(hdr->frame_control)) अणु
				/*
				 * This is unlocked and using gtk_i(c)vlen,
				 * but since everything is under RTNL still
				 * that's not really a problem - changing
				 * it would be dअगरficult.
				 */
				अगर (is_multicast_ether_addr(hdr->addr1)) अणु
					ivlen = mvm->gtk_ivlen;
					icvlen += mvm->gtk_icvlen;
				पूर्ण अन्यथा अणु
					ivlen = mvm->ptk_ivlen;
					icvlen += mvm->ptk_icvlen;
				पूर्ण
			पूर्ण

			/* अगर truncated, FCS/ICV is (partially) gone */
			अगर (truncated >= icvlen) अणु
				icvlen = 0;
				truncated -= icvlen;
			पूर्ण अन्यथा अणु
				icvlen -= truncated;
				truncated = 0;
			पूर्ण

			pktsize -= ivlen + icvlen;
			pktdata += ivlen;

			skb_put_data(pkt, pktdata, pktsize);

			अगर (ieee80211_data_to_8023(pkt, vअगर->addr, vअगर->type))
				जाओ report;
			wakeup.packet = pkt->data;
			wakeup.packet_present_len = pkt->len;
			wakeup.packet_len = pkt->len - truncated;
			wakeup.packet_80211 = false;
		पूर्ण अन्यथा अणु
			पूर्णांक fcslen = 4;

			अगर (truncated >= 4) अणु
				truncated -= 4;
				fcslen = 0;
			पूर्ण अन्यथा अणु
				fcslen -= truncated;
				truncated = 0;
			पूर्ण
			pktsize -= fcslen;
			wakeup.packet = status->wake_packet;
			wakeup.packet_present_len = pktsize;
			wakeup.packet_len = pktlen - truncated;
			wakeup.packet_80211 = true;
		पूर्ण
	पूर्ण

 report:
	ieee80211_report_wowlan_wakeup(vअगर, wakeup_report, GFP_KERNEL);
	kमुक्त_skb(pkt);
पूर्ण

अटल व्योम iwl_mvm_aes_sc_to_seq(काष्ठा aes_sc *sc,
				  काष्ठा ieee80211_key_seq *seq)
अणु
	u64 pn;

	pn = le64_to_cpu(sc->pn);
	seq->ccmp.pn[0] = pn >> 40;
	seq->ccmp.pn[1] = pn >> 32;
	seq->ccmp.pn[2] = pn >> 24;
	seq->ccmp.pn[3] = pn >> 16;
	seq->ccmp.pn[4] = pn >> 8;
	seq->ccmp.pn[5] = pn;
पूर्ण

अटल व्योम iwl_mvm_tkip_sc_to_seq(काष्ठा tkip_sc *sc,
				   काष्ठा ieee80211_key_seq *seq)
अणु
	seq->tkip.iv32 = le32_to_cpu(sc->iv32);
	seq->tkip.iv16 = le16_to_cpu(sc->iv16);
पूर्ण

अटल व्योम iwl_mvm_set_aes_rx_seq(काष्ठा iwl_mvm *mvm, काष्ठा aes_sc *scs,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा ieee80211_key_conf *key)
अणु
	पूर्णांक tid;

	BUILD_BUG_ON(IWL_NUM_RSC != IEEE80211_NUM_TIDS);

	अगर (sta && iwl_mvm_has_new_rx_api(mvm)) अणु
		काष्ठा iwl_mvm_sta *mvmsta;
		काष्ठा iwl_mvm_key_pn *ptk_pn;

		mvmsta = iwl_mvm_sta_from_mac80211(sta);

		rcu_पढ़ो_lock();
		ptk_pn = rcu_dereference(mvmsta->ptk_pn[key->keyidx]);
		अगर (WARN_ON(!ptk_pn)) अणु
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण

		क्रम (tid = 0; tid < IWL_MAX_TID_COUNT; tid++) अणु
			काष्ठा ieee80211_key_seq seq = अणुपूर्ण;
			पूर्णांक i;

			iwl_mvm_aes_sc_to_seq(&scs[tid], &seq);
			ieee80211_set_key_rx_seq(key, tid, &seq);
			क्रम (i = 1; i < mvm->trans->num_rx_queues; i++)
				स_नकल(ptk_pn->q[i].pn[tid],
				       seq.ccmp.pn, IEEE80211_CCMP_PN_LEN);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		क्रम (tid = 0; tid < IWL_NUM_RSC; tid++) अणु
			काष्ठा ieee80211_key_seq seq = अणुपूर्ण;

			iwl_mvm_aes_sc_to_seq(&scs[tid], &seq);
			ieee80211_set_key_rx_seq(key, tid, &seq);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_set_tkip_rx_seq(काष्ठा tkip_sc *scs,
				    काष्ठा ieee80211_key_conf *key)
अणु
	पूर्णांक tid;

	BUILD_BUG_ON(IWL_NUM_RSC != IEEE80211_NUM_TIDS);

	क्रम (tid = 0; tid < IWL_NUM_RSC; tid++) अणु
		काष्ठा ieee80211_key_seq seq = अणुपूर्ण;

		iwl_mvm_tkip_sc_to_seq(&scs[tid], &seq);
		ieee80211_set_key_rx_seq(key, tid, &seq);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_set_key_rx_seq(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_key_conf *key,
				   काष्ठा iwl_wowlan_status *status)
अणु
	जोड़ iwl_all_tsc_rsc *rsc = &status->gtk[0].rsc.all_tsc_rsc;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		iwl_mvm_set_aes_rx_seq(mvm, rsc->aes.multicast_rsc, शून्य, key);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		iwl_mvm_set_tkip_rx_seq(rsc->tkip.multicast_rsc, key);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण

काष्ठा iwl_mvm_d3_gtk_iter_data अणु
	काष्ठा iwl_mvm *mvm;
	काष्ठा iwl_wowlan_status *status;
	व्योम *last_gtk;
	u32 cipher;
	bool find_phase, unhandled_cipher;
	पूर्णांक num_keys;
पूर्ण;

अटल व्योम iwl_mvm_d3_update_keys(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा ieee80211_key_conf *key,
				   व्योम *_data)
अणु
	काष्ठा iwl_mvm_d3_gtk_iter_data *data = _data;

	अगर (data->unhandled_cipher)
		वापस;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		/* ignore WEP completely, nothing to करो */
		वापस;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
	हाल WLAN_CIPHER_SUITE_TKIP:
		/* we support these */
		अवरोध;
	शेष:
		/* everything अन्यथा (even CMAC क्रम MFP) - disconnect from AP */
		data->unhandled_cipher = true;
		वापस;
	पूर्ण

	data->num_keys++;

	/*
	 * pairwise key - update sequence counters only;
	 * note that this assumes no TDLS sessions are active
	 */
	अगर (sta) अणु
		काष्ठा ieee80211_key_seq seq = अणुपूर्ण;
		जोड़ iwl_all_tsc_rsc *sc =
			&data->status->gtk[0].rsc.all_tsc_rsc;

		अगर (data->find_phase)
			वापस;

		चयन (key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_CCMP:
		हाल WLAN_CIPHER_SUITE_GCMP:
		हाल WLAN_CIPHER_SUITE_GCMP_256:
			iwl_mvm_set_aes_rx_seq(data->mvm, sc->aes.unicast_rsc,
					       sta, key);
			atomic64_set(&key->tx_pn, le64_to_cpu(sc->aes.tsc.pn));
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			iwl_mvm_tkip_sc_to_seq(&sc->tkip.tsc, &seq);
			iwl_mvm_set_tkip_rx_seq(sc->tkip.unicast_rsc, key);
			atomic64_set(&key->tx_pn,
				     (u64)seq.tkip.iv16 |
				     ((u64)seq.tkip.iv32 << 16));
			अवरोध;
		पूर्ण

		/* that's it क्रम this key */
		वापस;
	पूर्ण

	अगर (data->find_phase) अणु
		data->last_gtk = key;
		data->cipher = key->cipher;
		वापस;
	पूर्ण

	अगर (data->status->num_of_gtk_rekeys)
		ieee80211_हटाओ_key(key);
	अन्यथा अगर (data->last_gtk == key)
		iwl_mvm_set_key_rx_seq(data->mvm, key, data->status);
पूर्ण

अटल bool iwl_mvm_setup_connection_keep(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा iwl_wowlan_status *status)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_d3_gtk_iter_data gtkdata = अणु
		.mvm = mvm,
		.status = status,
	पूर्ण;
	u32 disconnection_reasons =
		IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON |
		IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH;

	अगर (!status || !vअगर->bss_conf.bssid)
		वापस false;

	अगर (le32_to_cpu(status->wakeup_reasons) & disconnection_reasons)
		वापस false;

	/* find last GTK that we used initially, अगर any */
	gtkdata.find_phase = true;
	ieee80211_iter_keys(mvm->hw, vअगर,
			    iwl_mvm_d3_update_keys, &gtkdata);
	/* not trying to keep connections with MFP/unhandled ciphers */
	अगर (gtkdata.unhandled_cipher)
		वापस false;
	अगर (!gtkdata.num_keys)
		जाओ out;
	अगर (!gtkdata.last_gtk)
		वापस false;

	/*
	 * invalidate all other GTKs that might still exist and update
	 * the one that we used
	 */
	gtkdata.find_phase = false;
	ieee80211_iter_keys(mvm->hw, vअगर,
			    iwl_mvm_d3_update_keys, &gtkdata);

	IWL_DEBUG_WOWLAN(mvm, "num of GTK rekeying %d\n",
			 le32_to_cpu(status->num_of_gtk_rekeys));
	अगर (status->num_of_gtk_rekeys) अणु
		काष्ठा ieee80211_key_conf *key;
		काष्ठा अणु
			काष्ठा ieee80211_key_conf conf;
			u8 key[32];
		पूर्ण conf = अणु
			.conf.cipher = gtkdata.cipher,
			.conf.keyidx =
				iwlmvm_wowlan_gtk_idx(&status->gtk[0]),
		पूर्ण;
		__be64 replay_ctr;

		IWL_DEBUG_WOWLAN(mvm,
				 "Received from FW GTK cipher %d, key index %d\n",
				 conf.conf.cipher, conf.conf.keyidx);
		चयन (gtkdata.cipher) अणु
		हाल WLAN_CIPHER_SUITE_CCMP:
		हाल WLAN_CIPHER_SUITE_GCMP:
			BUILD_BUG_ON(WLAN_KEY_LEN_CCMP != WLAN_KEY_LEN_GCMP);
			BUILD_BUG_ON(माप(conf.key) < WLAN_KEY_LEN_CCMP);
			conf.conf.keylen = WLAN_KEY_LEN_CCMP;
			स_नकल(conf.conf.key, status->gtk[0].key,
			       WLAN_KEY_LEN_CCMP);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_GCMP_256:
			BUILD_BUG_ON(माप(conf.key) < WLAN_KEY_LEN_GCMP_256);
			conf.conf.keylen = WLAN_KEY_LEN_GCMP_256;
			स_नकल(conf.conf.key, status->gtk[0].key,
			       WLAN_KEY_LEN_GCMP_256);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_TKIP:
			BUILD_BUG_ON(माप(conf.key) < WLAN_KEY_LEN_TKIP);
			conf.conf.keylen = WLAN_KEY_LEN_TKIP;
			स_नकल(conf.conf.key, status->gtk[0].key, 16);
			/* leave TX MIC key zeroed, we करोn't use it anyway */
			स_नकल(conf.conf.key +
			       NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY,
			       status->gtk[0].tkip_mic_key, 8);
			अवरोध;
		पूर्ण

		key = ieee80211_gtk_rekey_add(vअगर, &conf.conf);
		अगर (IS_ERR(key))
			वापस false;
		iwl_mvm_set_key_rx_seq(mvm, key, status);

		replay_ctr =
			cpu_to_be64(le64_to_cpu(status->replay_ctr));

		ieee80211_gtk_rekey_notअगरy(vअगर, vअगर->bss_conf.bssid,
					   (व्योम *)&replay_ctr, GFP_KERNEL);
	पूर्ण

out:
	mvmvअगर->seqno_valid = true;
	/* +0x10 because the set API expects next-to-use, not last-used */
	mvmvअगर->seqno = le16_to_cpu(status->non_qos_seq_ctr) + 0x10;

	वापस true;
पूर्ण

/* Occasionally, ढाँचाs would be nice. This is one of those बार ... */
#घोषणा iwl_mvm_parse_wowlan_status_common(_ver)			\
अटल काष्ठा iwl_wowlan_status *					\
iwl_mvm_parse_wowlan_status_common_ ## _ver(काष्ठा iwl_mvm *mvm,	\
					    व्योम *_data, पूर्णांक len)	\
अणु									\
	काष्ठा iwl_wowlan_status *status;				\
	काष्ठा iwl_wowlan_status_ ##_ver *data = _data;			\
	पूर्णांक data_size;							\
									\
	अगर (len < माप(*data)) अणु					\
		IWL_ERR(mvm, "Invalid WoWLAN status response!\n");	\
		वापस ERR_PTR(-EIO);					\
	पूर्ण								\
									\
	data_size = ALIGN(le32_to_cpu(data->wake_packet_bufsize), 4);	\
	अगर (len != माप(*data) + data_size) अणु				\
		IWL_ERR(mvm, "Invalid WoWLAN status response!\n");	\
		वापस ERR_PTR(-EIO);					\
	पूर्ण								\
									\
	status = kzalloc(माप(*status) + data_size, GFP_KERNEL);	\
	अगर (!status)							\
		वापस ERR_PTR(-ENOMEM);				\
									\
	/* copy all the common fields */				\
	status->replay_ctr = data->replay_ctr;				\
	status->pattern_number = data->pattern_number;			\
	status->non_qos_seq_ctr = data->non_qos_seq_ctr;		\
	स_नकल(status->qos_seq_ctr, data->qos_seq_ctr,			\
	       माप(status->qos_seq_ctr));				\
	status->wakeup_reasons = data->wakeup_reasons;			\
	status->num_of_gtk_rekeys = data->num_of_gtk_rekeys;		\
	status->received_beacons = data->received_beacons;		\
	status->wake_packet_length = data->wake_packet_length;		\
	status->wake_packet_bufsize = data->wake_packet_bufsize;	\
	स_नकल(status->wake_packet, data->wake_packet,			\
	       le32_to_cpu(status->wake_packet_bufsize));		\
									\
	वापस status;							\
पूर्ण

iwl_mvm_parse_wowlan_status_common(v6)
iwl_mvm_parse_wowlan_status_common(v7)
iwl_mvm_parse_wowlan_status_common(v9)

काष्ठा iwl_wowlan_status *iwl_mvm_send_wowlan_get_status(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_wowlan_status *status;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = WOWLAN_GET_STATUSES,
		.flags = CMD_WANT_SKB,
	पूर्ण;
	पूर्णांक ret, len;
	u8 notअगर_ver;

	lockdep_निश्चित_held(&mvm->mutex);

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "failed to query wakeup status (%d)\n", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	len = iwl_rx_packet_payload_len(cmd.resp_pkt);

	/* शेष to 7 (when we have IWL_UCODE_TLV_API_WOWLAN_KEY_MATERIAL) */
	notअगर_ver = iwl_fw_lookup_notअगर_ver(mvm->fw, LEGACY_GROUP,
					    WOWLAN_GET_STATUSES, 7);

	अगर (!fw_has_api(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_API_WOWLAN_KEY_MATERIAL)) अणु
		काष्ठा iwl_wowlan_status_v6 *v6 = (व्योम *)cmd.resp_pkt->data;

		status = iwl_mvm_parse_wowlan_status_common_v6(mvm,
							       cmd.resp_pkt->data,
							       len);
		अगर (IS_ERR(status))
			जाओ out_मुक्त_resp;

		BUILD_BUG_ON(माप(v6->gtk.decrypt_key) >
			     माप(status->gtk[0].key));
		BUILD_BUG_ON(माप(v6->gtk.tkip_mic_key) >
			     माप(status->gtk[0].tkip_mic_key));

		/* copy GTK info to the right place */
		स_नकल(status->gtk[0].key, v6->gtk.decrypt_key,
		       माप(v6->gtk.decrypt_key));
		स_नकल(status->gtk[0].tkip_mic_key, v6->gtk.tkip_mic_key,
		       माप(v6->gtk.tkip_mic_key));
		स_नकल(&status->gtk[0].rsc, &v6->gtk.rsc,
		       माप(status->gtk[0].rsc));

		/* hardcode the key length to 16 since v6 only supports 16 */
		status->gtk[0].key_len = 16;

		/*
		 * The key index only uses 2 bits (values 0 to 3) and
		 * we always set bit 7 which means this is the
		 * currently used key.
		 */
		status->gtk[0].key_flags = v6->gtk.key_index | BIT(7);
	पूर्ण अन्यथा अगर (notअगर_ver == 7) अणु
		काष्ठा iwl_wowlan_status_v7 *v7 = (व्योम *)cmd.resp_pkt->data;

		status = iwl_mvm_parse_wowlan_status_common_v7(mvm,
							       cmd.resp_pkt->data,
							       len);
		अगर (IS_ERR(status))
			जाओ out_मुक्त_resp;

		status->gtk[0] = v7->gtk[0];
		status->igtk[0] = v7->igtk[0];
	पूर्ण अन्यथा अगर (notअगर_ver == 9) अणु
		काष्ठा iwl_wowlan_status_v9 *v9 = (व्योम *)cmd.resp_pkt->data;

		status = iwl_mvm_parse_wowlan_status_common_v9(mvm,
							       cmd.resp_pkt->data,
							       len);
		अगर (IS_ERR(status))
			जाओ out_मुक्त_resp;

		status->gtk[0] = v9->gtk[0];
		status->igtk[0] = v9->igtk[0];

		status->tid_tear_करोwn = v9->tid_tear_करोwn;
	पूर्ण अन्यथा अणु
		IWL_ERR(mvm,
			"Firmware advertises unknown WoWLAN status response %d!\n",
			notअगर_ver);
		status = ERR_PTR(-EIO);
	पूर्ण

out_मुक्त_resp:
	iwl_मुक्त_resp(&cmd);
	वापस status;
पूर्ण

अटल काष्ठा iwl_wowlan_status *
iwl_mvm_get_wakeup_status(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	/* only क्रम tracing क्रम now */
	ret = iwl_mvm_send_cmd_pdu(mvm, OFFLOADS_QUERY_CMD, 0, 0, शून्य);
	अगर (ret)
		IWL_ERR(mvm, "failed to query offload statistics (%d)\n", ret);

	वापस iwl_mvm_send_wowlan_get_status(mvm);
पूर्ण

/* releases the MVM mutex */
अटल bool iwl_mvm_query_wakeup_reasons(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_wowlan_status_data status;
	काष्ठा iwl_wowlan_status *fw_status;
	पूर्णांक i;
	bool keep;
	काष्ठा iwl_mvm_sta *mvm_ap_sta;

	fw_status = iwl_mvm_get_wakeup_status(mvm);
	अगर (IS_ERR_OR_शून्य(fw_status))
		जाओ out_unlock;

	IWL_DEBUG_WOWLAN(mvm, "wakeup reason 0x%x\n",
			 le32_to_cpu(fw_status->wakeup_reasons));

	status.pattern_number = le16_to_cpu(fw_status->pattern_number);
	क्रम (i = 0; i < 8; i++)
		status.qos_seq_ctr[i] =
			le16_to_cpu(fw_status->qos_seq_ctr[i]);
	status.wakeup_reasons = le32_to_cpu(fw_status->wakeup_reasons);
	status.wake_packet_length =
		le32_to_cpu(fw_status->wake_packet_length);
	status.wake_packet_bufsize =
		le32_to_cpu(fw_status->wake_packet_bufsize);
	status.wake_packet = fw_status->wake_packet;

	/* still at hard-coded place 0 क्रम D3 image */
	mvm_ap_sta = iwl_mvm_sta_from_staid_रक्षित(mvm, 0);
	अगर (!mvm_ap_sta)
		जाओ out_मुक्त;

	क्रम (i = 0; i < IWL_MAX_TID_COUNT; i++) अणु
		u16 seq = status.qos_seq_ctr[i];
		/* firmware stores last-used value, we store next value */
		seq += 0x10;
		mvm_ap_sta->tid_data[i].seq_number = seq;
	पूर्ण

	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000) अणु
		i = mvm->offload_tid;
		iwl_trans_set_q_ptrs(mvm->trans,
				     mvm_ap_sta->tid_data[i].txq_id,
				     mvm_ap_sta->tid_data[i].seq_number >> 4);
	पूर्ण

	/* now we have all the data we need, unlock to aव्योम mac80211 issues */
	mutex_unlock(&mvm->mutex);

	iwl_mvm_report_wakeup_reasons(mvm, vअगर, &status);

	keep = iwl_mvm_setup_connection_keep(mvm, vअगर, fw_status);

	kमुक्त(fw_status);
	वापस keep;

out_मुक्त:
	kमुक्त(fw_status);
out_unlock:
	mutex_unlock(&mvm->mutex);
	वापस false;
पूर्ण

#घोषणा ND_QUERY_BUF_LEN (माप(काष्ठा iwl_scan_offload_profile_match) * \
			  IWL_SCAN_MAX_PROखाताS)

काष्ठा iwl_mvm_nd_query_results अणु
	u32 matched_profiles;
	u8 matches[ND_QUERY_BUF_LEN];
पूर्ण;

अटल पूर्णांक
iwl_mvm_netdetect_query_results(काष्ठा iwl_mvm *mvm,
				काष्ठा iwl_mvm_nd_query_results *results)
अणु
	काष्ठा iwl_scan_offload_profiles_query *query;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = SCAN_OFFLOAD_PROखाताS_QUERY_CMD,
		.flags = CMD_WANT_SKB,
	पूर्ण;
	पूर्णांक ret, len;
	माप_प्रकार query_len, matches_len;
	पूर्णांक max_profiles = iwl_umac_scan_get_max_profiles(mvm->fw);

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "failed to query matched profiles (%d)\n", ret);
		वापस ret;
	पूर्ण

	अगर (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_SCAN_OFFLOAD_CHANS)) अणु
		query_len = माप(काष्ठा iwl_scan_offload_profiles_query);
		matches_len = माप(काष्ठा iwl_scan_offload_profile_match) *
			max_profiles;
	पूर्ण अन्यथा अणु
		query_len = माप(काष्ठा iwl_scan_offload_profiles_query_v1);
		matches_len = माप(काष्ठा iwl_scan_offload_profile_match_v1) *
			max_profiles;
	पूर्ण

	len = iwl_rx_packet_payload_len(cmd.resp_pkt);
	अगर (len < query_len) अणु
		IWL_ERR(mvm, "Invalid scan offload profiles query response!\n");
		ret = -EIO;
		जाओ out_मुक्त_resp;
	पूर्ण

	query = (व्योम *)cmd.resp_pkt->data;

	results->matched_profiles = le32_to_cpu(query->matched_profiles);
	स_नकल(results->matches, query->matches, matches_len);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	mvm->last_netdetect_scans = le32_to_cpu(query->n_scans_करोne);
#पूर्ण_अगर

out_मुक्त_resp:
	iwl_मुक्त_resp(&cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_query_num_match_chans(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_mvm_nd_query_results *query,
					 पूर्णांक idx)
अणु
	पूर्णांक n_chans = 0, i;

	अगर (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_SCAN_OFFLOAD_CHANS)) अणु
		काष्ठा iwl_scan_offload_profile_match *matches =
			(काष्ठा iwl_scan_offload_profile_match *)query->matches;

		क्रम (i = 0; i < SCAN_OFFLOAD_MATCHING_CHANNELS_LEN; i++)
			n_chans += hweight8(matches[idx].matching_channels[i]);
	पूर्ण अन्यथा अणु
		काष्ठा iwl_scan_offload_profile_match_v1 *matches =
			(काष्ठा iwl_scan_offload_profile_match_v1 *)query->matches;

		क्रम (i = 0; i < SCAN_OFFLOAD_MATCHING_CHANNELS_LEN_V1; i++)
			n_chans += hweight8(matches[idx].matching_channels[i]);
	पूर्ण

	वापस n_chans;
पूर्ण

अटल व्योम iwl_mvm_query_set_freqs(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_mvm_nd_query_results *query,
				    काष्ठा cfg80211_wowlan_nd_match *match,
				    पूर्णांक idx)
अणु
	पूर्णांक i;

	अगर (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_SCAN_OFFLOAD_CHANS)) अणु
		काष्ठा iwl_scan_offload_profile_match *matches =
			(काष्ठा iwl_scan_offload_profile_match *)query->matches;

		क्रम (i = 0; i < SCAN_OFFLOAD_MATCHING_CHANNELS_LEN * 8; i++)
			अगर (matches[idx].matching_channels[i / 8] & (BIT(i % 8)))
				match->channels[match->n_channels++] =
					mvm->nd_channels[i]->center_freq;
	पूर्ण अन्यथा अणु
		काष्ठा iwl_scan_offload_profile_match_v1 *matches =
			(काष्ठा iwl_scan_offload_profile_match_v1 *)query->matches;

		क्रम (i = 0; i < SCAN_OFFLOAD_MATCHING_CHANNELS_LEN_V1 * 8; i++)
			अगर (matches[idx].matching_channels[i / 8] & (BIT(i % 8)))
				match->channels[match->n_channels++] =
					mvm->nd_channels[i]->center_freq;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_query_netdetect_reasons(काष्ठा iwl_mvm *mvm,
					    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा cfg80211_wowlan_nd_info *net_detect = शून्य;
	काष्ठा cfg80211_wowlan_wakeup wakeup = अणु
		.pattern_idx = -1,
	पूर्ण;
	काष्ठा cfg80211_wowlan_wakeup *wakeup_report = &wakeup;
	काष्ठा iwl_mvm_nd_query_results query;
	काष्ठा iwl_wowlan_status *fw_status;
	अचिन्हित दीर्घ matched_profiles;
	u32 reasons = 0;
	पूर्णांक i, n_matches, ret;

	fw_status = iwl_mvm_get_wakeup_status(mvm);
	अगर (!IS_ERR_OR_शून्य(fw_status)) अणु
		reasons = le32_to_cpu(fw_status->wakeup_reasons);
		kमुक्त(fw_status);
	पूर्ण

	अगर (reasons & IWL_WOWLAN_WAKEUP_BY_RFKILL_DEASSERTED)
		wakeup.rfसमाप्त_release = true;

	अगर (reasons != IWL_WOWLAN_WAKEUP_BY_NON_WIRELESS)
		जाओ out;

	ret = iwl_mvm_netdetect_query_results(mvm, &query);
	अगर (ret || !query.matched_profiles) अणु
		wakeup_report = शून्य;
		जाओ out;
	पूर्ण

	matched_profiles = query.matched_profiles;
	अगर (mvm->n_nd_match_sets) अणु
		n_matches = hweight_दीर्घ(matched_profiles);
	पूर्ण अन्यथा अणु
		IWL_ERR(mvm, "no net detect match information available\n");
		n_matches = 0;
	पूर्ण

	net_detect = kzalloc(काष्ठा_size(net_detect, matches, n_matches),
			     GFP_KERNEL);
	अगर (!net_detect || !n_matches)
		जाओ out_report_nd;

	क्रम_each_set_bit(i, &matched_profiles, mvm->n_nd_match_sets) अणु
		काष्ठा cfg80211_wowlan_nd_match *match;
		पूर्णांक idx, n_channels = 0;

		n_channels = iwl_mvm_query_num_match_chans(mvm, &query, i);

		match = kzalloc(काष्ठा_size(match, channels, n_channels),
				GFP_KERNEL);
		अगर (!match)
			जाओ out_report_nd;

		net_detect->matches[net_detect->n_matches++] = match;

		/* We inverted the order of the SSIDs in the scan
		 * request, so invert the index here.
		 */
		idx = mvm->n_nd_match_sets - i - 1;
		match->ssid.ssid_len = mvm->nd_match_sets[idx].ssid.ssid_len;
		स_नकल(match->ssid.ssid, mvm->nd_match_sets[idx].ssid.ssid,
		       match->ssid.ssid_len);

		अगर (mvm->n_nd_channels < n_channels)
			जारी;

		iwl_mvm_query_set_freqs(mvm, &query, match, i);
	पूर्ण

out_report_nd:
	wakeup.net_detect = net_detect;
out:
	iwl_mvm_मुक्त_nd(mvm);

	mutex_unlock(&mvm->mutex);
	ieee80211_report_wowlan_wakeup(vअगर, wakeup_report, GFP_KERNEL);

	अगर (net_detect) अणु
		क्रम (i = 0; i < net_detect->n_matches; i++)
			kमुक्त(net_detect->matches[i]);
		kमुक्त(net_detect);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_d3_disconnect_iter(व्योम *data, u8 *mac,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	/* skip the one we keep connection on */
	अगर (data == vअगर)
		वापस;

	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		ieee80211_resume_disconnect(vअगर);
पूर्ण

अटल bool iwl_mvm_rt_status(काष्ठा iwl_trans *trans, u32 base, u32 *err_id)
अणु
	काष्ठा error_table_start अणु
		/* cf. काष्ठा iwl_error_event_table */
		u32 valid;
		__le32 err_id;
	पूर्ण err_info;

	अगर (!base)
		वापस false;

	iwl_trans_पढ़ो_mem_bytes(trans, base,
				 &err_info, माप(err_info));
	अगर (err_info.valid && err_id)
		*err_id = le32_to_cpu(err_info.err_id);

	वापस !!err_info.valid;
पूर्ण

अटल bool iwl_mvm_check_rt_status(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	u32 err_id;

	/* check क्रम lmac1 error */
	अगर (iwl_mvm_rt_status(mvm->trans,
			      mvm->trans->dbg.lmac_error_event_table[0],
			      &err_id)) अणु
		अगर (err_id == RF_KILL_INDICATOR_FOR_WOWLAN) अणु
			काष्ठा cfg80211_wowlan_wakeup wakeup = अणु
				.rfसमाप्त_release = true,
			पूर्ण;
			ieee80211_report_wowlan_wakeup(vअगर, &wakeup,
						       GFP_KERNEL);
		पूर्ण
		वापस true;
	पूर्ण

	/* check अगर we have lmac2 set and check क्रम error */
	अगर (iwl_mvm_rt_status(mvm->trans,
			      mvm->trans->dbg.lmac_error_event_table[1], शून्य))
		वापस true;

	/* check क्रम umac error */
	अगर (iwl_mvm_rt_status(mvm->trans,
			      mvm->trans->dbg.umac_error_event_table, शून्य))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक __iwl_mvm_resume(काष्ठा iwl_mvm *mvm, bool test)
अणु
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	पूर्णांक ret = 1;
	क्रमागत iwl_d3_status d3_status;
	bool keep = false;
	bool unअगरied_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);
	bool d0i3_first = fw_has_capa(&mvm->fw->ucode_capa,
				      IWL_UCODE_TLV_CAPA_D0I3_END_FIRST);

	mutex_lock(&mvm->mutex);

	mvm->last_reset_or_resume_समय_jअगरfies = jअगरfies;

	/* get the BSS vअगर poपूर्णांकer again */
	vअगर = iwl_mvm_get_bss_vअगर(mvm);
	अगर (IS_ERR_OR_शून्य(vअगर))
		जाओ err;

	iwl_fw_dbg_पढ़ो_d3_debug_data(&mvm->fwrt);

	अगर (iwl_mvm_check_rt_status(mvm, vअगर)) अणु
		set_bit(STATUS_FW_ERROR, &mvm->trans->status);
		iwl_mvm_dump_nic_error_log(mvm);
		iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt,
				       IWL_FW_INI_TIME_POINT_FW_ASSERT, शून्य);
		iwl_fw_dbg_collect_desc(&mvm->fwrt, &iwl_dump_desc_निश्चित,
					false, 0);
		ret = 1;
		mvm->trans->प्रणाली_pm_mode = IWL_PLAT_PM_MODE_DISABLED;
		जाओ err;
	पूर्ण

	ret = iwl_trans_d3_resume(mvm->trans, &d3_status, test, !unअगरied_image);
	अगर (ret)
		जाओ err;

	अगर (d3_status != IWL_D3_STATUS_ALIVE) अणु
		IWL_INFO(mvm, "Device was reset during suspend\n");
		जाओ err;
	पूर्ण

	अगर (d0i3_first) अणु
		काष्ठा iwl_host_cmd cmd = अणु
			.id = D0I3_END_CMD,
			.flags = CMD_WANT_SKB | CMD_SEND_IN_D3,
		पूर्ण;
		पूर्णांक len;

		ret = iwl_mvm_send_cmd(mvm, &cmd);
		अगर (ret < 0) अणु
			IWL_ERR(mvm, "Failed to send D0I3_END_CMD first (%d)\n",
				ret);
			जाओ err;
		पूर्ण
		चयन (mvm->cmd_ver.d0i3_resp) अणु
		हाल 0:
			अवरोध;
		हाल 1:
			len = iwl_rx_packet_payload_len(cmd.resp_pkt);
			अगर (len != माप(u32)) अणु
				IWL_ERR(mvm,
					"Error with D0I3_END_CMD response size (%d)\n",
					len);
				जाओ err;
			पूर्ण
			अगर (IWL_D0I3_RESET_REQUIRE &
			    le32_to_cpu(*(__le32 *)cmd.resp_pkt->data)) अणु
				iwl_ग_लिखो32(mvm->trans, CSR_RESET,
					    CSR_RESET_REG_FLAG_FORCE_NMI);
				iwl_मुक्त_resp(&cmd);
			पूर्ण
			अवरोध;
		शेष:
			WARN_ON(1);
		पूर्ण
	पूर्ण

	mvm->trans->प्रणाली_pm_mode = IWL_PLAT_PM_MODE_DISABLED;

	/*
	 * Query the current location and source from the D3 firmware so we
	 * can play it back when we re-पूर्णांकiailize the D0 firmware
	 */
	iwl_mvm_update_changed_regकरोm(mvm);

	/* Re-configure PPAG settings */
	iwl_mvm_ppag_send_cmd(mvm);

	अगर (!unअगरied_image)
		/*  Re-configure शेष SAR profile */
		iwl_mvm_sar_select_profile(mvm, 1, 1);

	अगर (mvm->net_detect) अणु
		/* If this is a non-unअगरied image, we restart the FW,
		 * so no need to stop the netdetect scan.  If that
		 * fails, जारी and try to get the wake-up reasons,
		 * but trigger a HW restart by keeping a failure code
		 * in ret.
		 */
		अगर (unअगरied_image)
			ret = iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_NETDETECT,
						false);

		iwl_mvm_query_netdetect_reasons(mvm, vअगर);
		/* has unlocked the mutex, so skip that */
		जाओ out;
	पूर्ण अन्यथा अणु
		keep = iwl_mvm_query_wakeup_reasons(mvm, vअगर);
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
		अगर (keep)
			mvm->keep_vअगर = vअगर;
#पूर्ण_अगर
		/* has unlocked the mutex, so skip that */
		जाओ out_iterate;
	पूर्ण

err:
	iwl_mvm_मुक्त_nd(mvm);
	mutex_unlock(&mvm->mutex);

out_iterate:
	अगर (!test)
		ieee80211_iterate_active_पूर्णांकerfaces_mtx(mvm->hw,
			IEEE80211_IFACE_ITER_NORMAL,
			iwl_mvm_d3_disconnect_iter, keep ? vअगर : शून्य);

out:
	clear_bit(IWL_MVM_STATUS_IN_D3, &mvm->status);

	/* no need to reset the device in unअगरied images, अगर successful */
	अगर (unअगरied_image && !ret) अणु
		/* nothing अन्यथा to करो अगर we alपढ़ोy sent D0I3_END_CMD */
		अगर (d0i3_first)
			वापस 0;

		ret = iwl_mvm_send_cmd_pdu(mvm, D0I3_END_CMD, 0, 0, शून्य);
		अगर (!ret)
			वापस 0;
	पूर्ण

	/*
	 * Reconfigure the device in one of the following हालs:
	 * 1. We are not using a unअगरied image
	 * 2. We are using a unअगरied image but had an error जबतक निकासing D3
	 */
	set_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status);

	वापस 1;
पूर्ण

पूर्णांक iwl_mvm_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	पूर्णांक ret;

	ret = __iwl_mvm_resume(mvm, false);

	iwl_mvm_resume_tcm(mvm);

	iwl_fw_runसमय_resume(&mvm->fwrt);

	वापस ret;
पूर्ण

व्योम iwl_mvm_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	device_set_wakeup_enable(mvm->trans->dev, enabled);
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
अटल पूर्णांक iwl_mvm_d3_test_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा iwl_mvm *mvm = inode->i_निजी;
	पूर्णांक err;

	अगर (mvm->d3_test_active)
		वापस -EBUSY;

	file->निजी_data = inode->i_निजी;

	iwl_mvm_छोड़ो_tcm(mvm, true);

	iwl_fw_runसमय_suspend(&mvm->fwrt);

	/* start pseuकरो D3 */
	rtnl_lock();
	err = __iwl_mvm_suspend(mvm->hw, mvm->hw->wiphy->wowlan_config, true);
	rtnl_unlock();
	अगर (err > 0)
		err = -EINVAL;
	अगर (err)
		वापस err;

	mvm->d3_test_active = true;
	mvm->keep_vअगर = शून्य;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार iwl_mvm_d3_test_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = file->निजी_data;
	u32 pme_निश्चितed;

	जबतक (true) अणु
		/* पढ़ो pme_ptr अगर available */
		अगर (mvm->d3_test_pme_ptr) अणु
			pme_निश्चितed = iwl_trans_पढ़ो_mem32(mvm->trans,
						mvm->d3_test_pme_ptr);
			अगर (pme_निश्चितed)
				अवरोध;
		पूर्ण

		अगर (msleep_पूर्णांकerruptible(100))
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_d3_test_disconn_work_iter(व्योम *_data, u8 *mac,
					      काष्ठा ieee80211_vअगर *vअगर)
अणु
	/* skip the one we keep connection on */
	अगर (_data == vअगर)
		वापस;

	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		ieee80211_connection_loss(vअगर);
पूर्ण

अटल पूर्णांक iwl_mvm_d3_test_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा iwl_mvm *mvm = inode->i_निजी;
	bool unअगरied_image = fw_has_capa(&mvm->fw->ucode_capa,
					 IWL_UCODE_TLV_CAPA_CNSLDTD_D3_D0_IMG);

	mvm->d3_test_active = false;

	iwl_fw_dbg_पढ़ो_d3_debug_data(&mvm->fwrt);

	rtnl_lock();
	__iwl_mvm_resume(mvm, true);
	rtnl_unlock();

	iwl_mvm_resume_tcm(mvm);

	iwl_fw_runसमय_resume(&mvm->fwrt);

	iwl_पात_notअगरication_रुकोs(&mvm->notअगर_रुको);
	अगर (!unअगरied_image) अणु
		पूर्णांक reमुख्यing_समय = 10;

		ieee80211_restart_hw(mvm->hw);

		/* रुको क्रम restart and disconnect all पूर्णांकerfaces */
		जबतक (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		       reमुख्यing_समय > 0) अणु
			reमुख्यing_समय--;
			msleep(1000);
		पूर्ण

		अगर (reमुख्यing_समय == 0)
			IWL_ERR(mvm, "Timed out waiting for HW restart!\n");
	पूर्ण

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_NORMAL,
		iwl_mvm_d3_test_disconn_work_iter, mvm->keep_vअगर);

	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations iwl_dbgfs_d3_test_ops = अणु
	.llseek = no_llseek,
	.खोलो = iwl_mvm_d3_test_खोलो,
	.पढ़ो = iwl_mvm_d3_test_पढ़ो,
	.release = iwl_mvm_d3_test_release,
पूर्ण;
#पूर्ण_अगर
