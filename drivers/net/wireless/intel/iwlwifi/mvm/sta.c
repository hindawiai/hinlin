<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2015, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <net/mac80211.h>

#समावेश "mvm.h"
#समावेश "sta.h"
#समावेश "rs.h"

/*
 * New version of ADD_STA_sta command added new fields at the end of the
 * काष्ठाure, so sending the size of the relevant API's काष्ठाure is enough to
 * support both API versions.
 */
अटल अंतरभूत पूर्णांक iwl_mvm_add_sta_cmd_size(काष्ठा iwl_mvm *mvm)
अणु
	अगर (iwl_mvm_has_new_rx_api(mvm) ||
	    fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE))
		वापस माप(काष्ठा iwl_mvm_add_sta_cmd);
	अन्यथा
		वापस माप(काष्ठा iwl_mvm_add_sta_cmd_v7);
पूर्ण

अटल पूर्णांक iwl_mvm_find_मुक्त_sta_id(काष्ठा iwl_mvm *mvm,
				    क्रमागत nl80211_अगरtype अगरtype)
अणु
	पूर्णांक sta_id;
	u32 reserved_ids = 0;

	BUILD_BUG_ON(IWL_MVM_STATION_COUNT_MAX > 32);
	WARN_ON_ONCE(test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status));

	lockdep_निश्चित_held(&mvm->mutex);

	/* d0i3/d3 assumes the AP's sta_id (of sta vअगर) is 0. reserve it. */
	अगर (अगरtype != NL80211_IFTYPE_STATION)
		reserved_ids = BIT(0);

	/* Don't take rcu_पढ़ो_lock() since we are रक्षित by mvm->mutex */
	क्रम (sta_id = 0; sta_id < mvm->fw->ucode_capa.num_stations; sta_id++) अणु
		अगर (BIT(sta_id) & reserved_ids)
			जारी;

		अगर (!rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[sta_id],
					       lockdep_is_held(&mvm->mutex)))
			वापस sta_id;
	पूर्ण
	वापस IWL_MVM_INVALID_STA;
पूर्ण

/* send station add/update command to firmware */
पूर्णांक iwl_mvm_sta_send_to_fw(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			   bool update, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_add_sta_cmd add_sta_cmd = अणु
		.sta_id = mvm_sta->sta_id,
		.mac_id_n_color = cpu_to_le32(mvm_sta->mac_id_n_color),
		.add_modअगरy = update ? 1 : 0,
		.station_flags_msk = cpu_to_le32(STA_FLG_FAT_EN_MSK |
						 STA_FLG_MIMO_EN_MSK |
						 STA_FLG_RTS_MIMO_PROT),
		.tid_disable_tx = cpu_to_le16(mvm_sta->tid_disable_agg),
	पूर्ण;
	पूर्णांक ret;
	u32 status;
	u32 agg_size = 0, mpdu_dens = 0;

	अगर (fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE))
		add_sta_cmd.station_type = mvm_sta->sta_type;

	अगर (!update || (flags & STA_MODIFY_QUEUES)) अणु
		स_नकल(&add_sta_cmd.addr, sta->addr, ETH_ALEN);

		अगर (!iwl_mvm_has_new_tx_api(mvm)) अणु
			add_sta_cmd.tfd_queue_msk =
				cpu_to_le32(mvm_sta->tfd_queue_msk);

			अगर (flags & STA_MODIFY_QUEUES)
				add_sta_cmd.modअगरy_mask |= STA_MODIFY_QUEUES;
		पूर्ण अन्यथा अणु
			WARN_ON(flags & STA_MODIFY_QUEUES);
		पूर्ण
	पूर्ण

	चयन (sta->bandwidth) अणु
	हाल IEEE80211_STA_RX_BW_160:
		add_sta_cmd.station_flags |= cpu_to_le32(STA_FLG_FAT_EN_160MHZ);
		fallthrough;
	हाल IEEE80211_STA_RX_BW_80:
		add_sta_cmd.station_flags |= cpu_to_le32(STA_FLG_FAT_EN_80MHZ);
		fallthrough;
	हाल IEEE80211_STA_RX_BW_40:
		add_sta_cmd.station_flags |= cpu_to_le32(STA_FLG_FAT_EN_40MHZ);
		fallthrough;
	हाल IEEE80211_STA_RX_BW_20:
		अगर (sta->ht_cap.ht_supported)
			add_sta_cmd.station_flags |=
				cpu_to_le32(STA_FLG_FAT_EN_20MHZ);
		अवरोध;
	पूर्ण

	चयन (sta->rx_nss) अणु
	हाल 1:
		add_sta_cmd.station_flags |= cpu_to_le32(STA_FLG_MIMO_EN_SISO);
		अवरोध;
	हाल 2:
		add_sta_cmd.station_flags |= cpu_to_le32(STA_FLG_MIMO_EN_MIMO2);
		अवरोध;
	हाल 3 ... 8:
		add_sta_cmd.station_flags |= cpu_to_le32(STA_FLG_MIMO_EN_MIMO3);
		अवरोध;
	पूर्ण

	चयन (sta->smps_mode) अणु
	हाल IEEE80211_SMPS_AUTOMATIC:
	हाल IEEE80211_SMPS_NUM_MODES:
		WARN_ON(1);
		अवरोध;
	हाल IEEE80211_SMPS_STATIC:
		/* override NSS */
		add_sta_cmd.station_flags &= ~cpu_to_le32(STA_FLG_MIMO_EN_MSK);
		add_sta_cmd.station_flags |= cpu_to_le32(STA_FLG_MIMO_EN_SISO);
		अवरोध;
	हाल IEEE80211_SMPS_DYNAMIC:
		add_sta_cmd.station_flags |= cpu_to_le32(STA_FLG_RTS_MIMO_PROT);
		अवरोध;
	हाल IEEE80211_SMPS_OFF:
		/* nothing */
		अवरोध;
	पूर्ण

	अगर (sta->ht_cap.ht_supported) अणु
		add_sta_cmd.station_flags_msk |=
			cpu_to_le32(STA_FLG_MAX_AGG_SIZE_MSK |
				    STA_FLG_AGG_MPDU_DENS_MSK);

		mpdu_dens = sta->ht_cap.ampdu_density;
	पूर्ण

	अगर (mvm_sta->vअगर->bss_conf.chandef.chan->band == NL80211_BAND_6GHZ) अणु
		add_sta_cmd.station_flags_msk |=
			cpu_to_le32(STA_FLG_MAX_AGG_SIZE_MSK |
				    STA_FLG_AGG_MPDU_DENS_MSK);

		mpdu_dens = le16_get_bits(sta->he_6ghz_capa.capa,
					  IEEE80211_HE_6GHZ_CAP_MIN_MPDU_START);
		agg_size = le16_get_bits(sta->he_6ghz_capa.capa,
				IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_LEN_EXP);
	पूर्ण अन्यथा
	अगर (sta->vht_cap.vht_supported) अणु
		agg_size = sta->vht_cap.cap &
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
		agg_size >>=
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;
	पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported) अणु
		agg_size = sta->ht_cap.ampdu_factor;
	पूर्ण

	/* D6.0 10.12.2 A-MPDU length limit rules
	 * A STA indicates the maximum length of the A-MPDU preखातापूर्ण padding
	 * that it can receive in an HE PPDU in the Maximum A-MPDU Length
	 * Exponent field in its HT Capabilities, VHT Capabilities,
	 * and HE 6 GHz Band Capabilities elements (अगर present) and the
	 * Maximum AMPDU Length Exponent Extension field in its HE
	 * Capabilities element
	 */
	अगर (sta->he_cap.has_he)
		agg_size += u8_get_bits(sta->he_cap.he_cap_elem.mac_cap_info[3],
					IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_MASK);

	/* Limit to max A-MPDU supported by FW */
	अगर (agg_size > (STA_FLG_MAX_AGG_SIZE_4M >> STA_FLG_MAX_AGG_SIZE_SHIFT))
		agg_size = (STA_FLG_MAX_AGG_SIZE_4M >>
			    STA_FLG_MAX_AGG_SIZE_SHIFT);

	add_sta_cmd.station_flags |=
		cpu_to_le32(agg_size << STA_FLG_MAX_AGG_SIZE_SHIFT);
	add_sta_cmd.station_flags |=
		cpu_to_le32(mpdu_dens << STA_FLG_AGG_MPDU_DENS_SHIFT);
	अगर (mvm_sta->sta_state >= IEEE80211_STA_ASSOC)
		add_sta_cmd.assoc_id = cpu_to_le16(sta->aid);

	अगर (sta->wme) अणु
		add_sta_cmd.modअगरy_mask |= STA_MODIFY_UAPSD_ACS;

		अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)
			add_sta_cmd.uapsd_acs |= BIT(AC_BK);
		अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE)
			add_sta_cmd.uapsd_acs |= BIT(AC_BE);
		अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI)
			add_sta_cmd.uapsd_acs |= BIT(AC_VI);
		अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
			add_sta_cmd.uapsd_acs |= BIT(AC_VO);
		add_sta_cmd.uapsd_acs |= add_sta_cmd.uapsd_acs << 4;
		add_sta_cmd.sp_length = sta->max_sp ? sta->max_sp * 2 : 128;
	पूर्ण

	status = ADD_STA_SUCCESS;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA,
					  iwl_mvm_add_sta_cmd_size(mvm),
					  &add_sta_cmd, &status);
	अगर (ret)
		वापस ret;

	चयन (status & IWL_ADD_STA_STATUS_MASK) अणु
	हाल ADD_STA_SUCCESS:
		IWL_DEBUG_ASSOC(mvm, "ADD_STA PASSED\n");
		अवरोध;
	शेष:
		ret = -EIO;
		IWL_ERR(mvm, "ADD_STA failed\n");
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_rx_agg_session_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा iwl_mvm_baid_data *data =
		from_समयr(data, t, session_समयr);
	काष्ठा iwl_mvm_baid_data __rcu **rcu_ptr = data->rcu_ptr;
	काष्ठा iwl_mvm_baid_data *ba_data;
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvm_sta;
	अचिन्हित दीर्घ समयout;

	rcu_पढ़ो_lock();

	ba_data = rcu_dereference(*rcu_ptr);

	अगर (WARN_ON(!ba_data))
		जाओ unlock;

	अगर (!ba_data->समयout)
		जाओ unlock;

	समयout = ba_data->last_rx + TU_TO_JIFFIES(ba_data->समयout * 2);
	अगर (समय_is_after_jअगरfies(समयout)) अणु
		mod_समयr(&ba_data->session_समयr, समयout);
		जाओ unlock;
	पूर्ण

	/* Timer expired */
	sta = rcu_dereference(ba_data->mvm->fw_id_to_mac_id[ba_data->sta_id]);

	/*
	 * sta should be valid unless the following happens:
	 * The firmware निश्चितs which triggers a reconfig flow, but
	 * the reconfig fails beक्रमe we set the poपूर्णांकer to sta पूर्णांकo
	 * the fw_id_to_mac_id poपूर्णांकer table. Mac80211 can't stop
	 * A-MDPU and hence the समयr जारीs to run. Then, the
	 * समयr expires and sta is शून्य.
	 */
	अगर (!sta)
		जाओ unlock;

	mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	ieee80211_rx_ba_समयr_expired(mvm_sta->vअगर,
				      sta->addr, ba_data->tid);
unlock:
	rcu_पढ़ो_unlock();
पूर्ण

/* Disable aggregations क्रम a biपंचांगap of TIDs क्रम a given station */
अटल पूर्णांक iwl_mvm_invalidate_sta_queue(काष्ठा iwl_mvm *mvm, पूर्णांक queue,
					अचिन्हित दीर्घ disable_agg_tids,
					bool हटाओ_queue)
अणु
	काष्ठा iwl_mvm_add_sta_cmd cmd = अणुपूर्ण;
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	u32 status;
	u8 sta_id;

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस -EINVAL;

	sta_id = mvm->queue_info[queue].ra_sta_id;

	rcu_पढ़ो_lock();

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);

	अगर (WARN_ON_ONCE(IS_ERR_OR_शून्य(sta))) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	mvmsta->tid_disable_agg |= disable_agg_tids;

	cmd.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color);
	cmd.sta_id = mvmsta->sta_id;
	cmd.add_modअगरy = STA_MODE_MODIFY;
	cmd.modअगरy_mask = STA_MODIFY_QUEUES;
	अगर (disable_agg_tids)
		cmd.modअगरy_mask |= STA_MODIFY_TID_DISABLE_TX;
	अगर (हटाओ_queue)
		cmd.modअगरy_mask |= STA_MODIFY_QUEUE_REMOVAL;
	cmd.tfd_queue_msk = cpu_to_le32(mvmsta->tfd_queue_msk);
	cmd.tid_disable_tx = cpu_to_le16(mvmsta->tid_disable_agg);

	rcu_पढ़ो_unlock();

	/* Notअगरy FW of queue removal from the STA queues */
	status = ADD_STA_SUCCESS;
	वापस iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA,
					   iwl_mvm_add_sta_cmd_size(mvm),
					   &cmd, &status);
पूर्ण

अटल पूर्णांक iwl_mvm_disable_txq(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			       पूर्णांक queue, u8 tid, u8 flags)
अणु
	काष्ठा iwl_scd_txq_cfg_cmd cmd = अणु
		.scd_queue = queue,
		.action = SCD_CFG_DISABLE_QUEUE,
	पूर्ण;
	पूर्णांक ret;

	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		iwl_trans_txq_मुक्त(mvm->trans, queue);

		वापस 0;
	पूर्ण

	अगर (WARN_ON(mvm->queue_info[queue].tid_biपंचांगap == 0))
		वापस 0;

	mvm->queue_info[queue].tid_biपंचांगap &= ~BIT(tid);

	cmd.action = mvm->queue_info[queue].tid_biपंचांगap ?
		SCD_CFG_ENABLE_QUEUE : SCD_CFG_DISABLE_QUEUE;
	अगर (cmd.action == SCD_CFG_DISABLE_QUEUE)
		mvm->queue_info[queue].status = IWL_MVM_QUEUE_FREE;

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Disabling TXQ #%d tids=0x%x\n",
			    queue,
			    mvm->queue_info[queue].tid_biपंचांगap);

	/* If the queue is still enabled - nothing left to करो in this func */
	अगर (cmd.action == SCD_CFG_ENABLE_QUEUE)
		वापस 0;

	cmd.sta_id = mvm->queue_info[queue].ra_sta_id;
	cmd.tid = mvm->queue_info[queue].txq_tid;

	/* Make sure queue info is correct even though we overग_लिखो it */
	WARN(mvm->queue_info[queue].tid_biपंचांगap,
	     "TXQ #%d info out-of-sync - tids=0x%x\n",
	     queue, mvm->queue_info[queue].tid_biपंचांगap);

	/* If we are here - the queue is मुक्तd and we can zero out these vals */
	mvm->queue_info[queue].tid_biपंचांगap = 0;

	अगर (sta) अणु
		काष्ठा iwl_mvm_txq *mvmtxq =
			iwl_mvm_txq_from_tid(sta, tid);

		mvmtxq->txq_id = IWL_MVM_INVALID_QUEUE;
	पूर्ण

	/* Regardless अगर this is a reserved TXQ क्रम a STA - mark it as false */
	mvm->queue_info[queue].reserved = false;

	iwl_trans_txq_disable(mvm->trans, queue, false);
	ret = iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, flags,
				   माप(काष्ठा iwl_scd_txq_cfg_cmd), &cmd);

	अगर (ret)
		IWL_ERR(mvm, "Failed to disable queue %d (ret=%d)\n",
			queue, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_get_queue_agg_tids(काष्ठा iwl_mvm *mvm, पूर्णांक queue)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	अचिन्हित दीर्घ tid_biपंचांगap;
	अचिन्हित दीर्घ agg_tids = 0;
	u8 sta_id;
	पूर्णांक tid;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस -EINVAL;

	sta_id = mvm->queue_info[queue].ra_sta_id;
	tid_biपंचांगap = mvm->queue_info[queue].tid_biपंचांगap;

	sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[sta_id],
					lockdep_is_held(&mvm->mutex));

	अगर (WARN_ON_ONCE(IS_ERR_OR_शून्य(sta)))
		वापस -EINVAL;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	spin_lock_bh(&mvmsta->lock);
	क्रम_each_set_bit(tid, &tid_biपंचांगap, IWL_MAX_TID_COUNT + 1) अणु
		अगर (mvmsta->tid_data[tid].state == IWL_AGG_ON)
			agg_tids |= BIT(tid);
	पूर्ण
	spin_unlock_bh(&mvmsta->lock);

	वापस agg_tids;
पूर्ण

/*
 * Remove a queue from a station's resources.
 * Note that this only marks as मुक्त. It DOESN'T delete a BA agreement, and
 * करोesn't disable the queue
 */
अटल पूर्णांक iwl_mvm_हटाओ_sta_queue_marking(काष्ठा iwl_mvm *mvm, पूर्णांक queue)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	अचिन्हित दीर्घ tid_biपंचांगap;
	अचिन्हित दीर्घ disable_agg_tids = 0;
	u8 sta_id;
	पूर्णांक tid;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस -EINVAL;

	sta_id = mvm->queue_info[queue].ra_sta_id;
	tid_biपंचांगap = mvm->queue_info[queue].tid_biपंचांगap;

	rcu_पढ़ो_lock();

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);

	अगर (WARN_ON_ONCE(IS_ERR_OR_शून्य(sta))) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	spin_lock_bh(&mvmsta->lock);
	/* Unmap MAC queues and TIDs from this queue */
	क्रम_each_set_bit(tid, &tid_biपंचांगap, IWL_MAX_TID_COUNT + 1) अणु
		काष्ठा iwl_mvm_txq *mvmtxq =
			iwl_mvm_txq_from_tid(sta, tid);

		अगर (mvmsta->tid_data[tid].state == IWL_AGG_ON)
			disable_agg_tids |= BIT(tid);
		mvmsta->tid_data[tid].txq_id = IWL_MVM_INVALID_QUEUE;

		mvmtxq->txq_id = IWL_MVM_INVALID_QUEUE;
	पूर्ण

	mvmsta->tfd_queue_msk &= ~BIT(queue); /* Don't use this queue anymore */
	spin_unlock_bh(&mvmsta->lock);

	rcu_पढ़ो_unlock();

	/*
	 * The TX path may have been using this TXQ_ID from the tid_data,
	 * so make sure it's no दीर्घer running so that we can safely reuse
	 * this TXQ later. We've set all the TIDs to IWL_MVM_INVALID_QUEUE
	 * above, but nothing guarantees we've stopped using them. Thus,
	 * without this, we could get to iwl_mvm_disable_txq() and हटाओ
	 * the queue जबतक still sending frames to it.
	 */
	synchronize_net();

	वापस disable_agg_tids;
पूर्ण

अटल पूर्णांक iwl_mvm_मुक्त_inactive_queue(काष्ठा iwl_mvm *mvm, पूर्णांक queue,
				       काष्ठा ieee80211_sta *old_sta,
				       u8 new_sta_id)
अणु
	काष्ठा iwl_mvm_sta *mvmsta;
	u8 sta_id, tid;
	अचिन्हित दीर्घ disable_agg_tids = 0;
	bool same_sta;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस -EINVAL;

	sta_id = mvm->queue_info[queue].ra_sta_id;
	tid = mvm->queue_info[queue].txq_tid;

	same_sta = sta_id == new_sta_id;

	mvmsta = iwl_mvm_sta_from_staid_रक्षित(mvm, sta_id);
	अगर (WARN_ON(!mvmsta))
		वापस -EINVAL;

	disable_agg_tids = iwl_mvm_हटाओ_sta_queue_marking(mvm, queue);
	/* Disable the queue */
	अगर (disable_agg_tids)
		iwl_mvm_invalidate_sta_queue(mvm, queue,
					     disable_agg_tids, false);

	ret = iwl_mvm_disable_txq(mvm, old_sta, queue, tid, 0);
	अगर (ret) अणु
		IWL_ERR(mvm,
			"Failed to free inactive queue %d (ret=%d)\n",
			queue, ret);

		वापस ret;
	पूर्ण

	/* If TXQ is allocated to another STA, update removal in FW */
	अगर (!same_sta)
		iwl_mvm_invalidate_sta_queue(mvm, queue, 0, true);

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_get_shared_queue(काष्ठा iwl_mvm *mvm,
				    अचिन्हित दीर्घ tfd_queue_mask, u8 ac)
अणु
	पूर्णांक queue = 0;
	u8 ac_to_queue[IEEE80211_NUM_ACS];
	पूर्णांक i;

	/*
	 * This protects us against grabbing a queue that's being reconfigured
	 * by the inactivity checker.
	 */
	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस -EINVAL;

	स_रखो(&ac_to_queue, IEEE80211_INVAL_HW_QUEUE, माप(ac_to_queue));

	/* See what ACs the existing queues क्रम this STA have */
	क्रम_each_set_bit(i, &tfd_queue_mask, IWL_MVM_DQA_MAX_DATA_QUEUE) अणु
		/* Only DATA queues can be shared */
		अगर (i < IWL_MVM_DQA_MIN_DATA_QUEUE &&
		    i != IWL_MVM_DQA_BSS_CLIENT_QUEUE)
			जारी;

		ac_to_queue[mvm->queue_info[i].mac80211_ac] = i;
	पूर्ण

	/*
	 * The queue to share is chosen only from DATA queues as follows (in
	 * descending priority):
	 * 1. An AC_BE queue
	 * 2. Same AC queue
	 * 3. Highest AC queue that is lower than new AC
	 * 4. Any existing AC (there always is at least 1 DATA queue)
	 */

	/* Priority 1: An AC_BE queue */
	अगर (ac_to_queue[IEEE80211_AC_BE] != IEEE80211_INVAL_HW_QUEUE)
		queue = ac_to_queue[IEEE80211_AC_BE];
	/* Priority 2: Same AC queue */
	अन्यथा अगर (ac_to_queue[ac] != IEEE80211_INVAL_HW_QUEUE)
		queue = ac_to_queue[ac];
	/* Priority 3a: If new AC is VO and VI exists - use VI */
	अन्यथा अगर (ac == IEEE80211_AC_VO &&
		 ac_to_queue[IEEE80211_AC_VI] != IEEE80211_INVAL_HW_QUEUE)
		queue = ac_to_queue[IEEE80211_AC_VI];
	/* Priority 3b: No BE so only AC less than the new one is BK */
	अन्यथा अगर (ac_to_queue[IEEE80211_AC_BK] != IEEE80211_INVAL_HW_QUEUE)
		queue = ac_to_queue[IEEE80211_AC_BK];
	/* Priority 4a: No BE nor BK - use VI अगर exists */
	अन्यथा अगर (ac_to_queue[IEEE80211_AC_VI] != IEEE80211_INVAL_HW_QUEUE)
		queue = ac_to_queue[IEEE80211_AC_VI];
	/* Priority 4b: No BE, BK nor VI - use VO अगर exists */
	अन्यथा अगर (ac_to_queue[IEEE80211_AC_VO] != IEEE80211_INVAL_HW_QUEUE)
		queue = ac_to_queue[IEEE80211_AC_VO];

	/* Make sure queue found (or not) is legal */
	अगर (!iwl_mvm_is_dqa_data_queue(mvm, queue) &&
	    !iwl_mvm_is_dqa_mgmt_queue(mvm, queue) &&
	    (queue != IWL_MVM_DQA_BSS_CLIENT_QUEUE)) अणु
		IWL_ERR(mvm, "No DATA queues available to share\n");
		वापस -ENOSPC;
	पूर्ण

	वापस queue;
पूर्ण

/*
 * If a given queue has a higher AC than the TID stream that is being compared
 * to, the queue needs to be redirected to the lower AC. This function करोes that
 * in such a हाल, otherwise - अगर no redirection required - it करोes nothing,
 * unless the %क्रमce param is true.
 */
अटल पूर्णांक iwl_mvm_redirect_queue(काष्ठा iwl_mvm *mvm, पूर्णांक queue, पूर्णांक tid,
				  पूर्णांक ac, पूर्णांक ssn, अचिन्हित पूर्णांक wdg_समयout,
				  bool क्रमce, काष्ठा iwl_mvm_txq *txq)
अणु
	काष्ठा iwl_scd_txq_cfg_cmd cmd = अणु
		.scd_queue = queue,
		.action = SCD_CFG_DISABLE_QUEUE,
	पूर्ण;
	bool shared_queue;
	पूर्णांक ret;

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस -EINVAL;

	/*
	 * If the AC is lower than current one - FIFO needs to be redirected to
	 * the lowest one of the streams in the queue. Check अगर this is needed
	 * here.
	 * Notice that the क्रमागत ieee80211_ac_numbers is "flipped", so BK is with
	 * value 3 and VO with value 0, so to check अगर ac X is lower than ac Y
	 * we need to check अगर the numerical value of X is LARGER than of Y.
	 */
	अगर (ac <= mvm->queue_info[queue].mac80211_ac && !क्रमce) अणु
		IWL_DEBUG_TX_QUEUES(mvm,
				    "No redirection needed on TXQ #%d\n",
				    queue);
		वापस 0;
	पूर्ण

	cmd.sta_id = mvm->queue_info[queue].ra_sta_id;
	cmd.tx_fअगरo = iwl_mvm_ac_to_tx_fअगरo[mvm->queue_info[queue].mac80211_ac];
	cmd.tid = mvm->queue_info[queue].txq_tid;
	shared_queue = hweight16(mvm->queue_info[queue].tid_biपंचांगap) > 1;

	IWL_DEBUG_TX_QUEUES(mvm, "Redirecting TXQ #%d to FIFO #%d\n",
			    queue, iwl_mvm_ac_to_tx_fअगरo[ac]);

	/* Stop the queue and रुको क्रम it to empty */
	txq->stopped = true;

	ret = iwl_trans_रुको_tx_queues_empty(mvm->trans, BIT(queue));
	अगर (ret) अणु
		IWL_ERR(mvm, "Error draining queue %d before reconfig\n",
			queue);
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Beक्रमe redirecting the queue we need to de-activate it */
	iwl_trans_txq_disable(mvm->trans, queue, false);
	ret = iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, 0, माप(cmd), &cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed SCD disable TXQ %d (ret=%d)\n", queue,
			ret);

	/* Make sure the SCD wrptr is correctly set beक्रमe reconfiguring */
	iwl_trans_txq_enable_cfg(mvm->trans, queue, ssn, शून्य, wdg_समयout);

	/* Update the TID "owner" of the queue */
	mvm->queue_info[queue].txq_tid = tid;

	/* TODO: Work-around SCD bug when moving back by multiples of 0x40 */

	/* Redirect to lower AC */
	iwl_mvm_reconfig_scd(mvm, queue, iwl_mvm_ac_to_tx_fअगरo[ac],
			     cmd.sta_id, tid, IWL_FRAME_LIMIT, ssn);

	/* Update AC marking of the queue */
	mvm->queue_info[queue].mac80211_ac = ac;

	/*
	 * Mark queue as shared in transport अगर shared
	 * Note this has to be करोne after queue enablement because enablement
	 * can also set this value, and there is no indication there to shared
	 * queues
	 */
	अगर (shared_queue)
		iwl_trans_txq_set_shared_mode(mvm->trans, queue, true);

out:
	/* Continue using the queue */
	txq->stopped = false;

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_find_मुक्त_queue(काष्ठा iwl_mvm *mvm, u8 sta_id,
				   u8 minq, u8 maxq)
अणु
	पूर्णांक i;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN(maxq >= mvm->trans->trans_cfg->base_params->num_of_queues,
		 "max queue %d >= num_of_queues (%d)", maxq,
		 mvm->trans->trans_cfg->base_params->num_of_queues))
		maxq = mvm->trans->trans_cfg->base_params->num_of_queues - 1;

	/* This should not be hit with new TX path */
	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस -ENOSPC;

	/* Start by looking क्रम a मुक्त queue */
	क्रम (i = minq; i <= maxq; i++)
		अगर (mvm->queue_info[i].tid_biपंचांगap == 0 &&
		    mvm->queue_info[i].status == IWL_MVM_QUEUE_FREE)
			वापस i;

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक iwl_mvm_tvqm_enable_txq(काष्ठा iwl_mvm *mvm,
				   u8 sta_id, u8 tid, अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक queue, size = max_t(u32, IWL_DEFAULT_QUEUE_SIZE,
				mvm->trans->cfg->min_256_ba_txq_size);

	अगर (tid == IWL_MAX_TID_COUNT) अणु
		tid = IWL_MGMT_TID;
		size = max_t(u32, IWL_MGMT_QUEUE_SIZE,
			     mvm->trans->cfg->min_txq_size);
	पूर्ण

	करो अणु
		__le16 enable = cpu_to_le16(TX_QUEUE_CFG_ENABLE_QUEUE);

		queue = iwl_trans_txq_alloc(mvm->trans, enable,
					    sta_id, tid, SCD_QUEUE_CFG,
					    size, समयout);

		अगर (queue < 0)
			IWL_DEBUG_TX_QUEUES(mvm,
					    "Failed allocating TXQ of size %d for sta %d tid %d, ret: %d\n",
					    size, sta_id, tid, queue);
		size /= 2;
	पूर्ण जबतक (queue < 0 && size >= 16);

	अगर (queue < 0)
		वापस queue;

	IWL_DEBUG_TX_QUEUES(mvm, "Enabling TXQ #%d for sta %d tid %d\n",
			    queue, sta_id, tid);

	वापस queue;
पूर्ण

अटल पूर्णांक iwl_mvm_sta_alloc_queue_tvqm(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_sta *sta, u8 ac,
					पूर्णांक tid)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_txq *mvmtxq =
		iwl_mvm_txq_from_tid(sta, tid);
	अचिन्हित पूर्णांक wdg_समयout =
		iwl_mvm_get_wd_समयout(mvm, mvmsta->vअगर, false, false);
	पूर्णांक queue = -1;

	lockdep_निश्चित_held(&mvm->mutex);

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Allocating queue for sta %d on tid %d\n",
			    mvmsta->sta_id, tid);
	queue = iwl_mvm_tvqm_enable_txq(mvm, mvmsta->sta_id, tid, wdg_समयout);
	अगर (queue < 0)
		वापस queue;

	mvmtxq->txq_id = queue;
	mvm->tvqm_info[queue].txq_tid = tid;
	mvm->tvqm_info[queue].sta_id = mvmsta->sta_id;

	IWL_DEBUG_TX_QUEUES(mvm, "Allocated queue is %d\n", queue);

	spin_lock_bh(&mvmsta->lock);
	mvmsta->tid_data[tid].txq_id = queue;
	spin_unlock_bh(&mvmsta->lock);

	वापस 0;
पूर्ण

अटल bool iwl_mvm_update_txq_mapping(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_sta *sta,
				       पूर्णांक queue, u8 sta_id, u8 tid)
अणु
	bool enable_queue = true;

	/* Make sure this TID isn't alपढ़ोy enabled */
	अगर (mvm->queue_info[queue].tid_biपंचांगap & BIT(tid)) अणु
		IWL_ERR(mvm, "Trying to enable TXQ %d with existing TID %d\n",
			queue, tid);
		वापस false;
	पूर्ण

	/* Update mappings and refcounts */
	अगर (mvm->queue_info[queue].tid_biपंचांगap)
		enable_queue = false;

	mvm->queue_info[queue].tid_biपंचांगap |= BIT(tid);
	mvm->queue_info[queue].ra_sta_id = sta_id;

	अगर (enable_queue) अणु
		अगर (tid != IWL_MAX_TID_COUNT)
			mvm->queue_info[queue].mac80211_ac =
				tid_to_mac80211_ac[tid];
		अन्यथा
			mvm->queue_info[queue].mac80211_ac = IEEE80211_AC_VO;

		mvm->queue_info[queue].txq_tid = tid;
	पूर्ण

	अगर (sta) अणु
		काष्ठा iwl_mvm_txq *mvmtxq =
			iwl_mvm_txq_from_tid(sta, tid);

		mvmtxq->txq_id = queue;
	पूर्ण

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Enabling TXQ #%d tids=0x%x\n",
			    queue, mvm->queue_info[queue].tid_biपंचांगap);

	वापस enable_queue;
पूर्ण

अटल bool iwl_mvm_enable_txq(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			       पूर्णांक queue, u16 ssn,
			       स्थिर काष्ठा iwl_trans_txq_scd_cfg *cfg,
			       अचिन्हित पूर्णांक wdg_समयout)
अणु
	काष्ठा iwl_scd_txq_cfg_cmd cmd = अणु
		.scd_queue = queue,
		.action = SCD_CFG_ENABLE_QUEUE,
		.winकरोw = cfg->frame_limit,
		.sta_id = cfg->sta_id,
		.ssn = cpu_to_le16(ssn),
		.tx_fअगरo = cfg->fअगरo,
		.aggregate = cfg->aggregate,
		.tid = cfg->tid,
	पूर्ण;
	bool inc_ssn;

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस false;

	/* Send the enabling command अगर we need to */
	अगर (!iwl_mvm_update_txq_mapping(mvm, sta, queue, cfg->sta_id, cfg->tid))
		वापस false;

	inc_ssn = iwl_trans_txq_enable_cfg(mvm->trans, queue, ssn,
					   शून्य, wdg_समयout);
	अगर (inc_ssn)
		le16_add_cpu(&cmd.ssn, 1);

	WARN(iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, 0, माप(cmd), &cmd),
	     "Failed to configure queue %d on FIFO %d\n", queue, cfg->fअगरo);

	वापस inc_ssn;
पूर्ण

अटल व्योम iwl_mvm_change_queue_tid(काष्ठा iwl_mvm *mvm, पूर्णांक queue)
अणु
	काष्ठा iwl_scd_txq_cfg_cmd cmd = अणु
		.scd_queue = queue,
		.action = SCD_CFG_UPDATE_QUEUE_TID,
	पूर्ण;
	पूर्णांक tid;
	अचिन्हित दीर्घ tid_biपंचांगap;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस;

	tid_biपंचांगap = mvm->queue_info[queue].tid_biपंचांगap;

	अगर (WARN(!tid_biपंचांगap, "TXQ %d has no tids assigned to it\n", queue))
		वापस;

	/* Find any TID क्रम queue */
	tid = find_first_bit(&tid_biपंचांगap, IWL_MAX_TID_COUNT + 1);
	cmd.tid = tid;
	cmd.tx_fअगरo = iwl_mvm_ac_to_tx_fअगरo[tid_to_mac80211_ac[tid]];

	ret = iwl_mvm_send_cmd_pdu(mvm, SCD_QUEUE_CFG, 0, माप(cmd), &cmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to update owner of TXQ %d (ret=%d)\n",
			queue, ret);
		वापस;
	पूर्ण

	mvm->queue_info[queue].txq_tid = tid;
	IWL_DEBUG_TX_QUEUES(mvm, "Changed TXQ %d ownership to tid %d\n",
			    queue, tid);
पूर्ण

अटल व्योम iwl_mvm_unshare_queue(काष्ठा iwl_mvm *mvm, पूर्णांक queue)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	u8 sta_id;
	पूर्णांक tid = -1;
	अचिन्हित दीर्घ tid_biपंचांगap;
	अचिन्हित पूर्णांक wdg_समयout;
	पूर्णांक ssn;
	पूर्णांक ret = true;

	/* queue sharing is disabled on new TX path */
	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस;

	lockdep_निश्चित_held(&mvm->mutex);

	sta_id = mvm->queue_info[queue].ra_sta_id;
	tid_biपंचांगap = mvm->queue_info[queue].tid_biपंचांगap;

	/* Find TID क्रम queue, and make sure it is the only one on the queue */
	tid = find_first_bit(&tid_biपंचांगap, IWL_MAX_TID_COUNT + 1);
	अगर (tid_biपंचांगap != BIT(tid)) अणु
		IWL_ERR(mvm, "Failed to unshare q %d, active tids=0x%lx\n",
			queue, tid_biपंचांगap);
		वापस;
	पूर्ण

	IWL_DEBUG_TX_QUEUES(mvm, "Unsharing TXQ %d, keeping tid %d\n", queue,
			    tid);

	sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[sta_id],
					lockdep_is_held(&mvm->mutex));

	अगर (WARN_ON_ONCE(IS_ERR_OR_शून्य(sta)))
		वापस;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	wdg_समयout = iwl_mvm_get_wd_समयout(mvm, mvmsta->vअगर, false, false);

	ssn = IEEE80211_SEQ_TO_SN(mvmsta->tid_data[tid].seq_number);

	ret = iwl_mvm_redirect_queue(mvm, queue, tid,
				     tid_to_mac80211_ac[tid], ssn,
				     wdg_समयout, true,
				     iwl_mvm_txq_from_tid(sta, tid));
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to redirect TXQ %d\n", queue);
		वापस;
	पूर्ण

	/* If aggs should be turned back on - करो it */
	अगर (mvmsta->tid_data[tid].state == IWL_AGG_ON) अणु
		काष्ठा iwl_mvm_add_sta_cmd cmd = अणु0पूर्ण;

		mvmsta->tid_disable_agg &= ~BIT(tid);

		cmd.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color);
		cmd.sta_id = mvmsta->sta_id;
		cmd.add_modअगरy = STA_MODE_MODIFY;
		cmd.modअगरy_mask = STA_MODIFY_TID_DISABLE_TX;
		cmd.tfd_queue_msk = cpu_to_le32(mvmsta->tfd_queue_msk);
		cmd.tid_disable_tx = cpu_to_le16(mvmsta->tid_disable_agg);

		ret = iwl_mvm_send_cmd_pdu(mvm, ADD_STA, CMD_ASYNC,
					   iwl_mvm_add_sta_cmd_size(mvm), &cmd);
		अगर (!ret) अणु
			IWL_DEBUG_TX_QUEUES(mvm,
					    "TXQ #%d is now aggregated again\n",
					    queue);

			/* Mark queue पूर्णांकenally as aggregating again */
			iwl_trans_txq_set_shared_mode(mvm->trans, queue, false);
		पूर्ण
	पूर्ण

	mvm->queue_info[queue].status = IWL_MVM_QUEUE_READY;
पूर्ण

/*
 * Remove inactive TIDs of a given queue.
 * If all queue TIDs are inactive - mark the queue as inactive
 * If only some the queue TIDs are inactive - unmap them from the queue
 *
 * Returns %true अगर all TIDs were हटाओd and the queue could be reused.
 */
अटल bool iwl_mvm_हटाओ_inactive_tids(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_mvm_sta *mvmsta, पूर्णांक queue,
					 अचिन्हित दीर्घ tid_biपंचांगap,
					 अचिन्हित दीर्घ *unshare_queues,
					 अचिन्हित दीर्घ *changetid_queues)
अणु
	पूर्णांक tid;

	lockdep_निश्चित_held(&mvmsta->lock);
	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस false;

	/* Go over all non-active TIDs, incl. IWL_MAX_TID_COUNT (क्रम mgmt) */
	क्रम_each_set_bit(tid, &tid_biपंचांगap, IWL_MAX_TID_COUNT + 1) अणु
		/* If some TFDs are still queued - करोn't mark TID as inactive */
		अगर (iwl_mvm_tid_queued(mvm, &mvmsta->tid_data[tid]))
			tid_biपंचांगap &= ~BIT(tid);

		/* Don't mark as inactive any TID that has an active BA */
		अगर (mvmsta->tid_data[tid].state != IWL_AGG_OFF)
			tid_biपंचांगap &= ~BIT(tid);
	पूर्ण

	/* If all TIDs in the queue are inactive - वापस it can be reused */
	अगर (tid_biपंचांगap == mvm->queue_info[queue].tid_biपंचांगap) अणु
		IWL_DEBUG_TX_QUEUES(mvm, "Queue %d is inactive\n", queue);
		वापस true;
	पूर्ण

	/*
	 * If we are here, this is a shared queue and not all TIDs समयd-out.
	 * Remove the ones that did.
	 */
	क्रम_each_set_bit(tid, &tid_biपंचांगap, IWL_MAX_TID_COUNT + 1) अणु
		u16 tid_biपंचांगap;

		mvmsta->tid_data[tid].txq_id = IWL_MVM_INVALID_QUEUE;
		mvm->queue_info[queue].tid_biपंचांगap &= ~BIT(tid);

		tid_biपंचांगap = mvm->queue_info[queue].tid_biपंचांगap;

		/*
		 * We need to take पूर्णांकo account a situation in which a TXQ was
		 * allocated to TID x, and then turned shared by adding TIDs y
		 * and z. If TID x becomes inactive and is हटाओd from the TXQ,
		 * ownership must be given to one of the reमुख्यing TIDs.
		 * This is मुख्यly because अगर TID x जारीs - a new queue can't
		 * be allocated क्रम it as दीर्घ as it is an owner of another TXQ.
		 *
		 * Mark this queue in the right biपंचांगap, we'll send the command
		 * to the firmware later.
		 */
		अगर (!(tid_biपंचांगap & BIT(mvm->queue_info[queue].txq_tid)))
			set_bit(queue, changetid_queues);

		IWL_DEBUG_TX_QUEUES(mvm,
				    "Removing inactive TID %d from shared Q:%d\n",
				    tid, queue);
	पूर्ण

	IWL_DEBUG_TX_QUEUES(mvm,
			    "TXQ #%d left with tid bitmap 0x%x\n", queue,
			    mvm->queue_info[queue].tid_biपंचांगap);

	/*
	 * There may be dअगरferent TIDs with the same mac queues, so make
	 * sure all TIDs have existing corresponding mac queues enabled
	 */
	tid_biपंचांगap = mvm->queue_info[queue].tid_biपंचांगap;

	/* If the queue is marked as shared - "unshare" it */
	अगर (hweight16(mvm->queue_info[queue].tid_biपंचांगap) == 1 &&
	    mvm->queue_info[queue].status == IWL_MVM_QUEUE_SHARED) अणु
		IWL_DEBUG_TX_QUEUES(mvm, "Marking Q:%d for reconfig\n",
				    queue);
		set_bit(queue, unshare_queues);
	पूर्ण

	वापस false;
पूर्ण

/*
 * Check क्रम inactivity - this includes checking अगर any queue
 * can be unshared and finding one (and only one) that can be
 * reused.
 * This function is also invoked as a sort of clean-up task,
 * in which हाल @alloc_क्रम_sta is IWL_MVM_INVALID_STA.
 *
 * Returns the queue number, or -ENOSPC.
 */
अटल पूर्णांक iwl_mvm_inactivity_check(काष्ठा iwl_mvm *mvm, u8 alloc_क्रम_sta)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ unshare_queues = 0;
	अचिन्हित दीर्घ changetid_queues = 0;
	पूर्णांक i, ret, मुक्त_queue = -ENOSPC;
	काष्ठा ieee80211_sta *queue_owner  = शून्य;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (iwl_mvm_has_new_tx_api(mvm))
		वापस -ENOSPC;

	rcu_पढ़ो_lock();

	/* we skip the CMD queue below by starting at 1 */
	BUILD_BUG_ON(IWL_MVM_DQA_CMD_QUEUE != 0);

	क्रम (i = 1; i < IWL_MAX_HW_QUEUES; i++) अणु
		काष्ठा ieee80211_sta *sta;
		काष्ठा iwl_mvm_sta *mvmsta;
		u8 sta_id;
		पूर्णांक tid;
		अचिन्हित दीर्घ inactive_tid_biपंचांगap = 0;
		अचिन्हित दीर्घ queue_tid_biपंचांगap;

		queue_tid_biपंचांगap = mvm->queue_info[i].tid_biपंचांगap;
		अगर (!queue_tid_biपंचांगap)
			जारी;

		/* If TXQ isn't in active use anyway - nothing to करो here... */
		अगर (mvm->queue_info[i].status != IWL_MVM_QUEUE_READY &&
		    mvm->queue_info[i].status != IWL_MVM_QUEUE_SHARED)
			जारी;

		/* Check to see अगर there are inactive TIDs on this queue */
		क्रम_each_set_bit(tid, &queue_tid_biपंचांगap,
				 IWL_MAX_TID_COUNT + 1) अणु
			अगर (समय_after(mvm->queue_info[i].last_frame_समय[tid] +
				       IWL_MVM_DQA_QUEUE_TIMEOUT, now))
				जारी;

			inactive_tid_biपंचांगap |= BIT(tid);
		पूर्ण

		/* If all TIDs are active - finish check on this queue */
		अगर (!inactive_tid_biपंचांगap)
			जारी;

		/*
		 * If we are here - the queue hadn't been served recently and is
		 * in use
		 */

		sta_id = mvm->queue_info[i].ra_sta_id;
		sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);

		/*
		 * If the STA करोesn't exist anymore, it isn't an error. It could
		 * be that it was हटाओd since getting the queues, and in this
		 * हाल it should've inactivated its queues anyway.
		 */
		अगर (IS_ERR_OR_शून्य(sta))
			जारी;

		mvmsta = iwl_mvm_sta_from_mac80211(sta);

		spin_lock_bh(&mvmsta->lock);
		ret = iwl_mvm_हटाओ_inactive_tids(mvm, mvmsta, i,
						   inactive_tid_biपंचांगap,
						   &unshare_queues,
						   &changetid_queues);
		अगर (ret && मुक्त_queue < 0) अणु
			queue_owner = sta;
			मुक्त_queue = i;
		पूर्ण
		/* only unlock sta lock - we still need the queue info lock */
		spin_unlock_bh(&mvmsta->lock);
	पूर्ण


	/* Reconfigure queues requiring reconfiguation */
	क्रम_each_set_bit(i, &unshare_queues, IWL_MAX_HW_QUEUES)
		iwl_mvm_unshare_queue(mvm, i);
	क्रम_each_set_bit(i, &changetid_queues, IWL_MAX_HW_QUEUES)
		iwl_mvm_change_queue_tid(mvm, i);

	rcu_पढ़ो_unlock();

	अगर (मुक्त_queue >= 0 && alloc_क्रम_sta != IWL_MVM_INVALID_STA) अणु
		ret = iwl_mvm_मुक्त_inactive_queue(mvm, मुक्त_queue, queue_owner,
						  alloc_क्रम_sta);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस मुक्त_queue;
पूर्ण

अटल पूर्णांक iwl_mvm_sta_alloc_queue(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_sta *sta, u8 ac, पूर्णांक tid)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_trans_txq_scd_cfg cfg = अणु
		.fअगरo = iwl_mvm_mac_ac_to_tx_fअगरo(mvm, ac),
		.sta_id = mvmsta->sta_id,
		.tid = tid,
		.frame_limit = IWL_FRAME_LIMIT,
	पूर्ण;
	अचिन्हित पूर्णांक wdg_समयout =
		iwl_mvm_get_wd_समयout(mvm, mvmsta->vअगर, false, false);
	पूर्णांक queue = -1;
	अचिन्हित दीर्घ disable_agg_tids = 0;
	क्रमागत iwl_mvm_agg_state queue_state;
	bool shared_queue = false, inc_ssn;
	पूर्णांक ssn;
	अचिन्हित दीर्घ tfd_queue_mask;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (iwl_mvm_has_new_tx_api(mvm))
		वापस iwl_mvm_sta_alloc_queue_tvqm(mvm, sta, ac, tid);

	spin_lock_bh(&mvmsta->lock);
	tfd_queue_mask = mvmsta->tfd_queue_msk;
	ssn = IEEE80211_SEQ_TO_SN(mvmsta->tid_data[tid].seq_number);
	spin_unlock_bh(&mvmsta->lock);

	अगर (tid == IWL_MAX_TID_COUNT) अणु
		queue = iwl_mvm_find_मुक्त_queue(mvm, mvmsta->sta_id,
						IWL_MVM_DQA_MIN_MGMT_QUEUE,
						IWL_MVM_DQA_MAX_MGMT_QUEUE);
		अगर (queue >= IWL_MVM_DQA_MIN_MGMT_QUEUE)
			IWL_DEBUG_TX_QUEUES(mvm, "Found free MGMT queue #%d\n",
					    queue);

		/* If no such queue is found, we'll use a DATA queue instead */
	पूर्ण

	अगर ((queue < 0 && mvmsta->reserved_queue != IEEE80211_INVAL_HW_QUEUE) &&
	    (mvm->queue_info[mvmsta->reserved_queue].status ==
			IWL_MVM_QUEUE_RESERVED)) अणु
		queue = mvmsta->reserved_queue;
		mvm->queue_info[queue].reserved = true;
		IWL_DEBUG_TX_QUEUES(mvm, "Using reserved queue #%d\n", queue);
	पूर्ण

	अगर (queue < 0)
		queue = iwl_mvm_find_मुक्त_queue(mvm, mvmsta->sta_id,
						IWL_MVM_DQA_MIN_DATA_QUEUE,
						IWL_MVM_DQA_MAX_DATA_QUEUE);
	अगर (queue < 0) अणु
		/* try harder - perhaps समाप्त an inactive queue */
		queue = iwl_mvm_inactivity_check(mvm, mvmsta->sta_id);
	पूर्ण

	/* No मुक्त queue - we'll have to share */
	अगर (queue <= 0) अणु
		queue = iwl_mvm_get_shared_queue(mvm, tfd_queue_mask, ac);
		अगर (queue > 0) अणु
			shared_queue = true;
			mvm->queue_info[queue].status = IWL_MVM_QUEUE_SHARED;
		पूर्ण
	पूर्ण

	/*
	 * Mark TXQ as पढ़ोy, even though it hasn't been fully configured yet,
	 * to make sure no one अन्यथा takes it.
	 * This will allow aव्योमing re-acquiring the lock at the end of the
	 * configuration. On error we'll mark it back as मुक्त.
	 */
	अगर (queue > 0 && !shared_queue)
		mvm->queue_info[queue].status = IWL_MVM_QUEUE_READY;

	/* This shouldn't happen - out of queues */
	अगर (WARN_ON(queue <= 0)) अणु
		IWL_ERR(mvm, "No available queues for tid %d on sta_id %d\n",
			tid, cfg.sta_id);
		वापस queue;
	पूर्ण

	/*
	 * Actual en/disablement of aggregations is through the ADD_STA HCMD,
	 * but क्रम configuring the SCD to send A-MPDUs we need to mark the queue
	 * as aggregatable.
	 * Mark all DATA queues as allowing to be aggregated at some poपूर्णांक
	 */
	cfg.aggregate = (queue >= IWL_MVM_DQA_MIN_DATA_QUEUE ||
			 queue == IWL_MVM_DQA_BSS_CLIENT_QUEUE);

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Allocating %squeue #%d to sta %d on tid %d\n",
			    shared_queue ? "shared " : "", queue,
			    mvmsta->sta_id, tid);

	अगर (shared_queue) अणु
		/* Disable any खोलो aggs on this queue */
		disable_agg_tids = iwl_mvm_get_queue_agg_tids(mvm, queue);

		अगर (disable_agg_tids) अणु
			IWL_DEBUG_TX_QUEUES(mvm, "Disabling aggs on queue %d\n",
					    queue);
			iwl_mvm_invalidate_sta_queue(mvm, queue,
						     disable_agg_tids, false);
		पूर्ण
	पूर्ण

	inc_ssn = iwl_mvm_enable_txq(mvm, sta, queue, ssn, &cfg, wdg_समयout);

	/*
	 * Mark queue as shared in transport अगर shared
	 * Note this has to be करोne after queue enablement because enablement
	 * can also set this value, and there is no indication there to shared
	 * queues
	 */
	अगर (shared_queue)
		iwl_trans_txq_set_shared_mode(mvm->trans, queue, true);

	spin_lock_bh(&mvmsta->lock);
	/*
	 * This looks racy, but it is not. We have only one packet क्रम
	 * this ra/tid in our Tx path since we stop the Qdisc when we
	 * need to allocate a new TFD queue.
	 */
	अगर (inc_ssn) अणु
		mvmsta->tid_data[tid].seq_number += 0x10;
		ssn = (ssn + 1) & IEEE80211_SCTL_SEQ;
	पूर्ण
	mvmsta->tid_data[tid].txq_id = queue;
	mvmsta->tfd_queue_msk |= BIT(queue);
	queue_state = mvmsta->tid_data[tid].state;

	अगर (mvmsta->reserved_queue == queue)
		mvmsta->reserved_queue = IEEE80211_INVAL_HW_QUEUE;
	spin_unlock_bh(&mvmsta->lock);

	अगर (!shared_queue) अणु
		ret = iwl_mvm_sta_send_to_fw(mvm, sta, true, STA_MODIFY_QUEUES);
		अगर (ret)
			जाओ out_err;

		/* If we need to re-enable aggregations... */
		अगर (queue_state == IWL_AGG_ON) अणु
			ret = iwl_mvm_sta_tx_agg(mvm, sta, tid, queue, true);
			अगर (ret)
				जाओ out_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Redirect queue, अगर needed */
		ret = iwl_mvm_redirect_queue(mvm, queue, tid, ac, ssn,
					     wdg_समयout, false,
					     iwl_mvm_txq_from_tid(sta, tid));
		अगर (ret)
			जाओ out_err;
	पूर्ण

	वापस 0;

out_err:
	iwl_mvm_disable_txq(mvm, sta, queue, tid, 0);

	वापस ret;
पूर्ण

व्योम iwl_mvm_add_new_dqa_stream_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा iwl_mvm *mvm = container_of(wk, काष्ठा iwl_mvm,
					   add_stream_wk);

	mutex_lock(&mvm->mutex);

	iwl_mvm_inactivity_check(mvm, IWL_MVM_INVALID_STA);

	जबतक (!list_empty(&mvm->add_stream_txqs)) अणु
		काष्ठा iwl_mvm_txq *mvmtxq;
		काष्ठा ieee80211_txq *txq;
		u8 tid;

		mvmtxq = list_first_entry(&mvm->add_stream_txqs,
					  काष्ठा iwl_mvm_txq, list);

		txq = container_of((व्योम *)mvmtxq, काष्ठा ieee80211_txq,
				   drv_priv);
		tid = txq->tid;
		अगर (tid == IEEE80211_NUM_TIDS)
			tid = IWL_MAX_TID_COUNT;

		/*
		 * We can't really do much here, but if this fails we can't
		 * transmit anyway - so just करोn't transmit the frame etc.
		 * and let them back up ... we've tried our best to allocate
		 * a queue in the function itself.
		 */
		अगर (iwl_mvm_sta_alloc_queue(mvm, txq->sta, txq->ac, tid)) अणु
			list_del_init(&mvmtxq->list);
			जारी;
		पूर्ण

		list_del_init(&mvmtxq->list);
		local_bh_disable();
		iwl_mvm_mac_itxq_xmit(mvm->hw, txq);
		local_bh_enable();
	पूर्ण

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल पूर्णांक iwl_mvm_reserve_sta_stream(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_sta *sta,
				      क्रमागत nl80211_अगरtype vअगर_type)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	पूर्णांक queue;

	/* queue reserving is disabled on new TX path */
	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस 0;

	/* run the general cleanup/unsharing of queues */
	iwl_mvm_inactivity_check(mvm, IWL_MVM_INVALID_STA);

	/* Make sure we have मुक्त resources क्रम this STA */
	अगर (vअगर_type == NL80211_IFTYPE_STATION && !sta->tdls &&
	    !mvm->queue_info[IWL_MVM_DQA_BSS_CLIENT_QUEUE].tid_biपंचांगap &&
	    (mvm->queue_info[IWL_MVM_DQA_BSS_CLIENT_QUEUE].status ==
	     IWL_MVM_QUEUE_FREE))
		queue = IWL_MVM_DQA_BSS_CLIENT_QUEUE;
	अन्यथा
		queue = iwl_mvm_find_मुक्त_queue(mvm, mvmsta->sta_id,
						IWL_MVM_DQA_MIN_DATA_QUEUE,
						IWL_MVM_DQA_MAX_DATA_QUEUE);
	अगर (queue < 0) अणु
		/* try again - this समय kick out a queue अगर needed */
		queue = iwl_mvm_inactivity_check(mvm, mvmsta->sta_id);
		अगर (queue < 0) अणु
			IWL_ERR(mvm, "No available queues for new station\n");
			वापस -ENOSPC;
		पूर्ण
	पूर्ण
	mvm->queue_info[queue].status = IWL_MVM_QUEUE_RESERVED;

	mvmsta->reserved_queue = queue;

	IWL_DEBUG_TX_QUEUES(mvm, "Reserving data queue #%d for sta_id %d\n",
			    queue, mvmsta->sta_id);

	वापस 0;
पूर्ण

/*
 * In DQA mode, after a HW restart the queues should be allocated as beक्रमe, in
 * order to aव्योम race conditions when there are shared queues. This function
 * करोes the re-mapping and queue allocation.
 *
 * Note that re-enabling aggregations isn't करोne in this function.
 */
अटल व्योम iwl_mvm_पुनः_स्मृति_queues_after_restart(काष्ठा iwl_mvm *mvm,
						 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	अचिन्हित पूर्णांक wdg =
		iwl_mvm_get_wd_समयout(mvm, mvm_sta->vअगर, false, false);
	पूर्णांक i;
	काष्ठा iwl_trans_txq_scd_cfg cfg = अणु
		.sta_id = mvm_sta->sta_id,
		.frame_limit = IWL_FRAME_LIMIT,
	पूर्ण;

	/* Make sure reserved queue is still marked as such (अगर allocated) */
	अगर (mvm_sta->reserved_queue != IEEE80211_INVAL_HW_QUEUE)
		mvm->queue_info[mvm_sta->reserved_queue].status =
			IWL_MVM_QUEUE_RESERVED;

	क्रम (i = 0; i <= IWL_MAX_TID_COUNT; i++) अणु
		काष्ठा iwl_mvm_tid_data *tid_data = &mvm_sta->tid_data[i];
		पूर्णांक txq_id = tid_data->txq_id;
		पूर्णांक ac;

		अगर (txq_id == IWL_MVM_INVALID_QUEUE)
			जारी;

		ac = tid_to_mac80211_ac[i];

		अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
			IWL_DEBUG_TX_QUEUES(mvm,
					    "Re-mapping sta %d tid %d\n",
					    mvm_sta->sta_id, i);
			txq_id = iwl_mvm_tvqm_enable_txq(mvm, mvm_sta->sta_id,
							 i, wdg);
			/*
			 * on failures, just set it to IWL_MVM_INVALID_QUEUE
			 * to try again later, we have no other good way of
			 * failing here
			 */
			अगर (txq_id < 0)
				txq_id = IWL_MVM_INVALID_QUEUE;
			tid_data->txq_id = txq_id;

			/*
			 * Since we करोn't set the seq number after reset, and HW
			 * sets it now, FW reset will cause the seq num to start
			 * at 0 again, so driver will need to update it
			 * पूर्णांकernally as well, so it keeps in sync with real val
			 */
			tid_data->seq_number = 0;
		पूर्ण अन्यथा अणु
			u16 seq = IEEE80211_SEQ_TO_SN(tid_data->seq_number);

			cfg.tid = i;
			cfg.fअगरo = iwl_mvm_mac_ac_to_tx_fअगरo(mvm, ac);
			cfg.aggregate = (txq_id >= IWL_MVM_DQA_MIN_DATA_QUEUE ||
					 txq_id ==
					 IWL_MVM_DQA_BSS_CLIENT_QUEUE);

			IWL_DEBUG_TX_QUEUES(mvm,
					    "Re-mapping sta %d tid %d to queue %d\n",
					    mvm_sta->sta_id, i, txq_id);

			iwl_mvm_enable_txq(mvm, sta, txq_id, seq, &cfg, wdg);
			mvm->queue_info[txq_id].status = IWL_MVM_QUEUE_READY;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक iwl_mvm_add_पूर्णांक_sta_common(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_mvm_पूर्णांक_sta *sta,
				      स्थिर u8 *addr,
				      u16 mac_id, u16 color)
अणु
	काष्ठा iwl_mvm_add_sta_cmd cmd;
	पूर्णांक ret;
	u32 status = ADD_STA_SUCCESS;

	lockdep_निश्चित_held(&mvm->mutex);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.sta_id = sta->sta_id;

	अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP, ADD_STA,
				  0) >= 12 &&
	    sta->type == IWL_STA_AUX_ACTIVITY)
		cmd.mac_id_n_color = cpu_to_le32(mac_id);
	अन्यथा
		cmd.mac_id_n_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(mac_id,
								     color));

	अगर (fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE))
		cmd.station_type = sta->type;

	अगर (!iwl_mvm_has_new_tx_api(mvm))
		cmd.tfd_queue_msk = cpu_to_le32(sta->tfd_queue_msk);
	cmd.tid_disable_tx = cpu_to_le16(0xffff);

	अगर (addr)
		स_नकल(cmd.addr, addr, ETH_ALEN);

	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA,
					  iwl_mvm_add_sta_cmd_size(mvm),
					  &cmd, &status);
	अगर (ret)
		वापस ret;

	चयन (status & IWL_ADD_STA_STATUS_MASK) अणु
	हाल ADD_STA_SUCCESS:
		IWL_DEBUG_INFO(mvm, "Internal station added.\n");
		वापस 0;
	शेष:
		ret = -EIO;
		IWL_ERR(mvm, "Add internal station failed, status=0x%x\n",
			status);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_add_sta(काष्ठा iwl_mvm *mvm,
		    काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_rxq_dup_data *dup_data;
	पूर्णांक i, ret, sta_id;
	bool sta_update = false;
	अचिन्हित पूर्णांक sta_flags = 0;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
		sta_id = iwl_mvm_find_मुक्त_sta_id(mvm,
						  ieee80211_vअगर_type_p2p(vअगर));
	अन्यथा
		sta_id = mvm_sta->sta_id;

	अगर (sta_id == IWL_MVM_INVALID_STA)
		वापस -ENOSPC;

	spin_lock_init(&mvm_sta->lock);

	/* अगर this is a HW restart re-alloc existing queues */
	अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) अणु
		काष्ठा iwl_mvm_पूर्णांक_sta पंचांगp_sta = अणु
			.sta_id = sta_id,
			.type = mvm_sta->sta_type,
		पूर्ण;

		/*
		 * First add an empty station since allocating
		 * a queue requires a valid station
		 */
		ret = iwl_mvm_add_पूर्णांक_sta_common(mvm, &पंचांगp_sta, sta->addr,
						 mvmvअगर->id, mvmvअगर->color);
		अगर (ret)
			जाओ err;

		iwl_mvm_पुनः_स्मृति_queues_after_restart(mvm, sta);
		sta_update = true;
		sta_flags = iwl_mvm_has_new_tx_api(mvm) ? 0 : STA_MODIFY_QUEUES;
		जाओ update_fw;
	पूर्ण

	mvm_sta->sta_id = sta_id;
	mvm_sta->mac_id_n_color = FW_CMD_ID_AND_COLOR(mvmvअगर->id,
						      mvmvअगर->color);
	mvm_sta->vअगर = vअगर;
	अगर (!mvm->trans->trans_cfg->gen2)
		mvm_sta->max_agg_bufsize = LINK_QUAL_AGG_FRAME_LIMIT_DEF;
	अन्यथा
		mvm_sta->max_agg_bufsize = LINK_QUAL_AGG_FRAME_LIMIT_GEN2_DEF;
	mvm_sta->tx_protection = 0;
	mvm_sta->tt_tx_protection = false;
	mvm_sta->sta_type = sta->tdls ? IWL_STA_TDLS_LINK : IWL_STA_LINK;

	/* HW restart, करोn't assume the memory has been zeroed */
	mvm_sta->tid_disable_agg = 0xffff; /* No aggs at first */
	mvm_sta->tfd_queue_msk = 0;

	/* क्रम HW restart - reset everything but the sequence number */
	क्रम (i = 0; i <= IWL_MAX_TID_COUNT; i++) अणु
		u16 seq = mvm_sta->tid_data[i].seq_number;
		स_रखो(&mvm_sta->tid_data[i], 0, माप(mvm_sta->tid_data[i]));
		mvm_sta->tid_data[i].seq_number = seq;

		/*
		 * Mark all queues क्रम this STA as unallocated and defer TX
		 * frames until the queue is allocated
		 */
		mvm_sta->tid_data[i].txq_id = IWL_MVM_INVALID_QUEUE;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sta->txq); i++) अणु
		काष्ठा iwl_mvm_txq *mvmtxq =
			iwl_mvm_txq_from_mac80211(sta->txq[i]);

		mvmtxq->txq_id = IWL_MVM_INVALID_QUEUE;
		INIT_LIST_HEAD(&mvmtxq->list);
		atomic_set(&mvmtxq->tx_request, 0);
	पूर्ण

	mvm_sta->agg_tids = 0;

	अगर (iwl_mvm_has_new_rx_api(mvm) &&
	    !test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) अणु
		पूर्णांक q;

		dup_data = kसुस्मृति(mvm->trans->num_rx_queues,
				   माप(*dup_data), GFP_KERNEL);
		अगर (!dup_data)
			वापस -ENOMEM;
		/*
		 * Initialize all the last_seq values to 0xffff which can never
		 * compare equal to the frame's seq_ctrl in the check in
		 * iwl_mvm_is_dup() since the lower 4 bits are the fragment
		 * number and fragmented packets करोn't reach that function.
		 *
		 * This thus allows receiving a packet with seqno 0 and the
		 * retry bit set as the very first packet on a new TID.
		 */
		क्रम (q = 0; q < mvm->trans->num_rx_queues; q++)
			स_रखो(dup_data[q].last_seq, 0xff,
			       माप(dup_data[q].last_seq));
		mvm_sta->dup_data = dup_data;
	पूर्ण

	अगर (!iwl_mvm_has_new_tx_api(mvm)) अणु
		ret = iwl_mvm_reserve_sta_stream(mvm, sta,
						 ieee80211_vअगर_type_p2p(vअगर));
		अगर (ret)
			जाओ err;
	पूर्ण

	/*
	 * अगर rs is रेजिस्टरed with mac80211, then "add station" will be handled
	 * via the corresponding ops, otherwise need to notअगरy rate scaling here
	 */
	अगर (iwl_mvm_has_tlc_offload(mvm))
		iwl_mvm_rs_add_sta(mvm, mvm_sta);
	अन्यथा
		spin_lock_init(&mvm_sta->lq_sta.rs_drv.pers.lock);

	iwl_mvm_toggle_tx_ant(mvm, &mvm_sta->tx_ant);

update_fw:
	ret = iwl_mvm_sta_send_to_fw(mvm, sta, sta_update, sta_flags);
	अगर (ret)
		जाओ err;

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		अगर (!sta->tdls) अणु
			WARN_ON(mvmvअगर->ap_sta_id != IWL_MVM_INVALID_STA);
			mvmvअगर->ap_sta_id = sta_id;
		पूर्ण अन्यथा अणु
			WARN_ON(mvmvअगर->ap_sta_id == IWL_MVM_INVALID_STA);
		पूर्ण
	पूर्ण

	rcu_assign_poपूर्णांकer(mvm->fw_id_to_mac_id[sta_id], sta);

	वापस 0;

err:
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_drain_sta(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta,
		      bool drain)
अणु
	काष्ठा iwl_mvm_add_sta_cmd cmd = अणुपूर्ण;
	पूर्णांक ret;
	u32 status;

	lockdep_निश्चित_held(&mvm->mutex);

	cmd.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color);
	cmd.sta_id = mvmsta->sta_id;
	cmd.add_modअगरy = STA_MODE_MODIFY;
	cmd.station_flags = drain ? cpu_to_le32(STA_FLG_DRAIN_FLOW) : 0;
	cmd.station_flags_msk = cpu_to_le32(STA_FLG_DRAIN_FLOW);

	status = ADD_STA_SUCCESS;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA,
					  iwl_mvm_add_sta_cmd_size(mvm),
					  &cmd, &status);
	अगर (ret)
		वापस ret;

	चयन (status & IWL_ADD_STA_STATUS_MASK) अणु
	हाल ADD_STA_SUCCESS:
		IWL_DEBUG_INFO(mvm, "Frames for staid %d will drained in fw\n",
			       mvmsta->sta_id);
		अवरोध;
	शेष:
		ret = -EIO;
		IWL_ERR(mvm, "Couldn't drain frames for staid %d\n",
			mvmsta->sta_id);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Remove a station from the FW table. Beक्रमe sending the command to हटाओ
 * the station validate that the station is indeed known to the driver (sanity
 * only).
 */
अटल पूर्णांक iwl_mvm_rm_sta_common(काष्ठा iwl_mvm *mvm, u8 sta_id)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_rm_sta_cmd rm_sta_cmd = अणु
		.sta_id = sta_id,
	पूर्ण;
	पूर्णांक ret;

	sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[sta_id],
					lockdep_is_held(&mvm->mutex));

	/* Note: पूर्णांकernal stations are marked as error values */
	अगर (!sta) अणु
		IWL_ERR(mvm, "Invalid station id\n");
		वापस -EINVAL;
	पूर्ण

	ret = iwl_mvm_send_cmd_pdu(mvm, REMOVE_STA, 0,
				   माप(rm_sta_cmd), &rm_sta_cmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to remove station. Id=%d\n", sta_id);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_disable_sta_queues(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	पूर्णांक i;

	lockdep_निश्चित_held(&mvm->mutex);

	क्रम (i = 0; i < ARRAY_SIZE(mvm_sta->tid_data); i++) अणु
		अगर (mvm_sta->tid_data[i].txq_id == IWL_MVM_INVALID_QUEUE)
			जारी;

		iwl_mvm_disable_txq(mvm, sta, mvm_sta->tid_data[i].txq_id, i,
				    0);
		mvm_sta->tid_data[i].txq_id = IWL_MVM_INVALID_QUEUE;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sta->txq); i++) अणु
		काष्ठा iwl_mvm_txq *mvmtxq =
			iwl_mvm_txq_from_mac80211(sta->txq[i]);

		mvmtxq->txq_id = IWL_MVM_INVALID_QUEUE;
	पूर्ण
पूर्ण

पूर्णांक iwl_mvm_रुको_sta_queues_empty(काष्ठा iwl_mvm *mvm,
				  काष्ठा iwl_mvm_sta *mvm_sta)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mvm_sta->tid_data); i++) अणु
		u16 txq_id;
		पूर्णांक ret;

		spin_lock_bh(&mvm_sta->lock);
		txq_id = mvm_sta->tid_data[i].txq_id;
		spin_unlock_bh(&mvm_sta->lock);

		अगर (txq_id == IWL_MVM_INVALID_QUEUE)
			जारी;

		ret = iwl_trans_रुको_txq_empty(mvm->trans, txq_id);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_rm_sta(काष्ठा iwl_mvm *mvm,
		   काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	u8 sta_id = mvm_sta->sta_id;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (iwl_mvm_has_new_rx_api(mvm))
		kमुक्त(mvm_sta->dup_data);

	ret = iwl_mvm_drain_sta(mvm, mvm_sta, true);
	अगर (ret)
		वापस ret;

	/* flush its queues here since we are मुक्तing mvm_sta */
	ret = iwl_mvm_flush_sta(mvm, mvm_sta, false);
	अगर (ret)
		वापस ret;
	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		ret = iwl_mvm_रुको_sta_queues_empty(mvm, mvm_sta);
	पूर्ण अन्यथा अणु
		u32 q_mask = mvm_sta->tfd_queue_msk;

		ret = iwl_trans_रुको_tx_queues_empty(mvm->trans,
						     q_mask);
	पूर्ण
	अगर (ret)
		वापस ret;

	ret = iwl_mvm_drain_sta(mvm, mvm_sta, false);

	iwl_mvm_disable_sta_queues(mvm, vअगर, sta);

	/* If there is a TXQ still marked as reserved - मुक्त it */
	अगर (mvm_sta->reserved_queue != IEEE80211_INVAL_HW_QUEUE) अणु
		u8 reserved_txq = mvm_sta->reserved_queue;
		क्रमागत iwl_mvm_queue_status *status;

		/*
		 * If no traffic has gone through the reserved TXQ - it
		 * is still marked as IWL_MVM_QUEUE_RESERVED, and
		 * should be manually marked as मुक्त again
		 */
		status = &mvm->queue_info[reserved_txq].status;
		अगर (WARN((*status != IWL_MVM_QUEUE_RESERVED) &&
			 (*status != IWL_MVM_QUEUE_FREE),
			 "sta_id %d reserved txq %d status %d",
			 sta_id, reserved_txq, *status))
			वापस -EINVAL;

		*status = IWL_MVM_QUEUE_FREE;
	पूर्ण

	अगर (vअगर->type == NL80211_IFTYPE_STATION &&
	    mvmvअगर->ap_sta_id == sta_id) अणु
		/* अगर associated - we can't हटाओ the AP STA now */
		अगर (vअगर->bss_conf.assoc)
			वापस ret;

		/* unassoc - go ahead - हटाओ the AP STA now */
		mvmvअगर->ap_sta_id = IWL_MVM_INVALID_STA;
	पूर्ण

	/*
	 * This shouldn't happen - the TDLS channel चयन should be canceled
	 * beक्रमe the STA is हटाओd.
	 */
	अगर (WARN_ON_ONCE(mvm->tdls_cs.peer.sta_id == sta_id)) अणु
		mvm->tdls_cs.peer.sta_id = IWL_MVM_INVALID_STA;
		cancel_delayed_work(&mvm->tdls_cs.dwork);
	पूर्ण

	/*
	 * Make sure that the tx response code sees the station as -EBUSY and
	 * calls the drain worker.
	 */
	spin_lock_bh(&mvm_sta->lock);
	spin_unlock_bh(&mvm_sta->lock);

	ret = iwl_mvm_rm_sta_common(mvm, mvm_sta->sta_id);
	RCU_INIT_POINTER(mvm->fw_id_to_mac_id[mvm_sta->sta_id], शून्य);

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_rm_sta_id(काष्ठा iwl_mvm *mvm,
		      काष्ठा ieee80211_vअगर *vअगर,
		      u8 sta_id)
अणु
	पूर्णांक ret = iwl_mvm_rm_sta_common(mvm, sta_id);

	lockdep_निश्चित_held(&mvm->mutex);

	RCU_INIT_POINTER(mvm->fw_id_to_mac_id[sta_id], शून्य);
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_allocate_पूर्णांक_sta(काष्ठा iwl_mvm *mvm,
			     काष्ठा iwl_mvm_पूर्णांक_sta *sta,
			     u32 qmask, क्रमागत nl80211_अगरtype अगरtype,
			     क्रमागत iwl_sta_type type)
अणु
	अगर (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) ||
	    sta->sta_id == IWL_MVM_INVALID_STA) अणु
		sta->sta_id = iwl_mvm_find_मुक्त_sta_id(mvm, अगरtype);
		अगर (WARN_ON_ONCE(sta->sta_id == IWL_MVM_INVALID_STA))
			वापस -ENOSPC;
	पूर्ण

	sta->tfd_queue_msk = qmask;
	sta->type = type;

	/* put a non-शून्य value so iterating over the stations won't stop */
	rcu_assign_poपूर्णांकer(mvm->fw_id_to_mac_id[sta->sta_id], ERR_PTR(-EINVAL));
	वापस 0;
पूर्ण

व्योम iwl_mvm_dealloc_पूर्णांक_sta(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_पूर्णांक_sta *sta)
अणु
	RCU_INIT_POINTER(mvm->fw_id_to_mac_id[sta->sta_id], शून्य);
	स_रखो(sta, 0, माप(काष्ठा iwl_mvm_पूर्णांक_sta));
	sta->sta_id = IWL_MVM_INVALID_STA;
पूर्ण

अटल व्योम iwl_mvm_enable_aux_snअगर_queue(काष्ठा iwl_mvm *mvm, u16 queue,
					  u8 sta_id, u8 fअगरo)
अणु
	अचिन्हित पूर्णांक wdg_समयout =
		mvm->trans->trans_cfg->base_params->wd_समयout;
	काष्ठा iwl_trans_txq_scd_cfg cfg = अणु
		.fअगरo = fअगरo,
		.sta_id = sta_id,
		.tid = IWL_MAX_TID_COUNT,
		.aggregate = false,
		.frame_limit = IWL_FRAME_LIMIT,
	पूर्ण;

	WARN_ON(iwl_mvm_has_new_tx_api(mvm));

	iwl_mvm_enable_txq(mvm, शून्य, queue, 0, &cfg, wdg_समयout);
पूर्ण

अटल पूर्णांक iwl_mvm_enable_aux_snअगर_queue_tvqm(काष्ठा iwl_mvm *mvm, u8 sta_id)
अणु
	अचिन्हित पूर्णांक wdg_समयout =
		mvm->trans->trans_cfg->base_params->wd_समयout;

	WARN_ON(!iwl_mvm_has_new_tx_api(mvm));

	वापस iwl_mvm_tvqm_enable_txq(mvm, sta_id, IWL_MAX_TID_COUNT,
				       wdg_समयout);
पूर्ण

अटल पूर्णांक iwl_mvm_add_पूर्णांक_sta_with_queue(काष्ठा iwl_mvm *mvm, पूर्णांक macidx,
					  पूर्णांक maccolor, u8 *addr,
					  काष्ठा iwl_mvm_पूर्णांक_sta *sta,
					  u16 *queue, पूर्णांक fअगरo)
अणु
	पूर्णांक ret;

	/* Map queue to fअगरo - needs to happen beक्रमe adding station */
	अगर (!iwl_mvm_has_new_tx_api(mvm))
		iwl_mvm_enable_aux_snअगर_queue(mvm, *queue, sta->sta_id, fअगरo);

	ret = iwl_mvm_add_पूर्णांक_sta_common(mvm, sta, addr, macidx, maccolor);
	अगर (ret) अणु
		अगर (!iwl_mvm_has_new_tx_api(mvm))
			iwl_mvm_disable_txq(mvm, शून्य, *queue,
					    IWL_MAX_TID_COUNT, 0);
		वापस ret;
	पूर्ण

	/*
	 * For 22000 firmware and on we cannot add queue to a station unknown
	 * to firmware so enable queue here - after the station was added
	 */
	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		पूर्णांक txq;

		txq = iwl_mvm_enable_aux_snअगर_queue_tvqm(mvm, sta->sta_id);
		अगर (txq < 0) अणु
			iwl_mvm_rm_sta_common(mvm, sta->sta_id);
			वापस txq;
		पूर्ण

		*queue = txq;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_add_aux_sta(काष्ठा iwl_mvm *mvm, u32 lmac_id)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	/* Allocate aux station and assign to it the aux queue */
	ret = iwl_mvm_allocate_पूर्णांक_sta(mvm, &mvm->aux_sta, BIT(mvm->aux_queue),
				       NL80211_IFTYPE_UNSPECIFIED,
				       IWL_STA_AUX_ACTIVITY);
	अगर (ret)
		वापस ret;

	/*
	 * In CDB NICs we need to specअगरy which lmac to use क्रम aux activity
	 * using the mac_id argument place to send lmac_id to the function
	 */
	ret = iwl_mvm_add_पूर्णांक_sta_with_queue(mvm, lmac_id, 0, शून्य,
					     &mvm->aux_sta, &mvm->aux_queue,
					     IWL_MVM_TX_FIFO_MCAST);
	अगर (ret) अणु
		iwl_mvm_dealloc_पूर्णांक_sta(mvm, &mvm->aux_sta);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_add_snअगर_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	lockdep_निश्चित_held(&mvm->mutex);

	वापस iwl_mvm_add_पूर्णांक_sta_with_queue(mvm, mvmvअगर->id, mvmvअगर->color,
					      शून्य, &mvm->snअगर_sta,
					      &mvm->snअगर_queue,
					      IWL_MVM_TX_FIFO_BE);
पूर्ण

पूर्णांक iwl_mvm_rm_snअगर_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON_ONCE(mvm->snअगर_sta.sta_id == IWL_MVM_INVALID_STA))
		वापस -EINVAL;

	iwl_mvm_disable_txq(mvm, शून्य, mvm->snअगर_queue, IWL_MAX_TID_COUNT, 0);
	ret = iwl_mvm_rm_sta_common(mvm, mvm->snअगर_sta.sta_id);
	अगर (ret)
		IWL_WARN(mvm, "Failed sending remove station\n");

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_rm_aux_sta(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON_ONCE(mvm->aux_sta.sta_id == IWL_MVM_INVALID_STA))
		वापस -EINVAL;

	iwl_mvm_disable_txq(mvm, शून्य, mvm->aux_queue, IWL_MAX_TID_COUNT, 0);
	ret = iwl_mvm_rm_sta_common(mvm, mvm->aux_sta.sta_id);
	अगर (ret)
		IWL_WARN(mvm, "Failed sending remove station\n");
	iwl_mvm_dealloc_पूर्णांक_sta(mvm, &mvm->aux_sta);

	वापस ret;
पूर्ण

व्योम iwl_mvm_dealloc_snअगर_sta(काष्ठा iwl_mvm *mvm)
अणु
	iwl_mvm_dealloc_पूर्णांक_sta(mvm, &mvm->snअगर_sta);
पूर्ण

/*
 * Send the add station command क्रम the vअगर's broadcast station.
 * Assumes that the station was alपढ़ोy allocated.
 *
 * @mvm: the mvm component
 * @vअगर: the पूर्णांकerface to which the broadcast station is added
 * @bsta: the broadcast station to add.
 */
पूर्णांक iwl_mvm_send_add_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_पूर्णांक_sta *bsta = &mvmvअगर->bcast_sta;
	अटल स्थिर u8 _baddr[] = अणु0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFFपूर्ण;
	स्थिर u8 *baddr = _baddr;
	पूर्णांक queue;
	पूर्णांक ret;
	अचिन्हित पूर्णांक wdg_समयout =
		iwl_mvm_get_wd_समयout(mvm, vअगर, false, false);
	काष्ठा iwl_trans_txq_scd_cfg cfg = अणु
		.fअगरo = IWL_MVM_TX_FIFO_VO,
		.sta_id = mvmvअगर->bcast_sta.sta_id,
		.tid = IWL_MAX_TID_COUNT,
		.aggregate = false,
		.frame_limit = IWL_FRAME_LIMIT,
	पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (!iwl_mvm_has_new_tx_api(mvm)) अणु
		अगर (vअगर->type == NL80211_IFTYPE_AP ||
		    vअगर->type == NL80211_IFTYPE_ADHOC) अणु
			queue = mvm->probe_queue;
		पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
			queue = mvm->p2p_dev_queue;
		पूर्ण अन्यथा अणु
			WARN(1, "Missing required TXQ for adding bcast STA\n");
			वापस -EINVAL;
		पूर्ण

		bsta->tfd_queue_msk |= BIT(queue);

		iwl_mvm_enable_txq(mvm, शून्य, queue, 0, &cfg, wdg_समयout);
	पूर्ण

	अगर (vअगर->type == NL80211_IFTYPE_ADHOC)
		baddr = vअगर->bss_conf.bssid;

	अगर (WARN_ON_ONCE(bsta->sta_id == IWL_MVM_INVALID_STA))
		वापस -ENOSPC;

	ret = iwl_mvm_add_पूर्णांक_sta_common(mvm, bsta, baddr,
					 mvmvअगर->id, mvmvअगर->color);
	अगर (ret)
		वापस ret;

	/*
	 * For 22000 firmware and on we cannot add queue to a station unknown
	 * to firmware so enable queue here - after the station was added
	 */
	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		queue = iwl_mvm_tvqm_enable_txq(mvm, bsta->sta_id,
						IWL_MAX_TID_COUNT,
						wdg_समयout);
		अगर (queue < 0) अणु
			iwl_mvm_rm_sta_common(mvm, bsta->sta_id);
			वापस queue;
		पूर्ण

		अगर (vअगर->type == NL80211_IFTYPE_AP ||
		    vअगर->type == NL80211_IFTYPE_ADHOC)
			mvm->probe_queue = queue;
		अन्यथा अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE)
			mvm->p2p_dev_queue = queue;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_मुक्त_bcast_sta_queues(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक queue;

	lockdep_निश्चित_held(&mvm->mutex);

	iwl_mvm_flush_sta(mvm, &mvmvअगर->bcast_sta, true);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_ADHOC:
		queue = mvm->probe_queue;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		queue = mvm->p2p_dev_queue;
		अवरोध;
	शेष:
		WARN(1, "Can't free bcast queue on vif type %d\n",
		     vअगर->type);
		वापस;
	पूर्ण

	iwl_mvm_disable_txq(mvm, शून्य, queue, IWL_MAX_TID_COUNT, 0);
	अगर (iwl_mvm_has_new_tx_api(mvm))
		वापस;

	WARN_ON(!(mvmvअगर->bcast_sta.tfd_queue_msk & BIT(queue)));
	mvmvअगर->bcast_sta.tfd_queue_msk &= ~BIT(queue);
पूर्ण

/* Send the FW a request to हटाओ the station from it's पूर्णांकernal data
 * काष्ठाures, but DO NOT हटाओ the entry from the local data काष्ठाures. */
पूर्णांक iwl_mvm_send_rm_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	iwl_mvm_मुक्त_bcast_sta_queues(mvm, vअगर);

	ret = iwl_mvm_rm_sta_common(mvm, mvmvअगर->bcast_sta.sta_id);
	अगर (ret)
		IWL_WARN(mvm, "Failed sending remove station\n");
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_alloc_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	lockdep_निश्चित_held(&mvm->mutex);

	वापस iwl_mvm_allocate_पूर्णांक_sta(mvm, &mvmvअगर->bcast_sta, 0,
					ieee80211_vअगर_type_p2p(vअगर),
					IWL_STA_GENERAL_PURPOSE);
पूर्ण

/* Allocate a new station entry क्रम the broadcast station to the given vअगर,
 * and send it to the FW.
 * Note that each P2P mac should have its own broadcast station.
 *
 * @mvm: the mvm component
 * @vअगर: the पूर्णांकerface to which the broadcast station is added
 * @bsta: the broadcast station to add. */
पूर्णांक iwl_mvm_add_p2p_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_पूर्णांक_sta *bsta = &mvmvअगर->bcast_sta;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	ret = iwl_mvm_alloc_bcast_sta(mvm, vअगर);
	अगर (ret)
		वापस ret;

	ret = iwl_mvm_send_add_bcast_sta(mvm, vअगर);

	अगर (ret)
		iwl_mvm_dealloc_पूर्णांक_sta(mvm, bsta);

	वापस ret;
पूर्ण

व्योम iwl_mvm_dealloc_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	iwl_mvm_dealloc_पूर्णांक_sta(mvm, &mvmvअगर->bcast_sta);
पूर्ण

/*
 * Send the FW a request to हटाओ the station from it's पूर्णांकernal data
 * काष्ठाures, and in addition हटाओ it from the local data काष्ठाure.
 */
पूर्णांक iwl_mvm_rm_p2p_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	ret = iwl_mvm_send_rm_bcast_sta(mvm, vअगर);

	iwl_mvm_dealloc_bcast_sta(mvm, vअगर);

	वापस ret;
पूर्ण

/*
 * Allocate a new station entry क्रम the multicast station to the given vअगर,
 * and send it to the FW.
 * Note that each AP/GO mac should have its own multicast station.
 *
 * @mvm: the mvm component
 * @vअगर: the पूर्णांकerface to which the multicast station is added
 */
पूर्णांक iwl_mvm_add_mcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_पूर्णांक_sta *msta = &mvmvअगर->mcast_sta;
	अटल स्थिर u8 _maddr[] = अणु0x03, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
	स्थिर u8 *maddr = _maddr;
	काष्ठा iwl_trans_txq_scd_cfg cfg = अणु
		.fअगरo = vअगर->type == NL80211_IFTYPE_AP ?
			IWL_MVM_TX_FIFO_MCAST : IWL_MVM_TX_FIFO_BE,
		.sta_id = msta->sta_id,
		.tid = 0,
		.aggregate = false,
		.frame_limit = IWL_FRAME_LIMIT,
	पूर्ण;
	अचिन्हित पूर्णांक समयout = iwl_mvm_get_wd_समयout(mvm, vअगर, false, false);
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (WARN_ON(vअगर->type != NL80211_IFTYPE_AP &&
		    vअगर->type != NL80211_IFTYPE_ADHOC))
		वापस -ENOTSUPP;

	/*
	 * In IBSS, ieee80211_check_queues() sets the cab_queue to be
	 * invalid, so make sure we use the queue we want.
	 * Note that this is करोne here as we want to aव्योम making DQA
	 * changes in mac80211 layer.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC)
		mvmvअगर->cab_queue = IWL_MVM_DQA_GCAST_QUEUE;

	/*
	 * While in previous FWs we had to exclude cab queue from TFD queue
	 * mask, now it is needed as any other queue.
	 */
	अगर (!iwl_mvm_has_new_tx_api(mvm) &&
	    fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE)) अणु
		iwl_mvm_enable_txq(mvm, शून्य, mvmvअगर->cab_queue, 0, &cfg,
				   समयout);
		msta->tfd_queue_msk |= BIT(mvmvअगर->cab_queue);
	पूर्ण
	ret = iwl_mvm_add_पूर्णांक_sta_common(mvm, msta, maddr,
					 mvmvअगर->id, mvmvअगर->color);
	अगर (ret)
		जाओ err;

	/*
	 * Enable cab queue after the ADD_STA command is sent.
	 * This is needed क्रम 22000 firmware which won't accept SCD_QUEUE_CFG
	 * command with unknown station id, and क्रम FW that करोesn't support
	 * station API since the cab queue is not included in the
	 * tfd_queue_mask.
	 */
	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		पूर्णांक queue = iwl_mvm_tvqm_enable_txq(mvm, msta->sta_id,
						    0,
						    समयout);
		अगर (queue < 0) अणु
			ret = queue;
			जाओ err;
		पूर्ण
		mvmvअगर->cab_queue = queue;
	पूर्ण अन्यथा अगर (!fw_has_api(&mvm->fw->ucode_capa,
			       IWL_UCODE_TLV_API_STA_TYPE))
		iwl_mvm_enable_txq(mvm, शून्य, mvmvअगर->cab_queue, 0, &cfg,
				   समयout);

	वापस 0;
err:
	iwl_mvm_dealloc_पूर्णांक_sta(mvm, msta);
	वापस ret;
पूर्ण

अटल पूर्णांक __iwl_mvm_हटाओ_sta_key(काष्ठा iwl_mvm *mvm, u8 sta_id,
				    काष्ठा ieee80211_key_conf *keyconf,
				    bool mcast)
अणु
	जोड़ अणु
		काष्ठा iwl_mvm_add_sta_key_cmd_v1 cmd_v1;
		काष्ठा iwl_mvm_add_sta_key_cmd cmd;
	पूर्ण u = अणुपूर्ण;
	bool new_api = fw_has_api(&mvm->fw->ucode_capa,
				  IWL_UCODE_TLV_API_TKIP_MIC_KEYS);
	__le16 key_flags;
	पूर्णांक ret, size;
	u32 status;

	/* This is a valid situation क्रम GTK removal */
	अगर (sta_id == IWL_MVM_INVALID_STA)
		वापस 0;

	key_flags = cpu_to_le16((keyconf->keyidx << STA_KEY_FLG_KEYID_POS) &
				 STA_KEY_FLG_KEYID_MSK);
	key_flags |= cpu_to_le16(STA_KEY_FLG_NO_ENC | STA_KEY_FLG_WEP_KEY_MAP);
	key_flags |= cpu_to_le16(STA_KEY_NOT_VALID);

	अगर (mcast)
		key_flags |= cpu_to_le16(STA_KEY_MULTICAST);

	/*
	 * The fields asचिन्हित here are in the same location at the start
	 * of the command, so we can करो this जोड़ trick.
	 */
	u.cmd.common.key_flags = key_flags;
	u.cmd.common.key_offset = keyconf->hw_key_idx;
	u.cmd.common.sta_id = sta_id;

	size = new_api ? माप(u.cmd) : माप(u.cmd_v1);

	status = ADD_STA_SUCCESS;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA_KEY, size, &u.cmd,
					  &status);

	चयन (status) अणु
	हाल ADD_STA_SUCCESS:
		IWL_DEBUG_WEP(mvm, "MODIFY_STA: remove sta key passed\n");
		अवरोध;
	शेष:
		ret = -EIO;
		IWL_ERR(mvm, "MODIFY_STA: remove sta key failed\n");
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Send the FW a request to हटाओ the station from it's पूर्णांकernal data
 * काष्ठाures, and in addition हटाओ it from the local data काष्ठाure.
 */
पूर्णांक iwl_mvm_rm_mcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	iwl_mvm_flush_sta(mvm, &mvmvअगर->mcast_sta, true);

	iwl_mvm_disable_txq(mvm, शून्य, mvmvअगर->cab_queue, 0, 0);

	ret = iwl_mvm_rm_sta_common(mvm, mvmvअगर->mcast_sta.sta_id);
	अगर (ret)
		IWL_WARN(mvm, "Failed sending remove station\n");

	वापस ret;
पूर्ण

#घोषणा IWL_MAX_RX_BA_SESSIONS 16

अटल व्योम iwl_mvm_sync_rxq_del_ba(काष्ठा iwl_mvm *mvm, u8 baid)
अणु
	काष्ठा iwl_mvm_delba_data notअगर = अणु
		.baid = baid,
	पूर्ण;

	iwl_mvm_sync_rx_queues_पूर्णांकernal(mvm, IWL_MVM_RXQ_NOTIF_DEL_BA, true,
					&notअगर, माप(notअगर));
पूर्ण;

अटल व्योम iwl_mvm_मुक्त_reorder(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_mvm_baid_data *data)
अणु
	पूर्णांक i;

	iwl_mvm_sync_rxq_del_ba(mvm, data->baid);

	क्रम (i = 0; i < mvm->trans->num_rx_queues; i++) अणु
		पूर्णांक j;
		काष्ठा iwl_mvm_reorder_buffer *reorder_buf =
			&data->reorder_buf[i];
		काष्ठा iwl_mvm_reorder_buf_entry *entries =
			&data->entries[i * data->entries_per_queue];

		spin_lock_bh(&reorder_buf->lock);
		अगर (likely(!reorder_buf->num_stored)) अणु
			spin_unlock_bh(&reorder_buf->lock);
			जारी;
		पूर्ण

		/*
		 * This shouldn't happen in regular DELBA since the पूर्णांकernal
		 * delBA notअगरication should trigger a release of all frames in
		 * the reorder buffer.
		 */
		WARN_ON(1);

		क्रम (j = 0; j < reorder_buf->buf_size; j++)
			__skb_queue_purge(&entries[j].e.frames);
		/*
		 * Prevent समयr re-arm. This prevents a very far fetched हाल
		 * where we समयd out on the notअगरication. There may be prior
		 * RX frames pending in the RX queue beक्रमe the notअगरication
		 * that might get processed between now and the actual deletion
		 * and we would re-arm the समयr although we are deleting the
		 * reorder buffer.
		 */
		reorder_buf->हटाओd = true;
		spin_unlock_bh(&reorder_buf->lock);
		del_समयr_sync(&reorder_buf->reorder_समयr);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_init_reorder_buffer(काष्ठा iwl_mvm *mvm,
					काष्ठा iwl_mvm_baid_data *data,
					u16 ssn, u16 buf_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mvm->trans->num_rx_queues; i++) अणु
		काष्ठा iwl_mvm_reorder_buffer *reorder_buf =
			&data->reorder_buf[i];
		काष्ठा iwl_mvm_reorder_buf_entry *entries =
			&data->entries[i * data->entries_per_queue];
		पूर्णांक j;

		reorder_buf->num_stored = 0;
		reorder_buf->head_sn = ssn;
		reorder_buf->buf_size = buf_size;
		/* rx reorder समयr */
		समयr_setup(&reorder_buf->reorder_समयr,
			    iwl_mvm_reorder_समयr_expired, 0);
		spin_lock_init(&reorder_buf->lock);
		reorder_buf->mvm = mvm;
		reorder_buf->queue = i;
		reorder_buf->valid = false;
		क्रम (j = 0; j < reorder_buf->buf_size; j++)
			__skb_queue_head_init(&entries[j].e.frames);
	पूर्ण
पूर्ण

पूर्णांक iwl_mvm_sta_rx_agg(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
		       पूर्णांक tid, u16 ssn, bool start, u16 buf_size, u16 समयout)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_add_sta_cmd cmd = अणुपूर्ण;
	काष्ठा iwl_mvm_baid_data *baid_data = शून्य;
	पूर्णांक ret;
	u32 status;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (start && mvm->rx_ba_sessions >= IWL_MAX_RX_BA_SESSIONS) अणु
		IWL_WARN(mvm, "Not enough RX BA SESSIONS\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (iwl_mvm_has_new_rx_api(mvm) && start) अणु
		u16 reorder_buf_size = buf_size * माप(baid_data->entries[0]);

		/* sparse करोesn't like the __align() so don't check */
#अगर_अघोषित __CHECKER__
		/*
		 * The भागision below will be OK अगर either the cache line size
		 * can be भागided by the entry size (ALIGN will round up) or अगर
		 * अगर the entry size can be भागided by the cache line size, in
		 * which हाल the ALIGN() will करो nothing.
		 */
		BUILD_BUG_ON(SMP_CACHE_BYTES % माप(baid_data->entries[0]) &&
			     माप(baid_data->entries[0]) % SMP_CACHE_BYTES);
#पूर्ण_अगर

		/*
		 * Upward align the reorder buffer size to fill an entire cache
		 * line क्रम each queue, to aव्योम sharing cache lines between
		 * dअगरferent queues.
		 */
		reorder_buf_size = ALIGN(reorder_buf_size, SMP_CACHE_BYTES);

		/*
		 * Allocate here so अगर allocation fails we can bail out early
		 * beक्रमe starting the BA session in the firmware
		 */
		baid_data = kzalloc(माप(*baid_data) +
				    mvm->trans->num_rx_queues *
				    reorder_buf_size,
				    GFP_KERNEL);
		अगर (!baid_data)
			वापस -ENOMEM;

		/*
		 * This भागision is why we need the above BUILD_BUG_ON(),
		 * अगर that करोesn't hold then this will not be right.
		 */
		baid_data->entries_per_queue =
			reorder_buf_size / माप(baid_data->entries[0]);
	पूर्ण

	cmd.mac_id_n_color = cpu_to_le32(mvm_sta->mac_id_n_color);
	cmd.sta_id = mvm_sta->sta_id;
	cmd.add_modअगरy = STA_MODE_MODIFY;
	अगर (start) अणु
		cmd.add_immediate_ba_tid = (u8) tid;
		cmd.add_immediate_ba_ssn = cpu_to_le16(ssn);
		cmd.rx_ba_winकरोw = cpu_to_le16(buf_size);
	पूर्ण अन्यथा अणु
		cmd.हटाओ_immediate_ba_tid = (u8) tid;
	पूर्ण
	cmd.modअगरy_mask = start ? STA_MODIFY_ADD_BA_TID :
				  STA_MODIFY_REMOVE_BA_TID;

	status = ADD_STA_SUCCESS;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA,
					  iwl_mvm_add_sta_cmd_size(mvm),
					  &cmd, &status);
	अगर (ret)
		जाओ out_मुक्त;

	चयन (status & IWL_ADD_STA_STATUS_MASK) अणु
	हाल ADD_STA_SUCCESS:
		IWL_DEBUG_HT(mvm, "RX BA Session %sed in fw\n",
			     start ? "start" : "stopp");
		अवरोध;
	हाल ADD_STA_IMMEDIATE_BA_FAILURE:
		IWL_WARN(mvm, "RX BA Session refused by fw\n");
		ret = -ENOSPC;
		अवरोध;
	शेष:
		ret = -EIO;
		IWL_ERR(mvm, "RX BA Session failed %sing, status 0x%x\n",
			start ? "start" : "stopp", status);
		अवरोध;
	पूर्ण

	अगर (ret)
		जाओ out_मुक्त;

	अगर (start) अणु
		u8 baid;

		mvm->rx_ba_sessions++;

		अगर (!iwl_mvm_has_new_rx_api(mvm))
			वापस 0;

		अगर (WARN_ON(!(status & IWL_ADD_STA_BAID_VALID_MASK))) अणु
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		baid = (u8)((status & IWL_ADD_STA_BAID_MASK) >>
			    IWL_ADD_STA_BAID_SHIFT);
		baid_data->baid = baid;
		baid_data->समयout = समयout;
		baid_data->last_rx = jअगरfies;
		baid_data->rcu_ptr = &mvm->baid_map[baid];
		समयr_setup(&baid_data->session_समयr,
			    iwl_mvm_rx_agg_session_expired, 0);
		baid_data->mvm = mvm;
		baid_data->tid = tid;
		baid_data->sta_id = mvm_sta->sta_id;

		mvm_sta->tid_to_baid[tid] = baid;
		अगर (समयout)
			mod_समयr(&baid_data->session_समयr,
				  TU_TO_EXP_TIME(समयout * 2));

		iwl_mvm_init_reorder_buffer(mvm, baid_data, ssn, buf_size);
		/*
		 * protect the BA data with RCU to cover a हाल where our
		 * पूर्णांकernal RX sync mechanism will समयout (not that it's
		 * supposed to happen) and we will मुक्त the session data जबतक
		 * RX is being processed in parallel
		 */
		IWL_DEBUG_HT(mvm, "Sta %d(%d) is assigned to BAID %d\n",
			     mvm_sta->sta_id, tid, baid);
		WARN_ON(rcu_access_poपूर्णांकer(mvm->baid_map[baid]));
		rcu_assign_poपूर्णांकer(mvm->baid_map[baid], baid_data);
	पूर्ण अन्यथा  अणु
		u8 baid = mvm_sta->tid_to_baid[tid];

		अगर (mvm->rx_ba_sessions > 0)
			/* check that restart flow didn't zero the counter */
			mvm->rx_ba_sessions--;
		अगर (!iwl_mvm_has_new_rx_api(mvm))
			वापस 0;

		अगर (WARN_ON(baid == IWL_RX_REORDER_DATA_INVALID_BAID))
			वापस -EINVAL;

		baid_data = rcu_access_poपूर्णांकer(mvm->baid_map[baid]);
		अगर (WARN_ON(!baid_data))
			वापस -EINVAL;

		/* synchronize all rx queues so we can safely delete */
		iwl_mvm_मुक्त_reorder(mvm, baid_data);
		del_समयr_sync(&baid_data->session_समयr);
		RCU_INIT_POINTER(mvm->baid_map[baid], शून्य);
		kमुक्त_rcu(baid_data, rcu_head);
		IWL_DEBUG_HT(mvm, "BAID %d is free\n", baid);
	पूर्ण
	वापस 0;

out_मुक्त:
	kमुक्त(baid_data);
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_sta_tx_agg(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
		       पूर्णांक tid, u8 queue, bool start)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_add_sta_cmd cmd = अणुपूर्ण;
	पूर्णांक ret;
	u32 status;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (start) अणु
		mvm_sta->tfd_queue_msk |= BIT(queue);
		mvm_sta->tid_disable_agg &= ~BIT(tid);
	पूर्ण अन्यथा अणु
		/* In DQA-mode the queue isn't हटाओd on agg termination */
		mvm_sta->tid_disable_agg |= BIT(tid);
	पूर्ण

	cmd.mac_id_n_color = cpu_to_le32(mvm_sta->mac_id_n_color);
	cmd.sta_id = mvm_sta->sta_id;
	cmd.add_modअगरy = STA_MODE_MODIFY;
	अगर (!iwl_mvm_has_new_tx_api(mvm))
		cmd.modअगरy_mask = STA_MODIFY_QUEUES;
	cmd.modअगरy_mask |= STA_MODIFY_TID_DISABLE_TX;
	cmd.tfd_queue_msk = cpu_to_le32(mvm_sta->tfd_queue_msk);
	cmd.tid_disable_tx = cpu_to_le16(mvm_sta->tid_disable_agg);

	status = ADD_STA_SUCCESS;
	ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA,
					  iwl_mvm_add_sta_cmd_size(mvm),
					  &cmd, &status);
	अगर (ret)
		वापस ret;

	चयन (status & IWL_ADD_STA_STATUS_MASK) अणु
	हाल ADD_STA_SUCCESS:
		अवरोध;
	शेष:
		ret = -EIO;
		IWL_ERR(mvm, "TX BA Session failed %sing, status 0x%x\n",
			start ? "start" : "stopp", status);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

स्थिर u8 tid_to_mac80211_ac[] = अणु
	IEEE80211_AC_BE,
	IEEE80211_AC_BK,
	IEEE80211_AC_BK,
	IEEE80211_AC_BE,
	IEEE80211_AC_VI,
	IEEE80211_AC_VI,
	IEEE80211_AC_VO,
	IEEE80211_AC_VO,
	IEEE80211_AC_VO, /* We treat MGMT as TID 8, which is set as AC_VO */
पूर्ण;

अटल स्थिर u8 tid_to_ucode_ac[] = अणु
	AC_BE,
	AC_BK,
	AC_BK,
	AC_BE,
	AC_VI,
	AC_VI,
	AC_VO,
	AC_VO,
पूर्ण;

पूर्णांक iwl_mvm_sta_tx_agg_start(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta, u16 tid, u16 *ssn)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_tid_data *tid_data;
	u16 normalized_ssn;
	u16 txq_id;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(tid >= IWL_MAX_TID_COUNT))
		वापस -EINVAL;

	अगर (mvmsta->tid_data[tid].state != IWL_AGG_QUEUED &&
	    mvmsta->tid_data[tid].state != IWL_AGG_OFF) अणु
		IWL_ERR(mvm,
			"Start AGG when state is not IWL_AGG_QUEUED or IWL_AGG_OFF %d!\n",
			mvmsta->tid_data[tid].state);
		वापस -ENXIO;
	पूर्ण

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (mvmsta->tid_data[tid].txq_id == IWL_MVM_INVALID_QUEUE &&
	    iwl_mvm_has_new_tx_api(mvm)) अणु
		u8 ac = tid_to_mac80211_ac[tid];

		ret = iwl_mvm_sta_alloc_queue_tvqm(mvm, sta, ac, tid);
		अगर (ret)
			वापस ret;
	पूर्ण

	spin_lock_bh(&mvmsta->lock);

	/*
	 * Note the possible हालs:
	 *  1. An enabled TXQ - TXQ needs to become agg'ed
	 *  2. The TXQ hasn't yet been enabled, so find a मुक्त one and mark
	 *	it as reserved
	 */
	txq_id = mvmsta->tid_data[tid].txq_id;
	अगर (txq_id == IWL_MVM_INVALID_QUEUE) अणु
		ret = iwl_mvm_find_मुक्त_queue(mvm, mvmsta->sta_id,
					      IWL_MVM_DQA_MIN_DATA_QUEUE,
					      IWL_MVM_DQA_MAX_DATA_QUEUE);
		अगर (ret < 0) अणु
			IWL_ERR(mvm, "Failed to allocate agg queue\n");
			जाओ out;
		पूर्ण

		txq_id = ret;

		/* TXQ hasn't yet been enabled, so mark it only as reserved */
		mvm->queue_info[txq_id].status = IWL_MVM_QUEUE_RESERVED;
	पूर्ण अन्यथा अगर (WARN_ON(txq_id >= IWL_MAX_HW_QUEUES)) अणु
		ret = -ENXIO;
		IWL_ERR(mvm, "tid_id %d out of range (0, %d)!\n",
			tid, IWL_MAX_HW_QUEUES - 1);
		जाओ out;

	पूर्ण अन्यथा अगर (unlikely(mvm->queue_info[txq_id].status ==
			    IWL_MVM_QUEUE_SHARED)) अणु
		ret = -ENXIO;
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Can't start tid %d agg on shared queue!\n",
				    tid);
		जाओ out;
	पूर्ण

	IWL_DEBUG_TX_QUEUES(mvm,
			    "AGG for tid %d will be on queue #%d\n",
			    tid, txq_id);

	tid_data = &mvmsta->tid_data[tid];
	tid_data->ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);
	tid_data->txq_id = txq_id;
	*ssn = tid_data->ssn;

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Start AGG: sta %d tid %d queue %d - ssn = %d, next_recl = %d\n",
			    mvmsta->sta_id, tid, txq_id, tid_data->ssn,
			    tid_data->next_reclaimed);

	/*
	 * In 22000 HW, the next_reclaimed index is only 8 bit, so we'll need
	 * to align the wrap around of ssn so we compare relevant values.
	 */
	normalized_ssn = tid_data->ssn;
	अगर (mvm->trans->trans_cfg->gen2)
		normalized_ssn &= 0xff;

	अगर (normalized_ssn == tid_data->next_reclaimed) अणु
		tid_data->state = IWL_AGG_STARTING;
		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
	पूर्ण अन्यथा अणु
		tid_data->state = IWL_EMPTYING_HW_QUEUE_ADDBA;
		ret = IEEE80211_AMPDU_TX_START_DELAY_ADDBA;
	पूर्ण

out:
	spin_unlock_bh(&mvmsta->lock);

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_sta_tx_agg_oper(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, u16 tid, u16 buf_size,
			    bool amsdu)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];
	अचिन्हित पूर्णांक wdg_समयout =
		iwl_mvm_get_wd_समयout(mvm, vअगर, sta->tdls, false);
	पूर्णांक queue, ret;
	bool alloc_queue = true;
	क्रमागत iwl_mvm_queue_status queue_status;
	u16 ssn;

	काष्ठा iwl_trans_txq_scd_cfg cfg = अणु
		.sta_id = mvmsta->sta_id,
		.tid = tid,
		.frame_limit = buf_size,
		.aggregate = true,
	पूर्ण;

	/*
	 * When FW supports TLC_OFFLOAD, it also implements Tx aggregation
	 * manager, so this function should never be called in this हाल.
	 */
	अगर (WARN_ON_ONCE(iwl_mvm_has_tlc_offload(mvm)))
		वापस -EINVAL;

	BUILD_BUG_ON((माप(mvmsta->agg_tids) * BITS_PER_BYTE)
		     != IWL_MAX_TID_COUNT);

	spin_lock_bh(&mvmsta->lock);
	ssn = tid_data->ssn;
	queue = tid_data->txq_id;
	tid_data->state = IWL_AGG_ON;
	mvmsta->agg_tids |= BIT(tid);
	tid_data->ssn = 0xffff;
	tid_data->amsdu_in_ampdu_allowed = amsdu;
	spin_unlock_bh(&mvmsta->lock);

	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		/*
		 * If there is no queue क्रम this tid, iwl_mvm_sta_tx_agg_start()
		 * would have failed, so अगर we are here there is no need to
		 * allocate a queue.
		 * However, अगर aggregation size is dअगरferent than the शेष
		 * size, the scheduler should be reconfigured.
		 * We cannot करो this with the new TX API, so वापस unsupported
		 * क्रम now, until it will be offloaded to firmware..
		 * Note that अगर SCD शेष value changes - this condition
		 * should be updated as well.
		 */
		अगर (buf_size < IWL_FRAME_LIMIT)
			वापस -ENOTSUPP;

		ret = iwl_mvm_sta_tx_agg(mvm, sta, tid, queue, true);
		अगर (ret)
			वापस -EIO;
		जाओ out;
	पूर्ण

	cfg.fअगरo = iwl_mvm_ac_to_tx_fअगरo[tid_to_mac80211_ac[tid]];

	queue_status = mvm->queue_info[queue].status;

	/* Maybe there is no need to even alloc a queue... */
	अगर (mvm->queue_info[queue].status == IWL_MVM_QUEUE_READY)
		alloc_queue = false;

	/*
	 * Only reconfig the SCD क्रम the queue अगर the winकरोw size has
	 * changed from current (become smaller)
	 */
	अगर (!alloc_queue && buf_size < IWL_FRAME_LIMIT) अणु
		/*
		 * If reconfiguring an existing queue, it first must be
		 * drained
		 */
		ret = iwl_trans_रुको_tx_queues_empty(mvm->trans,
						     BIT(queue));
		अगर (ret) अणु
			IWL_ERR(mvm,
				"Error draining queue before reconfig\n");
			वापस ret;
		पूर्ण

		ret = iwl_mvm_reconfig_scd(mvm, queue, cfg.fअगरo,
					   mvmsta->sta_id, tid,
					   buf_size, ssn);
		अगर (ret) अणु
			IWL_ERR(mvm,
				"Error reconfiguring TXQ #%d\n", queue);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (alloc_queue)
		iwl_mvm_enable_txq(mvm, sta, queue, ssn,
				   &cfg, wdg_समयout);

	/* Send ADD_STA command to enable aggs only अगर the queue isn't shared */
	अगर (queue_status != IWL_MVM_QUEUE_SHARED) अणु
		ret = iwl_mvm_sta_tx_agg(mvm, sta, tid, queue, true);
		अगर (ret)
			वापस -EIO;
	पूर्ण

	/* No need to mark as reserved */
	mvm->queue_info[queue].status = IWL_MVM_QUEUE_READY;

out:
	/*
	 * Even though in theory the peer could have dअगरferent
	 * aggregation reorder buffer sizes क्रम dअगरferent sessions,
	 * our ucode करोesn't allow क्रम that and has a global limit
	 * क्रम each station. Thereक्रमe, use the minimum of all the
	 * aggregation sessions and our शेष value.
	 */
	mvmsta->max_agg_bufsize =
		min(mvmsta->max_agg_bufsize, buf_size);
	mvmsta->lq_sta.rs_drv.lq.agg_frame_cnt_limit = mvmsta->max_agg_bufsize;

	IWL_DEBUG_HT(mvm, "Tx aggregation enabled on ra = %pM tid = %d\n",
		     sta->addr, tid);

	वापस iwl_mvm_send_lq_cmd(mvm, &mvmsta->lq_sta.rs_drv.lq);
पूर्ण

अटल व्योम iwl_mvm_unreserve_agg_queue(काष्ठा iwl_mvm *mvm,
					काष्ठा iwl_mvm_sta *mvmsta,
					काष्ठा iwl_mvm_tid_data *tid_data)
अणु
	u16 txq_id = tid_data->txq_id;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (iwl_mvm_has_new_tx_api(mvm))
		वापस;

	/*
	 * The TXQ is marked as reserved only अगर no traffic came through yet
	 * This means no traffic has been sent on this TID (agg'd or not), so
	 * we no दीर्घer have use क्रम the queue. Since it hasn't even been
	 * allocated through iwl_mvm_enable_txq, so we can just mark it back as
	 * मुक्त.
	 */
	अगर (mvm->queue_info[txq_id].status == IWL_MVM_QUEUE_RESERVED) अणु
		mvm->queue_info[txq_id].status = IWL_MVM_QUEUE_FREE;
		tid_data->txq_id = IWL_MVM_INVALID_QUEUE;
	पूर्ण
पूर्ण

पूर्णांक iwl_mvm_sta_tx_agg_stop(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];
	u16 txq_id;
	पूर्णांक err;

	/*
	 * If mac80211 is cleaning its state, then say that we finished since
	 * our state has been cleared anyway.
	 */
	अगर (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) अणु
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		वापस 0;
	पूर्ण

	spin_lock_bh(&mvmsta->lock);

	txq_id = tid_data->txq_id;

	IWL_DEBUG_TX_QUEUES(mvm, "Stop AGG: sta %d tid %d q %d state %d\n",
			    mvmsta->sta_id, tid, txq_id, tid_data->state);

	mvmsta->agg_tids &= ~BIT(tid);

	iwl_mvm_unreserve_agg_queue(mvm, mvmsta, tid_data);

	चयन (tid_data->state) अणु
	हाल IWL_AGG_ON:
		tid_data->ssn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);

		IWL_DEBUG_TX_QUEUES(mvm,
				    "ssn = %d, next_recl = %d\n",
				    tid_data->ssn, tid_data->next_reclaimed);

		tid_data->ssn = 0xffff;
		tid_data->state = IWL_AGG_OFF;
		spin_unlock_bh(&mvmsta->lock);

		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);

		iwl_mvm_sta_tx_agg(mvm, sta, tid, txq_id, false);
		वापस 0;
	हाल IWL_AGG_STARTING:
	हाल IWL_EMPTYING_HW_QUEUE_ADDBA:
		/*
		 * The agg session has been stopped beक्रमe it was set up. This
		 * can happen when the AddBA समयr बार out क्रम example.
		 */

		/* No barriers since we are under mutex */
		lockdep_निश्चित_held(&mvm->mutex);

		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		tid_data->state = IWL_AGG_OFF;
		err = 0;
		अवरोध;
	शेष:
		IWL_ERR(mvm,
			"Stopping AGG while state not ON or starting for %d on %d (%d)\n",
			mvmsta->sta_id, tid, tid_data->state);
		IWL_ERR(mvm,
			"\ttid_data->txq_id = %d\n", tid_data->txq_id);
		err = -EINVAL;
	पूर्ण

	spin_unlock_bh(&mvmsta->lock);

	वापस err;
पूर्ण

पूर्णांक iwl_mvm_sta_tx_agg_flush(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];
	u16 txq_id;
	क्रमागत iwl_mvm_agg_state old_state;

	/*
	 * First set the agg state to OFF to aव्योम calling
	 * ieee80211_stop_tx_ba_cb in iwl_mvm_check_ratid_empty.
	 */
	spin_lock_bh(&mvmsta->lock);
	txq_id = tid_data->txq_id;
	IWL_DEBUG_TX_QUEUES(mvm, "Flush AGG: sta %d tid %d q %d state %d\n",
			    mvmsta->sta_id, tid, txq_id, tid_data->state);
	old_state = tid_data->state;
	tid_data->state = IWL_AGG_OFF;
	mvmsta->agg_tids &= ~BIT(tid);
	spin_unlock_bh(&mvmsta->lock);

	iwl_mvm_unreserve_agg_queue(mvm, mvmsta, tid_data);

	अगर (old_state >= IWL_AGG_ON) अणु
		iwl_mvm_drain_sta(mvm, mvmsta, true);

		अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
			अगर (iwl_mvm_flush_sta_tids(mvm, mvmsta->sta_id,
						   BIT(tid)))
				IWL_ERR(mvm, "Couldn't flush the AGG queue\n");
			iwl_trans_रुको_txq_empty(mvm->trans, txq_id);
		पूर्ण अन्यथा अणु
			अगर (iwl_mvm_flush_tx_path(mvm, BIT(txq_id)))
				IWL_ERR(mvm, "Couldn't flush the AGG queue\n");
			iwl_trans_रुको_tx_queues_empty(mvm->trans, BIT(txq_id));
		पूर्ण

		iwl_mvm_drain_sta(mvm, mvmsta, false);

		iwl_mvm_sta_tx_agg(mvm, sta, tid, txq_id, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_set_fw_key_idx(काष्ठा iwl_mvm *mvm)
अणु
	पूर्णांक i, max = -1, max_offs = -1;

	lockdep_निश्चित_held(&mvm->mutex);

	/* Pick the unused key offset with the highest 'deleted'
	 * counter. Every समय a key is deleted, all the counters
	 * are incremented and the one that was just deleted is
	 * reset to zero. Thus, the highest counter is the one
	 * that was deleted दीर्घest ago. Pick that one.
	 */
	क्रम (i = 0; i < STA_KEY_MAX_NUM; i++) अणु
		अगर (test_bit(i, mvm->fw_key_table))
			जारी;
		अगर (mvm->fw_key_deleted[i] > max) अणु
			max = mvm->fw_key_deleted[i];
			max_offs = i;
		पूर्ण
	पूर्ण

	अगर (max_offs < 0)
		वापस STA_KEY_IDX_INVALID;

	वापस max_offs;
पूर्ण

अटल काष्ठा iwl_mvm_sta *iwl_mvm_get_key_sta(काष्ठा iwl_mvm *mvm,
					       काष्ठा ieee80211_vअगर *vअगर,
					       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (sta)
		वापस iwl_mvm_sta_from_mac80211(sta);

	/*
	 * The device expects GTKs क्रम station पूर्णांकerfaces to be
	 * installed as GTKs क्रम the AP station. If we have no
	 * station ID, then use AP's station ID.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_STATION &&
	    mvmvअगर->ap_sta_id != IWL_MVM_INVALID_STA) अणु
		u8 sta_id = mvmvअगर->ap_sta_id;

		sta = rcu_dereference_check(mvm->fw_id_to_mac_id[sta_id],
					    lockdep_is_held(&mvm->mutex));

		/*
		 * It is possible that the 'sta' parameter is शून्य,
		 * क्रम example when a GTK is हटाओd - the sta_id will then
		 * be the AP ID, and no station was passed by mac80211.
		 */
		अगर (IS_ERR_OR_शून्य(sta))
			वापस शून्य;

		वापस iwl_mvm_sta_from_mac80211(sta);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक iwl_mvm_send_sta_key(काष्ठा iwl_mvm *mvm,
				u32 sta_id,
				काष्ठा ieee80211_key_conf *key, bool mcast,
				u32 tkip_iv32, u16 *tkip_p1k, u32 cmd_flags,
				u8 key_offset, bool mfp)
अणु
	जोड़ अणु
		काष्ठा iwl_mvm_add_sta_key_cmd_v1 cmd_v1;
		काष्ठा iwl_mvm_add_sta_key_cmd cmd;
	पूर्ण u = अणुपूर्ण;
	__le16 key_flags;
	पूर्णांक ret;
	u32 status;
	u16 keyidx;
	u64 pn = 0;
	पूर्णांक i, size;
	bool new_api = fw_has_api(&mvm->fw->ucode_capa,
				  IWL_UCODE_TLV_API_TKIP_MIC_KEYS);

	अगर (sta_id == IWL_MVM_INVALID_STA)
		वापस -EINVAL;

	keyidx = (key->keyidx << STA_KEY_FLG_KEYID_POS) &
		 STA_KEY_FLG_KEYID_MSK;
	key_flags = cpu_to_le16(keyidx);
	key_flags |= cpu_to_le16(STA_KEY_FLG_WEP_KEY_MAP);

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		key_flags |= cpu_to_le16(STA_KEY_FLG_TKIP);
		अगर (new_api) अणु
			स_नकल((व्योम *)&u.cmd.tx_mic_key,
			       &key->key[NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY],
			       IWL_MIC_KEY_SIZE);

			स_नकल((व्योम *)&u.cmd.rx_mic_key,
			       &key->key[NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY],
			       IWL_MIC_KEY_SIZE);
			pn = atomic64_पढ़ो(&key->tx_pn);

		पूर्ण अन्यथा अणु
			u.cmd_v1.tkip_rx_tsc_byte2 = tkip_iv32;
			क्रम (i = 0; i < 5; i++)
				u.cmd_v1.tkip_rx_ttak[i] =
					cpu_to_le16(tkip_p1k[i]);
		पूर्ण
		स_नकल(u.cmd.common.key, key->key, key->keylen);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		key_flags |= cpu_to_le16(STA_KEY_FLG_CCM);
		स_नकल(u.cmd.common.key, key->key, key->keylen);
		अगर (new_api)
			pn = atomic64_पढ़ो(&key->tx_pn);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		key_flags |= cpu_to_le16(STA_KEY_FLG_WEP_13BYTES);
		fallthrough;
	हाल WLAN_CIPHER_SUITE_WEP40:
		key_flags |= cpu_to_le16(STA_KEY_FLG_WEP);
		स_नकल(u.cmd.common.key + 3, key->key, key->keylen);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		key_flags |= cpu_to_le16(STA_KEY_FLG_KEY_32BYTES);
		fallthrough;
	हाल WLAN_CIPHER_SUITE_GCMP:
		key_flags |= cpu_to_le16(STA_KEY_FLG_GCMP);
		स_नकल(u.cmd.common.key, key->key, key->keylen);
		अगर (new_api)
			pn = atomic64_पढ़ो(&key->tx_pn);
		अवरोध;
	शेष:
		key_flags |= cpu_to_le16(STA_KEY_FLG_EXT);
		स_नकल(u.cmd.common.key, key->key, key->keylen);
	पूर्ण

	अगर (mcast)
		key_flags |= cpu_to_le16(STA_KEY_MULTICAST);
	अगर (mfp)
		key_flags |= cpu_to_le16(STA_KEY_MFP);

	u.cmd.common.key_offset = key_offset;
	u.cmd.common.key_flags = key_flags;
	u.cmd.common.sta_id = sta_id;

	अगर (new_api) अणु
		u.cmd.transmit_seq_cnt = cpu_to_le64(pn);
		size = माप(u.cmd);
	पूर्ण अन्यथा अणु
		size = माप(u.cmd_v1);
	पूर्ण

	status = ADD_STA_SUCCESS;
	अगर (cmd_flags & CMD_ASYNC)
		ret = iwl_mvm_send_cmd_pdu(mvm, ADD_STA_KEY, CMD_ASYNC, size,
					   &u.cmd);
	अन्यथा
		ret = iwl_mvm_send_cmd_pdu_status(mvm, ADD_STA_KEY, size,
						  &u.cmd, &status);

	चयन (status) अणु
	हाल ADD_STA_SUCCESS:
		IWL_DEBUG_WEP(mvm, "MODIFY_STA: set dynamic key passed\n");
		अवरोध;
	शेष:
		ret = -EIO;
		IWL_ERR(mvm, "MODIFY_STA: set dynamic key failed\n");
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_send_sta_igtk(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_key_conf *keyconf,
				 u8 sta_id, bool हटाओ_key)
अणु
	काष्ठा iwl_mvm_mgmt_mcast_key_cmd igtk_cmd = अणुपूर्ण;

	/* verअगरy the key details match the required command's expectations */
	अगर (WARN_ON((keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE) ||
		    (keyconf->keyidx != 4 && keyconf->keyidx != 5 &&
		     keyconf->keyidx != 6 && keyconf->keyidx != 7) ||
		    (keyconf->cipher != WLAN_CIPHER_SUITE_AES_CMAC &&
		     keyconf->cipher != WLAN_CIPHER_SUITE_BIP_GMAC_128 &&
		     keyconf->cipher != WLAN_CIPHER_SUITE_BIP_GMAC_256)))
		वापस -EINVAL;

	अगर (WARN_ON(!iwl_mvm_has_new_rx_api(mvm) &&
		    keyconf->cipher != WLAN_CIPHER_SUITE_AES_CMAC))
		वापस -EINVAL;

	igtk_cmd.key_id = cpu_to_le32(keyconf->keyidx);
	igtk_cmd.sta_id = cpu_to_le32(sta_id);

	अगर (हटाओ_key) अणु
		/* This is a valid situation क्रम IGTK */
		अगर (sta_id == IWL_MVM_INVALID_STA)
			वापस 0;

		igtk_cmd.ctrl_flags |= cpu_to_le32(STA_KEY_NOT_VALID);
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_key_seq seq;
		स्थिर u8 *pn;

		चयन (keyconf->cipher) अणु
		हाल WLAN_CIPHER_SUITE_AES_CMAC:
			igtk_cmd.ctrl_flags |= cpu_to_le32(STA_KEY_FLG_CCM);
			अवरोध;
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
		हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
			igtk_cmd.ctrl_flags |= cpu_to_le32(STA_KEY_FLG_GCMP);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		स_नकल(igtk_cmd.igtk, keyconf->key, keyconf->keylen);
		अगर (keyconf->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_256)
			igtk_cmd.ctrl_flags |=
				cpu_to_le32(STA_KEY_FLG_KEY_32BYTES);
		ieee80211_get_key_rx_seq(keyconf, 0, &seq);
		pn = seq.aes_cmac.pn;
		igtk_cmd.receive_seq_cnt = cpu_to_le64(((u64) pn[5] << 0) |
						       ((u64) pn[4] << 8) |
						       ((u64) pn[3] << 16) |
						       ((u64) pn[2] << 24) |
						       ((u64) pn[1] << 32) |
						       ((u64) pn[0] << 40));
	पूर्ण

	IWL_DEBUG_INFO(mvm, "%s %sIGTK (%d) for sta %u\n",
		       हटाओ_key ? "removing" : "installing",
		       keyconf->keyidx >= 6 ? "B" : "",
		       keyconf->keyidx, igtk_cmd.sta_id);

	अगर (!iwl_mvm_has_new_rx_api(mvm)) अणु
		काष्ठा iwl_mvm_mgmt_mcast_key_cmd_v1 igtk_cmd_v1 = अणु
			.ctrl_flags = igtk_cmd.ctrl_flags,
			.key_id = igtk_cmd.key_id,
			.sta_id = igtk_cmd.sta_id,
			.receive_seq_cnt = igtk_cmd.receive_seq_cnt
		पूर्ण;

		स_नकल(igtk_cmd_v1.igtk, igtk_cmd.igtk,
		       ARRAY_SIZE(igtk_cmd_v1.igtk));
		वापस iwl_mvm_send_cmd_pdu(mvm, MGMT_MCAST_KEY, 0,
					    माप(igtk_cmd_v1), &igtk_cmd_v1);
	पूर्ण
	वापस iwl_mvm_send_cmd_pdu(mvm, MGMT_MCAST_KEY, 0,
				    माप(igtk_cmd), &igtk_cmd);
पूर्ण


अटल अंतरभूत u8 *iwl_mvm_get_mac_addr(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (sta)
		वापस sta->addr;

	अगर (vअगर->type == NL80211_IFTYPE_STATION &&
	    mvmvअगर->ap_sta_id != IWL_MVM_INVALID_STA) अणु
		u8 sta_id = mvmvअगर->ap_sta_id;
		sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[sta_id],
						lockdep_is_held(&mvm->mutex));
		वापस sta->addr;
	पूर्ण


	वापस शून्य;
पूर्ण

अटल पूर्णांक __iwl_mvm_set_sta_key(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta,
				 काष्ठा ieee80211_key_conf *keyconf,
				 u8 key_offset,
				 bool mcast)
अणु
	पूर्णांक ret;
	स्थिर u8 *addr;
	काष्ठा ieee80211_key_seq seq;
	u16 p1k[5];
	u32 sta_id;
	bool mfp = false;

	अगर (sta) अणु
		काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);

		sta_id = mvm_sta->sta_id;
		mfp = sta->mfp;
	पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_AP &&
		   !(keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

		sta_id = mvmvअगर->mcast_sta.sta_id;
	पूर्ण अन्यथा अणु
		IWL_ERR(mvm, "Failed to find station id\n");
		वापस -EINVAL;
	पूर्ण

	चयन (keyconf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		addr = iwl_mvm_get_mac_addr(mvm, vअगर, sta);
		/* get phase 1 key from mac80211 */
		ieee80211_get_key_rx_seq(keyconf, 0, &seq);
		ieee80211_get_tkip_rx_p1k(keyconf, addr, seq.tkip.iv32, p1k);
		ret = iwl_mvm_send_sta_key(mvm, sta_id, keyconf, mcast,
					   seq.tkip.iv32, p1k, 0, key_offset,
					   mfp);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		ret = iwl_mvm_send_sta_key(mvm, sta_id, keyconf, mcast,
					   0, शून्य, 0, key_offset, mfp);
		अवरोध;
	शेष:
		ret = iwl_mvm_send_sta_key(mvm, sta_id, keyconf, mcast,
					   0, शून्य, 0, key_offset, mfp);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_set_sta_key(काष्ठा iwl_mvm *mvm,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta,
			काष्ठा ieee80211_key_conf *keyconf,
			u8 key_offset)
अणु
	bool mcast = !(keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE);
	काष्ठा iwl_mvm_sta *mvm_sta;
	u8 sta_id = IWL_MVM_INVALID_STA;
	पूर्णांक ret;
	अटल स्थिर u8 __maybe_unused zero_addr[ETH_ALEN] = अणु0पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (vअगर->type != NL80211_IFTYPE_AP ||
	    keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
		/* Get the station id from the mvm local station table */
		mvm_sta = iwl_mvm_get_key_sta(mvm, vअगर, sta);
		अगर (!mvm_sta) अणु
			IWL_ERR(mvm, "Failed to find station\n");
			वापस -EINVAL;
		पूर्ण
		sta_id = mvm_sta->sta_id;

		/*
		 * It is possible that the 'sta' parameter is शून्य, and thus
		 * there is a need to retrieve the sta from the local station
		 * table.
		 */
		अगर (!sta) अणु
			sta = rcu_dereference_रक्षित(
				mvm->fw_id_to_mac_id[sta_id],
				lockdep_is_held(&mvm->mutex));
			अगर (IS_ERR_OR_शून्य(sta)) अणु
				IWL_ERR(mvm, "Invalid station id\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (WARN_ON_ONCE(iwl_mvm_sta_from_mac80211(sta)->vअगर != vअगर))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

		sta_id = mvmvअगर->mcast_sta.sta_id;
	पूर्ण

	अगर (keyconf->cipher == WLAN_CIPHER_SUITE_AES_CMAC ||
	    keyconf->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_128 ||
	    keyconf->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_256) अणु
		ret = iwl_mvm_send_sta_igtk(mvm, keyconf, sta_id, false);
		जाओ end;
	पूर्ण

	/* If the key_offset is not pre-asचिन्हित, we need to find a
	 * new offset to use.  In normal हालs, the offset is not
	 * pre-asचिन्हित, but during HW_RESTART we want to reuse the
	 * same indices, so we pass them when this function is called.
	 *
	 * In D3 entry, we need to hardcoded the indices (because the
	 * firmware hardcodes the PTK offset to 0).  In this हाल, we
	 * need to make sure we करोn't overग_लिखो the hw_key_idx in the
	 * keyconf काष्ठाure, because otherwise we cannot configure
	 * the original ones back when resuming.
	 */
	अगर (key_offset == STA_KEY_IDX_INVALID) अणु
		key_offset  = iwl_mvm_set_fw_key_idx(mvm);
		अगर (key_offset == STA_KEY_IDX_INVALID)
			वापस -ENOSPC;
		keyconf->hw_key_idx = key_offset;
	पूर्ण

	ret = __iwl_mvm_set_sta_key(mvm, vअगर, sta, keyconf, key_offset, mcast);
	अगर (ret)
		जाओ end;

	/*
	 * For WEP, the same key is used क्रम multicast and unicast. Upload it
	 * again, using the same key offset, and now poपूर्णांकing the other one
	 * to the same key slot (offset).
	 * If this fails, हटाओ the original as well.
	 */
	अगर ((keyconf->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	     keyconf->cipher == WLAN_CIPHER_SUITE_WEP104) &&
	    sta) अणु
		ret = __iwl_mvm_set_sta_key(mvm, vअगर, sta, keyconf,
					    key_offset, !mcast);
		अगर (ret) अणु
			__iwl_mvm_हटाओ_sta_key(mvm, sta_id, keyconf, mcast);
			जाओ end;
		पूर्ण
	पूर्ण

	__set_bit(key_offset, mvm->fw_key_table);

end:
	IWL_DEBUG_WEP(mvm, "key: cipher=%x len=%d idx=%d sta=%pM ret=%d\n",
		      keyconf->cipher, keyconf->keylen, keyconf->keyidx,
		      sta ? sta->addr : zero_addr, ret);
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_हटाओ_sta_key(काष्ठा iwl_mvm *mvm,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा ieee80211_key_conf *keyconf)
अणु
	bool mcast = !(keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE);
	काष्ठा iwl_mvm_sta *mvm_sta;
	u8 sta_id = IWL_MVM_INVALID_STA;
	पूर्णांक ret, i;

	lockdep_निश्चित_held(&mvm->mutex);

	/* Get the station from the mvm local station table */
	mvm_sta = iwl_mvm_get_key_sta(mvm, vअगर, sta);
	अगर (mvm_sta)
		sta_id = mvm_sta->sta_id;
	अन्यथा अगर (!sta && vअगर->type == NL80211_IFTYPE_AP && mcast)
		sta_id = iwl_mvm_vअगर_from_mac80211(vअगर)->mcast_sta.sta_id;


	IWL_DEBUG_WEP(mvm, "mvm remove dynamic key: idx=%d sta=%d\n",
		      keyconf->keyidx, sta_id);

	अगर (keyconf->cipher == WLAN_CIPHER_SUITE_AES_CMAC ||
	    keyconf->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_128 ||
	    keyconf->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_256)
		वापस iwl_mvm_send_sta_igtk(mvm, keyconf, sta_id, true);

	अगर (!__test_and_clear_bit(keyconf->hw_key_idx, mvm->fw_key_table)) अणु
		IWL_ERR(mvm, "offset %d not used in fw key table.\n",
			keyconf->hw_key_idx);
		वापस -ENOENT;
	पूर्ण

	/* track which key was deleted last */
	क्रम (i = 0; i < STA_KEY_MAX_NUM; i++) अणु
		अगर (mvm->fw_key_deleted[i] < U8_MAX)
			mvm->fw_key_deleted[i]++;
	पूर्ण
	mvm->fw_key_deleted[keyconf->hw_key_idx] = 0;

	अगर (sta && !mvm_sta) अणु
		IWL_DEBUG_WEP(mvm, "station non-existent, early return.\n");
		वापस 0;
	पूर्ण

	ret = __iwl_mvm_हटाओ_sta_key(mvm, sta_id, keyconf, mcast);
	अगर (ret)
		वापस ret;

	/* delete WEP key twice to get rid of (now useless) offset */
	अगर (keyconf->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	    keyconf->cipher == WLAN_CIPHER_SUITE_WEP104)
		ret = __iwl_mvm_हटाओ_sta_key(mvm, sta_id, keyconf, !mcast);

	वापस ret;
पूर्ण

व्योम iwl_mvm_update_tkip_key(काष्ठा iwl_mvm *mvm,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_key_conf *keyconf,
			     काष्ठा ieee80211_sta *sta, u32 iv32,
			     u16 *phase1key)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta;
	bool mcast = !(keyconf->flags & IEEE80211_KEY_FLAG_PAIRWISE);
	bool mfp = sta ? sta->mfp : false;

	rcu_पढ़ो_lock();

	mvm_sta = iwl_mvm_get_key_sta(mvm, vअगर, sta);
	अगर (WARN_ON_ONCE(!mvm_sta))
		जाओ unlock;
	iwl_mvm_send_sta_key(mvm, mvm_sta->sta_id, keyconf, mcast,
			     iv32, phase1key, CMD_ASYNC, keyconf->hw_key_idx,
			     mfp);

 unlock:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम iwl_mvm_sta_modअगरy_ps_wake(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_add_sta_cmd cmd = अणु
		.add_modअगरy = STA_MODE_MODIFY,
		.sta_id = mvmsta->sta_id,
		.station_flags_msk = cpu_to_le32(STA_FLG_PS),
		.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color),
	पूर्ण;
	पूर्णांक ret;

	ret = iwl_mvm_send_cmd_pdu(mvm, ADD_STA, CMD_ASYNC,
				   iwl_mvm_add_sta_cmd_size(mvm), &cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send ADD_STA command (%d)\n", ret);
पूर्ण

व्योम iwl_mvm_sta_modअगरy_sleep_tx_count(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_sta *sta,
				       क्रमागत ieee80211_frame_release_type reason,
				       u16 cnt, u16 tids, bool more_data,
				       bool single_sta_queue)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_add_sta_cmd cmd = अणु
		.add_modअगरy = STA_MODE_MODIFY,
		.sta_id = mvmsta->sta_id,
		.modअगरy_mask = STA_MODIFY_SLEEPING_STA_TX_COUNT,
		.sleep_tx_count = cpu_to_le16(cnt),
		.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color),
	पूर्ण;
	पूर्णांक tid, ret;
	अचिन्हित दीर्घ _tids = tids;

	/* convert TIDs to ACs - we करोn't support TSPEC so that's OK
	 * Note that this field is reserved and unused by firmware not
	 * supporting GO uAPSD, so it's safe to always करो this.
	 */
	क्रम_each_set_bit(tid, &_tids, IWL_MAX_TID_COUNT)
		cmd.awake_acs |= BIT(tid_to_ucode_ac[tid]);

	/* If we're releasing frames from aggregation or dqa queues then check
	 * अगर all the queues that we're releasing frames from, combined, have:
	 *  - more frames than the service period, in which हाल more_data
	 *    needs to be set
	 *  - fewer than 'cnt' frames, in which हाल we need to adjust the
	 *    firmware command (but करो that unconditionally)
	 */
	अगर (single_sta_queue) अणु
		पूर्णांक reमुख्यing = cnt;
		पूर्णांक sleep_tx_count;

		spin_lock_bh(&mvmsta->lock);
		क्रम_each_set_bit(tid, &_tids, IWL_MAX_TID_COUNT) अणु
			काष्ठा iwl_mvm_tid_data *tid_data;
			u16 n_queued;

			tid_data = &mvmsta->tid_data[tid];

			n_queued = iwl_mvm_tid_queued(mvm, tid_data);
			अगर (n_queued > reमुख्यing) अणु
				more_data = true;
				reमुख्यing = 0;
				अवरोध;
			पूर्ण
			reमुख्यing -= n_queued;
		पूर्ण
		sleep_tx_count = cnt - reमुख्यing;
		अगर (reason == IEEE80211_FRAME_RELEASE_UAPSD)
			mvmsta->sleep_tx_count = sleep_tx_count;
		spin_unlock_bh(&mvmsta->lock);

		cmd.sleep_tx_count = cpu_to_le16(sleep_tx_count);
		अगर (WARN_ON(cnt - reमुख्यing == 0)) अणु
			ieee80211_sta_eosp(sta);
			वापस;
		पूर्ण
	पूर्ण

	/* Note: this is ignored by firmware not supporting GO uAPSD */
	अगर (more_data)
		cmd.sleep_state_flags |= STA_SLEEP_STATE_MOREDATA;

	अगर (reason == IEEE80211_FRAME_RELEASE_PSPOLL) अणु
		mvmsta->next_status_eosp = true;
		cmd.sleep_state_flags |= STA_SLEEP_STATE_PS_POLL;
	पूर्ण अन्यथा अणु
		cmd.sleep_state_flags |= STA_SLEEP_STATE_UAPSD;
	पूर्ण

	/* block the Tx queues until the FW updated the sleep Tx count */
	iwl_trans_block_txq_ptrs(mvm->trans, true);

	ret = iwl_mvm_send_cmd_pdu(mvm, ADD_STA,
				   CMD_ASYNC | CMD_WANT_ASYNC_CALLBACK,
				   iwl_mvm_add_sta_cmd_size(mvm), &cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send ADD_STA command (%d)\n", ret);
पूर्ण

व्योम iwl_mvm_rx_eosp_notअगर(काष्ठा iwl_mvm *mvm,
			   काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mvm_eosp_notअगरication *notअगर = (व्योम *)pkt->data;
	काष्ठा ieee80211_sta *sta;
	u32 sta_id = le32_to_cpu(notअगर->sta_id);

	अगर (WARN_ON_ONCE(sta_id >= mvm->fw->ucode_capa.num_stations))
		वापस;

	rcu_पढ़ो_lock();
	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);
	अगर (!IS_ERR_OR_शून्य(sta))
		ieee80211_sta_eosp(sta);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम iwl_mvm_sta_modअगरy_disable_tx(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_mvm_sta *mvmsta, bool disable)
अणु
	काष्ठा iwl_mvm_add_sta_cmd cmd = अणु
		.add_modअगरy = STA_MODE_MODIFY,
		.sta_id = mvmsta->sta_id,
		.station_flags = disable ? cpu_to_le32(STA_FLG_DISABLE_TX) : 0,
		.station_flags_msk = cpu_to_le32(STA_FLG_DISABLE_TX),
		.mac_id_n_color = cpu_to_le32(mvmsta->mac_id_n_color),
	पूर्ण;
	पूर्णांक ret;

	ret = iwl_mvm_send_cmd_pdu(mvm, ADD_STA, CMD_ASYNC,
				   iwl_mvm_add_sta_cmd_size(mvm), &cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send ADD_STA command (%d)\n", ret);
पूर्ण

व्योम iwl_mvm_sta_modअगरy_disable_tx_ap(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_sta *sta,
				      bool disable)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);

	spin_lock_bh(&mvm_sta->lock);

	अगर (mvm_sta->disable_tx == disable) अणु
		spin_unlock_bh(&mvm_sta->lock);
		वापस;
	पूर्ण

	mvm_sta->disable_tx = disable;

	/* Tell mac80211 to start/stop queuing tx क्रम this station */
	ieee80211_sta_block_awake(mvm->hw, sta, disable);

	iwl_mvm_sta_modअगरy_disable_tx(mvm, mvm_sta, disable);

	spin_unlock_bh(&mvm_sta->lock);
पूर्ण

अटल व्योम iwl_mvm_पूर्णांक_sta_modअगरy_disable_tx(काष्ठा iwl_mvm *mvm,
					      काष्ठा iwl_mvm_vअगर *mvmvअगर,
					      काष्ठा iwl_mvm_पूर्णांक_sta *sta,
					      bool disable)
अणु
	u32 id = FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color);
	काष्ठा iwl_mvm_add_sta_cmd cmd = अणु
		.add_modअगरy = STA_MODE_MODIFY,
		.sta_id = sta->sta_id,
		.station_flags = disable ? cpu_to_le32(STA_FLG_DISABLE_TX) : 0,
		.station_flags_msk = cpu_to_le32(STA_FLG_DISABLE_TX),
		.mac_id_n_color = cpu_to_le32(id),
	पूर्ण;
	पूर्णांक ret;

	ret = iwl_mvm_send_cmd_pdu(mvm, ADD_STA, CMD_ASYNC,
				   iwl_mvm_add_sta_cmd_size(mvm), &cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send ADD_STA command (%d)\n", ret);
पूर्ण

व्योम iwl_mvm_modअगरy_all_sta_disable_tx(काष्ठा iwl_mvm *mvm,
				       काष्ठा iwl_mvm_vअगर *mvmvअगर,
				       bool disable)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvm_sta;
	पूर्णांक i;

	rcu_पढ़ो_lock();

	/* Block/unblock all the stations of the given mvmvअगर */
	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) अणु
		sta = rcu_dereference(mvm->fw_id_to_mac_id[i]);
		अगर (IS_ERR_OR_शून्य(sta))
			जारी;

		mvm_sta = iwl_mvm_sta_from_mac80211(sta);
		अगर (mvm_sta->mac_id_n_color !=
		    FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color))
			जारी;

		iwl_mvm_sta_modअगरy_disable_tx_ap(mvm, sta, disable);
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (!fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_STA_TYPE))
		वापस;

	/* Need to block/unblock also multicast station */
	अगर (mvmvअगर->mcast_sta.sta_id != IWL_MVM_INVALID_STA)
		iwl_mvm_पूर्णांक_sta_modअगरy_disable_tx(mvm, mvmvअगर,
						  &mvmvअगर->mcast_sta, disable);

	/*
	 * Only unblock the broadcast station (FW blocks it क्रम immediate
	 * quiet, not the driver)
	 */
	अगर (!disable && mvmvअगर->bcast_sta.sta_id != IWL_MVM_INVALID_STA)
		iwl_mvm_पूर्णांक_sta_modअगरy_disable_tx(mvm, mvmvअगर,
						  &mvmvअगर->bcast_sta, disable);
पूर्ण

व्योम iwl_mvm_csa_client_असलent(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_sta *mvmsta;

	rcu_पढ़ो_lock();

	mvmsta = iwl_mvm_sta_from_staid_rcu(mvm, mvmvअगर->ap_sta_id);

	अगर (!WARN_ON(!mvmsta))
		iwl_mvm_sta_modअगरy_disable_tx(mvm, mvmsta, true);

	rcu_पढ़ो_unlock();
पूर्ण

u16 iwl_mvm_tid_queued(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_tid_data *tid_data)
अणु
	u16 sn = IEEE80211_SEQ_TO_SN(tid_data->seq_number);

	/*
	 * In 22000 HW, the next_reclaimed index is only 8 bit, so we'll need
	 * to align the wrap around of ssn so we compare relevant values.
	 */
	अगर (mvm->trans->trans_cfg->gen2)
		sn &= 0xff;

	वापस ieee80211_sn_sub(sn, tid_data->next_reclaimed);
पूर्ण

पूर्णांक iwl_mvm_add_pasn_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा iwl_mvm_पूर्णांक_sta *sta, u8 *addr, u32 cipher,
			 u8 *key, u32 key_len)
अणु
	पूर्णांक ret;
	u16 queue;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा ieee80211_key_conf *keyconf;

	ret = iwl_mvm_allocate_पूर्णांक_sta(mvm, sta, 0,
				       NL80211_IFTYPE_UNSPECIFIED,
				       IWL_STA_LINK);
	अगर (ret)
		वापस ret;

	ret = iwl_mvm_add_पूर्णांक_sta_with_queue(mvm, mvmvअगर->id, mvmvअगर->color,
					     addr, sta, &queue,
					     IWL_MVM_TX_FIFO_BE);
	अगर (ret)
		जाओ out;

	keyconf = kzalloc(माप(*keyconf) + key_len, GFP_KERNEL);
	अगर (!keyconf) अणु
		ret = -ENOBUFS;
		जाओ out;
	पूर्ण

	keyconf->cipher = cipher;
	स_नकल(keyconf->key, key, key_len);
	keyconf->keylen = key_len;

	ret = iwl_mvm_send_sta_key(mvm, sta->sta_id, keyconf, false,
				   0, शून्य, 0, 0, true);
	kमुक्त(keyconf);
	वापस 0;
out:
	iwl_mvm_dealloc_पूर्णांक_sta(mvm, sta);
	वापस ret;
पूर्ण
