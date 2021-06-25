<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (c) 2000-2001, 2010, Code Aurora Forum. All rights reserved.

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

/* Bluetooth HCI connection handling. */

#समावेश <linux/export.h>
#समावेश <linux/debugfs.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>

#समावेश "hci_request.h"
#समावेश "smp.h"
#समावेश "a2mp.h"

काष्ठा sco_param अणु
	u16 pkt_type;
	u16 max_latency;
	u8  retrans_efक्रमt;
पूर्ण;

अटल स्थिर काष्ठा sco_param esco_param_cvsd[] = अणु
	अणु EDR_ESCO_MASK & ~ESCO_2EV3, 0x000a,	0x01 पूर्ण, /* S3 */
	अणु EDR_ESCO_MASK & ~ESCO_2EV3, 0x0007,	0x01 पूर्ण, /* S2 */
	अणु EDR_ESCO_MASK | ESCO_EV3,   0x0007,	0x01 पूर्ण, /* S1 */
	अणु EDR_ESCO_MASK | ESCO_HV3,   0xffff,	0x01 पूर्ण, /* D1 */
	अणु EDR_ESCO_MASK | ESCO_HV1,   0xffff,	0x01 पूर्ण, /* D0 */
पूर्ण;

अटल स्थिर काष्ठा sco_param sco_param_cvsd[] = अणु
	अणु EDR_ESCO_MASK | ESCO_HV3,   0xffff,	0xff पूर्ण, /* D1 */
	अणु EDR_ESCO_MASK | ESCO_HV1,   0xffff,	0xff पूर्ण, /* D0 */
पूर्ण;

अटल स्थिर काष्ठा sco_param esco_param_msbc[] = अणु
	अणु EDR_ESCO_MASK & ~ESCO_2EV3, 0x000d,	0x02 पूर्ण, /* T2 */
	अणु EDR_ESCO_MASK | ESCO_EV3,   0x0008,	0x02 पूर्ण, /* T1 */
पूर्ण;

/* This function requires the caller holds hdev->lock */
अटल व्योम hci_connect_le_scan_cleanup(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_conn_params *params;
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा smp_irk *irk;
	bdaddr_t *bdaddr;
	u8 bdaddr_type;

	bdaddr = &conn->dst;
	bdaddr_type = conn->dst_type;

	/* Check अगर we need to convert to identity address */
	irk = hci_get_irk(hdev, bdaddr, bdaddr_type);
	अगर (irk) अणु
		bdaddr = &irk->bdaddr;
		bdaddr_type = irk->addr_type;
	पूर्ण

	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, bdaddr,
					   bdaddr_type);
	अगर (!params || !params->explicit_connect)
		वापस;

	/* The connection attempt was करोing scan क्रम new RPA, and is
	 * in scan phase. If params are not associated with any other
	 * स्वतःconnect action, हटाओ them completely. If they are, just unmark
	 * them as रुकोing क्रम connection, by clearing explicit_connect field.
	 */
	params->explicit_connect = false;

	list_del_init(&params->action);

	चयन (params->स्वतः_connect) अणु
	हाल HCI_AUTO_CONN_EXPLICIT:
		hci_conn_params_del(hdev, bdaddr, bdaddr_type);
		/* वापस instead of अवरोध to aव्योम duplicate scan update */
		वापस;
	हाल HCI_AUTO_CONN_सूचीECT:
	हाल HCI_AUTO_CONN_ALWAYS:
		list_add(&params->action, &hdev->pend_le_conns);
		अवरोध;
	हाल HCI_AUTO_CONN_REPORT:
		list_add(&params->action, &hdev->pend_le_reports);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	hci_update_background_scan(hdev);
पूर्ण

अटल व्योम hci_conn_cleanup(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	अगर (test_bit(HCI_CONN_PARAM_REMOVAL_PEND, &conn->flags))
		hci_conn_params_del(conn->hdev, &conn->dst, conn->dst_type);

	hci_chan_list_flush(conn);

	hci_conn_hash_del(hdev, conn);

	अगर (conn->type == SCO_LINK || conn->type == ESCO_LINK) अणु
		चयन (conn->setting & SCO_AIRMODE_MASK) अणु
		हाल SCO_AIRMODE_CVSD:
		हाल SCO_AIRMODE_TRANSP:
			अगर (hdev->notअगरy)
				hdev->notअगरy(hdev, HCI_NOTIFY_DISABLE_SCO);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hdev->notअगरy)
			hdev->notअगरy(hdev, HCI_NOTIFY_CONN_DEL);
	पूर्ण

	hci_conn_del_sysfs(conn);

	debugfs_हटाओ_recursive(conn->debugfs);

	hci_dev_put(hdev);

	hci_conn_put(conn);
पूर्ण

अटल व्योम le_scan_cleanup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_conn *conn = container_of(work, काष्ठा hci_conn,
					     le_scan_cleanup);
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा hci_conn *c = शून्य;

	BT_DBG("%s hcon %p", hdev->name, conn);

	hci_dev_lock(hdev);

	/* Check that the hci_conn is still around */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(c, &hdev->conn_hash.list, list) अणु
		अगर (c == conn)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (c == conn) अणु
		hci_connect_le_scan_cleanup(conn);
		hci_conn_cleanup(conn);
	पूर्ण

	hci_dev_unlock(hdev);
	hci_dev_put(hdev);
	hci_conn_put(conn);
पूर्ण

अटल व्योम hci_connect_le_scan_हटाओ(काष्ठा hci_conn *conn)
अणु
	BT_DBG("%s hcon %p", conn->hdev->name, conn);

	/* We can't call hci_conn_del/hci_conn_cleanup here since that
	 * could deadlock with another hci_conn_del() call that's holding
	 * hci_dev_lock and करोing cancel_delayed_work_sync(&conn->disc_work).
	 * Instead, grab temporary extra references to the hci_dev and
	 * hci_conn and perक्रमm the necessary cleanup in a separate work
	 * callback.
	 */

	hci_dev_hold(conn->hdev);
	hci_conn_get(conn);

	/* Even though we hold a reference to the hdev, many other
	 * things might get cleaned up meanजबतक, including the hdev's
	 * own workqueue, so we can't use that क्रम scheduling.
	 */
	schedule_work(&conn->le_scan_cleanup);
पूर्ण

अटल व्योम hci_acl_create_connection(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा inquiry_entry *ie;
	काष्ठा hci_cp_create_conn cp;

	BT_DBG("hcon %p", conn);

	/* Many controllers disallow HCI Create Connection जबतक it is करोing
	 * HCI Inquiry. So we cancel the Inquiry first beक्रमe issuing HCI Create
	 * Connection. This may cause the MGMT discovering state to become false
	 * without user space's request but it is okay since the MGMT Discovery
	 * APIs करो not promise that discovery should be करोne क्रमever. Instead,
	 * the user space monitors the status of MGMT discovering and it may
	 * request क्रम discovery again when this flag becomes false.
	 */
	अगर (test_bit(HCI_INQUIRY, &hdev->flags)) अणु
		/* Put this connection to "pending" state so that it will be
		 * executed after the inquiry cancel command complete event.
		 */
		conn->state = BT_CONNECT2;
		hci_send_cmd(hdev, HCI_OP_INQUIRY_CANCEL, 0, शून्य);
		वापस;
	पूर्ण

	conn->state = BT_CONNECT;
	conn->out = true;
	conn->role = HCI_ROLE_MASTER;

	conn->attempt++;

	conn->link_policy = hdev->link_policy;

	स_रखो(&cp, 0, माप(cp));
	bacpy(&cp.bdaddr, &conn->dst);
	cp.pscan_rep_mode = 0x02;

	ie = hci_inquiry_cache_lookup(hdev, &conn->dst);
	अगर (ie) अणु
		अगर (inquiry_entry_age(ie) <= INQUIRY_ENTRY_AGE_MAX) अणु
			cp.pscan_rep_mode = ie->data.pscan_rep_mode;
			cp.pscan_mode     = ie->data.pscan_mode;
			cp.घड़ी_offset   = ie->data.घड़ी_offset |
					    cpu_to_le16(0x8000);
		पूर्ण

		स_नकल(conn->dev_class, ie->data.dev_class, 3);
	पूर्ण

	cp.pkt_type = cpu_to_le16(conn->pkt_type);
	अगर (lmp_rचयन_capable(hdev) && !(hdev->link_mode & HCI_LM_MASTER))
		cp.role_चयन = 0x01;
	अन्यथा
		cp.role_चयन = 0x00;

	hci_send_cmd(hdev, HCI_OP_CREATE_CONN, माप(cp), &cp);
पूर्ण

पूर्णांक hci_disconnect(काष्ठा hci_conn *conn, __u8 reason)
अणु
	BT_DBG("hcon %p", conn);

	/* When we are master of an established connection and it enters
	 * the disconnect समयout, then go ahead and try to पढ़ो the
	 * current घड़ी offset.  Processing of the result is करोne
	 * within the event handling and hci_घड़ी_offset_evt function.
	 */
	अगर (conn->type == ACL_LINK && conn->role == HCI_ROLE_MASTER &&
	    (conn->state == BT_CONNECTED || conn->state == BT_CONFIG)) अणु
		काष्ठा hci_dev *hdev = conn->hdev;
		काष्ठा hci_cp_पढ़ो_घड़ी_offset clkoff_cp;

		clkoff_cp.handle = cpu_to_le16(conn->handle);
		hci_send_cmd(hdev, HCI_OP_READ_CLOCK_OFFSET, माप(clkoff_cp),
			     &clkoff_cp);
	पूर्ण

	वापस hci_पात_conn(conn, reason);
पूर्ण

अटल व्योम hci_add_sco(काष्ठा hci_conn *conn, __u16 handle)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा hci_cp_add_sco cp;

	BT_DBG("hcon %p", conn);

	conn->state = BT_CONNECT;
	conn->out = true;

	conn->attempt++;

	cp.handle   = cpu_to_le16(handle);
	cp.pkt_type = cpu_to_le16(conn->pkt_type);

	hci_send_cmd(hdev, HCI_OP_ADD_SCO, माप(cp), &cp);
पूर्ण

अटल bool find_next_esco_param(काष्ठा hci_conn *conn,
				 स्थिर काष्ठा sco_param *esco_param, पूर्णांक size)
अणु
	क्रम (; conn->attempt <= size; conn->attempt++) अणु
		अगर (lmp_esco_2m_capable(conn->link) ||
		    (esco_param[conn->attempt - 1].pkt_type & ESCO_2EV3))
			अवरोध;
		BT_DBG("hcon %p skipped attempt %d, eSCO 2M not supported",
		       conn, conn->attempt);
	पूर्ण

	वापस conn->attempt <= size;
पूर्ण

bool hci_setup_sync(काष्ठा hci_conn *conn, __u16 handle)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा hci_cp_setup_sync_conn cp;
	स्थिर काष्ठा sco_param *param;

	BT_DBG("hcon %p", conn);

	conn->state = BT_CONNECT;
	conn->out = true;

	conn->attempt++;

	cp.handle   = cpu_to_le16(handle);

	cp.tx_bandwidth   = cpu_to_le32(0x00001f40);
	cp.rx_bandwidth   = cpu_to_le32(0x00001f40);
	cp.voice_setting  = cpu_to_le16(conn->setting);

	चयन (conn->setting & SCO_AIRMODE_MASK) अणु
	हाल SCO_AIRMODE_TRANSP:
		अगर (!find_next_esco_param(conn, esco_param_msbc,
					  ARRAY_SIZE(esco_param_msbc)))
			वापस false;
		param = &esco_param_msbc[conn->attempt - 1];
		अवरोध;
	हाल SCO_AIRMODE_CVSD:
		अगर (lmp_esco_capable(conn->link)) अणु
			अगर (!find_next_esco_param(conn, esco_param_cvsd,
						  ARRAY_SIZE(esco_param_cvsd)))
				वापस false;
			param = &esco_param_cvsd[conn->attempt - 1];
		पूर्ण अन्यथा अणु
			अगर (conn->attempt > ARRAY_SIZE(sco_param_cvsd))
				वापस false;
			param = &sco_param_cvsd[conn->attempt - 1];
		पूर्ण
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	cp.retrans_efक्रमt = param->retrans_efक्रमt;
	cp.pkt_type = __cpu_to_le16(param->pkt_type);
	cp.max_latency = __cpu_to_le16(param->max_latency);

	अगर (hci_send_cmd(hdev, HCI_OP_SETUP_SYNC_CONN, माप(cp), &cp) < 0)
		वापस false;

	वापस true;
पूर्ण

u8 hci_le_conn_update(काष्ठा hci_conn *conn, u16 min, u16 max, u16 latency,
		      u16 to_multiplier)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा hci_conn_params *params;
	काष्ठा hci_cp_le_conn_update cp;

	hci_dev_lock(hdev);

	params = hci_conn_params_lookup(hdev, &conn->dst, conn->dst_type);
	अगर (params) अणु
		params->conn_min_पूर्णांकerval = min;
		params->conn_max_पूर्णांकerval = max;
		params->conn_latency = latency;
		params->supervision_समयout = to_multiplier;
	पूर्ण

	hci_dev_unlock(hdev);

	स_रखो(&cp, 0, माप(cp));
	cp.handle		= cpu_to_le16(conn->handle);
	cp.conn_पूर्णांकerval_min	= cpu_to_le16(min);
	cp.conn_पूर्णांकerval_max	= cpu_to_le16(max);
	cp.conn_latency		= cpu_to_le16(latency);
	cp.supervision_समयout	= cpu_to_le16(to_multiplier);
	cp.min_ce_len		= cpu_to_le16(0x0000);
	cp.max_ce_len		= cpu_to_le16(0x0000);

	hci_send_cmd(hdev, HCI_OP_LE_CONN_UPDATE, माप(cp), &cp);

	अगर (params)
		वापस 0x01;

	वापस 0x00;
पूर्ण

व्योम hci_le_start_enc(काष्ठा hci_conn *conn, __le16 eभाग, __le64 अक्रम,
		      __u8 ltk[16], __u8 key_size)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा hci_cp_le_start_enc cp;

	BT_DBG("hcon %p", conn);

	स_रखो(&cp, 0, माप(cp));

	cp.handle = cpu_to_le16(conn->handle);
	cp.अक्रम = अक्रम;
	cp.eभाग = eभाग;
	स_नकल(cp.ltk, ltk, key_size);

	hci_send_cmd(hdev, HCI_OP_LE_START_ENC, माप(cp), &cp);
पूर्ण

/* Device _must_ be locked */
व्योम hci_sco_setup(काष्ठा hci_conn *conn, __u8 status)
अणु
	काष्ठा hci_conn *sco = conn->link;

	अगर (!sco)
		वापस;

	BT_DBG("hcon %p", conn);

	अगर (!status) अणु
		अगर (lmp_esco_capable(conn->hdev))
			hci_setup_sync(sco, conn->handle);
		अन्यथा
			hci_add_sco(sco, conn->handle);
	पूर्ण अन्यथा अणु
		hci_connect_cfm(sco, status);
		hci_conn_del(sco);
	पूर्ण
पूर्ण

अटल व्योम hci_conn_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_conn *conn = container_of(work, काष्ठा hci_conn,
					     disc_work.work);
	पूर्णांक refcnt = atomic_पढ़ो(&conn->refcnt);

	BT_DBG("hcon %p state %s", conn, state_to_string(conn->state));

	WARN_ON(refcnt < 0);

	/* FIXME: It was observed that in pairing failed scenario, refcnt
	 * drops below 0. Probably this is because l2cap_conn_del calls
	 * l2cap_chan_del क्रम each channel, and inside l2cap_chan_del conn is
	 * dropped. After that loop hci_chan_del is called which also drops
	 * conn. For now make sure that ACL is alive अगर refcnt is higher then 0,
	 * otherwise drop it.
	 */
	अगर (refcnt > 0)
		वापस;

	/* LE connections in scanning state need special handling */
	अगर (conn->state == BT_CONNECT && conn->type == LE_LINK &&
	    test_bit(HCI_CONN_SCANNING, &conn->flags)) अणु
		hci_connect_le_scan_हटाओ(conn);
		वापस;
	पूर्ण

	hci_पात_conn(conn, hci_proto_disconn_ind(conn));
पूर्ण

/* Enter snअगरf mode */
अटल व्योम hci_conn_idle(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_conn *conn = container_of(work, काष्ठा hci_conn,
					     idle_work.work);
	काष्ठा hci_dev *hdev = conn->hdev;

	BT_DBG("hcon %p mode %d", conn, conn->mode);

	अगर (!lmp_snअगरf_capable(hdev) || !lmp_snअगरf_capable(conn))
		वापस;

	अगर (conn->mode != HCI_CM_ACTIVE || !(conn->link_policy & HCI_LP_SNIFF))
		वापस;

	अगर (lmp_snअगरfsubr_capable(hdev) && lmp_snअगरfsubr_capable(conn)) अणु
		काष्ठा hci_cp_snअगरf_subrate cp;
		cp.handle             = cpu_to_le16(conn->handle);
		cp.max_latency        = cpu_to_le16(0);
		cp.min_remote_समयout = cpu_to_le16(0);
		cp.min_local_समयout  = cpu_to_le16(0);
		hci_send_cmd(hdev, HCI_OP_SNIFF_SUBRATE, माप(cp), &cp);
	पूर्ण

	अगर (!test_and_set_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->flags)) अणु
		काष्ठा hci_cp_snअगरf_mode cp;
		cp.handle       = cpu_to_le16(conn->handle);
		cp.max_पूर्णांकerval = cpu_to_le16(hdev->snअगरf_max_पूर्णांकerval);
		cp.min_पूर्णांकerval = cpu_to_le16(hdev->snअगरf_min_पूर्णांकerval);
		cp.attempt      = cpu_to_le16(4);
		cp.समयout      = cpu_to_le16(1);
		hci_send_cmd(hdev, HCI_OP_SNIFF_MODE, माप(cp), &cp);
	पूर्ण
पूर्ण

अटल व्योम hci_conn_स्वतः_accept(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_conn *conn = container_of(work, काष्ठा hci_conn,
					     स्वतः_accept_work.work);

	hci_send_cmd(conn->hdev, HCI_OP_USER_CONFIRM_REPLY, माप(conn->dst),
		     &conn->dst);
पूर्ण

अटल व्योम le_disable_advertising(काष्ठा hci_dev *hdev)
अणु
	अगर (ext_adv_capable(hdev)) अणु
		काष्ठा hci_cp_le_set_ext_adv_enable cp;

		cp.enable = 0x00;
		cp.num_of_sets = 0x00;

		hci_send_cmd(hdev, HCI_OP_LE_SET_EXT_ADV_ENABLE, माप(cp),
			     &cp);
	पूर्ण अन्यथा अणु
		u8 enable = 0x00;
		hci_send_cmd(hdev, HCI_OP_LE_SET_ADV_ENABLE, माप(enable),
			     &enable);
	पूर्ण
पूर्ण

अटल व्योम le_conn_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hci_conn *conn = container_of(work, काष्ठा hci_conn,
					     le_conn_समयout.work);
	काष्ठा hci_dev *hdev = conn->hdev;

	BT_DBG("");

	/* We could end up here due to having करोne directed advertising,
	 * so clean up the state अगर necessary. This should however only
	 * happen with broken hardware or अगर low duty cycle was used
	 * (which करोesn't have a समयout of its own).
	 */
	अगर (conn->role == HCI_ROLE_SLAVE) अणु
		/* Disable LE Advertising */
		le_disable_advertising(hdev);
		hci_le_conn_failed(conn, HCI_ERROR_ADVERTISING_TIMEOUT);
		वापस;
	पूर्ण

	hci_पात_conn(conn, HCI_ERROR_REMOTE_USER_TERM);
पूर्ण

काष्ठा hci_conn *hci_conn_add(काष्ठा hci_dev *hdev, पूर्णांक type, bdaddr_t *dst,
			      u8 role)
अणु
	काष्ठा hci_conn *conn;

	BT_DBG("%s dst %pMR", hdev->name, dst);

	conn = kzalloc(माप(*conn), GFP_KERNEL);
	अगर (!conn)
		वापस शून्य;

	bacpy(&conn->dst, dst);
	bacpy(&conn->src, &hdev->bdaddr);
	conn->hdev  = hdev;
	conn->type  = type;
	conn->role  = role;
	conn->mode  = HCI_CM_ACTIVE;
	conn->state = BT_OPEN;
	conn->auth_type = HCI_AT_GENERAL_BONDING;
	conn->io_capability = hdev->io_capability;
	conn->remote_auth = 0xff;
	conn->key_type = 0xff;
	conn->rssi = HCI_RSSI_INVALID;
	conn->tx_घातer = HCI_TX_POWER_INVALID;
	conn->max_tx_घातer = HCI_TX_POWER_INVALID;

	set_bit(HCI_CONN_POWER_SAVE, &conn->flags);
	conn->disc_समयout = HCI_DISCONN_TIMEOUT;

	/* Set Default Authenticated payload समयout to 30s */
	conn->auth_payload_समयout = DEFAULT_AUTH_PAYLOAD_TIMEOUT;

	अगर (conn->role == HCI_ROLE_MASTER)
		conn->out = true;

	चयन (type) अणु
	हाल ACL_LINK:
		conn->pkt_type = hdev->pkt_type & ACL_PTYPE_MASK;
		अवरोध;
	हाल LE_LINK:
		/* conn->src should reflect the local identity address */
		hci_copy_identity_address(hdev, &conn->src, &conn->src_type);
		अवरोध;
	हाल SCO_LINK:
		अगर (lmp_esco_capable(hdev))
			conn->pkt_type = (hdev->esco_type & SCO_ESCO_MASK) |
					(hdev->esco_type & EDR_ESCO_MASK);
		अन्यथा
			conn->pkt_type = hdev->pkt_type & SCO_PTYPE_MASK;
		अवरोध;
	हाल ESCO_LINK:
		conn->pkt_type = hdev->esco_type & ~EDR_ESCO_MASK;
		अवरोध;
	पूर्ण

	skb_queue_head_init(&conn->data_q);

	INIT_LIST_HEAD(&conn->chan_list);

	INIT_DELAYED_WORK(&conn->disc_work, hci_conn_समयout);
	INIT_DELAYED_WORK(&conn->स्वतः_accept_work, hci_conn_स्वतः_accept);
	INIT_DELAYED_WORK(&conn->idle_work, hci_conn_idle);
	INIT_DELAYED_WORK(&conn->le_conn_समयout, le_conn_समयout);
	INIT_WORK(&conn->le_scan_cleanup, le_scan_cleanup);

	atomic_set(&conn->refcnt, 0);

	hci_dev_hold(hdev);

	hci_conn_hash_add(hdev, conn);

	/* The SCO and eSCO connections will only be notअगरied when their
	 * setup has been completed. This is dअगरferent to ACL links which
	 * can be notअगरied right away.
	 */
	अगर (conn->type != SCO_LINK && conn->type != ESCO_LINK) अणु
		अगर (hdev->notअगरy)
			hdev->notअगरy(hdev, HCI_NOTIFY_CONN_ADD);
	पूर्ण

	hci_conn_init_sysfs(conn);

	वापस conn;
पूर्ण

पूर्णांक hci_conn_del(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	BT_DBG("%s hcon %p handle %d", hdev->name, conn, conn->handle);

	cancel_delayed_work_sync(&conn->disc_work);
	cancel_delayed_work_sync(&conn->स्वतः_accept_work);
	cancel_delayed_work_sync(&conn->idle_work);

	अगर (conn->type == ACL_LINK) अणु
		काष्ठा hci_conn *sco = conn->link;
		अगर (sco)
			sco->link = शून्य;

		/* Unacked frames */
		hdev->acl_cnt += conn->sent;
	पूर्ण अन्यथा अगर (conn->type == LE_LINK) अणु
		cancel_delayed_work(&conn->le_conn_समयout);

		अगर (hdev->le_pkts)
			hdev->le_cnt += conn->sent;
		अन्यथा
			hdev->acl_cnt += conn->sent;
	पूर्ण अन्यथा अणु
		काष्ठा hci_conn *acl = conn->link;
		अगर (acl) अणु
			acl->link = शून्य;
			hci_conn_drop(acl);
		पूर्ण
	पूर्ण

	अगर (conn->amp_mgr)
		amp_mgr_put(conn->amp_mgr);

	skb_queue_purge(&conn->data_q);

	/* Remove the connection from the list and cleanup its reमुख्यing
	 * state. This is a separate function since क्रम some हालs like
	 * BT_CONNECT_SCAN we *only* want the cleanup part without the
	 * rest of hci_conn_del.
	 */
	hci_conn_cleanup(conn);

	वापस 0;
पूर्ण

काष्ठा hci_dev *hci_get_route(bdaddr_t *dst, bdaddr_t *src, uपूर्णांक8_t src_type)
अणु
	पूर्णांक use_src = bacmp(src, BDADDR_ANY);
	काष्ठा hci_dev *hdev = शून्य, *d;

	BT_DBG("%pMR -> %pMR", src, dst);

	पढ़ो_lock(&hci_dev_list_lock);

	list_क्रम_each_entry(d, &hci_dev_list, list) अणु
		अगर (!test_bit(HCI_UP, &d->flags) ||
		    hci_dev_test_flag(d, HCI_USER_CHANNEL) ||
		    d->dev_type != HCI_PRIMARY)
			जारी;

		/* Simple routing:
		 *   No source address - find पूर्णांकerface with bdaddr != dst
		 *   Source address    - find पूर्णांकerface with bdaddr == src
		 */

		अगर (use_src) अणु
			bdaddr_t id_addr;
			u8 id_addr_type;

			अगर (src_type == BDADDR_BREDR) अणु
				अगर (!lmp_bredr_capable(d))
					जारी;
				bacpy(&id_addr, &d->bdaddr);
				id_addr_type = BDADDR_BREDR;
			पूर्ण अन्यथा अणु
				अगर (!lmp_le_capable(d))
					जारी;

				hci_copy_identity_address(d, &id_addr,
							  &id_addr_type);

				/* Convert from HCI to three-value type */
				अगर (id_addr_type == ADDR_LE_DEV_PUBLIC)
					id_addr_type = BDADDR_LE_PUBLIC;
				अन्यथा
					id_addr_type = BDADDR_LE_RANDOM;
			पूर्ण

			अगर (!bacmp(&id_addr, src) && id_addr_type == src_type) अणु
				hdev = d; अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bacmp(&d->bdaddr, dst)) अणु
				hdev = d; अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (hdev)
		hdev = hci_dev_hold(hdev);

	पढ़ो_unlock(&hci_dev_list_lock);
	वापस hdev;
पूर्ण
EXPORT_SYMBOL(hci_get_route);

/* This function requires the caller holds hdev->lock */
व्योम hci_le_conn_failed(काष्ठा hci_conn *conn, u8 status)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा hci_conn_params *params;

	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, &conn->dst,
					   conn->dst_type);
	अगर (params && params->conn) अणु
		hci_conn_drop(params->conn);
		hci_conn_put(params->conn);
		params->conn = शून्य;
	पूर्ण

	conn->state = BT_CLOSED;

	/* If the status indicates successful cancellation of
	 * the attempt (i.e. Unkown Connection Id) there's no poपूर्णांक of
	 * notअगरying failure since we'll go back to keep trying to
	 * connect. The only exception is explicit connect requests
	 * where a समयout + cancel करोes indicate an actual failure.
	 */
	अगर (status != HCI_ERROR_UNKNOWN_CONN_ID ||
	    (params && params->explicit_connect))
		mgmt_connect_failed(hdev, &conn->dst, conn->type,
				    conn->dst_type, status);

	hci_connect_cfm(conn, status);

	hci_conn_del(conn);

	/* The suspend notअगरier is रुकोing क्रम all devices to disconnect and an
	 * LE connect cancel will result in an hci_le_conn_failed. Once the last
	 * connection is deleted, we should also wake the suspend queue to
	 * complete suspend operations.
	 */
	अगर (list_empty(&hdev->conn_hash.list) &&
	    test_and_clear_bit(SUSPEND_DISCONNECTING, hdev->suspend_tasks)) अणु
		wake_up(&hdev->suspend_रुको_q);
	पूर्ण

	/* Since we may have temporarily stopped the background scanning in
	 * favor of connection establishment, we should restart it.
	 */
	hci_update_background_scan(hdev);

	/* Re-enable advertising in हाल this was a failed connection
	 * attempt as a peripheral.
	 */
	hci_req_reenable_advertising(hdev);
पूर्ण

अटल व्योम create_le_conn_complete(काष्ठा hci_dev *hdev, u8 status, u16 opcode)
अणु
	काष्ठा hci_conn *conn;

	hci_dev_lock(hdev);

	conn = hci_lookup_le_connect(hdev);

	अगर (hdev->adv_instance_cnt)
		hci_req_resume_adv_instances(hdev);

	अगर (!status) अणु
		hci_connect_le_scan_cleanup(conn);
		जाओ करोne;
	पूर्ण

	bt_dev_err(hdev, "request failed to create LE connection: "
		   "status 0x%2.2x", status);

	अगर (!conn)
		जाओ करोne;

	hci_le_conn_failed(conn, status);

करोne:
	hci_dev_unlock(hdev);
पूर्ण

अटल bool conn_use_rpa(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	वापस hci_dev_test_flag(hdev, HCI_PRIVACY);
पूर्ण

अटल व्योम set_ext_conn_params(काष्ठा hci_conn *conn,
				काष्ठा hci_cp_le_ext_conn_param *p)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	स_रखो(p, 0, माप(*p));

	p->scan_पूर्णांकerval = cpu_to_le16(hdev->le_scan_पूर्णांक_connect);
	p->scan_winकरोw = cpu_to_le16(hdev->le_scan_winकरोw_connect);
	p->conn_पूर्णांकerval_min = cpu_to_le16(conn->le_conn_min_पूर्णांकerval);
	p->conn_पूर्णांकerval_max = cpu_to_le16(conn->le_conn_max_पूर्णांकerval);
	p->conn_latency = cpu_to_le16(conn->le_conn_latency);
	p->supervision_समयout = cpu_to_le16(conn->le_supv_समयout);
	p->min_ce_len = cpu_to_le16(0x0000);
	p->max_ce_len = cpu_to_le16(0x0000);
पूर्ण

अटल व्योम hci_req_add_le_create_conn(काष्ठा hci_request *req,
				       काष्ठा hci_conn *conn,
				       bdaddr_t *direct_rpa)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	u8 own_addr_type;

	/* If direct address was provided we use it instead of current
	 * address.
	 */
	अगर (direct_rpa) अणु
		अगर (bacmp(&req->hdev->अक्रमom_addr, direct_rpa))
			hci_req_add(req, HCI_OP_LE_SET_RANDOM_ADDR, 6,
								direct_rpa);

		/* direct address is always RPA */
		own_addr_type = ADDR_LE_DEV_RANDOM;
	पूर्ण अन्यथा अणु
		/* Update अक्रमom address, but set require_privacy to false so
		 * that we never connect with an non-resolvable address.
		 */
		अगर (hci_update_अक्रमom_address(req, false, conn_use_rpa(conn),
					      &own_addr_type))
			वापस;
	पूर्ण

	अगर (use_ext_conn(hdev)) अणु
		काष्ठा hci_cp_le_ext_create_conn *cp;
		काष्ठा hci_cp_le_ext_conn_param *p;
		u8 data[माप(*cp) + माप(*p) * 3];
		u32 plen;

		cp = (व्योम *) data;
		p = (व्योम *) cp->data;

		स_रखो(cp, 0, माप(*cp));

		bacpy(&cp->peer_addr, &conn->dst);
		cp->peer_addr_type = conn->dst_type;
		cp->own_addr_type = own_addr_type;

		plen = माप(*cp);

		अगर (scan_1m(hdev)) अणु
			cp->phys |= LE_SCAN_PHY_1M;
			set_ext_conn_params(conn, p);

			p++;
			plen += माप(*p);
		पूर्ण

		अगर (scan_2m(hdev)) अणु
			cp->phys |= LE_SCAN_PHY_2M;
			set_ext_conn_params(conn, p);

			p++;
			plen += माप(*p);
		पूर्ण

		अगर (scan_coded(hdev)) अणु
			cp->phys |= LE_SCAN_PHY_CODED;
			set_ext_conn_params(conn, p);

			plen += माप(*p);
		पूर्ण

		hci_req_add(req, HCI_OP_LE_EXT_CREATE_CONN, plen, data);

	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_le_create_conn cp;

		स_रखो(&cp, 0, माप(cp));

		cp.scan_पूर्णांकerval = cpu_to_le16(hdev->le_scan_पूर्णांक_connect);
		cp.scan_winकरोw = cpu_to_le16(hdev->le_scan_winकरोw_connect);

		bacpy(&cp.peer_addr, &conn->dst);
		cp.peer_addr_type = conn->dst_type;
		cp.own_address_type = own_addr_type;
		cp.conn_पूर्णांकerval_min = cpu_to_le16(conn->le_conn_min_पूर्णांकerval);
		cp.conn_पूर्णांकerval_max = cpu_to_le16(conn->le_conn_max_पूर्णांकerval);
		cp.conn_latency = cpu_to_le16(conn->le_conn_latency);
		cp.supervision_समयout = cpu_to_le16(conn->le_supv_समयout);
		cp.min_ce_len = cpu_to_le16(0x0000);
		cp.max_ce_len = cpu_to_le16(0x0000);

		hci_req_add(req, HCI_OP_LE_CREATE_CONN, माप(cp), &cp);
	पूर्ण

	conn->state = BT_CONNECT;
	clear_bit(HCI_CONN_SCANNING, &conn->flags);
पूर्ण

अटल व्योम hci_req_directed_advertising(काष्ठा hci_request *req,
					 काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = req->hdev;
	u8 own_addr_type;
	u8 enable;

	अगर (ext_adv_capable(hdev)) अणु
		काष्ठा hci_cp_le_set_ext_adv_params cp;
		bdaddr_t अक्रमom_addr;

		/* Set require_privacy to false so that the remote device has a
		 * chance of identअगरying us.
		 */
		अगर (hci_get_अक्रमom_address(hdev, false, conn_use_rpa(conn), शून्य,
					   &own_addr_type, &अक्रमom_addr) < 0)
			वापस;

		स_रखो(&cp, 0, माप(cp));

		cp.evt_properties = cpu_to_le16(LE_LEGACY_ADV_सूचीECT_IND);
		cp.own_addr_type = own_addr_type;
		cp.channel_map = hdev->le_adv_channel_map;
		cp.tx_घातer = HCI_TX_POWER_INVALID;
		cp.primary_phy = HCI_ADV_PHY_1M;
		cp.secondary_phy = HCI_ADV_PHY_1M;
		cp.handle = 0; /* Use instance 0 क्रम directed adv */
		cp.own_addr_type = own_addr_type;
		cp.peer_addr_type = conn->dst_type;
		bacpy(&cp.peer_addr, &conn->dst);

		/* As per Core Spec 5.2 Vol 2, PART E, Sec 7.8.53, क्रम
		 * advertising_event_property LE_LEGACY_ADV_सूचीECT_IND
		 * करोes not supports advertising data when the advertising set alपढ़ोy
		 * contains some, the controller shall वापस erroc code 'Invalid
		 * HCI Command Parameters(0x12).
		 * So it is required to हटाओ adv set क्रम handle 0x00. since we use
		 * instance 0 क्रम directed adv.
		 */
		__hci_req_हटाओ_ext_adv_instance(req, cp.handle);

		hci_req_add(req, HCI_OP_LE_SET_EXT_ADV_PARAMS, माप(cp), &cp);

		अगर (own_addr_type == ADDR_LE_DEV_RANDOM &&
		    bacmp(&अक्रमom_addr, BDADDR_ANY) &&
		    bacmp(&अक्रमom_addr, &hdev->अक्रमom_addr)) अणु
			काष्ठा hci_cp_le_set_adv_set_अक्रम_addr cp;

			स_रखो(&cp, 0, माप(cp));

			cp.handle = 0;
			bacpy(&cp.bdaddr, &अक्रमom_addr);

			hci_req_add(req,
				    HCI_OP_LE_SET_ADV_SET_RAND_ADDR,
				    माप(cp), &cp);
		पूर्ण

		__hci_req_enable_ext_advertising(req, 0x00);
	पूर्ण अन्यथा अणु
		काष्ठा hci_cp_le_set_adv_param cp;

		/* Clear the HCI_LE_ADV bit temporarily so that the
		 * hci_update_अक्रमom_address knows that it's safe to go ahead
		 * and ग_लिखो a new अक्रमom address. The flag will be set back on
		 * as soon as the SET_ADV_ENABLE HCI command completes.
		 */
		hci_dev_clear_flag(hdev, HCI_LE_ADV);

		/* Set require_privacy to false so that the remote device has a
		 * chance of identअगरying us.
		 */
		अगर (hci_update_अक्रमom_address(req, false, conn_use_rpa(conn),
					      &own_addr_type) < 0)
			वापस;

		स_रखो(&cp, 0, माप(cp));

		/* Some controllers might reject command अगर पूर्णांकervals are not
		 * within range क्रम undirected advertising.
		 * BCM20702A0 is known to be affected by this.
		 */
		cp.min_पूर्णांकerval = cpu_to_le16(0x0020);
		cp.max_पूर्णांकerval = cpu_to_le16(0x0020);

		cp.type = LE_ADV_सूचीECT_IND;
		cp.own_address_type = own_addr_type;
		cp.direct_addr_type = conn->dst_type;
		bacpy(&cp.direct_addr, &conn->dst);
		cp.channel_map = hdev->le_adv_channel_map;

		hci_req_add(req, HCI_OP_LE_SET_ADV_PARAM, माप(cp), &cp);

		enable = 0x01;
		hci_req_add(req, HCI_OP_LE_SET_ADV_ENABLE, माप(enable),
			    &enable);
	पूर्ण

	conn->state = BT_CONNECT;
पूर्ण

काष्ठा hci_conn *hci_connect_le(काष्ठा hci_dev *hdev, bdaddr_t *dst,
				u8 dst_type, u8 sec_level, u16 conn_समयout,
				u8 role, bdaddr_t *direct_rpa)
अणु
	काष्ठा hci_conn_params *params;
	काष्ठा hci_conn *conn;
	काष्ठा smp_irk *irk;
	काष्ठा hci_request req;
	पूर्णांक err;

	/* This ensures that during disable le_scan address resolution
	 * will not be disabled अगर it is followed by le_create_conn
	 */
	bool rpa_le_conn = true;

	/* Let's make sure that le is enabled.*/
	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED)) अणु
		अगर (lmp_le_capable(hdev))
			वापस ERR_PTR(-ECONNREFUSED);

		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	/* Since the controller supports only one LE connection attempt at a
	 * समय, we वापस -EBUSY अगर there is any connection attempt running.
	 */
	अगर (hci_lookup_le_connect(hdev))
		वापस ERR_PTR(-EBUSY);

	/* If there's already a connection object but it's not in
	 * scanning state it means it must alपढ़ोy be established, in
	 * which हाल we can't करो anything अन्यथा except report a failure
	 * to connect.
	 */
	conn = hci_conn_hash_lookup_le(hdev, dst, dst_type);
	अगर (conn && !test_bit(HCI_CONN_SCANNING, &conn->flags)) अणु
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	/* When given an identity address with existing identity
	 * resolving key, the connection needs to be established
	 * to a resolvable अक्रमom address.
	 *
	 * Storing the resolvable अक्रमom address is required here
	 * to handle connection failures. The address will later
	 * be resolved back पूर्णांकo the original identity address
	 * from the connect request.
	 */
	irk = hci_find_irk_by_addr(hdev, dst, dst_type);
	अगर (irk && bacmp(&irk->rpa, BDADDR_ANY)) अणु
		dst = &irk->rpa;
		dst_type = ADDR_LE_DEV_RANDOM;
	पूर्ण

	अगर (conn) अणु
		bacpy(&conn->dst, dst);
	पूर्ण अन्यथा अणु
		conn = hci_conn_add(hdev, LE_LINK, dst, role);
		अगर (!conn)
			वापस ERR_PTR(-ENOMEM);
		hci_conn_hold(conn);
		conn->pending_sec_level = sec_level;
	पूर्ण

	conn->dst_type = dst_type;
	conn->sec_level = BT_SECURITY_LOW;
	conn->conn_समयout = conn_समयout;

	hci_req_init(&req, hdev);

	/* Disable advertising अगर we're active. For master role
	 * connections most controllers will refuse to connect अगर
	 * advertising is enabled, and क्रम slave role connections we
	 * anyway have to disable it in order to start directed
	 * advertising. Any रेजिस्टरed advertisements will be
	 * re-enabled after the connection attempt is finished.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_LE_ADV))
		__hci_req_छोड़ो_adv_instances(&req);

	/* If requested to connect as slave use directed advertising */
	अगर (conn->role == HCI_ROLE_SLAVE) अणु
		/* If we're active scanning most controllers are unable
		 * to initiate advertising. Simply reject the attempt.
		 */
		अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN) &&
		    hdev->le_scan_type == LE_SCAN_ACTIVE) अणु
			hci_req_purge(&req);
			hci_conn_del(conn);
			वापस ERR_PTR(-EBUSY);
		पूर्ण

		hci_req_directed_advertising(&req, conn);
		जाओ create_conn;
	पूर्ण

	params = hci_conn_params_lookup(hdev, &conn->dst, conn->dst_type);
	अगर (params) अणु
		conn->le_conn_min_पूर्णांकerval = params->conn_min_पूर्णांकerval;
		conn->le_conn_max_पूर्णांकerval = params->conn_max_पूर्णांकerval;
		conn->le_conn_latency = params->conn_latency;
		conn->le_supv_समयout = params->supervision_समयout;
	पूर्ण अन्यथा अणु
		conn->le_conn_min_पूर्णांकerval = hdev->le_conn_min_पूर्णांकerval;
		conn->le_conn_max_पूर्णांकerval = hdev->le_conn_max_पूर्णांकerval;
		conn->le_conn_latency = hdev->le_conn_latency;
		conn->le_supv_समयout = hdev->le_supv_समयout;
	पूर्ण

	/* If controller is scanning, we stop it since some controllers are
	 * not able to scan and connect at the same समय. Also set the
	 * HCI_LE_SCAN_INTERRUPTED flag so that the command complete
	 * handler क्रम scan disabling knows to set the correct discovery
	 * state.
	 */
	अगर (hci_dev_test_flag(hdev, HCI_LE_SCAN)) अणु
		hci_req_add_le_scan_disable(&req, rpa_le_conn);
		hci_dev_set_flag(hdev, HCI_LE_SCAN_INTERRUPTED);
	पूर्ण

	hci_req_add_le_create_conn(&req, conn, direct_rpa);

create_conn:
	err = hci_req_run(&req, create_le_conn_complete);
	अगर (err) अणु
		hci_conn_del(conn);

		अगर (hdev->adv_instance_cnt)
			hci_req_resume_adv_instances(hdev);

		वापस ERR_PTR(err);
	पूर्ण

	वापस conn;
पूर्ण

अटल bool is_connected(काष्ठा hci_dev *hdev, bdaddr_t *addr, u8 type)
अणु
	काष्ठा hci_conn *conn;

	conn = hci_conn_hash_lookup_le(hdev, addr, type);
	अगर (!conn)
		वापस false;

	अगर (conn->state != BT_CONNECTED)
		वापस false;

	वापस true;
पूर्ण

/* This function requires the caller holds hdev->lock */
अटल पूर्णांक hci_explicit_conn_params_set(काष्ठा hci_dev *hdev,
					bdaddr_t *addr, u8 addr_type)
अणु
	काष्ठा hci_conn_params *params;

	अगर (is_connected(hdev, addr, addr_type))
		वापस -EISCONN;

	params = hci_conn_params_lookup(hdev, addr, addr_type);
	अगर (!params) अणु
		params = hci_conn_params_add(hdev, addr, addr_type);
		अगर (!params)
			वापस -ENOMEM;

		/* If we created new params, mark them to be deleted in
		 * hci_connect_le_scan_cleanup. It's dअगरferent हाल than
		 * existing disabled params, those will stay after cleanup.
		 */
		params->स्वतः_connect = HCI_AUTO_CONN_EXPLICIT;
	पूर्ण

	/* We're trying to connect, so make sure params are at pend_le_conns */
	अगर (params->स्वतः_connect == HCI_AUTO_CONN_DISABLED ||
	    params->स्वतः_connect == HCI_AUTO_CONN_REPORT ||
	    params->स्वतः_connect == HCI_AUTO_CONN_EXPLICIT) अणु
		list_del_init(&params->action);
		list_add(&params->action, &hdev->pend_le_conns);
	पूर्ण

	params->explicit_connect = true;

	BT_DBG("addr %pMR (type %u) auto_connect %u", addr, addr_type,
	       params->स्वतः_connect);

	वापस 0;
पूर्ण

/* This function requires the caller holds hdev->lock */
काष्ठा hci_conn *hci_connect_le_scan(काष्ठा hci_dev *hdev, bdaddr_t *dst,
				     u8 dst_type, u8 sec_level,
				     u16 conn_समयout,
				     क्रमागत conn_reasons conn_reason)
अणु
	काष्ठा hci_conn *conn;

	/* Let's make sure that le is enabled.*/
	अगर (!hci_dev_test_flag(hdev, HCI_LE_ENABLED)) अणु
		अगर (lmp_le_capable(hdev))
			वापस ERR_PTR(-ECONNREFUSED);

		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	/* Some devices send ATT messages as soon as the physical link is
	 * established. To be able to handle these ATT messages, the user-
	 * space first establishes the connection and then starts the pairing
	 * process.
	 *
	 * So अगर a hci_conn object alपढ़ोy exists क्रम the following connection
	 * attempt, we simply update pending_sec_level and auth_type fields
	 * and वापस the object found.
	 */
	conn = hci_conn_hash_lookup_le(hdev, dst, dst_type);
	अगर (conn) अणु
		अगर (conn->pending_sec_level < sec_level)
			conn->pending_sec_level = sec_level;
		जाओ करोne;
	पूर्ण

	BT_DBG("requesting refresh of dst_addr");

	conn = hci_conn_add(hdev, LE_LINK, dst, HCI_ROLE_MASTER);
	अगर (!conn)
		वापस ERR_PTR(-ENOMEM);

	अगर (hci_explicit_conn_params_set(hdev, dst, dst_type) < 0) अणु
		hci_conn_del(conn);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	conn->state = BT_CONNECT;
	set_bit(HCI_CONN_SCANNING, &conn->flags);
	conn->dst_type = dst_type;
	conn->sec_level = BT_SECURITY_LOW;
	conn->pending_sec_level = sec_level;
	conn->conn_समयout = conn_समयout;
	conn->conn_reason = conn_reason;

	hci_update_background_scan(hdev);

करोne:
	hci_conn_hold(conn);
	वापस conn;
पूर्ण

काष्ठा hci_conn *hci_connect_acl(काष्ठा hci_dev *hdev, bdaddr_t *dst,
				 u8 sec_level, u8 auth_type,
				 क्रमागत conn_reasons conn_reason)
अणु
	काष्ठा hci_conn *acl;

	अगर (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) अणु
		अगर (lmp_bredr_capable(hdev))
			वापस ERR_PTR(-ECONNREFUSED);

		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	acl = hci_conn_hash_lookup_ba(hdev, ACL_LINK, dst);
	अगर (!acl) अणु
		acl = hci_conn_add(hdev, ACL_LINK, dst, HCI_ROLE_MASTER);
		अगर (!acl)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	hci_conn_hold(acl);

	acl->conn_reason = conn_reason;
	अगर (acl->state == BT_OPEN || acl->state == BT_CLOSED) अणु
		acl->sec_level = BT_SECURITY_LOW;
		acl->pending_sec_level = sec_level;
		acl->auth_type = auth_type;
		hci_acl_create_connection(acl);
	पूर्ण

	वापस acl;
पूर्ण

काष्ठा hci_conn *hci_connect_sco(काष्ठा hci_dev *hdev, पूर्णांक type, bdaddr_t *dst,
				 __u16 setting)
अणु
	काष्ठा hci_conn *acl;
	काष्ठा hci_conn *sco;

	acl = hci_connect_acl(hdev, dst, BT_SECURITY_LOW, HCI_AT_NO_BONDING,
			      CONN_REASON_SCO_CONNECT);
	अगर (IS_ERR(acl))
		वापस acl;

	sco = hci_conn_hash_lookup_ba(hdev, type, dst);
	अगर (!sco) अणु
		sco = hci_conn_add(hdev, type, dst, HCI_ROLE_MASTER);
		अगर (!sco) अणु
			hci_conn_drop(acl);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	acl->link = sco;
	sco->link = acl;

	hci_conn_hold(sco);

	sco->setting = setting;

	अगर (acl->state == BT_CONNECTED &&
	    (sco->state == BT_OPEN || sco->state == BT_CLOSED)) अणु
		set_bit(HCI_CONN_POWER_SAVE, &acl->flags);
		hci_conn_enter_active_mode(acl, BT_POWER_FORCE_ACTIVE_ON);

		अगर (test_bit(HCI_CONN_MODE_CHANGE_PEND, &acl->flags)) अणु
			/* defer SCO setup until mode change completed */
			set_bit(HCI_CONN_SCO_SETUP_PEND, &acl->flags);
			वापस sco;
		पूर्ण

		hci_sco_setup(acl, 0x00);
	पूर्ण

	वापस sco;
पूर्ण

/* Check link security requirement */
पूर्णांक hci_conn_check_link_mode(काष्ठा hci_conn *conn)
अणु
	BT_DBG("hcon %p", conn);

	/* In Secure Connections Only mode, it is required that Secure
	 * Connections is used and the link is encrypted with AES-CCM
	 * using a P-256 authenticated combination key.
	 */
	अगर (hci_dev_test_flag(conn->hdev, HCI_SC_ONLY)) अणु
		अगर (!hci_conn_sc_enabled(conn) ||
		    !test_bit(HCI_CONN_AES_CCM, &conn->flags) ||
		    conn->key_type != HCI_LK_AUTH_COMBINATION_P256)
			वापस 0;
	पूर्ण

	 /* AES encryption is required क्रम Level 4:
	  *
	  * BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 3, Part C
	  * page 1319:
	  *
	  * 128-bit equivalent strength क्रम link and encryption keys
	  * required using FIPS approved algorithms (E0 not allowed,
	  * SAFER+ not allowed, and P-192 not allowed; encryption key
	  * not लघुened)
	  */
	अगर (conn->sec_level == BT_SECURITY_FIPS &&
	    !test_bit(HCI_CONN_AES_CCM, &conn->flags)) अणु
		bt_dev_err(conn->hdev,
			   "Invalid security: Missing AES-CCM usage");
		वापस 0;
	पूर्ण

	अगर (hci_conn_ssp_enabled(conn) &&
	    !test_bit(HCI_CONN_ENCRYPT, &conn->flags))
		वापस 0;

	वापस 1;
पूर्ण

/* Authenticate remote device */
अटल पूर्णांक hci_conn_auth(काष्ठा hci_conn *conn, __u8 sec_level, __u8 auth_type)
अणु
	BT_DBG("hcon %p", conn);

	अगर (conn->pending_sec_level > sec_level)
		sec_level = conn->pending_sec_level;

	अगर (sec_level > conn->sec_level)
		conn->pending_sec_level = sec_level;
	अन्यथा अगर (test_bit(HCI_CONN_AUTH, &conn->flags))
		वापस 1;

	/* Make sure we preserve an existing MITM requirement*/
	auth_type |= (conn->auth_type & 0x01);

	conn->auth_type = auth_type;

	अगर (!test_and_set_bit(HCI_CONN_AUTH_PEND, &conn->flags)) अणु
		काष्ठा hci_cp_auth_requested cp;

		cp.handle = cpu_to_le16(conn->handle);
		hci_send_cmd(conn->hdev, HCI_OP_AUTH_REQUESTED,
			     माप(cp), &cp);

		/* If we're alपढ़ोy encrypted set the REAUTH_PEND flag,
		 * otherwise set the ENCRYPT_PEND.
		 */
		अगर (test_bit(HCI_CONN_ENCRYPT, &conn->flags))
			set_bit(HCI_CONN_REAUTH_PEND, &conn->flags);
		अन्यथा
			set_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags);
	पूर्ण

	वापस 0;
पूर्ण

/* Encrypt the link */
अटल व्योम hci_conn_encrypt(काष्ठा hci_conn *conn)
अणु
	BT_DBG("hcon %p", conn);

	अगर (!test_and_set_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags)) अणु
		काष्ठा hci_cp_set_conn_encrypt cp;
		cp.handle  = cpu_to_le16(conn->handle);
		cp.encrypt = 0x01;
		hci_send_cmd(conn->hdev, HCI_OP_SET_CONN_ENCRYPT, माप(cp),
			     &cp);
	पूर्ण
पूर्ण

/* Enable security */
पूर्णांक hci_conn_security(काष्ठा hci_conn *conn, __u8 sec_level, __u8 auth_type,
		      bool initiator)
अणु
	BT_DBG("hcon %p", conn);

	अगर (conn->type == LE_LINK)
		वापस smp_conn_security(conn, sec_level);

	/* For sdp we करोn't need the link key. */
	अगर (sec_level == BT_SECURITY_SDP)
		वापस 1;

	/* For non 2.1 devices and low security level we करोn't need the link
	   key. */
	अगर (sec_level == BT_SECURITY_LOW && !hci_conn_ssp_enabled(conn))
		वापस 1;

	/* For other security levels we need the link key. */
	अगर (!test_bit(HCI_CONN_AUTH, &conn->flags))
		जाओ auth;

	/* An authenticated FIPS approved combination key has sufficient
	 * security क्रम security level 4. */
	अगर (conn->key_type == HCI_LK_AUTH_COMBINATION_P256 &&
	    sec_level == BT_SECURITY_FIPS)
		जाओ encrypt;

	/* An authenticated combination key has sufficient security क्रम
	   security level 3. */
	अगर ((conn->key_type == HCI_LK_AUTH_COMBINATION_P192 ||
	     conn->key_type == HCI_LK_AUTH_COMBINATION_P256) &&
	    sec_level == BT_SECURITY_HIGH)
		जाओ encrypt;

	/* An unauthenticated combination key has sufficient security क्रम
	   security level 1 and 2. */
	अगर ((conn->key_type == HCI_LK_UNAUTH_COMBINATION_P192 ||
	     conn->key_type == HCI_LK_UNAUTH_COMBINATION_P256) &&
	    (sec_level == BT_SECURITY_MEDIUM || sec_level == BT_SECURITY_LOW))
		जाओ encrypt;

	/* A combination key has always sufficient security क्रम the security
	   levels 1 or 2. High security level requires the combination key
	   is generated using maximum PIN code length (16).
	   For pre 2.1 units. */
	अगर (conn->key_type == HCI_LK_COMBINATION &&
	    (sec_level == BT_SECURITY_MEDIUM || sec_level == BT_SECURITY_LOW ||
	     conn->pin_length == 16))
		जाओ encrypt;

auth:
	अगर (test_bit(HCI_CONN_ENCRYPT_PEND, &conn->flags))
		वापस 0;

	अगर (initiator)
		set_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags);

	अगर (!hci_conn_auth(conn, sec_level, auth_type))
		वापस 0;

encrypt:
	अगर (test_bit(HCI_CONN_ENCRYPT, &conn->flags)) अणु
		/* Ensure that the encryption key size has been पढ़ो,
		 * otherwise stall the upper layer responses.
		 */
		अगर (!conn->enc_key_size)
			वापस 0;

		/* Nothing अन्यथा needed, all requirements are met */
		वापस 1;
	पूर्ण

	hci_conn_encrypt(conn);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_conn_security);

/* Check secure link requirement */
पूर्णांक hci_conn_check_secure(काष्ठा hci_conn *conn, __u8 sec_level)
अणु
	BT_DBG("hcon %p", conn);

	/* Accept अगर non-secure or higher security level is required */
	अगर (sec_level != BT_SECURITY_HIGH && sec_level != BT_SECURITY_FIPS)
		वापस 1;

	/* Accept अगर secure or higher security level is alपढ़ोy present */
	अगर (conn->sec_level == BT_SECURITY_HIGH ||
	    conn->sec_level == BT_SECURITY_FIPS)
		वापस 1;

	/* Reject not secure link */
	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_conn_check_secure);

/* Switch role */
पूर्णांक hci_conn_चयन_role(काष्ठा hci_conn *conn, __u8 role)
अणु
	BT_DBG("hcon %p", conn);

	अगर (role == conn->role)
		वापस 1;

	अगर (!test_and_set_bit(HCI_CONN_RSWITCH_PEND, &conn->flags)) अणु
		काष्ठा hci_cp_चयन_role cp;
		bacpy(&cp.bdaddr, &conn->dst);
		cp.role = role;
		hci_send_cmd(conn->hdev, HCI_OP_SWITCH_ROLE, माप(cp), &cp);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hci_conn_चयन_role);

/* Enter active mode */
व्योम hci_conn_enter_active_mode(काष्ठा hci_conn *conn, __u8 क्रमce_active)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;

	BT_DBG("hcon %p mode %d", conn, conn->mode);

	अगर (conn->mode != HCI_CM_SNIFF)
		जाओ समयr;

	अगर (!test_bit(HCI_CONN_POWER_SAVE, &conn->flags) && !क्रमce_active)
		जाओ समयr;

	अगर (!test_and_set_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->flags)) अणु
		काष्ठा hci_cp_निकास_snअगरf_mode cp;
		cp.handle = cpu_to_le16(conn->handle);
		hci_send_cmd(hdev, HCI_OP_EXIT_SNIFF_MODE, माप(cp), &cp);
	पूर्ण

समयr:
	अगर (hdev->idle_समयout > 0)
		queue_delayed_work(hdev->workqueue, &conn->idle_work,
				   msecs_to_jअगरfies(hdev->idle_समयout));
पूर्ण

/* Drop all connection on the device */
व्योम hci_conn_hash_flush(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn *c, *n;

	BT_DBG("hdev %s", hdev->name);

	list_क्रम_each_entry_safe(c, n, &h->list, list) अणु
		c->state = BT_CLOSED;

		hci_disconn_cfm(c, HCI_ERROR_LOCAL_HOST_TERM);
		hci_conn_del(c);
	पूर्ण
पूर्ण

/* Check pending connect attempts */
व्योम hci_conn_check_pending(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_conn *conn;

	BT_DBG("hdev %s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_state(hdev, ACL_LINK, BT_CONNECT2);
	अगर (conn)
		hci_acl_create_connection(conn);

	hci_dev_unlock(hdev);
पूर्ण

अटल u32 get_link_mode(काष्ठा hci_conn *conn)
अणु
	u32 link_mode = 0;

	अगर (conn->role == HCI_ROLE_MASTER)
		link_mode |= HCI_LM_MASTER;

	अगर (test_bit(HCI_CONN_ENCRYPT, &conn->flags))
		link_mode |= HCI_LM_ENCRYPT;

	अगर (test_bit(HCI_CONN_AUTH, &conn->flags))
		link_mode |= HCI_LM_AUTH;

	अगर (test_bit(HCI_CONN_SECURE, &conn->flags))
		link_mode |= HCI_LM_SECURE;

	अगर (test_bit(HCI_CONN_FIPS, &conn->flags))
		link_mode |= HCI_LM_FIPS;

	वापस link_mode;
पूर्ण

पूर्णांक hci_get_conn_list(व्योम __user *arg)
अणु
	काष्ठा hci_conn *c;
	काष्ठा hci_conn_list_req req, *cl;
	काष्ठा hci_conn_info *ci;
	काष्ठा hci_dev *hdev;
	पूर्णांक n = 0, size, err;

	अगर (copy_from_user(&req, arg, माप(req)))
		वापस -EFAULT;

	अगर (!req.conn_num || req.conn_num > (PAGE_SIZE * 2) / माप(*ci))
		वापस -EINVAL;

	size = माप(req) + req.conn_num * माप(*ci);

	cl = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!cl)
		वापस -ENOMEM;

	hdev = hci_dev_get(req.dev_id);
	अगर (!hdev) अणु
		kमुक्त(cl);
		वापस -ENODEV;
	पूर्ण

	ci = cl->conn_info;

	hci_dev_lock(hdev);
	list_क्रम_each_entry(c, &hdev->conn_hash.list, list) अणु
		bacpy(&(ci + n)->bdaddr, &c->dst);
		(ci + n)->handle = c->handle;
		(ci + n)->type  = c->type;
		(ci + n)->out   = c->out;
		(ci + n)->state = c->state;
		(ci + n)->link_mode = get_link_mode(c);
		अगर (++n >= req.conn_num)
			अवरोध;
	पूर्ण
	hci_dev_unlock(hdev);

	cl->dev_id = hdev->id;
	cl->conn_num = n;
	size = माप(req) + n * माप(*ci);

	hci_dev_put(hdev);

	err = copy_to_user(arg, cl, size);
	kमुक्त(cl);

	वापस err ? -EFAULT : 0;
पूर्ण

पूर्णांक hci_get_conn_info(काष्ठा hci_dev *hdev, व्योम __user *arg)
अणु
	काष्ठा hci_conn_info_req req;
	काष्ठा hci_conn_info ci;
	काष्ठा hci_conn *conn;
	अक्षर __user *ptr = arg + माप(req);

	अगर (copy_from_user(&req, arg, माप(req)))
		वापस -EFAULT;

	hci_dev_lock(hdev);
	conn = hci_conn_hash_lookup_ba(hdev, req.type, &req.bdaddr);
	अगर (conn) अणु
		bacpy(&ci.bdaddr, &conn->dst);
		ci.handle = conn->handle;
		ci.type  = conn->type;
		ci.out   = conn->out;
		ci.state = conn->state;
		ci.link_mode = get_link_mode(conn);
	पूर्ण
	hci_dev_unlock(hdev);

	अगर (!conn)
		वापस -ENOENT;

	वापस copy_to_user(ptr, &ci, माप(ci)) ? -EFAULT : 0;
पूर्ण

पूर्णांक hci_get_auth_info(काष्ठा hci_dev *hdev, व्योम __user *arg)
अणु
	काष्ठा hci_auth_info_req req;
	काष्ठा hci_conn *conn;

	अगर (copy_from_user(&req, arg, माप(req)))
		वापस -EFAULT;

	hci_dev_lock(hdev);
	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &req.bdaddr);
	अगर (conn)
		req.type = conn->auth_type;
	hci_dev_unlock(hdev);

	अगर (!conn)
		वापस -ENOENT;

	वापस copy_to_user(arg, &req, माप(req)) ? -EFAULT : 0;
पूर्ण

काष्ठा hci_chan *hci_chan_create(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_dev *hdev = conn->hdev;
	काष्ठा hci_chan *chan;

	BT_DBG("%s hcon %p", hdev->name, conn);

	अगर (test_bit(HCI_CONN_DROP, &conn->flags)) अणु
		BT_DBG("Refusing to create new hci_chan");
		वापस शून्य;
	पूर्ण

	chan = kzalloc(माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस शून्य;

	chan->conn = hci_conn_get(conn);
	skb_queue_head_init(&chan->data_q);
	chan->state = BT_CONNECTED;

	list_add_rcu(&chan->list, &conn->chan_list);

	वापस chan;
पूर्ण

व्योम hci_chan_del(काष्ठा hci_chan *chan)
अणु
	काष्ठा hci_conn *conn = chan->conn;
	काष्ठा hci_dev *hdev = conn->hdev;

	BT_DBG("%s hcon %p chan %p", hdev->name, conn, chan);

	list_del_rcu(&chan->list);

	synchronize_rcu();

	/* Prevent new hci_chan's to be created क्रम this hci_conn */
	set_bit(HCI_CONN_DROP, &conn->flags);

	hci_conn_put(conn);

	skb_queue_purge(&chan->data_q);
	kमुक्त(chan);
पूर्ण

व्योम hci_chan_list_flush(काष्ठा hci_conn *conn)
अणु
	काष्ठा hci_chan *chan, *n;

	BT_DBG("hcon %p", conn);

	list_क्रम_each_entry_safe(chan, n, &conn->chan_list, list)
		hci_chan_del(chan);
पूर्ण

अटल काष्ठा hci_chan *__hci_chan_lookup_handle(काष्ठा hci_conn *hcon,
						 __u16 handle)
अणु
	काष्ठा hci_chan *hchan;

	list_क्रम_each_entry(hchan, &hcon->chan_list, list) अणु
		अगर (hchan->handle == handle)
			वापस hchan;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा hci_chan *hci_chan_lookup_handle(काष्ठा hci_dev *hdev, __u16 handle)
अणु
	काष्ठा hci_conn_hash *h = &hdev->conn_hash;
	काष्ठा hci_conn *hcon;
	काष्ठा hci_chan *hchan = शून्य;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(hcon, &h->list, list) अणु
		hchan = __hci_chan_lookup_handle(hcon, handle);
		अगर (hchan)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस hchan;
पूर्ण

u32 hci_conn_get_phy(काष्ठा hci_conn *conn)
अणु
	u32 phys = 0;

	/* BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 2, Part B page 471:
	 * Table 6.2: Packets defined क्रम synchronous, asynchronous, and
	 * CSB logical transport types.
	 */
	चयन (conn->type) अणु
	हाल SCO_LINK:
		/* SCO logical transport (1 Mb/s):
		 * HV1, HV2, HV3 and DV.
		 */
		phys |= BT_PHY_BR_1M_1SLOT;

		अवरोध;

	हाल ACL_LINK:
		/* ACL logical transport (1 Mb/s) ptt=0:
		 * DH1, DM3, DH3, DM5 and DH5.
		 */
		phys |= BT_PHY_BR_1M_1SLOT;

		अगर (conn->pkt_type & (HCI_DM3 | HCI_DH3))
			phys |= BT_PHY_BR_1M_3SLOT;

		अगर (conn->pkt_type & (HCI_DM5 | HCI_DH5))
			phys |= BT_PHY_BR_1M_5SLOT;

		/* ACL logical transport (2 Mb/s) ptt=1:
		 * 2-DH1, 2-DH3 and 2-DH5.
		 */
		अगर (!(conn->pkt_type & HCI_2DH1))
			phys |= BT_PHY_EDR_2M_1SLOT;

		अगर (!(conn->pkt_type & HCI_2DH3))
			phys |= BT_PHY_EDR_2M_3SLOT;

		अगर (!(conn->pkt_type & HCI_2DH5))
			phys |= BT_PHY_EDR_2M_5SLOT;

		/* ACL logical transport (3 Mb/s) ptt=1:
		 * 3-DH1, 3-DH3 and 3-DH5.
		 */
		अगर (!(conn->pkt_type & HCI_3DH1))
			phys |= BT_PHY_EDR_3M_1SLOT;

		अगर (!(conn->pkt_type & HCI_3DH3))
			phys |= BT_PHY_EDR_3M_3SLOT;

		अगर (!(conn->pkt_type & HCI_3DH5))
			phys |= BT_PHY_EDR_3M_5SLOT;

		अवरोध;

	हाल ESCO_LINK:
		/* eSCO logical transport (1 Mb/s): EV3, EV4 and EV5 */
		phys |= BT_PHY_BR_1M_1SLOT;

		अगर (!(conn->pkt_type & (ESCO_EV4 | ESCO_EV5)))
			phys |= BT_PHY_BR_1M_3SLOT;

		/* eSCO logical transport (2 Mb/s): 2-EV3, 2-EV5 */
		अगर (!(conn->pkt_type & ESCO_2EV3))
			phys |= BT_PHY_EDR_2M_1SLOT;

		अगर (!(conn->pkt_type & ESCO_2EV5))
			phys |= BT_PHY_EDR_2M_3SLOT;

		/* eSCO logical transport (3 Mb/s): 3-EV3, 3-EV5 */
		अगर (!(conn->pkt_type & ESCO_3EV3))
			phys |= BT_PHY_EDR_3M_1SLOT;

		अगर (!(conn->pkt_type & ESCO_3EV5))
			phys |= BT_PHY_EDR_3M_3SLOT;

		अवरोध;

	हाल LE_LINK:
		अगर (conn->le_tx_phy & HCI_LE_SET_PHY_1M)
			phys |= BT_PHY_LE_1M_TX;

		अगर (conn->le_rx_phy & HCI_LE_SET_PHY_1M)
			phys |= BT_PHY_LE_1M_RX;

		अगर (conn->le_tx_phy & HCI_LE_SET_PHY_2M)
			phys |= BT_PHY_LE_2M_TX;

		अगर (conn->le_rx_phy & HCI_LE_SET_PHY_2M)
			phys |= BT_PHY_LE_2M_RX;

		अगर (conn->le_tx_phy & HCI_LE_SET_PHY_CODED)
			phys |= BT_PHY_LE_CODED_TX;

		अगर (conn->le_rx_phy & HCI_LE_SET_PHY_CODED)
			phys |= BT_PHY_LE_CODED_RX;

		अवरोध;
	पूर्ण

	वापस phys;
पूर्ण
