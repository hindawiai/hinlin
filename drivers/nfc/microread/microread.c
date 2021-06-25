<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HCI based Driver क्रम Inside Secure microपढ़ो NFC Chip
 *
 * Copyright (C) 2013  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc-ccitt.h>

#समावेश <linux/nfc.h>
#समावेश <net/nfc/nfc.h>
#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>

#समावेश "microread.h"

/* Proprietary gates, events, commands and रेजिस्टरs */
/* Admin */
#घोषणा MICROREAD_GATE_ID_ADM NFC_HCI_ADMIN_GATE
#घोषणा MICROREAD_GATE_ID_MGT 0x01
#घोषणा MICROREAD_GATE_ID_OS 0x02
#घोषणा MICROREAD_GATE_ID_TESTRF 0x03
#घोषणा MICROREAD_GATE_ID_LOOPBACK NFC_HCI_LOOPBACK_GATE
#घोषणा MICROREAD_GATE_ID_IDT NFC_HCI_ID_MGMT_GATE
#घोषणा MICROREAD_GATE_ID_LMS NFC_HCI_LINK_MGMT_GATE

/* Reader */
#घोषणा MICROREAD_GATE_ID_MREAD_GEN 0x10
#घोषणा MICROREAD_GATE_ID_MREAD_ISO_B NFC_HCI_RF_READER_B_GATE
#घोषणा MICROREAD_GATE_ID_MREAD_NFC_T1 0x12
#घोषणा MICROREAD_GATE_ID_MREAD_ISO_A NFC_HCI_RF_READER_A_GATE
#घोषणा MICROREAD_GATE_ID_MREAD_NFC_T3 0x14
#घोषणा MICROREAD_GATE_ID_MREAD_ISO_15_3 0x15
#घोषणा MICROREAD_GATE_ID_MREAD_ISO_15_2 0x16
#घोषणा MICROREAD_GATE_ID_MREAD_ISO_B_3 0x17
#घोषणा MICROREAD_GATE_ID_MREAD_BPRIME 0x18
#घोषणा MICROREAD_GATE_ID_MREAD_ISO_A_3 0x19

/* Card */
#घोषणा MICROREAD_GATE_ID_MCARD_GEN 0x20
#घोषणा MICROREAD_GATE_ID_MCARD_ISO_B 0x21
#घोषणा MICROREAD_GATE_ID_MCARD_BPRIME 0x22
#घोषणा MICROREAD_GATE_ID_MCARD_ISO_A 0x23
#घोषणा MICROREAD_GATE_ID_MCARD_NFC_T3 0x24
#घोषणा MICROREAD_GATE_ID_MCARD_ISO_15_3 0x25
#घोषणा MICROREAD_GATE_ID_MCARD_ISO_15_2 0x26
#घोषणा MICROREAD_GATE_ID_MCARD_ISO_B_2 0x27
#घोषणा MICROREAD_GATE_ID_MCARD_ISO_CUSTOM 0x28
#घोषणा MICROREAD_GATE_ID_SECURE_ELEMENT 0x2F

/* P2P */
#घोषणा MICROREAD_GATE_ID_P2P_GEN 0x30
#घोषणा MICROREAD_GATE_ID_P2P_TARGET 0x31
#घोषणा MICROREAD_PAR_P2P_TARGET_MODE 0x01
#घोषणा MICROREAD_PAR_P2P_TARGET_GT 0x04
#घोषणा MICROREAD_GATE_ID_P2P_INITIATOR 0x32
#घोषणा MICROREAD_PAR_P2P_INITIATOR_GI 0x01
#घोषणा MICROREAD_PAR_P2P_INITIATOR_GT 0x03

/* Those pipes are created/खोलोed by शेष in the chip */
#घोषणा MICROREAD_PIPE_ID_LMS 0x00
#घोषणा MICROREAD_PIPE_ID_ADMIN 0x01
#घोषणा MICROREAD_PIPE_ID_MGT 0x02
#घोषणा MICROREAD_PIPE_ID_OS 0x03
#घोषणा MICROREAD_PIPE_ID_HDS_LOOPBACK 0x04
#घोषणा MICROREAD_PIPE_ID_HDS_IDT 0x05
#घोषणा MICROREAD_PIPE_ID_HDS_MCARD_ISO_B 0x08
#घोषणा MICROREAD_PIPE_ID_HDS_MCARD_ISO_BPRIME 0x09
#घोषणा MICROREAD_PIPE_ID_HDS_MCARD_ISO_A 0x0A
#घोषणा MICROREAD_PIPE_ID_HDS_MCARD_ISO_15_3 0x0B
#घोषणा MICROREAD_PIPE_ID_HDS_MCARD_ISO_15_2 0x0C
#घोषणा MICROREAD_PIPE_ID_HDS_MCARD_NFC_T3 0x0D
#घोषणा MICROREAD_PIPE_ID_HDS_MCARD_ISO_B_2 0x0E
#घोषणा MICROREAD_PIPE_ID_HDS_MCARD_CUSTOM 0x0F
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_ISO_B 0x10
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_NFC_T1 0x11
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_ISO_A 0x12
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_ISO_15_3 0x13
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_ISO_15_2 0x14
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_NFC_T3 0x15
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_ISO_B_3 0x16
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_BPRIME 0x17
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_ISO_A_3 0x18
#घोषणा MICROREAD_PIPE_ID_HDS_MREAD_GEN 0x1B
#घोषणा MICROREAD_PIPE_ID_HDS_STACKED_ELEMENT 0x1C
#घोषणा MICROREAD_PIPE_ID_HDS_INSTANCES 0x1D
#घोषणा MICROREAD_PIPE_ID_HDS_TESTRF 0x1E
#घोषणा MICROREAD_PIPE_ID_HDS_P2P_TARGET 0x1F
#घोषणा MICROREAD_PIPE_ID_HDS_P2P_INITIATOR 0x20

/* Events */
#घोषणा MICROREAD_EVT_MREAD_DISCOVERY_OCCURED NFC_HCI_EVT_TARGET_DISCOVERED
#घोषणा MICROREAD_EVT_MREAD_CARD_FOUND 0x3D
#घोषणा MICROREAD_EMCF_A_ATQA 0
#घोषणा MICROREAD_EMCF_A_SAK 2
#घोषणा MICROREAD_EMCF_A_LEN 3
#घोषणा MICROREAD_EMCF_A_UID 4
#घोषणा MICROREAD_EMCF_A3_ATQA 0
#घोषणा MICROREAD_EMCF_A3_SAK 2
#घोषणा MICROREAD_EMCF_A3_LEN 3
#घोषणा MICROREAD_EMCF_A3_UID 4
#घोषणा MICROREAD_EMCF_B_UID 0
#घोषणा MICROREAD_EMCF_T1_ATQA 0
#घोषणा MICROREAD_EMCF_T1_UID 4
#घोषणा MICROREAD_EMCF_T3_UID 0
#घोषणा MICROREAD_EVT_MREAD_DISCOVERY_START NFC_HCI_EVT_READER_REQUESTED
#घोषणा MICROREAD_EVT_MREAD_DISCOVERY_START_SOME 0x3E
#घोषणा MICROREAD_EVT_MREAD_DISCOVERY_STOP NFC_HCI_EVT_END_OPERATION
#घोषणा MICROREAD_EVT_MREAD_SIM_REQUESTS 0x3F
#घोषणा MICROREAD_EVT_MCARD_EXCHANGE NFC_HCI_EVT_TARGET_DISCOVERED
#घोषणा MICROREAD_EVT_P2P_INITIATOR_EXCHANGE_TO_RF 0x20
#घोषणा MICROREAD_EVT_P2P_INITIATOR_EXCHANGE_FROM_RF 0x21
#घोषणा MICROREAD_EVT_MCARD_FIELD_ON 0x11
#घोषणा MICROREAD_EVT_P2P_TARGET_ACTIVATED 0x13
#घोषणा MICROREAD_EVT_P2P_TARGET_DEACTIVATED 0x12
#घोषणा MICROREAD_EVT_MCARD_FIELD_OFF 0x14

/* Commands */
#घोषणा MICROREAD_CMD_MREAD_EXCHANGE 0x10
#घोषणा MICROREAD_CMD_MREAD_SUBSCRIBE 0x3F

/* Hosts IDs */
#घोषणा MICROREAD_ELT_ID_HDS NFC_HCI_TERMINAL_HOST_ID
#घोषणा MICROREAD_ELT_ID_SIM NFC_HCI_UICC_HOST_ID
#घोषणा MICROREAD_ELT_ID_SE1 0x03
#घोषणा MICROREAD_ELT_ID_SE2 0x04
#घोषणा MICROREAD_ELT_ID_SE3 0x05

अटल काष्ठा nfc_hci_gate microपढ़ो_gates[] = अणु
	अणुMICROREAD_GATE_ID_ADM, MICROREAD_PIPE_ID_ADMINपूर्ण,
	अणुMICROREAD_GATE_ID_LOOPBACK, MICROREAD_PIPE_ID_HDS_LOOPBACKपूर्ण,
	अणुMICROREAD_GATE_ID_IDT, MICROREAD_PIPE_ID_HDS_IDTपूर्ण,
	अणुMICROREAD_GATE_ID_LMS, MICROREAD_PIPE_ID_LMSपूर्ण,
	अणुMICROREAD_GATE_ID_MREAD_ISO_B, MICROREAD_PIPE_ID_HDS_MREAD_ISO_Bपूर्ण,
	अणुMICROREAD_GATE_ID_MREAD_ISO_A, MICROREAD_PIPE_ID_HDS_MREAD_ISO_Aपूर्ण,
	अणुMICROREAD_GATE_ID_MREAD_ISO_A_3, MICROREAD_PIPE_ID_HDS_MREAD_ISO_A_3पूर्ण,
	अणुMICROREAD_GATE_ID_MGT, MICROREAD_PIPE_ID_MGTपूर्ण,
	अणुMICROREAD_GATE_ID_OS, MICROREAD_PIPE_ID_OSपूर्ण,
	अणुMICROREAD_GATE_ID_MREAD_NFC_T1, MICROREAD_PIPE_ID_HDS_MREAD_NFC_T1पूर्ण,
	अणुMICROREAD_GATE_ID_MREAD_NFC_T3, MICROREAD_PIPE_ID_HDS_MREAD_NFC_T3पूर्ण,
	अणुMICROREAD_GATE_ID_P2P_TARGET, MICROREAD_PIPE_ID_HDS_P2P_TARGETपूर्ण,
	अणुMICROREAD_GATE_ID_P2P_INITIATOR, MICROREAD_PIPE_ID_HDS_P2P_INITIATORपूर्ण
पूर्ण;

/* Largest headroom needed क्रम outgoing custom commands */
#घोषणा MICROREAD_CMDS_HEADROOM	2
#घोषणा MICROREAD_CMD_TAILROOM	2

काष्ठा microपढ़ो_info अणु
	काष्ठा nfc_phy_ops *phy_ops;
	व्योम *phy_id;

	काष्ठा nfc_hci_dev *hdev;

	पूर्णांक async_cb_type;
	data_exchange_cb_t async_cb;
	व्योम *async_cb_context;
पूर्ण;

अटल पूर्णांक microपढ़ो_खोलो(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा microपढ़ो_info *info = nfc_hci_get_clientdata(hdev);

	वापस info->phy_ops->enable(info->phy_id);
पूर्ण

अटल व्योम microपढ़ो_बंद(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा microपढ़ो_info *info = nfc_hci_get_clientdata(hdev);

	info->phy_ops->disable(info->phy_id);
पूर्ण

अटल पूर्णांक microपढ़ो_hci_पढ़ोy(काष्ठा nfc_hci_dev *hdev)
अणु
	पूर्णांक r;
	u8 param[4];

	param[0] = 0x03;
	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_ISO_A,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, param, 1, शून्य);
	अगर (r)
		वापस r;

	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_ISO_A_3,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, शून्य, 0, शून्य);
	अगर (r)
		वापस r;

	param[0] = 0x00;
	param[1] = 0x03;
	param[2] = 0x00;
	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_ISO_B,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, param, 3, शून्य);
	अगर (r)
		वापस r;

	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_NFC_T1,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, शून्य, 0, शून्य);
	अगर (r)
		वापस r;

	param[0] = 0xFF;
	param[1] = 0xFF;
	param[2] = 0x00;
	param[3] = 0x00;
	r = nfc_hci_send_cmd(hdev, MICROREAD_GATE_ID_MREAD_NFC_T3,
			     MICROREAD_CMD_MREAD_SUBSCRIBE, param, 4, शून्य);

	वापस r;
पूर्ण

अटल पूर्णांक microपढ़ो_xmit(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा microपढ़ो_info *info = nfc_hci_get_clientdata(hdev);

	वापस info->phy_ops->ग_लिखो(info->phy_id, skb);
पूर्ण

अटल पूर्णांक microपढ़ो_start_poll(काष्ठा nfc_hci_dev *hdev,
				u32 im_protocols, u32 पंचांग_protocols)
अणु
	पूर्णांक r;

	u8 param[2];
	u8 mode;

	param[0] = 0x00;
	param[1] = 0x00;

	अगर (im_protocols & NFC_PROTO_ISO14443_MASK)
		param[0] |= (1 << 2);

	अगर (im_protocols & NFC_PROTO_ISO14443_B_MASK)
		param[0] |= 1;

	अगर (im_protocols & NFC_PROTO_MIFARE_MASK)
		param[1] |= 1;

	अगर (im_protocols & NFC_PROTO_JEWEL_MASK)
		param[0] |= (1 << 1);

	अगर (im_protocols & NFC_PROTO_FELICA_MASK)
		param[0] |= (1 << 5);

	अगर (im_protocols & NFC_PROTO_NFC_DEP_MASK)
		param[1] |= (1 << 1);

	अगर ((im_protocols | पंचांग_protocols) & NFC_PROTO_NFC_DEP_MASK) अणु
		hdev->gb = nfc_get_local_general_bytes(hdev->ndev,
						       &hdev->gb_len);
		अगर (hdev->gb == शून्य || hdev->gb_len == 0) अणु
			im_protocols &= ~NFC_PROTO_NFC_DEP_MASK;
			पंचांग_protocols &= ~NFC_PROTO_NFC_DEP_MASK;
		पूर्ण
	पूर्ण

	r = nfc_hci_send_event(hdev, MICROREAD_GATE_ID_MREAD_ISO_A,
			       MICROREAD_EVT_MREAD_DISCOVERY_STOP, शून्य, 0);
	अगर (r)
		वापस r;

	mode = 0xff;
	r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_TARGET,
			      MICROREAD_PAR_P2P_TARGET_MODE, &mode, 1);
	अगर (r)
		वापस r;

	अगर (im_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_INITIATOR,
				      MICROREAD_PAR_P2P_INITIATOR_GI,
				      hdev->gb, hdev->gb_len);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (पंचांग_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_TARGET,
				      MICROREAD_PAR_P2P_TARGET_GT,
				      hdev->gb, hdev->gb_len);
		अगर (r)
			वापस r;

		mode = 0x02;
		r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_TARGET,
				      MICROREAD_PAR_P2P_TARGET_MODE, &mode, 1);
		अगर (r)
			वापस r;
	पूर्ण

	वापस nfc_hci_send_event(hdev, MICROREAD_GATE_ID_MREAD_ISO_A,
				  MICROREAD_EVT_MREAD_DISCOVERY_START_SOME,
				  param, 2);
पूर्ण

अटल पूर्णांक microपढ़ो_dep_link_up(काष्ठा nfc_hci_dev *hdev,
				काष्ठा nfc_target *target, u8 comm_mode,
				u8 *gb, माप_प्रकार gb_len)
अणु
	काष्ठा sk_buff *rgb_skb = शून्य;
	पूर्णांक r;

	r = nfc_hci_get_param(hdev, target->hci_पढ़ोer_gate,
			      MICROREAD_PAR_P2P_INITIATOR_GT, &rgb_skb);
	अगर (r < 0)
		वापस r;

	अगर (rgb_skb->len == 0 || rgb_skb->len > NFC_GB_MAXSIZE) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	r = nfc_set_remote_general_bytes(hdev->ndev, rgb_skb->data,
					 rgb_skb->len);
	अगर (r == 0)
		r = nfc_dep_link_is_up(hdev->ndev, target->idx, comm_mode,
				       NFC_RF_INITIATOR);
निकास:
	kमुक्त_skb(rgb_skb);

	वापस r;
पूर्ण

अटल पूर्णांक microपढ़ो_dep_link_करोwn(काष्ठा nfc_hci_dev *hdev)
अणु
	वापस nfc_hci_send_event(hdev, MICROREAD_GATE_ID_P2P_INITIATOR,
				  MICROREAD_EVT_MREAD_DISCOVERY_STOP, शून्य, 0);
पूर्ण

अटल पूर्णांक microपढ़ो_target_from_gate(काष्ठा nfc_hci_dev *hdev, u8 gate,
				      काष्ठा nfc_target *target)
अणु
	चयन (gate) अणु
	हाल MICROREAD_GATE_ID_P2P_INITIATOR:
		target->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
		अवरोध;
	शेष:
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक microपढ़ो_complete_target_discovered(काष्ठा nfc_hci_dev *hdev,
						u8 gate,
						काष्ठा nfc_target *target)
अणु
	वापस 0;
पूर्ण

#घोषणा MICROREAD_CB_TYPE_READER_ALL 1

अटल व्योम microपढ़ो_im_transceive_cb(व्योम *context, काष्ठा sk_buff *skb,
				       पूर्णांक err)
अणु
	काष्ठा microपढ़ो_info *info = context;

	चयन (info->async_cb_type) अणु
	हाल MICROREAD_CB_TYPE_READER_ALL:
		अगर (err == 0) अणु
			अगर (skb->len == 0) अणु
				err = -EPROTO;
				kमुक्त_skb(skb);
				info->async_cb(info->async_cb_context, शून्य,
					       -EPROTO);
				वापस;
			पूर्ण

			अगर (skb->data[skb->len - 1] != 0) अणु
				err = nfc_hci_result_to_त्रुटि_सं(
						       skb->data[skb->len - 1]);
				kमुक्त_skb(skb);
				info->async_cb(info->async_cb_context, शून्य,
					       err);
				वापस;
			पूर्ण

			skb_trim(skb, skb->len - 1);	/* RF Error ind. */
		पूर्ण
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
अटल पूर्णांक microपढ़ो_im_transceive(काष्ठा nfc_hci_dev *hdev,
				   काष्ठा nfc_target *target,
				   काष्ठा sk_buff *skb, data_exchange_cb_t cb,
				   व्योम *cb_context)
अणु
	काष्ठा microपढ़ो_info *info = nfc_hci_get_clientdata(hdev);
	u8 control_bits;
	u16 crc;

	pr_info("data exchange to gate 0x%x\n", target->hci_पढ़ोer_gate);

	अगर (target->hci_पढ़ोer_gate == MICROREAD_GATE_ID_P2P_INITIATOR) अणु
		*(u8 *)skb_push(skb, 1) = 0;

		वापस nfc_hci_send_event(hdev, target->hci_पढ़ोer_gate,
				     MICROREAD_EVT_P2P_INITIATOR_EXCHANGE_TO_RF,
				     skb->data, skb->len);
	पूर्ण

	चयन (target->hci_पढ़ोer_gate) अणु
	हाल MICROREAD_GATE_ID_MREAD_ISO_A:
		control_bits = 0xCB;
		अवरोध;
	हाल MICROREAD_GATE_ID_MREAD_ISO_A_3:
		control_bits = 0xCB;
		अवरोध;
	हाल MICROREAD_GATE_ID_MREAD_ISO_B:
		control_bits = 0xCB;
		अवरोध;
	हाल MICROREAD_GATE_ID_MREAD_NFC_T1:
		control_bits = 0x1B;

		crc = crc_ccitt(0xffff, skb->data, skb->len);
		crc = ~crc;
		skb_put_u8(skb, crc & 0xff);
		skb_put_u8(skb, crc >> 8);
		अवरोध;
	हाल MICROREAD_GATE_ID_MREAD_NFC_T3:
		control_bits = 0xDB;
		अवरोध;
	शेष:
		pr_info("Abort im_transceive to invalid gate 0x%x\n",
			target->hci_पढ़ोer_gate);
		वापस 1;
	पूर्ण

	*(u8 *)skb_push(skb, 1) = control_bits;

	info->async_cb_type = MICROREAD_CB_TYPE_READER_ALL;
	info->async_cb = cb;
	info->async_cb_context = cb_context;

	वापस nfc_hci_send_cmd_async(hdev, target->hci_पढ़ोer_gate,
				      MICROREAD_CMD_MREAD_EXCHANGE,
				      skb->data, skb->len,
				      microपढ़ो_im_transceive_cb, info);
पूर्ण

अटल पूर्णांक microपढ़ो_पंचांग_send(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;

	r = nfc_hci_send_event(hdev, MICROREAD_GATE_ID_P2P_TARGET,
			       MICROREAD_EVT_MCARD_EXCHANGE,
			       skb->data, skb->len);

	kमुक्त_skb(skb);

	वापस r;
पूर्ण

अटल व्योम microपढ़ो_target_discovered(काष्ठा nfc_hci_dev *hdev, u8 gate,
					काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_target *tarमाला_लो;
	पूर्णांक r = 0;

	pr_info("target discovered to gate 0x%x\n", gate);

	tarमाला_लो = kzalloc(माप(काष्ठा nfc_target), GFP_KERNEL);
	अगर (tarमाला_लो == शून्य) अणु
		r = -ENOMEM;
		जाओ निकास;
	पूर्ण

	tarमाला_लो->hci_पढ़ोer_gate = gate;

	चयन (gate) अणु
	हाल MICROREAD_GATE_ID_MREAD_ISO_A:
		tarमाला_लो->supported_protocols =
		      nfc_hci_sak_to_protocol(skb->data[MICROREAD_EMCF_A_SAK]);
		tarमाला_लो->sens_res =
			 be16_to_cpu(*(u16 *)&skb->data[MICROREAD_EMCF_A_ATQA]);
		tarमाला_लो->sel_res = skb->data[MICROREAD_EMCF_A_SAK];
		tarमाला_लो->nfcid1_len = skb->data[MICROREAD_EMCF_A_LEN];
		अगर (tarमाला_लो->nfcid1_len > माप(tarमाला_लो->nfcid1)) अणु
			r = -EINVAL;
			जाओ निकास_मुक्त;
		पूर्ण
		स_नकल(tarमाला_लो->nfcid1, &skb->data[MICROREAD_EMCF_A_UID],
		       tarमाला_लो->nfcid1_len);
		अवरोध;
	हाल MICROREAD_GATE_ID_MREAD_ISO_A_3:
		tarमाला_लो->supported_protocols =
		      nfc_hci_sak_to_protocol(skb->data[MICROREAD_EMCF_A3_SAK]);
		tarमाला_लो->sens_res =
			 be16_to_cpu(*(u16 *)&skb->data[MICROREAD_EMCF_A3_ATQA]);
		tarमाला_लो->sel_res = skb->data[MICROREAD_EMCF_A3_SAK];
		tarमाला_लो->nfcid1_len = skb->data[MICROREAD_EMCF_A3_LEN];
		अगर (tarमाला_लो->nfcid1_len > माप(tarमाला_लो->nfcid1)) अणु
			r = -EINVAL;
			जाओ निकास_मुक्त;
		पूर्ण
		स_नकल(tarमाला_लो->nfcid1, &skb->data[MICROREAD_EMCF_A3_UID],
		       tarमाला_लो->nfcid1_len);
		अवरोध;
	हाल MICROREAD_GATE_ID_MREAD_ISO_B:
		tarमाला_लो->supported_protocols = NFC_PROTO_ISO14443_B_MASK;
		स_नकल(tarमाला_लो->nfcid1, &skb->data[MICROREAD_EMCF_B_UID], 4);
		tarमाला_लो->nfcid1_len = 4;
		अवरोध;
	हाल MICROREAD_GATE_ID_MREAD_NFC_T1:
		tarमाला_लो->supported_protocols = NFC_PROTO_JEWEL_MASK;
		tarमाला_लो->sens_res =
			le16_to_cpu(*(u16 *)&skb->data[MICROREAD_EMCF_T1_ATQA]);
		स_नकल(tarमाला_लो->nfcid1, &skb->data[MICROREAD_EMCF_T1_UID], 4);
		tarमाला_लो->nfcid1_len = 4;
		अवरोध;
	हाल MICROREAD_GATE_ID_MREAD_NFC_T3:
		tarमाला_लो->supported_protocols = NFC_PROTO_FELICA_MASK;
		स_नकल(tarमाला_लो->nfcid1, &skb->data[MICROREAD_EMCF_T3_UID], 8);
		tarमाला_लो->nfcid1_len = 8;
		अवरोध;
	शेष:
		pr_info("discard target discovered to gate 0x%x\n", gate);
		जाओ निकास_मुक्त;
	पूर्ण

	r = nfc_tarमाला_लो_found(hdev->ndev, tarमाला_लो, 1);

निकास_मुक्त:
	kमुक्त(tarमाला_लो);

निकास:
	kमुक्त_skb(skb);

	अगर (r)
		pr_err("Failed to handle discovered target err=%d\n", r);
पूर्ण

अटल पूर्णांक microपढ़ो_event_received(काष्ठा nfc_hci_dev *hdev, u8 pipe,
				     u8 event, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;
	u8 gate = hdev->pipes[pipe].gate;
	u8 mode;

	pr_info("Microread received event 0x%x to gate 0x%x\n", event, gate);

	चयन (event) अणु
	हाल MICROREAD_EVT_MREAD_CARD_FOUND:
		microपढ़ो_target_discovered(hdev, gate, skb);
		वापस 0;

	हाल MICROREAD_EVT_P2P_INITIATOR_EXCHANGE_FROM_RF:
		अगर (skb->len < 1) अणु
			kमुक्त_skb(skb);
			वापस -EPROTO;
		पूर्ण

		अगर (skb->data[skb->len - 1]) अणु
			kमुक्त_skb(skb);
			वापस -EIO;
		पूर्ण

		skb_trim(skb, skb->len - 1);

		r = nfc_पंचांग_data_received(hdev->ndev, skb);
		अवरोध;

	हाल MICROREAD_EVT_MCARD_FIELD_ON:
	हाल MICROREAD_EVT_MCARD_FIELD_OFF:
		kमुक्त_skb(skb);
		वापस 0;

	हाल MICROREAD_EVT_P2P_TARGET_ACTIVATED:
		r = nfc_पंचांग_activated(hdev->ndev, NFC_PROTO_NFC_DEP_MASK,
				     NFC_COMM_PASSIVE, skb->data,
				     skb->len);

		kमुक्त_skb(skb);
		अवरोध;

	हाल MICROREAD_EVT_MCARD_EXCHANGE:
		अगर (skb->len < 1) अणु
			kमुक्त_skb(skb);
			वापस -EPROTO;
		पूर्ण

		अगर (skb->data[skb->len-1]) अणु
			kमुक्त_skb(skb);
			वापस -EIO;
		पूर्ण

		skb_trim(skb, skb->len - 1);

		r = nfc_पंचांग_data_received(hdev->ndev, skb);
		अवरोध;

	हाल MICROREAD_EVT_P2P_TARGET_DEACTIVATED:
		kमुक्त_skb(skb);

		mode = 0xff;
		r = nfc_hci_set_param(hdev, MICROREAD_GATE_ID_P2P_TARGET,
				      MICROREAD_PAR_P2P_TARGET_MODE, &mode, 1);
		अगर (r)
			अवरोध;

		r = nfc_hci_send_event(hdev, gate,
				       MICROREAD_EVT_MREAD_DISCOVERY_STOP, शून्य,
				       0);
		अवरोध;

	शेष:
		वापस 1;
	पूर्ण

	वापस r;
पूर्ण

अटल काष्ठा nfc_hci_ops microपढ़ो_hci_ops = अणु
	.खोलो = microपढ़ो_खोलो,
	.बंद = microपढ़ो_बंद,
	.hci_पढ़ोy = microपढ़ो_hci_पढ़ोy,
	.xmit = microपढ़ो_xmit,
	.start_poll = microपढ़ो_start_poll,
	.dep_link_up = microपढ़ो_dep_link_up,
	.dep_link_करोwn = microपढ़ो_dep_link_करोwn,
	.target_from_gate = microपढ़ो_target_from_gate,
	.complete_target_discovered = microपढ़ो_complete_target_discovered,
	.im_transceive = microपढ़ो_im_transceive,
	.पंचांग_send = microपढ़ो_पंचांग_send,
	.check_presence = शून्य,
	.event_received = microपढ़ो_event_received,
पूर्ण;

पूर्णांक microपढ़ो_probe(व्योम *phy_id, काष्ठा nfc_phy_ops *phy_ops, अक्षर *llc_name,
		    पूर्णांक phy_headroom, पूर्णांक phy_tailroom, पूर्णांक phy_payload,
		    काष्ठा nfc_hci_dev **hdev)
अणु
	काष्ठा microपढ़ो_info *info;
	अचिन्हित दीर्घ quirks = 0;
	u32 protocols;
	काष्ठा nfc_hci_init_data init_data;
	पूर्णांक r;

	info = kzalloc(माप(काष्ठा microपढ़ो_info), GFP_KERNEL);
	अगर (!info) अणु
		r = -ENOMEM;
		जाओ err_info_alloc;
	पूर्ण

	info->phy_ops = phy_ops;
	info->phy_id = phy_id;

	init_data.gate_count = ARRAY_SIZE(microपढ़ो_gates);
	स_नकल(init_data.gates, microपढ़ो_gates, माप(microपढ़ो_gates));

	म_नकल(init_data.session_id, "MICROREA");

	set_bit(NFC_HCI_QUIRK_SHORT_CLEAR, &quirks);

	protocols = NFC_PROTO_JEWEL_MASK |
		    NFC_PROTO_MIFARE_MASK |
		    NFC_PROTO_FELICA_MASK |
		    NFC_PROTO_ISO14443_MASK |
		    NFC_PROTO_ISO14443_B_MASK |
		    NFC_PROTO_NFC_DEP_MASK;

	info->hdev = nfc_hci_allocate_device(&microपढ़ो_hci_ops, &init_data,
					     quirks, protocols, llc_name,
					     phy_headroom +
					     MICROREAD_CMDS_HEADROOM,
					     phy_tailroom +
					     MICROREAD_CMD_TAILROOM,
					     phy_payload);
	अगर (!info->hdev) अणु
		pr_err("Cannot allocate nfc hdev\n");
		r = -ENOMEM;
		जाओ err_alloc_hdev;
	पूर्ण

	nfc_hci_set_clientdata(info->hdev, info);

	r = nfc_hci_रेजिस्टर_device(info->hdev);
	अगर (r)
		जाओ err_regdev;

	*hdev = info->hdev;

	वापस 0;

err_regdev:
	nfc_hci_मुक्त_device(info->hdev);

err_alloc_hdev:
	kमुक्त(info);

err_info_alloc:
	वापस r;
पूर्ण
EXPORT_SYMBOL(microपढ़ो_probe);

व्योम microपढ़ो_हटाओ(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा microपढ़ो_info *info = nfc_hci_get_clientdata(hdev);

	nfc_hci_unरेजिस्टर_device(hdev);
	nfc_hci_मुक्त_device(hdev);
	kमुक्त(info);
पूर्ण
EXPORT_SYMBOL(microपढ़ो_हटाओ);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
