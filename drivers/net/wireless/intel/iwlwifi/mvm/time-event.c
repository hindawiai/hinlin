<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2017 Intel Deutschland GmbH
 */
#समावेश <linux/jअगरfies.h>
#समावेश <net/mac80211.h>

#समावेश "fw/notif-wait.h"
#समावेश "iwl-trans.h"
#समावेश "fw-api.h"
#समावेश "time-event.h"
#समावेश "mvm.h"
#समावेश "iwl-io.h"
#समावेश "iwl-prph.h"

/*
 * For the high priority TE use a समय event type that has similar priority to
 * the FW's action scan priority.
 */
#घोषणा IWL_MVM_ROC_TE_TYPE_NORMAL TE_P2P_DEVICE_DISCOVERABLE
#घोषणा IWL_MVM_ROC_TE_TYPE_MGMT_TX TE_P2P_CLIENT_ASSOC

व्योम iwl_mvm_te_clear_data(काष्ठा iwl_mvm *mvm,
			   काष्ठा iwl_mvm_समय_event_data *te_data)
अणु
	lockdep_निश्चित_held(&mvm->समय_event_lock);

	अगर (!te_data || !te_data->vअगर)
		वापस;

	list_del(&te_data->list);
	te_data->running = false;
	te_data->uid = 0;
	te_data->id = TE_MAX;
	te_data->vअगर = शून्य;
पूर्ण

व्योम iwl_mvm_roc_करोne_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा iwl_mvm *mvm = container_of(wk, काष्ठा iwl_mvm, roc_करोne_wk);

	/*
	 * Clear the ROC_RUNNING /ROC_AUX_RUNNING status bit.
	 * This will cause the TX path to drop offchannel transmissions.
	 * That would also be करोne by mac80211, but it is racy, in particular
	 * in the हाल that the समय event actually completed in the firmware
	 * (which is handled in iwl_mvm_te_handle_notअगर).
	 */
	clear_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status);
	clear_bit(IWL_MVM_STATUS_ROC_AUX_RUNNING, &mvm->status);

	synchronize_net();

	/*
	 * Flush the offchannel queue -- this is called when the समय
	 * event finishes or is canceled, so that frames queued क्रम it
	 * won't get stuck on the queue and be transmitted in the next
	 * समय event.
	 */

	mutex_lock(&mvm->mutex);
	अगर (test_and_clear_bit(IWL_MVM_STATUS_NEED_FLUSH_P2P, &mvm->status)) अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर;

		/*
		 * NB: access to this poपूर्णांकer would be racy, but the flush bit
		 * can only be set when we had a P2P-Device VIF, and we have a
		 * flush of this work in iwl_mvm_prepare_mac_removal() so it's
		 * not really racy.
		 */

		अगर (!WARN_ON(!mvm->p2p_device_vअगर)) अणु
			mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvm->p2p_device_vअगर);
			iwl_mvm_flush_sta(mvm, &mvmvअगर->bcast_sta, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* करो the same in हाल of hot spot 2.0 */
		iwl_mvm_flush_sta(mvm, &mvm->aux_sta, true);
		/* In newer version of this command an aux station is added only
		 * in हालs of dedicated tx queue and need to be हटाओd in end
		 * of use */
		अगर (iwl_fw_lookup_cmd_ver(mvm->fw, LONG_GROUP,
					  ADD_STA, 0) >= 12)
			iwl_mvm_rm_aux_sta(mvm);
	पूर्ण

	mutex_unlock(&mvm->mutex);
पूर्ण

अटल व्योम iwl_mvm_roc_finished(काष्ठा iwl_mvm *mvm)
अणु
	/*
	 * Of course, our status bit is just as racy as mac80211, so in
	 * addition, fire off the work काष्ठा which will drop all frames
	 * from the hardware queues that made it through the race. First
	 * it will of course synchronize the TX path to make sure that
	 * any *new* TX will be rejected.
	 */
	schedule_work(&mvm->roc_करोne_wk);
पूर्ण

अटल व्योम iwl_mvm_csa_noa_start(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा ieee80211_vअगर *csa_vअगर;

	rcu_पढ़ो_lock();

	csa_vअगर = rcu_dereference(mvm->csa_vअगर);
	अगर (!csa_vअगर || !csa_vअगर->csa_active)
		जाओ out_unlock;

	IWL_DEBUG_TE(mvm, "CSA NOA started\n");

	/*
	 * CSA NoA is started but we still have beacons to
	 * transmit on the current channel.
	 * So we just करो nothing here and the चयन
	 * will be perक्रमmed on the last TBTT.
	 */
	अगर (!ieee80211_beacon_cntdwn_is_complete(csa_vअगर)) अणु
		IWL_WARN(mvm, "CSA NOA started too early\n");
		जाओ out_unlock;
	पूर्ण

	ieee80211_csa_finish(csa_vअगर);

	rcu_पढ़ो_unlock();

	RCU_INIT_POINTER(mvm->csa_vअगर, शून्य);

	वापस;

out_unlock:
	rcu_पढ़ो_unlock();
पूर्ण

अटल bool iwl_mvm_te_check_disconnect(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_vअगर *vअगर,
					स्थिर अक्षर *errmsg)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस false;

	अगर (!mvmvअगर->csa_bcn_pending && vअगर->bss_conf.assoc &&
	    vअगर->bss_conf.dtim_period)
		वापस false;
	अगर (errmsg)
		IWL_ERR(mvm, "%s\n", errmsg);

	अगर (mvmvअगर->csa_bcn_pending) अणु
		काष्ठा iwl_mvm_sta *mvmsta;

		rcu_पढ़ो_lock();
		mvmsta = iwl_mvm_sta_from_staid_rcu(mvm, mvmvअगर->ap_sta_id);
		अगर (!WARN_ON(!mvmsta))
			iwl_mvm_sta_modअगरy_disable_tx(mvm, mvmsta, false);
		rcu_पढ़ो_unlock();
	पूर्ण

	iwl_mvm_connection_loss(mvm, vअगर, errmsg);
	वापस true;
पूर्ण

अटल व्योम
iwl_mvm_te_handle_notअगरy_csa(काष्ठा iwl_mvm *mvm,
			     काष्ठा iwl_mvm_समय_event_data *te_data,
			     काष्ठा iwl_समय_event_notअगर *notअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = te_data->vअगर;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	अगर (!notअगर->status)
		IWL_DEBUG_TE(mvm, "CSA time event failed to start\n");

	चयन (te_data->vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
		अगर (!notअगर->status)
			mvmvअगर->csa_failed = true;
		iwl_mvm_csa_noa_start(mvm);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (!notअगर->status) अणु
			iwl_mvm_connection_loss(mvm, vअगर,
						"CSA TE failed to start");
			अवरोध;
		पूर्ण
		iwl_mvm_csa_client_असलent(mvm, te_data->vअगर);
		cancel_delayed_work(&mvmvअगर->csa_work);
		ieee80211_chचयन_करोne(te_data->vअगर, true);
		अवरोध;
	शेष:
		/* should never happen */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	/* we करोn't need it anymore */
	iwl_mvm_te_clear_data(mvm, te_data);
पूर्ण

अटल व्योम iwl_mvm_te_check_trigger(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_समय_event_notअगर *notअगर,
				     काष्ठा iwl_mvm_समय_event_data *te_data)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_समय_event *te_trig;
	पूर्णांक i;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt,
				     ieee80211_vअगर_to_wdev(te_data->vअगर),
				     FW_DBG_TRIGGER_TIME_EVENT);
	अगर (!trig)
		वापस;

	te_trig = (व्योम *)trig->data;

	क्रम (i = 0; i < ARRAY_SIZE(te_trig->समय_events); i++) अणु
		u32 trig_te_id = le32_to_cpu(te_trig->समय_events[i].id);
		u32 trig_action_biपंचांगap =
			le32_to_cpu(te_trig->समय_events[i].action_biपंचांगap);
		u32 trig_status_biपंचांगap =
			le32_to_cpu(te_trig->समय_events[i].status_biपंचांगap);

		अगर (trig_te_id != te_data->id ||
		    !(trig_action_biपंचांगap & le32_to_cpu(notअगर->action)) ||
		    !(trig_status_biपंचांगap & BIT(le32_to_cpu(notअगर->status))))
			जारी;

		iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
					"Time event %d Action 0x%x received status: %d",
					te_data->id,
					le32_to_cpu(notअगर->action),
					le32_to_cpu(notअगर->status));
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Handles a FW notअगरication क्रम an event that is known to the driver.
 *
 * @mvm: the mvm component
 * @te_data: the समय event data
 * @notअगर: the notअगरication data corresponding the समय event data.
 */
अटल व्योम iwl_mvm_te_handle_notअगर(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_mvm_समय_event_data *te_data,
				    काष्ठा iwl_समय_event_notअगर *notअगर)
अणु
	lockdep_निश्चित_held(&mvm->समय_event_lock);

	IWL_DEBUG_TE(mvm, "Handle time event notif - UID = 0x%x action %d\n",
		     le32_to_cpu(notअगर->unique_id),
		     le32_to_cpu(notअगर->action));

	iwl_mvm_te_check_trigger(mvm, notअगर, te_data);

	/*
	 * The FW sends the start/end समय event notअगरications even क्रम events
	 * that it fails to schedule. This is indicated in the status field of
	 * the notअगरication. This happens in हालs that the scheduler cannot
	 * find a schedule that can handle the event (क्रम example requesting a
	 * P2P Device discoveribility, जबतक there are other higher priority
	 * events in the प्रणाली).
	 */
	अगर (!le32_to_cpu(notअगर->status)) अणु
		स्थिर अक्षर *msg;

		अगर (notअगर->action & cpu_to_le32(TE_V2_NOTIF_HOST_EVENT_START))
			msg = "Time Event start notification failure";
		अन्यथा
			msg = "Time Event end notification failure";

		IWL_DEBUG_TE(mvm, "%s\n", msg);

		अगर (iwl_mvm_te_check_disconnect(mvm, te_data->vअगर, msg)) अणु
			iwl_mvm_te_clear_data(mvm, te_data);
			वापस;
		पूर्ण
	पूर्ण

	अगर (le32_to_cpu(notअगर->action) & TE_V2_NOTIF_HOST_EVENT_END) अणु
		IWL_DEBUG_TE(mvm,
			     "TE ended - current time %lu, estimated end %lu\n",
			     jअगरfies, te_data->end_jअगरfies);

		चयन (te_data->vअगर->type) अणु
		हाल NL80211_IFTYPE_P2P_DEVICE:
			ieee80211_reमुख्य_on_channel_expired(mvm->hw);
			set_bit(IWL_MVM_STATUS_NEED_FLUSH_P2P, &mvm->status);
			iwl_mvm_roc_finished(mvm);
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
			/*
			 * If we are चयनing channel, करोn't disconnect
			 * अगर the समय event is alपढ़ोy करोne. Beacons can
			 * be delayed a bit after the चयन.
			 */
			अगर (te_data->id == TE_CHANNEL_SWITCH_PERIOD) अणु
				IWL_DEBUG_TE(mvm,
					     "No beacon heard and the CS time event is over, don't disconnect\n");
				अवरोध;
			पूर्ण

			/*
			 * By now, we should have finished association
			 * and know the dtim period.
			 */
			iwl_mvm_te_check_disconnect(mvm, te_data->vअगर,
				"No beacon heard and the time event is over already...");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		iwl_mvm_te_clear_data(mvm, te_data);
	पूर्ण अन्यथा अगर (le32_to_cpu(notअगर->action) & TE_V2_NOTIF_HOST_EVENT_START) अणु
		te_data->running = true;
		te_data->end_jअगरfies = TU_TO_EXP_TIME(te_data->duration);

		अगर (te_data->vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
			set_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status);
			ieee80211_पढ़ोy_on_channel(mvm->hw);
		पूर्ण अन्यथा अगर (te_data->id == TE_CHANNEL_SWITCH_PERIOD) अणु
			iwl_mvm_te_handle_notअगरy_csa(mvm, te_data, notअगर);
		पूर्ण
	पूर्ण अन्यथा अणु
		IWL_WARN(mvm, "Got TE with unknown action\n");
	पूर्ण
पूर्ण

/*
 * Handle A Aux ROC समय event
 */
अटल पूर्णांक iwl_mvm_aux_roc_te_handle_notअगर(काष्ठा iwl_mvm *mvm,
					   काष्ठा iwl_समय_event_notअगर *notअगर)
अणु
	काष्ठा iwl_mvm_समय_event_data *te_data, *पंचांगp;
	bool aux_roc_te = false;

	list_क्रम_each_entry_safe(te_data, पंचांगp, &mvm->aux_roc_te_list, list) अणु
		अगर (le32_to_cpu(notअगर->unique_id) == te_data->uid) अणु
			aux_roc_te = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!aux_roc_te) /* Not a Aux ROC समय event */
		वापस -EINVAL;

	iwl_mvm_te_check_trigger(mvm, notअगर, te_data);

	IWL_DEBUG_TE(mvm,
		     "Aux ROC time event notification  - UID = 0x%x action %d (error = %d)\n",
		     le32_to_cpu(notअगर->unique_id),
		     le32_to_cpu(notअगर->action), le32_to_cpu(notअगर->status));

	अगर (!le32_to_cpu(notअगर->status) ||
	    le32_to_cpu(notअगर->action) == TE_V2_NOTIF_HOST_EVENT_END) अणु
		/* End TE, notअगरy mac80211 */
		ieee80211_reमुख्य_on_channel_expired(mvm->hw);
		iwl_mvm_roc_finished(mvm); /* flush aux queue */
		list_del(&te_data->list); /* हटाओ from list */
		te_data->running = false;
		te_data->vअगर = शून्य;
		te_data->uid = 0;
		te_data->id = TE_MAX;
	पूर्ण अन्यथा अगर (le32_to_cpu(notअगर->action) == TE_V2_NOTIF_HOST_EVENT_START) अणु
		set_bit(IWL_MVM_STATUS_ROC_AUX_RUNNING, &mvm->status);
		te_data->running = true;
		ieee80211_पढ़ोy_on_channel(mvm->hw); /* Start TE */
	पूर्ण अन्यथा अणु
		IWL_DEBUG_TE(mvm,
			     "ERROR: Unknown Aux ROC Time Event (action = %d)\n",
			     le32_to_cpu(notअगर->action));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * The Rx handler क्रम समय event notअगरications
 */
व्योम iwl_mvm_rx_समय_event_notअगर(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_समय_event_notअगर *notअगर = (व्योम *)pkt->data;
	काष्ठा iwl_mvm_समय_event_data *te_data, *पंचांगp;

	IWL_DEBUG_TE(mvm, "Time event notification - UID = 0x%x action %d\n",
		     le32_to_cpu(notअगर->unique_id),
		     le32_to_cpu(notअगर->action));

	spin_lock_bh(&mvm->समय_event_lock);
	/* This समय event is triggered क्रम Aux ROC request */
	अगर (!iwl_mvm_aux_roc_te_handle_notअगर(mvm, notअगर))
		जाओ unlock;

	list_क्रम_each_entry_safe(te_data, पंचांगp, &mvm->समय_event_list, list) अणु
		अगर (le32_to_cpu(notअगर->unique_id) == te_data->uid)
			iwl_mvm_te_handle_notअगर(mvm, te_data, notअगर);
	पूर्ण
unlock:
	spin_unlock_bh(&mvm->समय_event_lock);
पूर्ण

अटल bool iwl_mvm_te_notअगर(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
			     काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_mvm *mvm =
		container_of(notअगर_रुको, काष्ठा iwl_mvm, notअगर_रुको);
	काष्ठा iwl_mvm_समय_event_data *te_data = data;
	काष्ठा iwl_समय_event_notअगर *resp;
	पूर्णांक resp_len = iwl_rx_packet_payload_len(pkt);

	अगर (WARN_ON(pkt->hdr.cmd != TIME_EVENT_NOTIFICATION))
		वापस true;

	अगर (WARN_ON_ONCE(resp_len != माप(*resp))) अणु
		IWL_ERR(mvm, "Invalid TIME_EVENT_NOTIFICATION response\n");
		वापस true;
	पूर्ण

	resp = (व्योम *)pkt->data;

	/* te_data->uid is alपढ़ोy set in the TIME_EVENT_CMD response */
	अगर (le32_to_cpu(resp->unique_id) != te_data->uid)
		वापस false;

	IWL_DEBUG_TE(mvm, "TIME_EVENT_NOTIFICATION response - UID = 0x%x\n",
		     te_data->uid);
	अगर (!resp->status)
		IWL_ERR(mvm,
			"TIME_EVENT_NOTIFICATION received but not executed\n");

	वापस true;
पूर्ण

अटल bool iwl_mvm_समय_event_response(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
					काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_mvm *mvm =
		container_of(notअगर_रुको, काष्ठा iwl_mvm, notअगर_रुको);
	काष्ठा iwl_mvm_समय_event_data *te_data = data;
	काष्ठा iwl_समय_event_resp *resp;
	पूर्णांक resp_len = iwl_rx_packet_payload_len(pkt);

	अगर (WARN_ON(pkt->hdr.cmd != TIME_EVENT_CMD))
		वापस true;

	अगर (WARN_ON_ONCE(resp_len != माप(*resp))) अणु
		IWL_ERR(mvm, "Invalid TIME_EVENT_CMD response\n");
		वापस true;
	पूर्ण

	resp = (व्योम *)pkt->data;

	/* we should never get a response to another TIME_EVENT_CMD here */
	अगर (WARN_ON_ONCE(le32_to_cpu(resp->id) != te_data->id))
		वापस false;

	te_data->uid = le32_to_cpu(resp->unique_id);
	IWL_DEBUG_TE(mvm, "TIME_EVENT_CMD response - UID = 0x%x\n",
		     te_data->uid);
	वापस true;
पूर्ण

अटल पूर्णांक iwl_mvm_समय_event_send_add(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा iwl_mvm_समय_event_data *te_data,
				       काष्ठा iwl_समय_event_cmd *te_cmd)
अणु
	अटल स्थिर u16 समय_event_response[] = अणु TIME_EVENT_CMD पूर्ण;
	काष्ठा iwl_notअगरication_रुको रुको_समय_event;
	पूर्णांक ret;

	lockdep_निश्चित_held(&mvm->mutex);

	IWL_DEBUG_TE(mvm, "Add new TE, duration %d TU\n",
		     le32_to_cpu(te_cmd->duration));

	spin_lock_bh(&mvm->समय_event_lock);
	अगर (WARN_ON(te_data->id != TE_MAX)) अणु
		spin_unlock_bh(&mvm->समय_event_lock);
		वापस -EIO;
	पूर्ण
	te_data->vअगर = vअगर;
	te_data->duration = le32_to_cpu(te_cmd->duration);
	te_data->id = le32_to_cpu(te_cmd->id);
	list_add_tail(&te_data->list, &mvm->समय_event_list);
	spin_unlock_bh(&mvm->समय_event_lock);

	/*
	 * Use a notअगरication रुको, which really just processes the
	 * command response and करोesn't रुको क्रम anything, in order
	 * to be able to process the response and get the UID inside
	 * the RX path. Using CMD_WANT_SKB करोesn't work because it
	 * stores the buffer and then wakes up this thपढ़ो, by which
	 * समय another notअगरication (that the समय event started)
	 * might alपढ़ोy be processed unsuccessfully.
	 */
	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको, &रुको_समय_event,
				   समय_event_response,
				   ARRAY_SIZE(समय_event_response),
				   iwl_mvm_समय_event_response, te_data);

	ret = iwl_mvm_send_cmd_pdu(mvm, TIME_EVENT_CMD, 0,
					    माप(*te_cmd), te_cmd);
	अगर (ret) अणु
		IWL_ERR(mvm, "Couldn't send TIME_EVENT_CMD: %d\n", ret);
		iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &रुको_समय_event);
		जाओ out_clear_te;
	पूर्ण

	/* No need to रुको क्रम anything, so just pass 1 (0 isn't valid) */
	ret = iwl_रुको_notअगरication(&mvm->notअगर_रुको, &रुको_समय_event, 1);
	/* should never fail */
	WARN_ON_ONCE(ret);

	अगर (ret) अणु
 out_clear_te:
		spin_lock_bh(&mvm->समय_event_lock);
		iwl_mvm_te_clear_data(mvm, te_data);
		spin_unlock_bh(&mvm->समय_event_lock);
	पूर्ण
	वापस ret;
पूर्ण

व्योम iwl_mvm_protect_session(काष्ठा iwl_mvm *mvm,
			     काष्ठा ieee80211_vअगर *vअगर,
			     u32 duration, u32 min_duration,
			     u32 max_delay, bool रुको_क्रम_notअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_समय_event_data *te_data = &mvmvअगर->समय_event_data;
	स्थिर u16 te_notअगर_response[] = अणु TIME_EVENT_NOTIFICATION पूर्ण;
	काष्ठा iwl_notअगरication_रुको रुको_te_notअगर;
	काष्ठा iwl_समय_event_cmd समय_cmd = अणुपूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (te_data->running &&
	    समय_after(te_data->end_jअगरfies, TU_TO_EXP_TIME(min_duration))) अणु
		IWL_DEBUG_TE(mvm, "We have enough time in the current TE: %u\n",
			     jअगरfies_to_msecs(te_data->end_jअगरfies - jअगरfies));
		वापस;
	पूर्ण

	अगर (te_data->running) अणु
		IWL_DEBUG_TE(mvm, "extend 0x%x: only %u ms left\n",
			     te_data->uid,
			     jअगरfies_to_msecs(te_data->end_jअगरfies - jअगरfies));
		/*
		 * we करोn't have enough समय
		 * cancel the current TE and issue a new one
		 * Of course it would be better to हटाओ the old one only
		 * when the new one is added, but we करोn't care अगर we are off
		 * channel क्रम a bit. All we need to करो, is not to वापस
		 * beक्रमe we actually begin to be on the channel.
		 */
		iwl_mvm_stop_session_protection(mvm, vअगर);
	पूर्ण

	समय_cmd.action = cpu_to_le32(FW_CTXT_ACTION_ADD);
	समय_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color));
	समय_cmd.id = cpu_to_le32(TE_BSS_STA_AGGRESSIVE_ASSOC);

	समय_cmd.apply_समय = cpu_to_le32(0);

	समय_cmd.max_frags = TE_V2_FRAG_NONE;
	समय_cmd.max_delay = cpu_to_le32(max_delay);
	/* TODO: why करो we need to पूर्णांकerval = bi अगर it is not periodic? */
	समय_cmd.पूर्णांकerval = cpu_to_le32(1);
	समय_cmd.duration = cpu_to_le32(duration);
	समय_cmd.repeat = 1;
	समय_cmd.policy = cpu_to_le16(TE_V2_NOTIF_HOST_EVENT_START |
				      TE_V2_NOTIF_HOST_EVENT_END |
				      TE_V2_START_IMMEDIATELY);

	अगर (!रुको_क्रम_notअगर) अणु
		iwl_mvm_समय_event_send_add(mvm, vअगर, te_data, &समय_cmd);
		वापस;
	पूर्ण

	/*
	 * Create notअगरication_रुको क्रम the TIME_EVENT_NOTIFICATION to use
	 * right after we send the समय event
	 */
	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको, &रुको_te_notअगर,
				   te_notअगर_response,
				   ARRAY_SIZE(te_notअगर_response),
				   iwl_mvm_te_notअगर, te_data);

	/* If TE was sent OK - रुको क्रम the notअगरication that started */
	अगर (iwl_mvm_समय_event_send_add(mvm, vअगर, te_data, &समय_cmd)) अणु
		IWL_ERR(mvm, "Failed to add TE to protect session\n");
		iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &रुको_te_notअगर);
	पूर्ण अन्यथा अगर (iwl_रुको_notअगरication(&mvm->notअगर_रुको, &रुको_te_notअगर,
					 TU_TO_JIFFIES(max_delay))) अणु
		IWL_ERR(mvm, "Failed to protect session until TE\n");
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_cancel_session_protection(काष्ठा iwl_mvm *mvm,
					      काष्ठा iwl_mvm_vअगर *mvmvअगर)
अणु
	काष्ठा iwl_mvm_session_prot_cmd cmd = अणु
		.id_and_color =
			cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							mvmvअगर->color)),
		.action = cpu_to_le32(FW_CTXT_ACTION_REMOVE),
		.conf_id = cpu_to_le32(mvmvअगर->समय_event_data.id),
	पूर्ण;
	पूर्णांक ret;

	ret = iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(SESSION_PROTECTION_CMD,
						   MAC_CONF_GROUP, 0),
				   0, माप(cmd), &cmd);
	अगर (ret)
		IWL_ERR(mvm,
			"Couldn't send the SESSION_PROTECTION_CMD: %d\n", ret);
पूर्ण

अटल bool __iwl_mvm_हटाओ_समय_event(काष्ठा iwl_mvm *mvm,
					काष्ठा iwl_mvm_समय_event_data *te_data,
					u32 *uid)
अणु
	u32 id;
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(te_data->vअगर);

	/*
	 * It is possible that by the समय we got to this poपूर्णांक the समय
	 * event was alपढ़ोy हटाओd.
	 */
	spin_lock_bh(&mvm->समय_event_lock);

	/* Save समय event uid beक्रमe clearing its data */
	*uid = te_data->uid;
	id = te_data->id;

	/*
	 * The clear_data function handles समय events that were alपढ़ोy हटाओd
	 */
	iwl_mvm_te_clear_data(mvm, te_data);
	spin_unlock_bh(&mvm->समय_event_lock);

	/* When session protection is supported, the te_data->id field
	 * is reused to save session protection's configuration.
	 */
	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_SESSION_PROT_CMD)) अणु
		अगर (mvmvअगर && id < SESSION_PROTECT_CONF_MAX_ID) अणु
			/* Session protection is still ongoing. Cancel it */
			iwl_mvm_cancel_session_protection(mvm, mvmvअगर);
			अगर (te_data->vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
				set_bit(IWL_MVM_STATUS_NEED_FLUSH_P2P, &mvm->status);
				iwl_mvm_roc_finished(mvm);
			पूर्ण
		पूर्ण
		वापस false;
	पूर्ण अन्यथा अणु
		/* It is possible that by the समय we try to हटाओ it, the
		 * समय event has alपढ़ोy ended and हटाओd. In such a हाल
		 * there is no need to send a removal command.
		 */
		अगर (id == TE_MAX) अणु
			IWL_DEBUG_TE(mvm, "TE 0x%x has already ended\n", *uid);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/*
 * Explicit request to हटाओ a aux roc समय event. The removal of a समय
 * event needs to be synchronized with the flow of a समय event's end
 * notअगरication, which also हटाओs the समय event from the op mode
 * data काष्ठाures.
 */
अटल व्योम iwl_mvm_हटाओ_aux_roc_te(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_mvm_vअगर *mvmvअगर,
				      काष्ठा iwl_mvm_समय_event_data *te_data)
अणु
	काष्ठा iwl_hs20_roc_req aux_cmd = अणुपूर्ण;
	u16 len = माप(aux_cmd) - iwl_mvm_chan_info_padding(mvm);

	u32 uid;
	पूर्णांक ret;

	अगर (!__iwl_mvm_हटाओ_समय_event(mvm, te_data, &uid))
		वापस;

	aux_cmd.event_unique_id = cpu_to_le32(uid);
	aux_cmd.action = cpu_to_le32(FW_CTXT_ACTION_REMOVE);
	aux_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color));
	IWL_DEBUG_TE(mvm, "Removing BSS AUX ROC TE 0x%x\n",
		     le32_to_cpu(aux_cmd.event_unique_id));
	ret = iwl_mvm_send_cmd_pdu(mvm, HOT_SPOT_CMD, 0,
				   len, &aux_cmd);

	अगर (WARN_ON(ret))
		वापस;
पूर्ण

/*
 * Explicit request to हटाओ a समय event. The removal of a समय event needs to
 * be synchronized with the flow of a समय event's end notअगरication, which also
 * हटाओs the समय event from the op mode data काष्ठाures.
 */
व्योम iwl_mvm_हटाओ_समय_event(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_mvm_vअगर *mvmvअगर,
			       काष्ठा iwl_mvm_समय_event_data *te_data)
अणु
	काष्ठा iwl_समय_event_cmd समय_cmd = अणुपूर्ण;
	u32 uid;
	पूर्णांक ret;

	अगर (!__iwl_mvm_हटाओ_समय_event(mvm, te_data, &uid))
		वापस;

	/* When we हटाओ a TE, the UID is to be set in the id field */
	समय_cmd.id = cpu_to_le32(uid);
	समय_cmd.action = cpu_to_le32(FW_CTXT_ACTION_REMOVE);
	समय_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color));

	IWL_DEBUG_TE(mvm, "Removing TE 0x%x\n", le32_to_cpu(समय_cmd.id));
	ret = iwl_mvm_send_cmd_pdu(mvm, TIME_EVENT_CMD, 0,
				   माप(समय_cmd), &समय_cmd);
	अगर (ret)
		IWL_ERR(mvm, "Couldn't remove the time event\n");
पूर्ण

/*
 * When the firmware supports the session protection API,
 * this is not needed since it'll स्वतःmatically हटाओ the
 * session protection after association + beacon reception.
 */
व्योम iwl_mvm_stop_session_protection(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_समय_event_data *te_data = &mvmvअगर->समय_event_data;
	u32 id;

	lockdep_निश्चित_held(&mvm->mutex);

	spin_lock_bh(&mvm->समय_event_lock);
	id = te_data->id;
	spin_unlock_bh(&mvm->समय_event_lock);

	अगर (id != TE_BSS_STA_AGGRESSIVE_ASSOC) अणु
		IWL_DEBUG_TE(mvm,
			     "don't remove TE with id=%u (not session protection)\n",
			     id);
		वापस;
	पूर्ण

	iwl_mvm_हटाओ_समय_event(mvm, mvmvअगर, te_data);
पूर्ण

व्योम iwl_mvm_rx_session_protect_notअगर(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mvm_session_prot_notअगर *notअगर = (व्योम *)pkt->data;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा iwl_mvm_vअगर *mvmvअगर;

	rcu_पढ़ो_lock();
	vअगर = iwl_mvm_rcu_dereference_vअगर_id(mvm, le32_to_cpu(notअगर->mac_id),
					     true);

	अगर (!vअगर)
		जाओ out_unlock;

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

	/* The vअगर is not a P2P_DEVICE, मुख्यtain its समय_event_data */
	अगर (vअगर->type != NL80211_IFTYPE_P2P_DEVICE) अणु
		काष्ठा iwl_mvm_समय_event_data *te_data =
			&mvmvअगर->समय_event_data;

		अगर (!le32_to_cpu(notअगर->status)) अणु
			iwl_mvm_te_check_disconnect(mvm, vअगर,
						    "Session protection failure");
			spin_lock_bh(&mvm->समय_event_lock);
			iwl_mvm_te_clear_data(mvm, te_data);
			spin_unlock_bh(&mvm->समय_event_lock);
		पूर्ण

		अगर (le32_to_cpu(notअगर->start)) अणु
			spin_lock_bh(&mvm->समय_event_lock);
			te_data->running = le32_to_cpu(notअगर->start);
			te_data->end_jअगरfies =
				TU_TO_EXP_TIME(te_data->duration);
			spin_unlock_bh(&mvm->समय_event_lock);
		पूर्ण अन्यथा अणु
			/*
			 * By now, we should have finished association
			 * and know the dtim period.
			 */
			iwl_mvm_te_check_disconnect(mvm, vअगर,
						    "No beacon heard and the session protection is over already...");
			spin_lock_bh(&mvm->समय_event_lock);
			iwl_mvm_te_clear_data(mvm, te_data);
			spin_unlock_bh(&mvm->समय_event_lock);
		पूर्ण

		जाओ out_unlock;
	पूर्ण

	अगर (!le32_to_cpu(notअगर->status) || !le32_to_cpu(notअगर->start)) अणु
		/* End TE, notअगरy mac80211 */
		mvmvअगर->समय_event_data.id = SESSION_PROTECT_CONF_MAX_ID;
		ieee80211_reमुख्य_on_channel_expired(mvm->hw);
		set_bit(IWL_MVM_STATUS_NEED_FLUSH_P2P, &mvm->status);
		iwl_mvm_roc_finished(mvm);
	पूर्ण अन्यथा अगर (le32_to_cpu(notअगर->start)) अणु
		अगर (WARN_ON(mvmvअगर->समय_event_data.id !=
				le32_to_cpu(notअगर->conf_id)))
			जाओ out_unlock;
		set_bit(IWL_MVM_STATUS_ROC_RUNNING, &mvm->status);
		ieee80211_पढ़ोy_on_channel(mvm->hw); /* Start TE */
	पूर्ण

 out_unlock:
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक
iwl_mvm_start_p2p_roc_session_protection(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर,
					 पूर्णांक duration,
					 क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_session_prot_cmd cmd = अणु
		.id_and_color =
			cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							mvmvअगर->color)),
		.action = cpu_to_le32(FW_CTXT_ACTION_ADD),
		.duration_tu = cpu_to_le32(MSEC_TO_TU(duration)),
	पूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	/* The समय_event_data.id field is reused to save session
	 * protection's configuration.
	 */
	चयन (type) अणु
	हाल IEEE80211_ROC_TYPE_NORMAL:
		mvmvअगर->समय_event_data.id =
			SESSION_PROTECT_CONF_P2P_DEVICE_DISCOV;
		अवरोध;
	हाल IEEE80211_ROC_TYPE_MGMT_TX:
		mvmvअगर->समय_event_data.id =
			SESSION_PROTECT_CONF_P2P_GO_NEGOTIATION;
		अवरोध;
	शेष:
		WARN_ONCE(1, "Got an invalid ROC type\n");
		वापस -EINVAL;
	पूर्ण

	cmd.conf_id = cpu_to_le32(mvmvअगर->समय_event_data.id);
	वापस iwl_mvm_send_cmd_pdu(mvm, iwl_cmd_id(SESSION_PROTECTION_CMD,
						    MAC_CONF_GROUP, 0),
				    0, माप(cmd), &cmd);
पूर्ण

पूर्णांक iwl_mvm_start_p2p_roc(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			  पूर्णांक duration, क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_समय_event_data *te_data = &mvmvअगर->समय_event_data;
	काष्ठा iwl_समय_event_cmd समय_cmd = अणुपूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);
	अगर (te_data->running) अणु
		IWL_WARN(mvm, "P2P_DEVICE remain on channel already running\n");
		वापस -EBUSY;
	पूर्ण

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_SESSION_PROT_CMD))
		वापस iwl_mvm_start_p2p_roc_session_protection(mvm, vअगर,
								duration,
								type);

	समय_cmd.action = cpu_to_le32(FW_CTXT_ACTION_ADD);
	समय_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color));

	चयन (type) अणु
	हाल IEEE80211_ROC_TYPE_NORMAL:
		समय_cmd.id = cpu_to_le32(IWL_MVM_ROC_TE_TYPE_NORMAL);
		अवरोध;
	हाल IEEE80211_ROC_TYPE_MGMT_TX:
		समय_cmd.id = cpu_to_le32(IWL_MVM_ROC_TE_TYPE_MGMT_TX);
		अवरोध;
	शेष:
		WARN_ONCE(1, "Got an invalid ROC type\n");
		वापस -EINVAL;
	पूर्ण

	समय_cmd.apply_समय = cpu_to_le32(0);
	समय_cmd.पूर्णांकerval = cpu_to_le32(1);

	/*
	 * The P2P Device TEs can have lower priority than other events
	 * that are being scheduled by the driver/fw, and thus it might not be
	 * scheduled. To improve the chances of it being scheduled, allow them
	 * to be fragmented, and in addition allow them to be delayed.
	 */
	समय_cmd.max_frags = min(MSEC_TO_TU(duration)/50, TE_V2_FRAG_ENDLESS);
	समय_cmd.max_delay = cpu_to_le32(MSEC_TO_TU(duration/2));
	समय_cmd.duration = cpu_to_le32(MSEC_TO_TU(duration));
	समय_cmd.repeat = 1;
	समय_cmd.policy = cpu_to_le16(TE_V2_NOTIF_HOST_EVENT_START |
				      TE_V2_NOTIF_HOST_EVENT_END |
				      TE_V2_START_IMMEDIATELY);

	वापस iwl_mvm_समय_event_send_add(mvm, vअगर, te_data, &समय_cmd);
पूर्ण

अटल काष्ठा iwl_mvm_समय_event_data *iwl_mvm_get_roc_te(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_mvm_समय_event_data *te_data;

	lockdep_निश्चित_held(&mvm->mutex);

	spin_lock_bh(&mvm->समय_event_lock);

	/*
	 * Iterate over the list of समय events and find the समय event that is
	 * associated with a P2P_DEVICE पूर्णांकerface.
	 * This assumes that a P2P_DEVICE पूर्णांकerface can have only a single समय
	 * event at any given समय and this समय event coresponds to a ROC
	 * request
	 */
	list_क्रम_each_entry(te_data, &mvm->समय_event_list, list) अणु
		अगर (te_data->vअगर->type == NL80211_IFTYPE_P2P_DEVICE)
			जाओ out;
	पूर्ण

	/* There can only be at most one AUX ROC समय event, we just use the
	 * list to simplअगरy/unअगरy code. Remove it अगर it exists.
	 */
	te_data = list_first_entry_or_null(&mvm->aux_roc_te_list,
					   काष्ठा iwl_mvm_समय_event_data,
					   list);
out:
	spin_unlock_bh(&mvm->समय_event_lock);
	वापस te_data;
पूर्ण

व्योम iwl_mvm_cleanup_roc_te(काष्ठा iwl_mvm *mvm)
अणु
	काष्ठा iwl_mvm_समय_event_data *te_data;
	u32 uid;

	te_data = iwl_mvm_get_roc_te(mvm);
	अगर (te_data)
		__iwl_mvm_हटाओ_समय_event(mvm, te_data, &uid);
पूर्ण

व्योम iwl_mvm_stop_roc(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	काष्ठा iwl_mvm_समय_event_data *te_data;

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_SESSION_PROT_CMD)) अणु
		mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);

		अगर (vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
			iwl_mvm_cancel_session_protection(mvm, mvmvअगर);
			set_bit(IWL_MVM_STATUS_NEED_FLUSH_P2P, &mvm->status);
		पूर्ण अन्यथा अणु
			iwl_mvm_हटाओ_aux_roc_te(mvm, mvmvअगर,
						  &mvmvअगर->समय_event_data);
		पूर्ण

		iwl_mvm_roc_finished(mvm);

		वापस;
	पूर्ण

	te_data = iwl_mvm_get_roc_te(mvm);
	अगर (!te_data) अणु
		IWL_WARN(mvm, "No remain on channel event\n");
		वापस;
	पूर्ण

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(te_data->vअगर);

	अगर (te_data->vअगर->type == NL80211_IFTYPE_P2P_DEVICE) अणु
		iwl_mvm_हटाओ_समय_event(mvm, mvmvअगर, te_data);
		set_bit(IWL_MVM_STATUS_NEED_FLUSH_P2P, &mvm->status);
	पूर्ण अन्यथा अणु
		iwl_mvm_हटाओ_aux_roc_te(mvm, mvmvअगर, te_data);
	पूर्ण

	iwl_mvm_roc_finished(mvm);
पूर्ण

व्योम iwl_mvm_हटाओ_csa_period(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_समय_event_data *te_data = &mvmvअगर->समय_event_data;
	u32 id;

	lockdep_निश्चित_held(&mvm->mutex);

	spin_lock_bh(&mvm->समय_event_lock);
	id = te_data->id;
	spin_unlock_bh(&mvm->समय_event_lock);

	अगर (id != TE_CHANNEL_SWITCH_PERIOD)
		वापस;

	iwl_mvm_हटाओ_समय_event(mvm, mvmvअगर, te_data);
पूर्ण

पूर्णांक iwl_mvm_schedule_csa_period(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_vअगर *vअगर,
				u32 duration, u32 apply_समय)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_समय_event_data *te_data = &mvmvअगर->समय_event_data;
	काष्ठा iwl_समय_event_cmd समय_cmd = अणुपूर्ण;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (te_data->running) अणु
		u32 id;

		spin_lock_bh(&mvm->समय_event_lock);
		id = te_data->id;
		spin_unlock_bh(&mvm->समय_event_lock);

		अगर (id == TE_CHANNEL_SWITCH_PERIOD) अणु
			IWL_DEBUG_TE(mvm, "CS period is already scheduled\n");
			वापस -EBUSY;
		पूर्ण

		/*
		 * Remove the session protection समय event to allow the
		 * channel चयन. If we got here, we just heard a beacon so
		 * the session protection is not needed anymore anyway.
		 */
		iwl_mvm_हटाओ_समय_event(mvm, mvmvअगर, te_data);
	पूर्ण

	समय_cmd.action = cpu_to_le32(FW_CTXT_ACTION_ADD);
	समय_cmd.id_and_color =
		cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id, mvmvअगर->color));
	समय_cmd.id = cpu_to_le32(TE_CHANNEL_SWITCH_PERIOD);
	समय_cmd.apply_समय = cpu_to_le32(apply_समय);
	समय_cmd.max_frags = TE_V2_FRAG_NONE;
	समय_cmd.duration = cpu_to_le32(duration);
	समय_cmd.repeat = 1;
	समय_cmd.पूर्णांकerval = cpu_to_le32(1);
	समय_cmd.policy = cpu_to_le16(TE_V2_NOTIF_HOST_EVENT_START |
				      TE_V2_ABSENCE);
	अगर (!apply_समय)
		समय_cmd.policy |= cpu_to_le16(TE_V2_START_IMMEDIATELY);

	वापस iwl_mvm_समय_event_send_add(mvm, vअगर, te_data, &समय_cmd);
पूर्ण

अटल bool iwl_mvm_session_prot_notअगर(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
				       काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_mvm *mvm =
		container_of(notअगर_रुको, काष्ठा iwl_mvm, notअगर_रुको);
	काष्ठा iwl_mvm_session_prot_notअगर *resp;
	पूर्णांक resp_len = iwl_rx_packet_payload_len(pkt);

	अगर (WARN_ON(pkt->hdr.cmd != SESSION_PROTECTION_NOTIF ||
		    pkt->hdr.group_id != MAC_CONF_GROUP))
		वापस true;

	अगर (WARN_ON_ONCE(resp_len != माप(*resp))) अणु
		IWL_ERR(mvm, "Invalid SESSION_PROTECTION_NOTIF response\n");
		वापस true;
	पूर्ण

	resp = (व्योम *)pkt->data;

	अगर (!resp->status)
		IWL_ERR(mvm,
			"TIME_EVENT_NOTIFICATION received but not executed\n");

	वापस true;
पूर्ण

व्योम iwl_mvm_schedule_session_protection(काष्ठा iwl_mvm *mvm,
					 काष्ठा ieee80211_vअगर *vअगर,
					 u32 duration, u32 min_duration,
					 bool रुको_क्रम_notअगर)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	काष्ठा iwl_mvm_समय_event_data *te_data = &mvmvअगर->समय_event_data;
	स्थिर u16 notअगर[] = अणु iwl_cmd_id(SESSION_PROTECTION_NOTIF,
					 MAC_CONF_GROUP, 0) पूर्ण;
	काष्ठा iwl_notअगरication_रुको रुको_notअगर;
	काष्ठा iwl_mvm_session_prot_cmd cmd = अणु
		.id_and_color =
			cpu_to_le32(FW_CMD_ID_AND_COLOR(mvmvअगर->id,
							mvmvअगर->color)),
		.action = cpu_to_le32(FW_CTXT_ACTION_ADD),
		.duration_tu = cpu_to_le32(MSEC_TO_TU(duration)),
	पूर्ण;

	/* The समय_event_data.id field is reused to save session
	 * protection's configuration.
	 */
	mvmvअगर->समय_event_data.id = SESSION_PROTECT_CONF_ASSOC;
	cmd.conf_id = cpu_to_le32(mvmvअगर->समय_event_data.id);

	lockdep_निश्चित_held(&mvm->mutex);

	spin_lock_bh(&mvm->समय_event_lock);
	अगर (te_data->running &&
	    समय_after(te_data->end_jअगरfies, TU_TO_EXP_TIME(min_duration))) अणु
		IWL_DEBUG_TE(mvm, "We have enough time in the current TE: %u\n",
			     jअगरfies_to_msecs(te_data->end_jअगरfies - jअगरfies));
		spin_unlock_bh(&mvm->समय_event_lock);

		वापस;
	पूर्ण

	iwl_mvm_te_clear_data(mvm, te_data);
	te_data->duration = le32_to_cpu(cmd.duration_tu);
	spin_unlock_bh(&mvm->समय_event_lock);

	IWL_DEBUG_TE(mvm, "Add new session protection, duration %d TU\n",
		     le32_to_cpu(cmd.duration_tu));

	अगर (!रुको_क्रम_notअगर) अणु
		अगर (iwl_mvm_send_cmd_pdu(mvm,
					 iwl_cmd_id(SESSION_PROTECTION_CMD,
						    MAC_CONF_GROUP, 0),
					 0, माप(cmd), &cmd)) अणु
			IWL_ERR(mvm,
				"Couldn't send the SESSION_PROTECTION_CMD\n");
			spin_lock_bh(&mvm->समय_event_lock);
			iwl_mvm_te_clear_data(mvm, te_data);
			spin_unlock_bh(&mvm->समय_event_lock);
		पूर्ण

		वापस;
	पूर्ण

	iwl_init_notअगरication_रुको(&mvm->notअगर_रुको, &रुको_notअगर,
				   notअगर, ARRAY_SIZE(notअगर),
				   iwl_mvm_session_prot_notअगर, शून्य);

	अगर (iwl_mvm_send_cmd_pdu(mvm,
				 iwl_cmd_id(SESSION_PROTECTION_CMD,
					    MAC_CONF_GROUP, 0),
				 0, माप(cmd), &cmd)) अणु
		IWL_ERR(mvm,
			"Couldn't send the SESSION_PROTECTION_CMD\n");
		iwl_हटाओ_notअगरication(&mvm->notअगर_रुको, &रुको_notअगर);
	पूर्ण अन्यथा अगर (iwl_रुको_notअगरication(&mvm->notअगर_रुको, &रुको_notअगर,
					 TU_TO_JIFFIES(100))) अणु
		IWL_ERR(mvm,
			"Failed to protect session until session protection\n");
	पूर्ण
पूर्ण
