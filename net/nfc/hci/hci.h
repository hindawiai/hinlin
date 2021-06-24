<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __LOCAL_HCI_H
#घोषणा __LOCAL_HCI_H

#समावेश <net/nfc/hci.h>

काष्ठा gate_pipe_map अणु
	u8 gate;
	u8 pipe;
पूर्ण;

काष्ठा hcp_message अणु
	u8 header;		/* type -cmd,evt,rsp- + inकाष्ठाion */
	u8 data[];
पूर्ण __packed;

काष्ठा hcp_packet अणु
	u8 header;		/* cbit+pipe */
	काष्ठा hcp_message message;
पूर्ण __packed;

काष्ठा hcp_exec_रुकोer अणु
	रुको_queue_head_t *wq;
	bool exec_complete;
	पूर्णांक exec_result;
	काष्ठा sk_buff *result_skb;
पूर्ण;

काष्ठा hci_msg अणु
	काष्ठा list_head msg_l;
	काष्ठा sk_buff_head msg_frags;
	bool रुको_response;
	data_exchange_cb_t cb;
	व्योम *cb_context;
	अचिन्हित दीर्घ completion_delay;
पूर्ण;

काष्ठा hci_create_pipe_params अणु
	u8 src_gate;
	u8 dest_host;
	u8 dest_gate;
पूर्ण __packed;

काष्ठा hci_create_pipe_resp अणु
	u8 src_host;
	u8 src_gate;
	u8 dest_host;
	u8 dest_gate;
	u8 pipe;
पूर्ण __packed;

काष्ठा hci_delete_pipe_noti अणु
	u8 pipe;
पूर्ण __packed;

काष्ठा hci_all_pipe_cleared_noti अणु
	u8 host;
पूर्ण __packed;

#घोषणा NFC_HCI_FRAGMENT	0x7f

#घोषणा HCP_HEADER(type, instr) ((((type) & 0x03) << 6) | ((instr) & 0x3f))
#घोषणा HCP_MSG_GET_TYPE(header) ((header & 0xc0) >> 6)
#घोषणा HCP_MSG_GET_CMD(header) (header & 0x3f)

पूर्णांक nfc_hci_hcp_message_tx(काष्ठा nfc_hci_dev *hdev, u8 pipe,
			   u8 type, u8 inकाष्ठाion,
			   स्थिर u8 *payload, माप_प्रकार payload_len,
			   data_exchange_cb_t cb, व्योम *cb_context,
			   अचिन्हित दीर्घ completion_delay);

व्योम nfc_hci_hcp_message_rx(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 type,
			    u8 inकाष्ठाion, काष्ठा sk_buff *skb);

/* HCP headers */
#घोषणा NFC_HCI_HCP_PACKET_HEADER_LEN	1
#घोषणा NFC_HCI_HCP_MESSAGE_HEADER_LEN	1
#घोषणा NFC_HCI_HCP_HEADER_LEN		2

/* HCP types */
#घोषणा NFC_HCI_HCP_COMMAND	0x00
#घोषणा NFC_HCI_HCP_EVENT	0x01
#घोषणा NFC_HCI_HCP_RESPONSE	0x02

/* Generic commands */
#घोषणा NFC_HCI_ANY_SET_PARAMETER	0x01
#घोषणा NFC_HCI_ANY_GET_PARAMETER	0x02
#घोषणा NFC_HCI_ANY_OPEN_PIPE		0x03
#घोषणा NFC_HCI_ANY_CLOSE_PIPE		0x04

/* Reader RF commands */
#घोषणा NFC_HCI_WR_XCHG_DATA		0x10

/* Admin commands */
#घोषणा NFC_HCI_ADM_CREATE_PIPE			0x10
#घोषणा NFC_HCI_ADM_DELETE_PIPE			0x11
#घोषणा NFC_HCI_ADM_NOTIFY_PIPE_CREATED		0x12
#घोषणा NFC_HCI_ADM_NOTIFY_PIPE_DELETED		0x13
#घोषणा NFC_HCI_ADM_CLEAR_ALL_PIPE		0x14
#घोषणा NFC_HCI_ADM_NOTIFY_ALL_PIPE_CLEARED	0x15

/* Generic responses */
#घोषणा NFC_HCI_ANY_OK				0x00
#घोषणा NFC_HCI_ANY_E_NOT_CONNECTED		0x01
#घोषणा NFC_HCI_ANY_E_CMD_PAR_UNKNOWN		0x02
#घोषणा NFC_HCI_ANY_E_NOK			0x03
#घोषणा NFC_HCI_ANY_E_PIPES_FULL		0x04
#घोषणा NFC_HCI_ANY_E_REG_PAR_UNKNOWN		0x05
#घोषणा NFC_HCI_ANY_E_PIPE_NOT_OPENED		0x06
#घोषणा NFC_HCI_ANY_E_CMD_NOT_SUPPORTED		0x07
#घोषणा NFC_HCI_ANY_E_INHIBITED			0x08
#घोषणा NFC_HCI_ANY_E_TIMEOUT			0x09
#घोषणा NFC_HCI_ANY_E_REG_ACCESS_DENIED		0x0a
#घोषणा NFC_HCI_ANY_E_PIPE_ACCESS_DENIED	0x0b

#पूर्ण_अगर /* __LOCAL_HCI_H */
