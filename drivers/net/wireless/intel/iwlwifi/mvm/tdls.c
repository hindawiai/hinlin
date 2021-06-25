<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2014 Intel Mobile Communications GmbH
 * Copyright (C) 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */
#समावेश <linux/etherdevice.h>
#समावेश "mvm.h"
#समावेश "time-event.h"
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"

#घोषणा TU_TO_US(x) (x * 1024)
#घोषणा TU_TO_MS(x) (TU_TO_US(x) / 1000)

व्योम iwl_mvm_tearकरोwn_tdls_peers(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	पूर्णांक i;

	lockdep_निश्चित_held(&mvm->mutex);

	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) अणु
		sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		अगर (!sta || IS_ERR(sta) || !sta->tdls)
			जारी;

		mvmsta = iwl_mvm_sta_from_mac80211(sta);
		ieee80211_tdls_oper_request(mvmsta->vअगर, sta->addr,
				NL80211_TDLS_TEARDOWN,
				WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED,
				GFP_KERNEL);
	पूर्ण
पूर्ण

पूर्णांक iwl_mvm_tdls_sta_count(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	पूर्णांक count = 0;
	पूर्णांक i;

	lockdep_निश्चित_held(&mvm->mutex);

	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) अणु
		sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		अगर (!sta || IS_ERR(sta) || !sta->tdls)
			जारी;

		अगर (vअगर) अणु
			mvmsta = iwl_mvm_sta_from_mac80211(sta);
			अगर (mvmsta->vअगर != vअगर)
				जारी;
		पूर्ण

		count++;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम iwl_mvm_tdls_config(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_rx_packet *pkt;
	काष्ठा iwl_tdls_config_res *resp;
	काष्ठा iwl_tdls_config_cmd tdls_cfg_cmd = अणुपूर्ण;
	काष्ठा iwl_host_cmd cmd = अणु
		.id = TDLS_CONFIG_CMD,
		.flags = CMD_WANT_SKB,
		.data = अणु &tdls_cfg_cmd, पूर्ण,
		.len = अणु माप(काष्ठा iwl_tdls_config_cmd), पूर्ण,
	पूर्ण;
	काष्ठा ieee80211_sta *sta;
	पूर्णांक ret, i, cnt;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	lockdep_निश्चित_held(&mvm->mutex);

	tdls_cfg_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color));
	tdls_cfg_cmd.tx_to_ap_tid = IWL_MVM_TDLS_FW_TID;
	tdls_cfg_cmd.tx_to_ap_ssn = cpu_to_le16(0); /* not used क्रम now */

	/* क्रम now the Tx cmd is empty and unused */

	/* populate TDLS peer data */
	cnt = 0;
	क्रम (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) अणु
		sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[i],
						lockdep_is_held(&mvm->mutex));
		अगर (IS_ERR_OR_शून्य(sta) || !sta->tdls)
			जारी;

		tdls_cfg_cmd.sta_info[cnt].sta_id = i;
		tdls_cfg_cmd.sta_info[cnt].tx_to_peer_tid =
							IWL_MVM_TDLS_FW_TID;
		tdls_cfg_cmd.sta_info[cnt].tx_to_peer_ssn = cpu_to_le16(0);
		tdls_cfg_cmd.sta_info[cnt].is_initiator =
				cpu_to_le32(sta->tdls_initiator ? 1 : 0);

		cnt++;
	पूर्ण

	tdls_cfg_cmd.tdls_peer_count = cnt;
	IWL_DEBUG_TDLS(mvm, "send TDLS config to FW for %d peers\n", cnt);

	ret = iwl_mvm_send_cmd(mvm, &cmd);
	अगर (WARN_ON_ONCE(ret))
		वापस;

	pkt = cmd.resp_pkt;

	WARN_ON_ONCE(iwl_rx_packet_payload_len(pkt) != माप(*resp));

	/* we करोn't really care about the response at this poपूर्णांक */

	iwl_मुक्त_resp(&cmd);
पूर्ण

व्योम iwl_mvm_recalc_tdls_state(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			       bool sta_added)
अणु
	पूर्णांक tdls_sta_cnt = iwl_mvm_tdls_sta_count(mvm, vअगर);

	/* when the first peer joins, send a घातer update first */
	अगर (tdls_sta_cnt == 1 && sta_added)
		iwl_mvm_घातer_update_mac(mvm);

	/* Configure the FW with TDLS peer info only अगर TDLS channel चयन
	 * capability is set.
	 * TDLS config data is used currently only in TDLS channel चयन code.
	 * Supposed to serve also TDLS buffer station which is not implemneted
	 * yet in FW*/
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_TDLS_CHANNEL_SWITCH))
		iwl_mvm_tdls_config(mvm, vअगर);

	/* when the last peer leaves, send a घातer update last */
	अगर (tdls_sta_cnt == 0 && !sta_added)
		iwl_mvm_घातer_update_mac(mvm);
पूर्ण

व्योम iwl_mvm_mac_mgd_protect_tdls_discover(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	u32 duration = 2 * vअगर->bss_conf.dtim_period * vअगर->bss_conf.beacon_पूर्णांक;

	/* Protect the session to hear the TDLS setup response on the channel */
	mutex_lock(&mvm->mutex);
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_SESSION_PROT_CMD))
		iwl_mvm_schedule_session_protection(mvm, vअगर, duration,
						    duration, true);
	अन्यथा
		iwl_mvm_protect_session(mvm, vअगर, duration,
					duration, 100, true);
	mutex_unlock(&mvm->mutex);
पूर्ण

अटल स्थिर अक्षर *
iwl_mvm_tdls_cs_state_str(क्रमागत iwl_mvm_tdls_cs_state state)
अणु
	चयन (state) अणु
	हाल IWL_MVM_TDLS_SW_IDLE:
		वापस "IDLE";
	हाल IWL_MVM_TDLS_SW_REQ_SENT:
		वापस "REQ SENT";
	हाल IWL_MVM_TDLS_SW_RESP_RCVD:
		वापस "RESP RECEIVED";
	हाल IWL_MVM_TDLS_SW_REQ_RCVD:
		वापस "REQ RECEIVED";
	हाल IWL_MVM_TDLS_SW_ACTIVE:
		वापस "ACTIVE";
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम iwl_mvm_tdls_update_cs_state(काष्ठा iwl_mvm *mvm,
					 क्रमागत iwl_mvm_tdls_cs_state state)
अणु
	अगर (mvm->tdls_cs.state == state)
		वापस;

	IWL_DEBUG_TDLS(mvm, "TDLS channel switch state: %s -> %s\n",
		       iwl_mvm_tdls_cs_state_str(mvm->tdls_cs.state),
		       iwl_mvm_tdls_cs_state_str(state));
	mvm->tdls_cs.state = state;

	/* we only send requests to our चयनing peer - update sent समय */
	अगर (state == IWL_MVM_TDLS_SW_REQ_SENT)
		mvm->tdls_cs.peer.sent_बारtamp = iwl_mvm_get_sysसमय(mvm);

	अगर (state == IWL_MVM_TDLS_SW_IDLE)
		mvm->tdls_cs.cur_sta_id = IWL_MVM_INVALID_STA;
पूर्ण

व्योम iwl_mvm_rx_tdls_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_tdls_channel_चयन_notअगर *notअगर = (व्योम *)pkt->data;
	काष्ठा ieee80211_sta *sta;
	अचिन्हित पूर्णांक delay;
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा ieee80211_vअगर *vअगर;
	u32 sta_id = le32_to_cpu(notअगर->sta_id);

	lockdep_निश्चित_held(&mvm->mutex);

	/* can fail someबार */
	अगर (!le32_to_cpu(notअगर->status)) अणु
		iwl_mvm_tdls_update_cs_state(mvm, IWL_MVM_TDLS_SW_IDLE);
		वापस;
	पूर्ण

	अगर (WARN_ON(sta_id >= mvm->fw->ucode_capa.num_stations))
		वापस;

	sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[sta_id],
					lockdep_is_held(&mvm->mutex));
	/* the station may not be here, but अगर it is, it must be a TDLS peer */
	अगर (IS_ERR_OR_शून्य(sta) || WARN_ON(!sta->tdls))
		वापस;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	vअगर = mvmsta->vअगर;

	/*
	 * Update state and possibly चयन again after this is over (DTIM).
	 * Also convert TU to msec.
	 */
	delay = TU_TO_MS(vअगर->bss_conf.dtim_period * vअगर->bss_conf.beacon_पूर्णांक);
	mod_delayed_work(प्रणाली_wq, &mvm->tdls_cs.dwork,
			 msecs_to_jअगरfies(delay));

	iwl_mvm_tdls_update_cs_state(mvm, IWL_MVM_TDLS_SW_ACTIVE);
पूर्ण

अटल पूर्णांक
iwl_mvm_tdls_check_action(काष्ठा iwl_mvm *mvm,
			  क्रमागत iwl_tdls_channel_चयन_type type,
			  स्थिर u8 *peer, bool peer_initiator, u32 बारtamp)
अणु
	bool same_peer = false;
	पूर्णांक ret = 0;

	/* get the existing peer अगर it's there */
	अगर (mvm->tdls_cs.state != IWL_MVM_TDLS_SW_IDLE &&
	    mvm->tdls_cs.cur_sta_id != IWL_MVM_INVALID_STA) अणु
		काष्ठा ieee80211_sta *sta = rcu_dereference_रक्षित(
				mvm->fw_id_to_mac_id[mvm->tdls_cs.cur_sta_id],
				lockdep_is_held(&mvm->mutex));
		अगर (!IS_ERR_OR_शून्य(sta))
			same_peer = ether_addr_equal(peer, sta->addr);
	पूर्ण

	चयन (mvm->tdls_cs.state) अणु
	हाल IWL_MVM_TDLS_SW_IDLE:
		/*
		 * might be spurious packet from the peer after the चयन is
		 * alपढ़ोy करोne
		 */
		अगर (type == TDLS_MOVE_CH)
			ret = -EINVAL;
		अवरोध;
	हाल IWL_MVM_TDLS_SW_REQ_SENT:
		/* only allow requests from the same peer */
		अगर (!same_peer)
			ret = -EBUSY;
		अन्यथा अगर (type == TDLS_SEND_CHAN_SW_RESP_AND_MOVE_CH &&
			 !peer_initiator)
			/*
			 * We received a ch-चयन request जबतक an outgoing
			 * one is pending. Allow it अगर the peer is the link
			 * initiator.
			 */
			ret = -EBUSY;
		अन्यथा अगर (type == TDLS_SEND_CHAN_SW_REQ)
			/* रुको क्रम idle beक्रमe sending another request */
			ret = -EBUSY;
		अन्यथा अगर (बारtamp <= mvm->tdls_cs.peer.sent_बारtamp)
			/* we got a stale response - ignore it */
			ret = -EINVAL;
		अवरोध;
	हाल IWL_MVM_TDLS_SW_RESP_RCVD:
		/*
		 * we are रुकोing क्रम the FW to give an "active" notअगरication,
		 * so ignore requests in the meanसमय
		 */
		ret = -EBUSY;
		अवरोध;
	हाल IWL_MVM_TDLS_SW_REQ_RCVD:
		/* as above, allow the link initiator to proceed */
		अगर (type == TDLS_SEND_CHAN_SW_REQ) अणु
			अगर (!same_peer)
				ret = -EBUSY;
			अन्यथा अगर (peer_initiator) /* they are the initiator */
				ret = -EBUSY;
		पूर्ण अन्यथा अगर (type == TDLS_MOVE_CH) अणु
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IWL_MVM_TDLS_SW_ACTIVE:
		/*
		 * the only valid request when active is a request to वापस
		 * to the base channel by the current off-channel peer
		 */
		अगर (type != TDLS_MOVE_CH || !same_peer)
			ret = -EBUSY;
		अवरोध;
	पूर्ण

	अगर (ret)
		IWL_DEBUG_TDLS(mvm,
			       "Invalid TDLS action %d state %d peer %pM same_peer %d initiator %d\n",
			       type, mvm->tdls_cs.state, peer, same_peer,
			       peer_initiator);

	वापस ret;
पूर्ण

अटल पूर्णांक
iwl_mvm_tdls_config_channel_चयन(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_vअगर *vअगर,
				   क्रमागत iwl_tdls_channel_चयन_type type,
				   स्थिर u8 *peer, bool peer_initiator,
				   u8 oper_class,
				   काष्ठा cfg80211_chan_def *chandef,
				   u32 बारtamp, u16 चयन_समय,
				   u16 चयन_समयout, काष्ठा sk_buff *skb,
				   u32 ch_sw_पंचांग_ie)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा iwl_tdls_channel_चयन_cmd cmd = अणु0पूर्ण;
	काष्ठा iwl_tdls_channel_चयन_cmd_tail *tail =
		iwl_mvm_chan_info_cmd_tail(mvm, &cmd.ci);
	u16 len = माप(cmd) - iwl_mvm_chan_info_padding(mvm);
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	ret = iwl_mvm_tdls_check_action(mvm, type, peer, peer_initiator,
					बारtamp);
	अगर (ret)
		वापस ret;

	अगर (!skb || WARN_ON(skb->len > IWL_TDLS_CH_SW_FRAME_MAX_SIZE)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	cmd.चयन_type = type;
	tail->timing.frame_बारtamp = cpu_to_le32(बारtamp);
	tail->timing.चयन_समय = cpu_to_le32(चयन_समय);
	tail->timing.चयन_समयout = cpu_to_le32(चयन_समयout);

	rcu_पढ़ो_lock();
	sta = ieee80211_find_sta(vअगर, peer);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	cmd.peer_sta_id = cpu_to_le32(mvmsta->sta_id);

	अगर (!chandef) अणु
		अगर (mvm->tdls_cs.state == IWL_MVM_TDLS_SW_REQ_SENT &&
		    mvm->tdls_cs.peer.chandef.chan) अणु
			/* actually moving to the channel */
			chandef = &mvm->tdls_cs.peer.chandef;
		पूर्ण अन्यथा अगर (mvm->tdls_cs.state == IWL_MVM_TDLS_SW_ACTIVE &&
			   type == TDLS_MOVE_CH) अणु
			/* we need to वापस to base channel */
			काष्ठा ieee80211_chanctx_conf *chanctx =
					rcu_dereference(vअगर->chanctx_conf);

			अगर (WARN_ON_ONCE(!chanctx)) अणु
				rcu_पढ़ो_unlock();
				जाओ out;
			पूर्ण

			chandef = &chanctx->def;
		पूर्ण
	पूर्ण

	अगर (chandef)
		iwl_mvm_set_chan_info_chandef(mvm, &cmd.ci, chandef);

	/* keep quota calculation simple क्रम now - 50% of DTIM क्रम TDLS */
	tail->timing.max_offchan_duration =
			cpu_to_le32(TU_TO_US(vअगर->bss_conf.dtim_period *
					     vअगर->bss_conf.beacon_पूर्णांक) / 2);

	/* Switch समय is the first element in the चयन-timing IE. */
	tail->frame.चयन_समय_offset = cpu_to_le32(ch_sw_पंचांग_ie + 2);

	info = IEEE80211_SKB_CB(skb);
	hdr = (व्योम *)skb->data;
	अगर (info->control.hw_key) अणु
		अगर (info->control.hw_key->cipher != WLAN_CIPHER_SUITE_CCMP) अणु
			rcu_पढ़ो_unlock();
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		iwl_mvm_set_tx_cmd_ccmp(info, &tail->frame.tx_cmd);
	पूर्ण

	iwl_mvm_set_tx_cmd(mvm, skb, &tail->frame.tx_cmd, info,
			   mvmsta->sta_id);

	iwl_mvm_set_tx_cmd_rate(mvm, &tail->frame.tx_cmd, info, sta,
				hdr->frame_control);
	rcu_पढ़ो_unlock();

	स_नकल(tail->frame.data, skb->data, skb->len);

	ret = iwl_mvm_send_cmd_pdu(mvm, TDLS_CHANNEL_SWITCH_CMD, 0, len, &cmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to send TDLS_CHANNEL_SWITCH cmd: %d\n",
			ret);
		जाओ out;
	पूर्ण

	/* channel चयन has started, update state */
	अगर (type != TDLS_MOVE_CH) अणु
		mvm->tdls_cs.cur_sta_id = mvmsta->sta_id;
		iwl_mvm_tdls_update_cs_state(mvm,
					     type == TDLS_SEND_CHAN_SW_REQ ?
					     IWL_MVM_TDLS_SW_REQ_SENT :
					     IWL_MVM_TDLS_SW_REQ_RCVD);
	पूर्ण अन्यथा अणु
		iwl_mvm_tdls_update_cs_state(mvm, IWL_MVM_TDLS_SW_RESP_RCVD);
	पूर्ण

out:

	/* channel चयन failed - we are idle */
	अगर (ret)
		iwl_mvm_tdls_update_cs_state(mvm, IWL_MVM_TDLS_SW_IDLE);

	वापस ret;
पूर्ण

व्योम iwl_mvm_tdls_ch_चयन_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iwl_mvm *mvm;
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा ieee80211_vअगर *vअगर;
	अचिन्हित पूर्णांक delay;
	पूर्णांक ret;

	mvm = container_of(work, काष्ठा iwl_mvm, tdls_cs.dwork.work);
	mutex_lock(&mvm->mutex);

	/* called after an active channel चयन has finished or समयd-out */
	iwl_mvm_tdls_update_cs_state(mvm, IWL_MVM_TDLS_SW_IDLE);

	/* station might be gone, in that हाल करो nothing */
	अगर (mvm->tdls_cs.peer.sta_id == IWL_MVM_INVALID_STA)
		जाओ out;

	sta = rcu_dereference_रक्षित(
				mvm->fw_id_to_mac_id[mvm->tdls_cs.peer.sta_id],
				lockdep_is_held(&mvm->mutex));
	/* the station may not be here, but अगर it is, it must be a TDLS peer */
	अगर (!sta || IS_ERR(sta) || WARN_ON(!sta->tdls))
		जाओ out;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	vअगर = mvmsta->vअगर;
	ret = iwl_mvm_tdls_config_channel_चयन(mvm, vअगर,
						 TDLS_SEND_CHAN_SW_REQ,
						 sta->addr,
						 mvm->tdls_cs.peer.initiator,
						 mvm->tdls_cs.peer.op_class,
						 &mvm->tdls_cs.peer.chandef,
						 0, 0, 0,
						 mvm->tdls_cs.peer.skb,
						 mvm->tdls_cs.peer.ch_sw_पंचांग_ie);
	अगर (ret)
		IWL_ERR(mvm, "Not sending TDLS channel switch: %d\n", ret);

	/* retry after a DTIM अगर we failed sending now */
	delay = TU_TO_MS(vअगर->bss_conf.dtim_period * vअगर->bss_conf.beacon_पूर्णांक);
	schedule_delayed_work(&mvm->tdls_cs.dwork, msecs_to_jअगरfies(delay));
out:
	mutex_unlock(&mvm->mutex);
पूर्ण

पूर्णांक
iwl_mvm_tdls_channel_चयन(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, u8 oper_class,
			    काष्ठा cfg80211_chan_def *chandef,
			    काष्ठा sk_buff *पंचांगpl_skb, u32 ch_sw_पंचांग_ie)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा iwl_mvm_sta *mvmsta;
	अचिन्हित पूर्णांक delay;
	पूर्णांक ret;

	mutex_lock(&mvm->mutex);

	IWL_DEBUG_TDLS(mvm, "TDLS channel switch with %pM ch %d width %d\n",
		       sta->addr, chandef->chan->center_freq, chandef->width);

	/* we only support a single peer क्रम channel चयनing */
	अगर (mvm->tdls_cs.peer.sta_id != IWL_MVM_INVALID_STA) अणु
		IWL_DEBUG_TDLS(mvm,
			       "Existing peer. Can't start switch with %pM\n",
			       sta->addr);
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = iwl_mvm_tdls_config_channel_चयन(mvm, vअगर,
						 TDLS_SEND_CHAN_SW_REQ,
						 sta->addr, sta->tdls_initiator,
						 oper_class, chandef, 0, 0, 0,
						 पंचांगpl_skb, ch_sw_पंचांग_ie);
	अगर (ret)
		जाओ out;

	/*
	 * Mark the peer as "in tdls switch" क्रम this vअगर. We only allow a
	 * single such peer per vअगर.
	 */
	mvm->tdls_cs.peer.skb = skb_copy(पंचांगpl_skb, GFP_KERNEL);
	अगर (!mvm->tdls_cs.peer.skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	mvm->tdls_cs.peer.sta_id = mvmsta->sta_id;
	mvm->tdls_cs.peer.chandef = *chandef;
	mvm->tdls_cs.peer.initiator = sta->tdls_initiator;
	mvm->tdls_cs.peer.op_class = oper_class;
	mvm->tdls_cs.peer.ch_sw_पंचांग_ie = ch_sw_पंचांग_ie;

	/*
	 * Wait क्रम 2 DTIM periods beक्रमe attempting the next चयन. The next
	 * चयन will be made sooner अगर the current one completes beक्रमe that.
	 */
	delay = 2 * TU_TO_MS(vअगर->bss_conf.dtim_period *
			     vअगर->bss_conf.beacon_पूर्णांक);
	mod_delayed_work(प्रणाली_wq, &mvm->tdls_cs.dwork,
			 msecs_to_jअगरfies(delay));

out:
	mutex_unlock(&mvm->mutex);
	वापस ret;
पूर्ण

व्योम iwl_mvm_tdls_cancel_channel_चयन(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	काष्ठा ieee80211_sta *cur_sta;
	bool रुको_क्रम_phy = false;

	mutex_lock(&mvm->mutex);

	IWL_DEBUG_TDLS(mvm, "TDLS cancel channel switch with %pM\n", sta->addr);

	/* we only support a single peer क्रम channel चयनing */
	अगर (mvm->tdls_cs.peer.sta_id == IWL_MVM_INVALID_STA) अणु
		IWL_DEBUG_TDLS(mvm, "No ch switch peer - %pM\n", sta->addr);
		जाओ out;
	पूर्ण

	cur_sta = rcu_dereference_रक्षित(
				mvm->fw_id_to_mac_id[mvm->tdls_cs.peer.sta_id],
				lockdep_is_held(&mvm->mutex));
	/* make sure it's the same peer */
	अगर (cur_sta != sta)
		जाओ out;

	/*
	 * If we're currently in a चयन because of the now canceled peer,
	 * रुको a DTIM here to make sure the phy is back on the base channel.
	 * We can't otherwise क्रमce it.
	 */
	अगर (mvm->tdls_cs.cur_sta_id == mvm->tdls_cs.peer.sta_id &&
	    mvm->tdls_cs.state != IWL_MVM_TDLS_SW_IDLE)
		रुको_क्रम_phy = true;

	mvm->tdls_cs.peer.sta_id = IWL_MVM_INVALID_STA;
	dev_kमुक्त_skb(mvm->tdls_cs.peer.skb);
	mvm->tdls_cs.peer.skb = शून्य;

out:
	mutex_unlock(&mvm->mutex);

	/* make sure the phy is on the base channel */
	अगर (रुको_क्रम_phy)
		msleep(TU_TO_MS(vअगर->bss_conf.dtim_period *
				vअगर->bss_conf.beacon_पूर्णांक));

	/* flush the channel चयन state */
	flush_delayed_work(&mvm->tdls_cs.dwork);

	IWL_DEBUG_TDLS(mvm, "TDLS ending channel switch with %pM\n", sta->addr);
पूर्ण

व्योम
iwl_mvm_tdls_recv_channel_चयन(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_tdls_ch_sw_params *params)
अणु
	काष्ठा iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	क्रमागत iwl_tdls_channel_चयन_type type;
	अचिन्हित पूर्णांक delay;
	स्थिर अक्षर *action_str =
		params->action_code == WLAN_TDLS_CHANNEL_SWITCH_REQUEST ?
		"REQ" : "RESP";

	mutex_lock(&mvm->mutex);

	IWL_DEBUG_TDLS(mvm,
		       "Received TDLS ch switch action %s from %pM status %d\n",
		       action_str, params->sta->addr, params->status);

	/*
	 * we got a non-zero status from a peer we were चयनing to - move to
	 * the idle state and retry again later
	 */
	अगर (params->action_code == WLAN_TDLS_CHANNEL_SWITCH_RESPONSE &&
	    params->status != 0 &&
	    mvm->tdls_cs.state == IWL_MVM_TDLS_SW_REQ_SENT &&
	    mvm->tdls_cs.cur_sta_id != IWL_MVM_INVALID_STA) अणु
		काष्ठा ieee80211_sta *cur_sta;

		/* make sure it's the same peer */
		cur_sta = rcu_dereference_रक्षित(
				mvm->fw_id_to_mac_id[mvm->tdls_cs.cur_sta_id],
				lockdep_is_held(&mvm->mutex));
		अगर (cur_sta == params->sta) अणु
			iwl_mvm_tdls_update_cs_state(mvm,
						     IWL_MVM_TDLS_SW_IDLE);
			जाओ retry;
		पूर्ण
	पूर्ण

	type = (params->action_code == WLAN_TDLS_CHANNEL_SWITCH_REQUEST) ?
	       TDLS_SEND_CHAN_SW_RESP_AND_MOVE_CH : TDLS_MOVE_CH;

	iwl_mvm_tdls_config_channel_चयन(mvm, vअगर, type, params->sta->addr,
					   params->sta->tdls_initiator, 0,
					   params->chandef, params->बारtamp,
					   params->चयन_समय,
					   params->चयन_समयout,
					   params->पंचांगpl_skb,
					   params->ch_sw_पंचांग_ie);

retry:
	/* रेजिस्टर a समयout in हाल we करोn't succeed in चयनing */
	delay = vअगर->bss_conf.dtim_period * vअगर->bss_conf.beacon_पूर्णांक *
		1024 / 1000;
	mod_delayed_work(प्रणाली_wq, &mvm->tdls_cs.dwork,
			 msecs_to_jअगरfies(delay));
	mutex_unlock(&mvm->mutex);
पूर्ण
