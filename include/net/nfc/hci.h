<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011  Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __NET_HCI_H
#घोषणा __NET_HCI_H

#समावेश <linux/skbuff.h>

#समावेश <net/nfc/nfc.h>

काष्ठा nfc_hci_dev;

काष्ठा nfc_hci_ops अणु
	पूर्णांक (*खोलो) (काष्ठा nfc_hci_dev *hdev);
	व्योम (*बंद) (काष्ठा nfc_hci_dev *hdev);
	पूर्णांक (*load_session) (काष्ठा nfc_hci_dev *hdev);
	पूर्णांक (*hci_पढ़ोy) (काष्ठा nfc_hci_dev *hdev);
	/*
	 * xmit must always send the complete buffer beक्रमe
	 * वापसing. Returned result must be 0 क्रम success
	 * or negative क्रम failure.
	 */
	पूर्णांक (*xmit) (काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb);
	पूर्णांक (*start_poll) (काष्ठा nfc_hci_dev *hdev,
			   u32 im_protocols, u32 पंचांग_protocols);
	व्योम (*stop_poll) (काष्ठा nfc_hci_dev *hdev);
	पूर्णांक (*dep_link_up)(काष्ठा nfc_hci_dev *hdev, काष्ठा nfc_target *target,
			   u8 comm_mode, u8 *gb, माप_प्रकार gb_len);
	पूर्णांक (*dep_link_करोwn)(काष्ठा nfc_hci_dev *hdev);
	पूर्णांक (*target_from_gate) (काष्ठा nfc_hci_dev *hdev, u8 gate,
				 काष्ठा nfc_target *target);
	पूर्णांक (*complete_target_discovered) (काष्ठा nfc_hci_dev *hdev, u8 gate,
					   काष्ठा nfc_target *target);
	पूर्णांक (*im_transceive) (काष्ठा nfc_hci_dev *hdev,
			      काष्ठा nfc_target *target, काष्ठा sk_buff *skb,
			      data_exchange_cb_t cb, व्योम *cb_context);
	पूर्णांक (*पंचांग_send)(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb);
	पूर्णांक (*check_presence)(काष्ठा nfc_hci_dev *hdev,
			      काष्ठा nfc_target *target);
	पूर्णांक (*event_received)(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 event,
			      काष्ठा sk_buff *skb);
	व्योम (*cmd_received)(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			    काष्ठा sk_buff *skb);
	पूर्णांक (*fw_करोwnload)(काष्ठा nfc_hci_dev *hdev, स्थिर अक्षर *firmware_name);
	पूर्णांक (*discover_se)(काष्ठा nfc_hci_dev *dev);
	पूर्णांक (*enable_se)(काष्ठा nfc_hci_dev *dev, u32 se_idx);
	पूर्णांक (*disable_se)(काष्ठा nfc_hci_dev *dev, u32 se_idx);
	पूर्णांक (*se_io)(काष्ठा nfc_hci_dev *dev, u32 se_idx,
		      u8 *apdu, माप_प्रकार apdu_length,
		      se_io_cb_t cb, व्योम *cb_context);
पूर्ण;

/* Pipes */
#घोषणा NFC_HCI_DO_NOT_CREATE_PIPE	0x81
#घोषणा NFC_HCI_INVALID_PIPE	0x80
#घोषणा NFC_HCI_INVALID_GATE	0xFF
#घोषणा NFC_HCI_INVALID_HOST	0x80
#घोषणा NFC_HCI_LINK_MGMT_PIPE	0x00
#घोषणा NFC_HCI_ADMIN_PIPE	0x01

काष्ठा nfc_hci_gate अणु
	u8 gate;
	u8 pipe;
पूर्ण;

काष्ठा nfc_hci_pipe अणु
	u8 gate;
	u8 dest_host;
पूर्ण;

#घोषणा NFC_HCI_MAX_CUSTOM_GATES	50
/*
 * According to specअगरication 102 622 chapter 4.4 Pipes,
 * the pipe identअगरier is 7 bits दीर्घ.
 */
#घोषणा NFC_HCI_MAX_PIPES		128
काष्ठा nfc_hci_init_data अणु
	u8 gate_count;
	काष्ठा nfc_hci_gate gates[NFC_HCI_MAX_CUSTOM_GATES];
	अक्षर session_id[9];
पूर्ण;

प्रकार पूर्णांक (*xmit) (काष्ठा sk_buff *skb, व्योम *cb_data);

#घोषणा NFC_HCI_MAX_GATES		256

/*
 * These values can be specअगरied by a driver to indicate it requires some
 * adaptation of the HCI standard.
 *
 * NFC_HCI_QUIRK_SHORT_CLEAR - send HCI_ADM_CLEAR_ALL_PIPE cmd with no params
 */
क्रमागत अणु
	NFC_HCI_QUIRK_SHORT_CLEAR	= 0,
पूर्ण;

काष्ठा nfc_hci_dev अणु
	काष्ठा nfc_dev *ndev;

	u32 max_data_link_payload;

	bool shutting_करोwn;

	काष्ठा mutex msg_tx_mutex;

	काष्ठा list_head msg_tx_queue;

	काष्ठा work_काष्ठा msg_tx_work;

	काष्ठा समयr_list cmd_समयr;
	काष्ठा hci_msg *cmd_pending_msg;

	काष्ठा sk_buff_head rx_hcp_frags;

	काष्ठा work_काष्ठा msg_rx_work;

	काष्ठा sk_buff_head msg_rx_queue;

	काष्ठा nfc_hci_ops *ops;

	काष्ठा nfc_llc *llc;

	काष्ठा nfc_hci_init_data init_data;

	व्योम *clientdata;

	u8 gate2pipe[NFC_HCI_MAX_GATES];
	काष्ठा nfc_hci_pipe pipes[NFC_HCI_MAX_PIPES];

	u8 sw_romlib;
	u8 sw_patch;
	u8 sw_flashlib_major;
	u8 sw_flashlib_minor;

	u8 hw_derivative;
	u8 hw_version;
	u8 hw_mpw;
	u8 hw_software;
	u8 hw_bsid;

	पूर्णांक async_cb_type;
	data_exchange_cb_t async_cb;
	व्योम *async_cb_context;

	u8 *gb;
	माप_प्रकार gb_len;

	अचिन्हित दीर्घ quirks;
पूर्ण;

/* hci device allocation */
काष्ठा nfc_hci_dev *nfc_hci_allocate_device(काष्ठा nfc_hci_ops *ops,
					    काष्ठा nfc_hci_init_data *init_data,
					    अचिन्हित दीर्घ quirks,
					    u32 protocols,
					    स्थिर अक्षर *llc_name,
					    पूर्णांक tx_headroom,
					    पूर्णांक tx_tailroom,
					    पूर्णांक max_link_payload);
व्योम nfc_hci_मुक्त_device(काष्ठा nfc_hci_dev *hdev);

पूर्णांक nfc_hci_रेजिस्टर_device(काष्ठा nfc_hci_dev *hdev);
व्योम nfc_hci_unरेजिस्टर_device(काष्ठा nfc_hci_dev *hdev);

व्योम nfc_hci_set_clientdata(काष्ठा nfc_hci_dev *hdev, व्योम *clientdata);
व्योम *nfc_hci_get_clientdata(काष्ठा nfc_hci_dev *hdev);

अटल अंतरभूत पूर्णांक nfc_hci_set_venकरोr_cmds(काष्ठा nfc_hci_dev *hdev,
					  काष्ठा nfc_venकरोr_cmd *cmds,
					  पूर्णांक n_cmds)
अणु
	वापस nfc_set_venकरोr_cmds(hdev->ndev, cmds, n_cmds);
पूर्ण

व्योम nfc_hci_driver_failure(काष्ठा nfc_hci_dev *hdev, पूर्णांक err);

पूर्णांक nfc_hci_result_to_त्रुटि_सं(u8 result);
व्योम nfc_hci_reset_pipes(काष्ठा nfc_hci_dev *dev);
व्योम nfc_hci_reset_pipes_per_host(काष्ठा nfc_hci_dev *hdev, u8 host);

/* Host IDs */
#घोषणा NFC_HCI_HOST_CONTROLLER_ID	0x00
#घोषणा NFC_HCI_TERMINAL_HOST_ID	0x01
#घोषणा NFC_HCI_UICC_HOST_ID		0x02

/* Host Controller Gates and registry indexes */
#घोषणा NFC_HCI_ADMIN_GATE 0x00
#घोषणा NFC_HCI_ADMIN_SESSION_IDENTITY	0x01
#घोषणा NFC_HCI_ADMIN_MAX_PIPE		0x02
#घोषणा NFC_HCI_ADMIN_WHITELIST		0x03
#घोषणा NFC_HCI_ADMIN_HOST_LIST		0x04

#घोषणा NFC_HCI_LOOPBACK_GATE		0x04

#घोषणा NFC_HCI_ID_MGMT_GATE		0x05
#घोषणा NFC_HCI_ID_MGMT_VERSION_SW	0x01
#घोषणा NFC_HCI_ID_MGMT_VERSION_HW	0x03
#घोषणा NFC_HCI_ID_MGMT_VENDOR_NAME	0x04
#घोषणा NFC_HCI_ID_MGMT_MODEL_ID	0x05
#घोषणा NFC_HCI_ID_MGMT_HCI_VERSION	0x02
#घोषणा NFC_HCI_ID_MGMT_GATES_LIST	0x06

#घोषणा NFC_HCI_LINK_MGMT_GATE		0x06
#घोषणा NFC_HCI_LINK_MGMT_REC_ERROR	0x01

#घोषणा NFC_HCI_RF_READER_B_GATE			0x11
#घोषणा NFC_HCI_RF_READER_B_PUPI			0x03
#घोषणा NFC_HCI_RF_READER_B_APPLICATION_DATA		0x04
#घोषणा NFC_HCI_RF_READER_B_AFI				0x02
#घोषणा NFC_HCI_RF_READER_B_HIGHER_LAYER_RESPONSE	0x01
#घोषणा NFC_HCI_RF_READER_B_HIGHER_LAYER_DATA		0x05

#घोषणा NFC_HCI_RF_READER_A_GATE		0x13
#घोषणा NFC_HCI_RF_READER_A_UID			0x02
#घोषणा NFC_HCI_RF_READER_A_ATQA		0x04
#घोषणा NFC_HCI_RF_READER_A_APPLICATION_DATA	0x05
#घोषणा NFC_HCI_RF_READER_A_SAK			0x03
#घोषणा NFC_HCI_RF_READER_A_FWI_SFGT		0x06
#घोषणा NFC_HCI_RF_READER_A_DATARATE_MAX	0x01

#घोषणा NFC_HCI_TYPE_A_SEL_PROT(x)		(((x) & 0x60) >> 5)
#घोषणा NFC_HCI_TYPE_A_SEL_PROT_MIFARE		0
#घोषणा NFC_HCI_TYPE_A_SEL_PROT_ISO14443	1
#घोषणा NFC_HCI_TYPE_A_SEL_PROT_DEP		2
#घोषणा NFC_HCI_TYPE_A_SEL_PROT_ISO14443_DEP	3

/* Generic events */
#घोषणा NFC_HCI_EVT_HCI_END_OF_OPERATION	0x01
#घोषणा NFC_HCI_EVT_POST_DATA			0x02
#घोषणा NFC_HCI_EVT_HOT_PLUG			0x03

/* Generic commands */
#घोषणा NFC_HCI_ANY_SET_PARAMETER	0x01
#घोषणा NFC_HCI_ANY_GET_PARAMETER	0x02
#घोषणा NFC_HCI_ANY_OPEN_PIPE		0x03
#घोषणा NFC_HCI_ANY_CLOSE_PIPE		0x04

/* Reader RF gates events */
#घोषणा NFC_HCI_EVT_READER_REQUESTED	0x10
#घोषणा NFC_HCI_EVT_END_OPERATION	0x11

/* Reader Application gate events */
#घोषणा NFC_HCI_EVT_TARGET_DISCOVERED	0x10

/* receiving messages from lower layer */
व्योम nfc_hci_resp_received(काष्ठा nfc_hci_dev *hdev, u8 result,
			   काष्ठा sk_buff *skb);
व्योम nfc_hci_cmd_received(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			  काष्ठा sk_buff *skb);
व्योम nfc_hci_event_received(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 event,
			    काष्ठा sk_buff *skb);
व्योम nfc_hci_recv_frame(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb);

/* connecting to gates and sending hci inकाष्ठाions */
पूर्णांक nfc_hci_connect_gate(काष्ठा nfc_hci_dev *hdev, u8 dest_host, u8 dest_gate,
			 u8 pipe);
पूर्णांक nfc_hci_disconnect_gate(काष्ठा nfc_hci_dev *hdev, u8 gate);
पूर्णांक nfc_hci_disconnect_all_gates(काष्ठा nfc_hci_dev *hdev);
पूर्णांक nfc_hci_get_param(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 idx,
		      काष्ठा sk_buff **skb);
पूर्णांक nfc_hci_set_param(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 idx,
		      स्थिर u8 *param, माप_प्रकार param_len);
पूर्णांक nfc_hci_send_cmd(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 cmd,
		     स्थिर u8 *param, माप_प्रकार param_len, काष्ठा sk_buff **skb);
पूर्णांक nfc_hci_send_cmd_async(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 cmd,
			   स्थिर u8 *param, माप_प्रकार param_len,
			   data_exchange_cb_t cb, व्योम *cb_context);
पूर्णांक nfc_hci_send_event(काष्ठा nfc_hci_dev *hdev, u8 gate, u8 event,
		       स्थिर u8 *param, माप_प्रकार param_len);
पूर्णांक nfc_hci_target_discovered(काष्ठा nfc_hci_dev *hdev, u8 gate);
u32 nfc_hci_sak_to_protocol(u8 sak);

#पूर्ण_अगर /* __NET_HCI_H */
