<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "hci: %s: " fmt, __func__

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <net/nfc/hci.h>

#समावेश "hci.h"

/*
 * Payload is the HCP message data only. Inकाष्ठाion will be prepended.
 * Guarantees that cb will be called upon completion or समयout delay
 * counted from the moment the cmd is sent to the transport.
 */
पूर्णांक nfc_hci_hcp_message_tx(काष्ठा nfc_hci_dev *hdev, u8 pipe,
			   u8 type, u8 inकाष्ठाion,
			   स्थिर u8 *payload, माप_प्रकार payload_len,
			   data_exchange_cb_t cb, व्योम *cb_context,
			   अचिन्हित दीर्घ completion_delay)
अणु
	काष्ठा nfc_dev *ndev = hdev->ndev;
	काष्ठा hci_msg *cmd;
	स्थिर u8 *ptr = payload;
	पूर्णांक hci_len, err;
	bool firstfrag = true;

	cmd = kzalloc(माप(काष्ठा hci_msg), GFP_KERNEL);
	अगर (cmd == शून्य)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&cmd->msg_l);
	skb_queue_head_init(&cmd->msg_frags);
	cmd->रुको_response = (type == NFC_HCI_HCP_COMMAND) ? true : false;
	cmd->cb = cb;
	cmd->cb_context = cb_context;
	cmd->completion_delay = completion_delay;

	hci_len = payload_len + 1;
	जबतक (hci_len > 0) अणु
		काष्ठा sk_buff *skb;
		पूर्णांक skb_len, data_link_len;
		काष्ठा hcp_packet *packet;

		अगर (NFC_HCI_HCP_PACKET_HEADER_LEN + hci_len <=
		    hdev->max_data_link_payload)
			data_link_len = hci_len;
		अन्यथा
			data_link_len = hdev->max_data_link_payload -
					NFC_HCI_HCP_PACKET_HEADER_LEN;

		skb_len = ndev->tx_headroom + NFC_HCI_HCP_PACKET_HEADER_LEN +
			  data_link_len + ndev->tx_tailroom;
		hci_len -= data_link_len;

		skb = alloc_skb(skb_len, GFP_KERNEL);
		अगर (skb == शून्य) अणु
			err = -ENOMEM;
			जाओ out_skb_err;
		पूर्ण
		skb_reserve(skb, ndev->tx_headroom);

		skb_put(skb, NFC_HCI_HCP_PACKET_HEADER_LEN + data_link_len);

		/* Only the last fragment will have the cb bit set to 1 */
		packet = (काष्ठा hcp_packet *)skb->data;
		packet->header = pipe;
		अगर (firstfrag) अणु
			firstfrag = false;
			packet->message.header = HCP_HEADER(type, inकाष्ठाion);
			अगर (ptr) अणु
				स_नकल(packet->message.data, ptr,
				       data_link_len - 1);
				ptr += data_link_len - 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(&packet->message, ptr, data_link_len);
			ptr += data_link_len;
		पूर्ण

		/* This is the last fragment, set the cb bit */
		अगर (hci_len == 0)
			packet->header |= ~NFC_HCI_FRAGMENT;

		skb_queue_tail(&cmd->msg_frags, skb);
	पूर्ण

	mutex_lock(&hdev->msg_tx_mutex);

	अगर (hdev->shutting_करोwn) अणु
		err = -ESHUTDOWN;
		mutex_unlock(&hdev->msg_tx_mutex);
		जाओ out_skb_err;
	पूर्ण

	list_add_tail(&cmd->msg_l, &hdev->msg_tx_queue);
	mutex_unlock(&hdev->msg_tx_mutex);

	schedule_work(&hdev->msg_tx_work);

	वापस 0;

out_skb_err:
	skb_queue_purge(&cmd->msg_frags);
	kमुक्त(cmd);

	वापस err;
पूर्ण

/*
 * Receive hcp message क्रम pipe, with type and cmd.
 * skb contains optional message data only.
 */
व्योम nfc_hci_hcp_message_rx(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 type,
			    u8 inकाष्ठाion, काष्ठा sk_buff *skb)
अणु
	चयन (type) अणु
	हाल NFC_HCI_HCP_RESPONSE:
		nfc_hci_resp_received(hdev, inकाष्ठाion, skb);
		अवरोध;
	हाल NFC_HCI_HCP_COMMAND:
		nfc_hci_cmd_received(hdev, pipe, inकाष्ठाion, skb);
		अवरोध;
	हाल NFC_HCI_HCP_EVENT:
		nfc_hci_event_received(hdev, pipe, inकाष्ठाion, skb);
		अवरोध;
	शेष:
		pr_err("UNKNOWN MSG Type %d, instruction=%d\n",
		       type, inकाष्ठाion);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण
