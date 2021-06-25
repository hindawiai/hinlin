<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>
#समावेश <net/mac80211.h>
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"
#समावेश "fw-api.h"
#समावेश "mvm.h"
#समावेश "time-event.h"

स्थिर u8 iwl_mvm_ac_to_tx_fअगरo[] = अणु
	IWL_MVM_TX_FIFO_VO,
	IWL_MVM_TX_FIFO_VI,
	IWL_MVM_TX_FIFO_BE,
	IWL_MVM_TX_FIFO_BK,
पूर्ण;

स्थिर u8 iwl_mvm_ac_to_gen2_tx_fअगरo[] = अणु
	IWL_GEN2_EDCA_TX_FIFO_VO,
	IWL_GEN2_EDCA_TX_FIFO_VI,
	IWL_GEN2_EDCA_TX_FIFO_BE,
	IWL_GEN2_EDCA_TX_FIFO_BK,
	IWL_GEN2_TRIG_TX_FIFO_VO,
	IWL_GEN2_TRIG_TX_FIFO_VI,
	IWL_GEN2_TRIG_TX_FIFO_BE,
	IWL_GEN2_TRIG_TX_FIFO_BK,
पूर्ण;

काष्ठा iwl_mvm_mac_अगरace_iterator_data अणु
	काष्ठा iwl_mvm *mvm;
	काष्ठा ieee80211_vअगर *vअगर;
	अचिन्हित दीर्घ available_mac_ids[BITS_TO_LONGS(NUM_MAC_INDEX_DRIVER)];
	अचिन्हित दीर्घ available_tsf_ids[BITS_TO_LONGS(NUM_TSF_IDS)];
	क्रमागत iwl_tsf_id preferred_tsf;
	bool found_vअगर;
पूर्ण;

अटल व्योम iwl_mvm_mac_tsf_id_iter(व्योम *_data, u8 *mac,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_mac_अगरace_iterator_data *data = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	u16 min_bi;

	/* Skip the पूर्णांकerface क्रम which we are trying to assign a tsf_id  */
	अगर (vअगर == data->vअगर)
		वापस;

	/*
	 * The TSF is a hardware/firmware resource, there are 4 and
	 * the driver should assign and मुक्त them as needed. However,
	 * there are हालs where 2 MACs should share the same TSF ID
	 * क्रम the purpose of घड़ी sync, an optimization to aव्योम
	 * घड़ी drअगरt causing overlapping TBTTs/DTIMs क्रम a GO and
	 * client in the प्रणाली.
	 *
	 * The firmware will decide according to the MAC type which
	 * will be the leader and follower. Clients that need to sync
	 * with a remote station will be the leader, and an AP or GO
	 * will be the follower.
	 *
	 * Depending on the new पूर्णांकerface type it can be following
	 * or become the leader of an existing पूर्णांकerface.
	 */
	चयन (data->vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		/*
		 * The new पूर्णांकerface is a client, so अगर the one we're iterating
		 * is an AP, and the beacon पूर्णांकerval of the AP is a multiple or
		 * भागisor of the beacon पूर्णांकerval of the client, the same TSF
		 * should be used to aव्योम drअगरt between the new client and
		 * existing AP. The existing AP will get drअगरt updates from the
		 * new client context in this हाल.
		 */
		अगर (vअगर->type != NL80211_IFTYPE_AP ||
		    data->preferred_tsf != NUM_TSF_IDS ||
		    !test_bit(mvmvअगर->tsf_id, data->available_tsf_ids))
			अवरोध;

		min_bi = min(data->vअगर->bss_conf.beacon_पूर्णांक,
			     vअगर->bss_conf.beacon_पूर्णांक);

		अगर (!min_bi)
			अवरोध;

		अगर ((data->vअगर->bss_conf.beacon_पूर्णांक -
		     vअगर->bss_conf.beacon_पूर्णांक) % min_bi == 0) अणु
			data->preferred_tsf = mvmvअगर->tsf_id;
			वापस;
		पूर्ण
		अवरोध;

	हाल NL80211_IFTYPE_AP:
		/*
		 * The new पूर्णांकerface is AP/GO, so अगर its beacon पूर्णांकerval is a
		 * multiple or a भागisor of the beacon पूर्णांकerval of an existing
		 * पूर्णांकerface, it should get drअगरt updates from an existing
		 * client or use the same TSF as an existing GO. There's no
		 * drअगरt between TSFs पूर्णांकernally but अगर they used dअगरferent
		 * TSFs then a new client MAC could update one of them and
		 * cause drअगरt that way.
		 */
		अगर ((vअगर->type != NL80211_IFTYPE_AP &&
		     vअगर->type != NL80211_IFTYPE_STATION) ||
		    data->preferred_tsf != NUM_TSF_IDS ||
		    !test_bit(mvmvअगर->tsf_id, data->available_tsf_ids))
			अवरोध;

		min_bi = min(data->vअगर->bss_conf.beacon_पूर्णांक,
			     vअगर->bss_conf.beacon_पूर्णांक);

		अगर (!min_bi)
			अवरोध;

		अगर ((data->vअगर->bss_conf.beacon_पूर्णांक -
		     vअगर->bss_conf.beacon_पूर्णांक) % min_bi == 0) अणु
			data->preferred_tsf = mvmvअगर->tsf_id;
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		/*
		 * For all other पूर्णांकerface types there's no need to
		 * take drअगरt पूर्णांकo account. Either they're exclusive
		 * like IBSS and monitor, or we करोn't care much about
		 * their TSF (like P2P Device), but we won't be able
		 * to share the TSF resource.
		 */
		अवरोध;
	पूर्ण

	/*
	 * Unless we निकासed above, we can't share the TSF resource
	 * that the भव पूर्णांकerface we're iterating over is using
	 * with the new one, so clear the available bit and अगर this
	 * was the preferred one, reset that as well.
	 */
	__clear_bit(mvmvअगर->tsf_id, data->available_tsf_ids);

	अगर (data->preferred_tsf == mvmvअगर->tsf_id)
		data->preferred_tsf = NUM_TSF_IDS;
पूर्ण

अटल व्योम iwl_mvm_mac_अगरace_iterator(व्योम *_data, u8 *mac,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_mac_अगरace_iterator_data *data = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	/* Iterator may alपढ़ोy find the पूर्णांकerface being added -- skip it */
	अगर (vअगर == data->vअगर) अणु
		data->found_vअगर = true;
		वापस;
	पूर्ण

	/* Mark MAC IDs as used by clearing the available bit, and
	 * (below) mark TSFs as used अगर their existing use is not
	 * compatible with the new पूर्णांकerface type.
	 * No locking or atomic bit operations are needed since the
	 * data is on the stack of the caller function.
	 */
	__clear_bit(mvmvअगर->id, data->available_mac_ids);

	/* find a suitable tsf_id */
	iwl_mvm_mac_tsf_id_iter(_data, mac, vअगर);
पूर्ण

व्योम iwl_mvm_mac_ctxt_recalc_tsf_id(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_mac_अगरace_iterator_data data = अणु
		.mvm = mvm,
		.vअगर = vअगर,
		.available_tsf_ids = अणु (1 << NUM_TSF_IDS) - 1 पूर्ण,
		/* no preference yet */
		.preferred_tsf = NUM_TSF_IDS,
	पूर्ण;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		iwl_mvm_mac_tsf_id_iter, &data);

	अगर (data.preferred_tsf != NUM_TSF_IDS)
		mvmvअगर->tsf_id = data.preferred_tsf;
	अन्यथा अगर (!test_bit(mvmvअगर->tsf_id, data.available_tsf_ids))
		mvmvअगर->tsf_id = find_first_bit(data.available_tsf_ids,
						NUM_TSF_IDS);
पूर्ण

पूर्णांक iwl_mvm_mac_ctxt_init(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_mac_अगरace_iterator_data data = अणु
		.mvm = mvm,
		.vअगर = vअगर,
		.available_mac_ids = अणु (1 << NUM_MAC_INDEX_DRIVER) - 1 पूर्ण,
		.available_tsf_ids = अणु (1 << NUM_TSF_IDS) - 1 पूर्ण,
		/* no preference yet */
		.preferred_tsf = NUM_TSF_IDS,
		.found_vअगर = false,
	पूर्ण;
	पूर्णांक ret, i;

	lockdep_निश्चित_held(&mvm->mutex);

	/*
	 * Allocate a MAC ID and a TSF क्रम this MAC, aदीर्घ with the queues
	 * and other resources.
	 */

	/*
	 * Beक्रमe the iterator, we start with all MAC IDs and TSFs available.
	 *
	 * During iteration, all MAC IDs are cleared that are in use by other
	 * भव पूर्णांकerfaces, and all TSF IDs are cleared that can't be used
	 * by this new भव पूर्णांकerface because they're used by an पूर्णांकerface
	 * that can't share it with the new one.
	 * At the same समय, we check अगर there's a preferred TSF in the हाल
	 * that we should share it with another पूर्णांकerface.
	 */

	/* Currently, MAC ID 0 should be used only क्रम the managed/IBSS vअगर */
	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (!vअगर->p2p)
			अवरोध;
		fallthrough;
	शेष:
		__clear_bit(0, data.available_mac_ids);
	पूर्ण

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		iwl_mvm_mac_अगरace_iterator, &data);

	/*
	 * In the हाल we're getting here during resume, it's similar to
	 * firmware restart, and with RESUME_ALL the iterator will find
	 * the vअगर being added alपढ़ोy.
	 * We करोn't want to reassign any IDs in either हाल since करोing
	 * so would probably assign dअगरferent IDs (as पूर्णांकerfaces aren't
	 * necessarily added in the same order), but the old IDs were
	 * preserved anyway, so skip ID assignment क्रम both resume and
	 * recovery.
	 */
	अगर (data.found_vअगर)
		वापस 0;

	/* Thereक्रमe, in recovery, we can't get here */
	अगर (WARN_ON_ONCE(test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)))
		वापस -EBUSY;

	mvmvअगर->id = find_first_bit(data.available_mac_ids,
				    NUM_MAC_INDEX_DRIVER);
	अगर (mvmvअगर->id == NUM_MAC_INDEX_DRIVER) अणु
		IWL_ERR(mvm, "Failed to init MAC context - no free ID!\n");
		ret = -EIO;
		जाओ निकास_fail;
	पूर्ण

	अगर (data.preferred_tsf != NUM_TSF_IDS)
		mvmvअगर->tsf_id = data.preferred_tsf;
	अन्यथा
		mvmvअगर->tsf_id = find_first_bit(data.available_tsf_ids,
						NUM_TSF_IDS);
	अगर (mvmvअगर->tsf_id == NUM_TSF_IDS) अणु
		IWL_ERR(mvm, "Failed to init MAC context - no free TSF!\n");
		ret = -EIO;
		जाओ निकास_fail;
	पूर्ण

	mvmvअगर->color = 0;

	INIT_LIST_HEAD(&mvmvअगर->समय_event_data.list);
	mvmvअगर->समय_event_data.id = TE_MAX;

	/* No need to allocate data queues to P2P Device MAC and न_अंक.*/
	अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE)
		वापस 0;

	/* Allocate the CAB queue क्रम softAP and GO पूर्णांकerfaces */
	अगर (vअगर->type == NL80211_IFTYPE_AP ||
	    vअगर->type == NL80211_IFTYPE_ADHOC) अणु
		/*
		 * For TVQM this will be overwritten later with the FW asचिन्हित
		 * queue value (when queue is enabled).
		 */
		mvmvअगर->cab_queue = IWL_MVM_DQA_GCAST_QUEUE;
	पूर्ण

	mvmvअगर->bcast_sta.sta_id = IWL_MVM_INVALID_STA;
	mvmvअगर->mcast_sta.sta_id = IWL_MVM_INVALID_STA;
	mvmvअगर->ap_sta_id = IWL_MVM_INVALID_STA;

	क्रम (i = 0; i < NUM_IWL_MVM_SMPS_REQ; i++)
		mvmvअगर->smps_requests[i] = IEEE80211_SMPS_AUTOMATIC;

	वापस 0;

निकास_fail:
	स_रखो(mvmvअगर, 0, माप(काष्ठा iwl_mvm_vअगर));
	वापस ret;
पूर्ण

अटल व्योम iwl_mvm_ack_rates(काष्ठा iwl_mvm *mvm,
			      काष्ठा ieee80211_vअगर *vअगर,
			      क्रमागत nl80211_band band,
			      u8 *cck_rates, u8 *ofdm_rates)
अणु
	काष्ठा ieee80211_supported_band *sband;
	अचिन्हित दीर्घ basic = vअगर->bss_conf.basic_rates;
	पूर्णांक lowest_present_ofdm = 100;
	पूर्णांक lowest_present_cck = 100;
	u8 cck = 0;
	u8 ofdm = 0;
	पूर्णांक i;

	sband = mvm->hw->wiphy->bands[band];

	क्रम_each_set_bit(i, &basic, BITS_PER_LONG) अणु
		पूर्णांक hw = sband->bitrates[i].hw_value;
		अगर (hw >= IWL_FIRST_OFDM_RATE) अणु
			ofdm |= BIT(hw - IWL_FIRST_OFDM_RATE);
			अगर (lowest_present_ofdm > hw)
				lowest_present_ofdm = hw;
		पूर्ण अन्यथा अणु
			BUILD_BUG_ON(IWL_FIRST_CCK_RATE != 0);

			cck |= BIT(hw);
			अगर (lowest_present_cck > hw)
				lowest_present_cck = hw;
		पूर्ण
	पूर्ण

	/*
	 * Now we've got the basic rates as biपंचांगaps in the ofdm and cck
	 * variables. This isn't sufficient though, as there might not
	 * be all the right rates in the biपंचांगap. E.g. अगर the only basic
	 * rates are 5.5 Mbps and 11 Mbps, we still need to add 1 Mbps
	 * and 6 Mbps because the 802.11-2007 standard says in 9.6:
	 *
	 *    [...] a STA responding to a received frame shall transmit
	 *    its Control Response frame [...] at the highest rate in the
	 *    BSSBasicRateSet parameter that is less than or equal to the
	 *    rate of the immediately previous frame in the frame exchange
	 *    sequence ([...]) and that is of the same modulation class
	 *    ([...]) as the received frame. If no rate contained in the
	 *    BSSBasicRateSet parameter meets these conditions, then the
	 *    control frame sent in response to a received frame shall be
	 *    transmitted at the highest mandatory rate of the PHY that is
	 *    less than or equal to the rate of the received frame, and
	 *    that is of the same modulation class as the received frame.
	 *
	 * As a consequence, we need to add all mandatory rates that are
	 * lower than all of the basic rates to these biपंचांगaps.
	 */

	अगर (IWL_RATE_24M_INDEX < lowest_present_ofdm)
		ofdm |= IWL_RATE_BIT_MSK(24) >> IWL_FIRST_OFDM_RATE;
	अगर (IWL_RATE_12M_INDEX < lowest_present_ofdm)
		ofdm |= IWL_RATE_BIT_MSK(12) >> IWL_FIRST_OFDM_RATE;
	/* 6M alपढ़ोy there or needed so always add */
	ofdm |= IWL_RATE_BIT_MSK(6) >> IWL_FIRST_OFDM_RATE;

	/*
	 * CCK is a bit more complex with DSSS vs. HR/DSSS vs. ERP.
	 * Note, however:
	 *  - अगर no CCK rates are basic, it must be ERP since there must
	 *    be some basic rates at all, so they're OFDM => ERP PHY
	 *    (or we're in 5 GHz, and the cck biपंचांगap will never be used)
	 *  - अगर 11M is a basic rate, it must be ERP as well, so add 5.5M
	 *  - अगर 5.5M is basic, 1M and 2M are mandatory
	 *  - अगर 2M is basic, 1M is mandatory
	 *  - अगर 1M is basic, that's the only valid ACK rate.
	 * As a consequence, it's not as complicated as it sounds, just add
	 * any lower rates to the ACK rate biपंचांगap.
	 */
	अगर (IWL_RATE_11M_INDEX < lowest_present_cck)
		cck |= IWL_RATE_BIT_MSK(11) >> IWL_FIRST_CCK_RATE;
	अगर (IWL_RATE_5M_INDEX < lowest_present_cck)
		cck |= IWL_RATE_BIT_MSK(5) >> IWL_FIRST_CCK_RATE;
	अगर (IWL_RATE_2M_INDEX < lowest_present_cck)
		cck |= IWL_RATE_BIT_MSK(2) >> IWL_FIRST_CCK_RATE;
	/* 1M alपढ़ोy there or needed so always add */
	cck |= IWL_RATE_BIT_MSK(1) >> IWL_FIRST_CCK_RATE;

	*cck_rates = cck;
	*ofdm_rates = ofdm;
पूर्ण

अटल व्योम iwl_mvm_mac_ctxt_set_ht_flags(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा iwl_mac_ctx_cmd *cmd)
अणु
	/* क्रम both sta and ap, ht_operation_mode hold the protection_mode */
	u8 protection_mode = vअगर->bss_conf.ht_operation_mode &
				 IEEE80211_HT_OP_MODE_PROTECTION;
	/* The fw करोes not distinguish between ht and fat */
	u32 ht_flag = MAC_PROT_FLG_HT_PROT | MAC_PROT_FLG_FAT_PROT;

	IWL_DEBUG_RATE(mvm, "protection mode set to %d\n", protection_mode);
	/*
	 * See section 9.23.3.1 of IEEE 80211-2012.
	 * Nongreenfield HT STAs Present is not supported.
	 */
	चयन (protection_mode) अणु
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONE:
		अवरोध;
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER:
	हाल IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
		cmd->protection_flags |= cpu_to_le32(ht_flag);
		अवरोध;
	हाल IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
		/* Protect when channel wider than 20MHz */
		अगर (vअगर->bss_conf.chandef.width > NL80211_CHAN_WIDTH_20)
			cmd->protection_flags |= cpu_to_le32(ht_flag);
		अवरोध;
	शेष:
		IWL_ERR(mvm, "Illegal protection mode %d\n",
			protection_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_mac_ctxt_cmd_common(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा iwl_mac_ctx_cmd *cmd,
					स्थिर u8 *bssid_override,
					u32 action)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा ieee80211_chanctx_conf *chanctx;
	bool ht_enabled = !!(vअगर->bss_conf.ht_operation_mode &
			     IEEE80211_HT_OP_MODE_PROTECTION);
	u8 cck_ack_rates, ofdm_ack_rates;
	स्थिर u8 *bssid = bssid_override ?: vअगर->bss_conf.bssid;
	पूर्णांक i;

	cmd->id_and_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							    mvmvअगर->color));
	cmd->action = cpu_to_le32(action);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (vअगर->p2p)
			cmd->mac_type = cpu_to_le32(FW_MAC_TYPE_P2P_STA);
		अन्यथा
			cmd->mac_type = cpu_to_le32(FW_MAC_TYPE_BSS_STA);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		cmd->mac_type = cpu_to_le32(FW_MAC_TYPE_GO);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		cmd->mac_type = cpu_to_le32(FW_MAC_TYPE_LISTENER);
		अवरोध;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		cmd->mac_type = cpu_to_le32(FW_MAC_TYPE_P2P_DEVICE);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		cmd->mac_type = cpu_to_le32(FW_MAC_TYPE_IBSS);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	cmd->tsf_id = cpu_to_le32(mvmvअगर->tsf_id);

	स_नकल(cmd->node_addr, vअगर->addr, ETH_ALEN);

	अगर (bssid)
		स_नकल(cmd->bssid_addr, bssid, ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(cmd->bssid_addr);

	rcu_पढ़ो_lock();
	chanctx = rcu_dereference(vअगर->chanctx_conf);
	iwl_mvm_ack_rates(mvm, vअगर, chanctx ? chanctx->def.chan->band
					    : NL80211_BAND_2GHZ,
			  &cck_ack_rates, &ofdm_ack_rates);
	rcu_पढ़ो_unlock();

	cmd->cck_rates = cpu_to_le32((u32)cck_ack_rates);
	cmd->ofdm_rates = cpu_to_le32((u32)ofdm_ack_rates);

	cmd->cck_लघु_preamble =
		cpu_to_le32(vअगर->bss_conf.use_लघु_preamble ?
			    MAC_FLG_SHORT_PREAMBLE : 0);
	cmd->लघु_slot =
		cpu_to_le32(vअगर->bss_conf.use_लघु_slot ?
			    MAC_FLG_SHORT_SLOT : 0);

	cmd->filter_flags = 0;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		u8 txf = iwl_mvm_mac_ac_to_tx_fअगरo(mvm, i);
		u8 ucode_ac = iwl_mvm_mac80211_ac_to_ucode_ac(i);

		cmd->ac[ucode_ac].cw_min =
			cpu_to_le16(mvmvअगर->queue_params[i].cw_min);
		cmd->ac[ucode_ac].cw_max =
			cpu_to_le16(mvmvअगर->queue_params[i].cw_max);
		cmd->ac[ucode_ac].edca_txop =
			cpu_to_le16(mvmvअगर->queue_params[i].txop * 32);
		cmd->ac[ucode_ac].aअगरsn = mvmvअगर->queue_params[i].aअगरs;
		cmd->ac[ucode_ac].fअगरos_mask = BIT(txf);
	पूर्ण

	अगर (vअगर->bss_conf.qos)
		cmd->qos_flags |= cpu_to_le32(MAC_QOS_FLG_UPDATE_EDCA);

	अगर (vअगर->bss_conf.use_cts_prot)
		cmd->protection_flags |= cpu_to_le32(MAC_PROT_FLG_TGG_PROTECT);

	IWL_DEBUG_RATE(mvm, "use_cts_prot %d, ht_operation_mode %d\n",
		       vअगर->bss_conf.use_cts_prot,
		       vअगर->bss_conf.ht_operation_mode);
	अगर (vअगर->bss_conf.chandef.width != NL80211_CHAN_WIDTH_20_NOHT)
		cmd->qos_flags |= cpu_to_le32(MAC_QOS_FLG_TGN);
	अगर (ht_enabled)
		iwl_mvm_mac_ctxt_set_ht_flags(mvm, vअगर, cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_send_cmd(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_mac_ctx_cmd *cmd)
अणु
	पूर्णांक ret = iwl_mvm_send_cmd_pdu(mvm, MAC_CONTEXT_CMD, 0,
				       माप(*cmd), cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send MAC context (action:%d): %d\n",
			le32_to_cpu(cmd->action), ret);
	वापस ret;
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_cmd_sta(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर,
				    u32 action, bool क्रमce_assoc_off,
				    स्थिर u8 *bssid_override)
अणु
	काष्ठा iwl_mac_ctx_cmd cmd = अणुपूर्ण;
	काष्ठा iwl_mac_data_sta *ctxt_sta;

	WARN_ON(vअगर->type != NL80211_IFTYPE_STATION);

	/* Fill the common data क्रम all mac context types */
	iwl_mvm_mac_ctxt_cmd_common(mvm, vअगर, &cmd, bssid_override, action);

	अगर (vअगर->p2p) अणु
		काष्ठा ieee80211_p2p_noa_attr *noa =
			&vअगर->bss_conf.p2p_noa_attr;

		cmd.p2p_sta.ctwin = cpu_to_le32(noa->oppps_ctwinकरोw &
					IEEE80211_P2P_OPPPS_CTWINDOW_MASK);
		ctxt_sta = &cmd.p2p_sta.sta;
	पूर्ण अन्यथा अणु
		ctxt_sta = &cmd.sta;
	पूर्ण

	/* We need the dtim_period to set the MAC as associated */
	अगर (vअगर->bss_conf.assoc && vअगर->bss_conf.dtim_period &&
	    !क्रमce_assoc_off) अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
		u8 ap_sta_id = mvmvअगर->ap_sta_id;
		u32 dtim_offs;

		/*
		 * The DTIM count counts करोwn, so when it is N that means N
		 * more beacon पूर्णांकervals happen until the DTIM TBTT. Thereक्रमe
		 * add this to the current समय. If that ends up being in the
		 * future, the firmware will handle it.
		 *
		 * Also note that the प्रणाली_बारtamp (which we get here as
		 * "sync_device_ts") and TSF बारtamp aren't at exactly the
		 * same offset in the frame -- the TSF is at the first symbol
		 * of the TSF, the प्रणाली बारtamp is at संकेत acquisition
		 * समय. This means there's an offset between them of at most
		 * a few hundred microseconds (24 * 8 bits + PLCP समय gives
		 * 384us in the दीर्घest हाल), this is currently not relevant
		 * as the firmware wakes up around 2ms beक्रमe the TBTT.
		 */
		dtim_offs = vअगर->bss_conf.sync_dtim_count *
				vअगर->bss_conf.beacon_पूर्णांक;
		/* convert TU to usecs */
		dtim_offs *= 1024;

		ctxt_sta->dtim_tsf =
			cpu_to_le64(vअगर->bss_conf.sync_tsf + dtim_offs);
		ctxt_sta->dtim_समय =
			cpu_to_le32(vअगर->bss_conf.sync_device_ts + dtim_offs);
		ctxt_sta->assoc_beacon_arrive_समय =
			cpu_to_le32(vअगर->bss_conf.sync_device_ts);

		IWL_DEBUG_INFO(mvm, "DTIM TBTT is 0x%llx/0x%x, offset %d\n",
			       le64_to_cpu(ctxt_sta->dtim_tsf),
			       le32_to_cpu(ctxt_sta->dtim_समय),
			       dtim_offs);

		ctxt_sta->is_assoc = cpu_to_le32(1);

		/*
		 * allow multicast data frames only as दीर्घ as the station is
		 * authorized, i.e., GTK keys are alपढ़ोy installed (अगर needed)
		 */
		अगर (ap_sta_id < mvm->fw->ucode_capa.num_stations) अणु
			काष्ठा ieee80211_sta *sta;

			rcu_पढ़ो_lock();

			sta = rcu_dereference(mvm->fw_id_to_mac_id[ap_sta_id]);
			अगर (!IS_ERR_OR_शून्य(sta)) अणु
				काष्ठा iwl_mvm_sta *mvmsta =
					iwl_mvm_sta_from_mac80211(sta);

				अगर (mvmsta->sta_state ==
				    IEEE80211_STA_AUTHORIZED)
					cmd.filter_flags |=
						cpu_to_le32(MAC_FILTER_ACCEPT_GRP);
			पूर्ण

			rcu_पढ़ो_unlock();
		पूर्ण
	पूर्ण अन्यथा अणु
		ctxt_sta->is_assoc = cpu_to_le32(0);

		/* Allow beacons to pass through as दीर्घ as we are not
		 * associated, or we करो not have dtim period inक्रमmation.
		 */
		cmd.filter_flags |= cpu_to_le32(MAC_FILTER_IN_BEACON);
	पूर्ण

	ctxt_sta->bi = cpu_to_le32(vअगर->bss_conf.beacon_पूर्णांक);
	ctxt_sta->dtim_पूर्णांकerval = cpu_to_le32(vअगर->bss_conf.beacon_पूर्णांक *
					      vअगर->bss_conf.dtim_period);

	ctxt_sta->listen_पूर्णांकerval = cpu_to_le32(mvm->hw->conf.listen_पूर्णांकerval);
	ctxt_sta->assoc_id = cpu_to_le32(vअगर->bss_conf.aid);

	अगर (vअगर->probe_req_reg && vअगर->bss_conf.assoc && vअगर->p2p)
		cmd.filter_flags |= cpu_to_le32(MAC_FILTER_IN_PROBE_REQUEST);

	अगर (vअगर->bss_conf.he_support && !iwlwअगरi_mod_params.disable_11ax) अणु
		cmd.filter_flags |= cpu_to_le32(MAC_FILTER_IN_11AX);
		अगर (vअगर->bss_conf.twt_requester && IWL_MVM_USE_TWT) अणु
			ctxt_sta->data_policy |= cpu_to_le32(TWT_SUPPORTED);
			अगर (vअगर->bss_conf.twt_रक्षित)
				ctxt_sta->data_policy |=
					cpu_to_le32(PROTECTED_TWT_SUPPORTED);
		पूर्ण
	पूर्ण


	वापस iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_cmd_listener(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर,
					 u32 action)
अणु
	काष्ठा iwl_mac_ctx_cmd cmd = अणुपूर्ण;
	u32 tfd_queue_msk = BIT(mvm->snअगर_queue);
	पूर्णांक ret;

	WARN_ON(vअगर->type != NL80211_IFTYPE_MONITOR);

	iwl_mvm_mac_ctxt_cmd_common(mvm, vअगर, &cmd, शून्य, action);

	cmd.filter_flags = cpu_to_le32(MAC_FILTER_IN_PROMISC |
				       MAC_FILTER_IN_CONTROL_AND_MGMT |
				       MAC_FILTER_IN_BEACON |
				       MAC_FILTER_IN_PROBE_REQUEST |
				       MAC_FILTER_IN_CRC32 |
				       MAC_FILTER_ACCEPT_GRP);
	ieee80211_hw_set(mvm->hw, RX_INCLUDES_FCS);

	/* Allocate snअगरfer station */
	ret = iwl_mvm_allocate_पूर्णांक_sta(mvm, &mvm->snअगर_sta, tfd_queue_msk,
				       vअगर->type, IWL_STA_GENERAL_PURPOSE);
	अगर (ret)
		वापस ret;

	वापस iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_cmd_ibss(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_vअगर *vअगर,
				     u32 action)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mac_ctx_cmd cmd = अणुपूर्ण;

	WARN_ON(vअगर->type != NL80211_IFTYPE_ADHOC);

	iwl_mvm_mac_ctxt_cmd_common(mvm, vअगर, &cmd, शून्य, action);

	cmd.filter_flags = cpu_to_le32(MAC_FILTER_IN_BEACON |
				       MAC_FILTER_IN_PROBE_REQUEST |
				       MAC_FILTER_ACCEPT_GRP);

	/* cmd.ibss.beacon_समय/cmd.ibss.beacon_tsf are curently ignored */
	cmd.ibss.bi = cpu_to_le32(vअगर->bss_conf.beacon_पूर्णांक);

	/* TODO: Assumes that the beacon id == mac context id */
	cmd.ibss.beacon_ढाँचा = cpu_to_le32(mvmvअगर->id);

	वापस iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
पूर्ण

काष्ठा iwl_mvm_go_iterator_data अणु
	bool go_active;
पूर्ण;

अटल व्योम iwl_mvm_go_iterator(व्योम *_data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_go_iterator_data *data = _data;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (vअगर->type == NL80211_IFTYPE_AP && vअगर->p2p &&
	    mvmvअगर->ap_ibss_active)
		data->go_active = true;
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_cmd_p2p_device(काष्ठा iwl_mvm *mvm,
					   काष्ठा ieee80211_vअगर *vअगर,
					   u32 action)
अणु
	काष्ठा iwl_mac_ctx_cmd cmd = अणुपूर्ण;
	काष्ठा iwl_mvm_go_iterator_data data = अणुपूर्ण;

	WARN_ON(vअगर->type != NL80211_IFTYPE_P2P_DEVICE);

	iwl_mvm_mac_ctxt_cmd_common(mvm, vअगर, &cmd, शून्य, action);

	/* Override the filter flags to accept only probe requests */
	cmd.filter_flags = cpu_to_le32(MAC_FILTER_IN_PROBE_REQUEST);

	/*
	 * This flag should be set to true when the P2P Device is
	 * discoverable and there is at least another active P2P GO. Settings
	 * this flag will allow the P2P Device to be discoverable on other
	 * channels in addition to its listen channel.
	 * Note that this flag should not be set in other हालs as it खोलोs the
	 * Rx filters on all MAC and increases the number of पूर्णांकerrupts.
	 */
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		iwl_mvm_go_iterator, &data);

	cmd.p2p_dev.is_disc_extended = cpu_to_le32(data.go_active ? 1 : 0);
	वापस iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
पूर्ण

व्योम iwl_mvm_mac_ctxt_set_tim(काष्ठा iwl_mvm *mvm,
			      __le32 *tim_index, __le32 *tim_size,
			      u8 *beacon, u32 frame_size)
अणु
	u32 tim_idx;
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)beacon;

	/* The index is relative to frame start but we start looking at the
	 * variable-length part of the beacon. */
	tim_idx = mgmt->u.beacon.variable - beacon;

	/* Parse variable-length elements of beacon to find WLAN_EID_TIM */
	जबतक ((tim_idx < (frame_size - 2)) &&
			(beacon[tim_idx] != WLAN_EID_TIM))
		tim_idx += beacon[tim_idx+1] + 2;

	/* If TIM field was found, set variables */
	अगर ((tim_idx < (frame_size - 1)) && (beacon[tim_idx] == WLAN_EID_TIM)) अणु
		*tim_index = cpu_to_le32(tim_idx);
		*tim_size = cpu_to_le32((u32)beacon[tim_idx + 1]);
	पूर्ण अन्यथा अणु
		IWL_WARN(mvm, "Unable to find TIM Element in beacon\n");
	पूर्ण
पूर्ण

अटल u32 iwl_mvm_find_ie_offset(u8 *beacon, u8 eid, u32 frame_size)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)beacon;
	स्थिर u8 *ie;

	अगर (WARN_ON_ONCE(frame_size <= (mgmt->u.beacon.variable - beacon)))
		वापस 0;

	frame_size -= mgmt->u.beacon.variable - beacon;

	ie = cfg80211_find_ie(eid, mgmt->u.beacon.variable, frame_size);
	अगर (!ie)
		वापस 0;

	वापस ie - beacon;
पूर्ण

u8 iwl_mvm_mac_ctxt_get_lowest_rate(काष्ठा ieee80211_tx_info *info,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	u8 rate;
	अगर (info->band == NL80211_BAND_2GHZ && !vअगर->p2p)
		rate = IWL_FIRST_CCK_RATE;
	अन्यथा
		rate = IWL_FIRST_OFDM_RATE;

	वापस rate;
पूर्ण

अटल व्योम iwl_mvm_mac_ctxt_set_tx(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा sk_buff *beacon,
				    काष्ठा iwl_tx_cmd *tx)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा ieee80211_tx_info *info;
	u8 rate;
	u32 tx_flags;

	info = IEEE80211_SKB_CB(beacon);

	/* Set up TX command fields */
	tx->len = cpu_to_le16((u16)beacon->len);
	tx->sta_id = mvmvअगर->bcast_sta.sta_id;
	tx->lअगरe_समय = cpu_to_le32(TX_CMD_LIFE_TIME_INFINITE);
	tx_flags = TX_CMD_FLG_SEQ_CTL | TX_CMD_FLG_TSF;
	tx_flags |=
		iwl_mvm_bt_coex_tx_prio(mvm, (व्योम *)beacon->data, info, 0) <<
						TX_CMD_FLG_BT_PRIO_POS;
	tx->tx_flags = cpu_to_le32(tx_flags);

	अगर (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_BEACON_ANT_SELECTION))
		iwl_mvm_toggle_tx_ant(mvm, &mvm->mgmt_last_antenna_idx);

	tx->rate_n_flags =
		cpu_to_le32(BIT(mvm->mgmt_last_antenna_idx) <<
			    RATE_MCS_ANT_POS);

	rate = iwl_mvm_mac_ctxt_get_lowest_rate(info, vअगर);

	tx->rate_n_flags |= cpu_to_le32(iwl_mvm_mac80211_idx_to_hwrate(rate));
	अगर (rate == IWL_FIRST_CCK_RATE)
		tx->rate_n_flags |= cpu_to_le32(RATE_MCS_CCK_MSK);

पूर्ण

पूर्णांक iwl_mvm_mac_ctxt_send_beacon_cmd(काष्ठा iwl_mvm *mvm,
				     काष्ठा sk_buff *beacon,
				     व्योम *data, पूर्णांक len)
अणु
	काष्ठा iwl_host_cmd cmd = अणु
		.id = BEACON_TEMPLATE_CMD,
		.flags = CMD_ASYNC,
	पूर्ण;

	cmd.len[0] = len;
	cmd.data[0] = data;
	cmd.dataflags[0] = 0;
	cmd.len[1] = beacon->len;
	cmd.data[1] = beacon->data;
	cmd.dataflags[1] = IWL_HCMD_DFL_DUP;

	वापस iwl_mvm_send_cmd(mvm, &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_send_beacon_v6(काष्ठा iwl_mvm *mvm,
					   काष्ठा ieee80211_vअगर *vअगर,
					   काष्ठा sk_buff *beacon)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mac_beacon_cmd_v6 beacon_cmd = अणुपूर्ण;

	iwl_mvm_mac_ctxt_set_tx(mvm, vअगर, beacon, &beacon_cmd.tx);

	beacon_cmd.ढाँचा_id = cpu_to_le32((u32)mvmvअगर->id);

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		iwl_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
					 &beacon_cmd.tim_size,
					 beacon->data, beacon->len);

	वापस iwl_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
						माप(beacon_cmd));
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_send_beacon_v7(काष्ठा iwl_mvm *mvm,
					   काष्ठा ieee80211_vअगर *vअगर,
					   काष्ठा sk_buff *beacon)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mac_beacon_cmd_v7 beacon_cmd = अणुपूर्ण;

	iwl_mvm_mac_ctxt_set_tx(mvm, vअगर, beacon, &beacon_cmd.tx);

	beacon_cmd.ढाँचा_id = cpu_to_le32((u32)mvmvअगर->id);

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		iwl_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
					 &beacon_cmd.tim_size,
					 beacon->data, beacon->len);

	beacon_cmd.csa_offset =
		cpu_to_le32(iwl_mvm_find_ie_offset(beacon->data,
						   WLAN_EID_CHANNEL_SWITCH,
						   beacon->len));
	beacon_cmd.ecsa_offset =
		cpu_to_le32(iwl_mvm_find_ie_offset(beacon->data,
						   WLAN_EID_EXT_CHANSWITCH_ANN,
						   beacon->len));

	वापस iwl_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
						माप(beacon_cmd));
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_send_beacon_v9(काष्ठा iwl_mvm *mvm,
					   काष्ठा ieee80211_vअगर *vअगर,
					   काष्ठा sk_buff *beacon)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(beacon);
	काष्ठा iwl_mac_beacon_cmd beacon_cmd = अणुपूर्ण;
	u8 rate = iwl_mvm_mac_ctxt_get_lowest_rate(info, vअगर);
	u16 flags;
	काष्ठा ieee80211_chanctx_conf *ctx;
	पूर्णांक channel;

	flags = iwl_mvm_mac80211_idx_to_hwrate(rate);

	अगर (rate == IWL_FIRST_CCK_RATE)
		flags |= IWL_MAC_BEACON_CCK;

	/* Enable FILS on PSC channels only */
	rcu_पढ़ो_lock();
	ctx = rcu_dereference(vअगर->chanctx_conf);
	channel = ieee80211_frequency_to_channel(ctx->def.chan->center_freq);
	WARN_ON(channel == 0);
	अगर (cfg80211_channel_is_psc(ctx->def.chan) &&
	    !IWL_MVM_DISABLE_AP_FILS) अणु
		flags |= IWL_MAC_BEACON_FILS;
		beacon_cmd.लघु_ssid =
			cpu_to_le32(~crc32_le(~0, vअगर->bss_conf.ssid,
					      vअगर->bss_conf.ssid_len));
	पूर्ण
	rcu_पढ़ो_unlock();

	beacon_cmd.flags = cpu_to_le16(flags);
	beacon_cmd.byte_cnt = cpu_to_le16((u16)beacon->len);
	beacon_cmd.ढाँचा_id = cpu_to_le32((u32)mvmvअगर->id);

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		iwl_mvm_mac_ctxt_set_tim(mvm, &beacon_cmd.tim_idx,
					 &beacon_cmd.tim_size,
					 beacon->data, beacon->len);

	beacon_cmd.csa_offset =
		cpu_to_le32(iwl_mvm_find_ie_offset(beacon->data,
						   WLAN_EID_CHANNEL_SWITCH,
						   beacon->len));
	beacon_cmd.ecsa_offset =
		cpu_to_le32(iwl_mvm_find_ie_offset(beacon->data,
						   WLAN_EID_EXT_CHANSWITCH_ANN,
						   beacon->len));

	वापस iwl_mvm_mac_ctxt_send_beacon_cmd(mvm, beacon, &beacon_cmd,
						माप(beacon_cmd));
पूर्ण

पूर्णांक iwl_mvm_mac_ctxt_send_beacon(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा sk_buff *beacon)
अणु
	अगर (WARN_ON(!beacon))
		वापस -EINVAL;

	अगर (IWL_MVM_NON_TRANSMITTING_AP)
		वापस 0;

	अगर (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWL_UCODE_TLV_CAPA_CSA_AND_TBTT_OFFLOAD))
		वापस iwl_mvm_mac_ctxt_send_beacon_v6(mvm, vअगर, beacon);

	अगर (fw_has_api(&mvm->fw->ucode_capa,
		       IWL_UCODE_TLV_API_NEW_BEACON_TEMPLATE))
		वापस iwl_mvm_mac_ctxt_send_beacon_v9(mvm, vअगर, beacon);

	वापस iwl_mvm_mac_ctxt_send_beacon_v7(mvm, vअगर, beacon);
पूर्ण

/* The beacon ढाँचा क्रम the AP/GO/IBSS has changed and needs update */
पूर्णांक iwl_mvm_mac_ctxt_beacon_changed(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *beacon;
	पूर्णांक ret;

	WARN_ON(vअगर->type != NL80211_IFTYPE_AP &&
		vअगर->type != NL80211_IFTYPE_ADHOC);

	beacon = ieee80211_beacon_get_ढाँचा(mvm->hw, vअगर, शून्य);
	अगर (!beacon)
		वापस -ENOMEM;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (mvm->beacon_inject_active)
		वापस -EBUSY;
#पूर्ण_अगर

	ret = iwl_mvm_mac_ctxt_send_beacon(mvm, vअगर, beacon);
	dev_kमुक्त_skb(beacon);
	वापस ret;
पूर्ण

काष्ठा iwl_mvm_mac_ap_iterator_data अणु
	काष्ठा iwl_mvm *mvm;
	काष्ठा ieee80211_vअगर *vअगर;
	u32 beacon_device_ts;
	u16 beacon_पूर्णांक;
पूर्ण;

/* Find the beacon_device_ts and beacon_पूर्णांक क्रम a managed पूर्णांकerface */
अटल व्योम iwl_mvm_mac_ap_iterator(व्योम *_data, u8 *mac,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_mac_ap_iterator_data *data = _data;

	अगर (vअगर->type != NL80211_IFTYPE_STATION || !vअगर->bss_conf.assoc)
		वापस;

	/* Station client has higher priority over P2P client*/
	अगर (vअगर->p2p && data->beacon_device_ts)
		वापस;

	data->beacon_device_ts = vअगर->bss_conf.sync_device_ts;
	data->beacon_पूर्णांक = vअगर->bss_conf.beacon_पूर्णांक;
पूर्ण

/*
 * Fill the specअगरic data क्रम mac context of type AP of P2P GO
 */
अटल व्योम iwl_mvm_mac_ctxt_cmd_fill_ap(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा iwl_mac_ctx_cmd *cmd,
					 काष्ठा iwl_mac_data_ap *ctxt_ap,
					 bool add)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_mac_ap_iterator_data data = अणु
		.mvm = mvm,
		.vअगर = vअगर,
		.beacon_device_ts = 0
	पूर्ण;

	/* in AP mode, the MCAST FIFO takes the EDCA params from VO */
	cmd->ac[IWL_MVM_TX_FIFO_VO].fअगरos_mask |= BIT(IWL_MVM_TX_FIFO_MCAST);

	/*
	 * in AP mode, pass probe requests and beacons from other APs
	 * (needed क्रम ht protection); when there're no any associated
	 * station करोn't ask FW to pass beacons to prevent unnecessary
	 * wake-ups.
	 */
	cmd->filter_flags |= cpu_to_le32(MAC_FILTER_IN_PROBE_REQUEST);
	अगर (mvmvअगर->ap_assoc_sta_count || !mvm->drop_bcn_ap_mode) अणु
		cmd->filter_flags |= cpu_to_le32(MAC_FILTER_IN_BEACON);
		IWL_DEBUG_HC(mvm, "Asking FW to pass beacons\n");
	पूर्ण अन्यथा अणु
		IWL_DEBUG_HC(mvm, "No need to receive beacons\n");
	पूर्ण

	ctxt_ap->bi = cpu_to_le32(vअगर->bss_conf.beacon_पूर्णांक);
	ctxt_ap->dtim_पूर्णांकerval = cpu_to_le32(vअगर->bss_conf.beacon_पूर्णांक *
					     vअगर->bss_conf.dtim_period);

	अगर (!fw_has_api(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_API_STA_TYPE))
		ctxt_ap->mcast_qid = cpu_to_le32(mvmvअगर->cab_queue);

	/*
	 * Only set the beacon समय when the MAC is being added, when we
	 * just modअगरy the MAC then we should keep the समय -- the firmware
	 * can otherwise have a "jumping" TBTT.
	 */
	अगर (add) अणु
		/*
		 * If there is a station/P2P client पूर्णांकerface which is
		 * associated, set the AP's TBTT far enough from the station's
		 * TBTT. Otherwise, set it to the current प्रणाली समय
		 */
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
			iwl_mvm_mac_ap_iterator, &data);

		अगर (data.beacon_device_ts) अणु
			u32 अक्रम = (pअक्रमom_u32() % (64 - 36)) + 36;
			mvmvअगर->ap_beacon_समय = data.beacon_device_ts +
				ieee80211_tu_to_usec(data.beacon_पूर्णांक * अक्रम /
						     100);
		पूर्ण अन्यथा अणु
			mvmvअगर->ap_beacon_समय = iwl_mvm_get_sysसमय(mvm);
		पूर्ण
	पूर्ण

	ctxt_ap->beacon_समय = cpu_to_le32(mvmvअगर->ap_beacon_समय);
	ctxt_ap->beacon_tsf = 0; /* unused */

	/* TODO: Assume that the beacon id == mac context id */
	ctxt_ap->beacon_ढाँचा = cpu_to_le32(mvmvअगर->id);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_cmd_ap(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_vअगर *vअगर,
				   u32 action)
अणु
	काष्ठा iwl_mac_ctx_cmd cmd = अणुपूर्ण;

	WARN_ON(vअगर->type != NL80211_IFTYPE_AP || vअगर->p2p);

	/* Fill the common data क्रम all mac context types */
	iwl_mvm_mac_ctxt_cmd_common(mvm, vअगर, &cmd, शून्य, action);

	/* Fill the data specअगरic क्रम ap mode */
	iwl_mvm_mac_ctxt_cmd_fill_ap(mvm, vअगर, &cmd, &cmd.ap,
				     action == FW_CTXT_ACTION_ADD);

	वापस iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctxt_cmd_go(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_vअगर *vअगर,
				   u32 action)
अणु
	काष्ठा iwl_mac_ctx_cmd cmd = अणुपूर्ण;
	काष्ठा ieee80211_p2p_noa_attr *noa = &vअगर->bss_conf.p2p_noa_attr;

	WARN_ON(vअगर->type != NL80211_IFTYPE_AP || !vअगर->p2p);

	/* Fill the common data क्रम all mac context types */
	iwl_mvm_mac_ctxt_cmd_common(mvm, vअगर, &cmd, शून्य, action);

	/* Fill the data specअगरic क्रम GO mode */
	iwl_mvm_mac_ctxt_cmd_fill_ap(mvm, vअगर, &cmd, &cmd.go.ap,
				     action == FW_CTXT_ACTION_ADD);

	cmd.go.ctwin = cpu_to_le32(noa->oppps_ctwinकरोw &
					IEEE80211_P2P_OPPPS_CTWINDOW_MASK);
	cmd.go.opp_ps_enabled =
			cpu_to_le32(!!(noa->oppps_ctwinकरोw &
					IEEE80211_P2P_OPPPS_ENABLE_BIT));

	वापस iwl_mvm_mac_ctxt_send_cmd(mvm, &cmd);
पूर्ण

अटल पूर्णांक iwl_mvm_mac_ctx_send(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				u32 action, bool क्रमce_assoc_off,
				स्थिर u8 *bssid_override)
अणु
	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		वापस iwl_mvm_mac_ctxt_cmd_sta(mvm, vअगर, action,
						क्रमce_assoc_off,
						bssid_override);
	हाल NL80211_IFTYPE_AP:
		अगर (!vअगर->p2p)
			वापस iwl_mvm_mac_ctxt_cmd_ap(mvm, vअगर, action);
		अन्यथा
			वापस iwl_mvm_mac_ctxt_cmd_go(mvm, vअगर, action);
	हाल NL80211_IFTYPE_MONITOR:
		वापस iwl_mvm_mac_ctxt_cmd_listener(mvm, vअगर, action);
	हाल NL80211_IFTYPE_P2P_DEVICE:
		वापस iwl_mvm_mac_ctxt_cmd_p2p_device(mvm, vअगर, action);
	हाल NL80211_IFTYPE_ADHOC:
		वापस iwl_mvm_mac_ctxt_cmd_ibss(mvm, vअगर, action);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक iwl_mvm_mac_ctxt_add(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	पूर्णांक ret;

	अगर (WARN_ONCE(mvmvअगर->uploaded, "Adding active MAC %pM/%d\n",
		      vअगर->addr, ieee80211_vअगर_type_p2p(vअगर)))
		वापस -EIO;

	ret = iwl_mvm_mac_ctx_send(mvm, vअगर, FW_CTXT_ACTION_ADD,
				   true, शून्य);
	अगर (ret)
		वापस ret;

	/* will only करो anything at resume from D3 समय */
	iwl_mvm_set_last_nonqos_seq(mvm, vअगर);

	mvmvअगर->uploaded = true;
	वापस 0;
पूर्ण

पूर्णांक iwl_mvm_mac_ctxt_changed(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     bool क्रमce_assoc_off, स्थिर u8 *bssid_override)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (WARN_ONCE(!mvmvअगर->uploaded, "Changing inactive MAC %pM/%d\n",
		      vअगर->addr, ieee80211_vअगर_type_p2p(vअगर)))
		वापस -EIO;

	वापस iwl_mvm_mac_ctx_send(mvm, vअगर, FW_CTXT_ACTION_MODIFY,
				    क्रमce_assoc_off, bssid_override);
पूर्ण

पूर्णांक iwl_mvm_mac_ctxt_हटाओ(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mac_ctx_cmd cmd;
	पूर्णांक ret;

	अगर (WARN_ONCE(!mvmvअगर->uploaded, "Removing inactive MAC %pM/%d\n",
		      vअगर->addr, ieee80211_vअगर_type_p2p(vअगर)))
		वापस -EIO;

	स_रखो(&cmd, 0, माप(cmd));

	cmd.id_and_color = cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							   mvmvअगर->color));
	cmd.action = cpu_to_le32(FW_CTXT_ACTION_REMOVE);

	ret = iwl_mvm_send_cmd_pdu(mvm, MAC_CONTEXT_CMD, 0,
				   माप(cmd), &cmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to remove MAC context: %d\n", ret);
		वापस ret;
	पूर्ण

	mvmvअगर->uploaded = false;

	अगर (vअगर->type == NL80211_IFTYPE_MONITOR) अणु
		__clear_bit(IEEE80211_HW_RX_INCLUDES_FCS, mvm->hw->flags);
		iwl_mvm_dealloc_snअगर_sta(mvm);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_csa_count_करोwn(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_vअगर *csa_vअगर, u32 gp2,
				   bool tx_success)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर =
			iwl_mvm_vअगर_from_mac80211(csa_vअगर);

	/* Don't start to countकरोwn from a failed beacon */
	अगर (!tx_success && !mvmvअगर->csa_countकरोwn)
		वापस;

	mvmvअगर->csa_countकरोwn = true;

	अगर (!ieee80211_beacon_cntdwn_is_complete(csa_vअगर)) अणु
		पूर्णांक c = ieee80211_beacon_update_cntdwn(csa_vअगर);

		iwl_mvm_mac_ctxt_beacon_changed(mvm, csa_vअगर);
		अगर (csa_vअगर->p2p &&
		    !iwl_mvm_te_scheduled(&mvmvअगर->समय_event_data) && gp2 &&
		    tx_success) अणु
			u32 rel_समय = (c + 1) *
				       csa_vअगर->bss_conf.beacon_पूर्णांक -
				       IWL_MVM_CHANNEL_SWITCH_TIME_GO;
			u32 apply_समय = gp2 + rel_समय * 1024;

			iwl_mvm_schedule_csa_period(mvm, csa_vअगर,
					 IWL_MVM_CHANNEL_SWITCH_TIME_GO -
					 IWL_MVM_CHANNEL_SWITCH_MARGIN,
					 apply_समय);
		पूर्ण
	पूर्ण अन्यथा अगर (!iwl_mvm_te_scheduled(&mvmvअगर->समय_event_data)) अणु
		/* we करोn't have CSA NoA scheduled yet, चयन now */
		ieee80211_csa_finish(csa_vअगर);
		RCU_INIT_POINTER(mvm->csa_vअगर, शून्य);
	पूर्ण
पूर्ण

व्योम iwl_mvm_rx_beacon_notअगर(काष्ठा iwl_mvm *mvm,
			     काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	अचिन्हित पूर्णांक pkt_len = iwl_rx_packet_payload_len(pkt);
	काष्ठा iwl_extended_beacon_notअगर *beacon = (व्योम *)pkt->data;
	काष्ठा iwl_extended_beacon_notअगर_v5 *beacon_v5 = (व्योम *)pkt->data;
	काष्ठा ieee80211_vअगर *csa_vअगर;
	काष्ठा ieee80211_vअगर *tx_blocked_vअगर;
	काष्ठा agg_tx_status *agg_status;
	u16 status;

	lockdep_निश्चित_held(&mvm->mutex);

	mvm->ap_last_beacon_gp2 = le32_to_cpu(beacon->gp2);

	अगर (!iwl_mvm_is_लघु_beacon_notअगर_supported(mvm)) अणु
		काष्ठा iwl_mvm_tx_resp *beacon_notअगरy_hdr =
			&beacon_v5->beacon_notअगरy_hdr;

		अगर (unlikely(pkt_len < माप(*beacon_v5)))
			वापस;

		mvm->ibss_manager = beacon_v5->ibss_mgr_status != 0;
		agg_status = iwl_mvm_get_agg_status(mvm, beacon_notअगरy_hdr);
		status = le16_to_cpu(agg_status->status) & TX_STATUS_MSK;
		IWL_DEBUG_RX(mvm,
			     "beacon status %#x retries:%d tsf:0x%016llX gp2:0x%X rate:%d\n",
			     status, beacon_notअगरy_hdr->failure_frame,
			     le64_to_cpu(beacon->tsf),
			     mvm->ap_last_beacon_gp2,
			     le32_to_cpu(beacon_notअगरy_hdr->initial_rate));
	पूर्ण अन्यथा अणु
		अगर (unlikely(pkt_len < माप(*beacon)))
			वापस;

		mvm->ibss_manager = beacon->ibss_mgr_status != 0;
		status = le32_to_cpu(beacon->status) & TX_STATUS_MSK;
		IWL_DEBUG_RX(mvm,
			     "beacon status %#x tsf:0x%016llX gp2:0x%X\n",
			     status, le64_to_cpu(beacon->tsf),
			     mvm->ap_last_beacon_gp2);
	पूर्ण

	csa_vअगर = rcu_dereference_रक्षित(mvm->csa_vअगर,
					    lockdep_is_held(&mvm->mutex));
	अगर (unlikely(csa_vअगर && csa_vअगर->csa_active))
		iwl_mvm_csa_count_करोwn(mvm, csa_vअगर, mvm->ap_last_beacon_gp2,
				       (status == TX_STATUS_SUCCESS));

	tx_blocked_vअगर = rcu_dereference_रक्षित(mvm->csa_tx_blocked_vअगर,
						lockdep_is_held(&mvm->mutex));
	अगर (unlikely(tx_blocked_vअगर)) अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर =
			iwl_mvm_vअगर_from_mac80211(tx_blocked_vअगर);

		/*
		 * The channel चयन is started and we have blocked the
		 * stations. If this is the first beacon (the समयout wasn't
		 * set), set the unblock समयout, otherwise countकरोwn
		 */
		अगर (!mvm->csa_tx_block_bcn_समयout)
			mvm->csa_tx_block_bcn_समयout =
				IWL_MVM_CS_UNBLOCK_TX_TIMEOUT;
		अन्यथा
			mvm->csa_tx_block_bcn_समयout--;

		/* Check अगर the समयout is expired, and unblock tx */
		अगर (mvm->csa_tx_block_bcn_समयout == 0) अणु
			iwl_mvm_modअगरy_all_sta_disable_tx(mvm, mvmvअगर, false);
			RCU_INIT_POINTER(mvm->csa_tx_blocked_vअगर, शून्य);
		पूर्ण
	पूर्ण
पूर्ण

व्योम iwl_mvm_rx_missed_beacons_notअगर(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_missed_beacons_notअगर *mb = (व्योम *)pkt->data;
	काष्ठा iwl_fw_dbg_trigger_missed_bcon *bcon_trig;
	काष्ठा iwl_fw_dbg_trigger_tlv *trigger;
	u32 stop_trig_missed_bcon, stop_trig_missed_bcon_since_rx;
	u32 rx_missed_bcon, rx_missed_bcon_since_rx;
	काष्ठा ieee80211_vअगर *vअगर;
	u32 id = le32_to_cpu(mb->mac_id);
	जोड़ iwl_dbg_tlv_tp_data tp_data = अणु .fw_pkt = pkt पूर्ण;

	IWL_DEBUG_INFO(mvm,
		       "missed bcn mac_id=%u, consecutive=%u (%u, %u, %u)\n",
		       le32_to_cpu(mb->mac_id),
		       le32_to_cpu(mb->consec_missed_beacons),
		       le32_to_cpu(mb->consec_missed_beacons_since_last_rx),
		       le32_to_cpu(mb->num_recvd_beacons),
		       le32_to_cpu(mb->num_expected_beacons));

	rcu_पढ़ो_lock();

	vअगर = iwl_mvm_rcu_dereference_vअगर_id(mvm, id, true);
	अगर (!vअगर)
		जाओ out;

	rx_missed_bcon = le32_to_cpu(mb->consec_missed_beacons);
	rx_missed_bcon_since_rx =
		le32_to_cpu(mb->consec_missed_beacons_since_last_rx);
	/*
	 * TODO: the threshold should be adjusted based on latency conditions,
	 * and/or in हाल of a CS flow on one of the other AP vअगरs.
	 */
	अगर (rx_missed_bcon > IWL_MVM_MISSED_BEACONS_THRESHOLD_LONG)
		iwl_mvm_connection_loss(mvm, vअगर, "missed beacons");
	अन्यथा अगर (rx_missed_bcon_since_rx > IWL_MVM_MISSED_BEACONS_THRESHOLD)
		ieee80211_beacon_loss(vअगर);

	iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt,
			       IWL_FW_INI_TIME_POINT_MISSED_BEACONS, &tp_data);

	trigger = iwl_fw_dbg_trigger_on(&mvm->fwrt, ieee80211_vअगर_to_wdev(vअगर),
					FW_DBG_TRIGGER_MISSED_BEACONS);
	अगर (!trigger)
		जाओ out;

	bcon_trig = (व्योम *)trigger->data;
	stop_trig_missed_bcon = le32_to_cpu(bcon_trig->stop_consec_missed_bcon);
	stop_trig_missed_bcon_since_rx =
		le32_to_cpu(bcon_trig->stop_consec_missed_bcon_since_rx);

	/* TODO: implement start trigger */

	अगर (rx_missed_bcon_since_rx >= stop_trig_missed_bcon_since_rx ||
	    rx_missed_bcon >= stop_trig_missed_bcon)
		iwl_fw_dbg_collect_trig(&mvm->fwrt, trigger, शून्य);

out:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम iwl_mvm_rx_stored_beacon_notअगर(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	अचिन्हित पूर्णांक pkt_len = iwl_rx_packet_payload_len(pkt);
	काष्ठा iwl_stored_beacon_notअगर *sb = (व्योम *)pkt->data;
	काष्ठा ieee80211_rx_status rx_status;
	काष्ठा sk_buff *skb;
	u32 size = le32_to_cpu(sb->byte_count);

	अगर (size == 0 || pkt_len < काष्ठा_size(sb, data, size))
		वापस;

	skb = alloc_skb(size, GFP_ATOMIC);
	अगर (!skb) अणु
		IWL_ERR(mvm, "alloc_skb failed\n");
		वापस;
	पूर्ण

	/* update rx_status according to the notअगरication's metadata */
	स_रखो(&rx_status, 0, माप(rx_status));
	rx_status.maस_समय = le64_to_cpu(sb->tsf);
	/* TSF as indicated by the firmware  is at INA समय */
	rx_status.flag |= RX_FLAG_MACTIME_PLCP_START;
	rx_status.device_बारtamp = le32_to_cpu(sb->प्रणाली_समय);
	rx_status.band =
		(sb->band & cpu_to_le16(RX_RES_PHY_FLAGS_BAND_24)) ?
				NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
	rx_status.freq =
		ieee80211_channel_to_frequency(le16_to_cpu(sb->channel),
					       rx_status.band);

	/* copy the data */
	skb_put_data(skb, sb->data, size);
	स_नकल(IEEE80211_SKB_RXCB(skb), &rx_status, माप(rx_status));

	/* pass it as regular rx to mac80211 */
	ieee80211_rx_napi(mvm->hw, शून्य, skb, शून्य);
पूर्ण

व्योम iwl_mvm_probe_resp_data_notअगर(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_probe_resp_data_notअगर *notअगर = (व्योम *)pkt->data;
	काष्ठा iwl_probe_resp_data *old_data, *new_data;
	u32 id = le32_to_cpu(notअगर->mac_id);
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा iwl_mvm_vअगर *mvmvअगर;

	IWL_DEBUG_INFO(mvm, "Probe response data notif: noa %d, csa %d\n",
		       notअगर->noa_active, notअगर->csa_counter);

	vअगर = iwl_mvm_rcu_dereference_vअगर_id(mvm, id, false);
	अगर (!vअगर)
		वापस;

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	new_data = kzalloc(माप(*new_data), GFP_KERNEL);
	अगर (!new_data)
		वापस;

	स_नकल(&new_data->notअगर, notअगर, माप(new_data->notअगर));

	/* noa_attr contains 1 reserved byte, need to subकाष्ठा it */
	new_data->noa_len = माप(काष्ठा ieee80211_venकरोr_ie) +
			    माप(new_data->notअगर.noa_attr) - 1;

	/*
	 * If it's a one समय NoA, only one descriptor is needed,
	 * adjust the length according to len_low.
	 */
	अगर (new_data->notअगर.noa_attr.len_low ==
	    माप(काष्ठा ieee80211_p2p_noa_desc) + 2)
		new_data->noa_len -= माप(काष्ठा ieee80211_p2p_noa_desc);

	old_data = rcu_dereference_रक्षित(mvmvअगर->probe_resp_data,
					lockdep_is_held(&mvmvअगर->mvm->mutex));
	rcu_assign_poपूर्णांकer(mvmvअगर->probe_resp_data, new_data);

	अगर (old_data)
		kमुक्त_rcu(old_data, rcu_head);

	अगर (notअगर->csa_counter != IWL_PROBE_RESP_DATA_NO_CSA &&
	    notअगर->csa_counter >= 1)
		ieee80211_beacon_set_cntdwn(vअगर, notअगर->csa_counter);
पूर्ण

व्योम iwl_mvm_channel_चयन_noa_notअगर(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_channel_चयन_noa_notअगर *notअगर = (व्योम *)pkt->data;
	काष्ठा ieee80211_vअगर *csa_vअगर, *vअगर;
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	u32 id_n_color, csa_id, mac_id;

	id_n_color = le32_to_cpu(notअगर->id_and_color);
	mac_id = id_n_color & FW_CTXT_ID_MSK;

	अगर (WARN_ON_ONCE(mac_id >= NUM_MAC_INDEX_DRIVER))
		वापस;

	rcu_पढ़ो_lock();
	vअगर = rcu_dereference(mvm->vअगर_id_to_mac[mac_id]);
	mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
		csa_vअगर = rcu_dereference(mvm->csa_vअगर);
		अगर (WARN_ON(!csa_vअगर || !csa_vअगर->csa_active ||
			    csa_vअगर != vअगर))
			जाओ out_unlock;

		csa_id = FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color);
		अगर (WARN(csa_id != id_n_color,
			 "channel switch noa notification on unexpected vif (csa_vif=%d, notif=%d)",
			 csa_id, id_n_color))
			जाओ out_unlock;

		IWL_DEBUG_INFO(mvm, "Channel Switch Started Notification\n");

		schedule_delayed_work(&mvm->cs_tx_unblock_dwork,
				      msecs_to_jअगरfies(IWL_MVM_CS_UNBLOCK_TX_TIMEOUT *
						       csa_vअगर->bss_conf.beacon_पूर्णांक));

		ieee80211_csa_finish(csa_vअगर);

		rcu_पढ़ो_unlock();

		RCU_INIT_POINTER(mvm->csa_vअगर, शून्य);
		वापस;
	हाल NL80211_IFTYPE_STATION:
		iwl_mvm_csa_client_असलent(mvm, vअगर);
		cancel_delayed_work(&mvmvअगर->csa_work);
		ieee80211_chचयन_करोne(vअगर, true);
		अवरोध;
	शेष:
		/* should never happen */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम iwl_mvm_rx_missed_vap_notअगर(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_missed_vap_notअगर *mb = (व्योम *)pkt->data;
	काष्ठा ieee80211_vअगर *vअगर;
	u32 id = le32_to_cpu(mb->mac_id);

	IWL_DEBUG_INFO(mvm,
		       "missed_vap notify mac_id=%u, num_beacon_intervals_elapsed=%u, profile_periodicity=%u\n",
		       le32_to_cpu(mb->mac_id),
		       mb->num_beacon_पूर्णांकervals_elapsed,
		       mb->profile_periodicity);

	rcu_पढ़ो_lock();

	vअगर = iwl_mvm_rcu_dereference_vअगर_id(mvm, id, true);
	अगर (vअगर)
		iwl_mvm_connection_loss(mvm, vअगर, "missed vap beacon");

	rcu_पढ़ो_unlock();
पूर्ण
