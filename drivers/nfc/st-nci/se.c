<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Secure Element driver क्रम STMicroelectronics NFC NCI chip
 *
 * Copyright (C) 2014-2015 STMicroelectronics SAS. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <linux/delay.h>
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>

#समावेश "st-nci.h"

काष्ठा st_nci_pipe_info अणु
	u8 pipe_state;
	u8 src_host_id;
	u8 src_gate_id;
	u8 dst_host_id;
	u8 dst_gate_id;
पूर्ण __packed;

/* Hosts */
#घोषणा ST_NCI_HOST_CONTROLLER_ID     0x00
#घोषणा ST_NCI_TERMINAL_HOST_ID       0x01
#घोषणा ST_NCI_UICC_HOST_ID           0x02
#घोषणा ST_NCI_ESE_HOST_ID            0xc0

/* Gates */
#घोषणा ST_NCI_APDU_READER_GATE       0xf0
#घोषणा ST_NCI_CONNECTIVITY_GATE      0x41

/* Pipes */
#घोषणा ST_NCI_DEVICE_MGNT_PIPE               0x02

/* Connectivity pipe only */
#घोषणा ST_NCI_SE_COUNT_PIPE_UICC             0x01
/* Connectivity + APDU Reader pipe */
#घोषणा ST_NCI_SE_COUNT_PIPE_EMBEDDED         0x02

#घोषणा ST_NCI_SE_TO_HOT_PLUG			1000 /* msecs */
#घोषणा ST_NCI_SE_TO_PIPES			2000

#घोषणा ST_NCI_EVT_HOT_PLUG_IS_INHIBITED(x)   (x->data[0] & 0x80)

#घोषणा NCI_HCI_APDU_PARAM_ATR                     0x01
#घोषणा NCI_HCI_ADMIN_PARAM_SESSION_IDENTITY       0x01
#घोषणा NCI_HCI_ADMIN_PARAM_WHITELIST              0x03
#घोषणा NCI_HCI_ADMIN_PARAM_HOST_LIST              0x04

#घोषणा ST_NCI_EVT_SE_HARD_RESET		0x20
#घोषणा ST_NCI_EVT_TRANSMIT_DATA		0x10
#घोषणा ST_NCI_EVT_WTX_REQUEST			0x11
#घोषणा ST_NCI_EVT_SE_SOFT_RESET		0x11
#घोषणा ST_NCI_EVT_SE_END_OF_APDU_TRANSFER	0x21
#घोषणा ST_NCI_EVT_HOT_PLUG			0x03

#घोषणा ST_NCI_SE_MODE_OFF                    0x00
#घोषणा ST_NCI_SE_MODE_ON                     0x01

#घोषणा ST_NCI_EVT_CONNECTIVITY       0x10
#घोषणा ST_NCI_EVT_TRANSACTION        0x12

#घोषणा ST_NCI_DM_GETINFO             0x13
#घोषणा ST_NCI_DM_GETINFO_PIPE_LIST   0x02
#घोषणा ST_NCI_DM_GETINFO_PIPE_INFO   0x01
#घोषणा ST_NCI_DM_PIPE_CREATED        0x02
#घोषणा ST_NCI_DM_PIPE_OPEN           0x04
#घोषणा ST_NCI_DM_RF_ACTIVE           0x80
#घोषणा ST_NCI_DM_DISCONNECT          0x30

#घोषणा ST_NCI_DM_IS_PIPE_OPEN(p) \
	((p & 0x0f) == (ST_NCI_DM_PIPE_CREATED | ST_NCI_DM_PIPE_OPEN))

#घोषणा ST_NCI_ATR_DEFAULT_BWI        0x04

/*
 * WT = 2^BWI/10[s], convert पूर्णांकo msecs and add a secure
 * room by increasing by 2 this समयout
 */
#घोषणा ST_NCI_BWI_TO_TIMEOUT(x)      ((1 << x) * 200)
#घोषणा ST_NCI_ATR_GET_Y_FROM_TD(x)   (x >> 4)

/* If TA is present bit 0 is set */
#घोषणा ST_NCI_ATR_TA_PRESENT(x) (x & 0x01)
/* If TB is present bit 1 is set */
#घोषणा ST_NCI_ATR_TB_PRESENT(x) (x & 0x02)

#घोषणा ST_NCI_NUM_DEVICES           256

अटल DECLARE_BITMAP(dev_mask, ST_NCI_NUM_DEVICES);

/* Here are the mandatory pipe क्रम st_nci */
अटल काष्ठा nci_hci_gate st_nci_gates[] = अणु
	अणुNCI_HCI_ADMIN_GATE, NCI_HCI_ADMIN_PIPE,
					ST_NCI_HOST_CONTROLLER_IDपूर्ण,
	अणुNCI_HCI_LINK_MGMT_GATE, NCI_HCI_LINK_MGMT_PIPE,
					ST_NCI_HOST_CONTROLLER_IDपूर्ण,
	अणुST_NCI_DEVICE_MGNT_GATE, ST_NCI_DEVICE_MGNT_PIPE,
					ST_NCI_HOST_CONTROLLER_IDपूर्ण,

	अणुNCI_HCI_IDENTITY_MGMT_GATE, NCI_HCI_INVALID_PIPE,
					ST_NCI_HOST_CONTROLLER_IDपूर्ण,

	/* Secure element pipes are created by secure element host */
	अणुST_NCI_CONNECTIVITY_GATE, NCI_HCI_DO_NOT_OPEN_PIPE,
					ST_NCI_HOST_CONTROLLER_IDपूर्ण,
	अणुST_NCI_APDU_READER_GATE, NCI_HCI_DO_NOT_OPEN_PIPE,
					ST_NCI_HOST_CONTROLLER_IDपूर्ण,
पूर्ण;

अटल u8 st_nci_se_get_bwi(काष्ठा nci_dev *ndev)
अणु
	पूर्णांक i;
	u8 td;
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	/* Bits 8 to 5 of the first TB क्रम T=1 encode BWI from zero to nine */
	क्रम (i = 1; i < ST_NCI_ESE_MAX_LENGTH; i++) अणु
		td = ST_NCI_ATR_GET_Y_FROM_TD(info->se_info.atr[i]);
		अगर (ST_NCI_ATR_TA_PRESENT(td))
			i++;
		अगर (ST_NCI_ATR_TB_PRESENT(td)) अणु
			i++;
			वापस info->se_info.atr[i] >> 4;
		पूर्ण
	पूर्ण
	वापस ST_NCI_ATR_DEFAULT_BWI;
पूर्ण

अटल व्योम st_nci_se_get_atr(काष्ठा nci_dev *ndev)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);
	पूर्णांक r;
	काष्ठा sk_buff *skb;

	r = nci_hci_get_param(ndev, ST_NCI_APDU_READER_GATE,
				NCI_HCI_APDU_PARAM_ATR, &skb);
	अगर (r < 0)
		वापस;

	अगर (skb->len <= ST_NCI_ESE_MAX_LENGTH) अणु
		स_नकल(info->se_info.atr, skb->data, skb->len);

		info->se_info.wt_समयout =
			ST_NCI_BWI_TO_TIMEOUT(st_nci_se_get_bwi(ndev));
	पूर्ण
	kमुक्त_skb(skb);
पूर्ण

पूर्णांक st_nci_hci_load_session(काष्ठा nci_dev *ndev)
अणु
	पूर्णांक i, j, r;
	काष्ठा sk_buff *skb_pipe_list, *skb_pipe_info;
	काष्ठा st_nci_pipe_info *dm_pipe_info;
	u8 pipe_list[] = अणु ST_NCI_DM_GETINFO_PIPE_LIST,
			ST_NCI_TERMINAL_HOST_IDपूर्ण;
	u8 pipe_info[] = अणु ST_NCI_DM_GETINFO_PIPE_INFO,
			ST_NCI_TERMINAL_HOST_ID, 0पूर्ण;

	/* On ST_NCI device pipes number are dynamics
	 * If pipes are alपढ़ोy created, hci_dev_up will fail.
	 * Doing a clear all pipe is a bad idea because:
	 * - It करोes useless EEPROM cycling
	 * - It might cause issue क्रम secure elements support
	 * (such as removing connectivity or APDU पढ़ोer pipe)
	 * A better approach on ST_NCI is to:
	 * - get a pipe list क्रम each host.
	 * (eg: ST_NCI_HOST_CONTROLLER_ID क्रम now).
	 * (TODO Later on UICC HOST and eSE HOST)
	 * - get pipe inक्रमmation
	 * - match retrieved pipe list in st_nci_gates
	 * ST_NCI_DEVICE_MGNT_GATE is a proprietary gate
	 * with ST_NCI_DEVICE_MGNT_PIPE.
	 * Pipe can be बंदd and need to be खोलो.
	 */
	r = nci_hci_connect_gate(ndev, ST_NCI_HOST_CONTROLLER_ID,
				ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_DEVICE_MGNT_PIPE);
	अगर (r < 0)
		वापस r;

	/* Get pipe list */
	r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_DM_GETINFO, pipe_list, माप(pipe_list),
			&skb_pipe_list);
	अगर (r < 0)
		वापस r;

	/* Complete the existing gate_pipe table */
	क्रम (i = 0; i < skb_pipe_list->len; i++) अणु
		pipe_info[2] = skb_pipe_list->data[i];
		r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
					ST_NCI_DM_GETINFO, pipe_info,
					माप(pipe_info), &skb_pipe_info);

		अगर (r)
			जारी;

		/*
		 * Match pipe ID and gate ID
		 * Output क्रमmat from ST21NFC_DM_GETINFO is:
		 * - pipe state (1byte)
		 * - source hid (1byte)
		 * - source gid (1byte)
		 * - destination hid (1byte)
		 * - destination gid (1byte)
		 */
		dm_pipe_info = (काष्ठा st_nci_pipe_info *)skb_pipe_info->data;
		अगर (dm_pipe_info->dst_gate_id == ST_NCI_APDU_READER_GATE &&
		    dm_pipe_info->src_host_id == ST_NCI_UICC_HOST_ID) अणु
			pr_err("Unexpected apdu_reader pipe on host %x\n",
			       dm_pipe_info->src_host_id);
			kमुक्त_skb(skb_pipe_info);
			जारी;
		पूर्ण

		क्रम (j = 3; (j < ARRAY_SIZE(st_nci_gates)) &&
		     (st_nci_gates[j].gate != dm_pipe_info->dst_gate_id); j++)
			;

		अगर (j < ARRAY_SIZE(st_nci_gates) &&
		    st_nci_gates[j].gate == dm_pipe_info->dst_gate_id &&
		    ST_NCI_DM_IS_PIPE_OPEN(dm_pipe_info->pipe_state)) अणु
			ndev->hci_dev->init_data.gates[j].pipe = pipe_info[2];

			ndev->hci_dev->gate2pipe[st_nci_gates[j].gate] =
						pipe_info[2];
			ndev->hci_dev->pipes[pipe_info[2]].gate =
						st_nci_gates[j].gate;
			ndev->hci_dev->pipes[pipe_info[2]].host =
						dm_pipe_info->src_host_id;
		पूर्ण
		kमुक्त_skb(skb_pipe_info);
	पूर्ण

	/*
	 * 3 gates have a well known pipe ID. Only NCI_HCI_LINK_MGMT_GATE
	 * is not yet खोलो at this stage.
	 */
	r = nci_hci_connect_gate(ndev, ST_NCI_HOST_CONTROLLER_ID,
				 NCI_HCI_LINK_MGMT_GATE,
				 NCI_HCI_LINK_MGMT_PIPE);

	kमुक्त_skb(skb_pipe_list);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(st_nci_hci_load_session);

अटल व्योम st_nci_hci_admin_event_received(काष्ठा nci_dev *ndev,
					      u8 event, काष्ठा sk_buff *skb)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	चयन (event) अणु
	हाल ST_NCI_EVT_HOT_PLUG:
		अगर (info->se_info.se_active) अणु
			अगर (!ST_NCI_EVT_HOT_PLUG_IS_INHIBITED(skb)) अणु
				del_समयr_sync(&info->se_info.se_active_समयr);
				info->se_info.se_active = false;
				complete(&info->se_info.req_completion);
			पूर्ण अन्यथा अणु
				mod_समयr(&info->se_info.se_active_समयr,
				      jअगरfies +
				      msecs_to_jअगरfies(ST_NCI_SE_TO_PIPES));
			पूर्ण
		पूर्ण
	अवरोध;
	शेष:
		nfc_err(&ndev->nfc_dev->dev, "Unexpected event on admin gate\n");
	पूर्ण
पूर्ण

अटल पूर्णांक st_nci_hci_apdu_पढ़ोer_event_received(काष्ठा nci_dev *ndev,
						   u8 event,
						   काष्ठा sk_buff *skb)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	pr_debug("apdu reader gate event: %x\n", event);

	चयन (event) अणु
	हाल ST_NCI_EVT_TRANSMIT_DATA:
		del_समयr_sync(&info->se_info.bwi_समयr);
		info->se_info.bwi_active = false;
		info->se_info.cb(info->se_info.cb_context,
				 skb->data, skb->len, 0);
	अवरोध;
	हाल ST_NCI_EVT_WTX_REQUEST:
		mod_समयr(&info->se_info.bwi_समयr, jअगरfies +
			  msecs_to_jअगरfies(info->se_info.wt_समयout));
	अवरोध;
	शेष:
		nfc_err(&ndev->nfc_dev->dev, "Unexpected event on apdu reader gate\n");
		वापस 1;
	पूर्ण

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Returns:
 * <= 0: driver handled the event, skb consumed
 *    1: driver करोes not handle the event, please करो standard processing
 */
अटल पूर्णांक st_nci_hci_connectivity_event_received(काष्ठा nci_dev *ndev,
						u8 host, u8 event,
						काष्ठा sk_buff *skb)
अणु
	पूर्णांक r = 0;
	काष्ठा device *dev = &ndev->nfc_dev->dev;
	काष्ठा nfc_evt_transaction *transaction;

	pr_debug("connectivity gate event: %x\n", event);

	चयन (event) अणु
	हाल ST_NCI_EVT_CONNECTIVITY:
		r = nfc_se_connectivity(ndev->nfc_dev, host);
	अवरोध;
	हाल ST_NCI_EVT_TRANSACTION:
		/* According to specअगरication etsi 102 622
		 * 11.2.2.4 EVT_TRANSACTION Table 52
		 * Description  Tag     Length
		 * AID          81      5 to 16
		 * PARAMETERS   82      0 to 255
		 */
		अगर (skb->len < NFC_MIN_AID_LENGTH + 2 &&
		    skb->data[0] != NFC_EVT_TRANSACTION_AID_TAG)
			वापस -EPROTO;

		transaction = devm_kzalloc(dev, skb->len - 2, GFP_KERNEL);
		अगर (!transaction)
			वापस -ENOMEM;

		transaction->aid_len = skb->data[1];
		स_नकल(transaction->aid, &skb->data[2], transaction->aid_len);

		/* Check next byte is PARAMETERS tag (82) */
		अगर (skb->data[transaction->aid_len + 2] !=
		    NFC_EVT_TRANSACTION_PARAMS_TAG)
			वापस -EPROTO;

		transaction->params_len = skb->data[transaction->aid_len + 3];
		स_नकल(transaction->params, skb->data +
		       transaction->aid_len + 4, transaction->params_len);

		r = nfc_se_transaction(ndev->nfc_dev, host, transaction);
		अवरोध;
	शेष:
		nfc_err(&ndev->nfc_dev->dev, "Unexpected event on connectivity gate\n");
		वापस 1;
	पूर्ण
	kमुक्त_skb(skb);
	वापस r;
पूर्ण

व्योम st_nci_hci_event_received(काष्ठा nci_dev *ndev, u8 pipe,
				 u8 event, काष्ठा sk_buff *skb)
अणु
	u8 gate = ndev->hci_dev->pipes[pipe].gate;
	u8 host = ndev->hci_dev->pipes[pipe].host;

	चयन (gate) अणु
	हाल NCI_HCI_ADMIN_GATE:
		st_nci_hci_admin_event_received(ndev, event, skb);
	अवरोध;
	हाल ST_NCI_APDU_READER_GATE:
		st_nci_hci_apdu_पढ़ोer_event_received(ndev, event, skb);
	अवरोध;
	हाल ST_NCI_CONNECTIVITY_GATE:
		st_nci_hci_connectivity_event_received(ndev, host, event, skb);
	अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(st_nci_hci_event_received);

व्योम st_nci_hci_cmd_received(काष्ठा nci_dev *ndev, u8 pipe, u8 cmd,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);
	u8 gate = ndev->hci_dev->pipes[pipe].gate;

	pr_debug("cmd: %x\n", cmd);

	चयन (cmd) अणु
	हाल NCI_HCI_ANY_OPEN_PIPE:
		अगर (gate != ST_NCI_APDU_READER_GATE &&
		    ndev->hci_dev->pipes[pipe].host != ST_NCI_UICC_HOST_ID)
			ndev->hci_dev->count_pipes++;

		अगर (ndev->hci_dev->count_pipes ==
		    ndev->hci_dev->expected_pipes) अणु
			del_समयr_sync(&info->se_info.se_active_समयr);
			info->se_info.se_active = false;
			ndev->hci_dev->count_pipes = 0;
			complete(&info->se_info.req_completion);
		पूर्ण
	अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(st_nci_hci_cmd_received);

अटल पूर्णांक st_nci_control_se(काष्ठा nci_dev *ndev, u8 se_idx,
			     u8 state)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);
	पूर्णांक r, i;
	काष्ठा sk_buff *sk_host_list;
	u8 host_id;

	चयन (se_idx) अणु
	हाल ST_NCI_UICC_HOST_ID:
		ndev->hci_dev->count_pipes = 0;
		ndev->hci_dev->expected_pipes = ST_NCI_SE_COUNT_PIPE_UICC;
		अवरोध;
	हाल ST_NCI_ESE_HOST_ID:
		ndev->hci_dev->count_pipes = 0;
		ndev->hci_dev->expected_pipes = ST_NCI_SE_COUNT_PIPE_EMBEDDED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Wait क्रम an EVT_HOT_PLUG in order to
	 * retrieve a relevant host list.
	 */
	reinit_completion(&info->se_info.req_completion);
	r = nci_nfcee_mode_set(ndev, se_idx, state);
	अगर (r != NCI_STATUS_OK)
		वापस r;

	mod_समयr(&info->se_info.se_active_समयr, jअगरfies +
		msecs_to_jअगरfies(ST_NCI_SE_TO_HOT_PLUG));
	info->se_info.se_active = true;

	/* Ignore वापस value and check in any हाल the host_list */
	रुको_क्रम_completion_पूर्णांकerruptible(&info->se_info.req_completion);

	/* There might be some "collision" after receiving a HOT_PLUG event
	 * This may cause the CLF to not answer to the next hci command.
	 * There is no possible synchronization to prevent this.
	 * Adding a small delay is the only way to solve the issue.
	 */
	अगर (info->se_info.se_status->is_ese_present &&
	    info->se_info.se_status->is_uicc_present)
		usleep_range(15000, 20000);

	r = nci_hci_get_param(ndev, NCI_HCI_ADMIN_GATE,
			NCI_HCI_ADMIN_PARAM_HOST_LIST, &sk_host_list);
	अगर (r != NCI_HCI_ANY_OK)
		वापस r;

	क्रम (i = 0; i < sk_host_list->len &&
		sk_host_list->data[i] != se_idx; i++)
		;
	host_id = sk_host_list->data[i];
	kमुक्त_skb(sk_host_list);
	अगर (state == ST_NCI_SE_MODE_ON && host_id == se_idx)
		वापस se_idx;
	अन्यथा अगर (state == ST_NCI_SE_MODE_OFF && host_id != se_idx)
		वापस se_idx;

	वापस -1;
पूर्ण

पूर्णांक st_nci_disable_se(काष्ठा nci_dev *ndev, u32 se_idx)
अणु
	पूर्णांक r;

	pr_debug("st_nci_disable_se\n");

	/*
	 * According to upper layer, se_idx == NFC_SE_UICC when
	 * info->se_info.se_status->is_uicc_enable is true should never happen
	 * Same क्रम eSE.
	 */
	r = st_nci_control_se(ndev, se_idx, ST_NCI_SE_MODE_OFF);
	अगर (r < 0) अणु
		/* Do best efक्रमt to release SWP */
		अगर (se_idx == NFC_SE_EMBEDDED) अणु
			r = nci_hci_send_event(ndev, ST_NCI_APDU_READER_GATE,
					ST_NCI_EVT_SE_END_OF_APDU_TRANSFER,
					शून्य, 0);
		पूर्ण
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(st_nci_disable_se);

पूर्णांक st_nci_enable_se(काष्ठा nci_dev *ndev, u32 se_idx)
अणु
	पूर्णांक r;

	pr_debug("st_nci_enable_se\n");

	/*
	 * According to upper layer, se_idx == NFC_SE_UICC when
	 * info->se_info.se_status->is_uicc_enable is true should never happen.
	 * Same क्रम eSE.
	 */
	r = st_nci_control_se(ndev, se_idx, ST_NCI_SE_MODE_ON);
	अगर (r == ST_NCI_ESE_HOST_ID) अणु
		st_nci_se_get_atr(ndev);
		r = nci_hci_send_event(ndev, ST_NCI_APDU_READER_GATE,
				ST_NCI_EVT_SE_SOFT_RESET, शून्य, 0);
	पूर्ण

	अगर (r < 0) अणु
		/*
		 * The activation procedure failed, the secure element
		 * is not connected. Remove from the list.
		 */
		nfc_हटाओ_se(ndev->nfc_dev, se_idx);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(st_nci_enable_se);

अटल पूर्णांक st_nci_hci_network_init(काष्ठा nci_dev *ndev)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा core_conn_create_dest_spec_params *dest_params;
	काष्ठा dest_spec_params spec_params;
	काष्ठा nci_conn_info    *conn_info;
	पूर्णांक r, dev_num;

	dest_params =
		kzalloc(माप(काष्ठा core_conn_create_dest_spec_params) +
			माप(काष्ठा dest_spec_params), GFP_KERNEL);
	अगर (dest_params == शून्य) अणु
		r = -ENOMEM;
		जाओ निकास;
	पूर्ण

	dest_params->type = NCI_DESTINATION_SPECIFIC_PARAM_NFCEE_TYPE;
	dest_params->length = माप(काष्ठा dest_spec_params);
	spec_params.id = ndev->hci_dev->nfcee_id;
	spec_params.protocol = NCI_NFCEE_INTERFACE_HCI_ACCESS;
	स_नकल(dest_params->value, &spec_params,
	       माप(काष्ठा dest_spec_params));
	r = nci_core_conn_create(ndev, NCI_DESTINATION_NFCEE, 1,
				 माप(काष्ठा core_conn_create_dest_spec_params) +
				 माप(काष्ठा dest_spec_params),
				 dest_params);
	अगर (r != NCI_STATUS_OK)
		जाओ मुक्त_dest_params;

	conn_info = ndev->hci_dev->conn_info;
	अगर (!conn_info)
		जाओ मुक्त_dest_params;

	ndev->hci_dev->init_data.gate_count = ARRAY_SIZE(st_nci_gates);
	स_नकल(ndev->hci_dev->init_data.gates, st_nci_gates,
	       माप(st_nci_gates));

	/*
	 * Session id must include the driver name + i2c bus addr
	 * persistent info to discriminate 2 identical chips
	 */
	dev_num = find_first_zero_bit(dev_mask, ST_NCI_NUM_DEVICES);
	अगर (dev_num >= ST_NCI_NUM_DEVICES) अणु
		r = -ENODEV;
		जाओ मुक्त_dest_params;
	पूर्ण

	scnम_लिखो(ndev->hci_dev->init_data.session_id,
		  माप(ndev->hci_dev->init_data.session_id),
		  "%s%2x", "ST21BH", dev_num);

	r = nci_hci_dev_session_init(ndev);
	अगर (r != NCI_HCI_ANY_OK)
		जाओ मुक्त_dest_params;

	/*
	 * In factory mode, we prevent secure elements activation
	 * by disabling nfcee on the current HCI connection id.
	 * HCI will be used here only क्रम proprietary commands.
	 */
	अगर (test_bit(ST_NCI_FACTORY_MODE, &info->flags))
		r = nci_nfcee_mode_set(ndev,
				       ndev->hci_dev->conn_info->dest_params->id,
				       NCI_NFCEE_DISABLE);
	अन्यथा
		r = nci_nfcee_mode_set(ndev,
				       ndev->hci_dev->conn_info->dest_params->id,
				       NCI_NFCEE_ENABLE);

मुक्त_dest_params:
	kमुक्त(dest_params);

निकास:
	वापस r;
पूर्ण

पूर्णांक st_nci_discover_se(काष्ठा nci_dev *ndev)
अणु
	u8 white_list[2];
	पूर्णांक r, wl_size = 0;
	पूर्णांक se_count = 0;
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	pr_debug("st_nci_discover_se\n");

	r = st_nci_hci_network_init(ndev);
	अगर (r != 0)
		वापस r;

	अगर (test_bit(ST_NCI_FACTORY_MODE, &info->flags))
		वापस 0;

	अगर (info->se_info.se_status->is_uicc_present)
		white_list[wl_size++] = ST_NCI_UICC_HOST_ID;
	अगर (info->se_info.se_status->is_ese_present)
		white_list[wl_size++] = ST_NCI_ESE_HOST_ID;

	अगर (wl_size) अणु
		r = nci_hci_set_param(ndev, NCI_HCI_ADMIN_GATE,
				      NCI_HCI_ADMIN_PARAM_WHITELIST,
				      white_list, wl_size);
		अगर (r != NCI_HCI_ANY_OK)
			वापस r;
	पूर्ण

	अगर (info->se_info.se_status->is_uicc_present) अणु
		nfc_add_se(ndev->nfc_dev, ST_NCI_UICC_HOST_ID, NFC_SE_UICC);
		se_count++;
	पूर्ण

	अगर (info->se_info.se_status->is_ese_present) अणु
		nfc_add_se(ndev->nfc_dev, ST_NCI_ESE_HOST_ID, NFC_SE_EMBEDDED);
		se_count++;
	पूर्ण

	वापस !se_count;
पूर्ण
EXPORT_SYMBOL_GPL(st_nci_discover_se);

पूर्णांक st_nci_se_io(काष्ठा nci_dev *ndev, u32 se_idx,
		       u8 *apdu, माप_प्रकार apdu_length,
		       se_io_cb_t cb, व्योम *cb_context)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	pr_debug("\n");

	चयन (se_idx) अणु
	हाल ST_NCI_ESE_HOST_ID:
		info->se_info.cb = cb;
		info->se_info.cb_context = cb_context;
		mod_समयr(&info->se_info.bwi_समयr, jअगरfies +
			  msecs_to_jअगरfies(info->se_info.wt_समयout));
		info->se_info.bwi_active = true;
		वापस nci_hci_send_event(ndev, ST_NCI_APDU_READER_GATE,
					ST_NCI_EVT_TRANSMIT_DATA, apdu,
					apdu_length);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(st_nci_se_io);

अटल व्योम st_nci_se_wt_समयout(काष्ठा समयr_list *t)
अणु
	/*
	 * No answer from the secure element
	 * within the defined समयout.
	 * Let's send a reset request as recovery procedure.
	 * According to the situation, we first try to send a software reset
	 * to the secure element. If the next command is still not
	 * answering in समय, we send to the CLF a secure element hardware
	 * reset request.
	 */
	/* hardware reset managed through VCC_UICC_OUT घातer supply */
	u8 param = 0x01;
	काष्ठा st_nci_info *info = from_समयr(info, t, se_info.bwi_समयr);

	pr_debug("\n");

	info->se_info.bwi_active = false;

	अगर (!info->se_info.xch_error) अणु
		info->se_info.xch_error = true;
		nci_hci_send_event(info->ndlc->ndev, ST_NCI_APDU_READER_GATE,
				ST_NCI_EVT_SE_SOFT_RESET, शून्य, 0);
	पूर्ण अन्यथा अणु
		info->se_info.xch_error = false;
		nci_hci_send_event(info->ndlc->ndev, ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_EVT_SE_HARD_RESET, &param, 1);
	पूर्ण
	info->se_info.cb(info->se_info.cb_context, शून्य, 0, -ETIME);
पूर्ण

अटल व्योम st_nci_se_activation_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा st_nci_info *info = from_समयr(info, t,
					      se_info.se_active_समयr);

	pr_debug("\n");

	info->se_info.se_active = false;

	complete(&info->se_info.req_completion);
पूर्ण

पूर्णांक st_nci_se_init(काष्ठा nci_dev *ndev, काष्ठा st_nci_se_status *se_status)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	init_completion(&info->se_info.req_completion);
	/* initialize समयrs */
	समयr_setup(&info->se_info.bwi_समयr, st_nci_se_wt_समयout, 0);
	info->se_info.bwi_active = false;

	समयr_setup(&info->se_info.se_active_समयr,
		    st_nci_se_activation_समयout, 0);
	info->se_info.se_active = false;

	info->se_info.xch_error = false;

	info->se_info.wt_समयout =
		ST_NCI_BWI_TO_TIMEOUT(ST_NCI_ATR_DEFAULT_BWI);

	info->se_info.se_status = se_status;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st_nci_se_init);

व्योम st_nci_se_deinit(काष्ठा nci_dev *ndev)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	अगर (info->se_info.bwi_active)
		del_समयr_sync(&info->se_info.bwi_समयr);
	अगर (info->se_info.se_active)
		del_समयr_sync(&info->se_info.se_active_समयr);

	info->se_info.se_active = false;
	info->se_info.bwi_active = false;
पूर्ण
EXPORT_SYMBOL(st_nci_se_deinit);

