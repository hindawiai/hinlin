<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NFC Digital Protocol stack
 * Copyright (c) 2013, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "digital: %s: " fmt, __func__

#समावेश "digital.h"

#घोषणा DIGITAL_CMD_SENS_REQ    0x26
#घोषणा DIGITAL_CMD_ALL_REQ     0x52
#घोषणा DIGITAL_CMD_SEL_REQ_CL1 0x93
#घोषणा DIGITAL_CMD_SEL_REQ_CL2 0x95
#घोषणा DIGITAL_CMD_SEL_REQ_CL3 0x97

#घोषणा DIGITAL_SDD_REQ_SEL_PAR 0x20

#घोषणा DIGITAL_SDD_RES_CT  0x88
#घोषणा DIGITAL_SDD_RES_LEN 5
#घोषणा DIGITAL_SEL_RES_LEN 1

#घोषणा DIGITAL_SEL_RES_NFCID1_COMPLETE(sel_res) (!((sel_res) & 0x04))
#घोषणा DIGITAL_SEL_RES_IS_T2T(sel_res) (!((sel_res) & 0x60))
#घोषणा DIGITAL_SEL_RES_IS_T4T(sel_res) ((sel_res) & 0x20)
#घोषणा DIGITAL_SEL_RES_IS_NFC_DEP(sel_res) ((sel_res) & 0x40)

#घोषणा DIGITAL_SENS_RES_IS_T1T(sens_res) (((sens_res) & 0x0C00) == 0x0C00)
#घोषणा DIGITAL_SENS_RES_IS_VALID(sens_res) \
	((!((sens_res) & 0x001F) && (((sens_res) & 0x0C00) == 0x0C00)) || \
	(((sens_res) & 0x001F) && ((sens_res) & 0x0C00) != 0x0C00))

#घोषणा DIGITAL_MIFARE_READ_RES_LEN 16
#घोषणा DIGITAL_MIFARE_ACK_RES	0x0A

#घोषणा DIGITAL_CMD_SENSB_REQ			0x05
#घोषणा DIGITAL_SENSB_ADVANCED			BIT(5)
#घोषणा DIGITAL_SENSB_EXTENDED			BIT(4)
#घोषणा DIGITAL_SENSB_ALLB_REQ			BIT(3)
#घोषणा DIGITAL_SENSB_N(n)			((n) & 0x7)

#घोषणा DIGITAL_CMD_SENSB_RES			0x50

#घोषणा DIGITAL_CMD_ATTRIB_REQ			0x1D
#घोषणा DIGITAL_ATTRIB_P1_TR0_DEFAULT		(0x0 << 6)
#घोषणा DIGITAL_ATTRIB_P1_TR1_DEFAULT		(0x0 << 4)
#घोषणा DIGITAL_ATTRIB_P1_SUPRESS_EOS		BIT(3)
#घोषणा DIGITAL_ATTRIB_P1_SUPRESS_SOS		BIT(2)
#घोषणा DIGITAL_ATTRIB_P2_LISTEN_POLL_1		(0x0 << 6)
#घोषणा DIGITAL_ATTRIB_P2_POLL_LISTEN_1		(0x0 << 4)
#घोषणा DIGITAL_ATTRIB_P2_MAX_FRAME_256		0x8
#घोषणा DIGITAL_ATTRIB_P4_DID(n)		((n) & 0xf)

#घोषणा DIGITAL_CMD_SENSF_REQ	0x00
#घोषणा DIGITAL_CMD_SENSF_RES	0x01

#घोषणा DIGITAL_SENSF_RES_MIN_LENGTH 17
#घोषणा DIGITAL_SENSF_RES_RD_AP_B1   0x00
#घोषणा DIGITAL_SENSF_RES_RD_AP_B2   0x8F

#घोषणा DIGITAL_SENSF_REQ_RC_NONE 0
#घोषणा DIGITAL_SENSF_REQ_RC_SC   1
#घोषणा DIGITAL_SENSF_REQ_RC_AP   2

#घोषणा DIGITAL_CMD_ISO15693_INVENTORY_REQ	0x01

#घोषणा DIGITAL_ISO15693_REQ_FLAG_DATA_RATE	BIT(1)
#घोषणा DIGITAL_ISO15693_REQ_FLAG_INVENTORY	BIT(2)
#घोषणा DIGITAL_ISO15693_REQ_FLAG_NB_SLOTS	BIT(5)
#घोषणा DIGITAL_ISO15693_RES_FLAG_ERROR		BIT(0)
#घोषणा DIGITAL_ISO15693_RES_IS_VALID(flags) \
	(!((flags) & DIGITAL_ISO15693_RES_FLAG_ERROR))

#घोषणा DIGITAL_ISO_DEP_I_PCB	 0x02
#घोषणा DIGITAL_ISO_DEP_PNI(pni) ((pni) & 0x01)

#घोषणा DIGITAL_ISO_DEP_PCB_TYPE(pcb) ((pcb) & 0xC0)

#घोषणा DIGITAL_ISO_DEP_I_BLOCK 0x00

#घोषणा DIGITAL_ISO_DEP_BLOCK_HAS_DID(pcb) ((pcb) & 0x08)

अटल स्थिर u8 digital_ats_fsc[] = अणु
	 16,  24,  32,  40,  48,  64,  96, 128,
पूर्ण;

#घोषणा DIGITAL_ATS_FSCI(t0) ((t0) & 0x0F)
#घोषणा DIGITAL_SENSB_FSCI(pi2) (((pi2) & 0xF0) >> 4)
#घोषणा DIGITAL_ATS_MAX_FSC  256

#घोषणा DIGITAL_RATS_BYTE1 0xE0
#घोषणा DIGITAL_RATS_PARAM 0x80

काष्ठा digital_sdd_res अणु
	u8 nfcid1[4];
	u8 bcc;
पूर्ण __packed;

काष्ठा digital_sel_req अणु
	u8 sel_cmd;
	u8 b2;
	u8 nfcid1[4];
	u8 bcc;
पूर्ण __packed;

काष्ठा digital_sensb_req अणु
	u8 cmd;
	u8 afi;
	u8 param;
पूर्ण __packed;

काष्ठा digital_sensb_res अणु
	u8 cmd;
	u8 nfcid0[4];
	u8 app_data[4];
	u8 proto_info[3];
पूर्ण __packed;

काष्ठा digital_attrib_req अणु
	u8 cmd;
	u8 nfcid0[4];
	u8 param1;
	u8 param2;
	u8 param3;
	u8 param4;
पूर्ण __packed;

काष्ठा digital_attrib_res अणु
	u8 mbli_did;
पूर्ण __packed;

काष्ठा digital_sensf_req अणु
	u8 cmd;
	u8 sc1;
	u8 sc2;
	u8 rc;
	u8 tsn;
पूर्ण __packed;

काष्ठा digital_sensf_res अणु
	u8 cmd;
	u8 nfcid2[8];
	u8 pad0[2];
	u8 pad1[3];
	u8 mrti_check;
	u8 mrti_update;
	u8 pad2;
	u8 rd[2];
पूर्ण __packed;

काष्ठा digital_iso15693_inv_req अणु
	u8 flags;
	u8 cmd;
	u8 mask_len;
	u64 mask;
पूर्ण __packed;

काष्ठा digital_iso15693_inv_res अणु
	u8 flags;
	u8 dsfid;
	u64 uid;
पूर्ण __packed;

अटल पूर्णांक digital_in_send_sdd_req(काष्ठा nfc_digital_dev *ddev,
				   काष्ठा nfc_target *target);

पूर्णांक digital_in_iso_dep_pull_sod(काष्ठा nfc_digital_dev *ddev,
				काष्ठा sk_buff *skb)
अणु
	u8 pcb;
	u8 block_type;

	अगर (skb->len < 1)
		वापस -EIO;

	pcb = *skb->data;
	block_type = DIGITAL_ISO_DEP_PCB_TYPE(pcb);

	/* No support fo R-block nor S-block */
	अगर (block_type != DIGITAL_ISO_DEP_I_BLOCK) अणु
		pr_err("ISO_DEP R-block and S-block not supported\n");
		वापस -EIO;
	पूर्ण

	अगर (DIGITAL_ISO_DEP_BLOCK_HAS_DID(pcb)) अणु
		pr_err("DID field in ISO_DEP PCB not supported\n");
		वापस -EIO;
	पूर्ण

	skb_pull(skb, 1);

	वापस 0;
पूर्ण

पूर्णांक digital_in_iso_dep_push_sod(काष्ठा nfc_digital_dev *ddev,
				काष्ठा sk_buff *skb)
अणु
	/*
	 * Chaining not supported so skb->len + 1 PCB byte + 2 CRC bytes must
	 * not be greater than remote FSC
	 */
	अगर (skb->len + 3 > ddev->target_fsc)
		वापस -EIO;

	skb_push(skb, 1);

	*skb->data = DIGITAL_ISO_DEP_I_PCB | ddev->curr_nfc_dep_pni;

	ddev->curr_nfc_dep_pni =
		DIGITAL_ISO_DEP_PNI(ddev->curr_nfc_dep_pni + 1);

	वापस 0;
पूर्ण

अटल व्योम digital_in_recv_ats(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				काष्ठा sk_buff *resp)
अणु
	काष्ठा nfc_target *target = arg;
	u8 fsdi;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (resp->len < 2) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	fsdi = DIGITAL_ATS_FSCI(resp->data[1]);
	अगर (fsdi >= 8)
		ddev->target_fsc = DIGITAL_ATS_MAX_FSC;
	अन्यथा
		ddev->target_fsc = digital_ats_fsc[fsdi];

	ddev->curr_nfc_dep_pni = 0;

	rc = digital_target_found(ddev, target, NFC_PROTO_ISO14443);

निकास:
	dev_kमुक्त_skb(resp);
	kमुक्त(target);

	अगर (rc)
		digital_poll_next_tech(ddev);
पूर्ण

अटल पूर्णांक digital_in_send_rats(काष्ठा nfc_digital_dev *ddev,
				काष्ठा nfc_target *target)
अणु
	पूर्णांक rc;
	काष्ठा sk_buff *skb;

	skb = digital_skb_alloc(ddev, 2);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, DIGITAL_RATS_BYTE1);
	skb_put_u8(skb, DIGITAL_RATS_PARAM);

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_ats,
				 target);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_in_recv_sel_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp)
अणु
	काष्ठा nfc_target *target = arg;
	पूर्णांक rc;
	u8 sel_res;
	u8 nfc_proto;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (!DIGITAL_DRV_CAPS_IN_CRC(ddev)) अणु
		rc = digital_skb_check_crc_a(resp);
		अगर (rc) अणु
			PROTOCOL_ERR("4.4.1.3");
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (resp->len != DIGITAL_SEL_RES_LEN) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	sel_res = resp->data[0];

	अगर (!DIGITAL_SEL_RES_NFCID1_COMPLETE(sel_res)) अणु
		rc = digital_in_send_sdd_req(ddev, target);
		अगर (rc)
			जाओ निकास;

		जाओ निकास_मुक्त_skb;
	पूर्ण

	target->sel_res = sel_res;

	अगर (DIGITAL_SEL_RES_IS_T2T(sel_res)) अणु
		nfc_proto = NFC_PROTO_MIFARE;
	पूर्ण अन्यथा अगर (DIGITAL_SEL_RES_IS_NFC_DEP(sel_res)) अणु
		nfc_proto = NFC_PROTO_NFC_DEP;
	पूर्ण अन्यथा अगर (DIGITAL_SEL_RES_IS_T4T(sel_res)) अणु
		rc = digital_in_send_rats(ddev, target);
		अगर (rc)
			जाओ निकास;
		/*
		 * Skip target_found and करोn't मुक्त it क्रम now. This will be
		 * करोne when receiving the ATS
		 */
		जाओ निकास_मुक्त_skb;
	पूर्ण अन्यथा अणु
		rc = -EOPNOTSUPP;
		जाओ निकास;
	पूर्ण

	rc = digital_target_found(ddev, target, nfc_proto);

निकास:
	kमुक्त(target);

निकास_मुक्त_skb:
	dev_kमुक्त_skb(resp);

	अगर (rc)
		digital_poll_next_tech(ddev);
पूर्ण

अटल पूर्णांक digital_in_send_sel_req(काष्ठा nfc_digital_dev *ddev,
				   काष्ठा nfc_target *target,
				   काष्ठा digital_sdd_res *sdd_res)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा digital_sel_req *sel_req;
	u8 sel_cmd;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, माप(काष्ठा digital_sel_req));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(काष्ठा digital_sel_req));
	sel_req = (काष्ठा digital_sel_req *)skb->data;

	अगर (target->nfcid1_len <= 4)
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL1;
	अन्यथा अगर (target->nfcid1_len < 10)
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL2;
	अन्यथा
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL3;

	sel_req->sel_cmd = sel_cmd;
	sel_req->b2 = 0x70;
	स_नकल(sel_req->nfcid1, sdd_res->nfcid1, 4);
	sel_req->bcc = sdd_res->bcc;

	अगर (DIGITAL_DRV_CAPS_IN_CRC(ddev)) अणु
		rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A);
		अगर (rc)
			जाओ निकास;
	पूर्ण अन्यथा अणु
		digital_skb_add_crc_a(skb);
	पूर्ण

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_sel_res,
				 target);
निकास:
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_in_recv_sdd_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp)
अणु
	काष्ठा nfc_target *target = arg;
	काष्ठा digital_sdd_res *sdd_res;
	पूर्णांक rc;
	u8 offset, size;
	u8 i, bcc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (resp->len < DIGITAL_SDD_RES_LEN) अणु
		PROTOCOL_ERR("4.7.2.8");
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	sdd_res = (काष्ठा digital_sdd_res *)resp->data;

	क्रम (i = 0, bcc = 0; i < 4; i++)
		bcc ^= sdd_res->nfcid1[i];

	अगर (bcc != sdd_res->bcc) अणु
		PROTOCOL_ERR("4.7.2.6");
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (sdd_res->nfcid1[0] == DIGITAL_SDD_RES_CT) अणु
		offset = 1;
		size = 3;
	पूर्ण अन्यथा अणु
		offset = 0;
		size = 4;
	पूर्ण

	स_नकल(target->nfcid1 + target->nfcid1_len, sdd_res->nfcid1 + offset,
	       size);
	target->nfcid1_len += size;

	rc = digital_in_send_sel_req(ddev, target, sdd_res);

निकास:
	dev_kमुक्त_skb(resp);

	अगर (rc) अणु
		kमुक्त(target);
		digital_poll_next_tech(ddev);
	पूर्ण
पूर्ण

अटल पूर्णांक digital_in_send_sdd_req(काष्ठा nfc_digital_dev *ddev,
				   काष्ठा nfc_target *target)
अणु
	पूर्णांक rc;
	काष्ठा sk_buff *skb;
	u8 sel_cmd;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCA_STANDARD);
	अगर (rc)
		वापस rc;

	skb = digital_skb_alloc(ddev, 2);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (target->nfcid1_len == 0)
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL1;
	अन्यथा अगर (target->nfcid1_len == 3)
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL2;
	अन्यथा
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL3;

	skb_put_u8(skb, sel_cmd);
	skb_put_u8(skb, DIGITAL_SDD_REQ_SEL_PAR);

	वापस digital_in_send_cmd(ddev, skb, 30, digital_in_recv_sdd_res,
				   target);
पूर्ण

अटल व्योम digital_in_recv_sens_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				     काष्ठा sk_buff *resp)
अणु
	काष्ठा nfc_target *target = शून्य;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (resp->len < माप(u16)) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	target = kzalloc(माप(काष्ठा nfc_target), GFP_KERNEL);
	अगर (!target) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण

	target->sens_res = __le16_to_cpu(*(__le16 *)resp->data);

	अगर (!DIGITAL_SENS_RES_IS_VALID(target->sens_res)) अणु
		PROTOCOL_ERR("4.6.3.3");
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	अगर (DIGITAL_SENS_RES_IS_T1T(target->sens_res))
		rc = digital_target_found(ddev, target, NFC_PROTO_JEWEL);
	अन्यथा
		rc = digital_in_send_sdd_req(ddev, target);

निकास:
	dev_kमुक्त_skb(resp);

	अगर (rc) अणु
		kमुक्त(target);
		digital_poll_next_tech(ddev);
	पूर्ण
पूर्ण

पूर्णांक digital_in_send_sens_req(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				     NFC_DIGITAL_RF_TECH_106A);
	अगर (rc)
		वापस rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCA_SHORT);
	अगर (rc)
		वापस rc;

	skb = digital_skb_alloc(ddev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, DIGITAL_CMD_SENS_REQ);

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_sens_res, शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

पूर्णांक digital_in_recv_mअगरare_res(काष्ठा sk_buff *resp)
अणु
	/* Successful READ command response is 16 data bytes + 2 CRC bytes दीर्घ.
	 * Since the driver can't dअगरferentiate a ACK/NACK response from a valid
	 * READ response, the CRC calculation must be handled at digital level
	 * even अगर the driver supports it क्रम this technology.
	 */
	अगर (resp->len == DIGITAL_MIFARE_READ_RES_LEN + DIGITAL_CRC_LEN) अणु
		अगर (digital_skb_check_crc_a(resp)) अणु
			PROTOCOL_ERR("9.4.1.2");
			वापस -EIO;
		पूर्ण

		वापस 0;
	पूर्ण

	/* ACK response (i.e. successful WRITE). */
	अगर (resp->len == 1 && resp->data[0] == DIGITAL_MIFARE_ACK_RES) अणु
		resp->data[0] = 0;
		वापस 0;
	पूर्ण

	/* NACK and any other responses are treated as error. */
	वापस -EIO;
पूर्ण

अटल व्योम digital_in_recv_attrib_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				       काष्ठा sk_buff *resp)
अणु
	काष्ठा nfc_target *target = arg;
	काष्ठा digital_attrib_res *attrib_res;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (resp->len < माप(*attrib_res)) अणु
		PROTOCOL_ERR("12.6.2");
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	attrib_res = (काष्ठा digital_attrib_res *)resp->data;

	अगर (attrib_res->mbli_did & 0x0f) अणु
		PROTOCOL_ERR("12.6.2.1");
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	rc = digital_target_found(ddev, target, NFC_PROTO_ISO14443_B);

निकास:
	dev_kमुक्त_skb(resp);
	kमुक्त(target);

	अगर (rc)
		digital_poll_next_tech(ddev);
पूर्ण

अटल पूर्णांक digital_in_send_attrib_req(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा nfc_target *target,
			       काष्ठा digital_sensb_res *sensb_res)
अणु
	काष्ठा digital_attrib_req *attrib_req;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, माप(*attrib_req));
	अगर (!skb)
		वापस -ENOMEM;

	attrib_req = skb_put(skb, माप(*attrib_req));

	attrib_req->cmd = DIGITAL_CMD_ATTRIB_REQ;
	स_नकल(attrib_req->nfcid0, sensb_res->nfcid0,
	       माप(attrib_req->nfcid0));
	attrib_req->param1 = DIGITAL_ATTRIB_P1_TR0_DEFAULT |
			     DIGITAL_ATTRIB_P1_TR1_DEFAULT;
	attrib_req->param2 = DIGITAL_ATTRIB_P2_LISTEN_POLL_1 |
			     DIGITAL_ATTRIB_P2_POLL_LISTEN_1 |
			     DIGITAL_ATTRIB_P2_MAX_FRAME_256;
	attrib_req->param3 = sensb_res->proto_info[1] & 0x07;
	attrib_req->param4 = DIGITAL_ATTRIB_P4_DID(0);

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_attrib_res,
				 target);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_in_recv_sensb_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				      काष्ठा sk_buff *resp)
अणु
	काष्ठा nfc_target *target = शून्य;
	काष्ठा digital_sensb_res *sensb_res;
	u8 fsci;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (resp->len != माप(*sensb_res)) अणु
		PROTOCOL_ERR("5.6.2.1");
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	sensb_res = (काष्ठा digital_sensb_res *)resp->data;

	अगर (sensb_res->cmd != DIGITAL_CMD_SENSB_RES) अणु
		PROTOCOL_ERR("5.6.2");
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (!(sensb_res->proto_info[1] & BIT(0))) अणु
		PROTOCOL_ERR("5.6.2.12");
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (sensb_res->proto_info[1] & BIT(3)) अणु
		PROTOCOL_ERR("5.6.2.16");
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	fsci = DIGITAL_SENSB_FSCI(sensb_res->proto_info[1]);
	अगर (fsci >= 8)
		ddev->target_fsc = DIGITAL_ATS_MAX_FSC;
	अन्यथा
		ddev->target_fsc = digital_ats_fsc[fsci];

	target = kzalloc(माप(काष्ठा nfc_target), GFP_KERNEL);
	अगर (!target) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण

	rc = digital_in_send_attrib_req(ddev, target, sensb_res);

निकास:
	dev_kमुक्त_skb(resp);

	अगर (rc) अणु
		kमुक्त(target);
		digital_poll_next_tech(ddev);
	पूर्ण
पूर्ण

पूर्णांक digital_in_send_sensb_req(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	काष्ठा digital_sensb_req *sensb_req;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				     NFC_DIGITAL_RF_TECH_106B);
	अगर (rc)
		वापस rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCB);
	अगर (rc)
		वापस rc;

	skb = digital_skb_alloc(ddev, माप(*sensb_req));
	अगर (!skb)
		वापस -ENOMEM;

	sensb_req = skb_put(skb, माप(*sensb_req));

	sensb_req->cmd = DIGITAL_CMD_SENSB_REQ;
	sensb_req->afi = 0x00; /* All families and sub-families */
	sensb_req->param = DIGITAL_SENSB_N(0);

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_sensb_res,
				 शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_in_recv_sensf_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				   काष्ठा sk_buff *resp)
अणु
	पूर्णांक rc;
	u8 proto;
	काष्ठा nfc_target target;
	काष्ठा digital_sensf_res *sensf_res;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (resp->len < DIGITAL_SENSF_RES_MIN_LENGTH) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (!DIGITAL_DRV_CAPS_IN_CRC(ddev)) अणु
		rc = digital_skb_check_crc_f(resp);
		अगर (rc) अणु
			PROTOCOL_ERR("6.4.1.8");
			जाओ निकास;
		पूर्ण
	पूर्ण

	skb_pull(resp, 1);

	स_रखो(&target, 0, माप(काष्ठा nfc_target));

	sensf_res = (काष्ठा digital_sensf_res *)resp->data;

	स_नकल(target.sensf_res, sensf_res, resp->len);
	target.sensf_res_len = resp->len;

	स_नकल(target.nfcid2, sensf_res->nfcid2, NFC_NFCID2_MAXSIZE);
	target.nfcid2_len = NFC_NFCID2_MAXSIZE;

	अगर (target.nfcid2[0] == DIGITAL_SENSF_NFCID2_NFC_DEP_B1 &&
	    target.nfcid2[1] == DIGITAL_SENSF_NFCID2_NFC_DEP_B2)
		proto = NFC_PROTO_NFC_DEP;
	अन्यथा
		proto = NFC_PROTO_FELICA;

	rc = digital_target_found(ddev, &target, proto);

निकास:
	dev_kमुक्त_skb(resp);

	अगर (rc)
		digital_poll_next_tech(ddev);
पूर्ण

पूर्णांक digital_in_send_sensf_req(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	काष्ठा digital_sensf_req *sensf_req;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;
	u8 size;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH, rf_tech);
	अगर (rc)
		वापस rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCF);
	अगर (rc)
		वापस rc;

	size = माप(काष्ठा digital_sensf_req);

	skb = digital_skb_alloc(ddev, size);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, size);

	sensf_req = (काष्ठा digital_sensf_req *)skb->data;
	sensf_req->cmd = DIGITAL_CMD_SENSF_REQ;
	sensf_req->sc1 = 0xFF;
	sensf_req->sc2 = 0xFF;
	sensf_req->rc = 0;
	sensf_req->tsn = 0;

	*(u8 *)skb_push(skb, 1) = size + 1;

	अगर (!DIGITAL_DRV_CAPS_IN_CRC(ddev))
		digital_skb_add_crc_f(skb);

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_sensf_res,
				 शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_in_recv_iso15693_inv_res(काष्ठा nfc_digital_dev *ddev,
		व्योम *arg, काष्ठा sk_buff *resp)
अणु
	काष्ठा digital_iso15693_inv_res *res;
	काष्ठा nfc_target *target = शून्य;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ out_मुक्त_skb;
	पूर्ण

	अगर (resp->len != माप(*res)) अणु
		rc = -EIO;
		जाओ out_मुक्त_skb;
	पूर्ण

	res = (काष्ठा digital_iso15693_inv_res *)resp->data;

	अगर (!DIGITAL_ISO15693_RES_IS_VALID(res->flags)) अणु
		PROTOCOL_ERR("ISO15693 - 10.3.1");
		rc = -EINVAL;
		जाओ out_मुक्त_skb;
	पूर्ण

	target = kzalloc(माप(*target), GFP_KERNEL);
	अगर (!target) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त_skb;
	पूर्ण

	target->is_iso15693 = 1;
	target->iso15693_dsfid = res->dsfid;
	स_नकल(target->iso15693_uid, &res->uid, माप(target->iso15693_uid));

	rc = digital_target_found(ddev, target, NFC_PROTO_ISO15693);

	kमुक्त(target);

out_मुक्त_skb:
	dev_kमुक्त_skb(resp);

	अगर (rc)
		digital_poll_next_tech(ddev);
पूर्ण

पूर्णांक digital_in_send_iso15693_inv_req(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	काष्ठा digital_iso15693_inv_req *req;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				     NFC_DIGITAL_RF_TECH_ISO15693);
	अगर (rc)
		वापस rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_ISO15693_INVENTORY);
	अगर (rc)
		वापस rc;

	skb = digital_skb_alloc(ddev, माप(*req));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(*req) - माप(req->mask)); /* No mask */
	req = (काष्ठा digital_iso15693_inv_req *)skb->data;

	/* Single sub-carrier, high data rate, no AFI, single slot
	 * Inventory command
	 */
	req->flags = DIGITAL_ISO15693_REQ_FLAG_DATA_RATE |
		     DIGITAL_ISO15693_REQ_FLAG_INVENTORY |
		     DIGITAL_ISO15693_REQ_FLAG_NB_SLOTS;
	req->cmd = DIGITAL_CMD_ISO15693_INVENTORY_REQ;
	req->mask_len = 0;

	rc = digital_in_send_cmd(ddev, skb, 30,
				 digital_in_recv_iso15693_inv_res, शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल पूर्णांक digital_tg_send_sel_res(काष्ठा nfc_digital_dev *ddev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, DIGITAL_SEL_RES_NFC_DEP);

	अगर (!DIGITAL_DRV_CAPS_TG_CRC(ddev))
		digital_skb_add_crc_a(skb);

	rc = digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCA_ANTICOL_COMPLETE);
	अगर (rc) अणु
		kमुक्त_skb(skb);
		वापस rc;
	पूर्ण

	rc = digital_tg_send_cmd(ddev, skb, 300, digital_tg_recv_atr_req,
				 शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_tg_recv_sel_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp)
अणु
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (!DIGITAL_DRV_CAPS_TG_CRC(ddev)) अणु
		rc = digital_skb_check_crc_a(resp);
		अगर (rc) अणु
			PROTOCOL_ERR("4.4.1.3");
			जाओ निकास;
		पूर्ण
	पूर्ण

	/* Silently ignore SEL_REQ content and send a SEL_RES क्रम NFC-DEP */

	rc = digital_tg_send_sel_res(ddev);

निकास:
	अगर (rc)
		digital_poll_next_tech(ddev);

	dev_kमुक्त_skb(resp);
पूर्ण

अटल पूर्णांक digital_tg_send_sdd_res(काष्ठा nfc_digital_dev *ddev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा digital_sdd_res *sdd_res;
	पूर्णांक rc, i;

	skb = digital_skb_alloc(ddev, माप(काष्ठा digital_sdd_res));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(काष्ठा digital_sdd_res));
	sdd_res = (काष्ठा digital_sdd_res *)skb->data;

	sdd_res->nfcid1[0] = 0x08;
	get_अक्रमom_bytes(sdd_res->nfcid1 + 1, 3);

	sdd_res->bcc = 0;
	क्रम (i = 0; i < 4; i++)
		sdd_res->bcc ^= sdd_res->nfcid1[i];

	rc = digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A);
	अगर (rc) अणु
		kमुक्त_skb(skb);
		वापस rc;
	पूर्ण

	rc = digital_tg_send_cmd(ddev, skb, 300, digital_tg_recv_sel_req,
				 शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_tg_recv_sdd_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp)
अणु
	u8 *sdd_req;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	sdd_req = resp->data;

	अगर (resp->len < 2 || sdd_req[0] != DIGITAL_CMD_SEL_REQ_CL1 ||
	    sdd_req[1] != DIGITAL_SDD_REQ_SEL_PAR) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	rc = digital_tg_send_sdd_res(ddev);

निकास:
	अगर (rc)
		digital_poll_next_tech(ddev);

	dev_kमुक्त_skb(resp);
पूर्ण

अटल पूर्णांक digital_tg_send_sens_res(काष्ठा nfc_digital_dev *ddev)
अणु
	काष्ठा sk_buff *skb;
	u8 *sens_res;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, 2);
	अगर (!skb)
		वापस -ENOMEM;

	sens_res = skb_put(skb, 2);

	sens_res[0] = (DIGITAL_SENS_RES_NFC_DEP >> 8) & 0xFF;
	sens_res[1] = DIGITAL_SENS_RES_NFC_DEP & 0xFF;

	rc = digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCA_STANDARD);
	अगर (rc) अणु
		kमुक्त_skb(skb);
		वापस rc;
	पूर्ण

	rc = digital_tg_send_cmd(ddev, skb, 300, digital_tg_recv_sdd_req,
				 शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

व्योम digital_tg_recv_sens_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
			      काष्ठा sk_buff *resp)
अणु
	u8 sens_req;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	sens_req = resp->data[0];

	अगर (!resp->len || (sens_req != DIGITAL_CMD_SENS_REQ &&
	    sens_req != DIGITAL_CMD_ALL_REQ)) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	rc = digital_tg_send_sens_res(ddev);

निकास:
	अगर (rc)
		digital_poll_next_tech(ddev);

	dev_kमुक्त_skb(resp);
पूर्ण

अटल व्योम digital_tg_recv_atr_or_sensf_req(काष्ठा nfc_digital_dev *ddev,
		व्योम *arg, काष्ठा sk_buff *resp)
अणु
	अगर (!IS_ERR(resp) && (resp->len >= 2) &&
			(resp->data[1] == DIGITAL_CMD_SENSF_REQ))
		digital_tg_recv_sensf_req(ddev, arg, resp);
	अन्यथा
		digital_tg_recv_atr_req(ddev, arg, resp);

	वापस;
पूर्ण

अटल पूर्णांक digital_tg_send_sensf_res(काष्ठा nfc_digital_dev *ddev,
			      काष्ठा digital_sensf_req *sensf_req)
अणु
	काष्ठा sk_buff *skb;
	u8 size;
	पूर्णांक rc;
	काष्ठा digital_sensf_res *sensf_res;

	size = माप(काष्ठा digital_sensf_res);

	अगर (sensf_req->rc == DIGITAL_SENSF_REQ_RC_NONE)
		size -= माप(sensf_res->rd);

	skb = digital_skb_alloc(ddev, size);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, size);

	sensf_res = (काष्ठा digital_sensf_res *)skb->data;

	स_रखो(sensf_res, 0, size);

	sensf_res->cmd = DIGITAL_CMD_SENSF_RES;
	sensf_res->nfcid2[0] = DIGITAL_SENSF_NFCID2_NFC_DEP_B1;
	sensf_res->nfcid2[1] = DIGITAL_SENSF_NFCID2_NFC_DEP_B2;
	get_अक्रमom_bytes(&sensf_res->nfcid2[2], 6);

	चयन (sensf_req->rc) अणु
	हाल DIGITAL_SENSF_REQ_RC_SC:
		sensf_res->rd[0] = sensf_req->sc1;
		sensf_res->rd[1] = sensf_req->sc2;
		अवरोध;
	हाल DIGITAL_SENSF_REQ_RC_AP:
		sensf_res->rd[0] = DIGITAL_SENSF_RES_RD_AP_B1;
		sensf_res->rd[1] = DIGITAL_SENSF_RES_RD_AP_B2;
		अवरोध;
	पूर्ण

	*(u8 *)skb_push(skb, माप(u8)) = size + 1;

	अगर (!DIGITAL_DRV_CAPS_TG_CRC(ddev))
		digital_skb_add_crc_f(skb);

	rc = digital_tg_send_cmd(ddev, skb, 300,
				 digital_tg_recv_atr_or_sensf_req, शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

व्योम digital_tg_recv_sensf_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
			       काष्ठा sk_buff *resp)
अणु
	काष्ठा digital_sensf_req *sensf_req;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (!DIGITAL_DRV_CAPS_TG_CRC(ddev)) अणु
		rc = digital_skb_check_crc_f(resp);
		अगर (rc) अणु
			PROTOCOL_ERR("6.4.1.8");
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (resp->len != माप(काष्ठा digital_sensf_req) + 1) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	skb_pull(resp, 1);
	sensf_req = (काष्ठा digital_sensf_req *)resp->data;

	अगर (sensf_req->cmd != DIGITAL_CMD_SENSF_REQ) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	rc = digital_tg_send_sensf_res(ddev, sensf_req);

निकास:
	अगर (rc)
		digital_poll_next_tech(ddev);

	dev_kमुक्त_skb(resp);
पूर्ण

अटल पूर्णांक digital_tg_config_nfca(काष्ठा nfc_digital_dev *ddev)
अणु
	पूर्णांक rc;

	rc = digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				     NFC_DIGITAL_RF_TECH_106A);
	अगर (rc)
		वापस rc;

	वापस digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				       NFC_DIGITAL_FRAMING_NFCA_NFC_DEP);
पूर्ण

पूर्णांक digital_tg_listen_nfca(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	पूर्णांक rc;

	rc = digital_tg_config_nfca(ddev);
	अगर (rc)
		वापस rc;

	वापस digital_tg_listen(ddev, 300, digital_tg_recv_sens_req, शून्य);
पूर्ण

अटल पूर्णांक digital_tg_config_nfcf(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	पूर्णांक rc;

	rc = digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH, rf_tech);
	अगर (rc)
		वापस rc;

	वापस digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				       NFC_DIGITAL_FRAMING_NFCF_NFC_DEP);
पूर्ण

पूर्णांक digital_tg_listen_nfcf(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	पूर्णांक rc;

	rc = digital_tg_config_nfcf(ddev, rf_tech);
	अगर (rc)
		वापस rc;

	वापस digital_tg_listen(ddev, 300, digital_tg_recv_sensf_req, शून्य);
पूर्ण

व्योम digital_tg_recv_md_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
			    काष्ठा sk_buff *resp)
अणु
	u8 rf_tech;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		resp = शून्य;
		जाओ निकास_मुक्त_skb;
	पूर्ण

	rc = ddev->ops->tg_get_rf_tech(ddev, &rf_tech);
	अगर (rc)
		जाओ निकास_मुक्त_skb;

	चयन (rf_tech) अणु
	हाल NFC_DIGITAL_RF_TECH_106A:
		rc = digital_tg_config_nfca(ddev);
		अगर (rc)
			जाओ निकास_मुक्त_skb;
		digital_tg_recv_sens_req(ddev, arg, resp);
		अवरोध;
	हाल NFC_DIGITAL_RF_TECH_212F:
	हाल NFC_DIGITAL_RF_TECH_424F:
		rc = digital_tg_config_nfcf(ddev, rf_tech);
		अगर (rc)
			जाओ निकास_मुक्त_skb;
		digital_tg_recv_sensf_req(ddev, arg, resp);
		अवरोध;
	शेष:
		जाओ निकास_मुक्त_skb;
	पूर्ण

	वापस;

निकास_मुक्त_skb:
	digital_poll_next_tech(ddev);
	dev_kमुक्त_skb(resp);
पूर्ण
