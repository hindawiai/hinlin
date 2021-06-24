<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HCI based Driver क्रम NXP PN544 NFC Chip
 *
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <linux/nfc.h>
#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>

#समावेश "pn544.h"

/* Timing restrictions (ms) */
#घोषणा PN544_HCI_RESETVEN_TIME		30

क्रमागत pn544_state अणु
	PN544_ST_COLD,
	PN544_ST_FW_READY,
	PN544_ST_READY,
पूर्ण;

#घोषणा FULL_VERSION_LEN 11

/* Proprietary commands */
#घोषणा PN544_WRITE		0x3f
#घोषणा PN544_TEST_SWP		0x21

/* Proprietary gates, events, commands and रेजिस्टरs */

/* NFC_HCI_RF_READER_A_GATE additional रेजिस्टरs and commands */
#घोषणा PN544_RF_READER_A_AUTO_ACTIVATION			0x10
#घोषणा PN544_RF_READER_A_CMD_CONTINUE_ACTIVATION		0x12
#घोषणा PN544_MIFARE_CMD					0x21

/* Commands that apply to all RF पढ़ोers */
#घोषणा PN544_RF_READER_CMD_PRESENCE_CHECK	0x30
#घोषणा PN544_RF_READER_CMD_ACTIVATE_NEXT	0x32

/* NFC_HCI_ID_MGMT_GATE additional रेजिस्टरs */
#घोषणा PN544_ID_MGMT_FULL_VERSION_SW		0x10

#घोषणा PN544_RF_READER_ISO15693_GATE		0x12

#घोषणा PN544_RF_READER_F_GATE			0x14
#घोषणा PN544_FELICA_ID				0x04
#घोषणा PN544_FELICA_RAW			0x20

#घोषणा PN544_RF_READER_JEWEL_GATE		0x15
#घोषणा PN544_JEWEL_RAW_CMD			0x23

#घोषणा PN544_RF_READER_NFCIP1_INITIATOR_GATE	0x30
#घोषणा PN544_RF_READER_NFCIP1_TARGET_GATE	0x31

#घोषणा PN544_SYS_MGMT_GATE			0x90
#घोषणा PN544_SYS_MGMT_INFO_NOTIFICATION	0x02

#घोषणा PN544_POLLING_LOOP_MGMT_GATE		0x94
#घोषणा PN544_DEP_MODE				0x01
#घोषणा PN544_DEP_ATR_REQ			0x02
#घोषणा PN544_DEP_ATR_RES			0x03
#घोषणा PN544_DEP_MERGE				0x0D
#घोषणा PN544_PL_RDPHASES			0x06
#घोषणा PN544_PL_EMULATION			0x07
#घोषणा PN544_PL_NFCT_DEACTIVATED		0x09

#घोषणा PN544_SWP_MGMT_GATE			0xA0
#घोषणा PN544_SWP_DEFAULT_MODE			0x01

#घोषणा PN544_NFC_WI_MGMT_GATE			0xA1
#घोषणा PN544_NFC_ESE_DEFAULT_MODE		0x01

#घोषणा PN544_HCI_EVT_SND_DATA			0x01
#घोषणा PN544_HCI_EVT_ACTIVATED			0x02
#घोषणा PN544_HCI_EVT_DEACTIVATED		0x03
#घोषणा PN544_HCI_EVT_RCV_DATA			0x04
#घोषणा PN544_HCI_EVT_CONTINUE_MI		0x05
#घोषणा PN544_HCI_EVT_SWITCH_MODE		0x03

#घोषणा PN544_HCI_CMD_ATTREQUEST		0x12
#घोषणा PN544_HCI_CMD_CONTINUE_ACTIVATION	0x13

अटल काष्ठा nfc_hci_gate pn544_gates[] = अणु
	अणुNFC_HCI_ADMIN_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुNFC_HCI_LOOPBACK_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुNFC_HCI_ID_MGMT_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुNFC_HCI_LINK_MGMT_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुNFC_HCI_RF_READER_B_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुNFC_HCI_RF_READER_A_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_SYS_MGMT_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_SWP_MGMT_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_POLLING_LOOP_MGMT_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_NFC_WI_MGMT_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_RF_READER_F_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_RF_READER_JEWEL_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_RF_READER_ISO15693_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_RF_READER_NFCIP1_INITIATOR_GATE, NFC_HCI_INVALID_PIPEपूर्ण,
	अणुPN544_RF_READER_NFCIP1_TARGET_GATE, NFC_HCI_INVALID_PIPEपूर्ण
पूर्ण;

/* Largest headroom needed क्रम outgoing custom commands */
#घोषणा PN544_CMDS_HEADROOM	2

काष्ठा pn544_hci_info अणु
	काष्ठा nfc_phy_ops *phy_ops;
	व्योम *phy_id;

	काष्ठा nfc_hci_dev *hdev;

	क्रमागत pn544_state state;

	काष्ठा mutex info_lock;

	पूर्णांक async_cb_type;
	data_exchange_cb_t async_cb;
	व्योम *async_cb_context;

	fw_करोwnload_t fw_करोwnload;
पूर्ण;

अटल पूर्णांक pn544_hci_खोलो(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा pn544_hci_info *info = nfc_hci_get_clientdata(hdev);
	पूर्णांक r = 0;

	mutex_lock(&info->info_lock);

	अगर (info->state != PN544_ST_COLD) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण

	r = info->phy_ops->enable(info->phy_id);

	अगर (r == 0)
		info->state = PN544_ST_READY;

out:
	mutex_unlock(&info->info_lock);
	वापस r;
पूर्ण

अटल व्योम pn544_hci_बंद(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा pn544_hci_info *info = nfc_hci_get_clientdata(hdev);

	mutex_lock(&info->info_lock);

	अगर (info->state == PN544_ST_COLD)
		जाओ out;

	info->phy_ops->disable(info->phy_id);

	info->state = PN544_ST_COLD;

out:
	mutex_unlock(&info->info_lock);
पूर्ण

अटल पूर्णांक pn544_hci_पढ़ोy(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	अटल काष्ठा hw_config अणु
		u8 adr[2];
		u8 value;
	पूर्ण hw_config[] = अणु
		अणुअणु0x9f, 0x9aपूर्ण, 0x00पूर्ण,

		अणुअणु0x98, 0x10पूर्ण, 0xbcपूर्ण,

		अणुअणु0x9e, 0x71पूर्ण, 0x00पूर्ण,

		अणुअणु0x98, 0x09पूर्ण, 0x00पूर्ण,

		अणुअणु0x9e, 0xb4पूर्ण, 0x00पूर्ण,

		अणुअणु0x9c, 0x01पूर्ण, 0x08पूर्ण,

		अणुअणु0x9e, 0xaaपूर्ण, 0x01पूर्ण,

		अणुअणु0x9b, 0xd1पूर्ण, 0x17पूर्ण,
		अणुअणु0x9b, 0xd2पूर्ण, 0x58पूर्ण,
		अणुअणु0x9b, 0xd3पूर्ण, 0x10पूर्ण,
		अणुअणु0x9b, 0xd4पूर्ण, 0x47पूर्ण,
		अणुअणु0x9b, 0xd5पूर्ण, 0x0cपूर्ण,
		अणुअणु0x9b, 0xd6पूर्ण, 0x37पूर्ण,
		अणुअणु0x9b, 0xddपूर्ण, 0x33पूर्ण,

		अणुअणु0x9b, 0x84पूर्ण, 0x00पूर्ण,
		अणुअणु0x99, 0x81पूर्ण, 0x79पूर्ण,
		अणुअणु0x99, 0x31पूर्ण, 0x79पूर्ण,

		अणुअणु0x98, 0x00पूर्ण, 0x3fपूर्ण,

		अणुअणु0x9f, 0x09पूर्ण, 0x02पूर्ण,

		अणुअणु0x9f, 0x0aपूर्ण, 0x05पूर्ण,

		अणुअणु0x9e, 0xd1पूर्ण, 0xa1पूर्ण,
		अणुअणु0x99, 0x23पूर्ण, 0x01पूर्ण,

		अणुअणु0x9e, 0x74पूर्ण, 0x00पूर्ण,
		अणुअणु0x9e, 0x90पूर्ण, 0x00पूर्ण,
		अणुअणु0x9f, 0x28पूर्ण, 0x10पूर्ण,

		अणुअणु0x9f, 0x35पूर्ण, 0x04पूर्ण,

		अणुअणु0x9f, 0x36पूर्ण, 0x11पूर्ण,

		अणुअणु0x9c, 0x31पूर्ण, 0x00पूर्ण,

		अणुअणु0x9c, 0x32पूर्ण, 0x00पूर्ण,

		अणुअणु0x9c, 0x19पूर्ण, 0x0aपूर्ण,

		अणुअणु0x9c, 0x1aपूर्ण, 0x0aपूर्ण,

		अणुअणु0x9c, 0x0cपूर्ण, 0x00पूर्ण,

		अणुअणु0x9c, 0x0dपूर्ण, 0x00पूर्ण,

		अणुअणु0x9c, 0x12पूर्ण, 0x00पूर्ण,

		अणुअणु0x9c, 0x13पूर्ण, 0x00पूर्ण,

		अणुअणु0x98, 0xa2पूर्ण, 0x09पूर्ण,

		अणुअणु0x98, 0x93पूर्ण, 0x00पूर्ण,

		अणुअणु0x98, 0x7dपूर्ण, 0x08पूर्ण,
		अणुअणु0x98, 0x7eपूर्ण, 0x00पूर्ण,
		अणुअणु0x9f, 0xc8पूर्ण, 0x00पूर्ण,
	पूर्ण;
	काष्ठा hw_config *p = hw_config;
	पूर्णांक count = ARRAY_SIZE(hw_config);
	काष्ठा sk_buff *res_skb;
	u8 param[4];
	पूर्णांक r;

	param[0] = 0;
	जबतक (count--) अणु
		param[1] = p->adr[0];
		param[2] = p->adr[1];
		param[3] = p->value;

		r = nfc_hci_send_cmd(hdev, PN544_SYS_MGMT_GATE, PN544_WRITE,
				     param, 4, &res_skb);
		अगर (r < 0)
			वापस r;

		अगर (res_skb->len != 1) अणु
			kमुक्त_skb(res_skb);
			वापस -EPROTO;
		पूर्ण

		अगर (res_skb->data[0] != p->value) अणु
			kमुक्त_skb(res_skb);
			वापस -EIO;
		पूर्ण

		kमुक्त_skb(res_skb);

		p++;
	पूर्ण

	param[0] = NFC_HCI_UICC_HOST_ID;
	r = nfc_hci_set_param(hdev, NFC_HCI_ADMIN_GATE,
			      NFC_HCI_ADMIN_WHITELIST, param, 1);
	अगर (r < 0)
		वापस r;

	param[0] = 0x3d;
	r = nfc_hci_set_param(hdev, PN544_SYS_MGMT_GATE,
			      PN544_SYS_MGMT_INFO_NOTIFICATION, param, 1);
	अगर (r < 0)
		वापस r;

	param[0] = 0x0;
	r = nfc_hci_set_param(hdev, NFC_HCI_RF_READER_A_GATE,
			      PN544_RF_READER_A_AUTO_ACTIVATION, param, 1);
	अगर (r < 0)
		वापस r;

	r = nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
			       NFC_HCI_EVT_END_OPERATION, शून्य, 0);
	अगर (r < 0)
		वापस r;

	param[0] = 0x1;
	r = nfc_hci_set_param(hdev, PN544_POLLING_LOOP_MGMT_GATE,
			      PN544_PL_NFCT_DEACTIVATED, param, 1);
	अगर (r < 0)
		वापस r;

	param[0] = 0x0;
	r = nfc_hci_set_param(hdev, PN544_POLLING_LOOP_MGMT_GATE,
			      PN544_PL_RDPHASES, param, 1);
	अगर (r < 0)
		वापस r;

	r = nfc_hci_get_param(hdev, NFC_HCI_ID_MGMT_GATE,
			      PN544_ID_MGMT_FULL_VERSION_SW, &skb);
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

अटल पूर्णांक pn544_hci_xmit(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा pn544_hci_info *info = nfc_hci_get_clientdata(hdev);

	वापस info->phy_ops->ग_लिखो(info->phy_id, skb);
पूर्ण

अटल पूर्णांक pn544_hci_start_poll(काष्ठा nfc_hci_dev *hdev,
				u32 im_protocols, u32 पंचांग_protocols)
अणु
	u8 phases = 0;
	पूर्णांक r;
	u8 duration[2];
	u8 activated;
	u8 i_mode = 0x3f; /* Enable all supported modes */
	u8 t_mode = 0x0f;
	u8 t_merge = 0x01; /* Enable merge by शेष */

	pr_info(DRIVER_DESC ": %s protocols 0x%x 0x%x\n",
		__func__, im_protocols, पंचांग_protocols);

	r = nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
			       NFC_HCI_EVT_END_OPERATION, शून्य, 0);
	अगर (r < 0)
		वापस r;

	duration[0] = 0x18;
	duration[1] = 0x6a;
	r = nfc_hci_set_param(hdev, PN544_POLLING_LOOP_MGMT_GATE,
			      PN544_PL_EMULATION, duration, 2);
	अगर (r < 0)
		वापस r;

	activated = 0;
	r = nfc_hci_set_param(hdev, PN544_POLLING_LOOP_MGMT_GATE,
			      PN544_PL_NFCT_DEACTIVATED, &activated, 1);
	अगर (r < 0)
		वापस r;

	अगर (im_protocols & (NFC_PROTO_ISO14443_MASK | NFC_PROTO_MIFARE_MASK |
			 NFC_PROTO_JEWEL_MASK))
		phases |= 1;		/* Type A */
	अगर (im_protocols & NFC_PROTO_FELICA_MASK) अणु
		phases |= (1 << 2);	/* Type F 212 */
		phases |= (1 << 3);	/* Type F 424 */
	पूर्ण

	phases |= (1 << 5);		/* NFC active */

	r = nfc_hci_set_param(hdev, PN544_POLLING_LOOP_MGMT_GATE,
			      PN544_PL_RDPHASES, &phases, 1);
	अगर (r < 0)
		वापस r;

	अगर ((im_protocols | पंचांग_protocols) & NFC_PROTO_NFC_DEP_MASK) अणु
		hdev->gb = nfc_get_local_general_bytes(hdev->ndev,
							&hdev->gb_len);
		pr_debug("generate local bytes %p\n", hdev->gb);
		अगर (hdev->gb == शून्य || hdev->gb_len == 0) अणु
			im_protocols &= ~NFC_PROTO_NFC_DEP_MASK;
			पंचांग_protocols &= ~NFC_PROTO_NFC_DEP_MASK;
		पूर्ण
	पूर्ण

	अगर (im_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		r = nfc_hci_send_event(hdev,
				PN544_RF_READER_NFCIP1_INITIATOR_GATE,
				NFC_HCI_EVT_END_OPERATION, शून्य, 0);
		अगर (r < 0)
			वापस r;

		r = nfc_hci_set_param(hdev,
				PN544_RF_READER_NFCIP1_INITIATOR_GATE,
				PN544_DEP_MODE, &i_mode, 1);
		अगर (r < 0)
			वापस r;

		r = nfc_hci_set_param(hdev,
				PN544_RF_READER_NFCIP1_INITIATOR_GATE,
				PN544_DEP_ATR_REQ, hdev->gb, hdev->gb_len);
		अगर (r < 0)
			वापस r;

		r = nfc_hci_send_event(hdev,
				PN544_RF_READER_NFCIP1_INITIATOR_GATE,
				NFC_HCI_EVT_READER_REQUESTED, शून्य, 0);
		अगर (r < 0)
			nfc_hci_send_event(hdev,
					PN544_RF_READER_NFCIP1_INITIATOR_GATE,
					NFC_HCI_EVT_END_OPERATION, शून्य, 0);
	पूर्ण

	अगर (पंचांग_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		r = nfc_hci_set_param(hdev, PN544_RF_READER_NFCIP1_TARGET_GATE,
				PN544_DEP_MODE, &t_mode, 1);
		अगर (r < 0)
			वापस r;

		r = nfc_hci_set_param(hdev, PN544_RF_READER_NFCIP1_TARGET_GATE,
				PN544_DEP_ATR_RES, hdev->gb, hdev->gb_len);
		अगर (r < 0)
			वापस r;

		r = nfc_hci_set_param(hdev, PN544_RF_READER_NFCIP1_TARGET_GATE,
				PN544_DEP_MERGE, &t_merge, 1);
		अगर (r < 0)
			वापस r;
	पूर्ण

	r = nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
			       NFC_HCI_EVT_READER_REQUESTED, शून्य, 0);
	अगर (r < 0)
		nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
				   NFC_HCI_EVT_END_OPERATION, शून्य, 0);

	वापस r;
पूर्ण

अटल पूर्णांक pn544_hci_dep_link_up(काष्ठा nfc_hci_dev *hdev,
				काष्ठा nfc_target *target, u8 comm_mode,
				u8 *gb, माप_प्रकार gb_len)
अणु
	काष्ठा sk_buff *rgb_skb = शून्य;
	पूर्णांक r;

	r = nfc_hci_get_param(hdev, target->hci_पढ़ोer_gate,
				PN544_DEP_ATR_RES, &rgb_skb);
	अगर (r < 0)
		वापस r;

	अगर (rgb_skb->len == 0 || rgb_skb->len > NFC_GB_MAXSIZE) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण
	prपूर्णांक_hex_dump(KERN_DEBUG, "remote gb: ", DUMP_PREFIX_OFFSET,
			16, 1, rgb_skb->data, rgb_skb->len, true);

	r = nfc_set_remote_general_bytes(hdev->ndev, rgb_skb->data,
						rgb_skb->len);

	अगर (r == 0)
		r = nfc_dep_link_is_up(hdev->ndev, target->idx, comm_mode,
					NFC_RF_INITIATOR);
निकास:
	kमुक्त_skb(rgb_skb);
	वापस r;
पूर्ण

अटल पूर्णांक pn544_hci_dep_link_करोwn(काष्ठा nfc_hci_dev *hdev)
अणु

	वापस nfc_hci_send_event(hdev, PN544_RF_READER_NFCIP1_INITIATOR_GATE,
					NFC_HCI_EVT_END_OPERATION, शून्य, 0);
पूर्ण

अटल पूर्णांक pn544_hci_target_from_gate(काष्ठा nfc_hci_dev *hdev, u8 gate,
				      काष्ठा nfc_target *target)
अणु
	चयन (gate) अणु
	हाल PN544_RF_READER_F_GATE:
		target->supported_protocols = NFC_PROTO_FELICA_MASK;
		अवरोध;
	हाल PN544_RF_READER_JEWEL_GATE:
		target->supported_protocols = NFC_PROTO_JEWEL_MASK;
		target->sens_res = 0x0c00;
		अवरोध;
	हाल PN544_RF_READER_NFCIP1_INITIATOR_GATE:
		target->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
		अवरोध;
	शेष:
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pn544_hci_complete_target_discovered(काष्ठा nfc_hci_dev *hdev,
						u8 gate,
						काष्ठा nfc_target *target)
अणु
	काष्ठा sk_buff *uid_skb;
	पूर्णांक r = 0;

	अगर (gate == PN544_RF_READER_NFCIP1_INITIATOR_GATE)
		वापस r;

	अगर (target->supported_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		r = nfc_hci_send_cmd(hdev,
			PN544_RF_READER_NFCIP1_INITIATOR_GATE,
			PN544_HCI_CMD_CONTINUE_ACTIVATION, शून्य, 0, शून्य);
		अगर (r < 0)
			वापस r;

		target->hci_पढ़ोer_gate = PN544_RF_READER_NFCIP1_INITIATOR_GATE;
	पूर्ण अन्यथा अगर (target->supported_protocols & NFC_PROTO_MIFARE_MASK) अणु
		अगर (target->nfcid1_len != 4 && target->nfcid1_len != 7 &&
		    target->nfcid1_len != 10)
			वापस -EPROTO;

		r = nfc_hci_send_cmd(hdev, NFC_HCI_RF_READER_A_GATE,
				     PN544_RF_READER_CMD_ACTIVATE_NEXT,
				     target->nfcid1, target->nfcid1_len, शून्य);
	पूर्ण अन्यथा अगर (target->supported_protocols & NFC_PROTO_FELICA_MASK) अणु
		r = nfc_hci_get_param(hdev, PN544_RF_READER_F_GATE,
				      PN544_FELICA_ID, &uid_skb);
		अगर (r < 0)
			वापस r;

		अगर (uid_skb->len != 8) अणु
			kमुक्त_skb(uid_skb);
			वापस -EPROTO;
		पूर्ण

		/* Type F NFC-DEP IDm has prefix 0x01FE */
		अगर ((uid_skb->data[0] == 0x01) && (uid_skb->data[1] == 0xfe)) अणु
			kमुक्त_skb(uid_skb);
			r = nfc_hci_send_cmd(hdev,
					PN544_RF_READER_NFCIP1_INITIATOR_GATE,
					PN544_HCI_CMD_CONTINUE_ACTIVATION,
					शून्य, 0, शून्य);
			अगर (r < 0)
				वापस r;

			target->supported_protocols = NFC_PROTO_NFC_DEP_MASK;
			target->hci_पढ़ोer_gate =
				PN544_RF_READER_NFCIP1_INITIATOR_GATE;
		पूर्ण अन्यथा अणु
			r = nfc_hci_send_cmd(hdev, PN544_RF_READER_F_GATE,
					     PN544_RF_READER_CMD_ACTIVATE_NEXT,
					     uid_skb->data, uid_skb->len, शून्य);
			kमुक्त_skb(uid_skb);
		पूर्ण
	पूर्ण अन्यथा अगर (target->supported_protocols & NFC_PROTO_ISO14443_MASK) अणु
		/*
		 * TODO: maybe other ISO 14443 require some kind of जारी
		 * activation, but क्रम now we've seen only this one below.
		 */
		अगर (target->sens_res == 0x4403)	/* Type 4 Mअगरare DESFire */
			r = nfc_hci_send_cmd(hdev, NFC_HCI_RF_READER_A_GATE,
			      PN544_RF_READER_A_CMD_CONTINUE_ACTIVATION,
			      शून्य, 0, शून्य);
	पूर्ण

	वापस r;
पूर्ण

#घोषणा PN544_CB_TYPE_READER_F 1

अटल व्योम pn544_hci_data_exchange_cb(व्योम *context, काष्ठा sk_buff *skb,
				       पूर्णांक err)
अणु
	काष्ठा pn544_hci_info *info = context;

	चयन (info->async_cb_type) अणु
	हाल PN544_CB_TYPE_READER_F:
		अगर (err == 0)
			skb_pull(skb, 1);
		info->async_cb(info->async_cb_context, skb, err);
		अवरोध;
	शेष:
		अगर (err == 0)
			kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा MIFARE_CMD_AUTH_KEY_A	0x60
#घोषणा MIFARE_CMD_AUTH_KEY_B	0x61
#घोषणा MIFARE_CMD_HEADER	2
#घोषणा MIFARE_UID_LEN		4
#घोषणा MIFARE_KEY_LEN		6
#घोषणा MIFARE_CMD_LEN		12
/*
 * Returns:
 * <= 0: driver handled the data exchange
 *    1: driver करोesn't especially handle, please करो standard processing
 */
अटल पूर्णांक pn544_hci_im_transceive(काष्ठा nfc_hci_dev *hdev,
				   काष्ठा nfc_target *target,
				   काष्ठा sk_buff *skb, data_exchange_cb_t cb,
				   व्योम *cb_context)
अणु
	काष्ठा pn544_hci_info *info = nfc_hci_get_clientdata(hdev);

	pr_info(DRIVER_DESC ": %s for gate=%d\n", __func__,
		target->hci_पढ़ोer_gate);

	चयन (target->hci_पढ़ोer_gate) अणु
	हाल NFC_HCI_RF_READER_A_GATE:
		अगर (target->supported_protocols & NFC_PROTO_MIFARE_MASK) अणु
			/*
			 * It seems that pn544 is inverting key and UID क्रम
			 * MIFARE authentication commands.
			 */
			अगर (skb->len == MIFARE_CMD_LEN &&
			    (skb->data[0] == MIFARE_CMD_AUTH_KEY_A ||
			     skb->data[0] == MIFARE_CMD_AUTH_KEY_B)) अणु
				u8 uid[MIFARE_UID_LEN];
				u8 *data = skb->data + MIFARE_CMD_HEADER;

				स_नकल(uid, data + MIFARE_KEY_LEN,
				       MIFARE_UID_LEN);
				स_हटाओ(data + MIFARE_UID_LEN, data,
					MIFARE_KEY_LEN);
				स_नकल(data, uid, MIFARE_UID_LEN);
			पूर्ण

			वापस nfc_hci_send_cmd_async(hdev,
						      target->hci_पढ़ोer_gate,
						      PN544_MIFARE_CMD,
						      skb->data, skb->len,
						      cb, cb_context);
		पूर्ण अन्यथा
			वापस 1;
	हाल PN544_RF_READER_F_GATE:
		*(u8 *)skb_push(skb, 1) = 0;
		*(u8 *)skb_push(skb, 1) = 0;

		info->async_cb_type = PN544_CB_TYPE_READER_F;
		info->async_cb = cb;
		info->async_cb_context = cb_context;

		वापस nfc_hci_send_cmd_async(hdev, target->hci_पढ़ोer_gate,
					      PN544_FELICA_RAW, skb->data,
					      skb->len,
					      pn544_hci_data_exchange_cb, info);
	हाल PN544_RF_READER_JEWEL_GATE:
		वापस nfc_hci_send_cmd_async(hdev, target->hci_पढ़ोer_gate,
					      PN544_JEWEL_RAW_CMD, skb->data,
					      skb->len, cb, cb_context);
	हाल PN544_RF_READER_NFCIP1_INITIATOR_GATE:
		*(u8 *)skb_push(skb, 1) = 0;

		वापस nfc_hci_send_event(hdev, target->hci_पढ़ोer_gate,
					PN544_HCI_EVT_SND_DATA, skb->data,
					skb->len);
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक pn544_hci_पंचांग_send(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;

	/* Set शेष false क्रम multiple inक्रमmation chaining */
	*(u8 *)skb_push(skb, 1) = 0;

	r = nfc_hci_send_event(hdev, PN544_RF_READER_NFCIP1_TARGET_GATE,
			       PN544_HCI_EVT_SND_DATA, skb->data, skb->len);

	kमुक्त_skb(skb);

	वापस r;
पूर्ण

अटल पूर्णांक pn544_hci_check_presence(काष्ठा nfc_hci_dev *hdev,
				   काष्ठा nfc_target *target)
अणु
	pr_debug("supported protocol %d\n", target->supported_protocols);
	अगर (target->supported_protocols & (NFC_PROTO_ISO14443_MASK |
					NFC_PROTO_ISO14443_B_MASK)) अणु
		वापस nfc_hci_send_cmd(hdev, target->hci_पढ़ोer_gate,
					PN544_RF_READER_CMD_PRESENCE_CHECK,
					शून्य, 0, शून्य);
	पूर्ण अन्यथा अगर (target->supported_protocols & NFC_PROTO_MIFARE_MASK) अणु
		अगर (target->nfcid1_len != 4 && target->nfcid1_len != 7 &&
		    target->nfcid1_len != 10)
			वापस -EOPNOTSUPP;

		वापस nfc_hci_send_cmd(hdev, NFC_HCI_RF_READER_A_GATE,
				     PN544_RF_READER_CMD_ACTIVATE_NEXT,
				     target->nfcid1, target->nfcid1_len, शून्य);
	पूर्ण अन्यथा अगर (target->supported_protocols & (NFC_PROTO_JEWEL_MASK |
						NFC_PROTO_FELICA_MASK)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (target->supported_protocols & NFC_PROTO_NFC_DEP_MASK) अणु
		वापस nfc_hci_send_cmd(hdev, target->hci_पढ़ोer_gate,
					PN544_HCI_CMD_ATTREQUEST,
					शून्य, 0, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Returns:
 * <= 0: driver handled the event, skb consumed
 *    1: driver करोes not handle the event, please करो standard processing
 */
अटल पूर्णांक pn544_hci_event_received(काष्ठा nfc_hci_dev *hdev, u8 pipe, u8 event,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *rgb_skb = शून्य;
	u8 gate = hdev->pipes[pipe].gate;
	पूर्णांक r;

	pr_debug("hci event %d\n", event);
	चयन (event) अणु
	हाल PN544_HCI_EVT_ACTIVATED:
		अगर (gate == PN544_RF_READER_NFCIP1_INITIATOR_GATE) अणु
			r = nfc_hci_target_discovered(hdev, gate);
		पूर्ण अन्यथा अगर (gate == PN544_RF_READER_NFCIP1_TARGET_GATE) अणु
			r = nfc_hci_get_param(hdev, gate, PN544_DEP_ATR_REQ,
					      &rgb_skb);
			अगर (r < 0)
				जाओ निकास;

			r = nfc_पंचांग_activated(hdev->ndev, NFC_PROTO_NFC_DEP_MASK,
					     NFC_COMM_PASSIVE, rgb_skb->data,
					     rgb_skb->len);

			kमुक्त_skb(rgb_skb);
		पूर्ण अन्यथा अणु
			r = -EINVAL;
		पूर्ण
		अवरोध;
	हाल PN544_HCI_EVT_DEACTIVATED:
		r = nfc_hci_send_event(hdev, gate, NFC_HCI_EVT_END_OPERATION,
				       शून्य, 0);
		अवरोध;
	हाल PN544_HCI_EVT_RCV_DATA:
		अगर (skb->len < 2) अणु
			r = -EPROTO;
			जाओ निकास;
		पूर्ण

		अगर (skb->data[0] != 0) अणु
			pr_debug("data0 %d\n", skb->data[0]);
			r = -EPROTO;
			जाओ निकास;
		पूर्ण

		skb_pull(skb, 2);
		वापस nfc_पंचांग_data_received(hdev->ndev, skb);
	शेष:
		वापस 1;
	पूर्ण

निकास:
	kमुक्त_skb(skb);

	वापस r;
पूर्ण

अटल पूर्णांक pn544_hci_fw_करोwnload(काष्ठा nfc_hci_dev *hdev,
				 स्थिर अक्षर *firmware_name)
अणु
	काष्ठा pn544_hci_info *info = nfc_hci_get_clientdata(hdev);

	अगर (info->fw_करोwnload == शून्य)
		वापस -ENOTSUPP;

	वापस info->fw_करोwnload(info->phy_id, firmware_name, hdev->sw_romlib);
पूर्ण

अटल पूर्णांक pn544_hci_discover_se(काष्ठा nfc_hci_dev *hdev)
अणु
	u32 se_idx = 0;
	u8 ese_mode = 0x01; /* Default mode */
	काष्ठा sk_buff *res_skb;
	पूर्णांक r;

	r = nfc_hci_send_cmd(hdev, PN544_SYS_MGMT_GATE, PN544_TEST_SWP,
			     शून्य, 0, &res_skb);

	अगर (r == 0) अणु
		अगर (res_skb->len == 2 && res_skb->data[0] == 0x00)
			nfc_add_se(hdev->ndev, se_idx++, NFC_SE_UICC);

		kमुक्त_skb(res_skb);
	पूर्ण

	r = nfc_hci_send_event(hdev, PN544_NFC_WI_MGMT_GATE,
				PN544_HCI_EVT_SWITCH_MODE,
				&ese_mode, 1);
	अगर (r == 0)
		nfc_add_se(hdev->ndev, se_idx++, NFC_SE_EMBEDDED);

	वापस !se_idx;
पूर्ण

#घोषणा PN544_SE_MODE_OFF	0x00
#घोषणा PN544_SE_MODE_ON	0x01
अटल पूर्णांक pn544_hci_enable_se(काष्ठा nfc_hci_dev *hdev, u32 se_idx)
अणु
	काष्ठा nfc_se *se;
	u8 enable = PN544_SE_MODE_ON;
	अटल काष्ठा uicc_gatelist अणु
		u8 head;
		u8 adr[2];
		u8 value;
	पूर्ण uicc_gatelist[] = अणु
		अणु0x00, अणु0x9e, 0xd9पूर्ण, 0x23पूर्ण,
		अणु0x00, अणु0x9e, 0xdaपूर्ण, 0x21पूर्ण,
		अणु0x00, अणु0x9e, 0xdbपूर्ण, 0x22पूर्ण,
		अणु0x00, अणु0x9e, 0xdcपूर्ण, 0x24पूर्ण,
	पूर्ण;
	काष्ठा uicc_gatelist *p = uicc_gatelist;
	पूर्णांक count = ARRAY_SIZE(uicc_gatelist);
	काष्ठा sk_buff *res_skb;
	पूर्णांक r;

	se = nfc_find_se(hdev->ndev, se_idx);

	चयन (se->type) अणु
	हाल NFC_SE_UICC:
		जबतक (count--) अणु
			r = nfc_hci_send_cmd(hdev, PN544_SYS_MGMT_GATE,
					PN544_WRITE, (u8 *)p, 4, &res_skb);
			अगर (r < 0)
				वापस r;

			अगर (res_skb->len != 1) अणु
				kमुक्त_skb(res_skb);
				वापस -EPROTO;
			पूर्ण

			अगर (res_skb->data[0] != p->value) अणु
				kमुक्त_skb(res_skb);
				वापस -EIO;
			पूर्ण

			kमुक्त_skb(res_skb);

			p++;
		पूर्ण

		वापस nfc_hci_set_param(hdev, PN544_SWP_MGMT_GATE,
			      PN544_SWP_DEFAULT_MODE, &enable, 1);
	हाल NFC_SE_EMBEDDED:
		वापस nfc_hci_set_param(hdev, PN544_NFC_WI_MGMT_GATE,
			      PN544_NFC_ESE_DEFAULT_MODE, &enable, 1);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक pn544_hci_disable_se(काष्ठा nfc_hci_dev *hdev, u32 se_idx)
अणु
	काष्ठा nfc_se *se;
	u8 disable = PN544_SE_MODE_OFF;

	se = nfc_find_se(hdev->ndev, se_idx);

	चयन (se->type) अणु
	हाल NFC_SE_UICC:
		वापस nfc_hci_set_param(hdev, PN544_SWP_MGMT_GATE,
			      PN544_SWP_DEFAULT_MODE, &disable, 1);
	हाल NFC_SE_EMBEDDED:
		वापस nfc_hci_set_param(hdev, PN544_NFC_WI_MGMT_GATE,
			      PN544_NFC_ESE_DEFAULT_MODE, &disable, 1);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा nfc_hci_ops pn544_hci_ops = अणु
	.खोलो = pn544_hci_खोलो,
	.बंद = pn544_hci_बंद,
	.hci_पढ़ोy = pn544_hci_पढ़ोy,
	.xmit = pn544_hci_xmit,
	.start_poll = pn544_hci_start_poll,
	.dep_link_up = pn544_hci_dep_link_up,
	.dep_link_करोwn = pn544_hci_dep_link_करोwn,
	.target_from_gate = pn544_hci_target_from_gate,
	.complete_target_discovered = pn544_hci_complete_target_discovered,
	.im_transceive = pn544_hci_im_transceive,
	.पंचांग_send = pn544_hci_पंचांग_send,
	.check_presence = pn544_hci_check_presence,
	.event_received = pn544_hci_event_received,
	.fw_करोwnload = pn544_hci_fw_करोwnload,
	.discover_se = pn544_hci_discover_se,
	.enable_se = pn544_hci_enable_se,
	.disable_se = pn544_hci_disable_se,
पूर्ण;

पूर्णांक pn544_hci_probe(व्योम *phy_id, काष्ठा nfc_phy_ops *phy_ops, अक्षर *llc_name,
		    पूर्णांक phy_headroom, पूर्णांक phy_tailroom, पूर्णांक phy_payload,
		    fw_करोwnload_t fw_करोwnload, काष्ठा nfc_hci_dev **hdev)
अणु
	काष्ठा pn544_hci_info *info;
	u32 protocols;
	काष्ठा nfc_hci_init_data init_data;
	पूर्णांक r;

	info = kzalloc(माप(काष्ठा pn544_hci_info), GFP_KERNEL);
	अगर (!info) अणु
		r = -ENOMEM;
		जाओ err_info_alloc;
	पूर्ण

	info->phy_ops = phy_ops;
	info->phy_id = phy_id;
	info->fw_करोwnload = fw_करोwnload;
	info->state = PN544_ST_COLD;
	mutex_init(&info->info_lock);

	init_data.gate_count = ARRAY_SIZE(pn544_gates);

	स_नकल(init_data.gates, pn544_gates, माप(pn544_gates));

	/*
	 * TODO: Session id must include the driver name + some bus addr
	 * persistent info to discriminate 2 identical chips
	 */
	म_नकल(init_data.session_id, "ID544HCI");

	protocols = NFC_PROTO_JEWEL_MASK |
		    NFC_PROTO_MIFARE_MASK |
		    NFC_PROTO_FELICA_MASK |
		    NFC_PROTO_ISO14443_MASK |
		    NFC_PROTO_ISO14443_B_MASK |
		    NFC_PROTO_NFC_DEP_MASK;

	info->hdev = nfc_hci_allocate_device(&pn544_hci_ops, &init_data, 0,
					     protocols, llc_name,
					     phy_headroom + PN544_CMDS_HEADROOM,
					     phy_tailroom, phy_payload);
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
EXPORT_SYMBOL(pn544_hci_probe);

व्योम pn544_hci_हटाओ(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा pn544_hci_info *info = nfc_hci_get_clientdata(hdev);

	nfc_hci_unरेजिस्टर_device(hdev);
	nfc_hci_मुक्त_device(hdev);
	kमुक्त(info);
पूर्ण
EXPORT_SYMBOL(pn544_hci_हटाओ);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
