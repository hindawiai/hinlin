<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014  STMicroelectronics SAS. All rights reserved.
 */

#समावेश <net/nfc/hci.h>

#समावेश "st21nfca.h"

#घोषणा ST21NFCA_NFCIP1_INITIATOR 0x00
#घोषणा ST21NFCA_NFCIP1_REQ 0xd4
#घोषणा ST21NFCA_NFCIP1_RES 0xd5
#घोषणा ST21NFCA_NFCIP1_ATR_REQ 0x00
#घोषणा ST21NFCA_NFCIP1_ATR_RES 0x01
#घोषणा ST21NFCA_NFCIP1_PSL_REQ 0x04
#घोषणा ST21NFCA_NFCIP1_PSL_RES 0x05
#घोषणा ST21NFCA_NFCIP1_DEP_REQ 0x06
#घोषणा ST21NFCA_NFCIP1_DEP_RES 0x07

#घोषणा ST21NFCA_NFC_DEP_PFB_PNI(pfb)     ((pfb) & 0x03)
#घोषणा ST21NFCA_NFC_DEP_PFB_TYPE(pfb) ((pfb) & 0xE0)
#घोषणा ST21NFCA_NFC_DEP_PFB_IS_TIMEOUT(pfb) \
				((pfb) & ST21NFCA_NFC_DEP_PFB_TIMEOUT_BIT)
#घोषणा ST21NFCA_NFC_DEP_DID_BIT_SET(pfb) ((pfb) & 0x04)
#घोषणा ST21NFCA_NFC_DEP_NAD_BIT_SET(pfb) ((pfb) & 0x08)
#घोषणा ST21NFCA_NFC_DEP_PFB_TIMEOUT_BIT 0x10

#घोषणा ST21NFCA_NFC_DEP_PFB_IS_TIMEOUT(pfb) \
				((pfb) & ST21NFCA_NFC_DEP_PFB_TIMEOUT_BIT)

#घोषणा ST21NFCA_NFC_DEP_PFB_I_PDU          0x00
#घोषणा ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU   0x40
#घोषणा ST21NFCA_NFC_DEP_PFB_SUPERVISOR_PDU 0x80

#घोषणा ST21NFCA_ATR_REQ_MIN_SIZE 17
#घोषणा ST21NFCA_ATR_REQ_MAX_SIZE 65
#घोषणा ST21NFCA_LR_BITS_PAYLOAD_SIZE_254B 0x30
#घोषणा ST21NFCA_GB_BIT  0x02

#घोषणा ST21NFCA_EVT_SEND_DATA		0x10
#घोषणा ST21NFCA_EVT_FIELD_ON           0x11
#घोषणा ST21NFCA_EVT_CARD_DEACTIVATED   0x12
#घोषणा ST21NFCA_EVT_CARD_ACTIVATED     0x13
#घोषणा ST21NFCA_EVT_FIELD_OFF          0x14

#घोषणा ST21NFCA_EVT_CARD_F_BITRATE 0x16
#घोषणा ST21NFCA_EVT_READER_F_BITRATE 0x13
#घोषणा	ST21NFCA_PSL_REQ_SEND_SPEED(brs) (brs & 0x38)
#घोषणा ST21NFCA_PSL_REQ_RECV_SPEED(brs) (brs & 0x07)
#घोषणा ST21NFCA_PP2LRI(pp) ((pp & 0x30) >> 4)
#घोषणा ST21NFCA_CARD_BITRATE_212 0x01
#घोषणा ST21NFCA_CARD_BITRATE_424 0x02

#घोषणा ST21NFCA_DEFAULT_TIMEOUT 0x0a


#घोषणा PROTOCOL_ERR(req) pr_err("%d: ST21NFCA Protocol error: %s\n", \
				 __LINE__, req)

काष्ठा st21nfca_atr_req अणु
	u8 length;
	u8 cmd0;
	u8 cmd1;
	u8 nfcid3[NFC_NFCID3_MAXSIZE];
	u8 did;
	u8 bsi;
	u8 bri;
	u8 ppi;
	u8 gbi[];
पूर्ण __packed;

काष्ठा st21nfca_atr_res अणु
	u8 length;
	u8 cmd0;
	u8 cmd1;
	u8 nfcid3[NFC_NFCID3_MAXSIZE];
	u8 did;
	u8 bsi;
	u8 bri;
	u8 to;
	u8 ppi;
	u8 gbi[];
पूर्ण __packed;

काष्ठा st21nfca_psl_req अणु
	u8 length;
	u8 cmd0;
	u8 cmd1;
	u8 did;
	u8 brs;
	u8 fsl;
पूर्ण __packed;

काष्ठा st21nfca_psl_res अणु
	u8 length;
	u8 cmd0;
	u8 cmd1;
	u8 did;
पूर्ण __packed;

काष्ठा st21nfca_dep_req_res अणु
	u8 length;
	u8 cmd0;
	u8 cmd1;
	u8 pfb;
	u8 did;
	u8 nad;
पूर्ण __packed;

अटल व्योम st21nfca_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा st21nfca_hci_info *info = container_of(work,
						काष्ठा st21nfca_hci_info,
						dep_info.tx_work);

	काष्ठा nfc_dev *dev;
	काष्ठा sk_buff *skb;

	अगर (info) अणु
		dev = info->hdev->ndev;
		skb = info->dep_info.tx_pending;

		device_lock(&dev->dev);

		nfc_hci_send_cmd_async(info->hdev, ST21NFCA_RF_READER_F_GATE,
				ST21NFCA_WR_XCHG_DATA, skb->data, skb->len,
				info->async_cb, info);
		device_unlock(&dev->dev);
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम st21nfca_im_send_pdu(काष्ठा st21nfca_hci_info *info,
						काष्ठा sk_buff *skb)
अणु
	info->dep_info.tx_pending = skb;
	schedule_work(&info->dep_info.tx_work);
पूर्ण

अटल पूर्णांक st21nfca_पंचांग_send_atr_res(काष्ठा nfc_hci_dev *hdev,
				    काष्ठा st21nfca_atr_req *atr_req)
अणु
	काष्ठा st21nfca_atr_res *atr_res;
	काष्ठा sk_buff *skb;
	माप_प्रकार gb_len;
	पूर्णांक r;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	gb_len = atr_req->length - माप(काष्ठा st21nfca_atr_req);
	skb = alloc_skb(atr_req->length + 1, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put(skb, माप(काष्ठा st21nfca_atr_res));

	atr_res = (काष्ठा st21nfca_atr_res *)skb->data;
	स_रखो(atr_res, 0, माप(काष्ठा st21nfca_atr_res));

	atr_res->length = atr_req->length + 1;
	atr_res->cmd0 = ST21NFCA_NFCIP1_RES;
	atr_res->cmd1 = ST21NFCA_NFCIP1_ATR_RES;

	स_नकल(atr_res->nfcid3, atr_req->nfcid3, 6);
	atr_res->bsi = 0x00;
	atr_res->bri = 0x00;
	atr_res->to = ST21NFCA_DEFAULT_TIMEOUT;
	atr_res->ppi = ST21NFCA_LR_BITS_PAYLOAD_SIZE_254B;

	अगर (gb_len) अणु
		skb_put(skb, gb_len);

		atr_res->ppi |= ST21NFCA_GB_BIT;
		स_नकल(atr_res->gbi, atr_req->gbi, gb_len);
		r = nfc_set_remote_general_bytes(hdev->ndev, atr_res->gbi,
						  gb_len);
		अगर (r < 0) अणु
			kमुक्त_skb(skb);
			वापस r;
		पूर्ण
	पूर्ण

	info->dep_info.curr_nfc_dep_pni = 0;

	r = nfc_hci_send_event(hdev, ST21NFCA_RF_CARD_F_GATE,
				ST21NFCA_EVT_SEND_DATA, skb->data, skb->len);
	kमुक्त_skb(skb);
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_पंचांग_recv_atr_req(काष्ठा nfc_hci_dev *hdev,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा st21nfca_atr_req *atr_req;
	माप_प्रकार gb_len;
	पूर्णांक r;

	skb_trim(skb, skb->len - 1);

	अगर (!skb->len) अणु
		r = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (skb->len < ST21NFCA_ATR_REQ_MIN_SIZE) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	atr_req = (काष्ठा st21nfca_atr_req *)skb->data;

	अगर (atr_req->length < माप(काष्ठा st21nfca_atr_req)) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	r = st21nfca_पंचांग_send_atr_res(hdev, atr_req);
	अगर (r)
		जाओ निकास;

	gb_len = skb->len - माप(काष्ठा st21nfca_atr_req);

	r = nfc_पंचांग_activated(hdev->ndev, NFC_PROTO_NFC_DEP_MASK,
			      NFC_COMM_PASSIVE, atr_req->gbi, gb_len);
	अगर (r)
		जाओ निकास;

	r = 0;

निकास:
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_पंचांग_send_psl_res(काष्ठा nfc_hci_dev *hdev,
				    काष्ठा st21nfca_psl_req *psl_req)
अणु
	काष्ठा st21nfca_psl_res *psl_res;
	काष्ठा sk_buff *skb;
	u8 bitrate[2] = अणु0, 0पूर्ण;
	पूर्णांक r;

	skb = alloc_skb(माप(काष्ठा st21nfca_psl_res), GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;
	skb_put(skb, माप(काष्ठा st21nfca_psl_res));

	psl_res = (काष्ठा st21nfca_psl_res *)skb->data;

	psl_res->length = माप(काष्ठा st21nfca_psl_res);
	psl_res->cmd0 = ST21NFCA_NFCIP1_RES;
	psl_res->cmd1 = ST21NFCA_NFCIP1_PSL_RES;
	psl_res->did = psl_req->did;

	r = nfc_hci_send_event(hdev, ST21NFCA_RF_CARD_F_GATE,
				ST21NFCA_EVT_SEND_DATA, skb->data, skb->len);
	अगर (r < 0)
		जाओ error;

	/*
	 * ST21NFCA only support P2P passive.
	 * PSL_REQ BRS value != 0 has only a meaning to
	 * change technology to type F.
	 * We change to BITRATE 424Kbits.
	 * In other हाल चयन to BITRATE 106Kbits.
	 */
	अगर (ST21NFCA_PSL_REQ_SEND_SPEED(psl_req->brs) &&
	    ST21NFCA_PSL_REQ_RECV_SPEED(psl_req->brs)) अणु
		bitrate[0] = ST21NFCA_CARD_BITRATE_424;
		bitrate[1] = ST21NFCA_CARD_BITRATE_424;
	पूर्ण

	/* Send an event to change bitrate change event to card f */
	r = nfc_hci_send_event(hdev, ST21NFCA_RF_CARD_F_GATE,
			ST21NFCA_EVT_CARD_F_BITRATE, bitrate, 2);
error:
	kमुक्त_skb(skb);
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_पंचांग_recv_psl_req(काष्ठा nfc_hci_dev *hdev,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा st21nfca_psl_req *psl_req;
	पूर्णांक r;

	skb_trim(skb, skb->len - 1);

	अगर (!skb->len) अणु
		r = -EIO;
		जाओ निकास;
	पूर्ण

	psl_req = (काष्ठा st21nfca_psl_req *)skb->data;

	अगर (skb->len < माप(काष्ठा st21nfca_psl_req)) अणु
		r = -EIO;
		जाओ निकास;
	पूर्ण

	r = st21nfca_पंचांग_send_psl_res(hdev, psl_req);
निकास:
	वापस r;
पूर्ण

पूर्णांक st21nfca_पंचांग_send_dep_res(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	*(u8 *)skb_push(skb, 1) = info->dep_info.curr_nfc_dep_pni;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_DEP_RES;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_RES;
	*(u8 *)skb_push(skb, 1) = skb->len;

	r = nfc_hci_send_event(hdev, ST21NFCA_RF_CARD_F_GATE,
			ST21NFCA_EVT_SEND_DATA, skb->data, skb->len);
	kमुक्त_skb(skb);

	वापस r;
पूर्ण
EXPORT_SYMBOL(st21nfca_पंचांग_send_dep_res);

अटल पूर्णांक st21nfca_पंचांग_recv_dep_req(काष्ठा nfc_hci_dev *hdev,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा st21nfca_dep_req_res *dep_req;
	u8 size;
	पूर्णांक r;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	skb_trim(skb, skb->len - 1);

	size = 4;

	dep_req = (काष्ठा st21nfca_dep_req_res *)skb->data;
	अगर (skb->len < size) अणु
		r = -EIO;
		जाओ निकास;
	पूर्ण

	अगर (ST21NFCA_NFC_DEP_DID_BIT_SET(dep_req->pfb))
		size++;
	अगर (ST21NFCA_NFC_DEP_NAD_BIT_SET(dep_req->pfb))
		size++;

	अगर (skb->len < size) अणु
		r = -EIO;
		जाओ निकास;
	पूर्ण

	/* Receiving DEP_REQ - Decoding */
	चयन (ST21NFCA_NFC_DEP_PFB_TYPE(dep_req->pfb)) अणु
	हाल ST21NFCA_NFC_DEP_PFB_I_PDU:
		info->dep_info.curr_nfc_dep_pni =
				ST21NFCA_NFC_DEP_PFB_PNI(dep_req->pfb);
		अवरोध;
	हाल ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU:
		pr_err("Received a ACK/NACK PDU\n");
		अवरोध;
	हाल ST21NFCA_NFC_DEP_PFB_SUPERVISOR_PDU:
		pr_err("Received a SUPERVISOR PDU\n");
		अवरोध;
	पूर्ण

	skb_pull(skb, size);

	वापस nfc_पंचांग_data_received(hdev->ndev, skb);
निकास:
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_पंचांग_event_send_data(काष्ठा nfc_hci_dev *hdev,
				काष्ठा sk_buff *skb)
अणु
	u8 cmd0, cmd1;
	पूर्णांक r;

	cmd0 = skb->data[1];
	चयन (cmd0) अणु
	हाल ST21NFCA_NFCIP1_REQ:
		cmd1 = skb->data[2];
		चयन (cmd1) अणु
		हाल ST21NFCA_NFCIP1_ATR_REQ:
			r = st21nfca_पंचांग_recv_atr_req(hdev, skb);
			अवरोध;
		हाल ST21NFCA_NFCIP1_PSL_REQ:
			r = st21nfca_पंचांग_recv_psl_req(hdev, skb);
			अवरोध;
		हाल ST21NFCA_NFCIP1_DEP_REQ:
			r = st21nfca_पंचांग_recv_dep_req(hdev, skb);
			अवरोध;
		शेष:
			वापस 1;
		पूर्ण
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण
	वापस r;
पूर्ण

/*
 * Returns:
 * <= 0: driver handled the event, skb consumed
 *    1: driver करोes not handle the event, please करो standard processing
 */
पूर्णांक st21nfca_dep_event_received(काष्ठा nfc_hci_dev *hdev,
				u8 event, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r = 0;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	pr_debug("dep event: %d\n", event);

	चयन (event) अणु
	हाल ST21NFCA_EVT_CARD_ACTIVATED:
		info->dep_info.curr_nfc_dep_pni = 0;
		अवरोध;
	हाल ST21NFCA_EVT_CARD_DEACTIVATED:
		अवरोध;
	हाल ST21NFCA_EVT_FIELD_ON:
		अवरोध;
	हाल ST21NFCA_EVT_FIELD_OFF:
		अवरोध;
	हाल ST21NFCA_EVT_SEND_DATA:
		r = st21nfca_पंचांग_event_send_data(hdev, skb);
		अगर (r < 0)
			वापस r;
		वापस 0;
	शेष:
		nfc_err(&hdev->ndev->dev, "Unexpected event on card f gate\n");
		वापस 1;
	पूर्ण
	kमुक्त_skb(skb);
	वापस r;
पूर्ण
EXPORT_SYMBOL(st21nfca_dep_event_received);

अटल व्योम st21nfca_im_send_psl_req(काष्ठा nfc_hci_dev *hdev, u8 did, u8 bsi,
				     u8 bri, u8 lri)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा st21nfca_psl_req *psl_req;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	skb =
	    alloc_skb(माप(काष्ठा st21nfca_psl_req) + 1, GFP_KERNEL);
	अगर (!skb)
		वापस;
	skb_reserve(skb, 1);

	skb_put(skb, माप(काष्ठा st21nfca_psl_req));
	psl_req = (काष्ठा st21nfca_psl_req *) skb->data;

	psl_req->length = माप(काष्ठा st21nfca_psl_req);
	psl_req->cmd0 = ST21NFCA_NFCIP1_REQ;
	psl_req->cmd1 = ST21NFCA_NFCIP1_PSL_REQ;
	psl_req->did = did;
	psl_req->brs = (0x30 & bsi << 4) | (bri & 0x03);
	psl_req->fsl = lri;

	*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10;

	st21nfca_im_send_pdu(info, skb);
पूर्ण

#घोषणा ST21NFCA_CB_TYPE_READER_F 1
अटल व्योम st21nfca_im_recv_atr_res_cb(व्योम *context, काष्ठा sk_buff *skb,
					पूर्णांक err)
अणु
	काष्ठा st21nfca_hci_info *info = context;
	काष्ठा st21nfca_atr_res *atr_res;
	पूर्णांक r;

	अगर (err != 0)
		वापस;

	अगर (!skb)
		वापस;

	चयन (info->async_cb_type) अणु
	हाल ST21NFCA_CB_TYPE_READER_F:
		skb_trim(skb, skb->len - 1);
		atr_res = (काष्ठा st21nfca_atr_res *)skb->data;
		r = nfc_set_remote_general_bytes(info->hdev->ndev,
				atr_res->gbi,
				skb->len - माप(काष्ठा st21nfca_atr_res));
		अगर (r < 0)
			वापस;

		अगर (atr_res->to >= 0x0e)
			info->dep_info.to = 0x0e;
		अन्यथा
			info->dep_info.to = atr_res->to + 1;

		info->dep_info.to |= 0x10;

		r = nfc_dep_link_is_up(info->hdev->ndev, info->dep_info.idx,
					NFC_COMM_PASSIVE, NFC_RF_INITIATOR);
		अगर (r < 0)
			वापस;

		info->dep_info.curr_nfc_dep_pni = 0;
		अगर (ST21NFCA_PP2LRI(atr_res->ppi) != info->dep_info.lri)
			st21nfca_im_send_psl_req(info->hdev, atr_res->did,
						atr_res->bsi, atr_res->bri,
						ST21NFCA_PP2LRI(atr_res->ppi));
		अवरोध;
	शेष:
		kमुक्त_skb(skb);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक st21nfca_im_send_atr_req(काष्ठा nfc_hci_dev *hdev, u8 *gb, माप_प्रकार gb_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);
	काष्ठा st21nfca_atr_req *atr_req;
	काष्ठा nfc_target *target;
	uपूर्णांक size;

	info->dep_info.to = ST21NFCA_DEFAULT_TIMEOUT;
	size = ST21NFCA_ATR_REQ_MIN_SIZE + gb_len;
	अगर (size > ST21NFCA_ATR_REQ_MAX_SIZE) अणु
		PROTOCOL_ERR("14.6.1.1");
		वापस -EINVAL;
	पूर्ण

	skb =
	    alloc_skb(माप(काष्ठा st21nfca_atr_req) + gb_len + 1, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, 1);

	skb_put(skb, माप(काष्ठा st21nfca_atr_req));

	atr_req = (काष्ठा st21nfca_atr_req *)skb->data;
	स_रखो(atr_req, 0, माप(काष्ठा st21nfca_atr_req));

	atr_req->cmd0 = ST21NFCA_NFCIP1_REQ;
	atr_req->cmd1 = ST21NFCA_NFCIP1_ATR_REQ;
	स_रखो(atr_req->nfcid3, 0, NFC_NFCID3_MAXSIZE);
	target = hdev->ndev->tarमाला_लो;

	अगर (target->sensf_res_len > 0)
		स_नकल(atr_req->nfcid3, target->sensf_res,
				target->sensf_res_len);
	अन्यथा
		get_अक्रमom_bytes(atr_req->nfcid3, NFC_NFCID3_MAXSIZE);

	atr_req->did = 0x0;

	atr_req->bsi = 0x00;
	atr_req->bri = 0x00;
	atr_req->ppi = ST21NFCA_LR_BITS_PAYLOAD_SIZE_254B;
	अगर (gb_len) अणु
		atr_req->ppi |= ST21NFCA_GB_BIT;
		skb_put_data(skb, gb, gb_len);
	पूर्ण
	atr_req->length = माप(काष्ठा st21nfca_atr_req) + hdev->gb_len;

	*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10; /* समयout */

	info->async_cb_type = ST21NFCA_CB_TYPE_READER_F;
	info->async_cb_context = info;
	info->async_cb = st21nfca_im_recv_atr_res_cb;
	info->dep_info.bri = atr_req->bri;
	info->dep_info.bsi = atr_req->bsi;
	info->dep_info.lri = ST21NFCA_PP2LRI(atr_req->ppi);

	वापस nfc_hci_send_cmd_async(hdev, ST21NFCA_RF_READER_F_GATE,
				ST21NFCA_WR_XCHG_DATA, skb->data,
				skb->len, info->async_cb, info);
पूर्ण
EXPORT_SYMBOL(st21nfca_im_send_atr_req);

अटल व्योम st21nfca_im_recv_dep_res_cb(व्योम *context, काष्ठा sk_buff *skb,
					पूर्णांक err)
अणु
	काष्ठा st21nfca_hci_info *info = context;
	काष्ठा st21nfca_dep_req_res *dep_res;

	पूर्णांक size;

	अगर (err != 0)
		वापस;

	अगर (!skb)
		वापस;

	चयन (info->async_cb_type) अणु
	हाल ST21NFCA_CB_TYPE_READER_F:
		dep_res = (काष्ठा st21nfca_dep_req_res *)skb->data;

		size = 3;
		अगर (skb->len < size)
			जाओ निकास;

		अगर (ST21NFCA_NFC_DEP_DID_BIT_SET(dep_res->pfb))
			size++;
		अगर (ST21NFCA_NFC_DEP_NAD_BIT_SET(dep_res->pfb))
			size++;

		अगर (skb->len < size)
			जाओ निकास;

		skb_trim(skb, skb->len - 1);

		/* Receiving DEP_REQ - Decoding */
		चयन (ST21NFCA_NFC_DEP_PFB_TYPE(dep_res->pfb)) अणु
		हाल ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU:
			pr_err("Received a ACK/NACK PDU\n");
			fallthrough;
		हाल ST21NFCA_NFC_DEP_PFB_I_PDU:
			info->dep_info.curr_nfc_dep_pni =
			    ST21NFCA_NFC_DEP_PFB_PNI(dep_res->pfb + 1);
			size++;
			skb_pull(skb, size);
			nfc_पंचांग_data_received(info->hdev->ndev, skb);
			अवरोध;
		हाल ST21NFCA_NFC_DEP_PFB_SUPERVISOR_PDU:
			pr_err("Received a SUPERVISOR PDU\n");
			skb_pull(skb, size);
			*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_DEP_REQ;
			*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_REQ;
			*(u8 *)skb_push(skb, 1) = skb->len;
			*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10;

			st21nfca_im_send_pdu(info, skb);
			अवरोध;
		पूर्ण

		वापस;
	शेष:
		अवरोध;
	पूर्ण

निकास:
	kमुक्त_skb(skb);
पूर्ण

पूर्णांक st21nfca_im_send_dep_req(काष्ठा nfc_hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	info->async_cb_type = ST21NFCA_CB_TYPE_READER_F;
	info->async_cb_context = info;
	info->async_cb = st21nfca_im_recv_dep_res_cb;

	*(u8 *)skb_push(skb, 1) = info->dep_info.curr_nfc_dep_pni;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_DEP_REQ;
	*(u8 *)skb_push(skb, 1) = ST21NFCA_NFCIP1_REQ;
	*(u8 *)skb_push(skb, 1) = skb->len;

	*(u8 *)skb_push(skb, 1) = info->dep_info.to | 0x10;

	वापस nfc_hci_send_cmd_async(hdev, ST21NFCA_RF_READER_F_GATE,
				      ST21NFCA_WR_XCHG_DATA,
				      skb->data, skb->len,
				      info->async_cb, info);
पूर्ण
EXPORT_SYMBOL(st21nfca_im_send_dep_req);

व्योम st21nfca_dep_init(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	INIT_WORK(&info->dep_info.tx_work, st21nfca_tx_work);
	info->dep_info.curr_nfc_dep_pni = 0;
	info->dep_info.idx = 0;
	info->dep_info.to = ST21NFCA_DEFAULT_TIMEOUT;
पूर्ण
EXPORT_SYMBOL(st21nfca_dep_init);

व्योम st21nfca_dep_deinit(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	cancel_work_sync(&info->dep_info.tx_work);
पूर्ण
EXPORT_SYMBOL(st21nfca_dep_deinit);
