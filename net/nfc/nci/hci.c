<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  The NFC Controller Interface is the communication protocol between an
 *  NFC Controller (NFCC) and a Device Host (DH).
 *  This is the HCI over NCI implementation, as specअगरied in the 10.2
 *  section of the NCI 1.1 specअगरication.
 *
 *  Copyright (C) 2014  STMicroelectronics SAS. All rights reserved.
 */

#समावेश <linux/skbuff.h>

#समावेश "../nfc.h"
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश <linux/nfc.h>

काष्ठा nci_data अणु
	u8              conn_id;
	u8              pipe;
	u8              cmd;
	स्थिर u8        *data;
	u32             data_len;
पूर्ण __packed;

काष्ठा nci_hci_create_pipe_params अणु
	u8 src_gate;
	u8 dest_host;
	u8 dest_gate;
पूर्ण __packed;

काष्ठा nci_hci_create_pipe_resp अणु
	u8 src_host;
	u8 src_gate;
	u8 dest_host;
	u8 dest_gate;
	u8 pipe;
पूर्ण __packed;

काष्ठा nci_hci_delete_pipe_noti अणु
	u8 pipe;
पूर्ण __packed;

काष्ठा nci_hci_all_pipe_cleared_noti अणु
	u8 host;
पूर्ण __packed;

काष्ठा nci_hcp_message अणु
	u8 header;      /* type -cmd,evt,rsp- + inकाष्ठाion */
	u8 data[];
पूर्ण __packed;

काष्ठा nci_hcp_packet अणु
	u8 header;      /* cbit+pipe */
	काष्ठा nci_hcp_message message;
पूर्ण __packed;

#घोषणा NCI_HCI_ANY_SET_PARAMETER  0x01
#घोषणा NCI_HCI_ANY_GET_PARAMETER  0x02
#घोषणा NCI_HCI_ANY_CLOSE_PIPE     0x04
#घोषणा NCI_HCI_ADM_CLEAR_ALL_PIPE 0x14

#घोषणा NCI_HFP_NO_CHAINING        0x80

#घोषणा NCI_NFCEE_ID_HCI                0x80

#घोषणा NCI_EVT_HOT_PLUG           0x03

#घोषणा NCI_HCI_ADMIN_PARAM_SESSION_IDENTITY       0x01
#घोषणा NCI_HCI_ADM_CREATE_PIPE			0x10
#घोषणा NCI_HCI_ADM_DELETE_PIPE			0x11

/* HCP headers */
#घोषणा NCI_HCI_HCP_PACKET_HEADER_LEN      1
#घोषणा NCI_HCI_HCP_MESSAGE_HEADER_LEN     1
#घोषणा NCI_HCI_HCP_HEADER_LEN             2

/* HCP types */
#घोषणा NCI_HCI_HCP_COMMAND        0x00
#घोषणा NCI_HCI_HCP_EVENT          0x01
#घोषणा NCI_HCI_HCP_RESPONSE       0x02

#घोषणा NCI_HCI_ADM_NOTIFY_PIPE_CREATED     0x12
#घोषणा NCI_HCI_ADM_NOTIFY_PIPE_DELETED     0x13
#घोषणा NCI_HCI_ADM_NOTIFY_ALL_PIPE_CLEARED 0x15

#घोषणा NCI_HCI_FRAGMENT           0x7f
#घोषणा NCI_HCP_HEADER(type, instr) ((((type) & 0x03) << 6) |\
				      ((instr) & 0x3f))

#घोषणा NCI_HCP_MSG_GET_TYPE(header) ((header & 0xc0) >> 6)
#घोषणा NCI_HCP_MSG_GET_CMD(header)  (header & 0x3f)
#घोषणा NCI_HCP_MSG_GET_PIPE(header) (header & 0x7f)

अटल पूर्णांक nci_hci_result_to_त्रुटि_सं(u8 result)
अणु
	चयन (result) अणु
	हाल NCI_HCI_ANY_OK:
		वापस 0;
	हाल NCI_HCI_ANY_E_REG_PAR_UNKNOWN:
		वापस -EOPNOTSUPP;
	हाल NCI_HCI_ANY_E_TIMEOUT:
		वापस -ETIME;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

/* HCI core */
अटल व्योम nci_hci_reset_pipes(काष्ठा nci_hci_dev *hdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NCI_HCI_MAX_PIPES; i++) अणु
		hdev->pipes[i].gate = NCI_HCI_INVALID_GATE;
		hdev->pipes[i].host = NCI_HCI_INVALID_HOST;
	पूर्ण
	स_रखो(hdev->gate2pipe, NCI_HCI_INVALID_PIPE, माप(hdev->gate2pipe));
पूर्ण

अटल व्योम nci_hci_reset_pipes_per_host(काष्ठा nci_dev *ndev, u8 host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NCI_HCI_MAX_PIPES; i++) अणु
		अगर (ndev->hci_dev->pipes[i].host == host) अणु
			ndev->hci_dev->pipes[i].gate = NCI_HCI_INVALID_GATE;
			ndev->hci_dev->pipes[i].host = NCI_HCI_INVALID_HOST;
		पूर्ण
	पूर्ण
पूर्ण

/* Fragment HCI data over NCI packet.
 * NFC Forum NCI 10.2.2 Data Exchange:
 * The payload of the Data Packets sent on the Logical Connection SHALL be
 * valid HCP packets, as defined within [ETSI_102622]. Each Data Packet SHALL
 * contain a single HCP packet. NCI Segmentation and Reassembly SHALL NOT be
 * applied to Data Messages in either direction. The HCI fragmentation mechanism
 * is used अगर required.
 */
अटल पूर्णांक nci_hci_send_data(काष्ठा nci_dev *ndev, u8 pipe,
			     स्थिर u8 data_type, स्थिर u8 *data,
			     माप_प्रकार data_len)
अणु
	काष्ठा nci_conn_info    *conn_info;
	काष्ठा sk_buff *skb;
	पूर्णांक len, i, r;
	u8 cb = pipe;

	conn_info = ndev->hci_dev->conn_info;
	अगर (!conn_info)
		वापस -EPROTO;

	i = 0;
	skb = nci_skb_alloc(ndev, conn_info->max_pkt_payload_len +
			    NCI_DATA_HDR_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, NCI_DATA_HDR_SIZE + 2);
	*(u8 *)skb_push(skb, 1) = data_type;

	करो अणु
		len = conn_info->max_pkt_payload_len;

		/* If last packet add NCI_HFP_NO_CHAINING */
		अगर (i + conn_info->max_pkt_payload_len -
		    (skb->len + 1) >= data_len) अणु
			cb |= NCI_HFP_NO_CHAINING;
			len = data_len - i;
		पूर्ण अन्यथा अणु
			len = conn_info->max_pkt_payload_len - skb->len - 1;
		पूर्ण

		*(u8 *)skb_push(skb, 1) = cb;

		अगर (len > 0)
			skb_put_data(skb, data + i, len);

		r = nci_send_data(ndev, conn_info->conn_id, skb);
		अगर (r < 0)
			वापस r;

		i += len;

		अगर (i < data_len) अणु
			skb = nci_skb_alloc(ndev,
					    conn_info->max_pkt_payload_len +
					    NCI_DATA_HDR_SIZE, GFP_KERNEL);
			अगर (!skb)
				वापस -ENOMEM;

			skb_reserve(skb, NCI_DATA_HDR_SIZE + 1);
		पूर्ण
	पूर्ण जबतक (i < data_len);

	वापस i;
पूर्ण

अटल व्योम nci_hci_send_data_req(काष्ठा nci_dev *ndev, अचिन्हित दीर्घ opt)
अणु
	काष्ठा nci_data *data = (काष्ठा nci_data *)opt;

	nci_hci_send_data(ndev, data->pipe, data->cmd,
			  data->data, data->data_len);
पूर्ण

पूर्णांक nci_hci_send_event(काष्ठा nci_dev *ndev, u8 gate, u8 event,
		       स्थिर u8 *param, माप_प्रकार param_len)
अणु
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	अगर (pipe == NCI_HCI_INVALID_PIPE)
		वापस -EADDRNOTAVAIL;

	वापस nci_hci_send_data(ndev, pipe,
			NCI_HCP_HEADER(NCI_HCI_HCP_EVENT, event),
			param, param_len);
पूर्ण
EXPORT_SYMBOL(nci_hci_send_event);

पूर्णांक nci_hci_send_cmd(काष्ठा nci_dev *ndev, u8 gate, u8 cmd,
		     स्थिर u8 *param, माप_प्रकार param_len,
		     काष्ठा sk_buff **skb)
अणु
	काष्ठा nci_hcp_message *message;
	काष्ठा nci_conn_info   *conn_info;
	काष्ठा nci_data data;
	पूर्णांक r;
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	अगर (pipe == NCI_HCI_INVALID_PIPE)
		वापस -EADDRNOTAVAIL;

	conn_info = ndev->hci_dev->conn_info;
	अगर (!conn_info)
		वापस -EPROTO;

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADER(NCI_HCI_HCP_COMMAND, cmd);
	data.data = param;
	data.data_len = param_len;

	r = nci_request(ndev, nci_hci_send_data_req, (अचिन्हित दीर्घ)&data,
			msecs_to_jअगरfies(NCI_DATA_TIMEOUT));
	अगर (r == NCI_STATUS_OK) अणु
		message = (काष्ठा nci_hcp_message *)conn_info->rx_skb->data;
		r = nci_hci_result_to_त्रुटि_सं(
			NCI_HCP_MSG_GET_CMD(message->header));
		skb_pull(conn_info->rx_skb, NCI_HCI_HCP_MESSAGE_HEADER_LEN);

		अगर (!r && skb)
			*skb = conn_info->rx_skb;
	पूर्ण

	वापस r;
पूर्ण
EXPORT_SYMBOL(nci_hci_send_cmd);

पूर्णांक nci_hci_clear_all_pipes(काष्ठा nci_dev *ndev)
अणु
	पूर्णांक r;

	r = nci_hci_send_cmd(ndev, NCI_HCI_ADMIN_GATE,
			     NCI_HCI_ADM_CLEAR_ALL_PIPE, शून्य, 0, शून्य);
	अगर (r < 0)
		वापस r;

	nci_hci_reset_pipes(ndev->hci_dev);
	वापस r;
पूर्ण
EXPORT_SYMBOL(nci_hci_clear_all_pipes);

अटल व्योम nci_hci_event_received(काष्ठा nci_dev *ndev, u8 pipe,
				   u8 event, काष्ठा sk_buff *skb)
अणु
	अगर (ndev->ops->hci_event_received)
		ndev->ops->hci_event_received(ndev, pipe, event, skb);
पूर्ण

अटल व्योम nci_hci_cmd_received(काष्ठा nci_dev *ndev, u8 pipe,
				 u8 cmd, काष्ठा sk_buff *skb)
अणु
	u8 gate = ndev->hci_dev->pipes[pipe].gate;
	u8 status = NCI_HCI_ANY_OK | ~NCI_HCI_FRAGMENT;
	u8 dest_gate, new_pipe;
	काष्ठा nci_hci_create_pipe_resp *create_info;
	काष्ठा nci_hci_delete_pipe_noti *delete_info;
	काष्ठा nci_hci_all_pipe_cleared_noti *cleared_info;

	pr_debug("from gate %x pipe %x cmd %x\n", gate, pipe, cmd);

	चयन (cmd) अणु
	हाल NCI_HCI_ADM_NOTIFY_PIPE_CREATED:
		अगर (skb->len != 5) अणु
			status = NCI_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण
		create_info = (काष्ठा nci_hci_create_pipe_resp *)skb->data;
		dest_gate = create_info->dest_gate;
		new_pipe = create_info->pipe;
		अगर (new_pipe >= NCI_HCI_MAX_PIPES) अणु
			status = NCI_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण

		/* Save the new created pipe and bind with local gate,
		 * the description क्रम skb->data[3] is destination gate id
		 * but since we received this cmd from host controller, we
		 * are the destination and it is our local gate
		 */
		ndev->hci_dev->gate2pipe[dest_gate] = new_pipe;
		ndev->hci_dev->pipes[new_pipe].gate = dest_gate;
		ndev->hci_dev->pipes[new_pipe].host =
						create_info->src_host;
		अवरोध;
	हाल NCI_HCI_ANY_OPEN_PIPE:
		/* If the pipe is not created report an error */
		अगर (gate == NCI_HCI_INVALID_GATE) अणु
			status = NCI_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण
		अवरोध;
	हाल NCI_HCI_ADM_NOTIFY_PIPE_DELETED:
		अगर (skb->len != 1) अणु
			status = NCI_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण
		delete_info = (काष्ठा nci_hci_delete_pipe_noti *)skb->data;
		अगर (delete_info->pipe >= NCI_HCI_MAX_PIPES) अणु
			status = NCI_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण

		ndev->hci_dev->pipes[delete_info->pipe].gate =
						NCI_HCI_INVALID_GATE;
		ndev->hci_dev->pipes[delete_info->pipe].host =
						NCI_HCI_INVALID_HOST;
		अवरोध;
	हाल NCI_HCI_ADM_NOTIFY_ALL_PIPE_CLEARED:
		अगर (skb->len != 1) अणु
			status = NCI_HCI_ANY_E_NOK;
			जाओ निकास;
		पूर्ण

		cleared_info =
			(काष्ठा nci_hci_all_pipe_cleared_noti *)skb->data;
		nci_hci_reset_pipes_per_host(ndev, cleared_info->host);
		अवरोध;
	शेष:
		pr_debug("Discarded unknown cmd %x to gate %x\n", cmd, gate);
		अवरोध;
	पूर्ण

	अगर (ndev->ops->hci_cmd_received)
		ndev->ops->hci_cmd_received(ndev, pipe, cmd, skb);

निकास:
	nci_hci_send_data(ndev, pipe, status, शून्य, 0);

	kमुक्त_skb(skb);
पूर्ण

अटल व्योम nci_hci_resp_received(काष्ठा nci_dev *ndev, u8 pipe,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_conn_info    *conn_info;

	conn_info = ndev->hci_dev->conn_info;
	अगर (!conn_info)
		जाओ निकास;

	conn_info->rx_skb = skb;

निकास:
	nci_req_complete(ndev, NCI_STATUS_OK);
पूर्ण

/* Receive hcp message क्रम pipe, with type and cmd.
 * skb contains optional message data only.
 */
अटल व्योम nci_hci_hcp_message_rx(काष्ठा nci_dev *ndev, u8 pipe,
				   u8 type, u8 inकाष्ठाion, काष्ठा sk_buff *skb)
अणु
	चयन (type) अणु
	हाल NCI_HCI_HCP_RESPONSE:
		nci_hci_resp_received(ndev, pipe, skb);
		अवरोध;
	हाल NCI_HCI_HCP_COMMAND:
		nci_hci_cmd_received(ndev, pipe, inकाष्ठाion, skb);
		अवरोध;
	हाल NCI_HCI_HCP_EVENT:
		nci_hci_event_received(ndev, pipe, inकाष्ठाion, skb);
		अवरोध;
	शेष:
		pr_err("UNKNOWN MSG Type %d, instruction=%d\n",
		       type, inकाष्ठाion);
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण

	nci_req_complete(ndev, NCI_STATUS_OK);
पूर्ण

अटल व्योम nci_hci_msg_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nci_hci_dev *hdev =
		container_of(work, काष्ठा nci_hci_dev, msg_rx_work);
	काष्ठा sk_buff *skb;
	काष्ठा nci_hcp_message *message;
	u8 pipe, type, inकाष्ठाion;

	जबतक ((skb = skb_dequeue(&hdev->msg_rx_queue)) != शून्य) अणु
		pipe = NCI_HCP_MSG_GET_PIPE(skb->data[0]);
		skb_pull(skb, NCI_HCI_HCP_PACKET_HEADER_LEN);
		message = (काष्ठा nci_hcp_message *)skb->data;
		type = NCI_HCP_MSG_GET_TYPE(message->header);
		inकाष्ठाion = NCI_HCP_MSG_GET_CMD(message->header);
		skb_pull(skb, NCI_HCI_HCP_MESSAGE_HEADER_LEN);

		nci_hci_hcp_message_rx(hdev->ndev, pipe,
				       type, inकाष्ठाion, skb);
	पूर्ण
पूर्ण

व्योम nci_hci_data_received_cb(व्योम *context,
			      काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा nci_dev *ndev = (काष्ठा nci_dev *)context;
	काष्ठा nci_hcp_packet *packet;
	u8 pipe, type;
	काष्ठा sk_buff *hcp_skb;
	काष्ठा sk_buff *frag_skb;
	पूर्णांक msg_len;

	pr_debug("\n");

	अगर (err) अणु
		nci_req_complete(ndev, err);
		वापस;
	पूर्ण

	packet = (काष्ठा nci_hcp_packet *)skb->data;
	अगर ((packet->header & ~NCI_HCI_FRAGMENT) == 0) अणु
		skb_queue_tail(&ndev->hci_dev->rx_hcp_frags, skb);
		वापस;
	पूर्ण

	/* it's the last fragment. Does it need re-aggregation? */
	अगर (skb_queue_len(&ndev->hci_dev->rx_hcp_frags)) अणु
		pipe = NCI_HCP_MSG_GET_PIPE(packet->header);
		skb_queue_tail(&ndev->hci_dev->rx_hcp_frags, skb);

		msg_len = 0;
		skb_queue_walk(&ndev->hci_dev->rx_hcp_frags, frag_skb) अणु
			msg_len += (frag_skb->len -
				    NCI_HCI_HCP_PACKET_HEADER_LEN);
		पूर्ण

		hcp_skb = nfc_alloc_recv_skb(NCI_HCI_HCP_PACKET_HEADER_LEN +
					     msg_len, GFP_KERNEL);
		अगर (!hcp_skb) अणु
			nci_req_complete(ndev, -ENOMEM);
			वापस;
		पूर्ण

		skb_put_u8(hcp_skb, pipe);

		skb_queue_walk(&ndev->hci_dev->rx_hcp_frags, frag_skb) अणु
			msg_len = frag_skb->len - NCI_HCI_HCP_PACKET_HEADER_LEN;
			skb_put_data(hcp_skb,
				     frag_skb->data + NCI_HCI_HCP_PACKET_HEADER_LEN,
				     msg_len);
		पूर्ण

		skb_queue_purge(&ndev->hci_dev->rx_hcp_frags);
	पूर्ण अन्यथा अणु
		packet->header &= NCI_HCI_FRAGMENT;
		hcp_skb = skb;
	पूर्ण

	/* अगर this is a response, dispatch immediately to
	 * unblock रुकोing cmd context. Otherwise, enqueue to dispatch
	 * in separate context where handler can also execute command.
	 */
	packet = (काष्ठा nci_hcp_packet *)hcp_skb->data;
	type = NCI_HCP_MSG_GET_TYPE(packet->message.header);
	अगर (type == NCI_HCI_HCP_RESPONSE) अणु
		pipe = NCI_HCP_MSG_GET_PIPE(packet->header);
		skb_pull(hcp_skb, NCI_HCI_HCP_PACKET_HEADER_LEN);
		nci_hci_hcp_message_rx(ndev, pipe, type,
				       NCI_STATUS_OK, hcp_skb);
	पूर्ण अन्यथा अणु
		skb_queue_tail(&ndev->hci_dev->msg_rx_queue, hcp_skb);
		schedule_work(&ndev->hci_dev->msg_rx_work);
	पूर्ण
पूर्ण

पूर्णांक nci_hci_खोलो_pipe(काष्ठा nci_dev *ndev, u8 pipe)
अणु
	काष्ठा nci_data data;
	काष्ठा nci_conn_info    *conn_info;

	conn_info = ndev->hci_dev->conn_info;
	अगर (!conn_info)
		वापस -EPROTO;

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADER(NCI_HCI_HCP_COMMAND,
				       NCI_HCI_ANY_OPEN_PIPE);
	data.data = शून्य;
	data.data_len = 0;

	वापस nci_request(ndev, nci_hci_send_data_req,
			(अचिन्हित दीर्घ)&data,
			msecs_to_jअगरfies(NCI_DATA_TIMEOUT));
पूर्ण
EXPORT_SYMBOL(nci_hci_खोलो_pipe);

अटल u8 nci_hci_create_pipe(काष्ठा nci_dev *ndev, u8 dest_host,
			      u8 dest_gate, पूर्णांक *result)
अणु
	u8 pipe;
	काष्ठा sk_buff *skb;
	काष्ठा nci_hci_create_pipe_params params;
	काष्ठा nci_hci_create_pipe_resp *resp;

	pr_debug("gate=%d\n", dest_gate);

	params.src_gate = NCI_HCI_ADMIN_GATE;
	params.dest_host = dest_host;
	params.dest_gate = dest_gate;

	*result = nci_hci_send_cmd(ndev, NCI_HCI_ADMIN_GATE,
				   NCI_HCI_ADM_CREATE_PIPE,
				   (u8 *)&params, माप(params), &skb);
	अगर (*result < 0)
		वापस NCI_HCI_INVALID_PIPE;

	resp = (काष्ठा nci_hci_create_pipe_resp *)skb->data;
	pipe = resp->pipe;
	kमुक्त_skb(skb);

	pr_debug("pipe created=%d\n", pipe);

	वापस pipe;
पूर्ण

अटल पूर्णांक nci_hci_delete_pipe(काष्ठा nci_dev *ndev, u8 pipe)
अणु
	pr_debug("\n");

	वापस nci_hci_send_cmd(ndev, NCI_HCI_ADMIN_GATE,
				NCI_HCI_ADM_DELETE_PIPE, &pipe, 1, शून्य);
पूर्ण

पूर्णांक nci_hci_set_param(काष्ठा nci_dev *ndev, u8 gate, u8 idx,
		      स्थिर u8 *param, माप_प्रकार param_len)
अणु
	काष्ठा nci_hcp_message *message;
	काष्ठा nci_conn_info *conn_info;
	काष्ठा nci_data data;
	पूर्णांक r;
	u8 *पंचांगp;
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	pr_debug("idx=%d to gate %d\n", idx, gate);

	अगर (pipe == NCI_HCI_INVALID_PIPE)
		वापस -EADDRNOTAVAIL;

	conn_info = ndev->hci_dev->conn_info;
	अगर (!conn_info)
		वापस -EPROTO;

	पंचांगp = kदो_स्मृति(1 + param_len, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	*पंचांगp = idx;
	स_नकल(पंचांगp + 1, param, param_len);

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADER(NCI_HCI_HCP_COMMAND,
				       NCI_HCI_ANY_SET_PARAMETER);
	data.data = पंचांगp;
	data.data_len = param_len + 1;

	r = nci_request(ndev, nci_hci_send_data_req,
			(अचिन्हित दीर्घ)&data,
			msecs_to_jअगरfies(NCI_DATA_TIMEOUT));
	अगर (r == NCI_STATUS_OK) अणु
		message = (काष्ठा nci_hcp_message *)conn_info->rx_skb->data;
		r = nci_hci_result_to_त्रुटि_सं(
			NCI_HCP_MSG_GET_CMD(message->header));
		skb_pull(conn_info->rx_skb, NCI_HCI_HCP_MESSAGE_HEADER_LEN);
	पूर्ण

	kमुक्त(पंचांगp);
	वापस r;
पूर्ण
EXPORT_SYMBOL(nci_hci_set_param);

पूर्णांक nci_hci_get_param(काष्ठा nci_dev *ndev, u8 gate, u8 idx,
		      काष्ठा sk_buff **skb)
अणु
	काष्ठा nci_hcp_message *message;
	काष्ठा nci_conn_info    *conn_info;
	काष्ठा nci_data data;
	पूर्णांक r;
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	pr_debug("idx=%d to gate %d\n", idx, gate);

	अगर (pipe == NCI_HCI_INVALID_PIPE)
		वापस -EADDRNOTAVAIL;

	conn_info = ndev->hci_dev->conn_info;
	अगर (!conn_info)
		वापस -EPROTO;

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADER(NCI_HCI_HCP_COMMAND,
				  NCI_HCI_ANY_GET_PARAMETER);
	data.data = &idx;
	data.data_len = 1;

	r = nci_request(ndev, nci_hci_send_data_req, (अचिन्हित दीर्घ)&data,
			msecs_to_jअगरfies(NCI_DATA_TIMEOUT));

	अगर (r == NCI_STATUS_OK) अणु
		message = (काष्ठा nci_hcp_message *)conn_info->rx_skb->data;
		r = nci_hci_result_to_त्रुटि_सं(
			NCI_HCP_MSG_GET_CMD(message->header));
		skb_pull(conn_info->rx_skb, NCI_HCI_HCP_MESSAGE_HEADER_LEN);

		अगर (!r && skb)
			*skb = conn_info->rx_skb;
	पूर्ण

	वापस r;
पूर्ण
EXPORT_SYMBOL(nci_hci_get_param);

पूर्णांक nci_hci_connect_gate(काष्ठा nci_dev *ndev,
			 u8 dest_host, u8 dest_gate, u8 pipe)
अणु
	bool pipe_created = false;
	पूर्णांक r;

	अगर (pipe == NCI_HCI_DO_NOT_OPEN_PIPE)
		वापस 0;

	अगर (ndev->hci_dev->gate2pipe[dest_gate] != NCI_HCI_INVALID_PIPE)
		वापस -EADDRINUSE;

	अगर (pipe != NCI_HCI_INVALID_PIPE)
		जाओ खोलो_pipe;

	चयन (dest_gate) अणु
	हाल NCI_HCI_LINK_MGMT_GATE:
		pipe = NCI_HCI_LINK_MGMT_PIPE;
	अवरोध;
	हाल NCI_HCI_ADMIN_GATE:
		pipe = NCI_HCI_ADMIN_PIPE;
	अवरोध;
	शेष:
		pipe = nci_hci_create_pipe(ndev, dest_host, dest_gate, &r);
		अगर (pipe == NCI_HCI_INVALID_PIPE)
			वापस r;
		pipe_created = true;
		अवरोध;
	पूर्ण

खोलो_pipe:
	r = nci_hci_खोलो_pipe(ndev, pipe);
	अगर (r < 0) अणु
		अगर (pipe_created) अणु
			अगर (nci_hci_delete_pipe(ndev, pipe) < 0) अणु
				/* TODO: Cannot clean by deleting pipe...
				 * -> inconsistent state
				 */
			पूर्ण
		पूर्ण
		वापस r;
	पूर्ण

	ndev->hci_dev->pipes[pipe].gate = dest_gate;
	ndev->hci_dev->pipes[pipe].host = dest_host;
	ndev->hci_dev->gate2pipe[dest_gate] = pipe;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nci_hci_connect_gate);

अटल पूर्णांक nci_hci_dev_connect_gates(काष्ठा nci_dev *ndev,
				     u8 gate_count,
				     काष्ठा nci_hci_gate *gates)
अणु
	पूर्णांक r;

	जबतक (gate_count--) अणु
		r = nci_hci_connect_gate(ndev, gates->dest_host,
					 gates->gate, gates->pipe);
		अगर (r < 0)
			वापस r;
		gates++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nci_hci_dev_session_init(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nci_conn_info    *conn_info;
	काष्ठा sk_buff *skb;
	पूर्णांक r;

	ndev->hci_dev->count_pipes = 0;
	ndev->hci_dev->expected_pipes = 0;

	conn_info = ndev->hci_dev->conn_info;
	अगर (!conn_info)
		वापस -EPROTO;

	conn_info->data_exchange_cb = nci_hci_data_received_cb;
	conn_info->data_exchange_cb_context = ndev;

	nci_hci_reset_pipes(ndev->hci_dev);

	अगर (ndev->hci_dev->init_data.gates[0].gate != NCI_HCI_ADMIN_GATE)
		वापस -EPROTO;

	r = nci_hci_connect_gate(ndev,
				 ndev->hci_dev->init_data.gates[0].dest_host,
				 ndev->hci_dev->init_data.gates[0].gate,
				 ndev->hci_dev->init_data.gates[0].pipe);
	अगर (r < 0)
		वापस r;

	r = nci_hci_get_param(ndev, NCI_HCI_ADMIN_GATE,
			      NCI_HCI_ADMIN_PARAM_SESSION_IDENTITY, &skb);
	अगर (r < 0)
		वापस r;

	अगर (skb->len &&
	    skb->len == म_माप(ndev->hci_dev->init_data.session_id) &&
	    !स_भेद(ndev->hci_dev->init_data.session_id, skb->data, skb->len) &&
	    ndev->ops->hci_load_session) अणु
		/* Restore gate<->pipe table from some proprietary location. */
		r = ndev->ops->hci_load_session(ndev);
	पूर्ण अन्यथा अणु
		r = nci_hci_clear_all_pipes(ndev);
		अगर (r < 0)
			जाओ निकास;

		r = nci_hci_dev_connect_gates(ndev,
					      ndev->hci_dev->init_data.gate_count,
					      ndev->hci_dev->init_data.gates);
		अगर (r < 0)
			जाओ निकास;

		r = nci_hci_set_param(ndev, NCI_HCI_ADMIN_GATE,
				      NCI_HCI_ADMIN_PARAM_SESSION_IDENTITY,
				      ndev->hci_dev->init_data.session_id,
				      म_माप(ndev->hci_dev->init_data.session_id));
	पूर्ण

निकास:
	kमुक्त_skb(skb);

	वापस r;
पूर्ण
EXPORT_SYMBOL(nci_hci_dev_session_init);

काष्ठा nci_hci_dev *nci_hci_allocate(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nci_hci_dev *hdev;

	hdev = kzalloc(माप(*hdev), GFP_KERNEL);
	अगर (!hdev)
		वापस शून्य;

	skb_queue_head_init(&hdev->rx_hcp_frags);
	INIT_WORK(&hdev->msg_rx_work, nci_hci_msg_rx_work);
	skb_queue_head_init(&hdev->msg_rx_queue);
	hdev->ndev = ndev;

	वापस hdev;
पूर्ण

व्योम nci_hci_deallocate(काष्ठा nci_dev *ndev)
अणु
	kमुक्त(ndev->hci_dev);
पूर्ण
