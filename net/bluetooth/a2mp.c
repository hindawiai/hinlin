<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
   Copyright (c) 2010,2011 Code Aurora Forum.  All rights reserved.
   Copyright (c) 2011,2012 Intel Corp.

*/

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>

#समावेश "hci_request.h"
#समावेश "a2mp.h"
#समावेश "amp.h"

#घोषणा A2MP_FEAT_EXT	0x8000

/* Global AMP Manager list */
अटल LIST_HEAD(amp_mgr_list);
अटल DEFINE_MUTEX(amp_mgr_list_lock);

/* A2MP build & send command helper functions */
अटल काष्ठा a2mp_cmd *__a2mp_build(u8 code, u8 ident, u16 len, व्योम *data)
अणु
	काष्ठा a2mp_cmd *cmd;
	पूर्णांक plen;

	plen = माप(*cmd) + len;
	cmd = kzalloc(plen, GFP_KERNEL);
	अगर (!cmd)
		वापस शून्य;

	cmd->code = code;
	cmd->ident = ident;
	cmd->len = cpu_to_le16(len);

	स_नकल(cmd->data, data, len);

	वापस cmd;
पूर्ण

अटल व्योम a2mp_send(काष्ठा amp_mgr *mgr, u8 code, u8 ident, u16 len, व्योम *data)
अणु
	काष्ठा l2cap_chan *chan = mgr->a2mp_chan;
	काष्ठा a2mp_cmd *cmd;
	u16 total_len = len + माप(*cmd);
	काष्ठा kvec iv;
	काष्ठा msghdr msg;

	cmd = __a2mp_build(code, ident, len, data);
	अगर (!cmd)
		वापस;

	iv.iov_base = cmd;
	iv.iov_len = total_len;

	स_रखो(&msg, 0, माप(msg));

	iov_iter_kvec(&msg.msg_iter, WRITE, &iv, 1, total_len);

	l2cap_chan_send(chan, &msg, total_len);

	kमुक्त(cmd);
पूर्ण

अटल u8 __next_ident(काष्ठा amp_mgr *mgr)
अणु
	अगर (++mgr->ident == 0)
		mgr->ident = 1;

	वापस mgr->ident;
पूर्ण

अटल काष्ठा amp_mgr *amp_mgr_lookup_by_state(u8 state)
अणु
	काष्ठा amp_mgr *mgr;

	mutex_lock(&amp_mgr_list_lock);
	list_क्रम_each_entry(mgr, &amp_mgr_list, list) अणु
		अगर (test_and_clear_bit(state, &mgr->state)) अणु
			amp_mgr_get(mgr);
			mutex_unlock(&amp_mgr_list_lock);
			वापस mgr;
		पूर्ण
	पूर्ण
	mutex_unlock(&amp_mgr_list_lock);

	वापस शून्य;
पूर्ण

/* hci_dev_list shall be locked */
अटल व्योम __a2mp_add_cl(काष्ठा amp_mgr *mgr, काष्ठा a2mp_cl *cl)
अणु
	काष्ठा hci_dev *hdev;
	पूर्णांक i = 1;

	cl[0].id = AMP_ID_BREDR;
	cl[0].type = AMP_TYPE_BREDR;
	cl[0].status = AMP_STATUS_BLUETOOTH_ONLY;

	list_क्रम_each_entry(hdev, &hci_dev_list, list) अणु
		अगर (hdev->dev_type == HCI_AMP) अणु
			cl[i].id = hdev->id;
			cl[i].type = hdev->amp_type;
			अगर (test_bit(HCI_UP, &hdev->flags))
				cl[i].status = hdev->amp_status;
			अन्यथा
				cl[i].status = AMP_STATUS_POWERED_DOWN;
			i++;
		पूर्ण
	पूर्ण
पूर्ण

/* Processing A2MP messages */
अटल पूर्णांक a2mp_command_rej(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
			    काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_cmd_rej *rej = (व्योम *) skb->data;

	अगर (le16_to_cpu(hdr->len) < माप(*rej))
		वापस -EINVAL;

	BT_DBG("ident %d reason %d", hdr->ident, le16_to_cpu(rej->reason));

	skb_pull(skb, माप(*rej));

	वापस 0;
पूर्ण

अटल पूर्णांक a2mp_discover_req(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
			     काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_discov_req *req = (व्योम *) skb->data;
	u16 len = le16_to_cpu(hdr->len);
	काष्ठा a2mp_discov_rsp *rsp;
	u16 ext_feat;
	u8 num_ctrl;
	काष्ठा hci_dev *hdev;

	अगर (len < माप(*req))
		वापस -EINVAL;

	skb_pull(skb, माप(*req));

	ext_feat = le16_to_cpu(req->ext_feat);

	BT_DBG("mtu %d efm 0x%4.4x", le16_to_cpu(req->mtu), ext_feat);

	/* check that packet is not broken क्रम now */
	जबतक (ext_feat & A2MP_FEAT_EXT) अणु
		अगर (len < माप(ext_feat))
			वापस -EINVAL;

		ext_feat = get_unaligned_le16(skb->data);
		BT_DBG("efm 0x%4.4x", ext_feat);
		len -= माप(ext_feat);
		skb_pull(skb, माप(ext_feat));
	पूर्ण

	पढ़ो_lock(&hci_dev_list_lock);

	/* at minimum the BR/EDR needs to be listed */
	num_ctrl = 1;

	list_क्रम_each_entry(hdev, &hci_dev_list, list) अणु
		अगर (hdev->dev_type == HCI_AMP)
			num_ctrl++;
	पूर्ण

	len = काष्ठा_size(rsp, cl, num_ctrl);
	rsp = kदो_स्मृति(len, GFP_ATOMIC);
	अगर (!rsp) अणु
		पढ़ो_unlock(&hci_dev_list_lock);
		वापस -ENOMEM;
	पूर्ण

	rsp->mtu = cpu_to_le16(L2CAP_A2MP_DEFAULT_MTU);
	rsp->ext_feat = 0;

	__a2mp_add_cl(mgr, rsp->cl);

	पढ़ो_unlock(&hci_dev_list_lock);

	a2mp_send(mgr, A2MP_DISCOVER_RSP, hdr->ident, len, rsp);

	kमुक्त(rsp);
	वापस 0;
पूर्ण

अटल पूर्णांक a2mp_discover_rsp(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
			     काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_discov_rsp *rsp = (व्योम *) skb->data;
	u16 len = le16_to_cpu(hdr->len);
	काष्ठा a2mp_cl *cl;
	u16 ext_feat;
	bool found = false;

	अगर (len < माप(*rsp))
		वापस -EINVAL;

	len -= माप(*rsp);
	skb_pull(skb, माप(*rsp));

	ext_feat = le16_to_cpu(rsp->ext_feat);

	BT_DBG("mtu %d efm 0x%4.4x", le16_to_cpu(rsp->mtu), ext_feat);

	/* check that packet is not broken क्रम now */
	जबतक (ext_feat & A2MP_FEAT_EXT) अणु
		अगर (len < माप(ext_feat))
			वापस -EINVAL;

		ext_feat = get_unaligned_le16(skb->data);
		BT_DBG("efm 0x%4.4x", ext_feat);
		len -= माप(ext_feat);
		skb_pull(skb, माप(ext_feat));
	पूर्ण

	cl = (व्योम *) skb->data;
	जबतक (len >= माप(*cl)) अणु
		BT_DBG("Remote AMP id %d type %d status %d", cl->id, cl->type,
		       cl->status);

		अगर (cl->id != AMP_ID_BREDR && cl->type != AMP_TYPE_BREDR) अणु
			काष्ठा a2mp_info_req req;

			found = true;

			स_रखो(&req, 0, माप(req));

			req.id = cl->id;
			a2mp_send(mgr, A2MP_GETINFO_REQ, __next_ident(mgr),
				  माप(req), &req);
		पूर्ण

		len -= माप(*cl);
		cl = skb_pull(skb, माप(*cl));
	पूर्ण

	/* Fall back to L2CAP init sequence */
	अगर (!found) अणु
		काष्ठा l2cap_conn *conn = mgr->l2cap_conn;
		काष्ठा l2cap_chan *chan;

		mutex_lock(&conn->chan_lock);

		list_क्रम_each_entry(chan, &conn->chan_l, list) अणु

			BT_DBG("chan %p state %s", chan,
			       state_to_string(chan->state));

			अगर (chan->scid == L2CAP_CID_A2MP)
				जारी;

			l2cap_chan_lock(chan);

			अगर (chan->state == BT_CONNECT)
				l2cap_send_conn_req(chan);

			l2cap_chan_unlock(chan);
		पूर्ण

		mutex_unlock(&conn->chan_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a2mp_change_notअगरy(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
			      काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_cl *cl = (व्योम *) skb->data;

	जबतक (skb->len >= माप(*cl)) अणु
		BT_DBG("Controller id %d type %d status %d", cl->id, cl->type,
		       cl->status);
		cl = skb_pull(skb, माप(*cl));
	पूर्ण

	/* TODO send A2MP_CHANGE_RSP */

	वापस 0;
पूर्ण

अटल व्योम पढ़ो_local_amp_info_complete(काष्ठा hci_dev *hdev, u8 status,
					 u16 opcode)
अणु
	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	a2mp_send_getinfo_rsp(hdev);
पूर्ण

अटल पूर्णांक a2mp_getinfo_req(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
			    काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_info_req *req  = (व्योम *) skb->data;
	काष्ठा hci_dev *hdev;
	काष्ठा hci_request hreq;
	पूर्णांक err = 0;

	अगर (le16_to_cpu(hdr->len) < माप(*req))
		वापस -EINVAL;

	BT_DBG("id %d", req->id);

	hdev = hci_dev_get(req->id);
	अगर (!hdev || hdev->dev_type != HCI_AMP) अणु
		काष्ठा a2mp_info_rsp rsp;

		स_रखो(&rsp, 0, माप(rsp));

		rsp.id = req->id;
		rsp.status = A2MP_STATUS_INVALID_CTRL_ID;

		a2mp_send(mgr, A2MP_GETINFO_RSP, hdr->ident, माप(rsp),
			  &rsp);

		जाओ करोne;
	पूर्ण

	set_bit(READ_LOC_AMP_INFO, &mgr->state);
	hci_req_init(&hreq, hdev);
	hci_req_add(&hreq, HCI_OP_READ_LOCAL_AMP_INFO, 0, शून्य);
	err = hci_req_run(&hreq, पढ़ो_local_amp_info_complete);
	अगर (err < 0)
		a2mp_send_getinfo_rsp(hdev);

करोne:
	अगर (hdev)
		hci_dev_put(hdev);

	skb_pull(skb, माप(*req));
	वापस 0;
पूर्ण

अटल पूर्णांक a2mp_getinfo_rsp(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
			    काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_info_rsp *rsp = (काष्ठा a2mp_info_rsp *) skb->data;
	काष्ठा a2mp_amp_assoc_req req;
	काष्ठा amp_ctrl *ctrl;

	अगर (le16_to_cpu(hdr->len) < माप(*rsp))
		वापस -EINVAL;

	BT_DBG("id %d status 0x%2.2x", rsp->id, rsp->status);

	अगर (rsp->status)
		वापस -EINVAL;

	ctrl = amp_ctrl_add(mgr, rsp->id);
	अगर (!ctrl)
		वापस -ENOMEM;

	स_रखो(&req, 0, माप(req));

	req.id = rsp->id;
	a2mp_send(mgr, A2MP_GETAMPASSOC_REQ, __next_ident(mgr), माप(req),
		  &req);

	skb_pull(skb, माप(*rsp));
	वापस 0;
पूर्ण

अटल पूर्णांक a2mp_getampassoc_req(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
				काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_amp_assoc_req *req = (व्योम *) skb->data;
	काष्ठा hci_dev *hdev;
	काष्ठा amp_mgr *पंचांगp;

	अगर (le16_to_cpu(hdr->len) < माप(*req))
		वापस -EINVAL;

	BT_DBG("id %d", req->id);

	/* Make sure that other request is not processed */
	पंचांगp = amp_mgr_lookup_by_state(READ_LOC_AMP_ASSOC);

	hdev = hci_dev_get(req->id);
	अगर (!hdev || hdev->amp_type == AMP_TYPE_BREDR || पंचांगp) अणु
		काष्ठा a2mp_amp_assoc_rsp rsp;

		स_रखो(&rsp, 0, माप(rsp));
		rsp.id = req->id;

		अगर (पंचांगp) अणु
			rsp.status = A2MP_STATUS_COLLISION_OCCURED;
			amp_mgr_put(पंचांगp);
		पूर्ण अन्यथा अणु
			rsp.status = A2MP_STATUS_INVALID_CTRL_ID;
		पूर्ण

		a2mp_send(mgr, A2MP_GETAMPASSOC_RSP, hdr->ident, माप(rsp),
			  &rsp);

		जाओ करोne;
	पूर्ण

	amp_पढ़ो_loc_assoc(hdev, mgr);

करोne:
	अगर (hdev)
		hci_dev_put(hdev);

	skb_pull(skb, माप(*req));
	वापस 0;
पूर्ण

अटल पूर्णांक a2mp_getampassoc_rsp(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
				काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_amp_assoc_rsp *rsp = (व्योम *) skb->data;
	u16 len = le16_to_cpu(hdr->len);
	काष्ठा hci_dev *hdev;
	काष्ठा amp_ctrl *ctrl;
	काष्ठा hci_conn *hcon;
	माप_प्रकार assoc_len;

	अगर (len < माप(*rsp))
		वापस -EINVAL;

	assoc_len = len - माप(*rsp);

	BT_DBG("id %d status 0x%2.2x assoc len %zu", rsp->id, rsp->status,
	       assoc_len);

	अगर (rsp->status)
		वापस -EINVAL;

	/* Save remote ASSOC data */
	ctrl = amp_ctrl_lookup(mgr, rsp->id);
	अगर (ctrl) अणु
		u8 *assoc;

		assoc = kmemdup(rsp->amp_assoc, assoc_len, GFP_KERNEL);
		अगर (!assoc) अणु
			amp_ctrl_put(ctrl);
			वापस -ENOMEM;
		पूर्ण

		ctrl->assoc = assoc;
		ctrl->assoc_len = assoc_len;
		ctrl->assoc_rem_len = assoc_len;
		ctrl->assoc_len_so_far = 0;

		amp_ctrl_put(ctrl);
	पूर्ण

	/* Create Phys Link */
	hdev = hci_dev_get(rsp->id);
	अगर (!hdev)
		वापस -EINVAL;

	hcon = phylink_add(hdev, mgr, rsp->id, true);
	अगर (!hcon)
		जाओ करोne;

	BT_DBG("Created hcon %p: loc:%d -> rem:%d", hcon, hdev->id, rsp->id);

	mgr->bredr_chan->remote_amp_id = rsp->id;

	amp_create_phylink(hdev, mgr, hcon);

करोne:
	hci_dev_put(hdev);
	skb_pull(skb, len);
	वापस 0;
पूर्ण

अटल पूर्णांक a2mp_createphyslink_req(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
				   काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_physlink_req *req = (व्योम *) skb->data;
	काष्ठा a2mp_physlink_rsp rsp;
	काष्ठा hci_dev *hdev;
	काष्ठा hci_conn *hcon;
	काष्ठा amp_ctrl *ctrl;

	अगर (le16_to_cpu(hdr->len) < माप(*req))
		वापस -EINVAL;

	BT_DBG("local_id %d, remote_id %d", req->local_id, req->remote_id);

	स_रखो(&rsp, 0, माप(rsp));

	rsp.local_id = req->remote_id;
	rsp.remote_id = req->local_id;

	hdev = hci_dev_get(req->remote_id);
	अगर (!hdev || hdev->amp_type == AMP_TYPE_BREDR) अणु
		rsp.status = A2MP_STATUS_INVALID_CTRL_ID;
		जाओ send_rsp;
	पूर्ण

	ctrl = amp_ctrl_lookup(mgr, rsp.remote_id);
	अगर (!ctrl) अणु
		ctrl = amp_ctrl_add(mgr, rsp.remote_id);
		अगर (ctrl) अणु
			amp_ctrl_get(ctrl);
		पूर्ण अन्यथा अणु
			rsp.status = A2MP_STATUS_UNABLE_START_LINK_CREATION;
			जाओ send_rsp;
		पूर्ण
	पूर्ण

	अगर (ctrl) अणु
		माप_प्रकार assoc_len = le16_to_cpu(hdr->len) - माप(*req);
		u8 *assoc;

		assoc = kmemdup(req->amp_assoc, assoc_len, GFP_KERNEL);
		अगर (!assoc) अणु
			amp_ctrl_put(ctrl);
			hci_dev_put(hdev);
			वापस -ENOMEM;
		पूर्ण

		ctrl->assoc = assoc;
		ctrl->assoc_len = assoc_len;
		ctrl->assoc_rem_len = assoc_len;
		ctrl->assoc_len_so_far = 0;

		amp_ctrl_put(ctrl);
	पूर्ण

	hcon = phylink_add(hdev, mgr, req->local_id, false);
	अगर (hcon) अणु
		amp_accept_phylink(hdev, mgr, hcon);
		rsp.status = A2MP_STATUS_SUCCESS;
	पूर्ण अन्यथा अणु
		rsp.status = A2MP_STATUS_UNABLE_START_LINK_CREATION;
	पूर्ण

send_rsp:
	अगर (hdev)
		hci_dev_put(hdev);

	/* Reply error now and success after HCI Write Remote AMP Assoc
	   command complete with success status
	 */
	अगर (rsp.status != A2MP_STATUS_SUCCESS) अणु
		a2mp_send(mgr, A2MP_CREATEPHYSLINK_RSP, hdr->ident,
			  माप(rsp), &rsp);
	पूर्ण अन्यथा अणु
		set_bit(WRITE_REMOTE_AMP_ASSOC, &mgr->state);
		mgr->ident = hdr->ident;
	पूर्ण

	skb_pull(skb, le16_to_cpu(hdr->len));
	वापस 0;
पूर्ण

अटल पूर्णांक a2mp_discphyslink_req(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
				 काष्ठा a2mp_cmd *hdr)
अणु
	काष्ठा a2mp_physlink_req *req = (व्योम *) skb->data;
	काष्ठा a2mp_physlink_rsp rsp;
	काष्ठा hci_dev *hdev;
	काष्ठा hci_conn *hcon;

	अगर (le16_to_cpu(hdr->len) < माप(*req))
		वापस -EINVAL;

	BT_DBG("local_id %d remote_id %d", req->local_id, req->remote_id);

	स_रखो(&rsp, 0, माप(rsp));

	rsp.local_id = req->remote_id;
	rsp.remote_id = req->local_id;
	rsp.status = A2MP_STATUS_SUCCESS;

	hdev = hci_dev_get(req->remote_id);
	अगर (!hdev) अणु
		rsp.status = A2MP_STATUS_INVALID_CTRL_ID;
		जाओ send_rsp;
	पूर्ण

	hcon = hci_conn_hash_lookup_ba(hdev, AMP_LINK,
				       &mgr->l2cap_conn->hcon->dst);
	अगर (!hcon) अणु
		bt_dev_err(hdev, "no phys link exist");
		rsp.status = A2MP_STATUS_NO_PHYSICAL_LINK_EXISTS;
		जाओ clean;
	पूर्ण

	/* TODO Disconnect Phys Link here */

clean:
	hci_dev_put(hdev);

send_rsp:
	a2mp_send(mgr, A2MP_DISCONNPHYSLINK_RSP, hdr->ident, माप(rsp), &rsp);

	skb_pull(skb, माप(*req));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक a2mp_cmd_rsp(काष्ठा amp_mgr *mgr, काष्ठा sk_buff *skb,
			       काष्ठा a2mp_cmd *hdr)
अणु
	BT_DBG("ident %d code 0x%2.2x", hdr->ident, hdr->code);

	skb_pull(skb, le16_to_cpu(hdr->len));
	वापस 0;
पूर्ण

/* Handle A2MP संकेतling */
अटल पूर्णांक a2mp_chan_recv_cb(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा a2mp_cmd *hdr;
	काष्ठा amp_mgr *mgr = chan->data;
	पूर्णांक err = 0;

	amp_mgr_get(mgr);

	जबतक (skb->len >= माप(*hdr)) अणु
		u16 len;

		hdr = (व्योम *) skb->data;
		len = le16_to_cpu(hdr->len);

		BT_DBG("code 0x%2.2x id %d len %u", hdr->code, hdr->ident, len);

		skb_pull(skb, माप(*hdr));

		अगर (len > skb->len || !hdr->ident) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		mgr->ident = hdr->ident;

		चयन (hdr->code) अणु
		हाल A2MP_COMMAND_REJ:
			a2mp_command_rej(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_DISCOVER_REQ:
			err = a2mp_discover_req(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_CHANGE_NOTIFY:
			err = a2mp_change_notअगरy(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_GETINFO_REQ:
			err = a2mp_getinfo_req(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_GETAMPASSOC_REQ:
			err = a2mp_getampassoc_req(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_CREATEPHYSLINK_REQ:
			err = a2mp_createphyslink_req(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_DISCONNPHYSLINK_REQ:
			err = a2mp_discphyslink_req(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_DISCOVER_RSP:
			err = a2mp_discover_rsp(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_GETINFO_RSP:
			err = a2mp_getinfo_rsp(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_GETAMPASSOC_RSP:
			err = a2mp_getampassoc_rsp(mgr, skb, hdr);
			अवरोध;

		हाल A2MP_CHANGE_RSP:
		हाल A2MP_CREATEPHYSLINK_RSP:
		हाल A2MP_DISCONNPHYSLINK_RSP:
			err = a2mp_cmd_rsp(mgr, skb, hdr);
			अवरोध;

		शेष:
			BT_ERR("Unknown A2MP sig cmd 0x%2.2x", hdr->code);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (err) अणु
		काष्ठा a2mp_cmd_rej rej;

		स_रखो(&rej, 0, माप(rej));

		rej.reason = cpu_to_le16(0);
		hdr = (व्योम *) skb->data;

		BT_DBG("Send A2MP Rej: cmd 0x%2.2x err %d", hdr->code, err);

		a2mp_send(mgr, A2MP_COMMAND_REJ, hdr->ident, माप(rej),
			  &rej);
	पूर्ण

	/* Always मुक्त skb and वापस success error code to prevent
	   from sending L2CAP Disconnect over A2MP channel */
	kमुक्त_skb(skb);

	amp_mgr_put(mgr);

	वापस 0;
पूर्ण

अटल व्योम a2mp_chan_बंद_cb(काष्ठा l2cap_chan *chan)
अणु
	l2cap_chan_put(chan);
पूर्ण

अटल व्योम a2mp_chan_state_change_cb(काष्ठा l2cap_chan *chan, पूर्णांक state,
				      पूर्णांक err)
अणु
	काष्ठा amp_mgr *mgr = chan->data;

	अगर (!mgr)
		वापस;

	BT_DBG("chan %p state %s", chan, state_to_string(state));

	chan->state = state;

	चयन (state) अणु
	हाल BT_CLOSED:
		अगर (mgr)
			amp_mgr_put(mgr);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *a2mp_chan_alloc_skb_cb(काष्ठा l2cap_chan *chan,
					      अचिन्हित दीर्घ hdr_len,
					      अचिन्हित दीर्घ len, पूर्णांक nb)
अणु
	काष्ठा sk_buff *skb;

	skb = bt_skb_alloc(hdr_len + len, GFP_KERNEL);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	वापस skb;
पूर्ण

अटल स्थिर काष्ठा l2cap_ops a2mp_chan_ops = अणु
	.name = "L2CAP A2MP channel",
	.recv = a2mp_chan_recv_cb,
	.बंद = a2mp_chan_बंद_cb,
	.state_change = a2mp_chan_state_change_cb,
	.alloc_skb = a2mp_chan_alloc_skb_cb,

	/* Not implemented क्रम A2MP */
	.new_connection = l2cap_chan_no_new_connection,
	.tearकरोwn = l2cap_chan_no_tearकरोwn,
	.पढ़ोy = l2cap_chan_no_पढ़ोy,
	.defer = l2cap_chan_no_defer,
	.resume = l2cap_chan_no_resume,
	.set_shutकरोwn = l2cap_chan_no_set_shutकरोwn,
	.get_sndसमयo = l2cap_chan_no_get_sndसमयo,
पूर्ण;

अटल काष्ठा l2cap_chan *a2mp_chan_खोलो(काष्ठा l2cap_conn *conn, bool locked)
अणु
	काष्ठा l2cap_chan *chan;
	पूर्णांक err;

	chan = l2cap_chan_create();
	अगर (!chan)
		वापस शून्य;

	BT_DBG("chan %p", chan);

	chan->chan_type = L2CAP_CHAN_FIXED;
	chan->scid = L2CAP_CID_A2MP;
	chan->dcid = L2CAP_CID_A2MP;
	chan->omtu = L2CAP_A2MP_DEFAULT_MTU;
	chan->imtu = L2CAP_A2MP_DEFAULT_MTU;
	chan->flush_to = L2CAP_DEFAULT_FLUSH_TO;

	chan->ops = &a2mp_chan_ops;

	l2cap_chan_set_शेषs(chan);
	chan->remote_max_tx = chan->max_tx;
	chan->remote_tx_win = chan->tx_win;

	chan->retrans_समयout = L2CAP_DEFAULT_RETRANS_TO;
	chan->monitor_समयout = L2CAP_DEFAULT_MONITOR_TO;

	skb_queue_head_init(&chan->tx_q);

	chan->mode = L2CAP_MODE_ERTM;

	err = l2cap_erपंचांग_init(chan);
	अगर (err < 0) अणु
		l2cap_chan_del(chan, 0);
		वापस शून्य;
	पूर्ण

	chan->conf_state = 0;

	अगर (locked)
		__l2cap_chan_add(conn, chan);
	अन्यथा
		l2cap_chan_add(conn, chan);

	chan->remote_mps = chan->omtu;
	chan->mps = chan->omtu;

	chan->state = BT_CONNECTED;

	वापस chan;
पूर्ण

/* AMP Manager functions */
काष्ठा amp_mgr *amp_mgr_get(काष्ठा amp_mgr *mgr)
अणु
	BT_DBG("mgr %p orig refcnt %d", mgr, kref_पढ़ो(&mgr->kref));

	kref_get(&mgr->kref);

	वापस mgr;
पूर्ण

अटल व्योम amp_mgr_destroy(काष्ठा kref *kref)
अणु
	काष्ठा amp_mgr *mgr = container_of(kref, काष्ठा amp_mgr, kref);

	BT_DBG("mgr %p", mgr);

	mutex_lock(&amp_mgr_list_lock);
	list_del(&mgr->list);
	mutex_unlock(&amp_mgr_list_lock);

	amp_ctrl_list_flush(mgr);
	kमुक्त(mgr);
पूर्ण

पूर्णांक amp_mgr_put(काष्ठा amp_mgr *mgr)
अणु
	BT_DBG("mgr %p orig refcnt %d", mgr, kref_पढ़ो(&mgr->kref));

	वापस kref_put(&mgr->kref, &amp_mgr_destroy);
पूर्ण

अटल काष्ठा amp_mgr *amp_mgr_create(काष्ठा l2cap_conn *conn, bool locked)
अणु
	काष्ठा amp_mgr *mgr;
	काष्ठा l2cap_chan *chan;

	mgr = kzalloc(माप(*mgr), GFP_KERNEL);
	अगर (!mgr)
		वापस शून्य;

	BT_DBG("conn %p mgr %p", conn, mgr);

	mgr->l2cap_conn = conn;

	chan = a2mp_chan_खोलो(conn, locked);
	अगर (!chan) अणु
		kमुक्त(mgr);
		वापस शून्य;
	पूर्ण

	mgr->a2mp_chan = chan;
	chan->data = mgr;

	conn->hcon->amp_mgr = mgr;

	kref_init(&mgr->kref);

	/* Remote AMP ctrl list initialization */
	INIT_LIST_HEAD(&mgr->amp_ctrls);
	mutex_init(&mgr->amp_ctrls_lock);

	mutex_lock(&amp_mgr_list_lock);
	list_add(&mgr->list, &amp_mgr_list);
	mutex_unlock(&amp_mgr_list_lock);

	वापस mgr;
पूर्ण

काष्ठा l2cap_chan *a2mp_channel_create(काष्ठा l2cap_conn *conn,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा amp_mgr *mgr;

	अगर (conn->hcon->type != ACL_LINK)
		वापस शून्य;

	mgr = amp_mgr_create(conn, false);
	अगर (!mgr) अणु
		BT_ERR("Could not create AMP manager");
		वापस शून्य;
	पूर्ण

	BT_DBG("mgr: %p chan %p", mgr, mgr->a2mp_chan);

	वापस mgr->a2mp_chan;
पूर्ण

व्योम a2mp_send_getinfo_rsp(काष्ठा hci_dev *hdev)
अणु
	काष्ठा amp_mgr *mgr;
	काष्ठा a2mp_info_rsp rsp;

	mgr = amp_mgr_lookup_by_state(READ_LOC_AMP_INFO);
	अगर (!mgr)
		वापस;

	BT_DBG("%s mgr %p", hdev->name, mgr);

	स_रखो(&rsp, 0, माप(rsp));

	rsp.id = hdev->id;
	rsp.status = A2MP_STATUS_INVALID_CTRL_ID;

	अगर (hdev->amp_type != AMP_TYPE_BREDR) अणु
		rsp.status = 0;
		rsp.total_bw = cpu_to_le32(hdev->amp_total_bw);
		rsp.max_bw = cpu_to_le32(hdev->amp_max_bw);
		rsp.min_latency = cpu_to_le32(hdev->amp_min_latency);
		rsp.pal_cap = cpu_to_le16(hdev->amp_pal_cap);
		rsp.assoc_size = cpu_to_le16(hdev->amp_assoc_size);
	पूर्ण

	a2mp_send(mgr, A2MP_GETINFO_RSP, mgr->ident, माप(rsp), &rsp);
	amp_mgr_put(mgr);
पूर्ण

व्योम a2mp_send_getampassoc_rsp(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा amp_mgr *mgr;
	काष्ठा amp_assoc *loc_assoc = &hdev->loc_assoc;
	काष्ठा a2mp_amp_assoc_rsp *rsp;
	माप_प्रकार len;

	mgr = amp_mgr_lookup_by_state(READ_LOC_AMP_ASSOC);
	अगर (!mgr)
		वापस;

	BT_DBG("%s mgr %p", hdev->name, mgr);

	len = माप(काष्ठा a2mp_amp_assoc_rsp) + loc_assoc->len;
	rsp = kzalloc(len, GFP_KERNEL);
	अगर (!rsp) अणु
		amp_mgr_put(mgr);
		वापस;
	पूर्ण

	rsp->id = hdev->id;

	अगर (status) अणु
		rsp->status = A2MP_STATUS_INVALID_CTRL_ID;
	पूर्ण अन्यथा अणु
		rsp->status = A2MP_STATUS_SUCCESS;
		स_नकल(rsp->amp_assoc, loc_assoc->data, loc_assoc->len);
	पूर्ण

	a2mp_send(mgr, A2MP_GETAMPASSOC_RSP, mgr->ident, len, rsp);
	amp_mgr_put(mgr);
	kमुक्त(rsp);
पूर्ण

व्योम a2mp_send_create_phy_link_req(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा amp_mgr *mgr;
	काष्ठा amp_assoc *loc_assoc = &hdev->loc_assoc;
	काष्ठा a2mp_physlink_req *req;
	काष्ठा l2cap_chan *bredr_chan;
	माप_प्रकार len;

	mgr = amp_mgr_lookup_by_state(READ_LOC_AMP_ASSOC_FINAL);
	अगर (!mgr)
		वापस;

	len = माप(*req) + loc_assoc->len;

	BT_DBG("%s mgr %p assoc_len %zu", hdev->name, mgr, len);

	req = kzalloc(len, GFP_KERNEL);
	अगर (!req) अणु
		amp_mgr_put(mgr);
		वापस;
	पूर्ण

	bredr_chan = mgr->bredr_chan;
	अगर (!bredr_chan)
		जाओ clean;

	req->local_id = hdev->id;
	req->remote_id = bredr_chan->remote_amp_id;
	स_नकल(req->amp_assoc, loc_assoc->data, loc_assoc->len);

	a2mp_send(mgr, A2MP_CREATEPHYSLINK_REQ, __next_ident(mgr), len, req);

clean:
	amp_mgr_put(mgr);
	kमुक्त(req);
पूर्ण

व्योम a2mp_send_create_phy_link_rsp(काष्ठा hci_dev *hdev, u8 status)
अणु
	काष्ठा amp_mgr *mgr;
	काष्ठा a2mp_physlink_rsp rsp;
	काष्ठा hci_conn *hs_hcon;

	mgr = amp_mgr_lookup_by_state(WRITE_REMOTE_AMP_ASSOC);
	अगर (!mgr)
		वापस;

	स_रखो(&rsp, 0, माप(rsp));

	hs_hcon = hci_conn_hash_lookup_state(hdev, AMP_LINK, BT_CONNECT);
	अगर (!hs_hcon) अणु
		rsp.status = A2MP_STATUS_UNABLE_START_LINK_CREATION;
	पूर्ण अन्यथा अणु
		rsp.remote_id = hs_hcon->remote_id;
		rsp.status = A2MP_STATUS_SUCCESS;
	पूर्ण

	BT_DBG("%s mgr %p hs_hcon %p status %u", hdev->name, mgr, hs_hcon,
	       status);

	rsp.local_id = hdev->id;
	a2mp_send(mgr, A2MP_CREATEPHYSLINK_RSP, mgr->ident, माप(rsp), &rsp);
	amp_mgr_put(mgr);
पूर्ण

व्योम a2mp_discover_amp(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा l2cap_conn *conn = chan->conn;
	काष्ठा amp_mgr *mgr = conn->hcon->amp_mgr;
	काष्ठा a2mp_discov_req req;

	BT_DBG("chan %p conn %p mgr %p", chan, conn, mgr);

	अगर (!mgr) अणु
		mgr = amp_mgr_create(conn, true);
		अगर (!mgr)
			वापस;
	पूर्ण

	mgr->bredr_chan = chan;

	स_रखो(&req, 0, माप(req));

	req.mtu = cpu_to_le16(L2CAP_A2MP_DEFAULT_MTU);
	req.ext_feat = 0;
	a2mp_send(mgr, A2MP_DISCOVER_REQ, 1, माप(req), &req);
पूर्ण
