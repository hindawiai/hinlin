<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HCI based Driver क्रम STMicroelectronics NFC Chip
 *
 * Copyright (C) 2014  STMicroelectronics SAS. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>

#समावेश "st21nfca.h"

#घोषणा DRIVER_DESC "HCI NFC driver for ST21NFCA"

#घोषणा FULL_VERSION_LEN 3

/* Proprietary gates, events, commands and रेजिस्टरs */

/* Commands that apply to all RF पढ़ोers */
#घोषणा ST21NFCA_RF_READER_CMD_PRESENCE_CHECK	0x30

#घोषणा ST21NFCA_RF_READER_ISO15693_GATE	0x12
#घोषणा ST21NFCA_RF_READER_ISO15693_INVENTORY	0x01

/*
 * Reader gate क्रम communication with contact-less cards using Type A
 * protocol ISO14443-3 but not compliant with ISO14443-4
 */
#घोषणा ST21NFCA_RF_READER_14443_3_A_GATE	0x15
#घोषणा ST21NFCA_RF_READER_14443_3_A_UID	0x02
#घोषणा ST21NFCA_RF_READER_14443_3_A_ATQA	0x03
#घोषणा ST21NFCA_RF_READER_14443_3_A_SAK	0x04

#घोषणा ST21NFCA_RF_READER_F_DATARATE		0x01
#घोषणा ST21NFCA_RF_READER_F_DATARATE_106	0x01
#घोषणा ST21NFCA_RF_READER_F_DATARATE_212	0x02
#घोषणा ST21NFCA_RF_READER_F_DATARATE_424	0x04
#घोषणा ST21NFCA_RF_READER_F_POL_REQ		0x02
#घोषणा ST21NFCA_RF_READER_F_POL_REQ_DEFAULT	0xffff0000
#घोषणा ST21NFCA_RF_READER_F_NFCID2		0x03
#घोषणा ST21NFCA_RF_READER_F_NFCID1		0x04

#घोषणा ST21NFCA_RF_CARD_F_MODE			0x01
#घोषणा ST21NFCA_RF_CARD_F_NFCID2_LIST		0x04
#घोषणा ST21NFCA_RF_CARD_F_NFCID1		0x05
#घोषणा ST21NFCA_RF_CARD_F_SENS_RES		0x06
#घोषणा ST21NFCA_RF_CARD_F_SEL_RES		0x07
#घोषणा ST21NFCA_RF_CARD_F_DATARATE		0x08
#घोषणा ST21NFCA_RF_CARD_F_DATARATE_212_424	0x01

#घोषणा ST21NFCA_DEVICE_MGNT_PIPE		0x02

#घोषणा ST21NFCA_DM_GETINFO			0x13
#घोषणा ST21NFCA_DM_GETINFO_PIPE_LIST		0x02
#घोषणा ST21NFCA_DM_GETINFO_PIPE_INFO		0x01
#घोषणा ST21NFCA_DM_PIPE_CREATED		0x02
#घोषणा ST21NFCA_DM_PIPE_OPEN			0x04
#घोषणा ST21NFCA_DM_RF_ACTIVE			0x80
#घोषणा ST21NFCA_DM_DISCONNECT			0x30

#घोषणा ST21NFCA_DM_IS_PIPE_OPEN(p) \
	((p & 0x0f) == (ST21NFCA_DM_PIPE_CREATED | ST21NFCA_DM_PIPE_OPEN))

#घोषणा ST21NFCA_NFC_MODE			0x03	/* NFC_MODE parameter*/

#घोषणा ST21NFCA_EVT_HOT_PLUG			0x03
#घोषणा ST21NFCA_EVT_HOT_PLUG_IS_INHIBITED(x) (x->data[0] & 0x80)

#घोषणा ST21NFCA_SE_TO_PIPES			2000

अटल DECLARE_BITMAP(dev_mask, ST21NFCA_NUM_DEVICES);

अटल काष्ठा nfc_hci_gate st21nfca_gates[] = अणु
	अणुNFC_HCI_ADMIN_GATE, NFC_HCI_ADMIN_PIPEपूर्ण,
	अणुNFC_HCI_LINK_MGMT_GATE, NFC_HCI_LINK_MGMT_PIPEपूर्ण,
	अणुST21NFCA_DEVICE_MGNT_GATE, ST21NFCA_DEVICE_MGNT_PIPEपूर्ण,

	अणुNFC_HCI_LOOPBACK_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुNFC_HCI_ID_MGMT_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुNFC_HCI_RF_READER_B_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुNFC_HCI_RF_READER_A_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुST21NFCA_RF_READER_F_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुST21NFCA_RF_READER_14443_3_A_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुST21NFCA_RF_READER_ISO15693_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुST21NFCA_RF_CARD_F_GATE, NFC_HCI_INVALID_PIPEपूर्ण,

	/* Secure element pipes are created by secure element host */
	अणुST21NFCA_CONNECTIVITY_GATE, NFC_HCI_DO_NOT_CREATE_PIPEपूर्ण,
	अणुST21NFCA_APDU_READER_GATE, NFC_HCI_DO_NOT_CREATE_PIPEपूर्ण,
पूर्ण;

काष्ठा st21nfca_pipe_info अणु
	u8 pipe_state;
	u8 src_host_id;
	u8 src_gate_id;
	u8 dst_host_id;
	u8 dst_gate_id;
पूर्ण __packed;

/* Largest headroom needed क्रम outgoing custom commands */
#घोषणा ST21NFCA_CMDS_HEADROOM  7

अटल पूर्णांक st21nfca_hci_load_session(काष्ठा nfc_hci_dev *hdev)
अणु
	पूर्णांक i, j, r;
	काष्ठा sk_buff *skb_pipe_list, *skb_pipe_info;
	काष्ठा st21nfca_pipe_info *info;

	u8 pipe_list[] = अणु ST21NFCA_DM_GETINFO_PIPE_LIST,
		NFC_HCI_TERMINAL_HOST_ID
	पूर्ण;
	u8 pipe_info[] = अणु ST21NFCA_DM_GETINFO_PIPE_INFO,
		NFC_HCI_TERMINAL_HOST_ID, 0
	पूर्ण;

	/* On ST21NFCA device pipes number are dynamics
	 * A maximum of 16 pipes can be created at the same समय
	 * If pipes are alपढ़ोy created, hci_dev_up will fail.
	 * Doing a clear all pipe is a bad idea because:
	 * - It करोes useless EEPROM cycling
	 * - It might cause issue क्रम secure elements support
	 * (such as removing connectivity or APDU पढ़ोer pipe)
	 * A better approach on ST21NFCA is to:
	 * - get a pipe list क्रम each host.
	 * (eg: NFC_HCI_HOST_CONTROLLER_ID क्रम now).
	 * (TODO Later on UICC HOST and eSE HOST)
	 * - get pipe inक्रमmation
	 * - match retrieved pipe list in st21nfca_gates
	 * ST21NFCA_DEVICE_MGNT_GATE is a proprietary gate
	 * with ST21NFCA_DEVICE_MGNT_PIPE.
	 * Pipe can be बंदd and need to be खोलो.
	 */
	r = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTROLLER_ID,
				ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_DEVICE_MGNT_PIPE);
	अगर (r < 0)
		वापस r;

	/* Get pipe list */
	r = nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_DM_GETINFO, pipe_list, माप(pipe_list),
			&skb_pipe_list);
	अगर (r < 0)
		वापस r;

	/* Complete the existing gate_pipe table */
	क्रम (i = 0; i < skb_pipe_list->len; i++) अणु
		pipe_info[2] = skb_pipe_list->data[i];
		r = nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
					ST21NFCA_DM_GETINFO, pipe_info,
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
		info = (काष्ठा st21nfca_pipe_info *) skb_pipe_info->data;
		अगर (info->dst_gate_id == ST21NFCA_APDU_READER_GATE &&
			info->src_host_id == NFC_HCI_UICC_HOST_ID) अणु
			pr_err("Unexpected apdu_reader pipe on host %x\n",
				info->src_host_id);
			kमुक्त_skb(skb_pipe_info);
			जारी;
		पूर्ण

		क्रम (j = 3; (j < ARRAY_SIZE(st21nfca_gates)) &&
			(st21nfca_gates[j].gate != info->dst_gate_id) ; j++)
			;

		अगर (j < ARRAY_SIZE(st21nfca_gates) &&
			st21nfca_gates[j].gate == info->dst_gate_id &&
			ST21NFCA_DM_IS_PIPE_OPEN(info->pipe_state)) अणु
			hdev->init_data.gates[j].pipe = pipe_info[2];

			hdev->gate2pipe[st21nfca_gates[j].gate] =
						pipe_info[2];
			hdev->pipes[pipe_info[2]].gate =
						st21nfca_gates[j].gate;
			hdev->pipes[pipe_info[2]].dest_host =
						info->src_host_id;
		पूर्ण
		kमुक्त_skb(skb_pipe_info);
	पूर्ण

	/*
	 * 3 gates have a well known pipe ID. Only NFC_HCI_LINK_MGMT_GATE
	 * is not yet खोलो at this stage.
	 */
	r = nfc_hci_connect_gate(hdev, NFC_HCI_HOST_CONTROLLER_ID,
				 NFC_HCI_LINK_MGMT_GATE,
				 NFC_HCI_LINK_MGMT_PIPE);

	kमुक्त_skb(skb_pipe_list);
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_hci_खोलो(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	पूर्णांक r;

	mutex_lock(&info->info_lock);

	अगर (info->state != ST21NFCA_ST_COLD) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण

	r = info->phy_ops->enable(info->phy_id);

	अगर (r == 0)
		info->state = ST21NFCA_ST_READY;

out:
	mutex_unlock(&info->info_lock);
	वापस r;
पूर्ण

अटल व्योम st21nfca_hci_बंद(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	mutex_lock(&info->info_lock);

	अगर (info->state == ST21NFCA_ST_COLD)
		जाओ out;

	info->phy_ops->disable(info->phy_id);
	info->state = ST21NFCA_ST_COLD;

out:
	mutex_unlock(&info->info_lock);
पूर्ण

अटल पूर्णांक st21nfca_hci_पढ़ोy(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	काष्ठा sk_buff *skb;

	u8 param;
	u8 white_list[2];
	पूर्णांक wl_size = 0;
	पूर्णांक r;

	अगर (info->se_status->is_uicc_present)
		white_list[wl_size++] = NFC_HCI_UICC_HOST_ID;
	अगर (info->se_status->is_ese_present)
		white_list[wl_size++] = ST21NFCA_ESE_HOST_ID;

	अगर (wl_size) अणु
		r = nfc_hci_set_param(hdev, NFC_HCI_ADMIN_GATE,
					NFC_HCI_ADMIN_WHITELIST,
					(u8 *) &white_list, wl_size);
		अगर (r < 0)
			वापस r;
	पूर्ण

	/* Set NFC_MODE in device management gate to enable */
	r = nfc_hci_get_param(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			      ST21NFCA_NFC_MODE, &skb);
	अगर (r < 0)
		वापस r;

	param = skb->data[0];
	kमुक्त_skb(skb);
	अगर (param == 0) अणु
		param = 1;

		r = nfc_hci_set_param(hdev, ST21NFCA_DEVICE_MGNT_GATE,
					ST21NFCA_NFC_MODE, &param, 1);
		अगर (r < 0)
			वापस r;
	पूर्ण

	r = nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
			       NFC_HCI_EVT_END_OPERATION, शून्य, 0);
	अगर (r < 0)
		वापस r;

	r = nfc_hci_get_param(hdev, NFC_HCI_ID_MGMT_GATE,
			      NFC_HCI_ID_MGMT_VERSION_SW, &skb);
	अगर (r < 0)
		वापस r;

	अगर (skb->len != FULL_VERSION_LEN) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	prपूर्णांक_hex_dump(KERN_DEBUG, "FULL VERSION SOFTWARE INFO: ",
		       DUMP_PREFIX_NONE, 16, 1,
		       skb->data, FULL_VERSION_LEN, false);

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक st21nfca_hci_xmit(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	वापस info->phy_ops->ग_लिखो(info->phy_id, skb);
पूर्ण

अटल पूर्णांक st21nfca_hci_start_poll(काष्ठा nfc_hci_dev *hdev,
				   u32 im_protocols, u32 पंचांग_protocols)
अणु
	पूर्णांक r;
	u32 pol_req;
	u8 param[19];
	काष्ठा sk_buff *datarate_skb;

	pr_info(DRIVER_DESC ": %s protocols 0x%x 0x%x\n",
		__func__, im_protocols, पंचांग_protocols);

	r = nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
			       NFC_HCI_EVT_END_OPERATION, शून्य, 0);
	अगर (r < 0)
		वापस r;
	अगर (im_protocols) अणु
		/*
		 * enable polling according to im_protocols & पंचांग_protocols
		 * - CLOSE pipe according to im_protocols & पंचांग_protocols
		 */
		अगर ((NFC_HCI_RF_READER_B_GATE & im_protocols) == 0) अणु
			r = nfc_hci_disconnect_gate(hdev,
					NFC_HCI_RF_READER_B_GATE);
			अगर (r < 0)
				वापस r;
		पूर्ण

		अगर ((NFC_HCI_RF_READER_A_GATE & im_protocols) == 0) अणु
			r = nfc_hci_disconnect_gate(hdev,
					NFC_HCI_RF_READER_A_GATE);
			अगर (r < 0)
				वापस r;
		पूर्ण

		अगर ((ST21NFCA_RF_READER_F_GATE & im_protocols) == 0) अणु
			r = nfc_hci_disconnect_gate(hdev,
					ST21NFCA_RF_READER_F_GATE);
			अगर (r < 0)
				वापस r;
		पूर्ण अन्यथा अणु
			hdev->gb = nfc_get_local_general_bytes(hdev->ndev,
							       &hdev->gb_len);

			अगर (hdev->gb == शून्य || hdev->gb_len == 0) अणु
				im_protocols &= ~NFC_PROTO_NFC_DEP_MASK;
				पंचांग_protocols &= ~NFC_PROTO_NFC_DEP_MASK;
			पूर्ण

			param[0] = ST21NFCA_RF_READER_F_DATARATE_106 |
			    ST21NFCA_RF_READER_F_DATARATE_212 |
			    ST21NFCA_RF_READER_F_DATARATE_424;
			r = nfc_hci_set_param(hdev, ST21NFCA_RF_READER_F_GATE,
					      ST21NFCA_RF_READER_F_DATARATE,
					      param, 1);
			अगर (r < 0)
				वापस r;

			pol_req = be32_to_cpu((__क्रमce __be32)
					ST21NFCA_RF_READER_F_POL_REQ_DEFAULT);
			r = nfc_hci_set_param(hdev, ST21NFCA_RF_READER_F_GATE,
					      ST21NFCA_RF_READER_F_POL_REQ,
					      (u8 *) &pol_req, 4);
			अगर (r < 0)
				वापस r;
		पूर्ण

		अगर ((ST21NFCA_RF_READER_14443_3_A_GATE & im_protocols) == 0) अणु
			r = nfc_hci_disconnect_gate(hdev,
					ST21NFCA_RF_READER_14443_3_A_GATE);
			अगर (r < 0)
				वापस r;
		पूर्ण

		अगर ((ST21NFCA_RF_READER_ISO15693_GATE & im_protocols) == 0) अणु
			r = nfc_hci_disconnect_gate(hdev,
					ST21NFCA_RF_READER_ISO15693_GATE);
			अगर (r < 0)
				वापस r;
		पूर्ण

		r = nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
				       NFC_HCI_EVT_READER_REQUESTED, शून्य, 0);
		अगर (r < 0)
			nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
					   NFC_HCI_EVT_END_OPERATION, शून्य, 0);
	पूर्ण

	अगर (पंचांग_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		r = nfc_hci_get_param(hdev, ST21NFCA_RF_CARD_F_GATE,
				      ST21NFCA_RF_CARD_F_DATARATE,
				      &datarate_skb);
		अगर (r < 0)
			वापस r;

		/* Configure the maximum supported datarate to 424Kbps */
		अगर (datarate_skb->len > 0 &&
		    datarate_skb->data[0] !=
		    ST21NFCA_RF_CARD_F_DATARATE_212_424) अणु
			param[0] = ST21NFCA_RF_CARD_F_DATARATE_212_424;
			r = nfc_hci_set_param(hdev, ST21NFCA_RF_CARD_F_GATE,
					      ST21NFCA_RF_CARD_F_DATARATE,
					      param, 1);
			अगर (r < 0) अणु
				kमुक्त_skb(datarate_skb);
				वापस r;
			पूर्ण
		पूर्ण
		kमुक्त_skb(datarate_skb);

		/*
		 * Configure sens_res
		 *
		 * NFC Forum Digital Spec Table 7:
		 * NFCID1 size: triple (10 bytes)
		 */
		param[0] = 0x00;
		param[1] = 0x08;
		r = nfc_hci_set_param(hdev, ST21NFCA_RF_CARD_F_GATE,
				      ST21NFCA_RF_CARD_F_SENS_RES, param, 2);
		अगर (r < 0)
			वापस r;

		/*
		 * Configure sel_res
		 *
		 * NFC Forum Digistal Spec Table 17:
		 * b3 set to 0b (value b7-b6):
		 * - 10b: Configured क्रम NFC-DEP Protocol
		 */
		param[0] = 0x40;
		r = nfc_hci_set_param(hdev, ST21NFCA_RF_CARD_F_GATE,
				      ST21NFCA_RF_CARD_F_SEL_RES, param, 1);
		अगर (r < 0)
			वापस r;

		/* Configure NFCID1 Ranकरोm uid */
		r = nfc_hci_set_param(hdev, ST21NFCA_RF_CARD_F_GATE,
				      ST21NFCA_RF_CARD_F_NFCID1, शून्य, 0);
		अगर (r < 0)
			वापस r;

		/* Configure NFCID2_LIST */
		/* System Code */
		param[0] = 0x00;
		param[1] = 0x00;
		/* NFCID2 */
		param[2] = 0x01;
		param[3] = 0xfe;
		param[4] = 'S';
		param[5] = 'T';
		param[6] = 'M';
		param[7] = 'i';
		param[8] = 'c';
		param[9] = 'r';
		/* 8 byte Pad bytes used क्रम polling respone frame */

		/*
		 * Configuration byte:
		 * - bit 0: define the शेष NFCID2 entry used when the
		 * प्रणाली code is equal to 'FFFF'
		 * - bit 1: use a अक्रमom value क्रम lowest 6 bytes of
		 * NFCID2 value
		 * - bit 2: ignore polling request frame अगर request code
		 * is equal to '01'
		 * - Other bits are RFU
		 */
		param[18] = 0x01;
		r = nfc_hci_set_param(hdev, ST21NFCA_RF_CARD_F_GATE,
				      ST21NFCA_RF_CARD_F_NFCID2_LIST, param,
				      19);
		अगर (r < 0)
			वापस r;

		param[0] = 0x02;
		r = nfc_hci_set_param(hdev, ST21NFCA_RF_CARD_F_GATE,
				      ST21NFCA_RF_CARD_F_MODE, param, 1);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम st21nfca_hci_stop_poll(काष्ठा nfc_hci_dev *hdev)
अणु
	nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_DM_DISCONNECT, शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक st21nfca_get_iso14443_3_atqa(काष्ठा nfc_hci_dev *hdev, u16 *atqa)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *atqa_skb = शून्य;

	r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_14443_3_A_GATE,
			      ST21NFCA_RF_READER_14443_3_A_ATQA, &atqa_skb);
	अगर (r < 0)
		जाओ निकास;

	अगर (atqa_skb->len != 2) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	*atqa = be16_to_cpu(*(__be16 *) atqa_skb->data);

निकास:
	kमुक्त_skb(atqa_skb);
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_get_iso14443_3_sak(काष्ठा nfc_hci_dev *hdev, u8 *sak)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *sak_skb = शून्य;

	r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_14443_3_A_GATE,
			      ST21NFCA_RF_READER_14443_3_A_SAK, &sak_skb);
	अगर (r < 0)
		जाओ निकास;

	अगर (sak_skb->len != 1) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	*sak = sak_skb->data[0];

निकास:
	kमुक्त_skb(sak_skb);
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_get_iso14443_3_uid(काष्ठा nfc_hci_dev *hdev, u8 *uid,
				       पूर्णांक *len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *uid_skb = शून्य;

	r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_14443_3_A_GATE,
			      ST21NFCA_RF_READER_14443_3_A_UID, &uid_skb);
	अगर (r < 0)
		जाओ निकास;

	अगर (uid_skb->len == 0 || uid_skb->len > NFC_NFCID1_MAXSIZE) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	स_नकल(uid, uid_skb->data, uid_skb->len);
	*len = uid_skb->len;
निकास:
	kमुक्त_skb(uid_skb);
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_get_iso15693_inventory(काष्ठा nfc_hci_dev *hdev,
					   काष्ठा nfc_target *target)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *inventory_skb = शून्य;

	r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_ISO15693_GATE,
			      ST21NFCA_RF_READER_ISO15693_INVENTORY,
			      &inventory_skb);
	अगर (r < 0)
		जाओ निकास;

	skb_pull(inventory_skb, 2);

	अगर (inventory_skb->len == 0 ||
	    inventory_skb->len > NFC_ISO15693_UID_MAXSIZE) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	स_नकल(target->iso15693_uid, inventory_skb->data, inventory_skb->len);
	target->iso15693_dsfid	= inventory_skb->data[1];
	target->is_iso15693 = 1;
निकास:
	kमुक्त_skb(inventory_skb);
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_hci_dep_link_up(काष्ठा nfc_hci_dev *hdev,
				    काष्ठा nfc_target *target, u8 comm_mode,
				    u8 *gb, माप_प्रकार gb_len)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	info->dep_info.idx = target->idx;
	वापस st21nfca_im_send_atr_req(hdev, gb, gb_len);
पूर्ण

अटल पूर्णांक st21nfca_hci_dep_link_करोwn(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	info->state = ST21NFCA_ST_READY;

	वापस nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_DM_DISCONNECT, शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक st21nfca_hci_target_from_gate(काष्ठा nfc_hci_dev *hdev, u8 gate,
					 काष्ठा nfc_target *target)
अणु
	पूर्णांक r, len;
	u16 atqa;
	u8 sak;
	u8 uid[NFC_NFCID1_MAXSIZE];

	चयन (gate) अणु
	हाल ST21NFCA_RF_READER_F_GATE:
		target->supported_protocols = NFC_PROTO_FELICA_MASK;
		अवरोध;
	हाल ST21NFCA_RF_READER_14443_3_A_GATE:
		/* ISO14443-3 type 1 or 2 tags */
		r = st21nfca_get_iso14443_3_atqa(hdev, &atqa);
		अगर (r < 0)
			वापस r;
		अगर (atqa == 0x000c) अणु
			target->supported_protocols = NFC_PROTO_JEWEL_MASK;
			target->sens_res = 0x0c00;
		पूर्ण अन्यथा अणु
			r = st21nfca_get_iso14443_3_sak(hdev, &sak);
			अगर (r < 0)
				वापस r;

			r = st21nfca_get_iso14443_3_uid(hdev, uid, &len);
			अगर (r < 0)
				वापस r;

			target->supported_protocols =
			    nfc_hci_sak_to_protocol(sak);
			अगर (target->supported_protocols == 0xffffffff)
				वापस -EPROTO;

			target->sens_res = atqa;
			target->sel_res = sak;
			स_नकल(target->nfcid1, uid, len);
			target->nfcid1_len = len;
		पूर्ण

		अवरोध;
	हाल ST21NFCA_RF_READER_ISO15693_GATE:
		target->supported_protocols = NFC_PROTO_ISO15693_MASK;
		r = st21nfca_get_iso15693_inventory(hdev, target);
		अगर (r < 0)
			वापस r;
		अवरोध;
	शेष:
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st21nfca_hci_complete_target_discovered(काष्ठा nfc_hci_dev *hdev,
						u8 gate,
						काष्ठा nfc_target *target)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *nfcid_skb = शून्य;

	अगर (gate == ST21NFCA_RF_READER_F_GATE) अणु
		r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_F_GATE,
				ST21NFCA_RF_READER_F_NFCID2, &nfcid_skb);
		अगर (r < 0)
			जाओ निकास;

		अगर (nfcid_skb->len > NFC_SENSF_RES_MAXSIZE) अणु
			r = -EPROTO;
			जाओ निकास;
		पूर्ण

		/*
		 * - After the recepton of polling response क्रम type F frame
		 * at 212 or 424 Kbit/s, NFCID2 registry parameters will be
		 * updated.
		 * - After the reception of SEL_RES with NFCIP-1 compliant bit
		 * set क्रम type A frame NFCID1 will be updated
		 */
		अगर (nfcid_skb->len > 0) अणु
			/* P2P in type F */
			स_नकल(target->sensf_res, nfcid_skb->data,
				nfcid_skb->len);
			target->sensf_res_len = nfcid_skb->len;
			/* NFC Forum Digital Protocol Table 44 */
			अगर (target->sensf_res[0] == 0x01 &&
			    target->sensf_res[1] == 0xfe)
				target->supported_protocols =
							NFC_PROTO_NFC_DEP_MASK;
			अन्यथा
				target->supported_protocols =
							NFC_PROTO_FELICA_MASK;
		पूर्ण अन्यथा अणु
			kमुक्त_skb(nfcid_skb);
			nfcid_skb = शून्य;
			/* P2P in type A */
			r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_F_GATE,
					ST21NFCA_RF_READER_F_NFCID1,
					&nfcid_skb);
			अगर (r < 0)
				जाओ निकास;

			अगर (nfcid_skb->len > NFC_NFCID1_MAXSIZE) अणु
				r = -EPROTO;
				जाओ निकास;
			पूर्ण
			स_नकल(target->sensf_res, nfcid_skb->data,
				nfcid_skb->len);
			target->sensf_res_len = nfcid_skb->len;
			target->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
		पूर्ण
		target->hci_पढ़ोer_gate = ST21NFCA_RF_READER_F_GATE;
	पूर्ण
	r = 1;
निकास:
	kमुक्त_skb(nfcid_skb);
	वापस r;
पूर्ण

#घोषणा ST21NFCA_CB_TYPE_READER_ISO15693 1
अटल व्योम st21nfca_hci_data_exchange_cb(व्योम *context, काष्ठा sk_buff *skb,
					  पूर्णांक err)
अणु
	काष्ठा st21nfca_hci_info *info = context;

	चयन (info->async_cb_type) अणु
	हाल ST21NFCA_CB_TYPE_READER_ISO15693:
		अगर (err == 0)
			skb_trim(skb, skb->len - 1);
		info->async_cb(info->async_cb_context, skb, err);
		अवरोध;
	शेष:
		अगर (err == 0)
			kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Returns:
 * <= 0: driver handled the data exchange
 *    1: driver करोesn't especially handle, please करो standard processing
 */
अटल पूर्णांक st21nfca_hci_im_transceive(काष्ठा nfc_hci_dev *hdev,
				      काष्ठा nfc_target *target,
				      काष्ठा sk_buff *skb,
				      data_exchange_cb_t cb, व्योम *cb_context)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	pr_info(DRIVER_DESC ": %s for gate=%d len=%d\n", __func__,
		target->hci_पढ़ोer_gate, skb->len);

	चयन (target->hci_पढ़ोer_gate) अणु
	हाल ST21NFCA_RF_READER_F_GATE:
		अगर (target->supported_protocols == NFC_PROTO_NFC_DEP_MASK)
			वापस st21nfca_im_send_dep_req(hdev, skb);

		*(u8 *)skb_push(skb, 1) = 0x1a;
		वापस nfc_hci_send_cmd_async(hdev, target->hci_पढ़ोer_gate,
					      ST21NFCA_WR_XCHG_DATA, skb->data,
					      skb->len, cb, cb_context);
	हाल ST21NFCA_RF_READER_14443_3_A_GATE:
		*(u8 *)skb_push(skb, 1) = 0x1a;	/* CTR, see spec:10.2.2.1 */

		वापस nfc_hci_send_cmd_async(hdev, target->hci_पढ़ोer_gate,
					      ST21NFCA_WR_XCHG_DATA, skb->data,
					      skb->len, cb, cb_context);
	हाल ST21NFCA_RF_READER_ISO15693_GATE:
		info->async_cb_type = ST21NFCA_CB_TYPE_READER_ISO15693;
		info->async_cb = cb;
		info->async_cb_context = cb_context;

		*(u8 *)skb_push(skb, 1) = 0x17;

		वापस nfc_hci_send_cmd_async(hdev, target->hci_पढ़ोer_gate,
					      ST21NFCA_WR_XCHG_DATA, skb->data,
					      skb->len,
					      st21nfca_hci_data_exchange_cb,
					      info);
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक st21nfca_hci_पंचांग_send(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	वापस st21nfca_पंचांग_send_dep_res(hdev, skb);
पूर्ण

अटल पूर्णांक st21nfca_hci_check_presence(काष्ठा nfc_hci_dev *hdev,
				       काष्ठा nfc_target *target)
अणु
	u8 fwi = 0x11;

	चयन (target->hci_पढ़ोer_gate) अणु
	हाल NFC_HCI_RF_READER_A_GATE:
	हाल NFC_HCI_RF_READER_B_GATE:
		/*
		 * PRESENCE_CHECK on those gates is available
		 * However, the answer to this command is taking 3 * fwi
		 * अगर the card is no present.
		 * Instead, we send an empty I-Frame with a very लघु
		 * configurable fwi ~604तगs.
		 */
		वापस nfc_hci_send_cmd(hdev, target->hci_पढ़ोer_gate,
					ST21NFCA_WR_XCHG_DATA, &fwi, 1, शून्य);
	हाल ST21NFCA_RF_READER_14443_3_A_GATE:
		वापस nfc_hci_send_cmd(hdev, target->hci_पढ़ोer_gate,
					ST21NFCA_RF_READER_CMD_PRESENCE_CHECK,
					शून्य, 0, शून्य);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम st21nfca_hci_cmd_received(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 cmd,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	u8 gate = hdev->pipes[pipe].gate;

	pr_debug("cmd: %x\n", cmd);

	चयन (cmd) अणु
	हाल NFC_HCI_ANY_OPEN_PIPE:
		अगर (gate != ST21NFCA_APDU_READER_GATE &&
			hdev->pipes[pipe].dest_host != NFC_HCI_UICC_HOST_ID)
			info->se_info.count_pipes++;

		अगर (info->se_info.count_pipes == info->se_info.expected_pipes) अणु
			del_समयr_sync(&info->se_info.se_active_समयr);
			info->se_info.se_active = false;
			info->se_info.count_pipes = 0;
			complete(&info->se_info.req_completion);
		पूर्ण
	अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक st21nfca_admin_event_received(काष्ठा nfc_hci_dev *hdev, u8 event,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	pr_debug("admin event: %x\n", event);

	चयन (event) अणु
	हाल ST21NFCA_EVT_HOT_PLUG:
		अगर (info->se_info.se_active) अणु
			अगर (!ST21NFCA_EVT_HOT_PLUG_IS_INHIBITED(skb)) अणु
				del_समयr_sync(&info->se_info.se_active_समयr);
				info->se_info.se_active = false;
				complete(&info->se_info.req_completion);
			पूर्ण अन्यथा अणु
				mod_समयr(&info->se_info.se_active_समयr,
					jअगरfies +
					msecs_to_jअगरfies(ST21NFCA_SE_TO_PIPES));
			पूर्ण
		पूर्ण
	अवरोध;
	शेष:
		nfc_err(&hdev->ndev->dev, "Unexpected event on admin gate\n");
	पूर्ण
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

/*
 * Returns:
 * <= 0: driver handled the event, skb consumed
 *    1: driver करोes not handle the event, please करो standard processing
 */
अटल पूर्णांक st21nfca_hci_event_received(काष्ठा nfc_hci_dev *hdev, u8 pipe,
				       u8 event, काष्ठा sk_buff *skb)
अणु
	u8 gate = hdev->pipes[pipe].gate;
	u8 host = hdev->pipes[pipe].dest_host;

	pr_debug("hci event: %d gate: %x\n", event, gate);

	चयन (gate) अणु
	हाल NFC_HCI_ADMIN_GATE:
		वापस st21nfca_admin_event_received(hdev, event, skb);
	हाल ST21NFCA_RF_CARD_F_GATE:
		वापस st21nfca_dep_event_received(hdev, event, skb);
	हाल ST21NFCA_CONNECTIVITY_GATE:
		वापस st21nfca_connectivity_event_received(hdev, host,
							event, skb);
	हाल ST21NFCA_APDU_READER_GATE:
		वापस st21nfca_apdu_पढ़ोer_event_received(hdev, event, skb);
	हाल NFC_HCI_LOOPBACK_GATE:
		वापस st21nfca_hci_loopback_event_received(hdev, event, skb);
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल काष्ठा nfc_hci_ops st21nfca_hci_ops = अणु
	.खोलो = st21nfca_hci_खोलो,
	.बंद = st21nfca_hci_बंद,
	.load_session = st21nfca_hci_load_session,
	.hci_पढ़ोy = st21nfca_hci_पढ़ोy,
	.xmit = st21nfca_hci_xmit,
	.start_poll = st21nfca_hci_start_poll,
	.stop_poll = st21nfca_hci_stop_poll,
	.dep_link_up = st21nfca_hci_dep_link_up,
	.dep_link_करोwn = st21nfca_hci_dep_link_करोwn,
	.target_from_gate = st21nfca_hci_target_from_gate,
	.complete_target_discovered = st21nfca_hci_complete_target_discovered,
	.im_transceive = st21nfca_hci_im_transceive,
	.पंचांग_send = st21nfca_hci_पंचांग_send,
	.check_presence = st21nfca_hci_check_presence,
	.event_received = st21nfca_hci_event_received,
	.cmd_received = st21nfca_hci_cmd_received,
	.discover_se = st21nfca_hci_discover_se,
	.enable_se = st21nfca_hci_enable_se,
	.disable_se = st21nfca_hci_disable_se,
	.se_io = st21nfca_hci_se_io,
पूर्ण;

पूर्णांक st21nfca_hci_probe(व्योम *phy_id, काष्ठा nfc_phy_ops *phy_ops,
		       अक्षर *llc_name, पूर्णांक phy_headroom, पूर्णांक phy_tailroom,
		       पूर्णांक phy_payload, काष्ठा nfc_hci_dev **hdev,
			   काष्ठा st21nfca_se_status *se_status)
अणु
	काष्ठा st21nfca_hci_info *info;
	पूर्णांक r = 0;
	पूर्णांक dev_num;
	u32 protocols;
	काष्ठा nfc_hci_init_data init_data;
	अचिन्हित दीर्घ quirks = 0;

	info = kzalloc(माप(काष्ठा st21nfca_hci_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->phy_ops = phy_ops;
	info->phy_id = phy_id;
	info->state = ST21NFCA_ST_COLD;
	mutex_init(&info->info_lock);

	init_data.gate_count = ARRAY_SIZE(st21nfca_gates);

	स_नकल(init_data.gates, st21nfca_gates, माप(st21nfca_gates));

	/*
	 * Session id must include the driver name + i2c bus addr
	 * persistent info to discriminate 2 identical chips
	 */
	dev_num = find_first_zero_bit(dev_mask, ST21NFCA_NUM_DEVICES);
	अगर (dev_num >= ST21NFCA_NUM_DEVICES) अणु
		r = -ENODEV;
		जाओ err_alloc_hdev;
	पूर्ण

	set_bit(dev_num, dev_mask);

	scnम_लिखो(init_data.session_id, माप(init_data.session_id), "%s%2x",
		  "ST21AH", dev_num);

	protocols = NFC_PROTO_JEWEL_MASK |
	    NFC_PROTO_MIFARE_MASK |
	    NFC_PROTO_FELICA_MASK |
	    NFC_PROTO_ISO14443_MASK |
	    NFC_PROTO_ISO14443_B_MASK |
	    NFC_PROTO_ISO15693_MASK |
	    NFC_PROTO_NFC_DEP_MASK;

	set_bit(NFC_HCI_QUIRK_SHORT_CLEAR, &quirks);

	info->hdev =
	    nfc_hci_allocate_device(&st21nfca_hci_ops, &init_data, quirks,
				    protocols, llc_name,
				    phy_headroom + ST21NFCA_CMDS_HEADROOM,
				    phy_tailroom, phy_payload);

	अगर (!info->hdev) अणु
		pr_err("Cannot allocate nfc hdev.\n");
		r = -ENOMEM;
		जाओ err_alloc_hdev;
	पूर्ण

	info->se_status = se_status;

	nfc_hci_set_clientdata(info->hdev, info);

	r = nfc_hci_रेजिस्टर_device(info->hdev);
	अगर (r)
		जाओ err_regdev;

	*hdev = info->hdev;
	st21nfca_dep_init(info->hdev);
	st21nfca_se_init(info->hdev);
	st21nfca_venकरोr_cmds_init(info->hdev);

	वापस 0;

err_regdev:
	nfc_hci_मुक्त_device(info->hdev);

err_alloc_hdev:
	kमुक्त(info);

	वापस r;
पूर्ण
EXPORT_SYMBOL(st21nfca_hci_probe);

व्योम st21nfca_hci_हटाओ(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	st21nfca_dep_deinit(hdev);
	st21nfca_se_deinit(hdev);
	nfc_hci_unरेजिस्टर_device(hdev);
	nfc_hci_मुक्त_device(hdev);
	kमुक्त(info);
पूर्ण
EXPORT_SYMBOL(st21nfca_hci_हटाओ);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
