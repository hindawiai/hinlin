<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NFC Digital Protocol stack
 * Copyright (c) 2013, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "digital: %s: " fmt, __func__

#समावेश "digital.h"

#घोषणा DIGITAL_NFC_DEP_N_RETRY_NACK	2
#घोषणा DIGITAL_NFC_DEP_N_RETRY_ATN	2

#घोषणा DIGITAL_NFC_DEP_FRAME_सूची_OUT 0xD4
#घोषणा DIGITAL_NFC_DEP_FRAME_सूची_IN  0xD5

#घोषणा DIGITAL_NFC_DEP_NFCA_SOD_SB   0xF0

#घोषणा DIGITAL_CMD_ATR_REQ 0x00
#घोषणा DIGITAL_CMD_ATR_RES 0x01
#घोषणा DIGITAL_CMD_PSL_REQ 0x04
#घोषणा DIGITAL_CMD_PSL_RES 0x05
#घोषणा DIGITAL_CMD_DEP_REQ 0x06
#घोषणा DIGITAL_CMD_DEP_RES 0x07

#घोषणा DIGITAL_ATR_REQ_MIN_SIZE 16
#घोषणा DIGITAL_ATR_REQ_MAX_SIZE 64

#घोषणा DIGITAL_ATR_RES_TO_WT(s)	((s) & 0xF)

#घोषणा DIGITAL_DID_MAX	14

#घोषणा DIGITAL_PAYLOAD_SIZE_MAX	254
#घोषणा DIGITAL_PAYLOAD_BITS_TO_PP(s)	(((s) & 0x3) << 4)
#घोषणा DIGITAL_PAYLOAD_PP_TO_BITS(s)	(((s) >> 4) & 0x3)
#घोषणा DIGITAL_PAYLOAD_BITS_TO_FSL(s)	((s) & 0x3)
#घोषणा DIGITAL_PAYLOAD_FSL_TO_BITS(s)	((s) & 0x3)

#घोषणा DIGITAL_GB_BIT	0x02

#घोषणा DIGITAL_NFC_DEP_PFB_TYPE(pfb) ((pfb) & 0xE0)

#घोषणा DIGITAL_NFC_DEP_PFB_TIMEOUT_BIT 0x10
#घोषणा DIGITAL_NFC_DEP_PFB_MI_BIT	0x10
#घोषणा DIGITAL_NFC_DEP_PFB_NACK_BIT	0x10
#घोषणा DIGITAL_NFC_DEP_PFB_DID_BIT	0x04

#घोषणा DIGITAL_NFC_DEP_PFB_IS_TIMEOUT(pfb) \
				((pfb) & DIGITAL_NFC_DEP_PFB_TIMEOUT_BIT)
#घोषणा DIGITAL_NFC_DEP_MI_BIT_SET(pfb)  ((pfb) & DIGITAL_NFC_DEP_PFB_MI_BIT)
#घोषणा DIGITAL_NFC_DEP_NACK_BIT_SET(pfb) ((pfb) & DIGITAL_NFC_DEP_PFB_NACK_BIT)
#घोषणा DIGITAL_NFC_DEP_NAD_BIT_SET(pfb) ((pfb) & 0x08)
#घोषणा DIGITAL_NFC_DEP_DID_BIT_SET(pfb) ((pfb) & DIGITAL_NFC_DEP_PFB_DID_BIT)
#घोषणा DIGITAL_NFC_DEP_PFB_PNI(pfb)     ((pfb) & 0x03)

#घोषणा DIGITAL_NFC_DEP_RTOX_VALUE(data) ((data) & 0x3F)
#घोषणा DIGITAL_NFC_DEP_RTOX_MAX	 59

#घोषणा DIGITAL_NFC_DEP_PFB_I_PDU          0x00
#घोषणा DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU   0x40
#घोषणा DIGITAL_NFC_DEP_PFB_SUPERVISOR_PDU 0x80

काष्ठा digital_atr_req अणु
	u8 dir;
	u8 cmd;
	u8 nfcid3[10];
	u8 did;
	u8 bs;
	u8 br;
	u8 pp;
	u8 gb[];
पूर्ण __packed;

काष्ठा digital_atr_res अणु
	u8 dir;
	u8 cmd;
	u8 nfcid3[10];
	u8 did;
	u8 bs;
	u8 br;
	u8 to;
	u8 pp;
	u8 gb[];
पूर्ण __packed;

काष्ठा digital_psl_req अणु
	u8 dir;
	u8 cmd;
	u8 did;
	u8 brs;
	u8 fsl;
पूर्ण __packed;

काष्ठा digital_psl_res अणु
	u8 dir;
	u8 cmd;
	u8 did;
पूर्ण __packed;

काष्ठा digital_dep_req_res अणु
	u8 dir;
	u8 cmd;
	u8 pfb;
पूर्ण __packed;

अटल व्योम digital_in_recv_dep_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp);
अटल व्योम digital_tg_recv_dep_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp);

अटल स्थिर u8 digital_payload_bits_map[4] = अणु
	[0] = 64,
	[1] = 128,
	[2] = 192,
	[3] = 254
पूर्ण;

/* Response Waiting Time क्रम ATR_RES PDU in ms
 *
 * RWT(ATR_RES) = RWT(nfcdep,activation) + dRWT(nfcdep) + dT(nfcdep,initiator)
 *
 * with:
 *  RWT(nfcdep,activation) = 4096 * 2^12 / f(c) s
 *  dRWT(nfcdep) = 16 / f(c) s
 *  dT(nfcdep,initiator) = 100 ms
 *  f(c) = 13560000 Hz
 */
#घोषणा DIGITAL_ATR_RES_RWT 1337

/* Response Waiting Time क्रम other DEP PDUs in ms
 *
 * max_rwt = rwt + dRWT(nfcdep) + dT(nfcdep,initiator)
 *
 * with:
 *  rwt = (256 * 16 / f(c)) * 2^wt s
 *  dRWT(nfcdep) = 16 / f(c) s
 *  dT(nfcdep,initiator) = 100 ms
 *  f(c) = 13560000 Hz
 *  0 <= wt <= 14 (given by the target by the TO field of ATR_RES response)
 */
#घोषणा DIGITAL_NFC_DEP_IN_MAX_WT 14
#घोषणा DIGITAL_NFC_DEP_TG_MAX_WT 14
अटल स्थिर u16 digital_rwt_map[DIGITAL_NFC_DEP_IN_MAX_WT + 1] = अणु
	100,  101,  101,  102,  105,
	110,  119,  139,  177,  255,
	409,  719, 1337, 2575, 5049,
पूर्ण;

अटल u8 digital_payload_bits_to_size(u8 payload_bits)
अणु
	अगर (payload_bits >= ARRAY_SIZE(digital_payload_bits_map))
		वापस 0;

	वापस digital_payload_bits_map[payload_bits];
पूर्ण

अटल u8 digital_payload_माप_प्रकारo_bits(u8 payload_size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(digital_payload_bits_map); i++)
		अगर (digital_payload_bits_map[i] == payload_size)
			वापस i;

	वापस 0xff;
पूर्ण

अटल व्योम digital_skb_push_dep_sod(काष्ठा nfc_digital_dev *ddev,
				     काष्ठा sk_buff *skb)
अणु
	skb_push(skb, माप(u8));

	skb->data[0] = skb->len;

	अगर (ddev->curr_rf_tech == NFC_DIGITAL_RF_TECH_106A)
		*(u8 *)skb_push(skb, माप(u8)) = DIGITAL_NFC_DEP_NFCA_SOD_SB;
पूर्ण

अटल पूर्णांक digital_skb_pull_dep_sod(काष्ठा nfc_digital_dev *ddev,
				    काष्ठा sk_buff *skb)
अणु
	u8 size;

	अगर (skb->len < 2)
		वापस -EIO;

	अगर (ddev->curr_rf_tech == NFC_DIGITAL_RF_TECH_106A)
		skb_pull(skb, माप(u8));

	size = skb->data[0];
	अगर (size != skb->len)
		वापस -EIO;

	skb_pull(skb, माप(u8));

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *
digital_send_dep_data_prep(काष्ठा nfc_digital_dev *ddev, काष्ठा sk_buff *skb,
			   काष्ठा digital_dep_req_res *dep_req_res,
			   काष्ठा digital_data_exch *data_exch)
अणु
	काष्ठा sk_buff *new_skb;

	अगर (skb->len > ddev->remote_payload_max) अणु
		dep_req_res->pfb |= DIGITAL_NFC_DEP_PFB_MI_BIT;

		new_skb = digital_skb_alloc(ddev, ddev->remote_payload_max);
		अगर (!new_skb) अणु
			kमुक्त_skb(ddev->chaining_skb);
			ddev->chaining_skb = शून्य;

			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		skb_put_data(new_skb, skb->data, ddev->remote_payload_max);
		skb_pull(skb, ddev->remote_payload_max);

		ddev->chaining_skb = skb;
		ddev->data_exch = data_exch;
	पूर्ण अन्यथा अणु
		ddev->chaining_skb = शून्य;
		new_skb = skb;
	पूर्ण

	वापस new_skb;
पूर्ण

अटल काष्ठा sk_buff *
digital_recv_dep_data_gather(काष्ठा nfc_digital_dev *ddev, u8 pfb,
			     काष्ठा sk_buff *resp,
			     पूर्णांक (*send_ack)(काष्ठा nfc_digital_dev *ddev,
					     काष्ठा digital_data_exch
							     *data_exch),
			     काष्ठा digital_data_exch *data_exch)
अणु
	काष्ठा sk_buff *new_skb;
	पूर्णांक rc;

	अगर (DIGITAL_NFC_DEP_MI_BIT_SET(pfb) && (!ddev->chaining_skb)) अणु
		ddev->chaining_skb =
			nfc_alloc_recv_skb(8 * ddev->local_payload_max,
					   GFP_KERNEL);
		अगर (!ddev->chaining_skb) अणु
			rc = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण

	अगर (ddev->chaining_skb) अणु
		अगर (resp->len > skb_tailroom(ddev->chaining_skb)) अणु
			new_skb = skb_copy_expand(ddev->chaining_skb,
						  skb_headroom(
							  ddev->chaining_skb),
						  8 * ddev->local_payload_max,
						  GFP_KERNEL);
			अगर (!new_skb) अणु
				rc = -ENOMEM;
				जाओ error;
			पूर्ण

			kमुक्त_skb(ddev->chaining_skb);
			ddev->chaining_skb = new_skb;
		पूर्ण

		skb_put_data(ddev->chaining_skb, resp->data, resp->len);

		kमुक्त_skb(resp);
		resp = शून्य;

		अगर (DIGITAL_NFC_DEP_MI_BIT_SET(pfb)) अणु
			rc = send_ack(ddev, data_exch);
			अगर (rc)
				जाओ error;

			वापस शून्य;
		पूर्ण

		resp = ddev->chaining_skb;
		ddev->chaining_skb = शून्य;
	पूर्ण

	वापस resp;

error:
	kमुक्त_skb(resp);

	kमुक्त_skb(ddev->chaining_skb);
	ddev->chaining_skb = शून्य;

	वापस ERR_PTR(rc);
पूर्ण

अटल व्योम digital_in_recv_psl_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp)
अणु
	काष्ठा nfc_target *target = arg;
	काष्ठा digital_psl_res *psl_res;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	rc = ddev->skb_check_crc(resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.6");
		जाओ निकास;
	पूर्ण

	rc = digital_skb_pull_dep_sod(ddev, resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.2");
		जाओ निकास;
	पूर्ण

	psl_res = (काष्ठा digital_psl_res *)resp->data;

	अगर ((resp->len != माप(*psl_res)) ||
	    (psl_res->dir != DIGITAL_NFC_DEP_FRAME_सूची_IN) ||
	    (psl_res->cmd != DIGITAL_CMD_PSL_RES)) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				     NFC_DIGITAL_RF_TECH_424F);
	अगर (rc)
		जाओ निकास;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCF_NFC_DEP);
	अगर (rc)
		जाओ निकास;

	अगर (!DIGITAL_DRV_CAPS_IN_CRC(ddev) &&
	    (ddev->curr_rf_tech == NFC_DIGITAL_RF_TECH_106A)) अणु
		ddev->skb_add_crc = digital_skb_add_crc_f;
		ddev->skb_check_crc = digital_skb_check_crc_f;
	पूर्ण

	ddev->curr_rf_tech = NFC_DIGITAL_RF_TECH_424F;

	nfc_dep_link_is_up(ddev->nfc_dev, target->idx, NFC_COMM_ACTIVE,
			   NFC_RF_INITIATOR);

	ddev->curr_nfc_dep_pni = 0;

निकास:
	dev_kमुक्त_skb(resp);

	अगर (rc)
		ddev->curr_protocol = 0;
पूर्ण

अटल पूर्णांक digital_in_send_psl_req(काष्ठा nfc_digital_dev *ddev,
				   काष्ठा nfc_target *target)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा digital_psl_req *psl_req;
	पूर्णांक rc;
	u8 payload_size, payload_bits;

	skb = digital_skb_alloc(ddev, माप(*psl_req));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(*psl_req));

	psl_req = (काष्ठा digital_psl_req *)skb->data;

	psl_req->dir = DIGITAL_NFC_DEP_FRAME_सूची_OUT;
	psl_req->cmd = DIGITAL_CMD_PSL_REQ;
	psl_req->did = 0;
	psl_req->brs = (0x2 << 3) | 0x2; /* 424F both directions */

	payload_size = min(ddev->local_payload_max, ddev->remote_payload_max);
	payload_bits = digital_payload_माप_प्रकारo_bits(payload_size);
	psl_req->fsl = DIGITAL_PAYLOAD_BITS_TO_FSL(payload_bits);

	ddev->local_payload_max = payload_size;
	ddev->remote_payload_max = payload_size;

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	rc = digital_in_send_cmd(ddev, skb, ddev->dep_rwt,
				 digital_in_recv_psl_res, target);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_in_recv_atr_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				 काष्ठा sk_buff *resp)
अणु
	काष्ठा nfc_target *target = arg;
	काष्ठा digital_atr_res *atr_res;
	u8 gb_len, payload_bits;
	u8 wt;
	पूर्णांक rc;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	rc = ddev->skb_check_crc(resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.6");
		जाओ निकास;
	पूर्ण

	rc = digital_skb_pull_dep_sod(ddev, resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.2");
		जाओ निकास;
	पूर्ण

	अगर (resp->len < माप(काष्ठा digital_atr_res)) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	gb_len = resp->len - माप(काष्ठा digital_atr_res);

	atr_res = (काष्ठा digital_atr_res *)resp->data;

	wt = DIGITAL_ATR_RES_TO_WT(atr_res->to);
	अगर (wt > DIGITAL_NFC_DEP_IN_MAX_WT)
		wt = DIGITAL_NFC_DEP_IN_MAX_WT;
	ddev->dep_rwt = digital_rwt_map[wt];

	payload_bits = DIGITAL_PAYLOAD_PP_TO_BITS(atr_res->pp);
	ddev->remote_payload_max = digital_payload_bits_to_size(payload_bits);

	अगर (!ddev->remote_payload_max) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	rc = nfc_set_remote_general_bytes(ddev->nfc_dev, atr_res->gb, gb_len);
	अगर (rc)
		जाओ निकास;

	अगर ((ddev->protocols & NFC_PROTO_FELICA_MASK) &&
	    (ddev->curr_rf_tech != NFC_DIGITAL_RF_TECH_424F)) अणु
		rc = digital_in_send_psl_req(ddev, target);
		अगर (!rc)
			जाओ निकास;
	पूर्ण

	rc = nfc_dep_link_is_up(ddev->nfc_dev, target->idx, NFC_COMM_ACTIVE,
				NFC_RF_INITIATOR);

	ddev->curr_nfc_dep_pni = 0;

निकास:
	dev_kमुक्त_skb(resp);

	अगर (rc)
		ddev->curr_protocol = 0;
पूर्ण

पूर्णांक digital_in_send_atr_req(काष्ठा nfc_digital_dev *ddev,
			    काष्ठा nfc_target *target, __u8 comm_mode, __u8 *gb,
			    माप_प्रकार gb_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा digital_atr_req *atr_req;
	uपूर्णांक size;
	पूर्णांक rc;
	u8 payload_bits;

	size = DIGITAL_ATR_REQ_MIN_SIZE + gb_len;

	अगर (size > DIGITAL_ATR_REQ_MAX_SIZE) अणु
		PROTOCOL_ERR("14.6.1.1");
		वापस -EINVAL;
	पूर्ण

	skb = digital_skb_alloc(ddev, size);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(काष्ठा digital_atr_req));

	atr_req = (काष्ठा digital_atr_req *)skb->data;
	स_रखो(atr_req, 0, माप(काष्ठा digital_atr_req));

	atr_req->dir = DIGITAL_NFC_DEP_FRAME_सूची_OUT;
	atr_req->cmd = DIGITAL_CMD_ATR_REQ;
	अगर (target->nfcid2_len)
		स_नकल(atr_req->nfcid3, target->nfcid2, NFC_NFCID2_MAXSIZE);
	अन्यथा
		get_अक्रमom_bytes(atr_req->nfcid3, NFC_NFCID3_MAXSIZE);

	atr_req->did = 0;
	atr_req->bs = 0;
	atr_req->br = 0;

	ddev->local_payload_max = DIGITAL_PAYLOAD_SIZE_MAX;
	payload_bits = digital_payload_माप_प्रकारo_bits(ddev->local_payload_max);
	atr_req->pp = DIGITAL_PAYLOAD_BITS_TO_PP(payload_bits);

	अगर (gb_len) अणु
		atr_req->pp |= DIGITAL_GB_BIT;
		skb_put_data(skb, gb, gb_len);
	पूर्ण

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	rc = digital_in_send_cmd(ddev, skb, DIGITAL_ATR_RES_RWT,
				 digital_in_recv_atr_res, target);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल पूर्णांक digital_in_send_ack(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा digital_data_exch *data_exch)
अणु
	काष्ठा digital_dep_req_res *dep_req;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_push(skb, माप(काष्ठा digital_dep_req_res));

	dep_req = (काष्ठा digital_dep_req_res *)skb->data;

	dep_req->dir = DIGITAL_NFC_DEP_FRAME_सूची_OUT;
	dep_req->cmd = DIGITAL_CMD_DEP_REQ;
	dep_req->pfb = DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU |
		       ddev->curr_nfc_dep_pni;

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	ddev->saved_skb = pskb_copy(skb, GFP_KERNEL);

	rc = digital_in_send_cmd(ddev, skb, ddev->dep_rwt,
				 digital_in_recv_dep_res, data_exch);
	अगर (rc) अणु
		kमुक्त_skb(skb);
		kमुक्त_skb(ddev->saved_skb);
		ddev->saved_skb = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक digital_in_send_nack(काष्ठा nfc_digital_dev *ddev,
				काष्ठा digital_data_exch *data_exch)
अणु
	काष्ठा digital_dep_req_res *dep_req;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_push(skb, माप(काष्ठा digital_dep_req_res));

	dep_req = (काष्ठा digital_dep_req_res *)skb->data;

	dep_req->dir = DIGITAL_NFC_DEP_FRAME_सूची_OUT;
	dep_req->cmd = DIGITAL_CMD_DEP_REQ;
	dep_req->pfb = DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU |
		       DIGITAL_NFC_DEP_PFB_NACK_BIT | ddev->curr_nfc_dep_pni;

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	rc = digital_in_send_cmd(ddev, skb, ddev->dep_rwt,
				 digital_in_recv_dep_res, data_exch);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल पूर्णांक digital_in_send_atn(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा digital_data_exch *data_exch)
अणु
	काष्ठा digital_dep_req_res *dep_req;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_push(skb, माप(काष्ठा digital_dep_req_res));

	dep_req = (काष्ठा digital_dep_req_res *)skb->data;

	dep_req->dir = DIGITAL_NFC_DEP_FRAME_सूची_OUT;
	dep_req->cmd = DIGITAL_CMD_DEP_REQ;
	dep_req->pfb = DIGITAL_NFC_DEP_PFB_SUPERVISOR_PDU;

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	rc = digital_in_send_cmd(ddev, skb, ddev->dep_rwt,
				 digital_in_recv_dep_res, data_exch);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल पूर्णांक digital_in_send_rtox(काष्ठा nfc_digital_dev *ddev,
				काष्ठा digital_data_exch *data_exch, u8 rtox)
अणु
	काष्ठा digital_dep_req_res *dep_req;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;
	u16 rwt_पूर्णांक;

	rwt_पूर्णांक = ddev->dep_rwt * rtox;
	अगर (rwt_पूर्णांक > digital_rwt_map[DIGITAL_NFC_DEP_IN_MAX_WT])
		rwt_पूर्णांक = digital_rwt_map[DIGITAL_NFC_DEP_IN_MAX_WT];

	skb = digital_skb_alloc(ddev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_u8(skb, rtox);

	skb_push(skb, माप(काष्ठा digital_dep_req_res));

	dep_req = (काष्ठा digital_dep_req_res *)skb->data;

	dep_req->dir = DIGITAL_NFC_DEP_FRAME_सूची_OUT;
	dep_req->cmd = DIGITAL_CMD_DEP_REQ;
	dep_req->pfb = DIGITAL_NFC_DEP_PFB_SUPERVISOR_PDU |
		       DIGITAL_NFC_DEP_PFB_TIMEOUT_BIT;

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	rc = digital_in_send_cmd(ddev, skb, rwt_पूर्णांक,
				 digital_in_recv_dep_res, data_exch);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल पूर्णांक digital_in_send_saved_skb(काष्ठा nfc_digital_dev *ddev,
				     काष्ठा digital_data_exch *data_exch)
अणु
	पूर्णांक rc;

	अगर (!ddev->saved_skb)
		वापस -EINVAL;

	skb_get(ddev->saved_skb);

	rc = digital_in_send_cmd(ddev, ddev->saved_skb, ddev->dep_rwt,
				 digital_in_recv_dep_res, data_exch);
	अगर (rc)
		kमुक्त_skb(ddev->saved_skb);

	वापस rc;
पूर्ण

अटल व्योम digital_in_recv_dep_res(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp)
अणु
	काष्ठा digital_data_exch *data_exch = arg;
	काष्ठा digital_dep_req_res *dep_res;
	u8 pfb;
	uपूर्णांक size;
	पूर्णांक rc;
	u8 rtox;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;

		अगर ((rc == -EIO || (rc == -ETIMEDOUT && ddev->nack_count)) &&
		    (ddev->nack_count++ < DIGITAL_NFC_DEP_N_RETRY_NACK)) अणु
			ddev->atn_count = 0;

			rc = digital_in_send_nack(ddev, data_exch);
			अगर (rc)
				जाओ error;

			वापस;
		पूर्ण अन्यथा अगर ((rc == -ETIMEDOUT) &&
			   (ddev->atn_count++ < DIGITAL_NFC_DEP_N_RETRY_ATN)) अणु
			ddev->nack_count = 0;

			rc = digital_in_send_atn(ddev, data_exch);
			अगर (rc)
				जाओ error;

			वापस;
		पूर्ण

		जाओ निकास;
	पूर्ण

	rc = digital_skb_pull_dep_sod(ddev, resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.2");
		जाओ निकास;
	पूर्ण

	rc = ddev->skb_check_crc(resp);
	अगर (rc) अणु
		अगर ((resp->len >= 4) &&
		    (ddev->nack_count++ < DIGITAL_NFC_DEP_N_RETRY_NACK)) अणु
			ddev->atn_count = 0;

			rc = digital_in_send_nack(ddev, data_exch);
			अगर (rc)
				जाओ error;

			kमुक्त_skb(resp);

			वापस;
		पूर्ण

		PROTOCOL_ERR("14.4.1.6");
		जाओ error;
	पूर्ण

	ddev->atn_count = 0;
	ddev->nack_count = 0;

	अगर (resp->len > ddev->local_payload_max) अणु
		rc = -EMSGSIZE;
		जाओ निकास;
	पूर्ण

	size = माप(काष्ठा digital_dep_req_res);
	dep_res = (काष्ठा digital_dep_req_res *)resp->data;

	अगर (resp->len < size || dep_res->dir != DIGITAL_NFC_DEP_FRAME_सूची_IN ||
	    dep_res->cmd != DIGITAL_CMD_DEP_RES) अणु
		rc = -EIO;
		जाओ error;
	पूर्ण

	pfb = dep_res->pfb;

	अगर (DIGITAL_NFC_DEP_DID_BIT_SET(pfb)) अणु
		PROTOCOL_ERR("14.8.2.1");
		rc = -EIO;
		जाओ error;
	पूर्ण

	अगर (DIGITAL_NFC_DEP_NAD_BIT_SET(pfb)) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (size > resp->len) अणु
		rc = -EIO;
		जाओ error;
	पूर्ण

	skb_pull(resp, size);

	चयन (DIGITAL_NFC_DEP_PFB_TYPE(pfb)) अणु
	हाल DIGITAL_NFC_DEP_PFB_I_PDU:
		अगर (DIGITAL_NFC_DEP_PFB_PNI(pfb) != ddev->curr_nfc_dep_pni) अणु
			PROTOCOL_ERR("14.12.3.3");
			rc = -EIO;
			जाओ error;
		पूर्ण

		ddev->curr_nfc_dep_pni =
			DIGITAL_NFC_DEP_PFB_PNI(ddev->curr_nfc_dep_pni + 1);

		kमुक्त_skb(ddev->saved_skb);
		ddev->saved_skb = शून्य;

		resp = digital_recv_dep_data_gather(ddev, pfb, resp,
						    digital_in_send_ack,
						    data_exch);
		अगर (IS_ERR(resp)) अणु
			rc = PTR_ERR(resp);
			resp = शून्य;
			जाओ error;
		पूर्ण

		/* If resp is शून्य then we're still chaining so वापस and
		 * रुको क्रम the next part of the PDU.  Else, the PDU is
		 * complete so pass it up.
		 */
		अगर (!resp)
			वापस;

		rc = 0;
		अवरोध;

	हाल DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU:
		अगर (DIGITAL_NFC_DEP_NACK_BIT_SET(pfb)) अणु
			PROTOCOL_ERR("14.12.4.5");
			rc = -EIO;
			जाओ निकास;
		पूर्ण

		अगर (DIGITAL_NFC_DEP_PFB_PNI(pfb) != ddev->curr_nfc_dep_pni) अणु
			PROTOCOL_ERR("14.12.3.3");
			rc = -EIO;
			जाओ निकास;
		पूर्ण

		ddev->curr_nfc_dep_pni =
			DIGITAL_NFC_DEP_PFB_PNI(ddev->curr_nfc_dep_pni + 1);

		अगर (!ddev->chaining_skb) अणु
			PROTOCOL_ERR("14.12.4.3");
			rc = -EIO;
			जाओ निकास;
		पूर्ण

		/* The initiator has received a valid ACK. Free the last sent
		 * PDU and keep on sending chained skb.
		 */
		kमुक्त_skb(ddev->saved_skb);
		ddev->saved_skb = शून्य;

		rc = digital_in_send_dep_req(ddev, शून्य,
					     ddev->chaining_skb,
					     ddev->data_exch);
		अगर (rc)
			जाओ error;

		जाओ मुक्त_resp;

	हाल DIGITAL_NFC_DEP_PFB_SUPERVISOR_PDU:
		अगर (!DIGITAL_NFC_DEP_PFB_IS_TIMEOUT(pfb)) अणु /* ATN */
			rc = digital_in_send_saved_skb(ddev, data_exch);
			अगर (rc)
				जाओ error;

			जाओ मुक्त_resp;
		पूर्ण

		अगर (ddev->atn_count || ddev->nack_count) अणु
			PROTOCOL_ERR("14.12.4.4");
			rc = -EIO;
			जाओ error;
		पूर्ण

		rtox = DIGITAL_NFC_DEP_RTOX_VALUE(resp->data[0]);
		अगर (!rtox || rtox > DIGITAL_NFC_DEP_RTOX_MAX) अणु
			PROTOCOL_ERR("14.8.4.1");
			rc = -EIO;
			जाओ error;
		पूर्ण

		rc = digital_in_send_rtox(ddev, data_exch, rtox);
		अगर (rc)
			जाओ error;

		जाओ मुक्त_resp;
	पूर्ण

निकास:
	data_exch->cb(data_exch->cb_context, resp, rc);

error:
	kमुक्त(data_exch);

	kमुक्त_skb(ddev->chaining_skb);
	ddev->chaining_skb = शून्य;

	kमुक्त_skb(ddev->saved_skb);
	ddev->saved_skb = शून्य;

	अगर (rc)
		kमुक्त_skb(resp);

	वापस;

मुक्त_resp:
	dev_kमुक्त_skb(resp);
पूर्ण

पूर्णांक digital_in_send_dep_req(काष्ठा nfc_digital_dev *ddev,
			    काष्ठा nfc_target *target, काष्ठा sk_buff *skb,
			    काष्ठा digital_data_exch *data_exch)
अणु
	काष्ठा digital_dep_req_res *dep_req;
	काष्ठा sk_buff *chaining_skb, *पंचांगp_skb;
	पूर्णांक rc;

	skb_push(skb, माप(काष्ठा digital_dep_req_res));

	dep_req = (काष्ठा digital_dep_req_res *)skb->data;

	dep_req->dir = DIGITAL_NFC_DEP_FRAME_सूची_OUT;
	dep_req->cmd = DIGITAL_CMD_DEP_REQ;
	dep_req->pfb = ddev->curr_nfc_dep_pni;

	ddev->atn_count = 0;
	ddev->nack_count = 0;

	chaining_skb = ddev->chaining_skb;

	पंचांगp_skb = digital_send_dep_data_prep(ddev, skb, dep_req, data_exch);
	अगर (IS_ERR(पंचांगp_skb))
		वापस PTR_ERR(पंचांगp_skb);

	digital_skb_push_dep_sod(ddev, पंचांगp_skb);

	ddev->skb_add_crc(पंचांगp_skb);

	ddev->saved_skb = pskb_copy(पंचांगp_skb, GFP_KERNEL);

	rc = digital_in_send_cmd(ddev, पंचांगp_skb, ddev->dep_rwt,
				 digital_in_recv_dep_res, data_exch);
	अगर (rc) अणु
		अगर (पंचांगp_skb != skb)
			kमुक्त_skb(पंचांगp_skb);

		kमुक्त_skb(chaining_skb);
		ddev->chaining_skb = शून्य;

		kमुक्त_skb(ddev->saved_skb);
		ddev->saved_skb = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम digital_tg_set_rf_tech(काष्ठा nfc_digital_dev *ddev, u8 rf_tech)
अणु
	ddev->curr_rf_tech = rf_tech;

	ddev->skb_add_crc = digital_skb_add_crc_none;
	ddev->skb_check_crc = digital_skb_check_crc_none;

	अगर (DIGITAL_DRV_CAPS_TG_CRC(ddev))
		वापस;

	चयन (ddev->curr_rf_tech) अणु
	हाल NFC_DIGITAL_RF_TECH_106A:
		ddev->skb_add_crc = digital_skb_add_crc_a;
		ddev->skb_check_crc = digital_skb_check_crc_a;
		अवरोध;

	हाल NFC_DIGITAL_RF_TECH_212F:
	हाल NFC_DIGITAL_RF_TECH_424F:
		ddev->skb_add_crc = digital_skb_add_crc_f;
		ddev->skb_check_crc = digital_skb_check_crc_f;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक digital_tg_send_ack(काष्ठा nfc_digital_dev *ddev,
			       काष्ठा digital_data_exch *data_exch)
अणु
	काष्ठा digital_dep_req_res *dep_res;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_push(skb, माप(काष्ठा digital_dep_req_res));

	dep_res = (काष्ठा digital_dep_req_res *)skb->data;

	dep_res->dir = DIGITAL_NFC_DEP_FRAME_सूची_IN;
	dep_res->cmd = DIGITAL_CMD_DEP_RES;
	dep_res->pfb = DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU |
		       ddev->curr_nfc_dep_pni;

	अगर (ddev->did) अणु
		dep_res->pfb |= DIGITAL_NFC_DEP_PFB_DID_BIT;

		skb_put_data(skb, &ddev->did, माप(ddev->did));
	पूर्ण

	ddev->curr_nfc_dep_pni =
		DIGITAL_NFC_DEP_PFB_PNI(ddev->curr_nfc_dep_pni + 1);

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	ddev->saved_skb = pskb_copy(skb, GFP_KERNEL);

	rc = digital_tg_send_cmd(ddev, skb, 1500, digital_tg_recv_dep_req,
				 data_exch);
	अगर (rc) अणु
		kमुक्त_skb(skb);
		kमुक्त_skb(ddev->saved_skb);
		ddev->saved_skb = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक digital_tg_send_atn(काष्ठा nfc_digital_dev *ddev)
अणु
	काष्ठा digital_dep_req_res *dep_res;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, 1);
	अगर (!skb)
		वापस -ENOMEM;

	skb_push(skb, माप(काष्ठा digital_dep_req_res));

	dep_res = (काष्ठा digital_dep_req_res *)skb->data;

	dep_res->dir = DIGITAL_NFC_DEP_FRAME_सूची_IN;
	dep_res->cmd = DIGITAL_CMD_DEP_RES;
	dep_res->pfb = DIGITAL_NFC_DEP_PFB_SUPERVISOR_PDU;

	अगर (ddev->did) अणु
		dep_res->pfb |= DIGITAL_NFC_DEP_PFB_DID_BIT;

		skb_put_data(skb, &ddev->did, माप(ddev->did));
	पूर्ण

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	rc = digital_tg_send_cmd(ddev, skb, 1500, digital_tg_recv_dep_req,
				 शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल पूर्णांक digital_tg_send_saved_skb(काष्ठा nfc_digital_dev *ddev)
अणु
	पूर्णांक rc;

	अगर (!ddev->saved_skb)
		वापस -EINVAL;

	skb_get(ddev->saved_skb);

	rc = digital_tg_send_cmd(ddev, ddev->saved_skb, 1500,
				 digital_tg_recv_dep_req, शून्य);
	अगर (rc)
		kमुक्त_skb(ddev->saved_skb);

	वापस rc;
पूर्ण

अटल व्योम digital_tg_recv_dep_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp)
अणु
	पूर्णांक rc;
	काष्ठा digital_dep_req_res *dep_req;
	u8 pfb;
	माप_प्रकार size;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	rc = ddev->skb_check_crc(resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.6");
		जाओ निकास;
	पूर्ण

	rc = digital_skb_pull_dep_sod(ddev, resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.2");
		जाओ निकास;
	पूर्ण

	अगर (resp->len > ddev->local_payload_max) अणु
		rc = -EMSGSIZE;
		जाओ निकास;
	पूर्ण

	size = माप(काष्ठा digital_dep_req_res);
	dep_req = (काष्ठा digital_dep_req_res *)resp->data;

	अगर (resp->len < size || dep_req->dir != DIGITAL_NFC_DEP_FRAME_सूची_OUT ||
	    dep_req->cmd != DIGITAL_CMD_DEP_REQ) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	pfb = dep_req->pfb;

	अगर (DIGITAL_NFC_DEP_DID_BIT_SET(pfb)) अणु
		अगर (ddev->did && (ddev->did == resp->data[3])) अणु
			size++;
		पूर्ण अन्यथा अणु
			rc = -EIO;
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अगर (ddev->did) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (DIGITAL_NFC_DEP_NAD_BIT_SET(pfb)) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (size > resp->len) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	skb_pull(resp, size);

	चयन (DIGITAL_NFC_DEP_PFB_TYPE(pfb)) अणु
	हाल DIGITAL_NFC_DEP_PFB_I_PDU:
		pr_debug("DIGITAL_NFC_DEP_PFB_I_PDU\n");

		अगर (ddev->atn_count) अणु
			/* The target has received (and replied to) at least one
			 * ATN DEP_REQ.
			 */
			ddev->atn_count = 0;

			/* pni of resp PDU equal to the target current pni - 1
			 * means resp is the previous DEP_REQ PDU received from
			 * the initiator so the target replies with saved_skb
			 * which is the previous DEP_RES saved in
			 * digital_tg_send_dep_res().
			 */
			अगर (DIGITAL_NFC_DEP_PFB_PNI(pfb) ==
			  DIGITAL_NFC_DEP_PFB_PNI(ddev->curr_nfc_dep_pni - 1)) अणु
				rc = digital_tg_send_saved_skb(ddev);
				अगर (rc)
					जाओ निकास;

				जाओ मुक्त_resp;
			पूर्ण

			/* atn_count > 0 and PDU pni != curr_nfc_dep_pni - 1
			 * means the target probably did not received the last
			 * DEP_REQ PDU sent by the initiator. The target
			 * fallbacks to normal processing then.
			 */
		पूर्ण

		अगर (DIGITAL_NFC_DEP_PFB_PNI(pfb) != ddev->curr_nfc_dep_pni) अणु
			PROTOCOL_ERR("14.12.3.4");
			rc = -EIO;
			जाओ निकास;
		पूर्ण

		kमुक्त_skb(ddev->saved_skb);
		ddev->saved_skb = शून्य;

		resp = digital_recv_dep_data_gather(ddev, pfb, resp,
						    digital_tg_send_ack, शून्य);
		अगर (IS_ERR(resp)) अणु
			rc = PTR_ERR(resp);
			resp = शून्य;
			जाओ निकास;
		पूर्ण

		/* If resp is शून्य then we're still chaining so वापस and
		 * रुको क्रम the next part of the PDU.  Else, the PDU is
		 * complete so pass it up.
		 */
		अगर (!resp)
			वापस;

		rc = 0;
		अवरोध;
	हाल DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU:
		अगर (DIGITAL_NFC_DEP_NACK_BIT_SET(pfb)) अणु /* NACK */
			अगर (DIGITAL_NFC_DEP_PFB_PNI(pfb + 1) !=
						ddev->curr_nfc_dep_pni) अणु
				rc = -EIO;
				जाओ निकास;
			पूर्ण

			ddev->atn_count = 0;

			rc = digital_tg_send_saved_skb(ddev);
			अगर (rc)
				जाओ निकास;

			जाओ मुक्त_resp;
		पूर्ण

		/* ACK */
		अगर (ddev->atn_count) अणु
			/* The target has previously received one or more ATN
			 * PDUs.
			 */
			ddev->atn_count = 0;

			/* If the ACK PNI is equal to the target PNI - 1 means
			 * that the initiator did not receive the previous PDU
			 * sent by the target so re-send it.
			 */
			अगर (DIGITAL_NFC_DEP_PFB_PNI(pfb + 1) ==
						ddev->curr_nfc_dep_pni) अणु
				rc = digital_tg_send_saved_skb(ddev);
				अगर (rc)
					जाओ निकास;

				जाओ मुक्त_resp;
			पूर्ण

			/* Otherwise, the target did not receive the previous
			 * ACK PDU from the initiator. Fallback to normal
			 * processing of chained PDU then.
			 */
		पूर्ण

		/* Keep on sending chained PDU */
		अगर (!ddev->chaining_skb ||
		    DIGITAL_NFC_DEP_PFB_PNI(pfb) !=
					ddev->curr_nfc_dep_pni) अणु
			rc = -EIO;
			जाओ निकास;
		पूर्ण

		kमुक्त_skb(ddev->saved_skb);
		ddev->saved_skb = शून्य;

		rc = digital_tg_send_dep_res(ddev, ddev->chaining_skb);
		अगर (rc)
			जाओ निकास;

		जाओ मुक्त_resp;
	हाल DIGITAL_NFC_DEP_PFB_SUPERVISOR_PDU:
		अगर (DIGITAL_NFC_DEP_PFB_IS_TIMEOUT(pfb)) अणु
			rc = -EINVAL;
			जाओ निकास;
		पूर्ण

		rc = digital_tg_send_atn(ddev);
		अगर (rc)
			जाओ निकास;

		ddev->atn_count++;

		जाओ मुक्त_resp;
	पूर्ण

	rc = nfc_पंचांग_data_received(ddev->nfc_dev, resp);
	अगर (rc)
		resp = शून्य;

निकास:
	kमुक्त_skb(ddev->chaining_skb);
	ddev->chaining_skb = शून्य;

	ddev->atn_count = 0;

	kमुक्त_skb(ddev->saved_skb);
	ddev->saved_skb = शून्य;

	अगर (rc)
		kमुक्त_skb(resp);

	वापस;

मुक्त_resp:
	dev_kमुक्त_skb(resp);
पूर्ण

पूर्णांक digital_tg_send_dep_res(काष्ठा nfc_digital_dev *ddev, काष्ठा sk_buff *skb)
अणु
	काष्ठा digital_dep_req_res *dep_res;
	काष्ठा sk_buff *chaining_skb, *पंचांगp_skb;
	पूर्णांक rc;

	skb_push(skb, माप(काष्ठा digital_dep_req_res));

	dep_res = (काष्ठा digital_dep_req_res *)skb->data;

	dep_res->dir = DIGITAL_NFC_DEP_FRAME_सूची_IN;
	dep_res->cmd = DIGITAL_CMD_DEP_RES;
	dep_res->pfb = ddev->curr_nfc_dep_pni;

	अगर (ddev->did) अणु
		dep_res->pfb |= DIGITAL_NFC_DEP_PFB_DID_BIT;

		skb_put_data(skb, &ddev->did, माप(ddev->did));
	पूर्ण

	ddev->curr_nfc_dep_pni =
		DIGITAL_NFC_DEP_PFB_PNI(ddev->curr_nfc_dep_pni + 1);

	chaining_skb = ddev->chaining_skb;

	पंचांगp_skb = digital_send_dep_data_prep(ddev, skb, dep_res, शून्य);
	अगर (IS_ERR(पंचांगp_skb))
		वापस PTR_ERR(पंचांगp_skb);

	digital_skb_push_dep_sod(ddev, पंचांगp_skb);

	ddev->skb_add_crc(पंचांगp_skb);

	ddev->saved_skb = pskb_copy(पंचांगp_skb, GFP_KERNEL);

	rc = digital_tg_send_cmd(ddev, पंचांगp_skb, 1500, digital_tg_recv_dep_req,
				 शून्य);
	अगर (rc) अणु
		अगर (पंचांगp_skb != skb)
			kमुक्त_skb(पंचांगp_skb);

		kमुक्त_skb(chaining_skb);
		ddev->chaining_skb = शून्य;

		kमुक्त_skb(ddev->saved_skb);
		ddev->saved_skb = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम digital_tg_send_psl_res_complete(काष्ठा nfc_digital_dev *ddev,
					     व्योम *arg, काष्ठा sk_buff *resp)
अणु
	u8 rf_tech = (अचिन्हित दीर्घ)arg;

	अगर (IS_ERR(resp))
		वापस;

	digital_tg_set_rf_tech(ddev, rf_tech);

	digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH, rf_tech);

	digital_tg_listen(ddev, 1500, digital_tg_recv_dep_req, शून्य);

	dev_kमुक्त_skb(resp);
पूर्ण

अटल पूर्णांक digital_tg_send_psl_res(काष्ठा nfc_digital_dev *ddev, u8 did,
				   u8 rf_tech)
अणु
	काष्ठा digital_psl_res *psl_res;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	skb = digital_skb_alloc(ddev, माप(काष्ठा digital_psl_res));
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(काष्ठा digital_psl_res));

	psl_res = (काष्ठा digital_psl_res *)skb->data;

	psl_res->dir = DIGITAL_NFC_DEP_FRAME_सूची_IN;
	psl_res->cmd = DIGITAL_CMD_PSL_RES;
	psl_res->did = did;

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	ddev->curr_nfc_dep_pni = 0;

	rc = digital_tg_send_cmd(ddev, skb, 0, digital_tg_send_psl_res_complete,
				 (व्योम *)(अचिन्हित दीर्घ)rf_tech);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

अटल व्योम digital_tg_recv_psl_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
				    काष्ठा sk_buff *resp)
अणु
	पूर्णांक rc;
	काष्ठा digital_psl_req *psl_req;
	u8 rf_tech;
	u8 dsi, payload_size, payload_bits;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	rc = ddev->skb_check_crc(resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.6");
		जाओ निकास;
	पूर्ण

	rc = digital_skb_pull_dep_sod(ddev, resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.2");
		जाओ निकास;
	पूर्ण

	psl_req = (काष्ठा digital_psl_req *)resp->data;

	अगर (resp->len != माप(काष्ठा digital_psl_req) ||
	    psl_req->dir != DIGITAL_NFC_DEP_FRAME_सूची_OUT ||
	    psl_req->cmd != DIGITAL_CMD_PSL_REQ) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	dsi = (psl_req->brs >> 3) & 0x07;
	चयन (dsi) अणु
	हाल 0:
		rf_tech = NFC_DIGITAL_RF_TECH_106A;
		अवरोध;
	हाल 1:
		rf_tech = NFC_DIGITAL_RF_TECH_212F;
		अवरोध;
	हाल 2:
		rf_tech = NFC_DIGITAL_RF_TECH_424F;
		अवरोध;
	शेष:
		pr_err("Unsupported dsi value %d\n", dsi);
		जाओ निकास;
	पूर्ण

	payload_bits = DIGITAL_PAYLOAD_FSL_TO_BITS(psl_req->fsl);
	payload_size = digital_payload_bits_to_size(payload_bits);

	अगर (!payload_size || (payload_size > min(ddev->local_payload_max,
						 ddev->remote_payload_max))) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	ddev->local_payload_max = payload_size;
	ddev->remote_payload_max = payload_size;

	rc = digital_tg_send_psl_res(ddev, psl_req->did, rf_tech);

निकास:
	kमुक्त_skb(resp);
पूर्ण

अटल व्योम digital_tg_send_atr_res_complete(काष्ठा nfc_digital_dev *ddev,
					     व्योम *arg, काष्ठा sk_buff *resp)
अणु
	पूर्णांक offset;

	अगर (IS_ERR(resp)) अणु
		digital_poll_next_tech(ddev);
		वापस;
	पूर्ण

	offset = 2;
	अगर (resp->data[0] == DIGITAL_NFC_DEP_NFCA_SOD_SB)
		offset++;

	ddev->atn_count = 0;

	अगर (resp->data[offset] == DIGITAL_CMD_PSL_REQ)
		digital_tg_recv_psl_req(ddev, arg, resp);
	अन्यथा
		digital_tg_recv_dep_req(ddev, arg, resp);
पूर्ण

अटल पूर्णांक digital_tg_send_atr_res(काष्ठा nfc_digital_dev *ddev,
				   काष्ठा digital_atr_req *atr_req)
अणु
	काष्ठा digital_atr_res *atr_res;
	काष्ठा sk_buff *skb;
	u8 *gb, payload_bits;
	माप_प्रकार gb_len;
	पूर्णांक rc;

	gb = nfc_get_local_general_bytes(ddev->nfc_dev, &gb_len);
	अगर (!gb)
		gb_len = 0;

	skb = digital_skb_alloc(ddev, माप(काष्ठा digital_atr_res) + gb_len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(काष्ठा digital_atr_res));
	atr_res = (काष्ठा digital_atr_res *)skb->data;

	स_रखो(atr_res, 0, माप(काष्ठा digital_atr_res));

	atr_res->dir = DIGITAL_NFC_DEP_FRAME_सूची_IN;
	atr_res->cmd = DIGITAL_CMD_ATR_RES;
	स_नकल(atr_res->nfcid3, atr_req->nfcid3, माप(atr_req->nfcid3));
	atr_res->to = DIGITAL_NFC_DEP_TG_MAX_WT;

	ddev->local_payload_max = DIGITAL_PAYLOAD_SIZE_MAX;
	payload_bits = digital_payload_माप_प्रकारo_bits(ddev->local_payload_max);
	atr_res->pp = DIGITAL_PAYLOAD_BITS_TO_PP(payload_bits);

	अगर (gb_len) अणु
		skb_put(skb, gb_len);

		atr_res->pp |= DIGITAL_GB_BIT;
		स_नकल(atr_res->gb, gb, gb_len);
	पूर्ण

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	ddev->curr_nfc_dep_pni = 0;

	rc = digital_tg_send_cmd(ddev, skb, 999,
				 digital_tg_send_atr_res_complete, शून्य);
	अगर (rc)
		kमुक्त_skb(skb);

	वापस rc;
पूर्ण

व्योम digital_tg_recv_atr_req(काष्ठा nfc_digital_dev *ddev, व्योम *arg,
			     काष्ठा sk_buff *resp)
अणु
	पूर्णांक rc;
	काष्ठा digital_atr_req *atr_req;
	माप_प्रकार gb_len, min_size;
	u8 poll_tech_count, payload_bits;

	अगर (IS_ERR(resp)) अणु
		rc = PTR_ERR(resp);
		resp = शून्य;
		जाओ निकास;
	पूर्ण

	अगर (!resp->len) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (resp->data[0] == DIGITAL_NFC_DEP_NFCA_SOD_SB) अणु
		min_size = DIGITAL_ATR_REQ_MIN_SIZE + 2;
		digital_tg_set_rf_tech(ddev, NFC_DIGITAL_RF_TECH_106A);
	पूर्ण अन्यथा अणु
		min_size = DIGITAL_ATR_REQ_MIN_SIZE + 1;
		digital_tg_set_rf_tech(ddev, NFC_DIGITAL_RF_TECH_212F);
	पूर्ण

	अगर (resp->len < min_size) अणु
		rc = -EIO;
		जाओ निकास;
	पूर्ण

	ddev->curr_protocol = NFC_PROTO_NFC_DEP_MASK;

	rc = ddev->skb_check_crc(resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.6");
		जाओ निकास;
	पूर्ण

	rc = digital_skb_pull_dep_sod(ddev, resp);
	अगर (rc) अणु
		PROTOCOL_ERR("14.4.1.2");
		जाओ निकास;
	पूर्ण

	atr_req = (काष्ठा digital_atr_req *)resp->data;

	अगर (atr_req->dir != DIGITAL_NFC_DEP_FRAME_सूची_OUT ||
	    atr_req->cmd != DIGITAL_CMD_ATR_REQ ||
	    atr_req->did > DIGITAL_DID_MAX) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	payload_bits = DIGITAL_PAYLOAD_PP_TO_BITS(atr_req->pp);
	ddev->remote_payload_max = digital_payload_bits_to_size(payload_bits);

	अगर (!ddev->remote_payload_max) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	ddev->did = atr_req->did;

	rc = digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFC_DEP_ACTIVATED);
	अगर (rc)
		जाओ निकास;

	rc = digital_tg_send_atr_res(ddev, atr_req);
	अगर (rc)
		जाओ निकास;

	gb_len = resp->len - माप(काष्ठा digital_atr_req);

	poll_tech_count = ddev->poll_tech_count;
	ddev->poll_tech_count = 0;

	rc = nfc_पंचांग_activated(ddev->nfc_dev, NFC_PROTO_NFC_DEP_MASK,
			      NFC_COMM_PASSIVE, atr_req->gb, gb_len);
	अगर (rc) अणु
		ddev->poll_tech_count = poll_tech_count;
		जाओ निकास;
	पूर्ण

	rc = 0;
निकास:
	अगर (rc)
		digital_poll_next_tech(ddev);

	dev_kमुक्त_skb(resp);
पूर्ण
