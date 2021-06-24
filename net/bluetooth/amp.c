<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
   Copyright (c) 2011,2012 Intel Corp.

*/

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <crypto/hash.h>

#समावेश "hci_request.h"
#समावेश "a2mp.h"
#समावेश "amp.h"

/* Remote AMP Controllers पूर्णांकerface */
व्योम amp_ctrl_get(काष्ठा amp_ctrl *ctrl)
अणु
	BT_DBG("ctrl %p orig refcnt %d", ctrl,
	       kref_पढ़ो(&ctrl->kref));

	kref_get(&ctrl->kref);
पूर्ण

अटल व्योम amp_ctrl_destroy(काष्ठा kref *kref)
अणु
	काष्ठा amp_ctrl *ctrl = container_of(kref, काष्ठा amp_ctrl, kref);

	BT_DBG("ctrl %p", ctrl);

	kमुक्त(ctrl->assoc);
	kमुक्त(ctrl);
पूर्ण

पूर्णांक amp_ctrl_put(काष्ठा amp_ctrl *ctrl)
अणु
	BT_DBG("ctrl %p orig refcnt %d", ctrl,
	       kref_पढ़ो(&ctrl->kref));

	वापस kref_put(&ctrl->kref, &amp_ctrl_destroy);
पूर्ण

काष्ठा amp_ctrl *amp_ctrl_add(काष्ठा amp_mgr *mgr, u8 id)
अणु
	काष्ठा amp_ctrl *ctrl;

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस शून्य;

	kref_init(&ctrl->kref);
	ctrl->id = id;

	mutex_lock(&mgr->amp_ctrls_lock);
	list_add(&ctrl->list, &mgr->amp_ctrls);
	mutex_unlock(&mgr->amp_ctrls_lock);

	BT_DBG("mgr %p ctrl %p", mgr, ctrl);

	वापस ctrl;
पूर्ण

व्योम amp_ctrl_list_flush(काष्ठा amp_mgr *mgr)
अणु
	काष्ठा amp_ctrl *ctrl, *n;

	BT_DBG("mgr %p", mgr);

	mutex_lock(&mgr->amp_ctrls_lock);
	list_क्रम_each_entry_safe(ctrl, n, &mgr->amp_ctrls, list) अणु
		list_del(&ctrl->list);
		amp_ctrl_put(ctrl);
	पूर्ण
	mutex_unlock(&mgr->amp_ctrls_lock);
पूर्ण

काष्ठा amp_ctrl *amp_ctrl_lookup(काष्ठा amp_mgr *mgr, u8 id)
अणु
	काष्ठा amp_ctrl *ctrl;

	BT_DBG("mgr %p id %d", mgr, id);

	mutex_lock(&mgr->amp_ctrls_lock);
	list_क्रम_each_entry(ctrl, &mgr->amp_ctrls, list) अणु
		अगर (ctrl->id == id) अणु
			amp_ctrl_get(ctrl);
			mutex_unlock(&mgr->amp_ctrls_lock);
			वापस ctrl;
		पूर्ण
	पूर्ण
	mutex_unlock(&mgr->amp_ctrls_lock);

	वापस शून्य;
पूर्ण

/* Physical Link पूर्णांकerface */
अटल u8 __next_handle(काष्ठा amp_mgr *mgr)
अणु
	अगर (++mgr->handle == 0)
		mgr->handle = 1;

	वापस mgr->handle;
पूर्ण

काष्ठा hci_conn *phylink_add(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr,
			     u8 remote_id, bool out)
अणु
	bdaddr_t *dst = &mgr->l2cap_conn->hcon->dst;
	काष्ठा hci_conn *hcon;
	u8 role = out ? HCI_ROLE_MASTER : HCI_ROLE_SLAVE;

	hcon = hci_conn_add(hdev, AMP_LINK, dst, role);
	अगर (!hcon)
		वापस शून्य;

	BT_DBG("hcon %p dst %pMR", hcon, dst);

	hcon->state = BT_CONNECT;
	hcon->attempt++;
	hcon->handle = __next_handle(mgr);
	hcon->remote_id = remote_id;
	hcon->amp_mgr = amp_mgr_get(mgr);

	वापस hcon;
पूर्ण

/* AMP crypto key generation पूर्णांकerface */
अटल पूर्णांक hmac_sha256(u8 *key, u8 ksize, अक्षर *plaपूर्णांकext, u8 psize, u8 *output)
अणु
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *shash;
	पूर्णांक ret;

	अगर (!ksize)
		वापस -EINVAL;

	tfm = crypto_alloc_shash("hmac(sha256)", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		BT_DBG("crypto_alloc_ahash failed: err %ld", PTR_ERR(tfm));
		वापस PTR_ERR(tfm);
	पूर्ण

	ret = crypto_shash_setkey(tfm, key, ksize);
	अगर (ret) अणु
		BT_DBG("crypto_ahash_setkey failed: err %d", ret);
		जाओ failed;
	पूर्ण

	shash = kzalloc(माप(*shash) + crypto_shash_descsize(tfm),
			GFP_KERNEL);
	अगर (!shash) अणु
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	shash->tfm = tfm;

	ret = crypto_shash_digest(shash, plaपूर्णांकext, psize, output);

	kमुक्त(shash);

failed:
	crypto_मुक्त_shash(tfm);
	वापस ret;
पूर्ण

पूर्णांक phylink_gen_key(काष्ठा hci_conn *conn, u8 *data, u8 *len, u8 *type)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा link_key *key;
	u8 keybuf[HCI_AMP_LINK_KEY_SIZE];
	u8 gamp_key[HCI_AMP_LINK_KEY_SIZE];
	पूर्णांक err;

	अगर (!hci_conn_check_link_mode(conn))
		वापस -EACCES;

	BT_DBG("conn %p key_type %d", conn, conn->key_type);

	/* Legacy key */
	अगर (conn->key_type < 3) अणु
		bt_dev_err(hdev, "legacy key type %d", conn->key_type);
		वापस -EACCES;
	पूर्ण

	*type = conn->key_type;
	*len = HCI_AMP_LINK_KEY_SIZE;

	key = hci_find_link_key(hdev, &conn->dst);
	अगर (!key) अणु
		BT_DBG("No Link key for conn %p dst %pMR", conn, &conn->dst);
		वापस -EACCES;
	पूर्ण

	/* BR/EDR Link Key concatenated together with itself */
	स_नकल(&keybuf[0], key->val, HCI_LINK_KEY_SIZE);
	स_नकल(&keybuf[HCI_LINK_KEY_SIZE], key->val, HCI_LINK_KEY_SIZE);

	/* Derive Generic AMP Link Key (gamp) */
	err = hmac_sha256(keybuf, HCI_AMP_LINK_KEY_SIZE, "gamp", 4, gamp_key);
	अगर (err) अणु
		bt_dev_err(hdev, "could not derive Generic AMP Key: err %d", err);
		वापस err;
	पूर्ण

	अगर (conn->key_type == HCI_LK_DEBUG_COMBINATION) अणु
		BT_DBG("Use Generic AMP Key (gamp)");
		स_नकल(data, gamp_key, HCI_AMP_LINK_KEY_SIZE);
		वापस err;
	पूर्ण

	/* Derive Dedicated AMP Link Key: "802b" is 802.11 PAL keyID */
	वापस hmac_sha256(gamp_key, HCI_AMP_LINK_KEY_SIZE, "802b", 4, data);
पूर्ण

अटल व्योम पढ़ो_local_amp_assoc_complete(काष्ठा hci_dev *hdev, u8 status,
					  u16 opcode, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_पढ़ो_local_amp_assoc *rp = (व्योम *)skb->data;
	काष्ठा amp_assoc *assoc = &hdev->loc_assoc;
	माप_प्रकार rem_len, frag_len;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	अगर (rp->status)
		जाओ send_rsp;

	frag_len = skb->len - माप(*rp);
	rem_len = __le16_to_cpu(rp->rem_len);

	अगर (rem_len > frag_len) अणु
		BT_DBG("frag_len %zu rem_len %zu", frag_len, rem_len);

		स_नकल(assoc->data + assoc->offset, rp->frag, frag_len);
		assoc->offset += frag_len;

		/* Read other fragments */
		amp_पढ़ो_loc_assoc_frag(hdev, rp->phy_handle);

		वापस;
	पूर्ण

	स_नकल(assoc->data + assoc->offset, rp->frag, rem_len);
	assoc->len = assoc->offset + rem_len;
	assoc->offset = 0;

send_rsp:
	/* Send A2MP Rsp when all fragments are received */
	a2mp_send_getampassoc_rsp(hdev, rp->status);
	a2mp_send_create_phy_link_req(hdev, rp->status);
पूर्ण

व्योम amp_पढ़ो_loc_assoc_frag(काष्ठा hci_dev *hdev, u8 phy_handle)
अणु
	काष्ठा hci_cp_पढ़ो_local_amp_assoc cp;
	काष्ठा amp_assoc *loc_assoc = &hdev->loc_assoc;
	काष्ठा hci_request req;
	पूर्णांक err;

	BT_DBG("%s handle %d", hdev->name, phy_handle);

	cp.phy_handle = phy_handle;
	cp.max_len = cpu_to_le16(hdev->amp_assoc_size);
	cp.len_so_far = cpu_to_le16(loc_assoc->offset);

	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_READ_LOCAL_AMP_ASSOC, माप(cp), &cp);
	err = hci_req_run_skb(&req, पढ़ो_local_amp_assoc_complete);
	अगर (err < 0)
		a2mp_send_getampassoc_rsp(hdev, A2MP_STATUS_INVALID_CTRL_ID);
पूर्ण

व्योम amp_पढ़ो_loc_assoc(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr)
अणु
	काष्ठा hci_cp_पढ़ो_local_amp_assoc cp;
	काष्ठा hci_request req;
	पूर्णांक err;

	स_रखो(&hdev->loc_assoc, 0, माप(काष्ठा amp_assoc));
	स_रखो(&cp, 0, माप(cp));

	cp.max_len = cpu_to_le16(hdev->amp_assoc_size);

	set_bit(READ_LOC_AMP_ASSOC, &mgr->state);
	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_READ_LOCAL_AMP_ASSOC, माप(cp), &cp);
	err = hci_req_run_skb(&req, पढ़ो_local_amp_assoc_complete);
	अगर (err < 0)
		a2mp_send_getampassoc_rsp(hdev, A2MP_STATUS_INVALID_CTRL_ID);
पूर्ण

व्योम amp_पढ़ो_loc_assoc_final_data(काष्ठा hci_dev *hdev,
				   काष्ठा hci_conn *hcon)
अणु
	काष्ठा hci_cp_पढ़ो_local_amp_assoc cp;
	काष्ठा amp_mgr *mgr = hcon->amp_mgr;
	काष्ठा hci_request req;
	पूर्णांक err;

	अगर (!mgr)
		वापस;

	cp.phy_handle = hcon->handle;
	cp.len_so_far = cpu_to_le16(0);
	cp.max_len = cpu_to_le16(hdev->amp_assoc_size);

	set_bit(READ_LOC_AMP_ASSOC_FINAL, &mgr->state);

	/* Read Local AMP Assoc final link inक्रमmation data */
	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_READ_LOCAL_AMP_ASSOC, माप(cp), &cp);
	err = hci_req_run_skb(&req, पढ़ो_local_amp_assoc_complete);
	अगर (err < 0)
		a2mp_send_getampassoc_rsp(hdev, A2MP_STATUS_INVALID_CTRL_ID);
पूर्ण

अटल व्योम ग_लिखो_remote_amp_assoc_complete(काष्ठा hci_dev *hdev, u8 status,
					    u16 opcode, काष्ठा sk_buff *skb)
अणु
	काष्ठा hci_rp_ग_लिखो_remote_amp_assoc *rp = (व्योम *)skb->data;

	BT_DBG("%s status 0x%2.2x phy_handle 0x%2.2x",
	       hdev->name, rp->status, rp->phy_handle);

	अगर (rp->status)
		वापस;

	amp_ग_लिखो_rem_assoc_जारी(hdev, rp->phy_handle);
पूर्ण

/* Write AMP Assoc data fragments, वापसs true with last fragment written*/
अटल bool amp_ग_लिखो_rem_assoc_frag(काष्ठा hci_dev *hdev,
				     काष्ठा hci_conn *hcon)
अणु
	काष्ठा hci_cp_ग_लिखो_remote_amp_assoc *cp;
	काष्ठा amp_mgr *mgr = hcon->amp_mgr;
	काष्ठा amp_ctrl *ctrl;
	काष्ठा hci_request req;
	u16 frag_len, len;

	ctrl = amp_ctrl_lookup(mgr, hcon->remote_id);
	अगर (!ctrl)
		वापस false;

	अगर (!ctrl->assoc_rem_len) अणु
		BT_DBG("all fragments are written");
		ctrl->assoc_rem_len = ctrl->assoc_len;
		ctrl->assoc_len_so_far = 0;

		amp_ctrl_put(ctrl);
		वापस true;
	पूर्ण

	frag_len = min_t(u16, 248, ctrl->assoc_rem_len);
	len = frag_len + माप(*cp);

	cp = kzalloc(len, GFP_KERNEL);
	अगर (!cp) अणु
		amp_ctrl_put(ctrl);
		वापस false;
	पूर्ण

	BT_DBG("hcon %p ctrl %p frag_len %u assoc_len %u rem_len %u",
	       hcon, ctrl, frag_len, ctrl->assoc_len, ctrl->assoc_rem_len);

	cp->phy_handle = hcon->handle;
	cp->len_so_far = cpu_to_le16(ctrl->assoc_len_so_far);
	cp->rem_len = cpu_to_le16(ctrl->assoc_rem_len);
	स_नकल(cp->frag, ctrl->assoc, frag_len);

	ctrl->assoc_len_so_far += frag_len;
	ctrl->assoc_rem_len -= frag_len;

	amp_ctrl_put(ctrl);

	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_WRITE_REMOTE_AMP_ASSOC, len, cp);
	hci_req_run_skb(&req, ग_लिखो_remote_amp_assoc_complete);

	kमुक्त(cp);

	वापस false;
पूर्ण

व्योम amp_ग_लिखो_rem_assoc_जारी(काष्ठा hci_dev *hdev, u8 handle)
अणु
	काष्ठा hci_conn *hcon;

	BT_DBG("%s phy handle 0x%2.2x", hdev->name, handle);

	hcon = hci_conn_hash_lookup_handle(hdev, handle);
	अगर (!hcon)
		वापस;

	/* Send A2MP create phylink rsp when all fragments are written */
	अगर (amp_ग_लिखो_rem_assoc_frag(hdev, hcon))
		a2mp_send_create_phy_link_rsp(hdev, 0);
पूर्ण

व्योम amp_ग_लिखो_remote_assoc(काष्ठा hci_dev *hdev, u8 handle)
अणु
	काष्ठा hci_conn *hcon;

	BT_DBG("%s phy handle 0x%2.2x", hdev->name, handle);

	hcon = hci_conn_hash_lookup_handle(hdev, handle);
	अगर (!hcon)
		वापस;

	BT_DBG("%s phy handle 0x%2.2x hcon %p", hdev->name, handle, hcon);

	amp_ग_लिखो_rem_assoc_frag(hdev, hcon);
पूर्ण

अटल व्योम create_phylink_complete(काष्ठा hci_dev *hdev, u8 status,
				    u16 opcode)
अणु
	काष्ठा hci_cp_create_phy_link *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	cp = hci_sent_cmd_data(hdev, HCI_OP_CREATE_PHY_LINK);
	अगर (!cp)
		वापस;

	hci_dev_lock(hdev);

	अगर (status) अणु
		काष्ठा hci_conn *hcon;

		hcon = hci_conn_hash_lookup_handle(hdev, cp->phy_handle);
		अगर (hcon)
			hci_conn_del(hcon);
	पूर्ण अन्यथा अणु
		amp_ग_लिखो_remote_assoc(hdev, cp->phy_handle);
	पूर्ण

	hci_dev_unlock(hdev);
पूर्ण

व्योम amp_create_phylink(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr,
			काष्ठा hci_conn *hcon)
अणु
	काष्ठा hci_cp_create_phy_link cp;
	काष्ठा hci_request req;

	cp.phy_handle = hcon->handle;

	BT_DBG("%s hcon %p phy handle 0x%2.2x", hdev->name, hcon,
	       hcon->handle);

	अगर (phylink_gen_key(mgr->l2cap_conn->hcon, cp.key, &cp.key_len,
			    &cp.key_type)) अणु
		BT_DBG("Cannot create link key");
		वापस;
	पूर्ण

	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_CREATE_PHY_LINK, माप(cp), &cp);
	hci_req_run(&req, create_phylink_complete);
पूर्ण

अटल व्योम accept_phylink_complete(काष्ठा hci_dev *hdev, u8 status,
				    u16 opcode)
अणु
	काष्ठा hci_cp_accept_phy_link *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	अगर (status)
		वापस;

	cp = hci_sent_cmd_data(hdev, HCI_OP_ACCEPT_PHY_LINK);
	अगर (!cp)
		वापस;

	amp_ग_लिखो_remote_assoc(hdev, cp->phy_handle);
पूर्ण

व्योम amp_accept_phylink(काष्ठा hci_dev *hdev, काष्ठा amp_mgr *mgr,
			काष्ठा hci_conn *hcon)
अणु
	काष्ठा hci_cp_accept_phy_link cp;
	काष्ठा hci_request req;

	cp.phy_handle = hcon->handle;

	BT_DBG("%s hcon %p phy handle 0x%2.2x", hdev->name, hcon,
	       hcon->handle);

	अगर (phylink_gen_key(mgr->l2cap_conn->hcon, cp.key, &cp.key_len,
			    &cp.key_type)) अणु
		BT_DBG("Cannot create link key");
		वापस;
	पूर्ण

	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_ACCEPT_PHY_LINK, माप(cp), &cp);
	hci_req_run(&req, accept_phylink_complete);
पूर्ण

व्योम amp_physical_cfm(काष्ठा hci_conn *bredr_hcon, काष्ठा hci_conn *hs_hcon)
अणु
	काष्ठा hci_dev *bredr_hdev = hci_dev_hold(bredr_hcon->hdev);
	काष्ठा amp_mgr *mgr = hs_hcon->amp_mgr;
	काष्ठा l2cap_chan *bredr_chan;

	BT_DBG("bredr_hcon %p hs_hcon %p mgr %p", bredr_hcon, hs_hcon, mgr);

	अगर (!bredr_hdev || !mgr || !mgr->bredr_chan)
		वापस;

	bredr_chan = mgr->bredr_chan;

	l2cap_chan_lock(bredr_chan);

	set_bit(FLAG_EFS_ENABLE, &bredr_chan->flags);
	bredr_chan->remote_amp_id = hs_hcon->remote_id;
	bredr_chan->local_amp_id = hs_hcon->hdev->id;
	bredr_chan->hs_hcon = hs_hcon;
	bredr_chan->conn->mtu = hs_hcon->hdev->block_mtu;

	__l2cap_physical_cfm(bredr_chan, 0);

	l2cap_chan_unlock(bredr_chan);

	hci_dev_put(bredr_hdev);
पूर्ण

व्योम amp_create_logical_link(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा hci_conn *hs_hcon = chan->hs_hcon;
	काष्ठा hci_cp_create_accept_logical_link cp;
	काष्ठा hci_dev *hdev;

	BT_DBG("chan %p hs_hcon %p dst %pMR", chan, hs_hcon,
	       &chan->conn->hcon->dst);

	अगर (!hs_hcon)
		वापस;

	hdev = hci_dev_hold(chan->hs_hcon->hdev);
	अगर (!hdev)
		वापस;

	cp.phy_handle = hs_hcon->handle;

	cp.tx_flow_spec.id = chan->local_id;
	cp.tx_flow_spec.stype = chan->local_stype;
	cp.tx_flow_spec.msdu = cpu_to_le16(chan->local_msdu);
	cp.tx_flow_spec.sdu_iसमय = cpu_to_le32(chan->local_sdu_iसमय);
	cp.tx_flow_spec.acc_lat = cpu_to_le32(chan->local_acc_lat);
	cp.tx_flow_spec.flush_to = cpu_to_le32(chan->local_flush_to);

	cp.rx_flow_spec.id = chan->remote_id;
	cp.rx_flow_spec.stype = chan->remote_stype;
	cp.rx_flow_spec.msdu = cpu_to_le16(chan->remote_msdu);
	cp.rx_flow_spec.sdu_iसमय = cpu_to_le32(chan->remote_sdu_iसमय);
	cp.rx_flow_spec.acc_lat = cpu_to_le32(chan->remote_acc_lat);
	cp.rx_flow_spec.flush_to = cpu_to_le32(chan->remote_flush_to);

	अगर (hs_hcon->out)
		hci_send_cmd(hdev, HCI_OP_CREATE_LOGICAL_LINK, माप(cp),
			     &cp);
	अन्यथा
		hci_send_cmd(hdev, HCI_OP_ACCEPT_LOGICAL_LINK, माप(cp),
			     &cp);

	hci_dev_put(hdev);
पूर्ण

व्योम amp_disconnect_logical_link(काष्ठा hci_chan *hchan)
अणु
	काष्ठा hci_conn *hcon = hchan->conn;
	काष्ठा hci_cp_disconn_logical_link cp;

	अगर (hcon->state != BT_CONNECTED) अणु
		BT_DBG("hchan %p not connected", hchan);
		वापस;
	पूर्ण

	cp.log_handle = cpu_to_le16(hchan->handle);
	hci_send_cmd(hcon->hdev, HCI_OP_DISCONN_LOGICAL_LINK, माप(cp), &cp);
पूर्ण

व्योम amp_destroy_logical_link(काष्ठा hci_chan *hchan, u8 reason)
अणु
	BT_DBG("hchan %p", hchan);

	hci_chan_del(hchan);
पूर्ण
