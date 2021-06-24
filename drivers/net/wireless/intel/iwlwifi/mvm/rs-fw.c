<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */
#समावेश "rs.h"
#समावेश "fw-api.h"
#समावेश "sta.h"
#समावेश "iwl-op-mode.h"
#समावेश "mvm.h"

अटल u8 rs_fw_bw_from_sta_bw(काष्ठा ieee80211_sta *sta)
अणु
	चयन (sta->bandwidth) अणु
	हाल IEEE80211_STA_RX_BW_160:
		वापस IWL_TLC_MNG_CH_WIDTH_160MHZ;
	हाल IEEE80211_STA_RX_BW_80:
		वापस IWL_TLC_MNG_CH_WIDTH_80MHZ;
	हाल IEEE80211_STA_RX_BW_40:
		वापस IWL_TLC_MNG_CH_WIDTH_40MHZ;
	हाल IEEE80211_STA_RX_BW_20:
	शेष:
		वापस IWL_TLC_MNG_CH_WIDTH_20MHZ;
	पूर्ण
पूर्ण

अटल u8 rs_fw_set_active_chains(u8 chains)
अणु
	u8 fw_chains = 0;

	अगर (chains & ANT_A)
		fw_chains |= IWL_TLC_MNG_CHAIN_A_MSK;
	अगर (chains & ANT_B)
		fw_chains |= IWL_TLC_MNG_CHAIN_B_MSK;
	अगर (chains & ANT_C)
		WARN(false,
		     "tlc offload doesn't support antenna C. chains: 0x%x\n",
		     chains);

	वापस fw_chains;
पूर्ण

अटल u8 rs_fw_sgi_cw_support(काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	काष्ठा ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	u8 supp = 0;

	अगर (he_cap->has_he)
		वापस 0;

	अगर (ht_cap->cap & IEEE80211_HT_CAP_SGI_20)
		supp |= BIT(IWL_TLC_MNG_CH_WIDTH_20MHZ);
	अगर (ht_cap->cap & IEEE80211_HT_CAP_SGI_40)
		supp |= BIT(IWL_TLC_MNG_CH_WIDTH_40MHZ);
	अगर (vht_cap->cap & IEEE80211_VHT_CAP_SHORT_GI_80)
		supp |= BIT(IWL_TLC_MNG_CH_WIDTH_80MHZ);
	अगर (vht_cap->cap & IEEE80211_VHT_CAP_SHORT_GI_160)
		supp |= BIT(IWL_TLC_MNG_CH_WIDTH_160MHZ);

	वापस supp;
पूर्ण

अटल u16 rs_fw_get_config_flags(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा ieee80211_supported_band *sband)
अणु
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	काष्ठा ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	bool vht_ena = vht_cap->vht_supported;
	u16 flags = 0;

	/* get STBC flags */
	अगर (mvm->cfg->ht_params->stbc &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1)) अणु
		अगर (he_cap->has_he && he_cap->he_cap_elem.phy_cap_info[2] &
				      IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ)
			flags |= IWL_TLC_MNG_CFG_FLAGS_STBC_MSK;
		अन्यथा अगर (vht_cap->cap & IEEE80211_VHT_CAP_RXSTBC_MASK)
			flags |= IWL_TLC_MNG_CFG_FLAGS_STBC_MSK;
		अन्यथा अगर (ht_cap->cap & IEEE80211_HT_CAP_RX_STBC)
			flags |= IWL_TLC_MNG_CFG_FLAGS_STBC_MSK;
	पूर्ण

	अगर (mvm->cfg->ht_params->ldpc &&
	    ((ht_cap->cap & IEEE80211_HT_CAP_LDPC_CODING) ||
	     (vht_ena && (vht_cap->cap & IEEE80211_VHT_CAP_RXLDPC))))
		flags |= IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK;

	/* consider LDPC support in हाल of HE */
	अगर (he_cap->has_he && (he_cap->he_cap_elem.phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD))
		flags |= IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK;

	अगर (sband->अगरtype_data && sband->अगरtype_data->he_cap.has_he &&
	    !(sband->अगरtype_data->he_cap.he_cap_elem.phy_cap_info[1] &
	     IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD))
		flags &= ~IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK;

	अगर (he_cap->has_he &&
	    (he_cap->he_cap_elem.phy_cap_info[3] &
	     IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_MASK))
		flags |= IWL_TLC_MNG_CFG_FLAGS_HE_DCM_NSS_1_MSK;

	वापस flags;
पूर्ण

अटल
पूर्णांक rs_fw_vht_highest_rx_mcs_index(स्थिर काष्ठा ieee80211_sta_vht_cap *vht_cap,
				   पूर्णांक nss)
अणु
	u16 rx_mcs = le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map) &
		(0x3 << (2 * (nss - 1)));
	rx_mcs >>= (2 * (nss - 1));

	चयन (rx_mcs) अणु
	हाल IEEE80211_VHT_MCS_SUPPORT_0_7:
		वापस IWL_TLC_MNG_HT_RATE_MCS7;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_8:
		वापस IWL_TLC_MNG_HT_RATE_MCS8;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_9:
		वापस IWL_TLC_MNG_HT_RATE_MCS9;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
rs_fw_vht_set_enabled_rates(स्थिर काष्ठा ieee80211_sta *sta,
			    स्थिर काष्ठा ieee80211_sta_vht_cap *vht_cap,
			    काष्ठा iwl_tlc_config_cmd *cmd)
अणु
	u16 supp;
	पूर्णांक i, highest_mcs;
	u8 max_nss = sta->rx_nss;
	काष्ठा ieee80211_vht_cap ieee_vht_cap = अणु
		.vht_cap_info = cpu_to_le32(vht_cap->cap),
		.supp_mcs = vht_cap->vht_mcs,
	पूर्ण;

	/* the station support only a single receive chain */
	अगर (sta->smps_mode == IEEE80211_SMPS_STATIC)
		max_nss = 1;

	क्रम (i = 0; i < max_nss && i < IWL_TLC_NSS_MAX; i++) अणु
		पूर्णांक nss = i + 1;

		highest_mcs = rs_fw_vht_highest_rx_mcs_index(vht_cap, nss);
		अगर (!highest_mcs)
			जारी;

		supp = BIT(highest_mcs + 1) - 1;
		अगर (sta->bandwidth == IEEE80211_STA_RX_BW_20)
			supp &= ~BIT(IWL_TLC_MNG_HT_RATE_MCS9);

		cmd->ht_rates[i][IWL_TLC_HT_BW_NONE_160] = cpu_to_le16(supp);
		/*
		 * Check अगर VHT extended NSS indicates that the bandwidth/NSS
		 * configuration is supported - only क्रम MCS 0 since we alपढ़ोy
		 * decoded the MCS bits anyway ourselves.
		 */
		अगर (sta->bandwidth == IEEE80211_STA_RX_BW_160 &&
		    ieee80211_get_vht_max_nss(&ieee_vht_cap,
					      IEEE80211_VHT_CHANWIDTH_160MHZ,
					      0, true, nss) >= nss)
			cmd->ht_rates[i][IWL_TLC_HT_BW_160] =
				cmd->ht_rates[i][IWL_TLC_HT_BW_NONE_160];
	पूर्ण
पूर्ण

अटल u16 rs_fw_he_ieee80211_mcs_to_rs_mcs(u16 mcs)
अणु
	चयन (mcs) अणु
	हाल IEEE80211_HE_MCS_SUPPORT_0_7:
		वापस BIT(IWL_TLC_MNG_HT_RATE_MCS7 + 1) - 1;
	हाल IEEE80211_HE_MCS_SUPPORT_0_9:
		वापस BIT(IWL_TLC_MNG_HT_RATE_MCS9 + 1) - 1;
	हाल IEEE80211_HE_MCS_SUPPORT_0_11:
		वापस BIT(IWL_TLC_MNG_HT_RATE_MCS11 + 1) - 1;
	हाल IEEE80211_HE_MCS_NOT_SUPPORTED:
		वापस 0;
	पूर्ण

	WARN(1, "invalid HE MCS %d\n", mcs);
	वापस 0;
पूर्ण

अटल व्योम
rs_fw_he_set_enabled_rates(स्थिर काष्ठा ieee80211_sta *sta,
			   काष्ठा ieee80211_supported_band *sband,
			   काष्ठा iwl_tlc_config_cmd *cmd)
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	u16 mcs_160 = le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_160);
	u16 mcs_80 = le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_80);
	u16 tx_mcs_80 =
		le16_to_cpu(sband->अगरtype_data->he_cap.he_mcs_nss_supp.tx_mcs_80);
	u16 tx_mcs_160 =
		le16_to_cpu(sband->अगरtype_data->he_cap.he_mcs_nss_supp.tx_mcs_160);
	पूर्णांक i;
	u8 nss = sta->rx_nss;

	/* the station support only a single receive chain */
	अगर (sta->smps_mode == IEEE80211_SMPS_STATIC)
		nss = 1;

	क्रम (i = 0; i < nss && i < IWL_TLC_NSS_MAX; i++) अणु
		u16 _mcs_160 = (mcs_160 >> (2 * i)) & 0x3;
		u16 _mcs_80 = (mcs_80 >> (2 * i)) & 0x3;
		u16 _tx_mcs_160 = (tx_mcs_160 >> (2 * i)) & 0x3;
		u16 _tx_mcs_80 = (tx_mcs_80 >> (2 * i)) & 0x3;

		/* If one side करोesn't support - mark both as not supporting */
		अगर (_mcs_80 == IEEE80211_HE_MCS_NOT_SUPPORTED ||
		    _tx_mcs_80 == IEEE80211_HE_MCS_NOT_SUPPORTED) अणु
			_mcs_80 = IEEE80211_HE_MCS_NOT_SUPPORTED;
			_tx_mcs_80 = IEEE80211_HE_MCS_NOT_SUPPORTED;
		पूर्ण
		अगर (_mcs_80 > _tx_mcs_80)
			_mcs_80 = _tx_mcs_80;
		cmd->ht_rates[i][IWL_TLC_HT_BW_NONE_160] =
			cpu_to_le16(rs_fw_he_ieee80211_mcs_to_rs_mcs(_mcs_80));

		/* If one side करोesn't support - mark both as not supporting */
		अगर (_mcs_160 == IEEE80211_HE_MCS_NOT_SUPPORTED ||
		    _tx_mcs_160 == IEEE80211_HE_MCS_NOT_SUPPORTED) अणु
			_mcs_160 = IEEE80211_HE_MCS_NOT_SUPPORTED;
			_tx_mcs_160 = IEEE80211_HE_MCS_NOT_SUPPORTED;
		पूर्ण
		अगर (_mcs_160 > _tx_mcs_160)
			_mcs_160 = _tx_mcs_160;
		cmd->ht_rates[i][IWL_TLC_HT_BW_160] =
			cpu_to_le16(rs_fw_he_ieee80211_mcs_to_rs_mcs(_mcs_160));
	पूर्ण
पूर्ण

अटल व्योम rs_fw_set_supp_rates(काष्ठा ieee80211_sta *sta,
				 काष्ठा ieee80211_supported_band *sband,
				 काष्ठा iwl_tlc_config_cmd *cmd)
अणु
	पूर्णांक i;
	u16 supp = 0;
	अचिन्हित दीर्घ पंचांगp; /* must be अचिन्हित दीर्घ क्रम क्रम_each_set_bit */
	स्थिर काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	स्थिर काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap = &sta->he_cap;

	/* non HT rates */
	पंचांगp = sta->supp_rates[sband->band];
	क्रम_each_set_bit(i, &पंचांगp, BITS_PER_LONG)
		supp |= BIT(sband->bitrates[i].hw_value);

	cmd->non_ht_rates = cpu_to_le16(supp);
	cmd->mode = IWL_TLC_MNG_MODE_NON_HT;

	/* HT/VHT rates */
	अगर (he_cap->has_he) अणु
		cmd->mode = IWL_TLC_MNG_MODE_HE;
		rs_fw_he_set_enabled_rates(sta, sband, cmd);
	पूर्ण अन्यथा अगर (vht_cap->vht_supported) अणु
		cmd->mode = IWL_TLC_MNG_MODE_VHT;
		rs_fw_vht_set_enabled_rates(sta, vht_cap, cmd);
	पूर्ण अन्यथा अगर (ht_cap->ht_supported) अणु
		cmd->mode = IWL_TLC_MNG_MODE_HT;
		cmd->ht_rates[IWL_TLC_NSS_1][IWL_TLC_HT_BW_NONE_160] =
			cpu_to_le16(ht_cap->mcs.rx_mask[0]);

		/* the station support only a single receive chain */
		अगर (sta->smps_mode == IEEE80211_SMPS_STATIC)
			cmd->ht_rates[IWL_TLC_NSS_2][IWL_TLC_HT_BW_NONE_160] =
				0;
		अन्यथा
			cmd->ht_rates[IWL_TLC_NSS_2][IWL_TLC_HT_BW_NONE_160] =
				cpu_to_le16(ht_cap->mcs.rx_mask[1]);
	पूर्ण
पूर्ण

व्योम iwl_mvm_tlc_update_notअगर(काष्ठा iwl_mvm *mvm,
			      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_tlc_update_notअगर *notअगर;
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा iwl_lq_sta_rs_fw *lq_sta;
	u32 flags;

	rcu_पढ़ो_lock();

	notअगर = (व्योम *)pkt->data;
	sta = rcu_dereference(mvm->fw_id_to_mac_id[notअगर->sta_id]);
	अगर (IS_ERR_OR_शून्य(sta)) अणु
		IWL_ERR(mvm, "Invalid sta id (%d) in FW TLC notification\n",
			notअगर->sta_id);
		जाओ out;
	पूर्ण

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	अगर (!mvmsta) अणु
		IWL_ERR(mvm, "Invalid sta id (%d) in FW TLC notification\n",
			notअगर->sta_id);
		जाओ out;
	पूर्ण

	flags = le32_to_cpu(notअगर->flags);

	lq_sta = &mvmsta->lq_sta.rs_fw;

	अगर (flags & IWL_TLC_NOTIF_FLAG_RATE) अणु
		अक्षर pretty_rate[100];
		lq_sta->last_rate_n_flags = le32_to_cpu(notअगर->rate);
		rs_pretty_prपूर्णांक_rate(pretty_rate, माप(pretty_rate),
				     lq_sta->last_rate_n_flags);
		IWL_DEBUG_RATE(mvm, "new rate: %s\n", pretty_rate);
	पूर्ण

	अगर (flags & IWL_TLC_NOTIF_FLAG_AMSDU && !mvmsta->orig_amsdu_len) अणु
		u16 size = le32_to_cpu(notअगर->amsdu_size);
		पूर्णांक i;

		अगर (sta->max_amsdu_len < size) अणु
			/*
			 * In debug sta->max_amsdu_len < size
			 * so also check with orig_amsdu_len which holds the
			 * original data beक्रमe debugfs changed the value
			 */
			WARN_ON(mvmsta->orig_amsdu_len < size);
			जाओ out;
		पूर्ण

		mvmsta->amsdu_enabled = le32_to_cpu(notअगर->amsdu_enabled);
		mvmsta->max_amsdu_len = size;
		sta->max_rc_amsdu_len = mvmsta->max_amsdu_len;

		क्रम (i = 0; i < IWL_MAX_TID_COUNT; i++) अणु
			अगर (mvmsta->amsdu_enabled & BIT(i))
				sta->max_tid_amsdu_len[i] =
					iwl_mvm_max_amsdu_size(mvm, sta, i);
			अन्यथा
				/*
				 * Not so elegant, but this will effectively
				 * prevent AMSDU on this TID
				 */
				sta->max_tid_amsdu_len[i] = 1;
		पूर्ण

		IWL_DEBUG_RATE(mvm,
			       "AMSDU update. AMSDU size: %d, AMSDU selected size: %d, AMSDU TID bitmap 0x%X\n",
			       le32_to_cpu(notअगर->amsdu_size), size,
			       mvmsta->amsdu_enabled);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
पूर्ण

u16 rs_fw_get_max_amsdu_len(काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	स्थिर काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	स्थिर काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;

	अगर (mvmsta->vअगर->bss_conf.chandef.chan->band == NL80211_BAND_6GHZ) अणु
		चयन (le16_get_bits(sta->he_6ghz_capa.capa,
				      IEEE80211_HE_6GHZ_CAP_MAX_MPDU_LEN)) अणु
		हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454:
			वापस IEEE80211_MAX_MPDU_LEN_VHT_11454;
		हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991:
			वापस IEEE80211_MAX_MPDU_LEN_VHT_7991;
		शेष:
			वापस IEEE80211_MAX_MPDU_LEN_VHT_3895;
		पूर्ण
	पूर्ण अन्यथा
	अगर (vht_cap->vht_supported) अणु
		चयन (vht_cap->cap & IEEE80211_VHT_CAP_MAX_MPDU_MASK) अणु
		हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454:
			वापस IEEE80211_MAX_MPDU_LEN_VHT_11454;
		हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991:
			वापस IEEE80211_MAX_MPDU_LEN_VHT_7991;
		शेष:
			वापस IEEE80211_MAX_MPDU_LEN_VHT_3895;
		पूर्ण
	पूर्ण अन्यथा अगर (ht_cap->ht_supported) अणु
		अगर (ht_cap->cap & IEEE80211_HT_CAP_MAX_AMSDU)
			/*
			 * agg is offloaded so we need to assume that agg
			 * are enabled and max mpdu in ampdu is 4095
			 * (spec 802.11-2016 9.3.2.1)
			 */
			वापस IEEE80211_MAX_MPDU_LEN_HT_BA;
		अन्यथा
			वापस IEEE80211_MAX_MPDU_LEN_HT_3839;
	पूर्ण

	/* in legacy mode no amsdu is enabled so वापस zero */
	वापस 0;
पूर्ण

व्योम rs_fw_rate_init(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
		     क्रमागत nl80211_band band, bool update)
अणु
	काष्ठा ieee80211_hw *hw = mvm->hw;
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_lq_sta_rs_fw *lq_sta = &mvmsta->lq_sta.rs_fw;
	u32 cmd_id = iwl_cmd_id(TLC_MNG_CONFIG_CMD, DATA_PATH_GROUP, 0);
	काष्ठा ieee80211_supported_band *sband = hw->wiphy->bands[band];
	u16 max_amsdu_len = rs_fw_get_max_amsdu_len(sta);
	काष्ठा iwl_tlc_config_cmd cfg_cmd = अणु
		.sta_id = mvmsta->sta_id,
		.max_ch_width = update ?
			rs_fw_bw_from_sta_bw(sta) : RATE_MCS_CHAN_WIDTH_20,
		.flags = cpu_to_le16(rs_fw_get_config_flags(mvm, sta, sband)),
		.chains = rs_fw_set_active_chains(iwl_mvm_get_valid_tx_ant(mvm)),
		.sgi_ch_width_supp = rs_fw_sgi_cw_support(sta),
		.max_mpdu_len = cpu_to_le16(max_amsdu_len),
		.amsdu = iwl_mvm_is_csum_supported(mvm),
	पूर्ण;
	पूर्णांक ret;
	u16 cmd_size = माप(cfg_cmd);

	/* In old versions of the API the काष्ठा is 4 bytes smaller */
	अगर (iwl_fw_lookup_cmd_ver(mvm->fw, DATA_PATH_GROUP,
				  TLC_MNG_CONFIG_CMD, 0) < 3)
		cmd_size -= 4;

	स_रखो(lq_sta, 0, दुरत्व(typeof(*lq_sta), pers));

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	iwl_mvm_reset_frame_stats(mvm);
#पूर्ण_अगर
	rs_fw_set_supp_rates(sta, sband, &cfg_cmd);

	/*
	 * since TLC offload works with one mode we can assume
	 * that only vht/ht is used and also set it as station max amsdu
	 */
	sta->max_amsdu_len = max_amsdu_len;

	ret = iwl_mvm_send_cmd_pdu(mvm, cmd_id, CMD_ASYNC, cmd_size,
				   &cfg_cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send rate scale config (%d)\n", ret);
पूर्ण

पूर्णांक rs_fw_tx_protection(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta,
			bool enable)
अणु
	/* TODO: need to पूर्णांकroduce a new FW cmd since LQ cmd is not relevant */
	IWL_DEBUG_RATE(mvm, "tx protection - not implemented yet.\n");
	वापस 0;
पूर्ण

व्योम iwl_mvm_rs_add_sta(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta)
अणु
	काष्ठा iwl_lq_sta_rs_fw *lq_sta = &mvmsta->lq_sta.rs_fw;

	IWL_DEBUG_RATE(mvm, "create station rate scale window\n");

	lq_sta->pers.drv = mvm;
	lq_sta->pers.sta_id = mvmsta->sta_id;
	lq_sta->pers.chains = 0;
	स_रखो(lq_sta->pers.chain_संकेत, 0, माप(lq_sta->pers.chain_संकेत));
	lq_sta->pers.last_rssi = S8_MIN;
	lq_sta->last_rate_n_flags = 0;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	lq_sta->pers.dbg_fixed_rate = 0;
#पूर्ण_अगर
पूर्ण
