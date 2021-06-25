<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "hci: %s: " fmt, __func__

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>

#समावेश <net/nfc/nfc.h>
#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>

#समावेश "hci.h"

/* Largest headroom needed क्रम outgoing HCI commands */
#घोषणा HCI_CMDS_HEADROOM 1

पूर्णांक nfc_hci_result_to_त्रुटि_सं(u8 result)
अणु
	चयन (result) अणु
	हाल NFC_HCI_ANY_OK:
		वापस 0;
	हाल NFC_HCI_ANY_E_REG_PAR_UNKNOWN:
		वापस -EOPNOTSUPP;
	हाल NFC_HCI_ANY_E_TIMEOUT:
		वापस -ETIME;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nfc_hci_result_to_त्रुटि_सं);

व्योम nfc_hci_reset_pipes(काष्ठा nfc_hci_dev *hdev)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < NFC_HCI_MAX_PIPES; i++) अणु
		hdev->pipes[i].gate = NFC_HCI_INVALID_GATE;
		hdev->pipes[i].dest_host = NFC_HCI_INVALID_HOST;
	पूर्ण
	स_रखो(hdev->gate2pipe, NFC_HCI_INVALID_PIPE, माप(hdev->gate2pipe));
पूर्ण
EXPORT_SYMBOL(nfc_hci_reset_pipes);

व्योम nfc_hci_reset_pipes_per_host(काष्ठा nfc_hci_dev *hdev, u8 host)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < NFC_HCI_MAX_PIPES; i++) अणु
		अगर (hdev->pipes[i].dest_host != host)
			जारी;

		hdev->pipes[i].gate = NFC_HCI_INVALID_GATE;
		hdev->pipes[i].dest_host = NFC_HCI_INVALID_HOST;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nfc_hci_reset_pipes_per_host);

अटल व्योम nfc_hci_msg_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfc_hci_dev *hdev = container_of(work, काष्ठा nfc_hci_dev,
						msg_tx_work);
	काष्ठा hci_msg *msg;
	काष्ठा sk_buff *skb;
	पूर्णांक r = 0;

	mutex_lock(&hdev->msg_tx_mutex);
	अगर (hdev->shutting_करोwn)
		जाओ निकास;

	अगर (hdev->cmd_pending_msg) अणु
		अगर (समयr_pending(&hdev->cmd_समयr) == 0) अणु
			अगर (hdev->cmd_pending_msg->cb)
				hdev->cmd_pending_msg->cb(hdev->
							  cmd_pending_msg->
							  cb_context,
							  शून्य,
							  -ETIME);
			kमुक्त(hdev->cmd_pending_msg);
			hdev->cmd_pending_msg = शून्य;
		पूर्ण अन्यथा अणु
			जाओ निकास;
		पूर्ण
	पूर्ण

next_msg:
	अगर (list_empty(&hdev->msg_tx_queue))
		जाओ निकास;

	msg = list_first_entry(&hdev->msg_tx_queue, काष्ठा hci_msg, msg_l);
	list_del(&msg->msg_l);

	pr_debug("msg_tx_queue has a cmd to send\n");
	जबतक ((skb = skb_dequeue(&msg->msg_frags)) != शून्य) अणु
		r = nfc_llc_xmit_from_hci(hdev->llc, skb);
		अगर (r < 0) अणु
			kमुक्त_skb(skb);
			skb_queue_purge(&msg->msg_frags);
			अगर (msg->cb)
				msg->cb(msg->cb_context, शून्य, r);
			kमुक्त(msg);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (r)
		जाओ next_msg;

	अगर (msg->रुको_response == false) अणु
		kमुक्त(msg);
		जाओ next_msg;
	पूर्ण

	hdev->cmd_pending_msg = msg;
	mod_समयr(&hdev->cmd_समयr, jअगरfies +
		  msecs_to_jअगरfies(hdev->cmd_pending_msg->completion_delay));

निकास:
	mutex_unlock(&hdev->msg_tx_mutex);
पूर्ण

अटल व्योम nfc_hci_msg_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfc_hci_dev *hdev = container_of(work, काष्ठा nfc_hci_dev,
						msg_rx_work);
	काष्ठा sk_buff *skb;
	काष्ठा hcp_message *message;
	u8 pipe;
	u8 type;
	u8 inकाष्ठाion;

	जबतक ((skb = skb_dequeue(&hdev->msg_rx_queue)) != शून्य) अणु
		pipe = skb->data[0];
		skb_pull(skb, NFC_HCI_HCP_PACKET_HEADER_LEN);
		message = (काष्ठा hcp_message *)skb->data;
		type = HCP_MSG_GET_TYPE(message->header);
		inकाष्ठाion = HCP_MSG_GET_CMD(message->header);
		skb_pull(skb, NFC_HCI_HCP_MESSAGE_HEADER_LEN);

		nfc_hci_hcp_message_rx(hdev, pipe, type, inकाष्ठाion, skb);
	पूर्ण
पूर्ण

अटल व्योम __nfc_hci_cmd_completion(काष्ठा nfc_hci_dev *hdev, पूर्णांक err,
				     काष्ठा sk_buff *skb)
अणु
	del_समयr_sync(&hdev->cmd_समयr);

	अगर (hdev->cmd_pending_msg->cb)
		hdev->cmd_pending_msg->cb(hdev->cmd_pending_msg->cb_context,
					  skb, err);
	अन्यथा
		kमुक्त_skb(skb);

	kमुक्त(hdev->cmd_pending_msg);
	hdev->cmd_pending_msg = शून्य;

	schedule_work(&hdev->msg_tx_work);
पूर्ण

व्योम nfc_hci_resp_received(काष्ठा nfc_hci_dev *hdev, u8 result,
			   काष्ठा sk_buff *skb)
अणु
	mutex_lock(&hdev->msg_tx_mutex);

	अगर (hdev->cmd_pending_msg == शून्य) अणु
		kमुक्त_skb(skb);
		जाओ निकास;
	पूर्ण

	__nfc_hci_cmd_completion(hdev, nfc_hci_result_to_त्रुटि_सं(result), skb);

निकास:
	mutex_unlock(&hdev->msg_tx_mutex);
पूर्ण

व्योम nfc_hci_cmd_received(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			  काष्ठा sk_buff *skb)
अणु
	u8 status = NFC_HCI_ANY_OK;
	काष्ठा hci_create_pipe_resp *create_info;
	काष्ठा hci_delete_pipe_noti *delete_info;
	काष्ठा hci_all_pipe_cleared_noti *cleared_info;
	u8 gate;

	pr_debug("from pipe %x cmd %x\n", pipe, cmd);

	अगर (pipe >= NFC_HCI_MAX_PIPES) अणु
		status = NFC_HCI_ANY_E_NOK;
		जाओ निकास;
	पूर्ण

	gate = hdev->pipes[pipe].gate;

	चयन (cmd) अणु
	हाल NFC_HCI_ADM_NOTIFY_PIPE_CREATED:
		अगर (skb->len != 5) अणु
			status = NFC_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण
		create_info = (काष्ठा hci_create_pipe_resp *)skb->data;

		अगर (create_info->pipe >= NFC_HCI_MAX_PIPES) अणु
			status = NFC_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण

		/* Save the new created pipe and bind with local gate,
		 * the description क्रम skb->data[3] is destination gate id
		 * but since we received this cmd from host controller, we
		 * are the destination and it is our local gate
		 */
		hdev->gate2pipe[create_info->dest_gate] = create_info->pipe;
		hdev->pipes[create_info->pipe].gate = create_info->dest_gate;
		hdev->pipes[create_info->pipe].dest_host =
							create_info->src_host;
		अवरोध;
	हाल NFC_HCI_ANY_OPEN_PIPE:
		अगर (gate == NFC_HCI_INVALID_GATE) अणु
			status = NFC_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण
		अवरोध;
	हाल NFC_HCI_ADM_NOTIFY_PIPE_DELETED:
		अगर (skb->len != 1) अणु
			status = NFC_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण
		delete_info = (काष्ठा hci_delete_pipe_noti *)skb->data;

		अगर (delete_info->pipe >= NFC_HCI_MAX_PIPES) अणु
			status = NFC_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण

		hdev->pipes[delete_info->pipe].gate = NFC_HCI_INVALID_GATE;
		hdev->pipes[delete_info->pipe].dest_host = NFC_HCI_INVALID_HOST;
		अवरोध;
	हाल NFC_HCI_ADM_NOTIFY_ALL_PIPE_CLEARED:
		अगर (skb->len != 1) अणु
			status = NFC_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण
		cleared_info = (काष्ठा hci_all_pipe_cleared_noti *)skb->data;

		nfc_hci_reset_pipes_per_host(hdev, cleared_info->host);
		अवरोध;
	शेष:
		pr_info("Discarded unknown cmd %x to gate %x\n", cmd, gate);
		अवरोध;
	पूर्ण

	अगर (hdev->ops->cmd_received)
		hdev->ops->cmd_received(hdev, pipe, cmd, skb);

निकास:
	nfc_hci_hcp_message_tx(hdev, pipe, NFC_HCI_HCP_RESPONSE,
			       status, शून्य, 0, शून्य, शून्य, 0);

	kमुक्त_skb(skb);
पूर्ण

u32 nfc_hci_sak_to_protocol(u8 sak)
अणु
	चयन (NFC_HCI_TYPE_A_SEL_PROT(sak)) अणु
	हाल NFC_HCI_TYPE_A_SEL_PROT_MIFARE:
		वापस NFC_PROTO_MIFARE_MASK;
	हाल NFC_HCI_TYPE_A_SEL_PROT_ISO14443:
		वापस NFC_PROTO_ISO14443_MASK;
	हाल NFC_HCI_TYPE_A_SEL_PROT_DEP:
		वापस NFC_PROTO_NFC_DEP_MASK;
	हाल NFC_HCI_TYPE_A_SEL_PROT_ISO14443_DEP:
		वापस NFC_PROTO_ISO14443_MASK | NFC_PROTO_NFC_DEP_MASK;
	शेष:
		वापस 0xffffffff;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nfc_hci_sak_to_protocol);

पूर्णांक nfc_hci_target_discovered(काष्ठा nfc_hci_dev *hdev, u8 gate)
अणु
	काष्ठा nfc_target *tarमाला_लो;
	काष्ठा sk_buff *atqa_skb = शून्य;
	काष्ठा sk_buff *sak_skb = शून्य;
	काष्ठा sk_buff *uid_skb = शून्य;
	पूर्णांक r;

	pr_debug("from gate %d\n", gate);

	tarमाला_लो = kzalloc(माप(काष्ठा nfc_target), GFP_KERNEL);
	अगर (tarमाला_लो == शून्य)
		वापस -ENOMEM;

	चयन (gate) अणु
	हाल NFC_HCI_RF_READER_A_GATE:
		r = nfc_hci_get_param(hdev, NFC_HCI_RF_READER_A_GATE,
				      NFC_HCI_RF_READER_A_ATQA, &atqa_skb);
		अगर (r < 0)
			जाओ निकास;

		r = nfc_hci_get_param(hdev, NFC_HCI_RF_READER_A_GATE,
				      NFC_HCI_RF_READER_A_SAK, &sak_skb);
		अगर (r < 0)
			जाओ निकास;

		अगर (atqa_skb->len != 2 || sak_skb->len != 1) अणु
			r = -EPROTO;
			जाओ निकास;
		पूर्ण

		tarमाला_लो->supported_protocols =
				nfc_hci_sak_to_protocol(sak_skb->data[0]);
		अगर (tarमाला_लो->supported_protocols == 0xffffffff) अणु
			r = -EPROTO;
			जाओ निकास;
		पूर्ण

		tarमाला_लो->sens_res = be16_to_cpu(*(__be16 *)atqa_skb->data);
		tarमाला_लो->sel_res = sak_skb->data[0];

		r = nfc_hci_get_param(hdev, NFC_HCI_RF_READER_A_GATE,
				      NFC_HCI_RF_READER_A_UID, &uid_skb);
		अगर (r < 0)
			जाओ निकास;

		अगर (uid_skb->len == 0 || uid_skb->len > NFC_NFCID1_MAXSIZE) अणु
			r = -EPROTO;
			जाओ निकास;
		पूर्ण

		स_नकल(tarमाला_लो->nfcid1, uid_skb->data, uid_skb->len);
		tarमाला_लो->nfcid1_len = uid_skb->len;

		अगर (hdev->ops->complete_target_discovered) अणु
			r = hdev->ops->complete_target_discovered(hdev, gate,
								  tarमाला_लो);
			अगर (r < 0)
				जाओ निकास;
		पूर्ण
		अवरोध;
	हाल NFC_HCI_RF_READER_B_GATE:
		tarमाला_लो->supported_protocols = NFC_PROTO_ISO14443_B_MASK;
		अवरोध;
	शेष:
		अगर (hdev->ops->target_from_gate)
			r = hdev->ops->target_from_gate(hdev, gate, tarमाला_लो);
		अन्यथा
			r = -EPROTO;
		अगर (r < 0)
			जाओ निकास;

		अगर (hdev->ops->complete_target_discovered) अणु
			r = hdev->ops->complete_target_discovered(hdev, gate,
								  tarमाला_लो);
			अगर (r < 0)
				जाओ निकास;
		पूर्ण
		अवरोध;
	पूर्ण

	/* अगर driver set the new gate, we will skip the old one */
	अगर (tarमाला_लो->hci_पढ़ोer_gate == 0x00)
		tarमाला_लो->hci_पढ़ोer_gate = gate;

	r = nfc_tarमाला_लो_found(hdev->ndev, tarमाला_लो, 1);

निकास:
	kमुक्त(tarमाला_लो);
	kमुक्त_skb(atqa_skb);
	kमुक्त_skb(sak_skb);
	kमुक्त_skb(uid_skb);

	वापस r;
पूर्ण
EXPORT_SYMBOL(nfc_hci_target_discovered);

व्योम nfc_hci_event_received(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 event,
			    काष्ठा sk_buff *skb)
अणु
	पूर्णांक r = 0;
	u8 gate;

	अगर (pipe >= NFC_HCI_MAX_PIPES) अणु
		pr_err("Discarded event %x to invalid pipe %x\n", event, pipe);
		जाओ निकास;
	पूर्ण

	gate = hdev->pipes[pipe].gate;
	अगर (gate == NFC_HCI_INVALID_GATE) अणु
		pr_err("Discarded event %x to unopened pipe %x\n", event, pipe);
		जाओ निकास;
	पूर्ण

	अगर (hdev->ops->event_received) अणु
		r = hdev->ops->event_received(hdev, pipe, event, skb);
		अगर (r <= 0)
			जाओ निकास_noskb;
	पूर्ण

	चयन (event) अणु
	हाल NFC_HCI_EVT_TARGET_DISCOVERED:
		अगर (skb->len < 1) अणु	/* no status data? */
			r = -EPROTO;
			जाओ निकास;
		पूर्ण

		अगर (skb->data[0] == 3) अणु
			/* TODO: Multiple tarमाला_लो in field, none activated
			 * poll is supposedly stopped, but there is no
			 * single target to activate, so nothing to report
			 * up.
			 * अगर we need to restart poll, we must save the
			 * protocols from the initial poll and reuse here.
			 */
		पूर्ण

		अगर (skb->data[0] != 0) अणु
			r = -EPROTO;
			जाओ निकास;
		पूर्ण

		r = nfc_hci_target_discovered(hdev, gate);
		अवरोध;
	शेष:
		pr_info("Discarded unknown event %x to gate %x\n", event, gate);
		r = -EINVAL;
		अवरोध;
	पूर्ण

निकास:
	kमुक्त_skb(skb);

निकास_noskb:
	अगर (r)
		nfc_hci_driver_failure(hdev, r);
पूर्ण

अटल व्योम nfc_hci_cmd_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा nfc_hci_dev *hdev = from_समयr(hdev, t, cmd_समयr);

	schedule_work(&hdev->msg_tx_work);
पूर्ण

अटल पूर्णांक hci_dev_connect_gates(काष्ठा nfc_hci_dev *hdev, u8 gate_count,
				 काष्ठा nfc_hci_gate *gates)
अणु
	पूर्णांक r;
	जबतक (gate_count--) अणु
		r = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTROLLER_ID,
					 gates->gate, gates->pipe);
		अगर (r < 0)
			वापस r;
		gates++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hci_dev_session_init(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक r;

	अगर (hdev->init_data.gates[0].gate != NFC_HCI_ADMIN_GATE)
		वापस -EPROTO;

	r = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTROLLER_ID,
				 hdev->init_data.gates[0].gate,
				 hdev->init_data.gates[0].pipe);
	अगर (r < 0)
		जाओ निकास;

	r = nfc_hci_get_param(hdev, NFC_HCI_ADMIN_GATE,
			      NFC_HCI_ADMIN_SESSION_IDENTITY, &skb);
	अगर (r < 0)
		जाओ disconnect_all;

	अगर (skb->len && skb->len == म_माप(hdev->init_data.session_id) &&
		(स_भेद(hdev->init_data.session_id, skb->data,
			   skb->len) == 0) && hdev->ops->load_session) अणु
		/* Restore gate<->pipe table from some proprietary location. */

		r = hdev->ops->load_session(hdev);

		अगर (r < 0)
			जाओ disconnect_all;
	पूर्ण अन्यथा अणु

		r = nfc_hci_disconnect_all_gates(hdev);
		अगर (r < 0)
			जाओ निकास;

		r = hci_dev_connect_gates(hdev, hdev->init_data.gate_count,
					  hdev->init_data.gates);
		अगर (r < 0)
			जाओ disconnect_all;

		r = nfc_hci_set_param(hdev, NFC_HCI_ADMIN_GATE,
				NFC_HCI_ADMIN_SESSION_IDENTITY,
				hdev->init_data.session_id,
				म_माप(hdev->init_data.session_id));
	पूर्ण
	अगर (r == 0)
		जाओ निकास;

disconnect_all:
	nfc_hci_disconnect_all_gates(hdev);

निकास:
	kमुक्त_skb(skb);

	वापस r;
पूर्ण

अटल पूर्णांक hci_dev_version(काष्ठा nfc_hci_dev *hdev)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *skb;

	r = nfc_hci_get_param(hdev, NFC_HCI_ID_MGMT_GATE,
			      NFC_HCI_ID_MGMT_VERSION_SW, &skb);
	अगर (r == -EOPNOTSUPP) अणु
		pr_info("Software/Hardware info not available\n");
		वापस 0;
	पूर्ण
	अगर (r < 0)
		वापस r;

	अगर (skb->len != 3) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	hdev->sw_romlib = (skb->data[0] & 0xf0) >> 4;
	hdev->sw_patch = skb->data[0] & 0x0f;
	hdev->sw_flashlib_major = skb->data[1];
	hdev->sw_flashlib_minor = skb->data[2];

	kमुक्त_skb(skb);

	r = nfc_hci_get_param(hdev, NFC_HCI_ID_MGMT_GATE,
			      NFC_HCI_ID_MGMT_VERSION_HW, &skb);
	अगर (r < 0)
		वापस r;

	अगर (skb->len != 3) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	hdev->hw_derivative = (skb->data[0] & 0xe0) >> 5;
	hdev->hw_version = skb->data[0] & 0x1f;
	hdev->hw_mpw = (skb->data[1] & 0xc0) >> 6;
	hdev->hw_software = skb->data[1] & 0x3f;
	hdev->hw_bsid = skb->data[2];

	kमुक्त_skb(skb);

	pr_info("SOFTWARE INFO:\n");
	pr_info("RomLib         : %d\n", hdev->sw_romlib);
	pr_info("Patch          : %d\n", hdev->sw_patch);
	pr_info("FlashLib Major : %d\n", hdev->sw_flashlib_major);
	pr_info("FlashLib Minor : %d\n", hdev->sw_flashlib_minor);
	pr_info("HARDWARE INFO:\n");
	pr_info("Derivative     : %d\n", hdev->hw_derivative);
	pr_info("HW Version     : %d\n", hdev->hw_version);
	pr_info("#MPW           : %d\n", hdev->hw_mpw);
	pr_info("Software       : %d\n", hdev->hw_software);
	pr_info("BSID Version   : %d\n", hdev->hw_bsid);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_dev_up(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);
	पूर्णांक r = 0;

	अगर (hdev->ops->खोलो) अणु
		r = hdev->ops->खोलो(hdev);
		अगर (r < 0)
			वापस r;
	पूर्ण

	r = nfc_llc_start(hdev->llc);
	अगर (r < 0)
		जाओ निकास_बंद;

	r = hci_dev_session_init(hdev);
	अगर (r < 0)
		जाओ निकास_llc;

	r = nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
			       NFC_HCI_EVT_END_OPERATION, शून्य, 0);
	अगर (r < 0)
		जाओ निकास_llc;

	अगर (hdev->ops->hci_पढ़ोy) अणु
		r = hdev->ops->hci_पढ़ोy(hdev);
		अगर (r < 0)
			जाओ निकास_llc;
	पूर्ण

	r = hci_dev_version(hdev);
	अगर (r < 0)
		जाओ निकास_llc;

	वापस 0;

निकास_llc:
	nfc_llc_stop(hdev->llc);

निकास_बंद:
	अगर (hdev->ops->बंद)
		hdev->ops->बंद(hdev);

	वापस r;
पूर्ण

अटल पूर्णांक hci_dev_करोwn(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	nfc_llc_stop(hdev->llc);

	अगर (hdev->ops->बंद)
		hdev->ops->बंद(hdev);

	nfc_hci_reset_pipes(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_start_poll(काष्ठा nfc_dev *nfc_dev,
			  u32 im_protocols, u32 पंचांग_protocols)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (hdev->ops->start_poll)
		वापस hdev->ops->start_poll(hdev, im_protocols, पंचांग_protocols);
	अन्यथा
		वापस nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
					  NFC_HCI_EVT_READER_REQUESTED,
					  शून्य, 0);
पूर्ण

अटल व्योम hci_stop_poll(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (hdev->ops->stop_poll)
		hdev->ops->stop_poll(hdev);
	अन्यथा
		nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
				   NFC_HCI_EVT_END_OPERATION, शून्य, 0);
पूर्ण

अटल पूर्णांक hci_dep_link_up(काष्ठा nfc_dev *nfc_dev, काष्ठा nfc_target *target,
				__u8 comm_mode, __u8 *gb, माप_प्रकार gb_len)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (!hdev->ops->dep_link_up)
		वापस 0;

	वापस hdev->ops->dep_link_up(hdev, target, comm_mode,
				      gb, gb_len);
पूर्ण

अटल पूर्णांक hci_dep_link_करोwn(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (!hdev->ops->dep_link_करोwn)
		वापस 0;

	वापस hdev->ops->dep_link_करोwn(hdev);
पूर्ण

अटल पूर्णांक hci_activate_target(काष्ठा nfc_dev *nfc_dev,
			       काष्ठा nfc_target *target, u32 protocol)
अणु
	वापस 0;
पूर्ण

अटल व्योम hci_deactivate_target(काष्ठा nfc_dev *nfc_dev,
				  काष्ठा nfc_target *target,
				  u8 mode)
अणु
पूर्ण

#घोषणा HCI_CB_TYPE_TRANSCEIVE 1

अटल व्योम hci_transceive_cb(व्योम *context, काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा nfc_hci_dev *hdev = context;

	चयन (hdev->async_cb_type) अणु
	हाल HCI_CB_TYPE_TRANSCEIVE:
		/*
		 * TODO: Check RF Error indicator to make sure data is valid.
		 * It seems that HCI cmd can complete without error, but data
		 * can be invalid अगर an RF error occured? Ignore क्रम now.
		 */
		अगर (err == 0)
			skb_trim(skb, skb->len - 1); /* RF Err ind */

		hdev->async_cb(hdev->async_cb_context, skb, err);
		अवरोध;
	शेष:
		अगर (err == 0)
			kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक hci_transceive(काष्ठा nfc_dev *nfc_dev, काष्ठा nfc_target *target,
			  काष्ठा sk_buff *skb, data_exchange_cb_t cb,
			  व्योम *cb_context)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);
	पूर्णांक r;

	pr_debug("target_idx=%d\n", target->idx);

	चयन (target->hci_पढ़ोer_gate) अणु
	हाल NFC_HCI_RF_READER_A_GATE:
	हाल NFC_HCI_RF_READER_B_GATE:
		अगर (hdev->ops->im_transceive) अणु
			r = hdev->ops->im_transceive(hdev, target, skb, cb,
						     cb_context);
			अगर (r <= 0)	/* handled */
				अवरोध;
		पूर्ण

		*(u8 *)skb_push(skb, 1) = 0;	/* CTR, see spec:10.2.2.1 */

		hdev->async_cb_type = HCI_CB_TYPE_TRANSCEIVE;
		hdev->async_cb = cb;
		hdev->async_cb_context = cb_context;

		r = nfc_hci_send_cmd_async(hdev, target->hci_पढ़ोer_gate,
					   NFC_HCI_WR_XCHG_DATA, skb->data,
					   skb->len, hci_transceive_cb, hdev);
		अवरोध;
	शेष:
		अगर (hdev->ops->im_transceive) अणु
			r = hdev->ops->im_transceive(hdev, target, skb, cb,
						     cb_context);
			अगर (r == 1)
				r = -ENOTSUPP;
		पूर्ण अन्यथा अणु
			r = -ENOTSUPP;
		पूर्ण
		अवरोध;
	पूर्ण

	kमुक्त_skb(skb);

	वापस r;
पूर्ण

अटल पूर्णांक hci_पंचांग_send(काष्ठा nfc_dev *nfc_dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (!hdev->ops->पंचांग_send) अणु
		kमुक्त_skb(skb);
		वापस -ENOTSUPP;
	पूर्ण

	वापस hdev->ops->पंचांग_send(hdev, skb);
पूर्ण

अटल पूर्णांक hci_check_presence(काष्ठा nfc_dev *nfc_dev,
			      काष्ठा nfc_target *target)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (!hdev->ops->check_presence)
		वापस 0;

	वापस hdev->ops->check_presence(hdev, target);
पूर्ण

अटल पूर्णांक hci_discover_se(काष्ठा nfc_dev *nfc_dev)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (hdev->ops->discover_se)
		वापस hdev->ops->discover_se(hdev);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_enable_se(काष्ठा nfc_dev *nfc_dev, u32 se_idx)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (hdev->ops->enable_se)
		वापस hdev->ops->enable_se(hdev, se_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_disable_se(काष्ठा nfc_dev *nfc_dev, u32 se_idx)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (hdev->ops->disable_se)
		वापस hdev->ops->disable_se(hdev, se_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक hci_se_io(काष्ठा nfc_dev *nfc_dev, u32 se_idx,
		     u8 *apdu, माप_प्रकार apdu_length,
		     se_io_cb_t cb, व्योम *cb_context)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (hdev->ops->se_io)
		वापस hdev->ops->se_io(hdev, se_idx, apdu,
					apdu_length, cb, cb_context);

	वापस 0;
पूर्ण

अटल व्योम nfc_hci_failure(काष्ठा nfc_hci_dev *hdev, पूर्णांक err)
अणु
	mutex_lock(&hdev->msg_tx_mutex);

	अगर (hdev->cmd_pending_msg == शून्य) अणु
		nfc_driver_failure(hdev->ndev, err);
		जाओ निकास;
	पूर्ण

	__nfc_hci_cmd_completion(hdev, err, शून्य);

निकास:
	mutex_unlock(&hdev->msg_tx_mutex);
पूर्ण

अटल व्योम nfc_hci_llc_failure(काष्ठा nfc_hci_dev *hdev, पूर्णांक err)
अणु
	nfc_hci_failure(hdev, err);
पूर्ण

अटल व्योम nfc_hci_recv_from_llc(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा hcp_packet *packet;
	u8 type;
	u8 inकाष्ठाion;
	काष्ठा sk_buff *hcp_skb;
	u8 pipe;
	काष्ठा sk_buff *frag_skb;
	पूर्णांक msg_len;

	packet = (काष्ठा hcp_packet *)skb->data;
	अगर ((packet->header & ~NFC_HCI_FRAGMENT) == 0) अणु
		skb_queue_tail(&hdev->rx_hcp_frags, skb);
		वापस;
	पूर्ण

	/* it's the last fragment. Does it need re-aggregation? */
	अगर (skb_queue_len(&hdev->rx_hcp_frags)) अणु
		pipe = packet->header & NFC_HCI_FRAGMENT;
		skb_queue_tail(&hdev->rx_hcp_frags, skb);

		msg_len = 0;
		skb_queue_walk(&hdev->rx_hcp_frags, frag_skb) अणु
			msg_len += (frag_skb->len -
				    NFC_HCI_HCP_PACKET_HEADER_LEN);
		पूर्ण

		hcp_skb = nfc_alloc_recv_skb(NFC_HCI_HCP_PACKET_HEADER_LEN +
					     msg_len, GFP_KERNEL);
		अगर (hcp_skb == शून्य) अणु
			nfc_hci_failure(hdev, -ENOMEM);
			वापस;
		पूर्ण

		skb_put_u8(hcp_skb, pipe);

		skb_queue_walk(&hdev->rx_hcp_frags, frag_skb) अणु
			msg_len = frag_skb->len - NFC_HCI_HCP_PACKET_HEADER_LEN;
			skb_put_data(hcp_skb,
				     frag_skb->data + NFC_HCI_HCP_PACKET_HEADER_LEN,
				     msg_len);
		पूर्ण

		skb_queue_purge(&hdev->rx_hcp_frags);
	पूर्ण अन्यथा अणु
		packet->header &= NFC_HCI_FRAGMENT;
		hcp_skb = skb;
	पूर्ण

	/* अगर this is a response, dispatch immediately to
	 * unblock रुकोing cmd context. Otherwise, enqueue to dispatch
	 * in separate context where handler can also execute command.
	 */
	packet = (काष्ठा hcp_packet *)hcp_skb->data;
	type = HCP_MSG_GET_TYPE(packet->message.header);
	अगर (type == NFC_HCI_HCP_RESPONSE) अणु
		pipe = packet->header;
		inकाष्ठाion = HCP_MSG_GET_CMD(packet->message.header);
		skb_pull(hcp_skb, NFC_HCI_HCP_PACKET_HEADER_LEN +
			 NFC_HCI_HCP_MESSAGE_HEADER_LEN);
		nfc_hci_hcp_message_rx(hdev, pipe, type, inकाष्ठाion, hcp_skb);
	पूर्ण अन्यथा अणु
		skb_queue_tail(&hdev->msg_rx_queue, hcp_skb);
		schedule_work(&hdev->msg_rx_work);
	पूर्ण
पूर्ण

अटल पूर्णांक hci_fw_करोwnload(काष्ठा nfc_dev *nfc_dev, स्थिर अक्षर *firmware_name)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	अगर (!hdev->ops->fw_करोwnload)
		वापस -ENOTSUPP;

	वापस hdev->ops->fw_करोwnload(hdev, firmware_name);
पूर्ण

अटल काष्ठा nfc_ops hci_nfc_ops = अणु
	.dev_up = hci_dev_up,
	.dev_करोwn = hci_dev_करोwn,
	.start_poll = hci_start_poll,
	.stop_poll = hci_stop_poll,
	.dep_link_up = hci_dep_link_up,
	.dep_link_करोwn = hci_dep_link_करोwn,
	.activate_target = hci_activate_target,
	.deactivate_target = hci_deactivate_target,
	.im_transceive = hci_transceive,
	.पंचांग_send = hci_पंचांग_send,
	.check_presence = hci_check_presence,
	.fw_करोwnload = hci_fw_करोwnload,
	.discover_se = hci_discover_se,
	.enable_se = hci_enable_se,
	.disable_se = hci_disable_se,
	.se_io = hci_se_io,
पूर्ण;

काष्ठा nfc_hci_dev *nfc_hci_allocate_device(काष्ठा nfc_hci_ops *ops,
					    काष्ठा nfc_hci_init_data *init_data,
					    अचिन्हित दीर्घ quirks,
					    u32 protocols,
					    स्थिर अक्षर *llc_name,
					    पूर्णांक tx_headroom,
					    पूर्णांक tx_tailroom,
					    पूर्णांक max_link_payload)
अणु
	काष्ठा nfc_hci_dev *hdev;

	अगर (ops->xmit == शून्य)
		वापस शून्य;

	अगर (protocols == 0)
		वापस शून्य;

	hdev = kzalloc(माप(काष्ठा nfc_hci_dev), GFP_KERNEL);
	अगर (hdev == शून्य)
		वापस शून्य;

	hdev->llc = nfc_llc_allocate(llc_name, hdev, ops->xmit,
				     nfc_hci_recv_from_llc, tx_headroom,
				     tx_tailroom, nfc_hci_llc_failure);
	अगर (hdev->llc == शून्य) अणु
		kमुक्त(hdev);
		वापस शून्य;
	पूर्ण

	hdev->ndev = nfc_allocate_device(&hci_nfc_ops, protocols,
					 tx_headroom + HCI_CMDS_HEADROOM,
					 tx_tailroom);
	अगर (!hdev->ndev) अणु
		nfc_llc_मुक्त(hdev->llc);
		kमुक्त(hdev);
		वापस शून्य;
	पूर्ण

	hdev->ops = ops;
	hdev->max_data_link_payload = max_link_payload;
	hdev->init_data = *init_data;

	nfc_set_drvdata(hdev->ndev, hdev);

	nfc_hci_reset_pipes(hdev);

	hdev->quirks = quirks;

	वापस hdev;
पूर्ण
EXPORT_SYMBOL(nfc_hci_allocate_device);

व्योम nfc_hci_मुक्त_device(काष्ठा nfc_hci_dev *hdev)
अणु
	nfc_मुक्त_device(hdev->ndev);
	nfc_llc_मुक्त(hdev->llc);
	kमुक्त(hdev);
पूर्ण
EXPORT_SYMBOL(nfc_hci_मुक्त_device);

पूर्णांक nfc_hci_रेजिस्टर_device(काष्ठा nfc_hci_dev *hdev)
अणु
	mutex_init(&hdev->msg_tx_mutex);

	INIT_LIST_HEAD(&hdev->msg_tx_queue);

	INIT_WORK(&hdev->msg_tx_work, nfc_hci_msg_tx_work);

	समयr_setup(&hdev->cmd_समयr, nfc_hci_cmd_समयout, 0);

	skb_queue_head_init(&hdev->rx_hcp_frags);

	INIT_WORK(&hdev->msg_rx_work, nfc_hci_msg_rx_work);

	skb_queue_head_init(&hdev->msg_rx_queue);

	वापस nfc_रेजिस्टर_device(hdev->ndev);
पूर्ण
EXPORT_SYMBOL(nfc_hci_रेजिस्टर_device);

व्योम nfc_hci_unरेजिस्टर_device(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा hci_msg *msg, *n;

	mutex_lock(&hdev->msg_tx_mutex);

	अगर (hdev->cmd_pending_msg) अणु
		अगर (hdev->cmd_pending_msg->cb)
			hdev->cmd_pending_msg->cb(
					     hdev->cmd_pending_msg->cb_context,
					     शून्य, -ESHUTDOWN);
		kमुक्त(hdev->cmd_pending_msg);
		hdev->cmd_pending_msg = शून्य;
	पूर्ण

	hdev->shutting_करोwn = true;

	mutex_unlock(&hdev->msg_tx_mutex);

	del_समयr_sync(&hdev->cmd_समयr);
	cancel_work_sync(&hdev->msg_tx_work);

	cancel_work_sync(&hdev->msg_rx_work);

	nfc_unरेजिस्टर_device(hdev->ndev);

	skb_queue_purge(&hdev->rx_hcp_frags);
	skb_queue_purge(&hdev->msg_rx_queue);

	list_क्रम_each_entry_safe(msg, n, &hdev->msg_tx_queue, msg_l) अणु
		list_del(&msg->msg_l);
		skb_queue_purge(&msg->msg_frags);
		kमुक्त(msg);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nfc_hci_unरेजिस्टर_device);

व्योम nfc_hci_set_clientdata(काष्ठा nfc_hci_dev *hdev, व्योम *clientdata)
अणु
	hdev->clientdata = clientdata;
पूर्ण
EXPORT_SYMBOL(nfc_hci_set_clientdata);

व्योम *nfc_hci_get_clientdata(काष्ठा nfc_hci_dev *hdev)
अणु
	वापस hdev->clientdata;
पूर्ण
EXPORT_SYMBOL(nfc_hci_get_clientdata);

व्योम nfc_hci_driver_failure(काष्ठा nfc_hci_dev *hdev, पूर्णांक err)
अणु
	nfc_hci_failure(hdev, err);
पूर्ण
EXPORT_SYMBOL(nfc_hci_driver_failure);

व्योम nfc_hci_recv_frame(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	nfc_llc_rcv_from_drv(hdev->llc, skb);
पूर्ण
EXPORT_SYMBOL(nfc_hci_recv_frame);

अटल पूर्णांक __init nfc_hci_init(व्योम)
अणु
	वापस nfc_llc_init();
पूर्ण

अटल व्योम __निकास nfc_hci_निकास(व्योम)
अणु
	nfc_llc_निकास();
पूर्ण

subsys_initcall(nfc_hci_init);
module_निकास(nfc_hci_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("NFC HCI Core");
