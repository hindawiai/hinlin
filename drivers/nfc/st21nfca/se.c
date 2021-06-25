<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014  STMicroelectronics SAS. All rights reserved.
 */

#समावेश <net/nfc/hci.h>

#समावेश "st21nfca.h"

#घोषणा ST21NFCA_EVT_UICC_ACTIVATE		0x10
#घोषणा ST21NFCA_EVT_UICC_DEACTIVATE		0x13
#घोषणा ST21NFCA_EVT_SE_HARD_RESET		0x20
#घोषणा ST21NFCA_EVT_SE_SOFT_RESET		0x11
#घोषणा ST21NFCA_EVT_SE_END_OF_APDU_TRANSFER	0x21
#घोषणा ST21NFCA_EVT_SE_ACTIVATE		0x22
#घोषणा ST21NFCA_EVT_SE_DEACTIVATE		0x23

#घोषणा ST21NFCA_EVT_TRANSMIT_DATA		0x10
#घोषणा ST21NFCA_EVT_WTX_REQUEST		0x11

#घोषणा ST21NFCA_EVT_CONNECTIVITY		0x10
#घोषणा ST21NFCA_EVT_TRANSACTION		0x12

#घोषणा ST21NFCA_SE_TO_HOT_PLUG			1000
/* Connectivity pipe only */
#घोषणा ST21NFCA_SE_COUNT_PIPE_UICC		0x01
/* Connectivity + APDU Reader pipe */
#घोषणा ST21NFCA_SE_COUNT_PIPE_EMBEDDED	0x02

#घोषणा ST21NFCA_SE_MODE_OFF			0x00
#घोषणा ST21NFCA_SE_MODE_ON				0x01

#घोषणा ST21NFCA_PARAM_ATR				0x01
#घोषणा ST21NFCA_ATR_DEFAULT_BWI		0x04

/*
 * WT = 2^BWI/10[s], convert पूर्णांकo msecs and add a secure
 * room by increasing by 2 this समयout
 */
#घोषणा ST21NFCA_BWI_TO_TIMEOUT(x)		((1 << x) * 200)
#घोषणा ST21NFCA_ATR_GET_Y_FROM_TD(x)	(x >> 4)

/* If TA is present bit 0 is set */
#घोषणा ST21NFCA_ATR_TA_PRESENT(x) (x & 0x01)
/* If TB is present bit 1 is set */
#घोषणा ST21NFCA_ATR_TB_PRESENT(x) (x & 0x02)

अटल u8 st21nfca_se_get_bwi(काष्ठा nfc_hci_dev *hdev)
अणु
	पूर्णांक i;
	u8 td;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	/* Bits 8 to 5 of the first TB क्रम T=1 encode BWI from zero to nine */
	क्रम (i = 1; i < ST21NFCA_ESE_MAX_LENGTH; i++) अणु
		td = ST21NFCA_ATR_GET_Y_FROM_TD(info->se_info.atr[i]);
		अगर (ST21NFCA_ATR_TA_PRESENT(td))
			i++;
		अगर (ST21NFCA_ATR_TB_PRESENT(td)) अणु
			i++;
			वापस info->se_info.atr[i] >> 4;
		पूर्ण
	पूर्ण
	वापस ST21NFCA_ATR_DEFAULT_BWI;
पूर्ण

अटल व्योम st21nfca_se_get_atr(काष्ठा nfc_hci_dev *hdev)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *skb;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	r = nfc_hci_get_param(hdev, ST21NFCA_APDU_READER_GATE,
			ST21NFCA_PARAM_ATR, &skb);
	अगर (r < 0)
		वापस;

	अगर (skb->len <= ST21NFCA_ESE_MAX_LENGTH) अणु
		स_नकल(info->se_info.atr, skb->data, skb->len);
		info->se_info.wt_समयout =
			ST21NFCA_BWI_TO_TIMEOUT(st21nfca_se_get_bwi(hdev));
	पूर्ण
	kमुक्त_skb(skb);
पूर्ण

अटल पूर्णांक st21nfca_hci_control_se(काष्ठा nfc_hci_dev *hdev, u32 se_idx,
				u8 state)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	पूर्णांक r, i;
	काष्ठा sk_buff *sk_host_list;
	u8 se_event, host_id;

	चयन (se_idx) अणु
	हाल NFC_HCI_UICC_HOST_ID:
		se_event = (state == ST21NFCA_SE_MODE_ON ?
					ST21NFCA_EVT_UICC_ACTIVATE :
					ST21NFCA_EVT_UICC_DEACTIVATE);

		info->se_info.count_pipes = 0;
		info->se_info.expected_pipes = ST21NFCA_SE_COUNT_PIPE_UICC;
		अवरोध;
	हाल ST21NFCA_ESE_HOST_ID:
		se_event = (state == ST21NFCA_SE_MODE_ON ?
					ST21NFCA_EVT_SE_ACTIVATE :
					ST21NFCA_EVT_SE_DEACTIVATE);

		info->se_info.count_pipes = 0;
		info->se_info.expected_pipes = ST21NFCA_SE_COUNT_PIPE_EMBEDDED;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Wait क्रम an EVT_HOT_PLUG in order to
	 * retrieve a relevant host list.
	 */
	reinit_completion(&info->se_info.req_completion);
	r = nfc_hci_send_event(hdev, ST21NFCA_DEVICE_MGNT_GATE, se_event,
			       शून्य, 0);
	अगर (r < 0)
		वापस r;

	mod_समयr(&info->se_info.se_active_समयr, jअगरfies +
		msecs_to_jअगरfies(ST21NFCA_SE_TO_HOT_PLUG));
	info->se_info.se_active = true;

	/* Ignore वापस value and check in any हाल the host_list */
	रुको_क्रम_completion_पूर्णांकerruptible(&info->se_info.req_completion);

	r = nfc_hci_get_param(hdev, NFC_HCI_ADMIN_GATE,
			NFC_HCI_ADMIN_HOST_LIST,
			&sk_host_list);
	अगर (r < 0)
		वापस r;

	क्रम (i = 0; i < sk_host_list->len &&
		sk_host_list->data[i] != se_idx; i++)
		;
	host_id = sk_host_list->data[i];
	kमुक्त_skb(sk_host_list);

	अगर (state == ST21NFCA_SE_MODE_ON && host_id == se_idx)
		वापस se_idx;
	अन्यथा अगर (state == ST21NFCA_SE_MODE_OFF && host_id != se_idx)
		वापस se_idx;

	वापस -1;
पूर्ण

पूर्णांक st21nfca_hci_discover_se(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	पूर्णांक se_count = 0;

	अगर (test_bit(ST21NFCA_FACTORY_MODE, &hdev->quirks))
		वापस 0;

	अगर (info->se_status->is_uicc_present) अणु
		nfc_add_se(hdev->ndev, NFC_HCI_UICC_HOST_ID, NFC_SE_UICC);
		se_count++;
	पूर्ण

	अगर (info->se_status->is_ese_present) अणु
		nfc_add_se(hdev->ndev, ST21NFCA_ESE_HOST_ID, NFC_SE_EMBEDDED);
		se_count++;
	पूर्ण

	वापस !se_count;
पूर्ण
EXPORT_SYMBOL(st21nfca_hci_discover_se);

पूर्णांक st21nfca_hci_enable_se(काष्ठा nfc_hci_dev *hdev, u32 se_idx)
अणु
	पूर्णांक r;

	/*
	 * According to upper layer, se_idx == NFC_SE_UICC when
	 * info->se_status->is_uicc_enable is true should never happen.
	 * Same क्रम eSE.
	 */
	r = st21nfca_hci_control_se(hdev, se_idx, ST21NFCA_SE_MODE_ON);
	अगर (r == ST21NFCA_ESE_HOST_ID) अणु
		st21nfca_se_get_atr(hdev);
		r = nfc_hci_send_event(hdev, ST21NFCA_APDU_READER_GATE,
				ST21NFCA_EVT_SE_SOFT_RESET, शून्य, 0);
		अगर (r < 0)
			वापस r;
	पूर्ण अन्यथा अगर (r < 0) अणु
		/*
		 * The activation tentative failed, the secure element
		 * is not connected. Remove from the list.
		 */
		nfc_हटाओ_se(hdev->ndev, se_idx);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st21nfca_hci_enable_se);

पूर्णांक st21nfca_hci_disable_se(काष्ठा nfc_hci_dev *hdev, u32 se_idx)
अणु
	पूर्णांक r;

	/*
	 * According to upper layer, se_idx == NFC_SE_UICC when
	 * info->se_status->is_uicc_enable is true should never happen
	 * Same क्रम eSE.
	 */
	r = st21nfca_hci_control_se(hdev, se_idx, ST21NFCA_SE_MODE_OFF);
	अगर (r < 0)
		वापस r;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st21nfca_hci_disable_se);

पूर्णांक st21nfca_hci_se_io(काष्ठा nfc_hci_dev *hdev, u32 se_idx,
			u8 *apdu, माप_प्रकार apdu_length,
			se_io_cb_t cb, व्योम *cb_context)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	pr_debug("se_io %x\n", se_idx);

	चयन (se_idx) अणु
	हाल ST21NFCA_ESE_HOST_ID:
		info->se_info.cb = cb;
		info->se_info.cb_context = cb_context;
		mod_समयr(&info->se_info.bwi_समयr, jअगरfies +
			  msecs_to_jअगरfies(info->se_info.wt_समयout));
		info->se_info.bwi_active = true;
		वापस nfc_hci_send_event(hdev, ST21NFCA_APDU_READER_GATE,
					ST21NFCA_EVT_TRANSMIT_DATA,
					apdu, apdu_length);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(st21nfca_hci_se_io);

अटल व्योम st21nfca_se_wt_समयout(काष्ठा समयr_list *t)
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
	काष्ठा st21nfca_hci_info *info = from_समयr(info, t,
						    se_info.bwi_समयr);

	pr_debug("\n");

	info->se_info.bwi_active = false;

	अगर (!info->se_info.xch_error) अणु
		info->se_info.xch_error = true;
		nfc_hci_send_event(info->hdev, ST21NFCA_APDU_READER_GATE,
				ST21NFCA_EVT_SE_SOFT_RESET, शून्य, 0);
	पूर्ण अन्यथा अणु
		info->se_info.xch_error = false;
		nfc_hci_send_event(info->hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_EVT_SE_HARD_RESET, &param, 1);
	पूर्ण
	info->se_info.cb(info->se_info.cb_context, शून्य, 0, -ETIME);
पूर्ण

अटल व्योम st21nfca_se_activation_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा st21nfca_hci_info *info = from_समयr(info, t,
						    se_info.se_active_समयr);

	pr_debug("\n");

	info->se_info.se_active = false;

	complete(&info->se_info.req_completion);
पूर्ण

/*
 * Returns:
 * <= 0: driver handled the event, skb consumed
 *    1: driver करोes not handle the event, please करो standard processing
 */
पूर्णांक st21nfca_connectivity_event_received(काष्ठा nfc_hci_dev *hdev, u8 host,
				u8 event, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r = 0;
	काष्ठा device *dev = &hdev->ndev->dev;
	काष्ठा nfc_evt_transaction *transaction;

	pr_debug("connectivity gate event: %x\n", event);

	चयन (event) अणु
	हाल ST21NFCA_EVT_CONNECTIVITY:
		r = nfc_se_connectivity(hdev->ndev, host);
	अवरोध;
	हाल ST21NFCA_EVT_TRANSACTION:
		/*
		 * According to specअगरication etsi 102 622
		 * 11.2.2.4 EVT_TRANSACTION Table 52
		 * Description	Tag	Length
		 * AID		81	5 to 16
		 * PARAMETERS	82	0 to 255
		 */
		अगर (skb->len < NFC_MIN_AID_LENGTH + 2 &&
		    skb->data[0] != NFC_EVT_TRANSACTION_AID_TAG)
			वापस -EPROTO;

		transaction = devm_kzalloc(dev, skb->len - 2, GFP_KERNEL);
		अगर (!transaction)
			वापस -ENOMEM;

		transaction->aid_len = skb->data[1];
		स_नकल(transaction->aid, &skb->data[2],
		       transaction->aid_len);

		/* Check next byte is PARAMETERS tag (82) */
		अगर (skb->data[transaction->aid_len + 2] !=
		    NFC_EVT_TRANSACTION_PARAMS_TAG)
			वापस -EPROTO;

		transaction->params_len = skb->data[transaction->aid_len + 3];
		स_नकल(transaction->params, skb->data +
		       transaction->aid_len + 4, transaction->params_len);

		r = nfc_se_transaction(hdev->ndev, host, transaction);
	अवरोध;
	शेष:
		nfc_err(&hdev->ndev->dev, "Unexpected event on connectivity gate\n");
		वापस 1;
	पूर्ण
	kमुक्त_skb(skb);
	वापस r;
पूर्ण
EXPORT_SYMBOL(st21nfca_connectivity_event_received);

पूर्णांक st21nfca_apdu_पढ़ोer_event_received(काष्ठा nfc_hci_dev *hdev,
					u8 event, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r = 0;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	pr_debug("apdu reader gate event: %x\n", event);

	चयन (event) अणु
	हाल ST21NFCA_EVT_TRANSMIT_DATA:
		del_समयr_sync(&info->se_info.bwi_समयr);
		info->se_info.bwi_active = false;
		r = nfc_hci_send_event(hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_EVT_SE_END_OF_APDU_TRANSFER, शून्य, 0);
		अगर (r < 0)
			जाओ निकास;

		info->se_info.cb(info->se_info.cb_context,
			skb->data, skb->len, 0);
		अवरोध;
	हाल ST21NFCA_EVT_WTX_REQUEST:
		mod_समयr(&info->se_info.bwi_समयr, jअगरfies +
				msecs_to_jअगरfies(info->se_info.wt_समयout));
		अवरोध;
	शेष:
		nfc_err(&hdev->ndev->dev, "Unexpected event on apdu reader gate\n");
		वापस 1;
	पूर्ण

निकास:
	kमुक्त_skb(skb);
	वापस r;
पूर्ण
EXPORT_SYMBOL(st21nfca_apdu_पढ़ोer_event_received);

व्योम st21nfca_se_init(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	init_completion(&info->se_info.req_completion);
	/* initialize समयrs */
	समयr_setup(&info->se_info.bwi_समयr, st21nfca_se_wt_समयout, 0);
	info->se_info.bwi_active = false;

	समयr_setup(&info->se_info.se_active_समयr,
		    st21nfca_se_activation_समयout, 0);
	info->se_info.se_active = false;

	info->se_info.count_pipes = 0;
	info->se_info.expected_pipes = 0;

	info->se_info.xch_error = false;

	info->se_info.wt_समयout =
			ST21NFCA_BWI_TO_TIMEOUT(ST21NFCA_ATR_DEFAULT_BWI);
पूर्ण
EXPORT_SYMBOL(st21nfca_se_init);

व्योम st21nfca_se_deinit(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	अगर (info->se_info.bwi_active)
		del_समयr_sync(&info->se_info.bwi_समयr);
	अगर (info->se_info.se_active)
		del_समयr_sync(&info->se_info.se_active_समयr);

	info->se_info.bwi_active = false;
	info->se_info.se_active = false;
पूर्ण
EXPORT_SYMBOL(st21nfca_se_deinit);
